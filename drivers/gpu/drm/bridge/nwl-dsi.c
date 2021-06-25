<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i.MX8 NWL MIPI DSI host driver
 *
 * Copyright (C) 2017 NXP
 * Copyright (C) 2020 Purism SPC
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/math64.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/समय64.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश <video/mipi_display.h>

#समावेश "nwl-dsi.h"

#घोषणा DRV_NAME "nwl-dsi"

/* i.MX8 NWL quirks */
/* i.MX8MQ errata E11418 */
#घोषणा E11418_HS_MODE_QUIRK	BIT(0)

#घोषणा NWL_DSI_MIPI_FIFO_TIMEOUT msecs_to_jअगरfies(500)

क्रमागत transfer_direction अणु
	DSI_PACKET_SEND,
	DSI_PACKET_RECEIVE,
पूर्ण;

#घोषणा NWL_DSI_ENDPOINT_LCDIF 0
#घोषणा NWL_DSI_ENDPOINT_DCSS 1

काष्ठा nwl_dsi_plat_clk_config अणु
	स्थिर अक्षर *id;
	काष्ठा clk *clk;
	bool present;
पूर्ण;

काष्ठा nwl_dsi_transfer अणु
	स्थिर काष्ठा mipi_dsi_msg *msg;
	काष्ठा mipi_dsi_packet packet;
	काष्ठा completion completed;

	पूर्णांक status; /* status of transmission */
	क्रमागत transfer_direction direction;
	bool need_bta;
	u8 cmd;
	u16 rx_word_count;
	माप_प्रकार tx_len; /* in bytes */
	माप_प्रकार rx_len; /* in bytes */
पूर्ण;

काष्ठा nwl_dsi अणु
	काष्ठा drm_bridge bridge;
	काष्ठा mipi_dsi_host dsi_host;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा device *dev;
	काष्ठा phy *phy;
	जोड़ phy_configure_opts phy_cfg;
	अचिन्हित पूर्णांक quirks;

	काष्ठा regmap *regmap;
	पूर्णांक irq;
	/*
	 * The DSI host controller needs this reset sequence according to NWL:
	 * 1. Deनिश्चित pclk reset to get access to DSI regs
	 * 2. Configure DSI Host and DPHY and enable DPHY
	 * 3. Deनिश्चित ESC and BYTE resets to allow host TX operations)
	 * 4. Send DSI cmds to configure peripheral (handled by panel drv)
	 * 5. Deनिश्चित DPI reset so DPI receives pixels and starts sending
	 *    DSI data
	 *
	 * TODO: Since panel_bridges करो their DSI setup in enable we
	 * currently have 4. and 5. swapped.
	 */
	काष्ठा reset_control *rst_byte;
	काष्ठा reset_control *rst_esc;
	काष्ठा reset_control *rst_dpi;
	काष्ठा reset_control *rst_pclk;
	काष्ठा mux_control *mux;

	/* DSI घड़ीs */
	काष्ठा clk *phy_ref_clk;
	काष्ठा clk *rx_esc_clk;
	काष्ठा clk *tx_esc_clk;
	काष्ठा clk *core_clk;
	/*
	 * hardware bug: the i.MX8MQ needs this घड़ी on during reset
	 * even when not using LCDIF.
	 */
	काष्ठा clk *lcdअगर_clk;

	/* dsi lanes */
	u32 lanes;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	काष्ठा drm_display_mode mode;
	अचिन्हित दीर्घ dsi_mode_flags;
	पूर्णांक error;

	काष्ठा nwl_dsi_transfer *xfer;
पूर्ण;

अटल स्थिर काष्ठा regmap_config nwl_dsi_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = NWL_DSI_IRQ_MASK2,
	.name = DRV_NAME,
पूर्ण;

अटल अंतरभूत काष्ठा nwl_dsi *bridge_to_dsi(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा nwl_dsi, bridge);
पूर्ण

अटल पूर्णांक nwl_dsi_clear_error(काष्ठा nwl_dsi *dsi)
अणु
	पूर्णांक ret = dsi->error;

	dsi->error = 0;
	वापस ret;
पूर्ण

अटल व्योम nwl_dsi_ग_लिखो(काष्ठा nwl_dsi *dsi, अचिन्हित पूर्णांक reg, u32 val)
अणु
	पूर्णांक ret;

	अगर (dsi->error)
		वापस;

	ret = regmap_ग_लिखो(dsi->regmap, reg, val);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev,
			      "Failed to write NWL DSI reg 0x%x: %d\n", reg,
			      ret);
		dsi->error = ret;
	पूर्ण
पूर्ण

अटल u32 nwl_dsi_पढ़ो(काष्ठा nwl_dsi *dsi, u32 reg)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (dsi->error)
		वापस 0;

	ret = regmap_पढ़ो(dsi->regmap, reg, &val);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to read NWL DSI reg 0x%x: %d\n",
			      reg, ret);
		dsi->error = ret;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक nwl_dsi_get_dpi_pixel_क्रमmat(क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB565:
		वापस NWL_DSI_PIXEL_FORMAT_16;
	हाल MIPI_DSI_FMT_RGB666:
		वापस NWL_DSI_PIXEL_FORMAT_18L;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		वापस NWL_DSI_PIXEL_FORMAT_18;
	हाल MIPI_DSI_FMT_RGB888:
		वापस NWL_DSI_PIXEL_FORMAT_24;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * ps2bc - Picoseconds to byte घड़ी cycles
 */
अटल u32 ps2bc(काष्ठा nwl_dsi *dsi, अचिन्हित दीर्घ दीर्घ ps)
अणु
	u32 bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat);

	वापस DIV64_U64_ROUND_UP(ps * dsi->mode.घड़ी * bpp,
				  dsi->lanes * 8 * NSEC_PER_SEC);
