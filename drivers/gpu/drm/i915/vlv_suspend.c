<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/kernel.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"
#समावेश "i915_trace.h"
#समावेश "i915_utils.h"
#समावेश "intel_pm.h"
#समावेश "vlv_suspend.h"

काष्ठा vlv_s0ix_state अणु
	/* GAM */
	u32 wr_watermark;
	u32 gfx_prio_ctrl;
	u32 arb_mode;
	u32 gfx_pend_tlb0;
	u32 gfx_pend_tlb1;
	u32 lra_limits[GEN7_LRA_LIMITS_REG_NUM];
	u32 media_max_req_count;
	u32 gfx_max_req_count;
	u32 render_hwsp;
	u32 ecochk;
	u32 bsd_hwsp;
	u32 blt_hwsp;
	u32 tlb_rd_addr;

	/* MBC */
	u32 g3dctl;
	u32 gsckgctl;
	u32 mbctl;

	/* GCP */
	u32 ucgctl1;
	u32 ucgctl3;
	u32 rcgctl1;
	u32 rcgctl2;
	u32 rstctl;
	u32 misccpctl;

	/* GPM */
	u32 gfxछोड़ो;
	u32 rpdeuhwtc;
	u32 rpdeuc;
	u32 ecobus;
	u32 pwrdwnupctl;
	u32 rp_करोwn_समयout;
	u32 rp_deucsw;
	u32 rcubmabdपंचांगr;
	u32 rcedata;
	u32 spare2gh;

	/* Display 1 CZ करोमुख्य */
	u32 gt_imr;
	u32 gt_ier;
	u32 pm_imr;
	u32 pm_ier;
	u32 gt_scratch[GEN7_GT_SCRATCH_REG_NUM];

	/* GT SA CZ करोमुख्य */
	u32 tilectl;
	u32 gt_fअगरoctl;
	u32 gtlc_wake_ctrl;
	u32 gtlc_survive;
	u32 pmwgicz;

	/* Display 2 CZ करोमुख्य */
	u32 gu_ctl0;
	u32 gu_ctl1;
	u32 pcbr;
	u32 घड़ी_gate_dis2;
पूर्ण;

/*
 * Save all Gunit रेजिस्टरs that may be lost after a D3 and a subsequent
 * S0i[R123] transition. The list of रेजिस्टरs needing a save/restore is
 * defined in the VLV2_S0IXRegs करोcument. This करोcuments marks all Gunit
 * रेजिस्टरs in the following way:
 * - Driver: saved/restored by the driver
 * - Punit : saved/restored by the Punit firmware
 * - No, w/o marking: no need to save/restore, since the रेजिस्टर is R/O or
 *                    used पूर्णांकernally by the HW in a way that करोesn't depend
 *                    keeping the content across a suspend/resume.
 * - Debug : used क्रम debugging
 *
 * We save/restore all रेजिस्टरs marked with 'Driver', with the following
 * exceptions:
 * - Registers out of use, including also रेजिस्टरs marked with 'Debug'.
 *   These have no effect on the driver's operation, so we don't save/restore
 *   them to reduce the overhead.
 * - Registers that are fully setup by an initialization function called from
 *   the resume path. For example many घड़ी gating and RPS/RC6 रेजिस्टरs.
 * - Registers that provide the right functionality with their reset शेषs.
 *
 * TODO: Except क्रम रेजिस्टरs that based on the above 3 criteria can be safely
 * ignored, we save/restore all others, practically treating the HW context as
 * a black-box क्रम the driver. Further investigation is needed to reduce the
 * saved/restored रेजिस्टरs even further, by following the same 3 criteria.
 */
