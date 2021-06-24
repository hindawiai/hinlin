<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

/* HDक्रमmatter रेजिस्टरs */
#घोषणा HDA_ANA_CFG                     0x0000
#घोषणा HDA_ANA_SCALE_CTRL_Y            0x0004
#घोषणा HDA_ANA_SCALE_CTRL_CB           0x0008
#घोषणा HDA_ANA_SCALE_CTRL_CR           0x000C
#घोषणा HDA_ANA_ANC_CTRL                0x0010
#घोषणा HDA_ANA_SRC_Y_CFG               0x0014
#घोषणा HDA_COEFF_Y_PH1_TAP123          0x0018
#घोषणा HDA_COEFF_Y_PH1_TAP456          0x001C
#घोषणा HDA_COEFF_Y_PH2_TAP123          0x0020
#घोषणा HDA_COEFF_Y_PH2_TAP456          0x0024
#घोषणा HDA_COEFF_Y_PH3_TAP123          0x0028
#घोषणा HDA_COEFF_Y_PH3_TAP456          0x002C
#घोषणा HDA_COEFF_Y_PH4_TAP123          0x0030
#घोषणा HDA_COEFF_Y_PH4_TAP456          0x0034
#घोषणा HDA_ANA_SRC_C_CFG               0x0040
#घोषणा HDA_COEFF_C_PH1_TAP123          0x0044
#घोषणा HDA_COEFF_C_PH1_TAP456          0x0048
#घोषणा HDA_COEFF_C_PH2_TAP123          0x004C
#घोषणा HDA_COEFF_C_PH2_TAP456          0x0050
#घोषणा HDA_COEFF_C_PH3_TAP123          0x0054
#घोषणा HDA_COEFF_C_PH3_TAP456          0x0058
#घोषणा HDA_COEFF_C_PH4_TAP123          0x005C
#घोषणा HDA_COEFF_C_PH4_TAP456          0x0060
#घोषणा HDA_SYNC_AWGI                   0x0300

/* HDA_ANA_CFG */
#घोषणा CFG_AWG_ASYNC_EN                BIT(0)
#घोषणा CFG_AWG_ASYNC_HSYNC_MTD         BIT(1)
#घोषणा CFG_AWG_ASYNC_VSYNC_MTD         BIT(2)
#घोषणा CFG_AWG_SYNC_DEL                BIT(3)
#घोषणा CFG_AWG_FLTR_MODE_SHIFT         4
#घोषणा CFG_AWG_FLTR_MODE_MASK          (0xF << CFG_AWG_FLTR_MODE_SHIFT)
#घोषणा CFG_AWG_FLTR_MODE_SD            (0 << CFG_AWG_FLTR_MODE_SHIFT)
#घोषणा CFG_AWG_FLTR_MODE_ED            (1 << CFG_AWG_FLTR_MODE_SHIFT)
#घोषणा CFG_AWG_FLTR_MODE_HD            (2 << CFG_AWG_FLTR_MODE_SHIFT)
#घोषणा CFG_SYNC_ON_PBPR_MASK           BIT(8)
#घोषणा CFG_PREFILTER_EN_MASK           BIT(9)
#घोषणा CFG_PBPR_SYNC_OFF_SHIFT         16
#घोषणा CFG_PBPR_SYNC_OFF_MASK          (0x7FF << CFG_PBPR_SYNC_OFF_SHIFT)
#घोषणा CFG_PBPR_SYNC_OFF_VAL           0x117 /* Voltage dependent. stiH416 */

/* Default scaling values */
#घोषणा SCALE_CTRL_Y_DFLT               0x00C50256
#घोषणा SCALE_CTRL_CB_DFLT              0x00DB0249
#घोषणा SCALE_CTRL_CR_DFLT              0x00DB0249

/* Video DACs control */
#घोषणा DAC_CFG_HD_HZUVW_OFF_MASK       BIT(1)

