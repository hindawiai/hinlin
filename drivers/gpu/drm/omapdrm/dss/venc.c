<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *
 * VENC settings from TI's DSS driver
 */

#घोषणा DSS_SUBSYS_NAME "VENC"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/component.h>
#समावेश <linux/sys_soc.h>

#समावेश <drm/drm_bridge.h>

#समावेश "omapdss.h"
#समावेश "dss.h"

/* Venc रेजिस्टरs */
#घोषणा VENC_REV_ID				0x00
#घोषणा VENC_STATUS				0x04
#घोषणा VENC_F_CONTROL				0x08
#घोषणा VENC_VIDOUT_CTRL			0x10
#घोषणा VENC_SYNC_CTRL				0x14
#घोषणा VENC_LLEN				0x1C
#घोषणा VENC_FLENS				0x20
#घोषणा VENC_HFLTR_CTRL				0x24
#घोषणा VENC_CC_CARR_WSS_CARR			0x28
#घोषणा VENC_C_PHASE				0x2C
#घोषणा VENC_GAIN_U				0x30
#घोषणा VENC_GAIN_V				0x34
#घोषणा VENC_GAIN_Y				0x38
#घोषणा VENC_BLACK_LEVEL			0x3C
#घोषणा VENC_BLANK_LEVEL			0x40
#घोषणा VENC_X_COLOR				0x44
#घोषणा VENC_M_CONTROL				0x48
#घोषणा VENC_BSTAMP_WSS_DATA			0x4C
#घोषणा VENC_S_CARR				0x50
#घोषणा VENC_LINE21				0x54
#घोषणा VENC_LN_SEL				0x58
#घोषणा VENC_L21__WC_CTL			0x5C
#घोषणा VENC_HTRIGGER_VTRIGGER			0x60
#घोषणा VENC_SAVID__EAVID			0x64
#घोषणा VENC_FLEN__FAL				0x68
#घोषणा VENC_LAL__PHASE_RESET			0x6C
#घोषणा VENC_HS_INT_START_STOP_X		0x70
#घोषणा VENC_HS_EXT_START_STOP_X		0x74
#घोषणा VENC_VS_INT_START_X			0x78
#घोषणा VENC_VS_INT_STOP_X__VS_INT_START_Y	0x7C
#घोषणा VENC_VS_INT_STOP_Y__VS_EXT_START_X	0x80
#घोषणा VENC_VS_EXT_STOP_X__VS_EXT_START_Y	0x84
#घोषणा VENC_VS_EXT_STOP_Y			0x88
#घोषणा VENC_AVID_START_STOP_X			0x90
#घोषणा VENC_AVID_START_STOP_Y			0x94
#घोषणा VENC_FID_INT_START_X__FID_INT_START_Y	0xA0
#घोषणा VENC_FID_INT_OFFSET_Y__FID_EXT_START_X	0xA4
#घोषणा VENC_FID_EXT_START_Y__FID_EXT_OFFSET_Y	0xA8
#घोषणा VENC_TVDETGP_INT_START_STOP_X		0xB0
#घोषणा VENC_TVDETGP_INT_START_STOP_Y		0xB4
#घोषणा VENC_GEN_CTRL				0xB8
#घोषणा VENC_OUTPUT_CONTROL			0xC4
#घोषणा VENC_OUTPUT_TEST			0xC8
#घोषणा VENC_DAC_B__DAC_C			0xC8

काष्ठा venc_config अणु
	u32 f_control;
	u32 viकरोut_ctrl;
	u32 sync_ctrl;
	u32 llen;
	u32 flens;
	u32 hfltr_ctrl;
	u32 cc_carr_wss_carr;
	u32 c_phase;
	u32 gain_u;
	u32 gain_v;
	u32 gain_y;
	u32 black_level;
	u32 blank_level;
	u32 x_color;
	u32 m_control;
	u32 bstamp_wss_data;
	u32 s_carr;
	u32 line21;
	u32 ln_sel;
	u32 l21__wc_ctl;
	u32 htrigger_vtrigger;
	u32 savid__eavid;
	u32 flen__fal;
	u32 lal__phase_reset;
	u32 hs_पूर्णांक_start_stop_x;
	u32 hs_ext_start_stop_x;
	u32 vs_पूर्णांक_start_x;
	u32 vs_पूर्णांक_stop_x__vs_पूर्णांक_start_y;
	u32 vs_पूर्णांक_stop_y__vs_ext_start_x;
	u32 vs_ext_stop_x__vs_ext_start_y;
	u32 vs_ext_stop_y;
	u32 avid_start_stop_x;
	u32 avid_start_stop_y;
	u32 fid_पूर्णांक_start_x__fid_पूर्णांक_start_y;
	u32 fid_पूर्णांक_offset_y__fid_ext_start_x;
	u32 fid_ext_start_y__fid_ext_offset_y;
	u32 tvdetgp_पूर्णांक_start_stop_x;
	u32 tvdetgp_पूर्णांक_start_stop_y;
	u32 gen_ctrl;
