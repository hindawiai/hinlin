<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>

#समावेश "sti_compositor.h"
#समावेश "sti_gdp.h"
#समावेश "sti_plane.h"
#समावेश "sti_vtg.h"

#घोषणा ALPHASWITCH     BIT(6)
#घोषणा ENA_COLOR_FILL  BIT(8)
#घोषणा BIGNOTLITTLE    BIT(23)
#घोषणा WAIT_NEXT_VSYNC BIT(31)

/* GDP color क्रमmats */
#घोषणा GDP_RGB565      0x00
#घोषणा GDP_RGB888      0x01
#घोषणा GDP_RGB888_32   0x02
#घोषणा GDP_XBGR8888    (GDP_RGB888_32 | BIGNOTLITTLE | ALPHASWITCH)
#घोषणा GDP_ARGB8565    0x04
#घोषणा GDP_ARGB8888    0x05
#घोषणा GDP_ABGR8888    (GDP_ARGB8888 | BIGNOTLITTLE | ALPHASWITCH)
#घोषणा GDP_ARGB1555    0x06
#घोषणा GDP_ARGB4444    0x07

#घोषणा GDP2STR(fmt) अणु GDP_ ## fmt, #fmt पूर्ण

अटल काष्ठा gdp_क्रमmat_to_str अणु
	पूर्णांक क्रमmat;
	अक्षर name[20];
पूर्ण gdp_क्रमmat_to_str[] = अणु
		GDP2STR(RGB565),
		GDP2STR(RGB888),
		GDP2STR(RGB888_32),
		GDP2STR(XBGR8888),
		GDP2STR(ARGB8565),
		GDP2STR(ARGB8888),
		GDP2STR(ABGR8888),
		GDP2STR(ARGB1555),
		GDP2STR(ARGB4444)
		पूर्ण;

#घोषणा GAM_GDP_CTL_OFFSET      0x00
#घोषणा GAM_GDP_AGC_OFFSET      0x04
#घोषणा GAM_GDP_VPO_OFFSET      0x0C
#घोषणा GAM_GDP_VPS_OFFSET      0x10
#घोषणा GAM_GDP_PML_OFFSET      0x14
#घोषणा GAM_GDP_PMP_OFFSET      0x18
#घोषणा GAM_GDP_SIZE_OFFSET     0x1C
#घोषणा GAM_GDP_NVN_OFFSET      0x24
#घोषणा GAM_GDP_KEY1_OFFSET     0x28
#घोषणा GAM_GDP_KEY2_OFFSET     0x2C
#घोषणा GAM_GDP_PPT_OFFSET      0x34
#घोषणा GAM_GDP_CML_OFFSET      0x3C
#घोषणा GAM_GDP_MST_OFFSET      0x68

#घोषणा GAM_GDP_ALPHARANGE_255  BIT(5)
#घोषणा GAM_GDP_AGC_FULL_RANGE  0x00808080
#घोषणा GAM_GDP_PPT_IGNORE      (BIT(1) | BIT(0))

#घोषणा GAM_GDP_SIZE_MAX_WIDTH  3840
#घोषणा GAM_GDP_SIZE_MAX_HEIGHT 2160

#घोषणा GDP_NODE_NB_BANK        2
#घोषणा GDP_NODE_PER_FIELD      2

काष्ठा sti_gdp_node अणु
	u32 gam_gdp_ctl;
	u32 gam_gdp_agc;
	u32 reserved1;
	u32 gam_gdp_vpo;
	u32 gam_gdp_vps;
	u32 gam_gdp_pml;
	u32 gam_gdp_pmp;
	u32 gam_gdp_size;
	u32 reserved2;
	u32 gam_gdp_nvn;
	u32 gam_gdp_key1;
	u32 gam_gdp_key2;
	u32 reserved3;
	u32 gam_gdp_ppt;
	u32 reserved4;
	u32 gam_gdp_cml;
पूर्ण;

काष्ठा sti_gdp_node_list अणु
	काष्ठा sti_gdp_node *top_field;
	dma_addr_t top_field_paddr;
	काष्ठा sti_gdp_node *bपंचांग_field;
	dma_addr_t bपंचांग_field_paddr;
पूर्ण;

/*
 * STI GDP काष्ठाure
 *
 * @sti_plane:          sti_plane काष्ठाure
 * @dev:                driver device
 * @regs:               gdp रेजिस्टरs
 * @clk_pix:            pixel घड़ी क्रम the current gdp
 * @clk_मुख्य_parent:    gdp parent घड़ी अगर मुख्य path used
 * @clk_aux_parent:     gdp parent घड़ी अगर aux path used
 * @vtg_field_nb:       callback क्रम VTG FIELD (top or bottom) notअगरication
 * @is_curr_top:        true अगर the current node processed is the top field
 * @node_list:          array of node list
 * @vtg:                रेजिस्टरed vtg
 */
