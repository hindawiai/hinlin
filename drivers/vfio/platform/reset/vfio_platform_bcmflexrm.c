<शैली गुरु>
/*
 * Copyright (C) 2017 Broadcom
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

/*
 * This driver provides reset support क्रम Broadcom FlexRM ring manager
 * to VFIO platक्रमm.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "../vfio_platform_private.h"

/* FlexRM configuration */
#घोषणा RING_REGS_SIZE					0x10000
#घोषणा RING_VER_MAGIC					0x76303031

/* Per-Ring रेजिस्टर offsets */
#घोषणा RING_VER					0x000
#घोषणा RING_CONTROL					0x034
#घोषणा RING_FLUSH_DONE					0x038

/* Register RING_CONTROL fields */
#घोषणा CONTROL_FLUSH_SHIFT				5

/* Register RING_FLUSH_DONE fields */
#घोषणा FLUSH_DONE_MASK					0x1

अटल पूर्णांक vfio_platक्रमm_bcmflexrm_shutकरोwn(व्योम __iomem *ring)
अणु
	अचिन्हित पूर्णांक समयout;

	/* Disable/inactivate ring */
	ग_लिखोl_relaxed(0x0, ring + RING_CONTROL);

	/* Set ring flush state */
	समयout = 1000; /* समयout of 1s */
	ग_लिखोl_relaxed(BIT(CONTROL_FLUSH_SHIFT), ring + RING_CONTROL);
	करो अणु
		अगर (पढ़ोl_relaxed(ring + RING_FLUSH_DONE) &
		    FLUSH_DONE_MASK)
			अवरोध;
		mdelay(1);
	पूर्ण जबतक (--समयout);
	अगर (!समयout)
		वापस -ETIMEDOUT;

	/* Clear ring flush state */
	समयout = 1000; /* समयout of 1s */
	ग_लिखोl_relaxed(0x0, ring + RING_CONTROL);
	करो अणु
		अगर (!(पढ़ोl_relaxed(ring + RING_FLUSH_DONE) &
		      FLUSH_DONE_MASK))
			अवरोध;
		mdelay(1);
	पूर्ण जबतक (--समयout);
	अगर (!समयout)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_bcmflexrm_reset(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	व्योम __iomem *ring;
	पूर्णांक rc = 0, ret = 0, ring_num = 0;
	काष्ठा vfio_platक्रमm_region *reg = &vdev->regions[0];

	/* Map FlexRM ring रेजिस्टरs अगर not mapped */
	अगर (!reg->ioaddr) अणु
		reg->ioaddr = ioremap(reg->addr, reg->size);
		अगर (!reg->ioaddr)
			वापस -ENOMEM;
	पूर्ण

	/* Discover and shutकरोwn each FlexRM ring */
	क्रम (ring = reg->ioaddr;
	     ring < (reg->ioaddr + reg->size); ring += RING_REGS_SIZE) अणु
		अगर (पढ़ोl_relaxed(ring + RING_VER) == RING_VER_MAGIC) अणु
			rc = vfio_platक्रमm_bcmflexrm_shutकरोwn(ring);
			अगर (rc) अणु
				dev_warn(vdev->device,
					 "FlexRM ring%d shutdown error %d\n",
					 ring_num, rc);
				ret |= rc;
			पूर्ण
			ring_num++;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

module_vfio_reset_handler("brcm,iproc-flexrm-mbox",
			  vfio_platक्रमm_bcmflexrm_reset);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Anup Patel <anup.patel@broadcom.com>");
MODULE_DESCRIPTION("Reset support for Broadcom FlexRM VFIO platform device");
