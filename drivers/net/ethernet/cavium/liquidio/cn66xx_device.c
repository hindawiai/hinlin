<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_main.h"
#समावेश "cn66xx_regs.h"
#समावेश "cn66xx_device.h"

पूर्णांक lio_cn6xxx_soft_reset(काष्ठा octeon_device *oct)
अणु
	octeon_ग_लिखो_csr64(oct, CN6XXX_WIN_WR_MASK_REG, 0xFF);

	dev_dbg(&oct->pci_dev->dev, "BIST enabled for soft reset\n");

	lio_pci_ग_लिखोq(oct, 1, CN6XXX_CIU_SOFT_BIST);
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_SCRATCH1, 0x1234ULL);

	lio_pci_पढ़ोq(oct, CN6XXX_CIU_SOFT_RST);
	lio_pci_ग_लिखोq(oct, 1, CN6XXX_CIU_SOFT_RST);

	/* Wait क्रम 10ms as Octeon resets. */
	mdelay(100);

	अगर (octeon_पढ़ो_csr64(oct, CN6XXX_SLI_SCRATCH1)) अणु
		dev_err(&oct->pci_dev->dev, "Soft reset failed\n");
		वापस 1;
	पूर्ण

	dev_dbg(&oct->pci_dev->dev, "Reset completed\n");
	octeon_ग_लिखो_csr64(oct, CN6XXX_WIN_WR_MASK_REG, 0xFF);

	वापस 0;
पूर्ण

व्योम lio_cn6xxx_enable_error_reporting(काष्ठा octeon_device *oct)
अणु
	u32 val;

	pci_पढ़ो_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, &val);
	अगर (val & 0x000c0000) अणु
		dev_err(&oct->pci_dev->dev, "PCI-E Link error detected: 0x%08x\n",
			val & 0x000c0000);
	पूर्ण

	val |= 0xf;          /* Enable Link error reporting */

	dev_dbg(&oct->pci_dev->dev, "Enabling PCI-E error reporting..\n");
	pci_ग_लिखो_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, val);
पूर्ण

व्योम lio_cn6xxx_setup_pcie_mps(काष्ठा octeon_device *oct,
			       क्रमागत octeon_pcie_mps mps)
अणु
	u32 val;
	u64 r64;

	/* Read config रेजिस्टर क्रम MPS */
	pci_पढ़ो_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, &val);

	अगर (mps == PCIE_MPS_DEFAULT) अणु
		mps = ((val & (0x7 << 5)) >> 5);
	पूर्ण अन्यथा अणु
		val &= ~(0x7 << 5);  /* Turn off any MPS bits */
		val |= (mps << 5);   /* Set MPS */
		pci_ग_लिखो_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, val);
	पूर्ण

	/* Set MPS in DPI_SLI_PRT0_CFG to the same value. */
	r64 = lio_pci_पढ़ोq(oct, CN6XXX_DPI_SLI_PRTX_CFG(oct->pcie_port));
	r64 |= (mps << 4);
	lio_pci_ग_लिखोq(oct, r64, CN6XXX_DPI_SLI_PRTX_CFG(oct->pcie_port));
पूर्ण

व्योम lio_cn6xxx_setup_pcie_mrrs(काष्ठा octeon_device *oct,
				क्रमागत octeon_pcie_mrrs mrrs)
अणु
	u32 val;
	u64 r64;

	/* Read config रेजिस्टर क्रम MRRS */
	pci_पढ़ो_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, &val);

	अगर (mrrs == PCIE_MRRS_DEFAULT) अणु
		mrrs = ((val & (0x7 << 12)) >> 12);
	पूर्ण अन्यथा अणु
		val &= ~(0x7 << 12); /* Turn off any MRRS bits */
		val |= (mrrs << 12); /* Set MRRS */
		pci_ग_लिखो_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, val);
	पूर्ण

	/* Set MRRS in SLI_S2M_PORT0_CTL to the same value. */
	r64 = octeon_पढ़ो_csr64(oct, CN6XXX_SLI_S2M_PORTX_CTL(oct->pcie_port));
	r64 |= mrrs;
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_S2M_PORTX_CTL(oct->pcie_port), r64);

	/* Set MRRS in DPI_SLI_PRT0_CFG to the same value. */
	r64 = lio_pci_पढ़ोq(oct, CN6XXX_DPI_SLI_PRTX_CFG(oct->pcie_port));
	r64 |= mrrs;
	lio_pci_ग_लिखोq(oct, r64, CN6XXX_DPI_SLI_PRTX_CFG(oct->pcie_port));