अटल व्योम vlv_save_gunit_s0ix_state(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा vlv_s0ix_state *s = i915->vlv_s0ix_state;
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	पूर्णांक i;

	अगर (!s)
		वापस;

	/* GAM 0x4000-0x4770 */
	s->wr_watermark = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_WR_WATERMARK);
	s->gfx_prio_ctrl = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_GFX_PRIO_CTRL);
	s->arb_mode = पूर्णांकel_uncore_पढ़ो(uncore, ARB_MODE);
	s->gfx_pend_tlb0 = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_GFX_PEND_TLB0);
	s->gfx_pend_tlb1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_GFX_PEND_TLB1);

	क्रम (i = 0; i < ARRAY_SIZE(s->lra_limits); i++)
		s->lra_limits[i] = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_LRA_LIMITS(i));

	s->media_max_req_count = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_MEDIA_MAX_REQ_COUNT);
	s->gfx_max_req_count = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_GFX_MAX_REQ_COUNT);

	s->render_hwsp = पूर्णांकel_uncore_पढ़ो(uncore, RENDER_HWS_PGA_GEN7);
	s->ecochk = पूर्णांकel_uncore_पढ़ो(uncore, GAM_ECOCHK);
	s->bsd_hwsp = पूर्णांकel_uncore_पढ़ो(uncore, BSD_HWS_PGA_GEN7);
	s->blt_hwsp = पूर्णांकel_uncore_पढ़ो(uncore, BLT_HWS_PGA_GEN7);

	s->tlb_rd_addr = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_TLB_RD_ADDR);

	/* MBC 0x9024-0x91D0, 0x8500 */
	s->g3dctl = पूर्णांकel_uncore_पढ़ो(uncore, VLV_G3DCTL);
	s->gsckgctl = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GSCKGCTL);
	s->mbctl = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_MBCTL);

	/* GCP 0x9400-0x9424, 0x8100-0x810C */
	s->ucgctl1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_UCGCTL1);
	s->ucgctl3 = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_UCGCTL3);
	s->rcgctl1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RCGCTL1);
	s->rcgctl2 = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RCGCTL2);
	s->rstctl = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RSTCTL);
	s->misccpctl = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_MISCCPCTL);

	/* GPM 0xA000-0xAA84, 0x8000-0x80FC */
	s->gfxछोड़ो = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_GFXPAUSE);
	s->rpdeuhwtc = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RPDEUHWTC);
	s->rpdeuc = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RPDEUC);
	s->ecobus = पूर्णांकel_uncore_पढ़ो(uncore, ECOBUS);
	s->pwrdwnupctl = पूर्णांकel_uncore_पढ़ो(uncore, VLV_PWRDWNUPCTL);
	s->rp_करोwn_समयout = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_DOWN_TIMEOUT);
	s->rp_deucsw = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RPDEUCSW);
	s->rcubmabdपंचांगr = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RCUBMABDTMR);
	s->rcedata = पूर्णांकel_uncore_पढ़ो(uncore, VLV_RCEDATA);
	s->spare2gh = पूर्णांकel_uncore_पढ़ो(uncore, VLV_SPAREG2H);

	/* Display CZ करोमुख्य, 0x4400C-0x4402C, 0x4F000-0x4F11F */
	s->gt_imr = पूर्णांकel_uncore_पढ़ो(uncore, GTIMR);
	s->gt_ier = पूर्णांकel_uncore_पढ़ो(uncore, GTIER);
	s->pm_imr = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_PMIMR);
	s->pm_ier = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_PMIER);

	क्रम (i = 0; i < ARRAY_SIZE(s->gt_scratch); i++)
		s->gt_scratch[i] = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_GT_SCRATCH(i));

	/* GT SA CZ करोमुख्य, 0x100000-0x138124 */
	s->tilectl = पूर्णांकel_uncore_पढ़ो(uncore, TILECTL);
	s->gt_fअगरoctl = पूर्णांकel_uncore_पढ़ो(uncore, GTFIFOCTL);
	s->gtlc_wake_ctrl = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_WAKE_CTRL);
	s->gtlc_survive = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_SURVIVABILITY_REG);
	s->pmwgicz = पूर्णांकel_uncore_पढ़ो(uncore, VLV_PMWGICZ);

	/* Gunit-Display CZ करोमुख्य, 0x182028-0x1821CF */
	s->gu_ctl0 = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GU_CTL0);
	s->gu_ctl1 = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GU_CTL1);
	s->pcbr = पूर्णांकel_uncore_पढ़ो(uncore, VLV_PCBR);
	s->घड़ी_gate_dis2 = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GUNIT_CLOCK_GATE2);

	/*
	 * Not saving any of:
	 * DFT,		0x9800-0x9EC0
	 * SARB,	0xB000-0xB1FC
	 * GAC,		0x5208-0x524C, 0x14000-0x14C000
	 * PCI CFG
	 */
