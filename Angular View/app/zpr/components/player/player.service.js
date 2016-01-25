(function() {
	angular
		.module('zpr.app-module')
		.factory('PlayerService', [
			'$rootScope',
			'zpr.event:userInfo',
			PlayerService
		]);

	function PlayerService ($rootScope, userInfo) {
		var srv = {};

		srv.actualStage = 0;
		srv.userName = null;

		srv.setPlayerData = function (data) {
			this.userName = data.user;
			this.actualStage = data.actualStage;
			$rootScope.$emit(userInfo);	
		};
		return srv;
	}
})();