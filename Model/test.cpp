//============================================================================
// Name        : Boxing.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Boxing.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_GLContext glcontext;

#define ScreenWidth 800
#define ScreenHeight 600

int InitGraphics(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("Boxing Test",0,0,ScreenWidth,ScreenHeight,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	glcontext = SDL_GL_CreateContext(window);
	atexit(SDL_Quit);
	SDL_RenderPresent(renderer);
	glViewport( 0, 0, ScreenWidth, ScreenHeight );
	glClearColor( 1, 1, 1, 1 );
	glMatrixMode(GL_PROJECTION);
	glOrtho(-ScreenWidth/2, ScreenWidth/2, -ScreenHeight/2, ScreenHeight/2, 50.f, -50.f);
	glMatrixMode(GL_MODELVIEW);

	return 0;
}

void RenderShape(BoShape *shape){
	const std::vector<Vector2> points = shape->GetPointArray();
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(0.f, 0.f, 0.f);
	for(int i = 0; i < points.size(); i++)
		glVertex3f(points[i].x,points[i].y,0.f);

	glEnd();
}

void RenderWorld(BoWorld *world){
	for(std::vector<BoEntity*>::iterator i = world->entities.begin();
			i != world->entities.end();
			i++){
		BoEntity* entity = (*i);
		glLoadIdentity();
		Vector2 pos = entity->GetPosition();
		glTranslatef(pos.x, pos.y, 0);
		glRotatef(entity->GetRotation()*180.f/3.1415f,0.f,0.f,1.f);
		RenderShape(entity->GetShape());
	}
}

int main() {

	InitGraphics();

	//Make a shape out of points. It is user's duty to make sure it is ok.
	std::vector<Vector2> points = {
		Vector2(-100,-50),
		Vector2(100,-50),
		Vector2(100,50),
		Vector2(-100,50)
	};
	BoShape shape(points, 10.f);

	//Make entities with given shape, mass and inertia.
	BoEntity entity(&shape, 1.f, 1.f);
	entity.SetRotation(0.2f);
	BoEntity entity2(&shape, 1.f, 1.f);
	entity2.SetRotation(0.5f);
	entity2.SetPosition(Vector2(-20.f,200.f));
	//entity2.SetSpeed(Vector2(1.f,0.f));
	//entity2.SetOmega(-0.1f);
	entity.isstatic = true;

	//Make world, set same basic rules, and add entities.
	BoWorld world;
	world.gravity = Vector2(0,-1);
	world.ground_level = -100.f;
	world.AddEntity(&entity);
	world.AddEntity(&entity2);

	//Done.

	SDL_Event event;
	while(1){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
				return 0;
		}
		world.Simulate(.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderWorld(&world);

		SDL_GL_SwapWindow(window);
	}
	return 0;
}
