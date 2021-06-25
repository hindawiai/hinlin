<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Vincent Abriou <vincent.abriou@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "sti_crtc.h"
#समावेश "sti_drv.h"
#समावेश "sti_vtg.h"

/* glue रेजिस्टरs */
#घोषणा TVO_CSC_MAIN_M0                  0x000
#घोषणा TVO_CSC_MAIN_M1                  0x004
#घोषणा TVO_CSC_MAIN_M2                  0x008
#घोषणा TVO_CSC_MAIN_M3                  0x00c
#घोषणा TVO_CSC_MAIN_M4                  0x010
#घोषणा TVO_CSC_MAIN_M5                  0x014
#घोषणा TVO_CSC_MAIN_M6                  0x018
#घोषणा TVO_CSC_MAIN_M7                  0x01c
#घोषणा TVO_MAIN_IN_VID_FORMAT           0x030
#घोषणा TVO_CSC_AUX_M0                   0x100
#घोषणा TVO_CSC_AUX_M1                   0x104
#घोषणा TVO_CSC_AUX_M2                   0x108
#घोषणा TVO_CSC_AUX_M3                   0x10c
#घोषणा TVO_CSC_AUX_M4                   0x110
#घोषणा TVO_CSC_AUX_M5                   0x114
#घोषणा TVO_CSC_AUX_M6                   0x118
#घोषणा TVO_CSC_AUX_M7                   0x11c
#घोषणा TVO_AUX_IN_VID_FORMAT            0x130
#घोषणा TVO_VIP_HDF                      0x400
#घोषणा TVO_HD_SYNC_SEL                  0x418
#घोषणा TVO_HD_DAC_CFG_OFF               0x420
#घोषणा TVO_VIP_HDMI                     0x500
#घोषणा TVO_HDMI_FORCE_COLOR_0           0x504
#घोषणा TVO_HDMI_FORCE_COLOR_1           0x508
#घोषणा TVO_HDMI_CLIP_VALUE_B_CB         0x50c
#घोषणा TVO_HDMI_CLIP_VALUE_Y_G          0x510
#घोषणा TVO_HDMI_CLIP_VALUE_R_CR         0x514
#घोषणा TVO_HDMI_SYNC_SEL                0x518
#घोषणा TVO_HDMI_DFV_OBS                 0x540
#घोषणा TVO_VIP_DVO                      0x600
#घोषणा TVO_DVO_SYNC_SEL                 0x618
#घोषणा TVO_DVO_CONFIG                   0x620

#घोषणा TVO_IN_FMT_SIGNED                BIT(0)
#घोषणा TVO_SYNC_EXT                     BIT(4)

#घोषणा TVO_VIP_REORDER_R_SHIFT          24
#घोषणा TVO_VIP_REORDER_G_SHIFT          20
#घोषणा TVO_VIP_REORDER_B_SHIFT          16
#घोषणा TVO_VIP_REORDER_MASK             0x3
#घोषणा TVO_VIP_REORDER_Y_G_SEL          0
#घोषणा TVO_VIP_REORDER_CB_B_SEL         1
#घोषणा TVO_VIP_REORDER_CR_R_SEL         2

#घोषणा TVO_VIP_CLIP_SHIFT               8
#घोषणा TVO_VIP_CLIP_MASK                0x7
#घोषणा TVO_VIP_CLIP_DISABLED            0
#घोषणा TVO_VIP_CLIP_EAV_SAV             1
#घोषणा TVO_VIP_CLIP_LIMITED_RANGE_RGB_Y 2
#घोषणा TVO_VIP_CLIP_LIMITED_RANGE_CB_CR 3
#घोषणा TVO_VIP_CLIP_PROG_RANGE          4

#घोषणा TVO_VIP_RND_SHIFT                4
#घोषणा TVO_VIP_RND_MASK                 0x3
#घोषणा TVO_VIP_RND_8BIT_ROUNDED         0
#घोषणा TVO_VIP_RND_10BIT_ROUNDED        1
#घोषणा TVO_VIP_RND_12BIT_ROUNDED        2

#घोषणा TVO_VIP_SEL_INPUT_MASK           0xf
#घोषणा TVO_VIP_SEL_INPUT_MAIN           0x0
#घोषणा TVO_VIP_SEL_INPUT_AUX            0x8
#घोषणा TVO_VIP_SEL_INPUT_FORCE_COLOR    0xf
#घोषणा TVO_VIP_SEL_INPUT_BYPASS_MASK    0x1
#घोषणा TVO_VIP_SEL_INPUT_BYPASSED       1

#घोषणा TVO_SYNC_MAIN_VTG_SET_REF        0x00
#घोषणा TVO_SYNC_AUX_VTG_SET_REF         0x10

#घोषणा TVO_SYNC_HD_DCS_SHIFT            8

