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
<title>Badge Browser</title>

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
}
tr td:first-child {
text-align: left;
}
tr td {
text-align: right;
}
table {
	border-collapse: collapse;
	border-spacing: 0;
}
</style>
</head>

<body>
<h1>Badge Browser</h1>
<?php
if ($_GET['btype']) {
	$badgeqry = $GLOBALS['db']->query("SELECT CAs.id, CAs.first, CAs.middle, CAs.last, badges.badgeno, badges.status, badges.price FROM CAs INNER JOIN badges ON CAs.id = badges.ca WHERE badges.con = {$_SESSION['conid']} AND badges.type = {$_GET['btype']} ORDER BY badgeno");
?>
<table>
<tr><th>Badge Number</th><th>Owner</th><th>Status</th><th>Price</th></tr>
<?php
while($row = $GLOBALS['db']->fetch_row($badgeqry)) {
	echo "<tr><td>" . $row['badgeno'] . "</td><td><a href=\"caedit.php?ca_id={$row['id']}\">{$row['first']} {$row['middle']} {$row['last']}</a></td><td>&nbsp;&nbsp;&nbsp;&nbsp;{$_SESSION['db_enums']['badgestatus'][$row['status']]['name']}</td><td>&nbsp;&nbsp;&nbsp;&nbsp;\${$row['price']}</td></tr>\n";
}
echo "</table>";
}
else {
?>
<table>
<tr><th>Badge Type</th><th>Count</th><th>Total</th></tr>
<?php
$countqry = $GLOBALS['db']->query("SELECT Count(badges.badgeno) AS NumOfBadges, badges.type AS BadgeType, SUM(badges.price) AS TypeTotal FROM badges WHERE con = {$_SESSION['conid']} GROUP BY badges.type ORDER BY badges.type");
while($row = $GLOBALS['db']->fetch_row($countqry)) {
	echo "<tr><td><a href=\"badgebrowse.php?btype={$row['BadgeType']}\">" . $_SESSION['db_enums']['badgetypes'][$row['BadgeType']]['name'] . "</a></td><td>{$row['NumOfBadges']}</td><td>\${$row['TypeTotal']}</td></tr>\n";
}
$countqry = $GLOBALS['db']->query("SELECT Count(badges.badgeno) AS NumOfBadges, SUM(badges.price) as Total FROM badges where con = {$_SESSION['conid']} ORDER BY NumOfBadges");
while($row = $GLOBALS['db']->fetch_row($countqry)) {
	echo "<tr><td><b>Total</b></td><td><b>{$row['NumOfBadges']}</b></td><td><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\${$row['Total']}</b></td></tr>\n";
}
?>
</table>
<?php
}
require("menu.inc");
?>

</body>

</html>
