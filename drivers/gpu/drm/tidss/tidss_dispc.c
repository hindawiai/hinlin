<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/sys_soc.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_panel.h>

#समावेश "tidss_crtc.h"
#समावेश "tidss_dispc.h"
#समावेश "tidss_drv.h"
#समावेश "tidss_irq.h"
#समावेश "tidss_plane.h"

#समावेश "tidss_dispc_regs.h"
#समावेश "tidss_scale_coefs.h"

अटल स्थिर u16 tidss_k2g_common_regs[DISPC_COMMON_REG_TABLE_LEN] = अणु
	[DSS_REVISION_OFF] =                    0x00,
	[DSS_SYSCONFIG_OFF] =                   0x04,
	[DSS_SYSSTATUS_OFF] =                   0x08,
	[DISPC_IRQ_EOI_OFF] =                   0x20,
	[DISPC_IRQSTATUS_RAW_OFF] =             0x24,
	[DISPC_IRQSTATUS_OFF] =                 0x28,
	[DISPC_IRQENABLE_SET_OFF] =             0x2c,
	[DISPC_IRQENABLE_CLR_OFF] =             0x30,

	[DISPC_GLOBAL_MFLAG_ATTRIBUTE_OFF] =    0x40,
	[DISPC_GLOBAL_BUFFER_OFF] =             0x44,

	[DISPC_DBG_CONTROL_OFF] =               0x4c,
	[DISPC_DBG_STATUS_OFF] =                0x50,

	[DISPC_CLKGATING_DISABLE_OFF] =         0x54,
पूर्ण;

स्थिर काष्ठा dispc_features dispc_k2g_feats = अणु
	.min_pclk_khz = 4375,

	.max_pclk_khz = अणु
		[DISPC_VP_DPI] = 150000,
	पूर्ण,

	/*
	 * XXX According TRM the RGB input buffer width up to 2560 should
	 *     work on 3 taps, but in practice it only works up to 1280.
	 */
	.scaling = अणु
		.in_width_max_5tap_rgb = 1280,
		.in_width_max_3tap_rgb = 1280,
		.in_width_max_5tap_yuv = 2560,
		.in_width_max_3tap_yuv = 2560,
		.upscale_limit = 16,
		.करोwnscale_limit_5tap = 4,
		.करोwnscale_limit_3tap = 2,
		/*
		 * The max supported pixel inc value is 255. The value
		 * of pixel inc is calculated like this: 1+(xinc-1)*bpp.
		 * The maximum bpp of all क्रमmats supported by the HW
		 * is 8. So the maximum supported xinc value is 32,
		 * because 1+(32-1)*8 < 255 < 1+(33-1)*4.
		 */
		.xinc_max = 32,
	पूर्ण,

	.subrev = DISPC_K2G,

	.common = "common",

	.common_regs = tidss_k2g_common_regs,

	.num_vps = 1,
	.vp_name = अणु "vp1" पूर्ण,
	.ovr_name = अणु "ovr1" पूर्ण,
	.vpclk_name =  अणु "vp1" पूर्ण,
	.vp_bus_type = अणु DISPC_VP_DPI पूर्ण,

	.vp_feat = अणु .color = अणु
			.has_cपंचांग = true,
			.gamma_size = 256,
			.gamma_type = TIDSS_GAMMA_8BIT,
		पूर्ण,
	पूर्ण,

	.num_planes = 1,
	.vid_name = अणु "vid1" पूर्ण,
	.vid_lite = अणु false पूर्ण,
	.vid_order = अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर u16 tidss_am65x_common_regs[DISPC_COMMON_REG_TABLE_LEN] = अणु
	[DSS_REVISION_OFF] =			0x4,
	[DSS_SYSCONFIG_OFF] =			0x8,
	[DSS_SYSSTATUS_OFF] =			0x20,
	[DISPC_IRQ_EOI_OFF] =			0x24,
	[DISPC_IRQSTATUS_RAW_OFF] =		0x28,
	[DISPC_IRQSTATUS_OFF] =			0x2c,
	[DISPC_IRQENABLE_SET_OFF] =		0x30,
	[DISPC_IRQENABLE_CLR_OFF] =		0x40,
	[DISPC_VID_IRQENABLE_OFF] =		0x44,
	[DISPC_VID_IRQSTATUS_OFF] =		0x58,
	[DISPC_VP_IRQENABLE_OFF] =		0x70,
	[DISPC_VP_IRQSTATUS_OFF] =		0x7c,

	[WB_IRQENABLE_OFF] =			0x88,
	[WB_IRQSTATUS_OFF] =			0x8c,

	[DISPC_GLOBAL_MFLAG_ATTRIBUTE_OFF] =	0x90,
	[DISPC_GLOBAL_OUTPUT_ENABLE_OFF] =	0x94,
	[DISPC_GLOBAL_BUFFER_OFF] =		0x98,
	[DSS_CBA_CFG_OFF] =			0x9c,
	[DISPC_DBG_CONTROL_OFF] =		0xa0,
	[DISPC_DBG_STATUS_OFF] =		0xa4,
	[DISPC_CLKGATING_DISABLE_OFF] =		0xa8,
	[DISPC_SECURE_DISABLE_OFF] =		0xac,
पूर्ण;

स्थिर काष्ठा dispc_features dispc_am65x_feats = अणु
	.max_pclk_khz = अणु
		[DISPC_VP_DPI] = 165000,
		[DISPC_VP_OLDI] = 165000,
	पूर्ण,

	.scaling = अणु
		.in_width_max_5tap_rgb = 1280,
		.in_width_max_3tap_rgb = 2560,
		.in_width_max_5tap_yuv = 2560,
		.in_width_max_3tap_yuv = 4096,
		.upscale_limit = 16,
		.करोwnscale_limit_5tap = 4,
		.करोwnscale_limit_3tap = 2,
		/*
		 * The max supported pixel inc value is 255. The value
		 * of pixel inc is calculated like this: 1+(xinc-1)*bpp.
		 * The maximum bpp of all क्रमmats supported by the HW
		 * is 8. So the maximum supported xinc value is 32,
		 * because 1+(32-1)*8 < 255 < 1+(33-1)*4.
		 */
		.xinc_max = 32,
	पूर्ण,

	.subrev = DISPC_AM65X,

	.common = "common",
	.common_regs = tidss_am65x_common_regs,

	.num_vps = 2,
	.vp_name = अणु "vp1", "vp2" पूर्ण,
	.ovr_name = अणु "ovr1", "ovr2" पूर्ण,
	.vpclk_name =  अणु "vp1", "vp2" पूर्ण,
	.vp_bus_type = अणु DISPC_VP_OLDI, DISPC_VP_DPI पूर्ण,

	.vp_feat = अणु .color = अणु
			.has_cपंचांग = true,
			.gamma_size = 256,
			.gamma_type = TIDSS_GAMMA_8BIT,
		पूर्ण,
	पूर्ण,

	.num_planes = 2,
	/* note: vid is plane_id 0 and vidl1 is plane_id 1 */
	.vid_name = अणु "vid", "vidl1" पूर्ण,
	.vid_lite = अणु false, true, पूर्ण,
	.vid_order = अणु 1, 0 पूर्ण,
पूर्ण;

अटल स्थिर u16 tidss_j721e_common_regs[DISPC_COMMON_REG_TABLE_LEN] = अणु
	[DSS_REVISION_OFF] =			0x4,
	[DSS_SYSCONFIG_OFF] =			0x8,
	[DSS_SYSSTATUS_OFF] =			0x20,
	[DISPC_IRQ_EOI_OFF] =			0x80,
	[DISPC_IRQSTATUS_RAW_OFF] =		0x28,
	[DISPC_IRQSTATUS_OFF] =			0x2c,
	[DISPC_IRQENABLE_SET_OFF] =		0x30,
	[DISPC_IRQENABLE_CLR_OFF] =		0x34,
	[DISPC_VID_IRQENABLE_OFF] =		0x38,
	[DISPC_VID_IRQSTATUS_OFF] =		0x48,
	[DISPC_VP_IRQENABLE_OFF] =		0x58,
	[DISPC_VP_IRQSTATUS_OFF] =		0x68,

	[WB_IRQENABLE_OFF] =			0x78,
	[WB_IRQSTATUS_OFF] =			0x7c,

	[DISPC_GLOBAL_MFLAG_ATTRIBUTE_OFF] =	0x98,
	[DISPC_GLOBAL_OUTPUT_ENABLE_OFF] =	0x9c,
	[DISPC_GLOBAL_BUFFER_OFF] =		0xa0,
	[DSS_CBA_CFG_OFF] =			0xa4,
	[DISPC_DBG_CONTROL_OFF] =		0xa8,
	[DISPC_DBG_STATUS_OFF] =		0xac,
	[DISPC_CLKGATING_DISABLE_OFF] =		0xb0,
	[DISPC_SECURE_DISABLE_OFF] =		0x90,

	[FBDC_REVISION_1_OFF] =			0xb8,
	[FBDC_REVISION_2_OFF] =			0xbc,
	[FBDC_REVISION_3_OFF] =			0xc0,
	[FBDC_REVISION_4_OFF] =			0xc4,
	[FBDC_REVISION_5_OFF] =			0xc8,
	[FBDC_REVISION_6_OFF] =			0xcc,
	[FBDC_COMMON_CONTROL_OFF] =		0xd0,
	[FBDC_CONSTANT_COLOR_0_OFF] =		0xd4,
	[FBDC_CONSTANT_COLOR_1_OFF] =		0xd8,
	[DISPC_CONNECTIONS_OFF] =		0xe4,
	[DISPC_MSS_VP1_OFF] =			0xe8,
	[DISPC_MSS_VP3_OFF] =			0xec,
पूर्ण;

स्थिर काष्ठा dispc_features dispc_j721e_feats = अणु
	.max_pclk_khz = अणु
		[DISPC_VP_DPI] = 170000,
		[DISPC_VP_INTERNAL] = 600000,
	पूर्ण,

	.scaling = अणु
		.in_width_max_5tap_rgb = 2048,
		.in_width_max_3tap_rgb = 4096,
		.in_width_max_5tap_yuv = 4096,
		.in_width_max_3tap_yuv = 4096,
		.upscale_limit = 16,
		.करोwnscale_limit_5tap = 4,
		.करोwnscale_limit_3tap = 2,
		/*
		 * The max supported pixel inc value is 255. The value
		 * of pixel inc is calculated like this: 1+(xinc-1)*bpp.
		 * The maximum bpp of all क्रमmats supported by the HW
		 * is 8. So the maximum supported xinc value is 32,
		 * because 1+(32-1)*8 < 255 < 1+(33-1)*4.
		 */
		.xinc_max = 32,
	पूर्ण,

	.subrev = DISPC_J721E,

	.common = "common_m",
	.common_regs = tidss_j721e_common_regs,

	.num_vps = 4,
	.vp_name = अणु "vp1", "vp2", "vp3", "vp4" पूर्ण,
	.ovr_name = अणु "ovr1", "ovr2", "ovr3", "ovr4" पूर्ण,
	.vpclk_name = अणु "vp1", "vp2", "vp3", "vp4" पूर्ण,
	/* Currently hard coded VP routing (see dispc_initial_config()) */
	.vp_bus_type =	अणु DISPC_VP_INTERNAL, DISPC_VP_DPI,
			  DISPC_VP_INTERNAL, DISPC_VP_DPI, पूर्ण,
	.vp_feat = अणु .color = अणु
			.has_cपंचांग = true,
			.gamma_size = 1024,
			.gamma_type = TIDSS_GAMMA_10BIT,
		पूर्ण,
	पूर्ण,
	.num_planes = 4,
	.vid_name = अणु "vid1", "vidl1", "vid2", "vidl2" पूर्ण,
	.vid_lite = अणु 0, 1, 0, 1, पूर्ण,
	.vid_order = अणु 1, 3, 0, 2 पूर्ण,
पूर्ण;

अटल स्थिर u16 *dispc_common_regmap;

काष्ठा dss_vp_data अणु
	u32 *gamma_table;
पूर्ण;

काष्ठा dispc_device अणु
	काष्ठा tidss_device *tidss;
	काष्ठा device *dev;

	व्योम __iomem *base_common;
	व्योम __iomem *base_vid[TIDSS_MAX_PLANES];
	व्योम __iomem *base_ovr[TIDSS_MAX_PORTS];
	व्योम __iomem *base_vp[TIDSS_MAX_PORTS];

	काष्ठा regmap *oldi_io_ctrl;

	काष्ठा clk *vp_clk[TIDSS_MAX_PORTS];

	स्थिर काष्ठा dispc_features *feat;

	काष्ठा clk *fclk;

	bool is_enabled;

	काष्ठा dss_vp_data vp_data[TIDSS_MAX_PORTS];

	u32 *fourccs;
	u32 num_fourccs;

	u32 memory_bandwidth_limit;

	काष्ठा dispc_errata errata;
पूर्ण;

अटल व्योम dispc_ग_लिखो(काष्ठा dispc_device *dispc, u16 reg, u32 val)
अणु
	ioग_लिखो32(val, dispc->base_common + reg);
पूर्ण

अटल u32 dispc_पढ़ो(काष्ठा dispc_device *dispc, u16 reg)
अणु
	वापस ioपढ़ो32(dispc->base_common + reg);
पूर्ण

अटल
व्योम dispc_vid_ग_लिखो(काष्ठा dispc_device *dispc, u32 hw_plane, u16 reg, u32 val)
अणु
	व्योम __iomem *base = dispc->base_vid[hw_plane];

	ioग_लिखो32(val, base + reg);
पूर्ण

अटल u32 dispc_vid_पढ़ो(काष्ठा dispc_device *dispc, u32 hw_plane, u16 reg)
अणु
	व्योम __iomem *base = dispc->base_vid[hw_plane];

	वापस ioपढ़ो32(base + reg);
पूर्ण

अटल व्योम dispc_ovr_ग_लिखो(काष्ठा dispc_device *dispc, u32 hw_videoport,
			    u16 reg, u32 val)
अणु
	व्योम __iomem *base = dispc->base_ovr[hw_videoport];

	ioग_लिखो32(val, base + reg);
पूर्ण

अटल u32 dispc_ovr_पढ़ो(काष्ठा dispc_device *dispc, u32 hw_videoport, u16 reg)
अणु
	व्योम __iomem *base = dispc->base_ovr[hw_videoport];

	वापस ioपढ़ो32(base + reg);
पूर्ण

अटल व्योम dispc_vp_ग_लिखो(काष्ठा dispc_device *dispc, u32 hw_videoport,
			   u16 reg, u32 val)
