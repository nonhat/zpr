(function() {

	var missle;

	stage.on('message:actionData', handleActionData);
	stage.on('message:initialStageData', handleInitialStageData);
	stage.on('message:objectsData', handleObjectsData);
	
	function handleActionData(actionData) {
		handleMissleData(actionData.missleData);
	}

	function handleMissleData (missleData) {
		var path = missleData.frames;
		var interval = 10;
		var animation = prepareKeyFrameAnimation(path, interval);

		missle.animate(animation);
	}

	function handleInitialStageData (stageData) {
		if(!stageData.missle || !stageData.objects) {
			throw new Error('missing configuration');
		}
		
		var missleData = stageData.missle;
		evaluateMissle(missleData);
		
		stage.sendMessage('mapResolved', {});		
	}

	function evaluateMissle(missleData) {
		var pos = missleData.start;

		missle = new Circle(pos.x, pos.y, 10);

		missle.on('drag', function(event) {
			this.attr({
				x: event.x,
				y: event.y
			})
		});

		missle.on('pointerup', function(event) {
			stage.sendMessage('missleFiered', {
				x: event.x,
				y: event.y
			});
		});

		missle.addTo(stage);
		missle.attr('fillColor', 'green');
	}

	function handleObjectsData (objectsData) {
		
	}

	function prepareKeyFrameAnimation(path, interval) {
		var steps = {}; 
		var animationTime = interval * path.length;
		path.forEach(function(el, index) {
			steps[interval * index + 'ms'] = el;
		})

		return new KeyframeAnimation(animationTime + 'ms', steps);
	}

})();