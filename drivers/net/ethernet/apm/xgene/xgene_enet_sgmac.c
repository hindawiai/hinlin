<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 *	    Keyur Chudgar <kchudgar@apm.com>
 */

#समावेश "xgene_enet_main.h"
#समावेश "xgene_enet_hw.h"
#समावेश "xgene_enet_sgmac.h"
#समावेश "xgene_enet_xgmac.h"

अटल व्योम xgene_enet_wr_csr(काष्ठा xgene_enet_pdata *p, u32 offset, u32 val)
अणु
	ioग_लिखो32(val, p->eth_csr_addr + offset);
पूर्ण

अटल व्योम xgene_enet_wr_clkrst_csr(काष्ठा xgene_enet_pdata *p, u32 offset,
				     u32 val)
अणु
	ioग_लिखो32(val, p->base_addr + offset);
पूर्ण

अटल व्योम xgene_enet_wr_ring_अगर(काष्ठा xgene_enet_pdata *p,
				  u32 offset, u32 val)
अणु
	ioग_लिखो32(val, p->eth_ring_अगर_addr + offset);
पूर्ण

अटल व्योम xgene_enet_wr_diag_csr(काष्ठा xgene_enet_pdata *p,
				   u32 offset, u32 val)
अणु
	ioग_लिखो32(val, p->eth_diag_csr_addr + offset);
पूर्ण

अटल व्योम xgene_enet_wr_mcx_csr(काष्ठा xgene_enet_pdata *pdata,
				  u32 offset, u32 val)
अणु
	व्योम __iomem *addr = pdata->mcx_mac_csr_addr + offset;

	ioग_लिखो32(val, addr);
पूर्ण

अटल u32 xgene_enet_rd_csr(काष्ठा xgene_enet_pdata *p, u32 offset)
अणु
	वापस ioपढ़ो32(p->eth_csr_addr + offset);
पूर्ण

अटल u32 xgene_enet_rd_diag_csr(काष्ठा xgene_enet_pdata *p, u32 offset)
अणु
	वापस ioपढ़ो32(p->eth_diag_csr_addr + offset);
पूर्ण

अटल u32 xgene_enet_rd_mcx_csr(काष्ठा xgene_enet_pdata *p, u32 offset)
अणु
	वापस ioपढ़ो32(p->mcx_mac_csr_addr + offset);
पूर्ण

अटल पूर्णांक xgene_enet_ecc_init(काष्ठा xgene_enet_pdata *p)
अणु
	काष्ठा net_device *ndev = p->ndev;
	u32 data, shutकरोwn;
	पूर्णांक i = 0;

	shutकरोwn = xgene_enet_rd_diag_csr(p, ENET_CFG_MEM_RAM_SHUTDOWN_ADDR);
	data = xgene_enet_rd_diag_csr(p, ENET_BLOCK_MEM_RDY_ADDR);

	अगर (!shutकरोwn && data == ~0U) अणु
		netdev_dbg(ndev, "+ ecc_init done, skipping\n");
		वापस 0;
	पूर्ण

	xgene_enet_wr_diag_csr(p, ENET_CFG_MEM_RAM_SHUTDOWN_ADDR, 0);
	करो अणु
		usleep_range(100, 110);
		data = xgene_enet_rd_diag_csr(p, ENET_BLOCK_MEM_RDY_ADDR);
		अगर (data == ~0U)
			वापस 0;
	पूर्ण जबतक (++i < 10);

	netdev_err(ndev, "Failed to release memory from shutdown\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम xgene_sgmac_get_drop_cnt(काष्ठा xgene_enet_pdata *pdata,
				     u32 *rx, u32 *tx)
अणु
	u32 addr, count;

	addr = (pdata->enet_id != XGENE_ENET1) ?
		XG_MCX_ICM_ECM_DROP_COUNT_REG0_ADDR :
		ICM_ECM_DROP_COUNT_REG0_ADDR + pdata->port_id * OFFSET_4;
	count = xgene_enet_rd_mcx_csr(pdata, addr);
	*rx = ICM_DROP_COUNT(count);
	*tx = ECM_DROP_COUNT(count);
	/* Errata: 10GE_4 - ICM_ECM_DROP_COUNT not clear-on-पढ़ो */
	addr = (pdata->enet_id != XGENE_ENET1) ?
		XG_MCX_ECM_CONFIG0_REG_0_ADDR :
		ECM_CONFIG0_REG_0_ADDR + pdata->port_id * OFFSET_4;
	xgene_enet_rd_mcx_csr(pdata, addr);
