<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Keystone2 based boards and SOC related code.
 *
 * Copyright 2013 Texas Instruments, Inc.
 *	Cyril Chemparathy <cyril@ti.com>
 *	Santosh Shilimkar <santosh.shillimkar@ti.com>
 */
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/memory.h>

#समावेश "memory.h"

#समावेश "keystone.h"

#अगर_घोषित CONFIG_ARM_LPAE
अटल पूर्णांक keystone_platक्रमm_notअगरier(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा device *dev = data;

	अगर (event != BUS_NOTIFY_ADD_DEVICE)
		वापस NOTIFY_DONE;

	अगर (!dev)
		वापस NOTIFY_BAD;

	अगर (!dev->of_node) अणु
		पूर्णांक ret = dma_direct_set_offset(dev, KEYSTONE_HIGH_PHYS_START,
						KEYSTONE_LOW_PHYS_START,
						KEYSTONE_HIGH_PHYS_SIZE);
		dev_err(dev, "set dma_offset%08llx%s\n",
			KEYSTONE_HIGH_PHYS_START - KEYSTONE_LOW_PHYS_START,
			ret ? " failed" : "");
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block platक्रमm_nb = अणु
	.notअगरier_call = keystone_platक्रमm_notअगरier,
पूर्ण;
#पूर्ण_अगर /* CONFIG_ARM_LPAE */

अटल व्योम __init keystone_init(व्योम)
अणु
#अगर_घोषित CONFIG_ARM_LPAE
	अगर (PHYS_OFFSET >= KEYSTONE_HIGH_PHYS_START)
		bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &platक्रमm_nb);
#पूर्ण_अगर
	keystone_pm_runसमय_init();
पूर्ण

अटल दीर्घ दीर्घ __init keystone_pv_fixup(व्योम)
अणु
	दीर्घ दीर्घ offset;
	u64 mem_start, mem_end;

	mem_start = memblock_start_of_DRAM();
	mem_end = memblock_end_of_DRAM();

	/* nothing to करो अगर we are running out of the <32-bit space */
	अगर (mem_start >= KEYSTONE_LOW_PHYS_START &&
	    mem_end   <= KEYSTONE_LOW_PHYS_END)
		वापस 0;

	अगर (mem_start < KEYSTONE_HIGH_PHYS_START ||
	    mem_end   > KEYSTONE_HIGH_PHYS_END) अणु
		pr_crit("Invalid address space for memory (%08llx-%08llx)\n",
		        mem_start, mem_end);
		वापस 0;
	पूर्ण

	offset = KEYSTONE_HIGH_PHYS_START - KEYSTONE_LOW_PHYS_START;

	/* Populate the arch idmap hook */
	arch_phys_to_idmap_offset = -offset;

	वापस offset;
पूर्ण

अटल स्थिर अक्षर *स्थिर keystone_match[] __initस्थिर = अणु
	"ti,k2hk",
	"ti,k2e",
	"ti,k2l",
	"ti,k2g",
	"ti,keystone",
	शून्य,
पूर्ण;

DT_MACHINE_START(KEYSTONE, "Keystone")
#अगर defined(CONFIG_ZONE_DMA) && defined(CONFIG_ARM_LPAE)
	.dma_zone_size	= SZ_2G,
#पूर्ण_अगर
	.smp		= smp_ops(keystone_smp_ops),
	.init_machine	= keystone_init,
	.dt_compat	= keystone_match,
	.pv_fixup	= keystone_pv_fixup,
MACHINE_END
