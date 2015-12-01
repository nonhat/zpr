(function(zpr) {
	zpr.Notyficator = Notyficator;

	function Notyficator() {
		this.eventContexts = {};
	} 


	Notyficator.prototype.addListener = function(evname, callback, context) {
	    if (!this.eventContexts[evname]) {
	      	this.eventContexts[evname] = [];
	    }

	    this.eventContexts[evname].push({
	    	callback: callback,
	    	context: context
	    });
	}

	Notyficator.prototype.removeEvent = function(evname) {
	    if (!this.eventContexts[evname]) {
	      return;
	    }
	    this.eventContexts[evname] = undefined;
	}

	Notyficator.prototype.triggerEvent = function(evname, data) {
		if (this.eventContexts[evname]) {
			this.eventContexts[evname].forEach(function(eventContext) {
			 	eventContext.callback.call(eventContext.context, data);
			});
		}
	}

})(window.zpr ? window.zpr : window.zpr = {})