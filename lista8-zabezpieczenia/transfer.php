<?php

function debug_to_console( $data ) {
    if ( is_array( $data ) )
        $output = "<script>console.log( 'Debug Objects: " . implode( ',', $data) . "' );</script>";
    else
        $output = "<script>console.log( 'Debug Objects: " . $data . "' );</script>";
    echo $output;
}

	$host = "localhost";
	$user = "root";
	$pass = "root";
	$db = "test";
	$id;
	if($_COOKIE["id"]==0 || !isset($_COOKIE["id"])){
		echo 'COOKIE id isn\'t correct: '.+$_COOKIE["id"];
		exit();
	}
	else{
		echo 'ok '.$_COOKIE["id"];
		$id = $_COOKIE["id"];
//		unset($_COOKIE["id"]);
//		setcookie("id", '0', time() - 3600, '/');
	}

	$conn = mysql_connect($host, $user, $pass);
	if(! $conn ) {
	   die('Could not connect: ' . mysql_error());
	}
	mysql_select_db($db);


	if (isset($_POST['receiver'])) {
		$receiver = $_POST['receiver'];
		$title = $_POST['title'];
		$amount = $_POST['amount'];
		$sql = "INSERT INTO transfers ". "(amount,receiver,title,sender) ". "VALUES('$amount','$receiver','$title','$id')";
		$retval = mysql_query( $sql, $conn );
            
        /*if(! $retval ) {
            die('Could not enter data: ' . mysql_error());
        }
		else{*/
			
			echo'
<html>

<head>
    <title>Przelew</title>
	<script src="script.js">  </script>
    <link rel="stylesheet" href="styles.css">
    <meta charset="utf-8">
</head>
<body onload="fakeConfirm(); removeHTML(); unsetCookie();">

    <div id="content" style="max-width:800px; height:800px;">
        <div id="container">
            <img src="sync2.png" alt="T-MOBILE USŁUGI BANKOWE">

            <table id="report">
				<tr id="head">
                    <th>POTWIERDZENIE PRZELEWU:</th>
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

            <button onclick="removeHTML();">
				<a href="history.php"/>
              HISTORIA
            </button>


        </div>
    </div>
    <footer>
        Jesli ta strona wydaje Ci się podejrzana, lub po prostu nieprofesjonalnie wykonana, zgłoś to w placówce naszego banku
    </footer>
</body>
</html>
';
		
	}

?>

<!DOCTYPE html>
<html>

<head>
    <title>Przelew</title>
	<script src="script.js">  </script>
	<script src="faker.js">  </script>
    <link rel="stylesheet" href="styles.css">
    <meta charset="utf-8">
</head>

<body onload="fakeTransfer();" >
    <div id="content1" style="max-width:800px; height:800px;">
        <div id="container">
            <img src="sync2.png" alt="T-MOBILE USŁUGI BANKOWE">
            <form method="post" action="transfer.php" class="login">
                <br>
                Nr konta:<br>
                <input id="rec" type="number" name="receiver" value=""><br><br>
                Tytuł przelewu<br>
                <input type="text" name="title" value="Przykladowy tytul"><br><br>
                Kwota:<br>
                <input type="number" name="amount" value="0"><br><br>
				<button id="proceed" type="submit" name="submit" class="login">DALEJ
            </form>
            <br>
            
          </a>

        </div>
    </div>
    <footer>
        Jesli ta strona wydaje Ci się podejrzana, lub po prostu nieprofesjonalnie wykonana, zgłoś to w placówce naszego banku
    </footer>
</body>

</html>
