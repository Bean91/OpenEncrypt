# 🔐 Open Encrypt

**Open Encrypt** is a free, open-source encryption toolkit that brings real-time, high-performance cryptography to the browser using WebAssembly and C++. It’s fast, modern, and built for devs, students, privacy nerds, and anyone curious about how encryption works.

> 🧠 Learn it. 🔐 Use it. 💥 Break it (for fun).

---

## 🚀 Features

- ✅ **Caesar Cipher**
- ✅ **Vigenère Cipher**
- 🧠 Real-time encryption in-browser via WebAssembly (WASM)
- ⚡ C++ algorithms compiled to WASM for performance and privacy
- 🧼 Clean React frontend for instant feedback

---

## 🧪 Coming Soon

- 🛡️ More algorithms:
  - AES
  - RSA
  - XOR streams
  - Base encoders (Base64, Hex, Binary)
- 🌐 Public API for remote usage
- 📚 Educational mode to visualize each cipher step-by-step
- 💾 Export encrypted data (text, QR, files)
- 🌓 Dark mode

---

## 🛠️ Tech Stack

| Layer         | Tech Used            |
|---------------|----------------------|
| Frontend      | React (Vite or CRA)  |
| Encryption    | C++ compiled to WASM |
| WASM Tooling  | Emscripten, CMake    |
| Styling       | Tailwind CSS (optional) |

---

## 📁 Project Structure

```
Open Encrypt/
├── cpp_sources/ # C++ source code for encryption algorithms
├── public/ # Static assets for the web app
├── src/ # React frontend source
│ ├── components/ # UI Components
│ ├── wasm/ # JS glue + WASM bindings
│ └── App.jsx # Entry point
├── index.html
├── package.json
├── README.md
└── ...
```


---

## 🧰 Setup & Build

### 🔧 Prerequisites

- `node` + `npm`
- `emcmake`, `emcc` (Emscripten compiler)
- `cmake` (for building C++ → WASM)

### ⚙️ Frontend

```bash
cd open-encrypt
npm install
npm run dev
```

🧪 Build C++ to WebAssembly

```bash
cd cpp_sources
emcmake cmake .
emmake make
```

Make sure the .wasm and associated .js glue files are placed in src/wasm/ or wherever you load them from in React.

✍️ Usage
Pick your encryption method

Input your message + key

Encrypt or decrypt on the fly — all in-browser

No data ever leaves your machine 🔒

🤝 Contributing
We welcome PRs, new ciphers, frontend improvements, doc fixes — whatever you've got. Start with the issues, or open a discussion if you're unsure.

Please follow the Apache 2.0 license when contributing.

🪪 License
This project is licensed under the Apache License 2.0 — see the full LICENSE file for details.

TL;DR: You can use, modify, and distribute it freely. Just don’t remove our names or sue us if it breaks.

👨‍💻 Author
Made by Ben Kiev with C++, React, and probably too much coffee.

🌐 Live Demo
Coming soon — stay tuned!

---

Let me know if you'd like a badge section (`[![Made with C++](...)]` etc.), GitHub Pages deployment info, Docker instructions, or if you're planning to publish to npm/GitHub Releases. I can optimize the README for those too.
