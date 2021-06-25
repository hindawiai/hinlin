<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Free Electrons
 * Copyright (C) 2017 NextThing Co
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश "internals.h"

अटल व्योम amd_nand_decode_id(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;

	memorg = nanddev_get_memorg(&chip->base);

	nand_decode_ext_id(chip);

	/*
	 * Check क्रम Spansion/AMD ID + repeating 5th, 6th byte since
	 * some Spansion chips have erasesize that conflicts with size
	 * listed in nand_ids table.
	 * Data sheet (5 byte ID): Spansion S30ML-P ORन_अंकD (p.39)
	 */
	अगर (chip->id.data[4] != 0x00 && chip->id.data[5] == 0x00 &&
	    chip->id.data[6] == 0x00 && chip->id.data[7] == 0x00 &&
	    memorg->pagesize == 512) अणु
		memorg->pages_per_eraseblock = 256;
		memorg->pages_per_eraseblock <<= ((chip->id.data[3] & 0x03) << 1);
		mtd->erasesize = memorg->pages_per_eraseblock *
				 memorg->pagesize;
	पूर्ण
पूर्ण

अटल पूर्णांक amd_nand_init(काष्ठा nand_chip *chip)
अणु
	अगर (nand_is_slc(chip))
		/*
		 * According to the datasheet of some Cypress SLC न_अंकDs,
		 * the bad block markers can be in the first, second or last
		 * page of a block. So let's check all three locations.
		 */
		chip->options |= न_अंकD_BBM_FIRSTPAGE | न_अंकD_BBM_SECONDPAGE |
				 न_अंकD_BBM_LASTPAGE;

	वापस 0;
पूर्ण

स्थिर काष्ठा nand_manufacturer_ops amd_nand_manuf_ops = अणु
	.detect = amd_nand_decode_id,
	.init = amd_nand_init,
पूर्ण;
