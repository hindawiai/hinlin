<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2016 Allwinnertech Co., Ltd.
 * Copyright (C) 2017-2018 Bootlin
 *
 * Maxime Ripard <maxime.ripard@bootlin.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy-mipi-dphy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "sun4i_crtc.h"
#समावेश "sun4i_tcon.h"
#समावेश "sun6i_mipi_dsi.h"

#समावेश <video/mipi_display.h>

#घोषणा SUN6I_DSI_CTL_REG		0x000
#घोषणा SUN6I_DSI_CTL_EN			BIT(0)

#घोषणा SUN6I_DSI_BASIC_CTL_REG		0x00c
#घोषणा SUN6I_DSI_BASIC_CTL_TRAIL_INV(n)		(((n) & 0xf) << 4)
#घोषणा SUN6I_DSI_BASIC_CTL_TRAIL_FILL		BIT(3)
#घोषणा SUN6I_DSI_BASIC_CTL_HBP_DIS		BIT(2)
#घोषणा SUN6I_DSI_BASIC_CTL_HSA_HSE_DIS		BIT(1)
#घोषणा SUN6I_DSI_BASIC_CTL_VIDEO_BURST		BIT(0)

#घोषणा SUN6I_DSI_BASIC_CTL0_REG	0x010
#घोषणा SUN6I_DSI_BASIC_CTL0_HS_EOTP_EN		BIT(18)
#घोषणा SUN6I_DSI_BASIC_CTL0_CRC_EN		BIT(17)
#घोषणा SUN6I_DSI_BASIC_CTL0_ECC_EN		BIT(16)
#घोषणा SUN6I_DSI_BASIC_CTL0_INST_ST		BIT(0)

#घोषणा SUN6I_DSI_BASIC_CTL1_REG	0x014
#घोषणा SUN6I_DSI_BASIC_CTL1_VIDEO_ST_DELAY(n)	(((n) & 0x1fff) << 4)
#घोषणा SUN6I_DSI_BASIC_CTL1_VIDEO_FILL		BIT(2)
#घोषणा SUN6I_DSI_BASIC_CTL1_VIDEO_PRECISION	BIT(1)
#घोषणा SUN6I_DSI_BASIC_CTL1_VIDEO_MODE		BIT(0)

#घोषणा SUN6I_DSI_BASIC_SIZE0_REG	0x018
#घोषणा SUN6I_DSI_BASIC_SIZE0_VBP(n)		(((n) & 0xfff) << 16)
#घोषणा SUN6I_DSI_BASIC_SIZE0_VSA(n)		((n) & 0xfff)

#घोषणा SUN6I_DSI_BASIC_SIZE1_REG	0x01c
#घोषणा SUN6I_DSI_BASIC_SIZE1_VT(n)		(((n) & 0xfff) << 16)
#घोषणा SUN6I_DSI_BASIC_SIZE1_VACT(n)		((n) & 0xfff)

#घोषणा SUN6I_DSI_INST_FUNC_REG(n)	(0x020 + (n) * 0x04)
#घोषणा SUN6I_DSI_INST_FUNC_INST_MODE(n)	(((n) & 0xf) << 28)
#घोषणा SUN6I_DSI_INST_FUNC_ESCAPE_ENTRY(n)	(((n) & 0xf) << 24)
#घोषणा SUN6I_DSI_INST_FUNC_TRANS_PACKET(n)	(((n) & 0xf) << 20)
#घोषणा SUN6I_DSI_INST_FUNC_LANE_CEN		BIT(4)
#घोषणा SUN6I_DSI_INST_FUNC_LANE_DEN(n)		((n) & 0xf)

#घोषणा SUN6I_DSI_INST_LOOP_SEL_REG	0x040

#घोषणा SUN6I_DSI_INST_LOOP_NUM_REG(n)	(0x044 + (n) * 0x10)
#घोषणा SUN6I_DSI_INST_LOOP_NUM_N1(n)		(((n) & 0xfff) << 16)
#घोषणा SUN6I_DSI_INST_LOOP_NUM_N0(n)		((n) & 0xfff)

#घोषणा SUN6I_DSI_INST_JUMP_SEL_REG	0x048

#घोषणा SUN6I_DSI_INST_JUMP_CFG_REG(n)	(0x04c + (n) * 0x04)
#घोषणा SUN6I_DSI_INST_JUMP_CFG_TO(n)		(((n) & 0xf) << 20)
#घोषणा SUN6I_DSI_INST_JUMP_CFG_POINT(n)	(((n) & 0xf) << 16)
#घोषणा SUN6I_DSI_INST_JUMP_CFG_NUM(n)		((n) & 0xffff)

#घोषणा SUN6I_DSI_TRANS_START_REG	0x060

#घोषणा SUN6I_DSI_TRANS_ZERO_REG	0x078

#घोषणा SUN6I_DSI_TCON_DRQ_REG		0x07c
#घोषणा SUN6I_DSI_TCON_DRQ_ENABLE_MODE		BIT(28)
#घोषणा SUN6I_DSI_TCON_DRQ_SET(n)		((n) & 0x3ff)

#घोषणा SUN6I_DSI_PIXEL_CTL0_REG	0x080
#घोषणा SUN6I_DSI_PIXEL_CTL0_PD_PLUG_DISABLE	BIT(16)
#घोषणा SUN6I_DSI_PIXEL_CTL0_FORMAT(n)		((n) & 0xf)

#घोषणा SUN6I_DSI_PIXEL_CTL1_REG	0x084

#घोषणा SUN6I_DSI_PIXEL_PH_REG		0x090
#घोषणा SUN6I_DSI_PIXEL_PH_ECC(n)		(((n) & 0xff) << 24)
#घोषणा SUN6I_DSI_PIXEL_PH_WC(n)		(((n) & 0xffff) << 8)
#घोषणा SUN6I_DSI_PIXEL_PH_VC(n)		(((n) & 3) << 6)
#घोषणा SUN6I_DSI_PIXEL_PH_DT(n)		((n) & 0x3f)

#घोषणा SUN6I_DSI_PIXEL_PF0_REG		0x098
#घोषणा SUN6I_DSI_PIXEL_PF0_CRC_FORCE(n)	((n) & 0xffff)

#घोषणा SUN6I_DSI_PIXEL_PF1_REG		0x09c
#घोषणा SUN6I_DSI_PIXEL_PF1_CRC_INIT_LINEN(n)	(((n) & 0xffff) << 16)
#घोषणा SUN6I_DSI_PIXEL_PF1_CRC_INIT_LINE0(n)	((n) & 0xffff)

