export async function loadSubstsitutionWasm() {
    const { default: createModule } = await import("../compiled_cpp/substitution.js");
    return await createModule(); // Use the actual factory function
  }
