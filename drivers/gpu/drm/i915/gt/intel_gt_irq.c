<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/sched/घड़ी.h>

#समावेश "i915_drv.h"
#समावेश "i915_irq.h"
#समावेश "intel_breadcrumbs.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_irq.h"
#समावेश "intel_lrc_reg.h"
#समावेश "intel_uncore.h"
#समावेश "intel_rps.h"

अटल व्योम guc_irq_handler(काष्ठा पूर्णांकel_guc *guc, u16 iir)
अणु
	अगर (iir & GUC_INTR_GUC2HOST)
		पूर्णांकel_guc_to_host_event_handler(guc);
पूर्ण

अटल व्योम
cs_irq_handler(काष्ठा पूर्णांकel_engine_cs *engine, u32 iir)
अणु
	bool tasklet = false;

	अगर (unlikely(iir & GT_CS_MASTER_ERROR_INTERRUPT)) अणु
		u32 eir;

		/* Upper 16b are the enabling mask, rsvd क्रम पूर्णांकernal errors */
		eir = ENGINE_READ(engine, RING_EIR) & GENMASK(15, 0);
		ENGINE_TRACE(engine, "CS error: %x\n", eir);

		/* Disable the error पूर्णांकerrupt until after the reset */
		अगर (likely(eir)) अणु
			ENGINE_WRITE(engine, RING_EMR, ~0u);
			ENGINE_WRITE(engine, RING_EIR, eir);
			WRITE_ONCE(engine->execlists.error_पूर्णांकerrupt, eir);
			tasklet = true;
		पूर्ण
	पूर्ण

	अगर (iir & GT_WAIT_SEMAPHORE_INTERRUPT) अणु
		WRITE_ONCE(engine->execlists.yield,
			   ENGINE_READ_FW(engine, RING_EXECLIST_STATUS_HI));
		ENGINE_TRACE(engine, "semaphore yield: %08x\n",
			     engine->execlists.yield);
		अगर (del_समयr(&engine->execlists.समयr))
			tasklet = true;
	पूर्ण

	अगर (iir & GT_CONTEXT_SWITCH_INTERRUPT)
		tasklet = true;

	अगर (iir & GT_RENDER_USER_INTERRUPT) अणु
		पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(engine);
		tasklet |= पूर्णांकel_engine_needs_bपढ़ोcrumb_tasklet(engine);
	पूर्ण

	अगर (tasklet)
		tasklet_hi_schedule(&engine->execlists.tasklet);
पूर्ण

अटल u32
gen11_gt_engine_identity(काष्ठा पूर्णांकel_gt *gt,
			 स्थिर अचिन्हित पूर्णांक bank, स्थिर अचिन्हित पूर्णांक bit)
अणु
	व्योम __iomem * स्थिर regs = gt->uncore->regs;
	u32 समयout_ts;
	u32 ident;

	lockdep_निश्चित_held(&gt->irq_lock);

	raw_reg_ग_लिखो(regs, GEN11_IIR_REG_SELECTOR(bank), BIT(bit));

	/*
	 * NB: Specs करो not specअगरy how दीर्घ to spin रुको,
	 * so we करो ~100us as an educated guess.
	 */
	समयout_ts = (local_घड़ी() >> 10) + 100;
	करो अणु
		ident = raw_reg_पढ़ो(regs, GEN11_INTR_IDENTITY_REG(bank));
	पूर्ण जबतक (!(ident & GEN11_INTR_DATA_VALID) &&
		 !समय_after32(local_घड़ी() >> 10, समयout_ts));

	अगर (unlikely(!(ident & GEN11_INTR_DATA_VALID))) अणु
		DRM_ERROR("INTR_IDENTITY_REG%u:%u 0x%08x not valid!\n",
			  bank, bit, ident);
		वापस 0;
	पूर्ण

	raw_reg_ग_लिखो(regs, GEN11_INTR_IDENTITY_REG(bank),
		      GEN11_INTR_DATA_VALID);

	वापस ident;
पूर्ण

अटल व्योम
gen11_other_irq_handler(काष्ठा पूर्णांकel_gt *gt, स्थिर u8 instance,
			स्थिर u16 iir)
