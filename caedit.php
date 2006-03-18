<?php
require_once("session.inc");
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <title>CA Editor</title>
  <meta http-equiv="Pragma" content="no-cache">
  <meta http-equiv="Expires" content="-1">
<?php
require_once("condb.inc");
echo implode("", $javascript);

if ($_SERVER['REQUEST_METHOD'] == "POST") {
	$ca =& current($postobjs['ca']);
	$ca->save();
	if ($_SESSION['ca_pic']['dirty']) {
		if ($_SESSION['ca_pic']['in_db']) $GLOBALS['db']->query("UPDATE pictures SET picture = '" . $GLOBALS['db']->escape($_SESSION['ca_pic']['data']) . "' WHERE id = {$ca->obj_id}");
		else $GLOBALS['db']->query("INSERT INTO pictures(picture, id) VALUES('" . $GLOBALS['db']->escape($_SESSION['ca_pic']['data']) . "', {$ca->obj_id})"); 
	}
}
elseif (isset($_GET['ca_id'])) $ca = new ca($_GET['ca_id']);
else $ca = new ca();
if (isset($_SESSION['ca_id']) && ($_SESSION['ca_id'] != $ca->obj_id)) unset($_SESSION['ca_pic']);
$_SESSION['ca_id'] = $ca->obj_id;
?>

<script type="text/javascript">
function currentAddress() {
	var addrdivs = document.getElementById("addrEdit").getElementsByTagName("div");
	var cur = -2;
	for (x=0; x<addrdivs.length; x++) if (addrdivs[x].style.display != "none") cur = x;
	return cur;
}
function selectAddress(target) {
	var addrdivs = document.getElementById("addrEdit").getElementsByTagName("div");
	if (target == -1) target = addrdivs.length - 1;
	else target %= addrdivs.length;
	for (x=0; x<addrdivs.length; x++) {
		if (x == target) addrdivs[x].style.display = "block";
		else addrdivs[x].style.display = "none";
	}
	var newInfo = "";
	var desc = addrdivs[target].childNodes[4].childNodes[1].value;
	if (desc != "" && String(desc) != "undefined") newInfo = newInfo + ": " + desc;
	newInfo = newInfo + " (" + (target + 1) + " of " + addrdivs.length + ")";
	if (document.getElementById("addrInfo").childNodes.length == 0) {
		document.getElementById("addrInfo").appendChild(document.createTextNode(" "));
	}
	document.getElementById("addrInfo").firstChild.replaceData(0, 100, newInfo);
}
function addAddress() {
	var addrdivs = document.getElementById("addrEdit").getElementsByTagName("div");
	for (var x=0; x<addrdivs.length; x++) addrdivs[x].style.display = "none";
	document.getElementById('addrEdit').appendChild(newaddress());
	var newInfo = "";
	newInfo = newInfo + " (" + addrdivs.length + " of " + addrdivs.length + ")";
	if (document.getElementById("addrInfo").childNodes.length == 0) {
		document.getElementById("addrInfo").appendChild(document.createTextNode(" "));
	}
	document.getElementById("addrInfo").firstChild.replaceData(0, 100, newInfo);
}
function updateTotal() {
	var inputs = document.getElementById("stuff").getElementsByTagName("input");
	total = 0;
	for (x=0; x<inputs.length; x++) {
		if ((inputs[x].id != "total") && (inputs[x].className == "price")) {
			str = String(inputs[x].value);
			total = total + Number(str.replace(/\D/, ""));
		}
	}
	document.getElementById("total").value = "$" + total.toFixed(2);
}
function mailAddr(changed) {
	var inputs = document.getElementById("addrEdit").getElementsByTagName("input");
	for (x=0; x<inputs.length; x++) if (inputs[x].name.substr(-7,7) == "mailing") if (inputs[x].name != changed) inputs[x].checked = false;
}

function picShow(mode) {
	if (!mode) mode = "display";
	document.getElementById("pic_content").innerHTML = "<img src=\"picture.php?mode=" + mode + "&dummy=" + newID() + "\">";
}

function initDynamicFields() {
	picShow("display");
}

