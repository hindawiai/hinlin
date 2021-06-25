<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <drm/drm_atomic_helper.h>

#समावेश "display/intel_dp.h"

#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp_aux.h"
#समावेश "intel_hdmi.h"
#समावेश "intel_psr.h"
#समावेश "intel_sprite.h"
#समावेश "skl_universal_plane.h"

/**
 * DOC: Panel Self Refresh (PSR/SRD)
 *
 * Since Haswell Display controller supports Panel Self-Refresh on display
 * panels witch have a remote frame buffer (RFB) implemented according to PSR
 * spec in eDP1.3. PSR feature allows the display to go to lower standby states
 * when प्रणाली is idle but display is on as it eliminates display refresh
 * request to DDR memory completely as दीर्घ as the frame buffer क्रम that
 * display is unchanged.
 *
 * Panel Self Refresh must be supported by both Hardware (source) and
 * Panel (sink).
 *
 * PSR saves घातer by caching the framebuffer in the panel RFB, which allows us
 * to घातer करोwn the link and memory controller. For DSI panels the same idea
 * is called "manual mode".
 *
 * The implementation uses the hardware-based PSR support which स्वतःmatically
 * enters/निकासs self-refresh mode. The hardware takes care of sending the
 * required DP aux message and could even retrain the link (that part isn't
 * enabled yet though). The hardware also keeps track of any frontbuffer
 * changes to know when to निकास self-refresh mode again. Unक्रमtunately that
 * part करोesn't work too well, hence why the i915 PSR support uses the
 * software frontbuffer tracking to make sure it करोesn't miss a screen
 * update. For this पूर्णांकegration पूर्णांकel_psr_invalidate() and पूर्णांकel_psr_flush()
 * get called by the frontbuffer tracking code. Note that because of locking
 * issues the self-refresh re-enable code is करोne from a work queue, which
 * must be correctly synchronized/cancelled when shutting करोwn the pipe."
 *
 * DC3CO (DC3 घड़ी off)
 *
 * On top of PSR2, GEN12 adds a पूर्णांकermediate घातer savings state that turns
 * घड़ी off स्वतःmatically during PSR2 idle state.
 * The smaller overhead of DC3co entry/निकास vs. the overhead of PSR2 deep sleep
 * entry/निकास allows the HW to enter a low-घातer state even when page flipping
 * periodically (क्रम instance a 30fps video playback scenario).
 *
 * Every समय a flips occurs PSR2 will get out of deep sleep state(अगर it was),
 * so DC3CO is enabled and tgl_dc3co_disable_work is schedule to run after 6
 * frames, अगर no other flip occurs and the function above is executed, DC3CO is
 * disabled and PSR2 is configured to enter deep sleep, resetting again in हाल
 * of another flip.
 * Front buffer modअगरications करो not trigger DC3CO activation on purpose as it
 * would bring a lot of complनिकासy and most of the moderns प्रणालीs will only
 * use page flips.
 */