अणु
	अगर (instance == OTHER_GUC_INSTANCE)
		वापस guc_irq_handler(&gt->uc.guc, iir);

	अगर (instance == OTHER_GTPM_INSTANCE)
		वापस gen11_rps_irq_handler(&gt->rps, iir);

	WARN_ONCE(1, "unhandled other interrupt instance=0x%x, iir=0x%x\n",
		  instance, iir);
पूर्ण

अटल व्योम
gen11_engine_irq_handler(काष्ठा पूर्णांकel_gt *gt, स्थिर u8 class,
			 स्थिर u8 instance, स्थिर u16 iir)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;

	अगर (instance <= MAX_ENGINE_INSTANCE)
		engine = gt->engine_class[class][instance];
	अन्यथा
		engine = शून्य;

	अगर (likely(engine))
		वापस cs_irq_handler(engine, iir);

	WARN_ONCE(1, "unhandled engine interrupt class=0x%x, instance=0x%x\n",
		  class, instance);
पूर्ण

अटल व्योम
gen11_gt_identity_handler(काष्ठा पूर्णांकel_gt *gt, स्थिर u32 identity)
अणु
	स्थिर u8 class = GEN11_INTR_ENGINE_CLASS(identity);
	स्थिर u8 instance = GEN11_INTR_ENGINE_INSTANCE(identity);
	स्थिर u16 पूर्णांकr = GEN11_INTR_ENGINE_INTR(identity);

	अगर (unlikely(!पूर्णांकr))
		वापस;

	अगर (class <= COPY_ENGINE_CLASS)
		वापस gen11_engine_irq_handler(gt, class, instance, पूर्णांकr);

	अगर (class == OTHER_CLASS)
		वापस gen11_other_irq_handler(gt, instance, पूर्णांकr);

	WARN_ONCE(1, "unknown interrupt class=0x%x, instance=0x%x, intr=0x%x\n",
		  class, instance, पूर्णांकr);
पूर्ण

अटल व्योम
gen11_gt_bank_handler(काष्ठा पूर्णांकel_gt *gt, स्थिर अचिन्हित पूर्णांक bank)
अणु
	व्योम __iomem * स्थिर regs = gt->uncore->regs;
	अचिन्हित दीर्घ पूर्णांकr_dw;
	अचिन्हित पूर्णांक bit;

	lockdep_निश्चित_held(&gt->irq_lock);

	पूर्णांकr_dw = raw_reg_पढ़ो(regs, GEN11_GT_INTR_DW(bank));

	क्रम_each_set_bit(bit, &पूर्णांकr_dw, 32) अणु
		स्थिर u32 ident = gen11_gt_engine_identity(gt, bank, bit);

		gen11_gt_identity_handler(gt, ident);
	पूर्ण

	/* Clear must be after shared has been served क्रम engine */
	raw_reg_ग_लिखो(regs, GEN11_GT_INTR_DW(bank), पूर्णांकr_dw);
पूर्ण

व्योम gen11_gt_irq_handler(काष्ठा पूर्णांकel_gt *gt, स्थिर u32 master_ctl)
अणु
	अचिन्हित पूर्णांक bank;

	spin_lock(&gt->irq_lock);

	क्रम (bank = 0; bank < 2; bank++) अणु
		अगर (master_ctl & GEN11_GT_DW_IRQ(bank))
			gen11_gt_bank_handler(gt, bank);
	पूर्ण

	spin_unlock(&gt->irq_lock);
पूर्ण

bool gen11_gt_reset_one_iir(काष्ठा पूर्णांकel_gt *gt,
			    स्थिर अचिन्हित पूर्णांक bank, स्थिर अचिन्हित पूर्णांक bit)
