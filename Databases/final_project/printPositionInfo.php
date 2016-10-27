<html>

<body>

<b>Print Position Information</b><br><br>

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
	
	$query = "SELECT M.fName, M.chapter, M.mName, P.posName, P.dateElected, P.rank FROM final_position P, final_membership M WHERE P.sID = M.sID AND M.fName = '$fName' AND M.chapter = '$chapter';";
	$result = mysqli_query($dbc,$query) or die(mysql_error());
	
	while($row = mysqli_fetch_array($result))
	{
		echo 'Fraternity Name: ';
		echo $row[0];		
		echo'<br>';
		echo 'Chapter: ';
		echo $row[1];
		echo '<br>';
		echo 'Member Name: ';
		echo $row[2];
		echo '<br>';
		echo 'Position Name: ';
		echo $row[3];
		echo '<br>';
		echo 'Date Elected: ';
		echo $row[4];
		echo '<br>';
		echo 'Rank: ';
		echo $row[5];
		echo '<br>';
	}
	mysqli_close($mysql_handle);
	echo "<br><a href=http://web.engr.oregonstate.edu/~armatasc/cs275project/index>Return to Home Page</a><br>";
	
?>
</body>

</html>