<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2000 Steven J. Hill (sjhill@realitydiluted.com)
 *		  2002-2006 Thomas Gleixner (tglx@linutronix.de)
 *
 *  Credits:
 *	David Woodhouse क्रम adding multichip support
 *
 *	Aleph One Ltd. and Toby Churchill Ltd. क्रम supporting the
 *	rework क्रम 2K page size chips
 *
 * This file contains all ONFI helpers.
 */

#समावेश <linux/slab.h>

#समावेश "internals.h"

#घोषणा JEDEC_PARAM_PAGES 3

/*
 * Check अगर the न_अंकD chip is JEDEC compliant, वापसs 1 अगर it is, 0 otherwise.
 */
पूर्णांक nand_jedec_detect(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;
	काष्ठा nand_jedec_params *p;
	काष्ठा jedec_ecc_info *ecc;
	bool use_datain = false;
	पूर्णांक jedec_version = 0;
	अक्षर id[5];
	पूर्णांक i, val, ret;
	u16 crc;

	memorg = nanddev_get_memorg(&chip->base);

	/* Try JEDEC क्रम unknown chip or LP */
	ret = nand_पढ़ोid_op(chip, 0x40, id, माप(id));
	अगर (ret || म_भेदन(id, "JEDEC", माप(id)))
		वापस 0;

	/* JEDEC chip: allocate a buffer to hold its parameter page */
	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	अगर (!nand_has_exec_op(chip) ||
	    !nand_पढ़ो_data_op(chip, p, माप(*p), true, true))
		use_datain = true;

	क्रम (i = 0; i < JEDEC_PARAM_PAGES; i++) अणु
		अगर (!i)
			ret = nand_पढ़ो_param_page_op(chip, 0x40, p,
						      माप(*p));
		अन्यथा अगर (use_datain)
			ret = nand_पढ़ो_data_op(chip, p, माप(*p), true,
						false);
		अन्यथा
			ret = nand_change_पढ़ो_column_op(chip, माप(*p) * i,
							 p, माप(*p), true);
		अगर (ret) अणु
			ret = 0;
			जाओ मुक्त_jedec_param_page;
		पूर्ण

		crc = onfi_crc16(ONFI_CRC_BASE, (u8 *)p, 510);
		अगर (crc == le16_to_cpu(p->crc))
			अवरोध;
	पूर्ण

	अगर (i == JEDEC_PARAM_PAGES) अणु
		pr_err("Could not find valid JEDEC parameter page; aborting\n");
		जाओ मुक्त_jedec_param_page;
	पूर्ण

	/* Check version */
	val = le16_to_cpu(p->revision);
	अगर (val & (1 << 2))
		jedec_version = 10;
	अन्यथा अगर (val & (1 << 1))
		jedec_version = 1; /* venकरोr specअगरic version */

	अगर (!jedec_version) अणु
		pr_info("unsupported JEDEC version: %d\n", val);
		जाओ मुक्त_jedec_param_page;
	पूर्ण

	sanitize_string(p->manufacturer, माप(p->manufacturer));
	sanitize_string(p->model, माप(p->model));
	chip->parameters.model = kstrdup(p->model, GFP_KERNEL);
	अगर (!chip->parameters.model) अणु
		ret = -ENOMEM;
		जाओ मुक्त_jedec_param_page;
	पूर्ण

	memorg->pagesize = le32_to_cpu(p->byte_per_page);
	mtd->ग_लिखोsize = memorg->pagesize;

	/* Please reference to the comment क्रम nand_flash_detect_onfi. */
	memorg->pages_per_eraseblock =
			1 << (fls(le32_to_cpu(p->pages_per_block)) - 1);
	mtd->erasesize = memorg->pages_per_eraseblock * memorg->pagesize;

	memorg->oobsize = le16_to_cpu(p->spare_bytes_per_page);
	mtd->oobsize = memorg->oobsize;

	memorg->luns_per_target = p->lun_count;
	memorg->planes_per_lun = 1 << p->multi_plane_addr;

	/* Please reference to the comment क्रम nand_flash_detect_onfi. */
	memorg->eraseblocks_per_lun =
		1 << (fls(le32_to_cpu(p->blocks_per_lun)) - 1);
	memorg->bits_per_cell = p->bits_per_cell;

	अगर (le16_to_cpu(p->features) & JEDEC_FEATURE_16_BIT_BUS)
		chip->options |= न_अंकD_BUSWIDTH_16;

	/* ECC info */
	ecc = &p->ecc_info[0];

	अगर (ecc->codeword_size >= 9) अणु
		काष्ठा nand_ecc_props requirements = अणु
			.strength = ecc->ecc_bits,
			.step_size = 1 << ecc->codeword_size,
		पूर्ण;

		nanddev_set_ecc_requirements(base, &requirements);
	पूर्ण अन्यथा अणु
		pr_warn("Invalid codeword size\n");
	पूर्ण

	ret = 1;

मुक्त_jedec_param_page:
	kमुक्त(p);
	वापस ret;
पूर्ण
