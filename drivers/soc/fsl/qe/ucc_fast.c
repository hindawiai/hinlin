<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 *
 * Description:
 * QE UCC Fast API Set - UCC Fast specअगरic routines implementations.
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
#समावेश <soc/fsl/qe/ucc_fast.h>

व्योम ucc_fast_dump_regs(काष्ठा ucc_fast_निजी * uccf)
अणु
	prपूर्णांकk(KERN_INFO "UCC%u Fast registers:\n", uccf->uf_info->ucc_num);
	prपूर्णांकk(KERN_INFO "Base address: 0x%p\n", uccf->uf_regs);

	prपूर्णांकk(KERN_INFO "gumr  : addr=0x%p, val=0x%08x\n",
		  &uccf->uf_regs->gumr, ioपढ़ो32be(&uccf->uf_regs->gumr));
	prपूर्णांकk(KERN_INFO "upsmr : addr=0x%p, val=0x%08x\n",
		  &uccf->uf_regs->upsmr, ioपढ़ो32be(&uccf->uf_regs->upsmr));
	prपूर्णांकk(KERN_INFO "utodr : addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->utodr, ioपढ़ो16be(&uccf->uf_regs->utodr));
	prपूर्णांकk(KERN_INFO "udsr  : addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->udsr, ioपढ़ो16be(&uccf->uf_regs->udsr));
	prपूर्णांकk(KERN_INFO "ucce  : addr=0x%p, val=0x%08x\n",
		  &uccf->uf_regs->ucce, ioपढ़ो32be(&uccf->uf_regs->ucce));
	prपूर्णांकk(KERN_INFO "uccm  : addr=0x%p, val=0x%08x\n",
		  &uccf->uf_regs->uccm, ioपढ़ो32be(&uccf->uf_regs->uccm));
	prपूर्णांकk(KERN_INFO "uccs  : addr=0x%p, val=0x%02x\n",
		  &uccf->uf_regs->uccs, ioपढ़ो8(&uccf->uf_regs->uccs));
	prपूर्णांकk(KERN_INFO "urfb  : addr=0x%p, val=0x%08x\n",
		  &uccf->uf_regs->urfb, ioपढ़ो32be(&uccf->uf_regs->urfb));
	prपूर्णांकk(KERN_INFO "urfs  : addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->urfs, ioपढ़ो16be(&uccf->uf_regs->urfs));
	prपूर्णांकk(KERN_INFO "urfet : addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->urfet, ioपढ़ो16be(&uccf->uf_regs->urfet));
	prपूर्णांकk(KERN_INFO "urfset: addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->urfset,
		  ioपढ़ो16be(&uccf->uf_regs->urfset));
	prपूर्णांकk(KERN_INFO "utfb  : addr=0x%p, val=0x%08x\n",
		  &uccf->uf_regs->utfb, ioपढ़ो32be(&uccf->uf_regs->utfb));
	prपूर्णांकk(KERN_INFO "utfs  : addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->utfs, ioपढ़ो16be(&uccf->uf_regs->utfs));
	prपूर्णांकk(KERN_INFO "utfet : addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->utfet, ioपढ़ो16be(&uccf->uf_regs->utfet));
	prपूर्णांकk(KERN_INFO "utftt : addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->utftt, ioपढ़ो16be(&uccf->uf_regs->utftt));
	prपूर्णांकk(KERN_INFO "utpt  : addr=0x%p, val=0x%04x\n",
		  &uccf->uf_regs->utpt, ioपढ़ो16be(&uccf->uf_regs->utpt));
	prपूर्णांकk(KERN_INFO "urtry : addr=0x%p, val=0x%08x\n",
		  &uccf->uf_regs->urtry, ioपढ़ो32be(&uccf->uf_regs->urtry));
	prपूर्णांकk(KERN_INFO "guemr : addr=0x%p, val=0x%02x\n",
		  &uccf->uf_regs->guemr, ioपढ़ो8(&uccf->uf_regs->guemr));
पूर्ण
EXPORT_SYMBOL(ucc_fast_dump_regs);

u32 ucc_fast_get_qe_cr_subblock(पूर्णांक uccf_num)
अणु
	चयन (uccf_num) अणु
	हाल 0: वापस QE_CR_SUBBLOCK_UCCFAST1;
	हाल 1: वापस QE_CR_SUBBLOCK_UCCFAST2;
	हाल 2: वापस QE_CR_SUBBLOCK_UCCFAST3;
	हाल 3: वापस QE_CR_SUBBLOCK_UCCFAST4;
	हाल 4: वापस QE_CR_SUBBLOCK_UCCFAST5;
	हाल 5: वापस QE_CR_SUBBLOCK_UCCFAST6;
	हाल 6: वापस QE_CR_SUBBLOCK_UCCFAST7;
	हाल 7: वापस QE_CR_SUBBLOCK_UCCFAST8;
	शेष: वापस QE_CR_SUBBLOCK_INVALID;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ucc_fast_get_qe_cr_subblock);

व्योम ucc_fast_transmit_on_demand(काष्ठा ucc_fast_निजी * uccf)
अणु
	ioग_लिखो16be(UCC_FAST_TOD, &uccf->uf_regs->utodr);
पूर्ण
EXPORT_SYMBOL(ucc_fast_transmit_on_demand);

व्योम ucc_fast_enable(काष्ठा ucc_fast_निजी * uccf, क्रमागत comm_dir mode)
अणु
	काष्ठा ucc_fast __iomem *uf_regs;
	u32 gumr;

	uf_regs = uccf->uf_regs;

	/* Enable reception and/or transmission on this UCC. */
	gumr = ioपढ़ो32be(&uf_regs->gumr);
	अगर (mode & COMM_सूची_TX) अणु
		gumr |= UCC_FAST_GUMR_ENT;
		uccf->enabled_tx = 1;
	पूर्ण
	अगर (mode & COMM_सूची_RX) अणु
		gumr |= UCC_FAST_GUMR_ENR;
		uccf->enabled_rx = 1;
	पूर्ण
	ioग_लिखो32be(gumr, &uf_regs->gumr);
पूर्ण
EXPORT_SYMBOL(ucc_fast_enable);

व्योम ucc_fast_disable(काष्ठा ucc_fast_निजी * uccf, क्रमागत comm_dir mode)
अणु
	काष्ठा ucc_fast __iomem *uf_regs;
	u32 gumr;

	uf_regs = uccf->uf_regs;

	/* Disable reception and/or transmission on this UCC. */
	gumr = ioपढ़ो32be(&uf_regs->gumr);
	अगर (mode & COMM_सूची_TX) अणु
		gumr &= ~UCC_FAST_GUMR_ENT;
		uccf->enabled_tx = 0;
	पूर्ण
	अगर (mode & COMM_सूची_RX) अणु
		gumr &= ~UCC_FAST_GUMR_ENR;
		uccf->enabled_rx = 0;
	पूर्ण
	ioग_लिखो32be(gumr, &uf_regs->gumr);
पूर्ण
EXPORT_SYMBOL(ucc_fast_disable);

पूर्णांक ucc_fast_init(काष्ठा ucc_fast_info * uf_info, काष्ठा ucc_fast_निजी ** uccf_ret)
अणु
	काष्ठा ucc_fast_निजी *uccf;
	काष्ठा ucc_fast __iomem *uf_regs;
	u32 gumr;
	पूर्णांक ret;

	अगर (!uf_info)
		वापस -EINVAL;

	/* check अगर the UCC port number is in range. */
	अगर ((uf_info->ucc_num < 0) || (uf_info->ucc_num > UCC_MAX_NUM - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: illegal UCC number\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Check that 'max_rx_buf_length' is properly aligned (4). */
	अगर (uf_info->max_rx_buf_length & (UCC_FAST_MRBLR_ALIGNMENT - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: max_rx_buf_length not aligned\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	/* Validate Virtual Fअगरo रेजिस्टर values */
	अगर (uf_info->urfs < UCC_FAST_URFS_MIN_VAL) अणु
		prपूर्णांकk(KERN_ERR "%s: urfs is too small\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (uf_info->urfs & (UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: urfs is not aligned\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (uf_info->urfet & (UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: urfet is not aligned.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (uf_info->urfset & (UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: urfset is not aligned\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (uf_info->utfs & (UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: utfs is not aligned\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (uf_info->utfet & (UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: utfet is not aligned\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (uf_info->utftt & (UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: utftt is not aligned\n", __func__);
		वापस -EINVAL;
	पूर्ण

	uccf = kzalloc(माप(काष्ठा ucc_fast_निजी), GFP_KERNEL);
	अगर (!uccf) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot allocate private data\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	uccf->ucc_fast_tx_भव_fअगरo_base_offset = -1;
	uccf->ucc_fast_rx_भव_fअगरo_base_offset = -1;

	/* Fill fast UCC काष्ठाure */
	uccf->uf_info = uf_info;
	/* Set the PHY base address */
	uccf->uf_regs = ioremap(uf_info->regs, माप(काष्ठा ucc_fast));
	अगर (uccf->uf_regs == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot map UCC registers\n", __func__);
		kमुक्त(uccf);
		वापस -ENOMEM;
	पूर्ण

	uccf->enabled_tx = 0;
	uccf->enabled_rx = 0;
	uccf->stopped_tx = 0;
	uccf->stopped_rx = 0;
	uf_regs = uccf->uf_regs;
	uccf->p_ucce = &uf_regs->ucce;
	uccf->p_uccm = &uf_regs->uccm;
#अगर_घोषित CONFIG_UGETH_TX_ON_DEMAND
	uccf->p_utodr = &uf_regs->utodr;
#पूर्ण_अगर
#अगर_घोषित STATISTICS
	uccf->tx_frames = 0;
	uccf->rx_frames = 0;
	uccf->rx_discarded = 0;
#पूर्ण_अगर				/* STATISTICS */

	/* Set UCC to fast type */
	ret = ucc_set_type(uf_info->ucc_num, UCC_SPEED_TYPE_FAST);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot set UCC type\n", __func__);
		ucc_fast_मुक्त(uccf);
		वापस ret;
	पूर्ण

	uccf->mrblr = uf_info->max_rx_buf_length;

	/* Set GUMR */
	/* For more details see the hardware spec. */
	gumr = uf_info->ttx_trx;
	अगर (uf_info->tci)
		gumr |= UCC_FAST_GUMR_TCI;
	अगर (uf_info->cdp)
		gumr |= UCC_FAST_GUMR_CDP;
	अगर (uf_info->ctsp)
		gumr |= UCC_FAST_GUMR_CTSP;
	अगर (uf_info->cds)
		gumr |= UCC_FAST_GUMR_CDS;
	अगर (uf_info->ctss)
		gumr |= UCC_FAST_GUMR_CTSS;
	अगर (uf_info->txsy)
		gumr |= UCC_FAST_GUMR_TXSY;
	अगर (uf_info->rsyn)
		gumr |= UCC_FAST_GUMR_RSYN;
	gumr |= uf_info->synl;
	अगर (uf_info->rtsm)
		gumr |= UCC_FAST_GUMR_RTSM;
	gumr |= uf_info->renc;
	अगर (uf_info->revd)
		gumr |= UCC_FAST_GUMR_REVD;
	gumr |= uf_info->tenc;
	gumr |= uf_info->tcrc;
	gumr |= uf_info->mode;
	ioग_लिखो32be(gumr, &uf_regs->gumr);

	/* Allocate memory क्रम Tx Virtual Fअगरo */
	uccf->ucc_fast_tx_भव_fअगरo_base_offset =
	    qe_muram_alloc(uf_info->utfs, UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT);
	अगर (uccf->ucc_fast_tx_भव_fअगरo_base_offset < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot allocate MURAM for TX FIFO\n",
			__func__);
		ucc_fast_मुक्त(uccf);
		वापस -ENOMEM;
	पूर्ण

	/* Allocate memory क्रम Rx Virtual Fअगरo */
	uccf->ucc_fast_rx_भव_fअगरo_base_offset =
		qe_muram_alloc(uf_info->urfs +
			   UCC_FAST_RECEIVE_VIRTUAL_FIFO_SIZE_FUDGE_FACTOR,
			   UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT);
	अगर (uccf->ucc_fast_rx_भव_fअगरo_base_offset < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot allocate MURAM for RX FIFO\n",
			__func__);
		ucc_fast_मुक्त(uccf);
		वापस -ENOMEM;
	पूर्ण

	/* Set Virtual Fअगरo रेजिस्टरs */
	ioग_लिखो16be(uf_info->urfs, &uf_regs->urfs);
	ioग_लिखो16be(uf_info->urfet, &uf_regs->urfet);
	ioग_लिखो16be(uf_info->urfset, &uf_regs->urfset);
	ioग_लिखो16be(uf_info->utfs, &uf_regs->utfs);
	ioग_लिखो16be(uf_info->utfet, &uf_regs->utfet);
	ioग_लिखो16be(uf_info->utftt, &uf_regs->utftt);
	/* utfb, urfb are offsets from MURAM base */
	ioग_लिखो32be(uccf->ucc_fast_tx_भव_fअगरo_base_offset,
		       &uf_regs->utfb);
	ioग_लिखो32be(uccf->ucc_fast_rx_भव_fअगरo_base_offset,
		       &uf_regs->urfb);

	/* Mux घड़ीing */
	/* Grant Support */
	ucc_set_qe_mux_grant(uf_info->ucc_num, uf_info->grant_support);
	/* Breakpoपूर्णांक Support */
	ucc_set_qe_mux_bkpt(uf_info->ucc_num, uf_info->brkpt_support);
	/* Set Tsa or NMSI mode. */
	ucc_set_qe_mux_tsa(uf_info->ucc_num, uf_info->tsa);
	/* If NMSI (not Tsa), set Tx and Rx घड़ी. */
	अगर (!uf_info->tsa) अणु
		/* Rx घड़ी routing */
		अगर ((uf_info->rx_घड़ी != QE_CLK_NONE) &&
		    ucc_set_qe_mux_rxtx(uf_info->ucc_num, uf_info->rx_घड़ी,
					COMM_सूची_RX)) अणु
			prपूर्णांकk(KERN_ERR "%s: illegal value for RX clock\n",
			       __func__);
			ucc_fast_मुक्त(uccf);
			वापस -EINVAL;
		पूर्ण
		/* Tx घड़ी routing */
		अगर ((uf_info->tx_घड़ी != QE_CLK_NONE) &&
		    ucc_set_qe_mux_rxtx(uf_info->ucc_num, uf_info->tx_घड़ी,
					COMM_सूची_TX)) अणु
			prपूर्णांकk(KERN_ERR "%s: illegal value for TX clock\n",
			       __func__);
			ucc_fast_मुक्त(uccf);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* tdm Rx घड़ी routing */
		अगर ((uf_info->rx_घड़ी != QE_CLK_NONE) &&
		    ucc_set_tdm_rxtx_clk(uf_info->tdm_num, uf_info->rx_घड़ी,
					 COMM_सूची_RX)) अणु
			pr_err("%s: illegal value for RX clock", __func__);
			ucc_fast_मुक्त(uccf);
			वापस -EINVAL;
		पूर्ण

		/* tdm Tx घड़ी routing */
		अगर ((uf_info->tx_घड़ी != QE_CLK_NONE) &&
		    ucc_set_tdm_rxtx_clk(uf_info->tdm_num, uf_info->tx_घड़ी,
					 COMM_सूची_TX)) अणु
			pr_err("%s: illegal value for TX clock", __func__);
			ucc_fast_मुक्त(uccf);
			वापस -EINVAL;
		पूर्ण

		/* tdm Rx sync घड़ी routing */
		अगर ((uf_info->rx_sync != QE_CLK_NONE) &&
		    ucc_set_tdm_rxtx_sync(uf_info->tdm_num, uf_info->rx_sync,
					  COMM_सूची_RX)) अणु
			pr_err("%s: illegal value for RX clock", __func__);
			ucc_fast_मुक्त(uccf);
			वापस -EINVAL;
		पूर्ण

		/* tdm Tx sync घड़ी routing */
		अगर ((uf_info->tx_sync != QE_CLK_NONE) &&
		    ucc_set_tdm_rxtx_sync(uf_info->tdm_num, uf_info->tx_sync,
					  COMM_सूची_TX)) अणु
			pr_err("%s: illegal value for TX clock", __func__);
			ucc_fast_मुक्त(uccf);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Set पूर्णांकerrupt mask रेजिस्टर at UCC level. */
	ioग_लिखो32be(uf_info->uccm_mask, &uf_regs->uccm);

	/* First, clear anything pending at UCC level,
	 * otherwise, old garbage may come through
	 * as soon as the dam is खोलोed. */

	/* Writing '1' clears */
	ioग_लिखो32be(0xffffffff, &uf_regs->ucce);

	*uccf_ret = uccf;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ucc_fast_init);

व्योम ucc_fast_मुक्त(काष्ठा ucc_fast_निजी * uccf)
अणु
	अगर (!uccf)
		वापस;

	qe_muram_मुक्त(uccf->ucc_fast_tx_भव_fअगरo_base_offset);
	qe_muram_मुक्त(uccf->ucc_fast_rx_भव_fअगरo_base_offset);

	अगर (uccf->uf_regs)
		iounmap(uccf->uf_regs);

	kमुक्त(uccf);
पूर्ण
EXPORT_SYMBOL(ucc_fast_मुक्त);