पूर्ण

अटल व्योम xgene_enet_config_ring_अगर_assoc(काष्ठा xgene_enet_pdata *p)
अणु
	u32 val;

	val = (p->enet_id == XGENE_ENET1) ? 0xffffffff : 0;
	xgene_enet_wr_ring_अगर(p, ENET_CFGSSQMIWQASSOC_ADDR, val);
	xgene_enet_wr_ring_अगर(p, ENET_CFGSSQMIFPQASSOC_ADDR, val);
पूर्ण

अटल व्योम xgene_mii_phy_ग_लिखो(काष्ठा xgene_enet_pdata *p, u8 phy_id,
				u32 reg, u16 data)
अणु
	u32 addr, wr_data, करोne;
	पूर्णांक i;

	addr = PHY_ADDR(phy_id) | REG_ADDR(reg);
	xgene_enet_wr_mac(p, MII_MGMT_ADDRESS_ADDR, addr);

	wr_data = PHY_CONTROL(data);
	xgene_enet_wr_mac(p, MII_MGMT_CONTROL_ADDR, wr_data);

	क्रम (i = 0; i < 10; i++) अणु
		करोne = xgene_enet_rd_mac(p, MII_MGMT_INDICATORS_ADDR);
		अगर (!(करोne & BUSY_MASK))
			वापस;
		usleep_range(10, 20);
	पूर्ण

	netdev_err(p->ndev, "MII_MGMT write failed\n");
पूर्ण

अटल u32 xgene_mii_phy_पढ़ो(काष्ठा xgene_enet_pdata *p, u8 phy_id, u32 reg)
अणु
	u32 addr, data, करोne;
	पूर्णांक i;

	addr = PHY_ADDR(phy_id) | REG_ADDR(reg);
	xgene_enet_wr_mac(p, MII_MGMT_ADDRESS_ADDR, addr);
	xgene_enet_wr_mac(p, MII_MGMT_COMMAND_ADDR, READ_CYCLE_MASK);

	क्रम (i = 0; i < 10; i++) अणु
		करोne = xgene_enet_rd_mac(p, MII_MGMT_INDICATORS_ADDR);
		अगर (!(करोne & BUSY_MASK)) अणु
			data = xgene_enet_rd_mac(p, MII_MGMT_STATUS_ADDR);
			xgene_enet_wr_mac(p, MII_MGMT_COMMAND_ADDR, 0);

			वापस data;
		पूर्ण
		usleep_range(10, 20);
	पूर्ण

	netdev_err(p->ndev, "MII_MGMT read failed\n");

	वापस 0;
पूर्ण

अटल व्योम xgene_sgmac_reset(काष्ठा xgene_enet_pdata *p)
अणु
	xgene_enet_wr_mac(p, MAC_CONFIG_1_ADDR, SOFT_RESET1);
	xgene_enet_wr_mac(p, MAC_CONFIG_1_ADDR, 0);
पूर्ण

अटल व्योम xgene_sgmac_set_mac_addr(काष्ठा xgene_enet_pdata *p)
अणु
	u32 addr0, addr1;
	u8 *dev_addr = p->ndev->dev_addr;

	addr0 = (dev_addr[3] << 24) | (dev_addr[2] << 16) |
		(dev_addr[1] << 8) | dev_addr[0];
	xgene_enet_wr_mac(p, STATION_ADDR0_ADDR, addr0);

	addr1 = xgene_enet_rd_mac(p, STATION_ADDR1_ADDR);
	addr1 |= (dev_addr[5] << 24) | (dev_addr[4] << 16);
	xgene_enet_wr_mac(p, STATION_ADDR1_ADDR, addr1);
पूर्ण

