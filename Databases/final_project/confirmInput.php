<html>

<body>
<?php
	$student_ID = htmlspecialchars($_POST['ID']);
	$member_name = htmlspecialchars($_POST['memberName']);
	$age = htmlspecialchars($_POST['age']);
 	$frat_name = htmlspecialchars($_POST['frat']);
	$chapter = htmlspecialchars($_POST['chapter']);	
	$year_in_house = htmlspecialchars($_POST['YIH']);
	
	$posName = htmlspecialchars($_POST['posName']);
	$dateElected = htmlspecialchars($_POST['dateElected']);
	$posRank = htmlspecialchars($_POST['posRank']);
	$description = htmlspecialchars($_POST['description']);

	$dbhost = 'oniddb.cws.oregonstate.edu';		
	$dbname = 'armatasc-db';		
	$dbuser = 'armatasc-db';		
	$dbpass = '98xf7xW8S5pkhLuR';

	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die("Error connecting to database server");
	$query = "INSERT INTO final_membership(sID, mName, Age, yearInHouse, fName, chapter) VALUES ('$student_ID', '$member_name', '$age', '$year_in_house','$frat_name', '$chapter')";
	$result = mysqli_query($dbc, $query) or die("Error in querying database1.");
	
	$query2 = "INSERT INTO final_position(posName, dateElected, rank, description, sID) VALUES('$posName', '$dateElected', '$posRank', '$description', '$student_ID')";
	$result = mysqli_query($dbc, $query2) or die("Error in querying database2.");
	
	echo "Thank you $member_name for submitting your membership information.<br><br>";
	
	echo "Student ID: $student_ID <br>Age: $age <br>Fraternity: $frat_name <br>Chapter: $chapter <br>Year in House: $year_in_house <br><br>";
	echo "Position: $posName <br>Date Elected: $dateElected <br>Rank: $posRank <br>Description: $description <br>";

	mysqli_close($dbc);
	echo "<a href=http://web.engr.oregonstate.edu/~armatasc/cs275project/index>Return to Home Page</a>";
	
?>
</body>
</html>