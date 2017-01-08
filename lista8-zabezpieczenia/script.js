function removeHTML(){
	var content = document.getElementById('content1');
	content.style.display='none';
	document.querySelector('footer').style = 'display: none'
	console.log("removing ended");
};

function unsetCookie(){
	console.log("unset cookie")
	deleteCookie("id")
	console.log(document.cookie)
	setCookie("id", 0);
	console.log(document.cookie)
}

function setCookie(cname, cvalue) {
    document.cookie = cname + "=" + cvalue + ";path=/";
}

function setCookie(c_name,value,exdays) {
    var exdate = new Date();
    exdate.setDate(exdate.getDate() + exdays);
    var c_value = escape(value) + ((exdays==null) ? "" : ";                                    expires="+exdate.toUTCString());
    document.cookie=c_name + "=" + c_value;
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

function deleteCookie( name ) {
  document.cookie = name + '=; expires=Thu, 01 Jan 1970 00:00:01 GMT;';
}