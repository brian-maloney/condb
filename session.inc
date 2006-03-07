<?php
// Initialize Session

session_name("condb");
session_start();

if ($_SERVER['REQUEST_METHOD'] == "POST" && isset($_POST['newcon'])) {
	session_unset();
	session_destroy();
	session_name("condb");
	session_start();
	$_SESSION['conid'] = intval($_POST['newcon']);
	$_SERVER['REQUEST_METHOD'] = "GET";
}
?>