#घोषणा SUN6I_DSI_SYNC_HSS_REG		0x0b0

#घोषणा SUN6I_DSI_SYNC_HSE_REG		0x0b4

#घोषणा SUN6I_DSI_SYNC_VSS_REG		0x0b8

#घोषणा SUN6I_DSI_SYNC_VSE_REG		0x0bc

#घोषणा SUN6I_DSI_BLK_HSA0_REG		0x0c0

#घोषणा SUN6I_DSI_BLK_HSA1_REG		0x0c4
#घोषणा SUN6I_DSI_BLK_PF(n)			(((n) & 0xffff) << 16)
#घोषणा SUN6I_DSI_BLK_PD(n)			((n) & 0xff)

#घोषणा SUN6I_DSI_BLK_HBP0_REG		0x0c8

#घोषणा SUN6I_DSI_BLK_HBP1_REG		0x0cc

#घोषणा SUN6I_DSI_BLK_HFP0_REG		0x0d0

#घोषणा SUN6I_DSI_BLK_HFP1_REG		0x0d4

#घोषणा SUN6I_DSI_BLK_HBLK0_REG		0x0e0

#घोषणा SUN6I_DSI_BLK_HBLK1_REG		0x0e4

#घोषणा SUN6I_DSI_BLK_VBLK0_REG		0x0e8

#घोषणा SUN6I_DSI_BLK_VBLK1_REG		0x0ec

#घोषणा SUN6I_DSI_BURST_LINE_REG	0x0f0
#घोषणा SUN6I_DSI_BURST_LINE_SYNC_POINT(n)	(((n) & 0xffff) << 16)
#घोषणा SUN6I_DSI_BURST_LINE_NUM(n)		((n) & 0xffff)

#घोषणा SUN6I_DSI_BURST_DRQ_REG		0x0f4
#घोषणा SUN6I_DSI_BURST_DRQ_EDGE1(n)		(((n) & 0xffff) << 16)
#घोषणा SUN6I_DSI_BURST_DRQ_EDGE0(n)		((n) & 0xffff)

#घोषणा SUN6I_DSI_CMD_CTL_REG		0x200
#घोषणा SUN6I_DSI_CMD_CTL_RX_OVERFLOW		BIT(26)
#घोषणा SUN6I_DSI_CMD_CTL_RX_FLAG		BIT(25)
#घोषणा SUN6I_DSI_CMD_CTL_TX_FLAG		BIT(9)

#घोषणा SUN6I_DSI_CMD_RX_REG(n)		(0x240 + (n) * 0x04)

#घोषणा SUN6I_DSI_DEBUG_DATA_REG	0x2f8

#घोषणा SUN6I_DSI_CMD_TX_REG(n)		(0x300 + (n) * 0x04)

#घोषणा SUN6I_DSI_SYNC_POINT		40

क्रमागत sun6i_dsi_start_inst अणु
	DSI_START_LPRX,
	DSI_START_LPTX,
	DSI_START_HSC,
	DSI_START_HSD,
पूर्ण;

क्रमागत sun6i_dsi_inst_id अणु
	DSI_INST_ID_LP11	= 0,
	DSI_INST_ID_TBA,
	DSI_INST_ID_HSC,
	DSI_INST_ID_HSD,
	DSI_INST_ID_LPDT,
	DSI_INST_ID_HSCEXIT,
	DSI_INST_ID_NOP,
	DSI_INST_ID_DLY,
	DSI_INST_ID_END		= 15,
पूर्ण;

क्रमागत sun6i_dsi_inst_mode अणु
	DSI_INST_MODE_STOP	= 0,
	DSI_INST_MODE_TBA,
	DSI_INST_MODE_HS,
	DSI_INST_MODE_ESCAPE,
	DSI_INST_MODE_HSCEXIT,
	DSI_INST_MODE_NOP,
पूर्ण;

क्रमागत sun6i_dsi_inst_escape अणु
	DSI_INST_ESCA_LPDT	= 0,
	DSI_INST_ESCA_ULPS,
	DSI_INST_ESCA_UN1,
	DSI_INST_ESCA_UN2,
	DSI_INST_ESCA_RESET,
	DSI_INST_ESCA_UN3,
	DSI_INST_ESCA_UN4,
	DSI_INST_ESCA_UN5,
पूर्ण;

क्रमागत sun6i_dsi_inst_packet अणु
	DSI_INST_PACK_PIXEL	= 0,
	DSI_INST_PACK_COMMAND,
पूर्ण;

अटल स्थिर u32 sun6i_dsi_ecc_array[] = अणु
	[0] = (BIT(0) | BIT(1) | BIT(2) | BIT(4) | BIT(5) | BIT(7) | BIT(10) |
	       BIT(11) | BIT(13) | BIT(16) | BIT(20) | BIT(21) | BIT(22) |
	       BIT(23)),
	[1] = (BIT(0) | BIT(1) | BIT(3) | BIT(4) | BIT(6) | BIT(8) | BIT(10) |
	       BIT(12) | BIT(14) | BIT(17) | BIT(20) | BIT(21) | BIT(22) |
	       BIT(23)),
	[2] = (BIT(0) | BIT(2) | BIT(3) | BIT(5) | BIT(6) | BIT(9) | BIT(11) |
	       BIT(12) | BIT(15) | BIT(18) | BIT(20) | BIT(21) | BIT(22)),
	[3] = (BIT(1) | BIT(2) | BIT(3) | BIT(7) | BIT(8) | BIT(9) | BIT(13) |
	       BIT(14) | BIT(15) | BIT(19) | BIT(20) | BIT(21) | BIT(23)),
	[4] = (BIT(4) | BIT(5) | BIT(6) | BIT(7) | BIT(8) | BIT(9) | BIT(16) |
	       BIT(17) | BIT(18) | BIT(19) | BIT(20) | BIT(22) | BIT(23)),
	[5] = (BIT(10) | BIT(11) | BIT(12) | BIT(13) | BIT(14) | BIT(15) |
	       BIT(16) | BIT(17) | BIT(18) | BIT(19) | BIT(21) | BIT(22) |
	       BIT(23)),
पूर्ण;

