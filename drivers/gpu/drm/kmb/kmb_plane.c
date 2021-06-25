<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2018-2020 Intel Corporation
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "kmb_drv.h"
#समावेश "kmb_plane.h"
#समावेश "kmb_regs.h"

स्थिर u32 layer_irqs[] = अणु
	LCD_INT_VL0,
	LCD_INT_VL1,
	LCD_INT_GL0,
	LCD_INT_GL1
पूर्ण;

/* Conversion (yuv->rgb) matrix from myriadx */
अटल स्थिर u32 csc_coef_lcd[] = अणु
	1024, 0, 1436,
	1024, -352, -731,
	1024, 1814, 0,
	-179, 125, -226
पूर्ण;

/* Graphics layer (layers 2 & 3) क्रमmats, only packed क्रमmats  are supported */
अटल स्थिर u32 kmb_क्रमmats_g[] = अणु
	DRM_FORMAT_RGB332,
	DRM_FORMAT_XRGB4444, DRM_FORMAT_XBGR4444,
	DRM_FORMAT_ARGB4444, DRM_FORMAT_ABGR4444,
	DRM_FORMAT_XRGB1555, DRM_FORMAT_XBGR1555,
	DRM_FORMAT_ARGB1555, DRM_FORMAT_ABGR1555,
	DRM_FORMAT_RGB565, DRM_FORMAT_BGR565,
	DRM_FORMAT_RGB888, DRM_FORMAT_BGR888,
	DRM_FORMAT_XRGB8888, DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888, DRM_FORMAT_ABGR8888,
पूर्ण;

/* Video layer ( 0 & 1) क्रमmats, packed and planar क्रमmats are supported */
अटल स्थिर u32 kmb_क्रमmats_v[] = अणु
	/* packed क्रमmats */
	DRM_FORMAT_RGB332,
	DRM_FORMAT_XRGB4444, DRM_FORMAT_XBGR4444,
	DRM_FORMAT_ARGB4444, DRM_FORMAT_ABGR4444,
	DRM_FORMAT_XRGB1555, DRM_FORMAT_XBGR1555,
	DRM_FORMAT_ARGB1555, DRM_FORMAT_ABGR1555,
	DRM_FORMAT_RGB565, DRM_FORMAT_BGR565,
	DRM_FORMAT_RGB888, DRM_FORMAT_BGR888,
	DRM_FORMAT_XRGB8888, DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888, DRM_FORMAT_ABGR8888,
	/*planar क्रमmats */
	DRM_FORMAT_YUV420, DRM_FORMAT_YVU420,
	DRM_FORMAT_YUV422, DRM_FORMAT_YVU422,
	DRM_FORMAT_YUV444, DRM_FORMAT_YVU444,
	DRM_FORMAT_NV12, DRM_FORMAT_NV21,
पूर्ण;

