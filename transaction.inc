<?php

class transaction extends db_object {

function __construct($loadid = 0) {
	$this->table = "transactions";
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

	$transtype =  '<select name="' . $basename . '_paytype">';
	foreach($_SESSION['db_enums']['paytypes'] as $typecode => $typedetails) {
		$transtype = $transtype . "<option value=\"$typecode\"";
		if (!strcmp($this->fields['paytype'], $typecode)) $transtype .= " selected";
		$transtype = $transtype . ">{$typedetails['name']}</option>\n";
	}
	$transtype .= "</select>\n";
	$html .= $this->section("type", "Transaction Type", $transtype);

	$html .= $this->section("paidby", "Paid By", $this->textbox('paidby'));
	$html .= $this->section("paidto", "Paid To", $this->textbox('paidto'));
	$html .= "<span style=\"display: block; padding-top: 0.5em\">";
	$html .= $this->section("details", "Details", $this->textbox('details'));
	$html .= "&nbsp;&nbsp;&nbsp;";
	$html .= $this->section("notes", "Notes", $this->textbox('notes'));
	$html .= "</span>";

	$html .= $this->section("amount", "Amount", "<input type=\"text\" class=\"amount\" name=\"${basename}_amount\" value=\"\${$this->fields['amount']}\">");
	$html .= "</div>\n";
	return $html;
}

function readvals() {
	parent::readvals();
	$this->fields['amount'] = ereg_replace("[^0-9.]", "", $this->fields['amount']);
}

}
?>