पूर्ण

अटल व्योम vlv_restore_gunit_s0ix_state(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा vlv_s0ix_state *s = i915->vlv_s0ix_state;
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 val;
	पूर्णांक i;

	अगर (!s)
		वापस;

	/* GAM 0x4000-0x4770 */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_WR_WATERMARK, s->wr_watermark);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_GFX_PRIO_CTRL, s->gfx_prio_ctrl);
	पूर्णांकel_uncore_ग_लिखो(uncore, ARB_MODE, s->arb_mode | (0xffff << 16));
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_GFX_PEND_TLB0, s->gfx_pend_tlb0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_GFX_PEND_TLB1, s->gfx_pend_tlb1);

	क्रम (i = 0; i < ARRAY_SIZE(s->lra_limits); i++)
		पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_LRA_LIMITS(i), s->lra_limits[i]);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_MEDIA_MAX_REQ_COUNT, s->media_max_req_count);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_GFX_MAX_REQ_COUNT, s->gfx_max_req_count);

	पूर्णांकel_uncore_ग_लिखो(uncore, RENDER_HWS_PGA_GEN7, s->render_hwsp);
	पूर्णांकel_uncore_ग_लिखो(uncore, GAM_ECOCHK, s->ecochk);
	पूर्णांकel_uncore_ग_लिखो(uncore, BSD_HWS_PGA_GEN7, s->bsd_hwsp);
	पूर्णांकel_uncore_ग_लिखो(uncore, BLT_HWS_PGA_GEN7, s->blt_hwsp);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_TLB_RD_ADDR, s->tlb_rd_addr);

	/* MBC 0x9024-0x91D0, 0x8500 */
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_G3DCTL, s->g3dctl);
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GSCKGCTL, s->gsckgctl);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_MBCTL, s->mbctl);

	/* GCP 0x9400-0x9424, 0x8100-0x810C */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_UCGCTL1, s->ucgctl1);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_UCGCTL3, s->ucgctl3);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_RCGCTL1, s->rcgctl1);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_RCGCTL2, s->rcgctl2);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_RSTCTL, s->rstctl);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_MISCCPCTL, s->misccpctl);

	/* GPM 0xA000-0xAA84, 0x8000-0x80FC */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_GFXPAUSE, s->gfxछोड़ो);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_RPDEUHWTC, s->rpdeuhwtc);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_RPDEUC, s->rpdeuc);
	पूर्णांकel_uncore_ग_लिखो(uncore, ECOBUS, s->ecobus);
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_PWRDWNUPCTL, s->pwrdwnupctl);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_RP_DOWN_TIMEOUT, s->rp_करोwn_समयout);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_RPDEUCSW, s->rp_deucsw);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_RCUBMABDTMR, s->rcubmabdपंचांगr);
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_RCEDATA, s->rcedata);
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_SPAREG2H, s->spare2gh);

	/* Display CZ करोमुख्य, 0x4400C-0x4402C, 0x4F000-0x4F11F */
	पूर्णांकel_uncore_ग_लिखो(uncore, GTIMR, s->gt_imr);
	पूर्णांकel_uncore_ग_लिखो(uncore, GTIER, s->gt_ier);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_PMIMR, s->pm_imr);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN6_PMIER, s->pm_ier);

	क्रम (i = 0; i < ARRAY_SIZE(s->gt_scratch); i++)
		पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_GT_SCRATCH(i), s->gt_scratch[i]);

	/* GT SA CZ करोमुख्य, 0x100000-0x138124 */
	पूर्णांकel_uncore_ग_लिखो(uncore, TILECTL, s->tilectl);
	पूर्णांकel_uncore_ग_लिखो(uncore, GTFIFOCTL, s->gt_fअगरoctl);
	/*
	 * Preserve the GT allow wake and GFX क्रमce घड़ी bit, they are not
	 * be restored, as they are used to control the s0ix suspend/resume
	 * sequence by the caller.
	 */
	val = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_WAKE_CTRL);
	val &= VLV_GTLC_ALLOWWAKEREQ;
	val |= s->gtlc_wake_ctrl & ~VLV_GTLC_ALLOWWAKEREQ;
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GTLC_WAKE_CTRL, val);

	val = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_SURVIVABILITY_REG);
	val &= VLV_GFX_CLK_FORCE_ON_BIT;
	val |= s->gtlc_survive & ~VLV_GFX_CLK_FORCE_ON_BIT;
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GTLC_SURVIVABILITY_REG, val);

	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_PMWGICZ, s->pmwgicz);

	/* Gunit-Display CZ करोमुख्य, 0x182028-0x1821CF */
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GU_CTL0, s->gu_ctl0);
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GU_CTL1, s->gu_ctl1);
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_PCBR, s->pcbr);
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GUNIT_CLOCK_GATE2, s->घड़ी_gate_dis2);
पूर्ण

