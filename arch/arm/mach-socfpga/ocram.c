<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright Altera Corporation (C) 2016. All rights reserved.
 */
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/genभाग.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश "core.h"

#घोषणा ALTR_OCRAM_CLEAR_ECC          0x00000018
#घोषणा ALTR_OCRAM_ECC_EN             0x00000019

व्योम socfpga_init_ocram_ecc(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *mapped_ocr_edac_addr;

	/* Find the OCRAM EDAC device tree node */
	np = of_find_compatible_node(शून्य, शून्य, "altr,socfpga-ocram-ecc");
	अगर (!np) अणु
		pr_err("Unable to find socfpga-ocram-ecc\n");
		वापस;
	पूर्ण

	mapped_ocr_edac_addr = of_iomap(np, 0);
	of_node_put(np);
	अगर (!mapped_ocr_edac_addr) अणु
		pr_err("Unable to map OCRAM ecc regs.\n");
		वापस;
	पूर्ण

	/* Clear any pending OCRAM ECC पूर्णांकerrupts, then enable ECC */
	ग_लिखोl(ALTR_OCRAM_CLEAR_ECC, mapped_ocr_edac_addr);
	ग_लिखोl(ALTR_OCRAM_ECC_EN, mapped_ocr_edac_addr);

	iounmap(mapped_ocr_edac_addr);
पूर्ण

/* Arria10 OCRAM Section */
#घोषणा ALTR_A10_ECC_CTRL_OFST          0x08
#घोषणा ALTR_A10_OCRAM_ECC_EN_CTL       (BIT(1) | BIT(0))
#घोषणा ALTR_A10_ECC_INITA              BIT(16)

#घोषणा ALTR_A10_ECC_INITSTAT_OFST      0x0C
#घोषणा ALTR_A10_ECC_INITCOMPLETEA      BIT(0)
#घोषणा ALTR_A10_ECC_INITCOMPLETEB      BIT(8)

#घोषणा ALTR_A10_ECC_ERRINTEN_OFST      0x10
#घोषणा ALTR_A10_ECC_SERRINTEN          BIT(0)

#घोषणा ALTR_A10_ECC_INTSTAT_OFST       0x20
#घोषणा ALTR_A10_ECC_SERRPENA           BIT(0)
#घोषणा ALTR_A10_ECC_DERRPENA           BIT(8)
#घोषणा ALTR_A10_ECC_ERRPENA_MASK       (ALTR_A10_ECC_SERRPENA | \
					 ALTR_A10_ECC_DERRPENA)
/* ECC Manager Defines */
#घोषणा A10_SYSMGR_ECC_INTMASK_SET_OFST   0x94
#घोषणा A10_SYSMGR_ECC_INTMASK_CLR_OFST   0x98
#घोषणा A10_SYSMGR_ECC_INTMASK_OCRAM      BIT(1)

#घोषणा ALTR_A10_ECC_INIT_WATCHDOG_10US   10000

अटल अंतरभूत व्योम ecc_set_bits(u32 bit_mask, व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr);

	value |= bit_mask;
	ग_लिखोl(value, ioaddr);
पूर्ण

अटल अंतरभूत व्योम ecc_clear_bits(u32 bit_mask, व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr);

	value &= ~bit_mask;
	ग_लिखोl(value, ioaddr);
पूर्ण

अटल अंतरभूत पूर्णांक ecc_test_bits(u32 bit_mask, व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr);

	वापस (value & bit_mask) ? 1 : 0;
पूर्ण

/*
 * This function uses the memory initialization block in the Arria10 ECC
 * controller to initialize/clear the entire memory data and ECC data.
 */
अटल पूर्णांक altr_init_memory_port(व्योम __iomem *ioaddr)
अणु
	पूर्णांक limit = ALTR_A10_ECC_INIT_WATCHDOG_10US;

	ecc_set_bits(ALTR_A10_ECC_INITA, (ioaddr + ALTR_A10_ECC_CTRL_OFST));
	जबतक (limit--) अणु
		अगर (ecc_test_bits(ALTR_A10_ECC_INITCOMPLETEA,
				  (ioaddr + ALTR_A10_ECC_INITSTAT_OFST)))
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (limit < 0)
		वापस -EBUSY;

	/* Clear any pending ECC पूर्णांकerrupts */
	ग_लिखोl(ALTR_A10_ECC_ERRPENA_MASK,
	       (ioaddr + ALTR_A10_ECC_INTSTAT_OFST));

	वापस 0;
पूर्ण

व्योम socfpga_init_arria10_ocram_ecc(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret = 0;
	व्योम __iomem *ecc_block_base;

	अगर (!sys_manager_base_addr) अणु
		pr_err("SOCFPGA: sys-mgr is not initialized\n");
		वापस;
	पूर्ण

	/* Find the OCRAM EDAC device tree node */
	np = of_find_compatible_node(शून्य, शून्य, "altr,socfpga-a10-ocram-ecc");
	अगर (!np) अणु
		pr_err("Unable to find socfpga-a10-ocram-ecc\n");
		वापस;
	पूर्ण

	/* Map the ECC Block */
	ecc_block_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!ecc_block_base) अणु
		pr_err("Unable to map OCRAM ECC block\n");
		वापस;
	पूर्ण

	/* Disable ECC */
	ग_लिखोl(ALTR_A10_OCRAM_ECC_EN_CTL,
	       sys_manager_base_addr + A10_SYSMGR_ECC_INTMASK_SET_OFST);
	ecc_clear_bits(ALTR_A10_ECC_SERRINTEN,
		       (ecc_block_base + ALTR_A10_ECC_ERRINTEN_OFST));
	ecc_clear_bits(ALTR_A10_OCRAM_ECC_EN_CTL,
		       (ecc_block_base + ALTR_A10_ECC_CTRL_OFST));

	/* Ensure all ग_लिखोs complete */
	wmb();

	/* Use HW initialization block to initialize memory क्रम ECC */
	ret = altr_init_memory_port(ecc_block_base);
	अगर (ret) अणु
		pr_err("ECC: cannot init OCRAM PORTA memory\n");
		जाओ निकास;
	पूर्ण

	/* Enable ECC */
	ecc_set_bits(ALTR_A10_OCRAM_ECC_EN_CTL,
		     (ecc_block_base + ALTR_A10_ECC_CTRL_OFST));
	ecc_set_bits(ALTR_A10_ECC_SERRINTEN,
		     (ecc_block_base + ALTR_A10_ECC_ERRINTEN_OFST));
	ग_लिखोl(ALTR_A10_OCRAM_ECC_EN_CTL,
	       sys_manager_base_addr + A10_SYSMGR_ECC_INTMASK_CLR_OFST);

	/* Ensure all ग_लिखोs complete */
	wmb();
निकास:
	iounmap(ecc_block_base);
पूर्ण
