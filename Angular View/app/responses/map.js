(function (){

    var map = {
        name: 'nazwa',
        size: {
            x:500, 
            y:300
        },
        animationInterval: 10,
        missle:{
            start: {
                x:20, 
                y:20
            }
        },
        objects:[
        {
                id: 'ob1',
                x:100,
                y:20,
                side: 10, //długość boku 
                r: 0.5
        }],
        ground:{}
    };

    angular
        .module('zpr.app-module')
        .constant('http.resp.map', map);

})();