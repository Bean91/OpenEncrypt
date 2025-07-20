import React, { useState } from "react";

export default function CodeCard({ name, type, onEncode, onDecode }) {
  const [key, setKey] = useState(
    type === "affine" ? { a: "", b: "" } : ""
  );
  const [msg, setMsg] = useState("");
  const [answer, setAnswer] = useState("");

  const handleKeyChange = (e) => {
    if (type === "affine") {
      setKey({ ...key, [e.target.name]: e.target.value });
    } else {
      setKey(e.target.value);
    }
    };

    const handleMsgChange = (e) => {
      setMsg(e.target.value);
    };

  const handleEncode = () => {
    const result = onEncode?.({ key, message: msg });
    if (typeof result === "string") {
      setAnswer(result);
    } else if (result instanceof Promise) {
      result.then(setAnswer);
    }
  };

  const handleSwap = () => {
    const temp_msg = msg;
    setMsg(answer);
    setAnswer(temp_msg);
  }

  const handleDecode = () => {
    const result = onDecode?.({ key, message: msg });
    if (typeof result === "string") {
      setAnswer(result);
    } else if (result instanceof Promise) {
      result.then(setAnswer);
    }
  };

    const renderKeyInput = () => {
      switch (type) {
        case "affine":
          return (
            <div className="flex gap-2">
              <input
                name="a"
                type="number"
                value={key.a}
                onChange={handleKeyChange}
                placeholder="a"
                className="w-1/2 p-2 border rounded-md"
              />
              <input
                name="b"
                type="number"
                value={key.b}
                onChange={handleKeyChange}
                placeholder="b"
                className="w-1/2 p-2 border rounded-md"
              />
            </div>
          );
        case "caesar":
          return (
            <input
              type="text"
              maxLength="1"
              pattern="[a-zA-Z]"
              value={key}
              onChange={handleKeyChange}
              placeholder="e.g. C"
              className="w-full p-2 border rounded-md uppercase"
            />
          );
        case "substitution":
          return (
            <input
              type="text"
              value={key}
              onChange={handleKeyChange}
              maxLength="26"
              pattern="[a-zA-Z]"
              placeholder="e.g. QWERTYUIOPASDFGHJKLZXCVBNM"
              className="w-full p-2 border rounded-md uppercase"
            />
          );
        case "vigenere":
          return (
            <input
              type="text"
              value={key}
              onChange={handleKeyChange}
              placeholder="e.g. LEMON"
              className="w-full p-2 border rounded-md uppercase"
            />
          );
        case "playfair":
          return (
            <input
              type="text"
              value={key}
              onChange={handleKeyChange}
              placeholder="e.g. LEMON"
              className="w-full p-2 border rounded-md uppercase"
            />
          );
        default:
          return (
            <input
              type="text"
              value={key}
              onChange={handleKeyChange}
              placeholder="Enter key"
              className="w-full p-2 border rounded-md"
            />
          );
      }
    };

    return (
      <div className="bg-slate-600 shadow-md rounded-2xl p-6 space-y-4 max-w-md inline-block m-2 w-96">
        <h2 className="text-xl font-semibold text-white">{name}</h2>

        {/* Key Input */}
        <div>
          <label className="block text-sm font-medium text-gray-200 mb-1">
            Key:
          </label>
          {renderKeyInput()}
        </div>

        {/* Message Input */}
        <div>
          <label className="block text-sm font-medium text-gray-200 mb-1">
            Message:
          </label>
          <textarea
            value={msg}
            onChange={handleMsgChange}
            placeholder="Enter message..."
            className="w-full p-2 border rounded-md resize-none"
            rows={4}
          />
        </div>

        {/* Submit Button */}
        <div className="flex items-center w-full">
          <button
            onClick={handleEncode}
            disabled={!msg || !key}
            className={`${
              msg ? "bg-blue-600 hover:bg-blue-700" : "bg-gray-400 cursor-not-allowed"
            } text-white px-4 py-2 rounded-lg font-medium mx-auto`}
          >
            Encode
          </button>
          <button
            onClick={handleSwap}
            disabled={!msg || !key}
            className={`${
              msg ? "bg-blue-600 hover:bg-blue-700" : "bg-gray-400 cursor-not-allowed"
            } text-white px-4 py-2 rounded-lg font-medium mx-auto`}
          >
            Swap
          </button>
          <button
            onClick={handleDecode}
            disabled={!msg || !key}
            className={`${
              msg ? "bg-blue-600 hover:bg-blue-700" : "bg-gray-400 cursor-not-allowed"
            } text-white px-4 py-2 rounded-lg font-medium mx-auto`}
          >
            Decode
          </button>
          </div>
        <div>
          <label className="block text-sm font-medium text-gray-200 mb-1">
            Answer:
          </label>
          <textarea
            value={answer}
            readOnly={true}
            placeholder="Returned message..."
            className="w-full p-2 border rounded-md resize-none"
            rows={4}
          />
        </div>
      </div>
    );
  }
