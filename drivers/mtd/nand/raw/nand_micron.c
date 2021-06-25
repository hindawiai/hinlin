<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Free Electrons
 * Copyright (C) 2017 NextThing Co
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/slab.h>

#समावेश "internals.h"

/*
 * Special Micron status bit 3 indicates that the block has been
 * corrected by on-die ECC and should be rewritten.
 */
#घोषणा न_अंकD_ECC_STATUS_WRITE_RECOMMENDED	BIT(3)

/*
 * On chips with 8-bit ECC and additional bit can be used to distinguish
 * हालs where a errors were corrected without needing a reग_लिखो
 *
 * Bit 4 Bit 3 Bit 0 Description
 * ----- ----- ----- -----------
 * 0     0     0     No Errors
 * 0     0     1     Multiple uncorrected errors
 * 0     1     0     4 - 6 errors corrected, recommend reग_लिखो
 * 0     1     1     Reserved
 * 1     0     0     1 - 3 errors corrected
 * 1     0     1     Reserved
 * 1     1     0     7 - 8 errors corrected, recommend reग_लिखो
 */
#घोषणा न_अंकD_ECC_STATUS_MASK		(BIT(4) | BIT(3) | BIT(0))
#घोषणा न_अंकD_ECC_STATUS_UNCORRECTABLE	BIT(0)
#घोषणा न_अंकD_ECC_STATUS_4_6_CORRECTED	BIT(3)
#घोषणा न_अंकD_ECC_STATUS_1_3_CORRECTED	BIT(4)
#घोषणा न_अंकD_ECC_STATUS_7_8_CORRECTED	(BIT(4) | BIT(3))

काष्ठा nand_onfi_venकरोr_micron अणु
	u8 two_plane_पढ़ो;
	u8 पढ़ो_cache;
	u8 पढ़ो_unique_id;
	u8 dq_imped;
	u8 dq_imped_num_settings;
	u8 dq_imped_feat_addr;
	u8 rb_pullकरोwn_strength;
	u8 rb_pullकरोwn_strength_feat_addr;
	u8 rb_pullकरोwn_strength_num_settings;
	u8 otp_mode;
	u8 otp_page_start;
	u8 otp_data_prot_addr;
	u8 otp_num_pages;
	u8 otp_feat_addr;
	u8 पढ़ो_retry_options;
	u8 reserved[72];
	u8 param_revision;
पूर्ण __packed;

काष्ठा micron_on_die_ecc अणु
	bool क्रमced;
	bool enabled;
	व्योम *rawbuf;
पूर्ण;

काष्ठा micron_nand अणु
	काष्ठा micron_on_die_ecc ecc;
पूर्ण;

अटल पूर्णांक micron_nand_setup_पढ़ो_retry(काष्ठा nand_chip *chip, पूर्णांक retry_mode)
अणु
	u8 feature[ONFI_SUBFEATURE_PARAM_LEN] = अणुretry_modeपूर्ण;

	वापस nand_set_features(chip, ONFI_FEATURE_ADDR_READ_RETRY, feature);
पूर्ण

/*
 * Configure chip properties from Micron venकरोr-specअगरic ONFI table
 */
