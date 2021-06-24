<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2019-2020 Intel Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_bridge_connector.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "kmb_dsi.h"
#समावेश "kmb_regs.h"

अटल काष्ठा mipi_dsi_host *dsi_host;
अटल काष्ठा mipi_dsi_device *dsi_device;
अटल काष्ठा drm_bridge *adv_bridge;

/* Default setting is 1080p, 4 lanes */
#घोषणा IMG_HEIGHT_LINES  1080
#घोषणा IMG_WIDTH_PX      1920
#घोषणा MIPI_TX_ACTIVE_LANES 4

अटल काष्ठा mipi_tx_frame_section_cfg mipi_tx_frame0_sect_cfg = अणु
	.width_pixels = IMG_WIDTH_PX,
	.height_lines = IMG_HEIGHT_LINES,
	.data_type = DSI_LP_DT_PPS_RGB888_24B,
	.data_mode = MIPI_DATA_MODE1,
	.dma_packed = 0
पूर्ण;

अटल काष्ठा mipi_tx_frame_cfg mipitx_frame0_cfg = अणु
	.sections[0] = &mipi_tx_frame0_sect_cfg,
	.sections[1] = शून्य,
	.sections[2] = शून्य,
	.sections[3] = शून्य,
	.vsync_width = 5,
	.v_backporch = 36,
	.v_frontporch = 4,
	.hsync_width = 44,
	.h_backporch = 148,
	.h_frontporch = 88
पूर्ण;

अटल स्थिर काष्ठा mipi_tx_dsi_cfg mipitx_dsi_cfg = अणु
	.hfp_blank_en = 0,
	.eotp_en = 0,
	.lpm_last_vfp_line = 0,
	.lpm_first_vsa_line = 0,
	.sync_pulse_eventn = DSI_VIDEO_MODE_NO_BURST_EVENT,
	.hfp_blanking = SEND_BLANK_PACKET,
	.hbp_blanking = SEND_BLANK_PACKET,
	.hsa_blanking = SEND_BLANK_PACKET,
	.v_blanking = SEND_BLANK_PACKET,
पूर्ण;

अटल काष्ठा mipi_ctrl_cfg mipi_tx_init_cfg = अणु
	.active_lanes = MIPI_TX_ACTIVE_LANES,
	.lane_rate_mbps = MIPI_TX_LANE_DATA_RATE_MBPS,
	.ref_clk_khz = MIPI_TX_REF_CLK_KHZ,
	.cfg_clk_khz = MIPI_TX_CFG_CLK_KHZ,
	.tx_ctrl_cfg = अणु
			.frames[0] = &mipitx_frame0_cfg,
			.frames[1] = शून्य,
			.frames[2] = शून्य,
			.frames[3] = शून्य,
			.tx_dsi_cfg = &mipitx_dsi_cfg,
			.line_sync_pkt_en = 0,
			.line_counter_active = 0,
			.frame_counter_active = 0,
			.tx_always_use_hact = 1,
			.tx_hact_रुको_stop = 1,
			पूर्ण
पूर्ण;

काष्ठा  mipi_hs_freq_range_cfg अणु
	u16 शेष_bit_rate_mbps;
	u8 hsfreqrange_code;
पूर्ण;

काष्ठा vco_params अणु
	u32 freq;
	u32 range;
	u32 भागider;
पूर्ण;

अटल स्थिर काष्ठा vco_params vco_table[] = अणु
	अणु52, 0x3f, 8पूर्ण,
	अणु80, 0x39, 8पूर्ण,
	अणु105, 0x2f, 4पूर्ण,
	अणु160, 0x29, 4पूर्ण,
	अणु210, 0x1f, 2पूर्ण,
	अणु320, 0x19, 2पूर्ण,
	अणु420, 0x0f, 1पूर्ण,
	अणु630, 0x09, 1पूर्ण,
	अणु1100, 0x03, 1पूर्ण,
	अणु0xffff, 0x01, 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mipi_hs_freq_range_cfg
mipi_hs_freq_range[MIPI_DPHY_DEFAULT_BIT_RATES] = अणु
	अणु.शेष_bit_rate_mbps = 80, .hsfreqrange_code = 0x00पूर्ण,
	अणु.शेष_bit_rate_mbps = 90, .hsfreqrange_code = 0x10पूर्ण,
	अणु.शेष_bit_rate_mbps = 100, .hsfreqrange_code = 0x20पूर्ण,
	अणु.शेष_bit_rate_mbps = 110, .hsfreqrange_code = 0x30पूर्ण,
	अणु.शेष_bit_rate_mbps = 120, .hsfreqrange_code = 0x01पूर्ण,
	अणु.शेष_bit_rate_mbps = 130, .hsfreqrange_code = 0x11पूर्ण,
	अणु.शेष_bit_rate_mbps = 140, .hsfreqrange_code = 0x21पूर्ण,
	अणु.शेष_bit_rate_mbps = 150, .hsfreqrange_code = 0x31पूर्ण,
	अणु.शेष_bit_rate_mbps = 160, .hsfreqrange_code = 0x02पूर्ण,
	अणु.शेष_bit_rate_mbps = 170, .hsfreqrange_code = 0x12पूर्ण,
	अणु.शेष_bit_rate_mbps = 180, .hsfreqrange_code = 0x22पूर्ण,
	अणु.शेष_bit_rate_mbps = 190, .hsfreqrange_code = 0x32पूर्ण,
	अणु.शेष_bit_rate_mbps = 205, .hsfreqrange_code = 0x03पूर्ण,
	अणु.शेष_bit_rate_mbps = 220, .hsfreqrange_code = 0x13पूर्ण,
	अणु.शेष_bit_rate_mbps = 235, .hsfreqrange_code = 0x23पूर्ण,
	अणु.शेष_bit_rate_mbps = 250, .hsfreqrange_code = 0x33पूर्ण,
	अणु.शेष_bit_rate_mbps = 275, .hsfreqrange_code = 0x04पूर्ण,
	अणु.शेष_bit_rate_mbps = 300, .hsfreqrange_code = 0x14पूर्ण,
	अणु.शेष_bit_rate_mbps = 325, .hsfreqrange_code = 0x25पूर्ण,
	अणु.शेष_bit_rate_mbps = 350, .hsfreqrange_code = 0x35पूर्ण,
	अणु.शेष_bit_rate_mbps = 400, .hsfreqrange_code = 0x05पूर्ण,
	अणु.शेष_bit_rate_mbps = 450, .hsfreqrange_code = 0x16पूर्ण,
	अणु.शेष_bit_rate_mbps = 500, .hsfreqrange_code = 0x26पूर्ण,
	अणु.शेष_bit_rate_mbps = 550, .hsfreqrange_code = 0x37पूर्ण,
	अणु.शेष_bit_rate_mbps = 600, .hsfreqrange_code = 0x07पूर्ण,
	अणु.शेष_bit_rate_mbps = 650, .hsfreqrange_code = 0x18पूर्ण,
	अणु.शेष_bit_rate_mbps = 700, .hsfreqrange_code = 0x28पूर्ण,
	अणु.शेष_bit_rate_mbps = 750, .hsfreqrange_code = 0x39पूर्ण,
	अणु.शेष_bit_rate_mbps = 800, .hsfreqrange_code = 0x09पूर्ण,
	अणु.शेष_bit_rate_mbps = 850, .hsfreqrange_code = 0x19पूर्ण,
	अणु.शेष_bit_rate_mbps = 900, .hsfreqrange_code = 0x29पूर्ण,
	अणु.शेष_bit_rate_mbps = 1000, .hsfreqrange_code = 0x0Aपूर्ण,
	अणु.शेष_bit_rate_mbps = 1050, .hsfreqrange_code = 0x1Aपूर्ण,
	अणु.शेष_bit_rate_mbps = 1100, .hsfreqrange_code = 0x2Aपूर्ण,
	अणु.शेष_bit_rate_mbps = 1150, .hsfreqrange_code = 0x3Bपूर्ण,
	अणु.शेष_bit_rate_mbps = 1200, .hsfreqrange_code = 0x0Bपूर्ण,
	अणु.शेष_bit_rate_mbps = 1250, .hsfreqrange_code = 0x1Bपूर्ण,
	अणु.शेष_bit_rate_mbps = 1300, .hsfreqrange_code = 0x2Bपूर्ण,
	अणु.शेष_bit_rate_mbps = 1350, .hsfreqrange_code = 0x3Cपूर्ण,
	अणु.शेष_bit_rate_mbps = 1400, .hsfreqrange_code = 0x0Cपूर्ण,
	अणु.शेष_bit_rate_mbps = 1450, .hsfreqrange_code = 0x1Cपूर्ण,
	अणु.शेष_bit_rate_mbps = 1500, .hsfreqrange_code = 0x2Cपूर्ण,
	अणु.शेष_bit_rate_mbps = 1550, .hsfreqrange_code = 0x3Dपूर्ण,
	अणु.शेष_bit_rate_mbps = 1600, .hsfreqrange_code = 0x0Dपूर्ण,
	अणु.शेष_bit_rate_mbps = 1650, .hsfreqrange_code = 0x1Dपूर्ण,
	अणु.शेष_bit_rate_mbps = 1700, .hsfreqrange_code = 0x2Eपूर्ण,
	अणु.शेष_bit_rate_mbps = 1750, .hsfreqrange_code = 0x3Eपूर्ण,
	अणु.शेष_bit_rate_mbps = 1800, .hsfreqrange_code = 0x0Eपूर्ण,
	अणु.शेष_bit_rate_mbps = 1850, .hsfreqrange_code = 0x1Eपूर्ण,
	अणु.शेष_bit_rate_mbps = 1900, .hsfreqrange_code = 0x2Fपूर्ण,
	अणु.शेष_bit_rate_mbps = 1950, .hsfreqrange_code = 0x3Fपूर्ण,
	अणु.शेष_bit_rate_mbps = 2000, .hsfreqrange_code = 0x0Fपूर्ण,
	अणु.शेष_bit_rate_mbps = 2050, .hsfreqrange_code = 0x40पूर्ण,
	अणु.शेष_bit_rate_mbps = 2100, .hsfreqrange_code = 0x41पूर्ण,
	अणु.शेष_bit_rate_mbps = 2150, .hsfreqrange_code = 0x42पूर्ण,
	अणु.शेष_bit_rate_mbps = 2200, .hsfreqrange_code = 0x43पूर्ण,
	अणु.शेष_bit_rate_mbps = 2250, .hsfreqrange_code = 0x44पूर्ण,
	अणु.शेष_bit_rate_mbps = 2300, .hsfreqrange_code = 0x45पूर्ण,
	अणु.शेष_bit_rate_mbps = 2350, .hsfreqrange_code = 0x46पूर्ण,
	अणु.शेष_bit_rate_mbps = 2400, .hsfreqrange_code = 0x47पूर्ण,
	अणु.शेष_bit_rate_mbps = 2450, .hsfreqrange_code = 0x48पूर्ण,
	अणु.शेष_bit_rate_mbps = 2500, .hsfreqrange_code = 0x49पूर्ण