/* Upsampler values क्रम the alternative 2X Filter */
#घोषणा SAMPLER_COEF_NB                 8
#घोषणा HDA_ANA_SRC_Y_CFG_ALT_2X        0x01130000
अटल u32 coef_y_alt_2x[] = अणु
	0x00FE83FB, 0x1F900401, 0x00000000, 0x00000000,
	0x00F408F9, 0x055F7C25, 0x00000000, 0x00000000
पूर्ण;

#घोषणा HDA_ANA_SRC_C_CFG_ALT_2X        0x01750004
अटल u32 coef_c_alt_2x[] = अणु
	0x001305F7, 0x05274BD0, 0x00000000, 0x00000000,
	0x0004907C, 0x09C80B9D, 0x00000000, 0x00000000
पूर्ण;

/* Upsampler values क्रम the 4X Filter */
#घोषणा HDA_ANA_SRC_Y_CFG_4X            0x01ED0005
#घोषणा HDA_ANA_SRC_C_CFG_4X            0x01ED0004
अटल u32 coef_yc_4x[] = अणु
	0x00FC827F, 0x008FE20B, 0x00F684FC, 0x050F7C24,
	0x00F4857C, 0x0A1F402E, 0x00FA027F, 0x0E076E1D
पूर्ण;

/* AWG inकाष्ठाions क्रम some video modes */
#घोषणा AWG_MAX_INST                    64

/* 720p@50 */
अटल u32 AWGi_720p_50[] = अणु
	0x00000971, 0x00000C26, 0x0000013B, 0x00000CDA,
	0x00000104, 0x00000E7E, 0x00000E7F, 0x0000013B,
	0x00000D8E, 0x00000104, 0x00001804, 0x00000971,
	0x00000C26, 0x0000003B, 0x00000FB4, 0x00000FB5,
	0x00000104, 0x00001AE8
पूर्ण;

#घोषणा NN_720p_50 ARRAY_SIZE(AWGi_720p_50)

/* 720p@60 */
अटल u32 AWGi_720p_60[] = अणु
	0x00000971, 0x00000C26, 0x0000013B, 0x00000CDA,
	0x00000104, 0x00000E7E, 0x00000E7F, 0x0000013B,
	0x00000C44, 0x00000104, 0x00001804, 0x00000971,
	0x00000C26, 0x0000003B, 0x00000F0F, 0x00000F10,
	0x00000104, 0x00001AE8
पूर्ण;

#घोषणा NN_720p_60 ARRAY_SIZE(AWGi_720p_60)

/* 1080p@30 */
अटल u32 AWGi_1080p_30[] = अणु
	0x00000971, 0x00000C2A, 0x0000013B, 0x00000C56,
	0x00000104, 0x00000FDC, 0x00000FDD, 0x0000013B,
	0x00000C2A, 0x00000104, 0x00001804, 0x00000971,
	0x00000C2A, 0x0000003B, 0x00000EBE, 0x00000EBF,
	0x00000EBF, 0x00000104, 0x00001A2F, 0x00001C4B,
	0x00001C52
पूर्ण;

#घोषणा NN_1080p_30 ARRAY_SIZE(AWGi_1080p_30)

/* 1080p@25 */
अटल u32 AWGi_1080p_25[] = अणु
	0x00000971, 0x00000C2A, 0x0000013B, 0x00000C56,
	0x00000104, 0x00000FDC, 0x00000FDD, 0x0000013B,
	0x00000DE2, 0x00000104, 0x00001804, 0x00000971,
	0x00000C2A, 0x0000003B, 0x00000F51, 0x00000F51,
	0x00000F52, 0x00000104, 0x00001A2F, 0x00001C4B,
	0x00001C52
पूर्ण;

#घोषणा NN_1080p_25 ARRAY_SIZE(AWGi_1080p_25)

/* 1080p@24 */
अटल u32 AWGi_1080p_24[] = अणु
	0x00000971, 0x00000C2A, 0x0000013B, 0x00000C56,
	0x00000104, 0x00000FDC, 0x00000FDD, 0x0000013B,
	0x00000E50, 0x00000104, 0x00001804, 0x00000971,
	0x00000C2A, 0x0000003B, 0x00000F76, 0x00000F76,
	0x00000F76, 0x00000104, 0x00001A2F, 0x00001C4B,
	0x00001C52
