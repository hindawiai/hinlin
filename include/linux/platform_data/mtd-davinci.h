<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * mach-davinci/nand.h
 *
 * Copyright तऊ 2006 Texas Instruments.
 *
 * Ported to 2.6.23 Copyright तऊ 2008 by
 *   Sander Huijsen <Shuijsen@optelecom-nkf.com>
 *   Troy Kisky <troy.kisky@boundarydevices.com>
 *   Dirk Behme <Dirk.Behme@gmail.com>
 *
 * --------------------------------------------------------------------------
 */

#अगर_अघोषित __ARCH_ARM_DAVINCI_न_अंकD_H
#घोषणा __ARCH_ARM_DAVINCI_न_अंकD_H

#समावेश <linux/mtd/rawnand.h>

#घोषणा न_अंकDFCR_OFFSET		0x60
#घोषणा न_अंकDFSR_OFFSET		0x64
#घोषणा न_अंकDF1ECC_OFFSET	0x70

/* 4-bit ECC syndrome रेजिस्टरs */
#घोषणा न_अंकD_4BIT_ECC_LOAD_OFFSET	0xbc
#घोषणा न_अंकD_4BIT_ECC1_OFFSET		0xc0
#घोषणा न_अंकD_4BIT_ECC2_OFFSET		0xc4
#घोषणा न_अंकD_4BIT_ECC3_OFFSET		0xc8
#घोषणा न_अंकD_4BIT_ECC4_OFFSET		0xcc
#घोषणा न_अंकD_ERR_ADD1_OFFSET		0xd0
#घोषणा न_अंकD_ERR_ADD2_OFFSET		0xd4
#घोषणा न_अंकD_ERR_ERRVAL1_OFFSET		0xd8
#घोषणा न_अंकD_ERR_ERRVAL2_OFFSET		0xdc

/* NOTE:  boards करोn't need to use these address bits
 * क्रम ALE/CLE unless they support booting from न_अंकD.
 * They're used unless platक्रमm data overrides them.
 */
#घोषणा	MASK_ALE		0x08
#घोषणा	MASK_CLE		0x10

काष्ठा davinci_nand_pdata अणु		/* platक्रमm_data */
	uपूर्णांक32_t		mask_ale;
	uपूर्णांक32_t		mask_cle;

	/*
	 * 0-indexed chip-select number of the asynchronous
	 * पूर्णांकerface to which the न_अंकD device has been connected.
	 *
	 * So, अगर you have न_अंकD connected to CS3 of DA850, you
	 * will pass '1' here. Since the asynchronous पूर्णांकerface
	 * on DA850 starts from CS2.
	 */
	uपूर्णांक32_t		core_chipsel;

	/* क्रम packages using two chipselects */
	uपूर्णांक32_t		mask_chipsel;

	/* board's शेष अटल partition info */
	काष्ठा mtd_partition	*parts;
	अचिन्हित		nr_parts;

	/* none  == न_अंकD_ECC_ENGINE_TYPE_NONE (strongly *not* advised!!)
	 * soft  == न_अंकD_ECC_ENGINE_TYPE_SOFT
	 * अन्यथा  == न_अंकD_ECC_ENGINE_TYPE_ON_HOST, according to ecc_bits
	 *
	 * All DaVinci-family chips support 1-bit hardware ECC.
	 * Newer ones also support 4-bit ECC, but are awkward
	 * using it with large page chips.
	 */
	क्रमागत nand_ecc_engine_type engine_type;
	क्रमागत nand_ecc_placement ecc_placement;
	u8			ecc_bits;

	/* e.g. न_अंकD_BUSWIDTH_16 */
	अचिन्हित		options;
	/* e.g. न_अंकD_BBT_USE_FLASH */
	अचिन्हित		bbt_options;

	/* Main and mirror bbt descriptor overrides */
	काष्ठा nand_bbt_descr	*bbt_td;
	काष्ठा nand_bbt_descr	*bbt_md;

	/* Access timings */
	काष्ठा davinci_aemअगर_timing	*timing;
पूर्ण;

#पूर्ण_अगर	/* __ARCH_ARM_DAVINCI_न_अंकD_H */
