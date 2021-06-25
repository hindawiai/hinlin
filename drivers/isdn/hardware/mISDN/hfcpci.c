<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * hfcpci.c     low level driver क्रम CCD's hfc-pci based cards
 *
 * Author     Werner Cornelius (werner@isdn4linux.de)
 *            based on existing driver क्रम CCD hfc ISA cards
 *            type approval valid क्रम HFC-S PCI A based card
 *
 * Copyright 1999  by Werner Cornelius (werner@isdn-development.de)
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 *
 * Module options:
 *
 * debug:
 *	NOTE: only one poll value must be given क्रम all cards
 *	See hfc_pci.h क्रम debug flags.
 *
 * poll:
 *	NOTE: only one poll value must be given क्रम all cards
 *	Give the number of samples क्रम each fअगरo process.
 *	By शेष 128 is used. Decrease to reduce delay, increase to
 *	reduce cpu load. If unsure, करोn't mess with it!
 *	A value of 128 will use controller's पूर्णांकerrupt. Other values will
 *	use kernel समयr, because the controller will not allow lower values
 *	than 128.
 *	Also note that the value depends on the kernel समयr frequency.
 *	If kernel uses a frequency of 1000 Hz, steps of 8 samples are possible.
 *	If the kernel uses 100 Hz, steps of 80 samples are possible.
 *	If the kernel uses 300 Hz, steps of about 26 samples are possible.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/slab.h>

#समावेश "hfc_pci.h"

अटल स्थिर अक्षर *hfcpci_revision = "2.0";

अटल पूर्णांक HFC_cnt;
अटल uपूर्णांक debug;
अटल uपूर्णांक poll, tics;
अटल काष्ठा समयr_list hfc_tl;
अटल अचिन्हित दीर्घ hfc_jअगरfies;

MODULE_AUTHOR("Karsten Keil");
MODULE_LICENSE("GPL");
module_param(debug, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param(poll, uपूर्णांक, S_IRUGO | S_IWUSR);

क्रमागत अणु
	HFC_CCD_2BD0,
	HFC_CCD_B000,
	HFC_CCD_B006,
	HFC_CCD_B007,
	HFC_CCD_B008,
	HFC_CCD_B009,
	HFC_CCD_B00A,
	HFC_CCD_B00B,
	HFC_CCD_B00C,
	HFC_CCD_B100,
	HFC_CCD_B700,
	HFC_CCD_B701,
	HFC_ASUS_0675,
	HFC_BERKOM_A1T,
	HFC_BERKOM_TCONCEPT,
	HFC_ANIGMA_MC145575,
	HFC_ZOLTRIX_2BD0,
	HFC_DIGI_DF_M_IOM2_E,
	HFC_DIGI_DF_M_E,
	HFC_DIGI_DF_M_IOM2_A,
	HFC_DIGI_DF_M_A,
	HFC_ABOCOM_2BD1,
	HFC_SITECOM_DC105V2,
पूर्ण;

काष्ठा hfcPCI_hw अणु
	अचिन्हित अक्षर		cirm;
	अचिन्हित अक्षर		cपंचांगt;
	अचिन्हित अक्षर		clkdel;
	अचिन्हित अक्षर		states;
	अचिन्हित अक्षर		conn;
	अचिन्हित अक्षर		mst_m;
	अचिन्हित अक्षर		पूर्णांक_m1;
	अचिन्हित अक्षर		पूर्णांक_m2;
	अचिन्हित अक्षर		sctrl;
	अचिन्हित अक्षर		sctrl_r;
	अचिन्हित अक्षर		sctrl_e;
	अचिन्हित अक्षर		trm;
	अचिन्हित अक्षर		fअगरo_en;
	अचिन्हित अक्षर		bswapped;
	अचिन्हित अक्षर		protocol;
	पूर्णांक			nt_समयr;
	अचिन्हित अक्षर __iomem	*pci_io; /* start of PCI IO memory */
	dma_addr_t		dmahandle;
	व्योम			*fअगरos; /* FIFO memory */
	पूर्णांक			last_bfअगरo_cnt[2];
	/* marker saving last b-fअगरo frame count */
	काष्ठा समयr_list	समयr;
पूर्ण;

#घोषणा	HFC_CFG_MASTER		1
#घोषणा HFC_CFG_SLAVE		2
#घोषणा	HFC_CFG_PCM		3
#घोषणा HFC_CFG_2HFC		4
#घोषणा HFC_CFG_SLAVEHFC	5
#घोषणा HFC_CFG_NEG_F0		6
#घोषणा HFC_CFG_SW_DD_DU	7

#घोषणा FLG_HFC_TIMER_T1	16
#घोषणा FLG_HFC_TIMER_T3	17

#घोषणा NT_T1_COUNT	1120	/* number of 3.125ms पूर्णांकerrupts (3.5s) */
#घोषणा NT_T3_COUNT	31	/* number of 3.125ms पूर्णांकerrupts (97 ms) */
#घोषणा CLKDEL_TE	0x0e	/* CLKDEL in TE mode */
#घोषणा CLKDEL_NT	0x6c	/* CLKDEL in NT mode */


काष्ठा hfc_pci अणु
	u_अक्षर			subtype;
	u_अक्षर			chanlimit;
	u_अक्षर			initकरोne;
	u_दीर्घ			cfg;
	u_पूर्णांक			irq;
	u_पूर्णांक			irqcnt;
	काष्ठा pci_dev		*pdev;
	काष्ठा hfcPCI_hw	hw;
	spinlock_t		lock;	/* card lock */
	काष्ठा dchannel		dch;
	काष्ठा bchannel		bch[2];
पूर्ण;

/* Interface functions */
अटल व्योम
enable_hwirq(काष्ठा hfc_pci *hc)
अणु
	hc->hw.पूर्णांक_m2 |= HFCPCI_IRQ_ENABLE;
	Write_hfc(hc, HFCPCI_INT_M2, hc->hw.पूर्णांक_m2);
पूर्ण

अटल व्योम
disable_hwirq(काष्ठा hfc_pci *hc)
अणु
	hc->hw.पूर्णांक_m2 &= ~((u_अक्षर)HFCPCI_IRQ_ENABLE);
	Write_hfc(hc, HFCPCI_INT_M2, hc->hw.पूर्णांक_m2);
पूर्ण

/*
 * मुक्त hardware resources used by driver
 */
अटल व्योम
release_io_hfcpci(काष्ठा hfc_pci *hc)
अणु
	/* disable memory mapped ports + busmaster */
	pci_ग_लिखो_config_word(hc->pdev, PCI_COMMAND, 0);
	del_समयr(&hc->hw.समयr);
	dma_मुक्त_coherent(&hc->pdev->dev, 0x8000, hc->hw.fअगरos,
			  hc->hw.dmahandle);
	iounmap(hc->hw.pci_io);
पूर्ण

/*
 * set mode (NT or TE)
 */
अटल व्योम
hfcpci_seपंचांगode(काष्ठा hfc_pci *hc)
अणु
	अगर (hc->hw.protocol == ISDN_P_NT_S0) अणु
		hc->hw.clkdel = CLKDEL_NT;	/* ST-Bit delay क्रम NT-Mode */
		hc->hw.sctrl |= SCTRL_MODE_NT;	/* NT-MODE */
		hc->hw.states = 1;		/* G1 */
	पूर्ण अन्यथा अणु
		hc->hw.clkdel = CLKDEL_TE;	/* ST-Bit delay क्रम TE-Mode */
		hc->hw.sctrl &= ~SCTRL_MODE_NT;	/* TE-MODE */
		hc->hw.states = 2;		/* F2 */
	पूर्ण
	Write_hfc(hc, HFCPCI_CLKDEL, hc->hw.clkdel);
	Write_hfc(hc, HFCPCI_STATES, HFCPCI_LOAD_STATE | hc->hw.states);
	udelay(10);
	Write_hfc(hc, HFCPCI_STATES, hc->hw.states | 0x40); /* Deactivate */
	Write_hfc(hc, HFCPCI_SCTRL, hc->hw.sctrl);
पूर्ण

/*
 * function called to reset the HFC PCI chip. A complete software reset of chip
 * and fअगरos is करोne.
 */
अटल व्योम
reset_hfcpci(काष्ठा hfc_pci *hc)
अणु
	u_अक्षर	val;
	पूर्णांक	cnt = 0;

	prपूर्णांकk(KERN_DEBUG "reset_hfcpci: entered\n");
	val = Read_hfc(hc, HFCPCI_CHIP_ID);
	prपूर्णांकk(KERN_INFO "HFC_PCI: resetting HFC ChipId(%x)\n", val);
	/* enable memory mapped ports, disable busmaster */
	pci_ग_लिखो_config_word(hc->pdev, PCI_COMMAND, PCI_ENA_MEMIO);
	disable_hwirq(hc);
	/* enable memory ports + busmaster */
	pci_ग_लिखो_config_word(hc->pdev, PCI_COMMAND,
			      PCI_ENA_MEMIO + PCI_ENA_MASTER);
	val = Read_hfc(hc, HFCPCI_STATUS);
	prपूर्णांकk(KERN_DEBUG "HFC-PCI status(%x) before reset\n", val);
	hc->hw.cirm = HFCPCI_RESET;	/* Reset On */
	Write_hfc(hc, HFCPCI_CIRM, hc->hw.cirm);
	set_current_state(TASK_UNINTERRUPTIBLE);
	mdelay(10);			/* Timeout 10ms */
	hc->hw.cirm = 0;		/* Reset Off */
	Write_hfc(hc, HFCPCI_CIRM, hc->hw.cirm);
	val = Read_hfc(hc, HFCPCI_STATUS);
	prपूर्णांकk(KERN_DEBUG "HFC-PCI status(%x) after reset\n", val);
	जबतक (cnt < 50000) अणु /* max 50000 us */
		udelay(5);
		cnt += 5;
		val = Read_hfc(hc, HFCPCI_STATUS);
		अगर (!(val & 2))
			अवरोध;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "HFC-PCI status(%x) after %dus\n", val, cnt);

	hc->hw.fअगरo_en = 0x30;	/* only D fअगरos enabled */

	hc->hw.bswapped = 0;	/* no exchange */
	hc->hw.cपंचांगt = HFCPCI_TIM3_125 | HFCPCI_AUTO_TIMER;
	hc->hw.trm = HFCPCI_BTRANS_THRESMASK; /* no echo connect , threshold */
	hc->hw.sctrl = 0x40;	/* set tx_lo mode, error in datasheet ! */
	hc->hw.sctrl_r = 0;
	hc->hw.sctrl_e = HFCPCI_AUTO_AWAKE;	/* S/T Auto awake */
	hc->hw.mst_m = 0;
	अगर (test_bit(HFC_CFG_MASTER, &hc->cfg))
		hc->hw.mst_m |= HFCPCI_MASTER;	/* HFC Master Mode */
	अगर (test_bit(HFC_CFG_NEG_F0, &hc->cfg))
		hc->hw.mst_m |= HFCPCI_F0_NEGATIV;
	Write_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fअगरo_en);
	Write_hfc(hc, HFCPCI_TRM, hc->hw.trm);
	Write_hfc(hc, HFCPCI_SCTRL_E, hc->hw.sctrl_e);
	Write_hfc(hc, HFCPCI_CTMT, hc->hw.cपंचांगt);

	hc->hw.पूर्णांक_m1 = HFCPCI_INTS_DTRANS | HFCPCI_INTS_DREC |
		HFCPCI_INTS_L1STATE | HFCPCI_INTS_TIMER;
	Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);

	/* Clear alपढ़ोy pending पूर्णांकs */
	val = Read_hfc(hc, HFCPCI_INT_S1);

	/* set NT/TE mode */
	hfcpci_seपंचांगode(hc);

	Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
	Write_hfc(hc, HFCPCI_SCTRL_R, hc->hw.sctrl_r);

	/*
	 * Init GCI/IOM2 in master mode
	 * Slots 0 and 1 are set क्रम B-chan 1 and 2
	 * D- and monitor/CI channel are not enabled
	 * STIO1 is used as output क्रम data, B1+B2 from ST->IOM+HFC
	 * STIO2 is used as data input, B1+B2 from IOM->ST
	 * ST B-channel send disabled -> continuous 1s
	 * The IOM slots are always enabled
	 */
	अगर (test_bit(HFC_CFG_PCM, &hc->cfg)) अणु
		/* set data flow directions: connect B1,B2: HFC to/from PCM */
		hc->hw.conn = 0x09;
	पूर्ण अन्यथा अणु
		hc->hw.conn = 0x36;	/* set data flow directions */
		अगर (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg)) अणु
			Write_hfc(hc, HFCPCI_B1_SSL, 0xC0);
			Write_hfc(hc, HFCPCI_B2_SSL, 0xC1);
			Write_hfc(hc, HFCPCI_B1_RSL, 0xC0);
			Write_hfc(hc, HFCPCI_B2_RSL, 0xC1);
		पूर्ण अन्यथा अणु
			Write_hfc(hc, HFCPCI_B1_SSL, 0x80);
			Write_hfc(hc, HFCPCI_B2_SSL, 0x81);
			Write_hfc(hc, HFCPCI_B1_RSL, 0x80);
			Write_hfc(hc, HFCPCI_B2_RSL, 0x81);
		पूर्ण
	पूर्ण
	Write_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
	val = Read_hfc(hc, HFCPCI_INT_S2);
