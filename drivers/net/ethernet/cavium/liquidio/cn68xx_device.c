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
#समावेश "cn68xx_device.h"
#समावेश "cn68xx_regs.h"

अटल व्योम lio_cn68xx_set_dpi_regs(काष्ठा octeon_device *oct)
अणु
	u32 i;
	u32 fअगरo_sizes[6] = अणु 3, 3, 1, 1, 1, 8 पूर्ण;

	lio_pci_ग_लिखोq(oct, CN6XXX_DPI_DMA_CTL_MASK, CN6XXX_DPI_DMA_CONTROL);
	dev_dbg(&oct->pci_dev->dev, "DPI_DMA_CONTROL: 0x%016llx\n",
		lio_pci_पढ़ोq(oct, CN6XXX_DPI_DMA_CONTROL));

	क्रम (i = 0; i < 6; i++) अणु
		/* Prevent service of inकाष्ठाion queue क्रम all DMA engines
		 * Engine 5 will reमुख्य 0. Engines 0 - 4 will be setup by
		 * core.
		 */
		lio_pci_ग_लिखोq(oct, 0, CN6XXX_DPI_DMA_ENG_ENB(i));
		lio_pci_ग_लिखोq(oct, fअगरo_sizes[i], CN6XXX_DPI_DMA_ENG_BUF(i));
		dev_dbg(&oct->pci_dev->dev, "DPI_ENG_BUF%d: 0x%016llx\n", i,
			lio_pci_पढ़ोq(oct, CN6XXX_DPI_DMA_ENG_BUF(i)));
	पूर्ण

	/* DPI_SLI_PRT_CFG has MPS and MRRS settings that will be set
	 * separately.
	 */

	lio_pci_ग_लिखोq(oct, 1, CN6XXX_DPI_CTL);
	dev_dbg(&oct->pci_dev->dev, "DPI_CTL: 0x%016llx\n",
		lio_pci_पढ़ोq(oct, CN6XXX_DPI_CTL));
पूर्ण

अटल पूर्णांक lio_cn68xx_soft_reset(काष्ठा octeon_device *oct)
अणु
	lio_cn6xxx_soft_reset(oct);
	lio_cn68xx_set_dpi_regs(oct);

	वापस 0;
पूर्ण

अटल व्योम lio_cn68xx_setup_pkt_ctl_regs(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_cn6xxx *cn68xx = (काष्ठा octeon_cn6xxx *)oct->chip;
	u64 pktctl, tx_pipe, max_oqs;

	pktctl = octeon_पढ़ो_csr64(oct, CN6XXX_SLI_PKT_CTL);

	/* 68XX specअगरic */
	max_oqs = CFG_GET_OQ_MAX_Q(CHIP_CONF(oct, cn6xxx));
	tx_pipe  = octeon_पढ़ो_csr64(oct, CN68XX_SLI_TX_PIPE);
	tx_pipe &= 0xffffffffff00ffffULL; /* clear out NUMP field */
	tx_pipe |= max_oqs << 16; /* put max_oqs in NUMP field */
	octeon_ग_लिखो_csr64(oct, CN68XX_SLI_TX_PIPE, tx_pipe);

	अगर (CFG_GET_IS_SLI_BP_ON(cn68xx->conf))
		pktctl |= 0xF;
	अन्यथा
		/* Disable per-port backpressure. */
		pktctl &= ~0xF;
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_PKT_CTL, pktctl);
पूर्ण

अटल पूर्णांक lio_cn68xx_setup_device_regs(काष्ठा octeon_device *oct)
अणु
	lio_cn6xxx_setup_pcie_mps(oct, PCIE_MPS_DEFAULT);
	lio_cn6xxx_setup_pcie_mrrs(oct, PCIE_MRRS_256B);
	lio_cn6xxx_enable_error_reporting(oct);

	lio_cn6xxx_setup_global_input_regs(oct);
	lio_cn68xx_setup_pkt_ctl_regs(oct);
	lio_cn6xxx_setup_global_output_regs(oct);

	/* Default error समयout value should be 0x200000 to aव्योम host hang
	 * when पढ़ोs invalid रेजिस्टर
	 */
	octeon_ग_लिखो_csr64(oct, CN6XXX_SLI_WINDOW_CTL, 0x200000ULL);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम lio_cn68xx_venकरोr_message_fix(काष्ठा octeon_device *oct)