अणु
	व्योम __iomem *base = dispc->base_vp[hw_videoport];

	ioग_लिखो32(val, base + reg);
पूर्ण

अटल u32 dispc_vp_पढ़ो(काष्ठा dispc_device *dispc, u32 hw_videoport, u16 reg)
अणु
	व्योम __iomem *base = dispc->base_vp[hw_videoport];

	वापस ioपढ़ो32(base + reg);
पूर्ण

/*
 * TRM gives bitfields as start:end, where start is the higher bit
 * number. For example 7:0
 */

अटल u32 FLD_MASK(u32 start, u32 end)
अणु
	वापस ((1 << (start - end + 1)) - 1) << end;
पूर्ण

अटल u32 FLD_VAL(u32 val, u32 start, u32 end)
अणु
	वापस (val << end) & FLD_MASK(start, end);
पूर्ण

अटल u32 FLD_GET(u32 val, u32 start, u32 end)
अणु
	वापस (val & FLD_MASK(start, end)) >> end;
पूर्ण

अटल u32 FLD_MOD(u32 orig, u32 val, u32 start, u32 end)
अणु
	वापस (orig & ~FLD_MASK(start, end)) | FLD_VAL(val, start, end);
पूर्ण

अटल u32 REG_GET(काष्ठा dispc_device *dispc, u32 idx, u32 start, u32 end)
अणु
	वापस FLD_GET(dispc_पढ़ो(dispc, idx), start, end);
पूर्ण

अटल व्योम REG_FLD_MOD(काष्ठा dispc_device *dispc, u32 idx, u32 val,
			u32 start, u32 end)
अणु
	dispc_ग_लिखो(dispc, idx, FLD_MOD(dispc_पढ़ो(dispc, idx), val,
					start, end));
पूर्ण

अटल u32 VID_REG_GET(काष्ठा dispc_device *dispc, u32 hw_plane, u32 idx,
		       u32 start, u32 end)
अणु
	वापस FLD_GET(dispc_vid_पढ़ो(dispc, hw_plane, idx), start, end);
पूर्ण

अटल व्योम VID_REG_FLD_MOD(काष्ठा dispc_device *dispc, u32 hw_plane, u32 idx,
			    u32 val, u32 start, u32 end)
अणु
	dispc_vid_ग_लिखो(dispc, hw_plane, idx,
			FLD_MOD(dispc_vid_पढ़ो(dispc, hw_plane, idx),
				val, start, end));
पूर्ण

अटल u32 VP_REG_GET(काष्ठा dispc_device *dispc, u32 vp, u32 idx,
		      u32 start, u32 end)
अणु
	वापस FLD_GET(dispc_vp_पढ़ो(dispc, vp, idx), start, end);
पूर्ण

अटल व्योम VP_REG_FLD_MOD(काष्ठा dispc_device *dispc, u32 vp, u32 idx, u32 val,
			   u32 start, u32 end)
अणु
	dispc_vp_ग_लिखो(dispc, vp, idx, FLD_MOD(dispc_vp_पढ़ो(dispc, vp, idx),
					       val, start, end));
पूर्ण

__maybe_unused
अटल u32 OVR_REG_GET(काष्ठा dispc_device *dispc, u32 ovr, u32 idx,
		       u32 start, u32 end)
अणु
	वापस FLD_GET(dispc_ovr_पढ़ो(dispc, ovr, idx), start, end);
पूर्ण

अटल व्योम OVR_REG_FLD_MOD(काष्ठा dispc_device *dispc, u32 ovr, u32 idx,
			    u32 val, u32 start, u32 end)
अणु
	dispc_ovr_ग_लिखो(dispc, ovr, idx,
			FLD_MOD(dispc_ovr_पढ़ो(dispc, ovr, idx),
				val, start, end));
पूर्ण

अटल dispc_irq_t dispc_vp_irq_from_raw(u32 stat, u32 hw_videoport)
अणु
	dispc_irq_t vp_stat = 0;

	अगर (stat & BIT(0))
		vp_stat |= DSS_IRQ_VP_FRAME_DONE(hw_videoport);
	अगर (stat & BIT(1))
		vp_stat |= DSS_IRQ_VP_VSYNC_EVEN(hw_videoport);
	अगर (stat & BIT(2))
		vp_stat |= DSS_IRQ_VP_VSYNC_ODD(hw_videoport);
	अगर (stat & BIT(4))
		vp_stat |= DSS_IRQ_VP_SYNC_LOST(hw_videoport);

	वापस vp_stat;
पूर्ण

अटल u32 dispc_vp_irq_to_raw(dispc_irq_t vpstat, u32 hw_videoport)
अणु
	u32 stat = 0;

	अगर (vpstat & DSS_IRQ_VP_FRAME_DONE(hw_videoport))
		stat |= BIT(0);
	अगर (vpstat & DSS_IRQ_VP_VSYNC_EVEN(hw_videoport))
		stat |= BIT(1);
	अगर (vpstat & DSS_IRQ_VP_VSYNC_ODD(hw_videoport))
		stat |= BIT(2);
	अगर (vpstat & DSS_IRQ_VP_SYNC_LOST(hw_videoport))
		stat |= BIT(4);

	वापस stat;
पूर्ण

अटल dispc_irq_t dispc_vid_irq_from_raw(u32 stat, u32 hw_plane)
अणु
	dispc_irq_t vid_stat = 0;

	अगर (stat & BIT(0))
		vid_stat |= DSS_IRQ_PLANE_FIFO_UNDERFLOW(hw_plane);

	वापस vid_stat;
पूर्ण

अटल u32 dispc_vid_irq_to_raw(dispc_irq_t vidstat, u32 hw_plane)
अणु
	u32 stat = 0;

	अगर (vidstat & DSS_IRQ_PLANE_FIFO_UNDERFLOW(hw_plane))
		stat |= BIT(0);

	वापस stat;
पूर्ण

अटल dispc_irq_t dispc_k2g_vp_पढ़ो_irqstatus(काष्ठा dispc_device *dispc,
					       u32 hw_videoport)
अणु
	u32 stat = dispc_vp_पढ़ो(dispc, hw_videoport, DISPC_VP_K2G_IRQSTATUS);

	वापस dispc_vp_irq_from_raw(stat, hw_videoport);
पूर्ण

अटल व्योम dispc_k2g_vp_ग_लिखो_irqstatus(काष्ठा dispc_device *dispc,
					 u32 hw_videoport, dispc_irq_t vpstat)
अणु
	u32 stat = dispc_vp_irq_to_raw(vpstat, hw_videoport);

	dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_K2G_IRQSTATUS, stat);
पूर्ण

अटल dispc_irq_t dispc_k2g_vid_पढ़ो_irqstatus(काष्ठा dispc_device *dispc,
						u32 hw_plane)
अणु
	u32 stat = dispc_vid_पढ़ो(dispc, hw_plane, DISPC_VID_K2G_IRQSTATUS);

	वापस dispc_vid_irq_from_raw(stat, hw_plane);
पूर्ण

अटल व्योम dispc_k2g_vid_ग_लिखो_irqstatus(काष्ठा dispc_device *dispc,
					  u32 hw_plane, dispc_irq_t vidstat)
अणु
	u32 stat = dispc_vid_irq_to_raw(vidstat, hw_plane);

	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_K2G_IRQSTATUS, stat);
पूर्ण

अटल dispc_irq_t dispc_k2g_vp_पढ़ो_irqenable(काष्ठा dispc_device *dispc,
					       u32 hw_videoport)
अणु
	u32 stat = dispc_vp_पढ़ो(dispc, hw_videoport, DISPC_VP_K2G_IRQENABLE);

	वापस dispc_vp_irq_from_raw(stat, hw_videoport);
पूर्ण

अटल व्योम dispc_k2g_vp_set_irqenable(काष्ठा dispc_device *dispc,
				       u32 hw_videoport, dispc_irq_t vpstat)
अणु
	u32 stat = dispc_vp_irq_to_raw(vpstat, hw_videoport);

	dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_K2G_IRQENABLE, stat);
पूर्ण

अटल dispc_irq_t dispc_k2g_vid_पढ़ो_irqenable(काष्ठा dispc_device *dispc,
						u32 hw_plane)
अणु
	u32 stat = dispc_vid_पढ़ो(dispc, hw_plane, DISPC_VID_K2G_IRQENABLE);

	वापस dispc_vid_irq_from_raw(stat, hw_plane);
पूर्ण

अटल व्योम dispc_k2g_vid_set_irqenable(काष्ठा dispc_device *dispc,
					u32 hw_plane, dispc_irq_t vidstat)
अणु
	u32 stat = dispc_vid_irq_to_raw(vidstat, hw_plane);

	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_K2G_IRQENABLE, stat);
पूर्ण

अटल व्योम dispc_k2g_clear_irqstatus(काष्ठा dispc_device *dispc,
				      dispc_irq_t mask)
अणु
	dispc_k2g_vp_ग_लिखो_irqstatus(dispc, 0, mask);
	dispc_k2g_vid_ग_लिखो_irqstatus(dispc, 0, mask);
पूर्ण

अटल
dispc_irq_t dispc_k2g_पढ़ो_and_clear_irqstatus(काष्ठा dispc_device *dispc)
अणु
	dispc_irq_t stat = 0;

	/* always clear the top level irqstatus */
	dispc_ग_लिखो(dispc, DISPC_IRQSTATUS,
		    dispc_पढ़ो(dispc, DISPC_IRQSTATUS));

	stat |= dispc_k2g_vp_पढ़ो_irqstatus(dispc, 0);
	stat |= dispc_k2g_vid_पढ़ो_irqstatus(dispc, 0);

	dispc_k2g_clear_irqstatus(dispc, stat);

	वापस stat;
पूर्ण

अटल dispc_irq_t dispc_k2g_पढ़ो_irqenable(काष्ठा dispc_device *dispc)
अणु
	dispc_irq_t stat = 0;

	stat |= dispc_k2g_vp_पढ़ो_irqenable(dispc, 0);
	stat |= dispc_k2g_vid_पढ़ो_irqenable(dispc, 0);

	वापस stat;
पूर्ण

अटल
व्योम dispc_k2g_set_irqenable(काष्ठा dispc_device *dispc, dispc_irq_t mask)
अणु
	dispc_irq_t old_mask = dispc_k2g_पढ़ो_irqenable(dispc);

	/* clear the irqstatus क्रम newly enabled irqs */
	dispc_k2g_clear_irqstatus(dispc, (mask ^ old_mask) & mask);

	dispc_k2g_vp_set_irqenable(dispc, 0, mask);
	dispc_k2g_vid_set_irqenable(dispc, 0, mask);

	dispc_ग_लिखो(dispc, DISPC_IRQENABLE_SET, (1 << 0) | (1 << 7));

	/* flush posted ग_लिखो */
	dispc_k2g_पढ़ो_irqenable(dispc);
पूर्ण

अटल dispc_irq_t dispc_k3_vp_पढ़ो_irqstatus(काष्ठा dispc_device *dispc,
					      u32 hw_videoport)
अणु
	u32 stat = dispc_पढ़ो(dispc, DISPC_VP_IRQSTATUS(hw_videoport));

	वापस dispc_vp_irq_from_raw(stat, hw_videoport);
पूर्ण

अटल व्योम dispc_k3_vp_ग_लिखो_irqstatus(काष्ठा dispc_device *dispc,
					u32 hw_videoport, dispc_irq_t vpstat)
अणु
	u32 stat = dispc_vp_irq_to_raw(vpstat, hw_videoport);

	dispc_ग_लिखो(dispc, DISPC_VP_IRQSTATUS(hw_videoport), stat);
पूर्ण

अटल dispc_irq_t dispc_k3_vid_पढ़ो_irqstatus(काष्ठा dispc_device *dispc,
					       u32 hw_plane)
अणु
	u32 stat = dispc_पढ़ो(dispc, DISPC_VID_IRQSTATUS(hw_plane));

	वापस dispc_vid_irq_from_raw(stat, hw_plane);
पूर्ण

अटल व्योम dispc_k3_vid_ग_लिखो_irqstatus(काष्ठा dispc_device *dispc,
					 u32 hw_plane, dispc_irq_t vidstat)
अणु
	u32 stat = dispc_vid_irq_to_raw(vidstat, hw_plane);

	dispc_ग_लिखो(dispc, DISPC_VID_IRQSTATUS(hw_plane), stat);
पूर्ण

अटल dispc_irq_t dispc_k3_vp_पढ़ो_irqenable(काष्ठा dispc_device *dispc,
					      u32 hw_videoport)
अणु
	u32 stat = dispc_पढ़ो(dispc, DISPC_VP_IRQENABLE(hw_videoport));

	वापस dispc_vp_irq_from_raw(stat, hw_videoport);
पूर्ण

अटल व्योम dispc_k3_vp_set_irqenable(काष्ठा dispc_device *dispc,
				      u32 hw_videoport, dispc_irq_t vpstat)
अणु
	u32 stat = dispc_vp_irq_to_raw(vpstat, hw_videoport);

	dispc_ग_लिखो(dispc, DISPC_VP_IRQENABLE(hw_videoport), stat);
पूर्ण

अटल dispc_irq_t dispc_k3_vid_पढ़ो_irqenable(काष्ठा dispc_device *dispc,
					       u32 hw_plane)
अणु
	u32 stat = dispc_पढ़ो(dispc, DISPC_VID_IRQENABLE(hw_plane));

	वापस dispc_vid_irq_from_raw(stat, hw_plane);
पूर्ण

अटल व्योम dispc_k3_vid_set_irqenable(काष्ठा dispc_device *dispc,
				       u32 hw_plane, dispc_irq_t vidstat)
अणु
	u32 stat = dispc_vid_irq_to_raw(vidstat, hw_plane);

	dispc_ग_लिखो(dispc, DISPC_VID_IRQENABLE(hw_plane), stat);
पूर्ण

अटल
व्योम dispc_k3_clear_irqstatus(काष्ठा dispc_device *dispc, dispc_irq_t clearmask)
अणु
	अचिन्हित पूर्णांक i;
	u32 top_clear = 0;

	क्रम (i = 0; i < dispc->feat->num_vps; ++i) अणु
		अगर (clearmask & DSS_IRQ_VP_MASK(i)) अणु
			dispc_k3_vp_ग_लिखो_irqstatus(dispc, i, clearmask);
			top_clear |= BIT(i);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < dispc->feat->num_planes; ++i) अणु
		अगर (clearmask & DSS_IRQ_PLANE_MASK(i)) अणु
			dispc_k3_vid_ग_लिखो_irqstatus(dispc, i, clearmask);
			top_clear |= BIT(4 + i);
		पूर्ण
	पूर्ण
	अगर (dispc->feat->subrev == DISPC_K2G)
		वापस;

	dispc_ग_लिखो(dispc, DISPC_IRQSTATUS, top_clear);

	/* Flush posted ग_लिखोs */
	dispc_पढ़ो(dispc, DISPC_IRQSTATUS);
