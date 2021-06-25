<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/parisc/kernel/firmware.c  - safe PDC access routines
 *
 *	PDC == Processor Dependent Code
 *
 * See PDC करोcumentation at
 * https://parisc.wiki.kernel.org/index.php/Technical_Documentation
 * क्रम करोcumentation describing the entry poपूर्णांकs and calling
 * conventions defined below.
 *
 * Copyright 1999 SuSE GmbH Nuernberg (Philipp Rumpf, prumpf@tux.org)
 * Copyright 1999 The Puffin Group, (Alex deVries, David Kennedy)
 * Copyright 2003 Grant Grundler <grundler parisc-linux org>
 * Copyright 2003,2004 Ryan Bradetich <rbrad@parisc-linux.org>
 * Copyright 2004,2006 Thibaut VARENE <varenet@parisc-linux.org>
 */

/*	I think it would be in everyone's best पूर्णांकerest to follow this
 *	guidelines when writing PDC wrappers:
 *
 *	 - the name of the pdc wrapper should match one of the macros
 *	   used क्रम the first two arguments
 *	 - करोn't use caps क्रम अक्रमom parts of the name
 *	 - use the अटल PDC result buffers and "copyout" to काष्ठाs
 *	   supplied by the caller to encapsulate alignment restrictions
 *	 - hold pdc_lock जबतक in PDC or using अटल result buffers
 *	 - use __pa() to convert भव (kernel) poपूर्णांकers to physical
 *	   ones.
 *	 - the name of the काष्ठा used क्रम pdc वापस values should equal
 *	   one of the macros used क्रम the first two arguments to the
 *	   corresponding PDC call
 *	 - keep the order of arguments
 *	 - करोn't be smart (setting trailing NUL bytes क्रम strings, वापस
 *	   something useful even अगर the call failed) unless you are sure
 *	   it's not going to affect functionality or perक्रमmance
 *
 *	Example:
 *	पूर्णांक pdc_cache_info(काष्ठा pdc_cache_info *cache_info )
 *	अणु
 *		पूर्णांक retval;
 *
 *		spin_lock_irq(&pdc_lock);
 *		retval = mem_pdc_call(PDC_CACHE,PDC_CACHE_INFO,__pa(cache_info),0);
 *		convert_to_wide(pdc_result);
 *		स_नकल(cache_info, pdc_result, माप(*cache_info));
 *		spin_unlock_irq(&pdc_lock);
 *
 *		वापस retval;
 *	पूर्ण
 *					prumpf	991016	
 */

#समावेश <मानकतर्क.स>

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/pdcpat.h>
#समावेश <यंत्र/processor.h>	/* क्रम boot_cpu_data */

#अगर defined(BOOTLOADER)
# undef  spin_lock_irqsave
# define spin_lock_irqsave(a, b) अणु b = 1; पूर्ण
# undef  spin_unlock_irqrestore
# define spin_unlock_irqrestore(a, b)
#अन्यथा
अटल DEFINE_SPINLOCK(pdc_lock);
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ pdc_result[NUM_PDC_RESULT];
बाह्य अचिन्हित दीर्घ pdc_result2[NUM_PDC_RESULT];

#अगर_घोषित CONFIG_64BIT
#घोषणा WIDE_FIRMWARE 0x1
#घोषणा NARROW_FIRMWARE 0x2

/* Firmware needs to be initially set to narrow to determine the 
 * actual firmware width. */
पूर्णांक parisc_narrow_firmware __ro_after_init = 1;
#पूर्ण_अगर

/* On most currently-supported platक्रमms, IODC I/O calls are 32-bit calls
 * and MEM_PDC calls are always the same width as the OS.
 * Some PAT boxes may have 64-bit IODC I/O.
 *
 * Ryan Bradetich added the now obsolete CONFIG_PDC_NARROW to allow
 * 64-bit kernels to run on प्रणालीs with 32-bit MEM_PDC calls.
 * This allowed wide kernels to run on Cxxx boxes.
 * We now detect 32-bit-only PDC and dynamically चयन to 32-bit mode
 * when running a 64-bit kernel on such boxes (e.g. C200 or C360).
 */

#अगर_घोषित CONFIG_64BIT
दीर्घ real64_call(अचिन्हित दीर्घ function, ...);
#पूर्ण_अगर
दीर्घ real32_call(अचिन्हित दीर्घ function, ...);

#अगर_घोषित CONFIG_64BIT
#   define MEM_PDC (अचिन्हित दीर्घ)(PAGE0->mem_pdc_hi) << 32 | PAGE0->mem_pdc
#   define mem_pdc_call(args...) unlikely(parisc_narrow_firmware) ? real32_call(MEM_PDC, args) : real64_call(MEM_PDC, args)
#अन्यथा
#   define MEM_PDC (अचिन्हित दीर्घ)PAGE0->mem_pdc
#   define mem_pdc_call(args...) real32_call(MEM_PDC, args)
#पूर्ण_अगर


/**
 * f_extend - Convert PDC addresses to kernel addresses.
 * @address: Address वापसed from PDC.
 *
 * This function is used to convert PDC addresses पूर्णांकo kernel addresses
 * when the PDC address size and kernel address size are dअगरferent.
 */
अटल अचिन्हित दीर्घ f_extend(अचिन्हित दीर्घ address)
अणु
#अगर_घोषित CONFIG_64BIT
	अगर(unlikely(parisc_narrow_firmware)) अणु
		अगर((address & 0xff000000) == 0xf0000000)
			वापस 0xf0f0f0f000000000UL | (u32)address;

		अगर((address & 0xf0000000) == 0xf0000000)
			वापस 0xffffffff00000000UL | (u32)address;
	पूर्ण
#पूर्ण_अगर
	वापस address;
पूर्ण

/**
 * convert_to_wide - Convert the वापस buffer addresses पूर्णांकo kernel addresses.
 * @address: The वापस buffer from PDC.
 *
 * This function is used to convert the वापस buffer addresses retrieved from PDC
 * पूर्णांकo kernel addresses when the PDC address size and kernel address size are
 * dअगरferent.
 */
अटल व्योम convert_to_wide(अचिन्हित दीर्घ *addr)
अणु
#अगर_घोषित CONFIG_64BIT
	पूर्णांक i;
	अचिन्हित पूर्णांक *p = (अचिन्हित पूर्णांक *)addr;

	अगर (unlikely(parisc_narrow_firmware)) अणु
		क्रम (i = (NUM_PDC_RESULT-1); i >= 0; --i)
			addr[i] = p[i];
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_64BIT
व्योम set_firmware_width_unlocked(व्योम)
अणु
	पूर्णांक ret;

	ret = mem_pdc_call(PDC_MODEL, PDC_MODEL_CAPABILITIES,
		__pa(pdc_result), 0);
	convert_to_wide(pdc_result);
	अगर (pdc_result[0] != NARROW_FIRMWARE)
		parisc_narrow_firmware = 0;
पूर्ण
	
/**
 * set_firmware_width - Determine अगर the firmware is wide or narrow.
 * 
 * This function must be called beक्रमe any pdc_* function that uses the
 * convert_to_wide function.
 */
व्योम set_firmware_width(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&pdc_lock, flags);
	set_firmware_width_unlocked();
	spin_unlock_irqrestore(&pdc_lock, flags);
पूर्ण
#अन्यथा
व्योम set_firmware_width_unlocked(व्योम)
अणु
	वापस;
पूर्ण

व्योम set_firmware_width(व्योम)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /*CONFIG_64BIT*/


