<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Tehuti Networks(R) Network Driver
 * ethtool पूर्णांकerface implementation
 * Copyright (C) 2007 Tehuti Networks Ltd. All rights reserved
 */

/*
 * RX HW/SW पूर्णांकeraction overview
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * There are 2 types of RX communication channels between driver and NIC.
 * 1) RX Free Fअगरo - RXF - holds descriptors of empty buffers to accept incoming
 * traffic. This Fअगरo is filled by SW and is पढ़ोen by HW. Each descriptor holds
 * info about buffer's location, size and ID. An ID field is used to identअगरy a
 * buffer when it's वापसed with data via RXD Fअगरo (see below)
 * 2) RX Data Fअगरo - RXD - holds descriptors of full buffers. This Fअगरo is
 * filled by HW and is पढ़ोen by SW. Each descriptor holds status and ID.
 * HW pops descriptor from RXF Fअगरo, stores ID, fills buffer with incoming data,
 * via dma moves it पूर्णांकo host memory, builds new RXD descriptor with same ID,
 * pushes it पूर्णांकo RXD Fअगरo and उठाओs पूर्णांकerrupt to indicate new RX data.
 *
 * Current NIC configuration (रेजिस्टरs + firmware) makes NIC use 2 RXF Fअगरos.
 * One holds 1.5K packets and another - 26K packets. Depending on incoming
 * packet size, HW desides on a RXF Fअगरo to pop buffer from. When packet is
 * filled with data, HW builds new RXD descriptor क्रम it and push it पूर्णांकo single
 * RXD Fअगरo.
 *
 * RX SW Data Structures
 * ~~~~~~~~~~~~~~~~~~~~~
 * skb db - used to keep track of all skbs owned by SW and their dma addresses.
 * For RX हाल, ownership lasts from allocating new empty skb क्रम RXF until
 * accepting full skb from RXD and passing it to OS. Each RXF Fअगरo has its own
 * skb db. Implemented as array with biपंचांगask.
 * fअगरo - keeps info about fअगरo's size and location, relevant HW रेजिस्टरs,
 * usage and skb db. Each RXD and RXF Fअगरo has its own fअगरo काष्ठाure.
 * Implemented as simple काष्ठा.
 *
 * RX SW Execution Flow
 * ~~~~~~~~~~~~~~~~~~~~
 * Upon initialization (अगरconfig up) driver creates RX fअगरos and initializes
 * relevant रेजिस्टरs. At the end of init phase, driver enables पूर्णांकerrupts.
 * NIC sees that there is no RXF buffers and उठाओs
 * RD_INTR पूर्णांकerrupt, isr fills skbs and Rx begins.
 * Driver has two receive operation modes:
 *    NAPI - पूर्णांकerrupt-driven mixed with polling
 *    पूर्णांकerrupt-driven only
 *
 * Interrupt-driven only flow is following. When buffer is पढ़ोy, HW उठाओs
 * पूर्णांकerrupt and isr is called. isr collects all available packets
 * (bdx_rx_receive), refills skbs (bdx_rx_alloc_skbs) and निकास.

 * Rx buffer allocation note
 * ~~~~~~~~~~~~~~~~~~~~~~~~~
 * Driver cares to feed such amount of RxF descriptors that respective amount of
 * RxD descriptors can not fill entire RxD fअगरo. The मुख्य reason is lack of
 * overflow check in Bordeaux क्रम RxD fअगरo मुक्त/used size.
 * FIXME: this is NOT fully implemented, more work should be करोne
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "tehuti.h"

अटल स्थिर काष्ठा pci_device_id bdx_pci_tbl[] = अणु
	अणु PCI_VDEVICE(TEHUTI, 0x3009), पूर्ण,
	अणु PCI_VDEVICE(TEHUTI, 0x3010), पूर्ण,
	अणु PCI_VDEVICE(TEHUTI, 0x3014), पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, bdx_pci_tbl);

/* Definitions needed by ISR or NAPI functions */
अटल व्योम bdx_rx_alloc_skbs(काष्ठा bdx_priv *priv, काष्ठा rxf_fअगरo *f);
अटल व्योम bdx_tx_cleanup(काष्ठा bdx_priv *priv);
अटल पूर्णांक bdx_rx_receive(काष्ठा bdx_priv *priv, काष्ठा rxd_fअगरo *f, पूर्णांक budget);

/* Definitions needed by FW loading */
अटल व्योम bdx_tx_push_desc_safe(काष्ठा bdx_priv *priv, व्योम *data, पूर्णांक size);

/* Definitions needed by hw_start */
अटल पूर्णांक bdx_tx_init(काष्ठा bdx_priv *priv);
अटल पूर्णांक bdx_rx_init(काष्ठा bdx_priv *priv);

/* Definitions needed by bdx_बंद */
अटल व्योम bdx_rx_मुक्त(काष्ठा bdx_priv *priv);
अटल व्योम bdx_tx_मुक्त(काष्ठा bdx_priv *priv);

/* Definitions needed by bdx_probe */
अटल व्योम bdx_set_ethtool_ops(काष्ठा net_device *netdev);

/*************************************************************************
 *    Prपूर्णांक Info                                                         *
 *************************************************************************/

