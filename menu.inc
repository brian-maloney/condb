<div style="position: absolute; right: 3em; top: 1em">
<a href="search.php">Search</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="caedit.php">New Attendee</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="badgebrowse.php">Badge Browser</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="merchbrowse.php">Merchandise Browser</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="foodbrowse.php">Food Browser</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<form style="display: inline" id="conselform" action="<?php $_SERVER['REQUEST_URI'] ?>" method="post">
<select name="newcon">
<?php
	foreach($_SESSION['db_enums']['cons'] as $conid => $coninfo) {
		echo "<option value=\"$conid\"";
		if ($_SESSION['conid'] == $conid) echo " selected";
		echo ">{$coninfo['description']}</option>\n";
	}
?>
</select>
<input type="submit" value="Go"></input>
</form>
</div>
