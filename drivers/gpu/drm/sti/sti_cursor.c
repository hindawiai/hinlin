<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Vincent Abriou <vincent.abriou@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>

#समावेश "sti_compositor.h"
#समावेश "sti_cursor.h"
#समावेश "sti_plane.h"
#समावेश "sti_vtg.h"

/* Registers */
#घोषणा CUR_CTL             0x00
#घोषणा CUR_VPO             0x0C
#घोषणा CUR_PML             0x14
#घोषणा CUR_PMP             0x18
#घोषणा CUR_SIZE            0x1C
#घोषणा CUR_CML             0x20
#घोषणा CUR_AWS             0x28
#घोषणा CUR_AWE             0x2C

#घोषणा CUR_CTL_CLUT_UPDATE BIT(1)

#घोषणा STI_CURS_MIN_SIZE   1
#घोषणा STI_CURS_MAX_SIZE   128

/*
 * pixmap dma buffer काष्ठाure
 *
 * @paddr:  physical address
 * @size:   buffer size
 * @base:   भव address
 */
काष्ठा dma_pixmap अणु
	dma_addr_t paddr;
	माप_प्रकार size;
	व्योम *base;
पूर्ण;

/*
 * STI Cursor काष्ठाure
 *
 * @sti_plane:    sti_plane काष्ठाure
 * @dev:          driver device
 * @regs:         cursor रेजिस्टरs
 * @width:        cursor width
 * @height:       cursor height
 * @clut:         color look up table
 * @clut_paddr:   color look up table physical address
 * @pixmap:       pixmap dma buffer (clut8-क्रमmat cursor)
 */
काष्ठा sti_cursor अणु
	काष्ठा sti_plane plane;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित लघु *clut;
	dma_addr_t clut_paddr;
	काष्ठा dma_pixmap pixmap;
पूर्ण;

अटल स्थिर uपूर्णांक32_t cursor_supported_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
पूर्ण;

#घोषणा to_sti_cursor(x) container_of(x, काष्ठा sti_cursor, plane)

#घोषणा DBGFS_DUMP(reg) seq_म_लिखो(s, "\n  %-25s 0x%08X", #reg, \
				   पढ़ोl(cursor->regs + reg))

अटल व्योम cursor_dbg_vpo(काष्ठा seq_file *s, u32 val)
अणु
	seq_म_लिखो(s, "\txdo:%4d\tydo:%4d", val & 0x0FFF, (val >> 16) & 0x0FFF);
पूर्ण

अटल व्योम cursor_dbg_size(काष्ठा seq_file *s, u32 val)
अणु
	seq_म_लिखो(s, "\t%d x %d", val & 0x07FF, (val >> 16) & 0x07FF);
पूर्ण

अटल व्योम cursor_dbg_pml(काष्ठा seq_file *s,
			   काष्ठा sti_cursor *cursor, u32 val)
अणु
	अगर (cursor->pixmap.paddr == val)
		seq_म_लिखो(s, "\tVirt @: %p", cursor->pixmap.base);
पूर्ण

अटल व्योम cursor_dbg_cml(काष्ठा seq_file *s,
			   काष्ठा sti_cursor *cursor, u32 val)
अणु
	अगर (cursor->clut_paddr == val)
		seq_म_लिखो(s, "\tVirt @: %p", cursor->clut);
पूर्ण

अटल पूर्णांक cursor_dbg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_cursor *cursor = (काष्ठा sti_cursor *)node->info_ent->data;

	seq_म_लिखो(s, "%s: (vaddr = 0x%p)",
		   sti_plane_to_str(&cursor->plane), cursor->regs);

	DBGFS_DUMP(CUR_CTL);
	DBGFS_DUMP(CUR_VPO);
	cursor_dbg_vpo(s, पढ़ोl(cursor->regs + CUR_VPO));
	DBGFS_DUMP(CUR_PML);
	cursor_dbg_pml(s, cursor, पढ़ोl(cursor->regs + CUR_PML));
	DBGFS_DUMP(CUR_PMP);
	DBGFS_DUMP(CUR_SIZE);
	cursor_dbg_size(s, पढ़ोl(cursor->regs + CUR_SIZE));
	DBGFS_DUMP(CUR_CML);
	cursor_dbg_cml(s, cursor, पढ़ोl(cursor->regs + CUR_CML));
	DBGFS_DUMP(CUR_AWS);
	DBGFS_DUMP(CUR_AWE);
	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list cursor_debugfs_files[] = अणु
	अणु "cursor", cursor_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल व्योम cursor_debugfs_init(काष्ठा sti_cursor *cursor,
				काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cursor_debugfs_files); i++)
		cursor_debugfs_files[i].data = cursor;

	drm_debugfs_create_files(cursor_debugfs_files,
				 ARRAY_SIZE(cursor_debugfs_files),
				 minor->debugfs_root, minor);
