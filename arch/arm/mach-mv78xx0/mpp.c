<शैली गुरु>
/*
 * arch/arm/mach-mv78x00/mpp.c
 *
 * MPP functions क्रम Marvell MV78x00 SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <plat/mpp.h>
#समावेश "mv78xx0.h"
#समावेश "common.h"
#समावेश "mpp.h"

अटल अचिन्हित पूर्णांक __init mv78xx0_variant(व्योम)
अणु
	u32 dev, rev;

	mv78xx0_pcie_id(&dev, &rev);

	अगर (dev == MV78100_DEV_ID && rev >= MV78100_REV_A0)
		वापस MPP_78100_A0_MASK;

	prपूर्णांकk(KERN_ERR "MPP setup: unknown mv78x00 variant "
			"(dev %#x rev %#x)\n", dev, rev);
	वापस 0;
पूर्ण

व्योम __init mv78xx0_mpp_conf(अचिन्हित पूर्णांक *mpp_list)
अणु
	orion_mpp_conf(mpp_list, mv78xx0_variant(),
		       MPP_MAX, DEV_BUS_VIRT_BASE);
पूर्ण
