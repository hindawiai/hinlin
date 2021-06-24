<शैली गुरु>
/*
 * Copyright तऊ 2009
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Daniel Vetter <daniel@ffwll.ch>
 *
 * Derived from Xorg ddx, xf86-video-पूर्णांकel, src/i830_video.c
 */

#समावेश <drm/drm_fourcc.h>

#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_ring.h"

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"
#समावेश "intel_display_types.h"
#समावेश "intel_frontbuffer.h"
#समावेश "intel_overlay.h"

/* Limits क्रम overlay size. According to पूर्णांकel करोc, the real limits are:
 * Y width: 4095, UV width (planar): 2047, Y height: 2047,
 * UV width (planar): * 1023. But the xorg thinks 2048 क्रम height and width. Use
 * the mininum of both.  */
#घोषणा IMAGE_MAX_WIDTH		2048
#घोषणा IMAGE_MAX_HEIGHT	2046 /* 2 * 1023 */
/* on 830 and 845 these large limits result in the card hanging */
#घोषणा IMAGE_MAX_WIDTH_LEGACY	1024
#घोषणा IMAGE_MAX_HEIGHT_LEGACY	1088

/* overlay रेजिस्टर definitions */
/* OCMD रेजिस्टर */
#घोषणा OCMD_TILED_SURFACE	(0x1<<19)
#घोषणा OCMD_MIRROR_MASK	(0x3<<17)
#घोषणा OCMD_MIRROR_MODE	(0x3<<17)
#घोषणा OCMD_MIRROR_HORIZONTAL	(0x1<<17)
#घोषणा OCMD_MIRROR_VERTICAL	(0x2<<17)
#घोषणा OCMD_MIRROR_BOTH	(0x3<<17)
#घोषणा OCMD_BYTEORDER_MASK	(0x3<<14) /* zero क्रम YUYV or FOURCC YUY2 */
#घोषणा OCMD_UV_SWAP		(0x1<<14) /* YVYU */
#घोषणा OCMD_Y_SWAP		(0x2<<14) /* UYVY or FOURCC UYVY */
#घोषणा OCMD_Y_AND_UV_SWAP	(0x3<<14) /* VYUY */
#घोषणा OCMD_SOURCE_FORMAT_MASK (0xf<<10)
#घोषणा OCMD_RGB_888		(0x1<<10) /* not in i965 Intel करोcs */
#घोषणा OCMD_RGB_555		(0x2<<10) /* not in i965 Intel करोcs */
#घोषणा OCMD_RGB_565		(0x3<<10) /* not in i965 Intel करोcs */
#घोषणा OCMD_YUV_422_PACKED	(0x8<<10)
#घोषणा OCMD_YUV_411_PACKED	(0x9<<10) /* not in i965 Intel करोcs */
#घोषणा OCMD_YUV_420_PLANAR	(0xc<<10)
#घोषणा OCMD_YUV_422_PLANAR	(0xd<<10)
#घोषणा OCMD_YUV_410_PLANAR	(0xe<<10) /* also 411 */
#घोषणा OCMD_TVSYNCFLIP_PARITY	(0x1<<9)
#घोषणा OCMD_TVSYNCFLIP_ENABLE	(0x1<<7)
#घोषणा OCMD_BUF_TYPE_MASK	(0x1<<5)
#घोषणा OCMD_BUF_TYPE_FRAME	(0x0<<5)
#घोषणा OCMD_BUF_TYPE_FIELD	(0x1<<5)
#घोषणा OCMD_TEST_MODE		(0x1<<4)
#घोषणा OCMD_BUFFER_SELECT	(0x3<<2)
#घोषणा OCMD_BUFFER0		(0x0<<2)
#घोषणा OCMD_BUFFER1		(0x1<<2)
#घोषणा OCMD_FIELD_SELECT	(0x1<<2)
#घोषणा OCMD_FIELD0		(0x0<<1)
#घोषणा OCMD_FIELD1		(0x1<<1)
#घोषणा OCMD_ENABLE		(0x1<<0)

/* OCONFIG रेजिस्टर */
#घोषणा OCONF_PIPE_MASK		(0x1<<18)
#घोषणा OCONF_PIPE_A		(0x0<<18)
#घोषणा OCONF_PIPE_B		(0x1<<18)
#घोषणा OCONF_GAMMA2_ENABLE	(0x1<<16)
#घोषणा OCONF_CSC_MODE_BT601	(0x0<<5)
#घोषणा OCONF_CSC_MODE_BT709	(0x1<<5)
#घोषणा OCONF_CSC_BYPASS	(0x1<<4)
#घोषणा OCONF_CC_OUT_8BIT	(0x1<<3)
#घोषणा OCONF_TEST_MODE		(0x1<<2)
#घोषणा OCONF_THREE_LINE_BUFFER	(0x1<<0)
#घोषणा OCONF_TWO_LINE_BUFFER	(0x0<<0)

/* DCLRKM (dst-key) रेजिस्टर */
#घोषणा DST_KEY_ENABLE		(0x1<<31)
#घोषणा CLK_RGB24_MASK		0x0
#घोषणा CLK_RGB16_MASK		0x070307
#घोषणा CLK_RGB15_MASK		0x070707

#घोषणा RGB30_TO_COLORKEY(c) \
	((((c) & 0x3fc00000) >> 6) | (((c) & 0x000ff000) >> 4) | (((c) & 0x000003fc) >> 2))
#घोषणा RGB16_TO_COLORKEY(c) \
	((((c) & 0xf800) << 8) | (((c) & 0x07e0) << 5) | (((c) & 0x001f) << 3))
#घोषणा RGB15_TO_COLORKEY(c) \
	((((c) & 0x7c00) << 9) | (((c) & 0x03e0) << 6) | (((c) & 0x001f) << 3))
#घोषणा RGB8I_TO_COLORKEY(c) \
	((((c) & 0xff) << 16) | (((c) & 0xff) << 8) | (((c) & 0xff) << 0))

/* overlay flip addr flag */
#घोषणा OFC_UPDATE		0x1

/* polyphase filter coefficients */
#घोषणा N_HORIZ_Y_TAPS          5
#घोषणा N_VERT_Y_TAPS           3
#घोषणा N_HORIZ_UV_TAPS         3
#घोषणा N_VERT_UV_TAPS          3
#घोषणा N_PHASES                17
#घोषणा MAX_TAPS                5

