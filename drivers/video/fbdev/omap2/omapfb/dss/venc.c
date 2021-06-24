<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/venc.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * VENC settings from TI's DSS driver
 */

#घोषणा DSS_SUBSYS_NAME "VENC"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/component.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

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

स्थिर काष्ठा omap_video_timings omap_dss_pal_timings = अणु
	.x_res		= 720,
	.y_res		= 574,
	.pixelघड़ी	= 13500000,
	.hsw		= 64,
	.hfp		= 12,
	.hbp		= 68,
	.vsw		= 5,
	.vfp		= 5,
	.vbp		= 41,

	.पूर्णांकerlace	= true,
पूर्ण;
EXPORT_SYMBOL(omap_dss_pal_timings);

स्थिर काष्ठा omap_video_timings omap_dss_ntsc_timings = अणु
	.x_res		= 720,
	.y_res		= 482,
	.pixelघड़ी	= 13500000,
	.hsw		= 64,
	.hfp		= 16,
	.hbp		= 58,
	.vsw		= 6,
	.vfp		= 6,
	.vbp		= 31,

	.पूर्णांकerlace	= true,
पूर्ण;
EXPORT_SYMBOL(omap_dss_ntsc_timings);

अटल काष्ठा अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *base;
	काष्ठा mutex venc_lock;
	u32 wss_data;
	काष्ठा regulator *vdda_dac_reg;

	काष्ठा clk	*tv_dac_clk;

	काष्ठा omap_video_timings timings;
	क्रमागत omap_dss_venc_type type;
	bool invert_polarity;

	काष्ठा omap_dss_device output;
पूर्ण venc;

अटल अंतरभूत व्योम venc_ग_लिखो_reg(पूर्णांक idx, u32 val)
अणु
	__raw_ग_लिखोl(val, venc.base + idx);
पूर्ण

अटल अंतरभूत u32 venc_पढ़ो_reg(पूर्णांक idx)
अणु
	u32 l = __raw_पढ़ोl(venc.base + idx);
	वापस l;
पूर्ण

