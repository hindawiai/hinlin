<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Free Electrons
 * Copyright (C) 2017 NextThing Co
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश "internals.h"

अटल व्योम samsung_nand_decode_id(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;
	काष्ठा nand_ecc_props requirements = अणुपूर्ण;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;

	memorg = nanddev_get_memorg(&chip->base);

	/* New Samsung (6 byte ID): Samsung K9GAG08U0F (p.44) */
	अगर (chip->id.len == 6 && !nand_is_slc(chip) &&
	    chip->id.data[5] != 0x00) अणु
		u8 extid = chip->id.data[3];

		/* Get pagesize */
		memorg->pagesize = 2048 << (extid & 0x03);
		mtd->ग_लिखोsize = memorg->pagesize;

		extid >>= 2;

		/* Get oobsize */
		चयन (((extid >> 2) & 0x4) | (extid & 0x3)) अणु
		हाल 1:
			memorg->oobsize = 128;
			अवरोध;
		हाल 2:
			memorg->oobsize = 218;
			अवरोध;
		हाल 3:
			memorg->oobsize = 400;
			अवरोध;
		हाल 4:
			memorg->oobsize = 436;
			अवरोध;
		हाल 5:
			memorg->oobsize = 512;
			अवरोध;
		हाल 6:
			memorg->oobsize = 640;
			अवरोध;
		शेष:
			/*
			 * We should never reach this हाल, but अगर that
			 * happens, this probably means Samsung decided to use
			 * a dअगरferent extended ID क्रमmat, and we should find
			 * a way to support it.
			 */
			WARN(1, "Invalid OOB size value");
			अवरोध;
		पूर्ण

		mtd->oobsize = memorg->oobsize;

		/* Get blocksize */
		extid >>= 2;
		memorg->pages_per_eraseblock = (128 * 1024) <<
					       (((extid >> 1) & 0x04) |
						(extid & 0x03)) /
					       memorg->pagesize;
		mtd->erasesize = (128 * 1024) <<
				 (((extid >> 1) & 0x04) | (extid & 0x03));

		/* Extract ECC requirements from 5th id byte*/
		extid = (chip->id.data[4] >> 4) & 0x07;
		अगर (extid < 5) अणु
			requirements.step_size = 512;
			requirements.strength = 1 << extid;
		पूर्ण अन्यथा अणु
			requirements.step_size = 1024;
			चयन (extid) अणु
			हाल 5:
				requirements.strength = 24;
				अवरोध;
			हाल 6:
				requirements.strength = 40;
				अवरोध;
			हाल 7:
				requirements.strength = 60;
				अवरोध;
			शेष:
				WARN(1, "Could not decode ECC info");
				requirements.step_size = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		nand_decode_ext_id(chip);

		अगर (nand_is_slc(chip)) अणु
			चयन (chip->id.data[1]) अणु
			/* K9F4G08U0D-S[I|C]B0(T00) */
			हाल 0xDC:
				requirements.step_size = 512;
				requirements.strength = 1;
				अवरोध;

			/* K9F1G08U0E 21nm chips करो not support subpage ग_लिखो */
			हाल 0xF1:
				अगर (chip->id.len > 4 &&
				    (chip->id.data[4] & GENMASK(1, 0)) == 0x1)
					chip->options |= न_अंकD_NO_SUBPAGE_WRITE;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	nanddev_set_ecc_requirements(base, &requirements);
पूर्ण

अटल पूर्णांक samsung_nand_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (mtd->ग_लिखोsize > 512)
		chip->options |= न_अंकD_SAMSUNG_LP_OPTIONS;

	अगर (!nand_is_slc(chip))
		chip->options |= न_अंकD_BBM_LASTPAGE;
	अन्यथा
		chip->options |= न_अंकD_BBM_FIRSTPAGE | न_अंकD_BBM_SECONDPAGE;

	वापस 0;
पूर्ण

स्थिर काष्ठा nand_manufacturer_ops samsung_nand_manuf_ops = अणु
	.detect = samsung_nand_decode_id,
	.init = samsung_nand_init,
पूर्ण;