पूर्ण

/*
 * Timer function called when kernel समयr expires
 */
अटल व्योम
hfcpci_Timer(काष्ठा समयr_list *t)
अणु
	काष्ठा hfc_pci *hc = from_समयr(hc, t, hw.समयr);
	hc->hw.समयr.expires = jअगरfies + 75;
	/* WD RESET */
/*
 *	WriteReg(hc, HFCD_DATA, HFCD_CTMT, hc->hw.cपंचांगt | 0x80);
 *	add_समयr(&hc->hw.समयr);
 */
पूर्ण


/*
 * select a b-channel entry matching and active
 */
अटल काष्ठा bchannel *
Sel_BCS(काष्ठा hfc_pci *hc, पूर्णांक channel)
अणु
	अगर (test_bit(FLG_ACTIVE, &hc->bch[0].Flags) &&
	    (hc->bch[0].nr & channel))
		वापस &hc->bch[0];
	अन्यथा अगर (test_bit(FLG_ACTIVE, &hc->bch[1].Flags) &&
		 (hc->bch[1].nr & channel))
		वापस &hc->bch[1];
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * clear the desired B-channel rx fअगरo
 */
अटल व्योम
hfcpci_clear_fअगरo_rx(काष्ठा hfc_pci *hc, पूर्णांक fअगरo)
अणु
	u_अक्षर		fअगरo_state;
	काष्ठा bzfअगरo	*bzr;

	अगर (fअगरo) अणु
		bzr = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.rxbz_b2;
		fअगरo_state = hc->hw.fअगरo_en & HFCPCI_FIFOEN_B2RX;
	पूर्ण अन्यथा अणु
		bzr = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.rxbz_b1;
		fअगरo_state = hc->hw.fअगरo_en & HFCPCI_FIFOEN_B1RX;
	पूर्ण
	अगर (fअगरo_state)
		hc->hw.fअगरo_en ^= fअगरo_state;
	Write_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fअगरo_en);
	hc->hw.last_bfअगरo_cnt[fअगरo] = 0;
	bzr->f1 = MAX_B_FRAMES;
	bzr->f2 = bzr->f1;	/* init F poपूर्णांकers to reमुख्य स्थिरant */
	bzr->za[MAX_B_FRAMES].z1 = cpu_to_le16(B_FIFO_SIZE + B_SUB_VAL - 1);
	bzr->za[MAX_B_FRAMES].z2 = cpu_to_le16(
		le16_to_cpu(bzr->za[MAX_B_FRAMES].z1));
	अगर (fअगरo_state)
		hc->hw.fअगरo_en |= fअगरo_state;
	Write_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fअगरo_en);
पूर्ण

/*
 * clear the desired B-channel tx fअगरo
 */
अटल व्योम hfcpci_clear_fअगरo_tx(काष्ठा hfc_pci *hc, पूर्णांक fअगरo)
अणु
	u_अक्षर		fअगरo_state;
	काष्ठा bzfअगरo	*bzt;

	अगर (fअगरo) अणु
		bzt = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.txbz_b2;
		fअगरo_state = hc->hw.fअगरo_en & HFCPCI_FIFOEN_B2TX;
	पूर्ण अन्यथा अणु
		bzt = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.txbz_b1;
		fअगरo_state = hc->hw.fअगरo_en & HFCPCI_FIFOEN_B1TX;
	पूर्ण
	अगर (fअगरo_state)
		hc->hw.fअगरo_en ^= fअगरo_state;
	Write_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fअगरo_en);
	अगर (hc->bch[fअगरo].debug & DEBUG_HW_BCHANNEL)
		prपूर्णांकk(KERN_DEBUG "hfcpci_clear_fifo_tx%d f1(%x) f2(%x) "
		       "z1(%x) z2(%x) state(%x)\n",
		       fअगरo, bzt->f1, bzt->f2,
		       le16_to_cpu(bzt->za[MAX_B_FRAMES].z1),
		       le16_to_cpu(bzt->za[MAX_B_FRAMES].z2),
		       fअगरo_state);
	bzt->f2 = MAX_B_FRAMES;
	bzt->f1 = bzt->f2;	/* init F poपूर्णांकers to reमुख्य स्थिरant */
	bzt->za[MAX_B_FRAMES].z1 = cpu_to_le16(B_FIFO_SIZE + B_SUB_VAL - 1);
	bzt->za[MAX_B_FRAMES].z2 = cpu_to_le16(B_FIFO_SIZE + B_SUB_VAL - 2);
	अगर (fअगरo_state)
		hc->hw.fअगरo_en |= fअगरo_state;
	Write_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fअगरo_en);
	अगर (hc->bch[fअगरo].debug & DEBUG_HW_BCHANNEL)
		prपूर्णांकk(KERN_DEBUG
		       "hfcpci_clear_fifo_tx%d f1(%x) f2(%x) z1(%x) z2(%x)\n",
		       fअगरo, bzt->f1, bzt->f2,
		       le16_to_cpu(bzt->za[MAX_B_FRAMES].z1),
		       le16_to_cpu(bzt->za[MAX_B_FRAMES].z2));
पूर्ण

/*
 * पढ़ो a complete B-frame out of the buffer
 */
अटल व्योम
hfcpci_empty_bfअगरo(काष्ठा bchannel *bch, काष्ठा bzfअगरo *bz,
		   u_अक्षर *bdata, पूर्णांक count)
अणु
	u_अक्षर		*ptr, *ptr1, new_f2;
	पूर्णांक		maxlen, new_z2;
	काष्ठा zt	*zp;

	अगर ((bch->debug & DEBUG_HW_BCHANNEL) && !(bch->debug & DEBUG_HW_BFIFO))
		prपूर्णांकk(KERN_DEBUG "hfcpci_empty_fifo\n");
	zp = &bz->za[bz->f2];	/* poपूर्णांक to Z-Regs */
	new_z2 = le16_to_cpu(zp->z2) + count;	/* new position in fअगरo */
	अगर (new_z2 >= (B_FIFO_SIZE + B_SUB_VAL))
		new_z2 -= B_FIFO_SIZE;	/* buffer wrap */
	new_f2 = (bz->f2 + 1) & MAX_B_FRAMES;
	अगर ((count > MAX_DATA_SIZE + 3) || (count < 4) ||
	    (*(bdata + (le16_to_cpu(zp->z1) - B_SUB_VAL)))) अणु
		अगर (bch->debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "hfcpci_empty_fifo: incoming packet "
			       "invalid length %d or crc\n", count);
#अगर_घोषित ERROR_STATISTIC
		bch->err_inv++;
#पूर्ण_अगर
		bz->za[new_f2].z2 = cpu_to_le16(new_z2);
		bz->f2 = new_f2;	/* next buffer */
	पूर्ण अन्यथा अणु
		bch->rx_skb = mI_alloc_skb(count - 3, GFP_ATOMIC);
		अगर (!bch->rx_skb) अणु
			prपूर्णांकk(KERN_WARNING "HFCPCI: receive out of memory\n");
			वापस;
		पूर्ण
		count -= 3;
		ptr = skb_put(bch->rx_skb, count);

		अगर (le16_to_cpu(zp->z2) + count <= B_FIFO_SIZE + B_SUB_VAL)
			maxlen = count;		/* complete transfer */
		अन्यथा
			maxlen = B_FIFO_SIZE + B_SUB_VAL -
				le16_to_cpu(zp->z2);	/* maximum */

		ptr1 = bdata + (le16_to_cpu(zp->z2) - B_SUB_VAL);
		/* start of data */
		स_नकल(ptr, ptr1, maxlen);	/* copy data */
		count -= maxlen;

		अगर (count) अणु	/* rest reमुख्यing */
			ptr += maxlen;
			ptr1 = bdata;	/* start of buffer */
			स_नकल(ptr, ptr1, count);	/* rest */
		पूर्ण
		bz->za[new_f2].z2 = cpu_to_le16(new_z2);
		bz->f2 = new_f2;	/* next buffer */
		recv_Bchannel(bch, MISDN_ID_ANY, false);
	पूर्ण
पूर्ण

/*
 * D-channel receive procedure
 */
अटल पूर्णांक
receive_dmsg(काष्ठा hfc_pci *hc)
अणु
	काष्ठा dchannel	*dch = &hc->dch;
	पूर्णांक		maxlen;
	पूर्णांक		rcnt, total;
	पूर्णांक		count = 5;
	u_अक्षर		*ptr, *ptr1;
	काष्ठा dfअगरo	*df;
	काष्ठा zt	*zp;

	df = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->d_chan.d_rx;
	जबतक (((df->f1 & D_FREG_MASK) != (df->f2 & D_FREG_MASK)) && count--) अणु
		zp = &df->za[df->f2 & D_FREG_MASK];
		rcnt = le16_to_cpu(zp->z1) - le16_to_cpu(zp->z2);
		अगर (rcnt < 0)
			rcnt += D_FIFO_SIZE;
		rcnt++;
		अगर (dch->debug & DEBUG_HW_DCHANNEL)
			prपूर्णांकk(KERN_DEBUG
			       "hfcpci recd f1(%d) f2(%d) z1(%x) z2(%x) cnt(%d)\n",
			       df->f1, df->f2,
			       le16_to_cpu(zp->z1),
			       le16_to_cpu(zp->z2),
			       rcnt);

		अगर ((rcnt > MAX_DFRAME_LEN + 3) || (rcnt < 4) ||
		    (df->data[le16_to_cpu(zp->z1)])) अणु
			अगर (dch->debug & DEBUG_HW)
				prपूर्णांकk(KERN_DEBUG
				       "empty_fifo hfcpci packet inv. len "
				       "%d or crc %d\n",
				       rcnt,
				       df->data[le16_to_cpu(zp->z1)]);
#अगर_घोषित ERROR_STATISTIC
			cs->err_rx++;
#पूर्ण_अगर
			df->f2 = ((df->f2 + 1) & MAX_D_FRAMES) |
				(MAX_D_FRAMES + 1);	/* next buffer */
			df->za[df->f2 & D_FREG_MASK].z2 =
				cpu_to_le16((le16_to_cpu(zp->z2) + rcnt) &
					    (D_FIFO_SIZE - 1));
		पूर्ण अन्यथा अणु
			dch->rx_skb = mI_alloc_skb(rcnt - 3, GFP_ATOMIC);
			अगर (!dch->rx_skb) अणु
				prपूर्णांकk(KERN_WARNING
				       "HFC-PCI: D receive out of memory\n");
				अवरोध;
			पूर्ण
			total = rcnt;
			rcnt -= 3;
			ptr = skb_put(dch->rx_skb, rcnt);

			अगर (le16_to_cpu(zp->z2) + rcnt <= D_FIFO_SIZE)
				maxlen = rcnt;	/* complete transfer */
			अन्यथा
				maxlen = D_FIFO_SIZE - le16_to_cpu(zp->z2);
			/* maximum */

			ptr1 = df->data + le16_to_cpu(zp->z2);
			/* start of data */
			स_नकल(ptr, ptr1, maxlen);	/* copy data */
			rcnt -= maxlen;

			अगर (rcnt) अणु	/* rest reमुख्यing */
				ptr += maxlen;
				ptr1 = df->data;	/* start of buffer */
				स_नकल(ptr, ptr1, rcnt);	/* rest */
			पूर्ण
			df->f2 = ((df->f2 + 1) & MAX_D_FRAMES) |
				(MAX_D_FRAMES + 1);	/* next buffer */
			df->za[df->f2 & D_FREG_MASK].z2 = cpu_to_le16((
									      le16_to_cpu(zp->z2) + total) & (D_FIFO_SIZE - 1));
			recv_Dchannel(dch);
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * check क्रम transparent receive data and पढ़ो max one 'poll' size अगर avail
 */
अटल व्योम
hfcpci_empty_fअगरo_trans(काष्ठा bchannel *bch, काष्ठा bzfअगरo *rxbz,
			काष्ठा bzfअगरo *txbz, u_अक्षर *bdata)
