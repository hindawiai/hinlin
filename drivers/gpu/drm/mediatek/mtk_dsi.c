<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/mipi_display.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_bridge_connector.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "mtk_disp_drv.h"
#समावेश "mtk_drm_ddp_comp.h"

#घोषणा DSI_START		0x00

#घोषणा DSI_INTEN		0x08

#घोषणा DSI_INTSTA		0x0c
#घोषणा LPRX_RD_RDY_INT_FLAG		BIT(0)
#घोषणा CMD_DONE_INT_FLAG		BIT(1)
#घोषणा TE_RDY_INT_FLAG			BIT(2)
#घोषणा VM_DONE_INT_FLAG		BIT(3)
#घोषणा EXT_TE_RDY_INT_FLAG		BIT(4)
#घोषणा DSI_BUSY			BIT(31)

#घोषणा DSI_CON_CTRL		0x10
#घोषणा DSI_RESET			BIT(0)
#घोषणा DSI_EN				BIT(1)
#घोषणा DPHY_RESET			BIT(2)

#घोषणा DSI_MODE_CTRL		0x14
#घोषणा MODE				(3)
#घोषणा CMD_MODE			0
#घोषणा SYNC_PULSE_MODE			1
#घोषणा SYNC_EVENT_MODE			2
#घोषणा BURST_MODE			3
#घोषणा FRM_MODE			BIT(16)
#घोषणा MIX_MODE			BIT(17)

#घोषणा DSI_TXRX_CTRL		0x18
#घोषणा VC_NUM				BIT(1)
#घोषणा LANE_NUM			(0xf << 2)
#घोषणा DIS_EOT				BIT(6)
#घोषणा शून्य_EN				BIT(7)
#घोषणा TE_FREERUN			BIT(8)
#घोषणा EXT_TE_EN			BIT(9)
#घोषणा EXT_TE_EDGE			BIT(10)
#घोषणा MAX_RTN_SIZE			(0xf << 12)
#घोषणा HSTX_CKLP_EN			BIT(16)

#घोषणा DSI_PSCTRL		0x1c
#घोषणा DSI_PS_WC			0x3fff
#घोषणा DSI_PS_SEL			(3 << 16)
#घोषणा PACKED_PS_16BIT_RGB565		(0 << 16)
#घोषणा LOOSELY_PS_18BIT_RGB666		(1 << 16)
#घोषणा PACKED_PS_18BIT_RGB666		(2 << 16)
#घोषणा PACKED_PS_24BIT_RGB888		(3 << 16)

#घोषणा DSI_VSA_NL		0x20
#घोषणा DSI_VBP_NL		0x24
#घोषणा DSI_VFP_NL		0x28
#घोषणा DSI_VACT_NL		0x2C
#घोषणा DSI_SIZE_CON		0x38
#घोषणा DSI_HSA_WC		0x50
#घोषणा DSI_HBP_WC		0x54
#घोषणा DSI_HFP_WC		0x58

#घोषणा DSI_CMDQ_SIZE		0x60
#घोषणा CMDQ_SIZE			0x3f

#घोषणा DSI_HSTX_CKL_WC		0x64

#घोषणा DSI_RX_DATA0		0x74
#घोषणा DSI_RX_DATA1		0x78
#घोषणा DSI_RX_DATA2		0x7c
#घोषणा DSI_RX_DATA3		0x80

#घोषणा DSI_RACK		0x84
#घोषणा RACK				BIT(0)

#घोषणा DSI_PHY_LCCON		0x104
#घोषणा LC_HS_TX_EN			BIT(0)
#घोषणा LC_ULPM_EN			BIT(1)
#घोषणा LC_WAKEUP_EN			BIT(2)

#घोषणा DSI_PHY_LD0CON		0x108
#घोषणा LD0_HS_TX_EN			BIT(0)
#घोषणा LD0_ULPM_EN			BIT(1)
#घोषणा LD0_WAKEUP_EN			BIT(2)

#घोषणा DSI_PHY_TIMECON0	0x110
#घोषणा LPX				(0xff << 0)
#घोषणा HS_PREP				(0xff << 8)
#घोषणा HS_ZERO				(0xff << 16)
#घोषणा HS_TRAIL			(0xff << 24)

#घोषणा DSI_PHY_TIMECON1	0x114
#घोषणा TA_GO				(0xff << 0)
#घोषणा TA_SURE				(0xff << 8)
#घोषणा TA_GET				(0xff << 16)
#घोषणा DA_HS_EXIT			(0xff << 24)

#घोषणा DSI_PHY_TIMECON2	0x118
#घोषणा CONT_DET			(0xff << 0)
#घोषणा CLK_ZERO			(0xff << 16)
#घोषणा CLK_TRAIL			(0xff << 24)

#घोषणा DSI_PHY_TIMECON3	0x11c
#घोषणा CLK_HS_PREP			(0xff << 0)
#घोषणा CLK_HS_POST			(0xff << 8)
#घोषणा CLK_HS_EXIT			(0xff << 16)

#घोषणा DSI_VM_CMD_CON		0x130
#घोषणा VM_CMD_EN			BIT(0)
#घोषणा TS_VFP_EN			BIT(5)

#घोषणा DSI_SHADOW_DEBUG	0x190U
#घोषणा FORCE_COMMIT			BIT(0)
#घोषणा BYPASS_SHADOW			BIT(1)