#घोषणा TVO_SYNC_DVO_PAD_HSYNC_SHIFT     8
#घोषणा TVO_SYNC_DVO_PAD_VSYNC_SHIFT     16

#घोषणा ENCODER_CRTC_MASK                (BIT(0) | BIT(1))

#घोषणा TVO_MIN_HD_HEIGHT                720

/* क्रमागत listing the supported output data क्रमmat */
क्रमागत sti_tvout_video_out_type अणु
	STI_TVOUT_VIDEO_OUT_RGB,
	STI_TVOUT_VIDEO_OUT_YUV,
पूर्ण;

काष्ठा sti_tvout अणु
	काष्ठा device *dev;
	काष्ठा drm_device *drm_dev;
	व्योम __iomem *regs;
	काष्ठा reset_control *reset;
	काष्ठा drm_encoder *hdmi;
	काष्ठा drm_encoder *hda;
	काष्ठा drm_encoder *dvo;
	bool debugfs_रेजिस्टरed;
पूर्ण;

काष्ठा sti_tvout_encoder अणु
	काष्ठा drm_encoder encoder;
	काष्ठा sti_tvout *tvout;
पूर्ण;

#घोषणा to_sti_tvout_encoder(x) \
	container_of(x, काष्ठा sti_tvout_encoder, encoder)

#घोषणा to_sti_tvout(x) to_sti_tvout_encoder(x)->tvout

/* preक्रमmatter conversion matrix */
अटल स्थिर u32 rgb_to_ycbcr_601[8] = अणु
	0xF927082E, 0x04C9FEAB, 0x01D30964, 0xFA95FD3D,
	0x0000082E, 0x00002000, 0x00002000, 0x00000000
पूर्ण;

/* 709 RGB to YCbCr */
अटल स्थिर u32 rgb_to_ycbcr_709[8] = अणु
	0xF891082F, 0x0367FF40, 0x01280B71, 0xF9B1FE20,
	0x0000082F, 0x00002000, 0x00002000, 0x00000000
पूर्ण;

अटल u32 tvout_पढ़ो(काष्ठा sti_tvout *tvout, पूर्णांक offset)
अणु
	वापस पढ़ोl(tvout->regs + offset);
पूर्ण

अटल व्योम tvout_ग_लिखो(काष्ठा sti_tvout *tvout, u32 val, पूर्णांक offset)
अणु
	ग_लिखोl(val, tvout->regs + offset);
पूर्ण

/**
 * Set the clipping mode of a VIP
 *
 * @tvout: tvout काष्ठाure
 * @reg: रेजिस्टर to set
 * @cr_r: red chroma or red order
 * @y_g: y or green order
 * @cb_b: blue chroma or blue order
 */
अटल व्योम tvout_vip_set_color_order(काष्ठा sti_tvout *tvout, पूर्णांक reg,
				      u32 cr_r, u32 y_g, u32 cb_b)
अणु
	u32 val = tvout_पढ़ो(tvout, reg);

	val &= ~(TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_R_SHIFT);
	val &= ~(TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_G_SHIFT);
	val &= ~(TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_B_SHIFT);
	val |= cr_r << TVO_VIP_REORDER_R_SHIFT;
	val |= y_g << TVO_VIP_REORDER_G_SHIFT;
	val |= cb_b << TVO_VIP_REORDER_B_SHIFT;

	tvout_ग_लिखो(tvout, val, reg);
पूर्ण

/**
 * Set the clipping mode of a VIP
 *
 * @tvout: tvout काष्ठाure
 * @reg: रेजिस्टर to set
 * @range: clipping range
 */
अटल व्योम tvout_vip_set_clip_mode(काष्ठा sti_tvout *tvout, पूर्णांक reg, u32 range)
अणु
	u32 val = tvout_पढ़ो(tvout, reg);

	val &= ~(TVO_VIP_CLIP_MASK << TVO_VIP_CLIP_SHIFT);
	val |= range << TVO_VIP_CLIP_SHIFT;
	tvout_ग_लिखो(tvout, val, reg);
पूर्ण

/**
 * Set the rounded value of a VIP
 *
 * @tvout: tvout काष्ठाure
 * @reg: रेजिस्टर to set
 * @rnd: rounded val per component
 */
अटल व्योम tvout_vip_set_rnd(काष्ठा sti_tvout *tvout, पूर्णांक reg, u32 rnd)
अणु
	u32 val = tvout_पढ़ो(tvout, reg);

	val &= ~(TVO_VIP_RND_MASK << TVO_VIP_RND_SHIFT);
	val |= rnd << TVO_VIP_RND_SHIFT;
	tvout_ग_लिखो(tvout, val, reg);
पूर्ण

/**
 * Select the VIP input
 *
 * @tvout: tvout काष्ठाure
 * @reg: रेजिस्टर to set
 * @मुख्य_path: मुख्य or auxiliary path
 * @video_out: selected_input (मुख्य/aux + conv)
 */