पूर्ण;

#घोषणा NN_1080p_24 ARRAY_SIZE(AWGi_1080p_24)

/* 720x480p@60 */
अटल u32 AWGi_720x480p_60[] = अणु
	0x00000904, 0x00000F18, 0x0000013B, 0x00001805,
	0x00000904, 0x00000C3D, 0x0000003B, 0x00001A06
पूर्ण;

#घोषणा NN_720x480p_60 ARRAY_SIZE(AWGi_720x480p_60)

/* Video mode category */
क्रमागत sti_hda_vid_cat अणु
	VID_SD,
	VID_ED,
	VID_HD_74M,
	VID_HD_148M
पूर्ण;

काष्ठा sti_hda_video_config अणु
	काष्ठा drm_display_mode mode;
	u32 *awg_instr;
	पूर्णांक nb_instr;
	क्रमागत sti_hda_vid_cat vid_cat;
पूर्ण;

/* HD analog supported modes
 * Interlaced modes may be added when supported by the whole display chain
 */
अटल स्थिर काष्ठा sti_hda_video_config hda_supported_modes[] = अणु
	/* 1080p30 74.250Mhz */
	अणुअणुDRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)पूर्ण,
	 AWGi_1080p_30, NN_1080p_30, VID_HD_74Mपूर्ण,
	/* 1080p30 74.176Mhz */
	अणुअणुDRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74176, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)पूर्ण,
	 AWGi_1080p_30, NN_1080p_30, VID_HD_74Mपूर्ण,
	/* 1080p24 74.250Mhz */
	अणुअणुDRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)पूर्ण,
	 AWGi_1080p_24, NN_1080p_24, VID_HD_74Mपूर्ण,
	/* 1080p24 74.176Mhz */
	अणुअणुDRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74176, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)पूर्ण,
	 AWGi_1080p_24, NN_1080p_24, VID_HD_74Mपूर्ण,
	/* 1080p25 74.250Mhz */
	अणुअणुDRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)पूर्ण,
	 AWGi_1080p_25, NN_1080p_25, VID_HD_74Mपूर्ण,
	/* 720p60 74.250Mhz */
	अणुअणुDRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)पूर्ण,
	 AWGi_720p_60, NN_720p_60, VID_HD_74Mपूर्ण,
	/* 720p60 74.176Mhz */
	अणुअणुDRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74176, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)पूर्ण,
	 AWGi_720p_60, NN_720p_60, VID_HD_74Mपूर्ण,
	/* 720p50 74.250Mhz */
	अणुअणुDRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC)पूर्ण,
	 AWGi_720p_50, NN_720p_50, VID_HD_74Mपूर्ण,
	/* 720x480p60 27.027Mhz */
	अणुअणुDRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27027, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)पूर्ण,
	 AWGi_720x480p_60, NN_720x480p_60, VID_EDपूर्ण,
	/* 720x480p60 27.000Mhz */
	अणुअणुDRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)पूर्ण,
	 AWGi_720x480p_60, NN_720x480p_60, VID_EDपूर्ण
पूर्ण;

/*
 * STI hd analog काष्ठाure
 *
 * @dev: driver device
 * @drm_dev: poपूर्णांकer to drm device
 * @mode: current display mode selected
 * @regs: HD analog रेजिस्टर
 * @video_dacs_ctrl: video DACS control रेजिस्टर
 * @enabled: true अगर HD analog is enabled अन्यथा false
 */
काष्ठा sti_hda अणु
	काष्ठा device dev;
	काष्ठा drm_device *drm_dev;
	काष्ठा drm_display_mode mode;
	व्योम __iomem *regs;
	व्योम __iomem *video_dacs_ctrl;
	काष्ठा clk *clk_pix;
	काष्ठा clk *clk_hddac;
	bool enabled;