अटल bool psr_global_enabled(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	चयन (पूर्णांकel_dp->psr.debug & I915_PSR_DEBUG_MODE_MASK) अणु
	हाल I915_PSR_DEBUG_DEFAULT:
		वापस i915->params.enable_psr;
	हाल I915_PSR_DEBUG_DISABLE:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool psr2_global_enabled(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	चयन (पूर्णांकel_dp->psr.debug & I915_PSR_DEBUG_MODE_MASK) अणु
	हाल I915_PSR_DEBUG_DISABLE:
	हाल I915_PSR_DEBUG_FORCE_PSR1:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम psr_irq_control(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	क्रमागत transcoder trans_shअगरt;
	i915_reg_t imr_reg;
	u32 mask, val;

	/*
	 * gen12+ has रेजिस्टरs relative to transcoder and one per transcoder
	 * using the same bit definition: handle it as TRANSCODER_EDP to क्रमce
	 * 0 shअगरt in bit definition
	 */
	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		trans_shअगरt = 0;
		imr_reg = TRANS_PSR_IMR(पूर्णांकel_dp->psr.transcoder);
	पूर्ण अन्यथा अणु
		trans_shअगरt = पूर्णांकel_dp->psr.transcoder;
		imr_reg = EDP_PSR_IMR;
	पूर्ण

	mask = EDP_PSR_ERROR(trans_shअगरt);
	अगर (पूर्णांकel_dp->psr.debug & I915_PSR_DEBUG_IRQ)
		mask |= EDP_PSR_POST_EXIT(trans_shअगरt) |
			EDP_PSR_PRE_ENTRY(trans_shअगरt);

	/* Warning: it is masking/setting reserved bits too */
	val = पूर्णांकel_de_पढ़ो(dev_priv, imr_reg);
	val &= ~EDP_PSR_TRANS_MASK(trans_shअगरt);
	val |= ~mask;
	पूर्णांकel_de_ग_लिखो(dev_priv, imr_reg, val);
पूर्ण

अटल व्योम psr_event_prपूर्णांक(काष्ठा drm_i915_निजी *i915,
			    u32 val, bool psr2_enabled)
अणु
	drm_dbg_kms(&i915->drm, "PSR exit events: 0x%x\n", val);
	अगर (val & PSR_EVENT_PSR2_WD_TIMER_EXPIRE)
		drm_dbg_kms(&i915->drm, "\tPSR2 watchdog timer expired\n");
	अगर ((val & PSR_EVENT_PSR2_DISABLED) && psr2_enabled)
		drm_dbg_kms(&i915->drm, "\tPSR2 disabled\n");
	अगर (val & PSR_EVENT_SU_सूचीTY_FIFO_UNDERRUN)
		drm_dbg_kms(&i915->drm, "\tSU dirty FIFO underrun\n");
	अगर (val & PSR_EVENT_SU_CRC_FIFO_UNDERRUN)
		drm_dbg_kms(&i915->drm, "\tSU CRC FIFO underrun\n");
	अगर (val & PSR_EVENT_GRAPHICS_RESET)
		drm_dbg_kms(&i915->drm, "\tGraphics reset\n");
	अगर (val & PSR_EVENT_PCH_INTERRUPT)
		drm_dbg_kms(&i915->drm, "\tPCH interrupt\n");
	अगर (val & PSR_EVENT_MEMORY_UP)
		drm_dbg_kms(&i915->drm, "\tMemory up\n");
	अगर (val & PSR_EVENT_FRONT_BUFFER_MODIFY)
		drm_dbg_kms(&i915->drm, "\tFront buffer modification\n");
	अगर (val & PSR_EVENT_WD_TIMER_EXPIRE)
		drm_dbg_kms(&i915->drm, "\tPSR watchdog timer expired\n");
	अगर (val & PSR_EVENT_PIPE_REGISTERS_UPDATE)
		drm_dbg_kms(&i915->drm, "\tPIPE registers updated\n");
	अगर (val & PSR_EVENT_REGISTER_UPDATE)
		drm_dbg_kms(&i915->drm, "\tRegister updated\n");
	अगर (val & PSR_EVENT_HDCP_ENABLE)
		drm_dbg_kms(&i915->drm, "\tHDCP enabled\n");
	अगर (val & PSR_EVENT_KVMR_SESSION_ENABLE)
		drm_dbg_kms(&i915->drm, "\tKVMR session enabled\n");
	अगर (val & PSR_EVENT_VBI_ENABLE)
		drm_dbg_kms(&i915->drm, "\tVBI enabled\n");
	अगर (val & PSR_EVENT_LPSP_MODE_EXIT)
		drm_dbg_kms(&i915->drm, "\tLPSP mode exited\n");
	अगर ((val & PSR_EVENT_PSR_DISABLE) && !psr2_enabled)
		drm_dbg_kms(&i915->drm, "\tPSR disabled\n");
पूर्ण

व्योम पूर्णांकel_psr_irq_handler(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u32 psr_iir)
अणु
	क्रमागत transcoder cpu_transcoder = पूर्णांकel_dp->psr.transcoder;
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	kसमय_प्रकार समय_ns =  kसमय_get();
	क्रमागत transcoder trans_shअगरt;
	i915_reg_t imr_reg;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		trans_shअगरt = 0;
		imr_reg = TRANS_PSR_IMR(पूर्णांकel_dp->psr.transcoder);
	पूर्ण अन्यथा अणु
		trans_shअगरt = पूर्णांकel_dp->psr.transcoder;
		imr_reg = EDP_PSR_IMR;
	पूर्ण

	अगर (psr_iir & EDP_PSR_PRE_ENTRY(trans_shअगरt)) अणु
		पूर्णांकel_dp->psr.last_entry_attempt = समय_ns;
		drm_dbg_kms(&dev_priv->drm,
			    "[transcoder %s] PSR entry attempt in 2 vblanks\n",
			    transcoder_name(cpu_transcoder));
	पूर्ण

	अगर (psr_iir & EDP_PSR_POST_EXIT(trans_shअगरt)) अणु
		पूर्णांकel_dp->psr.last_निकास = समय_ns;
		drm_dbg_kms(&dev_priv->drm,
			    "[transcoder %s] PSR exit completed\n",
			    transcoder_name(cpu_transcoder));

		अगर (DISPLAY_VER(dev_priv) >= 9) अणु
			u32 val = पूर्णांकel_de_पढ़ो(dev_priv,
						PSR_EVENT(cpu_transcoder));
			bool psr2_enabled = पूर्णांकel_dp->psr.psr2_enabled;

			पूर्णांकel_de_ग_लिखो(dev_priv, PSR_EVENT(cpu_transcoder),
				       val);
			psr_event_prपूर्णांक(dev_priv, val, psr2_enabled);
		पूर्ण
	पूर्ण

	अगर (psr_iir & EDP_PSR_ERROR(trans_shअगरt)) अणु
		u32 val;

		drm_warn(&dev_priv->drm, "[transcoder %s] PSR aux error\n",
			 transcoder_name(cpu_transcoder));

		पूर्णांकel_dp->psr.irq_aux_error = true;

		/*
		 * If this पूर्णांकerruption is not masked it will keep
		 * पूर्णांकerrupting so fast that it prevents the scheduled
		 * work to run.
		 * Also after a PSR error, we करोn't want to arm PSR
		 * again so we करोn't care about unmask the पूर्णांकerruption
		 * or unset irq_aux_error.
		 */
		val = पूर्णांकel_de_पढ़ो(dev_priv, imr_reg);
		val |= EDP_PSR_ERROR(trans_shअगरt);
		पूर्णांकel_de_ग_लिखो(dev_priv, imr_reg, val);

		schedule_work(&पूर्णांकel_dp->psr.work);
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_dp_get_alpm_status(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	u8 alpm_caps = 0;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_RECEIVER_ALPM_CAP,
			      &alpm_caps) != 1)
		वापस false;
	वापस alpm_caps & DP_ALPM_CAP;
पूर्ण

अटल u8 पूर्णांकel_dp_get_sink_sync_latency(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 val = 8; /* assume the worst अगर we can't पढ़ो the value */

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux,
			      DP_SYNCHRONIZATION_LATENCY_IN_SINK, &val) == 1)
		val &= DP_MAX_RESYNC_FRAME_COUNT_MASK;
	अन्यथा
		drm_dbg_kms(&i915->drm,
			    "Unable to get sink synchronization latency, assuming 8 frames\n");
	वापस val;
पूर्ण

अटल u16 पूर्णांकel_dp_get_su_x_granulartiy(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u16 val;
	sमाप_प्रकार r;

	/*
	 * Returning the शेष X granularity अगर granularity not required or
	 * अगर DPCD पढ़ो fails
	 */
	अगर (!(पूर्णांकel_dp->psr_dpcd[1] & DP_PSR2_SU_GRANULARITY_REQUIRED))
		वापस 4;

	r = drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_PSR2_SU_X_GRANULARITY, &val, 2);
	अगर (r != 2)
		drm_dbg_kms(&i915->drm,
			    "Unable to read DP_PSR2_SU_X_GRANULARITY\n");

	/*
	 * Spec says that अगर the value पढ़ो is 0 the शेष granularity should
	 * be used instead.
	 */
	अगर (r != 2 || val == 0)
		val = 4;

	वापस val;
पूर्ण

व्योम पूर्णांकel_psr_init_dpcd(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(dp_to_dig_port(पूर्णांकel_dp)->base.base.dev);

	drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_PSR_SUPPORT, पूर्णांकel_dp->psr_dpcd,
			 माप(पूर्णांकel_dp->psr_dpcd));

	अगर (!पूर्णांकel_dp->psr_dpcd[0])
		वापस;
	drm_dbg_kms(&dev_priv->drm, "eDP panel supports PSR version %x\n",
		    पूर्णांकel_dp->psr_dpcd[0]);

	अगर (drm_dp_has_quirk(&पूर्णांकel_dp->desc, DP_DPCD_QUIRK_NO_PSR)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR support not currently available for this panel\n");
		वापस;
	पूर्ण

	अगर (!(पूर्णांकel_dp->edp_dpcd[1] & DP_EDP_SET_POWER_CAP)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Panel lacks power state control, PSR cannot be enabled\n");
		वापस;
	पूर्ण

	पूर्णांकel_dp->psr.sink_support = true;
	पूर्णांकel_dp->psr.sink_sync_latency =
		पूर्णांकel_dp_get_sink_sync_latency(पूर्णांकel_dp);

	अगर (DISPLAY_VER(dev_priv) >= 9 &&
	    (पूर्णांकel_dp->psr_dpcd[0] == DP_PSR2_WITH_Y_COORD_IS_SUPPORTED)) अणु
		bool y_req = पूर्णांकel_dp->psr_dpcd[1] &
			     DP_PSR2_SU_Y_COORDINATE_REQUIRED;
		bool alpm = पूर्णांकel_dp_get_alpm_status(पूर्णांकel_dp);

		/*
		 * All panels that supports PSR version 03h (PSR2 +
		 * Y-coordinate) can handle Y-coordinates in VSC but we are
		 * only sure that it is going to be used when required by the
		 * panel. This way panel is capable to करो selective update
		 * without a aux frame sync.
		 *
		 * To support PSR version 02h and PSR version 03h without
		 * Y-coordinate requirement panels we would need to enable
		 * GTC first.
		 */
		पूर्णांकel_dp->psr.sink_psr2_support = y_req && alpm;
		drm_dbg_kms(&dev_priv->drm, "PSR2 %ssupported\n",
			    पूर्णांकel_dp->psr.sink_psr2_support ? "" : "not ");

		अगर (पूर्णांकel_dp->psr.sink_psr2_support) अणु
			पूर्णांकel_dp->psr.colorimetry_support =
				पूर्णांकel_dp_get_colorimetry_status(पूर्णांकel_dp);
			पूर्णांकel_dp->psr.su_x_granularity =
				पूर्णांकel_dp_get_su_x_granulartiy(पूर्णांकel_dp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hsw_psr_setup_aux(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 aux_घड़ी_भागider, aux_ctl;
	पूर्णांक i;
	अटल स्थिर u8 aux_msg[] = अणु
		[0] = DP_AUX_NATIVE_WRITE << 4,
		[1] = DP_SET_POWER >> 8,
		[2] = DP_SET_POWER & 0xff,
		[3] = 1 - 1,
		[4] = DP_SET_POWER_D0,
	पूर्ण;
	u32 psr_aux_mask = EDP_PSR_AUX_CTL_TIME_OUT_MASK |
			   EDP_PSR_AUX_CTL_MESSAGE_SIZE_MASK |
			   EDP_PSR_AUX_CTL_PRECHARGE_2US_MASK |
			   EDP_PSR_AUX_CTL_BIT_CLOCK_2X_MASK;

	BUILD_BUG_ON(माप(aux_msg) > 20);
	क्रम (i = 0; i < माप(aux_msg); i += 4)
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       EDP_PSR_AUX_DATA(पूर्णांकel_dp->psr.transcoder, i >> 2),
			       पूर्णांकel_dp_pack_aux(&aux_msg[i], माप(aux_msg) - i));

	aux_घड़ी_भागider = पूर्णांकel_dp->get_aux_घड़ी_भागider(पूर्णांकel_dp, 0);

	/* Start with bits set क्रम DDI_AUX_CTL रेजिस्टर */
	aux_ctl = पूर्णांकel_dp->get_aux_send_ctl(पूर्णांकel_dp, माप(aux_msg),
					     aux_घड़ी_भागider);

	/* Select only valid bits क्रम SRD_AUX_CTL */
	aux_ctl &= psr_aux_mask;
	पूर्णांकel_de_ग_लिखो(dev_priv, EDP_PSR_AUX_CTL(पूर्णांकel_dp->psr.transcoder),
		       aux_ctl);
पूर्ण

अटल व्योम पूर्णांकel_psr_enable_sink(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u8 dpcd_val = DP_PSR_ENABLE;

	/* Enable ALPM at sink क्रम psr2 */
	अगर (पूर्णांकel_dp->psr.psr2_enabled) अणु
		drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_RECEIVER_ALPM_CONFIG,
				   DP_ALPM_ENABLE |
				   DP_ALPM_LOCK_ERROR_IRQ_HPD_ENABLE);

		dpcd_val |= DP_PSR_ENABLE_PSR2 | DP_PSR_IRQ_HPD_WITH_CRC_ERRORS;
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकel_dp->psr.link_standby)
			dpcd_val |= DP_PSR_MAIN_LINK_ACTIVE;

		अगर (DISPLAY_VER(dev_priv) >= 8)
			dpcd_val |= DP_PSR_CRC_VERIFICATION;
	पूर्ण

	drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_PSR_EN_CFG, dpcd_val);

	drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_SET_POWER, DP_SET_POWER_D0);
पूर्ण

अटल u32 पूर्णांकel_psr1_get_tp_समय(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 val = 0;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		val |= EDP_PSR_TP4_TIME_0US;

	अगर (dev_priv->params.psr_safest_params) अणु
		val |= EDP_PSR_TP1_TIME_2500us;
		val |= EDP_PSR_TP2_TP3_TIME_2500us;
		जाओ check_tp3_sel;
	पूर्ण

	अगर (dev_priv->vbt.psr.tp1_wakeup_समय_us == 0)
		val |= EDP_PSR_TP1_TIME_0us;
	अन्यथा अगर (dev_priv->vbt.psr.tp1_wakeup_समय_us <= 100)
		val |= EDP_PSR_TP1_TIME_100us;
	अन्यथा अगर (dev_priv->vbt.psr.tp1_wakeup_समय_us <= 500)
		val |= EDP_PSR_TP1_TIME_500us;
	अन्यथा
		val |= EDP_PSR_TP1_TIME_2500us;

	अगर (dev_priv->vbt.psr.tp2_tp3_wakeup_समय_us == 0)
		val |= EDP_PSR_TP2_TP3_TIME_0us;
	अन्यथा अगर (dev_priv->vbt.psr.tp2_tp3_wakeup_समय_us <= 100)
		val |= EDP_PSR_TP2_TP3_TIME_100us;
	अन्यथा अगर (dev_priv->vbt.psr.tp2_tp3_wakeup_समय_us <= 500)
		val |= EDP_PSR_TP2_TP3_TIME_500us;
	अन्यथा
		val |= EDP_PSR_TP2_TP3_TIME_2500us;

check_tp3_sel:
	अगर (पूर्णांकel_dp_source_supports_hbr2(पूर्णांकel_dp) &&
	    drm_dp_tps3_supported(पूर्णांकel_dp->dpcd))
		val |= EDP_PSR_TP1_TP3_SEL;
	अन्यथा
		val |= EDP_PSR_TP1_TP2_SEL;

	वापस val;
पूर्ण

अटल u8 psr_compute_idle_frames(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक idle_frames;

	/* Let's use 6 as the minimum to cover all known हालs including the
	 * off-by-one issue that HW has in some हालs.
	 */
	idle_frames = max(6, dev_priv->vbt.psr.idle_frames);
	idle_frames = max(idle_frames, पूर्णांकel_dp->psr.sink_sync_latency + 1);

	अगर (drm_WARN_ON(&dev_priv->drm, idle_frames > 0xf))
		idle_frames = 0xf;

	वापस idle_frames;
पूर्ण

अटल व्योम hsw_activate_psr1(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 max_sleep_समय = 0x1f;
	u32 val = EDP_PSR_ENABLE;

	val |= psr_compute_idle_frames(पूर्णांकel_dp) << EDP_PSR_IDLE_FRAME_SHIFT;

	val |= max_sleep_समय << EDP_PSR_MAX_SLEEP_TIME_SHIFT;
	अगर (IS_HASWELL(dev_priv))
		val |= EDP_PSR_MIN_LINK_ENTRY_TIME_8_LINES;

	अगर (पूर्णांकel_dp->psr.link_standby)
		val |= EDP_PSR_LINK_STANDBY;

	val |= पूर्णांकel_psr1_get_tp_समय(पूर्णांकel_dp);

	अगर (DISPLAY_VER(dev_priv) >= 8)
		val |= EDP_PSR_CRC_ENABLE;

	val |= (पूर्णांकel_de_पढ़ो(dev_priv, EDP_PSR_CTL(पूर्णांकel_dp->psr.transcoder)) &
		EDP_PSR_RESTORE_PSR_ACTIVE_CTX_MASK);
	पूर्णांकel_de_ग_लिखो(dev_priv, EDP_PSR_CTL(पूर्णांकel_dp->psr.transcoder), val);
पूर्ण

अटल u32 पूर्णांकel_psr2_get_tp_समय(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 val = 0;

	अगर (dev_priv->params.psr_safest_params)
		वापस EDP_PSR2_TP2_TIME_2500us;

	अगर (dev_priv->vbt.psr.psr2_tp2_tp3_wakeup_समय_us >= 0 &&
	    dev_priv->vbt.psr.psr2_tp2_tp3_wakeup_समय_us <= 50)
		val |= EDP_PSR2_TP2_TIME_50us;
	अन्यथा अगर (dev_priv->vbt.psr.psr2_tp2_tp3_wakeup_समय_us <= 100)
		val |= EDP_PSR2_TP2_TIME_100us;
	अन्यथा अगर (dev_priv->vbt.psr.psr2_tp2_tp3_wakeup_समय_us <= 500)
		val |= EDP_PSR2_TP2_TIME_500us;
	अन्यथा
		val |= EDP_PSR2_TP2_TIME_2500us;

	वापस val;
पूर्ण

अटल व्योम hsw_activate_psr2(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 val;

	val = psr_compute_idle_frames(पूर्णांकel_dp) << EDP_PSR2_IDLE_FRAME_SHIFT;

	val |= EDP_PSR2_ENABLE | EDP_SU_TRACK_ENABLE;
	अगर (DISPLAY_VER(dev_priv) >= 10)
		val |= EDP_Y_COORDINATE_ENABLE;

	val |= EDP_PSR2_FRAME_BEFORE_SU(पूर्णांकel_dp->psr.sink_sync_latency + 1);
	val |= पूर्णांकel_psr2_get_tp_समय(पूर्णांकel_dp);

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		/*
		 * TODO: 7 lines of IO_BUFFER_WAKE and FAST_WAKE are शेष
		 * values from BSpec. In order to setting an optimal घातer
		 * consumption, lower than 4k resoluition mode needs to decrese
		 * IO_BUFFER_WAKE and FAST_WAKE. And higher than 4K resolution
		 * mode needs to increase IO_BUFFER_WAKE and FAST_WAKE.
		 */
		val |= TGL_EDP_PSR2_BLOCK_COUNT_NUM_2;
		val |= TGL_EDP_PSR2_IO_BUFFER_WAKE(7);
		val |= TGL_EDP_PSR2_FAST_WAKE(7);
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		val |= EDP_PSR2_IO_BUFFER_WAKE(7);
		val |= EDP_PSR2_FAST_WAKE(7);
	पूर्ण

	अगर (पूर्णांकel_dp->psr.psr2_sel_fetch_enabled) अणु
		/* WA 1408330847 */
		अगर (IS_TGL_DISPLAY_STEP(dev_priv, STEP_A0, STEP_A0) ||
		    IS_RKL_REVID(dev_priv, RKL_REVID_A0, RKL_REVID_A0))
			पूर्णांकel_de_rmw(dev_priv, CHICKEN_PAR1_1,
				     DIS_RAM_BYPASS_PSR2_MAN_TRACK,
				     DIS_RAM_BYPASS_PSR2_MAN_TRACK);

		पूर्णांकel_de_ग_लिखो(dev_priv,
			       PSR2_MAN_TRK_CTL(पूर्णांकel_dp->psr.transcoder),
			       PSR2_MAN_TRK_CTL_ENABLE);
	पूर्ण अन्यथा अगर (HAS_PSR2_SEL_FETCH(dev_priv)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       PSR2_MAN_TRK_CTL(पूर्णांकel_dp->psr.transcoder), 0);
	पूर्ण

	/*
	 * PSR2 HW is incorrectly using EDP_PSR_TP1_TP3_SEL and BSpec is
	 * recommending keep this bit unset जबतक PSR2 is enabled.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, EDP_PSR_CTL(पूर्णांकel_dp->psr.transcoder), 0);

	पूर्णांकel_de_ग_लिखो(dev_priv, EDP_PSR2_CTL(पूर्णांकel_dp->psr.transcoder), val);
पूर्ण

अटल bool
transcoder_has_psr2(काष्ठा drm_i915_निजी *dev_priv, क्रमागत transcoder trans)
अणु
	अगर (DISPLAY_VER(dev_priv) < 9)
		वापस false;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12)
		वापस trans == TRANSCODER_A;
	अन्यथा
		वापस trans == TRANSCODER_EDP;
पूर्ण

अटल u32 पूर्णांकel_get_frame_समय_us(स्थिर काष्ठा पूर्णांकel_crtc_state *cstate)
अणु
	अगर (!cstate || !cstate->hw.active)
		वापस 0;

	वापस DIV_ROUND_UP(1000 * 1000,
			    drm_mode_vrefresh(&cstate->hw.adjusted_mode));
पूर्ण

अटल व्योम psr2_program_idle_frames(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     u32 idle_frames)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 val;

	idle_frames <<=  EDP_PSR2_IDLE_FRAME_SHIFT;
	val = पूर्णांकel_de_पढ़ो(dev_priv, EDP_PSR2_CTL(पूर्णांकel_dp->psr.transcoder));
	val &= ~EDP_PSR2_IDLE_FRAME_MASK;
	val |= idle_frames;
	पूर्णांकel_de_ग_लिखो(dev_priv, EDP_PSR2_CTL(पूर्णांकel_dp->psr.transcoder), val);
पूर्ण

अटल व्योम tgl_psr2_enable_dc3co(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	psr2_program_idle_frames(पूर्णांकel_dp, 0);
	पूर्णांकel_display_घातer_set_target_dc_state(dev_priv, DC_STATE_EN_DC3CO);
पूर्ण

अटल व्योम tgl_psr2_disable_dc3co(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	पूर्णांकel_display_घातer_set_target_dc_state(dev_priv, DC_STATE_EN_UPTO_DC6);
	psr2_program_idle_frames(पूर्णांकel_dp, psr_compute_idle_frames(पूर्णांकel_dp));
पूर्ण

अटल व्योम tgl_dc3co_disable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp =
		container_of(work, typeof(*पूर्णांकel_dp), psr.dc3co_work.work);

	mutex_lock(&पूर्णांकel_dp->psr.lock);
	/* If delayed work is pending, it is not idle */
	अगर (delayed_work_pending(&पूर्णांकel_dp->psr.dc3co_work))
		जाओ unlock;

	tgl_psr2_disable_dc3co(पूर्णांकel_dp);
unlock:
	mutex_unlock(&पूर्णांकel_dp->psr.lock);
पूर्ण

अटल व्योम tgl_disallow_dc3co_on_psr2_निकास(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	अगर (!पूर्णांकel_dp->psr.dc3co_enabled)
		वापस;

	cancel_delayed_work(&पूर्णांकel_dp->psr.dc3co_work);
	/* Beक्रमe PSR2 निकास disallow dc3co*/
	tgl_psr2_disable_dc3co(पूर्णांकel_dp);
पूर्ण

अटल व्योम
tgl_dc3co_निकासline_compute_config(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर u32 crtc_vdisplay = crtc_state->uapi.adjusted_mode.crtc_vdisplay;
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 निकास_scanlines;

	/*
	 * DMC's DC3CO निकास mechanism has an issue with Selective Fecth
	 * TODO: when the issue is addressed, this restriction should be हटाओd.
	 */
	अगर (crtc_state->enable_psr2_sel_fetch)
		वापस;

	अगर (!(dev_priv->csr.allowed_dc_mask & DC_STATE_EN_DC3CO))
		वापस;

	/* B.Specs:49196 DC3CO only works with pipeA and DDIA.*/
	अगर (to_पूर्णांकel_crtc(crtc_state->uapi.crtc)->pipe != PIPE_A ||
	    dig_port->base.port != PORT_A)
		वापस;

	/*
	 * DC3CO Exit समय 200us B.Spec 49196
	 * PSR2 transcoder Early Exit scanlines = ROUNDUP(200 / line समय) + 1
	 */
	निकास_scanlines =
		पूर्णांकel_usecs_to_scanlines(&crtc_state->uapi.adjusted_mode, 200) + 1;

	अगर (drm_WARN_ON(&dev_priv->drm, निकास_scanlines > crtc_vdisplay))
		वापस;

	crtc_state->dc3co_निकासline = crtc_vdisplay - निकास_scanlines;
पूर्ण

अटल bool पूर्णांकel_psr2_sel_fetch_config_valid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					      काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(crtc_state->uapi.state);
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक i;

	अगर (!dev_priv->params.enable_psr2_sel_fetch &&
	    पूर्णांकel_dp->psr.debug != I915_PSR_DEBUG_ENABLE_SEL_FETCH) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR2 sel fetch not enabled, disabled by parameter\n");
		वापस false;
	पूर्ण

	अगर (crtc_state->uapi.async_flip) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR2 sel fetch not enabled, async flip enabled\n");
		वापस false;
	पूर्ण

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane_state->uapi.rotation != DRM_MODE_ROTATE_0) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "PSR2 sel fetch not enabled, plane rotated\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस crtc_state->enable_psr2_sel_fetch = true;
पूर्ण

अटल bool पूर्णांकel_psr2_config_valid(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				    काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक crtc_hdisplay = crtc_state->hw.adjusted_mode.crtc_hdisplay;
	पूर्णांक crtc_vdisplay = crtc_state->hw.adjusted_mode.crtc_vdisplay;
	पूर्णांक psr_max_h = 0, psr_max_v = 0, max_bpp = 0;

	अगर (!पूर्णांकel_dp->psr.sink_psr2_support)
		वापस false;

	/* JSL and EHL only supports eDP 1.3 */
	अगर (IS_JSL_EHL(dev_priv)) अणु
		drm_dbg_kms(&dev_priv->drm, "PSR2 not supported by phy\n");
		वापस false;
	पूर्ण

	अगर (!transcoder_has_psr2(dev_priv, crtc_state->cpu_transcoder)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR2 not supported in transcoder %s\n",
			    transcoder_name(crtc_state->cpu_transcoder));
		वापस false;
	पूर्ण

	अगर (!psr2_global_enabled(पूर्णांकel_dp)) अणु
		drm_dbg_kms(&dev_priv->drm, "PSR2 disabled by flag\n");
		वापस false;
	पूर्ण

	/*
	 * DSC and PSR2 cannot be enabled simultaneously. If a requested
	 * resolution requires DSC to be enabled, priority is given to DSC
	 * over PSR2.
	 */
	अगर (crtc_state->dsc.compression_enable) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR2 cannot be enabled since DSC is enabled\n");
		वापस false;
	पूर्ण

	अगर (crtc_state->crc_enabled) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR2 not enabled because it would inhibit pipe CRC calculation\n");
		वापस false;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		psr_max_h = 5120;
		psr_max_v = 3200;
		max_bpp = 30;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 10) अणु
		psr_max_h = 4096;
		psr_max_v = 2304;
		max_bpp = 24;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 9)) अणु
		psr_max_h = 3640;
		psr_max_v = 2304;
		max_bpp = 24;
	पूर्ण

	अगर (crtc_state->pipe_bpp > max_bpp) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR2 not enabled, pipe bpp %d > max supported %d\n",
			    crtc_state->pipe_bpp, max_bpp);
		वापस false;
	पूर्ण

	/*
	 * HW sends SU blocks of size four scan lines, which means the starting
	 * X coordinate and Y granularity requirements will always be met. We
	 * only need to validate the SU block width is a multiple of
	 * x granularity.
	 */
	अगर (crtc_hdisplay % पूर्णांकel_dp->psr.su_x_granularity) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR2 not enabled, hdisplay(%d) not multiple of %d\n",
			    crtc_hdisplay, पूर्णांकel_dp->psr.su_x_granularity);
		वापस false;
	पूर्ण

	अगर (HAS_PSR2_SEL_FETCH(dev_priv)) अणु
		अगर (!पूर्णांकel_psr2_sel_fetch_config_valid(पूर्णांकel_dp, crtc_state) &&
		    !HAS_PSR_HW_TRACKING(dev_priv)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "PSR2 not enabled, selective fetch not valid and no HW tracking available\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (!crtc_state->enable_psr2_sel_fetch &&
	    (crtc_hdisplay > psr_max_h || crtc_vdisplay > psr_max_v)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR2 not enabled, resolution %dx%d > max supported %dx%d\n",
			    crtc_hdisplay, crtc_vdisplay,
			    psr_max_h, psr_max_v);
		वापस false;
	पूर्ण

	tgl_dc3co_निकासline_compute_config(पूर्णांकel_dp, crtc_state);
	वापस true;
पूर्ण

व्योम पूर्णांकel_psr_compute_config(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	पूर्णांक psr_setup_समय;

	/*
	 * Current PSR panels करोnt work reliably with VRR enabled
	 * So अगर VRR is enabled, करो not enable PSR.
	 */
	अगर (crtc_state->vrr.enable)
		वापस;

	अगर (!CAN_PSR(पूर्णांकel_dp))
		वापस;

	अगर (!psr_global_enabled(पूर्णांकel_dp)) अणु
		drm_dbg_kms(&dev_priv->drm, "PSR disabled by flag\n");
		वापस;
	पूर्ण

	अगर (पूर्णांकel_dp->psr.sink_not_reliable) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR sink implementation is not reliable\n");
		वापस;
	पूर्ण

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR condition failed: Interlaced mode enabled\n");
		वापस;
	पूर्ण

	psr_setup_समय = drm_dp_psr_setup_समय(पूर्णांकel_dp->psr_dpcd);
	अगर (psr_setup_समय < 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR condition failed: Invalid PSR setup time (0x%02x)\n",
			    पूर्णांकel_dp->psr_dpcd[1]);
		वापस;
	पूर्ण

	अगर (पूर्णांकel_usecs_to_scanlines(adjusted_mode, psr_setup_समय) >
	    adjusted_mode->crtc_vtotal - adjusted_mode->crtc_vdisplay - 1) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR condition failed: PSR setup time (%d us) too long\n",
			    psr_setup_समय);
		वापस;
	पूर्ण

	crtc_state->has_psr = true;
	crtc_state->has_psr2 = पूर्णांकel_psr2_config_valid(पूर्णांकel_dp, crtc_state);
	crtc_state->infoframes.enable |= पूर्णांकel_hdmi_infoframe_enable(DP_SDP_VSC);
पूर्ण

अटल व्योम पूर्णांकel_psr_activate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	क्रमागत transcoder transcoder = पूर्णांकel_dp->psr.transcoder;

	अगर (transcoder_has_psr2(dev_priv, transcoder))
		drm_WARN_ON(&dev_priv->drm,
			    पूर्णांकel_de_पढ़ो(dev_priv, EDP_PSR2_CTL(transcoder)) & EDP_PSR2_ENABLE);

	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, EDP_PSR_CTL(transcoder)) & EDP_PSR_ENABLE);
	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->psr.active);
	lockdep_निश्चित_held(&पूर्णांकel_dp->psr.lock);

	/* psr1 and psr2 are mutually exclusive.*/
	अगर (पूर्णांकel_dp->psr.psr2_enabled)
		hsw_activate_psr2(पूर्णांकel_dp);
	अन्यथा
		hsw_activate_psr1(पूर्णांकel_dp);

	पूर्णांकel_dp->psr.active = true;
