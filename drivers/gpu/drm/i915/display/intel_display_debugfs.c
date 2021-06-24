<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "i915_debugfs.h"
#समावेश "intel_csr.h"
#समावेश "intel_display_debugfs.h"
#समावेश "intel_display_power.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp.h"
#समावेश "intel_fbc.h"
#समावेश "intel_hdcp.h"
#समावेश "intel_hdmi.h"
#समावेश "intel_pm.h"
#समावेश "intel_psr.h"
#समावेश "intel_sideband.h"
#समावेश "intel_sprite.h"

अटल अंतरभूत काष्ठा drm_i915_निजी *node_to_i915(काष्ठा drm_info_node *node)
अणु
	वापस to_i915(node->minor->dev);
पूर्ण

अटल पूर्णांक i915_frontbuffer_tracking(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);

	seq_म_लिखो(m, "FB tracking busy bits: 0x%08x\n",
		   dev_priv->fb_tracking.busy_bits);

	seq_म_लिखो(m, "FB tracking flip bits: 0x%08x\n",
		   dev_priv->fb_tracking.flip_bits);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_fbc_status(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	पूर्णांकel_wakeref_t wakeref;

	अगर (!HAS_FBC(dev_priv))
		वापस -ENODEV;

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);
	mutex_lock(&fbc->lock);

	अगर (पूर्णांकel_fbc_is_active(dev_priv))
		seq_माला_दो(m, "FBC enabled\n");
	अन्यथा
		seq_म_लिखो(m, "FBC disabled: %s\n", fbc->no_fbc_reason);

	अगर (पूर्णांकel_fbc_is_active(dev_priv)) अणु
		u32 mask;

		अगर (DISPLAY_VER(dev_priv) >= 8)
			mask = पूर्णांकel_de_पढ़ो(dev_priv, IVB_FBC_STATUS2) & BDW_FBC_COMP_SEG_MASK;
		अन्यथा अगर (DISPLAY_VER(dev_priv) >= 7)
			mask = पूर्णांकel_de_पढ़ो(dev_priv, IVB_FBC_STATUS2) & IVB_FBC_COMP_SEG_MASK;
		अन्यथा अगर (DISPLAY_VER(dev_priv) >= 5)
			mask = पूर्णांकel_de_पढ़ो(dev_priv, ILK_DPFC_STATUS) & ILK_DPFC_COMP_SEG_MASK;
		अन्यथा अगर (IS_G4X(dev_priv))
			mask = पूर्णांकel_de_पढ़ो(dev_priv, DPFC_STATUS) & DPFC_COMP_SEG_MASK;
		अन्यथा
			mask = पूर्णांकel_de_पढ़ो(dev_priv, FBC_STATUS) &
				(FBC_STAT_COMPRESSING | FBC_STAT_COMPRESSED);

		seq_म_लिखो(m, "Compressing: %s\n", yesno(mask));
	पूर्ण

	mutex_unlock(&fbc->lock);
	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_fbc_false_color_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = data;

	अगर (DISPLAY_VER(dev_priv) < 7 || !HAS_FBC(dev_priv))
		वापस -ENODEV;

	*val = dev_priv->fbc.false_color;

	वापस 0;
पूर्ण

अटल पूर्णांक i915_fbc_false_color_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = data;
	u32 reg;

	अगर (DISPLAY_VER(dev_priv) < 7 || !HAS_FBC(dev_priv))
		वापस -ENODEV;

	mutex_lock(&dev_priv->fbc.lock);

	reg = पूर्णांकel_de_पढ़ो(dev_priv, ILK_DPFC_CONTROL);
	dev_priv->fbc.false_color = val;

	पूर्णांकel_de_ग_लिखो(dev_priv, ILK_DPFC_CONTROL,
		       val ? (reg | FBC_CTL_FALSE_COLOR) : (reg & ~FBC_CTL_FALSE_COLOR));

	mutex_unlock(&dev_priv->fbc.lock);
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(i915_fbc_false_color_fops,
			i915_fbc_false_color_get, i915_fbc_false_color_set,
			"%llu\n");

अटल पूर्णांक i915_ips_status(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	पूर्णांकel_wakeref_t wakeref;

	अगर (!HAS_IPS(dev_priv))
		वापस -ENODEV;

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	seq_म_लिखो(m, "Enabled by kernel parameter: %s\n",
		   yesno(dev_priv->params.enable_ips));

	अगर (DISPLAY_VER(dev_priv) >= 8) अणु
		seq_माला_दो(m, "Currently: unknown\n");
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकel_de_पढ़ो(dev_priv, IPS_CTL) & IPS_ENABLE)
			seq_माला_दो(m, "Currently: enabled\n");
		अन्यथा
			seq_माला_दो(m, "Currently: disabled\n");
	पूर्ण

	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_sr_status(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	पूर्णांकel_wakeref_t wakeref;
	bool sr_enabled = false;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_INIT);

	अगर (DISPLAY_VER(dev_priv) >= 9)
		/* no global SR status; inspect per-plane WM */;
	अन्यथा अगर (HAS_PCH_SPLIT(dev_priv))
		sr_enabled = पूर्णांकel_de_पढ़ो(dev_priv, WM1_LP_ILK) & WM1_LP_SR_EN;
	अन्यथा अगर (IS_I965GM(dev_priv) || IS_G4X(dev_priv) ||
		 IS_I945G(dev_priv) || IS_I945GM(dev_priv))
		sr_enabled = पूर्णांकel_de_पढ़ो(dev_priv, FW_BLC_SELF) & FW_BLC_SELF_EN;
	अन्यथा अगर (IS_I915GM(dev_priv))
		sr_enabled = पूर्णांकel_de_पढ़ो(dev_priv, INSTPM) & INSTPM_SELF_EN;
	अन्यथा अगर (IS_PINEVIEW(dev_priv))
		sr_enabled = पूर्णांकel_de_पढ़ो(dev_priv, DSPFW3) & PINEVIEW_SELF_REFRESH_EN;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		sr_enabled = पूर्णांकel_de_पढ़ो(dev_priv, FW_BLC_SELF_VLV) & FW_CSPWRDWNEN;

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_INIT, wakeref);

	seq_म_लिखो(m, "self-refresh: %s\n", enableddisabled(sr_enabled));

	वापस 0;
पूर्ण

अटल पूर्णांक i915_opregion(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &node_to_i915(m->निजी)->opregion;

	अगर (opregion->header)
		seq_ग_लिखो(m, opregion->header, OPREGION_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_vbt(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा पूर्णांकel_opregion *opregion = &node_to_i915(m->निजी)->opregion;

	अगर (opregion->vbt)
		seq_ग_लिखो(m, opregion->vbt, opregion->vbt_size);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_gem_framebuffer_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_framebuffer *fbdev_fb = शून्य;
	काष्ठा drm_framebuffer *drm_fb;

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	अगर (dev_priv->fbdev && dev_priv->fbdev->helper.fb) अणु
		fbdev_fb = to_पूर्णांकel_framebuffer(dev_priv->fbdev->helper.fb);

		seq_म_लिखो(m, "fbcon size: %d x %d, depth %d, %d bpp, modifier 0x%llx, refcount %d, obj ",
			   fbdev_fb->base.width,
			   fbdev_fb->base.height,
			   fbdev_fb->base.क्रमmat->depth,
			   fbdev_fb->base.क्रमmat->cpp[0] * 8,
			   fbdev_fb->base.modअगरier,
			   drm_framebuffer_पढ़ो_refcount(&fbdev_fb->base));
		i915_debugfs_describe_obj(m, पूर्णांकel_fb_obj(&fbdev_fb->base));
		seq_अ_दो(m, '\n');
	पूर्ण
#पूर्ण_अगर

	mutex_lock(&dev->mode_config.fb_lock);
	drm_क्रम_each_fb(drm_fb, dev) अणु
		काष्ठा पूर्णांकel_framebuffer *fb = to_पूर्णांकel_framebuffer(drm_fb);
		अगर (fb == fbdev_fb)
			जारी;

		seq_म_लिखो(m, "user size: %d x %d, depth %d, %d bpp, modifier 0x%llx, refcount %d, obj ",
			   fb->base.width,
			   fb->base.height,
			   fb->base.क्रमmat->depth,
			   fb->base.क्रमmat->cpp[0] * 8,
			   fb->base.modअगरier,
			   drm_framebuffer_पढ़ो_refcount(&fb->base));
		i915_debugfs_describe_obj(m, पूर्णांकel_fb_obj(&fb->base));
		seq_अ_दो(m, '\n');
	पूर्ण
	mutex_unlock(&dev->mode_config.fb_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_psr_sink_status_show(काष्ठा seq_file *m, व्योम *data)
अणु
	u8 val;
	अटल स्थिर अक्षर * स्थिर sink_status[] = अणु
		"inactive",
		"transition to active, capture and display",
		"active, display from RFB",
		"active, capture and display on sink device timings",
		"transition to inactive, capture and display, timing re-sync",
		"reserved",
		"reserved",
		"sink internal error",
	पूर्ण;
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp =
		पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));
	पूर्णांक ret;

	अगर (!CAN_PSR(पूर्णांकel_dp)) अणु
		seq_माला_दो(m, "PSR Unsupported\n");
		वापस -ENODEV;
	पूर्ण

	अगर (connector->status != connector_status_connected)
		वापस -ENODEV;

	ret = drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_PSR_STATUS, &val);

	अगर (ret == 1) अणु
		स्थिर अक्षर *str = "unknown";

		val &= DP_PSR_SINK_STATE_MASK;
		अगर (val < ARRAY_SIZE(sink_status))
			str = sink_status[val];
		seq_म_लिखो(m, "Sink PSR status: 0x%x [%s]\n", val, str);
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(i915_psr_sink_status);

अटल व्योम
psr_source_status(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, काष्ठा seq_file *m)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	स्थिर अक्षर *status = "unknown";
	u32 val, status_val;

	अगर (पूर्णांकel_dp->psr.psr2_enabled) अणु
		अटल स्थिर अक्षर * स्थिर live_status[] = अणु
			"IDLE",
			"CAPTURE",
			"CAPTURE_FS",
			"SLEEP",
			"BUFON_FW",
			"ML_UP",
			"SU_STANDBY",
			"FAST_SLEEP",
			"DEEP_SLEEP",
			"BUF_ON",
			"TG_ON"
		पूर्ण;
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    EDP_PSR2_STATUS(पूर्णांकel_dp->psr.transcoder));
		status_val = (val & EDP_PSR2_STATUS_STATE_MASK) >>
			      EDP_PSR2_STATUS_STATE_SHIFT;
		अगर (status_val < ARRAY_SIZE(live_status))
			status = live_status[status_val];
	पूर्ण अन्यथा अणु
		अटल स्थिर अक्षर * स्थिर live_status[] = अणु
			"IDLE",
			"SRDONACK",
			"SRDENT",
			"BUFOFF",
			"BUFON",
			"AUXACK",
			"SRDOFFACK",
			"SRDENT_ON",
		पूर्ण;
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    EDP_PSR_STATUS(पूर्णांकel_dp->psr.transcoder));
		status_val = (val & EDP_PSR_STATUS_STATE_MASK) >>
			      EDP_PSR_STATUS_STATE_SHIFT;
		अगर (status_val < ARRAY_SIZE(live_status))
			status = live_status[status_val];
	पूर्ण

	seq_म_लिखो(m, "Source PSR status: %s [0x%08x]\n", status, val);