अटल u32 sun6i_dsi_ecc_compute(अचिन्हित पूर्णांक data)
अणु
	पूर्णांक i;
	u8 ecc = 0;

	क्रम (i = 0; i < ARRAY_SIZE(sun6i_dsi_ecc_array); i++) अणु
		u32 field = sun6i_dsi_ecc_array[i];
		bool init = false;
		u8 val = 0;
		पूर्णांक j;

		क्रम (j = 0; j < 24; j++) अणु
			अगर (!(BIT(j) & field))
				जारी;

			अगर (!init) अणु
				val = (BIT(j) & data) ? 1 : 0;
				init = true;
			पूर्ण अन्यथा अणु
				val ^= (BIT(j) & data) ? 1 : 0;
			पूर्ण
		पूर्ण

		ecc |= val << i;
	पूर्ण

	वापस ecc;
पूर्ण

अटल u16 sun6i_dsi_crc_compute(u8 स्थिर *buffer, माप_प्रकार len)
अणु
	वापस crc_ccitt(0xffff, buffer, len);
पूर्ण

अटल u16 sun6i_dsi_crc_repeat(u8 pd, u8 *buffer, माप_प्रकार len)
अणु
	स_रखो(buffer, pd, len);

	वापस sun6i_dsi_crc_compute(buffer, len);
पूर्ण

अटल u32 sun6i_dsi_build_sync_pkt(u8 dt, u8 vc, u8 d0, u8 d1)
अणु
	u32 val = dt & 0x3f;

	val |= (vc & 3) << 6;
	val |= (d0 & 0xff) << 8;
	val |= (d1 & 0xff) << 16;
	val |= sun6i_dsi_ecc_compute(val) << 24;

	वापस val;
पूर्ण

अटल u32 sun6i_dsi_build_blk0_pkt(u8 vc, u16 wc)
अणु
	वापस sun6i_dsi_build_sync_pkt(MIPI_DSI_BLANKING_PACKET, vc,
					wc & 0xff, wc >> 8);
पूर्ण

अटल u32 sun6i_dsi_build_blk1_pkt(u16 pd, u8 *buffer, माप_प्रकार len)
अणु
	u32 val = SUN6I_DSI_BLK_PD(pd);

	वापस val | SUN6I_DSI_BLK_PF(sun6i_dsi_crc_repeat(pd, buffer, len));
पूर्ण

अटल व्योम sun6i_dsi_inst_पात(काष्ठा sun6i_dsi *dsi)
अणु
	regmap_update_bits(dsi->regs, SUN6I_DSI_BASIC_CTL0_REG,
			   SUN6I_DSI_BASIC_CTL0_INST_ST, 0);
पूर्ण

अटल व्योम sun6i_dsi_inst_commit(काष्ठा sun6i_dsi *dsi)
अणु
	regmap_update_bits(dsi->regs, SUN6I_DSI_BASIC_CTL0_REG,
			   SUN6I_DSI_BASIC_CTL0_INST_ST,
			   SUN6I_DSI_BASIC_CTL0_INST_ST);
पूर्ण

अटल पूर्णांक sun6i_dsi_inst_रुको_क्रम_completion(काष्ठा sun6i_dsi *dsi)
अणु
	u32 val;

	वापस regmap_पढ़ो_poll_समयout(dsi->regs, SUN6I_DSI_BASIC_CTL0_REG,
					val,
					!(val & SUN6I_DSI_BASIC_CTL0_INST_ST),
					100, 5000);
पूर्ण

अटल व्योम sun6i_dsi_inst_setup(काष्ठा sun6i_dsi *dsi,
				 क्रमागत sun6i_dsi_inst_id id,
				 क्रमागत sun6i_dsi_inst_mode mode,
				 bool घड़ी, u8 data,
				 क्रमागत sun6i_dsi_inst_packet packet,
				 क्रमागत sun6i_dsi_inst_escape escape)
अणु
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_FUNC_REG(id),
		     SUN6I_DSI_INST_FUNC_INST_MODE(mode) |
		     SUN6I_DSI_INST_FUNC_ESCAPE_ENTRY(escape) |
		     SUN6I_DSI_INST_FUNC_TRANS_PACKET(packet) |
		     (घड़ी ? SUN6I_DSI_INST_FUNC_LANE_CEN : 0) |
		     SUN6I_DSI_INST_FUNC_LANE_DEN(data));
पूर्ण

अटल व्योम sun6i_dsi_inst_init(काष्ठा sun6i_dsi *dsi,
				काष्ठा mipi_dsi_device *device)
अणु
	u8 lanes_mask = GENMASK(device->lanes - 1, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_LP11, DSI_INST_MODE_STOP,
			     true, lanes_mask, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_TBA, DSI_INST_MODE_TBA,
			     false, 1, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSC, DSI_INST_MODE_HS,
			     true, 0, DSI_INST_PACK_PIXEL, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSD, DSI_INST_MODE_HS,
			     false, lanes_mask, DSI_INST_PACK_PIXEL, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_LPDT, DSI_INST_MODE_ESCAPE,
			     false, 1, DSI_INST_PACK_COMMAND,
			     DSI_INST_ESCA_LPDT);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSCEXIT, DSI_INST_MODE_HSCEXIT,
			     true, 0, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_NOP, DSI_INST_MODE_STOP,
			     false, lanes_mask, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_DLY, DSI_INST_MODE_NOP,
			     true, lanes_mask, 0, 0);

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_JUMP_CFG_REG(0),
		     SUN6I_DSI_INST_JUMP_CFG_POINT(DSI_INST_ID_NOP) |
		     SUN6I_DSI_INST_JUMP_CFG_TO(DSI_INST_ID_HSCEXIT) |
		     SUN6I_DSI_INST_JUMP_CFG_NUM(1));
पूर्ण;

अटल u16 sun6i_dsi_get_video_start_delay(काष्ठा sun6i_dsi *dsi,
					   काष्ठा drm_display_mode *mode)
अणु
	u16 delay = mode->vtotal - (mode->vsync_start - mode->vdisplay) + 1;

	अगर (delay > mode->vtotal)
		delay = delay % mode->vtotal;

	वापस max_t(u16, delay, 1);
पूर्ण