पूर्ण

u32 lio_cn6xxx_coprocessor_घड़ी(काष्ठा octeon_device *oct)
अणु
	/* Bits 29:24 of MIO_RST_BOOT holds the ref. घड़ी multiplier
	 * क्रम SLI.
	 */
	वापस ((lio_pci_पढ़ोq(oct, CN6XXX_MIO_RST_BOOT) >> 24) & 0x3f) * 50;
पूर्ण

u32 lio_cn6xxx_get_oq_ticks(काष्ठा octeon_device *oct,
			    u32 समय_पूर्णांकr_in_us)
अणु
	/* This gives the SLI घड़ी per microsec */
	u32 oqticks_per_us = lio_cn6xxx_coprocessor_घड़ी(oct);

	/* core घड़ी per us / oq ticks will be fractional. TO aव्योम that
	 * we use the method below.
	 */

	/* This gives the घड़ी cycles per millisecond */
	oqticks_per_us *= 1000;

	/* This gives the oq ticks (1024 core घड़ी cycles) per millisecond */
	oqticks_per_us /= 1024;

	/* समय_पूर्णांकr is in microseconds. The next 2 steps gives the oq ticks
	 * corressponding to समय_पूर्णांकr.
	 */
	oqticks_per_us *= समय_पूर्णांकr_in_us;
	oqticks_per_us /= 1000;

	वापस oqticks_per_us;
पूर्ण

व्योम lio_cn6xxx_setup_global_input_regs(काष्ठा octeon_device *oct)
अणु
	/* Select Round-Robin Arb, ES, RO, NS क्रम Input Queues */
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_INPUT_CONTROL,
			 CN6XXX_INPUT_CTL_MASK);

	/* Inकाष्ठाion Read Size - Max 4 inकाष्ठाions per PCIE Read */
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_PKT_INSTR_RD_SIZE,
			   0xFFFFFFFFFFFFFFFFULL);

	/* Select PCIE Port क्रम all Input rings. */
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_IN_PCIE_PORT,
			   (oct->pcie_port * 0x5555555555555555ULL));
पूर्ण

अटल व्योम lio_cn66xx_setup_pkt_ctl_regs(काष्ठा octeon_device *oct)
अणु
	u64 pktctl;

	काष्ठा octeon_cn6xxx *cn6xxx = (काष्ठा octeon_cn6xxx *)oct->chip;

	pktctl = octeon_पढ़ो_csr64(oct, CN6XXX_SLI_PKT_CTL);

	/* 66XX SPECIFIC */
	अगर (CFG_GET_OQ_MAX_Q(cn6xxx->conf) <= 4)
		/* Disable RING_EN अगर only upto 4 rings are used. */
		pktctl &= ~(1 << 4);
	अन्यथा
		pktctl |= (1 << 4);

	अगर (CFG_GET_IS_SLI_BP_ON(cn6xxx->conf))
		pktctl |= 0xF;
	अन्यथा
		/* Disable per-port backpressure. */
		pktctl &= ~0xF;
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_PKT_CTL, pktctl);
पूर्ण

