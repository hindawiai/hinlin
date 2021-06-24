<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 *	    Keyur Chudgar <kchudgar@apm.com>
 */

#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpपन.स>
#समावेश "xgene_enet_main.h"
#समावेश "xgene_enet_hw.h"
#समावेश "xgene_enet_xgmac.h"

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

अटल bool xgene_enet_wr_indirect(व्योम __iomem *addr, व्योम __iomem *wr,
				   व्योम __iomem *cmd, व्योम __iomem *cmd_करोne,
				   u32 wr_addr, u32 wr_data)
अणु
	u32 करोne;
	u8 रुको = 10;

	ioग_लिखो32(wr_addr, addr);
	ioग_लिखो32(wr_data, wr);
	ioग_लिखो32(XGENE_ENET_WR_CMD, cmd);

	/* रुको क्रम ग_लिखो command to complete */
	जबतक (!(करोne = ioपढ़ो32(cmd_करोne)) && रुको--)
		udelay(1);

	अगर (!करोne)
		वापस false;

	ioग_लिखो32(0, cmd);

	वापस true;
पूर्ण

अटल व्योम xgene_enet_wr_pcs(काष्ठा xgene_enet_pdata *pdata,
			      u32 wr_addr, u32 wr_data)
अणु
	व्योम __iomem *addr, *wr, *cmd, *cmd_करोne;

	addr = pdata->pcs_addr + PCS_ADDR_REG_OFFSET;
	wr = pdata->pcs_addr + PCS_WRITE_REG_OFFSET;
	cmd = pdata->pcs_addr + PCS_COMMAND_REG_OFFSET;
	cmd_करोne = pdata->pcs_addr + PCS_COMMAND_DONE_REG_OFFSET;

	अगर (!xgene_enet_wr_indirect(addr, wr, cmd, cmd_करोne, wr_addr, wr_data))
		netdev_err(pdata->ndev, "PCS write failed, addr: %04x\n",
			   wr_addr);
पूर्ण

अटल व्योम xgene_enet_wr_axg_csr(काष्ठा xgene_enet_pdata *pdata,
				  u32 offset, u32 val)
अणु
	व्योम __iomem *addr = pdata->mcx_mac_csr_addr + offset;

	ioग_लिखो32(val, addr);
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

अटल bool xgene_enet_rd_indirect(व्योम __iomem *addr, व्योम __iomem *rd,
				   व्योम __iomem *cmd, व्योम __iomem *cmd_करोne,
				   u32 rd_addr, u32 *rd_data)
अणु
	u32 करोne;
	u8 रुको = 10;

	ioग_लिखो32(rd_addr, addr);
	ioग_लिखो32(XGENE_ENET_RD_CMD, cmd);

	/* रुको क्रम पढ़ो command to complete */
	जबतक (!(करोne = ioपढ़ो32(cmd_करोne)) && रुको--)
		udelay(1);

	अगर (!करोne)
		वापस false;

	*rd_data = ioपढ़ो32(rd);
	ioग_लिखो32(0, cmd);

	वापस true;
पूर्ण

अटल bool xgene_enet_rd_pcs(काष्ठा xgene_enet_pdata *pdata,
			      u32 rd_addr, u32 *rd_data)
अणु
	व्योम __iomem *addr, *rd, *cmd, *cmd_करोne;
	bool success;

	addr = pdata->pcs_addr + PCS_ADDR_REG_OFFSET;
	rd = pdata->pcs_addr + PCS_READ_REG_OFFSET;
	cmd = pdata->pcs_addr + PCS_COMMAND_REG_OFFSET;
	cmd_करोne = pdata->pcs_addr + PCS_COMMAND_DONE_REG_OFFSET;

	success = xgene_enet_rd_indirect(addr, rd, cmd, cmd_करोne, rd_addr, rd_data);
	अगर (!success)
		netdev_err(pdata->ndev, "PCS read failed, addr: %04x\n",
			   rd_addr);

	वापस success;
पूर्ण

अटल व्योम xgene_enet_rd_axg_csr(काष्ठा xgene_enet_pdata *pdata,
				  u32 offset, u32 *val)
अणु
	व्योम __iomem *addr = pdata->mcx_mac_csr_addr + offset;

	*val = ioपढ़ो32(addr);
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

अटल व्योम xgene_xgmac_get_drop_cnt(काष्ठा xgene_enet_pdata *pdata,
				     u32 *rx, u32 *tx)