पूर्ण;

काष्ठा sti_hda_connector अणु
	काष्ठा drm_connector drm_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा sti_hda *hda;
पूर्ण;

#घोषणा to_sti_hda_connector(x) \
	container_of(x, काष्ठा sti_hda_connector, drm_connector)

अटल u32 hda_पढ़ो(काष्ठा sti_hda *hda, पूर्णांक offset)
अणु
	वापस पढ़ोl(hda->regs + offset);
पूर्ण

अटल व्योम hda_ग_लिखो(काष्ठा sti_hda *hda, u32 val, पूर्णांक offset)
अणु
	ग_लिखोl(val, hda->regs + offset);
पूर्ण

/**
 * Search क्रम a video mode in the supported modes table
 *
 * @mode: mode being searched
 * @idx: index of the found mode
 *
 * Return true अगर mode is found
 */
अटल bool hda_get_mode_idx(काष्ठा drm_display_mode mode, पूर्णांक *idx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hda_supported_modes); i++)
		अगर (drm_mode_equal(&hda_supported_modes[i].mode, &mode)) अणु
			*idx = i;
			वापस true;
		पूर्ण
	वापस false;
पूर्ण

/**
 * Enable the HD DACS
 *
 * @hda: poपूर्णांकer to HD analog काष्ठाure
 * @enable: true अगर HD DACS need to be enabled, अन्यथा false
 */
अटल व्योम hda_enable_hd_dacs(काष्ठा sti_hda *hda, bool enable)
अणु
	अगर (hda->video_dacs_ctrl) अणु
		u32 val;

		val = पढ़ोl(hda->video_dacs_ctrl);
		अगर (enable)
			val &= ~DAC_CFG_HD_HZUVW_OFF_MASK;
		अन्यथा
			val |= DAC_CFG_HD_HZUVW_OFF_MASK;

		ग_लिखोl(val, hda->video_dacs_ctrl);
	पूर्ण
पूर्ण

#घोषणा DBGFS_DUMP(reg) seq_म_लिखो(s, "\n  %-25s 0x%08X", #reg, \
				   पढ़ोl(hda->regs + reg))

अटल व्योम hda_dbg_cfg(काष्ठा seq_file *s, पूर्णांक val)
अणु
	seq_माला_दो(s, "\tAWG ");
	seq_माला_दो(s, val & CFG_AWG_ASYNC_EN ? "enabled" : "disabled");
पूर्ण

अटल व्योम hda_dbg_awg_microcode(काष्ठा seq_file *s, व्योम __iomem *reg)
अणु
	अचिन्हित पूर्णांक i;

	seq_माला_दो(s, "\n\n  HDA AWG microcode:");
	क्रम (i = 0; i < AWG_MAX_INST; i++) अणु
		अगर (i % 8 == 0)
			seq_म_लिखो(s, "\n  %04X:", i);
		seq_म_लिखो(s, " %04X", पढ़ोl(reg + i * 4));
	पूर्ण
पूर्ण

अटल व्योम hda_dbg_video_dacs_ctrl(काष्ठा seq_file *s, व्योम __iomem *reg)
अणु
	u32 val = पढ़ोl(reg);

	seq_म_लिखो(s, "\n\n  %-25s 0x%08X", "VIDEO_DACS_CONTROL", val);
	seq_माला_दो(s, "\tHD DACs ");
	seq_माला_दो(s, val & DAC_CFG_HD_HZUVW_OFF_MASK ? "disabled" : "enabled");
पूर्ण

