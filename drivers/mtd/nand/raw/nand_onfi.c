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

#घोषणा ONFI_PARAM_PAGES 3

u16 onfi_crc16(u16 crc, u8 स्थिर *p, माप_प्रकार len)
अणु
	पूर्णांक i;
	जबतक (len--) अणु
		crc ^= *p++ << 8;
		क्रम (i = 0; i < 8; i++)
			crc = (crc << 1) ^ ((crc & 0x8000) ? 0x8005 : 0);
	पूर्ण

	वापस crc;
पूर्ण

/* Parse the Extended Parameter Page. */
अटल पूर्णांक nand_flash_detect_ext_param_page(काष्ठा nand_chip *chip,
					    काष्ठा nand_onfi_params *p)
अणु
	काष्ठा nand_device *base = &chip->base;
	काष्ठा nand_ecc_props requirements;
	काष्ठा onfi_ext_param_page *ep;
	काष्ठा onfi_ext_section *s;
	काष्ठा onfi_ext_ecc_info *ecc;
	uपूर्णांक8_t *cursor;
	पूर्णांक ret;
	पूर्णांक len;
	पूर्णांक i;

	len = le16_to_cpu(p->ext_param_page_length) * 16;
	ep = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	/*
	 * Use the Change Read Column command to skip the ONFI param pages and
	 * ensure we पढ़ो at the right location.
	 */
	ret = nand_change_पढ़ो_column_op(chip,
					 माप(*p) * p->num_of_param_pages,
					 ep, len, true);
	अगर (ret)
		जाओ ext_out;

	ret = -EINVAL;
	अगर ((onfi_crc16(ONFI_CRC_BASE, ((uपूर्णांक8_t *)ep) + 2, len - 2)
		!= le16_to_cpu(ep->crc))) अणु
		pr_debug("fail in the CRC.\n");
		जाओ ext_out;
	पूर्ण

	/*
	 * Check the signature.
	 * Do not strictly follow the ONFI spec, maybe changed in future.
	 */
	अगर (म_भेदन(ep->sig, "EPPS", 4)) अणु
		pr_debug("The signature is invalid.\n");
		जाओ ext_out;
	पूर्ण

	/* find the ECC section. */
	cursor = (uपूर्णांक8_t *)(ep + 1);
	क्रम (i = 0; i < ONFI_EXT_SECTION_MAX; i++) अणु
		s = ep->sections + i;
		अगर (s->type == ONFI_SECTION_TYPE_2)
			अवरोध;
		cursor += s->length * 16;
	पूर्ण
	अगर (i == ONFI_EXT_SECTION_MAX) अणु
		pr_debug("We can not find the ECC section.\n");
		जाओ ext_out;
	पूर्ण

	/* get the info we want. */
	ecc = (काष्ठा onfi_ext_ecc_info *)cursor;

	अगर (!ecc->codeword_size) अणु
		pr_debug("Invalid codeword size\n");
		जाओ ext_out;
	पूर्ण

	requirements.strength = ecc->ecc_bits;
	requirements.step_size = 1 << ecc->codeword_size;
	nanddev_set_ecc_requirements(base, &requirements);

	ret = 0;

ext_out:
	kमुक्त(ep);
	वापस ret;
पूर्ण

/*
 * Recover data with bit-wise majority
 */
अटल व्योम nand_bit_wise_majority(स्थिर व्योम **srcbufs,
				   अचिन्हित पूर्णांक nsrcbufs,
				   व्योम *dstbuf,
				   अचिन्हित पूर्णांक bufsize)
अणु
	पूर्णांक i, j, k;

	क्रम (i = 0; i < bufsize; i++) अणु
		u8 val = 0;

		क्रम (j = 0; j < 8; j++) अणु
			अचिन्हित पूर्णांक cnt = 0;

			क्रम (k = 0; k < nsrcbufs; k++) अणु
				स्थिर u8 *srcbuf = srcbufs[k];

				अगर (srcbuf[i] & BIT(j))
					cnt++;
			पूर्ण

			अगर (cnt > nsrcbufs / 2)
				val |= BIT(j);
		पूर्ण

		((u8 *)dstbuf)[i] = val;
	पूर्ण
पूर्ण