पूर्ण

अटल व्योम sti_cursor_argb8888_to_clut8(काष्ठा sti_cursor *cursor, u32 *src)
अणु
	u8  *dst = cursor->pixmap.base;
	अचिन्हित पूर्णांक i, j;
	u32 a, r, g, b;

	क्रम (i = 0; i < cursor->height; i++) अणु
		क्रम (j = 0; j < cursor->width; j++) अणु
			/* Pick the 2 higher bits of each component */
			a = (*src >> 30) & 3;
			r = (*src >> 22) & 3;
			g = (*src >> 14) & 3;
			b = (*src >> 6) & 3;
			*dst = a << 6 | r << 4 | g << 2 | b;
			src++;
			dst++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sti_cursor_init(काष्ठा sti_cursor *cursor)
अणु
	अचिन्हित लघु *base = cursor->clut;
	अचिन्हित पूर्णांक a, r, g, b;

	/* Assign CLUT values, ARGB444 क्रमmat */
	क्रम (a = 0; a < 4; a++)
		क्रम (r = 0; r < 4; r++)
			क्रम (g = 0; g < 4; g++)
				क्रम (b = 0; b < 4; b++)
					*base++ = (a * 5) << 12 |
						  (r * 5) << 8 |
						  (g * 5) << 4 |
						  (b * 5);
पूर्ण