काष्ठा sti_gdp अणु
	काष्ठा sti_plane plane;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा clk *clk_pix;
	काष्ठा clk *clk_मुख्य_parent;
	काष्ठा clk *clk_aux_parent;
	काष्ठा notअगरier_block vtg_field_nb;
	bool is_curr_top;
	काष्ठा sti_gdp_node_list node_list[GDP_NODE_NB_BANK];
	काष्ठा sti_vtg *vtg;
पूर्ण;

#घोषणा to_sti_gdp(x) container_of(x, काष्ठा sti_gdp, plane)

अटल स्थिर uपूर्णांक32_t gdp_supported_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
पूर्ण;

#घोषणा DBGFS_DUMP(reg) seq_म_लिखो(s, "\n  %-25s 0x%08X", #reg, \
				   पढ़ोl(gdp->regs + reg ## _OFFSET))

अटल व्योम gdp_dbg_ctl(काष्ठा seq_file *s, पूर्णांक val)
अणु
	पूर्णांक i;

	seq_माला_दो(s, "\tColor:");
	क्रम (i = 0; i < ARRAY_SIZE(gdp_क्रमmat_to_str); i++) अणु
		अगर (gdp_क्रमmat_to_str[i].क्रमmat == (val & 0x1F)) अणु
			seq_माला_दो(s, gdp_क्रमmat_to_str[i].name);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(gdp_क्रमmat_to_str))
		seq_माला_दो(s, "<UNKNOWN>");

	seq_म_लिखो(s, "\tWaitNextVsync:%d", val & WAIT_NEXT_VSYNC ? 1 : 0);
पूर्ण

अटल व्योम gdp_dbg_vpo(काष्ठा seq_file *s, पूर्णांक val)
अणु
	seq_म_लिखो(s, "\txdo:%4d\tydo:%4d", val & 0xFFFF, (val >> 16) & 0xFFFF);
पूर्ण

अटल व्योम gdp_dbg_vps(काष्ठा seq_file *s, पूर्णांक val)
अणु
	seq_म_लिखो(s, "\txds:%4d\tyds:%4d", val & 0xFFFF, (val >> 16) & 0xFFFF);
पूर्ण

अटल व्योम gdp_dbg_size(काष्ठा seq_file *s, पूर्णांक val)
अणु
	seq_म_लिखो(s, "\t%d x %d", val & 0xFFFF, (val >> 16) & 0xFFFF);
पूर्ण

अटल व्योम gdp_dbg_nvn(काष्ठा seq_file *s, काष्ठा sti_gdp *gdp, पूर्णांक val)
अणु
	व्योम *base = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < GDP_NODE_NB_BANK; i++) अणु
		अगर (gdp->node_list[i].top_field_paddr == val) अणु
			base = gdp->node_list[i].top_field;
			अवरोध;
		पूर्ण
		अगर (gdp->node_list[i].bपंचांग_field_paddr == val) अणु
			base = gdp->node_list[i].bपंचांग_field;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (base)
		seq_म_लिखो(s, "\tVirt @: %p", base);
पूर्ण

अटल व्योम gdp_dbg_ppt(काष्ठा seq_file *s, पूर्णांक val)
अणु
	अगर (val & GAM_GDP_PPT_IGNORE)
		seq_माला_दो(s, "\tNot displayed on mixer!");
पूर्ण

अटल व्योम gdp_dbg_mst(काष्ठा seq_file *s, पूर्णांक val)
अणु
	अगर (val & 1)
		seq_माला_दो(s, "\tBUFFER UNDERFLOW!");
पूर्ण

अटल पूर्णांक gdp_dbg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_gdp *gdp = (काष्ठा sti_gdp *)node->info_ent->data;
	काष्ठा drm_plane *drm_plane = &gdp->plane.drm_plane;
	काष्ठा drm_crtc *crtc;

	drm_modeset_lock(&drm_plane->mutex, शून्य);
	crtc = drm_plane->state->crtc;
	drm_modeset_unlock(&drm_plane->mutex);

	seq_म_लिखो(s, "%s: (vaddr = 0x%p)",
		   sti_plane_to_str(&gdp->plane), gdp->regs);

	DBGFS_DUMP(GAM_GDP_CTL);
	gdp_dbg_ctl(s, पढ़ोl(gdp->regs + GAM_GDP_CTL_OFFSET));
	DBGFS_DUMP(GAM_GDP_AGC);
	DBGFS_DUMP(GAM_GDP_VPO);
	gdp_dbg_vpo(s, पढ़ोl(gdp->regs + GAM_GDP_VPO_OFFSET));
	DBGFS_DUMP(GAM_GDP_VPS);
	gdp_dbg_vps(s, पढ़ोl(gdp->regs + GAM_GDP_VPS_OFFSET));
	DBGFS_DUMP(GAM_GDP_PML);
	DBGFS_DUMP(GAM_GDP_PMP);
	DBGFS_DUMP(GAM_GDP_SIZE);
	gdp_dbg_size(s, पढ़ोl(gdp->regs + GAM_GDP_SIZE_OFFSET));
	DBGFS_DUMP(GAM_GDP_NVN);
	gdp_dbg_nvn(s, gdp, पढ़ोl(gdp->regs + GAM_GDP_NVN_OFFSET));
	DBGFS_DUMP(GAM_GDP_KEY1);
	DBGFS_DUMP(GAM_GDP_KEY2);
	DBGFS_DUMP(GAM_GDP_PPT);
	gdp_dbg_ppt(s, पढ़ोl(gdp->regs + GAM_GDP_PPT_OFFSET));
	DBGFS_DUMP(GAM_GDP_CML);
	DBGFS_DUMP(GAM_GDP_MST);
	gdp_dbg_mst(s, पढ़ोl(gdp->regs + GAM_GDP_MST_OFFSET));

	seq_माला_दो(s, "\n\n");
	अगर (!crtc)
		seq_माला_दो(s, "  Not connected to any DRM CRTC\n");
	अन्यथा
		seq_म_लिखो(s, "  Connected to DRM CRTC #%d (%s)\n",
			   crtc->base.id, sti_mixer_to_str(to_sti_mixer(crtc)));

	वापस 0;
