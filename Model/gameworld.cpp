
#include "gameworld.h" 


GameWorld::GameWorld(const char *name){
    missleStartPos = Vector2(50,50);
    
    const int squareSize = 40;
    
    std::vector<Vector2> squarePoints = {
        Vector2(-squareSize,-squareSize),
        Vector2(squareSize,-squareSize),
        Vector2(squareSize,squareSize),
        Vector2(-squareSize,squareSize)
    };
    
    squareShape = new BoShape(squarePoints, 10.f);
    missleEntity = new BoEntity(squareShape,1.f,1.f);
    missleEntity->SetPosition(missleStartPos);
    
    world.gravity = Vector2(0.f,-1.f);
    world.ground_level = -100.f;
    world.AddEntity(missleEntity);
    
}

GameWorld::~GameWorld(){
    delete missleEntity;
    delete squareShape;
}

/*
 * map:{
    name: nazwa,
    size: {x:x, y:y},
    missle:{
        start: {x:x, y:y},
    },
    objects:[{
            id:id lub nazwa,
            x:x,
            y:y,
            r:rotacja
        },
		...
	],
    ground:{
        to już na późniejszy etap....
    }
}

 * */

std::string GameWorld::GetMapInfoInJSON(){
    std::ostringstream ret;
    ret << "{\n"
        "\t\"name\": \"round1\",\n"
        "\t\"size\": {\"x\":1000, \"y\":400},\n"
        "\t\"missle\": {\n"
        "\t\t\"startPosition\": {\"x\":";
    
    Vector2 MisslePos = missleEntity->GetPosition();
    ret << MisslePos.x << ", \"y\":" << MisslePos.y << "},\n"
        "\t\t\"start\": {\"x\":";
    
    ret << MisslePos.x << ", \"y\":" << MisslePos.y << "}\n";
    ret << "\t},\n"
        "\t\"objects\":[]\n"
        "}\n";
            
    return ret.str();
}
/*
simulation:{
    objectsData:[{
            objectID: id, //dla potrzeb graficznej reprezentacji
            startFrame: pierwsza klatka symulacji,
            frames: [
                {x:x, y:y, r:rotacja},
                ...
            ]
        },
        ...
    ],
    missleData:{        
		frames:[ 
			{x:x, y:y, r:rotacja},
			...
		]                
    }
}
*/
std::string GameWorld::GetSimulationJSON(float shootX, float shootY){
    std::ostringstream ret;
    std::ostringstream missleFrames;
    missleEntity->SetSpeed(Vector2(shootX,shootY));
    
    bool firstEntityEntry = true;
    for(int i = 0; i < 200; ++i){
        world.Simulate(0.5f);
        for(std::vector<BoEntity*>::iterator it = world.entities.begin();
			it != world.entities.end();
			++it){
            BoEntity* e = *it;
            if(e==missleEntity){
                Vector2 pos = e->GetPosition();
                if(!firstEntityEntry)
                    missleFrames << ",\n";
                missleFrames << "\t\t\t{\"x\":" << pos.x << ", \"y\":" << pos.y;
                missleFrames << ", \"r\":" << e->GetRotation() << "}";
                firstEntityEntry = false;
            }
        }
    }
    
    ret << "{\n"
        "\t\"objectsData\":[],\n"
        "\t\"missleData\":{\n"
        "\t\t\"frames\":[\n";
    ret << missleFrames.str();
    ret << "\t\t]\n"
        "\t}\n"
        "}\n";
    
    
    return ret.str();
    
}