व्योम lio_cn6xxx_setup_global_output_regs(काष्ठा octeon_device *oct)
अणु
	u32 समय_प्रकारhreshold;
	काष्ठा octeon_cn6xxx *cn6xxx = (काष्ठा octeon_cn6xxx *)oct->chip;

	/* / Select PCI-E Port क्रम all Output queues */
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_PKT_PCIE_PORT64,
			   (oct->pcie_port * 0x5555555555555555ULL));

	अगर (CFG_GET_IS_SLI_BP_ON(cn6xxx->conf)) अणु
		octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_OQ_WMARK, 32);
	पूर्ण अन्यथा अणु
		/* / Set Output queue watermark to 0 to disable backpressure */
		octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_OQ_WMARK, 0);
	पूर्ण

	/* / Select Packet count instead of bytes क्रम SLI_PKTi_CNTS[CNT] */
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_OUT_BMODE, 0);

	/* Select ES, RO, NS setting from रेजिस्टर क्रम Output Queue Packet
	 * Address
	 */
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_DPADDR, 0xFFFFFFFF);

	/* No Relaxed Ordering, No Snoop, 64-bit swap क्रम Output
	 * Queue ScatterList
	 */
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_SLIST_ROR, 0);
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_SLIST_NS, 0);

	/* / ENDIAN_SPECIFIC CHANGES - 0 works क्रम LE. */
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_PKT_SLIST_ES64,
			   0x5555555555555555ULL);
#अन्यथा
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_PKT_SLIST_ES64, 0ULL);
#पूर्ण_अगर

	/* / No Relaxed Ordering, No Snoop, 64-bit swap क्रम Output Queue Data */
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_DATA_OUT_ROR, 0);
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_DATA_OUT_NS, 0);
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_PKT_DATA_OUT_ES64,
			   0x5555555555555555ULL);

	/* / Set up पूर्णांकerrupt packet and समय threshold */
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_OQ_INT_LEVEL_PKTS,
			 (u32)CFG_GET_OQ_INTR_PKT(cn6xxx->conf));
	समय_प्रकारhreshold =
		lio_cn6xxx_get_oq_ticks(oct, (u32)
					CFG_GET_OQ_INTR_TIME(cn6xxx->conf));

	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_OQ_INT_LEVEL_TIME, समय_प्रकारhreshold);
पूर्ण

अटल पूर्णांक lio_cn6xxx_setup_device_regs(काष्ठा octeon_device *oct)
अणु
	lio_cn6xxx_setup_pcie_mps(oct, PCIE_MPS_DEFAULT);
	lio_cn6xxx_setup_pcie_mrrs(oct, PCIE_MRRS_512B);
	lio_cn6xxx_enable_error_reporting(oct);

	lio_cn6xxx_setup_global_input_regs(oct);
	lio_cn66xx_setup_pkt_ctl_regs(oct);
	lio_cn6xxx_setup_global_output_regs(oct);

	/* Default error समयout value should be 0x200000 to aव्योम host hang
	 * when पढ़ोs invalid रेजिस्टर
	 */
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_WINDOW_CTL, 0x200000ULL);
	वापस 0;
पूर्ण

व्योम lio_cn6xxx_setup_iq_regs(काष्ठा octeon_device *oct, u32 iq_no)
अणु
	काष्ठा octeon_instr_queue *iq = oct->instr_queue[iq_no];

	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_IQ_PKT_INSTR_HDR64(iq_no), 0);

	/* Write the start of the input queue's ring and its size  */
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_IQ_BASE_ADDR64(iq_no),
			   iq->base_addr_dma);
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_IQ_SIZE(iq_no), iq->max_count);

	/* Remember the करोorbell & inकाष्ठाion count रेजिस्टर addr क्रम this
	 * queue
	 */
	iq->करोorbell_reg = oct->mmio[0].hw_addr + CN6XXX_SLI_IQ_DOORBELL(iq_no);
	iq->inst_cnt_reg = oct->mmio[0].hw_addr
			   + CN6XXX_SLI_IQ_INSTR_COUNT(iq_no);
	dev_dbg(&oct->pci_dev->dev, "InstQ[%d]:dbell reg @ 0x%p instcnt_reg @ 0x%p\n",
		iq_no, iq->करोorbell_reg, iq->inst_cnt_reg);

	/* Store the current inकाष्ठाion counter
	 * (used in flush_iq calculation)
	 */
	iq->reset_instr_cnt = पढ़ोl(iq->inst_cnt_reg);
पूर्ण

अटल व्योम lio_cn66xx_setup_iq_regs(काष्ठा octeon_device *oct, u32 iq_no)
अणु
	lio_cn6xxx_setup_iq_regs(oct, iq_no);

	/* Backpressure क्रम this queue - WMARK set to all F's. This effectively
	 * disables the backpressure mechanism.
	 */
	octeon_ग_लिखो_csr64(oct, CN66XX_SLI_IQ_BP64(iq_no),
			   (0xFFFFFFFFULL << 32));
