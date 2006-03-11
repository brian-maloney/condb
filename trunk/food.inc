<?php

class food extends db_object {

function __construct($loadid = 0) {
	$this->table = "food";
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
	$html .= "Food: ";
	$html .= $this->section("price", "Price", "<input type=\"text\" class=\"price\" name=\"${basename}_price\" value=\"\${$this->fields['price']}\" onchange=\"updateTotal()\">");
	$html .= "</div>\n";
	return $html;
}

function display() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_display" class="' . get_class($this) . '_display">' . "\n";
	$html .= "Food: ";
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