पूर्ण;

/* from TRM */
अटल स्थिर काष्ठा venc_config venc_config_pal_trm = अणु
	.f_control				= 0,
	.viकरोut_ctrl				= 1,
	.sync_ctrl				= 0x40,
	.llen					= 0x35F, /* 863 */
	.flens					= 0x270, /* 624 */
	.hfltr_ctrl				= 0,
	.cc_carr_wss_carr			= 0x2F7225ED,
	.c_phase				= 0,
	.gain_u					= 0x111,
	.gain_v					= 0x181,
	.gain_y					= 0x140,
	.black_level				= 0x3B,
	.blank_level				= 0x3B,
	.x_color				= 0x7,
	.m_control				= 0x2,
	.bstamp_wss_data			= 0x3F,
	.s_carr					= 0x2A098ACB,
	.line21					= 0,
	.ln_sel					= 0x01290015,
	.l21__wc_ctl				= 0x0000F603,
	.htrigger_vtrigger			= 0,

	.savid__eavid				= 0x06A70108,
	.flen__fal				= 0x00180270,
	.lal__phase_reset			= 0x00040135,
	.hs_पूर्णांक_start_stop_x			= 0x00880358,
	.hs_ext_start_stop_x			= 0x000F035F,
	.vs_पूर्णांक_start_x				= 0x01A70000,
	.vs_पूर्णांक_stop_x__vs_पूर्णांक_start_y		= 0x000001A7,
	.vs_पूर्णांक_stop_y__vs_ext_start_x		= 0x01AF0000,
	.vs_ext_stop_x__vs_ext_start_y		= 0x000101AF,
	.vs_ext_stop_y				= 0x00000025,
	.avid_start_stop_x			= 0x03530083,
	.avid_start_stop_y			= 0x026C002E,
	.fid_पूर्णांक_start_x__fid_पूर्णांक_start_y	= 0x0001008A,
	.fid_पूर्णांक_offset_y__fid_ext_start_x	= 0x002E0138,
	.fid_ext_start_y__fid_ext_offset_y	= 0x01380001,

	.tvdetgp_पूर्णांक_start_stop_x		= 0x00140001,
	.tvdetgp_पूर्णांक_start_stop_y		= 0x00010001,
	.gen_ctrl				= 0x00FF0000,
पूर्ण;

/* from TRM */
अटल स्थिर काष्ठा venc_config venc_config_ntsc_trm = अणु
	.f_control				= 0,
	.viकरोut_ctrl				= 1,
	.sync_ctrl				= 0x8040,
	.llen					= 0x359,
	.flens					= 0x20C,
	.hfltr_ctrl				= 0,
	.cc_carr_wss_carr			= 0x043F2631,
	.c_phase				= 0,
	.gain_u					= 0x102,
	.gain_v					= 0x16C,
	.gain_y					= 0x12F,
	.black_level				= 0x43,
	.blank_level				= 0x38,
	.x_color				= 0x7,
	.m_control				= 0x1,
	.bstamp_wss_data			= 0x38,
	.s_carr					= 0x21F07C1F,
	.line21					= 0,
	.ln_sel					= 0x01310011,
	.l21__wc_ctl				= 0x0000F003,
	.htrigger_vtrigger			= 0,

	.savid__eavid				= 0x069300F4,
	.flen__fal				= 0x0016020C,
	.lal__phase_reset			= 0x00060107,
	.hs_पूर्णांक_start_stop_x			= 0x008E0350,
	.hs_ext_start_stop_x			= 0x000F0359,
	.vs_पूर्णांक_start_x				= 0x01A00000,
	.vs_पूर्णांक_stop_x__vs_पूर्णांक_start_y		= 0x020701A0,
	.vs_पूर्णांक_stop_y__vs_ext_start_x		= 0x01AC0024,
	.vs_ext_stop_x__vs_ext_start_y		= 0x020D01AC,
	.vs_ext_stop_y				= 0x00000006,
	.avid_start_stop_x			= 0x03480078,
	.avid_start_stop_y			= 0x02060024,
	.fid_पूर्णांक_start_x__fid_पूर्णांक_start_y	= 0x0001008A,
	.fid_पूर्णांक_offset_y__fid_ext_start_x	= 0x01AC0106,
	.fid_ext_start_y__fid_ext_offset_y	= 0x01060006,

	.tvdetgp_पूर्णांक_start_stop_x		= 0x00140001,
	.tvdetgp_पूर्णांक_start_stop_y		= 0x00010001,
	.gen_ctrl				= 0x00F90000,
