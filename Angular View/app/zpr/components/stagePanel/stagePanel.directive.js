(function(){
	angular
		.module('zpr.app-module')
		.directive('stagePanel', StagePanel);


	function StagePanel() {
		return {
			restrict: 'A',
			templateUrl: 'app/zpr/components/stagePanel/stagePanel.html',
			scope: {},
			controller: [
				'PlayerService',
				Ctrl
			],
			controllerAs: 'ctrl'
		}
	}

	function Ctrl (player) {
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

		this.getCurrentUser = function () {
			return player.userName;
		}
	}	

})()