अटल अचिन्हित पूर्णांक check_pixel_क्रमmat(काष्ठा drm_plane *plane, u32 क्रमmat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < plane->क्रमmat_count; i++) अणु
		अगर (plane->क्रमmat_types[i] == क्रमmat)
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kmb_plane_atomic_check(काष्ठा drm_plane *plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb;
	पूर्णांक ret;
	काष्ठा drm_crtc_state *crtc_state;
	bool can_position;

	fb = new_plane_state->fb;
	अगर (!fb || !new_plane_state->crtc)
		वापस 0;

	ret = check_pixel_क्रमmat(plane, fb->क्रमmat->क्रमmat);
	अगर (ret)
		वापस ret;

	अगर (new_plane_state->crtc_w > KMB_MAX_WIDTH || new_plane_state->crtc_h > KMB_MAX_HEIGHT)
		वापस -EINVAL;
	अगर (new_plane_state->crtc_w < KMB_MIN_WIDTH || new_plane_state->crtc_h < KMB_MIN_HEIGHT)
		वापस -EINVAL;
	can_position = (plane->type == DRM_PLANE_TYPE_OVERLAY);
	crtc_state =
		drm_atomic_get_existing_crtc_state(state,
						   new_plane_state->crtc);
	वापस drm_atomic_helper_check_plane_state(new_plane_state,
						   crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   can_position, true);
पूर्ण

अटल व्योम kmb_plane_atomic_disable(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा kmb_plane *kmb_plane = to_kmb_plane(plane);
	पूर्णांक plane_id = kmb_plane->id;
	काष्ठा kmb_drm_निजी *kmb;

	kmb = to_kmb(plane->dev);

	अगर (WARN_ON(plane_id >= KMB_MAX_PLANES))
		वापस;

	चयन (plane_id) अणु
	हाल LAYER_0:
		kmb->plane_status[plane_id].ctrl = LCD_CTRL_VL1_ENABLE;
		अवरोध;
	हाल LAYER_1:
		kmb->plane_status[plane_id].ctrl = LCD_CTRL_VL2_ENABLE;
		अवरोध;
	हाल LAYER_2:
		kmb->plane_status[plane_id].ctrl = LCD_CTRL_GL1_ENABLE;
		अवरोध;
	हाल LAYER_3:
		kmb->plane_status[plane_id].ctrl = LCD_CTRL_GL2_ENABLE;
		अवरोध;
	पूर्ण

	kmb->plane_status[plane_id].disable = true;
पूर्ण

अटल अचिन्हित पूर्णांक get_pixel_क्रमmat(u32 क्रमmat)
अणु
	अचिन्हित पूर्णांक val = 0;

	चयन (क्रमmat) अणु
		/* planar क्रमmats */
	हाल DRM_FORMAT_YUV444:
		val = LCD_LAYER_FORMAT_YCBCR444PLAN | LCD_LAYER_PLANAR_STORAGE;
		अवरोध;
	हाल DRM_FORMAT_YVU444:
		val = LCD_LAYER_FORMAT_YCBCR444PLAN | LCD_LAYER_PLANAR_STORAGE
		    | LCD_LAYER_CRCB_ORDER;
		अवरोध;
	हाल DRM_FORMAT_YUV422:
		val = LCD_LAYER_FORMAT_YCBCR422PLAN | LCD_LAYER_PLANAR_STORAGE;
		अवरोध;
	हाल DRM_FORMAT_YVU422:
		val = LCD_LAYER_FORMAT_YCBCR422PLAN | LCD_LAYER_PLANAR_STORAGE
		    | LCD_LAYER_CRCB_ORDER;
		अवरोध;
	हाल DRM_FORMAT_YUV420:
		val = LCD_LAYER_FORMAT_YCBCR420PLAN | LCD_LAYER_PLANAR_STORAGE;
		अवरोध;
	हाल DRM_FORMAT_YVU420:
		val = LCD_LAYER_FORMAT_YCBCR420PLAN | LCD_LAYER_PLANAR_STORAGE
		    | LCD_LAYER_CRCB_ORDER;
		अवरोध;
	हाल DRM_FORMAT_NV12:
		val = LCD_LAYER_FORMAT_NV12 | LCD_LAYER_PLANAR_STORAGE;
		अवरोध;
	हाल DRM_FORMAT_NV21:
		val = LCD_LAYER_FORMAT_NV12 | LCD_LAYER_PLANAR_STORAGE
		    | LCD_LAYER_CRCB_ORDER;
		अवरोध;
		/* packed क्रमmats */
		/* looks hw requires B & G to be swapped when RGB */
	हाल DRM_FORMAT_RGB332:
		val = LCD_LAYER_FORMAT_RGB332 | LCD_LAYER_BGR_ORDER;
		अवरोध;
	हाल DRM_FORMAT_XBGR4444:
		val = LCD_LAYER_FORMAT_RGBX4444;
		अवरोध;
	हाल DRM_FORMAT_ARGB4444:
		val = LCD_LAYER_FORMAT_RGBA4444 | LCD_LAYER_BGR_ORDER;
		अवरोध;
	हाल DRM_FORMAT_ABGR4444:
		val = LCD_LAYER_FORMAT_RGBA4444;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		val = LCD_LAYER_FORMAT_XRGB1555 | LCD_LAYER_BGR_ORDER;
		अवरोध;
	हाल DRM_FORMAT_XBGR1555:
		val = LCD_LAYER_FORMAT_XRGB1555;
		अवरोध;
	हाल DRM_FORMAT_ARGB1555:
		val = LCD_LAYER_FORMAT_RGBA1555 | LCD_LAYER_BGR_ORDER;
		अवरोध;
	हाल DRM_FORMAT_ABGR1555:
		val = LCD_LAYER_FORMAT_RGBA1555;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		val = LCD_LAYER_FORMAT_RGB565 | LCD_LAYER_BGR_ORDER;
		अवरोध;
	हाल DRM_FORMAT_BGR565:
		val = LCD_LAYER_FORMAT_RGB565;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
		val = LCD_LAYER_FORMAT_RGB888 | LCD_LAYER_BGR_ORDER;
		अवरोध;
	हाल DRM_FORMAT_BGR888:
		val = LCD_LAYER_FORMAT_RGB888;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		val = LCD_LAYER_FORMAT_RGBX8888 | LCD_LAYER_BGR_ORDER;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
		val = LCD_LAYER_FORMAT_RGBX8888;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		val = LCD_LAYER_FORMAT_RGBA8888 | LCD_LAYER_BGR_ORDER;
		अवरोध;
	हाल DRM_FORMAT_ABGR8888:
		val = LCD_LAYER_FORMAT_RGBA8888;
		अवरोध;
	पूर्ण
	DRM_INFO_ONCE("%s : %d format=0x%x val=0x%x\n",
		      __func__, __LINE__, क्रमmat, val);
	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक get_bits_per_pixel(स्थिर काष्ठा drm_क्रमmat_info *क्रमmat)
अणु
	u32 bpp = 0;
	अचिन्हित पूर्णांक val = 0;

	अगर (क्रमmat->num_planes > 1) अणु
		val = LCD_LAYER_8BPP;
		वापस val;
	पूर्ण

	bpp += 8 * क्रमmat->cpp[0];

	चयन (bpp) अणु
	हाल 8:
		val = LCD_LAYER_8BPP;
		अवरोध;
	हाल 16:
		val = LCD_LAYER_16BPP;
		अवरोध;
	हाल 24:
		val = LCD_LAYER_24BPP;
		अवरोध;
	हाल 32:
		val = LCD_LAYER_32BPP;
		अवरोध;
	पूर्ण

	DRM_DEBUG("bpp=%d val=0x%x\n", bpp, val);
	वापस val;
पूर्ण

अटल व्योम config_csc(काष्ठा kmb_drm_निजी *kmb, पूर्णांक plane_id)
अणु
	/* YUV to RGB conversion using the fixed matrix csc_coef_lcd */
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF11(plane_id), csc_coef_lcd[0]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF12(plane_id), csc_coef_lcd[1]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF13(plane_id), csc_coef_lcd[2]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF21(plane_id), csc_coef_lcd[3]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF22(plane_id), csc_coef_lcd[4]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF23(plane_id), csc_coef_lcd[5]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF31(plane_id), csc_coef_lcd[6]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF32(plane_id), csc_coef_lcd[7]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_COEFF33(plane_id), csc_coef_lcd[8]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_OFF1(plane_id), csc_coef_lcd[9]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_OFF2(plane_id), csc_coef_lcd[10]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CSC_OFF3(plane_id), csc_coef_lcd[11]);
पूर्ण

अटल व्योम kmb_plane_atomic_update(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_plane_state = drm_atomic_get_old_plane_state(state,
										 plane);
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb;
	काष्ठा kmb_drm_निजी *kmb;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक dma_len;
	काष्ठा kmb_plane *kmb_plane;
	अचिन्हित पूर्णांक dma_cfg;
	अचिन्हित पूर्णांक ctrl = 0, val = 0, out_क्रमmat = 0;
	अचिन्हित पूर्णांक src_w, src_h, crtc_x, crtc_y;
	अचिन्हित अक्षर plane_id;
	पूर्णांक num_planes;
	अटल dma_addr_t addr[MAX_SUB_PLANES];

	अगर (!plane || !new_plane_state || !old_plane_state)
		वापस;

	fb = new_plane_state->fb;
	अगर (!fb)
		वापस;
	num_planes = fb->क्रमmat->num_planes;
	kmb_plane = to_kmb_plane(plane);
	plane_id = kmb_plane->id;

	kmb = to_kmb(plane->dev);

	spin_lock_irq(&kmb->irq_lock);
	अगर (kmb->kmb_under_flow || kmb->kmb_flush_करोne) अणु
		spin_unlock_irq(&kmb->irq_lock);
		drm_dbg(&kmb->drm, "plane_update:underflow!!!! returning");
		वापस;
	पूर्ण
	spin_unlock_irq(&kmb->irq_lock);

	src_w = (new_plane_state->src_w >> 16);
	src_h = new_plane_state->src_h >> 16;
	crtc_x = new_plane_state->crtc_x;
	crtc_y = new_plane_state->crtc_y;

	drm_dbg(&kmb->drm,
		"src_w=%d src_h=%d, fb->format->format=0x%x fb->flags=0x%x\n",
		  src_w, src_h, fb->क्रमmat->क्रमmat, fb->flags);

	width = fb->width;
	height = fb->height;
	dma_len = (width * height * fb->क्रमmat->cpp[0]);
	drm_dbg(&kmb->drm, "dma_len=%d ", dma_len);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_DMA_LEN(plane_id), dma_len);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_DMA_LEN_SHADOW(plane_id), dma_len);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_DMA_LINE_VSTRIDE(plane_id),
		      fb->pitches[0]);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_DMA_LINE_WIDTH(plane_id),
		      (width * fb->क्रमmat->cpp[0]));

	addr[Y_PLANE] = drm_fb_cma_get_gem_addr(fb, new_plane_state, 0);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_DMA_START_ADDR(plane_id),
		      addr[Y_PLANE] + fb->offsets[0]);
	val = get_pixel_क्रमmat(fb->क्रमmat->क्रमmat);
	val |= get_bits_per_pixel(fb->क्रमmat);
	/* Program Cb/Cr क्रम planar क्रमmats */
	अगर (num_planes > 1) अणु
		kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_DMA_CB_LINE_VSTRIDE(plane_id),
			      width * fb->क्रमmat->cpp[0]);
		kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_DMA_CB_LINE_WIDTH(plane_id),
			      (width * fb->क्रमmat->cpp[0]));

		addr[U_PLANE] = drm_fb_cma_get_gem_addr(fb, new_plane_state,
							U_PLANE);
		/* check अगर Cb/Cr is swapped*/
		अगर (num_planes == 3 && (val & LCD_LAYER_CRCB_ORDER))
			kmb_ग_लिखो_lcd(kmb,
				      LCD_LAYERn_DMA_START_CR_ADR(plane_id),
					addr[U_PLANE]);
		अन्यथा
			kmb_ग_लिखो_lcd(kmb,
				      LCD_LAYERn_DMA_START_CB_ADR(plane_id),
					addr[U_PLANE]);

		अगर (num_planes == 3) अणु
			kmb_ग_लिखो_lcd(kmb,
				      LCD_LAYERn_DMA_CR_LINE_VSTRIDE(plane_id),
				      ((width) * fb->क्रमmat->cpp[0]));

			kmb_ग_लिखो_lcd(kmb,
				      LCD_LAYERn_DMA_CR_LINE_WIDTH(plane_id),
				      ((width) * fb->क्रमmat->cpp[0]));

			addr[V_PLANE] = drm_fb_cma_get_gem_addr(fb,
								new_plane_state,
								V_PLANE);

			/* check अगर Cb/Cr is swapped*/
			अगर (val & LCD_LAYER_CRCB_ORDER)
				kmb_ग_लिखो_lcd(kmb,
					      LCD_LAYERn_DMA_START_CB_ADR(plane_id),
					      addr[V_PLANE]);
			अन्यथा
				kmb_ग_लिखो_lcd(kmb,
					      LCD_LAYERn_DMA_START_CR_ADR(plane_id),
					      addr[V_PLANE]);
		पूर्ण
	पूर्ण

	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_WIDTH(plane_id), src_w - 1);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_HEIGHT(plane_id), src_h - 1);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_COL_START(plane_id), crtc_x);
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_ROW_START(plane_id), crtc_y);

	val |= LCD_LAYER_FIFO_100;

	अगर (val & LCD_LAYER_PLANAR_STORAGE) अणु
		val |= LCD_LAYER_CSC_EN;

		/* Enable CSC अगर input is planar and output is RGB */
		config_csc(kmb, plane_id);
	पूर्ण

	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_CFG(plane_id), val);

	चयन (plane_id) अणु
	हाल LAYER_0:
		ctrl = LCD_CTRL_VL1_ENABLE;
		अवरोध;
	हाल LAYER_1:
		ctrl = LCD_CTRL_VL2_ENABLE;
		अवरोध;
	हाल LAYER_2:
		ctrl = LCD_CTRL_GL1_ENABLE;
		अवरोध;
	हाल LAYER_3:
		ctrl = LCD_CTRL_GL2_ENABLE;
		अवरोध;
	पूर्ण

	ctrl |= LCD_CTRL_PROGRESSIVE | LCD_CTRL_TIM_GEN_ENABLE
	    | LCD_CTRL_CONTINUOUS | LCD_CTRL_OUTPUT_ENABLED;

	/* LCD is connected to MIPI on kmb
	 * Thereक्रमe this bit is required क्रम DSI Tx
	 */
	ctrl |= LCD_CTRL_VHSYNC_IDLE_LVL;

	kmb_set_biपंचांगask_lcd(kmb, LCD_CONTROL, ctrl);

	/* FIXME no करोc on how to set output क्रमmat,these values are
	 * taken from the Myriadx tests
	 */
	out_क्रमmat |= LCD_OUTF_FORMAT_RGB888;

	/* Leave RGB order,conversion mode and clip mode to शेष */
	/* करो not पूर्णांकerleave RGB channels क्रम mipi Tx compatibility */
	out_क्रमmat |= LCD_OUTF_MIPI_RGB_MODE;
	kmb_ग_लिखो_lcd(kmb, LCD_OUT_FORMAT_CFG, out_क्रमmat);

	dma_cfg = LCD_DMA_LAYER_ENABLE | LCD_DMA_LAYER_VSTRIDE_EN |
	    LCD_DMA_LAYER_CONT_UPDATE | LCD_DMA_LAYER_AXI_BURST_16;

	/* Enable DMA */
	kmb_ग_लिखो_lcd(kmb, LCD_LAYERn_DMA_CFG(plane_id), dma_cfg);
	drm_dbg(&kmb->drm, "dma_cfg=0x%x LCD_DMA_CFG=0x%x\n", dma_cfg,
		kmb_पढ़ो_lcd(kmb, LCD_LAYERn_DMA_CFG(plane_id)));

	kmb_set_biपंचांगask_lcd(kmb, LCD_INT_CLEAR, LCD_INT_खातापूर्ण |
			LCD_INT_DMA_ERR);
	kmb_set_biपंचांगask_lcd(kmb, LCD_INT_ENABLE, LCD_INT_खातापूर्ण |
			LCD_INT_DMA_ERR);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs kmb_plane_helper_funcs = अणु
	.atomic_check = kmb_plane_atomic_check,
	.atomic_update = kmb_plane_atomic_update,
	.atomic_disable = kmb_plane_atomic_disable
