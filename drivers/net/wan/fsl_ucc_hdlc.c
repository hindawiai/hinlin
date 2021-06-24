<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Freescale QUICC Engine HDLC Device Driver
 *
 * Copyright 2016 Freescale Semiconductor Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <soc/fsl/qe/qe_tdm.h>
#समावेश <uapi/linux/अगर_arp.h>

#समावेश "fsl_ucc_hdlc.h"

#घोषणा DRV_DESC "Freescale QE UCC HDLC Driver"
#घोषणा DRV_NAME "ucc_hdlc"

#घोषणा TDM_PPPOHT_SLIC_MAXIN
#घोषणा RX_BD_ERRORS (R_CD_S | R_OV_S | R_CR_S | R_AB_S | R_NO_S | R_LG_S)

अटल काष्ठा ucc_tdm_info utdm_primary_info = अणु
	.uf_info = अणु
		.tsa = 0,
		.cdp = 0,
		.cds = 1,
		.ctsp = 1,
		.ctss = 1,
		.revd = 0,
		.urfs = 256,
		.utfs = 256,
		.urfet = 128,
		.urfset = 192,
		.utfet = 128,
		.utftt = 0x40,
		.ufpt = 256,
		.mode = UCC_FAST_PROTOCOL_MODE_HDLC,
		.ttx_trx = UCC_FAST_GUMR_TRANSPARENT_TTX_TRX_NORMAL,
		.tenc = UCC_FAST_TX_ENCODING_NRZ,
		.renc = UCC_FAST_RX_ENCODING_NRZ,
		.tcrc = UCC_FAST_16_BIT_CRC,
		.synl = UCC_FAST_SYNC_LEN_NOT_USED,
	पूर्ण,

	.si_info = अणु
#अगर_घोषित TDM_PPPOHT_SLIC_MAXIN
		.simr_rfsd = 1,
		.simr_tfsd = 2,
#अन्यथा
		.simr_rfsd = 0,
		.simr_tfsd = 0,
#पूर्ण_अगर
		.simr_crt = 0,
		.simr_sl = 0,
		.simr_ce = 1,
		.simr_fe = 1,
		.simr_gm = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा ucc_tdm_info utdm_info[UCC_MAX_NUM];