अटल पूर्णांक micron_nand_onfi_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_parameters *p = &chip->parameters;

	अगर (p->onfi) अणु
		काष्ठा nand_onfi_venकरोr_micron *micron = (व्योम *)p->onfi->venकरोr;

		chip->पढ़ो_retries = micron->पढ़ो_retry_options;
		chip->ops.setup_पढ़ो_retry = micron_nand_setup_पढ़ो_retry;
	पूर्ण

	अगर (p->supports_set_get_features) अणु
		set_bit(ONFI_FEATURE_ADDR_READ_RETRY, p->set_feature_list);
		set_bit(ONFI_FEATURE_ON_DIE_ECC, p->set_feature_list);
		set_bit(ONFI_FEATURE_ADDR_READ_RETRY, p->get_feature_list);
		set_bit(ONFI_FEATURE_ON_DIE_ECC, p->get_feature_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक micron_nand_on_die_4_ooblayout_ecc(काष्ठा mtd_info *mtd,
					      पूर्णांक section,
					      काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section >= 4)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 8;
	oobregion->length = 8;

	वापस 0;
पूर्ण

अटल पूर्णांक micron_nand_on_die_4_ooblayout_मुक्त(काष्ठा mtd_info *mtd,
					       पूर्णांक section,
					       काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section >= 4)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 2;
	oobregion->length = 6;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops micron_nand_on_die_4_ooblayout_ops = अणु
	.ecc = micron_nand_on_die_4_ooblayout_ecc,
	.मुक्त = micron_nand_on_die_4_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक micron_nand_on_die_8_ooblayout_ecc(काष्ठा mtd_info *mtd,
					      पूर्णांक section,
					      काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = mtd->oobsize - chip->ecc.total;
	oobregion->length = chip->ecc.total;

	वापस 0;
पूर्ण

अटल पूर्णांक micron_nand_on_die_8_ooblayout_मुक्त(काष्ठा mtd_info *mtd,
					       पूर्णांक section,
					       काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 2;
	oobregion->length = mtd->oobsize - chip->ecc.total - 2;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops micron_nand_on_die_8_ooblayout_ops = अणु
	.ecc = micron_nand_on_die_8_ooblayout_ecc,
	.मुक्त = micron_nand_on_die_8_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक micron_nand_on_die_ecc_setup(काष्ठा nand_chip *chip, bool enable)
अणु
	काष्ठा micron_nand *micron = nand_get_manufacturer_data(chip);
	u8 feature[ONFI_SUBFEATURE_PARAM_LEN] = अणु 0, पूर्ण;
	पूर्णांक ret;

	अगर (micron->ecc.क्रमced)
		वापस 0;

	अगर (micron->ecc.enabled == enable)
		वापस 0;

	अगर (enable)
		feature[0] |= ONFI_FEATURE_ON_DIE_ECC_EN;

	ret = nand_set_features(chip, ONFI_FEATURE_ON_DIE_ECC, feature);
	अगर (!ret)
		micron->ecc.enabled = enable;

	वापस ret;
पूर्ण

अटल पूर्णांक micron_nand_on_die_ecc_status_4(काष्ठा nand_chip *chip, u8 status,
					   व्योम *buf, पूर्णांक page,
					   पूर्णांक oob_required)
अणु
	काष्ठा micron_nand *micron = nand_get_manufacturer_data(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित पूर्णांक step, max_bitflips = 0;
	bool use_datain = false;
	पूर्णांक ret;

	अगर (!(status & न_अंकD_ECC_STATUS_WRITE_RECOMMENDED)) अणु
		अगर (status & न_अंकD_STATUS_FAIL)
			mtd->ecc_stats.failed++;

		वापस 0;
	पूर्ण

	/*
	 * The पूर्णांकernal ECC करोesn't tell us the number of bitflips that have
	 * been corrected, but tells us अगर it recommends to reग_लिखो the block.
	 * If it's the हाल, we need to पढ़ो the page in raw mode and compare
	 * its content to the corrected version to extract the actual number of
	 * bitflips.
	 * But beक्रमe we करो that, we must make sure we have all OOB bytes पढ़ो
	 * in non-raw mode, even अगर the user did not request those bytes.
	 */
	अगर (!oob_required) अणु
		/*
		 * We first check which operation is supported by the controller
		 * beक्रमe running it. This trick makes it possible to support
		 * all controllers, even the most स्थिरraपूर्णांकs, without almost
		 * any perक्रमmance hit.
		 *
		 * TODO: could be enhanced to aव्योम repeating the same check
		 * over and over in the fast path.
		 */
		अगर (!nand_has_exec_op(chip) ||
		    !nand_पढ़ो_data_op(chip, chip->oob_poi, mtd->oobsize, false,
				       true))
			use_datain = true;

		अगर (use_datain)
			ret = nand_पढ़ो_data_op(chip, chip->oob_poi,
						mtd->oobsize, false, false);
		अन्यथा
			ret = nand_change_पढ़ो_column_op(chip, mtd->ग_लिखोsize,
							 chip->oob_poi,
							 mtd->oobsize, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	micron_nand_on_die_ecc_setup(chip, false);

	ret = nand_पढ़ो_page_op(chip, page, 0, micron->ecc.rawbuf,
				mtd->ग_लिखोsize + mtd->oobsize);
	अगर (ret)
		वापस ret;

	क्रम (step = 0; step < chip->ecc.steps; step++) अणु
		अचिन्हित पूर्णांक offs, i, nbitflips = 0;
		u8 *rawbuf, *corrbuf;

		offs = step * chip->ecc.size;
		rawbuf = micron->ecc.rawbuf + offs;
		corrbuf = buf + offs;

		क्रम (i = 0; i < chip->ecc.size; i++)
			nbitflips += hweight8(corrbuf[i] ^ rawbuf[i]);

		offs = (step * 16) + 4;
		rawbuf = micron->ecc.rawbuf + mtd->ग_लिखोsize + offs;
		corrbuf = chip->oob_poi + offs;

		क्रम (i = 0; i < chip->ecc.bytes + 4; i++)
			nbitflips += hweight8(corrbuf[i] ^ rawbuf[i]);

		अगर (WARN_ON(nbitflips > chip->ecc.strength))
			वापस -EINVAL;

		max_bitflips = max(nbitflips, max_bitflips);
		mtd->ecc_stats.corrected += nbitflips;
	पूर्ण

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक micron_nand_on_die_ecc_status_8(काष्ठा nand_chip *chip, u8 status)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/*
	 * With 8/512 we have more inक्रमmation but still करोn't know precisely
	 * how many bit-flips were seen.
	 */
	चयन (status & न_अंकD_ECC_STATUS_MASK) अणु
	हाल न_अंकD_ECC_STATUS_UNCORRECTABLE:
		mtd->ecc_stats.failed++;
		वापस 0;
	हाल न_अंकD_ECC_STATUS_1_3_CORRECTED:
		mtd->ecc_stats.corrected += 3;
		वापस 3;
	हाल न_अंकD_ECC_STATUS_4_6_CORRECTED:
		mtd->ecc_stats.corrected += 6;
		/* reग_लिखो recommended */
		वापस 6;
	हाल न_अंकD_ECC_STATUS_7_8_CORRECTED:
		mtd->ecc_stats.corrected += 8;
		/* reग_लिखो recommended */
		वापस 8;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
micron_nand_पढ़ो_page_on_die_ecc(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				 पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	bool use_datain = false;
	u8 status;
	पूर्णांक ret, max_bitflips = 0;

	ret = micron_nand_on_die_ecc_setup(chip, true);
	अगर (ret)
		वापस ret;

	ret = nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		जाओ out;

	ret = nand_status_op(chip, &status);
	अगर (ret)
		जाओ out;

	/*
	 * We first check which operation is supported by the controller beक्रमe
	 * running it. This trick makes it possible to support all controllers,
	 * even the most स्थिरraपूर्णांकs, without almost any perक्रमmance hit.
	 *
	 * TODO: could be enhanced to aव्योम repeating the same check over and
	 * over in the fast path.
	 */
	अगर (!nand_has_exec_op(chip) ||
	    !nand_पढ़ो_data_op(chip, buf, mtd->ग_लिखोsize, false, true))
		use_datain = true;

	अगर (use_datain) अणु
		ret = nand_निकास_status_op(chip);
		अगर (ret)
			जाओ out;

		ret = nand_पढ़ो_data_op(chip, buf, mtd->ग_लिखोsize, false,
					false);
		अगर (!ret && oob_required)
			ret = nand_पढ़ो_data_op(chip, chip->oob_poi,
						mtd->oobsize, false, false);
	पूर्ण अन्यथा अणु
		ret = nand_change_पढ़ो_column_op(chip, 0, buf, mtd->ग_लिखोsize,
						 false);
		अगर (!ret && oob_required)
			ret = nand_change_पढ़ो_column_op(chip, mtd->ग_लिखोsize,
							 chip->oob_poi,
							 mtd->oobsize, false);
	पूर्ण

	अगर (chip->ecc.strength == 4)
		max_bitflips = micron_nand_on_die_ecc_status_4(chip, status,
							       buf, page,
							       oob_required);
	अन्यथा
		max_bitflips = micron_nand_on_die_ecc_status_8(chip, status);

out:
	micron_nand_on_die_ecc_setup(chip, false);

	वापस ret ? ret : max_bitflips;
पूर्ण

अटल पूर्णांक
micron_nand_ग_लिखो_page_on_die_ecc(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	पूर्णांक ret;

	ret = micron_nand_on_die_ecc_setup(chip, true);
	अगर (ret)
		वापस ret;

	ret = nand_ग_लिखो_page_raw(chip, buf, oob_required, page);
	micron_nand_on_die_ecc_setup(chip, false);

	वापस ret;
पूर्ण

क्रमागत अणु
	/* The न_अंकD flash करोesn't support on-die ECC */
	MICRON_ON_DIE_UNSUPPORTED,

	/*
	 * The न_अंकD flash supports on-die ECC and it can be
	 * enabled/disabled by a set features command.
	 */
	MICRON_ON_DIE_SUPPORTED,

	/*
	 * The न_अंकD flash supports on-die ECC, and it cannot be
	 * disabled.
	 */
	MICRON_ON_DIE_MANDATORY,
पूर्ण;

#घोषणा MICRON_ID_INTERNAL_ECC_MASK	GENMASK(1, 0)
#घोषणा MICRON_ID_ECC_ENABLED		BIT(7)

/*
 * Try to detect अगर the न_अंकD support on-die ECC. To करो this, we enable
 * the feature, and पढ़ो back अगर it has been enabled as expected. We
 * also check अगर it can be disabled, because some Micron न_अंकDs करो not
 * allow disabling the on-die ECC and we करोn't support such न_अंकDs क्रम
 * now.
 *
 * This function also has the side effect of disabling on-die ECC अगर
 * it had been left enabled by the firmware/bootloader.
 */
अटल पूर्णांक micron_supports_on_die_ecc(काष्ठा nand_chip *chip)
अणु
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&chip->base);
	u8 id[5];
	पूर्णांक ret;

	अगर (!chip->parameters.onfi)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	अगर (nanddev_bits_per_cell(&chip->base) != 1)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	/*
	 * We only support on-die ECC of 4/512 or 8/512
	 */
	अगर  (requirements->strength != 4 && requirements->strength != 8)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	/* 0x2 means on-die ECC is available. */
	अगर (chip->id.len != 5 ||
	    (chip->id.data[4] & MICRON_ID_INTERNAL_ECC_MASK) != 0x2)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	/*
	 * It seems that there are devices which करो not support ECC officially.
	 * At least the MT29F2G08ABAGA / MT29F2G08ABBGA devices supports
	 * enabling the ECC feature but करोn't reflect that to the READ_ID table.
	 * So we have to guarantee that we disable the ECC feature directly
	 * after we did the READ_ID table command. Later we can evaluate the
	 * ECC_ENABLE support.
	 */
	ret = micron_nand_on_die_ecc_setup(chip, true);
	अगर (ret)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	ret = nand_पढ़ोid_op(chip, 0, id, माप(id));
	अगर (ret)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	ret = micron_nand_on_die_ecc_setup(chip, false);
	अगर (ret)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	अगर (!(id[4] & MICRON_ID_ECC_ENABLED))
		वापस MICRON_ON_DIE_UNSUPPORTED;

	ret = nand_पढ़ोid_op(chip, 0, id, माप(id));
	अगर (ret)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	अगर (id[4] & MICRON_ID_ECC_ENABLED)
		वापस MICRON_ON_DIE_MANDATORY;

	/*
	 * We only support on-die ECC of 4/512 or 8/512
	 */
	अगर  (requirements->strength != 4 && requirements->strength != 8)
		वापस MICRON_ON_DIE_UNSUPPORTED;

	वापस MICRON_ON_DIE_SUPPORTED;
पूर्ण

अटल पूर्णांक micron_nand_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(base);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा micron_nand *micron;
	पूर्णांक ondie;
	पूर्णांक ret;

	micron = kzalloc(माप(*micron), GFP_KERNEL);
	अगर (!micron)
		वापस -ENOMEM;

	nand_set_manufacturer_data(chip, micron);

	ret = micron_nand_onfi_init(chip);
	अगर (ret)
		जाओ err_मुक्त_manuf_data;

	chip->options |= न_अंकD_BBM_FIRSTPAGE;

	अगर (mtd->ग_लिखोsize == 2048)
		chip->options |= न_अंकD_BBM_SECONDPAGE;

	ondie = micron_supports_on_die_ecc(chip);

	अगर (ondie == MICRON_ON_DIE_MANDATORY &&
	    chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_DIE) अणु
		pr_err("On-die ECC forcefully enabled, not supported\n");
		ret = -EINVAL;
		जाओ err_मुक्त_manuf_data;
	पूर्ण

	अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_DIE) अणु
		अगर (ondie == MICRON_ON_DIE_UNSUPPORTED) अणु
			pr_err("On-die ECC selected but not supported\n");
			ret = -EINVAL;
			जाओ err_मुक्त_manuf_data;
		पूर्ण

		अगर (ondie == MICRON_ON_DIE_MANDATORY) अणु
			micron->ecc.क्रमced = true;
			micron->ecc.enabled = true;
		पूर्ण

		/*
		 * In हाल of 4bit on-die ECC, we need a buffer to store a
		 * page dumped in raw mode so that we can compare its content
		 * to the same page after ECC correction happened and extract
		 * the real number of bitflips from this comparison.
		 * That's not needed क्रम 8-bit ECC, because the status expose
		 * a better approximation of the number of bitflips in a page.
		 */
		अगर (requirements->strength == 4) अणु
			micron->ecc.rawbuf = kदो_स्मृति(mtd->ग_लिखोsize +
						     mtd->oobsize,
						     GFP_KERNEL);
			अगर (!micron->ecc.rawbuf) अणु
				ret = -ENOMEM;
				जाओ err_मुक्त_manuf_data;
			पूर्ण
		पूर्ण

		अगर (requirements->strength == 4)
			mtd_set_ooblayout(mtd,
					  &micron_nand_on_die_4_ooblayout_ops);
		अन्यथा
			mtd_set_ooblayout(mtd,
					  &micron_nand_on_die_8_ooblayout_ops);

		chip->ecc.bytes = requirements->strength * 2;
		chip->ecc.size = 512;
		chip->ecc.strength = requirements->strength;
		chip->ecc.algo = न_अंकD_ECC_ALGO_BCH;
		chip->ecc.पढ़ो_page = micron_nand_पढ़ो_page_on_die_ecc;
		chip->ecc.ग_लिखो_page = micron_nand_ग_लिखो_page_on_die_ecc;

		अगर (ondie == MICRON_ON_DIE_MANDATORY) अणु
			chip->ecc.पढ़ो_page_raw = nand_पढ़ो_page_raw_notsupp;
			chip->ecc.ग_लिखो_page_raw = nand_ग_लिखो_page_raw_notsupp;
		पूर्ण अन्यथा अणु
			अगर (!chip->ecc.पढ़ो_page_raw)
				chip->ecc.पढ़ो_page_raw = nand_पढ़ो_page_raw;
			अगर (!chip->ecc.ग_लिखो_page_raw)
				chip->ecc.ग_लिखो_page_raw = nand_ग_लिखो_page_raw;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_manuf_data:
	kमुक्त(micron->ecc.rawbuf);
	kमुक्त(micron);

	वापस ret;
पूर्ण

अटल व्योम micron_nand_cleanup(काष्ठा nand_chip *chip)
अणु
	काष्ठा micron_nand *micron = nand_get_manufacturer_data(chip);

	kमुक्त(micron->ecc.rawbuf);
	kमुक्त(micron);
पूर्ण

अटल व्योम micron_fixup_onfi_param_page(काष्ठा nand_chip *chip,
					 काष्ठा nand_onfi_params *p)
अणु
	/*
	 * MT29F1G08ABAFAWP-ITE:F and possibly others report 00 00 क्रम the
	 * revision number field of the ONFI parameter page. Assume ONFI
	 * version 1.0 अगर the revision number is 00 00.
	 */
	अगर (le16_to_cpu(p->revision) == 0)
		p->revision = cpu_to_le16(ONFI_VERSION_1_0);
पूर्ण

स्थिर काष्ठा nand_manufacturer_ops micron_nand_manuf_ops = अणु
	.init = micron_nand_init,
	.cleanup = micron_nand_cleanup,
	.fixup_onfi_param_page = micron_fixup_onfi_param_page,
पूर्ण;