पूर्ण

अटल
dispc_irq_t dispc_k3_पढ़ो_and_clear_irqstatus(काष्ठा dispc_device *dispc)
अणु
	dispc_irq_t status = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dispc->feat->num_vps; ++i)
		status |= dispc_k3_vp_पढ़ो_irqstatus(dispc, i);

	क्रम (i = 0; i < dispc->feat->num_planes; ++i)
		status |= dispc_k3_vid_पढ़ो_irqstatus(dispc, i);

	dispc_k3_clear_irqstatus(dispc, status);

	वापस status;
पूर्ण

अटल dispc_irq_t dispc_k3_पढ़ो_irqenable(काष्ठा dispc_device *dispc)
अणु
	dispc_irq_t enable = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dispc->feat->num_vps; ++i)
		enable |= dispc_k3_vp_पढ़ो_irqenable(dispc, i);

	क्रम (i = 0; i < dispc->feat->num_planes; ++i)
		enable |= dispc_k3_vid_पढ़ो_irqenable(dispc, i);

	वापस enable;
पूर्ण

अटल व्योम dispc_k3_set_irqenable(काष्ठा dispc_device *dispc,
				   dispc_irq_t mask)
अणु
	अचिन्हित पूर्णांक i;
	u32 मुख्य_enable = 0, मुख्य_disable = 0;
	dispc_irq_t old_mask;

	old_mask = dispc_k3_पढ़ो_irqenable(dispc);

	/* clear the irqstatus क्रम newly enabled irqs */
	dispc_k3_clear_irqstatus(dispc, (old_mask ^ mask) & mask);

	क्रम (i = 0; i < dispc->feat->num_vps; ++i) अणु
		dispc_k3_vp_set_irqenable(dispc, i, mask);
		अगर (mask & DSS_IRQ_VP_MASK(i))
			मुख्य_enable |= BIT(i);		/* VP IRQ */
		अन्यथा
			मुख्य_disable |= BIT(i);		/* VP IRQ */
	पूर्ण

	क्रम (i = 0; i < dispc->feat->num_planes; ++i) अणु
		dispc_k3_vid_set_irqenable(dispc, i, mask);
		अगर (mask & DSS_IRQ_PLANE_MASK(i))
			मुख्य_enable |= BIT(i + 4);	/* VID IRQ */
		अन्यथा
			मुख्य_disable |= BIT(i + 4);	/* VID IRQ */
	पूर्ण

	अगर (मुख्य_enable)
		dispc_ग_लिखो(dispc, DISPC_IRQENABLE_SET, मुख्य_enable);

	अगर (मुख्य_disable)
		dispc_ग_लिखो(dispc, DISPC_IRQENABLE_CLR, मुख्य_disable);

	/* Flush posted ग_लिखोs */
	dispc_पढ़ो(dispc, DISPC_IRQENABLE_SET);
पूर्ण

dispc_irq_t dispc_पढ़ो_and_clear_irqstatus(काष्ठा dispc_device *dispc)
अणु
	चयन (dispc->feat->subrev) अणु
	हाल DISPC_K2G:
		वापस dispc_k2g_पढ़ो_and_clear_irqstatus(dispc);
	हाल DISPC_AM65X:
	हाल DISPC_J721E:
		वापस dispc_k3_पढ़ो_and_clear_irqstatus(dispc);
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

व्योम dispc_set_irqenable(काष्ठा dispc_device *dispc, dispc_irq_t mask)
अणु
	चयन (dispc->feat->subrev) अणु
	हाल DISPC_K2G:
		dispc_k2g_set_irqenable(dispc, mask);
		अवरोध;
	हाल DISPC_AM65X:
	हाल DISPC_J721E:
		dispc_k3_set_irqenable(dispc, mask);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

क्रमागत dispc_oldi_mode_reg_val अणु SPWG_18 = 0, JEIDA_24 = 1, SPWG_24 = 2 पूर्ण;

काष्ठा dispc_bus_क्रमmat अणु
	u32 bus_fmt;
	u32 data_width;
	bool is_oldi_fmt;
	क्रमागत dispc_oldi_mode_reg_val oldi_mode_reg_val;
पूर्ण;

अटल स्थिर काष्ठा dispc_bus_क्रमmat dispc_bus_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_RGB444_1X12,		12, false, 0 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB565_1X16,		16, false, 0 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB666_1X18,		18, false, 0 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB888_1X24,		24, false, 0 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB101010_1X30,		30, false, 0 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB121212_1X36,		36, false, 0 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,	18, true, SPWG_18 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,	24, true, SPWG_24 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA,	24, true, JEIDA_24 पूर्ण,
पूर्ण;

अटल स्थिर
काष्ठा dispc_bus_क्रमmat *dispc_vp_find_bus_fmt(काष्ठा dispc_device *dispc,
					       u32 hw_videoport,
					       u32 bus_fmt, u32 bus_flags)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dispc_bus_क्रमmats); ++i) अणु
		अगर (dispc_bus_क्रमmats[i].bus_fmt == bus_fmt)
			वापस &dispc_bus_क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक dispc_vp_bus_check(काष्ठा dispc_device *dispc, u32 hw_videoport,
		       स्थिर काष्ठा drm_crtc_state *state)
अणु
	स्थिर काष्ठा tidss_crtc_state *tstate = to_tidss_crtc_state(state);
	स्थिर काष्ठा dispc_bus_क्रमmat *fmt;

	fmt = dispc_vp_find_bus_fmt(dispc, hw_videoport, tstate->bus_क्रमmat,
				    tstate->bus_flags);
	अगर (!fmt) अणु
		dev_dbg(dispc->dev, "%s: Unsupported bus format: %u\n",
			__func__, tstate->bus_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (dispc->feat->vp_bus_type[hw_videoport] != DISPC_VP_OLDI &&
	    fmt->is_oldi_fmt) अणु
		dev_dbg(dispc->dev, "%s: %s is not OLDI-port\n",
			__func__, dispc->feat->vp_name[hw_videoport]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dispc_oldi_tx_घातer(काष्ठा dispc_device *dispc, bool घातer)
अणु
	u32 val = घातer ? 0 : OLDI_PWRDN_TX;

	अगर (WARN_ON(!dispc->oldi_io_ctrl))
		वापस;

	regmap_update_bits(dispc->oldi_io_ctrl, OLDI_DAT0_IO_CTRL,
			   OLDI_PWRDN_TX, val);
	regmap_update_bits(dispc->oldi_io_ctrl, OLDI_DAT1_IO_CTRL,
			   OLDI_PWRDN_TX, val);
	regmap_update_bits(dispc->oldi_io_ctrl, OLDI_DAT2_IO_CTRL,
			   OLDI_PWRDN_TX, val);
	regmap_update_bits(dispc->oldi_io_ctrl, OLDI_DAT3_IO_CTRL,
			   OLDI_PWRDN_TX, val);
	regmap_update_bits(dispc->oldi_io_ctrl, OLDI_CLK_IO_CTRL,
			   OLDI_PWRDN_TX, val);
पूर्ण

अटल व्योम dispc_set_num_datalines(काष्ठा dispc_device *dispc,
				    u32 hw_videoport, पूर्णांक num_lines)
अणु
	पूर्णांक v;

	चयन (num_lines) अणु
	हाल 12:
		v = 0; अवरोध;
	हाल 16:
		v = 1; अवरोध;
	हाल 18:
		v = 2; अवरोध;
	हाल 24:
		v = 3; अवरोध;
	हाल 30:
		v = 4; अवरोध;
	हाल 36:
		v = 5; अवरोध;
	शेष:
		WARN_ON(1);
		v = 3;
	पूर्ण

	VP_REG_FLD_MOD(dispc, hw_videoport, DISPC_VP_CONTROL, v, 10, 8);
पूर्ण

अटल व्योम dispc_enable_oldi(काष्ठा dispc_device *dispc, u32 hw_videoport,
			      स्थिर काष्ठा dispc_bus_क्रमmat *fmt)
अणु
	u32 oldi_cfg = 0;
	u32 oldi_reset_bit = BIT(5 + hw_videoport);
	पूर्णांक count = 0;

	/*
	 * For the moment DUALMODESYNC, MASTERSLAVE, MODE, and SRC
	 * bits of DISPC_VP_DSS_OLDI_CFG are set अटलally to 0.
	 */

	अगर (fmt->data_width == 24)
		oldi_cfg |= BIT(8); /* MSB */
	अन्यथा अगर (fmt->data_width != 18)
		dev_warn(dispc->dev, "%s: %d port width not supported\n",
			 __func__, fmt->data_width);

	oldi_cfg |= BIT(7); /* DEPOL */

	oldi_cfg = FLD_MOD(oldi_cfg, fmt->oldi_mode_reg_val, 3, 1);

	oldi_cfg |= BIT(12); /* SOFTRST */

	oldi_cfg |= BIT(0); /* ENABLE */

	dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_DSS_OLDI_CFG, oldi_cfg);

	जबतक (!(oldi_reset_bit & dispc_पढ़ो(dispc, DSS_SYSSTATUS)) &&
	       count < 10000)
		count++;

	अगर (!(oldi_reset_bit & dispc_पढ़ो(dispc, DSS_SYSSTATUS)))
		dev_warn(dispc->dev, "%s: timeout waiting OLDI reset done\n",
			 __func__);
पूर्ण

व्योम dispc_vp_prepare(काष्ठा dispc_device *dispc, u32 hw_videoport,
		      स्थिर काष्ठा drm_crtc_state *state)
अणु
	स्थिर काष्ठा tidss_crtc_state *tstate = to_tidss_crtc_state(state);
	स्थिर काष्ठा dispc_bus_क्रमmat *fmt;

	fmt = dispc_vp_find_bus_fmt(dispc, hw_videoport, tstate->bus_क्रमmat,
				    tstate->bus_flags);

	अगर (WARN_ON(!fmt))
		वापस;

	अगर (dispc->feat->vp_bus_type[hw_videoport] == DISPC_VP_OLDI) अणु
		dispc_oldi_tx_घातer(dispc, true);

		dispc_enable_oldi(dispc, hw_videoport, fmt);
	पूर्ण
पूर्ण

व्योम dispc_vp_enable(काष्ठा dispc_device *dispc, u32 hw_videoport,
		     स्थिर काष्ठा drm_crtc_state *state)
अणु
	स्थिर काष्ठा drm_display_mode *mode = &state->adjusted_mode;
	स्थिर काष्ठा tidss_crtc_state *tstate = to_tidss_crtc_state(state);
	bool align, onoff, rf, ieo, ipc, ihs, ivs;
	स्थिर काष्ठा dispc_bus_क्रमmat *fmt;
	u32 hsw, hfp, hbp, vsw, vfp, vbp;

	fmt = dispc_vp_find_bus_fmt(dispc, hw_videoport, tstate->bus_क्रमmat,
				    tstate->bus_flags);

	अगर (WARN_ON(!fmt))
		वापस;

	dispc_set_num_datalines(dispc, hw_videoport, fmt->data_width);

	hfp = mode->hsync_start - mode->hdisplay;
	hsw = mode->hsync_end - mode->hsync_start;
	hbp = mode->htotal - mode->hsync_end;

	vfp = mode->vsync_start - mode->vdisplay;
	vsw = mode->vsync_end - mode->vsync_start;
	vbp = mode->vtotal - mode->vsync_end;

	dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_TIMING_H,
		       FLD_VAL(hsw - 1, 7, 0) |
		       FLD_VAL(hfp - 1, 19, 8) |
		       FLD_VAL(hbp - 1, 31, 20));

	dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_TIMING_V,
		       FLD_VAL(vsw - 1, 7, 0) |
		       FLD_VAL(vfp, 19, 8) |
		       FLD_VAL(vbp, 31, 20));

	ivs = !!(mode->flags & DRM_MODE_FLAG_NVSYNC);

	ihs = !!(mode->flags & DRM_MODE_FLAG_NHSYNC);

	ieo = !!(tstate->bus_flags & DRM_BUS_FLAG_DE_LOW);

	ipc = !!(tstate->bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE);

	/* always use the 'rf' setting */
	onoff = true;

	rf = !!(tstate->bus_flags & DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE);

	/* always use aligned syncs */
	align = true;

	/* always use DE_HIGH क्रम OLDI */
	अगर (dispc->feat->vp_bus_type[hw_videoport] == DISPC_VP_OLDI)
		ieo = false;

	dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_POL_FREQ,
		       FLD_VAL(align, 18, 18) |
		       FLD_VAL(onoff, 17, 17) |
		       FLD_VAL(rf, 16, 16) |
		       FLD_VAL(ieo, 15, 15) |
		       FLD_VAL(ipc, 14, 14) |
		       FLD_VAL(ihs, 13, 13) |
		       FLD_VAL(ivs, 12, 12));

	dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_SIZE_SCREEN,
		       FLD_VAL(mode->hdisplay - 1, 11, 0) |
		       FLD_VAL(mode->vdisplay - 1, 27, 16));

	VP_REG_FLD_MOD(dispc, hw_videoport, DISPC_VP_CONTROL, 1, 0, 0);
पूर्ण

व्योम dispc_vp_disable(काष्ठा dispc_device *dispc, u32 hw_videoport)
अणु
	VP_REG_FLD_MOD(dispc, hw_videoport, DISPC_VP_CONTROL, 0, 0, 0);
पूर्ण

व्योम dispc_vp_unprepare(काष्ठा dispc_device *dispc, u32 hw_videoport)
अणु
	अगर (dispc->feat->vp_bus_type[hw_videoport] == DISPC_VP_OLDI) अणु
		dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_DSS_OLDI_CFG, 0);

		dispc_oldi_tx_घातer(dispc, false);
	पूर्ण
पूर्ण

bool dispc_vp_go_busy(काष्ठा dispc_device *dispc, u32 hw_videoport)
अणु
	वापस VP_REG_GET(dispc, hw_videoport, DISPC_VP_CONTROL, 5, 5);
पूर्ण

व्योम dispc_vp_go(काष्ठा dispc_device *dispc, u32 hw_videoport)
अणु
	WARN_ON(VP_REG_GET(dispc, hw_videoport, DISPC_VP_CONTROL, 5, 5));
	VP_REG_FLD_MOD(dispc, hw_videoport, DISPC_VP_CONTROL, 1, 5, 5);