अणु
	__le16	*z1r, *z2r, *z1t, *z2t;
	पूर्णांक	new_z2, fcnt_rx, fcnt_tx, maxlen;
	u_अक्षर	*ptr, *ptr1;

	z1r = &rxbz->za[MAX_B_FRAMES].z1;	/* poपूर्णांकer to z reg */
	z2r = z1r + 1;
	z1t = &txbz->za[MAX_B_FRAMES].z1;
	z2t = z1t + 1;

	fcnt_rx = le16_to_cpu(*z1r) - le16_to_cpu(*z2r);
	अगर (!fcnt_rx)
		वापस;	/* no data avail */

	अगर (fcnt_rx <= 0)
		fcnt_rx += B_FIFO_SIZE;	/* bytes actually buffered */
	new_z2 = le16_to_cpu(*z2r) + fcnt_rx;	/* new position in fअगरo */
	अगर (new_z2 >= (B_FIFO_SIZE + B_SUB_VAL))
		new_z2 -= B_FIFO_SIZE;	/* buffer wrap */

	fcnt_tx = le16_to_cpu(*z2t) - le16_to_cpu(*z1t);
	अगर (fcnt_tx <= 0)
		fcnt_tx += B_FIFO_SIZE;
	/* fcnt_tx contains available bytes in tx-fअगरo */
	fcnt_tx = B_FIFO_SIZE - fcnt_tx;
	/* reमुख्यing bytes to send (bytes in tx-fअगरo) */

	अगर (test_bit(FLG_RX_OFF, &bch->Flags)) अणु
		bch->dropcnt += fcnt_rx;
		*z2r = cpu_to_le16(new_z2);
		वापस;
	पूर्ण
	maxlen = bchannel_get_rxbuf(bch, fcnt_rx);
	अगर (maxlen < 0) अणु
		pr_warn("B%d: No bufferspace for %d bytes\n", bch->nr, fcnt_rx);
	पूर्ण अन्यथा अणु
		ptr = skb_put(bch->rx_skb, fcnt_rx);
		अगर (le16_to_cpu(*z2r) + fcnt_rx <= B_FIFO_SIZE + B_SUB_VAL)
			maxlen = fcnt_rx;	/* complete transfer */
		अन्यथा
			maxlen = B_FIFO_SIZE + B_SUB_VAL - le16_to_cpu(*z2r);
		/* maximum */

		ptr1 = bdata + (le16_to_cpu(*z2r) - B_SUB_VAL);
		/* start of data */
		स_नकल(ptr, ptr1, maxlen);	/* copy data */
		fcnt_rx -= maxlen;

		अगर (fcnt_rx) अणु	/* rest reमुख्यing */
			ptr += maxlen;
			ptr1 = bdata;	/* start of buffer */
			स_नकल(ptr, ptr1, fcnt_rx);	/* rest */
		पूर्ण
		recv_Bchannel(bch, fcnt_tx, false); /* bch, id, !क्रमce */
	पूर्ण
	*z2r = cpu_to_le16(new_z2);		/* new position */
पूर्ण

/*
 * B-channel मुख्य receive routine
 */