#अगर !defined(BOOTLOADER)
/**
 * pdc_emergency_unlock - Unlock the linux pdc lock
 *
 * This call unlocks the linux pdc lock in हाल we need some PDC functions
 * (like pdc_add_valid) during kernel stack dump.
 */
व्योम pdc_emergency_unlock(व्योम)
अणु
 	/* Spinlock DEBUG code freaks out अगर we unconditionally unlock */
        अगर (spin_is_locked(&pdc_lock))
		spin_unlock(&pdc_lock);
पूर्ण


/**
 * pdc_add_valid - Verअगरy address can be accessed without causing a HPMC.
 * @address: Address to be verअगरied.
 *
 * This PDC call attempts to पढ़ो from the specअगरied address and verअगरies
 * अगर the address is valid.
 * 
 * The वापस value is PDC_OK (0) in हाल accessing this address is valid.
 */
पूर्णांक pdc_add_valid(अचिन्हित दीर्घ address)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_ADD_VALID, PDC_ADD_VALID_VERIFY, address);
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_add_valid);

/**
 * pdc_instr - Get inकाष्ठाion that invokes PDCE_CHECK in HPMC handler.
 * @instr: Poपूर्णांकer to variable which will get inकाष्ठाion opcode.
 *
 * The वापस value is PDC_OK (0) in हाल call succeeded.
 */
पूर्णांक __init pdc_instr(अचिन्हित पूर्णांक *instr)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_INSTR, 0UL, __pa(pdc_result));
	convert_to_wide(pdc_result);
	*instr = pdc_result[0];
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_chassis_info - Return chassis inक्रमmation.
 * @result: The वापस buffer.
 * @chassis_info: The memory buffer address.
 * @len: The size of the memory buffer address.
 *
 * An HVERSION dependent call क्रम वापसing the chassis inक्रमmation.
 */
पूर्णांक __init pdc_chassis_info(काष्ठा pdc_chassis_info *chassis_info, व्योम *led_info, अचिन्हित दीर्घ len)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        स_नकल(&pdc_result, chassis_info, माप(*chassis_info));
        स_नकल(&pdc_result2, led_info, len);
        retval = mem_pdc_call(PDC_CHASSIS, PDC_RETURN_CHASSIS_INFO,
                              __pa(pdc_result), __pa(pdc_result2), len);
        स_नकल(chassis_info, pdc_result, माप(*chassis_info));
        स_नकल(led_info, pdc_result2, len);
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण

/**
 * pdc_pat_chassis_send_log - Sends a PDC PAT CHASSIS log message.
 * @retval: -1 on error, 0 on success. Other value are PDC errors
 * 
 * Must be correctly क्रमmatted or expect प्रणाली crash
 */
#अगर_घोषित CONFIG_64BIT
पूर्णांक pdc_pat_chassis_send_log(अचिन्हित दीर्घ state, अचिन्हित दीर्घ data)
अणु
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;
        
	अगर (!is_pdc_pat())
		वापस -1;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_CHASSIS_LOG, PDC_PAT_CHASSIS_WRITE_LOG, __pa(&state), __pa(&data));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण
#पूर्ण_अगर

/**
 * pdc_chassis_disp - Updates chassis code
 * @retval: -1 on error, 0 on success
 */
पूर्णांक pdc_chassis_disp(अचिन्हित दीर्घ disp)
अणु
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_CHASSIS, PDC_CHASSIS_DISP, disp);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_cpu_rendenzvous - Stop currently executing CPU
 * @retval: -1 on error, 0 on success
 */
पूर्णांक __pdc_cpu_rendezvous(व्योम)
अणु
	अगर (is_pdc_pat())
		वापस mem_pdc_call(PDC_PAT_CPU, PDC_PAT_CPU_RENDEZVOUS);
	अन्यथा
		वापस mem_pdc_call(PDC_PROC, 1, 0);
पूर्ण


/**
 * pdc_chassis_warn - Fetches chassis warnings
 * @retval: -1 on error, 0 on success
 */
पूर्णांक pdc_chassis_warn(अचिन्हित दीर्घ *warn)
अणु
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_CHASSIS, PDC_CHASSIS_WARN, __pa(pdc_result));
	*warn = pdc_result[0];
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

पूर्णांक pdc_coproc_cfg_unlocked(काष्ठा pdc_coproc_cfg *pdc_coproc_info)
अणु
	पूर्णांक ret;

	ret = mem_pdc_call(PDC_COPROC, PDC_COPROC_CFG, __pa(pdc_result));
	convert_to_wide(pdc_result);
	pdc_coproc_info->ccr_functional = pdc_result[0];
	pdc_coproc_info->ccr_present = pdc_result[1];
	pdc_coproc_info->revision = pdc_result[17];
	pdc_coproc_info->model = pdc_result[18];

	वापस ret;
पूर्ण

/**
 * pdc_coproc_cfg - To identअगरy coprocessors attached to the processor.
 * @pdc_coproc_info: Return buffer address.
 *
 * This PDC call वापसs the presence and status of all the coprocessors
 * attached to the processor.
 */
पूर्णांक pdc_coproc_cfg(काष्ठा pdc_coproc_cfg *pdc_coproc_info)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	ret = pdc_coproc_cfg_unlocked(pdc_coproc_info);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस ret;
पूर्ण

/**
 * pdc_iodc_पढ़ो - Read data from the modules IODC.
 * @actcnt: The actual number of bytes.
 * @hpa: The HPA of the module क्रम the iodc पढ़ो.
 * @index: The iodc entry poपूर्णांक.
 * @iodc_data: A buffer memory क्रम the iodc options.
 * @iodc_data_size: Size of the memory buffer.
 *
 * This PDC call पढ़ोs from the IODC of the module specअगरied by the hpa
 * argument.
 */
पूर्णांक pdc_iodc_पढ़ो(अचिन्हित दीर्घ *actcnt, अचिन्हित दीर्घ hpa, अचिन्हित पूर्णांक index,
		  व्योम *iodc_data, अचिन्हित पूर्णांक iodc_data_size)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_IODC, PDC_IODC_READ, __pa(pdc_result), hpa, 
			      index, __pa(pdc_result2), iodc_data_size);
	convert_to_wide(pdc_result);
	*actcnt = pdc_result[0];
	स_नकल(iodc_data, pdc_result2, iodc_data_size);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_iodc_पढ़ो);

/**
 * pdc_प्रणाली_map_find_mods - Locate unarchitected modules.
 * @pdc_mod_info: Return buffer address.
 * @mod_path: poपूर्णांकer to dev path काष्ठाure.
 * @mod_index: fixed address module index.
 *
 * To locate and identअगरy modules which reside at fixed I/O addresses, which
 * करो not self-identअगरy via architected bus walks.
 */
पूर्णांक pdc_प्रणाली_map_find_mods(काष्ठा pdc_प्रणाली_map_mod_info *pdc_mod_info,
			     काष्ठा pdc_module_path *mod_path, दीर्घ mod_index)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_SYSTEM_MAP, PDC_FIND_MODULE, __pa(pdc_result), 
			      __pa(pdc_result2), mod_index);
	convert_to_wide(pdc_result);
	स_नकल(pdc_mod_info, pdc_result, माप(*pdc_mod_info));
	स_नकल(mod_path, pdc_result2, माप(*mod_path));
	spin_unlock_irqrestore(&pdc_lock, flags);

	pdc_mod_info->mod_addr = f_extend(pdc_mod_info->mod_addr);
	वापस retval;
