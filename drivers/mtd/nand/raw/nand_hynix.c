<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Free Electrons
 * Copyright (C) 2017 NextThing Co
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

#समावेश "internals.h"

#घोषणा न_अंकD_HYNIX_CMD_SET_PARAMS	0x36
#घोषणा न_अंकD_HYNIX_CMD_APPLY_PARAMS	0x16

#घोषणा न_अंकD_HYNIX_1XNM_RR_REPEAT	8

/**
 * काष्ठा hynix_पढ़ो_retry - पढ़ो-retry data
 * @nregs: number of रेजिस्टर to set when applying a new पढ़ो-retry mode
 * @regs: रेजिस्टर offsets (न_अंकD chip dependent)
 * @values: array of values to set in रेजिस्टरs. The array size is equal to
 *	    (nregs * nmodes)
 */
काष्ठा hynix_पढ़ो_retry अणु
	पूर्णांक nregs;
	स्थिर u8 *regs;
	u8 values[];
पूर्ण;

/**
 * काष्ठा hynix_nand - निजी Hynix न_अंकD काष्ठा
 * @nand_technology: manufacturing process expressed in picometer
 * @पढ़ो_retry: पढ़ो-retry inक्रमmation
 */
काष्ठा hynix_nand अणु
	स्थिर काष्ठा hynix_पढ़ो_retry *पढ़ो_retry;
पूर्ण;

/**
 * काष्ठा hynix_पढ़ो_retry_otp - काष्ठाure describing how the पढ़ो-retry OTP
 *				 area
 * @nregs: number of hynix निजी रेजिस्टरs to set beक्रमe पढ़ोing the पढ़ोing
 *	   the OTP area
 * @regs: रेजिस्टरs that should be configured
 * @values: values that should be set in regs
 * @page: the address to pass to the READ_PAGE command. Depends on the न_अंकD
 *	  chip
 * @size: size of the पढ़ो-retry OTP section
 */
काष्ठा hynix_पढ़ो_retry_otp अणु
	पूर्णांक nregs;
	स्थिर u8 *regs;
	स्थिर u8 *values;
	पूर्णांक page;
	पूर्णांक size;
पूर्ण;

अटल bool hynix_nand_has_valid_jedecid(काष्ठा nand_chip *chip)
अणु
	u8 jedecid[5] = अणु पूर्ण;
	पूर्णांक ret;

	ret = nand_पढ़ोid_op(chip, 0x40, jedecid, माप(jedecid));
	अगर (ret)
		वापस false;

	वापस !म_भेदन("JEDEC", jedecid, माप(jedecid));
पूर्ण

अटल पूर्णांक hynix_nand_cmd_op(काष्ठा nand_chip *chip, u8 cmd)
अणु
	अगर (nand_has_exec_op(chip)) अणु
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(cmd, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, cmd, -1, -1);

	वापस 0;
पूर्ण

अटल पूर्णांक hynix_nand_reg_ग_लिखो_op(काष्ठा nand_chip *chip, u8 addr, u8 val)
अणु
	u16 column = ((u16)addr << 8) | addr;

	अगर (nand_has_exec_op(chip)) अणु
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_ADDR(1, &addr, 0),
			न_अंकD_OP_8BIT_DATA_OUT(1, &val, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_NONE, column, -1);
	chip->legacy.ग_लिखो_byte(chip, val);

	वापस 0;
पूर्ण