अटल व्योम
मुख्य_rec_hfcpci(काष्ठा bchannel *bch)
अणु
	काष्ठा hfc_pci	*hc = bch->hw;
	पूर्णांक		rcnt, real_fअगरo;
	पूर्णांक		receive = 0, count = 5;
	काष्ठा bzfअगरo	*txbz, *rxbz;
	u_अक्षर		*bdata;
	काष्ठा zt	*zp;

	अगर ((bch->nr & 2) && (!hc->hw.bswapped)) अणु
		rxbz = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.rxbz_b2;
		txbz = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.txbz_b2;
		bdata = ((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.rxdat_b2;
		real_fअगरo = 1;
	पूर्ण अन्यथा अणु
		rxbz = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.rxbz_b1;
		txbz = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.txbz_b1;
		bdata = ((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.rxdat_b1;
		real_fअगरo = 0;
	पूर्ण
Begin:
	count--;
	अगर (rxbz->f1 != rxbz->f2) अणु
		अगर (bch->debug & DEBUG_HW_BCHANNEL)
			prपूर्णांकk(KERN_DEBUG "hfcpci rec ch(%x) f1(%d) f2(%d)\n",
			       bch->nr, rxbz->f1, rxbz->f2);
		zp = &rxbz->za[rxbz->f2];

		rcnt = le16_to_cpu(zp->z1) - le16_to_cpu(zp->z2);
		अगर (rcnt < 0)
			rcnt += B_FIFO_SIZE;
		rcnt++;
		अगर (bch->debug & DEBUG_HW_BCHANNEL)
			prपूर्णांकk(KERN_DEBUG
			       "hfcpci rec ch(%x) z1(%x) z2(%x) cnt(%d)\n",
			       bch->nr, le16_to_cpu(zp->z1),
			       le16_to_cpu(zp->z2), rcnt);
		hfcpci_empty_bfअगरo(bch, rxbz, bdata, rcnt);
		rcnt = rxbz->f1 - rxbz->f2;
		अगर (rcnt < 0)
			rcnt += MAX_B_FRAMES + 1;
		अगर (hc->hw.last_bfअगरo_cnt[real_fअगरo] > rcnt + 1) अणु
			rcnt = 0;
			hfcpci_clear_fअगरo_rx(hc, real_fअगरo);
		पूर्ण
		hc->hw.last_bfअगरo_cnt[real_fअगरo] = rcnt;
		अगर (rcnt > 1)
			receive = 1;
		अन्यथा
			receive = 0;
	पूर्ण अन्यथा अगर (test_bit(FLG_TRANSPARENT, &bch->Flags)) अणु
		hfcpci_empty_fअगरo_trans(bch, rxbz, txbz, bdata);
		वापस;
	पूर्ण अन्यथा
		receive = 0;
	अगर (count && receive)
		जाओ Begin;

पूर्ण

/*
 * D-channel send routine
 */
अटल व्योम
hfcpci_fill_dfअगरo(काष्ठा hfc_pci *hc)
अणु
	काष्ठा dchannel	*dch = &hc->dch;
	पूर्णांक		fcnt;
	पूर्णांक		count, new_z1, maxlen;
	काष्ठा dfअगरo	*df;
	u_अक्षर		*src, *dst, new_f1;

	अगर ((dch->debug & DEBUG_HW_DCHANNEL) && !(dch->debug & DEBUG_HW_DFIFO))
		prपूर्णांकk(KERN_DEBUG "%s\n", __func__);

	अगर (!dch->tx_skb)
		वापस;
	count = dch->tx_skb->len - dch->tx_idx;
	अगर (count <= 0)
		वापस;
	df = &((जोड़ fअगरo_area *) (hc->hw.fअगरos))->d_chan.d_tx;

	अगर (dch->debug & DEBUG_HW_DFIFO)
		prपूर्णांकk(KERN_DEBUG "%s:f1(%d) f2(%d) z1(f1)(%x)\n", __func__,
		       df->f1, df->f2,
		       le16_to_cpu(df->za[df->f1 & D_FREG_MASK].z1));
	fcnt = df->f1 - df->f2;	/* frame count actually buffered */
	अगर (fcnt < 0)
		fcnt += (MAX_D_FRAMES + 1);	/* अगर wrap around */
	अगर (fcnt > (MAX_D_FRAMES - 1)) अणु
		अगर (dch->debug & DEBUG_HW_DCHANNEL)
			prपूर्णांकk(KERN_DEBUG
			       "hfcpci_fill_Dfifo more as 14 frames\n");
#अगर_घोषित ERROR_STATISTIC
		cs->err_tx++;
#पूर्ण_अगर
		वापस;
	पूर्ण
	/* now determine मुक्त bytes in FIFO buffer */
	maxlen = le16_to_cpu(df->za[df->f2 & D_FREG_MASK].z2) -
		le16_to_cpu(df->za[df->f1 & D_FREG_MASK].z1) - 1;
	अगर (maxlen <= 0)
		maxlen += D_FIFO_SIZE;	/* count now contains available bytes */

	अगर (dch->debug & DEBUG_HW_DCHANNEL)
		prपूर्णांकk(KERN_DEBUG "hfcpci_fill_Dfifo count(%d/%d)\n",
		       count, maxlen);
	अगर (count > maxlen) अणु
		अगर (dch->debug & DEBUG_HW_DCHANNEL)
			prपूर्णांकk(KERN_DEBUG "hfcpci_fill_Dfifo no fifo mem\n");
		वापस;
	पूर्ण
	new_z1 = (le16_to_cpu(df->za[df->f1 & D_FREG_MASK].z1) + count) &
		(D_FIFO_SIZE - 1);
	new_f1 = ((df->f1 + 1) & D_FREG_MASK) | (D_FREG_MASK + 1);
	src = dch->tx_skb->data + dch->tx_idx;	/* source poपूर्णांकer */
	dst = df->data + le16_to_cpu(df->za[df->f1 & D_FREG_MASK].z1);
	maxlen = D_FIFO_SIZE - le16_to_cpu(df->za[df->f1 & D_FREG_MASK].z1);
	/* end fअगरo */
	अगर (maxlen > count)
		maxlen = count;	/* limit size */
	स_नकल(dst, src, maxlen);	/* first copy */

	count -= maxlen;	/* reमुख्यing bytes */
	अगर (count) अणु
		dst = df->data;	/* start of buffer */
		src += maxlen;	/* new position */
		स_नकल(dst, src, count);
	पूर्ण
	df->za[new_f1 & D_FREG_MASK].z1 = cpu_to_le16(new_z1);
	/* क्रम next buffer */
	df->za[df->f1 & D_FREG_MASK].z1 = cpu_to_le16(new_z1);
	/* new pos actual buffer */
	df->f1 = new_f1;	/* next frame */
	dch->tx_idx = dch->tx_skb->len;
पूर्ण

/*
 * B-channel send routine
 */
अटल व्योम
hfcpci_fill_fअगरo(काष्ठा bchannel *bch)
अणु
	काष्ठा hfc_pci	*hc = bch->hw;
	पूर्णांक		maxlen, fcnt;
	पूर्णांक		count, new_z1;
	काष्ठा bzfअगरo	*bz;
	u_अक्षर		*bdata;
	u_अक्षर		new_f1, *src, *dst;
	__le16 *z1t, *z2t;

	अगर ((bch->debug & DEBUG_HW_BCHANNEL) && !(bch->debug & DEBUG_HW_BFIFO))
		prपूर्णांकk(KERN_DEBUG "%s\n", __func__);
	अगर ((!bch->tx_skb) || bch->tx_skb->len == 0) अणु
		अगर (!test_bit(FLG_FILLEMPTY, &bch->Flags) &&
		    !test_bit(FLG_TRANSPARENT, &bch->Flags))
			वापस;
		count = HFCPCI_FILLEMPTY;
	पूर्ण अन्यथा अणु
		count = bch->tx_skb->len - bch->tx_idx;
	पूर्ण
	अगर ((bch->nr & 2) && (!hc->hw.bswapped)) अणु
		bz = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.txbz_b2;
		bdata = ((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.txdat_b2;
	पूर्ण अन्यथा अणु
		bz = &((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.txbz_b1;
		bdata = ((जोड़ fअगरo_area *)(hc->hw.fअगरos))->b_chans.txdat_b1;
	पूर्ण

	अगर (test_bit(FLG_TRANSPARENT, &bch->Flags)) अणु
		z1t = &bz->za[MAX_B_FRAMES].z1;
		z2t = z1t + 1;
		अगर (bch->debug & DEBUG_HW_BCHANNEL)
			prपूर्णांकk(KERN_DEBUG "hfcpci_fill_fifo_trans ch(%x) "
			       "cnt(%d) z1(%x) z2(%x)\n", bch->nr, count,
			       le16_to_cpu(*z1t), le16_to_cpu(*z2t));
		fcnt = le16_to_cpu(*z2t) - le16_to_cpu(*z1t);
		अगर (fcnt <= 0)
			fcnt += B_FIFO_SIZE;
		अगर (test_bit(FLG_FILLEMPTY, &bch->Flags)) अणु
			/* fcnt contains available bytes in fअगरo */
			अगर (count > fcnt)
				count = fcnt;
			new_z1 = le16_to_cpu(*z1t) + count;
			/* new buffer Position */
			अगर (new_z1 >= (B_FIFO_SIZE + B_SUB_VAL))
				new_z1 -= B_FIFO_SIZE;	/* buffer wrap */
			dst = bdata + (le16_to_cpu(*z1t) - B_SUB_VAL);
			maxlen = (B_FIFO_SIZE + B_SUB_VAL) - le16_to_cpu(*z1t);
			/* end of fअगरo */
			अगर (bch->debug & DEBUG_HW_BFIFO)
				prपूर्णांकk(KERN_DEBUG "hfcpci_FFt fillempty "
				       "fcnt(%d) maxl(%d) nz1(%x) dst(%p)\n",
				       fcnt, maxlen, new_z1, dst);
			अगर (maxlen > count)
				maxlen = count;		/* limit size */
			स_रखो(dst, bch->fill[0], maxlen); /* first copy */
			count -= maxlen;		/* reमुख्यing bytes */
			अगर (count) अणु
				dst = bdata;		/* start of buffer */
				स_रखो(dst, bch->fill[0], count);
			पूर्ण
			*z1t = cpu_to_le16(new_z1);	/* now send data */
			वापस;
		पूर्ण
		/* fcnt contains available bytes in fअगरo */
		fcnt = B_FIFO_SIZE - fcnt;
		/* reमुख्यing bytes to send (bytes in fअगरo) */

	next_t_frame:
		count = bch->tx_skb->len - bch->tx_idx;
		/* maximum fill shall be poll*2 */
		अगर (count > (poll << 1) - fcnt)
			count = (poll << 1) - fcnt;
		अगर (count <= 0)
			वापस;
		/* data is suitable क्रम fअगरo */
		new_z1 = le16_to_cpu(*z1t) + count;
		/* new buffer Position */
		अगर (new_z1 >= (B_FIFO_SIZE + B_SUB_VAL))
			new_z1 -= B_FIFO_SIZE;	/* buffer wrap */
		src = bch->tx_skb->data + bch->tx_idx;
		/* source poपूर्णांकer */
		dst = bdata + (le16_to_cpu(*z1t) - B_SUB_VAL);
		maxlen = (B_FIFO_SIZE + B_SUB_VAL) - le16_to_cpu(*z1t);
		/* end of fअगरo */
		अगर (bch->debug & DEBUG_HW_BFIFO)
			prपूर्णांकk(KERN_DEBUG "hfcpci_FFt fcnt(%d) "
			       "maxl(%d) nz1(%x) dst(%p)\n",
			       fcnt, maxlen, new_z1, dst);
		fcnt += count;
		bch->tx_idx += count;
		अगर (maxlen > count)
			maxlen = count;		/* limit size */
		स_नकल(dst, src, maxlen);	/* first copy */
		count -= maxlen;	/* reमुख्यing bytes */
		अगर (count) अणु
			dst = bdata;	/* start of buffer */
			src += maxlen;	/* new position */
			स_नकल(dst, src, count);
		पूर्ण
		*z1t = cpu_to_le16(new_z1);	/* now send data */
		अगर (bch->tx_idx < bch->tx_skb->len)
			वापस;
		dev_kमुक्त_skb(bch->tx_skb);
		अगर (get_next_bframe(bch))
			जाओ next_t_frame;
		वापस;
	पूर्ण
	अगर (bch->debug & DEBUG_HW_BCHANNEL)
		prपूर्णांकk(KERN_DEBUG
		       "%s: ch(%x) f1(%d) f2(%d) z1(f1)(%x)\n",
		       __func__, bch->nr, bz->f1, bz->f2,
		       bz->za[bz->f1].z1);
	fcnt = bz->f1 - bz->f2;	/* frame count actually buffered */
	अगर (fcnt < 0)
		fcnt += (MAX_B_FRAMES + 1);	/* अगर wrap around */
	अगर (fcnt > (MAX_B_FRAMES - 1)) अणु
		अगर (bch->debug & DEBUG_HW_BCHANNEL)
			prपूर्णांकk(KERN_DEBUG
			       "hfcpci_fill_Bfifo more as 14 frames\n");
		वापस;
	पूर्ण
	/* now determine मुक्त bytes in FIFO buffer */
	maxlen = le16_to_cpu(bz->za[bz->f2].z2) -
		le16_to_cpu(bz->za[bz->f1].z1) - 1;
	अगर (maxlen <= 0)
		maxlen += B_FIFO_SIZE;	/* count now contains available bytes */

	अगर (bch->debug & DEBUG_HW_BCHANNEL)
		prपूर्णांकk(KERN_DEBUG "hfcpci_fill_fifo ch(%x) count(%d/%d)\n",
		       bch->nr, count, maxlen);

	अगर (maxlen < count) अणु
		अगर (bch->debug & DEBUG_HW_BCHANNEL)
			prपूर्णांकk(KERN_DEBUG "hfcpci_fill_fifo no fifo mem\n");
		वापस;
	पूर्ण
	new_z1 = le16_to_cpu(bz->za[bz->f1].z1) + count;
	/* new buffer Position */
	अगर (new_z1 >= (B_FIFO_SIZE + B_SUB_VAL))
		new_z1 -= B_FIFO_SIZE;	/* buffer wrap */

	new_f1 = ((bz->f1 + 1) & MAX_B_FRAMES);
	src = bch->tx_skb->data + bch->tx_idx;	/* source poपूर्णांकer */
	dst = bdata + (le16_to_cpu(bz->za[bz->f1].z1) - B_SUB_VAL);
	maxlen = (B_FIFO_SIZE + B_SUB_VAL) - le16_to_cpu(bz->za[bz->f1].z1);
	/* end fअगरo */
	अगर (maxlen > count)
		maxlen = count;	/* limit size */
	स_नकल(dst, src, maxlen);	/* first copy */

	count -= maxlen;	/* reमुख्यing bytes */
	अगर (count) अणु
		dst = bdata;	/* start of buffer */
		src += maxlen;	/* new position */
		स_नकल(dst, src, count);
	पूर्ण
	bz->za[new_f1].z1 = cpu_to_le16(new_z1);	/* क्रम next buffer */
	bz->f1 = new_f1;	/* next frame */
	dev_kमुक्त_skb(bch->tx_skb);
	get_next_bframe(bch);
पूर्ण



/*
 * handle L1 state changes TE
 */

अटल व्योम
ph_state_te(काष्ठा dchannel *dch)
अणु
	अगर (dch->debug)
		prपूर्णांकk(KERN_DEBUG "%s: TE newstate %x\n",
		       __func__, dch->state);
	चयन (dch->state) अणु
	हाल 0:
		l1_event(dch->l1, HW_RESET_IND);
		अवरोध;
	हाल 3:
		l1_event(dch->l1, HW_DEACT_IND);
		अवरोध;
	हाल 5:
	हाल 8:
		l1_event(dch->l1, ANYSIGNAL);
		अवरोध;
	हाल 6:
		l1_event(dch->l1, INFO2);
		अवरोध;
	हाल 7:
		l1_event(dch->l1, INFO4_P8);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * handle L1 state changes NT
 */

अटल व्योम
handle_nt_समयr3(काष्ठा dchannel *dch) अणु
	काष्ठा hfc_pci	*hc = dch->hw;

	test_and_clear_bit(FLG_HFC_TIMER_T3, &dch->Flags);
	hc->hw.पूर्णांक_m1 &= ~HFCPCI_INTS_TIMER;
	Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
	hc->hw.nt_समयr = 0;
	test_and_set_bit(FLG_ACTIVE, &dch->Flags);
	अगर (test_bit(HFC_CFG_MASTER, &hc->cfg))
		hc->hw.mst_m |= HFCPCI_MASTER;
	Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
	_queue_data(&dch->dev.D, PH_ACTIVATE_IND,
		    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
पूर्ण

अटल व्योम
ph_state_nt(काष्ठा dchannel *dch)
अणु
	काष्ठा hfc_pci	*hc = dch->hw;

	अगर (dch->debug)
		prपूर्णांकk(KERN_DEBUG "%s: NT newstate %x\n",
		       __func__, dch->state);
	चयन (dch->state) अणु
	हाल 2:
		अगर (hc->hw.nt_समयr < 0) अणु
			hc->hw.nt_समयr = 0;
			test_and_clear_bit(FLG_HFC_TIMER_T3, &dch->Flags);
			test_and_clear_bit(FLG_HFC_TIMER_T1, &dch->Flags);
			hc->hw.पूर्णांक_m1 &= ~HFCPCI_INTS_TIMER;
			Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
			/* Clear alपढ़ोy pending पूर्णांकs */
			(व्योम) Read_hfc(hc, HFCPCI_INT_S1);
			Write_hfc(hc, HFCPCI_STATES, 4 | HFCPCI_LOAD_STATE);
			udelay(10);
			Write_hfc(hc, HFCPCI_STATES, 4);
			dch->state = 4;
		पूर्ण अन्यथा अगर (hc->hw.nt_समयr == 0) अणु
			hc->hw.पूर्णांक_m1 |= HFCPCI_INTS_TIMER;
			Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
			hc->hw.nt_समयr = NT_T1_COUNT;
			hc->hw.cपंचांगt &= ~HFCPCI_AUTO_TIMER;
			hc->hw.cपंचांगt |= HFCPCI_TIM3_125;
			Write_hfc(hc, HFCPCI_CTMT, hc->hw.cपंचांगt |
				  HFCPCI_CLTIMER);
			test_and_clear_bit(FLG_HFC_TIMER_T3, &dch->Flags);
			test_and_set_bit(FLG_HFC_TIMER_T1, &dch->Flags);
			/* allow G2 -> G3 transition */
			Write_hfc(hc, HFCPCI_STATES, 2 | HFCPCI_NT_G2_G3);
		पूर्ण अन्यथा अणु
			Write_hfc(hc, HFCPCI_STATES, 2 | HFCPCI_NT_G2_G3);
		पूर्ण
		अवरोध;
	हाल 1:
		hc->hw.nt_समयr = 0;
		test_and_clear_bit(FLG_HFC_TIMER_T3, &dch->Flags);
		test_and_clear_bit(FLG_HFC_TIMER_T1, &dch->Flags);
		hc->hw.पूर्णांक_m1 &= ~HFCPCI_INTS_TIMER;
		Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
		test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
		hc->hw.mst_m &= ~HFCPCI_MASTER;
		Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		test_and_clear_bit(FLG_L2_ACTIVATED, &dch->Flags);
		_queue_data(&dch->dev.D, PH_DEACTIVATE_IND,
			    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
		अवरोध;
	हाल 4:
		hc->hw.nt_समयr = 0;
		test_and_clear_bit(FLG_HFC_TIMER_T3, &dch->Flags);
		test_and_clear_bit(FLG_HFC_TIMER_T1, &dch->Flags);
		hc->hw.पूर्णांक_m1 &= ~HFCPCI_INTS_TIMER;
		Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
		अवरोध;
	हाल 3:
		अगर (!test_and_set_bit(FLG_HFC_TIMER_T3, &dch->Flags)) अणु
			अगर (!test_and_clear_bit(FLG_L2_ACTIVATED,
						&dch->Flags)) अणु
				handle_nt_समयr3(dch);
				अवरोध;
			पूर्ण
			test_and_clear_bit(FLG_HFC_TIMER_T1, &dch->Flags);
			hc->hw.पूर्णांक_m1 |= HFCPCI_INTS_TIMER;
			Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
			hc->hw.nt_समयr = NT_T3_COUNT;
			hc->hw.cपंचांगt &= ~HFCPCI_AUTO_TIMER;
			hc->hw.cपंचांगt |= HFCPCI_TIM3_125;
			Write_hfc(hc, HFCPCI_CTMT, hc->hw.cपंचांगt |
				  HFCPCI_CLTIMER);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
ph_state(काष्ठा dchannel *dch)
अणु
	काष्ठा hfc_pci	*hc = dch->hw;

	अगर (hc->hw.protocol == ISDN_P_NT_S0) अणु
		अगर (test_bit(FLG_HFC_TIMER_T3, &dch->Flags) &&
		    hc->hw.nt_समयr < 0)
			handle_nt_समयr3(dch);
		अन्यथा
			ph_state_nt(dch);
	पूर्ण अन्यथा
		ph_state_te(dch);
पूर्ण

/*
 * Layer 1 callback function
 */
अटल पूर्णांक
hfc_l1callback(काष्ठा dchannel *dch, u_पूर्णांक cmd)
अणु
	काष्ठा hfc_pci		*hc = dch->hw;

	चयन (cmd) अणु
	हाल INFO3_P8:
	हाल INFO3_P10:
		अगर (test_bit(HFC_CFG_MASTER, &hc->cfg))
			hc->hw.mst_m |= HFCPCI_MASTER;
		Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		अवरोध;
	हाल HW_RESET_REQ:
		Write_hfc(hc, HFCPCI_STATES, HFCPCI_LOAD_STATE | 3);
		/* HFC ST 3 */
		udelay(6);
		Write_hfc(hc, HFCPCI_STATES, 3);	/* HFC ST 2 */
		अगर (test_bit(HFC_CFG_MASTER, &hc->cfg))
			hc->hw.mst_m |= HFCPCI_MASTER;
		Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		Write_hfc(hc, HFCPCI_STATES, HFCPCI_ACTIVATE |
			  HFCPCI_DO_ACTION);
		l1_event(dch->l1, HW_POWERUP_IND);
		अवरोध;
	हाल HW_DEACT_REQ:
		hc->hw.mst_m &= ~HFCPCI_MASTER;
		Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		skb_queue_purge(&dch->squeue);
		अगर (dch->tx_skb) अणु
			dev_kमुक्त_skb(dch->tx_skb);
			dch->tx_skb = शून्य;
		पूर्ण
		dch->tx_idx = 0;
		अगर (dch->rx_skb) अणु
			dev_kमुक्त_skb(dch->rx_skb);
			dch->rx_skb = शून्य;
		पूर्ण
		test_and_clear_bit(FLG_TX_BUSY, &dch->Flags);
		अगर (test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags))
			del_समयr(&dch->समयr);
		अवरोध;
	हाल HW_POWERUP_REQ:
		Write_hfc(hc, HFCPCI_STATES, HFCPCI_DO_ACTION);
		अवरोध;
	हाल PH_ACTIVATE_IND:
		test_and_set_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, शून्य,
			    GFP_ATOMIC);
		अवरोध;
	हाल PH_DEACTIVATE_IND:
		test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, शून्य,
			    GFP_ATOMIC);
		अवरोध;
	शेष:
		अगर (dch->debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: unknown command %x\n",
			       __func__, cmd);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Interrupt handler
 */
अटल अंतरभूत व्योम
tx_birq(काष्ठा bchannel *bch)
अणु
	अगर (bch->tx_skb && bch->tx_idx < bch->tx_skb->len)
		hfcpci_fill_fअगरo(bch);
	अन्यथा अणु
		dev_kमुक्त_skb(bch->tx_skb);
		अगर (get_next_bframe(bch))
			hfcpci_fill_fअगरo(bch);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
tx_dirq(काष्ठा dchannel *dch)
अणु
	अगर (dch->tx_skb && dch->tx_idx < dch->tx_skb->len)
		hfcpci_fill_dfअगरo(dch->hw);
	अन्यथा अणु
		dev_kमुक्त_skb(dch->tx_skb);
		अगर (get_next_dframe(dch))
			hfcpci_fill_dfअगरo(dch->hw);
	पूर्ण
पूर्ण

अटल irqवापस_t
hfcpci_पूर्णांक(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	काष्ठा hfc_pci	*hc = dev_id;
	u_अक्षर		exval;
	काष्ठा bchannel	*bch;
	u_अक्षर		val, stat;

	spin_lock(&hc->lock);
	अगर (!(hc->hw.पूर्णांक_m2 & 0x08)) अणु
		spin_unlock(&hc->lock);
		वापस IRQ_NONE; /* not initialised */
	पूर्ण
	stat = Read_hfc(hc, HFCPCI_STATUS);
	अगर (HFCPCI_ANYINT & stat) अणु
		val = Read_hfc(hc, HFCPCI_INT_S1);
		अगर (hc->dch.debug & DEBUG_HW_DCHANNEL)
			prपूर्णांकk(KERN_DEBUG
			       "HFC-PCI: stat(%02x) s1(%02x)\n", stat, val);
	पूर्ण अन्यथा अणु
		/* shared */
		spin_unlock(&hc->lock);
		वापस IRQ_NONE;
	पूर्ण
	hc->irqcnt++;

	अगर (hc->dch.debug & DEBUG_HW_DCHANNEL)
		prपूर्णांकk(KERN_DEBUG "HFC-PCI irq %x\n", val);
	val &= hc->hw.पूर्णांक_m1;
	अगर (val & 0x40) अणु	/* state machine irq */
		exval = Read_hfc(hc, HFCPCI_STATES) & 0xf;
		अगर (hc->dch.debug & DEBUG_HW_DCHANNEL)
			prपूर्णांकk(KERN_DEBUG "ph_state chg %d->%d\n",
			       hc->dch.state, exval);
		hc->dch.state = exval;
		schedule_event(&hc->dch, FLG_PHCHANGE);
		val &= ~0x40;
	पूर्ण
	अगर (val & 0x80) अणु	/* समयr irq */
		अगर (hc->hw.protocol == ISDN_P_NT_S0) अणु
			अगर ((--hc->hw.nt_समयr) < 0)
				schedule_event(&hc->dch, FLG_PHCHANGE);
		पूर्ण
		val &= ~0x80;
		Write_hfc(hc, HFCPCI_CTMT, hc->hw.cपंचांगt | HFCPCI_CLTIMER);
	पूर्ण
	अगर (val & 0x08) अणु	/* B1 rx */
		bch = Sel_BCS(hc, hc->hw.bswapped ? 2 : 1);
		अगर (bch)
			मुख्य_rec_hfcpci(bch);
		अन्यथा अगर (hc->dch.debug)
			prपूर्णांकk(KERN_DEBUG "hfcpci spurious 0x08 IRQ\n");
	पूर्ण
	अगर (val & 0x10) अणु	/* B2 rx */
		bch = Sel_BCS(hc, 2);
		अगर (bch)
			मुख्य_rec_hfcpci(bch);
		अन्यथा अगर (hc->dch.debug)
			prपूर्णांकk(KERN_DEBUG "hfcpci spurious 0x10 IRQ\n");
	पूर्ण
	अगर (val & 0x01) अणु	/* B1 tx */
		bch = Sel_BCS(hc, hc->hw.bswapped ? 2 : 1);
		अगर (bch)
			tx_birq(bch);
		अन्यथा अगर (hc->dch.debug)
			prपूर्णांकk(KERN_DEBUG "hfcpci spurious 0x01 IRQ\n");
	पूर्ण
	अगर (val & 0x02) अणु	/* B2 tx */
		bch = Sel_BCS(hc, 2);
		अगर (bch)
			tx_birq(bch);
		अन्यथा अगर (hc->dch.debug)
			prपूर्णांकk(KERN_DEBUG "hfcpci spurious 0x02 IRQ\n");
	पूर्ण
	अगर (val & 0x20)		/* D rx */
		receive_dmsg(hc);
	अगर (val & 0x04) अणु	/* D tx */
		अगर (test_and_clear_bit(FLG_BUSY_TIMER, &hc->dch.Flags))
			del_समयr(&hc->dch.समयr);
		tx_dirq(&hc->dch);
	पूर्ण
	spin_unlock(&hc->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * समयr callback क्रम D-chan busy resolution. Currently no function
 */
अटल व्योम
hfcpci_dbusy_समयr(काष्ठा समयr_list *t)
अणु
पूर्ण

/*
 * activate/deactivate hardware क्रम selected channels and mode
 */
अटल पूर्णांक
mode_hfcpci(काष्ठा bchannel *bch, पूर्णांक bc, पूर्णांक protocol)
अणु
	काष्ठा hfc_pci	*hc = bch->hw;
	पूर्णांक		fअगरo2;
	u_अक्षर		rx_slot = 0, tx_slot = 0, pcm_mode;

	अगर (bch->debug & DEBUG_HW_BCHANNEL)
		prपूर्णांकk(KERN_DEBUG
		       "HFCPCI bchannel protocol %x-->%x ch %x-->%x\n",
		       bch->state, protocol, bch->nr, bc);

	fअगरo2 = bc;
	pcm_mode = (bc >> 24) & 0xff;
	अगर (pcm_mode) अणु /* PCM SLOT USE */
		अगर (!test_bit(HFC_CFG_PCM, &hc->cfg))
			prपूर्णांकk(KERN_WARNING
			       "%s: pcm channel id without HFC_CFG_PCM\n",
			       __func__);
		rx_slot = (bc >> 8) & 0xff;
		tx_slot = (bc >> 16) & 0xff;
		bc = bc & 0xff;
	पूर्ण अन्यथा अगर (test_bit(HFC_CFG_PCM, &hc->cfg) && (protocol > ISDN_P_NONE))
		prपूर्णांकk(KERN_WARNING "%s: no pcm channel id but HFC_CFG_PCM\n",
		       __func__);
	अगर (hc->chanlimit > 1) अणु
		hc->hw.bswapped = 0;	/* B1 and B2 normal mode */
		hc->hw.sctrl_e &= ~0x80;
	पूर्ण अन्यथा अणु
		अगर (bc & 2) अणु
			अगर (protocol != ISDN_P_NONE) अणु
				hc->hw.bswapped = 1; /* B1 and B2 exchanged */
				hc->hw.sctrl_e |= 0x80;
			पूर्ण अन्यथा अणु
				hc->hw.bswapped = 0; /* B1 and B2 normal mode */
				hc->hw.sctrl_e &= ~0x80;
			पूर्ण
			fअगरo2 = 1;
		पूर्ण अन्यथा अणु
			hc->hw.bswapped = 0;	/* B1 and B2 normal mode */
			hc->hw.sctrl_e &= ~0x80;
		पूर्ण
	पूर्ण
	चयन (protocol) अणु
	हाल (-1): /* used क्रम init */
		bch->state = -1;
		bch->nr = bc;
		fallthrough;
	हाल (ISDN_P_NONE):
		अगर (bch->state == ISDN_P_NONE)
			वापस 0;
		अगर (bc & 2) अणु
			hc->hw.sctrl &= ~SCTRL_B2_ENA;
			hc->hw.sctrl_r &= ~SCTRL_B2_ENA;
		पूर्ण अन्यथा अणु
			hc->hw.sctrl &= ~SCTRL_B1_ENA;
			hc->hw.sctrl_r &= ~SCTRL_B1_ENA;
		पूर्ण
		अगर (fअगरo2 & 2) अणु
			hc->hw.fअगरo_en &= ~HFCPCI_FIFOEN_B2;
			hc->hw.पूर्णांक_m1 &= ~(HFCPCI_INTS_B2TRANS |
					   HFCPCI_INTS_B2REC);
		पूर्ण अन्यथा अणु
			hc->hw.fअगरo_en &= ~HFCPCI_FIFOEN_B1;
			hc->hw.पूर्णांक_m1 &= ~(HFCPCI_INTS_B1TRANS |
					   HFCPCI_INTS_B1REC);
		पूर्ण
#अगर_घोषित REVERSE_BITORDER
		अगर (bch->nr & 2)
			hc->hw.cirm &= 0x7f;
		अन्यथा
			hc->hw.cirm &= 0xbf;
#पूर्ण_अगर
		bch->state = ISDN_P_NONE;
		bch->nr = bc;
		test_and_clear_bit(FLG_HDLC, &bch->Flags);
		test_and_clear_bit(FLG_TRANSPARENT, &bch->Flags);
		अवरोध;
	हाल (ISDN_P_B_RAW):
		bch->state = protocol;
		bch->nr = bc;
		hfcpci_clear_fअगरo_rx(hc, (fअगरo2 & 2) ? 1 : 0);
		hfcpci_clear_fअगरo_tx(hc, (fअगरo2 & 2) ? 1 : 0);
		अगर (bc & 2) अणु
			hc->hw.sctrl |= SCTRL_B2_ENA;
			hc->hw.sctrl_r |= SCTRL_B2_ENA;
#अगर_घोषित REVERSE_BITORDER
			hc->hw.cirm |= 0x80;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			hc->hw.sctrl |= SCTRL_B1_ENA;
			hc->hw.sctrl_r |= SCTRL_B1_ENA;
#अगर_घोषित REVERSE_BITORDER
			hc->hw.cirm |= 0x40;
#पूर्ण_अगर
		पूर्ण
		अगर (fअगरo2 & 2) अणु
			hc->hw.fअगरo_en |= HFCPCI_FIFOEN_B2;
			अगर (!tics)
				hc->hw.पूर्णांक_m1 |= (HFCPCI_INTS_B2TRANS |
						  HFCPCI_INTS_B2REC);
			hc->hw.cपंचांगt |= 2;
			hc->hw.conn &= ~0x18;
		पूर्ण अन्यथा अणु
			hc->hw.fअगरo_en |= HFCPCI_FIFOEN_B1;
			अगर (!tics)
				hc->hw.पूर्णांक_m1 |= (HFCPCI_INTS_B1TRANS |
						  HFCPCI_INTS_B1REC);
			hc->hw.cपंचांगt |= 1;
			hc->hw.conn &= ~0x03;
		पूर्ण
		test_and_set_bit(FLG_TRANSPARENT, &bch->Flags);
		अवरोध;
	हाल (ISDN_P_B_HDLC):
		bch->state = protocol;
		bch->nr = bc;
		hfcpci_clear_fअगरo_rx(hc, (fअगरo2 & 2) ? 1 : 0);
		hfcpci_clear_fअगरo_tx(hc, (fअगरo2 & 2) ? 1 : 0);
		अगर (bc & 2) अणु
			hc->hw.sctrl |= SCTRL_B2_ENA;
			hc->hw.sctrl_r |= SCTRL_B2_ENA;
		पूर्ण अन्यथा अणु
			hc->hw.sctrl |= SCTRL_B1_ENA;
			hc->hw.sctrl_r |= SCTRL_B1_ENA;
		पूर्ण
		अगर (fअगरo2 & 2) अणु
			hc->hw.last_bfअगरo_cnt[1] = 0;
			hc->hw.fअगरo_en |= HFCPCI_FIFOEN_B2;
			hc->hw.पूर्णांक_m1 |= (HFCPCI_INTS_B2TRANS |
					  HFCPCI_INTS_B2REC);
			hc->hw.cपंचांगt &= ~2;
			hc->hw.conn &= ~0x18;
		पूर्ण अन्यथा अणु
			hc->hw.last_bfअगरo_cnt[0] = 0;
			hc->hw.fअगरo_en |= HFCPCI_FIFOEN_B1;
			hc->hw.पूर्णांक_m1 |= (HFCPCI_INTS_B1TRANS |
					  HFCPCI_INTS_B1REC);
			hc->hw.cपंचांगt &= ~1;
			hc->hw.conn &= ~0x03;
		पूर्ण
		test_and_set_bit(FLG_HDLC, &bch->Flags);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "prot not known %x\n", protocol);
		वापस -ENOPROTOOPT;
	पूर्ण
	अगर (test_bit(HFC_CFG_PCM, &hc->cfg)) अणु
		अगर ((protocol == ISDN_P_NONE) ||
		    (protocol == -1)) अणु	/* init हाल */
			rx_slot = 0;
			tx_slot = 0;
		पूर्ण अन्यथा अणु
			अगर (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg)) अणु
				rx_slot |= 0xC0;
				tx_slot |= 0xC0;
			पूर्ण अन्यथा अणु
				rx_slot |= 0x80;
				tx_slot |= 0x80;
			पूर्ण
		पूर्ण
		अगर (bc & 2) अणु
			hc->hw.conn &= 0xc7;
			hc->hw.conn |= 0x08;
			prपूर्णांकk(KERN_DEBUG "%s: Write_hfc: B2_SSL 0x%x\n",
			       __func__, tx_slot);
			prपूर्णांकk(KERN_DEBUG "%s: Write_hfc: B2_RSL 0x%x\n",
			       __func__, rx_slot);
			Write_hfc(hc, HFCPCI_B2_SSL, tx_slot);
			Write_hfc(hc, HFCPCI_B2_RSL, rx_slot);
		पूर्ण अन्यथा अणु
			hc->hw.conn &= 0xf8;
			hc->hw.conn |= 0x01;
			prपूर्णांकk(KERN_DEBUG "%s: Write_hfc: B1_SSL 0x%x\n",
			       __func__, tx_slot);
			prपूर्णांकk(KERN_DEBUG "%s: Write_hfc: B1_RSL 0x%x\n",
			       __func__, rx_slot);
			Write_hfc(hc, HFCPCI_B1_SSL, tx_slot);
			Write_hfc(hc, HFCPCI_B1_RSL, rx_slot);
		पूर्ण
	पूर्ण
	Write_hfc(hc, HFCPCI_SCTRL_E, hc->hw.sctrl_e);
	Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
	Write_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fअगरo_en);
	Write_hfc(hc, HFCPCI_SCTRL, hc->hw.sctrl);
	Write_hfc(hc, HFCPCI_SCTRL_R, hc->hw.sctrl_r);
	Write_hfc(hc, HFCPCI_CTMT, hc->hw.cपंचांगt);
	Write_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
#अगर_घोषित REVERSE_BITORDER
	Write_hfc(hc, HFCPCI_CIRM, hc->hw.cirm);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक
set_hfcpci_rxtest(काष्ठा bchannel *bch, पूर्णांक protocol, पूर्णांक chan)
अणु
	काष्ठा hfc_pci	*hc = bch->hw;

	अगर (bch->debug & DEBUG_HW_BCHANNEL)
		prपूर्णांकk(KERN_DEBUG
		       "HFCPCI bchannel test rx protocol %x-->%x ch %x-->%x\n",
		       bch->state, protocol, bch->nr, chan);
	अगर (bch->nr != chan) अणु
		prपूर्णांकk(KERN_DEBUG
		       "HFCPCI rxtest wrong channel parameter %x/%x\n",
		       bch->nr, chan);
		वापस -EINVAL;
	पूर्ण
	चयन (protocol) अणु
	हाल (ISDN_P_B_RAW):
		bch->state = protocol;
		hfcpci_clear_fअगरo_rx(hc, (chan & 2) ? 1 : 0);
		अगर (chan & 2) अणु
			hc->hw.sctrl_r |= SCTRL_B2_ENA;
			hc->hw.fअगरo_en |= HFCPCI_FIFOEN_B2RX;
			अगर (!tics)
				hc->hw.पूर्णांक_m1 |= HFCPCI_INTS_B2REC;
			hc->hw.cपंचांगt |= 2;
			hc->hw.conn &= ~0x18;
#अगर_घोषित REVERSE_BITORDER
			hc->hw.cirm |= 0x80;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			hc->hw.sctrl_r |= SCTRL_B1_ENA;
			hc->hw.fअगरo_en |= HFCPCI_FIFOEN_B1RX;
			अगर (!tics)
				hc->hw.पूर्णांक_m1 |= HFCPCI_INTS_B1REC;
			hc->hw.cपंचांगt |= 1;
			hc->hw.conn &= ~0x03;
#अगर_घोषित REVERSE_BITORDER
			hc->hw.cirm |= 0x40;
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	हाल (ISDN_P_B_HDLC):
		bch->state = protocol;
		hfcpci_clear_fअगरo_rx(hc, (chan & 2) ? 1 : 0);
		अगर (chan & 2) अणु
			hc->hw.sctrl_r |= SCTRL_B2_ENA;
			hc->hw.last_bfअगरo_cnt[1] = 0;
			hc->hw.fअगरo_en |= HFCPCI_FIFOEN_B2RX;
			hc->hw.पूर्णांक_m1 |= HFCPCI_INTS_B2REC;
			hc->hw.cपंचांगt &= ~2;
			hc->hw.conn &= ~0x18;
		पूर्ण अन्यथा अणु
			hc->hw.sctrl_r |= SCTRL_B1_ENA;
			hc->hw.last_bfअगरo_cnt[0] = 0;
			hc->hw.fअगरo_en |= HFCPCI_FIFOEN_B1RX;
			hc->hw.पूर्णांक_m1 |= HFCPCI_INTS_B1REC;
			hc->hw.cपंचांगt &= ~1;
			hc->hw.conn &= ~0x03;
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "prot not known %x\n", protocol);
		वापस -ENOPROTOOPT;
	पूर्ण
	Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
	Write_hfc(hc, HFCPCI_FIFO_EN, hc->hw.fअगरo_en);
	Write_hfc(hc, HFCPCI_SCTRL_R, hc->hw.sctrl_r);
	Write_hfc(hc, HFCPCI_CTMT, hc->hw.cपंचांगt);
	Write_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
#अगर_घोषित REVERSE_BITORDER
	Write_hfc(hc, HFCPCI_CIRM, hc->hw.cirm);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम
deactivate_bchannel(काष्ठा bchannel *bch)
अणु
	काष्ठा hfc_pci	*hc = bch->hw;
	u_दीर्घ		flags;

	spin_lock_irqsave(&hc->lock, flags);
	mISDN_clear_bchannel(bch);
	mode_hfcpci(bch, bch->nr, ISDN_P_NONE);
	spin_unlock_irqrestore(&hc->lock, flags);
पूर्ण

/*
 * Layer 1 B-channel hardware access
 */
अटल पूर्णांक
channel_bctrl(काष्ठा bchannel *bch, काष्ठा mISDN_ctrl_req *cq)
अणु
	वापस mISDN_ctrl_bchannel(bch, cq);
पूर्ण
अटल पूर्णांक
hfc_bctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा bchannel	*bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा hfc_pci	*hc = bch->hw;
	पूर्णांक		ret = -EINVAL;
	u_दीर्घ		flags;

	अगर (bch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: cmd:%x %p\n", __func__, cmd, arg);
	चयन (cmd) अणु
	हाल HW_TESTRX_RAW:
		spin_lock_irqsave(&hc->lock, flags);
		ret = set_hfcpci_rxtest(bch, ISDN_P_B_RAW, (पूर्णांक)(दीर्घ)arg);
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	हाल HW_TESTRX_HDLC:
		spin_lock_irqsave(&hc->lock, flags);
		ret = set_hfcpci_rxtest(bch, ISDN_P_B_HDLC, (पूर्णांक)(दीर्घ)arg);
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	हाल HW_TESTRX_OFF:
		spin_lock_irqsave(&hc->lock, flags);
		mode_hfcpci(bch, bch->nr, ISDN_P_NONE);
		spin_unlock_irqrestore(&hc->lock, flags);
		ret = 0;
		अवरोध;
	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		deactivate_bchannel(bch);
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(THIS_MODULE);
		ret = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		ret = channel_bctrl(bch, arg);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown prim(%x)\n",
		       __func__, cmd);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Layer2 -> Layer 1 Dchannel data
 */
अटल पूर्णांक
hfcpci_l2l1D(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा hfc_pci		*hc = dch->hw;
	पूर्णांक			ret = -EINVAL;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	अचिन्हित पूर्णांक		id;
	u_दीर्घ			flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(&hc->lock, flags);
		ret = dchannel_senddata(dch, skb);
		अगर (ret > 0) अणु /* direct TX */
			id = hh->id; /* skb can be मुक्तd */
			hfcpci_fill_dfअगरo(dch->hw);
			ret = 0;
			spin_unlock_irqrestore(&hc->lock, flags);
			queue_ch_frame(ch, PH_DATA_CNF, id, शून्य);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&hc->lock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		spin_lock_irqsave(&hc->lock, flags);
		अगर (hc->hw.protocol == ISDN_P_NT_S0) अणु
			ret = 0;
			अगर (test_bit(HFC_CFG_MASTER, &hc->cfg))
				hc->hw.mst_m |= HFCPCI_MASTER;
			Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
			अगर (test_bit(FLG_ACTIVE, &dch->Flags)) अणु
				spin_unlock_irqrestore(&hc->lock, flags);
				_queue_data(&dch->dev.D, PH_ACTIVATE_IND,
					    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
				अवरोध;
			पूर्ण
			test_and_set_bit(FLG_L2_ACTIVATED, &dch->Flags);
			Write_hfc(hc, HFCPCI_STATES, HFCPCI_ACTIVATE |
				  HFCPCI_DO_ACTION | 1);
		पूर्ण अन्यथा
			ret = l1_event(dch->l1, hh->prim);
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		test_and_clear_bit(FLG_L2_ACTIVATED, &dch->Flags);
		spin_lock_irqsave(&hc->lock, flags);
		अगर (hc->hw.protocol == ISDN_P_NT_S0) अणु
			/* prepare deactivation */
			Write_hfc(hc, HFCPCI_STATES, 0x40);
			skb_queue_purge(&dch->squeue);
			अगर (dch->tx_skb) अणु
				dev_kमुक्त_skb(dch->tx_skb);
				dch->tx_skb = शून्य;
			पूर्ण
			dch->tx_idx = 0;
			अगर (dch->rx_skb) अणु
				dev_kमुक्त_skb(dch->rx_skb);
				dch->rx_skb = शून्य;
			पूर्ण
			test_and_clear_bit(FLG_TX_BUSY, &dch->Flags);
			अगर (test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags))
				del_समयr(&dch->समयr);
#अगर_घोषित FIXME
			अगर (test_and_clear_bit(FLG_L1_BUSY, &dch->Flags))
				dchannel_sched_event(&hc->dch, D_CLEARBUSY);
#पूर्ण_अगर
			hc->hw.mst_m &= ~HFCPCI_MASTER;
			Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = l1_event(dch->l1, hh->prim);
		पूर्ण
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

/*
 * Layer2 -> Layer 1 Bchannel data
 */
अटल पूर्णांक
hfcpci_l2l1B(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा bchannel		*bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा hfc_pci		*hc = bch->hw;
	पूर्णांक			ret = -EINVAL;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	अचिन्हित दीर्घ		flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		spin_lock_irqsave(&hc->lock, flags);
		ret = bchannel_senddata(bch, skb);
		अगर (ret > 0) अणु /* direct TX */
			hfcpci_fill_fअगरo(bch);
			ret = 0;
		पूर्ण
		spin_unlock_irqrestore(&hc->lock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		spin_lock_irqsave(&hc->lock, flags);
		अगर (!test_and_set_bit(FLG_ACTIVE, &bch->Flags))
			ret = mode_hfcpci(bch, bch->nr, ch->protocol);
		अन्यथा
			ret = 0;
		spin_unlock_irqrestore(&hc->lock, flags);
		अगर (!ret)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    शून्य, GFP_KERNEL);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		deactivate_bchannel(bch);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_KERNEL);
		ret = 0;
		अवरोध;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

/*
 * called क्रम card init message
 */

अटल व्योम
inithfcpci(काष्ठा hfc_pci *hc)
अणु
	prपूर्णांकk(KERN_DEBUG "inithfcpci: entered\n");
	समयr_setup(&hc->dch.समयr, hfcpci_dbusy_समयr, 0);
	hc->chanlimit = 2;
	mode_hfcpci(&hc->bch[0], 1, -1);
	mode_hfcpci(&hc->bch[1], 2, -1);
पूर्ण


अटल पूर्णांक
init_card(काष्ठा hfc_pci *hc)
अणु
	पूर्णांक	cnt = 3;
	u_दीर्घ	flags;

	prपूर्णांकk(KERN_DEBUG "init_card: entered\n");


	spin_lock_irqsave(&hc->lock, flags);
	disable_hwirq(hc);
	spin_unlock_irqrestore(&hc->lock, flags);
	अगर (request_irq(hc->irq, hfcpci_पूर्णांक, IRQF_SHARED, "HFC PCI", hc)) अणु
		prपूर्णांकk(KERN_WARNING
		       "mISDN: couldn't get interrupt %d\n", hc->irq);
		वापस -EIO;
	पूर्ण
	spin_lock_irqsave(&hc->lock, flags);
	reset_hfcpci(hc);
	जबतक (cnt) अणु
		inithfcpci(hc);
		/*
		 * Finally enable IRQ output
		 * this is only allowed, अगर an IRQ routine is alपढ़ोy
		 * established क्रम this HFC, so करोn't करो that earlier
		 */
		enable_hwirq(hc);
		spin_unlock_irqrestore(&hc->lock, flags);
		/* Timeout 80ms */
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout((80 * HZ) / 1000);
		prपूर्णांकk(KERN_INFO "HFC PCI: IRQ %d count %d\n",
		       hc->irq, hc->irqcnt);
		/* now चयन समयr पूर्णांकerrupt off */
		spin_lock_irqsave(&hc->lock, flags);
		hc->hw.पूर्णांक_m1 &= ~HFCPCI_INTS_TIMER;
		Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
		/* reinit mode reg */
		Write_hfc(hc, HFCPCI_MST_MODE, hc->hw.mst_m);
		अगर (!hc->irqcnt) अणु
			prपूर्णांकk(KERN_WARNING
			       "HFC PCI: IRQ(%d) getting no interrupts "
			       "during init %d\n", hc->irq, 4 - cnt);
			अगर (cnt == 1)
				अवरोध;
			अन्यथा अणु
				reset_hfcpci(hc);
				cnt--;
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&hc->lock, flags);
			hc->initकरोne = 1;
			वापस 0;
		पूर्ण
	पूर्ण
	disable_hwirq(hc);
	spin_unlock_irqrestore(&hc->lock, flags);
	मुक्त_irq(hc->irq, hc);
	वापस -EIO;
पूर्ण

अटल पूर्णांक
channel_ctrl(काष्ठा hfc_pci *hc, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक	ret = 0;
	u_अक्षर	slot;

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_LOOP | MISDN_CTRL_CONNECT |
			 MISDN_CTRL_DISCONNECT | MISDN_CTRL_L1_TIMER3;
		अवरोध;
	हाल MISDN_CTRL_LOOP:
		/* channel 0 disabled loop */
		अगर (cq->channel < 0 || cq->channel > 2) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (cq->channel & 1) अणु
			अगर (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg))
				slot = 0xC0;
			अन्यथा
				slot = 0x80;
			prपूर्णांकk(KERN_DEBUG "%s: Write_hfc: B1_SSL/RSL 0x%x\n",
			       __func__, slot);
			Write_hfc(hc, HFCPCI_B1_SSL, slot);
			Write_hfc(hc, HFCPCI_B1_RSL, slot);
			hc->hw.conn = (hc->hw.conn & ~7) | 6;
			Write_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
		पूर्ण
		अगर (cq->channel & 2) अणु
			अगर (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg))
				slot = 0xC1;
			अन्यथा
				slot = 0x81;
			prपूर्णांकk(KERN_DEBUG "%s: Write_hfc: B2_SSL/RSL 0x%x\n",
			       __func__, slot);
			Write_hfc(hc, HFCPCI_B2_SSL, slot);
			Write_hfc(hc, HFCPCI_B2_RSL, slot);
			hc->hw.conn = (hc->hw.conn & ~0x38) | 0x30;
			Write_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
		पूर्ण
		अगर (cq->channel & 3)
			hc->hw.trm |= 0x80;	/* enable IOM-loop */
		अन्यथा अणु
			hc->hw.conn = (hc->hw.conn & ~0x3f) | 0x09;
			Write_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
			hc->hw.trm &= 0x7f;	/* disable IOM-loop */
		पूर्ण
		Write_hfc(hc, HFCPCI_TRM, hc->hw.trm);
		अवरोध;
	हाल MISDN_CTRL_CONNECT:
		अगर (cq->channel == cq->p1) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (cq->channel < 1 || cq->channel > 2 ||
		    cq->p1 < 1 || cq->p1 > 2) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg))
			slot = 0xC0;
		अन्यथा
			slot = 0x80;
		prपूर्णांकk(KERN_DEBUG "%s: Write_hfc: B1_SSL/RSL 0x%x\n",
		       __func__, slot);
		Write_hfc(hc, HFCPCI_B1_SSL, slot);
		Write_hfc(hc, HFCPCI_B2_RSL, slot);
		अगर (test_bit(HFC_CFG_SW_DD_DU, &hc->cfg))
			slot = 0xC1;
		अन्यथा
			slot = 0x81;
		prपूर्णांकk(KERN_DEBUG "%s: Write_hfc: B2_SSL/RSL 0x%x\n",
		       __func__, slot);
		Write_hfc(hc, HFCPCI_B2_SSL, slot);
		Write_hfc(hc, HFCPCI_B1_RSL, slot);
		hc->hw.conn = (hc->hw.conn & ~0x3f) | 0x36;
		Write_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
		hc->hw.trm |= 0x80;
		Write_hfc(hc, HFCPCI_TRM, hc->hw.trm);
		अवरोध;
	हाल MISDN_CTRL_DISCONNECT:
		hc->hw.conn = (hc->hw.conn & ~0x3f) | 0x09;
		Write_hfc(hc, HFCPCI_CONNECT, hc->hw.conn);
		hc->hw.trm &= 0x7f;	/* disable IOM-loop */
		अवरोध;
	हाल MISDN_CTRL_L1_TIMER3:
		ret = l1_event(hc->dch.l1, HW_TIMER3_VALUE | (cq->p1 & 0xff));
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown Op %x\n",
		       __func__, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
खोलो_dchannel(काष्ठा hfc_pci *hc, काष्ठा mISDNchannel *ch,
	      काष्ठा channel_req *rq)
अणु
	पूर्णांक err = 0;

	अगर (debug & DEBUG_HW_OPEN)
		prपूर्णांकk(KERN_DEBUG "%s: dev(%d) open from %p\n", __func__,
		       hc->dch.dev.id, __builtin_वापस_address(0));
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	अगर (rq->adr.channel == 1) अणु
		/* TODO: E-Channel */
		वापस -EINVAL;
	पूर्ण
	अगर (!hc->initकरोne) अणु
		अगर (rq->protocol == ISDN_P_TE_S0) अणु
			err = create_l1(&hc->dch, hfc_l1callback);
			अगर (err)
				वापस err;
		पूर्ण
		hc->hw.protocol = rq->protocol;
		ch->protocol = rq->protocol;
		err = init_card(hc);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		अगर (rq->protocol != ch->protocol) अणु
			अगर (hc->hw.protocol == ISDN_P_TE_S0)
				l1_event(hc->dch.l1, CLOSE_CHANNEL);
			अगर (rq->protocol == ISDN_P_TE_S0) अणु
				err = create_l1(&hc->dch, hfc_l1callback);
				अगर (err)
					वापस err;
			पूर्ण
			hc->hw.protocol = rq->protocol;
			ch->protocol = rq->protocol;
			hfcpci_seपंचांगode(hc);
		पूर्ण
	पूर्ण

	अगर (((ch->protocol == ISDN_P_NT_S0) && (hc->dch.state == 3)) ||
	    ((ch->protocol == ISDN_P_TE_S0) && (hc->dch.state == 7))) अणु
		_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, शून्य, GFP_KERNEL);
	पूर्ण
	rq->ch = ch;
	अगर (!try_module_get(THIS_MODULE))
		prपूर्णांकk(KERN_WARNING "%s:cannot get module\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक
खोलो_bchannel(काष्ठा hfc_pci *hc, काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel		*bch;

	अगर (rq->adr.channel == 0 || rq->adr.channel > 2)
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	bch = &hc->bch[rq->adr.channel - 1];
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch; /* TODO: E-channel */
	अगर (!try_module_get(THIS_MODULE))
		prपूर्णांकk(KERN_WARNING "%s:cannot get module\n", __func__);
	वापस 0;
पूर्ण

/*
 * device control function
 */
अटल पूर्णांक
hfc_dctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा hfc_pci		*hc = dch->hw;
	काष्ठा channel_req	*rq;
	पूर्णांक			err = 0;

	अगर (dch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		अगर ((rq->protocol == ISDN_P_TE_S0) ||
		    (rq->protocol == ISDN_P_NT_S0))
			err = खोलो_dchannel(hc, ch, rq);
		अन्यथा
			err = खोलो_bchannel(hc, rq);
		अवरोध;
	हाल CLOSE_CHANNEL:
		अगर (debug & DEBUG_HW_OPEN)
			prपूर्णांकk(KERN_DEBUG "%s: dev(%d) close from %p\n",
			       __func__, hc->dch.dev.id,
			       __builtin_वापस_address(0));
		module_put(THIS_MODULE);
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_ctrl(hc, arg);
		अवरोध;
	शेष:
		अगर (dch->debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: unknown command %x\n",
			       __func__, cmd);
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
setup_hw(काष्ठा hfc_pci *hc)
अणु
	व्योम	*buffer;

	prपूर्णांकk(KERN_INFO "mISDN: HFC-PCI driver %s\n", hfcpci_revision);
	hc->hw.cirm = 0;
	hc->dch.state = 0;
	pci_set_master(hc->pdev);
	अगर (!hc->irq) अणु
		prपूर्णांकk(KERN_WARNING "HFC-PCI: No IRQ for PCI card found\n");
		वापस 1;
	पूर्ण
	hc->hw.pci_io =
		(अक्षर __iomem *)(अचिन्हित दीर्घ)hc->pdev->resource[1].start;

	अगर (!hc->hw.pci_io) अणु
		prपूर्णांकk(KERN_WARNING "HFC-PCI: No IO-Mem for PCI card found\n");
		वापस 1;
	पूर्ण
	/* Allocate memory क्रम FIFOS */
	/* the memory needs to be on a 32k boundary within the first 4G */
	dma_set_mask(&hc->pdev->dev, 0xFFFF8000);
	buffer = dma_alloc_coherent(&hc->pdev->dev, 0x8000, &hc->hw.dmahandle,
				    GFP_KERNEL);
	/* We silently assume the address is okay अगर nonzero */
	अगर (!buffer) अणु
		prपूर्णांकk(KERN_WARNING
		       "HFC-PCI: Error allocating memory for FIFO!\n");
		वापस 1;
	पूर्ण
	hc->hw.fअगरos = buffer;
	pci_ग_लिखो_config_dword(hc->pdev, 0x80, hc->hw.dmahandle);
	hc->hw.pci_io = ioremap((uदीर्घ) hc->hw.pci_io, 256);
	अगर (unlikely(!hc->hw.pci_io)) अणु
		prपूर्णांकk(KERN_WARNING
		       "HFC-PCI: Error in ioremap for PCI!\n");
		dma_मुक्त_coherent(&hc->pdev->dev, 0x8000, hc->hw.fअगरos,
				  hc->hw.dmahandle);
		वापस 1;
	पूर्ण

	prपूर्णांकk(KERN_INFO
	       "HFC-PCI: defined at mem %#lx fifo %p(%pad) IRQ %d HZ %d\n",
	       (u_दीर्घ) hc->hw.pci_io, hc->hw.fअगरos,
	       &hc->hw.dmahandle, hc->irq, HZ);

	/* enable memory mapped ports, disable busmaster */
	pci_ग_लिखो_config_word(hc->pdev, PCI_COMMAND, PCI_ENA_MEMIO);
	hc->hw.पूर्णांक_m2 = 0;
	disable_hwirq(hc);
	hc->hw.पूर्णांक_m1 = 0;
	Write_hfc(hc, HFCPCI_INT_M1, hc->hw.पूर्णांक_m1);
	/* At this poपूर्णांक the needed PCI config is करोne */
	/* fअगरos are still not enabled */
	समयr_setup(&hc->hw.समयr, hfcpci_Timer, 0);
	/* शेष PCM master */
	test_and_set_bit(HFC_CFG_MASTER, &hc->cfg);
	वापस 0;
पूर्ण

अटल व्योम
release_card(काष्ठा hfc_pci *hc) अणु
	u_दीर्घ	flags;

	spin_lock_irqsave(&hc->lock, flags);
	hc->hw.पूर्णांक_m2 = 0; /* पूर्णांकerrupt output off ! */
	disable_hwirq(hc);
	mode_hfcpci(&hc->bch[0], 1, ISDN_P_NONE);
	mode_hfcpci(&hc->bch[1], 2, ISDN_P_NONE);
	अगर (hc->dch.समयr.function != शून्य) अणु
		del_समयr(&hc->dch.समयr);
		hc->dch.समयr.function = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&hc->lock, flags);
	अगर (hc->hw.protocol == ISDN_P_TE_S0)
		l1_event(hc->dch.l1, CLOSE_CHANNEL);
	अगर (hc->initकरोne)
		मुक्त_irq(hc->irq, hc);
	release_io_hfcpci(hc); /* must release after मुक्त_irq! */
	mISDN_unरेजिस्टर_device(&hc->dch.dev);
	mISDN_मुक्तbchannel(&hc->bch[1]);
	mISDN_मुक्तbchannel(&hc->bch[0]);
	mISDN_मुक्तdchannel(&hc->dch);
	pci_set_drvdata(hc->pdev, शून्य);
	kमुक्त(hc);
पूर्ण

अटल पूर्णांक
setup_card(काष्ठा hfc_pci *card)
अणु
	पूर्णांक		err = -EINVAL;
	u_पूर्णांक		i;
	अक्षर		name[MISDN_MAX_IDLEN];

	card->dch.debug = debug;
	spin_lock_init(&card->lock);
	mISDN_initdchannel(&card->dch, MAX_DFRAME_LEN_L1, ph_state);
	card->dch.hw = card;
	card->dch.dev.Dprotocols = (1 << ISDN_P_TE_S0) | (1 << ISDN_P_NT_S0);
	card->dch.dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	card->dch.dev.D.send = hfcpci_l2l1D;
	card->dch.dev.D.ctrl = hfc_dctrl;
	card->dch.dev.nrbchan = 2;
	क्रम (i = 0; i < 2; i++) अणु
		card->bch[i].nr = i + 1;
		set_channelmap(i + 1, card->dch.dev.channelmap);
		card->bch[i].debug = debug;
		mISDN_initbchannel(&card->bch[i], MAX_DATA_MEM, poll >> 1);
		card->bch[i].hw = card;
		card->bch[i].ch.send = hfcpci_l2l1B;
		card->bch[i].ch.ctrl = hfc_bctrl;
		card->bch[i].ch.nr = i + 1;
		list_add(&card->bch[i].ch.list, &card->dch.dev.bchannels);
	पूर्ण
	err = setup_hw(card);
	अगर (err)
		जाओ error;
	snम_लिखो(name, MISDN_MAX_IDLEN - 1, "hfc-pci.%d", HFC_cnt + 1);
	err = mISDN_रेजिस्टर_device(&card->dch.dev, &card->pdev->dev, name);
	अगर (err)
		जाओ error;
	HFC_cnt++;
	prपूर्णांकk(KERN_INFO "HFC %d cards installed\n", HFC_cnt);
	वापस 0;
error:
	mISDN_मुक्तbchannel(&card->bch[1]);
	mISDN_मुक्तbchannel(&card->bch[0]);
	mISDN_मुक्तdchannel(&card->dch);
	kमुक्त(card);
	वापस err;
पूर्ण

/* निजी data in the PCI devices list */
काष्ठा _hfc_map अणु
	u_पूर्णांक	subtype;
	u_पूर्णांक	flag;
	अक्षर	*name;
पूर्ण;

अटल स्थिर काष्ठा _hfc_map hfc_map[] =
अणु
	अणुHFC_CCD_2BD0, 0, "CCD/Billion/Asuscom 2BD0"पूर्ण,
	अणुHFC_CCD_B000, 0, "Billion B000"पूर्ण,
	अणुHFC_CCD_B006, 0, "Billion B006"पूर्ण,
	अणुHFC_CCD_B007, 0, "Billion B007"पूर्ण,
	अणुHFC_CCD_B008, 0, "Billion B008"पूर्ण,
	अणुHFC_CCD_B009, 0, "Billion B009"पूर्ण,
	अणुHFC_CCD_B00A, 0, "Billion B00A"पूर्ण,
	अणुHFC_CCD_B00B, 0, "Billion B00B"पूर्ण,
	अणुHFC_CCD_B00C, 0, "Billion B00C"पूर्ण,
	अणुHFC_CCD_B100, 0, "Seyeon B100"पूर्ण,
	अणुHFC_CCD_B700, 0, "Primux II S0 B700"पूर्ण,
	अणुHFC_CCD_B701, 0, "Primux II S0 NT B701"पूर्ण,
	अणुHFC_ABOCOM_2BD1, 0, "Abocom/Magitek 2BD1"पूर्ण,
	अणुHFC_ASUS_0675, 0, "Asuscom/Askey 675"पूर्ण,
	अणुHFC_BERKOM_TCONCEPT, 0, "German telekom T-Concept"पूर्ण,
	अणुHFC_BERKOM_A1T, 0, "German telekom A1T"पूर्ण,
	अणुHFC_ANIGMA_MC145575, 0, "Motorola MC145575"पूर्ण,
	अणुHFC_ZOLTRIX_2BD0, 0, "Zoltrix 2BD0"पूर्ण,
	अणुHFC_DIGI_DF_M_IOM2_E, 0,
	 "Digi International DataFire Micro V IOM2 (Europe)"पूर्ण,
	अणुHFC_DIGI_DF_M_E, 0,
	 "Digi International DataFire Micro V (Europe)"पूर्ण,
	अणुHFC_DIGI_DF_M_IOM2_A, 0,
	 "Digi International DataFire Micro V IOM2 (North America)"पूर्ण,
	अणुHFC_DIGI_DF_M_A, 0,
	 "Digi International DataFire Micro V (North America)"पूर्ण,
	अणुHFC_SITECOM_DC105V2, 0, "Sitecom Connectivity DC-105 ISDN TA"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id hfc_ids[] =
अणु
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_2BD0),
	  (अचिन्हित दीर्घ) &hfc_map[0] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B000),
	  (अचिन्हित दीर्घ) &hfc_map[1] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B006),
	  (अचिन्हित दीर्घ) &hfc_map[2] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B007),
	  (अचिन्हित दीर्घ) &hfc_map[3] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B008),
	  (अचिन्हित दीर्घ) &hfc_map[4] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B009),
	  (अचिन्हित दीर्घ) &hfc_map[5] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B00A),
	  (अचिन्हित दीर्घ) &hfc_map[6] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B00B),
	  (अचिन्हित दीर्घ) &hfc_map[7] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B00C),
	  (अचिन्हित दीर्घ) &hfc_map[8] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B100),
	  (अचिन्हित दीर्घ) &hfc_map[9] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B700),
	  (अचिन्हित दीर्घ) &hfc_map[10] पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_B701),
	  (अचिन्हित दीर्घ) &hfc_map[11] पूर्ण,
	अणु PCI_VDEVICE(ABOCOM, PCI_DEVICE_ID_ABOCOM_2BD1),
	  (अचिन्हित दीर्घ) &hfc_map[12] पूर्ण,
	अणु PCI_VDEVICE(ASUSTEK, PCI_DEVICE_ID_ASUSTEK_0675),
	  (अचिन्हित दीर्घ) &hfc_map[13] पूर्ण,
	अणु PCI_VDEVICE(BERKOM, PCI_DEVICE_ID_BERKOM_T_CONCEPT),
	  (अचिन्हित दीर्घ) &hfc_map[14] पूर्ण,
	अणु PCI_VDEVICE(BERKOM, PCI_DEVICE_ID_BERKOM_A1T),
	  (अचिन्हित दीर्घ) &hfc_map[15] पूर्ण,
	अणु PCI_VDEVICE(ANIGMA, PCI_DEVICE_ID_ANIGMA_MC145575),
	  (अचिन्हित दीर्घ) &hfc_map[16] पूर्ण,
	अणु PCI_VDEVICE(ZOLTRIX, PCI_DEVICE_ID_ZOLTRIX_2BD0),
	  (अचिन्हित दीर्घ) &hfc_map[17] पूर्ण,
	अणु PCI_VDEVICE(DIGI, PCI_DEVICE_ID_DIGI_DF_M_IOM2_E),
	  (अचिन्हित दीर्घ) &hfc_map[18] पूर्ण,
	अणु PCI_VDEVICE(DIGI, PCI_DEVICE_ID_DIGI_DF_M_E),
	  (अचिन्हित दीर्घ) &hfc_map[19] पूर्ण,
	अणु PCI_VDEVICE(DIGI, PCI_DEVICE_ID_DIGI_DF_M_IOM2_A),
	  (अचिन्हित दीर्घ) &hfc_map[20] पूर्ण,
	अणु PCI_VDEVICE(DIGI, PCI_DEVICE_ID_DIGI_DF_M_A),
	  (अचिन्हित दीर्घ) &hfc_map[21] पूर्ण,
	अणु PCI_VDEVICE(SITECOM, PCI_DEVICE_ID_SITECOM_DC105V2),
	  (अचिन्हित दीर्घ) &hfc_map[22] पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक
