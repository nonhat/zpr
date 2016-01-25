(function () {
	/*******************/console.log('TEST: loaded bonsai');
	var missle = null;
	var objects = {};
	

	stage.on('message:init.data', evaluateInitialData);
	stage.on('message:sim.data', evaluteSimulation);

	function evaluateInitialData (bonsaiData) {
		/*******************/console.log('TEST: event handled');
		evaluateGround(bonsaiData.missle);
		evaluateMissle(bonsaiData.missle);
		evaluateObjects(bonsaiData.objects);
	}

	function evaluateMissle(missleData) {
		var start = missleData.start;
		missle = new Circle(start.x, start.y, 10);
		missle.start = start;
		//TODO czy to jest na pewno potrzebne?
		missle.on('drag', function(event) {
			this.attr({
				x: event.x,
				y: event.y
			});
		});

		missle.on('pointerup', function(event) {
			stage.sendMessage('sim.start', {
				x: event.x - missle.start.x,
				y: event.y - missle.start.y
			});
		});
		
		missle.fill('red');

		missle.addTo(stage);
	}

	function evaluateObjects(objs) {
		objs.forEach(function(obj, index) {
			evaluateObject(obj);
		});
	}

	function evaluateObject(obj) {
		var x = obj.x;
		var y = obj.y;
		var side = obj.side;
		var newObject = new Rect(x, y, side, side/*[,cornerRadius]*/);

		newObject.addTo(stage);
		objects[obj.id] = newObject;
	}

	function evaluateGround(ground) {

	}

	function evaluteSimulation(bonsaiData) {
		var animations = [];
		var missleAnmation = {
			screenpaly: new KeyframeAnimation(bonsaiData.missle.animationTime, bonsaiData.missle.path)
		}
		
		
		bonsaiData.objects.forEach(function(obj) {
			animations.push({
				id: obj.id,
				screenpaly: new KeyframeAnimation(obj.animationTime, obj.path)
			});
		});

		missle.animate(missleAnmation.screenpaly);

		animations.forEach(function (animation) {
			var object = objects[animation.id]; 
			object.animate(animation.screenpaly);
		});
	}

	function resetMissle() {
		missle.x  = missle.start.x;
		missle.y  = missle.start.y; 
	}
	
	/*function setMisslePath(path, interval) {
		if (!missle) {
			createMissle();
		}

		prepareKeyFrameAnimation(path, interval);
	}

	function setMisslePosition(pos) {
		missle.x = pos.x;
		missle.y = pos.y;
	}*/

})();