(function(){
	angular
		.module('zpr.app-module')
		.directive('stagePanel', StagePanel);


	function StagePanel() {
		return {
			restrict: 'A',
			templateUrl: 'app/zpr/components/stage/stagePanel.html',
			scope: {},
			controller: [Ctrl],
			controllerAs: 'ctrl'
		}
	}

	function Ctrl () {
		this.menuVisible = false;
		this.initStage = false;
		this.loggedIn = false;

		this.init = function () {
			this.initStage = true;
		} 

		this.hideMenu = function () {
			this.menuVisible = false;
		} 

		this.showMenu = function () {
			this.menuVisible = true;
		}
	}	

})()