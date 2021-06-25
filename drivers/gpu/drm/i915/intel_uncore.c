<शैली गुरु>
/*
 * Copyright तऊ 2013 Intel Corporation
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
 */

#समावेश <linux/pm_runसमय.स>
#समावेश <यंत्र/iosf_mbi.h>

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"
#समावेश "intel_pm.h"

#घोषणा FORCEWAKE_ACK_TIMEOUT_MS 50
#घोषणा GT_FIFO_TIMEOUT_MS	 10

#घोषणा __raw_posting_पढ़ो(...) ((व्योम)__raw_uncore_पढ़ो32(__VA_ARGS__))

व्योम
पूर्णांकel_uncore_mmio_debug_init_early(काष्ठा पूर्णांकel_uncore_mmio_debug *mmio_debug)
अणु
	spin_lock_init(&mmio_debug->lock);
	mmio_debug->unclaimed_mmio_check = 1;
पूर्ण

अटल व्योम mmio_debug_suspend(काष्ठा पूर्णांकel_uncore_mmio_debug *mmio_debug)
अणु
	lockdep_निश्चित_held(&mmio_debug->lock);

	/* Save and disable mmio debugging क्रम the user bypass */
	अगर (!mmio_debug->suspend_count++) अणु
		mmio_debug->saved_mmio_check = mmio_debug->unclaimed_mmio_check;
		mmio_debug->unclaimed_mmio_check = 0;
	पूर्ण
पूर्ण

अटल व्योम mmio_debug_resume(काष्ठा पूर्णांकel_uncore_mmio_debug *mmio_debug)
अणु
	lockdep_निश्चित_held(&mmio_debug->lock);

	अगर (!--mmio_debug->suspend_count)
		mmio_debug->unclaimed_mmio_check = mmio_debug->saved_mmio_check;
पूर्ण

अटल स्थिर अक्षर * स्थिर क्रमcewake_करोमुख्य_names[] = अणु
	"render",
	"blitter",
	"media",
	"vdbox0",
	"vdbox1",
	"vdbox2",
	"vdbox3",
	"vebox0",
	"vebox1",
पूर्ण;

स्थिर अक्षर *
पूर्णांकel_uncore_क्रमcewake_करोमुख्य_to_str(स्थिर क्रमागत क्रमcewake_करोमुख्य_id id)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(क्रमcewake_करोमुख्य_names) != FW_DOMAIN_ID_COUNT);

	अगर (id >= 0 && id < FW_DOMAIN_ID_COUNT)
		वापस क्रमcewake_करोमुख्य_names[id];

	WARN_ON(id);

	वापस "unknown";
पूर्ण

#घोषणा fw_ack(d) पढ़ोl((d)->reg_ack)
#घोषणा fw_set(d, val) ग_लिखोl(_MASKED_BIT_ENABLE((val)), (d)->reg_set)
#घोषणा fw_clear(d, val) ग_लिखोl(_MASKED_BIT_DISABLE((val)), (d)->reg_set)

अटल अंतरभूत व्योम
fw_करोमुख्य_reset(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d)
अणु
	/*
	 * We करोn't really know अगर the घातerwell क्रम the क्रमcewake करोमुख्य we are
	 * trying to reset here करोes exist at this poपूर्णांक (engines could be fused
	 * off in ICL+), so no रुकोing क्रम acks
	 */
	/* WaRsClearFWBitsAtReset:bdw,skl */
	fw_clear(d, 0xffff);
पूर्ण

अटल अंतरभूत व्योम
fw_करोमुख्य_arm_समयr(काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d)
अणु
	GEM_BUG_ON(d->uncore->fw_करोमुख्यs_समयr & d->mask);
	d->uncore->fw_करोमुख्यs_समयr |= d->mask;
	d->wake_count++;
	hrसमयr_start_range_ns(&d->समयr,
			       NSEC_PER_MSEC,
			       NSEC_PER_MSEC,
			       HRTIMER_MODE_REL);
पूर्ण

अटल अंतरभूत पूर्णांक
__रुको_क्रम_ack(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d,
	       स्थिर u32 ack,
	       स्थिर u32 value)
अणु
	वापस रुको_क्रम_atomic((fw_ack(d) & ack) == value,
			       FORCEWAKE_ACK_TIMEOUT_MS);
पूर्ण

अटल अंतरभूत पूर्णांक
रुको_ack_clear(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d,
	       स्थिर u32 ack)
अणु
	वापस __रुको_क्रम_ack(d, ack, 0);
पूर्ण

अटल अंतरभूत पूर्णांक
रुको_ack_set(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d,
	     स्थिर u32 ack)
अणु
	वापस __रुको_क्रम_ack(d, ack, ack);
पूर्ण

अटल अंतरभूत व्योम
fw_करोमुख्य_रुको_ack_clear(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d)
अणु
	अगर (रुको_ack_clear(d, FORCEWAKE_KERNEL)) अणु
		DRM_ERROR("%s: timed out waiting for forcewake ack to clear.\n",
			  पूर्णांकel_uncore_क्रमcewake_करोमुख्य_to_str(d->id));
		add_taपूर्णांक_क्रम_CI(d->uncore->i915, TAINT_WARN); /* CI now unreliable */
	पूर्ण
पूर्ण

क्रमागत ack_type अणु
	ACK_CLEAR = 0,
	ACK_SET
पूर्ण;

अटल पूर्णांक
fw_करोमुख्य_रुको_ack_with_fallback(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d,
				 स्थिर क्रमागत ack_type type)
अणु
	स्थिर u32 ack_bit = FORCEWAKE_KERNEL;
	स्थिर u32 value = type == ACK_SET ? ack_bit : 0;
	अचिन्हित पूर्णांक pass;
	bool ack_detected;

	/*
	 * There is a possibility of driver's wake request colliding
	 * with hardware's own wake requests and that can cause
	 * hardware to not deliver the driver's ack message.
	 *
	 * Use a fallback bit toggle to kick the gpu state machine
	 * in the hope that the original ack will be delivered aदीर्घ with
	 * the fallback ack.
	 *
	 * This workaround is described in HSDES #1604254524 and it's known as:
	 * WaRsForcewakeAddDelayForAck:skl,bxt,kbl,glk,cfl,cnl,icl
	 * although the name is a bit misleading.
	 */

	pass = 1;
	करो अणु
		रुको_ack_clear(d, FORCEWAKE_KERNEL_FALLBACK);

		fw_set(d, FORCEWAKE_KERNEL_FALLBACK);
		/* Give gt some समय to relax beक्रमe the polling frenzy */
		udelay(10 * pass);
		रुको_ack_set(d, FORCEWAKE_KERNEL_FALLBACK);

		ack_detected = (fw_ack(d) & ack_bit) == value;

		fw_clear(d, FORCEWAKE_KERNEL_FALLBACK);
	पूर्ण जबतक (!ack_detected && pass++ < 10);

	DRM_DEBUG_DRIVER("%s had to use fallback to %s ack, 0x%x (passes %u)\n",
			 पूर्णांकel_uncore_क्रमcewake_करोमुख्य_to_str(d->id),
			 type == ACK_SET ? "set" : "clear",
			 fw_ack(d),
			 pass);

	वापस ack_detected ? 0 : -ETIMEDOUT;
पूर्ण

अटल अंतरभूत व्योम
fw_करोमुख्य_रुको_ack_clear_fallback(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d)
अणु
	अगर (likely(!रुको_ack_clear(d, FORCEWAKE_KERNEL)))
		वापस;

	अगर (fw_करोमुख्य_रुको_ack_with_fallback(d, ACK_CLEAR))
		fw_करोमुख्य_रुको_ack_clear(d);
पूर्ण

अटल अंतरभूत व्योम
fw_करोमुख्य_get(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d)
अणु
	fw_set(d, FORCEWAKE_KERNEL);
पूर्ण

अटल अंतरभूत व्योम
fw_करोमुख्य_रुको_ack_set(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d)
अणु
	अगर (रुको_ack_set(d, FORCEWAKE_KERNEL)) अणु
		DRM_ERROR("%s: timed out waiting for forcewake ack request.\n",
			  पूर्णांकel_uncore_क्रमcewake_करोमुख्य_to_str(d->id));
		add_taपूर्णांक_क्रम_CI(d->uncore->i915, TAINT_WARN); /* CI now unreliable */
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
fw_करोमुख्य_रुको_ack_set_fallback(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d)
अणु
	अगर (likely(!रुको_ack_set(d, FORCEWAKE_KERNEL)))
		वापस;

	अगर (fw_करोमुख्य_रुको_ack_with_fallback(d, ACK_SET))
		fw_करोमुख्य_रुको_ack_set(d);
पूर्ण

अटल अंतरभूत व्योम
fw_करोमुख्य_put(स्थिर काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d)
अणु
	fw_clear(d, FORCEWAKE_KERNEL);
पूर्ण

