const WebSocket = require('ws');

// const wss = new WebSocket.Server({ port: 8080, host: '0.0.0.0' });
// const wss = new WebSocket.Server({ port: 8080, host: '10.1.1.18' });
// const wss = new WebSocket.Server({ port: 3000, host: '10.1.1.18' });
const PORT = 5000;
// const wss = new WebSocket.Server({ port: PORT });
// const wss = new WebSocket.Server({ port: PORT, host: '0.0.0.0' });
const wss = new WebSocket.Server({ port: PORT, host: '10.1.1.18' });

wss.on('connection', (ws) => {
    console.log('Client connected');

    ws.on('message', (message) => {
        console.log('Received:', message);

        // Broadcast the message to all clients
        wss.clients.forEach((client) => {
            if (client !== ws && client.readyState === WebSocket.OPEN) {
                client.send(message);
            }
        });
    });

    ws.on('close', () => {
        console.log('Client disconnected');
    });

    ws.on('error', (error) => {
        console.error('WebSocket error:', error);
    });
});

console.log('WebSocket server is running on ws://localhost:' + PORT);