अटल u16 sun6i_dsi_get_line_num(काष्ठा sun6i_dsi *dsi,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mipi_dsi_device *device = dsi->device;
	अचिन्हित पूर्णांक Bpp = mipi_dsi_pixel_क्रमmat_to_bpp(device->क्रमmat) / 8;

	वापस mode->htotal * Bpp / device->lanes;
पूर्ण

अटल u16 sun6i_dsi_get_drq_edge0(काष्ठा sun6i_dsi *dsi,
				   काष्ठा drm_display_mode *mode,
				   u16 line_num, u16 edge1)
अणु
	u16 edge0 = edge1;

	edge0 += (mode->hdisplay + 40) * SUN6I_DSI_TCON_DIV / 8;

	अगर (edge0 > line_num)
		वापस edge0 - line_num;

	वापस 1;
पूर्ण

अटल u16 sun6i_dsi_get_drq_edge1(काष्ठा sun6i_dsi *dsi,
				   काष्ठा drm_display_mode *mode,
				   u16 line_num)
अणु
	काष्ठा mipi_dsi_device *device = dsi->device;
	अचिन्हित पूर्णांक Bpp = mipi_dsi_pixel_क्रमmat_to_bpp(device->क्रमmat) / 8;
	अचिन्हित पूर्णांक hbp = mode->htotal - mode->hsync_end;
	u16 edge1;

	edge1 = SUN6I_DSI_SYNC_POINT;
	edge1 += (mode->hdisplay + hbp + 20) * Bpp / device->lanes;

	अगर (edge1 > line_num)
		वापस line_num;

	वापस edge1;
पूर्ण

अटल व्योम sun6i_dsi_setup_burst(काष्ठा sun6i_dsi *dsi,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mipi_dsi_device *device = dsi->device;
	u32 val = 0;

	अगर (device->mode_flags & MIPI_DSI_MODE_VIDEO_BURST) अणु
		u16 line_num = sun6i_dsi_get_line_num(dsi, mode);
		u16 edge0, edge1;

		edge1 = sun6i_dsi_get_drq_edge1(dsi, mode, line_num);
		edge0 = sun6i_dsi_get_drq_edge0(dsi, mode, line_num, edge1);

		regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BURST_DRQ_REG,
			     SUN6I_DSI_BURST_DRQ_EDGE0(edge0) |
			     SUN6I_DSI_BURST_DRQ_EDGE1(edge1));

		regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BURST_LINE_REG,
			     SUN6I_DSI_BURST_LINE_NUM(line_num) |
			     SUN6I_DSI_BURST_LINE_SYNC_POINT(SUN6I_DSI_SYNC_POINT));

		val = SUN6I_DSI_TCON_DRQ_ENABLE_MODE;
	पूर्ण अन्यथा अगर ((mode->hsync_start - mode->hdisplay) > 20) अणु
		/* Maaaaaagic */
		u16 drq = (mode->hsync_start - mode->hdisplay) - 20;

		drq *= mipi_dsi_pixel_क्रमmat_to_bpp(device->क्रमmat);
		drq /= 32;

		val = (SUN6I_DSI_TCON_DRQ_ENABLE_MODE |
		       SUN6I_DSI_TCON_DRQ_SET(drq));
	पूर्ण

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_TCON_DRQ_REG, val);
पूर्ण

अटल व्योम sun6i_dsi_setup_inst_loop(काष्ठा sun6i_dsi *dsi,
				      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mipi_dsi_device *device = dsi->device;
	u16 delay = 50 - 1;

	अगर (device->mode_flags & MIPI_DSI_MODE_VIDEO_BURST) अणु
		u32 hsync_porch = (mode->htotal - mode->hdisplay) * 150;

		delay = (hsync_porch / ((mode->घड़ी / 1000) * 8));
		delay -= 50;
	पूर्ण

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_LOOP_SEL_REG,
		     2 << (4 * DSI_INST_ID_LP11) |
		     3 << (4 * DSI_INST_ID_DLY));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_LOOP_NUM_REG(0),
		     SUN6I_DSI_INST_LOOP_NUM_N0(50 - 1) |
		     SUN6I_DSI_INST_LOOP_NUM_N1(delay));
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_LOOP_NUM_REG(1),
		     SUN6I_DSI_INST_LOOP_NUM_N0(50 - 1) |
		     SUN6I_DSI_INST_LOOP_NUM_N1(delay));
पूर्ण

अटल व्योम sun6i_dsi_setup_क्रमmat(काष्ठा sun6i_dsi *dsi,
				   काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mipi_dsi_device *device = dsi->device;
	u32 val = SUN6I_DSI_PIXEL_PH_VC(device->channel);
	u8 dt, fmt;
	u16 wc;

	/*
	 * TODO: The क्रमmat defines are only valid in video mode and
	 * change in command mode.
	 */
	चयन (device->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		dt = MIPI_DSI_PACKED_PIXEL_STREAM_24;
		fmt = 8;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		dt = MIPI_DSI_PIXEL_STREAM_3BYTE_18;
		fmt = 9;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		dt = MIPI_DSI_PACKED_PIXEL_STREAM_18;
		fmt = 10;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		dt = MIPI_DSI_PACKED_PIXEL_STREAM_16;
		fmt = 11;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	val |= SUN6I_DSI_PIXEL_PH_DT(dt);

	wc = mode->hdisplay * mipi_dsi_pixel_क्रमmat_to_bpp(device->क्रमmat) / 8;
	val |= SUN6I_DSI_PIXEL_PH_WC(wc);
	val |= SUN6I_DSI_PIXEL_PH_ECC(sun6i_dsi_ecc_compute(val));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_PIXEL_PH_REG, val);

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_PIXEL_PF0_REG,
		     SUN6I_DSI_PIXEL_PF0_CRC_FORCE(0xffff));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_PIXEL_PF1_REG,
		     SUN6I_DSI_PIXEL_PF1_CRC_INIT_LINE0(0xffff) |
		     SUN6I_DSI_PIXEL_PF1_CRC_INIT_LINEN(0xffff));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_PIXEL_CTL0_REG,
		     SUN6I_DSI_PIXEL_CTL0_PD_PLUG_DISABLE |
		     SUN6I_DSI_PIXEL_CTL0_FORMAT(fmt));
पूर्ण

