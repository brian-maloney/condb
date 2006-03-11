<?php
require_once("session.inc");
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <title>CA Merge Tool</title>
<?php
require_once("condb.inc");

function runandprint($qry) {
	$GLOBALS['db']->query($qry);
	echo "$qry\n";
}
?>

</style>
</head>

<body>

<h2 style="text-align:center">CA Merge Tool</h2>

<form method="POST">
<?php
if (($_SERVER['REQUEST_METHOD'] != "POST") || !isset($_POST['function'])) {
?>
<table align="center">
<tr>
    <th colspan="3" style="text-align: center">Select two CA's to merge or enter filter:</th>
</tr>
<tr>
    <td colspan="3" style="text-align: center"><input type="text" name="filter"></input><input type="submit" value="Filter"></input></td>
</tr>
<tr>
<?php
    if (isset($_POST['filter'])) $filter = "WHERE CONCAT(CAs.first, ' ', CAs.last) LIKE '%{$_POST['filter']}%'";
    else $filter = "";
    echo "<!-- Filter: $filter -->";
    $caoptlist = "";
    $caqry = $GLOBALS['db']->query("SELECT CAs.id, CAs.first, CAs.last FROM CAs $filter ORDER BY CAs.last");
    while($row = $GLOBALS['db']->fetch_row($caqry)) $caoptlist .= "<option value=\"{$row['id']}\">{$row['id']} - {$row['first']} {$row['last']}</option>\n";
?>
    <td style="padding-right: 3em">
        <select name="ca1" size="25"><?php echo $caoptlist ?></select>
    </td>
    <td><-></td>
    <td style="padding-left: 3em">
        <select name="ca2" size="25"><?php echo $caoptlist ?></select>
    </td>
</tr> 
</table>
<div  style="text-align: center; margin-top: 1em"><input type="submit" name="function" value="Next Page >>"></input></div>
</form>
<?php
}
elseif ($_POST['function'] == "Next Page >>") {
    $ca1 = new ca(min($_POST['ca1'], $_POST['ca2']));
    $ca2 = new ca(max($_POST['ca1'], $_POST['ca2']));
    echo "<input type=\"hidden\" name=\"target_ca\" value=\"{$ca1->obj_id}\"></input>\n";
    echo "<input type=\"hidden\" name=\"source_ca\" value=\"{$ca2->obj_id}\"></input>\n";
?>
<table align="center">
<tr>
    <th colspan="4" style="text-align: center">Select CA Elements</th>
</tr>
<?php
    foreach ($ca1->fields as $fieldname => $field) if ($fieldname != "id") echo "<tr><td style=\"padding-right: 1em\"><input type=\"radio\" name=\"$fieldname\" value=\"" . htmlentities($field) . "\" checked>$fieldname</input></td>\n<td style=\"padding-right: 3em\">$field</td>\n<td style=\"padding-left: 3em; padding-right: 1em\"><input type=\"radio\" name=\"$fieldname\" value=\"" . htmlentities($ca2->fields[$fieldname]) . "\">$fieldname</input></td>\n<td>{$ca2->fields[$fieldname]}</td></tr>\n";
?>
<tr>
    <th colspan="4" style="text-align: center; padding-top: 1em">Select Addresses</th>
</tr>
<?php
    foreach ($ca1->addresses as $addrname => $addr) echo "<tr><td style=\"padding-right: 1em; text-align: right\"><input type=\"checkbox\" name=\"{$addrname}\" value=\"keepthisaddr\" checked></input></td><td colspan=\"3\">{$addr->fields['addr1']} {$addr->fields['city']} {$addr->fields['state']}</td></tr>\n";
    foreach ($ca2->addresses as $addrname => $addr) echo "<tr><td style=\"padding-right: 1em; text-align: right\"><input type=\"checkbox\" name=\"{$addrname}\" value=\"keepthisaddr\" checked></input></td><td colspan=\"3\">{$addr->fields['addr1']} {$addr->fields['city']} {$addr->fields['state']}</td></tr>\n";
?>
</table>
<div  style="text-align: center; margin-top: 1em"><input type="submit" name="function" value="Complete Merge"></input></div>
</form>
<?php
}
elseif ($_POST['function'] == "Complete Merge") {
echo "<h4>Merge steps:</h4>\n";
echo "<pre>";
runandprint("UPDATE addresses SET ca = {$_POST['source_ca']} WHERE ca = {$_POST['target_ca']}");
foreach (array_keys($_POST, "keepthisaddr") as $addrid) runandprint("UPDATE addresses SET ca = {$_POST['target_ca']} WHERE id = $addrid");
runandprint("UPDATE many SET toid = {$_POST['target_ca']} WHERE totable = 'CAs' AND toid = {$_POST['source_ca']}");
runandprint("UPDATE many SET fromid = {$_POST['target_ca']} WHERE fromtable = 'CAs' AND fromid = {$_POST['source_ca']}");
foreach($_SESSION['classes'] as &$class) if (in_array("ca", $GLOBALS['db']->get_fields($class['table']))) runandprint("UPDATE {$class['table']} SET ca = {$_POST['target_ca']} WHERE ca = {$_POST['source_ca']}");
runandprint("DELETE FROM addresses WHERE ca = {$_POST['source_ca']}");
runandprint("DELETE FROM pictures WHERE id = {$_POST['source_ca']}");
runandprint("DELETE FROM CAs WHERE id = {$_POST['source_ca']}");

echo "</pre><h4>Final CA Fields:</h4><pre>\n";
$updca = new ca($_POST['target_ca']);
foreach ($updca->fields as $fieldname => &$field) if (isset($_POST[$fieldname])) $field = $_POST[$fieldname];
print_r($updca->fields);
$updca->save();

echo "</pre>\n<a href=\"camerge.php\">9-10, Start Over Again!</a>\n";
}
?>
</body>
</html>
