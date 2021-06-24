<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale Integrated Flash Controller न_अंकD driver
 *
 * Copyright 2011-2012 Freescale Semiconductor, Inc
 *
 * Author: Dipen Dudhat <Dipen.Dudhat@मुक्तscale.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/fsl_अगरc.h>
#समावेश <linux/iopoll.h>

#घोषणा ERR_BYTE		0xFF /* Value वापसed क्रम पढ़ो
					bytes when पढ़ो failed	*/
#घोषणा IFC_TIMEOUT_MSECS	500  /* Maximum number of mSecs to रुको
					क्रम IFC न_अंकD Machine	*/

काष्ठा fsl_अगरc_ctrl;

/* mtd inक्रमmation per set */
काष्ठा fsl_अगरc_mtd अणु
	काष्ठा nand_chip chip;
	काष्ठा fsl_अगरc_ctrl *ctrl;

	काष्ठा device *dev;
	पूर्णांक bank;		/* Chip select bank number		*/
	अचिन्हित पूर्णांक bufnum_mask; /* bufnum = page & bufnum_mask */
	u8 __iomem *vbase;      /* Chip select base भव address	*/
पूर्ण;

/* overview of the fsl अगरc controller */
काष्ठा fsl_अगरc_nand_ctrl अणु
	काष्ठा nand_controller controller;
	काष्ठा fsl_अगरc_mtd *chips[FSL_IFC_BANK_COUNT];

	व्योम __iomem *addr;	/* Address of asचिन्हित IFC buffer	*/
	अचिन्हित पूर्णांक page;	/* Last page written to / पढ़ो from	*/
	अचिन्हित पूर्णांक पढ़ो_bytes;/* Number of bytes पढ़ो during command	*/
	अचिन्हित पूर्णांक column;	/* Saved column from SEQIN		*/
	अचिन्हित पूर्णांक index;	/* Poपूर्णांकer to next byte to 'read'	*/
	अचिन्हित पूर्णांक oob;	/* Non zero अगर operating on OOB data	*/
	अचिन्हित पूर्णांक eccपढ़ो;	/* Non zero क्रम a full-page ECC पढ़ो	*/
	अचिन्हित पूर्णांक counter;	/* counter क्रम the initializations	*/
	अचिन्हित पूर्णांक max_bitflips;  /* Saved during READ0 cmd		*/
पूर्ण;

अटल काष्ठा fsl_अगरc_nand_ctrl *अगरc_nand_ctrl;

/*
 * Generic flash bbt descriptors
 */
अटल u8 bbt_pattern[] = अणु'B', 'b', 't', '0' पूर्ण;
अटल u8 mirror_pattern[] = अणु'1', 't', 'b', 'B' पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_मुख्य_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE |
		   न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION,
	.offs =	2, /* 0 on 8-bit small page */
	.len = 4,
	.veroffs = 6,
	.maxblocks = 4,
	.pattern = bbt_pattern,
पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_mirror_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE |
		   न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION,
	.offs =	2, /* 0 on 8-bit small page */
	.len = 4,
	.veroffs = 6,
	.maxblocks = 4,
	.pattern = mirror_pattern,
पूर्ण;

अटल पूर्णांक fsl_अगरc_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 8;
	oobregion->length = chip->ecc.total;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_अगरc_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section > 1)
		वापस -दुस्फल;

	अगर (mtd->ग_लिखोsize == 512 &&
	    !(chip->options & न_अंकD_BUSWIDTH_16)) अणु
		अगर (!section) अणु
			oobregion->offset = 0;
			oobregion->length = 5;
		पूर्ण अन्यथा अणु
			oobregion->offset = 6;
			oobregion->length = 2;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (!section) अणु
		oobregion->offset = 2;
		oobregion->length = 6;
	पूर्ण अन्यथा अणु
		oobregion->offset = chip->ecc.total + 8;
		oobregion->length = mtd->oobsize - oobregion->offset;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops fsl_अगरc_ooblayout_ops = अणु
	.ecc = fsl_अगरc_ooblayout_ecc,
	.मुक्त = fsl_अगरc_ooblayout_मुक्त,
पूर्ण;

/*
 * Set up the IFC hardware block and page address fields, and the अगरc nand
 * काष्ठाure addr field to poपूर्णांक to the correct IFC buffer in memory
 */
अटल व्योम set_addr(काष्ठा mtd_info *mtd, पूर्णांक column, पूर्णांक page_addr, पूर्णांक oob)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc = ctrl->rregs;
	पूर्णांक buf_num;

	अगरc_nand_ctrl->page = page_addr;
	/* Program ROW0/COL0 */
	अगरc_out32(page_addr, &अगरc->अगरc_nand.row0);
	अगरc_out32((oob ? IFC_न_अंकD_COL_MS : 0) | column, &अगरc->अगरc_nand.col0);

	buf_num = page_addr & priv->bufnum_mask;

	अगरc_nand_ctrl->addr = priv->vbase + buf_num * (mtd->ग_लिखोsize * 2);
	अगरc_nand_ctrl->index = column;

	/* क्रम OOB data poपूर्णांक to the second half of the buffer */
	अगर (oob)
		अगरc_nand_ctrl->index += mtd->ग_लिखोsize;
पूर्ण

/* वापसs nonzero अगर entire page is blank */
अटल पूर्णांक check_पढ़ो_ecc(काष्ठा mtd_info *mtd, काष्ठा fsl_अगरc_ctrl *ctrl,
			  u32 eccstat, अचिन्हित पूर्णांक bufnum)
अणु
	वापस  (eccstat >> ((3 - bufnum % 4) * 8)) & 15;
पूर्ण

/*
 * execute IFC न_अंकD command and रुको क्रम it to complete
 */
