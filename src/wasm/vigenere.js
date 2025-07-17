export async function loadVigenereWasm() {
  const { default: createModule } = await import("../compiled_cpp/vigenere.js");
  return await createModule(); // Use the actual factory function
}