पूर्ण

व्योम lio_cn6xxx_setup_oq_regs(काष्ठा octeon_device *oct, u32 oq_no)
अणु
	u32 पूर्णांकr;
	काष्ठा octeon_droq *droq = oct->droq[oq_no];

	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_OQ_BASE_ADDR64(oq_no),
			   droq->desc_ring_dma);
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_OQ_SIZE(oq_no), droq->max_count);

	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_OQ_BUFF_INFO_SIZE(oq_no),
			 droq->buffer_size);

	/* Get the mapped address of the pkt_sent and pkts_credit regs */
	droq->pkts_sent_reg =
		oct->mmio[0].hw_addr + CN6XXX_SLI_OQ_PKTS_SENT(oq_no);
	droq->pkts_credit_reg =
		oct->mmio[0].hw_addr + CN6XXX_SLI_OQ_PKTS_CREDIT(oq_no);

	/* Enable this output queue to generate Packet Timer Interrupt */
	पूर्णांकr = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_TIME_INT_ENB);
	पूर्णांकr |= (1 << oq_no);
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_TIME_INT_ENB, पूर्णांकr);

	/* Enable this output queue to generate Packet Timer Interrupt */
	पूर्णांकr = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_CNT_INT_ENB);
	पूर्णांकr |= (1 << oq_no);
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_CNT_INT_ENB, पूर्णांकr);
पूर्ण

पूर्णांक lio_cn6xxx_enable_io_queues(काष्ठा octeon_device *oct)
अणु
	u32 mask;

	mask = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_INSTR_SIZE);
	mask |= oct->io_qmask.iq64B;
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_INSTR_SIZE, mask);

	mask = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_INSTR_ENB);
	mask |= oct->io_qmask.iq;
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_INSTR_ENB, mask);

	mask = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_OUT_ENB);
	mask |= oct->io_qmask.oq;
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_OUT_ENB, mask);

	वापस 0;
पूर्ण

व्योम lio_cn6xxx_disable_io_queues(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i;
	u32 mask, loop = HZ;
	u32 d32;

	/* Reset the Enable bits क्रम Input Queues. */
	mask = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_INSTR_ENB);
	mask ^= oct->io_qmask.iq;
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_INSTR_ENB, mask);

	/* Wait until hardware indicates that the queues are out of reset. */
	mask = (u32)oct->io_qmask.iq;
	d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PORT_IN_RST_IQ);
	जबतक (((d32 & mask) != mask) && loop--) अणु
		d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PORT_IN_RST_IQ);
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	/* Reset the करोorbell रेजिस्टर क्रम each Input queue. */
	क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) अणु
		अगर (!(oct->io_qmask.iq & BIT_ULL(i)))
			जारी;
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_IQ_DOORBELL(i), 0xFFFFFFFF);
		d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_IQ_DOORBELL(i));
	पूर्ण

	/* Reset the Enable bits क्रम Output Queues. */
	mask = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_OUT_ENB);
	mask ^= oct->io_qmask.oq;
	octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_OUT_ENB, mask);

	/* Wait until hardware indicates that the queues are out of reset. */
	loop = HZ;
	mask = (u32)oct->io_qmask.oq;
	d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PORT_IN_RST_OQ);
	जबतक (((d32 & mask) != mask) && loop--) अणु
		d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PORT_IN_RST_OQ);
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	;

	/* Reset the करोorbell रेजिस्टर क्रम each Output queue. */
	क्रम (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) अणु
		अगर (!(oct->io_qmask.oq & BIT_ULL(i)))
			जारी;
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_OQ_PKTS_CREDIT(i), 0xFFFFFFFF);
		d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_OQ_PKTS_CREDIT(i));

		d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_OQ_PKTS_SENT(i));
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_OQ_PKTS_SENT(i), d32);
	पूर्ण

	d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_CNT_INT);
	अगर (d32)
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_CNT_INT, d32);

	d32 = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_TIME_INT);
	अगर (d32)
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_TIME_INT, d32);
पूर्ण