पूर्ण

अटल पूर्णांक पूर्णांकel_psr_status(काष्ठा seq_file *m, काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_psr *psr = &पूर्णांकel_dp->psr;
	पूर्णांकel_wakeref_t wakeref;
	स्थिर अक्षर *status;
	bool enabled;
	u32 val;

	seq_म_लिखो(m, "Sink support: %s", yesno(psr->sink_support));
	अगर (psr->sink_support)
		seq_म_लिखो(m, " [0x%02x]", पूर्णांकel_dp->psr_dpcd[0]);
	seq_माला_दो(m, "\n");

	अगर (!psr->sink_support)
		वापस 0;

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);
	mutex_lock(&psr->lock);

	अगर (psr->enabled)
		status = psr->psr2_enabled ? "PSR2 enabled" : "PSR1 enabled";
	अन्यथा
		status = "disabled";
	seq_म_लिखो(m, "PSR mode: %s\n", status);

	अगर (!psr->enabled) अणु
		seq_म_लिखो(m, "PSR sink not reliable: %s\n",
			   yesno(psr->sink_not_reliable));

		जाओ unlock;
	पूर्ण

	अगर (psr->psr2_enabled) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    EDP_PSR2_CTL(पूर्णांकel_dp->psr.transcoder));
		enabled = val & EDP_PSR2_ENABLE;
	पूर्ण अन्यथा अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    EDP_PSR_CTL(पूर्णांकel_dp->psr.transcoder));
		enabled = val & EDP_PSR_ENABLE;
	पूर्ण
	seq_म_लिखो(m, "Source PSR ctl: %s [0x%08x]\n",
		   enableddisabled(enabled), val);
	psr_source_status(पूर्णांकel_dp, m);
	seq_म_लिखो(m, "Busy frontbuffer bits: 0x%08x\n",
		   psr->busy_frontbuffer_bits);

	/*
	 * SKL+ Perf counter is reset to 0 everyसमय DC state is entered
	 */
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    EDP_PSR_PERF_CNT(पूर्णांकel_dp->psr.transcoder));
		val &= EDP_PSR_PERF_CNT_MASK;
		seq_म_लिखो(m, "Performance counter: %u\n", val);
	पूर्ण

	अगर (psr->debug & I915_PSR_DEBUG_IRQ) अणु
		seq_म_लिखो(m, "Last attempted entry at: %lld\n",
			   psr->last_entry_attempt);
		seq_म_लिखो(m, "Last exit at: %lld\n", psr->last_निकास);
	पूर्ण

	अगर (psr->psr2_enabled) अणु
		u32 su_frames_val[3];
		पूर्णांक frame;

		/*
		 * Reading all 3 रेजिस्टरs beक्रमe hand to minimize crossing a
		 * frame boundary between रेजिस्टर पढ़ोs
		 */
		क्रम (frame = 0; frame < PSR2_SU_STATUS_FRAMES; frame += 3) अणु
			val = पूर्णांकel_de_पढ़ो(dev_priv,
					    PSR2_SU_STATUS(पूर्णांकel_dp->psr.transcoder, frame));
			su_frames_val[frame / 3] = val;
		पूर्ण

		seq_माला_दो(m, "Frame:\tPSR2 SU blocks:\n");

		क्रम (frame = 0; frame < PSR2_SU_STATUS_FRAMES; frame++) अणु
			u32 su_blocks;

			su_blocks = su_frames_val[frame / 3] &
				    PSR2_SU_STATUS_MASK(frame);
			su_blocks = su_blocks >> PSR2_SU_STATUS_SHIFT(frame);
			seq_म_लिखो(m, "%d\t%d\n", frame, su_blocks);
		पूर्ण

		seq_म_लिखो(m, "PSR2 selective fetch: %s\n",
			   enableddisabled(psr->psr2_sel_fetch_enabled));
	पूर्ण

