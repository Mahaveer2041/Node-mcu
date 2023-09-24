const express = require("express");
const app = express();
const port = 3000;

const fetch = require("node-fetch");

app.use(express.json());

// Define the IP address of your NodeMCU (replace with the actual IP)
 // Replace with your NodeMCU's IP

app.get("/on", (req, res) => {
  // Send an HTTP GET request to NodeMCU to turn the LED on
  fetch(`http://${"172.17.7.89"}/ledon`)
    .then(response => response.text())
    .then(data => {
      console.log(data);
      res.send("LED is ON");
    })
    .catch(error => {
      console.error(error);
      res.status(500).send("Error turning on LED");
    });
});

app.get("/off", (req, res) => {
  // Send an HTTP GET request to NodeMCU to turn the LED off
  fetch(`http://${"172.17.7.89"}/ledoff`)
    .then(response => response.text())
    .then(data => {
      console.log(data);
      res.send("LED is OFF");
    })
    .catch(error => {
      console.error(error);
      res.status(500).send("Error turning off LED");
    });
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
