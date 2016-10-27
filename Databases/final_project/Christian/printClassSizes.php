<html>

<body>
<b>Class Sizes</b><br><br>

<?php

$dbhost = 'oniddb.cws.oregonstate.edu';		
$dbname = 'armatasc-db';		
$dbuser = 'armatasc-db';		
$dbpass = '98xf7xW8S5pkhLuR';		

	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die("Error connecting to database server");

	$query = "SELECT C.cID, C.cName, COUNT(E.cID) FROM courseInfo C, enrollment E WHERE C.cID = E.cID GROUP BY C.cID HAVING COUNT(E.cID) > 0;";
	$result = mysqli_query($dbc,$query) or die(mysql_error());
	
	while ($row = mysqli_fetch_array($result))
	{	echo '<br>';
		echo"Course ID: ";
		echo $row[0];
		echo"<br>";
		echo"Course Name: ";
		echo $row[1];
		echo"<br>";
		echo"Class Size: ";
		echo $row[2];
		echo"/100<br>";
	}
	mysqli_close($mysql_handle);
	echo "<br><a href=http://web.engr.oregonstate.edu/~armatasc/Assign2/homePage/php>Return to Home Page</a><br>";
	?>
	
</body>

</html>