hfc_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक		err = -ENOMEM;
	काष्ठा hfc_pci	*card;
	काष्ठा _hfc_map	*m = (काष्ठा _hfc_map *)ent->driver_data;

	card = kzalloc(माप(काष्ठा hfc_pci), GFP_KERNEL);
	अगर (!card) अणु
		prपूर्णांकk(KERN_ERR "No kmem for HFC card\n");
		वापस err;
	पूर्ण
	card->pdev = pdev;
	card->subtype = m->subtype;
	err = pci_enable_device(pdev);
	अगर (err) अणु
		kमुक्त(card);
		वापस err;
	पूर्ण

	prपूर्णांकk(KERN_INFO "mISDN_hfcpci: found adapter %s at %s\n",
	       m->name, pci_name(pdev));

	card->irq = pdev->irq;
	pci_set_drvdata(pdev, card);
	err = setup_card(card);
	अगर (err)
		pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम
hfc_हटाओ_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hfc_pci	*card = pci_get_drvdata(pdev);

	अगर (card)
		release_card(card);
	अन्यथा
		अगर (debug)
			prपूर्णांकk(KERN_DEBUG "%s: drvdata already removed\n",
			       __func__);
पूर्ण


अटल काष्ठा pci_driver hfc_driver = अणु
	.name = "hfcpci",
	.probe = hfc_probe,
	.हटाओ = hfc_हटाओ_pci,
	.id_table = hfc_ids,
