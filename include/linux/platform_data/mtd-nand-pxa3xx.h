<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_PXA3XX_न_अंकD_H
#घोषणा __ASM_ARCH_PXA3XX_न_अंकD_H

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

/*
 * Current pxa3xx_nand controller has two chip select which both be workable but
 * historically all platक्रमms reमुख्यing on platक्रमm data used only one. Switch
 * to device tree अगर you need more.
 */
काष्ठा pxa3xx_nand_platक्रमm_data अणु
	/* Keep OBM/bootloader NFC timing configuration */
	bool keep_config;
	/* Use a flash-based bad block table */
	bool flash_bbt;
	/* Requested ECC strength and ECC step size */
	पूर्णांक ecc_strength, ecc_step_size;
	/* Partitions */
	स्थिर काष्ठा mtd_partition *parts;
	अचिन्हित पूर्णांक nr_parts;
पूर्ण;

बाह्य व्योम pxa3xx_set_nand_info(काष्ठा pxa3xx_nand_platक्रमm_data *info);

#पूर्ण_अगर /* __ASM_ARCH_PXA3XX_न_अंकD_H */
