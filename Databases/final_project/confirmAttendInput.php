<html>

<body>
<?php
	$student_ID = htmlspecialchars($_POST['ID']);
	$party_name = htmlspecialchars($_POST['partyname']);
	$party_date = htmlspecialchars($_POST['partydate']);
	$sober= htmlspecialchars($_POST['sober']);
	$guest_name = htmlspecialchars($_POST['guestname']);


	$dbhost = 'oniddb.cws.oregonstate.edu';		
	$dbname = 'armatasc-db';		
	$dbuser = 'armatasc-db';		
	$dbpass = '98xf7xW8S5pkhLuR';

	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die("Error connecting to database server");
	
	$query = "INSERT INTO final_attendance(sID, partyName, partyDate,  soberBrother, guestName) VALUES ('$student_ID', '$party_name', '$party_date', '$sober', '$guest_name');";
	$result = mysqli_query($dbc, $query) or die("Error in querying database.");
	
	echo "Thank you for submitting your attendance information! <br>You are now scheduled to attend $party_name on $party_date. <br><br>";
	echo "Sober?: $sober <br>Guest: $guest_name <br><br>";

	mysqli_close($dbc);
	echo "<a href=http://web.engr.oregonstate.edu/~armatasc/cs275project/index>Return to Home Page</a>";
	
?>
</body>
</html>