व्योम
lio_cn6xxx_bar1_idx_setup(काष्ठा octeon_device *oct,
			  u64 core_addr,
			  u32 idx,
			  पूर्णांक valid)
अणु
	u64 bar1;

	अगर (valid == 0) अणु
		bar1 = lio_pci_पढ़ोq(oct, CN6XXX_BAR1_REG(idx, oct->pcie_port));
		lio_pci_ग_लिखोq(oct, (bar1 & 0xFFFFFFFEULL),
			       CN6XXX_BAR1_REG(idx, oct->pcie_port));
		bar1 = lio_pci_पढ़ोq(oct, CN6XXX_BAR1_REG(idx, oct->pcie_port));
		वापस;
	पूर्ण

	/* Bits 17:4 of the PCI_BAR1_INDEXx stores bits 35:22 of
	 * the Core Addr
	 */
	lio_pci_ग_लिखोq(oct, (((core_addr >> 22) << 4) | PCI_BAR1_MASK),
		       CN6XXX_BAR1_REG(idx, oct->pcie_port));

	bar1 = lio_pci_पढ़ोq(oct, CN6XXX_BAR1_REG(idx, oct->pcie_port));
पूर्ण

व्योम lio_cn6xxx_bar1_idx_ग_लिखो(काष्ठा octeon_device *oct,
			       u32 idx,
			       u32 mask)
अणु
	lio_pci_ग_लिखोq(oct, mask, CN6XXX_BAR1_REG(idx, oct->pcie_port));
पूर्ण

u32 lio_cn6xxx_bar1_idx_पढ़ो(काष्ठा octeon_device *oct, u32 idx)
अणु
	वापस (u32)lio_pci_पढ़ोq(oct, CN6XXX_BAR1_REG(idx, oct->pcie_port));
पूर्ण

u32
lio_cn6xxx_update_पढ़ो_index(काष्ठा octeon_instr_queue *iq)
अणु
	u32 new_idx = पढ़ोl(iq->inst_cnt_reg);

	/* The new instr cnt reg is a 32-bit counter that can roll over. We have
	 * noted the counter's initial value at init समय पूर्णांकo
	 * reset_instr_cnt
	 */
	अगर (iq->reset_instr_cnt < new_idx)
		new_idx -= iq->reset_instr_cnt;
	अन्यथा
		new_idx += (0xffffffff - iq->reset_instr_cnt) + 1;

	/* Modulo of the new index with the IQ size will give us
	 * the new index.
	 */
	new_idx %= iq->max_count;

	वापस new_idx;
पूर्ण

व्योम lio_cn6xxx_enable_पूर्णांकerrupt(काष्ठा octeon_device *oct,
				 u8 unused __attribute__((unused)))
अणु
	काष्ठा octeon_cn6xxx *cn6xxx = (काष्ठा octeon_cn6xxx *)oct->chip;
	u64 mask = cn6xxx->पूर्णांकr_mask64 | CN6XXX_INTR_DMA0_FORCE;

	/* Enable Interrupt */
	ग_लिखोq(mask, cn6xxx->पूर्णांकr_enb_reg64);
पूर्ण

व्योम lio_cn6xxx_disable_पूर्णांकerrupt(काष्ठा octeon_device *oct,
				  u8 unused __attribute__((unused)))
अणु
	काष्ठा octeon_cn6xxx *cn6xxx = (काष्ठा octeon_cn6xxx *)oct->chip;

	/* Disable Interrupts */
	ग_लिखोq(0, cn6xxx->पूर्णांकr_enb_reg64);
पूर्ण

अटल व्योम lio_cn6xxx_get_pcie_qlmport(काष्ठा octeon_device *oct)
अणु
	/* CN63xx Pass2 and newer parts implements the SLI_MAC_NUMBER रेजिस्टर
	 * to determine the PCIE port #
	 */
	oct->pcie_port = octeon_पढ़ो_csr(oct, CN6XXX_SLI_MAC_NUMBER) & 0xff;

	dev_dbg(&oct->pci_dev->dev, "Using PCIE Port %d\n", oct->pcie_port);
पूर्ण