अटल व्योम sun6i_dsi_setup_timings(काष्ठा sun6i_dsi *dsi,
				    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mipi_dsi_device *device = dsi->device;
	अचिन्हित पूर्णांक Bpp = mipi_dsi_pixel_क्रमmat_to_bpp(device->क्रमmat) / 8;
	u16 hbp = 0, hfp = 0, hsa = 0, hblk = 0, vblk = 0;
	u32 basic_ctl = 0;
	माप_प्रकार bytes;
	u8 *buffer;

	/* Do all timing calculations up front to allocate buffer space */

	अगर (device->mode_flags & MIPI_DSI_MODE_VIDEO_BURST) अणु
		hblk = mode->hdisplay * Bpp;
		basic_ctl = SUN6I_DSI_BASIC_CTL_VIDEO_BURST |
			    SUN6I_DSI_BASIC_CTL_HSA_HSE_DIS |
			    SUN6I_DSI_BASIC_CTL_HBP_DIS;

		अगर (device->lanes == 4)
			basic_ctl |= SUN6I_DSI_BASIC_CTL_TRAIL_FILL |
				     SUN6I_DSI_BASIC_CTL_TRAIL_INV(0xc);
	पूर्ण अन्यथा अणु
		/*
		 * A sync period is composed of a blanking packet (4
		 * bytes + payload + 2 bytes) and a sync event packet
		 * (4 bytes). Its minimal size is thereक्रमe 10 bytes
		 */
#घोषणा HSA_PACKET_OVERHEAD	10
		hsa = max((अचिन्हित पूर्णांक)HSA_PACKET_OVERHEAD,
			  (mode->hsync_end - mode->hsync_start) * Bpp - HSA_PACKET_OVERHEAD);

		/*
		 * The backporch is set using a blanking packet (4
		 * bytes + payload + 2 bytes). Its minimal size is
		 * thereक्रमe 6 bytes
		 */
#घोषणा HBP_PACKET_OVERHEAD	6
		hbp = max((अचिन्हित पूर्णांक)HBP_PACKET_OVERHEAD,
			  (mode->htotal - mode->hsync_end) * Bpp - HBP_PACKET_OVERHEAD);

		/*
		 * The frontporch is set using a sync event (4 bytes)
		 * and two blanking packets (each one is 4 bytes +
		 * payload + 2 bytes). Its minimal size is thereक्रमe
		 * 16 bytes
		 */
#घोषणा HFP_PACKET_OVERHEAD	16
		hfp = max((अचिन्हित पूर्णांक)HFP_PACKET_OVERHEAD,
			  (mode->hsync_start - mode->hdisplay) * Bpp - HFP_PACKET_OVERHEAD);

		/*
		 * The blanking is set using a sync event (4 bytes)
		 * and a blanking packet (4 bytes + payload + 2
		 * bytes). Its minimal size is thereक्रमe 10 bytes.
		 */
#घोषणा HBLK_PACKET_OVERHEAD	10
		hblk = max((अचिन्हित पूर्णांक)HBLK_PACKET_OVERHEAD,
			   (mode->htotal - (mode->hsync_end - mode->hsync_start)) * Bpp -
			   HBLK_PACKET_OVERHEAD);

		/*
		 * And I'm not entirely sure what vblk is about. The driver in
		 * Allwinner BSP is using a rather convoluted calculation
		 * there only क्रम 4 lanes. However, using 0 (the !4 lanes
		 * हाल) even with a 4 lanes screen seems to work...
		 */
		vblk = 0;
	पूर्ण

	/* How many bytes करो we need to send all payloads? */
	bytes = max_t(माप_प्रकार, max(max(hfp, hblk), max(hsa, hbp)), vblk);
	buffer = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (WARN_ON(!buffer))
		वापस;

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BASIC_CTL_REG, basic_ctl);

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_SYNC_HSS_REG,
		     sun6i_dsi_build_sync_pkt(MIPI_DSI_H_SYNC_START,
					      device->channel,
					      0, 0));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_SYNC_HSE_REG,
		     sun6i_dsi_build_sync_pkt(MIPI_DSI_H_SYNC_END,
					      device->channel,
					      0, 0));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_SYNC_VSS_REG,
		     sun6i_dsi_build_sync_pkt(MIPI_DSI_V_SYNC_START,
					      device->channel,
					      0, 0));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_SYNC_VSE_REG,
		     sun6i_dsi_build_sync_pkt(MIPI_DSI_V_SYNC_END,
					      device->channel,
					      0, 0));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BASIC_SIZE0_REG,
		     SUN6I_DSI_BASIC_SIZE0_VSA(mode->vsync_end -
					       mode->vsync_start) |
		     SUN6I_DSI_BASIC_SIZE0_VBP(mode->vtotal -
					       mode->vsync_end));

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BASIC_SIZE1_REG,
		     SUN6I_DSI_BASIC_SIZE1_VACT(mode->vdisplay) |
		     SUN6I_DSI_BASIC_SIZE1_VT(mode->vtotal));

	/* sync */
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_HSA0_REG,
		     sun6i_dsi_build_blk0_pkt(device->channel, hsa));
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_HSA1_REG,
		     sun6i_dsi_build_blk1_pkt(0, buffer, hsa));

	/* backporch */
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_HBP0_REG,
		     sun6i_dsi_build_blk0_pkt(device->channel, hbp));
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_HBP1_REG,
		     sun6i_dsi_build_blk1_pkt(0, buffer, hbp));

	/* frontporch */
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_HFP0_REG,
		     sun6i_dsi_build_blk0_pkt(device->channel, hfp));
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_HFP1_REG,
		     sun6i_dsi_build_blk1_pkt(0, buffer, hfp));

	/* hblk */
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_HBLK0_REG,
		     sun6i_dsi_build_blk0_pkt(device->channel, hblk));
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_HBLK1_REG,
		     sun6i_dsi_build_blk1_pkt(0, buffer, hblk));

	/* vblk */
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_VBLK0_REG,
		     sun6i_dsi_build_blk0_pkt(device->channel, vblk));
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BLK_VBLK1_REG,
		     sun6i_dsi_build_blk1_pkt(0, buffer, vblk));

	kमुक्त(buffer);
पूर्ण

अटल पूर्णांक sun6i_dsi_start(काष्ठा sun6i_dsi *dsi,
			   क्रमागत sun6i_dsi_start_inst func)
