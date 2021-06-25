<शैली गुरु>
/*
 * Copyright तऊ 2006-2019 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _INTEL_DISPLAY_H_
#घोषणा _INTEL_DISPLAY_H_

#समावेश <drm/drm_util.h>

क्रमागत link_m_n_set;
क्रमागत drm_scaling_filter;
काष्ठा dpll;
काष्ठा drm_connector;
काष्ठा drm_device;
काष्ठा drm_display_mode;
काष्ठा drm_encoder;
काष्ठा drm_file;
काष्ठा drm_क्रमmat_info;
काष्ठा drm_framebuffer;
काष्ठा drm_i915_error_state_buf;
काष्ठा drm_i915_gem_object;
काष्ठा drm_i915_निजी;
काष्ठा drm_mode_fb_cmd2;
काष्ठा drm_modeset_acquire_ctx;
काष्ठा drm_plane;
काष्ठा drm_plane_state;
काष्ठा i915_ggtt_view;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_digital_port;
काष्ठा पूर्णांकel_dp;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_initial_plane_config;
काष्ठा पूर्णांकel_load_detect_pipe;
काष्ठा पूर्णांकel_plane;
काष्ठा पूर्णांकel_plane_state;
काष्ठा पूर्णांकel_remapped_info;
काष्ठा पूर्णांकel_rotation_info;

क्रमागत i915_gpio अणु
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH,
	__GPIOI_UNUSED,
	GPIOJ,
	GPIOK,
	GPIOL,
	GPIOM,
	GPION,
	GPIOO,
पूर्ण;

/*
 * Keep the pipe क्रमागत values fixed: the code assumes that PIPE_A=0, the
 * rest have consecutive values and match the क्रमागत values of transcoders
 * with a 1:1 transcoder -> pipe mapping.
 */
क्रमागत pipe अणु
	INVALID_PIPE = -1,

	PIPE_A = 0,
	PIPE_B,
	PIPE_C,
	PIPE_D,
	_PIPE_EDP,

	I915_MAX_PIPES = _PIPE_EDP
पूर्ण;

#घोषणा pipe_name(p) ((p) + 'A')

क्रमागत transcoder अणु
	INVALID_TRANSCODER = -1,
	/*
	 * The following transcoders have a 1:1 transcoder -> pipe mapping,
	 * keep their values fixed: the code assumes that TRANSCODER_A=0, the
	 * rest have consecutive values and match the क्रमागत values of the pipes
	 * they map to.
	 */
	TRANSCODER_A = PIPE_A,
	TRANSCODER_B = PIPE_B,
	TRANSCODER_C = PIPE_C,
	TRANSCODER_D = PIPE_D,

	/*
	 * The following transcoders can map to any pipe, their क्रमागत value
	 * करोesn't need to stay fixed.
	 */
	TRANSCODER_EDP,
	TRANSCODER_DSI_0,
	TRANSCODER_DSI_1,
	TRANSCODER_DSI_A = TRANSCODER_DSI_0,	/* legacy DSI */
	TRANSCODER_DSI_C = TRANSCODER_DSI_1,	/* legacy DSI */

	I915_MAX_TRANSCODERS
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *transcoder_name(क्रमागत transcoder transcoder)
अणु
	चयन (transcoder) अणु
	हाल TRANSCODER_A:
		वापस "A";
	हाल TRANSCODER_B:
		वापस "B";
	हाल TRANSCODER_C:
		वापस "C";
	हाल TRANSCODER_D:
		वापस "D";
	हाल TRANSCODER_EDP:
		वापस "EDP";
	हाल TRANSCODER_DSI_A:
		वापस "DSI A";
	हाल TRANSCODER_DSI_C:
		वापस "DSI C";
	शेष:
		वापस "<invalid>";
	पूर्ण
पूर्ण

अटल अंतरभूत bool transcoder_is_dsi(क्रमागत transcoder transcoder)
अणु
	वापस transcoder == TRANSCODER_DSI_A || transcoder == TRANSCODER_DSI_C;
पूर्ण

/*
 * Global legacy plane identअगरier. Valid only क्रम primary/sprite
 * planes on pre-g4x, and only क्रम primary planes on g4x-bdw.
 */
