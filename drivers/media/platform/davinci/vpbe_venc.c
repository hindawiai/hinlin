<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Texas Instruments Inc
 */
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/i2c-davinci.h>

#समावेश <linux/पन.स>

#समावेश <media/davinci/vpbe_types.h>
#समावेश <media/davinci/vpbe_venc.h>
#समावेश <media/davinci/vpss.h>
#समावेश <media/v4l2-device.h>

#समावेश "vpbe_venc_regs.h"

#घोषणा MODULE_NAME	"davinci-vpbe-venc"

अटल स्थिर काष्ठा platक्रमm_device_id vpbe_venc_devtype[] = अणु
	अणु
		.name = DM644X_VPBE_VENC_SUBDEV_NAME,
		.driver_data = VPBE_VERSION_1,
	पूर्ण, अणु
		.name = DM365_VPBE_VENC_SUBDEV_NAME,
		.driver_data = VPBE_VERSION_2,
	पूर्ण, अणु
		.name = DM355_VPBE_VENC_SUBDEV_NAME,
		.driver_data = VPBE_VERSION_3,
	पूर्ण,
	अणु
		/* sentinel */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, vpbe_venc_devtype);

अटल पूर्णांक debug = 2;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level 0-2");

काष्ठा venc_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा venc_callback *callback;
	काष्ठा venc_platक्रमm_data *pdata;
	काष्ठा device *pdev;
	u32 output;
	v4l2_std_id std;
	spinlock_t lock;
	व्योम __iomem *venc_base;
	व्योम __iomem *vdaccfg_reg;
	क्रमागत vpbe_version venc_type;
पूर्ण;

अटल अंतरभूत काष्ठा venc_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा venc_state, sd);
पूर्ण

अटल अंतरभूत u32 venc_पढ़ो(काष्ठा v4l2_subdev *sd, u32 offset)
अणु
	काष्ठा venc_state *venc = to_state(sd);

	वापस पढ़ोl(venc->venc_base + offset);
पूर्ण

अटल अंतरभूत u32 venc_ग_लिखो(काष्ठा v4l2_subdev *sd, u32 offset, u32 val)
अणु
	काष्ठा venc_state *venc = to_state(sd);

	ग_लिखोl(val, (venc->venc_base + offset));

	वापस val;
पूर्ण

अटल अंतरभूत u32 venc_modअगरy(काष्ठा v4l2_subdev *sd, u32 offset,
				 u32 val, u32 mask)
अणु
	u32 new_val = (venc_पढ़ो(sd, offset) & ~mask) | (val & mask);

	venc_ग_लिखो(sd, offset, new_val);

	वापस new_val;
पूर्ण

