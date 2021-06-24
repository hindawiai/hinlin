<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Free Electrons
 * Copyright (C) 2017 NextThing Co
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश "internals.h"

/* Bit क्रम detecting BEन_अंकD */
#घोषणा TOSHIBA_न_अंकD_ID4_IS_BEन_अंकD		BIT(7)

/* Recommended to reग_लिखो क्रम BEन_अंकD */
#घोषणा TOSHIBA_न_अंकD_STATUS_REWRITE_RECOMMENDED	BIT(3)

/* ECC Status Read Command क्रम BEन_अंकD */
#घोषणा TOSHIBA_न_अंकD_CMD_ECC_STATUS_READ	0x7A

/* ECC Status Mask क्रम BEन_अंकD */
#घोषणा TOSHIBA_न_अंकD_ECC_STATUS_MASK		0x0F

/* Uncorrectable Error क्रम BEन_अंकD */
#घोषणा TOSHIBA_न_अंकD_ECC_STATUS_UNCORR		0x0F

/* Max ECC Steps क्रम BEन_अंकD */
#घोषणा TOSHIBA_न_अंकD_MAX_ECC_STEPS		8

अटल पूर्णांक toshiba_nand_benand_पढ़ो_eccstatus_op(काष्ठा nand_chip *chip,
						 u8 *buf)