पूर्ण

/**
 * pdc_प्रणाली_map_find_addrs - Retrieve additional address ranges.
 * @pdc_addr_info: Return buffer address.
 * @mod_index: Fixed address module index.
 * @addr_index: Address range index.
 * 
 * Retrieve additional inक्रमmation about subsequent address ranges क्रम modules
 * with multiple address ranges.  
 */
पूर्णांक pdc_प्रणाली_map_find_addrs(काष्ठा pdc_प्रणाली_map_addr_info *pdc_addr_info, 
			      दीर्घ mod_index, दीर्घ addr_index)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_SYSTEM_MAP, PDC_FIND_ADDRESS, __pa(pdc_result),
			      mod_index, addr_index);
	convert_to_wide(pdc_result);
	स_नकल(pdc_addr_info, pdc_result, माप(*pdc_addr_info));
	spin_unlock_irqrestore(&pdc_lock, flags);

	pdc_addr_info->mod_addr = f_extend(pdc_addr_info->mod_addr);
	वापस retval;
पूर्ण

/**
 * pdc_model_info - Return model inक्रमmation about the processor.
 * @model: The वापस buffer.
 *
 * Returns the version numbers, identअगरiers, and capabilities from the processor module.
 */
पूर्णांक pdc_model_info(काष्ठा pdc_model *model) 
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_MODEL, PDC_MODEL_INFO, __pa(pdc_result), 0);
	convert_to_wide(pdc_result);
	स_नकल(model, pdc_result, माप(*model));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_model_sysmodel - Get the प्रणाली model name.
 * @name: A अक्षर array of at least 81 अक्षरacters.
 *
 * Get प्रणाली model name from PDC ROM (e.g. 9000/715 or 9000/778/B160L).
 * Using OS_ID_HPUX will वापस the equivalent of the 'modelname' command
 * on HP/UX.
 */
पूर्णांक pdc_model_sysmodel(अक्षर *name)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_MODEL, PDC_MODEL_SYSMODEL, __pa(pdc_result),
                              OS_ID_HPUX, __pa(name));
        convert_to_wide(pdc_result);

        अगर (retval == PDC_OK) अणु
                name[pdc_result[0]] = '\0'; /* add trailing '\0' */
        पूर्ण अन्यथा अणु
                name[0] = 0;
        पूर्ण
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण

/**
 * pdc_model_versions - Identअगरy the version number of each processor.
 * @cpu_id: The वापस buffer.
 * @id: The id of the processor to check.
 *
 * Returns the version number क्रम each processor component.
 *
 * This comment was here beक्रमe, but I करो not know what it means :( -RB
 * id: 0 = cpu revision, 1 = boot-rom-version
 */
पूर्णांक pdc_model_versions(अचिन्हित दीर्घ *versions, पूर्णांक id)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_MODEL, PDC_MODEL_VERSIONS, __pa(pdc_result), id);
        convert_to_wide(pdc_result);
        *versions = pdc_result[0];
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण

/**
 * pdc_model_cpuid - Returns the CPU_ID.
 * @cpu_id: The वापस buffer.
 *
 * Returns the CPU_ID value which uniquely identअगरies the cpu portion of
 * the processor module.
 */
पूर्णांक pdc_model_cpuid(अचिन्हित दीर्घ *cpu_id)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        pdc_result[0] = 0; /* preset zero (call may not be implemented!) */
        retval = mem_pdc_call(PDC_MODEL, PDC_MODEL_CPU_ID, __pa(pdc_result), 0);
        convert_to_wide(pdc_result);
        *cpu_id = pdc_result[0];
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण

/**
 * pdc_model_capabilities - Returns the platक्रमm capabilities.
 * @capabilities: The वापस buffer.
 *
 * Returns inक्रमmation about platक्रमm support क्रम 32- and/or 64-bit
 * OSes, IO-Pसूची coherency, and भव aliasing.
 */
पूर्णांक pdc_model_capabilities(अचिन्हित दीर्घ *capabilities)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        pdc_result[0] = 0; /* preset zero (call may not be implemented!) */
        retval = mem_pdc_call(PDC_MODEL, PDC_MODEL_CAPABILITIES, __pa(pdc_result), 0);
        convert_to_wide(pdc_result);
        अगर (retval == PDC_OK) अणु
                *capabilities = pdc_result[0];
        पूर्ण अन्यथा अणु
                *capabilities = PDC_MODEL_OS32;
        पूर्ण
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण

/**
 * pdc_model_platक्रमm_info - Returns machine product and serial number.
 * @orig_prod_num: Return buffer क्रम original product number.
 * @current_prod_num: Return buffer क्रम current product number.
 * @serial_no: Return buffer क्रम serial number.
 *
 * Returns strings containing the original and current product numbers and the
 * serial number of the प्रणाली.
 */
पूर्णांक pdc_model_platक्रमm_info(अक्षर *orig_prod_num, अक्षर *current_prod_num,
		अक्षर *serial_no)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_MODEL, PDC_MODEL_GET_PLATFORM_INFO,
		__pa(orig_prod_num), __pa(current_prod_num), __pa(serial_no));
	convert_to_wide(pdc_result);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_cache_info - Return cache and TLB inक्रमmation.
 * @cache_info: The वापस buffer.
 *
 * Returns inक्रमmation about the processor's cache and TLB.
 */
पूर्णांक pdc_cache_info(काष्ठा pdc_cache_info *cache_info)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_CACHE, PDC_CACHE_INFO, __pa(pdc_result), 0);
        convert_to_wide(pdc_result);
        स_नकल(cache_info, pdc_result, माप(*cache_info));
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण

/**
 * pdc_spaceid_bits - Return whether Space ID hashing is turned on.
 * @space_bits: Should be 0, अगर not, bad mojo!
 *
 * Returns inक्रमmation about Space ID hashing.
 */
पूर्णांक pdc_spaceid_bits(अचिन्हित दीर्घ *space_bits)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	pdc_result[0] = 0;
	retval = mem_pdc_call(PDC_CACHE, PDC_CACHE_RET_SPID, __pa(pdc_result), 0);
	convert_to_wide(pdc_result);
	*space_bits = pdc_result[0];
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

#अगर_अघोषित CONFIG_PA20
/**
 * pdc_btlb_info - Return block TLB inक्रमmation.
 * @btlb: The वापस buffer.
 *
 * Returns inक्रमmation about the hardware Block TLB.
 */
पूर्णांक pdc_btlb_info(काष्ठा pdc_btlb_info *btlb) 
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_BLOCK_TLB, PDC_BTLB_INFO, __pa(pdc_result), 0);
        स_नकल(btlb, pdc_result, माप(*btlb));
        spin_unlock_irqrestore(&pdc_lock, flags);

        अगर(retval < 0) अणु
                btlb->max_size = 0;
        पूर्ण
        वापस retval;
पूर्ण

/**
 * pdc_mem_map_hpa - Find fixed module inक्रमmation.  
 * @address: The वापस buffer
 * @mod_path: poपूर्णांकer to dev path काष्ठाure.
 *
 * This call was developed क्रम S700 workstations to allow the kernel to find
 * the I/O devices (Core I/O). In the future (Kittyhawk and beyond) this
 * call will be replaced (on workstations) by the architected PDC_SYSTEM_MAP
 * call.
 *
 * This call is supported by all existing S700 workstations (up to  Gecko).
 */