अणु
	u32 val = 0;

	/* Set M_VEND1_DRP and M_VEND0_DRP bits */
	pci_पढ़ो_config_dword(oct->pci_dev, CN6XXX_PCIE_FLTMSK, &val);
	val |= 0x3;
	pci_ग_लिखो_config_dword(oct->pci_dev, CN6XXX_PCIE_FLTMSK, val);
पूर्ण

अटल पूर्णांक lio_is_210nv(काष्ठा octeon_device *oct)
अणु
	u64 mio_qlm4_cfg = lio_pci_पढ़ोq(oct, CN6XXX_MIO_QLM4_CFG);

	वापस ((mio_qlm4_cfg & CN6XXX_MIO_QLM_CFG_MASK) == 0);
पूर्ण

पूर्णांक lio_setup_cn68xx_octeon_device(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_cn6xxx *cn68xx = (काष्ठा octeon_cn6xxx *)oct->chip;
	u16 card_type = LIO_410NV;

	अगर (octeon_map_pci_barx(oct, 0, 0))
		वापस 1;

	अगर (octeon_map_pci_barx(oct, 1, MAX_BAR1_IOREMAP_SIZE)) अणु
		dev_err(&oct->pci_dev->dev, "%s CN68XX BAR1 map failed\n",
			__func__);
		octeon_unmap_pci_barx(oct, 0);
		वापस 1;
	पूर्ण

	spin_lock_init(&cn68xx->lock_क्रम_droq_पूर्णांक_enb_reg);

	oct->fn_list.setup_iq_regs = lio_cn6xxx_setup_iq_regs;
	oct->fn_list.setup_oq_regs = lio_cn6xxx_setup_oq_regs;

	oct->fn_list.process_पूर्णांकerrupt_regs = lio_cn6xxx_process_पूर्णांकerrupt_regs;
	oct->fn_list.soft_reset = lio_cn68xx_soft_reset;
	oct->fn_list.setup_device_regs = lio_cn68xx_setup_device_regs;
	oct->fn_list.update_iq_पढ़ो_idx = lio_cn6xxx_update_पढ़ो_index;

	oct->fn_list.bar1_idx_setup = lio_cn6xxx_bar1_idx_setup;
	oct->fn_list.bar1_idx_ग_लिखो = lio_cn6xxx_bar1_idx_ग_लिखो;
	oct->fn_list.bar1_idx_पढ़ो = lio_cn6xxx_bar1_idx_पढ़ो;

	oct->fn_list.enable_पूर्णांकerrupt = lio_cn6xxx_enable_पूर्णांकerrupt;
	oct->fn_list.disable_पूर्णांकerrupt = lio_cn6xxx_disable_पूर्णांकerrupt;

	oct->fn_list.enable_io_queues = lio_cn6xxx_enable_io_queues;
	oct->fn_list.disable_io_queues = lio_cn6xxx_disable_io_queues;

	lio_cn6xxx_setup_reg_address(oct, oct->chip, &oct->reg_list);

	/* Determine variant of card */
	अगर (lio_is_210nv(oct))
		card_type = LIO_210NV;

	cn68xx->conf = (काष्ठा octeon_config *)
		       oct_get_config_info(oct, card_type);
	अगर (!cn68xx->conf) अणु
		dev_err(&oct->pci_dev->dev, "%s No Config found for CN68XX %s\n",
			__func__,
			(card_type == LIO_410NV) ? LIO_410NV_NAME :
			LIO_210NV_NAME);
		octeon_unmap_pci_barx(oct, 0);
		octeon_unmap_pci_barx(oct, 1);
		वापस 1;
	पूर्ण

	oct->coproc_घड़ी_rate = 1000000ULL * lio_cn6xxx_coprocessor_घड़ी(oct);

	lio_cn68xx_venकरोr_message_fix(oct);

	वापस 0;
पूर्ण