पूर्ण

क्रमागत c8_to_c12_mode अणु C8_TO_C12_REPLICATE, C8_TO_C12_MAX, C8_TO_C12_MIN पूर्ण;

अटल u16 c8_to_c12(u8 c8, क्रमागत c8_to_c12_mode mode)
अणु
	u16 c12;

	c12 = c8 << 4;

	चयन (mode) अणु
	हाल C8_TO_C12_REPLICATE:
		/* Copy c8 4 MSB to 4 LSB क्रम full scale c12 */
		c12 |= c8 >> 4;
		अवरोध;
	हाल C8_TO_C12_MAX:
		c12 |= 0xF;
		अवरोध;
	शेष:
	हाल C8_TO_C12_MIN:
		अवरोध;
	पूर्ण

	वापस c12;
पूर्ण

अटल u64 argb8888_to_argb12121212(u32 argb8888, क्रमागत c8_to_c12_mode m)
अणु
	u8 a, r, g, b;
	u64 v;

	a = (argb8888 >> 24) & 0xff;
	r = (argb8888 >> 16) & 0xff;
	g = (argb8888 >> 8) & 0xff;
	b = (argb8888 >> 0) & 0xff;

	v = ((u64)c8_to_c12(a, m) << 36) | ((u64)c8_to_c12(r, m) << 24) |
		((u64)c8_to_c12(g, m) << 12) | (u64)c8_to_c12(b, m);

	वापस v;
पूर्ण

अटल व्योम dispc_vp_set_शेष_color(काष्ठा dispc_device *dispc,
				       u32 hw_videoport, u32 शेष_color)
अणु
	u64 v;

	v = argb8888_to_argb12121212(शेष_color, C8_TO_C12_REPLICATE);

	dispc_ovr_ग_लिखो(dispc, hw_videoport,
			DISPC_OVR_DEFAULT_COLOR, v & 0xffffffff);
	dispc_ovr_ग_लिखो(dispc, hw_videoport,
			DISPC_OVR_DEFAULT_COLOR2, (v >> 32) & 0xffff);
पूर्ण

क्रमागत drm_mode_status dispc_vp_mode_valid(काष्ठा dispc_device *dispc,
					 u32 hw_videoport,
					 स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 hsw, hfp, hbp, vsw, vfp, vbp;
	क्रमागत dispc_vp_bus_type bus_type;
	पूर्णांक max_pclk;

	bus_type = dispc->feat->vp_bus_type[hw_videoport];

	max_pclk = dispc->feat->max_pclk_khz[bus_type];

	अगर (WARN_ON(max_pclk == 0))
		वापस MODE_BAD;

	अगर (mode->घड़ी < dispc->feat->min_pclk_khz)
		वापस MODE_CLOCK_LOW;

	अगर (mode->घड़ी > max_pclk)
		वापस MODE_CLOCK_HIGH;

	अगर (mode->hdisplay > 4096)
		वापस MODE_BAD;

	अगर (mode->vdisplay > 4096)
		वापस MODE_BAD;

	/* TODO: add पूर्णांकerlace support */
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस MODE_NO_INTERLACE;

	/*
	 * Enक्रमce the output width is भागisible by 2. Actually this
	 * is only needed in following हालs:
	 * - YUV output selected (BT656, BT1120)
	 * - Dithering enabled
	 * - TDM with TDMCycleFormat == 3
	 * But क्रम simplicity we enक्रमce that always.
	 */
	अगर ((mode->hdisplay % 2) != 0)
		वापस MODE_BAD_HVALUE;

	hfp = mode->hsync_start - mode->hdisplay;
	hsw = mode->hsync_end - mode->hsync_start;
	hbp = mode->htotal - mode->hsync_end;

	vfp = mode->vsync_start - mode->vdisplay;
	vsw = mode->vsync_end - mode->vsync_start;
	vbp = mode->vtotal - mode->vsync_end;

	अगर (hsw < 1 || hsw > 256 ||
	    hfp < 1 || hfp > 4096 ||
	    hbp < 1 || hbp > 4096)
		वापस MODE_BAD_HVALUE;

	अगर (vsw < 1 || vsw > 256 ||
	    vfp > 4095 || vbp > 4095)
		वापस MODE_BAD_VVALUE;

	अगर (dispc->memory_bandwidth_limit) अणु
		स्थिर अचिन्हित पूर्णांक bpp = 4;
		u64 bandwidth;

		bandwidth = 1000 * mode->घड़ी;
		bandwidth = bandwidth * mode->hdisplay * mode->vdisplay * bpp;
		bandwidth = भाग_u64(bandwidth, mode->htotal * mode->vtotal);

		अगर (dispc->memory_bandwidth_limit < bandwidth)
			वापस MODE_BAD;
	पूर्ण

	वापस MODE_OK;
पूर्ण

पूर्णांक dispc_vp_enable_clk(काष्ठा dispc_device *dispc, u32 hw_videoport)
अणु
	पूर्णांक ret = clk_prepare_enable(dispc->vp_clk[hw_videoport]);

	अगर (ret)
		dev_err(dispc->dev, "%s: enabling clk failed: %d\n", __func__,
			ret);

	वापस ret;
पूर्ण

व्योम dispc_vp_disable_clk(काष्ठा dispc_device *dispc, u32 hw_videoport)
अणु
	clk_disable_unprepare(dispc->vp_clk[hw_videoport]);
पूर्ण

/*
 * Calculate the percentage dअगरference between the requested pixel घड़ी rate
 * and the effective rate resulting from calculating the घड़ी भागider value.
 */
अटल
अचिन्हित पूर्णांक dispc_pclk_dअगरf(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ real_rate)
अणु
	पूर्णांक r = rate / 100, rr = real_rate / 100;

	वापस (अचिन्हित पूर्णांक)(असल(((rr - r) * 100) / r));
पूर्ण

पूर्णांक dispc_vp_set_clk_rate(काष्ठा dispc_device *dispc, u32 hw_videoport,
			  अचिन्हित दीर्घ rate)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ new_rate;

	r = clk_set_rate(dispc->vp_clk[hw_videoport], rate);
	अगर (r) अणु
		dev_err(dispc->dev, "vp%d: failed to set clk rate to %lu\n",
			hw_videoport, rate);
		वापस r;
	पूर्ण

	new_rate = clk_get_rate(dispc->vp_clk[hw_videoport]);

	अगर (dispc_pclk_dअगरf(rate, new_rate) > 5)
		dev_warn(dispc->dev,
			 "vp%d: Clock rate %lu differs over 5%% from requested %lu\n",
			 hw_videoport, new_rate, rate);

	dev_dbg(dispc->dev, "vp%d: new rate %lu Hz (requested %lu Hz)\n",
		hw_videoport, clk_get_rate(dispc->vp_clk[hw_videoport]), rate);

	वापस 0;
पूर्ण

/* OVR */
अटल व्योम dispc_k2g_ovr_set_plane(काष्ठा dispc_device *dispc,
				    u32 hw_plane, u32 hw_videoport,
				    u32 x, u32 y, u32 layer)
अणु
	/* On k2g there is only one plane and no need क्रम ovr */
	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_K2G_POSITION,
			x | (y << 16));
पूर्ण

अटल व्योम dispc_am65x_ovr_set_plane(काष्ठा dispc_device *dispc,
				      u32 hw_plane, u32 hw_videoport,
				      u32 x, u32 y, u32 layer)
अणु
	OVR_REG_FLD_MOD(dispc, hw_videoport, DISPC_OVR_ATTRIBUTES(layer),
			hw_plane, 4, 1);
	OVR_REG_FLD_MOD(dispc, hw_videoport, DISPC_OVR_ATTRIBUTES(layer),
			x, 17, 6);
	OVR_REG_FLD_MOD(dispc, hw_videoport, DISPC_OVR_ATTRIBUTES(layer),
			y, 30, 19);
पूर्ण

अटल व्योम dispc_j721e_ovr_set_plane(काष्ठा dispc_device *dispc,
				      u32 hw_plane, u32 hw_videoport,
				      u32 x, u32 y, u32 layer)
अणु
	OVR_REG_FLD_MOD(dispc, hw_videoport, DISPC_OVR_ATTRIBUTES(layer),
			hw_plane, 4, 1);
	OVR_REG_FLD_MOD(dispc, hw_videoport, DISPC_OVR_ATTRIBUTES2(layer),
			x, 13, 0);
	OVR_REG_FLD_MOD(dispc, hw_videoport, DISPC_OVR_ATTRIBUTES2(layer),
			y, 29, 16);
पूर्ण

व्योम dispc_ovr_set_plane(काष्ठा dispc_device *dispc, u32 hw_plane,
			 u32 hw_videoport, u32 x, u32 y, u32 layer)
अणु
	चयन (dispc->feat->subrev) अणु
	हाल DISPC_K2G:
		dispc_k2g_ovr_set_plane(dispc, hw_plane, hw_videoport,
					x, y, layer);
		अवरोध;
	हाल DISPC_AM65X:
		dispc_am65x_ovr_set_plane(dispc, hw_plane, hw_videoport,
					  x, y, layer);
		अवरोध;
	हाल DISPC_J721E:
		dispc_j721e_ovr_set_plane(dispc, hw_plane, hw_videoport,
					  x, y, layer);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

व्योम dispc_ovr_enable_layer(काष्ठा dispc_device *dispc,
			    u32 hw_videoport, u32 layer, bool enable)
अणु
	अगर (dispc->feat->subrev == DISPC_K2G)
		वापस;

	OVR_REG_FLD_MOD(dispc, hw_videoport, DISPC_OVR_ATTRIBUTES(layer),
			!!enable, 0, 0);
पूर्ण

/* CSC */
क्रमागत csc_cपंचांग अणु
	CSC_RR, CSC_RG, CSC_RB,
	CSC_GR, CSC_GG, CSC_GB,
	CSC_BR, CSC_BG, CSC_BB,
पूर्ण;

क्रमागत csc_yuv2rgb अणु
	CSC_RY, CSC_RCB, CSC_RCR,
	CSC_GY, CSC_GCB, CSC_GCR,
	CSC_BY, CSC_BCB, CSC_BCR,
पूर्ण;

क्रमागत csc_rgb2yuv अणु
	CSC_YR,  CSC_YG,  CSC_YB,
	CSC_CBR, CSC_CBG, CSC_CBB,
	CSC_CRR, CSC_CRG, CSC_CRB,
पूर्ण;

काष्ठा dispc_csc_coef अणु
	व्योम (*to_regval)(स्थिर काष्ठा dispc_csc_coef *csc, u32 *regval);
	पूर्णांक m[9];
	पूर्णांक preoffset[3];
	पूर्णांक postoffset[3];
	क्रमागत अणु CLIP_LIMITED_RANGE = 0, CLIP_FULL_RANGE = 1, पूर्ण cliping;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा DISPC_CSC_REGVAL_LEN 8

अटल
व्योम dispc_csc_offset_regval(स्थिर काष्ठा dispc_csc_coef *csc, u32 *regval)
अणु
#घोषणा OVAL(x, y) (FLD_VAL(x, 15, 3) | FLD_VAL(y, 31, 19))
	regval[5] = OVAL(csc->preoffset[0], csc->preoffset[1]);
	regval[6] = OVAL(csc->preoffset[2], csc->postoffset[0]);
	regval[7] = OVAL(csc->postoffset[1], csc->postoffset[2]);
#अघोषित OVAL
पूर्ण

#घोषणा CVAL(x, y) (FLD_VAL(x, 10, 0) | FLD_VAL(y, 26, 16))
अटल
व्योम dispc_csc_yuv2rgb_regval(स्थिर काष्ठा dispc_csc_coef *csc, u32 *regval)
अणु
	regval[0] = CVAL(csc->m[CSC_RY], csc->m[CSC_RCR]);
	regval[1] = CVAL(csc->m[CSC_RCB], csc->m[CSC_GY]);
	regval[2] = CVAL(csc->m[CSC_GCR], csc->m[CSC_GCB]);
	regval[3] = CVAL(csc->m[CSC_BY], csc->m[CSC_BCR]);
	regval[4] = CVAL(csc->m[CSC_BCB], 0);

	dispc_csc_offset_regval(csc, regval);
पूर्ण

__maybe_unused अटल
व्योम dispc_csc_rgb2yuv_regval(स्थिर काष्ठा dispc_csc_coef *csc, u32 *regval)
अणु
	regval[0] = CVAL(csc->m[CSC_YR], csc->m[CSC_YG]);
	regval[1] = CVAL(csc->m[CSC_YB], csc->m[CSC_CRR]);
	regval[2] = CVAL(csc->m[CSC_CRG], csc->m[CSC_CRB]);
	regval[3] = CVAL(csc->m[CSC_CBR], csc->m[CSC_CBG]);
	regval[4] = CVAL(csc->m[CSC_CBB], 0);

	dispc_csc_offset_regval(csc, regval);
पूर्ण

अटल व्योम dispc_csc_cpr_regval(स्थिर काष्ठा dispc_csc_coef *csc,
				 u32 *regval)
अणु
	regval[0] = CVAL(csc->m[CSC_RR], csc->m[CSC_RG]);
	regval[1] = CVAL(csc->m[CSC_RB], csc->m[CSC_GR]);
	regval[2] = CVAL(csc->m[CSC_GG], csc->m[CSC_GB]);
	regval[3] = CVAL(csc->m[CSC_BR], csc->m[CSC_BG]);
	regval[4] = CVAL(csc->m[CSC_BB], 0);

	dispc_csc_offset_regval(csc, regval);
पूर्ण

#अघोषित CVAL

अटल व्योम dispc_k2g_vid_ग_लिखो_csc(काष्ठा dispc_device *dispc, u32 hw_plane,
				    स्थिर काष्ठा dispc_csc_coef *csc)
अणु
	अटल स्थिर u16 dispc_vid_csc_coef_reg[] = अणु
		DISPC_VID_CSC_COEF(0), DISPC_VID_CSC_COEF(1),
		DISPC_VID_CSC_COEF(2), DISPC_VID_CSC_COEF(3),
		DISPC_VID_CSC_COEF(4), DISPC_VID_CSC_COEF(5),
		DISPC_VID_CSC_COEF(6), /* K2G has no post offset support */
	पूर्ण;
	u32 regval[DISPC_CSC_REGVAL_LEN];
	अचिन्हित पूर्णांक i;

	csc->to_regval(csc, regval);

	अगर (regval[7] != 0)
		dev_warn(dispc->dev, "%s: No post offset support for %s\n",
			 __func__, csc->name);

	क्रम (i = 0; i < ARRAY_SIZE(dispc_vid_csc_coef_reg); i++)
		dispc_vid_ग_लिखो(dispc, hw_plane, dispc_vid_csc_coef_reg[i],
				regval[i]);