/* memory bufferd overlay रेजिस्टरs */
काष्ठा overlay_रेजिस्टरs अणु
	u32 OBUF_0Y;
	u32 OBUF_1Y;
	u32 OBUF_0U;
	u32 OBUF_0V;
	u32 OBUF_1U;
	u32 OBUF_1V;
	u32 OSTRIDE;
	u32 YRGB_VPH;
	u32 UV_VPH;
	u32 HORZ_PH;
	u32 INIT_PHS;
	u32 DWINPOS;
	u32 DWINSZ;
	u32 SWIDTH;
	u32 SWIDTHSW;
	u32 SHEIGHT;
	u32 YRGBSCALE;
	u32 UVSCALE;
	u32 OCLRC0;
	u32 OCLRC1;
	u32 DCLRKV;
	u32 DCLRKM;
	u32 SCLRKVH;
	u32 SCLRKVL;
	u32 SCLRKEN;
	u32 OCONFIG;
	u32 OCMD;
	u32 RESERVED1; /* 0x6C */
	u32 OSTART_0Y;
	u32 OSTART_1Y;
	u32 OSTART_0U;
	u32 OSTART_0V;
	u32 OSTART_1U;
	u32 OSTART_1V;
	u32 OTILखातापूर्णF_0Y;
	u32 OTILखातापूर्णF_1Y;
	u32 OTILखातापूर्णF_0U;
	u32 OTILखातापूर्णF_0V;
	u32 OTILखातापूर्णF_1U;
	u32 OTILखातापूर्णF_1V;
	u32 FASTHSCALE; /* 0xA0 */
	u32 UVSCALEV; /* 0xA4 */
	u32 RESERVEDC[(0x200 - 0xA8) / 4]; /* 0xA8 - 0x1FC */
	u16 Y_VCOEFS[N_VERT_Y_TAPS * N_PHASES]; /* 0x200 */
	u16 RESERVEDD[0x100 / 2 - N_VERT_Y_TAPS * N_PHASES];
	u16 Y_HCOEFS[N_HORIZ_Y_TAPS * N_PHASES]; /* 0x300 */
	u16 RESERVEDE[0x200 / 2 - N_HORIZ_Y_TAPS * N_PHASES];
	u16 UV_VCOEFS[N_VERT_UV_TAPS * N_PHASES]; /* 0x500 */
	u16 RESERVEDF[0x100 / 2 - N_VERT_UV_TAPS * N_PHASES];
	u16 UV_HCOEFS[N_HORIZ_UV_TAPS * N_PHASES]; /* 0x600 */
	u16 RESERVEDG[0x100 / 2 - N_HORIZ_UV_TAPS * N_PHASES];
पूर्ण;

काष्ठा पूर्णांकel_overlay अणु
	काष्ठा drm_i915_निजी *i915;
	काष्ठा पूर्णांकel_context *context;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा i915_vma *vma;
	काष्ठा i915_vma *old_vma;
	काष्ठा पूर्णांकel_frontbuffer *frontbuffer;
	bool active;
	bool pfit_active;
	u32 pfit_vscale_ratio; /* shअगरted-poपूर्णांक number, (1<<12) == 1.0 */
	u32 color_key:24;
	u32 color_key_enabled:1;
	u32 brightness, contrast, saturation;
	u32 old_xscale, old_yscale;
	/* रेजिस्टर access */
	काष्ठा drm_i915_gem_object *reg_bo;
	काष्ठा overlay_रेजिस्टरs __iomem *regs;
	u32 flip_addr;
	/* flip handling */
	काष्ठा i915_active last_flip;
	व्योम (*flip_complete)(काष्ठा पूर्णांकel_overlay *ovl);
पूर्ण;

अटल व्योम i830_overlay_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv,
				      bool enable)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	u8 val;

	/* WA_OVERLAY_CLKGATE:alm */
	अगर (enable)
		पूर्णांकel_de_ग_लिखो(dev_priv, DSPCLK_GATE_D, 0);
	अन्यथा
		पूर्णांकel_de_ग_लिखो(dev_priv, DSPCLK_GATE_D,
			       OVRUNIT_CLOCK_GATE_DISABLE);

	/* WA_DISABLE_L2CACHE_CLOCK_GATING:alm */
	pci_bus_पढ़ो_config_byte(pdev->bus,
				 PCI_DEVFN(0, 0), I830_CLOCK_GATE, &val);
	अगर (enable)
		val &= ~I830_L2_CACHE_CLOCK_GATE_DISABLE;
	अन्यथा
		val |= I830_L2_CACHE_CLOCK_GATE_DISABLE;
	pci_bus_ग_लिखो_config_byte(pdev->bus,
				  PCI_DEVFN(0, 0), I830_CLOCK_GATE, val);
पूर्ण

अटल काष्ठा i915_request *
alloc_request(काष्ठा पूर्णांकel_overlay *overlay, व्योम (*fn)(काष्ठा पूर्णांकel_overlay *))
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	overlay->flip_complete = fn;

	rq = i915_request_create(overlay->context);
	अगर (IS_ERR(rq))
		वापस rq;

	err = i915_active_add_request(&overlay->last_flip, rq);
	अगर (err) अणु
		i915_request_add(rq);
		वापस ERR_PTR(err);
	पूर्ण

	वापस rq;
पूर्ण