अटल u32 xgene_enet_link_status(काष्ठा xgene_enet_pdata *p)
अणु
	u32 data;

	data = xgene_mii_phy_पढ़ो(p, INT_PHY_ADDR,
				  SGMII_BASE_PAGE_ABILITY_ADDR >> 2);

	अगर (LINK_SPEED(data) == PHY_SPEED_1000)
		p->phy_speed = SPEED_1000;
	अन्यथा अगर (LINK_SPEED(data) == PHY_SPEED_100)
		p->phy_speed = SPEED_100;
	अन्यथा
		p->phy_speed = SPEED_10;

	वापस data & LINK_UP;
पूर्ण

अटल व्योम xgene_sgmii_configure(काष्ठा xgene_enet_pdata *p)
अणु
	xgene_mii_phy_ग_लिखो(p, INT_PHY_ADDR, SGMII_TBI_CONTROL_ADDR >> 2,
			    0x8000);
	xgene_mii_phy_ग_लिखो(p, INT_PHY_ADDR, SGMII_CONTROL_ADDR >> 2, 0x9000);
	xgene_mii_phy_ग_लिखो(p, INT_PHY_ADDR, SGMII_TBI_CONTROL_ADDR >> 2, 0);
पूर्ण

अटल व्योम xgene_sgmii_tbi_control_reset(काष्ठा xgene_enet_pdata *p)
अणु
	xgene_mii_phy_ग_लिखो(p, INT_PHY_ADDR, SGMII_TBI_CONTROL_ADDR >> 2,
			    0x8000);
	xgene_mii_phy_ग_लिखो(p, INT_PHY_ADDR, SGMII_TBI_CONTROL_ADDR >> 2, 0);
पूर्ण

अटल व्योम xgene_sgmii_reset(काष्ठा xgene_enet_pdata *p)
अणु
	u32 value;

	अगर (p->phy_speed == SPEED_UNKNOWN)
		वापस;

	value = xgene_mii_phy_पढ़ो(p, INT_PHY_ADDR,
				   SGMII_BASE_PAGE_ABILITY_ADDR >> 2);
	अगर (!(value & LINK_UP))
		xgene_sgmii_tbi_control_reset(p);
पूर्ण

अटल व्योम xgene_sgmac_set_speed(काष्ठा xgene_enet_pdata *p)
अणु
	u32 icm0_addr, icm2_addr, debug_addr;
	u32 icm0, icm2, पूर्णांकf_ctl;
	u32 mc2, value;

	xgene_sgmii_reset(p);

	अगर (p->enet_id == XGENE_ENET1) अणु
		icm0_addr = ICM_CONFIG0_REG_0_ADDR + p->port_id * OFFSET_8;
		icm2_addr = ICM_CONFIG2_REG_0_ADDR + p->port_id * OFFSET_4;
		debug_addr = DEBUG_REG_ADDR;
	पूर्ण अन्यथा अणु
		icm0_addr = XG_MCX_ICM_CONFIG0_REG_0_ADDR;
		icm2_addr = XG_MCX_ICM_CONFIG2_REG_0_ADDR;
		debug_addr = XG_DEBUG_REG_ADDR;
	पूर्ण

	icm0 = xgene_enet_rd_mcx_csr(p, icm0_addr);
	icm2 = xgene_enet_rd_mcx_csr(p, icm2_addr);
	mc2 = xgene_enet_rd_mac(p, MAC_CONFIG_2_ADDR);
	पूर्णांकf_ctl = xgene_enet_rd_mac(p, INTERFACE_CONTROL_ADDR);

	चयन (p->phy_speed) अणु
	हाल SPEED_10:
		ENET_INTERFACE_MODE2_SET(&mc2, 1);
		पूर्णांकf_ctl &= ~(ENET_LHD_MODE | ENET_GHD_MODE);
		CFG_MACMODE_SET(&icm0, 0);
		CFG_WAITASYNCRD_SET(&icm2, 500);
		अवरोध;
	हाल SPEED_100:
		ENET_INTERFACE_MODE2_SET(&mc2, 1);
		पूर्णांकf_ctl &= ~ENET_GHD_MODE;
		पूर्णांकf_ctl |= ENET_LHD_MODE;
		CFG_MACMODE_SET(&icm0, 1);
		CFG_WAITASYNCRD_SET(&icm2, 80);
		अवरोध;
	शेष:
		ENET_INTERFACE_MODE2_SET(&mc2, 2);
		पूर्णांकf_ctl &= ~ENET_LHD_MODE;
		पूर्णांकf_ctl |= ENET_GHD_MODE;
		CFG_MACMODE_SET(&icm0, 2);
		CFG_WAITASYNCRD_SET(&icm2, 16);
		value = xgene_enet_rd_csr(p, debug_addr);
		value |= CFG_BYPASS_UNISEC_TX | CFG_BYPASS_UNISEC_RX;
		xgene_enet_wr_csr(p, debug_addr, value);
		अवरोध;
	पूर्ण

	mc2 |= FULL_DUPLEX2 | PAD_CRC;
	xgene_enet_wr_mac(p, MAC_CONFIG_2_ADDR, mc2);
	xgene_enet_wr_mac(p, INTERFACE_CONTROL_ADDR, पूर्णांकf_ctl);
	xgene_enet_wr_mcx_csr(p, icm0_addr, icm0);
	xgene_enet_wr_mcx_csr(p, icm2_addr, icm2);
