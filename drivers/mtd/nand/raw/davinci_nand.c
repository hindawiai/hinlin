<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * davinci_nand.c - न_अंकD Flash Driver क्रम DaVinci family chips
 *
 * Copyright तऊ 2006 Texas Instruments.
 *
 * Port to 2.6.23 Copyright तऊ 2008 by:
 *   Sander Huijsen <Shuijsen@optelecom-nkf.com>
 *   Troy Kisky <troy.kisky@boundarydevices.com>
 *   Dirk Behme <Dirk.Behme@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>

#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci-aemअगर.h>

/*
 * This is a device driver क्रम the न_अंकD flash controller found on the
 * various DaVinci family chips.  It handles up to four SoC chipselects,
 * and some flavors of secondary chipselect (e.g. based on A12) as used
 * with multichip packages.
 *
 * The 1-bit ECC hardware is supported, as well as the newer 4-bit ECC
 * available on chips like the DM355 and OMAP-L137 and needed with the
 * more error-prone MLC न_अंकD chips.
 *
 * This driver assumes EM_WAIT connects all the न_अंकD devices' RDY/nBUSY
 * outमाला_दो in a "wire-AND" configuration, with no per-chip संकेतs.
 */
काष्ठा davinci_nand_info अणु
	काष्ठा nand_controller	controller;
	काष्ठा nand_chip	chip;

	काष्ठा platक्रमm_device	*pdev;

	bool			is_पढ़ोmode;

	व्योम __iomem		*base;
	व्योम __iomem		*vaddr;

	व्योम __iomem		*current_cs;

	uपूर्णांक32_t		mask_chipsel;
	uपूर्णांक32_t		mask_ale;
	uपूर्णांक32_t		mask_cle;

	uपूर्णांक32_t		core_chipsel;

	काष्ठा davinci_aemअगर_timing	*timing;
पूर्ण;

अटल DEFINE_SPINLOCK(davinci_nand_lock);
अटल bool ecc4_busy;

अटल अंतरभूत काष्ठा davinci_nand_info *to_davinci_nand(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd_to_nand(mtd), काष्ठा davinci_nand_info, chip);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक davinci_nand_पढ़ोl(काष्ठा davinci_nand_info *info,
		पूर्णांक offset)
अणु
	वापस __raw_पढ़ोl(info->base + offset);
पूर्ण

अटल अंतरभूत व्योम davinci_nand_ग_लिखोl(काष्ठा davinci_nand_info *info,
		पूर्णांक offset, अचिन्हित दीर्घ value)
अणु
	__raw_ग_लिखोl(value, info->base + offset);
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * 1-bit hardware ECC ... context मुख्यtained क्रम each core chipselect
 */

अटल अंतरभूत uपूर्णांक32_t nand_davinci_पढ़ोecc_1bit(काष्ठा mtd_info *mtd)
अणु
	काष्ठा davinci_nand_info *info = to_davinci_nand(mtd);

	वापस davinci_nand_पढ़ोl(info, न_अंकDF1ECC_OFFSET
			+ 4 * info->core_chipsel);
पूर्ण