अटल व्योम tvout_vip_set_sel_input(काष्ठा sti_tvout *tvout,
				    पूर्णांक reg,
				    bool मुख्य_path,
				    क्रमागत sti_tvout_video_out_type video_out)
अणु
	u32 sel_input;
	u32 val = tvout_पढ़ो(tvout, reg);

	अगर (मुख्य_path)
		sel_input = TVO_VIP_SEL_INPUT_MAIN;
	अन्यथा
		sel_input = TVO_VIP_SEL_INPUT_AUX;

	चयन (video_out) अणु
	हाल STI_TVOUT_VIDEO_OUT_RGB:
		sel_input |= TVO_VIP_SEL_INPUT_BYPASSED;
		अवरोध;
	हाल STI_TVOUT_VIDEO_OUT_YUV:
		sel_input &= ~TVO_VIP_SEL_INPUT_BYPASSED;
		अवरोध;
	पूर्ण

	/* on stih407 chip the sel_input bypass mode logic is inverted */
	sel_input = sel_input ^ TVO_VIP_SEL_INPUT_BYPASS_MASK;

	val &= ~TVO_VIP_SEL_INPUT_MASK;
	val |= sel_input;
	tvout_ग_लिखो(tvout, val, reg);
पूर्ण

/**
 * Select the input video चिन्हित or अचिन्हित
 *
 * @tvout: tvout काष्ठाure
 * @reg: रेजिस्टर to set
 * @in_vid_fmt: used video input क्रमmat
 */
अटल व्योम tvout_vip_set_in_vid_fmt(काष्ठा sti_tvout *tvout,
		पूर्णांक reg, u32 in_vid_fmt)
अणु
	u32 val = tvout_पढ़ो(tvout, reg);

	val &= ~TVO_IN_FMT_SIGNED;
	val |= in_vid_fmt;
	tvout_ग_लिखो(tvout, val, reg);
पूर्ण

/**
 * Set preक्रमmatter matrix
 *
 * @tvout: tvout काष्ठाure
 * @mode: display mode काष्ठाure
 */