पूर्ण;

अटल व्योम kmb_dsi_clk_disable(काष्ठा kmb_dsi *kmb_dsi)
अणु
	clk_disable_unprepare(kmb_dsi->clk_mipi);
	clk_disable_unprepare(kmb_dsi->clk_mipi_ecfg);
	clk_disable_unprepare(kmb_dsi->clk_mipi_cfg);
पूर्ण

व्योम kmb_dsi_host_unरेजिस्टर(काष्ठा kmb_dsi *kmb_dsi)
अणु
	kmb_dsi_clk_disable(kmb_dsi);
	mipi_dsi_host_unरेजिस्टर(kmb_dsi->host);
पूर्ण

/*
 * This DSI can only be paired with bridges that करो config through i2c
 * which is ADV 7535 in the KMB EVM
 */
अटल sमाप_प्रकार kmb_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
				     स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक kmb_dsi_host_attach(काष्ठा mipi_dsi_host *host,
			       काष्ठा mipi_dsi_device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक kmb_dsi_host_detach(काष्ठा mipi_dsi_host *host,
			       काष्ठा mipi_dsi_device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops kmb_dsi_host_ops = अणु
	.attach = kmb_dsi_host_attach,
	.detach = kmb_dsi_host_detach,
	.transfer = kmb_dsi_host_transfer,
पूर्ण;

पूर्णांक kmb_dsi_host_bridge_init(काष्ठा device *dev)
अणु
	काष्ठा device_node *encoder_node, *dsi_out;

	/* Create and रेजिस्टर MIPI DSI host */
	अगर (!dsi_host) अणु
		dsi_host = kzalloc(माप(*dsi_host), GFP_KERNEL);
		अगर (!dsi_host)
			वापस -ENOMEM;

		dsi_host->ops = &kmb_dsi_host_ops;

		अगर (!dsi_device) अणु
			dsi_device = kzalloc(माप(*dsi_device), GFP_KERNEL);
			अगर (!dsi_device) अणु
				kमुक्त(dsi_host);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		dsi_host->dev = dev;
		mipi_dsi_host_रेजिस्टर(dsi_host);
	पूर्ण

	/* Find ADV7535 node and initialize it */
	dsi_out = of_graph_get_endpoपूर्णांक_by_regs(dev->of_node, 0, 1);
	अगर (!dsi_out) अणु
		DRM_ERROR("Failed to get dsi_out node info from DT\n");
		वापस -EINVAL;
	पूर्ण
	encoder_node = of_graph_get_remote_port_parent(dsi_out);
	अगर (!encoder_node) अणु
		of_node_put(dsi_out);
		DRM_ERROR("Failed to get bridge info from DT\n");
		वापस -EINVAL;
	पूर्ण
	/* Locate drm bridge from the hdmi encoder DT node */
	adv_bridge = of_drm_find_bridge(encoder_node);
	of_node_put(dsi_out);
	of_node_put(encoder_node);
	अगर (!adv_bridge) अणु
		DRM_DEBUG("Wait for external bridge driver DT\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 mipi_get_datatype_params(u32 data_type, u32 data_mode,
				    काष्ठा mipi_data_type_params *params)
अणु
	काष्ठा mipi_data_type_params data_type_param;

	चयन (data_type) अणु
	हाल DSI_LP_DT_PPS_YCBCR420_12B:
		data_type_param.size_स्थिरraपूर्णांक_pixels = 2;
		data_type_param.size_स्थिरraपूर्णांक_bytes = 3;
		चयन (data_mode) अणु
			/* Case 0 not supported according to MDK */
		हाल 1:
		हाल 2:
		हाल 3:
			data_type_param.pixels_per_pclk = 2;
			data_type_param.bits_per_pclk = 24;
			अवरोध;
		शेष:
			DRM_ERROR("DSI: Invalid data_mode %d\n", data_mode);
			वापस -EINVAL;
		पूर्ण;
		अवरोध;
	हाल DSI_LP_DT_PPS_YCBCR422_16B:
		data_type_param.size_स्थिरraपूर्णांक_pixels = 2;
		data_type_param.size_स्थिरraपूर्णांक_bytes = 4;
		चयन (data_mode) अणु
			/* Case 0 and 1 not supported according
			 * to MDK
			 */
		हाल 2:
			data_type_param.pixels_per_pclk = 1;
			data_type_param.bits_per_pclk = 16;
			अवरोध;
		हाल 3:
			data_type_param.pixels_per_pclk = 2;
			data_type_param.bits_per_pclk = 32;
			अवरोध;
		शेष:
			DRM_ERROR("DSI: Invalid data_mode %d\n", data_mode);
			वापस -EINVAL;
		पूर्ण;
		अवरोध;
	हाल DSI_LP_DT_LPPS_YCBCR422_20B:
	हाल DSI_LP_DT_PPS_YCBCR422_24B:
		data_type_param.size_स्थिरraपूर्णांक_pixels = 2;
		data_type_param.size_स्थिरraपूर्णांक_bytes = 6;
		चयन (data_mode) अणु
			/* Case 0 not supported according to MDK */
		हाल 1:
		हाल 2:
		हाल 3:
			data_type_param.pixels_per_pclk = 1;
			data_type_param.bits_per_pclk = 24;
			अवरोध;
		शेष:
			DRM_ERROR("DSI: Invalid data_mode %d\n", data_mode);
			वापस -EINVAL;
		पूर्ण;
		अवरोध;
	हाल DSI_LP_DT_PPS_RGB565_16B:
		data_type_param.size_स्थिरraपूर्णांक_pixels = 1;
		data_type_param.size_स्थिरraपूर्णांक_bytes = 2;
		चयन (data_mode) अणु
		हाल 0:
		हाल 1:
			data_type_param.pixels_per_pclk = 1;
			data_type_param.bits_per_pclk = 16;
			अवरोध;
		हाल 2:
		हाल 3:
			data_type_param.pixels_per_pclk = 2;
			data_type_param.bits_per_pclk = 32;
			अवरोध;
		शेष:
			DRM_ERROR("DSI: Invalid data_mode %d\n", data_mode);
			वापस -EINVAL;
		पूर्ण;
		अवरोध;
	हाल DSI_LP_DT_PPS_RGB666_18B:
		data_type_param.size_स्थिरraपूर्णांक_pixels = 4;
		data_type_param.size_स्थिरraपूर्णांक_bytes = 9;
		data_type_param.bits_per_pclk = 18;
		data_type_param.pixels_per_pclk = 1;
		अवरोध;
	हाल DSI_LP_DT_LPPS_RGB666_18B:
	हाल DSI_LP_DT_PPS_RGB888_24B:
		data_type_param.size_स्थिरraपूर्णांक_pixels = 1;
		data_type_param.size_स्थिरraपूर्णांक_bytes = 3;
		data_type_param.bits_per_pclk = 24;
		data_type_param.pixels_per_pclk = 1;
		अवरोध;
	हाल DSI_LP_DT_PPS_RGB101010_30B:
		data_type_param.size_स्थिरraपूर्णांक_pixels = 4;
		data_type_param.size_स्थिरraपूर्णांक_bytes = 15;
		data_type_param.bits_per_pclk = 30;
		data_type_param.pixels_per_pclk = 1;
		अवरोध;
	शेष:
		DRM_ERROR("DSI: Invalid data_type %d\n", data_type);
		वापस -EINVAL;
	पूर्ण;

	*params = data_type_param;
	वापस 0;
पूर्ण

अटल u32 compute_wc(u32 width_px, u8 size_स्थिरr_p, u8 size_स्थिरr_b)
अणु
	/* Calculate the word count क्रम each दीर्घ packet */
	वापस (((width_px / size_स्थिरr_p) * size_स्थिरr_b) & 0xffff);
पूर्ण

अटल u32 compute_unpacked_bytes(u32 wc, u8 bits_per_pclk)
अणु
	/* Number of PCLK cycles needed to transfer a line
	 * with each PCLK cycle, 4 Bytes are sent through the PPL module
	 */
	वापस ((wc * 8) / bits_per_pclk) * 4;
पूर्ण

अटल u32 mipi_tx_fg_section_cfg_regs(काष्ठा kmb_dsi *kmb_dsi,
				       u8 frame_id, u8 section,
				       u32 height_lines, u32 unpacked_bytes,
				       काष्ठा mipi_tx_frame_sect_phcfg *ph_cfg)
अणु
	u32 cfg = 0;
	u32 ctrl_no = MIPI_CTRL6;
	u32 reg_adr;

	/* Frame section packet header */
	/* Word count bits [15:0] */
	cfg = (ph_cfg->wc & MIPI_TX_SECT_WC_MASK) << 0;

	/* Data type (bits [21:16]) */
	cfg |= ((ph_cfg->data_type & MIPI_TX_SECT_DT_MASK)
		<< MIPI_TX_SECT_DT_SHIFT);

	/* Virtual channel (bits [23:22]) */
	cfg |= ((ph_cfg->vchannel & MIPI_TX_SECT_VC_MASK)
		<< MIPI_TX_SECT_VC_SHIFT);

	/* Data mode (bits [24:25]) */
	cfg |= ((ph_cfg->data_mode & MIPI_TX_SECT_DM_MASK)
		<< MIPI_TX_SECT_DM_SHIFT);
	अगर (ph_cfg->dma_packed)
		cfg |= MIPI_TX_SECT_DMA_PACKED;

	dev_dbg(kmb_dsi->dev,
		"ctrl=%d frame_id=%d section=%d cfg=%x packed=%d\n",
		  ctrl_no, frame_id, section, cfg, ph_cfg->dma_packed);
	kmb_ग_लिखो_mipi(kmb_dsi,
		       (MIPI_TXm_HS_FGn_SECTo_PH(ctrl_no, frame_id, section)),
		       cfg);

	/* Unpacked bytes */

	/* There are 4 frame generators and each fg has 4 sections
	 * There are 2 रेजिस्टरs क्रम unpacked bytes (# bytes each
	 * section occupies in memory)
	 * REG_UNPACKED_BYTES0: [15:0]-BYTES0, [31:16]-BYTES1
	 * REG_UNPACKED_BYTES1: [15:0]-BYTES2, [31:16]-BYTES3
	 */
	reg_adr =
	    MIPI_TXm_HS_FGn_SECT_UNPACKED_BYTES0(ctrl_no,
						 frame_id) + (section / 2) * 4;
	kmb_ग_लिखो_bits_mipi(kmb_dsi, reg_adr, (section % 2) * 16, 16,
			    unpacked_bytes);
	dev_dbg(kmb_dsi->dev,
		"unpacked_bytes = %d, wordcount = %d\n", unpacked_bytes,
		  ph_cfg->wc);

	/* Line config */
	reg_adr = MIPI_TXm_HS_FGn_SECTo_LINE_CFG(ctrl_no, frame_id, section);
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr, height_lines);
	वापस 0;
पूर्ण

अटल u32 mipi_tx_fg_section_cfg(काष्ठा kmb_dsi *kmb_dsi,
				  u8 frame_id, u8 section,
				  काष्ठा mipi_tx_frame_section_cfg *frame_scfg,
				  u32 *bits_per_pclk, u32 *wc)
अणु
	u32 ret = 0;
	u32 unpacked_bytes;
	काष्ठा mipi_data_type_params data_type_parameters;
	काष्ठा mipi_tx_frame_sect_phcfg ph_cfg;

	ret = mipi_get_datatype_params(frame_scfg->data_type,
				       frame_scfg->data_mode,
				       &data_type_parameters);
	अगर (ret)
		वापस ret;

	/* Packet width has to be a multiple of the minimum packet width
	 * (in pixels) set क्रम each data type
	 */
	अगर (frame_scfg->width_pixels %
	    data_type_parameters.size_स्थिरraपूर्णांक_pixels != 0)
		वापस -EINVAL;

	*wc = compute_wc(frame_scfg->width_pixels,
			 data_type_parameters.size_स्थिरraपूर्णांक_pixels,
			 data_type_parameters.size_स्थिरraपूर्णांक_bytes);
	unpacked_bytes = compute_unpacked_bytes(*wc,
						data_type_parameters.bits_per_pclk);
	ph_cfg.wc = *wc;
	ph_cfg.data_mode = frame_scfg->data_mode;
	ph_cfg.data_type = frame_scfg->data_type;
	ph_cfg.dma_packed = frame_scfg->dma_packed;
	ph_cfg.vchannel = frame_id;

	mipi_tx_fg_section_cfg_regs(kmb_dsi, frame_id, section,
				    frame_scfg->height_lines,
				    unpacked_bytes, &ph_cfg);

	/* Caller needs bits_per_clk क्रम additional caluclations */
	*bits_per_pclk = data_type_parameters.bits_per_pclk;

	वापस 0;
पूर्ण

अटल व्योम mipi_tx_fg_cfg_regs(काष्ठा kmb_dsi *kmb_dsi, u8 frame_gen,
				काष्ठा mipi_tx_frame_timing_cfg *fg_cfg)
अणु
	u32 sysclk;
	u32 ppl_llp_ratio;
	u32 ctrl_no = MIPI_CTRL6, reg_adr, val, offset;

	/* 500 Mhz प्रणाली घड़ी minus 50 to account क्रम the dअगरference in
	 * MIPI घड़ी speed in RTL tests
	 */
	sysclk = kmb_dsi->sys_clk_mhz - 50;

	/* PPL-Pixel Packing Layer, LLP-Low Level Protocol
	 * Frame genartor timing parameters are घड़ीed on the प्रणाली घड़ी,
	 * whereas as the equivalent parameters in the LLP blocks are घड़ीed
	 * on LLP Tx घड़ी from the D-PHY - BYTE घड़ी
	 */

	/* Multiply by 1000 to मुख्यtain precision */
	ppl_llp_ratio = ((fg_cfg->bpp / 8) * sysclk * 1000) /
	    ((fg_cfg->lane_rate_mbps / 8) * fg_cfg->active_lanes);

	dev_dbg(kmb_dsi->dev, "ppl_llp_ratio=%d\n", ppl_llp_ratio);
	dev_dbg(kmb_dsi->dev, "bpp=%d sysclk=%d lane-rate=%d active-lanes=%d\n",
		fg_cfg->bpp, sysclk, fg_cfg->lane_rate_mbps,
		 fg_cfg->active_lanes);

	/* Frame generator number of lines */
	reg_adr = MIPI_TXm_HS_FGn_NUM_LINES(ctrl_no, frame_gen);
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr, fg_cfg->v_active);

	/* vsync width
	 * There are 2 रेजिस्टरs क्रम vsync width (VSA in lines क्रम
	 * channels 0-3)
	 * REG_VSYNC_WIDTH0: [15:0]-VSA क्रम channel0, [31:16]-VSA क्रम channel1
	 * REG_VSYNC_WIDTH1: [15:0]-VSA क्रम channel2, [31:16]-VSA क्रम channel3
	 */
	offset = (frame_gen % 2) * 16;
	reg_adr = MIPI_TXm_HS_VSYNC_WIDTHn(ctrl_no, frame_gen / 2);
	kmb_ग_लिखो_bits_mipi(kmb_dsi, reg_adr, offset, 16, fg_cfg->vsync_width);

	/* vertical backporch (vbp) */
	reg_adr = MIPI_TXm_HS_V_BACKPORCHESn(ctrl_no, frame_gen / 2);
	kmb_ग_लिखो_bits_mipi(kmb_dsi, reg_adr, offset, 16, fg_cfg->v_backporch);

	/* vertical frontporch (vfp) */
	reg_adr = MIPI_TXm_HS_V_FRONTPORCHESn(ctrl_no, frame_gen / 2);
	kmb_ग_लिखो_bits_mipi(kmb_dsi, reg_adr, offset, 16, fg_cfg->v_frontporch);

	/* vertical active (vactive) */
	reg_adr = MIPI_TXm_HS_V_ACTIVEn(ctrl_no, frame_gen / 2);
	kmb_ग_लिखो_bits_mipi(kmb_dsi, reg_adr, offset, 16, fg_cfg->v_active);

	/* hsync width */
	reg_adr = MIPI_TXm_HS_HSYNC_WIDTHn(ctrl_no, frame_gen);
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr,
		       (fg_cfg->hsync_width * ppl_llp_ratio) / 1000);

	/* horizontal backporch (hbp) */
	reg_adr = MIPI_TXm_HS_H_BACKPORCHn(ctrl_no, frame_gen);
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr,
		       (fg_cfg->h_backporch * ppl_llp_ratio) / 1000);

	/* horizontal frontporch (hfp) */
	reg_adr = MIPI_TXm_HS_H_FRONTPORCHn(ctrl_no, frame_gen);
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr,
		       (fg_cfg->h_frontporch * ppl_llp_ratio) / 1000);

	/* horizontal active (ha) */
	reg_adr = MIPI_TXm_HS_H_ACTIVEn(ctrl_no, frame_gen);

	/* convert h_active which is wc in bytes to cycles */
	val = (fg_cfg->h_active * sysclk * 1000) /
	    ((fg_cfg->lane_rate_mbps / 8) * fg_cfg->active_lanes);
	val /= 1000;
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr, val);

	/* llp hsync width */
	reg_adr = MIPI_TXm_HS_LLP_HSYNC_WIDTHn(ctrl_no, frame_gen);
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr, fg_cfg->hsync_width * (fg_cfg->bpp / 8));

	/* llp h backporch */
	reg_adr = MIPI_TXm_HS_LLP_H_BACKPORCHn(ctrl_no, frame_gen);
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr, fg_cfg->h_backporch * (fg_cfg->bpp / 8));

	/* llp h frontporch */
	reg_adr = MIPI_TXm_HS_LLP_H_FRONTPORCHn(ctrl_no, frame_gen);
	kmb_ग_लिखो_mipi(kmb_dsi, reg_adr,
		       fg_cfg->h_frontporch * (fg_cfg->bpp / 8));
