<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale GPMI न_अंकD Flash Driver
 *
 * Copyright (C) 2010-2015 Freescale Semiconductor, Inc.
 * Copyright (C) 2008 Embedded Alley Solutions, Inc.
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma/mxs-dma.h>
#समावेश "gpmi-nand.h"
#समावेश "gpmi-regs.h"
#समावेश "bch-regs.h"

/* Resource names क्रम the GPMI न_अंकD driver. */
#घोषणा GPMI_न_अंकD_GPMI_REGS_ADDR_RES_NAME  "gpmi-nand"
#घोषणा GPMI_न_अंकD_BCH_REGS_ADDR_RES_NAME   "bch"
#घोषणा GPMI_न_अंकD_BCH_INTERRUPT_RES_NAME   "bch"

/* Converts समय to घड़ी cycles */
#घोषणा TO_CYCLES(duration, period) DIV_ROUND_UP_ULL(duration, period)

#घोषणा MXS_SET_ADDR		0x4
#घोषणा MXS_CLR_ADDR		0x8
/*
 * Clear the bit and poll it cleared.  This is usually called with
 * a reset address and mask being either SFTRST(bit 31) or CLKGATE
 * (bit 30).
 */
अटल पूर्णांक clear_poll_bit(व्योम __iomem *addr, u32 mask)
अणु
	पूर्णांक समयout = 0x400;

	/* clear the bit */
	ग_लिखोl(mask, addr + MXS_CLR_ADDR);

	/*
	 * SFTRST needs 3 GPMI घड़ीs to settle, the reference manual
	 * recommends to रुको 1us.
	 */
	udelay(1);

	/* poll the bit becoming clear */
	जबतक ((पढ़ोl(addr) & mask) && --समयout)
		/* nothing */;

	वापस !समयout;
पूर्ण

#घोषणा MODULE_CLKGATE		(1 << 30)
#घोषणा MODULE_SFTRST		(1 << 31)
/*
 * The current mxs_reset_block() will करो two things:
 *  [1] enable the module.
 *  [2] reset the module.
 *
 * In most of the हालs, it's ok.
 * But in MX23, there is a hardware bug in the BCH block (see erratum #2847).
 * If you try to soft reset the BCH block, it becomes unusable until
 * the next hard reset. This हाल occurs in the न_अंकD boot mode. When the board
 * boots by न_अंकD, the ROM of the chip will initialize the BCH blocks itself.
 * So If the driver tries to reset the BCH again, the BCH will not work anymore.
 * You will see a DMA समयout in this हाल. The bug has been fixed
 * in the following chips, such as MX28.
 *
 * To aव्योम this bug, just add a new parameter `just_enable` क्रम
 * the mxs_reset_block(), and reग_लिखो it here.
 */
अटल पूर्णांक gpmi_reset_block(व्योम __iomem *reset_addr, bool just_enable)
अणु
	पूर्णांक ret;
	पूर्णांक समयout = 0x400;

	/* clear and poll SFTRST */
	ret = clear_poll_bit(reset_addr, MODULE_SFTRST);
	अगर (unlikely(ret))
		जाओ error;

	/* clear CLKGATE */
	ग_लिखोl(MODULE_CLKGATE, reset_addr + MXS_CLR_ADDR);

	अगर (!just_enable) अणु
		/* set SFTRST to reset the block */
		ग_लिखोl(MODULE_SFTRST, reset_addr + MXS_SET_ADDR);
		udelay(1);

		/* poll CLKGATE becoming set */
		जबतक ((!(पढ़ोl(reset_addr) & MODULE_CLKGATE)) && --समयout)
			/* nothing */;
		अगर (unlikely(!समयout))
			जाओ error;
	पूर्ण

	/* clear and poll SFTRST */
	ret = clear_poll_bit(reset_addr, MODULE_SFTRST);
	अगर (unlikely(ret))
		जाओ error;

	/* clear and poll CLKGATE */
	ret = clear_poll_bit(reset_addr, MODULE_CLKGATE);
	अगर (unlikely(ret))
		जाओ error;

	वापस 0;

error:
	pr_err("%s(%p): module reset timeout\n", __func__, reset_addr);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक __gpmi_enable_clk(काष्ठा gpmi_nand_data *this, bool v)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < GPMI_CLK_MAX; i++) अणु
		clk = this->resources.घड़ी[i];
		अगर (!clk)
			अवरोध;

		अगर (v) अणु
			ret = clk_prepare_enable(clk);
			अगर (ret)
				जाओ err_clk;
		पूर्ण अन्यथा अणु
			clk_disable_unprepare(clk);
		पूर्ण
	पूर्ण
	वापस 0;

err_clk:
	क्रम (; i > 0; i--)
		clk_disable_unprepare(this->resources.घड़ी[i - 1]);
	वापस ret;
पूर्ण

