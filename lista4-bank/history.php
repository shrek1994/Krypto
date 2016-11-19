<?php

	$host = "localhost";
	$user = "root";
	$pass = "root";
	$db = "test";

	$conn = mysql_connect($host, $user, $pass);
	if(! $conn ) {
	   die('Could not connect: ' . mysql_error());
	}
	mysql_select_db($db);
	

	$sql = "SELECT * FROM transfers ORDER BY id DESC";
	$res = mysql_query($sql);
	$rek = mysql_fetch_array($res); 
    $amount = $rek['amount'];
	$receiver =  $rek['receiver']; 		
	$title =  $rek['title']; 
	
	echo'
<html>

<head>
    <title>Przelew</title>
	<script src="script.js">  </script>
	<script src="faker.js">  </script>
    <link rel="stylesheet" href="styles.css">
    <meta charset="utf-8">
</head>
<body onload="fakeHistory()">

    <div id="content" style="max-width:800px; height:800px;">
        <div id="container">
            <img src="sync2.png" alt="T-MOBILE USŁUGI BANKOWE">

            <table id="report">
				<tr id="head">
                    <th>OSTATNI PRZELEW:</th>
                </tr>
                <tr>
                    <th>Nr konta</th>
                </tr>
                <tr>
                    <td id="account">' .$receiver. '</td>
                </tr>
                <br>
                <tr>
                    <th>Tytuł</th>
                </tr>
                <tr>
                    <td id="transferText">' .$title. '</td>
                </tr>
                <br>
                <tr>
                    <th>Kwota</th>
                </tr>
                <tr>
                    <td id="amount">' .$amount. '</td>
                </tr>
            </table>
            <br><br>


        </div>
    </div>
    <footer>
        Jesli ta strona wydaje Ci się podejrzana, lub po prostu nieprofesjonalnie wykonana, zgłoś to w placówce naszego banku
    </footer>
</body>
</html>
';

	

?>
