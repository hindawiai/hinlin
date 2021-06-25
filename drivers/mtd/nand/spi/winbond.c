<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 exceet electronics GmbH
 *
 * Authors:
 *	Frieder Schrempf <frieder.schrempf@exceet.de>
 *	Boris Brezillon <boris.brezillon@bootlin.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/spinand.h>

#घोषणा SPIन_अंकD_MFR_WINBOND		0xEF

#घोषणा WINBOND_CFG_BUF_READ		BIT(3)

अटल SPIन_अंकD_OP_VARIANTS(पढ़ो_cache_variants,
		SPIन_अंकD_PAGE_READ_FROM_CACHE_QUADIO_OP(0, 2, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_DUALIO_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(true, 0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(false, 0, 1, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(ग_लिखो_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(true, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(true, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(update_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(false, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(false, 0, शून्य, 0));

अटल पूर्णांक w25m02gv_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *region)
अणु
	अगर (section > 3)
		वापस -दुस्फल;

	region->offset = (16 * section) + 8;
	region->length = 8;

	वापस 0;
पूर्ण

अटल पूर्णांक w25m02gv_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *region)
अणु
	अगर (section > 3)
		वापस -दुस्फल;

	region->offset = (16 * section) + 2;
	region->length = 6;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops w25m02gv_ooblayout = अणु
	.ecc = w25m02gv_ooblayout_ecc,
	.मुक्त = w25m02gv_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक w25m02gv_select_target(काष्ठा spinand_device *spinand,
				  अचिन्हित पूर्णांक target)
अणु
	काष्ठा spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(0xc2, 1),
					  SPI_MEM_OP_NO_ADDR,
					  SPI_MEM_OP_NO_DUMMY,
					  SPI_MEM_OP_DATA_OUT(1,
							spinand->scratchbuf,
							1));

	*spinand->scratchbuf = target;
	वापस spi_mem_exec_op(spinand->spimem, &op);
पूर्ण

अटल स्थिर काष्ठा spinand_info winbond_spinand_table[] = अणु
	SPIन_अंकD_INFO("W25M02GV",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xab),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 1024, 20, 1, 1, 2),
		     न_अंकD_ECCREQ(1, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&w25m02gv_ooblayout, शून्य),
		     SPIन_अंकD_SELECT_TARGET(w25m02gv_select_target)),
	SPIन_अंकD_INFO("W25N01GV",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xaa),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(1, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&w25m02gv_ooblayout, शून्य)),
पूर्ण;

अटल पूर्णांक winbond_spinand_init(काष्ठा spinand_device *spinand)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	अचिन्हित पूर्णांक i;

	/*
	 * Make sure all dies are in buffer पढ़ो mode and not continuous पढ़ो
	 * mode.
	 */
	क्रम (i = 0; i < nand->memorg.ntarमाला_लो; i++) अणु
		spinand_select_target(spinand, i);
		spinand_upd_cfg(spinand, WINBOND_CFG_BUF_READ,
				WINBOND_CFG_BUF_READ);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spinand_manufacturer_ops winbond_spinand_manuf_ops = अणु
	.init = winbond_spinand_init,
पूर्ण;

स्थिर काष्ठा spinand_manufacturer winbond_spinand_manufacturer = अणु
	.id = SPIन_अंकD_MFR_WINBOND,
	.name = "Winbond",
	.chips = winbond_spinand_table,
	.nchips = ARRAY_SIZE(winbond_spinand_table),
	.ops = &winbond_spinand_manuf_ops,
पूर्ण;