अटल व्योम nand_davinci_hwctl_1bit(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा davinci_nand_info *info;
	uपूर्णांक32_t nandcfr;
	अचिन्हित दीर्घ flags;

	info = to_davinci_nand(nand_to_mtd(chip));

	/* Reset ECC hardware */
	nand_davinci_पढ़ोecc_1bit(nand_to_mtd(chip));

	spin_lock_irqsave(&davinci_nand_lock, flags);

	/* Restart ECC hardware */
	nandcfr = davinci_nand_पढ़ोl(info, न_अंकDFCR_OFFSET);
	nandcfr |= BIT(8 + info->core_chipsel);
	davinci_nand_ग_लिखोl(info, न_अंकDFCR_OFFSET, nandcfr);

	spin_unlock_irqrestore(&davinci_nand_lock, flags);
पूर्ण

/*
 * Read hardware ECC value and pack पूर्णांकo three bytes
 */
अटल पूर्णांक nand_davinci_calculate_1bit(काष्ठा nand_chip *chip,
				       स्थिर u_अक्षर *dat, u_अक्षर *ecc_code)
अणु
	अचिन्हित पूर्णांक ecc_val = nand_davinci_पढ़ोecc_1bit(nand_to_mtd(chip));
	अचिन्हित पूर्णांक ecc24 = (ecc_val & 0x0fff) | ((ecc_val & 0x0fff0000) >> 4);

	/* invert so that erased block ecc is correct */
	ecc24 = ~ecc24;
	ecc_code[0] = (u_अक्षर)(ecc24);
	ecc_code[1] = (u_अक्षर)(ecc24 >> 8);
	ecc_code[2] = (u_अक्षर)(ecc24 >> 16);

	वापस 0;
पूर्ण

अटल पूर्णांक nand_davinci_correct_1bit(काष्ठा nand_chip *chip, u_अक्षर *dat,
				     u_अक्षर *पढ़ो_ecc, u_अक्षर *calc_ecc)
अणु
	uपूर्णांक32_t eccNand = पढ़ो_ecc[0] | (पढ़ो_ecc[1] << 8) |
					  (पढ़ो_ecc[2] << 16);
	uपूर्णांक32_t eccCalc = calc_ecc[0] | (calc_ecc[1] << 8) |
					  (calc_ecc[2] << 16);
	uपूर्णांक32_t dअगरf = eccCalc ^ eccNand;

	अगर (dअगरf) अणु
		अगर ((((dअगरf >> 12) ^ dअगरf) & 0xfff) == 0xfff) अणु
			/* Correctable error */
			अगर ((dअगरf >> (12 + 3)) < chip->ecc.size) अणु
				dat[dअगरf >> (12 + 3)] ^= BIT((dअगरf >> 12) & 7);
				वापस 1;
			पूर्ण अन्यथा अणु
				वापस -EBADMSG;
			पूर्ण
		पूर्ण अन्यथा अगर (!(dअगरf & (dअगरf - 1))) अणु
			/* Single bit ECC error in the ECC itself,
			 * nothing to fix */
			वापस 1;
		पूर्ण अन्यथा अणु
			/* Uncorrectable error */
			वापस -EBADMSG;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * 4-bit hardware ECC ... context मुख्यtained over entire AEMIF
 *
 * This is a syndrome engine, but we aव्योम न_अंकD_ECC_PLACEMENT_INTERLEAVED
 * since that क्रमces use of a problematic "infix OOB" layout.
 * Among other things, it trashes manufacturer bad block markers.
 * Also, and specअगरic to this hardware, it ECC-protects the "prepad"
 * in the OOB ... जबतक having ECC protection क्रम parts of OOB would
 * seem useful, the current MTD stack someबार wants to update the
 * OOB without recomputing ECC.
 */

अटल व्योम nand_davinci_hwctl_4bit(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा davinci_nand_info *info = to_davinci_nand(nand_to_mtd(chip));
	अचिन्हित दीर्घ flags;
	u32 val;

	/* Reset ECC hardware */
	davinci_nand_पढ़ोl(info, न_अंकD_4BIT_ECC1_OFFSET);

	spin_lock_irqsave(&davinci_nand_lock, flags);

	/* Start 4-bit ECC calculation क्रम पढ़ो/ग_लिखो */
	val = davinci_nand_पढ़ोl(info, न_अंकDFCR_OFFSET);
	val &= ~(0x03 << 4);
	val |= (info->core_chipsel << 4) | BIT(12);
	davinci_nand_ग_लिखोl(info, न_अंकDFCR_OFFSET, val);

	info->is_पढ़ोmode = (mode == न_अंकD_ECC_READ);

	spin_unlock_irqrestore(&davinci_nand_lock, flags);
पूर्ण

/* Read raw ECC code after writing to न_अंकD. */
अटल व्योम
nand_davinci_पढ़ोecc_4bit(काष्ठा davinci_nand_info *info, u32 code[4])
अणु
	स्थिर u32 mask = 0x03ff03ff;

	code[0] = davinci_nand_पढ़ोl(info, न_अंकD_4BIT_ECC1_OFFSET) & mask;
	code[1] = davinci_nand_पढ़ोl(info, न_अंकD_4BIT_ECC2_OFFSET) & mask;
	code[2] = davinci_nand_पढ़ोl(info, न_अंकD_4BIT_ECC3_OFFSET) & mask;
	code[3] = davinci_nand_पढ़ोl(info, न_अंकD_4BIT_ECC4_OFFSET) & mask;
पूर्ण

/* Terminate पढ़ो ECC; or वापस ECC (as bytes) of data written to न_अंकD. */
अटल पूर्णांक nand_davinci_calculate_4bit(काष्ठा nand_chip *chip,
				       स्थिर u_अक्षर *dat, u_अक्षर *ecc_code)
अणु
	काष्ठा davinci_nand_info *info = to_davinci_nand(nand_to_mtd(chip));
	u32 raw_ecc[4], *p;
	अचिन्हित i;

	/* After a पढ़ो, terminate ECC calculation by a dummy पढ़ो
	 * of some 4-bit ECC रेजिस्टर.  ECC covers everything that
	 * was पढ़ो; correct() just uses the hardware state, so
	 * ecc_code is not needed.
	 */
	अगर (info->is_पढ़ोmode) अणु
		davinci_nand_पढ़ोl(info, न_अंकD_4BIT_ECC1_OFFSET);
		वापस 0;
	पूर्ण

	/* Pack eight raw 10-bit ecc values पूर्णांकo ten bytes, making
	 * two passes which each convert four values (in upper and
	 * lower halves of two 32-bit words) पूर्णांकo five bytes.  The
	 * ROM boot loader uses this same packing scheme.
	 */
	nand_davinci_पढ़ोecc_4bit(info, raw_ecc);
	क्रम (i = 0, p = raw_ecc; i < 2; i++, p += 2) अणु
		*ecc_code++ =   p[0]        & 0xff;
		*ecc_code++ = ((p[0] >>  8) & 0x03) | ((p[0] >> 14) & 0xfc);
		*ecc_code++ = ((p[0] >> 22) & 0x0f) | ((p[1] <<  4) & 0xf0);
		*ecc_code++ = ((p[1] >>  4) & 0x3f) | ((p[1] >> 10) & 0xc0);
		*ecc_code++ =  (p[1] >> 18) & 0xff;
	पूर्ण

	वापस 0;
पूर्ण

/* Correct up to 4 bits in data we just पढ़ो, using state left in the
 * hardware plus the ecc_code computed when it was first written.
 */
अटल पूर्णांक nand_davinci_correct_4bit(काष्ठा nand_chip *chip, u_अक्षर *data,
				     u_अक्षर *ecc_code, u_अक्षर *null)
अणु
	पूर्णांक i;
	काष्ठा davinci_nand_info *info = to_davinci_nand(nand_to_mtd(chip));
	अचिन्हित लघु ecc10[8];
	अचिन्हित लघु *ecc16;
	u32 syndrome[4];
	u32 ecc_state;
	अचिन्हित num_errors, corrected;
	अचिन्हित दीर्घ समयo;

	/* Unpack ten bytes पूर्णांकo eight 10 bit values.  We know we're
	 * little-endian, and use type punning क्रम less shअगरting/masking.
	 */
	अगर (WARN_ON(0x01 & (uपूर्णांकptr_t)ecc_code))
		वापस -EINVAL;
	ecc16 = (अचिन्हित लघु *)ecc_code;

	ecc10[0] =  (ecc16[0] >>  0) & 0x3ff;
	ecc10[1] = ((ecc16[0] >> 10) & 0x3f) | ((ecc16[1] << 6) & 0x3c0);
	ecc10[2] =  (ecc16[1] >>  4) & 0x3ff;
	ecc10[3] = ((ecc16[1] >> 14) & 0x3)  | ((ecc16[2] << 2) & 0x3fc);
	ecc10[4] =  (ecc16[2] >>  8)         | ((ecc16[3] << 8) & 0x300);
	ecc10[5] =  (ecc16[3] >>  2) & 0x3ff;
	ecc10[6] = ((ecc16[3] >> 12) & 0xf)  | ((ecc16[4] << 4) & 0x3f0);
	ecc10[7] =  (ecc16[4] >>  6) & 0x3ff;

	/* Tell ECC controller about the expected ECC codes. */
	क्रम (i = 7; i >= 0; i--)
		davinci_nand_ग_लिखोl(info, न_अंकD_4BIT_ECC_LOAD_OFFSET, ecc10[i]);

	/* Allow समय क्रम syndrome calculation ... then पढ़ो it.
	 * A syndrome of all zeroes 0 means no detected errors.
	 */
	davinci_nand_पढ़ोl(info, न_अंकDFSR_OFFSET);
	nand_davinci_पढ़ोecc_4bit(info, syndrome);
	अगर (!(syndrome[0] | syndrome[1] | syndrome[2] | syndrome[3]))
		वापस 0;

	/*
	 * Clear any previous address calculation by करोing a dummy पढ़ो of an
	 * error address रेजिस्टर.
	 */
	davinci_nand_पढ़ोl(info, न_अंकD_ERR_ADD1_OFFSET);

	/* Start address calculation, and रुको क्रम it to complete.
	 * We _could_ start पढ़ोing more data जबतक this is working,
	 * to speed up the overall page पढ़ो.
	 */
	davinci_nand_ग_लिखोl(info, न_अंकDFCR_OFFSET,
			davinci_nand_पढ़ोl(info, न_अंकDFCR_OFFSET) | BIT(13));

	/*
	 * ECC_STATE field पढ़ोs 0x3 (Error correction complete) immediately
	 * after setting the 4BITECC_ADD_CALC_START bit. So अगर you immediately
	 * begin trying to poll क्रम the state, you may fall right out of your
	 * loop without any of the correction calculations having taken place.
	 * The recommendation from the hardware team is to initially delay as
	 * दीर्घ as ECC_STATE पढ़ोs less than 4. After that, ECC HW has entered
	 * correction state.
	 */
	समयo = jअगरfies + usecs_to_jअगरfies(100);
	करो अणु
		ecc_state = (davinci_nand_पढ़ोl(info,
				न_अंकDFSR_OFFSET) >> 8) & 0x0f;
		cpu_relax();
	पूर्ण जबतक ((ecc_state < 4) && समय_beक्रमe(jअगरfies, समयo));

	क्रम (;;) अणु
		u32	fsr = davinci_nand_पढ़ोl(info, न_अंकDFSR_OFFSET);

		चयन ((fsr >> 8) & 0x0f) अणु
		हाल 0:		/* no error, should not happen */
			davinci_nand_पढ़ोl(info, न_अंकD_ERR_ERRVAL1_OFFSET);
			वापस 0;
		हाल 1:		/* five or more errors detected */
			davinci_nand_पढ़ोl(info, न_अंकD_ERR_ERRVAL1_OFFSET);
			वापस -EBADMSG;
		हाल 2:		/* error addresses computed */
		हाल 3:
			num_errors = 1 + ((fsr >> 16) & 0x03);
			जाओ correct;
		शेष:	/* still working on it */
			cpu_relax();
			जारी;
		पूर्ण
	पूर्ण

correct:
	/* correct each error */
	क्रम (i = 0, corrected = 0; i < num_errors; i++) अणु
		पूर्णांक error_address, error_value;

		अगर (i > 1) अणु
			error_address = davinci_nand_पढ़ोl(info,
						न_अंकD_ERR_ADD2_OFFSET);
			error_value = davinci_nand_पढ़ोl(info,
						न_अंकD_ERR_ERRVAL2_OFFSET);
		पूर्ण अन्यथा अणु
			error_address = davinci_nand_पढ़ोl(info,
						न_अंकD_ERR_ADD1_OFFSET);
			error_value = davinci_nand_पढ़ोl(info,
						न_अंकD_ERR_ERRVAL1_OFFSET);
		पूर्ण

		अगर (i & 1) अणु
			error_address >>= 16;
			error_value >>= 16;
		पूर्ण
		error_address &= 0x3ff;
		error_address = (512 + 7) - error_address;

		अगर (error_address < 512) अणु
			data[error_address] ^= error_value;
			corrected++;
		पूर्ण
	पूर्ण

	वापस corrected;
पूर्ण

/**
 * nand_पढ़ो_page_hwecc_oob_first - hw ecc, पढ़ो oob first
 * @chip: nand chip info काष्ठाure
 * @buf: buffer to store पढ़ो data
 * @oob_required: caller requires OOB data पढ़ो to chip->oob_poi
 * @page: page number to पढ़ो
 *
 * Hardware ECC क्रम large page chips, require OOB to be पढ़ो first. For this
 * ECC mode, the ग_लिखो_page method is re-used from ECC_HW. These methods
 * पढ़ो/ग_लिखो ECC from the OOB area, unlike the ECC_HW_SYNDROME support with
 * multiple ECC steps, follows the "infix ECC" scheme and पढ़ोs/ग_लिखोs ECC from
 * the data area, by overwriting the न_अंकD manufacturer bad block markings.
 */
अटल पूर्णांक nand_davinci_पढ़ो_page_hwecc_oob_first(काष्ठा nand_chip *chip,
						  uपूर्णांक8_t *buf,
						  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक i, eccsize = chip->ecc.size, ret;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	uपूर्णांक8_t *p = buf;
	uपूर्णांक8_t *ecc_code = chip->ecc.code_buf;
	uपूर्णांक8_t *ecc_calc = chip->ecc.calc_buf;
	अचिन्हित पूर्णांक max_bitflips = 0;

	/* Read the OOB area first */
	ret = nand_पढ़ो_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
	अगर (ret)
		वापस ret;

	ret = nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	ret = mtd_ooblayout_get_eccbytes(mtd, ecc_code, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) अणु
		पूर्णांक stat;

		chip->ecc.hwctl(chip, न_अंकD_ECC_READ);

		ret = nand_पढ़ो_data_op(chip, p, eccsize, false, false);
		अगर (ret)
			वापस ret;

		chip->ecc.calculate(chip, p, &ecc_calc[i]);

		stat = chip->ecc.correct(chip, p, &ecc_code[i], शून्य);
		अगर (stat == -EBADMSG &&
		    (chip->ecc.options & न_अंकD_ECC_GENERIC_ERASED_CHECK)) अणु
			/* check क्रम empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, eccsize,
							   &ecc_code[i],
							   eccbytes, शून्य, 0,
							   chip->ecc.strength);
		पूर्ण

		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण
	वापस max_bitflips;
पूर्ण

/*----------------------------------------------------------------------*/

/* An ECC layout क्रम using 4-bit ECC with small-page flash, storing
 * ten ECC bytes plus the manufacturer's bad block marker byte, and
 * and not overlapping the शेष BBT markers.
 */
अटल पूर्णांक hwecc4_ooblayout_small_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				      काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 2)
		वापस -दुस्फल;

	अगर (!section) अणु
		oobregion->offset = 0;
		oobregion->length = 5;
	पूर्ण अन्यथा अगर (section == 1) अणु
		oobregion->offset = 6;
		oobregion->length = 2;
	पूर्ण अन्यथा अणु
		oobregion->offset = 13;
		oobregion->length = 3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hwecc4_ooblayout_small_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 1)
		वापस -दुस्फल;

	अगर (!section) अणु
		oobregion->offset = 8;
		oobregion->length = 5;
	पूर्ण अन्यथा अणु
		oobregion->offset = 16;
		oobregion->length = mtd->oobsize - 16;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops hwecc4_small_ooblayout_ops = अणु
	.ecc = hwecc4_ooblayout_small_ecc,
	.मुक्त = hwecc4_ooblayout_small_मुक्त,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id davinci_nand_of_match[] = अणु
	अणु.compatible = "ti,davinci-nand", पूर्ण,
	अणु.compatible = "ti,keystone-nand", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_nand_of_match);