अटल पूर्णांक vlv_रुको_क्रम_pw_status(काष्ठा drm_i915_निजी *i915,
				  u32 mask, u32 val)
अणु
	i915_reg_t reg = VLV_GTLC_PW_STATUS;
	u32 reg_value;
	पूर्णांक ret;

	/* The HW करोes not like us polling क्रम PW_STATUS frequently, so
	 * use the sleeping loop rather than risk the busy spin within
	 * पूर्णांकel_रुको_क्रम_रेजिस्टर().
	 *
	 * Transitioning between RC6 states should be at most 2ms (see
	 * valleyview_enable_rps) so use a 3ms समयout.
	 */
	ret = रुको_क्रम(((reg_value =
			 पूर्णांकel_uncore_पढ़ो_notrace(&i915->uncore, reg)) & mask)
		       == val, 3);

	/* just trace the final value */
	trace_i915_reg_rw(false, reg, reg_value, माप(reg_value), true);

	वापस ret;
पूर्ण

अटल पूर्णांक vlv_क्रमce_gfx_घड़ी(काष्ठा drm_i915_निजी *i915, bool क्रमce_on)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 val;
	पूर्णांक err;

	val = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_SURVIVABILITY_REG);
	val &= ~VLV_GFX_CLK_FORCE_ON_BIT;
	अगर (क्रमce_on)
		val |= VLV_GFX_CLK_FORCE_ON_BIT;
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GTLC_SURVIVABILITY_REG, val);

	अगर (!क्रमce_on)
		वापस 0;

	err = पूर्णांकel_रुको_क्रम_रेजिस्टर(uncore,
				      VLV_GTLC_SURVIVABILITY_REG,
				      VLV_GFX_CLK_STATUS_BIT,
				      VLV_GFX_CLK_STATUS_BIT,
				      20);
	अगर (err)
		drm_err(&i915->drm,
			"timeout waiting for GFX clock force-on (%08x)\n",
			पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_SURVIVABILITY_REG));

	वापस err;
पूर्ण

अटल पूर्णांक vlv_allow_gt_wake(काष्ठा drm_i915_निजी *i915, bool allow)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 mask;
	u32 val;
	पूर्णांक err;

	val = पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_WAKE_CTRL);
	val &= ~VLV_GTLC_ALLOWWAKEREQ;
	अगर (allow)
		val |= VLV_GTLC_ALLOWWAKEREQ;
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GTLC_WAKE_CTRL, val);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, VLV_GTLC_WAKE_CTRL);

	mask = VLV_GTLC_ALLOWWAKEACK;
	val = allow ? mask : 0;

	err = vlv_रुको_क्रम_pw_status(i915, mask, val);
	अगर (err)
		drm_err(&i915->drm, "timeout disabling GT waking\n");

	वापस err;
पूर्ण

अटल व्योम vlv_रुको_क्रम_gt_wells(काष्ठा drm_i915_निजी *dev_priv,
				  bool रुको_क्रम_on)