पूर्णांक pdc_mem_map_hpa(काष्ठा pdc_memory_map *address,
		काष्ठा pdc_module_path *mod_path)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        स_नकल(pdc_result2, mod_path, माप(*mod_path));
        retval = mem_pdc_call(PDC_MEM_MAP, PDC_MEM_MAP_HPA, __pa(pdc_result),
				__pa(pdc_result2));
        स_नकल(address, pdc_result, माप(*address));
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण
#पूर्ण_अगर	/* !CONFIG_PA20 */

/**
 * pdc_lan_station_id - Get the LAN address.
 * @lan_addr: The वापस buffer.
 * @hpa: The network device HPA.
 *
 * Get the LAN station address when it is not directly available from the LAN hardware.
 */
पूर्णांक pdc_lan_station_id(अक्षर *lan_addr, अचिन्हित दीर्घ hpa)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_LAN_STATION_ID, PDC_LAN_STATION_ID_READ,
			__pa(pdc_result), hpa);
	अगर (retval < 0) अणु
		/* FIXME: अन्यथा पढ़ो MAC from NVRAM */
		स_रखो(lan_addr, 0, PDC_LAN_STATION_ID_SIZE);
	पूर्ण अन्यथा अणु
		स_नकल(lan_addr, pdc_result, PDC_LAN_STATION_ID_SIZE);
	पूर्ण
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_lan_station_id);

/**
 * pdc_stable_पढ़ो - Read data from Stable Storage.
 * @staddr: Stable Storage address to access.
 * @memaddr: The memory address where Stable Storage data shall be copied.
 * @count: number of bytes to transfer. count is multiple of 4.
 *
 * This PDC call पढ़ोs from the Stable Storage address supplied in staddr
 * and copies count bytes to the memory address memaddr.
 * The call will fail अगर staddr+count > PDC_STABLE size.
 */
पूर्णांक pdc_stable_पढ़ो(अचिन्हित दीर्घ staddr, व्योम *memaddr, अचिन्हित दीर्घ count)
अणु
       पूर्णांक retval;
	अचिन्हित दीर्घ flags;

       spin_lock_irqsave(&pdc_lock, flags);
       retval = mem_pdc_call(PDC_STABLE, PDC_STABLE_READ, staddr,
               __pa(pdc_result), count);
       convert_to_wide(pdc_result);
       स_नकल(memaddr, pdc_result, count);
       spin_unlock_irqrestore(&pdc_lock, flags);

       वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_stable_पढ़ो);

/**
 * pdc_stable_ग_लिखो - Write data to Stable Storage.
 * @staddr: Stable Storage address to access.
 * @memaddr: The memory address where Stable Storage data shall be पढ़ो from.
 * @count: number of bytes to transfer. count is multiple of 4.
 *
 * This PDC call पढ़ोs count bytes from the supplied memaddr address,
 * and copies count bytes to the Stable Storage address staddr.
 * The call will fail अगर staddr+count > PDC_STABLE size.
 */
पूर्णांक pdc_stable_ग_लिखो(अचिन्हित दीर्घ staddr, व्योम *memaddr, अचिन्हित दीर्घ count)
अणु
       पूर्णांक retval;
	अचिन्हित दीर्घ flags;

       spin_lock_irqsave(&pdc_lock, flags);
       स_नकल(pdc_result, memaddr, count);
       convert_to_wide(pdc_result);
       retval = mem_pdc_call(PDC_STABLE, PDC_STABLE_WRITE, staddr,
               __pa(pdc_result), count);
       spin_unlock_irqrestore(&pdc_lock, flags);

       वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_stable_ग_लिखो);

/**
 * pdc_stable_get_size - Get Stable Storage size in bytes.
 * @size: poपूर्णांकer where the size will be stored.
 *
 * This PDC call वापसs the number of bytes in the processor's Stable
 * Storage, which is the number of contiguous bytes implemented in Stable
 * Storage starting from staddr=0. size in an अचिन्हित 64-bit पूर्णांकeger
 * which is a multiple of four.
 */
पूर्णांक pdc_stable_get_size(अचिन्हित दीर्घ *size)
अणु
       पूर्णांक retval;
	अचिन्हित दीर्घ flags;

       spin_lock_irqsave(&pdc_lock, flags);
       retval = mem_pdc_call(PDC_STABLE, PDC_STABLE_RETURN_SIZE, __pa(pdc_result));
       *size = pdc_result[0];
       spin_unlock_irqrestore(&pdc_lock, flags);

       वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_stable_get_size);

/**
 * pdc_stable_verअगरy_contents - Checks that Stable Storage contents are valid.
 *
 * This PDC call is meant to be used to check the पूर्णांकegrity of the current
 * contents of Stable Storage.
 */
पूर्णांक pdc_stable_verअगरy_contents(व्योम)
अणु
       पूर्णांक retval;
	अचिन्हित दीर्घ flags;

       spin_lock_irqsave(&pdc_lock, flags);
       retval = mem_pdc_call(PDC_STABLE, PDC_STABLE_VERIFY_CONTENTS);
       spin_unlock_irqrestore(&pdc_lock, flags);

       वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_stable_verअगरy_contents);

/**
 * pdc_stable_initialize - Sets Stable Storage contents to zero and initialize
 * the validity indicator.
 *
 * This PDC call will erase all contents of Stable Storage. Use with care!
 */
पूर्णांक pdc_stable_initialize(व्योम)
अणु
       पूर्णांक retval;
	अचिन्हित दीर्घ flags;

       spin_lock_irqsave(&pdc_lock, flags);
       retval = mem_pdc_call(PDC_STABLE, PDC_STABLE_INITIALIZE);
       spin_unlock_irqrestore(&pdc_lock, flags);

       वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_stable_initialize);

/**
 * pdc_get_initiator - Get the SCSI Interface Card params (SCSI ID, SDTR, SE or LVD)
 * @hwpath: fully bc.mod style path to the device.
 * @initiator: the array to वापस the result पूर्णांकo
 *
 * Get the SCSI operational parameters from PDC.
 * Needed since HPUX never used BIOS or symbios card NVRAM.
 * Most ncr/sym cards won't have an entry and just use whatever
 * capabilities of the card are (eg Ultra, LVD). But there are
 * several हालs where it's useful:
 *    o set SCSI id क्रम Multi-initiator clusters,
 *    o cable too दीर्घ (ie SE scsi 10Mhz won't support 6m length),
 *    o bus width exported is less than what the पूर्णांकerface chip supports.
 */
पूर्णांक pdc_get_initiator(काष्ठा hardware_path *hwpath, काष्ठा pdc_initiator *initiator)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);

/* BCJ-XXXX series boxes. E.G. "9000/785/C3000" */
#घोषणा IS_SPROCKETS() (म_माप(boot_cpu_data.pdc.sys_model_name) == 14 && \
	म_भेदन(boot_cpu_data.pdc.sys_model_name, "9000/785", 8) == 0)

	retval = mem_pdc_call(PDC_INITIATOR, PDC_GET_INITIATOR, 
			      __pa(pdc_result), __pa(hwpath));
	अगर (retval < PDC_OK)
		जाओ out;

	अगर (pdc_result[0] < 16) अणु
		initiator->host_id = pdc_result[0];
	पूर्ण अन्यथा अणु
		initiator->host_id = -1;
	पूर्ण

	/*
	 * Sprockets and Piranha वापस 20 or 40 (MT/s).  Prelude वापसs
	 * 1, 2, 5 or 10 क्रम 5, 10, 20 or 40 MT/s, respectively
	 */
	चयन (pdc_result[1]) अणु
		हाल  1: initiator->factor = 50; अवरोध;
		हाल  2: initiator->factor = 25; अवरोध;
		हाल  5: initiator->factor = 12; अवरोध;
		हाल 25: initiator->factor = 10; अवरोध;
		हाल 20: initiator->factor = 12; अवरोध;
		हाल 40: initiator->factor = 10; अवरोध;
		शेष: initiator->factor = -1; अवरोध;
	पूर्ण

	अगर (IS_SPROCKETS()) अणु
		initiator->width = pdc_result[4];
		initiator->mode = pdc_result[5];
	पूर्ण अन्यथा अणु
		initiator->width = -1;
		initiator->mode = -1;
	पूर्ण

 out:
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस (retval >= PDC_OK);
पूर्ण
EXPORT_SYMBOL(pdc_get_initiator);