अटल पूर्णांक hda_dbg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_hda *hda = (काष्ठा sti_hda *)node->info_ent->data;

	seq_म_लिखो(s, "HD Analog: (vaddr = 0x%p)", hda->regs);
	DBGFS_DUMP(HDA_ANA_CFG);
	hda_dbg_cfg(s, पढ़ोl(hda->regs + HDA_ANA_CFG));
	DBGFS_DUMP(HDA_ANA_SCALE_CTRL_Y);
	DBGFS_DUMP(HDA_ANA_SCALE_CTRL_CB);
	DBGFS_DUMP(HDA_ANA_SCALE_CTRL_CR);
	DBGFS_DUMP(HDA_ANA_ANC_CTRL);
	DBGFS_DUMP(HDA_ANA_SRC_Y_CFG);
	DBGFS_DUMP(HDA_ANA_SRC_C_CFG);
	hda_dbg_awg_microcode(s, hda->regs + HDA_SYNC_AWGI);
	अगर (hda->video_dacs_ctrl)
		hda_dbg_video_dacs_ctrl(s, hda->video_dacs_ctrl);
	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list hda_debugfs_files[] = अणु
	अणु "hda", hda_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल व्योम hda_debugfs_init(काष्ठा sti_hda *hda, काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hda_debugfs_files); i++)
		hda_debugfs_files[i].data = hda;

	drm_debugfs_create_files(hda_debugfs_files,
				 ARRAY_SIZE(hda_debugfs_files),
				 minor->debugfs_root, minor);
पूर्ण

/**
 * Configure AWG, writing inकाष्ठाions
 *
 * @hda: poपूर्णांकer to HD analog काष्ठाure
 * @awg_instr: poपूर्णांकer to AWG inकाष्ठाions table
 * @nb: nb of AWG inकाष्ठाions
 */
अटल व्योम sti_hda_configure_awg(काष्ठा sti_hda *hda, u32 *awg_instr, पूर्णांक nb)
अणु
	अचिन्हित पूर्णांक i;

	DRM_DEBUG_DRIVER("\n");

	क्रम (i = 0; i < nb; i++)
		hda_ग_लिखो(hda, awg_instr[i], HDA_SYNC_AWGI + i * 4);
	क्रम (i = nb; i < AWG_MAX_INST; i++)
		hda_ग_लिखो(hda, 0, HDA_SYNC_AWGI + i * 4);
पूर्ण

अटल व्योम sti_hda_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sti_hda *hda = bridge->driver_निजी;
	u32 val;

	अगर (!hda->enabled)
		वापस;

	DRM_DEBUG_DRIVER("\n");

	/* Disable HD DAC and AWG */
	val = hda_पढ़ो(hda, HDA_ANA_CFG);
	val &= ~CFG_AWG_ASYNC_EN;
	hda_ग_लिखो(hda, val, HDA_ANA_CFG);
	hda_ग_लिखो(hda, 0, HDA_ANA_ANC_CTRL);

	hda_enable_hd_dacs(hda, false);

	/* Disable/unprepare hda घड़ी */
	clk_disable_unprepare(hda->clk_hddac);
	clk_disable_unprepare(hda->clk_pix);

	hda->enabled = false;
पूर्ण

