<?php

session_name("condb");
session_start();
session_unset();
session_destroy();
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
   "http://www.w3.org/TR/html4/strict.dtd">
<html>

<head>
<meta HTTP-EQUIV='Content-Type' CONTENT='text/html; charset=iso-8859-1'>
<meta HTTP-EQUIV='Content-Style-Type' CONTENT='text/css'>
<meta HTTP-EQUIV='Content-Script-Type' CONTENT='text/javascript'>
<style TYPE='text/css'>
<?php
readfile("base.css");
?>
</style>
</head>

<body>
<h1>Session Reset</h1>

<a href="search.php">Return to CA Search</a>
</body>
</html>