पूर्ण

अटल व्योम dispc_k3_vid_ग_लिखो_csc(काष्ठा dispc_device *dispc, u32 hw_plane,
				   स्थिर काष्ठा dispc_csc_coef *csc)
अणु
	अटल स्थिर u16 dispc_vid_csc_coef_reg[DISPC_CSC_REGVAL_LEN] = अणु
		DISPC_VID_CSC_COEF(0), DISPC_VID_CSC_COEF(1),
		DISPC_VID_CSC_COEF(2), DISPC_VID_CSC_COEF(3),
		DISPC_VID_CSC_COEF(4), DISPC_VID_CSC_COEF(5),
		DISPC_VID_CSC_COEF(6), DISPC_VID_CSC_COEF7,
	पूर्ण;
	u32 regval[DISPC_CSC_REGVAL_LEN];
	अचिन्हित पूर्णांक i;

	csc->to_regval(csc, regval);

	क्रम (i = 0; i < ARRAY_SIZE(dispc_vid_csc_coef_reg); i++)
		dispc_vid_ग_लिखो(dispc, hw_plane, dispc_vid_csc_coef_reg[i],
				regval[i]);
पूर्ण

/* YUV -> RGB, ITU-R BT.601, full range */
अटल स्थिर काष्ठा dispc_csc_coef csc_yuv2rgb_bt601_full = अणु
	dispc_csc_yuv2rgb_regval,
	अणु 256,   0,  358,	/* ry, rcb, rcr |1.000  0.000  1.402|*/
	  256, -88, -182,	/* gy, gcb, gcr |1.000 -0.344 -0.714|*/
	  256, 452,    0, पूर्ण,	/* by, bcb, bcr |1.000  1.772  0.000|*/
	अणु    0, -2048, -2048, पूर्ण,	/* full range */
	अणु    0,     0,     0, पूर्ण,
	CLIP_FULL_RANGE,
	"BT.601 Full",
पूर्ण;

/* YUV -> RGB, ITU-R BT.601, limited range */
अटल स्थिर काष्ठा dispc_csc_coef csc_yuv2rgb_bt601_lim = अणु
	dispc_csc_yuv2rgb_regval,
	अणु 298,    0,  409,	/* ry, rcb, rcr |1.164  0.000  1.596|*/
	  298, -100, -208,	/* gy, gcb, gcr |1.164 -0.392 -0.813|*/
	  298,  516,    0, पूर्ण,	/* by, bcb, bcr |1.164  2.017  0.000|*/
	अणु -256, -2048, -2048, पूर्ण,	/* limited range */
	अणु    0,     0,     0, पूर्ण,
	CLIP_FULL_RANGE,
	"BT.601 Limited",
पूर्ण;

/* YUV -> RGB, ITU-R BT.709, full range */
अटल स्थिर काष्ठा dispc_csc_coef csc_yuv2rgb_bt709_full = अणु
	dispc_csc_yuv2rgb_regval,
	अणु 256,	  0,  402,	/* ry, rcb, rcr |1.000	0.000  1.570|*/
	  256,  -48, -120,	/* gy, gcb, gcr |1.000 -0.187 -0.467|*/
	  256,  475,    0, पूर्ण,	/* by, bcb, bcr |1.000	1.856  0.000|*/
	अणु    0, -2048, -2048, पूर्ण,	/* full range */
	अणु    0,     0,     0, पूर्ण,
	CLIP_FULL_RANGE,
	"BT.709 Full",
पूर्ण;

/* YUV -> RGB, ITU-R BT.709, limited range */
अटल स्थिर काष्ठा dispc_csc_coef csc_yuv2rgb_bt709_lim = अणु
	dispc_csc_yuv2rgb_regval,
	अणु 298,    0,  459,	/* ry, rcb, rcr |1.164  0.000  1.793|*/
	  298,  -55, -136,	/* gy, gcb, gcr |1.164 -0.213 -0.533|*/
	  298,  541,    0, पूर्ण,	/* by, bcb, bcr |1.164  2.112  0.000|*/
	अणु -256, -2048, -2048, पूर्ण,	/* limited range */
	अणु    0,     0,     0, पूर्ण,
	CLIP_FULL_RANGE,
	"BT.709 Limited",
पूर्ण;

अटल स्थिर काष्ठा अणु
	क्रमागत drm_color_encoding encoding;
	क्रमागत drm_color_range range;
	स्थिर काष्ठा dispc_csc_coef *csc;
पूर्ण dispc_csc_table[] = अणु
	अणु DRM_COLOR_YCBCR_BT601, DRM_COLOR_YCBCR_FULL_RANGE,
	  &csc_yuv2rgb_bt601_full, पूर्ण,
	अणु DRM_COLOR_YCBCR_BT601, DRM_COLOR_YCBCR_LIMITED_RANGE,
	  &csc_yuv2rgb_bt601_lim, पूर्ण,
	अणु DRM_COLOR_YCBCR_BT709, DRM_COLOR_YCBCR_FULL_RANGE,
	  &csc_yuv2rgb_bt709_full, पूर्ण,
	अणु DRM_COLOR_YCBCR_BT709, DRM_COLOR_YCBCR_LIMITED_RANGE,
	  &csc_yuv2rgb_bt709_lim, पूर्ण,
पूर्ण;

अटल स्थिर
काष्ठा dispc_csc_coef *dispc_find_csc(क्रमागत drm_color_encoding encoding,
				      क्रमागत drm_color_range range)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dispc_csc_table); i++) अणु
		अगर (dispc_csc_table[i].encoding == encoding &&
		    dispc_csc_table[i].range == range) अणु
			वापस dispc_csc_table[i].csc;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम dispc_vid_csc_setup(काष्ठा dispc_device *dispc, u32 hw_plane,
				स्थिर काष्ठा drm_plane_state *state)
अणु
	स्थिर काष्ठा dispc_csc_coef *coef;

	coef = dispc_find_csc(state->color_encoding, state->color_range);
	अगर (!coef) अणु
		dev_err(dispc->dev, "%s: CSC (%u,%u) not found\n",
			__func__, state->color_encoding, state->color_range);
		वापस;
	पूर्ण

	अगर (dispc->feat->subrev == DISPC_K2G)
		dispc_k2g_vid_ग_लिखो_csc(dispc, hw_plane, coef);
	अन्यथा
		dispc_k3_vid_ग_लिखो_csc(dispc, hw_plane, coef);
पूर्ण

अटल व्योम dispc_vid_csc_enable(काष्ठा dispc_device *dispc, u32 hw_plane,
				 bool enable)
अणु
	VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES, !!enable, 9, 9);
पूर्ण

/* SCALER */

अटल u32 dispc_calc_fir_inc(u32 in, u32 out)
अणु
	वापस (u32)भाग_u64(0x200000ull * in, out);
पूर्ण

क्रमागत dispc_vid_fir_coef_set अणु
	DISPC_VID_FIR_COEF_HORIZ,
	DISPC_VID_FIR_COEF_HORIZ_UV,
	DISPC_VID_FIR_COEF_VERT,
	DISPC_VID_FIR_COEF_VERT_UV,
पूर्ण;

अटल व्योम dispc_vid_ग_लिखो_fir_coefs(काष्ठा dispc_device *dispc,
				      u32 hw_plane,
				      क्रमागत dispc_vid_fir_coef_set coef_set,
				      स्थिर काष्ठा tidss_scale_coefs *coefs)
अणु
	अटल स्थिर u16 c0_regs[] = अणु
		[DISPC_VID_FIR_COEF_HORIZ] = DISPC_VID_FIR_COEFS_H0,
		[DISPC_VID_FIR_COEF_HORIZ_UV] = DISPC_VID_FIR_COEFS_H0_C,
		[DISPC_VID_FIR_COEF_VERT] = DISPC_VID_FIR_COEFS_V0,
		[DISPC_VID_FIR_COEF_VERT_UV] = DISPC_VID_FIR_COEFS_V0_C,
	पूर्ण;

	अटल स्थिर u16 c12_regs[] = अणु
		[DISPC_VID_FIR_COEF_HORIZ] = DISPC_VID_FIR_COEFS_H12,
		[DISPC_VID_FIR_COEF_HORIZ_UV] = DISPC_VID_FIR_COEFS_H12_C,
		[DISPC_VID_FIR_COEF_VERT] = DISPC_VID_FIR_COEFS_V12,
		[DISPC_VID_FIR_COEF_VERT_UV] = DISPC_VID_FIR_COEFS_V12_C,
	पूर्ण;

	स्थिर u16 c0_base = c0_regs[coef_set];
	स्थिर u16 c12_base = c12_regs[coef_set];
	पूर्णांक phase;

	अगर (!coefs) अणु
		dev_err(dispc->dev, "%s: No coefficients given.\n", __func__);
		वापस;
	पूर्ण

	क्रम (phase = 0; phase <= 8; ++phase) अणु
		u16 reg = c0_base + phase * 4;
		u16 c0 = coefs->c0[phase];

		dispc_vid_ग_लिखो(dispc, hw_plane, reg, c0);
	पूर्ण

	क्रम (phase = 0; phase <= 15; ++phase) अणु
		u16 reg = c12_base + phase * 4;
		s16 c1, c2;
		u32 c12;

		c1 = coefs->c1[phase];
		c2 = coefs->c2[phase];
		c12 = FLD_VAL(c1, 19, 10) | FLD_VAL(c2, 29, 20);

		dispc_vid_ग_लिखो(dispc, hw_plane, reg, c12);
	पूर्ण
पूर्ण

अटल bool dispc_fourcc_is_yuv(u32 fourcc)
अणु
	चयन (fourcc) अणु
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_NV12:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

काष्ठा dispc_scaling_params अणु
	पूर्णांक xinc, yinc;
	u32 in_w, in_h, in_w_uv, in_h_uv;
	u32 fir_xinc, fir_yinc, fir_xinc_uv, fir_yinc_uv;
	bool scale_x, scale_y;
	स्थिर काष्ठा tidss_scale_coefs *xcoef, *ycoef, *xcoef_uv, *ycoef_uv;
	bool five_taps;
पूर्ण;

अटल पूर्णांक dispc_vid_calc_scaling(काष्ठा dispc_device *dispc,
				  स्थिर काष्ठा drm_plane_state *state,
				  काष्ठा dispc_scaling_params *sp,
				  bool lite_plane)
अणु
	स्थिर काष्ठा dispc_features_scaling *f = &dispc->feat->scaling;
	u32 fourcc = state->fb->क्रमmat->क्रमmat;
	u32 in_width_max_5tap = f->in_width_max_5tap_rgb;
	u32 in_width_max_3tap = f->in_width_max_3tap_rgb;
	u32 करोwnscale_limit;
	u32 in_width_max;

	स_रखो(sp, 0, माप(*sp));
	sp->xinc = 1;
	sp->yinc = 1;
	sp->in_w = state->src_w >> 16;
	sp->in_w_uv = sp->in_w;
	sp->in_h = state->src_h >> 16;
	sp->in_h_uv = sp->in_h;

	sp->scale_x = sp->in_w != state->crtc_w;
	sp->scale_y = sp->in_h != state->crtc_h;

	अगर (dispc_fourcc_is_yuv(fourcc)) अणु
		in_width_max_5tap = f->in_width_max_5tap_yuv;
		in_width_max_3tap = f->in_width_max_3tap_yuv;

		sp->in_w_uv >>= 1;
		sp->scale_x = true;

		अगर (fourcc == DRM_FORMAT_NV12) अणु
			sp->in_h_uv >>= 1;
			sp->scale_y = true;
		पूर्ण
	पूर्ण

	/* Skip the rest अगर no scaling is used */
	अगर ((!sp->scale_x && !sp->scale_y) || lite_plane)
		वापस 0;

	अगर (sp->in_w > in_width_max_5tap) अणु
		sp->five_taps = false;
		in_width_max = in_width_max_3tap;
		करोwnscale_limit = f->करोwnscale_limit_3tap;
	पूर्ण अन्यथा अणु
		sp->five_taps = true;
		in_width_max = in_width_max_5tap;
		करोwnscale_limit = f->करोwnscale_limit_5tap;
	पूर्ण

	अगर (sp->scale_x) अणु
		sp->fir_xinc = dispc_calc_fir_inc(sp->in_w, state->crtc_w);

		अगर (sp->fir_xinc < dispc_calc_fir_inc(1, f->upscale_limit)) अणु
			dev_dbg(dispc->dev,
				"%s: X-scaling factor %u/%u > %u\n",
				__func__, state->crtc_w, state->src_w >> 16,
				f->upscale_limit);
			वापस -EINVAL;
		पूर्ण

		अगर (sp->fir_xinc >= dispc_calc_fir_inc(करोwnscale_limit, 1)) अणु
			sp->xinc = DIV_ROUND_UP(DIV_ROUND_UP(sp->in_w,
							     state->crtc_w),
						करोwnscale_limit);

			अगर (sp->xinc > f->xinc_max) अणु
				dev_dbg(dispc->dev,
					"%s: X-scaling factor %u/%u < 1/%u\n",
					__func__, state->crtc_w,
					state->src_w >> 16,
					करोwnscale_limit * f->xinc_max);
				वापस -EINVAL;
			पूर्ण

			sp->in_w = (state->src_w >> 16) / sp->xinc;
		पूर्ण

		जबतक (sp->in_w > in_width_max) अणु
			sp->xinc++;
			sp->in_w = (state->src_w >> 16) / sp->xinc;
		पूर्ण

		अगर (sp->xinc > f->xinc_max) अणु
			dev_dbg(dispc->dev,
				"%s: Too wide input buffer %u > %u\n", __func__,
				state->src_w >> 16, in_width_max * f->xinc_max);
			वापस -EINVAL;
		पूर्ण

		/*
		 * We need even line length क्रम YUV क्रमmats. Decimation
		 * can lead to odd length, so we need to make it even
		 * again.
		 */
		अगर (dispc_fourcc_is_yuv(fourcc))
			sp->in_w &= ~1;

		sp->fir_xinc = dispc_calc_fir_inc(sp->in_w, state->crtc_w);
	पूर्ण

	अगर (sp->scale_y) अणु
		sp->fir_yinc = dispc_calc_fir_inc(sp->in_h, state->crtc_h);

		अगर (sp->fir_yinc < dispc_calc_fir_inc(1, f->upscale_limit)) अणु
			dev_dbg(dispc->dev,
				"%s: Y-scaling factor %u/%u > %u\n",
				__func__, state->crtc_h, state->src_h >> 16,
				f->upscale_limit);
			वापस -EINVAL;
		पूर्ण

		अगर (sp->fir_yinc >= dispc_calc_fir_inc(करोwnscale_limit, 1)) अणु
			sp->yinc = DIV_ROUND_UP(DIV_ROUND_UP(sp->in_h,
							     state->crtc_h),
						करोwnscale_limit);

			sp->in_h /= sp->yinc;
			sp->fir_yinc = dispc_calc_fir_inc(sp->in_h,
							  state->crtc_h);
		पूर्ण
	पूर्ण

	dev_dbg(dispc->dev,
		"%s: %ux%u decim %ux%u -> %ux%u firinc %u.%03ux%u.%03u taps %u -> %ux%u\n",
		__func__, state->src_w >> 16, state->src_h >> 16,
		sp->xinc, sp->yinc, sp->in_w, sp->in_h,
		sp->fir_xinc / 0x200000u,
		((sp->fir_xinc & 0x1FFFFFu) * 999u) / 0x1FFFFFu,
		sp->fir_yinc / 0x200000u,
		((sp->fir_yinc & 0x1FFFFFu) * 999u) / 0x1FFFFFu,
		sp->five_taps ? 5 : 3,
		state->crtc_w, state->crtc_h);

	अगर (dispc_fourcc_is_yuv(fourcc)) अणु
		अगर (sp->scale_x) अणु
			sp->in_w_uv /= sp->xinc;
			sp->fir_xinc_uv = dispc_calc_fir_inc(sp->in_w_uv,
							     state->crtc_w);
			sp->xcoef_uv = tidss_get_scale_coefs(dispc->dev,
							     sp->fir_xinc_uv,
							     true);
		पूर्ण
		अगर (sp->scale_y) अणु
			sp->in_h_uv /= sp->yinc;
			sp->fir_yinc_uv = dispc_calc_fir_inc(sp->in_h_uv,
							     state->crtc_h);
			sp->ycoef_uv = tidss_get_scale_coefs(dispc->dev,
							     sp->fir_yinc_uv,
							     sp->five_taps);
		पूर्ण
	पूर्ण

	अगर (sp->scale_x)
		sp->xcoef = tidss_get_scale_coefs(dispc->dev, sp->fir_xinc,
						  true);

	अगर (sp->scale_y)
		sp->ycoef = tidss_get_scale_coefs(dispc->dev, sp->fir_yinc,
						  sp->five_taps);

	वापस 0;