पूर्ण

अटल व्योम mipi_tx_fg_cfg(काष्ठा kmb_dsi *kmb_dsi, u8 frame_gen,
			   u8 active_lanes, u32 bpp, u32 wc,
			   u32 lane_rate_mbps, काष्ठा mipi_tx_frame_cfg *fg_cfg)
अणु
	u32 i, fg_num_lines = 0;
	काष्ठा mipi_tx_frame_timing_cfg fg_t_cfg;

	/* Calculate the total frame generator number of
	 * lines based on it's active sections
	 */
	क्रम (i = 0; i < MIPI_TX_FRAME_GEN_SECTIONS; i++) अणु
		अगर (fg_cfg->sections[i])
			fg_num_lines += fg_cfg->sections[i]->height_lines;
	पूर्ण

	fg_t_cfg.bpp = bpp;
	fg_t_cfg.lane_rate_mbps = lane_rate_mbps;
	fg_t_cfg.hsync_width = fg_cfg->hsync_width;
	fg_t_cfg.h_backporch = fg_cfg->h_backporch;
	fg_t_cfg.h_frontporch = fg_cfg->h_frontporch;
	fg_t_cfg.h_active = wc;
	fg_t_cfg.vsync_width = fg_cfg->vsync_width;
	fg_t_cfg.v_backporch = fg_cfg->v_backporch;
	fg_t_cfg.v_frontporch = fg_cfg->v_frontporch;
	fg_t_cfg.v_active = fg_num_lines;
	fg_t_cfg.active_lanes = active_lanes;

	/* Apply frame generator timing setting */
	mipi_tx_fg_cfg_regs(kmb_dsi, frame_gen, &fg_t_cfg);
