<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2006-2011 Intel Corporation
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Patrik Jakobsson <patrik.r.jakobsson@gmail.com>
 */

#अगर_अघोषित _GMA_DISPLAY_H_
#घोषणा _GMA_DISPLAY_H_

#समावेश <linux/pm_runसमय.स>
#समावेश <drm/drm_vblank.h>

काष्ठा drm_encoder;
काष्ठा drm_mode_set;

काष्ठा gma_घड़ी_प्रकार अणु
	/* given values */
	पूर्णांक n;
	पूर्णांक m1, m2;
	पूर्णांक p1, p2;
	/* derived values */
	पूर्णांक करोt;
	पूर्णांक vco;
	पूर्णांक m;
	पूर्णांक p;
पूर्ण;

काष्ठा gma_range_t अणु
	पूर्णांक min, max;
पूर्ण;

काष्ठा gma_p2_t अणु
	पूर्णांक करोt_limit;
	पूर्णांक p2_slow, p2_fast;
पूर्ण;

काष्ठा gma_limit_t अणु
	काष्ठा gma_range_t करोt, vco, n, m, m1, m2, p, p1;
	काष्ठा gma_p2_t p2;
	bool (*find_pll)(स्थिर काष्ठा gma_limit_t *, काष्ठा drm_crtc *,
			 पूर्णांक target, पूर्णांक refclk,
			 काष्ठा gma_घड़ी_प्रकार *best_घड़ी);
पूर्ण;

काष्ठा gma_घड़ी_funcs अणु
	व्योम (*घड़ी)(पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *घड़ी);
	स्थिर काष्ठा gma_limit_t *(*limit)(काष्ठा drm_crtc *crtc, पूर्णांक refclk);
	bool (*pll_is_valid)(काष्ठा drm_crtc *crtc,
			     स्थिर काष्ठा gma_limit_t *limit,
			     काष्ठा gma_घड़ी_प्रकार *घड़ी);
पूर्ण;

/* Common pipe related functions */
बाह्य bool gma_pipe_has_type(काष्ठा drm_crtc *crtc, पूर्णांक type);
बाह्य व्योम gma_रुको_क्रम_vblank(काष्ठा drm_device *dev);
बाह्य पूर्णांक gma_pipe_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
			     काष्ठा drm_framebuffer *old_fb);
बाह्य पूर्णांक gma_crtc_cursor_set(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_file *file_priv,
			       uपूर्णांक32_t handle,
			       uपूर्णांक32_t width, uपूर्णांक32_t height);
बाह्य पूर्णांक gma_crtc_cursor_move(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y);
बाह्य व्योम gma_crtc_load_lut(काष्ठा drm_crtc *crtc);
बाह्य पूर्णांक gma_crtc_gamma_set(काष्ठा drm_crtc *crtc, u16 *red, u16 *green,
			      u16 *blue, u32 size,
			      काष्ठा drm_modeset_acquire_ctx *ctx);
बाह्य व्योम gma_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode);
बाह्य व्योम gma_crtc_prepare(काष्ठा drm_crtc *crtc);
बाह्य व्योम gma_crtc_commit(काष्ठा drm_crtc *crtc);
बाह्य व्योम gma_crtc_disable(काष्ठा drm_crtc *crtc);
बाह्य व्योम gma_crtc_destroy(काष्ठा drm_crtc *crtc);
बाह्य पूर्णांक gma_crtc_page_flip(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_framebuffer *fb,
			      काष्ठा drm_pending_vblank_event *event,
			      uपूर्णांक32_t page_flip_flags,
			      काष्ठा drm_modeset_acquire_ctx *ctx);
बाह्य पूर्णांक gma_crtc_set_config(काष्ठा drm_mode_set *set,
			       काष्ठा drm_modeset_acquire_ctx *ctx);

बाह्य व्योम gma_crtc_save(काष्ठा drm_crtc *crtc);
बाह्य व्योम gma_crtc_restore(काष्ठा drm_crtc *crtc);

बाह्य व्योम gma_encoder_prepare(काष्ठा drm_encoder *encoder);
बाह्य व्योम gma_encoder_commit(काष्ठा drm_encoder *encoder);
बाह्य व्योम gma_encoder_destroy(काष्ठा drm_encoder *encoder);

/* Common घड़ी related functions */
बाह्य स्थिर काष्ठा gma_limit_t *gma_limit(काष्ठा drm_crtc *crtc, पूर्णांक refclk);
बाह्य व्योम gma_घड़ी(पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *घड़ी);
बाह्य bool gma_pll_is_valid(काष्ठा drm_crtc *crtc,
			     स्थिर काष्ठा gma_limit_t *limit,
			     काष्ठा gma_घड़ी_प्रकार *घड़ी);
बाह्य bool gma_find_best_pll(स्थिर काष्ठा gma_limit_t *limit,
			      काष्ठा drm_crtc *crtc, पूर्णांक target, पूर्णांक refclk,
			      काष्ठा gma_घड़ी_प्रकार *best_घड़ी);
#पूर्ण_अगर
