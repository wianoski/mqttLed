function update(){
	const socket = io.connect();

	socket.on('led1', (data)=>{
		console.log(data);
		// document.getElementById("receiveData").innerHTML = "Current LED ON " + data.datahasil;
		$("#receiveData-1").text('message ' + data.data + ' on ' + data.topic); 
	});
	socket.on('led2', (data)=>{
		console.log(data);
		// document.getElementById("receiveData").innerHTML = "Current LED ON " + data.datahasil;
		$("#receiveData-2").text('message ' + data.data + ' on ' + data.topic); 
	});
	socket.on('led3', (data)=>{
		console.log(data);
		// document.getElementById("receiveData").innerHTML = "Current LED ON " + data.datahasil;
		$("#receiveData-3").text('message ' + data.data + ' on ' + data.topic); 
	});
	socket.on('runLED', (data)=>{
		console.log(data);
		// document.getElementById("receiveData").innerHTML = "Current LED ON " + data.datahasil;
		$("#receiveData-4").text('message ' + data.data + ' on ' + data.topic); 
	});

}

function slowLED(){
		const socket = io.connect();
		socket.emit('slowLED', true);
		$("#status").text("Slow");
		console.log("slow LED");
}

function mediumLED(){
	const socket = io.connect();
	socket.emit('mediumLED', true);
	$("#status").text("Medium");
	console.log("medium LED");
}

function fastLED(){
	const socket = io.connect();
	socket.emit('fastLED', true);
	$("#status").text("Fast");
	console.log("fast LED");
}

function startLED_1(){
	const socket = io.connect();
	socket.emit('ctrl-led1', {data : true});
	$("#onoroff-1").text("Turn On LED");
	console.log("On LED");
}

function stopLED_1(){
	const socket = io.connect();
	socket.emit('ctrl-led1', {data : false});
	$("#onoroff-1").text("Turn Off LED");
	console.log("Off LED");
}

function startLED_2(){
	const socket = io.connect();
	socket.emit('ctrl-led2', {data : true});
	$("#onoroff-2").text("Turn On LED");
	console.log("On LED");
}

function stopLED_2(){
	const socket = io.connect();
	socket.emit('ctrl-led2', {data : false});
	$("#onoroff-2").text("Turn Off LED");
	console.log("Off LED");
}

function startLED_3(){
	const socket = io.connect();
	socket.emit('ctrl-led3', {data : true});
	$("#onoroff-3").text("Turn On LED");
	console.log("On LED");
}

function stopLED_3(){
	const socket = io.connect();
	socket.emit('ctrl-led3', {data : false});
	$("#onoroff-3").text("Turn Off LED");
	console.log("Off LED");
}

function startRunningLED(){
	const socket = io.connect();
	socket.emit('ctrl-runLED', {data : true});
	$("#onoroff-4").text("Turn ON Runing LED");
	console.log("Turn ON Runing LED");
}

function stopRunningLED(){
	const socket = io.connect();
	socket.emit('ctrl-runLED', {data : false});
	$("#onoroff-4").text("Turn OFF Runing LED");
	console.log("Turn OFF Runing LED");
}