अटल व्योम
fw_करोमुख्यs_get(काष्ठा पूर्णांकel_uncore *uncore, क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d;
	अचिन्हित पूर्णांक पंचांगp;

	GEM_BUG_ON(fw_करोमुख्यs & ~uncore->fw_करोमुख्यs);

	क्रम_each_fw_करोमुख्य_masked(d, fw_करोमुख्यs, uncore, पंचांगp) अणु
		fw_करोमुख्य_रुको_ack_clear(d);
		fw_करोमुख्य_get(d);
	पूर्ण

	क्रम_each_fw_करोमुख्य_masked(d, fw_करोमुख्यs, uncore, पंचांगp)
		fw_करोमुख्य_रुको_ack_set(d);

	uncore->fw_करोमुख्यs_active |= fw_करोमुख्यs;
पूर्ण

अटल व्योम
fw_करोमुख्यs_get_with_fallback(काष्ठा पूर्णांकel_uncore *uncore,
			     क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d;
	अचिन्हित पूर्णांक पंचांगp;

	GEM_BUG_ON(fw_करोमुख्यs & ~uncore->fw_करोमुख्यs);

	क्रम_each_fw_करोमुख्य_masked(d, fw_करोमुख्यs, uncore, पंचांगp) अणु
		fw_करोमुख्य_रुको_ack_clear_fallback(d);
		fw_करोमुख्य_get(d);
	पूर्ण

	क्रम_each_fw_करोमुख्य_masked(d, fw_करोमुख्यs, uncore, पंचांगp)
		fw_करोमुख्य_रुको_ack_set_fallback(d);

	uncore->fw_करोमुख्यs_active |= fw_करोमुख्यs;
पूर्ण

अटल व्योम
fw_करोमुख्यs_put(काष्ठा पूर्णांकel_uncore *uncore, क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d;
	अचिन्हित पूर्णांक पंचांगp;

	GEM_BUG_ON(fw_करोमुख्यs & ~uncore->fw_करोमुख्यs);

	क्रम_each_fw_करोमुख्य_masked(d, fw_करोमुख्यs, uncore, पंचांगp)
		fw_करोमुख्य_put(d);

	uncore->fw_करोमुख्यs_active &= ~fw_करोमुख्यs;
पूर्ण

अटल व्योम
fw_करोमुख्यs_reset(काष्ठा पूर्णांकel_uncore *uncore,
		 क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (!fw_करोमुख्यs)
		वापस;

	GEM_BUG_ON(fw_करोमुख्यs & ~uncore->fw_करोमुख्यs);

	क्रम_each_fw_करोमुख्य_masked(d, fw_करोमुख्यs, uncore, पंचांगp)
		fw_करोमुख्य_reset(d);
पूर्ण

अटल अंतरभूत u32 gt_thपढ़ो_status(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 val;

	val = __raw_uncore_पढ़ो32(uncore, GEN6_GT_THREAD_STATUS_REG);
	val &= GEN6_GT_THREAD_STATUS_CORE_MASK;

	वापस val;
पूर्ण

अटल व्योम __gen6_gt_रुको_क्रम_thपढ़ो_c0(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	/*
	 * w/a क्रम a sporadic पढ़ो वापसing 0 by रुकोing क्रम the GT
	 * thपढ़ो to wake up.
	 */
	drm_WARN_ONCE(&uncore->i915->drm,
		      रुको_क्रम_atomic_us(gt_thपढ़ो_status(uncore) == 0, 5000),
		      "GT thread status wait timed out\n");
पूर्ण

अटल व्योम fw_करोमुख्यs_get_with_thपढ़ो_status(काष्ठा पूर्णांकel_uncore *uncore,
					      क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	fw_करोमुख्यs_get(uncore, fw_करोमुख्यs);

	/* WaRsForcewakeWaitTC0:snb,ivb,hsw,bdw,vlv */
	__gen6_gt_रुको_क्रम_thपढ़ो_c0(uncore);
पूर्ण

अटल अंतरभूत u32 fअगरo_मुक्त_entries(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 count = __raw_uncore_पढ़ो32(uncore, GTFIFOCTL);

	वापस count & GT_FIFO_FREE_ENTRIES_MASK;
पूर्ण

अटल व्योम __gen6_gt_रुको_क्रम_fअगरo(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 n;

	/* On VLV, FIFO will be shared by both SW and HW.
	 * So, we need to पढ़ो the FREE_ENTRIES everyसमय */
	अगर (IS_VALLEYVIEW(uncore->i915))
		n = fअगरo_मुक्त_entries(uncore);
	अन्यथा
		n = uncore->fअगरo_count;

	अगर (n <= GT_FIFO_NUM_RESERVED_ENTRIES) अणु
		अगर (रुको_क्रम_atomic((n = fअगरo_मुक्त_entries(uncore)) >
				    GT_FIFO_NUM_RESERVED_ENTRIES,
				    GT_FIFO_TIMEOUT_MS)) अणु
			drm_dbg(&uncore->i915->drm,
				"GT_FIFO timeout, entries: %u\n", n);
			वापस;
		पूर्ण
	पूर्ण

	uncore->fअगरo_count = n - 1;
पूर्ण

अटल क्रमागत hrसमयr_restart
पूर्णांकel_uncore_fw_release_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *करोमुख्य =
	       container_of(समयr, काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य, समयr);
	काष्ठा पूर्णांकel_uncore *uncore = करोमुख्य->uncore;
	अचिन्हित दीर्घ irqflags;

	निश्चित_rpm_device_not_suspended(uncore->rpm);

	अगर (xchg(&करोमुख्य->active, false))
		वापस HRTIMER_RESTART;

	spin_lock_irqsave(&uncore->lock, irqflags);

	uncore->fw_करोमुख्यs_समयr &= ~करोमुख्य->mask;

	GEM_BUG_ON(!करोमुख्य->wake_count);
	अगर (--करोमुख्य->wake_count == 0)
		uncore->funcs.क्रमce_wake_put(uncore, करोमुख्य->mask);

	spin_unlock_irqrestore(&uncore->lock, irqflags);

	वापस HRTIMER_NORESTART;
पूर्ण

/* Note callers must have acquired the PUNIT->PMIC bus, beक्रमe calling this. */
अटल अचिन्हित पूर्णांक
पूर्णांकel_uncore_क्रमcewake_reset(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	अचिन्हित दीर्घ irqflags;
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *करोमुख्य;
	पूर्णांक retry_count = 100;
	क्रमागत क्रमcewake_करोमुख्यs fw, active_करोमुख्यs;

	iosf_mbi_निश्चित_punit_acquired();

	/* Hold uncore.lock across reset to prevent any रेजिस्टर access
	 * with क्रमcewake not set correctly. Wait until all pending
	 * समयrs are run beक्रमe holding.
	 */
	जबतक (1) अणु
		अचिन्हित पूर्णांक पंचांगp;

		active_करोमुख्यs = 0;

		क्रम_each_fw_करोमुख्य(करोमुख्य, uncore, पंचांगp) अणु
			smp_store_mb(करोमुख्य->active, false);
			अगर (hrसमयr_cancel(&करोमुख्य->समयr) == 0)
				जारी;

			पूर्णांकel_uncore_fw_release_समयr(&करोमुख्य->समयr);
		पूर्ण

		spin_lock_irqsave(&uncore->lock, irqflags);

		क्रम_each_fw_करोमुख्य(करोमुख्य, uncore, पंचांगp) अणु
			अगर (hrसमयr_active(&करोमुख्य->समयr))
				active_करोमुख्यs |= करोमुख्य->mask;
		पूर्ण

		अगर (active_करोमुख्यs == 0)
			अवरोध;

		अगर (--retry_count == 0) अणु
			drm_err(&uncore->i915->drm, "Timed out waiting for forcewake timers to finish\n");
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(&uncore->lock, irqflags);
		cond_resched();
	पूर्ण

	drm_WARN_ON(&uncore->i915->drm, active_करोमुख्यs);

	fw = uncore->fw_करोमुख्यs_active;
	अगर (fw)
		uncore->funcs.क्रमce_wake_put(uncore, fw);

	fw_करोमुख्यs_reset(uncore, uncore->fw_करोमुख्यs);
	निश्चित_क्रमcewakes_inactive(uncore);

	spin_unlock_irqrestore(&uncore->lock, irqflags);

	वापस fw; /* track the lost user क्रमcewake करोमुख्यs */
पूर्ण

अटल bool
fpga_check_क्रम_unclaimed_mmio(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 dbg;

	dbg = __raw_uncore_पढ़ो32(uncore, FPGA_DBG);
	अगर (likely(!(dbg & FPGA_DBG_RM_NOCLAIM)))
		वापस false;

	/*
	 * Bugs in PCI programming (or failing hardware) can occasionally cause
	 * us to lose access to the MMIO BAR.  When this happens, रेजिस्टर
	 * पढ़ोs will come back with 0xFFFFFFFF क्रम every रेजिस्टर and things
	 * go bad very quickly.  Let's try to detect that special हाल and at
	 * least try to prपूर्णांक a more inक्रमmative message about what has
	 * happened.
	 *
	 * During normal operation the FPGA_DBG रेजिस्टर has several unused
	 * bits that will always पढ़ो back as 0's so we can use them as canaries
	 * to recognize when MMIO accesses are just busted.
	 */
	अगर (unlikely(dbg == ~0))
		drm_err(&uncore->i915->drm,
			"Lost access to MMIO BAR; all registers now read back as 0xFFFFFFFF!\n");

	__raw_uncore_ग_लिखो32(uncore, FPGA_DBG, FPGA_DBG_RM_NOCLAIM);

	वापस true;
पूर्ण

अटल bool
vlv_check_क्रम_unclaimed_mmio(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 cer;

	cer = __raw_uncore_पढ़ो32(uncore, CLAIM_ER);
	अगर (likely(!(cer & (CLAIM_ER_OVERFLOW | CLAIM_ER_CTR_MASK))))
		वापस false;

	__raw_uncore_ग_लिखो32(uncore, CLAIM_ER, CLAIM_ER_CLR);

	वापस true;
पूर्ण

अटल bool
gen6_check_क्रम_fअगरo_debug(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 fअगरodbg;

	fअगरodbg = __raw_uncore_पढ़ो32(uncore, GTFIFODBG);

	अगर (unlikely(fअगरodbg)) अणु
		drm_dbg(&uncore->i915->drm, "GTFIFODBG = 0x08%x\n", fअगरodbg);
		__raw_uncore_ग_लिखो32(uncore, GTFIFODBG, fअगरodbg);
	पूर्ण

	वापस fअगरodbg;
पूर्ण

अटल bool
check_क्रम_unclaimed_mmio(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	bool ret = false;

	lockdep_निश्चित_held(&uncore->debug->lock);

	अगर (uncore->debug->suspend_count)
		वापस false;

	अगर (पूर्णांकel_uncore_has_fpga_dbg_unclaimed(uncore))
		ret |= fpga_check_क्रम_unclaimed_mmio(uncore);

	अगर (पूर्णांकel_uncore_has_dbg_unclaimed(uncore))
		ret |= vlv_check_क्रम_unclaimed_mmio(uncore);

	अगर (पूर्णांकel_uncore_has_fअगरo(uncore))
		ret |= gen6_check_क्रम_fअगरo_debug(uncore);

	वापस ret;
पूर्ण

अटल व्योम क्रमcewake_early_sanitize(काष्ठा पूर्णांकel_uncore *uncore,
				     अचिन्हित पूर्णांक restore_क्रमcewake)
अणु
	GEM_BUG_ON(!पूर्णांकel_uncore_has_क्रमcewake(uncore));

	/* WaDisableShaकरोwRegForCpd:chv */
	अगर (IS_CHERRYVIEW(uncore->i915)) अणु
		__raw_uncore_ग_लिखो32(uncore, GTFIFOCTL,
				     __raw_uncore_पढ़ो32(uncore, GTFIFOCTL) |
				     GT_FIFO_CTL_BLOCK_ALL_POLICY_STALL |
				     GT_FIFO_CTL_RC6_POLICY_STALL);
	पूर्ण

	iosf_mbi_punit_acquire();
	पूर्णांकel_uncore_क्रमcewake_reset(uncore);
	अगर (restore_क्रमcewake) अणु
		spin_lock_irq(&uncore->lock);
		uncore->funcs.क्रमce_wake_get(uncore, restore_क्रमcewake);

		अगर (पूर्णांकel_uncore_has_fअगरo(uncore))
			uncore->fअगरo_count = fअगरo_मुक्त_entries(uncore);
		spin_unlock_irq(&uncore->lock);
	पूर्ण
	iosf_mbi_punit_release();
पूर्ण

व्योम पूर्णांकel_uncore_suspend(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	अगर (!पूर्णांकel_uncore_has_क्रमcewake(uncore))
		वापस;

	iosf_mbi_punit_acquire();
	iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier_unlocked(
		&uncore->pmic_bus_access_nb);
	uncore->fw_करोमुख्यs_saved = पूर्णांकel_uncore_क्रमcewake_reset(uncore);
	iosf_mbi_punit_release();
पूर्ण

व्योम पूर्णांकel_uncore_resume_early(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	अचिन्हित पूर्णांक restore_क्रमcewake;

	अगर (पूर्णांकel_uncore_unclaimed_mmio(uncore))
		drm_dbg(&uncore->i915->drm, "unclaimed mmio detected on resume, clearing\n");

	अगर (!पूर्णांकel_uncore_has_क्रमcewake(uncore))
		वापस;

	restore_क्रमcewake = fetch_and_zero(&uncore->fw_करोमुख्यs_saved);
	क्रमcewake_early_sanitize(uncore, restore_क्रमcewake);

	iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier(&uncore->pmic_bus_access_nb);
पूर्ण

व्योम पूर्णांकel_uncore_runसमय_resume(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	अगर (!पूर्णांकel_uncore_has_क्रमcewake(uncore))
		वापस;

	iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier(&uncore->pmic_bus_access_nb);
पूर्ण

अटल व्योम __पूर्णांकel_uncore_क्रमcewake_get(काष्ठा पूर्णांकel_uncore *uncore,
					 क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक पंचांगp;

	fw_करोमुख्यs &= uncore->fw_करोमुख्यs;

	क्रम_each_fw_करोमुख्य_masked(करोमुख्य, fw_करोमुख्यs, uncore, पंचांगp) अणु
		अगर (करोमुख्य->wake_count++) अणु
			fw_करोमुख्यs &= ~करोमुख्य->mask;
			करोमुख्य->active = true;
		पूर्ण
	पूर्ण

	अगर (fw_करोमुख्यs)
		uncore->funcs.क्रमce_wake_get(uncore, fw_करोमुख्यs);
पूर्ण

/**
 * पूर्णांकel_uncore_क्रमcewake_get - grab क्रमcewake करोमुख्य references
 * @uncore: the पूर्णांकel_uncore काष्ठाure
 * @fw_करोमुख्यs: क्रमcewake करोमुख्यs to get reference on
 *
 * This function can be used get GT's क्रमcewake करोमुख्य references.
 * Normal रेजिस्टर access will handle the क्रमcewake करोमुख्यs स्वतःmatically.
 * However अगर some sequence requires the GT to not घातer करोwn a particular
 * क्रमcewake करोमुख्यs this function should be called at the beginning of the
 * sequence. And subsequently the reference should be dropped by symmetric
 * call to पूर्णांकel_unक्रमce_क्रमcewake_put(). Usually caller wants all the करोमुख्यs
 * to be kept awake so the @fw_करोमुख्यs would be then FORCEWAKE_ALL.
 */
व्योम पूर्णांकel_uncore_क्रमcewake_get(काष्ठा पूर्णांकel_uncore *uncore,
				क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!uncore->funcs.क्रमce_wake_get)
		वापस;

	निश्चित_rpm_wakelock_held(uncore->rpm);

	spin_lock_irqsave(&uncore->lock, irqflags);
	__पूर्णांकel_uncore_क्रमcewake_get(uncore, fw_करोमुख्यs);
	spin_unlock_irqrestore(&uncore->lock, irqflags);
पूर्ण

/**
 * पूर्णांकel_uncore_क्रमcewake_user_get - claim क्रमcewake on behalf of userspace
 * @uncore: the पूर्णांकel_uncore काष्ठाure
 *
 * This function is a wrapper around पूर्णांकel_uncore_क्रमcewake_get() to acquire
 * the GT घातerwell and in the process disable our debugging क्रम the
 * duration of userspace's bypass.
 */
व्योम पूर्णांकel_uncore_क्रमcewake_user_get(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	spin_lock_irq(&uncore->lock);
	अगर (!uncore->user_क्रमcewake_count++) अणु
		पूर्णांकel_uncore_क्रमcewake_get__locked(uncore, FORCEWAKE_ALL);
		spin_lock(&uncore->debug->lock);
		mmio_debug_suspend(uncore->debug);
		spin_unlock(&uncore->debug->lock);
	पूर्ण
	spin_unlock_irq(&uncore->lock);
पूर्ण

/**
 * पूर्णांकel_uncore_क्रमcewake_user_put - release क्रमcewake on behalf of userspace
 * @uncore: the पूर्णांकel_uncore काष्ठाure
 *
 * This function complements पूर्णांकel_uncore_क्रमcewake_user_get() and releases
 * the GT घातerwell taken on behalf of the userspace bypass.
 */
व्योम पूर्णांकel_uncore_क्रमcewake_user_put(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	spin_lock_irq(&uncore->lock);
	अगर (!--uncore->user_क्रमcewake_count) अणु
		spin_lock(&uncore->debug->lock);
		mmio_debug_resume(uncore->debug);

		अगर (check_क्रम_unclaimed_mmio(uncore))
			drm_info(&uncore->i915->drm,
				 "Invalid mmio detected during user access\n");
		spin_unlock(&uncore->debug->lock);

		पूर्णांकel_uncore_क्रमcewake_put__locked(uncore, FORCEWAKE_ALL);
	पूर्ण
	spin_unlock_irq(&uncore->lock);
पूर्ण

/**
 * पूर्णांकel_uncore_क्रमcewake_get__locked - grab क्रमcewake करोमुख्य references
 * @uncore: the पूर्णांकel_uncore काष्ठाure
 * @fw_करोमुख्यs: क्रमcewake करोमुख्यs to get reference on
 *
 * See पूर्णांकel_uncore_क्रमcewake_get(). This variant places the onus
 * on the caller to explicitly handle the dev_priv->uncore.lock spinlock.
 */
व्योम पूर्णांकel_uncore_क्रमcewake_get__locked(काष्ठा पूर्णांकel_uncore *uncore,
					क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	lockdep_निश्चित_held(&uncore->lock);

	अगर (!uncore->funcs.क्रमce_wake_get)
		वापस;

	__पूर्णांकel_uncore_क्रमcewake_get(uncore, fw_करोमुख्यs);
पूर्ण

अटल व्योम __पूर्णांकel_uncore_क्रमcewake_put(काष्ठा पूर्णांकel_uncore *uncore,
					 क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक पंचांगp;

	fw_करोमुख्यs &= uncore->fw_करोमुख्यs;

	क्रम_each_fw_करोमुख्य_masked(करोमुख्य, fw_करोमुख्यs, uncore, पंचांगp) अणु
		GEM_BUG_ON(!करोमुख्य->wake_count);

		अगर (--करोमुख्य->wake_count) अणु
			करोमुख्य->active = true;
			जारी;
		पूर्ण

		uncore->funcs.क्रमce_wake_put(uncore, करोमुख्य->mask);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_uncore_क्रमcewake_put - release a क्रमcewake करोमुख्य reference
 * @uncore: the पूर्णांकel_uncore काष्ठाure
 * @fw_करोमुख्यs: क्रमcewake करोमुख्यs to put references
 *
 * This function drops the device-level क्रमcewakes क्रम specअगरied
 * करोमुख्यs obtained by पूर्णांकel_uncore_क्रमcewake_get().
 */
व्योम पूर्णांकel_uncore_क्रमcewake_put(काष्ठा पूर्णांकel_uncore *uncore,
				क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!uncore->funcs.क्रमce_wake_put)
		वापस;

	spin_lock_irqsave(&uncore->lock, irqflags);
	__पूर्णांकel_uncore_क्रमcewake_put(uncore, fw_करोमुख्यs);
	spin_unlock_irqrestore(&uncore->lock, irqflags);
पूर्ण

/**
 * पूर्णांकel_uncore_क्रमcewake_flush - flush the delayed release
 * @uncore: the पूर्णांकel_uncore काष्ठाure
 * @fw_करोमुख्यs: क्रमcewake करोमुख्यs to flush
 */
व्योम पूर्णांकel_uncore_क्रमcewake_flush(काष्ठा पूर्णांकel_uncore *uncore,
				  क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (!uncore->funcs.क्रमce_wake_put)
		वापस;

	fw_करोमुख्यs &= uncore->fw_करोमुख्यs;
	क्रम_each_fw_करोमुख्य_masked(करोमुख्य, fw_करोमुख्यs, uncore, पंचांगp) अणु
		WRITE_ONCE(करोमुख्य->active, false);
		अगर (hrसमयr_cancel(&करोमुख्य->समयr))
			पूर्णांकel_uncore_fw_release_समयr(&करोमुख्य->समयr);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_uncore_क्रमcewake_put__locked - grab क्रमcewake करोमुख्य references
 * @uncore: the पूर्णांकel_uncore काष्ठाure
 * @fw_करोमुख्यs: क्रमcewake करोमुख्यs to get reference on
 *
 * See पूर्णांकel_uncore_क्रमcewake_put(). This variant places the onus
 * on the caller to explicitly handle the dev_priv->uncore.lock spinlock.
 */
व्योम पूर्णांकel_uncore_क्रमcewake_put__locked(काष्ठा पूर्णांकel_uncore *uncore,
					क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	lockdep_निश्चित_held(&uncore->lock);

	अगर (!uncore->funcs.क्रमce_wake_put)
		वापस;

	__पूर्णांकel_uncore_क्रमcewake_put(uncore, fw_करोमुख्यs);
पूर्ण

व्योम निश्चित_क्रमcewakes_inactive(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	अगर (!uncore->funcs.क्रमce_wake_get)
		वापस;

	drm_WARN(&uncore->i915->drm, uncore->fw_करोमुख्यs_active,
		 "Expected all fw_domains to be inactive, but %08x are still on\n",
		 uncore->fw_करोमुख्यs_active);
पूर्ण

व्योम निश्चित_क्रमcewakes_active(काष्ठा पूर्णांकel_uncore *uncore,
			      क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (!IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM))
		वापस;

	अगर (!uncore->funcs.क्रमce_wake_get)
		वापस;

	spin_lock_irq(&uncore->lock);

	निश्चित_rpm_wakelock_held(uncore->rpm);

	fw_करोमुख्यs &= uncore->fw_करोमुख्यs;
	drm_WARN(&uncore->i915->drm, fw_करोमुख्यs & ~uncore->fw_करोमुख्यs_active,
		 "Expected %08x fw_domains to be active, but %08x are off\n",
		 fw_करोमुख्यs, fw_करोमुख्यs & ~uncore->fw_करोमुख्यs_active);

	/*
	 * Check that the caller has an explicit wakeref and we करोn't mistake
	 * it क्रम the स्वतः wakeref.
	 */
	क्रम_each_fw_करोमुख्य_masked(करोमुख्य, fw_करोमुख्यs, uncore, पंचांगp) अणु
		अचिन्हित पूर्णांक actual = READ_ONCE(करोमुख्य->wake_count);
		अचिन्हित पूर्णांक expect = 1;

		अगर (uncore->fw_करोमुख्यs_समयr & करोमुख्य->mask)
			expect++; /* pending स्वतःmatic release */

		अगर (drm_WARN(&uncore->i915->drm, actual < expect,
			     "Expected domain %d to be held awake by caller, count=%d\n",
			     करोमुख्य->id, actual))
			अवरोध;
	पूर्ण

	spin_unlock_irq(&uncore->lock);
पूर्ण

/* We give fast paths क्रम the really cool रेजिस्टरs */
#घोषणा NEEDS_FORCE_WAKE(reg) ((reg) < 0x40000)

#घोषणा __gen6_reg_पढ़ो_fw_करोमुख्यs(uncore, offset) \
(अणु \
	क्रमागत क्रमcewake_करोमुख्यs __fwd; \
	अगर (NEEDS_FORCE_WAKE(offset)) \
		__fwd = FORCEWAKE_RENDER; \
	अन्यथा \
		__fwd = 0; \
	__fwd; \
पूर्ण)

अटल पूर्णांक fw_range_cmp(u32 offset, स्थिर काष्ठा पूर्णांकel_क्रमcewake_range *entry)
अणु
	अगर (offset < entry->start)
		वापस -1;
	अन्यथा अगर (offset > entry->end)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* Copied and "macroized" from lib/द्वा_खोज.c */
#घोषणा BSEARCH(key, base, num, cmp) (अणु                                 \
	अचिन्हित पूर्णांक start__ = 0, end__ = (num);                        \
	typeof(base) result__ = शून्य;                                   \
	जबतक (start__ < end__) अणु                                       \
		अचिन्हित पूर्णांक mid__ = start__ + (end__ - start__) / 2;   \
		पूर्णांक ret__ = (cmp)((key), (base) + mid__);               \
		अगर (ret__ < 0) अणु                                        \
			end__ = mid__;                                  \
		पूर्ण अन्यथा अगर (ret__ > 0) अणु                                 \
			start__ = mid__ + 1;                            \
		पूर्ण अन्यथा अणु                                                \
			result__ = (base) + mid__;                      \
			अवरोध;                                          \
		पूर्ण                                                       \
	पूर्ण                                                               \
	result__;                                                       \
पूर्ण)

अटल क्रमागत क्रमcewake_करोमुख्यs
find_fw_करोमुख्य(काष्ठा पूर्णांकel_uncore *uncore, u32 offset)
अणु
	स्थिर काष्ठा पूर्णांकel_क्रमcewake_range *entry;

	entry = BSEARCH(offset,
			uncore->fw_करोमुख्यs_table,
			uncore->fw_करोमुख्यs_table_entries,
			fw_range_cmp);

	अगर (!entry)
		वापस 0;

	/*
	 * The list of FW करोमुख्यs depends on the SKU in gen11+ so we
	 * can't determine it अटलally. We use FORCEWAKE_ALL and
	 * translate it here to the list of available करोमुख्यs.
	 */
	अगर (entry->करोमुख्यs == FORCEWAKE_ALL)
		वापस uncore->fw_करोमुख्यs;

	drm_WARN(&uncore->i915->drm, entry->करोमुख्यs & ~uncore->fw_करोमुख्यs,
		 "Uninitialized forcewake domain(s) 0x%x accessed at 0x%x\n",
		 entry->करोमुख्यs & ~uncore->fw_करोमुख्यs, offset);

	वापस entry->करोमुख्यs;
पूर्ण

#घोषणा GEN_FW_RANGE(s, e, d) \
	अणु .start = (s), .end = (e), .करोमुख्यs = (d) पूर्ण

/* *Must* be sorted by offset ranges! See पूर्णांकel_fw_table_check(). */
अटल स्थिर काष्ठा पूर्णांकel_क्रमcewake_range __vlv_fw_ranges[] = अणु
	GEN_FW_RANGE(0x2000, 0x3fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x5000, 0x7fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xb000, 0x11fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x12000, 0x13fff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x22000, 0x23fff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x2e000, 0x2ffff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x30000, 0x3ffff, FORCEWAKE_MEDIA),
पूर्ण;

#घोषणा __fwtable_reg_पढ़ो_fw_करोमुख्यs(uncore, offset) \
(अणु \
	क्रमागत क्रमcewake_करोमुख्यs __fwd = 0; \
	अगर (NEEDS_FORCE_WAKE((offset))) \
		__fwd = find_fw_करोमुख्य(uncore, offset); \
	__fwd; \
पूर्ण)

#घोषणा __gen11_fwtable_reg_पढ़ो_fw_करोमुख्यs(uncore, offset) \
	find_fw_करोमुख्य(uncore, offset)

#घोषणा __gen12_fwtable_reg_पढ़ो_fw_करोमुख्यs(uncore, offset) \
	find_fw_करोमुख्य(uncore, offset)

/* *Must* be sorted by offset! See पूर्णांकel_shaकरोw_table_check(). */
अटल स्थिर i915_reg_t gen8_shaकरोwed_regs[] = अणु
	RING_TAIL(RENDER_RING_BASE),	/* 0x2000 (base) */
	GEN6_RPNSWREQ,			/* 0xA008 */
	GEN6_RC_VIDEO_FREQ,		/* 0xA00C */
	RING_TAIL(GEN6_BSD_RING_BASE),	/* 0x12000 (base) */
	RING_TAIL(VEBOX_RING_BASE),	/* 0x1a000 (base) */
	RING_TAIL(BLT_RING_BASE),	/* 0x22000 (base) */
	/* TODO: Other रेजिस्टरs are not yet used */
पूर्ण;

अटल स्थिर i915_reg_t gen11_shaकरोwed_regs[] = अणु
	RING_TAIL(RENDER_RING_BASE),		/* 0x2000 (base) */
	GEN6_RPNSWREQ,				/* 0xA008 */
	GEN6_RC_VIDEO_FREQ,			/* 0xA00C */
	RING_TAIL(BLT_RING_BASE),		/* 0x22000 (base) */
	RING_TAIL(GEN11_BSD_RING_BASE),		/* 0x1C0000 (base) */
	RING_TAIL(GEN11_BSD2_RING_BASE),	/* 0x1C4000 (base) */
	RING_TAIL(GEN11_VEBOX_RING_BASE),	/* 0x1C8000 (base) */
	RING_TAIL(GEN11_BSD3_RING_BASE),	/* 0x1D0000 (base) */
	RING_TAIL(GEN11_BSD4_RING_BASE),	/* 0x1D4000 (base) */
	RING_TAIL(GEN11_VEBOX2_RING_BASE),	/* 0x1D8000 (base) */
	/* TODO: Other रेजिस्टरs are not yet used */
पूर्ण;

अटल स्थिर i915_reg_t gen12_shaकरोwed_regs[] = अणु
	RING_TAIL(RENDER_RING_BASE),		/* 0x2000 (base) */
	GEN6_RPNSWREQ,				/* 0xA008 */
	GEN6_RC_VIDEO_FREQ,			/* 0xA00C */
	RING_TAIL(BLT_RING_BASE),		/* 0x22000 (base) */
	RING_TAIL(GEN11_BSD_RING_BASE),		/* 0x1C0000 (base) */
	RING_TAIL(GEN11_BSD2_RING_BASE),	/* 0x1C4000 (base) */
	RING_TAIL(GEN11_VEBOX_RING_BASE),	/* 0x1C8000 (base) */
	RING_TAIL(GEN11_BSD3_RING_BASE),	/* 0x1D0000 (base) */
	RING_TAIL(GEN11_BSD4_RING_BASE),	/* 0x1D4000 (base) */
	RING_TAIL(GEN11_VEBOX2_RING_BASE),	/* 0x1D8000 (base) */
	/* TODO: Other रेजिस्टरs are not yet used */
पूर्ण;

अटल पूर्णांक mmio_reg_cmp(u32 key, स्थिर i915_reg_t *reg)
अणु
	u32 offset = i915_mmio_reg_offset(*reg);

	अगर (key < offset)
		वापस -1;
	अन्यथा अगर (key > offset)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा __is_genX_shaकरोwed(x) \
अटल bool is_gen##x##_shaकरोwed(u32 offset) \
अणु \
	स्थिर i915_reg_t *regs = gen##x##_shaकरोwed_regs; \
	वापस BSEARCH(offset, regs, ARRAY_SIZE(gen##x##_shaकरोwed_regs), \
		       mmio_reg_cmp); \
पूर्ण

__is_genX_shaकरोwed(8)
__is_genX_shaकरोwed(11)
__is_genX_shaकरोwed(12)

अटल क्रमागत क्रमcewake_करोमुख्यs
gen6_reg_ग_लिखो_fw_करोमुख्यs(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg)
अणु
	वापस FORCEWAKE_RENDER;
पूर्ण

#घोषणा __gen8_reg_ग_लिखो_fw_करोमुख्यs(uncore, offset) \
(अणु \
	क्रमागत क्रमcewake_करोमुख्यs __fwd; \
	अगर (NEEDS_FORCE_WAKE(offset) && !is_gen8_shaकरोwed(offset)) \
		__fwd = FORCEWAKE_RENDER; \
	अन्यथा \
		__fwd = 0; \
	__fwd; \
पूर्ण)

/* *Must* be sorted by offset ranges! See पूर्णांकel_fw_table_check(). */
अटल स्थिर काष्ठा पूर्णांकel_क्रमcewake_range __chv_fw_ranges[] = अणु
	GEN_FW_RANGE(0x2000, 0x3fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x4000, 0x4fff, FORCEWAKE_RENDER | FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x5200, 0x7fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8000, 0x82ff, FORCEWAKE_RENDER | FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x8300, 0x84ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8500, 0x85ff, FORCEWAKE_RENDER | FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x8800, 0x88ff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x9000, 0xafff, FORCEWAKE_RENDER | FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0xb000, 0xb47f, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xd000, 0xd7ff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0xe000, 0xe7ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xf000, 0xffff, FORCEWAKE_RENDER | FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x12000, 0x13fff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x1a000, 0x1bfff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x1e800, 0x1e9ff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x30000, 0x37fff, FORCEWAKE_MEDIA),
पूर्ण;

#घोषणा __fwtable_reg_ग_लिखो_fw_करोमुख्यs(uncore, offset) \
(अणु \
	क्रमागत क्रमcewake_करोमुख्यs __fwd = 0; \
	अगर (NEEDS_FORCE_WAKE((offset)) && !is_gen8_shaकरोwed(offset)) \
		__fwd = find_fw_करोमुख्य(uncore, offset); \
	__fwd; \
पूर्ण)

#घोषणा __gen11_fwtable_reg_ग_लिखो_fw_करोमुख्यs(uncore, offset) \
(अणु \
	क्रमागत क्रमcewake_करोमुख्यs __fwd = 0; \
	स्थिर u32 __offset = (offset); \
	अगर (!is_gen11_shaकरोwed(__offset)) \
		__fwd = find_fw_करोमुख्य(uncore, __offset); \
	__fwd; \
पूर्ण)

#घोषणा __gen12_fwtable_reg_ग_लिखो_fw_करोमुख्यs(uncore, offset) \
(अणु \
	क्रमागत क्रमcewake_करोमुख्यs __fwd = 0; \
	स्थिर u32 __offset = (offset); \
	अगर (!is_gen12_shaकरोwed(__offset)) \
		__fwd = find_fw_करोमुख्य(uncore, __offset); \
	__fwd; \
पूर्ण)

/* *Must* be sorted by offset ranges! See पूर्णांकel_fw_table_check(). */
अटल स्थिर काष्ठा पूर्णांकel_क्रमcewake_range __gen9_fw_ranges[] = अणु
	GEN_FW_RANGE(0x0, 0xaff, FORCEWAKE_GT),
	GEN_FW_RANGE(0xb00, 0x1fff, 0), /* uncore range */
	GEN_FW_RANGE(0x2000, 0x26ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x2700, 0x2fff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x3000, 0x3fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x4000, 0x51ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x5200, 0x7fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8000, 0x812f, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8130, 0x813f, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x8140, 0x815f, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8160, 0x82ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8300, 0x84ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8500, 0x87ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8800, 0x89ff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x8a00, 0x8bff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8c00, 0x8cff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8d00, 0x93ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x9400, 0x97ff, FORCEWAKE_RENDER | FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x9800, 0xafff, FORCEWAKE_GT),
	GEN_FW_RANGE(0xb000, 0xb47f, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xb480, 0xcfff, FORCEWAKE_GT),
	GEN_FW_RANGE(0xd000, 0xd7ff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0xd800, 0xdfff, FORCEWAKE_GT),
	GEN_FW_RANGE(0xe000, 0xe8ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xe900, 0x11fff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x12000, 0x13fff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x14000, 0x19fff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x1a000, 0x1e9ff, FORCEWAKE_MEDIA),
	GEN_FW_RANGE(0x1ea00, 0x243ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x24400, 0x247ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x24800, 0x2ffff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x30000, 0x3ffff, FORCEWAKE_MEDIA),
पूर्ण;

/* *Must* be sorted by offset ranges! See पूर्णांकel_fw_table_check(). */
अटल स्थिर काष्ठा पूर्णांकel_क्रमcewake_range __gen11_fw_ranges[] = अणु
	GEN_FW_RANGE(0x0, 0x1fff, 0), /* uncore range */
	GEN_FW_RANGE(0x2000, 0x26ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x2700, 0x2fff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x3000, 0x3fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x4000, 0x51ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x5200, 0x7fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8000, 0x813f, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8140, 0x815f, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8160, 0x82ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8300, 0x84ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8500, 0x87ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8800, 0x8bff, 0),
	GEN_FW_RANGE(0x8c00, 0x8cff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8d00, 0x94cf, FORCEWAKE_GT),
	GEN_FW_RANGE(0x94d0, 0x955f, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x9560, 0x95ff, 0),
	GEN_FW_RANGE(0x9600, 0xafff, FORCEWAKE_GT),
	GEN_FW_RANGE(0xb000, 0xb47f, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xb480, 0xdeff, FORCEWAKE_GT),
	GEN_FW_RANGE(0xdf00, 0xe8ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xe900, 0x16dff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x16e00, 0x19fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x1a000, 0x23fff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x24000, 0x2407f, 0),
	GEN_FW_RANGE(0x24080, 0x2417f, FORCEWAKE_GT),
	GEN_FW_RANGE(0x24180, 0x242ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x24300, 0x243ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x24400, 0x24fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x25000, 0x3ffff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x40000, 0x1bffff, 0),
	GEN_FW_RANGE(0x1c0000, 0x1c3fff, FORCEWAKE_MEDIA_VDBOX0),
	GEN_FW_RANGE(0x1c4000, 0x1c7fff, 0),
	GEN_FW_RANGE(0x1c8000, 0x1cffff, FORCEWAKE_MEDIA_VEBOX0),
	GEN_FW_RANGE(0x1d0000, 0x1d3fff, FORCEWAKE_MEDIA_VDBOX2),
	GEN_FW_RANGE(0x1d4000, 0x1dbfff, 0)
पूर्ण;

/*
 * *Must* be sorted by offset ranges! See पूर्णांकel_fw_table_check().
 *
 * Note that the spec lists several reserved/unused ranges that करोn't
 * actually contain any रेजिस्टरs.  In the table below we'll combine those
 * reserved ranges with either the preceding or following range to keep the
 * table small and lookups fast.
 */
अटल स्थिर काष्ठा पूर्णांकel_क्रमcewake_range __gen12_fw_ranges[] = अणु
	GEN_FW_RANGE(0x0, 0x1fff, 0), /*
		0x0   -  0xaff: reserved
		0xb00 - 0x1fff: always on */
	GEN_FW_RANGE(0x2000, 0x26ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x2700, 0x27ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x2800, 0x2aff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x2b00, 0x2fff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x3000, 0x3fff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x4000, 0x51ff, FORCEWAKE_GT), /*
		0x4000 - 0x48ff: gt
		0x4900 - 0x51ff: reserved */
	GEN_FW_RANGE(0x5200, 0x7fff, FORCEWAKE_RENDER), /*
		0x5200 - 0x53ff: render
		0x5400 - 0x54ff: reserved
		0x5500 - 0x7fff: render */
	GEN_FW_RANGE(0x8000, 0x813f, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8140, 0x815f, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8160, 0x81ff, 0), /*
		0x8160 - 0x817f: reserved
		0x8180 - 0x81ff: always on */
	GEN_FW_RANGE(0x8200, 0x82ff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x8300, 0x84ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x8500, 0x94cf, FORCEWAKE_GT), /*
		0x8500 - 0x87ff: gt
		0x8800 - 0x8fff: reserved
		0x9000 - 0x947f: gt
		0x9480 - 0x94cf: reserved */
	GEN_FW_RANGE(0x94d0, 0x955f, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0x9560, 0x97ff, 0), /*
		0x9560 - 0x95ff: always on
		0x9600 - 0x97ff: reserved */
	GEN_FW_RANGE(0x9800, 0xafff, FORCEWAKE_GT),
	GEN_FW_RANGE(0xb000, 0xb3ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xb400, 0xcfff, FORCEWAKE_GT), /*
		0xb400 - 0xbf7f: gt
		0xb480 - 0xbfff: reserved
		0xc000 - 0xcfff: gt */
	GEN_FW_RANGE(0xd000, 0xd7ff, 0),
	GEN_FW_RANGE(0xd800, 0xd8ff, FORCEWAKE_RENDER),
	GEN_FW_RANGE(0xd900, 0xdbff, FORCEWAKE_GT),
	GEN_FW_RANGE(0xdc00, 0xefff, FORCEWAKE_RENDER), /*
		0xdc00 - 0xddff: render
		0xde00 - 0xde7f: reserved
		0xde80 - 0xe8ff: render
		0xe900 - 0xefff: reserved */
	GEN_FW_RANGE(0xf000, 0x147ff, FORCEWAKE_GT), /*
		 0xf000 - 0xffff: gt
		0x10000 - 0x147ff: reserved */
	GEN_FW_RANGE(0x14800, 0x1ffff, FORCEWAKE_RENDER), /*
		0x14800 - 0x14fff: render
		0x15000 - 0x16dff: reserved
		0x16e00 - 0x1bfff: render
		0x1c000 - 0x1ffff: reserved */
	GEN_FW_RANGE(0x20000, 0x20fff, FORCEWAKE_MEDIA_VDBOX0),
	GEN_FW_RANGE(0x21000, 0x21fff, FORCEWAKE_MEDIA_VDBOX2),
	GEN_FW_RANGE(0x22000, 0x23fff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x24000, 0x2417f, 0), /*
		0x24000 - 0x2407f: always on
		0x24080 - 0x2417f: reserved */
	GEN_FW_RANGE(0x24180, 0x249ff, FORCEWAKE_GT), /*
		0x24180 - 0x241ff: gt
		0x24200 - 0x249ff: reserved */
	GEN_FW_RANGE(0x24a00, 0x251ff, FORCEWAKE_RENDER), /*
		0x24a00 - 0x24a7f: render
		0x24a80 - 0x251ff: reserved */
	GEN_FW_RANGE(0x25200, 0x255ff, FORCEWAKE_GT), /*
		0x25200 - 0x252ff: gt
		0x25300 - 0x255ff: reserved */
	GEN_FW_RANGE(0x25600, 0x2567f, FORCEWAKE_MEDIA_VDBOX0),
	GEN_FW_RANGE(0x25680, 0x259ff, FORCEWAKE_MEDIA_VDBOX2), /*
		0x25680 - 0x256ff: VD2
		0x25700 - 0x259ff: reserved */
	GEN_FW_RANGE(0x25a00, 0x25a7f, FORCEWAKE_MEDIA_VDBOX0),
	GEN_FW_RANGE(0x25a80, 0x2ffff, FORCEWAKE_MEDIA_VDBOX2), /*
		0x25a80 - 0x25aff: VD2
		0x25b00 - 0x2ffff: reserved */
	GEN_FW_RANGE(0x30000, 0x3ffff, FORCEWAKE_GT),
	GEN_FW_RANGE(0x40000, 0x1bffff, 0),
	GEN_FW_RANGE(0x1c0000, 0x1c3fff, FORCEWAKE_MEDIA_VDBOX0), /*
		0x1c0000 - 0x1c2bff: VD0
		0x1c2c00 - 0x1c2cff: reserved
		0x1c2d00 - 0x1c2dff: VD0
		0x1c2e00 - 0x1c3eff: reserved
		0x1c3f00 - 0x1c3fff: VD0 */
	GEN_FW_RANGE(0x1c4000, 0x1c7fff, 0),
	GEN_FW_RANGE(0x1c8000, 0x1cbfff, FORCEWAKE_MEDIA_VEBOX0), /*
		0x1c8000 - 0x1ca0ff: VE0
		0x1ca100 - 0x1cbeff: reserved
		0x1cbf00 - 0x1cbfff: VE0 */
	GEN_FW_RANGE(0x1cc000, 0x1cffff, FORCEWAKE_MEDIA_VDBOX0), /*
		0x1cc000 - 0x1ccfff: VD0
		0x1cd000 - 0x1cffff: reserved */
	GEN_FW_RANGE(0x1d0000, 0x1d3fff, FORCEWAKE_MEDIA_VDBOX2), /*
		0x1d0000 - 0x1d2bff: VD2
		0x1d2c00 - 0x1d2cff: reserved
		0x1d2d00 - 0x1d2dff: VD2
		0x1d2e00 - 0x1d3eff: reserved
		0x1d3f00 - 0x1d3fff: VD2 */
पूर्ण;

अटल व्योम
ilk_dummy_ग_लिखो(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	/* WaIssueDummyWriteToWakeupFromRC6:ilk Issue a dummy ग_लिखो to wake up
	 * the chip from rc6 beक्रमe touching it क्रम real. MI_MODE is masked,
	 * hence harmless to ग_लिखो 0 पूर्णांकo. */
	__raw_uncore_ग_लिखो32(uncore, MI_MODE, 0);
पूर्ण

अटल व्योम
__unclaimed_reg_debug(काष्ठा पूर्णांकel_uncore *uncore,
		      स्थिर i915_reg_t reg,
		      स्थिर bool पढ़ो,
		      स्थिर bool beक्रमe)
अणु
	अगर (drm_WARN(&uncore->i915->drm,
		     check_क्रम_unclaimed_mmio(uncore) && !beक्रमe,
		     "Unclaimed %s register 0x%x\n",
		     पढ़ो ? "read from" : "write to",
		     i915_mmio_reg_offset(reg)))
		/* Only report the first N failures */
		uncore->i915->params.mmio_debug--;
पूर्ण

अटल अंतरभूत व्योम
unclaimed_reg_debug(काष्ठा पूर्णांकel_uncore *uncore,
		    स्थिर i915_reg_t reg,
		    स्थिर bool पढ़ो,
		    स्थिर bool beक्रमe)
अणु
	अगर (likely(!uncore->i915->params.mmio_debug))
		वापस;

	/* पूर्णांकerrupts are disabled and re-enabled around uncore->lock usage */
	lockdep_निश्चित_held(&uncore->lock);

	अगर (beक्रमe)
		spin_lock(&uncore->debug->lock);

	__unclaimed_reg_debug(uncore, reg, पढ़ो, beक्रमe);

	अगर (!beक्रमe)
		spin_unlock(&uncore->debug->lock);
पूर्ण

#घोषणा __vgpu_पढ़ो(x) \
अटल u##x \
vgpu_पढ़ो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, bool trace) अणु \
	u##x val = __raw_uncore_पढ़ो##x(uncore, reg); \
	trace_i915_reg_rw(false, reg, val, माप(val), trace); \
	वापस val; \
पूर्ण
__vgpu_पढ़ो(8)
__vgpu_पढ़ो(16)
__vgpu_पढ़ो(32)
__vgpu_पढ़ो(64)

#घोषणा GEN2_READ_HEADER(x) \
	u##x val = 0; \
	निश्चित_rpm_wakelock_held(uncore->rpm);

#घोषणा GEN2_READ_FOOTER \
	trace_i915_reg_rw(false, reg, val, माप(val), trace); \
	वापस val

#घोषणा __gen2_पढ़ो(x) \
अटल u##x \
gen2_पढ़ो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, bool trace) अणु \
	GEN2_READ_HEADER(x); \
	val = __raw_uncore_पढ़ो##x(uncore, reg); \
	GEN2_READ_FOOTER; \
पूर्ण

#घोषणा __gen5_पढ़ो(x) \
अटल u##x \
gen5_पढ़ो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, bool trace) अणु \
	GEN2_READ_HEADER(x); \
	ilk_dummy_ग_लिखो(uncore); \
	val = __raw_uncore_पढ़ो##x(uncore, reg); \
	GEN2_READ_FOOTER; \
पूर्ण

__gen5_पढ़ो(8)
__gen5_पढ़ो(16)
__gen5_पढ़ो(32)
__gen5_पढ़ो(64)
__gen2_पढ़ो(8)
__gen2_पढ़ो(16)
__gen2_पढ़ो(32)
__gen2_पढ़ो(64)

#अघोषित __gen5_पढ़ो
#अघोषित __gen2_पढ़ो

#अघोषित GEN2_READ_FOOTER
#अघोषित GEN2_READ_HEADER

#घोषणा GEN6_READ_HEADER(x) \
	u32 offset = i915_mmio_reg_offset(reg); \
	अचिन्हित दीर्घ irqflags; \
	u##x val = 0; \
	निश्चित_rpm_wakelock_held(uncore->rpm); \
	spin_lock_irqsave(&uncore->lock, irqflags); \
	unclaimed_reg_debug(uncore, reg, true, true)

#घोषणा GEN6_READ_FOOTER \
	unclaimed_reg_debug(uncore, reg, true, false); \
	spin_unlock_irqrestore(&uncore->lock, irqflags); \
	trace_i915_reg_rw(false, reg, val, माप(val), trace); \
	वापस val

अटल noअंतरभूत व्योम ___क्रमce_wake_स्वतः(काष्ठा पूर्णांकel_uncore *uncore,
					क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक पंचांगp;

	GEM_BUG_ON(fw_करोमुख्यs & ~uncore->fw_करोमुख्यs);

	क्रम_each_fw_करोमुख्य_masked(करोमुख्य, fw_करोमुख्यs, uncore, पंचांगp)
		fw_करोमुख्य_arm_समयr(करोमुख्य);

	uncore->funcs.क्रमce_wake_get(uncore, fw_करोमुख्यs);
पूर्ण

अटल अंतरभूत व्योम __क्रमce_wake_स्वतः(काष्ठा पूर्णांकel_uncore *uncore,
				     क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs)
अणु
	GEM_BUG_ON(!fw_करोमुख्यs);

	/* Turn on all requested but inactive supported क्रमcewake करोमुख्यs. */
	fw_करोमुख्यs &= uncore->fw_करोमुख्यs;
	fw_करोमुख्यs &= ~uncore->fw_करोमुख्यs_active;

	अगर (fw_करोमुख्यs)
		___क्रमce_wake_स्वतः(uncore, fw_करोमुख्यs);
पूर्ण

#घोषणा __gen_पढ़ो(func, x) \
अटल u##x \
func##_पढ़ो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, bool trace) अणु \
	क्रमागत क्रमcewake_करोमुख्यs fw_engine; \
	GEN6_READ_HEADER(x); \
	fw_engine = __##func##_reg_पढ़ो_fw_करोमुख्यs(uncore, offset); \
	अगर (fw_engine) \
		__क्रमce_wake_स्वतः(uncore, fw_engine); \
	val = __raw_uncore_पढ़ो##x(uncore, reg); \
	GEN6_READ_FOOTER; \
पूर्ण

#घोषणा __gen_reg_पढ़ो_funcs(func) \
अटल क्रमागत क्रमcewake_करोमुख्यs \
func##_reg_पढ़ो_fw_करोमुख्यs(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg) अणु \
	वापस __##func##_reg_पढ़ो_fw_करोमुख्यs(uncore, i915_mmio_reg_offset(reg)); \
पूर्ण \
\
__gen_पढ़ो(func, 8) \
__gen_पढ़ो(func, 16) \
__gen_पढ़ो(func, 32) \
__gen_पढ़ो(func, 64)

__gen_reg_पढ़ो_funcs(gen12_fwtable);
__gen_reg_पढ़ो_funcs(gen11_fwtable);
__gen_reg_पढ़ो_funcs(fwtable);
__gen_reg_पढ़ो_funcs(gen6);

#अघोषित __gen_reg_पढ़ो_funcs
#अघोषित GEN6_READ_FOOTER
#अघोषित GEN6_READ_HEADER

#घोषणा GEN2_WRITE_HEADER \
	trace_i915_reg_rw(true, reg, val, माप(val), trace); \
	निश्चित_rpm_wakelock_held(uncore->rpm); \

#घोषणा GEN2_WRITE_FOOTER

#घोषणा __gen2_ग_लिखो(x) \
अटल व्योम \
gen2_ग_लिखो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u##x val, bool trace) अणु \
	GEN2_WRITE_HEADER; \
	__raw_uncore_ग_लिखो##x(uncore, reg, val); \
	GEN2_WRITE_FOOTER; \
पूर्ण

#घोषणा __gen5_ग_लिखो(x) \
अटल व्योम \
gen5_ग_लिखो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u##x val, bool trace) अणु \
	GEN2_WRITE_HEADER; \
	ilk_dummy_ग_लिखो(uncore); \
	__raw_uncore_ग_लिखो##x(uncore, reg, val); \
	GEN2_WRITE_FOOTER; \
पूर्ण

__gen5_ग_लिखो(8)
__gen5_ग_लिखो(16)
__gen5_ग_लिखो(32)
__gen2_ग_लिखो(8)
__gen2_ग_लिखो(16)
__gen2_ग_लिखो(32)

#अघोषित __gen5_ग_लिखो
#अघोषित __gen2_ग_लिखो

#अघोषित GEN2_WRITE_FOOTER
#अघोषित GEN2_WRITE_HEADER

#घोषणा GEN6_WRITE_HEADER \
	u32 offset = i915_mmio_reg_offset(reg); \
	अचिन्हित दीर्घ irqflags; \
	trace_i915_reg_rw(true, reg, val, माप(val), trace); \
	निश्चित_rpm_wakelock_held(uncore->rpm); \
	spin_lock_irqsave(&uncore->lock, irqflags); \
	unclaimed_reg_debug(uncore, reg, false, true)

#घोषणा GEN6_WRITE_FOOTER \
	unclaimed_reg_debug(uncore, reg, false, false); \
	spin_unlock_irqrestore(&uncore->lock, irqflags)

#घोषणा __gen6_ग_लिखो(x) \
अटल व्योम \
gen6_ग_लिखो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u##x val, bool trace) अणु \
	GEN6_WRITE_HEADER; \
	अगर (NEEDS_FORCE_WAKE(offset)) \
		__gen6_gt_रुको_क्रम_fअगरo(uncore); \
	__raw_uncore_ग_लिखो##x(uncore, reg, val); \
	GEN6_WRITE_FOOTER; \
पूर्ण
__gen6_ग_लिखो(8)
__gen6_ग_लिखो(16)
__gen6_ग_लिखो(32)

#घोषणा __gen_ग_लिखो(func, x) \
अटल व्योम \
func##_ग_लिखो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u##x val, bool trace) अणु \
	क्रमागत क्रमcewake_करोमुख्यs fw_engine; \
	GEN6_WRITE_HEADER; \
	fw_engine = __##func##_reg_ग_लिखो_fw_करोमुख्यs(uncore, offset); \
	अगर (fw_engine) \
		__क्रमce_wake_स्वतः(uncore, fw_engine); \
	__raw_uncore_ग_लिखो##x(uncore, reg, val); \
	GEN6_WRITE_FOOTER; \
पूर्ण

#घोषणा __gen_reg_ग_लिखो_funcs(func) \
अटल क्रमागत क्रमcewake_करोमुख्यs \
func##_reg_ग_लिखो_fw_करोमुख्यs(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg) अणु \
	वापस __##func##_reg_ग_लिखो_fw_करोमुख्यs(uncore, i915_mmio_reg_offset(reg)); \
पूर्ण \
\
__gen_ग_लिखो(func, 8) \
__gen_ग_लिखो(func, 16) \
__gen_ग_लिखो(func, 32)

__gen_reg_ग_लिखो_funcs(gen12_fwtable);
__gen_reg_ग_लिखो_funcs(gen11_fwtable);
__gen_reg_ग_लिखो_funcs(fwtable);
__gen_reg_ग_लिखो_funcs(gen8);

#अघोषित __gen_reg_ग_लिखो_funcs
#अघोषित GEN6_WRITE_FOOTER
#अघोषित GEN6_WRITE_HEADER

#घोषणा __vgpu_ग_लिखो(x) \
अटल व्योम \
vgpu_ग_लिखो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u##x val, bool trace) अणु \
	trace_i915_reg_rw(true, reg, val, माप(val), trace); \
	__raw_uncore_ग_लिखो##x(uncore, reg, val); \
पूर्ण
__vgpu_ग_लिखो(8)
__vgpu_ग_लिखो(16)
__vgpu_ग_लिखो(32)

#घोषणा ASSIGN_RAW_WRITE_MMIO_VFUNCS(uncore, x) \
करो अणु \
	(uncore)->funcs.mmio_ग_लिखोb = x##_ग_लिखो8; \
	(uncore)->funcs.mmio_ग_लिखोw = x##_ग_लिखो16; \
	(uncore)->funcs.mmio_ग_लिखोl = x##_ग_लिखो32; \
पूर्ण जबतक (0)

#घोषणा ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, x) \
करो अणु \
	(uncore)->funcs.mmio_पढ़ोb = x##_पढ़ो8; \
	(uncore)->funcs.mmio_पढ़ोw = x##_पढ़ो16; \
	(uncore)->funcs.mmio_पढ़ोl = x##_पढ़ो32; \
	(uncore)->funcs.mmio_पढ़ोq = x##_पढ़ो64; \
पूर्ण जबतक (0)

#घोषणा ASSIGN_WRITE_MMIO_VFUNCS(uncore, x) \
करो अणु \
	ASSIGN_RAW_WRITE_MMIO_VFUNCS((uncore), x); \
	(uncore)->funcs.ग_लिखो_fw_करोमुख्यs = x##_reg_ग_लिखो_fw_करोमुख्यs; \
पूर्ण जबतक (0)

#घोषणा ASSIGN_READ_MMIO_VFUNCS(uncore, x) \
करो अणु \
	ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, x); \
	(uncore)->funcs.पढ़ो_fw_करोमुख्यs = x##_reg_पढ़ो_fw_करोमुख्यs; \
पूर्ण जबतक (0)

अटल पूर्णांक __fw_करोमुख्य_init(काष्ठा पूर्णांकel_uncore *uncore,
			    क्रमागत क्रमcewake_करोमुख्य_id करोमुख्य_id,
			    i915_reg_t reg_set,
			    i915_reg_t reg_ack)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d;

	GEM_BUG_ON(करोमुख्य_id >= FW_DOMAIN_ID_COUNT);
	GEM_BUG_ON(uncore->fw_करोमुख्य[करोमुख्य_id]);

	अगर (i915_inject_probe_failure(uncore->i915))
		वापस -ENOMEM;

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	drm_WARN_ON(&uncore->i915->drm, !i915_mmio_reg_valid(reg_set));
	drm_WARN_ON(&uncore->i915->drm, !i915_mmio_reg_valid(reg_ack));

	d->uncore = uncore;
	d->wake_count = 0;
	d->reg_set = uncore->regs + i915_mmio_reg_offset(reg_set);
	d->reg_ack = uncore->regs + i915_mmio_reg_offset(reg_ack);

	d->id = करोमुख्य_id;

	BUILD_BUG_ON(FORCEWAKE_RENDER != (1 << FW_DOMAIN_ID_RENDER));
	BUILD_BUG_ON(FORCEWAKE_GT != (1 << FW_DOMAIN_ID_GT));
	BUILD_BUG_ON(FORCEWAKE_MEDIA != (1 << FW_DOMAIN_ID_MEDIA));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VDBOX0 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX0));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VDBOX1 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX1));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VDBOX2 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX2));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VDBOX3 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX3));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VEBOX0 != (1 << FW_DOMAIN_ID_MEDIA_VEBOX0));
	BUILD_BUG_ON(FORCEWAKE_MEDIA_VEBOX1 != (1 << FW_DOMAIN_ID_MEDIA_VEBOX1));

	d->mask = BIT(करोमुख्य_id);

	hrसमयr_init(&d->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	d->समयr.function = पूर्णांकel_uncore_fw_release_समयr;

	uncore->fw_करोमुख्यs |= BIT(करोमुख्य_id);

	fw_करोमुख्य_reset(d);

	uncore->fw_करोमुख्य[करोमुख्य_id] = d;

	वापस 0;
पूर्ण

अटल व्योम fw_करोमुख्य_fini(काष्ठा पूर्णांकel_uncore *uncore,
			   क्रमागत क्रमcewake_करोमुख्य_id करोमुख्य_id)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d;

	GEM_BUG_ON(करोमुख्य_id >= FW_DOMAIN_ID_COUNT);

	d = fetch_and_zero(&uncore->fw_करोमुख्य[करोमुख्य_id]);
	अगर (!d)
		वापस;

	uncore->fw_करोमुख्यs &= ~BIT(करोमुख्य_id);
	drm_WARN_ON(&uncore->i915->drm, d->wake_count);
	drm_WARN_ON(&uncore->i915->drm, hrसमयr_cancel(&d->समयr));
	kमुक्त(d);
पूर्ण

अटल व्योम पूर्णांकel_uncore_fw_करोमुख्यs_fini(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *d;
	पूर्णांक पंचांगp;

	क्रम_each_fw_करोमुख्य(d, uncore, पंचांगp)
		fw_करोमुख्य_fini(uncore, d->id);
पूर्ण

अटल पूर्णांक पूर्णांकel_uncore_fw_करोमुख्यs_init(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	काष्ठा drm_i915_निजी *i915 = uncore->i915;
	पूर्णांक ret = 0;

	GEM_BUG_ON(!पूर्णांकel_uncore_has_क्रमcewake(uncore));

#घोषणा fw_करोमुख्य_init(uncore__, id__, set__, ack__) \
	(ret ?: (ret = __fw_करोमुख्य_init((uncore__), (id__), (set__), (ack__))))

	अगर (INTEL_GEN(i915) >= 11) अणु
		/* we'll prune the करोमुख्यs of missing engines later */
		पूर्णांकel_engine_mask_t emask = INTEL_INFO(i915)->platक्रमm_engine_mask;
		पूर्णांक i;

		uncore->funcs.क्रमce_wake_get = fw_करोमुख्यs_get_with_fallback;
		uncore->funcs.क्रमce_wake_put = fw_करोमुख्यs_put;
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_RENDER,
			       FORCEWAKE_RENDER_GEN9,
			       FORCEWAKE_ACK_RENDER_GEN9);
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_GT,
			       FORCEWAKE_GT_GEN9,
			       FORCEWAKE_ACK_GT_GEN9);

		क्रम (i = 0; i < I915_MAX_VCS; i++) अणु
			अगर (!__HAS_ENGINE(emask, _VCS(i)))
				जारी;

			fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_MEDIA_VDBOX0 + i,
				       FORCEWAKE_MEDIA_VDBOX_GEN11(i),
				       FORCEWAKE_ACK_MEDIA_VDBOX_GEN11(i));
		पूर्ण
		क्रम (i = 0; i < I915_MAX_VECS; i++) अणु
			अगर (!__HAS_ENGINE(emask, _VECS(i)))
				जारी;

			fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_MEDIA_VEBOX0 + i,
				       FORCEWAKE_MEDIA_VEBOX_GEN11(i),
				       FORCEWAKE_ACK_MEDIA_VEBOX_GEN11(i));
		पूर्ण
	पूर्ण अन्यथा अगर (IS_GEN_RANGE(i915, 9, 10)) अणु
		uncore->funcs.क्रमce_wake_get = fw_करोमुख्यs_get_with_fallback;
		uncore->funcs.क्रमce_wake_put = fw_करोमुख्यs_put;
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_RENDER,
			       FORCEWAKE_RENDER_GEN9,
			       FORCEWAKE_ACK_RENDER_GEN9);
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_GT,
			       FORCEWAKE_GT_GEN9,
			       FORCEWAKE_ACK_GT_GEN9);
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_MEDIA,
			       FORCEWAKE_MEDIA_GEN9, FORCEWAKE_ACK_MEDIA_GEN9);
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915)) अणु
		uncore->funcs.क्रमce_wake_get = fw_करोमुख्यs_get;
		uncore->funcs.क्रमce_wake_put = fw_करोमुख्यs_put;
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_RENDER,
			       FORCEWAKE_VLV, FORCEWAKE_ACK_VLV);
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_MEDIA,
			       FORCEWAKE_MEDIA_VLV, FORCEWAKE_ACK_MEDIA_VLV);
	पूर्ण अन्यथा अगर (IS_HASWELL(i915) || IS_BROADWELL(i915)) अणु
		uncore->funcs.क्रमce_wake_get =
			fw_करोमुख्यs_get_with_thपढ़ो_status;
		uncore->funcs.क्रमce_wake_put = fw_करोमुख्यs_put;
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_RENDER,
			       FORCEWAKE_MT, FORCEWAKE_ACK_HSW);
	पूर्ण अन्यथा अगर (IS_IVYBRIDGE(i915)) अणु
		u32 ecobus;

		/* IVB configs may use multi-thपढ़ोed क्रमcewake */

		/* A small trick here - अगर the bios hasn't configured
		 * MT क्रमcewake, and अगर the device is in RC6, then
		 * क्रमce_wake_mt_get will not wake the device and the
		 * ECOBUS पढ़ो will वापस zero. Which will be
		 * (correctly) पूर्णांकerpreted by the test below as MT
		 * क्रमcewake being disabled.
		 */
		uncore->funcs.क्रमce_wake_get =
			fw_करोमुख्यs_get_with_thपढ़ो_status;
		uncore->funcs.क्रमce_wake_put = fw_करोमुख्यs_put;

		/* We need to init first क्रम ECOBUS access and then
		 * determine later अगर we want to reinit, in हाल of MT access is
		 * not working. In this stage we करोn't know which flavour this
		 * ivb is, so it is better to reset also the gen6 fw रेजिस्टरs
		 * beक्रमe the ecobus check.
		 */

		__raw_uncore_ग_लिखो32(uncore, FORCEWAKE, 0);
		__raw_posting_पढ़ो(uncore, ECOBUS);

		ret = __fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_RENDER,
				       FORCEWAKE_MT, FORCEWAKE_MT_ACK);
		अगर (ret)
			जाओ out;

		spin_lock_irq(&uncore->lock);
		fw_करोमुख्यs_get_with_thपढ़ो_status(uncore, FORCEWAKE_RENDER);
		ecobus = __raw_uncore_पढ़ो32(uncore, ECOBUS);
		fw_करोमुख्यs_put(uncore, FORCEWAKE_RENDER);
		spin_unlock_irq(&uncore->lock);

		अगर (!(ecobus & FORCEWAKE_MT_ENABLE)) अणु
			drm_info(&i915->drm, "No MT forcewake available on Ivybridge, this can result in issues\n");
			drm_info(&i915->drm, "when using vblank-synced partial screen updates.\n");
			fw_करोमुख्य_fini(uncore, FW_DOMAIN_ID_RENDER);
			fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_RENDER,
				       FORCEWAKE, FORCEWAKE_ACK);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_GEN(i915, 6)) अणु
		uncore->funcs.क्रमce_wake_get =
			fw_करोमुख्यs_get_with_thपढ़ो_status;
		uncore->funcs.क्रमce_wake_put = fw_करोमुख्यs_put;
		fw_करोमुख्य_init(uncore, FW_DOMAIN_ID_RENDER,
			       FORCEWAKE, FORCEWAKE_ACK);
	पूर्ण

#अघोषित fw_करोमुख्य_init

	/* All future platक्रमms are expected to require complex घातer gating */
	drm_WARN_ON(&i915->drm, !ret && uncore->fw_करोमुख्यs == 0);

out:
	अगर (ret)
		पूर्णांकel_uncore_fw_करोमुख्यs_fini(uncore);

	वापस ret;
पूर्ण

#घोषणा ASSIGN_FW_DOMAINS_TABLE(uncore, d) \
अणु \
	(uncore)->fw_करोमुख्यs_table = \
			(काष्ठा पूर्णांकel_क्रमcewake_range *)(d); \
	(uncore)->fw_करोमुख्यs_table_entries = ARRAY_SIZE((d)); \
पूर्ण

अटल पूर्णांक i915_pmic_bus_access_notअगरier(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = container_of(nb,
			काष्ठा पूर्णांकel_uncore, pmic_bus_access_nb);

	चयन (action) अणु
	हाल MBI_PMIC_BUS_ACCESS_BEGIN:
		/*
		 * क्रमcewake all now to make sure that we करोn't need to करो a
		 * क्रमcewake later which on प्रणालीs where this notअगरier माला_लो
		 * called requires the punit to access to the shared pmic i2c
		 * bus, which will be busy after this notअगरication, leading to:
		 * "render: timed out waiting for forcewake ack request."
		 * errors.
		 *
		 * The notअगरier is unरेजिस्टरed during पूर्णांकel_runसमय_suspend(),
		 * so it's ok to access the HW here without holding a RPM
		 * wake reference -> disable wakeref निश्चितs क्रम the समय of
		 * the access.
		 */
		disable_rpm_wakeref_निश्चितs(uncore->rpm);
		पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);
		enable_rpm_wakeref_निश्चितs(uncore->rpm);
		अवरोध;
	हाल MBI_PMIC_BUS_ACCESS_END:
		पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक uncore_mmio_setup(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	काष्ठा drm_i915_निजी *i915 = uncore->i915;
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);
	पूर्णांक mmio_bar;
	पूर्णांक mmio_size;

	mmio_bar = IS_GEN(i915, 2) ? 1 : 0;
	/*
	 * Beक्रमe gen4, the रेजिस्टरs and the GTT are behind dअगरferent BARs.
	 * However, from gen4 onwards, the रेजिस्टरs and the GTT are shared
	 * in the same BAR, so we want to restrict this ioremap from
	 * clobbering the GTT which we want ioremap_wc instead. Fortunately,
	 * the रेजिस्टर BAR reमुख्यs the same size क्रम all the earlier
	 * generations up to Ironlake.
	 * For dgfx chips रेजिस्टर range is expanded to 4MB.
	 */
	अगर (INTEL_GEN(i915) < 5)
		mmio_size = 512 * 1024;
	अन्यथा अगर (IS_DGFX(i915))
		mmio_size = 4 * 1024 * 1024;
	अन्यथा
		mmio_size = 2 * 1024 * 1024;

	uncore->regs = pci_iomap(pdev, mmio_bar, mmio_size);
	अगर (uncore->regs == शून्य) अणु
		drm_err(&i915->drm, "failed to map registers\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uncore_mmio_cleanup(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(uncore->i915->drm.dev);

	pci_iounmap(pdev, uncore->regs);
पूर्ण

व्योम पूर्णांकel_uncore_init_early(काष्ठा पूर्णांकel_uncore *uncore,
			     काष्ठा drm_i915_निजी *i915)
अणु
	spin_lock_init(&uncore->lock);
	uncore->i915 = i915;
	uncore->rpm = &i915->runसमय_pm;
	uncore->debug = &i915->mmio_debug;
पूर्ण

अटल व्योम uncore_raw_init(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	GEM_BUG_ON(पूर्णांकel_uncore_has_क्रमcewake(uncore));

	अगर (पूर्णांकel_vgpu_active(uncore->i915)) अणु
		ASSIGN_RAW_WRITE_MMIO_VFUNCS(uncore, vgpu);
		ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, vgpu);
	पूर्ण अन्यथा अगर (IS_GEN(uncore->i915, 5)) अणु
		ASSIGN_RAW_WRITE_MMIO_VFUNCS(uncore, gen5);
		ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, gen5);
	पूर्ण अन्यथा अणु
		ASSIGN_RAW_WRITE_MMIO_VFUNCS(uncore, gen2);
		ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, gen2);
	पूर्ण
पूर्ण

अटल पूर्णांक uncore_क्रमcewake_init(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	काष्ठा drm_i915_निजी *i915 = uncore->i915;
	पूर्णांक ret;

	GEM_BUG_ON(!पूर्णांकel_uncore_has_क्रमcewake(uncore));

	ret = पूर्णांकel_uncore_fw_करोमुख्यs_init(uncore);
	अगर (ret)
		वापस ret;
	क्रमcewake_early_sanitize(uncore, 0);

	अगर (IS_GEN_RANGE(i915, 6, 7)) अणु
		ASSIGN_WRITE_MMIO_VFUNCS(uncore, gen6);

		अगर (IS_VALLEYVIEW(i915)) अणु
			ASSIGN_FW_DOMAINS_TABLE(uncore, __vlv_fw_ranges);
			ASSIGN_READ_MMIO_VFUNCS(uncore, fwtable);
		पूर्ण अन्यथा अणु
			ASSIGN_READ_MMIO_VFUNCS(uncore, gen6);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_GEN(i915, 8)) अणु
		अगर (IS_CHERRYVIEW(i915)) अणु
			ASSIGN_FW_DOMAINS_TABLE(uncore, __chv_fw_ranges);
			ASSIGN_WRITE_MMIO_VFUNCS(uncore, fwtable);
			ASSIGN_READ_MMIO_VFUNCS(uncore, fwtable);
		पूर्ण अन्यथा अणु
			ASSIGN_WRITE_MMIO_VFUNCS(uncore, gen8);
			ASSIGN_READ_MMIO_VFUNCS(uncore, gen6);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_GEN_RANGE(i915, 9, 10)) अणु
		ASSIGN_FW_DOMAINS_TABLE(uncore, __gen9_fw_ranges);
		ASSIGN_WRITE_MMIO_VFUNCS(uncore, fwtable);
		ASSIGN_READ_MMIO_VFUNCS(uncore, fwtable);
	पूर्ण अन्यथा अगर (IS_GEN(i915, 11)) अणु
		ASSIGN_FW_DOMAINS_TABLE(uncore, __gen11_fw_ranges);
		ASSIGN_WRITE_MMIO_VFUNCS(uncore, gen11_fwtable);
		ASSIGN_READ_MMIO_VFUNCS(uncore, gen11_fwtable);
	पूर्ण अन्यथा अणु
		ASSIGN_FW_DOMAINS_TABLE(uncore, __gen12_fw_ranges);
		ASSIGN_WRITE_MMIO_VFUNCS(uncore, gen12_fwtable);
		ASSIGN_READ_MMIO_VFUNCS(uncore, gen12_fwtable);
	पूर्ण

	uncore->pmic_bus_access_nb.notअगरier_call = i915_pmic_bus_access_notअगरier;
	iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier(&uncore->pmic_bus_access_nb);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_uncore_init_mmio(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	काष्ठा drm_i915_निजी *i915 = uncore->i915;
	पूर्णांक ret;

	ret = uncore_mmio_setup(uncore);
	अगर (ret)
		वापस ret;

	अगर (INTEL_GEN(i915) > 5 && !पूर्णांकel_vgpu_active(i915))
		uncore->flags |= UNCORE_HAS_FORCEWAKE;

	अगर (!पूर्णांकel_uncore_has_क्रमcewake(uncore)) अणु
		uncore_raw_init(uncore);
	पूर्ण अन्यथा अणु
		ret = uncore_क्रमcewake_init(uncore);
		अगर (ret)
			जाओ out_mmio_cleanup;
	पूर्ण

	/* make sure fw funcs are set अगर and only अगर we have fw*/
	GEM_BUG_ON(पूर्णांकel_uncore_has_क्रमcewake(uncore) != !!uncore->funcs.क्रमce_wake_get);
	GEM_BUG_ON(पूर्णांकel_uncore_has_क्रमcewake(uncore) != !!uncore->funcs.क्रमce_wake_put);
	GEM_BUG_ON(पूर्णांकel_uncore_has_क्रमcewake(uncore) != !!uncore->funcs.पढ़ो_fw_करोमुख्यs);
	GEM_BUG_ON(पूर्णांकel_uncore_has_क्रमcewake(uncore) != !!uncore->funcs.ग_लिखो_fw_करोमुख्यs);

	अगर (HAS_FPGA_DBG_UNCLAIMED(i915))
		uncore->flags |= UNCORE_HAS_FPGA_DBG_UNCLAIMED;

	अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
		uncore->flags |= UNCORE_HAS_DBG_UNCLAIMED;

	अगर (IS_GEN_RANGE(i915, 6, 7))
		uncore->flags |= UNCORE_HAS_FIFO;

	/* clear out unclaimed reg detection bit */
	अगर (पूर्णांकel_uncore_unclaimed_mmio(uncore))
		drm_dbg(&i915->drm, "unclaimed mmio detected on uncore init, clearing\n");

	वापस 0;

out_mmio_cleanup:
	uncore_mmio_cleanup(uncore);

	वापस ret;
पूर्ण

/*
 * We might have detected that some engines are fused off after we initialized
 * the क्रमcewake करोमुख्यs. Prune them, to make sure they only reference existing
 * engines.
 */
व्योम पूर्णांकel_uncore_prune_engine_fw_करोमुख्यs(काष्ठा पूर्णांकel_uncore *uncore,
					  काष्ठा पूर्णांकel_gt *gt)
अणु
	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs = uncore->fw_करोमुख्यs;
	क्रमागत क्रमcewake_करोमुख्य_id करोमुख्य_id;
	पूर्णांक i;

	अगर (!पूर्णांकel_uncore_has_क्रमcewake(uncore) || INTEL_GEN(uncore->i915) < 11)
		वापस;

	क्रम (i = 0; i < I915_MAX_VCS; i++) अणु
		करोमुख्य_id = FW_DOMAIN_ID_MEDIA_VDBOX0 + i;

		अगर (HAS_ENGINE(gt, _VCS(i)))
			जारी;

		अगर (fw_करोमुख्यs & BIT(करोमुख्य_id))
			fw_करोमुख्य_fini(uncore, करोमुख्य_id);
	पूर्ण

	क्रम (i = 0; i < I915_MAX_VECS; i++) अणु
		करोमुख्य_id = FW_DOMAIN_ID_MEDIA_VEBOX0 + i;

		अगर (HAS_ENGINE(gt, _VECS(i)))
			जारी;

		अगर (fw_करोमुख्यs & BIT(करोमुख्य_id))
			fw_करोमुख्य_fini(uncore, करोमुख्य_id);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_uncore_fini_mmio(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	अगर (पूर्णांकel_uncore_has_क्रमcewake(uncore)) अणु
		iosf_mbi_punit_acquire();
		iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier_unlocked(
			&uncore->pmic_bus_access_nb);
		पूर्णांकel_uncore_क्रमcewake_reset(uncore);
		पूर्णांकel_uncore_fw_करोमुख्यs_fini(uncore);
		iosf_mbi_punit_release();
	पूर्ण

	uncore_mmio_cleanup(uncore);
पूर्ण

अटल स्थिर काष्ठा reg_whitelist अणु
	i915_reg_t offset_ldw;
	i915_reg_t offset_udw;
	u16 gen_mask;
	u8 size;
पूर्ण reg_पढ़ो_whitelist[] = अणु अणु
	.offset_ldw = RING_TIMESTAMP(RENDER_RING_BASE),
	.offset_udw = RING_TIMESTAMP_UDW(RENDER_RING_BASE),
	.gen_mask = INTEL_GEN_MASK(4, 12),
	.size = 8
पूर्ण पूर्ण;

पूर्णांक i915_reg_पढ़ो_ioctl(काष्ठा drm_device *dev,
			व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	काष्ठा drm_i915_reg_पढ़ो *reg = data;
	काष्ठा reg_whitelist स्थिर *entry;
	पूर्णांकel_wakeref_t wakeref;
	अचिन्हित पूर्णांक flags;
	पूर्णांक reमुख्य;
	पूर्णांक ret = 0;

	entry = reg_पढ़ो_whitelist;
	reमुख्य = ARRAY_SIZE(reg_पढ़ो_whitelist);
	जबतक (reमुख्य) अणु
		u32 entry_offset = i915_mmio_reg_offset(entry->offset_ldw);

		GEM_BUG_ON(!is_घातer_of_2(entry->size));
		GEM_BUG_ON(entry->size > 8);
		GEM_BUG_ON(entry_offset & (entry->size - 1));

		अगर (INTEL_INFO(i915)->gen_mask & entry->gen_mask &&
		    entry_offset == (reg->offset & -entry->size))
			अवरोध;
		entry++;
		reमुख्य--;
	पूर्ण

	अगर (!reमुख्य)
		वापस -EINVAL;

	flags = reg->offset & (entry->size - 1);

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref) अणु
		अगर (entry->size == 8 && flags == I915_REG_READ_8B_WA)
			reg->val = पूर्णांकel_uncore_पढ़ो64_2x32(uncore,
							    entry->offset_ldw,
							    entry->offset_udw);
		अन्यथा अगर (entry->size == 8 && flags == 0)
			reg->val = पूर्णांकel_uncore_पढ़ो64(uncore,
						       entry->offset_ldw);
		अन्यथा अगर (entry->size == 4 && flags == 0)
			reg->val = पूर्णांकel_uncore_पढ़ो(uncore, entry->offset_ldw);
		अन्यथा अगर (entry->size == 2 && flags == 0)
			reg->val = पूर्णांकel_uncore_पढ़ो16(uncore,
						       entry->offset_ldw);
		अन्यथा अगर (entry->size == 1 && flags == 0)
			reg->val = पूर्णांकel_uncore_पढ़ो8(uncore,
						      entry->offset_ldw);
		अन्यथा
			ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw - रुको until रेजिस्टर matches expected state
 * @uncore: the काष्ठा पूर्णांकel_uncore
 * @reg: the रेजिस्टर to पढ़ो
 * @mask: mask to apply to रेजिस्टर value
 * @value: expected value
 * @fast_समयout_us: fast समयout in microsecond क्रम atomic/tight रुको
 * @slow_समयout_ms: slow समयout in millisecond
 * @out_value: optional placeholder to hold registry value
 *
 * This routine रुकोs until the target रेजिस्टर @reg contains the expected
 * @value after applying the @mask, i.e. it रुकोs until ::
 *
 *     (पूर्णांकel_uncore_पढ़ो_fw(uncore, reg) & mask) == value
 *
 * Otherwise, the रुको will समयout after @slow_समयout_ms milliseconds.
 * For atomic context @slow_समयout_ms must be zero and @fast_समयout_us
 * must be not larger than 20,0000 microseconds.
 *
 * Note that this routine assumes the caller holds क्रमcewake निश्चितed, it is
 * not suitable क्रम very दीर्घ रुकोs. See पूर्णांकel_रुको_क्रम_रेजिस्टर() अगर you
 * wish to रुको without holding क्रमcewake क्रम the duration (i.e. you expect
 * the रुको to be slow).
 *
 * Return: 0 अगर the रेजिस्टर matches the desired condition, or -ETIMEDOUT.
 */
पूर्णांक __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(काष्ठा पूर्णांकel_uncore *uncore,
				 i915_reg_t reg,
				 u32 mask,
				 u32 value,
				 अचिन्हित पूर्णांक fast_समयout_us,
				 अचिन्हित पूर्णांक slow_समयout_ms,
				 u32 *out_value)
अणु
	u32 reg_value = 0;
#घोषणा करोne (((reg_value = पूर्णांकel_uncore_पढ़ो_fw(uncore, reg)) & mask) == value)
	पूर्णांक ret;

	/* Catch any overuse of this function */
	might_sleep_अगर(slow_समयout_ms);
	GEM_BUG_ON(fast_समयout_us > 20000);
	GEM_BUG_ON(!fast_समयout_us && !slow_समयout_ms);

	ret = -ETIMEDOUT;
	अगर (fast_समयout_us && fast_समयout_us <= 20000)
		ret = _रुको_क्रम_atomic(करोne, fast_समयout_us, 0);
	अगर (ret && slow_समयout_ms)
		ret = रुको_क्रम(करोne, slow_समयout_ms);

	अगर (out_value)
		*out_value = reg_value;

	वापस ret;
#अघोषित करोne
पूर्ण

/**
 * __पूर्णांकel_रुको_क्रम_रेजिस्टर - रुको until रेजिस्टर matches expected state
 * @uncore: the काष्ठा पूर्णांकel_uncore
 * @reg: the रेजिस्टर to पढ़ो
 * @mask: mask to apply to रेजिस्टर value
 * @value: expected value
 * @fast_समयout_us: fast समयout in microsecond क्रम atomic/tight रुको
 * @slow_समयout_ms: slow समयout in millisecond
 * @out_value: optional placeholder to hold registry value
 *
 * This routine रुकोs until the target रेजिस्टर @reg contains the expected
 * @value after applying the @mask, i.e. it रुकोs until ::
 *
 *     (पूर्णांकel_uncore_पढ़ो(uncore, reg) & mask) == value
 *
 * Otherwise, the रुको will समयout after @समयout_ms milliseconds.
 *
 * Return: 0 अगर the रेजिस्टर matches the desired condition, or -ETIMEDOUT.
 */
पूर्णांक __पूर्णांकel_रुको_क्रम_रेजिस्टर(काष्ठा पूर्णांकel_uncore *uncore,
			      i915_reg_t reg,
			      u32 mask,
			      u32 value,
			      अचिन्हित पूर्णांक fast_समयout_us,
			      अचिन्हित पूर्णांक slow_समयout_ms,
			      u32 *out_value)
अणु
	अचिन्हित fw =
		पूर्णांकel_uncore_क्रमcewake_क्रम_reg(uncore, reg, FW_REG_READ);
	u32 reg_value;
	पूर्णांक ret;

	might_sleep_अगर(slow_समयout_ms);

	spin_lock_irq(&uncore->lock);
	पूर्णांकel_uncore_क्रमcewake_get__locked(uncore, fw);

	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
					   reg, mask, value,
					   fast_समयout_us, 0, &reg_value);

	पूर्णांकel_uncore_क्रमcewake_put__locked(uncore, fw);
	spin_unlock_irq(&uncore->lock);

	अगर (ret && slow_समयout_ms)
		ret = __रुको_क्रम(reg_value = पूर्णांकel_uncore_पढ़ो_notrace(uncore,
								       reg),
				 (reg_value & mask) == value,
				 slow_समयout_ms * 1000, 10, 1000);

	/* just trace the final value */
	trace_i915_reg_rw(false, reg, reg_value, माप(reg_value), true);

	अगर (out_value)
		*out_value = reg_value;

	वापस ret;
पूर्ण

bool पूर्णांकel_uncore_unclaimed_mmio(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	bool ret;

	spin_lock_irq(&uncore->debug->lock);
	ret = check_क्रम_unclaimed_mmio(uncore);
	spin_unlock_irq(&uncore->debug->lock);

	वापस ret;
पूर्ण

bool
पूर्णांकel_uncore_arm_unclaimed_mmio_detection(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	bool ret = false;

	spin_lock_irq(&uncore->debug->lock);

	अगर (unlikely(uncore->debug->unclaimed_mmio_check <= 0))
		जाओ out;

	अगर (unlikely(check_क्रम_unclaimed_mmio(uncore))) अणु
		अगर (!uncore->i915->params.mmio_debug) अणु
			drm_dbg(&uncore->i915->drm,
				"Unclaimed register detected, "
				"enabling oneshot unclaimed register reporting. "
				"Please use i915.mmio_debug=N for more information.\n");
			uncore->i915->params.mmio_debug++;
		पूर्ण
		uncore->debug->unclaimed_mmio_check--;
		ret = true;
	पूर्ण

out:
	spin_unlock_irq(&uncore->debug->lock);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_uncore_क्रमcewake_क्रम_reg - which क्रमcewake करोमुख्यs are needed to access
 * 				    a रेजिस्टर
 * @uncore: poपूर्णांकer to काष्ठा पूर्णांकel_uncore
 * @reg: रेजिस्टर in question
 * @op: operation biपंचांगask of FW_REG_READ and/or FW_REG_WRITE
 *
 * Returns a set of क्रमcewake करोमुख्यs required to be taken with क्रम example
 * पूर्णांकel_uncore_क्रमcewake_get क्रम the specअगरied रेजिस्टर to be accessible in the
 * specअगरied mode (पढ़ो, ग_लिखो or पढ़ो/ग_लिखो) with raw mmio accessors.
 *
 * NOTE: On Gen6 and Gen7 ग_लिखो क्रमcewake करोमुख्य (FORCEWAKE_RENDER) requires the
 * callers to करो FIFO management on their own or risk losing ग_लिखोs.
 */
क्रमागत क्रमcewake_करोमुख्यs
पूर्णांकel_uncore_क्रमcewake_क्रम_reg(काष्ठा पूर्णांकel_uncore *uncore,
			       i915_reg_t reg, अचिन्हित पूर्णांक op)
अणु
	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs = 0;

	drm_WARN_ON(&uncore->i915->drm, !op);

	अगर (!पूर्णांकel_uncore_has_क्रमcewake(uncore))
		वापस 0;

	अगर (op & FW_REG_READ)
		fw_करोमुख्यs = uncore->funcs.पढ़ो_fw_करोमुख्यs(uncore, reg);

	अगर (op & FW_REG_WRITE)
		fw_करोमुख्यs |= uncore->funcs.ग_लिखो_fw_करोमुख्यs(uncore, reg);

	drm_WARN_ON(&uncore->i915->drm, fw_करोमुख्यs & ~uncore->fw_करोमुख्यs);

	वापस fw_करोमुख्यs;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/mock_uncore.c"
#समावेश "selftests/intel_uncore.c"
#पूर्ण_अगर
