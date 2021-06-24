<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "sti_plane.h"
#समावेश "sti_vid.h"
#समावेश "sti_vtg.h"

/* Registers */
#घोषणा VID_CTL                 0x00
#घोषणा VID_ALP                 0x04
#घोषणा VID_CLF                 0x08
#घोषणा VID_VPO                 0x0C
#घोषणा VID_VPS                 0x10
#घोषणा VID_KEY1                0x28
#घोषणा VID_KEY2                0x2C
#घोषणा VID_MPR0                0x30
#घोषणा VID_MPR1                0x34
#घोषणा VID_MPR2                0x38
#घोषणा VID_MPR3                0x3C
#घोषणा VID_MST                 0x68
#घोषणा VID_BC                  0x70
#घोषणा VID_TINT                0x74
#घोषणा VID_CSAT                0x78

/* Registers values */
#घोषणा VID_CTL_IGNORE          (BIT(31) | BIT(30))
#घोषणा VID_CTL_PSI_ENABLE      (BIT(2) | BIT(1) | BIT(0))
#घोषणा VID_ALP_OPAQUE          0x00000080
#घोषणा VID_BC_DFLT             0x00008000
#घोषणा VID_TINT_DFLT           0x00000000
#घोषणा VID_CSAT_DFLT           0x00000080
/* YCbCr to RGB BT709:
 * R = Y+1.5391Cr
 * G = Y-0.4590Cr-0.1826Cb
 * B = Y+1.8125Cb */
#घोषणा VID_MPR0_BT709          0x0A800000
#घोषणा VID_MPR1_BT709          0x0AC50000
#घोषणा VID_MPR2_BT709          0x07150545
#घोषणा VID_MPR3_BT709          0x00000AE8
/* YCbCr to RGB BT709:
 * R = Y+1.3711Cr
 * G = Y-0.6992Cr-0.3359Cb
 * B = Y+1.7344Cb
 */
#घोषणा VID_MPR0_BT601          0x0A800000
#घोषणा VID_MPR1_BT601          0x0AAF0000
#घोषणा VID_MPR2_BT601          0x094E0754
#घोषणा VID_MPR3_BT601          0x00000ADD

#घोषणा VID_MIN_HD_HEIGHT       720

#घोषणा DBGFS_DUMP(reg) seq_म_लिखो(s, "\n  %-25s 0x%08X", #reg, \
				   पढ़ोl(vid->regs + reg))

अटल व्योम vid_dbg_ctl(काष्ठा seq_file *s, पूर्णांक val)
अणु
	val = val >> 30;
	seq_अ_दो(s, '\t');

	अगर (!(val & 1))
		seq_माला_दो(s, "NOT ");
	seq_माला_दो(s, "ignored on main mixer - ");

	अगर (!(val & 2))
		seq_माला_दो(s, "NOT ");
	seq_माला_दो(s, "ignored on aux mixer");
पूर्ण

अटल व्योम vid_dbg_vpo(काष्ठा seq_file *s, पूर्णांक val)
अणु
	seq_म_लिखो(s, "\txdo:%4d\tydo:%4d", val & 0x0FFF, (val >> 16) & 0x0FFF);
पूर्ण

अटल व्योम vid_dbg_vps(काष्ठा seq_file *s, पूर्णांक val)
अणु
	seq_म_लिखो(s, "\txds:%4d\tyds:%4d", val & 0x0FFF, (val >> 16) & 0x0FFF);
पूर्ण

अटल व्योम vid_dbg_mst(काष्ठा seq_file *s, पूर्णांक val)
अणु
	अगर (val & 1)
		seq_माला_दो(s, "\tBUFFER UNDERFLOW!");
पूर्ण

अटल पूर्णांक vid_dbg_show(काष्ठा seq_file *s, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_vid *vid = (काष्ठा sti_vid *)node->info_ent->data;

	seq_म_लिखो(s, "VID: (vaddr= 0x%p)", vid->regs);

	DBGFS_DUMP(VID_CTL);
	vid_dbg_ctl(s, पढ़ोl(vid->regs + VID_CTL));
	DBGFS_DUMP(VID_ALP);
	DBGFS_DUMP(VID_CLF);
	DBGFS_DUMP(VID_VPO);
	vid_dbg_vpo(s, पढ़ोl(vid->regs + VID_VPO));
	DBGFS_DUMP(VID_VPS);
	vid_dbg_vps(s, पढ़ोl(vid->regs + VID_VPS));
	DBGFS_DUMP(VID_KEY1);
	DBGFS_DUMP(VID_KEY2);
	DBGFS_DUMP(VID_MPR0);
	DBGFS_DUMP(VID_MPR1);
	DBGFS_DUMP(VID_MPR2);
	DBGFS_DUMP(VID_MPR3);
	DBGFS_DUMP(VID_MST);
	vid_dbg_mst(s, पढ़ोl(vid->regs + VID_MST));
	DBGFS_DUMP(VID_BC);
	DBGFS_DUMP(VID_TINT);
	DBGFS_DUMP(VID_CSAT);
	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list vid_debugfs_files[] = अणु
	अणु "vid", vid_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

व्योम vid_debugfs_init(काष्ठा sti_vid *vid, काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vid_debugfs_files); i++)
		vid_debugfs_files[i].data = vid;

	drm_debugfs_create_files(vid_debugfs_files,
				 ARRAY_SIZE(vid_debugfs_files),
				 minor->debugfs_root, minor);
