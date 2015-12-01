(function(zpr){
	
	zpr.init = function() {

		var bonsaiProcess = bonsai.run(document.getElementById('stage'), {
			url: '/static/GraphicEngine/bonsaiLogic.js',
			width: 1000,
	    	height: 500
		});


		var Service = new zpr.Service();
		var Communication = new zpr.CommunicationManager(bonsaiProcess);
		var DataHandler = new zpr.DataHandler(Communication, Service);

		DataHandler.loadNewStage('1');
	}

})(window.zpr ? window.zpr : window.zpr = {})