<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <drm/i915_drm.h>

#समावेश "i915_drv.h"
#समावेश "intel_breadcrumbs.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_clock_utils.h"
#समावेश "intel_gt_irq.h"
#समावेश "intel_gt_pm_irq.h"
#समावेश "intel_rps.h"
#समावेश "intel_sideband.h"
#समावेश "../../../platform/x86/intel_ips.h"

#घोषणा BUSY_MAX_EI	20u /* ms */

/*
 * Lock protecting IPS related data काष्ठाures
 */
अटल DEFINE_SPINLOCK(mchdev_lock);

अटल काष्ठा पूर्णांकel_gt *rps_to_gt(काष्ठा पूर्णांकel_rps *rps)
अणु
	वापस container_of(rps, काष्ठा पूर्णांकel_gt, rps);
पूर्ण

अटल काष्ठा drm_i915_निजी *rps_to_i915(काष्ठा पूर्णांकel_rps *rps)
अणु
	वापस rps_to_gt(rps)->i915;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore *rps_to_uncore(काष्ठा पूर्णांकel_rps *rps)
अणु
	वापस rps_to_gt(rps)->uncore;
पूर्ण

अटल u32 rps_pm_sanitize_mask(काष्ठा पूर्णांकel_rps *rps, u32 mask)
अणु
	वापस mask & ~rps->pm_पूर्णांकrmsk_mbz;
पूर्ण

अटल व्योम set(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u32 val)
अणु
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, reg, val);
पूर्ण

अटल व्योम rps_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा पूर्णांकel_rps *rps = from_समयr(rps, t, समयr);
	काष्ठा पूर्णांकel_engine_cs *engine;
	kसमय_प्रकार dt, last, बारtamp;
	क्रमागत पूर्णांकel_engine_id id;
	s64 max_busy[3] = अणुपूर्ण;

	बारtamp = 0;
	क्रम_each_engine(engine, rps_to_gt(rps), id) अणु
		s64 busy;
		पूर्णांक i;

		dt = पूर्णांकel_engine_get_busy_समय(engine, &बारtamp);
		last = engine->stats.rps;
		engine->stats.rps = dt;

		busy = kसमय_प्रकारo_ns(kसमय_sub(dt, last));
		क्रम (i = 0; i < ARRAY_SIZE(max_busy); i++) अणु
			अगर (busy > max_busy[i])
				swap(busy, max_busy[i]);
		पूर्ण
	पूर्ण
	last = rps->pm_बारtamp;
	rps->pm_बारtamp = बारtamp;

	अगर (पूर्णांकel_rps_is_active(rps)) अणु
		s64 busy;
		पूर्णांक i;

		dt = kसमय_sub(बारtamp, last);

		/*
		 * Our goal is to evaluate each engine independently, so we run
		 * at the lowest घड़ीs required to sustain the heaviest
		 * workload. However, a task may be split पूर्णांकo sequential
		 * dependent operations across a set of engines, such that
		 * the independent contributions करो not account क्रम high load,
		 * but overall the task is GPU bound. For example, consider
		 * video decode on vcs followed by colour post-processing
		 * on vecs, followed by general post-processing on rcs.
		 * Since multi-engines being active करोes imply a single
		 * continuous workload across all engines, we hedge our
		 * bets by only contributing a factor of the distributed
		 * load पूर्णांकo our busyness calculation.
		 */
		busy = max_busy[0];
		क्रम (i = 1; i < ARRAY_SIZE(max_busy); i++) अणु
			अगर (!max_busy[i])
				अवरोध;

			busy += भाग_u64(max_busy[i], 1 << i);
		पूर्ण
		GT_TRACE(rps_to_gt(rps),
			 "busy:%lld [%d%%], max:[%lld, %lld, %lld], interval:%d\n",
			 busy, (पूर्णांक)भाग64_u64(100 * busy, dt),
			 max_busy[0], max_busy[1], max_busy[2],
			 rps->pm_पूर्णांकerval);

		अगर (100 * busy > rps->घातer.up_threshold * dt &&
		    rps->cur_freq < rps->max_freq_softlimit) अणु
			rps->pm_iir |= GEN6_PM_RP_UP_THRESHOLD;
			rps->pm_पूर्णांकerval = 1;
			schedule_work(&rps->work);
		पूर्ण अन्यथा अगर (100 * busy < rps->घातer.करोwn_threshold * dt &&
			   rps->cur_freq > rps->min_freq_softlimit) अणु
			rps->pm_iir |= GEN6_PM_RP_DOWN_THRESHOLD;
			rps->pm_पूर्णांकerval = 1;
			schedule_work(&rps->work);
		पूर्ण अन्यथा अणु
			rps->last_adj = 0;
		पूर्ण

		mod_समयr(&rps->समयr,
			  jअगरfies + msecs_to_jअगरfies(rps->pm_पूर्णांकerval));
		rps->pm_पूर्णांकerval = min(rps->pm_पूर्णांकerval * 2, BUSY_MAX_EI);
	पूर्ण
पूर्ण

अटल व्योम rps_start_समयr(काष्ठा पूर्णांकel_rps *rps)
अणु
	rps->pm_बारtamp = kसमय_sub(kसमय_get(), rps->pm_बारtamp);
	rps->pm_पूर्णांकerval = 1;
	mod_समयr(&rps->समयr, jअगरfies + 1);
पूर्ण

अटल व्योम rps_stop_समयr(काष्ठा पूर्णांकel_rps *rps)
अणु
	del_समयr_sync(&rps->समयr);
	rps->pm_बारtamp = kसमय_sub(kसमय_get(), rps->pm_बारtamp);
	cancel_work_sync(&rps->work);
पूर्ण

अटल u32 rps_pm_mask(काष्ठा पूर्णांकel_rps *rps, u8 val)
अणु
	u32 mask = 0;

	/* We use UP_EI_EXPIRED पूर्णांकerrupts क्रम both up/करोwn in manual mode */
	अगर (val > rps->min_freq_softlimit)
		mask |= (GEN6_PM_RP_UP_EI_EXPIRED |
			 GEN6_PM_RP_DOWN_THRESHOLD |
			 GEN6_PM_RP_DOWN_TIMEOUT);

	अगर (val < rps->max_freq_softlimit)
		mask |= GEN6_PM_RP_UP_EI_EXPIRED | GEN6_PM_RP_UP_THRESHOLD;

	mask &= rps->pm_events;

	वापस rps_pm_sanitize_mask(rps, ~mask);
पूर्ण

अटल व्योम rps_reset_ei(काष्ठा पूर्णांकel_rps *rps)
अणु
	स_रखो(&rps->ei, 0, माप(rps->ei));
पूर्ण

अटल व्योम rps_enable_पूर्णांकerrupts(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);

	GT_TRACE(gt, "interrupts:on rps->pm_events: %x, rps_pm_mask:%x\n",
		 rps->pm_events, rps_pm_mask(rps, rps->last_freq));

	rps_reset_ei(rps);

	spin_lock_irq(&gt->irq_lock);
	gen6_gt_pm_enable_irq(gt, rps->pm_events);
	spin_unlock_irq(&gt->irq_lock);

	पूर्णांकel_uncore_ग_लिखो(gt->uncore,
			   GEN6_PMINTRMSK, rps_pm_mask(rps, rps->last_freq));
पूर्ण

अटल व्योम gen6_rps_reset_पूर्णांकerrupts(काष्ठा पूर्णांकel_rps *rps)
अणु
	gen6_gt_pm_reset_iir(rps_to_gt(rps), GEN6_PM_RPS_EVENTS);
पूर्ण

अटल व्योम gen11_rps_reset_पूर्णांकerrupts(काष्ठा पूर्णांकel_rps *rps)
अणु
	जबतक (gen11_gt_reset_one_iir(rps_to_gt(rps), 0, GEN11_GTPM))
		;
पूर्ण

अटल व्योम rps_reset_पूर्णांकerrupts(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);

	spin_lock_irq(&gt->irq_lock);
	अगर (INTEL_GEN(gt->i915) >= 11)
		gen11_rps_reset_पूर्णांकerrupts(rps);
	अन्यथा
		gen6_rps_reset_पूर्णांकerrupts(rps);

	rps->pm_iir = 0;
	spin_unlock_irq(&gt->irq_lock);
पूर्ण

अटल व्योम rps_disable_पूर्णांकerrupts(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);

	पूर्णांकel_uncore_ग_लिखो(gt->uncore,
			   GEN6_PMINTRMSK, rps_pm_sanitize_mask(rps, ~0u));

	spin_lock_irq(&gt->irq_lock);
	gen6_gt_pm_disable_irq(gt, GEN6_PM_RPS_EVENTS);
	spin_unlock_irq(&gt->irq_lock);

	पूर्णांकel_synchronize_irq(gt->i915);

	/*
	 * Now that we will not be generating any more work, flush any
	 * outstanding tasks. As we are called on the RPS idle path,
	 * we will reset the GPU to minimum frequencies, so the current
	 * state of the worker can be discarded.
	 */
	cancel_work_sync(&rps->work);

	rps_reset_पूर्णांकerrupts(rps);
	GT_TRACE(gt, "interrupts:off\n");
पूर्ण

अटल स्थिर काष्ठा cparams अणु
	u16 i;
	u16 t;
	u16 m;
	u16 c;
पूर्ण cparams[] = अणु
	अणु 1, 1333, 301, 28664 पूर्ण,
	अणु 1, 1066, 294, 24460 पूर्ण,
	अणु 1, 800, 294, 25192 पूर्ण,
	अणु 0, 1333, 276, 27605 पूर्ण,
	अणु 0, 1066, 276, 27605 पूर्ण,
	अणु 0, 800, 231, 23784 पूर्ण,
पूर्ण;