क्रमागत i9xx_plane_id अणु
	PLANE_A,
	PLANE_B,
	PLANE_C,
पूर्ण;

#घोषणा plane_name(p) ((p) + 'A')
#घोषणा sprite_name(p, s) ((p) * RUNTIME_INFO(dev_priv)->num_sprites[(p)] + (s) + 'A')

/*
 * Per-pipe plane identअगरier.
 * I915_MAX_PLANES in the क्रमागत below is the maximum (across all platक्रमms)
 * number of planes per CRTC.  Not all platक्रमms really have this many planes,
 * which means some arrays of size I915_MAX_PLANES may have unused entries
 * between the topmost sprite plane and the cursor plane.
 *
 * This is expected to be passed to various रेजिस्टर macros
 * (eg. PLANE_CTL(), PS_PLANE_SEL(), etc.) so adjust with care.
 */
क्रमागत plane_id अणु
	PLANE_PRIMARY,
	PLANE_SPRITE0,
	PLANE_SPRITE1,
	PLANE_SPRITE2,
	PLANE_SPRITE3,
	PLANE_SPRITE4,
	PLANE_SPRITE5,
	PLANE_CURSOR,

	I915_MAX_PLANES,
पूर्ण;

#घोषणा क्रम_each_plane_id_on_crtc(__crtc, __p) \
	क्रम ((__p) = PLANE_PRIMARY; (__p) < I915_MAX_PLANES; (__p)++) \
		क्रम_each_अगर((__crtc)->plane_ids_mask & BIT(__p))

#घोषणा क्रम_each_dbuf_slice_in_mask(__slice, __mask) \
	क्रम ((__slice) = DBUF_S1; (__slice) < I915_MAX_DBUF_SLICES; (__slice)++) \
		क्रम_each_अगर((BIT(__slice)) & (__mask))

#घोषणा क्रम_each_dbuf_slice(__slice) \
	क्रम_each_dbuf_slice_in_mask(__slice, BIT(I915_MAX_DBUF_SLICES) - 1)

क्रमागत port अणु
	PORT_NONE = -1,

	PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G,
	PORT_H,
	PORT_I,

	/* tgl+ */
	PORT_TC1 = PORT_D,
	PORT_TC2,
	PORT_TC3,
	PORT_TC4,
	PORT_TC5,
	PORT_TC6,

	I915_MAX_PORTS
पूर्ण;

#घोषणा port_name(p) ((p) + 'A')

/*
 * Ports identअगरier referenced from other drivers.
 * Expected to reमुख्य stable over समय
 */
अटल अंतरभूत स्थिर अक्षर *port_identअगरier(क्रमागत port port)
अणु
	चयन (port) अणु
	हाल PORT_A:
		वापस "Port A";
	हाल PORT_B:
		वापस "Port B";
	हाल PORT_C:
		वापस "Port C";
	हाल PORT_D:
		वापस "Port D";
	हाल PORT_E:
		वापस "Port E";
	हाल PORT_F:
		वापस "Port F";
	हाल PORT_G:
		वापस "Port G";
	हाल PORT_H:
		वापस "Port H";
	हाल PORT_I:
		वापस "Port I";
	शेष:
		वापस "<invalid>";
	पूर्ण
पूर्ण

क्रमागत tc_port अणु
	TC_PORT_NONE = -1,

	TC_PORT_1 = 0,
	TC_PORT_2,
	TC_PORT_3,
	TC_PORT_4,
	TC_PORT_5,
	TC_PORT_6,

	I915_MAX_TC_PORTS
पूर्ण;

क्रमागत tc_port_mode अणु
	TC_PORT_TBT_ALT,
	TC_PORT_DP_ALT,
	TC_PORT_LEGACY,
पूर्ण;

क्रमागत dpio_channel अणु
	DPIO_CH0,
	DPIO_CH1
पूर्ण;

क्रमागत dpio_phy अणु
	DPIO_PHY0,
	DPIO_PHY1,
	DPIO_PHY2,
पूर्ण;