पूर्ण

/*
 * ui2bc - UI समय periods to byte घड़ी cycles
 */
अटल u32 ui2bc(काष्ठा nwl_dsi *dsi, अचिन्हित दीर्घ दीर्घ ui)
अणु
	u32 bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat);

	वापस DIV64_U64_ROUND_UP(ui * dsi->lanes,
				  dsi->mode.घड़ी * 1000 * bpp);
पूर्ण

/*
 * us2bc - micro seconds to lp घड़ी cycles
 */
अटल u32 us2lp(u32 lp_clk_rate, अचिन्हित दीर्घ us)
अणु
	वापस DIV_ROUND_UP(us * lp_clk_rate, USEC_PER_SEC);
पूर्ण

अटल पूर्णांक nwl_dsi_config_host(काष्ठा nwl_dsi *dsi)
अणु
	u32 cycles;
	काष्ठा phy_configure_opts_mipi_dphy *cfg = &dsi->phy_cfg.mipi_dphy;

	अगर (dsi->lanes < 1 || dsi->lanes > 4)
		वापस -EINVAL;

	DRM_DEV_DEBUG_DRIVER(dsi->dev, "DSI Lanes %d\n", dsi->lanes);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_NUM_LANES, dsi->lanes - 1);

	अगर (dsi->dsi_mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS) अणु
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_NONCONTINUOUS_CLK, 0x01);
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_AUTOINSERT_EOTP, 0x01);
	पूर्ण अन्यथा अणु
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_NONCONTINUOUS_CLK, 0x00);
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_AUTOINSERT_EOTP, 0x00);
	पूर्ण

	/* values in byte घड़ी cycles */
	cycles = ui2bc(dsi, cfg->clk_pre);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "cfg_t_pre: 0x%x\n", cycles);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_T_PRE, cycles);
	cycles = ps2bc(dsi, cfg->lpx + cfg->clk_prepare + cfg->clk_zero);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "cfg_tx_gap (pre): 0x%x\n", cycles);
	cycles += ui2bc(dsi, cfg->clk_pre);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "cfg_t_post: 0x%x\n", cycles);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_T_POST, cycles);
	cycles = ps2bc(dsi, cfg->hs_निकास);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "cfg_tx_gap: 0x%x\n", cycles);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_TX_GAP, cycles);

	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_EXTRA_CMDS_AFTER_EOTP, 0x01);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_HTX_TO_COUNT, 0x00);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_LRX_H_TO_COUNT, 0x00);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_BTA_H_TO_COUNT, 0x00);
	/* In LP घड़ी cycles */
	cycles = us2lp(cfg->lp_clk_rate, cfg->wakeup);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "cfg_twakeup: 0x%x\n", cycles);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_CFG_TWAKEUP, cycles);

	वापस nwl_dsi_clear_error(dsi);
पूर्ण

अटल पूर्णांक nwl_dsi_config_dpi(काष्ठा nwl_dsi *dsi)
अणु
	u32 mode;
	पूर्णांक color_क्रमmat;
	bool burst_mode;
	पूर्णांक hfront_porch, hback_porch, vfront_porch, vback_porch;
	पूर्णांक hsync_len, vsync_len;

	hfront_porch = dsi->mode.hsync_start - dsi->mode.hdisplay;
	hsync_len = dsi->mode.hsync_end - dsi->mode.hsync_start;
	hback_porch = dsi->mode.htotal - dsi->mode.hsync_end;

	vfront_porch = dsi->mode.vsync_start - dsi->mode.vdisplay;
	vsync_len = dsi->mode.vsync_end - dsi->mode.vsync_start;
	vback_porch = dsi->mode.vtotal - dsi->mode.vsync_end;

	DRM_DEV_DEBUG_DRIVER(dsi->dev, "hfront_porch = %d\n", hfront_porch);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "hback_porch = %d\n", hback_porch);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "hsync_len = %d\n", hsync_len);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "hdisplay = %d\n", dsi->mode.hdisplay);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "vfront_porch = %d\n", vfront_porch);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "vback_porch = %d\n", vback_porch);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "vsync_len = %d\n", vsync_len);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "vactive = %d\n", dsi->mode.vdisplay);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "clock = %d kHz\n", dsi->mode.घड़ी);

	color_क्रमmat = nwl_dsi_get_dpi_pixel_क्रमmat(dsi->क्रमmat);
	अगर (color_क्रमmat < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Invalid color format 0x%x\n",
			      dsi->क्रमmat);
		वापस color_क्रमmat;
	पूर्ण
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "pixel fmt = %d\n", dsi->क्रमmat);

	nwl_dsi_ग_लिखो(dsi, NWL_DSI_INTERFACE_COLOR_CODING, NWL_DSI_DPI_24_BIT);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_PIXEL_FORMAT, color_क्रमmat);
	/*
	 * Adjusting input polarity based on the video mode results in
	 * a black screen so always pick active low:
	 */
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_VSYNC_POLARITY,
		      NWL_DSI_VSYNC_POLARITY_ACTIVE_LOW);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_HSYNC_POLARITY,
		      NWL_DSI_HSYNC_POLARITY_ACTIVE_LOW);

	burst_mode = (dsi->dsi_mode_flags & MIPI_DSI_MODE_VIDEO_BURST) &&
		     !(dsi->dsi_mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE);

	अगर (burst_mode) अणु
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_VIDEO_MODE, NWL_DSI_VM_BURST_MODE);
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_PIXEL_FIFO_SEND_LEVEL, 256);
	पूर्ण अन्यथा अणु
		mode = ((dsi->dsi_mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) ?
				NWL_DSI_VM_BURST_MODE_WITH_SYNC_PULSES :
				NWL_DSI_VM_NON_BURST_MODE_WITH_SYNC_EVENTS);
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_VIDEO_MODE, mode);
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_PIXEL_FIFO_SEND_LEVEL,
			      dsi->mode.hdisplay);
	पूर्ण

	nwl_dsi_ग_लिखो(dsi, NWL_DSI_HFP, hfront_porch);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_HBP, hback_porch);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_HSA, hsync_len);

	nwl_dsi_ग_लिखो(dsi, NWL_DSI_ENABLE_MULT_PKTS, 0x0);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_BLLP_MODE, 0x1);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_USE_शून्य_PKT_BLLP, 0x0);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_VC, 0x0);

	nwl_dsi_ग_लिखो(dsi, NWL_DSI_PIXEL_PAYLOAD_SIZE, dsi->mode.hdisplay);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_VACTIVE, dsi->mode.vdisplay - 1);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_VBP, vback_porch);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_VFP, vfront_porch);

	वापस nwl_dsi_clear_error(dsi);
