<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * shmob_drm_plane.c  --  SH Mobile DRM Planes
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>

#समावेश "shmob_drm_drv.h"
#समावेश "shmob_drm_kms.h"
#समावेश "shmob_drm_plane.h"
#समावेश "shmob_drm_regs.h"

काष्ठा shmob_drm_plane अणु
	काष्ठा drm_plane plane;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक alpha;

	स्थिर काष्ठा shmob_drm_क्रमmat_info *क्रमmat;
	अचिन्हित दीर्घ dma[2];

	अचिन्हित पूर्णांक src_x;
	अचिन्हित पूर्णांक src_y;
	अचिन्हित पूर्णांक crtc_x;
	अचिन्हित पूर्णांक crtc_y;
	अचिन्हित पूर्णांक crtc_w;
	अचिन्हित पूर्णांक crtc_h;
पूर्ण;

#घोषणा to_shmob_plane(p)	container_of(p, काष्ठा shmob_drm_plane, plane)

अटल व्योम shmob_drm_plane_compute_base(काष्ठा shmob_drm_plane *splane,
					 काष्ठा drm_framebuffer *fb,
					 पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा drm_gem_cma_object *gem;
	अचिन्हित पूर्णांक bpp;

	bpp = splane->क्रमmat->yuv ? 8 : splane->क्रमmat->bpp;
	gem = drm_fb_cma_get_gem_obj(fb, 0);
	splane->dma[0] = gem->paddr + fb->offsets[0]
		       + y * fb->pitches[0] + x * bpp / 8;

	अगर (splane->क्रमmat->yuv) अणु
		bpp = splane->क्रमmat->bpp - 8;
		gem = drm_fb_cma_get_gem_obj(fb, 1);
		splane->dma[1] = gem->paddr + fb->offsets[1]
			       + y / (bpp == 4 ? 2 : 1) * fb->pitches[1]
			       + x * (bpp == 16 ? 2 : 1);
	पूर्ण
पूर्ण

अटल व्योम __shmob_drm_plane_setup(काष्ठा shmob_drm_plane *splane,
				    काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा shmob_drm_device *sdev = splane->plane.dev->dev_निजी;
	u32 क्रमmat;

	/* TODO: Support ROP3 mode */
	क्रमmat = LDBBSIFR_EN | (splane->alpha << LDBBSIFR_LAY_SHIFT);

	चयन (splane->क्रमmat->fourcc) अणु
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_NV21:
	हाल DRM_FORMAT_NV61:
	हाल DRM_FORMAT_NV42:
		क्रमmat |= LDBBSIFR_SWPL | LDBBSIFR_SWPW;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV16:
	हाल DRM_FORMAT_NV24:
		क्रमmat |= LDBBSIFR_SWPL | LDBBSIFR_SWPW | LDBBSIFR_SWPB;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
	शेष:
		क्रमmat |= LDBBSIFR_SWPL;
		अवरोध;
	पूर्ण

	चयन (splane->क्रमmat->fourcc) अणु
	हाल DRM_FORMAT_RGB565:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_RY | LDBBSIFR_RPKF_RGB16;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_RY | LDBBSIFR_RPKF_RGB24;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		क्रमmat |= LDBBSIFR_AL_PK | LDBBSIFR_RY | LDDFR_PKF_ARGB32;
		अवरोध;
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV21:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_420;
		अवरोध;
	हाल DRM_FORMAT_NV16:
	हाल DRM_FORMAT_NV61:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_422;
		अवरोध;
	हाल DRM_FORMAT_NV24:
	हाल DRM_FORMAT_NV42:
		क्रमmat |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_444;
		अवरोध;
	पूर्ण

#घोषणा plane_reg_dump(sdev, splane, reg) \
	dev_dbg(sdev->ddev->dev, "%s(%u): %s 0x%08x 0x%08x\n", __func__, \
		splane->index, #reg, \
		lcdc_पढ़ो(sdev, reg(splane->index)), \
		lcdc_पढ़ो(sdev, reg(splane->index) + LCDC_SIDE_B_OFFSET))

	plane_reg_dump(sdev, splane, LDBnBSIFR);
	plane_reg_dump(sdev, splane, LDBnBSSZR);
	plane_reg_dump(sdev, splane, LDBnBLOCR);
	plane_reg_dump(sdev, splane, LDBnBSMWR);
	plane_reg_dump(sdev, splane, LDBnBSAYR);
	plane_reg_dump(sdev, splane, LDBnBSACR);

	lcdc_ग_लिखो(sdev, LDBCR, LDBCR_UPC(splane->index));
	dev_dbg(sdev->ddev->dev, "%s(%u): %s 0x%08x\n", __func__, splane->index,
		"LDBCR", lcdc_पढ़ो(sdev, LDBCR));

	lcdc_ग_लिखो(sdev, LDBnBSIFR(splane->index), क्रमmat);

	lcdc_ग_लिखो(sdev, LDBnBSSZR(splane->index),
		   (splane->crtc_h << LDBBSSZR_BVSS_SHIFT) |
		   (splane->crtc_w << LDBBSSZR_BHSS_SHIFT));
	lcdc_ग_लिखो(sdev, LDBnBLOCR(splane->index),
		   (splane->crtc_y << LDBBLOCR_CVLC_SHIFT) |
		   (splane->crtc_x << LDBBLOCR_CHLC_SHIFT));
	lcdc_ग_लिखो(sdev, LDBnBSMWR(splane->index),
		   fb->pitches[0] << LDBBSMWR_BSMW_SHIFT);

	shmob_drm_plane_compute_base(splane, fb, splane->src_x, splane->src_y);

	lcdc_ग_लिखो(sdev, LDBnBSAYR(splane->index), splane->dma[0]);
	अगर (splane->क्रमmat->yuv)
		lcdc_ग_लिखो(sdev, LDBnBSACR(splane->index), splane->dma[1]);

	lcdc_ग_लिखो(sdev, LDBCR,
		   LDBCR_UPF(splane->index) | LDBCR_UPD(splane->index));
	dev_dbg(sdev->ddev->dev, "%s(%u): %s 0x%08x\n", __func__, splane->index,
		"LDBCR", lcdc_पढ़ो(sdev, LDBCR));

	plane_reg_dump(sdev, splane, LDBnBSIFR);
	plane_reg_dump(sdev, splane, LDBnBSSZR);
	plane_reg_dump(sdev, splane, LDBnBLOCR);
	plane_reg_dump(sdev, splane, LDBnBSMWR);
	plane_reg_dump(sdev, splane, LDBnBSAYR);
	plane_reg_dump(sdev, splane, LDBnBSACR);
पूर्ण

व्योम shmob_drm_plane_setup(काष्ठा drm_plane *plane)
अणु
	काष्ठा shmob_drm_plane *splane = to_shmob_plane(plane);

	अगर (plane->fb == शून्य)
		वापस;

	__shmob_drm_plane_setup(splane, plane->fb);
पूर्ण

अटल पूर्णांक
shmob_drm_plane_update(काष्ठा drm_plane *plane, काष्ठा drm_crtc *crtc,
		       काष्ठा drm_framebuffer *fb, पूर्णांक crtc_x, पूर्णांक crtc_y,
		       अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
		       uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
		       uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
		       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा shmob_drm_plane *splane = to_shmob_plane(plane);
	काष्ठा shmob_drm_device *sdev = plane->dev->dev_निजी;
	स्थिर काष्ठा shmob_drm_क्रमmat_info *क्रमmat;

	क्रमmat = shmob_drm_क्रमmat_info(fb->क्रमmat->क्रमmat);
	अगर (क्रमmat == शून्य) अणु
		dev_dbg(sdev->dev, "update_plane: unsupported format %08x\n",
			fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (src_w >> 16 != crtc_w || src_h >> 16 != crtc_h) अणु
		dev_dbg(sdev->dev, "%s: scaling not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	splane->क्रमmat = क्रमmat;

	splane->src_x = src_x >> 16;
	splane->src_y = src_y >> 16;
	splane->crtc_x = crtc_x;
	splane->crtc_y = crtc_y;
	splane->crtc_w = crtc_w;
	splane->crtc_h = crtc_h;

	__shmob_drm_plane_setup(splane, fb);
	वापस 0;
पूर्ण

अटल पूर्णांक shmob_drm_plane_disable(काष्ठा drm_plane *plane,
				   काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा shmob_drm_plane *splane = to_shmob_plane(plane);
	काष्ठा shmob_drm_device *sdev = plane->dev->dev_निजी;

	splane->क्रमmat = शून्य;

	lcdc_ग_लिखो(sdev, LDBnBSIFR(splane->index), 0);
	वापस 0;
पूर्ण

अटल व्योम shmob_drm_plane_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_क्रमce_disable(plane);
	drm_plane_cleanup(plane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs shmob_drm_plane_funcs = अणु
	.update_plane = shmob_drm_plane_update,
	.disable_plane = shmob_drm_plane_disable,
	.destroy = shmob_drm_plane_destroy,
पूर्ण;

अटल स्थिर uपूर्णांक32_t क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV21,
	DRM_FORMAT_NV16,
	DRM_FORMAT_NV61,
	DRM_FORMAT_NV24,
	DRM_FORMAT_NV42,
पूर्ण;

पूर्णांक shmob_drm_plane_create(काष्ठा shmob_drm_device *sdev, अचिन्हित पूर्णांक index)
अणु
	काष्ठा shmob_drm_plane *splane;
	पूर्णांक ret;

	splane = devm_kzalloc(sdev->dev, माप(*splane), GFP_KERNEL);
	अगर (splane == शून्य)
		वापस -ENOMEM;

	splane->index = index;
	splane->alpha = 255;

	ret = drm_plane_init(sdev->ddev, &splane->plane, 1,
			     &shmob_drm_plane_funcs, क्रमmats,
			     ARRAY_SIZE(क्रमmats), false);

	वापस ret;
पूर्ण
