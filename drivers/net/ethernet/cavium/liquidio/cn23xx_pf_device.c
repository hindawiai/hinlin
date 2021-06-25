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
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/etherdevice.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "cn23xx_pf_device.h"
#समावेश "octeon_main.h"
#समावेश "octeon_mailbox.h"

#घोषणा RESET_NOTDONE 0
#घोषणा RESET_DONE 1

/* Change the value of SLI Packet Input Jabber Register to allow
 * VXLAN TSO packets which can be 64424 bytes, exceeding the
 * MAX_GSO_SIZE we supplied to the kernel
 */
#घोषणा CN23XX_INPUT_JABBER 64600

व्योम cn23xx_dump_pf_initialized_regs(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i = 0;
	u32 regval = 0;
	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;

	/*In cn23xx_soft_reset*/
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%llx\n",
		"CN23XX_WIN_WR_MASK_REG", CVM_CAST64(CN23XX_WIN_WR_MASK_REG),
		CVM_CAST64(octeon_पढ़ो_csr64(oct, CN23XX_WIN_WR_MASK_REG)));
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_SCRATCH1", CVM_CAST64(CN23XX_SLI_SCRATCH1),
		CVM_CAST64(octeon_पढ़ो_csr64(oct, CN23XX_SLI_SCRATCH1)));
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_RST_SOFT_RST", CN23XX_RST_SOFT_RST,
		lio_pci_पढ़ोq(oct, CN23XX_RST_SOFT_RST));

	/*In cn23xx_set_dpi_regs*/
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_DPI_DMA_CONTROL", CN23XX_DPI_DMA_CONTROL,
		lio_pci_पढ़ोq(oct, CN23XX_DPI_DMA_CONTROL));

	क्रम (i = 0; i < 6; i++) अणु
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_DPI_DMA_ENG_ENB", i,
			CN23XX_DPI_DMA_ENG_ENB(i),
			lio_pci_पढ़ोq(oct, CN23XX_DPI_DMA_ENG_ENB(i)));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_DPI_DMA_ENG_BUF", i,
			CN23XX_DPI_DMA_ENG_BUF(i),
			lio_pci_पढ़ोq(oct, CN23XX_DPI_DMA_ENG_BUF(i)));
	पूर्ण

	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n", "CN23XX_DPI_CTL",
		CN23XX_DPI_CTL, lio_pci_पढ़ोq(oct, CN23XX_DPI_CTL));

	/*In cn23xx_setup_pcie_mps and cn23xx_setup_pcie_mrrs */
	pci_पढ़ो_config_dword(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTL, &regval);
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_CONFIG_PCIE_DEVCTL",
		CVM_CAST64(CN23XX_CONFIG_PCIE_DEVCTL), CVM_CAST64(regval));

	dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
		"CN23XX_DPI_SLI_PRTX_CFG", oct->pcie_port,
		CN23XX_DPI_SLI_PRTX_CFG(oct->pcie_port),
		lio_pci_पढ़ोq(oct, CN23XX_DPI_SLI_PRTX_CFG(oct->pcie_port)));

	/*In cn23xx_specअगरic_regs_setup */
	dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
		"CN23XX_SLI_S2M_PORTX_CTL", oct->pcie_port,
		CVM_CAST64(CN23XX_SLI_S2M_PORTX_CTL(oct->pcie_port)),
		CVM_CAST64(octeon_पढ़ो_csr64(
			oct, CN23XX_SLI_S2M_PORTX_CTL(oct->pcie_port))));

	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_RING_RST", CVM_CAST64(CN23XX_SLI_PKT_IOQ_RING_RST),
		(u64)octeon_पढ़ो_csr64(oct, CN23XX_SLI_PKT_IOQ_RING_RST));

	/*In cn23xx_setup_global_mac_regs*/
	क्रम (i = 0; i < CN23XX_MAX_MACS; i++) अणु
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_PKT_MAC_RINFO64", i,
			CVM_CAST64(CN23XX_SLI_PKT_MAC_RINFO64(i, oct->pf_num)),
			CVM_CAST64(octeon_पढ़ो_csr64
				(oct, CN23XX_SLI_PKT_MAC_RINFO64
					(i, oct->pf_num))));
	पूर्ण

	/*In cn23xx_setup_global_input_regs*/
	क्रम (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) अणु
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_PKT_CONTROL64", i,
			CVM_CAST64(CN23XX_SLI_IQ_PKT_CONTROL64(i)),
			CVM_CAST64(octeon_पढ़ो_csr64
				(oct, CN23XX_SLI_IQ_PKT_CONTROL64(i))));
	पूर्ण

	/*In cn23xx_setup_global_output_regs*/
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_OQ_WMARK", CVM_CAST64(CN23XX_SLI_OQ_WMARK),
		CVM_CAST64(octeon_पढ़ो_csr64(oct, CN23XX_SLI_OQ_WMARK)));

	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_PKT_CONTROL", i,
			CVM_CAST64(CN23XX_SLI_OQ_PKT_CONTROL(i)),
			CVM_CAST64(octeon_पढ़ो_csr(
				oct, CN23XX_SLI_OQ_PKT_CONTROL(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_PKT_INT_LEVELS", i,
			CVM_CAST64(CN23XX_SLI_OQ_PKT_INT_LEVELS(i)),
			CVM_CAST64(octeon_पढ़ो_csr64(
				oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(i))));
	पूर्ण

	/*In cn23xx_enable_पूर्णांकerrupt and cn23xx_disable_पूर्णांकerrupt*/
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"cn23xx->intr_enb_reg64",
		CVM_CAST64((दीर्घ)(cn23xx->पूर्णांकr_enb_reg64)),
		CVM_CAST64(पढ़ोq(cn23xx->पूर्णांकr_enb_reg64)));

	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"cn23xx->intr_sum_reg64",
		CVM_CAST64((दीर्घ)(cn23xx->पूर्णांकr_sum_reg64)),
		CVM_CAST64(पढ़ोq(cn23xx->पूर्णांकr_sum_reg64)));

	/*In cn23xx_setup_iq_regs*/
	क्रम (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) अणु
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_BASE_ADDR64", i,
			CVM_CAST64(CN23XX_SLI_IQ_BASE_ADDR64(i)),
			CVM_CAST64(octeon_पढ़ो_csr64(
				oct, CN23XX_SLI_IQ_BASE_ADDR64(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_SIZE", i,
			CVM_CAST64(CN23XX_SLI_IQ_SIZE(i)),
			CVM_CAST64(octeon_पढ़ो_csr
				(oct, CN23XX_SLI_IQ_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_DOORBELL", i,
			CVM_CAST64(CN23XX_SLI_IQ_DOORBELL(i)),
			CVM_CAST64(octeon_पढ़ो_csr64(
				oct, CN23XX_SLI_IQ_DOORBELL(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_INSTR_COUNT64", i,
			CVM_CAST64(CN23XX_SLI_IQ_INSTR_COUNT64(i)),
			CVM_CAST64(octeon_पढ़ो_csr64(
				oct, CN23XX_SLI_IQ_INSTR_COUNT64(i))));
	पूर्ण

	/*In cn23xx_setup_oq_regs*/
	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_BASE_ADDR64", i,
			CVM_CAST64(CN23XX_SLI_OQ_BASE_ADDR64(i)),
			CVM_CAST64(octeon_पढ़ो_csr64(
				oct, CN23XX_SLI_OQ_BASE_ADDR64(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_SIZE", i,
			CVM_CAST64(CN23XX_SLI_OQ_SIZE(i)),
			CVM_CAST64(octeon_पढ़ो_csr
				(oct, CN23XX_SLI_OQ_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_BUFF_INFO_SIZE", i,
			CVM_CAST64(CN23XX_SLI_OQ_BUFF_INFO_SIZE(i)),
			CVM_CAST64(octeon_पढ़ो_csr(
				oct, CN23XX_SLI_OQ_BUFF_INFO_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_PKTS_SENT", i,
			CVM_CAST64(CN23XX_SLI_OQ_PKTS_SENT(i)),
			CVM_CAST64(octeon_पढ़ो_csr64(
				oct, CN23XX_SLI_OQ_PKTS_SENT(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_PKTS_CREDIT", i,
			CVM_CAST64(CN23XX_SLI_OQ_PKTS_CREDIT(i)),
			CVM_CAST64(octeon_पढ़ो_csr64(
				oct, CN23XX_SLI_OQ_PKTS_CREDIT(i))));
	पूर्ण

	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_PKT_TIME_INT",
		CVM_CAST64(CN23XX_SLI_PKT_TIME_INT),
		CVM_CAST64(octeon_पढ़ो_csr64(oct, CN23XX_SLI_PKT_TIME_INT)));
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_PKT_CNT_INT",
		CVM_CAST64(CN23XX_SLI_PKT_CNT_INT),
		CVM_CAST64(octeon_पढ़ो_csr64(oct, CN23XX_SLI_PKT_CNT_INT)));
पूर्ण

अटल पूर्णांक cn23xx_pf_soft_reset(काष्ठा octeon_device *oct)
अणु
	octeon_ग_लिखो_csr64(oct, CN23XX_WIN_WR_MASK_REG, 0xFF);

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: BIST enabled for CN23XX soft reset\n",
		oct->octeon_id);

	octeon_ग_लिखो_csr64(oct, CN23XX_SLI_SCRATCH1, 0x1234ULL);

	/* Initiate chip-wide soft reset */
	lio_pci_पढ़ोq(oct, CN23XX_RST_SOFT_RST);
	lio_pci_ग_लिखोq(oct, 1, CN23XX_RST_SOFT_RST);

	/* Wait क्रम 100ms as Octeon resets. */
	mdelay(100);

	अगर (octeon_पढ़ो_csr64(oct, CN23XX_SLI_SCRATCH1)) अणु
		dev_err(&oct->pci_dev->dev, "OCTEON[%d]: Soft reset failed\n",
			oct->octeon_id);
		वापस 1;
	पूर्ण

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: Reset completed\n",
		oct->octeon_id);

	/* restore the  reset value*/
	octeon_ग_लिखो_csr64(oct, CN23XX_WIN_WR_MASK_REG, 0xFF);

	वापस 0;
पूर्ण

अटल व्योम cn23xx_enable_error_reporting(काष्ठा octeon_device *oct)
अणु
	u32 regval;
	u32 uncorrectable_err_mask, corrtable_err_status;

	pci_पढ़ो_config_dword(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTL, &regval);
	अगर (regval & CN23XX_CONFIG_PCIE_DEVCTL_MASK) अणु
		uncorrectable_err_mask = 0;
		corrtable_err_status = 0;
		pci_पढ़ो_config_dword(oct->pci_dev,
				      CN23XX_CONFIG_PCIE_UNCORRECT_ERR_MASK,
				      &uncorrectable_err_mask);
		pci_पढ़ो_config_dword(oct->pci_dev,
				      CN23XX_CONFIG_PCIE_CORRECT_ERR_STATUS,
				      &corrtable_err_status);
		dev_err(&oct->pci_dev->dev, "PCI-E Fatal error detected;\n"
				 "\tdev_ctl_status_reg = 0x%08x\n"
				 "\tuncorrectable_error_mask_reg = 0x%08x\n"
				 "\tcorrectable_error_status_reg = 0x%08x\n",
			    regval, uncorrectable_err_mask,
			    corrtable_err_status);
	पूर्ण

	regval |= 0xf; /* Enable Link error reporting */

	dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: Enabling PCI-E error reporting..\n",
		oct->octeon_id);
	pci_ग_लिखो_config_dword(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTL, regval);
पूर्ण

अटल u32 cn23xx_coprocessor_घड़ी(काष्ठा octeon_device *oct)
अणु
	/* Bits 29:24 of RST_BOOT[PNR_MUL] holds the ref.घड़ी MULTIPLIER
	 * क्रम SLI.
	 */

	/* TBD: get the info in Hand-shake */
	वापस (((lio_pci_पढ़ोq(oct, CN23XX_RST_BOOT) >> 24) & 0x3f) * 50);
पूर्ण

u32 cn23xx_pf_get_oq_ticks(काष्ठा octeon_device *oct, u32 समय_पूर्णांकr_in_us)
अणु
	/* This gives the SLI घड़ी per microsec */
	u32 oqticks_per_us = cn23xx_coprocessor_घड़ी(oct);

	oct->pfvf_hsword.coproc_tics_per_us = oqticks_per_us;

	/* This gives the घड़ी cycles per millisecond */
	oqticks_per_us *= 1000;

	/* This gives the oq ticks (1024 core घड़ी cycles) per millisecond */
	oqticks_per_us /= 1024;

	/* समय_पूर्णांकr is in microseconds. The next 2 steps gives the oq ticks
	 *  corressponding to समय_पूर्णांकr.
	 */
	oqticks_per_us *= समय_पूर्णांकr_in_us;
	oqticks_per_us /= 1000;

	वापस oqticks_per_us;
पूर्ण

अटल व्योम cn23xx_setup_global_mac_regs(काष्ठा octeon_device *oct)
अणु
	u16 mac_no = oct->pcie_port;
	u16 pf_num = oct->pf_num;
	u64 reg_val;
	u64 temp;

	/* programming SRN and TRS क्रम each MAC(0..3)  */

	dev_dbg(&oct->pci_dev->dev, "%s:Using pcie port %d\n",
		__func__, mac_no);
	/* By शेष, mapping all 64 IOQs to  a single MACs */

	reg_val =
	    octeon_पढ़ो_csr64(oct, CN23XX_SLI_PKT_MAC_RINFO64(mac_no, pf_num));

	अगर (oct->rev_id == OCTEON_CN23XX_REV_1_1) अणु
		/* setting SRN <6:0>  */
		reg_val = pf_num * CN23XX_MAX_RINGS_PER_PF_PASS_1_1;
	पूर्ण अन्यथा अणु
		/* setting SRN <6:0>  */
		reg_val = pf_num * CN23XX_MAX_RINGS_PER_PF;
	पूर्ण

	/* setting TRS <23:16> */
	reg_val = reg_val |
		  (oct->sriov_info.trs << CN23XX_PKT_MAC_CTL_RINFO_TRS_BIT_POS);
	/* setting RPVF <39:32> */
	temp = oct->sriov_info.rings_per_vf & 0xff;
	reg_val |= (temp << CN23XX_PKT_MAC_CTL_RINFO_RPVF_BIT_POS);

	/* setting NVFS <55:48> */
	temp = oct->sriov_info.max_vfs & 0xff;
	reg_val |= (temp << CN23XX_PKT_MAC_CTL_RINFO_NVFS_BIT_POS);

	/* ग_लिखो these settings to MAC रेजिस्टर */
	octeon_ग_लिखो_csr64(oct, CN23XX_SLI_PKT_MAC_RINFO64(mac_no, pf_num),
			   reg_val);

	dev_dbg(&oct->pci_dev->dev, "SLI_PKT_MAC(%d)_PF(%d)_RINFO : 0x%016llx\n",
		mac_no, pf_num, (u64)octeon_पढ़ो_csr64
		(oct, CN23XX_SLI_PKT_MAC_RINFO64(mac_no, pf_num)));
पूर्ण

अटल पूर्णांक cn23xx_reset_io_queues(काष्ठा octeon_device *oct)
अणु
	पूर्णांक ret_val = 0;
	u64 d64;
	u32 q_no, srn, ern;
	u32 loop = 1000;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->sriov_info.num_pf_rings;

	/*As per HRM reg description, s/w cant ग_लिखो 0 to ENB. */
	/*to make the queue off, need to set the RST bit. */

	/* Reset the Enable bit क्रम all the 64 IQs.  */
	क्रम (q_no = srn; q_no < ern; q_no++) अणु
		/* set RST bit to 1. This bit applies to both IQ and OQ */
		d64 = octeon_पढ़ो_csr64(oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
		d64 = d64 | CN23XX_PKT_INPUT_CTL_RST;
		octeon_ग_लिखो_csr64(oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no), d64);
	पूर्ण

	/*रुको until the RST bit is clear or the RST and quite bits are set*/
	क्रम (q_no = srn; q_no < ern; q_no++) अणु
		u64 reg_val = octeon_पढ़ो_csr64(oct,
					CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
		जबतक ((READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_RST) &&
		       !(READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_QUIET) &&
		       loop--) अणु
			WRITE_ONCE(reg_val, octeon_पढ़ो_csr64(
			    oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no)));
		पूर्ण
		अगर (!loop) अणु
			dev_err(&oct->pci_dev->dev,
				"clearing the reset reg failed or setting the quiet reg failed for qno: %u\n",
				q_no);
			वापस -1;
		पूर्ण
		WRITE_ONCE(reg_val, READ_ONCE(reg_val) &
			~CN23XX_PKT_INPUT_CTL_RST);
		octeon_ग_लिखो_csr64(oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
				   READ_ONCE(reg_val));

		WRITE_ONCE(reg_val, octeon_पढ़ो_csr64(
			   oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no)));
		अगर (READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_RST) अणु
			dev_err(&oct->pci_dev->dev,
				"clearing the reset failed for qno: %u\n",
				q_no);
			ret_val = -1;
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

अटल पूर्णांक cn23xx_pf_setup_global_input_regs(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;
	काष्ठा octeon_instr_queue *iq;
	u64 पूर्णांकr_threshold, reg_val;
	u32 q_no, ern, srn;
	u64 pf_num;
	u64 vf_num;

	pf_num = oct->pf_num;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->sriov_info.num_pf_rings;

	अगर (cn23xx_reset_io_queues(oct))
		वापस -1;

	/** Set the MAC_NUM and PVF_NUM in IQ_PKT_CONTROL reg
	 * क्रम all queues.Only PF can set these bits.
	 * bits 29:30 indicate the MAC num.
	 * bits 32:47 indicate the PVF num.
	 */
	क्रम (q_no = 0; q_no < ern; q_no++) अणु
		reg_val = oct->pcie_port << CN23XX_PKT_INPUT_CTL_MAC_NUM_POS;

		/* क्रम VF asचिन्हित queues. */
		अगर (q_no < oct->sriov_info.pf_srn) अणु
			vf_num = q_no / oct->sriov_info.rings_per_vf;
			vf_num += 1; /* VF1, VF2,........ */
		पूर्ण अन्यथा अणु
			vf_num = 0;
		पूर्ण

		reg_val |= vf_num << CN23XX_PKT_INPUT_CTL_VF_NUM_POS;
		reg_val |= pf_num << CN23XX_PKT_INPUT_CTL_PF_NUM_POS;

		octeon_ग_लिखो_csr64(oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
				   reg_val);
	पूर्ण

	/* Select ES, RO, NS, RDSIZE,DPTR Fomat#0 क्रम
	 * pf queues
	 */
	क्रम (q_no = srn; q_no < ern; q_no++) अणु
		व्योम __iomem *inst_cnt_reg;

		iq = oct->instr_queue[q_no];
		अगर (iq)
			inst_cnt_reg = iq->inst_cnt_reg;
		अन्यथा
			inst_cnt_reg = (u8 *)oct->mmio[0].hw_addr +
				       CN23XX_SLI_IQ_INSTR_COUNT64(q_no);

		reg_val =
		    octeon_पढ़ो_csr64(oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));

		reg_val |= CN23XX_PKT_INPUT_CTL_MASK;

		octeon_ग_लिखो_csr64(oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
				   reg_val);

		/* Set WMARK level क्रम triggering PI_INT */
		/* पूर्णांकr_threshold = CN23XX_DEF_IQ_INTR_THRESHOLD & */
		पूर्णांकr_threshold = CFG_GET_IQ_INTR_PKT(cn23xx->conf) &
				 CN23XX_PKT_IN_DONE_WMARK_MASK;

		ग_लिखोq((पढ़ोq(inst_cnt_reg) &
			~(CN23XX_PKT_IN_DONE_WMARK_MASK <<
			  CN23XX_PKT_IN_DONE_WMARK_BIT_POS)) |
		       (पूर्णांकr_threshold << CN23XX_PKT_IN_DONE_WMARK_BIT_POS),
		       inst_cnt_reg);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cn23xx_pf_setup_global_output_regs(काष्ठा octeon_device *oct)
अणु
	u32 reg_val;
	u32 q_no, ern, srn;
	u64 समय_प्रकारhreshold;

	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->sriov_info.num_pf_rings;

	अगर (CFG_GET_IS_SLI_BP_ON(cn23xx->conf)) अणु
		octeon_ग_लिखो_csr64(oct, CN23XX_SLI_OQ_WMARK, 32);
	पूर्ण अन्यथा अणु
		/** Set Output queue watermark to 0 to disable backpressure */
		octeon_ग_लिखो_csr64(oct, CN23XX_SLI_OQ_WMARK, 0);
	पूर्ण

	क्रम (q_no = srn; q_no < ern; q_no++) अणु
		reg_val = octeon_पढ़ो_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(q_no));

		/* clear IPTR */
		reg_val &= ~CN23XX_PKT_OUTPUT_CTL_IPTR;

		/* set DPTR */
		reg_val |= CN23XX_PKT_OUTPUT_CTL_DPTR;

		/* reset BMODE */
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_BMODE);

		/* No Relaxed Ordering, No Snoop, 64-bit Byte swap
		 * क्रम Output Queue ScatterList
		 * reset ROR_P, NSR_P
		 */
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_ROR_P);
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_NSR_P);

#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_ES_P);
#अन्यथा
		reg_val |= (CN23XX_PKT_OUTPUT_CTL_ES_P);
#पूर्ण_अगर
		/* No Relaxed Ordering, No Snoop, 64-bit Byte swap
		 * क्रम Output Queue Data
		 * reset ROR, NSR
		 */
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_ROR);
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_NSR);
		/* set the ES bit */
		reg_val |= (CN23XX_PKT_OUTPUT_CTL_ES);

		/* ग_लिखो all the selected settings */
		octeon_ग_लिखो_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(q_no), reg_val);

		/* Enabling these पूर्णांकerrupt in oct->fn_list.enable_पूर्णांकerrupt()
		 * routine which called after IOQ init.
		 * Set up पूर्णांकerrupt packet and समय thresholds
		 * क्रम all the OQs
		 */
		समय_प्रकारhreshold = cn23xx_pf_get_oq_ticks(
		    oct, (u32)CFG_GET_OQ_INTR_TIME(cn23xx->conf));

		octeon_ग_लिखो_csr64(oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(q_no),
				   (CFG_GET_OQ_INTR_PKT(cn23xx->conf) |
				    (समय_प्रकारhreshold << 32)));
	पूर्ण

	/** Setting the water mark level क्रम pko back pressure **/
	ग_लिखोq(0x40, (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_OQ_WMARK);

	/** Disabling setting OQs in reset when ring has no करोrebells
	 * enabling this will cause of head of line blocking
	 */
	/* Do it only क्रम pass1.1. and pass1.2 */
	अगर ((oct->rev_id == OCTEON_CN23XX_REV_1_0) ||
	    (oct->rev_id == OCTEON_CN23XX_REV_1_1))
		ग_लिखोq(पढ़ोq((u8 *)oct->mmio[0].hw_addr +
				     CN23XX_SLI_GBL_CONTROL) | 0x2,
		       (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_GBL_CONTROL);

	/** Enable channel-level backpressure */
	अगर (oct->pf_num)
		ग_लिखोq(0xffffffffffffffffULL,
		       (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_OUT_BP_EN2_W1S);
	अन्यथा
		ग_लिखोq(0xffffffffffffffffULL,
		       (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_OUT_BP_EN_W1S);
पूर्ण

अटल पूर्णांक cn23xx_setup_pf_device_regs(काष्ठा octeon_device *oct)
अणु
	cn23xx_enable_error_reporting(oct);

	/* program the MAC(0..3)_RINFO beक्रमe setting up input/output regs */
	cn23xx_setup_global_mac_regs(oct);

	अगर (cn23xx_pf_setup_global_input_regs(oct))
		वापस -1;

	cn23xx_pf_setup_global_output_regs(oct);

	/* Default error समयout value should be 0x200000 to aव्योम host hang
	 * when पढ़ोs invalid रेजिस्टर
	 */
	octeon_ग_लिखो_csr64(oct, CN23XX_SLI_WINDOW_CTL,
			   CN23XX_SLI_WINDOW_CTL_DEFAULT);

	/* set SLI_PKT_IN_JABBER to handle large VXLAN packets */
	octeon_ग_लिखो_csr64(oct, CN23XX_SLI_PKT_IN_JABBER, CN23XX_INPUT_JABBER);
	वापस 0;
पूर्ण

अटल व्योम cn23xx_setup_iq_regs(काष्ठा octeon_device *oct, u32 iq_no)
अणु
	काष्ठा octeon_instr_queue *iq = oct->instr_queue[iq_no];
	u64 pkt_in_करोne;

	iq_no += oct->sriov_info.pf_srn;

	/* Write the start of the input queue's ring and its size  */
	octeon_ग_लिखो_csr64(oct, CN23XX_SLI_IQ_BASE_ADDR64(iq_no),
			   iq->base_addr_dma);
	octeon_ग_लिखो_csr(oct, CN23XX_SLI_IQ_SIZE(iq_no), iq->max_count);

	/* Remember the करोorbell & inकाष्ठाion count रेजिस्टर addr
	 * क्रम this queue
	 */
	iq->करोorbell_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_IQ_DOORBELL(iq_no);
	iq->inst_cnt_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_IQ_INSTR_COUNT64(iq_no);
	dev_dbg(&oct->pci_dev->dev, "InstQ[%d]:dbell reg @ 0x%p instcnt_reg @ 0x%p\n",
		iq_no, iq->करोorbell_reg, iq->inst_cnt_reg);

	/* Store the current inकाष्ठाion counter (used in flush_iq
	 * calculation)
	 */
	pkt_in_करोne = पढ़ोq(iq->inst_cnt_reg);

	अगर (oct->msix_on) अणु
		/* Set CINT_ENB to enable IQ पूर्णांकerrupt   */
		ग_लिखोq((pkt_in_करोne | CN23XX_INTR_CINT_ENB),
		       iq->inst_cnt_reg);
	पूर्ण अन्यथा अणु
		/* Clear the count by writing back what we पढ़ो, but करोn't
		 * enable पूर्णांकerrupts
		 */
		ग_लिखोq(pkt_in_करोne, iq->inst_cnt_reg);
	पूर्ण

	iq->reset_instr_cnt = 0;
पूर्ण

अटल व्योम cn23xx_setup_oq_regs(काष्ठा octeon_device *oct, u32 oq_no)
अणु
	u32 reg_val;
	काष्ठा octeon_droq *droq = oct->droq[oq_no];
	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;
	u64 समय_प्रकारhreshold;
	u64 cnt_threshold;

	oq_no += oct->sriov_info.pf_srn;

	octeon_ग_लिखो_csr64(oct, CN23XX_SLI_OQ_BASE_ADDR64(oq_no),
			   droq->desc_ring_dma);
	octeon_ग_लिखो_csr(oct, CN23XX_SLI_OQ_SIZE(oq_no), droq->max_count);

	octeon_ग_लिखो_csr(oct, CN23XX_SLI_OQ_BUFF_INFO_SIZE(oq_no),
			 droq->buffer_size);

	/* Get the mapped address of the pkt_sent and pkts_credit regs */
	droq->pkts_sent_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_OQ_PKTS_SENT(oq_no);
	droq->pkts_credit_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_OQ_PKTS_CREDIT(oq_no);

	अगर (!oct->msix_on) अणु
		/* Enable this output queue to generate Packet Timer Interrupt
		 */
		reg_val =
		    octeon_पढ़ो_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(oq_no));
		reg_val |= CN23XX_PKT_OUTPUT_CTL_TENB;
		octeon_ग_लिखो_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(oq_no),
				 reg_val);

		/* Enable this output queue to generate Packet Count Interrupt
		 */
		reg_val =
		    octeon_पढ़ो_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(oq_no));
		reg_val |= CN23XX_PKT_OUTPUT_CTL_CENB;
		octeon_ग_लिखो_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(oq_no),
				 reg_val);
	पूर्ण अन्यथा अणु
		समय_प्रकारhreshold = cn23xx_pf_get_oq_ticks(
		    oct, (u32)CFG_GET_OQ_INTR_TIME(cn23xx->conf));
		cnt_threshold = (u32)CFG_GET_OQ_INTR_PKT(cn23xx->conf);

		octeon_ग_लिखो_csr64(
		    oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(oq_no),
		    ((समय_प्रकारhreshold << 32 | cnt_threshold)));
	पूर्ण
पूर्ण

अटल व्योम cn23xx_pf_mbox_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा octeon_mbox *mbox = (काष्ठा octeon_mbox *)wk->ctxptr;
	काष्ठा octeon_device *oct = mbox->oct_dev;
	u64 mbox_पूर्णांक_val, val64;
	u32 q_no, i;

	अगर (oct->rev_id < OCTEON_CN23XX_REV_1_1) अणु
		/*पढ़ो and clear by writing 1*/
		mbox_पूर्णांक_val = पढ़ोq(mbox->mbox_पूर्णांक_reg);
		ग_लिखोq(mbox_पूर्णांक_val, mbox->mbox_पूर्णांक_reg);

		क्रम (i = 0; i < oct->sriov_info.num_vfs_alloced; i++) अणु
			q_no = i * oct->sriov_info.rings_per_vf;

			val64 = पढ़ोq(oct->mbox[q_no]->mbox_ग_लिखो_reg);

			अगर (val64 && (val64 != OCTEON_PFVFACK)) अणु
				अगर (octeon_mbox_पढ़ो(oct->mbox[q_no]))
					octeon_mbox_process_message(
					    oct->mbox[q_no]);
			पूर्ण
		पूर्ण

		schedule_delayed_work(&wk->work, msecs_to_jअगरfies(10));
	पूर्ण अन्यथा अणु
		octeon_mbox_process_message(mbox);
	पूर्ण
पूर्ण

अटल पूर्णांक cn23xx_setup_pf_mbox(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_mbox *mbox = शून्य;
	u16 mac_no = oct->pcie_port;
	u16 pf_num = oct->pf_num;
	u32 q_no, i;

	अगर (!oct->sriov_info.max_vfs)
		वापस 0;

	क्रम (i = 0; i < oct->sriov_info.max_vfs; i++) अणु
		q_no = i * oct->sriov_info.rings_per_vf;

		mbox = vदो_स्मृति(माप(*mbox));
		अगर (!mbox)
			जाओ मुक्त_mbox;

		स_रखो(mbox, 0, माप(काष्ठा octeon_mbox));

		spin_lock_init(&mbox->lock);

		mbox->oct_dev = oct;

		mbox->q_no = q_no;

		mbox->state = OCTEON_MBOX_STATE_IDLE;

		/* PF mbox पूर्णांकerrupt reg */
		mbox->mbox_पूर्णांक_reg = (u8 *)oct->mmio[0].hw_addr +
				     CN23XX_SLI_MAC_PF_MBOX_INT(mac_no, pf_num);

		/* PF ग_लिखोs पूर्णांकo SIG0 reg */
		mbox->mbox_ग_लिखो_reg = (u8 *)oct->mmio[0].hw_addr +
				       CN23XX_SLI_PKT_PF_VF_MBOX_SIG(q_no, 0);

		/* PF पढ़ोs from SIG1 reg */
		mbox->mbox_पढ़ो_reg = (u8 *)oct->mmio[0].hw_addr +
				      CN23XX_SLI_PKT_PF_VF_MBOX_SIG(q_no, 1);

		/*Mail Box Thपढ़ो creation*/
		INIT_DELAYED_WORK(&mbox->mbox_poll_wk.work,
				  cn23xx_pf_mbox_thपढ़ो);
		mbox->mbox_poll_wk.ctxptr = (व्योम *)mbox;

		oct->mbox[q_no] = mbox;

		ग_लिखोq(OCTEON_PFVFSIG, mbox->mbox_पढ़ो_reg);
	पूर्ण

	अगर (oct->rev_id < OCTEON_CN23XX_REV_1_1)
		schedule_delayed_work(&oct->mbox[0]->mbox_poll_wk.work,
				      msecs_to_jअगरfies(0));

	वापस 0;

मुक्त_mbox:
	जबतक (i) अणु
		i--;
		vमुक्त(oct->mbox[i]);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक cn23xx_मुक्त_pf_mbox(काष्ठा octeon_device *oct)
अणु
	u32 q_no, i;

	अगर (!oct->sriov_info.max_vfs)
		वापस 0;

	क्रम (i = 0; i < oct->sriov_info.max_vfs; i++) अणु
		q_no = i * oct->sriov_info.rings_per_vf;
		cancel_delayed_work_sync(
		    &oct->mbox[q_no]->mbox_poll_wk.work);
		vमुक्त(oct->mbox[q_no]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cn23xx_enable_io_queues(काष्ठा octeon_device *oct)
अणु
	u64 reg_val;
	u32 srn, ern, q_no;
	u32 loop = 1000;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->num_iqs;

	क्रम (q_no = srn; q_no < ern; q_no++) अणु
		/* set the corresponding IQ IS_64B bit */
		अगर (oct->io_qmask.iq64B & BIT_ULL(q_no - srn)) अणु
			reg_val = octeon_पढ़ो_csr64(
			    oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
			reg_val = reg_val | CN23XX_PKT_INPUT_CTL_IS_64B;
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no), reg_val);
		पूर्ण

		/* set the corresponding IQ ENB bit */
		अगर (oct->io_qmask.iq & BIT_ULL(q_no - srn)) अणु
			/* IOQs are in reset by शेष in PEM2 mode,
			 * clearing reset bit
			 */
			reg_val = octeon_पढ़ो_csr64(
			    oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));

			अगर (reg_val & CN23XX_PKT_INPUT_CTL_RST) अणु
				जबतक ((reg_val & CN23XX_PKT_INPUT_CTL_RST) &&
				       !(reg_val &
					 CN23XX_PKT_INPUT_CTL_QUIET) &&
				       --loop) अणु
					reg_val = octeon_पढ़ो_csr64(
					    oct,
					    CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
				पूर्ण
				अगर (!loop) अणु
					dev_err(&oct->pci_dev->dev,
						"clearing the reset reg failed or setting the quiet reg failed for qno: %u\n",
						q_no);
					वापस -1;
				पूर्ण
				reg_val = reg_val & ~CN23XX_PKT_INPUT_CTL_RST;
				octeon_ग_लिखो_csr64(
				    oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
				    reg_val);

				reg_val = octeon_पढ़ो_csr64(
				    oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
				अगर (reg_val & CN23XX_PKT_INPUT_CTL_RST) अणु
					dev_err(&oct->pci_dev->dev,
						"clearing the reset failed for qno: %u\n",
						q_no);
					वापस -1;
				पूर्ण
			पूर्ण
			reg_val = octeon_पढ़ो_csr64(
			    oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
			reg_val = reg_val | CN23XX_PKT_INPUT_CTL_RING_ENB;
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no), reg_val);
		पूर्ण
	पूर्ण
	क्रम (q_no = srn; q_no < ern; q_no++) अणु
		u32 reg_val;
		/* set the corresponding OQ ENB bit */
		अगर (oct->io_qmask.oq & BIT_ULL(q_no - srn)) अणु
			reg_val = octeon_पढ़ो_csr(
			    oct, CN23XX_SLI_OQ_PKT_CONTROL(q_no));
			reg_val = reg_val | CN23XX_PKT_OUTPUT_CTL_RING_ENB;
			octeon_ग_लिखो_csr(oct, CN23XX_SLI_OQ_PKT_CONTROL(q_no),
					 reg_val);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cn23xx_disable_io_queues(काष्ठा octeon_device *oct)
अणु
	पूर्णांक q_no, loop;
	u64 d64;
	u32 d32;
	u32 srn, ern;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->num_iqs;

	/*** Disable Input Queues. ***/
	क्रम (q_no = srn; q_no < ern; q_no++) अणु
		loop = HZ;

		/* start the Reset क्रम a particular ring */
		WRITE_ONCE(d64, octeon_पढ़ो_csr64(
			   oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no)));
		WRITE_ONCE(d64, READ_ONCE(d64) &
					(~(CN23XX_PKT_INPUT_CTL_RING_ENB)));
		WRITE_ONCE(d64, READ_ONCE(d64) | CN23XX_PKT_INPUT_CTL_RST);
		octeon_ग_लिखो_csr64(oct, CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
				   READ_ONCE(d64));

		/* Wait until hardware indicates that the particular IQ
		 * is out of reset.
		 */
		WRITE_ONCE(d64, octeon_पढ़ो_csr64(
					oct, CN23XX_SLI_PKT_IOQ_RING_RST));
		जबतक (!(READ_ONCE(d64) & BIT_ULL(q_no)) && loop--) अणु
			WRITE_ONCE(d64, octeon_पढ़ो_csr64(
					oct, CN23XX_SLI_PKT_IOQ_RING_RST));
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण

		/* Reset the करोorbell रेजिस्टर क्रम this Input Queue. */
		octeon_ग_लिखो_csr(oct, CN23XX_SLI_IQ_DOORBELL(q_no), 0xFFFFFFFF);
		जबतक (octeon_पढ़ो_csr64(oct, CN23XX_SLI_IQ_DOORBELL(q_no)) &&
		       loop--) अणु
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण
	पूर्ण

	/*** Disable Output Queues. ***/
	क्रम (q_no = srn; q_no < ern; q_no++) अणु
		loop = HZ;

		/* Wait until hardware indicates that the particular IQ
		 * is out of reset.It given that SLI_PKT_RING_RST is
		 * common क्रम both IQs and OQs
		 */
		WRITE_ONCE(d64, octeon_पढ़ो_csr64(
					oct, CN23XX_SLI_PKT_IOQ_RING_RST));
		जबतक (!(READ_ONCE(d64) & BIT_ULL(q_no)) && loop--) अणु
			WRITE_ONCE(d64, octeon_पढ़ो_csr64(
					oct, CN23XX_SLI_PKT_IOQ_RING_RST));
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण

		/* Reset the करोorbell रेजिस्टर क्रम this Output Queue. */
		octeon_ग_लिखो_csr(oct, CN23XX_SLI_OQ_PKTS_CREDIT(q_no),
				 0xFFFFFFFF);
		जबतक (octeon_पढ़ो_csr64(oct,
					 CN23XX_SLI_OQ_PKTS_CREDIT(q_no)) &&
		       loop--) अणु
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण

		/* clear the SLI_PKT(0..63)_CNTS[CNT] reg value */
		WRITE_ONCE(d32, octeon_पढ़ो_csr(
					oct, CN23XX_SLI_OQ_PKTS_SENT(q_no)));
		octeon_ग_लिखो_csr(oct, CN23XX_SLI_OQ_PKTS_SENT(q_no),
				 READ_ONCE(d32));
	पूर्ण
पूर्ण

अटल u64 cn23xx_pf_msix_पूर्णांकerrupt_handler(व्योम *dev)
अणु
	काष्ठा octeon_ioq_vector *ioq_vector = (काष्ठा octeon_ioq_vector *)dev;
	काष्ठा octeon_device *oct = ioq_vector->oct_dev;
	u64 pkts_sent;
	u64 ret = 0;
	काष्ठा octeon_droq *droq = oct->droq[ioq_vector->droq_index];

	dev_dbg(&oct->pci_dev->dev, "In %s octeon_dev @ %p\n", __func__, oct);

	अगर (!droq) अणु
		dev_err(&oct->pci_dev->dev, "23XX bringup FIXME: oct pfnum:%d ioq_vector->ioq_num :%d droq is NULL\n",
			oct->pf_num, ioq_vector->ioq_num);
		वापस 0;
	पूर्ण

	pkts_sent = पढ़ोq(droq->pkts_sent_reg);

	/* If our device has पूर्णांकerrupted, then proceed. Also check
	 * क्रम all f's अगर पूर्णांकerrupt was triggered on an error
	 * and the PCI पढ़ो fails.
	 */
	अगर (!pkts_sent || (pkts_sent == 0xFFFFFFFFFFFFFFFFULL))
		वापस ret;

	/* Write count reg in sli_pkt_cnts to clear these पूर्णांक.*/
	अगर ((pkts_sent & CN23XX_INTR_PO_INT) ||
	    (pkts_sent & CN23XX_INTR_PI_INT)) अणु
		अगर (pkts_sent & CN23XX_INTR_PO_INT)
			ret |= MSIX_PO_INT;
	पूर्ण

	अगर (pkts_sent & CN23XX_INTR_PI_INT)
		/* We will clear the count when we update the पढ़ो_index. */
		ret |= MSIX_PI_INT;

	/* Never need to handle msix mbox पूर्णांकr क्रम pf. They arrive on the last
	 * msix
	 */
	वापस ret;
पूर्ण

अटल व्योम cn23xx_handle_pf_mbox_पूर्णांकr(काष्ठा octeon_device *oct)
अणु
	काष्ठा delayed_work *work;
	u64 mbox_पूर्णांक_val;
	u32 i, q_no;

	mbox_पूर्णांक_val = पढ़ोq(oct->mbox[0]->mbox_पूर्णांक_reg);

	क्रम (i = 0; i < oct->sriov_info.num_vfs_alloced; i++) अणु
		q_no = i * oct->sriov_info.rings_per_vf;

		अगर (mbox_पूर्णांक_val & BIT_ULL(q_no)) अणु
			ग_लिखोq(BIT_ULL(q_no),
			       oct->mbox[0]->mbox_पूर्णांक_reg);
			अगर (octeon_mbox_पढ़ो(oct->mbox[q_no])) अणु
				work = &oct->mbox[q_no]->mbox_poll_wk.work;
				schedule_delayed_work(work,
						      msecs_to_jअगरfies(0));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t cn23xx_पूर्णांकerrupt_handler(व्योम *dev)
अणु
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)dev;
	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;
	u64 पूर्णांकr64;

	dev_dbg(&oct->pci_dev->dev, "In %s octeon_dev @ %p\n", __func__, oct);
	पूर्णांकr64 = पढ़ोq(cn23xx->पूर्णांकr_sum_reg64);

	oct->पूर्णांक_status = 0;

	अगर (पूर्णांकr64 & CN23XX_INTR_ERR)
		dev_err(&oct->pci_dev->dev, "OCTEON[%d]: Error Intr: 0x%016llx\n",
			oct->octeon_id, CVM_CAST64(पूर्णांकr64));

	/* When VFs ग_लिखो पूर्णांकo MBOX_SIG2 reg,these पूर्णांकr is set in PF */
	अगर (पूर्णांकr64 & CN23XX_INTR_VF_MBOX)
		cn23xx_handle_pf_mbox_पूर्णांकr(oct);

	अगर (oct->msix_on != LIO_FLAG_MSIX_ENABLED) अणु
		अगर (पूर्णांकr64 & CN23XX_INTR_PKT_DATA)
			oct->पूर्णांक_status |= OCT_DEV_INTR_PKT_DATA;
	पूर्ण

	अगर (पूर्णांकr64 & (CN23XX_INTR_DMA0_FORCE))
		oct->पूर्णांक_status |= OCT_DEV_INTR_DMA0_FORCE;
	अगर (पूर्णांकr64 & (CN23XX_INTR_DMA1_FORCE))
		oct->पूर्णांक_status |= OCT_DEV_INTR_DMA1_FORCE;

	/* Clear the current पूर्णांकerrupts */
	ग_लिखोq(पूर्णांकr64, cn23xx->पूर्णांकr_sum_reg64);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cn23xx_bar1_idx_setup(काष्ठा octeon_device *oct, u64 core_addr,
				  u32 idx, पूर्णांक valid)
अणु
	u64 bar1;
	u64 reg_adr;

	अगर (!valid) अणु
		reg_adr = lio_pci_पढ़ोq(
			oct, CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));
		WRITE_ONCE(bar1, reg_adr);
		lio_pci_ग_लिखोq(oct, (READ_ONCE(bar1) & 0xFFFFFFFEULL),
			       CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));
		reg_adr = lio_pci_पढ़ोq(
			oct, CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));
		WRITE_ONCE(bar1, reg_adr);
		वापस;
	पूर्ण

	/*  The PEM(0..3)_BAR1_INDEX(0..15)[ADDR_IDX]<23:4> stores
	 *  bits <41:22> of the Core Addr
	 */
	lio_pci_ग_लिखोq(oct, (((core_addr >> 22) << 4) | PCI_BAR1_MASK),
		       CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));

	WRITE_ONCE(bar1, lio_pci_पढ़ोq(
		   oct, CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx)));
