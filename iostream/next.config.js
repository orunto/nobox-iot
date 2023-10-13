/** @type {import('next').NextConfig} */
const nextConfig = {
    // ...
    env: {
        // declare here all your variables
        BASE_URL: process.env.BASE_URL,
    }
}

module.exports = nextConfig