/**
 * pdc_pci_irt_size - Get the number of entries in the पूर्णांकerrupt routing table.
 * @num_entries: The वापस value.
 * @hpa: The HPA क्रम the device.
 *
 * This PDC function वापसs the number of entries in the specअगरied cell's
 * पूर्णांकerrupt table.
 * Similar to PDC_PAT stuff - but added क्रम Forte/Allegro boxes
 */ 
पूर्णांक pdc_pci_irt_size(अचिन्हित दीर्घ *num_entries, अचिन्हित दीर्घ hpa)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PCI_INDEX, PDC_PCI_GET_INT_TBL_SIZE, 
			      __pa(pdc_result), hpa);
	convert_to_wide(pdc_result);
	*num_entries = pdc_result[0];
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/** 
 * pdc_pci_irt - Get the PCI पूर्णांकerrupt routing table.
 * @num_entries: The number of entries in the table.
 * @hpa: The Hard Physical Address of the device.
 * @tbl: 
 *
 * Get the PCI पूर्णांकerrupt routing table क्रम the device at the given HPA.
 * Similar to PDC_PAT stuff - but added क्रम Forte/Allegro boxes
 */
पूर्णांक pdc_pci_irt(अचिन्हित दीर्घ num_entries, अचिन्हित दीर्घ hpa, व्योम *tbl)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	BUG_ON((अचिन्हित दीर्घ)tbl & 0x7);

	spin_lock_irqsave(&pdc_lock, flags);
	pdc_result[0] = num_entries;
	retval = mem_pdc_call(PDC_PCI_INDEX, PDC_PCI_GET_INT_TBL, 
			      __pa(pdc_result), hpa, __pa(tbl));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण


#अगर 0	/* UNTEST CODE - left here in हाल someone needs it */

/** 
 * pdc_pci_config_पढ़ो - पढ़ो PCI config space.
 * @hpa		token from PDC to indicate which PCI device
 * @pci_addr	configuration space address to पढ़ो from
 *
 * Read PCI Configuration space *beक्रमe* linux PCI subप्रणाली is running.
 */
अचिन्हित पूर्णांक pdc_pci_config_पढ़ो(व्योम *hpa, अचिन्हित दीर्घ cfg_addr)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	pdc_result[0] = 0;
	pdc_result[1] = 0;
	retval = mem_pdc_call(PDC_PCI_INDEX, PDC_PCI_READ_CONFIG, 
			      __pa(pdc_result), hpa, cfg_addr&~3UL, 4UL);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval ? ~0 : (अचिन्हित पूर्णांक) pdc_result[0];
पूर्ण


/** 
 * pdc_pci_config_ग_लिखो - पढ़ो PCI config space.
 * @hpa		token from PDC to indicate which PCI device
 * @pci_addr	configuration space address to ग_लिखो
 * @val		value we want in the 32-bit रेजिस्टर
 *
 * Write PCI Configuration space *beक्रमe* linux PCI subप्रणाली is running.
 */
व्योम pdc_pci_config_ग_लिखो(व्योम *hpa, अचिन्हित दीर्घ cfg_addr, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	pdc_result[0] = 0;
	retval = mem_pdc_call(PDC_PCI_INDEX, PDC_PCI_WRITE_CONFIG, 
			      __pa(pdc_result), hpa,
			      cfg_addr&~3UL, 4UL, (अचिन्हित दीर्घ) val);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण
#पूर्ण_अगर /* UNTESTED CODE */

/**
 * pdc_tod_पढ़ो - Read the Time-Of-Day घड़ी.
 * @tod: The वापस buffer:
 *
 * Read the Time-Of-Day घड़ी
 */
पूर्णांक pdc_tod_पढ़ो(काष्ठा pdc_tod *tod)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_TOD, PDC_TOD_READ, __pa(pdc_result), 0);
        convert_to_wide(pdc_result);
        स_नकल(tod, pdc_result, माप(*tod));
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_tod_पढ़ो);

पूर्णांक pdc_mem_pdt_info(काष्ठा pdc_mem_retinfo *rinfo)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_MEM, PDC_MEM_MEMINFO, __pa(pdc_result), 0);
	convert_to_wide(pdc_result);
	स_नकल(rinfo, pdc_result, माप(*rinfo));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

पूर्णांक pdc_mem_pdt_पढ़ो_entries(काष्ठा pdc_mem_पढ़ो_pdt *pret,
		अचिन्हित दीर्घ *pdt_entries_ptr)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_MEM, PDC_MEM_READ_PDT, __pa(pdc_result),
			__pa(pdt_entries_ptr));
	अगर (retval == PDC_OK) अणु
		convert_to_wide(pdc_result);
		स_नकल(pret, pdc_result, माप(*pret));
	पूर्ण
	spin_unlock_irqrestore(&pdc_lock, flags);

#अगर_घोषित CONFIG_64BIT
	/*
	 * 64-bit kernels should not call this PDT function in narrow mode.
	 * The pdt_entries_ptr array above will now contain 32-bit values
	 */
	अगर (WARN_ON_ONCE((retval == PDC_OK) && parisc_narrow_firmware))
		वापस PDC_ERROR;
#पूर्ण_अगर

	वापस retval;
पूर्ण

/**
 * pdc_tod_set - Set the Time-Of-Day घड़ी.
 * @sec: The number of seconds since epoch.
 * @usec: The number of micro seconds.
 *
 * Set the Time-Of-Day घड़ी.
 */ 
पूर्णांक pdc_tod_set(अचिन्हित दीर्घ sec, अचिन्हित दीर्घ usec)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_TOD, PDC_TOD_WRITE, sec, usec);
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_tod_set);

#अगर_घोषित CONFIG_64BIT
पूर्णांक pdc_mem_mem_table(काष्ठा pdc_memory_table_raddr *r_addr,
		काष्ठा pdc_memory_table *tbl, अचिन्हित दीर्घ entries)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_MEM, PDC_MEM_TABLE, __pa(pdc_result), __pa(pdc_result2), entries);
	convert_to_wide(pdc_result);
	स_नकल(r_addr, pdc_result, माप(*r_addr));
	स_नकल(tbl, pdc_result2, entries * माप(*tbl));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */

/* FIXME: Is this pdc used?  I could not find type reference to ftc_biपंचांगap
 * so I guessed at अचिन्हित दीर्घ.  Someone who knows what this करोes, can fix
 * it later. :)
 */
पूर्णांक pdc_करो_firm_test_reset(अचिन्हित दीर्घ ftc_biपंचांगap)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_BROADCAST_RESET, PDC_DO_FIRM_TEST_RESET,
                              PDC_FIRM_TEST_MAGIC, ftc_biपंचांगap);
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण

