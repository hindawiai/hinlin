<शैली गुरु>
// SPDX-License-Identअगरier: MIT

/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/seq_file.h>

#समावेश "debugfs_gt.h"
#समावेश "debugfs_gt_pm.h"
#समावेश "i915_drv.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_clock_utils.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_llc.h"
#समावेश "intel_rc6.h"
#समावेश "intel_rps.h"
#समावेश "intel_runtime_pm.h"
#समावेश "intel_sideband.h"
#समावेश "intel_uncore.h"

अटल पूर्णांक fw_करोमुख्यs_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *fw_करोमुख्य;
	अचिन्हित पूर्णांक पंचांगp;

	seq_म_लिखो(m, "user.bypass_count = %u\n",
		   uncore->user_क्रमcewake_count);

	क्रम_each_fw_करोमुख्य(fw_करोमुख्य, uncore, पंचांगp)
		seq_म_लिखो(m, "%s.wake_count = %u\n",
			   पूर्णांकel_uncore_क्रमcewake_करोमुख्य_to_str(fw_करोमुख्य->id),
			   READ_ONCE(fw_करोमुख्य->wake_count));

	वापस 0;
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(fw_करोमुख्यs);

अटल व्योम prपूर्णांक_rc6_res(काष्ठा seq_file *m,
			  स्थिर अक्षर *title,
			  स्थिर i915_reg_t reg)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	पूर्णांकel_wakeref_t wakeref;

	with_पूर्णांकel_runसमय_pm(gt->uncore->rpm, wakeref)
		seq_म_लिखो(m, "%s %u (%llu us)\n", title,
			   पूर्णांकel_uncore_पढ़ो(gt->uncore, reg),
			   पूर्णांकel_rc6_residency_us(&gt->rc6, reg));
पूर्ण

अटल पूर्णांक vlv_drpc(काष्ठा seq_file *m)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 rcctl1, pw_status;

	pw_status = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_PW_STATUS);
	rcctl1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RC_CONTROL);

	seq_म_लिखो(m, "RC6 Enabled: %s\n",
		   yesno(rcctl1 & (GEN7_RC_CTL_TO_MODE |
					GEN6_RC_CTL_EI_MODE(1))));
	seq_म_लिखो(m, "Render Power Well: %s\n",
		   (pw_status & VLV_GTLC_PW_RENDER_STATUS_MASK) ? "Up" : "Down");
	seq_म_लिखो(m, "Media Power Well: %s\n",
		   (pw_status & VLV_GTLC_PW_MEDIA_STATUS_MASK) ? "Up" : "Down");

	prपूर्णांक_rc6_res(m, "Render RC6 residency since boot:", VLV_GT_RENDER_RC6);
	prपूर्णांक_rc6_res(m, "Media RC6 residency since boot:", VLV_GT_MEDIA_RC6);

	वापस fw_करोमुख्यs_show(m, शून्य);
पूर्ण