पूर्ण

अटल पूर्णांक nwl_dsi_init_पूर्णांकerrupts(काष्ठा nwl_dsi *dsi)
अणु
	u32 irq_enable;

	nwl_dsi_ग_लिखो(dsi, NWL_DSI_IRQ_MASK, 0xffffffff);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_IRQ_MASK2, 0x7);

	irq_enable = ~(u32)(NWL_DSI_TX_PKT_DONE_MASK |
			    NWL_DSI_RX_PKT_HDR_RCVD_MASK |
			    NWL_DSI_TX_FIFO_OVFLW_MASK |
			    NWL_DSI_HS_TX_TIMEOUT_MASK);

	nwl_dsi_ग_लिखो(dsi, NWL_DSI_IRQ_MASK, irq_enable);

	वापस nwl_dsi_clear_error(dsi);
पूर्ण

अटल पूर्णांक nwl_dsi_host_attach(काष्ठा mipi_dsi_host *dsi_host,
			       काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा nwl_dsi *dsi = container_of(dsi_host, काष्ठा nwl_dsi, dsi_host);
	काष्ठा device *dev = dsi->dev;

	DRM_DEV_INFO(dev, "lanes=%u, format=0x%x flags=0x%lx\n", device->lanes,
		     device->क्रमmat, device->mode_flags);

	अगर (device->lanes < 1 || device->lanes > 4)
		वापस -EINVAL;

	dsi->lanes = device->lanes;
	dsi->क्रमmat = device->क्रमmat;
	dsi->dsi_mode_flags = device->mode_flags;

	वापस 0;
पूर्ण

अटल bool nwl_dsi_पढ़ो_packet(काष्ठा nwl_dsi *dsi, u32 status)
अणु
	काष्ठा device *dev = dsi->dev;
	काष्ठा nwl_dsi_transfer *xfer = dsi->xfer;
	पूर्णांक err;
	u8 *payload = xfer->msg->rx_buf;
	u32 val;
	u16 word_count;
	u8 channel;
	u8 data_type;

	xfer->status = 0;

	अगर (xfer->rx_word_count == 0) अणु
		अगर (!(status & NWL_DSI_RX_PKT_HDR_RCVD))
			वापस false;
		/* Get the RX header and parse it */
		val = nwl_dsi_पढ़ो(dsi, NWL_DSI_RX_PKT_HEADER);
		err = nwl_dsi_clear_error(dsi);
		अगर (err)
			xfer->status = err;
		word_count = NWL_DSI_WC(val);
		channel = NWL_DSI_RX_VC(val);
		data_type = NWL_DSI_RX_DT(val);

		अगर (channel != xfer->msg->channel) अणु
			DRM_DEV_ERROR(dev,
				      "[%02X] Channel mismatch (%u != %u)\n",
				      xfer->cmd, channel, xfer->msg->channel);
			xfer->status = -EINVAL;
			वापस true;
		पूर्ण

		चयन (data_type) अणु
		हाल MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE:
		हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE:
			अगर (xfer->msg->rx_len > 1) अणु
				/* पढ़ो second byte */
				payload[1] = word_count >> 8;
				++xfer->rx_len;
			पूर्ण
			fallthrough;
		हाल MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE:
		हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE:
			अगर (xfer->msg->rx_len > 0) अणु
				/* पढ़ो first byte */
				payload[0] = word_count & 0xff;
				++xfer->rx_len;
			पूर्ण
			xfer->status = xfer->rx_len;
			वापस true;
		हाल MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT:
			word_count &= 0xff;
			DRM_DEV_ERROR(dev, "[%02X] DSI error report: 0x%02x\n",
				      xfer->cmd, word_count);
			xfer->status = -EPROTO;
			वापस true;
		पूर्ण

		अगर (word_count > xfer->msg->rx_len) अणु
			DRM_DEV_ERROR(dev,
				"[%02X] Receive buffer too small: %zu (< %u)\n",
				xfer->cmd, xfer->msg->rx_len, word_count);
			xfer->status = -EINVAL;
			वापस true;
		पूर्ण

		xfer->rx_word_count = word_count;
	पूर्ण अन्यथा अणु
		/* Set word_count from previous header पढ़ो */
		word_count = xfer->rx_word_count;
	पूर्ण

	/* If RX payload is not yet received, रुको क्रम it */
	अगर (!(status & NWL_DSI_RX_PKT_PAYLOAD_DATA_RCVD))
		वापस false;

	/* Read the RX payload */
	जबतक (word_count >= 4) अणु
		val = nwl_dsi_पढ़ो(dsi, NWL_DSI_RX_PAYLOAD);
		payload[0] = (val >> 0) & 0xff;
		payload[1] = (val >> 8) & 0xff;
		payload[2] = (val >> 16) & 0xff;
		payload[3] = (val >> 24) & 0xff;
		payload += 4;
		xfer->rx_len += 4;
		word_count -= 4;
	पूर्ण

	अगर (word_count > 0) अणु
		val = nwl_dsi_पढ़ो(dsi, NWL_DSI_RX_PAYLOAD);
		चयन (word_count) अणु
		हाल 3:
			payload[2] = (val >> 16) & 0xff;
			++xfer->rx_len;
			fallthrough;
		हाल 2:
			payload[1] = (val >> 8) & 0xff;
			++xfer->rx_len;
			fallthrough;
		हाल 1:
			payload[0] = (val >> 0) & 0xff;
			++xfer->rx_len;
			अवरोध;
		पूर्ण
	पूर्ण

	xfer->status = xfer->rx_len;
	err = nwl_dsi_clear_error(dsi);
	अगर (err)
		xfer->status = err;

	वापस true;
पूर्ण

अटल व्योम nwl_dsi_finish_transmission(काष्ठा nwl_dsi *dsi, u32 status)
अणु
	काष्ठा nwl_dsi_transfer *xfer = dsi->xfer;
	bool end_packet = false;

	अगर (!xfer)
		वापस;

	अगर (xfer->direction == DSI_PACKET_SEND &&
	    status & NWL_DSI_TX_PKT_DONE) अणु
		xfer->status = xfer->tx_len;
		end_packet = true;
	पूर्ण अन्यथा अगर (status & NWL_DSI_DPHY_सूचीECTION &&
		   ((status & (NWL_DSI_RX_PKT_HDR_RCVD |
			       NWL_DSI_RX_PKT_PAYLOAD_DATA_RCVD)))) अणु
		end_packet = nwl_dsi_पढ़ो_packet(dsi, status);
	पूर्ण

	अगर (end_packet)
		complete(&xfer->completed);
पूर्ण

अटल व्योम nwl_dsi_begin_transmission(काष्ठा nwl_dsi *dsi)
अणु
	काष्ठा nwl_dsi_transfer *xfer = dsi->xfer;
	काष्ठा mipi_dsi_packet *pkt = &xfer->packet;
	स्थिर u8 *payload;
	माप_प्रकार length;
	u16 word_count;
	u8 hs_mode;
	u32 val;
	u32 hs_workaround = 0;

	/* Send the payload, अगर any */
	length = pkt->payload_length;
	payload = pkt->payload;

	जबतक (length >= 4) अणु
		val = *(u32 *)payload;
		hs_workaround |= !(val & 0xFFFF00);
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_TX_PAYLOAD, val);
		payload += 4;
		length -= 4;
	पूर्ण
	/* Send the rest of the payload */
	val = 0;
	चयन (length) अणु
	हाल 3:
		val |= payload[2] << 16;
		fallthrough;
	हाल 2:
		val |= payload[1] << 8;
		hs_workaround |= !(val & 0xFFFF00);
		fallthrough;
	हाल 1:
		val |= payload[0];
		nwl_dsi_ग_लिखो(dsi, NWL_DSI_TX_PAYLOAD, val);
		अवरोध;
	पूर्ण
	xfer->tx_len = pkt->payload_length;

	/*
	 * Send the header
	 * header[0] = Virtual Channel + Data Type
	 * header[1] = Word Count LSB (LP) or first param (SP)
	 * header[2] = Word Count MSB (LP) or second param (SP)
	 */
	word_count = pkt->header[1] | (pkt->header[2] << 8);
	अगर (hs_workaround && (dsi->quirks & E11418_HS_MODE_QUIRK)) अणु
		DRM_DEV_DEBUG_DRIVER(dsi->dev,
				     "Using hs mode workaround for cmd 0x%x\n",
				     xfer->cmd);
		hs_mode = 1;
	पूर्ण अन्यथा अणु
		hs_mode = (xfer->msg->flags & MIPI_DSI_MSG_USE_LPM) ? 0 : 1;
	पूर्ण
	val = NWL_DSI_WC(word_count) | NWL_DSI_TX_VC(xfer->msg->channel) |
	      NWL_DSI_TX_DT(xfer->msg->type) | NWL_DSI_HS_SEL(hs_mode) |
	      NWL_DSI_BTA_TX(xfer->need_bta);
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_PKT_CONTROL, val);

	/* Send packet command */
	nwl_dsi_ग_लिखो(dsi, NWL_DSI_SEND_PACKET, 0x1);
