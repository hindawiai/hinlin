<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Freescale Enhanced Local Bus Controller न_अंकD driver
 *
 * Copyright तऊ 2006-2007, 2010 Freescale Semiconductor
 *
 * Authors: Nick Spence <nick.spence@मुक्तscale.com>,
 *          Scott Wood <scottwood@मुक्तscale.com>
 *          Jack Lan <jack.lan@मुक्तscale.com>
 *          Roy Zang <tie-fei.zang@मुक्तscale.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/fsl_lbc.h>

#घोषणा MAX_BANKS 8
#घोषणा ERR_BYTE 0xFF /* Value वापसed क्रम पढ़ो bytes when पढ़ो failed */
#घोषणा FCM_TIMEOUT_MSECS 500 /* Maximum number of mSecs to रुको क्रम FCM */

/* mtd inक्रमmation per set */

काष्ठा fsl_elbc_mtd अणु
	काष्ठा nand_chip chip;
	काष्ठा fsl_lbc_ctrl *ctrl;

	काष्ठा device *dev;
	पूर्णांक bank;               /* Chip select bank number           */
	u8 __iomem *vbase;      /* Chip select base भव address  */
	पूर्णांक page_size;          /* न_अंकD page size (0=512, 1=2048)    */
	अचिन्हित पूर्णांक fmr;       /* FCM Flash Mode Register value     */
पूर्ण;

/* Freescale eLBC FCM controller inक्रमmation */

काष्ठा fsl_elbc_fcm_ctrl अणु
	काष्ठा nand_controller controller;
	काष्ठा fsl_elbc_mtd *chips[MAX_BANKS];

	u8 __iomem *addr;        /* Address of asचिन्हित FCM buffer        */
	अचिन्हित पूर्णांक page;       /* Last page written to / पढ़ो from      */
	अचिन्हित पूर्णांक पढ़ो_bytes; /* Number of bytes पढ़ो during command   */
	अचिन्हित पूर्णांक column;     /* Saved column from SEQIN               */
	अचिन्हित पूर्णांक index;      /* Poपूर्णांकer to next byte to 'read'        */
	अचिन्हित पूर्णांक status;     /* status पढ़ो from LTESR after last op  */
	अचिन्हित पूर्णांक mdr;        /* UPM/FCM Data Register value           */
	अचिन्हित पूर्णांक use_mdr;    /* Non zero अगर the MDR is to be set      */
	अचिन्हित पूर्णांक oob;        /* Non zero अगर operating on OOB data     */
	अचिन्हित पूर्णांक counter;	 /* counter क्रम the initializations	  */
	अचिन्हित पूर्णांक max_bitflips;  /* Saved during READ0 cmd		  */
पूर्ण;

/* These map to the positions used by the FCM hardware ECC generator */

अटल पूर्णांक fsl_elbc_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);

	अगर (section >= chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = (16 * section) + 6;
	अगर (priv->fmr & FMR_ECCM)
		oobregion->offset += 2;

	oobregion->length = chip->ecc.bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_elbc_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);

	अगर (section > chip->ecc.steps)
		वापस -दुस्फल;

	अगर (!section) अणु
		oobregion->offset = 0;
		अगर (mtd->ग_लिखोsize > 512)
			oobregion->offset++;
		oobregion->length = (priv->fmr & FMR_ECCM) ? 7 : 5;
	पूर्ण अन्यथा अणु
		oobregion->offset = (16 * section) -
				    ((priv->fmr & FMR_ECCM) ? 5 : 7);
		अगर (section < chip->ecc.steps)
			oobregion->length = 13;
		अन्यथा
			oobregion->length = mtd->oobsize - oobregion->offset;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops fsl_elbc_ooblayout_ops = अणु
	.ecc = fsl_elbc_ooblayout_ecc,
	.मुक्त = fsl_elbc_ooblayout_मुक्त,
पूर्ण;

/*
 * ELBC may use HW ECC, so that OOB offsets, that न_अंकD core uses क्रम bbt,
 * पूर्णांकerfere with ECC positions, that's why we implement our own descriptors.
 * OOB अणु11, 5पूर्ण, works क्रम both SP and LP chips, with ECCM = 1 and ECCM = 0.
 */
अटल u8 bbt_pattern[] = अणु'B', 'b', 't', '0' पूर्ण;
अटल u8 mirror_pattern[] = अणु'1', 't', 'b', 'B' पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_मुख्य_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE |
		   न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION,
	.offs =	11,
	.len = 4,
	.veroffs = 15,
	.maxblocks = 4,
	.pattern = bbt_pattern,
पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_mirror_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE |
		   न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION,
	.offs =	11,
	.len = 4,
	.veroffs = 15,
	.maxblocks = 4,
	.pattern = mirror_pattern,
पूर्ण;

/*=================================*/

/*
 * Set up the FCM hardware block and page address fields, and the fcm
 * काष्ठाure addr field to poपूर्णांक to the correct FCM buffer in memory
 */