अणु
	व्योम __iomem * स्थिर regs = gt->uncore->regs;
	u32 dw;

	lockdep_निश्चित_held(&gt->irq_lock);

	dw = raw_reg_पढ़ो(regs, GEN11_GT_INTR_DW(bank));
	अगर (dw & BIT(bit)) अणु
		/*
		 * According to the BSpec, DW_IIR bits cannot be cleared without
		 * first servicing the Selector & Shared IIR रेजिस्टरs.
		 */
		gen11_gt_engine_identity(gt, bank, bit);

		/*
		 * We locked GT INT DW by पढ़ोing it. If we want to (try
		 * to) recover from this successfully, we need to clear
		 * our bit, otherwise we are locking the रेजिस्टर क्रम
		 * everybody.
		 */
		raw_reg_ग_लिखो(regs, GEN11_GT_INTR_DW(bank), BIT(bit));

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम gen11_gt_irq_reset(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	/* Disable RCS, BCS, VCS and VECS class engines. */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_RENDER_COPY_INTR_ENABLE, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_VCS_VECS_INTR_ENABLE,	  0);

	/* Restore masks irqs on RCS, BCS, VCS and VECS engines. */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_RCS0_RSVD_INTR_MASK,	~0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_BCS_RSVD_INTR_MASK,	~0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_VCS0_VCS1_INTR_MASK,	~0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_VCS2_VCS3_INTR_MASK,	~0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_VECS0_VECS1_INTR_MASK,	~0);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_GPM_WGBOXPERF_INTR_ENABLE, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_GPM_WGBOXPERF_INTR_MASK,  ~0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_GUC_SG_INTR_ENABLE, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_GUC_SG_INTR_MASK,  ~0);
पूर्ण

व्योम gen11_gt_irq_postinstall(काष्ठा पूर्णांकel_gt *gt)
अणु
	स्थिर u32 irqs =
		GT_CS_MASTER_ERROR_INTERRUPT |
		GT_RENDER_USER_INTERRUPT |
		GT_CONTEXT_SWITCH_INTERRUPT |
		GT_WAIT_SEMAPHORE_INTERRUPT;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	स्थिर u32 dmask = irqs << 16 | irqs;
	स्थिर u32 smask = irqs << 16;

	BUILD_BUG_ON(irqs & 0xffff0000);

	/* Enable RCS, BCS, VCS and VECS class पूर्णांकerrupts. */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_RENDER_COPY_INTR_ENABLE, dmask);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_VCS_VECS_INTR_ENABLE, dmask);

	/* Unmask irqs on RCS, BCS, VCS and VECS engines. */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_RCS0_RSVD_INTR_MASK, ~smask);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_BCS_RSVD_INTR_MASK, ~smask);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_VCS0_VCS1_INTR_MASK, ~dmask);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_VCS2_VCS3_INTR_MASK, ~dmask);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_VECS0_VECS1_INTR_MASK, ~dmask);

	/*
	 * RPS पूर्णांकerrupts will get enabled/disabled on demand when RPS itself
	 * is enabled/disabled.
	 */
	gt->pm_ier = 0x0;
	gt->pm_imr = ~gt->pm_ier;
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_GPM_WGBOXPERF_INTR_ENABLE, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_GPM_WGBOXPERF_INTR_MASK,  ~0);

	/* Same thing क्रम GuC पूर्णांकerrupts */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_GUC_SG_INTR_ENABLE, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_GUC_SG_INTR_MASK,  ~0);
पूर्ण

व्योम gen5_gt_irq_handler(काष्ठा पूर्णांकel_gt *gt, u32 gt_iir)
अणु
	अगर (gt_iir & GT_RENDER_USER_INTERRUPT)
		पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(gt->engine_class[RENDER_CLASS][0]);
	अगर (gt_iir & ILK_BSD_USER_INTERRUPT)
		पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(gt->engine_class[VIDEO_DECODE_CLASS][0]);
पूर्ण

अटल व्योम gen7_parity_error_irq_handler(काष्ठा पूर्णांकel_gt *gt, u32 iir)
अणु
	अगर (!HAS_L3_DPF(gt->i915))
		वापस;

	spin_lock(&gt->irq_lock);
	gen5_gt_disable_irq(gt, GT_PARITY_ERROR(gt->i915));
	spin_unlock(&gt->irq_lock);

	अगर (iir & GT_RENDER_L3_PARITY_ERROR_INTERRUPT_S1)
		gt->i915->l3_parity.which_slice |= 1 << 1;

	अगर (iir & GT_RENDER_L3_PARITY_ERROR_INTERRUPT)
		gt->i915->l3_parity.which_slice |= 1 << 0;

	schedule_work(&gt->i915->l3_parity.error_work);
पूर्ण