पूर्ण

अटल व्योम xgene_sgmac_set_frame_size(काष्ठा xgene_enet_pdata *pdata, पूर्णांक size)
अणु
	xgene_enet_wr_mac(pdata, MAX_FRAME_LEN_ADDR, size);
पूर्ण

अटल व्योम xgene_sgmii_enable_स्वतःneg(काष्ठा xgene_enet_pdata *p)
अणु
	u32 data, loop = 10;

	xgene_sgmii_configure(p);

	जबतक (loop--) अणु
		data = xgene_mii_phy_पढ़ो(p, INT_PHY_ADDR,
					  SGMII_STATUS_ADDR >> 2);
		अगर ((data & AUTO_NEG_COMPLETE) && (data & LINK_STATUS))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	अगर (!(data & AUTO_NEG_COMPLETE) || !(data & LINK_STATUS))
		netdev_err(p->ndev, "Auto-negotiation failed\n");
पूर्ण

अटल व्योम xgene_sgmac_rxtx(काष्ठा xgene_enet_pdata *p, u32 bits, bool set)
अणु
	u32 data;

	data = xgene_enet_rd_mac(p, MAC_CONFIG_1_ADDR);

	अगर (set)
		data |= bits;
	अन्यथा
		data &= ~bits;

	xgene_enet_wr_mac(p, MAC_CONFIG_1_ADDR, data);
पूर्ण

अटल व्योम xgene_sgmac_flowctl_tx(काष्ठा xgene_enet_pdata *p, bool enable)
अणु
	xgene_sgmac_rxtx(p, TX_FLOW_EN, enable);

	p->mac_ops->enable_tx_छोड़ो(p, enable);
पूर्ण

अटल व्योम xgene_sgmac_flowctl_rx(काष्ठा xgene_enet_pdata *pdata, bool enable)
अणु
	xgene_sgmac_rxtx(pdata, RX_FLOW_EN, enable);
पूर्ण