अणु
	u32 count;

	xgene_enet_rd_axg_csr(pdata, XGENET_ICM_ECM_DROP_COUNT_REG0, &count);
	*rx = ICM_DROP_COUNT(count);
	*tx = ECM_DROP_COUNT(count);
	/* Errata: 10GE_4 - ICM_ECM_DROP_COUNT not clear-on-पढ़ो */
	xgene_enet_rd_axg_csr(pdata, XGENET_ECM_CONFIG0_REG_0, &count);
पूर्ण

अटल व्योम xgene_enet_config_ring_अगर_assoc(काष्ठा xgene_enet_pdata *pdata)
अणु
	xgene_enet_wr_ring_अगर(pdata, ENET_CFGSSQMIWQASSOC_ADDR, 0);
	xgene_enet_wr_ring_अगर(pdata, ENET_CFGSSQMIFPQASSOC_ADDR, 0);
	xgene_enet_wr_ring_अगर(pdata, ENET_CFGSSQMIQMLITEWQASSOC_ADDR, 0);
	xgene_enet_wr_ring_अगर(pdata, ENET_CFGSSQMIQMLITEFPQASSOC_ADDR, 0);
पूर्ण

अटल व्योम xgene_xgmac_reset(काष्ठा xgene_enet_pdata *pdata)
अणु
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_0, HSTMACRST);
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_0, 0);
पूर्ण

अटल व्योम xgene_pcs_reset(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	अगर (!xgene_enet_rd_pcs(pdata, PCS_CONTROL_1, &data))
		वापस;

	xgene_enet_wr_pcs(pdata, PCS_CONTROL_1, data | PCS_CTRL_PCS_RST);
	xgene_enet_wr_pcs(pdata, PCS_CONTROL_1, data & ~PCS_CTRL_PCS_RST);
पूर्ण

अटल व्योम xgene_xgmac_set_mac_addr(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 addr0, addr1;
	u8 *dev_addr = pdata->ndev->dev_addr;

	addr0 = (dev_addr[3] << 24) | (dev_addr[2] << 16) |
		(dev_addr[1] << 8) | dev_addr[0];
	addr1 = (dev_addr[5] << 24) | (dev_addr[4] << 16);

	xgene_enet_wr_mac(pdata, HSTMACADR_LSW_ADDR, addr0);
	xgene_enet_wr_mac(pdata, HSTMACADR_MSW_ADDR, addr1);
पूर्ण

अटल व्योम xgene_xgmac_set_mss(काष्ठा xgene_enet_pdata *pdata,
				u16 mss, u8 index)
अणु
	u8 offset;
	u32 data;

	offset = (index < 2) ? 0 : 4;
	xgene_enet_rd_csr(pdata, XG_TSIF_MSS_REG0_ADDR + offset, &data);

	अगर (!(index & 0x1))
		data = SET_VAL(TSO_MSS1, data >> TSO_MSS1_POS) |
			SET_VAL(TSO_MSS0, mss);
	अन्यथा
		data = SET_VAL(TSO_MSS1, mss) | SET_VAL(TSO_MSS0, data);

	xgene_enet_wr_csr(pdata, XG_TSIF_MSS_REG0_ADDR + offset, data);
पूर्ण

अटल व्योम xgene_xgmac_set_frame_size(काष्ठा xgene_enet_pdata *pdata, पूर्णांक size)
अणु
	xgene_enet_wr_mac(pdata, HSTMAXFRAME_LENGTH_ADDR,
			  ((((size + 2) >> 2) << 16) | size));
पूर्ण

अटल u32 xgene_enet_link_status(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	xgene_enet_rd_csr(pdata, XG_LINK_STATUS_ADDR, &data);

	वापस data;
पूर्ण

अटल व्योम xgene_xgmac_enable_tx_छोड़ो(काष्ठा xgene_enet_pdata *pdata,
					bool enable)
अणु
	u32 data;

	xgene_enet_rd_axg_csr(pdata, XGENET_CSR_ECM_CFG_0_ADDR, &data);

	अगर (enable)
		data |= MULTI_DPF_AUTOCTRL | PAUSE_XON_EN;
	अन्यथा
		data &= ~(MULTI_DPF_AUTOCTRL | PAUSE_XON_EN);

	xgene_enet_wr_axg_csr(pdata, XGENET_CSR_ECM_CFG_0_ADDR, data);
पूर्ण

अटल व्योम xgene_xgmac_flowctl_tx(काष्ठा xgene_enet_pdata *pdata, bool enable)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);

	अगर (enable)
		data |= HSTTCTLEN;
	अन्यथा
		data &= ~HSTTCTLEN;

	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data);

	pdata->mac_ops->enable_tx_छोड़ो(pdata, enable);
पूर्ण

अटल व्योम xgene_xgmac_flowctl_rx(काष्ठा xgene_enet_pdata *pdata, bool enable)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);

	अगर (enable)
		data |= HSTRCTLEN;
	अन्यथा
		data &= ~HSTRCTLEN;

	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data);