अटल पूर्णांक uhdlc_init(काष्ठा ucc_hdlc_निजी *priv)
अणु
	काष्ठा ucc_tdm_info *ut_info;
	काष्ठा ucc_fast_info *uf_info;
	u32 cecr_subblock;
	u16 bd_status;
	पूर्णांक ret, i;
	व्योम *bd_buffer;
	dma_addr_t bd_dma_addr;
	s32 riptr;
	s32 tiptr;
	u32 gumr;

	ut_info = priv->ut_info;
	uf_info = &ut_info->uf_info;

	अगर (priv->tsa) अणु
		uf_info->tsa = 1;
		uf_info->ctsp = 1;
		uf_info->cds = 1;
		uf_info->ctss = 1;
	पूर्ण अन्यथा अणु
		uf_info->cds = 0;
		uf_info->ctsp = 0;
		uf_info->ctss = 0;
	पूर्ण

	/* This sets HPM रेजिस्टर in CMXUCR रेजिस्टर which configures a
	 * खोलो drain connected HDLC bus
	 */
	अगर (priv->hdlc_bus)
		uf_info->brkpt_support = 1;

	uf_info->uccm_mask = ((UCC_HDLC_UCCE_RXB | UCC_HDLC_UCCE_RXF |
				UCC_HDLC_UCCE_TXB) << 16);

	ret = ucc_fast_init(uf_info, &priv->uccf);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to init uccf.");
		वापस ret;
	पूर्ण

	priv->uf_regs = priv->uccf->uf_regs;
	ucc_fast_disable(priv->uccf, COMM_सूची_RX | COMM_सूची_TX);

	/* Loopback mode */
	अगर (priv->loopback) अणु
		dev_info(priv->dev, "Loopback Mode\n");
		/* use the same घड़ी when work in loopback */
		qe_setbrg(ut_info->uf_info.rx_घड़ी, 20000000, 1);

		gumr = ioपढ़ो32be(&priv->uf_regs->gumr);
		gumr |= (UCC_FAST_GUMR_LOOPBACK | UCC_FAST_GUMR_CDS |
			 UCC_FAST_GUMR_TCI);
		gumr &= ~(UCC_FAST_GUMR_CTSP | UCC_FAST_GUMR_RSYN);
		ioग_लिखो32be(gumr, &priv->uf_regs->gumr);
	पूर्ण

	/* Initialize SI */
	अगर (priv->tsa)
		ucc_tdm_init(priv->utdm, priv->ut_info);

	/* Write to QE CECR, UCCx channel to Stop Transmission */
	cecr_subblock = ucc_fast_get_qe_cr_subblock(uf_info->ucc_num);
	ret = qe_issue_cmd(QE_STOP_TX, cecr_subblock,
			   QE_CR_PROTOCOL_UNSPECIFIED, 0);

	/* Set UPSMR normal mode (need fixed)*/
	ioग_लिखो32be(0, &priv->uf_regs->upsmr);

	/* hdlc_bus mode */
	अगर (priv->hdlc_bus) अणु
		u32 upsmr;

		dev_info(priv->dev, "HDLC bus Mode\n");
		upsmr = ioपढ़ो32be(&priv->uf_regs->upsmr);

		/* bus mode and retransmit enable, with collision winकरोw
		 * set to 8 bytes
		 */
		upsmr |= UCC_HDLC_UPSMR_RTE | UCC_HDLC_UPSMR_BUS |
				UCC_HDLC_UPSMR_CW8;
		ioग_लिखो32be(upsmr, &priv->uf_regs->upsmr);

		/* explicitly disable CDS & CTSP */
		gumr = ioपढ़ो32be(&priv->uf_regs->gumr);
		gumr &= ~(UCC_FAST_GUMR_CDS | UCC_FAST_GUMR_CTSP);
		/* set स्वतःmatic sync to explicitly ignore CD संकेत */
		gumr |= UCC_FAST_GUMR_SYNL_AUTO;
		ioग_लिखो32be(gumr, &priv->uf_regs->gumr);
	पूर्ण

	priv->rx_ring_size = RX_BD_RING_LEN;
	priv->tx_ring_size = TX_BD_RING_LEN;
	/* Alloc Rx BD */
	priv->rx_bd_base = dma_alloc_coherent(priv->dev,
			RX_BD_RING_LEN * माप(काष्ठा qe_bd),
			&priv->dma_rx_bd, GFP_KERNEL);

	अगर (!priv->rx_bd_base) अणु
		dev_err(priv->dev, "Cannot allocate MURAM memory for RxBDs\n");
		ret = -ENOMEM;
		जाओ मुक्त_uccf;
	पूर्ण

	/* Alloc Tx BD */
	priv->tx_bd_base = dma_alloc_coherent(priv->dev,
			TX_BD_RING_LEN * माप(काष्ठा qe_bd),
			&priv->dma_tx_bd, GFP_KERNEL);

	अगर (!priv->tx_bd_base) अणु
		dev_err(priv->dev, "Cannot allocate MURAM memory for TxBDs\n");
		ret = -ENOMEM;
		जाओ मुक्त_rx_bd;
	पूर्ण

	/* Alloc parameter ram क्रम ucc hdlc */
	priv->ucc_pram_offset = qe_muram_alloc(माप(काष्ठा ucc_hdlc_param),
				ALIGNMENT_OF_UCC_HDLC_PRAM);

	अगर (priv->ucc_pram_offset < 0) अणु
		dev_err(priv->dev, "Can not allocate MURAM for hdlc parameter.\n");
		ret = -ENOMEM;
		जाओ मुक्त_tx_bd;
	पूर्ण

	priv->rx_skbuff = kसुस्मृति(priv->rx_ring_size,
				  माप(*priv->rx_skbuff),
				  GFP_KERNEL);
	अगर (!priv->rx_skbuff) अणु
		ret = -ENOMEM;
		जाओ मुक्त_ucc_pram;
	पूर्ण

	priv->tx_skbuff = kसुस्मृति(priv->tx_ring_size,
				  माप(*priv->tx_skbuff),
				  GFP_KERNEL);
	अगर (!priv->tx_skbuff) अणु
		ret = -ENOMEM;
		जाओ मुक्त_rx_skbuff;
	पूर्ण

	priv->skb_curtx = 0;
	priv->skb_dirtytx = 0;
	priv->curtx_bd = priv->tx_bd_base;
	priv->dirty_tx = priv->tx_bd_base;
	priv->currx_bd = priv->rx_bd_base;
	priv->currx_bdnum = 0;

	/* init parameter base */
	cecr_subblock = ucc_fast_get_qe_cr_subblock(uf_info->ucc_num);
	ret = qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, cecr_subblock,
			   QE_CR_PROTOCOL_UNSPECIFIED, priv->ucc_pram_offset);

	priv->ucc_pram = (काष्ठा ucc_hdlc_param __iomem *)
					qe_muram_addr(priv->ucc_pram_offset);

	/* Zero out parameter ram */
	स_रखो_io(priv->ucc_pram, 0, माप(काष्ठा ucc_hdlc_param));

	/* Alloc riptr, tiptr */
	riptr = qe_muram_alloc(32, 32);
	अगर (riptr < 0) अणु
		dev_err(priv->dev, "Cannot allocate MURAM mem for Receive internal temp data pointer\n");
		ret = -ENOMEM;
		जाओ मुक्त_tx_skbuff;
	पूर्ण

	tiptr = qe_muram_alloc(32, 32);
	अगर (tiptr < 0) अणु
		dev_err(priv->dev, "Cannot allocate MURAM mem for Transmit internal temp data pointer\n");
		ret = -ENOMEM;
		जाओ मुक्त_riptr;
	पूर्ण
	अगर (riptr != (u16)riptr || tiptr != (u16)tiptr) अणु
		dev_err(priv->dev, "MURAM allocation out of addressable range\n");
		ret = -ENOMEM;
		जाओ मुक्त_tiptr;
	पूर्ण

	/* Set RIPTR, TIPTR */
	ioग_लिखो16be(riptr, &priv->ucc_pram->riptr);
	ioग_लिखो16be(tiptr, &priv->ucc_pram->tiptr);

	/* Set MRBLR */
	ioग_लिखो16be(MAX_RX_BUF_LENGTH, &priv->ucc_pram->mrblr);

	/* Set RBASE, TBASE */
	ioग_लिखो32be(priv->dma_rx_bd, &priv->ucc_pram->rbase);
	ioग_लिखो32be(priv->dma_tx_bd, &priv->ucc_pram->tbase);

	/* Set RSTATE, TSTATE */
	ioग_लिखो32be(BMR_GBL | BMR_BIG_ENDIAN, &priv->ucc_pram->rstate);
	ioग_लिखो32be(BMR_GBL | BMR_BIG_ENDIAN, &priv->ucc_pram->tstate);

	/* Set C_MASK, C_PRES क्रम 16bit CRC */
	ioग_लिखो32be(CRC_16BIT_MASK, &priv->ucc_pram->c_mask);
	ioग_लिखो32be(CRC_16BIT_PRES, &priv->ucc_pram->c_pres);

	ioग_लिखो16be(MAX_FRAME_LENGTH, &priv->ucc_pram->mflr);
	ioग_लिखो16be(DEFAULT_RFTHR, &priv->ucc_pram->rfthr);
	ioग_लिखो16be(DEFAULT_RFTHR, &priv->ucc_pram->rfcnt);
	ioग_लिखो16be(priv->hmask, &priv->ucc_pram->hmask);
	ioग_लिखो16be(DEFAULT_HDLC_ADDR, &priv->ucc_pram->haddr1);
	ioग_लिखो16be(DEFAULT_HDLC_ADDR, &priv->ucc_pram->haddr2);
	ioग_लिखो16be(DEFAULT_HDLC_ADDR, &priv->ucc_pram->haddr3);
	ioग_लिखो16be(DEFAULT_HDLC_ADDR, &priv->ucc_pram->haddr4);

	/* Get BD buffer */
	bd_buffer = dma_alloc_coherent(priv->dev,
				       (RX_BD_RING_LEN + TX_BD_RING_LEN) * MAX_RX_BUF_LENGTH,
				       &bd_dma_addr, GFP_KERNEL);

	अगर (!bd_buffer) अणु
		dev_err(priv->dev, "Could not allocate buffer descriptors\n");
		ret = -ENOMEM;
		जाओ मुक्त_tiptr;
	पूर्ण

	priv->rx_buffer = bd_buffer;
	priv->tx_buffer = bd_buffer + RX_BD_RING_LEN * MAX_RX_BUF_LENGTH;

	priv->dma_rx_addr = bd_dma_addr;
	priv->dma_tx_addr = bd_dma_addr + RX_BD_RING_LEN * MAX_RX_BUF_LENGTH;

	क्रम (i = 0; i < RX_BD_RING_LEN; i++) अणु
		अगर (i < (RX_BD_RING_LEN - 1))
			bd_status = R_E_S | R_I_S;
		अन्यथा
			bd_status = R_E_S | R_I_S | R_W_S;

		ioग_लिखो16be(bd_status, &priv->rx_bd_base[i].status);
		ioग_लिखो32be(priv->dma_rx_addr + i * MAX_RX_BUF_LENGTH,
			    &priv->rx_bd_base[i].buf);
	पूर्ण

	क्रम (i = 0; i < TX_BD_RING_LEN; i++) अणु
		अगर (i < (TX_BD_RING_LEN - 1))
			bd_status =  T_I_S | T_TC_S;
		अन्यथा
			bd_status =  T_I_S | T_TC_S | T_W_S;

		ioग_लिखो16be(bd_status, &priv->tx_bd_base[i].status);
		ioग_लिखो32be(priv->dma_tx_addr + i * MAX_RX_BUF_LENGTH,
			    &priv->tx_bd_base[i].buf);
	पूर्ण

	वापस 0;