अटल व्योम xgene_sgmac_init(काष्ठा xgene_enet_pdata *p)
अणु
	u32 छोड़ो_thres_reg, छोड़ो_off_thres_reg;
	u32 enet_spare_cfg_reg, rsअगर_config_reg;
	u32 cfg_bypass_reg, rx_dv_gate_reg;
	u32 data, data1, data2, offset;
	u32 multi_dpf_reg;

	अगर (!(p->enet_id == XGENE_ENET2 && p->mdio_driver))
		xgene_sgmac_reset(p);

	xgene_sgmii_enable_स्वतःneg(p);
	xgene_sgmac_set_speed(p);
	xgene_sgmac_set_mac_addr(p);

	अगर (p->enet_id == XGENE_ENET1) अणु
		enet_spare_cfg_reg = ENET_SPARE_CFG_REG_ADDR;
		rsअगर_config_reg = RSIF_CONFIG_REG_ADDR;
		cfg_bypass_reg = CFG_BYPASS_ADDR;
		offset = p->port_id * OFFSET_4;
		rx_dv_gate_reg = SG_RX_DV_GATE_REG_0_ADDR + offset;
	पूर्ण अन्यथा अणु
		enet_spare_cfg_reg = XG_ENET_SPARE_CFG_REG_ADDR;
		rsअगर_config_reg = XG_RSIF_CONFIG_REG_ADDR;
		cfg_bypass_reg = XG_CFG_BYPASS_ADDR;
		rx_dv_gate_reg = XG_MCX_RX_DV_GATE_REG_0_ADDR;
	पूर्ण

	data = xgene_enet_rd_csr(p, enet_spare_cfg_reg);
	data |= MPA_IDLE_WITH_QMI_EMPTY;
	xgene_enet_wr_csr(p, enet_spare_cfg_reg, data);

	/* Adjust MDC घड़ी frequency */
	data = xgene_enet_rd_mac(p, MII_MGMT_CONFIG_ADDR);
	MGMT_CLOCK_SEL_SET(&data, 7);
	xgene_enet_wr_mac(p, MII_MGMT_CONFIG_ADDR, data);

	/* Enable drop अगर bufpool not available */
	data = xgene_enet_rd_csr(p, rsअगर_config_reg);
	data |= CFG_RSIF_FPBUFF_TIMEOUT_EN;
	xgene_enet_wr_csr(p, rsअगर_config_reg, data);

	/* Configure HW छोड़ो frame generation */
	multi_dpf_reg = (p->enet_id == XGENE_ENET1) ? CSR_MULTI_DPF0_ADDR :
			 XG_MCX_MULTI_DPF0_ADDR;
	data = xgene_enet_rd_mcx_csr(p, multi_dpf_reg);
	data = (DEF_QUANTA << 16) | (data & 0xffff);
	xgene_enet_wr_mcx_csr(p, multi_dpf_reg, data);

	अगर (p->enet_id != XGENE_ENET1) अणु
		data = xgene_enet_rd_mcx_csr(p, XG_MCX_MULTI_DPF1_ADDR);
		data =  (NORM_PAUSE_OPCODE << 16) | (data & 0xFFFF);
		xgene_enet_wr_mcx_csr(p, XG_MCX_MULTI_DPF1_ADDR, data);
	पूर्ण

	छोड़ो_thres_reg = (p->enet_id == XGENE_ENET1) ? RXBUF_PAUSE_THRESH :
			   XG_RXBUF_PAUSE_THRESH;
	छोड़ो_off_thres_reg = (p->enet_id == XGENE_ENET1) ?
			       RXBUF_PAUSE_OFF_THRESH : 0;

	अगर (p->enet_id == XGENE_ENET1) अणु
		data1 = xgene_enet_rd_csr(p, छोड़ो_thres_reg);
		data2 = xgene_enet_rd_csr(p, छोड़ो_off_thres_reg);

		अगर (!(p->port_id % 2)) अणु
			data1 = (data1 & 0xffff0000) | DEF_PAUSE_THRES;
			data2 = (data2 & 0xffff0000) | DEF_PAUSE_OFF_THRES;
		पूर्ण अन्यथा अणु
			data1 = (data1 & 0xffff) | (DEF_PAUSE_THRES << 16);
			data2 = (data2 & 0xffff) | (DEF_PAUSE_OFF_THRES << 16);
		पूर्ण

		xgene_enet_wr_csr(p, छोड़ो_thres_reg, data1);
		xgene_enet_wr_csr(p, छोड़ो_off_thres_reg, data2);
	पूर्ण अन्यथा अणु
		data = (DEF_PAUSE_OFF_THRES << 16) | DEF_PAUSE_THRES;
		xgene_enet_wr_csr(p, छोड़ो_thres_reg, data);
	पूर्ण

	xgene_sgmac_flowctl_tx(p, p->tx_छोड़ो);
	xgene_sgmac_flowctl_rx(p, p->rx_छोड़ो);

	/* Bypass traffic gating */
	xgene_enet_wr_csr(p, XG_ENET_SPARE_CFG_REG_1_ADDR, 0x84);
	xgene_enet_wr_csr(p, cfg_bypass_reg, RESUME_TX);
	xgene_enet_wr_mcx_csr(p, rx_dv_gate_reg, RESUME_RX0);