पूर्ण

अटल sमाप_प्रकार nwl_dsi_host_transfer(काष्ठा mipi_dsi_host *dsi_host,
				     स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा nwl_dsi *dsi = container_of(dsi_host, काष्ठा nwl_dsi, dsi_host);
	काष्ठा nwl_dsi_transfer xfer;
	sमाप_प्रकार ret = 0;

	/* Create packet to be sent */
	dsi->xfer = &xfer;
	ret = mipi_dsi_create_packet(&xfer.packet, msg);
	अगर (ret < 0) अणु
		dsi->xfer = शून्य;
		वापस ret;
	पूर्ण

	अगर ((msg->type & MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM ||
	     msg->type & MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM ||
	     msg->type & MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM ||
	     msg->type & MIPI_DSI_DCS_READ) &&
	    msg->rx_len > 0 && msg->rx_buf)
		xfer.direction = DSI_PACKET_RECEIVE;
	अन्यथा
		xfer.direction = DSI_PACKET_SEND;

	xfer.need_bta = (xfer.direction == DSI_PACKET_RECEIVE);
	xfer.need_bta |= (msg->flags & MIPI_DSI_MSG_REQ_ACK) ? 1 : 0;
	xfer.msg = msg;
	xfer.status = -ETIMEDOUT;
	xfer.rx_word_count = 0;
	xfer.rx_len = 0;
	xfer.cmd = 0x00;
	अगर (msg->tx_len > 0)
		xfer.cmd = ((u8 *)(msg->tx_buf))[0];
	init_completion(&xfer.completed);

	ret = clk_prepare_enable(dsi->rx_esc_clk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to enable rx_esc clk: %zd\n",
			      ret);
		वापस ret;
	पूर्ण
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "Enabled rx_esc clk @%lu Hz\n",
			     clk_get_rate(dsi->rx_esc_clk));

	/* Initiate the DSI packet transmision */
	nwl_dsi_begin_transmission(dsi);

	अगर (!रुको_क्रम_completion_समयout(&xfer.completed,
					 NWL_DSI_MIPI_FIFO_TIMEOUT)) अणु
		DRM_DEV_ERROR(dsi_host->dev, "[%02X] DSI transfer timed out\n",
			      xfer.cmd);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = xfer.status;
	पूर्ण

	clk_disable_unprepare(dsi->rx_esc_clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops nwl_dsi_host_ops = अणु
	.attach = nwl_dsi_host_attach,
	.transfer = nwl_dsi_host_transfer,
पूर्ण;

अटल irqवापस_t nwl_dsi_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	u32 irq_status;
	काष्ठा nwl_dsi *dsi = data;

	irq_status = nwl_dsi_पढ़ो(dsi, NWL_DSI_IRQ_STATUS);

	अगर (irq_status & NWL_DSI_TX_FIFO_OVFLW)
		DRM_DEV_ERROR_RATELIMITED(dsi->dev, "tx fifo overflow\n");

	अगर (irq_status & NWL_DSI_HS_TX_TIMEOUT)
		DRM_DEV_ERROR_RATELIMITED(dsi->dev, "HS tx timeout\n");

	अगर (irq_status & NWL_DSI_TX_PKT_DONE ||
	    irq_status & NWL_DSI_RX_PKT_HDR_RCVD ||
	    irq_status & NWL_DSI_RX_PKT_PAYLOAD_DATA_RCVD)
		nwl_dsi_finish_transmission(dsi, irq_status);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nwl_dsi_enable(काष्ठा nwl_dsi *dsi)
अणु
	काष्ठा device *dev = dsi->dev;
	जोड़ phy_configure_opts *phy_cfg = &dsi->phy_cfg;
	पूर्णांक ret;

	अगर (!dsi->lanes) अणु
		DRM_DEV_ERROR(dev, "Need DSI lanes: %d\n", dsi->lanes);
		वापस -EINVAL;
	पूर्ण

	ret = phy_init(dsi->phy);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to init DSI phy: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = phy_configure(dsi->phy, phy_cfg);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to configure DSI phy: %d\n", ret);
		जाओ uninit_phy;
	पूर्ण

	ret = clk_prepare_enable(dsi->tx_esc_clk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to enable tx_esc clk: %d\n",
			      ret);
		जाओ uninit_phy;
	पूर्ण
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "Enabled tx_esc clk @%lu Hz\n",
			     clk_get_rate(dsi->tx_esc_clk));

	ret = nwl_dsi_config_host(dsi);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to set up DSI: %d", ret);
		जाओ disable_घड़ी;
	पूर्ण

	ret = nwl_dsi_config_dpi(dsi);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to set up DPI: %d", ret);
		जाओ disable_घड़ी;
	पूर्ण

	ret = phy_घातer_on(dsi->phy);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to power on DPHY (%d)\n", ret);
		जाओ disable_घड़ी;
	पूर्ण

	ret = nwl_dsi_init_पूर्णांकerrupts(dsi);
	अगर (ret < 0)
		जाओ घातer_off_phy;

	वापस ret;