व्योम gen6_gt_irq_handler(काष्ठा पूर्णांकel_gt *gt, u32 gt_iir)
अणु
	अगर (gt_iir & GT_RENDER_USER_INTERRUPT)
		पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(gt->engine_class[RENDER_CLASS][0]);
	अगर (gt_iir & GT_BSD_USER_INTERRUPT)
		पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(gt->engine_class[VIDEO_DECODE_CLASS][0]);
	अगर (gt_iir & GT_BLT_USER_INTERRUPT)
		पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(gt->engine_class[COPY_ENGINE_CLASS][0]);

	अगर (gt_iir & (GT_BLT_CS_ERROR_INTERRUPT |
		      GT_BSD_CS_ERROR_INTERRUPT |
		      GT_CS_MASTER_ERROR_INTERRUPT))
		DRM_DEBUG("Command parser error, gt_iir 0x%08x\n", gt_iir);

	अगर (gt_iir & GT_PARITY_ERROR(gt->i915))
		gen7_parity_error_irq_handler(gt, gt_iir);
पूर्ण

व्योम gen8_gt_irq_handler(काष्ठा पूर्णांकel_gt *gt, u32 master_ctl)
अणु
	व्योम __iomem * स्थिर regs = gt->uncore->regs;
	u32 iir;

	अगर (master_ctl & (GEN8_GT_RCS_IRQ | GEN8_GT_BCS_IRQ)) अणु
		iir = raw_reg_पढ़ो(regs, GEN8_GT_IIR(0));
		अगर (likely(iir)) अणु
			cs_irq_handler(gt->engine_class[RENDER_CLASS][0],
				       iir >> GEN8_RCS_IRQ_SHIFT);
			cs_irq_handler(gt->engine_class[COPY_ENGINE_CLASS][0],
				       iir >> GEN8_BCS_IRQ_SHIFT);
			raw_reg_ग_लिखो(regs, GEN8_GT_IIR(0), iir);
		पूर्ण
	पूर्ण

	अगर (master_ctl & (GEN8_GT_VCS0_IRQ | GEN8_GT_VCS1_IRQ)) अणु
		iir = raw_reg_पढ़ो(regs, GEN8_GT_IIR(1));
		अगर (likely(iir)) अणु
			cs_irq_handler(gt->engine_class[VIDEO_DECODE_CLASS][0],
				       iir >> GEN8_VCS0_IRQ_SHIFT);
			cs_irq_handler(gt->engine_class[VIDEO_DECODE_CLASS][1],
				       iir >> GEN8_VCS1_IRQ_SHIFT);
			raw_reg_ग_लिखो(regs, GEN8_GT_IIR(1), iir);
		पूर्ण
	पूर्ण

	अगर (master_ctl & GEN8_GT_VECS_IRQ) अणु
		iir = raw_reg_पढ़ो(regs, GEN8_GT_IIR(3));
		अगर (likely(iir)) अणु
			cs_irq_handler(gt->engine_class[VIDEO_ENHANCEMENT_CLASS][0],
				       iir >> GEN8_VECS_IRQ_SHIFT);
			raw_reg_ग_लिखो(regs, GEN8_GT_IIR(3), iir);
		पूर्ण
	पूर्ण

	अगर (master_ctl & (GEN8_GT_PM_IRQ | GEN8_GT_GUC_IRQ)) अणु
		iir = raw_reg_पढ़ो(regs, GEN8_GT_IIR(2));
		अगर (likely(iir)) अणु
			gen6_rps_irq_handler(&gt->rps, iir);
			guc_irq_handler(&gt->uc.guc, iir >> 16);
			raw_reg_ग_लिखो(regs, GEN8_GT_IIR(2), iir);
		पूर्ण
	पूर्ण
पूर्ण