पूर्ण

अटल व्योम पूर्णांकel_psr_enable_source(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 mask;

	/* Only HSW and BDW have PSR AUX रेजिस्टरs that need to be setup. SKL+
	 * use hardcoded values PSR AUX transactions
	 */
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		hsw_psr_setup_aux(पूर्णांकel_dp);

	अगर (पूर्णांकel_dp->psr.psr2_enabled && IS_DISPLAY_VER(dev_priv, 9)) अणु
		i915_reg_t reg = CHICKEN_TRANS(cpu_transcoder);
		u32 chicken = पूर्णांकel_de_पढ़ो(dev_priv, reg);

		chicken |= PSR2_VSC_ENABLE_PROG_HEADER |
			   PSR2_ADD_VERTICAL_LINE_COUNT;
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, chicken);
	पूर्ण

	/*
	 * Per Spec: Aव्योम continuous PSR निकास by masking MEMUP and HPD also
	 * mask LPSP to aव्योम dependency on other drivers that might block
	 * runसमय_pm besides preventing  other hw tracking issues now we
	 * can rely on frontbuffer tracking.
	 */
	mask = EDP_PSR_DEBUG_MASK_MEMUP |
	       EDP_PSR_DEBUG_MASK_HPD |
	       EDP_PSR_DEBUG_MASK_LPSP |
	       EDP_PSR_DEBUG_MASK_MAX_SLEEP;

	अगर (DISPLAY_VER(dev_priv) < 11)
		mask |= EDP_PSR_DEBUG_MASK_DISP_REG_WRITE;

	पूर्णांकel_de_ग_लिखो(dev_priv, EDP_PSR_DEBUG(पूर्णांकel_dp->psr.transcoder),
		       mask);

	psr_irq_control(पूर्णांकel_dp);

	अगर (crtc_state->dc3co_निकासline) अणु
		u32 val;

		/*
		 * TODO: अगर future platक्रमms supports DC3CO in more than one
		 * transcoder, EXITLINE will need to be unset when disabling PSR
		 */
		val = पूर्णांकel_de_पढ़ो(dev_priv, EXITLINE(cpu_transcoder));
		val &= ~EXITLINE_MASK;
		val |= crtc_state->dc3co_निकासline << EXITLINE_SHIFT;
		val |= EXITLINE_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, EXITLINE(cpu_transcoder), val);
	पूर्ण

	अगर (HAS_PSR_HW_TRACKING(dev_priv) && HAS_PSR2_SEL_FETCH(dev_priv))
		पूर्णांकel_de_rmw(dev_priv, CHICKEN_PAR1_1, IGNORE_PSR2_HW_TRACKING,
			     पूर्णांकel_dp->psr.psr2_sel_fetch_enabled ?
			     IGNORE_PSR2_HW_TRACKING : 0);