अटल पूर्णांक gpmi_init(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा resources *r = &this->resources;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(this->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(this->dev);
		वापस ret;
	पूर्ण

	ret = gpmi_reset_block(r->gpmi_regs, false);
	अगर (ret)
		जाओ err_out;

	/*
	 * Reset BCH here, too. We got failures otherwise :(
	 * See later BCH reset क्रम explanation of MX23 and MX28 handling
	 */
	ret = gpmi_reset_block(r->bch_regs, GPMI_IS_MXS(this));
	अगर (ret)
		जाओ err_out;

	/* Choose न_अंकD mode. */
	ग_लिखोl(BM_GPMI_CTRL1_GPMI_MODE, r->gpmi_regs + HW_GPMI_CTRL1_CLR);

	/* Set the IRQ polarity. */
	ग_लिखोl(BM_GPMI_CTRL1_ATA_IRQRDY_POLARITY,
				r->gpmi_regs + HW_GPMI_CTRL1_SET);

	/* Disable Write-Protection. */
	ग_लिखोl(BM_GPMI_CTRL1_DEV_RESET, r->gpmi_regs + HW_GPMI_CTRL1_SET);

	/* Select BCH ECC. */
	ग_लिखोl(BM_GPMI_CTRL1_BCH_MODE, r->gpmi_regs + HW_GPMI_CTRL1_SET);

	/*
	 * Decouple the chip select from dma channel. We use dma0 क्रम all
	 * the chips, क्रमce all न_अंकD RDY_BUSY inमाला_दो to be sourced from
	 * RDY_BUSY0.
	 */
	ग_लिखोl(BM_GPMI_CTRL1_DECOUPLE_CS | BM_GPMI_CTRL1_GANGED_RDYBUSY,
	       r->gpmi_regs + HW_GPMI_CTRL1_SET);

err_out:
	pm_runसमय_mark_last_busy(this->dev);
	pm_runसमय_put_स्वतःsuspend(this->dev);
	वापस ret;
पूर्ण

/* This function is very useful. It is called only when the bug occur. */
अटल व्योम gpmi_dump_info(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा resources *r = &this->resources;
	काष्ठा bch_geometry *geo = &this->bch_geometry;
	u32 reg;
	पूर्णांक i;

	dev_err(this->dev, "Show GPMI registers :\n");
	क्रम (i = 0; i <= HW_GPMI_DEBUG / 0x10 + 1; i++) अणु
		reg = पढ़ोl(r->gpmi_regs + i * 0x10);
		dev_err(this->dev, "offset 0x%.3x : 0x%.8x\n", i * 0x10, reg);
	पूर्ण

	/* start to prपूर्णांक out the BCH info */
	dev_err(this->dev, "Show BCH registers :\n");
	क्रम (i = 0; i <= HW_BCH_VERSION / 0x10 + 1; i++) अणु
		reg = पढ़ोl(r->bch_regs + i * 0x10);
		dev_err(this->dev, "offset 0x%.3x : 0x%.8x\n", i * 0x10, reg);
	पूर्ण
	dev_err(this->dev, "BCH Geometry :\n"
		"GF length              : %u\n"
		"ECC Strength           : %u\n"
		"Page Size in Bytes     : %u\n"
		"Metadata Size in Bytes : %u\n"
		"ECC Chunk Size in Bytes: %u\n"
		"ECC Chunk Count        : %u\n"
		"Payload Size in Bytes  : %u\n"
		"Auxiliary Size in Bytes: %u\n"
		"Auxiliary Status Offset: %u\n"
		"Block Mark Byte Offset : %u\n"
		"Block Mark Bit Offset  : %u\n",
		geo->gf_len,
		geo->ecc_strength,
		geo->page_size,
		geo->metadata_size,
		geo->ecc_chunk_size,
		geo->ecc_chunk_count,
		geo->payload_size,
		geo->auxiliary_size,
		geo->auxiliary_status_offset,
		geo->block_mark_byte_offset,
		geo->block_mark_bit_offset);
पूर्ण

अटल अंतरभूत bool gpmi_check_ecc(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा bch_geometry *geo = &this->bch_geometry;

	/* Do the sanity check. */
	अगर (GPMI_IS_MXS(this)) अणु
		/* The mx23/mx28 only support the GF13. */
		अगर (geo->gf_len == 14)
			वापस false;
	पूर्ण
	वापस geo->ecc_strength <= this->devdata->bch_max_ecc_strength;
पूर्ण

/*
 * If we can get the ECC inक्रमmation from the nand chip, we करो not
 * need to calculate them ourselves.
 *
 * We may have available oob space in this हाल.
 */
अटल पूर्णांक set_geometry_by_ecc_info(काष्ठा gpmi_nand_data *this,
				    अचिन्हित पूर्णांक ecc_strength,
				    अचिन्हित पूर्णांक ecc_step)
अणु
	काष्ठा bch_geometry *geo = &this->bch_geometry;
	काष्ठा nand_chip *chip = &this->nand;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित पूर्णांक block_mark_bit_offset;

	चयन (ecc_step) अणु
	हाल SZ_512:
		geo->gf_len = 13;
		अवरोध;
	हाल SZ_1K:
		geo->gf_len = 14;
		अवरोध;
	शेष:
		dev_err(this->dev,
			"unsupported nand chip. ecc bits : %d, ecc size : %d\n",
			nanddev_get_ecc_requirements(&chip->base)->strength,
			nanddev_get_ecc_requirements(&chip->base)->step_size);
		वापस -EINVAL;
	पूर्ण
	geo->ecc_chunk_size = ecc_step;
	geo->ecc_strength = round_up(ecc_strength, 2);
	अगर (!gpmi_check_ecc(this))
		वापस -EINVAL;

	/* Keep the C >= O */
	अगर (geo->ecc_chunk_size < mtd->oobsize) अणु
		dev_err(this->dev,
			"unsupported nand chip. ecc size: %d, oob size : %d\n",
			ecc_step, mtd->oobsize);
		वापस -EINVAL;
	पूर्ण

	/* The शेष value, see comment in the legacy_set_geometry(). */
	geo->metadata_size = 10;

	geo->ecc_chunk_count = mtd->ग_लिखोsize / geo->ecc_chunk_size;

	/*
	 * Now, the न_अंकD chip with 2K page(data chunk is 512byte) shows below:
	 *
	 *    |                          P                            |
	 *    |<----------------------------------------------------->|
	 *    |                                                       |
	 *    |                                        (Block Mark)   |
	 *    |                      P'                      |      | |     |
	 *    |<-------------------------------------------->|  D   | |  O' |
	 *    |                                              |<---->| |<--->|
	 *    V                                              V      V V     V
	 *    +---+----------+-+----------+-+----------+-+----------+-+-----+
	 *    | M |   data   |E|   data   |E|   data   |E|   data   |E|     |
	 *    +---+----------+-+----------+-+----------+-+----------+-+-----+
	 *                                                   ^              ^
	 *                                                   |      O       |
	 *                                                   |<------------>|
	 *                                                   |              |
	 *
	 *	P : the page size क्रम BCH module.
	 *	E : The ECC strength.
	 *	G : the length of Galois Field.
	 *	N : The chunk count of per page.
	 *	M : the metasize of per page.
	 *	C : the ecc chunk size, aka the "data" above.
	 *	P': the nand chip's page size.
	 *	O : the nand chip's oob size.
	 *	O': the मुक्त oob.
	 *
	 *	The क्रमmula क्रम P is :
	 *
	 *	            E * G * N
	 *	       P = ------------ + P' + M
	 *                      8
	 *
	 * The position of block mark moves क्रमward in the ECC-based view
	 * of page, and the delta is:
	 *
	 *                   E * G * (N - 1)
	 *             D = (---------------- + M)
	 *                          8
	 *
	 * Please see the comment in legacy_set_geometry().
	 * With the condition C >= O , we still can get same result.
	 * So the bit position of the physical block mark within the ECC-based
	 * view of the page is :
	 *             (P' - D) * 8
	 */
	geo->page_size = mtd->ग_लिखोsize + geo->metadata_size +
		(geo->gf_len * geo->ecc_strength * geo->ecc_chunk_count) / 8;

	geo->payload_size = mtd->ग_लिखोsize;

	geo->auxiliary_status_offset = ALIGN(geo->metadata_size, 4);
	geo->auxiliary_size = ALIGN(geo->metadata_size, 4)
				+ ALIGN(geo->ecc_chunk_count, 4);

	अगर (!this->swap_block_mark)
		वापस 0;

	/* For bit swap. */
	block_mark_bit_offset = mtd->ग_लिखोsize * 8 -
		(geo->ecc_strength * geo->gf_len * (geo->ecc_chunk_count - 1)
				+ geo->metadata_size * 8);

	geo->block_mark_byte_offset = block_mark_bit_offset / 8;
	geo->block_mark_bit_offset  = block_mark_bit_offset % 8;
	वापस 0;
पूर्ण

/*
 *  Calculate the ECC strength by hand:
 *	E : The ECC strength.
 *	G : the length of Galois Field.
 *	N : The chunk count of per page.
 *	O : the oobsize of the न_अंकD chip.
 *	M : the metasize of per page.
 *
 *	The क्रमmula is :
 *		E * G * N
 *	      ------------ <= (O - M)
 *                  8
 *
 *      So, we get E by:
 *                    (O - M) * 8
 *              E <= -------------
 *                       G * N
 */
अटल अंतरभूत पूर्णांक get_ecc_strength(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा bch_geometry *geo = &this->bch_geometry;
	काष्ठा mtd_info	*mtd = nand_to_mtd(&this->nand);
	पूर्णांक ecc_strength;

	ecc_strength = ((mtd->oobsize - geo->metadata_size) * 8)
			/ (geo->gf_len * geo->ecc_chunk_count);

	/* We need the minor even number. */
	वापस round_करोwn(ecc_strength, 2);
पूर्ण

अटल पूर्णांक legacy_set_geometry(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा bch_geometry *geo = &this->bch_geometry;
	काष्ठा mtd_info *mtd = nand_to_mtd(&this->nand);
	अचिन्हित पूर्णांक metadata_size;
	अचिन्हित पूर्णांक status_size;
	अचिन्हित पूर्णांक block_mark_bit_offset;

	/*
	 * The size of the metadata can be changed, though we set it to 10
	 * bytes now. But it can't be too large, because we have to save
	 * enough space क्रम BCH.
	 */
	geo->metadata_size = 10;

	/* The शेष क्रम the length of Galois Field. */
	geo->gf_len = 13;

	/* The शेष क्रम chunk size. */
	geo->ecc_chunk_size = 512;
	जबतक (geo->ecc_chunk_size < mtd->oobsize) अणु
		geo->ecc_chunk_size *= 2; /* keep C >= O */
		geo->gf_len = 14;
	पूर्ण

	geo->ecc_chunk_count = mtd->ग_लिखोsize / geo->ecc_chunk_size;

	/* We use the same ECC strength क्रम all chunks. */
	geo->ecc_strength = get_ecc_strength(this);
	अगर (!gpmi_check_ecc(this)) अणु
		dev_err(this->dev,
			"ecc strength: %d cannot be supported by the controller (%d)\n"
			"try to use minimum ecc strength that NAND chip required\n",
			geo->ecc_strength,
			this->devdata->bch_max_ecc_strength);
		वापस -EINVAL;
	पूर्ण

	geo->page_size = mtd->ग_लिखोsize + geo->metadata_size +
		(geo->gf_len * geo->ecc_strength * geo->ecc_chunk_count) / 8;
	geo->payload_size = mtd->ग_लिखोsize;

	/*
	 * The auxiliary buffer contains the metadata and the ECC status. The
	 * metadata is padded to the nearest 32-bit boundary. The ECC status
	 * contains one byte क्रम every ECC chunk, and is also padded to the
	 * nearest 32-bit boundary.
	 */
	metadata_size = ALIGN(geo->metadata_size, 4);
	status_size   = ALIGN(geo->ecc_chunk_count, 4);

	geo->auxiliary_size = metadata_size + status_size;
	geo->auxiliary_status_offset = metadata_size;

	अगर (!this->swap_block_mark)
		वापस 0;

	/*
	 * We need to compute the byte and bit offsets of
	 * the physical block mark within the ECC-based view of the page.
	 *
	 * न_अंकD chip with 2K page shows below:
	 *                                             (Block Mark)
	 *                                                   |      |
	 *                                                   |  D   |
	 *                                                   |<---->|
	 *                                                   V      V
	 *    +---+----------+-+----------+-+----------+-+----------+-+
	 *    | M |   data   |E|   data   |E|   data   |E|   data   |E|
	 *    +---+----------+-+----------+-+----------+-+----------+-+
	 *
	 * The position of block mark moves क्रमward in the ECC-based view
	 * of page, and the delta is:
	 *
	 *                   E * G * (N - 1)
	 *             D = (---------------- + M)
	 *                          8
	 *
	 * With the क्रमmula to compute the ECC strength, and the condition
	 *       : C >= O         (C is the ecc chunk size)
	 *
	 * It's easy to deduce to the following result:
	 *
	 *         E * G       (O - M)      C - M         C - M
	 *      ----------- <= ------- <=  --------  <  ---------
	 *           8            N           N          (N - 1)
	 *
	 *  So, we get:
	 *
	 *                   E * G * (N - 1)
	 *             D = (---------------- + M) < C
	 *                          8
	 *
	 *  The above inequality means the position of block mark
	 *  within the ECC-based view of the page is still in the data chunk,
	 *  and it's NOT in the ECC bits of the chunk.
	 *
	 *  Use the following to compute the bit position of the
	 *  physical block mark within the ECC-based view of the page:
	 *          (page_size - D) * 8
	 *
	 *  --Huang Shijie
	 */
	block_mark_bit_offset = mtd->ग_लिखोsize * 8 -
		(geo->ecc_strength * geo->gf_len * (geo->ecc_chunk_count - 1)
				+ geo->metadata_size * 8);

	geo->block_mark_byte_offset = block_mark_bit_offset / 8;
	geo->block_mark_bit_offset  = block_mark_bit_offset % 8;
	वापस 0;
पूर्ण

अटल पूर्णांक common_nfc_set_geometry(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा nand_chip *chip = &this->nand;
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&chip->base);

	अगर (chip->ecc.strength > 0 && chip->ecc.size > 0)
		वापस set_geometry_by_ecc_info(this, chip->ecc.strength,
						chip->ecc.size);

	अगर ((of_property_पढ़ो_bool(this->dev->of_node, "fsl,use-minimum-ecc"))
				|| legacy_set_geometry(this)) अणु
		अगर (!(requirements->strength > 0 && requirements->step_size > 0))
			वापस -EINVAL;

		वापस set_geometry_by_ecc_info(this,
						requirements->strength,
						requirements->step_size);
	पूर्ण

	वापस 0;
पूर्ण

/* Configures the geometry क्रम BCH.  */
अटल पूर्णांक bch_set_geometry(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा resources *r = &this->resources;
	पूर्णांक ret;

	ret = common_nfc_set_geometry(this);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_get_sync(this->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(this->dev);
		वापस ret;
	पूर्ण

	/*
	* Due to erratum #2847 of the MX23, the BCH cannot be soft reset on this
	* chip, otherwise it will lock up. So we skip resetting BCH on the MX23.
	* and MX28.
	*/
	ret = gpmi_reset_block(r->bch_regs, GPMI_IS_MXS(this));
	अगर (ret)
		जाओ err_out;

	/* Set *all* chip selects to use layout 0. */
	ग_लिखोl(0, r->bch_regs + HW_BCH_LAYOUTSELECT);

	ret = 0;
err_out:
	pm_runसमय_mark_last_busy(this->dev);
	pm_runसमय_put_स्वतःsuspend(this->dev);

	वापस ret;
पूर्ण

/*
 * <1> Firstly, we should know what's the GPMI-घड़ी means.
 *     The GPMI-घड़ी is the पूर्णांकernal घड़ी in the gpmi nand controller.
 *     If you set 100MHz to gpmi nand controller, the GPMI-घड़ी's period
 *     is 10ns. Mark the GPMI-घड़ी's period as GPMI-घड़ी-period.
 *
 * <2> Secondly, we should know what's the frequency on the nand chip pins.
 *     The frequency on the nand chip pins is derived from the GPMI-घड़ी.
 *     We can get it from the following equation:
 *
 *         F = G / (DS + DH)
 *
 *         F  : the frequency on the nand chip pins.
 *         G  : the GPMI घड़ी, such as 100MHz.
 *         DS : GPMI_HW_GPMI_TIMING0:DATA_SETUP
 *         DH : GPMI_HW_GPMI_TIMING0:DATA_HOLD
 *
 * <3> Thirdly, when the frequency on the nand chip pins is above 33MHz,
 *     the nand EDO(extended Data Out) timing could be applied.
 *     The GPMI implements a feedback पढ़ो strobe to sample the पढ़ो data.
 *     The feedback पढ़ो strobe can be delayed to support the nand EDO timing
 *     where the पढ़ो strobe may deनिश्चितs beक्रमe the पढ़ो data is valid, and
 *     पढ़ो data is valid क्रम some समय after पढ़ो strobe.
 *
 *     The following figure illustrates some aspects of a न_अंकD Flash पढ़ो:
 *
 *                   |<---tREA---->|
 *                   |             |
 *                   |         |   |
 *                   |<--tRP-->|   |
 *                   |         |   |
 *                  __          ___|__________________________________
 *     RDN            \________/   |
 *                                 |
 *                                 /---------\
 *     Read Data    --------------<           >---------
 *                                 \---------/
 *                                |     |
 *                                |<-D->|
 *     FeedbackRDN  ________             ____________
 *                          \___________/
 *
 *          D stands क्रम delay, set in the HW_GPMI_CTRL1:RDN_DELAY.
 *
 *
 * <4> Now, we begin to describe how to compute the right RDN_DELAY.
 *
 *  4.1) From the aspect of the nand chip pins:
 *        Delay = (tREA + C - tRP)               अणु1पूर्ण
 *
 *        tREA : the maximum पढ़ो access समय.
 *        C    : a स्थिरant to adjust the delay. शेष is 4000ps.
 *        tRP  : the पढ़ो pulse width, which is exactly:
 *                   tRP = (GPMI-घड़ी-period) * DATA_SETUP
 *
 *  4.2) From the aspect of the GPMI nand controller:
 *         Delay = RDN_DELAY * 0.125 * RP        अणु2पूर्ण
 *
 *         RP   : the DLL reference period.
 *            अगर (GPMI-घड़ी-period > DLL_THRETHOLD)
 *                   RP = GPMI-घड़ी-period / 2;
 *            अन्यथा
 *                   RP = GPMI-घड़ी-period;
 *
 *            Set the HW_GPMI_CTRL1:HALF_PERIOD अगर GPMI-घड़ी-period
 *            is greater DLL_THRETHOLD. In other SOCs, the DLL_THRETHOLD
 *            is 16000ps, but in mx6q, we use 12000ps.
 *
 *  4.3) since अणु1पूर्ण equals अणु2पूर्ण, we get:
 *
 *                     (tREA + 4000 - tRP) * 8
 *         RDN_DELAY = -----------------------     अणु3पूर्ण
 *                           RP
 */
अटल व्योम gpmi_nfc_compute_timings(काष्ठा gpmi_nand_data *this,
				     स्थिर काष्ठा nand_sdr_timings *sdr)
अणु
	काष्ठा gpmi_nfc_hardware_timing *hw = &this->hw;
	अचिन्हित पूर्णांक dll_threshold_ps = this->devdata->max_chain_delay;
	अचिन्हित पूर्णांक period_ps, reference_period_ps;
	अचिन्हित पूर्णांक data_setup_cycles, data_hold_cycles, addr_setup_cycles;
	अचिन्हित पूर्णांक tRP_ps;
	bool use_half_period;
	पूर्णांक sample_delay_ps, sample_delay_factor;
	u16 busy_समयout_cycles;
	u8 wrn_dly_sel;

	अगर (sdr->tRC_min >= 30000) अणु
		/* ONFI non-EDO modes [0-3] */
		hw->clk_rate = 22000000;
		wrn_dly_sel = BV_GPMI_CTRL1_WRN_DLY_SEL_4_TO_8NS;
	पूर्ण अन्यथा अगर (sdr->tRC_min >= 25000) अणु
		/* ONFI EDO mode 4 */
		hw->clk_rate = 80000000;
		wrn_dly_sel = BV_GPMI_CTRL1_WRN_DLY_SEL_NO_DELAY;
	पूर्ण अन्यथा अणु
		/* ONFI EDO mode 5 */
		hw->clk_rate = 100000000;
		wrn_dly_sel = BV_GPMI_CTRL1_WRN_DLY_SEL_NO_DELAY;
	पूर्ण

	/* SDR core timings are given in picoseconds */
	period_ps = भाग_u64((u64)NSEC_PER_SEC * 1000, hw->clk_rate);

	addr_setup_cycles = TO_CYCLES(sdr->tALS_min, period_ps);
	data_setup_cycles = TO_CYCLES(sdr->tDS_min, period_ps);
	data_hold_cycles = TO_CYCLES(sdr->tDH_min, period_ps);
	busy_समयout_cycles = TO_CYCLES(sdr->tWB_max + sdr->tR_max, period_ps);

	hw->timing0 = BF_GPMI_TIMING0_ADDRESS_SETUP(addr_setup_cycles) |
		      BF_GPMI_TIMING0_DATA_HOLD(data_hold_cycles) |
		      BF_GPMI_TIMING0_DATA_SETUP(data_setup_cycles);
	hw->timing1 = BF_GPMI_TIMING1_BUSY_TIMEOUT(busy_समयout_cycles * 4096);

	/*
	 * Derive NFC ideal delay from अणु3पूर्ण:
	 *
	 *                     (tREA + 4000 - tRP) * 8
	 *         RDN_DELAY = -----------------------
	 *                                RP
	 */
	अगर (period_ps > dll_threshold_ps) अणु
		use_half_period = true;
		reference_period_ps = period_ps / 2;
	पूर्ण अन्यथा अणु
		use_half_period = false;
		reference_period_ps = period_ps;
	पूर्ण

	tRP_ps = data_setup_cycles * period_ps;
	sample_delay_ps = (sdr->tREA_max + 4000 - tRP_ps) * 8;
	अगर (sample_delay_ps > 0)
		sample_delay_factor = sample_delay_ps / reference_period_ps;
	अन्यथा
		sample_delay_factor = 0;

	hw->ctrl1n = BF_GPMI_CTRL1_WRN_DLY_SEL(wrn_dly_sel);
	अगर (sample_delay_factor)
		hw->ctrl1n |= BF_GPMI_CTRL1_RDN_DELAY(sample_delay_factor) |
			      BM_GPMI_CTRL1_DLL_ENABLE |
			      (use_half_period ? BM_GPMI_CTRL1_HALF_PERIOD : 0);
पूर्ण

अटल व्योम gpmi_nfc_apply_timings(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा gpmi_nfc_hardware_timing *hw = &this->hw;
	काष्ठा resources *r = &this->resources;
	व्योम __iomem *gpmi_regs = r->gpmi_regs;
	अचिन्हित पूर्णांक dll_रुको_समय_us;

	clk_set_rate(r->घड़ी[0], hw->clk_rate);

	ग_लिखोl(hw->timing0, gpmi_regs + HW_GPMI_TIMING0);
	ग_लिखोl(hw->timing1, gpmi_regs + HW_GPMI_TIMING1);

	/*
	 * Clear several CTRL1 fields, DLL must be disabled when setting
	 * RDN_DELAY or HALF_PERIOD.
	 */
	ग_लिखोl(BM_GPMI_CTRL1_CLEAR_MASK, gpmi_regs + HW_GPMI_CTRL1_CLR);
	ग_लिखोl(hw->ctrl1n, gpmi_regs + HW_GPMI_CTRL1_SET);

	/* Wait 64 घड़ी cycles beक्रमe using the GPMI after enabling the DLL */
	dll_रुको_समय_us = USEC_PER_SEC / hw->clk_rate * 64;
	अगर (!dll_रुको_समय_us)
		dll_रुको_समय_us = 1;

	/* Wait क्रम the DLL to settle. */
	udelay(dll_रुको_समय_us);
पूर्ण

अटल पूर्णांक gpmi_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr,
				स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	स्थिर काष्ठा nand_sdr_timings *sdr;

	/* Retrieve required न_अंकD timings */
	sdr = nand_get_sdr_timings(conf);
	अगर (IS_ERR(sdr))
		वापस PTR_ERR(sdr);

	/* Only MX6 GPMI controller can reach EDO timings */
	अगर (sdr->tRC_min <= 25000 && !GPMI_IS_MX6(this))
		वापस -ENOTSUPP;

	/* Stop here अगर this call was just a check */
	अगर (chipnr < 0)
		वापस 0;

	/* Do the actual derivation of the controller timings */
	gpmi_nfc_compute_timings(this, sdr);

	this->hw.must_apply_timings = true;

	वापस 0;
पूर्ण

/* Clears a BCH पूर्णांकerrupt. */
अटल व्योम gpmi_clear_bch(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा resources *r = &this->resources;
	ग_लिखोl(BM_BCH_CTRL_COMPLETE_IRQ, r->bch_regs + HW_BCH_CTRL_CLR);
पूर्ण

अटल काष्ठा dma_chan *get_dma_chan(काष्ठा gpmi_nand_data *this)
अणु
	/* We use the DMA channel 0 to access all the nand chips. */
	वापस this->dma_chans[0];
पूर्ण

/* This will be called after the DMA operation is finished. */
अटल व्योम dma_irq_callback(व्योम *param)
अणु
	काष्ठा gpmi_nand_data *this = param;
	काष्ठा completion *dma_c = &this->dma_करोne;

	complete(dma_c);
पूर्ण

अटल irqवापस_t bch_irq(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा gpmi_nand_data *this = cookie;

	gpmi_clear_bch(this);
	complete(&this->bch_करोne);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gpmi_raw_len_to_len(काष्ठा gpmi_nand_data *this, पूर्णांक raw_len)
अणु
	/*
	 * raw_len is the length to पढ़ो/ग_लिखो including bch data which
	 * we are passed in exec_op. Calculate the data length from it.
	 */
	अगर (this->bch)
		वापस ALIGN_DOWN(raw_len, this->bch_geometry.ecc_chunk_size);
	अन्यथा
		वापस raw_len;
पूर्ण

/* Can we use the upper's buffer directly क्रम DMA? */
अटल bool prepare_data_dma(काष्ठा gpmi_nand_data *this, स्थिर व्योम *buf,
			     पूर्णांक raw_len, काष्ठा scatterlist *sgl,
			     क्रमागत dma_data_direction dr)
अणु
	पूर्णांक ret;
	पूर्णांक len = gpmi_raw_len_to_len(this, raw_len);

	/* first try to map the upper buffer directly */
	अगर (virt_addr_valid(buf) && !object_is_on_stack(buf)) अणु
		sg_init_one(sgl, buf, len);
		ret = dma_map_sg(this->dev, sgl, 1, dr);
		अगर (ret == 0)
			जाओ map_fail;

		वापस true;
	पूर्ण

map_fail:
	/* We have to use our own DMA buffer. */
	sg_init_one(sgl, this->data_buffer_dma, len);

	अगर (dr == DMA_TO_DEVICE && buf != this->data_buffer_dma)
		स_नकल(this->data_buffer_dma, buf, len);

	dma_map_sg(this->dev, sgl, 1, dr);

	वापस false;
पूर्ण

/* add our owner bbt descriptor */
अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff पूर्ण;
अटल काष्ठा nand_bbt_descr gpmi_bbt_descr = अणु
	.options	= 0,
	.offs		= 0,
	.len		= 1,
	.pattern	= scan_ff_pattern
पूर्ण;

/*
 * We may change the layout अगर we can get the ECC info from the datasheet,
 * अन्यथा we will use all the (page + OOB).
 */
अटल पूर्णांक gpmi_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
			      काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा bch_geometry *geo = &this->bch_geometry;

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 0;
	oobregion->length = geo->page_size - mtd->ग_लिखोsize;

	वापस 0;
पूर्ण

अटल पूर्णांक gpmi_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
			       काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा bch_geometry *geo = &this->bch_geometry;

	अगर (section)
		वापस -दुस्फल;

	/* The available oob size we have. */
	अगर (geo->page_size < mtd->ग_लिखोsize + mtd->oobsize) अणु
		oobregion->offset = geo->page_size - mtd->ग_लिखोsize;
		oobregion->length = mtd->oobsize - oobregion->offset;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर gpmi_clks_क्रम_mx2x[] = अणु
	"gpmi_io",
पूर्ण;

अटल स्थिर काष्ठा mtd_ooblayout_ops gpmi_ooblayout_ops = अणु
	.ecc = gpmi_ooblayout_ecc,
	.मुक्त = gpmi_ooblayout_मुक्त,
पूर्ण;

अटल स्थिर काष्ठा gpmi_devdata gpmi_devdata_imx23 = अणु
	.type = IS_MX23,
	.bch_max_ecc_strength = 20,
	.max_chain_delay = 16000,
	.clks = gpmi_clks_क्रम_mx2x,
	.clks_count = ARRAY_SIZE(gpmi_clks_क्रम_mx2x),
पूर्ण;

अटल स्थिर काष्ठा gpmi_devdata gpmi_devdata_imx28 = अणु
	.type = IS_MX28,
	.bch_max_ecc_strength = 20,
	.max_chain_delay = 16000,
	.clks = gpmi_clks_क्रम_mx2x,
	.clks_count = ARRAY_SIZE(gpmi_clks_क्रम_mx2x),
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpmi_clks_क्रम_mx6[] = अणु
	"gpmi_io", "gpmi_apb", "gpmi_bch", "gpmi_bch_apb", "per1_bch",
पूर्ण;

अटल स्थिर काष्ठा gpmi_devdata gpmi_devdata_imx6q = अणु
	.type = IS_MX6Q,
	.bch_max_ecc_strength = 40,
	.max_chain_delay = 12000,
	.clks = gpmi_clks_क्रम_mx6,
	.clks_count = ARRAY_SIZE(gpmi_clks_क्रम_mx6),
पूर्ण;

अटल स्थिर काष्ठा gpmi_devdata gpmi_devdata_imx6sx = अणु
	.type = IS_MX6SX,
	.bch_max_ecc_strength = 62,
	.max_chain_delay = 12000,
	.clks = gpmi_clks_क्रम_mx6,
	.clks_count = ARRAY_SIZE(gpmi_clks_क्रम_mx6),
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpmi_clks_क्रम_mx7d[] = अणु
	"gpmi_io", "gpmi_bch_apb",
पूर्ण;

अटल स्थिर काष्ठा gpmi_devdata gpmi_devdata_imx7d = अणु
	.type = IS_MX7D,
	.bch_max_ecc_strength = 62,
	.max_chain_delay = 12000,
	.clks = gpmi_clks_क्रम_mx7d,
	.clks_count = ARRAY_SIZE(gpmi_clks_क्रम_mx7d),
पूर्ण;

अटल पूर्णांक acquire_रेजिस्टर_block(काष्ठा gpmi_nand_data *this,
				  स्थिर अक्षर *res_name)
अणु
	काष्ठा platक्रमm_device *pdev = this->pdev;
	काष्ठा resources *res = &this->resources;
	काष्ठा resource *r;
	व्योम __iomem *p;

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, res_name);
	p = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	अगर (!म_भेद(res_name, GPMI_न_अंकD_GPMI_REGS_ADDR_RES_NAME))
		res->gpmi_regs = p;
	अन्यथा अगर (!म_भेद(res_name, GPMI_न_अंकD_BCH_REGS_ADDR_RES_NAME))
		res->bch_regs = p;
	अन्यथा
		dev_err(this->dev, "unknown resource name : %s\n", res_name);

	वापस 0;
पूर्ण

अटल पूर्णांक acquire_bch_irq(काष्ठा gpmi_nand_data *this, irq_handler_t irq_h)
अणु
	काष्ठा platक्रमm_device *pdev = this->pdev;
	स्थिर अक्षर *res_name = GPMI_न_अंकD_BCH_INTERRUPT_RES_NAME;
	काष्ठा resource *r;
	पूर्णांक err;

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, res_name);
	अगर (!r) अणु
		dev_err(this->dev, "Can't get resource for %s\n", res_name);
		वापस -ENODEV;
	पूर्ण

	err = devm_request_irq(this->dev, r->start, irq_h, 0, res_name, this);
	अगर (err)
		dev_err(this->dev, "error requesting BCH IRQ\n");

	वापस err;
पूर्ण

अटल व्योम release_dma_channels(काष्ठा gpmi_nand_data *this)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < DMA_CHANS; i++)
		अगर (this->dma_chans[i]) अणु
			dma_release_channel(this->dma_chans[i]);
			this->dma_chans[i] = शून्य;
		पूर्ण
पूर्ण

अटल पूर्णांक acquire_dma_channels(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा platक्रमm_device *pdev = this->pdev;
	काष्ठा dma_chan *dma_chan;
	पूर्णांक ret = 0;

	/* request dma channel */
	dma_chan = dma_request_chan(&pdev->dev, "rx-tx");
	अगर (IS_ERR(dma_chan)) अणु
		ret = dev_err_probe(this->dev, PTR_ERR(dma_chan),
				    "DMA channel request failed\n");
		release_dma_channels(this);
	पूर्ण अन्यथा अणु
		this->dma_chans[0] = dma_chan;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gpmi_get_clks(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा resources *r = &this->resources;
	काष्ठा clk *clk;
	पूर्णांक err, i;

	क्रम (i = 0; i < this->devdata->clks_count; i++) अणु
		clk = devm_clk_get(this->dev, this->devdata->clks[i]);
		अगर (IS_ERR(clk)) अणु
			err = PTR_ERR(clk);
			जाओ err_घड़ी;
		पूर्ण

		r->घड़ी[i] = clk;
	पूर्ण

	अगर (GPMI_IS_MX6(this))
		/*
		 * Set the शेष value क्रम the gpmi घड़ी.
		 *
		 * If you want to use the ONFI nand which is in the
		 * Synchronous Mode, you should change the घड़ी as you need.
		 */
		clk_set_rate(r->घड़ी[0], 22000000);

	वापस 0;

err_घड़ी:
	dev_dbg(this->dev, "failed in finding the clocks.\n");
	वापस err;
पूर्ण

अटल पूर्णांक acquire_resources(काष्ठा gpmi_nand_data *this)
अणु
	पूर्णांक ret;

	ret = acquire_रेजिस्टर_block(this, GPMI_न_अंकD_GPMI_REGS_ADDR_RES_NAME);
	अगर (ret)
		जाओ निकास_regs;

	ret = acquire_रेजिस्टर_block(this, GPMI_न_अंकD_BCH_REGS_ADDR_RES_NAME);
	अगर (ret)
		जाओ निकास_regs;

	ret = acquire_bch_irq(this, bch_irq);
	अगर (ret)
		जाओ निकास_regs;

	ret = acquire_dma_channels(this);
	अगर (ret)
		जाओ निकास_regs;

	ret = gpmi_get_clks(this);
	अगर (ret)
		जाओ निकास_घड़ी;
	वापस 0;

निकास_घड़ी:
	release_dma_channels(this);
निकास_regs:
	वापस ret;
पूर्ण

अटल व्योम release_resources(काष्ठा gpmi_nand_data *this)
अणु
	release_dma_channels(this);
पूर्ण

अटल व्योम gpmi_मुक्त_dma_buffer(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा device *dev = this->dev;
	काष्ठा bch_geometry *geo = &this->bch_geometry;

	अगर (this->auxiliary_virt && virt_addr_valid(this->auxiliary_virt))
		dma_मुक्त_coherent(dev, geo->auxiliary_size,
					this->auxiliary_virt,
					this->auxiliary_phys);
	kमुक्त(this->data_buffer_dma);
	kमुक्त(this->raw_buffer);

	this->data_buffer_dma	= शून्य;
	this->raw_buffer	= शून्य;
पूर्ण

/* Allocate the DMA buffers */
अटल पूर्णांक gpmi_alloc_dma_buffer(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा bch_geometry *geo = &this->bch_geometry;
	काष्ठा device *dev = this->dev;
	काष्ठा mtd_info *mtd = nand_to_mtd(&this->nand);

	/*
	 * [2] Allocate a पढ़ो/ग_लिखो data buffer.
	 *     The gpmi_alloc_dma_buffer can be called twice.
	 *     We allocate a PAGE_SIZE length buffer अगर gpmi_alloc_dma_buffer
	 *     is called beक्रमe the न_अंकD identअगरication; and we allocate a
	 *     buffer of the real न_अंकD page size when the gpmi_alloc_dma_buffer
	 *     is called after.
	 */
	this->data_buffer_dma = kzalloc(mtd->ग_लिखोsize ?: PAGE_SIZE,
					GFP_DMA | GFP_KERNEL);
	अगर (this->data_buffer_dma == शून्य)
		जाओ error_alloc;

	this->auxiliary_virt = dma_alloc_coherent(dev, geo->auxiliary_size,
					&this->auxiliary_phys, GFP_DMA);
	अगर (!this->auxiliary_virt)
		जाओ error_alloc;

	this->raw_buffer = kzalloc((mtd->ग_लिखोsize ?: PAGE_SIZE) + mtd->oobsize, GFP_KERNEL);
	अगर (!this->raw_buffer)
		जाओ error_alloc;

	वापस 0;

error_alloc:
	gpmi_मुक्त_dma_buffer(this);
	वापस -ENOMEM;
पूर्ण

/*
 * Handles block mark swapping.
 * It can be called in swapping the block mark, or swapping it back,
 * because the the operations are the same.
 */
अटल व्योम block_mark_swapping(काष्ठा gpmi_nand_data *this,
				व्योम *payload, व्योम *auxiliary)
अणु
	काष्ठा bch_geometry *nfc_geo = &this->bch_geometry;
	अचिन्हित अक्षर *p;
	अचिन्हित अक्षर *a;
	अचिन्हित पूर्णांक  bit;
	अचिन्हित अक्षर mask;
	अचिन्हित अक्षर from_data;
	अचिन्हित अक्षर from_oob;

	अगर (!this->swap_block_mark)
		वापस;

	/*
	 * If control arrives here, we're swapping. Make some convenience
	 * variables.
	 */
	bit = nfc_geo->block_mark_bit_offset;
	p   = payload + nfc_geo->block_mark_byte_offset;
	a   = auxiliary;

	/*
	 * Get the byte from the data area that overlays the block mark. Since
	 * the ECC engine applies its own view to the bits in the page, the
	 * physical block mark won't (in general) appear on a byte boundary in
	 * the data.
	 */
	from_data = (p[0] >> bit) | (p[1] << (8 - bit));

	/* Get the byte from the OOB. */
	from_oob = a[0];

	/* Swap them. */
	a[0] = from_data;

	mask = (0x1 << bit) - 1;
	p[0] = (p[0] & mask) | (from_oob << bit);

	mask = ~0 << bit;
	p[1] = (p[1] & mask) | (from_oob >> (8 - bit));
पूर्ण

अटल पूर्णांक gpmi_count_bitflips(काष्ठा nand_chip *chip, व्योम *buf, पूर्णांक first,
			       पूर्णांक last, पूर्णांक meta)
अणु
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा bch_geometry *nfc_geo = &this->bch_geometry;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक i;
	अचिन्हित अक्षर *status;
	अचिन्हित पूर्णांक max_bitflips = 0;

	/* Loop over status bytes, accumulating ECC status. */
	status = this->auxiliary_virt + ALIGN(meta, 4);

	क्रम (i = first; i < last; i++, status++) अणु
		अगर ((*status == STATUS_GOOD) || (*status == STATUS_ERASED))
			जारी;

		अगर (*status == STATUS_UNCORRECTABLE) अणु
			पूर्णांक eccbits = nfc_geo->ecc_strength * nfc_geo->gf_len;
			u8 *eccbuf = this->raw_buffer;
			पूर्णांक offset, bitoffset;
			पूर्णांक eccbytes;
			पूर्णांक flips;

			/* Read ECC bytes पूर्णांकo our पूर्णांकernal raw_buffer */
			offset = nfc_geo->metadata_size * 8;
			offset += ((8 * nfc_geo->ecc_chunk_size) + eccbits) * (i + 1);
			offset -= eccbits;
			bitoffset = offset % 8;
			eccbytes = DIV_ROUND_UP(offset + eccbits, 8);
			offset /= 8;
			eccbytes -= offset;
			nand_change_पढ़ो_column_op(chip, offset, eccbuf,
						   eccbytes, false);

			/*
			 * ECC data are not byte aligned and we may have
			 * in-band data in the first and last byte of
			 * eccbuf. Set non-eccbits to one so that
			 * nand_check_erased_ecc_chunk() करोes not count them
			 * as bitflips.
			 */
			अगर (bitoffset)
				eccbuf[0] |= GENMASK(bitoffset - 1, 0);

			bitoffset = (bitoffset + eccbits) % 8;
			अगर (bitoffset)
				eccbuf[eccbytes - 1] |= GENMASK(7, bitoffset);

			/*
			 * The ECC hardware has an uncorrectable ECC status
			 * code in हाल we have bitflips in an erased page. As
			 * nothing was written पूर्णांकo this subpage the ECC is
			 * obviously wrong and we can not trust it. We assume
			 * at this poपूर्णांक that we are पढ़ोing an erased page and
			 * try to correct the bitflips in buffer up to
			 * ecc_strength bitflips. If this is a page with अक्रमom
			 * data, we exceed this number of bitflips and have a
			 * ECC failure. Otherwise we use the corrected buffer.
			 */
			अगर (i == 0) अणु
				/* The first block includes metadata */
				flips = nand_check_erased_ecc_chunk(
						buf + i * nfc_geo->ecc_chunk_size,
						nfc_geo->ecc_chunk_size,
						eccbuf, eccbytes,
						this->auxiliary_virt,
						nfc_geo->metadata_size,
						nfc_geo->ecc_strength);
			पूर्ण अन्यथा अणु
				flips = nand_check_erased_ecc_chunk(
						buf + i * nfc_geo->ecc_chunk_size,
						nfc_geo->ecc_chunk_size,
						eccbuf, eccbytes,
						शून्य, 0,
						nfc_geo->ecc_strength);
			पूर्ण

			अगर (flips > 0) अणु
				max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips,
						     flips);
				mtd->ecc_stats.corrected += flips;
				जारी;
			पूर्ण

			mtd->ecc_stats.failed++;
			जारी;
		पूर्ण

		mtd->ecc_stats.corrected += *status;
		max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, *status);
	पूर्ण

	वापस max_bitflips;
पूर्ण

अटल व्योम gpmi_bch_layout_std(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा bch_geometry *geo = &this->bch_geometry;
	अचिन्हित पूर्णांक ecc_strength = geo->ecc_strength >> 1;
	अचिन्हित पूर्णांक gf_len = geo->gf_len;
	अचिन्हित पूर्णांक block_size = geo->ecc_chunk_size;

	this->bch_flashlayout0 =
		BF_BCH_FLASH0LAYOUT0_NBLOCKS(geo->ecc_chunk_count - 1) |
		BF_BCH_FLASH0LAYOUT0_META_SIZE(geo->metadata_size) |
		BF_BCH_FLASH0LAYOUT0_ECC0(ecc_strength, this) |
		BF_BCH_FLASH0LAYOUT0_GF(gf_len, this) |
		BF_BCH_FLASH0LAYOUT0_DATA0_SIZE(block_size, this);

	this->bch_flashlayout1 =
		BF_BCH_FLASH0LAYOUT1_PAGE_SIZE(geo->page_size) |
		BF_BCH_FLASH0LAYOUT1_ECCN(ecc_strength, this) |
		BF_BCH_FLASH0LAYOUT1_GF(gf_len, this) |
		BF_BCH_FLASH0LAYOUT1_DATAN_SIZE(block_size, this);
पूर्ण

अटल पूर्णांक gpmi_ecc_पढ़ो_page(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			      पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा bch_geometry *geo = &this->bch_geometry;
	अचिन्हित पूर्णांक max_bitflips;
	पूर्णांक ret;

	gpmi_bch_layout_std(this);
	this->bch = true;

	ret = nand_पढ़ो_page_op(chip, page, 0, buf, geo->page_size);
	अगर (ret)
		वापस ret;

	max_bitflips = gpmi_count_bitflips(chip, buf, 0,
					   geo->ecc_chunk_count,
					   geo->auxiliary_status_offset);

	/* handle the block mark swapping */
	block_mark_swapping(this, buf, this->auxiliary_virt);

	अगर (oob_required) अणु
		/*
		 * It's समय to deliver the OOB bytes. See gpmi_ecc_पढ़ो_oob()
		 * क्रम details about our policy क्रम delivering the OOB.
		 *
		 * We fill the caller's buffer with set bits, and then copy the
		 * block mark to th caller's buffer. Note that, अगर block mark
		 * swapping was necessary, it has alपढ़ोy been करोne, so we can
		 * rely on the first byte of the auxiliary buffer to contain
		 * the block mark.
		 */
		स_रखो(chip->oob_poi, ~0, mtd->oobsize);
		chip->oob_poi[0] = ((uपूर्णांक8_t *)this->auxiliary_virt)[0];
	पूर्ण

	वापस max_bitflips;
पूर्ण

/* Fake a भव small page क्रम the subpage पढ़ो */
अटल पूर्णांक gpmi_ecc_पढ़ो_subpage(काष्ठा nand_chip *chip, uपूर्णांक32_t offs,
				 uपूर्णांक32_t len, uपूर्णांक8_t *buf, पूर्णांक page)
अणु
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा bch_geometry *geo = &this->bch_geometry;
	पूर्णांक size = chip->ecc.size; /* ECC chunk size */
	पूर्णांक meta, n, page_size;
	अचिन्हित पूर्णांक max_bitflips;
	अचिन्हित पूर्णांक ecc_strength;
	पूर्णांक first, last, marker_pos;
	पूर्णांक ecc_parity_size;
	पूर्णांक col = 0;
	पूर्णांक ret;

	/* The size of ECC parity */
	ecc_parity_size = geo->gf_len * geo->ecc_strength / 8;

	/* Align it with the chunk size */
	first = offs / size;
	last = (offs + len - 1) / size;

	अगर (this->swap_block_mark) अणु
		/*
		 * Find the chunk which contains the Block Marker.
		 * If this chunk is in the range of [first, last],
		 * we have to पढ़ो out the whole page.
		 * Why? since we had swapped the data at the position of Block
		 * Marker to the metadata which is bound with the chunk 0.
		 */
		marker_pos = geo->block_mark_byte_offset / size;
		अगर (last >= marker_pos && first <= marker_pos) अणु
			dev_dbg(this->dev,
				"page:%d, first:%d, last:%d, marker at:%d\n",
				page, first, last, marker_pos);
			वापस gpmi_ecc_पढ़ो_page(chip, buf, 0, page);
		पूर्ण
	पूर्ण

	meta = geo->metadata_size;
	अगर (first) अणु
		col = meta + (size + ecc_parity_size) * first;
		meta = 0;
		buf = buf + first * size;
	पूर्ण

	ecc_parity_size = geo->gf_len * geo->ecc_strength / 8;

	n = last - first + 1;
	page_size = meta + (size + ecc_parity_size) * n;
	ecc_strength = geo->ecc_strength >> 1;

	this->bch_flashlayout0 = BF_BCH_FLASH0LAYOUT0_NBLOCKS(n - 1) |
		BF_BCH_FLASH0LAYOUT0_META_SIZE(meta) |
		BF_BCH_FLASH0LAYOUT0_ECC0(ecc_strength, this) |
		BF_BCH_FLASH0LAYOUT0_GF(geo->gf_len, this) |
		BF_BCH_FLASH0LAYOUT0_DATA0_SIZE(geo->ecc_chunk_size, this);

	this->bch_flashlayout1 = BF_BCH_FLASH0LAYOUT1_PAGE_SIZE(page_size) |
		BF_BCH_FLASH0LAYOUT1_ECCN(ecc_strength, this) |
		BF_BCH_FLASH0LAYOUT1_GF(geo->gf_len, this) |
		BF_BCH_FLASH0LAYOUT1_DATAN_SIZE(geo->ecc_chunk_size, this);

	this->bch = true;

	ret = nand_पढ़ो_page_op(chip, page, col, buf, page_size);
	अगर (ret)
		वापस ret;

	dev_dbg(this->dev, "page:%d(%d:%d)%d, chunk:(%d:%d), BCH PG size:%d\n",
		page, offs, len, col, first, n, page_size);

	max_bitflips = gpmi_count_bitflips(chip, buf, first, last, meta);

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक gpmi_ecc_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			       पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा bch_geometry *nfc_geo = &this->bch_geometry;
	पूर्णांक ret;

	dev_dbg(this->dev, "ecc write page.\n");

	gpmi_bch_layout_std(this);
	this->bch = true;

	स_नकल(this->auxiliary_virt, chip->oob_poi, nfc_geo->auxiliary_size);

	अगर (this->swap_block_mark) अणु
		/*
		 * When करोing bad block marker swapping we must always copy the
		 * input buffer as we can't modअगरy the स्थिर buffer.
		 */
		स_नकल(this->data_buffer_dma, buf, mtd->ग_लिखोsize);
		buf = this->data_buffer_dma;
		block_mark_swapping(this, this->data_buffer_dma,
				    this->auxiliary_virt);
	पूर्ण

	ret = nand_prog_page_op(chip, page, 0, buf, nfc_geo->page_size);

	वापस ret;
पूर्ण

/*
 * There are several places in this driver where we have to handle the OOB and
 * block marks. This is the function where things are the most complicated, so
 * this is where we try to explain it all. All the other places refer back to
 * here.
 *
 * These are the rules, in order of decreasing importance:
 *
 * 1) Nothing the caller करोes can be allowed to imperil the block mark.
 *
 * 2) In पढ़ो operations, the first byte of the OOB we वापस must reflect the
 *    true state of the block mark, no matter where that block mark appears in
 *    the physical page.
 *
 * 3) ECC-based पढ़ो operations वापस an OOB full of set bits (since we never
 *    allow ECC-based ग_लिखोs to the OOB, it करोesn't matter what ECC-based पढ़ोs
 *    वापस).
 *
 * 4) "Raw" पढ़ो operations वापस a direct view of the physical bytes in the
 *    page, using the conventional definition of which bytes are data and which
 *    are OOB. This gives the caller a way to see the actual, physical bytes
 *    in the page, without the distortions applied by our ECC engine.
 *
 *
 * What we करो क्रम this specअगरic पढ़ो operation depends on two questions:
 *
 * 1) Are we करोing a "raw" पढ़ो, or an ECC-based पढ़ो?
 *
 * 2) Are we using block mark swapping or transcription?
 *
 * There are four हालs, illustrated by the following Karnaugh map:
 *
 *                    |           Raw           |         ECC-based       |
 *       -------------+-------------------------+-------------------------+
 *                    | Read the conventional   |                         |
 *                    | OOB at the end of the   |                         |
 *       Swapping     | page and वापस it. It  |                         |
 *                    | contains exactly what   |                         |
 *                    | we want.                | Read the block mark and |
 *       -------------+-------------------------+ वापस it in a buffer   |
 *                    | Read the conventional   | full of set bits.       |
 *                    | OOB at the end of the   |                         |
 *                    | page and also the block |                         |
 *       Transcribing | mark in the metadata.   |                         |
 *                    | Copy the block mark     |                         |
 *                    | पूर्णांकo the first byte of  |                         |
 *                    | the OOB.                |                         |
 *       -------------+-------------------------+-------------------------+
 *
 * Note that we अवरोध rule #4 in the Transcribing/Raw हाल because we're not
 * giving an accurate view of the actual, physical bytes in the page (we're
 * overwriting the block mark). That's OK because it's more important to follow
 * rule #2.
 *
 * It turns out that knowing whether we want an "ECC-based" or "raw" पढ़ो is not
 * easy. When पढ़ोing a page, क्रम example, the न_अंकD Flash MTD code calls our
 * ecc.पढ़ो_page or ecc.पढ़ो_page_raw function. Thus, the fact that MTD wants an
 * ECC-based or raw view of the page is implicit in which function it calls
 * (there is a similar pair of ECC-based/raw functions क्रम writing).
 */
अटल पूर्णांक gpmi_ecc_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	पूर्णांक ret;

	/* clear the OOB buffer */
	स_रखो(chip->oob_poi, ~0, mtd->oobsize);

	/* Read out the conventional OOB. */
	ret = nand_पढ़ो_page_op(chip, page, mtd->ग_लिखोsize, chip->oob_poi,
				mtd->oobsize);
	अगर (ret)
		वापस ret;

	/*
	 * Now, we want to make sure the block mark is correct. In the
	 * non-transcribing हाल (!GPMI_IS_MX23()), we alपढ़ोy have it.
	 * Otherwise, we need to explicitly पढ़ो it.
	 */
	अगर (GPMI_IS_MX23(this)) अणु
		/* Read the block mark पूर्णांकo the first byte of the OOB buffer. */
		ret = nand_पढ़ो_page_op(chip, page, 0, chip->oob_poi, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpmi_ecc_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mtd_oob_region of = अणु पूर्ण;

	/* Do we have available oob area? */
	mtd_ooblayout_मुक्त(mtd, 0, &of);
	अगर (!of.length)
		वापस -EPERM;

	अगर (!nand_is_slc(chip))
		वापस -EPERM;

	वापस nand_prog_page_op(chip, page, mtd->ग_लिखोsize + of.offset,
				 chip->oob_poi + of.offset, of.length);
पूर्ण

/*
 * This function पढ़ोs a न_अंकD page without involving the ECC engine (no HW
 * ECC correction).
 * The tricky part in the GPMI/BCH controller is that it stores ECC bits
 * अंतरभूत (पूर्णांकerleaved with payload DATA), and करो not align data chunk on
 * byte boundaries.
 * We thus need to take care moving the payload data and ECC bits stored in the
 * page पूर्णांकo the provided buffers, which is why we're using nand_extract_bits().
 *
 * See set_geometry_by_ecc_info अंतरभूत comments to have a full description
 * of the layout used by the GPMI controller.
 */
अटल पूर्णांक gpmi_ecc_पढ़ो_page_raw(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा bch_geometry *nfc_geo = &this->bch_geometry;
	पूर्णांक eccsize = nfc_geo->ecc_chunk_size;
	पूर्णांक eccbits = nfc_geo->ecc_strength * nfc_geo->gf_len;
	u8 *पंचांगp_buf = this->raw_buffer;
	माप_प्रकार src_bit_off;
	माप_प्रकार oob_bit_off;
	माप_प्रकार oob_byte_off;
	uपूर्णांक8_t *oob = chip->oob_poi;
	पूर्णांक step;
	पूर्णांक ret;

	ret = nand_पढ़ो_page_op(chip, page, 0, पंचांगp_buf,
				mtd->ग_लिखोsize + mtd->oobsize);
	अगर (ret)
		वापस ret;

	/*
	 * If required, swap the bad block marker and the data stored in the
	 * metadata section, so that we करोn't wrongly consider a block as bad.
	 *
	 * See the layout description क्रम a detailed explanation on why this
	 * is needed.
	 */
	अगर (this->swap_block_mark)
		swap(पंचांगp_buf[0], पंचांगp_buf[mtd->ग_लिखोsize]);

	/*
	 * Copy the metadata section पूर्णांकo the oob buffer (this section is
	 * guaranteed to be aligned on a byte boundary).
	 */
	अगर (oob_required)
		स_नकल(oob, पंचांगp_buf, nfc_geo->metadata_size);

	oob_bit_off = nfc_geo->metadata_size * 8;
	src_bit_off = oob_bit_off;

	/* Extract पूर्णांकerleaved payload data and ECC bits */
	क्रम (step = 0; step < nfc_geo->ecc_chunk_count; step++) अणु
		अगर (buf)
			nand_extract_bits(buf, step * eccsize * 8, पंचांगp_buf,
					  src_bit_off, eccsize * 8);
		src_bit_off += eccsize * 8;

		/* Align last ECC block to align a byte boundary */
		अगर (step == nfc_geo->ecc_chunk_count - 1 &&
		    (oob_bit_off + eccbits) % 8)
			eccbits += 8 - ((oob_bit_off + eccbits) % 8);

		अगर (oob_required)
			nand_extract_bits(oob, oob_bit_off, पंचांगp_buf,
					  src_bit_off, eccbits);

		src_bit_off += eccbits;
		oob_bit_off += eccbits;
	पूर्ण

	अगर (oob_required) अणु
		oob_byte_off = oob_bit_off / 8;

		अगर (oob_byte_off < mtd->oobsize)
			स_नकल(oob + oob_byte_off,
			       पंचांगp_buf + mtd->ग_लिखोsize + oob_byte_off,
			       mtd->oobsize - oob_byte_off);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function ग_लिखोs a न_अंकD page without involving the ECC engine (no HW
 * ECC generation).
 * The tricky part in the GPMI/BCH controller is that it stores ECC bits
 * अंतरभूत (पूर्णांकerleaved with payload DATA), and करो not align data chunk on
 * byte boundaries.
 * We thus need to take care moving the OOB area at the right place in the
 * final page, which is why we're using nand_extract_bits().
 *
 * See set_geometry_by_ecc_info अंतरभूत comments to have a full description
 * of the layout used by the GPMI controller.
 */
अटल पूर्णांक gpmi_ecc_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				   पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा bch_geometry *nfc_geo = &this->bch_geometry;
	पूर्णांक eccsize = nfc_geo->ecc_chunk_size;
	पूर्णांक eccbits = nfc_geo->ecc_strength * nfc_geo->gf_len;
	u8 *पंचांगp_buf = this->raw_buffer;
	uपूर्णांक8_t *oob = chip->oob_poi;
	माप_प्रकार dst_bit_off;
	माप_प्रकार oob_bit_off;
	माप_प्रकार oob_byte_off;
	पूर्णांक step;

	/*
	 * Initialize all bits to 1 in हाल we करोn't have a buffer क्रम the
	 * payload or oob data in order to leave unspecअगरied bits of data
	 * to their initial state.
	 */
	अगर (!buf || !oob_required)
		स_रखो(पंचांगp_buf, 0xff, mtd->ग_लिखोsize + mtd->oobsize);

	/*
	 * First copy the metadata section (stored in oob buffer) at the
	 * beginning of the page, as imposed by the GPMI layout.
	 */
	स_नकल(पंचांगp_buf, oob, nfc_geo->metadata_size);
	oob_bit_off = nfc_geo->metadata_size * 8;
	dst_bit_off = oob_bit_off;

	/* Interleave payload data and ECC bits */
	क्रम (step = 0; step < nfc_geo->ecc_chunk_count; step++) अणु
		अगर (buf)
			nand_extract_bits(पंचांगp_buf, dst_bit_off, buf,
					  step * eccsize * 8, eccsize * 8);
		dst_bit_off += eccsize * 8;

		/* Align last ECC block to align a byte boundary */
		अगर (step == nfc_geo->ecc_chunk_count - 1 &&
		    (oob_bit_off + eccbits) % 8)
			eccbits += 8 - ((oob_bit_off + eccbits) % 8);

		अगर (oob_required)
			nand_extract_bits(पंचांगp_buf, dst_bit_off, oob,
					  oob_bit_off, eccbits);

		dst_bit_off += eccbits;
		oob_bit_off += eccbits;
	पूर्ण

	oob_byte_off = oob_bit_off / 8;

	अगर (oob_required && oob_byte_off < mtd->oobsize)
		स_नकल(पंचांगp_buf + mtd->ग_लिखोsize + oob_byte_off,
		       oob + oob_byte_off, mtd->oobsize - oob_byte_off);

	/*
	 * If required, swap the bad block marker and the first byte of the
	 * metadata section, so that we करोn't modअगरy the bad block marker.
	 *
	 * See the layout description क्रम a detailed explanation on why this
	 * is needed.
	 */
	अगर (this->swap_block_mark)
		swap(पंचांगp_buf[0], पंचांगp_buf[mtd->ग_लिखोsize]);

	वापस nand_prog_page_op(chip, page, 0, पंचांगp_buf,
				 mtd->ग_लिखोsize + mtd->oobsize);
पूर्ण

अटल पूर्णांक gpmi_ecc_पढ़ो_oob_raw(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस gpmi_ecc_पढ़ो_page_raw(chip, शून्य, 1, page);
पूर्ण

अटल पूर्णांक gpmi_ecc_ग_लिखो_oob_raw(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस gpmi_ecc_ग_लिखो_page_raw(chip, शून्य, 1, page);
पूर्ण

अटल पूर्णांक gpmi_block_markbad(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	पूर्णांक ret = 0;
	uपूर्णांक8_t *block_mark;
	पूर्णांक column, page, chipnr;

	chipnr = (पूर्णांक)(ofs >> chip->chip_shअगरt);
	nand_select_target(chip, chipnr);

	column = !GPMI_IS_MX23(this) ? mtd->ग_लिखोsize : 0;

	/* Write the block mark. */
	block_mark = this->data_buffer_dma;
	block_mark[0] = 0; /* bad block marker */

	/* Shअगरt to get page */
	page = (पूर्णांक)(ofs >> chip->page_shअगरt);

	ret = nand_prog_page_op(chip, page, column, block_mark, 1);

	nand_deselect_target(chip);

	वापस ret;
पूर्ण

अटल पूर्णांक nand_boot_set_geometry(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा boot_rom_geometry *geometry = &this->rom_geometry;

	/*
	 * Set the boot block stride size.
	 *
	 * In principle, we should be पढ़ोing this from the OTP bits, since
	 * that's where the ROM is going to get it. In fact, we don't have any
	 * way to पढ़ो the OTP bits, so we go with the शेष and hope क्रम the
	 * best.
	 */
	geometry->stride_size_in_pages = 64;

	/*
	 * Set the search area stride exponent.
	 *
	 * In principle, we should be पढ़ोing this from the OTP bits, since
	 * that's where the ROM is going to get it. In fact, we don't have any
	 * way to पढ़ो the OTP bits, so we go with the शेष and hope क्रम the
	 * best.
	 */
	geometry->search_area_stride_exponent = 2;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर  *fingerprपूर्णांक = "STMP";
अटल पूर्णांक mx23_check_transcription_stamp(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा boot_rom_geometry *rom_geo = &this->rom_geometry;
	काष्ठा device *dev = this->dev;
	काष्ठा nand_chip *chip = &this->nand;
	अचिन्हित पूर्णांक search_area_size_in_strides;
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक page;
	u8 *buffer = nand_get_data_buf(chip);
	पूर्णांक found_an_ncb_fingerprपूर्णांक = false;
	पूर्णांक ret;

	/* Compute the number of strides in a search area. */
	search_area_size_in_strides = 1 << rom_geo->search_area_stride_exponent;

	nand_select_target(chip, 0);

	/*
	 * Loop through the first search area, looking क्रम the NCB fingerprपूर्णांक.
	 */
	dev_dbg(dev, "Scanning for an NCB fingerprint...\n");

	क्रम (stride = 0; stride < search_area_size_in_strides; stride++) अणु
		/* Compute the page addresses. */
		page = stride * rom_geo->stride_size_in_pages;

		dev_dbg(dev, "Looking for a fingerprint in page 0x%x\n", page);

		/*
		 * Read the NCB fingerprपूर्णांक. The fingerprपूर्णांक is four bytes दीर्घ
		 * and starts in the 12th byte of the page.
		 */
		ret = nand_पढ़ो_page_op(chip, page, 12, buffer,
					म_माप(fingerprपूर्णांक));
		अगर (ret)
			जारी;

		/* Look क्रम the fingerprपूर्णांक. */
		अगर (!स_भेद(buffer, fingerprपूर्णांक, म_माप(fingerprपूर्णांक))) अणु
			found_an_ncb_fingerprपूर्णांक = true;
			अवरोध;
		पूर्ण

	पूर्ण

	nand_deselect_target(chip);

	अगर (found_an_ncb_fingerprपूर्णांक)
		dev_dbg(dev, "\tFound a fingerprint\n");
	अन्यथा
		dev_dbg(dev, "\tNo fingerprint found\n");
	वापस found_an_ncb_fingerprपूर्णांक;
पूर्ण

/* Writes a transcription stamp. */
अटल पूर्णांक mx23_ग_लिखो_transcription_stamp(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा device *dev = this->dev;
	काष्ठा boot_rom_geometry *rom_geo = &this->rom_geometry;
	काष्ठा nand_chip *chip = &this->nand;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित पूर्णांक block_size_in_pages;
	अचिन्हित पूर्णांक search_area_size_in_strides;
	अचिन्हित पूर्णांक search_area_size_in_pages;
	अचिन्हित पूर्णांक search_area_size_in_blocks;
	अचिन्हित पूर्णांक block;
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक page;
	u8 *buffer = nand_get_data_buf(chip);
	पूर्णांक status;

	/* Compute the search area geometry. */
	block_size_in_pages = mtd->erasesize / mtd->ग_लिखोsize;
	search_area_size_in_strides = 1 << rom_geo->search_area_stride_exponent;
	search_area_size_in_pages = search_area_size_in_strides *
					rom_geo->stride_size_in_pages;
	search_area_size_in_blocks =
		  (search_area_size_in_pages + (block_size_in_pages - 1)) /
				    block_size_in_pages;

	dev_dbg(dev, "Search Area Geometry :\n");
	dev_dbg(dev, "\tin Blocks : %u\n", search_area_size_in_blocks);
	dev_dbg(dev, "\tin Strides: %u\n", search_area_size_in_strides);
	dev_dbg(dev, "\tin Pages  : %u\n", search_area_size_in_pages);

	nand_select_target(chip, 0);

	/* Loop over blocks in the first search area, erasing them. */
	dev_dbg(dev, "Erasing the search area...\n");

	क्रम (block = 0; block < search_area_size_in_blocks; block++) अणु
		/* Erase this block. */
		dev_dbg(dev, "\tErasing block 0x%x\n", block);
		status = nand_erase_op(chip, block);
		अगर (status)
			dev_err(dev, "[%s] Erase failed.\n", __func__);
	पूर्ण

	/* Write the NCB fingerprपूर्णांक पूर्णांकo the page buffer. */
	स_रखो(buffer, ~0, mtd->ग_लिखोsize);
	स_नकल(buffer + 12, fingerprपूर्णांक, म_माप(fingerprपूर्णांक));

	/* Loop through the first search area, writing NCB fingerprपूर्णांकs. */
	dev_dbg(dev, "Writing NCB fingerprints...\n");
	क्रम (stride = 0; stride < search_area_size_in_strides; stride++) अणु
		/* Compute the page addresses. */
		page = stride * rom_geo->stride_size_in_pages;

		/* Write the first page of the current stride. */
		dev_dbg(dev, "Writing an NCB fingerprint in page 0x%x\n", page);

		status = chip->ecc.ग_लिखो_page_raw(chip, buffer, 0, page);
		अगर (status)
			dev_err(dev, "[%s] Write failed.\n", __func__);
	पूर्ण

	nand_deselect_target(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mx23_boot_init(काष्ठा gpmi_nand_data  *this)
अणु
	काष्ठा device *dev = this->dev;
	काष्ठा nand_chip *chip = &this->nand;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित पूर्णांक block_count;
	अचिन्हित पूर्णांक block;
	पूर्णांक     chipnr;
	पूर्णांक     page;
	loff_t  byte;
	uपूर्णांक8_t block_mark;
	पूर्णांक     ret = 0;

	/*
	 * If control arrives here, we can't use block mark swapping, which
	 * means we're क्रमced to use transcription. First, scan क्रम the
	 * transcription stamp. If we find it, then we करोn't have to करो
	 * anything -- the block marks are alपढ़ोy transcribed.
	 */
	अगर (mx23_check_transcription_stamp(this))
		वापस 0;

	/*
	 * If control arrives here, we couldn't find a transcription stamp, so
	 * so we presume the block marks are in the conventional location.
	 */
	dev_dbg(dev, "Transcribing bad block marks...\n");

	/* Compute the number of blocks in the entire medium. */
	block_count = nanddev_eraseblocks_per_target(&chip->base);

	/*
	 * Loop over all the blocks in the medium, transcribing block marks as
	 * we go.
	 */
	क्रम (block = 0; block < block_count; block++) अणु
		/*
		 * Compute the chip, page and byte addresses क्रम this block's
		 * conventional mark.
		 */
		chipnr = block >> (chip->chip_shअगरt - chip->phys_erase_shअगरt);
		page = block << (chip->phys_erase_shअगरt - chip->page_shअगरt);
		byte = block <<  chip->phys_erase_shअगरt;

		/* Send the command to पढ़ो the conventional block mark. */
		nand_select_target(chip, chipnr);
		ret = nand_पढ़ो_page_op(chip, page, mtd->ग_लिखोsize, &block_mark,
					1);
		nand_deselect_target(chip);

		अगर (ret)
			जारी;

		/*
		 * Check अगर the block is marked bad. If so, we need to mark it
		 * again, but this समय the result will be a mark in the
		 * location where we transcribe block marks.
		 */
		अगर (block_mark != 0xff) अणु
			dev_dbg(dev, "Transcribing mark in block %u\n", block);
			ret = chip->legacy.block_markbad(chip, byte);
			अगर (ret)
				dev_err(dev,
					"Failed to mark block bad with ret %d\n",
					ret);
		पूर्ण
	पूर्ण

	/* Write the stamp that indicates we've transcribed the block marks. */
	mx23_ग_लिखो_transcription_stamp(this);
	वापस 0;
पूर्ण

अटल पूर्णांक nand_boot_init(काष्ठा gpmi_nand_data  *this)
अणु
	nand_boot_set_geometry(this);

	/* This is ROM arch-specअगरic initilization beक्रमe the BBT scanning. */
	अगर (GPMI_IS_MX23(this))
		वापस mx23_boot_init(this);
	वापस 0;
पूर्ण

अटल पूर्णांक gpmi_set_geometry(काष्ठा gpmi_nand_data *this)
अणु
	पूर्णांक ret;

	/* Free the temporary DMA memory क्रम पढ़ोing ID. */
	gpmi_मुक्त_dma_buffer(this);

	/* Set up the NFC geometry which is used by BCH. */
	ret = bch_set_geometry(this);
	अगर (ret) अणु
		dev_err(this->dev, "Error setting BCH geometry : %d\n", ret);
		वापस ret;
	पूर्ण

	/* Alloc the new DMA buffers according to the pagesize and oobsize */
	वापस gpmi_alloc_dma_buffer(this);
पूर्ण

अटल पूर्णांक gpmi_init_last(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा nand_chip *chip = &this->nand;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	काष्ठा bch_geometry *bch_geo = &this->bch_geometry;
	पूर्णांक ret;

	/* Set up the medium geometry */
	ret = gpmi_set_geometry(this);
	अगर (ret)
		वापस ret;

	/* Init the nand_ecc_ctrlअणुपूर्ण */
	ecc->पढ़ो_page	= gpmi_ecc_पढ़ो_page;
	ecc->ग_लिखो_page	= gpmi_ecc_ग_लिखो_page;
	ecc->पढ़ो_oob	= gpmi_ecc_पढ़ो_oob;
	ecc->ग_लिखो_oob	= gpmi_ecc_ग_लिखो_oob;
	ecc->पढ़ो_page_raw = gpmi_ecc_पढ़ो_page_raw;
	ecc->ग_लिखो_page_raw = gpmi_ecc_ग_लिखो_page_raw;
	ecc->पढ़ो_oob_raw = gpmi_ecc_पढ़ो_oob_raw;
	ecc->ग_लिखो_oob_raw = gpmi_ecc_ग_लिखो_oob_raw;
	ecc->engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	ecc->size	= bch_geo->ecc_chunk_size;
	ecc->strength	= bch_geo->ecc_strength;
	mtd_set_ooblayout(mtd, &gpmi_ooblayout_ops);

	/*
	 * We only enable the subpage पढ़ो when:
	 *  (1) the chip is imx6, and
	 *  (2) the size of the ECC parity is byte aligned.
	 */
	अगर (GPMI_IS_MX6(this) &&
		((bch_geo->gf_len * bch_geo->ecc_strength) % 8) == 0) अणु
		ecc->पढ़ो_subpage = gpmi_ecc_पढ़ो_subpage;
		chip->options |= न_अंकD_SUBPAGE_READ;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpmi_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	पूर्णांक ret;

	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH) अणु
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;

		अगर (of_property_पढ़ो_bool(this->dev->of_node,
					  "fsl,no-blockmark-swap"))
			this->swap_block_mark = false;
	पूर्ण
	dev_dbg(this->dev, "Blockmark swapping %sabled\n",
		this->swap_block_mark ? "en" : "dis");

	ret = gpmi_init_last(this);
	अगर (ret)
		वापस ret;

	chip->options |= न_अंकD_SKIP_BBTSCAN;

	वापस 0;
पूर्ण

अटल काष्ठा gpmi_transfer *get_next_transfer(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा gpmi_transfer *transfer = &this->transfers[this->ntransfers];

	this->ntransfers++;

	अगर (this->ntransfers == GPMI_MAX_TRANSFERS)
		वापस शून्य;

	वापस transfer;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *gpmi_chain_command(
	काष्ठा gpmi_nand_data *this, u8 cmd, स्थिर u8 *addr, पूर्णांक naddr)
अणु
	काष्ठा dma_chan *channel = get_dma_chan(this);
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा gpmi_transfer *transfer;
	पूर्णांक chip = this->nand.cur_cs;
	u32 pio[3];

	/* [1] send out the PIO words */
	pio[0] = BF_GPMI_CTRL0_COMMAND_MODE(BV_GPMI_CTRL0_COMMAND_MODE__WRITE)
		| BM_GPMI_CTRL0_WORD_LENGTH
		| BF_GPMI_CTRL0_CS(chip, this)
		| BF_GPMI_CTRL0_LOCK_CS(LOCK_CS_ENABLE, this)
		| BF_GPMI_CTRL0_ADDRESS(BV_GPMI_CTRL0_ADDRESS__न_अंकD_CLE)
		| BM_GPMI_CTRL0_ADDRESS_INCREMENT
		| BF_GPMI_CTRL0_XFER_COUNT(naddr + 1);
	pio[1] = 0;
	pio[2] = 0;
	desc = mxs_dmaengine_prep_pio(channel, pio, ARRAY_SIZE(pio),
				      DMA_TRANS_NONE, 0);
	अगर (!desc)
		वापस शून्य;

	transfer = get_next_transfer(this);
	अगर (!transfer)
		वापस शून्य;

	transfer->cmdbuf[0] = cmd;
	अगर (naddr)
		स_नकल(&transfer->cmdbuf[1], addr, naddr);

	sg_init_one(&transfer->sgl, transfer->cmdbuf, naddr + 1);
	dma_map_sg(this->dev, &transfer->sgl, 1, DMA_TO_DEVICE);

	transfer->direction = DMA_TO_DEVICE;

	desc = dmaengine_prep_slave_sg(channel, &transfer->sgl, 1, DMA_MEM_TO_DEV,
				       MXS_DMA_CTRL_WAIT4END);
	वापस desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *gpmi_chain_रुको_पढ़ोy(
	काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा dma_chan *channel = get_dma_chan(this);
	u32 pio[2];

	pio[0] =  BF_GPMI_CTRL0_COMMAND_MODE(BV_GPMI_CTRL0_COMMAND_MODE__WAIT_FOR_READY)
		| BM_GPMI_CTRL0_WORD_LENGTH
		| BF_GPMI_CTRL0_CS(this->nand.cur_cs, this)
		| BF_GPMI_CTRL0_LOCK_CS(LOCK_CS_ENABLE, this)
		| BF_GPMI_CTRL0_ADDRESS(BV_GPMI_CTRL0_ADDRESS__न_अंकD_DATA)
		| BF_GPMI_CTRL0_XFER_COUNT(0);
	pio[1] = 0;

	वापस mxs_dmaengine_prep_pio(channel, pio, 2, DMA_TRANS_NONE,
				MXS_DMA_CTRL_WAIT4END | MXS_DMA_CTRL_WAIT4RDY);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *gpmi_chain_data_पढ़ो(
	काष्ठा gpmi_nand_data *this, व्योम *buf, पूर्णांक raw_len, bool *direct)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_chan *channel = get_dma_chan(this);
	काष्ठा gpmi_transfer *transfer;
	u32 pio[6] = अणुपूर्ण;

	transfer = get_next_transfer(this);
	अगर (!transfer)
		वापस शून्य;

	transfer->direction = DMA_FROM_DEVICE;

	*direct = prepare_data_dma(this, buf, raw_len, &transfer->sgl,
				   DMA_FROM_DEVICE);

	pio[0] =  BF_GPMI_CTRL0_COMMAND_MODE(BV_GPMI_CTRL0_COMMAND_MODE__READ)
		| BM_GPMI_CTRL0_WORD_LENGTH
		| BF_GPMI_CTRL0_CS(this->nand.cur_cs, this)
		| BF_GPMI_CTRL0_LOCK_CS(LOCK_CS_ENABLE, this)
		| BF_GPMI_CTRL0_ADDRESS(BV_GPMI_CTRL0_ADDRESS__न_अंकD_DATA)
		| BF_GPMI_CTRL0_XFER_COUNT(raw_len);

	अगर (this->bch) अणु
		pio[2] =  BM_GPMI_ECCCTRL_ENABLE_ECC
			| BF_GPMI_ECCCTRL_ECC_CMD(BV_GPMI_ECCCTRL_ECC_CMD__BCH_DECODE)
			| BF_GPMI_ECCCTRL_BUFFER_MASK(BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE
				| BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_AUXONLY);
		pio[3] = raw_len;
		pio[4] = transfer->sgl.dma_address;
		pio[5] = this->auxiliary_phys;
	पूर्ण

	desc = mxs_dmaengine_prep_pio(channel, pio, ARRAY_SIZE(pio),
				      DMA_TRANS_NONE, 0);
	अगर (!desc)
		वापस शून्य;

	अगर (!this->bch)
		desc = dmaengine_prep_slave_sg(channel, &transfer->sgl, 1,
					     DMA_DEV_TO_MEM,
					     MXS_DMA_CTRL_WAIT4END);

	वापस desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *gpmi_chain_data_ग_लिखो(
	काष्ठा gpmi_nand_data *this, स्थिर व्योम *buf, पूर्णांक raw_len)
अणु
	काष्ठा dma_chan *channel = get_dma_chan(this);
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा gpmi_transfer *transfer;
	u32 pio[6] = अणुपूर्ण;

	transfer = get_next_transfer(this);
	अगर (!transfer)
		वापस शून्य;

	transfer->direction = DMA_TO_DEVICE;

	prepare_data_dma(this, buf, raw_len, &transfer->sgl, DMA_TO_DEVICE);

	pio[0] = BF_GPMI_CTRL0_COMMAND_MODE(BV_GPMI_CTRL0_COMMAND_MODE__WRITE)
		| BM_GPMI_CTRL0_WORD_LENGTH
		| BF_GPMI_CTRL0_CS(this->nand.cur_cs, this)
		| BF_GPMI_CTRL0_LOCK_CS(LOCK_CS_ENABLE, this)
		| BF_GPMI_CTRL0_ADDRESS(BV_GPMI_CTRL0_ADDRESS__न_अंकD_DATA)
		| BF_GPMI_CTRL0_XFER_COUNT(raw_len);

	अगर (this->bch) अणु
		pio[2] = BM_GPMI_ECCCTRL_ENABLE_ECC
			| BF_GPMI_ECCCTRL_ECC_CMD(BV_GPMI_ECCCTRL_ECC_CMD__BCH_ENCODE)
			| BF_GPMI_ECCCTRL_BUFFER_MASK(BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE |
					BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_AUXONLY);
		pio[3] = raw_len;
		pio[4] = transfer->sgl.dma_address;
		pio[5] = this->auxiliary_phys;
	पूर्ण

	desc = mxs_dmaengine_prep_pio(channel, pio, ARRAY_SIZE(pio),
				      DMA_TRANS_NONE,
				      (this->bch ? MXS_DMA_CTRL_WAIT4END : 0));
	अगर (!desc)
		वापस शून्य;

	अगर (!this->bch)
		desc = dmaengine_prep_slave_sg(channel, &transfer->sgl, 1,
					       DMA_MEM_TO_DEV,
					       MXS_DMA_CTRL_WAIT4END);

	वापस desc;
पूर्ण

अटल पूर्णांक gpmi_nfc_exec_op(काष्ठा nand_chip *chip,
			     स्थिर काष्ठा nand_operation *op,
			     bool check_only)
अणु
	स्थिर काष्ठा nand_op_instr *instr;
	काष्ठा gpmi_nand_data *this = nand_get_controller_data(chip);
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	पूर्णांक i, ret, buf_len = 0, nbufs = 0;
	u8 cmd = 0;
	व्योम *buf_पढ़ो = शून्य;
	स्थिर व्योम *buf_ग_लिखो = शून्य;
	bool direct = false;
	काष्ठा completion *dma_completion, *bch_completion;
	अचिन्हित दीर्घ to;

	अगर (check_only)
		वापस 0;

	this->ntransfers = 0;
	क्रम (i = 0; i < GPMI_MAX_TRANSFERS; i++)
		this->transfers[i].direction = DMA_NONE;

	ret = pm_runसमय_get_sync(this->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(this->dev);
		वापस ret;
	पूर्ण

	/*
	 * This driver currently supports only one न_अंकD chip. Plus, dies share
	 * the same configuration. So once timings have been applied on the
	 * controller side, they will not change anymore. When the समय will
	 * come, the check on must_apply_timings will have to be dropped.
	 */
	अगर (this->hw.must_apply_timings) अणु
		this->hw.must_apply_timings = false;
		gpmi_nfc_apply_timings(this);
	पूर्ण

	dev_dbg(this->dev, "%s: %d instructions\n", __func__, op->ninstrs);

	क्रम (i = 0; i < op->ninstrs; i++) अणु
		instr = &op->instrs[i];

		nand_op_trace("  ", instr);

		चयन (instr->type) अणु
		हाल न_अंकD_OP_WAITRDY_INSTR:
			desc = gpmi_chain_रुको_पढ़ोy(this);
			अवरोध;
		हाल न_अंकD_OP_CMD_INSTR:
			cmd = instr->ctx.cmd.opcode;

			/*
			 * When this command has an address cycle chain it
			 * together with the address cycle
			 */
			अगर (i + 1 != op->ninstrs &&
			    op->instrs[i + 1].type == न_अंकD_OP_ADDR_INSTR)
				जारी;

			desc = gpmi_chain_command(this, cmd, शून्य, 0);

			अवरोध;
		हाल न_अंकD_OP_ADDR_INSTR:
			desc = gpmi_chain_command(this, cmd, instr->ctx.addr.addrs,
						  instr->ctx.addr.naddrs);
			अवरोध;
		हाल न_अंकD_OP_DATA_OUT_INSTR:
			buf_ग_लिखो = instr->ctx.data.buf.out;
			buf_len = instr->ctx.data.len;
			nbufs++;

			desc = gpmi_chain_data_ग_लिखो(this, buf_ग_लिखो, buf_len);

			अवरोध;
		हाल न_अंकD_OP_DATA_IN_INSTR:
			अगर (!instr->ctx.data.len)
				अवरोध;
			buf_पढ़ो = instr->ctx.data.buf.in;
			buf_len = instr->ctx.data.len;
			nbufs++;

			desc = gpmi_chain_data_पढ़ो(this, buf_पढ़ो, buf_len,
						   &direct);
			अवरोध;
		पूर्ण

		अगर (!desc) अणु
			ret = -ENXIO;
			जाओ unmap;
		पूर्ण
	पूर्ण

	dev_dbg(this->dev, "%s setup done\n", __func__);

	अगर (nbufs > 1) अणु
		dev_err(this->dev, "Multiple data instructions not supported\n");
		ret = -EINVAL;
		जाओ unmap;
	पूर्ण

	अगर (this->bch) अणु
		ग_लिखोl(this->bch_flashlayout0,
		       this->resources.bch_regs + HW_BCH_FLASH0LAYOUT0);
		ग_लिखोl(this->bch_flashlayout1,
		       this->resources.bch_regs + HW_BCH_FLASH0LAYOUT1);
	पूर्ण

	desc->callback = dma_irq_callback;
	desc->callback_param = this;
	dma_completion = &this->dma_करोne;
	bch_completion = शून्य;

	init_completion(dma_completion);

	अगर (this->bch && buf_पढ़ो) अणु
		ग_लिखोl(BM_BCH_CTRL_COMPLETE_IRQ_EN,
		       this->resources.bch_regs + HW_BCH_CTRL_SET);
		bch_completion = &this->bch_करोne;
		init_completion(bch_completion);
	पूर्ण

	dmaengine_submit(desc);
	dma_async_issue_pending(get_dma_chan(this));

	to = रुको_क्रम_completion_समयout(dma_completion, msecs_to_jअगरfies(1000));
	अगर (!to) अणु
		dev_err(this->dev, "DMA timeout, last DMA\n");
		gpmi_dump_info(this);
		ret = -ETIMEDOUT;
		जाओ unmap;
	पूर्ण

	अगर (this->bch && buf_पढ़ो) अणु
		to = रुको_क्रम_completion_समयout(bch_completion, msecs_to_jअगरfies(1000));
		अगर (!to) अणु
			dev_err(this->dev, "BCH timeout, last DMA\n");
			gpmi_dump_info(this);
			ret = -ETIMEDOUT;
			जाओ unmap;
		पूर्ण
	पूर्ण

	ग_लिखोl(BM_BCH_CTRL_COMPLETE_IRQ_EN,
	       this->resources.bch_regs + HW_BCH_CTRL_CLR);
	gpmi_clear_bch(this);

	ret = 0;

unmap:
	क्रम (i = 0; i < this->ntransfers; i++) अणु
		काष्ठा gpmi_transfer *transfer = &this->transfers[i];

		अगर (transfer->direction != DMA_NONE)
			dma_unmap_sg(this->dev, &transfer->sgl, 1,
				     transfer->direction);
	पूर्ण

	अगर (!ret && buf_पढ़ो && !direct)
		स_नकल(buf_पढ़ो, this->data_buffer_dma,
		       gpmi_raw_len_to_len(this, buf_len));

	this->bch = false;

	pm_runसमय_mark_last_busy(this->dev);
	pm_runसमय_put_स्वतःsuspend(this->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops gpmi_nand_controller_ops = अणु
	.attach_chip = gpmi_nand_attach_chip,
	.setup_पूर्णांकerface = gpmi_setup_पूर्णांकerface,
	.exec_op = gpmi_nfc_exec_op,
पूर्ण;

अटल पूर्णांक gpmi_nand_init(काष्ठा gpmi_nand_data *this)
अणु
	काष्ठा nand_chip *chip = &this->nand;
	काष्ठा mtd_info  *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	/* init the MTD data काष्ठाures */
	mtd->name		= "gpmi-nand";
	mtd->dev.parent		= this->dev;

	/* init the nand_chipअणुपूर्ण, we करोn't support a 16-bit न_अंकD Flash bus. */
	nand_set_controller_data(chip, this);
	nand_set_flash_node(chip, this->pdev->dev.of_node);
	chip->legacy.block_markbad = gpmi_block_markbad;
	chip->badblock_pattern	= &gpmi_bbt_descr;
	chip->options		|= न_अंकD_NO_SUBPAGE_WRITE;

	/* Set up swap_block_mark, must be set beक्रमe the gpmi_set_geometry() */
	this->swap_block_mark = !GPMI_IS_MX23(this);

	/*
	 * Allocate a temporary DMA buffer क्रम पढ़ोing ID in the
	 * nand_scan_ident().
	 */
	this->bch_geometry.payload_size = 1024;
	this->bch_geometry.auxiliary_size = 128;
	ret = gpmi_alloc_dma_buffer(this);
	अगर (ret)
		वापस ret;

	nand_controller_init(&this->base);
	this->base.ops = &gpmi_nand_controller_ops;
	chip->controller = &this->base;

	ret = nand_scan(chip, GPMI_IS_MX6(this) ? 2 : 1);
	अगर (ret)
		जाओ err_out;

	ret = nand_boot_init(this);
	अगर (ret)
		जाओ err_nand_cleanup;
	ret = nand_create_bbt(chip);
	अगर (ret)
		जाओ err_nand_cleanup;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret)
		जाओ err_nand_cleanup;
	वापस 0;

err_nand_cleanup:
	nand_cleanup(chip);
err_out:
	gpmi_मुक्त_dma_buffer(this);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id gpmi_nand_id_table[] = अणु
	अणु .compatible = "fsl,imx23-gpmi-nand", .data = &gpmi_devdata_imx23, पूर्ण,
	अणु .compatible = "fsl,imx28-gpmi-nand", .data = &gpmi_devdata_imx28, पूर्ण,
	अणु .compatible = "fsl,imx6q-gpmi-nand", .data = &gpmi_devdata_imx6q, पूर्ण,
	अणु .compatible = "fsl,imx6sx-gpmi-nand", .data = &gpmi_devdata_imx6sx, पूर्ण,
	अणु .compatible = "fsl,imx7d-gpmi-nand", .data = &gpmi_devdata_imx7d,पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpmi_nand_id_table);

अटल पूर्णांक gpmi_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpmi_nand_data *this;
	पूर्णांक ret;

	this = devm_kzalloc(&pdev->dev, माप(*this), GFP_KERNEL);
	अगर (!this)
		वापस -ENOMEM;

	this->devdata = of_device_get_match_data(&pdev->dev);
	platक्रमm_set_drvdata(pdev, this);
	this->pdev  = pdev;
	this->dev   = &pdev->dev;

	ret = acquire_resources(this);
	अगर (ret)
		जाओ निकास_acquire_resources;

	ret = __gpmi_enable_clk(this, true);
	अगर (ret)
		जाओ निकास_acquire_resources;

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 500);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	ret = gpmi_init(this);
	अगर (ret)
		जाओ निकास_nfc_init;

	ret = gpmi_nand_init(this);
	अगर (ret)
		जाओ निकास_nfc_init;

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	dev_info(this->dev, "driver registered.\n");

	वापस 0;

निकास_nfc_init:
	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	release_resources(this);
निकास_acquire_resources:

	वापस ret;
पूर्ण

अटल पूर्णांक gpmi_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpmi_nand_data *this = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &this->nand;
	पूर्णांक ret;

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);
	gpmi_मुक्त_dma_buffer(this);
	release_resources(this);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक gpmi_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpmi_nand_data *this = dev_get_drvdata(dev);

	release_dma_channels(this);
	वापस 0;
पूर्ण

अटल पूर्णांक gpmi_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा gpmi_nand_data *this = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = acquire_dma_channels(this);
	अगर (ret < 0)
		वापस ret;

	/* re-init the GPMI रेजिस्टरs */
	ret = gpmi_init(this);
	अगर (ret) अणु
		dev_err(this->dev, "Error setting GPMI : %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set flag to get timing setup restored क्रम next exec_op */
	अगर (this->hw.clk_rate)
		this->hw.must_apply_timings = true;

	/* re-init the BCH रेजिस्टरs */
	ret = bch_set_geometry(this);
	अगर (ret) अणु
		dev_err(this->dev, "Error setting BCH : %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक __maybe_unused gpmi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpmi_nand_data *this = dev_get_drvdata(dev);

	वापस __gpmi_enable_clk(this, false);
पूर्ण

अटल पूर्णांक __maybe_unused gpmi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा gpmi_nand_data *this = dev_get_drvdata(dev);

	वापस __gpmi_enable_clk(this, true);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gpmi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(gpmi_pm_suspend, gpmi_pm_resume)
	SET_RUNTIME_PM_OPS(gpmi_runसमय_suspend, gpmi_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver gpmi_nand_driver = अणु
	.driver = अणु
		.name = "gpmi-nand",
		.pm = &gpmi_pm_ops,
		.of_match_table = gpmi_nand_id_table,
	पूर्ण,
	.probe   = gpmi_nand_probe,
	.हटाओ  = gpmi_nand_हटाओ,
पूर्ण;
module_platक्रमm_driver(gpmi_nand_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("i.MX GPMI NAND Flash Controller Driver");
MODULE_LICENSE("GPL");
