<?php
if ($_SERVER['REQUEST_METHOD'] == "POST" && $_POST['ca_id']) header("Location: caedit.php?ca_id=" . $_POST['ca_id']);

require_once("session.inc");
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
   "http://www.w3.org/TR/html4/strict.dtd">
<html>

<head>
<meta HTTP-EQUIV='Content-Type' CONTENT='text/html; charset=iso-8859-1'>
<meta HTTP-EQUIV='Content-Style-Type' CONTENT='text/css'>
<meta HTTP-EQUIV='Content-Script-Type' CONTENT='text/javascript'>
<title>Convention Database Search</title>

<?php
require_once("condb.inc");

if ($_SERVER['REQUEST_METHOD'] == "POST" && $_POST['ca_name']) {
	$_SESSION['namesearch'] = mysql_escape_string((get_magic_quotes_gpc()) ? stripslashes($_POST['ca_name']) : $_POST['ca_name']);
}

elseif ($_SERVER['REQUEST_METHOD'] == "POST" && $_POST['comments']) {
	$caqry = $GLOBALS['db']->query("SELECT id, first, middle, last FROM CAs WHERE comments LIKE '%{$_POST['comments']}%' ORDER BY last");
}

elseif ($_SERVER['REQUEST_METHOD'] == "POST" && $_POST['badgeno'] && is_numeric($_POST['badgeno'])) {
	unset($_SESSION['namesearch']);
	$badgeqry = $GLOBALS['db']->query("SELECT ca FROM badges WHERE badgeno = {$_POST['badgeno']} AND con = {$_SESSION['conid']}");
	if ($GLOBALS['db']->row_count($badgeqry)) {
		$row = $GLOBALS['db']->fetch_row($badgeqry);
		$caqry = $GLOBALS['db']->query("SELECT id, first, middle, last FROM CAs WHERE id = {$row['ca']}");
	}
}

if (isset($_SESSION['namesearch'])) {
	$caqry = $GLOBALS['db']->query("SELECT id, first, middle, last FROM CAs WHERE first LIKE '%{$_SESSION['namesearch']}%' OR last LIKE '%{$_SESSION['namesearch']}%' ORDER BY last");
}
?>

<style TYPE='text/css'>
<?php
readfile("base.css");
?>
</style>
</head>

<body>
<h1>Search</h1>

<?php
if (isset($badgeqry) && !($GLOBALS['db']->row_count($badgeqry))) {
	echo "<p>No Badge found...</p>";
}
if (isset($caqry)) {
	if ($GLOBALS['db']->row_count($caqry)) {
		echo "<ul>\n";
		while ($row = $GLOBALS['db']->fetch_row($caqry)) echo "<li><a href=\"caedit.php?ca_id=$row[0]\">$row[1] $row[2] $row[3]</a></li>\n";
		echo "</ul>\n";
	}
	else echo "<p>No CAs found...</p>";
}
?>

<form method="post" action="search.php">
<table>
  <tr><td>CA ID Number:</td><td><input type="text" name="ca_id"></td></tr>
  <tr><td>Name:</td><td><input type="text" name="ca_name"></td></tr>
  <tr><td>Comments:</td><td><input type="text" name="comments"></td></tr>
  <tr><td>Badge Number:</td><td><input type="text" name="badgeno"></td></tr>
</table>
<button type="submit" name="search" value="search">Search</button>
</form>

<?php require("menu.inc"); ?>

</body>

</html>