क्रमागत aux_ch अणु
	AUX_CH_A,
	AUX_CH_B,
	AUX_CH_C,
	AUX_CH_D,
	AUX_CH_E, /* ICL+ */
	AUX_CH_F,
	AUX_CH_G,
	AUX_CH_H,
	AUX_CH_I,

	/* tgl+ */
	AUX_CH_USBC1 = AUX_CH_D,
	AUX_CH_USBC2,
	AUX_CH_USBC3,
	AUX_CH_USBC4,
	AUX_CH_USBC5,
	AUX_CH_USBC6,
पूर्ण;

#घोषणा aux_ch_name(a) ((a) + 'A')

/* Used by dp and fdi links */
काष्ठा पूर्णांकel_link_m_n अणु
	u32 tu;
	u32 gmch_m;
	u32 gmch_n;
	u32 link_m;
	u32 link_n;
पूर्ण;

क्रमागत phy अणु
	PHY_NONE = -1,

	PHY_A = 0,
	PHY_B,
	PHY_C,
	PHY_D,
	PHY_E,
	PHY_F,
	PHY_G,
	PHY_H,
	PHY_I,

	I915_MAX_PHYS
पूर्ण;

#घोषणा phy_name(a) ((a) + 'A')

क्रमागत phy_fia अणु
	FIA1,
	FIA2,
	FIA3,
पूर्ण;

#घोषणा क्रम_each_pipe(__dev_priv, __p) \
	क्रम ((__p) = 0; (__p) < I915_MAX_PIPES; (__p)++) \
		क्रम_each_अगर(INTEL_INFO(__dev_priv)->pipe_mask & BIT(__p))

#घोषणा क्रम_each_pipe_masked(__dev_priv, __p, __mask) \
	क्रम_each_pipe(__dev_priv, __p) \
		क्रम_each_अगर((__mask) & BIT(__p))

#घोषणा क्रम_each_cpu_transcoder(__dev_priv, __t) \
	क्रम ((__t) = 0; (__t) < I915_MAX_TRANSCODERS; (__t)++)	\
		क्रम_each_अगर (INTEL_INFO(__dev_priv)->cpu_transcoder_mask & BIT(__t))

#घोषणा क्रम_each_cpu_transcoder_masked(__dev_priv, __t, __mask) \
	क्रम_each_cpu_transcoder(__dev_priv, __t) \
		क्रम_each_अगर ((__mask) & BIT(__t))

#घोषणा क्रम_each_sprite(__dev_priv, __p, __s)				\
	क्रम ((__s) = 0;							\
	     (__s) < RUNTIME_INFO(__dev_priv)->num_sprites[(__p)];	\
	     (__s)++)

#घोषणा क्रम_each_port(__port) \
	क्रम ((__port) = PORT_A; (__port) < I915_MAX_PORTS; (__port)++)

#घोषणा क्रम_each_port_masked(__port, __ports_mask)			\
	क्रम_each_port(__port)						\
		क्रम_each_अगर((__ports_mask) & BIT(__port))

#घोषणा क्रम_each_phy_masked(__phy, __phys_mask) \
	क्रम ((__phy) = PHY_A; (__phy) < I915_MAX_PHYS; (__phy)++)	\
		क्रम_each_अगर((__phys_mask) & BIT(__phy))

#घोषणा क्रम_each_crtc(dev, crtc) \
	list_क्रम_each_entry(crtc, &(dev)->mode_config.crtc_list, head)

#घोषणा क्रम_each_पूर्णांकel_plane(dev, पूर्णांकel_plane) \
	list_क्रम_each_entry(पूर्णांकel_plane,			\
			    &(dev)->mode_config.plane_list,	\
			    base.head)

#घोषणा क्रम_each_पूर्णांकel_plane_mask(dev, पूर्णांकel_plane, plane_mask)		\
	list_क्रम_each_entry(पूर्णांकel_plane,				\
			    &(dev)->mode_config.plane_list,		\
			    base.head)					\
		क्रम_each_अगर((plane_mask) &				\
			    drm_plane_mask(&पूर्णांकel_plane->base))

