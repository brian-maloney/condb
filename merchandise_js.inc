function newmerchandise() {
	var myID = newID();
	var newRoot = newDiv("merchandise_" + myID + "_editor", "merchandise_editor");
	newRoot.appendChild(newInput("", "", "hidden", "editobj_merchandise_" + myID, "true"));
	newRoot.appendChild(document.createTextNode(" "));
	newRoot.appendChild(newInput("", "", "hidden", "merchandise_" + myID + "_ca", currentCA));
	newRoot.appendChild(document.createTextNode(" "));
	var newNode = newRoot.appendChild(newSection("type", "Merchandise Type"));
	var newNode2 = newNode.appendChild(newSelect("merchandise_" + myID + "_type"));
	newNode2.setAttribute("onchange", "setmerchandiseprice('" + myID + "')");
	newNode2.appendChild(newOption("", ""));
	newNode2.firstChild.selected = true;
	newNode2.firstChild.defaultSelected = true;
<?php
foreach($_SESSION['db_enums']['merchtypes'] as $typecode => $typedetails) {
	if ($typedetails['con'] == $_SESSION['conid']) {
		echo '	newNode2.appendChild(newOption("', $typedetails['name'], '", "', $typecode, '"));', "\n";
	}
}
?>
	newNode.appendChild(document.createTextNode(" "));

	newNode = newRoot.appendChild(newSection("qty", "Quantity"));
	newNode2 = newNode.appendChild(newSelect("merchandise_" + myID + "_qty"));
	newNode2.setAttribute("onchange", "setmerchandiseprice('" + myID + "')");
	//newNode2.appendChild(newOption("", ""));
<?php
for($x=1;$x<51;$x++) {
	echo '	newNode2.appendChild(newOption("', $x, '", "', $x, '"));', "\n";
}
?>
	newNode2.firstChild.selected = true;
	newNode2.firstChild.defaultSelected = true;
	newNode.appendChild(document.createTextNode(" "));


/*
	newNode = newRoot.appendChild(newSection("qty", "Quantity"));
	newNode2 = newInput("", "qty", "text", "merchandise_" + myID + "_qty", "1");
	var oc = document.createAttribute("onchange");
	oc.value = "setmerchandiseprice(myID); updateTotal()";
	newNode2.attributes.setNamedItem(oc);
	newNode.appendChild(newNode2);
	newNode.appendChild(document.createTextNode(" "));
*/

	newNode = newRoot.appendChild(newSection("price", "Price"));
	newNode2 = newInput("", "price", "text", "merchandise_" + myID + "_price", "");
	var oc = document.createAttribute("onchange");
	oc.value = "updateTotal()";
	newNode2.attributes.setNamedItem(oc);
	newNode.appendChild(newNode2);
	newNode.appendChild(document.createTextNode(" "));
	newRoot.appendChild(document.createTextNode(" "));
	return newRoot;
}

function setmerchandiseprice(merchid) {
switch (document.getElementsByName("merchandise_" + merchid + "_type").item(0).value) {
<?php
foreach($_SESSION['db_enums']['merchtypes'] as $typecode => $typedetails) {
	if ($typedetails['con'] == $_SESSION['conid']) {
		echo '	', "case \"{$typecode}\":\n";
		echo '	', "subtotal = ";
		echo '		document.getElementsByName("merchandise_" + merchid + "_price").item(0).value = "$" + ', "String(Number({$typedetails['price']} * document.getElementsByName(\"merchandise_\" + merchid + \"_qty\").item(0).value).toFixed(2));\n";
		echo '		break;', "\n";
	}
}
?>
	default:
		document.getElementsByName("merchandise_" + merchid + "_price").item(0).value =  "";
	}
	updateTotal();
}