पूर्ण

अटल व्योम पूर्णांकel_psr_enable_locked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *encoder = &dig_port->base;
	u32 val;

	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->psr.enabled);

	पूर्णांकel_dp->psr.psr2_enabled = crtc_state->has_psr2;
	पूर्णांकel_dp->psr.busy_frontbuffer_bits = 0;
	पूर्णांकel_dp->psr.pipe = to_पूर्णांकel_crtc(crtc_state->uapi.crtc)->pipe;
	पूर्णांकel_dp->psr.dc3co_enabled = !!crtc_state->dc3co_निकासline;
	पूर्णांकel_dp->psr.transcoder = crtc_state->cpu_transcoder;
	/* DC5/DC6 requires at least 6 idle frames */
	val = usecs_to_jअगरfies(पूर्णांकel_get_frame_समय_us(crtc_state) * 6);
	पूर्णांकel_dp->psr.dc3co_निकास_delay = val;
	पूर्णांकel_dp->psr.psr2_sel_fetch_enabled = crtc_state->enable_psr2_sel_fetch;

	/*
	 * If a PSR error happened and the driver is reloaded, the EDP_PSR_IIR
	 * will still keep the error set even after the reset करोne in the
	 * irq_preinstall and irq_uninstall hooks.
	 * And enabling in this situation cause the screen to मुक्तze in the
	 * first समय that PSR HW tries to activate so lets keep PSR disabled
	 * to aव्योम any rendering problems.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    TRANS_PSR_IIR(पूर्णांकel_dp->psr.transcoder));
		val &= EDP_PSR_ERROR(0);
	पूर्ण अन्यथा अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, EDP_PSR_IIR);
		val &= EDP_PSR_ERROR(पूर्णांकel_dp->psr.transcoder);
	पूर्ण
	अगर (val) अणु
		पूर्णांकel_dp->psr.sink_not_reliable = true;
		drm_dbg_kms(&dev_priv->drm,
			    "PSR interruption error set, not enabling PSR\n");
		वापस;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "Enabling PSR%s\n",
		    पूर्णांकel_dp->psr.psr2_enabled ? "2" : "1");
	पूर्णांकel_dp_compute_psr_vsc_sdp(पूर्णांकel_dp, crtc_state, conn_state,
				     &पूर्णांकel_dp->psr.vsc);
	पूर्णांकel_ग_लिखो_dp_vsc_sdp(encoder, crtc_state, &पूर्णांकel_dp->psr.vsc);
	पूर्णांकel_psr_enable_sink(पूर्णांकel_dp);
	पूर्णांकel_psr_enable_source(पूर्णांकel_dp, crtc_state);
	पूर्णांकel_dp->psr.enabled = true;

	पूर्णांकel_psr_activate(पूर्णांकel_dp);
पूर्ण

/**
 * पूर्णांकel_psr_enable - Enable PSR
 * @पूर्णांकel_dp: Intel DP
 * @crtc_state: new CRTC state
 * @conn_state: new CONNECTOR state
 *
 * This function can only be called after the pipe is fully trained and enabled.
 */