#घोषणा क्रम_each_पूर्णांकel_plane_on_crtc(dev, पूर्णांकel_crtc, पूर्णांकel_plane)	\
	list_क्रम_each_entry(पूर्णांकel_plane,				\
			    &(dev)->mode_config.plane_list,		\
			    base.head)					\
		क्रम_each_अगर((पूर्णांकel_plane)->pipe == (पूर्णांकel_crtc)->pipe)

#घोषणा क्रम_each_पूर्णांकel_crtc(dev, पूर्णांकel_crtc)				\
	list_क्रम_each_entry(पूर्णांकel_crtc,					\
			    &(dev)->mode_config.crtc_list,		\
			    base.head)

#घोषणा क्रम_each_पूर्णांकel_crtc_mask(dev, पूर्णांकel_crtc, crtc_mask)		\
	list_क्रम_each_entry(पूर्णांकel_crtc,					\
			    &(dev)->mode_config.crtc_list,		\
			    base.head)					\
		क्रम_each_अगर((crtc_mask) & drm_crtc_mask(&पूर्णांकel_crtc->base))

#घोषणा क्रम_each_पूर्णांकel_encoder(dev, पूर्णांकel_encoder)		\
	list_क्रम_each_entry(पूर्णांकel_encoder,			\
			    &(dev)->mode_config.encoder_list,	\
			    base.head)

#घोषणा क्रम_each_पूर्णांकel_encoder_mask(dev, पूर्णांकel_encoder, encoder_mask)	\
	list_क्रम_each_entry(पूर्णांकel_encoder,				\
			    &(dev)->mode_config.encoder_list,		\
			    base.head)					\
		क्रम_each_अगर((encoder_mask) &				\
			    drm_encoder_mask(&पूर्णांकel_encoder->base))

#घोषणा क्रम_each_पूर्णांकel_encoder_mask_with_psr(dev, पूर्णांकel_encoder, encoder_mask) \
	list_क्रम_each_entry((पूर्णांकel_encoder), &(dev)->mode_config.encoder_list, base.head) \
		क्रम_each_अगर(((encoder_mask) & drm_encoder_mask(&(पूर्णांकel_encoder)->base)) && \
			    पूर्णांकel_encoder_can_psr(पूर्णांकel_encoder))

#घोषणा क्रम_each_पूर्णांकel_dp(dev, पूर्णांकel_encoder)			\
	क्रम_each_पूर्णांकel_encoder(dev, पूर्णांकel_encoder)		\
		क्रम_each_अगर(पूर्णांकel_encoder_is_dp(पूर्णांकel_encoder))

#घोषणा क्रम_each_पूर्णांकel_encoder_with_psr(dev, पूर्णांकel_encoder) \
	क्रम_each_पूर्णांकel_encoder((dev), (पूर्णांकel_encoder)) \
		क्रम_each_अगर(पूर्णांकel_encoder_can_psr(पूर्णांकel_encoder))

#घोषणा क्रम_each_पूर्णांकel_connector_iter(पूर्णांकel_connector, iter) \
	जबतक ((पूर्णांकel_connector = to_पूर्णांकel_connector(drm_connector_list_iter_next(iter))))

#घोषणा क्रम_each_encoder_on_crtc(dev, __crtc, पूर्णांकel_encoder) \
	list_क्रम_each_entry((पूर्णांकel_encoder), &(dev)->mode_config.encoder_list, base.head) \
		क्रम_each_अगर((पूर्णांकel_encoder)->base.crtc == (__crtc))

#घोषणा क्रम_each_connector_on_encoder(dev, __encoder, पूर्णांकel_connector) \
	list_क्रम_each_entry((पूर्णांकel_connector), &(dev)->mode_config.connector_list, base.head) \
		क्रम_each_अगर((पूर्णांकel_connector)->base.encoder == (__encoder))

#घोषणा क्रम_each_old_पूर्णांकel_plane_in_state(__state, plane, old_plane_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_total_plane && \
		     ((plane) = to_पूर्णांकel_plane((__state)->base.planes[__i].ptr), \
		      (old_plane_state) = to_पूर्णांकel_plane_state((__state)->base.planes[__i].old_state), 1); \
	     (__i)++) \
		क्रम_each_अगर(plane)

