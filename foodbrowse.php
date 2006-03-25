<?php
require_once("session.inc");
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
   "http://www.w3.org/TR/html4/strict.dtd">
<html>

<head>
<meta HTTP-EQUIV='Content-Type' CONTENT='text/html; charset=iso-8859-1'>
<meta HTTP-EQUIV='Content-Style-Type' CONTENT='text/css'>
<meta HTTP-EQUIV='Content-Script-Type' CONTENT='text/javascript'>
<title>Food Browser</title>

<?php
require_once("condb.inc");
?>
<style TYPE='text/css'>
<?php
readfile("base.css");
?>
table td {
padding-top: 0.1em;
padding-bottom: 0.1em;
border-top: thin solid black;
}
th:first-child {
text-align: left;
}
th {
text-align: right;
padding-right: 1em;
}
tr td:first-child {
text-align: left;
}
tr td {
text-align: right;
padding-right: 1em;
}
table {
	border-collapse: collapse;
	border-spacing: 0;
	float: left;
}
</style>
</head>

<body>
<h1>Food Browser</h1>
<?php
$foodqry = $GLOBALS['db']->query("SELECT CAs.id, CAs.first, CAs.middle, CAs.last, food.price FROM CAs INNER JOIN food ON CAs.id = food.ca WHERE food.con = {$_SESSION['conid']} AND food.price = 0.00 ORDER BY food.price ASC, CAs.last");
?>
<table style="margin-right: 5em">
<tr><th colspan="2">Owner</th><th>Price</th></tr>
<?php
while($row = $GLOBALS['db']->fetch_row($foodqry)) {
	echo "<tr><td colspan=\"2\"><a href=\"caedit.php?ca_id={$row['id']}\">{$row['first']} {$row['middle']} {$row['last']}</a></td><td>&nbsp;&nbsp;&nbsp;&nbsp;\${$row['price']}</td></tr>\n";
}
$countqry = $GLOBALS['db']->query("SELECT Count(food.id) AS NumOfItems, SUM(food.price) as Total FROM food WHERE con = {$_SESSION['conid']} AND food.price = 0.00 ORDER BY NumOfItems");
while($row = $GLOBALS['db']->fetch_row($countqry)) {
        echo "<tr><td><b>Total</b></td><td><b>{$row['NumOfItems']}</b></td><td><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\${$row['Total']}</b></td></tr>\n";
	}
echo "</table>";

$foodqry = $GLOBALS['db']->query("SELECT CAs.id, CAs.first, CAs.middle, CAs.last, food.price FROM CAs INNER JOIN food ON CAs.id = food.ca WHERE food.con = {$_SESSION['conid']} AND food.price <> 0.00 ORDER BY food.price ASC, CAs.last");
?>
<table>
<tr><th colspan="2">Owner</th><th>Price</th></tr>
<?php
while($row = $GLOBALS['db']->fetch_row($foodqry)) {
	echo "<tr><td colspan=\"2\"><a href=\"caedit.php?ca_id={$row['id']}\">{$row['first']} {$row['middle']} {$row['last']}</a></td><td>&nbsp;&nbsp;&nbsp;&nbsp;\${$row['price']}</td></tr>\n";
}
$countqry = $GLOBALS['db']->query("SELECT Count(food.id) AS NumOfItems, SUM(food.price) as Total FROM food WHERE con = {$_SESSION['conid']} AND food.price <> 0.00 ORDER BY NumOfItems");
while($row = $GLOBALS['db']->fetch_row($countqry)) {
        echo "<tr><td><b>Total</b></td><td><b>{$row['NumOfItems']}</b></td><td><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\${$row['Total']}</b></td></tr>\n";
	}
echo "</table>";


require("menu.inc");
?>

</body>

</html>