पूर्ण

व्योम sti_vid_commit(काष्ठा sti_vid *vid,
		    काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_crtc *crtc = state->crtc;
	काष्ठा drm_display_mode *mode = &crtc->mode;
	पूर्णांक dst_x = state->crtc_x;
	पूर्णांक dst_y = state->crtc_y;
	पूर्णांक dst_w = clamp_val(state->crtc_w, 0, mode->hdisplay - dst_x);
	पूर्णांक dst_h = clamp_val(state->crtc_h, 0, mode->vdisplay - dst_y);
	पूर्णांक src_h = state->src_h >> 16;
	u32 val, yकरो, xकरो, yds, xds;

	/* Input / output size
	 * Align to upper even value */
	dst_w = ALIGN(dst_w, 2);
	dst_h = ALIGN(dst_h, 2);

	/* Unmask */
	val = पढ़ोl(vid->regs + VID_CTL);
	val &= ~VID_CTL_IGNORE;
	ग_लिखोl(val, vid->regs + VID_CTL);

	yकरो = sti_vtg_get_line_number(*mode, dst_y);
	yds = sti_vtg_get_line_number(*mode, dst_y + dst_h - 1);
	xकरो = sti_vtg_get_pixel_number(*mode, dst_x);
	xds = sti_vtg_get_pixel_number(*mode, dst_x + dst_w - 1);

	ग_लिखोl((yकरो << 16) | xकरो, vid->regs + VID_VPO);
	ग_लिखोl((yds << 16) | xds, vid->regs + VID_VPS);

	/* Color conversion parameters */
	अगर (src_h >= VID_MIN_HD_HEIGHT) अणु
		ग_लिखोl(VID_MPR0_BT709, vid->regs + VID_MPR0);
		ग_लिखोl(VID_MPR1_BT709, vid->regs + VID_MPR1);
		ग_लिखोl(VID_MPR2_BT709, vid->regs + VID_MPR2);
		ग_लिखोl(VID_MPR3_BT709, vid->regs + VID_MPR3);
	पूर्ण अन्यथा अणु
		ग_लिखोl(VID_MPR0_BT601, vid->regs + VID_MPR0);
		ग_लिखोl(VID_MPR1_BT601, vid->regs + VID_MPR1);
		ग_लिखोl(VID_MPR2_BT601, vid->regs + VID_MPR2);
		ग_लिखोl(VID_MPR3_BT601, vid->regs + VID_MPR3);
	पूर्ण
पूर्ण

व्योम sti_vid_disable(काष्ठा sti_vid *vid)
अणु
	u32 val;

	/* Mask */
	val = पढ़ोl(vid->regs + VID_CTL);
	val |= VID_CTL_IGNORE;
	ग_लिखोl(val, vid->regs + VID_CTL);
पूर्ण

अटल व्योम sti_vid_init(काष्ठा sti_vid *vid)
अणु
	/* Enable PSI, Mask layer */
	ग_लिखोl(VID_CTL_PSI_ENABLE | VID_CTL_IGNORE, vid->regs + VID_CTL);

	/* Opaque */
	ग_लिखोl(VID_ALP_OPAQUE, vid->regs + VID_ALP);

	/* Brightness, contrast, tपूर्णांक, saturation */
	ग_लिखोl(VID_BC_DFLT, vid->regs + VID_BC);
	ग_लिखोl(VID_TINT_DFLT, vid->regs + VID_TINT);
	ग_लिखोl(VID_CSAT_DFLT, vid->regs + VID_CSAT);
पूर्ण

काष्ठा sti_vid *sti_vid_create(काष्ठा device *dev, काष्ठा drm_device *drm_dev,
			       पूर्णांक id, व्योम __iomem *baseaddr)
अणु
	काष्ठा sti_vid *vid;

	vid = devm_kzalloc(dev, माप(*vid), GFP_KERNEL);
	अगर (!vid) अणु
		DRM_ERROR("Failed to allocate memory for VID\n");
		वापस शून्य;
	पूर्ण

	vid->dev = dev;
	vid->regs = baseaddr;
	vid->id = id;

	sti_vid_init(vid);

	वापस vid;
पूर्ण