अटल व्योम prपूर्णांक_hw_id(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_nic *nic = pci_get_drvdata(pdev);
	u16 pci_link_status = 0;
	u16 pci_ctrl = 0;

	pci_पढ़ो_config_word(pdev, PCI_LINK_STATUS_REG, &pci_link_status);
	pci_पढ़ो_config_word(pdev, PCI_DEV_CTRL_REG, &pci_ctrl);

	pr_info("%s%s\n", BDX_NIC_NAME,
		nic->port_num == 1 ? "" : ", 2-Port");
	pr_info("srom 0x%x fpga %d build %u lane# %d max_pl 0x%x mrrs 0x%x\n",
		पढ़ोl(nic->regs + SROM_VER), पढ़ोl(nic->regs + FPGA_VER) & 0xFFF,
		पढ़ोl(nic->regs + FPGA_SEED),
		GET_LINK_STATUS_LANES(pci_link_status),
		GET_DEV_CTRL_MAXPL(pci_ctrl), GET_DEV_CTRL_MRRS(pci_ctrl));
पूर्ण

अटल व्योम prपूर्णांक_fw_id(काष्ठा pci_nic *nic)
अणु
	pr_info("fw 0x%x\n", पढ़ोl(nic->regs + FW_VER));
पूर्ण

अटल व्योम prपूर्णांक_eth_id(काष्ठा net_device *ndev)
अणु
	netdev_info(ndev, "%s, Port %c\n",
		    BDX_NIC_NAME, (ndev->अगर_port == 0) ? 'A' : 'B');

पूर्ण

/*************************************************************************
 *    Code                                                               *
 *************************************************************************/

#घोषणा bdx_enable_पूर्णांकerrupts(priv)	\
	करो अणु WRITE_REG(priv, regIMR, IR_RUN); पूर्ण जबतक (0)
#घोषणा bdx_disable_पूर्णांकerrupts(priv)	\
	करो अणु WRITE_REG(priv, regIMR, 0); पूर्ण जबतक (0)

/**
 * bdx_fअगरo_init - create TX/RX descriptor fअगरo क्रम host-NIC communication.
 * @priv: NIC निजी काष्ठाure
 * @f: fअगरo to initialize
 * @fsz_type: fअगरo size type: 0-4KB, 1-8KB, 2-16KB, 3-32KB
 * @reg_CFG0: offsets of रेजिस्टरs relative to base address
 * @reg_CFG1: offsets of रेजिस्टरs relative to base address
 * @reg_RPTR: offsets of रेजिस्टरs relative to base address
 * @reg_WPTR: offsets of रेजिस्टरs relative to base address
 *
 * 1K extra space is allocated at the end of the fअगरo to simplअगरy
 * processing of descriptors that wraps around fअगरo's end
 *
 * Returns 0 on success, negative value on failure
 *
 */
अटल पूर्णांक
bdx_fअगरo_init(काष्ठा bdx_priv *priv, काष्ठा fअगरo *f, पूर्णांक fsz_type,
	      u16 reg_CFG0, u16 reg_CFG1, u16 reg_RPTR, u16 reg_WPTR)
अणु
	u16 memsz = FIFO_SIZE * (1 << fsz_type);

	स_रखो(f, 0, माप(काष्ठा fअगरo));
	/* dma_alloc_coherent gives us 4k-aligned memory */
	f->va = dma_alloc_coherent(&priv->pdev->dev, memsz + FIFO_EXTRA_SPACE,
				   &f->da, GFP_ATOMIC);
	अगर (!f->va) अणु
		pr_err("dma_alloc_coherent failed\n");
		RET(-ENOMEM);
	पूर्ण
	f->reg_CFG0 = reg_CFG0;
	f->reg_CFG1 = reg_CFG1;
	f->reg_RPTR = reg_RPTR;
	f->reg_WPTR = reg_WPTR;
	f->rptr = 0;
	f->wptr = 0;
	f->memsz = memsz;
	f->size_mask = memsz - 1;
	WRITE_REG(priv, reg_CFG0, (u32) ((f->da & TX_RX_CFG0_BASE) | fsz_type));
	WRITE_REG(priv, reg_CFG1, H32_64(f->da));

	RET(0);
पूर्ण

/**
 * bdx_fअगरo_मुक्त - मुक्त all resources used by fअगरo
 * @priv: NIC निजी काष्ठाure
 * @f: fअगरo to release
 */
अटल व्योम bdx_fअगरo_मुक्त(काष्ठा bdx_priv *priv, काष्ठा fअगरo *f)
अणु
	ENTER;
	अगर (f->va) अणु
		dma_मुक्त_coherent(&priv->pdev->dev,
				  f->memsz + FIFO_EXTRA_SPACE, f->va, f->da);
		f->va = शून्य;
	पूर्ण
	RET();
पूर्ण

/**
 * bdx_link_changed - notअगरies OS about hw link state.
 * @priv: hw adapter काष्ठाure
 */
अटल व्योम bdx_link_changed(काष्ठा bdx_priv *priv)
अणु
	u32 link = READ_REG(priv, regMAC_LNK_STAT) & MAC_LINK_STAT;

	अगर (!link) अणु
		अगर (netअगर_carrier_ok(priv->ndev)) अणु
			netअगर_stop_queue(priv->ndev);
			netअगर_carrier_off(priv->ndev);
			netdev_err(priv->ndev, "Link Down\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!netअगर_carrier_ok(priv->ndev)) अणु
			netअगर_wake_queue(priv->ndev);
			netअगर_carrier_on(priv->ndev);
			netdev_err(priv->ndev, "Link Up\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bdx_isr_extra(काष्ठा bdx_priv *priv, u32 isr)
अणु
	अगर (isr & IR_RX_FREE_0) अणु
		bdx_rx_alloc_skbs(priv, &priv->rxf_fअगरo0);
		DBG("RX_FREE_0\n");
	पूर्ण

	अगर (isr & IR_LNKCHG0)
		bdx_link_changed(priv);

	अगर (isr & IR_PCIE_LINK)
		netdev_err(priv->ndev, "PCI-E Link Fault\n");

	अगर (isr & IR_PCIE_TOUT)
		netdev_err(priv->ndev, "PCI-E Time Out\n");

पूर्ण

/**
 * bdx_isr_napi - Interrupt Service Routine क्रम Bordeaux NIC
 * @irq: पूर्णांकerrupt number
 * @dev: network device
 *
 * Return IRQ_NONE अगर it was not our पूर्णांकerrupt, IRQ_HANDLED - otherwise
 *
 * It पढ़ोs ISR रेजिस्टर to know पूर्णांकerrupt reasons, and proceed them one by one.
 * Reasons of पूर्णांकerest are:
 *    RX_DESC - new packet has arrived and RXD fअगरo holds its descriptor
 *    RX_FREE - number of मुक्त Rx buffers in RXF fअगरo माला_लो low
 *    TX_FREE - packet was transmited and RXF fअगरo holds its descriptor
 */

अटल irqवापस_t bdx_isr_napi(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा net_device *ndev = dev;
	काष्ठा bdx_priv *priv = netdev_priv(ndev);
	u32 isr;

	ENTER;
	isr = (READ_REG(priv, regISR) & IR_RUN);
	अगर (unlikely(!isr)) अणु
		bdx_enable_पूर्णांकerrupts(priv);
		वापस IRQ_NONE;	/* Not our पूर्णांकerrupt */
	पूर्ण

	अगर (isr & IR_EXTRA)
		bdx_isr_extra(priv, isr);

	अगर (isr & (IR_RX_DESC_0 | IR_TX_FREE_0)) अणु
		अगर (likely(napi_schedule_prep(&priv->napi))) अणु
			__napi_schedule(&priv->napi);
			RET(IRQ_HANDLED);
		पूर्ण अन्यथा अणु
			/* NOTE: we get here अगर पूर्णांकr has slipped पूर्णांकo winकरोw
			 * between these lines in bdx_poll:
			 *    bdx_enable_पूर्णांकerrupts(priv);
			 *    वापस 0;
			 * currently पूर्णांकrs are disabled (since we पढ़ो ISR),
			 * and we have failed to रेजिस्टर next poll.
			 * so we पढ़ो the regs to trigger chip
			 * and allow further पूर्णांकerupts. */
			READ_REG(priv, regTXF_WPTR_0);
			READ_REG(priv, regRXD_WPTR_0);
		पूर्ण
	पूर्ण

	bdx_enable_पूर्णांकerrupts(priv);
	RET(IRQ_HANDLED);
पूर्ण

अटल पूर्णांक bdx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bdx_priv *priv = container_of(napi, काष्ठा bdx_priv, napi);
	पूर्णांक work_करोne;

	ENTER;
	bdx_tx_cleanup(priv);
	work_करोne = bdx_rx_receive(priv, &priv->rxd_fअगरo0, budget);
	अगर ((work_करोne < budget) ||
	    (priv->napi_stop++ >= 30)) अणु
		DBG("rx poll is done. backing to isr-driven\n");

		/* from समय to समय we निकास to let NAPI layer release
		 * device lock and allow रुकोing tasks (eg rmmod) to advance) */
		priv->napi_stop = 0;

		napi_complete_करोne(napi, work_करोne);
		bdx_enable_पूर्णांकerrupts(priv);
	पूर्ण
	वापस work_करोne;
पूर्ण

/**
 * bdx_fw_load - loads firmware to NIC
 * @priv: NIC निजी काष्ठाure
 *
 * Firmware is loaded via TXD fअगरo, so it must be initialized first.
 * Firware must be loaded once per NIC not per PCI device provided by NIC (NIC
 * can have few of them). So all drivers use semaphore रेजिस्टर to choose one
 * that will actually load FW to NIC.
 */

अटल पूर्णांक bdx_fw_load(काष्ठा bdx_priv *priv)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक master, i;
	पूर्णांक rc;

	ENTER;
	master = READ_REG(priv, regINIT_SEMAPHORE);
	अगर (!READ_REG(priv, regINIT_STATUS) && master) अणु
		rc = request_firmware(&fw, "tehuti/bdx.bin", &priv->pdev->dev);
		अगर (rc)
			जाओ out;
		bdx_tx_push_desc_safe(priv, (अक्षर *)fw->data, fw->size);
		mdelay(100);
	पूर्ण
	क्रम (i = 0; i < 200; i++) अणु
		अगर (READ_REG(priv, regINIT_STATUS)) अणु
			rc = 0;
			जाओ out;
		पूर्ण
		mdelay(2);
	पूर्ण
	rc = -EIO;
out:
	अगर (master)
		WRITE_REG(priv, regINIT_SEMAPHORE, 1);

	release_firmware(fw);

	अगर (rc) अणु
		netdev_err(priv->ndev, "firmware loading failed\n");
		अगर (rc == -EIO)
			DBG("VPC = 0x%x VIC = 0x%x INIT_STATUS = 0x%x i=%d\n",
			    READ_REG(priv, regVPC),
			    READ_REG(priv, regVIC),
			    READ_REG(priv, regINIT_STATUS), i);
		RET(rc);
	पूर्ण अन्यथा अणु
		DBG("%s: firmware loading success\n", priv->ndev->name);
		RET(0);
	पूर्ण
पूर्ण

अटल व्योम bdx_restore_mac(काष्ठा net_device *ndev, काष्ठा bdx_priv *priv)
अणु
	u32 val;

	ENTER;
	DBG("mac0=%x mac1=%x mac2=%x\n",
	    READ_REG(priv, regUNC_MAC0_A),
	    READ_REG(priv, regUNC_MAC1_A), READ_REG(priv, regUNC_MAC2_A));

	val = (ndev->dev_addr[0] << 8) | (ndev->dev_addr[1]);
	WRITE_REG(priv, regUNC_MAC2_A, val);
	val = (ndev->dev_addr[2] << 8) | (ndev->dev_addr[3]);
	WRITE_REG(priv, regUNC_MAC1_A, val);
	val = (ndev->dev_addr[4] << 8) | (ndev->dev_addr[5]);
	WRITE_REG(priv, regUNC_MAC0_A, val);

	DBG("mac0=%x mac1=%x mac2=%x\n",
	    READ_REG(priv, regUNC_MAC0_A),
	    READ_REG(priv, regUNC_MAC1_A), READ_REG(priv, regUNC_MAC2_A));
	RET();
पूर्ण

/**
 * bdx_hw_start - inits रेजिस्टरs and starts HW's Rx and Tx engines
 * @priv: NIC निजी काष्ठाure
 */
अटल पूर्णांक bdx_hw_start(काष्ठा bdx_priv *priv)
अणु
	पूर्णांक rc = -EIO;
	काष्ठा net_device *ndev = priv->ndev;

	ENTER;
	bdx_link_changed(priv);

	/* 10G overall max length (vlan, eth&ip header, ip payload, crc) */
	WRITE_REG(priv, regFRM_LENGTH, 0X3FE0);
	WRITE_REG(priv, regPAUSE_QUANT, 0x96);
	WRITE_REG(priv, regRX_FIFO_SECTION, 0x800010);
	WRITE_REG(priv, regTX_FIFO_SECTION, 0xE00010);
	WRITE_REG(priv, regRX_FULLNESS, 0);
	WRITE_REG(priv, regTX_FULLNESS, 0);
	WRITE_REG(priv, regCTRLST,
		  regCTRLST_BASE | regCTRLST_RX_ENA | regCTRLST_TX_ENA);

	WRITE_REG(priv, regVGLB, 0);
	WRITE_REG(priv, regMAX_FRAME_A,
		  priv->rxf_fअगरo0.m.pktsz & MAX_FRAME_AB_VAL);

	DBG("RDINTCM=%08x\n", priv->rdपूर्णांकcm);	/*NOTE: test script uses this */
	WRITE_REG(priv, regRDINTCM0, priv->rdपूर्णांकcm);
	WRITE_REG(priv, regRDINTCM2, 0);	/*cpu_to_le32(rcm.val)); */

	DBG("TDINTCM=%08x\n", priv->tdपूर्णांकcm);	/*NOTE: test script uses this */
	WRITE_REG(priv, regTDINTCM0, priv->tdपूर्णांकcm);	/* old val = 0x300064 */

	/* Enable समयr पूर्णांकerrupt once in 2 secs. */
	/*WRITE_REG(priv, regGTMR0, ((GTMR_SEC * 2) & GTMR_DATA)); */
	bdx_restore_mac(priv->ndev, priv);

	WRITE_REG(priv, regGMAC_RXF_A, GMAC_RX_FILTER_OSEN |
		  GMAC_RX_FILTER_AM | GMAC_RX_FILTER_AB);

#घोषणा BDX_IRQ_TYPE	((priv->nic->irq_type == IRQ_MSI) ? 0 : IRQF_SHARED)

	rc = request_irq(priv->pdev->irq, bdx_isr_napi, BDX_IRQ_TYPE,
			 ndev->name, ndev);
	अगर (rc)
		जाओ err_irq;
	bdx_enable_पूर्णांकerrupts(priv);

	RET(0);

err_irq:
	RET(rc);
पूर्ण

अटल व्योम bdx_hw_stop(काष्ठा bdx_priv *priv)
अणु
	ENTER;
	bdx_disable_पूर्णांकerrupts(priv);
	मुक्त_irq(priv->pdev->irq, priv->ndev);

	netअगर_carrier_off(priv->ndev);
	netअगर_stop_queue(priv->ndev);

	RET();
पूर्ण

अटल पूर्णांक bdx_hw_reset_direct(व्योम __iomem *regs)
अणु
	u32 val, i;
	ENTER;

	/* reset sequences: पढ़ो, ग_लिखो 1, पढ़ो, ग_लिखो 0 */
	val = पढ़ोl(regs + regCLKPLL);
	ग_लिखोl((val | CLKPLL_SFTRST) + 0x8, regs + regCLKPLL);
	udelay(50);
	val = पढ़ोl(regs + regCLKPLL);
	ग_लिखोl(val & ~CLKPLL_SFTRST, regs + regCLKPLL);

	/* check that the PLLs are locked and reset ended */
	क्रम (i = 0; i < 70; i++, mdelay(10))
		अगर ((पढ़ोl(regs + regCLKPLL) & CLKPLL_LKD) == CLKPLL_LKD) अणु
			/* करो any PCI-E पढ़ो transaction */
			पढ़ोl(regs + regRXD_CFG0_0);
			वापस 0;
		पूर्ण
	pr_err("HW reset failed\n");
	वापस 1;		/* failure */
पूर्ण

अटल पूर्णांक bdx_hw_reset(काष्ठा bdx_priv *priv)
अणु
	u32 val, i;
	ENTER;

	अगर (priv->port == 0) अणु
		/* reset sequences: पढ़ो, ग_लिखो 1, पढ़ो, ग_लिखो 0 */
		val = READ_REG(priv, regCLKPLL);
		WRITE_REG(priv, regCLKPLL, (val | CLKPLL_SFTRST) + 0x8);
		udelay(50);
		val = READ_REG(priv, regCLKPLL);
		WRITE_REG(priv, regCLKPLL, val & ~CLKPLL_SFTRST);
	पूर्ण
	/* check that the PLLs are locked and reset ended */
	क्रम (i = 0; i < 70; i++, mdelay(10))
		अगर ((READ_REG(priv, regCLKPLL) & CLKPLL_LKD) == CLKPLL_LKD) अणु
			/* करो any PCI-E पढ़ो transaction */
			READ_REG(priv, regRXD_CFG0_0);
			वापस 0;
		पूर्ण
	pr_err("HW reset failed\n");
	वापस 1;		/* failure */
पूर्ण

अटल पूर्णांक bdx_sw_reset(काष्ठा bdx_priv *priv)
अणु
	पूर्णांक i;

	ENTER;
	/* 1. load MAC (obsolete) */
	/* 2. disable Rx (and Tx) */
	WRITE_REG(priv, regGMAC_RXF_A, 0);
	mdelay(100);
	/* 3. disable port */
	WRITE_REG(priv, regDIS_PORT, 1);
	/* 4. disable queue */
	WRITE_REG(priv, regDIS_QU, 1);
	/* 5. रुको until hw is disabled */
	क्रम (i = 0; i < 50; i++) अणु
		अगर (READ_REG(priv, regRST_PORT) & 1)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 50)
		netdev_err(priv->ndev, "SW reset timeout. continuing anyway\n");

	/* 6. disable पूर्णांकrs */
	WRITE_REG(priv, regRDINTCM0, 0);
	WRITE_REG(priv, regTDINTCM0, 0);
	WRITE_REG(priv, regIMR, 0);
	READ_REG(priv, regISR);

	/* 7. reset queue */
	WRITE_REG(priv, regRST_QU, 1);
	/* 8. reset port */
	WRITE_REG(priv, regRST_PORT, 1);
	/* 9. zero all पढ़ो and ग_लिखो poपूर्णांकers */
	क्रम (i = regTXD_WPTR_0; i <= regTXF_RPTR_3; i += 0x10)
		DBG("%x = %x\n", i, READ_REG(priv, i) & TXF_WPTR_WR_PTR);
	क्रम (i = regTXD_WPTR_0; i <= regTXF_RPTR_3; i += 0x10)
		WRITE_REG(priv, i, 0);
	/* 10. unseet port disable */
	WRITE_REG(priv, regDIS_PORT, 0);
	/* 11. unset queue disable */
	WRITE_REG(priv, regDIS_QU, 0);
	/* 12. unset queue reset */
	WRITE_REG(priv, regRST_QU, 0);
	/* 13. unset port reset */
	WRITE_REG(priv, regRST_PORT, 0);
	/* 14. enable Rx */
	/* skiped. will be करोne later */
	/* 15. save MAC (obsolete) */
	क्रम (i = regTXD_WPTR_0; i <= regTXF_RPTR_3; i += 0x10)
		DBG("%x = %x\n", i, READ_REG(priv, i) & TXF_WPTR_WR_PTR);

	RET(0);
पूर्ण

/* bdx_reset - perक्रमms right type of reset depending on hw type */
अटल पूर्णांक bdx_reset(काष्ठा bdx_priv *priv)
अणु
	ENTER;
	RET((priv->pdev->device == 0x3009)
	    ? bdx_hw_reset(priv)
	    : bdx_sw_reset(priv));
पूर्ण

/**
 * bdx_बंद - Disables a network पूर्णांकerface
 * @ndev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 **/
अटल पूर्णांक bdx_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा bdx_priv *priv = शून्य;

	ENTER;
	priv = netdev_priv(ndev);

	napi_disable(&priv->napi);

	bdx_reset(priv);
	bdx_hw_stop(priv);
	bdx_rx_मुक्त(priv);
	bdx_tx_मुक्त(priv);
	RET(0);
पूर्ण

/**
 * bdx_खोलो - Called when a network पूर्णांकerface is made active
 * @ndev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
अटल पूर्णांक bdx_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा bdx_priv *priv;
	पूर्णांक rc;

	ENTER;
	priv = netdev_priv(ndev);
	bdx_reset(priv);
	अगर (netअगर_running(ndev))
		netअगर_stop_queue(priv->ndev);

	अगर ((rc = bdx_tx_init(priv)) ||
	    (rc = bdx_rx_init(priv)) ||
	    (rc = bdx_fw_load(priv)))
		जाओ err;

	bdx_rx_alloc_skbs(priv, &priv->rxf_fअगरo0);

	rc = bdx_hw_start(priv);
	अगर (rc)
		जाओ err;

	napi_enable(&priv->napi);

	prपूर्णांक_fw_id(priv->nic);

	RET(0);

err:
	bdx_बंद(ndev);
	RET(rc);
पूर्ण

अटल पूर्णांक bdx_range_check(काष्ठा bdx_priv *priv, u32 offset)
अणु
	वापस (offset > (u32) (BDX_REGS_SIZE / priv->nic->port_num)) ?
		-EINVAL : 0;
पूर्ण

अटल पूर्णांक bdx_ioctl_priv(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(ndev);
	u32 data[3];
	पूर्णांक error;

	ENTER;

	DBG("jiffies=%ld cmd=%d\n", jअगरfies, cmd);
	अगर (cmd != SIOCDEVPRIVATE) अणु
		error = copy_from_user(data, अगरr->अगरr_data, माप(data));
		अगर (error) अणु
			pr_err("can't copy from user\n");
			RET(-EFAULT);
		पूर्ण
		DBG("%d 0x%x 0x%x\n", data[0], data[1], data[2]);
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	चयन (data[0]) अणु

	हाल BDX_OP_READ:
		error = bdx_range_check(priv, data[1]);
		अगर (error < 0)
			वापस error;
		data[2] = READ_REG(priv, data[1]);
		DBG("read_reg(0x%x)=0x%x (dec %d)\n", data[1], data[2],
		    data[2]);
		error = copy_to_user(अगरr->अगरr_data, data, माप(data));
		अगर (error)
			RET(-EFAULT);
		अवरोध;

	हाल BDX_OP_WRITE:
		error = bdx_range_check(priv, data[1]);
		अगर (error < 0)
			वापस error;
		WRITE_REG(priv, data[1], data[2]);
		DBG("write_reg(0x%x, 0x%x)\n", data[1], data[2]);
		अवरोध;

	शेष:
		RET(-EOPNOTSUPP);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bdx_ioctl(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	ENTER;
	अगर (cmd >= SIOCDEVPRIVATE && cmd <= (SIOCDEVPRIVATE + 15))
		RET(bdx_ioctl_priv(ndev, अगरr, cmd));
	अन्यथा
		RET(-EOPNOTSUPP);
पूर्ण

/**
 * __bdx_vlan_rx_vid - निजी helper क्रम adding/समाप्तing VLAN vid
 * @ndev: network device
 * @vid:  VLAN vid
 * @enable: enable or disable vlan
 *
 * Passes VLAN filter table to hardware
 */
अटल व्योम __bdx_vlan_rx_vid(काष्ठा net_device *ndev, uपूर्णांक16_t vid, पूर्णांक enable)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(ndev);
	u32 reg, bit, val;

	ENTER;
	DBG2("vid=%d value=%d\n", (पूर्णांक)vid, enable);
	अगर (unlikely(vid >= 4096)) अणु
		pr_err("invalid VID: %u (> 4096)\n", vid);
		RET();
	पूर्ण
	reg = regVLAN_0 + (vid / 32) * 4;
	bit = 1 << vid % 32;
	val = READ_REG(priv, reg);
	DBG2("reg=%x, val=%x, bit=%d\n", reg, val, bit);
	अगर (enable)
		val |= bit;
	अन्यथा
		val &= ~bit;
	DBG2("new val %x\n", val);
	WRITE_REG(priv, reg, val);
	RET();
पूर्ण

/**
 * bdx_vlan_rx_add_vid - kernel hook क्रम adding VLAN vid to hw filtering table
 * @ndev: network device
 * @proto: unused
 * @vid:  VLAN vid to add
 */
अटल पूर्णांक bdx_vlan_rx_add_vid(काष्ठा net_device *ndev, __be16 proto, u16 vid)
अणु
	__bdx_vlan_rx_vid(ndev, vid, 1);
	वापस 0;
पूर्ण

/**
 * bdx_vlan_rx_समाप्त_vid - kernel hook क्रम समाप्तing VLAN vid in hw filtering table
 * @ndev: network device
 * @proto: unused
 * @vid:  VLAN vid to समाप्त
 */
अटल पूर्णांक bdx_vlan_rx_समाप्त_vid(काष्ठा net_device *ndev, __be16 proto, u16 vid)
अणु
	__bdx_vlan_rx_vid(ndev, vid, 0);
	वापस 0;
पूर्ण

/**
 * bdx_change_mtu - Change the Maximum Transfer Unit
 * @ndev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक bdx_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	ENTER;

	ndev->mtu = new_mtu;
	अगर (netअगर_running(ndev)) अणु
		bdx_बंद(ndev);
		bdx_खोलो(ndev);
	पूर्ण
	RET(0);
पूर्ण

अटल व्योम bdx_seपंचांगulti(काष्ठा net_device *ndev)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(ndev);

	u32 rxf_val =
	    GMAC_RX_FILTER_AM | GMAC_RX_FILTER_AB | GMAC_RX_FILTER_OSEN;
	पूर्णांक i;

	ENTER;
	/* IMF - imperfect (hash) rx multicat filter */
	/* PMF - perfect rx multicat filter */

	/* FIXME: RXE(OFF) */
	अगर (ndev->flags & IFF_PROMISC) अणु
		rxf_val |= GMAC_RX_FILTER_PRM;
	पूर्ण अन्यथा अगर (ndev->flags & IFF_ALLMULTI) अणु
		/* set IMF to accept all multicast frmaes */
		क्रम (i = 0; i < MAC_MCST_HASH_NUM; i++)
			WRITE_REG(priv, regRX_MCST_HASH0 + i * 4, ~0);
	पूर्ण अन्यथा अगर (!netdev_mc_empty(ndev)) अणु
		u8 hash;
		काष्ठा netdev_hw_addr *ha;
		u32 reg, val;

		/* set IMF to deny all multicast frames */
		क्रम (i = 0; i < MAC_MCST_HASH_NUM; i++)
			WRITE_REG(priv, regRX_MCST_HASH0 + i * 4, 0);
		/* set PMF to deny all multicast frames */
		क्रम (i = 0; i < MAC_MCST_NUM; i++) अणु
			WRITE_REG(priv, regRX_MAC_MCST0 + i * 8, 0);
			WRITE_REG(priv, regRX_MAC_MCST1 + i * 8, 0);
		पूर्ण

		/* use PMF to accept first MAC_MCST_NUM (15) addresses */
		/* TBD: sort addresses and ग_लिखो them in ascending order
		 * पूर्णांकo RX_MAC_MCST regs. we skip this phase now and accept ALL
		 * multicast frames throu IMF */
		/* accept the rest of addresses throu IMF */
		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			hash = 0;
			क्रम (i = 0; i < ETH_ALEN; i++)
				hash ^= ha->addr[i];
			reg = regRX_MCST_HASH0 + ((hash >> 5) << 2);
			val = READ_REG(priv, reg);
			val |= (1 << (hash % 32));
			WRITE_REG(priv, reg, val);
		पूर्ण

	पूर्ण अन्यथा अणु
		DBG("only own mac %d\n", netdev_mc_count(ndev));
		rxf_val |= GMAC_RX_FILTER_AB;
	पूर्ण
	WRITE_REG(priv, regGMAC_RXF_A, rxf_val);
	/* enable RX */
	/* FIXME: RXE(ON) */
	RET();
पूर्ण

अटल पूर्णांक bdx_set_mac(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(ndev);
	काष्ठा sockaddr *addr = p;

	ENTER;
	/*
	   अगर (netअगर_running(dev))
	   वापस -EBUSY
	 */
	स_नकल(ndev->dev_addr, addr->sa_data, ndev->addr_len);
	bdx_restore_mac(ndev, priv);
	RET(0);
पूर्ण

अटल पूर्णांक bdx_पढ़ो_mac(काष्ठा bdx_priv *priv)
अणु
	u16 macAddress[3], i;
	ENTER;

	macAddress[2] = READ_REG(priv, regUNC_MAC0_A);
	macAddress[2] = READ_REG(priv, regUNC_MAC0_A);
	macAddress[1] = READ_REG(priv, regUNC_MAC1_A);
	macAddress[1] = READ_REG(priv, regUNC_MAC1_A);
	macAddress[0] = READ_REG(priv, regUNC_MAC2_A);
	macAddress[0] = READ_REG(priv, regUNC_MAC2_A);
	क्रम (i = 0; i < 3; i++) अणु
		priv->ndev->dev_addr[i * 2 + 1] = macAddress[i];
		priv->ndev->dev_addr[i * 2] = macAddress[i] >> 8;
	पूर्ण
	RET(0);
पूर्ण

अटल u64 bdx_पढ़ो_l2stat(काष्ठा bdx_priv *priv, पूर्णांक reg)
अणु
	u64 val;

	val = READ_REG(priv, reg);
	val |= ((u64) READ_REG(priv, reg + 8)) << 32;
	वापस val;
पूर्ण

/*Do the statistics-update work*/
अटल व्योम bdx_update_stats(काष्ठा bdx_priv *priv)
अणु
	काष्ठा bdx_stats *stats = &priv->hw_stats;
	u64 *stats_vector = (u64 *) stats;
	पूर्णांक i;
	पूर्णांक addr;

	/*Fill HW काष्ठाure */
	addr = 0x7200;
	/*First 12 statistics - 0x7200 - 0x72B0 */
	क्रम (i = 0; i < 12; i++) अणु
		stats_vector[i] = bdx_पढ़ो_l2stat(priv, addr);
		addr += 0x10;
	पूर्ण
	BDX_ASSERT(addr != 0x72C0);
	/* 0x72C0-0x72E0 RSRV */
	addr = 0x72F0;
	क्रम (; i < 16; i++) अणु
		stats_vector[i] = bdx_पढ़ो_l2stat(priv, addr);
		addr += 0x10;
	पूर्ण
	BDX_ASSERT(addr != 0x7330);
	/* 0x7330-0x7360 RSRV */
	addr = 0x7370;
	क्रम (; i < 19; i++) अणु
		stats_vector[i] = bdx_पढ़ो_l2stat(priv, addr);
		addr += 0x10;
	पूर्ण
	BDX_ASSERT(addr != 0x73A0);
	/* 0x73A0-0x73B0 RSRV */
	addr = 0x73C0;
	क्रम (; i < 23; i++) अणु
		stats_vector[i] = bdx_पढ़ो_l2stat(priv, addr);
		addr += 0x10;
	पूर्ण
	BDX_ASSERT(addr != 0x7400);
	BDX_ASSERT((माप(काष्ठा bdx_stats) / माप(u64)) != i);
पूर्ण

अटल व्योम prपूर्णांक_rxdd(काष्ठा rxd_desc *rxdd, u32 rxd_val1, u16 len,
		       u16 rxd_vlan);
अटल व्योम prपूर्णांक_rxfd(काष्ठा rxf_desc *rxfd);

/*************************************************************************
 *     Rx DB                                                             *
 *************************************************************************/

अटल व्योम bdx_rxdb_destroy(काष्ठा rxdb *db)
अणु
	vमुक्त(db);
पूर्ण

अटल काष्ठा rxdb *bdx_rxdb_create(पूर्णांक nelem)
अणु
	काष्ठा rxdb *db;
	पूर्णांक i;

	db = vदो_स्मृति(माप(काष्ठा rxdb)
		     + (nelem * माप(पूर्णांक))
		     + (nelem * माप(काष्ठा rx_map)));
	अगर (likely(db != शून्य)) अणु
		db->stack = (पूर्णांक *)(db + 1);
		db->elems = (व्योम *)(db->stack + nelem);
		db->nelem = nelem;
		db->top = nelem;
		क्रम (i = 0; i < nelem; i++)
			db->stack[i] = nelem - i - 1;	/* to make first allocs
							   बंद to db काष्ठा*/
	पूर्ण

	वापस db;
पूर्ण

अटल अंतरभूत पूर्णांक bdx_rxdb_alloc_elem(काष्ठा rxdb *db)
अणु
	BDX_ASSERT(db->top <= 0);
	वापस db->stack[--(db->top)];
पूर्ण

अटल अंतरभूत व्योम *bdx_rxdb_addr_elem(काष्ठा rxdb *db, पूर्णांक n)
अणु
	BDX_ASSERT((n < 0) || (n >= db->nelem));
	वापस db->elems + n;
पूर्ण

अटल अंतरभूत पूर्णांक bdx_rxdb_available(काष्ठा rxdb *db)
अणु
	वापस db->top;
पूर्ण

अटल अंतरभूत व्योम bdx_rxdb_मुक्त_elem(काष्ठा rxdb *db, पूर्णांक n)
अणु
	BDX_ASSERT((n >= db->nelem) || (n < 0));
	db->stack[(db->top)++] = n;
पूर्ण

/*************************************************************************
 *     Rx Init                                                           *
 *************************************************************************/

/**
 * bdx_rx_init - initialize RX all related HW and SW resources
 * @priv: NIC निजी काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * It creates rxf and rxd fअगरos, update relevant HW रेजिस्टरs, pपुनः_स्मृतिate
 * skb क्रम rx. It assumes that Rx is desabled in HW
 * funcs are grouped क्रम better cache usage
 *
 * RxD fअगरo is smaller than RxF fअगरo by design. Upon high load, RxD will be
 * filled and packets will be dropped by nic without getting पूर्णांकo host or
 * cousing पूर्णांकerrupt. Anyway, in that condition, host has no chance to process
 * all packets, but dropping in nic is cheaper, since it takes 0 cpu cycles
 */

/* TBD: ensure proper packet size */

अटल पूर्णांक bdx_rx_init(काष्ठा bdx_priv *priv)
अणु
	ENTER;

	अगर (bdx_fअगरo_init(priv, &priv->rxd_fअगरo0.m, priv->rxd_size,
			  regRXD_CFG0_0, regRXD_CFG1_0,
			  regRXD_RPTR_0, regRXD_WPTR_0))
		जाओ err_mem;
	अगर (bdx_fअगरo_init(priv, &priv->rxf_fअगरo0.m, priv->rxf_size,
			  regRXF_CFG0_0, regRXF_CFG1_0,
			  regRXF_RPTR_0, regRXF_WPTR_0))
		जाओ err_mem;
	priv->rxdb = bdx_rxdb_create(priv->rxf_fअगरo0.m.memsz /
				     माप(काष्ठा rxf_desc));
	अगर (!priv->rxdb)
		जाओ err_mem;

	priv->rxf_fअगरo0.m.pktsz = priv->ndev->mtu + VLAN_ETH_HLEN;
	वापस 0;

err_mem:
	netdev_err(priv->ndev, "Rx init failed\n");
	वापस -ENOMEM;
पूर्ण

/**
 * bdx_rx_मुक्त_skbs - मुक्तs and unmaps all skbs allocated क्रम the fअगरo
 * @priv: NIC निजी काष्ठाure
 * @f: RXF fअगरo
 */
अटल व्योम bdx_rx_मुक्त_skbs(काष्ठा bdx_priv *priv, काष्ठा rxf_fअगरo *f)
अणु
	काष्ठा rx_map *dm;
	काष्ठा rxdb *db = priv->rxdb;
	u16 i;

	ENTER;
	DBG("total=%d free=%d busy=%d\n", db->nelem, bdx_rxdb_available(db),
	    db->nelem - bdx_rxdb_available(db));
	जबतक (bdx_rxdb_available(db) > 0) अणु
		i = bdx_rxdb_alloc_elem(db);
		dm = bdx_rxdb_addr_elem(db, i);
		dm->dma = 0;
	पूर्ण
	क्रम (i = 0; i < db->nelem; i++) अणु
		dm = bdx_rxdb_addr_elem(db, i);
		अगर (dm->dma) अणु
			dma_unmap_single(&priv->pdev->dev, dm->dma,
					 f->m.pktsz, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(dm->skb);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * bdx_rx_मुक्त - release all Rx resources
 * @priv: NIC निजी काष्ठाure
 *
 * It assumes that Rx is desabled in HW
 */
अटल व्योम bdx_rx_मुक्त(काष्ठा bdx_priv *priv)
अणु
	ENTER;
	अगर (priv->rxdb) अणु
		bdx_rx_मुक्त_skbs(priv, &priv->rxf_fअगरo0);
		bdx_rxdb_destroy(priv->rxdb);
		priv->rxdb = शून्य;
	पूर्ण
	bdx_fअगरo_मुक्त(priv, &priv->rxf_fअगरo0.m);
	bdx_fअगरo_मुक्त(priv, &priv->rxd_fअगरo0.m);

	RET();
पूर्ण

/*************************************************************************
 *     Rx Engine                                                         *
 *************************************************************************/

/**
 * bdx_rx_alloc_skbs - fill rxf fअगरo with new skbs
 * @priv: nic's निजी काष्ठाure
 * @f: RXF fअगरo that needs skbs
 *
 * It allocates skbs, build rxf descs and push it (rxf descr) पूर्णांकo rxf fअगरo.
 * skb's भव and physical addresses are stored in skb db.
 * To calculate मुक्त space, func uses cached values of RPTR and WPTR
 * When needed, it also updates RPTR and WPTR.
 */

/* TBD: करो not update WPTR अगर no desc were written */

अटल व्योम bdx_rx_alloc_skbs(काष्ठा bdx_priv *priv, काष्ठा rxf_fअगरo *f)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rxf_desc *rxfd;
	काष्ठा rx_map *dm;
	पूर्णांक dno, delta, idx;
	काष्ठा rxdb *db = priv->rxdb;

	ENTER;
	dno = bdx_rxdb_available(db) - 1;
	जबतक (dno > 0) अणु
		skb = netdev_alloc_skb(priv->ndev, f->m.pktsz + NET_IP_ALIGN);
		अगर (!skb)
			अवरोध;

		skb_reserve(skb, NET_IP_ALIGN);

		idx = bdx_rxdb_alloc_elem(db);
		dm = bdx_rxdb_addr_elem(db, idx);
		dm->dma = dma_map_single(&priv->pdev->dev, skb->data,
					 f->m.pktsz, DMA_FROM_DEVICE);
		dm->skb = skb;
		rxfd = (काष्ठा rxf_desc *)(f->m.va + f->m.wptr);
		rxfd->info = CPU_CHIP_SWAP32(0x10003);	/* INFO=1 BC=3 */
		rxfd->va_lo = idx;
		rxfd->pa_lo = CPU_CHIP_SWAP32(L32_64(dm->dma));
		rxfd->pa_hi = CPU_CHIP_SWAP32(H32_64(dm->dma));
		rxfd->len = CPU_CHIP_SWAP32(f->m.pktsz);
		prपूर्णांक_rxfd(rxfd);

		f->m.wptr += माप(काष्ठा rxf_desc);
		delta = f->m.wptr - f->m.memsz;
		अगर (unlikely(delta >= 0)) अणु
			f->m.wptr = delta;
			अगर (delta > 0) अणु
				स_नकल(f->m.va, f->m.va + f->m.memsz, delta);
				DBG("wrapped descriptor\n");
			पूर्ण
		पूर्ण
		dno--;
	पूर्ण
	/*TBD: to करो - delayed rxf wptr like in txd */
	WRITE_REG(priv, f->m.reg_WPTR, f->m.wptr & TXF_WPTR_WR_PTR);
	RET();
पूर्ण

अटल अंतरभूत व्योम
NETIF_RX_MUX(काष्ठा bdx_priv *priv, u32 rxd_val1, u16 rxd_vlan,
	     काष्ठा sk_buff *skb)
अणु
	ENTER;
	DBG("rxdd->flags.bits.vtag=%d\n", GET_RXD_VTAG(rxd_val1));
	अगर (GET_RXD_VTAG(rxd_val1)) अणु
		DBG("%s: vlan rcv vlan '%x' vtag '%x'\n",
		    priv->ndev->name,
		    GET_RXD_VLAN_ID(rxd_vlan),
		    GET_RXD_VTAG(rxd_val1));
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), GET_RXD_VLAN_TCI(rxd_vlan));
	पूर्ण
	netअगर_receive_skb(skb);
पूर्ण

अटल व्योम bdx_recycle_skb(काष्ठा bdx_priv *priv, काष्ठा rxd_desc *rxdd)
अणु
	काष्ठा rxf_desc *rxfd;
	काष्ठा rx_map *dm;
	काष्ठा rxf_fअगरo *f;
	काष्ठा rxdb *db;
	पूर्णांक delta;

	ENTER;
	DBG("priv=%p rxdd=%p\n", priv, rxdd);
	f = &priv->rxf_fअगरo0;
	db = priv->rxdb;
	DBG("db=%p f=%p\n", db, f);
	dm = bdx_rxdb_addr_elem(db, rxdd->va_lo);
	DBG("dm=%p\n", dm);
	rxfd = (काष्ठा rxf_desc *)(f->m.va + f->m.wptr);
	rxfd->info = CPU_CHIP_SWAP32(0x10003);	/* INFO=1 BC=3 */
	rxfd->va_lo = rxdd->va_lo;
	rxfd->pa_lo = CPU_CHIP_SWAP32(L32_64(dm->dma));
	rxfd->pa_hi = CPU_CHIP_SWAP32(H32_64(dm->dma));
	rxfd->len = CPU_CHIP_SWAP32(f->m.pktsz);
	prपूर्णांक_rxfd(rxfd);

	f->m.wptr += माप(काष्ठा rxf_desc);
	delta = f->m.wptr - f->m.memsz;
	अगर (unlikely(delta >= 0)) अणु
		f->m.wptr = delta;
		अगर (delta > 0) अणु
			स_नकल(f->m.va, f->m.va + f->m.memsz, delta);
			DBG("wrapped descriptor\n");
		पूर्ण
	पूर्ण
	RET();
पूर्ण

/**
 * bdx_rx_receive - receives full packets from RXD fअगरo and pass them to OS
 * NOTE: a special treaपंचांगent is given to non-continuous descriptors
 * that start near the end, wraps around and जारी at the beginning. a second
 * part is copied right after the first, and then descriptor is पूर्णांकerpreted as
 * normal. fअगरo has an extra space to allow such operations
 * @priv: nic's निजी काष्ठाure
 * @f: RXF fअगरo that needs skbs
 * @budget: maximum number of packets to receive
 */

/* TBD: replace स_नकल func call by explicite अंतरभूत यंत्र */

अटल पूर्णांक bdx_rx_receive(काष्ठा bdx_priv *priv, काष्ठा rxd_fअगरo *f, पूर्णांक budget)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा sk_buff *skb, *skb2;
	काष्ठा rxd_desc *rxdd;
	काष्ठा rx_map *dm;
	काष्ठा rxf_fअगरo *rxf_fअगरo;
	पूर्णांक पंचांगp_len, size;
	पूर्णांक करोne = 0;
	पूर्णांक max_करोne = BDX_MAX_RX_DONE;
	काष्ठा rxdb *db = शून्य;
	/* Unmarshalled descriptor - copy of descriptor in host order */
	u32 rxd_val1;
	u16 len;
	u16 rxd_vlan;

	ENTER;
	max_करोne = budget;

	f->m.wptr = READ_REG(priv, f->m.reg_WPTR) & TXF_WPTR_WR_PTR;

	size = f->m.wptr - f->m.rptr;
	अगर (size < 0)
		size = f->m.memsz + size;	/* size is negative :-) */

	जबतक (size > 0) अणु

		rxdd = (काष्ठा rxd_desc *)(f->m.va + f->m.rptr);
		rxd_val1 = CPU_CHIP_SWAP32(rxdd->rxd_val1);

		len = CPU_CHIP_SWAP16(rxdd->len);

		rxd_vlan = CPU_CHIP_SWAP16(rxdd->rxd_vlan);

		prपूर्णांक_rxdd(rxdd, rxd_val1, len, rxd_vlan);

		पंचांगp_len = GET_RXD_BC(rxd_val1) << 3;
		BDX_ASSERT(पंचांगp_len <= 0);
		size -= पंचांगp_len;
		अगर (size < 0)	/* test क्रम partially arrived descriptor */
			अवरोध;

		f->m.rptr += पंचांगp_len;

		पंचांगp_len = f->m.rptr - f->m.memsz;
		अगर (unlikely(पंचांगp_len >= 0)) अणु
			f->m.rptr = पंचांगp_len;
			अगर (पंचांगp_len > 0) अणु
				DBG("wrapped desc rptr=%d tmp_len=%d\n",
				    f->m.rptr, पंचांगp_len);
				स_नकल(f->m.va + f->m.memsz, f->m.va, पंचांगp_len);
			पूर्ण
		पूर्ण

		अगर (unlikely(GET_RXD_ERR(rxd_val1))) अणु
			DBG("rxd_err = 0x%x\n", GET_RXD_ERR(rxd_val1));
			ndev->stats.rx_errors++;
			bdx_recycle_skb(priv, rxdd);
			जारी;
		पूर्ण

		rxf_fअगरo = &priv->rxf_fअगरo0;
		db = priv->rxdb;
		dm = bdx_rxdb_addr_elem(db, rxdd->va_lo);
		skb = dm->skb;

		अगर (len < BDX_COPYBREAK &&
		    (skb2 = netdev_alloc_skb(priv->ndev, len + NET_IP_ALIGN))) अणु
			skb_reserve(skb2, NET_IP_ALIGN);
			/*skb_put(skb2, len); */
			dma_sync_single_क्रम_cpu(&priv->pdev->dev, dm->dma,
						rxf_fअगरo->m.pktsz,
						DMA_FROM_DEVICE);
			स_नकल(skb2->data, skb->data, len);
			bdx_recycle_skb(priv, rxdd);
			skb = skb2;
		पूर्ण अन्यथा अणु
			dma_unmap_single(&priv->pdev->dev, dm->dma,
					 rxf_fअगरo->m.pktsz, DMA_FROM_DEVICE);
			bdx_rxdb_मुक्त_elem(db, rxdd->va_lo);
		पूर्ण

		ndev->stats.rx_bytes += len;

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, ndev);

		/* Non-IP packets aren't checksum-offloaded */
		अगर (GET_RXD_PKT_ID(rxd_val1) == 0)
			skb_checksum_none_निश्चित(skb);
		अन्यथा
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		NETIF_RX_MUX(priv, rxd_val1, rxd_vlan, skb);

		अगर (++करोne >= max_करोne)
			अवरोध;
	पूर्ण

	ndev->stats.rx_packets += करोne;

	/* FIXME: करो smth to minimize pci accesses    */
	WRITE_REG(priv, f->m.reg_RPTR, f->m.rptr & TXF_WPTR_WR_PTR);

	bdx_rx_alloc_skbs(priv, &priv->rxf_fअगरo0);

	RET(करोne);
पूर्ण

/*************************************************************************
 * Debug / Temprorary Code                                               *
 *************************************************************************/
अटल व्योम prपूर्णांक_rxdd(काष्ठा rxd_desc *rxdd, u32 rxd_val1, u16 len,
		       u16 rxd_vlan)
अणु
	DBG("ERROR: rxdd bc %d rxfq %d to %d type %d err %d rxp %d pkt_id %d vtag %d len %d vlan_id %d cfi %d prio %d va_lo %d va_hi %d\n",
	    GET_RXD_BC(rxd_val1), GET_RXD_RXFQ(rxd_val1), GET_RXD_TO(rxd_val1),
	    GET_RXD_TYPE(rxd_val1), GET_RXD_ERR(rxd_val1),
	    GET_RXD_RXP(rxd_val1), GET_RXD_PKT_ID(rxd_val1),
	    GET_RXD_VTAG(rxd_val1), len, GET_RXD_VLAN_ID(rxd_vlan),
	    GET_RXD_CFI(rxd_vlan), GET_RXD_PRIO(rxd_vlan), rxdd->va_lo,
	    rxdd->va_hi);
पूर्ण

अटल व्योम prपूर्णांक_rxfd(काष्ठा rxf_desc *rxfd)
अणु
	DBG("=== RxF desc CHIP ORDER/ENDIANNESS =============\n"
	    "info 0x%x va_lo %u pa_lo 0x%x pa_hi 0x%x len 0x%x\n",
	    rxfd->info, rxfd->va_lo, rxfd->pa_lo, rxfd->pa_hi, rxfd->len);
पूर्ण

/*
 * TX HW/SW पूर्णांकeraction overview
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * There are 2 types of TX communication channels between driver and NIC.
 * 1) TX Free Fअगरo - TXF - holds ack descriptors क्रम sent packets
 * 2) TX Data Fअगरo - TXD - holds descriptors of full buffers.
 *
 * Currently NIC supports TSO, checksuming and gather DMA
 * UFO and IP fragmentation is on the way
 *
 * RX SW Data Structures
 * ~~~~~~~~~~~~~~~~~~~~~
 * txdb - used to keep track of all skbs owned by SW and their dma addresses.
 * For TX हाल, ownership lasts from geting packet via hard_xmit and until HW
 * acknowledges sent by TXF descriptors.
 * Implemented as cyclic buffer.
 * fअगरo - keeps info about fअगरo's size and location, relevant HW रेजिस्टरs,
 * usage and skb db. Each RXD and RXF Fअगरo has its own fअगरo काष्ठाure.
 * Implemented as simple काष्ठा.
 *
 * TX SW Execution Flow
 * ~~~~~~~~~~~~~~~~~~~~
 * OS calls driver's hard_xmit method with packet to sent.
 * Driver creates DMA mappings, builds TXD descriptors and kicks HW
 * by updating TXD WPTR.
 * When packet is sent, HW ग_लिखो us TXF descriptor and SW मुक्तs original skb.
 * To prevent TXD fअगरo overflow without पढ़ोing HW रेजिस्टरs every समय,
 * SW deploys "tx level" technique.
 * Upon strart up, tx level is initialized to TXD fअगरo length.
 * For every sent packet, SW माला_लो its TXD descriptor sizei
 * (from precalculated array) and subकाष्ठाs it from tx level.
 * The size is also stored in txdb. When TXF ack arrives, SW fetch size of
 * original TXD descriptor from txdb and adds it to tx level.
 * When Tx level drops under some predefined treshhold, the driver
 * stops the TX queue. When TX level rises above that level,
 * the tx queue is enabled again.
 *
 * This technique aव्योमs eccessive पढ़ोing of RPTR and WPTR रेजिस्टरs.
 * As our benchmarks shows, it adds 1.5 Gbit/sec to NIS's throuput.
 */

/**
 * __bdx_tx_db_ptr_next - helper function, increment पढ़ो/ग_लिखो poपूर्णांकer + wrap
 * @db: tx data base
 * @pptr: पढ़ो or ग_लिखो poपूर्णांकer
 */
अटल अंतरभूत व्योम __bdx_tx_db_ptr_next(काष्ठा txdb *db, काष्ठा tx_map **pptr)
अणु
	BDX_ASSERT(db == शून्य || pptr == शून्य);	/* sanity */

	BDX_ASSERT(*pptr != db->rptr &&	/* expect either पढ़ो */
		   *pptr != db->wptr);	/* or ग_लिखो poपूर्णांकer */

	BDX_ASSERT(*pptr < db->start ||	/* poपूर्णांकer has to be */
		   *pptr >= db->end);	/* in range */

	++*pptr;
	अगर (unlikely(*pptr == db->end))
		*pptr = db->start;
पूर्ण

/**
 * bdx_tx_db_inc_rptr - increment पढ़ो poपूर्णांकer
 * @db: tx data base
 */
अटल अंतरभूत व्योम bdx_tx_db_inc_rptr(काष्ठा txdb *db)
अणु
	BDX_ASSERT(db->rptr == db->wptr);	/* can't पढ़ो from empty db */
	__bdx_tx_db_ptr_next(db, &db->rptr);
पूर्ण

/**
 * bdx_tx_db_inc_wptr - increment ग_लिखो poपूर्णांकer
 * @db: tx data base
 */
अटल अंतरभूत व्योम bdx_tx_db_inc_wptr(काष्ठा txdb *db)
अणु
	__bdx_tx_db_ptr_next(db, &db->wptr);
	BDX_ASSERT(db->rptr == db->wptr);	/* we can not get empty db as
						   a result of ग_लिखो */
पूर्ण

/**
 * bdx_tx_db_init - creates and initializes tx db
 * @d: tx data base
 * @sz_type: size of tx fअगरo
 *
 * Returns 0 on success, error code otherwise
 */
अटल पूर्णांक bdx_tx_db_init(काष्ठा txdb *d, पूर्णांक sz_type)
अणु
	पूर्णांक memsz = FIFO_SIZE * (1 << (sz_type + 1));

	d->start = vदो_स्मृति(memsz);
	अगर (!d->start)
		वापस -ENOMEM;

	/*
	 * In order to dअगरferentiate between db is empty and db is full
	 * states at least one element should always be empty in order to
	 * aव्योम rptr == wptr which means db is empty
	 */
	d->size = memsz / माप(काष्ठा tx_map) - 1;
	d->end = d->start + d->size + 1;	/* just after last element */

	/* all dbs are created equally empty */
	d->rptr = d->start;
	d->wptr = d->start;

	वापस 0;
पूर्ण

/**
 * bdx_tx_db_बंद - बंदs tx db and मुक्तs all memory
 * @d: tx data base
 */
अटल व्योम bdx_tx_db_बंद(काष्ठा txdb *d)
अणु
	BDX_ASSERT(d == शून्य);

	vमुक्त(d->start);
	d->start = शून्य;
पूर्ण

/*************************************************************************
 *     Tx Engine                                                         *
 *************************************************************************/

/* sizes of tx desc (including padding अगर needed) as function
 * of skb's frag number */
अटल काष्ठा अणु
	u16 bytes;
	u16 qwords;		/* qword = 64 bit */
पूर्ण txd_sizes[MAX_SKB_FRAGS + 1];

/**
 * bdx_tx_map_skb - creates and stores dma mappings क्रम skb's data blocks
 * @priv: NIC निजी काष्ठाure
 * @skb: socket buffer to map
 * @txdd: TX descriptor to use
 *
 * It makes dma mappings क्रम skb's data blocks and ग_लिखोs them to PBL of
 * new tx descriptor. It also stores them in the tx db, so they could be
 * unmaped after data was sent. It is reponsibility of a caller to make
 * sure that there is enough space in the tx db. Last element holds poपूर्णांकer
 * to skb itself and marked with zero length
 */
अटल अंतरभूत व्योम
bdx_tx_map_skb(काष्ठा bdx_priv *priv, काष्ठा sk_buff *skb,
	       काष्ठा txd_desc *txdd)
अणु
	काष्ठा txdb *db = &priv->txdb;
	काष्ठा pbl *pbl = &txdd->pbl[0];
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक i;

	db->wptr->len = skb_headlen(skb);
	db->wptr->addr.dma = dma_map_single(&priv->pdev->dev, skb->data,
					    db->wptr->len, DMA_TO_DEVICE);
	pbl->len = CPU_CHIP_SWAP32(db->wptr->len);
	pbl->pa_lo = CPU_CHIP_SWAP32(L32_64(db->wptr->addr.dma));
	pbl->pa_hi = CPU_CHIP_SWAP32(H32_64(db->wptr->addr.dma));
	DBG("=== pbl   len: 0x%x ================\n", pbl->len);
	DBG("=== pbl pa_lo: 0x%x ================\n", pbl->pa_lo);
	DBG("=== pbl pa_hi: 0x%x ================\n", pbl->pa_hi);
	bdx_tx_db_inc_wptr(db);

	क्रम (i = 0; i < nr_frags; i++) अणु
		स्थिर skb_frag_t *frag;

		frag = &skb_shinfo(skb)->frags[i];
		db->wptr->len = skb_frag_size(frag);
		db->wptr->addr.dma = skb_frag_dma_map(&priv->pdev->dev, frag,
						      0, skb_frag_size(frag),
						      DMA_TO_DEVICE);

		pbl++;
		pbl->len = CPU_CHIP_SWAP32(db->wptr->len);
		pbl->pa_lo = CPU_CHIP_SWAP32(L32_64(db->wptr->addr.dma));
		pbl->pa_hi = CPU_CHIP_SWAP32(H32_64(db->wptr->addr.dma));
		bdx_tx_db_inc_wptr(db);
	पूर्ण

	/* add skb clean up info. */
	db->wptr->len = -txd_sizes[nr_frags].bytes;
	db->wptr->addr.skb = skb;
	bdx_tx_db_inc_wptr(db);
पूर्ण

/* init_txd_sizes - precalculate sizes of descriptors क्रम skbs up to 16 frags
 * number of frags is used as index to fetch correct descriptors size,
 * instead of calculating it each समय */
अटल व्योम __init init_txd_sizes(व्योम)
अणु
	पूर्णांक i, lwords;

	/* 7 - is number of lwords in txd with one phys buffer
	 * 3 - is number of lwords used क्रम every additional phys buffer */
	क्रम (i = 0; i < MAX_SKB_FRAGS + 1; i++) अणु
		lwords = 7 + (i * 3);
		अगर (lwords & 1)
			lwords++;	/* pad it with 1 lword */
		txd_sizes[i].qwords = lwords >> 1;
		txd_sizes[i].bytes = lwords << 2;
	पूर्ण
पूर्ण

/* bdx_tx_init - initialize all Tx related stuff.
 * Namely, TXD and TXF fअगरos, database etc */
अटल पूर्णांक bdx_tx_init(काष्ठा bdx_priv *priv)
अणु
	अगर (bdx_fअगरo_init(priv, &priv->txd_fअगरo0.m, priv->txd_size,
			  regTXD_CFG0_0,
			  regTXD_CFG1_0, regTXD_RPTR_0, regTXD_WPTR_0))
		जाओ err_mem;
	अगर (bdx_fअगरo_init(priv, &priv->txf_fअगरo0.m, priv->txf_size,
			  regTXF_CFG0_0,
			  regTXF_CFG1_0, regTXF_RPTR_0, regTXF_WPTR_0))
		जाओ err_mem;

	/* The TX db has to keep mappings क्रम all packets sent (on TxD)
	 * and not yet reclaimed (on TxF) */
	अगर (bdx_tx_db_init(&priv->txdb, max(priv->txd_size, priv->txf_size)))
		जाओ err_mem;

	priv->tx_level = BDX_MAX_TX_LEVEL;
#अगर_घोषित BDX_DELAY_WPTR
	priv->tx_update_mark = priv->tx_level - 1024;
#पूर्ण_अगर
	वापस 0;

err_mem:
	netdev_err(priv->ndev, "Tx init failed\n");
	वापस -ENOMEM;
पूर्ण

/**
 * bdx_tx_space - calculates available space in TX fअगरo
 * @priv: NIC निजी काष्ठाure
 *
 * Returns available space in TX fअगरo in bytes
 */
अटल अंतरभूत पूर्णांक bdx_tx_space(काष्ठा bdx_priv *priv)
अणु
	काष्ठा txd_fअगरo *f = &priv->txd_fअगरo0;
	पूर्णांक fsize;

	f->m.rptr = READ_REG(priv, f->m.reg_RPTR) & TXF_WPTR_WR_PTR;
	fsize = f->m.rptr - f->m.wptr;
	अगर (fsize <= 0)
		fsize = f->m.memsz + fsize;
	वापस fsize;
पूर्ण

/**
 * bdx_tx_transmit - send packet to NIC
 * @skb: packet to send
 * @ndev: network device asचिन्हित to NIC
 * Return codes:
 * o NETDEV_TX_OK everything ok.
 * o NETDEV_TX_BUSY Cannot transmit packet, try later
 *   Usually a bug, means queue start/stop flow control is broken in
 *   the driver. Note: the driver must NOT put the skb in its DMA ring.
 */
अटल netdev_tx_t bdx_tx_transmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *ndev)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(ndev);
	काष्ठा txd_fअगरo *f = &priv->txd_fअगरo0;
	पूर्णांक txd_checksum = 7;	/* full checksum */
	पूर्णांक txd_lgsnd = 0;
	पूर्णांक txd_vlan_id = 0;
	पूर्णांक txd_vtag = 0;
	पूर्णांक txd_mss = 0;

	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	काष्ठा txd_desc *txdd;
	पूर्णांक len;
	अचिन्हित दीर्घ flags;

	ENTER;
	local_irq_save(flags);
	spin_lock(&priv->tx_lock);

	/* build tx descriptor */
	BDX_ASSERT(f->m.wptr >= f->m.memsz);	/* started with valid wptr */
	txdd = (काष्ठा txd_desc *)(f->m.va + f->m.wptr);
	अगर (unlikely(skb->ip_summed != CHECKSUM_PARTIAL))
		txd_checksum = 0;

	अगर (skb_shinfo(skb)->gso_size) अणु
		txd_mss = skb_shinfo(skb)->gso_size;
		txd_lgsnd = 1;
		DBG("skb %p skb len %d gso size = %d\n", skb, skb->len,
		    txd_mss);
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		/*Cut VLAN ID to 12 bits */
		txd_vlan_id = skb_vlan_tag_get(skb) & BITS_MASK(12);
		txd_vtag = 1;
	पूर्ण

	txdd->length = CPU_CHIP_SWAP16(skb->len);
	txdd->mss = CPU_CHIP_SWAP16(txd_mss);
	txdd->txd_val1 =
	    CPU_CHIP_SWAP32(TXD_W1_VAL
			    (txd_sizes[nr_frags].qwords, txd_checksum, txd_vtag,
			     txd_lgsnd, txd_vlan_id));
	DBG("=== TxD desc =====================\n");
	DBG("=== w1: 0x%x ================\n", txdd->txd_val1);
	DBG("=== w2: mss 0x%x len 0x%x\n", txdd->mss, txdd->length);

	bdx_tx_map_skb(priv, skb, txdd);

	/* increment TXD ग_लिखो poपूर्णांकer. In हाल of
	   fअगरo wrapping copy reminder of the descriptor
	   to the beginning */
	f->m.wptr += txd_sizes[nr_frags].bytes;
	len = f->m.wptr - f->m.memsz;
	अगर (unlikely(len >= 0)) अणु
		f->m.wptr = len;
		अगर (len > 0) अणु
			BDX_ASSERT(len > f->m.memsz);
			स_नकल(f->m.va, f->m.va + f->m.memsz, len);
		पूर्ण
	पूर्ण
	BDX_ASSERT(f->m.wptr >= f->m.memsz);	/* finished with valid wptr */

	priv->tx_level -= txd_sizes[nr_frags].bytes;
	BDX_ASSERT(priv->tx_level <= 0 || priv->tx_level > BDX_MAX_TX_LEVEL);
#अगर_घोषित BDX_DELAY_WPTR
	अगर (priv->tx_level > priv->tx_update_mark) अणु
		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		   know there are new descriptors to fetch.
		   (might be needed on platक्रमms like IA64)
		   wmb(); */
		WRITE_REG(priv, f->m.reg_WPTR, f->m.wptr & TXF_WPTR_WR_PTR);
	पूर्ण अन्यथा अणु
		अगर (priv->tx_noupd++ > BDX_NO_UPD_PACKETS) अणु
			priv->tx_noupd = 0;
			WRITE_REG(priv, f->m.reg_WPTR,
				  f->m.wptr & TXF_WPTR_WR_PTR);
		पूर्ण
	पूर्ण
#अन्यथा
	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	   know there are new descriptors to fetch.
	   (might be needed on platक्रमms like IA64)
	   wmb(); */
	WRITE_REG(priv, f->m.reg_WPTR, f->m.wptr & TXF_WPTR_WR_PTR);

#पूर्ण_अगर
#अगर_घोषित BDX_LLTX
	netअगर_trans_update(ndev); /* NETIF_F_LLTX driver :( */
#पूर्ण_अगर
	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += skb->len;

	अगर (priv->tx_level < BDX_MIN_TX_LEVEL) अणु
		DBG("%s: %s: TX Q STOP level %d\n",
		    BDX_DRV_NAME, ndev->name, priv->tx_level);
		netअगर_stop_queue(ndev);
	पूर्ण

	spin_unlock_irqrestore(&priv->tx_lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * bdx_tx_cleanup - clean TXF fअगरo, run in the context of IRQ.
 * @priv: bdx adapter
 *
 * It scans TXF fअगरo क्रम descriptors, मुक्तs DMA mappings and reports to OS
 * that those packets were sent
 */
अटल व्योम bdx_tx_cleanup(काष्ठा bdx_priv *priv)
अणु
	काष्ठा txf_fअगरo *f = &priv->txf_fअगरo0;
	काष्ठा txdb *db = &priv->txdb;
	पूर्णांक tx_level = 0;

	ENTER;
	f->m.wptr = READ_REG(priv, f->m.reg_WPTR) & TXF_WPTR_MASK;
	BDX_ASSERT(f->m.rptr >= f->m.memsz);	/* started with valid rptr */

	जबतक (f->m.wptr != f->m.rptr) अणु
		f->m.rptr += BDX_TXF_DESC_SZ;
		f->m.rptr &= f->m.size_mask;

		/* unmap all the fragments */
		/* first has to come tx_maps containing dma */
		BDX_ASSERT(db->rptr->len == 0);
		करो अणु
			BDX_ASSERT(db->rptr->addr.dma == 0);
			dma_unmap_page(&priv->pdev->dev, db->rptr->addr.dma,
				       db->rptr->len, DMA_TO_DEVICE);
			bdx_tx_db_inc_rptr(db);
		पूर्ण जबतक (db->rptr->len > 0);
		tx_level -= db->rptr->len;	/* '-' koz len is negative */

		/* now should come skb poपूर्णांकer - मुक्त it */
		dev_consume_skb_irq(db->rptr->addr.skb);
		bdx_tx_db_inc_rptr(db);
	पूर्ण

	/* let h/w know which TXF descriptors were cleaned */
	BDX_ASSERT((f->m.wptr & TXF_WPTR_WR_PTR) >= f->m.memsz);
	WRITE_REG(priv, f->m.reg_RPTR, f->m.rptr & TXF_WPTR_WR_PTR);

	/* We reclaimed resources, so in हाल the Q is stopped by xmit callback,
	 * we resume the transmission and use tx_lock to synchronize with xmit.*/
	spin_lock(&priv->tx_lock);
	priv->tx_level += tx_level;
	BDX_ASSERT(priv->tx_level <= 0 || priv->tx_level > BDX_MAX_TX_LEVEL);
#अगर_घोषित BDX_DELAY_WPTR
	अगर (priv->tx_noupd) अणु
		priv->tx_noupd = 0;
		WRITE_REG(priv, priv->txd_fअगरo0.m.reg_WPTR,
			  priv->txd_fअगरo0.m.wptr & TXF_WPTR_WR_PTR);
	पूर्ण
#पूर्ण_अगर

	अगर (unlikely(netअगर_queue_stopped(priv->ndev) &&
		     netअगर_carrier_ok(priv->ndev) &&
		     (priv->tx_level >= BDX_MIN_TX_LEVEL))) अणु
		DBG("%s: %s: TX Q WAKE level %d\n",
		    BDX_DRV_NAME, priv->ndev->name, priv->tx_level);
		netअगर_wake_queue(priv->ndev);
	पूर्ण
	spin_unlock(&priv->tx_lock);
पूर्ण

/**
 * bdx_tx_मुक्त_skbs - मुक्तs all skbs from TXD fअगरo.
 * @priv: NIC निजी काष्ठाure
 *
 * It माला_लो called when OS stops this dev, eg upon "ifconfig down" or rmmod
 */
अटल व्योम bdx_tx_मुक्त_skbs(काष्ठा bdx_priv *priv)
अणु
	काष्ठा txdb *db = &priv->txdb;

	ENTER;
	जबतक (db->rptr != db->wptr) अणु
		अगर (likely(db->rptr->len))
			dma_unmap_page(&priv->pdev->dev, db->rptr->addr.dma,
				       db->rptr->len, DMA_TO_DEVICE);
		अन्यथा
			dev_kमुक्त_skb(db->rptr->addr.skb);
		bdx_tx_db_inc_rptr(db);
	पूर्ण
	RET();
पूर्ण

/* bdx_tx_मुक्त - मुक्तs all Tx resources */
अटल व्योम bdx_tx_मुक्त(काष्ठा bdx_priv *priv)
अणु
	ENTER;
	bdx_tx_मुक्त_skbs(priv);
	bdx_fअगरo_मुक्त(priv, &priv->txd_fअगरo0.m);
	bdx_fअगरo_मुक्त(priv, &priv->txf_fअगरo0.m);
	bdx_tx_db_बंद(&priv->txdb);
पूर्ण

/**
 * bdx_tx_push_desc - push descriptor to TxD fअगरo
 * @priv: NIC निजी काष्ठाure
 * @data: desc's data
 * @size: desc's size
 *
 * Pushes desc to TxD fअगरo and overlaps it अगर needed.
 * NOTE: this func करोes not check क्रम available space. this is responsibility
 *    of the caller. Neither करोes it check that data size is smaller than
 *    fअगरo size.
 */
अटल व्योम bdx_tx_push_desc(काष्ठा bdx_priv *priv, व्योम *data, पूर्णांक size)
अणु
	काष्ठा txd_fअगरo *f = &priv->txd_fअगरo0;
	पूर्णांक i = f->m.memsz - f->m.wptr;

	अगर (size == 0)
		वापस;

	अगर (i > size) अणु
		स_नकल(f->m.va + f->m.wptr, data, size);
		f->m.wptr += size;
	पूर्ण अन्यथा अणु
		स_नकल(f->m.va + f->m.wptr, data, i);
		f->m.wptr = size - i;
		स_नकल(f->m.va, data + i, f->m.wptr);
	पूर्ण
	WRITE_REG(priv, f->m.reg_WPTR, f->m.wptr & TXF_WPTR_WR_PTR);
पूर्ण

/**
 * bdx_tx_push_desc_safe - push descriptor to TxD fअगरo in a safe way
 * @priv: NIC निजी काष्ठाure
 * @data: desc's data
 * @size: desc's size
 *
 * NOTE: this func करोes check क्रम available space and, अगर necessary, रुकोs क्रम
 *   NIC to पढ़ो existing data beक्रमe writing new one.
 */
अटल व्योम bdx_tx_push_desc_safe(काष्ठा bdx_priv *priv, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक समयr = 0;
	ENTER;

	जबतक (size > 0) अणु
		/* we subकाष्ठा 8 because when fअगरo is full rptr == wptr
		   which also means that fअगरo is empty, we can understand
		   the dअगरference, but could hw करो the same ??? :) */
		पूर्णांक avail = bdx_tx_space(priv) - 8;
		अगर (avail <= 0) अणु
			अगर (समयr++ > 300) अणु	/* prevent endless loop */
				DBG("timeout while writing desc to TxD fifo\n");
				अवरोध;
			पूर्ण
			udelay(50);	/* give hw a chance to clean fअगरo */
			जारी;
		पूर्ण
		avail = min(avail, size);
		DBG("about to push  %d bytes starting %p size %d\n", avail,
		    data, size);
		bdx_tx_push_desc(priv, data, avail);
		size -= avail;
		data += avail;
	पूर्ण
	RET();
पूर्ण

अटल स्थिर काष्ठा net_device_ops bdx_netdev_ops = अणु
	.nकरो_खोलो		= bdx_खोलो,
	.nकरो_stop		= bdx_बंद,
	.nकरो_start_xmit		= bdx_tx_transmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= bdx_ioctl,
	.nकरो_set_rx_mode	= bdx_seपंचांगulti,
	.nकरो_change_mtu		= bdx_change_mtu,
	.nकरो_set_mac_address	= bdx_set_mac,
	.nकरो_vlan_rx_add_vid	= bdx_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= bdx_vlan_rx_समाप्त_vid,
पूर्ण;

/**
 * bdx_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in bdx_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * bdx_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 *
 * functions and their order used as explained in
 * /usr/src/linux/Documentation/DMA-अणुAPI,mappingपूर्ण.txt
 *
 */

/* TBD: netअगर_msg should be checked and implemented. I disable it क्रम now */
अटल पूर्णांक
bdx_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *ndev;
	काष्ठा bdx_priv *priv;
	पूर्णांक err, pci_using_dac, port;
	अचिन्हित दीर्घ pciaddr;
	u32 regionSize;
	काष्ठा pci_nic *nic;

	ENTER;

	nic = vदो_स्मृति(माप(*nic));
	अगर (!nic)
		RET(-ENOMEM);

    /************** pci *****************/
	err = pci_enable_device(pdev);
	अगर (err)			/* it triggers पूर्णांकerrupt, dunno why. */
		जाओ err_pci;		/* it's not a problem though */

	अगर (!(err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) &&
	    !(err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64)))) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		अगर ((err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) ||
		    (err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32)))) अणु
			pr_err("No usable DMA configuration, aborting\n");
			जाओ err_dma;
		पूर्ण
		pci_using_dac = 0;
	पूर्ण

	err = pci_request_regions(pdev, BDX_DRV_NAME);
	अगर (err)
		जाओ err_dma;

	pci_set_master(pdev);

	pciaddr = pci_resource_start(pdev, 0);
	अगर (!pciaddr) अणु
		err = -EIO;
		pr_err("no MMIO resource\n");
		जाओ err_out_res;
	पूर्ण
	regionSize = pci_resource_len(pdev, 0);
	अगर (regionSize < BDX_REGS_SIZE) अणु
		err = -EIO;
		pr_err("MMIO resource (%x) too small\n", regionSize);
		जाओ err_out_res;
	पूर्ण

	nic->regs = ioremap(pciaddr, regionSize);
	अगर (!nic->regs) अणु
		err = -EIO;
		pr_err("ioremap failed\n");
		जाओ err_out_res;
	पूर्ण

	अगर (pdev->irq < 2) अणु
		err = -EIO;
		pr_err("invalid irq (%d)\n", pdev->irq);
		जाओ err_out_iomap;
	पूर्ण
	pci_set_drvdata(pdev, nic);

	अगर (pdev->device == 0x3014)
		nic->port_num = 2;
	अन्यथा
		nic->port_num = 1;

	prपूर्णांक_hw_id(pdev);

	bdx_hw_reset_direct(nic->regs);

	nic->irq_type = IRQ_INTX;