पूर्ण

अटल व्योम cn23xx_bar1_idx_ग_लिखो(काष्ठा octeon_device *oct, u32 idx, u32 mask)
अणु
	lio_pci_ग_लिखोq(oct, mask,
		       CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));
पूर्ण

अटल u32 cn23xx_bar1_idx_पढ़ो(काष्ठा octeon_device *oct, u32 idx)
अणु
	वापस (u32)lio_pci_पढ़ोq(
	    oct, CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));
पूर्ण

/* always call with lock held */
अटल u32 cn23xx_update_पढ़ो_index(काष्ठा octeon_instr_queue *iq)
अणु
	u32 new_idx;
	u32 last_करोne;
	u32 pkt_in_करोne = पढ़ोl(iq->inst_cnt_reg);

	last_करोne = pkt_in_करोne - iq->pkt_in_करोne;
	iq->pkt_in_करोne = pkt_in_करोne;

	/* Modulo of the new index with the IQ size will give us
	 * the new index.  The iq->reset_instr_cnt is always zero क्रम
	 * cn23xx, so no extra adjusपंचांगents are needed.
	 */
	new_idx = (iq->octeon_पढ़ो_index +
		   (u32)(last_करोne & CN23XX_PKT_IN_DONE_CNT_MASK)) %
		  iq->max_count;

	वापस new_idx;
