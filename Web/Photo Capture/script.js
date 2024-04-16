const video = document.getElementById('video');
const toggleButton = document.getElementById('toggleButton');
const captureButton = document.getElementById('captureButton');
const imageGallery = document.getElementById('imageGallery');

let isCameraOn = false;

async function setupCamera() {
  try {
    const stream = await navigator.mediaDevices.getUserMedia({ video: true });
    video.srcObject = stream;
    return new Promise(resolve => {
      video.onloadedmetadata = () => {
        resolve(video);
      };
    });
  } catch (error) {
    console.error('Error accessing the webcam:', error);
  }
}

async function toggleCamera() {
  if (isCameraOn) {
    video.srcObject.getTracks().forEach(track => track.stop());
    video.srcObject = null;
    toggleButton.textContent = 'Turn Camera On';
    captureButton.disabled = true;
    isCameraOn = false;
  } else {
    const videoElement = await setupCamera();
    videoElement.play();
    toggleButton.textContent = 'Turn Camera Off';
    captureButton.disabled = false;
    isCameraOn = true;
  }
}

async function capturePhoto() {
  const canvas = document.createElement('canvas');
  canvas.width = video.videoWidth;
  canvas.height = video.videoHeight;
  const context = canvas.getContext('2d');

  // Flip the image horizontally
  context.translate(canvas.width, 0);
  context.scale(-1, 1);

  context.drawImage(video, 0, 0, canvas.width, canvas.height);

  const dataURL = canvas.toDataURL('image/jpeg');
  const imageElement = document.createElement('img');
  imageElement.src = dataURL;

  const downloadButton = document.createElement('a');
  downloadButton.textContent = 'Download';
  downloadButton.href = dataURL;
  downloadButton.download = 'webcam-photo.jpeg';

  const imageContainer = document.createElement('div');
  imageContainer.classList.add('image-container');
  imageContainer.appendChild(imageElement);
  imageContainer.appendChild(downloadButton);

  imageGallery.appendChild(imageContainer);
}

toggleButton.addEventListener('click', toggleCamera);

captureButton.addEventListener('click', () => {
  capturePhoto();
});