#अगर_घोषित BDX_MSI
	अगर ((पढ़ोl(nic->regs + FPGA_VER) & 0xFFF) >= 378) अणु
		err = pci_enable_msi(pdev);
		अगर (err)
			pr_err("Can't enable msi. error is %d\n", err);
		अन्यथा
			nic->irq_type = IRQ_MSI;
	पूर्ण अन्यथा
		DBG("HW does not support MSI\n");
#पूर्ण_अगर

    /************** netdev **************/
	क्रम (port = 0; port < nic->port_num; port++) अणु
		ndev = alloc_etherdev(माप(काष्ठा bdx_priv));
		अगर (!ndev) अणु
			err = -ENOMEM;
			जाओ err_out_iomap;
		पूर्ण

		ndev->netdev_ops = &bdx_netdev_ops;
		ndev->tx_queue_len = BDX_NDEV_TXQ_LEN;

		bdx_set_ethtool_ops(ndev);	/* ethtool पूर्णांकerface */

		/* these fields are used क्रम info purposes only
		 * so we can have them same क्रम all ports of the board */
		ndev->अगर_port = port;
		ndev->features = NETIF_F_IP_CSUM | NETIF_F_SG | NETIF_F_TSO
		    | NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
		    NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_RXCSUM
		    ;
		ndev->hw_features = NETIF_F_IP_CSUM | NETIF_F_SG |
			NETIF_F_TSO | NETIF_F_HW_VLAN_CTAG_TX;

		अगर (pci_using_dac)
			ndev->features |= NETIF_F_HIGHDMA;

	/************** priv ****************/
		priv = nic->priv[port] = netdev_priv(ndev);

		priv->pBdxRegs = nic->regs + port * 0x8000;
		priv->port = port;
		priv->pdev = pdev;
		priv->ndev = ndev;
		priv->nic = nic;
		priv->msg_enable = BDX_DEF_MSG_ENABLE;

		netअगर_napi_add(ndev, &priv->napi, bdx_poll, 64);

		अगर ((पढ़ोl(nic->regs + FPGA_VER) & 0xFFF) == 308) अणु
			DBG("HW statistics not supported\n");
			priv->stats_flag = 0;
		पूर्ण अन्यथा अणु
			priv->stats_flag = 1;
		पूर्ण

		/* Initialize fअगरo sizes. */
		priv->txd_size = 2;
		priv->txf_size = 2;
		priv->rxd_size = 2;
		priv->rxf_size = 3;

		/* Initialize the initial coalescing रेजिस्टरs. */
		priv->rdपूर्णांकcm = INT_REG_VAL(0x20, 1, 4, 12);
		priv->tdपूर्णांकcm = INT_REG_VAL(0x20, 1, 0, 12);

		/* ndev->xmit_lock spinlock is not used.
		 * Private priv->tx_lock is used क्रम synchronization
		 * between transmit and TX irq cleanup.  In addition
		 * set multicast list callback has to use priv->tx_lock.
		 */