अटल काष्ठा davinci_nand_pdata
	*nand_davinci_get_pdata(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!dev_get_platdata(&pdev->dev) && pdev->dev.of_node) अणु
		काष्ठा davinci_nand_pdata *pdata;
		स्थिर अक्षर *mode;
		u32 prop;

		pdata =  devm_kzalloc(&pdev->dev,
				माप(काष्ठा davinci_nand_pdata),
				GFP_KERNEL);
		pdev->dev.platक्रमm_data = pdata;
		अगर (!pdata)
			वापस ERR_PTR(-ENOMEM);
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
			"ti,davinci-chipselect", &prop))
			pdata->core_chipsel = prop;
		अन्यथा
			वापस ERR_PTR(-EINVAL);

		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
			"ti,davinci-mask-ale", &prop))
			pdata->mask_ale = prop;
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
			"ti,davinci-mask-cle", &prop))
			pdata->mask_cle = prop;
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
			"ti,davinci-mask-chipsel", &prop))
			pdata->mask_chipsel = prop;
		अगर (!of_property_पढ़ो_string(pdev->dev.of_node,
			"ti,davinci-ecc-mode", &mode)) अणु
			अगर (!म_भेदन("none", mode, 4))
				pdata->engine_type = न_अंकD_ECC_ENGINE_TYPE_NONE;
			अगर (!म_भेदन("soft", mode, 4))
				pdata->engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
			अगर (!म_भेदन("hw", mode, 2))
				pdata->engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
		पूर्ण
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
			"ti,davinci-ecc-bits", &prop))
			pdata->ecc_bits = prop;

		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
			"ti,davinci-nand-buswidth", &prop) && prop == 16)
			pdata->options |= न_अंकD_BUSWIDTH_16;

		अगर (of_property_पढ़ो_bool(pdev->dev.of_node,
			"ti,davinci-nand-use-bbt"))
			pdata->bbt_options = न_अंकD_BBT_USE_FLASH;

		/*
		 * Since kernel v4.8, this driver has been fixed to enable
		 * use of 4-bit hardware ECC with subpages and verअगरied on
		 * TI's keystone EVMs (K2L, K2HK and K2E).
		 * However, in the पूर्णांकerest of not अवरोधing प्रणालीs using
		 * existing UBI partitions, sub-page ग_लिखोs are not being
		 * (re)enabled. If you want to use subpage ग_लिखोs on Keystone
		 * platक्रमms (i.e. करो not have any existing UBI partitions),
		 * then use "ti,davinci-nand" as the compatible in your
		 * device-tree file.
		 */
		अगर (of_device_is_compatible(pdev->dev.of_node,
					    "ti,keystone-nand")) अणु
			pdata->options |= न_अंकD_NO_SUBPAGE_WRITE;
		पूर्ण
	पूर्ण

	वापस dev_get_platdata(&pdev->dev);