unlock:
	mutex_unlock(&psr->lock);
	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_edp_psr_status(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = शून्य;
	काष्ठा पूर्णांकel_encoder *encoder;

	अगर (!HAS_PSR(dev_priv))
		वापस -ENODEV;

	/* Find the first EDP which supports PSR */
	क्रम_each_पूर्णांकel_encoder_with_psr(&dev_priv->drm, encoder) अणु
		पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
		अवरोध;
	पूर्ण

	अगर (!पूर्णांकel_dp)
		वापस -ENODEV;

	वापस पूर्णांकel_psr_status(m, पूर्णांकel_dp);
पूर्ण

अटल पूर्णांक
i915_edp_psr_debug_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = data;
	काष्ठा पूर्णांकel_encoder *encoder;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक ret = -ENODEV;

	अगर (!HAS_PSR(dev_priv))
		वापस ret;

	क्रम_each_पूर्णांकel_encoder_with_psr(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		drm_dbg_kms(&dev_priv->drm, "Setting PSR debug to %llx\n", val);

		wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

		// TODO: split to each transcoder's PSR debug state
		ret = पूर्णांकel_psr_debug_set(पूर्णांकel_dp, val);

		पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
i915_edp_psr_debug_get(व्योम *data, u64 *val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = data;
	काष्ठा पूर्णांकel_encoder *encoder;

	अगर (!HAS_PSR(dev_priv))
		वापस -ENODEV;

	क्रम_each_पूर्णांकel_encoder_with_psr(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		// TODO: split to each transcoder's PSR debug state
		*val = READ_ONCE(पूर्णांकel_dp->psr.debug);
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(i915_edp_psr_debug_fops,
			i915_edp_psr_debug_get, i915_edp_psr_debug_set,
			"%llu\n");

अटल पूर्णांक i915_घातer_करोमुख्य_info(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	पूर्णांक i;

	mutex_lock(&घातer_करोमुख्यs->lock);

	seq_म_लिखो(m, "%-25s %s\n", "Power well/domain", "Use count");
	क्रम (i = 0; i < घातer_करोमुख्यs->घातer_well_count; i++) अणु
		काष्ठा i915_घातer_well *घातer_well;
		क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;

		घातer_well = &घातer_करोमुख्यs->घातer_wells[i];
		seq_म_लिखो(m, "%-25s %d\n", घातer_well->desc->name,
			   घातer_well->count);

		क्रम_each_घातer_करोमुख्य(घातer_करोमुख्य, घातer_well->desc->करोमुख्यs)
			seq_म_लिखो(m, "  %-23s %d\n",
				 पूर्णांकel_display_घातer_करोमुख्य_str(घातer_करोमुख्य),
				 घातer_करोमुख्यs->करोमुख्य_use_count[घातer_करोमुख्य]);
	पूर्ण

	mutex_unlock(&घातer_करोमुख्यs->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_dmc_info(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा पूर्णांकel_csr *csr;
	i915_reg_t dc5_reg, dc6_reg = अणुपूर्ण;

	अगर (!HAS_CSR(dev_priv))
		वापस -ENODEV;

	csr = &dev_priv->csr;

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	seq_म_लिखो(m, "fw loaded: %s\n", yesno(csr->dmc_payload != शून्य));
	seq_म_लिखो(m, "path: %s\n", csr->fw_path);

	अगर (!csr->dmc_payload)
		जाओ out;

	seq_म_लिखो(m, "version: %d.%d\n", CSR_VERSION_MAJOR(csr->version),
		   CSR_VERSION_MINOR(csr->version));

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		अगर (IS_DGFX(dev_priv)) अणु
			dc5_reg = DG1_DMC_DEBUG_DC5_COUNT;
		पूर्ण अन्यथा अणु
			dc5_reg = TGL_DMC_DEBUG_DC5_COUNT;
			dc6_reg = TGL_DMC_DEBUG_DC6_COUNT;
		पूर्ण

		/*
		 * NOTE: DMC_DEBUG3 is a general purpose reg.
		 * According to B.Specs:49196 DMC f/w reuses DC5/6 counter
		 * reg क्रम DC3CO debugging and validation,
		 * but TGL DMC f/w is using DMC_DEBUG3 reg क्रम DC3CO counter.
		 */
		seq_म_लिखो(m, "DC3CO count: %d\n",
			   पूर्णांकel_de_पढ़ो(dev_priv, DMC_DEBUG3));
	पूर्ण अन्यथा अणु
		dc5_reg = IS_BROXTON(dev_priv) ? BXT_CSR_DC3_DC5_COUNT :
						 SKL_CSR_DC3_DC5_COUNT;
		अगर (!IS_GEN9_LP(dev_priv))
			dc6_reg = SKL_CSR_DC5_DC6_COUNT;
	पूर्ण

	seq_म_लिखो(m, "DC3 -> DC5 count: %d\n",
		   पूर्णांकel_de_पढ़ो(dev_priv, dc5_reg));
	अगर (dc6_reg.reg)
		seq_म_लिखो(m, "DC5 -> DC6 count: %d\n",
			   पूर्णांकel_de_पढ़ो(dev_priv, dc6_reg));

out:
	seq_म_लिखो(m, "program base: 0x%08x\n",
		   पूर्णांकel_de_पढ़ो(dev_priv, CSR_PROGRAM(0)));
	seq_म_लिखो(m, "ssp base: 0x%08x\n",
		   पूर्णांकel_de_पढ़ो(dev_priv, CSR_SSP_BASE));
	seq_म_लिखो(m, "htp: 0x%08x\n", पूर्णांकel_de_पढ़ो(dev_priv, CSR_HTP_SKL));

	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_seq_prपूर्णांक_mode(काष्ठा seq_file *m, पूर्णांक tअसल,
				 स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tअसल; i++)
		seq_अ_दो(m, '\t');

	seq_म_लिखो(m, DRM_MODE_FMT "\n", DRM_MODE_ARG(mode));
पूर्ण

अटल व्योम पूर्णांकel_encoder_info(काष्ठा seq_file *m,
			       काष्ठा पूर्णांकel_crtc *crtc,
			       काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_connector *connector;

	seq_म_लिखो(m, "\t[ENCODER:%d:%s]: connectors:\n",
		   encoder->base.base.id, encoder->base.name);

	drm_connector_list_iter_begin(&dev_priv->drm, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		स्थिर काष्ठा drm_connector_state *conn_state =
			connector->state;

		अगर (conn_state->best_encoder != &encoder->base)
			जारी;

		seq_म_लिखो(m, "\t\t[CONNECTOR:%d:%s]\n",
			   connector->base.id, connector->name);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
पूर्ण

अटल व्योम पूर्णांकel_panel_info(काष्ठा seq_file *m, काष्ठा पूर्णांकel_panel *panel)
अणु
	स्थिर काष्ठा drm_display_mode *mode = panel->fixed_mode;

	seq_म_लिखो(m, "\tfixed mode: " DRM_MODE_FMT "\n", DRM_MODE_ARG(mode));
पूर्ण

अटल व्योम पूर्णांकel_hdcp_info(काष्ठा seq_file *m,
			    काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	bool hdcp_cap, hdcp2_cap;

	अगर (!पूर्णांकel_connector->hdcp.shim) अणु
		seq_माला_दो(m, "No Connector Support");
		जाओ out;
	पूर्ण

	hdcp_cap = पूर्णांकel_hdcp_capable(पूर्णांकel_connector);
	hdcp2_cap = पूर्णांकel_hdcp2_capable(पूर्णांकel_connector);

	अगर (hdcp_cap)
		seq_माला_दो(m, "HDCP1.4 ");
	अगर (hdcp2_cap)
		seq_माला_दो(m, "HDCP2.2 ");

	अगर (!hdcp_cap && !hdcp2_cap)
		seq_माला_दो(m, "None");

out:
	seq_माला_दो(m, "\n");
पूर्ण

अटल व्योम पूर्णांकel_dp_info(काष्ठा seq_file *m,
			  काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = पूर्णांकel_attached_encoder(पूर्णांकel_connector);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(पूर्णांकel_encoder);
	स्थिर काष्ठा drm_property_blob *edid = पूर्णांकel_connector->base.edid_blob_ptr;

	seq_म_लिखो(m, "\tDPCD rev: %x\n", पूर्णांकel_dp->dpcd[DP_DPCD_REV]);
	seq_म_लिखो(m, "\taudio support: %s\n", yesno(पूर्णांकel_dp->has_audio));
	अगर (पूर्णांकel_connector->base.connector_type == DRM_MODE_CONNECTOR_eDP)
		पूर्णांकel_panel_info(m, &पूर्णांकel_connector->panel);

	drm_dp_करोwnstream_debug(m, पूर्णांकel_dp->dpcd, पूर्णांकel_dp->करोwnstream_ports,
				edid ? edid->data : शून्य, &पूर्णांकel_dp->aux);
पूर्ण

अटल व्योम पूर्णांकel_dp_mst_info(काष्ठा seq_file *m,
			      काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	bool has_audio = पूर्णांकel_connector->port->has_audio;

	seq_म_लिखो(m, "\taudio support: %s\n", yesno(has_audio));
पूर्ण

अटल व्योम पूर्णांकel_hdmi_info(काष्ठा seq_file *m,
			    काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = पूर्णांकel_attached_encoder(पूर्णांकel_connector);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(पूर्णांकel_encoder);

	seq_म_लिखो(m, "\taudio support: %s\n", yesno(पूर्णांकel_hdmi->has_audio));
पूर्ण

अटल व्योम पूर्णांकel_lvds_info(काष्ठा seq_file *m,
			    काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	पूर्णांकel_panel_info(m, &पूर्णांकel_connector->panel);
पूर्ण

अटल व्योम पूर्णांकel_connector_info(काष्ठा seq_file *m,
				 काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	स्थिर काष्ठा drm_connector_state *conn_state = connector->state;
	काष्ठा पूर्णांकel_encoder *encoder =
		to_पूर्णांकel_encoder(conn_state->best_encoder);
	स्थिर काष्ठा drm_display_mode *mode;

	seq_म_लिखो(m, "[CONNECTOR:%d:%s]: status: %s\n",
		   connector->base.id, connector->name,
		   drm_get_connector_status_name(connector->status));

	अगर (connector->status == connector_status_disconnected)
		वापस;

	seq_म_लिखो(m, "\tphysical dimensions: %dx%dmm\n",
		   connector->display_info.width_mm,
		   connector->display_info.height_mm);
	seq_म_लिखो(m, "\tsubpixel order: %s\n",
		   drm_get_subpixel_order_name(connector->display_info.subpixel_order));
	seq_म_लिखो(m, "\tCEA rev: %d\n", connector->display_info.cea_rev);

	अगर (!encoder)
		वापस;

	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_DisplayPort:
	हाल DRM_MODE_CONNECTOR_eDP:
		अगर (encoder->type == INTEL_OUTPUT_DP_MST)
			पूर्णांकel_dp_mst_info(m, पूर्णांकel_connector);
		अन्यथा
			पूर्णांकel_dp_info(m, पूर्णांकel_connector);
		अवरोध;
	हाल DRM_MODE_CONNECTOR_LVDS:
		अगर (encoder->type == INTEL_OUTPUT_LVDS)
			पूर्णांकel_lvds_info(m, पूर्णांकel_connector);
		अवरोध;
	हाल DRM_MODE_CONNECTOR_HDMIA:
		अगर (encoder->type == INTEL_OUTPUT_HDMI ||
		    encoder->type == INTEL_OUTPUT_DDI)
			पूर्णांकel_hdmi_info(m, पूर्णांकel_connector);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	seq_माला_दो(m, "\tHDCP version: ");
	पूर्णांकel_hdcp_info(m, पूर्णांकel_connector);

	seq_म_लिखो(m, "\tmodes:\n");
	list_क्रम_each_entry(mode, &connector->modes, head)
		पूर्णांकel_seq_prपूर्णांक_mode(m, 2, mode);
पूर्ण

अटल स्थिर अक्षर *plane_type(क्रमागत drm_plane_type type)
अणु
	चयन (type) अणु
	हाल DRM_PLANE_TYPE_OVERLAY:
		वापस "OVL";
	हाल DRM_PLANE_TYPE_PRIMARY:
		वापस "PRI";
	हाल DRM_PLANE_TYPE_CURSOR:
		वापस "CUR";
	/*
	 * Deliberately omitting शेष: to generate compiler warnings
	 * when a new drm_plane_type माला_लो added.
	 */
	पूर्ण

	वापस "unknown";
पूर्ण

अटल व्योम plane_rotation(अक्षर *buf, माप_प्रकार bufsize, अचिन्हित पूर्णांक rotation)
अणु
	/*
	 * According to करोc only one DRM_MODE_ROTATE_ is allowed but this
	 * will prपूर्णांक them all to visualize अगर the values are misused
	 */
	snम_लिखो(buf, bufsize,
		 "%s%s%s%s%s%s(0x%08x)",
		 (rotation & DRM_MODE_ROTATE_0) ? "0 " : "",
		 (rotation & DRM_MODE_ROTATE_90) ? "90 " : "",
		 (rotation & DRM_MODE_ROTATE_180) ? "180 " : "",
		 (rotation & DRM_MODE_ROTATE_270) ? "270 " : "",
		 (rotation & DRM_MODE_REFLECT_X) ? "FLIPX " : "",
		 (rotation & DRM_MODE_REFLECT_Y) ? "FLIPY " : "",
		 rotation);
पूर्ण

अटल स्थिर अक्षर *plane_visibility(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अगर (plane_state->uapi.visible)
		वापस "visible";

	अगर (plane_state->planar_slave)
		वापस "planar-slave";

	वापस "hidden";
पूर्ण

अटल व्योम पूर्णांकel_plane_uapi_info(काष्ठा seq_file *m, काष्ठा पूर्णांकel_plane *plane)
अणु
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
		to_पूर्णांकel_plane_state(plane->base.state);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->uapi.fb;
	काष्ठा drm_rect src, dst;
	अक्षर rot_str[48];

	src = drm_plane_state_src(&plane_state->uapi);
	dst = drm_plane_state_dest(&plane_state->uapi);

	plane_rotation(rot_str, माप(rot_str),
		       plane_state->uapi.rotation);

	seq_माला_दो(m, "\t\tuapi: [FB:");
	अगर (fb)
		seq_म_लिखो(m, "%d] %p4cc,0x%llx,%dx%d", fb->base.id,
			   &fb->क्रमmat->क्रमmat, fb->modअगरier, fb->width,
			   fb->height);
	अन्यथा
		seq_माला_दो(m, "0] n/a,0x0,0x0,");
	seq_म_लिखो(m, ", visible=%s, src=" DRM_RECT_FP_FMT ", dst=" DRM_RECT_FMT
		   ", rotation=%s\n", plane_visibility(plane_state),
		   DRM_RECT_FP_ARG(&src), DRM_RECT_ARG(&dst), rot_str);

	अगर (plane_state->planar_linked_plane)
		seq_म_लिखो(m, "\t\tplanar: Linked to [PLANE:%d:%s] as a %s\n",
			   plane_state->planar_linked_plane->base.base.id, plane_state->planar_linked_plane->base.name,
			   plane_state->planar_slave ? "slave" : "master");
पूर्ण

अटल व्योम पूर्णांकel_plane_hw_info(काष्ठा seq_file *m, काष्ठा पूर्णांकel_plane *plane)
अणु
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
		to_पूर्णांकel_plane_state(plane->base.state);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अक्षर rot_str[48];

	अगर (!fb)
		वापस;

	plane_rotation(rot_str, माप(rot_str),
		       plane_state->hw.rotation);

	seq_म_लिखो(m, "\t\thw: [FB:%d] %p4cc,0x%llx,%dx%d, visible=%s, src="
		   DRM_RECT_FP_FMT ", dst=" DRM_RECT_FMT ", rotation=%s\n",
		   fb->base.id, &fb->क्रमmat->क्रमmat,
		   fb->modअगरier, fb->width, fb->height,
		   yesno(plane_state->uapi.visible),
		   DRM_RECT_FP_ARG(&plane_state->uapi.src),
		   DRM_RECT_ARG(&plane_state->uapi.dst),
		   rot_str);
पूर्ण

अटल व्योम पूर्णांकel_plane_info(काष्ठा seq_file *m, काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा पूर्णांकel_plane *plane;

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
		seq_म_लिखो(m, "\t[PLANE:%d:%s]: type=%s\n",
			   plane->base.base.id, plane->base.name,
			   plane_type(plane->base.type));
		पूर्णांकel_plane_uapi_info(m, plane);
		पूर्णांकel_plane_hw_info(m, plane);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_scaler_info(काष्ठा seq_file *m, काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		to_पूर्णांकel_crtc_state(crtc->base.state);
	पूर्णांक num_scalers = crtc->num_scalers;
	पूर्णांक i;

	/* Not all platक्रमmas have a scaler */
	अगर (num_scalers) अणु
		seq_म_लिखो(m, "\tnum_scalers=%d, scaler_users=%x scaler_id=%d",
			   num_scalers,
			   crtc_state->scaler_state.scaler_users,
			   crtc_state->scaler_state.scaler_id);

		क्रम (i = 0; i < num_scalers; i++) अणु
			स्थिर काष्ठा पूर्णांकel_scaler *sc =
				&crtc_state->scaler_state.scalers[i];

			seq_म_लिखो(m, ", scalers[%d]: use=%s, mode=%x",
				   i, yesno(sc->in_use), sc->mode);
		पूर्ण
		seq_माला_दो(m, "\n");
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "\tNo scalers available on this platform\n");
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_VBLANK_EVADE)
अटल व्योम crtc_updates_info(काष्ठा seq_file *m,
			      काष्ठा पूर्णांकel_crtc *crtc,
			      स्थिर अक्षर *hdr)
अणु
	u64 count;
	पूर्णांक row;

	count = 0;
	क्रम (row = 0; row < ARRAY_SIZE(crtc->debug.vbl.बार); row++)
		count += crtc->debug.vbl.बार[row];
	seq_म_लिखो(m, "%sUpdates: %llu\n", hdr, count);
	अगर (!count)
		वापस;

	क्रम (row = 0; row < ARRAY_SIZE(crtc->debug.vbl.बार); row++) अणु
		अक्षर columns[80] = "       |";
		अचिन्हित पूर्णांक x;

		अगर (row & 1) अणु
			स्थिर अक्षर *units;

			अगर (row > 10) अणु
				x = 1000000;
				units = "ms";
			पूर्ण अन्यथा अणु
				x = 1000;
				units = "us";
			पूर्ण

			snम_लिखो(columns, माप(columns), "%4ld%s |",
				 DIV_ROUND_CLOSEST(BIT(row + 9), x), units);
		पूर्ण

		अगर (crtc->debug.vbl.बार[row]) अणु
			x = ilog2(crtc->debug.vbl.बार[row]);
			स_रखो(columns + 8, '*', x);
			columns[8 + x] = '\0';
		पूर्ण

		seq_म_लिखो(m, "%s%s\n", hdr, columns);
	पूर्ण

	seq_म_लिखो(m, "%sMin update: %lluns\n",
		   hdr, crtc->debug.vbl.min);
	seq_म_लिखो(m, "%sMax update: %lluns\n",
		   hdr, crtc->debug.vbl.max);
	seq_म_लिखो(m, "%sAverage update: %lluns\n",
		   hdr, भाग64_u64(crtc->debug.vbl.sum,  count));
	seq_म_लिखो(m, "%sOverruns > %uus: %u\n",
		   hdr, VBLANK_EVASION_TIME_US, crtc->debug.vbl.over);
पूर्ण

अटल पूर्णांक crtc_updates_show(काष्ठा seq_file *m, व्योम *data)
अणु
	crtc_updates_info(m, m->निजी, "");
	वापस 0;
पूर्ण

अटल पूर्णांक crtc_updates_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, crtc_updates_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार crtc_updates_ग_लिखो(काष्ठा file *file,
				  स्थिर अक्षर __user *ubuf,
				  माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा पूर्णांकel_crtc *crtc = m->निजी;

	/* May race with an update. Meh. */
	स_रखो(&crtc->debug.vbl, 0, माप(crtc->debug.vbl));

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations crtc_updates_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = crtc_updates_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = crtc_updates_ग_लिखो
पूर्ण;

अटल व्योम crtc_updates_add(काष्ठा drm_crtc *crtc)
अणु
	debugfs_create_file("i915_update_info", 0644, crtc->debugfs_entry,
			    to_पूर्णांकel_crtc(crtc), &crtc_updates_fops);
पूर्ण

#अन्यथा
अटल व्योम crtc_updates_info(काष्ठा seq_file *m,
			      काष्ठा पूर्णांकel_crtc *crtc,
			      स्थिर अक्षर *hdr)
अणु
पूर्ण

अटल व्योम crtc_updates_add(काष्ठा drm_crtc *crtc)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम पूर्णांकel_crtc_info(काष्ठा seq_file *m, काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		to_पूर्णांकel_crtc_state(crtc->base.state);
	काष्ठा पूर्णांकel_encoder *encoder;

	seq_म_लिखो(m, "[CRTC:%d:%s]:\n",
		   crtc->base.base.id, crtc->base.name);

	seq_म_लिखो(m, "\tuapi: enable=%s, active=%s, mode=" DRM_MODE_FMT "\n",
		   yesno(crtc_state->uapi.enable),
		   yesno(crtc_state->uapi.active),
		   DRM_MODE_ARG(&crtc_state->uapi.mode));

	अगर (crtc_state->hw.enable) अणु
		seq_म_लिखो(m, "\thw: active=%s, adjusted_mode=" DRM_MODE_FMT "\n",
			   yesno(crtc_state->hw.active),
			   DRM_MODE_ARG(&crtc_state->hw.adjusted_mode));

		seq_म_लिखो(m, "\tpipe src size=%dx%d, dither=%s, bpp=%d\n",
			   crtc_state->pipe_src_w, crtc_state->pipe_src_h,
			   yesno(crtc_state->dither), crtc_state->pipe_bpp);

		पूर्णांकel_scaler_info(m, crtc);
	पूर्ण

	अगर (crtc_state->bigjoiner)
		seq_म_लिखो(m, "\tLinked to [CRTC:%d:%s] as a %s\n",
			   crtc_state->bigjoiner_linked_crtc->base.base.id,
			   crtc_state->bigjoiner_linked_crtc->base.name,
			   crtc_state->bigjoiner_slave ? "slave" : "master");

	क्रम_each_पूर्णांकel_encoder_mask(&dev_priv->drm, encoder,
				    crtc_state->uapi.encoder_mask)
		पूर्णांकel_encoder_info(m, crtc, encoder);

	पूर्णांकel_plane_info(m, crtc);

	seq_म_लिखो(m, "\tunderrun reporting: cpu=%s pch=%s\n",
		   yesno(!crtc->cpu_fअगरo_underrun_disabled),
		   yesno(!crtc->pch_fअगरo_underrun_disabled));

	crtc_updates_info(m, crtc, "\t");
पूर्ण

अटल पूर्णांक i915_display_info(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांकel_wakeref_t wakeref;

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	drm_modeset_lock_all(dev);

	seq_म_लिखो(m, "CRTC info\n");
	seq_म_लिखो(m, "---------\n");
	क्रम_each_पूर्णांकel_crtc(dev, crtc)
		पूर्णांकel_crtc_info(m, crtc);

	seq_म_लिखो(m, "\n");
	seq_म_लिखो(m, "Connector info\n");
	seq_म_लिखो(m, "--------------\n");
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter)
		पूर्णांकel_connector_info(m, connector);
	drm_connector_list_iter_end(&conn_iter);

	drm_modeset_unlock_all(dev);

	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_shared_dplls_info(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक i;

	drm_modeset_lock_all(dev);

	seq_म_लिखो(m, "PLL refclks: non-SSC: %d kHz, SSC: %d kHz\n",
		   dev_priv->dpll.ref_clks.nssc,
		   dev_priv->dpll.ref_clks.ssc);

	क्रम (i = 0; i < dev_priv->dpll.num_shared_dpll; i++) अणु
		काष्ठा पूर्णांकel_shared_dpll *pll = &dev_priv->dpll.shared_dplls[i];

		seq_म_लिखो(m, "DPLL%i: %s, id: %i\n", i, pll->info->name,
			   pll->info->id);
		seq_म_लिखो(m, " pipe_mask: 0x%x, active: 0x%x, on: %s\n",
			   pll->state.pipe_mask, pll->active_mask, yesno(pll->on));
		seq_म_लिखो(m, " tracked hardware state:\n");
		seq_म_लिखो(m, " dpll:    0x%08x\n", pll->state.hw_state.dpll);
		seq_म_लिखो(m, " dpll_md: 0x%08x\n",
			   pll->state.hw_state.dpll_md);
		seq_म_लिखो(m, " fp0:     0x%08x\n", pll->state.hw_state.fp0);
		seq_म_लिखो(m, " fp1:     0x%08x\n", pll->state.hw_state.fp1);
		seq_म_लिखो(m, " wrpll:   0x%08x\n", pll->state.hw_state.wrpll);
		seq_म_लिखो(m, " cfgcr0:  0x%08x\n", pll->state.hw_state.cfgcr0);
		seq_म_लिखो(m, " cfgcr1:  0x%08x\n", pll->state.hw_state.cfgcr1);
		seq_म_लिखो(m, " mg_refclkin_ctl:        0x%08x\n",
			   pll->state.hw_state.mg_refclkin_ctl);
		seq_म_लिखो(m, " mg_clktop2_coreclkctl1: 0x%08x\n",
			   pll->state.hw_state.mg_clktop2_coreclkctl1);
		seq_म_लिखो(m, " mg_clktop2_hsclkctl:    0x%08x\n",
			   pll->state.hw_state.mg_clktop2_hsclkctl);
		seq_म_लिखो(m, " mg_pll_div0:  0x%08x\n",
			   pll->state.hw_state.mg_pll_भाग0);
		seq_म_लिखो(m, " mg_pll_div1:  0x%08x\n",
			   pll->state.hw_state.mg_pll_भाग1);
		seq_म_लिखो(m, " mg_pll_lf:    0x%08x\n",
			   pll->state.hw_state.mg_pll_lf);
		seq_म_लिखो(m, " mg_pll_frac_lock: 0x%08x\n",
			   pll->state.hw_state.mg_pll_frac_lock);
		seq_म_लिखो(m, " mg_pll_ssc:   0x%08x\n",
			   pll->state.hw_state.mg_pll_ssc);
		seq_म_लिखो(m, " mg_pll_bias:  0x%08x\n",
			   pll->state.hw_state.mg_pll_bias);
		seq_म_लिखो(m, " mg_pll_tdc_coldst_bias: 0x%08x\n",
			   pll->state.hw_state.mg_pll_tdc_coldst_bias);
	पूर्ण
	drm_modeset_unlock_all(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_ipc_status_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;

	seq_म_लिखो(m, "Isochronous Priority Control: %s\n",
			yesno(dev_priv->ipc_enabled));
	वापस 0;
पूर्ण

अटल पूर्णांक i915_ipc_status_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_i915_निजी *dev_priv = inode->i_निजी;

	अगर (!HAS_IPC(dev_priv))
		वापस -ENODEV;

	वापस single_खोलो(file, i915_ipc_status_show, dev_priv);
पूर्ण

अटल sमाप_प्रकार i915_ipc_status_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				     माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	पूर्णांकel_wakeref_t wakeref;
	bool enable;
	पूर्णांक ret;

	ret = kstrtobool_from_user(ubuf, len, &enable);
	अगर (ret < 0)
		वापस ret;

	with_पूर्णांकel_runसमय_pm(&dev_priv->runसमय_pm, wakeref) अणु
		अगर (!dev_priv->ipc_enabled && enable)
			drm_info(&dev_priv->drm,
				 "Enabling IPC: WM will be proper only after next commit\n");
		dev_priv->ipc_enabled = enable;
		पूर्णांकel_enable_ipc(dev_priv);
	पूर्ण

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_ipc_status_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_ipc_status_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = i915_ipc_status_ग_लिखो
पूर्ण;

अटल पूर्णांक i915_ddb_info(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा skl_ddb_entry *entry;
	काष्ठा पूर्णांकel_crtc *crtc;

	अगर (DISPLAY_VER(dev_priv) < 9)
		वापस -ENODEV;

	drm_modeset_lock_all(dev);

	seq_म_लिखो(m, "%-15s%8s%8s%8s\n", "", "Start", "End", "Size");

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);
		क्रमागत pipe pipe = crtc->pipe;
		क्रमागत plane_id plane_id;

		seq_म_लिखो(m, "Pipe %c\n", pipe_name(pipe));

		क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
			entry = &crtc_state->wm.skl.plane_ddb_y[plane_id];
			seq_म_लिखो(m, "  Plane%-8d%8u%8u%8u\n", plane_id + 1,
				   entry->start, entry->end,
				   skl_ddb_entry_size(entry));
		पूर्ण

		entry = &crtc_state->wm.skl.plane_ddb_y[PLANE_CURSOR];
		seq_म_लिखो(m, "  %-13s%8u%8u%8u\n", "Cursor", entry->start,
			   entry->end, skl_ddb_entry_size(entry));
	पूर्ण

	drm_modeset_unlock_all(dev);

	वापस 0;
पूर्ण

अटल व्योम drrs_status_per_crtc(काष्ठा seq_file *m,
				 काष्ठा drm_device *dev,
				 काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा i915_drrs *drrs = &dev_priv->drrs;
	पूर्णांक vrefresh = 0;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		bool supported = false;

		अगर (connector->state->crtc != &पूर्णांकel_crtc->base)
			जारी;

		seq_म_लिखो(m, "%s:\n", connector->name);

		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP &&
		    drrs->type == SEAMLESS_DRRS_SUPPORT)
			supported = true;

		seq_म_लिखो(m, "\tDRRS Supported: %s\n", yesno(supported));
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	seq_माला_दो(m, "\n");

	अगर (to_पूर्णांकel_crtc_state(पूर्णांकel_crtc->base.state)->has_drrs) अणु
		काष्ठा पूर्णांकel_panel *panel;

		mutex_lock(&drrs->mutex);
		/* DRRS Supported */
		seq_माला_दो(m, "\tDRRS Enabled: Yes\n");

		/* disable_drrs() will make drrs->dp शून्य */
		अगर (!drrs->dp) अणु
			seq_माला_दो(m, "Idleness DRRS: Disabled\n");
			mutex_unlock(&drrs->mutex);
			वापस;
		पूर्ण

		panel = &drrs->dp->attached_connector->panel;
		seq_म_लिखो(m, "\t\tBusy_frontbuffer_bits: 0x%X",
					drrs->busy_frontbuffer_bits);

		seq_माला_दो(m, "\n\t\t");
		अगर (drrs->refresh_rate_type == DRRS_HIGH_RR) अणु
			seq_माला_दो(m, "DRRS_State: DRRS_HIGH_RR\n");
			vrefresh = drm_mode_vrefresh(panel->fixed_mode);
		पूर्ण अन्यथा अगर (drrs->refresh_rate_type == DRRS_LOW_RR) अणु
			seq_माला_दो(m, "DRRS_State: DRRS_LOW_RR\n");
			vrefresh = drm_mode_vrefresh(panel->करोwnघड़ी_mode);
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m, "DRRS_State: Unknown(%d)\n",
						drrs->refresh_rate_type);
			mutex_unlock(&drrs->mutex);
			वापस;
		पूर्ण
		seq_म_लिखो(m, "\t\tVrefresh: %d", vrefresh);

		seq_माला_दो(m, "\n\t\t");
		mutex_unlock(&drrs->mutex);
	पूर्ण अन्यथा अणु
		/* DRRS not supported. Prपूर्णांक the VBT parameter*/
		seq_माला_दो(m, "\tDRRS Enabled : No");
	पूर्ण
	seq_माला_दो(m, "\n");
पूर्ण

अटल पूर्णांक i915_drrs_status(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc;
	पूर्णांक active_crtc_cnt = 0;

	drm_modeset_lock_all(dev);
	क्रम_each_पूर्णांकel_crtc(dev, पूर्णांकel_crtc) अणु
		अगर (पूर्णांकel_crtc->base.state->active) अणु
			active_crtc_cnt++;
			seq_म_लिखो(m, "\nCRTC %d:  ", active_crtc_cnt);

			drrs_status_per_crtc(m, dev, पूर्णांकel_crtc);
		पूर्ण
	पूर्ण
	drm_modeset_unlock_all(dev);

	अगर (!active_crtc_cnt)
		seq_माला_दो(m, "No active crtc found\n");

	वापस 0;
पूर्ण

#घोषणा LPSP_STATUS(COND) (COND ? seq_माला_दो(m, "LPSP: enabled\n") : \
				seq_माला_दो(m, "LPSP: disabled\n"))

अटल bool
पूर्णांकel_lpsp_घातer_well_enabled(काष्ठा drm_i915_निजी *i915,
			      क्रमागत i915_घातer_well_id घातer_well_id)
अणु
	पूर्णांकel_wakeref_t wakeref;
	bool is_enabled;

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);
	is_enabled = पूर्णांकel_display_घातer_well_is_enabled(i915,
							 घातer_well_id);
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);

	वापस is_enabled;
पूर्ण

अटल पूर्णांक i915_lpsp_status(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *i915 = node_to_i915(m->निजी);

	चयन (DISPLAY_VER(i915)) अणु
	हाल 12:
	हाल 11:
		LPSP_STATUS(!पूर्णांकel_lpsp_घातer_well_enabled(i915, ICL_DISP_PW_3));
		अवरोध;
	हाल 10:
	हाल 9:
		LPSP_STATUS(!पूर्णांकel_lpsp_घातer_well_enabled(i915, SKL_DISP_PW_2));
		अवरोध;
	शेष:
		/*
		 * Apart from HASWELL/BROADWELL other legacy platक्रमm करोesn't
		 * support lpsp.
		 */
		अगर (IS_HASWELL(i915) || IS_BROADWELL(i915))
			LPSP_STATUS(!पूर्णांकel_lpsp_घातer_well_enabled(i915, HSW_DISP_PW_GLOBAL));
		अन्यथा
			seq_माला_दो(m, "LPSP: not supported\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i915_dp_mst_info(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = node_to_i915(m->निजी);
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा पूर्णांकel_digital_port *dig_port;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->connector_type != DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		पूर्णांकel_encoder = पूर्णांकel_attached_encoder(to_पूर्णांकel_connector(connector));
		अगर (!पूर्णांकel_encoder || पूर्णांकel_encoder->type == INTEL_OUTPUT_DP_MST)
			जारी;

		dig_port = enc_to_dig_port(पूर्णांकel_encoder);
		अगर (!dig_port->dp.can_mst)
			जारी;

		seq_म_लिखो(m, "MST Source Port [ENCODER:%d:%s]\n",
			   dig_port->base.base.base.id,
			   dig_port->base.base.name);
		drm_dp_mst_dump_topology(m, &dig_port->dp.mst_mgr);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार i915_displayport_test_active_ग_लिखो(काष्ठा file *file,
						  स्थिर अक्षर __user *ubuf,
						  माप_प्रकार len, loff_t *offp)
अणु
	अक्षर *input_buffer;
	पूर्णांक status = 0;
	काष्ठा drm_device *dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;
	पूर्णांक val = 0;

	dev = ((काष्ठा seq_file *)file->निजी_data)->निजी;

	अगर (len == 0)
		वापस 0;

	input_buffer = memdup_user_nul(ubuf, len);
	अगर (IS_ERR(input_buffer))
		वापस PTR_ERR(input_buffer);

	drm_dbg(&to_i915(dev)->drm,
		"Copied %d bytes from user\n", (अचिन्हित पूर्णांक)len);

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा पूर्णांकel_encoder *encoder;

		अगर (connector->connector_type !=
		    DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		encoder = to_पूर्णांकel_encoder(connector->encoder);
		अगर (encoder && encoder->type == INTEL_OUTPUT_DP_MST)
			जारी;

		अगर (encoder && connector->status == connector_status_connected) अणु
			पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
			status = kstrtoपूर्णांक(input_buffer, 10, &val);
			अगर (status < 0)
				अवरोध;
			drm_dbg(&to_i915(dev)->drm,
				"Got %d for test active\n", val);
			/* To prevent erroneous activation of the compliance
			 * testing code, only accept an actual value of 1 here
			 */
			अगर (val == 1)
				पूर्णांकel_dp->compliance.test_active = true;
			अन्यथा
				पूर्णांकel_dp->compliance.test_active = false;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
	kमुक्त(input_buffer);
	अगर (status < 0)
		वापस status;

	*offp += len;
	वापस len;
पूर्ण

अटल पूर्णांक i915_displayport_test_active_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा पूर्णांकel_encoder *encoder;

		अगर (connector->connector_type !=
		    DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		encoder = to_पूर्णांकel_encoder(connector->encoder);
		अगर (encoder && encoder->type == INTEL_OUTPUT_DP_MST)
			जारी;

		अगर (encoder && connector->status == connector_status_connected) अणु
			पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
			अगर (पूर्णांकel_dp->compliance.test_active)
				seq_माला_दो(m, "1");
			अन्यथा
				seq_माला_दो(m, "0");
		पूर्ण अन्यथा
			seq_माला_दो(m, "0");
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_displayport_test_active_खोलो(काष्ठा inode *inode,
					     काष्ठा file *file)
अणु
	वापस single_खोलो(file, i915_displayport_test_active_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations i915_displayport_test_active_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_displayport_test_active_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = i915_displayport_test_active_ग_लिखो
पूर्ण;

अटल पूर्णांक i915_displayport_test_data_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा पूर्णांकel_encoder *encoder;

		अगर (connector->connector_type !=
		    DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		encoder = to_पूर्णांकel_encoder(connector->encoder);
		अगर (encoder && encoder->type == INTEL_OUTPUT_DP_MST)
			जारी;

		अगर (encoder && connector->status == connector_status_connected) अणु
			पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
			अगर (पूर्णांकel_dp->compliance.test_type ==
			    DP_TEST_LINK_EDID_READ)
				seq_म_लिखो(m, "%lx",
					   पूर्णांकel_dp->compliance.test_data.edid);
			अन्यथा अगर (पूर्णांकel_dp->compliance.test_type ==
				 DP_TEST_LINK_VIDEO_PATTERN) अणु
				seq_म_लिखो(m, "hdisplay: %d\n",
					   पूर्णांकel_dp->compliance.test_data.hdisplay);
				seq_म_लिखो(m, "vdisplay: %d\n",
					   पूर्णांकel_dp->compliance.test_data.vdisplay);
				seq_म_लिखो(m, "bpc: %u\n",
					   पूर्णांकel_dp->compliance.test_data.bpc);
			पूर्ण अन्यथा अगर (पूर्णांकel_dp->compliance.test_type ==
				   DP_TEST_LINK_PHY_TEST_PATTERN) अणु
				seq_म_लिखो(m, "pattern: %d\n",
					   पूर्णांकel_dp->compliance.test_data.phytest.phy_pattern);
				seq_म_लिखो(m, "Number of lanes: %d\n",
					   पूर्णांकel_dp->compliance.test_data.phytest.num_lanes);
				seq_म_लिखो(m, "Link Rate: %d\n",
					   पूर्णांकel_dp->compliance.test_data.phytest.link_rate);
				seq_म_लिखो(m, "level: %02x\n",
					   पूर्णांकel_dp->train_set[0]);
			पूर्ण
		पूर्ण अन्यथा
			seq_माला_दो(m, "0");
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(i915_displayport_test_data);

अटल पूर्णांक i915_displayport_test_type_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा पूर्णांकel_encoder *encoder;

		अगर (connector->connector_type !=
		    DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		encoder = to_पूर्णांकel_encoder(connector->encoder);
		अगर (encoder && encoder->type == INTEL_OUTPUT_DP_MST)
			जारी;

		अगर (encoder && connector->status == connector_status_connected) अणु
			पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
			seq_म_लिखो(m, "%02lx\n", पूर्णांकel_dp->compliance.test_type);
		पूर्ण अन्यथा
			seq_माला_दो(m, "0");
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(i915_displayport_test_type);

अटल व्योम wm_latency_show(काष्ठा seq_file *m, स्थिर u16 wm[8])
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक level;
	पूर्णांक num_levels;

	अगर (IS_CHERRYVIEW(dev_priv))
		num_levels = 3;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		num_levels = 1;
	अन्यथा अगर (IS_G4X(dev_priv))
		num_levels = 3;
	अन्यथा
		num_levels = ilk_wm_max_level(dev_priv) + 1;

	drm_modeset_lock_all(dev);

	क्रम (level = 0; level < num_levels; level++) अणु
		अचिन्हित पूर्णांक latency = wm[level];

		/*
		 * - WM1+ latency values in 0.5us units
		 * - latencies are in us on gen9/vlv/chv
		 */
		अगर (DISPLAY_VER(dev_priv) >= 9 ||
		    IS_VALLEYVIEW(dev_priv) ||
		    IS_CHERRYVIEW(dev_priv) ||
		    IS_G4X(dev_priv))
			latency *= 10;
		अन्यथा अगर (level > 0)
			latency *= 5;

		seq_म_लिखो(m, "WM%d %u (%u.%u usec)\n",
			   level, wm[level], latency / 10, latency % 10);
	पूर्ण

	drm_modeset_unlock_all(dev);
पूर्ण

अटल पूर्णांक pri_wm_latency_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	स्थिर u16 *latencies;

	अगर (DISPLAY_VER(dev_priv) >= 9)
		latencies = dev_priv->wm.skl_latency;
	अन्यथा
		latencies = dev_priv->wm.pri_latency;

	wm_latency_show(m, latencies);

	वापस 0;
पूर्ण

अटल पूर्णांक spr_wm_latency_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	स्थिर u16 *latencies;

	अगर (DISPLAY_VER(dev_priv) >= 9)
		latencies = dev_priv->wm.skl_latency;
	अन्यथा
		latencies = dev_priv->wm.spr_latency;

	wm_latency_show(m, latencies);

	वापस 0;
पूर्ण

अटल पूर्णांक cur_wm_latency_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	स्थिर u16 *latencies;

	अगर (DISPLAY_VER(dev_priv) >= 9)
		latencies = dev_priv->wm.skl_latency;
	अन्यथा
		latencies = dev_priv->wm.cur_latency;

	wm_latency_show(m, latencies);

	वापस 0;
पूर्ण

अटल पूर्णांक pri_wm_latency_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_i915_निजी *dev_priv = inode->i_निजी;

	अगर (DISPLAY_VER(dev_priv) < 5 && !IS_G4X(dev_priv))
		वापस -ENODEV;

	वापस single_खोलो(file, pri_wm_latency_show, dev_priv);
पूर्ण

अटल पूर्णांक spr_wm_latency_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_i915_निजी *dev_priv = inode->i_निजी;

	अगर (HAS_GMCH(dev_priv))
		वापस -ENODEV;

	वापस single_खोलो(file, spr_wm_latency_show, dev_priv);
पूर्ण

अटल पूर्णांक cur_wm_latency_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_i915_निजी *dev_priv = inode->i_निजी;

	अगर (HAS_GMCH(dev_priv))
		वापस -ENODEV;

	वापस single_खोलो(file, cur_wm_latency_show, dev_priv);
पूर्ण

अटल sमाप_प्रकार wm_latency_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				माप_प्रकार len, loff_t *offp, u16 wm[8])
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	काष्ठा drm_device *dev = &dev_priv->drm;
	u16 new[8] = अणु 0 पूर्ण;
	पूर्णांक num_levels;
	पूर्णांक level;
	पूर्णांक ret;
	अक्षर पंचांगp[32];

	अगर (IS_CHERRYVIEW(dev_priv))
		num_levels = 3;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		num_levels = 1;
	अन्यथा अगर (IS_G4X(dev_priv))
		num_levels = 3;
	अन्यथा
		num_levels = ilk_wm_max_level(dev_priv) + 1;

	अगर (len >= माप(पंचांगp))
		वापस -EINVAL;

	अगर (copy_from_user(पंचांगp, ubuf, len))
		वापस -EFAULT;

	पंचांगp[len] = '\0';

	ret = माला_पूछो(पंचांगp, "%hu %hu %hu %hu %hu %hu %hu %hu",
		     &new[0], &new[1], &new[2], &new[3],
		     &new[4], &new[5], &new[6], &new[7]);
	अगर (ret != num_levels)
		वापस -EINVAL;

	drm_modeset_lock_all(dev);

	क्रम (level = 0; level < num_levels; level++)
		wm[level] = new[level];

	drm_modeset_unlock_all(dev);

	वापस len;
पूर्ण


अटल sमाप_प्रकार pri_wm_latency_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				    माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	u16 *latencies;

	अगर (DISPLAY_VER(dev_priv) >= 9)
		latencies = dev_priv->wm.skl_latency;
	अन्यथा
		latencies = dev_priv->wm.pri_latency;

	वापस wm_latency_ग_लिखो(file, ubuf, len, offp, latencies);
पूर्ण

अटल sमाप_प्रकार spr_wm_latency_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				    माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	u16 *latencies;

	अगर (DISPLAY_VER(dev_priv) >= 9)
		latencies = dev_priv->wm.skl_latency;
	अन्यथा
		latencies = dev_priv->wm.spr_latency;

	वापस wm_latency_ग_लिखो(file, ubuf, len, offp, latencies);
पूर्ण

अटल sमाप_प्रकार cur_wm_latency_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				    माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	u16 *latencies;

	अगर (DISPLAY_VER(dev_priv) >= 9)
		latencies = dev_priv->wm.skl_latency;
	अन्यथा
		latencies = dev_priv->wm.cur_latency;

	वापस wm_latency_ग_लिखो(file, ubuf, len, offp, latencies);
पूर्ण

अटल स्थिर काष्ठा file_operations i915_pri_wm_latency_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = pri_wm_latency_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = pri_wm_latency_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations i915_spr_wm_latency_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = spr_wm_latency_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = spr_wm_latency_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा file_operations i915_cur_wm_latency_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = cur_wm_latency_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = cur_wm_latency_ग_लिखो
पूर्ण;

अटल पूर्णांक i915_hpd_storm_ctl_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	काष्ठा i915_hotplug *hotplug = &dev_priv->hotplug;

	/* Synchronize with everything first in हाल there's been an HPD
	 * storm, but we haven't finished handling it in the kernel yet
	 */
	पूर्णांकel_synchronize_irq(dev_priv);
	flush_work(&dev_priv->hotplug.dig_port_work);
	flush_delayed_work(&dev_priv->hotplug.hotplug_work);

	seq_म_लिखो(m, "Threshold: %d\n", hotplug->hpd_storm_threshold);
	seq_म_लिखो(m, "Detected: %s\n",
		   yesno(delayed_work_pending(&hotplug->reenable_work)));

	वापस 0;
पूर्ण

अटल sमाप_प्रकार i915_hpd_storm_ctl_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *ubuf, माप_प्रकार len,
					loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	काष्ठा i915_hotplug *hotplug = &dev_priv->hotplug;
	अचिन्हित पूर्णांक new_threshold;
	पूर्णांक i;
	अक्षर *newline;
	अक्षर पंचांगp[16];

	अगर (len >= माप(पंचांगp))
		वापस -EINVAL;

	अगर (copy_from_user(पंचांगp, ubuf, len))
		वापस -EFAULT;

	पंचांगp[len] = '\0';

	/* Strip newline, अगर any */
	newline = म_अक्षर(पंचांगp, '\n');
	अगर (newline)
		*newline = '\0';

	अगर (म_भेद(पंचांगp, "reset") == 0)
		new_threshold = HPD_STORM_DEFAULT_THRESHOLD;
	अन्यथा अगर (kstrtouपूर्णांक(पंचांगp, 10, &new_threshold) != 0)
		वापस -EINVAL;

	अगर (new_threshold > 0)
		drm_dbg_kms(&dev_priv->drm,
			    "Setting HPD storm detection threshold to %d\n",
			    new_threshold);
	अन्यथा
		drm_dbg_kms(&dev_priv->drm, "Disabling HPD storm detection\n");

	spin_lock_irq(&dev_priv->irq_lock);
	hotplug->hpd_storm_threshold = new_threshold;
	/* Reset the HPD storm stats so we करोn't accidentally trigger a storm */
	क्रम_each_hpd_pin(i)
		hotplug->stats[i].count = 0;
	spin_unlock_irq(&dev_priv->irq_lock);

	/* Re-enable hpd immediately अगर we were in an irq storm */
	flush_delayed_work(&dev_priv->hotplug.reenable_work);

	वापस len;
पूर्ण

अटल पूर्णांक i915_hpd_storm_ctl_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, i915_hpd_storm_ctl_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations i915_hpd_storm_ctl_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_hpd_storm_ctl_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = i915_hpd_storm_ctl_ग_लिखो
पूर्ण;

अटल पूर्णांक i915_hpd_लघु_storm_ctl_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;

	seq_म_लिखो(m, "Enabled: %s\n",
		   yesno(dev_priv->hotplug.hpd_लघु_storm_enabled));

	वापस 0;
पूर्ण

अटल पूर्णांक
i915_hpd_लघु_storm_ctl_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, i915_hpd_लघु_storm_ctl_show,
			   inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार i915_hpd_लघु_storm_ctl_ग_लिखो(काष्ठा file *file,
					      स्थिर अक्षर __user *ubuf,
					      माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_i915_निजी *dev_priv = m->निजी;
	काष्ठा i915_hotplug *hotplug = &dev_priv->hotplug;
	अक्षर *newline;
	अक्षर पंचांगp[16];
	पूर्णांक i;
	bool new_state;

	अगर (len >= माप(पंचांगp))
		वापस -EINVAL;

	अगर (copy_from_user(पंचांगp, ubuf, len))
		वापस -EFAULT;

	पंचांगp[len] = '\0';

	/* Strip newline, अगर any */
	newline = म_अक्षर(पंचांगp, '\n');
	अगर (newline)
		*newline = '\0';

	/* Reset to the "default" state क्रम this प्रणाली */
	अगर (म_भेद(पंचांगp, "reset") == 0)
		new_state = !HAS_DP_MST(dev_priv);
	अन्यथा अगर (kstrtobool(पंचांगp, &new_state) != 0)
		वापस -EINVAL;

	drm_dbg_kms(&dev_priv->drm, "%sabling HPD short storm detection\n",
		    new_state ? "En" : "Dis");

	spin_lock_irq(&dev_priv->irq_lock);
	hotplug->hpd_लघु_storm_enabled = new_state;
	/* Reset the HPD storm stats so we करोn't accidentally trigger a storm */
	क्रम_each_hpd_pin(i)
		hotplug->stats[i].count = 0;
	spin_unlock_irq(&dev_priv->irq_lock);

	/* Re-enable hpd immediately अगर we were in an irq storm */
	flush_delayed_work(&dev_priv->hotplug.reenable_work);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_hpd_लघु_storm_ctl_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_hpd_लघु_storm_ctl_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = i915_hpd_लघु_storm_ctl_ग_लिखो,
पूर्ण;

अटल पूर्णांक i915_drrs_ctl_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = data;
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_crtc *crtc;

	अगर (DISPLAY_VER(dev_priv) < 7)
		वापस -ENODEV;

	क्रम_each_पूर्णांकel_crtc(dev, crtc) अणु
		काष्ठा drm_connector_list_iter conn_iter;
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		काष्ठा drm_connector *connector;
		काष्ठा drm_crtc_commit *commit;
		पूर्णांक ret;

		ret = drm_modeset_lock_single_पूर्णांकerruptible(&crtc->base.mutex);
		अगर (ret)
			वापस ret;

		crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);

		अगर (!crtc_state->hw.active ||
		    !crtc_state->has_drrs)
			जाओ out;

		commit = crtc_state->uapi.commit;
		अगर (commit) अणु
			ret = रुको_क्रम_completion_पूर्णांकerruptible(&commit->hw_करोne);
			अगर (ret)
				जाओ out;
		पूर्ण

		drm_connector_list_iter_begin(dev, &conn_iter);
		drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
			काष्ठा पूर्णांकel_encoder *encoder;
			काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;

			अगर (!(crtc_state->uapi.connector_mask &
			      drm_connector_mask(connector)))
				जारी;

			encoder = पूर्णांकel_attached_encoder(to_पूर्णांकel_connector(connector));
			अगर (encoder->type != INTEL_OUTPUT_EDP)
				जारी;

			drm_dbg(&dev_priv->drm,
				"Manually %sabling DRRS. %llu\n",
				val ? "en" : "dis", val);

			पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
			अगर (val)
				पूर्णांकel_edp_drrs_enable(पूर्णांकel_dp,
						      crtc_state);
			अन्यथा
				पूर्णांकel_edp_drrs_disable(पूर्णांकel_dp,
						       crtc_state);
		पूर्ण
		drm_connector_list_iter_end(&conn_iter);

out:
		drm_modeset_unlock(&crtc->base.mutex);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(i915_drrs_ctl_fops, शून्य, i915_drrs_ctl_set, "%llu\n");

अटल sमाप_प्रकार
i915_fअगरo_underrun_reset_ग_लिखो(काष्ठा file *filp,
			       स्थिर अक्षर __user *ubuf,
			       माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा drm_i915_निजी *dev_priv = filp->निजी_data;
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc;
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक ret;
	bool reset;

	ret = kstrtobool_from_user(ubuf, cnt, &reset);
	अगर (ret)
		वापस ret;

	अगर (!reset)
		वापस cnt;

	क्रम_each_पूर्णांकel_crtc(dev, पूर्णांकel_crtc) अणु
		काष्ठा drm_crtc_commit *commit;
		काष्ठा पूर्णांकel_crtc_state *crtc_state;

		ret = drm_modeset_lock_single_पूर्णांकerruptible(&पूर्णांकel_crtc->base.mutex);
		अगर (ret)
			वापस ret;

		crtc_state = to_पूर्णांकel_crtc_state(पूर्णांकel_crtc->base.state);
		commit = crtc_state->uapi.commit;
		अगर (commit) अणु
			ret = रुको_क्रम_completion_पूर्णांकerruptible(&commit->hw_करोne);
			अगर (!ret)
				ret = रुको_क्रम_completion_पूर्णांकerruptible(&commit->flip_करोne);
		पूर्ण

		अगर (!ret && crtc_state->hw.active) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Re-arming FIFO underruns on pipe %c\n",
				    pipe_name(पूर्णांकel_crtc->pipe));

			पूर्णांकel_crtc_arm_fअगरo_underrun(पूर्णांकel_crtc, crtc_state);
		पूर्ण

		drm_modeset_unlock(&पूर्णांकel_crtc->base.mutex);

		अगर (ret)
			वापस ret;
	पूर्ण

	ret = पूर्णांकel_fbc_reset_underrun(dev_priv);
	अगर (ret)
		वापस ret;

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_fअगरo_underrun_reset_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.ग_लिखो = i915_fअगरo_underrun_reset_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा drm_info_list पूर्णांकel_display_debugfs_list[] = अणु
	अणु"i915_frontbuffer_tracking", i915_frontbuffer_tracking, 0पूर्ण,
	अणु"i915_fbc_status", i915_fbc_status, 0पूर्ण,
	अणु"i915_ips_status", i915_ips_status, 0पूर्ण,
	अणु"i915_sr_status", i915_sr_status, 0पूर्ण,
	अणु"i915_opregion", i915_opregion, 0पूर्ण,
	अणु"i915_vbt", i915_vbt, 0पूर्ण,
	अणु"i915_gem_framebuffer", i915_gem_framebuffer_info, 0पूर्ण,
	अणु"i915_edp_psr_status", i915_edp_psr_status, 0पूर्ण,
	अणु"i915_power_domain_info", i915_घातer_करोमुख्य_info, 0पूर्ण,
	अणु"i915_dmc_info", i915_dmc_info, 0पूर्ण,
	अणु"i915_display_info", i915_display_info, 0पूर्ण,
	अणु"i915_shared_dplls_info", i915_shared_dplls_info, 0पूर्ण,
	अणु"i915_dp_mst_info", i915_dp_mst_info, 0पूर्ण,
	अणु"i915_ddb_info", i915_ddb_info, 0पूर्ण,
	अणु"i915_drrs_status", i915_drrs_status, 0पूर्ण,
	अणु"i915_lpsp_status", i915_lpsp_status, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
पूर्ण पूर्णांकel_display_debugfs_files[] = अणु
	अणु"i915_fifo_underrun_reset", &i915_fअगरo_underrun_reset_opsपूर्ण,
	अणु"i915_pri_wm_latency", &i915_pri_wm_latency_fopsपूर्ण,
	अणु"i915_spr_wm_latency", &i915_spr_wm_latency_fopsपूर्ण,
	अणु"i915_cur_wm_latency", &i915_cur_wm_latency_fopsपूर्ण,
	अणु"i915_fbc_false_color", &i915_fbc_false_color_fopsपूर्ण,
	अणु"i915_dp_test_data", &i915_displayport_test_data_fopsपूर्ण,
	अणु"i915_dp_test_type", &i915_displayport_test_type_fopsपूर्ण,
	अणु"i915_dp_test_active", &i915_displayport_test_active_fopsपूर्ण,
	अणु"i915_hpd_storm_ctl", &i915_hpd_storm_ctl_fopsपूर्ण,
	अणु"i915_hpd_short_storm_ctl", &i915_hpd_लघु_storm_ctl_fopsपूर्ण,
	अणु"i915_ipc_status", &i915_ipc_status_fopsपूर्ण,
	अणु"i915_drrs_ctl", &i915_drrs_ctl_fopsपूर्ण,
	अणु"i915_edp_psr_debug", &i915_edp_psr_debug_fopsपूर्ण,
पूर्ण;

व्योम पूर्णांकel_display_debugfs_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_minor *minor = i915->drm.primary;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकel_display_debugfs_files); i++) अणु
		debugfs_create_file(पूर्णांकel_display_debugfs_files[i].name,
				    S_IRUGO | S_IWUSR,
				    minor->debugfs_root,
				    to_i915(minor->dev),
				    पूर्णांकel_display_debugfs_files[i].fops);
	पूर्ण

	drm_debugfs_create_files(पूर्णांकel_display_debugfs_list,
				 ARRAY_SIZE(पूर्णांकel_display_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण

अटल पूर्णांक i915_panel_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp =
		पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));

	अगर (connector->status != connector_status_connected)
		वापस -ENODEV;

	seq_म_लिखो(m, "Panel power up delay: %d\n",
		   पूर्णांकel_dp->pps.panel_घातer_up_delay);
	seq_म_लिखो(m, "Panel power down delay: %d\n",
		   पूर्णांकel_dp->pps.panel_घातer_करोwn_delay);
	seq_म_लिखो(m, "Backlight on delay: %d\n",
		   पूर्णांकel_dp->pps.backlight_on_delay);
	seq_म_लिखो(m, "Backlight off delay: %d\n",
		   पूर्णांकel_dp->pps.backlight_off_delay);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(i915_panel);

अटल पूर्णांक i915_hdcp_sink_capability_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	पूर्णांक ret;

	ret = drm_modeset_lock_single_पूर्णांकerruptible(&i915->drm.mode_config.connection_mutex);
	अगर (ret)
		वापस ret;

	अगर (!connector->encoder || connector->status != connector_status_connected) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	seq_म_लिखो(m, "%s:%d HDCP version: ", connector->name,
		   connector->base.id);
	पूर्णांकel_hdcp_info(m, पूर्णांकel_connector);

out:
	drm_modeset_unlock(&i915->drm.mode_config.connection_mutex);

	वापस ret;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(i915_hdcp_sink_capability);

अटल पूर्णांक i915_psr_status_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp =
		पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));

	वापस पूर्णांकel_psr_status(m, पूर्णांकel_dp);
पूर्ण
DEFINE_SHOW_ATTRIBUTE(i915_psr_status);

#घोषणा LPSP_CAPABLE(COND) (COND ? seq_माला_दो(m, "LPSP: capable\n") : \
				seq_माला_दो(m, "LPSP: incapable\n"))

अटल पूर्णांक i915_lpsp_capability_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा पूर्णांकel_encoder *encoder;

	encoder = पूर्णांकel_attached_encoder(to_पूर्णांकel_connector(connector));
	अगर (!encoder)
		वापस -ENODEV;

	अगर (connector->status != connector_status_connected)
		वापस -ENODEV;

	चयन (DISPLAY_VER(i915)) अणु
	हाल 12:
		/*
		 * Actually TGL can drive LPSP on port till DDI_C
		 * but there is no physical connected DDI_C on TGL sku's,
		 * even driver is not initilizing DDI_C port क्रम gen12.
		 */
		LPSP_CAPABLE(encoder->port <= PORT_B);
		अवरोध;
	हाल 11:
		LPSP_CAPABLE(connector->connector_type == DRM_MODE_CONNECTOR_DSI ||
			     connector->connector_type == DRM_MODE_CONNECTOR_eDP);
		अवरोध;
	हाल 10:
	हाल 9:
		LPSP_CAPABLE(encoder->port == PORT_A &&
			     (connector->connector_type == DRM_MODE_CONNECTOR_DSI ||
			     connector->connector_type == DRM_MODE_CONNECTOR_eDP  ||
			     connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort));
		अवरोध;
	शेष:
		अगर (IS_HASWELL(i915) || IS_BROADWELL(i915))
			LPSP_CAPABLE(connector->connector_type == DRM_MODE_CONNECTOR_eDP);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(i915_lpsp_capability);

अटल पूर्णांक i915_dsc_fec_support_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_crtc *crtc;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा पूर्णांकel_crtc_state *crtc_state = शून्य;
	पूर्णांक ret = 0;
	bool try_again = false;

	drm_modeset_acquire_init(&ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE);

	करो अणु
		try_again = false;
		ret = drm_modeset_lock(&dev->mode_config.connection_mutex,
				       &ctx);
		अगर (ret) अणु
			अगर (ret == -EDEADLK && !drm_modeset_backoff(&ctx)) अणु
				try_again = true;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
		crtc = connector->state->crtc;
		अगर (connector->status != connector_status_connected || !crtc) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण
		ret = drm_modeset_lock(&crtc->mutex, &ctx);
		अगर (ret == -EDEADLK) अणु
			ret = drm_modeset_backoff(&ctx);
			अगर (!ret) अणु
				try_again = true;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (ret) अणु
			अवरोध;
		पूर्ण
		पूर्णांकel_dp = पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));
		crtc_state = to_पूर्णांकel_crtc_state(crtc->state);
		seq_म_लिखो(m, "DSC_Enabled: %s\n",
			   yesno(crtc_state->dsc.compression_enable));
		seq_म_लिखो(m, "DSC_Sink_Support: %s\n",
			   yesno(drm_dp_sink_supports_dsc(पूर्णांकel_dp->dsc_dpcd)));
		seq_म_लिखो(m, "Force_DSC_Enable: %s\n",
			   yesno(पूर्णांकel_dp->क्रमce_dsc_en));
		अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
			seq_म_लिखो(m, "FEC_Sink_Support: %s\n",
				   yesno(drm_dp_sink_supports_fec(पूर्णांकel_dp->fec_capable)));
	पूर्ण जबतक (try_again);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार i915_dsc_fec_support_ग_लिखो(काष्ठा file *file,
					  स्थिर अक्षर __user *ubuf,
					  माप_प्रकार len, loff_t *offp)
अणु
	bool dsc_enable = false;
	पूर्णांक ret;
	काष्ठा drm_connector *connector =
		((काष्ठा seq_file *)file->निजी_data)->निजी;
	काष्ठा पूर्णांकel_encoder *encoder = पूर्णांकel_attached_encoder(to_पूर्णांकel_connector(connector));
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

	अगर (len == 0)
		वापस 0;

	drm_dbg(&i915->drm,
		"Copied %zu bytes from user to force DSC\n", len);

	ret = kstrtobool_from_user(ubuf, len, &dsc_enable);
	अगर (ret < 0)
		वापस ret;

	drm_dbg(&i915->drm, "Got %s for DSC Enable\n",
		(dsc_enable) ? "true" : "false");
	पूर्णांकel_dp->क्रमce_dsc_en = dsc_enable;

	*offp += len;
	वापस len;
पूर्ण

अटल पूर्णांक i915_dsc_fec_support_खोलो(काष्ठा inode *inode,
				     काष्ठा file *file)
अणु
	वापस single_खोलो(file, i915_dsc_fec_support_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations i915_dsc_fec_support_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_dsc_fec_support_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = i915_dsc_fec_support_ग_लिखो
पूर्ण;

/**
 * पूर्णांकel_connector_debugfs_add - add i915 specअगरic connector debugfs files
 * @connector: poपूर्णांकer to a रेजिस्टरed drm_connector
 *
 * Cleanup will be करोne by drm_connector_unरेजिस्टर() through a call to
 * drm_debugfs_connector_हटाओ().
 *
 * Returns 0 on success, negative error codes on error.
 */
पूर्णांक पूर्णांकel_connector_debugfs_add(काष्ठा drm_connector *connector)
अणु
	काष्ठा dentry *root = connector->debugfs_entry;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);

	/* The connector must have been रेजिस्टरed beक्रमehands. */
	अगर (!root)
		वापस -ENODEV;

	अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
		debugfs_create_file("i915_panel_timings", S_IRUGO, root,
				    connector, &i915_panel_fops);
		debugfs_create_file("i915_psr_sink_status", S_IRUGO, root,
				    connector, &i915_psr_sink_status_fops);
	पूर्ण

	अगर (HAS_PSR(dev_priv) &&
	    connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
		debugfs_create_file("i915_psr_status", 0444, root,
				    connector, &i915_psr_status_fops);
	पूर्ण

	अगर (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	    connector->connector_type == DRM_MODE_CONNECTOR_HDMIA ||
	    connector->connector_type == DRM_MODE_CONNECTOR_HDMIB) अणु
		debugfs_create_file("i915_hdcp_sink_capability", S_IRUGO, root,
				    connector, &i915_hdcp_sink_capability_fops);
	पूर्ण

	अगर ((DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv)) && ((connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort && !to_पूर्णांकel_connector(connector)->mst_port) || connector->connector_type == DRM_MODE_CONNECTOR_eDP))
		debugfs_create_file("i915_dsc_fec_support", S_IRUGO, root,
				    connector, &i915_dsc_fec_support_fops);

	/* Legacy panels करोesn't lpsp on any platक्रमm */
	अगर ((DISPLAY_VER(dev_priv) >= 9 || IS_HASWELL(dev_priv) ||
	     IS_BROADWELL(dev_priv)) &&
	     (connector->connector_type == DRM_MODE_CONNECTOR_DSI ||
	     connector->connector_type == DRM_MODE_CONNECTOR_eDP ||
	     connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	     connector->connector_type == DRM_MODE_CONNECTOR_HDMIA ||
	     connector->connector_type == DRM_MODE_CONNECTOR_HDMIB))
		debugfs_create_file("i915_lpsp_capability", 0444, root,
				    connector, &i915_lpsp_capability_fops);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_crtc_debugfs_add - add i915 specअगरic crtc debugfs files
 * @crtc: poपूर्णांकer to a drm_crtc
 *
 * Returns 0 on success, negative error codes on error.
 *
 * Failure to add debugfs entries should generally be ignored.
 */
पूर्णांक पूर्णांकel_crtc_debugfs_add(काष्ठा drm_crtc *crtc)
अणु
	अगर (!crtc->debugfs_entry)
		वापस -ENODEV;

	crtc_updates_add(crtc);
	वापस 0;
पूर्ण
