<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 *
 * Description:
 * QE UCC Slow API Set - UCC Slow specअगरic routines implementations.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/पन.स>
#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <soc/fsl/qe/ucc.h>
#समावेश <soc/fsl/qe/ucc_slow.h>

u32 ucc_slow_get_qe_cr_subblock(पूर्णांक uccs_num)
अणु
	चयन (uccs_num) अणु
	हाल 0: वापस QE_CR_SUBBLOCK_UCCSLOW1;
	हाल 1: वापस QE_CR_SUBBLOCK_UCCSLOW2;
	हाल 2: वापस QE_CR_SUBBLOCK_UCCSLOW3;
	हाल 3: वापस QE_CR_SUBBLOCK_UCCSLOW4;
	हाल 4: वापस QE_CR_SUBBLOCK_UCCSLOW5;
	हाल 5: वापस QE_CR_SUBBLOCK_UCCSLOW6;
	हाल 6: वापस QE_CR_SUBBLOCK_UCCSLOW7;
	हाल 7: वापस QE_CR_SUBBLOCK_UCCSLOW8;
	शेष: वापस QE_CR_SUBBLOCK_INVALID;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ucc_slow_get_qe_cr_subblock);

व्योम ucc_slow_graceful_stop_tx(काष्ठा ucc_slow_निजी * uccs)
अणु
	काष्ठा ucc_slow_info *us_info = uccs->us_info;
	u32 id;

	id = ucc_slow_get_qe_cr_subblock(us_info->ucc_num);
	qe_issue_cmd(QE_GRACEFUL_STOP_TX, id,
			 QE_CR_PROTOCOL_UNSPECIFIED, 0);
पूर्ण
EXPORT_SYMBOL(ucc_slow_graceful_stop_tx);

व्योम ucc_slow_stop_tx(काष्ठा ucc_slow_निजी * uccs)
अणु
	काष्ठा ucc_slow_info *us_info = uccs->us_info;
	u32 id;

	id = ucc_slow_get_qe_cr_subblock(us_info->ucc_num);
	qe_issue_cmd(QE_STOP_TX, id, QE_CR_PROTOCOL_UNSPECIFIED, 0);
पूर्ण
EXPORT_SYMBOL(ucc_slow_stop_tx);

व्योम ucc_slow_restart_tx(काष्ठा ucc_slow_निजी * uccs)
अणु
	काष्ठा ucc_slow_info *us_info = uccs->us_info;
	u32 id;

	id = ucc_slow_get_qe_cr_subblock(us_info->ucc_num);
	qe_issue_cmd(QE_RESTART_TX, id, QE_CR_PROTOCOL_UNSPECIFIED, 0);
पूर्ण
EXPORT_SYMBOL(ucc_slow_restart_tx);

व्योम ucc_slow_enable(काष्ठा ucc_slow_निजी * uccs, क्रमागत comm_dir mode)
अणु
	काष्ठा ucc_slow __iomem *us_regs;
	u32 gumr_l;

	us_regs = uccs->us_regs;

	/* Enable reception and/or transmission on this UCC. */
	gumr_l = ioपढ़ो32be(&us_regs->gumr_l);
	अगर (mode & COMM_सूची_TX) अणु
		gumr_l |= UCC_SLOW_GUMR_L_ENT;
		uccs->enabled_tx = 1;
	पूर्ण
	अगर (mode & COMM_सूची_RX) अणु
		gumr_l |= UCC_SLOW_GUMR_L_ENR;
		uccs->enabled_rx = 1;
	पूर्ण
	ioग_लिखो32be(gumr_l, &us_regs->gumr_l);
पूर्ण
EXPORT_SYMBOL(ucc_slow_enable);

व्योम ucc_slow_disable(काष्ठा ucc_slow_निजी * uccs, क्रमागत comm_dir mode)
अणु
	काष्ठा ucc_slow __iomem *us_regs;
	u32 gumr_l;

	us_regs = uccs->us_regs;

	/* Disable reception and/or transmission on this UCC. */
	gumr_l = ioपढ़ो32be(&us_regs->gumr_l);
	अगर (mode & COMM_सूची_TX) अणु
		gumr_l &= ~UCC_SLOW_GUMR_L_ENT;
		uccs->enabled_tx = 0;
	पूर्ण
	अगर (mode & COMM_सूची_RX) अणु
		gumr_l &= ~UCC_SLOW_GUMR_L_ENR;
		uccs->enabled_rx = 0;
	पूर्ण
	ioग_लिखो32be(gumr_l, &us_regs->gumr_l);
पूर्ण
EXPORT_SYMBOL(ucc_slow_disable);

/* Initialize the UCC क्रम Slow operations
 *
 * The caller should initialize the following us_info
 */