अटल पूर्णांक hynix_nand_setup_पढ़ो_retry(काष्ठा nand_chip *chip, पूर्णांक retry_mode)
अणु
	काष्ठा hynix_nand *hynix = nand_get_manufacturer_data(chip);
	स्थिर u8 *values;
	पूर्णांक i, ret;

	values = hynix->पढ़ो_retry->values +
		 (retry_mode * hynix->पढ़ो_retry->nregs);

	/* Enter 'Set Hynix Parameters' mode */
	ret = hynix_nand_cmd_op(chip, न_अंकD_HYNIX_CMD_SET_PARAMS);
	अगर (ret)
		वापस ret;

	/*
	 * Configure the न_अंकD in the requested पढ़ो-retry mode.
	 * This is करोne by setting pre-defined values in पूर्णांकernal न_अंकD
	 * रेजिस्टरs.
	 *
	 * The set of रेजिस्टरs is न_अंकD specअगरic, and the values are either
	 * predefined or extracted from an OTP area on the न_अंकD (values are
	 * probably tweaked at production in this हाल).
	 */
	क्रम (i = 0; i < hynix->पढ़ो_retry->nregs; i++) अणु
		ret = hynix_nand_reg_ग_लिखो_op(chip, hynix->पढ़ो_retry->regs[i],
					      values[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Apply the new settings. */
	वापस hynix_nand_cmd_op(chip, न_अंकD_HYNIX_CMD_APPLY_PARAMS);
पूर्ण

/**
 * hynix_get_majority - get the value that is occurring the most in a given
 *			set of values
 * @in: the array of values to test
 * @repeat: the size of the in array
 * @out: poपूर्णांकer used to store the output value
 *
 * This function implements the 'majority check' logic that is supposed to
 * overcome the unreliability of MLC न_अंकDs when पढ़ोing the OTP area storing
 * the पढ़ो-retry parameters.
 *
 * It's based on a pretty simple assumption: अगर we repeat the same value
 * several बार and then take the one that is occurring the most, we should
 * find the correct value.
 * Let's hope this dummy algorithm prevents us from losing the पढ़ो-retry
 * parameters.
 */
अटल पूर्णांक hynix_get_majority(स्थिर u8 *in, पूर्णांक repeat, u8 *out)
अणु
	पूर्णांक i, j, half = repeat / 2;

	/*
	 * We only test the first half of the in array because we must ensure
	 * that the value is at least occurring repeat / 2 बार.
	 *
	 * This loop is suboptimal since we may count the occurrences of the
	 * same value several समय, but we are करोing that on small sets, which
	 * makes it acceptable.
	 */
	क्रम (i = 0; i < half; i++) अणु
		पूर्णांक cnt = 0;
		u8 val = in[i];

		/* Count all values that are matching the one at index i. */
		क्रम (j = i + 1; j < repeat; j++) अणु
			अगर (in[j] == val)
				cnt++;
		पूर्ण

		/* We found a value occurring more than repeat / 2. */
		अगर (cnt > half) अणु
			*out = val;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक hynix_पढ़ो_rr_otp(काष्ठा nand_chip *chip,
			     स्थिर काष्ठा hynix_पढ़ो_retry_otp *info,
			     व्योम *buf)
अणु
	पूर्णांक i, ret;

	ret = nand_reset_op(chip);
	अगर (ret)
		वापस ret;

	ret = hynix_nand_cmd_op(chip, न_अंकD_HYNIX_CMD_SET_PARAMS);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < info->nregs; i++) अणु
		ret = hynix_nand_reg_ग_लिखो_op(chip, info->regs[i],
					      info->values[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hynix_nand_cmd_op(chip, न_अंकD_HYNIX_CMD_APPLY_PARAMS);
	अगर (ret)
		वापस ret;

	/* Sequence to enter OTP mode? */
	ret = hynix_nand_cmd_op(chip, 0x17);
	अगर (ret)
		वापस ret;

	ret = hynix_nand_cmd_op(chip, 0x4);
	अगर (ret)
		वापस ret;

	ret = hynix_nand_cmd_op(chip, 0x19);
	अगर (ret)
		वापस ret;

	/* Now पढ़ो the page */
	ret = nand_पढ़ो_page_op(chip, info->page, 0, buf, info->size);
	अगर (ret)
		वापस ret;

	/* Put everything back to normal */
	ret = nand_reset_op(chip);
	अगर (ret)
		वापस ret;

	ret = hynix_nand_cmd_op(chip, न_अंकD_HYNIX_CMD_SET_PARAMS);
	अगर (ret)
		वापस ret;

	ret = hynix_nand_reg_ग_लिखो_op(chip, 0x38, 0);
	अगर (ret)
		वापस ret;

	ret = hynix_nand_cmd_op(chip, न_अंकD_HYNIX_CMD_APPLY_PARAMS);
	अगर (ret)
		वापस ret;

	वापस nand_पढ़ो_page_op(chip, 0, 0, शून्य, 0);
पूर्ण

#घोषणा न_अंकD_HYNIX_1XNM_RR_COUNT_OFFS				0
#घोषणा न_अंकD_HYNIX_1XNM_RR_REG_COUNT_OFFS			8
#घोषणा न_अंकD_HYNIX_1XNM_RR_SET_OFFS(x, setsize, inv)		\
	(16 + ((((x) * 2) + ((inv) ? 1 : 0)) * (setsize)))

अटल पूर्णांक hynix_mlc_1xnm_rr_value(स्थिर u8 *buf, पूर्णांक nmodes, पूर्णांक nregs,
				   पूर्णांक mode, पूर्णांक reg, bool inv, u8 *val)
अणु
	u8 पंचांगp[न_अंकD_HYNIX_1XNM_RR_REPEAT];
	पूर्णांक val_offs = (mode * nregs) + reg;
	पूर्णांक set_size = nmodes * nregs;
	पूर्णांक i, ret;

	क्रम (i = 0; i < न_अंकD_HYNIX_1XNM_RR_REPEAT; i++) अणु
		पूर्णांक set_offs = न_अंकD_HYNIX_1XNM_RR_SET_OFFS(i, set_size, inv);

		पंचांगp[i] = buf[val_offs + set_offs];
	पूर्ण

	ret = hynix_get_majority(पंचांगp, न_अंकD_HYNIX_1XNM_RR_REPEAT, val);
	अगर (ret)
		वापस ret;

	अगर (inv)
		*val = ~*val;

	वापस 0;
पूर्ण

अटल u8 hynix_1xnm_mlc_पढ़ो_retry_regs[] = अणु
	0xcc, 0xbf, 0xaa, 0xab, 0xcd, 0xad, 0xae, 0xaf
पूर्ण;

अटल पूर्णांक hynix_mlc_1xnm_rr_init(काष्ठा nand_chip *chip,
				  स्थिर काष्ठा hynix_पढ़ो_retry_otp *info)
अणु
	काष्ठा hynix_nand *hynix = nand_get_manufacturer_data(chip);
	काष्ठा hynix_पढ़ो_retry *rr = शून्य;
	पूर्णांक ret, i, j;
	u8 nregs, nmodes;
	u8 *buf;

	buf = kदो_स्मृति(info->size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hynix_पढ़ो_rr_otp(chip, info, buf);
	अगर (ret)
		जाओ out;

	ret = hynix_get_majority(buf, न_अंकD_HYNIX_1XNM_RR_REPEAT,
				 &nmodes);
	अगर (ret)
		जाओ out;

	ret = hynix_get_majority(buf + न_अंकD_HYNIX_1XNM_RR_REPEAT,
				 न_अंकD_HYNIX_1XNM_RR_REPEAT,
				 &nregs);
	अगर (ret)
		जाओ out;

	rr = kzalloc(माप(*rr) + (nregs * nmodes), GFP_KERNEL);
	अगर (!rr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < nmodes; i++) अणु
		क्रम (j = 0; j < nregs; j++) अणु
			u8 *val = rr->values + (i * nregs);

			ret = hynix_mlc_1xnm_rr_value(buf, nmodes, nregs, i, j,
						      false, val);
			अगर (!ret)
				जारी;

			ret = hynix_mlc_1xnm_rr_value(buf, nmodes, nregs, i, j,
						      true, val);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

	rr->nregs = nregs;
	rr->regs = hynix_1xnm_mlc_पढ़ो_retry_regs;
	hynix->पढ़ो_retry = rr;
	chip->ops.setup_पढ़ो_retry = hynix_nand_setup_पढ़ो_retry;
	chip->पढ़ो_retries = nmodes;

out:
	kमुक्त(buf);

	अगर (ret)
		kमुक्त(rr);

	वापस ret;
पूर्ण

अटल स्थिर u8 hynix_mlc_1xnm_rr_otp_regs[] = अणु 0x38 पूर्ण;
अटल स्थिर u8 hynix_mlc_1xnm_rr_otp_values[] = अणु 0x52 पूर्ण;

अटल स्थिर काष्ठा hynix_पढ़ो_retry_otp hynix_mlc_1xnm_rr_otps[] = अणु
	अणु
		.nregs = ARRAY_SIZE(hynix_mlc_1xnm_rr_otp_regs),
		.regs = hynix_mlc_1xnm_rr_otp_regs,
		.values = hynix_mlc_1xnm_rr_otp_values,
		.page = 0x21f,
		.size = 784
	पूर्ण,
	अणु
		.nregs = ARRAY_SIZE(hynix_mlc_1xnm_rr_otp_regs),
		.regs = hynix_mlc_1xnm_rr_otp_regs,
		.values = hynix_mlc_1xnm_rr_otp_values,
		.page = 0x200,
		.size = 528,
	पूर्ण,
पूर्ण;

अटल पूर्णांक hynix_nand_rr_init(काष्ठा nand_chip *chip)
अणु
	पूर्णांक i, ret = 0;
	bool valid_jedecid;

	valid_jedecid = hynix_nand_has_valid_jedecid(chip);

	/*
	 * We only support पढ़ो-retry क्रम 1xnm न_अंकDs, and those न_अंकDs all
	 * expose a valid JEDEC ID.
	 */
	अगर (valid_jedecid) अणु
		u8 nand_tech = chip->id.data[5] >> 4;

		/* 1xnm technology */
		अगर (nand_tech == 4) अणु
			क्रम (i = 0; i < ARRAY_SIZE(hynix_mlc_1xnm_rr_otps);
			     i++) अणु
				/*
				 * FIXME: Hynix recommend to copy the
				 * पढ़ो-retry OTP area पूर्णांकo a normal page.
				 */
				ret = hynix_mlc_1xnm_rr_init(chip,
						hynix_mlc_1xnm_rr_otps);
				अगर (!ret)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ret)
		pr_warn("failed to initialize read-retry infrastructure");

	वापस 0;
पूर्ण

अटल व्योम hynix_nand_extract_oobsize(काष्ठा nand_chip *chip,
				       bool valid_jedecid)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;
	u8 oobsize;

	memorg = nanddev_get_memorg(&chip->base);

	oobsize = ((chip->id.data[3] >> 2) & 0x3) |
		  ((chip->id.data[3] >> 4) & 0x4);

	अगर (valid_jedecid) अणु
		चयन (oobsize) अणु
		हाल 0:
			memorg->oobsize = 2048;
			अवरोध;
		हाल 1:
			memorg->oobsize = 1664;
			अवरोध;
		हाल 2:
			memorg->oobsize = 1024;
			अवरोध;
		हाल 3:
			memorg->oobsize = 640;
			अवरोध;
		शेष:
			/*
			 * We should never reach this हाल, but अगर that
			 * happens, this probably means Hynix decided to use
			 * a dअगरferent extended ID क्रमmat, and we should find
			 * a way to support it.
			 */
			WARN(1, "Invalid OOB size");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (oobsize) अणु
		हाल 0:
			memorg->oobsize = 128;
			अवरोध;
		हाल 1:
			memorg->oobsize = 224;
			अवरोध;
		हाल 2:
			memorg->oobsize = 448;
			अवरोध;
		हाल 3:
			memorg->oobsize = 64;
			अवरोध;
		हाल 4:
			memorg->oobsize = 32;
			अवरोध;
		हाल 5:
			memorg->oobsize = 16;
			अवरोध;
		हाल 6:
			memorg->oobsize = 640;
			अवरोध;
		शेष:
			/*
			 * We should never reach this हाल, but अगर that
			 * happens, this probably means Hynix decided to use
			 * a dअगरferent extended ID क्रमmat, and we should find
			 * a way to support it.
			 */
			WARN(1, "Invalid OOB size");
			अवरोध;
		पूर्ण

		/*
		 * The datasheet of H27UCG8T2BTR mentions that the "Redundant
		 * Area Size" is encoded "per 8KB" (page size). This chip uses
		 * a page size of 16KiB. The datasheet mentions an OOB size of
		 * 1.280 bytes, but the OOB size encoded in the ID bytes (using
		 * the existing logic above) is 640 bytes.
		 * Update the OOB size क्रम this chip by taking the value
		 * determined above and scaling it to the actual page size (so
		 * the actual OOB size क्रम this chip is: 640 * 16k / 8k).
		 */
		अगर (chip->id.data[1] == 0xde)
			memorg->oobsize *= memorg->pagesize / SZ_8K;
	पूर्ण

	mtd->oobsize = memorg->oobsize;
पूर्ण

अटल व्योम hynix_nand_extract_ecc_requirements(काष्ठा nand_chip *chip,
						bool valid_jedecid)
अणु
	काष्ठा nand_device *base = &chip->base;
	काष्ठा nand_ecc_props requirements = अणुपूर्ण;
	u8 ecc_level = (chip->id.data[4] >> 4) & 0x7;

	अगर (valid_jedecid) अणु
		/* Reference: H27UCG8T2E datasheet */
		requirements.step_size = 1024;

		चयन (ecc_level) अणु
		हाल 0:
			requirements.step_size = 0;
			requirements.strength = 0;
			अवरोध;
		हाल 1:
			requirements.strength = 4;
			अवरोध;
		हाल 2:
			requirements.strength = 24;
			अवरोध;
		हाल 3:
			requirements.strength = 32;
			अवरोध;
		हाल 4:
			requirements.strength = 40;
			अवरोध;
		हाल 5:
			requirements.strength = 50;
			अवरोध;
		हाल 6:
			requirements.strength = 60;
			अवरोध;
		शेष:
			/*
			 * We should never reach this हाल, but अगर that
			 * happens, this probably means Hynix decided to use
			 * a dअगरferent extended ID क्रमmat, and we should find
			 * a way to support it.
			 */
			WARN(1, "Invalid ECC requirements");
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The ECC requirements field meaning depends on the
		 * न_अंकD technology.
		 */
		u8 nand_tech = chip->id.data[5] & 0x7;

		अगर (nand_tech < 3) अणु
			/* > 26nm, reference: H27UBG8T2A datasheet */
			अगर (ecc_level < 5) अणु
				requirements.step_size = 512;
				requirements.strength = 1 << ecc_level;
			पूर्ण अन्यथा अगर (ecc_level < 7) अणु
				अगर (ecc_level == 5)
					requirements.step_size = 2048;
				अन्यथा
					requirements.step_size = 1024;
				requirements.strength = 24;
			पूर्ण अन्यथा अणु
				/*
				 * We should never reach this हाल, but अगर that
				 * happens, this probably means Hynix decided
				 * to use a dअगरferent extended ID क्रमmat, and
				 * we should find a way to support it.
				 */
				WARN(1, "Invalid ECC requirements");
			पूर्ण
		पूर्ण अन्यथा अणु
			/* <= 26nm, reference: H27UBG8T2B datasheet */
			अगर (!ecc_level) अणु
				requirements.step_size = 0;
				requirements.strength = 0;
			पूर्ण अन्यथा अगर (ecc_level < 5) अणु
				requirements.step_size = 512;
				requirements.strength = 1 << (ecc_level - 1);
			पूर्ण अन्यथा अणु
				requirements.step_size = 1024;
				requirements.strength = 24 +
							(8 * (ecc_level - 5));
			पूर्ण
		पूर्ण
	पूर्ण

	nanddev_set_ecc_requirements(base, &requirements);
पूर्ण

अटल व्योम hynix_nand_extract_scrambling_requirements(काष्ठा nand_chip *chip,
						       bool valid_jedecid)
अणु
	u8 nand_tech;

	/* We need scrambling on all TLC न_अंकDs*/
	अगर (nanddev_bits_per_cell(&chip->base) > 2)
		chip->options |= न_अंकD_NEED_SCRAMBLING;

	/* And on MLC न_अंकDs with sub-3xnm process */
	अगर (valid_jedecid) अणु
		nand_tech = chip->id.data[5] >> 4;

		/* < 3xnm */
		अगर (nand_tech > 0)
			chip->options |= न_अंकD_NEED_SCRAMBLING;
	पूर्ण अन्यथा अणु
		nand_tech = chip->id.data[5] & 0x7;

		/* < 32nm */
		अगर (nand_tech > 2)
			chip->options |= न_अंकD_NEED_SCRAMBLING;
	पूर्ण
पूर्ण

अटल व्योम hynix_nand_decode_id(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;
	bool valid_jedecid;
	u8 पंचांगp;

	memorg = nanddev_get_memorg(&chip->base);

	/*
	 * Exclude all SLC न_अंकDs from this advanced detection scheme.
	 * According to the ranges defined in several datasheets, it might
	 * appear that even SLC न_अंकDs could fall in this extended ID scheme.
	 * If that the हाल rework the test to let SLC न_अंकDs go through the
	 * detection process.
	 */
	अगर (chip->id.len < 6 || nand_is_slc(chip)) अणु
		nand_decode_ext_id(chip);
		वापस;
	पूर्ण

	/* Extract pagesize */
	memorg->pagesize = 2048 << (chip->id.data[3] & 0x03);
	mtd->ग_लिखोsize = memorg->pagesize;

	पंचांगp = (chip->id.data[3] >> 4) & 0x3;
	/*
	 * When bit7 is set that means we start counting at 1MiB, otherwise
	 * we start counting at 128KiB and shअगरt this value the content of
	 * ID[3][4:5].
	 * The only exception is when ID[3][4:5] == 3 and ID[3][7] == 0, in
	 * this हाल the erasesize is set to 768KiB.
	 */
	अगर (chip->id.data[3] & 0x80) अणु
		memorg->pages_per_eraseblock = (SZ_1M << पंचांगp) /
					       memorg->pagesize;
		mtd->erasesize = SZ_1M << पंचांगp;
	पूर्ण अन्यथा अगर (पंचांगp == 3) अणु
		memorg->pages_per_eraseblock = (SZ_512K + SZ_256K) /
					       memorg->pagesize;
		mtd->erasesize = SZ_512K + SZ_256K;
	पूर्ण अन्यथा अणु
		memorg->pages_per_eraseblock = (SZ_128K << पंचांगp) /
					       memorg->pagesize;
		mtd->erasesize = SZ_128K << पंचांगp;
	पूर्ण

	/*
	 * Modern Toggle DDR न_अंकDs have a valid JEDECID even though they are
	 * not exposing a valid JEDEC parameter table.
	 * These न_अंकDs use a dअगरferent न_अंकD ID scheme.
	 */
	valid_jedecid = hynix_nand_has_valid_jedecid(chip);

	hynix_nand_extract_oobsize(chip, valid_jedecid);
	hynix_nand_extract_ecc_requirements(chip, valid_jedecid);
	hynix_nand_extract_scrambling_requirements(chip, valid_jedecid);
पूर्ण

अटल व्योम hynix_nand_cleanup(काष्ठा nand_chip *chip)
अणु
	काष्ठा hynix_nand *hynix = nand_get_manufacturer_data(chip);

	अगर (!hynix)
		वापस;

	kमुक्त(hynix->पढ़ो_retry);
	kमुक्त(hynix);
	nand_set_manufacturer_data(chip, शून्य);
पूर्ण

अटल पूर्णांक
h27ucg8t2atrbc_choose_पूर्णांकerface_config(काष्ठा nand_chip *chip,
				       काष्ठा nand_पूर्णांकerface_config *अगरace)
अणु
	onfi_fill_पूर्णांकerface_config(chip, अगरace, न_अंकD_SDR_IFACE, 4);

	वापस nand_choose_best_sdr_timings(chip, अगरace, शून्य);
पूर्ण

अटल पूर्णांक hynix_nand_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा hynix_nand *hynix;
	पूर्णांक ret;

	अगर (!nand_is_slc(chip))
		chip->options |= न_अंकD_BBM_LASTPAGE;
	अन्यथा
		chip->options |= न_अंकD_BBM_FIRSTPAGE | न_अंकD_BBM_SECONDPAGE;

	hynix = kzalloc(माप(*hynix), GFP_KERNEL);
	अगर (!hynix)
		वापस -ENOMEM;

	nand_set_manufacturer_data(chip, hynix);

	अगर (!म_भेदन("H27UCG8T2ATR-BC", chip->parameters.model,
		     माप("H27UCG8T2ATR-BC") - 1))
		chip->ops.choose_पूर्णांकerface_config =
			h27ucg8t2atrbc_choose_पूर्णांकerface_config;

	ret = hynix_nand_rr_init(chip);
	अगर (ret)
		hynix_nand_cleanup(chip);

	वापस ret;
पूर्ण

स्थिर काष्ठा nand_manufacturer_ops hynix_nand_manuf_ops = अणु
	.detect = hynix_nand_decode_id,
	.init = hynix_nand_init,
	.cleanup = hynix_nand_cleanup,
पूर्ण;
