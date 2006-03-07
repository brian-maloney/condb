<?php

// "Pure Virtual" Class - Do not create an object of this type!

abstract class db_object {

var $fields;
var $original;
var $table;
var $in_db;
var $obj_id;

function __construct($loadid = 0) {
	if (substr($loadid, 0, 2) == "id") {
		$this->obj_id = $loadid;
	}
	elseif (is_numeric($loadid) && $loadid > 0) {
		$this->obj_id = $loadid;
		$this->load();
	}
	else {
		$this->in_db = false;
		$this->obj_id = "id" . substr(md5(microtime().posix_getpid()), 10, 6);
		if (!isset($_SESSION['fieldlists'][get_class($this)])) $_SESSION['fieldlists'][get_class($this)] = $GLOBALS['db']->get_fields($this->table);
		foreach($_SESSION['fieldlists'][get_class($this)] as $fieldname) $this->fields[$fieldname] = "";
	}
}

function readvals() {
	foreach($_POST as $postvar => $value) {
		$varname = explode("_", $postvar);
		if (next($varname) == $this->obj_id) {
			$varname = explode("_", $postvar);
			$this->fields[end($varname)] = html_entity_decode(((get_magic_quotes_gpc()) ? stripslashes($value) : $value));
		}
	}
}

function dirty() {
	return ($this->original != $this->fields);
}

function save() {
	if (!function_exists("array_intersect_assoc")) {
		function array_intersect_assoc($array1, $array2) {
			$retarr = array();
			foreach ($array1 as $key => $value) {
				if ($value == $array2[$key]) $retarr[$key] = $value;
			}
			return $retarr;
		}
	}

	$savefields = array();
	foreach($this->fields as $key => $value) {
		if (!is_numeric($value)) $savefields[$key] = "'" . mysql_escape_string((get_magic_quotes_gpc()) ? stripslashes($value) : $value) . "'";
		else $savefields[$key] = $value;
		if ($value === "") $savefields[$key] = "NULL";
	}
	if ($this->in_db) {
		$changed_fields = array_diff(array_keys($this->original), array_keys(array_intersect_assoc($this->fields, $this->original)));
		if (count($changed_fields)) {
			$sqlstr = "UPDATE {$this->table} SET "; 
			foreach($changed_fields as $field) $sqlstr .= "$field={$savefields[$field]}, ";
			$sqlstr = substr($sqlstr, 0, -2);
			$sqlstr .= " WHERE id={$this->fields['id']}";
		}
	}
	else {
		$sqlstr = "INSERT INTO {$this->table} (";
		foreach($savefields as $fieldname => $fieldvalue) $sqlstr.= "$fieldname, ";
		$sqlstr = substr($sqlstr, 0, -2) . ") VALUES (";
		foreach($savefields as $fieldname => $fieldvalue) $sqlstr.= "$fieldvalue, ";
		$sqlstr = substr($sqlstr, 0, -2) . ")";
	}
	if (isset($sqlstr)) $query_id = $GLOBALS['db']->query($sqlstr);
	if (isset($changed_fields)) unset($changed_fields);
	else $this->obj_id = $GLOBALS['db']->new_id($query_id);
	$this->load();
}

function load() {
	$query_id = $GLOBALS['db']->query("SELECT * FROM $this->table WHERE id = {$this->obj_id}");
	if ($GLOBALS['db']->row_count($query_id) == 1) {
		$this->in_db = true;
		$this->original = $GLOBALS['db']->fetch_row($query_id, MYSQL_ASSOC);
		$this->fields = $this->original;
	}
	else {
		$this->in_db = false;
		$this->obj_id = "id" . substr(md5(microtime().posix_getpid()), 10, 6);
		if (!isset($_SESSION['fieldlists'][get_class($this)])) $_SESSION['fieldlists'][get_class($this)] = $GLOBALS['db']->get_fields($this->table);
		foreach($_SESSION['fieldlists'][get_class($this)] as $fieldname) $this->fields[$fieldname] = "";
	}
}

function section($name, $label, $code) {
	$sec = "<span class=\"$name\"><span class=\"label\">$label</span>$code</span>";
	return $sec;
}

function editor() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_editor" class="' . get_class($this) . '_editor">';
	$html .= '<input type="hidden" name="editobj_' . $basename . '" value="true">' . "\n";
	foreach($this->fields as $fieldname => $fieldval) {
		if ($fieldname != "id") $html .= $this->section($fieldname, ucwords(strtolower($fieldname)), $this->textbox($fieldname)) . "\n";
	}
	$html .= "</div>\n";
	return $html;
}

function display() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_display" class="' . get_class($this) . '_display">' . "\n";
	foreach($this->fields as $fieldname => $fieldval) {
		if ($fieldname != "id") $html .= $this->section($fieldname, ucwords(strtolower($fieldname)), $fieldval) . "\n";
	}
	$html .= "</div>\n";
	return $html;
}

function display_hidden() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html .= '<input type="hidden" name="editobj_' . $basename . '" value="true">' . "\n";
	foreach($this->fields as $fieldname => $fieldval) {
		if ($fieldname != "id") $html .= $this->hidden($fieldname);
	}
	return $html;
}

function textbox($field, $size = NULL) {
	$basename = get_class($this) . '_' . $this->obj_id;
	$sizefield = is_null($size) ? "" : " size=\"$size\"";
	return "<input type=\"text\"$sizefield class=\"$field\" name=\"${basename}_$field\" value=\"" . htmlspecialchars($this->fields[$field]) . "\">\n";
}

function hidden($field) {
	$basename = get_class($this) . '_' . $this->obj_id;
	return "<input type=\"hidden\" name=\"${basename}_$field\" value=\"" . htmlspecialchars($this->fields[$field]) . "\">\n";
}

function checkbox($field) {
	$basename = get_class($this) . '_' . $this->obj_id;
	$curval = intval($this->fields[$field]) ? "checked" : "";
	return "<input type=\"checkbox\" class=\"$field\" name=\"${basename}_$field\" $curval>\n";
}

function textarea($field) {
	$basename = get_class($this) . '_' . $this->obj_id;
	return "<textarea class=\"$field\" name=\"${basename}_$field\">{$this->fields[$field]}</textarea>\n";
}

}
?>
