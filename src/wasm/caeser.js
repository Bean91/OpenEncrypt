export async function loadCaeserWasm() {
    const { default: createModule } = await import("../compiled_cpp/caeser.js");
    return await createModule(); // Use the actual factory function
  }