पूर्ण

अटल व्योम gdp_node_dump_node(काष्ठा seq_file *s, काष्ठा sti_gdp_node *node)
अणु
	seq_म_लिखो(s, "\t@:0x%p", node);
	seq_म_लिखो(s, "\n\tCTL  0x%08X", node->gam_gdp_ctl);
	gdp_dbg_ctl(s, node->gam_gdp_ctl);
	seq_म_लिखो(s, "\n\tAGC  0x%08X", node->gam_gdp_agc);
	seq_म_लिखो(s, "\n\tVPO  0x%08X", node->gam_gdp_vpo);
	gdp_dbg_vpo(s, node->gam_gdp_vpo);
	seq_म_लिखो(s, "\n\tVPS  0x%08X", node->gam_gdp_vps);
	gdp_dbg_vps(s, node->gam_gdp_vps);
	seq_म_लिखो(s, "\n\tPML  0x%08X", node->gam_gdp_pml);
	seq_म_लिखो(s, "\n\tPMP  0x%08X", node->gam_gdp_pmp);
	seq_म_लिखो(s, "\n\tSIZE 0x%08X", node->gam_gdp_size);
	gdp_dbg_size(s, node->gam_gdp_size);
	seq_म_लिखो(s, "\n\tNVN  0x%08X", node->gam_gdp_nvn);
	seq_म_लिखो(s, "\n\tKEY1 0x%08X", node->gam_gdp_key1);
	seq_म_लिखो(s, "\n\tKEY2 0x%08X", node->gam_gdp_key2);
	seq_म_लिखो(s, "\n\tPPT  0x%08X", node->gam_gdp_ppt);
	gdp_dbg_ppt(s, node->gam_gdp_ppt);
	seq_म_लिखो(s, "\n\tCML  0x%08X\n", node->gam_gdp_cml);
पूर्ण