अटल व्योम
lio_cn6xxx_process_pcie_error_पूर्णांकr(काष्ठा octeon_device *oct, u64 पूर्णांकr64)
अणु
	dev_err(&oct->pci_dev->dev, "Error Intr: 0x%016llx\n",
		CVM_CAST64(पूर्णांकr64));
पूर्ण

अटल पूर्णांक lio_cn6xxx_process_droq_पूर्णांकr_regs(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_droq *droq;
	पूर्णांक oq_no;
	u32 pkt_count, droq_समय_mask, droq_mask, droq_पूर्णांक_enb;
	u32 droq_cnt_enb, droq_cnt_mask;

	droq_cnt_enb = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_CNT_INT_ENB);
	droq_cnt_mask = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_CNT_INT);
	droq_mask = droq_cnt_mask & droq_cnt_enb;

	droq_समय_mask = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_TIME_INT);
	droq_पूर्णांक_enb = octeon_पढ़ो_csr(oct, CN6XXX_SLI_PKT_TIME_INT_ENB);
	droq_mask |= (droq_समय_mask & droq_पूर्णांक_enb);

	droq_mask &= oct->io_qmask.oq;

	oct->droq_पूर्णांकr = 0;

	क्रम (oq_no = 0; oq_no < MAX_OCTEON_OUTPUT_QUEUES(oct); oq_no++) अणु
		अगर (!(droq_mask & BIT_ULL(oq_no)))
			जारी;

		droq = oct->droq[oq_no];
		pkt_count = octeon_droq_check_hw_क्रम_pkts(droq);
		अगर (pkt_count) अणु
			oct->droq_पूर्णांकr |= BIT_ULL(oq_no);
			अगर (droq->ops.poll_mode) अणु
				u32 value;
				u32 reg;

				काष्ठा octeon_cn6xxx *cn6xxx =
					(काष्ठा octeon_cn6xxx *)oct->chip;

				/* disable पूर्णांकerrupts क्रम this droq */
				spin_lock
					(&cn6xxx->lock_क्रम_droq_पूर्णांक_enb_reg);
				reg = CN6XXX_SLI_PKT_TIME_INT_ENB;
				value = octeon_पढ़ो_csr(oct, reg);
				value &= ~(1 << oq_no);
				octeon_ग_लिखो_csr(oct, reg, value);
				reg = CN6XXX_SLI_PKT_CNT_INT_ENB;
				value = octeon_पढ़ो_csr(oct, reg);
				value &= ~(1 << oq_no);
				octeon_ग_लिखो_csr(oct, reg, value);

				spin_unlock(&cn6xxx->lock_क्रम_droq_पूर्णांक_enb_reg);
			पूर्ण
		पूर्ण
	पूर्ण

	droq_समय_mask &= oct->io_qmask.oq;
	droq_cnt_mask &= oct->io_qmask.oq;

	/* Reset the PKT_CNT/TIME_INT रेजिस्टरs. */
	अगर (droq_समय_mask)
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_TIME_INT, droq_समय_mask);

	अगर (droq_cnt_mask)      /* reset PKT_CNT रेजिस्टर:66xx */
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_PKT_CNT_INT, droq_cnt_mask);

	वापस 0;
पूर्ण

irqवापस_t lio_cn6xxx_process_पूर्णांकerrupt_regs(व्योम *dev)
अणु
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)dev;
	काष्ठा octeon_cn6xxx *cn6xxx = (काष्ठा octeon_cn6xxx *)oct->chip;
	u64 पूर्णांकr64;

	पूर्णांकr64 = पढ़ोq(cn6xxx->पूर्णांकr_sum_reg64);

	/* If our device has पूर्णांकerrupted, then proceed.
	 * Also check क्रम all f's अगर पूर्णांकerrupt was triggered on an error
	 * and the PCI पढ़ो fails.
	 */
	अगर (!पूर्णांकr64 || (पूर्णांकr64 == 0xFFFFFFFFFFFFFFFFULL))
		वापस IRQ_NONE;

	oct->पूर्णांक_status = 0;

	अगर (पूर्णांकr64 & CN6XXX_INTR_ERR)
		lio_cn6xxx_process_pcie_error_पूर्णांकr(oct, पूर्णांकr64);

	अगर (पूर्णांकr64 & CN6XXX_INTR_PKT_DATA) अणु
		lio_cn6xxx_process_droq_पूर्णांकr_regs(oct);
		oct->पूर्णांक_status |= OCT_DEV_INTR_PKT_DATA;
	पूर्ण

	अगर (पूर्णांकr64 & CN6XXX_INTR_DMA0_FORCE)
		oct->पूर्णांक_status |= OCT_DEV_INTR_DMA0_FORCE;

	अगर (पूर्णांकr64 & CN6XXX_INTR_DMA1_FORCE)
		oct->पूर्णांक_status |= OCT_DEV_INTR_DMA1_FORCE;

	/* Clear the current पूर्णांकerrupts */
	ग_लिखोq(पूर्णांकr64, cn6xxx->पूर्णांकr_sum_reg64);

	वापस IRQ_HANDLED;
