export async function loadAffineWasm() {
    const { default: createModule } = await import("../compiled_cpp/affine.js");
    return await createModule(); // Use the actual factory function
  }