अटल पूर्णांक sti_cursor_atomic_check(काष्ठा drm_plane *drm_plane,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 drm_plane);
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_cursor *cursor = to_sti_cursor(plane);
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_display_mode *mode;
	पूर्णांक dst_x, dst_y, dst_w, dst_h;
	पूर्णांक src_w, src_h;

	/* no need क्रम further checks अगर the plane is being disabled */
	अगर (!crtc || !fb)
		वापस 0;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	mode = &crtc_state->mode;
	dst_x = new_plane_state->crtc_x;
	dst_y = new_plane_state->crtc_y;
	dst_w = clamp_val(new_plane_state->crtc_w, 0,
			  mode->crtc_hdisplay - dst_x);
	dst_h = clamp_val(new_plane_state->crtc_h, 0,
			  mode->crtc_vdisplay - dst_y);
	/* src_x are in 16.16 क्रमmat */
	src_w = new_plane_state->src_w >> 16;
	src_h = new_plane_state->src_h >> 16;

	अगर (src_w < STI_CURS_MIN_SIZE ||
	    src_h < STI_CURS_MIN_SIZE ||
	    src_w > STI_CURS_MAX_SIZE ||
	    src_h > STI_CURS_MAX_SIZE) अणु
		DRM_ERROR("Invalid cursor size (%dx%d)\n",
				src_w, src_h);
		वापस -EINVAL;
	पूर्ण

	/* If the cursor size has changed, re-allocated the pixmap */
	अगर (!cursor->pixmap.base ||
	    (cursor->width != src_w) ||
	    (cursor->height != src_h)) अणु
		cursor->width = src_w;
		cursor->height = src_h;

		अगर (cursor->pixmap.base)
			dma_मुक्त_wc(cursor->dev, cursor->pixmap.size,
				    cursor->pixmap.base, cursor->pixmap.paddr);

		cursor->pixmap.size = cursor->width * cursor->height;

		cursor->pixmap.base = dma_alloc_wc(cursor->dev,
						   cursor->pixmap.size,
						   &cursor->pixmap.paddr,
						   GFP_KERNEL | GFP_DMA);
		अगर (!cursor->pixmap.base) अणु
			DRM_ERROR("Failed to allocate memory for pixmap\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!drm_fb_cma_get_gem_obj(fb, 0)) अणु
		DRM_ERROR("Can't get CMA GEM object for fb\n");
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG_KMS("CRTC:%d (%s) drm plane:%d (%s)\n",
		      crtc->base.id, sti_mixer_to_str(to_sti_mixer(crtc)),
		      drm_plane->base.id, sti_plane_to_str(plane));
	DRM_DEBUG_KMS("(%dx%d)@(%d,%d)\n", dst_w, dst_h, dst_x, dst_y);

	वापस 0;
पूर्ण

अटल व्योम sti_cursor_atomic_update(काष्ठा drm_plane *drm_plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *newstate = drm_atomic_get_new_plane_state(state,
									  drm_plane);
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_cursor *cursor = to_sti_cursor(plane);
	काष्ठा drm_crtc *crtc = newstate->crtc;
	काष्ठा drm_framebuffer *fb = newstate->fb;
	काष्ठा drm_display_mode *mode;
	पूर्णांक dst_x, dst_y;
	काष्ठा drm_gem_cma_object *cma_obj;
	u32 y, x;
	u32 val;

	अगर (!crtc || !fb)
		वापस;

	mode = &crtc->mode;
	dst_x = newstate->crtc_x;
	dst_y = newstate->crtc_y;

	cma_obj = drm_fb_cma_get_gem_obj(fb, 0);

	/* Convert ARGB8888 to CLUT8 */
	sti_cursor_argb8888_to_clut8(cursor, (u32 *)cma_obj->vaddr);

	/* AWS and AWE depend on the mode */
	y = sti_vtg_get_line_number(*mode, 0);
	x = sti_vtg_get_pixel_number(*mode, 0);
	val = y << 16 | x;
	ग_लिखोl(val, cursor->regs + CUR_AWS);
	y = sti_vtg_get_line_number(*mode, mode->vdisplay - 1);
	x = sti_vtg_get_pixel_number(*mode, mode->hdisplay - 1);
	val = y << 16 | x;
	ग_लिखोl(val, cursor->regs + CUR_AWE);

	/* Set memory location, size, and position */
	ग_लिखोl(cursor->pixmap.paddr, cursor->regs + CUR_PML);
	ग_लिखोl(cursor->width, cursor->regs + CUR_PMP);
	ग_लिखोl(cursor->height << 16 | cursor->width, cursor->regs + CUR_SIZE);

	y = sti_vtg_get_line_number(*mode, dst_y);
	x = sti_vtg_get_pixel_number(*mode, dst_x);
	ग_लिखोl((y << 16) | x, cursor->regs + CUR_VPO);

	/* Set and fetch CLUT */
	ग_लिखोl(cursor->clut_paddr, cursor->regs + CUR_CML);
	ग_लिखोl(CUR_CTL_CLUT_UPDATE, cursor->regs + CUR_CTL);

	sti_plane_update_fps(plane, true, false);

	plane->status = STI_PLANE_UPDATED;
पूर्ण

अटल व्योम sti_cursor_atomic_disable(काष्ठा drm_plane *drm_plane,
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

अटल स्थिर काष्ठा drm_plane_helper_funcs sti_cursor_helpers_funcs = अणु
	.atomic_check = sti_cursor_atomic_check,
	.atomic_update = sti_cursor_atomic_update,
	.atomic_disable = sti_cursor_atomic_disable,
पूर्ण;

अटल पूर्णांक sti_cursor_late_रेजिस्टर(काष्ठा drm_plane *drm_plane)
अणु
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_cursor *cursor = to_sti_cursor(plane);

	cursor_debugfs_init(cursor, drm_plane->dev->primary);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs sti_cursor_plane_helpers_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = sti_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.late_रेजिस्टर = sti_cursor_late_रेजिस्टर,
पूर्ण;

काष्ठा drm_plane *sti_cursor_create(काष्ठा drm_device *drm_dev,
				    काष्ठा device *dev, पूर्णांक desc,
				    व्योम __iomem *baseaddr,
				    अचिन्हित पूर्णांक possible_crtcs)
अणु
	काष्ठा sti_cursor *cursor;
	माप_प्रकार size;
	पूर्णांक res;

	cursor = devm_kzalloc(dev, माप(*cursor), GFP_KERNEL);
	अगर (!cursor) अणु
		DRM_ERROR("Failed to allocate memory for cursor\n");
		वापस शून्य;
	पूर्ण

	/* Allocate clut buffer */
	size = 0x100 * माप(अचिन्हित लघु);
	cursor->clut = dma_alloc_wc(dev, size, &cursor->clut_paddr,
				    GFP_KERNEL | GFP_DMA);

	अगर (!cursor->clut) अणु
		DRM_ERROR("Failed to allocate memory for cursor clut\n");
		जाओ err_clut;
	पूर्ण

	cursor->dev = dev;
	cursor->regs = baseaddr;
	cursor->plane.desc = desc;
	cursor->plane.status = STI_PLANE_DISABLED;

	sti_cursor_init(cursor);

	res = drm_universal_plane_init(drm_dev, &cursor->plane.drm_plane,
				       possible_crtcs,
				       &sti_cursor_plane_helpers_funcs,
				       cursor_supported_क्रमmats,
				       ARRAY_SIZE(cursor_supported_क्रमmats),
				       शून्य, DRM_PLANE_TYPE_CURSOR, शून्य);
	अगर (res) अणु
		DRM_ERROR("Failed to initialize universal plane\n");
		जाओ err_plane;
	पूर्ण

	drm_plane_helper_add(&cursor->plane.drm_plane,
			     &sti_cursor_helpers_funcs);

	sti_plane_init_property(&cursor->plane, DRM_PLANE_TYPE_CURSOR);

	वापस &cursor->plane.drm_plane;

err_plane:
	dma_मुक्त_wc(dev, size, cursor->clut, cursor->clut_paddr);
err_clut:
	devm_kमुक्त(dev, cursor);
	वापस शून्य;
पूर्ण