व्योम पूर्णांकel_psr_enable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (!CAN_PSR(पूर्णांकel_dp))
		वापस;

	अगर (!crtc_state->has_psr)
		वापस;

	drm_WARN_ON(&dev_priv->drm, dev_priv->drrs.dp);

	mutex_lock(&पूर्णांकel_dp->psr.lock);
	पूर्णांकel_psr_enable_locked(पूर्णांकel_dp, crtc_state, conn_state);
	mutex_unlock(&पूर्णांकel_dp->psr.lock);
पूर्ण

अटल व्योम पूर्णांकel_psr_निकास(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 val;

	अगर (!पूर्णांकel_dp->psr.active) अणु
		अगर (transcoder_has_psr2(dev_priv, पूर्णांकel_dp->psr.transcoder)) अणु
			val = पूर्णांकel_de_पढ़ो(dev_priv,
					    EDP_PSR2_CTL(पूर्णांकel_dp->psr.transcoder));
			drm_WARN_ON(&dev_priv->drm, val & EDP_PSR2_ENABLE);
		पूर्ण

		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    EDP_PSR_CTL(पूर्णांकel_dp->psr.transcoder));
		drm_WARN_ON(&dev_priv->drm, val & EDP_PSR_ENABLE);

		वापस;
	पूर्ण

	अगर (पूर्णांकel_dp->psr.psr2_enabled) अणु
		tgl_disallow_dc3co_on_psr2_निकास(पूर्णांकel_dp);
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    EDP_PSR2_CTL(पूर्णांकel_dp->psr.transcoder));
		drm_WARN_ON(&dev_priv->drm, !(val & EDP_PSR2_ENABLE));
		val &= ~EDP_PSR2_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       EDP_PSR2_CTL(पूर्णांकel_dp->psr.transcoder), val);
	पूर्ण अन्यथा अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    EDP_PSR_CTL(पूर्णांकel_dp->psr.transcoder));
		drm_WARN_ON(&dev_priv->drm, !(val & EDP_PSR_ENABLE));
		val &= ~EDP_PSR_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       EDP_PSR_CTL(पूर्णांकel_dp->psr.transcoder), val);
	पूर्ण
	पूर्णांकel_dp->psr.active = false;
पूर्ण

अटल व्योम पूर्णांकel_psr_disable_locked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	i915_reg_t psr_status;
	u32 psr_status_mask;

	lockdep_निश्चित_held(&पूर्णांकel_dp->psr.lock);

	अगर (!पूर्णांकel_dp->psr.enabled)
		वापस;

	drm_dbg_kms(&dev_priv->drm, "Disabling PSR%s\n",
		    पूर्णांकel_dp->psr.psr2_enabled ? "2" : "1");

	पूर्णांकel_psr_निकास(पूर्णांकel_dp);

	अगर (पूर्णांकel_dp->psr.psr2_enabled) अणु
		psr_status = EDP_PSR2_STATUS(पूर्णांकel_dp->psr.transcoder);
		psr_status_mask = EDP_PSR2_STATUS_STATE_MASK;
	पूर्ण अन्यथा अणु
		psr_status = EDP_PSR_STATUS(पूर्णांकel_dp->psr.transcoder);
		psr_status_mask = EDP_PSR_STATUS_STATE_MASK;
	पूर्ण

	/* Wait till PSR is idle */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, psr_status,
				    psr_status_mask, 2000))
		drm_err(&dev_priv->drm, "Timed out waiting PSR idle state\n");

	/* WA 1408330847 */
	अगर (पूर्णांकel_dp->psr.psr2_sel_fetch_enabled &&
	    (IS_TGL_DISPLAY_STEP(dev_priv, STEP_A0, STEP_A0) ||
	     IS_RKL_REVID(dev_priv, RKL_REVID_A0, RKL_REVID_A0)))
		पूर्णांकel_de_rmw(dev_priv, CHICKEN_PAR1_1,
			     DIS_RAM_BYPASS_PSR2_MAN_TRACK, 0);

	/* Disable PSR on Sink */
	drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_PSR_EN_CFG, 0);

	अगर (पूर्णांकel_dp->psr.psr2_enabled)
		drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_RECEIVER_ALPM_CONFIG, 0);

	पूर्णांकel_dp->psr.enabled = false;
पूर्ण

/**
 * पूर्णांकel_psr_disable - Disable PSR
 * @पूर्णांकel_dp: Intel DP
 * @old_crtc_state: old CRTC state
 *
 * This function needs to be called beक्रमe disabling pipe.
 */
व्योम पूर्णांकel_psr_disable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		       स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (!old_crtc_state->has_psr)
		वापस;

	अगर (drm_WARN_ON(&dev_priv->drm, !CAN_PSR(पूर्णांकel_dp)))
		वापस;

	mutex_lock(&पूर्णांकel_dp->psr.lock);

	पूर्णांकel_psr_disable_locked(पूर्णांकel_dp);

	mutex_unlock(&पूर्णांकel_dp->psr.lock);
	cancel_work_sync(&पूर्णांकel_dp->psr.work);
	cancel_delayed_work_sync(&पूर्णांकel_dp->psr.dc3co_work);
पूर्ण

अटल व्योम psr_क्रमce_hw_tracking_निकास(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (IS_TIGERLAKE(dev_priv))
		/*
		 * Writes to CURSURFLIVE in TGL are causing IOMMU errors and
		 * visual glitches that are often reproduced when executing
		 * CPU पूर्णांकensive workloads जबतक a eDP 4K panel is attached.
		 *
		 * Manually निकासing PSR causes the frontbuffer to be updated
		 * without glitches and the IOMMU errors are also gone but
		 * this comes at the cost of less समय with PSR active.
		 *
		 * So using this workaround until this issue is root caused
		 * and a better fix is found.
		 */
		पूर्णांकel_psr_निकास(पूर्णांकel_dp);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 9)
		/*
		 * Display WA #0884: skl+
		 * This करोcumented WA क्रम bxt can be safely applied
		 * broadly so we can क्रमce HW tracking to निकास PSR
		 * instead of disabling and re-enabling.
		 * Workaround tells us to ग_लिखो 0 to CUR_SURFLIVE_A,
		 * but it makes more sense ग_लिखो to the current active
		 * pipe.
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, CURSURFLIVE(पूर्णांकel_dp->psr.pipe), 0);
	अन्यथा
		/*
		 * A ग_लिखो to CURSURFLIVE करो not cause HW tracking to निकास PSR
		 * on older gens so करोing the manual निकास instead.
		 */
		पूर्णांकel_psr_निकास(पूर्णांकel_dp);
पूर्ण

व्योम पूर्णांकel_psr2_program_plane_sel_fetch(काष्ठा पूर्णांकel_plane *plane,
					स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
					पूर्णांक color_plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	स्थिर काष्ठा drm_rect *clip;
	u32 val, offset;
	पूर्णांक ret, x, y;

	अगर (!crtc_state->enable_psr2_sel_fetch)
		वापस;

	val = plane_state ? plane_state->ctl : 0;
	val &= plane->id == PLANE_CURSOR ? val : PLANE_SEL_FETCH_CTL_ENABLE;
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_SEL_FETCH_CTL(pipe, plane->id), val);
	अगर (!val || plane->id == PLANE_CURSOR)
		वापस;

	clip = &plane_state->psr2_sel_fetch_area;

	val = (clip->y1 + plane_state->uapi.dst.y1) << 16;
	val |= plane_state->uapi.dst.x1;
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_SEL_FETCH_POS(pipe, plane->id), val);

	/* TODO: consider auxiliary surfaces */
	x = plane_state->uapi.src.x1 >> 16;
	y = (plane_state->uapi.src.y1 >> 16) + clip->y1;
	ret = skl_calc_मुख्य_surface_offset(plane_state, &x, &y, &offset);
	अगर (ret)
		drm_warn_once(&dev_priv->drm, "skl_calc_main_surface_offset() returned %i\n",
			      ret);
	val = y << 16 | x;
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_SEL_FETCH_OFFSET(pipe, plane->id),
			  val);

	/* Sizes are 0 based */
	val = (drm_rect_height(clip) - 1) << 16;
	val |= (drm_rect_width(&plane_state->uapi.src) >> 16) - 1;
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_SEL_FETCH_SIZE(pipe, plane->id), val);
पूर्ण