/*
 * Check अगर the न_अंकD chip is ONFI compliant, वापसs 1 अगर it is, 0 otherwise.
 */
पूर्णांक nand_onfi_detect(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;
	काष्ठा nand_onfi_params *p = शून्य, *pbuf;
	काष्ठा onfi_params *onfi;
	bool use_datain = false;
	पूर्णांक onfi_version = 0;
	अक्षर id[4];
	पूर्णांक i, ret, val;
	u16 crc;

	memorg = nanddev_get_memorg(&chip->base);

	/* Try ONFI क्रम unknown chip or LP */
	ret = nand_पढ़ोid_op(chip, 0x20, id, माप(id));
	अगर (ret || म_भेदन(id, "ONFI", 4))
		वापस 0;

	/* ONFI chip: allocate a buffer to hold its parameter page */
	pbuf = kzalloc((माप(*pbuf) * ONFI_PARAM_PAGES), GFP_KERNEL);
	अगर (!pbuf)
		वापस -ENOMEM;

	अगर (!nand_has_exec_op(chip) ||
	    !nand_पढ़ो_data_op(chip, &pbuf[0], माप(*pbuf), true, true))
		use_datain = true;

	क्रम (i = 0; i < ONFI_PARAM_PAGES; i++) अणु
		अगर (!i)
			ret = nand_पढ़ो_param_page_op(chip, 0, &pbuf[i],
						      माप(*pbuf));
		अन्यथा अगर (use_datain)
			ret = nand_पढ़ो_data_op(chip, &pbuf[i], माप(*pbuf),
						true, false);
		अन्यथा
			ret = nand_change_पढ़ो_column_op(chip, माप(*pbuf) * i,
							 &pbuf[i], माप(*pbuf),
							 true);
		अगर (ret) अणु
			ret = 0;
			जाओ मुक्त_onfi_param_page;
		पूर्ण

		crc = onfi_crc16(ONFI_CRC_BASE, (u8 *)&pbuf[i], 254);
		अगर (crc == le16_to_cpu(pbuf[i].crc)) अणु
			p = &pbuf[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ONFI_PARAM_PAGES) अणु
		स्थिर व्योम *srcbufs[ONFI_PARAM_PAGES];
		अचिन्हित पूर्णांक j;

		क्रम (j = 0; j < ONFI_PARAM_PAGES; j++)
			srcbufs[j] = pbuf + j;

		pr_warn("Could not find a valid ONFI parameter page, trying bit-wise majority to recover it\n");
		nand_bit_wise_majority(srcbufs, ONFI_PARAM_PAGES, pbuf,
				       माप(*pbuf));

		crc = onfi_crc16(ONFI_CRC_BASE, (u8 *)pbuf, 254);
		अगर (crc != le16_to_cpu(pbuf->crc)) अणु
			pr_err("ONFI parameter recovery failed, aborting\n");
			जाओ मुक्त_onfi_param_page;
		पूर्ण
		p = pbuf;
	पूर्ण

	अगर (chip->manufacturer.desc && chip->manufacturer.desc->ops &&
	    chip->manufacturer.desc->ops->fixup_onfi_param_page)
		chip->manufacturer.desc->ops->fixup_onfi_param_page(chip, p);

	/* Check version */
	val = le16_to_cpu(p->revision);
	अगर (val & ONFI_VERSION_2_3)
		onfi_version = 23;
	अन्यथा अगर (val & ONFI_VERSION_2_2)
		onfi_version = 22;
	अन्यथा अगर (val & ONFI_VERSION_2_1)
		onfi_version = 21;
	अन्यथा अगर (val & ONFI_VERSION_2_0)
		onfi_version = 20;
	अन्यथा अगर (val & ONFI_VERSION_1_0)
		onfi_version = 10;

	अगर (!onfi_version) अणु
		pr_info("unsupported ONFI version: %d\n", val);
		जाओ मुक्त_onfi_param_page;
	पूर्ण

	sanitize_string(p->manufacturer, माप(p->manufacturer));
	sanitize_string(p->model, माप(p->model));
	chip->parameters.model = kstrdup(p->model, GFP_KERNEL);
	अगर (!chip->parameters.model) अणु
		ret = -ENOMEM;
		जाओ मुक्त_onfi_param_page;
	पूर्ण

	memorg->pagesize = le32_to_cpu(p->byte_per_page);
	mtd->ग_लिखोsize = memorg->pagesize;

	/*
	 * pages_per_block and blocks_per_lun may not be a घातer-of-2 size
	 * (करोn't ask me who thought of this...). MTD assumes that these
	 * dimensions will be घातer-of-2, so just truncate the reमुख्यing area.
	 */
	memorg->pages_per_eraseblock =
			1 << (fls(le32_to_cpu(p->pages_per_block)) - 1);
	mtd->erasesize = memorg->pages_per_eraseblock * memorg->pagesize;

	memorg->oobsize = le16_to_cpu(p->spare_bytes_per_page);
	mtd->oobsize = memorg->oobsize;

	memorg->luns_per_target = p->lun_count;
	memorg->planes_per_lun = 1 << p->पूर्णांकerleaved_bits;

	/* See erasesize comment */
	memorg->eraseblocks_per_lun =
		1 << (fls(le32_to_cpu(p->blocks_per_lun)) - 1);
	memorg->max_bad_eraseblocks_per_lun = le32_to_cpu(p->blocks_per_lun);
	memorg->bits_per_cell = p->bits_per_cell;

	अगर (le16_to_cpu(p->features) & ONFI_FEATURE_16_BIT_BUS)
		chip->options |= न_अंकD_BUSWIDTH_16;

	अगर (p->ecc_bits != 0xff) अणु
		काष्ठा nand_ecc_props requirements = अणु
			.strength = p->ecc_bits,
			.step_size = 512,
		पूर्ण;

		nanddev_set_ecc_requirements(base, &requirements);
	पूर्ण अन्यथा अगर (onfi_version >= 21 &&
		(le16_to_cpu(p->features) & ONFI_FEATURE_EXT_PARAM_PAGE)) अणु

		/*
		 * The nand_flash_detect_ext_param_page() uses the
		 * Change Read Column command which maybe not supported
		 * by the chip->legacy.cmdfunc. So try to update the
		 * chip->legacy.cmdfunc now. We करो not replace user supplied
		 * command function.
		 */
		nand_legacy_adjust_cmdfunc(chip);

		/* The Extended Parameter Page is supported since ONFI 2.1. */
		अगर (nand_flash_detect_ext_param_page(chip, p))
			pr_warn("Failed to detect ONFI extended param page\n");
	पूर्ण अन्यथा अणु
		pr_warn("Could not retrieve ONFI ECC requirements\n");
	पूर्ण

	/* Save some parameters from the parameter page क्रम future use */
	अगर (le16_to_cpu(p->opt_cmd) & ONFI_OPT_CMD_SET_GET_FEATURES) अणु
		chip->parameters.supports_set_get_features = true;
		biपंचांगap_set(chip->parameters.get_feature_list,
			   ONFI_FEATURE_ADDR_TIMING_MODE, 1);
		biपंचांगap_set(chip->parameters.set_feature_list,
			   ONFI_FEATURE_ADDR_TIMING_MODE, 1);
	पूर्ण

	onfi = kzalloc(माप(*onfi), GFP_KERNEL);
	अगर (!onfi) अणु
		ret = -ENOMEM;
		जाओ मुक्त_model;
	पूर्ण

	onfi->version = onfi_version;
	onfi->tPROG = le16_to_cpu(p->t_prog);
	onfi->tBERS = le16_to_cpu(p->t_bers);
	onfi->tR = le16_to_cpu(p->t_r);
	onfi->tCCS = le16_to_cpu(p->t_ccs);
	onfi->async_timing_mode = le16_to_cpu(p->async_timing_mode);
	onfi->venकरोr_revision = le16_to_cpu(p->venकरोr_revision);
	स_नकल(onfi->venकरोr, p->venकरोr, माप(p->venकरोr));
	chip->parameters.onfi = onfi;

	/* Identअगरication करोne, मुक्त the full ONFI parameter page and निकास */
	kमुक्त(pbuf);

	वापस 1;

मुक्त_model:
	kमुक्त(chip->parameters.model);
मुक्त_onfi_param_page:
	kमुक्त(pbuf);

	वापस ret;
पूर्ण