अटल पूर्णांक gen6_drpc(काष्ठा seq_file *m)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 gt_core_status, rcctl1, rc6vids = 0;
	u32 gen9_घातergate_enable = 0, gen9_घातergate_status = 0;

	gt_core_status = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_GT_CORE_STATUS);

	rcctl1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RC_CONTROL);
	अगर (INTEL_GEN(i915) >= 9) अणु
		gen9_घातergate_enable =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN9_PG_ENABLE);
		gen9_घातergate_status =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN9_PWRGT_DOMAIN_STATUS);
	पूर्ण

	अगर (INTEL_GEN(i915) <= 7)
		sandybridge_pcode_पढ़ो(i915, GEN6_PCODE_READ_RC6VIDS,
				       &rc6vids, शून्य);

	seq_म_लिखो(m, "RC1e Enabled: %s\n",
		   yesno(rcctl1 & GEN6_RC_CTL_RC1e_ENABLE));
	seq_म_लिखो(m, "RC6 Enabled: %s\n",
		   yesno(rcctl1 & GEN6_RC_CTL_RC6_ENABLE));
	अगर (INTEL_GEN(i915) >= 9) अणु
		seq_म_लिखो(m, "Render Well Gating Enabled: %s\n",
			   yesno(gen9_घातergate_enable & GEN9_RENDER_PG_ENABLE));
		seq_म_लिखो(m, "Media Well Gating Enabled: %s\n",
			   yesno(gen9_घातergate_enable & GEN9_MEDIA_PG_ENABLE));
	पूर्ण
	seq_म_लिखो(m, "Deep RC6 Enabled: %s\n",
		   yesno(rcctl1 & GEN6_RC_CTL_RC6p_ENABLE));
	seq_म_लिखो(m, "Deepest RC6 Enabled: %s\n",
		   yesno(rcctl1 & GEN6_RC_CTL_RC6pp_ENABLE));
	seq_माला_दो(m, "Current RC state: ");
	चयन (gt_core_status & GEN6_RCn_MASK) अणु
	हाल GEN6_RC0:
		अगर (gt_core_status & GEN6_CORE_CPD_STATE_MASK)
			seq_माला_दो(m, "Core Power Down\n");
		अन्यथा
			seq_माला_दो(m, "on\n");
		अवरोध;
	हाल GEN6_RC3:
		seq_माला_दो(m, "RC3\n");
		अवरोध;
	हाल GEN6_RC6:
		seq_माला_दो(m, "RC6\n");
		अवरोध;
	हाल GEN6_RC7:
		seq_माला_दो(m, "RC7\n");
		अवरोध;
	शेष:
		seq_माला_दो(m, "Unknown\n");
		अवरोध;
	पूर्ण

	seq_म_लिखो(m, "Core Power Down: %s\n",
		   yesno(gt_core_status & GEN6_CORE_CPD_STATE_MASK));
	अगर (INTEL_GEN(i915) >= 9) अणु
		seq_म_लिखो(m, "Render Power Well: %s\n",
			   (gen9_घातergate_status &
			    GEN9_PWRGT_RENDER_STATUS_MASK) ? "Up" : "Down");
		seq_म_लिखो(m, "Media Power Well: %s\n",
			   (gen9_घातergate_status &
			    GEN9_PWRGT_MEDIA_STATUS_MASK) ? "Up" : "Down");
	पूर्ण

	/* Not exactly sure what this is */
	prपूर्णांक_rc6_res(m, "RC6 \"Locked to RPn\" residency since boot:",
		      GEN6_GT_GFX_RC6_LOCKED);
	prपूर्णांक_rc6_res(m, "RC6 residency since boot:", GEN6_GT_GFX_RC6);
	prपूर्णांक_rc6_res(m, "RC6+ residency since boot:", GEN6_GT_GFX_RC6p);
	prपूर्णांक_rc6_res(m, "RC6++ residency since boot:", GEN6_GT_GFX_RC6pp);

	अगर (INTEL_GEN(i915) <= 7) अणु
		seq_म_लिखो(m, "RC6   voltage: %dmV\n",
			   GEN6_DECODE_RC6_VID(((rc6vids >> 0) & 0xff)));
		seq_म_लिखो(m, "RC6+  voltage: %dmV\n",
			   GEN6_DECODE_RC6_VID(((rc6vids >> 8) & 0xff)));
		seq_म_लिखो(m, "RC6++ voltage: %dmV\n",
			   GEN6_DECODE_RC6_VID(((rc6vids >> 16) & 0xff)));
	पूर्ण

	वापस fw_करोमुख्यs_show(m, शून्य);
पूर्ण