व्योम पूर्णांकel_psr2_program_trans_man_trk_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	अगर (!HAS_PSR2_SEL_FETCH(dev_priv) ||
	    !crtc_state->enable_psr2_sel_fetch)
		वापस;

	पूर्णांकel_de_ग_लिखो(dev_priv, PSR2_MAN_TRK_CTL(crtc_state->cpu_transcoder),
		       crtc_state->psr2_man_track_ctl);
पूर्ण

अटल व्योम psr2_man_trk_ctl_calc(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  काष्ठा drm_rect *clip, bool full_update)
अणु
	u32 val = PSR2_MAN_TRK_CTL_ENABLE;

	अगर (full_update) अणु
		val |= PSR2_MAN_TRK_CTL_SF_SINGLE_FULL_FRAME;
		जाओ निकास;
	पूर्ण

	अगर (clip->y1 == -1)
		जाओ निकास;

	drm_WARN_ON(crtc_state->uapi.crtc->dev, clip->y1 % 4 || clip->y2 % 4);

	val |= PSR2_MAN_TRK_CTL_SF_PARTIAL_FRAME_UPDATE;
	val |= PSR2_MAN_TRK_CTL_SU_REGION_START_ADDR(clip->y1 / 4 + 1);
	val |= PSR2_MAN_TRK_CTL_SU_REGION_END_ADDR(clip->y2 / 4 + 1);
निकास:
	crtc_state->psr2_man_track_ctl = val;
पूर्ण

अटल व्योम clip_area_update(काष्ठा drm_rect *overlap_damage_area,
			     काष्ठा drm_rect *damage_area)
अणु
	अगर (overlap_damage_area->y1 == -1) अणु
		overlap_damage_area->y1 = damage_area->y1;
		overlap_damage_area->y2 = damage_area->y2;
		वापस;
	पूर्ण

	अगर (damage_area->y1 < overlap_damage_area->y1)
		overlap_damage_area->y1 = damage_area->y1;

	अगर (damage_area->y2 > overlap_damage_area->y2)
		overlap_damage_area->y2 = damage_area->y2;
पूर्ण

