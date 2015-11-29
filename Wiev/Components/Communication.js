(function(zpr, notyficator) {
	zpr.CommunicationManager = CommunicationManager;

	function CommunicationManager(bonsaiProcess) {
		//TODO sprawdzenie czy bonsiaProcess jest opowiedniego typu
		this.bonsaiProcess = bonsaiProcess;

		this.bonsaiProcess.on('message:mapResolved', onMapResolved);
		this.bonsaiProcess.on('message:missleFiered', onMissleFiered);
	}

	function onMapResolved() {
		notyficator.triggerEvent('mapResolved');
	}

	function onMissleFiered() {
		notyficator.triggerEvent('missleFiered');
	}

	CommunicationManager.prototype.passDataToContext = function (data, dataType) {
		var process = this.bonsaiProcess;
		process.sendMessage(dataType, data);
	}  
})(
	window.zpr ? window.zpr : window.zpr = {},
	window.notyficator ? window.notyficator : window.notyficator = new window.zpr.Notyficator()
)