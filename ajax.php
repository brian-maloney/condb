<?php

require("session.inc");

echo "<ajax><target>{$_GET['target']}</target>";

switch ($_GET['action']) {

case "camsrc":
	$_SESSION['cam_src'] = $_GET['data'];
	break;
case "camconf":
	echo "<data><input id=\"pic_source\" value=\"{$_SESSION['cam_src']}\"></input><br /><input type=\"button\" value=\"Cancel\" onClick=\"picShow('display')\"></input> <input type=\"button\" value=\"Save\" onClick=\"ajaxRequest('pic_content', 'camsrc', encodeURIComponent(document.getElementById('pic_source').value)); picShow('display')\"></input></data>";
	break;
}

echo "</ajax>";

?>