पूर्ण

अटल व्योम mipi_tx_multichannel_fअगरo_cfg(काष्ठा kmb_dsi *kmb_dsi,
					  u8 active_lanes, u8 vchannel_id)
अणु
	u32 fअगरo_size, fअगरo_rthreshold;
	u32 ctrl_no = MIPI_CTRL6;

	/* Clear all mc fअगरo channel sizes and thresholds */
	kmb_ग_लिखो_mipi(kmb_dsi, MIPI_TX_HS_MC_FIFO_CTRL_EN, 0);
	kmb_ग_लिखो_mipi(kmb_dsi, MIPI_TX_HS_MC_FIFO_CHAN_ALLOC0, 0);
	kmb_ग_लिखो_mipi(kmb_dsi, MIPI_TX_HS_MC_FIFO_CHAN_ALLOC1, 0);
	kmb_ग_लिखो_mipi(kmb_dsi, MIPI_TX_HS_MC_FIFO_RTHRESHOLD0, 0);
	kmb_ग_लिखो_mipi(kmb_dsi, MIPI_TX_HS_MC_FIFO_RTHRESHOLD1, 0);

	fअगरo_size = ((active_lanes > MIPI_D_LANES_PER_DPHY) ?
		     MIPI_CTRL_4LANE_MAX_MC_FIFO_LOC :
		     MIPI_CTRL_2LANE_MAX_MC_FIFO_LOC) - 1;

	/* MC fअगरo size क्रम भव channels 0-3
	 * REG_MC_FIFO_CHAN_ALLOC0: [8:0]-channel0, [24:16]-channel1
	 * REG_MC_FIFO_CHAN_ALLOC1: [8:0]-2, [24:16]-channel3
	 */
	SET_MC_FIFO_CHAN_ALLOC(kmb_dsi, ctrl_no, vchannel_id, fअगरo_size);

	/* Set threshold to half the fअगरo size, actual size=size*16 */
	fअगरo_rthreshold = ((fअगरo_size) * 8) & BIT_MASK_16;
	SET_MC_FIFO_RTHRESHOLD(kmb_dsi, ctrl_no, vchannel_id, fअगरo_rthreshold);

	/* Enable the MC FIFO channel corresponding to the Virtual Channel */
	kmb_set_bit_mipi(kmb_dsi, MIPI_TXm_HS_MC_FIFO_CTRL_EN(ctrl_no),
			 vchannel_id);
पूर्ण

अटल व्योम mipi_tx_ctrl_cfg(काष्ठा kmb_dsi *kmb_dsi, u8 fg_id,
			     काष्ठा mipi_ctrl_cfg *ctrl_cfg)
अणु
	u32 sync_cfg = 0, ctrl = 0, fg_en;
	u32 ctrl_no = MIPI_CTRL6;

	/* MIPI_TX_HS_SYNC_CFG */
	अगर (ctrl_cfg->tx_ctrl_cfg.line_sync_pkt_en)
		sync_cfg |= LINE_SYNC_PKT_ENABLE;
	अगर (ctrl_cfg->tx_ctrl_cfg.frame_counter_active)
		sync_cfg |= FRAME_COUNTER_ACTIVE;
	अगर (ctrl_cfg->tx_ctrl_cfg.line_counter_active)
		sync_cfg |= LINE_COUNTER_ACTIVE;
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->v_blanking)
		sync_cfg |= DSI_V_BLANKING;
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->hsa_blanking)
		sync_cfg |= DSI_HSA_BLANKING;
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->hbp_blanking)
		sync_cfg |= DSI_HBP_BLANKING;
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->hfp_blanking)
		sync_cfg |= DSI_HFP_BLANKING;
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->sync_pulse_eventn)
		sync_cfg |= DSI_SYNC_PULSE_EVENTN;
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->lpm_first_vsa_line)
		sync_cfg |= DSI_LPM_FIRST_VSA_LINE;
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->lpm_last_vfp_line)
		sync_cfg |= DSI_LPM_LAST_VFP_LINE;

	/* Enable frame generator */
	fg_en = 1 << fg_id;
	sync_cfg |= FRAME_GEN_EN(fg_en);

	अगर (ctrl_cfg->tx_ctrl_cfg.tx_always_use_hact)
		sync_cfg |= ALWAYS_USE_HACT(fg_en);
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_hact_रुको_stop)
		sync_cfg |= HACT_WAIT_STOP(fg_en);

	dev_dbg(kmb_dsi->dev, "sync_cfg=%d fg_en=%d\n", sync_cfg, fg_en);

	/* MIPI_TX_HS_CTRL */

	/* type:DSI, source:LCD */
	ctrl = HS_CTRL_EN | TX_SOURCE;
	ctrl |= LCD_VC(fg_id);
	ctrl |= ACTIVE_LANES(ctrl_cfg->active_lanes - 1);
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->eotp_en)
		ctrl |= DSI_EOTP_EN;
	अगर (ctrl_cfg->tx_ctrl_cfg.tx_dsi_cfg->hfp_blank_en)
		ctrl |= DSI_CMD_HFP_EN;

	/*67 ns stop समय */
	ctrl |= HSEXIT_CNT(0x43);

	kmb_ग_लिखो_mipi(kmb_dsi, MIPI_TXm_HS_SYNC_CFG(ctrl_no), sync_cfg);
	kmb_ग_लिखो_mipi(kmb_dsi, MIPI_TXm_HS_CTRL(ctrl_no), ctrl);
