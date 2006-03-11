<?php

// Replace this with a picture object someday!!!

if ($_GET['mode'] != "debug") error_reporting(0);
require("session.inc");
require("db.inc");

if ($_GET['mode'] != "debug") header("Content-type: image/jpeg");

switch ($_GET['mode']) {
case "debug":
	echo "Fetching picture from: {$_SESSION['cam_src']}<br>\n";
case "capture":
	if (isset( $_SESSION['cam_src'])) if ($_SESSION['cam_src'] != "") {
		if (!isset($_SESSION['ca_pic'])) $_SESSION['ca_pic'] = array();
		$_SESSION['ca_pic']['data'] = "";
		$fp = fopen($_SESSION['cam_src'], "rb");
		if ($fp) {
			$starttime = time();
			while (!feof($fp) && (time() < ($starttime + 5))) $_SESSION['ca_pic']['data'] .= fread($fp,8192);
			fclose($fp);
		}
		$_SESSION['ca_pic']['dirty'] = true;
	}
	break;
case "reset":
	unset($_SESSION['ca_pic']);
	break;
}

if (!isset($_SESSION['ca_pic'])) {

	$_SESSION['ca_pic'] = array();
	$_SESSION['ca_pic']['dirty'] = false;

	$db = new dbconn;

	$return = $db->query("SELECT picture FROM pictures WHERE id=" . $_SESSION['ca_id']);

	if ($db->row_count($return) > 0) {
		$_SESSION['ca_pic']['in_db'] = true;
		$arr = $db->fetch_row($return);
		$_SESSION['ca_pic']['data'] = $arr[0];
	}
	else {
		$_SESSION['ca_pic']['in_db'] = false;
		$fp = fopen("unknown.jpg", "rb");
		$_SESSION['ca_pic']['data'] = fread($fp,906240);
		fclose($fp);
	}
}
echo $_SESSION['ca_pic']['data'];
?>