अटल व्योम venc_ग_लिखो_config(स्थिर काष्ठा venc_config *config)
अणु
	DSSDBG("write venc conf\n");

	venc_ग_लिखो_reg(VENC_LLEN, config->llen);
	venc_ग_लिखो_reg(VENC_FLENS, config->flens);
	venc_ग_लिखो_reg(VENC_CC_CARR_WSS_CARR, config->cc_carr_wss_carr);
	venc_ग_लिखो_reg(VENC_C_PHASE, config->c_phase);
	venc_ग_लिखो_reg(VENC_GAIN_U, config->gain_u);
	venc_ग_लिखो_reg(VENC_GAIN_V, config->gain_v);
	venc_ग_लिखो_reg(VENC_GAIN_Y, config->gain_y);
	venc_ग_लिखो_reg(VENC_BLACK_LEVEL, config->black_level);
	venc_ग_लिखो_reg(VENC_BLANK_LEVEL, config->blank_level);
	venc_ग_लिखो_reg(VENC_M_CONTROL, config->m_control);
	venc_ग_लिखो_reg(VENC_BSTAMP_WSS_DATA, config->bstamp_wss_data |
			venc.wss_data);
	venc_ग_लिखो_reg(VENC_S_CARR, config->s_carr);
	venc_ग_लिखो_reg(VENC_L21__WC_CTL, config->l21__wc_ctl);
	venc_ग_लिखो_reg(VENC_SAVID__EAVID, config->savid__eavid);
	venc_ग_लिखो_reg(VENC_FLEN__FAL, config->flen__fal);
	venc_ग_लिखो_reg(VENC_LAL__PHASE_RESET, config->lal__phase_reset);
	venc_ग_लिखो_reg(VENC_HS_INT_START_STOP_X, config->hs_पूर्णांक_start_stop_x);
	venc_ग_लिखो_reg(VENC_HS_EXT_START_STOP_X, config->hs_ext_start_stop_x);
	venc_ग_लिखो_reg(VENC_VS_INT_START_X, config->vs_पूर्णांक_start_x);
	venc_ग_लिखो_reg(VENC_VS_INT_STOP_X__VS_INT_START_Y,
		       config->vs_पूर्णांक_stop_x__vs_पूर्णांक_start_y);
	venc_ग_लिखो_reg(VENC_VS_INT_STOP_Y__VS_EXT_START_X,
		       config->vs_पूर्णांक_stop_y__vs_ext_start_x);
	venc_ग_लिखो_reg(VENC_VS_EXT_STOP_X__VS_EXT_START_Y,
		       config->vs_ext_stop_x__vs_ext_start_y);
	venc_ग_लिखो_reg(VENC_VS_EXT_STOP_Y, config->vs_ext_stop_y);
	venc_ग_लिखो_reg(VENC_AVID_START_STOP_X, config->avid_start_stop_x);
	venc_ग_लिखो_reg(VENC_AVID_START_STOP_Y, config->avid_start_stop_y);
	venc_ग_लिखो_reg(VENC_FID_INT_START_X__FID_INT_START_Y,
		       config->fid_पूर्णांक_start_x__fid_पूर्णांक_start_y);
	venc_ग_लिखो_reg(VENC_FID_INT_OFFSET_Y__FID_EXT_START_X,
		       config->fid_पूर्णांक_offset_y__fid_ext_start_x);
	venc_ग_लिखो_reg(VENC_FID_EXT_START_Y__FID_EXT_OFFSET_Y,
		       config->fid_ext_start_y__fid_ext_offset_y);

	venc_ग_लिखो_reg(VENC_DAC_B__DAC_C,  venc_पढ़ो_reg(VENC_DAC_B__DAC_C));
	venc_ग_लिखो_reg(VENC_VIDOUT_CTRL, config->viकरोut_ctrl);
	venc_ग_लिखो_reg(VENC_HFLTR_CTRL, config->hfltr_ctrl);
	venc_ग_लिखो_reg(VENC_X_COLOR, config->x_color);
	venc_ग_लिखो_reg(VENC_LINE21, config->line21);
	venc_ग_लिखो_reg(VENC_LN_SEL, config->ln_sel);
	venc_ग_लिखो_reg(VENC_HTRIGGER_VTRIGGER, config->htrigger_vtrigger);
	venc_ग_लिखो_reg(VENC_TVDETGP_INT_START_STOP_X,
		       config->tvdetgp_पूर्णांक_start_stop_x);
	venc_ग_लिखो_reg(VENC_TVDETGP_INT_START_STOP_Y,
		       config->tvdetgp_पूर्णांक_start_stop_y);
	venc_ग_लिखो_reg(VENC_GEN_CTRL, config->gen_ctrl);
	venc_ग_लिखो_reg(VENC_F_CONTROL, config->f_control);
	venc_ग_लिखो_reg(VENC_SYNC_CTRL, config->sync_ctrl);
पूर्ण

अटल व्योम venc_reset(व्योम)
अणु
	पूर्णांक t = 1000;

	venc_ग_लिखो_reg(VENC_F_CONTROL, 1<<8);
	जबतक (venc_पढ़ो_reg(VENC_F_CONTROL) & (1<<8)) अणु
		अगर (--t == 0) अणु
			DSSERR("Failed to reset venc\n");
			वापस;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_FB_OMAP2_DSS_SLEEP_AFTER_VENC_RESET
	/* the magical sleep that makes things work */
	/* XXX more info? What bug this circumvents? */
	msleep(20);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक venc_runसमय_get(व्योम)