पूर्ण

अटल u32 mipi_tx_init_cntrl(काष्ठा kmb_dsi *kmb_dsi,
			      काष्ठा mipi_ctrl_cfg *ctrl_cfg)
अणु
	u32 ret = 0;
	u8 active_vchannels = 0;
	u8 frame_id, sect;
	u32 bits_per_pclk = 0;
	u32 word_count = 0;
	काष्ठा mipi_tx_frame_cfg *frame;

	/* This is the order to initialize MIPI TX:
	 * 1. set frame section parameters
	 * 2. set frame specअगरic parameters
	 * 3. connect lcd to mipi
	 * 4. multi channel fअगरo cfg
	 * 5. set mipitxcctrlcfg
	 */

	क्रम (frame_id = 0; frame_id < 4; frame_id++) अणु
		frame = ctrl_cfg->tx_ctrl_cfg.frames[frame_id];

		/* Find valid frame, assume only one valid frame */
		अगर (!frame)
			जारी;

		/* Frame Section configuration */
		/* TODO - assume there is only one valid section in a frame,
		 * so bits_per_pclk and word_count are only set once
		 */
		क्रम (sect = 0; sect < MIPI_CTRL_VIRTUAL_CHANNELS; sect++) अणु
			अगर (!frame->sections[sect])
				जारी;

			ret = mipi_tx_fg_section_cfg(kmb_dsi, frame_id, sect,
						     frame->sections[sect],
						     &bits_per_pclk,
						     &word_count);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* Set frame specअगरic parameters */
		mipi_tx_fg_cfg(kmb_dsi, frame_id, ctrl_cfg->active_lanes,
			       bits_per_pclk, word_count,
			       ctrl_cfg->lane_rate_mbps, frame);

		active_vchannels++;

		/* Stop iterating as only one भव channel
		 * shall be used क्रम LCD connection
		 */
		अवरोध;
	पूर्ण

	अगर (active_vchannels == 0)
		वापस -EINVAL;
	/* Multi-Channel FIFO Configuration */
	mipi_tx_multichannel_fअगरo_cfg(kmb_dsi, ctrl_cfg->active_lanes, frame_id);

	/* Frame Generator Enable */
	mipi_tx_ctrl_cfg(kmb_dsi, frame_id, ctrl_cfg);

	वापस ret;
पूर्ण

अटल व्योम test_mode_send(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no,
			   u32 test_code, u32 test_data)
अणु
	/* Steps to send test code:
	 * - set testclk HIGH
	 * - set teमानक_निवेश with test code
	 * - set testen HIGH
	 * - set testclk LOW
	 * - set testen LOW
	 */

	/* Set testclk high */
	SET_DPHY_TEST_CTRL1_CLK(kmb_dsi, dphy_no);

	/* Set teमानक_निवेश */
	SET_TEST_DIN0_3(kmb_dsi, dphy_no, test_code);

	/* Set testen high */
	SET_DPHY_TEST_CTRL1_EN(kmb_dsi, dphy_no);

	/* Set testclk low */
	CLR_DPHY_TEST_CTRL1_CLK(kmb_dsi, dphy_no);

	/* Set testen low */
	CLR_DPHY_TEST_CTRL1_EN(kmb_dsi, dphy_no);

	अगर (test_code) अणु
		/*  Steps to send test data:
		 * - set testen LOW
		 * - set testclk LOW
		 * - set teमानक_निवेश with data
		 * - set testclk HIGH
		 */

		/* Set testen low */
		CLR_DPHY_TEST_CTRL1_EN(kmb_dsi, dphy_no);

		/* Set testclk low */
		CLR_DPHY_TEST_CTRL1_CLK(kmb_dsi, dphy_no);

		/* Set data in teमानक_निवेश */
		kmb_ग_लिखो_mipi(kmb_dsi,
			       DPHY_TEST_DIN0_3 + ((dphy_no / 0x4) * 0x4),
			       test_data << ((dphy_no % 4) * 8));

		/* Set testclk high */
		SET_DPHY_TEST_CTRL1_CLK(kmb_dsi, dphy_no);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
	set_test_mode_src_osc_freq_target_low_bits(काष्ठा kmb_dsi *kmb_dsi,
						   u32 dphy_no,
						   u32 freq)
अणु
	/* Typical rise/fall समय=166, refer Table 1207 databook,
	 * sr_osc_freq_target[7:0]
	 */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_SLEW_RATE_DDL_CYCLES,
		       (freq & 0x7f));
पूर्ण

अटल अंतरभूत व्योम
	set_test_mode_src_osc_freq_target_hi_bits(काष्ठा kmb_dsi *kmb_dsi,
						  u32 dphy_no,
						  u32 freq)
अणु
	u32 data;

	/* Flag this as high nibble */
	data = ((freq >> 6) & 0x1f) | (1 << 7);

	/* Typical rise/fall समय=166, refer Table 1207 databook,
	 * sr_osc_freq_target[11:7]
	 */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_SLEW_RATE_DDL_CYCLES, data);
पूर्ण

अटल व्योम mipi_tx_get_vco_params(काष्ठा vco_params *vco)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vco_table); i++) अणु
		अगर (vco->freq < vco_table[i].freq) अणु
			*vco = vco_table[i];
			वापस;
		पूर्ण
	पूर्ण

	WARN_ONCE(1, "Invalid vco freq = %u for PLL setup\n", vco->freq);
पूर्ण

अटल व्योम mipi_tx_pll_setup(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no,
			      u32 ref_clk_mhz, u32 target_freq_mhz)
अणु
	u32 best_n = 0, best_m = 0;
	u32 n = 0, m = 0, भाग = 0, delta, freq = 0, t_freq;
	u32 best_freq_delta = 3000;

	/* pll_ref_clk: - valid range: 2~64 MHz; Typically 24 MHz
	 * Fvco: - valid range: 320~1250 MHz (Gen3 D-PHY)
	 * Fout: - valid range: 40~1250 MHz (Gen3 D-PHY)
	 * n: - valid range [0 15]
	 * N: - N = n + 1
	 *      -valid range: [1 16]
	 *      -conditions: - (pll_ref_clk / N) >= 2 MHz
	 *             -(pll_ref_clk / N) <= 8 MHz
	 * m: valid range [62 623]
	 * M: - M = m + 2
	 *      -valid range [64 625]
	 *      -Fvco = (M/N) * pll_ref_clk
	 */
	काष्ठा vco_params vco_p = अणु
		.range = 0,
		.भागider = 1,
	पूर्ण;

	vco_p.freq = target_freq_mhz;
	mipi_tx_get_vco_params(&vco_p);

	/* Search pll n parameter */
	क्रम (n = PLL_N_MIN; n <= PLL_N_MAX; n++) अणु
		/* Calculate the pll input frequency भागision ratio
		 * multiply by 1000 क्रम precision -
		 * no भग्नing poपूर्णांक, add n क्रम rounding
		 */
		भाग = ((ref_clk_mhz * 1000) + n) / (n + 1);

		/* Found a valid n parameter */
		अगर ((भाग < 2000 || भाग > 8000))
			जारी;

		/* Search pll m parameter */
		क्रम (m = PLL_M_MIN; m <= PLL_M_MAX; m++) अणु
			/* Calculate the Fvco(DPHY PLL output frequency)
			 * using the current n,m params
			 */
			freq = भाग * (m + 2);
			freq /= 1000;

			/* Trim the potential pll freq to max supported */
			अगर (freq > PLL_FVCO_MAX)
				जारी;

			delta = असल(freq - target_freq_mhz);

			/* Select the best (बंदst to target pll freq)
			 * n,m parameters so far
			 */
			अगर (delta < best_freq_delta) अणु
				best_n = n;
				best_m = m;
				best_freq_delta = delta;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Program vco_cntrl parameter
	 * PLL_VCO_Control[5:0] = pll_vco_cntrl_ovr,
	 * PLL_VCO_Control[6]   = pll_vco_cntrl_ovr_en
	 */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_VCO_CTRL, (vco_p.range
								| (1 << 6)));

	/* Program m, n pll parameters */
	dev_dbg(kmb_dsi->dev, "m = %d n = %d\n", best_m, best_n);

	/* PLL_Input_Divider_Ratio[3:0] = pll_n_ovr */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_INPUT_DIVIDER,
		       (best_n & 0x0f));

	/* m - low nibble PLL_Loop_Divider_Ratio[4:0]
	 * pll_m_ovr[4:0]
	 */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_FEEDBACK_DIVIDER,
		       (best_m & 0x1f));

	/* m - high nibble PLL_Loop_Divider_Ratio[4:0]
	 * pll_m_ovr[9:5]
	 */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_FEEDBACK_DIVIDER,
		       ((best_m >> 5) & 0x1f) | PLL_FEEDBACK_DIVIDER_HIGH);

	/* Enable overग_लिखो of n,m parameters :pll_n_ovr_en, pll_m_ovr_en */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_OUTPUT_CLK_SEL,
		       (PLL_N_OVR_EN | PLL_M_OVR_EN));

	/* Program Charge-Pump parameters */

	/* pll_prop_cntrl-fixed values क्रम prop_cntrl from DPHY करोc */
	t_freq = target_freq_mhz * vco_p.भागider;
	test_mode_send(kmb_dsi, dphy_no,
		       TEST_CODE_PLL_PROPORTIONAL_CHARGE_PUMP_CTRL,
		       ((t_freq > 1150) ? 0x0C : 0x0B));

	/* pll_पूर्णांक_cntrl-fixed value क्रम पूर्णांक_cntrl from DPHY करोc */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_INTEGRAL_CHARGE_PUMP_CTRL,
		       0x00);

	/* pll_gmp_cntrl-fixed value क्रम gmp_cntrl from DPHY करोci */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_GMP_CTRL, 0x10);

	/* pll_cpbias_cntrl-fixed value क्रम cpbias_cntrl from DPHY करोc */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_CHARGE_PUMP_BIAS, 0x10);

	/* pll_th1 -Lock Detector Phase error threshold,
	 * करोcument gives fixed value
	 */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_PHASE_ERR_CTRL, 0x02);

	/* PLL Lock Configuration */

	/* pll_th2 - Lock Filter length, करोcument gives fixed value */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_LOCK_FILTER, 0x60);

	/* pll_th3- PLL Unlocking filter, करोcument gives fixed value */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_UNLOCK_FILTER, 0x03);

	/* pll_lock_sel-PLL Lock Detector Selection,
	 * करोcument gives fixed value
	 */
	test_mode_send(kmb_dsi, dphy_no, TEST_CODE_PLL_LOCK_DETECTOR, 0x02);
