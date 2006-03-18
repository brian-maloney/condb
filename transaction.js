function newtransaction() {
	var myID = newID();
	var idstring = "transaction_" + myID + "_editor";
	var newRoot = newDiv(idstring, "transaction_editor");
	ajaxRequest(idstring, "new_obj_editor", "transaction(" + myID + ");");
	return newRoot;
}

function linktranslist() {
	var newRoot = newDiv("translist", "");
	ajaxRequest("translist", "transaction_picker");
	return newRoot;
}

function linktransaction() {
	var transNum = document.getElementById("transid").value;
	var transRoot = document.getElementById("translist");
	transRoot.id = "transaction_" + transNum + "_editor";
	transRoot.className = "transaction_editor";
	//while (transRoot.hasChildNodes()) transRoot.removeChild(transRoot.firstChild);
	ajaxRequest("transaction_" + transNum + "_editor", "new_obj_editor", "transaction(" + transNum + ");");
}
