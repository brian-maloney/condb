<?php

class badge extends db_object {

function __construct($loadid = 0) {
	$this->table = "badges";
	parent::__construct($loadid);
	if (substr($this->obj_id, 0, 2) == "id") {
		$this->fields['badgeno'] = "auto";
		$this->fields['con'] = $_SESSION['conid'];
	}
}

function cmp($a, $b) {
	if ($a->fields['badgeno'] == $b->fields['badgeno']) return 0;
	return (intval($a->fields['badgeno']) > intval($b->fields['badgeno'])) ? 1 : -1;
}

function editor() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_editor" class="' . get_class($this) . '_editor">';
	$html .= '<input type="hidden" name="editobj_' . $basename . '" value="true">' . "\n";
	$html .= "<input type=\"hidden\" name=\"{$basename}_ca\" value=\"{$this->fields['ca']}\">\n";
	$html .= $this->section("badgeno", "Badge Number", $this->textbox("badgeno"));
	$btype =  '<select name="' . $basename . '_type" onchange="setprice(' . "'$this->obj_id'" . ')">';
	$btype = $btype . "<option value=\"\"";
	if (!strcmp($this->fields['type'], "")) $btype .= " selected";
	$btype = $btype . "></option>\n";
	foreach($_SESSION['db_enums']['badgetypes'] as $typecode => $typedetails) {
		if ($typedetails['con'] == $_SESSION['conid']) {
			$btype = $btype . "<option value=\"$typecode\"";
			if (!strcmp($this->fields['type'], $typecode)) $btype .= " selected";
			$btype = $btype . ">{$typedetails['name']}</option>\n";
		}
	}
	$btype .= "</select>\n";
	$html .= $this->section("type", "Badge Type", $btype);
	$bstatus =  '<select name="' . $basename . '_status">';
	$bstatus = $bstatus . "<option value=\"\"";
	if (!strcmp($this->fields['status'], "")) $bstatus .= " selected";
	$bstatus .= "></option>\n";
	foreach($_SESSION['db_enums']['badgestatus'] as $statuscode => $statusdetails) {
		$bstatus .= "<option value=\"$statuscode\"";
		if (!strcmp($this->fields['status'], $statuscode)) $bstatus .= " selected";
		$bstatus .= ">{$statusdetails['name']}</option>\n";
	}
	$bstatus .= "</select>\n";
	$html .= $this->section("status", "Badge Status", $bstatus);
	$html .= $this->section("price", "Price", "<input type=\"text\" class=\"price\" name=\"${basename}_price\" value=\"\${$this->fields['price']}\" onchange=\"updateTotal()\">");
	$html .= "</div>\n";
	return $html;
}

function display() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_display" class="' . get_class($this) . '_display">' . "\n";
	$html .= $this->section("badgeno", "Badge Number", $this->fields['badgeno']);
	$html .= $this->section("type", "Badge Type", $_SESSION['db_enums']['badgetypes'][$this->fields['type']]['name']);
	$html .= $this->section("status", "Badge Status", $_SESSION['db_enums']['badgestatus'][$this->fields['status']]['name']);
	$html .= $this->section("price", "Price", "$" . $this->fields['price']);	
	$html .= "</div>\n";
	return $html;
}

function save() {
	if ($this->fields['badgeno'] == "auto") {
		$row = $GLOBALS['db']->fetch_row($GLOBALS['db']->query("SELECT MAX(badgeno) FROM badges WHERE con = {$_SESSION['conid']}"), MYSQL_NUM);
		if (!is_numeric($row[0])) $this->fields['badgeno'] = 1;
		else $this->fields['badgeno'] = $row[0] + 1;
	}
	parent::save();
}

function readvals() {
	parent::readvals();
	$this->fields['price'] = ereg_replace("[^0-9.]", "", $this->fields['price']);
}

}
?>
