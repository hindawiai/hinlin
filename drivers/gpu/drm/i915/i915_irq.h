<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_IRQ_H__
#घोषणा __I915_IRQ_H__

#समावेश <linux/kसमय.स>
#समावेश <linux/types.h>

#समावेश "display/intel_display.h"
#समावेश "i915_reg.h"

काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा drm_display_mode;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_uncore;

व्योम पूर्णांकel_irq_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_irq_fini(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_irq_install(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_irq_uninstall(काष्ठा drm_i915_निजी *dev_priv);

u32 i915_pipestat_enable_mask(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत pipe pipe);
व्योम
i915_enable_pipestat(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe,
		     u32 status_mask);

व्योम
i915_disable_pipestat(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe,
		      u32 status_mask);

व्योम valleyview_enable_display_irqs(काष्ठा drm_i915_निजी *dev_priv);
व्योम valleyview_disable_display_irqs(काष्ठा drm_i915_निजी *dev_priv);

व्योम i915_hotplug_पूर्णांकerrupt_update(काष्ठा drm_i915_निजी *dev_priv,
				   u32 mask,
				   u32 bits);
व्योम ilk_update_display_irq(काष्ठा drm_i915_निजी *dev_priv,
			    u32 पूर्णांकerrupt_mask,
			    u32 enabled_irq_mask);
अटल अंतरभूत व्योम
ilk_enable_display_irq(काष्ठा drm_i915_निजी *dev_priv, u32 bits)
अणु
	ilk_update_display_irq(dev_priv, bits, bits);
पूर्ण
अटल अंतरभूत व्योम
ilk_disable_display_irq(काष्ठा drm_i915_निजी *dev_priv, u32 bits)
अणु
	ilk_update_display_irq(dev_priv, bits, 0);
पूर्ण
व्योम bdw_update_pipe_irq(काष्ठा drm_i915_निजी *dev_priv,
			 क्रमागत pipe pipe,
			 u32 पूर्णांकerrupt_mask,
			 u32 enabled_irq_mask);
अटल अंतरभूत व्योम bdw_enable_pipe_irq(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत pipe pipe, u32 bits)
अणु
	bdw_update_pipe_irq(dev_priv, pipe, bits, bits);
पूर्ण
अटल अंतरभूत व्योम bdw_disable_pipe_irq(काष्ठा drm_i915_निजी *dev_priv,
					क्रमागत pipe pipe, u32 bits)
अणु
	bdw_update_pipe_irq(dev_priv, pipe, bits, 0);
पूर्ण
व्योम ibx_display_पूर्णांकerrupt_update(काष्ठा drm_i915_निजी *dev_priv,
				  u32 पूर्णांकerrupt_mask,
				  u32 enabled_irq_mask);
अटल अंतरभूत व्योम
ibx_enable_display_पूर्णांकerrupt(काष्ठा drm_i915_निजी *dev_priv, u32 bits)
अणु
	ibx_display_पूर्णांकerrupt_update(dev_priv, bits, bits);
पूर्ण
अटल अंतरभूत व्योम
ibx_disable_display_पूर्णांकerrupt(काष्ठा drm_i915_निजी *dev_priv, u32 bits)
अणु
	ibx_display_पूर्णांकerrupt_update(dev_priv, bits, 0);
पूर्ण

व्योम gen5_enable_gt_irq(काष्ठा drm_i915_निजी *dev_priv, u32 mask);
व्योम gen5_disable_gt_irq(काष्ठा drm_i915_निजी *dev_priv, u32 mask);
व्योम gen11_reset_rps_पूर्णांकerrupts(काष्ठा drm_i915_निजी *dev_priv);
व्योम gen6_reset_rps_पूर्णांकerrupts(काष्ठा drm_i915_निजी *dev_priv);
व्योम gen6_enable_rps_पूर्णांकerrupts(काष्ठा drm_i915_निजी *dev_priv);
व्योम gen6_disable_rps_पूर्णांकerrupts(काष्ठा drm_i915_निजी *dev_priv);
व्योम gen6_rps_reset_ei(काष्ठा drm_i915_निजी *dev_priv);
u32 gen6_sanitize_rps_pm_mask(स्थिर काष्ठा drm_i915_निजी *i915, u32 mask);

व्योम पूर्णांकel_runसमय_pm_disable_पूर्णांकerrupts(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_runसमय_pm_enable_पूर्णांकerrupts(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_irqs_enabled(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_synchronize_irq(काष्ठा drm_i915_निजी *i915);

पूर्णांक पूर्णांकel_get_crtc_scanline(काष्ठा पूर्णांकel_crtc *crtc);
व्योम gen8_irq_घातer_well_post_enable(काष्ठा drm_i915_निजी *dev_priv,
				     u8 pipe_mask);
व्योम gen8_irq_घातer_well_pre_disable(काष्ठा drm_i915_निजी *dev_priv,
				     u8 pipe_mask);

bool पूर्णांकel_crtc_get_vblank_बारtamp(काष्ठा drm_crtc *crtc, पूर्णांक *max_error,
				     kसमय_प्रकार *vblank_समय, bool in_vblank_irq);

u32 i915_get_vblank_counter(काष्ठा drm_crtc *crtc);
u32 g4x_get_vblank_counter(काष्ठा drm_crtc *crtc);

पूर्णांक i8xx_enable_vblank(काष्ठा drm_crtc *crtc);
पूर्णांक i915gm_enable_vblank(काष्ठा drm_crtc *crtc);
पूर्णांक i965_enable_vblank(काष्ठा drm_crtc *crtc);
पूर्णांक ilk_enable_vblank(काष्ठा drm_crtc *crtc);
पूर्णांक bdw_enable_vblank(काष्ठा drm_crtc *crtc);
व्योम i8xx_disable_vblank(काष्ठा drm_crtc *crtc);
व्योम i915gm_disable_vblank(काष्ठा drm_crtc *crtc);
व्योम i965_disable_vblank(काष्ठा drm_crtc *crtc);
व्योम ilk_disable_vblank(काष्ठा drm_crtc *crtc);
व्योम bdw_disable_vblank(काष्ठा drm_crtc *crtc);

व्योम gen2_irq_reset(काष्ठा पूर्णांकel_uncore *uncore);
व्योम gen3_irq_reset(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t imr,
		    i915_reg_t iir, i915_reg_t ier);

व्योम gen2_irq_init(काष्ठा पूर्णांकel_uncore *uncore,
		   u32 imr_val, u32 ier_val);
व्योम gen3_irq_init(काष्ठा पूर्णांकel_uncore *uncore,
		   i915_reg_t imr, u32 imr_val,
		   i915_reg_t ier, u32 ier_val,
		   i915_reg_t iir);

#घोषणा GEN8_IRQ_RESET_NDX(uncore, type, which) \
(अणु \
	अचिन्हित पूर्णांक which_ = which; \
	gen3_irq_reset((uncore), GEN8_##type##_IMR(which_), \
		       GEN8_##type##_IIR(which_), GEN8_##type##_IER(which_)); \
पूर्ण)

#घोषणा GEN3_IRQ_RESET(uncore, type) \
	gen3_irq_reset((uncore), type##IMR, type##IIR, type##IER)

#घोषणा GEN2_IRQ_RESET(uncore) \
	gen2_irq_reset(uncore)

#घोषणा GEN8_IRQ_INIT_NDX(uncore, type, which, imr_val, ier_val) \
(अणु \
	अचिन्हित पूर्णांक which_ = which; \
	gen3_irq_init((uncore), \
		      GEN8_##type##_IMR(which_), imr_val, \
		      GEN8_##type##_IER(which_), ier_val, \
		      GEN8_##type##_IIR(which_)); \
पूर्ण)

#घोषणा GEN3_IRQ_INIT(uncore, type, imr_val, ier_val) \
	gen3_irq_init((uncore), \
		      type##IMR, imr_val, \
		      type##IER, ier_val, \
		      type##IIR)

#घोषणा GEN2_IRQ_INIT(uncore, imr_val, ier_val) \
	gen2_irq_init((uncore), imr_val, ier_val)

#पूर्ण_अगर /* __I915_IRQ_H__ */