#घोषणा CONFIG				(0xff << 0)
#घोषणा SHORT_PACKET			0
#घोषणा LONG_PACKET			2
#घोषणा BTA				BIT(2)
#घोषणा DATA_ID				(0xff << 8)
#घोषणा DATA_0				(0xff << 16)
#घोषणा DATA_1				(0xff << 24)

#घोषणा NS_TO_CYCLE(n, c)    ((n) / (c) + (((n) % (c)) ? 1 : 0))

#घोषणा MTK_DSI_HOST_IS_READ(type) \
	((type == MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM) || \
	(type == MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM) || \
	(type == MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM) || \
	(type == MIPI_DSI_DCS_READ))

काष्ठा mtk_phy_timing अणु
	u32 lpx;
	u32 da_hs_prepare;
	u32 da_hs_zero;
	u32 da_hs_trail;

	u32 ta_go;
	u32 ta_sure;
	u32 ta_get;
	u32 da_hs_निकास;

	u32 clk_hs_zero;
	u32 clk_hs_trail;

	u32 clk_hs_prepare;
	u32 clk_hs_post;
	u32 clk_hs_निकास;
पूर्ण;

काष्ठा phy;

काष्ठा mtk_dsi_driver_data अणु
	स्थिर u32 reg_cmdq_off;
	bool has_shaकरोw_ctl;
	bool has_size_ctl;
पूर्ण;

काष्ठा mtk_dsi अणु
	काष्ठा device *dev;
	काष्ठा mipi_dsi_host host;
	काष्ठा drm_encoder encoder;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *next_bridge;
	काष्ठा drm_connector *connector;
	काष्ठा phy *phy;

	व्योम __iomem *regs;

	काष्ठा clk *engine_clk;
	काष्ठा clk *digital_clk;
	काष्ठा clk *hs_clk;

	u32 data_rate;

	अचिन्हित दीर्घ mode_flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक lanes;
	काष्ठा videomode vm;
	काष्ठा mtk_phy_timing phy_timing;
	पूर्णांक refcount;
	bool enabled;
	u32 irq_data;
	रुको_queue_head_t irq_रुको_queue;
	स्थिर काष्ठा mtk_dsi_driver_data *driver_data;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_dsi *bridge_to_dsi(काष्ठा drm_bridge *b)
अणु
	वापस container_of(b, काष्ठा mtk_dsi, bridge);
पूर्ण

अटल अंतरभूत काष्ठा mtk_dsi *host_to_dsi(काष्ठा mipi_dsi_host *h)
अणु
	वापस container_of(h, काष्ठा mtk_dsi, host);
पूर्ण

अटल व्योम mtk_dsi_mask(काष्ठा mtk_dsi *dsi, u32 offset, u32 mask, u32 data)
अणु
	u32 temp = पढ़ोl(dsi->regs + offset);

	ग_लिखोl((temp & ~mask) | (data & mask), dsi->regs + offset);
पूर्ण

अटल व्योम mtk_dsi_phy_timconfig(काष्ठा mtk_dsi *dsi)
अणु
	u32 timcon0, timcon1, timcon2, timcon3;
	u32 data_rate_mhz = DIV_ROUND_UP(dsi->data_rate, 1000000);
	काष्ठा mtk_phy_timing *timing = &dsi->phy_timing;

	timing->lpx = (60 * data_rate_mhz / (8 * 1000)) + 1;
	timing->da_hs_prepare = (80 * data_rate_mhz + 4 * 1000) / 8000;
	timing->da_hs_zero = (170 * data_rate_mhz + 10 * 1000) / 8000 + 1 -
			     timing->da_hs_prepare;
	timing->da_hs_trail = timing->da_hs_prepare + 1;

	timing->ta_go = 4 * timing->lpx - 2;
	timing->ta_sure = timing->lpx + 2;
	timing->ta_get = 4 * timing->lpx;
	timing->da_hs_निकास = 2 * timing->lpx + 1;

	timing->clk_hs_prepare = 70 * data_rate_mhz / (8 * 1000);
	timing->clk_hs_post = timing->clk_hs_prepare + 8;
	timing->clk_hs_trail = timing->clk_hs_prepare;
	timing->clk_hs_zero = timing->clk_hs_trail * 4;
	timing->clk_hs_निकास = 2 * timing->clk_hs_trail;

	timcon0 = timing->lpx | timing->da_hs_prepare << 8 |
		  timing->da_hs_zero << 16 | timing->da_hs_trail << 24;
	timcon1 = timing->ta_go | timing->ta_sure << 8 |
		  timing->ta_get << 16 | timing->da_hs_निकास << 24;
	timcon2 = 1 << 8 | timing->clk_hs_zero << 16 |
		  timing->clk_hs_trail << 24;
	timcon3 = timing->clk_hs_prepare | timing->clk_hs_post << 8 |
		  timing->clk_hs_निकास << 16;

	ग_लिखोl(timcon0, dsi->regs + DSI_PHY_TIMECON0);
	ग_लिखोl(timcon1, dsi->regs + DSI_PHY_TIMECON1);
	ग_लिखोl(timcon2, dsi->regs + DSI_PHY_TIMECON2);
	ग_लिखोl(timcon3, dsi->regs + DSI_PHY_TIMECON3);
पूर्ण

अटल व्योम mtk_dsi_enable(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_CON_CTRL, DSI_EN, DSI_EN);
पूर्ण

अटल व्योम mtk_dsi_disable(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_CON_CTRL, DSI_EN, 0);
पूर्ण

