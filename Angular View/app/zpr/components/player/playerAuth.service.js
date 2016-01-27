(function () {
	angular
		.module('zpr.app-module')
		.constant('zpr.event:userInfo', 'zpr.event:userInfo')
		.factory('PlayerAuthService', [
			'zpr.event:userInfo',
			'CommServiceProvider',
			'PlayerService',
			PlayerAuthService
		]);

	function PlayerAuthService(userInfo, communication, player) {
		var srv = {};
		var currentUser = null;

		srv.authenticate = function (user, pass) {
			communication.authenticate(this.userName, this.password, persistUser);
			function persistUser (userData) {
				if(userData.state = 'AUTHORIZED') {
					player.setPlayerData(userData, true);
				} else {
					currentUser = null;
				}
			};
		}

		return srv;
	}
})();