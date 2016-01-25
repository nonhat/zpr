(function () {
	angular
		.module('zpr.app-module')
		.directive('loginPanel', [
			'$rootScope',
			'zpr.event:userInfo',
			'PlayerService',	
			LoginPanel
		]);

	function LoginPanel ($rootScope, userInfo, player) {
		return {
			require: '^^stagePanel',
			restict: 'A',
			scope: {},
			templateUrl: 'app/zpr/components/stage/loginPanel.html',
			controller: [
				'PlayerAuthService',
				Ctrl
			],
			controllerAs: 'ctrl', 
			link: function ($scope, $element, $attr, stagePanel) {
				
				$rootScope.$on(userInfo, function () {
					if(player.userName) {
						stagePanel.loggedIn = true;
					} else {
						stagePanel.loggedIn = false;
					}
				})
			}
		}
	}



	function Ctrl (playerAuth) {
		this.userLabel = 'User';
		this.passwordLabel = 'Password';

		this.userName = null;
		this.password = null;

		this.authenticateUser = function () {
			playerAuth.authenticate(this.userName, this.password);
		}
	}

})();