#अगर_घोषित BDX_LLTX
		ndev->features |= NETIF_F_LLTX;
#पूर्ण_अगर
		/* MTU range: 60 - 16384 */
		ndev->min_mtu = ETH_ZLEN;
		ndev->max_mtu = BDX_MAX_MTU;

		spin_lock_init(&priv->tx_lock);

		/*bdx_hw_reset(priv); */
		अगर (bdx_पढ़ो_mac(priv)) अणु
			pr_err("load MAC address failed\n");
			err = -EFAULT;
			जाओ err_out_iomap;
		पूर्ण
		SET_NETDEV_DEV(ndev, &pdev->dev);
		err = रेजिस्टर_netdev(ndev);
		अगर (err) अणु
			pr_err("register_netdev failed\n");
			जाओ err_out_मुक्त;
		पूर्ण
		netअगर_carrier_off(ndev);
		netअगर_stop_queue(ndev);

		prपूर्णांक_eth_id(ndev);
	पूर्ण
	RET(0);

err_out_मुक्त:
	मुक्त_netdev(ndev);
err_out_iomap:
	iounmap(nic->regs);
err_out_res:
	pci_release_regions(pdev);
err_dma:
	pci_disable_device(pdev);
err_pci:
	vमुक्त(nic);

	RET(err);
