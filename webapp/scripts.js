// Auto-refresh the images every 5 seconds to check for updates
setInterval(function() {
    // Select the image elements
    const aStarImg = document.querySelector('img[alt="A* Path Visualization"]');
    const bellmanFordImg = document.querySelector('img[alt="Bellman-Ford Path Visualization"]');

    // Append a timestamp to the image source to force the browser to reload it
    aStarImg.src = '../matlab_scripts/A* Algorithm Path.png?' + new Date().getTime();
    bellmanFordImg.src = '../matlab_scripts/Bellman-Ford Algorithm Path.png?' + new Date().getTime();
}, 5000);  // Refresh every 5 seconds

// Function to manually refresh the images
function refreshImages() {
    // Select the image elements
    const aStarImg = document.querySelector('img[alt="A* Path Visualization"]');
    const bellmanFordImg = document.querySelector('img[alt="Bellman-Ford Path Visualization"]');

    // Append a timestamp to the image source to force the browser to reload it
    aStarImg.src = '../matlab_scripts/A* Algorithm Path.png?' + new Date().getTime();
    bellmanFordImg.src = '../matlab_scripts/Bellman-Ford Algorithm Path.png?' + new Date().getTime();
}

// Attach the refreshImages function to a button with id "refreshButton"
document.getElementById("refreshButton").addEventListener("click", refreshImages);