पूर्ण

अटल व्योम dispc_vid_set_scaling(काष्ठा dispc_device *dispc,
				  u32 hw_plane,
				  काष्ठा dispc_scaling_params *sp,
				  u32 fourcc)
अणु
	/* HORIZONTAL RESIZE ENABLE */
	VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES,
			sp->scale_x, 7, 7);

	/* VERTICAL RESIZE ENABLE */
	VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES,
			sp->scale_y, 8, 8);

	/* Skip the rest अगर no scaling is used */
	अगर (!sp->scale_x && !sp->scale_y)
		वापस;

	/* VERTICAL 5-TAPS  */
	VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES,
			sp->five_taps, 21, 21);

	अगर (dispc_fourcc_is_yuv(fourcc)) अणु
		अगर (sp->scale_x) अणु
			dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_FIRH2,
					sp->fir_xinc_uv);
			dispc_vid_ग_लिखो_fir_coefs(dispc, hw_plane,
						  DISPC_VID_FIR_COEF_HORIZ_UV,
						  sp->xcoef_uv);
		पूर्ण
		अगर (sp->scale_y) अणु
			dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_FIRV2,
					sp->fir_yinc_uv);
			dispc_vid_ग_लिखो_fir_coefs(dispc, hw_plane,
						  DISPC_VID_FIR_COEF_VERT_UV,
						  sp->ycoef_uv);
		पूर्ण
	पूर्ण

	अगर (sp->scale_x) अणु
		dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_FIRH, sp->fir_xinc);
		dispc_vid_ग_लिखो_fir_coefs(dispc, hw_plane,
					  DISPC_VID_FIR_COEF_HORIZ,
					  sp->xcoef);
	पूर्ण

	अगर (sp->scale_y) अणु
		dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_FIRV, sp->fir_yinc);
		dispc_vid_ग_लिखो_fir_coefs(dispc, hw_plane,
					  DISPC_VID_FIR_COEF_VERT, sp->ycoef);
	पूर्ण
पूर्ण

/* OTHER */

अटल स्थिर काष्ठा अणु
	u32 fourcc;
	u8 dss_code;
पूर्ण dispc_color_क्रमmats[] = अणु
	अणु DRM_FORMAT_ARGB4444, 0x0, पूर्ण,
	अणु DRM_FORMAT_ABGR4444, 0x1, पूर्ण,
	अणु DRM_FORMAT_RGBA4444, 0x2, पूर्ण,

	अणु DRM_FORMAT_RGB565, 0x3, पूर्ण,
	अणु DRM_FORMAT_BGR565, 0x4, पूर्ण,

	अणु DRM_FORMAT_ARGB1555, 0x5, पूर्ण,
	अणु DRM_FORMAT_ABGR1555, 0x6, पूर्ण,

	अणु DRM_FORMAT_ARGB8888, 0x7, पूर्ण,
	अणु DRM_FORMAT_ABGR8888, 0x8, पूर्ण,
	अणु DRM_FORMAT_RGBA8888, 0x9, पूर्ण,
	अणु DRM_FORMAT_BGRA8888, 0xa, पूर्ण,

	अणु DRM_FORMAT_RGB888, 0xb, पूर्ण,
	अणु DRM_FORMAT_BGR888, 0xc, पूर्ण,

	अणु DRM_FORMAT_ARGB2101010, 0xe, पूर्ण,
	अणु DRM_FORMAT_ABGR2101010, 0xf, पूर्ण,

	अणु DRM_FORMAT_XRGB4444, 0x20, पूर्ण,
	अणु DRM_FORMAT_XBGR4444, 0x21, पूर्ण,
	अणु DRM_FORMAT_RGBX4444, 0x22, पूर्ण,

	अणु DRM_FORMAT_ARGB1555, 0x25, पूर्ण,
	अणु DRM_FORMAT_ABGR1555, 0x26, पूर्ण,

	अणु DRM_FORMAT_XRGB8888, 0x27, पूर्ण,
	अणु DRM_FORMAT_XBGR8888, 0x28, पूर्ण,
	अणु DRM_FORMAT_RGBX8888, 0x29, पूर्ण,
	अणु DRM_FORMAT_BGRX8888, 0x2a, पूर्ण,

	अणु DRM_FORMAT_XRGB2101010, 0x2e, पूर्ण,
	अणु DRM_FORMAT_XBGR2101010, 0x2f, पूर्ण,

	अणु DRM_FORMAT_YUYV, 0x3e, पूर्ण,
	अणु DRM_FORMAT_UYVY, 0x3f, पूर्ण,

	अणु DRM_FORMAT_NV12, 0x3d, पूर्ण,
पूर्ण;

अटल व्योम dispc_plane_set_pixel_क्रमmat(काष्ठा dispc_device *dispc,
					 u32 hw_plane, u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dispc_color_क्रमmats); ++i) अणु
		अगर (dispc_color_क्रमmats[i].fourcc == fourcc) अणु
			VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES,
					dispc_color_क्रमmats[i].dss_code,
					6, 1);
			वापस;
		पूर्ण
	पूर्ण

	WARN_ON(1);
पूर्ण

स्थिर u32 *dispc_plane_क्रमmats(काष्ठा dispc_device *dispc, अचिन्हित पूर्णांक *len)
अणु
	WARN_ON(!dispc->fourccs);

	*len = dispc->num_fourccs;

	वापस dispc->fourccs;
पूर्ण

अटल s32 pixinc(पूर्णांक pixels, u8 ps)
अणु
	अगर (pixels == 1)
		वापस 1;
	अन्यथा अगर (pixels > 1)
		वापस 1 + (pixels - 1) * ps;
	अन्यथा अगर (pixels < 0)
		वापस 1 - (-pixels + 1) * ps;

	WARN_ON(1);
	वापस 0;
पूर्ण

पूर्णांक dispc_plane_check(काष्ठा dispc_device *dispc, u32 hw_plane,
		      स्थिर काष्ठा drm_plane_state *state,
		      u32 hw_videoport)
अणु
	bool lite = dispc->feat->vid_lite[hw_plane];
	u32 fourcc = state->fb->क्रमmat->क्रमmat;
	bool need_scaling = state->src_w >> 16 != state->crtc_w ||
		state->src_h >> 16 != state->crtc_h;
	काष्ठा dispc_scaling_params scaling;
	पूर्णांक ret;

	अगर (dispc_fourcc_is_yuv(fourcc)) अणु
		अगर (!dispc_find_csc(state->color_encoding,
				    state->color_range)) अणु
			dev_dbg(dispc->dev,
				"%s: Unsupported CSC (%u,%u) for HW plane %u\n",
				__func__, state->color_encoding,
				state->color_range, hw_plane);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (need_scaling) अणु
		अगर (lite) अणु
			dev_dbg(dispc->dev,
				"%s: Lite plane %u can't scale %ux%u!=%ux%u\n",
				__func__, hw_plane,
				state->src_w >> 16, state->src_h >> 16,
				state->crtc_w, state->crtc_h);
			वापस -EINVAL;
		पूर्ण
		ret = dispc_vid_calc_scaling(dispc, state, &scaling, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल
dma_addr_t dispc_plane_state_paddr(स्थिर काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_gem_cma_object *gem;
	u32 x = state->src_x >> 16;
	u32 y = state->src_y >> 16;

	gem = drm_fb_cma_get_gem_obj(state->fb, 0);

	वापस gem->paddr + fb->offsets[0] + x * fb->क्रमmat->cpp[0] +
		y * fb->pitches[0];
पूर्ण

अटल
dma_addr_t dispc_plane_state_p_uv_addr(स्थिर काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_gem_cma_object *gem;
	u32 x = state->src_x >> 16;
	u32 y = state->src_y >> 16;

	अगर (WARN_ON(state->fb->क्रमmat->num_planes != 2))
		वापस 0;

	gem = drm_fb_cma_get_gem_obj(fb, 1);

	वापस gem->paddr + fb->offsets[1] +
		(x * fb->क्रमmat->cpp[1] / fb->क्रमmat->hsub) +
		(y * fb->pitches[1] / fb->क्रमmat->vsub);
पूर्ण

पूर्णांक dispc_plane_setup(काष्ठा dispc_device *dispc, u32 hw_plane,
		      स्थिर काष्ठा drm_plane_state *state,
		      u32 hw_videoport)
अणु
	bool lite = dispc->feat->vid_lite[hw_plane];
	u32 fourcc = state->fb->क्रमmat->क्रमmat;
	u16 cpp = state->fb->क्रमmat->cpp[0];
	u32 fb_width = state->fb->pitches[0] / cpp;
	dma_addr_t paddr = dispc_plane_state_paddr(state);
	काष्ठा dispc_scaling_params scale;

	dispc_vid_calc_scaling(dispc, state, &scale, lite);

	dispc_plane_set_pixel_क्रमmat(dispc, hw_plane, fourcc);

	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_BA_0, paddr & 0xffffffff);
	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_BA_EXT_0, (u64)paddr >> 32);
	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_BA_1, paddr & 0xffffffff);
	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_BA_EXT_1, (u64)paddr >> 32);

	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_PICTURE_SIZE,
			(scale.in_w - 1) | ((scale.in_h - 1) << 16));

	/* For YUV422 क्रमmat we use the macropixel size क्रम pixel inc */
	अगर (fourcc == DRM_FORMAT_YUYV || fourcc == DRM_FORMAT_UYVY)
		dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_PIXEL_INC,
				pixinc(scale.xinc, cpp * 2));
	अन्यथा
		dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_PIXEL_INC,
				pixinc(scale.xinc, cpp));

	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_ROW_INC,
			pixinc(1 + (scale.yinc * fb_width -
				    scale.xinc * scale.in_w),
			       cpp));

	अगर (state->fb->क्रमmat->num_planes == 2) अणु
		u16 cpp_uv = state->fb->क्रमmat->cpp[1];
		u32 fb_width_uv = state->fb->pitches[1] / cpp_uv;
		dma_addr_t p_uv_addr = dispc_plane_state_p_uv_addr(state);

		dispc_vid_ग_लिखो(dispc, hw_plane,
				DISPC_VID_BA_UV_0, p_uv_addr & 0xffffffff);
		dispc_vid_ग_लिखो(dispc, hw_plane,
				DISPC_VID_BA_UV_EXT_0, (u64)p_uv_addr >> 32);
		dispc_vid_ग_लिखो(dispc, hw_plane,
				DISPC_VID_BA_UV_1, p_uv_addr & 0xffffffff);
		dispc_vid_ग_लिखो(dispc, hw_plane,
				DISPC_VID_BA_UV_EXT_1, (u64)p_uv_addr >> 32);

		dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_ROW_INC_UV,
				pixinc(1 + (scale.yinc * fb_width_uv -
					    scale.xinc * scale.in_w_uv),
				       cpp_uv));
	पूर्ण

	अगर (!lite) अणु
		dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_SIZE,
				(state->crtc_w - 1) |
				((state->crtc_h - 1) << 16));

		dispc_vid_set_scaling(dispc, hw_plane, &scale, fourcc);
	पूर्ण

	/* enable YUV->RGB color conversion */
	अगर (dispc_fourcc_is_yuv(fourcc)) अणु
		dispc_vid_csc_setup(dispc, hw_plane, state);
		dispc_vid_csc_enable(dispc, hw_plane, true);
	पूर्ण अन्यथा अणु
		dispc_vid_csc_enable(dispc, hw_plane, false);
	पूर्ण

	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_GLOBAL_ALPHA,
			0xFF & (state->alpha >> 8));

	अगर (state->pixel_blend_mode == DRM_MODE_BLEND_PREMULTI)
		VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES, 1,
				28, 28);
	अन्यथा
		VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES, 0,
				28, 28);

	वापस 0;
पूर्ण

पूर्णांक dispc_plane_enable(काष्ठा dispc_device *dispc, u32 hw_plane, bool enable)
अणु
	VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES, !!enable, 0, 0);

	वापस 0;
पूर्ण