currentCA = "<?php echo $ca->obj_id ?>";
</script>
<style type="text/css">
<?php
echo implode("", $css);
?>
.mainsheet {
position: absolute;
left: 1em;
right: 1em;
top: 3em;
border: groove;
min-width: 56em;
}
.mainsheet .content {
padding: 0.5em;
}
.ca_editor span.comments {
margin-top: 0.5em;
}
.ca_editor input.first {
width: 20%
}
.ca_editor input.middle {
width: 10%
}
.ca_editor input.last {
width: 25%
}
.ca_editor input.nick {
width: 28%
}
.ca_editor span.gender span.label {
display: none;
}
.ca_editor span.age {
display: inline;
margin-left: 1em;
margin-right: 1em;
}
.ca_editor span.gender {
display: inline;
}
.ca_editor span.nick {
display: inline;
}
.ca_editor span.reference {
margin-top: 0.5em;
}
.ca_editor span.attraction {
position: relative;
top: -2.1em;
left: 55%;
margin-bottom: -2.1em;
}
.ca_editor span.comments textarea {
height: 5em;
width: 82%;
}
.address_editor span.description {
position: absolute;
right: 0.5em;
top: 1.9em;
}
.address_editor span.validfrom {
position: absolute;
right: 0.5em;
top: 3.7em;
}
.address_editor span.validto {
position: absolute;
right: 0.5em;
top: 5.5em;
}
.address_editor span.lastcheck {
position: absolute;
right: 0.5em;
top: 7.2em;
}
.address_editor span.straddr input {
width: 25%;
margin-bottom: 0.2em;
}
.address_editor span.city {
position: absolute;
top: 1.9em;
left: 40%;
}
.address_editor span.state {
position: absolute;
top: 3.7em;
left: 40%;
}
.address_editor span.zip {
position: absolute;
top: 5.5em;
left: 40%;
}
.address_editor span.country {
position: absolute;
top: 7.2em;
left: 40%;
}
.address_editor span.valid {
position: absolute;
top: 4em;
right: 14em;
}
.address_editor span.mailing {
position: relative;
top: -0.3em;
left: 7em;
margin-bottom: -0.4em;
}
#picture {
position: absolute;
right: 0em;
top: 0em;
width: 16em;
}
#picture .content img {
width: 100%
}
#stuff .label:after {
content: ": ";
}
#stuff .price>span.label {
display: none;
}
#stuff .amount>span.label {
display: none;
}
#stuff input.notes {
width: 19em
}
#stuff input.details {
width: 19em
}
#stuff>div {
position: relative;
width: 100%;
border-top: thin solid;
padding-top: 0.5em;
margin-bottom: 0.5em;
}
#stuff .price {
position: absolute;
right: 0.5em;
top: 0.3em;
}
#stuff .amount {
position: absolute;
right: 0.5em;
top: 0.3em;
}
.mainsheet .subsheet {
position: relative;
}
.mainsheet .header {
position: relative;
background: #222277;
color: white;
width: 90%;
padding-left: 0.5em;
}
.mainsheet .controls {
position: absolute;
top: 0em;
right: 0em;
background: #222277;
color: white;
min-width: 11%;
text-align: right;
cursor: default;
padding-right: 0.5em;
}
.mainsheet .controls .help span {
display: none;
}
.mainsheet .controls>span {
cursor: pointer;
padding-left: 0.1em;
padding-right: 0.1em;
text-align: left;
}
.mainsheet .controls>span:hover {
color: yellow;
background: #113;
}
.mainsheet .controls .help {
cursor: default;
}
.mainsheet .controls .help:hover span {
display: block;
position: absolute;
border: thin groove;
right: 1em;
top: 1.4em;
color: #000;
background: #FFFFCC;
width: 15em;
font-size: 0.8em;
cursor: default;
z-index: 100;
}
#stuffmenu {
position: absolute;
border: thin black groove;
right: 1em;
top: 1em;
background: #FFC;
z-index: 100;
padding-left: 1em;
padding-right: 1em;
padding-top: 0.1em;
padding-bottom: 0.1em;
font-size: 1.2em;
}
#stuffmenu .item {
display: block;
color: #000;
}
#stuffmenu .item:hover {
display: block;
color: #000;
color: yellow;
background: #113;
}
</style>
</head>