पूर्ण

/****************** Ethtool पूर्णांकerface *********************/
/* get strings क्रम statistics counters */
अटल स्थिर अक्षर
 bdx_stat_names[][ETH_GSTRING_LEN] = अणु
	"InUCast",		/* 0x7200 */
	"InMCast",		/* 0x7210 */
	"InBCast",		/* 0x7220 */
	"InPkts",		/* 0x7230 */
	"InErrors",		/* 0x7240 */
	"InDropped",		/* 0x7250 */
	"FrameTooLong",		/* 0x7260 */
	"FrameSequenceErrors",	/* 0x7270 */
	"InVLAN",		/* 0x7280 */
	"InDroppedDFE",		/* 0x7290 */
	"InDroppedIntFull",	/* 0x72A0 */
	"InFrameAlignErrors",	/* 0x72B0 */

	/* 0x72C0-0x72E0 RSRV */

	"OutUCast",		/* 0x72F0 */
	"OutMCast",		/* 0x7300 */
	"OutBCast",		/* 0x7310 */
	"OutPkts",		/* 0x7320 */

	/* 0x7330-0x7360 RSRV */

	"OutVLAN",		/* 0x7370 */
	"InUCastOctects",	/* 0x7380 */
	"OutUCastOctects",	/* 0x7390 */

	/* 0x73A0-0x73B0 RSRV */

	"InBCastOctects",	/* 0x73C0 */
	"OutBCastOctects",	/* 0x73D0 */
	"InOctects",		/* 0x73E0 */
	"OutOctects",		/* 0x73F0 */
