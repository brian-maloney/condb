<?php

class ca extends db_object {

var $addresses;
var $stuff;

function __construct($loadid = 0) {
	$this->table = "CAs";
	parent::__construct($loadid);
	$this->addresses = array();
	$this->stuff = array();

	if(isset($GLOBALS['postobjs']['address'])) foreach($GLOBALS['postobjs']['address'] as $addrkey => $address) if($address->fields['ca'] == $this->obj_id) $this->addresses[$addrkey] =& $GLOBALS['postobjs']['address'][$addrkey];

	if ($this->in_db) {
		$addrqry = $GLOBALS['db']->query("SELECT id, description FROM addresses WHERE CA = {$this->obj_id}");
		while ($row = $GLOBALS['db']->fetch_row($addrqry)) {
			if (!isset($this->addresses[$row['id']])) $this->addresses[$row['id']] = new address($row['id']);
		}
		uasort($this->addresses, array("address", "cmp"));
	}

	foreach($_SESSION['classes'] as $classkey => $class) {
		if (isset($GLOBALS['postobjs'][$classkey])) foreach($GLOBALS['postobjs'][$classkey] as $itemkey => $item) if (($item->fields['ca'] == $this->obj_id) || $class['many']) $this->stuff[$classkey][$itemkey] =& $GLOBALS['postobjs'][$classkey][$itemkey];
		if (($class['table'] != "") && ($this->in_db)) {
			if ($class['many']) $stuffqry = $GLOBALS['db']->query("SELECT {$class['table']}.* FROM {$class['table']} JOIN many ON {$class['table']}.id = many.fromid WHERE many.fromtable = '{$class['table']}' AND many.totable = 'CAs' AND many.toid = {$this->obj_id} AND {$class['table']}.con = {$_SESSION['conid']}");
			else $stuffqry = $GLOBALS['db']->query("SELECT id FROM {$class['table']} WHERE CA = {$this->obj_id} AND con = {$_SESSION['conid']}");
			while ($row = $GLOBALS['db']->fetch_row($stuffqry)) {
				if (!isset($this->stuff[$classkey][$row['id']])) eval("\$this->stuff[\$classkey][{$row['id']}] = new {$classkey}({$row['id']});");
			}
		}
		if (sizeof($this->stuff[$classkey])) {
			reset($this->stuff[$classkey]);
			if (method_exists(current($this->stuff[$classkey]), "cmp")) uasort($this->stuff[$classkey], array($classkey, "cmp"));
			else ksort($this->stuff[$classkey]);
		}
	}
}

function editor() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_editor" class="' . get_class($this) . '_editor">';
	$html .= '<input type="hidden" name="editobj_' . $basename . '" value="true">' . "\n";
	$name =  '<select name="' . $basename . '_prefix">';
	foreach(array("", "Mr.", "Ms.", "Mrs.", "Dr.", "Rev.") as $prefitem) {
		$name = $name . "<option value=\"$prefitem\"";
		if (!strcasecmp($this->fields['prefix'], $prefitem)) $name = $name . " selected";
		$name = $name . ">$prefitem</option>\n";
	}
	$name .= "</select>\n";
	$name .= $this->textbox("first");
	$name .= $this->textbox("middle");
	$name .= $this->textbox("last");
	$name .= '<select name="' . $basename . '_suffix">';
	foreach(array("", "Jr.", "Sr.", "III", "IV", "Esq.", "Ph.D.") as $suffitem) {
		$name = $name . "<option value=\"$suffitem\"";
		if (!strcasecmp($this->fields['suffix'], $suffitem)) $name = $name . " selected";
		$name = $name . ">$suffitem</option>\n";
	}
	$name .= "</select>\n";
	$html .= $this->section("name", "Name", $name);
	$html .= $this->section("nick", "Nick/Fan Name", $this->textbox("nick"));
	$html .= $this->section("age", "Age", $this->textbox("age"));
	$gender = "<input type=\"radio\" name=\"{$basename}_gender\" class=\"gender\" value=\"M\"";
	if ($this->fields['gender'] == "M") $gender .= " checked";
	$gender .= ">Male</input><input type=\"radio\" name=\"{$basename}_gender\" class=\"gender\" value=\"F\"";
	if ($this->fields['gender'] == "F") $gender .= " checked";
	$gender .= ">Female</input>";
	$html .= $this->section("gender", "Gender", $gender);
	$rtype =  '<select name="' . $basename . '_reference">';
	$rtype = $rtype . "<option value=\"\"";
	if (!strcmp($this->fields['reference'], "")) $rtype .= " selected";
	$rtype = $rtype . "></option>\n";
	foreach($_SESSION['db_enums']['reftypes'] as $typecode => $typedetails) {
		$rtype = $rtype . "<option value=\"$typecode\"";
		if (!strcmp($this->fields['reference'], $typecode)) $rtype .= " selected";
		$rtype = $rtype . ">{$typedetails['text']}</option>\n";
	}
	$rtype .= "</select>\n";
	$html .= $this->section("reference", "Reference", $rtype);