अटल पूर्णांक gdp_node_dbg_show(काष्ठा seq_file *s, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_gdp *gdp = (काष्ठा sti_gdp *)node->info_ent->data;
	अचिन्हित पूर्णांक b;

	क्रम (b = 0; b < GDP_NODE_NB_BANK; b++) अणु
		seq_म_लिखो(s, "\n%s[%d].top", sti_plane_to_str(&gdp->plane), b);
		gdp_node_dump_node(s, gdp->node_list[b].top_field);
		seq_म_लिखो(s, "\n%s[%d].btm", sti_plane_to_str(&gdp->plane), b);
		gdp_node_dump_node(s, gdp->node_list[b].bपंचांग_field);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list gdp0_debugfs_files[] = अणु
	अणु "gdp0", gdp_dbg_show, 0, शून्य पूर्ण,
	अणु "gdp0_node", gdp_node_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल काष्ठा drm_info_list gdp1_debugfs_files[] = अणु
	अणु "gdp1", gdp_dbg_show, 0, शून्य पूर्ण,
	अणु "gdp1_node", gdp_node_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल काष्ठा drm_info_list gdp2_debugfs_files[] = अणु
	अणु "gdp2", gdp_dbg_show, 0, शून्य पूर्ण,
	अणु "gdp2_node", gdp_node_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल काष्ठा drm_info_list gdp3_debugfs_files[] = अणु
	अणु "gdp3", gdp_dbg_show, 0, शून्य पूर्ण,
	अणु "gdp3_node", gdp_node_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल पूर्णांक gdp_debugfs_init(काष्ठा sti_gdp *gdp, काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा drm_info_list *gdp_debugfs_files;
	पूर्णांक nb_files;

	चयन (gdp->plane.desc) अणु
	हाल STI_GDP_0:
		gdp_debugfs_files = gdp0_debugfs_files;
		nb_files = ARRAY_SIZE(gdp0_debugfs_files);
		अवरोध;
	हाल STI_GDP_1:
		gdp_debugfs_files = gdp1_debugfs_files;
		nb_files = ARRAY_SIZE(gdp1_debugfs_files);
		अवरोध;
	हाल STI_GDP_2:
		gdp_debugfs_files = gdp2_debugfs_files;
		nb_files = ARRAY_SIZE(gdp2_debugfs_files);
		अवरोध;
	हाल STI_GDP_3:
		gdp_debugfs_files = gdp3_debugfs_files;
		nb_files = ARRAY_SIZE(gdp3_debugfs_files);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < nb_files; i++)
		gdp_debugfs_files[i].data = gdp;

	drm_debugfs_create_files(gdp_debugfs_files,
				 nb_files,
				 minor->debugfs_root, minor);
	वापस 0;
पूर्ण

अटल पूर्णांक sti_gdp_fourcc2क्रमmat(पूर्णांक fourcc)
अणु
	चयन (fourcc) अणु
	हाल DRM_FORMAT_XRGB8888:
		वापस GDP_RGB888_32;
	हाल DRM_FORMAT_XBGR8888:
		वापस GDP_XBGR8888;
	हाल DRM_FORMAT_ARGB8888:
		वापस GDP_ARGB8888;
	हाल DRM_FORMAT_ABGR8888:
		वापस GDP_ABGR8888;
	हाल DRM_FORMAT_ARGB4444:
		वापस GDP_ARGB4444;
	हाल DRM_FORMAT_ARGB1555:
		वापस GDP_ARGB1555;
	हाल DRM_FORMAT_RGB565:
		वापस GDP_RGB565;
	हाल DRM_FORMAT_RGB888:
		वापस GDP_RGB888;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक sti_gdp_get_alpharange(पूर्णांक क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल GDP_ARGB8565:
	हाल GDP_ARGB8888:
	हाल GDP_ABGR8888:
		वापस GAM_GDP_ALPHARANGE_255;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * sti_gdp_get_मुक्त_nodes
 * @gdp: gdp poपूर्णांकer
 *
 * Look क्रम a GDP node list that is not currently पढ़ो by the HW.
 *
 * RETURNS:
 * Poपूर्णांकer to the मुक्त GDP node list
 */
अटल काष्ठा sti_gdp_node_list *sti_gdp_get_मुक्त_nodes(काष्ठा sti_gdp *gdp)
अणु
	पूर्णांक hw_nvn;
	अचिन्हित पूर्णांक i;

	hw_nvn = पढ़ोl(gdp->regs + GAM_GDP_NVN_OFFSET);
	अगर (!hw_nvn)
		जाओ end;

	क्रम (i = 0; i < GDP_NODE_NB_BANK; i++)
		अगर ((hw_nvn != gdp->node_list[i].bपंचांग_field_paddr) &&
		    (hw_nvn != gdp->node_list[i].top_field_paddr))
			वापस &gdp->node_list[i];

	/* in hazardious हालs restart with the first node */
	DRM_ERROR("inconsistent NVN for %s: 0x%08X\n",
			sti_plane_to_str(&gdp->plane), hw_nvn);

end:
	वापस &gdp->node_list[0];
पूर्ण

/**
 * sti_gdp_get_current_nodes
 * @gdp: gdp poपूर्णांकer
 *
 * Look क्रम GDP nodes that are currently पढ़ो by the HW.
 *
 * RETURNS:
 * Poपूर्णांकer to the current GDP node list
 */
अटल
काष्ठा sti_gdp_node_list *sti_gdp_get_current_nodes(काष्ठा sti_gdp *gdp)
अणु
	पूर्णांक hw_nvn;
	अचिन्हित पूर्णांक i;

	hw_nvn = पढ़ोl(gdp->regs + GAM_GDP_NVN_OFFSET);
	अगर (!hw_nvn)
		जाओ end;

	क्रम (i = 0; i < GDP_NODE_NB_BANK; i++)
		अगर ((hw_nvn == gdp->node_list[i].bपंचांग_field_paddr) ||
				(hw_nvn == gdp->node_list[i].top_field_paddr))
			वापस &gdp->node_list[i];

end:
	DRM_DEBUG_DRIVER("Warning, NVN 0x%08X for %s does not match any node\n",
				hw_nvn, sti_plane_to_str(&gdp->plane));

	वापस शून्य;
पूर्ण

/**
 * sti_gdp_disable
 * @gdp: gdp poपूर्णांकer
 *
 * Disable a GDP.
 */
अटल व्योम sti_gdp_disable(काष्ठा sti_gdp *gdp)
अणु
	अचिन्हित पूर्णांक i;

	DRM_DEBUG_DRIVER("%s\n", sti_plane_to_str(&gdp->plane));

	/* Set the nodes as 'to be ignored on mixer' */
	क्रम (i = 0; i < GDP_NODE_NB_BANK; i++) अणु
		gdp->node_list[i].top_field->gam_gdp_ppt |= GAM_GDP_PPT_IGNORE;
		gdp->node_list[i].bपंचांग_field->gam_gdp_ppt |= GAM_GDP_PPT_IGNORE;
	पूर्ण

	अगर (sti_vtg_unरेजिस्टर_client(gdp->vtg, &gdp->vtg_field_nb))
		DRM_DEBUG_DRIVER("Warning: cannot unregister VTG notifier\n");

	अगर (gdp->clk_pix)
		clk_disable_unprepare(gdp->clk_pix);

	gdp->plane.status = STI_PLANE_DISABLED;
	gdp->vtg = शून्य;
पूर्ण

/**
 * sti_gdp_field_cb
 * @nb: notअगरier block
 * @event: event message
 * @data: निजी data
 *
 * Handle VTG top field and bottom field event.
 *
 * RETURNS:
 * 0 on success.
 */
अटल पूर्णांक sti_gdp_field_cb(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा sti_gdp *gdp = container_of(nb, काष्ठा sti_gdp, vtg_field_nb);

	अगर (gdp->plane.status == STI_PLANE_FLUSHING) अणु
		/* disable need to be synchronize on vsync event */
		DRM_DEBUG_DRIVER("Vsync event received => disable %s\n",
				 sti_plane_to_str(&gdp->plane));

		sti_gdp_disable(gdp);
	पूर्ण

	चयन (event) अणु
	हाल VTG_TOP_FIELD_EVENT:
		gdp->is_curr_top = true;
		अवरोध;
	हाल VTG_BOTTOM_FIELD_EVENT:
		gdp->is_curr_top = false;
		अवरोध;
	शेष:
		DRM_ERROR("unsupported event: %lu\n", event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sti_gdp_init(काष्ठा sti_gdp *gdp)
अणु
	काष्ठा device_node *np = gdp->dev->of_node;
	dma_addr_t dma_addr;
	व्योम *base;
	अचिन्हित पूर्णांक i, size;

	/* Allocate all the nodes within a single memory page */
	size = माप(काष्ठा sti_gdp_node) *
	    GDP_NODE_PER_FIELD * GDP_NODE_NB_BANK;
	base = dma_alloc_wc(gdp->dev, size, &dma_addr, GFP_KERNEL);

	अगर (!base) अणु
		DRM_ERROR("Failed to allocate memory for GDP node\n");
		वापस;
	पूर्ण
	स_रखो(base, 0, size);

	क्रम (i = 0; i < GDP_NODE_NB_BANK; i++) अणु
		अगर (dma_addr & 0xF) अणु
			DRM_ERROR("Mem alignment failed\n");
			वापस;
		पूर्ण
		gdp->node_list[i].top_field = base;
		gdp->node_list[i].top_field_paddr = dma_addr;

		DRM_DEBUG_DRIVER("node[%d].top_field=%p\n", i, base);
		base += माप(काष्ठा sti_gdp_node);
		dma_addr += माप(काष्ठा sti_gdp_node);

		अगर (dma_addr & 0xF) अणु
			DRM_ERROR("Mem alignment failed\n");
			वापस;
		पूर्ण
		gdp->node_list[i].bपंचांग_field = base;
		gdp->node_list[i].bपंचांग_field_paddr = dma_addr;
		DRM_DEBUG_DRIVER("node[%d].btm_field=%p\n", i, base);
		base += माप(काष्ठा sti_gdp_node);
		dma_addr += माप(काष्ठा sti_gdp_node);
	पूर्ण

	अगर (of_device_is_compatible(np, "st,stih407-compositor")) अणु
		/* GDP of STiH407 chip have its own pixel घड़ी */
		अक्षर *clk_name;

		चयन (gdp->plane.desc) अणु
		हाल STI_GDP_0:
			clk_name = "pix_gdp1";
			अवरोध;
		हाल STI_GDP_1:
			clk_name = "pix_gdp2";
			अवरोध;
		हाल STI_GDP_2:
			clk_name = "pix_gdp3";
			अवरोध;
		हाल STI_GDP_3:
			clk_name = "pix_gdp4";
			अवरोध;
		शेष:
			DRM_ERROR("GDP id not recognized\n");
			वापस;
		पूर्ण

		gdp->clk_pix = devm_clk_get(gdp->dev, clk_name);
		अगर (IS_ERR(gdp->clk_pix))
			DRM_ERROR("Cannot get %s clock\n", clk_name);

		gdp->clk_मुख्य_parent = devm_clk_get(gdp->dev, "main_parent");
		अगर (IS_ERR(gdp->clk_मुख्य_parent))
			DRM_ERROR("Cannot get main_parent clock\n");

		gdp->clk_aux_parent = devm_clk_get(gdp->dev, "aux_parent");
		अगर (IS_ERR(gdp->clk_aux_parent))
			DRM_ERROR("Cannot get aux_parent clock\n");
	पूर्ण
पूर्ण

/**
 * sti_gdp_get_dst
 * @dev: device
 * @dst: requested destination size
 * @src: source size
 *
 * Return the cropped / clamped destination size
 *
 * RETURNS:
 * cropped / clamped destination size
 */
अटल पूर्णांक sti_gdp_get_dst(काष्ठा device *dev, पूर्णांक dst, पूर्णांक src)
अणु
	अगर (dst == src)
		वापस dst;

	अगर (dst < src) अणु
		dev_dbg(dev, "WARNING: GDP scale not supported, will crop\n");
		वापस dst;
	पूर्ण

	dev_dbg(dev, "WARNING: GDP scale not supported, will clamp\n");
	वापस src;
पूर्ण

अटल पूर्णांक sti_gdp_atomic_check(काष्ठा drm_plane *drm_plane,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 drm_plane);
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_gdp *gdp = to_sti_gdp(plane);
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	काष्ठा drm_framebuffer *fb =  new_plane_state->fb;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा sti_mixer *mixer;
	काष्ठा drm_display_mode *mode;
	पूर्णांक dst_x, dst_y, dst_w, dst_h;
	पूर्णांक src_x, src_y, src_w, src_h;
	पूर्णांक क्रमmat;

	/* no need क्रम further checks अगर the plane is being disabled */
	अगर (!crtc || !fb)
		वापस 0;

	mixer = to_sti_mixer(crtc);
	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	mode = &crtc_state->mode;
	dst_x = new_plane_state->crtc_x;
	dst_y = new_plane_state->crtc_y;
	dst_w = clamp_val(new_plane_state->crtc_w, 0, mode->hdisplay - dst_x);
	dst_h = clamp_val(new_plane_state->crtc_h, 0, mode->vdisplay - dst_y);
	/* src_x are in 16.16 क्रमmat */
	src_x = new_plane_state->src_x >> 16;
	src_y = new_plane_state->src_y >> 16;
	src_w = clamp_val(new_plane_state->src_w >> 16, 0,
			  GAM_GDP_SIZE_MAX_WIDTH);
	src_h = clamp_val(new_plane_state->src_h >> 16, 0,
			  GAM_GDP_SIZE_MAX_HEIGHT);

	क्रमmat = sti_gdp_fourcc2क्रमmat(fb->क्रमmat->क्रमmat);
	अगर (क्रमmat == -1) अणु
		DRM_ERROR("Format not supported by GDP %.4s\n",
			  (अक्षर *)&fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (!drm_fb_cma_get_gem_obj(fb, 0)) अणु
		DRM_ERROR("Can't get CMA GEM object for fb\n");
		वापस -EINVAL;
	पूर्ण

	/* Set gdp घड़ी */
	अगर (mode->घड़ी && gdp->clk_pix) अणु
		काष्ठा clk *clkp;
		पूर्णांक rate = mode->घड़ी * 1000;
		पूर्णांक res;

		/*
		 * According to the mixer used, the gdp pixel घड़ी
		 * should have a dअगरferent parent घड़ी.
		 */
		अगर (mixer->id == STI_MIXER_MAIN)
			clkp = gdp->clk_मुख्य_parent;
		अन्यथा
			clkp = gdp->clk_aux_parent;

		अगर (clkp)
			clk_set_parent(gdp->clk_pix, clkp);

		res = clk_set_rate(gdp->clk_pix, rate);
		अगर (res < 0) अणु
			DRM_ERROR("Cannot set rate (%dHz) for gdp\n",
				  rate);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	DRM_DEBUG_KMS("CRTC:%d (%s) drm plane:%d (%s)\n",
		      crtc->base.id, sti_mixer_to_str(mixer),
		      drm_plane->base.id, sti_plane_to_str(plane));
	DRM_DEBUG_KMS("%s dst=(%dx%d)@(%d,%d) - src=(%dx%d)@(%d,%d)\n",
		      sti_plane_to_str(plane),
		      dst_w, dst_h, dst_x, dst_y,
		      src_w, src_h, src_x, src_y);

	वापस 0;
पूर्ण

अटल व्योम sti_gdp_atomic_update(काष्ठा drm_plane *drm_plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *oldstate = drm_atomic_get_old_plane_state(state,
									  drm_plane);
	काष्ठा drm_plane_state *newstate = drm_atomic_get_new_plane_state(state,
									  drm_plane);
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_gdp *gdp = to_sti_gdp(plane);
	काष्ठा drm_crtc *crtc = newstate->crtc;
	काष्ठा drm_framebuffer *fb =  newstate->fb;
	काष्ठा drm_display_mode *mode;
	पूर्णांक dst_x, dst_y, dst_w, dst_h;
	पूर्णांक src_x, src_y, src_w, src_h;
	काष्ठा drm_gem_cma_object *cma_obj;
	काष्ठा sti_gdp_node_list *list;
	काष्ठा sti_gdp_node_list *curr_list;
	काष्ठा sti_gdp_node *top_field, *bपंचांग_field;
	u32 dma_updated_top;
	u32 dma_updated_bपंचांग;
	पूर्णांक क्रमmat;
	अचिन्हित पूर्णांक bpp;
	u32 yकरो, xकरो, yds, xds;

	अगर (!crtc || !fb)
		वापस;

	अगर ((oldstate->fb == newstate->fb) &&
	    (oldstate->crtc_x == newstate->crtc_x) &&
	    (oldstate->crtc_y == newstate->crtc_y) &&
	    (oldstate->crtc_w == newstate->crtc_w) &&
	    (oldstate->crtc_h == newstate->crtc_h) &&
	    (oldstate->src_x == newstate->src_x) &&
	    (oldstate->src_y == newstate->src_y) &&
	    (oldstate->src_w == newstate->src_w) &&
	    (oldstate->src_h == newstate->src_h)) अणु
		/* No change since last update, करो not post cmd */
		DRM_DEBUG_DRIVER("No change, not posting cmd\n");
		plane->status = STI_PLANE_UPDATED;
		वापस;
	पूर्ण

	अगर (!gdp->vtg) अणु
		काष्ठा sti_compositor *compo = dev_get_drvdata(gdp->dev);
		काष्ठा sti_mixer *mixer = to_sti_mixer(crtc);

		/* Register gdp callback */
		gdp->vtg = compo->vtg[mixer->id];
		sti_vtg_रेजिस्टर_client(gdp->vtg, &gdp->vtg_field_nb, crtc);
		clk_prepare_enable(gdp->clk_pix);
	पूर्ण

	mode = &crtc->mode;
	dst_x = newstate->crtc_x;
	dst_y = newstate->crtc_y;
	dst_w = clamp_val(newstate->crtc_w, 0, mode->hdisplay - dst_x);
	dst_h = clamp_val(newstate->crtc_h, 0, mode->vdisplay - dst_y);
	/* src_x are in 16.16 क्रमmat */
	src_x = newstate->src_x >> 16;
	src_y = newstate->src_y >> 16;
	src_w = clamp_val(newstate->src_w >> 16, 0, GAM_GDP_SIZE_MAX_WIDTH);
	src_h = clamp_val(newstate->src_h >> 16, 0, GAM_GDP_SIZE_MAX_HEIGHT);

	list = sti_gdp_get_मुक्त_nodes(gdp);
	top_field = list->top_field;
	bपंचांग_field = list->bपंचांग_field;

	dev_dbg(gdp->dev, "%s %s top_node:0x%p btm_node:0x%p\n", __func__,
		sti_plane_to_str(plane), top_field, bपंचांग_field);

	/* build the top field */
	top_field->gam_gdp_agc = GAM_GDP_AGC_FULL_RANGE;
	top_field->gam_gdp_ctl = WAIT_NEXT_VSYNC;
	क्रमmat = sti_gdp_fourcc2क्रमmat(fb->क्रमmat->क्रमmat);
	top_field->gam_gdp_ctl |= क्रमmat;
	top_field->gam_gdp_ctl |= sti_gdp_get_alpharange(क्रमmat);
	top_field->gam_gdp_ppt &= ~GAM_GDP_PPT_IGNORE;

	cma_obj = drm_fb_cma_get_gem_obj(fb, 0);

	DRM_DEBUG_DRIVER("drm FB:%d format:%.4s phys@:0x%lx\n", fb->base.id,
			 (अक्षर *)&fb->क्रमmat->क्रमmat,
			 (अचिन्हित दीर्घ)cma_obj->paddr);

	/* pixel memory location */
	bpp = fb->क्रमmat->cpp[0];
	top_field->gam_gdp_pml = (u32)cma_obj->paddr + fb->offsets[0];
	top_field->gam_gdp_pml += src_x * bpp;
	top_field->gam_gdp_pml += src_y * fb->pitches[0];

	/* output parameters (clamped / cropped) */
	dst_w = sti_gdp_get_dst(gdp->dev, dst_w, src_w);
	dst_h = sti_gdp_get_dst(gdp->dev, dst_h, src_h);
	yकरो = sti_vtg_get_line_number(*mode, dst_y);
	yds = sti_vtg_get_line_number(*mode, dst_y + dst_h - 1);
	xकरो = sti_vtg_get_pixel_number(*mode, dst_x);
	xds = sti_vtg_get_pixel_number(*mode, dst_x + dst_w - 1);
	top_field->gam_gdp_vpo = (yकरो << 16) | xकरो;
	top_field->gam_gdp_vps = (yds << 16) | xds;

	/* input parameters */
	src_w = dst_w;
	top_field->gam_gdp_pmp = fb->pitches[0];
	top_field->gam_gdp_size = src_h << 16 | src_w;

	/* Same content and chained together */
	स_नकल(bपंचांग_field, top_field, माप(*bपंचांग_field));
	top_field->gam_gdp_nvn = list->bपंचांग_field_paddr;
	bपंचांग_field->gam_gdp_nvn = list->top_field_paddr;

	/* Interlaced mode */
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		bपंचांग_field->gam_gdp_pml = top_field->gam_gdp_pml +
					 fb->pitches[0];

	/* Update the NVN field of the 'right' field of the current GDP node
	 * (being used by the HW) with the address of the updated ('free') top
	 * field GDP node.
	 * - In पूर्णांकerlaced mode the 'right' field is the bottom field as we
	 *   update frames starting from their top field
	 * - In progressive mode, we update both bottom and top fields which
	 *   are equal nodes.
	 * At the next VSYNC, the updated node list will be used by the HW.
	 */
	curr_list = sti_gdp_get_current_nodes(gdp);
	dma_updated_top = list->top_field_paddr;
	dma_updated_bपंचांग = list->bपंचांग_field_paddr;

	dev_dbg(gdp->dev, "Current NVN:0x%X\n",
		पढ़ोl(gdp->regs + GAM_GDP_NVN_OFFSET));
	dev_dbg(gdp->dev, "Posted buff: %lx current buff: %x\n",
		(अचिन्हित दीर्घ)cma_obj->paddr,
		पढ़ोl(gdp->regs + GAM_GDP_PML_OFFSET));

	अगर (!curr_list) अणु
		/* First update or invalid node should directly ग_लिखो in the
		 * hw रेजिस्टर */
		DRM_DEBUG_DRIVER("%s first update (or invalid node)\n",
				 sti_plane_to_str(plane));

		ग_लिखोl(gdp->is_curr_top ?
				dma_updated_bपंचांग : dma_updated_top,
				gdp->regs + GAM_GDP_NVN_OFFSET);
		जाओ end;
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		अगर (gdp->is_curr_top) अणु
			/* Do not update in the middle of the frame, but
			 * postpone the update after the bottom field has
			 * been displayed */
			curr_list->bपंचांग_field->gam_gdp_nvn = dma_updated_top;
		पूर्ण अन्यथा अणु
			/* Direct update to aव्योम one frame delay */
			ग_लिखोl(dma_updated_top,
			       gdp->regs + GAM_GDP_NVN_OFFSET);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Direct update क्रम progressive to aव्योम one frame delay */
		ग_लिखोl(dma_updated_top, gdp->regs + GAM_GDP_NVN_OFFSET);
	पूर्ण

end:
	sti_plane_update_fps(plane, true, false);

	plane->status = STI_PLANE_UPDATED;
पूर्ण

अटल व्योम sti_gdp_atomic_disable(काष्ठा drm_plane *drm_plane,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *oldstate = drm_atomic_get_old_plane_state(state,
									  drm_plane);
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);

	अगर (!oldstate->crtc) अणु
		DRM_DEBUG_DRIVER("drm plane:%d not enabled\n",
				 drm_plane->base.id);
		वापस;
	पूर्ण

	DRM_DEBUG_DRIVER("CRTC:%d (%s) drm plane:%d (%s)\n",
			 oldstate->crtc->base.id,
			 sti_mixer_to_str(to_sti_mixer(oldstate->crtc)),
			 drm_plane->base.id, sti_plane_to_str(plane));

	plane->status = STI_PLANE_DISABLING;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs sti_gdp_helpers_funcs = अणु
	.atomic_check = sti_gdp_atomic_check,
	.atomic_update = sti_gdp_atomic_update,
	.atomic_disable = sti_gdp_atomic_disable,
पूर्ण;

अटल पूर्णांक sti_gdp_late_रेजिस्टर(काष्ठा drm_plane *drm_plane)
अणु
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_gdp *gdp = to_sti_gdp(plane);

	वापस gdp_debugfs_init(gdp, drm_plane->dev->primary);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs sti_gdp_plane_helpers_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = sti_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.late_रेजिस्टर = sti_gdp_late_रेजिस्टर,
पूर्ण;

काष्ठा drm_plane *sti_gdp_create(काष्ठा drm_device *drm_dev,
				 काष्ठा device *dev, पूर्णांक desc,
				 व्योम __iomem *baseaddr,
				 अचिन्हित पूर्णांक possible_crtcs,
				 क्रमागत drm_plane_type type)
अणु
	काष्ठा sti_gdp *gdp;
	पूर्णांक res;

	gdp = devm_kzalloc(dev, माप(*gdp), GFP_KERNEL);
	अगर (!gdp) अणु
		DRM_ERROR("Failed to allocate memory for GDP\n");
		वापस शून्य;
	पूर्ण

	gdp->dev = dev;
	gdp->regs = baseaddr;
	gdp->plane.desc = desc;
	gdp->plane.status = STI_PLANE_DISABLED;

	gdp->vtg_field_nb.notअगरier_call = sti_gdp_field_cb;

	sti_gdp_init(gdp);

	res = drm_universal_plane_init(drm_dev, &gdp->plane.drm_plane,
				       possible_crtcs,
				       &sti_gdp_plane_helpers_funcs,
				       gdp_supported_क्रमmats,
				       ARRAY_SIZE(gdp_supported_क्रमmats),
				       शून्य, type, शून्य);
	अगर (res) अणु
		DRM_ERROR("Failed to initialize universal plane\n");
		जाओ err;
	पूर्ण

	drm_plane_helper_add(&gdp->plane.drm_plane, &sti_gdp_helpers_funcs);

	sti_plane_init_property(&gdp->plane, type);

	वापस &gdp->plane.drm_plane;

err:
	devm_kमुक्त(dev, gdp);
	वापस शून्य;
पूर्ण