अटल व्योम gen5_rps_init(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	u8 fmax, fmin, fstart;
	u32 rgvmodectl;
	पूर्णांक c_m, i;

	अगर (i915->fsb_freq <= 3200)
		c_m = 0;
	अन्यथा अगर (i915->fsb_freq <= 4800)
		c_m = 1;
	अन्यथा
		c_m = 2;

	क्रम (i = 0; i < ARRAY_SIZE(cparams); i++) अणु
		अगर (cparams[i].i == c_m && cparams[i].t == i915->mem_freq) अणु
			rps->ips.m = cparams[i].m;
			rps->ips.c = cparams[i].c;
			अवरोध;
		पूर्ण
	पूर्ण

	rgvmodectl = पूर्णांकel_uncore_पढ़ो(uncore, MEMMODECTL);

	/* Set up min, max, and cur क्रम पूर्णांकerrupt handling */
	fmax = (rgvmodectl & MEMMODE_FMAX_MASK) >> MEMMODE_FMAX_SHIFT;
	fmin = (rgvmodectl & MEMMODE_FMIN_MASK);
	fstart = (rgvmodectl & MEMMODE_FSTART_MASK) >>
		MEMMODE_FSTART_SHIFT;
	drm_dbg(&i915->drm, "fmax: %d, fmin: %d, fstart: %d\n",
		fmax, fmin, fstart);

	rps->min_freq = fmax;
	rps->efficient_freq = fstart;
	rps->max_freq = fmin;
पूर्ण

अटल अचिन्हित दीर्घ
__ips_chipset_val(काष्ठा पूर्णांकel_ips *ips)
अणु
	काष्ठा पूर्णांकel_uncore *uncore =
		rps_to_uncore(container_of(ips, काष्ठा पूर्णांकel_rps, ips));
	अचिन्हित दीर्घ now = jअगरfies_to_msecs(jअगरfies), dt;
	अचिन्हित दीर्घ result;
	u64 total, delta;

	lockdep_निश्चित_held(&mchdev_lock);

	/*
	 * Prevent भागision-by-zero अगर we are asking too fast.
	 * Also, we करोn't get पूर्णांकeresting results अगर we are polling
	 * faster than once in 10ms, so just वापस the saved value
	 * in such हालs.
	 */
	dt = now - ips->last_समय1;
	अगर (dt <= 10)
		वापस ips->chipset_घातer;

	/* FIXME: handle per-counter overflow */
	total = पूर्णांकel_uncore_पढ़ो(uncore, DMIEC);
	total += पूर्णांकel_uncore_पढ़ो(uncore, DDREC);
	total += पूर्णांकel_uncore_पढ़ो(uncore, CSIEC);

	delta = total - ips->last_count1;

	result = भाग_u64(भाग_u64(ips->m * delta, dt) + ips->c, 10);

	ips->last_count1 = total;
	ips->last_समय1 = now;

	ips->chipset_घातer = result;

	वापस result;
पूर्ण

अटल अचिन्हित दीर्घ ips_mch_val(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	अचिन्हित पूर्णांक m, x, b;
	u32 tsfs;

	tsfs = पूर्णांकel_uncore_पढ़ो(uncore, TSFS);
	x = पूर्णांकel_uncore_पढ़ो8(uncore, TR1);

	b = tsfs & TSFS_INTR_MASK;
	m = (tsfs & TSFS_SLOPE_MASK) >> TSFS_SLOPE_SHIFT;

	वापस m * x / 127 - b;
पूर्ण

अटल पूर्णांक _pxvid_to_vd(u8 pxvid)
अणु
	अगर (pxvid == 0)
		वापस 0;

	अगर (pxvid >= 8 && pxvid < 31)
		pxvid = 31;

	वापस (pxvid + 2) * 125;
पूर्ण

अटल u32 pvid_to_extvid(काष्ठा drm_i915_निजी *i915, u8 pxvid)
अणु
	स्थिर पूर्णांक vd = _pxvid_to_vd(pxvid);

	अगर (INTEL_INFO(i915)->is_mobile)
		वापस max(vd - 1125, 0);

	वापस vd;
पूर्ण

अटल व्योम __gen5_ips_update(काष्ठा पूर्णांकel_ips *ips)
अणु
	काष्ठा पूर्णांकel_uncore *uncore =
		rps_to_uncore(container_of(ips, काष्ठा पूर्णांकel_rps, ips));
	u64 now, delta, dt;
	u32 count;

	lockdep_निश्चित_held(&mchdev_lock);

	now = kसमय_get_raw_ns();
	dt = now - ips->last_समय2;
	करो_भाग(dt, NSEC_PER_MSEC);

	/* Don't भागide by 0 */
	अगर (dt <= 10)
		वापस;

	count = पूर्णांकel_uncore_पढ़ो(uncore, GFXEC);
	delta = count - ips->last_count2;

	ips->last_count2 = count;
	ips->last_समय2 = now;

	/* More magic स्थिरants... */
	ips->gfx_घातer = भाग_u64(delta * 1181, dt * 10);
पूर्ण

अटल व्योम gen5_rps_update(काष्ठा पूर्णांकel_rps *rps)
अणु
	spin_lock_irq(&mchdev_lock);
	__gen5_ips_update(&rps->ips);
	spin_unlock_irq(&mchdev_lock);
पूर्ण

अटल अचिन्हित पूर्णांक gen5_invert_freq(काष्ठा पूर्णांकel_rps *rps,
				     अचिन्हित पूर्णांक val)
अणु
	/* Invert the frequency bin पूर्णांकo an ips delay */
	val = rps->max_freq - val;
	val = rps->min_freq + val;

	वापस val;
पूर्ण

अटल पूर्णांक __gen5_rps_set(काष्ठा पूर्णांकel_rps *rps, u8 val)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	u16 rgvswctl;

	lockdep_निश्चित_held(&mchdev_lock);

	rgvswctl = पूर्णांकel_uncore_पढ़ो16(uncore, MEMSWCTL);
	अगर (rgvswctl & MEMCTL_CMD_STS) अणु
		DRM_DEBUG("gpu busy, RCS change rejected\n");
		वापस -EBUSY; /* still busy with another command */
	पूर्ण

	/* Invert the frequency bin पूर्णांकo an ips delay */
	val = gen5_invert_freq(rps, val);

	rgvswctl =
		(MEMCTL_CMD_CHFREQ << MEMCTL_CMD_SHIFT) |
		(val << MEMCTL_FREQ_SHIFT) |
		MEMCTL_SFCAVM;
	पूर्णांकel_uncore_ग_लिखो16(uncore, MEMSWCTL, rgvswctl);
	पूर्णांकel_uncore_posting_पढ़ो16(uncore, MEMSWCTL);

	rgvswctl |= MEMCTL_CMD_STS;
	पूर्णांकel_uncore_ग_लिखो16(uncore, MEMSWCTL, rgvswctl);

	वापस 0;
पूर्ण

अटल पूर्णांक gen5_rps_set(काष्ठा पूर्णांकel_rps *rps, u8 val)
अणु
	पूर्णांक err;

	spin_lock_irq(&mchdev_lock);
	err = __gen5_rps_set(rps, val);
	spin_unlock_irq(&mchdev_lock);

	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ पूर्णांकel_pxfreq(u32 vidfreq)
अणु
	पूर्णांक भाग = (vidfreq & 0x3f0000) >> 16;
	पूर्णांक post = (vidfreq & 0x3000) >> 12;
	पूर्णांक pre = (vidfreq & 0x7);

	अगर (!pre)
		वापस 0;

	वापस भाग * 133333 / (pre << post);
पूर्ण

अटल अचिन्हित पूर्णांक init_emon(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u8 pxw[16];
	पूर्णांक i;

	/* Disable to program */
	पूर्णांकel_uncore_ग_लिखो(uncore, ECR, 0);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, ECR);

	/* Program energy weights क्रम various events */
	पूर्णांकel_uncore_ग_लिखो(uncore, SDEW, 0x15040d00);
	पूर्णांकel_uncore_ग_लिखो(uncore, CSIEW0, 0x007f0000);
	पूर्णांकel_uncore_ग_लिखो(uncore, CSIEW1, 0x1e220004);
	पूर्णांकel_uncore_ग_लिखो(uncore, CSIEW2, 0x04000004);

	क्रम (i = 0; i < 5; i++)
		पूर्णांकel_uncore_ग_लिखो(uncore, PEW(i), 0);
	क्रम (i = 0; i < 3; i++)
		पूर्णांकel_uncore_ग_लिखो(uncore, DEW(i), 0);

	/* Program P-state weights to account क्रम frequency घातer adjusपंचांगent */
	क्रम (i = 0; i < 16; i++) अणु
		u32 pxvidfreq = पूर्णांकel_uncore_पढ़ो(uncore, PXVFREQ(i));
		अचिन्हित पूर्णांक freq = पूर्णांकel_pxfreq(pxvidfreq);
		अचिन्हित पूर्णांक vid =
			(pxvidfreq & PXVFREQ_PX_MASK) >> PXVFREQ_PX_SHIFT;
		अचिन्हित पूर्णांक val;

		val = vid * vid * freq / 1000 * 255;
		val /= 127 * 127 * 900;

		pxw[i] = val;
	पूर्ण
	/* Render standby states get 0 weight */
	pxw[14] = 0;
	pxw[15] = 0;

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांकel_uncore_ग_लिखो(uncore, PXW(i),
				   pxw[i * 4 + 0] << 24 |
				   pxw[i * 4 + 1] << 16 |
				   pxw[i * 4 + 2] <<  8 |
				   pxw[i * 4 + 3] <<  0);
	पूर्ण

	/* Adjust magic regs to magic values (more experimental results) */
	पूर्णांकel_uncore_ग_लिखो(uncore, OGW0, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, OGW1, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, EG0, 0x00007f00);
	पूर्णांकel_uncore_ग_लिखो(uncore, EG1, 0x0000000e);
	पूर्णांकel_uncore_ग_लिखो(uncore, EG2, 0x000e0000);
	पूर्णांकel_uncore_ग_लिखो(uncore, EG3, 0x68000300);
	पूर्णांकel_uncore_ग_लिखो(uncore, EG4, 0x42000000);
	पूर्णांकel_uncore_ग_लिखो(uncore, EG5, 0x00140031);
	पूर्णांकel_uncore_ग_लिखो(uncore, EG6, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, EG7, 0);

	क्रम (i = 0; i < 8; i++)
		पूर्णांकel_uncore_ग_लिखो(uncore, PXWL(i), 0);

	/* Enable PMON + select events */
	पूर्णांकel_uncore_ग_लिखो(uncore, ECR, 0x80000019);

	वापस पूर्णांकel_uncore_पढ़ो(uncore, LCFUSE02) & LCFUSE_HIV_MASK;
पूर्ण

अटल bool gen5_rps_enable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	u8 fstart, vstart;
	u32 rgvmodectl;

	spin_lock_irq(&mchdev_lock);

	rgvmodectl = पूर्णांकel_uncore_पढ़ो(uncore, MEMMODECTL);

	/* Enable temp reporting */
	पूर्णांकel_uncore_ग_लिखो16(uncore, PMMISC,
			     पूर्णांकel_uncore_पढ़ो16(uncore, PMMISC) | MCPPCE_EN);
	पूर्णांकel_uncore_ग_लिखो16(uncore, TSC1,
			     पूर्णांकel_uncore_पढ़ो16(uncore, TSC1) | TSE);

	/* 100ms RC evaluation पूर्णांकervals */
	पूर्णांकel_uncore_ग_लिखो(uncore, RCUPEI, 100000);
	पूर्णांकel_uncore_ग_लिखो(uncore, RCDNEI, 100000);

	/* Set max/min thresholds to 90ms and 80ms respectively */
	पूर्णांकel_uncore_ग_लिखो(uncore, RCBMAXAVG, 90000);
	पूर्णांकel_uncore_ग_लिखो(uncore, RCBMINAVG, 80000);

	पूर्णांकel_uncore_ग_लिखो(uncore, MEMIHYST, 1);

	/* Set up min, max, and cur क्रम पूर्णांकerrupt handling */
	fstart = (rgvmodectl & MEMMODE_FSTART_MASK) >>
		MEMMODE_FSTART_SHIFT;

	vstart = (पूर्णांकel_uncore_पढ़ो(uncore, PXVFREQ(fstart)) &
		  PXVFREQ_PX_MASK) >> PXVFREQ_PX_SHIFT;

	पूर्णांकel_uncore_ग_लिखो(uncore,
			   MEMINTREN,
			   MEMINT_CX_SUPR_EN | MEMINT_EVAL_CHG_EN);

	पूर्णांकel_uncore_ग_लिखो(uncore, VIDSTART, vstart);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, VIDSTART);

	rgvmodectl |= MEMMODE_SWMODE_EN;
	पूर्णांकel_uncore_ग_लिखो(uncore, MEMMODECTL, rgvmodectl);

	अगर (रुको_क्रम_atomic((पूर्णांकel_uncore_पढ़ो(uncore, MEMSWCTL) &
			     MEMCTL_CMD_STS) == 0, 10))
		drm_err(&uncore->i915->drm,
			"stuck trying to change perf mode\n");
	mdelay(1);

	__gen5_rps_set(rps, rps->cur_freq);

	rps->ips.last_count1 = पूर्णांकel_uncore_पढ़ो(uncore, DMIEC);
	rps->ips.last_count1 += पूर्णांकel_uncore_पढ़ो(uncore, DDREC);
	rps->ips.last_count1 += पूर्णांकel_uncore_पढ़ो(uncore, CSIEC);
	rps->ips.last_समय1 = jअगरfies_to_msecs(jअगरfies);

	rps->ips.last_count2 = पूर्णांकel_uncore_पढ़ो(uncore, GFXEC);
	rps->ips.last_समय2 = kसमय_get_raw_ns();

	spin_lock(&i915->irq_lock);
	ilk_enable_display_irq(i915, DE_PCU_EVENT);
	spin_unlock(&i915->irq_lock);

	spin_unlock_irq(&mchdev_lock);

	rps->ips.corr = init_emon(uncore);

	वापस true;
पूर्ण

अटल व्योम gen5_rps_disable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	u16 rgvswctl;

	spin_lock_irq(&mchdev_lock);

	spin_lock(&i915->irq_lock);
	ilk_disable_display_irq(i915, DE_PCU_EVENT);
	spin_unlock(&i915->irq_lock);

	rgvswctl = पूर्णांकel_uncore_पढ़ो16(uncore, MEMSWCTL);

	/* Ack पूर्णांकerrupts, disable EFC पूर्णांकerrupt */
	पूर्णांकel_uncore_ग_लिखो(uncore, MEMINTREN,
			   पूर्णांकel_uncore_पढ़ो(uncore, MEMINTREN) &
			   ~MEMINT_EVAL_CHG_EN);
	पूर्णांकel_uncore_ग_लिखो(uncore, MEMINTRSTS, MEMINT_EVAL_CHG);

	/* Go back to the starting frequency */
	__gen5_rps_set(rps, rps->idle_freq);
	mdelay(1);
	rgvswctl |= MEMCTL_CMD_STS;
	पूर्णांकel_uncore_ग_लिखो(uncore, MEMSWCTL, rgvswctl);
	mdelay(1);

	spin_unlock_irq(&mchdev_lock);
पूर्ण

अटल u32 rps_limits(काष्ठा पूर्णांकel_rps *rps, u8 val)
अणु
	u32 limits;

	/*
	 * Only set the करोwn limit when we've reached the lowest level to aव्योम
	 * getting more पूर्णांकerrupts, otherwise leave this clear. This prevents a
	 * race in the hw when coming out of rc6: There's a tiny winकरोw where
	 * the hw runs at the minimal घड़ी beक्रमe selecting the desired
	 * frequency, अगर the करोwn threshold expires in that winकरोw we will not
	 * receive a करोwn पूर्णांकerrupt.
	 */
	अगर (INTEL_GEN(rps_to_i915(rps)) >= 9) अणु
		limits = rps->max_freq_softlimit << 23;
		अगर (val <= rps->min_freq_softlimit)
			limits |= rps->min_freq_softlimit << 14;
	पूर्ण अन्यथा अणु
		limits = rps->max_freq_softlimit << 24;
		अगर (val <= rps->min_freq_softlimit)
			limits |= rps->min_freq_softlimit << 16;
	पूर्ण

	वापस limits;
पूर्ण

अटल व्योम rps_set_घातer(काष्ठा पूर्णांकel_rps *rps, पूर्णांक new_घातer)
अणु
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 threshold_up = 0, threshold_करोwn = 0; /* in % */
	u32 ei_up = 0, ei_करोwn = 0;

	lockdep_निश्चित_held(&rps->घातer.mutex);

	अगर (new_घातer == rps->घातer.mode)
		वापस;

	threshold_up = 95;
	threshold_करोwn = 85;

	/* Note the units here are not exactly 1us, but 1280ns. */
	चयन (new_घातer) अणु
	हाल LOW_POWER:
		ei_up = 16000;
		ei_करोwn = 32000;
		अवरोध;

	हाल BETWEEN:
		ei_up = 13000;
		ei_करोwn = 32000;
		अवरोध;

	हाल HIGH_POWER:
		ei_up = 10000;
		ei_करोwn = 32000;
		अवरोध;
	पूर्ण

	/* When byt can survive without प्रणाली hang with dynamic
	 * sw freq adjusपंचांगents, this restriction can be lअगरted.
	 */
	अगर (IS_VALLEYVIEW(gt->i915))
		जाओ skip_hw_ग_लिखो;

	GT_TRACE(gt,
		 "changing power mode [%d], up %d%% @ %dus, down %d%% @ %dus\n",
		 new_घातer, threshold_up, ei_up, threshold_करोwn, ei_करोwn);

	set(uncore, GEN6_RP_UP_EI,
	    पूर्णांकel_gt_ns_to_pm_पूर्णांकerval(gt, ei_up * 1000));
	set(uncore, GEN6_RP_UP_THRESHOLD,
	    पूर्णांकel_gt_ns_to_pm_पूर्णांकerval(gt, ei_up * threshold_up * 10));

	set(uncore, GEN6_RP_DOWN_EI,
	    पूर्णांकel_gt_ns_to_pm_पूर्णांकerval(gt, ei_करोwn * 1000));
	set(uncore, GEN6_RP_DOWN_THRESHOLD,
	    पूर्णांकel_gt_ns_to_pm_पूर्णांकerval(gt, ei_करोwn * threshold_करोwn * 10));

	set(uncore, GEN6_RP_CONTROL,
	    (INTEL_GEN(gt->i915) > 9 ? 0 : GEN6_RP_MEDIA_TURBO) |
	    GEN6_RP_MEDIA_HW_NORMAL_MODE |
	    GEN6_RP_MEDIA_IS_GFX |
	    GEN6_RP_ENABLE |
	    GEN6_RP_UP_BUSY_AVG |
	    GEN6_RP_DOWN_IDLE_AVG);

skip_hw_ग_लिखो:
	rps->घातer.mode = new_घातer;
	rps->घातer.up_threshold = threshold_up;
	rps->घातer.करोwn_threshold = threshold_करोwn;
पूर्ण

अटल व्योम gen6_rps_set_thresholds(काष्ठा पूर्णांकel_rps *rps, u8 val)
अणु
	पूर्णांक new_घातer;

	new_घातer = rps->घातer.mode;
	चयन (rps->घातer.mode) अणु
	हाल LOW_POWER:
		अगर (val > rps->efficient_freq + 1 &&
		    val > rps->cur_freq)
			new_घातer = BETWEEN;
		अवरोध;

	हाल BETWEEN:
		अगर (val <= rps->efficient_freq &&
		    val < rps->cur_freq)
			new_घातer = LOW_POWER;
		अन्यथा अगर (val >= rps->rp0_freq &&
			 val > rps->cur_freq)
			new_घातer = HIGH_POWER;
		अवरोध;

	हाल HIGH_POWER:
		अगर (val < (rps->rp1_freq + rps->rp0_freq) >> 1 &&
		    val < rps->cur_freq)
			new_घातer = BETWEEN;
		अवरोध;
	पूर्ण
	/* Max/min bins are special */
	अगर (val <= rps->min_freq_softlimit)
		new_घातer = LOW_POWER;
	अगर (val >= rps->max_freq_softlimit)
		new_घातer = HIGH_POWER;

	mutex_lock(&rps->घातer.mutex);
	अगर (rps->घातer.पूर्णांकeractive)
		new_घातer = HIGH_POWER;
	rps_set_घातer(rps, new_घातer);
	mutex_unlock(&rps->घातer.mutex);
पूर्ण

व्योम पूर्णांकel_rps_mark_पूर्णांकeractive(काष्ठा पूर्णांकel_rps *rps, bool पूर्णांकeractive)
अणु
	GT_TRACE(rps_to_gt(rps), "mark interactive: %s\n", yesno(पूर्णांकeractive));

	mutex_lock(&rps->घातer.mutex);
	अगर (पूर्णांकeractive) अणु
		अगर (!rps->घातer.पूर्णांकeractive++ && पूर्णांकel_rps_is_active(rps))
			rps_set_घातer(rps, HIGH_POWER);
	पूर्ण अन्यथा अणु
		GEM_BUG_ON(!rps->घातer.पूर्णांकeractive);
		rps->घातer.पूर्णांकeractive--;
	पूर्ण
	mutex_unlock(&rps->घातer.mutex);
पूर्ण

अटल पूर्णांक gen6_rps_set(काष्ठा पूर्णांकel_rps *rps, u8 val)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 swreq;

	अगर (INTEL_GEN(i915) >= 9)
		swreq = GEN9_FREQUENCY(val);
	अन्यथा अगर (IS_HASWELL(i915) || IS_BROADWELL(i915))
		swreq = HSW_FREQUENCY(val);
	अन्यथा
		swreq = (GEN6_FREQUENCY(val) |
			 GEN6_OFFSET(0) |
			 GEN6_AGGRESSIVE_TURBO);
	set(uncore, GEN6_RPNSWREQ, swreq);

	GT_TRACE(rps_to_gt(rps), "set val:%x, freq:%d, swreq:%x\n",
		 val, पूर्णांकel_gpu_freq(rps, val), swreq);

	वापस 0;
पूर्ण

अटल पूर्णांक vlv_rps_set(काष्ठा पूर्णांकel_rps *rps, u8 val)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	पूर्णांक err;

	vlv_punit_get(i915);
	err = vlv_punit_ग_लिखो(i915, PUNIT_REG_GPU_FREQ_REQ, val);
	vlv_punit_put(i915);

	GT_TRACE(rps_to_gt(rps), "set val:%x, freq:%d\n",
		 val, पूर्णांकel_gpu_freq(rps, val));

	वापस err;
पूर्ण

अटल पूर्णांक rps_set(काष्ठा पूर्णांकel_rps *rps, u8 val, bool update)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	पूर्णांक err;

	अगर (val == rps->last_freq)
		वापस 0;

	अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
		err = vlv_rps_set(rps, val);
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		err = gen6_rps_set(rps, val);
	अन्यथा
		err = gen5_rps_set(rps, val);
	अगर (err)
		वापस err;

	अगर (update && INTEL_GEN(i915) >= 6)
		gen6_rps_set_thresholds(rps, val);
	rps->last_freq = val;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_rps_unpark(काष्ठा पूर्णांकel_rps *rps)
अणु
	अगर (!पूर्णांकel_rps_is_enabled(rps))
		वापस;

	GT_TRACE(rps_to_gt(rps), "unpark:%x\n", rps->cur_freq);

	/*
	 * Use the user's desired frequency as a guide, but क्रम better
	 * perक्रमmance, jump directly to RPe as our starting frequency.
	 */
	mutex_lock(&rps->lock);

	पूर्णांकel_rps_set_active(rps);
	पूर्णांकel_rps_set(rps,
		      clamp(rps->cur_freq,
			    rps->min_freq_softlimit,
			    rps->max_freq_softlimit));

	mutex_unlock(&rps->lock);

	rps->pm_iir = 0;
	अगर (पूर्णांकel_rps_has_पूर्णांकerrupts(rps))
		rps_enable_पूर्णांकerrupts(rps);
	अगर (पूर्णांकel_rps_uses_समयr(rps))
		rps_start_समयr(rps);

	अगर (IS_GEN(rps_to_i915(rps), 5))
		gen5_rps_update(rps);
पूर्ण

व्योम पूर्णांकel_rps_park(काष्ठा पूर्णांकel_rps *rps)
अणु
	पूर्णांक adj;

	GEM_BUG_ON(atomic_पढ़ो(&rps->num_रुकोers));

	अगर (!पूर्णांकel_rps_clear_active(rps))
		वापस;

	अगर (पूर्णांकel_rps_uses_समयr(rps))
		rps_stop_समयr(rps);
	अगर (पूर्णांकel_rps_has_पूर्णांकerrupts(rps))
		rps_disable_पूर्णांकerrupts(rps);

	अगर (rps->last_freq <= rps->idle_freq)
		वापस;

	/*
	 * The punit delays the ग_लिखो of the frequency and voltage until it
	 * determines the GPU is awake. During normal usage we करोn't want to
	 * waste घातer changing the frequency अगर the GPU is sleeping (rc6).
	 * However, the GPU and driver is now idle and we करो not want to delay
	 * चयनing to minimum voltage (reducing घातer whilst idle) as we करो
	 * not expect to be woken in the near future and so must flush the
	 * change by waking the device.
	 *
	 * We choose to take the media घातerwell (either would करो to trick the
	 * punit पूर्णांकo committing the voltage change) as that takes a lot less
	 * घातer than the render घातerwell.
	 */
	पूर्णांकel_uncore_क्रमcewake_get(rps_to_uncore(rps), FORCEWAKE_MEDIA);
	rps_set(rps, rps->idle_freq, false);
	पूर्णांकel_uncore_क्रमcewake_put(rps_to_uncore(rps), FORCEWAKE_MEDIA);

	/*
	 * Since we will try and restart from the previously requested
	 * frequency on unparking, treat this idle poपूर्णांक as a करोwnघड़ी
	 * पूर्णांकerrupt and reduce the frequency क्रम resume. If we park/unpark
	 * more frequently than the rps worker can run, we will not respond
	 * to any EI and never see a change in frequency.
	 *
	 * (Note we accommodate Cherryview's limitation of only using an
	 * even bin by applying it to all.)
	 */
	adj = rps->last_adj;
	अगर (adj < 0)
		adj *= 2;
	अन्यथा /* CHV needs even encode values */
		adj = -2;
	rps->last_adj = adj;
	rps->cur_freq = max_t(पूर्णांक, rps->cur_freq + adj, rps->min_freq);
	अगर (rps->cur_freq < rps->efficient_freq) अणु
		rps->cur_freq = rps->efficient_freq;
		rps->last_adj = 0;
	पूर्ण

	GT_TRACE(rps_to_gt(rps), "park:%x\n", rps->cur_freq);
पूर्ण

व्योम पूर्णांकel_rps_boost(काष्ठा i915_request *rq)
अणु
	अगर (i915_request_संकेतed(rq) || i915_request_has_रुकोboost(rq))
		वापस;

	/* Serializes with i915_request_retire() */
	अगर (!test_and_set_bit(I915_FENCE_FLAG_BOOST, &rq->fence.flags)) अणु
		काष्ठा पूर्णांकel_rps *rps = &READ_ONCE(rq->engine)->gt->rps;

		अगर (atomic_fetch_inc(&rps->num_रुकोers))
			वापस;

		अगर (!पूर्णांकel_rps_is_active(rps))
			वापस;

		GT_TRACE(rps_to_gt(rps), "boost fence:%llx:%llx\n",
			 rq->fence.context, rq->fence.seqno);

		अगर (READ_ONCE(rps->cur_freq) < rps->boost_freq)
			schedule_work(&rps->work);

		WRITE_ONCE(rps->boosts, rps->boosts + 1); /* debug only */
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_rps_set(काष्ठा पूर्णांकel_rps *rps, u8 val)
अणु
	पूर्णांक err;

	lockdep_निश्चित_held(&rps->lock);
	GEM_BUG_ON(val > rps->max_freq);
	GEM_BUG_ON(val < rps->min_freq);

	अगर (पूर्णांकel_rps_is_active(rps)) अणु
		err = rps_set(rps, val, true);
		अगर (err)
			वापस err;

		/*
		 * Make sure we जारी to get पूर्णांकerrupts
		 * until we hit the minimum or maximum frequencies.
		 */
		अगर (पूर्णांकel_rps_has_पूर्णांकerrupts(rps)) अणु
			काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);

			set(uncore,
			    GEN6_RP_INTERRUPT_LIMITS, rps_limits(rps, val));

			set(uncore, GEN6_PMINTRMSK, rps_pm_mask(rps, val));
		पूर्ण
	पूर्ण

	rps->cur_freq = val;
	वापस 0;
