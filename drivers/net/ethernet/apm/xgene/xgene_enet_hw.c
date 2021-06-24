<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 *	    Ravi Patel <rapatel@apm.com>
 *	    Keyur Chudgar <kchudgar@apm.com>
 */

#समावेश "xgene_enet_main.h"
#समावेश "xgene_enet_hw.h"

अटल व्योम xgene_enet_ring_init(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 *ring_cfg = ring->state;
	u64 addr = ring->dma;
	क्रमागत xgene_enet_ring_cfgsize cfgsize = ring->cfgsize;

	ring_cfg[4] |= (1 << SELTHRSH_POS) &
			CREATE_MASK(SELTHRSH_POS, SELTHRSH_LEN);
	ring_cfg[3] |= ACCEPTLERR;
	ring_cfg[2] |= QCOHERENT;

	addr >>= 8;
	ring_cfg[2] |= (addr << RINGADDRL_POS) &
			CREATE_MASK_ULL(RINGADDRL_POS, RINGADDRL_LEN);
	addr >>= RINGADDRL_LEN;
	ring_cfg[3] |= addr & CREATE_MASK_ULL(RINGADDRH_POS, RINGADDRH_LEN);
	ring_cfg[3] |= ((u32)cfgsize << RINGSIZE_POS) &
			CREATE_MASK(RINGSIZE_POS, RINGSIZE_LEN);
पूर्ण

अटल व्योम xgene_enet_ring_set_type(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 *ring_cfg = ring->state;
	bool is_bufpool;
	u32 val;

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	val = (is_bufpool) ? RING_BUFPOOL : RING_REGULAR;
	ring_cfg[4] |= (val << RINGTYPE_POS) &
			CREATE_MASK(RINGTYPE_POS, RINGTYPE_LEN);

	अगर (is_bufpool) अणु
		ring_cfg[3] |= (BUFPOOL_MODE << RINGMODE_POS) &
				CREATE_MASK(RINGMODE_POS, RINGMODE_LEN);
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_ring_set_recombbuf(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 *ring_cfg = ring->state;

	ring_cfg[3] |= RECOMBBUF;
	ring_cfg[3] |= (0xf << RECOMTIMEOUTL_POS) &
			CREATE_MASK(RECOMTIMEOUTL_POS, RECOMTIMEOUTL_LEN);
	ring_cfg[4] |= 0x7 & CREATE_MASK(RECOMTIMEOUTH_POS, RECOMTIMEOUTH_LEN);
पूर्ण

अटल व्योम xgene_enet_ring_wr32(काष्ठा xgene_enet_desc_ring *ring,
				 u32 offset, u32 data)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ring->ndev);

	ioग_लिखो32(data, pdata->ring_csr_addr + offset);
पूर्ण

अटल व्योम xgene_enet_ring_rd32(काष्ठा xgene_enet_desc_ring *ring,
				 u32 offset, u32 *data)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ring->ndev);

	*data = ioपढ़ो32(pdata->ring_csr_addr + offset);
पूर्ण

अटल व्योम xgene_enet_ग_लिखो_ring_state(काष्ठा xgene_enet_desc_ring *ring)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ring->ndev);
	पूर्णांक i;

	xgene_enet_ring_wr32(ring, CSR_RING_CONFIG, ring->num);
	क्रम (i = 0; i < pdata->ring_ops->num_ring_config; i++) अणु
		xgene_enet_ring_wr32(ring, CSR_RING_WR_BASE + (i * 4),
				     ring->state[i]);
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_clr_ring_state(काष्ठा xgene_enet_desc_ring *ring)
अणु
	स_रखो(ring->state, 0, माप(ring->state));
	xgene_enet_ग_लिखो_ring_state(ring);
पूर्ण

अटल व्योम xgene_enet_set_ring_state(काष्ठा xgene_enet_desc_ring *ring)
अणु
	xgene_enet_ring_set_type(ring);

	अगर (xgene_enet_ring_owner(ring->id) == RING_OWNER_ETH0 ||
	    xgene_enet_ring_owner(ring->id) == RING_OWNER_ETH1)
		xgene_enet_ring_set_recombbuf(ring);

	xgene_enet_ring_init(ring);
	xgene_enet_ग_लिखो_ring_state(ring);
पूर्ण

