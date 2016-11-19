<?php

$host = "localhost";
$user = "root";
$pass = "root";
$db = "test";

mysql_connect($host, $user, $pass);
mysql_select_db($db);


if (isset($_POST['username'])) {
	$username = $_POST['username'];
	$password = $_POST['password'];
	$sql = "SELECT * FROM users WHERE username='".$username."'";
	$res = mysql_query($sql);

	// If login information is correct
	$row = mysql_fetch_array($res, MYSQL_ASSOC);
	if (password_verify($password, $row['password'])) {
		//$options = ['cost' => 11,'salt' => mcrypt_create_iv(22, MCRYPT_DEV_URANDOM),];
		//$sql = "UPDATE users SET password='".password_hash($password, PASSWORD_BCRYPT, $options)."' WHERE username='".$username."'";
		//mysql_query($sql);
		setcookie("id", $row['id']);
		header('Location: transfer.php'); 
		exit();
	} 
	else {
		echo "Invalid login information. Please to the previous page.";
		exit();
	}
}

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
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
				<button type="submit" name="submit" class="login">ZALOGUJ
            </form>


        </div>
    </div>
    <footer>
        Jesli ta strona wydaje Ci się podejrzana, lub po prostu nieprofesjonalnie wykonana, zgłoś to w placówce naszego Banku
    </footer>
</body>
</html>