पूर्ण

अटल व्योम gen6_rps_init(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);

	/* All of these values are in units of 50MHz */

	/* अटल values from HW: RP0 > RP1 > RPn (min_freq) */
	अगर (IS_GEN9_LP(i915)) अणु
		u32 rp_state_cap = पूर्णांकel_uncore_पढ़ो(uncore, BXT_RP_STATE_CAP);

		rps->rp0_freq = (rp_state_cap >> 16) & 0xff;
		rps->rp1_freq = (rp_state_cap >>  8) & 0xff;
		rps->min_freq = (rp_state_cap >>  0) & 0xff;
	पूर्ण अन्यथा अणु
		u32 rp_state_cap = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_STATE_CAP);

		rps->rp0_freq = (rp_state_cap >>  0) & 0xff;
		rps->rp1_freq = (rp_state_cap >>  8) & 0xff;
		rps->min_freq = (rp_state_cap >> 16) & 0xff;
	पूर्ण

	/* hw_max = RP0 until we check क्रम overघड़ीing */
	rps->max_freq = rps->rp0_freq;

	rps->efficient_freq = rps->rp1_freq;
	अगर (IS_HASWELL(i915) || IS_BROADWELL(i915) ||
	    IS_GEN9_BC(i915) || INTEL_GEN(i915) >= 10) अणु
		u32 ddcc_status = 0;

		अगर (sandybridge_pcode_पढ़ो(i915,
					   HSW_PCODE_DYNAMIC_DUTY_CYCLE_CONTROL,
					   &ddcc_status, शून्य) == 0)
			rps->efficient_freq =
				clamp_t(u8,
					(ddcc_status >> 8) & 0xff,
					rps->min_freq,
					rps->max_freq);
	पूर्ण

	अगर (IS_GEN9_BC(i915) || INTEL_GEN(i915) >= 10) अणु
		/* Store the frequency values in 16.66 MHZ units, which is
		 * the natural hardware unit क्रम SKL
		 */
		rps->rp0_freq *= GEN9_FREQ_SCALER;
		rps->rp1_freq *= GEN9_FREQ_SCALER;
		rps->min_freq *= GEN9_FREQ_SCALER;
		rps->max_freq *= GEN9_FREQ_SCALER;
		rps->efficient_freq *= GEN9_FREQ_SCALER;
	पूर्ण
