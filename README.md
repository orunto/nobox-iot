# iostream with Nobox

## Overview
A realtime monitoring web application for IoT using Nobox backend-as-a-service.

## Features
This current version allows your web capable microcontroller to send data to the cloud service and the web app picks up that nigh instantaneously.

## How to get started
You'll need to have git and the latest LTS version of NodeJs.

You'll also need a package manager, either npm or yarn.

Once you have that set up, run the following commands to clone the repo and install the necessary dependencies

```bash
git clone git@github.com:orunto/nobox-iot.git

# After cloning is complete
cd iostream

npm install
```

Create an account at [`Nobox`](https://nobox.cloud) to start using the service for your project
### The iostream web app
Place the auth token you get into this file in its appropriate variable
```typescript
// Read environment varibales
// const env = process.env;
const env = {
    NEXT_PUBLIC_NOBOX_API_URL: "https://api.nobox.cloud",
    NEXT_PUBLIC_PROJECT: "iostream",
    // Place your auth token here
    NEXT_PUBLIC_NOBOX_AUTH_TOKEN: "here"
}

const apiUrl = env.NEXT_PUBLIC_NOBOX_API_URL || "https://api.nobox.cloud";
const project = env.NEXT_PUBLIC_PROJECT || "iostream"
const authToken = env.NEXT_PUBLIC_NOBOX_AUTH_TOKEN;

if (!authToken) console.log("Authentication Token is required in .env file");


export {
    apiUrl,
    project,
    authToken
}
```

### The board server
Make sure you have the ESP8266 wifi board installed on your IDE

If you haven't you can find a step-by-step guide on how to do so [`here`](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)

Place that same auth token in this file in its appropriate variable
```C
// Place your auth token here
client.println("const token = \"here\"");
```

## Contributions
This project intends to make good use of all the services Nobox offers and all the available features development boards have to offer, on this note, contribution to this project are welcome. Here's a list of features I hope to implement in future versions of the project:

<ul>
    <li>User Login</li>
    <li>Board instructions straight from the web app</li>
    <li>Webhook communication for instantaneous feedback</li>
</ul>

To contribute to this project, reach out to me [`here`](https://github.com/orunto/nobox-iot/discussions/new?category=ideas) to discuss your ideas to implement any item on the features wishlist or if you have an idea for a feature that's not on the list.


## Discussions
If you have questions, any questions actually, please feel free to ask in the [`Q&A discussion section`](https://github.com/orunto/nobox-iot/discussions/new?category=q-a)