/*
 * pdc_करो_reset - Reset the प्रणाली.
 *
 * Reset the प्रणाली.
 */
पूर्णांक pdc_करो_reset(व्योम)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_BROADCAST_RESET, PDC_DO_RESET);
        spin_unlock_irqrestore(&pdc_lock, flags);

        वापस retval;
पूर्ण

/*
 * pdc_soft_घातer_info - Enable soft घातer चयन.
 * @घातer_reg: address of soft घातer रेजिस्टर
 *
 * Return the असलolute address of the soft घातer चयन रेजिस्टर
 */
पूर्णांक __init pdc_soft_घातer_info(अचिन्हित दीर्घ *घातer_reg)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	*घातer_reg = (अचिन्हित दीर्घ) (-1);
	
	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_SOFT_POWER, PDC_SOFT_POWER_INFO, __pa(pdc_result), 0);
	अगर (retval == PDC_OK) अणु
                convert_to_wide(pdc_result);
                *घातer_reg = f_extend(pdc_result[0]);
	पूर्ण
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/*
 * pdc_soft_घातer_button - Control the soft घातer button behaviour
 * @sw_control: 0 क्रम hardware control, 1 क्रम software control 
 *
 *
 * This PDC function places the soft घातer button under software or
 * hardware control.
 * Under software control the OS may control to when to allow to shut 
 * करोwn the प्रणाली. Under hardware control pressing the घातer button 
 * घातers off the प्रणाली immediately.
 */
पूर्णांक pdc_soft_घातer_button(पूर्णांक sw_control)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_SOFT_POWER, PDC_SOFT_POWER_ENABLE, __pa(pdc_result), sw_control);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/*
 * pdc_io_reset - Hack to aव्योम overlapping range रेजिस्टरs of Bridges devices.
 * Primarily a problem on T600 (which parisc-linux करोesn't support) but
 * who knows what other platक्रमm firmware might करो with this OS "hook".
 */
व्योम pdc_io_reset(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	mem_pdc_call(PDC_IO, PDC_IO_RESET, 0);
	spin_unlock_irqrestore(&pdc_lock, flags);
पूर्ण

/*
 * pdc_io_reset_devices - Hack to Stop USB controller
 *
 * If PDC used the usb controller, the usb controller
 * is still running and will crash the machines during iommu 
 * setup, because of still running DMA. This PDC call
 * stops the USB controller.
 * Normally called after calling pdc_io_reset().
 */
व्योम pdc_io_reset_devices(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	mem_pdc_call(PDC_IO, PDC_IO_RESET_DEVICES, 0);
	spin_unlock_irqrestore(&pdc_lock, flags);
पूर्ण

#पूर्ण_अगर /* defined(BOOTLOADER) */

/* locked by pdc_console_lock */
अटल पूर्णांक __attribute__((aligned(8)))   iodc_retbuf[32];
अटल अक्षर __attribute__((aligned(64))) iodc_dbuf[4096];

/**
 * pdc_iodc_prपूर्णांक - Console prपूर्णांक using IODC.
 * @str: the string to output.
 * @count: length of str
 *
 * Note that only these special अक्षरs are architected क्रम console IODC io:
 * BEL, BS, CR, and LF. Others are passed through.
 * Since the HP console requires CR+LF to perक्रमm a 'newline', we translate
 * "\n" to "\r\n".
 */
पूर्णांक pdc_iodc_prपूर्णांक(स्थिर अचिन्हित अक्षर *str, अचिन्हित count)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < count;) अणु
		चयन(str[i]) अणु
		हाल '\n':
			iodc_dbuf[i+0] = '\r';
			iodc_dbuf[i+1] = '\n';
			i += 2;
			जाओ prपूर्णांक;
		शेष:
			iodc_dbuf[i] = str[i];
			i++;
			अवरोध;
		पूर्ण
	पूर्ण

prपूर्णांक:
        spin_lock_irqsave(&pdc_lock, flags);
        real32_call(PAGE0->mem_cons.iodc_io,
                    (अचिन्हित दीर्घ)PAGE0->mem_cons.hpa, ENTRY_IO_COUT,
                    PAGE0->mem_cons.spa, __pa(PAGE0->mem_cons.dp.layers),
                    __pa(iodc_retbuf), 0, __pa(iodc_dbuf), i, 0);
        spin_unlock_irqrestore(&pdc_lock, flags);

	वापस i;
पूर्ण

#अगर !defined(BOOTLOADER)
/**
 * pdc_iodc_अ_लो - Read a अक्षरacter (non-blocking) from the PDC console.
 *
 * Read a अक्षरacter (non-blocking) from the PDC console, वापसs -1 अगर
 * key is not present.
 */
पूर्णांक pdc_iodc_अ_लो(व्योम)
अणु
	पूर्णांक ch;
	पूर्णांक status;
	अचिन्हित दीर्घ flags;

	/* Bail अगर no console input device. */
	अगर (!PAGE0->mem_kbd.iodc_io)
		वापस 0;
	
	/* रुको क्रम a keyboard (rs232)-input */
	spin_lock_irqsave(&pdc_lock, flags);
	real32_call(PAGE0->mem_kbd.iodc_io,
		    (अचिन्हित दीर्घ)PAGE0->mem_kbd.hpa, ENTRY_IO_CIN,
		    PAGE0->mem_kbd.spa, __pa(PAGE0->mem_kbd.dp.layers), 
		    __pa(iodc_retbuf), 0, __pa(iodc_dbuf), 1, 0);

	ch = *iodc_dbuf;
	status = *iodc_retbuf;
	spin_unlock_irqrestore(&pdc_lock, flags);

	अगर (status == 0)
	    वापस -1;
	
	वापस ch;
पूर्ण

पूर्णांक pdc_sti_call(अचिन्हित दीर्घ func, अचिन्हित दीर्घ flags,
                 अचिन्हित दीर्घ inptr, अचिन्हित दीर्घ outputr,
                 अचिन्हित दीर्घ glob_cfg)
अणु
        पूर्णांक retval;
	अचिन्हित दीर्घ irqflags;

        spin_lock_irqsave(&pdc_lock, irqflags);  
        retval = real32_call(func, flags, inptr, outputr, glob_cfg);
        spin_unlock_irqrestore(&pdc_lock, irqflags);

        वापस retval;
पूर्ण
EXPORT_SYMBOL(pdc_sti_call);

#अगर_घोषित CONFIG_64BIT
/**
 * pdc_pat_cell_get_number - Returns the cell number.
 * @cell_info: The वापस buffer.
 *
 * This PDC call वापसs the cell number of the cell from which the call
 * is made.
 */
पूर्णांक pdc_pat_cell_get_number(काष्ठा pdc_pat_cell_num *cell_info)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_CELL, PDC_PAT_CELL_GET_NUMBER, __pa(pdc_result));
	स_नकल(cell_info, pdc_result, माप(*cell_info));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_cell_module - Retrieve the cell's module inक्रमmation.
 * @actcnt: The number of bytes written to mem_addr.
 * @ploc: The physical location.
 * @mod: The module index.
 * @view_type: The view of the address type.
 * @mem_addr: The वापस buffer.
 *
 * This PDC call वापसs inक्रमmation about each module attached to the cell
 * at the specअगरied location.
 */