अणु
	पूर्णांक r;

	DSSDBG("venc_runtime_get\n");

	r = pm_runसमय_get_sync(&venc.pdev->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_sync(&venc.pdev->dev);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम venc_runसमय_put(व्योम)
अणु
	पूर्णांक r;

	DSSDBG("venc_runtime_put\n");

	r = pm_runसमय_put_sync(&venc.pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण

अटल स्थिर काष्ठा venc_config *venc_timings_to_config(
		काष्ठा omap_video_timings *timings)
अणु
	अगर (स_भेद(&omap_dss_pal_timings, timings, माप(*timings)) == 0)
		वापस &venc_config_pal_trm;

	अगर (स_भेद(&omap_dss_ntsc_timings, timings, माप(*timings)) == 0)
		वापस &venc_config_ntsc_trm;

	BUG();
	वापस शून्य;
पूर्ण

अटल पूर्णांक venc_घातer_on(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_overlay_manager *mgr = venc.output.manager;
	u32 l;
	पूर्णांक r;

	r = venc_runसमय_get();
	अगर (r)
		जाओ err0;

	venc_reset();
	venc_ग_लिखो_config(venc_timings_to_config(&venc.timings));

	dss_set_venc_output(venc.type);
	dss_set_dac_pwrdn_bgz(1);

	l = 0;

	अगर (venc.type == OMAP_DSS_VENC_TYPE_COMPOSITE)
		l |= 1 << 1;
	अन्यथा /* S-Video */
		l |= (1 << 0) | (1 << 2);

	अगर (venc.invert_polarity == false)
		l |= 1 << 3;

	venc_ग_लिखो_reg(VENC_OUTPUT_CONTROL, l);

	dss_mgr_set_timings(mgr, &venc.timings);

	r = regulator_enable(venc.vdda_dac_reg);
	अगर (r)
		जाओ err1;

	r = dss_mgr_enable(mgr);
	अगर (r)
		जाओ err2;

	वापस 0;

err2:
	regulator_disable(venc.vdda_dac_reg);
err1:
	venc_ग_लिखो_reg(VENC_OUTPUT_CONTROL, 0);
	dss_set_dac_pwrdn_bgz(0);

	venc_runसमय_put();
err0:
	वापस r;
पूर्ण

अटल व्योम venc_घातer_off(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_overlay_manager *mgr = venc.output.manager;

	venc_ग_लिखो_reg(VENC_OUTPUT_CONTROL, 0);
	dss_set_dac_pwrdn_bgz(0);

	dss_mgr_disable(mgr);

	regulator_disable(venc.vdda_dac_reg);

	venc_runसमय_put();
पूर्ण

अटल पूर्णांक venc_display_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_dss_device *out = &venc.output;
	पूर्णांक r;

	DSSDBG("venc_display_enable\n");

	mutex_lock(&venc.venc_lock);

	अगर (out->manager == शून्य) अणु
		DSSERR("Failed to enable display: no output/manager\n");
		r = -ENODEV;
		जाओ err0;
	पूर्ण

	r = venc_घातer_on(dssdev);
	अगर (r)
		जाओ err0;

	venc.wss_data = 0;

	mutex_unlock(&venc.venc_lock);

	वापस 0;
err0:
	mutex_unlock(&venc.venc_lock);
	वापस r;
पूर्ण

अटल व्योम venc_display_disable(काष्ठा omap_dss_device *dssdev)
अणु
	DSSDBG("venc_display_disable\n");

	mutex_lock(&venc.venc_lock);

	venc_घातer_off(dssdev);

	mutex_unlock(&venc.venc_lock);
पूर्ण

अटल व्योम venc_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	DSSDBG("venc_set_timings\n");

	mutex_lock(&venc.venc_lock);

	/* Reset WSS data when the TV standard changes. */
	अगर (स_भेद(&venc.timings, timings, माप(*timings)))
		venc.wss_data = 0;

	venc.timings = *timings;

	dispc_set_tv_pclk(13500000);

	mutex_unlock(&venc.venc_lock);
पूर्ण

अटल पूर्णांक venc_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	DSSDBG("venc_check_timings\n");

	अगर (स_भेद(&omap_dss_pal_timings, timings, माप(*timings)) == 0)
		वापस 0;

	अगर (स_भेद(&omap_dss_ntsc_timings, timings, माप(*timings)) == 0)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल व्योम venc_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	mutex_lock(&venc.venc_lock);

	*timings = venc.timings;

	mutex_unlock(&venc.venc_lock);
पूर्ण

अटल u32 venc_get_wss(काष्ठा omap_dss_device *dssdev)
अणु
	/* Invert due to VENC_L21_WC_CTL:INV=1 */
	वापस (venc.wss_data >> 8) ^ 0xfffff;
पूर्ण

अटल पूर्णांक venc_set_wss(काष्ठा omap_dss_device *dssdev, u32 wss)
अणु
	स्थिर काष्ठा venc_config *config;
	पूर्णांक r;

	DSSDBG("venc_set_wss\n");

	mutex_lock(&venc.venc_lock);

	config = venc_timings_to_config(&venc.timings);

	/* Invert due to VENC_L21_WC_CTL:INV=1 */
	venc.wss_data = (wss ^ 0xfffff) << 8;

	r = venc_runसमय_get();
	अगर (r)
		जाओ err;

	venc_ग_लिखो_reg(VENC_BSTAMP_WSS_DATA, config->bstamp_wss_data |
			venc.wss_data);

	venc_runसमय_put();

err:
	mutex_unlock(&venc.venc_lock);

	वापस r;
पूर्ण

अटल व्योम venc_set_type(काष्ठा omap_dss_device *dssdev,
		क्रमागत omap_dss_venc_type type)
अणु
	mutex_lock(&venc.venc_lock);

	venc.type = type;

	mutex_unlock(&venc.venc_lock);
पूर्ण

अटल व्योम venc_invert_vid_out_polarity(काष्ठा omap_dss_device *dssdev,
		bool invert_polarity)
अणु
	mutex_lock(&venc.venc_lock);

	venc.invert_polarity = invert_polarity;

	mutex_unlock(&venc.venc_lock);
पूर्ण

अटल पूर्णांक venc_init_regulator(व्योम)
अणु
	काष्ठा regulator *vdda_dac;

	अगर (venc.vdda_dac_reg != शून्य)
		वापस 0;

	अगर (venc.pdev->dev.of_node)
		vdda_dac = devm_regulator_get(&venc.pdev->dev, "vdda");
	अन्यथा
		vdda_dac = devm_regulator_get(&venc.pdev->dev, "vdda_dac");

	अगर (IS_ERR(vdda_dac)) अणु
		अगर (PTR_ERR(vdda_dac) != -EPROBE_DEFER)
			DSSERR("can't get VDDA_DAC regulator\n");
		वापस PTR_ERR(vdda_dac);
	पूर्ण

	venc.vdda_dac_reg = vdda_dac;

	वापस 0;
पूर्ण

अटल व्योम venc_dump_regs(काष्ठा seq_file *s)
अणु
#घोषणा DUMPREG(r) seq_म_लिखो(s, "%-35s %08x\n", #r, venc_पढ़ो_reg(r))

	अगर (venc_runसमय_get())
		वापस;

	DUMPREG(VENC_F_CONTROL);
	DUMPREG(VENC_VIDOUT_CTRL);
	DUMPREG(VENC_SYNC_CTRL);
	DUMPREG(VENC_LLEN);
	DUMPREG(VENC_FLENS);
	DUMPREG(VENC_HFLTR_CTRL);
	DUMPREG(VENC_CC_CARR_WSS_CARR);
	DUMPREG(VENC_C_PHASE);
	DUMPREG(VENC_GAIN_U);
	DUMPREG(VENC_GAIN_V);
	DUMPREG(VENC_GAIN_Y);
	DUMPREG(VENC_BLACK_LEVEL);
	DUMPREG(VENC_BLANK_LEVEL);
	DUMPREG(VENC_X_COLOR);
	DUMPREG(VENC_M_CONTROL);
	DUMPREG(VENC_BSTAMP_WSS_DATA);
	DUMPREG(VENC_S_CARR);
	DUMPREG(VENC_LINE21);
	DUMPREG(VENC_LN_SEL);
	DUMPREG(VENC_L21__WC_CTL);
	DUMPREG(VENC_HTRIGGER_VTRIGGER);
	DUMPREG(VENC_SAVID__EAVID);
	DUMPREG(VENC_FLEN__FAL);
	DUMPREG(VENC_LAL__PHASE_RESET);
	DUMPREG(VENC_HS_INT_START_STOP_X);
	DUMPREG(VENC_HS_EXT_START_STOP_X);
	DUMPREG(VENC_VS_INT_START_X);
	DUMPREG(VENC_VS_INT_STOP_X__VS_INT_START_Y);
	DUMPREG(VENC_VS_INT_STOP_Y__VS_EXT_START_X);
	DUMPREG(VENC_VS_EXT_STOP_X__VS_EXT_START_Y);
	DUMPREG(VENC_VS_EXT_STOP_Y);
	DUMPREG(VENC_AVID_START_STOP_X);
	DUMPREG(VENC_AVID_START_STOP_Y);
	DUMPREG(VENC_FID_INT_START_X__FID_INT_START_Y);
	DUMPREG(VENC_FID_INT_OFFSET_Y__FID_EXT_START_X);
	DUMPREG(VENC_FID_EXT_START_Y__FID_EXT_OFFSET_Y);
	DUMPREG(VENC_TVDETGP_INT_START_STOP_X);
	DUMPREG(VENC_TVDETGP_INT_START_STOP_Y);
	DUMPREG(VENC_GEN_CTRL);
	DUMPREG(VENC_OUTPUT_CONTROL);
	DUMPREG(VENC_OUTPUT_TEST);

	venc_runसमय_put();

#अघोषित DUMPREG
पूर्ण

अटल पूर्णांक venc_get_घड़ीs(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *clk;

	अगर (dss_has_feature(FEAT_VENC_REQUIRES_TV_DAC_CLK)) अणु
		clk = devm_clk_get(&pdev->dev, "tv_dac_clk");
		अगर (IS_ERR(clk)) अणु
			DSSERR("can't get tv_dac_clk\n");
			वापस PTR_ERR(clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		clk = शून्य;
	पूर्ण

	venc.tv_dac_clk = clk;

	वापस 0;
पूर्ण

अटल पूर्णांक venc_connect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा omap_overlay_manager *mgr;
	पूर्णांक r;

	r = venc_init_regulator();
	अगर (r)
		वापस r;

	mgr = omap_dss_get_overlay_manager(dssdev->dispc_channel);
	अगर (!mgr)
		वापस -ENODEV;

	r = dss_mgr_connect(mgr, dssdev);
	अगर (r)
		वापस r;

	r = omapdss_output_set_device(dssdev, dst);
	अगर (r) अणु
		DSSERR("failed to connect output to new device: %s\n",
				dst->name);
		dss_mgr_disconnect(mgr, dssdev);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम venc_disconnect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	WARN_ON(dst != dssdev->dst);

	अगर (dst != dssdev->dst)
		वापस;

	omapdss_output_unset_device(dssdev);

	अगर (dssdev->manager)
		dss_mgr_disconnect(dssdev->manager, dssdev);
पूर्ण

अटल स्थिर काष्ठा omapdss_atv_ops venc_ops = अणु
	.connect = venc_connect,
	.disconnect = venc_disconnect,

	.enable = venc_display_enable,
	.disable = venc_display_disable,

	.check_timings = venc_check_timings,
	.set_timings = venc_set_timings,
	.get_timings = venc_get_timings,

	.set_type = venc_set_type,
	.invert_vid_out_polarity = venc_invert_vid_out_polarity,

	.set_wss = venc_set_wss,
	.get_wss = venc_get_wss,
पूर्ण;

अटल व्योम venc_init_output(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *out = &venc.output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_VENC;
	out->output_type = OMAP_DISPLAY_TYPE_VENC;
	out->name = "venc.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_DIGIT;
	out->ops.atv = &venc_ops;
	out->owner = THIS_MODULE;

	omapdss_रेजिस्टर_output(out);
पूर्ण

अटल व्योम venc_uninit_output(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *out = &venc.output;

	omapdss_unरेजिस्टर_output(out);
पूर्ण

अटल पूर्णांक venc_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *ep;
	u32 channels;
	पूर्णांक r;

	ep = omapdss_of_get_first_endpoपूर्णांक(node);
	अगर (!ep)
		वापस 0;

	venc.invert_polarity = of_property_पढ़ो_bool(ep, "ti,invert-polarity");

	r = of_property_पढ़ो_u32(ep, "ti,channels", &channels);
	अगर (r) अणु
		dev_err(&pdev->dev,
			"failed to read property 'ti,channels': %d\n", r);
		जाओ err;
	पूर्ण

	चयन (channels) अणु
	हाल 1:
		venc.type = OMAP_DSS_VENC_TYPE_COMPOSITE;
		अवरोध;
	हाल 2:
		venc.type = OMAP_DSS_VENC_TYPE_SVIDEO;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "bad channel property '%d'\n", channels);
		r = -EINVAL;
		जाओ err;
	पूर्ण

	of_node_put(ep);

	वापस 0;
err:
	of_node_put(ep);

	वापस 0;
पूर्ण

/* VENC HW IP initialisation */
अटल पूर्णांक venc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	u8 rev_id;
	काष्ठा resource *venc_mem;
	पूर्णांक r;

	venc.pdev = pdev;

	mutex_init(&venc.venc_lock);

	venc.wss_data = 0;

	venc_mem = platक्रमm_get_resource(venc.pdev, IORESOURCE_MEM, 0);
	अगर (!venc_mem) अणु
		DSSERR("can't get IORESOURCE_MEM VENC\n");
		वापस -EINVAL;
	पूर्ण

	venc.base = devm_ioremap(&pdev->dev, venc_mem->start,
				 resource_size(venc_mem));
	अगर (!venc.base) अणु
		DSSERR("can't ioremap VENC\n");
		वापस -ENOMEM;
	पूर्ण

	r = venc_get_घड़ीs(pdev);
	अगर (r)
		वापस r;

	pm_runसमय_enable(&pdev->dev);

	r = venc_runसमय_get();
	अगर (r)
		जाओ err_runसमय_get;

	rev_id = (u8)(venc_पढ़ो_reg(VENC_REV_ID) & 0xff);
	dev_dbg(&pdev->dev, "OMAP VENC rev %d\n", rev_id);

	venc_runसमय_put();

	अगर (pdev->dev.of_node) अणु
		r = venc_probe_of(pdev);
		अगर (r) अणु
			DSSERR("Invalid DT data\n");
			जाओ err_probe_of;
		पूर्ण
	पूर्ण

	dss_debugfs_create_file("venc", venc_dump_regs);

	venc_init_output(pdev);

	वापस 0;

err_probe_of:
err_runसमय_get:
	pm_runसमय_disable(&pdev->dev);
	वापस r;
पूर्ण

अटल व्योम venc_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	venc_uninit_output(pdev);

	pm_runसमय_disable(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा component_ops venc_component_ops = अणु
	.bind	= venc_bind,
	.unbind	= venc_unbind,
पूर्ण;

अटल पूर्णांक venc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &venc_component_ops);
पूर्ण

अटल पूर्णांक venc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &venc_component_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक venc_runसमय_suspend(काष्ठा device *dev)
अणु
	clk_disable_unprepare(venc.tv_dac_clk);

	dispc_runसमय_put();

	वापस 0;
पूर्ण

अटल पूर्णांक venc_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक r;

	r = dispc_runसमय_get();
	अगर (r < 0)
		वापस r;

	clk_prepare_enable(venc.tv_dac_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops venc_pm_ops = अणु
	.runसमय_suspend = venc_runसमय_suspend,
	.runसमय_resume = venc_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id venc_of_match[] = अणु
	अणु .compatible = "ti,omap2-venc", पूर्ण,
	अणु .compatible = "ti,omap3-venc", पूर्ण,
	अणु .compatible = "ti,omap4-venc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver omap_venchw_driver = अणु
	.probe		= venc_probe,
	.हटाओ		= venc_हटाओ,
	.driver         = अणु
		.name   = "omapdss_venc",
		.pm	= &venc_pm_ops,
		.of_match_table = venc_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

पूर्णांक __init venc_init_platक्रमm_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_venchw_driver);
पूर्ण

व्योम venc_uninit_platक्रमm_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_venchw_driver);
पूर्ण
