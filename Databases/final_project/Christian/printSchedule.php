<html>

<body>
<b>Print Schedule</b><br><br>

<form method="post" action="">

Student ID: <input type="text" name="ID">
<input type="submit" name="submit" value="Enter"><br>

<?php

$sID = htmlspecialchars($_POST['ID']);

$dbhost = 'oniddb.cws.oregonstate.edu';		
$dbname = 'armatasc-db';		
$dbuser = 'armatasc-db';		
$dbpass = '98xf7xW8S5pkhLuR';		

	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die("Error connecting to database server");
	
	$query = "SELECT S.sID, E.cID, C.cName, E.term FROM StudentInfo S, courseInfo C, enrollment E WHERE S.sID = '$sID' AND S.sID = E.sID AND E.cID = C.cID;";
	$result = mysqli_query($dbc,$query) or die(mysql_error());
	
	while($row = mysqli_fetch_array($result))
	{
		echo '<br>';
		echo 'Course ID: ';
		echo $row[1];
		echo'<br>';
		echo 'Course Name: ';
		echo $row[2];
		echo '<br>';
		echo 'Term: ';
		echo $row[3];
		echo '<br>';
		
	}
	mysqli_close($mysql_handle);
	echo "<br><a href=http://web.engr.oregonstate.edu/~armatasc/Assign2/homePage/php>Return to Home Page</a><br>";
	?>
</body>

</html>