अटल व्योम fsl_अगरc_run_command(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_nand_ctrl *nctrl = अगरc_nand_ctrl;
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc = ctrl->rregs;
	u32 eccstat;
	पूर्णांक i;

	/* set the chip select क्रम न_अंकD Transaction */
	अगरc_out32(priv->bank << IFC_न_अंकD_CSEL_SHIFT,
		  &अगरc->अगरc_nand.nand_csel);

	dev_vdbg(priv->dev,
			"%s: fir0=%08x fcr0=%08x\n",
			__func__,
			अगरc_in32(&अगरc->अगरc_nand.nand_fir0),
			अगरc_in32(&अगरc->अगरc_nand.nand_fcr0));

	ctrl->nand_stat = 0;

	/* start पढ़ो/ग_लिखो seq */
	अगरc_out32(IFC_न_अंकD_SEQ_STRT_FIR_STRT, &अगरc->अगरc_nand.nandseq_strt);

	/* रुको क्रम command complete flag or समयout */
	रुको_event_समयout(ctrl->nand_रुको, ctrl->nand_stat,
			   msecs_to_jअगरfies(IFC_TIMEOUT_MSECS));

	/* ctrl->nand_stat will be updated from IRQ context */
	अगर (!ctrl->nand_stat)
		dev_err(priv->dev, "Controller is not responding\n");
	अगर (ctrl->nand_stat & IFC_न_अंकD_EVTER_STAT_FTOER)
		dev_err(priv->dev, "NAND Flash Timeout Error\n");
	अगर (ctrl->nand_stat & IFC_न_अंकD_EVTER_STAT_WPER)
		dev_err(priv->dev, "NAND Flash Write Protect Error\n");

	nctrl->max_bitflips = 0;

	अगर (nctrl->eccपढ़ो) अणु
		पूर्णांक errors;
		पूर्णांक bufnum = nctrl->page & priv->bufnum_mask;
		पूर्णांक sector_start = bufnum * chip->ecc.steps;
		पूर्णांक sector_end = sector_start + chip->ecc.steps - 1;
		__be32 __iomem *eccstat_regs;

		eccstat_regs = अगरc->अगरc_nand.nand_eccstat;
		eccstat = अगरc_in32(&eccstat_regs[sector_start / 4]);

		क्रम (i = sector_start; i <= sector_end; i++) अणु
			अगर (i != sector_start && !(i % 4))
				eccstat = अगरc_in32(&eccstat_regs[i / 4]);

			errors = check_पढ़ो_ecc(mtd, ctrl, eccstat, i);

			अगर (errors == 15) अणु
				/*
				 * Uncorrectable error.
				 * We'll check क्रम blank pages later.
				 *
				 * We disable ECCER reporting due to...
				 * erratum IFC-A002770 -- so report it now अगर we
				 * see an uncorrectable error in ECCSTAT.
				 */
				ctrl->nand_stat |= IFC_न_अंकD_EVTER_STAT_ECCER;
				जारी;
			पूर्ण

			mtd->ecc_stats.corrected += errors;
			nctrl->max_bitflips = max_t(अचिन्हित पूर्णांक,
						    nctrl->max_bitflips,
						    errors);
		पूर्ण

		nctrl->eccपढ़ो = 0;
	पूर्ण
पूर्ण

अटल व्योम fsl_अगरc_करो_पढ़ो(काष्ठा nand_chip *chip,
			    पूर्णांक oob,
			    काष्ठा mtd_info *mtd)
अणु
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc = ctrl->rregs;

	/* Program FIR/IFC_न_अंकD_FCR0 क्रम Small/Large page */
	अगर (mtd->ग_लिखोsize > 512) अणु
		अगरc_out32((IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_CA0 << IFC_न_अंकD_FIR0_OP1_SHIFT) |
			  (IFC_FIR_OP_RA0 << IFC_न_अंकD_FIR0_OP2_SHIFT) |
			  (IFC_FIR_OP_CMD1 << IFC_न_अंकD_FIR0_OP3_SHIFT) |
			  (IFC_FIR_OP_RBCD << IFC_न_अंकD_FIR0_OP4_SHIFT),
			  &अगरc->अगरc_nand.nand_fir0);
		अगरc_out32(0x0, &अगरc->अगरc_nand.nand_fir1);

		अगरc_out32((न_अंकD_CMD_READ0 << IFC_न_अंकD_FCR0_CMD0_SHIFT) |
			  (न_अंकD_CMD_READSTART << IFC_न_अंकD_FCR0_CMD1_SHIFT),
			  &अगरc->अगरc_nand.nand_fcr0);
	पूर्ण अन्यथा अणु
		अगरc_out32((IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_CA0 << IFC_न_अंकD_FIR0_OP1_SHIFT) |
			  (IFC_FIR_OP_RA0  << IFC_न_अंकD_FIR0_OP2_SHIFT) |
			  (IFC_FIR_OP_RBCD << IFC_न_अंकD_FIR0_OP3_SHIFT),
			  &अगरc->अगरc_nand.nand_fir0);
		अगरc_out32(0x0, &अगरc->अगरc_nand.nand_fir1);

		अगर (oob)
			अगरc_out32(न_अंकD_CMD_READOOB <<
				  IFC_न_अंकD_FCR0_CMD0_SHIFT,
				  &अगरc->अगरc_nand.nand_fcr0);
		अन्यथा
			अगरc_out32(न_अंकD_CMD_READ0 <<
				  IFC_न_अंकD_FCR0_CMD0_SHIFT,
				  &अगरc->अगरc_nand.nand_fcr0);
	पूर्ण
पूर्ण

/* cmdfunc send commands to the IFC न_अंकD Machine */
अटल व्योम fsl_अगरc_cmdfunc(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक command,
			    पूर्णांक column, पूर्णांक page_addr) अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc = ctrl->rregs;

	/* clear the पढ़ो buffer */
	अगरc_nand_ctrl->पढ़ो_bytes = 0;
	अगर (command != न_अंकD_CMD_PAGEPROG)
		अगरc_nand_ctrl->index = 0;

	चयन (command) अणु
	/* READ0 पढ़ो the entire buffer to use hardware ECC. */
	हाल न_अंकD_CMD_READ0:
		अगरc_out32(0, &अगरc->अगरc_nand.nand_fbcr);
		set_addr(mtd, 0, page_addr, 0);

		अगरc_nand_ctrl->पढ़ो_bytes = mtd->ग_लिखोsize + mtd->oobsize;
		अगरc_nand_ctrl->index += column;

		अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
			अगरc_nand_ctrl->eccपढ़ो = 1;

		fsl_अगरc_करो_पढ़ो(chip, 0, mtd);
		fsl_अगरc_run_command(mtd);
		वापस;

	/* READOOB पढ़ोs only the OOB because no ECC is perक्रमmed. */
	हाल न_अंकD_CMD_READOOB:
		अगरc_out32(mtd->oobsize - column, &अगरc->अगरc_nand.nand_fbcr);
		set_addr(mtd, column, page_addr, 1);

		अगरc_nand_ctrl->पढ़ो_bytes = mtd->ग_लिखोsize + mtd->oobsize;

		fsl_अगरc_करो_पढ़ो(chip, 1, mtd);
		fsl_अगरc_run_command(mtd);

		वापस;

	हाल न_अंकD_CMD_READID:
	हाल न_अंकD_CMD_PARAM: अणु
		/*
		 * For READID, पढ़ो 8 bytes that are currently used.
		 * For PARAM, पढ़ो all 3 copies of 256-bytes pages.
		 */
		पूर्णांक len = 8;
		पूर्णांक timing = IFC_FIR_OP_RB;
		अगर (command == न_अंकD_CMD_PARAM) अणु
			timing = IFC_FIR_OP_RBCD;
			len = 256 * 3;
		पूर्ण

		अगरc_out32((IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_UA  << IFC_न_अंकD_FIR0_OP1_SHIFT) |
			  (timing << IFC_न_अंकD_FIR0_OP2_SHIFT),
			  &अगरc->अगरc_nand.nand_fir0);
		अगरc_out32(command << IFC_न_अंकD_FCR0_CMD0_SHIFT,
			  &अगरc->अगरc_nand.nand_fcr0);
		अगरc_out32(column, &अगरc->अगरc_nand.row3);

		अगरc_out32(len, &अगरc->अगरc_nand.nand_fbcr);
		अगरc_nand_ctrl->पढ़ो_bytes = len;

		set_addr(mtd, 0, 0, 0);
		fsl_अगरc_run_command(mtd);
		वापस;
	पूर्ण

	/* ERASE1 stores the block and page address */
	हाल न_अंकD_CMD_ERASE1:
		set_addr(mtd, 0, page_addr, 0);
		वापस;

	/* ERASE2 uses the block and page address from ERASE1 */
	हाल न_अंकD_CMD_ERASE2:
		अगरc_out32((IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_RA0 << IFC_न_अंकD_FIR0_OP1_SHIFT) |
			  (IFC_FIR_OP_CMD1 << IFC_न_अंकD_FIR0_OP2_SHIFT),
			  &अगरc->अगरc_nand.nand_fir0);

		अगरc_out32((न_अंकD_CMD_ERASE1 << IFC_न_अंकD_FCR0_CMD0_SHIFT) |
			  (न_अंकD_CMD_ERASE2 << IFC_न_अंकD_FCR0_CMD1_SHIFT),
			  &अगरc->अगरc_nand.nand_fcr0);

		अगरc_out32(0, &अगरc->अगरc_nand.nand_fbcr);
		अगरc_nand_ctrl->पढ़ो_bytes = 0;
		fsl_अगरc_run_command(mtd);
		वापस;

	/* SEQIN sets up the addr buffer and all रेजिस्टरs except the length */
	हाल न_अंकD_CMD_SEQIN: अणु
		u32 nand_fcr0;
		अगरc_nand_ctrl->column = column;
		अगरc_nand_ctrl->oob = 0;

		अगर (mtd->ग_लिखोsize > 512) अणु
			nand_fcr0 =
				(न_अंकD_CMD_SEQIN << IFC_न_अंकD_FCR0_CMD0_SHIFT) |
				(न_अंकD_CMD_STATUS << IFC_न_अंकD_FCR0_CMD1_SHIFT) |
				(न_अंकD_CMD_PAGEPROG << IFC_न_अंकD_FCR0_CMD2_SHIFT);

			अगरc_out32(
				(IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
				(IFC_FIR_OP_CA0 << IFC_न_अंकD_FIR0_OP1_SHIFT) |
				(IFC_FIR_OP_RA0 << IFC_न_अंकD_FIR0_OP2_SHIFT) |
				(IFC_FIR_OP_WBCD << IFC_न_अंकD_FIR0_OP3_SHIFT) |
				(IFC_FIR_OP_CMD2 << IFC_न_अंकD_FIR0_OP4_SHIFT),
				&अगरc->अगरc_nand.nand_fir0);
			अगरc_out32(
				(IFC_FIR_OP_CW1 << IFC_न_अंकD_FIR1_OP5_SHIFT) |
				(IFC_FIR_OP_RDSTAT << IFC_न_अंकD_FIR1_OP6_SHIFT) |
				(IFC_FIR_OP_NOP << IFC_न_अंकD_FIR1_OP7_SHIFT),
				&अगरc->अगरc_nand.nand_fir1);
		पूर्ण अन्यथा अणु
			nand_fcr0 = ((न_अंकD_CMD_PAGEPROG <<
					IFC_न_अंकD_FCR0_CMD1_SHIFT) |
				    (न_अंकD_CMD_SEQIN <<
					IFC_न_अंकD_FCR0_CMD2_SHIFT) |
				    (न_अंकD_CMD_STATUS <<
					IFC_न_अंकD_FCR0_CMD3_SHIFT));

			अगरc_out32(
				(IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
				(IFC_FIR_OP_CMD2 << IFC_न_अंकD_FIR0_OP1_SHIFT) |
				(IFC_FIR_OP_CA0 << IFC_न_अंकD_FIR0_OP2_SHIFT) |
				(IFC_FIR_OP_RA0 << IFC_न_अंकD_FIR0_OP3_SHIFT) |
				(IFC_FIR_OP_WBCD << IFC_न_अंकD_FIR0_OP4_SHIFT),
				&अगरc->अगरc_nand.nand_fir0);
			अगरc_out32(
				(IFC_FIR_OP_CMD1 << IFC_न_अंकD_FIR1_OP5_SHIFT) |
				(IFC_FIR_OP_CW3 << IFC_न_अंकD_FIR1_OP6_SHIFT) |
				(IFC_FIR_OP_RDSTAT << IFC_न_अंकD_FIR1_OP7_SHIFT) |
				(IFC_FIR_OP_NOP << IFC_न_अंकD_FIR1_OP8_SHIFT),
				&अगरc->अगरc_nand.nand_fir1);

			अगर (column >= mtd->ग_लिखोsize)
				nand_fcr0 |=
				न_अंकD_CMD_READOOB << IFC_न_अंकD_FCR0_CMD0_SHIFT;
			अन्यथा
				nand_fcr0 |=
				न_अंकD_CMD_READ0 << IFC_न_अंकD_FCR0_CMD0_SHIFT;
		पूर्ण

		अगर (column >= mtd->ग_लिखोsize) अणु
			/* OOB area --> READOOB */
			column -= mtd->ग_लिखोsize;
			अगरc_nand_ctrl->oob = 1;
		पूर्ण
		अगरc_out32(nand_fcr0, &अगरc->अगरc_nand.nand_fcr0);
		set_addr(mtd, column, page_addr, अगरc_nand_ctrl->oob);
		वापस;
	पूर्ण

	/* PAGEPROG reuses all of the setup from SEQIN and adds the length */
	हाल न_अंकD_CMD_PAGEPROG: अणु
		अगर (अगरc_nand_ctrl->oob) अणु
			अगरc_out32(अगरc_nand_ctrl->index -
				  अगरc_nand_ctrl->column,
				  &अगरc->अगरc_nand.nand_fbcr);
		पूर्ण अन्यथा अणु
			अगरc_out32(0, &अगरc->अगरc_nand.nand_fbcr);
		पूर्ण

		fsl_अगरc_run_command(mtd);
		वापस;
	पूर्ण

	हाल न_अंकD_CMD_STATUS: अणु
		व्योम __iomem *addr;

		अगरc_out32((IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_RB << IFC_न_अंकD_FIR0_OP1_SHIFT),
			  &अगरc->अगरc_nand.nand_fir0);
		अगरc_out32(न_अंकD_CMD_STATUS << IFC_न_अंकD_FCR0_CMD0_SHIFT,
			  &अगरc->अगरc_nand.nand_fcr0);
		अगरc_out32(1, &अगरc->अगरc_nand.nand_fbcr);
		set_addr(mtd, 0, 0, 0);
		अगरc_nand_ctrl->पढ़ो_bytes = 1;

		fsl_अगरc_run_command(mtd);

		/*
		 * The chip always seems to report that it is
		 * ग_लिखो-रक्षित, even when it is not.
		 */
		addr = अगरc_nand_ctrl->addr;
		अगर (chip->options & न_अंकD_BUSWIDTH_16)
			अगरc_out16(अगरc_in16(addr) | (न_अंकD_STATUS_WP), addr);
		अन्यथा
			अगरc_out8(अगरc_in8(addr) | (न_अंकD_STATUS_WP), addr);
		वापस;
	पूर्ण

	हाल न_अंकD_CMD_RESET:
		अगरc_out32(IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT,
			  &अगरc->अगरc_nand.nand_fir0);
		अगरc_out32(न_अंकD_CMD_RESET << IFC_न_अंकD_FCR0_CMD0_SHIFT,
			  &अगरc->अगरc_nand.nand_fcr0);
		fsl_अगरc_run_command(mtd);
		वापस;

	शेष:
		dev_err(priv->dev, "%s: error, unsupported command 0x%x.\n",
					__func__, command);
	पूर्ण
पूर्ण

अटल व्योम fsl_अगरc_select_chip(काष्ठा nand_chip *chip, पूर्णांक cs)
अणु
	/* The hardware करोes not seem to support multiple
	 * chips per bank.
	 */
पूर्ण

/*
 * Write buf to the IFC न_अंकD Controller Data Buffer
 */
अटल व्योम fsl_अगरc_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u8 *buf, पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	अचिन्हित पूर्णांक bufsize = mtd->ग_लिखोsize + mtd->oobsize;

	अगर (len <= 0) अणु
		dev_err(priv->dev, "%s: len %d bytes", __func__, len);
		वापस;
	पूर्ण

	अगर ((अचिन्हित पूर्णांक)len > bufsize - अगरc_nand_ctrl->index) अणु
		dev_err(priv->dev,
			"%s: beyond end of buffer (%d requested, %u available)\n",
			__func__, len, bufsize - अगरc_nand_ctrl->index);
		len = bufsize - अगरc_nand_ctrl->index;
	पूर्ण

	स_नकल_toio(अगरc_nand_ctrl->addr + अगरc_nand_ctrl->index, buf, len);
	अगरc_nand_ctrl->index += len;
पूर्ण

/*
 * Read a byte from either the IFC hardware buffer
 * पढ़ो function क्रम 8-bit buswidth
 */
अटल uपूर्णांक8_t fsl_अगरc_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	अचिन्हित पूर्णांक offset;

	/*
	 * If there are still bytes in the IFC buffer, then use the
	 * next byte.
	 */
	अगर (अगरc_nand_ctrl->index < अगरc_nand_ctrl->पढ़ो_bytes) अणु
		offset = अगरc_nand_ctrl->index++;
		वापस अगरc_in8(अगरc_nand_ctrl->addr + offset);
	पूर्ण

	dev_err(priv->dev, "%s: beyond end of buffer\n", __func__);
	वापस ERR_BYTE;
पूर्ण

/*
 * Read two bytes from the IFC hardware buffer
 * पढ़ो function क्रम 16-bit buswith
 */
अटल uपूर्णांक8_t fsl_अगरc_पढ़ो_byte16(काष्ठा nand_chip *chip)
अणु
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	uपूर्णांक16_t data;

	/*
	 * If there are still bytes in the IFC buffer, then use the
	 * next byte.
	 */
	अगर (अगरc_nand_ctrl->index < अगरc_nand_ctrl->पढ़ो_bytes) अणु
		data = अगरc_in16(अगरc_nand_ctrl->addr + अगरc_nand_ctrl->index);
		अगरc_nand_ctrl->index += 2;
		वापस (uपूर्णांक8_t) data;
	पूर्ण

	dev_err(priv->dev, "%s: beyond end of buffer\n", __func__);
	वापस ERR_BYTE;
पूर्ण

/*
 * Read from the IFC Controller Data Buffer
 */
अटल व्योम fsl_अगरc_पढ़ो_buf(काष्ठा nand_chip *chip, u8 *buf, पूर्णांक len)
अणु
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	पूर्णांक avail;

	अगर (len < 0) अणु
		dev_err(priv->dev, "%s: len %d bytes", __func__, len);
		वापस;
	पूर्ण

	avail = min((अचिन्हित पूर्णांक)len,
			अगरc_nand_ctrl->पढ़ो_bytes - अगरc_nand_ctrl->index);
	स_नकल_fromio(buf, अगरc_nand_ctrl->addr + अगरc_nand_ctrl->index, avail);
	अगरc_nand_ctrl->index += avail;

	अगर (len > avail)
		dev_err(priv->dev,
			"%s: beyond end of buffer (%d requested, %d available)\n",
			__func__, len, avail);
पूर्ण

/*
 * This function is called after Program and Erase Operations to
 * check क्रम success or failure.
 */
अटल पूर्णांक fsl_अगरc_रुको(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc = ctrl->rregs;
	u32 nand_fsr;
	पूर्णांक status;

	/* Use READ_STATUS command, but रुको क्रम the device to be पढ़ोy */
	अगरc_out32((IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
		  (IFC_FIR_OP_RDSTAT << IFC_न_अंकD_FIR0_OP1_SHIFT),
		  &अगरc->अगरc_nand.nand_fir0);
	अगरc_out32(न_अंकD_CMD_STATUS << IFC_न_अंकD_FCR0_CMD0_SHIFT,
		  &अगरc->अगरc_nand.nand_fcr0);
	अगरc_out32(1, &अगरc->अगरc_nand.nand_fbcr);
	set_addr(mtd, 0, 0, 0);
	अगरc_nand_ctrl->पढ़ो_bytes = 1;

	fsl_अगरc_run_command(mtd);

	nand_fsr = अगरc_in32(&अगरc->अगरc_nand.nand_fsr);
	status = nand_fsr >> 24;
	/*
	 * The chip always seems to report that it is
	 * ग_लिखो-रक्षित, even when it is not.
	 */
	वापस status | न_अंकD_STATUS_WP;
पूर्ण

/*
 * The controller करोes not check क्रम bitflips in erased pages,
 * thereक्रमe software must check instead.
 */
अटल पूर्णांक check_erased_page(काष्ठा nand_chip *chip, u8 *buf)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 *ecc = chip->oob_poi;
	स्थिर पूर्णांक ecc_size = chip->ecc.bytes;
	स्थिर पूर्णांक pkt_size = chip->ecc.size;
	पूर्णांक i, res, bitflips = 0;
	काष्ठा mtd_oob_region oobregion = अणु पूर्ण;

	mtd_ooblayout_ecc(mtd, 0, &oobregion);
	ecc += oobregion.offset;

	क्रम (i = 0; i < chip->ecc.steps; ++i) अणु
		res = nand_check_erased_ecc_chunk(buf, pkt_size, ecc, ecc_size,
						  शून्य, 0,
						  chip->ecc.strength);
		अगर (res < 0)
			mtd->ecc_stats.failed++;
		अन्यथा
			mtd->ecc_stats.corrected += res;

		bitflips = max(res, bitflips);
		buf += pkt_size;
		ecc += ecc_size;
	पूर्ण

	वापस bitflips;
पूर्ण

अटल पूर्णांक fsl_अगरc_पढ़ो_page(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			     पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_nand_ctrl *nctrl = अगरc_nand_ctrl;

	nand_पढ़ो_page_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	अगर (oob_required)
		fsl_अगरc_पढ़ो_buf(chip, chip->oob_poi, mtd->oobsize);

	अगर (ctrl->nand_stat & IFC_न_अंकD_EVTER_STAT_ECCER) अणु
		अगर (!oob_required)
			fsl_अगरc_पढ़ो_buf(chip, chip->oob_poi, mtd->oobsize);

		वापस check_erased_page(chip, buf);
	पूर्ण

	अगर (ctrl->nand_stat != IFC_न_अंकD_EVTER_STAT_OPC)
		mtd->ecc_stats.failed++;

	वापस nctrl->max_bitflips;
पूर्ण

/* ECC will be calculated स्वतःmatically, and errors will be detected in
 * रुकोfunc.
 */
अटल पूर्णांक fsl_अगरc_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			      पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	nand_prog_page_begin_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	fsl_अगरc_ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक fsl_अगरc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_अगरc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_global __iomem *अगरc_global = ctrl->gregs;
	u32 csor;

	csor = अगरc_in32(&अगरc_global->csor_cs[priv->bank].csor);

	/* Must also set CSOR_न_अंकD_ECC_ENC_EN अगर DEC_EN set */
	अगर (csor & CSOR_न_अंकD_ECC_DEC_EN) अणु
		chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
		mtd_set_ooblayout(mtd, &fsl_अगरc_ooblayout_ops);

		/* Hardware generates ECC per 512 Bytes */
		chip->ecc.size = 512;
		अगर ((csor & CSOR_न_अंकD_ECC_MODE_MASK) == CSOR_न_अंकD_ECC_MODE_4) अणु
			chip->ecc.bytes = 8;
			chip->ecc.strength = 4;
		पूर्ण अन्यथा अणु
			chip->ecc.bytes = 16;
			chip->ecc.strength = 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
	पूर्ण

	dev_dbg(priv->dev, "%s: nand->numchips = %d\n", __func__,
		nanddev_ntarमाला_लो(&chip->base));
	dev_dbg(priv->dev, "%s: nand->chipsize = %lld\n", __func__,
	        nanddev_target_size(&chip->base));
	dev_dbg(priv->dev, "%s: nand->pagemask = %8x\n", __func__,
							chip->pagemask);
	dev_dbg(priv->dev, "%s: nand->legacy.chip_delay = %d\n", __func__,
		chip->legacy.chip_delay);
	dev_dbg(priv->dev, "%s: nand->badblockpos = %d\n", __func__,
							chip->badblockpos);
	dev_dbg(priv->dev, "%s: nand->chip_shift = %d\n", __func__,
							chip->chip_shअगरt);
	dev_dbg(priv->dev, "%s: nand->page_shift = %d\n", __func__,
							chip->page_shअगरt);
	dev_dbg(priv->dev, "%s: nand->phys_erase_shift = %d\n", __func__,
							chip->phys_erase_shअगरt);
	dev_dbg(priv->dev, "%s: nand->ecc.engine_type = %d\n", __func__,
							chip->ecc.engine_type);
	dev_dbg(priv->dev, "%s: nand->ecc.steps = %d\n", __func__,
							chip->ecc.steps);
	dev_dbg(priv->dev, "%s: nand->ecc.bytes = %d\n", __func__,
							chip->ecc.bytes);
	dev_dbg(priv->dev, "%s: nand->ecc.total = %d\n", __func__,
							chip->ecc.total);
	dev_dbg(priv->dev, "%s: mtd->ooblayout = %p\n", __func__,
							mtd->ooblayout);
	dev_dbg(priv->dev, "%s: mtd->flags = %08x\n", __func__, mtd->flags);
	dev_dbg(priv->dev, "%s: mtd->size = %lld\n", __func__, mtd->size);
	dev_dbg(priv->dev, "%s: mtd->erasesize = %d\n", __func__,
							mtd->erasesize);
	dev_dbg(priv->dev, "%s: mtd->writesize = %d\n", __func__,
							mtd->ग_लिखोsize);
	dev_dbg(priv->dev, "%s: mtd->oobsize = %d\n", __func__,
							mtd->oobsize);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops fsl_अगरc_controller_ops = अणु
	.attach_chip = fsl_अगरc_attach_chip,
पूर्ण;

अटल पूर्णांक fsl_अगरc_sram_init(काष्ठा fsl_अगरc_mtd *priv)
अणु
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc_runसमय = ctrl->rregs;
	काष्ठा fsl_अगरc_global __iomem *अगरc_global = ctrl->gregs;
	uपूर्णांक32_t csor = 0, csor_8k = 0, csor_ext = 0;
	uपूर्णांक32_t cs = priv->bank;

	अगर (ctrl->version < FSL_IFC_VERSION_1_1_0)
		वापस 0;

	अगर (ctrl->version > FSL_IFC_VERSION_1_1_0) अणु
		u32 ncfgr, status;
		पूर्णांक ret;

		/* Trigger स्वतः initialization */
		ncfgr = अगरc_in32(&अगरc_runसमय->अगरc_nand.ncfgr);
		अगरc_out32(ncfgr | IFC_न_अंकD_NCFGR_SRAM_INIT_EN, &अगरc_runसमय->अगरc_nand.ncfgr);

		/* Wait until करोne */
		ret = पढ़ोx_poll_समयout(अगरc_in32, &अगरc_runसमय->अगरc_nand.ncfgr,
					 status, !(status & IFC_न_अंकD_NCFGR_SRAM_INIT_EN),
					 10, IFC_TIMEOUT_MSECS * 1000);
		अगर (ret)
			dev_err(priv->dev, "Failed to initialize SRAM!\n");

		वापस ret;
	पूर्ण

	/* Save CSOR and CSOR_ext */
	csor = अगरc_in32(&अगरc_global->csor_cs[cs].csor);
	csor_ext = अगरc_in32(&अगरc_global->csor_cs[cs].csor_ext);

	/* chage PageSize 8K and SpareSize 1K*/
	csor_8k = (csor & ~(CSOR_न_अंकD_PGS_MASK)) | 0x0018C000;
	अगरc_out32(csor_8k, &अगरc_global->csor_cs[cs].csor);
	अगरc_out32(0x0000400, &अगरc_global->csor_cs[cs].csor_ext);

	/* READID */
	अगरc_out32((IFC_FIR_OP_CW0 << IFC_न_अंकD_FIR0_OP0_SHIFT) |
		    (IFC_FIR_OP_UA  << IFC_न_अंकD_FIR0_OP1_SHIFT) |
		    (IFC_FIR_OP_RB << IFC_न_अंकD_FIR0_OP2_SHIFT),
		    &अगरc_runसमय->अगरc_nand.nand_fir0);
	अगरc_out32(न_अंकD_CMD_READID << IFC_न_अंकD_FCR0_CMD0_SHIFT,
		    &अगरc_runसमय->अगरc_nand.nand_fcr0);
	अगरc_out32(0x0, &अगरc_runसमय->अगरc_nand.row3);

	अगरc_out32(0x0, &अगरc_runसमय->अगरc_nand.nand_fbcr);

	/* Program ROW0/COL0 */
	अगरc_out32(0x0, &अगरc_runसमय->अगरc_nand.row0);
	अगरc_out32(0x0, &अगरc_runसमय->अगरc_nand.col0);

	/* set the chip select क्रम न_अंकD Transaction */
	अगरc_out32(cs << IFC_न_अंकD_CSEL_SHIFT,
		&अगरc_runसमय->अगरc_nand.nand_csel);

	/* start पढ़ो seq */
	अगरc_out32(IFC_न_अंकD_SEQ_STRT_FIR_STRT,
		&अगरc_runसमय->अगरc_nand.nandseq_strt);

	/* रुको क्रम command complete flag or समयout */
	रुको_event_समयout(ctrl->nand_रुको, ctrl->nand_stat,
			   msecs_to_jअगरfies(IFC_TIMEOUT_MSECS));

	अगर (ctrl->nand_stat != IFC_न_अंकD_EVTER_STAT_OPC) अणु
		pr_err("fsl-ifc: Failed to Initialise SRAM\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* Restore CSOR and CSOR_ext */
	अगरc_out32(csor, &अगरc_global->csor_cs[cs].csor);
	अगरc_out32(csor_ext, &अगरc_global->csor_cs[cs].csor_ext);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_अगरc_chip_init(काष्ठा fsl_अगरc_mtd *priv)
अणु
	काष्ठा fsl_अगरc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_अगरc_global __iomem *अगरc_global = ctrl->gregs;
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc_runसमय = ctrl->rregs;
	काष्ठा nand_chip *chip = &priv->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(&priv->chip);
	u32 csor;
	पूर्णांक ret;

	/* Fill in fsl_अगरc_mtd काष्ठाure */
	mtd->dev.parent = priv->dev;
	nand_set_flash_node(chip, priv->dev->of_node);

	/* fill in nand_chip काष्ठाure */
	/* set up function call table */
	अगर ((अगरc_in32(&अगरc_global->cspr_cs[priv->bank].cspr))
		& CSPR_PORT_SIZE_16)
		chip->legacy.पढ़ो_byte = fsl_अगरc_पढ़ो_byte16;
	अन्यथा
		chip->legacy.पढ़ो_byte = fsl_अगरc_पढ़ो_byte;

	chip->legacy.ग_लिखो_buf = fsl_अगरc_ग_लिखो_buf;
	chip->legacy.पढ़ो_buf = fsl_अगरc_पढ़ो_buf;
	chip->legacy.select_chip = fsl_अगरc_select_chip;
	chip->legacy.cmdfunc = fsl_अगरc_cmdfunc;
	chip->legacy.रुकोfunc = fsl_अगरc_रुको;
	chip->legacy.set_features = nand_get_set_features_notsupp;
	chip->legacy.get_features = nand_get_set_features_notsupp;

	chip->bbt_td = &bbt_मुख्य_descr;
	chip->bbt_md = &bbt_mirror_descr;

	अगरc_out32(0x0, &अगरc_runसमय->अगरc_nand.ncfgr);

	/* set up nand options */
	chip->bbt_options = न_अंकD_BBT_USE_FLASH;
	chip->options = न_अंकD_NO_SUBPAGE_WRITE;

	अगर (अगरc_in32(&अगरc_global->cspr_cs[priv->bank].cspr)
		& CSPR_PORT_SIZE_16) अणु
		chip->legacy.पढ़ो_byte = fsl_अगरc_पढ़ो_byte16;
		chip->options |= न_अंकD_BUSWIDTH_16;
	पूर्ण अन्यथा अणु
		chip->legacy.पढ़ो_byte = fsl_अगरc_पढ़ो_byte;
	पूर्ण

	chip->controller = &अगरc_nand_ctrl->controller;
	nand_set_controller_data(chip, priv);

	chip->ecc.पढ़ो_page = fsl_अगरc_पढ़ो_page;
	chip->ecc.ग_लिखो_page = fsl_अगरc_ग_लिखो_page;

	csor = अगरc_in32(&अगरc_global->csor_cs[priv->bank].csor);

	चयन (csor & CSOR_न_अंकD_PGS_MASK) अणु
	हाल CSOR_न_अंकD_PGS_512:
		अगर (!(chip->options & न_अंकD_BUSWIDTH_16)) अणु
			/* Aव्योम conflict with bad block marker */
			bbt_मुख्य_descr.offs = 0;
			bbt_mirror_descr.offs = 0;
		पूर्ण

		priv->bufnum_mask = 15;
		अवरोध;

	हाल CSOR_न_अंकD_PGS_2K:
		priv->bufnum_mask = 3;
		अवरोध;

	हाल CSOR_न_अंकD_PGS_4K:
		priv->bufnum_mask = 1;
		अवरोध;

	हाल CSOR_न_अंकD_PGS_8K:
		priv->bufnum_mask = 0;
		अवरोध;

	शेष:
		dev_err(priv->dev, "bad csor %#x: bad page size\n", csor);
		वापस -ENODEV;
	पूर्ण

	ret = fsl_अगरc_sram_init(priv);
	अगर (ret)
		वापस ret;

	/*
	 * As IFC version 2.0.0 has 16KB of पूर्णांकernal SRAM as compared to older
	 * versions which had 8KB. Hence bufnum mask needs to be updated.
	 */
	अगर (ctrl->version >= FSL_IFC_VERSION_2_0_0)
		priv->bufnum_mask = (priv->bufnum_mask * 2) + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_अगरc_chip_हटाओ(काष्ठा fsl_अगरc_mtd *priv)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(&priv->chip);

	kमुक्त(mtd->name);

	अगर (priv->vbase)
		iounmap(priv->vbase);

	अगरc_nand_ctrl->chips[priv->bank] = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक match_bank(काष्ठा fsl_अगरc_global __iomem *अगरc_global, पूर्णांक bank,
		      phys_addr_t addr)
अणु
	u32 cspr = अगरc_in32(&अगरc_global->cspr_cs[bank].cspr);

	अगर (!(cspr & CSPR_V))
		वापस 0;
	अगर ((cspr & CSPR_MSEL) != CSPR_MSEL_न_अंकD)
		वापस 0;

	वापस (cspr & CSPR_BA) == convert_अगरc_address(addr);
पूर्ण

अटल DEFINE_MUTEX(fsl_अगरc_nand_mutex);

अटल पूर्णांक fsl_अगरc_nand_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fsl_अगरc_runसमय __iomem *अगरc;
	काष्ठा fsl_अगरc_mtd *priv;
	काष्ठा resource res;
	अटल स्थिर अक्षर *part_probe_types[]
		= अणु "cmdlinepart", "RedBoot", "ofpart", शून्य पूर्ण;
	पूर्णांक ret;
	पूर्णांक bank;
	काष्ठा device_node *node = dev->dev.of_node;
	काष्ठा mtd_info *mtd;

	अगर (!fsl_अगरc_ctrl_dev || !fsl_अगरc_ctrl_dev->rregs)
		वापस -ENODEV;
	अगरc = fsl_अगरc_ctrl_dev->rregs;

	/* get, allocate and map the memory resource */
	ret = of_address_to_resource(node, 0, &res);
	अगर (ret) अणु
		dev_err(&dev->dev, "%s: failed to get resource\n", __func__);
		वापस ret;
	पूर्ण

	/* find which chip select it is connected to */
	क्रम (bank = 0; bank < fsl_अगरc_ctrl_dev->banks; bank++) अणु
		अगर (match_bank(fsl_अगरc_ctrl_dev->gregs, bank, res.start))
			अवरोध;
	पूर्ण

	अगर (bank >= fsl_अगरc_ctrl_dev->banks) अणु
		dev_err(&dev->dev, "%s: address did not match any chip selects\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&dev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_lock(&fsl_अगरc_nand_mutex);
	अगर (!fsl_अगरc_ctrl_dev->nand) अणु
		अगरc_nand_ctrl = kzalloc(माप(*अगरc_nand_ctrl), GFP_KERNEL);
		अगर (!अगरc_nand_ctrl) अणु
			mutex_unlock(&fsl_अगरc_nand_mutex);
			वापस -ENOMEM;
		पूर्ण

		अगरc_nand_ctrl->पढ़ो_bytes = 0;
		अगरc_nand_ctrl->index = 0;
		अगरc_nand_ctrl->addr = शून्य;
		fsl_अगरc_ctrl_dev->nand = अगरc_nand_ctrl;

		nand_controller_init(&अगरc_nand_ctrl->controller);
	पूर्ण अन्यथा अणु
		अगरc_nand_ctrl = fsl_अगरc_ctrl_dev->nand;
	पूर्ण
	mutex_unlock(&fsl_अगरc_nand_mutex);

	अगरc_nand_ctrl->chips[bank] = priv;
	priv->bank = bank;
	priv->ctrl = fsl_अगरc_ctrl_dev;
	priv->dev = &dev->dev;

	priv->vbase = ioremap(res.start, resource_size(&res));
	अगर (!priv->vbase) अणु
		dev_err(priv->dev, "%s: failed to map chip region\n", __func__);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev_set_drvdata(priv->dev, priv);

	अगरc_out32(IFC_न_अंकD_EVTER_EN_OPC_EN |
		  IFC_न_अंकD_EVTER_EN_FTOER_EN |
		  IFC_न_अंकD_EVTER_EN_WPER_EN,
		  &अगरc->अगरc_nand.nand_evter_en);

	/* enable न_अंकD Machine Interrupts */
	अगरc_out32(IFC_न_अंकD_EVTER_INTR_OPCIR_EN |
		  IFC_न_अंकD_EVTER_INTR_FTOERIR_EN |
		  IFC_न_अंकD_EVTER_INTR_WPERIR_EN,
		  &अगरc->अगरc_nand.nand_evter_पूर्णांकr_en);

	mtd = nand_to_mtd(&priv->chip);
	mtd->name = kaप्र_लिखो(GFP_KERNEL, "%llx.flash", (u64)res.start);
	अगर (!mtd->name) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = fsl_अगरc_chip_init(priv);
	अगर (ret)
		जाओ err;

	priv->chip.controller->ops = &fsl_अगरc_controller_ops;
	ret = nand_scan(&priv->chip, 1);
	अगर (ret)
		जाओ err;

	/* First look क्रम RedBoot table or partitions on the command
	 * line, these take precedence over device tree inक्रमmation */
	ret = mtd_device_parse_रेजिस्टर(mtd, part_probe_types, शून्य, शून्य, 0);
	अगर (ret)
		जाओ cleanup_nand;

	dev_info(priv->dev, "IFC NAND device at 0x%llx, bank %d\n",
		 (अचिन्हित दीर्घ दीर्घ)res.start, priv->bank);

	वापस 0;

cleanup_nand:
	nand_cleanup(&priv->chip);
err:
	fsl_अगरc_chip_हटाओ(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_अगरc_nand_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fsl_अगरc_mtd *priv = dev_get_drvdata(&dev->dev);
	काष्ठा nand_chip *chip = &priv->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	fsl_अगरc_chip_हटाओ(priv);

	mutex_lock(&fsl_अगरc_nand_mutex);
	अगरc_nand_ctrl->counter--;
	अगर (!अगरc_nand_ctrl->counter) अणु
		fsl_अगरc_ctrl_dev->nand = शून्य;
		kमुक्त(अगरc_nand_ctrl);
	पूर्ण
	mutex_unlock(&fsl_अगरc_nand_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_अगरc_nand_match[] = अणु
	अणु
		.compatible = "fsl,ifc-nand",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_अगरc_nand_match);

अटल काष्ठा platक्रमm_driver fsl_अगरc_nand_driver = अणु
	.driver = अणु
		.name	= "fsl,ifc-nand",
		.of_match_table = fsl_अगरc_nand_match,
	पूर्ण,
	.probe       = fsl_अगरc_nand_probe,
	.हटाओ      = fsl_अगरc_nand_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl_अगरc_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Freescale");
MODULE_DESCRIPTION("Freescale Integrated Flash Controller MTD NAND driver");
