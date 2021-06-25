<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013, 2014 Linaro Ltd;  <roy.franz@linaro.org>
 *
 * This file implements the EFI boot stub क्रम the arm64 kernel.
 * Adapted from ARM version by Mark Salter <msalter@redhat.com>
 */


#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/sysreg.h>

#समावेश "efistub.h"

efi_status_t check_platक्रमm_features(व्योम)
अणु
	u64 tg;

	/* UEFI mandates support क्रम 4 KB granularity, no need to check */
	अगर (IS_ENABLED(CONFIG_ARM64_4K_PAGES))
		वापस EFI_SUCCESS;

	tg = (पढ़ो_cpuid(ID_AA64MMFR0_EL1) >> ID_AA64MMFR0_TGRAN_SHIFT) & 0xf;
	अगर (tg < ID_AA64MMFR0_TGRAN_SUPPORTED_MIN || tg > ID_AA64MMFR0_TGRAN_SUPPORTED_MAX) अणु
		अगर (IS_ENABLED(CONFIG_ARM64_64K_PAGES))
			efi_err("This 64 KB granular kernel is not supported by your CPU\n");
		अन्यथा
			efi_err("This 16 KB granular kernel is not supported by your CPU\n");
		वापस EFI_UNSUPPORTED;
	पूर्ण
	वापस EFI_SUCCESS;
पूर्ण

/*
 * Although relocatable kernels can fix up the misalignment with respect to
 * MIN_KIMG_ALIGN, the resulting भव text addresses are subtly out of
 * sync with those recorded in the vmlinux when kaslr is disabled but the
 * image required relocation anyway. Thereक्रमe retain 2M alignment unless
 * KASLR is in use.
 */
अटल u64 min_kimg_align(व्योम)
अणु
	वापस efi_nokaslr ? MIN_KIMG_ALIGN : EFI_KIMG_ALIGN;
पूर्ण

efi_status_t handle_kernel_image(अचिन्हित दीर्घ *image_addr,
				 अचिन्हित दीर्घ *image_size,
				 अचिन्हित दीर्घ *reserve_addr,
				 अचिन्हित दीर्घ *reserve_size,
				 efi_loaded_image_t *image)
अणु
	efi_status_t status;
	अचिन्हित दीर्घ kernel_size, kernel_memsize = 0;
	u32 phys_seed = 0;

	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE)) अणु
		अगर (!efi_nokaslr) अणु
			status = efi_get_अक्रमom_bytes(माप(phys_seed),
						      (u8 *)&phys_seed);
			अगर (status == EFI_NOT_FOUND) अणु
				efi_info("EFI_RNG_PROTOCOL unavailable\n");
				efi_nokaslr = true;
			पूर्ण अन्यथा अगर (status != EFI_SUCCESS) अणु
				efi_err("efi_get_random_bytes() failed (0x%lx)\n",
					status);
				efi_nokaslr = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			efi_info("KASLR disabled on kernel command line\n");
		पूर्ण
	पूर्ण

	अगर (image->image_base != _text)
		efi_err("FIRMWARE BUG: efi_loaded_image_t::image_base has bogus value\n");

	kernel_size = _edata - _text;
	kernel_memsize = kernel_size + (_end - _edata);
	*reserve_size = kernel_memsize;

	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE) && phys_seed != 0) अणु
		/*
		 * If KASLR is enabled, and we have some अक्रमomness available,
		 * locate the kernel at a अक्रमomized offset in physical memory.
		 */
		status = efi_अक्रमom_alloc(*reserve_size, min_kimg_align(),
					  reserve_addr, phys_seed);
	पूर्ण अन्यथा अणु
		status = EFI_OUT_OF_RESOURCES;
	पूर्ण

	अगर (status != EFI_SUCCESS) अणु
		अगर (IS_ALIGNED((u64)_text, min_kimg_align())) अणु
			/*
			 * Just execute from wherever we were loaded by the
			 * UEFI PE/COFF loader अगर the alignment is suitable.
			 */
			*image_addr = (u64)_text;
			*reserve_size = 0;
			वापस EFI_SUCCESS;
		पूर्ण

		status = efi_allocate_pages_aligned(*reserve_size, reserve_addr,
						    अच_दीर्घ_उच्च, min_kimg_align());

		अगर (status != EFI_SUCCESS) अणु
			efi_err("Failed to relocate kernel\n");
			*reserve_size = 0;
			वापस status;
		पूर्ण
	पूर्ण

	*image_addr = *reserve_addr;
	स_नकल((व्योम *)*image_addr, _text, kernel_size);

	वापस EFI_SUCCESS;
पूर्ण