अटल u32 dispc_vid_get_fअगरo_size(काष्ठा dispc_device *dispc, u32 hw_plane)
अणु
	वापस VID_REG_GET(dispc, hw_plane, DISPC_VID_BUF_SIZE_STATUS, 15, 0);
पूर्ण

अटल व्योम dispc_vid_set_mflag_threshold(काष्ठा dispc_device *dispc,
					  u32 hw_plane, u32 low, u32 high)
अणु
	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_MFLAG_THRESHOLD,
			FLD_VAL(high, 31, 16) | FLD_VAL(low, 15, 0));
पूर्ण

अटल व्योम dispc_vid_set_buf_threshold(काष्ठा dispc_device *dispc,
					u32 hw_plane, u32 low, u32 high)
अणु
	dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_BUF_THRESHOLD,
			FLD_VAL(high, 31, 16) | FLD_VAL(low, 15, 0));
पूर्ण

अटल व्योम dispc_k2g_plane_init(काष्ठा dispc_device *dispc)
अणु
	अचिन्हित पूर्णांक hw_plane;

	dev_dbg(dispc->dev, "%s()\n", __func__);

	/* MFLAG_CTRL = ENABLED */
	REG_FLD_MOD(dispc, DISPC_GLOBAL_MFLAG_ATTRIBUTE, 2, 1, 0);
	/* MFLAG_START = MFLAGNORMALSTARTMODE */
	REG_FLD_MOD(dispc, DISPC_GLOBAL_MFLAG_ATTRIBUTE, 0, 6, 6);

	क्रम (hw_plane = 0; hw_plane < dispc->feat->num_planes; hw_plane++) अणु
		u32 size = dispc_vid_get_fअगरo_size(dispc, hw_plane);
		u32 thr_low, thr_high;
		u32 mflag_low, mflag_high;
		u32 preload;

		thr_high = size - 1;
		thr_low = size / 2;

		mflag_high = size * 2 / 3;
		mflag_low = size / 3;

		preload = thr_low;

		dev_dbg(dispc->dev,
			"%s: bufsize %u, buf_threshold %u/%u, mflag threshold %u/%u preload %u\n",
			dispc->feat->vid_name[hw_plane],
			size,
			thr_high, thr_low,
			mflag_high, mflag_low,
			preload);

		dispc_vid_set_buf_threshold(dispc, hw_plane,
					    thr_low, thr_high);
		dispc_vid_set_mflag_threshold(dispc, hw_plane,
					      mflag_low, mflag_high);

		dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_PRELOAD, preload);

		/*
		 * Prefetch up to fअगरo high-threshold value to minimize the
		 * possibility of underflows. Note that this means the PRELOAD
		 * रेजिस्टर is ignored.
		 */
		VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES, 1,
				19, 19);
	पूर्ण
पूर्ण

अटल व्योम dispc_k3_plane_init(काष्ठा dispc_device *dispc)
अणु
	अचिन्हित पूर्णांक hw_plane;
	u32 cba_lo_pri = 1;
	u32 cba_hi_pri = 0;

	dev_dbg(dispc->dev, "%s()\n", __func__);

	REG_FLD_MOD(dispc, DSS_CBA_CFG, cba_lo_pri, 2, 0);
	REG_FLD_MOD(dispc, DSS_CBA_CFG, cba_hi_pri, 5, 3);

	/* MFLAG_CTRL = ENABLED */
	REG_FLD_MOD(dispc, DISPC_GLOBAL_MFLAG_ATTRIBUTE, 2, 1, 0);
	/* MFLAG_START = MFLAGNORMALSTARTMODE */
	REG_FLD_MOD(dispc, DISPC_GLOBAL_MFLAG_ATTRIBUTE, 0, 6, 6);

	क्रम (hw_plane = 0; hw_plane < dispc->feat->num_planes; hw_plane++) अणु
		u32 size = dispc_vid_get_fअगरo_size(dispc, hw_plane);
		u32 thr_low, thr_high;
		u32 mflag_low, mflag_high;
		u32 preload;

		thr_high = size - 1;
		thr_low = size / 2;

		mflag_high = size * 2 / 3;
		mflag_low = size / 3;

		preload = thr_low;

		dev_dbg(dispc->dev,
			"%s: bufsize %u, buf_threshold %u/%u, mflag threshold %u/%u preload %u\n",
			dispc->feat->vid_name[hw_plane],
			size,
			thr_high, thr_low,
			mflag_high, mflag_low,
			preload);

		dispc_vid_set_buf_threshold(dispc, hw_plane,
					    thr_low, thr_high);
		dispc_vid_set_mflag_threshold(dispc, hw_plane,
					      mflag_low, mflag_high);

		dispc_vid_ग_लिखो(dispc, hw_plane, DISPC_VID_PRELOAD, preload);

		/* Prefech up to PRELOAD value */
		VID_REG_FLD_MOD(dispc, hw_plane, DISPC_VID_ATTRIBUTES, 0,
				19, 19);
	पूर्ण
पूर्ण

अटल व्योम dispc_plane_init(काष्ठा dispc_device *dispc)
अणु
	चयन (dispc->feat->subrev) अणु
	हाल DISPC_K2G:
		dispc_k2g_plane_init(dispc);
		अवरोध;
	हाल DISPC_AM65X:
	हाल DISPC_J721E:
		dispc_k3_plane_init(dispc);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम dispc_vp_init(काष्ठा dispc_device *dispc)
अणु
	अचिन्हित पूर्णांक i;

	dev_dbg(dispc->dev, "%s()\n", __func__);

	/* Enable the gamma Shaकरोw bit-field क्रम all VPs*/
	क्रम (i = 0; i < dispc->feat->num_vps; i++)
		VP_REG_FLD_MOD(dispc, i, DISPC_VP_CONFIG, 1, 2, 2);
पूर्ण

अटल व्योम dispc_initial_config(काष्ठा dispc_device *dispc)
अणु
	dispc_plane_init(dispc);
	dispc_vp_init(dispc);

	/* Note: Hardcoded DPI routing on J721E क्रम now */
	अगर (dispc->feat->subrev == DISPC_J721E) अणु
		dispc_ग_लिखो(dispc, DISPC_CONNECTIONS,
			    FLD_VAL(2, 3, 0) |		/* VP1 to DPI0 */
			    FLD_VAL(8, 7, 4)		/* VP3 to DPI1 */
			);
	पूर्ण
पूर्ण

अटल व्योम dispc_k2g_vp_ग_लिखो_gamma_table(काष्ठा dispc_device *dispc,
					   u32 hw_videoport)
अणु
	u32 *table = dispc->vp_data[hw_videoport].gamma_table;
	u32 hwlen = dispc->feat->vp_feat.color.gamma_size;
	अचिन्हित पूर्णांक i;

	dev_dbg(dispc->dev, "%s: hw_videoport %d\n", __func__, hw_videoport);

	अगर (WARN_ON(dispc->feat->vp_feat.color.gamma_type != TIDSS_GAMMA_8BIT))
		वापस;

	क्रम (i = 0; i < hwlen; ++i) अणु
		u32 v = table[i];

		v |= i << 24;

		dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_K2G_GAMMA_TABLE,
			       v);
	पूर्ण
पूर्ण

अटल व्योम dispc_am65x_vp_ग_लिखो_gamma_table(काष्ठा dispc_device *dispc,
					     u32 hw_videoport)
अणु
	u32 *table = dispc->vp_data[hw_videoport].gamma_table;
	u32 hwlen = dispc->feat->vp_feat.color.gamma_size;
	अचिन्हित पूर्णांक i;

	dev_dbg(dispc->dev, "%s: hw_videoport %d\n", __func__, hw_videoport);

	अगर (WARN_ON(dispc->feat->vp_feat.color.gamma_type != TIDSS_GAMMA_8BIT))
		वापस;

	क्रम (i = 0; i < hwlen; ++i) अणु
		u32 v = table[i];

		v |= i << 24;

		dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_GAMMA_TABLE, v);
	पूर्ण
पूर्ण

अटल व्योम dispc_j721e_vp_ग_लिखो_gamma_table(काष्ठा dispc_device *dispc,
					     u32 hw_videoport)
अणु
	u32 *table = dispc->vp_data[hw_videoport].gamma_table;
	u32 hwlen = dispc->feat->vp_feat.color.gamma_size;
	अचिन्हित पूर्णांक i;

	dev_dbg(dispc->dev, "%s: hw_videoport %d\n", __func__, hw_videoport);

	अगर (WARN_ON(dispc->feat->vp_feat.color.gamma_type != TIDSS_GAMMA_10BIT))
		वापस;

	क्रम (i = 0; i < hwlen; ++i) अणु
		u32 v = table[i];

		अगर (i == 0)
			v |= 1 << 31;

		dispc_vp_ग_लिखो(dispc, hw_videoport, DISPC_VP_GAMMA_TABLE, v);
	पूर्ण
पूर्ण

अटल व्योम dispc_vp_ग_लिखो_gamma_table(काष्ठा dispc_device *dispc,
				       u32 hw_videoport)
अणु
	चयन (dispc->feat->subrev) अणु
	हाल DISPC_K2G:
		dispc_k2g_vp_ग_लिखो_gamma_table(dispc, hw_videoport);
		अवरोध;
	हाल DISPC_AM65X:
		dispc_am65x_vp_ग_लिखो_gamma_table(dispc, hw_videoport);
		अवरोध;
	हाल DISPC_J721E:
		dispc_j721e_vp_ग_लिखो_gamma_table(dispc, hw_videoport);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_color_lut dispc_vp_gamma_शेष_lut[] = अणु
	अणु .red = 0, .green = 0, .blue = 0, पूर्ण,
	अणु .red = U16_MAX, .green = U16_MAX, .blue = U16_MAX, पूर्ण,
पूर्ण;

अटल व्योम dispc_vp_set_gamma(काष्ठा dispc_device *dispc,
			       u32 hw_videoport,
			       स्थिर काष्ठा drm_color_lut *lut,
			       अचिन्हित पूर्णांक length)
अणु
	u32 *table = dispc->vp_data[hw_videoport].gamma_table;
	u32 hwlen = dispc->feat->vp_feat.color.gamma_size;
	u32 hwbits;
	अचिन्हित पूर्णांक i;

	dev_dbg(dispc->dev, "%s: hw_videoport %d, lut len %u, hw len %u\n",
		__func__, hw_videoport, length, hwlen);

	अगर (dispc->feat->vp_feat.color.gamma_type == TIDSS_GAMMA_10BIT)
		hwbits = 10;
	अन्यथा
		hwbits = 8;

	अगर (!lut || length < 2) अणु
		lut = dispc_vp_gamma_शेष_lut;
		length = ARRAY_SIZE(dispc_vp_gamma_शेष_lut);
	पूर्ण

	क्रम (i = 0; i < length - 1; ++i) अणु
		अचिन्हित पूर्णांक first = i * (hwlen - 1) / (length - 1);
		अचिन्हित पूर्णांक last = (i + 1) * (hwlen - 1) / (length - 1);
		अचिन्हित पूर्णांक w = last - first;
		u16 r, g, b;
		अचिन्हित पूर्णांक j;

		अगर (w == 0)
			जारी;

		क्रम (j = 0; j <= w; j++) अणु
			r = (lut[i].red * (w - j) + lut[i + 1].red * j) / w;
			g = (lut[i].green * (w - j) + lut[i + 1].green * j) / w;
			b = (lut[i].blue * (w - j) + lut[i + 1].blue * j) / w;

			r >>= 16 - hwbits;
			g >>= 16 - hwbits;
			b >>= 16 - hwbits;

			table[first + j] = (r << (hwbits * 2)) |
				(g << hwbits) | b;
		पूर्ण
	पूर्ण

	dispc_vp_ग_लिखो_gamma_table(dispc, hw_videoport);
पूर्ण

अटल s16 dispc_S31_32_to_s2_8(s64 coef)
अणु
	u64 sign_bit = 1ULL << 63;
	u64 cbits = (u64)coef;
	s16 ret;

	अगर (cbits & sign_bit)
		ret = -clamp_val(((cbits & ~sign_bit) >> 24), 0, 0x200);
	अन्यथा
		ret = clamp_val(((cbits & ~sign_bit) >> 24), 0, 0x1FF);

	वापस ret;
पूर्ण

अटल व्योम dispc_k2g_cpr_from_cपंचांग(स्थिर काष्ठा drm_color_cपंचांग *cपंचांग,
				   काष्ठा dispc_csc_coef *cpr)
अणु
	स_रखो(cpr, 0, माप(*cpr));

	cpr->to_regval = dispc_csc_cpr_regval;
	cpr->m[CSC_RR] = dispc_S31_32_to_s2_8(cपंचांग->matrix[0]);
	cpr->m[CSC_RG] = dispc_S31_32_to_s2_8(cपंचांग->matrix[1]);
	cpr->m[CSC_RB] = dispc_S31_32_to_s2_8(cपंचांग->matrix[2]);
	cpr->m[CSC_GR] = dispc_S31_32_to_s2_8(cपंचांग->matrix[3]);
	cpr->m[CSC_GG] = dispc_S31_32_to_s2_8(cपंचांग->matrix[4]);
	cpr->m[CSC_GB] = dispc_S31_32_to_s2_8(cपंचांग->matrix[5]);
	cpr->m[CSC_BR] = dispc_S31_32_to_s2_8(cपंचांग->matrix[6]);
	cpr->m[CSC_BG] = dispc_S31_32_to_s2_8(cपंचांग->matrix[7]);
	cpr->m[CSC_BB] = dispc_S31_32_to_s2_8(cपंचांग->matrix[8]);
पूर्ण

#घोषणा CVAL(xR, xG, xB) (FLD_VAL(xR, 9, 0) | FLD_VAL(xG, 20, 11) |	\
			  FLD_VAL(xB, 31, 22))

अटल व्योम dispc_k2g_vp_csc_cpr_regval(स्थिर काष्ठा dispc_csc_coef *csc,
					u32 *regval)
अणु
	regval[0] = CVAL(csc->m[CSC_BB], csc->m[CSC_BG], csc->m[CSC_BR]);
	regval[1] = CVAL(csc->m[CSC_GB], csc->m[CSC_GG], csc->m[CSC_GR]);
	regval[2] = CVAL(csc->m[CSC_RB], csc->m[CSC_RG], csc->m[CSC_RR]);
पूर्ण

#अघोषित CVAL

अटल व्योम dispc_k2g_vp_ग_लिखो_csc(काष्ठा dispc_device *dispc, u32 hw_videoport,
				   स्थिर काष्ठा dispc_csc_coef *csc)