अणु
	u8 *ecc_status = buf;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(TOSHIBA_न_अंकD_CMD_ECC_STATUS_READ,
				    PSEC_TO_NSEC(sdr->tADL_min)),
			न_अंकD_OP_8BIT_DATA_IN(chip->ecc.steps, ecc_status, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक toshiba_nand_benand_eccstatus(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;
	अचिन्हित पूर्णांक max_bitflips = 0;
	u8 status, ecc_status[TOSHIBA_न_अंकD_MAX_ECC_STEPS];

	/* Check Status */
	ret = toshiba_nand_benand_पढ़ो_eccstatus_op(chip, ecc_status);
	अगर (!ret) अणु
		अचिन्हित पूर्णांक i, bitflips = 0;

		क्रम (i = 0; i < chip->ecc.steps; i++) अणु
			bitflips = ecc_status[i] & TOSHIBA_न_अंकD_ECC_STATUS_MASK;
			अगर (bitflips == TOSHIBA_न_अंकD_ECC_STATUS_UNCORR) अणु
				mtd->ecc_stats.failed++;
			पूर्ण अन्यथा अणु
				mtd->ecc_stats.corrected += bitflips;
				max_bitflips = max(max_bitflips, bitflips);
			पूर्ण
		पूर्ण

		वापस max_bitflips;
	पूर्ण

	/*
	 * Fallback to regular status check अगर
	 * toshiba_nand_benand_पढ़ो_eccstatus_op() failed.
	 */
	ret = nand_status_op(chip, &status);
	अगर (ret)
		वापस ret;

	अगर (status & न_अंकD_STATUS_FAIL) अणु
		/* uncorrected */
		mtd->ecc_stats.failed++;
	पूर्ण अन्यथा अगर (status & TOSHIBA_न_अंकD_STATUS_REWRITE_RECOMMENDED) अणु
		/* corrected */
		max_bitflips = mtd->bitflip_threshold;
		mtd->ecc_stats.corrected += max_bitflips;
	पूर्ण

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक
toshiba_nand_पढ़ो_page_benand(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			      पूर्णांक oob_required, पूर्णांक page)
अणु
	पूर्णांक ret;

	ret = nand_पढ़ो_page_raw(chip, buf, oob_required, page);
	अगर (ret)
		वापस ret;

	वापस toshiba_nand_benand_eccstatus(chip);
पूर्ण

अटल पूर्णांक
toshiba_nand_पढ़ो_subpage_benand(काष्ठा nand_chip *chip, uपूर्णांक32_t data_offs,
				 uपूर्णांक32_t पढ़ोlen, uपूर्णांक8_t *bufpoi, पूर्णांक page)
अणु
	पूर्णांक ret;

	ret = nand_पढ़ो_page_op(chip, page, data_offs,
				bufpoi + data_offs, पढ़ोlen);
	अगर (ret)
		वापस ret;

	वापस toshiba_nand_benand_eccstatus(chip);
पूर्ण

अटल व्योम toshiba_nand_benand_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/*
	 * On BEन_अंकD, the entire OOB region can be used by the MTD user.
	 * The calculated ECC bytes are stored पूर्णांकo other isolated
	 * area which is not accessible to users.
	 * This is why chip->ecc.bytes = 0.
	 */
	chip->ecc.bytes = 0;
	chip->ecc.size = 512;
	chip->ecc.strength = 8;
	chip->ecc.पढ़ो_page = toshiba_nand_पढ़ो_page_benand;
	chip->ecc.पढ़ो_subpage = toshiba_nand_पढ़ो_subpage_benand;
	chip->ecc.ग_लिखो_page = nand_ग_लिखो_page_raw;
	chip->ecc.पढ़ो_page_raw = nand_पढ़ो_page_raw_notsupp;
	chip->ecc.ग_लिखो_page_raw = nand_ग_लिखो_page_raw_notsupp;

	chip->options |= न_अंकD_SUBPAGE_READ;

	mtd_set_ooblayout(mtd, nand_get_large_page_ooblayout());
पूर्ण

अटल व्योम toshiba_nand_decode_id(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;
	काष्ठा nand_ecc_props requirements = अणुपूर्ण;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;

	memorg = nanddev_get_memorg(&chip->base);

	nand_decode_ext_id(chip);

	/*
	 * Toshiba 24nm raw SLC (i.e., not BEन_अंकD) have 32B OOB per
	 * 512B page. For Toshiba SLC, we decode the 5th/6th byte as
	 * follows:
	 * - ID byte 6, bits[2:0]: 100b -> 43nm, 101b -> 32nm,
	 *                         110b -> 24nm
	 * - ID byte 5, bit[7]:    1 -> BEन_अंकD, 0 -> raw SLC
	 */
	अगर (chip->id.len >= 6 && nand_is_slc(chip) &&
	    (chip->id.data[5] & 0x7) == 0x6 /* 24nm */ &&
	    !(chip->id.data[4] & TOSHIBA_न_अंकD_ID4_IS_BEन_अंकD) /* !BEन_अंकD */) अणु
		memorg->oobsize = 32 * memorg->pagesize >> 9;
		mtd->oobsize = memorg->oobsize;
	पूर्ण

	/*
	 * Extract ECC requirements from 6th id byte.
	 * For Toshiba SLC, ecc requrements are as follows:
	 *  - 43nm: 1 bit ECC क्रम each 512Byte is required.
	 *  - 32nm: 4 bit ECC क्रम each 512Byte is required.
	 *  - 24nm: 8 bit ECC क्रम each 512Byte is required.
	 */
	अगर (chip->id.len >= 6 && nand_is_slc(chip)) अणु
		requirements.step_size = 512;
		चयन (chip->id.data[5] & 0x7) अणु
		हाल 0x4:
			requirements.strength = 1;
			अवरोध;
		हाल 0x5:
			requirements.strength = 4;
			अवरोध;
		हाल 0x6:
			requirements.strength = 8;
			अवरोध;
		शेष:
			WARN(1, "Could not get ECC info");
			requirements.step_size = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	nanddev_set_ecc_requirements(base, &requirements);
पूर्ण

अटल पूर्णांक
tc58teg5dclta00_choose_पूर्णांकerface_config(काष्ठा nand_chip *chip,
					काष्ठा nand_पूर्णांकerface_config *अगरace)
अणु
	onfi_fill_पूर्णांकerface_config(chip, अगरace, न_अंकD_SDR_IFACE, 5);

	वापस nand_choose_best_sdr_timings(chip, अगरace, शून्य);
पूर्ण

अटल पूर्णांक
tc58nvg0s3e_choose_पूर्णांकerface_config(काष्ठा nand_chip *chip,
				    काष्ठा nand_पूर्णांकerface_config *अगरace)
अणु
	onfi_fill_पूर्णांकerface_config(chip, अगरace, न_अंकD_SDR_IFACE, 2);

	वापस nand_choose_best_sdr_timings(chip, अगरace, शून्य);
पूर्ण

अटल पूर्णांक
th58nvg2s3hbai4_choose_पूर्णांकerface_config(काष्ठा nand_chip *chip,
					काष्ठा nand_पूर्णांकerface_config *अगरace)
अणु
	काष्ठा nand_sdr_timings *sdr = &अगरace->timings.sdr;

	/* Start with timings from the बंदst timing mode, mode 4. */
	onfi_fill_पूर्णांकerface_config(chip, अगरace, न_अंकD_SDR_IFACE, 4);

	/* Patch timings that dअगरfer from mode 4. */
	sdr->tALS_min = 12000;
	sdr->tCHZ_max = 20000;
	sdr->tCLS_min = 12000;
	sdr->tCOH_min = 0;
	sdr->tDS_min = 12000;
	sdr->tRHOH_min = 25000;
	sdr->tRHW_min = 30000;
	sdr->tRHZ_max = 60000;
	sdr->tWHR_min = 60000;

	/* Patch timings not part of onfi timing mode. */
	sdr->tPROG_max = 700000000;
	sdr->tBERS_max = 5000000000;

	वापस nand_choose_best_sdr_timings(chip, अगरace, sdr);
पूर्ण

अटल पूर्णांक tc58teg5dclta00_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	chip->ops.choose_पूर्णांकerface_config =
		&tc58teg5dclta00_choose_पूर्णांकerface_config;
	chip->options |= न_अंकD_NEED_SCRAMBLING;
	mtd_set_pairing_scheme(mtd, &dist3_pairing_scheme);

	वापस 0;
पूर्ण

अटल पूर्णांक tc58nvg0s3e_init(काष्ठा nand_chip *chip)
अणु
	chip->ops.choose_पूर्णांकerface_config =
		&tc58nvg0s3e_choose_पूर्णांकerface_config;

	वापस 0;
पूर्ण

अटल पूर्णांक th58nvg2s3hbai4_init(काष्ठा nand_chip *chip)
अणु
	chip->ops.choose_पूर्णांकerface_config =
		&th58nvg2s3hbai4_choose_पूर्णांकerface_config;

	वापस 0;
पूर्ण

अटल पूर्णांक toshiba_nand_init(काष्ठा nand_chip *chip)
अणु
	अगर (nand_is_slc(chip))
		chip->options |= न_अंकD_BBM_FIRSTPAGE | न_अंकD_BBM_SECONDPAGE;

	/* Check that chip is BEन_अंकD and ECC mode is on-die */
	अगर (nand_is_slc(chip) &&
	    chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_DIE &&
	    chip->id.data[4] & TOSHIBA_न_अंकD_ID4_IS_BEन_अंकD)
		toshiba_nand_benand_init(chip);

	अगर (!म_भेद("TC58TEG5DCLTA00", chip->parameters.model))
		tc58teg5dclta00_init(chip);
	अगर (!म_भेदन("TC58NVG0S3E", chip->parameters.model,
		     माप("TC58NVG0S3E") - 1))
		tc58nvg0s3e_init(chip);
	अगर (!म_भेदन("TH58NVG2S3HBAI4", chip->parameters.model,
		     माप("TH58NVG2S3HBAI4") - 1))
		th58nvg2s3hbai4_init(chip);

	वापस 0;
पूर्ण

स्थिर काष्ठा nand_manufacturer_ops toshiba_nand_manuf_ops = अणु
	.detect = toshiba_nand_decode_id,
	.init = toshiba_nand_init,
पूर्ण;