पूर्णांक pdc_pat_cell_module(अचिन्हित दीर्घ *actcnt, अचिन्हित दीर्घ ploc, अचिन्हित दीर्घ mod,
			अचिन्हित दीर्घ view_type, व्योम *mem_addr)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;
	अटल काष्ठा pdc_pat_cell_mod_maddr_block result __attribute__ ((aligned (8)));

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_CELL, PDC_PAT_CELL_MODULE, __pa(pdc_result), 
			      ploc, mod, view_type, __pa(&result));
	अगर(!retval) अणु
		*actcnt = pdc_result[0];
		स_नकल(mem_addr, &result, *actcnt);
	पूर्ण
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_cell_info - Retrieve the cell's inक्रमmation.
 * @info: The poपूर्णांकer to a काष्ठा pdc_pat_cell_info_rtn_block.
 * @actcnt: The number of bytes which should be written to info.
 * @offset: offset of the काष्ठाure.
 * @cell_number: The cell number which should be asked, or -1 क्रम current cell.
 *
 * This PDC call वापसs inक्रमmation about the given cell (or all cells).
 */
पूर्णांक pdc_pat_cell_info(काष्ठा pdc_pat_cell_info_rtn_block *info,
		अचिन्हित दीर्घ *actcnt, अचिन्हित दीर्घ offset,
		अचिन्हित दीर्घ cell_number)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;
	काष्ठा pdc_pat_cell_info_rtn_block result;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_CELL, PDC_PAT_CELL_GET_INFO,
			__pa(pdc_result), __pa(&result), *actcnt,
			offset, cell_number);
	अगर (!retval) अणु
		*actcnt = pdc_result[0];
		स_नकल(info, &result, *actcnt);
	पूर्ण
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_cpu_get_number - Retrieve the cpu number.
 * @cpu_info: The वापस buffer.
 * @hpa: The Hard Physical Address of the CPU.
 *
 * Retrieve the cpu number क्रम the cpu at the specअगरied HPA.
 */
पूर्णांक pdc_pat_cpu_get_number(काष्ठा pdc_pat_cpu_num *cpu_info, अचिन्हित दीर्घ hpa)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_CPU, PDC_PAT_CPU_GET_NUMBER,
			      __pa(&pdc_result), hpa);
	स_नकल(cpu_info, pdc_result, माप(*cpu_info));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_get_irt_size - Retrieve the number of entries in the cell's पूर्णांकerrupt table.
 * @num_entries: The वापस value.
 * @cell_num: The target cell.
 *
 * This PDC function वापसs the number of entries in the specअगरied cell's
 * पूर्णांकerrupt table.
 */
पूर्णांक pdc_pat_get_irt_size(अचिन्हित दीर्घ *num_entries, अचिन्हित दीर्घ cell_num)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_IO, PDC_PAT_IO_GET_PCI_ROUTING_TABLE_SIZE,
			      __pa(pdc_result), cell_num);
	*num_entries = pdc_result[0];
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_get_irt - Retrieve the cell's पूर्णांकerrupt table.
 * @r_addr: The वापस buffer.
 * @cell_num: The target cell.
 *
 * This PDC function वापसs the actual पूर्णांकerrupt table क्रम the specअगरied cell.
 */
पूर्णांक pdc_pat_get_irt(व्योम *r_addr, अचिन्हित दीर्घ cell_num)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_IO, PDC_PAT_IO_GET_PCI_ROUTING_TABLE,
			      __pa(r_addr), cell_num);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_pd_get_addr_map - Retrieve inक्रमmation about memory address ranges.
 * @actlen: The वापस buffer.
 * @mem_addr: Poपूर्णांकer to the memory buffer.
 * @count: The number of bytes to पढ़ो from the buffer.
 * @offset: The offset with respect to the beginning of the buffer.
 *
 */
पूर्णांक pdc_pat_pd_get_addr_map(अचिन्हित दीर्घ *actual_len, व्योम *mem_addr, 
			    अचिन्हित दीर्घ count, अचिन्हित दीर्घ offset)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_PD, PDC_PAT_PD_GET_ADDR_MAP, __pa(pdc_result), 
			      __pa(pdc_result2), count, offset);
	*actual_len = pdc_result[0];
	स_नकल(mem_addr, pdc_result2, *actual_len);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_pd_get_PDC_पूर्णांकerface_revisions - Retrieve PDC पूर्णांकerface revisions.
 * @legacy_rev: The legacy revision.
 * @pat_rev: The PAT revision.
 * @pdc_cap: The PDC capabilities.
 *
 */
पूर्णांक pdc_pat_pd_get_pdc_revisions(अचिन्हित दीर्घ *legacy_rev,
		अचिन्हित दीर्घ *pat_rev, अचिन्हित दीर्घ *pdc_cap)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_PD, PDC_PAT_PD_GET_PDC_INTERF_REV,
				__pa(pdc_result));
	अगर (retval == PDC_OK) अणु
		*legacy_rev = pdc_result[0];
		*pat_rev = pdc_result[1];
		*pdc_cap = pdc_result[2];
	पूर्ण
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण


/**
 * pdc_pat_io_pci_cfg_पढ़ो - Read PCI configuration space.
 * @pci_addr: PCI configuration space address क्रम which the पढ़ो request is being made.
 * @pci_size: Size of पढ़ो in bytes. Valid values are 1, 2, and 4. 
 * @mem_addr: Poपूर्णांकer to वापस memory buffer.
 *
 */
पूर्णांक pdc_pat_io_pci_cfg_पढ़ो(अचिन्हित दीर्घ pci_addr, पूर्णांक pci_size, u32 *mem_addr)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_IO, PDC_PAT_IO_PCI_CONFIG_READ,
					__pa(pdc_result), pci_addr, pci_size);
	चयन(pci_size) अणु
		हाल 1: *(u8 *) mem_addr =  (u8)  pdc_result[0]; अवरोध;
		हाल 2: *(u16 *)mem_addr =  (u16) pdc_result[0]; अवरोध;
		हाल 4: *(u32 *)mem_addr =  (u32) pdc_result[0]; अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_io_pci_cfg_ग_लिखो - Retrieve inक्रमmation about memory address ranges.
 * @pci_addr: PCI configuration space address क्रम which the ग_लिखो  request is being made.
 * @pci_size: Size of ग_लिखो in bytes. Valid values are 1, 2, and 4. 
 * @value: Poपूर्णांकer to 1, 2, or 4 byte value in low order end of argument to be 
 *         written to PCI Config space.
 *
 */
पूर्णांक pdc_pat_io_pci_cfg_ग_लिखो(अचिन्हित दीर्घ pci_addr, पूर्णांक pci_size, u32 val)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_IO, PDC_PAT_IO_PCI_CONFIG_WRITE,
				pci_addr, pci_size, val);
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_mem_pdc_info - Retrieve inक्रमmation about page deallocation table
 * @rinfo: memory pdt inक्रमmation
 *
 */
पूर्णांक pdc_pat_mem_pdt_info(काष्ठा pdc_pat_mem_retinfo *rinfo)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_MEM, PDC_PAT_MEM_PD_INFO,
			__pa(&pdc_result));
	अगर (retval == PDC_OK)
		स_नकल(rinfo, &pdc_result, माप(*rinfo));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_mem_pdt_cell_info - Retrieve inक्रमmation about page deallocation
 *				table of a cell
 * @rinfo: memory pdt inक्रमmation
 * @cell: cell number
 *
 */
