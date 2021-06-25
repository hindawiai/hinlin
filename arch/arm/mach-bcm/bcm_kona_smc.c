<शैली गुरु>
/*
 * Copyright (C) 2013 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <मानकतर्क.स>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/of_address.h>

#समावेश "bcm_kona_smc.h"

अटल u32		bcm_smc_buffer_phys;	/* physical address */
अटल व्योम __iomem	*bcm_smc_buffer;	/* भव address */

काष्ठा bcm_kona_smc_data अणु
	अचिन्हित service_id;
	अचिन्हित arg0;
	अचिन्हित arg1;
	अचिन्हित arg2;
	अचिन्हित arg3;
	अचिन्हित result;
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_kona_smc_ids[] __initस्थिर = अणु
	अणु.compatible = "brcm,kona-smc"पूर्ण,
	अणु.compatible = "bcm,kona-smc"पूर्ण, /* deprecated name */
	अणुपूर्ण,
पूर्ण;

/* Map in the args buffer area */
पूर्णांक __init bcm_kona_smc_init(व्योम)
अणु
	काष्ठा device_node *node;
	स्थिर __be32 *prop_val;
	u64 prop_size = 0;
	अचिन्हित दीर्घ buffer_size;
	u32 buffer_phys;

	/* Read buffer addr and size from the device tree node */
	node = of_find_matching_node(शून्य, bcm_kona_smc_ids);
	अगर (!node)
		वापस -ENODEV;

	prop_val = of_get_address(node, 0, &prop_size, शून्य);
	अगर (!prop_val)
		वापस -EINVAL;

	/* We assume space क्रम four 32-bit arguments */
	अगर (prop_size < 4 * माप(u32) || prop_size > (u64)अच_दीर्घ_उच्च)
		वापस -EINVAL;
	buffer_size = (अचिन्हित दीर्घ)prop_size;

	buffer_phys = be32_to_cpup(prop_val);
	अगर (!buffer_phys)
		वापस -EINVAL;

	bcm_smc_buffer = ioremap(buffer_phys, buffer_size);
	अगर (!bcm_smc_buffer)
		वापस -ENOMEM;
	bcm_smc_buffer_phys = buffer_phys;

	pr_info("Kona Secure API initialized\n");

	वापस 0;
पूर्ण

/*
 * पूर्णांक bcm_kona_करो_smc(u32 service_id, u32 buffer_addr)
 *
 * Only core 0 can run the secure monitor code.  If an "smc" request
 * is initiated on a dअगरferent core it must be redirected to core 0
 * क्रम execution.  We rely on the caller to handle this.
 *
 * Each "smc" request supplies a service id and the address of a
 * buffer containing parameters related to the service to be
 * perक्रमmed.  A flags value defines the behavior of the level 2
 * cache and पूर्णांकerrupt handling जबतक the secure monitor executes.
 *
 * Parameters to the "smc" request are passed in r4-r6 as follows:
 *     r4	service id
 *     r5	flags (SEC_ROM_*)
 *     r6	physical address of buffer with other parameters
 *
 * Execution of an "smc" request produces two distinct results.
 *
 * First, the secure monitor call itself (regardless of the specअगरic
 * service request) can succeed, or can produce an error.  When an
 * "smc" request completes this value is found in r12; it should
 * always be SEC_EXIT_NORMAL.
 *
 * In addition, the particular service perक्रमmed produces a result.
 * The values that should be expected depend on the service.  We
 * thereक्रमe वापस this value to the caller, so it can handle the
 * request result appropriately.  This result value is found in r0
 * when the "smc" request completes.
 */
अटल पूर्णांक bcm_kona_करो_smc(u32 service_id, u32 buffer_phys)
अणु
	रेजिस्टर u32 ip यंत्र("ip");	/* Also called r12 */
	रेजिस्टर u32 r0 यंत्र("r0");
	रेजिस्टर u32 r4 यंत्र("r4");
	रेजिस्टर u32 r5 यंत्र("r5");
	रेजिस्टर u32 r6 यंत्र("r6");

	r4 = service_id;
	r5 = 0x3;		/* Keep IRQ and FIQ off in SM */
	r6 = buffer_phys;

	यंत्र अस्थिर (
		/* Make sure we got the रेजिस्टरs we want */
		__यंत्रeq("%0", "ip")
		__यंत्रeq("%1", "r0")
		__यंत्रeq("%2", "r4")
		__यंत्रeq("%3", "r5")
		__यंत्रeq("%4", "r6")
		".arch_extension sec\n"
		"	smc    #0\n"
		: "=r" (ip), "=r" (r0)
		: "r" (r4), "r" (r5), "r" (r6)
		: "r1", "r2", "r3", "r7", "lr");

	BUG_ON(ip != SEC_EXIT_NORMAL);

	वापस r0;
पूर्ण

/* __bcm_kona_smc() should only run on CPU 0, with pre-emption disabled */
अटल व्योम __bcm_kona_smc(व्योम *info)
अणु
	काष्ठा bcm_kona_smc_data *data = info;
	u32 __iomem *args = bcm_smc_buffer;

	BUG_ON(smp_processor_id() != 0);
	BUG_ON(!args);

	/* Copy the four 32 bit argument values पूर्णांकo the bounce area */
	ग_लिखोl_relaxed(data->arg0, args++);
	ग_लिखोl_relaxed(data->arg1, args++);
	ग_लिखोl_relaxed(data->arg2, args++);
	ग_लिखोl(data->arg3, args);

	/* Flush caches क्रम input data passed to Secure Monitor */
	flush_cache_all();

	/* Trap पूर्णांकo Secure Monitor and record the request result */
	data->result = bcm_kona_करो_smc(data->service_id, bcm_smc_buffer_phys);
पूर्ण

अचिन्हित bcm_kona_smc(अचिन्हित service_id, अचिन्हित arg0, अचिन्हित arg1,
		  अचिन्हित arg2, अचिन्हित arg3)
अणु
	काष्ठा bcm_kona_smc_data data;

	data.service_id = service_id;
	data.arg0 = arg0;
	data.arg1 = arg1;
	data.arg2 = arg2;
	data.arg3 = arg3;
	data.result = 0;

	/*
	 * Due to a limitation of the secure monitor, we must use the SMP
	 * infraकाष्ठाure to क्रमward all secure monitor calls to Core 0.
	 */
	smp_call_function_single(0, __bcm_kona_smc, &data, 1);

	वापस data.result;
पूर्ण