अणु
	चयन (func) अणु
	हाल DSI_START_LPTX:
		regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_LPDT << (4 * DSI_INST_ID_LP11) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_LPDT));
		अवरोध;
	हाल DSI_START_LPRX:
		regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_LPDT << (4 * DSI_INST_ID_LP11) |
			     DSI_INST_ID_DLY  << (4 * DSI_INST_ID_LPDT) |
			     DSI_INST_ID_TBA  << (4 * DSI_INST_ID_DLY) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_TBA));
		अवरोध;
	हाल DSI_START_HSC:
		regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_HSC  << (4 * DSI_INST_ID_LP11) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_HSC));
		अवरोध;
	हाल DSI_START_HSD:
		regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_NOP  << (4 * DSI_INST_ID_LP11) |
			     DSI_INST_ID_HSD  << (4 * DSI_INST_ID_NOP) |
			     DSI_INST_ID_DLY  << (4 * DSI_INST_ID_HSD) |
			     DSI_INST_ID_NOP  << (4 * DSI_INST_ID_DLY) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_HSCEXIT));
		अवरोध;
	शेष:
		regmap_ग_लिखो(dsi->regs, SUN6I_DSI_INST_JUMP_SEL_REG,
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_LP11));
		अवरोध;
	पूर्ण

	sun6i_dsi_inst_पात(dsi);
	sun6i_dsi_inst_commit(dsi);

	अगर (func == DSI_START_HSC)
		regmap_ग_लिखो_bits(dsi->regs,
				  SUN6I_DSI_INST_FUNC_REG(DSI_INST_ID_LP11),
				  SUN6I_DSI_INST_FUNC_LANE_CEN, 0);

	वापस 0;
पूर्ण

अटल व्योम sun6i_dsi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	काष्ठा sun6i_dsi *dsi = encoder_to_sun6i_dsi(encoder);
	काष्ठा mipi_dsi_device *device = dsi->device;
	जोड़ phy_configure_opts opts = अणु पूर्ण;
	काष्ठा phy_configure_opts_mipi_dphy *cfg = &opts.mipi_dphy;
	u16 delay;
	पूर्णांक err;

	DRM_DEBUG_DRIVER("Enabling DSI output\n");

	err = regulator_enable(dsi->regulator);
	अगर (err)
		dev_warn(dsi->dev, "failed to enable VCC-DSI supply: %d\n", err);

	reset_control_deनिश्चित(dsi->reset);
	clk_prepare_enable(dsi->mod_clk);

	/*
	 * Enable the DSI block.
	 */
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_CTL_REG, SUN6I_DSI_CTL_EN);

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BASIC_CTL0_REG,
		     SUN6I_DSI_BASIC_CTL0_ECC_EN | SUN6I_DSI_BASIC_CTL0_CRC_EN);

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_TRANS_START_REG, 10);
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_TRANS_ZERO_REG, 0);

	sun6i_dsi_inst_init(dsi, dsi->device);

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_DEBUG_DATA_REG, 0xff);

	delay = sun6i_dsi_get_video_start_delay(dsi, mode);
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_BASIC_CTL1_REG,
		     SUN6I_DSI_BASIC_CTL1_VIDEO_ST_DELAY(delay) |
		     SUN6I_DSI_BASIC_CTL1_VIDEO_FILL |
		     SUN6I_DSI_BASIC_CTL1_VIDEO_PRECISION |
		     SUN6I_DSI_BASIC_CTL1_VIDEO_MODE);

	sun6i_dsi_setup_burst(dsi, mode);
	sun6i_dsi_setup_inst_loop(dsi, mode);
	sun6i_dsi_setup_क्रमmat(dsi, mode);
	sun6i_dsi_setup_timings(dsi, mode);

	phy_init(dsi->dphy);

	phy_mipi_dphy_get_शेष_config(mode->घड़ी * 1000,
					 mipi_dsi_pixel_क्रमmat_to_bpp(device->क्रमmat),
					 device->lanes, cfg);

	phy_set_mode(dsi->dphy, PHY_MODE_MIPI_DPHY);
	phy_configure(dsi->dphy, &opts);
	phy_घातer_on(dsi->dphy);

	अगर (dsi->panel)
		drm_panel_prepare(dsi->panel);

	/*
	 * FIXME: This should be moved after the चयन to HS mode.
	 *
	 * Unक्रमtunately, once in HS mode, it seems like we're not
	 * able to send DCS commands anymore, which would prevent any
	 * panel to send any DCS command as part as their enable
	 * method, which is quite common.
	 *
	 * I haven't seen any artअगरact due to that sub-optimal
	 * ordering on the panels I've tested it with, so I guess this
	 * will करो क्रम now, until that IP is better understood.
	 */
	अगर (dsi->panel)
		drm_panel_enable(dsi->panel);

	sun6i_dsi_start(dsi, DSI_START_HSC);

	udelay(1000);

	sun6i_dsi_start(dsi, DSI_START_HSD);
पूर्ण

अटल व्योम sun6i_dsi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun6i_dsi *dsi = encoder_to_sun6i_dsi(encoder);

	DRM_DEBUG_DRIVER("Disabling DSI output\n");

	अगर (dsi->panel) अणु
		drm_panel_disable(dsi->panel);
		drm_panel_unprepare(dsi->panel);
	पूर्ण

	phy_घातer_off(dsi->dphy);
	phy_निकास(dsi->dphy);

	clk_disable_unprepare(dsi->mod_clk);
	reset_control_निश्चित(dsi->reset);
	regulator_disable(dsi->regulator);
पूर्ण