#घोषणा क्रम_each_new_पूर्णांकel_plane_in_state(__state, plane, new_plane_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_total_plane && \
		     ((plane) = to_पूर्णांकel_plane((__state)->base.planes[__i].ptr), \
		      (new_plane_state) = to_पूर्णांकel_plane_state((__state)->base.planes[__i].new_state), 1); \
	     (__i)++) \
		क्रम_each_अगर(plane)

#घोषणा क्रम_each_new_पूर्णांकel_crtc_in_state(__state, crtc, new_crtc_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_crtc && \
		     ((crtc) = to_पूर्णांकel_crtc((__state)->base.crtcs[__i].ptr), \
		      (new_crtc_state) = to_पूर्णांकel_crtc_state((__state)->base.crtcs[__i].new_state), 1); \
	     (__i)++) \
		क्रम_each_अगर(crtc)

#घोषणा क्रम_each_oldnew_पूर्णांकel_plane_in_state(__state, plane, old_plane_state, new_plane_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_total_plane && \
		     ((plane) = to_पूर्णांकel_plane((__state)->base.planes[__i].ptr), \
		      (old_plane_state) = to_पूर्णांकel_plane_state((__state)->base.planes[__i].old_state), \
		      (new_plane_state) = to_पूर्णांकel_plane_state((__state)->base.planes[__i].new_state), 1); \
	     (__i)++) \
		क्रम_each_अगर(plane)

#घोषणा क्रम_each_oldnew_पूर्णांकel_crtc_in_state(__state, crtc, old_crtc_state, new_crtc_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_crtc && \
		     ((crtc) = to_पूर्णांकel_crtc((__state)->base.crtcs[__i].ptr), \
		      (old_crtc_state) = to_पूर्णांकel_crtc_state((__state)->base.crtcs[__i].old_state), \
		      (new_crtc_state) = to_पूर्णांकel_crtc_state((__state)->base.crtcs[__i].new_state), 1); \
	     (__i)++) \
		क्रम_each_अगर(crtc)

#घोषणा क्रम_each_oldnew_पूर्णांकel_crtc_in_state_reverse(__state, crtc, old_crtc_state, new_crtc_state, __i) \
	क्रम ((__i) = (__state)->base.dev->mode_config.num_crtc - 1; \
	     (__i) >= 0  && \
	     ((crtc) = to_पूर्णांकel_crtc((__state)->base.crtcs[__i].ptr), \
	      (old_crtc_state) = to_पूर्णांकel_crtc_state((__state)->base.crtcs[__i].old_state), \
	      (new_crtc_state) = to_पूर्णांकel_crtc_state((__state)->base.crtcs[__i].new_state), 1); \
	     (__i)--) \
		क्रम_each_अगर(crtc)

#घोषणा पूर्णांकel_atomic_crtc_state_क्रम_each_plane_state( \
		  plane, plane_state, \
		  crtc_state) \
	क्रम_each_पूर्णांकel_plane_mask(((crtc_state)->uapi.state->dev), (plane), \
				((crtc_state)->uapi.plane_mask)) \
		क्रम_each_अगर ((plane_state = \
			      to_पूर्णांकel_plane_state(__drm_atomic_get_current_plane_state((crtc_state)->uapi.state, &plane->base))))

#घोषणा क्रम_each_new_पूर्णांकel_connector_in_state(__state, connector, new_connector_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->base.num_connector; \
	     (__i)++) \
		क्रम_each_अगर ((__state)->base.connectors[__i].ptr && \
			     ((connector) = to_पूर्णांकel_connector((__state)->base.connectors[__i].ptr), \
			     (new_connector_state) = to_पूर्णांकel_digital_connector_state((__state)->base.connectors[__i].new_state), 1))

पूर्णांक पूर्णांकel_atomic_add_affected_planes(काष्ठा पूर्णांकel_atomic_state *state,
				     काष्ठा पूर्णांकel_crtc *crtc);
u8 पूर्णांकel_calc_active_pipes(काष्ठा पूर्णांकel_atomic_state *state,
			   u8 active_pipes);
