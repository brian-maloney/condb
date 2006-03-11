function newca() {
	var myID = newID();
	var newRoot = newDiv("ca_" + myID + "_editor", "ca_editor");
	newNode = newRoot.appendChild(newInput("", "", "hidden", "editobj_ca_" + myID, "true"));
	newRoot.appendChild(document.createTextNode(" "));
	var newNode = newRoot.appendChild(newSection("name", "Name"));
	newNode2 = newNode.appendChild(newSelect("ca_" + myID + "_prefix"));
	newNode2.appendChild(newOption("", ""));
	newNode2.firstChild.selected = true;
	newNode2.firstChild.defaultSelected = true;
	newNode2.appendChild(newOption("Mr.", "Mr."));
	newNode2.appendChild(newOption("Ms.", "Ms."));
	newNode2.appendChild(newOption("Mrs.", "Mrs."));
	newNode2.appendChild(newOption("Dr.", "Dr."));
	newNode2.appendChild(newOption("Rev.", "Rev."));
	newNode.appendChild(document.createTextNode(" "));
	newNode.appendChild(newInput("", "first", "text", "ca_" + myID + "_first", ""));
	newNode.appendChild(document.createTextNode(" "));
	newNode.appendChild(newInput("", "middle", "text", "ca_" + myID + "_middle", ""));
	newNode.appendChild(document.createTextNode(" "));
	newNode.appendChild(newInput("", "last", "text", "ca_" + myID + "_last", ""));
	newNode.appendChild(document.createTextNode(" "));
	newNode2 = newNode.appendChild(newSelect("ca_" + myID + "_suffix"));
	newNode2.appendChild(newOption("", ""));
	newNode2.firstChild.selected = true;
	newNode2.firstChild.defaultSelected = true;
	newNode2.appendChild(newOption("Jr.", "Jr."));
	newNode2.appendChild(newOption("Sr.", "Sr."));
	newNode2.appendChild(newOption("III", "III"));
	newNode2.appendChild(newOption("IV", "IV"));
	newNode2.appendChild(newOption("Ph.D.", "Ph.D."));
	newNode2.appendChild(newOption("Esq.", "Esq."));
	newNode.appendChild(document.createTextNode(" "));
	newNode = newRoot.appendChild(newSection("nick", "Nick/Fan Name"));
	newNode.appendChild(newInput("", "nick", "text", "ca_" + myID + "_nick", ""));
	newNode.appendChild(document.createTextNode(" "));
	newNode = newRoot.appendChild(newSection("age", "Age"));
	newNode.appendChild(newInput("", "age", "text", "ca_" + myID + "_age", ""));
	newNode.appendChild(document.createTextNode(" "));
	newNode = newRoot.appendChild(newSection("gender", "Gender"));
	newNode.appendChild(newInput("", "nick", "radio", "ca_" + myID + "_gender", "M"));
	newNode.appendChild(document.createTextNode("Male"));
	newNode.appendChild(newInput("", "nick", "radio", "ca_" + myID + "_gender", "F"));
	newNode.appendChild(document.createTextNode("Female"));

	newNode = newRoot.appendChild(newSection("reference", "Reference"));
	newNode2 = newNode.appendChild(newSelect("badge_" + myID + "_reference"));
	newNode2.appendChild(newOption("", ""));
	newNode2.firstChild.selected = true;
	newNode2.firstChild.defaultSelected = true;
<?php	
foreach($_SESSION['db_enums']['reftypes'] as $typecode => $typedetails) {
	echo '	newNode2.appendChild(newOption("', $typedetails['text'], '", "', $typecode, '"));', "\n";
}
?>
	newNode.appendChild(document.createTextNode(" "));

	newNode = newRoot.appendChild(newSection("attraction", "Attraction"));
	newNode2 = newNode.appendChild(newSelect("badge_" + myID + "_attraction"));
	newNode2.appendChild(newOption("", ""));
	newNode2.firstChild.selected = true;
	newNode2.firstChild.defaultSelected = true;
<?php	
foreach($_SESSION['db_enums']['attrtypes'] as $typecode => $typedetails) {
	echo '	newNode2.appendChild(newOption("', $typedetails['text'], '", "', $typecode, '"));', "\n";
}
?>
	newNode.appendChild(document.createTextNode(" "));

	newNode = newRoot.appendChild(newSection("comments", "Comments"));
	newNode2 = newNode.appendChild(document.createElement("textarea"));
	newNode2.className = "comments";
	newNode2.name = "ca_" + myID + "_comments";
	newNode.appendChild(document.createTextNode(" "));
	newRoot.appendChild(document.createTextNode(" "));
	return newRoot;
}