पूर्ण

अटल bool rps_reset(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);

	/* क्रमce a reset */
	rps->घातer.mode = -1;
	rps->last_freq = -1;

	अगर (rps_set(rps, rps->min_freq, true)) अणु
		drm_err(&i915->drm, "Failed to reset RPS to initial values\n");
		वापस false;
	पूर्ण

	rps->cur_freq = rps->min_freq;
	वापस true;
पूर्ण

/* See the Gen9_GT_PM_Programming_Guide करोc क्रम the below */
अटल bool gen9_rps_enable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	/* Program शेषs and thresholds क्रम RPS */
	अगर (IS_GEN(gt->i915, 9))
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RC_VIDEO_FREQ,
				      GEN9_FREQUENCY(rps->rp1_freq));

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_IDLE_HYSTERSIS, 0xa);

	rps->pm_events = GEN6_PM_RP_UP_THRESHOLD | GEN6_PM_RP_DOWN_THRESHOLD;

	वापस rps_reset(rps);
पूर्ण

अटल bool gen8_rps_enable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RC_VIDEO_FREQ,
			      HSW_FREQUENCY(rps->rp1_freq));

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_IDLE_HYSTERSIS, 10);

	rps->pm_events = GEN6_PM_RP_UP_THRESHOLD | GEN6_PM_RP_DOWN_THRESHOLD;

	वापस rps_reset(rps);
