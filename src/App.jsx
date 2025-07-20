import React, {useState, useEffect} from "react";
import CodeCard from "./CodeCard.jsx";
import { loadVigenereWasm } from "./wasm/vigenere.js";
import { loadCaeserWasm } from "./wasm/caeser.js";
import { loadAffineWasm } from "./wasm/affine.js";
import { loadSubstsitutionWasm } from "./wasm/substitution.js";
import { loadPlayfairWasm } from "./wasm/playfair.js";

function App() {
  const [vigenereModule, setVigenereModule] = useState(null);
  const [caeserModule, setCaeserModule] = useState(null);
  const [affineModule, setAffineModule] = useState(null);
  const [substitutionModule, setSubstitutionModule] = useState(null);
  const [playfairModule, setPlayfairModule] = useState(null);

  useEffect(() => {
    loadVigenereWasm().then(setVigenereModule);
    loadCaeserWasm().then(setCaeserModule);
    loadAffineWasm().then(setAffineModule);
    loadSubstsitutionWasm().then(setSubstitutionModule);
    loadPlayfairWasm().then(setPlayfairModule);
  }, []);

  if (!vigenereModule || !caeserModule || !affineModule || !substitutionModule) return <p className="text-white p-4">Loading WASM...</p>;

  function TailwindBreakpointDebugger() {
    return (
      <div className="fixed bottom-2 right-2 text-white bg-black px-2 py-1 rounded z-50 text-sm">
        <div className="sm:hidden md:hidden lg:hidden xl:hidden 2xl:hidden">xs</div>
        <div className="hidden sm:block md:hidden lg:hidden xl:hidden 2xl:hidden">sm</div>
        <div className="hidden md:block lg:hidden xl:hidden 2xl:hidden">md</div>
        <div className="hidden lg:block xl:hidden 2xl:hidden">lg</div>
        <div className="hidden xl:block 2xl:hidden">xl</div>
        <div className="hidden 2xl:block">2xl</div>
      </div>
    );
  }

  return (
    <div className="flex justify-center flex-wrap items-center h-screen">
      {/*<TailwindBreakpointDebugger />*/}
      <CodeCard
        name="Vigenère Cipher"
        type="vigenere"
        onEncode={({ key, message }) => {
          return vigenereModule.ccall(
            "encode",
            "string",
            ["string", "string"],
            [key, message]
          );
        }}
        onDecode={({ key, message }) => {
          return vigenereModule.ccall(
            "decode",
            "string",
            ["string", "string"],
            [key, message]
          );
        }}
      />
      <CodeCard
        name="Caesar Shift"
        type="caesar"
        onEncode={({ key, message }) => {
          return caeserModule.ccall(
            "encode",
            "string",
            ["number", "string"],
            [key.charCodeAt(0), message]
          );
        }}
        onDecode={({ key, message }) => {
          return caeserModule.ccall(
            "decode",
            "string",
            ["number", "string"],
            [key.charCodeAt(0), message]
          );
        }}
      />
      <CodeCard
        name="Affine Cipher"
        type="affine"
        onEncode={({ key, message }) => {
          const a = Number(key.a);
          const b = Number(key.b);
          if (!affineModule) return "";
          return affineModule.ccall(
            "encode",
            "string",
            ["number", "number", "string"],
            [a, b, message]
          );
        }}
        onDecode={({ key, message }) => {
          const a = Number(key.a);
          const b = Number(key.b);
          if (!affineModule) return "";
          return affineModule.ccall(
            "decode",
            "string",
            ["number", "number", "string"],
            [a, b, message]
          );
        }}
      />

      <CodeCard
        name="Substitution Cipher"
        type="substitution"
        onEncode={({ key, message }) => {
          if (!substitutionModule) return "";
          return substitutionModule.ccall(
            "encode",
            "string",
            ["string", "string"],
            [key, message]
          );
        }}
        onDecode={({ key, message }) => {
          if (!substitutionModule) return "";
          return substitutionModule.ccall(
            "decode",
            "string",
            ["string", "string"],
            [key, message]
          );
        }}
      />
      <CodeCard
        name="Playfair Cipher"
        type="playfair"
        onEncode={({ key, message }) => {
          if (!playfairModule) return "";
          return playfairModule.ccall(
            "encode",
            "string",
            ["string", "string"],
            [key, message]
          );
        }}
        onDecode={({ key, message }) => {
          if (!playfairModule) return "";
          return playfairModule.ccall(
            "decode",
            "string",
            ["string", "string"],
            [key, message]
          );
        }}
      />
    </div>
  )
}

export default App