पूर्ण
#अन्यथा
अटल काष्ठा davinci_nand_pdata
	*nand_davinci_get_pdata(काष्ठा platक्रमm_device *pdev)
अणु
	वापस dev_get_platdata(&pdev->dev);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक davinci_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा davinci_nand_info *info = to_davinci_nand(mtd);
	काष्ठा davinci_nand_pdata *pdata = nand_davinci_get_pdata(info->pdev);
	पूर्णांक ret = 0;

	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	/* Use board-specअगरic ECC config */
	chip->ecc.engine_type = pdata->engine_type;
	chip->ecc.placement = pdata->ecc_placement;

	चयन (chip->ecc.engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
		pdata->ecc_bits = 0;
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		pdata->ecc_bits = 0;
		/*
		 * This driver expects Hamming based ECC when engine_type is set
		 * to न_अंकD_ECC_ENGINE_TYPE_SOFT. Force ecc.algo to
		 * न_अंकD_ECC_ALGO_HAMMING to aव्योम adding an extra ->ecc_algo
		 * field to davinci_nand_pdata.
		 */
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		अगर (pdata->ecc_bits == 4) अणु
			पूर्णांक chunks = mtd->ग_लिखोsize / 512;

			अगर (!chunks || mtd->oobsize < 16) अणु
				dev_dbg(&info->pdev->dev, "too small\n");
				वापस -EINVAL;
			पूर्ण

			/*
			 * No sanity checks:  CPUs must support this,
			 * and the chips may not use न_अंकD_BUSWIDTH_16.
			 */

			/* No sharing 4-bit hardware between chipselects yet */
			spin_lock_irq(&davinci_nand_lock);
			अगर (ecc4_busy)
				ret = -EBUSY;
			अन्यथा
				ecc4_busy = true;
			spin_unlock_irq(&davinci_nand_lock);

			अगर (ret == -EBUSY)
				वापस ret;

			chip->ecc.calculate = nand_davinci_calculate_4bit;
			chip->ecc.correct = nand_davinci_correct_4bit;
			chip->ecc.hwctl = nand_davinci_hwctl_4bit;
			chip->ecc.bytes = 10;
			chip->ecc.options = न_अंकD_ECC_GENERIC_ERASED_CHECK;
			chip->ecc.algo = न_अंकD_ECC_ALGO_BCH;

			/*
			 * Update ECC layout अगर needed ... क्रम 1-bit HW ECC, the
			 * शेष is OK, but it allocates 6 bytes when only 3
			 * are needed (क्रम each 512 bytes). For 4-bit HW ECC,
			 * the शेष is not usable: 10 bytes needed, not 6.
			 *
			 * For small page chips, preserve the manufacturer's
			 * badblock marking data ... and make sure a flash BBT
			 * table marker fits in the मुक्त bytes.
			 */
			अगर (chunks == 1) अणु
				mtd_set_ooblayout(mtd,
						  &hwecc4_small_ooblayout_ops);
			पूर्ण अन्यथा अगर (chunks == 4 || chunks == 8) अणु
				mtd_set_ooblayout(mtd,
						  nand_get_large_page_ooblayout());
				chip->ecc.पढ़ो_page = nand_davinci_पढ़ो_page_hwecc_oob_first;
			पूर्ण अन्यथा अणु
				वापस -EIO;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* 1bit ecc hamming */
			chip->ecc.calculate = nand_davinci_calculate_1bit;
			chip->ecc.correct = nand_davinci_correct_1bit;
			chip->ecc.hwctl = nand_davinci_hwctl_1bit;
			chip->ecc.bytes = 3;
			chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
		पूर्ण
		chip->ecc.size = 512;
		chip->ecc.strength = pdata->ecc_bits;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम nand_davinci_data_in(काष्ठा davinci_nand_info *info, व्योम *buf,
				 अचिन्हित पूर्णांक len, bool क्रमce_8bit)
अणु
	u32 alignment = ((uपूर्णांकptr_t)buf | len) & 3;

	अगर (क्रमce_8bit || (alignment & 1))
		ioपढ़ो8_rep(info->current_cs, buf, len);
	अन्यथा अगर (alignment & 3)
		ioपढ़ो16_rep(info->current_cs, buf, len >> 1);
	अन्यथा
		ioपढ़ो32_rep(info->current_cs, buf, len >> 2);
पूर्ण

अटल व्योम nand_davinci_data_out(काष्ठा davinci_nand_info *info,
				  स्थिर व्योम *buf, अचिन्हित पूर्णांक len,
				  bool क्रमce_8bit)
अणु
	u32 alignment = ((uपूर्णांकptr_t)buf | len) & 3;

	अगर (क्रमce_8bit || (alignment & 1))
		ioग_लिखो8_rep(info->current_cs, buf, len);
	अन्यथा अगर (alignment & 3)
		ioग_लिखो16_rep(info->current_cs, buf, len >> 1);
	अन्यथा
		ioग_लिखो32_rep(info->current_cs, buf, len >> 2);
पूर्ण

अटल पूर्णांक davinci_nand_exec_instr(काष्ठा davinci_nand_info *info,
				   स्थिर काष्ठा nand_op_instr *instr)
अणु
	अचिन्हित पूर्णांक i, समयout_us;
	u32 status;
	पूर्णांक ret;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		ioग_लिखो8(instr->ctx.cmd.opcode,
			 info->current_cs + info->mask_cle);
		अवरोध;

	हाल न_अंकD_OP_ADDR_INSTR:
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++) अणु
			ioग_लिखो8(instr->ctx.addr.addrs[i],
				 info->current_cs + info->mask_ale);
		पूर्ण
		अवरोध;

	हाल न_अंकD_OP_DATA_IN_INSTR:
		nand_davinci_data_in(info, instr->ctx.data.buf.in,
				     instr->ctx.data.len,
				     instr->ctx.data.क्रमce_8bit);
		अवरोध;

	हाल न_अंकD_OP_DATA_OUT_INSTR:
		nand_davinci_data_out(info, instr->ctx.data.buf.out,
				      instr->ctx.data.len,
				      instr->ctx.data.क्रमce_8bit);
		अवरोध;

	हाल न_अंकD_OP_WAITRDY_INSTR:
		समयout_us = instr->ctx.रुकोrdy.समयout_ms * 1000;
		ret = पढ़ोl_relaxed_poll_समयout(info->base + न_अंकDFSR_OFFSET,
						 status, status & BIT(0), 100,
						 समयout_us);
		अगर (ret)
			वापस ret;

		अवरोध;
	पूर्ण

	अगर (instr->delay_ns)
		ndelay(instr->delay_ns);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_nand_exec_op(काष्ठा nand_chip *chip,
				स्थिर काष्ठा nand_operation *op,
				bool check_only)
