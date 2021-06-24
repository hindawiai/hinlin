<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * ChipCommon न_अंकD flash पूर्णांकerface
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcma/bcma.h>

काष्ठा platक्रमm_device bcma_nflash_dev = अणु
	.name		= "bcma_nflash",
	.num_resources	= 0,
पूर्ण;

/* Initialize न_अंकD flash access */
पूर्णांक bcma_nflash_init(काष्ठा bcma_drv_cc *cc)
अणु
	काष्ठा bcma_bus *bus = cc->core->bus;

	अगर (bus->chipinfo.id != BCMA_CHIP_ID_BCM4706 &&
	    cc->core->id.rev != 38) अणु
		bcma_err(bus, "NAND flash on unsupported board!\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!(cc->capabilities & BCMA_CC_CAP_NFLASH)) अणु
		bcma_err(bus, "NAND flash not present according to ChipCommon\n");
		वापस -ENODEV;
	पूर्ण

	cc->nflash.present = true;
	अगर (cc->core->id.rev == 38 &&
	    (cc->status & BCMA_CC_CHIPST_5357_न_अंकD_BOOT))
		cc->nflash.boot = true;

	/* Prepare platक्रमm device, but करोn't register it yet. It's too early,
	 * दो_स्मृति (required by device_निजी_init) is not available yet. */
	bcma_nflash_dev.dev.platक्रमm_data = &cc->nflash;

	वापस 0;
पूर्ण