घातer_off_phy:
	phy_घातer_off(dsi->phy);
disable_घड़ी:
	clk_disable_unprepare(dsi->tx_esc_clk);
uninit_phy:
	phy_निकास(dsi->phy);

	वापस ret;
पूर्ण

अटल पूर्णांक nwl_dsi_disable(काष्ठा nwl_dsi *dsi)
अणु
	काष्ठा device *dev = dsi->dev;

	DRM_DEV_DEBUG_DRIVER(dev, "Disabling clocks and phy\n");

	phy_घातer_off(dsi->phy);
	phy_निकास(dsi->phy);

	/* Disabling the घड़ी beक्रमe the phy अवरोधs enabling dsi again */
	clk_disable_unprepare(dsi->tx_esc_clk);

	वापस 0;
पूर्ण

अटल व्योम nwl_dsi_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा nwl_dsi *dsi = bridge_to_dsi(bridge);
	पूर्णांक ret;

	nwl_dsi_disable(dsi);

	ret = reset_control_निश्चित(dsi->rst_dpi);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to assert DPI: %d\n", ret);
		वापस;
	पूर्ण
	ret = reset_control_निश्चित(dsi->rst_byte);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to assert ESC: %d\n", ret);
		वापस;
	पूर्ण
	ret = reset_control_निश्चित(dsi->rst_esc);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to assert BYTE: %d\n", ret);
		वापस;
	पूर्ण
	ret = reset_control_निश्चित(dsi->rst_pclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to assert PCLK: %d\n", ret);
		वापस;
	पूर्ण

	clk_disable_unprepare(dsi->core_clk);
	clk_disable_unprepare(dsi->lcdअगर_clk);

	pm_runसमय_put(dsi->dev);
पूर्ण

अटल पूर्णांक nwl_dsi_get_dphy_params(काष्ठा nwl_dsi *dsi,
				   स्थिर काष्ठा drm_display_mode *mode,
				   जोड़ phy_configure_opts *phy_opts)
अणु
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	अगर (dsi->lanes < 1 || dsi->lanes > 4)
		वापस -EINVAL;

	/*
	 * So far the DPHY spec minimal timings work क्रम both mixel
	 * dphy and nwl dsi host
	 */
	ret = phy_mipi_dphy_get_शेष_config(mode->घड़ी * 1000,
		mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat), dsi->lanes,
		&phy_opts->mipi_dphy);
	अगर (ret < 0)
		वापस ret;

	rate = clk_get_rate(dsi->tx_esc_clk);
	DRM_DEV_DEBUG_DRIVER(dsi->dev, "LP clk is @%lu Hz\n", rate);
	phy_opts->mipi_dphy.lp_clk_rate = rate;

	वापस 0;