अटल व्योम mtk_dsi_reset_engine(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_CON_CTRL, DSI_RESET, DSI_RESET);
	mtk_dsi_mask(dsi, DSI_CON_CTRL, DSI_RESET, 0);
पूर्ण

अटल व्योम mtk_dsi_reset_dphy(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_CON_CTRL, DPHY_RESET, DPHY_RESET);
	mtk_dsi_mask(dsi, DSI_CON_CTRL, DPHY_RESET, 0);
पूर्ण

अटल व्योम mtk_dsi_clk_ulp_mode_enter(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_PHY_LCCON, LC_HS_TX_EN, 0);
	mtk_dsi_mask(dsi, DSI_PHY_LCCON, LC_ULPM_EN, 0);
पूर्ण

अटल व्योम mtk_dsi_clk_ulp_mode_leave(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_PHY_LCCON, LC_ULPM_EN, 0);
	mtk_dsi_mask(dsi, DSI_PHY_LCCON, LC_WAKEUP_EN, LC_WAKEUP_EN);
	mtk_dsi_mask(dsi, DSI_PHY_LCCON, LC_WAKEUP_EN, 0);
पूर्ण

अटल व्योम mtk_dsi_lane0_ulp_mode_enter(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_PHY_LD0CON, LD0_HS_TX_EN, 0);
	mtk_dsi_mask(dsi, DSI_PHY_LD0CON, LD0_ULPM_EN, 0);
पूर्ण

अटल व्योम mtk_dsi_lane0_ulp_mode_leave(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_PHY_LD0CON, LD0_ULPM_EN, 0);
	mtk_dsi_mask(dsi, DSI_PHY_LD0CON, LD0_WAKEUP_EN, LD0_WAKEUP_EN);
	mtk_dsi_mask(dsi, DSI_PHY_LD0CON, LD0_WAKEUP_EN, 0);
पूर्ण

अटल bool mtk_dsi_clk_hs_state(काष्ठा mtk_dsi *dsi)
अणु
	वापस पढ़ोl(dsi->regs + DSI_PHY_LCCON) & LC_HS_TX_EN;
पूर्ण

अटल व्योम mtk_dsi_clk_hs_mode(काष्ठा mtk_dsi *dsi, bool enter)
अणु
	अगर (enter && !mtk_dsi_clk_hs_state(dsi))
		mtk_dsi_mask(dsi, DSI_PHY_LCCON, LC_HS_TX_EN, LC_HS_TX_EN);
	अन्यथा अगर (!enter && mtk_dsi_clk_hs_state(dsi))
		mtk_dsi_mask(dsi, DSI_PHY_LCCON, LC_HS_TX_EN, 0);
पूर्ण

अटल व्योम mtk_dsi_set_mode(काष्ठा mtk_dsi *dsi)
अणु
	u32 vid_mode = CMD_MODE;

	अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
			vid_mode = BURST_MODE;
		अन्यथा अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
			vid_mode = SYNC_PULSE_MODE;
		अन्यथा
			vid_mode = SYNC_EVENT_MODE;
	पूर्ण

	ग_लिखोl(vid_mode, dsi->regs + DSI_MODE_CTRL);
पूर्ण

अटल व्योम mtk_dsi_set_vm_cmd(काष्ठा mtk_dsi *dsi)
अणु
	mtk_dsi_mask(dsi, DSI_VM_CMD_CON, VM_CMD_EN, VM_CMD_EN);
	mtk_dsi_mask(dsi, DSI_VM_CMD_CON, TS_VFP_EN, TS_VFP_EN);
पूर्ण

