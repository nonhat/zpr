(function(zpr, notyficator) {
	zpr.DataHandler = DataHandler;

	function DataHandler(communication, service) {
		this.communication = communication;
		this.service = service;
		notyficator.addListener('missleFiered', getActionData, this);
	} 

	DataHandler.prototype.loadNewStage = function (stageId) {
		var data = this.service.getInitialStageData(stageId);
		this.stageSize = data.stage.size;

		var missleData = data.objects.missle;
		transformCoordinateSystem.call(this, missleData.startPosition);
		this.communication.passDataToContext(data,'initialStageData');
	}

	function getActionData () {
		var data = this.service.getActionData();
		var missleData = data.missle;
		var that = this;
		
		missleData.path.map(function(el){
			transformCoordinateSystem.call(that, el);
			return el;
		});

		this.communication.passDataToContext(data,'actionData');
	}

	

	function transformCoordinateSystem (point) {
		point.y = this.stageSize.y - point.y;
	}



})(
	window.zpr ? window.zpr : window.zpr = {},
	window.notyficator ? window.notyficator : window.notyficator = new window.zpr.Notyficator()
)