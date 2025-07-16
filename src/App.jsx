

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
    <>
      {/*<TailwindBreakpointDebugger />*/}
    </>j
  )
}

export default App