अटल व्योम tvout_preक्रमmatter_set_matrix(काष्ठा sti_tvout *tvout,
					  काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर u32 *pf_matrix;

	अगर (mode->vdisplay >= TVO_MIN_HD_HEIGHT)
		pf_matrix = rgb_to_ycbcr_709;
	अन्यथा
		pf_matrix = rgb_to_ycbcr_601;

	क्रम (i = 0; i < 8; i++) अणु
		tvout_ग_लिखो(tvout, *(pf_matrix + i),
			    TVO_CSC_MAIN_M0 + (i * 4));
		tvout_ग_लिखो(tvout, *(pf_matrix + i),
			    TVO_CSC_AUX_M0 + (i * 4));
	पूर्ण
पूर्ण

/**
 * Start VIP block क्रम DVO output
 *
 * @tvout: poपूर्णांकer on tvout काष्ठाure
 * @मुख्य_path: true अगर मुख्य path has to be used in the vip configuration
 *	  अन्यथा aux path is used.
 */
अटल व्योम tvout_dvo_start(काष्ठा sti_tvout *tvout, bool मुख्य_path)
अणु
	u32 tvo_in_vid_क्रमmat;
	पूर्णांक val, पंचांगp;

	dev_dbg(tvout->dev, "%s\n", __func__);

	अगर (मुख्य_path) अणु
		DRM_DEBUG_DRIVER("main vip for DVO\n");
		/* Select the input sync क्रम dvo */
		पंचांगp = TVO_SYNC_MAIN_VTG_SET_REF | VTG_SYNC_ID_DVO;
		val  = पंचांगp << TVO_SYNC_DVO_PAD_VSYNC_SHIFT;
		val |= पंचांगp << TVO_SYNC_DVO_PAD_HSYNC_SHIFT;
		val |= पंचांगp;
		tvout_ग_लिखो(tvout, val, TVO_DVO_SYNC_SEL);
		tvo_in_vid_क्रमmat = TVO_MAIN_IN_VID_FORMAT;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_DRIVER("aux vip for DVO\n");
		/* Select the input sync क्रम dvo */
		पंचांगp = TVO_SYNC_AUX_VTG_SET_REF | VTG_SYNC_ID_DVO;
		val  = पंचांगp << TVO_SYNC_DVO_PAD_VSYNC_SHIFT;
		val |= पंचांगp << TVO_SYNC_DVO_PAD_HSYNC_SHIFT;
		val |= पंचांगp;
		tvout_ग_लिखो(tvout, val, TVO_DVO_SYNC_SEL);
		tvo_in_vid_क्रमmat = TVO_AUX_IN_VID_FORMAT;
	पूर्ण

	/* Set color channel order */
	tvout_vip_set_color_order(tvout, TVO_VIP_DVO,
				  TVO_VIP_REORDER_CR_R_SEL,
				  TVO_VIP_REORDER_Y_G_SEL,
				  TVO_VIP_REORDER_CB_B_SEL);

	/* Set clipping mode */
	tvout_vip_set_clip_mode(tvout, TVO_VIP_DVO, TVO_VIP_CLIP_DISABLED);

	/* Set round mode (rounded to 8-bit per component) */
	tvout_vip_set_rnd(tvout, TVO_VIP_DVO, TVO_VIP_RND_8BIT_ROUNDED);

	/* Set input video क्रमmat */
	tvout_vip_set_in_vid_fmt(tvout, tvo_in_vid_क्रमmat, TVO_IN_FMT_SIGNED);

	/* Input selection */
	tvout_vip_set_sel_input(tvout, TVO_VIP_DVO, मुख्य_path,
				STI_TVOUT_VIDEO_OUT_RGB);
पूर्ण

/**
 * Start VIP block क्रम HDMI output
 *
 * @tvout: poपूर्णांकer on tvout काष्ठाure
 * @मुख्य_path: true अगर मुख्य path has to be used in the vip configuration
 *	  अन्यथा aux path is used.
 */
अटल व्योम tvout_hdmi_start(काष्ठा sti_tvout *tvout, bool मुख्य_path)
अणु
	u32 tvo_in_vid_क्रमmat;

	dev_dbg(tvout->dev, "%s\n", __func__);

	अगर (मुख्य_path) अणु
		DRM_DEBUG_DRIVER("main vip for hdmi\n");
		/* select the input sync क्रम hdmi */
		tvout_ग_लिखो(tvout,
			    TVO_SYNC_MAIN_VTG_SET_REF | VTG_SYNC_ID_HDMI,
			    TVO_HDMI_SYNC_SEL);
		tvo_in_vid_क्रमmat = TVO_MAIN_IN_VID_FORMAT;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_DRIVER("aux vip for hdmi\n");
		/* select the input sync क्रम hdmi */
		tvout_ग_लिखो(tvout,
			    TVO_SYNC_AUX_VTG_SET_REF | VTG_SYNC_ID_HDMI,
			    TVO_HDMI_SYNC_SEL);
		tvo_in_vid_क्रमmat = TVO_AUX_IN_VID_FORMAT;
	पूर्ण

	/* set color channel order */
	tvout_vip_set_color_order(tvout, TVO_VIP_HDMI,
				  TVO_VIP_REORDER_CR_R_SEL,
				  TVO_VIP_REORDER_Y_G_SEL,
				  TVO_VIP_REORDER_CB_B_SEL);

	/* set clipping mode */
	tvout_vip_set_clip_mode(tvout, TVO_VIP_HDMI, TVO_VIP_CLIP_DISABLED);

	/* set round mode (rounded to 8-bit per component) */
	tvout_vip_set_rnd(tvout, TVO_VIP_HDMI, TVO_VIP_RND_8BIT_ROUNDED);

	/* set input video क्रमmat */
	tvout_vip_set_in_vid_fmt(tvout, tvo_in_vid_क्रमmat, TVO_IN_FMT_SIGNED);

	/* input selection */
	tvout_vip_set_sel_input(tvout, TVO_VIP_HDMI, मुख्य_path,
				STI_TVOUT_VIDEO_OUT_RGB);
पूर्ण

/**
 * Start HDF VIP and HD DAC
 *
 * @tvout: poपूर्णांकer on tvout काष्ठाure
 * @मुख्य_path: true अगर मुख्य path has to be used in the vip configuration
 *	  अन्यथा aux path is used.
 */
अटल व्योम tvout_hda_start(काष्ठा sti_tvout *tvout, bool मुख्य_path)
अणु
	u32 tvo_in_vid_क्रमmat;
	पूर्णांक val;

	dev_dbg(tvout->dev, "%s\n", __func__);

	अगर (मुख्य_path) अणु
		DRM_DEBUG_DRIVER("main vip for HDF\n");
		/* Select the input sync क्रम HD analog and HD DCS */
		val  = TVO_SYNC_MAIN_VTG_SET_REF | VTG_SYNC_ID_HDDCS;
		val  = val << TVO_SYNC_HD_DCS_SHIFT;
		val |= TVO_SYNC_MAIN_VTG_SET_REF | VTG_SYNC_ID_HDF;
		tvout_ग_लिखो(tvout, val, TVO_HD_SYNC_SEL);
		tvo_in_vid_क्रमmat = TVO_MAIN_IN_VID_FORMAT;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_DRIVER("aux vip for HDF\n");
		/* Select the input sync क्रम HD analog and HD DCS */
		val  = TVO_SYNC_AUX_VTG_SET_REF | VTG_SYNC_ID_HDDCS;
		val  = val << TVO_SYNC_HD_DCS_SHIFT;
		val |= TVO_SYNC_AUX_VTG_SET_REF | VTG_SYNC_ID_HDF;
		tvout_ग_लिखो(tvout, val, TVO_HD_SYNC_SEL);
		tvo_in_vid_क्रमmat = TVO_AUX_IN_VID_FORMAT;
	पूर्ण

	/* set color channel order */
	tvout_vip_set_color_order(tvout, TVO_VIP_HDF,
				  TVO_VIP_REORDER_CR_R_SEL,
				  TVO_VIP_REORDER_Y_G_SEL,
				  TVO_VIP_REORDER_CB_B_SEL);

	/* set clipping mode */
	tvout_vip_set_clip_mode(tvout, TVO_VIP_HDF, TVO_VIP_CLIP_DISABLED);

	/* set round mode (rounded to 10-bit per component) */
	tvout_vip_set_rnd(tvout, TVO_VIP_HDF, TVO_VIP_RND_10BIT_ROUNDED);

	/* Set input video क्रमmat */
	tvout_vip_set_in_vid_fmt(tvout, tvo_in_vid_क्रमmat, TVO_IN_FMT_SIGNED);

	/* Input selection */
	tvout_vip_set_sel_input(tvout, TVO_VIP_HDF, मुख्य_path,
				STI_TVOUT_VIDEO_OUT_YUV);

	/* घातer up HD DAC */
	tvout_ग_लिखो(tvout, 0, TVO_HD_DAC_CFG_OFF);
पूर्ण

#घोषणा DBGFS_DUMP(reg) seq_म_लिखो(s, "\n  %-25s 0x%08X", #reg, \
				   पढ़ोl(tvout->regs + reg))

