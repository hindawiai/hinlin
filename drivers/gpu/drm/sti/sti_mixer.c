<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "sti_compositor.h"
#समावेश "sti_mixer.h"
#समावेश "sti_vtg.h"

/* Module parameter to set the background color of the mixer */
अटल अचिन्हित पूर्णांक bkg_color = 0x000000;
MODULE_PARM_DESC(bkgcolor, "Value of the background color 0xRRGGBB");
module_param_named(bkgcolor, bkg_color, पूर्णांक, 0644);

/* regs offset */
#घोषणा GAM_MIXER_CTL      0x00
#घोषणा GAM_MIXER_BKC      0x04
#घोषणा GAM_MIXER_BCO      0x0C
#घोषणा GAM_MIXER_BCS      0x10
#घोषणा GAM_MIXER_AVO      0x28
#घोषणा GAM_MIXER_AVS      0x2C
#घोषणा GAM_MIXER_CRB      0x34
#घोषणा GAM_MIXER_ACT      0x38
#घोषणा GAM_MIXER_MBP      0x3C
#घोषणा GAM_MIXER_MX0      0x80

/* id क्रम depth of CRB reg */
#घोषणा GAM_DEPTH_VID0_ID  1
#घोषणा GAM_DEPTH_VID1_ID  2
#घोषणा GAM_DEPTH_GDP0_ID  3
#घोषणा GAM_DEPTH_GDP1_ID  4
#घोषणा GAM_DEPTH_GDP2_ID  5
#घोषणा GAM_DEPTH_GDP3_ID  6
#घोषणा GAM_DEPTH_MASK_ID  7

/* mask in CTL reg */
#घोषणा GAM_CTL_BACK_MASK  BIT(0)
#घोषणा GAM_CTL_VID0_MASK  BIT(1)
#घोषणा GAM_CTL_VID1_MASK  BIT(2)
#घोषणा GAM_CTL_GDP0_MASK  BIT(3)
#घोषणा GAM_CTL_GDP1_MASK  BIT(4)
#घोषणा GAM_CTL_GDP2_MASK  BIT(5)
#घोषणा GAM_CTL_GDP3_MASK  BIT(6)
#घोषणा GAM_CTL_CURSOR_MASK BIT(9)

स्थिर अक्षर *sti_mixer_to_str(काष्ठा sti_mixer *mixer)
अणु
	चयन (mixer->id) अणु
	हाल STI_MIXER_MAIN:
		वापस "MAIN_MIXER";
	हाल STI_MIXER_AUX:
		वापस "AUX_MIXER";
	शेष:
		वापस "<UNKNOWN MIXER>";
	पूर्ण
पूर्ण

अटल अंतरभूत u32 sti_mixer_reg_पढ़ो(काष्ठा sti_mixer *mixer, u32 reg_id)
अणु
	वापस पढ़ोl(mixer->regs + reg_id);
पूर्ण

अटल अंतरभूत व्योम sti_mixer_reg_ग_लिखो(काष्ठा sti_mixer *mixer,
				       u32 reg_id, u32 val)
अणु
	ग_लिखोl(val, mixer->regs + reg_id);
पूर्ण

#घोषणा DBGFS_DUMP(reg) seq_म_लिखो(s, "\n  %-25s 0x%08X", #reg, \
				   sti_mixer_reg_पढ़ो(mixer, reg))