पूर्णांक pdc_pat_mem_pdt_cell_info(काष्ठा pdc_pat_mem_cell_pdt_retinfo *rinfo,
		अचिन्हित दीर्घ cell)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_MEM, PDC_PAT_MEM_CELL_INFO,
			__pa(&pdc_result), cell);
	अगर (retval == PDC_OK)
		स_नकल(rinfo, &pdc_result, माप(*rinfo));
	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_mem_पढ़ो_cell_pdt - Read PDT entries from (old) PAT firmware
 * @pret: array of PDT entries
 * @pdt_entries_ptr: ptr to hold number of PDT entries
 * @max_entries: maximum number of entries to be पढ़ो
 *
 */
पूर्णांक pdc_pat_mem_पढ़ो_cell_pdt(काष्ठा pdc_pat_mem_पढ़ो_pd_retinfo *pret,
		अचिन्हित दीर्घ *pdt_entries_ptr, अचिन्हित दीर्घ max_entries)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags, entries;

	spin_lock_irqsave(&pdc_lock, flags);
	/* PDC_PAT_MEM_CELL_READ is available on early PAT machines only */
	retval = mem_pdc_call(PDC_PAT_MEM, PDC_PAT_MEM_CELL_READ,
			__pa(&pdc_result), parisc_cell_num,
			__pa(pdt_entries_ptr));

	अगर (retval == PDC_OK) अणु
		/* build up वापस value as क्रम PDC_PAT_MEM_PD_READ */
		entries = min(pdc_result[0], max_entries);
		pret->pdt_entries = entries;
		pret->actual_count_bytes = entries * माप(अचिन्हित दीर्घ);
	पूर्ण

	spin_unlock_irqrestore(&pdc_lock, flags);
	WARN_ON(retval == PDC_OK && pdc_result[0] > max_entries);

	वापस retval;
पूर्ण
/**
 * pdc_pat_mem_पढ़ो_pd_pdt - Read PDT entries from (newer) PAT firmware
 * @pret: array of PDT entries
 * @pdt_entries_ptr: ptr to hold number of PDT entries
 * @count: number of bytes to पढ़ो
 * @offset: offset to start (in bytes)
 *
 */
पूर्णांक pdc_pat_mem_पढ़ो_pd_pdt(काष्ठा pdc_pat_mem_पढ़ो_pd_retinfo *pret,
		अचिन्हित दीर्घ *pdt_entries_ptr, अचिन्हित दीर्घ count,
		अचिन्हित दीर्घ offset)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags, entries;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_MEM, PDC_PAT_MEM_PD_READ,
		__pa(&pdc_result), __pa(pdt_entries_ptr),
		count, offset);

	अगर (retval == PDC_OK) अणु
		entries = min(pdc_result[0], count);
		pret->actual_count_bytes = entries;
		pret->pdt_entries = entries / माप(अचिन्हित दीर्घ);
	पूर्ण

	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण

/**
 * pdc_pat_mem_get_dimm_phys_location - Get physical DIMM slot via PAT firmware
 * @pret: ptr to hold वापसed inक्रमmation
 * @phys_addr: physical address to examine
 *
 */
पूर्णांक pdc_pat_mem_get_dimm_phys_location(
		काष्ठा pdc_pat_mem_phys_mem_location *pret,
		अचिन्हित दीर्घ phys_addr)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_PAT_MEM, PDC_PAT_MEM_ADDRESS,
		__pa(&pdc_result), phys_addr);

	अगर (retval == PDC_OK)
		स_नकल(pret, &pdc_result, माप(*pret));

	spin_unlock_irqrestore(&pdc_lock, flags);

	वापस retval;
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */
#पूर्ण_अगर /* defined(BOOTLOADER) */


/***************** 32-bit real-mode calls ***********/
/* The काष्ठा below is used
 * to overlay real_stack (real2.S), preparing a 32-bit call frame.
 * real32_call_यंत्र() then uses this stack in narrow real mode
 */

काष्ठा narrow_stack अणु
	/* use पूर्णांक, not दीर्घ which is 64 bits */
	अचिन्हित पूर्णांक arg13;
	अचिन्हित पूर्णांक arg12;
	अचिन्हित पूर्णांक arg11;
	अचिन्हित पूर्णांक arg10;
	अचिन्हित पूर्णांक arg9;
	अचिन्हित पूर्णांक arg8;
	अचिन्हित पूर्णांक arg7;
	अचिन्हित पूर्णांक arg6;
	अचिन्हित पूर्णांक arg5;
	अचिन्हित पूर्णांक arg4;
	अचिन्हित पूर्णांक arg3;
	अचिन्हित पूर्णांक arg2;
	अचिन्हित पूर्णांक arg1;
	अचिन्हित पूर्णांक arg0;
	अचिन्हित पूर्णांक frame_marker[8];
	अचिन्हित पूर्णांक sp;
	/* in reality, there's nearly 8k of stack after this */
पूर्ण;

दीर्घ real32_call(अचिन्हित दीर्घ fn, ...)
अणु
	बहु_सूची args;
	बाह्य काष्ठा narrow_stack real_stack;
	बाह्य अचिन्हित दीर्घ real32_call_यंत्र(अचिन्हित पूर्णांक *,
					     अचिन्हित पूर्णांक *, 
					     अचिन्हित पूर्णांक);
	
	बहु_शुरू(args, fn);
	real_stack.arg0 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg1 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg2 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg3 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg4 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg5 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg6 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg7 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg8 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg9 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg10 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg11 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg12 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	real_stack.arg13 = बहु_तर्क(args, अचिन्हित पूर्णांक);
	बहु_पूर्ण(args);
	
	वापस real32_call_यंत्र(&real_stack.sp, &real_stack.arg0, fn);
पूर्ण

#अगर_घोषित CONFIG_64BIT
/***************** 64-bit real-mode calls ***********/

काष्ठा wide_stack अणु
	अचिन्हित दीर्घ arg0;
	अचिन्हित दीर्घ arg1;
	अचिन्हित दीर्घ arg2;
	अचिन्हित दीर्घ arg3;
	अचिन्हित दीर्घ arg4;
	अचिन्हित दीर्घ arg5;
	अचिन्हित दीर्घ arg6;
	अचिन्हित दीर्घ arg7;
	अचिन्हित दीर्घ arg8;
	अचिन्हित दीर्घ arg9;
	अचिन्हित दीर्घ arg10;
	अचिन्हित दीर्घ arg11;
	अचिन्हित दीर्घ arg12;
	अचिन्हित दीर्घ arg13;
	अचिन्हित दीर्घ frame_marker[2];	/* rp, previous sp */
	अचिन्हित दीर्घ sp;
	/* in reality, there's nearly 8k of stack after this */
पूर्ण;

दीर्घ real64_call(अचिन्हित दीर्घ fn, ...)
अणु
	बहु_सूची args;
	बाह्य काष्ठा wide_stack real64_stack;
	बाह्य अचिन्हित दीर्घ real64_call_यंत्र(अचिन्हित दीर्घ *,
					     अचिन्हित दीर्घ *, 
					     अचिन्हित दीर्घ);
    
	बहु_शुरू(args, fn);
	real64_stack.arg0 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg1 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg2 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg3 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg4 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg5 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg6 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg7 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg8 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg9 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg10 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg11 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg12 = बहु_तर्क(args, अचिन्हित दीर्घ);
	real64_stack.arg13 = बहु_तर्क(args, अचिन्हित दीर्घ);
	बहु_पूर्ण(args);
	
	वापस real64_call_यंत्र(&real64_stack.sp, &real64_stack.arg0, fn);
पूर्ण

#पूर्ण_अगर /* CONFIG_64BIT */
