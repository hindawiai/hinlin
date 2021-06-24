<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP Secure API infraकाष्ठाure.
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 * Copyright (C) 2012 Ivaylo Dimitrov <मुक्तmangorकरोn@abv.bg>
 * Copyright (C) 2013 Pali Rohथँr <pali@kernel.org>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/memblock.h>

#समावेश "common.h"
#समावेश "omap-secure.h"
#समावेश "soc.h"

अटल phys_addr_t omap_secure_memblock_base;

bool optee_available;

#घोषणा OMAP_SIP_SMC_STD_CALL_VAL(func_num) \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_STD_CALL, ARM_SMCCC_SMC_32, \
	ARM_SMCCC_OWNER_SIP, (func_num))

अटल व्योम __init omap_optee_init_check(व्योम)
अणु
	काष्ठा device_node *np;

	/*
	 * We only check that the OP-TEE node is present and available. The
	 * OP-TEE kernel driver is not needed क्रम the type of पूर्णांकeraction made
	 * with OP-TEE here so the driver's status is not checked.
	 */
	np = of_find_node_by_path("/firmware/optee");
	अगर (np && of_device_is_available(np))
		optee_available = true;
	of_node_put(np);
पूर्ण

/**
 * omap_sec_dispatcher: Routine to dispatch low घातer secure
 * service routines
 * @idx: The HAL API index
 * @flag: The flag indicating criticality of operation
 * @nargs: Number of valid arguments out of four.
 * @arg1, arg2, arg3 args4: Parameters passed to secure API
 *
 * Return the non-zero error value on failure.
 */
u32 omap_secure_dispatcher(u32 idx, u32 flag, u32 nargs, u32 arg1, u32 arg2,
							 u32 arg3, u32 arg4)
अणु
	u32 ret;
	u32 param[5];

	param[0] = nargs;
	param[1] = arg1;
	param[2] = arg2;
	param[3] = arg3;
	param[4] = arg4;

	/*
	 * Secure API needs physical address
	 * poपूर्णांकer क्रम the parameters
	 */
	flush_cache_all();
	outer_clean_range(__pa(param), __pa(param + 5));
	ret = omap_smc2(idx, flag, __pa(param));

	वापस ret;
पूर्ण

व्योम omap_smccc_smc(u32 fn, u32 arg)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(OMAP_SIP_SMC_STD_CALL_VAL(fn), arg,
		      0, 0, 0, 0, 0, 0, &res);
	WARN(res.a0, "Secure function call 0x%08x failed\n", fn);
पूर्ण

व्योम omap_smc1(u32 fn, u32 arg)
अणु
	/*
	 * If this platक्रमm has OP-TEE installed we use ARM SMC calls
	 * otherwise fall back to the OMAP ROM style calls.
	 */
	अगर (optee_available)
		omap_smccc_smc(fn, arg);
	अन्यथा
		_omap_smc1(fn, arg);
पूर्ण

/* Allocate the memory to save secure ram */
पूर्णांक __init omap_secure_ram_reserve_memblock(व्योम)
अणु
	u32 size = OMAP_SECURE_RAM_STORAGE;

	size = ALIGN(size, SECTION_SIZE);
	omap_secure_memblock_base = arm_memblock_steal(size, SECTION_SIZE);

	वापस 0;
पूर्ण

phys_addr_t omap_secure_ram_mempool_base(व्योम)
अणु
	वापस omap_secure_memblock_base;
पूर्ण

#अगर defined(CONFIG_ARCH_OMAP3) && defined(CONFIG_PM)
u32 omap3_save_secure_ram(व्योम __iomem *addr, पूर्णांक size)
अणु
	u32 ret;
	u32 param[5];

	अगर (size != OMAP3_SAVE_SECURE_RAM_SZ)
		वापस OMAP3_SAVE_SECURE_RAM_SZ;

	param[0] = 4;		/* Number of arguments */
	param[1] = __pa(addr);	/* Physical address क्रम saving */
	param[2] = 0;
	param[3] = 1;
	param[4] = 1;

	ret = save_secure_ram_context(__pa(param));

	वापस ret;
