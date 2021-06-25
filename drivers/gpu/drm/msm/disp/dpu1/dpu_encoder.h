<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __DPU_ENCODER_H__
#घोषणा __DPU_ENCODER_H__

#समावेश <drm/drm_crtc.h>
#समावेश "dpu_hw_mdss.h"

#घोषणा DPU_ENCODER_FRAME_EVENT_DONE			BIT(0)
#घोषणा DPU_ENCODER_FRAME_EVENT_ERROR			BIT(1)
#घोषणा DPU_ENCODER_FRAME_EVENT_PANEL_DEAD		BIT(2)
#घोषणा DPU_ENCODER_FRAME_EVENT_IDLE			BIT(3)

#घोषणा IDLE_TIMEOUT	(66 - 16/2)

/**
 * Encoder functions and data types
 * @पूर्णांकfs:	Interfaces this encoder is using, INTF_MODE_NONE अगर unused
 */
काष्ठा dpu_encoder_hw_resources अणु
	क्रमागत dpu_पूर्णांकf_mode पूर्णांकfs[INTF_MAX];
पूर्ण;

/**
 * dpu_encoder_get_hw_resources - Populate table of required hardware resources
 * @encoder:	encoder poपूर्णांकer
 * @hw_res:	resource table to populate with encoder required resources
 */
व्योम dpu_encoder_get_hw_resources(काष्ठा drm_encoder *encoder,
				  काष्ठा dpu_encoder_hw_resources *hw_res);

/**
 * dpu_encoder_assign_crtc - Link the encoder to the crtc it's asचिन्हित to
 * @encoder:	encoder poपूर्णांकer
 * @crtc:	crtc poपूर्णांकer
 */
व्योम dpu_encoder_assign_crtc(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_crtc *crtc);

/**
 * dpu_encoder_toggle_vblank_क्रम_crtc - Toggles vblank पूर्णांकerrupts on or off अगर
 *	the encoder is asचिन्हित to the given crtc
 * @encoder:	encoder poपूर्णांकer
 * @crtc:	crtc poपूर्णांकer
 * @enable:	true अगर vblank should be enabled
 */
व्योम dpu_encoder_toggle_vblank_क्रम_crtc(काष्ठा drm_encoder *encoder,
					काष्ठा drm_crtc *crtc, bool enable);

/**
 * dpu_encoder_रेजिस्टर_frame_event_callback - provide callback to encoder that
 *	will be called after the request is complete, or other events.
 * @encoder:	encoder poपूर्णांकer
 * @cb:		callback poपूर्णांकer, provide शून्य to deरेजिस्टर
 * @data:	user data provided to callback
 */
व्योम dpu_encoder_रेजिस्टर_frame_event_callback(काष्ठा drm_encoder *encoder,
		व्योम (*cb)(व्योम *, u32), व्योम *data);

/**
 * dpu_encoder_prepare_क्रम_kickoff - schedule द्विगुन buffer flip of the ctl
 *	path (i.e. ctl flush and start) at next appropriate समय.
 *	Immediately: अगर no previous commit is outstanding.
 *	Delayed: Block until next trigger can be issued.
 * @encoder:	encoder poपूर्णांकer
 */
व्योम dpu_encoder_prepare_क्रम_kickoff(काष्ठा drm_encoder *encoder);

/**
 * dpu_encoder_trigger_kickoff_pending - Clear the flush bits from previous
 *        kickoff and trigger the ctl prepare progress क्रम command mode display.
 * @encoder:	encoder poपूर्णांकer
 */
व्योम dpu_encoder_trigger_kickoff_pending(काष्ठा drm_encoder *encoder);

/**
 * dpu_encoder_kickoff - trigger a द्विगुन buffer flip of the ctl path
 *	(i.e. ctl flush and start) immediately.
 * @encoder:	encoder poपूर्णांकer
 */
व्योम dpu_encoder_kickoff(काष्ठा drm_encoder *encoder);

/**
 * dpu_encoder_wakeup_समय - get the समय of the next vsync
 */
पूर्णांक dpu_encoder_vsync_समय(काष्ठा drm_encoder *drm_enc, kसमय_प्रकार *wakeup_समय);

