<शैली गुरु>
/*
 * arch/arm/mach-orion5x/mpp.c
 *
 * MPP functions क्रम Marvell Orion 5x SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <plat/mpp.h>
#समावेश "orion5x.h"
#समावेश "mpp.h"
#समावेश "common.h"

अटल अचिन्हित पूर्णांक __init orion5x_variant(व्योम)
अणु
	u32 dev;
	u32 rev;

	orion5x_pcie_id(&dev, &rev);

	अगर (dev == MV88F5181_DEV_ID)
		वापस MPP_F5181_MASK;

	अगर (dev == MV88F5182_DEV_ID)
		वापस MPP_F5182_MASK;

	अगर (dev == MV88F5281_DEV_ID)
		वापस MPP_F5281_MASK;

	prपूर्णांकk(KERN_ERR "MPP setup: unknown orion5x variant "
	       "(dev %#x rev %#x)\n", dev, rev);
	वापस 0;
पूर्ण

व्योम __init orion5x_mpp_conf(अचिन्हित पूर्णांक *mpp_list)
अणु
	orion_mpp_conf(mpp_list, orion5x_variant(),
		       MPP_MAX, ORION5X_DEV_BUS_VIRT_BASE);
पूर्ण
