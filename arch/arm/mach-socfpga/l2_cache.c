<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright Altera Corporation (C) 2016. All rights reserved.
 */
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>

#समावेश "core.h"

/* A10 System Manager L2 ECC Control रेजिस्टर */
#घोषणा A10_MPU_CTRL_L2_ECC_OFST          0x0
#घोषणा A10_MPU_CTRL_L2_ECC_EN            BIT(0)

/* A10 System Manager Global IRQ Mask रेजिस्टर */
#घोषणा A10_SYSMGR_ECC_INTMASK_CLR_OFST   0x98
#घोषणा A10_SYSMGR_ECC_INTMASK_CLR_L2     BIT(0)

/* A10 System Manager L2 ECC IRQ Clear रेजिस्टर */
#घोषणा A10_SYSMGR_MPU_CLEAR_L2_ECC_OFST  0xA8
#घोषणा A10_SYSMGR_MPU_CLEAR_L2_ECC       (BIT(31) | BIT(15))

व्योम socfpga_init_l2_ecc(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *mapped_l2_edac_addr;

	np = of_find_compatible_node(शून्य, शून्य, "altr,socfpga-l2-ecc");
	अगर (!np) अणु
		pr_err("Unable to find socfpga-l2-ecc in dtb\n");
		वापस;
	पूर्ण

	mapped_l2_edac_addr = of_iomap(np, 0);
	of_node_put(np);
	अगर (!mapped_l2_edac_addr) अणु
		pr_err("Unable to find L2 ECC mapping in dtb\n");
		वापस;
	पूर्ण

	/* Enable ECC */
	ग_लिखोl(0x01, mapped_l2_edac_addr);
	iounmap(mapped_l2_edac_addr);
पूर्ण

व्योम socfpga_init_arria10_l2_ecc(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *mapped_l2_edac_addr;

	/* Find the L2 EDAC device tree node */
	np = of_find_compatible_node(शून्य, शून्य, "altr,socfpga-a10-l2-ecc");
	अगर (!np) अणु
		pr_err("Unable to find socfpga-a10-l2-ecc in dtb\n");
		वापस;
	पूर्ण

	mapped_l2_edac_addr = of_iomap(np, 0);
	of_node_put(np);
	अगर (!mapped_l2_edac_addr) अणु
		pr_err("Unable to find L2 ECC mapping in dtb\n");
		वापस;
	पूर्ण

	अगर (!sys_manager_base_addr) अणु
		pr_err("System Manager not mapped for L2 ECC\n");
		जाओ निकास;
	पूर्ण
	/* Clear any pending IRQs */
	ग_लिखोl(A10_SYSMGR_MPU_CLEAR_L2_ECC, (sys_manager_base_addr +
	       A10_SYSMGR_MPU_CLEAR_L2_ECC_OFST));
	/* Enable ECC */
	ग_लिखोl(A10_SYSMGR_ECC_INTMASK_CLR_L2, sys_manager_base_addr +
	       A10_SYSMGR_ECC_INTMASK_CLR_OFST);
	ग_लिखोl(A10_MPU_CTRL_L2_ECC_EN, mapped_l2_edac_addr +
	       A10_MPU_CTRL_L2_ECC_OFST);
निकास:
	iounmap(mapped_l2_edac_addr);
पूर्ण
