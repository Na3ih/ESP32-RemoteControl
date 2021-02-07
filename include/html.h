/** 
 * HTML page for remote control of the ESP32 module GPIO pins.
 * Contains 4 buttons and JavaScript code for keyboard control.
 * It uses the fetch API to send asynchronous queries to web server.
 */

#pragma once
#include <stdio.h>

const char htmlExample[] =
"<!DOCTYPE html> "
"<html lang=\"en\"> "
"<head> " 
"    <meta charset=\"UTF-8\">  " 
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> "
"    <title>ESP32 Remote Control Example</title>  " 
"    <script language=\"JavaScript\">  " 
"        window.onload = load;  "
"        let lastRequestDir = \"STOP\";  " 

"        function load() {  "
"            document.addEventListener(\"keydown\", function onPress(event) {  " 
"                var key = event.keyCode;  " 

"                switch (event.which || event.keyCode) {  " 
"                case 37:  " 
"                    move(\"LEFT\");  " 
"                    break;  " 
"                case 38:  " 
"                    move(\"UP\");  " 
"                    break;  " 
"                case 39:  " 
"                    move(\"RIGHT\");  " 
"                    break;  " 
"                case 40:  " 
"                    move(\"DOWN\");  " 
"                    break;  " 
"                }  " 
"            });  " 

"            document.addEventListener(\"keyup\", function onRelease() { "
"            stop();    "
"            });    "
"        };  " 

"        function move(direction) {  " 
"           if (direction != lastRequestDir) {  "
"               lastRequestDir = direction;  "
"       console.log(direction); "
"               switch (direction) {  " 
"               case \"UP\":  " 
"                 fetch(`http://my-esp32.local/forward`);  "
"                 break;  "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
"               case \"DOWN\":  " 
"                 fetch(`http://my-esp32.local/backward`);  " 
"                 break;  " 
"               case \"LEFT\":  " 
"                 fetch(`http://my-esp32.local/left`);  " 
"                 break;  " 
"               case \"RIGHT\":  " 
"                 fetch(`http://my-esp32.local/right`);  " 
"                 break;  " 
"               default:  " 
"                 stop();   " 
"                 break;  " 

"               }  "     
"           }  "
"        };  " 

"       function stop() {   "
"                lastRequestDir = \"STOP\"; "
"            fetch(`http://my-esp32.local/stop`);  " 
"       }; "
"    </script>  "
"</head>  " 
"<body>  " 
"   <button onmousedown='move(\"UP\")' onmouseup='stop()'>UP</button>  " 
"   <button onmousedown='move(\"DOWN\")' onmouseup='stop()'>DOWN</button>  " 
"   <button onmousedown='move(\"LEFT\")' onmouseup='stop()'>LEFT</button>  " 
"   <button onmousedown='move(\"RIGHT\")' onmouseup='stop()'>RIGHT</button>  " 
"</body>  " 
"</html> ";