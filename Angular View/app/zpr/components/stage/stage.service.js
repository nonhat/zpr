(function () {
	angular
		.module('zpr.app-module')
		.constant('bonsai.event:sim.start', 'message:sim.start')
		.constant('bonsai.init.data', 'init.data')
		.constant('bonsai.sim.data', 'sim.data')
		.provider('StageServiceProvider', [
			StageServiceProvider
		]);

	var bonsaiUrl = 'app/zpr/components/bonsai/bonsai.logic.js';
	
	function StageServiceProvider () {
		
		this.setBonsaiLogic = function (url) {
			bonsaiUrl = url;
		}
		
		this.$get = [
			'$log',
			'bonsai.event:sim.start',
			'bonsai.init.data',
			'bonsai.sim.data',
			'CommServiceProvider',
			'PlayerService',
			ServiceFactory
		];
	}

	function ServiceFactory ($log, simStart, initData, simData, communication, player) {
		var srv = {};
		var bonsaiProcess = null;
		var yAxis = null;
		
		srv.start = function ($element) {
			if (!($element instanceof angular.element)) {
				throw new Error('Wrong input data, expected angular.element');
			}			

			if (bonsaiUrl === null) {
				throw new Error('Bonsai URL required');
			}

			yAxis = $element[0].offsetHeight;

			bonsaiProcess = bonsai.run($element[0], {
				url: bonsaiUrl,
				width: $element[0].offsetWidth,
		    	height: $element[0].offsetHeight
			});

			bonsaiProcess.on(simStart, simiulate);

		}

		srv.pause = function(val) {
			if(val) {
				bonsaiProcess.sendMessage('pause');
			} else {
				bonsaiProcess.sendMessage('continiue');
			}
		}

		srv.loadInitialData = function () {
			communication.getInitialData(player.actualStage, initDataCallback);

			function initDataCallback(serverData)  {
				var bonsaiData = prepareInitData(serverData);
				bonsaiProcess.sendMessage(initData, bonsaiData);
			}
		}

		function simiulate (missleData) {
			communication.getSimilationData(missleData, simDataCallback);
			
			function simDataCallback (serverData) {
				var bonsaiData = prepareSimData(serverData);
				bonsaiProcess.sendMessage(simData, bonsaiData);
			} 

		}

		function prepareInitData(serverData) {
			srv.interval = serverData.animationInterval;
			convertYAxis(serverData.missle.start);
			return serverData;
		}

		function prepareSimData(serverData) {
			var animationTime = srv.interval * serverData.missleData.frames.length + 'ms';
			
			var missleData = prepareAnimationFrames(serverData.missleData.frames);

			var objectsData = [];

			serverData.objectsData.forEach(function (el, index) {
				var objectData = prepareAnimationFrames(el.frames, el.startFrame);
				objectsData.push({
					id: el.objectID,
					path: objectData.path,
					animationTime: objectData.animationTime
				});
			});

			return {
				missle: missleData,
				objects: objectsData
			};
		}

		function convertYAxis(point) {
			point.y =  yAxis - point.y;
		}

		function prepareAnimationFrames(frames, repeateFirst) {
			var path = {};
			
			if (frames.length === 0) {
				$log.info('frames array is empty');
				return;
			}

			if(repeateFirst) {
				frames.unshift(frames[0]);
			}

			var animationTime = srv.interval * frames.length + 'ms';
			frames.forEach(function (el, index) {
				convertYAxis(el);
				path[srv.interval * index + 'ms'] = el;
			});

			return {
				animationTime: animationTime,
				path: path
			}
		}
		
		return srv;
	}


})();