पूर्ण

अटल व्योम xgene_xgmac_init(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	xgene_xgmac_reset(pdata);

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);
	data |= HSTPPEN;
	data &= ~HSTLENCHK;
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data);

	xgene_xgmac_set_mac_addr(pdata);

	xgene_enet_rd_csr(pdata, XG_RSIF_CONFIG_REG_ADDR, &data);
	data |= CFG_RSIF_FPBUFF_TIMEOUT_EN;
	/* Errata 10GE_1 - FIFO threshold शेष value incorrect */
	RSIF_CLE_BUFF_THRESH_SET(&data, XG_RSIF_CLE_BUFF_THRESH);
	xgene_enet_wr_csr(pdata, XG_RSIF_CONFIG_REG_ADDR, data);

	/* Errata 10GE_1 - FIFO threshold शेष value incorrect */
	xgene_enet_rd_csr(pdata, XG_RSIF_CONFIG1_REG_ADDR, &data);
	RSIF_PLC_CLE_BUFF_THRESH_SET(&data, XG_RSIF_PLC_CLE_BUFF_THRESH);
	xgene_enet_wr_csr(pdata, XG_RSIF_CONFIG1_REG_ADDR, data);

	xgene_enet_rd_csr(pdata, XG_ENET_SPARE_CFG_REG_ADDR, &data);
	data |= BIT(12);
	xgene_enet_wr_csr(pdata, XG_ENET_SPARE_CFG_REG_ADDR, data);
	xgene_enet_wr_csr(pdata, XG_ENET_SPARE_CFG_REG_1_ADDR, 0x82);
	xgene_enet_wr_csr(pdata, XGENET_RX_DV_GATE_REG_0_ADDR, 0);
	xgene_enet_wr_csr(pdata, XG_CFG_BYPASS_ADDR, RESUME_TX);

	/* Configure HW छोड़ो frame generation */
	xgene_enet_rd_axg_csr(pdata, XGENET_CSR_MULTI_DPF0_ADDR, &data);
	data = (DEF_QUANTA << 16) | (data & 0xFFFF);
	xgene_enet_wr_axg_csr(pdata, XGENET_CSR_MULTI_DPF0_ADDR, data);

	अगर (pdata->enet_id != XGENE_ENET1) अणु
		xgene_enet_rd_axg_csr(pdata, XGENET_CSR_MULTI_DPF1_ADDR, &data);
		data = (NORM_PAUSE_OPCODE << 16) | (data & 0xFFFF);
		xgene_enet_wr_axg_csr(pdata, XGENET_CSR_MULTI_DPF1_ADDR, data);
	पूर्ण

	data = (XG_DEF_PAUSE_OFF_THRES << 16) | XG_DEF_PAUSE_THRES;
	xgene_enet_wr_csr(pdata, XG_RXBUF_PAUSE_THRESH, data);

	xgene_xgmac_flowctl_tx(pdata, pdata->tx_छोड़ो);
	xgene_xgmac_flowctl_rx(pdata, pdata->rx_छोड़ो);
पूर्ण

अटल व्योम xgene_xgmac_rx_enable(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data | HSTRFEN);
पूर्ण

अटल व्योम xgene_xgmac_tx_enable(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data | HSTTFEN);
पूर्ण

अटल व्योम xgene_xgmac_rx_disable(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data & ~HSTRFEN);
पूर्ण

अटल व्योम xgene_xgmac_tx_disable(काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 data;

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data & ~HSTTFEN);
पूर्ण