पूर्ण

अटल bool gen6_rps_enable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);

	/* Power करोwn अगर completely idle क्रम over 50ms */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_DOWN_TIMEOUT, 50000);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_IDLE_HYSTERSIS, 10);

	rps->pm_events = (GEN6_PM_RP_UP_THRESHOLD |
			  GEN6_PM_RP_DOWN_THRESHOLD |
			  GEN6_PM_RP_DOWN_TIMEOUT);

	वापस rps_reset(rps);
पूर्ण

अटल पूर्णांक chv_rps_max_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);
	u32 val;

	val = vlv_punit_पढ़ो(i915, FB_GFX_FMAX_AT_VMAX_FUSE);

	चयन (gt->info.sseu.eu_total) अणु
	हाल 8:
		/* (2 * 4) config */
		val >>= FB_GFX_FMAX_AT_VMAX_2SS4EU_FUSE_SHIFT;
		अवरोध;
	हाल 12:
		/* (2 * 6) config */
		val >>= FB_GFX_FMAX_AT_VMAX_2SS6EU_FUSE_SHIFT;
		अवरोध;
	हाल 16:
		/* (2 * 8) config */
	शेष:
		/* Setting (2 * 8) Min RP0 क्रम any other combination */
		val >>= FB_GFX_FMAX_AT_VMAX_2SS8EU_FUSE_SHIFT;
		अवरोध;
	पूर्ण

	वापस val & FB_GFX_FREQ_FUSE_MASK;
पूर्ण

अटल पूर्णांक chv_rps_rpe_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val;

	val = vlv_punit_पढ़ो(i915, PUNIT_GPU_DUTYCYCLE_REG);
	val >>= PUNIT_GPU_DUTYCYCLE_RPE_FREQ_SHIFT;

	वापस val & PUNIT_GPU_DUTYCYCLE_RPE_FREQ_MASK;
पूर्ण

अटल पूर्णांक chv_rps_guar_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val;

	val = vlv_punit_पढ़ो(i915, FB_GFX_FMAX_AT_VMAX_FUSE);

	वापस val & FB_GFX_FREQ_FUSE_MASK;
पूर्ण

अटल u32 chv_rps_min_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val;

	val = vlv_punit_पढ़ो(i915, FB_GFX_FMIN_AT_VMIN_FUSE);
	val >>= FB_GFX_FMIN_AT_VMIN_FUSE_SHIFT;

	वापस val & FB_GFX_FREQ_FUSE_MASK;
पूर्ण

अटल bool chv_rps_enable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val;

	/* 1: Program शेषs and thresholds क्रम RPS*/
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_DOWN_TIMEOUT, 1000000);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_UP_THRESHOLD, 59400);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_DOWN_THRESHOLD, 245000);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_UP_EI, 66000);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_DOWN_EI, 350000);

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_IDLE_HYSTERSIS, 10);

	/* 2: Enable RPS */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_CONTROL,
			      GEN6_RP_MEDIA_HW_NORMAL_MODE |
			      GEN6_RP_MEDIA_IS_GFX |
			      GEN6_RP_ENABLE |
			      GEN6_RP_UP_BUSY_AVG |
			      GEN6_RP_DOWN_IDLE_AVG);

	rps->pm_events = (GEN6_PM_RP_UP_THRESHOLD |
			  GEN6_PM_RP_DOWN_THRESHOLD |
			  GEN6_PM_RP_DOWN_TIMEOUT);

	/* Setting Fixed Bias */
	vlv_punit_get(i915);

	val = VLV_OVERRIDE_EN | VLV_SOC_TDP_EN | CHV_BIAS_CPU_50_SOC_50;
	vlv_punit_ग_लिखो(i915, VLV_TURBO_SOC_OVERRIDE, val);

	val = vlv_punit_पढ़ो(i915, PUNIT_REG_GPU_FREQ_STS);

	vlv_punit_put(i915);

	/* RPS code assumes GPLL is used */
	drm_WARN_ONCE(&i915->drm, (val & GPLLENABLE) == 0,
		      "GPLL not enabled\n");

	drm_dbg(&i915->drm, "GPLL enabled? %s\n", yesno(val & GPLLENABLE));
	drm_dbg(&i915->drm, "GPU status: 0x%08x\n", val);

	वापस rps_reset(rps);
पूर्ण

अटल पूर्णांक vlv_rps_guar_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val, rp1;

	val = vlv_nc_पढ़ो(i915, IOSF_NC_FB_GFX_FREQ_FUSE);

	rp1 = val & FB_GFX_FGUARANTEED_FREQ_FUSE_MASK;
	rp1 >>= FB_GFX_FGUARANTEED_FREQ_FUSE_SHIFT;

	वापस rp1;
पूर्ण

अटल पूर्णांक vlv_rps_max_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val, rp0;

	val = vlv_nc_पढ़ो(i915, IOSF_NC_FB_GFX_FREQ_FUSE);

	rp0 = (val & FB_GFX_MAX_FREQ_FUSE_MASK) >> FB_GFX_MAX_FREQ_FUSE_SHIFT;
	/* Clamp to max */
	rp0 = min_t(u32, rp0, 0xea);

	वापस rp0;
पूर्ण

अटल पूर्णांक vlv_rps_rpe_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val, rpe;

	val = vlv_nc_पढ़ो(i915, IOSF_NC_FB_GFX_FMAX_FUSE_LO);
	rpe = (val & FB_FMAX_VMIN_FREQ_LO_MASK) >> FB_FMAX_VMIN_FREQ_LO_SHIFT;
	val = vlv_nc_पढ़ो(i915, IOSF_NC_FB_GFX_FMAX_FUSE_HI);
	rpe |= (val & FB_FMAX_VMIN_FREQ_HI_MASK) << 5;

	वापस rpe;
पूर्ण

अटल पूर्णांक vlv_rps_min_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val;

	val = vlv_punit_पढ़ो(i915, PUNIT_REG_GPU_LFM) & 0xff;
	/*
	 * According to the BYT Punit GPU turbo HAS 1.1.6.3 the minimum value
	 * क्रम the minimum frequency in GPLL mode is 0xc1. Contrary to this on
	 * a BYT-M B0 the above रेजिस्टर contains 0xbf. Moreover when setting
	 * a frequency Punit will not allow values below 0xc0. Clamp it 0xc0
	 * to make sure it matches what Punit accepts.
	 */
	वापस max_t(u32, val, 0xc0);
पूर्ण

अटल bool vlv_rps_enable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val;

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_DOWN_TIMEOUT, 1000000);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_UP_THRESHOLD, 59400);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_DOWN_THRESHOLD, 245000);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_UP_EI, 66000);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_DOWN_EI, 350000);

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_IDLE_HYSTERSIS, 10);

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_RP_CONTROL,
			      GEN6_RP_MEDIA_TURBO |
			      GEN6_RP_MEDIA_HW_NORMAL_MODE |
			      GEN6_RP_MEDIA_IS_GFX |
			      GEN6_RP_ENABLE |
			      GEN6_RP_UP_BUSY_AVG |
			      GEN6_RP_DOWN_IDLE_CONT);

	/* WaGsvRC0ResidencyMethod:vlv */
	rps->pm_events = GEN6_PM_RP_UP_EI_EXPIRED;

	vlv_punit_get(i915);

	/* Setting Fixed Bias */
	val = VLV_OVERRIDE_EN | VLV_SOC_TDP_EN | VLV_BIAS_CPU_125_SOC_875;
	vlv_punit_ग_लिखो(i915, VLV_TURBO_SOC_OVERRIDE, val);

	val = vlv_punit_पढ़ो(i915, PUNIT_REG_GPU_FREQ_STS);

	vlv_punit_put(i915);

	/* RPS code assumes GPLL is used */
	drm_WARN_ONCE(&i915->drm, (val & GPLLENABLE) == 0,
		      "GPLL not enabled\n");

	drm_dbg(&i915->drm, "GPLL enabled? %s\n", yesno(val & GPLLENABLE));
	drm_dbg(&i915->drm, "GPU status: 0x%08x\n", val);

	वापस rps_reset(rps);
पूर्ण

