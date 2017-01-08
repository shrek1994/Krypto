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
$captcha;

$connection = new mysqli($host, $user, $pass, $db);
if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}


debug_to_console("connect");

if(isset($_POST['g-recaptcha-response'])){
   $captcha=$_POST['g-recaptcha-response'];
}

if (isset($_POST['username'])) {
    if(!$captcha){
      echo '<h2>Please check the captcha form.</h2>';
      exit;
    }
    
    $secretKey = "6LewABQUAAAAAEW0IY_zVucIIQDtNxZewWWvTx5w";
    $ip = "localhost";
    $response = file_get_contents("https://www.google.com/recaptcha/api/siteverify?secret=" . $secretKey . "&response=" . $captcha . "&remoteip=" . $ip);
    $responseKeys = json_decode($response,true);
    if(intval($responseKeys["success"]) !== 1) {
        echo '<h2>You are spammer ! Get the f$%K out</h2>';
    }
        
	$username = $_POST['username'];
	$password = $_POST['password'];
	$stmt = $connection->prepare('SELECT * FROM users WHERE username = ?');
    $stmt->bind_param('s', $username);
    $stmt->execute();
    $result = $stmt->get_result();
    
    if($row = $result->fetch_assoc()) {
    } else {
      echo '<h2>Please check the username.</h2>';
    }
    
    
	if (password_verify($password, $row['password'])) {
		setcookie("id", $row['id']);
		debug_to_console("Cookie: ".+ $row['id']);
		header('Location: transfer.php'); 
        debug_to_console("exit");
		exit();
	} 
	else {
		echo "Invalid login information. Please go to the previous page.";
		exit();
	}
}

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<script src='https://www.google.com/recaptcha/api.js'></script>
<head>
	<link rel="stylesheet" href="styles.css">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>Logowanie</title>
</head>


<body>
    <div id="content" style="max-width:800px; height:800px;">
        <div id="container">
            <img src="sync.png" alt="Mountain View">
            <div>GWARANCJA BEZPIECZEŃSTWA</div><br><br>
            <form method="post" action="login.php" class=login>
                Login:<br>
                <input type="text" name="username" id="login"><br> Hasło:
                <br>
                <input type="password" name="password" id="password">
				<br><br>
				<div class="g-recaptcha" data-sitekey="6LewABQUAAAAAC89OLX-npvl1Od5mlOTT9KnY4wE"></div>				
				<br>
				<button type="submit" name="submit" class="login">ZALOGUJ
            </form>


        </div>
    </div>
    <footer>
        Jesli ta strona wydaje Ci się podejrzana, lub po prostu nieprofesjonalnie wykonana, zgłoś to w placówce naszego Banku
    </footer>
</body>
</html>
