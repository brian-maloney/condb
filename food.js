function newfood() {
	var myID = newID();
	var newRoot = newDiv("food_" + myID + "_editor", "food_editor");
	newRoot.appendChild(newInput("", "", "hidden", "editobj_food_" + myID, "true"));
	newRoot.appendChild(document.createTextNode(" "));
	newRoot.appendChild(newInput("", "", "hidden", "food_" + myID + "_ca", currentCA));
	newRoot.appendChild(document.createTextNode("Food: "));
	var newNode = newRoot.appendChild(newSection("price", "Price"));
	var newNode2 = newInput("", "price", "text", "food_" + myID + "_price", "");
	newNode2.value = "$8.00";
	var oc = document.createAttribute("onchange");
        oc.value = "updateTotal()";
        newNode2.attributes.setNamedItem(oc);
	newNode.appendChild(newNode2);
	newNode.appendChild(document.createTextNode(" "));
	newRoot.appendChild(document.createTextNode(" "));
	return newRoot;
}