	$atype =  '<select name="' . $basename . '_attraction">';
	$atype .= "<option value=\"\"";
	if (!strcmp($this->fields['attraction'], "")) $atype .= " selected";
	$atype = $atype . "></option>\n";
	foreach($_SESSION['db_enums']['attrtypes'] as $typecode => $typedetails) {
		$atype .= "<option value=\"$typecode\"";
		if (!strcmp($this->fields['attraction'], $typecode)) $atype .= " selected";
		$atype .= ">{$typedetails['text']}</option>\n";
	}
	$atype .= "</select>\n";
	$html .= $this->section("attraction", "Attraction", $atype);

	$html .= $this->section("comments", "Comments", $this->textarea("comments"));
	$html .= "</div>\n";
	return $html;
}

function display() {
	$basename = get_class($this) . '_' . $this->obj_id;
	$html = '<div id="' . $basename . '_display" class="' . get_class($this) . '_display">' . "\n";
	$name = "";
	foreach(array("prefix", "first", "middle", "last", "suffix") as $namepart) {
		$name .= (($this->fields[$namepart] . " ") != " ") ? $this->fields[$namepart] . " " : "";
	}
	$name = trim($name);
	$html .= $this->section("name", "Name", $name);
	$html .= $this->section("nick", "Nick/Fan Name", $this->fields["nick"]);
	$html .= $this->section("age", "Age", $this->fields["age"]);
	$html .= $this->section("gender", "Gender", $this->fields["gender"]);
	$html .= $this->section("reference", "Reference", $_SESSION['db_enums']['reftypes'][$this->fields['reference']]['text']);
	$html .= $this->section("attraction", "Attraction", $_SESSION['db_enums']['attrtypes'][$this->fields['attraction']]['text']);
	$html .= $this->section("comments", "Comments", $this->fields["comments"]);
	$html .= "</div>\n";
	return $html;
}

function save() {
	parent::save();
	$newarr = array();
	while ($addr = array_pop($this->addresses)) {
		$addr->fields['ca'] = $this->obj_id;
		$addr->save();
		$newarr[$addr->obj_id] = $addr;
	}
	$this->addresses = $newarr;
	uasort($this->addresses, array("address", "cmp"));
	foreach($this->stuff as $classname => $class) {
		$newarr = array();
		while ($item = array_pop($class)) {
			if (!$_SESSION['classes'][$classname]['many']) $item->fields['ca'] = $this->obj_id;
			$item->save();
			if ($_SESSION['classes'][$classname]['many']) {
				$GLOBALS['db']->query("DELETE FROM many WHERE fromtable = '{$_SESSION['classes'][$classname]['table']}' AND fromid = {$item->obj_id} AND totable = 'CAs' AND toid = $this->obj_id");
				$GLOBALS['db']->query("INSERT INTO many (fromtable, fromid, totable, toid) VALUES ('{$_SESSION['classes'][$classname]['table']}', {$item->obj_id}, 'CAs', $this->obj_id)");
			}
			$newarr[$item->obj_id] = $item;
		}
		$this->stuff[$classname] = $newarr;
		if (sizeof($this->stuff[$classname])) {
			reset($this->stuff[$classname]);
			if (method_exists(current($this->stuff[$classname]), "cmp")) uasort($this->stuff[$classname], array($classname, "cmp"));
			else ksort($this->stuff[$classname]);
		}
	}
}

}

?>
