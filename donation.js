function newdonation() {
	var myID = newID();
	var newRoot = newDiv("donation_" + myID + "_editor", "donation_editor");
	newRoot.appendChild(newInput("", "", "hidden", "editobj_donation_" + myID, "true"));
	newRoot.appendChild(document.createTextNode(" "));
	newRoot.appendChild(newInput("", "", "hidden", "donation_" + myID + "_ca", currentCA));
	newRoot.appendChild(document.createTextNode("Donation: "));
	var newNode = newRoot.appendChild(newSection("price", "Price"));
	var newNode2 = newInput("", "price", "text", "donation_" + myID + "_price", "");
	newNode2.value = "$0.00";
	var oc = document.createAttribute("onchange");
        oc.value = "updateTotal()";
        newNode2.attributes.setNamedItem(oc);
	newNode.appendChild(newNode2);
	newNode.appendChild(document.createTextNode(" "));
	newRoot.appendChild(document.createTextNode(" "));
	return newRoot;
}
