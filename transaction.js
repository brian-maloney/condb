function newtransaction() {
	var myID = newID();
	var idstring = "transaction_" + myID + "_editor";
	var newRoot = newDiv(idstring, "transaction_editor");
	ajaxRequest(idstring, "new_obj_editor", "transaction(" + myID + ");");
	return newRoot;
}
