<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('uniqueid')) {
	dl('uniqueid.' . PHP_SHLIB_SUFFIX);
}
$module = 'uniqueid';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";

$id = generate_id(123);
echo $id."\n";

//$id = 6247276851392277528;
$time = generate_id_time($id);
echo $time."\n";

$iden = generate_id_iden($id);
echo $iden."\n";
?>