पूर्ण
#पूर्ण_अगर

/**
 * rx51_secure_dispatcher: Routine to dispatch secure PPA API calls
 * @idx: The PPA API index
 * @process: Process ID
 * @flag: The flag indicating criticality of operation
 * @nargs: Number of valid arguments out of four.
 * @arg1, arg2, arg3 args4: Parameters passed to secure API
 *
 * Return the non-zero error value on failure.
 *
 * NOTE: rx51_secure_dispatcher dअगरfers from omap_secure_dispatcher because
 *       it calling omap_smc3() instead omap_smc2() and param[0] is nargs+1
 */
u32 rx51_secure_dispatcher(u32 idx, u32 process, u32 flag, u32 nargs,
			   u32 arg1, u32 arg2, u32 arg3, u32 arg4)
अणु
	u32 ret;
	u32 param[5];

	param[0] = nargs+1; /* RX-51 needs number of arguments + 1 */
	param[1] = arg1;
	param[2] = arg2;
	param[3] = arg3;
	param[4] = arg4;

	/*
	 * Secure API needs physical address
	 * poपूर्णांकer क्रम the parameters
	 */
	local_irq_disable();
	local_fiq_disable();
	flush_cache_all();
	outer_clean_range(__pa(param), __pa(param + 5));
	ret = omap_smc3(idx, process, flag, __pa(param));
	flush_cache_all();
	local_fiq_enable();
	local_irq_enable();

	वापस ret;
पूर्ण

/**
 * rx51_secure_update_aux_cr: Routine to modअगरy the contents of Auxiliary Control Register
 *  @set_bits: bits to set in ACR
 *  @clr_bits: bits to clear in ACR
 *
 * Return the non-zero error value on failure.
*/
u32 rx51_secure_update_aux_cr(u32 set_bits, u32 clear_bits)
अणु
	u32 acr;

	/* Read ACR */
	यंत्र अस्थिर ("mrc p15, 0, %0, c1, c0, 1" : "=r" (acr));
	acr &= ~clear_bits;
	acr |= set_bits;

	वापस rx51_secure_dispatcher(RX51_PPA_WRITE_ACR,
				      0,
				      FLAG_START_CRITICAL,
				      1, acr, 0, 0, 0);
पूर्ण

/**
 * rx51_secure_rng_call: Routine क्रम HW अक्रमom generator
 */
u32 rx51_secure_rng_call(u32 ptr, u32 count, u32 flag)
अणु
	वापस rx51_secure_dispatcher(RX51_PPA_HWRNG,
				      0,
				      NO_FLAG,
				      3, ptr, count, flag, 0);
पूर्ण

व्योम __init omap_secure_init(व्योम)
अणु
	omap_optee_init_check();
पूर्ण

/*
 * Dummy dispatcher call after core OSWR and MPU off. Updates the ROM वापस
 * address after MMU has been re-enabled after CPU1 has been woken up again.
 * Otherwise the ROM code will attempt to use the earlier physical वापस
 * address that got set with MMU off when waking up CPU1. Only used on secure
 * devices.
 */
अटल पूर्णांक cpu_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_EXIT:
		omap_secure_dispatcher(OMAP4_PPA_SERVICE_0,
				       FLAG_START_CRITICAL,
				       0, 0, 0, 0, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block secure_notअगरier_block = अणु
	.notअगरier_call = cpu_notअगरier,
पूर्ण;

अटल पूर्णांक __init secure_pm_init(व्योम)
अणु
	अगर (omap_type() == OMAP2_DEVICE_TYPE_GP || !soc_is_omap44xx())
		वापस 0;

	cpu_pm_रेजिस्टर_notअगरier(&secure_notअगरier_block);

	वापस 0;
पूर्ण
omap_arch_initcall(secure_pm_init);
