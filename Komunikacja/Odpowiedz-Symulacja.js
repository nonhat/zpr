//w kazdej klatce obiekt ma: położenie x,y i rotację r.

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