पूर्णांक ucc_slow_init(काष्ठा ucc_slow_info * us_info, काष्ठा ucc_slow_निजी ** uccs_ret)
अणु
	काष्ठा ucc_slow_निजी *uccs;
	u32 i;
	काष्ठा ucc_slow __iomem *us_regs;
	u32 gumr;
	काष्ठा qe_bd __iomem *bd;
	u32 id;
	u32 command;
	पूर्णांक ret = 0;

	अगर (!us_info)
		वापस -EINVAL;

	/* check अगर the UCC port number is in range. */
	अगर ((us_info->ucc_num < 0) || (us_info->ucc_num > UCC_MAX_NUM - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: illegal UCC number\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set mrblr
	 * Check that 'max_rx_buf_length' is properly aligned (4), unless
	 * rfw is 1, meaning that QE accepts one byte at a समय, unlike normal
	 * हाल when QE accepts 32 bits at a समय.
	 */
	अगर ((!us_info->rfw) &&
		(us_info->max_rx_buf_length & (UCC_SLOW_MRBLR_ALIGNMENT - 1))) अणु
		prपूर्णांकk(KERN_ERR "max_rx_buf_length not aligned.\n");
		वापस -EINVAL;
	पूर्ण

	uccs = kzalloc(माप(काष्ठा ucc_slow_निजी), GFP_KERNEL);
	अगर (!uccs) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot allocate private data\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	uccs->rx_base_offset = -1;
	uccs->tx_base_offset = -1;
	uccs->us_pram_offset = -1;

	/* Fill slow UCC काष्ठाure */
	uccs->us_info = us_info;
	/* Set the PHY base address */
	uccs->us_regs = ioremap(us_info->regs, माप(काष्ठा ucc_slow));
	अगर (uccs->us_regs == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot map UCC registers\n", __func__);
		kमुक्त(uccs);
		वापस -ENOMEM;
	पूर्ण

	us_regs = uccs->us_regs;
	uccs->p_ucce = &us_regs->ucce;
	uccs->p_uccm = &us_regs->uccm;

	/* Get PRAM base */
	uccs->us_pram_offset =
		qe_muram_alloc(UCC_SLOW_PRAM_SIZE, ALIGNMENT_OF_UCC_SLOW_PRAM);
	अगर (uccs->us_pram_offset < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot allocate MURAM for PRAM", __func__);
		ucc_slow_मुक्त(uccs);
		वापस -ENOMEM;
	पूर्ण
	id = ucc_slow_get_qe_cr_subblock(us_info->ucc_num);
	qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, id, us_info->protocol,
		     uccs->us_pram_offset);

	uccs->us_pram = qe_muram_addr(uccs->us_pram_offset);

	/* Set UCC to slow type */
	ret = ucc_set_type(us_info->ucc_num, UCC_SPEED_TYPE_SLOW);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot set UCC type", __func__);
		ucc_slow_मुक्त(uccs);
		वापस ret;
	पूर्ण

	ioग_लिखो16be(us_info->max_rx_buf_length, &uccs->us_pram->mrblr);

	INIT_LIST_HEAD(&uccs->confQ);

	/* Allocate BDs. */
	uccs->rx_base_offset =
		qe_muram_alloc(us_info->rx_bd_ring_len * माप(काष्ठा qe_bd),
				QE_ALIGNMENT_OF_BD);
	अगर (uccs->rx_base_offset < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot allocate %u RX BDs\n", __func__,
			us_info->rx_bd_ring_len);
		ucc_slow_मुक्त(uccs);
		वापस -ENOMEM;
	पूर्ण

	uccs->tx_base_offset =
		qe_muram_alloc(us_info->tx_bd_ring_len * माप(काष्ठा qe_bd),
			QE_ALIGNMENT_OF_BD);
	अगर (uccs->tx_base_offset < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot allocate TX BDs", __func__);
		ucc_slow_मुक्त(uccs);
		वापस -ENOMEM;
	पूर्ण

	/* Init Tx bds */
	bd = uccs->confBd = uccs->tx_bd = qe_muram_addr(uccs->tx_base_offset);
	क्रम (i = 0; i < us_info->tx_bd_ring_len - 1; i++) अणु
		/* clear bd buffer */
		ioग_लिखो32be(0, &bd->buf);
		/* set bd status and length */
		ioग_लिखो32be(0, (u32 __iomem *)bd);
		bd++;
	पूर्ण
	/* क्रम last BD set Wrap bit */
	ioग_लिखो32be(0, &bd->buf);
	ioग_लिखो32be(T_W, (u32 __iomem *)bd);

	/* Init Rx bds */
	bd = uccs->rx_bd = qe_muram_addr(uccs->rx_base_offset);
	क्रम (i = 0; i < us_info->rx_bd_ring_len - 1; i++) अणु
		/* set bd status and length */
		ioग_लिखो32be(0, (u32 __iomem *)bd);
		/* clear bd buffer */
		ioग_लिखो32be(0, &bd->buf);
		bd++;
	पूर्ण
	/* क्रम last BD set Wrap bit */
	ioग_लिखो32be(R_W, (u32 __iomem *)bd);
	ioग_लिखो32be(0, &bd->buf);

	/* Set GUMR (For more details see the hardware spec.). */
	/* gumr_h */
	gumr = us_info->tcrc;
	अगर (us_info->cdp)
		gumr |= UCC_SLOW_GUMR_H_CDP;
	अगर (us_info->ctsp)
		gumr |= UCC_SLOW_GUMR_H_CTSP;
	अगर (us_info->cds)
		gumr |= UCC_SLOW_GUMR_H_CDS;
	अगर (us_info->ctss)
		gumr |= UCC_SLOW_GUMR_H_CTSS;
	अगर (us_info->tfl)
		gumr |= UCC_SLOW_GUMR_H_TFL;
	अगर (us_info->rfw)
		gumr |= UCC_SLOW_GUMR_H_RFW;
	अगर (us_info->txsy)
		gumr |= UCC_SLOW_GUMR_H_TXSY;
	अगर (us_info->rtsm)
		gumr |= UCC_SLOW_GUMR_H_RTSM;
	ioग_लिखो32be(gumr, &us_regs->gumr_h);

	/* gumr_l */
	gumr = (u32)us_info->tdcr | (u32)us_info->rdcr | (u32)us_info->tenc |
	       (u32)us_info->renc | (u32)us_info->diag | (u32)us_info->mode;
	अगर (us_info->tci)
		gumr |= UCC_SLOW_GUMR_L_TCI;
	अगर (us_info->rinv)
		gumr |= UCC_SLOW_GUMR_L_RINV;
	अगर (us_info->tinv)
		gumr |= UCC_SLOW_GUMR_L_TINV;
	अगर (us_info->tend)
		gumr |= UCC_SLOW_GUMR_L_TEND;
	ioग_लिखो32be(gumr, &us_regs->gumr_l);

	/* Function code रेजिस्टरs */

	/* अगर the data is in cachable memory, the 'global' */
	/* in the function code should be set. */
	ioग_लिखो8(UCC_BMR_BO_BE, &uccs->us_pram->tbmr);
	ioग_लिखो8(UCC_BMR_BO_BE, &uccs->us_pram->rbmr);

	/* rbase, tbase are offsets from MURAM base */
	ioग_लिखो16be(uccs->rx_base_offset, &uccs->us_pram->rbase);
	ioग_लिखो16be(uccs->tx_base_offset, &uccs->us_pram->tbase);

	/* Mux घड़ीing */
	/* Grant Support */
	ucc_set_qe_mux_grant(us_info->ucc_num, us_info->grant_support);
	/* Breakpoपूर्णांक Support */
	ucc_set_qe_mux_bkpt(us_info->ucc_num, us_info->brkpt_support);
	/* Set Tsa or NMSI mode. */
	ucc_set_qe_mux_tsa(us_info->ucc_num, us_info->tsa);
	/* If NMSI (not Tsa), set Tx and Rx घड़ी. */
	अगर (!us_info->tsa) अणु
		/* Rx घड़ी routing */
		अगर (ucc_set_qe_mux_rxtx(us_info->ucc_num, us_info->rx_घड़ी,
					COMM_सूची_RX)) अणु
			prपूर्णांकk(KERN_ERR "%s: illegal value for RX clock\n",
			       __func__);
			ucc_slow_मुक्त(uccs);
			वापस -EINVAL;
		पूर्ण
		/* Tx घड़ी routing */
		अगर (ucc_set_qe_mux_rxtx(us_info->ucc_num, us_info->tx_घड़ी,
					COMM_सूची_TX)) अणु
			prपूर्णांकk(KERN_ERR "%s: illegal value for TX clock\n",
			       __func__);
			ucc_slow_मुक्त(uccs);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Set पूर्णांकerrupt mask रेजिस्टर at UCC level. */
	ioग_लिखो16be(us_info->uccm_mask, &us_regs->uccm);

	/* First, clear anything pending at UCC level,
	 * otherwise, old garbage may come through
	 * as soon as the dam is खोलोed. */

	/* Writing '1' clears */
	ioग_लिखो16be(0xffff, &us_regs->ucce);

	/* Issue QE Init command */
	अगर (us_info->init_tx && us_info->init_rx)
		command = QE_INIT_TX_RX;
	अन्यथा अगर (us_info->init_tx)
		command = QE_INIT_TX;
	अन्यथा
		command = QE_INIT_RX;	/* We know at least one is TRUE */

	qe_issue_cmd(command, id, us_info->protocol, 0);

	*uccs_ret = uccs;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ucc_slow_init);

व्योम ucc_slow_मुक्त(काष्ठा ucc_slow_निजी * uccs)
अणु
	अगर (!uccs)
		वापस;

	qe_muram_मुक्त(uccs->rx_base_offset);
	qe_muram_मुक्त(uccs->tx_base_offset);
	qe_muram_मुक्त(uccs->us_pram_offset);

	अगर (uccs->us_regs)
		iounmap(uccs->us_regs);

	kमुक्त(uccs);
पूर्ण
EXPORT_SYMBOL(ucc_slow_मुक्त);

