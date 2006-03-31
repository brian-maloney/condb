<?php

require("session.inc");
require_once("condb.inc");

echo "<ajax><target>{$_GET['target']}</target>";

switch ($_GET['action']) {

case "camsrc":
	$_SESSION['cam_src'] = $_GET['data'];
	break;
case "camconf":
	echo "<data><input id=\"pic_source\" value=\"{$_SESSION['cam_src']}\"></input><br /><input type=\"button\" value=\"Cancel\" onClick=\"picShow('display')\"></input> <input type=\"button\" value=\"Save\" onClick=\"ajaxRequest('pic_content', 'camsrc', encodeURIComponent(document.getElementById('pic_source').value)); picShow('display')\"></input></data>";
	break;
case "new_obj_editor":
	echo "<data>";
	eval("\$newobj = new " . $_GET['data']);
	echo preg_replace("@<div[^>]*?>(.*)</div>$@i", '$1', str_replace("\n", '', $newobj->editor()));
	echo "</data>";
	break;
case "transaction_picker":
	echo '<data><select id="transid" style="text-align: right">';
	$translist = $GLOBALS['db']->query("SELECT id,paidby,amount FROM transactions WHERE con = {$_SESSION['conid']} ORDER BY updatetime DESC");
	while ($row = $GLOBALS['db']->fetch_row($translist)) {
		echo "<option value=\"{$row['id']}\">{$row['paidby']}&#160;&#160;&#160;&#160;&#160;&#160;&#36;{$row['amount']}</option>&#160;&#160;";
	}
	echo '</select>&#160;&#160;<input type="button" value="Link Transaction" onClick="linktransaction()"></input></data>';
}

echo "</ajax>";

?>