अटल व्योम tvout_dbg_vip(काष्ठा seq_file *s, पूर्णांक val)
अणु
	पूर्णांक r, g, b, पंचांगp, mask;
	अक्षर *स्थिर reorder[] = अणु"Y_G", "Cb_B", "Cr_R"पूर्ण;
	अक्षर *स्थिर clipping[] = अणु"No", "EAV/SAV", "Limited range RGB/Y",
				  "Limited range Cb/Cr", "decided by register"पूर्ण;
	अक्षर *स्थिर round[] = अणु"8-bit", "10-bit", "12-bit"पूर्ण;
	अक्षर *स्थिर input_sel[] = अणु"Main (color matrix enabled)",
				   "Main (color matrix by-passed)",
				   "", "", "", "", "", "",
				   "Aux (color matrix enabled)",
				   "Aux (color matrix by-passed)",
				   "", "", "", "", "", "Force value"पूर्ण;

	seq_अ_दो(s, '\t');
	mask = TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_R_SHIFT;
	r = (val & mask) >> TVO_VIP_REORDER_R_SHIFT;
	mask = TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_G_SHIFT;
	g = (val & mask) >> TVO_VIP_REORDER_G_SHIFT;
	mask = TVO_VIP_REORDER_MASK << TVO_VIP_REORDER_B_SHIFT;
	b = (val & mask) >> TVO_VIP_REORDER_B_SHIFT;
	seq_म_लिखो(s, "%-24s %s->%s %s->%s %s->%s\n", "Reorder:",
		   reorder[r], reorder[TVO_VIP_REORDER_CR_R_SEL],
		   reorder[g], reorder[TVO_VIP_REORDER_Y_G_SEL],
		   reorder[b], reorder[TVO_VIP_REORDER_CB_B_SEL]);
	seq_माला_दो(s, "\t\t\t\t\t");
	mask = TVO_VIP_CLIP_MASK << TVO_VIP_CLIP_SHIFT;
	पंचांगp = (val & mask) >> TVO_VIP_CLIP_SHIFT;
	seq_म_लिखो(s, "%-24s %s\n", "Clipping:", clipping[पंचांगp]);
	seq_माला_दो(s, "\t\t\t\t\t");
	mask = TVO_VIP_RND_MASK << TVO_VIP_RND_SHIFT;
	पंचांगp = (val & mask) >> TVO_VIP_RND_SHIFT;
	seq_म_लिखो(s, "%-24s input data rounded to %s per component\n",
		   "Round:", round[पंचांगp]);
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = (val & TVO_VIP_SEL_INPUT_MASK);
	seq_म_लिखो(s, "%-24s %s", "Input selection:", input_sel[पंचांगp]);
पूर्ण

अटल व्योम tvout_dbg_hd_dac_cfg(काष्ठा seq_file *s, पूर्णांक val)
अणु
	seq_म_लिखो(s, "\t%-24s %s", "HD DAC:",
		   val & 1 ? "disabled" : "enabled");
पूर्ण

