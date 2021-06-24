<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2016, Fuzhou Rockchip Electronics Co., Ltd
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Modअगरied by Philippe Cornu <philippe.cornu@st.com>
 * This generic Synopsys DesignWare MIPI DSI host driver is based on the
 * Rockchip version from rockchip/dw-mipi-dsi.c with phy & bridge APIs.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/bridge/dw_mipi_dsi.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_prपूर्णांक.h>

#घोषणा HWVER_131			0x31333100	/* IP version 1.31 */

#घोषणा DSI_VERSION			0x00
#घोषणा VERSION				GENMASK(31, 8)

#घोषणा DSI_PWR_UP			0x04
#घोषणा RESET				0
#घोषणा POWERUP				BIT(0)

#घोषणा DSI_CLKMGR_CFG			0x08
#घोषणा TO_CLK_DIVISION(भाग)		(((भाग) & 0xff) << 8)
#घोषणा TX_ESC_CLK_DIVISION(भाग)	((भाग) & 0xff)

#घोषणा DSI_DPI_VCID			0x0c
#घोषणा DPI_VCID(vcid)			((vcid) & 0x3)

#घोषणा DSI_DPI_COLOR_CODING		0x10
#घोषणा LOOSELY18_EN			BIT(8)
#घोषणा DPI_COLOR_CODING_16BIT_1	0x0
#घोषणा DPI_COLOR_CODING_16BIT_2	0x1
#घोषणा DPI_COLOR_CODING_16BIT_3	0x2
#घोषणा DPI_COLOR_CODING_18BIT_1	0x3
#घोषणा DPI_COLOR_CODING_18BIT_2	0x4
#घोषणा DPI_COLOR_CODING_24BIT		0x5

#घोषणा DSI_DPI_CFG_POL			0x14
#घोषणा COLORM_ACTIVE_LOW		BIT(4)
#घोषणा SHUTD_ACTIVE_LOW		BIT(3)
#घोषणा HSYNC_ACTIVE_LOW		BIT(2)
#घोषणा VSYNC_ACTIVE_LOW		BIT(1)
#घोषणा DATAEN_ACTIVE_LOW		BIT(0)

#घोषणा DSI_DPI_LP_CMD_TIM		0x18
#घोषणा OUTVACT_LPCMD_TIME(p)		(((p) & 0xff) << 16)
#घोषणा INVACT_LPCMD_TIME(p)		((p) & 0xff)

#घोषणा DSI_DBI_VCID			0x1c
#घोषणा DSI_DBI_CFG			0x20
#घोषणा DSI_DBI_PARTITIONING_EN		0x24
#घोषणा DSI_DBI_CMDSIZE			0x28

#घोषणा DSI_PCKHDL_CFG			0x2c
#घोषणा CRC_RX_EN			BIT(4)
#घोषणा ECC_RX_EN			BIT(3)
#घोषणा BTA_EN				BIT(2)
#घोषणा EOTP_RX_EN			BIT(1)
#घोषणा EOTP_TX_EN			BIT(0)

#घोषणा DSI_GEN_VCID			0x30

#घोषणा DSI_MODE_CFG			0x34
#घोषणा ENABLE_VIDEO_MODE		0
#घोषणा ENABLE_CMD_MODE			BIT(0)

#घोषणा DSI_VID_MODE_CFG		0x38
#घोषणा ENABLE_LOW_POWER		(0x3f << 8)
#घोषणा ENABLE_LOW_POWER_MASK		(0x3f << 8)
#घोषणा VID_MODE_TYPE_NON_BURST_SYNC_PULSES	0x0
#घोषणा VID_MODE_TYPE_NON_BURST_SYNC_EVENTS	0x1
#घोषणा VID_MODE_TYPE_BURST			0x2
#घोषणा VID_MODE_TYPE_MASK			0x3
#घोषणा ENABLE_LOW_POWER_CMD		BIT(15)
#घोषणा VID_MODE_VPG_ENABLE		BIT(16)
#घोषणा VID_MODE_VPG_MODE		BIT(20)
#घोषणा VID_MODE_VPG_HORIZONTAL		BIT(24)

#घोषणा DSI_VID_PKT_SIZE		0x3c
#घोषणा VID_PKT_SIZE(p)			((p) & 0x3fff)

#घोषणा DSI_VID_NUM_CHUNKS		0x40
#घोषणा VID_NUM_CHUNKS(c)		((c) & 0x1fff)

#घोषणा DSI_VID_शून्य_SIZE		0x44
#घोषणा VID_शून्य_SIZE(b)		((b) & 0x1fff)

#घोषणा DSI_VID_HSA_TIME		0x48
#घोषणा DSI_VID_HBP_TIME		0x4c
#घोषणा DSI_VID_HLINE_TIME		0x50
#घोषणा DSI_VID_VSA_LINES		0x54
#घोषणा DSI_VID_VBP_LINES		0x58
#घोषणा DSI_VID_VFP_LINES		0x5c
#घोषणा DSI_VID_VACTIVE_LINES		0x60
#घोषणा DSI_EDPI_CMD_SIZE		0x64

#घोषणा DSI_CMD_MODE_CFG		0x68
#घोषणा MAX_RD_PKT_SIZE_LP		BIT(24)
#घोषणा DCS_LW_TX_LP			BIT(19)
#घोषणा DCS_SR_0P_TX_LP			BIT(18)
#घोषणा DCS_SW_1P_TX_LP			BIT(17)
#घोषणा DCS_SW_0P_TX_LP			BIT(16)
#घोषणा GEN_LW_TX_LP			BIT(14)
#घोषणा GEN_SR_2P_TX_LP			BIT(13)
#घोषणा GEN_SR_1P_TX_LP			BIT(12)
#घोषणा GEN_SR_0P_TX_LP			BIT(11)
#घोषणा GEN_SW_2P_TX_LP			BIT(10)
#घोषणा GEN_SW_1P_TX_LP			BIT(9)
#घोषणा GEN_SW_0P_TX_LP			BIT(8)
#घोषणा ACK_RQST_EN			BIT(1)
#घोषणा TEAR_FX_EN			BIT(0)

#घोषणा CMD_MODE_ALL_LP			(MAX_RD_PKT_SIZE_LP | \
					 DCS_LW_TX_LP | \
					 DCS_SR_0P_TX_LP | \
					 DCS_SW_1P_TX_LP | \
					 DCS_SW_0P_TX_LP | \
					 GEN_LW_TX_LP | \
					 GEN_SR_2P_TX_LP | \
					 GEN_SR_1P_TX_LP | \
					 GEN_SR_0P_TX_LP | \
					 GEN_SW_2P_TX_LP | \
					 GEN_SW_1P_TX_LP | \
					 GEN_SW_0P_TX_LP)