अटल व्योम mtk_dsi_ps_control_vact(काष्ठा mtk_dsi *dsi)
अणु
	काष्ठा videomode *vm = &dsi->vm;
	u32 dsi_buf_bpp, ps_wc;
	u32 ps_bpp_mode;

	अगर (dsi->क्रमmat == MIPI_DSI_FMT_RGB565)
		dsi_buf_bpp = 2;
	अन्यथा
		dsi_buf_bpp = 3;

	ps_wc = vm->hactive * dsi_buf_bpp;
	ps_bpp_mode = ps_wc;

	चयन (dsi->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		ps_bpp_mode |= PACKED_PS_24BIT_RGB888;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		ps_bpp_mode |= PACKED_PS_18BIT_RGB666;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		ps_bpp_mode |= LOOSELY_PS_18BIT_RGB666;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		ps_bpp_mode |= PACKED_PS_16BIT_RGB565;
		अवरोध;
	पूर्ण

	ग_लिखोl(vm->vactive, dsi->regs + DSI_VACT_NL);
	ग_लिखोl(ps_bpp_mode, dsi->regs + DSI_PSCTRL);
	ग_लिखोl(ps_wc, dsi->regs + DSI_HSTX_CKL_WC);
पूर्ण

अटल व्योम mtk_dsi_rxtx_control(काष्ठा mtk_dsi *dsi)
अणु
	u32 पंचांगp_reg;

	चयन (dsi->lanes) अणु
	हाल 1:
		पंचांगp_reg = 1 << 2;
		अवरोध;
	हाल 2:
		पंचांगp_reg = 3 << 2;
		अवरोध;
	हाल 3:
		पंचांगp_reg = 7 << 2;
		अवरोध;
	हाल 4:
		पंचांगp_reg = 0xf << 2;
		अवरोध;
	शेष:
		पंचांगp_reg = 0xf << 2;
		अवरोध;
	पूर्ण

	अगर (dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS)
		पंचांगp_reg |= HSTX_CKLP_EN;

	अगर (!(dsi->mode_flags & MIPI_DSI_MODE_EOT_PACKET))
		पंचांगp_reg |= DIS_EOT;

	ग_लिखोl(पंचांगp_reg, dsi->regs + DSI_TXRX_CTRL);
पूर्ण

अटल व्योम mtk_dsi_ps_control(काष्ठा mtk_dsi *dsi)
अणु
	u32 dsi_पंचांगp_buf_bpp;
	u32 पंचांगp_reg;

	चयन (dsi->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		पंचांगp_reg = PACKED_PS_24BIT_RGB888;
		dsi_पंचांगp_buf_bpp = 3;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		पंचांगp_reg = LOOSELY_PS_18BIT_RGB666;
		dsi_पंचांगp_buf_bpp = 3;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		पंचांगp_reg = PACKED_PS_18BIT_RGB666;
		dsi_पंचांगp_buf_bpp = 3;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		पंचांगp_reg = PACKED_PS_16BIT_RGB565;
		dsi_पंचांगp_buf_bpp = 2;
		अवरोध;
	शेष:
		पंचांगp_reg = PACKED_PS_24BIT_RGB888;
		dsi_पंचांगp_buf_bpp = 3;
		अवरोध;
	पूर्ण

	पंचांगp_reg += dsi->vm.hactive * dsi_पंचांगp_buf_bpp & DSI_PS_WC;
	ग_लिखोl(पंचांगp_reg, dsi->regs + DSI_PSCTRL);
पूर्ण

अटल व्योम mtk_dsi_config_vकरो_timing(काष्ठा mtk_dsi *dsi)
अणु
	u32 horizontal_sync_active_byte;
	u32 horizontal_backporch_byte;
	u32 horizontal_frontporch_byte;
	u32 horizontal_front_back_byte;
	u32 data_phy_cycles_byte;
	u32 dsi_पंचांगp_buf_bpp, data_phy_cycles;
	u32 delta;
	काष्ठा mtk_phy_timing *timing = &dsi->phy_timing;

	काष्ठा videomode *vm = &dsi->vm;

	अगर (dsi->क्रमmat == MIPI_DSI_FMT_RGB565)
		dsi_पंचांगp_buf_bpp = 2;
	अन्यथा
		dsi_पंचांगp_buf_bpp = 3;

	ग_लिखोl(vm->vsync_len, dsi->regs + DSI_VSA_NL);
	ग_लिखोl(vm->vback_porch, dsi->regs + DSI_VBP_NL);
	ग_लिखोl(vm->vfront_porch, dsi->regs + DSI_VFP_NL);
	ग_लिखोl(vm->vactive, dsi->regs + DSI_VACT_NL);

	अगर (dsi->driver_data->has_size_ctl)
		ग_लिखोl(vm->vactive << 16 | vm->hactive,
		       dsi->regs + DSI_SIZE_CON);

	horizontal_sync_active_byte = (vm->hsync_len * dsi_पंचांगp_buf_bpp - 10);

	अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		horizontal_backporch_byte = vm->hback_porch * dsi_पंचांगp_buf_bpp - 10;
	अन्यथा
		horizontal_backporch_byte = (vm->hback_porch + vm->hsync_len) *
					    dsi_पंचांगp_buf_bpp - 10;

	data_phy_cycles = timing->lpx + timing->da_hs_prepare +
			  timing->da_hs_zero + timing->da_hs_निकास + 3;

	delta = dsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST ? 18 : 12;
	delta += dsi->mode_flags & MIPI_DSI_MODE_EOT_PACKET ? 2 : 0;

	horizontal_frontporch_byte = vm->hfront_porch * dsi_पंचांगp_buf_bpp;
	horizontal_front_back_byte = horizontal_frontporch_byte + horizontal_backporch_byte;
	data_phy_cycles_byte = data_phy_cycles * dsi->lanes + delta;

	अगर (horizontal_front_back_byte > data_phy_cycles_byte) अणु
		horizontal_frontporch_byte -= data_phy_cycles_byte *
					      horizontal_frontporch_byte /
					      horizontal_front_back_byte;

		horizontal_backporch_byte -= data_phy_cycles_byte *
					     horizontal_backporch_byte /
					     horizontal_front_back_byte;
	पूर्ण अन्यथा अणु
		DRM_WARN("HFP + HBP less than d-phy, FPS will under 60Hz\n");
	पूर्ण

	ग_लिखोl(horizontal_sync_active_byte, dsi->regs + DSI_HSA_WC);
	ग_लिखोl(horizontal_backporch_byte, dsi->regs + DSI_HBP_WC);
	ग_लिखोl(horizontal_frontporch_byte, dsi->regs + DSI_HFP_WC);

	mtk_dsi_ps_control(dsi);
पूर्ण

अटल व्योम mtk_dsi_start(काष्ठा mtk_dsi *dsi)
अणु
	ग_लिखोl(0, dsi->regs + DSI_START);
	ग_लिखोl(1, dsi->regs + DSI_START);
पूर्ण

अटल व्योम mtk_dsi_stop(काष्ठा mtk_dsi *dsi)
अणु
	ग_लिखोl(0, dsi->regs + DSI_START);
पूर्ण

अटल व्योम mtk_dsi_set_cmd_mode(काष्ठा mtk_dsi *dsi)
अणु
	ग_लिखोl(CMD_MODE, dsi->regs + DSI_MODE_CTRL);
पूर्ण

अटल व्योम mtk_dsi_set_पूर्णांकerrupt_enable(काष्ठा mtk_dsi *dsi)
अणु
	u32 पूर्णांकen = LPRX_RD_RDY_INT_FLAG | CMD_DONE_INT_FLAG | VM_DONE_INT_FLAG;

	ग_लिखोl(पूर्णांकen, dsi->regs + DSI_INTEN);
पूर्ण

अटल व्योम mtk_dsi_irq_data_set(काष्ठा mtk_dsi *dsi, u32 irq_bit)
अणु
	dsi->irq_data |= irq_bit;
पूर्ण

अटल व्योम mtk_dsi_irq_data_clear(काष्ठा mtk_dsi *dsi, u32 irq_bit)
अणु
	dsi->irq_data &= ~irq_bit;
पूर्ण

अटल s32 mtk_dsi_रुको_क्रम_irq_करोne(काष्ठा mtk_dsi *dsi, u32 irq_flag,
				     अचिन्हित पूर्णांक समयout)
अणु
	s32 ret = 0;
	अचिन्हित दीर्घ jअगरfies = msecs_to_jअगरfies(समयout);

	ret = रुको_event_पूर्णांकerruptible_समयout(dsi->irq_रुको_queue,
					       dsi->irq_data & irq_flag,
					       jअगरfies);
	अगर (ret == 0) अणु
		DRM_WARN("Wait DSI IRQ(0x%08x) Timeout\n", irq_flag);

		mtk_dsi_enable(dsi);
		mtk_dsi_reset_engine(dsi);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t mtk_dsi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mtk_dsi *dsi = dev_id;
	u32 status, पंचांगp;
	u32 flag = LPRX_RD_RDY_INT_FLAG | CMD_DONE_INT_FLAG | VM_DONE_INT_FLAG;

	status = पढ़ोl(dsi->regs + DSI_INTSTA) & flag;

	अगर (status) अणु
		करो अणु
			mtk_dsi_mask(dsi, DSI_RACK, RACK, RACK);
			पंचांगp = पढ़ोl(dsi->regs + DSI_INTSTA);
		पूर्ण जबतक (पंचांगp & DSI_BUSY);

		mtk_dsi_mask(dsi, DSI_INTSTA, status, 0);
		mtk_dsi_irq_data_set(dsi, status);
		wake_up_पूर्णांकerruptible(&dsi->irq_रुको_queue);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल s32 mtk_dsi_चयन_to_cmd_mode(काष्ठा mtk_dsi *dsi, u8 irq_flag, u32 t)
अणु
	mtk_dsi_irq_data_clear(dsi, irq_flag);
	mtk_dsi_set_cmd_mode(dsi);

	अगर (!mtk_dsi_रुको_क्रम_irq_करोne(dsi, irq_flag, t)) अणु
		DRM_ERROR("failed to switch cmd mode\n");
		वापस -ETIME;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_dsi_घातeron(काष्ठा mtk_dsi *dsi)
अणु
	काष्ठा device *dev = dsi->host.dev;
	पूर्णांक ret;
	u32 bit_per_pixel;

	अगर (++dsi->refcount != 1)
		वापस 0;

	चयन (dsi->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB565:
		bit_per_pixel = 16;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		bit_per_pixel = 18;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
	हाल MIPI_DSI_FMT_RGB888:
	शेष:
		bit_per_pixel = 24;
		अवरोध;
	पूर्ण

	dsi->data_rate = DIV_ROUND_UP_ULL(dsi->vm.pixelघड़ी * bit_per_pixel,
					  dsi->lanes);

	ret = clk_set_rate(dsi->hs_clk, dsi->data_rate);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set data rate: %d\n", ret);
		जाओ err_refcount;
	पूर्ण

	phy_घातer_on(dsi->phy);

	ret = clk_prepare_enable(dsi->engine_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable engine clock: %d\n", ret);
		जाओ err_phy_घातer_off;
	पूर्ण

	ret = clk_prepare_enable(dsi->digital_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable digital clock: %d\n", ret);
		जाओ err_disable_engine_clk;
	पूर्ण

	mtk_dsi_enable(dsi);

	अगर (dsi->driver_data->has_shaकरोw_ctl)
		ग_लिखोl(FORCE_COMMIT | BYPASS_SHADOW,
		       dsi->regs + DSI_SHADOW_DEBUG);

	mtk_dsi_reset_engine(dsi);
	mtk_dsi_phy_timconfig(dsi);

	mtk_dsi_rxtx_control(dsi);
	usleep_range(30, 100);
	mtk_dsi_reset_dphy(dsi);
	mtk_dsi_ps_control_vact(dsi);
	mtk_dsi_set_vm_cmd(dsi);
	mtk_dsi_config_vकरो_timing(dsi);
	mtk_dsi_set_पूर्णांकerrupt_enable(dsi);

	mtk_dsi_clk_ulp_mode_leave(dsi);
	mtk_dsi_lane0_ulp_mode_leave(dsi);
	mtk_dsi_clk_hs_mode(dsi, 0);

	वापस 0;
err_disable_engine_clk:
	clk_disable_unprepare(dsi->engine_clk);
err_phy_घातer_off:
	phy_घातer_off(dsi->phy);
err_refcount:
	dsi->refcount--;
	वापस ret;
पूर्ण

अटल व्योम mtk_dsi_घातeroff(काष्ठा mtk_dsi *dsi)
अणु
	अगर (WARN_ON(dsi->refcount == 0))
		वापस;

	अगर (--dsi->refcount != 0)
		वापस;

	/*
	 * mtk_dsi_stop() and mtk_dsi_start() is asymmetric, since
	 * mtk_dsi_stop() should be called after mtk_drm_crtc_atomic_disable(),
	 * which needs irq क्रम vblank, and mtk_dsi_stop() will disable irq.
	 * mtk_dsi_start() needs to be called in mtk_output_dsi_enable(),
	 * after dsi is fully set.
	 */
	mtk_dsi_stop(dsi);

	mtk_dsi_चयन_to_cmd_mode(dsi, VM_DONE_INT_FLAG, 500);
	mtk_dsi_reset_engine(dsi);
	mtk_dsi_lane0_ulp_mode_enter(dsi);
	mtk_dsi_clk_ulp_mode_enter(dsi);

	mtk_dsi_disable(dsi);

	clk_disable_unprepare(dsi->engine_clk);
	clk_disable_unprepare(dsi->digital_clk);

	phy_घातer_off(dsi->phy);
पूर्ण

अटल व्योम mtk_output_dsi_enable(काष्ठा mtk_dsi *dsi)
अणु
	पूर्णांक ret;

	अगर (dsi->enabled)
		वापस;

	ret = mtk_dsi_घातeron(dsi);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to power on dsi\n");
		वापस;
	पूर्ण

	mtk_dsi_set_mode(dsi);
	mtk_dsi_clk_hs_mode(dsi, 1);

	mtk_dsi_start(dsi);

	dsi->enabled = true;
पूर्ण

अटल व्योम mtk_output_dsi_disable(काष्ठा mtk_dsi *dsi)
अणु
	अगर (!dsi->enabled)
		वापस;

	mtk_dsi_घातeroff(dsi);

	dsi->enabled = false;
पूर्ण

अटल पूर्णांक mtk_dsi_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा mtk_dsi *dsi = bridge_to_dsi(bridge);

	/* Attach the panel or bridge to the dsi bridge */
	वापस drm_bridge_attach(bridge->encoder, dsi->next_bridge,
				 &dsi->bridge, flags);
पूर्ण

अटल व्योम mtk_dsi_bridge_mode_set(काष्ठा drm_bridge *bridge,
				    स्थिर काष्ठा drm_display_mode *mode,
				    स्थिर काष्ठा drm_display_mode *adjusted)
अणु
	काष्ठा mtk_dsi *dsi = bridge_to_dsi(bridge);

	drm_display_mode_to_videomode(adjusted, &dsi->vm);
पूर्ण

अटल व्योम mtk_dsi_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा mtk_dsi *dsi = bridge_to_dsi(bridge);

	mtk_output_dsi_disable(dsi);
पूर्ण

अटल व्योम mtk_dsi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा mtk_dsi *dsi = bridge_to_dsi(bridge);

	mtk_output_dsi_enable(dsi);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs mtk_dsi_bridge_funcs = अणु
	.attach = mtk_dsi_bridge_attach,
	.disable = mtk_dsi_bridge_disable,
	.enable = mtk_dsi_bridge_enable,
	.mode_set = mtk_dsi_bridge_mode_set,
पूर्ण;

व्योम mtk_dsi_ddp_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_dsi *dsi = dev_get_drvdata(dev);

	mtk_dsi_घातeron(dsi);
पूर्ण

व्योम mtk_dsi_ddp_stop(काष्ठा device *dev)
अणु
	काष्ठा mtk_dsi *dsi = dev_get_drvdata(dev);

	mtk_dsi_घातeroff(dsi);
पूर्ण

अटल पूर्णांक mtk_dsi_host_attach(काष्ठा mipi_dsi_host *host,
			       काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा mtk_dsi *dsi = host_to_dsi(host);

	dsi->lanes = device->lanes;
	dsi->क्रमmat = device->क्रमmat;
	dsi->mode_flags = device->mode_flags;

	वापस 0;
पूर्ण

अटल व्योम mtk_dsi_रुको_क्रम_idle(काष्ठा mtk_dsi *dsi)
अणु
	पूर्णांक ret;
	u32 val;

	ret = पढ़ोl_poll_समयout(dsi->regs + DSI_INTSTA, val, !(val & DSI_BUSY),
				 4, 2000000);
	अगर (ret) अणु
		DRM_WARN("polling dsi wait not busy timeout!\n");

		mtk_dsi_enable(dsi);
		mtk_dsi_reset_engine(dsi);
	पूर्ण
पूर्ण

अटल u32 mtk_dsi_recv_cnt(u8 type, u8 *पढ़ो_data)
अणु
	चयन (type) अणु
	हाल MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE:
	हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE:
		वापस 1;
	हाल MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE:
	हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE:
		वापस 2;
	हाल MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE:
	हाल MIPI_DSI_RX_DCS_LONG_READ_RESPONSE:
		वापस पढ़ो_data[1] + पढ़ो_data[2] * 16;
	हाल MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT:
		DRM_INFO("type is 0x02, try again\n");
		अवरोध;
	शेष:
		DRM_INFO("type(0x%x) not recognized\n", type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_dsi_cmdq(काष्ठा mtk_dsi *dsi, स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	स्थिर अक्षर *tx_buf = msg->tx_buf;
	u8 config, cmdq_size, cmdq_off, type = msg->type;
	u32 reg_val, cmdq_mask, i;
	u32 reg_cmdq_off = dsi->driver_data->reg_cmdq_off;

	अगर (MTK_DSI_HOST_IS_READ(type))
		config = BTA;
	अन्यथा
		config = (msg->tx_len > 2) ? LONG_PACKET : SHORT_PACKET;

	अगर (msg->tx_len > 2) अणु
		cmdq_size = 1 + (msg->tx_len + 3) / 4;
		cmdq_off = 4;
		cmdq_mask = CONFIG | DATA_ID | DATA_0 | DATA_1;
		reg_val = (msg->tx_len << 16) | (type << 8) | config;
	पूर्ण अन्यथा अणु
		cmdq_size = 1;
		cmdq_off = 2;
		cmdq_mask = CONFIG | DATA_ID;
		reg_val = (type << 8) | config;
	पूर्ण

	क्रम (i = 0; i < msg->tx_len; i++)
		mtk_dsi_mask(dsi, (reg_cmdq_off + cmdq_off + i) & (~0x3U),
			     (0xffUL << (((i + cmdq_off) & 3U) * 8U)),
			     tx_buf[i] << (((i + cmdq_off) & 3U) * 8U));

	mtk_dsi_mask(dsi, reg_cmdq_off, cmdq_mask, reg_val);
	mtk_dsi_mask(dsi, DSI_CMDQ_SIZE, CMDQ_SIZE, cmdq_size);
पूर्ण

अटल sमाप_प्रकार mtk_dsi_host_send_cmd(काष्ठा mtk_dsi *dsi,
				     स्थिर काष्ठा mipi_dsi_msg *msg, u8 flag)
अणु
	mtk_dsi_रुको_क्रम_idle(dsi);
	mtk_dsi_irq_data_clear(dsi, flag);
	mtk_dsi_cmdq(dsi, msg);
	mtk_dsi_start(dsi);

	अगर (!mtk_dsi_रुको_क्रम_irq_करोne(dsi, flag, 2000))
		वापस -ETIME;
	अन्यथा
		वापस 0;
पूर्ण

अटल sमाप_प्रकार mtk_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
				     स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा mtk_dsi *dsi = host_to_dsi(host);
	u32 recv_cnt, i;
	u8 पढ़ो_data[16];
	व्योम *src_addr;
	u8 irq_flag = CMD_DONE_INT_FLAG;

	अगर (पढ़ोl(dsi->regs + DSI_MODE_CTRL) & MODE) अणु
		DRM_ERROR("dsi engine is not command mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (MTK_DSI_HOST_IS_READ(msg->type))
		irq_flag |= LPRX_RD_RDY_INT_FLAG;

	अगर (mtk_dsi_host_send_cmd(dsi, msg, irq_flag) < 0)
		वापस -ETIME;

	अगर (!MTK_DSI_HOST_IS_READ(msg->type))
		वापस 0;

	अगर (!msg->rx_buf) अणु
		DRM_ERROR("dsi receive buffer size may be NULL\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 16; i++)
		*(पढ़ो_data + i) = पढ़ोb(dsi->regs + DSI_RX_DATA0 + i);

	recv_cnt = mtk_dsi_recv_cnt(पढ़ो_data[0], पढ़ो_data);

	अगर (recv_cnt > 2)
		src_addr = &पढ़ो_data[4];
	अन्यथा
		src_addr = &पढ़ो_data[1];

	अगर (recv_cnt > 10)
		recv_cnt = 10;

	अगर (recv_cnt > msg->rx_len)
		recv_cnt = msg->rx_len;

	अगर (recv_cnt)
		स_नकल(msg->rx_buf, src_addr, recv_cnt);

	DRM_INFO("dsi get %d byte data from the panel address(0x%x)\n",
		 recv_cnt, *((u8 *)(msg->tx_buf)));

	वापस recv_cnt;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops mtk_dsi_ops = अणु
	.attach = mtk_dsi_host_attach,
	.transfer = mtk_dsi_host_transfer,
पूर्ण;

अटल पूर्णांक mtk_dsi_encoder_init(काष्ठा drm_device *drm, काष्ठा mtk_dsi *dsi)
अणु
	पूर्णांक ret;

	ret = drm_simple_encoder_init(drm, &dsi->encoder,
				      DRM_MODE_ENCODER_DSI);
	अगर (ret) अणु
		DRM_ERROR("Failed to encoder init to drm\n");
		वापस ret;
	पूर्ण

	dsi->encoder.possible_crtcs = mtk_drm_find_possible_crtc_by_comp(drm, dsi->host.dev);

	ret = drm_bridge_attach(&dsi->encoder, &dsi->bridge, शून्य,
				DRM_BRIDGE_ATTACH_NO_CONNECTOR);
	अगर (ret)
		जाओ err_cleanup_encoder;

	dsi->connector = drm_bridge_connector_init(drm, &dsi->encoder);
	अगर (IS_ERR(dsi->connector)) अणु
		DRM_ERROR("Unable to create bridge connector\n");
		ret = PTR_ERR(dsi->connector);
		जाओ err_cleanup_encoder;
	पूर्ण
	drm_connector_attach_encoder(dsi->connector, &dsi->encoder);

	वापस 0;

err_cleanup_encoder:
	drm_encoder_cleanup(&dsi->encoder);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_dsi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा drm_device *drm = data;
	काष्ठा mtk_dsi *dsi = dev_get_drvdata(dev);

	ret = mtk_dsi_encoder_init(drm, dsi);

	वापस ret;
पूर्ण

अटल व्योम mtk_dsi_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा mtk_dsi *dsi = dev_get_drvdata(dev);

	drm_encoder_cleanup(&dsi->encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops mtk_dsi_component_ops = अणु
	.bind = mtk_dsi_bind,
	.unbind = mtk_dsi_unbind,
पूर्ण;

अटल पूर्णांक mtk_dsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_dsi *dsi;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा drm_panel *panel;
	काष्ठा resource *regs;
	पूर्णांक irq_num;
	पूर्णांक ret;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;

	dsi->host.ops = &mtk_dsi_ops;
	dsi->host.dev = dev;
	ret = mipi_dsi_host_रेजिस्टर(&dsi->host);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register DSI host: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0,
					  &panel, &dsi->next_bridge);
	अगर (ret)
		जाओ err_unरेजिस्टर_host;

	अगर (panel) अणु
		dsi->next_bridge = devm_drm_panel_bridge_add(dev, panel);
		अगर (IS_ERR(dsi->next_bridge)) अणु
			ret = PTR_ERR(dsi->next_bridge);
			जाओ err_unरेजिस्टर_host;
		पूर्ण
	पूर्ण

	dsi->driver_data = of_device_get_match_data(dev);

	dsi->engine_clk = devm_clk_get(dev, "engine");
	अगर (IS_ERR(dsi->engine_clk)) अणु
		ret = PTR_ERR(dsi->engine_clk);

		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get engine clock: %d\n", ret);
		जाओ err_unरेजिस्टर_host;
	पूर्ण

	dsi->digital_clk = devm_clk_get(dev, "digital");
	अगर (IS_ERR(dsi->digital_clk)) अणु
		ret = PTR_ERR(dsi->digital_clk);

		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get digital clock: %d\n", ret);
		जाओ err_unरेजिस्टर_host;
	पूर्ण

	dsi->hs_clk = devm_clk_get(dev, "hs");
	अगर (IS_ERR(dsi->hs_clk)) अणु
		ret = PTR_ERR(dsi->hs_clk);
		dev_err(dev, "Failed to get hs clock: %d\n", ret);
		जाओ err_unरेजिस्टर_host;
	पूर्ण

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->regs = devm_ioremap_resource(dev, regs);
	अगर (IS_ERR(dsi->regs)) अणु
		ret = PTR_ERR(dsi->regs);
		dev_err(dev, "Failed to ioremap memory: %d\n", ret);
		जाओ err_unरेजिस्टर_host;
	पूर्ण

	dsi->phy = devm_phy_get(dev, "dphy");
	अगर (IS_ERR(dsi->phy)) अणु
		ret = PTR_ERR(dsi->phy);
		dev_err(dev, "Failed to get MIPI-DPHY: %d\n", ret);
		जाओ err_unरेजिस्टर_host;
	पूर्ण

	irq_num = platक्रमm_get_irq(pdev, 0);
	अगर (irq_num < 0) अणु
		dev_err(&pdev->dev, "failed to get dsi irq_num: %d\n", irq_num);
		ret = irq_num;
		जाओ err_unरेजिस्टर_host;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq_num, mtk_dsi_irq,
			       IRQF_TRIGGER_NONE, dev_name(&pdev->dev), dsi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request mediatek dsi irq\n");
		जाओ err_unरेजिस्टर_host;
	पूर्ण

	init_रुकोqueue_head(&dsi->irq_रुको_queue);

	platक्रमm_set_drvdata(pdev, dsi);

	dsi->bridge.funcs = &mtk_dsi_bridge_funcs;
	dsi->bridge.of_node = dev->of_node;
	dsi->bridge.type = DRM_MODE_CONNECTOR_DSI;

	drm_bridge_add(&dsi->bridge);

	ret = component_add(&pdev->dev, &mtk_dsi_component_ops);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add component: %d\n", ret);
		जाओ err_unरेजिस्टर_host;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_host:
	mipi_dsi_host_unरेजिस्टर(&dsi->host);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_dsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_dsi *dsi = platक्रमm_get_drvdata(pdev);

	mtk_output_dsi_disable(dsi);
	drm_bridge_हटाओ(&dsi->bridge);
	component_del(&pdev->dev, &mtk_dsi_component_ops);
	mipi_dsi_host_unरेजिस्टर(&dsi->host);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_dsi_driver_data mt8173_dsi_driver_data = अणु
	.reg_cmdq_off = 0x200,
पूर्ण;

अटल स्थिर काष्ठा mtk_dsi_driver_data mt2701_dsi_driver_data = अणु
	.reg_cmdq_off = 0x180,
पूर्ण;

अटल स्थिर काष्ठा mtk_dsi_driver_data mt8183_dsi_driver_data = अणु
	.reg_cmdq_off = 0x200,
	.has_shaकरोw_ctl = true,
	.has_size_ctl = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_dsi_of_match[] = अणु
	अणु .compatible = "mediatek,mt2701-dsi",
	  .data = &mt2701_dsi_driver_data पूर्ण,
	अणु .compatible = "mediatek,mt8173-dsi",
	  .data = &mt8173_dsi_driver_data पूर्ण,
	अणु .compatible = "mediatek,mt8183-dsi",
	  .data = &mt8183_dsi_driver_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_dsi_of_match);

काष्ठा platक्रमm_driver mtk_dsi_driver = अणु
	.probe = mtk_dsi_probe,
	.हटाओ = mtk_dsi_हटाओ,
	.driver = अणु
		.name = "mtk-dsi",
		.of_match_table = mtk_dsi_of_match,
	पूर्ण,
पूर्ण;