/* overlay needs to be disable in OCMD reg */
अटल पूर्णांक पूर्णांकel_overlay_on(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	काष्ठा drm_i915_निजी *dev_priv = overlay->i915;
	काष्ठा i915_request *rq;
	u32 *cs;

	drm_WARN_ON(&dev_priv->drm, overlay->active);

	rq = alloc_request(overlay, शून्य);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	overlay->active = true;

	अगर (IS_I830(dev_priv))
		i830_overlay_घड़ी_gating(dev_priv, false);

	*cs++ = MI_OVERLAY_FLIP | MI_OVERLAY_ON;
	*cs++ = overlay->flip_addr | OFC_UPDATE;
	*cs++ = MI_WAIT_FOR_EVENT | MI_WAIT_FOR_OVERLAY_FLIP;
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	i915_request_add(rq);

	वापस i915_active_रुको(&overlay->last_flip);
पूर्ण

अटल व्योम पूर्णांकel_overlay_flip_prepare(काष्ठा पूर्णांकel_overlay *overlay,
				       काष्ठा i915_vma *vma)
अणु
	क्रमागत pipe pipe = overlay->crtc->pipe;
	काष्ठा पूर्णांकel_frontbuffer *frontbuffer = शून्य;

	drm_WARN_ON(&overlay->i915->drm, overlay->old_vma);

	अगर (vma)
		frontbuffer = पूर्णांकel_frontbuffer_get(vma->obj);

	पूर्णांकel_frontbuffer_track(overlay->frontbuffer, frontbuffer,
				INTEL_FRONTBUFFER_OVERLAY(pipe));

	अगर (overlay->frontbuffer)
		पूर्णांकel_frontbuffer_put(overlay->frontbuffer);
	overlay->frontbuffer = frontbuffer;

	पूर्णांकel_frontbuffer_flip_prepare(overlay->i915,
				       INTEL_FRONTBUFFER_OVERLAY(pipe));

	overlay->old_vma = overlay->vma;
	अगर (vma)
		overlay->vma = i915_vma_get(vma);
	अन्यथा
		overlay->vma = शून्य;
पूर्ण

/* overlay needs to be enabled in OCMD reg */
अटल पूर्णांक पूर्णांकel_overlay_जारी(काष्ठा पूर्णांकel_overlay *overlay,
				  काष्ठा i915_vma *vma,
				  bool load_polyphase_filter)
अणु
	काष्ठा drm_i915_निजी *dev_priv = overlay->i915;
	काष्ठा i915_request *rq;
	u32 flip_addr = overlay->flip_addr;
	u32 पंचांगp, *cs;

	drm_WARN_ON(&dev_priv->drm, !overlay->active);

	अगर (load_polyphase_filter)
		flip_addr |= OFC_UPDATE;

	/* check क्रम underruns */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DOVSTA);
	अगर (पंचांगp & (1 << 17))
		drm_dbg(&dev_priv->drm, "overlay underrun, DOVSTA: %x\n", पंचांगp);

	rq = alloc_request(overlay, शून्य);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 2);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	*cs++ = MI_OVERLAY_FLIP | MI_OVERLAY_CONTINUE;
	*cs++ = flip_addr;
	पूर्णांकel_ring_advance(rq, cs);

	पूर्णांकel_overlay_flip_prepare(overlay, vma);
	i915_request_add(rq);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_overlay_release_old_vma(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	काष्ठा i915_vma *vma;

	vma = fetch_and_zero(&overlay->old_vma);
	अगर (drm_WARN_ON(&overlay->i915->drm, !vma))
		वापस;

	पूर्णांकel_frontbuffer_flip_complete(overlay->i915,
					INTEL_FRONTBUFFER_OVERLAY(overlay->crtc->pipe));

	i915_vma_unpin(vma);
	i915_vma_put(vma);
पूर्ण

अटल व्योम
पूर्णांकel_overlay_release_old_vid_tail(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	पूर्णांकel_overlay_release_old_vma(overlay);
पूर्ण

अटल व्योम पूर्णांकel_overlay_off_tail(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	काष्ठा drm_i915_निजी *dev_priv = overlay->i915;

	पूर्णांकel_overlay_release_old_vma(overlay);

	overlay->crtc->overlay = शून्य;
	overlay->crtc = शून्य;
	overlay->active = false;

	अगर (IS_I830(dev_priv))
		i830_overlay_घड़ी_gating(dev_priv, true);
पूर्ण

__i915_active_call अटल व्योम
पूर्णांकel_overlay_last_flip_retire(काष्ठा i915_active *active)
अणु
	काष्ठा पूर्णांकel_overlay *overlay =
		container_of(active, typeof(*overlay), last_flip);

	अगर (overlay->flip_complete)
		overlay->flip_complete(overlay);
पूर्ण

/* overlay needs to be disabled in OCMD reg */
अटल पूर्णांक पूर्णांकel_overlay_off(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	काष्ठा i915_request *rq;
	u32 *cs, flip_addr = overlay->flip_addr;

	drm_WARN_ON(&overlay->i915->drm, !overlay->active);

	/* According to पूर्णांकel करोcs the overlay hw may hang (when चयनing
	 * off) without loading the filter coeffs. It is however unclear whether
	 * this applies to the disabling of the overlay or to the चयनing off
	 * of the hw. Do it in both हालs */
	flip_addr |= OFC_UPDATE;

	rq = alloc_request(overlay, पूर्णांकel_overlay_off_tail);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 6);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	/* रुको क्रम overlay to go idle */
	*cs++ = MI_OVERLAY_FLIP | MI_OVERLAY_CONTINUE;
	*cs++ = flip_addr;
	*cs++ = MI_WAIT_FOR_EVENT | MI_WAIT_FOR_OVERLAY_FLIP;

	/* turn overlay off */
	*cs++ = MI_OVERLAY_FLIP | MI_OVERLAY_OFF;
	*cs++ = flip_addr;
	*cs++ = MI_WAIT_FOR_EVENT | MI_WAIT_FOR_OVERLAY_FLIP;

	पूर्णांकel_ring_advance(rq, cs);

	पूर्णांकel_overlay_flip_prepare(overlay, शून्य);
	i915_request_add(rq);

	वापस i915_active_रुको(&overlay->last_flip);
पूर्ण

/* recover from an पूर्णांकerruption due to a संकेत
 * We have to be careful not to repeat work क्रमever an make क्रमward progess. */
अटल पूर्णांक पूर्णांकel_overlay_recover_from_पूर्णांकerrupt(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	वापस i915_active_रुको(&overlay->last_flip);
पूर्ण

/* Wait क्रम pending overlay flip and release old frame.
 * Needs to be called beक्रमe the overlay रेजिस्टर are changed
 * via पूर्णांकel_overlay_(un)map_regs
 */
अटल पूर्णांक पूर्णांकel_overlay_release_old_vid(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	काष्ठा drm_i915_निजी *dev_priv = overlay->i915;
	काष्ठा i915_request *rq;
	u32 *cs;

	/*
	 * Only रुको अगर there is actually an old frame to release to
	 * guarantee क्रमward progress.
	 */
	अगर (!overlay->old_vma)
		वापस 0;

	अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, GEN2_ISR) & I915_OVERLAY_PLANE_FLIP_PENDING_INTERRUPT)) अणु
		पूर्णांकel_overlay_release_old_vid_tail(overlay);
		वापस 0;
	पूर्ण

	rq = alloc_request(overlay, पूर्णांकel_overlay_release_old_vid_tail);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 2);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	*cs++ = MI_WAIT_FOR_EVENT | MI_WAIT_FOR_OVERLAY_FLIP;
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	i915_request_add(rq);

	वापस i915_active_रुको(&overlay->last_flip);
पूर्ण

व्योम पूर्णांकel_overlay_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_overlay *overlay = dev_priv->overlay;

	अगर (!overlay)
		वापस;

	overlay->old_xscale = 0;
	overlay->old_yscale = 0;
	overlay->crtc = शून्य;
	overlay->active = false;
पूर्ण

अटल पूर्णांक packed_depth_bytes(u32 क्रमmat)
अणु
	चयन (क्रमmat & I915_OVERLAY_DEPTH_MASK) अणु
	हाल I915_OVERLAY_YUV422:
		वापस 4;
	हाल I915_OVERLAY_YUV411:
		/* वापस 6; not implemented */
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक packed_width_bytes(u32 क्रमmat, लघु width)
अणु
	चयन (क्रमmat & I915_OVERLAY_DEPTH_MASK) अणु
	हाल I915_OVERLAY_YUV422:
		वापस width << 1;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक uv_hsubsampling(u32 क्रमmat)
अणु
	चयन (क्रमmat & I915_OVERLAY_DEPTH_MASK) अणु
	हाल I915_OVERLAY_YUV422:
	हाल I915_OVERLAY_YUV420:
		वापस 2;
	हाल I915_OVERLAY_YUV411:
	हाल I915_OVERLAY_YUV410:
		वापस 4;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक uv_vsubsampling(u32 क्रमmat)
अणु
	चयन (क्रमmat & I915_OVERLAY_DEPTH_MASK) अणु
	हाल I915_OVERLAY_YUV420:
	हाल I915_OVERLAY_YUV410:
		वापस 2;
	हाल I915_OVERLAY_YUV422:
	हाल I915_OVERLAY_YUV411:
		वापस 1;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u32 calc_swidthsw(काष्ठा drm_i915_निजी *dev_priv, u32 offset, u32 width)
अणु
	u32 sw;

	अगर (IS_DISPLAY_VER(dev_priv, 2))
		sw = ALIGN((offset & 31) + width, 32);
	अन्यथा
		sw = ALIGN((offset & 63) + width, 64);

	अगर (sw == 0)
		वापस 0;

	वापस (sw - 32) >> 3;
पूर्ण

अटल स्थिर u16 y_अटल_hcoeffs[N_PHASES][N_HORIZ_Y_TAPS] = अणु
	[ 0] = अणु 0x3000, 0xb4a0, 0x1930, 0x1920, 0xb4a0, पूर्ण,
	[ 1] = अणु 0x3000, 0xb500, 0x19d0, 0x1880, 0xb440, पूर्ण,
	[ 2] = अणु 0x3000, 0xb540, 0x1a88, 0x2f80, 0xb3e0, पूर्ण,
	[ 3] = अणु 0x3000, 0xb580, 0x1b30, 0x2e20, 0xb380, पूर्ण,
	[ 4] = अणु 0x3000, 0xb5c0, 0x1bd8, 0x2cc0, 0xb320, पूर्ण,
	[ 5] = अणु 0x3020, 0xb5e0, 0x1c60, 0x2b80, 0xb2c0, पूर्ण,
	[ 6] = अणु 0x3020, 0xb5e0, 0x1cf8, 0x2a20, 0xb260, पूर्ण,
	[ 7] = अणु 0x3020, 0xb5e0, 0x1d80, 0x28e0, 0xb200, पूर्ण,
	[ 8] = अणु 0x3020, 0xb5c0, 0x1e08, 0x3f40, 0xb1c0, पूर्ण,
	[ 9] = अणु 0x3020, 0xb580, 0x1e78, 0x3ce0, 0xb160, पूर्ण,
	[10] = अणु 0x3040, 0xb520, 0x1ed8, 0x3aa0, 0xb120, पूर्ण,
	[11] = अणु 0x3040, 0xb4a0, 0x1f30, 0x3880, 0xb0e0, पूर्ण,
	[12] = अणु 0x3040, 0xb400, 0x1f78, 0x3680, 0xb0a0, पूर्ण,
	[13] = अणु 0x3020, 0xb340, 0x1fb8, 0x34a0, 0xb060, पूर्ण,
	[14] = अणु 0x3020, 0xb240, 0x1fe0, 0x32e0, 0xb040, पूर्ण,
	[15] = अणु 0x3020, 0xb140, 0x1ff8, 0x3160, 0xb020, पूर्ण,
	[16] = अणु 0xb000, 0x3000, 0x0800, 0x3000, 0xb000, पूर्ण,
पूर्ण;

अटल स्थिर u16 uv_अटल_hcoeffs[N_PHASES][N_HORIZ_UV_TAPS] = अणु
	[ 0] = अणु 0x3000, 0x1800, 0x1800, पूर्ण,
	[ 1] = अणु 0xb000, 0x18d0, 0x2e60, पूर्ण,
	[ 2] = अणु 0xb000, 0x1990, 0x2ce0, पूर्ण,
	[ 3] = अणु 0xb020, 0x1a68, 0x2b40, पूर्ण,
	[ 4] = अणु 0xb040, 0x1b20, 0x29e0, पूर्ण,
	[ 5] = अणु 0xb060, 0x1bd8, 0x2880, पूर्ण,
	[ 6] = अणु 0xb080, 0x1c88, 0x3e60, पूर्ण,
	[ 7] = अणु 0xb0a0, 0x1d28, 0x3c00, पूर्ण,
	[ 8] = अणु 0xb0c0, 0x1db8, 0x39e0, पूर्ण,
	[ 9] = अणु 0xb0e0, 0x1e40, 0x37e0, पूर्ण,
	[10] = अणु 0xb100, 0x1eb8, 0x3620, पूर्ण,
	[11] = अणु 0xb100, 0x1f18, 0x34a0, पूर्ण,
	[12] = अणु 0xb100, 0x1f68, 0x3360, पूर्ण,
	[13] = अणु 0xb0e0, 0x1fa8, 0x3240, पूर्ण,
	[14] = अणु 0xb0c0, 0x1fe0, 0x3140, पूर्ण,
	[15] = अणु 0xb060, 0x1ff0, 0x30a0, पूर्ण,
	[16] = अणु 0x3000, 0x0800, 0x3000, पूर्ण,
पूर्ण;

अटल व्योम update_polyphase_filter(काष्ठा overlay_रेजिस्टरs __iomem *regs)
अणु
	स_नकल_toio(regs->Y_HCOEFS, y_अटल_hcoeffs, माप(y_अटल_hcoeffs));
	स_नकल_toio(regs->UV_HCOEFS, uv_अटल_hcoeffs,
		    माप(uv_अटल_hcoeffs));
पूर्ण

अटल bool update_scaling_factors(काष्ठा पूर्णांकel_overlay *overlay,
				   काष्ठा overlay_रेजिस्टरs __iomem *regs,
				   काष्ठा drm_पूर्णांकel_overlay_put_image *params)
अणु
	/* fixed poपूर्णांक with a 12 bit shअगरt */
	u32 xscale, yscale, xscale_UV, yscale_UV;
#घोषणा FP_SHIFT 12
#घोषणा FRACT_MASK 0xfff
	bool scale_changed = false;
	पूर्णांक uv_hscale = uv_hsubsampling(params->flags);
	पूर्णांक uv_vscale = uv_vsubsampling(params->flags);

	अगर (params->dst_width > 1)
		xscale = ((params->src_scan_width - 1) << FP_SHIFT) /
			params->dst_width;
	अन्यथा
		xscale = 1 << FP_SHIFT;

	अगर (params->dst_height > 1)
		yscale = ((params->src_scan_height - 1) << FP_SHIFT) /
			params->dst_height;
	अन्यथा
		yscale = 1 << FP_SHIFT;

	/*अगर (params->क्रमmat & I915_OVERLAY_YUV_PLANAR) अणु*/
	xscale_UV = xscale/uv_hscale;
	yscale_UV = yscale/uv_vscale;
	/* make the Y scale to UV scale ratio an exact multiply */
	xscale = xscale_UV * uv_hscale;
	yscale = yscale_UV * uv_vscale;
	/*पूर्ण अन्यथा अणु
	  xscale_UV = 0;
	  yscale_UV = 0;
	  पूर्ण*/

	अगर (xscale != overlay->old_xscale || yscale != overlay->old_yscale)
		scale_changed = true;
	overlay->old_xscale = xscale;
	overlay->old_yscale = yscale;

	ioग_लिखो32(((yscale & FRACT_MASK) << 20) |
		  ((xscale >> FP_SHIFT)  << 16) |
		  ((xscale & FRACT_MASK) << 3),
		 &regs->YRGBSCALE);

	ioग_लिखो32(((yscale_UV & FRACT_MASK) << 20) |
		  ((xscale_UV >> FP_SHIFT)  << 16) |
		  ((xscale_UV & FRACT_MASK) << 3),
		 &regs->UVSCALE);

	ioग_लिखो32((((yscale    >> FP_SHIFT) << 16) |
		   ((yscale_UV >> FP_SHIFT) << 0)),
		 &regs->UVSCALEV);

	अगर (scale_changed)
		update_polyphase_filter(regs);

	वापस scale_changed;
पूर्ण

अटल व्योम update_colorkey(काष्ठा पूर्णांकel_overlay *overlay,
			    काष्ठा overlay_रेजिस्टरs __iomem *regs)
अणु
	स्थिर काष्ठा पूर्णांकel_plane_state *state =
		to_पूर्णांकel_plane_state(overlay->crtc->base.primary->state);
	u32 key = overlay->color_key;
	u32 क्रमmat = 0;
	u32 flags = 0;

	अगर (overlay->color_key_enabled)
		flags |= DST_KEY_ENABLE;

	अगर (state->uapi.visible)
		क्रमmat = state->hw.fb->क्रमmat->क्रमmat;

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		key = RGB8I_TO_COLORKEY(key);
		flags |= CLK_RGB24_MASK;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		key = RGB15_TO_COLORKEY(key);
		flags |= CLK_RGB15_MASK;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		key = RGB16_TO_COLORKEY(key);
		flags |= CLK_RGB16_MASK;
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_XBGR2101010:
		key = RGB30_TO_COLORKEY(key);
		flags |= CLK_RGB24_MASK;
		अवरोध;
	शेष:
		flags |= CLK_RGB24_MASK;
		अवरोध;
	पूर्ण

	ioग_लिखो32(key, &regs->DCLRKV);
	ioग_लिखो32(flags, &regs->DCLRKM);
पूर्ण

अटल u32 overlay_cmd_reg(काष्ठा drm_पूर्णांकel_overlay_put_image *params)
अणु
	u32 cmd = OCMD_ENABLE | OCMD_BUF_TYPE_FRAME | OCMD_BUFFER0;

	अगर (params->flags & I915_OVERLAY_YUV_PLANAR) अणु
		चयन (params->flags & I915_OVERLAY_DEPTH_MASK) अणु
		हाल I915_OVERLAY_YUV422:
			cmd |= OCMD_YUV_422_PLANAR;
			अवरोध;
		हाल I915_OVERLAY_YUV420:
			cmd |= OCMD_YUV_420_PLANAR;
			अवरोध;
		हाल I915_OVERLAY_YUV411:
		हाल I915_OVERLAY_YUV410:
			cmd |= OCMD_YUV_410_PLANAR;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु /* YUV packed */
		चयन (params->flags & I915_OVERLAY_DEPTH_MASK) अणु
		हाल I915_OVERLAY_YUV422:
			cmd |= OCMD_YUV_422_PACKED;
			अवरोध;
		हाल I915_OVERLAY_YUV411:
			cmd |= OCMD_YUV_411_PACKED;
			अवरोध;
		पूर्ण

		चयन (params->flags & I915_OVERLAY_SWAP_MASK) अणु
		हाल I915_OVERLAY_NO_SWAP:
			अवरोध;
		हाल I915_OVERLAY_UV_SWAP:
			cmd |= OCMD_UV_SWAP;
			अवरोध;
		हाल I915_OVERLAY_Y_SWAP:
			cmd |= OCMD_Y_SWAP;
			अवरोध;
		हाल I915_OVERLAY_Y_AND_UV_SWAP:
			cmd |= OCMD_Y_AND_UV_SWAP;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस cmd;
पूर्ण

अटल काष्ठा i915_vma *पूर्णांकel_overlay_pin_fb(काष्ठा drm_i915_gem_object *new_bo)
अणु
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा i915_vma *vma;
	पूर्णांक ret;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	ret = i915_gem_object_lock(new_bo, &ww);
	अगर (!ret) अणु
		vma = i915_gem_object_pin_to_display_plane(new_bo, &ww, 0,
							   शून्य, PIN_MAPPABLE);
		ret = PTR_ERR_OR_ZERO(vma);
	पूर्ण
	अगर (ret == -EDEADLK) अणु
		ret = i915_gem_ww_ctx_backoff(&ww);
		अगर (!ret)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस vma;
पूर्ण

अटल पूर्णांक पूर्णांकel_overlay_करो_put_image(काष्ठा पूर्णांकel_overlay *overlay,
				      काष्ठा drm_i915_gem_object *new_bo,
				      काष्ठा drm_पूर्णांकel_overlay_put_image *params)
अणु
	काष्ठा overlay_रेजिस्टरs __iomem *regs = overlay->regs;
	काष्ठा drm_i915_निजी *dev_priv = overlay->i915;
	u32 swidth, swidthsw, sheight, ostride;
	क्रमागत pipe pipe = overlay->crtc->pipe;
	bool scale_changed = false;
	काष्ठा i915_vma *vma;
	पूर्णांक ret, पंचांगp_width;

	drm_WARN_ON(&dev_priv->drm,
		    !drm_modeset_is_locked(&dev_priv->drm.mode_config.connection_mutex));

	ret = पूर्णांकel_overlay_release_old_vid(overlay);
	अगर (ret != 0)
		वापस ret;

	atomic_inc(&dev_priv->gpu_error.pending_fb_pin);

	vma = पूर्णांकel_overlay_pin_fb(new_bo);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out_pin_section;
	पूर्ण

	i915_gem_object_flush_frontbuffer(new_bo, ORIGIN_सूचीTYFB);

	अगर (!overlay->active) अणु
		स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
			overlay->crtc->config;
		u32 oconfig = 0;

		अगर (crtc_state->gamma_enable &&
		    crtc_state->gamma_mode == GAMMA_MODE_MODE_8BIT)
			oconfig |= OCONF_CC_OUT_8BIT;
		अगर (crtc_state->gamma_enable)
			oconfig |= OCONF_GAMMA2_ENABLE;
		अगर (IS_DISPLAY_VER(dev_priv, 4))
			oconfig |= OCONF_CSC_MODE_BT709;
		oconfig |= pipe == 0 ?
			OCONF_PIPE_A : OCONF_PIPE_B;
		ioग_लिखो32(oconfig, &regs->OCONFIG);

		ret = पूर्णांकel_overlay_on(overlay);
		अगर (ret != 0)
			जाओ out_unpin;
	पूर्ण

	ioग_लिखो32(params->dst_y << 16 | params->dst_x, &regs->DWINPOS);
	ioग_लिखो32(params->dst_height << 16 | params->dst_width, &regs->DWINSZ);

	अगर (params->flags & I915_OVERLAY_YUV_PACKED)
		पंचांगp_width = packed_width_bytes(params->flags,
					       params->src_width);
	अन्यथा
		पंचांगp_width = params->src_width;

	swidth = params->src_width;
	swidthsw = calc_swidthsw(dev_priv, params->offset_Y, पंचांगp_width);
	sheight = params->src_height;
	ioग_लिखो32(i915_ggtt_offset(vma) + params->offset_Y, &regs->OBUF_0Y);
	ostride = params->stride_Y;

	अगर (params->flags & I915_OVERLAY_YUV_PLANAR) अणु
		पूर्णांक uv_hscale = uv_hsubsampling(params->flags);
		पूर्णांक uv_vscale = uv_vsubsampling(params->flags);
		u32 पंचांगp_U, पंचांगp_V;

		swidth |= (params->src_width / uv_hscale) << 16;
		sheight |= (params->src_height / uv_vscale) << 16;

		पंचांगp_U = calc_swidthsw(dev_priv, params->offset_U,
				      params->src_width / uv_hscale);
		पंचांगp_V = calc_swidthsw(dev_priv, params->offset_V,
				      params->src_width / uv_hscale);
		swidthsw |= max(पंचांगp_U, पंचांगp_V) << 16;

		ioग_लिखो32(i915_ggtt_offset(vma) + params->offset_U,
			  &regs->OBUF_0U);
		ioग_लिखो32(i915_ggtt_offset(vma) + params->offset_V,
			  &regs->OBUF_0V);

		ostride |= params->stride_UV << 16;
	पूर्ण

	ioग_लिखो32(swidth, &regs->SWIDTH);
	ioग_लिखो32(swidthsw, &regs->SWIDTHSW);
	ioग_लिखो32(sheight, &regs->SHEIGHT);
	ioग_लिखो32(ostride, &regs->OSTRIDE);

	scale_changed = update_scaling_factors(overlay, regs, params);

	update_colorkey(overlay, regs);

	ioग_लिखो32(overlay_cmd_reg(params), &regs->OCMD);

	ret = पूर्णांकel_overlay_जारी(overlay, vma, scale_changed);
	अगर (ret)
		जाओ out_unpin;

	वापस 0;

out_unpin:
	i915_vma_unpin(vma);
out_pin_section:
	atomic_dec(&dev_priv->gpu_error.pending_fb_pin);

	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_overlay_चयन_off(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	काष्ठा drm_i915_निजी *dev_priv = overlay->i915;
	पूर्णांक ret;

	drm_WARN_ON(&dev_priv->drm,
		    !drm_modeset_is_locked(&dev_priv->drm.mode_config.connection_mutex));

	ret = पूर्णांकel_overlay_recover_from_पूर्णांकerrupt(overlay);
	अगर (ret != 0)
		वापस ret;

	अगर (!overlay->active)
		वापस 0;

	ret = पूर्णांकel_overlay_release_old_vid(overlay);
	अगर (ret != 0)
		वापस ret;

	ioग_लिखो32(0, &overlay->regs->OCMD);

	वापस पूर्णांकel_overlay_off(overlay);
पूर्ण

अटल पूर्णांक check_overlay_possible_on_crtc(काष्ठा पूर्णांकel_overlay *overlay,
					  काष्ठा पूर्णांकel_crtc *crtc)
अणु
	अगर (!crtc->active)
		वापस -EINVAL;

	/* can't use the overlay with द्विगुन wide pipe */
	अगर (crtc->config->द्विगुन_wide)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम update_pfit_vscale_ratio(काष्ठा पूर्णांकel_overlay *overlay)
अणु
	काष्ठा drm_i915_निजी *dev_priv = overlay->i915;
	u32 pfit_control = पूर्णांकel_de_पढ़ो(dev_priv, PFIT_CONTROL);
	u32 ratio;

	/* XXX: This is not the same logic as in the xorg driver, but more in
	 * line with the पूर्णांकel करोcumentation क्रम the i965
	 */
	अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		/* on i965 use the PGM reg to पढ़ो out the स्वतःscaler values */
		ratio = पूर्णांकel_de_पढ़ो(dev_priv, PFIT_PGM_RATIOS) >> PFIT_VERT_SCALE_SHIFT_965;
	पूर्ण अन्यथा अणु
		अगर (pfit_control & VERT_AUTO_SCALE)
			ratio = पूर्णांकel_de_पढ़ो(dev_priv, PFIT_AUTO_RATIOS);
		अन्यथा
			ratio = पूर्णांकel_de_पढ़ो(dev_priv, PFIT_PGM_RATIOS);
		ratio >>= PFIT_VERT_SCALE_SHIFT;
	पूर्ण

	overlay->pfit_vscale_ratio = ratio;
पूर्ण

अटल पूर्णांक check_overlay_dst(काष्ठा पूर्णांकel_overlay *overlay,
			     काष्ठा drm_पूर्णांकel_overlay_put_image *rec)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config =
		overlay->crtc->config;

	अगर (rec->dst_x < pipe_config->pipe_src_w &&
	    rec->dst_x + rec->dst_width <= pipe_config->pipe_src_w &&
	    rec->dst_y < pipe_config->pipe_src_h &&
	    rec->dst_y + rec->dst_height <= pipe_config->pipe_src_h)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_overlay_scaling(काष्ठा drm_पूर्णांकel_overlay_put_image *rec)
अणु
	u32 पंचांगp;

	/* करोwnscaling limit is 8.0 */
	पंचांगp = ((rec->src_scan_height << 16) / rec->dst_height) >> 16;
	अगर (पंचांगp > 7)
		वापस -EINVAL;

	पंचांगp = ((rec->src_scan_width << 16) / rec->dst_width) >> 16;
	अगर (पंचांगp > 7)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक check_overlay_src(काष्ठा drm_i915_निजी *dev_priv,
			     काष्ठा drm_पूर्णांकel_overlay_put_image *rec,
			     काष्ठा drm_i915_gem_object *new_bo)
अणु
	पूर्णांक uv_hscale = uv_hsubsampling(rec->flags);
	पूर्णांक uv_vscale = uv_vsubsampling(rec->flags);
	u32 stride_mask;
	पूर्णांक depth;
	u32 पंचांगp;

	/* check src dimensions */
	अगर (IS_I845G(dev_priv) || IS_I830(dev_priv)) अणु
		अगर (rec->src_height > IMAGE_MAX_HEIGHT_LEGACY ||
		    rec->src_width  > IMAGE_MAX_WIDTH_LEGACY)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (rec->src_height > IMAGE_MAX_HEIGHT ||
		    rec->src_width  > IMAGE_MAX_WIDTH)
			वापस -EINVAL;
	पूर्ण

	/* better safe than sorry, use 4 as the maximal subsampling ratio */
	अगर (rec->src_height < N_VERT_Y_TAPS*4 ||
	    rec->src_width  < N_HORIZ_Y_TAPS*4)
		वापस -EINVAL;

	/* check alignment स्थिरraपूर्णांकs */
	चयन (rec->flags & I915_OVERLAY_TYPE_MASK) अणु
	हाल I915_OVERLAY_RGB:
		/* not implemented */
		वापस -EINVAL;

	हाल I915_OVERLAY_YUV_PACKED:
		अगर (uv_vscale != 1)
			वापस -EINVAL;

		depth = packed_depth_bytes(rec->flags);
		अगर (depth < 0)
			वापस depth;

		/* ignore UV planes */
		rec->stride_UV = 0;
		rec->offset_U = 0;
		rec->offset_V = 0;
		/* check pixel alignment */
		अगर (rec->offset_Y % depth)
			वापस -EINVAL;
		अवरोध;

	हाल I915_OVERLAY_YUV_PLANAR:
		अगर (uv_vscale < 0 || uv_hscale < 0)
			वापस -EINVAL;
		/* no offset restrictions क्रम planar क्रमmats */
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rec->src_width % uv_hscale)
		वापस -EINVAL;

	/* stride checking */
	अगर (IS_I830(dev_priv) || IS_I845G(dev_priv))
		stride_mask = 255;
	अन्यथा
		stride_mask = 63;

	अगर (rec->stride_Y & stride_mask || rec->stride_UV & stride_mask)
		वापस -EINVAL;
	अगर (IS_DISPLAY_VER(dev_priv, 4) && rec->stride_Y < 512)
		वापस -EINVAL;

	पंचांगp = (rec->flags & I915_OVERLAY_TYPE_MASK) == I915_OVERLAY_YUV_PLANAR ?
		4096 : 8192;
	अगर (rec->stride_Y > पंचांगp || rec->stride_UV > 2*1024)
		वापस -EINVAL;

	/* check buffer dimensions */
	चयन (rec->flags & I915_OVERLAY_TYPE_MASK) अणु
	हाल I915_OVERLAY_RGB:
	हाल I915_OVERLAY_YUV_PACKED:
		/* always 4 Y values per depth pixels */
		अगर (packed_width_bytes(rec->flags, rec->src_width) > rec->stride_Y)
			वापस -EINVAL;

		पंचांगp = rec->stride_Y*rec->src_height;
		अगर (rec->offset_Y + पंचांगp > new_bo->base.size)
			वापस -EINVAL;
		अवरोध;

	हाल I915_OVERLAY_YUV_PLANAR:
		अगर (rec->src_width > rec->stride_Y)
			वापस -EINVAL;
		अगर (rec->src_width/uv_hscale > rec->stride_UV)
			वापस -EINVAL;

		पंचांगp = rec->stride_Y * rec->src_height;
		अगर (rec->offset_Y + पंचांगp > new_bo->base.size)
			वापस -EINVAL;

		पंचांगp = rec->stride_UV * (rec->src_height / uv_vscale);
		अगर (rec->offset_U + पंचांगp > new_bo->base.size ||
		    rec->offset_V + पंचांगp > new_bo->base.size)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_overlay_put_image_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_पूर्णांकel_overlay_put_image *params = data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_overlay *overlay;
	काष्ठा drm_crtc *drmmode_crtc;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा drm_i915_gem_object *new_bo;
	पूर्णांक ret;

	overlay = dev_priv->overlay;
	अगर (!overlay) अणु
		drm_dbg(&dev_priv->drm, "userspace bug: no overlay\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!(params->flags & I915_OVERLAY_ENABLE)) अणु
		drm_modeset_lock_all(dev);
		ret = पूर्णांकel_overlay_चयन_off(overlay);
		drm_modeset_unlock_all(dev);

		वापस ret;
	पूर्ण

	drmmode_crtc = drm_crtc_find(dev, file_priv, params->crtc_id);
	अगर (!drmmode_crtc)
		वापस -ENOENT;
	crtc = to_पूर्णांकel_crtc(drmmode_crtc);

	new_bo = i915_gem_object_lookup(file_priv, params->bo_handle);
	अगर (!new_bo)
		वापस -ENOENT;

	drm_modeset_lock_all(dev);

	अगर (i915_gem_object_is_tiled(new_bo)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "buffer used for overlay image can not be tiled\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ret = पूर्णांकel_overlay_recover_from_पूर्णांकerrupt(overlay);
	अगर (ret != 0)
		जाओ out_unlock;

	अगर (overlay->crtc != crtc) अणु
		ret = पूर्णांकel_overlay_चयन_off(overlay);
		अगर (ret != 0)
			जाओ out_unlock;

		ret = check_overlay_possible_on_crtc(overlay, crtc);
		अगर (ret != 0)
			जाओ out_unlock;

		overlay->crtc = crtc;
		crtc->overlay = overlay;

		/* line too wide, i.e. one-line-mode */
		अगर (crtc->config->pipe_src_w > 1024 &&
		    crtc->config->gmch_pfit.control & PFIT_ENABLE) अणु
			overlay->pfit_active = true;
			update_pfit_vscale_ratio(overlay);
		पूर्ण अन्यथा
			overlay->pfit_active = false;
	पूर्ण

	ret = check_overlay_dst(overlay, params);
	अगर (ret != 0)
		जाओ out_unlock;

	अगर (overlay->pfit_active) अणु
		params->dst_y = (((u32)params->dst_y << 12) /
				 overlay->pfit_vscale_ratio);
		/* shअगरting right rounds करोwnwards, so add 1 */
		params->dst_height = (((u32)params->dst_height << 12) /
				 overlay->pfit_vscale_ratio) + 1;
	पूर्ण

	अगर (params->src_scan_height > params->src_height ||
	    params->src_scan_width > params->src_width) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ret = check_overlay_src(dev_priv, params, new_bo);
	अगर (ret != 0)
		जाओ out_unlock;

	/* Check scaling after src size to prevent a भागide-by-zero. */
	ret = check_overlay_scaling(params);
	अगर (ret != 0)
		जाओ out_unlock;

	ret = पूर्णांकel_overlay_करो_put_image(overlay, new_bo, params);
	अगर (ret != 0)
		जाओ out_unlock;

	drm_modeset_unlock_all(dev);
	i915_gem_object_put(new_bo);

	वापस 0;

out_unlock:
	drm_modeset_unlock_all(dev);
	i915_gem_object_put(new_bo);

	वापस ret;
पूर्ण

अटल व्योम update_reg_attrs(काष्ठा पूर्णांकel_overlay *overlay,
			     काष्ठा overlay_रेजिस्टरs __iomem *regs)
अणु
	ioग_लिखो32((overlay->contrast << 18) | (overlay->brightness & 0xff),
		  &regs->OCLRC0);
	ioग_लिखो32(overlay->saturation, &regs->OCLRC1);
पूर्ण

अटल bool check_gamma_bounds(u32 gamma1, u32 gamma2)
अणु
	पूर्णांक i;

	अगर (gamma1 & 0xff000000 || gamma2 & 0xff000000)
		वापस false;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (((gamma1 >> i*8) & 0xff) >= ((gamma2 >> i*8) & 0xff))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool check_gamma5_errata(u32 gamma5)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (((gamma5 >> i*8) & 0xff) == 0x80)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक check_gamma(काष्ठा drm_पूर्णांकel_overlay_attrs *attrs)
अणु
	अगर (!check_gamma_bounds(0, attrs->gamma0) ||
	    !check_gamma_bounds(attrs->gamma0, attrs->gamma1) ||
	    !check_gamma_bounds(attrs->gamma1, attrs->gamma2) ||
	    !check_gamma_bounds(attrs->gamma2, attrs->gamma3) ||
	    !check_gamma_bounds(attrs->gamma3, attrs->gamma4) ||
	    !check_gamma_bounds(attrs->gamma4, attrs->gamma5) ||
	    !check_gamma_bounds(attrs->gamma5, 0x00ffffff))
		वापस -EINVAL;

	अगर (!check_gamma5_errata(attrs->gamma5))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_overlay_attrs_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_पूर्णांकel_overlay_attrs *attrs = data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_overlay *overlay;
	पूर्णांक ret;

	overlay = dev_priv->overlay;
	अगर (!overlay) अणु
		drm_dbg(&dev_priv->drm, "userspace bug: no overlay\n");
		वापस -ENODEV;
	पूर्ण

	drm_modeset_lock_all(dev);

	ret = -EINVAL;
	अगर (!(attrs->flags & I915_OVERLAY_UPDATE_ATTRS)) अणु
		attrs->color_key  = overlay->color_key;
		attrs->brightness = overlay->brightness;
		attrs->contrast   = overlay->contrast;
		attrs->saturation = overlay->saturation;

		अगर (!IS_DISPLAY_VER(dev_priv, 2)) अणु
			attrs->gamma0 = पूर्णांकel_de_पढ़ो(dev_priv, OGAMC0);
			attrs->gamma1 = पूर्णांकel_de_पढ़ो(dev_priv, OGAMC1);
			attrs->gamma2 = पूर्णांकel_de_पढ़ो(dev_priv, OGAMC2);
			attrs->gamma3 = पूर्णांकel_de_पढ़ो(dev_priv, OGAMC3);
			attrs->gamma4 = पूर्णांकel_de_पढ़ो(dev_priv, OGAMC4);
			attrs->gamma5 = पूर्णांकel_de_पढ़ो(dev_priv, OGAMC5);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (attrs->brightness < -128 || attrs->brightness > 127)
			जाओ out_unlock;
		अगर (attrs->contrast > 255)
			जाओ out_unlock;
		अगर (attrs->saturation > 1023)
			जाओ out_unlock;

		overlay->color_key  = attrs->color_key;
		overlay->brightness = attrs->brightness;
		overlay->contrast   = attrs->contrast;
		overlay->saturation = attrs->saturation;

		update_reg_attrs(overlay, overlay->regs);

		अगर (attrs->flags & I915_OVERLAY_UPDATE_GAMMA) अणु
			अगर (IS_DISPLAY_VER(dev_priv, 2))
				जाओ out_unlock;

			अगर (overlay->active) अणु
				ret = -EBUSY;
				जाओ out_unlock;
			पूर्ण

			ret = check_gamma(attrs);
			अगर (ret)
				जाओ out_unlock;

			पूर्णांकel_de_ग_लिखो(dev_priv, OGAMC0, attrs->gamma0);
			पूर्णांकel_de_ग_लिखो(dev_priv, OGAMC1, attrs->gamma1);
			पूर्णांकel_de_ग_लिखो(dev_priv, OGAMC2, attrs->gamma2);
			पूर्णांकel_de_ग_लिखो(dev_priv, OGAMC3, attrs->gamma3);
			पूर्णांकel_de_ग_लिखो(dev_priv, OGAMC4, attrs->gamma4);
			पूर्णांकel_de_ग_लिखो(dev_priv, OGAMC5, attrs->gamma5);
		पूर्ण
	पूर्ण
	overlay->color_key_enabled = (attrs->flags & I915_OVERLAY_DISABLE_DEST_COLORKEY) == 0;

	ret = 0;
out_unlock:
	drm_modeset_unlock_all(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक get_रेजिस्टरs(काष्ठा पूर्णांकel_overlay *overlay, bool use_phys)
अणु
	काष्ठा drm_i915_निजी *i915 = overlay->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	obj = i915_gem_object_create_stolen(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0, PIN_MAPPABLE);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_put_bo;
	पूर्ण

	अगर (use_phys)
		overlay->flip_addr = sg_dma_address(obj->mm.pages->sgl);
	अन्यथा
		overlay->flip_addr = i915_ggtt_offset(vma);
	overlay->regs = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);

	अगर (IS_ERR(overlay->regs)) अणु
		err = PTR_ERR(overlay->regs);
		जाओ err_put_bo;
	पूर्ण

	overlay->reg_bo = obj;
	वापस 0;

err_put_bo:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

व्योम पूर्णांकel_overlay_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_overlay *overlay;
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांक ret;

	अगर (!HAS_OVERLAY(dev_priv))
		वापस;

	engine = dev_priv->gt.engine[RCS0];
	अगर (!engine || !engine->kernel_context)
		वापस;

	overlay = kzalloc(माप(*overlay), GFP_KERNEL);
	अगर (!overlay)
		वापस;

	overlay->i915 = dev_priv;
	overlay->context = engine->kernel_context;
	GEM_BUG_ON(!overlay->context);

	overlay->color_key = 0x0101fe;
	overlay->color_key_enabled = true;
	overlay->brightness = -19;
	overlay->contrast = 75;
	overlay->saturation = 146;

	i915_active_init(&overlay->last_flip,
			 शून्य, पूर्णांकel_overlay_last_flip_retire);

	ret = get_रेजिस्टरs(overlay, OVERLAY_NEEDS_PHYSICAL(dev_priv));
	अगर (ret)
		जाओ out_मुक्त;

	स_रखो_io(overlay->regs, 0, माप(काष्ठा overlay_रेजिस्टरs));
	update_polyphase_filter(overlay->regs);
	update_reg_attrs(overlay, overlay->regs);

	dev_priv->overlay = overlay;
	drm_info(&dev_priv->drm, "Initialized overlay support.\n");
	वापस;

out_मुक्त:
	kमुक्त(overlay);
पूर्ण

व्योम पूर्णांकel_overlay_cleanup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_overlay *overlay;

	overlay = fetch_and_zero(&dev_priv->overlay);
	अगर (!overlay)
		वापस;

	/*
	 * The bo's should be free'd by the generic code alपढ़ोy.
	 * Furthermore modesetting tearकरोwn happens beक्रमehand so the
	 * hardware should be off alपढ़ोy.
	 */
	drm_WARN_ON(&dev_priv->drm, overlay->active);

	i915_gem_object_put(overlay->reg_bo);
	i915_active_fini(&overlay->last_flip);

	kमुक्त(overlay);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR)

काष्ठा पूर्णांकel_overlay_error_state अणु
	काष्ठा overlay_रेजिस्टरs regs;
	अचिन्हित दीर्घ base;
	u32 करोvsta;
	u32 isr;
पूर्ण;

काष्ठा पूर्णांकel_overlay_error_state *
पूर्णांकel_overlay_capture_error_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_overlay *overlay = dev_priv->overlay;
	काष्ठा पूर्णांकel_overlay_error_state *error;

	अगर (!overlay || !overlay->active)
		वापस शून्य;

	error = kदो_स्मृति(माप(*error), GFP_ATOMIC);
	अगर (error == शून्य)
		वापस शून्य;

	error->करोvsta = पूर्णांकel_de_पढ़ो(dev_priv, DOVSTA);
	error->isr = पूर्णांकel_de_पढ़ो(dev_priv, GEN2_ISR);
	error->base = overlay->flip_addr;

	स_नकल_fromio(&error->regs, overlay->regs, माप(error->regs));

	वापस error;
पूर्ण

व्योम
पूर्णांकel_overlay_prपूर्णांक_error_state(काष्ठा drm_i915_error_state_buf *m,
				काष्ठा पूर्णांकel_overlay_error_state *error)
अणु
	i915_error_म_लिखो(m, "Overlay, status: 0x%08x, interrupt: 0x%08x\n",
			  error->करोvsta, error->isr);
	i915_error_म_लिखो(m, "  Register file at 0x%08lx:\n",
			  error->base);

#घोषणा P(x) i915_error_म_लिखो(m, "    " #x ":	0x%08x\n", error->regs.x)
	P(OBUF_0Y);
	P(OBUF_1Y);
	P(OBUF_0U);
	P(OBUF_0V);
	P(OBUF_1U);
	P(OBUF_1V);
	P(OSTRIDE);
	P(YRGB_VPH);
	P(UV_VPH);
	P(HORZ_PH);
	P(INIT_PHS);
	P(DWINPOS);
	P(DWINSZ);
	P(SWIDTH);
	P(SWIDTHSW);
	P(SHEIGHT);
	P(YRGBSCALE);
	P(UVSCALE);
	P(OCLRC0);
	P(OCLRC1);
	P(DCLRKV);
	P(DCLRKM);
	P(SCLRKVH);
	P(SCLRKVL);
	P(SCLRKEN);
	P(OCONFIG);
	P(OCMD);
	P(OSTART_0Y);
	P(OSTART_1Y);
	P(OSTART_0U);
	P(OSTART_0V);
	P(OSTART_1U);
	P(OSTART_1V);
	P(OTILखातापूर्णF_0Y);
	P(OTILखातापूर्णF_1Y);
	P(OTILखातापूर्णF_0U);
	P(OTILखातापूर्णF_0V);
	P(OTILखातापूर्णF_1U);
	P(OTILखातापूर्णF_1V);
	P(FASTHSCALE);
	P(UVSCALEV);
#अघोषित P
पूर्ण

#पूर्ण_अगर