अटल पूर्णांक tvout_dbg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_tvout *tvout = (काष्ठा sti_tvout *)node->info_ent->data;
	काष्ठा drm_crtc *crtc;

	seq_म_लिखो(s, "TVOUT: (vaddr = 0x%p)", tvout->regs);

	seq_माला_दो(s, "\n\n  HDMI encoder: ");
	crtc = tvout->hdmi->crtc;
	अगर (crtc) अणु
		seq_म_लिखो(s, "connected to %s path",
			   sti_crtc_is_मुख्य(crtc) ? "main" : "aux");
		DBGFS_DUMP(TVO_HDMI_SYNC_SEL);
		DBGFS_DUMP(TVO_VIP_HDMI);
		tvout_dbg_vip(s, पढ़ोl(tvout->regs + TVO_VIP_HDMI));
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "disabled");
	पूर्ण

	seq_माला_दो(s, "\n\n  DVO encoder: ");
	crtc = tvout->dvo->crtc;
	अगर (crtc) अणु
		seq_म_लिखो(s, "connected to %s path",
			   sti_crtc_is_मुख्य(crtc) ? "main" : "aux");
		DBGFS_DUMP(TVO_DVO_SYNC_SEL);
		DBGFS_DUMP(TVO_DVO_CONFIG);
		DBGFS_DUMP(TVO_VIP_DVO);
		tvout_dbg_vip(s, पढ़ोl(tvout->regs + TVO_VIP_DVO));
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "disabled");
	पूर्ण

	seq_माला_दो(s, "\n\n  HDA encoder: ");
	crtc = tvout->hda->crtc;
	अगर (crtc) अणु
		seq_म_लिखो(s, "connected to %s path",
			   sti_crtc_is_मुख्य(crtc) ? "main" : "aux");
		DBGFS_DUMP(TVO_HD_SYNC_SEL);
		DBGFS_DUMP(TVO_HD_DAC_CFG_OFF);
		tvout_dbg_hd_dac_cfg(s,
				     पढ़ोl(tvout->regs + TVO_HD_DAC_CFG_OFF));
		DBGFS_DUMP(TVO_VIP_HDF);
		tvout_dbg_vip(s, पढ़ोl(tvout->regs + TVO_VIP_HDF));
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "disabled");
	पूर्ण

	seq_माला_दो(s, "\n\n  main path configuration");
	DBGFS_DUMP(TVO_CSC_MAIN_M0);
	DBGFS_DUMP(TVO_CSC_MAIN_M1);
	DBGFS_DUMP(TVO_CSC_MAIN_M2);
	DBGFS_DUMP(TVO_CSC_MAIN_M3);
	DBGFS_DUMP(TVO_CSC_MAIN_M4);
	DBGFS_DUMP(TVO_CSC_MAIN_M5);
	DBGFS_DUMP(TVO_CSC_MAIN_M6);
	DBGFS_DUMP(TVO_CSC_MAIN_M7);
	DBGFS_DUMP(TVO_MAIN_IN_VID_FORMAT);

	seq_माला_दो(s, "\n\n  auxiliary path configuration");
	DBGFS_DUMP(TVO_CSC_AUX_M0);
	DBGFS_DUMP(TVO_CSC_AUX_M2);
	DBGFS_DUMP(TVO_CSC_AUX_M3);
	DBGFS_DUMP(TVO_CSC_AUX_M4);
	DBGFS_DUMP(TVO_CSC_AUX_M5);
	DBGFS_DUMP(TVO_CSC_AUX_M6);
	DBGFS_DUMP(TVO_CSC_AUX_M7);
	DBGFS_DUMP(TVO_AUX_IN_VID_FORMAT);
	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list tvout_debugfs_files[] = अणु
	अणु "tvout", tvout_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल व्योम tvout_debugfs_init(काष्ठा sti_tvout *tvout, काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tvout_debugfs_files); i++)
		tvout_debugfs_files[i].data = tvout;

	drm_debugfs_create_files(tvout_debugfs_files,
				 ARRAY_SIZE(tvout_debugfs_files),
				 minor->debugfs_root, minor);
पूर्ण

अटल व्योम sti_tvout_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
पूर्ण

अटल व्योम sti_tvout_encoder_mode_set(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_display_mode *mode,
				       काष्ठा drm_display_mode *adjusted_mode)
अणु
पूर्ण

