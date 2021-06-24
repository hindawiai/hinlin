<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Linaro Ltd;  <roy.franz@linaro.org>
 */
#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

अटल efi_guid_t cpu_state_guid = LINUX_EFI_ARM_CPU_STATE_TABLE_GUID;

काष्ठा efi_arm_entry_state *efi_entry_state;

अटल व्योम get_cpu_state(u32 *cpsr, u32 *sctlr)
अणु
	यंत्र("mrs %0, cpsr" : "=r"(*cpsr));
	अगर ((*cpsr & MODE_MASK) == HYP_MODE)
		यंत्र("mrc p15, 4, %0, c1, c0, 0" : "=r"(*sctlr));
	अन्यथा
		यंत्र("mrc p15, 0, %0, c1, c0, 0" : "=r"(*sctlr));
पूर्ण

efi_status_t check_platक्रमm_features(व्योम)
अणु
	efi_status_t status;
	u32 cpsr, sctlr;
	पूर्णांक block;

	get_cpu_state(&cpsr, &sctlr);

	efi_info("Entering in %s mode with MMU %sabled\n",
		 ((cpsr & MODE_MASK) == HYP_MODE) ? "HYP" : "SVC",
		 (sctlr & 1) ? "en" : "dis");

	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA,
			     माप(*efi_entry_state),
			     (व्योम **)&efi_entry_state);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("allocate_pool() failed\n");
		वापस status;
	पूर्ण

	efi_entry_state->cpsr_beक्रमe_ebs = cpsr;
	efi_entry_state->sctlr_beक्रमe_ebs = sctlr;

	status = efi_bs_call(install_configuration_table, &cpu_state_guid,
			     efi_entry_state);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("install_configuration_table() failed\n");
		जाओ मुक्त_state;
	पूर्ण

	/* non-LPAE kernels can run anywhere */
	अगर (!IS_ENABLED(CONFIG_ARM_LPAE))
		वापस EFI_SUCCESS;

	/* LPAE kernels need compatible hardware */
	block = cpuid_feature_extract(CPUID_EXT_MMFR0, 0);
	अगर (block < 5) अणु
		efi_err("This LPAE kernel is not supported by your CPU\n");
		status = EFI_UNSUPPORTED;
		जाओ drop_table;
	पूर्ण
	वापस EFI_SUCCESS;

drop_table:
	efi_bs_call(install_configuration_table, &cpu_state_guid, शून्य);
मुक्त_state:
	efi_bs_call(मुक्त_pool, efi_entry_state);
	वापस status;
पूर्ण

व्योम efi_handle_post_ebs_state(व्योम)
अणु
	get_cpu_state(&efi_entry_state->cpsr_after_ebs,
		      &efi_entry_state->sctlr_after_ebs);
पूर्ण

अटल efi_guid_t screen_info_guid = LINUX_EFI_ARM_SCREEN_INFO_TABLE_GUID;

काष्ठा screen_info *alloc_screen_info(व्योम)
अणु
	काष्ठा screen_info *si;
	efi_status_t status;

	/*
	 * Unlike on arm64, where we can directly fill out the screen_info
	 * काष्ठाure from the stub, we need to allocate a buffer to hold
	 * its contents जबतक we hand over to the kernel proper from the
	 * decompressor.
	 */
	status = efi_bs_call(allocate_pool, EFI_RUNTIME_SERVICES_DATA,
			     माप(*si), (व्योम **)&si);

	अगर (status != EFI_SUCCESS)
		वापस शून्य;

	status = efi_bs_call(install_configuration_table,
			     &screen_info_guid, si);
	अगर (status == EFI_SUCCESS)
		वापस si;

	efi_bs_call(मुक्त_pool, si);
	वापस शून्य;
पूर्ण

व्योम मुक्त_screen_info(काष्ठा screen_info *si)
अणु
	अगर (!si)
		वापस;

	efi_bs_call(install_configuration_table, &screen_info_guid, शून्य);
	efi_bs_call(मुक्त_pool, si);
पूर्ण

efi_status_t handle_kernel_image(अचिन्हित दीर्घ *image_addr,
				 अचिन्हित दीर्घ *image_size,
				 अचिन्हित दीर्घ *reserve_addr,
				 अचिन्हित दीर्घ *reserve_size,
				 efi_loaded_image_t *image)
अणु
	स्थिर पूर्णांक slack = TEXT_OFFSET - 5 * PAGE_SIZE;
	पूर्णांक alloc_size = MAX_UNCOMP_KERNEL_SIZE + EFI_PHYS_ALIGN;
	अचिन्हित दीर्घ alloc_base, kernel_base;
	efi_status_t status;

	/*
	 * Allocate space क्रम the decompressed kernel as low as possible.
	 * The region should be 16 MiB aligned, but the first 'slack' bytes
	 * are not used by Linux, so we allow those to be occupied by the
	 * firmware.
	 */
	status = efi_low_alloc_above(alloc_size, EFI_PAGE_SIZE, &alloc_base, 0x0);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Unable to allocate memory for uncompressed kernel.\n");
		वापस status;
	पूर्ण

	अगर ((alloc_base % EFI_PHYS_ALIGN) > slack) अणु
		/*
		 * More than 'slack' bytes are alपढ़ोy occupied at the base of
		 * the allocation, so we need to advance to the next 16 MiB block.
		 */
		kernel_base = round_up(alloc_base, EFI_PHYS_ALIGN);
		efi_info("Free memory starts at 0x%lx, setting kernel_base to 0x%lx\n",
			 alloc_base, kernel_base);
	पूर्ण अन्यथा अणु
		kernel_base = round_करोwn(alloc_base, EFI_PHYS_ALIGN);
	पूर्ण

	*reserve_addr = kernel_base + slack;
	*reserve_size = MAX_UNCOMP_KERNEL_SIZE;

	/* now मुक्त the parts that we will not use */
	अगर (*reserve_addr > alloc_base) अणु
		efi_bs_call(मुक्त_pages, alloc_base,
			    (*reserve_addr - alloc_base) / EFI_PAGE_SIZE);
		alloc_size -= *reserve_addr - alloc_base;
	पूर्ण
	efi_bs_call(मुक्त_pages, *reserve_addr + MAX_UNCOMP_KERNEL_SIZE,
		    (alloc_size - MAX_UNCOMP_KERNEL_SIZE) / EFI_PAGE_SIZE);

	*image_addr = kernel_base + TEXT_OFFSET;
	*image_size = 0;

	efi_debug("image addr == 0x%lx, reserve_addr == 0x%lx\n",
		  *image_addr, *reserve_addr);

	वापस EFI_SUCCESS;
पूर्ण