पूर्ण;

/*
 * bdx_get_link_ksettings - get device-specअगरic settings
 * @netdev
 * @ecmd
 */
अटल पूर्णांक bdx_get_link_ksettings(काष्ठा net_device *netdev,
				  काष्ठा ethtool_link_ksettings *ecmd)
अणु
	ethtool_link_ksettings_zero_link_mode(ecmd, supported);
	ethtool_link_ksettings_add_link_mode(ecmd, supported,
					     10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(ecmd, supported, FIBRE);
	ethtool_link_ksettings_zero_link_mode(ecmd, advertising);
	ethtool_link_ksettings_add_link_mode(ecmd, advertising,
					     10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(ecmd, advertising, FIBRE);

	ecmd->base.speed = SPEED_10000;
	ecmd->base.duplex = DUPLEX_FULL;
	ecmd->base.port = PORT_FIBRE;
	ecmd->base.स्वतःneg = AUTONEG_DISABLE;

	वापस 0;
पूर्ण

/*
 * bdx_get_drvinfo - report driver inक्रमmation
 * @netdev
 * @drvinfo
 */
अटल व्योम
bdx_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(netdev);

	strlcpy(drvinfo->driver, BDX_DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->version, BDX_DRV_VERSION, माप(drvinfo->version));
	strlcpy(drvinfo->fw_version, "N/A", माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(priv->pdev),
		माप(drvinfo->bus_info));
पूर्ण

/*
 * bdx_get_coalesce - get पूर्णांकerrupt coalescing parameters
 * @netdev
 * @ecoal
 */
अटल पूर्णांक
bdx_get_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ecoal)
अणु
	u32 rdपूर्णांकcm;
	u32 tdपूर्णांकcm;
	काष्ठा bdx_priv *priv = netdev_priv(netdev);

	rdपूर्णांकcm = priv->rdपूर्णांकcm;
	tdपूर्णांकcm = priv->tdपूर्णांकcm;

	/* PCK_TH measures in multiples of FIFO bytes
	   We translate to packets */
	ecoal->rx_coalesce_usecs = GET_INT_COAL(rdपूर्णांकcm) * INT_COAL_MULT;
	ecoal->rx_max_coalesced_frames =
	    ((GET_PCK_TH(rdपूर्णांकcm) * PCK_TH_MULT) / माप(काष्ठा rxf_desc));

	ecoal->tx_coalesce_usecs = GET_INT_COAL(tdपूर्णांकcm) * INT_COAL_MULT;
	ecoal->tx_max_coalesced_frames =
	    ((GET_PCK_TH(tdपूर्णांकcm) * PCK_TH_MULT) / BDX_TXF_DESC_SZ);

	/* adaptive parameters ignored */
	वापस 0;
पूर्ण

/*
 * bdx_set_coalesce - set पूर्णांकerrupt coalescing parameters
 * @netdev
 * @ecoal
 */
अटल पूर्णांक
bdx_set_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ecoal)
अणु
	u32 rdपूर्णांकcm;
	u32 tdपूर्णांकcm;
	काष्ठा bdx_priv *priv = netdev_priv(netdev);
	पूर्णांक rx_coal;
	पूर्णांक tx_coal;
	पूर्णांक rx_max_coal;
	पूर्णांक tx_max_coal;

	/* Check क्रम valid input */
	rx_coal = ecoal->rx_coalesce_usecs / INT_COAL_MULT;
	tx_coal = ecoal->tx_coalesce_usecs / INT_COAL_MULT;
	rx_max_coal = ecoal->rx_max_coalesced_frames;
	tx_max_coal = ecoal->tx_max_coalesced_frames;

	/* Translate from packets to multiples of FIFO bytes */
	rx_max_coal =
	    (((rx_max_coal * माप(काष्ठा rxf_desc)) + PCK_TH_MULT - 1)
	     / PCK_TH_MULT);
	tx_max_coal =
	    (((tx_max_coal * BDX_TXF_DESC_SZ) + PCK_TH_MULT - 1)
	     / PCK_TH_MULT);

	अगर ((rx_coal > 0x7FFF) || (tx_coal > 0x7FFF) ||
	    (rx_max_coal > 0xF) || (tx_max_coal > 0xF))
		वापस -EINVAL;

	rdपूर्णांकcm = INT_REG_VAL(rx_coal, GET_INT_COAL_RC(priv->rdपूर्णांकcm),
			      GET_RXF_TH(priv->rdपूर्णांकcm), rx_max_coal);
	tdपूर्णांकcm = INT_REG_VAL(tx_coal, GET_INT_COAL_RC(priv->tdपूर्णांकcm), 0,
			      tx_max_coal);

	priv->rdपूर्णांकcm = rdपूर्णांकcm;
	priv->tdपूर्णांकcm = tdपूर्णांकcm;

	WRITE_REG(priv, regRDINTCM0, rdपूर्णांकcm);
	WRITE_REG(priv, regTDINTCM0, tdपूर्णांकcm);

	वापस 0;