अटल व्योम xgene_enet_set_ring_id(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 ring_id_val, ring_id_buf;
	bool is_bufpool;

	is_bufpool = xgene_enet_is_bufpool(ring->id);

	ring_id_val = ring->id & GENMASK(9, 0);
	ring_id_val |= OVERWRITE;

	ring_id_buf = (ring->num << 9) & GENMASK(18, 9);
	ring_id_buf |= PREFETCH_BUF_EN;
	अगर (is_bufpool)
		ring_id_buf |= IS_BUFFER_POOL;

	xgene_enet_ring_wr32(ring, CSR_RING_ID, ring_id_val);
	xgene_enet_ring_wr32(ring, CSR_RING_ID_BUF, ring_id_buf);
पूर्ण

अटल व्योम xgene_enet_clr_desc_ring_id(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 ring_id;

	ring_id = ring->id | OVERWRITE;
	xgene_enet_ring_wr32(ring, CSR_RING_ID, ring_id);
	xgene_enet_ring_wr32(ring, CSR_RING_ID_BUF, 0);
पूर्ण

अटल काष्ठा xgene_enet_desc_ring *xgene_enet_setup_ring(
				    काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 size = ring->size;
	u32 i, data;
	bool is_bufpool;

	xgene_enet_clr_ring_state(ring);
	xgene_enet_set_ring_state(ring);
	xgene_enet_set_ring_id(ring);

	ring->slots = xgene_enet_get_numslots(ring->id, size);

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	अगर (is_bufpool || xgene_enet_ring_owner(ring->id) != RING_OWNER_CPU)
		वापस ring;

	क्रम (i = 0; i < ring->slots; i++)
		xgene_enet_mark_desc_slot_empty(&ring->raw_desc[i]);

	xgene_enet_ring_rd32(ring, CSR_RING_NE_INT_MODE, &data);
	data |= BIT(31 - xgene_enet_ring_bufnum(ring->id));
	xgene_enet_ring_wr32(ring, CSR_RING_NE_INT_MODE, data);

	वापस ring;
पूर्ण

अटल व्योम xgene_enet_clear_ring(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 data;
	bool is_bufpool;

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	अगर (is_bufpool || xgene_enet_ring_owner(ring->id) != RING_OWNER_CPU)
		जाओ out;

	xgene_enet_ring_rd32(ring, CSR_RING_NE_INT_MODE, &data);
	data &= ~BIT(31 - xgene_enet_ring_bufnum(ring->id));
	xgene_enet_ring_wr32(ring, CSR_RING_NE_INT_MODE, data);

out:
	xgene_enet_clr_desc_ring_id(ring);
	xgene_enet_clr_ring_state(ring);
पूर्ण

अटल व्योम xgene_enet_wr_cmd(काष्ठा xgene_enet_desc_ring *ring, पूर्णांक count)
अणु
	ioग_लिखो32(count, ring->cmd);
पूर्ण

अटल u32 xgene_enet_ring_len(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 __iomem *cmd_base = ring->cmd_base;
	u32 ring_state, num_msgs;

	ring_state = ioपढ़ो32(&cmd_base[1]);
	num_msgs = GET_VAL(NUMMSGSINQ, ring_state);

	वापस num_msgs;
पूर्ण

व्योम xgene_enet_parse_error(काष्ठा xgene_enet_desc_ring *ring,
			    क्रमागत xgene_enet_err_code status)
अणु
	चयन (status) अणु
	हाल INGRESS_CRC:
		ring->rx_crc_errors++;
		अवरोध;
	हाल INGRESS_CHECKSUM:
	हाल INGRESS_CHECKSUM_COMPUTE:
		ring->rx_errors++;
		अवरोध;
	हाल INGRESS_TRUNC_FRAME:
		ring->rx_frame_errors++;
		अवरोध;
	हाल INGRESS_PKT_LEN:
		ring->rx_length_errors++;
		अवरोध;
	हाल INGRESS_PKT_UNDER:
		ring->rx_frame_errors++;
		अवरोध;
	हाल INGRESS_FIFO_OVERRUN:
		ring->rx_fअगरo_errors++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_wr_csr(काष्ठा xgene_enet_pdata *pdata,
			      u32 offset, u32 val)
अणु
	व्योम __iomem *addr = pdata->eth_csr_addr + offset;

	ioग_लिखो32(val, addr);
पूर्ण

अटल व्योम xgene_enet_wr_ring_अगर(काष्ठा xgene_enet_pdata *pdata,
				  u32 offset, u32 val)
अणु
	व्योम __iomem *addr = pdata->eth_ring_अगर_addr + offset;

	ioग_लिखो32(val, addr);
पूर्ण

अटल व्योम xgene_enet_wr_diag_csr(काष्ठा xgene_enet_pdata *pdata,
				   u32 offset, u32 val)
अणु
	व्योम __iomem *addr = pdata->eth_diag_csr_addr + offset;

	ioग_लिखो32(val, addr);
पूर्ण

अटल व्योम xgene_enet_wr_mcx_csr(काष्ठा xgene_enet_pdata *pdata,
				  u32 offset, u32 val)
अणु
	व्योम __iomem *addr = pdata->mcx_mac_csr_addr + offset;

	ioग_लिखो32(val, addr);
पूर्ण

व्योम xgene_enet_wr_mac(काष्ठा xgene_enet_pdata *pdata, u32 wr_addr, u32 wr_data)
अणु
	व्योम __iomem *addr, *wr, *cmd, *cmd_करोne;
	काष्ठा net_device *ndev = pdata->ndev;
	u8 रुको = 10;
	u32 करोne;

	अगर (pdata->mdio_driver && ndev->phydev &&
	    phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode)) अणु
		काष्ठा mii_bus *bus = ndev->phydev->mdio.bus;

		वापस xgene_mdio_wr_mac(bus->priv, wr_addr, wr_data);
	पूर्ण

	addr = pdata->mcx_mac_addr + MAC_ADDR_REG_OFFSET;
	wr = pdata->mcx_mac_addr + MAC_WRITE_REG_OFFSET;
	cmd = pdata->mcx_mac_addr + MAC_COMMAND_REG_OFFSET;
	cmd_करोne = pdata->mcx_mac_addr + MAC_COMMAND_DONE_REG_OFFSET;

	spin_lock(&pdata->mac_lock);
	ioग_लिखो32(wr_addr, addr);
	ioग_लिखो32(wr_data, wr);
	ioग_लिखो32(XGENE_ENET_WR_CMD, cmd);

	जबतक (!(करोne = ioपढ़ो32(cmd_करोne)) && रुको--)
		udelay(1);

	अगर (!करोne)
		netdev_err(ndev, "mac write failed, addr: %04x data: %08x\n",
			   wr_addr, wr_data);

	ioग_लिखो32(0, cmd);
	spin_unlock(&pdata->mac_lock);
पूर्ण

अटल व्योम xgene_enet_rd_csr(काष्ठा xgene_enet_pdata *pdata,
			      u32 offset, u32 *val)
अणु
	व्योम __iomem *addr = pdata->eth_csr_addr + offset;

	*val = ioपढ़ो32(addr);
पूर्ण

अटल व्योम xgene_enet_rd_diag_csr(काष्ठा xgene_enet_pdata *pdata,
				   u32 offset, u32 *val)
अणु
	व्योम __iomem *addr = pdata->eth_diag_csr_addr + offset;

	*val = ioपढ़ो32(addr);
पूर्ण

अटल व्योम xgene_enet_rd_mcx_csr(काष्ठा xgene_enet_pdata *pdata,
				  u32 offset, u32 *val)
अणु
	व्योम __iomem *addr = pdata->mcx_mac_csr_addr + offset;

	*val = ioपढ़ो32(addr);
पूर्ण

u32 xgene_enet_rd_mac(काष्ठा xgene_enet_pdata *pdata, u32 rd_addr)
अणु
	व्योम __iomem *addr, *rd, *cmd, *cmd_करोne;
	काष्ठा net_device *ndev = pdata->ndev;
	u32 करोne, rd_data;
	u8 रुको = 10;

	अगर (pdata->mdio_driver && ndev->phydev &&
	    phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode)) अणु
		काष्ठा mii_bus *bus = ndev->phydev->mdio.bus;

		वापस xgene_mdio_rd_mac(bus->priv, rd_addr);
	पूर्ण

	addr = pdata->mcx_mac_addr + MAC_ADDR_REG_OFFSET;
	rd = pdata->mcx_mac_addr + MAC_READ_REG_OFFSET;
	cmd = pdata->mcx_mac_addr + MAC_COMMAND_REG_OFFSET;
	cmd_करोne = pdata->mcx_mac_addr + MAC_COMMAND_DONE_REG_OFFSET;

	spin_lock(&pdata->mac_lock);
	ioग_लिखो32(rd_addr, addr);
	ioग_लिखो32(XGENE_ENET_RD_CMD, cmd);

	जबतक (!(करोne = ioपढ़ो32(cmd_करोne)) && रुको--)
		udelay(1);

	अगर (!करोne)
		netdev_err(ndev, "mac read failed, addr: %04x\n", rd_addr);

	rd_data = ioपढ़ो32(rd);
	ioग_लिखो32(0, cmd);
	spin_unlock(&pdata->mac_lock);

	वापस rd_data;
पूर्ण

u32 xgene_enet_rd_stat(काष्ठा xgene_enet_pdata *pdata, u32 rd_addr)
अणु
	व्योम __iomem *addr, *rd, *cmd, *cmd_करोne;
	u32 करोne, rd_data;
	u8 रुको = 10;

	addr = pdata->mcx_stats_addr + STAT_ADDR_REG_OFFSET;
	rd = pdata->mcx_stats_addr + STAT_READ_REG_OFFSET;
	cmd = pdata->mcx_stats_addr + STAT_COMMAND_REG_OFFSET;
	cmd_करोne = pdata->mcx_stats_addr + STAT_COMMAND_DONE_REG_OFFSET;

	spin_lock(&pdata->stats_lock);
	ioग_लिखो32(rd_addr, addr);
	ioग_लिखो32(XGENE_ENET_RD_CMD, cmd);

	जबतक (!(करोne = ioपढ़ो32(cmd_करोne)) && रुको--)
		udelay(1);

	अगर (!करोne)
		netdev_err(pdata->ndev, "mac stats read failed, addr: %04x\n",
			   rd_addr);

	rd_data = ioपढ़ो32(rd);
	ioग_लिखो32(0, cmd);
	spin_unlock(&pdata->stats_lock);

	वापस rd_data;
पूर्ण

अटल व्योम xgene_gmac_set_mac_addr(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 addr0, addr1;
	u8 *dev_addr = pdata->ndev->dev_addr;

	addr0 = (dev_addr[3] << 24) | (dev_addr[2] << 16) |
		(dev_addr[1] << 8) | dev_addr[0];
	addr1 = (dev_addr[5] << 24) | (dev_addr[4] << 16);

	xgene_enet_wr_mac(pdata, STATION_ADDR0_ADDR, addr0);
	xgene_enet_wr_mac(pdata, STATION_ADDR1_ADDR, addr1);
पूर्ण

अटल पूर्णांक xgene_enet_ecc_init(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा net_device *ndev = pdata->ndev;
	u32 data;
	u8 रुको = 10;

	xgene_enet_wr_diag_csr(pdata, ENET_CFG_MEM_RAM_SHUTDOWN_ADDR, 0x0);
	करो अणु
		usleep_range(100, 110);
		xgene_enet_rd_diag_csr(pdata, ENET_BLOCK_MEM_RDY_ADDR, &data);
	पूर्ण जबतक ((data != 0xffffffff) && रुको--);

	अगर (data != 0xffffffff) अणु
		netdev_err(ndev, "Failed to release memory from shutdown\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgene_gmac_reset(काष्ठा xgene_enet_pdata *pdata)
अणु
	xgene_enet_wr_mac(pdata, MAC_CONFIG_1_ADDR, SOFT_RESET1);
	xgene_enet_wr_mac(pdata, MAC_CONFIG_1_ADDR, 0);
पूर्ण

अटल व्योम xgene_enet_configure_घड़ी(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;

	अगर (dev->of_node) अणु
		काष्ठा clk *parent = clk_get_parent(pdata->clk);

		चयन (pdata->phy_speed) अणु
		हाल SPEED_10:
			clk_set_rate(parent, 2500000);
			अवरोध;
		हाल SPEED_100:
			clk_set_rate(parent, 25000000);
			अवरोध;
		शेष:
			clk_set_rate(parent, 125000000);
			अवरोध;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_ACPI
	अन्यथा अणु
		चयन (pdata->phy_speed) अणु
		हाल SPEED_10:
			acpi_evaluate_object(ACPI_HANDLE(dev),
					     "S10", शून्य, शून्य);
			अवरोध;
		हाल SPEED_100:
			acpi_evaluate_object(ACPI_HANDLE(dev),
					     "S100", शून्य, शून्य);
			अवरोध;
		शेष:
			acpi_evaluate_object(ACPI_HANDLE(dev),
					     "S1G", शून्य, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम xgene_gmac_set_speed(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 icm0, icm2, mc2;
	u32 पूर्णांकf_ctl, rgmii, value;

	xgene_enet_rd_mcx_csr(pdata, ICM_CONFIG0_REG_0_ADDR, &icm0);
	xgene_enet_rd_mcx_csr(pdata, ICM_CONFIG2_REG_0_ADDR, &icm2);
	mc2 = xgene_enet_rd_mac(pdata, MAC_CONFIG_2_ADDR);
	पूर्णांकf_ctl = xgene_enet_rd_mac(pdata, INTERFACE_CONTROL_ADDR);
	xgene_enet_rd_csr(pdata, RGMII_REG_0_ADDR, &rgmii);

	चयन (pdata->phy_speed) अणु
	हाल SPEED_10:
		ENET_INTERFACE_MODE2_SET(&mc2, 1);
		पूर्णांकf_ctl &= ~(ENET_LHD_MODE | ENET_GHD_MODE);
		CFG_MACMODE_SET(&icm0, 0);
		CFG_WAITASYNCRD_SET(&icm2, 500);
		rgmii &= ~CFG_SPEED_1250;
		अवरोध;
	हाल SPEED_100:
		ENET_INTERFACE_MODE2_SET(&mc2, 1);
		पूर्णांकf_ctl &= ~ENET_GHD_MODE;
		पूर्णांकf_ctl |= ENET_LHD_MODE;
		CFG_MACMODE_SET(&icm0, 1);
		CFG_WAITASYNCRD_SET(&icm2, 80);
		rgmii &= ~CFG_SPEED_1250;
		अवरोध;
	शेष:
		ENET_INTERFACE_MODE2_SET(&mc2, 2);
		पूर्णांकf_ctl &= ~ENET_LHD_MODE;
		पूर्णांकf_ctl |= ENET_GHD_MODE;
		CFG_MACMODE_SET(&icm0, 2);
		CFG_WAITASYNCRD_SET(&icm2, 0);
		CFG_TXCLK_MUXSEL0_SET(&rgmii, pdata->tx_delay);
		CFG_RXCLK_MUXSEL0_SET(&rgmii, pdata->rx_delay);
		rgmii |= CFG_SPEED_1250;

		xgene_enet_rd_csr(pdata, DEBUG_REG_ADDR, &value);
		value |= CFG_BYPASS_UNISEC_TX | CFG_BYPASS_UNISEC_RX;
		xgene_enet_wr_csr(pdata, DEBUG_REG_ADDR, value);
		अवरोध;
	पूर्ण

	mc2 |= FULL_DUPLEX2 | PAD_CRC | LENGTH_CHK;
	xgene_enet_wr_mac(pdata, MAC_CONFIG_2_ADDR, mc2);
	xgene_enet_wr_mac(pdata, INTERFACE_CONTROL_ADDR, पूर्णांकf_ctl);
	xgene_enet_wr_csr(pdata, RGMII_REG_0_ADDR, rgmii);
	xgene_enet_configure_घड़ी(pdata);

	xgene_enet_wr_mcx_csr(pdata, ICM_CONFIG0_REG_0_ADDR, icm0);
	xgene_enet_wr_mcx_csr(pdata, ICM_CONFIG2_REG_0_ADDR, icm2);
पूर्ण

अटल व्योम xgene_enet_set_frame_size(काष्ठा xgene_enet_pdata *pdata, पूर्णांक size)
अणु
	xgene_enet_wr_mac(pdata, MAX_FRAME_LEN_ADDR, size);
पूर्ण

अटल व्योम xgene_gmac_enable_tx_छोड़ो(काष्ठा xgene_enet_pdata *pdata,
				       bool enable)
अणु
	u32 data;

	xgene_enet_rd_mcx_csr(pdata, CSR_ECM_CFG_0_ADDR, &data);

	अगर (enable)
		data |= MULTI_DPF_AUTOCTRL | PAUSE_XON_EN;
	अन्यथा
		data &= ~(MULTI_DPF_AUTOCTRL | PAUSE_XON_EN);

	xgene_enet_wr_mcx_csr(pdata, CSR_ECM_CFG_0_ADDR, data);
पूर्ण

अटल व्योम xgene_gmac_flowctl_tx(काष्ठा xgene_enet_pdata *pdata, bool enable)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, MAC_CONFIG_1_ADDR);

	अगर (enable)
		data |= TX_FLOW_EN;
	अन्यथा
		data &= ~TX_FLOW_EN;

	xgene_enet_wr_mac(pdata, MAC_CONFIG_1_ADDR, data);

	pdata->mac_ops->enable_tx_छोड़ो(pdata, enable);
पूर्ण

अटल व्योम xgene_gmac_flowctl_rx(काष्ठा xgene_enet_pdata *pdata, bool enable)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, MAC_CONFIG_1_ADDR);

	अगर (enable)
		data |= RX_FLOW_EN;
	अन्यथा
		data &= ~RX_FLOW_EN;

	xgene_enet_wr_mac(pdata, MAC_CONFIG_1_ADDR, data);
पूर्ण

अटल व्योम xgene_gmac_init(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 value;

	अगर (!pdata->mdio_driver)
		xgene_gmac_reset(pdata);

	xgene_gmac_set_speed(pdata);
	xgene_gmac_set_mac_addr(pdata);

	/* Adjust MDC घड़ी frequency */
	value = xgene_enet_rd_mac(pdata, MII_MGMT_CONFIG_ADDR);
	MGMT_CLOCK_SEL_SET(&value, 7);
	xgene_enet_wr_mac(pdata, MII_MGMT_CONFIG_ADDR, value);

	/* Enable drop अगर bufpool not available */
	xgene_enet_rd_csr(pdata, RSIF_CONFIG_REG_ADDR, &value);
	value |= CFG_RSIF_FPBUFF_TIMEOUT_EN;
	xgene_enet_wr_csr(pdata, RSIF_CONFIG_REG_ADDR, value);

	/* Rtype should be copied from FP */
	xgene_enet_wr_csr(pdata, RSIF_RAM_DBG_REG0_ADDR, 0);

	/* Configure HW छोड़ो frame generation */
	xgene_enet_rd_mcx_csr(pdata, CSR_MULTI_DPF0_ADDR, &value);
	value = (DEF_QUANTA << 16) | (value & 0xFFFF);
	xgene_enet_wr_mcx_csr(pdata, CSR_MULTI_DPF0_ADDR, value);

	xgene_enet_wr_csr(pdata, RXBUF_PAUSE_THRESH, DEF_PAUSE_THRES);
	xgene_enet_wr_csr(pdata, RXBUF_PAUSE_OFF_THRESH, DEF_PAUSE_OFF_THRES);

	xgene_gmac_flowctl_tx(pdata, pdata->tx_छोड़ो);
	xgene_gmac_flowctl_rx(pdata, pdata->rx_छोड़ो);

	/* Rx-Tx traffic resume */
	xgene_enet_wr_csr(pdata, CFG_LINK_AGGR_RESUME_0_ADDR, TX_PORT0);

	xgene_enet_rd_mcx_csr(pdata, RX_DV_GATE_REG_0_ADDR, &value);
	value &= ~TX_DV_GATE_EN0;
	value &= ~RX_DV_GATE_EN0;
	value |= RESUME_RX0;
	xgene_enet_wr_mcx_csr(pdata, RX_DV_GATE_REG_0_ADDR, value);

	xgene_enet_wr_csr(pdata, CFG_BYPASS_ADDR, RESUME_TX);
पूर्ण

अटल व्योम xgene_gmac_get_drop_cnt(काष्ठा xgene_enet_pdata *pdata,
				    u32 *rx, u32 *tx)
अणु
	u32 count;

	xgene_enet_rd_mcx_csr(pdata, ICM_ECM_DROP_COUNT_REG0_ADDR, &count);
	*rx = ICM_DROP_COUNT(count);
	*tx = ECM_DROP_COUNT(count);
	/* Errata: 10GE_4 - Fix ICM_ECM_DROP_COUNT not clear-on-पढ़ो */
	xgene_enet_rd_mcx_csr(pdata, ECM_CONFIG0_REG_0_ADDR, &count);
पूर्ण

अटल व्योम xgene_enet_config_ring_अगर_assoc(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 val = 0xffffffff;

	xgene_enet_wr_ring_अगर(pdata, ENET_CFGSSQMIWQASSOC_ADDR, val);
	xgene_enet_wr_ring_अगर(pdata, ENET_CFGSSQMIFPQASSOC_ADDR, val);
	xgene_enet_wr_ring_अगर(pdata, ENET_CFGSSQMIQMLITEWQASSOC_ADDR, val);
	xgene_enet_wr_ring_अगर(pdata, ENET_CFGSSQMIQMLITEFPQASSOC_ADDR, val);
पूर्ण

अटल व्योम xgene_enet_cle_bypass(काष्ठा xgene_enet_pdata *pdata,
				  u32 dst_ring_num, u16 bufpool_id,
				  u16 nxtbufpool_id)
अणु
	u32 cb;
	u32 fpsel, nxtfpsel;

	fpsel = xgene_enet_get_fpsel(bufpool_id);
	nxtfpsel = xgene_enet_get_fpsel(nxtbufpool_id);

	xgene_enet_rd_csr(pdata, CLE_BYPASS_REG0_0_ADDR, &cb);
	cb |= CFG_CLE_BYPASS_EN0;
	CFG_CLE_IP_PROTOCOL0_SET(&cb, 3);
	CFG_CLE_IP_HDR_LEN_SET(&cb, 0);
	xgene_enet_wr_csr(pdata, CLE_BYPASS_REG0_0_ADDR, cb);

	xgene_enet_rd_csr(pdata, CLE_BYPASS_REG1_0_ADDR, &cb);
	CFG_CLE_DSTQID0_SET(&cb, dst_ring_num);
	CFG_CLE_FPSEL0_SET(&cb, fpsel);
	CFG_CLE_NXTFPSEL0_SET(&cb, nxtfpsel);
	xgene_enet_wr_csr(pdata, CLE_BYPASS_REG1_0_ADDR, cb);
पूर्ण

अटल व्योम xgene_gmac_rx_enable(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, MAC_CONFIG_1_ADDR);
	xgene_enet_wr_mac(pdata, MAC_CONFIG_1_ADDR, data | RX_EN);
पूर्ण

अटल व्योम xgene_gmac_tx_enable(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, MAC_CONFIG_1_ADDR);
	xgene_enet_wr_mac(pdata, MAC_CONFIG_1_ADDR, data | TX_EN);
पूर्ण

अटल व्योम xgene_gmac_rx_disable(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, MAC_CONFIG_1_ADDR);
	xgene_enet_wr_mac(pdata, MAC_CONFIG_1_ADDR, data & ~RX_EN);
पूर्ण

अटल व्योम xgene_gmac_tx_disable(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, MAC_CONFIG_1_ADDR);
	xgene_enet_wr_mac(pdata, MAC_CONFIG_1_ADDR, data & ~TX_EN);
पूर्ण

bool xgene_ring_mgr_init(काष्ठा xgene_enet_pdata *p)
अणु
	अगर (!ioपढ़ो32(p->ring_csr_addr + CLKEN_ADDR))
		वापस false;

	अगर (ioपढ़ो32(p->ring_csr_addr + SRST_ADDR))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक xgene_enet_reset(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;

	अगर (!xgene_ring_mgr_init(pdata))
		वापस -ENODEV;

	अगर (pdata->mdio_driver) अणु
		xgene_enet_config_ring_अगर_assoc(pdata);
		वापस 0;
	पूर्ण

	अगर (dev->of_node) अणु
		clk_prepare_enable(pdata->clk);
		udelay(5);
		clk_disable_unprepare(pdata->clk);
		udelay(5);
		clk_prepare_enable(pdata->clk);
		udelay(5);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_ACPI
		acpi_status status;

		status = acpi_evaluate_object(ACPI_HANDLE(&pdata->pdev->dev),
					      "_RST", शून्य, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_evaluate_object(ACPI_HANDLE(&pdata->pdev->dev),
					     "_INI", शून्य, शून्य);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	xgene_enet_ecc_init(pdata);
	xgene_enet_config_ring_अगर_assoc(pdata);

	वापस 0;
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

अटल व्योम xgene_gport_shutकरोwn(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;

	अगर (dev->of_node) अणु
		अगर (!IS_ERR(pdata->clk))
			clk_disable_unprepare(pdata->clk);
	पूर्ण
पूर्ण

अटल u32 xgene_enet_flowctrl_cfg(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;
	u16 lcladv, rmtadv = 0;
	u32 rx_छोड़ो, tx_छोड़ो;
	u8 flowctl = 0;

	अगर (!phydev->duplex || !pdata->छोड़ो_स्वतःneg)
		वापस 0;

	अगर (pdata->tx_छोड़ो)
		flowctl |= FLOW_CTRL_TX;

	अगर (pdata->rx_छोड़ो)
		flowctl |= FLOW_CTRL_RX;

	lcladv = mii_advertise_flowctrl(flowctl);

	अगर (phydev->छोड़ो)
		rmtadv = LPA_PAUSE_CAP;

	अगर (phydev->asym_छोड़ो)
		rmtadv |= LPA_PAUSE_ASYM;

	flowctl = mii_resolve_flowctrl_fdx(lcladv, rmtadv);
	tx_छोड़ो = !!(flowctl & FLOW_CTRL_TX);
	rx_छोड़ो = !!(flowctl & FLOW_CTRL_RX);

	अगर (tx_छोड़ो != pdata->tx_छोड़ो) अणु
		pdata->tx_छोड़ो = tx_छोड़ो;
		pdata->mac_ops->flowctl_tx(pdata, pdata->tx_छोड़ो);
	पूर्ण

	अगर (rx_छोड़ो != pdata->rx_छोड़ो) अणु
		pdata->rx_छोड़ो = rx_छोड़ो;
		pdata->mac_ops->flowctl_rx(pdata, pdata->rx_छोड़ो);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgene_enet_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	स्थिर काष्ठा xgene_mac_ops *mac_ops = pdata->mac_ops;
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (phydev->link) अणु
		अगर (pdata->phy_speed != phydev->speed) अणु
			pdata->phy_speed = phydev->speed;
			mac_ops->set_speed(pdata);
			mac_ops->rx_enable(pdata);
			mac_ops->tx_enable(pdata);
			phy_prपूर्णांक_status(phydev);
		पूर्ण

		xgene_enet_flowctrl_cfg(ndev);
	पूर्ण अन्यथा अणु
		mac_ops->rx_disable(pdata);
		mac_ops->tx_disable(pdata);
		pdata->phy_speed = SPEED_UNKNOWN;
		phy_prपूर्णांक_status(phydev);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल काष्ठा acpi_device *acpi_phy_find_device(काष्ठा device *dev)
अणु
	काष्ठा fwnode_reference_args args;
	काष्ठा fwnode_handle *fw_node;
	पूर्णांक status;

	fw_node = acpi_fwnode_handle(ACPI_COMPANION(dev));
	status = acpi_node_get_property_reference(fw_node, "phy-handle", 0,
						  &args);
	अगर (ACPI_FAILURE(status) || !is_acpi_device_node(args.fwnode)) अणु
		dev_dbg(dev, "No matching phy in ACPI table\n");
		वापस शून्य;
	पूर्ण

	वापस to_acpi_device_node(args.fwnode);
पूर्ण
#पूर्ण_अगर

पूर्णांक xgene_enet_phy_connect(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा device_node *np;
	काष्ठा phy_device *phy_dev;
	काष्ठा device *dev = &pdata->pdev->dev;
	पूर्णांक i;

	अगर (dev->of_node) अणु
		क्रम (i = 0 ; i < 2; i++) अणु
			np = of_parse_phandle(dev->of_node, "phy-handle", i);
			phy_dev = of_phy_connect(ndev, np,
						 &xgene_enet_adjust_link,
						 0, pdata->phy_mode);
			of_node_put(np);
			अगर (phy_dev)
				अवरोध;
		पूर्ण

		अगर (!phy_dev) अणु
			netdev_err(ndev, "Could not connect to PHY\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_ACPI
		काष्ठा acpi_device *adev = acpi_phy_find_device(dev);
		अगर (adev)
			phy_dev = adev->driver_data;
		अन्यथा
			phy_dev = शून्य;

		अगर (!phy_dev ||
		    phy_connect_direct(ndev, phy_dev, &xgene_enet_adjust_link,
				       pdata->phy_mode)) अणु
			netdev_err(ndev, "Could not connect to PHY\n");
			वापस  -ENODEV;
		पूर्ण
#अन्यथा
		वापस -ENODEV;
#पूर्ण_अगर
	पूर्ण

	pdata->phy_speed = SPEED_UNKNOWN;
	phy_हटाओ_link_mode(phy_dev, ETHTOOL_LINK_MODE_10baseT_Half_BIT);
	phy_हटाओ_link_mode(phy_dev, ETHTOOL_LINK_MODE_100baseT_Half_BIT);
	phy_हटाओ_link_mode(phy_dev, ETHTOOL_LINK_MODE_1000baseT_Half_BIT);
	phy_support_asym_छोड़ो(phy_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_mdiobus_रेजिस्टर(काष्ठा xgene_enet_pdata *pdata,
				  काष्ठा mii_bus *mdio)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा net_device *ndev = pdata->ndev;
	काष्ठा phy_device *phy;
	काष्ठा device_node *child_np;
	काष्ठा device_node *mdio_np = शून्य;
	u32 phy_addr;
	पूर्णांक ret;

	अगर (dev->of_node) अणु
		क्रम_each_child_of_node(dev->of_node, child_np) अणु
			अगर (of_device_is_compatible(child_np,
						    "apm,xgene-mdio")) अणु
				mdio_np = child_np;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!mdio_np) अणु
			netdev_dbg(ndev, "No mdio node in the dts\n");
			वापस -ENXIO;
		पूर्ण

		वापस of_mdiobus_रेजिस्टर(mdio, mdio_np);
	पूर्ण

	/* Mask out all PHYs from स्वतः probing. */
	mdio->phy_mask = ~0;

	/* Register the MDIO bus */
	ret = mdiobus_रेजिस्टर(mdio);
	अगर (ret)
		वापस ret;

	ret = device_property_पढ़ो_u32(dev, "phy-channel", &phy_addr);
	अगर (ret)
		ret = device_property_पढ़ो_u32(dev, "phy-addr", &phy_addr);
	अगर (ret)
		वापस -EINVAL;

	phy = xgene_enet_phy_रेजिस्टर(mdio, phy_addr);
	अगर (!phy)
		वापस -EIO;

	वापस ret;
पूर्ण

पूर्णांक xgene_enet_mdio_config(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा net_device *ndev = pdata->ndev;
	काष्ठा mii_bus *mdio_bus;
	पूर्णांक ret;

	mdio_bus = mdiobus_alloc();
	अगर (!mdio_bus)
		वापस -ENOMEM;

	mdio_bus->name = "APM X-Gene MDIO bus";
	mdio_bus->पढ़ो = xgene_mdio_rgmii_पढ़ो;
	mdio_bus->ग_लिखो = xgene_mdio_rgmii_ग_लिखो;
	snम_लिखो(mdio_bus->id, MII_BUS_ID_SIZE, "%s-%s", "xgene-mii",
		 ndev->name);

	mdio_bus->priv = (व्योम __क्रमce *)pdata->mcx_mac_addr;
	mdio_bus->parent = &pdata->pdev->dev;

	ret = xgene_mdiobus_रेजिस्टर(pdata, mdio_bus);
	अगर (ret) अणु
		netdev_err(ndev, "Failed to register MDIO bus\n");
		mdiobus_मुक्त(mdio_bus);
		वापस ret;
	पूर्ण
	pdata->mdio_bus = mdio_bus;

	ret = xgene_enet_phy_connect(ndev);
	अगर (ret)
		xgene_enet_mdio_हटाओ(pdata);

	वापस ret;
पूर्ण

व्योम xgene_enet_phy_disconnect(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा net_device *ndev = pdata->ndev;

	अगर (ndev->phydev)
		phy_disconnect(ndev->phydev);
पूर्ण

व्योम xgene_enet_mdio_हटाओ(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा net_device *ndev = pdata->ndev;

	अगर (ndev->phydev)
		phy_disconnect(ndev->phydev);

	mdiobus_unरेजिस्टर(pdata->mdio_bus);
	mdiobus_मुक्त(pdata->mdio_bus);
	pdata->mdio_bus = शून्य;
पूर्ण

स्थिर काष्ठा xgene_mac_ops xgene_gmac_ops = अणु
	.init = xgene_gmac_init,
	.reset = xgene_gmac_reset,
	.rx_enable = xgene_gmac_rx_enable,
	.tx_enable = xgene_gmac_tx_enable,
	.rx_disable = xgene_gmac_rx_disable,
	.tx_disable = xgene_gmac_tx_disable,
	.get_drop_cnt = xgene_gmac_get_drop_cnt,
	.set_speed = xgene_gmac_set_speed,
	.set_mac_addr = xgene_gmac_set_mac_addr,
	.set_framesize = xgene_enet_set_frame_size,
	.enable_tx_छोड़ो = xgene_gmac_enable_tx_छोड़ो,
	.flowctl_tx     = xgene_gmac_flowctl_tx,
	.flowctl_rx     = xgene_gmac_flowctl_rx,
पूर्ण;

स्थिर काष्ठा xgene_port_ops xgene_gport_ops = अणु
	.reset = xgene_enet_reset,
	.clear = xgene_enet_clear,
	.cle_bypass = xgene_enet_cle_bypass,
	.shutकरोwn = xgene_gport_shutकरोwn,
पूर्ण;

काष्ठा xgene_ring_ops xgene_ring1_ops = अणु
	.num_ring_config = NUM_RING_CONFIG,
	.num_ring_id_shअगरt = 6,
	.setup = xgene_enet_setup_ring,
	.clear = xgene_enet_clear_ring,
	.wr_cmd = xgene_enet_wr_cmd,
	.len = xgene_enet_ring_len,
पूर्ण;
