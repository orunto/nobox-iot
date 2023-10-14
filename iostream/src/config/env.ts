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