पूर्ण

अटल bool nwl_dsi_bridge_mode_fixup(काष्ठा drm_bridge *bridge,
				      स्थिर काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adjusted_mode)
अणु
	/* At least LCDIF + NWL needs active high sync */
	adjusted_mode->flags |= (DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC);
	adjusted_mode->flags &= ~(DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC);

	वापस true;
पूर्ण

अटल क्रमागत drm_mode_status
nwl_dsi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			  स्थिर काष्ठा drm_display_info *info,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा nwl_dsi *dsi = bridge_to_dsi(bridge);
	पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat);

	अगर (mode->घड़ी * bpp > 15000000 * dsi->lanes)
		वापस MODE_CLOCK_HIGH;

	अगर (mode->घड़ी * bpp < 80000 * dsi->lanes)
		वापस MODE_CLOCK_LOW;

	वापस MODE_OK;
पूर्ण

अटल व्योम
nwl_dsi_bridge_mode_set(काष्ठा drm_bridge *bridge,
			स्थिर काष्ठा drm_display_mode *mode,
			स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा nwl_dsi *dsi = bridge_to_dsi(bridge);
	काष्ठा device *dev = dsi->dev;
	जोड़ phy_configure_opts new_cfg;
	अचिन्हित दीर्घ phy_ref_rate;
	पूर्णांक ret;

	ret = nwl_dsi_get_dphy_params(dsi, adjusted_mode, &new_cfg);
	अगर (ret < 0)
		वापस;

	/*
	 * If hs घड़ी is unchanged, we're all good - all parameters are
	 * derived from it aपंचांग.
	 */
	अगर (new_cfg.mipi_dphy.hs_clk_rate == dsi->phy_cfg.mipi_dphy.hs_clk_rate)
		वापस;

	phy_ref_rate = clk_get_rate(dsi->phy_ref_clk);
	DRM_DEV_DEBUG_DRIVER(dev, "PHY at ref rate: %lu\n", phy_ref_rate);
	/* Save the new desired phy config */
	स_नकल(&dsi->phy_cfg, &new_cfg, माप(new_cfg));

	स_नकल(&dsi->mode, adjusted_mode, माप(dsi->mode));
	drm_mode_debug_prपूर्णांकmodeline(adjusted_mode);
पूर्ण

अटल व्योम nwl_dsi_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा nwl_dsi *dsi = bridge_to_dsi(bridge);
	पूर्णांक ret;

	pm_runसमय_get_sync(dsi->dev);

	अगर (clk_prepare_enable(dsi->lcdअगर_clk) < 0)
		वापस;
	अगर (clk_prepare_enable(dsi->core_clk) < 0)
		वापस;

	/* Step 1 from DSI reset-out inकाष्ठाions */
	ret = reset_control_deनिश्चित(dsi->rst_pclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to deassert PCLK: %d\n", ret);
		वापस;
	पूर्ण

	/* Step 2 from DSI reset-out inकाष्ठाions */
	nwl_dsi_enable(dsi);

	/* Step 3 from DSI reset-out inकाष्ठाions */
	ret = reset_control_deनिश्चित(dsi->rst_esc);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to deassert ESC: %d\n", ret);
		वापस;
	पूर्ण
	ret = reset_control_deनिश्चित(dsi->rst_byte);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to deassert BYTE: %d\n", ret);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम nwl_dsi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा nwl_dsi *dsi = bridge_to_dsi(bridge);
	पूर्णांक ret;

	/* Step 5 from DSI reset-out inकाष्ठाions */
	ret = reset_control_deनिश्चित(dsi->rst_dpi);
	अगर (ret < 0)
		DRM_DEV_ERROR(dsi->dev, "Failed to deassert DPI: %d\n", ret);
पूर्ण

अटल पूर्णांक nwl_dsi_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा nwl_dsi *dsi = bridge_to_dsi(bridge);
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	ret = drm_of_find_panel_or_bridge(dsi->dev->of_node, 1, 0, &panel,
					  &panel_bridge);
	अगर (ret)
		वापस ret;

	अगर (panel) अणु
		panel_bridge = drm_panel_bridge_add(panel);
		अगर (IS_ERR(panel_bridge))
			वापस PTR_ERR(panel_bridge);
	पूर्ण
	dsi->panel_bridge = panel_bridge;

	अगर (!dsi->panel_bridge)
		वापस -EPROBE_DEFER;

	वापस drm_bridge_attach(bridge->encoder, dsi->panel_bridge, bridge,
				 flags);
पूर्ण

अटल व्योम nwl_dsi_bridge_detach(काष्ठा drm_bridge *bridge)
अणु	काष्ठा nwl_dsi *dsi = bridge_to_dsi(bridge);

	drm_of_panel_bridge_हटाओ(dsi->dev->of_node, 1, 0);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs nwl_dsi_bridge_funcs = अणु
	.pre_enable = nwl_dsi_bridge_pre_enable,
	.enable     = nwl_dsi_bridge_enable,
	.disable    = nwl_dsi_bridge_disable,
	.mode_fixup = nwl_dsi_bridge_mode_fixup,
	.mode_set   = nwl_dsi_bridge_mode_set,
	.mode_valid = nwl_dsi_bridge_mode_valid,
	.attach	    = nwl_dsi_bridge_attach,
	.detach	    = nwl_dsi_bridge_detach,
पूर्ण;

अटल पूर्णांक nwl_dsi_parse_dt(काष्ठा nwl_dsi *dsi)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dsi->dev);
	काष्ठा clk *clk;
	व्योम __iomem *base;
	पूर्णांक ret;

	dsi->phy = devm_phy_get(dsi->dev, "dphy");
	अगर (IS_ERR(dsi->phy)) अणु
		ret = PTR_ERR(dsi->phy);
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dsi->dev, "Could not get PHY: %d\n", ret);
		वापस ret;
	पूर्ण

	clk = devm_clk_get(dsi->dev, "lcdif");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		DRM_DEV_ERROR(dsi->dev, "Failed to get lcdif clock: %d\n",
			      ret);
		वापस ret;
	पूर्ण
	dsi->lcdअगर_clk = clk;

	clk = devm_clk_get(dsi->dev, "core");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		DRM_DEV_ERROR(dsi->dev, "Failed to get core clock: %d\n",
			      ret);
		वापस ret;
	पूर्ण
	dsi->core_clk = clk;

	clk = devm_clk_get(dsi->dev, "phy_ref");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		DRM_DEV_ERROR(dsi->dev, "Failed to get phy_ref clock: %d\n",
			      ret);
		वापस ret;
	पूर्ण
	dsi->phy_ref_clk = clk;

	clk = devm_clk_get(dsi->dev, "rx_esc");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		DRM_DEV_ERROR(dsi->dev, "Failed to get rx_esc clock: %d\n",
			      ret);
		वापस ret;
	पूर्ण
	dsi->rx_esc_clk = clk;

	clk = devm_clk_get(dsi->dev, "tx_esc");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		DRM_DEV_ERROR(dsi->dev, "Failed to get tx_esc clock: %d\n",
			      ret);
		वापस ret;
	पूर्ण
	dsi->tx_esc_clk = clk;

	dsi->mux = devm_mux_control_get(dsi->dev, शून्य);
	अगर (IS_ERR(dsi->mux)) अणु
		ret = PTR_ERR(dsi->mux);
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dsi->dev, "Failed to get mux: %d\n", ret);
		वापस ret;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	dsi->regmap =
		devm_regmap_init_mmio(dsi->dev, base, &nwl_dsi_regmap_config);
	अगर (IS_ERR(dsi->regmap)) अणु
		ret = PTR_ERR(dsi->regmap);
		DRM_DEV_ERROR(dsi->dev, "Failed to create NWL DSI regmap: %d\n",
			      ret);
		वापस ret;
	पूर्ण

	dsi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dsi->irq < 0) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to get device IRQ: %d\n",
			      dsi->irq);
		वापस dsi->irq;
	पूर्ण

	dsi->rst_pclk = devm_reset_control_get_exclusive(dsi->dev, "pclk");
	अगर (IS_ERR(dsi->rst_pclk)) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to get pclk reset: %ld\n",
			      PTR_ERR(dsi->rst_pclk));
		वापस PTR_ERR(dsi->rst_pclk);
	पूर्ण
	dsi->rst_byte = devm_reset_control_get_exclusive(dsi->dev, "byte");
	अगर (IS_ERR(dsi->rst_byte)) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to get byte reset: %ld\n",
			      PTR_ERR(dsi->rst_byte));
		वापस PTR_ERR(dsi->rst_byte);
	पूर्ण
	dsi->rst_esc = devm_reset_control_get_exclusive(dsi->dev, "esc");
	अगर (IS_ERR(dsi->rst_esc)) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to get esc reset: %ld\n",
			      PTR_ERR(dsi->rst_esc));
		वापस PTR_ERR(dsi->rst_esc);
	पूर्ण
	dsi->rst_dpi = devm_reset_control_get_exclusive(dsi->dev, "dpi");
	अगर (IS_ERR(dsi->rst_dpi)) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to get dpi reset: %ld\n",
			      PTR_ERR(dsi->rst_dpi));
		वापस PTR_ERR(dsi->rst_dpi);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nwl_dsi_select_input(काष्ठा nwl_dsi *dsi)