पूर्ण

अटल व्योम cn23xx_enable_pf_पूर्णांकerrupt(काष्ठा octeon_device *oct, u8 पूर्णांकr_flag)
अणु
	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;
	u64 पूर्णांकr_val = 0;

	/*  Divide the single ग_लिखो to multiple ग_लिखोs based on the flag. */
	/* Enable Interrupt */
	अगर (पूर्णांकr_flag == OCTEON_ALL_INTR) अणु
		ग_लिखोq(cn23xx->पूर्णांकr_mask64, cn23xx->पूर्णांकr_enb_reg64);
	पूर्ण अन्यथा अगर (पूर्णांकr_flag & OCTEON_OUTPUT_INTR) अणु
		पूर्णांकr_val = पढ़ोq(cn23xx->पूर्णांकr_enb_reg64);
		पूर्णांकr_val |= CN23XX_INTR_PKT_DATA;
		ग_लिखोq(पूर्णांकr_val, cn23xx->पूर्णांकr_enb_reg64);
	पूर्ण अन्यथा अगर ((पूर्णांकr_flag & OCTEON_MBOX_INTR) &&
		   (oct->sriov_info.max_vfs > 0)) अणु
		अगर (oct->rev_id >= OCTEON_CN23XX_REV_1_1) अणु
			पूर्णांकr_val = पढ़ोq(cn23xx->पूर्णांकr_enb_reg64);
			पूर्णांकr_val |= CN23XX_INTR_VF_MBOX;
			ग_लिखोq(पूर्णांकr_val, cn23xx->पूर्णांकr_enb_reg64);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cn23xx_disable_pf_पूर्णांकerrupt(काष्ठा octeon_device *oct, u8 पूर्णांकr_flag)