पूर्ण

/* Convert RX fअगरo size to number of pending packets */
अटल अंतरभूत पूर्णांक bdx_rx_fअगरo_माप_प्रकारo_packets(पूर्णांक rx_size)
अणु
	वापस (FIFO_SIZE * (1 << rx_size)) / माप(काष्ठा rxf_desc);
पूर्ण

/* Convert TX fअगरo size to number of pending packets */
अटल अंतरभूत पूर्णांक bdx_tx_fअगरo_माप_प्रकारo_packets(पूर्णांक tx_size)
अणु
	वापस (FIFO_SIZE * (1 << tx_size)) / BDX_TXF_DESC_SZ;
पूर्ण

/*
 * bdx_get_ringparam - report ring sizes
 * @netdev
 * @ring
 */
अटल व्योम
bdx_get_ringparam(काष्ठा net_device *netdev, काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(netdev);

	/*max_pending - the maximum-sized FIFO we allow */
	ring->rx_max_pending = bdx_rx_fअगरo_माप_प्रकारo_packets(3);
	ring->tx_max_pending = bdx_tx_fअगरo_माप_प्रकारo_packets(3);
	ring->rx_pending = bdx_rx_fअगरo_माप_प्रकारo_packets(priv->rxf_size);
	ring->tx_pending = bdx_tx_fअगरo_माप_प्रकारo_packets(priv->txd_size);
पूर्ण

/*
 * bdx_set_ringparam - set ring sizes
 * @netdev
 * @ring
 */
अटल पूर्णांक
bdx_set_ringparam(काष्ठा net_device *netdev, काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(netdev);
	पूर्णांक rx_size = 0;
	पूर्णांक tx_size = 0;

	क्रम (; rx_size < 4; rx_size++) अणु
		अगर (bdx_rx_fअगरo_माप_प्रकारo_packets(rx_size) >= ring->rx_pending)
			अवरोध;
	पूर्ण
	अगर (rx_size == 4)
		rx_size = 3;

	क्रम (; tx_size < 4; tx_size++) अणु
		अगर (bdx_tx_fअगरo_माप_प्रकारo_packets(tx_size) >= ring->tx_pending)
			अवरोध;
	पूर्ण
	अगर (tx_size == 4)
		tx_size = 3;

	/*Is there anything to करो? */
	अगर ((rx_size == priv->rxf_size) &&
	    (tx_size == priv->txd_size))
		वापस 0;

	priv->rxf_size = rx_size;
	अगर (rx_size > 1)
		priv->rxd_size = rx_size - 1;
	अन्यथा
		priv->rxd_size = rx_size;

	priv->txf_size = priv->txd_size = tx_size;

	अगर (netअगर_running(netdev)) अणु
		bdx_बंद(netdev);
		bdx_खोलो(netdev);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * bdx_get_strings - वापस a set of strings that describe the requested objects
 * @netdev
 * @data
 */
अटल व्योम bdx_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, *bdx_stat_names, माप(bdx_stat_names));
		अवरोध;
	पूर्ण
पूर्ण

/*
 * bdx_get_sset_count - वापस number of statistics or tests
 * @netdev
 */
अटल पूर्णांक bdx_get_sset_count(काष्ठा net_device *netdev, पूर्णांक stringset)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(netdev);

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		BDX_ASSERT(ARRAY_SIZE(bdx_stat_names)
			   != माप(काष्ठा bdx_stats) / माप(u64));
		वापस (priv->stats_flag) ? ARRAY_SIZE(bdx_stat_names)	: 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * bdx_get_ethtool_stats - वापस device's hardware L2 statistics
 * @netdev
 * @stats
 * @data
 */
अटल व्योम bdx_get_ethtool_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा bdx_priv *priv = netdev_priv(netdev);

	अगर (priv->stats_flag) अणु

		/* Update stats from HW */
		bdx_update_stats(priv);

		/* Copy data to user buffer */
		स_नकल(data, &priv->hw_stats, माप(priv->hw_stats));
	पूर्ण
पूर्ण

/*
 * bdx_set_ethtool_ops - ethtool पूर्णांकerface implementation
 * @netdev
 */
अटल व्योम bdx_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	अटल स्थिर काष्ठा ethtool_ops bdx_ethtool_ops = अणु
		.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
					     ETHTOOL_COALESCE_MAX_FRAMES,
		.get_drvinfo = bdx_get_drvinfo,
		.get_link = ethtool_op_get_link,
		.get_coalesce = bdx_get_coalesce,
		.set_coalesce = bdx_set_coalesce,
		.get_ringparam = bdx_get_ringparam,
		.set_ringparam = bdx_set_ringparam,
		.get_strings = bdx_get_strings,
		.get_sset_count = bdx_get_sset_count,
		.get_ethtool_stats = bdx_get_ethtool_stats,
		.get_link_ksettings = bdx_get_link_ksettings,
	पूर्ण;

	netdev->ethtool_ops = &bdx_ethtool_ops;
पूर्ण

/**
 * bdx_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * bdx_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम bdx_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_nic *nic = pci_get_drvdata(pdev);
	काष्ठा net_device *ndev;
	पूर्णांक port;

	क्रम (port = 0; port < nic->port_num; port++) अणु
		ndev = nic->priv[port]->ndev;
		unरेजिस्टर_netdev(ndev);
		मुक्त_netdev(ndev);
	पूर्ण

	/*bdx_hw_reset_direct(nic->regs); */
#अगर_घोषित BDX_MSI
	अगर (nic->irq_type == IRQ_MSI)
		pci_disable_msi(pdev);
#पूर्ण_अगर

	iounmap(nic->regs);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	vमुक्त(nic);

	RET();
पूर्ण

अटल काष्ठा pci_driver bdx_pci_driver = अणु
	.name = BDX_DRV_NAME,
	.id_table = bdx_pci_tbl,
	.probe = bdx_probe,
	.हटाओ = bdx_हटाओ,
पूर्ण;

/*
 * prपूर्णांक_driver_id - prपूर्णांक parameters of the driver build
 */
अटल व्योम __init prपूर्णांक_driver_id(व्योम)
अणु
	pr_info("%s, %s\n", BDX_DRV_DESC, BDX_DRV_VERSION);
	pr_info("Options: hw_csum %s\n", BDX_MSI_STRING);
पूर्ण

अटल पूर्णांक __init bdx_module_init(व्योम)
अणु
	ENTER;
	init_txd_sizes();
	prपूर्णांक_driver_id();
	RET(pci_रेजिस्टर_driver(&bdx_pci_driver));
पूर्ण

module_init(bdx_module_init);

अटल व्योम __निकास bdx_module_निकास(व्योम)
अणु
	ENTER;
	pci_unरेजिस्टर_driver(&bdx_pci_driver);
	RET();
पूर्ण

module_निकास(bdx_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(BDX_DRV_DESC);
MODULE_FIRMWARE("tehuti/bdx.bin");
