(function(zpr, notyficator) {
	zpr.DataHandler = DataHandler;

	function DataHandler(communication, service) {
		this.communication = communication;
		this.service = service;
		notyficator.addListener('missleFiered', getActionData, this);
	} 

	DataHandler.prototype.loadNewStage = function (stageId) {
		var that = this;
		
		this.service.getInitialStageData(stageId, function(data) {
			loadCallback.call(that, data)
		});
		
		function loadCallback(data) {
			this.stageSize = data.size;

			var missleData = data.missle;
			transformCoordinateSystem.call(this, missleData.start);
			this.communication.passDataToContext(data,'initialStageData');
		}
	}

	function getActionData () {
		var data = this.service.getActionData();
		var missleData = data.missleData;
		var objectsData = data.objectsData;
		var that = this;
		
		adjustCoordinates.call(this, missleData);
		objectsData.forEach(function(el, index) {
			adjustCoordinates(el);
		})

		this.communication.passDataToContext(data,'actionData');
	}

	function adjustCoordinates(mapObject) {
		var that = this;
		mapObject.frames.map(function(el){
			transformCoordinateSystem.call(that, el);
			return el;
		});
	}

	

	function transformCoordinateSystem (point) {
		point.y = this.stageSize.y - point.y;
	}



})(
	window.zpr ? window.zpr : window.zpr = {},
	window.notyficator ? window.notyficator : window.notyficator = new window.zpr.Notyficator()
)