अणु
	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;
	u64 पूर्णांकr_val = 0;

	/* Disable Interrupts */
	अगर (पूर्णांकr_flag == OCTEON_ALL_INTR) अणु
		ग_लिखोq(0, cn23xx->पूर्णांकr_enb_reg64);
	पूर्ण अन्यथा अगर (पूर्णांकr_flag & OCTEON_OUTPUT_INTR) अणु
		पूर्णांकr_val = पढ़ोq(cn23xx->पूर्णांकr_enb_reg64);
		पूर्णांकr_val &= ~CN23XX_INTR_PKT_DATA;
		ग_लिखोq(पूर्णांकr_val, cn23xx->पूर्णांकr_enb_reg64);
	पूर्ण अन्यथा अगर ((पूर्णांकr_flag & OCTEON_MBOX_INTR) &&
		   (oct->sriov_info.max_vfs > 0)) अणु
		अगर (oct->rev_id >= OCTEON_CN23XX_REV_1_1) अणु
			पूर्णांकr_val = पढ़ोq(cn23xx->पूर्णांकr_enb_reg64);
			पूर्णांकr_val &= ~CN23XX_INTR_VF_MBOX;
			ग_लिखोq(पूर्णांकr_val, cn23xx->पूर्णांकr_enb_reg64);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cn23xx_get_pcie_qlmport(काष्ठा octeon_device *oct)