अटल व्योम set_addr(काष्ठा mtd_info *mtd, पूर्णांक column, पूर्णांक page_addr, पूर्णांक oob)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_lbc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_lbc_regs __iomem *lbc = ctrl->regs;
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = ctrl->nand;
	पूर्णांक buf_num;

	elbc_fcm_ctrl->page = page_addr;

	अगर (priv->page_size) अणु
		/*
		 * large page size chip : FPAR[PI] save the lowest 6 bits,
		 *                        FBAR[BLK] save the other bits.
		 */
		out_be32(&lbc->fbar, page_addr >> 6);
		out_be32(&lbc->fpar,
		         ((page_addr << FPAR_LP_PI_SHIFT) & FPAR_LP_PI) |
		         (oob ? FPAR_LP_MS : 0) | column);
		buf_num = (page_addr & 1) << 2;
	पूर्ण अन्यथा अणु
		/*
		 * small page size chip : FPAR[PI] save the lowest 5 bits,
		 *                        FBAR[BLK] save the other bits.
		 */
		out_be32(&lbc->fbar, page_addr >> 5);
		out_be32(&lbc->fpar,
		         ((page_addr << FPAR_SP_PI_SHIFT) & FPAR_SP_PI) |
		         (oob ? FPAR_SP_MS : 0) | column);
		buf_num = page_addr & 7;
	पूर्ण

	elbc_fcm_ctrl->addr = priv->vbase + buf_num * 1024;
	elbc_fcm_ctrl->index = column;

	/* क्रम OOB data poपूर्णांक to the second half of the buffer */
	अगर (oob)
		elbc_fcm_ctrl->index += priv->page_size ? 2048 : 512;

	dev_vdbg(priv->dev, "set_addr: bank=%d, "
			    "elbc_fcm_ctrl->addr=0x%p (0x%p), "
	                    "index %x, pes %d ps %d\n",
		 buf_num, elbc_fcm_ctrl->addr, priv->vbase,
		 elbc_fcm_ctrl->index,
	         chip->phys_erase_shअगरt, chip->page_shअगरt);
पूर्ण

/*
 * execute FCM command and रुको क्रम it to complete
 */