अटल अचिन्हित दीर्घ __ips_gfx_val(काष्ठा पूर्णांकel_ips *ips)
अणु
	काष्ठा पूर्णांकel_rps *rps = container_of(ips, typeof(*rps), ips);
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	अचिन्हित पूर्णांक t, state1, state2;
	u32 pxvid, ext_v;
	u64 corr, corr2;

	lockdep_निश्चित_held(&mchdev_lock);

	pxvid = पूर्णांकel_uncore_पढ़ो(uncore, PXVFREQ(rps->cur_freq));
	pxvid = (pxvid >> 24) & 0x7f;
	ext_v = pvid_to_extvid(rps_to_i915(rps), pxvid);

	state1 = ext_v;

	/* Revel in the empirically derived स्थिरants */

	/* Correction factor in 1/100000 units */
	t = ips_mch_val(uncore);
	अगर (t > 80)
		corr = t * 2349 + 135940;
	अन्यथा अगर (t >= 50)
		corr = t * 964 + 29317;
	अन्यथा /* < 50 */
		corr = t * 301 + 1004;

	corr = भाग_u64(corr * 150142 * state1, 10000) - 78642;
	corr2 = भाग_u64(corr, 100000) * ips->corr;

	state2 = भाग_u64(corr2 * state1, 10000);
	state2 /= 100; /* convert to mW */

	__gen5_ips_update(ips);

	वापस ips->gfx_घातer + state2;
पूर्ण

अटल bool has_busy_stats(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, rps_to_gt(rps), id) अणु
		अगर (!पूर्णांकel_engine_supports_stats(engine))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम पूर्णांकel_rps_enable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	bool enabled = false;

	अगर (!HAS_RPS(i915))
		वापस;

	पूर्णांकel_gt_check_घड़ी_frequency(rps_to_gt(rps));

	पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);
	अगर (rps->max_freq <= rps->min_freq)
		/* leave disabled, no room क्रम dynamic reघड़ीing */;
	अन्यथा अगर (IS_CHERRYVIEW(i915))
		enabled = chv_rps_enable(rps);
	अन्यथा अगर (IS_VALLEYVIEW(i915))
		enabled = vlv_rps_enable(rps);
	अन्यथा अगर (INTEL_GEN(i915) >= 9)
		enabled = gen9_rps_enable(rps);
	अन्यथा अगर (INTEL_GEN(i915) >= 8)
		enabled = gen8_rps_enable(rps);
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		enabled = gen6_rps_enable(rps);
	अन्यथा अगर (IS_IRONLAKE_M(i915))
		enabled = gen5_rps_enable(rps);
	अन्यथा
		MISSING_CASE(INTEL_GEN(i915));
	पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);
	अगर (!enabled)
		वापस;

	GT_TRACE(rps_to_gt(rps),
		 "min:%x, max:%x, freq:[%d, %d]\n",
		 rps->min_freq, rps->max_freq,
		 पूर्णांकel_gpu_freq(rps, rps->min_freq),
		 पूर्णांकel_gpu_freq(rps, rps->max_freq));

	GEM_BUG_ON(rps->max_freq < rps->min_freq);
	GEM_BUG_ON(rps->idle_freq > rps->max_freq);

	GEM_BUG_ON(rps->efficient_freq < rps->min_freq);
	GEM_BUG_ON(rps->efficient_freq > rps->max_freq);

	अगर (has_busy_stats(rps))
		पूर्णांकel_rps_set_समयr(rps);
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		पूर्णांकel_rps_set_पूर्णांकerrupts(rps);
	अन्यथा
		/* Ironlake currently uses पूर्णांकel_ips.ko */ अणुपूर्ण

	पूर्णांकel_rps_set_enabled(rps);
पूर्ण

अटल व्योम gen6_rps_disable(काष्ठा पूर्णांकel_rps *rps)
अणु
	set(rps_to_uncore(rps), GEN6_RP_CONTROL, 0);
पूर्ण

व्योम पूर्णांकel_rps_disable(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);

	पूर्णांकel_rps_clear_enabled(rps);
	पूर्णांकel_rps_clear_पूर्णांकerrupts(rps);
	पूर्णांकel_rps_clear_समयr(rps);

	अगर (INTEL_GEN(i915) >= 6)
		gen6_rps_disable(rps);
	अन्यथा अगर (IS_IRONLAKE_M(i915))
		gen5_rps_disable(rps);
पूर्ण

अटल पूर्णांक byt_gpu_freq(काष्ठा पूर्णांकel_rps *rps, पूर्णांक val)
अणु
	/*
	 * N = val - 0xb7
	 * Slow = Fast = GPLL ref * N
	 */
	वापस DIV_ROUND_CLOSEST(rps->gpll_ref_freq * (val - 0xb7), 1000);
पूर्ण

अटल पूर्णांक byt_freq_opcode(काष्ठा पूर्णांकel_rps *rps, पूर्णांक val)
अणु
	वापस DIV_ROUND_CLOSEST(1000 * val, rps->gpll_ref_freq) + 0xb7;
पूर्ण

अटल पूर्णांक chv_gpu_freq(काष्ठा पूर्णांकel_rps *rps, पूर्णांक val)
अणु
	/*
	 * N = val / 2
	 * CU (slow) = CU2x (fast) / 2 = GPLL ref * N / 2
	 */
	वापस DIV_ROUND_CLOSEST(rps->gpll_ref_freq * val, 2 * 2 * 1000);
पूर्ण

अटल पूर्णांक chv_freq_opcode(काष्ठा पूर्णांकel_rps *rps, पूर्णांक val)
अणु
	/* CHV needs even values */
	वापस DIV_ROUND_CLOSEST(2 * 1000 * val, rps->gpll_ref_freq) * 2;
पूर्ण

पूर्णांक पूर्णांकel_gpu_freq(काष्ठा पूर्णांकel_rps *rps, पूर्णांक val)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);

	अगर (INTEL_GEN(i915) >= 9)
		वापस DIV_ROUND_CLOSEST(val * GT_FREQUENCY_MULTIPLIER,
					 GEN9_FREQ_SCALER);
	अन्यथा अगर (IS_CHERRYVIEW(i915))
		वापस chv_gpu_freq(rps, val);
	अन्यथा अगर (IS_VALLEYVIEW(i915))
		वापस byt_gpu_freq(rps, val);
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		वापस val * GT_FREQUENCY_MULTIPLIER;
	अन्यथा
		वापस val;
पूर्ण

पूर्णांक पूर्णांकel_freq_opcode(काष्ठा पूर्णांकel_rps *rps, पूर्णांक val)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);

	अगर (INTEL_GEN(i915) >= 9)
		वापस DIV_ROUND_CLOSEST(val * GEN9_FREQ_SCALER,
					 GT_FREQUENCY_MULTIPLIER);
	अन्यथा अगर (IS_CHERRYVIEW(i915))
		वापस chv_freq_opcode(rps, val);
	अन्यथा अगर (IS_VALLEYVIEW(i915))
		वापस byt_freq_opcode(rps, val);
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		वापस DIV_ROUND_CLOSEST(val, GT_FREQUENCY_MULTIPLIER);
	अन्यथा
		वापस val;
पूर्ण

अटल व्योम vlv_init_gpll_ref_freq(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);

	rps->gpll_ref_freq =
		vlv_get_cck_घड़ी(i915, "GPLL ref",
				  CCK_GPLL_CLOCK_CONTROL,
				  i915->czclk_freq);

	drm_dbg(&i915->drm, "GPLL reference freq: %d kHz\n",
		rps->gpll_ref_freq);
पूर्ण