<body onload="initDynamicFields()">
<form class="mainsheet" action="caedit.php" method="post">
<div style="padding-right: 16em">
<div class="subsheet" style="position: relative; border-right: inset">
<div class="header">CA Personal Details</div><div class="controls">[<span class="help">?<span>This window allows you to view and edit the Convention Attendee's personal details, such as name, gender, age, and edit any special comments about them.</span></span>]</div>
<div class="content"><div class="editors">
<?php
echo $ca->editor();
?>
</div></div></div>
</div>
<div class="subsheet" id="picture">
<div class="header">Mugshot</div>
<div class="controls">[<span class="menu"><span class="item">+<div id="stuffmenu"><div class="item" onclick="ajaxRequest('pic_content', 'camconf')">Configure</div><div class="item" onclick="picShow('capture')">Capture</div><div class="item" onclick="picShow('reset')">Reset</div></div></span></span>] [<span class="help">?<span>This window displays a picture of the Convention Attendee if one exists in the database.</span></span>]</div>
<div class="content" id="pic_content"></div>
</div>
<div class="subsheet" style="border-top: inset; min-height: 8em">
<div class="header">Addresses<span id="addrInfo"><?php
if (count($ca->addresses) > 0) {
	reset($ca->addresses);
	$cur = 0;
	while (list($key, $val) = each($ca->addresses)) {
		$cur++;
		if ($val->fields['mailing']) {
			prev($ca->addresses);
			break;
		}
	}
	$addr =& current($ca->addresses);
	if ($addr->fields['description'] != "") echo ": {$addr->fields['description']}";
	echo " ($cur of ", count($ca->addresses), ")";
}
?></span></div>
<div class="controls">[<span onclick="selectAddress(currentAddress() - 1)">&lt;&lt;</span>] [<span onclick="selectAddress(currentAddress() + 1)">&gt;&gt;</span>] [<span onclick="addAddress()">+</span>] [<span class="help">?<span>This window lists the addresses associated with the current Convention Attendee.  You may scroll through the addresses with the left and right buttons, or add a new address with the plus button.</span></span>]</div>
<div class="content"><div class="editors" id="addrEdit">
<?php
if (count($ca->addresses) > 0) {
	reset($ca->addresses);
	while(list($key, $addr) = each($ca->addresses)) {
		$cur--;
		echo str_replace("class=\"address_editor\"", "class=\"address_editor\" style=\"display: " . (($cur == 0) ? "block" : "none") . '"', $addr->editor());
	}
}
?>
</div></div></div>
<div class="subsheet" style="border-top: inset; min-height: 8em; padding-bottom: 1.5em">
<div class="header">Purchased Items</div>
<div class="controls">[<span class="menu"><span class="item">+<div id="stuffmenu"><?
foreach($_SESSION['classes'] as $class) echo '<div class="item" onclick="document.getElementById(\'stuff\').appendChild(new' . strtolower($class['singular']) . '()); updateTotal()">' . $class['singular'] . '</div>';
?><div class="item" onclick="document.getElementById('stuff').appendChild(linktranslist())">Link Trans.</div></div></span></span>] [<span class="help">?<span>This window displays the current items purchased for the current convention by the current Convention Attendee.  You may add purchases of any type with the plus button.</span></span>]</div>
<div class="content" id="stuff">
<div style="width: 100%; text-align: right; position: relative; right: 1.8em; font-weight: bold; border-top: none">Price</div>
<?php
foreach ($ca->stuff as $class) foreach ($class as $item) echo $item->editor();
?>
</div>
<div style="width: 100%; position: relative; padding-top: 1em; padding-bottom: 2em">
<span style="position:absolute; right: 1.5em; border-top: double; padding-top: 0.5em"><b>Total:</b> <input type="text" id="total" class="price" style="width: 4.5em" value="<?php echo $total ?>"></span>
</div>
</div>
<input type="submit" value="Save Changes" style="position: absolute; left: 2em; top: -2.2em">
</form>
<form method="get">
<input type="hidden" name="ca_id" value="<?php if ($ca->in_db) echo $ca->obj_id; ?>"></input>
<input type="submit" value="Reset" style="position: absolute; left: 12em; top: 1em">
</form>
<?php require("menu.inc"); ?>
</select>
<script type="text/javascript">
updateTotal();
</script>
</body>
</html>