व्योम gen8_gt_irq_reset(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	GEN8_IRQ_RESET_NDX(uncore, GT, 0);
	GEN8_IRQ_RESET_NDX(uncore, GT, 1);
	GEN8_IRQ_RESET_NDX(uncore, GT, 2);
	GEN8_IRQ_RESET_NDX(uncore, GT, 3);
पूर्ण

व्योम gen8_gt_irq_postinstall(काष्ठा पूर्णांकel_gt *gt)
अणु
	/* These are पूर्णांकerrupts we'll toggle with the ring mask रेजिस्टर */
	स्थिर u32 irqs =
		GT_CS_MASTER_ERROR_INTERRUPT |
		GT_RENDER_USER_INTERRUPT |
		GT_CONTEXT_SWITCH_INTERRUPT |
		GT_WAIT_SEMAPHORE_INTERRUPT;
	स्थिर u32 gt_पूर्णांकerrupts[] = अणु
		irqs << GEN8_RCS_IRQ_SHIFT | irqs << GEN8_BCS_IRQ_SHIFT,
		irqs << GEN8_VCS0_IRQ_SHIFT | irqs << GEN8_VCS1_IRQ_SHIFT,
		0,
		irqs << GEN8_VECS_IRQ_SHIFT,
	पूर्ण;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	gt->pm_ier = 0x0;
	gt->pm_imr = ~gt->pm_ier;
	GEN8_IRQ_INIT_NDX(uncore, GT, 0, ~gt_पूर्णांकerrupts[0], gt_पूर्णांकerrupts[0]);
	GEN8_IRQ_INIT_NDX(uncore, GT, 1, ~gt_पूर्णांकerrupts[1], gt_पूर्णांकerrupts[1]);
	/*
	 * RPS पूर्णांकerrupts will get enabled/disabled on demand when RPS itself
	 * is enabled/disabled. Same wil be the हाल क्रम GuC पूर्णांकerrupts.
	 */
	GEN8_IRQ_INIT_NDX(uncore, GT, 2, gt->pm_imr, gt->pm_ier);
	GEN8_IRQ_INIT_NDX(uncore, GT, 3, ~gt_पूर्णांकerrupts[3], gt_पूर्णांकerrupts[3]);
पूर्ण

अटल व्योम gen5_gt_update_irq(काष्ठा पूर्णांकel_gt *gt,
			       u32 पूर्णांकerrupt_mask,
			       u32 enabled_irq_mask)
अणु
	lockdep_निश्चित_held(&gt->irq_lock);

	GEM_BUG_ON(enabled_irq_mask & ~पूर्णांकerrupt_mask);

	gt->gt_imr &= ~पूर्णांकerrupt_mask;
	gt->gt_imr |= (~enabled_irq_mask & पूर्णांकerrupt_mask);
	पूर्णांकel_uncore_ग_लिखो(gt->uncore, GTIMR, gt->gt_imr);
पूर्ण

व्योम gen5_gt_enable_irq(काष्ठा पूर्णांकel_gt *gt, u32 mask)
अणु
	gen5_gt_update_irq(gt, mask, mask);
	पूर्णांकel_uncore_posting_पढ़ो_fw(gt->uncore, GTIMR);
पूर्ण

व्योम gen5_gt_disable_irq(काष्ठा पूर्णांकel_gt *gt, u32 mask)
अणु
	gen5_gt_update_irq(gt, mask, 0);
पूर्ण

व्योम gen5_gt_irq_reset(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	GEN3_IRQ_RESET(uncore, GT);
	अगर (INTEL_GEN(gt->i915) >= 6)
		GEN3_IRQ_RESET(uncore, GEN6_PM);
पूर्ण

व्योम gen5_gt_irq_postinstall(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 pm_irqs = 0;
	u32 gt_irqs = 0;

	gt->gt_imr = ~0;
	अगर (HAS_L3_DPF(gt->i915)) अणु
		/* L3 parity पूर्णांकerrupt is always unmasked. */
		gt->gt_imr = ~GT_PARITY_ERROR(gt->i915);
		gt_irqs |= GT_PARITY_ERROR(gt->i915);
	पूर्ण

	gt_irqs |= GT_RENDER_USER_INTERRUPT;
	अगर (IS_GEN(gt->i915, 5))
		gt_irqs |= ILK_BSD_USER_INTERRUPT;
	अन्यथा
		gt_irqs |= GT_BLT_USER_INTERRUPT | GT_BSD_USER_INTERRUPT;

	GEN3_IRQ_INIT(uncore, GT, gt->gt_imr, gt_irqs);

	अगर (INTEL_GEN(gt->i915) >= 6) अणु
		/*
		 * RPS पूर्णांकerrupts will get enabled/disabled on demand when RPS
		 * itself is enabled/disabled.
		 */
		अगर (HAS_ENGINE(gt, VECS0)) अणु
			pm_irqs |= PM_VEBOX_USER_INTERRUPT;
			gt->pm_ier |= PM_VEBOX_USER_INTERRUPT;
		पूर्ण

		gt->pm_imr = 0xffffffff;
		GEN3_IRQ_INIT(uncore, GEN6_PM, gt->pm_imr, pm_irqs);
	पूर्ण
पूर्ण