व्योम पूर्णांकel_link_compute_m_n(u16 bpp, पूर्णांक nlanes,
			    पूर्णांक pixel_घड़ी, पूर्णांक link_घड़ी,
			    काष्ठा पूर्णांकel_link_m_n *m_n,
			    bool स्थिरant_n, bool fec_enable);
व्योम lpt_disable_clkout_dp(काष्ठा drm_i915_निजी *dev_priv);
u32 पूर्णांकel_plane_fb_max_stride(काष्ठा drm_i915_निजी *dev_priv,
			      u32 pixel_क्रमmat, u64 modअगरier);
क्रमागत drm_mode_status
पूर्णांकel_mode_valid_max_plane_size(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर काष्ठा drm_display_mode *mode,
				bool bigjoiner);
क्रमागत phy पूर्णांकel_port_to_phy(काष्ठा drm_i915_निजी *i915, क्रमागत port port);
bool is_trans_port_sync_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *state);

व्योम पूर्णांकel_plane_destroy(काष्ठा drm_plane *plane);
व्योम पूर्णांकel_enable_pipe(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state);
व्योम पूर्णांकel_disable_pipe(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state);
व्योम i830_enable_pipe(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe);
व्योम i830_disable_pipe(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe);
क्रमागत pipe पूर्णांकel_crtc_pch_transcoder(काष्ठा पूर्णांकel_crtc *crtc);
पूर्णांक vlv_get_hpll_vco(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक vlv_get_cck_घड़ी(काष्ठा drm_i915_निजी *dev_priv,
		      स्थिर अक्षर *name, u32 reg, पूर्णांक ref_freq);
पूर्णांक vlv_get_cck_घड़ी_hpll(काष्ठा drm_i915_निजी *dev_priv,
			   स्थिर अक्षर *name, u32 reg);
व्योम lpt_pch_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम lpt_disable_pch_transcoder(काष्ठा drm_i915_निजी *dev_priv);
व्योम lpt_disable_iclkip(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_init_display_hooks(काष्ठा drm_i915_निजी *dev_priv);
अचिन्हित पूर्णांक पूर्णांकel_fb_xy_to_linear(पूर्णांक x, पूर्णांक y,
				   स्थिर काष्ठा पूर्णांकel_plane_state *state,
				   पूर्णांक plane);
अचिन्हित पूर्णांक पूर्णांकel_fb_align_height(स्थिर काष्ठा drm_framebuffer *fb,
				   पूर्णांक color_plane, अचिन्हित पूर्णांक height);
व्योम पूर्णांकel_add_fb_offsets(पूर्णांक *x, पूर्णांक *y,
			  स्थिर काष्ठा पूर्णांकel_plane_state *state, पूर्णांक plane);
अचिन्हित पूर्णांक पूर्णांकel_rotation_info_size(स्थिर काष्ठा पूर्णांकel_rotation_info *rot_info);
अचिन्हित पूर्णांक पूर्णांकel_remapped_info_size(स्थिर काष्ठा पूर्णांकel_remapped_info *rem_info);
bool पूर्णांकel_has_pending_fb_unpin(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_display_suspend(काष्ठा drm_device *dev);
व्योम पूर्णांकel_encoder_destroy(काष्ठा drm_encoder *encoder);
काष्ठा drm_display_mode *
पूर्णांकel_encoder_current_mode(काष्ठा पूर्णांकel_encoder *encoder);
bool पूर्णांकel_phy_is_combo(काष्ठा drm_i915_निजी *dev_priv, क्रमागत phy phy);
bool पूर्णांकel_phy_is_tc(काष्ठा drm_i915_निजी *dev_priv, क्रमागत phy phy);
क्रमागत tc_port पूर्णांकel_port_to_tc(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत port port);
पूर्णांक पूर्णांकel_get_pipe_from_crtc_id_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file_priv);
u32 पूर्णांकel_crtc_get_vblank_counter(काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_crtc_vblank_on(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_crtc_vblank_off(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

पूर्णांक ilk_get_lanes_required(पूर्णांक target_घड़ी, पूर्णांक link_bw, पूर्णांक bpp);
व्योम vlv_रुको_port_पढ़ोy(काष्ठा drm_i915_निजी *dev_priv,
			 काष्ठा पूर्णांकel_digital_port *dig_port,
			 अचिन्हित पूर्णांक expected_mask);
पूर्णांक पूर्णांकel_get_load_detect_pipe(काष्ठा drm_connector *connector,
			       काष्ठा पूर्णांकel_load_detect_pipe *old,
			       काष्ठा drm_modeset_acquire_ctx *ctx);
व्योम पूर्णांकel_release_load_detect_pipe(काष्ठा drm_connector *connector,
				    काष्ठा पूर्णांकel_load_detect_pipe *old,
				    काष्ठा drm_modeset_acquire_ctx *ctx);
काष्ठा i915_vma *
पूर्णांकel_pin_and_fence_fb_obj(काष्ठा drm_framebuffer *fb, bool phys_cursor,
			   स्थिर काष्ठा i915_ggtt_view *view,
			   bool uses_fence,
			   अचिन्हित दीर्घ *out_flags);
व्योम पूर्णांकel_unpin_fb_vma(काष्ठा i915_vma *vma, अचिन्हित दीर्घ flags);
काष्ठा drm_framebuffer *
पूर्णांकel_framebuffer_create(काष्ठा drm_i915_gem_object *obj,
			 काष्ठा drm_mode_fb_cmd2 *mode_cmd);
पूर्णांक पूर्णांकel_prepare_plane_fb(काष्ठा drm_plane *plane,
			   काष्ठा drm_plane_state *new_state);
व्योम पूर्णांकel_cleanup_plane_fb(काष्ठा drm_plane *plane,
			    काष्ठा drm_plane_state *old_state);

व्योम निश्चित_pch_transcoder_disabled(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत pipe pipe);

पूर्णांक lpt_get_iclkip(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_fuzzy_घड़ी_check(पूर्णांक घड़ी1, पूर्णांक घड़ी2);

व्योम पूर्णांकel_display_prepare_reset(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_display_finish_reset(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_dp_get_m_n(काष्ठा पूर्णांकel_crtc *crtc,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config);
व्योम पूर्णांकel_dp_set_m_n(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      क्रमागत link_m_n_set m_n);
पूर्णांक पूर्णांकel_करोtघड़ी_calculate(पूर्णांक link_freq, स्थिर काष्ठा पूर्णांकel_link_m_n *m_n);
bool bxt_find_best_dpll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			काष्ठा dpll *best_घड़ी);
पूर्णांक chv_calc_dpll_params(पूर्णांक refclk, काष्ठा dpll *pll_घड़ी);

bool hsw_crtc_state_ips_capable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम hsw_enable_ips(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम hsw_disable_ips(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
क्रमागत पूर्णांकel_display_घातer_करोमुख्य पूर्णांकel_port_to_घातer_करोमुख्य(क्रमागत port port);
क्रमागत पूर्णांकel_display_घातer_करोमुख्य
पूर्णांकel_aux_घातer_करोमुख्य(काष्ठा पूर्णांकel_digital_port *dig_port);
क्रमागत पूर्णांकel_display_घातer_करोमुख्य
पूर्णांकel_legacy_aux_to_घातer_करोमुख्य(क्रमागत aux_ch aux_ch);
व्योम पूर्णांकel_crtc_arm_fअगरo_underrun(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम ilk_pfit_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state);

पूर्णांक bdw_get_pipemisc_bpp(काष्ठा पूर्णांकel_crtc *crtc);
अचिन्हित पूर्णांक पूर्णांकel_plane_fence_y_offset(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);

काष्ठा पूर्णांकel_display_error_state *
पूर्णांकel_display_capture_error_state(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_display_prपूर्णांक_error_state(काष्ठा drm_i915_error_state_buf *e,
				     काष्ठा पूर्णांकel_display_error_state *error);

bool
पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(स्थिर काष्ठा drm_क्रमmat_info *info,
				    u64 modअगरier);

पूर्णांक पूर्णांकel_plane_pin_fb(काष्ठा पूर्णांकel_plane_state *plane_state);
व्योम पूर्णांकel_plane_unpin_fb(काष्ठा पूर्णांकel_plane_state *old_plane_state);
काष्ठा पूर्णांकel_encoder *
पूर्णांकel_get_crtc_new_encoder(स्थिर काष्ठा पूर्णांकel_atomic_state *state,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

अचिन्हित पूर्णांक पूर्णांकel_surf_alignment(स्थिर काष्ठा drm_framebuffer *fb,
				  पूर्णांक color_plane);
अचिन्हित पूर्णांक पूर्णांकel_tile_width_bytes(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane);

व्योम पूर्णांकel_display_driver_रेजिस्टर(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_display_driver_unरेजिस्टर(काष्ठा drm_i915_निजी *i915);

/* modesetting */
व्योम पूर्णांकel_modeset_init_hw(काष्ठा drm_i915_निजी *i915);
पूर्णांक पूर्णांकel_modeset_init_noirq(काष्ठा drm_i915_निजी *i915);
पूर्णांक पूर्णांकel_modeset_init_nogem(काष्ठा drm_i915_निजी *i915);
पूर्णांक पूर्णांकel_modeset_init(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_modeset_driver_हटाओ(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_modeset_driver_हटाओ_noirq(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_modeset_driver_हटाओ_nogem(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_display_resume(काष्ठा drm_device *dev);
व्योम पूर्णांकel_init_pch_refclk(काष्ठा drm_i915_निजी *dev_priv);

/* modesetting निश्चितs */
व्योम निश्चित_panel_unlocked(काष्ठा drm_i915_निजी *dev_priv,
			   क्रमागत pipe pipe);
व्योम निश्चित_pll(काष्ठा drm_i915_निजी *dev_priv,
		क्रमागत pipe pipe, bool state);
#घोषणा निश्चित_pll_enabled(d, p) निश्चित_pll(d, p, true)
#घोषणा निश्चित_pll_disabled(d, p) निश्चित_pll(d, p, false)
व्योम निश्चित_dsi_pll(काष्ठा drm_i915_निजी *dev_priv, bool state);
#घोषणा निश्चित_dsi_pll_enabled(d) निश्चित_dsi_pll(d, true)
#घोषणा निश्चित_dsi_pll_disabled(d) निश्चित_dsi_pll(d, false)
व्योम निश्चित_fdi_rx_pll(काष्ठा drm_i915_निजी *dev_priv,
		       क्रमागत pipe pipe, bool state);
#घोषणा निश्चित_fdi_rx_pll_enabled(d, p) निश्चित_fdi_rx_pll(d, p, true)
#घोषणा निश्चित_fdi_rx_pll_disabled(d, p) निश्चित_fdi_rx_pll(d, p, false)
व्योम निश्चित_pipe(काष्ठा drm_i915_निजी *dev_priv,
		 क्रमागत transcoder cpu_transcoder, bool state);
#घोषणा निश्चित_pipe_enabled(d, t) निश्चित_pipe(d, t, true)
#घोषणा निश्चित_pipe_disabled(d, t) निश्चित_pipe(d, t, false)

/* Use I915_STATE_WARN(x) and I915_STATE_WARN_ON() (rather than WARN() and
 * WARN_ON()) क्रम hw state sanity checks to check क्रम unexpected conditions
 * which may not necessarily be a user visible problem.  This will either
 * WARN() or DRM_ERROR() depending on the verbose_checks moduleparam, to
 * enable distros and users to tailor their preferred amount of i915 abrt
 * spam.
 */
#घोषणा I915_STATE_WARN(condition, क्रमmat...) (अणु			\
	पूर्णांक __ret_warn_on = !!(condition);				\
	अगर (unlikely(__ret_warn_on))					\
		अगर (!WARN(i915_modparams.verbose_state_checks, क्रमmat))	\
			DRM_ERROR(क्रमmat);				\
	unlikely(__ret_warn_on);					\
पूर्ण)

#घोषणा I915_STATE_WARN_ON(x)						\
	I915_STATE_WARN((x), "%s", "WARN_ON(" __stringअगरy(x) ")")

#पूर्ण_अगर