अणु
	oct->pcie_port = (octeon_पढ़ो_csr(oct, CN23XX_SLI_MAC_NUMBER)) & 0xff;

	dev_dbg(&oct->pci_dev->dev, "OCTEON: CN23xx uses PCIE Port %d\n",
		oct->pcie_port);
पूर्ण

अटल पूर्णांक cn23xx_get_pf_num(काष्ठा octeon_device *oct)
अणु
	u32 fdl_bit = 0;
	u64 pkt0_in_ctl, d64;
	पूर्णांक pfnum, mac, trs, ret;

	ret = 0;

	/** Read Function Dependency Link reg to get the function number */
	अगर (pci_पढ़ो_config_dword(oct->pci_dev, CN23XX_PCIE_SRIOV_FDL,
				  &fdl_bit) == 0) अणु
		oct->pf_num = ((fdl_bit >> CN23XX_PCIE_SRIOV_FDL_BIT_POS) &
			       CN23XX_PCIE_SRIOV_FDL_MASK);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;

		/* Under some भव environments, extended PCI regs are
		 * inaccessible, in which हाल the above पढ़ो will have failed.
		 * In this हाल, पढ़ो the PF number from the
		 * SLI_PKT0_INPUT_CONTROL reg (written by f/w)
		 */
		pkt0_in_ctl = octeon_पढ़ो_csr64(oct,
						CN23XX_SLI_IQ_PKT_CONTROL64(0));
		pfnum = (pkt0_in_ctl >> CN23XX_PKT_INPUT_CTL_PF_NUM_POS) &
			CN23XX_PKT_INPUT_CTL_PF_NUM_MASK;
		mac = (octeon_पढ़ो_csr(oct, CN23XX_SLI_MAC_NUMBER)) & 0xff;

		/* validate PF num by पढ़ोing RINFO; f/w ग_लिखोs RINFO.trs == 1*/
		d64 = octeon_पढ़ो_csr64(oct,
					CN23XX_SLI_PKT_MAC_RINFO64(mac, pfnum));
		trs = (पूर्णांक)(d64 >> CN23XX_PKT_MAC_CTL_RINFO_TRS_BIT_POS) & 0xff;
		अगर (trs == 1) अणु
			dev_err(&oct->pci_dev->dev,
				"OCTEON: error reading PCI cfg space pfnum, re-read %u\n",
				pfnum);
			oct->pf_num = pfnum;
			ret = 0;
		पूर्ण अन्यथा अणु
			dev_err(&oct->pci_dev->dev,
				"OCTEON: error reading PCI cfg space pfnum; could not ascertain PF number\n");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cn23xx_setup_reg_address(काष्ठा octeon_device *oct)
