<?php
require_once('db.inc');
require_once('db_object.inc');

function load_object($objname, $table, $loadphp = false, $loadjs = false) {
	global $css;
	global $javascript;
	if ($loadphp) {
		if (file_exists(strtolower($objname) . ".inc")) {
			require_once(strtolower($objname) . ".inc");
		}
		else {
			eval('class ' . strtolower($objname) . ' extends db_object {
			function __construct($loadid = 0) {
				$this->table = "' . $table . '";
				parent::__construct($loadid);
			}
			}
			');
		}
	}
   	if (file_exists(strtolower($objname) . ".css")) {
   		$css[strtolower($objname)] = trim(implode("", file(strtolower($objname) . ".css"))) . "\n";
   	}
	if ($loadjs) {
	       $javascript[strtolower($objname)] = "";
           if (file_exists(strtolower($objname) . ".js")) {
               $javascript[strtolower($objname)] .= '<script type="text/javascript" src="' . strtolower($objname) . ".js" . '">' . "\n";
               $javascript[strtolower($objname)] .= "</script>\n";
           }
           elseif (file_exists(strtolower($objname) . "_js.inc")) {
               $javascript[strtolower($objname)] .= "<script type=\"text/javascript\">\n";
               ob_start();
               require(strtolower($objname) . "_js.inc");
               $javascript[strtolower($objname)] .= ob_get_contents();
               ob_end_clean();
               $javascript[strtolower($objname)] .= "</script>\n";
           }
           elseif (class_exists($objname)) {
               $temp = new $objname;
               $javascript[strtolower($objname)] .= "<script type=\"text/javascript\">\n";
               $javascript[strtolower($objname)] .= 'function new' . strtolower($objname) . '() {' . "\n";
               $javascript[strtolower($objname)] .= str_replace('tname', strtolower($objname),'	var myID = newID();
           var newRoot = newDiv("tname_" + myID + "_editor", "tname_editor");
           var newNode = newRoot.appendChild(newInput("", "", "hidden", "editobj_tname_" + myID, "true"));
           newRoot.appendChild(document.createTextNode(" "));') . "\n";
               foreach($temp->fields as $fieldname => $fieldval) if ($fieldname != "id") $javascript[strtolower($objname)] .= str_replace("tname", strtolower($objname), str_replace("fname", $fieldname, str_replace("ucfname", ucwords(strtolower($fieldname)), '	newNode = newRoot.appendChild(newSection("fname", "ucfname"));
           newNode.appendChild(newInput("", "fname", "text", "tname_" + myID + "_fname", ""));
           newNode.appendChild(document.createTextNode(" "));'))) . "\n";
               $javascript[strtolower($objname)] .= '	newRoot.appendChild(document.createTextNode(" "));
           return newRoot;' . "\n";
               $javascript[strtolower($objname)] .= '}' . "\n";
               $javascript[strtolower($objname)] .= "</script>\n";
               unset($temp);
           }
    }
}

$GLOBALS['db'] = new dbconn();
$GLOBALS['dbtrace'] = false;

if (!isset($_SESSION['conid'])) list($_SESSION['conid']) = $GLOBALS['db']->fetch_row($GLOBALS['db']->query("SELECT id FROM cons WHERE NOT active = 0"));

if (!isset($_SESSION['classes'])) {
	$stuffqry = $GLOBALS['db']->query("SELECT * FROM classes");
	while ($row = $GLOBALS['db']->fetch_row($stuffqry, MYSQL_ASSOC)) $_SESSION['classes'][strtolower($row['singular'])] = $row;
}

if (!isset($_SESSION['db_enums'])) {
	$enum_tables = array("badgestatus", "badgetypes", "merchtypes", "paytypes", "reftypes", "attrtypes", "cons");
	foreach($enum_tables as $table) {
		$enumqry = $GLOBALS['db']->query("SELECT * FROM $table");
		while ($row = $GLOBALS['db']->fetch_row($enumqry, MYSQL_ASSOC)) {
			$_SESSION['db_enums'][$table][$row['id']] = $row;
			unset($_SESSION['db_enums'][$table][$row['id']]['id']);
		}
	}
}

$css['base'] = trim(implode("", file("base.css"))) . "\n";

$javascript["base"] .= '<script type="text/javascript" src="md5.js">' . "\n";
$javascript["base"] .= '</script>' . "\n";
$javascript["base"] .= '<script type="text/javascript" src="cookies.js">' . "\n";
$javascript["base"] .= '</script>' . "\n";
$javascript["base"] .= '<script type="text/javascript" src="base.js">' . "\n";
$javascript["base"] .= '</script>' . "\n";

load_object('ca', 'CAs', true, true);
load_object('address', 'addresses', true, true);
load_object('inventory', 'inventory', true, false);

foreach ($_SESSION['classes'] as $db_obj_type) load_object(strtolower($db_obj_type['singular']), $db_obj_type['table'], true, true);

// Snag edited/new objects from the POST

if ($_SERVER['REQUEST_METHOD'] == "POST") {

	$GLOBALS['postobjs'] = array();
	$postcas = array();

	foreach($_POST as $postvar => $value) {
		list($isedit, $oclass, $oid) = explode("_", $postvar);
		if ($isedit == "editobj") {
			if ($oclass == "ca") $postcas[] = $oid;
			else {
				eval("\$GLOBALS['postobjs']['$oclass'][\$oid] = new $oclass($oid);");
				$GLOBALS['postobjs'][$oclass][$oid]->readvals();
			}
		}
	}
// Load CAs last so they can grab their addresses and stuff objects if any exist
	foreach($postcas as $oid) {
		$GLOBALS['postobjs']['ca'][$oid] = new ca($oid);
		$GLOBALS['postobjs']['ca'][$oid]->readvals();
	}
}

?>