पूर्ण;

व्योम kmb_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा kmb_plane *kmb_plane = to_kmb_plane(plane);

	drm_plane_cleanup(plane);
	kमुक्त(kmb_plane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs kmb_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = kmb_plane_destroy,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

काष्ठा kmb_plane *kmb_plane_init(काष्ठा drm_device *drm)
अणु
	काष्ठा kmb_drm_निजी *kmb = to_kmb(drm);
	काष्ठा kmb_plane *plane = शून्य;
	काष्ठा kmb_plane *primary = शून्य;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;
	क्रमागत drm_plane_type plane_type;
	स्थिर u32 *plane_क्रमmats;
	पूर्णांक num_plane_क्रमmats;

	क्रम (i = 0; i < KMB_MAX_PLANES; i++) अणु
		plane = drmm_kzalloc(drm, माप(*plane), GFP_KERNEL);

		अगर (!plane) अणु
			drm_err(drm, "Failed to allocate plane\n");
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		plane_type = (i == 0) ? DRM_PLANE_TYPE_PRIMARY :
		    DRM_PLANE_TYPE_OVERLAY;
		अगर (i < 2) अणु
			plane_क्रमmats = kmb_क्रमmats_v;
			num_plane_क्रमmats = ARRAY_SIZE(kmb_क्रमmats_v);
		पूर्ण अन्यथा अणु
			plane_क्रमmats = kmb_क्रमmats_g;
			num_plane_क्रमmats = ARRAY_SIZE(kmb_क्रमmats_g);
		पूर्ण

		ret = drm_universal_plane_init(drm, &plane->base_plane,
					       POSSIBLE_CRTCS, &kmb_plane_funcs,
					       plane_क्रमmats, num_plane_क्रमmats,
					       शून्य, plane_type, "plane %d", i);
		अगर (ret < 0) अणु
			drm_err(drm, "drm_universal_plane_init failed (ret=%d)",
				ret);
			जाओ cleanup;
		पूर्ण
		drm_dbg(drm, "%s : %d i=%d type=%d",
			__func__, __LINE__,
			  i, plane_type);
		drm_plane_helper_add(&plane->base_plane,
				     &kmb_plane_helper_funcs);
		अगर (plane_type == DRM_PLANE_TYPE_PRIMARY) अणु
			primary = plane;
			kmb->plane = plane;
		पूर्ण
		drm_dbg(drm, "%s : %d primary=%p\n", __func__, __LINE__,
			&primary->base_plane);
		plane->id = i;
	पूर्ण

	वापस primary;
cleanup:
	drmm_kमुक्त(drm, plane);
	वापस ERR_PTR(ret);
पूर्ण
