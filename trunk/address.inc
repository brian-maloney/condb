<?php

class address extends db_object {

function __construct($loadid = 0) {
	$this->table = "addresses";
	parent::__construct($loadid);
}

function cmp($a, $b) {
	if ($a->fields['mailing'] == $b->fields['mailing']) return 0;
	return ($a->fields['mailing']) ? -1 : 1;
}

function load() {
	parent::load();
	foreach(array("validfrom", "validto", "lastcheck") as $field) {
		if ($this->fields[$field] != "") {
			$this->fields[$field] = strftime("%m/%d/%y" , strtotime($this->fields[$field]));
		}
	}
}

function editor() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_editor" class="' . get_class($this) . '_editor">';
	$html .= '<input type="hidden" name="editobj_' . $basename . '" value="true">' . "\n";
	$html .= "<input type=\"hidden\" name=\"{$basename}_ca\" value=\"{$this->fields['ca']}\">\n";
	$html .= $this->section("description", "Description", $this->textbox("description"));
	$html .= $this->section("straddr", "Street Address", $this->textbox("addr1") . $this->textbox("addr2") . $this->textbox("addr3"));
	$html .= $this->section("city", "City", $this->textbox("city"));
	$html .= $this->section("state", "State", $this->textbox("state"));
	$html .= $this->section("zip", "Postal Code", $this->textbox("zip"));
	$html .= $this->section("country", "Country", $this->textbox("country"));
	$html .= $this->section("validfrom", "Valid From", $this->textbox("validfrom"));
	$html .= $this->section("validto", "Valid To", $this->textbox("validto"));
	$html .= $this->section("lastcheck", "Last Verified", $this->textbox("lastcheck"));
	$html .= $this->section("valid", "Valid", $this->checkbox("valid"));
	$html .= $this->section("mailing", "Mailing Address", "<input type=\"checkbox\" name=\"{$basename}_mailing\" onclick=\"mailAddr('{$basename}_mailing')\"" . (intval($this->fields['mailing']) ? " checked" : "") . '>');
	$html .= "</div>\n";
	return $html;
}

function display() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_display" class="' . get_class($this) . '_display">' . "\n";
	$html .= $this->section("description", "Description", $this->fields['description']);
	$html .= $this->section("straddr", "Street Address", "{$this->fields['addr1']}<br>\n{$this->fields['addr2']}<br>\n{$this->fields['addr3']}");
	$html .= $this->section("city", "City", $this->fields['city']);
	$html .= $this->section("state", "State", $this->fields['state']);
	$html .= $this->section("zip", "Postal Code", $this->fields['zip']);
	$html .= $this->section("country", "Country", $this->fields['country']);
	$html .= $this->section("validfrom", "Valid From", $this->fields['validfrom']);
	$html .= $this->section("validto", "Valid To", $this->fields['validto']);
	$html .= $this->section("lastcheck", "Last Verified", $this->fields['lastcheck']);
	$html .= $this->section("valid", "Valid", $this->fields['valid']);
	$html .= $this->section("mailing", "Mailing Address", $this->fields['mailing']);
	$html .= "</div>\n";
	return $html;
}

function save() {
	foreach(array("validfrom", "validto", "lastcheck") as $field) if ($this->fields[$field] != "") $this->fields[$field] = strftime("%Y-%m-%d" , strtotime($this->fields[$field]));
	parent::save();
}

function readvals() {
	parent::readvals();
	$this->fields['valid'] = ($this->fields['valid'] == "on") ? 1 : 0;
	$this->fields['mailing'] = ($this->fields['mailing'] == "on") ? 1 : 0;
	foreach(array("validfrom", "validto", "lastcheck") as $field) {
		if ($this->fields[$field] != "") $this->fields[$field] = strftime("%m/%d/%y" , strtotime($this->fields[$field]));
	}
}

}
?>
