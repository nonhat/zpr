(function() {
	angular
		.module('zpr.app-module')
		.directive('stage', ['StageServiceProvider', Stage]);

		function Stage (stage) {
			return {
				require: '^^stagePanel',
				restrict: 'A',
				scope: {},
				templateUrl: 'app/zpr/components/stagePanel/stage/stage.html',
				controller: [
					'$scope',
					'$rootScope',
					'StageServiceProvider',
					Ctrl
				],
				controllerAs: 'ctrl',
				link: function ($scope, $element, $attr, stagePanel) {
					$scope.$watch(function () {
						return stagePanel.initStage;
					}, function(newVal, oldVal) {
						if(newVal) {
							stage.loadInitialData();
						} else {

						}
					});

					stage.start($element);
				}
			}
		}



		function Ctrl ($scope, $rootScope, stage) {
			var ctrl = this;
			this.pasued = false;

			//TODO sprawdzic czy wystarczy ctrl.init
			/*$scope.$watch(function () {
					return ctrl.init;
				}, 
				function(newVal, oldVal) {
					if(newVal) {
						stage.loadInitialData();
					} else {

					}
				});
*/
			
		}

})();