पूर्ण;

क्रमागत venc_videomode अणु
	VENC_MODE_UNKNOWN,
	VENC_MODE_PAL,
	VENC_MODE_NTSC,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode omap_dss_pal_mode = अणु
	.hdisplay	= 720,
	.hsync_start	= 732,
	.hsync_end	= 796,
	.htotal		= 864,
	.vdisplay	= 574,
	.vsync_start	= 579,
	.vsync_end	= 584,
	.vtotal		= 625,
	.घड़ी		= 13500,

	.flags		= DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_NHSYNC |
			  DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode omap_dss_ntsc_mode = अणु
	.hdisplay	= 720,
	.hsync_start	= 736,
	.hsync_end	= 800,
	.htotal		= 858,
	.vdisplay	= 482,
	.vsync_start	= 488,
	.vsync_end	= 494,
	.vtotal		= 525,
	.घड़ी		= 13500,

	.flags		= DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_NHSYNC |
			  DRM_MODE_FLAG_NVSYNC,
पूर्ण;

काष्ठा venc_device अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *base;
	काष्ठा regulator *vdda_dac_reg;
	काष्ठा dss_device *dss;

	काष्ठा dss_debugfs_entry *debugfs;

	काष्ठा clk	*tv_dac_clk;

	स्थिर काष्ठा venc_config *config;
	क्रमागत omap_dss_venc_type type;
	bool invert_polarity;
	bool requires_tv_dac_clk;

	काष्ठा omap_dss_device output;
	काष्ठा drm_bridge bridge;
पूर्ण;

#घोषणा drm_bridge_to_venc(b) container_of(b, काष्ठा venc_device, bridge)

अटल अंतरभूत व्योम venc_ग_लिखो_reg(काष्ठा venc_device *venc, पूर्णांक idx, u32 val)
अणु
	__raw_ग_लिखोl(val, venc->base + idx);
पूर्ण

अटल अंतरभूत u32 venc_पढ़ो_reg(काष्ठा venc_device *venc, पूर्णांक idx)
अणु
	u32 l = __raw_पढ़ोl(venc->base + idx);
	वापस l;
पूर्ण

अटल व्योम venc_ग_लिखो_config(काष्ठा venc_device *venc,
			      स्थिर काष्ठा venc_config *config)
