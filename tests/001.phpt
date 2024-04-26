--TEST--
Check if pgf is loaded
--SKIPIF--
<?php
if (!extension_loaded('pgf')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "pgf" is available';
?>
--EXPECT--
The extension "pgf" is available