अणु
	अटल स्थिर u16 dispc_vp_cpr_coef_reg[] = अणु
		DISPC_VP_CSC_COEF0, DISPC_VP_CSC_COEF1, DISPC_VP_CSC_COEF2,
		/* K2G CPR is packed to three रेजिस्टरs. */
	पूर्ण;
	u32 regval[DISPC_CSC_REGVAL_LEN];
	अचिन्हित पूर्णांक i;

	dispc_k2g_vp_csc_cpr_regval(csc, regval);

	क्रम (i = 0; i < ARRAY_SIZE(dispc_vp_cpr_coef_reg); i++)
		dispc_vp_ग_लिखो(dispc, hw_videoport, dispc_vp_cpr_coef_reg[i],
			       regval[i]);
पूर्ण

अटल व्योम dispc_k2g_vp_set_cपंचांग(काष्ठा dispc_device *dispc, u32 hw_videoport,
				 काष्ठा drm_color_cपंचांग *cपंचांग)
अणु
	u32 cprenable = 0;

	अगर (cपंचांग) अणु
		काष्ठा dispc_csc_coef cpr;

		dispc_k2g_cpr_from_cपंचांग(cपंचांग, &cpr);
		dispc_k2g_vp_ग_लिखो_csc(dispc, hw_videoport, &cpr);
		cprenable = 1;
	पूर्ण

	VP_REG_FLD_MOD(dispc, hw_videoport, DISPC_VP_CONFIG,
		       cprenable, 15, 15);
पूर्ण

अटल s16 dispc_S31_32_to_s3_8(s64 coef)
अणु
	u64 sign_bit = 1ULL << 63;
	u64 cbits = (u64)coef;
	s16 ret;

	अगर (cbits & sign_bit)
		ret = -clamp_val(((cbits & ~sign_bit) >> 24), 0, 0x400);
	अन्यथा
		ret = clamp_val(((cbits & ~sign_bit) >> 24), 0, 0x3FF);

	वापस ret;
पूर्ण

अटल व्योम dispc_csc_from_cपंचांग(स्थिर काष्ठा drm_color_cपंचांग *cपंचांग,
			       काष्ठा dispc_csc_coef *cpr)
अणु
	स_रखो(cpr, 0, माप(*cpr));

	cpr->to_regval = dispc_csc_cpr_regval;
	cpr->m[CSC_RR] = dispc_S31_32_to_s3_8(cपंचांग->matrix[0]);
	cpr->m[CSC_RG] = dispc_S31_32_to_s3_8(cपंचांग->matrix[1]);
	cpr->m[CSC_RB] = dispc_S31_32_to_s3_8(cपंचांग->matrix[2]);
	cpr->m[CSC_GR] = dispc_S31_32_to_s3_8(cपंचांग->matrix[3]);
	cpr->m[CSC_GG] = dispc_S31_32_to_s3_8(cपंचांग->matrix[4]);
	cpr->m[CSC_GB] = dispc_S31_32_to_s3_8(cपंचांग->matrix[5]);
	cpr->m[CSC_BR] = dispc_S31_32_to_s3_8(cपंचांग->matrix[6]);
	cpr->m[CSC_BG] = dispc_S31_32_to_s3_8(cपंचांग->matrix[7]);
	cpr->m[CSC_BB] = dispc_S31_32_to_s3_8(cपंचांग->matrix[8]);
पूर्ण

अटल व्योम dispc_k3_vp_ग_लिखो_csc(काष्ठा dispc_device *dispc, u32 hw_videoport,
				  स्थिर काष्ठा dispc_csc_coef *csc)
अणु
	अटल स्थिर u16 dispc_vp_csc_coef_reg[DISPC_CSC_REGVAL_LEN] = अणु
		DISPC_VP_CSC_COEF0, DISPC_VP_CSC_COEF1, DISPC_VP_CSC_COEF2,
		DISPC_VP_CSC_COEF3, DISPC_VP_CSC_COEF4, DISPC_VP_CSC_COEF5,
		DISPC_VP_CSC_COEF6, DISPC_VP_CSC_COEF7,
	पूर्ण;
	u32 regval[DISPC_CSC_REGVAL_LEN];
	अचिन्हित पूर्णांक i;

	csc->to_regval(csc, regval);

	क्रम (i = 0; i < ARRAY_SIZE(regval); i++)
		dispc_vp_ग_लिखो(dispc, hw_videoport, dispc_vp_csc_coef_reg[i],
			       regval[i]);
पूर्ण

अटल व्योम dispc_k3_vp_set_cपंचांग(काष्ठा dispc_device *dispc, u32 hw_videoport,
				काष्ठा drm_color_cपंचांग *cपंचांग)
अणु
	u32 colorconvenable = 0;

	अगर (cपंचांग) अणु
		काष्ठा dispc_csc_coef csc;

		dispc_csc_from_cपंचांग(cपंचांग, &csc);
		dispc_k3_vp_ग_लिखो_csc(dispc, hw_videoport, &csc);
		colorconvenable = 1;
	पूर्ण

	VP_REG_FLD_MOD(dispc, hw_videoport, DISPC_VP_CONFIG,
		       colorconvenable, 24, 24);
पूर्ण

अटल व्योम dispc_vp_set_color_mgmt(काष्ठा dispc_device *dispc,
				    u32 hw_videoport,
				    स्थिर काष्ठा drm_crtc_state *state,
				    bool newmodeset)
अणु
	काष्ठा drm_color_lut *lut = शून्य;
	काष्ठा drm_color_cपंचांग *cपंचांग = शून्य;
	अचिन्हित पूर्णांक length = 0;

	अगर (!(state->color_mgmt_changed || newmodeset))
		वापस;

	अगर (state->gamma_lut) अणु
		lut = (काष्ठा drm_color_lut *)state->gamma_lut->data;
		length = state->gamma_lut->length / माप(*lut);
	पूर्ण

	dispc_vp_set_gamma(dispc, hw_videoport, lut, length);

	अगर (state->cपंचांग)
		cपंचांग = (काष्ठा drm_color_cपंचांग *)state->cपंचांग->data;

	अगर (dispc->feat->subrev == DISPC_K2G)
		dispc_k2g_vp_set_cपंचांग(dispc, hw_videoport, cपंचांग);
	अन्यथा
		dispc_k3_vp_set_cपंचांग(dispc, hw_videoport, cपंचांग);
पूर्ण

व्योम dispc_vp_setup(काष्ठा dispc_device *dispc, u32 hw_videoport,
		    स्थिर काष्ठा drm_crtc_state *state, bool newmodeset)
अणु
	dispc_vp_set_शेष_color(dispc, hw_videoport, 0);
	dispc_vp_set_color_mgmt(dispc, hw_videoport, state, newmodeset);
पूर्ण

पूर्णांक dispc_runसमय_suspend(काष्ठा dispc_device *dispc)
अणु
	dev_dbg(dispc->dev, "suspend\n");

	dispc->is_enabled = false;

	clk_disable_unprepare(dispc->fclk);

	वापस 0;
पूर्ण

पूर्णांक dispc_runसमय_resume(काष्ठा dispc_device *dispc)
अणु
	dev_dbg(dispc->dev, "resume\n");

	clk_prepare_enable(dispc->fclk);

	अगर (REG_GET(dispc, DSS_SYSSTATUS, 0, 0) == 0)
		dev_warn(dispc->dev, "DSS FUNC RESET not done!\n");

	dev_dbg(dispc->dev, "OMAP DSS7 rev 0x%x\n",
		dispc_पढ़ो(dispc, DSS_REVISION));

	dev_dbg(dispc->dev, "VP RESETDONE %d,%d,%d\n",
		REG_GET(dispc, DSS_SYSSTATUS, 1, 1),
		REG_GET(dispc, DSS_SYSSTATUS, 2, 2),
		REG_GET(dispc, DSS_SYSSTATUS, 3, 3));

	अगर (dispc->feat->subrev == DISPC_AM65X)
		dev_dbg(dispc->dev, "OLDI RESETDONE %d,%d,%d\n",
			REG_GET(dispc, DSS_SYSSTATUS, 5, 5),
			REG_GET(dispc, DSS_SYSSTATUS, 6, 6),
			REG_GET(dispc, DSS_SYSSTATUS, 7, 7));

	dev_dbg(dispc->dev, "DISPC IDLE %d\n",
		REG_GET(dispc, DSS_SYSSTATUS, 9, 9));

	dispc_initial_config(dispc);

	dispc->is_enabled = true;

	tidss_irq_resume(dispc->tidss);

	वापस 0;
पूर्ण

व्योम dispc_हटाओ(काष्ठा tidss_device *tidss)
अणु
	dev_dbg(tidss->dev, "%s\n", __func__);

	tidss->dispc = शून्य;
पूर्ण

अटल पूर्णांक dispc_iomap_resource(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
				व्योम __iomem **base)
अणु
	व्योम __iomem *b;

	b = devm_platक्रमm_ioremap_resource_byname(pdev, name);
	अगर (IS_ERR(b)) अणु
		dev_err(&pdev->dev, "cannot ioremap resource '%s'\n", name);
		वापस PTR_ERR(b);
	पूर्ण

	*base = b;

	वापस 0;
पूर्ण

अटल पूर्णांक dispc_init_am65x_oldi_io_ctrl(काष्ठा device *dev,
					 काष्ठा dispc_device *dispc)
अणु
	dispc->oldi_io_ctrl =
		syscon_regmap_lookup_by_phandle(dev->of_node,
						"ti,am65x-oldi-io-ctrl");
	अगर (PTR_ERR(dispc->oldi_io_ctrl) == -ENODEV) अणु
		dispc->oldi_io_ctrl = शून्य;
	पूर्ण अन्यथा अगर (IS_ERR(dispc->oldi_io_ctrl)) अणु
		dev_err(dev, "%s: syscon_regmap_lookup_by_phandle failed %ld\n",
			__func__, PTR_ERR(dispc->oldi_io_ctrl));
		वापस PTR_ERR(dispc->oldi_io_ctrl);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dispc_init_errata(काष्ठा dispc_device *dispc)
अणु
	अटल स्थिर काष्ठा soc_device_attribute am65x_sr10_soc_devices[] = अणु
		अणु .family = "AM65X", .revision = "SR1.0" पूर्ण,
		अणु /* sentinel */ पूर्ण
	पूर्ण;

	अगर (soc_device_match(am65x_sr10_soc_devices)) अणु
		dispc->errata.i2000 = true;
		dev_info(dispc->dev, "WA for erratum i2000: YUV formats disabled\n");
	पूर्ण
पूर्ण

पूर्णांक dispc_init(काष्ठा tidss_device *tidss)
अणु
	काष्ठा device *dev = tidss->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा dispc_device *dispc;
	स्थिर काष्ठा dispc_features *feat;
	अचिन्हित पूर्णांक i, num_fourccs;
	पूर्णांक r = 0;

	dev_dbg(dev, "%s\n", __func__);

	feat = tidss->feat;

	अगर (feat->subrev != DISPC_K2G) अणु
		r = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
		अगर (r)
			dev_warn(dev, "cannot set DMA masks to 48-bit\n");
	पूर्ण

	dispc = devm_kzalloc(dev, माप(*dispc), GFP_KERNEL);
	अगर (!dispc)
		वापस -ENOMEM;

	dispc->tidss = tidss;
	dispc->dev = dev;
	dispc->feat = feat;

	dispc_init_errata(dispc);

	dispc->fourccs = devm_kसुस्मृति(dev, ARRAY_SIZE(dispc_color_क्रमmats),
				      माप(*dispc->fourccs), GFP_KERNEL);
	अगर (!dispc->fourccs)
		वापस -ENOMEM;

	num_fourccs = 0;
	क्रम (i = 0; i < ARRAY_SIZE(dispc_color_क्रमmats); ++i) अणु
		अगर (dispc->errata.i2000 &&
		    dispc_fourcc_is_yuv(dispc_color_क्रमmats[i].fourcc)) अणु
			जारी;
		पूर्ण
		dispc->fourccs[num_fourccs++] = dispc_color_क्रमmats[i].fourcc;
	पूर्ण

	dispc->num_fourccs = num_fourccs;

	dispc_common_regmap = dispc->feat->common_regs;

	r = dispc_iomap_resource(pdev, dispc->feat->common,
				 &dispc->base_common);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < dispc->feat->num_planes; i++) अणु
		r = dispc_iomap_resource(pdev, dispc->feat->vid_name[i],
					 &dispc->base_vid[i]);
		अगर (r)
			वापस r;
	पूर्ण

	क्रम (i = 0; i < dispc->feat->num_vps; i++) अणु
		u32 gamma_size = dispc->feat->vp_feat.color.gamma_size;
		u32 *gamma_table;
		काष्ठा clk *clk;

		r = dispc_iomap_resource(pdev, dispc->feat->ovr_name[i],
					 &dispc->base_ovr[i]);
		अगर (r)
			वापस r;

		r = dispc_iomap_resource(pdev, dispc->feat->vp_name[i],
					 &dispc->base_vp[i]);
		अगर (r)
			वापस r;

		clk = devm_clk_get(dev, dispc->feat->vpclk_name[i]);
		अगर (IS_ERR(clk)) अणु
			dev_err(dev, "%s: Failed to get clk %s:%ld\n", __func__,
				dispc->feat->vpclk_name[i], PTR_ERR(clk));
			वापस PTR_ERR(clk);
		पूर्ण
		dispc->vp_clk[i] = clk;

		gamma_table = devm_kदो_स्मृति_array(dev, gamma_size,
						 माप(*gamma_table),
						 GFP_KERNEL);
		अगर (!gamma_table)
			वापस -ENOMEM;
		dispc->vp_data[i].gamma_table = gamma_table;
	पूर्ण

	अगर (feat->subrev == DISPC_AM65X) अणु
		r = dispc_init_am65x_oldi_io_ctrl(dev, dispc);
		अगर (r)
			वापस r;
	पूर्ण

	dispc->fclk = devm_clk_get(dev, "fck");
	अगर (IS_ERR(dispc->fclk)) अणु
		dev_err(dev, "%s: Failed to get fclk: %ld\n",
			__func__, PTR_ERR(dispc->fclk));
		वापस PTR_ERR(dispc->fclk);
	पूर्ण
	dev_dbg(dev, "DSS fclk %lu Hz\n", clk_get_rate(dispc->fclk));

	of_property_पढ़ो_u32(dispc->dev->of_node, "max-memory-bandwidth",
			     &dispc->memory_bandwidth_limit);

	tidss->dispc = dispc;

	वापस 0;
पूर्ण