पूर्ण

व्योम lio_cn6xxx_setup_reg_address(काष्ठा octeon_device *oct,
				  व्योम *chip,
				  काष्ठा octeon_reg_list *reg_list)
अणु
	u8 __iomem *bar0_pciaddr = oct->mmio[0].hw_addr;
	काष्ठा octeon_cn6xxx *cn6xxx = (काष्ठा octeon_cn6xxx *)chip;

	reg_list->pci_win_wr_addr_hi =
		(u32 __iomem *)(bar0_pciaddr + CN6XXX_WIN_WR_ADDR_HI);
	reg_list->pci_win_wr_addr_lo =
		(u32 __iomem *)(bar0_pciaddr + CN6XXX_WIN_WR_ADDR_LO);
	reg_list->pci_win_wr_addr =
		(u64 __iomem *)(bar0_pciaddr + CN6XXX_WIN_WR_ADDR64);

	reg_list->pci_win_rd_addr_hi =
		(u32 __iomem *)(bar0_pciaddr + CN6XXX_WIN_RD_ADDR_HI);
	reg_list->pci_win_rd_addr_lo =
		(u32 __iomem *)(bar0_pciaddr + CN6XXX_WIN_RD_ADDR_LO);
	reg_list->pci_win_rd_addr =
		(u64 __iomem *)(bar0_pciaddr + CN6XXX_WIN_RD_ADDR64);

	reg_list->pci_win_wr_data_hi =
		(u32 __iomem *)(bar0_pciaddr + CN6XXX_WIN_WR_DATA_HI);
	reg_list->pci_win_wr_data_lo =
		(u32 __iomem *)(bar0_pciaddr + CN6XXX_WIN_WR_DATA_LO);
	reg_list->pci_win_wr_data =
		(u64 __iomem *)(bar0_pciaddr + CN6XXX_WIN_WR_DATA64);

	reg_list->pci_win_rd_data_hi =
		(u32 __iomem *)(bar0_pciaddr + CN6XXX_WIN_RD_DATA_HI);
	reg_list->pci_win_rd_data_lo =
		(u32 __iomem *)(bar0_pciaddr + CN6XXX_WIN_RD_DATA_LO);
	reg_list->pci_win_rd_data =
		(u64 __iomem *)(bar0_pciaddr + CN6XXX_WIN_RD_DATA64);

	lio_cn6xxx_get_pcie_qlmport(oct);

	cn6xxx->पूर्णांकr_sum_reg64 = bar0_pciaddr + CN6XXX_SLI_INT_SUM64;
	cn6xxx->पूर्णांकr_mask64 = CN6XXX_INTR_MASK;
	cn6xxx->पूर्णांकr_enb_reg64 =
		bar0_pciaddr + CN6XXX_SLI_INT_ENB64(oct->pcie_port);
पूर्ण