अटल अंतरभूत u32 vdaccfg_ग_लिखो(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा venc_state *venc = to_state(sd);

	ग_लिखोl(val, venc->vdaccfg_reg);

	val = पढ़ोl(venc->vdaccfg_reg);

	वापस val;
पूर्ण

#घोषणा VDAC_COMPONENT	0x543
#घोषणा VDAC_S_VIDEO	0x210
/* This function sets the dac of the VPBE क्रम various outमाला_दो
 */
अटल पूर्णांक venc_set_dac(काष्ठा v4l2_subdev *sd, u32 out_index)
अणु
	चयन (out_index) अणु
	हाल 0:
		v4l2_dbg(debug, 1, sd, "Setting output to Composite\n");
		venc_ग_लिखो(sd, VENC_DACSEL, 0);
		अवरोध;
	हाल 1:
		v4l2_dbg(debug, 1, sd, "Setting output to Component\n");
		venc_ग_लिखो(sd, VENC_DACSEL, VDAC_COMPONENT);
		अवरोध;
	हाल 2:
		v4l2_dbg(debug, 1, sd, "Setting output to S-video\n");
		venc_ग_लिखो(sd, VENC_DACSEL, VDAC_S_VIDEO);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम venc_enabledigitaloutput(काष्ठा v4l2_subdev *sd, पूर्णांक benable)
अणु
	काष्ठा venc_state *venc = to_state(sd);

	v4l2_dbg(debug, 2, sd, "venc_enabledigitaloutput\n");

	अगर (benable) अणु
		venc_ग_लिखो(sd, VENC_VMOD, 0);
		venc_ग_लिखो(sd, VENC_CVBS, 0);
		venc_ग_लिखो(sd, VENC_LCDOUT, 0);
		venc_ग_लिखो(sd, VENC_HSPLS, 0);
		venc_ग_लिखो(sd, VENC_HSTART, 0);
		venc_ग_लिखो(sd, VENC_HVALID, 0);
		venc_ग_लिखो(sd, VENC_HINT, 0);
		venc_ग_लिखो(sd, VENC_VSPLS, 0);
		venc_ग_लिखो(sd, VENC_VSTART, 0);
		venc_ग_लिखो(sd, VENC_VVALID, 0);
		venc_ग_लिखो(sd, VENC_VINT, 0);
		venc_ग_लिखो(sd, VENC_YCCCTL, 0);
		venc_ग_लिखो(sd, VENC_DACSEL, 0);

	पूर्ण अन्यथा अणु
		venc_ग_लिखो(sd, VENC_VMOD, 0);
		/* disable VCLK output pin enable */
		venc_ग_लिखो(sd, VENC_VIDCTL, 0x141);

		/* Disable output sync pins */
		venc_ग_लिखो(sd, VENC_SYNCCTL, 0);

		/* Disable DCLOCK */
		venc_ग_लिखो(sd, VENC_DCLKCTL, 0);
		venc_ग_लिखो(sd, VENC_DRGBX1, 0x0000057C);

		/* Disable LCD output control (accepting शेष polarity) */
		venc_ग_लिखो(sd, VENC_LCDOUT, 0);
		अगर (venc->venc_type != VPBE_VERSION_3)
			venc_ग_लिखो(sd, VENC_CMPNT, 0x100);
		venc_ग_लिखो(sd, VENC_HSPLS, 0);
		venc_ग_लिखो(sd, VENC_HINT, 0);
		venc_ग_लिखो(sd, VENC_HSTART, 0);
		venc_ग_लिखो(sd, VENC_HVALID, 0);

		venc_ग_लिखो(sd, VENC_VSPLS, 0);
		venc_ग_लिखो(sd, VENC_VINT, 0);
		venc_ग_लिखो(sd, VENC_VSTART, 0);
		venc_ग_लिखो(sd, VENC_VVALID, 0);

		venc_ग_लिखो(sd, VENC_HSDLY, 0);
		venc_ग_लिखो(sd, VENC_VSDLY, 0);

		venc_ग_लिखो(sd, VENC_YCCCTL, 0);
		venc_ग_लिखो(sd, VENC_VSTARTA, 0);

		/* Set OSD घड़ी and OSD Sync Adavance रेजिस्टरs */
		venc_ग_लिखो(sd, VENC_OSDCLK0, 1);
		venc_ग_लिखो(sd, VENC_OSDCLK1, 2);
	पूर्ण
पूर्ण

अटल व्योम
venc_enable_vpss_घड़ी(पूर्णांक venc_type,
		       क्रमागत vpbe_enc_timings_type type,
		       अचिन्हित पूर्णांक pघड़ी)
अणु
	अगर (venc_type == VPBE_VERSION_1)
		वापस;

	अगर (venc_type == VPBE_VERSION_2 && (type == VPBE_ENC_STD || (type ==
	    VPBE_ENC_DV_TIMINGS && pघड़ी <= 27000000))) अणु
		vpss_enable_घड़ी(VPSS_VENC_CLOCK_SEL, 1);
		vpss_enable_घड़ी(VPSS_VPBE_CLOCK, 1);
		वापस;
	पूर्ण

	अगर (venc_type == VPBE_VERSION_3 && type == VPBE_ENC_STD)
		vpss_enable_घड़ी(VPSS_VENC_CLOCK_SEL, 0);
पूर्ण

#घोषणा VDAC_CONFIG_SD_V3	0x0E21A6B6
#घोषणा VDAC_CONFIG_SD_V2	0x081141CF
/*
 * setting NTSC mode
 */
अटल पूर्णांक venc_set_ntsc(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा venc_state *venc = to_state(sd);
	काष्ठा venc_platक्रमm_data *pdata = venc->pdata;

	v4l2_dbg(debug, 2, sd, "venc_set_ntsc\n");

	/* Setup घड़ी at VPSS & VENC क्रम SD */
	vpss_enable_घड़ी(VPSS_VENC_CLOCK_SEL, 1);
	अगर (pdata->setup_घड़ी(VPBE_ENC_STD, V4L2_STD_525_60) < 0)
		वापस -EINVAL;

	venc_enable_vpss_घड़ी(venc->venc_type, VPBE_ENC_STD, V4L2_STD_525_60);
	venc_enabledigitaloutput(sd, 0);

	अगर (venc->venc_type == VPBE_VERSION_3) अणु
		venc_ग_लिखो(sd, VENC_CLKCTL, 0x01);
		venc_ग_लिखो(sd, VENC_VIDCTL, 0);
		vdaccfg_ग_लिखो(sd, VDAC_CONFIG_SD_V3);
	पूर्ण अन्यथा अगर (venc->venc_type == VPBE_VERSION_2) अणु
		venc_ग_लिखो(sd, VENC_CLKCTL, 0x01);
		venc_ग_लिखो(sd, VENC_VIDCTL, 0);
		vdaccfg_ग_लिखो(sd, VDAC_CONFIG_SD_V2);
	पूर्ण अन्यथा अणु
		/* to set VENC CLK DIV to 1 - final घड़ी is 54 MHz */
		venc_modअगरy(sd, VENC_VIDCTL, 0, 1 << 1);
		/* Set REC656 Mode */
		venc_ग_लिखो(sd, VENC_YCCCTL, 0x1);
		venc_modअगरy(sd, VENC_VDPRO, 0, VENC_VDPRO_DAFRQ);
		venc_modअगरy(sd, VENC_VDPRO, 0, VENC_VDPRO_DAUPS);
	पूर्ण

	venc_ग_लिखो(sd, VENC_VMOD, 0);
	venc_modअगरy(sd, VENC_VMOD, (1 << VENC_VMOD_VIE_SHIFT),
			VENC_VMOD_VIE);
	venc_modअगरy(sd, VENC_VMOD, (0 << VENC_VMOD_VMD), VENC_VMOD_VMD);
	venc_modअगरy(sd, VENC_VMOD, (0 << VENC_VMOD_TVTYP_SHIFT),
			VENC_VMOD_TVTYP);
	venc_ग_लिखो(sd, VENC_DACTST, 0x0);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);

	वापस 0;
पूर्ण

/*
 * setting PAL mode
 */
अटल पूर्णांक venc_set_pal(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा venc_state *venc = to_state(sd);

	v4l2_dbg(debug, 2, sd, "venc_set_pal\n");

	/* Setup घड़ी at VPSS & VENC क्रम SD */
	vpss_enable_घड़ी(VPSS_VENC_CLOCK_SEL, 1);
	अगर (venc->pdata->setup_घड़ी(VPBE_ENC_STD, V4L2_STD_625_50) < 0)
		वापस -EINVAL;

	venc_enable_vpss_घड़ी(venc->venc_type, VPBE_ENC_STD, V4L2_STD_625_50);
	venc_enabledigitaloutput(sd, 0);

	अगर (venc->venc_type == VPBE_VERSION_3) अणु
		venc_ग_लिखो(sd, VENC_CLKCTL, 0x1);
		venc_ग_लिखो(sd, VENC_VIDCTL, 0);
		vdaccfg_ग_लिखो(sd, VDAC_CONFIG_SD_V3);
	पूर्ण अन्यथा अगर (venc->venc_type == VPBE_VERSION_2) अणु
		venc_ग_लिखो(sd, VENC_CLKCTL, 0x1);
		venc_ग_लिखो(sd, VENC_VIDCTL, 0);
		vdaccfg_ग_लिखो(sd, VDAC_CONFIG_SD_V2);
	पूर्ण अन्यथा अणु
		/* to set VENC CLK DIV to 1 - final घड़ी is 54 MHz */
		venc_modअगरy(sd, VENC_VIDCTL, 0, 1 << 1);
		/* Set REC656 Mode */
		venc_ग_लिखो(sd, VENC_YCCCTL, 0x1);
	पूर्ण

	venc_modअगरy(sd, VENC_SYNCCTL, 1 << VENC_SYNCCTL_OVD_SHIFT,
			VENC_SYNCCTL_OVD);
	venc_ग_लिखो(sd, VENC_VMOD, 0);
	venc_modअगरy(sd, VENC_VMOD,
			(1 << VENC_VMOD_VIE_SHIFT),
			VENC_VMOD_VIE);
	venc_modअगरy(sd, VENC_VMOD,
			(0 << VENC_VMOD_VMD), VENC_VMOD_VMD);
	venc_modअगरy(sd, VENC_VMOD,
			(1 << VENC_VMOD_TVTYP_SHIFT),
			VENC_VMOD_TVTYP);
	venc_ग_लिखो(sd, VENC_DACTST, 0x0);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);

	वापस 0;
पूर्ण

#घोषणा VDAC_CONFIG_HD_V2	0x081141EF
/*
 * venc_set_480p59_94
 *
 * This function configures the video encoder to EDTV(525p) component setting.
 */
अटल पूर्णांक venc_set_480p59_94(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा venc_state *venc = to_state(sd);
	काष्ठा venc_platक्रमm_data *pdata = venc->pdata;

	v4l2_dbg(debug, 2, sd, "venc_set_480p59_94\n");
	अगर (venc->venc_type != VPBE_VERSION_1 &&
	    venc->venc_type != VPBE_VERSION_2)
		वापस -EINVAL;

	/* Setup घड़ी at VPSS & VENC क्रम SD */
	अगर (pdata->setup_घड़ी(VPBE_ENC_DV_TIMINGS, 27000000) < 0)
		वापस -EINVAL;

	venc_enable_vpss_घड़ी(venc->venc_type, VPBE_ENC_DV_TIMINGS, 27000000);
	venc_enabledigitaloutput(sd, 0);

	अगर (venc->venc_type == VPBE_VERSION_2)
		vdaccfg_ग_लिखो(sd, VDAC_CONFIG_HD_V2);
	venc_ग_लिखो(sd, VENC_OSDCLK0, 0);
	venc_ग_लिखो(sd, VENC_OSDCLK1, 1);

	अगर (venc->venc_type == VPBE_VERSION_1) अणु
		venc_modअगरy(sd, VENC_VDPRO, VENC_VDPRO_DAFRQ,
			    VENC_VDPRO_DAFRQ);
		venc_modअगरy(sd, VENC_VDPRO, VENC_VDPRO_DAUPS,
			    VENC_VDPRO_DAUPS);
	पूर्ण

	venc_ग_लिखो(sd, VENC_VMOD, 0);
	venc_modअगरy(sd, VENC_VMOD, (1 << VENC_VMOD_VIE_SHIFT),
		    VENC_VMOD_VIE);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_HDMD, VENC_VMOD_HDMD);
	venc_modअगरy(sd, VENC_VMOD, (HDTV_525P << VENC_VMOD_TVTYP_SHIFT),
		    VENC_VMOD_TVTYP);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_VDMD_YCBCR8 <<
		    VENC_VMOD_VDMD_SHIFT, VENC_VMOD_VDMD);

	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);

	वापस 0;