अणु
	u8 __iomem *bar0_pciaddr = oct->mmio[0].hw_addr;
	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;

	oct->reg_list.pci_win_wr_addr_hi =
	    (u32 __iomem *)(bar0_pciaddr + CN23XX_WIN_WR_ADDR_HI);
	oct->reg_list.pci_win_wr_addr_lo =
	    (u32 __iomem *)(bar0_pciaddr + CN23XX_WIN_WR_ADDR_LO);
	oct->reg_list.pci_win_wr_addr =
	    (u64 __iomem *)(bar0_pciaddr + CN23XX_WIN_WR_ADDR64);

	oct->reg_list.pci_win_rd_addr_hi =
	    (u32 __iomem *)(bar0_pciaddr + CN23XX_WIN_RD_ADDR_HI);
	oct->reg_list.pci_win_rd_addr_lo =
	    (u32 __iomem *)(bar0_pciaddr + CN23XX_WIN_RD_ADDR_LO);
	oct->reg_list.pci_win_rd_addr =
	    (u64 __iomem *)(bar0_pciaddr + CN23XX_WIN_RD_ADDR64);

	oct->reg_list.pci_win_wr_data_hi =
	    (u32 __iomem *)(bar0_pciaddr + CN23XX_WIN_WR_DATA_HI);
	oct->reg_list.pci_win_wr_data_lo =
	    (u32 __iomem *)(bar0_pciaddr + CN23XX_WIN_WR_DATA_LO);
	oct->reg_list.pci_win_wr_data =
	    (u64 __iomem *)(bar0_pciaddr + CN23XX_WIN_WR_DATA64);

	oct->reg_list.pci_win_rd_data_hi =
	    (u32 __iomem *)(bar0_pciaddr + CN23XX_WIN_RD_DATA_HI);
	oct->reg_list.pci_win_rd_data_lo =
	    (u32 __iomem *)(bar0_pciaddr + CN23XX_WIN_RD_DATA_LO);
	oct->reg_list.pci_win_rd_data =
	    (u64 __iomem *)(bar0_pciaddr + CN23XX_WIN_RD_DATA64);

	cn23xx_get_pcie_qlmport(oct);

	cn23xx->पूर्णांकr_mask64 = CN23XX_INTR_MASK;
	अगर (!oct->msix_on)
		cn23xx->पूर्णांकr_mask64 |= CN23XX_INTR_PKT_TIME;
	अगर (oct->rev_id >= OCTEON_CN23XX_REV_1_1)
		cn23xx->पूर्णांकr_mask64 |= CN23XX_INTR_VF_MBOX;

	cn23xx->पूर्णांकr_sum_reg64 =
	    bar0_pciaddr +
	    CN23XX_SLI_MAC_PF_INT_SUM64(oct->pcie_port, oct->pf_num);
	cn23xx->पूर्णांकr_enb_reg64 =
	    bar0_pciaddr +
	    CN23XX_SLI_MAC_PF_INT_ENB64(oct->pcie_port, oct->pf_num);
