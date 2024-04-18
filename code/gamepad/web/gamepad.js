const haveEvents = "ongamepadconnected" in window;

const controllers = {};

// Remember last values to send POST requests on change only
const lastVal = {};
const lastPressed = {};
const lastAxis = {};

// Dead zone from which we consider the axis value relevant to send
const AXIS_DEADZONE = 0.5;
const EPSILON = 0.1;

function connecthandler(e) {
  console.log("Gamepad connected: " + e.gamepad.id);
  addgamepad(e.gamepad);
}

function addgamepad(gamepad) {
  controllers[gamepad.index] = gamepad; 
  requestAnimationFrame(updateStatus);
}

function disconnecthandler(e) {
  console.log("Gamepad disconnected: " + e.gamepad.id);
  removegamepad(e.gamepad);
}

function removegamepad(gamepad) {
  delete controllers[gamepad.index];
}

async function postData(url, data) {
  console.log("POST DATA " + JSON.stringify(data));
  const response = await fetch(url, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(data),
  });
  return response;
}

function createButtonsData(buttons) {
  const buttonsData = []

  buttons.forEach((button, i) => {
    const buttonData = {}
    let val = button;
    let pressed = val === 1.0;

    if (typeof button === "object") {
      val = button.value;
      pressed = button.pressed || val > EPSILON;
    }

    if (lastVal[i] == null)
      lastVal[i] = 0;
    if (lastVal[i] != val) {
      buttonData["id"] = i;
      buttonData["val"] = val;
      lastVal[i] = val;
    }

    if (lastPressed[i] == null)
      lastPressed[i] = false;
    if (lastPressed[i] != pressed) {
      buttonData["id"] = i;
      buttonData["pressed"] = pressed;
      lastPressed[i] = pressed;
    }

    if (Object.keys(buttonData).length > 0)
      buttonsData.push(buttonData);
  });

  return buttonsData;
}

function createAxesData(axes) {
  const axesData = []

  axes.forEach((axis, i) => {
    if (Math.abs(axis) < EPSILON || Math.abs(axis) > AXIS_DEADZONE) {
      if (lastAxis[i] == null)
        lastAxis[i] = 0;
      if ((axis == 0 && lastAxis[i] != 0) || Math.abs(lastAxis[i] - axis) > EPSILON) {
        const axisData = { id: i, val: axis }
        axesData.push(axisData);
        lastAxis[i] = axis;
      }
    }
  });

  return axesData;
}

function createControllersData(controllers) {
  const controllersData = []

  Object.entries(controllers).forEach(([i, controller]) => {
    const controllerData = {};

    const buttonsData = createButtonsData(controller.buttons);
    if (buttonsData.length > 0) {
      controllerData["id"] = i;
      controllerData["buttons"] = buttonsData;
    }

    const axesData = createAxesData(controller.axes);
    if (axesData.length > 0) {
      controllerData["id"] = i;
      controllerData["axes"] = axesData;
    }

    if (Object.keys(controllerData).length > 0)
      controllersData.push(controllerData);
  });

  return controllersData;
}

function updateStatus() {
  scangamepads();

  const url = `http://${document.getElementById('ip-input').value}/data`;

  const controllersData = createControllersData(controllers)
  if (controllersData.length > 0)
    postData(url, {controllers: controllersData });

  requestAnimationFrame(updateStatus);
}

function scangamepads() {
  const gamepads = navigator.getGamepads();

  for (const gamepad of gamepads) {
    if (gamepad) {
      // Can be null if disconnected during the session
      if (gamepad.index in controllers) {
        controllers[gamepad.index] = gamepad;
      } else {
        addgamepad(gamepad);
      }
    }
  }
}

window.addEventListener("gamepadconnected", connecthandler);
window.addEventListener("gamepaddisconnected", disconnecthandler);

if (!haveEvents) {
  setInterval(scangamepads, 500);
}