अणु
	u32 mask;
	u32 val;

	mask = VLV_GTLC_PW_MEDIA_STATUS_MASK | VLV_GTLC_PW_RENDER_STATUS_MASK;
	val = रुको_क्रम_on ? mask : 0;

	/*
	 * RC6 transitioning can be delayed up to 2 msec (see
	 * valleyview_enable_rps), use 3 msec क्रम safety.
	 *
	 * This can fail to turn off the rc6 अगर the GPU is stuck after a failed
	 * reset and we are trying to क्रमce the machine to sleep.
	 */
	अगर (vlv_रुको_क्रम_pw_status(dev_priv, mask, val))
		drm_dbg(&dev_priv->drm,
			"timeout waiting for GT wells to go %s\n",
			onoff(रुको_क्रम_on));
पूर्ण

अटल व्योम vlv_check_no_gt_access(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;

	अगर (!(पूर्णांकel_uncore_पढ़ो(uncore, VLV_GTLC_PW_STATUS) & VLV_GTLC_ALLOWWAKEERR))
		वापस;

	drm_dbg(&i915->drm, "GT register access while GT waking disabled\n");
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_GTLC_PW_STATUS, VLV_GTLC_ALLOWWAKEERR);
पूर्ण

पूर्णांक vlv_suspend_complete(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 mask;
	पूर्णांक err;

	अगर (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		वापस 0;

	/*
	 * Bspec defines the following GT well on flags as debug only, so
	 * करोn't treat them as hard failures.
	 */
	vlv_रुको_क्रम_gt_wells(dev_priv, false);

	mask = VLV_GTLC_RENDER_CTX_EXISTS | VLV_GTLC_MEDIA_CTX_EXISTS;
	drm_WARN_ON(&dev_priv->drm,
		    (पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, VLV_GTLC_WAKE_CTRL) & mask) != mask);

	vlv_check_no_gt_access(dev_priv);

	err = vlv_क्रमce_gfx_घड़ी(dev_priv, true);
	अगर (err)
		जाओ err1;

	err = vlv_allow_gt_wake(dev_priv, false);
	अगर (err)
		जाओ err2;

	vlv_save_gunit_s0ix_state(dev_priv);

	err = vlv_क्रमce_gfx_घड़ी(dev_priv, false);
	अगर (err)
		जाओ err2;

	वापस 0;

err2:
	/* For safety always re-enable waking and disable gfx घड़ी क्रमcing */
	vlv_allow_gt_wake(dev_priv, true);
err1:
	vlv_क्रमce_gfx_घड़ी(dev_priv, false);

	वापस err;
पूर्ण

पूर्णांक vlv_resume_prepare(काष्ठा drm_i915_निजी *dev_priv, bool rpm_resume)
अणु
	पूर्णांक err;
	पूर्णांक ret;

	अगर (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		वापस 0;

	/*
	 * If any of the steps fail just try to जारी, that's the best we
	 * can करो at this poपूर्णांक. Return the first error code (which will also
	 * leave RPM permanently disabled).
	 */
	ret = vlv_क्रमce_gfx_घड़ी(dev_priv, true);

	vlv_restore_gunit_s0ix_state(dev_priv);

	err = vlv_allow_gt_wake(dev_priv, true);
	अगर (!ret)
		ret = err;

	err = vlv_क्रमce_gfx_घड़ी(dev_priv, false);
	अगर (!ret)
		ret = err;

	vlv_check_no_gt_access(dev_priv);

	अगर (rpm_resume)
		पूर्णांकel_init_घड़ी_gating(dev_priv);

	वापस ret;
पूर्ण

पूर्णांक vlv_suspend_init(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (!IS_VALLEYVIEW(i915))
		वापस 0;

	/* we ग_लिखो all the values in the काष्ठा, so no need to zero it out */
	i915->vlv_s0ix_state = kदो_स्मृति(माप(*i915->vlv_s0ix_state),
				       GFP_KERNEL);
	अगर (!i915->vlv_s0ix_state)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम vlv_suspend_cleanup(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (!i915->vlv_s0ix_state)
		वापस;

	kमुक्त(i915->vlv_s0ix_state);
	i915->vlv_s0ix_state = शून्य;
पूर्ण