#घोषणा DSI_GEN_HDR			0x6c
#घोषणा DSI_GEN_PLD_DATA		0x70

#घोषणा DSI_CMD_PKT_STATUS		0x74
#घोषणा GEN_RD_CMD_BUSY			BIT(6)
#घोषणा GEN_PLD_R_FULL			BIT(5)
#घोषणा GEN_PLD_R_EMPTY			BIT(4)
#घोषणा GEN_PLD_W_FULL			BIT(3)
#घोषणा GEN_PLD_W_EMPTY			BIT(2)
#घोषणा GEN_CMD_FULL			BIT(1)
#घोषणा GEN_CMD_EMPTY			BIT(0)

#घोषणा DSI_TO_CNT_CFG			0x78
#घोषणा HSTX_TO_CNT(p)			(((p) & 0xffff) << 16)
#घोषणा LPRX_TO_CNT(p)			((p) & 0xffff)

#घोषणा DSI_HS_RD_TO_CNT		0x7c
#घोषणा DSI_LP_RD_TO_CNT		0x80
#घोषणा DSI_HS_WR_TO_CNT		0x84
#घोषणा DSI_LP_WR_TO_CNT		0x88
#घोषणा DSI_BTA_TO_CNT			0x8c

#घोषणा DSI_LPCLK_CTRL			0x94
#घोषणा AUTO_CLKLANE_CTRL		BIT(1)
#घोषणा PHY_TXREQUESTCLKHS		BIT(0)

#घोषणा DSI_PHY_TMR_LPCLK_CFG		0x98
#घोषणा PHY_CLKHS2LP_TIME(lbcc)		(((lbcc) & 0x3ff) << 16)
#घोषणा PHY_CLKLP2HS_TIME(lbcc)		((lbcc) & 0x3ff)

#घोषणा DSI_PHY_TMR_CFG			0x9c
#घोषणा PHY_HS2LP_TIME(lbcc)		(((lbcc) & 0xff) << 24)
#घोषणा PHY_LP2HS_TIME(lbcc)		(((lbcc) & 0xff) << 16)
#घोषणा MAX_RD_TIME(lbcc)		((lbcc) & 0x7fff)
#घोषणा PHY_HS2LP_TIME_V131(lbcc)	(((lbcc) & 0x3ff) << 16)
#घोषणा PHY_LP2HS_TIME_V131(lbcc)	((lbcc) & 0x3ff)

#घोषणा DSI_PHY_RSTZ			0xa0
#घोषणा PHY_DISFORCEPLL			0
#घोषणा PHY_ENFORCEPLL			BIT(3)
#घोषणा PHY_DISABLECLK			0
#घोषणा PHY_ENABLECLK			BIT(2)
#घोषणा PHY_RSTZ			0
#घोषणा PHY_UNRSTZ			BIT(1)
#घोषणा PHY_SHUTDOWNZ			0
#घोषणा PHY_UNSHUTDOWNZ			BIT(0)

#घोषणा DSI_PHY_IF_CFG			0xa4
#घोषणा PHY_STOP_WAIT_TIME(cycle)	(((cycle) & 0xff) << 8)
#घोषणा N_LANES(n)			(((n) - 1) & 0x3)

#घोषणा DSI_PHY_ULPS_CTRL		0xa8
#घोषणा DSI_PHY_TX_TRIGGERS		0xac

#घोषणा DSI_PHY_STATUS			0xb0
#घोषणा PHY_STOP_STATE_CLK_LANE		BIT(2)
#घोषणा PHY_LOCK			BIT(0)

#घोषणा DSI_PHY_TST_CTRL0		0xb4
#घोषणा PHY_TESTCLK			BIT(1)
#घोषणा PHY_UNTESTCLK			0
#घोषणा PHY_TESTCLR			BIT(0)
#घोषणा PHY_UNTESTCLR			0

#घोषणा DSI_PHY_TST_CTRL1		0xb8
#घोषणा PHY_TESTEN			BIT(16)
#घोषणा PHY_UNTESTEN			0
#घोषणा PHY_TESTDOUT(n)			(((n) & 0xff) << 8)
#घोषणा PHY_TESTDIN(n)			((n) & 0xff)

#घोषणा DSI_INT_ST0			0xbc
#घोषणा DSI_INT_ST1			0xc0
#घोषणा DSI_INT_MSK0			0xc4
#घोषणा DSI_INT_MSK1			0xc8

#घोषणा DSI_PHY_TMR_RD_CFG		0xf4
#घोषणा MAX_RD_TIME_V131(lbcc)		((lbcc) & 0x7fff)

#घोषणा PHY_STATUS_TIMEOUT_US		10000
#घोषणा CMD_PKT_STATUS_TIMEOUT_US	20000

#अगर_घोषित CONFIG_DEBUG_FS
#घोषणा VPG_DEFS(name, dsi) \
	((व्योम __क्रमce *)&((*dsi).vpg_defs.name))

#घोषणा REGISTER(name, mask, dsi) \
	अणु #name, VPG_DEFS(name, dsi), mask, dsi पूर्ण

काष्ठा debugfs_entries अणु
	स्थिर अक्षर				*name;
	bool					*reg;
	u32					mask;
	काष्ठा dw_mipi_dsi			*dsi;
पूर्ण;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

काष्ठा dw_mipi_dsi अणु
	काष्ठा drm_bridge bridge;
	काष्ठा mipi_dsi_host dsi_host;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा device *dev;
	व्योम __iomem *base;

	काष्ठा clk *pclk;

	अचिन्हित पूर्णांक lane_mbps; /* per lane */
	u32 channel;
	u32 lanes;
	u32 क्रमmat;
	अचिन्हित दीर्घ mode_flags;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs;
	काष्ठा debugfs_entries *debugfs_vpg;
	काष्ठा अणु
		bool vpg;
		bool vpg_horizontal;
		bool vpg_ber_pattern;
	पूर्ण vpg_defs;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

	काष्ठा dw_mipi_dsi *master; /* dual-dsi master ptr */
	काष्ठा dw_mipi_dsi *slave; /* dual-dsi slave ptr */

	स्थिर काष्ठा dw_mipi_dsi_plat_data *plat_data;