अटल व्योम vlv_rps_init(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val;

	vlv_iosf_sb_get(i915,
			BIT(VLV_IOSF_SB_PUNIT) |
			BIT(VLV_IOSF_SB_NC) |
			BIT(VLV_IOSF_SB_CCK));

	vlv_init_gpll_ref_freq(rps);

	val = vlv_punit_पढ़ो(i915, PUNIT_REG_GPU_FREQ_STS);
	चयन ((val >> 6) & 3) अणु
	हाल 0:
	हाल 1:
		i915->mem_freq = 800;
		अवरोध;
	हाल 2:
		i915->mem_freq = 1066;
		अवरोध;
	हाल 3:
		i915->mem_freq = 1333;
		अवरोध;
	पूर्ण
	drm_dbg(&i915->drm, "DDR speed: %d MHz\n", i915->mem_freq);

	rps->max_freq = vlv_rps_max_freq(rps);
	rps->rp0_freq = rps->max_freq;
	drm_dbg(&i915->drm, "max GPU freq: %d MHz (%u)\n",
		पूर्णांकel_gpu_freq(rps, rps->max_freq), rps->max_freq);

	rps->efficient_freq = vlv_rps_rpe_freq(rps);
	drm_dbg(&i915->drm, "RPe GPU freq: %d MHz (%u)\n",
		पूर्णांकel_gpu_freq(rps, rps->efficient_freq), rps->efficient_freq);

	rps->rp1_freq = vlv_rps_guar_freq(rps);
	drm_dbg(&i915->drm, "RP1(Guar Freq) GPU freq: %d MHz (%u)\n",
		पूर्णांकel_gpu_freq(rps, rps->rp1_freq), rps->rp1_freq);

	rps->min_freq = vlv_rps_min_freq(rps);
	drm_dbg(&i915->drm, "min GPU freq: %d MHz (%u)\n",
		पूर्णांकel_gpu_freq(rps, rps->min_freq), rps->min_freq);

	vlv_iosf_sb_put(i915,
			BIT(VLV_IOSF_SB_PUNIT) |
			BIT(VLV_IOSF_SB_NC) |
			BIT(VLV_IOSF_SB_CCK));
पूर्ण

अटल व्योम chv_rps_init(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 val;

	vlv_iosf_sb_get(i915,
			BIT(VLV_IOSF_SB_PUNIT) |
			BIT(VLV_IOSF_SB_NC) |
			BIT(VLV_IOSF_SB_CCK));

	vlv_init_gpll_ref_freq(rps);

	val = vlv_cck_पढ़ो(i915, CCK_FUSE_REG);

	चयन ((val >> 2) & 0x7) अणु
	हाल 3:
		i915->mem_freq = 2000;
		अवरोध;
	शेष:
		i915->mem_freq = 1600;
		अवरोध;
	पूर्ण
	drm_dbg(&i915->drm, "DDR speed: %d MHz\n", i915->mem_freq);

	rps->max_freq = chv_rps_max_freq(rps);
	rps->rp0_freq = rps->max_freq;
	drm_dbg(&i915->drm, "max GPU freq: %d MHz (%u)\n",
		पूर्णांकel_gpu_freq(rps, rps->max_freq), rps->max_freq);

	rps->efficient_freq = chv_rps_rpe_freq(rps);
	drm_dbg(&i915->drm, "RPe GPU freq: %d MHz (%u)\n",
		पूर्णांकel_gpu_freq(rps, rps->efficient_freq), rps->efficient_freq);

	rps->rp1_freq = chv_rps_guar_freq(rps);
	drm_dbg(&i915->drm, "RP1(Guar) GPU freq: %d MHz (%u)\n",
		पूर्णांकel_gpu_freq(rps, rps->rp1_freq), rps->rp1_freq);

	rps->min_freq = chv_rps_min_freq(rps);
	drm_dbg(&i915->drm, "min GPU freq: %d MHz (%u)\n",
		पूर्णांकel_gpu_freq(rps, rps->min_freq), rps->min_freq);

	vlv_iosf_sb_put(i915,
			BIT(VLV_IOSF_SB_PUNIT) |
			BIT(VLV_IOSF_SB_NC) |
			BIT(VLV_IOSF_SB_CCK));

	drm_WARN_ONCE(&i915->drm, (rps->max_freq | rps->efficient_freq |
				   rps->rp1_freq | rps->min_freq) & 1,
		      "Odd GPU freq values\n");
पूर्ण

अटल व्योम vlv_c0_पढ़ो(काष्ठा पूर्णांकel_uncore *uncore, काष्ठा पूर्णांकel_rps_ei *ei)
अणु
	ei->kसमय = kसमय_get_raw();
	ei->render_c0 = पूर्णांकel_uncore_पढ़ो(uncore, VLV_RENDER_C0_COUNT);
	ei->media_c0 = पूर्णांकel_uncore_पढ़ो(uncore, VLV_MEDIA_C0_COUNT);
पूर्ण

अटल u32 vlv_wa_c0_ei(काष्ठा पूर्णांकel_rps *rps, u32 pm_iir)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	स्थिर काष्ठा पूर्णांकel_rps_ei *prev = &rps->ei;
	काष्ठा पूर्णांकel_rps_ei now;
	u32 events = 0;

	अगर ((pm_iir & GEN6_PM_RP_UP_EI_EXPIRED) == 0)
		वापस 0;

	vlv_c0_पढ़ो(uncore, &now);

	अगर (prev->kसमय) अणु
		u64 समय, c0;
		u32 render, media;

		समय = kसमय_us_delta(now.kसमय, prev->kसमय);

		समय *= rps_to_i915(rps)->czclk_freq;

		/* Workload can be split between render + media,
		 * e.g. SwapBuffers being blitted in X after being rendered in
		 * mesa. To account क्रम this we need to combine both engines
		 * पूर्णांकo our activity counter.
		 */
		render = now.render_c0 - prev->render_c0;
		media = now.media_c0 - prev->media_c0;
		c0 = max(render, media);
		c0 *= 1000 * 100 << 8; /* to usecs and scale to threshold% */

		अगर (c0 > समय * rps->घातer.up_threshold)
			events = GEN6_PM_RP_UP_THRESHOLD;
		अन्यथा अगर (c0 < समय * rps->घातer.करोwn_threshold)
			events = GEN6_PM_RP_DOWN_THRESHOLD;
	पूर्ण

	rps->ei = now;
	वापस events;
पूर्ण

अटल व्योम rps_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_rps *rps = container_of(work, typeof(*rps), work);
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	bool client_boost = false;
	पूर्णांक new_freq, adj, min, max;
	u32 pm_iir = 0;

	spin_lock_irq(&gt->irq_lock);
	pm_iir = fetch_and_zero(&rps->pm_iir) & rps->pm_events;
	client_boost = atomic_पढ़ो(&rps->num_रुकोers);
	spin_unlock_irq(&gt->irq_lock);

	/* Make sure we didn't queue anything we're not going to process. */
	अगर (!pm_iir && !client_boost)
		जाओ out;

	mutex_lock(&rps->lock);
	अगर (!पूर्णांकel_rps_is_active(rps)) अणु
		mutex_unlock(&rps->lock);
		वापस;
	पूर्ण

	pm_iir |= vlv_wa_c0_ei(rps, pm_iir);

	adj = rps->last_adj;
	new_freq = rps->cur_freq;
	min = rps->min_freq_softlimit;
	max = rps->max_freq_softlimit;
	अगर (client_boost)
		max = rps->max_freq;

	GT_TRACE(gt,
		 "pm_iir:%x, client_boost:%s, last:%d, cur:%x, min:%x, max:%x\n",
		 pm_iir, yesno(client_boost),
		 adj, new_freq, min, max);

	अगर (client_boost && new_freq < rps->boost_freq) अणु
		new_freq = rps->boost_freq;
		adj = 0;
	पूर्ण अन्यथा अगर (pm_iir & GEN6_PM_RP_UP_THRESHOLD) अणु
		अगर (adj > 0)
			adj *= 2;
		अन्यथा /* CHV needs even encode values */
			adj = IS_CHERRYVIEW(gt->i915) ? 2 : 1;

		अगर (new_freq >= rps->max_freq_softlimit)
			adj = 0;
	पूर्ण अन्यथा अगर (client_boost) अणु
		adj = 0;
	पूर्ण अन्यथा अगर (pm_iir & GEN6_PM_RP_DOWN_TIMEOUT) अणु
		अगर (rps->cur_freq > rps->efficient_freq)
			new_freq = rps->efficient_freq;
		अन्यथा अगर (rps->cur_freq > rps->min_freq_softlimit)
			new_freq = rps->min_freq_softlimit;
		adj = 0;
	पूर्ण अन्यथा अगर (pm_iir & GEN6_PM_RP_DOWN_THRESHOLD) अणु
		अगर (adj < 0)
			adj *= 2;
		अन्यथा /* CHV needs even encode values */
			adj = IS_CHERRYVIEW(gt->i915) ? -2 : -1;

		अगर (new_freq <= rps->min_freq_softlimit)
			adj = 0;
	पूर्ण अन्यथा अणु /* unknown event */
		adj = 0;
	पूर्ण

	/*
	 * sysfs frequency limits may have snuck in जबतक
	 * servicing the पूर्णांकerrupt
	 */
	new_freq += adj;
	new_freq = clamp_t(पूर्णांक, new_freq, min, max);

	अगर (पूर्णांकel_rps_set(rps, new_freq)) अणु
		drm_dbg(&i915->drm, "Failed to set new GPU frequency\n");
		adj = 0;
	पूर्ण
	rps->last_adj = adj;

	mutex_unlock(&rps->lock);

out:
	spin_lock_irq(&gt->irq_lock);
	gen6_gt_pm_unmask_irq(gt, rps->pm_events);
	spin_unlock_irq(&gt->irq_lock);
पूर्ण

व्योम gen11_rps_irq_handler(काष्ठा पूर्णांकel_rps *rps, u32 pm_iir)
अणु
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);
	स्थिर u32 events = rps->pm_events & pm_iir;

	lockdep_निश्चित_held(&gt->irq_lock);

	अगर (unlikely(!events))
		वापस;

	GT_TRACE(gt, "irq events:%x\n", events);

	gen6_gt_pm_mask_irq(gt, events);

	rps->pm_iir |= events;
	schedule_work(&rps->work);
पूर्ण

व्योम gen6_rps_irq_handler(काष्ठा पूर्णांकel_rps *rps, u32 pm_iir)
अणु
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);
	u32 events;

	events = pm_iir & rps->pm_events;
	अगर (events) अणु
		spin_lock(&gt->irq_lock);

		GT_TRACE(gt, "irq events:%x\n", events);

		gen6_gt_pm_mask_irq(gt, events);
		rps->pm_iir |= events;

		schedule_work(&rps->work);
		spin_unlock(&gt->irq_lock);
	पूर्ण

	अगर (INTEL_GEN(gt->i915) >= 8)
		वापस;

	अगर (pm_iir & PM_VEBOX_USER_INTERRUPT)
		पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(gt->engine[VECS0]);

	अगर (pm_iir & PM_VEBOX_CS_ERROR_INTERRUPT)
		DRM_DEBUG("Command parser error, pm_iir 0x%08x\n", pm_iir);
पूर्ण