पूर्ण

/*
 * venc_set_625p
 *
 * This function configures the video encoder to HDTV(625p) component setting
 */
अटल पूर्णांक venc_set_576p50(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा venc_state *venc = to_state(sd);
	काष्ठा venc_platक्रमm_data *pdata = venc->pdata;

	v4l2_dbg(debug, 2, sd, "venc_set_576p50\n");

	अगर (venc->venc_type != VPBE_VERSION_1 &&
	    venc->venc_type != VPBE_VERSION_2)
		वापस -EINVAL;
	/* Setup घड़ी at VPSS & VENC क्रम SD */
	अगर (pdata->setup_घड़ी(VPBE_ENC_DV_TIMINGS, 27000000) < 0)
		वापस -EINVAL;

	venc_enable_vpss_घड़ी(venc->venc_type, VPBE_ENC_DV_TIMINGS, 27000000);
	venc_enabledigitaloutput(sd, 0);

	अगर (venc->venc_type == VPBE_VERSION_2)
		vdaccfg_ग_लिखो(sd, VDAC_CONFIG_HD_V2);

	venc_ग_लिखो(sd, VENC_OSDCLK0, 0);
	venc_ग_लिखो(sd, VENC_OSDCLK1, 1);

	अगर (venc->venc_type == VPBE_VERSION_1) अणु
		venc_modअगरy(sd, VENC_VDPRO, VENC_VDPRO_DAFRQ,
			    VENC_VDPRO_DAFRQ);
		venc_modअगरy(sd, VENC_VDPRO, VENC_VDPRO_DAUPS,
			    VENC_VDPRO_DAUPS);
	पूर्ण

	venc_ग_लिखो(sd, VENC_VMOD, 0);
	venc_modअगरy(sd, VENC_VMOD, (1 << VENC_VMOD_VIE_SHIFT),
		    VENC_VMOD_VIE);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_HDMD, VENC_VMOD_HDMD);
	venc_modअगरy(sd, VENC_VMOD, (HDTV_625P << VENC_VMOD_TVTYP_SHIFT),
		    VENC_VMOD_TVTYP);

	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_VDMD_YCBCR8 <<
		    VENC_VMOD_VDMD_SHIFT, VENC_VMOD_VDMD);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);

	वापस 0;