पूर्ण;

/*
 * Check अगर either a link to a master or slave is present
 */
अटल अंतरभूत bool dw_mipi_is_dual_mode(काष्ठा dw_mipi_dsi *dsi)
अणु
	वापस dsi->slave || dsi->master;
पूर्ण

/*
 * The controller should generate 2 frames beक्रमe
 * preparing the peripheral.
 */
अटल व्योम dw_mipi_dsi_रुको_क्रम_two_frames(स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक refresh, two_frames;

	refresh = drm_mode_vrefresh(mode);
	two_frames = DIV_ROUND_UP(MSEC_PER_SEC, refresh) * 2;
	msleep(two_frames);
पूर्ण

अटल अंतरभूत काष्ठा dw_mipi_dsi *host_to_dsi(काष्ठा mipi_dsi_host *host)
अणु
	वापस container_of(host, काष्ठा dw_mipi_dsi, dsi_host);
पूर्ण

अटल अंतरभूत काष्ठा dw_mipi_dsi *bridge_to_dsi(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा dw_mipi_dsi, bridge);
पूर्ण

अटल अंतरभूत व्योम dsi_ग_लिखो(काष्ठा dw_mipi_dsi *dsi, u32 reg, u32 val)
अणु
	ग_लिखोl(val, dsi->base + reg);
पूर्ण

अटल अंतरभूत u32 dsi_पढ़ो(काष्ठा dw_mipi_dsi *dsi, u32 reg)
अणु
	वापस पढ़ोl(dsi->base + reg);
पूर्ण

अटल पूर्णांक dw_mipi_dsi_host_attach(काष्ठा mipi_dsi_host *host,
				   काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा dw_mipi_dsi *dsi = host_to_dsi(host);
	स्थिर काष्ठा dw_mipi_dsi_plat_data *pdata = dsi->plat_data;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	अगर (device->lanes > dsi->plat_data->max_data_lanes) अणु
		dev_err(dsi->dev, "the number of data lanes(%u) is too many\n",
			device->lanes);
		वापस -EINVAL;
	पूर्ण

	dsi->lanes = device->lanes;
	dsi->channel = device->channel;
	dsi->क्रमmat = device->क्रमmat;
	dsi->mode_flags = device->mode_flags;

	ret = drm_of_find_panel_or_bridge(host->dev->of_node, 1, 0,
					  &panel, &bridge);
	अगर (ret)
		वापस ret;

	अगर (panel) अणु
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_DSI);
		अगर (IS_ERR(bridge))
			वापस PTR_ERR(bridge);
	पूर्ण

	dsi->panel_bridge = bridge;

	drm_bridge_add(&dsi->bridge);

	अगर (pdata->host_ops && pdata->host_ops->attach) अणु
		ret = pdata->host_ops->attach(pdata->priv_data, device);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_host_detach(काष्ठा mipi_dsi_host *host,
				   काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा dw_mipi_dsi *dsi = host_to_dsi(host);
	स्थिर काष्ठा dw_mipi_dsi_plat_data *pdata = dsi->plat_data;
	पूर्णांक ret;

	अगर (pdata->host_ops && pdata->host_ops->detach) अणु
		ret = pdata->host_ops->detach(pdata->priv_data, device);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	drm_of_panel_bridge_हटाओ(host->dev->of_node, 1, 0);

	drm_bridge_हटाओ(&dsi->bridge);

	वापस 0;
पूर्ण

अटल व्योम dw_mipi_message_config(काष्ठा dw_mipi_dsi *dsi,
				   स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	bool lpm = msg->flags & MIPI_DSI_MSG_USE_LPM;
	u32 val = 0;

	/*
	 * TODO dw drv improvements
	 * largest packet sizes during hfp or during vsa/vpb/vfp
	 * should be computed according to byte lane, lane number and only
	 * अगर sending lp cmds in high speed is enable (PHY_TXREQUESTCLKHS)
	 */
	dsi_ग_लिखो(dsi, DSI_DPI_LP_CMD_TIM, OUTVACT_LPCMD_TIME(16)
		  | INVACT_LPCMD_TIME(4));

	अगर (msg->flags & MIPI_DSI_MSG_REQ_ACK)
		val |= ACK_RQST_EN;
	अगर (lpm)
		val |= CMD_MODE_ALL_LP;

	dsi_ग_लिखो(dsi, DSI_CMD_MODE_CFG, val);

	val = dsi_पढ़ो(dsi, DSI_VID_MODE_CFG);
	अगर (lpm)
		val |= ENABLE_LOW_POWER_CMD;
	अन्यथा
		val &= ~ENABLE_LOW_POWER_CMD;
	dsi_ग_लिखो(dsi, DSI_VID_MODE_CFG, val);
पूर्ण

अटल पूर्णांक dw_mipi_dsi_gen_pkt_hdr_ग_लिखो(काष्ठा dw_mipi_dsi *dsi, u32 hdr_val)
अणु
	पूर्णांक ret;
	u32 val, mask;

	ret = पढ़ोl_poll_समयout(dsi->base + DSI_CMD_PKT_STATUS,
				 val, !(val & GEN_CMD_FULL), 1000,
				 CMD_PKT_STATUS_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dsi->dev, "failed to get available command FIFO\n");
		वापस ret;
	पूर्ण

	dsi_ग_लिखो(dsi, DSI_GEN_HDR, hdr_val);

	mask = GEN_CMD_EMPTY | GEN_PLD_W_EMPTY;
	ret = पढ़ोl_poll_समयout(dsi->base + DSI_CMD_PKT_STATUS,
				 val, (val & mask) == mask,
				 1000, CMD_PKT_STATUS_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dsi->dev, "failed to write command FIFO\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_ग_लिखो(काष्ठा dw_mipi_dsi *dsi,
			     स्थिर काष्ठा mipi_dsi_packet *packet)
अणु
	स्थिर u8 *tx_buf = packet->payload;
	पूर्णांक len = packet->payload_length, pld_data_bytes = माप(u32), ret;
	__le32 word;
	u32 val;

	जबतक (len) अणु
		अगर (len < pld_data_bytes) अणु
			word = 0;
			स_नकल(&word, tx_buf, len);
			dsi_ग_लिखो(dsi, DSI_GEN_PLD_DATA, le32_to_cpu(word));
			len = 0;
		पूर्ण अन्यथा अणु
			स_नकल(&word, tx_buf, pld_data_bytes);
			dsi_ग_लिखो(dsi, DSI_GEN_PLD_DATA, le32_to_cpu(word));
			tx_buf += pld_data_bytes;
			len -= pld_data_bytes;
		पूर्ण

		ret = पढ़ोl_poll_समयout(dsi->base + DSI_CMD_PKT_STATUS,
					 val, !(val & GEN_PLD_W_FULL), 1000,
					 CMD_PKT_STATUS_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(dsi->dev,
				"failed to get available write payload FIFO\n");
			वापस ret;
		पूर्ण
	पूर्ण

	word = 0;
	स_नकल(&word, packet->header, माप(packet->header));
	वापस dw_mipi_dsi_gen_pkt_hdr_ग_लिखो(dsi, le32_to_cpu(word));
पूर्ण

अटल पूर्णांक dw_mipi_dsi_पढ़ो(काष्ठा dw_mipi_dsi *dsi,
			    स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	पूर्णांक i, j, ret, len = msg->rx_len;
	u8 *buf = msg->rx_buf;
	u32 val;

	/* Wait end of the पढ़ो operation */
	ret = पढ़ोl_poll_समयout(dsi->base + DSI_CMD_PKT_STATUS,
				 val, !(val & GEN_RD_CMD_BUSY),
				 1000, CMD_PKT_STATUS_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dsi->dev, "Timeout during read operation\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < len; i += 4) अणु
		/* Read fअगरo must not be empty beक्रमe all bytes are पढ़ो */
		ret = पढ़ोl_poll_समयout(dsi->base + DSI_CMD_PKT_STATUS,
					 val, !(val & GEN_PLD_R_EMPTY),
					 1000, CMD_PKT_STATUS_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(dsi->dev, "Read payload FIFO is empty\n");
			वापस ret;
		पूर्ण

		val = dsi_पढ़ो(dsi, DSI_GEN_PLD_DATA);
		क्रम (j = 0; j < 4 && j + i < len; j++)
			buf[i + j] = val >> (8 * j);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार dw_mipi_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
					 स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा dw_mipi_dsi *dsi = host_to_dsi(host);
	काष्ठा mipi_dsi_packet packet;
	पूर्णांक ret, nb_bytes;

	ret = mipi_dsi_create_packet(&packet, msg);
	अगर (ret) अणु
		dev_err(dsi->dev, "failed to create packet: %d\n", ret);
		वापस ret;
	पूर्ण

	dw_mipi_message_config(dsi, msg);
	अगर (dsi->slave)
		dw_mipi_message_config(dsi->slave, msg);

	ret = dw_mipi_dsi_ग_लिखो(dsi, &packet);
	अगर (ret)
		वापस ret;
	अगर (dsi->slave) अणु
		ret = dw_mipi_dsi_ग_लिखो(dsi->slave, &packet);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (msg->rx_buf && msg->rx_len) अणु
		ret = dw_mipi_dsi_पढ़ो(dsi, msg);
		अगर (ret)
			वापस ret;
		nb_bytes = msg->rx_len;
	पूर्ण अन्यथा अणु
		nb_bytes = packet.size;
	पूर्ण

	वापस nb_bytes;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops dw_mipi_dsi_host_ops = अणु
	.attach = dw_mipi_dsi_host_attach,
	.detach = dw_mipi_dsi_host_detach,
	.transfer = dw_mipi_dsi_host_transfer,
पूर्ण;

अटल व्योम dw_mipi_dsi_video_mode_config(काष्ठा dw_mipi_dsi *dsi)
अणु
	u32 val;

	/*
	 * TODO dw drv improvements
	 * enabling low घातer is panel-dependent, we should use the
	 * panel configuration here...
	 */
	val = ENABLE_LOW_POWER;

	अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		val |= VID_MODE_TYPE_BURST;
	अन्यथा अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		val |= VID_MODE_TYPE_NON_BURST_SYNC_PULSES;
	अन्यथा
		val |= VID_MODE_TYPE_NON_BURST_SYNC_EVENTS;

#अगर_घोषित CONFIG_DEBUG_FS
	अगर (dsi->vpg_defs.vpg) अणु
		val |= VID_MODE_VPG_ENABLE;
		val |= dsi->vpg_defs.vpg_horizontal ?
		       VID_MODE_VPG_HORIZONTAL : 0;
		val |= dsi->vpg_defs.vpg_ber_pattern ? VID_MODE_VPG_MODE : 0;
	पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

	dsi_ग_लिखो(dsi, DSI_VID_MODE_CFG, val);
पूर्ण

अटल व्योम dw_mipi_dsi_set_mode(काष्ठा dw_mipi_dsi *dsi,
				 अचिन्हित दीर्घ mode_flags)
अणु
	u32 val;

	dsi_ग_लिखो(dsi, DSI_PWR_UP, RESET);

	अगर (mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		dsi_ग_लिखो(dsi, DSI_MODE_CFG, ENABLE_VIDEO_MODE);
		dw_mipi_dsi_video_mode_config(dsi);
	पूर्ण अन्यथा अणु
		dsi_ग_लिखो(dsi, DSI_MODE_CFG, ENABLE_CMD_MODE);
	पूर्ण

	val = PHY_TXREQUESTCLKHS;
	अगर (dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS)
		val |= AUTO_CLKLANE_CTRL;
	dsi_ग_लिखो(dsi, DSI_LPCLK_CTRL, val);

	dsi_ग_लिखो(dsi, DSI_PWR_UP, POWERUP);
पूर्ण

अटल व्योम dw_mipi_dsi_disable(काष्ठा dw_mipi_dsi *dsi)
अणु
	dsi_ग_लिखो(dsi, DSI_PWR_UP, RESET);
	dsi_ग_लिखो(dsi, DSI_PHY_RSTZ, PHY_RSTZ);
पूर्ण

अटल व्योम dw_mipi_dsi_init(काष्ठा dw_mipi_dsi *dsi)
अणु
	स्थिर काष्ठा dw_mipi_dsi_phy_ops *phy_ops = dsi->plat_data->phy_ops;
	अचिन्हित पूर्णांक esc_rate; /* in MHz */
	u32 esc_clk_भागision;
	पूर्णांक ret;

	/*
	 * The maximum permitted escape घड़ी is 20MHz and it is derived from
	 * lanebyteclk, which is running at "lane_mbps / 8".
	 */
	अगर (phy_ops->get_esc_clk_rate) अणु
		ret = phy_ops->get_esc_clk_rate(dsi->plat_data->priv_data,
						&esc_rate);
		अगर (ret)
			DRM_DEBUG_DRIVER("Phy get_esc_clk_rate() failed\n");
	पूर्ण अन्यथा
		esc_rate = 20; /* Default to 20MHz */

	/*
	 * We want :
	 *     (lane_mbps >> 3) / esc_clk_भागision < X
	 * which is:
	 *     (lane_mbps >> 3) / X > esc_clk_भागision
	 */
	esc_clk_भागision = (dsi->lane_mbps >> 3) / esc_rate + 1;

	dsi_ग_लिखो(dsi, DSI_PWR_UP, RESET);

	/*
	 * TODO dw drv improvements
	 * समयout घड़ी भागision should be computed with the
	 * high speed transmission counter समयout and byte lane...
	 */
	dsi_ग_लिखो(dsi, DSI_CLKMGR_CFG, TO_CLK_DIVISION(10) |
		  TX_ESC_CLK_DIVISION(esc_clk_भागision));
पूर्ण

अटल व्योम dw_mipi_dsi_dpi_config(काष्ठा dw_mipi_dsi *dsi,
				   स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 val = 0, color = 0;

	चयन (dsi->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		color = DPI_COLOR_CODING_24BIT;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		color = DPI_COLOR_CODING_18BIT_2 | LOOSELY18_EN;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		color = DPI_COLOR_CODING_18BIT_1;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		color = DPI_COLOR_CODING_16BIT_1;
		अवरोध;
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		val |= VSYNC_ACTIVE_LOW;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		val |= HSYNC_ACTIVE_LOW;

	dsi_ग_लिखो(dsi, DSI_DPI_VCID, DPI_VCID(dsi->channel));
	dsi_ग_लिखो(dsi, DSI_DPI_COLOR_CODING, color);
	dsi_ग_लिखो(dsi, DSI_DPI_CFG_POL, val);
पूर्ण

अटल व्योम dw_mipi_dsi_packet_handler_config(काष्ठा dw_mipi_dsi *dsi)
अणु
	dsi_ग_लिखो(dsi, DSI_PCKHDL_CFG, CRC_RX_EN | ECC_RX_EN | BTA_EN);
पूर्ण

अटल व्योम dw_mipi_dsi_video_packet_config(काष्ठा dw_mipi_dsi *dsi,
					    स्थिर काष्ठा drm_display_mode *mode)
अणु
	/*
	 * TODO dw drv improvements
	 * only burst mode is supported here. For non-burst video modes,
	 * we should compute DSI_VID_PKT_SIZE, DSI_VCCR.NUMC &
	 * DSI_VNPCR.NPSIZE... especially because this driver supports
	 * non-burst video modes, see dw_mipi_dsi_video_mode_config()...
	 */

	dsi_ग_लिखो(dsi, DSI_VID_PKT_SIZE,
		       dw_mipi_is_dual_mode(dsi) ?
				VID_PKT_SIZE(mode->hdisplay / 2) :
				VID_PKT_SIZE(mode->hdisplay));
पूर्ण

अटल व्योम dw_mipi_dsi_command_mode_config(काष्ठा dw_mipi_dsi *dsi)
अणु
	/*
	 * TODO dw drv improvements
	 * compute high speed transmission counter समयout according
	 * to the समयout घड़ी भागision (TO_CLK_DIVISION) and byte lane...
	 */
	dsi_ग_लिखो(dsi, DSI_TO_CNT_CFG, HSTX_TO_CNT(1000) | LPRX_TO_CNT(1000));
	/*
	 * TODO dw drv improvements
	 * the Bus-Turn-Around Timeout Counter should be computed
	 * according to byte lane...
	 */
	dsi_ग_लिखो(dsi, DSI_BTA_TO_CNT, 0xd00);
	dsi_ग_लिखो(dsi, DSI_MODE_CFG, ENABLE_CMD_MODE);
पूर्ण

/* Get lane byte घड़ी cycles. */
अटल u32 dw_mipi_dsi_get_hcomponent_lbcc(काष्ठा dw_mipi_dsi *dsi,
					   स्थिर काष्ठा drm_display_mode *mode,
					   u32 hcomponent)
अणु
	u32 frac, lbcc;

	lbcc = hcomponent * dsi->lane_mbps * MSEC_PER_SEC / 8;

	frac = lbcc % mode->घड़ी;
	lbcc = lbcc / mode->घड़ी;
	अगर (frac)
		lbcc++;

	वापस lbcc;
पूर्ण

अटल व्योम dw_mipi_dsi_line_समयr_config(काष्ठा dw_mipi_dsi *dsi,
					  स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 htotal, hsa, hbp, lbcc;

	htotal = mode->htotal;
	hsa = mode->hsync_end - mode->hsync_start;
	hbp = mode->htotal - mode->hsync_end;

	/*
	 * TODO dw drv improvements
	 * computations below may be improved...
	 */
	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(dsi, mode, htotal);
	dsi_ग_लिखो(dsi, DSI_VID_HLINE_TIME, lbcc);

	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(dsi, mode, hsa);
	dsi_ग_लिखो(dsi, DSI_VID_HSA_TIME, lbcc);

	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(dsi, mode, hbp);
	dsi_ग_लिखो(dsi, DSI_VID_HBP_TIME, lbcc);
पूर्ण

अटल व्योम dw_mipi_dsi_vertical_timing_config(काष्ठा dw_mipi_dsi *dsi,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 vactive, vsa, vfp, vbp;

	vactive = mode->vdisplay;
	vsa = mode->vsync_end - mode->vsync_start;
	vfp = mode->vsync_start - mode->vdisplay;
	vbp = mode->vtotal - mode->vsync_end;

	dsi_ग_लिखो(dsi, DSI_VID_VACTIVE_LINES, vactive);
	dsi_ग_लिखो(dsi, DSI_VID_VSA_LINES, vsa);
	dsi_ग_लिखो(dsi, DSI_VID_VFP_LINES, vfp);
	dsi_ग_लिखो(dsi, DSI_VID_VBP_LINES, vbp);
पूर्ण

अटल व्योम dw_mipi_dsi_dphy_timing_config(काष्ठा dw_mipi_dsi *dsi)
अणु
	स्थिर काष्ठा dw_mipi_dsi_phy_ops *phy_ops = dsi->plat_data->phy_ops;
	काष्ठा dw_mipi_dsi_dphy_timing timing;
	u32 hw_version;
	पूर्णांक ret;

	ret = phy_ops->get_timing(dsi->plat_data->priv_data,
				  dsi->lane_mbps, &timing);
	अगर (ret)
		DRM_DEV_ERROR(dsi->dev, "Retrieving phy timings failed\n");

	/*
	 * TODO dw drv improvements
	 * data & घड़ी lane समयrs should be computed according to panel
	 * blankings and to the स्वतःmatic घड़ी lane control mode...
	 * note: DSI_PHY_TMR_CFG.MAX_RD_TIME should be in line with
	 * DSI_CMD_MODE_CFG.MAX_RD_PKT_SIZE_LP (see CMD_MODE_ALL_LP)
	 */

	hw_version = dsi_पढ़ो(dsi, DSI_VERSION) & VERSION;

	अगर (hw_version >= HWVER_131) अणु
		dsi_ग_लिखो(dsi, DSI_PHY_TMR_CFG,
			  PHY_HS2LP_TIME_V131(timing.data_hs2lp) |
			  PHY_LP2HS_TIME_V131(timing.data_lp2hs));
		dsi_ग_लिखो(dsi, DSI_PHY_TMR_RD_CFG, MAX_RD_TIME_V131(10000));
	पूर्ण अन्यथा अणु
		dsi_ग_लिखो(dsi, DSI_PHY_TMR_CFG,
			  PHY_HS2LP_TIME(timing.data_hs2lp) |
			  PHY_LP2HS_TIME(timing.data_lp2hs) |
			  MAX_RD_TIME(10000));
	पूर्ण

	dsi_ग_लिखो(dsi, DSI_PHY_TMR_LPCLK_CFG,
		  PHY_CLKHS2LP_TIME(timing.clk_hs2lp) |
		  PHY_CLKLP2HS_TIME(timing.clk_lp2hs));
पूर्ण

अटल व्योम dw_mipi_dsi_dphy_पूर्णांकerface_config(काष्ठा dw_mipi_dsi *dsi)
अणु
	/*
	 * TODO dw drv improvements
	 * stop रुको समय should be the maximum between host dsi
	 * and panel stop रुको बार
	 */
	dsi_ग_लिखो(dsi, DSI_PHY_IF_CFG, PHY_STOP_WAIT_TIME(0x20) |
		  N_LANES(dsi->lanes));
पूर्ण

अटल व्योम dw_mipi_dsi_dphy_init(काष्ठा dw_mipi_dsi *dsi)
अणु
	/* Clear PHY state */
	dsi_ग_लिखो(dsi, DSI_PHY_RSTZ, PHY_DISFORCEPLL | PHY_DISABLECLK
		  | PHY_RSTZ | PHY_SHUTDOWNZ);
	dsi_ग_लिखो(dsi, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR);
	dsi_ग_लिखो(dsi, DSI_PHY_TST_CTRL0, PHY_TESTCLR);
	dsi_ग_लिखो(dsi, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR);
पूर्ण

अटल व्योम dw_mipi_dsi_dphy_enable(काष्ठा dw_mipi_dsi *dsi)
अणु
	u32 val;
	पूर्णांक ret;

	dsi_ग_लिखो(dsi, DSI_PHY_RSTZ, PHY_ENFORCEPLL | PHY_ENABLECLK |
		  PHY_UNRSTZ | PHY_UNSHUTDOWNZ);

	ret = पढ़ोl_poll_समयout(dsi->base + DSI_PHY_STATUS, val,
				 val & PHY_LOCK, 1000, PHY_STATUS_TIMEOUT_US);
	अगर (ret)
		DRM_DEBUG_DRIVER("failed to wait phy lock state\n");

	ret = पढ़ोl_poll_समयout(dsi->base + DSI_PHY_STATUS,
				 val, val & PHY_STOP_STATE_CLK_LANE, 1000,
				 PHY_STATUS_TIMEOUT_US);
	अगर (ret)
		DRM_DEBUG_DRIVER("failed to wait phy clk lane stop state\n");
पूर्ण

अटल व्योम dw_mipi_dsi_clear_err(काष्ठा dw_mipi_dsi *dsi)
अणु
	dsi_पढ़ो(dsi, DSI_INT_ST0);
	dsi_पढ़ो(dsi, DSI_INT_ST1);
	dsi_ग_लिखो(dsi, DSI_INT_MSK0, 0);
	dsi_ग_लिखो(dsi, DSI_INT_MSK1, 0);
पूर्ण

अटल व्योम dw_mipi_dsi_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dw_mipi_dsi *dsi = bridge_to_dsi(bridge);
	स्थिर काष्ठा dw_mipi_dsi_phy_ops *phy_ops = dsi->plat_data->phy_ops;

	/*
	 * Switch to command mode beक्रमe panel-bridge post_disable &
	 * panel unprepare.
	 * Note: panel-bridge disable & panel disable has been called
	 * beक्रमe by the drm framework.
	 */
	dw_mipi_dsi_set_mode(dsi, 0);

	/*
	 * TODO Only way found to call panel-bridge post_disable &
	 * panel unprepare beक्रमe the dsi "final" disable...
	 * This needs to be fixed in the drm_bridge framework and the API
	 * needs to be updated to manage our own call chains...
	 */
	अगर (dsi->panel_bridge->funcs->post_disable)
		dsi->panel_bridge->funcs->post_disable(dsi->panel_bridge);

	अगर (phy_ops->घातer_off)
		phy_ops->घातer_off(dsi->plat_data->priv_data);

	अगर (dsi->slave) अणु
		dw_mipi_dsi_disable(dsi->slave);
		clk_disable_unprepare(dsi->slave->pclk);
		pm_runसमय_put(dsi->slave->dev);
	पूर्ण
	dw_mipi_dsi_disable(dsi);

	clk_disable_unprepare(dsi->pclk);
	pm_runसमय_put(dsi->dev);
पूर्ण

अटल अचिन्हित पूर्णांक dw_mipi_dsi_get_lanes(काष्ठा dw_mipi_dsi *dsi)
अणु
	/* this instance is the slave, so add the master's lanes */
	अगर (dsi->master)
		वापस dsi->master->lanes + dsi->lanes;

	/* this instance is the master, so add the slave's lanes */
	अगर (dsi->slave)
		वापस dsi->lanes + dsi->slave->lanes;

	/* single-dsi, so no other instance to consider */
	वापस dsi->lanes;
पूर्ण

अटल व्योम dw_mipi_dsi_mode_set(काष्ठा dw_mipi_dsi *dsi,
				 स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	स्थिर काष्ठा dw_mipi_dsi_phy_ops *phy_ops = dsi->plat_data->phy_ops;
	व्योम *priv_data = dsi->plat_data->priv_data;
	पूर्णांक ret;
	u32 lanes = dw_mipi_dsi_get_lanes(dsi);

	clk_prepare_enable(dsi->pclk);

	ret = phy_ops->get_lane_mbps(priv_data, adjusted_mode, dsi->mode_flags,
				     lanes, dsi->क्रमmat, &dsi->lane_mbps);
	अगर (ret)
		DRM_DEBUG_DRIVER("Phy get_lane_mbps() failed\n");

	pm_runसमय_get_sync(dsi->dev);
	dw_mipi_dsi_init(dsi);
	dw_mipi_dsi_dpi_config(dsi, adjusted_mode);
	dw_mipi_dsi_packet_handler_config(dsi);
	dw_mipi_dsi_video_mode_config(dsi);
	dw_mipi_dsi_video_packet_config(dsi, adjusted_mode);
	dw_mipi_dsi_command_mode_config(dsi);
	dw_mipi_dsi_line_समयr_config(dsi, adjusted_mode);
	dw_mipi_dsi_vertical_timing_config(dsi, adjusted_mode);

	dw_mipi_dsi_dphy_init(dsi);
	dw_mipi_dsi_dphy_timing_config(dsi);
	dw_mipi_dsi_dphy_पूर्णांकerface_config(dsi);

	dw_mipi_dsi_clear_err(dsi);

	ret = phy_ops->init(priv_data);
	अगर (ret)
		DRM_DEBUG_DRIVER("Phy init() failed\n");

	dw_mipi_dsi_dphy_enable(dsi);

	dw_mipi_dsi_रुको_क्रम_two_frames(adjusted_mode);

	/* Switch to cmd mode क्रम panel-bridge pre_enable & panel prepare */
	dw_mipi_dsi_set_mode(dsi, 0);

	अगर (phy_ops->घातer_on)
		phy_ops->घातer_on(dsi->plat_data->priv_data);
पूर्ण

अटल व्योम dw_mipi_dsi_bridge_mode_set(काष्ठा drm_bridge *bridge,
					स्थिर काष्ठा drm_display_mode *mode,
					स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा dw_mipi_dsi *dsi = bridge_to_dsi(bridge);

	dw_mipi_dsi_mode_set(dsi, adjusted_mode);
	अगर (dsi->slave)
		dw_mipi_dsi_mode_set(dsi->slave, adjusted_mode);
पूर्ण

अटल व्योम dw_mipi_dsi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dw_mipi_dsi *dsi = bridge_to_dsi(bridge);

	/* Switch to video mode क्रम panel-bridge enable & panel enable */
	dw_mipi_dsi_set_mode(dsi, MIPI_DSI_MODE_VIDEO);
	अगर (dsi->slave)
		dw_mipi_dsi_set_mode(dsi->slave, MIPI_DSI_MODE_VIDEO);
पूर्ण

अटल क्रमागत drm_mode_status
dw_mipi_dsi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			      स्थिर काष्ठा drm_display_info *info,
			      स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा dw_mipi_dsi *dsi = bridge_to_dsi(bridge);
	स्थिर काष्ठा dw_mipi_dsi_plat_data *pdata = dsi->plat_data;
	क्रमागत drm_mode_status mode_status = MODE_OK;

	अगर (pdata->mode_valid)
		mode_status = pdata->mode_valid(pdata->priv_data, mode);

	वापस mode_status;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_bridge_attach(काष्ठा drm_bridge *bridge,
				     क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा dw_mipi_dsi *dsi = bridge_to_dsi(bridge);

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found\n");
		वापस -ENODEV;
	पूर्ण

	/* Set the encoder type as caller करोes not know it */
	bridge->encoder->encoder_type = DRM_MODE_ENCODER_DSI;

	/* Attach the panel-bridge to the dsi bridge */
	वापस drm_bridge_attach(bridge->encoder, dsi->panel_bridge, bridge,
				 flags);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs dw_mipi_dsi_bridge_funcs = अणु
	.mode_set     = dw_mipi_dsi_bridge_mode_set,
	.enable	      = dw_mipi_dsi_bridge_enable,
	.post_disable = dw_mipi_dsi_bridge_post_disable,
	.mode_valid   = dw_mipi_dsi_bridge_mode_valid,
	.attach	      = dw_mipi_dsi_bridge_attach,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक dw_mipi_dsi_debugfs_ग_लिखो(व्योम *data, u64 val)
अणु
	काष्ठा debugfs_entries *vpg = data;
	काष्ठा dw_mipi_dsi *dsi;
	u32 mode_cfg;

	अगर (!vpg)
		वापस -ENODEV;

	dsi = vpg->dsi;

	*vpg->reg = (bool)val;

	mode_cfg = dsi_पढ़ो(dsi, DSI_VID_MODE_CFG);

	अगर (*vpg->reg)
		mode_cfg |= vpg->mask;
	अन्यथा
		mode_cfg &= ~vpg->mask;

	dsi_ग_लिखो(dsi, DSI_VID_MODE_CFG, mode_cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_debugfs_show(व्योम *data, u64 *val)
अणु
	काष्ठा debugfs_entries *vpg = data;

	अगर (!vpg)
		वापस -ENODEV;

	*val = *vpg->reg;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_x32, dw_mipi_dsi_debugfs_show,
			 dw_mipi_dsi_debugfs_ग_लिखो, "%llu\n");

अटल व्योम debugfs_create_files(व्योम *data)
अणु
	काष्ठा dw_mipi_dsi *dsi = data;
	काष्ठा debugfs_entries debugfs[] = अणु
		REGISTER(vpg, VID_MODE_VPG_ENABLE, dsi),
		REGISTER(vpg_horizontal, VID_MODE_VPG_HORIZONTAL, dsi),
		REGISTER(vpg_ber_pattern, VID_MODE_VPG_MODE, dsi),
	पूर्ण;
	पूर्णांक i;

	dsi->debugfs_vpg = kmemdup(debugfs, माप(debugfs), GFP_KERNEL);
	अगर (!dsi->debugfs_vpg)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(debugfs); i++)
		debugfs_create_file(dsi->debugfs_vpg[i].name, 0644,
				    dsi->debugfs, &dsi->debugfs_vpg[i],
				    &fops_x32);
पूर्ण

अटल व्योम dw_mipi_dsi_debugfs_init(काष्ठा dw_mipi_dsi *dsi)
अणु
	dsi->debugfs = debugfs_create_dir(dev_name(dsi->dev), शून्य);
	अगर (IS_ERR(dsi->debugfs)) अणु
		dev_err(dsi->dev, "failed to create debugfs root\n");
		वापस;
	पूर्ण

	debugfs_create_files(dsi);
पूर्ण

अटल व्योम dw_mipi_dsi_debugfs_हटाओ(काष्ठा dw_mipi_dsi *dsi)
अणु
	debugfs_हटाओ_recursive(dsi->debugfs);
	kमुक्त(dsi->debugfs_vpg);
पूर्ण

#अन्यथा

अटल व्योम dw_mipi_dsi_debugfs_init(काष्ठा dw_mipi_dsi *dsi) अणु पूर्ण
अटल व्योम dw_mipi_dsi_debugfs_हटाओ(काष्ठा dw_mipi_dsi *dsi) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल काष्ठा dw_mipi_dsi *
__dw_mipi_dsi_probe(काष्ठा platक्रमm_device *pdev,
		    स्थिर काष्ठा dw_mipi_dsi_plat_data *plat_data)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा reset_control *apb_rst;
	काष्ठा dw_mipi_dsi *dsi;
	पूर्णांक ret;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस ERR_PTR(-ENOMEM);

	dsi->dev = dev;
	dsi->plat_data = plat_data;

	अगर (!plat_data->phy_ops->init || !plat_data->phy_ops->get_lane_mbps ||
	    !plat_data->phy_ops->get_timing) अणु
		DRM_ERROR("Phy not properly configured\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर (!plat_data->base) अणु
		dsi->base = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(dsi->base))
			वापस ERR_PTR(-ENODEV);

	पूर्ण अन्यथा अणु
		dsi->base = plat_data->base;
	पूर्ण

	dsi->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(dsi->pclk)) अणु
		ret = PTR_ERR(dsi->pclk);
		dev_err(dev, "Unable to get pclk: %d\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	/*
	 * Note that the reset was not defined in the initial device tree, so
	 * we have to be prepared क्रम it not being found.
	 */
	apb_rst = devm_reset_control_get_optional_exclusive(dev, "apb");
	अगर (IS_ERR(apb_rst)) अणु
		ret = PTR_ERR(apb_rst);

		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Unable to get reset control: %d\n", ret);

		वापस ERR_PTR(ret);
	पूर्ण

	अगर (apb_rst) अणु
		ret = clk_prepare_enable(dsi->pclk);
		अगर (ret) अणु
			dev_err(dev, "%s: Failed to enable pclk\n", __func__);
			वापस ERR_PTR(ret);
		पूर्ण

		reset_control_निश्चित(apb_rst);
		usleep_range(10, 20);
		reset_control_deनिश्चित(apb_rst);

		clk_disable_unprepare(dsi->pclk);
	पूर्ण

	dw_mipi_dsi_debugfs_init(dsi);
	pm_runसमय_enable(dev);

	dsi->dsi_host.ops = &dw_mipi_dsi_host_ops;
	dsi->dsi_host.dev = dev;
	ret = mipi_dsi_host_रेजिस्टर(&dsi->dsi_host);
	अगर (ret) अणु
		dev_err(dev, "Failed to register MIPI host: %d\n", ret);
		dw_mipi_dsi_debugfs_हटाओ(dsi);
		वापस ERR_PTR(ret);
	पूर्ण

	dsi->bridge.driver_निजी = dsi;
	dsi->bridge.funcs = &dw_mipi_dsi_bridge_funcs;
#अगर_घोषित CONFIG_OF
	dsi->bridge.of_node = pdev->dev.of_node;
#पूर्ण_अगर

	वापस dsi;
पूर्ण

अटल व्योम __dw_mipi_dsi_हटाओ(काष्ठा dw_mipi_dsi *dsi)
अणु
	mipi_dsi_host_unरेजिस्टर(&dsi->dsi_host);

	pm_runसमय_disable(dsi->dev);
	dw_mipi_dsi_debugfs_हटाओ(dsi);
पूर्ण

व्योम dw_mipi_dsi_set_slave(काष्ठा dw_mipi_dsi *dsi, काष्ठा dw_mipi_dsi *slave)
अणु
	/* पूर्णांकroduce controllers to each other */
	dsi->slave = slave;
	dsi->slave->master = dsi;

	/* migrate settings क्रम alपढ़ोy attached displays */
	dsi->slave->lanes = dsi->lanes;
	dsi->slave->channel = dsi->channel;
	dsi->slave->क्रमmat = dsi->क्रमmat;
	dsi->slave->mode_flags = dsi->mode_flags;
पूर्ण
EXPORT_SYMBOL_GPL(dw_mipi_dsi_set_slave);

/*
 * Probe/हटाओ API, used from platक्रमms based on the DRM bridge API.
 */
काष्ठा dw_mipi_dsi *
dw_mipi_dsi_probe(काष्ठा platक्रमm_device *pdev,
		  स्थिर काष्ठा dw_mipi_dsi_plat_data *plat_data)
अणु
	वापस __dw_mipi_dsi_probe(pdev, plat_data);
पूर्ण
EXPORT_SYMBOL_GPL(dw_mipi_dsi_probe);

व्योम dw_mipi_dsi_हटाओ(काष्ठा dw_mipi_dsi *dsi)
अणु
	__dw_mipi_dsi_हटाओ(dsi);
पूर्ण
EXPORT_SYMBOL_GPL(dw_mipi_dsi_हटाओ);

/*
 * Bind/unbind API, used from platक्रमms based on the component framework.
 */
पूर्णांक dw_mipi_dsi_bind(काष्ठा dw_mipi_dsi *dsi, काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक ret;

	ret = drm_bridge_attach(encoder, &dsi->bridge, शून्य, 0);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize bridge with drm\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dw_mipi_dsi_bind);

व्योम dw_mipi_dsi_unbind(काष्ठा dw_mipi_dsi *dsi)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(dw_mipi_dsi_unbind);

MODULE_AUTHOR("Chris Zhong <zyw@rock-chips.com>");
MODULE_AUTHOR("Philippe Cornu <philippe.cornu@st.com>");
MODULE_DESCRIPTION("DW MIPI DSI host controller driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:dw-mipi-dsi");