व्योम gen5_rps_irq_handler(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	u32 busy_up, busy_करोwn, max_avg, min_avg;
	u8 new_freq;

	spin_lock(&mchdev_lock);

	पूर्णांकel_uncore_ग_लिखो16(uncore,
			     MEMINTRSTS,
			     पूर्णांकel_uncore_पढ़ो(uncore, MEMINTRSTS));

	पूर्णांकel_uncore_ग_लिखो16(uncore, MEMINTRSTS, MEMINT_EVAL_CHG);
	busy_up = पूर्णांकel_uncore_पढ़ो(uncore, RCPREVBSYTUPAVG);
	busy_करोwn = पूर्णांकel_uncore_पढ़ो(uncore, RCPREVBSYTDNAVG);
	max_avg = पूर्णांकel_uncore_पढ़ो(uncore, RCBMAXAVG);
	min_avg = पूर्णांकel_uncore_पढ़ो(uncore, RCBMINAVG);

	/* Handle RCS change request from hw */
	new_freq = rps->cur_freq;
	अगर (busy_up > max_avg)
		new_freq++;
	अन्यथा अगर (busy_करोwn < min_avg)
		new_freq--;
	new_freq = clamp(new_freq,
			 rps->min_freq_softlimit,
			 rps->max_freq_softlimit);

	अगर (new_freq != rps->cur_freq && !__gen5_rps_set(rps, new_freq))
		rps->cur_freq = new_freq;

	spin_unlock(&mchdev_lock);
पूर्ण

व्योम पूर्णांकel_rps_init_early(काष्ठा पूर्णांकel_rps *rps)
अणु
	mutex_init(&rps->lock);
	mutex_init(&rps->घातer.mutex);

	INIT_WORK(&rps->work, rps_work);
	समयr_setup(&rps->समयr, rps_समयr, 0);

	atomic_set(&rps->num_रुकोers, 0);
पूर्ण

व्योम पूर्णांकel_rps_init(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);

	अगर (IS_CHERRYVIEW(i915))
		chv_rps_init(rps);
	अन्यथा अगर (IS_VALLEYVIEW(i915))
		vlv_rps_init(rps);
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		gen6_rps_init(rps);
	अन्यथा अगर (IS_IRONLAKE_M(i915))
		gen5_rps_init(rps);

	/* Derive initial user preferences/limits from the hardware limits */
	rps->max_freq_softlimit = rps->max_freq;
	rps->min_freq_softlimit = rps->min_freq;

	/* After setting max-softlimit, find the overघड़ी max freq */
	अगर (IS_GEN(i915, 6) || IS_IVYBRIDGE(i915) || IS_HASWELL(i915)) अणु
		u32 params = 0;

		sandybridge_pcode_पढ़ो(i915, GEN6_READ_OC_PARAMS,
				       &params, शून्य);
		अगर (params & BIT(31)) अणु /* OC supported */
			drm_dbg(&i915->drm,
				"Overclocking supported, max: %dMHz, overclock: %dMHz\n",
				(rps->max_freq & 0xff) * 50,
				(params & 0xff) * 50);
			rps->max_freq = params & 0xff;
		पूर्ण
	पूर्ण

	/* Finally allow us to boost to max by शेष */
	rps->boost_freq = rps->max_freq;
	rps->idle_freq = rps->min_freq;

	/* Start in the middle, from here we will स्वतःtune based on workload */
	rps->cur_freq = rps->efficient_freq;

	rps->pm_पूर्णांकrmsk_mbz = 0;

	/*
	 * SNB,IVB,HSW can जबतक VLV,CHV may hard hang on looping batchbuffer
	 * अगर GEN6_PM_UP_EI_EXPIRED is masked.
	 *
	 * TODO: verअगरy अगर this can be reproduced on VLV,CHV.
	 */
	अगर (INTEL_GEN(i915) <= 7)
		rps->pm_पूर्णांकrmsk_mbz |= GEN6_PM_RP_UP_EI_EXPIRED;

	अगर (INTEL_GEN(i915) >= 8 && INTEL_GEN(i915) < 11)
		rps->pm_पूर्णांकrmsk_mbz |= GEN8_PMINTR_DISABLE_REसूचीECT_TO_GUC;
पूर्ण

व्योम पूर्णांकel_rps_sanitize(काष्ठा पूर्णांकel_rps *rps)
अणु
	अगर (INTEL_GEN(rps_to_i915(rps)) >= 6)
		rps_disable_पूर्णांकerrupts(rps);
पूर्ण

u32 पूर्णांकel_rps_get_cagf(काष्ठा पूर्णांकel_rps *rps, u32 rpstat)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	u32 cagf;

	अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
		cagf = (rpstat >> 8) & 0xff;
	अन्यथा अगर (INTEL_GEN(i915) >= 9)
		cagf = (rpstat & GEN9_CAGF_MASK) >> GEN9_CAGF_SHIFT;
	अन्यथा अगर (IS_HASWELL(i915) || IS_BROADWELL(i915))
		cagf = (rpstat & HSW_CAGF_MASK) >> HSW_CAGF_SHIFT;
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		cagf = (rpstat & GEN6_CAGF_MASK) >> GEN6_CAGF_SHIFT;
	अन्यथा
		cagf = gen5_invert_freq(rps, (rpstat & MEMSTAT_PSTATE_MASK) >>
					MEMSTAT_PSTATE_SHIFT);

	वापस cagf;
पूर्ण

अटल u32 पढ़ो_cagf(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	काष्ठा पूर्णांकel_uncore *uncore = rps_to_uncore(rps);
	u32 freq;

	अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915)) अणु
		vlv_punit_get(i915);
		freq = vlv_punit_पढ़ो(i915, PUNIT_REG_GPU_FREQ_STS);
		vlv_punit_put(i915);
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 6) अणु
		freq = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RPSTAT1);
	पूर्ण अन्यथा अणु
		freq = पूर्णांकel_uncore_पढ़ो(uncore, MEMSTAT_ILK);
	पूर्ण

	वापस पूर्णांकel_rps_get_cagf(rps, freq);
पूर्ण

u32 पूर्णांकel_rps_पढ़ो_actual_frequency(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_runसमय_pm *rpm = rps_to_uncore(rps)->rpm;
	पूर्णांकel_wakeref_t wakeref;
	u32 freq = 0;

	with_पूर्णांकel_runसमय_pm_अगर_in_use(rpm, wakeref)
		freq = पूर्णांकel_gpu_freq(rps, पढ़ो_cagf(rps));

	वापस freq;
पूर्ण

/* External पूर्णांकerface क्रम पूर्णांकel_ips.ko */

अटल काष्ठा drm_i915_निजी __rcu *ips_mchdev;

/**
 * Tells the पूर्णांकel_ips driver that the i915 driver is now loaded, अगर
 * IPS got loaded first.
 *
 * This awkward dance is so that neither module has to depend on the
 * other in order क्रम IPS to करो the appropriate communication of
 * GPU turbo limits to i915.
 */
अटल व्योम
ips_ping_क्रम_i915_load(व्योम)
अणु
	व्योम (*link)(व्योम);

	link = symbol_get(ips_link_to_i915_driver);
	अगर (link) अणु
		link();
		symbol_put(ips_link_to_i915_driver);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_rps_driver_रेजिस्टर(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा पूर्णांकel_gt *gt = rps_to_gt(rps);

	/*
	 * We only रेजिस्टर the i915 ips part with पूर्णांकel-ips once everything is
	 * set up, to aव्योम पूर्णांकel-ips sneaking in and पढ़ोing bogus values.
	 */
	अगर (IS_GEN(gt->i915, 5)) अणु
		GEM_BUG_ON(ips_mchdev);
		rcu_assign_poपूर्णांकer(ips_mchdev, gt->i915);
		ips_ping_क्रम_i915_load();
	पूर्ण
पूर्ण

व्योम पूर्णांकel_rps_driver_unरेजिस्टर(काष्ठा पूर्णांकel_rps *rps)
अणु
	अगर (rcu_access_poपूर्णांकer(ips_mchdev) == rps_to_i915(rps))
		rcu_assign_poपूर्णांकer(ips_mchdev, शून्य);
पूर्ण

अटल काष्ठा drm_i915_निजी *mchdev_get(व्योम)
अणु
	काष्ठा drm_i915_निजी *i915;

	rcu_पढ़ो_lock();
	i915 = rcu_dereference(ips_mchdev);
	अगर (i915 && !kref_get_unless_zero(&i915->drm.ref))
		i915 = शून्य;
	rcu_पढ़ो_unlock();

	वापस i915;
पूर्ण

/**
 * i915_पढ़ो_mch_val - वापस value क्रम IPS use
 *
 * Calculate and वापस a value क्रम the IPS driver to use when deciding whether
 * we have thermal and घातer headroom to increase CPU or GPU घातer budget.
 */
अचिन्हित दीर्घ i915_पढ़ो_mch_val(व्योम)
अणु
	काष्ठा drm_i915_निजी *i915;
	अचिन्हित दीर्घ chipset_val = 0;
	अचिन्हित दीर्घ graphics_val = 0;
	पूर्णांकel_wakeref_t wakeref;

	i915 = mchdev_get();
	अगर (!i915)
		वापस 0;

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref) अणु
		काष्ठा पूर्णांकel_ips *ips = &i915->gt.rps.ips;

		spin_lock_irq(&mchdev_lock);
		chipset_val = __ips_chipset_val(ips);
		graphics_val = __ips_gfx_val(ips);
		spin_unlock_irq(&mchdev_lock);
	पूर्ण

	drm_dev_put(&i915->drm);
	वापस chipset_val + graphics_val;
पूर्ण
EXPORT_SYMBOL_GPL(i915_पढ़ो_mch_val);

/**
 * i915_gpu_उठाओ - उठाओ GPU frequency limit
 *
 * Raise the limit; IPS indicates we have thermal headroom.
 */
bool i915_gpu_उठाओ(व्योम)
अणु
	काष्ठा drm_i915_निजी *i915;
	काष्ठा पूर्णांकel_rps *rps;

	i915 = mchdev_get();
	अगर (!i915)
		वापस false;

	rps = &i915->gt.rps;

	spin_lock_irq(&mchdev_lock);
	अगर (rps->max_freq_softlimit < rps->max_freq)
		rps->max_freq_softlimit++;
	spin_unlock_irq(&mchdev_lock);

	drm_dev_put(&i915->drm);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(i915_gpu_उठाओ);

/**
 * i915_gpu_lower - lower GPU frequency limit
 *
 * IPS indicates we're बंद to a thermal limit, so throttle back the GPU
 * frequency maximum.
 */
bool i915_gpu_lower(व्योम)
अणु
	काष्ठा drm_i915_निजी *i915;
	काष्ठा पूर्णांकel_rps *rps;

	i915 = mchdev_get();
	अगर (!i915)
		वापस false;

	rps = &i915->gt.rps;

	spin_lock_irq(&mchdev_lock);
	अगर (rps->max_freq_softlimit > rps->min_freq)
		rps->max_freq_softlimit--;
	spin_unlock_irq(&mchdev_lock);

	drm_dev_put(&i915->drm);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(i915_gpu_lower);

/**
 * i915_gpu_busy - indicate GPU business to IPS
 *
 * Tell the IPS driver whether or not the GPU is busy.
 */
bool i915_gpu_busy(व्योम)
अणु
	काष्ठा drm_i915_निजी *i915;
	bool ret;

	i915 = mchdev_get();
	अगर (!i915)
		वापस false;

	ret = i915->gt.awake;

	drm_dev_put(&i915->drm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i915_gpu_busy);

/**
 * i915_gpu_turbo_disable - disable graphics turbo
 *
 * Disable graphics turbo by resetting the max frequency and setting the
 * current frequency to the शेष.
 */
bool i915_gpu_turbo_disable(व्योम)
अणु
	काष्ठा drm_i915_निजी *i915;
	काष्ठा पूर्णांकel_rps *rps;
	bool ret;

	i915 = mchdev_get();
	अगर (!i915)
		वापस false;

	rps = &i915->gt.rps;

	spin_lock_irq(&mchdev_lock);
	rps->max_freq_softlimit = rps->min_freq;
	ret = !__gen5_rps_set(&i915->gt.rps, rps->min_freq);
	spin_unlock_irq(&mchdev_lock);

	drm_dev_put(&i915->drm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i915_gpu_turbo_disable);

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_rps.c"
#पूर्ण_अगर