पूर्ण

/*
 * venc_set_720p60_पूर्णांकernal - Setup 720p60 in venc क्रम dm365 only
 */
अटल पूर्णांक venc_set_720p60_पूर्णांकernal(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा venc_state *venc = to_state(sd);
	काष्ठा venc_platक्रमm_data *pdata = venc->pdata;

	अगर (pdata->setup_घड़ी(VPBE_ENC_DV_TIMINGS, 74250000) < 0)
		वापस -EINVAL;

	venc_enable_vpss_घड़ी(venc->venc_type, VPBE_ENC_DV_TIMINGS, 74250000);
	venc_enabledigitaloutput(sd, 0);

	venc_ग_लिखो(sd, VENC_OSDCLK0, 0);
	venc_ग_लिखो(sd, VENC_OSDCLK1, 1);

	venc_ग_लिखो(sd, VENC_VMOD, 0);
	/* DM365 component HD mode */
	venc_modअगरy(sd, VENC_VMOD, (1 << VENC_VMOD_VIE_SHIFT),
	    VENC_VMOD_VIE);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_HDMD, VENC_VMOD_HDMD);
	venc_modअगरy(sd, VENC_VMOD, (HDTV_720P << VENC_VMOD_TVTYP_SHIFT),
		    VENC_VMOD_TVTYP);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);
	venc_ग_लिखो(sd, VENC_XHINTVL, 0);
	वापस 0;