पूर्ण

अटल व्योम xgene_sgmac_rx_enable(काष्ठा xgene_enet_pdata *p)
अणु
	xgene_sgmac_rxtx(p, RX_EN, true);
पूर्ण

अटल व्योम xgene_sgmac_tx_enable(काष्ठा xgene_enet_pdata *p)
अणु
	xgene_sgmac_rxtx(p, TX_EN, true);
पूर्ण

अटल व्योम xgene_sgmac_rx_disable(काष्ठा xgene_enet_pdata *p)
अणु
	xgene_sgmac_rxtx(p, RX_EN, false);
पूर्ण

अटल व्योम xgene_sgmac_tx_disable(काष्ठा xgene_enet_pdata *p)
अणु
	xgene_sgmac_rxtx(p, TX_EN, false);
पूर्ण

अटल पूर्णांक xgene_enet_reset(काष्ठा xgene_enet_pdata *p)
अणु
	काष्ठा device *dev = &p->pdev->dev;

	अगर (!xgene_ring_mgr_init(p))
		वापस -ENODEV;

	अगर (p->mdio_driver && p->enet_id == XGENE_ENET2) अणु
		xgene_enet_config_ring_अगर_assoc(p);
		वापस 0;
	पूर्ण

	अगर (p->enet_id == XGENE_ENET2)
		xgene_enet_wr_clkrst_csr(p, XGENET_CONFIG_REG_ADDR, SGMII_EN);

	अगर (dev->of_node) अणु
		अगर (!IS_ERR(p->clk)) अणु
			clk_prepare_enable(p->clk);
			udelay(5);
			clk_disable_unprepare(p->clk);
			udelay(5);
			clk_prepare_enable(p->clk);
			udelay(5);
		पूर्ण
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_ACPI
		acpi_status status;

		status = acpi_evaluate_object(ACPI_HANDLE(&p->pdev->dev),
					      "_RST", शून्य, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_evaluate_object(ACPI_HANDLE(&p->pdev->dev),
					     "_INI", शून्य, शून्य);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (!p->port_id) अणु
		xgene_enet_ecc_init(p);
		xgene_enet_config_ring_अगर_assoc(p);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgene_enet_cle_bypass(काष्ठा xgene_enet_pdata *p,
				  u32 dst_ring_num, u16 bufpool_id,
				  u16 nxtbufpool_id)
अणु
	u32 cle_bypass_reg0, cle_bypass_reg1;
	u32 offset = p->port_id * MAC_OFFSET;
	u32 data, fpsel, nxtfpsel;

	अगर (p->enet_id == XGENE_ENET1) अणु
		cle_bypass_reg0 = CLE_BYPASS_REG0_0_ADDR;
		cle_bypass_reg1 = CLE_BYPASS_REG1_0_ADDR;
	पूर्ण अन्यथा अणु
		cle_bypass_reg0 = XCLE_BYPASS_REG0_ADDR;
		cle_bypass_reg1 = XCLE_BYPASS_REG1_ADDR;
	पूर्ण

	data = CFG_CLE_BYPASS_EN0;
	xgene_enet_wr_csr(p, cle_bypass_reg0 + offset, data);

	fpsel = xgene_enet_get_fpsel(bufpool_id);
	nxtfpsel = xgene_enet_get_fpsel(nxtbufpool_id);
	data = CFG_CLE_DSTQID0(dst_ring_num) | CFG_CLE_FPSEL0(fpsel) |
	       CFG_CLE_NXTFPSEL0(nxtfpsel);
	xgene_enet_wr_csr(p, cle_bypass_reg1 + offset, data);
पूर्ण

अटल व्योम xgene_enet_clear(काष्ठा xgene_enet_pdata *pdata,
			     काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 addr, data;

	अगर (xgene_enet_is_bufpool(ring->id)) अणु
		addr = ENET_CFGSSQMIFPRESET_ADDR;
		data = BIT(xgene_enet_get_fpsel(ring->id));
	पूर्ण अन्यथा अणु
		addr = ENET_CFGSSQMIWQRESET_ADDR;
		data = BIT(xgene_enet_ring_bufnum(ring->id));
	पूर्ण

	xgene_enet_wr_ring_अगर(pdata, addr, data);
पूर्ण

अटल व्योम xgene_enet_shutकरोwn(काष्ठा xgene_enet_pdata *p)
अणु
	काष्ठा device *dev = &p->pdev->dev;

	अगर (dev->of_node) अणु
		अगर (!IS_ERR(p->clk))
			clk_disable_unprepare(p->clk);
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_link_state(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xgene_enet_pdata *p = container_of(to_delayed_work(work),
				     काष्ठा xgene_enet_pdata, link_work);
	काष्ठा net_device *ndev = p->ndev;
	u32 link, poll_पूर्णांकerval;

	link = xgene_enet_link_status(p);
	अगर (link) अणु
		अगर (!netअगर_carrier_ok(ndev)) अणु
			netअगर_carrier_on(ndev);
			xgene_sgmac_set_speed(p);
			xgene_sgmac_rx_enable(p);
			xgene_sgmac_tx_enable(p);
			netdev_info(ndev, "Link is Up - %dMbps\n",
				    p->phy_speed);
		पूर्ण
		poll_पूर्णांकerval = PHY_POLL_LINK_ON;
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(ndev)) अणु
			xgene_sgmac_rx_disable(p);
			xgene_sgmac_tx_disable(p);
			netअगर_carrier_off(ndev);
			netdev_info(ndev, "Link is Down\n");
		पूर्ण
		poll_पूर्णांकerval = PHY_POLL_LINK_OFF;
	पूर्ण

	schedule_delayed_work(&p->link_work, poll_पूर्णांकerval);
पूर्ण

अटल व्योम xgene_sgmac_enable_tx_छोड़ो(काष्ठा xgene_enet_pdata *p, bool enable)
अणु
	u32 data, ecm_cfg_addr;

	अगर (p->enet_id == XGENE_ENET1) अणु
		ecm_cfg_addr = (!(p->port_id % 2)) ? CSR_ECM_CFG_0_ADDR :
				CSR_ECM_CFG_1_ADDR;
	पूर्ण अन्यथा अणु
		ecm_cfg_addr = XG_MCX_ECM_CFG_0_ADDR;
	पूर्ण

	data = xgene_enet_rd_mcx_csr(p, ecm_cfg_addr);
	अगर (enable)
		data |= MULTI_DPF_AUTOCTRL | PAUSE_XON_EN;
	अन्यथा
		data &= ~(MULTI_DPF_AUTOCTRL | PAUSE_XON_EN);
	xgene_enet_wr_mcx_csr(p, ecm_cfg_addr, data);
पूर्ण

स्थिर काष्ठा xgene_mac_ops xgene_sgmac_ops = अणु
	.init		= xgene_sgmac_init,
	.reset		= xgene_sgmac_reset,
	.rx_enable	= xgene_sgmac_rx_enable,
	.tx_enable	= xgene_sgmac_tx_enable,
	.rx_disable	= xgene_sgmac_rx_disable,
	.tx_disable	= xgene_sgmac_tx_disable,
	.get_drop_cnt   = xgene_sgmac_get_drop_cnt,
	.set_speed	= xgene_sgmac_set_speed,
	.set_mac_addr	= xgene_sgmac_set_mac_addr,
	.set_framesize  = xgene_sgmac_set_frame_size,
	.link_state	= xgene_enet_link_state,
	.enable_tx_छोड़ो = xgene_sgmac_enable_tx_छोड़ो,
	.flowctl_tx     = xgene_sgmac_flowctl_tx,
	.flowctl_rx     = xgene_sgmac_flowctl_rx
पूर्ण;

स्थिर काष्ठा xgene_port_ops xgene_sgport_ops = अणु
	.reset		= xgene_enet_reset,
	.clear		= xgene_enet_clear,
	.cle_bypass	= xgene_enet_cle_bypass,
	.shutकरोwn	= xgene_enet_shutकरोwn
पूर्ण;
