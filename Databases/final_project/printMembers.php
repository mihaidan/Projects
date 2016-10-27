<html>

<body>

<b>Print Members</b><br><br>

<form method="post" action="">

Fraternity Name: <input type="text" name="fName"><br>
Fraternity Chapter: <input type="text" name="chapter">
<input type="submit" name="submit" value="Enter"><br><br>

<?php

$fName = htmlspecialchars($_POST['fName']);
$chapter = htmlspecialchars($_POST['chapter']);

$dbhost = 'oniddb.cws.oregonstate.edu';		
$dbname = 'armatasc-db';		
$dbuser = 'armatasc-db';		
$dbpass = '98xf7xW8S5pkhLuR';		

	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die("Error connecting to database server");
	
	$query = "SELECT M.mName, M.Age, M.yearInHouse FROM final_membership M WHERE M.fName = '$fName' AND M.chapter = '$chapter';";
	$result = mysqli_query($dbc,$query) or die(mysql_error());
	
	while($row = mysqli_fetch_array($result))
	{
		echo 'Name: ';
		echo $row[0];		
		echo'<br>';
		echo 'Age: ';
		echo $row[1];
		echo '<br>';
		echo 'Year In House: ';
		echo $row[2];
		echo '<br>';
	}
	mysqli_close($mysql_handle);
	echo "<br><a href=http://web.engr.oregonstate.edu/~armatasc/cs275project/index>Return to Home Page</a><br>";
	
?>

</body>

</html>