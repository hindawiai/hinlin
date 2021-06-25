<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Toradex AG
 *
 * Author: Marcel Ziswiler <marcel.ziswiler@toradex.com>
 */

#समावेश <linux/mtd/rawnand.h>
#समावेश "internals.h"

अटल व्योम esmt_nand_decode_id(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;
	काष्ठा nand_ecc_props requirements = अणुपूर्ण;

	nand_decode_ext_id(chip);

	/* Extract ECC requirements from 5th id byte. */
	अगर (chip->id.len >= 5 && nand_is_slc(chip)) अणु
		requirements.step_size = 512;
		चयन (chip->id.data[4] & 0x3) अणु
		हाल 0x0:
			requirements.strength = 4;
			अवरोध;
		हाल 0x1:
			requirements.strength = 2;
			अवरोध;
		हाल 0x2:
			requirements.strength = 1;
			अवरोध;
		शेष:
			WARN(1, "Could not get ECC info");
			requirements.step_size = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	nanddev_set_ecc_requirements(base, &requirements);
पूर्ण

अटल पूर्णांक esmt_nand_init(काष्ठा nand_chip *chip)
अणु
	अगर (nand_is_slc(chip))
		/*
		 * It is known that some ESMT SLC न_अंकDs have been shipped
		 * with the factory bad block markers in the first or last page
		 * of the block, instead of the first or second page. To be on
		 * the safe side, let's check all three locations.
		 */
		chip->options |= न_अंकD_BBM_FIRSTPAGE | न_अंकD_BBM_SECONDPAGE |
				 न_अंकD_BBM_LASTPAGE;

	वापस 0;
पूर्ण

स्थिर काष्ठा nand_manufacturer_ops esmt_nand_manuf_ops = अणु
	.detect = esmt_nand_decode_id,
	.init = esmt_nand_init,
पूर्ण;
