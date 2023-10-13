import type { Metadata } from 'next'
import { Inter } from 'next/font/google'

import '../styles/globals.css';
import '../styles/utility.css';

const inter = Inter({ subsets: ['latin'] })

export const metadata: Metadata = {
  title: 'IOStream',
  description: 'Real-time monitoring service with IoT and Nobox Cloud service',
}

export default function RootLayout({
  children,
}: {
  children: React.ReactNode
}) {
  return (
    <html lang="en">
      {/* <SEO/> */}
      <body className={inter.className}>{children}</body>
    </html>
  )
}
