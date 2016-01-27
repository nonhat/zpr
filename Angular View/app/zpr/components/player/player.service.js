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

		srv.authenticated = false;
		srv.actualStage = 0;
		srv.userName = null;

		srv.setPlayerData = function (data, authenticated) {
			this.authenticated = authenticated;
			this.userName = data.user;
			this.actualStage = data.actualStage;
			$rootScope.$emit(userInfo);	
		};

		srv.createAnonim = function () {
			var data = {
				user: 'anonym',
				actualStage: 0
			}
			this.setPlayerData(data);
		}

		return srv;
	}
})();