पूर्ण

अटल व्योम set_slewrate_gt_1500(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no)
अणु
	u32 test_code = 0, test_data = 0;
	/* Bypass slew rate calibration algorithm
	 * bits[1:0पूर्ण srcal_en_ovr_en, srcal_en_ovr
	 */
	test_code = TEST_CODE_SLEW_RATE_OVERRIDE_CTRL;
	test_data = 0x02;
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Disable slew rate calibration */
	test_code = TEST_CODE_SLEW_RATE_DDL_LOOP_CTRL;
	test_data = 0x00;
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);
पूर्ण

अटल व्योम set_slewrate_gt_1000(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no)
अणु
	u32 test_code = 0, test_data = 0;

	/* BitRate: > 1 Gbps && <= 1.5 Gbps: - slew rate control ON
	 * typical rise/fall बार: 166 ps
	 */

	/* Do not bypass slew rate calibration algorithm
	 * bits[1:0पूर्ण=srcal_en_ovr_en, srcal_en_ovr, bit[6]=sr_range
	 */
	test_code = TEST_CODE_SLEW_RATE_OVERRIDE_CTRL;
	test_data = (0x03 | (1 << 6));
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Enable slew rate calibration */
	test_code = TEST_CODE_SLEW_RATE_DDL_LOOP_CTRL;
	test_data = 0x01;
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Set sr_osc_freq_target[6:0] low nibble
	 * typical rise/fall समय=166, refer Table 1207 databook
	 */
	test_code = TEST_CODE_SLEW_RATE_DDL_CYCLES;
	test_data = (0x72f & 0x7f);
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Set sr_osc_freq_target[11:7] high nibble
	 * Typical rise/fall समय=166, refer Table 1207 databook
	 */
	test_code = TEST_CODE_SLEW_RATE_DDL_CYCLES;
	test_data = ((0x72f >> 6) & 0x1f) | (1 << 7);
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);
पूर्ण

अटल व्योम set_slewrate_lt_1000(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no)
अणु
	u32 test_code = 0, test_data = 0;

	/* lane_rate_mbps <= 1000 Mbps
	 * BitRate:  <= 1 Gbps:
	 * - slew rate control ON
	 * - typical rise/fall बार: 225 ps
	 */

	/* Do not bypass slew rate calibration algorithm */
	test_code = TEST_CODE_SLEW_RATE_OVERRIDE_CTRL;
	test_data = (0x03 | (1 << 6));
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Enable slew rate calibration */
	test_code = TEST_CODE_SLEW_RATE_DDL_LOOP_CTRL;
	test_data = 0x01;
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Typical rise/fall समय=255, refer Table 1207 databook */
	test_code = TEST_CODE_SLEW_RATE_DDL_CYCLES;
	test_data = (0x523 & 0x7f);
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Set sr_osc_freq_target[11:7] high nibble */
	test_code = TEST_CODE_SLEW_RATE_DDL_CYCLES;
	test_data = ((0x523 >> 6) & 0x1f) | (1 << 7);
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);
पूर्ण

अटल व्योम setup_pll(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no,
		      काष्ठा mipi_ctrl_cfg *cfg)
अणु
	u32 test_code = 0, test_data = 0;

	/* Set PLL regulator in bypass */
	test_code = TEST_CODE_PLL_ANALOG_PROG;
	test_data = 0x01;
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* PLL Parameters Setup */
	mipi_tx_pll_setup(kmb_dsi, dphy_no, cfg->ref_clk_khz / 1000,
			  cfg->lane_rate_mbps / 2);

	/* Set clksel */
	kmb_ग_लिखो_bits_mipi(kmb_dsi, DPHY_INIT_CTRL1, PLL_CLKSEL_0, 2, 0x01);

	/* Set pll_shaकरोw_control */
	kmb_set_bit_mipi(kmb_dsi, DPHY_INIT_CTRL1, PLL_SHADOW_CTRL);
पूर्ण

अटल व्योम set_lane_data_rate(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no,
			       काष्ठा mipi_ctrl_cfg *cfg)
अणु
	u32 i, test_code = 0, test_data = 0;

	क्रम (i = 0; i < MIPI_DPHY_DEFAULT_BIT_RATES; i++) अणु
		अगर (mipi_hs_freq_range[i].शेष_bit_rate_mbps <
		    cfg->lane_rate_mbps)
			जारी;

		/* Send the test code and data */
		/* bit[6:0] = hsfreqrange_ovr bit[7] = hsfreqrange_ovr_en */
		test_code = TEST_CODE_HS_FREQ_RANGE_CFG;
		test_data = (mipi_hs_freq_range[i].hsfreqrange_code & 0x7f) |
		    (1 << 7);
		test_mode_send(kmb_dsi, dphy_no, test_code, test_data);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dphy_init_sequence(काष्ठा kmb_dsi *kmb_dsi,
			       काष्ठा mipi_ctrl_cfg *cfg, u32 dphy_no,
			       पूर्णांक active_lanes, क्रमागत dphy_mode mode)