अटल व्योम sti_hda_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sti_hda *hda = bridge->driver_निजी;
	u32 val, i, mode_idx;
	u32 src_filter_y, src_filter_c;
	u32 *coef_y, *coef_c;
	u32 filter_mode;

	DRM_DEBUG_DRIVER("\n");

	अगर (hda->enabled)
		वापस;

	/* Prepare/enable घड़ीs */
	अगर (clk_prepare_enable(hda->clk_pix))
		DRM_ERROR("Failed to prepare/enable hda_pix clk\n");
	अगर (clk_prepare_enable(hda->clk_hddac))
		DRM_ERROR("Failed to prepare/enable hda_hddac clk\n");

	अगर (!hda_get_mode_idx(hda->mode, &mode_idx)) अणु
		DRM_ERROR("Undefined mode\n");
		वापस;
	पूर्ण

	चयन (hda_supported_modes[mode_idx].vid_cat) अणु
	हाल VID_HD_148M:
		DRM_ERROR("Beyond HD analog capabilities\n");
		वापस;
	हाल VID_HD_74M:
		/* HD use alternate 2x filter */
		filter_mode = CFG_AWG_FLTR_MODE_HD;
		src_filter_y = HDA_ANA_SRC_Y_CFG_ALT_2X;
		src_filter_c = HDA_ANA_SRC_C_CFG_ALT_2X;
		coef_y = coef_y_alt_2x;
		coef_c = coef_c_alt_2x;
		अवरोध;
	हाल VID_ED:
		/* ED uses 4x filter */
		filter_mode = CFG_AWG_FLTR_MODE_ED;
		src_filter_y = HDA_ANA_SRC_Y_CFG_4X;
		src_filter_c = HDA_ANA_SRC_C_CFG_4X;
		coef_y = coef_yc_4x;
		coef_c = coef_yc_4x;
		अवरोध;
	हाल VID_SD:
		DRM_ERROR("Not supported\n");
		वापस;
	शेष:
		DRM_ERROR("Undefined resolution\n");
		वापस;
	पूर्ण
	DRM_DEBUG_DRIVER("Using HDA mode #%d\n", mode_idx);

	/* Enable HD Video DACs */
	hda_enable_hd_dacs(hda, true);

	/* Configure scaler */
	hda_ग_लिखो(hda, SCALE_CTRL_Y_DFLT, HDA_ANA_SCALE_CTRL_Y);
	hda_ग_लिखो(hda, SCALE_CTRL_CB_DFLT, HDA_ANA_SCALE_CTRL_CB);
	hda_ग_लिखो(hda, SCALE_CTRL_CR_DFLT, HDA_ANA_SCALE_CTRL_CR);

	/* Configure sampler */
	hda_ग_लिखो(hda , src_filter_y, HDA_ANA_SRC_Y_CFG);
	hda_ग_लिखो(hda, src_filter_c,  HDA_ANA_SRC_C_CFG);
	क्रम (i = 0; i < SAMPLER_COEF_NB; i++) अणु
		hda_ग_लिखो(hda, coef_y[i], HDA_COEFF_Y_PH1_TAP123 + i * 4);
		hda_ग_लिखो(hda, coef_c[i], HDA_COEFF_C_PH1_TAP123 + i * 4);
	पूर्ण

	/* Configure मुख्य HDFormatter */
	val = 0;
	val |= (hda->mode.flags & DRM_MODE_FLAG_INTERLACE) ?
	    0 : CFG_AWG_ASYNC_VSYNC_MTD;
	val |= (CFG_PBPR_SYNC_OFF_VAL << CFG_PBPR_SYNC_OFF_SHIFT);
	val |= filter_mode;
	hda_ग_लिखो(hda, val, HDA_ANA_CFG);

	/* Configure AWG */
	sti_hda_configure_awg(hda, hda_supported_modes[mode_idx].awg_instr,
			      hda_supported_modes[mode_idx].nb_instr);

	/* Enable AWG */
	val = hda_पढ़ो(hda, HDA_ANA_CFG);
	val |= CFG_AWG_ASYNC_EN;
	hda_ग_लिखो(hda, val, HDA_ANA_CFG);

	hda->enabled = true;
पूर्ण

