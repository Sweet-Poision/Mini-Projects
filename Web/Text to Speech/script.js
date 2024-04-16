const startButton = document.getElementById('startButton');
const stopButton = document.getElementById('stopButton');
const transcription = document.getElementById('transcription');
const volumeCanvas = document.getElementById('volumeCanvas');
const canvasContext = volumeCanvas.getContext('2d');
const volumeArray = [];

let recognition = new (window.SpeechRecognition || window.webkitSpeechRecognition)();

recognition.interimResults = true;
recognition.continuous = true;

recognition.onstart = () => {
    startButton.style.display = 'none';
    stopButton.style.display = 'inline-block';
};

recognition.onend = () => {
    startButton.style.display = 'inline-block';
    stopButton.style.display = 'none';
};

recognition.onresult = event => {
    const finalTranscript = event.results[event.results.length - 1][0].transcript;
    transcription.innerHTML = finalTranscript;

    const volume = calculateVolume(finalTranscript);
    volumeArray.push(volume);
};

function calculateVolume(transcript) {
    return transcript.length * 5; // Example volume calculation
}

function animateVolume() {
    canvasContext.clearRect(0, 0, volumeCanvas.width, volumeCanvas.height);
    canvasContext.fillStyle = '#4caf50';

    for (let i = 0; i < volumeArray.length; i++) {
        const barHeight = volumeArray[i];
        const x = i * 10;
        const y = volumeCanvas.height - barHeight;

        canvasContext.fillRect(x, y, 8, barHeight);
    }

    requestAnimationFrame(animateVolume);
}

startButton.addEventListener('click', () => {
    recognition.start();
    animateVolume();
});

stopButton.addEventListener('click', () => {
    recognition.stop();
});