अटल व्योम sti_tvout_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout_encoder *sti_encoder = to_sti_tvout_encoder(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(sti_encoder);
पूर्ण

अटल पूर्णांक sti_tvout_late_रेजिस्टर(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout *tvout = to_sti_tvout(encoder);

	अगर (tvout->debugfs_रेजिस्टरed)
		वापस 0;

	tvout_debugfs_init(tvout, encoder->dev->primary);

	tvout->debugfs_रेजिस्टरed = true;
	वापस 0;
पूर्ण

अटल व्योम sti_tvout_early_unरेजिस्टर(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout *tvout = to_sti_tvout(encoder);

	अगर (!tvout->debugfs_रेजिस्टरed)
		वापस;

	tvout->debugfs_रेजिस्टरed = false;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs sti_tvout_encoder_funcs = अणु
	.destroy = sti_tvout_encoder_destroy,
	.late_रेजिस्टर = sti_tvout_late_रेजिस्टर,
	.early_unरेजिस्टर = sti_tvout_early_unरेजिस्टर,
पूर्ण;

अटल व्योम sti_dvo_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout *tvout = to_sti_tvout(encoder);

	tvout_preक्रमmatter_set_matrix(tvout, &encoder->crtc->mode);

	tvout_dvo_start(tvout, sti_crtc_is_मुख्य(encoder->crtc));
पूर्ण

अटल व्योम sti_dvo_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout *tvout = to_sti_tvout(encoder);

	/* Reset VIP रेजिस्टर */
	tvout_ग_लिखो(tvout, 0x0, TVO_VIP_DVO);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs sti_dvo_encoder_helper_funcs = अणु
	.dpms = sti_tvout_encoder_dpms,
	.mode_set = sti_tvout_encoder_mode_set,
	.enable = sti_dvo_encoder_enable,
	.disable = sti_dvo_encoder_disable,
पूर्ण;

अटल काष्ठा drm_encoder *
sti_tvout_create_dvo_encoder(काष्ठा drm_device *dev,
			     काष्ठा sti_tvout *tvout)
अणु
	काष्ठा sti_tvout_encoder *encoder;
	काष्ठा drm_encoder *drm_encoder;

	encoder = devm_kzalloc(tvout->dev, माप(*encoder), GFP_KERNEL);
	अगर (!encoder)
		वापस शून्य;

	encoder->tvout = tvout;

	drm_encoder = &encoder->encoder;

	drm_encoder->possible_crtcs = ENCODER_CRTC_MASK;

	drm_encoder_init(dev, drm_encoder,
			 &sti_tvout_encoder_funcs, DRM_MODE_ENCODER_LVDS,
			 शून्य);

	drm_encoder_helper_add(drm_encoder, &sti_dvo_encoder_helper_funcs);

	वापस drm_encoder;
पूर्ण

अटल व्योम sti_hda_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout *tvout = to_sti_tvout(encoder);

	tvout_preक्रमmatter_set_matrix(tvout, &encoder->crtc->mode);

	tvout_hda_start(tvout, sti_crtc_is_मुख्य(encoder->crtc));
पूर्ण

अटल व्योम sti_hda_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout *tvout = to_sti_tvout(encoder);

	/* reset VIP रेजिस्टर */
	tvout_ग_लिखो(tvout, 0x0, TVO_VIP_HDF);

	/* घातer करोwn HD DAC */
	tvout_ग_लिखो(tvout, 1, TVO_HD_DAC_CFG_OFF);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs sti_hda_encoder_helper_funcs = अणु
	.dpms = sti_tvout_encoder_dpms,
	.mode_set = sti_tvout_encoder_mode_set,
	.commit = sti_hda_encoder_enable,
	.disable = sti_hda_encoder_disable,
पूर्ण;

अटल काष्ठा drm_encoder *sti_tvout_create_hda_encoder(काष्ठा drm_device *dev,
		काष्ठा sti_tvout *tvout)
अणु
	काष्ठा sti_tvout_encoder *encoder;
	काष्ठा drm_encoder *drm_encoder;

	encoder = devm_kzalloc(tvout->dev, माप(*encoder), GFP_KERNEL);
	अगर (!encoder)
		वापस शून्य;

	encoder->tvout = tvout;

	drm_encoder = &encoder->encoder;

	drm_encoder->possible_crtcs = ENCODER_CRTC_MASK;

	drm_encoder_init(dev, drm_encoder,
			&sti_tvout_encoder_funcs, DRM_MODE_ENCODER_DAC, शून्य);

	drm_encoder_helper_add(drm_encoder, &sti_hda_encoder_helper_funcs);

	वापस drm_encoder;
पूर्ण

अटल व्योम sti_hdmi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout *tvout = to_sti_tvout(encoder);

	tvout_preक्रमmatter_set_matrix(tvout, &encoder->crtc->mode);

	tvout_hdmi_start(tvout, sti_crtc_is_मुख्य(encoder->crtc));
पूर्ण

अटल व्योम sti_hdmi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sti_tvout *tvout = to_sti_tvout(encoder);

	/* reset VIP रेजिस्टर */
	tvout_ग_लिखो(tvout, 0x0, TVO_VIP_HDMI);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs sti_hdmi_encoder_helper_funcs = अणु
	.dpms = sti_tvout_encoder_dpms,
	.mode_set = sti_tvout_encoder_mode_set,
	.commit = sti_hdmi_encoder_enable,
	.disable = sti_hdmi_encoder_disable,
पूर्ण;

अटल काष्ठा drm_encoder *sti_tvout_create_hdmi_encoder(काष्ठा drm_device *dev,
		काष्ठा sti_tvout *tvout)
अणु
	काष्ठा sti_tvout_encoder *encoder;
	काष्ठा drm_encoder *drm_encoder;

	encoder = devm_kzalloc(tvout->dev, माप(*encoder), GFP_KERNEL);
	अगर (!encoder)
		वापस शून्य;

	encoder->tvout = tvout;

	drm_encoder = &encoder->encoder;

	drm_encoder->possible_crtcs = ENCODER_CRTC_MASK;

	drm_encoder_init(dev, drm_encoder,
			&sti_tvout_encoder_funcs, DRM_MODE_ENCODER_TMDS, शून्य);

	drm_encoder_helper_add(drm_encoder, &sti_hdmi_encoder_helper_funcs);

	वापस drm_encoder;
पूर्ण

अटल व्योम sti_tvout_create_encoders(काष्ठा drm_device *dev,
		काष्ठा sti_tvout *tvout)
अणु
	tvout->hdmi = sti_tvout_create_hdmi_encoder(dev, tvout);
	tvout->hda = sti_tvout_create_hda_encoder(dev, tvout);
	tvout->dvo = sti_tvout_create_dvo_encoder(dev, tvout);

	tvout->hdmi->possible_clones = drm_encoder_mask(tvout->hdmi) |
		drm_encoder_mask(tvout->hda) | drm_encoder_mask(tvout->dvo);
	tvout->hda->possible_clones = drm_encoder_mask(tvout->hdmi) |
		drm_encoder_mask(tvout->hda) | drm_encoder_mask(tvout->dvo);
	tvout->dvo->possible_clones = drm_encoder_mask(tvout->hdmi) |
		drm_encoder_mask(tvout->hda) | drm_encoder_mask(tvout->dvo);
पूर्ण

अटल व्योम sti_tvout_destroy_encoders(काष्ठा sti_tvout *tvout)
अणु
	अगर (tvout->hdmi)
		drm_encoder_cleanup(tvout->hdmi);
	tvout->hdmi = शून्य;

	अगर (tvout->hda)
		drm_encoder_cleanup(tvout->hda);
	tvout->hda = शून्य;

	अगर (tvout->dvo)
		drm_encoder_cleanup(tvout->dvo);
	tvout->dvo = शून्य;
पूर्ण

अटल पूर्णांक sti_tvout_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा sti_tvout *tvout = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;

	tvout->drm_dev = drm_dev;

	sti_tvout_create_encoders(drm_dev, tvout);

	वापस 0;
पूर्ण

अटल व्योम sti_tvout_unbind(काष्ठा device *dev, काष्ठा device *master,
	व्योम *data)
अणु
	काष्ठा sti_tvout *tvout = dev_get_drvdata(dev);

	sti_tvout_destroy_encoders(tvout);
पूर्ण

अटल स्थिर काष्ठा component_ops sti_tvout_ops = अणु
	.bind	= sti_tvout_bind,
	.unbind	= sti_tvout_unbind,
पूर्ण;

अटल पूर्णांक sti_tvout_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा sti_tvout *tvout;
	काष्ठा resource *res;

	DRM_INFO("%s\n", __func__);

	अगर (!node)
		वापस -ENODEV;

	tvout = devm_kzalloc(dev, माप(*tvout), GFP_KERNEL);
	अगर (!tvout)
		वापस -ENOMEM;

	tvout->dev = dev;

	/* get memory resources */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "tvout-reg");
	अगर (!res) अणु
		DRM_ERROR("Invalid glue resource\n");
		वापस -ENOMEM;
	पूर्ण
	tvout->regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!tvout->regs)
		वापस -ENOMEM;

	/* get reset resources */
	tvout->reset = devm_reset_control_get(dev, "tvout");
	/* take tvout out of reset */
	अगर (!IS_ERR(tvout->reset))
		reset_control_deनिश्चित(tvout->reset);

	platक्रमm_set_drvdata(pdev, tvout);

	वापस component_add(dev, &sti_tvout_ops);
पूर्ण

अटल पूर्णांक sti_tvout_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sti_tvout_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tvout_of_match[] = अणु
	अणु .compatible = "st,stih407-tvout", पूर्ण,
	अणु /* end node */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tvout_of_match);

काष्ठा platक्रमm_driver sti_tvout_driver = अणु
	.driver = अणु
		.name = "sti-tvout",
		.owner = THIS_MODULE,
		.of_match_table = tvout_of_match,
	पूर्ण,
	.probe = sti_tvout_probe,
	.हटाओ = sti_tvout_हटाओ,
पूर्ण;

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SoC DRM driver");
MODULE_LICENSE("GPL");