अटल पूर्णांक sun6i_dsi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा sun6i_dsi *dsi = connector_to_sun6i_dsi(connector);

	वापस drm_panel_get_modes(dsi->panel, connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs sun6i_dsi_connector_helper_funcs = अणु
	.get_modes	= sun6i_dsi_get_modes,
पूर्ण;

अटल क्रमागत drm_connector_status
sun6i_dsi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा sun6i_dsi *dsi = connector_to_sun6i_dsi(connector);

	वापस dsi->panel ? connector_status_connected :
			    connector_status_disconnected;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sun6i_dsi_connector_funcs = अणु
	.detect			= sun6i_dsi_connector_detect,
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= drm_connector_cleanup,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs sun6i_dsi_enc_helper_funcs = अणु
	.disable	= sun6i_dsi_encoder_disable,
	.enable		= sun6i_dsi_encoder_enable,
पूर्ण;

अटल u32 sun6i_dsi_dcs_build_pkt_hdr(काष्ठा sun6i_dsi *dsi,
				       स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	u32 pkt = msg->type;

	अगर (msg->type == MIPI_DSI_DCS_LONG_WRITE) अणु
		pkt |= ((msg->tx_len) & 0xffff) << 8;
		pkt |= (((msg->tx_len) >> 8) & 0xffff) << 16;
	पूर्ण अन्यथा अणु
		pkt |= (((u8 *)msg->tx_buf)[0] << 8);
		अगर (msg->tx_len > 1)
			pkt |= (((u8 *)msg->tx_buf)[1] << 16);
	पूर्ण

	pkt |= sun6i_dsi_ecc_compute(pkt) << 24;

	वापस pkt;
पूर्ण

अटल पूर्णांक sun6i_dsi_dcs_ग_लिखो_लघु(काष्ठा sun6i_dsi *dsi,
				     स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_CMD_TX_REG(0),
		     sun6i_dsi_dcs_build_pkt_hdr(dsi, msg));
	regmap_ग_लिखो_bits(dsi->regs, SUN6I_DSI_CMD_CTL_REG,
			  0xff, (4 - 1));

	sun6i_dsi_start(dsi, DSI_START_LPTX);

	वापस msg->tx_len;
पूर्ण

अटल पूर्णांक sun6i_dsi_dcs_ग_लिखो_दीर्घ(काष्ठा sun6i_dsi *dsi,
				    स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	पूर्णांक ret, len = 0;
	u8 *bounce;
	u16 crc;

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_CMD_TX_REG(0),
		     sun6i_dsi_dcs_build_pkt_hdr(dsi, msg));

	bounce = kzalloc(ALIGN(msg->tx_len + माप(crc), 4), GFP_KERNEL);
	अगर (!bounce)
		वापस -ENOMEM;

	स_नकल(bounce, msg->tx_buf, msg->tx_len);
	len += msg->tx_len;

	crc = sun6i_dsi_crc_compute(bounce, msg->tx_len);
	स_नकल((u8 *)bounce + msg->tx_len, &crc, माप(crc));
	len += माप(crc);

	regmap_bulk_ग_लिखो(dsi->regs, SUN6I_DSI_CMD_TX_REG(1), bounce, DIV_ROUND_UP(len, 4));
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_CMD_CTL_REG, len + 4 - 1);
	kमुक्त(bounce);

	sun6i_dsi_start(dsi, DSI_START_LPTX);

	ret = sun6i_dsi_inst_रुको_क्रम_completion(dsi);
	अगर (ret < 0) अणु
		sun6i_dsi_inst_पात(dsi);
		वापस ret;
	पूर्ण

	/*
	 * TODO: There's some bits (reg 0x200, bits 8/9) that
	 * apparently can be used to check whether the data have been
	 * sent, but I couldn't get it to work reliably.
	 */
	वापस msg->tx_len;
पूर्ण

अटल पूर्णांक sun6i_dsi_dcs_पढ़ो(काष्ठा sun6i_dsi *dsi,
			      स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	u32 val;
	पूर्णांक ret;
	u8 byte0;

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_CMD_TX_REG(0),
		     sun6i_dsi_dcs_build_pkt_hdr(dsi, msg));
	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_CMD_CTL_REG,
		     (4 - 1));

	sun6i_dsi_start(dsi, DSI_START_LPRX);

	ret = sun6i_dsi_inst_रुको_क्रम_completion(dsi);
	अगर (ret < 0) अणु
		sun6i_dsi_inst_पात(dsi);
		वापस ret;
	पूर्ण

	/*
	 * TODO: There's some bits (reg 0x200, bits 24/25) that
	 * apparently can be used to check whether the data have been
	 * received, but I couldn't get it to work reliably.
	 */
	regmap_पढ़ो(dsi->regs, SUN6I_DSI_CMD_CTL_REG, &val);
	अगर (val & SUN6I_DSI_CMD_CTL_RX_OVERFLOW)
		वापस -EIO;

	regmap_पढ़ो(dsi->regs, SUN6I_DSI_CMD_RX_REG(0), &val);
	byte0 = val & 0xff;
	अगर (byte0 == MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT)
		वापस -EIO;

	((u8 *)msg->rx_buf)[0] = (val >> 8);

	वापस 1;
पूर्ण

