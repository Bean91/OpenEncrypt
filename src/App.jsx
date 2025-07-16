import CodeCard from "./CodeCard.jsx";

function App() {
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
          console.log("Encode with key:", key, "msg:", message);
        }}
      />
      <CodeCard
        name="Caeser Shift"
        type="caeser"
        onEncode={({ key, message }) => {
          console.log("Encode with key:", key, "msg:", message);
        }}
      />
      <CodeCard
        name="Affine Cipher"
        type="affine"
        onEncode={({ key, message }) => {
          console.log("Encode with key:", key, "msg:", message);
        }}
      />
      <CodeCard
        name="Substitution Cipher"
        type="substitution"
        onEncode={({ key, message }) => {
          console.log("Encode with key:", key, "msg:", message);
        }}
      />
    </div>
  )
}

export default App