अणु
	u32 test_code = 0, test_data = 0, val;

	/* Set D-PHY in shutकरोwn mode */
	/* Assert RSTZ संकेत */
	CLR_DPHY_INIT_CTRL0(kmb_dsi, dphy_no, RESETZ);

	/* Assert SHUTDOWNZ संकेत */
	CLR_DPHY_INIT_CTRL0(kmb_dsi, dphy_no, SHUTDOWNZ);
	val = kmb_पढ़ो_mipi(kmb_dsi, DPHY_INIT_CTRL0);

	/* Init D-PHY_n
	 * Pulse testclear संकेत to make sure the d-phy configuration
	 * starts from a clean base
	 */
	CLR_DPHY_TEST_CTRL0(kmb_dsi, dphy_no);
	ndelay(15);
	SET_DPHY_TEST_CTRL0(kmb_dsi, dphy_no);
	ndelay(15);
	CLR_DPHY_TEST_CTRL0(kmb_dsi, dphy_no);
	ndelay(15);

	/* Set mastermacro bit - Master or slave mode */
	test_code = TEST_CODE_MULTIPLE_PHY_CTRL;

	/* DPHY has its own घड़ी lane enabled (master) */
	अगर (mode == MIPI_DPHY_MASTER)
		test_data = 0x01;
	अन्यथा
		test_data = 0x00;

	/* Send the test code and data */
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Set the lane data rate */
	set_lane_data_rate(kmb_dsi, dphy_no, cfg);

	/* High-Speed Tx Slew Rate Calibration
	 * BitRate: > 1.5 Gbps && <= 2.5 Gbps: slew rate control OFF
	 */
	अगर (cfg->lane_rate_mbps > 1500)
		set_slewrate_gt_1500(kmb_dsi, dphy_no);
	अन्यथा अगर (cfg->lane_rate_mbps > 1000)
		set_slewrate_gt_1000(kmb_dsi, dphy_no);
	अन्यथा
		set_slewrate_lt_1000(kmb_dsi, dphy_no);

	/* Set cfgclkfreqrange */
	val = (((cfg->cfg_clk_khz / 1000) - 17) * 4) & 0x3f;
	SET_DPHY_FREQ_CTRL0_3(kmb_dsi, dphy_no, val);

	/* Enable config clk क्रम the corresponding d-phy */
	kmb_set_bit_mipi(kmb_dsi, DPHY_CFG_CLK_EN, dphy_no);

	/* PLL setup */
	अगर (mode == MIPI_DPHY_MASTER)
		setup_pll(kmb_dsi, dphy_no, cfg);

	/* Send NORMAL OPERATION test code */
	test_code = 0x0;
	test_data = 0x0;
	test_mode_send(kmb_dsi, dphy_no, test_code, test_data);

	/* Configure BASEसूची क्रम data lanes
	 * NOTE: basedir only applies to LANE_0 of each D-PHY.
	 * The other lanes keep their direction based on the D-PHY type,
	 * either Rx or Tx.
	 * bits[5:0]  - BaseDir: 1 = Rx
	 * bits[9:6] - BaseDir: 0 = Tx
	 */
	kmb_ग_लिखो_bits_mipi(kmb_dsi, DPHY_INIT_CTRL2, 0, 9, 0x03f);
	ndelay(15);

	/* Enable CLOCK LANE
	 * Clock lane should be enabled regardless of the direction
	 * set क्रम the D-PHY (Rx/Tx)
	 */
	kmb_set_bit_mipi(kmb_dsi, DPHY_INIT_CTRL2, 12 + dphy_no);

	/* Enable DATA LANES */
	kmb_ग_लिखो_bits_mipi(kmb_dsi, DPHY_ENABLE, dphy_no * 2, 2,
			    ((1 << active_lanes) - 1));

	ndelay(15);

	/* Take D-PHY out of shutकरोwn mode */
	/* Deनिश्चित SHUTDOWNZ संकेत */
	SET_DPHY_INIT_CTRL0(kmb_dsi, dphy_no, SHUTDOWNZ);
	ndelay(15);

	/* Deनिश्चित RSTZ संकेत */
	SET_DPHY_INIT_CTRL0(kmb_dsi, dphy_no, RESETZ);
पूर्ण

अटल व्योम dphy_रुको_fsm(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no,
			  क्रमागत dphy_tx_fsm fsm_state)
अणु
	क्रमागत dphy_tx_fsm val = DPHY_TX_POWERDWN;
	पूर्णांक i = 0;
	पूर्णांक status = 1;

	करो अणु
		test_mode_send(kmb_dsi, dphy_no, TEST_CODE_FSM_CONTROL, 0x80);

		val = GET_TEST_DOUT4_7(kmb_dsi, dphy_no);
		i++;
		अगर (i > TIMEOUT) अणु
			status = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (val != fsm_state);

	dev_dbg(kmb_dsi->dev, "%s: dphy %d val = %x", __func__, dphy_no, val);
	dev_dbg(kmb_dsi->dev, "* DPHY %d WAIT_FSM %s *",
		dphy_no, status ? "SUCCESS" : "FAILED");
पूर्ण

अटल व्योम रुको_init_करोne(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no,
			   u32 active_lanes)
अणु
	u32 stopstatedata = 0;
	u32 data_lanes = (1 << active_lanes) - 1;
	पूर्णांक i = 0;
	पूर्णांक status = 1;

	करो अणु
		stopstatedata = GET_STOPSTATE_DATA(kmb_dsi, dphy_no)
				& data_lanes;

		/* TODO-need to add a समय out and वापस failure */
		i++;

		अगर (i > TIMEOUT) अणु
			status = 0;
			dev_dbg(kmb_dsi->dev,
				"! WAIT_INIT_DONE: TIMING OUT!(err_stat=%d)",
				kmb_पढ़ो_mipi(kmb_dsi, MIPI_DPHY_ERR_STAT6_7));
			अवरोध;
		पूर्ण
	पूर्ण जबतक (stopstatedata != data_lanes);

	dev_dbg(kmb_dsi->dev, "* DPHY %d INIT - %s *",
		dphy_no, status ? "SUCCESS" : "FAILED");
पूर्ण

अटल व्योम रुको_pll_lock(काष्ठा kmb_dsi *kmb_dsi, u32 dphy_no)
अणु
	पूर्णांक i = 0;
	पूर्णांक status = 1;

	करो अणु
		/* TODO-need to add a समय out and वापस failure */
		i++;
		अगर (i > TIMEOUT) अणु
			status = 0;
			dev_dbg(kmb_dsi->dev, "%s: timing out", __func__);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!GET_PLL_LOCK(kmb_dsi, dphy_no));

	dev_dbg(kmb_dsi->dev, "* PLL Locked for DPHY %d - %s *",
		dphy_no, status ? "SUCCESS" : "FAILED");
पूर्ण

अटल u32 mipi_tx_init_dphy(काष्ठा kmb_dsi *kmb_dsi,
			     काष्ठा mipi_ctrl_cfg *cfg)
अणु
	u32 dphy_no = MIPI_DPHY6;

	/* Multiple D-PHYs needed */
	अगर (cfg->active_lanes > MIPI_DPHY_D_LANES) अणु
		/*
		 *Initialization क्रम Tx aggregation mode is करोne according to
		 *a. start init PHY1
		 *b. poll क्रम PHY1 FSM state LOCK
		 *   b1. reg addr 0x03[3:0] - state_मुख्य[3:0] == 5 (LOCK)
		 *c. poll क्रम PHY1 calibrations करोne :
		 *   c1. termination calibration lower section: addr 0x22[5]
		 *   - rescal_करोne
		 *   c2. slewrate calibration (अगर data rate < = 1500 Mbps):
		 *     addr 0xA7[3:2] - srcal_करोne, sr_finished
		 *d. start init PHY0
		 *e. poll क्रम PHY0 stopstate
		 *f. poll क्रम PHY1 stopstate
		 */
		/* PHY #N+1 ('slave') */

		dphy_init_sequence(kmb_dsi, cfg, dphy_no + 1,
				   (cfg->active_lanes - MIPI_DPHY_D_LANES),
				   MIPI_DPHY_SLAVE);
		dphy_रुको_fsm(kmb_dsi, dphy_no + 1, DPHY_TX_LOCK);

		/* PHY #N master */
		dphy_init_sequence(kmb_dsi, cfg, dphy_no, MIPI_DPHY_D_LANES,
				   MIPI_DPHY_MASTER);

		/* Wait क्रम DPHY init to complete */
		रुको_init_करोne(kmb_dsi, dphy_no, MIPI_DPHY_D_LANES);
		रुको_init_करोne(kmb_dsi, dphy_no + 1,
			       cfg->active_lanes - MIPI_DPHY_D_LANES);
		रुको_pll_lock(kmb_dsi, dphy_no);
		रुको_pll_lock(kmb_dsi, dphy_no + 1);
		dphy_रुको_fsm(kmb_dsi, dphy_no, DPHY_TX_IDLE);
	पूर्ण अन्यथा अणु		/* Single DPHY */
		dphy_init_sequence(kmb_dsi, cfg, dphy_no, cfg->active_lanes,
				   MIPI_DPHY_MASTER);
		dphy_रुको_fsm(kmb_dsi, dphy_no, DPHY_TX_IDLE);
		रुको_init_करोne(kmb_dsi, dphy_no, cfg->active_lanes);
		रुको_pll_lock(kmb_dsi, dphy_no);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम connect_lcd_to_mipi(काष्ठा kmb_dsi *kmb_dsi)
अणु
	काष्ठा regmap *msscam;

	msscam = syscon_regmap_lookup_by_compatible("intel,keembay-msscam");
	अगर (IS_ERR(msscam)) अणु
		dev_dbg(kmb_dsi->dev, "failed to get msscam syscon");
		वापस;
	पूर्ण

	/* DISABLE MIPI->CIF CONNECTION */
	regmap_ग_लिखो(msscam, MSS_MIPI_CIF_CFG, 0);

	/* ENABLE LCD->MIPI CONNECTION */
	regmap_ग_लिखो(msscam, MSS_LCD_MIPI_CFG, 1);
	/* DISABLE LCD->CIF LOOPBACK */
	regmap_ग_लिखो(msscam, MSS_LOOPBACK_CFG, 1);
पूर्ण

पूर्णांक kmb_dsi_mode_set(काष्ठा kmb_dsi *kmb_dsi, काष्ठा drm_display_mode *mode,
		     पूर्णांक sys_clk_mhz)