अणु
	DSSDBG("write venc conf\n");

	venc_ग_लिखो_reg(venc, VENC_LLEN, config->llen);
	venc_ग_लिखो_reg(venc, VENC_FLENS, config->flens);
	venc_ग_लिखो_reg(venc, VENC_CC_CARR_WSS_CARR, config->cc_carr_wss_carr);
	venc_ग_लिखो_reg(venc, VENC_C_PHASE, config->c_phase);
	venc_ग_लिखो_reg(venc, VENC_GAIN_U, config->gain_u);
	venc_ग_लिखो_reg(venc, VENC_GAIN_V, config->gain_v);
	venc_ग_लिखो_reg(venc, VENC_GAIN_Y, config->gain_y);
	venc_ग_लिखो_reg(venc, VENC_BLACK_LEVEL, config->black_level);
	venc_ग_लिखो_reg(venc, VENC_BLANK_LEVEL, config->blank_level);
	venc_ग_लिखो_reg(venc, VENC_M_CONTROL, config->m_control);
	venc_ग_लिखो_reg(venc, VENC_BSTAMP_WSS_DATA, config->bstamp_wss_data);
	venc_ग_लिखो_reg(venc, VENC_S_CARR, config->s_carr);
	venc_ग_लिखो_reg(venc, VENC_L21__WC_CTL, config->l21__wc_ctl);
	venc_ग_लिखो_reg(venc, VENC_SAVID__EAVID, config->savid__eavid);
	venc_ग_लिखो_reg(venc, VENC_FLEN__FAL, config->flen__fal);
	venc_ग_लिखो_reg(venc, VENC_LAL__PHASE_RESET, config->lal__phase_reset);
	venc_ग_लिखो_reg(venc, VENC_HS_INT_START_STOP_X,
		       config->hs_पूर्णांक_start_stop_x);
	venc_ग_लिखो_reg(venc, VENC_HS_EXT_START_STOP_X,
		       config->hs_ext_start_stop_x);
	venc_ग_लिखो_reg(venc, VENC_VS_INT_START_X, config->vs_पूर्णांक_start_x);
	venc_ग_लिखो_reg(venc, VENC_VS_INT_STOP_X__VS_INT_START_Y,
		       config->vs_पूर्णांक_stop_x__vs_पूर्णांक_start_y);
	venc_ग_लिखो_reg(venc, VENC_VS_INT_STOP_Y__VS_EXT_START_X,
		       config->vs_पूर्णांक_stop_y__vs_ext_start_x);
	venc_ग_लिखो_reg(venc, VENC_VS_EXT_STOP_X__VS_EXT_START_Y,
		       config->vs_ext_stop_x__vs_ext_start_y);
	venc_ग_लिखो_reg(venc, VENC_VS_EXT_STOP_Y, config->vs_ext_stop_y);
	venc_ग_लिखो_reg(venc, VENC_AVID_START_STOP_X, config->avid_start_stop_x);
	venc_ग_लिखो_reg(venc, VENC_AVID_START_STOP_Y, config->avid_start_stop_y);
	venc_ग_लिखो_reg(venc, VENC_FID_INT_START_X__FID_INT_START_Y,
		       config->fid_पूर्णांक_start_x__fid_पूर्णांक_start_y);
	venc_ग_लिखो_reg(venc, VENC_FID_INT_OFFSET_Y__FID_EXT_START_X,
		       config->fid_पूर्णांक_offset_y__fid_ext_start_x);
	venc_ग_लिखो_reg(venc, VENC_FID_EXT_START_Y__FID_EXT_OFFSET_Y,
		       config->fid_ext_start_y__fid_ext_offset_y);

	venc_ग_लिखो_reg(venc, VENC_DAC_B__DAC_C,
		       venc_पढ़ो_reg(venc, VENC_DAC_B__DAC_C));
	venc_ग_लिखो_reg(venc, VENC_VIDOUT_CTRL, config->viकरोut_ctrl);
	venc_ग_लिखो_reg(venc, VENC_HFLTR_CTRL, config->hfltr_ctrl);
	venc_ग_लिखो_reg(venc, VENC_X_COLOR, config->x_color);
	venc_ग_लिखो_reg(venc, VENC_LINE21, config->line21);
	venc_ग_लिखो_reg(venc, VENC_LN_SEL, config->ln_sel);
	venc_ग_लिखो_reg(venc, VENC_HTRIGGER_VTRIGGER, config->htrigger_vtrigger);
	venc_ग_लिखो_reg(venc, VENC_TVDETGP_INT_START_STOP_X,
		       config->tvdetgp_पूर्णांक_start_stop_x);
	venc_ग_लिखो_reg(venc, VENC_TVDETGP_INT_START_STOP_Y,
		       config->tvdetgp_पूर्णांक_start_stop_y);
	venc_ग_लिखो_reg(venc, VENC_GEN_CTRL, config->gen_ctrl);
	venc_ग_लिखो_reg(venc, VENC_F_CONTROL, config->f_control);
	venc_ग_लिखो_reg(venc, VENC_SYNC_CTRL, config->sync_ctrl);
पूर्ण

अटल व्योम venc_reset(काष्ठा venc_device *venc)
अणु
	पूर्णांक t = 1000;

	venc_ग_लिखो_reg(venc, VENC_F_CONTROL, 1<<8);
	जबतक (venc_पढ़ो_reg(venc, VENC_F_CONTROL) & (1<<8)) अणु
		अगर (--t == 0) अणु
			DSSERR("Failed to reset venc\n");
			वापस;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_OMAP2_DSS_SLEEP_AFTER_VENC_RESET
	/* the magical sleep that makes things work */
	/* XXX more info? What bug this circumvents? */
	msleep(20);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक venc_runसमय_get(काष्ठा venc_device *venc)