अटल पूर्णांक fsl_elbc_run_command(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_lbc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = ctrl->nand;
	काष्ठा fsl_lbc_regs __iomem *lbc = ctrl->regs;

	/* Setup the FMR[OP] to execute without ग_लिखो protection */
	out_be32(&lbc->fmr, priv->fmr | 3);
	अगर (elbc_fcm_ctrl->use_mdr)
		out_be32(&lbc->mdr, elbc_fcm_ctrl->mdr);

	dev_vdbg(priv->dev,
	         "fsl_elbc_run_command: fmr=%08x fir=%08x fcr=%08x\n",
	         in_be32(&lbc->fmr), in_be32(&lbc->fir), in_be32(&lbc->fcr));
	dev_vdbg(priv->dev,
	         "fsl_elbc_run_command: fbar=%08x fpar=%08x "
	         "fbcr=%08x bank=%d\n",
	         in_be32(&lbc->fbar), in_be32(&lbc->fpar),
	         in_be32(&lbc->fbcr), priv->bank);

	ctrl->irq_status = 0;
	/* execute special operation */
	out_be32(&lbc->lsor, priv->bank);

	/* रुको क्रम FCM complete flag or समयout */
	रुको_event_समयout(ctrl->irq_रुको, ctrl->irq_status,
	                   FCM_TIMEOUT_MSECS * HZ/1000);
	elbc_fcm_ctrl->status = ctrl->irq_status;
	/* store mdr value in हाल it was needed */
	अगर (elbc_fcm_ctrl->use_mdr)
		elbc_fcm_ctrl->mdr = in_be32(&lbc->mdr);

	elbc_fcm_ctrl->use_mdr = 0;

	अगर (elbc_fcm_ctrl->status != LTESR_CC) अणु
		dev_info(priv->dev,
		         "command failed: fir %x fcr %x status %x mdr %x\n",
		         in_be32(&lbc->fir), in_be32(&lbc->fcr),
			 elbc_fcm_ctrl->status, elbc_fcm_ctrl->mdr);
		वापस -EIO;
	पूर्ण

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	elbc_fcm_ctrl->max_bitflips = 0;

	अगर (elbc_fcm_ctrl->पढ़ो_bytes == mtd->ग_लिखोsize + mtd->oobsize) अणु
		uपूर्णांक32_t lteccr = in_be32(&lbc->lteccr);
		/*
		 * अगर command was a full page पढ़ो and the ELBC
		 * has the LTECCR रेजिस्टर, then bits 12-15 (ppc order) of
		 * LTECCR indicates which 512 byte sub-pages had fixed errors.
		 * bits 28-31 are uncorrectable errors, marked अन्यथाwhere.
		 * क्रम small page nand only 1 bit is used.
		 * अगर the ELBC करोesn't have the lteccr रेजिस्टर it पढ़ोs 0
		 * FIXME: 4 bits can be corrected on न_अंकDs with 2k pages, so
		 * count the number of sub-pages with bitflips and update
		 * ecc_stats.corrected accordingly.
		 */
		अगर (lteccr & 0x000F000F)
			out_be32(&lbc->lteccr, 0x000F000F); /* clear lteccr */
		अगर (lteccr & 0x000F0000) अणु
			mtd->ecc_stats.corrected++;
			elbc_fcm_ctrl->max_bitflips = 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fsl_elbc_करो_पढ़ो(काष्ठा nand_chip *chip, पूर्णांक oob)
अणु
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_lbc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_lbc_regs __iomem *lbc = ctrl->regs;

	अगर (priv->page_size) अणु
		out_be32(&lbc->fir,
		         (FIR_OP_CM0 << FIR_OP0_SHIFT) |
		         (FIR_OP_CA  << FIR_OP1_SHIFT) |
		         (FIR_OP_PA  << FIR_OP2_SHIFT) |
		         (FIR_OP_CM1 << FIR_OP3_SHIFT) |
		         (FIR_OP_RBW << FIR_OP4_SHIFT));

		out_be32(&lbc->fcr, (न_अंकD_CMD_READ0 << FCR_CMD0_SHIFT) |
		                    (न_अंकD_CMD_READSTART << FCR_CMD1_SHIFT));
	पूर्ण अन्यथा अणु
		out_be32(&lbc->fir,
		         (FIR_OP_CM0 << FIR_OP0_SHIFT) |
		         (FIR_OP_CA  << FIR_OP1_SHIFT) |
		         (FIR_OP_PA  << FIR_OP2_SHIFT) |
		         (FIR_OP_RBW << FIR_OP3_SHIFT));

		अगर (oob)
			out_be32(&lbc->fcr, न_अंकD_CMD_READOOB << FCR_CMD0_SHIFT);
		अन्यथा
			out_be32(&lbc->fcr, न_अंकD_CMD_READ0 << FCR_CMD0_SHIFT);
	पूर्ण
पूर्ण

/* cmdfunc send commands to the FCM */
अटल व्योम fsl_elbc_cmdfunc(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक command,
                             पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_lbc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = ctrl->nand;
	काष्ठा fsl_lbc_regs __iomem *lbc = ctrl->regs;

	elbc_fcm_ctrl->use_mdr = 0;

	/* clear the पढ़ो buffer */
	elbc_fcm_ctrl->पढ़ो_bytes = 0;
	अगर (command != न_अंकD_CMD_PAGEPROG)
		elbc_fcm_ctrl->index = 0;

	चयन (command) अणु
	/* READ0 and READ1 पढ़ो the entire buffer to use hardware ECC. */
	हाल न_अंकD_CMD_READ1:
		column += 256;
		fallthrough;
	हाल न_अंकD_CMD_READ0:
		dev_dbg(priv->dev,
		        "fsl_elbc_cmdfunc: NAND_CMD_READ0, page_addr:"
		        " 0x%x, column: 0x%x.\n", page_addr, column);


		out_be32(&lbc->fbcr, 0); /* पढ़ो entire page to enable ECC */
		set_addr(mtd, 0, page_addr, 0);

		elbc_fcm_ctrl->पढ़ो_bytes = mtd->ग_लिखोsize + mtd->oobsize;
		elbc_fcm_ctrl->index += column;

		fsl_elbc_करो_पढ़ो(chip, 0);
		fsl_elbc_run_command(mtd);
		वापस;

	/* RNDOUT moves the poपूर्णांकer inside the page */
	हाल न_अंकD_CMD_RNDOUT:
		dev_dbg(priv->dev,
			"fsl_elbc_cmdfunc: NAND_CMD_RNDOUT, column: 0x%x.\n",
			column);

		elbc_fcm_ctrl->index = column;
		वापस;

	/* READOOB पढ़ोs only the OOB because no ECC is perक्रमmed. */
	हाल न_अंकD_CMD_READOOB:
		dev_vdbg(priv->dev,
		         "fsl_elbc_cmdfunc: NAND_CMD_READOOB, page_addr:"
			 " 0x%x, column: 0x%x.\n", page_addr, column);

		out_be32(&lbc->fbcr, mtd->oobsize - column);
		set_addr(mtd, column, page_addr, 1);

		elbc_fcm_ctrl->पढ़ो_bytes = mtd->ग_लिखोsize + mtd->oobsize;

		fsl_elbc_करो_पढ़ो(chip, 1);
		fsl_elbc_run_command(mtd);
		वापस;

	हाल न_अंकD_CMD_READID:
	हाल न_अंकD_CMD_PARAM:
		dev_vdbg(priv->dev, "fsl_elbc_cmdfunc: NAND_CMD %x\n", command);

		out_be32(&lbc->fir, (FIR_OP_CM0 << FIR_OP0_SHIFT) |
		                    (FIR_OP_UA  << FIR_OP1_SHIFT) |
		                    (FIR_OP_RBW << FIR_OP2_SHIFT));
		out_be32(&lbc->fcr, command << FCR_CMD0_SHIFT);
		/*
		 * although currently it's 8 bytes क्रम READID, we always पढ़ो
		 * the maximum 256 bytes(क्रम PARAM)
		 */
		out_be32(&lbc->fbcr, 256);
		elbc_fcm_ctrl->पढ़ो_bytes = 256;
		elbc_fcm_ctrl->use_mdr = 1;
		elbc_fcm_ctrl->mdr = column;
		set_addr(mtd, 0, 0, 0);
		fsl_elbc_run_command(mtd);
		वापस;

	/* ERASE1 stores the block and page address */
	हाल न_अंकD_CMD_ERASE1:
		dev_vdbg(priv->dev,
		         "fsl_elbc_cmdfunc: NAND_CMD_ERASE1, "
		         "page_addr: 0x%x.\n", page_addr);
		set_addr(mtd, 0, page_addr, 0);
		वापस;

	/* ERASE2 uses the block and page address from ERASE1 */
	हाल न_अंकD_CMD_ERASE2:
		dev_vdbg(priv->dev, "fsl_elbc_cmdfunc: NAND_CMD_ERASE2.\n");

		out_be32(&lbc->fir,
		         (FIR_OP_CM0 << FIR_OP0_SHIFT) |
		         (FIR_OP_PA  << FIR_OP1_SHIFT) |
		         (FIR_OP_CM2 << FIR_OP2_SHIFT) |
		         (FIR_OP_CW1 << FIR_OP3_SHIFT) |
		         (FIR_OP_RS  << FIR_OP4_SHIFT));

		out_be32(&lbc->fcr,
		         (न_अंकD_CMD_ERASE1 << FCR_CMD0_SHIFT) |
		         (न_अंकD_CMD_STATUS << FCR_CMD1_SHIFT) |
		         (न_अंकD_CMD_ERASE2 << FCR_CMD2_SHIFT));

		out_be32(&lbc->fbcr, 0);
		elbc_fcm_ctrl->पढ़ो_bytes = 0;
		elbc_fcm_ctrl->use_mdr = 1;

		fsl_elbc_run_command(mtd);
		वापस;

	/* SEQIN sets up the addr buffer and all रेजिस्टरs except the length */
	हाल न_अंकD_CMD_SEQIN: अणु
		__be32 fcr;
		dev_vdbg(priv->dev,
			 "fsl_elbc_cmdfunc: NAND_CMD_SEQIN/PAGE_PROG, "
		         "page_addr: 0x%x, column: 0x%x.\n",
		         page_addr, column);

		elbc_fcm_ctrl->column = column;
		elbc_fcm_ctrl->use_mdr = 1;

		अगर (column >= mtd->ग_लिखोsize) अणु
			/* OOB area */
			column -= mtd->ग_लिखोsize;
			elbc_fcm_ctrl->oob = 1;
		पूर्ण अन्यथा अणु
			WARN_ON(column != 0);
			elbc_fcm_ctrl->oob = 0;
		पूर्ण

		fcr = (न_अंकD_CMD_STATUS   << FCR_CMD1_SHIFT) |
		      (न_अंकD_CMD_SEQIN    << FCR_CMD2_SHIFT) |
		      (न_अंकD_CMD_PAGEPROG << FCR_CMD3_SHIFT);

		अगर (priv->page_size) अणु
			out_be32(&lbc->fir,
			         (FIR_OP_CM2 << FIR_OP0_SHIFT) |
			         (FIR_OP_CA  << FIR_OP1_SHIFT) |
			         (FIR_OP_PA  << FIR_OP2_SHIFT) |
			         (FIR_OP_WB  << FIR_OP3_SHIFT) |
			         (FIR_OP_CM3 << FIR_OP4_SHIFT) |
			         (FIR_OP_CW1 << FIR_OP5_SHIFT) |
			         (FIR_OP_RS  << FIR_OP6_SHIFT));
		पूर्ण अन्यथा अणु
			out_be32(&lbc->fir,
			         (FIR_OP_CM0 << FIR_OP0_SHIFT) |
			         (FIR_OP_CM2 << FIR_OP1_SHIFT) |
			         (FIR_OP_CA  << FIR_OP2_SHIFT) |
			         (FIR_OP_PA  << FIR_OP3_SHIFT) |
			         (FIR_OP_WB  << FIR_OP4_SHIFT) |
			         (FIR_OP_CM3 << FIR_OP5_SHIFT) |
			         (FIR_OP_CW1 << FIR_OP6_SHIFT) |
			         (FIR_OP_RS  << FIR_OP7_SHIFT));

			अगर (elbc_fcm_ctrl->oob)
				/* OOB area --> READOOB */
				fcr |= न_अंकD_CMD_READOOB << FCR_CMD0_SHIFT;
			अन्यथा
				/* First 256 bytes --> READ0 */
				fcr |= न_अंकD_CMD_READ0 << FCR_CMD0_SHIFT;
		पूर्ण

		out_be32(&lbc->fcr, fcr);
		set_addr(mtd, column, page_addr, elbc_fcm_ctrl->oob);
		वापस;
	पूर्ण

	/* PAGEPROG reuses all of the setup from SEQIN and adds the length */
	हाल न_अंकD_CMD_PAGEPROG: अणु
		dev_vdbg(priv->dev,
		         "fsl_elbc_cmdfunc: NAND_CMD_PAGEPROG "
			 "writing %d bytes.\n", elbc_fcm_ctrl->index);

		/* अगर the ग_लिखो did not start at 0 or is not a full page
		 * then set the exact length, otherwise use a full page
		 * ग_लिखो so the HW generates the ECC.
		 */
		अगर (elbc_fcm_ctrl->oob || elbc_fcm_ctrl->column != 0 ||
		    elbc_fcm_ctrl->index != mtd->ग_लिखोsize + mtd->oobsize)
			out_be32(&lbc->fbcr,
				elbc_fcm_ctrl->index - elbc_fcm_ctrl->column);
		अन्यथा
			out_be32(&lbc->fbcr, 0);

		fsl_elbc_run_command(mtd);
		वापस;
	पूर्ण

	/* CMD_STATUS must पढ़ो the status byte जबतक CEB is active */
	/* Note - it करोes not रुको क्रम the पढ़ोy line */
	हाल न_अंकD_CMD_STATUS:
		out_be32(&lbc->fir,
		         (FIR_OP_CM0 << FIR_OP0_SHIFT) |
		         (FIR_OP_RBW << FIR_OP1_SHIFT));
		out_be32(&lbc->fcr, न_अंकD_CMD_STATUS << FCR_CMD0_SHIFT);
		out_be32(&lbc->fbcr, 1);
		set_addr(mtd, 0, 0, 0);
		elbc_fcm_ctrl->पढ़ो_bytes = 1;

		fsl_elbc_run_command(mtd);

		/* The chip always seems to report that it is
		 * ग_लिखो-रक्षित, even when it is not.
		 */
		setbits8(elbc_fcm_ctrl->addr, न_अंकD_STATUS_WP);
		वापस;

	/* RESET without रुकोing क्रम the पढ़ोy line */
	हाल न_अंकD_CMD_RESET:
		dev_dbg(priv->dev, "fsl_elbc_cmdfunc: NAND_CMD_RESET.\n");
		out_be32(&lbc->fir, FIR_OP_CM0 << FIR_OP0_SHIFT);
		out_be32(&lbc->fcr, न_अंकD_CMD_RESET << FCR_CMD0_SHIFT);
		fsl_elbc_run_command(mtd);
		वापस;

	शेष:
		dev_err(priv->dev,
		        "fsl_elbc_cmdfunc: error, unsupported command 0x%x.\n",
		        command);
	पूर्ण
पूर्ण

अटल व्योम fsl_elbc_select_chip(काष्ठा nand_chip *chip, पूर्णांक cs)
अणु
	/* The hardware करोes not seem to support multiple
	 * chips per bank.
	 */
पूर्ण

/*
 * Write buf to the FCM Controller Data Buffer
 */
अटल व्योम fsl_elbc_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u8 *buf, पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = priv->ctrl->nand;
	अचिन्हित पूर्णांक bufsize = mtd->ग_लिखोsize + mtd->oobsize;

	अगर (len <= 0) अणु
		dev_err(priv->dev, "write_buf of %d bytes", len);
		elbc_fcm_ctrl->status = 0;
		वापस;
	पूर्ण

	अगर ((अचिन्हित पूर्णांक)len > bufsize - elbc_fcm_ctrl->index) अणु
		dev_err(priv->dev,
		        "write_buf beyond end of buffer "
		        "(%d requested, %u available)\n",
			len, bufsize - elbc_fcm_ctrl->index);
		len = bufsize - elbc_fcm_ctrl->index;
	पूर्ण

	स_नकल_toio(&elbc_fcm_ctrl->addr[elbc_fcm_ctrl->index], buf, len);
	/*
	 * This is workaround क्रम the weird elbc hangs during nand ग_लिखो,
	 * Scott Wood says: "...perhaps dअगरference in how दीर्घ it takes a
	 * ग_लिखो to make it through the localbus compared to a ग_लिखो to IMMR
	 * is causing problems, and sync isn't helping क्रम some reason."
	 * Reading back the last byte helps though.
	 */
	in_8(&elbc_fcm_ctrl->addr[elbc_fcm_ctrl->index] + len - 1);

	elbc_fcm_ctrl->index += len;
पूर्ण

/*
 * पढ़ो a byte from either the FCM hardware buffer अगर it has any data left
 * otherwise issue a command to पढ़ो a single byte.
 */
अटल u8 fsl_elbc_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = priv->ctrl->nand;

	/* If there are still bytes in the FCM, then use the next byte. */
	अगर (elbc_fcm_ctrl->index < elbc_fcm_ctrl->पढ़ो_bytes)
		वापस in_8(&elbc_fcm_ctrl->addr[elbc_fcm_ctrl->index++]);

	dev_err(priv->dev, "read_byte beyond end of buffer\n");
	वापस ERR_BYTE;
पूर्ण

/*
 * Read from the FCM Controller Data Buffer
 */
अटल व्योम fsl_elbc_पढ़ो_buf(काष्ठा nand_chip *chip, u8 *buf, पूर्णांक len)
अणु
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = priv->ctrl->nand;
	पूर्णांक avail;

	अगर (len < 0)
		वापस;

	avail = min((अचिन्हित पूर्णांक)len,
			elbc_fcm_ctrl->पढ़ो_bytes - elbc_fcm_ctrl->index);
	स_नकल_fromio(buf, &elbc_fcm_ctrl->addr[elbc_fcm_ctrl->index], avail);
	elbc_fcm_ctrl->index += avail;

	अगर (len > avail)
		dev_err(priv->dev,
		        "read_buf beyond end of buffer "
		        "(%d requested, %d available)\n",
		        len, avail);
पूर्ण

/* This function is called after Program and Erase Operations to
 * check क्रम success or failure.
 */
अटल पूर्णांक fsl_elbc_रुको(काष्ठा nand_chip *chip)
अणु
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = priv->ctrl->nand;

	अगर (elbc_fcm_ctrl->status != LTESR_CC)
		वापस न_अंकD_STATUS_FAIL;

	/* The chip always seems to report that it is
	 * ग_लिखो-रक्षित, even when it is not.
	 */
	वापस (elbc_fcm_ctrl->mdr & 0xff) | न_अंकD_STATUS_WP;
पूर्ण

अटल पूर्णांक fsl_elbc_पढ़ो_page(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			      पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_lbc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = ctrl->nand;

	nand_पढ़ो_page_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	अगर (oob_required)
		fsl_elbc_पढ़ो_buf(chip, chip->oob_poi, mtd->oobsize);

	अगर (fsl_elbc_रुको(chip) & न_अंकD_STATUS_FAIL)
		mtd->ecc_stats.failed++;

	वापस elbc_fcm_ctrl->max_bitflips;
पूर्ण

/* ECC will be calculated स्वतःmatically, and errors will be detected in
 * रुकोfunc.
 */
अटल पूर्णांक fsl_elbc_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			       पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	nand_prog_page_begin_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	fsl_elbc_ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);

	वापस nand_prog_page_end_op(chip);
पूर्ण

/* ECC will be calculated स्वतःmatically, and errors will be detected in
 * रुकोfunc.
 */
अटल पूर्णांक fsl_elbc_ग_लिखो_subpage(काष्ठा nand_chip *chip, uपूर्णांक32_t offset,
				  uपूर्णांक32_t data_len, स्थिर uपूर्णांक8_t *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	fsl_elbc_ग_लिखो_buf(chip, buf, mtd->ग_लिखोsize);
	fsl_elbc_ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);
	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक fsl_elbc_chip_init(काष्ठा fsl_elbc_mtd *priv)
अणु
	काष्ठा fsl_lbc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_lbc_regs __iomem *lbc = ctrl->regs;
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = ctrl->nand;
	काष्ठा nand_chip *chip = &priv->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	dev_dbg(priv->dev, "eLBC Set Information for bank %d\n", priv->bank);

	/* Fill in fsl_elbc_mtd काष्ठाure */
	mtd->dev.parent = priv->dev;
	nand_set_flash_node(chip, priv->dev->of_node);

	/* set समयout to maximum */
	priv->fmr = 15 << FMR_CWTO_SHIFT;
	अगर (in_be32(&lbc->bank[priv->bank].or) & OR_FCM_PGS)
		priv->fmr |= FMR_ECCM;

	/* fill in nand_chip काष्ठाure */
	/* set up function call table */
	chip->legacy.पढ़ो_byte = fsl_elbc_पढ़ो_byte;
	chip->legacy.ग_लिखो_buf = fsl_elbc_ग_लिखो_buf;
	chip->legacy.पढ़ो_buf = fsl_elbc_पढ़ो_buf;
	chip->legacy.select_chip = fsl_elbc_select_chip;
	chip->legacy.cmdfunc = fsl_elbc_cmdfunc;
	chip->legacy.रुकोfunc = fsl_elbc_रुको;
	chip->legacy.set_features = nand_get_set_features_notsupp;
	chip->legacy.get_features = nand_get_set_features_notsupp;

	chip->bbt_td = &bbt_मुख्य_descr;
	chip->bbt_md = &bbt_mirror_descr;

	/* set up nand options */
	chip->bbt_options = न_अंकD_BBT_USE_FLASH;

	chip->controller = &elbc_fcm_ctrl->controller;
	nand_set_controller_data(chip, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_elbc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	काष्ठा fsl_lbc_ctrl *ctrl = priv->ctrl;
	काष्ठा fsl_lbc_regs __iomem *lbc = ctrl->regs;
	अचिन्हित पूर्णांक al;

	चयन (chip->ecc.engine_type) अणु
	/*
	 * अगर ECC was not chosen in DT, decide whether to use HW or SW ECC from
	 * CS Base Register
	 */
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
		/* If CS Base Register selects full hardware ECC then use it */
		अगर ((in_be32(&lbc->bank[priv->bank].br) & BR_DECC) ==
		    BR_DECC_CHK_GEN) अणु
			chip->ecc.पढ़ो_page = fsl_elbc_पढ़ो_page;
			chip->ecc.ग_लिखो_page = fsl_elbc_ग_लिखो_page;
			chip->ecc.ग_लिखो_subpage = fsl_elbc_ग_लिखो_subpage;

			chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
			mtd_set_ooblayout(mtd, &fsl_elbc_ooblayout_ops);
			chip->ecc.size = 512;
			chip->ecc.bytes = 3;
			chip->ecc.strength = 1;
		पूर्ण अन्यथा अणु
			/* otherwise fall back to शेष software ECC */
			chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
			chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
		पूर्ण
		अवरोध;

	/* अगर SW ECC was chosen in DT, we करो not need to set anything here */
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		अवरोध;

	/* should we also implement *_ECC_ENGINE_CONTROLLER to करो as above? */
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* calculate FMR Address Length field */
	al = 0;
	अगर (chip->pagemask & 0xffff0000)
		al++;
	अगर (chip->pagemask & 0xff000000)
		al++;

	priv->fmr |= al << FMR_AL_SHIFT;

	dev_dbg(priv->dev, "fsl_elbc_init: nand->numchips = %d\n",
	        nanddev_ntarमाला_लो(&chip->base));
	dev_dbg(priv->dev, "fsl_elbc_init: nand->chipsize = %lld\n",
	        nanddev_target_size(&chip->base));
	dev_dbg(priv->dev, "fsl_elbc_init: nand->pagemask = %8x\n",
	        chip->pagemask);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->legacy.chip_delay = %d\n",
	        chip->legacy.chip_delay);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->badblockpos = %d\n",
	        chip->badblockpos);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->chip_shift = %d\n",
	        chip->chip_shअगरt);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->page_shift = %d\n",
	        chip->page_shअगरt);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->phys_erase_shift = %d\n",
	        chip->phys_erase_shअगरt);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->ecc.engine_type = %d\n",
		chip->ecc.engine_type);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->ecc.steps = %d\n",
	        chip->ecc.steps);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->ecc.bytes = %d\n",
	        chip->ecc.bytes);
	dev_dbg(priv->dev, "fsl_elbc_init: nand->ecc.total = %d\n",
	        chip->ecc.total);
	dev_dbg(priv->dev, "fsl_elbc_init: mtd->ooblayout = %p\n",
		mtd->ooblayout);
	dev_dbg(priv->dev, "fsl_elbc_init: mtd->flags = %08x\n", mtd->flags);
	dev_dbg(priv->dev, "fsl_elbc_init: mtd->size = %lld\n", mtd->size);
	dev_dbg(priv->dev, "fsl_elbc_init: mtd->erasesize = %d\n",
	        mtd->erasesize);
	dev_dbg(priv->dev, "fsl_elbc_init: mtd->writesize = %d\n",
	        mtd->ग_लिखोsize);
	dev_dbg(priv->dev, "fsl_elbc_init: mtd->oobsize = %d\n",
	        mtd->oobsize);

	/* adjust Option Register and ECC to match Flash page size */
	अगर (mtd->ग_लिखोsize == 512) अणु
		priv->page_size = 0;
		clrbits32(&lbc->bank[priv->bank].or, OR_FCM_PGS);
	पूर्ण अन्यथा अगर (mtd->ग_लिखोsize == 2048) अणु
		priv->page_size = 1;
		setbits32(&lbc->bank[priv->bank].or, OR_FCM_PGS);
	पूर्ण अन्यथा अणु
		dev_err(priv->dev,
		        "fsl_elbc_init: page size %d is not supported\n",
		        mtd->ग_लिखोsize);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops fsl_elbc_controller_ops = अणु
	.attach_chip = fsl_elbc_attach_chip,