अणु
	u64 data_rate;

	kmb_dsi->sys_clk_mhz = sys_clk_mhz;
	mipi_tx_init_cfg.active_lanes = MIPI_TX_ACTIVE_LANES;

	mipi_tx_frame0_sect_cfg.width_pixels = mode->crtc_hdisplay;
	mipi_tx_frame0_sect_cfg.height_lines = mode->crtc_vdisplay;
	mipitx_frame0_cfg.vsync_width =
		mode->crtc_vsync_end - mode->crtc_vsync_start;
	mipitx_frame0_cfg.v_backporch =
		mode->crtc_vtotal - mode->crtc_vsync_end;
	mipitx_frame0_cfg.v_frontporch =
		mode->crtc_vsync_start - mode->crtc_vdisplay;
	mipitx_frame0_cfg.hsync_width =
		mode->crtc_hsync_end - mode->crtc_hsync_start;
	mipitx_frame0_cfg.h_backporch =
		mode->crtc_htotal - mode->crtc_hsync_end;
	mipitx_frame0_cfg.h_frontporch =
		mode->crtc_hsync_start - mode->crtc_hdisplay;

	/* Lane rate = (vtotal*htotal*fps*bpp)/4 / 1000000
	 * to convert to Mbps
	 */
	data_rate = ((((u32)mode->crtc_vtotal *	(u32)mode->crtc_htotal) *
			(u32)(drm_mode_vrefresh(mode)) *
			MIPI_TX_BPP) / mipi_tx_init_cfg.active_lanes) /	1000000;

	dev_dbg(kmb_dsi->dev, "data_rate=%u active_lanes=%d\n",
		(u32)data_rate, mipi_tx_init_cfg.active_lanes);

	/* When late rate < 800, modeset fails with 4 lanes,
	 * so चयन to 2 lanes
	 */
	अगर (data_rate < 800) अणु
		mipi_tx_init_cfg.active_lanes = 2;
		mipi_tx_init_cfg.lane_rate_mbps = data_rate * 2;
	पूर्ण अन्यथा अणु
		mipi_tx_init_cfg.lane_rate_mbps = data_rate;
	पूर्ण

	kmb_ग_लिखो_mipi(kmb_dsi, DPHY_ENABLE, 0);
	kmb_ग_लिखो_mipi(kmb_dsi, DPHY_INIT_CTRL0, 0);
	kmb_ग_लिखो_mipi(kmb_dsi, DPHY_INIT_CTRL1, 0);
	kmb_ग_लिखो_mipi(kmb_dsi, DPHY_INIT_CTRL2, 0);

	/* Initialize mipi controller */
	mipi_tx_init_cntrl(kmb_dsi, &mipi_tx_init_cfg);

	/* Dphy initialization */
	mipi_tx_init_dphy(kmb_dsi, &mipi_tx_init_cfg);

	connect_lcd_to_mipi(kmb_dsi);
	dev_info(kmb_dsi->dev, "mipi hw initialized");

	वापस 0;
पूर्ण

काष्ठा kmb_dsi *kmb_dsi_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kmb_dsi *kmb_dsi;
	काष्ठा device *dev = get_device(&pdev->dev);

	kmb_dsi = devm_kzalloc(dev, माप(*kmb_dsi), GFP_KERNEL);
	अगर (!kmb_dsi) अणु
		dev_err(dev, "failed to allocate kmb_dsi\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	kmb_dsi->host = dsi_host;
	kmb_dsi->host->ops = &kmb_dsi_host_ops;

	dsi_device->host = kmb_dsi->host;
	kmb_dsi->device = dsi_device;

	वापस kmb_dsi;
पूर्ण

पूर्णांक kmb_dsi_encoder_init(काष्ठा drm_device *dev, काष्ठा kmb_dsi *kmb_dsi)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	पूर्णांक ret = 0;

	encoder = &kmb_dsi->base;
	encoder->possible_crtcs = 1;
	encoder->possible_clones = 0;

	ret = drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_DSI);
	अगर (ret) अणु
		dev_err(kmb_dsi->dev, "Failed to init encoder %d\n", ret);
		वापस ret;
	पूर्ण

	/* Link drm_bridge to encoder */
	ret = drm_bridge_attach(encoder, adv_bridge, शून्य,
				DRM_BRIDGE_ATTACH_NO_CONNECTOR);
	अगर (ret) अणु
		DRM_ERROR("failed to attach bridge to MIPI\n");
		drm_encoder_cleanup(encoder);
		वापस ret;
	पूर्ण
	drm_info(dev, "Bridge attached : SUCCESS");
	connector = drm_bridge_connector_init(dev, encoder);
	अगर (IS_ERR(connector)) अणु
		DRM_ERROR("Unable to create bridge connector");
		drm_encoder_cleanup(encoder);
		वापस PTR_ERR(connector);
	पूर्ण
	drm_connector_attach_encoder(connector, encoder);
	वापस 0;
पूर्ण

पूर्णांक kmb_dsi_map_mmio(काष्ठा kmb_dsi *kmb_dsi)
अणु
	काष्ठा resource *res;
	काष्ठा device *dev = kmb_dsi->dev;

	res = platक्रमm_get_resource_byname(kmb_dsi->pdev, IORESOURCE_MEM,
					   "mipi");
	अगर (!res) अणु
		dev_err(dev, "failed to get resource for mipi");
		वापस -ENOMEM;
	पूर्ण
	kmb_dsi->mipi_mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(kmb_dsi->mipi_mmio)) अणु
		dev_err(dev, "failed to ioremap mipi registers");
		वापस PTR_ERR(kmb_dsi->mipi_mmio);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kmb_dsi_clk_enable(काष्ठा kmb_dsi *kmb_dsi)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = kmb_dsi->dev;

	ret = clk_prepare_enable(kmb_dsi->clk_mipi);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable MIPI clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(kmb_dsi->clk_mipi_ecfg);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable MIPI_ECFG clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(kmb_dsi->clk_mipi_cfg);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable MIPI_CFG clock: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "SUCCESS : enabled MIPI clocks\n");
	वापस 0;
पूर्ण

पूर्णांक kmb_dsi_clk_init(काष्ठा kmb_dsi *kmb_dsi)
अणु
	काष्ठा device *dev = kmb_dsi->dev;
	अचिन्हित दीर्घ clk;

	kmb_dsi->clk_mipi = devm_clk_get(dev, "clk_mipi");
	अगर (IS_ERR(kmb_dsi->clk_mipi)) अणु
		dev_err(dev, "devm_clk_get() failed clk_mipi\n");
		वापस PTR_ERR(kmb_dsi->clk_mipi);
	पूर्ण

	kmb_dsi->clk_mipi_ecfg = devm_clk_get(dev, "clk_mipi_ecfg");
	अगर (IS_ERR(kmb_dsi->clk_mipi_ecfg)) अणु
		dev_err(dev, "devm_clk_get() failed clk_mipi_ecfg\n");
		वापस PTR_ERR(kmb_dsi->clk_mipi_ecfg);
	पूर्ण

	kmb_dsi->clk_mipi_cfg = devm_clk_get(dev, "clk_mipi_cfg");
	अगर (IS_ERR(kmb_dsi->clk_mipi_cfg)) अणु
		dev_err(dev, "devm_clk_get() failed clk_mipi_cfg\n");
		वापस PTR_ERR(kmb_dsi->clk_mipi_cfg);
	पूर्ण
	/* Set MIPI घड़ी to 24 Mhz */
	clk_set_rate(kmb_dsi->clk_mipi, KMB_MIPI_DEFAULT_CLK);
	अगर (clk_get_rate(kmb_dsi->clk_mipi) != KMB_MIPI_DEFAULT_CLK) अणु
		dev_err(dev, "failed to set to clk_mipi to %d\n",
			KMB_MIPI_DEFAULT_CLK);
		वापस -1;
	पूर्ण
	dev_dbg(dev, "clk_mipi = %ld\n", clk_get_rate(kmb_dsi->clk_mipi));

	clk = clk_get_rate(kmb_dsi->clk_mipi_ecfg);
	अगर (clk != KMB_MIPI_DEFAULT_CFG_CLK) अणु
		/* Set MIPI_ECFG घड़ी to 24 Mhz */
		clk_set_rate(kmb_dsi->clk_mipi_ecfg, KMB_MIPI_DEFAULT_CFG_CLK);
		clk = clk_get_rate(kmb_dsi->clk_mipi_ecfg);
		अगर (clk != KMB_MIPI_DEFAULT_CFG_CLK) अणु
			dev_err(dev, "failed to set to clk_mipi_ecfg to %d\n",
				KMB_MIPI_DEFAULT_CFG_CLK);
			वापस -1;
		पूर्ण
	पूर्ण

	clk = clk_get_rate(kmb_dsi->clk_mipi_cfg);
	अगर (clk != KMB_MIPI_DEFAULT_CFG_CLK) अणु
		/* Set MIPI_CFG घड़ी to 24 Mhz */
		clk_set_rate(kmb_dsi->clk_mipi_cfg, 24000000);
		clk = clk_get_rate(kmb_dsi->clk_mipi_cfg);
		अगर (clk != KMB_MIPI_DEFAULT_CFG_CLK) अणु
			dev_err(dev, "failed to set clk_mipi_cfg to %d\n",
				KMB_MIPI_DEFAULT_CFG_CLK);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस kmb_dsi_clk_enable(kmb_dsi);
पूर्ण
