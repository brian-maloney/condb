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
<title>Historical Con Statistics</title>

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
</style>
</head>

<body>
<h1>Historical Con Statistics</h1>
<?php
$statsqry = $GLOBALS['db']->query("SELECT * FROM constats");
$statsfields = $GLOBALS['db']->get_fields("constats");
?>
<table>
<tr>
<?php
foreach ($statsfields as $fieldname) echo "<th>$fieldname</th>";
?>
<th>New Attendees</th>
</tr>
<?php
while($row = $GLOBALS['db']->fetch_row($statsqry)) {
	echo "<tr>";
	foreach ($statsfields as $fieldname) echo "<td>{$row[$fieldname]}</td>";
	$newqry = $GLOBALS['db']->query("SELECT COUNT(*) AS 'New Attendees' FROM CAs WHERE CAs.id NOT IN (SELECT DISTINCT ca FROM badges WHERE con < {$row['Con ID']} AND ca IS NOT NULL) AND CAs.id IN (SELECT DISTINCT ca FROM badges WHERE con = {$row['Con ID']} AND ca IS NOT NULL)");
	echo "<td>";
	while ($newrow = $GLOBALS['db']->fetch_row($newqry)) echo $newrow[0];
	echo "</tr>\n";
}
echo "</table>";

require("menu.inc");
?>

</body>

</html>