पूर्ण;

अटल पूर्णांक fsl_elbc_chip_हटाओ(काष्ठा fsl_elbc_mtd *priv)
अणु
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = priv->ctrl->nand;
	काष्ठा mtd_info *mtd = nand_to_mtd(&priv->chip);

	kमुक्त(mtd->name);

	अगर (priv->vbase)
		iounmap(priv->vbase);

	elbc_fcm_ctrl->chips[priv->bank] = शून्य;
	kमुक्त(priv);
	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(fsl_elbc_nand_mutex);

अटल पूर्णांक fsl_elbc_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_lbc_regs __iomem *lbc;
	काष्ठा fsl_elbc_mtd *priv;
	काष्ठा resource res;
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl;
	अटल स्थिर अक्षर *part_probe_types[]
		= अणु "cmdlinepart", "RedBoot", "ofpart", शून्य पूर्ण;
	पूर्णांक ret;
	पूर्णांक bank;
	काष्ठा device *dev;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा mtd_info *mtd;

	अगर (!fsl_lbc_ctrl_dev || !fsl_lbc_ctrl_dev->regs)
		वापस -ENODEV;
	lbc = fsl_lbc_ctrl_dev->regs;
	dev = fsl_lbc_ctrl_dev->dev;

	/* get, allocate and map the memory resource */
	ret = of_address_to_resource(node, 0, &res);
	अगर (ret) अणु
		dev_err(dev, "failed to get resource\n");
		वापस ret;
	पूर्ण

	/* find which chip select it is connected to */
	क्रम (bank = 0; bank < MAX_BANKS; bank++)
		अगर ((in_be32(&lbc->bank[bank].br) & BR_V) &&
		    (in_be32(&lbc->bank[bank].br) & BR_MSEL) == BR_MS_FCM &&
		    (in_be32(&lbc->bank[bank].br) &
		     in_be32(&lbc->bank[bank].or) & BR_BA)
		     == fsl_lbc_addr(res.start))
			अवरोध;

	अगर (bank >= MAX_BANKS) अणु
		dev_err(dev, "address did not match any chip selects\n");
		वापस -ENODEV;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_lock(&fsl_elbc_nand_mutex);
	अगर (!fsl_lbc_ctrl_dev->nand) अणु
		elbc_fcm_ctrl = kzalloc(माप(*elbc_fcm_ctrl), GFP_KERNEL);
		अगर (!elbc_fcm_ctrl) अणु
			mutex_unlock(&fsl_elbc_nand_mutex);
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		elbc_fcm_ctrl->counter++;

		nand_controller_init(&elbc_fcm_ctrl->controller);
		fsl_lbc_ctrl_dev->nand = elbc_fcm_ctrl;
	पूर्ण अन्यथा अणु
		elbc_fcm_ctrl = fsl_lbc_ctrl_dev->nand;
	पूर्ण
	mutex_unlock(&fsl_elbc_nand_mutex);

	elbc_fcm_ctrl->chips[bank] = priv;
	priv->bank = bank;
	priv->ctrl = fsl_lbc_ctrl_dev;
	priv->dev = &pdev->dev;
	dev_set_drvdata(priv->dev, priv);

	priv->vbase = ioremap(res.start, resource_size(&res));
	अगर (!priv->vbase) अणु
		dev_err(dev, "failed to map chip region\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	mtd = nand_to_mtd(&priv->chip);
	mtd->name = kaप्र_लिखो(GFP_KERNEL, "%llx.flash", (u64)res.start);
	अगर (!nand_to_mtd(&priv->chip)->name) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = fsl_elbc_chip_init(priv);
	अगर (ret)
		जाओ err;

	priv->chip.controller->ops = &fsl_elbc_controller_ops;
	ret = nand_scan(&priv->chip, 1);
	अगर (ret)
		जाओ err;

	/* First look क्रम RedBoot table or partitions on the command
	 * line, these take precedence over device tree inक्रमmation */
	ret = mtd_device_parse_रेजिस्टर(mtd, part_probe_types, शून्य, शून्य, 0);
	अगर (ret)
		जाओ cleanup_nand;

	pr_info("eLBC NAND device at 0x%llx, bank %d\n",
		(अचिन्हित दीर्घ दीर्घ)res.start, priv->bank);

	वापस 0;

cleanup_nand:
	nand_cleanup(&priv->chip);
err:
	fsl_elbc_chip_हटाओ(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_elbc_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = fsl_lbc_ctrl_dev->nand;
	काष्ठा fsl_elbc_mtd *priv = dev_get_drvdata(&pdev->dev);
	काष्ठा nand_chip *chip = &priv->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	fsl_elbc_chip_हटाओ(priv);

	mutex_lock(&fsl_elbc_nand_mutex);
	elbc_fcm_ctrl->counter--;
	अगर (!elbc_fcm_ctrl->counter) अणु
		fsl_lbc_ctrl_dev->nand = शून्य;
		kमुक्त(elbc_fcm_ctrl);
	पूर्ण
	mutex_unlock(&fsl_elbc_nand_mutex);

	वापस 0;

पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_elbc_nand_match[] = अणु
	अणु .compatible = "fsl,elbc-fcm-nand", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_elbc_nand_match);

अटल काष्ठा platक्रमm_driver fsl_elbc_nand_driver = अणु
	.driver = अणु
		.name = "fsl,elbc-fcm-nand",
		.of_match_table = fsl_elbc_nand_match,
	पूर्ण,
	.probe = fsl_elbc_nand_probe,
	.हटाओ = fsl_elbc_nand_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl_elbc_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Freescale");
MODULE_DESCRIPTION("Freescale Enhanced Local Bus Controller MTD NAND driver");
