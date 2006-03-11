function newbadge() {
	var myID = newID();
	var newRoot = newDiv("badge_" + myID + "_editor", "badge_editor");
	newRoot.appendChild(newInput("", "", "hidden", "editobj_badge_" + myID, "true"));
	newRoot.appendChild(document.createTextNode(" "));
	newRoot.appendChild(newInput("", "", "hidden", "badge_" + myID + "_ca", currentCA));
	newRoot.appendChild(document.createTextNode(" "));
	var newNode = newRoot.appendChild(newSection("badgeno", "Badge Number"));
	newNode.appendChild(newInput("", "badgeno", "text", "badge_" + myID + "_badgeno", "auto"));
	newNode.appendChild(document.createTextNode(" "));
	newNode = newRoot.appendChild(newSection("type", "Badge Type"));
	newNode2 = newNode.appendChild(newSelect("badge_" + myID + "_type"));
	newNode2.setAttribute("onchange", "setprice('" + myID + "')");
	newNode2.appendChild(newOption("", ""));
	newNode2.firstChild.selected = true;
	newNode2.firstChild.defaultSelected = true;
<?php	
foreach($_SESSION['db_enums']['badgetypes'] as $typecode => $typedetails) {
	if ($typedetails['con'] == $_SESSION['conid']) {
		echo '	newNode2.appendChild(newOption("', $typedetails['name'], '", "', $typecode, '"));', "\n";
	}
}
?>
	newNode.appendChild(document.createTextNode(" "));
	newNode = newRoot.appendChild(newSection("status", "Badge Status"));
	newNode2 = newNode.appendChild(newSelect("badge_" + myID + "_status"));
	newNode2.appendChild(newOption("", ""));
	newNode2.firstChild.selected = true;
	newNode2.firstChild.defaultSelected = true;
<?php
foreach($_SESSION['db_enums']['badgestatus'] as $statuscode => $statusdetails) {
	echo '	newNode2.appendChild(newOption("', $statusdetails['name'], '", "', $statuscode, '"));', "\n";
}
?>
	newNode.appendChild(document.createTextNode(" "));
	newNode = newRoot.appendChild(newSection("price", "Price"));
	newNode2 = newInput("", "price", "text", "badge_" + myID + "_price", "");
	var oc = document.createAttribute("onchange");
	oc.value = "updateTotal()";
	newNode2.attributes.setNamedItem(oc);
	newNode.appendChild(newNode2);
	newNode.appendChild(document.createTextNode(" "));
	newRoot.appendChild(document.createTextNode(" "));
	return newRoot;
}

function setprice(badgeid) {
	switch (document.getElementsByName("badge_" + badgeid + "_type").item(0).value) {
<?php
foreach($_SESSION['db_enums']['badgetypes'] as $typecode => $typedetails) {
	if ($typedetails['con'] == $_SESSION['conid']) {
		echo '	', "case \"{$typecode}\":\n";
		echo '		document.getElementsByName("badge_" + badgeid + "_price").item(0).value = "$" + ', "\"{$typedetails['price']}\";\n";
		echo '		break;', "\n";
	}
}
?>
	default:
		document.getElementsByName("badge_" + badgeid + "_price").item(0).value =  "";
	}
	updateTotal();
}