पूर्ण

पूर्णांक cn23xx_sriov_config(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_cn23xx_pf *cn23xx = (काष्ठा octeon_cn23xx_pf *)oct->chip;
	u32 max_rings, total_rings, max_vfs, rings_per_vf;
	u32 pf_srn, num_pf_rings;
	u32 max_possible_vfs;

	cn23xx->conf =
		(काष्ठा octeon_config *)oct_get_config_info(oct, LIO_23XX);
	चयन (oct->rev_id) अणु
	हाल OCTEON_CN23XX_REV_1_0:
		max_rings = CN23XX_MAX_RINGS_PER_PF_PASS_1_0;
		max_possible_vfs = CN23XX_MAX_VFS_PER_PF_PASS_1_0;
		अवरोध;
	हाल OCTEON_CN23XX_REV_1_1:
		max_rings = CN23XX_MAX_RINGS_PER_PF_PASS_1_1;
		max_possible_vfs = CN23XX_MAX_VFS_PER_PF_PASS_1_1;
		अवरोध;
	शेष:
		max_rings = CN23XX_MAX_RINGS_PER_PF;
		max_possible_vfs = CN23XX_MAX_VFS_PER_PF;
		अवरोध;
	पूर्ण

	अगर (oct->sriov_info.num_pf_rings)
		num_pf_rings = oct->sriov_info.num_pf_rings;
	अन्यथा
		num_pf_rings = num_present_cpus();

#अगर_घोषित CONFIG_PCI_IOV
	max_vfs = min_t(u32,
			(max_rings - num_pf_rings), max_possible_vfs);
	rings_per_vf = 1;
#अन्यथा
	max_vfs = 0;
	rings_per_vf = 0;
#पूर्ण_अगर

	total_rings = num_pf_rings + max_vfs;

	/* the first ring of the pf */
	pf_srn = total_rings - num_pf_rings;

	oct->sriov_info.trs = total_rings;
	oct->sriov_info.max_vfs = max_vfs;
	oct->sriov_info.rings_per_vf = rings_per_vf;
	oct->sriov_info.pf_srn = pf_srn;
	oct->sriov_info.num_pf_rings = num_pf_rings;
	dev_notice(&oct->pci_dev->dev, "trs:%d max_vfs:%d rings_per_vf:%d pf_srn:%d num_pf_rings:%d\n",
		   oct->sriov_info.trs, oct->sriov_info.max_vfs,
		   oct->sriov_info.rings_per_vf, oct->sriov_info.pf_srn,
		   oct->sriov_info.num_pf_rings);

	oct->sriov_info.sriov_enabled = 0;

	वापस 0;
पूर्ण

पूर्णांक setup_cn23xx_octeon_pf_device(काष्ठा octeon_device *oct)
अणु
	u32 data32;
	u64 BAR0, BAR1;

	pci_पढ़ो_config_dword(oct->pci_dev, PCI_BASE_ADDRESS_0, &data32);
	BAR0 = (u64)(data32 & ~0xf);
	pci_पढ़ो_config_dword(oct->pci_dev, PCI_BASE_ADDRESS_1, &data32);
	BAR0 |= ((u64)data32 << 32);
	pci_पढ़ो_config_dword(oct->pci_dev, PCI_BASE_ADDRESS_2, &data32);
	BAR1 = (u64)(data32 & ~0xf);
	pci_पढ़ो_config_dword(oct->pci_dev, PCI_BASE_ADDRESS_3, &data32);
	BAR1 |= ((u64)data32 << 32);

	अगर (!BAR0 || !BAR1) अणु
		अगर (!BAR0)
			dev_err(&oct->pci_dev->dev, "device BAR0 unassigned\n");
		अगर (!BAR1)
			dev_err(&oct->pci_dev->dev, "device BAR1 unassigned\n");
		वापस 1;
	पूर्ण

	अगर (octeon_map_pci_barx(oct, 0, 0))
		वापस 1;

	अगर (octeon_map_pci_barx(oct, 1, MAX_BAR1_IOREMAP_SIZE)) अणु
		dev_err(&oct->pci_dev->dev, "%s CN23XX BAR1 map failed\n",
			__func__);
		octeon_unmap_pci_barx(oct, 0);
		वापस 1;
	पूर्ण

	अगर (cn23xx_get_pf_num(oct) != 0)
		वापस 1;

	अगर (cn23xx_sriov_config(oct)) अणु
		octeon_unmap_pci_barx(oct, 0);
		octeon_unmap_pci_barx(oct, 1);
		वापस 1;
	पूर्ण

	octeon_ग_लिखो_csr64(oct, CN23XX_SLI_MAC_CREDIT_CNT, 0x3F802080802080ULL);

	oct->fn_list.setup_iq_regs = cn23xx_setup_iq_regs;
	oct->fn_list.setup_oq_regs = cn23xx_setup_oq_regs;
	oct->fn_list.setup_mbox = cn23xx_setup_pf_mbox;
	oct->fn_list.मुक्त_mbox = cn23xx_मुक्त_pf_mbox;

	oct->fn_list.process_पूर्णांकerrupt_regs = cn23xx_पूर्णांकerrupt_handler;
	oct->fn_list.msix_पूर्णांकerrupt_handler = cn23xx_pf_msix_पूर्णांकerrupt_handler;

	oct->fn_list.soft_reset = cn23xx_pf_soft_reset;
	oct->fn_list.setup_device_regs = cn23xx_setup_pf_device_regs;
	oct->fn_list.update_iq_पढ़ो_idx = cn23xx_update_पढ़ो_index;

	oct->fn_list.bar1_idx_setup = cn23xx_bar1_idx_setup;
	oct->fn_list.bar1_idx_ग_लिखो = cn23xx_bar1_idx_ग_लिखो;
	oct->fn_list.bar1_idx_पढ़ो = cn23xx_bar1_idx_पढ़ो;

	oct->fn_list.enable_पूर्णांकerrupt = cn23xx_enable_pf_पूर्णांकerrupt;
	oct->fn_list.disable_पूर्णांकerrupt = cn23xx_disable_pf_पूर्णांकerrupt;

	oct->fn_list.enable_io_queues = cn23xx_enable_io_queues;
	oct->fn_list.disable_io_queues = cn23xx_disable_io_queues;

	cn23xx_setup_reg_address(oct);

	oct->coproc_घड़ी_rate = 1000000ULL * cn23xx_coprocessor_घड़ी(oct);

	वापस 0;
पूर्ण

पूर्णांक validate_cn23xx_pf_config_info(काष्ठा octeon_device *oct,
				   काष्ठा octeon_config *conf23xx)
अणु
	अगर (CFG_GET_IQ_MAX_Q(conf23xx) > CN23XX_MAX_INPUT_QUEUES) अणु
		dev_err(&oct->pci_dev->dev, "%s: Num IQ (%d) exceeds Max (%d)\n",
			__func__, CFG_GET_IQ_MAX_Q(conf23xx),
			CN23XX_MAX_INPUT_QUEUES);
		वापस 1;
	पूर्ण

	अगर (CFG_GET_OQ_MAX_Q(conf23xx) > CN23XX_MAX_OUTPUT_QUEUES) अणु
		dev_err(&oct->pci_dev->dev, "%s: Num OQ (%d) exceeds Max (%d)\n",
			__func__, CFG_GET_OQ_MAX_Q(conf23xx),
			CN23XX_MAX_OUTPUT_QUEUES);
		वापस 1;
	पूर्ण

	अगर (CFG_GET_IQ_INSTR_TYPE(conf23xx) != OCTEON_32BYTE_INSTR &&
	    CFG_GET_IQ_INSTR_TYPE(conf23xx) != OCTEON_64BYTE_INSTR) अणु
		dev_err(&oct->pci_dev->dev, "%s: Invalid instr type for IQ\n",
			__func__);
		वापस 1;
	पूर्ण

	अगर (!CFG_GET_OQ_REFILL_THRESHOLD(conf23xx)) अणु
		dev_err(&oct->pci_dev->dev, "%s: Invalid parameter for OQ\n",
			__func__);
		वापस 1;
	पूर्ण

	अगर (!(CFG_GET_OQ_INTR_TIME(conf23xx))) अणु
		dev_err(&oct->pci_dev->dev, "%s: Invalid parameter for OQ\n",
			__func__);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cn23xx_fw_loaded(काष्ठा octeon_device *oct)
अणु
	u64 val;

	/* If there's more than one active PF on this NIC, then that
	 * implies that the NIC firmware is loaded and running.  This check
	 * prevents a rare false negative that might occur अगर we only relied
	 * on checking the SCR2_BIT_FW_LOADED flag.  The false negative would
	 * happen अगर the PF driver sees SCR2_BIT_FW_LOADED as cleared even
	 * though the firmware was alपढ़ोy loaded but still booting and has yet
	 * to set SCR2_BIT_FW_LOADED.
	 */
	अगर (atomic_पढ़ो(oct->adapter_refcount) > 1)
		वापस 1;

	val = octeon_पढ़ो_csr64(oct, CN23XX_SLI_SCRATCH2);
	वापस (val >> SCR2_BIT_FW_LOADED) & 1ULL;
पूर्ण

व्योम cn23xx_tell_vf_its_macaddr_changed(काष्ठा octeon_device *oct, पूर्णांक vfidx,
					u8 *mac)
अणु
	अगर (oct->sriov_info.vf_drv_loaded_mask & BIT_ULL(vfidx)) अणु
		काष्ठा octeon_mbox_cmd mbox_cmd;

		mbox_cmd.msg.u64 = 0;
		mbox_cmd.msg.s.type = OCTEON_MBOX_REQUEST;
		mbox_cmd.msg.s.resp_needed = 0;
		mbox_cmd.msg.s.cmd = OCTEON_PF_CHANGED_VF_MACADDR;
		mbox_cmd.msg.s.len = 1;
		mbox_cmd.recv_len = 0;
		mbox_cmd.recv_status = 0;
		mbox_cmd.fn = शून्य;
		mbox_cmd.fn_arg = शून्य;
		ether_addr_copy(mbox_cmd.msg.s.params, mac);
		mbox_cmd.q_no = vfidx * oct->sriov_info.rings_per_vf;
		octeon_mbox_ग_लिखो(oct, &mbox_cmd);
	पूर्ण
पूर्ण

अटल व्योम
cn23xx_get_vf_stats_callback(काष्ठा octeon_device *oct,
			     काष्ठा octeon_mbox_cmd *cmd, व्योम *arg)
अणु
	काष्ठा oct_vf_stats_ctx *ctx = arg;

	स_नकल(ctx->stats, cmd->data, माप(काष्ठा oct_vf_stats));
	atomic_set(&ctx->status, 1);
पूर्ण

पूर्णांक cn23xx_get_vf_stats(काष्ठा octeon_device *oct, पूर्णांक vfidx,
			काष्ठा oct_vf_stats *stats)
अणु
	u32 समयout = HZ; // 1sec
	काष्ठा octeon_mbox_cmd mbox_cmd;
	काष्ठा oct_vf_stats_ctx ctx;
	u32 count = 0, ret;

	अगर (!(oct->sriov_info.vf_drv_loaded_mask & (1ULL << vfidx)))
		वापस -1;

	अगर (माप(काष्ठा oct_vf_stats) > माप(mbox_cmd.data))
		वापस -1;

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_REQUEST;
	mbox_cmd.msg.s.resp_needed = 1;
	mbox_cmd.msg.s.cmd = OCTEON_GET_VF_STATS;
	mbox_cmd.msg.s.len = 1;
	mbox_cmd.q_no = vfidx * oct->sriov_info.rings_per_vf;
	mbox_cmd.recv_len = 0;
	mbox_cmd.recv_status = 0;
	mbox_cmd.fn = (octeon_mbox_callback_t)cn23xx_get_vf_stats_callback;
	ctx.stats = stats;
	atomic_set(&ctx.status, 0);
	mbox_cmd.fn_arg = (व्योम *)&ctx;
	स_रखो(mbox_cmd.data, 0, माप(mbox_cmd.data));
	octeon_mbox_ग_लिखो(oct, &mbox_cmd);

	करो अणु
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक ((atomic_पढ़ो(&ctx.status) == 0) && (count++ < समयout));

	ret = atomic_पढ़ो(&ctx.status);
	अगर (ret == 0) अणु
		octeon_mbox_cancel(oct, 0);
		dev_err(&oct->pci_dev->dev, "Unable to get stats from VF-%d, timedout\n",
			vfidx);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