अणु
	काष्ठा device_node *remote;
	u32 use_dcss = 1;
	पूर्णांक ret;

	remote = of_graph_get_remote_node(dsi->dev->of_node, 0,
					  NWL_DSI_ENDPOINT_LCDIF);
	अगर (remote) अणु
		use_dcss = 0;
	पूर्ण अन्यथा अणु
		remote = of_graph_get_remote_node(dsi->dev->of_node, 0,
						  NWL_DSI_ENDPOINT_DCSS);
		अगर (!remote) अणु
			DRM_DEV_ERROR(dsi->dev,
				      "No valid input endpoint found\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	DRM_DEV_INFO(dsi->dev, "Using %s as input source\n",
		     (use_dcss) ? "DCSS" : "LCDIF");
	ret = mux_control_try_select(dsi->mux, use_dcss);
	अगर (ret < 0)
		DRM_DEV_ERROR(dsi->dev, "Failed to select input: %d\n", ret);

	of_node_put(remote);
	वापस ret;
पूर्ण

अटल पूर्णांक nwl_dsi_deselect_input(काष्ठा nwl_dsi *dsi)
अणु
	पूर्णांक ret;

	ret = mux_control_deselect(dsi->mux);
	अगर (ret < 0)
		DRM_DEV_ERROR(dsi->dev, "Failed to deselect input: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_timings nwl_dsi_timings = अणु
	.input_bus_flags = DRM_BUS_FLAG_DE_LOW,
पूर्ण;

अटल स्थिर काष्ठा of_device_id nwl_dsi_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8mq-nwl-dsi", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nwl_dsi_dt_ids);

अटल स्थिर काष्ठा soc_device_attribute nwl_dsi_quirks_match[] = अणु
	अणु .soc_id = "i.MX8MQ", .revision = "2.0",
	  .data = (व्योम *)E11418_HS_MODE_QUIRK पूर्ण,
	अणु /* sentinel. */ पूर्ण,
पूर्ण;

अटल पूर्णांक nwl_dsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा soc_device_attribute *attr;
	काष्ठा nwl_dsi *dsi;
	पूर्णांक ret;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;

	dsi->dev = dev;

	ret = nwl_dsi_parse_dt(dsi);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(dev, dsi->irq, nwl_dsi_irq_handler, 0,
			       dev_name(dev), dsi);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to request IRQ %d: %d\n", dsi->irq,
			      ret);
		वापस ret;
	पूर्ण

	dsi->dsi_host.ops = &nwl_dsi_host_ops;
	dsi->dsi_host.dev = dev;
	ret = mipi_dsi_host_रेजिस्टर(&dsi->dsi_host);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Failed to register MIPI host: %d\n", ret);
		वापस ret;
	पूर्ण

	attr = soc_device_match(nwl_dsi_quirks_match);
	अगर (attr)
		dsi->quirks = (uपूर्णांकptr_t)attr->data;

	dsi->bridge.driver_निजी = dsi;
	dsi->bridge.funcs = &nwl_dsi_bridge_funcs;
	dsi->bridge.of_node = dev->of_node;
	dsi->bridge.timings = &nwl_dsi_timings;

	dev_set_drvdata(dev, dsi);
	pm_runसमय_enable(dev);

	ret = nwl_dsi_select_input(dsi);
	अगर (ret < 0) अणु
		mipi_dsi_host_unरेजिस्टर(&dsi->dsi_host);
		वापस ret;
	पूर्ण

	drm_bridge_add(&dsi->bridge);
	वापस 0;
पूर्ण

अटल पूर्णांक nwl_dsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nwl_dsi *dsi = platक्रमm_get_drvdata(pdev);

	nwl_dsi_deselect_input(dsi);
	mipi_dsi_host_unरेजिस्टर(&dsi->dsi_host);
	drm_bridge_हटाओ(&dsi->bridge);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver nwl_dsi_driver = अणु
	.probe		= nwl_dsi_probe,
	.हटाओ		= nwl_dsi_हटाओ,
	.driver		= अणु
		.of_match_table = nwl_dsi_dt_ids,
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(nwl_dsi_driver);

MODULE_AUTHOR("NXP Semiconductor");
MODULE_AUTHOR("Purism SPC");
MODULE_DESCRIPTION("Northwest Logic MIPI-DSI driver");
MODULE_LICENSE("GPL"); /* GPLv2 or later */
