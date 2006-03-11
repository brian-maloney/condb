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
<title>Merchandise Browser</title>

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
}
</style>
</head>

<body>
<h1>Merchandise Browser</h1>
<?php
if ($_GET['mtype']) {
	$merchqry = $GLOBALS['db']->query("SELECT CAs.id, CAs.first, CAs.middle, CAs.last, merchandise.type, merchandise.qty, merchandise.price FROM CAs INNER JOIN merchandise ON CAs.id = merchandise.ca WHERE merchandise.con = {$_SESSION['conid']} AND merchandise.type = {$_GET['mtype']} ORDER BY CAs.last");
?>
<table>
<tr><th>Quantity</th><th>Merchandise Type</th><th>Owner</th><th>Price</th></tr>
<?php
while($row = $GLOBALS['db']->fetch_row($merchqry)) {
	echo "<tr><td>" . $row['qty'] . "</td><td>" . $_SESSION['db_enums']['merchtypes'][$row['type']]['name']  . "</td><td><a href=\"caedit.php?ca_id={$row['id']}\">{$row['first']} {$row['middle']} {$row['last']}</a></td><td>&nbsp;&nbsp;&nbsp;&nbsp;\${$row['price']}</td></tr>\n";
}
echo "</table>";
}
else {
?>
<table>
<tr><th>Merchandise Type</th><th>Count</th><th>Total</th></tr>
<?php
$countqry = $GLOBALS['db']->query("SELECT Count(merchandise.id) AS NumOfItems, merchandise.type AS MerchType, SUM(merchandise.price) AS TypeTotal FROM merchandise WHERE con = {$_SESSION['conid']} GROUP BY merchandise.type ORDER BY NumOfItems");
while($row = $GLOBALS['db']->fetch_row($countqry)) {
	echo "<tr><td><a href=\"merchbrowse.php?mtype={$row['MerchType']}\">" . $_SESSION['db_enums']['merchtypes'][$row['MerchType']]['name'] . "</a></td><td>{$row['NumOfItems']}</td><td>\${$row['TypeTotal']}</td></tr>\n";
}
$countqry = $GLOBALS['db']->query("SELECT Count(merchandise.id) AS NumOfItems, SUM(merchandise.price) as Total FROM merchandise where con = {$_SESSION['conid']} ORDER BY NumOfItems");
while($row = $GLOBALS['db']->fetch_row($countqry)) {
	echo "<tr><td><b>Total</b></td><td><b>{$row['NumOfItems']}</b></td><td><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\${$row['Total']}</b></td></tr>\n";
}
?>
</table>
<?php
}
require("menu.inc");
?>

</body>

</html>
