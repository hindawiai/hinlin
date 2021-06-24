<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * ChipCommon parallel flash
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/platक्रमm_device.h>

अटल स्थिर अक्षर * स्थिर part_probes[] = अणु "bcm47xxpart", शून्य पूर्ण;

अटल काष्ठा physmap_flash_data bcma_pflash_data = अणु
	.part_probe_types	= part_probes,
पूर्ण;

अटल काष्ठा resource bcma_pflash_resource = अणु
	.name	= "bcma_pflash",
	.flags  = IORESOURCE_MEM,
पूर्ण;

काष्ठा platक्रमm_device bcma_pflash_dev = अणु
	.name		= "physmap-flash",
	.dev		= अणु
		.platक्रमm_data  = &bcma_pflash_data,
	पूर्ण,
	.resource	= &bcma_pflash_resource,
	.num_resources	= 1,
पूर्ण;

पूर्णांक bcma_pflash_init(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_pflash *pflash = &cc->pflash;

	pflash->present = true;

	अगर (!(bcma_पढ़ो32(cc->core, BCMA_CC_FLASH_CFG) & BCMA_CC_FLASH_CFG_DS))
		bcma_pflash_data.width = 1;
	अन्यथा
		bcma_pflash_data.width = 2;

	bcma_pflash_resource.start = BCMA_SOC_FLASH2;
	bcma_pflash_resource.end = BCMA_SOC_FLASH2 + BCMA_SOC_FLASH2_SZ;

	वापस 0;
पूर्ण