अणु
	काष्ठा davinci_nand_info *info = to_davinci_nand(nand_to_mtd(chip));
	अचिन्हित पूर्णांक i;

	अगर (check_only)
		वापस 0;

	info->current_cs = info->vaddr + (op->cs * info->mask_chipsel);

	क्रम (i = 0; i < op->ninstrs; i++) अणु
		पूर्णांक ret;

		ret = davinci_nand_exec_instr(info, &op->instrs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops davinci_nand_controller_ops = अणु
	.attach_chip = davinci_nand_attach_chip,
	.exec_op = davinci_nand_exec_op,
पूर्ण;

अटल पूर्णांक nand_davinci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_nand_pdata	*pdata;
	काष्ठा davinci_nand_info	*info;
	काष्ठा resource			*res1;
	काष्ठा resource			*res2;
	व्योम __iomem			*vaddr;
	व्योम __iomem			*base;
	पूर्णांक				ret;
	uपूर्णांक32_t			val;
	काष्ठा mtd_info			*mtd;

	pdata = nand_davinci_get_pdata(pdev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	/* insist on board-specअगरic configuration */
	अगर (!pdata)
		वापस -ENODEV;

	/* which बाह्यal chipselect will we be managing? */
	अगर (pdata->core_chipsel < 0 || pdata->core_chipsel > 3)
		वापस -ENODEV;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, info);

	res1 = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	res2 = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res1 || !res2) अणु
		dev_err(&pdev->dev, "resource missing\n");
		वापस -EINVAL;
	पूर्ण

	vaddr = devm_ioremap_resource(&pdev->dev, res1);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);

	/*
	 * This रेजिस्टरs range is used to setup न_अंकD settings. In हाल with
	 * TI AEMIF driver, the same memory address range is requested alपढ़ोy
	 * by AEMIF, so we cannot request it twice, just ioremap.
	 * The AEMIF and न_अंकD drivers not use the same रेजिस्टरs in this range.
	 */
	base = devm_ioremap(&pdev->dev, res2->start, resource_size(res2));
	अगर (!base) अणु
		dev_err(&pdev->dev, "ioremap failed for resource %pR\n", res2);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	info->pdev		= pdev;
	info->base		= base;
	info->vaddr		= vaddr;

	mtd			= nand_to_mtd(&info->chip);
	mtd->dev.parent		= &pdev->dev;
	nand_set_flash_node(&info->chip, pdev->dev.of_node);

	/* options such as न_अंकD_BBT_USE_FLASH */
	info->chip.bbt_options	= pdata->bbt_options;
	/* options such as 16-bit widths */
	info->chip.options	= pdata->options;
	info->chip.bbt_td	= pdata->bbt_td;
	info->chip.bbt_md	= pdata->bbt_md;
	info->timing		= pdata->timing;

	info->current_cs	= info->vaddr;
	info->core_chipsel	= pdata->core_chipsel;
	info->mask_chipsel	= pdata->mask_chipsel;

	/* use nandboot-capable ALE/CLE masks by शेष */
	info->mask_ale		= pdata->mask_ale ? : MASK_ALE;
	info->mask_cle		= pdata->mask_cle ? : MASK_CLE;

	spin_lock_irq(&davinci_nand_lock);

	/* put CSxन_अंकD पूर्णांकo न_अंकD mode */
	val = davinci_nand_पढ़ोl(info, न_अंकDFCR_OFFSET);
	val |= BIT(info->core_chipsel);
	davinci_nand_ग_लिखोl(info, न_अंकDFCR_OFFSET, val);

	spin_unlock_irq(&davinci_nand_lock);

	/* Scan to find existence of the device(s) */
	nand_controller_init(&info->controller);
	info->controller.ops = &davinci_nand_controller_ops;
	info->chip.controller = &info->controller;
	ret = nand_scan(&info->chip, pdata->mask_chipsel ? 2 : 1);
	अगर (ret < 0) अणु
		dev_dbg(&pdev->dev, "no NAND chip(s) found\n");
		वापस ret;
	पूर्ण

	अगर (pdata->parts)
		ret = mtd_device_रेजिस्टर(mtd, pdata->parts, pdata->nr_parts);
	अन्यथा
		ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret < 0)
		जाओ err_cleanup_nand;

	val = davinci_nand_पढ़ोl(info, NRCSR_OFFSET);
	dev_info(&pdev->dev, "controller rev. %d.%d\n",
	       (val >> 8) & 0xff, val & 0xff);

	वापस 0;

err_cleanup_nand:
	nand_cleanup(&info->chip);

	वापस ret;
पूर्ण

अटल पूर्णांक nand_davinci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_nand_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &info->chip;
	पूर्णांक ret;

	spin_lock_irq(&davinci_nand_lock);
	अगर (chip->ecc.placement == न_अंकD_ECC_PLACEMENT_INTERLEAVED)
		ecc4_busy = false;
	spin_unlock_irq(&davinci_nand_lock);

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver nand_davinci_driver = अणु
	.probe		= nand_davinci_probe,
	.हटाओ		= nand_davinci_हटाओ,
	.driver		= अणु
		.name	= "davinci_nand",
		.of_match_table = of_match_ptr(davinci_nand_of_match),
	पूर्ण,
पूर्ण;
MODULE_ALIAS("platform:davinci_nand");

module_platक्रमm_driver(nand_davinci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("Davinci NAND flash driver");