अटल व्योम sti_hda_set_mode(काष्ठा drm_bridge *bridge,
			     स्थिर काष्ठा drm_display_mode *mode,
			     स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sti_hda *hda = bridge->driver_निजी;
	u32 mode_idx;
	पूर्णांक hddac_rate;
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	स_नकल(&hda->mode, mode, माप(काष्ठा drm_display_mode));

	अगर (!hda_get_mode_idx(hda->mode, &mode_idx)) अणु
		DRM_ERROR("Undefined mode\n");
		वापस;
	पूर्ण

	चयन (hda_supported_modes[mode_idx].vid_cat) अणु
	हाल VID_HD_74M:
		/* HD use alternate 2x filter */
		hddac_rate = mode->घड़ी * 1000 * 2;
		अवरोध;
	हाल VID_ED:
		/* ED uses 4x filter */
		hddac_rate = mode->घड़ी * 1000 * 4;
		अवरोध;
	शेष:
		DRM_ERROR("Undefined mode\n");
		वापस;
	पूर्ण

	/* HD DAC = 148.5Mhz or 108 Mhz */
	ret = clk_set_rate(hda->clk_hddac, hddac_rate);
	अगर (ret < 0)
		DRM_ERROR("Cannot set rate (%dHz) for hda_hddac clk\n",
			  hddac_rate);

	/* HDक्रमmatter घड़ी = compositor घड़ी */
	ret = clk_set_rate(hda->clk_pix, mode->घड़ी * 1000);
	अगर (ret < 0)
		DRM_ERROR("Cannot set rate (%dHz) for hda_pix clk\n",
			  mode->घड़ी * 1000);
पूर्ण

अटल व्योम sti_hda_bridge_nope(काष्ठा drm_bridge *bridge)
अणु
	/* करो nothing */
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs sti_hda_bridge_funcs = अणु
	.pre_enable = sti_hda_pre_enable,
	.enable = sti_hda_bridge_nope,
	.disable = sti_hda_disable,
	.post_disable = sti_hda_bridge_nope,
	.mode_set = sti_hda_set_mode,
पूर्ण;

अटल पूर्णांक sti_hda_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक count = 0;
	काष्ठा sti_hda_connector *hda_connector
		= to_sti_hda_connector(connector);
	काष्ठा sti_hda *hda = hda_connector->hda;

	DRM_DEBUG_DRIVER("\n");

	क्रम (i = 0; i < ARRAY_SIZE(hda_supported_modes); i++) अणु
		काष्ठा drm_display_mode *mode =
			drm_mode_duplicate(hda->drm_dev,
					&hda_supported_modes[i].mode);
		अगर (!mode)
			जारी;

		/* the first mode is the preferred mode */
		अगर (i == 0)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_probed_add(connector, mode);
		count++;
	पूर्ण

	वापस count;
पूर्ण

#घोषणा CLK_TOLERANCE_HZ 50

अटल पूर्णांक sti_hda_connector_mode_valid(काष्ठा drm_connector *connector,
					काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक target = mode->घड़ी * 1000;
	पूर्णांक target_min = target - CLK_TOLERANCE_HZ;
	पूर्णांक target_max = target + CLK_TOLERANCE_HZ;
	पूर्णांक result;
	पूर्णांक idx;
	काष्ठा sti_hda_connector *hda_connector
		= to_sti_hda_connector(connector);
	काष्ठा sti_hda *hda = hda_connector->hda;

	अगर (!hda_get_mode_idx(*mode, &idx)) अणु
		वापस MODE_BAD;
	पूर्ण अन्यथा अणु
		result = clk_round_rate(hda->clk_pix, target);

		DRM_DEBUG_DRIVER("target rate = %d => available rate = %d\n",
				 target, result);

		अगर ((result < target_min) || (result > target_max)) अणु
			DRM_DEBUG_DRIVER("hda pixclk=%d not supported\n",
					 target);
			वापस MODE_BAD;
		पूर्ण
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल स्थिर
काष्ठा drm_connector_helper_funcs sti_hda_connector_helper_funcs = अणु
	.get_modes = sti_hda_connector_get_modes,
	.mode_valid = sti_hda_connector_mode_valid,
पूर्ण;

अटल पूर्णांक sti_hda_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा sti_hda_connector *hda_connector
		= to_sti_hda_connector(connector);
	काष्ठा sti_hda *hda = hda_connector->hda;

	hda_debugfs_init(hda, hda->drm_dev->primary);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sti_hda_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.late_रेजिस्टर = sti_hda_late_रेजिस्टर,
पूर्ण;

अटल काष्ठा drm_encoder *sti_hda_find_encoder(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->encoder_type == DRM_MODE_ENCODER_DAC)
			वापस encoder;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sti_hda_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा sti_hda *hda = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा drm_encoder *encoder;
	काष्ठा sti_hda_connector *connector;
	काष्ठा drm_connector *drm_connector;
	काष्ठा drm_bridge *bridge;
	पूर्णांक err;

	/* Set the drm device handle */
	hda->drm_dev = drm_dev;

	encoder = sti_hda_find_encoder(drm_dev);
	अगर (!encoder)
		वापस -ENOMEM;

	connector = devm_kzalloc(dev, माप(*connector), GFP_KERNEL);
	अगर (!connector)
		वापस -ENOMEM;

	connector->hda = hda;

		bridge = devm_kzalloc(dev, माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->driver_निजी = hda;
	bridge->funcs = &sti_hda_bridge_funcs;
	drm_bridge_attach(encoder, bridge, शून्य, 0);

	connector->encoder = encoder;

	drm_connector = (काष्ठा drm_connector *)connector;

	drm_connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_init(drm_dev, drm_connector,
			&sti_hda_connector_funcs, DRM_MODE_CONNECTOR_Component);
	drm_connector_helper_add(drm_connector,
			&sti_hda_connector_helper_funcs);

	err = drm_connector_attach_encoder(drm_connector, encoder);
	अगर (err) अणु
		DRM_ERROR("Failed to attach a connector to a encoder\n");
		जाओ err_sysfs;
	पूर्ण

	/* क्रमce to disable hd dacs at startup */
	hda_enable_hd_dacs(hda, false);

	वापस 0;

err_sysfs:
	वापस -EINVAL;
पूर्ण

अटल व्योम sti_hda_unbind(काष्ठा device *dev,
		काष्ठा device *master, व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा component_ops sti_hda_ops = अणु
	.bind = sti_hda_bind,
	.unbind = sti_hda_unbind,
पूर्ण;

अटल पूर्णांक sti_hda_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sti_hda *hda;
	काष्ठा resource *res;

	DRM_INFO("%s\n", __func__);

	hda = devm_kzalloc(dev, माप(*hda), GFP_KERNEL);
	अगर (!hda)
		वापस -ENOMEM;

	hda->dev = pdev->dev;

	/* Get resources */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "hda-reg");
	अगर (!res) अणु
		DRM_ERROR("Invalid hda resource\n");
		वापस -ENOMEM;
	पूर्ण
	hda->regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!hda->regs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
			"video-dacs-ctrl");
	अगर (res) अणु
		hda->video_dacs_ctrl = devm_ioremap(dev, res->start,
				resource_size(res));
		अगर (!hda->video_dacs_ctrl)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		/* If no existing video-dacs-ctrl resource जारी the probe */
		DRM_DEBUG_DRIVER("No video-dacs-ctrl resource\n");
		hda->video_dacs_ctrl = शून्य;
	पूर्ण

	/* Get घड़ी resources */
	hda->clk_pix = devm_clk_get(dev, "pix");
	अगर (IS_ERR(hda->clk_pix)) अणु
		DRM_ERROR("Cannot get hda_pix clock\n");
		वापस PTR_ERR(hda->clk_pix);
	पूर्ण

	hda->clk_hddac = devm_clk_get(dev, "hddac");
	अगर (IS_ERR(hda->clk_hddac)) अणु
		DRM_ERROR("Cannot get hda_hddac clock\n");
		वापस PTR_ERR(hda->clk_hddac);
	पूर्ण

	platक्रमm_set_drvdata(pdev, hda);

	वापस component_add(&pdev->dev, &sti_hda_ops);
पूर्ण

अटल पूर्णांक sti_hda_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sti_hda_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hda_of_match[] = अणु
	अणु .compatible = "st,stih416-hda", पूर्ण,
	अणु .compatible = "st,stih407-hda", पूर्ण,
	अणु /* end node */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hda_of_match);

काष्ठा platक्रमm_driver sti_hda_driver = अणु
	.driver = अणु
		.name = "sti-hda",
		.owner = THIS_MODULE,
		.of_match_table = hda_of_match,
	पूर्ण,
	.probe = sti_hda_probe,
	.हटाओ = sti_hda_हटाओ,
पूर्ण;

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SoC DRM driver");
MODULE_LICENSE("GPL");