अटल पूर्णांक xgene_enet_reset(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;

	अगर (!xgene_ring_mgr_init(pdata))
		वापस -ENODEV;

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

अटल व्योम xgene_enet_xgcle_bypass(काष्ठा xgene_enet_pdata *pdata,
				    u32 dst_ring_num, u16 bufpool_id,
				    u16 nxtbufpool_id)
अणु
	u32 cb, fpsel, nxtfpsel;

	xgene_enet_rd_csr(pdata, XCLE_BYPASS_REG0_ADDR, &cb);
	cb |= CFG_CLE_BYPASS_EN0;
	CFG_CLE_IP_PROTOCOL0_SET(&cb, 3);
	xgene_enet_wr_csr(pdata, XCLE_BYPASS_REG0_ADDR, cb);

	fpsel = xgene_enet_get_fpsel(bufpool_id);
	nxtfpsel = xgene_enet_get_fpsel(nxtbufpool_id);
	xgene_enet_rd_csr(pdata, XCLE_BYPASS_REG1_ADDR, &cb);
	CFG_CLE_DSTQID0_SET(&cb, dst_ring_num);
	CFG_CLE_FPSEL0_SET(&cb, fpsel);
	CFG_CLE_NXTFPSEL0_SET(&cb, nxtfpsel);
	xgene_enet_wr_csr(pdata, XCLE_BYPASS_REG1_ADDR, cb);
	pr_info("+ cle_bypass: fpsel: %d nxtfpsel: %d\n", fpsel, nxtfpsel);
पूर्ण

अटल व्योम xgene_enet_shutकरोwn(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;

	अगर (dev->of_node) अणु
		अगर (!IS_ERR(pdata->clk))
			clk_disable_unprepare(pdata->clk);
	पूर्ण
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

अटल पूर्णांक xgene_enet_gpio_lookup(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;

	pdata->sfp_rdy = gpiod_get(dev, "rxlos", GPIOD_IN);
	अगर (IS_ERR(pdata->sfp_rdy))
		pdata->sfp_rdy = gpiod_get(dev, "sfp", GPIOD_IN);

	अगर (IS_ERR(pdata->sfp_rdy))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम xgene_enet_link_state(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xgene_enet_pdata *pdata = container_of(to_delayed_work(work),
					 काष्ठा xgene_enet_pdata, link_work);
	काष्ठा net_device *ndev = pdata->ndev;
	u32 link_status, poll_पूर्णांकerval;

	link_status = xgene_enet_link_status(pdata);
	अगर (pdata->sfp_gpio_en && link_status &&
	    (!IS_ERR(pdata->sfp_rdy) || !xgene_enet_gpio_lookup(pdata)) &&
	    !gpiod_get_value(pdata->sfp_rdy))
		link_status = 0;

	अगर (link_status) अणु
		अगर (!netअगर_carrier_ok(ndev)) अणु
			netअगर_carrier_on(ndev);
			xgene_xgmac_rx_enable(pdata);
			xgene_xgmac_tx_enable(pdata);
			netdev_info(ndev, "Link is Up - 10Gbps\n");
		पूर्ण
		poll_पूर्णांकerval = PHY_POLL_LINK_ON;
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(ndev)) अणु
			xgene_xgmac_rx_disable(pdata);
			xgene_xgmac_tx_disable(pdata);
			netअगर_carrier_off(ndev);
			netdev_info(ndev, "Link is Down\n");
		पूर्ण
		poll_पूर्णांकerval = PHY_POLL_LINK_OFF;

		xgene_pcs_reset(pdata);
	पूर्ण

	schedule_delayed_work(&pdata->link_work, poll_पूर्णांकerval);
पूर्ण

स्थिर काष्ठा xgene_mac_ops xgene_xgmac_ops = अणु
	.init = xgene_xgmac_init,
	.reset = xgene_xgmac_reset,
	.rx_enable = xgene_xgmac_rx_enable,
	.tx_enable = xgene_xgmac_tx_enable,
	.rx_disable = xgene_xgmac_rx_disable,
	.tx_disable = xgene_xgmac_tx_disable,
	.set_mac_addr = xgene_xgmac_set_mac_addr,
	.set_framesize = xgene_xgmac_set_frame_size,
	.set_mss = xgene_xgmac_set_mss,
	.get_drop_cnt = xgene_xgmac_get_drop_cnt,
	.link_state = xgene_enet_link_state,
	.enable_tx_छोड़ो = xgene_xgmac_enable_tx_छोड़ो,
	.flowctl_rx = xgene_xgmac_flowctl_rx,
	.flowctl_tx = xgene_xgmac_flowctl_tx
पूर्ण;

स्थिर काष्ठा xgene_port_ops xgene_xgport_ops = अणु
	.reset = xgene_enet_reset,
	.clear = xgene_enet_clear,
	.cle_bypass = xgene_enet_xgcle_bypass,
	.shutकरोwn = xgene_enet_shutकरोwn,
पूर्ण;
