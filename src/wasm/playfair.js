export async function loadPlayfairWasm() {
  const { default: createModule } = await import("../compiled_cpp/playfair.js");
  return await createModule(); // Use the actual factory function
}
