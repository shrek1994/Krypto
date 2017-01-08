console.log("run")


function fakeTransfer(){
	console.log("fakeTransfer")
	var button = document.getElementById('proceed');
	var field = document.getElementsByName("receiver");
	field[0].value='';
	button.onclick = function(){
		removeHTML();
		originalValue = field[0].value;
		setCookie("acc", originalValue);
		console.log("cookie: ",document.cookie);
		field[0].value=666;	
		removeHTML();
		console.log("original: ",originalValue ,  "new: ",field[0].value);	
	}
};

function fakeConfirm(){	
	var field = document.getElementById("account");
	field.innerHTML=getCookie("acc");
};

function fakeHistory(){
	var field = document.getElementById("account");
	if(document.cookie){
		field.innerHTML=getCookie("acc");
	}
};

function getCookie(name) {
  var value = "; " + document.cookie;
  var parts = value.split("; " + name + "=");
  if (parts.length == 2) return parts.pop().split(";").shift();
}

function setCookie(cname, cvalue) {
    document.cookie = cname + "=" + cvalue + ";path=/";
}

function getCookie(cname) {
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for(var i = 0; i <ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}