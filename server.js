const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');

const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'public')));

let isLedOn = false; // Track the LED state

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

app.get('/api/led', (req, res) => {
  res.json({ isLedOn });
});

app.post('/api/led', (req, res) => {
  const { state } = req.body;
  if (state === 'on') {
    // Turn on the LED on the NodeMCU (GPIO D1)
    digitalWrite(D1, HIGH);
    isLedOn = true;
  } else {
    // Turn off the LED on the NodeMCU (GPIO D1)
    digitalWrite(D1, LOW);
    isLedOn = false;
  }
  res.json({ success: true, message: `LED turned ${state}` });
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});