अणु
	पूर्णांक r;

	DSSDBG("venc_runtime_get\n");

	r = pm_runसमय_get_sync(&venc->pdev->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_noidle(&venc->pdev->dev);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम venc_runसमय_put(काष्ठा venc_device *venc)
अणु
	पूर्णांक r;

	DSSDBG("venc_runtime_put\n");

	r = pm_runसमय_put_sync(&venc->pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण

अटल पूर्णांक venc_घातer_on(काष्ठा venc_device *venc)
अणु
	u32 l;
	पूर्णांक r;

	r = venc_runसमय_get(venc);
	अगर (r)
		जाओ err0;

	venc_reset(venc);
	venc_ग_लिखो_config(venc, venc->config);

	dss_set_venc_output(venc->dss, venc->type);
	dss_set_dac_pwrdn_bgz(venc->dss, 1);

	l = 0;

	अगर (venc->type == OMAP_DSS_VENC_TYPE_COMPOSITE)
		l |= 1 << 1;
	अन्यथा /* S-Video */
		l |= (1 << 0) | (1 << 2);

	अगर (venc->invert_polarity == false)
		l |= 1 << 3;

	venc_ग_लिखो_reg(venc, VENC_OUTPUT_CONTROL, l);

	r = regulator_enable(venc->vdda_dac_reg);
	अगर (r)
		जाओ err1;

	r = dss_mgr_enable(&venc->output);
	अगर (r)
		जाओ err2;

	वापस 0;

err2:
	regulator_disable(venc->vdda_dac_reg);
err1:
	venc_ग_लिखो_reg(venc, VENC_OUTPUT_CONTROL, 0);
	dss_set_dac_pwrdn_bgz(venc->dss, 0);

	venc_runसमय_put(venc);
err0:
	वापस r;
पूर्ण

अटल व्योम venc_घातer_off(काष्ठा venc_device *venc)
अणु
	venc_ग_लिखो_reg(venc, VENC_OUTPUT_CONTROL, 0);
	dss_set_dac_pwrdn_bgz(venc->dss, 0);

	dss_mgr_disable(&venc->output);

	regulator_disable(venc->vdda_dac_reg);

	venc_runसमय_put(venc);
पूर्ण

अटल क्रमागत venc_videomode venc_get_videomode(स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (!(mode->flags & DRM_MODE_FLAG_INTERLACE))
		वापस VENC_MODE_UNKNOWN;

	अगर (mode->घड़ी == omap_dss_pal_mode.घड़ी &&
	    mode->hdisplay == omap_dss_pal_mode.hdisplay &&
	    mode->vdisplay == omap_dss_pal_mode.vdisplay)
		वापस VENC_MODE_PAL;

	अगर (mode->घड़ी == omap_dss_ntsc_mode.घड़ी &&
	    mode->hdisplay == omap_dss_ntsc_mode.hdisplay &&
	    mode->vdisplay == omap_dss_ntsc_mode.vdisplay)
		वापस VENC_MODE_NTSC;

	वापस VENC_MODE_UNKNOWN;
पूर्ण

अटल पूर्णांक venc_dump_regs(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा venc_device *venc = s->निजी;

#घोषणा DUMPREG(venc, r) \
	seq_म_लिखो(s, "%-35s %08x\n", #r, venc_पढ़ो_reg(venc, r))

	अगर (venc_runसमय_get(venc))
		वापस 0;

	DUMPREG(venc, VENC_F_CONTROL);
	DUMPREG(venc, VENC_VIDOUT_CTRL);
	DUMPREG(venc, VENC_SYNC_CTRL);
	DUMPREG(venc, VENC_LLEN);
	DUMPREG(venc, VENC_FLENS);
	DUMPREG(venc, VENC_HFLTR_CTRL);
	DUMPREG(venc, VENC_CC_CARR_WSS_CARR);
	DUMPREG(venc, VENC_C_PHASE);
	DUMPREG(venc, VENC_GAIN_U);
	DUMPREG(venc, VENC_GAIN_V);
	DUMPREG(venc, VENC_GAIN_Y);
	DUMPREG(venc, VENC_BLACK_LEVEL);
	DUMPREG(venc, VENC_BLANK_LEVEL);
	DUMPREG(venc, VENC_X_COLOR);
	DUMPREG(venc, VENC_M_CONTROL);
	DUMPREG(venc, VENC_BSTAMP_WSS_DATA);
	DUMPREG(venc, VENC_S_CARR);
	DUMPREG(venc, VENC_LINE21);
	DUMPREG(venc, VENC_LN_SEL);
	DUMPREG(venc, VENC_L21__WC_CTL);
	DUMPREG(venc, VENC_HTRIGGER_VTRIGGER);
	DUMPREG(venc, VENC_SAVID__EAVID);
	DUMPREG(venc, VENC_FLEN__FAL);
	DUMPREG(venc, VENC_LAL__PHASE_RESET);
	DUMPREG(venc, VENC_HS_INT_START_STOP_X);
	DUMPREG(venc, VENC_HS_EXT_START_STOP_X);
	DUMPREG(venc, VENC_VS_INT_START_X);
	DUMPREG(venc, VENC_VS_INT_STOP_X__VS_INT_START_Y);
	DUMPREG(venc, VENC_VS_INT_STOP_Y__VS_EXT_START_X);
	DUMPREG(venc, VENC_VS_EXT_STOP_X__VS_EXT_START_Y);
	DUMPREG(venc, VENC_VS_EXT_STOP_Y);
	DUMPREG(venc, VENC_AVID_START_STOP_X);
	DUMPREG(venc, VENC_AVID_START_STOP_Y);
	DUMPREG(venc, VENC_FID_INT_START_X__FID_INT_START_Y);
	DUMPREG(venc, VENC_FID_INT_OFFSET_Y__FID_EXT_START_X);
	DUMPREG(venc, VENC_FID_EXT_START_Y__FID_EXT_OFFSET_Y);
	DUMPREG(venc, VENC_TVDETGP_INT_START_STOP_X);
	DUMPREG(venc, VENC_TVDETGP_INT_START_STOP_Y);
	DUMPREG(venc, VENC_GEN_CTRL);
	DUMPREG(venc, VENC_OUTPUT_CONTROL);
	DUMPREG(venc, VENC_OUTPUT_TEST);

	venc_runसमय_put(venc);

#अघोषित DUMPREG
	वापस 0;
पूर्ण

अटल पूर्णांक venc_get_घड़ीs(काष्ठा venc_device *venc)
अणु
	काष्ठा clk *clk;

	अगर (venc->requires_tv_dac_clk) अणु
		clk = devm_clk_get(&venc->pdev->dev, "tv_dac_clk");
		अगर (IS_ERR(clk)) अणु
			DSSERR("can't get tv_dac_clk\n");
			वापस PTR_ERR(clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		clk = शून्य;
	पूर्ण

	venc->tv_dac_clk = clk;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Bridge Operations
 */

अटल पूर्णांक venc_bridge_attach(काष्ठा drm_bridge *bridge,
			      क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा venc_device *venc = drm_bridge_to_venc(bridge);

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR))
		वापस -EINVAL;

	वापस drm_bridge_attach(bridge->encoder, venc->output.next_bridge,
				 bridge, flags);
पूर्ण

अटल क्रमागत drm_mode_status
venc_bridge_mode_valid(काष्ठा drm_bridge *bridge,
		       स्थिर काष्ठा drm_display_info *info,
		       स्थिर काष्ठा drm_display_mode *mode)
अणु
	चयन (venc_get_videomode(mode)) अणु
	हाल VENC_MODE_PAL:
	हाल VENC_MODE_NTSC:
		वापस MODE_OK;

	शेष:
		वापस MODE_BAD;
	पूर्ण
पूर्ण

अटल bool venc_bridge_mode_fixup(काष्ठा drm_bridge *bridge,
				   स्थिर काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode)
अणु
	स्थिर काष्ठा drm_display_mode *venc_mode;

	चयन (venc_get_videomode(adjusted_mode)) अणु
	हाल VENC_MODE_PAL:
		venc_mode = &omap_dss_pal_mode;
		अवरोध;

	हाल VENC_MODE_NTSC:
		venc_mode = &omap_dss_ntsc_mode;
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	drm_mode_copy(adjusted_mode, venc_mode);
	drm_mode_set_crtcinfo(adjusted_mode, CRTC_INTERLACE_HALVE_V);
	drm_mode_set_name(adjusted_mode);

	वापस true;
पूर्ण

अटल व्योम venc_bridge_mode_set(काष्ठा drm_bridge *bridge,
				 स्थिर काष्ठा drm_display_mode *mode,
				 स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा venc_device *venc = drm_bridge_to_venc(bridge);
	क्रमागत venc_videomode venc_mode = venc_get_videomode(adjusted_mode);

	चयन (venc_mode) अणु
	शेष:
		WARN_ON_ONCE(1);
		fallthrough;
	हाल VENC_MODE_PAL:
		venc->config = &venc_config_pal_trm;
		अवरोध;

	हाल VENC_MODE_NTSC:
		venc->config = &venc_config_ntsc_trm;
		अवरोध;
	पूर्ण

	dispc_set_tv_pclk(venc->dss->dispc, 13500000);
पूर्ण

अटल व्योम venc_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा venc_device *venc = drm_bridge_to_venc(bridge);

	venc_घातer_on(venc);
पूर्ण

अटल व्योम venc_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा venc_device *venc = drm_bridge_to_venc(bridge);

	venc_घातer_off(venc);
पूर्ण

अटल पूर्णांक venc_bridge_get_modes(काष्ठा drm_bridge *bridge,
				 काष्ठा drm_connector *connector)
अणु
	अटल स्थिर काष्ठा drm_display_mode *modes[] = अणु
		&omap_dss_pal_mode,
		&omap_dss_ntsc_mode,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(modes); ++i) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_duplicate(connector->dev, modes[i]);
		अगर (!mode)
			वापस i;

		mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
		drm_mode_set_name(mode);
		drm_mode_probed_add(connector, mode);
	पूर्ण

	वापस ARRAY_SIZE(modes);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs venc_bridge_funcs = अणु
	.attach = venc_bridge_attach,
	.mode_valid = venc_bridge_mode_valid,
	.mode_fixup = venc_bridge_mode_fixup,
	.mode_set = venc_bridge_mode_set,
	.enable = venc_bridge_enable,
	.disable = venc_bridge_disable,
	.get_modes = venc_bridge_get_modes,
पूर्ण;

अटल व्योम venc_bridge_init(काष्ठा venc_device *venc)
अणु
	venc->bridge.funcs = &venc_bridge_funcs;
	venc->bridge.of_node = venc->pdev->dev.of_node;
	venc->bridge.ops = DRM_BRIDGE_OP_MODES;
	venc->bridge.type = DRM_MODE_CONNECTOR_SVIDEO;
	venc->bridge.पूर्णांकerlace_allowed = true;

	drm_bridge_add(&venc->bridge);
पूर्ण

अटल व्योम venc_bridge_cleanup(काष्ठा venc_device *venc)
अणु
	drm_bridge_हटाओ(&venc->bridge);
पूर्ण

/* -----------------------------------------------------------------------------
 * Component Bind & Unbind
 */

अटल पूर्णांक venc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा dss_device *dss = dss_get_device(master);
	काष्ठा venc_device *venc = dev_get_drvdata(dev);
	u8 rev_id;
	पूर्णांक r;

	venc->dss = dss;

	r = venc_runसमय_get(venc);
	अगर (r)
		वापस r;

	rev_id = (u8)(venc_पढ़ो_reg(venc, VENC_REV_ID) & 0xff);
	dev_dbg(dev, "OMAP VENC rev %d\n", rev_id);

	venc_runसमय_put(venc);

	venc->debugfs = dss_debugfs_create_file(dss, "venc", venc_dump_regs,
						venc);

	वापस 0;
पूर्ण

अटल व्योम venc_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा venc_device *venc = dev_get_drvdata(dev);

	dss_debugfs_हटाओ_file(venc->debugfs);
पूर्ण

अटल स्थिर काष्ठा component_ops venc_component_ops = अणु
	.bind	= venc_bind,
	.unbind	= venc_unbind,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe & Remove, Suspend & Resume
 */

अटल पूर्णांक venc_init_output(काष्ठा venc_device *venc)
अणु
	काष्ठा omap_dss_device *out = &venc->output;
	पूर्णांक r;

	venc_bridge_init(venc);

	out->dev = &venc->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_VENC;
	out->type = OMAP_DISPLAY_TYPE_VENC;
	out->name = "venc.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_DIGIT;
	out->of_port = 0;

	r = omapdss_device_init_output(out, &venc->bridge);
	अगर (r < 0) अणु
		venc_bridge_cleanup(venc);
		वापस r;
	पूर्ण

	omapdss_device_रेजिस्टर(out);

	वापस 0;
पूर्ण

अटल व्योम venc_uninit_output(काष्ठा venc_device *venc)
अणु
	omapdss_device_unरेजिस्टर(&venc->output);
	omapdss_device_cleanup_output(&venc->output);

	venc_bridge_cleanup(venc);
पूर्ण

अटल पूर्णांक venc_probe_of(काष्ठा venc_device *venc)
अणु
	काष्ठा device_node *node = venc->pdev->dev.of_node;
	काष्ठा device_node *ep;
	u32 channels;
	पूर्णांक r;

	ep = of_graph_get_endpoपूर्णांक_by_regs(node, 0, 0);
	अगर (!ep)
		वापस 0;

	venc->invert_polarity = of_property_पढ़ो_bool(ep, "ti,invert-polarity");

	r = of_property_पढ़ो_u32(ep, "ti,channels", &channels);
	अगर (r) अणु
		dev_err(&venc->pdev->dev,
			"failed to read property 'ti,channels': %d\n", r);
		जाओ err;
	पूर्ण

	चयन (channels) अणु
	हाल 1:
		venc->type = OMAP_DSS_VENC_TYPE_COMPOSITE;
		अवरोध;
	हाल 2:
		venc->type = OMAP_DSS_VENC_TYPE_SVIDEO;
		अवरोध;
	शेष:
		dev_err(&venc->pdev->dev, "bad channel property '%d'\n",
			channels);
		r = -EINVAL;
		जाओ err;
	पूर्ण

	of_node_put(ep);

	वापस 0;

err:
	of_node_put(ep);
	वापस r;
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute venc_soc_devices[] = अणु
	अणु .machine = "OMAP3[45]*" पूर्ण,
	अणु .machine = "AM35*" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक venc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा venc_device *venc;
	काष्ठा resource *venc_mem;
	पूर्णांक r;

	venc = kzalloc(माप(*venc), GFP_KERNEL);
	अगर (!venc)
		वापस -ENOMEM;

	venc->pdev = pdev;

	platक्रमm_set_drvdata(pdev, venc);

	/* The OMAP34xx, OMAP35xx and AM35xx VENC require the TV DAC घड़ी. */
	अगर (soc_device_match(venc_soc_devices))
		venc->requires_tv_dac_clk = true;

	venc->config = &venc_config_pal_trm;

	venc_mem = platक्रमm_get_resource(venc->pdev, IORESOURCE_MEM, 0);
	venc->base = devm_ioremap_resource(&pdev->dev, venc_mem);
	अगर (IS_ERR(venc->base)) अणु
		r = PTR_ERR(venc->base);
		जाओ err_मुक्त;
	पूर्ण

	venc->vdda_dac_reg = devm_regulator_get(&pdev->dev, "vdda");
	अगर (IS_ERR(venc->vdda_dac_reg)) अणु
		r = PTR_ERR(venc->vdda_dac_reg);
		अगर (r != -EPROBE_DEFER)
			DSSERR("can't get VDDA_DAC regulator\n");
		जाओ err_मुक्त;
	पूर्ण

	r = venc_get_घड़ीs(venc);
	अगर (r)
		जाओ err_मुक्त;

	r = venc_probe_of(venc);
	अगर (r)
		जाओ err_मुक्त;

	pm_runसमय_enable(&pdev->dev);

	r = venc_init_output(venc);
	अगर (r)
		जाओ err_pm_disable;

	r = component_add(&pdev->dev, &venc_component_ops);
	अगर (r)
		जाओ err_uninit_output;

	वापस 0;

err_uninit_output:
	venc_uninit_output(venc);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
err_मुक्त:
	kमुक्त(venc);
	वापस r;
पूर्ण

अटल पूर्णांक venc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा venc_device *venc = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &venc_component_ops);

	venc_uninit_output(venc);

	pm_runसमय_disable(&pdev->dev);

	kमुक्त(venc);
	वापस 0;
पूर्ण

अटल पूर्णांक venc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा venc_device *venc = dev_get_drvdata(dev);

	अगर (venc->tv_dac_clk)
		clk_disable_unprepare(venc->tv_dac_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक venc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा venc_device *venc = dev_get_drvdata(dev);

	अगर (venc->tv_dac_clk)
		clk_prepare_enable(venc->tv_dac_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops venc_pm_ops = अणु
	.runसमय_suspend = venc_runसमय_suspend,
	.runसमय_resume = venc_runसमय_resume,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id venc_of_match[] = अणु
	अणु .compatible = "ti,omap2-venc", पूर्ण,
	अणु .compatible = "ti,omap3-venc", पूर्ण,
	अणु .compatible = "ti,omap4-venc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

काष्ठा platक्रमm_driver omap_venchw_driver = अणु
	.probe		= venc_probe,
	.हटाओ		= venc_हटाओ,
	.driver         = अणु
		.name   = "omapdss_venc",
		.pm	= &venc_pm_ops,
		.of_match_table = venc_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
