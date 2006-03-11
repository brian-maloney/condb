<?php

class merchandise extends db_object {

function __construct($loadid = 0) {
	$this->table = "merchandise";
	parent::__construct($loadid);
	if (substr($this->obj_id, 0, 2) == "id") {
		$this->fields['con'] = $_SESSION['conid'];
	}
}

function editor() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_editor" class="' . get_class($this) . '_editor">';
	$html .= '<input type="hidden" name="editobj_' . $basename . '" value="true">' . "\n";
	$html .= "<input type=\"hidden\" name=\"{$basename}_ca\" value=\"{$this->fields['ca']}\">\n";
	$stype =  '<select name="' . $basename . '_type" onchange="setmerchandiseprice(' . "'$this->obj_id'" . ')">';
	$stype .= "<option value=\"\"";
	if (!strcmp($this->fields['type'], "")) $stype .= " selected";
	$stype = $stype . "></option>\n";
	foreach($_SESSION['db_enums']['merchtypes'] as $typecode => $typedetails) {
		if ($typedetails['con'] == $_SESSION['conid']) {
			$stype = $stype . "<option value=\"$typecode\"";
			if (!strcmp($this->fields['type'], $typecode)) $stype .= " selected";
			$stype = $stype . ">{$typedetails['name']}</option>\n";
		}
	}
	$stype .= "</select>\n";
	$html .= $this->section("type", "Merchandise Type", $stype);
//    $html .= $this->section("qty", "Quantity", "<input type=\"text\" name=\"${basename}_qty\" value=\"{$this->fields['qty']}\" onchange=\"setmerchandiseprice({$this->obj_id}); updateTotal()\">");

	$qtycode =  '<select name="' . $basename . '_qty" onchange="setmerchandiseprice(' . "'$this->obj_id'" . ')">';
	for($x=1;$x<51;$x++) {
			$qtycode = $qtycode . "<option value=\"$x\"";
			if (!strcmp($this->fields['qty'], $x)) $qtycode .= " selected";
			$qtycode = $qtycode . ">{$x}</option>\n";
	}
	$qtycode .= "</select>\n";

	$html .= $this->section("qty", "Quantity", $qtycode);

	$html .= $this->section("price", "Price", "<input type=\"text\" class=\"price\" name=\"${basename}_price\" value=\"\${$this->fields['price']}\" onchange=\"updateTotal()\">");
	$html .= "</div>\n";
	return $html;
}

function display() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_display" class="' . get_class($this) . '_display">' . "\n";
	$html .= $this->section("type", "Merchandise Type", $_SESSION['db_enums']['merchtypes'][$this->fields['type']]['name']);
	$html .= $this->section("qty", "Quantity", $this->fields['qty']);
	$html .= $this->section("price", "Price", "$" . $this->fields['price']);	
	$html .= "</div>\n";
	return $html;
}

function save() {
	parent::save();
}

function readvals() {
	parent::readvals();
	$this->fields['price'] = ereg_replace("[^0-9.]", "", $this->fields['price']);
}

}
?>