मुक्त_tiptr:
	qe_muram_मुक्त(tiptr);
मुक्त_riptr:
	qe_muram_मुक्त(riptr);
मुक्त_tx_skbuff:
	kमुक्त(priv->tx_skbuff);
मुक्त_rx_skbuff:
	kमुक्त(priv->rx_skbuff);
मुक्त_ucc_pram:
	qe_muram_मुक्त(priv->ucc_pram_offset);
मुक्त_tx_bd:
	dma_मुक्त_coherent(priv->dev,
			  TX_BD_RING_LEN * माप(काष्ठा qe_bd),
			  priv->tx_bd_base, priv->dma_tx_bd);
मुक्त_rx_bd:
	dma_मुक्त_coherent(priv->dev,
			  RX_BD_RING_LEN * माप(काष्ठा qe_bd),
			  priv->rx_bd_base, priv->dma_rx_bd);
मुक्त_uccf:
	ucc_fast_मुक्त(priv->uccf);

	वापस ret;
पूर्ण

अटल netdev_tx_t ucc_hdlc_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा ucc_hdlc_निजी *priv = (काष्ठा ucc_hdlc_निजी *)hdlc->priv;
	काष्ठा qe_bd __iomem *bd;
	u16 bd_status;
	अचिन्हित दीर्घ flags;
	u16 *proto_head;

	चयन (dev->type) अणु
	हाल ARPHRD_RAWHDLC:
		अगर (skb_headroom(skb) < HDLC_HEAD_LEN) अणु
			dev->stats.tx_dropped++;
			dev_kमुक्त_skb(skb);
			netdev_err(dev, "No enough space for hdlc head\n");
			वापस -ENOMEM;
		पूर्ण

		skb_push(skb, HDLC_HEAD_LEN);

		proto_head = (u16 *)skb->data;
		*proto_head = htons(DEFAULT_HDLC_HEAD);

		dev->stats.tx_bytes += skb->len;
		अवरोध;

	हाल ARPHRD_PPP:
		proto_head = (u16 *)skb->data;
		अगर (*proto_head != htons(DEFAULT_PPP_HEAD)) अणु
			dev->stats.tx_dropped++;
			dev_kमुक्त_skb(skb);
			netdev_err(dev, "Wrong ppp header\n");
			वापस -ENOMEM;
		पूर्ण

		dev->stats.tx_bytes += skb->len;
		अवरोध;

	हाल ARPHRD_ETHER:
		dev->stats.tx_bytes += skb->len;
		अवरोध;

	शेष:
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण
	netdev_sent_queue(dev, skb->len);
	spin_lock_irqsave(&priv->lock, flags);

	/* Start from the next BD that should be filled */
	bd = priv->curtx_bd;
	bd_status = ioपढ़ो16be(&bd->status);
	/* Save the skb poपूर्णांकer so we can मुक्त it later */
	priv->tx_skbuff[priv->skb_curtx] = skb;

	/* Update the current skb poपूर्णांकer (wrapping अगर this was the last) */
	priv->skb_curtx =
	    (priv->skb_curtx + 1) & TX_RING_MOD_MASK(TX_BD_RING_LEN);

	/* copy skb data to tx buffer क्रम sdma processing */
	स_नकल(priv->tx_buffer + (be32_to_cpu(bd->buf) - priv->dma_tx_addr),
	       skb->data, skb->len);

	/* set bd status and length */
	bd_status = (bd_status & T_W_S) | T_R_S | T_I_S | T_L_S | T_TC_S;

	ioग_लिखो16be(skb->len, &bd->length);
	ioग_लिखो16be(bd_status, &bd->status);

	/* Move to next BD in the ring */
	अगर (!(bd_status & T_W_S))
		bd += 1;
	अन्यथा
		bd = priv->tx_bd_base;

	अगर (bd == priv->dirty_tx) अणु
		अगर (!netअगर_queue_stopped(dev))
			netअगर_stop_queue(dev);
	पूर्ण

	priv->curtx_bd = bd;

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक hdlc_tx_restart(काष्ठा ucc_hdlc_निजी *priv)
अणु
	u32 cecr_subblock;

	cecr_subblock =
		ucc_fast_get_qe_cr_subblock(priv->ut_info->uf_info.ucc_num);

	qe_issue_cmd(QE_RESTART_TX, cecr_subblock,
		     QE_CR_PROTOCOL_UNSPECIFIED, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक hdlc_tx_करोne(काष्ठा ucc_hdlc_निजी *priv)
अणु
	/* Start from the next BD that should be filled */
	काष्ठा net_device *dev = priv->ndev;
	अचिन्हित पूर्णांक bytes_sent = 0;
	पूर्णांक howmany = 0;
	काष्ठा qe_bd *bd;		/* BD poपूर्णांकer */
	u16 bd_status;
	पूर्णांक tx_restart = 0;

	bd = priv->dirty_tx;
	bd_status = ioपढ़ो16be(&bd->status);

	/* Normal processing. */
	जबतक ((bd_status & T_R_S) == 0) अणु
		काष्ठा sk_buff *skb;

		अगर (bd_status & T_UN_S) अणु /* Underrun */
			dev->stats.tx_fअगरo_errors++;
			tx_restart = 1;
		पूर्ण
		अगर (bd_status & T_CT_S) अणु /* Carrier lost */
			dev->stats.tx_carrier_errors++;
			tx_restart = 1;
		पूर्ण

		/* BD contains alपढ़ोy transmitted buffer.   */
		/* Handle the transmitted buffer and release */
		/* the BD to be used with the current frame  */

		skb = priv->tx_skbuff[priv->skb_dirtytx];
		अगर (!skb)
			अवरोध;
		howmany++;
		bytes_sent += skb->len;
		dev->stats.tx_packets++;
		स_रखो(priv->tx_buffer +
		       (be32_to_cpu(bd->buf) - priv->dma_tx_addr),
		       0, skb->len);
		dev_consume_skb_irq(skb);

		priv->tx_skbuff[priv->skb_dirtytx] = शून्य;
		priv->skb_dirtytx =
		    (priv->skb_dirtytx +
		     1) & TX_RING_MOD_MASK(TX_BD_RING_LEN);

		/* We मुक्तd a buffer, so now we can restart transmission */
		अगर (netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);

		/* Advance the confirmation BD poपूर्णांकer */
		अगर (!(bd_status & T_W_S))
			bd += 1;
		अन्यथा
			bd = priv->tx_bd_base;
		bd_status = ioपढ़ो16be(&bd->status);
	पूर्ण
	priv->dirty_tx = bd;

	अगर (tx_restart)
		hdlc_tx_restart(priv);

	netdev_completed_queue(dev, howmany, bytes_sent);
	वापस 0;
पूर्ण

अटल पूर्णांक hdlc_rx_करोne(काष्ठा ucc_hdlc_निजी *priv, पूर्णांक rx_work_limit)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा sk_buff *skb = शून्य;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा qe_bd *bd;
	u16 bd_status;
	u16 length, howmany = 0;
	u8 *bdbuffer;

	bd = priv->currx_bd;
	bd_status = ioपढ़ो16be(&bd->status);

	/* जबतक there are received buffers and BD is full (~R_E) */
	जबतक (!((bd_status & (R_E_S)) || (--rx_work_limit < 0))) अणु
		अगर (bd_status & (RX_BD_ERRORS)) अणु
			dev->stats.rx_errors++;

			अगर (bd_status & R_CD_S)
				dev->stats.collisions++;
			अगर (bd_status & R_OV_S)
				dev->stats.rx_fअगरo_errors++;
			अगर (bd_status & R_CR_S)
				dev->stats.rx_crc_errors++;
			अगर (bd_status & R_AB_S)
				dev->stats.rx_over_errors++;
			अगर (bd_status & R_NO_S)
				dev->stats.rx_frame_errors++;
			अगर (bd_status & R_LG_S)
				dev->stats.rx_length_errors++;

			जाओ recycle;
		पूर्ण
		bdbuffer = priv->rx_buffer +
			(priv->currx_bdnum * MAX_RX_BUF_LENGTH);
		length = ioपढ़ो16be(&bd->length);

		चयन (dev->type) अणु
		हाल ARPHRD_RAWHDLC:
			bdbuffer += HDLC_HEAD_LEN;
			length -= (HDLC_HEAD_LEN + HDLC_CRC_SIZE);

			skb = dev_alloc_skb(length);
			अगर (!skb) अणु
				dev->stats.rx_dropped++;
				वापस -ENOMEM;
			पूर्ण

			skb_put(skb, length);
			skb->len = length;
			skb->dev = dev;
			स_नकल(skb->data, bdbuffer, length);
			अवरोध;

		हाल ARPHRD_PPP:
		हाल ARPHRD_ETHER:
			length -= HDLC_CRC_SIZE;

			skb = dev_alloc_skb(length);
			अगर (!skb) अणु
				dev->stats.rx_dropped++;
				वापस -ENOMEM;
			पूर्ण

			skb_put(skb, length);
			skb->len = length;
			skb->dev = dev;
			स_नकल(skb->data, bdbuffer, length);
			अवरोध;
		पूर्ण

		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		howmany++;
		अगर (hdlc->proto)
			skb->protocol = hdlc_type_trans(skb, dev);
		netअगर_receive_skb(skb);

recycle:
		ioग_लिखो16be((bd_status & R_W_S) | R_E_S | R_I_S, &bd->status);

		/* update to poपूर्णांक at the next bd */
		अगर (bd_status & R_W_S) अणु
			priv->currx_bdnum = 0;
			bd = priv->rx_bd_base;
		पूर्ण अन्यथा अणु
			अगर (priv->currx_bdnum < (RX_BD_RING_LEN - 1))
				priv->currx_bdnum += 1;
			अन्यथा
				priv->currx_bdnum = RX_BD_RING_LEN - 1;

			bd += 1;
		पूर्ण

		bd_status = ioपढ़ो16be(&bd->status);
	पूर्ण

	priv->currx_bd = bd;
	वापस howmany;
पूर्ण

अटल पूर्णांक ucc_hdlc_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ucc_hdlc_निजी *priv = container_of(napi,
						     काष्ठा ucc_hdlc_निजी,
						     napi);
	पूर्णांक howmany;

	/* Tx event processing */
	spin_lock(&priv->lock);
	hdlc_tx_करोne(priv);
	spin_unlock(&priv->lock);

	howmany = 0;
	howmany += hdlc_rx_करोne(priv, budget - howmany);

	अगर (howmany < budget) अणु
		napi_complete_करोne(napi, howmany);
		qe_setbits_be32(priv->uccf->p_uccm,
				(UCCE_HDLC_RX_EVENTS | UCCE_HDLC_TX_EVENTS) << 16);
	पूर्ण

	वापस howmany;
पूर्ण

अटल irqवापस_t ucc_hdlc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ucc_hdlc_निजी *priv = (काष्ठा ucc_hdlc_निजी *)dev_id;
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा ucc_fast_निजी *uccf;
	u32 ucce;
	u32 uccm;

	uccf = priv->uccf;

	ucce = ioपढ़ो32be(uccf->p_ucce);
	uccm = ioपढ़ो32be(uccf->p_uccm);
	ucce &= uccm;
	ioग_लिखो32be(ucce, uccf->p_ucce);
	अगर (!ucce)
		वापस IRQ_NONE;

	अगर ((ucce >> 16) & (UCCE_HDLC_RX_EVENTS | UCCE_HDLC_TX_EVENTS)) अणु
		अगर (napi_schedule_prep(&priv->napi)) अणु
			uccm &= ~((UCCE_HDLC_RX_EVENTS | UCCE_HDLC_TX_EVENTS)
				  << 16);
			ioग_लिखो32be(uccm, uccf->p_uccm);
			__napi_schedule(&priv->napi);
		पूर्ण
	पूर्ण

	/* Errors and other events */
	अगर (ucce >> 16 & UCC_HDLC_UCCE_BSY)
		dev->stats.rx_missed_errors++;
	अगर (ucce >> 16 & UCC_HDLC_UCCE_TXE)
		dev->stats.tx_errors++;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uhdlc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	स्थिर माप_प्रकार size = माप(te1_settings);
	te1_settings line;
	काष्ठा ucc_hdlc_निजी *priv = netdev_priv(dev);

	अगर (cmd != SIOCWANDEV)
		वापस hdlc_ioctl(dev, अगरr, cmd);

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_GET_IFACE:
		अगरr->अगरr_settings.type = IF_IFACE_E1;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		स_रखो(&line, 0, माप(line));
		line.घड़ी_प्रकारype = priv->घड़ीing;

		अगर (copy_to_user(अगरr->अगरr_settings.अगरs_अगरsu.sync, &line, size))
			वापस -EFAULT;
		वापस 0;

	शेष:
		वापस hdlc_ioctl(dev, अगरr, cmd);
	पूर्ण
पूर्ण

अटल पूर्णांक uhdlc_खोलो(काष्ठा net_device *dev)
अणु
	u32 cecr_subblock;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा ucc_hdlc_निजी *priv = hdlc->priv;
	काष्ठा ucc_tdm *utdm = priv->utdm;

	अगर (priv->hdlc_busy != 1) अणु
		अगर (request_irq(priv->ut_info->uf_info.irq,
				ucc_hdlc_irq_handler, 0, "hdlc", priv))
			वापस -ENODEV;

		cecr_subblock = ucc_fast_get_qe_cr_subblock(
					priv->ut_info->uf_info.ucc_num);

		qe_issue_cmd(QE_INIT_TX_RX, cecr_subblock,
			     QE_CR_PROTOCOL_UNSPECIFIED, 0);

		ucc_fast_enable(priv->uccf, COMM_सूची_RX | COMM_सूची_TX);

		/* Enable the TDM port */
		अगर (priv->tsa)
			utdm->si_regs->siglmr1_h |= (0x1 << utdm->tdm_port);

		priv->hdlc_busy = 1;
		netअगर_device_attach(priv->ndev);
		napi_enable(&priv->napi);
		netdev_reset_queue(dev);
		netअगर_start_queue(dev);
		hdlc_खोलो(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uhdlc_memclean(काष्ठा ucc_hdlc_निजी *priv)
अणु
	qe_muram_मुक्त(ioपढ़ो16be(&priv->ucc_pram->riptr));
	qe_muram_मुक्त(ioपढ़ो16be(&priv->ucc_pram->tiptr));

	अगर (priv->rx_bd_base) अणु
		dma_मुक्त_coherent(priv->dev,
				  RX_BD_RING_LEN * माप(काष्ठा qe_bd),
				  priv->rx_bd_base, priv->dma_rx_bd);

		priv->rx_bd_base = शून्य;
		priv->dma_rx_bd = 0;
	पूर्ण

	अगर (priv->tx_bd_base) अणु
		dma_मुक्त_coherent(priv->dev,
				  TX_BD_RING_LEN * माप(काष्ठा qe_bd),
				  priv->tx_bd_base, priv->dma_tx_bd);

		priv->tx_bd_base = शून्य;
		priv->dma_tx_bd = 0;
	पूर्ण

	अगर (priv->ucc_pram) अणु
		qe_muram_मुक्त(priv->ucc_pram_offset);
		priv->ucc_pram = शून्य;
		priv->ucc_pram_offset = 0;
	 पूर्ण

	kमुक्त(priv->rx_skbuff);
	priv->rx_skbuff = शून्य;

	kमुक्त(priv->tx_skbuff);
	priv->tx_skbuff = शून्य;

	अगर (priv->uf_regs) अणु
		iounmap(priv->uf_regs);
		priv->uf_regs = शून्य;
	पूर्ण

	अगर (priv->uccf) अणु
		ucc_fast_मुक्त(priv->uccf);
		priv->uccf = शून्य;
	पूर्ण

	अगर (priv->rx_buffer) अणु
		dma_मुक्त_coherent(priv->dev,
				  RX_BD_RING_LEN * MAX_RX_BUF_LENGTH,
				  priv->rx_buffer, priv->dma_rx_addr);
		priv->rx_buffer = शून्य;
		priv->dma_rx_addr = 0;
	पूर्ण

	अगर (priv->tx_buffer) अणु
		dma_मुक्त_coherent(priv->dev,
				  TX_BD_RING_LEN * MAX_RX_BUF_LENGTH,
				  priv->tx_buffer, priv->dma_tx_addr);
		priv->tx_buffer = शून्य;
		priv->dma_tx_addr = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक uhdlc_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ucc_hdlc_निजी *priv = dev_to_hdlc(dev)->priv;
	काष्ठा ucc_tdm *utdm = priv->utdm;
	u32 cecr_subblock;

	napi_disable(&priv->napi);
	cecr_subblock = ucc_fast_get_qe_cr_subblock(
				priv->ut_info->uf_info.ucc_num);

	qe_issue_cmd(QE_GRACEFUL_STOP_TX, cecr_subblock,
		     (u8)QE_CR_PROTOCOL_UNSPECIFIED, 0);
	qe_issue_cmd(QE_CLOSE_RX_BD, cecr_subblock,
		     (u8)QE_CR_PROTOCOL_UNSPECIFIED, 0);

	अगर (priv->tsa)
		utdm->si_regs->siglmr1_h &= ~(0x1 << utdm->tdm_port);

	ucc_fast_disable(priv->uccf, COMM_सूची_RX | COMM_सूची_TX);

	मुक्त_irq(priv->ut_info->uf_info.irq, priv);
	netअगर_stop_queue(dev);
	netdev_reset_queue(dev);
	priv->hdlc_busy = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ucc_hdlc_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			   अचिन्हित लघु parity)
अणु
	काष्ठा ucc_hdlc_निजी *priv = dev_to_hdlc(dev)->priv;

	अगर (encoding != ENCODING_NRZ &&
	    encoding != ENCODING_NRZI)
		वापस -EINVAL;

	अगर (parity != PARITY_NONE &&
	    parity != PARITY_CRC32_PR1_CCITT &&
	    parity != PARITY_CRC16_PR0_CCITT &&
	    parity != PARITY_CRC16_PR1_CCITT)
		वापस -EINVAL;

	priv->encoding = encoding;
	priv->parity = parity;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम store_clk_config(काष्ठा ucc_hdlc_निजी *priv)
अणु
	काष्ठा qe_mux *qe_mux_reg = &qe_immr->qmx;

	/* store si clk */
	priv->cmxsi1cr_h = ioपढ़ो32be(&qe_mux_reg->cmxsi1cr_h);
	priv->cmxsi1cr_l = ioपढ़ो32be(&qe_mux_reg->cmxsi1cr_l);

	/* store si sync */
	priv->cmxsi1syr = ioपढ़ो32be(&qe_mux_reg->cmxsi1syr);

	/* store ucc clk */
	स_नकल_fromio(priv->cmxucr, qe_mux_reg->cmxucr, 4 * माप(u32));
पूर्ण

अटल व्योम resume_clk_config(काष्ठा ucc_hdlc_निजी *priv)
अणु
	काष्ठा qe_mux *qe_mux_reg = &qe_immr->qmx;

	स_नकल_toio(qe_mux_reg->cmxucr, priv->cmxucr, 4 * माप(u32));

	ioग_लिखो32be(priv->cmxsi1cr_h, &qe_mux_reg->cmxsi1cr_h);
	ioग_लिखो32be(priv->cmxsi1cr_l, &qe_mux_reg->cmxsi1cr_l);

	ioग_लिखो32be(priv->cmxsi1syr, &qe_mux_reg->cmxsi1syr);
पूर्ण

अटल पूर्णांक uhdlc_suspend(काष्ठा device *dev)
अणु
	काष्ठा ucc_hdlc_निजी *priv = dev_get_drvdata(dev);
	काष्ठा ucc_fast __iomem *uf_regs;

	अगर (!priv)
		वापस -EINVAL;

	अगर (!netअगर_running(priv->ndev))
		वापस 0;

	netअगर_device_detach(priv->ndev);
	napi_disable(&priv->napi);

	uf_regs = priv->uf_regs;

	/* backup gumr guemr*/
	priv->gumr = ioपढ़ो32be(&uf_regs->gumr);
	priv->guemr = ioपढ़ो8(&uf_regs->guemr);

	priv->ucc_pram_bak = kदो_स्मृति(माप(*priv->ucc_pram_bak),
					GFP_KERNEL);
	अगर (!priv->ucc_pram_bak)
		वापस -ENOMEM;

	/* backup HDLC parameter */
	स_नकल_fromio(priv->ucc_pram_bak, priv->ucc_pram,
		      माप(काष्ठा ucc_hdlc_param));

	/* store the clk configuration */
	store_clk_config(priv);

	/* save घातer */
	ucc_fast_disable(priv->uccf, COMM_सूची_RX | COMM_सूची_TX);

	वापस 0;
पूर्ण

अटल पूर्णांक uhdlc_resume(काष्ठा device *dev)
अणु
	काष्ठा ucc_hdlc_निजी *priv = dev_get_drvdata(dev);
	काष्ठा ucc_tdm *utdm;
	काष्ठा ucc_tdm_info *ut_info;
	काष्ठा ucc_fast __iomem *uf_regs;
	काष्ठा ucc_fast_निजी *uccf;
	काष्ठा ucc_fast_info *uf_info;
	पूर्णांक i;
	u32 cecr_subblock;
	u16 bd_status;

	अगर (!priv)
		वापस -EINVAL;

	अगर (!netअगर_running(priv->ndev))
		वापस 0;

	utdm = priv->utdm;
	ut_info = priv->ut_info;
	uf_info = &ut_info->uf_info;
	uf_regs = priv->uf_regs;
	uccf = priv->uccf;

	/* restore gumr guemr */
	ioग_लिखो8(priv->guemr, &uf_regs->guemr);
	ioग_लिखो32be(priv->gumr, &uf_regs->gumr);

	/* Set Virtual Fअगरo रेजिस्टरs */
	ioग_लिखो16be(uf_info->urfs, &uf_regs->urfs);
	ioग_लिखो16be(uf_info->urfet, &uf_regs->urfet);
	ioग_लिखो16be(uf_info->urfset, &uf_regs->urfset);
	ioग_लिखो16be(uf_info->utfs, &uf_regs->utfs);
	ioग_लिखो16be(uf_info->utfet, &uf_regs->utfet);
	ioग_लिखो16be(uf_info->utftt, &uf_regs->utftt);
	/* utfb, urfb are offsets from MURAM base */
	ioग_लिखो32be(uccf->ucc_fast_tx_भव_fअगरo_base_offset, &uf_regs->utfb);
	ioग_लिखो32be(uccf->ucc_fast_rx_भव_fअगरo_base_offset, &uf_regs->urfb);

	/* Rx Tx and sync घड़ी routing */
	resume_clk_config(priv);

	ioग_लिखो32be(uf_info->uccm_mask, &uf_regs->uccm);
	ioग_लिखो32be(0xffffffff, &uf_regs->ucce);

	ucc_fast_disable(priv->uccf, COMM_सूची_RX | COMM_सूची_TX);

	/* rebuild SIRAM */
	अगर (priv->tsa)
		ucc_tdm_init(priv->utdm, priv->ut_info);

	/* Write to QE CECR, UCCx channel to Stop Transmission */
	cecr_subblock = ucc_fast_get_qe_cr_subblock(uf_info->ucc_num);
	qe_issue_cmd(QE_STOP_TX, cecr_subblock,
		     (u8)QE_CR_PROTOCOL_UNSPECIFIED, 0);

	/* Set UPSMR normal mode */
	ioग_लिखो32be(0, &uf_regs->upsmr);

	/* init parameter base */
	cecr_subblock = ucc_fast_get_qe_cr_subblock(uf_info->ucc_num);
	qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, cecr_subblock,
		     QE_CR_PROTOCOL_UNSPECIFIED, priv->ucc_pram_offset);

	priv->ucc_pram = (काष्ठा ucc_hdlc_param __iomem *)
				qe_muram_addr(priv->ucc_pram_offset);

	/* restore ucc parameter */
	स_नकल_toio(priv->ucc_pram, priv->ucc_pram_bak,
		    माप(काष्ठा ucc_hdlc_param));
	kमुक्त(priv->ucc_pram_bak);

	/* rebuild BD entry */
	क्रम (i = 0; i < RX_BD_RING_LEN; i++) अणु
		अगर (i < (RX_BD_RING_LEN - 1))
			bd_status = R_E_S | R_I_S;
		अन्यथा
			bd_status = R_E_S | R_I_S | R_W_S;

		ioग_लिखो16be(bd_status, &priv->rx_bd_base[i].status);
		ioग_लिखो32be(priv->dma_rx_addr + i * MAX_RX_BUF_LENGTH,
			    &priv->rx_bd_base[i].buf);
	पूर्ण

	क्रम (i = 0; i < TX_BD_RING_LEN; i++) अणु
		अगर (i < (TX_BD_RING_LEN - 1))
			bd_status =  T_I_S | T_TC_S;
		अन्यथा
			bd_status =  T_I_S | T_TC_S | T_W_S;

		ioग_लिखो16be(bd_status, &priv->tx_bd_base[i].status);
		ioग_लिखो32be(priv->dma_tx_addr + i * MAX_RX_BUF_LENGTH,
			    &priv->tx_bd_base[i].buf);
	पूर्ण

	/* अगर hdlc is busy enable TX and RX */
	अगर (priv->hdlc_busy == 1) अणु
		cecr_subblock = ucc_fast_get_qe_cr_subblock(
					priv->ut_info->uf_info.ucc_num);

		qe_issue_cmd(QE_INIT_TX_RX, cecr_subblock,
			     (u8)QE_CR_PROTOCOL_UNSPECIFIED, 0);

		ucc_fast_enable(priv->uccf, COMM_सूची_RX | COMM_सूची_TX);

		/* Enable the TDM port */
		अगर (priv->tsa)
			utdm->si_regs->siglmr1_h |= (0x1 << utdm->tdm_port);
	पूर्ण

	napi_enable(&priv->napi);
	netअगर_device_attach(priv->ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops uhdlc_pm_ops = अणु
	.suspend = uhdlc_suspend,
	.resume = uhdlc_resume,
	.मुक्तze = uhdlc_suspend,
	.thaw = uhdlc_resume,
पूर्ण;

#घोषणा HDLC_PM_OPS (&uhdlc_pm_ops)

#अन्यथा

#घोषणा HDLC_PM_OPS शून्य

#पूर्ण_अगर
अटल व्योम uhdlc_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	netdev_err(ndev, "%s\n", __func__);
पूर्ण

अटल स्थिर काष्ठा net_device_ops uhdlc_ops = अणु
	.nकरो_खोलो       = uhdlc_खोलो,
	.nकरो_stop       = uhdlc_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = uhdlc_ioctl,
	.nकरो_tx_समयout	= uhdlc_tx_समयout,
पूर्ण;

अटल पूर्णांक hdlc_map_iomem(अक्षर *name, पूर्णांक init_flag, व्योम __iomem **ptr)
अणु
	काष्ठा device_node *np;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *res;
	अटल पूर्णांक siram_init_flag;
	पूर्णांक ret = 0;

	np = of_find_compatible_node(शून्य, शून्य, name);
	अगर (!np)
		वापस -EINVAL;

	pdev = of_find_device_by_node(np);
	अगर (!pdev) अणु
		pr_err("%pOFn: failed to lookup pdev\n", np);
		of_node_put(np);
		वापस -EINVAL;
	पूर्ण

	of_node_put(np);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -EINVAL;
		जाओ error_put_device;
	पूर्ण
	*ptr = ioremap(res->start, resource_size(res));
	अगर (!*ptr) अणु
		ret = -ENOMEM;
		जाओ error_put_device;
	पूर्ण

	/* We've remapped the addresses, and we don't need the device any
	 * more, so we should release it.
	 */
	put_device(&pdev->dev);

	अगर (init_flag && siram_init_flag == 0) अणु
		स_रखो_io(*ptr, 0, resource_size(res));
		siram_init_flag = 1;
	पूर्ण
	वापस  0;

error_put_device:
	put_device(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक ucc_hdlc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ucc_hdlc_निजी *uhdlc_priv = शून्य;
	काष्ठा ucc_tdm_info *ut_info;
	काष्ठा ucc_tdm *utdm = शून्य;
	काष्ठा resource res;
	काष्ठा net_device *dev;
	hdlc_device *hdlc;
	पूर्णांक ucc_num;
	स्थिर अक्षर *sprop;
	पूर्णांक ret;
	u32 val;

	ret = of_property_पढ़ो_u32_index(np, "cell-index", 0, &val);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Invalid ucc property\n");
		वापस -ENODEV;
	पूर्ण

	ucc_num = val - 1;
	अगर (ucc_num > (UCC_MAX_NUM - 1) || ucc_num < 0) अणु
		dev_err(&pdev->dev, ": Invalid UCC num\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(&utdm_info[ucc_num], &utdm_primary_info,
	       माप(utdm_primary_info));

	ut_info = &utdm_info[ucc_num];
	ut_info->uf_info.ucc_num = ucc_num;

	sprop = of_get_property(np, "rx-clock-name", शून्य);
	अगर (sprop) अणु
		ut_info->uf_info.rx_घड़ी = qe_घड़ी_source(sprop);
		अगर ((ut_info->uf_info.rx_घड़ी < QE_CLK_NONE) ||
		    (ut_info->uf_info.rx_घड़ी > QE_CLK24)) अणु
			dev_err(&pdev->dev, "Invalid rx-clock-name property\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Invalid rx-clock-name property\n");
		वापस -EINVAL;
	पूर्ण

	sprop = of_get_property(np, "tx-clock-name", शून्य);
	अगर (sprop) अणु
		ut_info->uf_info.tx_घड़ी = qe_घड़ी_source(sprop);
		अगर ((ut_info->uf_info.tx_घड़ी < QE_CLK_NONE) ||
		    (ut_info->uf_info.tx_घड़ी > QE_CLK24)) अणु
			dev_err(&pdev->dev, "Invalid tx-clock-name property\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Invalid tx-clock-name property\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_address_to_resource(np, 0, &res);
	अगर (ret)
		वापस -EINVAL;

	ut_info->uf_info.regs = res.start;
	ut_info->uf_info.irq = irq_of_parse_and_map(np, 0);

	uhdlc_priv = kzalloc(माप(*uhdlc_priv), GFP_KERNEL);
	अगर (!uhdlc_priv) अणु
		वापस -ENOMEM;
	पूर्ण

	dev_set_drvdata(&pdev->dev, uhdlc_priv);
	uhdlc_priv->dev = &pdev->dev;
	uhdlc_priv->ut_info = ut_info;

	अगर (of_get_property(np, "fsl,tdm-interface", शून्य))
		uhdlc_priv->tsa = 1;

	अगर (of_get_property(np, "fsl,ucc-internal-loopback", शून्य))
		uhdlc_priv->loopback = 1;

	अगर (of_get_property(np, "fsl,hdlc-bus", शून्य))
		uhdlc_priv->hdlc_bus = 1;

	अगर (uhdlc_priv->tsa == 1) अणु
		utdm = kzalloc(माप(*utdm), GFP_KERNEL);
		अगर (!utdm) अणु
			ret = -ENOMEM;
			dev_err(&pdev->dev, "No mem to alloc ucc tdm data\n");
			जाओ मुक्त_uhdlc_priv;
		पूर्ण
		uhdlc_priv->utdm = utdm;
		ret = ucc_of_parse_tdm(np, utdm, ut_info);
		अगर (ret)
			जाओ मुक्त_utdm;

		ret = hdlc_map_iomem("fsl,t1040-qe-si", 0,
				     (व्योम __iomem **)&utdm->si_regs);
		अगर (ret)
			जाओ मुक्त_utdm;
		ret = hdlc_map_iomem("fsl,t1040-qe-siram", 1,
				     (व्योम __iomem **)&utdm->siram);
		अगर (ret)
			जाओ unmap_si_regs;
	पूर्ण

	अगर (of_property_पढ़ो_u16(np, "fsl,hmask", &uhdlc_priv->hmask))
		uhdlc_priv->hmask = DEFAULT_ADDR_MASK;

	ret = uhdlc_init(uhdlc_priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to init uhdlc\n");
		जाओ unकरो_uhdlc_init;
	पूर्ण

	dev = alloc_hdlcdev(uhdlc_priv);
	अगर (!dev) अणु
		ret = -ENOMEM;
		pr_err("ucc_hdlc: unable to allocate memory\n");
		जाओ unकरो_uhdlc_init;
	पूर्ण

	uhdlc_priv->ndev = dev;
	hdlc = dev_to_hdlc(dev);
	dev->tx_queue_len = 16;
	dev->netdev_ops = &uhdlc_ops;
	dev->watchकरोg_समयo = 2 * HZ;
	hdlc->attach = ucc_hdlc_attach;
	hdlc->xmit = ucc_hdlc_tx;
	netअगर_napi_add(dev, &uhdlc_priv->napi, ucc_hdlc_poll, 32);
	अगर (रेजिस्टर_hdlc_device(dev)) अणु
		ret = -ENOBUFS;
		pr_err("ucc_hdlc: unable to register hdlc device\n");
		जाओ मुक्त_dev;
	पूर्ण

	वापस 0;

मुक्त_dev:
	मुक्त_netdev(dev);
unकरो_uhdlc_init:
	iounmap(utdm->siram);
unmap_si_regs:
	iounmap(utdm->si_regs);
मुक्त_utdm:
	अगर (uhdlc_priv->tsa)
		kमुक्त(utdm);
मुक्त_uhdlc_priv:
	kमुक्त(uhdlc_priv);
	वापस ret;
पूर्ण

अटल पूर्णांक ucc_hdlc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ucc_hdlc_निजी *priv = dev_get_drvdata(&pdev->dev);

	uhdlc_memclean(priv);

	अगर (priv->utdm->si_regs) अणु
		iounmap(priv->utdm->si_regs);
		priv->utdm->si_regs = शून्य;
	पूर्ण

	अगर (priv->utdm->siram) अणु
		iounmap(priv->utdm->siram);
		priv->utdm->siram = शून्य;
	पूर्ण
	kमुक्त(priv);

	dev_info(&pdev->dev, "UCC based hdlc module removed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_ucc_hdlc_of_match[] = अणु
	अणु
	.compatible = "fsl,ucc-hdlc",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, fsl_ucc_hdlc_of_match);

अटल काष्ठा platक्रमm_driver ucc_hdlc_driver = अणु
	.probe	= ucc_hdlc_probe,
	.हटाओ	= ucc_hdlc_हटाओ,
	.driver	= अणु
		.name		= DRV_NAME,
		.pm		= HDLC_PM_OPS,
		.of_match_table	= fsl_ucc_hdlc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ucc_hdlc_driver);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRV_DESC);
