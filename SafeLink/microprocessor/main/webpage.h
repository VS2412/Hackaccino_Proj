#ifndef WEBPAGE_H
#define WEBPAGE_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 LoRa API</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #e5ddd5;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .chat-container {
            width: 400px;
            height: 600px;
            background-color: #ffffff;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            display: flex;
            flex-direction: column;
        }

        .header {
            background-color: #075e54;
            color: white;
            padding: 15px;
            border-top-left-radius: 10px;
            border-top-right-radius: 10px;
            text-align: center;
        }

        .message-log {
            flex-grow: 1;
            padding: 10px;
            overflow-y: auto;
            background-color: #ece5dd;
        }

        .message {
            margin: 5px 0;
            padding: 10px;
            border-radius: 10px;
            max-width: 70%;
            word-wrap: break-word;
        }

        .message.sent {
            background-color: #dcf8c6;
            align-self: flex-end;
        }

        .message.received {
            background-color: #ffffff;
            align-self: flex-start;
        }

        .input-container {
            display: flex;
            padding: 10px;
            background-color: #f0f0f0;
            border-bottom-left-radius: 10px;
            border-bottom-right-radius: 10px;
        }

        .input-container input {
            flex-grow: 1;
            padding: 10px;
            border-radius: 20px;
            border: 1px solid #ccc;
            outline: none;
        }

        .input-container button {
            margin-left: 10px;
            padding: 10px;
            border: none;
            border-radius: 50%;
            background-color: #075e54;
            color: white;
            cursor: pointer;
        }

        .status {
            text-align: center;
            color: #666;
            font-size: 12px;
            margin-top: 5px;
        }

        .username-container {
            display: flex;
            padding: 10px;
            background-color: #f0f0f0;
            border-bottom: 1px solid #ccc;
        }

        .username-container input {
            flex-grow: 1;
            padding: 8px;
            border-radius: 20px;
            border: 1px solid #ccc;
            outline: none;
        }

        .username-container button {
            margin-left: 10px;
            padding: 8px;
            border: none;
            border-radius: 20px;
            background-color: #075e54;
            color: white;
            cursor: pointer;
        }
    </style>
</head>

<body>
    <div class="chat-container">
        <div class="header">
            ESP32 LoRa Chat
        </div>

        <div class="username-container">
            <input type="text" id="usernameInput" placeholder="Enter username">
            <button onclick="setUsername()">Set</button>
        </div>

        <div class="message-log" id="messageLog">
            <p class="status">Waiting for messages...</p>
        </div>

        <div class="input-container">
            <input type="text" id="messageInput" placeholder="Type a message">
            <button onclick="sendMessage()">➤</button>
        </div>
    </div>

    <script>
        let username = "", lastMsgTimestamp=null;

        function setUsername() {
            username = document.getElementById("usernameInput").value;
            if (!username) {
                alert("Please enter a username!");
                return;
            }

            fetch(`/setuser`, {
                method: "POST",
                headers: { "Content-Type": "application/x-www-form-urlencoded" },
                body: `username=${username}`
            })
                .then(response => response.json())
                .then(data => alert(data.status))
                .catch(error => console.error("Error:", error));
        }

        function sendMessage() {
            let message = document.getElementById("messageInput").value;
            if (!message) {
                alert("Please enter a message!");
                return;
            }

            fetch(`/send`, {
                method: "POST",
                headers: { "Content-Type": "application/x-www-form-urlencoded" },
                body: `message=${message}`
            })
                .then(response => response.json())
                .then(data => {
                    addMessage("sent", `${username}: ${message}`);
                    document.getElementById("messageInput").value = "";
                })
                .catch(error => console.error("Error:", error));
        }

        function fetchLoRaMessages() {
            fetch(`/loradata`)
                .then(response => response.json())
                .then(data => {
                    if (data.message) {
                        if(data.timestamp!=lastMsgTimestamp){
                            addMessage("received", `${data.message}`);
                            lastMsgTimestamp=data.timestamp;
                        }
                    }
                })
                .catch(error => console.error("Error fetching messages:", error));
        }

        function addMessage(type, text) {
            let messageLog = document.getElementById("messageLog");
            let messageElement = document.createElement("div");
            messageElement.className = `message ${type}`;
            messageElement.innerText = text;
            messageLog.appendChild(messageElement);
            messageLog.scrollTop = messageLog.scrollHeight;
        }

        setInterval(fetchLoRaMessages, 3000); // Fetch messages every 3 seconds
    </script>
</body>

</html>
)rawliteral";

#endif