पूर्ण;

अटल पूर्णांक
_hfcpci_softirq(काष्ठा device *dev, व्योम *unused)
अणु
	काष्ठा hfc_pci  *hc = dev_get_drvdata(dev);
	काष्ठा bchannel *bch;
	अगर (hc == शून्य)
		वापस 0;

	अगर (hc->hw.पूर्णांक_m2 & HFCPCI_IRQ_ENABLE) अणु
		spin_lock(&hc->lock);
		bch = Sel_BCS(hc, hc->hw.bswapped ? 2 : 1);
		अगर (bch && bch->state == ISDN_P_B_RAW) अणु /* B1 rx&tx */
			मुख्य_rec_hfcpci(bch);
			tx_birq(bch);
		पूर्ण
		bch = Sel_BCS(hc, hc->hw.bswapped ? 1 : 2);
		अगर (bch && bch->state == ISDN_P_B_RAW) अणु /* B2 rx&tx */
			मुख्य_rec_hfcpci(bch);
			tx_birq(bch);
		पूर्ण
		spin_unlock(&hc->lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
hfcpci_softirq(काष्ठा समयr_list *unused)
अणु
	WARN_ON_ONCE(driver_क्रम_each_device(&hfc_driver.driver, शून्य, शून्य,
				      _hfcpci_softirq) != 0);

	/* अगर next event would be in the past ... */
	अगर ((s32)(hfc_jअगरfies + tics - jअगरfies) <= 0)
		hfc_jअगरfies = jअगरfies + 1;
	अन्यथा
		hfc_jअगरfies += tics;
	hfc_tl.expires = hfc_jअगरfies;
	add_समयr(&hfc_tl);
पूर्ण

अटल पूर्णांक __init
HFC_init(व्योम)
अणु
	पूर्णांक		err;

	अगर (!poll)
		poll = HFCPCI_BTRANS_THRESHOLD;

	अगर (poll != HFCPCI_BTRANS_THRESHOLD) अणु
		tics = (poll * HZ) / 8000;
		अगर (tics < 1)
			tics = 1;
		poll = (tics * 8000) / HZ;
		अगर (poll > 256 || poll < 8) अणु
			prपूर्णांकk(KERN_ERR "%s: Wrong poll value %d not in range "
			       "of 8..256.\n", __func__, poll);
			err = -EINVAL;
			वापस err;
		पूर्ण
	पूर्ण
	अगर (poll != HFCPCI_BTRANS_THRESHOLD) अणु
		prपूर्णांकk(KERN_INFO "%s: Using alternative poll value of %d\n",
		       __func__, poll);
		समयr_setup(&hfc_tl, hfcpci_softirq, 0);
		hfc_tl.expires = jअगरfies + tics;
		hfc_jअगरfies = hfc_tl.expires;
		add_समयr(&hfc_tl);
	पूर्ण अन्यथा
		tics = 0; /* indicate the use of controller's समयr */

	err = pci_रेजिस्टर_driver(&hfc_driver);
	अगर (err) अणु
		अगर (समयr_pending(&hfc_tl))
			del_समयr(&hfc_tl);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास
HFC_cleanup(व्योम)
अणु
	अगर (समयr_pending(&hfc_tl))
		del_समयr(&hfc_tl);

	pci_unरेजिस्टर_driver(&hfc_driver);
पूर्ण

module_init(HFC_init);
module_निकास(HFC_cleanup);

MODULE_DEVICE_TABLE(pci, hfc_ids);
