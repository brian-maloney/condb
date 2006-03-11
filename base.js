function newID() {
	var nowDate = new Date();
	return "id" + String(hex_md5(String(nowDate.valueOf()) + String(Math.abs(Math.random * 1000)))).substr(10, 6);
}

function newDiv(id, className) {
	newNode = document.createElement("div");
	if (id != "") newNode.id = id;
	if (className != "") newNode.className = className;
	return newNode;
}

function newSpan(className) {
	newNode = document.createElement("span");
	if (className != "") newNode.className = className;
	return newNode;
}

function newInput(id, className, type, name, value) {
	newNode = document.createElement("input");
	if (id != "") newNode.id = id;
	if (className != "") newNode.className = className;
	if (type != "") newNode.type = type;
	if (name != "") newNode.name = name;
	if (value != "") newNode.value = value;
	return newNode;
}

function newSelect(name) {
	newNode = document.createElement("select");
	if (name != "") newNode.name = name;
	return newNode;
}

function newOption(label, value) {
	newNode = document.createElement("option");
	if (value != "") newNode.value = value;
	newNode.appendChild(document.createTextNode(label));
	return newNode;
}

function newSection(className, label) {
	sec = newSpan(className);
	sec.appendChild(newSpan("label"));
	sec.lastChild.appendChild(document.createTextNode(label));
	return sec;
}

function setDateBox(DateBox) {
	with (new Date()) DateBox.value=(getMonth()+1) + "/" +  getDate() + "/" + getFullYear();
}

function createRequestObject() {
	var xmlHttpReq = false;
    
	// Mozilla/Safari
	if (window.XMLHttpRequest) {
		xmlHttpReq = new XMLHttpRequest();
		xmlHttpReq.overrideMimeType('text/xml');
	}
	// IE
	else if (window.ActiveXObject) {
		xmlHttpReq = new ActiveXObject("Microsoft.XMLHTTP");
	}

	return xmlHttpReq;
}

ajaxHTTP = createRequestObject();

function ajaxRequest(target, action, data) {
	var requestString = "ajax.php?target=" + target + "&action=" + action;
	if (data) requestString = requestString + "&data=" + data;
	ajaxHTTP.open("get", requestString);
	ajaxHTTP.onreadystatechange = ajaxCallback;
	ajaxHTTP.send(null);
}

function ajaxCallback() {
	if (ajaxHTTP.readyState == 4) {
		var response = ajaxHTTP.responseText;
		var targetRE = new RegExp("<target>(.*)</target>", 'i');
		var dataRE = new RegExp("<data>(.*)</data>", 'i');

		targetMatch = targetRE.exec(response);
		if (dataMatch = dataRE.exec(response)) document.getElementById(targetMatch[1]).innerHTML = dataMatch[1];
	}
}