/**
 * dpu_encoder_रुको_क्रम_event - Waits क्रम encoder events
 * @encoder:	encoder poपूर्णांकer
 * @event:      event to रुको क्रम
 * MSM_ENC_COMMIT_DONE -  Wait क्रम hardware to have flushed the current pending
 *                        frames to hardware at a vblank or ctl_start
 *                        Encoders will map this dअगरferently depending on the
 *                        panel type.
 *	                  vid mode -> vsync_irq
 *                        cmd mode -> ctl_start
 * MSM_ENC_TX_COMPLETE -  Wait क्रम the hardware to transfer all the pixels to
 *                        the panel. Encoders will map this dअगरferently
 *                        depending on the panel type.
 *                        vid mode -> vsync_irq
 *                        cmd mode -> pp_करोne
 * Returns: 0 on success, -EWOULDBLOCK अगर alपढ़ोy संकेतed, error otherwise
 */
पूर्णांक dpu_encoder_रुको_क्रम_event(काष्ठा drm_encoder *drm_encoder,
						क्रमागत msm_event_रुको event);

/*
 * dpu_encoder_get_पूर्णांकf_mode - get पूर्णांकerface mode of the given encoder
 * @encoder: Poपूर्णांकer to drm encoder object
 */
क्रमागत dpu_पूर्णांकf_mode dpu_encoder_get_पूर्णांकf_mode(काष्ठा drm_encoder *encoder);

/**
 * dpu_encoder_virt_runसमय_resume - pm runसमय resume the encoder configs
 * @encoder:	encoder poपूर्णांकer
 */
व्योम dpu_encoder_virt_runसमय_resume(काष्ठा drm_encoder *encoder);

/**
 * dpu_encoder_init - initialize भव encoder object
 * @dev:        Poपूर्णांकer to drm device काष्ठाure
 * @disp_info:  Poपूर्णांकer to display inक्रमmation काष्ठाure
 * Returns:     Poपूर्णांकer to newly created drm encoder
 */
काष्ठा drm_encoder *dpu_encoder_init(
		काष्ठा drm_device *dev,
		पूर्णांक drm_enc_mode);

/**
 * dpu_encoder_setup - setup dpu_encoder क्रम the display probed
 * @dev:		Poपूर्णांकer to drm device काष्ठाure
 * @enc:		Poपूर्णांकer to the drm_encoder
 * @disp_info:	Poपूर्णांकer to the display info
 */
पूर्णांक dpu_encoder_setup(काष्ठा drm_device *dev, काष्ठा drm_encoder *enc,
		काष्ठा msm_display_info *disp_info);

/**
 * dpu_encoder_prepare_commit - prepare encoder at the very beginning of an
 *	atomic commit, beक्रमe any रेजिस्टरs are written
 * @drm_enc:    Poपूर्णांकer to previously created drm encoder काष्ठाure
 */
व्योम dpu_encoder_prepare_commit(काष्ठा drm_encoder *drm_enc);

/**
 * dpu_encoder_set_idle_समयout - set the idle समयout क्रम video
 *                    and command mode encoders.
 * @drm_enc:    Poपूर्णांकer to previously created drm encoder काष्ठाure
 * @idle_समयout:    idle समयout duration in milliseconds
 */
व्योम dpu_encoder_set_idle_समयout(काष्ठा drm_encoder *drm_enc,
							u32 idle_समयout);
/**
 * dpu_encoder_get_linecount - get पूर्णांकerface line count क्रम the encoder.
 * @drm_enc:    Poपूर्णांकer to previously created drm encoder काष्ठाure
 */
पूर्णांक dpu_encoder_get_linecount(काष्ठा drm_encoder *drm_enc);

/**
 * dpu_encoder_get_frame_count - get पूर्णांकerface frame count क्रम the encoder.
 * @drm_enc:    Poपूर्णांकer to previously created drm encoder काष्ठाure
 */
पूर्णांक dpu_encoder_get_frame_count(काष्ठा drm_encoder *drm_enc);

#पूर्ण_अगर /* __DPU_ENCODER_H__ */
