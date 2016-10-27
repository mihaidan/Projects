<html>

<body>

<b>Scheduled Parties and Member Attendance</b><br><br>

<form method="post" action="">

Party Name: <input type="text" name="pName"><br>
Party Date: <input type="date" name="pDate">
<input type="submit" name="submit" value="Enter"><br><br>

<?php

$pName = htmlspecialchars($_POST['pName']);
$pDate = htmlspecialchars($_POST['pDate']);

$dbhost = 'oniddb.cws.oregonstate.edu';		
$dbname = 'armatasc-db';		
$dbuser = 'armatasc-db';		
$dbpass = '98xf7xW8S5pkhLuR';		

	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die("Error connecting to database server");
	
	$query = "SELECT M.mName, A.soberBrother, A.guestName FROM final_attendance A, final_membership M WHERE M.sID = A.sID AND A.partyName = '$pName' AND A.partyDate = '$pDate';";
	$result = mysqli_query($dbc,$query) or die(mysql_error());
	
		while($row = mysqli_fetch_array($result))
		{	echo "Party Name: ";
			echo "{$pName}<br>";
			echo "Party Date: ";
			echo "{$pDate}<br>";
			echo 'Member Name: ';
			echo $row[0];		
			echo'<br>';
			echo 'Sober?: ';
			echo $row[1];
			echo '<br>';
			echo 'Guest Name: ';
			echo $row[2];
			echo '<br><br>';
		};

	mysqli_close($mysql_handle);
	echo "<br><a href=http://web.engr.oregonstate.edu/~armatasc/cs275project/index>Return to Home Page</a><br>";
	
?>

</body>

</html>