अटल पूर्णांक ilk_drpc(काष्ठा seq_file *m)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 rgvmodectl, rstdbyctl;
	u16 crstandvid;

	rgvmodectl = पूर्णांकel_uncore_पढ़ो(uncore, MEMMODECTL);
	rstdbyctl = पूर्णांकel_uncore_पढ़ो(uncore, RSTDBYCTL);
	crstandvid = पूर्णांकel_uncore_पढ़ो16(uncore, CRSTANDVID);

	seq_म_लिखो(m, "HD boost: %s\n", yesno(rgvmodectl & MEMMODE_BOOST_EN));
	seq_म_लिखो(m, "Boost freq: %d\n",
		   (rgvmodectl & MEMMODE_BOOST_FREQ_MASK) >>
		   MEMMODE_BOOST_FREQ_SHIFT);
	seq_म_लिखो(m, "HW control enabled: %s\n",
		   yesno(rgvmodectl & MEMMODE_HWIDLE_EN));
	seq_म_लिखो(m, "SW control enabled: %s\n",
		   yesno(rgvmodectl & MEMMODE_SWMODE_EN));
	seq_म_लिखो(m, "Gated voltage change: %s\n",
		   yesno(rgvmodectl & MEMMODE_RCLK_GATE));
	seq_म_लिखो(m, "Starting frequency: P%d\n",
		   (rgvmodectl & MEMMODE_FSTART_MASK) >> MEMMODE_FSTART_SHIFT);
	seq_म_लिखो(m, "Max P-state: P%d\n",
		   (rgvmodectl & MEMMODE_FMAX_MASK) >> MEMMODE_FMAX_SHIFT);
	seq_म_लिखो(m, "Min P-state: P%d\n", (rgvmodectl & MEMMODE_FMIN_MASK));
	seq_म_लिखो(m, "RS1 VID: %d\n", (crstandvid & 0x3f));
	seq_म_लिखो(m, "RS2 VID: %d\n", ((crstandvid >> 8) & 0x3f));
	seq_म_लिखो(m, "Render standby enabled: %s\n",
		   yesno(!(rstdbyctl & RCX_SW_EXIT)));
	seq_माला_दो(m, "Current RS state: ");
	चयन (rstdbyctl & RSX_STATUS_MASK) अणु
	हाल RSX_STATUS_ON:
		seq_माला_दो(m, "on\n");
		अवरोध;
	हाल RSX_STATUS_RC1:
		seq_माला_दो(m, "RC1\n");
		अवरोध;
	हाल RSX_STATUS_RC1E:
		seq_माला_दो(m, "RC1E\n");
		अवरोध;
	हाल RSX_STATUS_RS1:
		seq_माला_दो(m, "RS1\n");
		अवरोध;
	हाल RSX_STATUS_RS2:
		seq_माला_दो(m, "RS2 (RC6)\n");
		अवरोध;
	हाल RSX_STATUS_RS3:
		seq_माला_दो(m, "RC3 (RC6+)\n");
		अवरोध;
	शेष:
		seq_माला_दो(m, "unknown\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drpc_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक err = -ENODEV;

	with_पूर्णांकel_runसमय_pm(gt->uncore->rpm, wakeref) अणु
		अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
			err = vlv_drpc(m);
		अन्यथा अगर (INTEL_GEN(i915) >= 6)
			err = gen6_drpc(m);
		अन्यथा
			err = ilk_drpc(m);
	पूर्ण

	वापस err;
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(drpc);

अटल पूर्णांक frequency_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	पूर्णांकel_wakeref_t wakeref;

	wakeref = पूर्णांकel_runसमय_pm_get(uncore->rpm);

	अगर (IS_GEN(i915, 5)) अणु
		u16 rgvswctl = पूर्णांकel_uncore_पढ़ो16(uncore, MEMSWCTL);
		u16 rgvstat = पूर्णांकel_uncore_पढ़ो16(uncore, MEMSTAT_ILK);

		seq_म_लिखो(m, "Requested P-state: %d\n", (rgvswctl >> 8) & 0xf);
		seq_म_लिखो(m, "Requested VID: %d\n", rgvswctl & 0x3f);
		seq_म_लिखो(m, "Current VID: %d\n", (rgvstat & MEMSTAT_VID_MASK) >>
			   MEMSTAT_VID_SHIFT);
		seq_म_लिखो(m, "Current P-state: %d\n",
			   (rgvstat & MEMSTAT_PSTATE_MASK) >> MEMSTAT_PSTATE_SHIFT);
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915)) अणु
		u32 rpmodectl, freq_sts;

		rpmodectl = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_CONTROL);
		seq_म_लिखो(m, "Video Turbo Mode: %s\n",
			   yesno(rpmodectl & GEN6_RP_MEDIA_TURBO));
		seq_म_लिखो(m, "HW control enabled: %s\n",
			   yesno(rpmodectl & GEN6_RP_ENABLE));
		seq_म_लिखो(m, "SW control enabled: %s\n",
			   yesno((rpmodectl & GEN6_RP_MEDIA_MODE_MASK) ==
				 GEN6_RP_MEDIA_SW_MODE));

		vlv_punit_get(i915);
		freq_sts = vlv_punit_पढ़ो(i915, PUNIT_REG_GPU_FREQ_STS);
		vlv_punit_put(i915);

		seq_म_लिखो(m, "PUNIT_REG_GPU_FREQ_STS: 0x%08x\n", freq_sts);
		seq_म_लिखो(m, "DDR freq: %d MHz\n", i915->mem_freq);

		seq_म_लिखो(m, "actual GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, (freq_sts >> 8) & 0xff));

		seq_म_लिखो(m, "current GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->cur_freq));

		seq_म_लिखो(m, "max GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->max_freq));

		seq_म_लिखो(m, "min GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->min_freq));

		seq_म_लिखो(m, "idle GPU freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->idle_freq));

		seq_म_लिखो(m, "efficient (RPe) frequency: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->efficient_freq));
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 6) अणु
		u32 rp_state_limits;
		u32 gt_perf_status;
		u32 rp_state_cap;
		u32 rpmodectl, rpinclimit, rpdeclimit;
		u32 rpstat, cagf, reqf;
		u32 rpcurupei, rpcurup, rpprevup;
		u32 rpcurकरोwnei, rpcurकरोwn, rpprevकरोwn;
		u32 rpupei, rpupt, rpकरोwnei, rpकरोwnt;
		u32 pm_ier, pm_imr, pm_isr, pm_iir, pm_mask;
		पूर्णांक max_freq;

		rp_state_limits = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_STATE_LIMITS);
		अगर (IS_GEN9_LP(i915)) अणु
			rp_state_cap = पूर्णांकel_uncore_पढ़ो(uncore, BXT_RP_STATE_CAP);
			gt_perf_status = पूर्णांकel_uncore_पढ़ो(uncore, BXT_GT_PERF_STATUS);
		पूर्ण अन्यथा अणु
			rp_state_cap = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_STATE_CAP);
			gt_perf_status = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_GT_PERF_STATUS);
		पूर्ण

		/* RPSTAT1 is in the GT घातer well */
		पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);

		reqf = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RPNSWREQ);
		अगर (INTEL_GEN(i915) >= 9) अणु
			reqf >>= 23;
		पूर्ण अन्यथा अणु
			reqf &= ~GEN6_TURBO_DISABLE;
			अगर (IS_HASWELL(i915) || IS_BROADWELL(i915))
				reqf >>= 24;
			अन्यथा
				reqf >>= 25;
		पूर्ण
		reqf = पूर्णांकel_gpu_freq(rps, reqf);

		rpmodectl = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_CONTROL);
		rpinclimit = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_UP_THRESHOLD);
		rpdeclimit = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_DOWN_THRESHOLD);

		rpstat = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RPSTAT1);
		rpcurupei = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_CUR_UP_EI) & GEN6_CURICONT_MASK;
		rpcurup = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_CUR_UP) & GEN6_CURBSYTAVG_MASK;
		rpprevup = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_PREV_UP) & GEN6_CURBSYTAVG_MASK;
		rpcurकरोwnei = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_CUR_DOWN_EI) & GEN6_CURIAVG_MASK;
		rpcurकरोwn = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_CUR_DOWN) & GEN6_CURBSYTAVG_MASK;
		rpprevकरोwn = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_PREV_DOWN) & GEN6_CURBSYTAVG_MASK;

		rpupei = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_UP_EI);
		rpupt = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_UP_THRESHOLD);

		rpकरोwnei = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_DOWN_EI);
		rpकरोwnt = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_DOWN_THRESHOLD);

		cagf = पूर्णांकel_rps_पढ़ो_actual_frequency(rps);

		पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);

		अगर (INTEL_GEN(i915) >= 11) अणु
			pm_ier = पूर्णांकel_uncore_पढ़ो(uncore, GEN11_GPM_WGBOXPERF_INTR_ENABLE);
			pm_imr = पूर्णांकel_uncore_पढ़ो(uncore, GEN11_GPM_WGBOXPERF_INTR_MASK);
			/*
			 * The equivalent to the PM ISR & IIR cannot be पढ़ो
			 * without affecting the current state of the प्रणाली
			 */
			pm_isr = 0;
			pm_iir = 0;
		पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
			pm_ier = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_GT_IER(2));
			pm_imr = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_GT_IMR(2));
			pm_isr = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_GT_ISR(2));
			pm_iir = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_GT_IIR(2));
		पूर्ण अन्यथा अणु
			pm_ier = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_PMIER);
			pm_imr = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_PMIMR);
			pm_isr = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_PMISR);
			pm_iir = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_PMIIR);
		पूर्ण
		pm_mask = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_PMINTRMSK);

		seq_म_लिखो(m, "Video Turbo Mode: %s\n",
			   yesno(rpmodectl & GEN6_RP_MEDIA_TURBO));
		seq_म_लिखो(m, "HW control enabled: %s\n",
			   yesno(rpmodectl & GEN6_RP_ENABLE));
		seq_म_लिखो(m, "SW control enabled: %s\n",
			   yesno((rpmodectl & GEN6_RP_MEDIA_MODE_MASK) ==
				 GEN6_RP_MEDIA_SW_MODE));

		seq_म_लिखो(m, "PM IER=0x%08x IMR=0x%08x, MASK=0x%08x\n",
			   pm_ier, pm_imr, pm_mask);
		अगर (INTEL_GEN(i915) <= 10)
			seq_म_लिखो(m, "PM ISR=0x%08x IIR=0x%08x\n",
				   pm_isr, pm_iir);
		seq_म_लिखो(m, "pm_intrmsk_mbz: 0x%08x\n",
			   rps->pm_पूर्णांकrmsk_mbz);
		seq_म_लिखो(m, "GT_PERF_STATUS: 0x%08x\n", gt_perf_status);
		seq_म_लिखो(m, "Render p-state ratio: %d\n",
			   (gt_perf_status & (INTEL_GEN(i915) >= 9 ? 0x1ff00 : 0xff00)) >> 8);
		seq_म_लिखो(m, "Render p-state VID: %d\n",
			   gt_perf_status & 0xff);
		seq_म_लिखो(m, "Render p-state limit: %d\n",
			   rp_state_limits & 0xff);
		seq_म_लिखो(m, "RPSTAT1: 0x%08x\n", rpstat);
		seq_म_लिखो(m, "RPMODECTL: 0x%08x\n", rpmodectl);
		seq_म_लिखो(m, "RPINCLIMIT: 0x%08x\n", rpinclimit);
		seq_म_लिखो(m, "RPDECLIMIT: 0x%08x\n", rpdeclimit);
		seq_म_लिखो(m, "RPNSWREQ: %dMHz\n", reqf);
		seq_म_लिखो(m, "CAGF: %dMHz\n", cagf);
		seq_म_लिखो(m, "RP CUR UP EI: %d (%lldns)\n",
			   rpcurupei,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpcurupei));
		seq_म_लिखो(m, "RP CUR UP: %d (%lldns)\n",
			   rpcurup, पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpcurup));
		seq_म_लिखो(m, "RP PREV UP: %d (%lldns)\n",
			   rpprevup, पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpprevup));
		seq_म_लिखो(m, "Up threshold: %d%%\n",
			   rps->घातer.up_threshold);
		seq_म_लिखो(m, "RP UP EI: %d (%lldns)\n",
			   rpupei, पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpupei));
		seq_म_लिखो(m, "RP UP THRESHOLD: %d (%lldns)\n",
			   rpupt, पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpupt));

		seq_म_लिखो(m, "RP CUR DOWN EI: %d (%lldns)\n",
			   rpcurकरोwnei,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpcurकरोwnei));
		seq_म_लिखो(m, "RP CUR DOWN: %d (%lldns)\n",
			   rpcurकरोwn,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpcurकरोwn));
		seq_म_लिखो(m, "RP PREV DOWN: %d (%lldns)\n",
			   rpprevकरोwn,
			   पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpprevकरोwn));
		seq_म_लिखो(m, "Down threshold: %d%%\n",
			   rps->घातer.करोwn_threshold);
		seq_म_लिखो(m, "RP DOWN EI: %d (%lldns)\n",
			   rpकरोwnei, पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpकरोwnei));
		seq_म_लिखो(m, "RP DOWN THRESHOLD: %d (%lldns)\n",
			   rpकरोwnt, पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, rpकरोwnt));

		max_freq = (IS_GEN9_LP(i915) ? rp_state_cap >> 0 :
			    rp_state_cap >> 16) & 0xff;
		max_freq *= (IS_GEN9_BC(i915) ||
			     INTEL_GEN(i915) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_म_लिखो(m, "Lowest (RPN) frequency: %dMHz\n",
			   पूर्णांकel_gpu_freq(rps, max_freq));

		max_freq = (rp_state_cap & 0xff00) >> 8;
		max_freq *= (IS_GEN9_BC(i915) ||
			     INTEL_GEN(i915) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_म_लिखो(m, "Nominal (RP1) frequency: %dMHz\n",
			   पूर्णांकel_gpu_freq(rps, max_freq));

		max_freq = (IS_GEN9_LP(i915) ? rp_state_cap >> 16 :
			    rp_state_cap >> 0) & 0xff;
		max_freq *= (IS_GEN9_BC(i915) ||
			     INTEL_GEN(i915) >= 10 ? GEN9_FREQ_SCALER : 1);
		seq_म_लिखो(m, "Max non-overclocked (RP0) frequency: %dMHz\n",
			   पूर्णांकel_gpu_freq(rps, max_freq));
		seq_म_लिखो(m, "Max overclocked frequency: %dMHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->max_freq));

		seq_म_लिखो(m, "Current freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->cur_freq));
		seq_म_लिखो(m, "Actual freq: %d MHz\n", cagf);
		seq_म_लिखो(m, "Idle freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->idle_freq));
		seq_म_लिखो(m, "Min freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->min_freq));
		seq_म_लिखो(m, "Boost freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->boost_freq));
		seq_म_लिखो(m, "Max freq: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->max_freq));
		seq_म_लिखो(m,
			   "efficient (RPe) frequency: %d MHz\n",
			   पूर्णांकel_gpu_freq(rps, rps->efficient_freq));
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "no P-state info available\n");
	पूर्ण

	seq_म_लिखो(m, "Current CD clock frequency: %d kHz\n", i915->cdclk.hw.cdclk);
	seq_म_लिखो(m, "Max CD clock frequency: %d kHz\n", i915->max_cdclk_freq);
	seq_म_लिखो(m, "Max pixel clock frequency: %d kHz\n", i915->max_करोtclk_freq);

	पूर्णांकel_runसमय_pm_put(uncore->rpm, wakeref);

	वापस 0;
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(frequency);

अटल पूर्णांक llc_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	स्थिर bool edram = INTEL_GEN(i915) > 8;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	अचिन्हित पूर्णांक max_gpu_freq, min_gpu_freq;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक gpu_freq, ia_freq;

	seq_म_लिखो(m, "LLC: %s\n", yesno(HAS_LLC(i915)));
	seq_म_लिखो(m, "%s: %uMB\n", edram ? "eDRAM" : "eLLC",
		   i915->edram_size_mb);

	min_gpu_freq = rps->min_freq;
	max_gpu_freq = rps->max_freq;
	अगर (IS_GEN9_BC(i915) || INTEL_GEN(i915) >= 10) अणु
		/* Convert GT frequency to 50 HZ units */
		min_gpu_freq /= GEN9_FREQ_SCALER;
		max_gpu_freq /= GEN9_FREQ_SCALER;
	पूर्ण

	seq_माला_दो(m, "GPU freq (MHz)\tEffective CPU freq (MHz)\tEffective Ring freq (MHz)\n");

	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);
	क्रम (gpu_freq = min_gpu_freq; gpu_freq <= max_gpu_freq; gpu_freq++) अणु
		ia_freq = gpu_freq;
		sandybridge_pcode_पढ़ो(i915,
				       GEN6_PCODE_READ_MIN_FREQ_TABLE,
				       &ia_freq, शून्य);
		seq_म_लिखो(m, "%d\t\t%d\t\t\t\t%d\n",
			   पूर्णांकel_gpu_freq(rps,
					  (gpu_freq *
					   (IS_GEN9_BC(i915) ||
					    INTEL_GEN(i915) >= 10 ?
					    GEN9_FREQ_SCALER : 1))),
			   ((ia_freq >> 0) & 0xff) * 100,
			   ((ia_freq >> 8) & 0xff) * 100);
	पूर्ण
	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);

	वापस 0;
पूर्ण

अटल bool llc_eval(व्योम *data)
अणु
	काष्ठा पूर्णांकel_gt *gt = data;

	वापस HAS_LLC(gt->i915);
पूर्ण

DEFINE_GT_DEBUGFS_ATTRIBUTE(llc);

अटल स्थिर अक्षर *rps_घातer_to_str(अचिन्हित पूर्णांक घातer)
अणु
	अटल स्थिर अक्षर * स्थिर strings[] = अणु
		[LOW_POWER] = "low power",
		[BETWEEN] = "mixed",
		[HIGH_POWER] = "high power",
	पूर्ण;

	अगर (घातer >= ARRAY_SIZE(strings) || !strings[घातer])
		वापस "unknown";

	वापस strings[घातer];
पूर्ण

अटल पूर्णांक rps_boost_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;

	seq_म_लिखो(m, "RPS enabled? %s\n", yesno(पूर्णांकel_rps_is_enabled(rps)));
	seq_म_लिखो(m, "RPS active? %s\n", yesno(पूर्णांकel_rps_is_active(rps)));
	seq_म_लिखो(m, "GPU busy? %s, %llums\n",
		   yesno(gt->awake),
		   kसमय_प्रकारo_ms(पूर्णांकel_gt_get_awake_समय(gt)));
	seq_म_लिखो(m, "Boosts outstanding? %d\n",
		   atomic_पढ़ो(&rps->num_रुकोers));
	seq_म_लिखो(m, "Interactive? %d\n", READ_ONCE(rps->घातer.पूर्णांकeractive));
	seq_म_लिखो(m, "Frequency requested %d, actual %d\n",
		   पूर्णांकel_gpu_freq(rps, rps->cur_freq),
		   पूर्णांकel_rps_पढ़ो_actual_frequency(rps));
	seq_म_लिखो(m, "  min hard:%d, soft:%d; max soft:%d, hard:%d\n",
		   पूर्णांकel_gpu_freq(rps, rps->min_freq),
		   पूर्णांकel_gpu_freq(rps, rps->min_freq_softlimit),
		   पूर्णांकel_gpu_freq(rps, rps->max_freq_softlimit),
		   पूर्णांकel_gpu_freq(rps, rps->max_freq));
	seq_म_लिखो(m, "  idle:%d, efficient:%d, boost:%d\n",
		   पूर्णांकel_gpu_freq(rps, rps->idle_freq),
		   पूर्णांकel_gpu_freq(rps, rps->efficient_freq),
		   पूर्णांकel_gpu_freq(rps, rps->boost_freq));

	seq_म_लिखो(m, "Wait boosts: %d\n", READ_ONCE(rps->boosts));

	अगर (INTEL_GEN(i915) >= 6 && पूर्णांकel_rps_is_active(rps)) अणु
		काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
		u32 rpup, rpupei;
		u32 rpकरोwn, rpकरोwnei;

		पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);
		rpup = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_RP_CUR_UP) & GEN6_RP_EI_MASK;
		rpupei = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_RP_CUR_UP_EI) & GEN6_RP_EI_MASK;
		rpकरोwn = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_RP_CUR_DOWN) & GEN6_RP_EI_MASK;
		rpकरोwnei = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_RP_CUR_DOWN_EI) & GEN6_RP_EI_MASK;
		पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);

		seq_म_लिखो(m, "\nRPS Autotuning (current \"%s\" window):\n",
			   rps_घातer_to_str(rps->घातer.mode));
		seq_म_लिखो(m, "  Avg. up: %d%% [above threshold? %d%%]\n",
			   rpup && rpupei ? 100 * rpup / rpupei : 0,
			   rps->घातer.up_threshold);
		seq_म_लिखो(m, "  Avg. down: %d%% [below threshold? %d%%]\n",
			   rpकरोwn && rpकरोwnei ? 100 * rpकरोwn / rpकरोwnei : 0,
			   rps->घातer.करोwn_threshold);
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "\nRPS Autotuning inactive\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल bool rps_eval(व्योम *data)
अणु
	काष्ठा पूर्णांकel_gt *gt = data;

	वापस HAS_RPS(gt->i915);
पूर्ण

DEFINE_GT_DEBUGFS_ATTRIBUTE(rps_boost);

व्योम debugfs_gt_pm_रेजिस्टर(काष्ठा पूर्णांकel_gt *gt, काष्ठा dentry *root)
अणु
	अटल स्थिर काष्ठा debugfs_gt_file files[] = अणु
		अणु "drpc", &drpc_fops, शून्य पूर्ण,
		अणु "frequency", &frequency_fops, शून्य पूर्ण,
		अणु "forcewake", &fw_करोमुख्यs_fops, शून्य पूर्ण,
		अणु "llc", &llc_fops, llc_eval पूर्ण,
		अणु "rps_boost", &rps_boost_fops, rps_eval पूर्ण,
	पूर्ण;

	पूर्णांकel_gt_debugfs_रेजिस्टर_files(root, files, ARRAY_SIZE(files), gt);
पूर्ण
