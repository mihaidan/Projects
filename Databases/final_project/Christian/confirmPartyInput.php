<html>

<body>
<?php
	$party_name = htmlspecialchars($_POST['partyName']);
	$address = htmlspecialchars($_POST['partyAddress']);
	$date = htmlspecialchars($_POST['partyDate']);
	$start_time = htmlspecialchars($_POST['startTime']);
	$theme = htmlspecialchars($_POST['partyTheme']);
 	$host_house = htmlspecialchars($_POST['hostHouse']);
	$additional_houses = htmlspecialchars($_POST['additionalHouse']);

	$dbhost = 'oniddb.cws.oregonstate.edu';		
	$dbname = 'armatasc-db';		
	$dbuser = 'armatasc-db';		
	$dbpass = '98xf7xW8S5pkhLuR';

	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die("Error connecting to database server");
	$query = "INSERT INTO final_party(partyName, address, date,  startTime, theme, hostHouse, additionalHouses) VALUES ('$party_name', '$address', '$date', '$start_time', '$theme','$host_house', '$additional_houses')";

	$result = mysqli_query($dbc, $query) or die("Error in querying database.");
	
	echo "Thank you for entering your party information. Have fun! <br><br>";
	echo "Party Name: $party_name <br>Place to be: $address <br>When to be there: $date <br>What time?: $start_time <br>Dressed as: $theme <br>Hosted by: $host_house <br>Other guys: $additional_houses <br><br>";

	mysqli_close($dbc);
	echo "<a href=http://web.engr.oregonstate.edu/~armatasc/Assign2/homePage/php>Return to Home Page</a>";
	
?>
</body>
</html>