पूर्णांक पूर्णांकel_psr2_sel_fetch_update(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_rect pipe_clip = अणु .x1 = 0, .y1 = -1, .x2 = पूर्णांक_उच्च, .y2 = -1 पूर्ण;
	काष्ठा पूर्णांकel_plane_state *new_plane_state, *old_plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	bool full_update = false;
	पूर्णांक i, ret;

	अगर (!crtc_state->enable_psr2_sel_fetch)
		वापस 0;

	ret = drm_atomic_add_affected_planes(&state->base, &crtc->base);
	अगर (ret)
		वापस ret;

	/*
	 * Calculate minimal selective fetch area of each plane and calculate
	 * the pipe damaged area.
	 * In the next loop the plane selective fetch area will actually be set
	 * using whole pipe damaged area.
	 */
	क्रम_each_oldnew_पूर्णांकel_plane_in_state(state, plane, old_plane_state,
					     new_plane_state, i) अणु
		काष्ठा drm_rect src, damaged_area = अणु .y1 = -1 पूर्ण;
		काष्ठा drm_mode_rect *damaged_clips;
		u32 num_clips, j;

		अगर (new_plane_state->uapi.crtc != crtc_state->uapi.crtc)
			जारी;

		अगर (!new_plane_state->uapi.visible &&
		    !old_plane_state->uapi.visible)
			जारी;

		/*
		 * TODO: Not clear how to handle planes with negative position,
		 * also planes are not updated अगर they have a negative X
		 * position so क्रम now करोing a full update in this हालs
		 */
		अगर (new_plane_state->uapi.dst.y1 < 0 ||
		    new_plane_state->uapi.dst.x1 < 0) अणु
			full_update = true;
			अवरोध;
		पूर्ण

		num_clips = drm_plane_get_damage_clips_count(&new_plane_state->uapi);

		/*
		 * If visibility or plane moved, mark the whole plane area as
		 * damaged as it needs to be complete redraw in the new and old
		 * position.
		 */
		अगर (new_plane_state->uapi.visible != old_plane_state->uapi.visible ||
		    !drm_rect_equals(&new_plane_state->uapi.dst,
				     &old_plane_state->uapi.dst)) अणु
			अगर (old_plane_state->uapi.visible) अणु
				damaged_area.y1 = old_plane_state->uapi.dst.y1;
				damaged_area.y2 = old_plane_state->uapi.dst.y2;
				clip_area_update(&pipe_clip, &damaged_area);
			पूर्ण

			अगर (new_plane_state->uapi.visible) अणु
				damaged_area.y1 = new_plane_state->uapi.dst.y1;
				damaged_area.y2 = new_plane_state->uapi.dst.y2;
				clip_area_update(&pipe_clip, &damaged_area);
			पूर्ण
			जारी;
		पूर्ण अन्यथा अगर (new_plane_state->uapi.alpha != old_plane_state->uapi.alpha ||
			   (!num_clips &&
			    new_plane_state->uapi.fb != old_plane_state->uapi.fb)) अणु
			/*
			 * If the plane करोn't have damaged areas but the
			 * framebuffer changed or alpha changed, mark the whole
			 * plane area as damaged.
			 */
			damaged_area.y1 = new_plane_state->uapi.dst.y1;
			damaged_area.y2 = new_plane_state->uapi.dst.y2;
			clip_area_update(&pipe_clip, &damaged_area);
			जारी;
		पूर्ण

		drm_rect_fp_to_पूर्णांक(&src, &new_plane_state->uapi.src);
		damaged_clips = drm_plane_get_damage_clips(&new_plane_state->uapi);

		क्रम (j = 0; j < num_clips; j++) अणु
			काष्ठा drm_rect clip;

			clip.x1 = damaged_clips[j].x1;
			clip.y1 = damaged_clips[j].y1;
			clip.x2 = damaged_clips[j].x2;
			clip.y2 = damaged_clips[j].y2;
			अगर (drm_rect_पूर्णांकersect(&clip, &src))
				clip_area_update(&damaged_area, &clip);
		पूर्ण

		अगर (damaged_area.y1 == -1)
			जारी;

		damaged_area.y1 += new_plane_state->uapi.dst.y1 - src.y1;
		damaged_area.y2 += new_plane_state->uapi.dst.y1 - src.y1;
		clip_area_update(&pipe_clip, &damaged_area);
	पूर्ण

	अगर (full_update)
		जाओ skip_sel_fetch_set_loop;

	/* It must be aligned to 4 lines */
	pipe_clip.y1 -= pipe_clip.y1 % 4;
	अगर (pipe_clip.y2 % 4)
		pipe_clip.y2 = ((pipe_clip.y2 / 4) + 1) * 4;

	/*
	 * Now that we have the pipe damaged area check अगर it पूर्णांकersect with
	 * every plane, अगर it करोes set the plane selective fetch area.
	 */
	क्रम_each_oldnew_पूर्णांकel_plane_in_state(state, plane, old_plane_state,
					     new_plane_state, i) अणु
		काष्ठा drm_rect *sel_fetch_area, पूर्णांकer;

		अगर (new_plane_state->uapi.crtc != crtc_state->uapi.crtc ||
		    !new_plane_state->uapi.visible)
			जारी;

		पूर्णांकer = pipe_clip;
		अगर (!drm_rect_पूर्णांकersect(&पूर्णांकer, &new_plane_state->uapi.dst))
			जारी;

		sel_fetch_area = &new_plane_state->psr2_sel_fetch_area;
		sel_fetch_area->y1 = पूर्णांकer.y1 - new_plane_state->uapi.dst.y1;
		sel_fetch_area->y2 = पूर्णांकer.y2 - new_plane_state->uapi.dst.y1;
	पूर्ण

skip_sel_fetch_set_loop:
	psr2_man_trk_ctl_calc(crtc_state, &pipe_clip, full_update);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_psr_update - Update PSR state
 * @पूर्णांकel_dp: Intel DP
 * @crtc_state: new CRTC state
 * @conn_state: new CONNECTOR state
 *
 * This functions will update PSR states, disabling, enabling or चयनing PSR
 * version when executing fastsets. For full modeset, पूर्णांकel_psr_disable() and
 * पूर्णांकel_psr_enable() should be called instead.
 */
व्योम पूर्णांकel_psr_update(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_psr *psr = &पूर्णांकel_dp->psr;
	bool enable, psr2_enable;

	अगर (!CAN_PSR(पूर्णांकel_dp))
		वापस;

	mutex_lock(&पूर्णांकel_dp->psr.lock);

	enable = crtc_state->has_psr;
	psr2_enable = crtc_state->has_psr2;

	अगर (enable == psr->enabled && psr2_enable == psr->psr2_enabled &&
	    crtc_state->enable_psr2_sel_fetch == psr->psr2_sel_fetch_enabled) अणु
		/* Force a PSR निकास when enabling CRC to aव्योम CRC समयouts */
		अगर (crtc_state->crc_enabled && psr->enabled)
			psr_क्रमce_hw_tracking_निकास(पूर्णांकel_dp);
		अन्यथा अगर (DISPLAY_VER(dev_priv) < 9 && psr->enabled) अणु
			/*
			 * Activate PSR again after a क्रमce निकास when enabling
			 * CRC in older gens
			 */
			अगर (!पूर्णांकel_dp->psr.active &&
			    !पूर्णांकel_dp->psr.busy_frontbuffer_bits)
				schedule_work(&पूर्णांकel_dp->psr.work);
		पूर्ण

		जाओ unlock;
	पूर्ण

	अगर (psr->enabled)
		पूर्णांकel_psr_disable_locked(पूर्णांकel_dp);

	अगर (enable)
		पूर्णांकel_psr_enable_locked(पूर्णांकel_dp, crtc_state, conn_state);

unlock:
	mutex_unlock(&पूर्णांकel_dp->psr.lock);
पूर्ण

/**
 * psr_रुको_क्रम_idle - रुको क्रम PSR1 to idle
 * @पूर्णांकel_dp: Intel DP
 * @out_value: PSR status in हाल of failure
 *
 * Returns: 0 on success or -ETIMEOUT अगर PSR status करोes not idle.
 *
 */
अटल पूर्णांक psr_रुको_क्रम_idle(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u32 *out_value)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	/*
	 * From bspec: Panel Self Refresh (BDW+)
	 * Max. समय क्रम PSR to idle = Inverse of the refresh rate + 6 ms of
	 * निकास training समय + 1.5 ms of aux channel handshake. 50 ms is
	 * defensive enough to cover everything.
	 */
	वापस __पूर्णांकel_रुको_क्रम_रेजिस्टर(&dev_priv->uncore,
					 EDP_PSR_STATUS(पूर्णांकel_dp->psr.transcoder),
					 EDP_PSR_STATUS_STATE_MASK,
					 EDP_PSR_STATUS_STATE_IDLE, 2, 50,
					 out_value);
पूर्ण

/**
 * पूर्णांकel_psr_रुको_क्रम_idle - रुको क्रम PSR1 to idle
 * @new_crtc_state: new CRTC state
 *
 * This function is expected to be called from pipe_update_start() where it is
 * not expected to race with PSR enable or disable.
 */
व्योम पूर्णांकel_psr_रुको_क्रम_idle(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(new_crtc_state->uapi.crtc->dev);
	काष्ठा पूर्णांकel_encoder *encoder;

	अगर (!new_crtc_state->has_psr)
		वापस;

	क्रम_each_पूर्णांकel_encoder_mask_with_psr(&dev_priv->drm, encoder,
					     new_crtc_state->uapi.encoder_mask) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
		u32 psr_status;

		mutex_lock(&पूर्णांकel_dp->psr.lock);
		अगर (!पूर्णांकel_dp->psr.enabled || पूर्णांकel_dp->psr.psr2_enabled) अणु
			mutex_unlock(&पूर्णांकel_dp->psr.lock);
			जारी;
		पूर्ण

		/* when the PSR1 is enabled */
		अगर (psr_रुको_क्रम_idle(पूर्णांकel_dp, &psr_status))
			drm_err(&dev_priv->drm,
				"PSR idle timed out 0x%x, atomic update may fail\n",
				psr_status);
		mutex_unlock(&पूर्णांकel_dp->psr.lock);
	पूर्ण
पूर्ण

अटल bool __psr_रुको_क्रम_idle_locked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	i915_reg_t reg;
	u32 mask;
	पूर्णांक err;

	अगर (!पूर्णांकel_dp->psr.enabled)
		वापस false;

	अगर (पूर्णांकel_dp->psr.psr2_enabled) अणु
		reg = EDP_PSR2_STATUS(पूर्णांकel_dp->psr.transcoder);
		mask = EDP_PSR2_STATUS_STATE_MASK;
	पूर्ण अन्यथा अणु
		reg = EDP_PSR_STATUS(पूर्णांकel_dp->psr.transcoder);
		mask = EDP_PSR_STATUS_STATE_MASK;
	पूर्ण

	mutex_unlock(&पूर्णांकel_dp->psr.lock);

	err = पूर्णांकel_de_रुको_क्रम_clear(dev_priv, reg, mask, 50);
	अगर (err)
		drm_err(&dev_priv->drm,
			"Timed out waiting for PSR Idle for re-enable\n");

	/* After the unlocked रुको, verअगरy that PSR is still wanted! */
	mutex_lock(&पूर्णांकel_dp->psr.lock);
	वापस err == 0 && पूर्णांकel_dp->psr.enabled;
पूर्ण

अटल पूर्णांक पूर्णांकel_psr_fastset_क्रमce(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_connector *conn;
	पूर्णांक err = 0;

	state = drm_atomic_state_alloc(dev);
	अगर (!state)
		वापस -ENOMEM;

	drm_modeset_acquire_init(&ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE);
	state->acquire_ctx = &ctx;

retry:

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(conn, &conn_iter) अणु
		काष्ठा drm_connector_state *conn_state;
		काष्ठा drm_crtc_state *crtc_state;

		अगर (conn->connector_type != DRM_MODE_CONNECTOR_eDP)
			जारी;

		conn_state = drm_atomic_get_connector_state(state, conn);
		अगर (IS_ERR(conn_state)) अणु
			err = PTR_ERR(conn_state);
			अवरोध;
		पूर्ण

		अगर (!conn_state->crtc)
			जारी;

		crtc_state = drm_atomic_get_crtc_state(state, conn_state->crtc);
		अगर (IS_ERR(crtc_state)) अणु
			err = PTR_ERR(crtc_state);
			अवरोध;
		पूर्ण

		/* Mark mode as changed to trigger a pipe->update() */
		crtc_state->mode_changed = true;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (err == 0)
		err = drm_atomic_commit(state);

	अगर (err == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		err = drm_modeset_backoff(&ctx);
		अगर (!err)
			जाओ retry;
	पूर्ण

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
	drm_atomic_state_put(state);

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_psr_debug_set(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u64 val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	स्थिर u32 mode = val & I915_PSR_DEBUG_MODE_MASK;
	u32 old_mode;
	पूर्णांक ret;

	अगर (val & ~(I915_PSR_DEBUG_IRQ | I915_PSR_DEBUG_MODE_MASK) ||
	    mode > I915_PSR_DEBUG_ENABLE_SEL_FETCH) अणु
		drm_dbg_kms(&dev_priv->drm, "Invalid debug mask %llx\n", val);
		वापस -EINVAL;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&पूर्णांकel_dp->psr.lock);
	अगर (ret)
		वापस ret;

	old_mode = पूर्णांकel_dp->psr.debug & I915_PSR_DEBUG_MODE_MASK;
	पूर्णांकel_dp->psr.debug = val;

	/*
	 * Do it right away अगर it's alपढ़ोy enabled, otherwise it will be करोne
	 * when enabling the source.
	 */
	अगर (पूर्णांकel_dp->psr.enabled)
		psr_irq_control(पूर्णांकel_dp);

	mutex_unlock(&पूर्णांकel_dp->psr.lock);

	अगर (old_mode != mode)
		ret = पूर्णांकel_psr_fastset_क्रमce(dev_priv);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_psr_handle_irq(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_psr *psr = &पूर्णांकel_dp->psr;

	पूर्णांकel_psr_disable_locked(पूर्णांकel_dp);
	psr->sink_not_reliable = true;
	/* let's make sure that sink is awaken */
	drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_SET_POWER, DP_SET_POWER_D0);
पूर्ण

अटल व्योम पूर्णांकel_psr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp =
		container_of(work, typeof(*पूर्णांकel_dp), psr.work);

	mutex_lock(&पूर्णांकel_dp->psr.lock);

	अगर (!पूर्णांकel_dp->psr.enabled)
		जाओ unlock;

	अगर (READ_ONCE(पूर्णांकel_dp->psr.irq_aux_error))
		पूर्णांकel_psr_handle_irq(पूर्णांकel_dp);

	/*
	 * We have to make sure PSR is पढ़ोy क्रम re-enable
	 * otherwise it keeps disabled until next full enable/disable cycle.
	 * PSR might take some समय to get fully disabled
	 * and be पढ़ोy क्रम re-enable.
	 */
	अगर (!__psr_रुको_क्रम_idle_locked(पूर्णांकel_dp))
		जाओ unlock;

	/*
	 * The delayed work can race with an invalidate hence we need to
	 * recheck. Since psr_flush first clears this and then reschedules we
	 * won't ever miss a flush when bailing out here.
	 */
	अगर (पूर्णांकel_dp->psr.busy_frontbuffer_bits || पूर्णांकel_dp->psr.active)
		जाओ unlock;

	पूर्णांकel_psr_activate(पूर्णांकel_dp);
unlock:
	mutex_unlock(&पूर्णांकel_dp->psr.lock);
पूर्ण

/**
 * पूर्णांकel_psr_invalidate - Invalidade PSR
 * @dev_priv: i915 device
 * @frontbuffer_bits: frontbuffer plane tracking bits
 * @origin: which operation caused the invalidate
 *
 * Since the hardware frontbuffer tracking has gaps we need to पूर्णांकegrate
 * with the software frontbuffer tracking. This function माला_लो called every
 * समय frontbuffer rendering starts and a buffer माला_लो dirtied. PSR must be
 * disabled अगर the frontbuffer mask contains a buffer relevant to PSR.
 *
 * Dirty frontbuffers relevant to PSR are tracked in busy_frontbuffer_bits."
 */
व्योम पूर्णांकel_psr_invalidate(काष्ठा drm_i915_निजी *dev_priv,
			  अचिन्हित frontbuffer_bits, क्रमागत fb_op_origin origin)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	अगर (origin == ORIGIN_FLIP)
		वापस;

	क्रम_each_पूर्णांकel_encoder_with_psr(&dev_priv->drm, encoder) अणु
		अचिन्हित पूर्णांक pipe_frontbuffer_bits = frontbuffer_bits;
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		mutex_lock(&पूर्णांकel_dp->psr.lock);
		अगर (!पूर्णांकel_dp->psr.enabled) अणु
			mutex_unlock(&पूर्णांकel_dp->psr.lock);
			जारी;
		पूर्ण

		pipe_frontbuffer_bits &=
			INTEL_FRONTBUFFER_ALL_MASK(पूर्णांकel_dp->psr.pipe);
		पूर्णांकel_dp->psr.busy_frontbuffer_bits |= pipe_frontbuffer_bits;

		अगर (pipe_frontbuffer_bits)
			पूर्णांकel_psr_निकास(पूर्णांकel_dp);

		mutex_unlock(&पूर्णांकel_dp->psr.lock);
	पूर्ण
पूर्ण
/*
 * When we will be completely rely on PSR2 S/W tracking in future,
 * पूर्णांकel_psr_flush() will invalidate and flush the PSR क्रम ORIGIN_FLIP
 * event also thereक्रमe tgl_dc3co_flush() require to be changed
 * accordingly in future.
 */
अटल व्योम
tgl_dc3co_flush(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, अचिन्हित पूर्णांक frontbuffer_bits,
		क्रमागत fb_op_origin origin)
अणु
	mutex_lock(&पूर्णांकel_dp->psr.lock);

	अगर (!पूर्णांकel_dp->psr.dc3co_enabled)
		जाओ unlock;

	अगर (!पूर्णांकel_dp->psr.psr2_enabled || !पूर्णांकel_dp->psr.active)
		जाओ unlock;

	/*
	 * At every frontbuffer flush flip event modअगरied delay of delayed work,
	 * when delayed work schedules that means display has been idle.
	 */
	अगर (!(frontbuffer_bits &
	    INTEL_FRONTBUFFER_ALL_MASK(पूर्णांकel_dp->psr.pipe)))
		जाओ unlock;

	tgl_psr2_enable_dc3co(पूर्णांकel_dp);
	mod_delayed_work(प्रणाली_wq, &पूर्णांकel_dp->psr.dc3co_work,
			 पूर्णांकel_dp->psr.dc3co_निकास_delay);

unlock:
	mutex_unlock(&पूर्णांकel_dp->psr.lock);
पूर्ण

/**
 * पूर्णांकel_psr_flush - Flush PSR
 * @dev_priv: i915 device
 * @frontbuffer_bits: frontbuffer plane tracking bits
 * @origin: which operation caused the flush
 *
 * Since the hardware frontbuffer tracking has gaps we need to पूर्णांकegrate
 * with the software frontbuffer tracking. This function माला_लो called every
 * समय frontbuffer rendering has completed and flushed out to memory. PSR
 * can be enabled again अगर no other frontbuffer relevant to PSR is dirty.
 *
 * Dirty frontbuffers relevant to PSR are tracked in busy_frontbuffer_bits.
 */
व्योम पूर्णांकel_psr_flush(काष्ठा drm_i915_निजी *dev_priv,
		     अचिन्हित frontbuffer_bits, क्रमागत fb_op_origin origin)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	क्रम_each_पूर्णांकel_encoder_with_psr(&dev_priv->drm, encoder) अणु
		अचिन्हित पूर्णांक pipe_frontbuffer_bits = frontbuffer_bits;
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		अगर (origin == ORIGIN_FLIP) अणु
			tgl_dc3co_flush(पूर्णांकel_dp, frontbuffer_bits, origin);
			जारी;
		पूर्ण

		mutex_lock(&पूर्णांकel_dp->psr.lock);
		अगर (!पूर्णांकel_dp->psr.enabled) अणु
			mutex_unlock(&पूर्णांकel_dp->psr.lock);
			जारी;
		पूर्ण

		pipe_frontbuffer_bits &=
			INTEL_FRONTBUFFER_ALL_MASK(पूर्णांकel_dp->psr.pipe);
		पूर्णांकel_dp->psr.busy_frontbuffer_bits &= ~pipe_frontbuffer_bits;

		/* By definition flush = invalidate + flush */
		अगर (pipe_frontbuffer_bits)
			psr_क्रमce_hw_tracking_निकास(पूर्णांकel_dp);

		अगर (!पूर्णांकel_dp->psr.active && !पूर्णांकel_dp->psr.busy_frontbuffer_bits)
			schedule_work(&पूर्णांकel_dp->psr.work);
		mutex_unlock(&पूर्णांकel_dp->psr.lock);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_psr_init - Init basic PSR work and mutex.
 * @पूर्णांकel_dp: Intel DP
 *
 * This function is called after the initializing connector.
 * (the initializing of connector treats the handling of connector capabilities)
 * And it initializes basic PSR stuff क्रम each DP Encoder.
 */
व्योम पूर्णांकel_psr_init(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (!HAS_PSR(dev_priv))
		वापस;

	/*
	 * HSW spec explicitly says PSR is tied to port A.
	 * BDW+ platक्रमms have a instance of PSR रेजिस्टरs per transcoder but
	 * BDW, GEN9 and GEN11 are not validated by HW team in other transcoder
	 * than eDP one.
	 * For now it only supports one instance of PSR क्रम BDW, GEN9 and GEN11.
	 * So lets keep it hardcoded to PORT_A क्रम BDW, GEN9 and GEN11.
	 * But GEN12 supports a instance of PSR रेजिस्टरs per transcoder.
	 */
	अगर (DISPLAY_VER(dev_priv) < 12 && dig_port->base.port != PORT_A) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "PSR condition failed: Port not supported\n");
		वापस;
	पूर्ण

	पूर्णांकel_dp->psr.source_support = true;

	अगर (IS_HASWELL(dev_priv))
		/*
		 * HSW करोn't have PSR रेजिस्टरs on the same space as transcoder
		 * so set this to a value that when subtract to the रेजिस्टर
		 * in transcoder space results in the right offset क्रम HSW
		 */
		dev_priv->hsw_psr_mmio_adjust = _SRD_CTL_EDP - _HSW_EDP_PSR_BASE;

	अगर (dev_priv->params.enable_psr == -1)
		अगर (DISPLAY_VER(dev_priv) < 9 || !dev_priv->vbt.psr.enable)
			dev_priv->params.enable_psr = 0;

	/* Set link_standby x link_off शेषs */
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		/* HSW and BDW require workarounds that we करोn't implement. */
		पूर्णांकel_dp->psr.link_standby = false;
	अन्यथा अगर (DISPLAY_VER(dev_priv) < 12)
		/* For new platक्रमms up to TGL let's respect VBT back again */
		पूर्णांकel_dp->psr.link_standby = dev_priv->vbt.psr.full_link;

	INIT_WORK(&पूर्णांकel_dp->psr.work, पूर्णांकel_psr_work);
	INIT_DELAYED_WORK(&पूर्णांकel_dp->psr.dc3co_work, tgl_dc3co_disable_work);
	mutex_init(&पूर्णांकel_dp->psr.lock);
पूर्ण

अटल पूर्णांक psr_get_status_and_error_status(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					   u8 *status, u8 *error_status)
अणु
	काष्ठा drm_dp_aux *aux = &पूर्णांकel_dp->aux;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PSR_STATUS, status);
	अगर (ret != 1)
		वापस ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PSR_ERROR_STATUS, error_status);
	अगर (ret != 1)
		वापस ret;

	*status = *status & DP_PSR_SINK_STATE_MASK;

	वापस 0;
पूर्ण

अटल व्योम psr_alpm_check(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा drm_dp_aux *aux = &पूर्णांकel_dp->aux;
	काष्ठा पूर्णांकel_psr *psr = &पूर्णांकel_dp->psr;
	u8 val;
	पूर्णांक r;

	अगर (!psr->psr2_enabled)
		वापस;

	r = drm_dp_dpcd_पढ़ोb(aux, DP_RECEIVER_ALPM_STATUS, &val);
	अगर (r != 1) अणु
		drm_err(&dev_priv->drm, "Error reading ALPM status\n");
		वापस;
	पूर्ण

	अगर (val & DP_ALPM_LOCK_TIMEOUT_ERROR) अणु
		पूर्णांकel_psr_disable_locked(पूर्णांकel_dp);
		psr->sink_not_reliable = true;
		drm_dbg_kms(&dev_priv->drm,
			    "ALPM lock timeout error, disabling PSR\n");

		/* Clearing error */
		drm_dp_dpcd_ग_लिखोb(aux, DP_RECEIVER_ALPM_STATUS, val);
	पूर्ण
पूर्ण

अटल व्योम psr_capability_changed_check(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_psr *psr = &पूर्णांकel_dp->psr;
	u8 val;
	पूर्णांक r;

	r = drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_PSR_ESI, &val);
	अगर (r != 1) अणु
		drm_err(&dev_priv->drm, "Error reading DP_PSR_ESI\n");
		वापस;
	पूर्ण

	अगर (val & DP_PSR_CAPS_CHANGE) अणु
		पूर्णांकel_psr_disable_locked(पूर्णांकel_dp);
		psr->sink_not_reliable = true;
		drm_dbg_kms(&dev_priv->drm,
			    "Sink PSR capability changed, disabling PSR\n");

		/* Clearing it */
		drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_PSR_ESI, val);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_psr_लघु_pulse(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_psr *psr = &पूर्णांकel_dp->psr;
	u8 status, error_status;
	स्थिर u8 errors = DP_PSR_RFB_STORAGE_ERROR |
			  DP_PSR_VSC_SDP_UNCORRECTABLE_ERROR |
			  DP_PSR_LINK_CRC_ERROR;

	अगर (!CAN_PSR(पूर्णांकel_dp))
		वापस;

	mutex_lock(&psr->lock);

	अगर (!psr->enabled)
		जाओ निकास;

	अगर (psr_get_status_and_error_status(पूर्णांकel_dp, &status, &error_status)) अणु
		drm_err(&dev_priv->drm,
			"Error reading PSR status or error status\n");
		जाओ निकास;
	पूर्ण

	अगर (status == DP_PSR_SINK_INTERNAL_ERROR || (error_status & errors)) अणु
		पूर्णांकel_psr_disable_locked(पूर्णांकel_dp);
		psr->sink_not_reliable = true;
	पूर्ण

	अगर (status == DP_PSR_SINK_INTERNAL_ERROR && !error_status)
		drm_dbg_kms(&dev_priv->drm,
			    "PSR sink internal error, disabling PSR\n");
	अगर (error_status & DP_PSR_RFB_STORAGE_ERROR)
		drm_dbg_kms(&dev_priv->drm,
			    "PSR RFB storage error, disabling PSR\n");
	अगर (error_status & DP_PSR_VSC_SDP_UNCORRECTABLE_ERROR)
		drm_dbg_kms(&dev_priv->drm,
			    "PSR VSC SDP uncorrectable error, disabling PSR\n");
	अगर (error_status & DP_PSR_LINK_CRC_ERROR)
		drm_dbg_kms(&dev_priv->drm,
			    "PSR Link CRC error, disabling PSR\n");

	अगर (error_status & ~errors)
		drm_err(&dev_priv->drm,
			"PSR_ERROR_STATUS unhandled errors %x\n",
			error_status & ~errors);
	/* clear status रेजिस्टर */
	drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_PSR_ERROR_STATUS, error_status);

	psr_alpm_check(पूर्णांकel_dp);
	psr_capability_changed_check(पूर्णांकel_dp);

निकास:
	mutex_unlock(&psr->lock);
पूर्ण

bool पूर्णांकel_psr_enabled(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	bool ret;

	अगर (!CAN_PSR(पूर्णांकel_dp))
		वापस false;

	mutex_lock(&पूर्णांकel_dp->psr.lock);
	ret = पूर्णांकel_dp->psr.enabled;
	mutex_unlock(&पूर्णांकel_dp->psr.lock);

	वापस ret;
पूर्ण