अटल व्योम mixer_dbg_ctl(काष्ठा seq_file *s, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक count = 0;
	अक्षर *स्थिर disp_layer[] = अणु"BKG", "VID0", "VID1", "GDP0",
				    "GDP1", "GDP2", "GDP3"पूर्ण;

	seq_माला_दो(s, "\tEnabled: ");
	क्रम (i = 0; i < 7; i++) अणु
		अगर (val & 1) अणु
			seq_म_लिखो(s, "%s ", disp_layer[i]);
			count++;
		पूर्ण
		val = val >> 1;
	पूर्ण

	val = val >> 2;
	अगर (val & 1) अणु
		seq_माला_दो(s, "CURS ");
		count++;
	पूर्ण
	अगर (!count)
		seq_माला_दो(s, "Nothing");
पूर्ण

अटल व्योम mixer_dbg_crb(काष्ठा seq_file *s, पूर्णांक val)
अणु
	पूर्णांक i;

	seq_माला_दो(s, "\tDepth: ");
	क्रम (i = 0; i < GAM_MIXER_NB_DEPTH_LEVEL; i++) अणु
		चयन (val & GAM_DEPTH_MASK_ID) अणु
		हाल GAM_DEPTH_VID0_ID:
			seq_माला_दो(s, "VID0");
			अवरोध;
		हाल GAM_DEPTH_VID1_ID:
			seq_माला_दो(s, "VID1");
			अवरोध;
		हाल GAM_DEPTH_GDP0_ID:
			seq_माला_दो(s, "GDP0");
			अवरोध;
		हाल GAM_DEPTH_GDP1_ID:
			seq_माला_दो(s, "GDP1");
			अवरोध;
		हाल GAM_DEPTH_GDP2_ID:
			seq_माला_दो(s, "GDP2");
			अवरोध;
		हाल GAM_DEPTH_GDP3_ID:
			seq_माला_दो(s, "GDP3");
			अवरोध;
		शेष:
			seq_माला_दो(s, "---");
		पूर्ण

		अगर (i < GAM_MIXER_NB_DEPTH_LEVEL - 1)
			seq_माला_दो(s, " < ");
		val = val >> 3;
	पूर्ण
पूर्ण

अटल व्योम mixer_dbg_mxn(काष्ठा seq_file *s, व्योम *addr)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < 8; i++)
		seq_म_लिखो(s, "-0x%08X", (पूर्णांक)पढ़ोl(addr + i * 4));
पूर्ण