अटल पूर्णांक sun6i_dsi_attach(काष्ठा mipi_dsi_host *host,
			    काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा sun6i_dsi *dsi = host_to_sun6i_dsi(host);
	काष्ठा drm_panel *panel = of_drm_find_panel(device->dev.of_node);

	अगर (IS_ERR(panel))
		वापस PTR_ERR(panel);
	अगर (!dsi->drm || !dsi->drm->रेजिस्टरed)
		वापस -EPROBE_DEFER;

	dsi->panel = panel;
	dsi->device = device;

	drm_kms_helper_hotplug_event(dsi->drm);

	dev_info(host->dev, "Attached device %s\n", device->name);

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_dsi_detach(काष्ठा mipi_dsi_host *host,
			    काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा sun6i_dsi *dsi = host_to_sun6i_dsi(host);

	dsi->panel = शून्य;
	dsi->device = शून्य;

	drm_kms_helper_hotplug_event(dsi->drm);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sun6i_dsi_transfer(काष्ठा mipi_dsi_host *host,
				  स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा sun6i_dsi *dsi = host_to_sun6i_dsi(host);
	पूर्णांक ret;

	ret = sun6i_dsi_inst_रुको_क्रम_completion(dsi);
	अगर (ret < 0)
		sun6i_dsi_inst_पात(dsi);

	regmap_ग_लिखो(dsi->regs, SUN6I_DSI_CMD_CTL_REG,
		     SUN6I_DSI_CMD_CTL_RX_OVERFLOW |
		     SUN6I_DSI_CMD_CTL_RX_FLAG |
		     SUN6I_DSI_CMD_CTL_TX_FLAG);

	चयन (msg->type) अणु
	हाल MIPI_DSI_DCS_SHORT_WRITE:
	हाल MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
		ret = sun6i_dsi_dcs_ग_लिखो_लघु(dsi, msg);
		अवरोध;

	हाल MIPI_DSI_DCS_LONG_WRITE:
		ret = sun6i_dsi_dcs_ग_लिखो_दीर्घ(dsi, msg);
		अवरोध;

	हाल MIPI_DSI_DCS_READ:
		अगर (msg->rx_len == 1) अणु
			ret = sun6i_dsi_dcs_पढ़ो(dsi, msg);
			अवरोध;
		पूर्ण
		fallthrough;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops sun6i_dsi_host_ops = अणु
	.attach		= sun6i_dsi_attach,
	.detach		= sun6i_dsi_detach,
	.transfer	= sun6i_dsi_transfer,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun6i_dsi_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= SUN6I_DSI_CMD_TX_REG(255),
	.name		= "mipi-dsi",
पूर्ण;

अटल पूर्णांक sun6i_dsi_bind(काष्ठा device *dev, काष्ठा device *master,
			 व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा sun6i_dsi *dsi = dev_get_drvdata(dev);
	पूर्णांक ret;

	drm_encoder_helper_add(&dsi->encoder,
			       &sun6i_dsi_enc_helper_funcs);
	ret = drm_simple_encoder_init(drm, &dsi->encoder,
				      DRM_MODE_ENCODER_DSI);
	अगर (ret) अणु
		dev_err(dsi->dev, "Couldn't initialise the DSI encoder\n");
		वापस ret;
	पूर्ण
	dsi->encoder.possible_crtcs = BIT(0);

	drm_connector_helper_add(&dsi->connector,
				 &sun6i_dsi_connector_helper_funcs);
	ret = drm_connector_init(drm, &dsi->connector,
				 &sun6i_dsi_connector_funcs,
				 DRM_MODE_CONNECTOR_DSI);
	अगर (ret) अणु
		dev_err(dsi->dev,
			"Couldn't initialise the DSI connector\n");
		जाओ err_cleanup_connector;
	पूर्ण

	drm_connector_attach_encoder(&dsi->connector, &dsi->encoder);

	dsi->drm = drm;

	वापस 0;

err_cleanup_connector:
	drm_encoder_cleanup(&dsi->encoder);
	वापस ret;
पूर्ण

अटल व्योम sun6i_dsi_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा sun6i_dsi *dsi = dev_get_drvdata(dev);

	dsi->drm = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops sun6i_dsi_ops = अणु
	.bind	= sun6i_dsi_bind,
	.unbind	= sun6i_dsi_unbind,
पूर्ण;

अटल पूर्णांक sun6i_dsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर अक्षर *bus_clk_name = शून्य;
	काष्ठा sun6i_dsi *dsi;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;
	dev_set_drvdata(dev, dsi);
	dsi->dev = dev;
	dsi->host.ops = &sun6i_dsi_host_ops;
	dsi->host.dev = dev;

	अगर (of_device_is_compatible(dev->of_node,
				    "allwinner,sun6i-a31-mipi-dsi"))
		bus_clk_name = "bus";

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base)) अणु
		dev_err(dev, "Couldn't map the DSI encoder registers\n");
		वापस PTR_ERR(base);
	पूर्ण

	dsi->regulator = devm_regulator_get(dev, "vcc-dsi");
	अगर (IS_ERR(dsi->regulator)) अणु
		dev_err(dev, "Couldn't get VCC-DSI supply\n");
		वापस PTR_ERR(dsi->regulator);
	पूर्ण

	dsi->reset = devm_reset_control_get_shared(dev, शून्य);
	अगर (IS_ERR(dsi->reset)) अणु
		dev_err(dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(dsi->reset);
	पूर्ण

	dsi->regs = devm_regmap_init_mmio(dev, base, &sun6i_dsi_regmap_config);
	अगर (IS_ERR(dsi->regs)) अणु
		dev_err(dev, "Couldn't init regmap\n");
		वापस PTR_ERR(dsi->regs);
	पूर्ण

	dsi->bus_clk = devm_clk_get(dev, bus_clk_name);
	अगर (IS_ERR(dsi->bus_clk)) अणु
		dev_err(dev, "Couldn't get the DSI bus clock\n");
		वापस PTR_ERR(dsi->bus_clk);
	पूर्ण

	ret = regmap_mmio_attach_clk(dsi->regs, dsi->bus_clk);
	अगर (ret)
		वापस ret;

	अगर (of_device_is_compatible(dev->of_node,
				    "allwinner,sun6i-a31-mipi-dsi")) अणु
		dsi->mod_clk = devm_clk_get(dev, "mod");
		अगर (IS_ERR(dsi->mod_clk)) अणु
			dev_err(dev, "Couldn't get the DSI mod clock\n");
			ret = PTR_ERR(dsi->mod_clk);
			जाओ err_attach_clk;
		पूर्ण
	पूर्ण

	/*
	 * In order to operate properly, that घड़ी seems to be always
	 * set to 297MHz.
	 */
	clk_set_rate_exclusive(dsi->mod_clk, 297000000);

	dsi->dphy = devm_phy_get(dev, "dphy");
	अगर (IS_ERR(dsi->dphy)) अणु
		dev_err(dev, "Couldn't get the MIPI D-PHY\n");
		ret = PTR_ERR(dsi->dphy);
		जाओ err_unprotect_clk;
	पूर्ण

	ret = mipi_dsi_host_रेजिस्टर(&dsi->host);
	अगर (ret) अणु
		dev_err(dev, "Couldn't register MIPI-DSI host\n");
		जाओ err_unprotect_clk;
	पूर्ण

	ret = component_add(&pdev->dev, &sun6i_dsi_ops);
	अगर (ret) अणु
		dev_err(dev, "Couldn't register our component\n");
		जाओ err_हटाओ_dsi_host;
	पूर्ण

	वापस 0;

err_हटाओ_dsi_host:
	mipi_dsi_host_unरेजिस्टर(&dsi->host);
err_unprotect_clk:
	clk_rate_exclusive_put(dsi->mod_clk);
err_attach_clk:
	अगर (!IS_ERR(dsi->bus_clk))
		regmap_mmio_detach_clk(dsi->regs);
	वापस ret;
पूर्ण

अटल पूर्णांक sun6i_dsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sun6i_dsi *dsi = dev_get_drvdata(dev);

	component_del(&pdev->dev, &sun6i_dsi_ops);
	mipi_dsi_host_unरेजिस्टर(&dsi->host);
	clk_rate_exclusive_put(dsi->mod_clk);

	अगर (!IS_ERR(dsi->bus_clk))
		regmap_mmio_detach_clk(dsi->regs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_dsi_of_table[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-mipi-dsi" पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-mipi-dsi" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun6i_dsi_of_table);

अटल काष्ठा platक्रमm_driver sun6i_dsi_platक्रमm_driver = अणु
	.probe		= sun6i_dsi_probe,
	.हटाओ		= sun6i_dsi_हटाओ,
	.driver		= अणु
		.name		= "sun6i-mipi-dsi",
		.of_match_table	= sun6i_dsi_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun6i_dsi_platक्रमm_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A31 DSI Driver");
MODULE_LICENSE("GPL");
