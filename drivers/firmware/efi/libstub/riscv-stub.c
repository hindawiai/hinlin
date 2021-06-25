<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/efi.h>
#समावेश <linux/libfdt.h>

#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/sections.h>

#समावेश "efistub.h"

/*
 * RISC-V requires the kernel image to placed 2 MB aligned base क्रम 64 bit and
 * 4MB क्रम 32 bit.
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा MIN_KIMG_ALIGN		SZ_2M
#अन्यथा
#घोषणा MIN_KIMG_ALIGN		SZ_4M
#पूर्ण_अगर

प्रकार व्योम __noवापस (*jump_kernel_func)(अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

अटल u32 hartid;

अटल u32 get_boot_hartid_from_fdt(व्योम)
अणु
	स्थिर व्योम *fdt;
	पूर्णांक chosen_node, len;
	स्थिर fdt32_t *prop;

	fdt = get_efi_config_table(DEVICE_TREE_GUID);
	अगर (!fdt)
		वापस U32_MAX;

	chosen_node = fdt_path_offset(fdt, "/chosen");
	अगर (chosen_node < 0)
		वापस U32_MAX;

	prop = fdt_getprop((व्योम *)fdt, chosen_node, "boot-hartid", &len);
	अगर (!prop || len != माप(u32))
		वापस U32_MAX;

	वापस fdt32_to_cpu(*prop);
पूर्ण

efi_status_t check_platक्रमm_features(व्योम)
अणु
	hartid = get_boot_hartid_from_fdt();
	अगर (hartid == U32_MAX) अणु
		efi_err("/chosen/boot-hartid missing or invalid!\n");
		वापस EFI_UNSUPPORTED;
	पूर्ण
	वापस EFI_SUCCESS;
पूर्ण

व्योम __noवापस efi_enter_kernel(अचिन्हित दीर्घ entrypoपूर्णांक, अचिन्हित दीर्घ fdt,
				 अचिन्हित दीर्घ fdt_size)
अणु
	अचिन्हित दीर्घ stext_offset = _start_kernel - _start;
	अचिन्हित दीर्घ kernel_entry = entrypoपूर्णांक + stext_offset;
	jump_kernel_func jump_kernel = (jump_kernel_func)kernel_entry;

	/*
	 * Jump to real kernel here with following स्थिरraपूर्णांकs.
	 * 1. MMU should be disabled.
	 * 2. a0 should contain hartid
	 * 3. a1 should DT address
	 */
	csr_ग_लिखो(CSR_SATP, 0);
	jump_kernel(hartid, fdt);
पूर्ण

efi_status_t handle_kernel_image(अचिन्हित दीर्घ *image_addr,
				 अचिन्हित दीर्घ *image_size,
				 अचिन्हित दीर्घ *reserve_addr,
				 अचिन्हित दीर्घ *reserve_size,
				 efi_loaded_image_t *image)
अणु
	अचिन्हित दीर्घ kernel_size = 0;
	अचिन्हित दीर्घ preferred_addr;
	efi_status_t status;

	kernel_size = _edata - _start;
	*image_addr = (अचिन्हित दीर्घ)_start;
	*image_size = kernel_size + (_end - _edata);

	/*
	 * RISC-V kernel maps PAGE_OFFSET भव address to the same physical
	 * address where kernel is booted. That's why kernel should boot from
	 * as low as possible to aव्योम wastage of memory. Currently, dram_base
	 * is occupied by the firmware. So the preferred address क्रम kernel to
	 * boot is next aligned address. If preferred address is not available,
	 * relocate_kernel will fall back to efi_low_alloc_above to allocate
	 * lowest possible memory region as दीर्घ as the address and size meets
	 * the alignment स्थिरraपूर्णांकs.
	 */
	preferred_addr = MIN_KIMG_ALIGN;
	status = efi_relocate_kernel(image_addr, kernel_size, *image_size,
				     preferred_addr, MIN_KIMG_ALIGN, 0x0);

	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to relocate kernel\n");
		*image_size = 0;
	पूर्ण
	वापस status;
पूर्ण