अटल पूर्णांक mixer_dbg_show(काष्ठा seq_file *s, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_mixer *mixer = (काष्ठा sti_mixer *)node->info_ent->data;

	seq_म_लिखो(s, "%s: (vaddr = 0x%p)",
		   sti_mixer_to_str(mixer), mixer->regs);

	DBGFS_DUMP(GAM_MIXER_CTL);
	mixer_dbg_ctl(s, sti_mixer_reg_पढ़ो(mixer, GAM_MIXER_CTL));
	DBGFS_DUMP(GAM_MIXER_BKC);
	DBGFS_DUMP(GAM_MIXER_BCO);
	DBGFS_DUMP(GAM_MIXER_BCS);
	DBGFS_DUMP(GAM_MIXER_AVO);
	DBGFS_DUMP(GAM_MIXER_AVS);
	DBGFS_DUMP(GAM_MIXER_CRB);
	mixer_dbg_crb(s, sti_mixer_reg_पढ़ो(mixer, GAM_MIXER_CRB));
	DBGFS_DUMP(GAM_MIXER_ACT);
	DBGFS_DUMP(GAM_MIXER_MBP);
	DBGFS_DUMP(GAM_MIXER_MX0);
	mixer_dbg_mxn(s, mixer->regs + GAM_MIXER_MX0);
	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list mixer0_debugfs_files[] = अणु
	अणु "mixer_main", mixer_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल काष्ठा drm_info_list mixer1_debugfs_files[] = अणु
	अणु "mixer_aux", mixer_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

व्योम sti_mixer_debugfs_init(काष्ठा sti_mixer *mixer, काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा drm_info_list *mixer_debugfs_files;
	पूर्णांक nb_files;

	चयन (mixer->id) अणु
	हाल STI_MIXER_MAIN:
		mixer_debugfs_files = mixer0_debugfs_files;
		nb_files = ARRAY_SIZE(mixer0_debugfs_files);
		अवरोध;
	हाल STI_MIXER_AUX:
		mixer_debugfs_files = mixer1_debugfs_files;
		nb_files = ARRAY_SIZE(mixer1_debugfs_files);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (i = 0; i < nb_files; i++)
		mixer_debugfs_files[i].data = mixer;

	drm_debugfs_create_files(mixer_debugfs_files,
				 nb_files,
				 minor->debugfs_root, minor);
पूर्ण

व्योम sti_mixer_set_background_status(काष्ठा sti_mixer *mixer, bool enable)
अणु
	u32 val = sti_mixer_reg_पढ़ो(mixer, GAM_MIXER_CTL);

	val &= ~GAM_CTL_BACK_MASK;
	val |= enable;
	sti_mixer_reg_ग_लिखो(mixer, GAM_MIXER_CTL, val);
पूर्ण

अटल व्योम sti_mixer_set_background_color(काष्ठा sti_mixer *mixer,
					   अचिन्हित पूर्णांक rgb)
अणु
	sti_mixer_reg_ग_लिखो(mixer, GAM_MIXER_BKC, rgb);
पूर्ण

अटल व्योम sti_mixer_set_background_area(काष्ठा sti_mixer *mixer,
					  काष्ठा drm_display_mode *mode)
अणु
	u32 yकरो, xकरो, yds, xds;

	yकरो = sti_vtg_get_line_number(*mode, 0);
	yds = sti_vtg_get_line_number(*mode, mode->vdisplay - 1);
	xकरो = sti_vtg_get_pixel_number(*mode, 0);
	xds = sti_vtg_get_pixel_number(*mode, mode->hdisplay - 1);

	sti_mixer_reg_ग_लिखो(mixer, GAM_MIXER_BCO, yकरो << 16 | xकरो);
	sti_mixer_reg_ग_लिखो(mixer, GAM_MIXER_BCS, yds << 16 | xds);
पूर्ण

पूर्णांक sti_mixer_set_plane_depth(काष्ठा sti_mixer *mixer, काष्ठा sti_plane *plane)
अणु
	पूर्णांक plane_id, depth = plane->drm_plane.state->normalized_zpos;
	अचिन्हित पूर्णांक i;
	u32 mask, val;

	चयन (plane->desc) अणु
	हाल STI_GDP_0:
		plane_id = GAM_DEPTH_GDP0_ID;
		अवरोध;
	हाल STI_GDP_1:
		plane_id = GAM_DEPTH_GDP1_ID;
		अवरोध;
	हाल STI_GDP_2:
		plane_id = GAM_DEPTH_GDP2_ID;
		अवरोध;
	हाल STI_GDP_3:
		plane_id = GAM_DEPTH_GDP3_ID;
		अवरोध;
	हाल STI_HQVDP_0:
		plane_id = GAM_DEPTH_VID0_ID;
		अवरोध;
	हाल STI_CURSOR:
		/* no need to set depth क्रम cursor */
		वापस 0;
	शेष:
		DRM_ERROR("Unknown plane %d\n", plane->desc);
		वापस 1;
	पूर्ण

	/* Search अगर a previous depth was alपढ़ोy asचिन्हित to the plane */
	val = sti_mixer_reg_पढ़ो(mixer, GAM_MIXER_CRB);
	क्रम (i = 0; i < GAM_MIXER_NB_DEPTH_LEVEL; i++) अणु
		mask = GAM_DEPTH_MASK_ID << (3 * i);
		अगर ((val & mask) == plane_id << (3 * i))
			अवरोध;
	पूर्ण

	mask |= GAM_DEPTH_MASK_ID << (3 * depth);
	plane_id = plane_id << (3 * depth);

	DRM_DEBUG_DRIVER("%s %s depth=%d\n", sti_mixer_to_str(mixer),
			 sti_plane_to_str(plane), depth);
	dev_dbg(mixer->dev, "GAM_MIXER_CRB val 0x%x mask 0x%x\n",
		plane_id, mask);

	val &= ~mask;
	val |= plane_id;
	sti_mixer_reg_ग_लिखो(mixer, GAM_MIXER_CRB, val);

	dev_dbg(mixer->dev, "Read GAM_MIXER_CRB 0x%x\n",
		sti_mixer_reg_पढ़ो(mixer, GAM_MIXER_CRB));
	वापस 0;
पूर्ण

पूर्णांक sti_mixer_active_video_area(काष्ठा sti_mixer *mixer,
				काष्ठा drm_display_mode *mode)
अणु
	u32 yकरो, xकरो, yds, xds;

	yकरो = sti_vtg_get_line_number(*mode, 0);
	yds = sti_vtg_get_line_number(*mode, mode->vdisplay - 1);
	xकरो = sti_vtg_get_pixel_number(*mode, 0);
	xds = sti_vtg_get_pixel_number(*mode, mode->hdisplay - 1);

	DRM_DEBUG_DRIVER("%s active video area xdo:%d ydo:%d xds:%d yds:%d\n",
			 sti_mixer_to_str(mixer), xकरो, yकरो, xds, yds);
	sti_mixer_reg_ग_लिखो(mixer, GAM_MIXER_AVO, yकरो << 16 | xकरो);
	sti_mixer_reg_ग_लिखो(mixer, GAM_MIXER_AVS, yds << 16 | xds);

	sti_mixer_set_background_color(mixer, bkg_color);

	sti_mixer_set_background_area(mixer, mode);
	sti_mixer_set_background_status(mixer, true);
	वापस 0;
पूर्ण

अटल u32 sti_mixer_get_plane_mask(काष्ठा sti_plane *plane)
अणु
	चयन (plane->desc) अणु
	हाल STI_BACK:
		वापस GAM_CTL_BACK_MASK;
	हाल STI_GDP_0:
		वापस GAM_CTL_GDP0_MASK;
	हाल STI_GDP_1:
		वापस GAM_CTL_GDP1_MASK;
	हाल STI_GDP_2:
		वापस GAM_CTL_GDP2_MASK;
	हाल STI_GDP_3:
		वापस GAM_CTL_GDP3_MASK;
	हाल STI_HQVDP_0:
		वापस GAM_CTL_VID0_MASK;
	हाल STI_CURSOR:
		वापस GAM_CTL_CURSOR_MASK;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक sti_mixer_set_plane_status(काष्ठा sti_mixer *mixer,
			       काष्ठा sti_plane *plane, bool status)
अणु
	u32 mask, val;

	DRM_DEBUG_DRIVER("%s %s %s\n", status ? "enable" : "disable",
			 sti_mixer_to_str(mixer), sti_plane_to_str(plane));

	mask = sti_mixer_get_plane_mask(plane);
	अगर (!mask) अणु
		DRM_ERROR("Can't find layer mask\n");
		वापस -EINVAL;
	पूर्ण

	val = sti_mixer_reg_पढ़ो(mixer, GAM_MIXER_CTL);
	val &= ~mask;
	val |= status ? mask : 0;
	sti_mixer_reg_ग_लिखो(mixer, GAM_MIXER_CTL, val);

	वापस 0;
पूर्ण

काष्ठा sti_mixer *sti_mixer_create(काष्ठा device *dev,
				   काष्ठा drm_device *drm_dev,
				   पूर्णांक id,
				   व्योम __iomem *baseaddr)
अणु
	काष्ठा sti_mixer *mixer = devm_kzalloc(dev, माप(*mixer), GFP_KERNEL);

	dev_dbg(dev, "%s\n", __func__);
	अगर (!mixer) अणु
		DRM_ERROR("Failed to allocated memory for mixer\n");
		वापस शून्य;
	पूर्ण
	mixer->regs = baseaddr;
	mixer->dev = dev;
	mixer->id = id;

	DRM_DEBUG_DRIVER("%s created. Regs=%p\n",
			 sti_mixer_to_str(mixer), mixer->regs);

	वापस mixer;
पूर्ण