पूर्ण

/*
 * venc_set_1080i30_पूर्णांकernal - Setup 1080i30 in venc क्रम dm365 only
 */
अटल पूर्णांक venc_set_1080i30_पूर्णांकernal(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा venc_state *venc = to_state(sd);
	काष्ठा venc_platक्रमm_data *pdata = venc->pdata;

	अगर (pdata->setup_घड़ी(VPBE_ENC_DV_TIMINGS, 74250000) < 0)
		वापस -EINVAL;

	venc_enable_vpss_घड़ी(venc->venc_type, VPBE_ENC_DV_TIMINGS, 74250000);
	venc_enabledigitaloutput(sd, 0);

	venc_ग_लिखो(sd, VENC_OSDCLK0, 0);
	venc_ग_लिखो(sd, VENC_OSDCLK1, 1);


	venc_ग_लिखो(sd, VENC_VMOD, 0);
	/* DM365 component HD mode */
	venc_modअगरy(sd, VENC_VMOD, (1 << VENC_VMOD_VIE_SHIFT),
		    VENC_VMOD_VIE);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_HDMD, VENC_VMOD_HDMD);
	venc_modअगरy(sd, VENC_VMOD, (HDTV_1080I << VENC_VMOD_TVTYP_SHIFT),
		    VENC_VMOD_TVTYP);
	venc_modअगरy(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);
	venc_ग_लिखो(sd, VENC_XHINTVL, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक venc_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	v4l2_dbg(debug, 1, sd, "venc_s_std_output\n");

	अगर (norm & V4L2_STD_525_60)
		वापस venc_set_ntsc(sd);
	अन्यथा अगर (norm & V4L2_STD_625_50)
		वापस venc_set_pal(sd);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक venc_s_dv_timings(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_dv_timings *dv_timings)
अणु
	काष्ठा venc_state *venc = to_state(sd);
	u32 height = dv_timings->bt.height;
	पूर्णांक ret;

	v4l2_dbg(debug, 1, sd, "venc_s_dv_timings\n");

	अगर (height == 576)
		वापस venc_set_576p50(sd);
	अन्यथा अगर (height == 480)
		वापस venc_set_480p59_94(sd);
	अन्यथा अगर ((height == 720) &&
			(venc->venc_type == VPBE_VERSION_2)) अणु
		/* TBD setup पूर्णांकernal 720p mode here */
		ret = venc_set_720p60_पूर्णांकernal(sd);
		/* क्रम DM365 VPBE, there is DAC inside */
		vdaccfg_ग_लिखो(sd, VDAC_CONFIG_HD_V2);
		वापस ret;
	पूर्ण अन्यथा अगर ((height == 1080) &&
		(venc->venc_type == VPBE_VERSION_2)) अणु
		/* TBD setup पूर्णांकernal 1080i mode here */
		ret = venc_set_1080i30_पूर्णांकernal(sd);
		/* क्रम DM365 VPBE, there is DAC inside */
		vdaccfg_ग_लिखो(sd, VDAC_CONFIG_HD_V2);
		वापस ret;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक venc_s_routing(काष्ठा v4l2_subdev *sd, u32 input, u32 output,
			  u32 config)
अणु
	काष्ठा venc_state *venc = to_state(sd);
	पूर्णांक ret;

	v4l2_dbg(debug, 1, sd, "venc_s_routing\n");

	ret = venc_set_dac(sd, output);
	अगर (!ret)
		venc->output = output;

	वापस ret;
पूर्ण

अटल दीर्घ venc_ioctl(काष्ठा v4l2_subdev *sd,
			अचिन्हित पूर्णांक cmd,
			व्योम *arg)
अणु
	u32 val;

	चयन (cmd) अणु
	हाल VENC_GET_FLD:
		val = venc_पढ़ो(sd, VENC_VSTAT);
		*((पूर्णांक *)arg) = ((val & VENC_VSTAT_FIDST) ==
		VENC_VSTAT_FIDST);
		अवरोध;
	शेष:
		v4l2_err(sd, "Wrong IOCTL cmd\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops venc_core_ops = अणु
	.ioctl      = venc_ioctl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops venc_video_ops = अणु
	.s_routing = venc_s_routing,
	.s_std_output = venc_s_std_output,
	.s_dv_timings = venc_s_dv_timings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops venc_ops = अणु
	.core = &venc_core_ops,
	.video = &venc_video_ops,
पूर्ण;

अटल पूर्णांक venc_initialize(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा venc_state *venc = to_state(sd);
	पूर्णांक ret;

	/* Set शेष to output to composite and std to NTSC */
	venc->output = 0;
	venc->std = V4L2_STD_525_60;

	ret = venc_s_routing(sd, 0, venc->output, 0);
	अगर (ret < 0) अणु
		v4l2_err(sd, "Error setting output during init\n");
		वापस -EINVAL;
	पूर्ण

	ret = venc_s_std_output(sd, venc->std);
	अगर (ret < 0) अणु
		v4l2_err(sd, "Error setting std during init\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक venc_device_get(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा venc_state **venc = data;

	अगर (म_माला(pdev->name, "vpbe-venc") != शून्य)
		*venc = platक्रमm_get_drvdata(pdev);

	वापस 0;
पूर्ण

काष्ठा v4l2_subdev *venc_sub_dev_init(काष्ठा v4l2_device *v4l2_dev,
		स्थिर अक्षर *venc_name)
अणु
	काष्ठा venc_state *venc = शून्य;

	bus_क्रम_each_dev(&platक्रमm_bus_type, शून्य, &venc,
			venc_device_get);
	अगर (venc == शून्य)
		वापस शून्य;

	v4l2_subdev_init(&venc->sd, &venc_ops);

	strscpy(venc->sd.name, venc_name, माप(venc->sd.name));
	अगर (v4l2_device_रेजिस्टर_subdev(v4l2_dev, &venc->sd) < 0) अणु
		v4l2_err(v4l2_dev,
			"vpbe unable to register venc sub device\n");
		वापस शून्य;
	पूर्ण
	अगर (venc_initialize(&venc->sd)) अणु
		v4l2_err(v4l2_dev,
			"vpbe venc initialization failed\n");
		वापस शून्य;
	पूर्ण

	वापस &venc->sd;
पूर्ण
EXPORT_SYMBOL(venc_sub_dev_init);

अटल पूर्णांक venc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *pdev_id;
	काष्ठा venc_state *venc;
	काष्ठा resource *res;

	अगर (!pdev->dev.platक्रमm_data) अणु
		dev_err(&pdev->dev, "No platform data for VENC sub device");
		वापस -EINVAL;
	पूर्ण

	pdev_id = platक्रमm_get_device_id(pdev);
	अगर (!pdev_id)
		वापस -EINVAL;

	venc = devm_kzalloc(&pdev->dev, माप(काष्ठा venc_state), GFP_KERNEL);
	अगर (venc == शून्य)
		वापस -ENOMEM;

	venc->venc_type = pdev_id->driver_data;
	venc->pdev = &pdev->dev;
	venc->pdata = pdev->dev.platक्रमm_data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	venc->venc_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(venc->venc_base))
		वापस PTR_ERR(venc->venc_base);

	अगर (venc->venc_type != VPBE_VERSION_1) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);

		venc->vdaccfg_reg = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(venc->vdaccfg_reg))
			वापस PTR_ERR(venc->vdaccfg_reg);
	पूर्ण
	spin_lock_init(&venc->lock);
	platक्रमm_set_drvdata(pdev, venc);
	dev_notice(venc->pdev, "VENC sub device probe success\n");

	वापस 0;
पूर्ण

अटल पूर्णांक venc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver venc_driver = अणु
	.probe		= venc_probe,
	.हटाओ		= venc_हटाओ,
	.driver		= अणु
		.name	= MODULE_NAME,
	पूर्ण,
	.id_table	= vpbe_venc_devtype
पूर्ण;

module_platक्रमm_driver(venc_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VPBE VENC Driver");
MODULE_AUTHOR("Texas Instruments");
