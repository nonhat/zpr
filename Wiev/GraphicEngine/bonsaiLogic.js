(function() {
	var missle;

	stage.on('message:actionData', handleActionData);
	stage.on('message:initialStageData', handleInitialStageData);
	stage.on('message:objectsData', handleObjectsData);
	
	function handleActionData(actionData) {
		handleMissleData(actionData.missle);
	}

	function handleMissleData (missleData) {
		var path = missleData.path;
		var interval = missleData.animationInterval;
		var animation = prepareKeyFrameAnimation(path, interval);

		missle.animate(animation);
	}

	function handleInitialStageData (stageData) {
		console.log('jestem w handleInitialStageData');
		if(!stageData.objects) {
			throw new Error('missing configuration');
		}
		
		var missleData = stageData.objects.missle;
		var pos = missleData.startPosition;

		missle = new Circle(pos.x, pos.y, missleData.missleSize);

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
		
		stage.sendMessage('mapResolved', {});		
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