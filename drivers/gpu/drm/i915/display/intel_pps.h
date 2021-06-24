<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __INTEL_PPS_H__
#घोषणा __INTEL_PPS_H__

#समावेश <linux/types.h>

#समावेश "intel_wakeref.h"

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_dp;
काष्ठा पूर्णांकel_encoder;

पूर्णांकel_wakeref_t पूर्णांकel_pps_lock(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
पूर्णांकel_wakeref_t पूर्णांकel_pps_unlock(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांकel_wakeref_t wakeref);

#घोषणा with_पूर्णांकel_pps_lock(dp, wf)						\
	क्रम ((wf) = पूर्णांकel_pps_lock(dp); (wf); (wf) = पूर्णांकel_pps_unlock((dp), (wf)))

व्योम पूर्णांकel_pps_backlight_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_backlight_off(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_backlight_घातer(काष्ठा पूर्णांकel_connector *connector, bool enable);

bool पूर्णांकel_pps_vdd_on_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_vdd_off_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, bool sync);
व्योम पूर्णांकel_pps_on_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_off_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_check_घातer_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);

व्योम पूर्णांकel_pps_vdd_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_off(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_vdd_off_sync(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
bool पूर्णांकel_pps_have_घातer(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_रुको_घातer_cycle(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);

व्योम पूर्णांकel_pps_init(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_encoder_reset(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_pps_reset_all(काष्ठा drm_i915_निजी *i915);

व्योम vlv_pps_init(काष्ठा पूर्णांकel_encoder *encoder,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

व्योम पूर्णांकel_pps_unlock_regs_wa(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_pps_setup(काष्ठा drm_i915_निजी *i915);

#पूर्ण_अगर /* __INTEL_PPS_H__ */