पूर्णांक lio_setup_cn66xx_octeon_device(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_cn6xxx *cn6xxx = (काष्ठा octeon_cn6xxx *)oct->chip;

	अगर (octeon_map_pci_barx(oct, 0, 0))
		वापस 1;

	अगर (octeon_map_pci_barx(oct, 1, MAX_BAR1_IOREMAP_SIZE)) अणु
		dev_err(&oct->pci_dev->dev, "%s CN66XX BAR1 map failed\n",
			__func__);
		octeon_unmap_pci_barx(oct, 0);
		वापस 1;
	पूर्ण

	spin_lock_init(&cn6xxx->lock_क्रम_droq_पूर्णांक_enb_reg);

	oct->fn_list.setup_iq_regs = lio_cn66xx_setup_iq_regs;
	oct->fn_list.setup_oq_regs = lio_cn6xxx_setup_oq_regs;

	oct->fn_list.soft_reset = lio_cn6xxx_soft_reset;
	oct->fn_list.setup_device_regs = lio_cn6xxx_setup_device_regs;
	oct->fn_list.update_iq_पढ़ो_idx = lio_cn6xxx_update_पढ़ो_index;

	oct->fn_list.bar1_idx_setup = lio_cn6xxx_bar1_idx_setup;
	oct->fn_list.bar1_idx_ग_लिखो = lio_cn6xxx_bar1_idx_ग_लिखो;
	oct->fn_list.bar1_idx_पढ़ो = lio_cn6xxx_bar1_idx_पढ़ो;

	oct->fn_list.process_पूर्णांकerrupt_regs = lio_cn6xxx_process_पूर्णांकerrupt_regs;
	oct->fn_list.enable_पूर्णांकerrupt = lio_cn6xxx_enable_पूर्णांकerrupt;
	oct->fn_list.disable_पूर्णांकerrupt = lio_cn6xxx_disable_पूर्णांकerrupt;

	oct->fn_list.enable_io_queues = lio_cn6xxx_enable_io_queues;
	oct->fn_list.disable_io_queues = lio_cn6xxx_disable_io_queues;

	lio_cn6xxx_setup_reg_address(oct, oct->chip, &oct->reg_list);

	cn6xxx->conf = (काष्ठा octeon_config *)
		       oct_get_config_info(oct, LIO_210SV);
	अगर (!cn6xxx->conf) अणु
		dev_err(&oct->pci_dev->dev, "%s No Config found for CN66XX\n",
			__func__);
		octeon_unmap_pci_barx(oct, 0);
		octeon_unmap_pci_barx(oct, 1);
		वापस 1;
	पूर्ण

	oct->coproc_घड़ी_rate = 1000000ULL * lio_cn6xxx_coprocessor_घड़ी(oct);

	वापस 0;
पूर्ण

पूर्णांक lio_validate_cn6xxx_config_info(काष्ठा octeon_device *oct,
				    काष्ठा octeon_config *conf6xxx)
अणु
	अगर (CFG_GET_IQ_MAX_Q(conf6xxx) > CN6XXX_MAX_INPUT_QUEUES) अणु
		dev_err(&oct->pci_dev->dev, "%s: Num IQ (%d) exceeds Max (%d)\n",
			__func__, CFG_GET_IQ_MAX_Q(conf6xxx),
			CN6XXX_MAX_INPUT_QUEUES);
		वापस 1;
	पूर्ण

	अगर (CFG_GET_OQ_MAX_Q(conf6xxx) > CN6XXX_MAX_OUTPUT_QUEUES) अणु
		dev_err(&oct->pci_dev->dev, "%s: Num OQ (%d) exceeds Max (%d)\n",
			__func__, CFG_GET_OQ_MAX_Q(conf6xxx),
			CN6XXX_MAX_OUTPUT_QUEUES);
		वापस 1;
	पूर्ण

	अगर (CFG_GET_IQ_INSTR_TYPE(conf6xxx) != OCTEON_32BYTE_INSTR &&
	    CFG_GET_IQ_INSTR_TYPE(conf6xxx) != OCTEON_64BYTE_INSTR) अणु
		dev_err(&oct->pci_dev->dev, "%s: Invalid instr type for IQ\n",
			__func__);
		वापस 1;
	पूर्ण
	अगर (!CFG_GET_OQ_REFILL_THRESHOLD(conf6xxx)) अणु
		dev_err(&oct->pci_dev->dev, "%s: Invalid parameter for OQ\n",
			__func__);
		वापस 1;
	पूर्ण

	अगर (!(CFG_GET_OQ_INTR_TIME(conf6xxx))) अणु
		dev_err(&oct->pci_dev->dev, "%s: No Time Interrupt for OQ\n",
			__func__);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
