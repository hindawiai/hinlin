<शैली गुरु>
/*
 * Copyright तऊ 2015-2016 Intel Corporation
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
 *
 * Authors:
 *   Robert Bragg <robert@sixbynine.org>
 */


/**
 * DOC: i915 Perf Overview
 *
 * Gen graphics supports a large number of perक्रमmance counters that can help
 * driver and application developers understand and optimize their use of the
 * GPU.
 *
 * This i915 perf पूर्णांकerface enables userspace to configure and खोलो a file
 * descriptor representing a stream of GPU metrics which can then be पढ़ो() as
 * a stream of sample records.
 *
 * The पूर्णांकerface is particularly suited to exposing buffered metrics that are
 * captured by DMA from the GPU, unsynchronized with and unrelated to the CPU.
 *
 * Streams representing a single context are accessible to applications with a
 * corresponding drm file descriptor, such that OpenGL can use the पूर्णांकerface
 * without special privileges. Access to प्रणाली-wide metrics requires root
 * privileges by शेष, unless changed via the dev.i915.perf_event_paranoid
 * sysctl option.
 *
 */

/**
 * DOC: i915 Perf History and Comparison with Core Perf
 *
 * The पूर्णांकerface was initially inspired by the core Perf infraकाष्ठाure but
 * some notable dअगरferences are:
 *
 * i915 perf file descriptors represent a "stream" instead of an "event"; where
 * a perf event primarily corresponds to a single 64bit value, जबतक a stream
 * might sample sets of tightly-coupled counters, depending on the
 * configuration.  For example the Gen OA unit isn't deचिन्हित to support
 * orthogonal configurations of inभागidual counters; it's configured क्रम a set
 * of related counters. Samples क्रम an i915 perf stream capturing OA metrics
 * will include a set of counter values packed in a compact HW specअगरic क्रमmat.
 * The OA unit supports a number of dअगरferent packing क्रमmats which can be
 * selected by the user खोलोing the stream. Perf has support क्रम grouping
 * events, but each event in the group is configured, validated and
 * authenticated inभागidually with separate प्रणाली calls.
 *
 * i915 perf stream configurations are provided as an array of u64 (key,value)
 * pairs, instead of a fixed काष्ठा with multiple miscellaneous config members,
 * पूर्णांकerleaved with event-type specअगरic members.
 *
 * i915 perf करोesn't support exposing metrics via an mmap'd circular buffer.
 * The supported metrics are being written to memory by the GPU unsynchronized
 * with the CPU, using HW specअगरic packing क्रमmats क्रम counter sets. Someबार
 * the स्थिरraपूर्णांकs on HW configuration require reports to be filtered beक्रमe it
 * would be acceptable to expose them to unprivileged applications - to hide
 * the metrics of other processes/contexts. For these use हालs a पढ़ो() based
 * पूर्णांकerface is a good fit, and provides an opportunity to filter data as it
 * माला_लो copied from the GPU mapped buffers to userspace buffers.
 *
 *
 * Issues hit with first prototype based on Core Perf
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * The first prototype of this driver was based on the core perf
 * infraकाष्ठाure, and जबतक we did make that mostly work, with some changes to
 * perf, we found we were अवरोधing or working around too many assumptions baked
 * पूर्णांकo perf's currently cpu centric design.
 *
 * In the end we didn't see a clear benefit to making perf's implementation and
 * पूर्णांकerface more complex by changing design assumptions जबतक we knew we still
 * wouldn't be able to use any existing perf based userspace tools.
 *
 * Also considering the Gen specअगरic nature of the Observability hardware and
 * how userspace will someबार need to combine i915 perf OA metrics with
 * side-band OA data captured via MI_REPORT_PERF_COUNT commands; we're
 * expecting the पूर्णांकerface to be used by a platक्रमm specअगरic userspace such as
 * OpenGL or tools. This is to say; we aren't inherently missing out on having
 * a standard venकरोr/architecture agnostic पूर्णांकerface by not using perf.
 *
 *
 * For posterity, in हाल we might re-visit trying to adapt core perf to be
 * better suited to exposing i915 metrics these were the मुख्य pain poपूर्णांकs we
 * hit:
 *
 * - The perf based OA PMU driver broke some signअगरicant design assumptions:
 *
 *   Existing perf pmus are used क्रम profiling work on a cpu and we were
 *   पूर्णांकroducing the idea of _IS_DEVICE pmus with dअगरferent security
 *   implications, the need to fake cpu-related data (such as user/kernel
 *   रेजिस्टरs) to fit with perf's current design, and adding _DEVICE records
 *   as a way to क्रमward device-specअगरic status records.
 *
 *   The OA unit ग_लिखोs reports of counters पूर्णांकo a circular buffer, without
 *   involvement from the CPU, making our PMU driver the first of a kind.
 *
 *   Given the way we were periodically क्रमward data from the GPU-mapped, OA
 *   buffer to perf's buffer, those bursts of sample ग_लिखोs looked to perf like
 *   we were sampling too fast and so we had to subvert its throttling checks.
 *
 *   Perf supports groups of counters and allows those to be पढ़ो via
 *   transactions पूर्णांकernally but transactions currently seem deचिन्हित to be
 *   explicitly initiated from the cpu (say in response to a userspace पढ़ो())
 *   and जबतक we could pull a report out of the OA buffer we can't
 *   trigger a report from the cpu on demand.
 *
 *   Related to being report based; the OA counters are configured in HW as a
 *   set जबतक perf generally expects counter configurations to be orthogonal.
 *   Although counters can be associated with a group leader as they are
 *   खोलोed, there's no clear precedent क्रम being able to provide group-wide
 *   configuration attributes (क्रम example we want to let userspace choose the
 *   OA unit report क्रमmat used to capture all counters in a set, or specअगरy a
 *   GPU context to filter metrics on). We aव्योमed using perf's grouping
 *   feature and क्रमwarded OA reports to userspace via perf's 'raw' sample
 *   field. This suited our userspace well considering how coupled the counters
 *   are when dealing with normalizing. It would be inconvenient to split
 *   counters up पूर्णांकo separate events, only to require userspace to recombine
 *   them. For Mesa it's also convenient to be क्रमwarded raw, periodic reports
 *   क्रम combining with the side-band raw reports it captures using
 *   MI_REPORT_PERF_COUNT commands.
 *
 *   - As a side note on perf's grouping feature; there was also some concern
 *     that using PERF_FORMAT_GROUP as a way to pack together counter values
 *     would quite drastically inflate our sample sizes, which would likely
 *     lower the effective sampling resolutions we could use when the available
 *     memory bandwidth is limited.
 *
 *     With the OA unit's report क्रमmats, counters are packed together as 32
 *     or 40bit values, with the largest report size being 256 bytes.
 *
 *     PERF_FORMAT_GROUP values are 64bit, but there करोesn't appear to be a
 *     करोcumented ordering to the values, implying PERF_FORMAT_ID must also be
 *     used to add a 64bit ID beक्रमe each value; giving 16 bytes per counter.
 *
 *   Related to counter orthogonality; we can't समय share the OA unit, जबतक
 *   event scheduling is a central design idea within perf क्रम allowing
 *   userspace to खोलो + enable more events than can be configured in HW at any
 *   one समय.  The OA unit is not deचिन्हित to allow re-configuration जबतक in
 *   use. We can't reconfigure the OA unit without losing पूर्णांकernal OA unit
 *   state which we can't access explicitly to save and restore. Reconfiguring
 *   the OA unit is also relatively slow, involving ~100 रेजिस्टर ग_लिखोs. From
 *   userspace Mesa also depends on a stable OA configuration when emitting
 *   MI_REPORT_PERF_COUNT commands and importantly the OA unit can't be
 *   disabled जबतक there are outstanding MI_RPC commands lest we hang the
 *   command streamer.
 *
 *   The contents of sample records aren't extensible by device drivers (i.e.
 *   the sample_type bits). As an example; Sourab Gupta had been looking to
 *   attach GPU बारtamps to our OA samples. We were shoehorning OA reports
 *   पूर्णांकo sample records by using the 'raw' field, but it's tricky to pack more
 *   than one thing पूर्णांकo this field because events/core.c currently only lets a
 *   pmu give a single raw data poपूर्णांकer plus len which will be copied पूर्णांकo the
 *   ring buffer. To include more than the OA report we'd have to copy the
 *   report पूर्णांकo an पूर्णांकermediate larger buffer. I'd been considering allowing a
 *   vector of data+len values to be specअगरied क्रम copying the raw data, but
 *   it felt like a kludge to being using the raw field क्रम this purpose.
 *
 * - It felt like our perf based PMU was making some technical compromises
 *   just क्रम the sake of using perf:
 *
 *   perf_event_खोलो() requires events to either relate to a pid or a specअगरic
 *   cpu core, जबतक our device pmu related to neither.  Events खोलोed with a
 *   pid will be स्वतःmatically enabled/disabled according to the scheduling of
 *   that process - so not appropriate क्रम us. When an event is related to a
 *   cpu id, perf ensures pmu methods will be invoked via an पूर्णांकer process
 *   पूर्णांकerrupt on that core. To aव्योम invasive changes our userspace खोलोed OA
 *   perf events क्रम a specअगरic cpu. This was workable but it meant the
 *   majority of the OA driver ran in atomic context, including all OA report
 *   क्रमwarding, which wasn't really necessary in our हाल and seems to make
 *   our locking requirements somewhat complex as we handled the पूर्णांकeraction
 *   with the rest of the i915 driver.
 */

#समावेश <linux/anon_inodes.h>
#समावेश <linux/sizes.h>
#समावेश <linux/uuid.h>

#समावेश "gem/i915_gem_context.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_engine_user.h"
#समावेश "gt/intel_execlists_submission.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_clock_utils.h"
#समावेश "gt/intel_lrc.h"
#समावेश "gt/intel_ring.h"

#समावेश "i915_drv.h"
#समावेश "i915_perf.h"

/* HW requires this to be a घातer of two, between 128k and 16M, though driver
 * is currently generally deचिन्हित assuming the largest 16M size is used such
 * that the overflow हालs are unlikely in normal operation.
 */
#घोषणा OA_BUFFER_SIZE		SZ_16M

#घोषणा OA_TAKEN(tail, head)	((tail - head) & (OA_BUFFER_SIZE - 1))

/**
 * DOC: OA Tail Poपूर्णांकer Race
 *
 * There's a HW race condition between OA unit tail poपूर्णांकer रेजिस्टर updates and
 * ग_लिखोs to memory whereby the tail poपूर्णांकer can someबार get ahead of what's
 * been written out to the OA buffer so far (in terms of what's visible to the
 * CPU).
 *
 * Although this can be observed explicitly जबतक copying reports to userspace
 * by checking क्रम a zeroed report-id field in tail reports, we want to account
 * क्रम this earlier, as part of the oa_buffer_check_unlocked to aव्योम lots of
 * redundant पढ़ो() attempts.
 *
 * We workaround this issue in oa_buffer_check_unlocked() by पढ़ोing the reports
 * in the OA buffer, starting from the tail reported by the HW until we find a
 * report with its first 2 dwords not 0 meaning its previous report is
 * completely in memory and पढ़ोy to be पढ़ो. Those dwords are also set to 0
 * once पढ़ो and the whole buffer is cleared upon OA buffer initialization. The
 * first dword is the reason क्रम this report जबतक the second is the बारtamp,
 * making the chances of having those 2 fields at 0 fairly unlikely. A more
 * detailed explanation is available in oa_buffer_check_unlocked().
 *
 * Most of the implementation details क्रम this workaround are in
 * oa_buffer_check_unlocked() and _append_oa_reports()
 *
 * Note क्रम posterity: previously the driver used to define an effective tail
 * poपूर्णांकer that lagged the real poपूर्णांकer by a 'tail margin' measured in bytes
 * derived from %OA_TAIL_MARGIN_NSEC and the configured sampling frequency.
 * This was flawed considering that the OA unit may also स्वतःmatically generate
 * non-periodic reports (such as on context चयन) or the OA unit may be
 * enabled without any periodic sampling.
 */
#घोषणा OA_TAIL_MARGIN_NSEC	100000ULL
#घोषणा INVALID_TAIL_PTR	0xffffffff

/* The शेष frequency क्रम checking whether the OA unit has written new
 * reports to the circular OA buffer...
 */
#घोषणा DEFAULT_POLL_FREQUENCY_HZ 200
#घोषणा DEFAULT_POLL_PERIOD_NS (NSEC_PER_SEC / DEFAULT_POLL_FREQUENCY_HZ)

/* क्रम sysctl proc_करोपूर्णांकvec_minmax of dev.i915.perf_stream_paranoid */
अटल u32 i915_perf_stream_paranoid = true;

/* The maximum exponent the hardware accepts is 63 (essentially it selects one
 * of the 64bit बारtamp bits to trigger reports from) but there's currently
 * no known use हाल क्रम sampling as infrequently as once per 47 thousand years.
 *
 * Since the बारtamps included in OA reports are only 32bits it seems
 * reasonable to limit the OA exponent where it's still possible to account क्रम
 * overflow in OA report बारtamps.
 */
#घोषणा OA_EXPONENT_MAX 31

#घोषणा INVALID_CTX_ID 0xffffffff

/* On Gen8+ स्वतःmatically triggered OA reports include a 'reason' field... */
#घोषणा OAREPORT_REASON_MASK           0x3f
#घोषणा OAREPORT_REASON_MASK_EXTENDED  0x7f
#घोषणा OAREPORT_REASON_SHIFT          19
#घोषणा OAREPORT_REASON_TIMER          (1<<0)
#घोषणा OAREPORT_REASON_CTX_SWITCH     (1<<3)
#घोषणा OAREPORT_REASON_CLK_RATIO      (1<<5)


/* For sysctl proc_करोपूर्णांकvec_minmax of i915_oa_max_sample_rate
 *
 * The highest sampling frequency we can theoretically program the OA unit
 * with is always half the बारtamp frequency: E.g. 6.25Mhz क्रम Haswell.
 *
 * Initialized just beक्रमe we रेजिस्टर the sysctl parameter.
 */
अटल पूर्णांक oa_sample_rate_hard_limit;

/* Theoretically we can program the OA unit to sample every 160ns but करोn't
 * allow that by शेष unless root...
 *
 * The शेष threshold of 100000Hz is based on perf's similar
 * kernel.perf_event_max_sample_rate sysctl parameter.
 */
अटल u32 i915_oa_max_sample_rate = 100000;

/* XXX: beware अगर future OA HW adds new report क्रमmats that the current
 * code assumes all reports have a घातer-of-two size and ~(size - 1) can
 * be used as a mask to align the OA tail poपूर्णांकer.
 */
अटल स्थिर काष्ठा i915_oa_क्रमmat oa_क्रमmats[I915_OA_FORMAT_MAX] = अणु
	[I915_OA_FORMAT_A13]	    = अणु 0, 64 पूर्ण,
	[I915_OA_FORMAT_A29]	    = अणु 1, 128 पूर्ण,
	[I915_OA_FORMAT_A13_B8_C8]  = अणु 2, 128 पूर्ण,
	/* A29_B8_C8 Disallowed as 192 bytes करोesn't factor पूर्णांकo buffer size */
	[I915_OA_FORMAT_B4_C8]	    = अणु 4, 64 पूर्ण,
	[I915_OA_FORMAT_A45_B8_C8]  = अणु 5, 256 पूर्ण,
	[I915_OA_FORMAT_B4_C8_A16]  = अणु 6, 128 पूर्ण,
	[I915_OA_FORMAT_C4_B8]	    = अणु 7, 64 पूर्ण,
	[I915_OA_FORMAT_A12]		    = अणु 0, 64 पूर्ण,
	[I915_OA_FORMAT_A12_B8_C8]	    = अणु 2, 128 पूर्ण,
	[I915_OA_FORMAT_A32u40_A4u32_B8_C8] = अणु 5, 256 पूर्ण,
पूर्ण;

#घोषणा SAMPLE_OA_REPORT      (1<<0)

/**
 * काष्ठा perf_खोलो_properties - क्रम validated properties given to खोलो a stream
 * @sample_flags: `DRM_I915_PERF_PROP_SAMPLE_*` properties are tracked as flags
 * @single_context: Whether a single or all gpu contexts should be monitored
 * @hold_preemption: Whether the preemption is disabled क्रम the filtered
 *                   context
 * @ctx_handle: A gem ctx handle क्रम use with @single_context
 * @metrics_set: An ID क्रम an OA unit metric set advertised via sysfs
 * @oa_क्रमmat: An OA unit HW report क्रमmat
 * @oa_periodic: Whether to enable periodic OA unit sampling
 * @oa_period_exponent: The OA unit sampling period is derived from this
 * @engine: The engine (typically rcs0) being monitored by the OA unit
 * @has_sseu: Whether @sseu was specअगरied by userspace
 * @sseu: पूर्णांकernal SSEU configuration computed either from the userspace
 *        specअगरied configuration in the खोलोing parameters or a शेष value
 *        (see get_शेष_sseu_config())
 * @poll_oa_period: The period in nanoseconds at which the CPU will check क्रम OA
 * data availability
 *
 * As पढ़ो_properties_unlocked() क्रमागतerates and validates the properties given
 * to खोलो a stream of metrics the configuration is built up in the काष्ठाure
 * which starts out zero initialized.
 */
काष्ठा perf_खोलो_properties अणु
	u32 sample_flags;

	u64 single_context:1;
	u64 hold_preemption:1;
	u64 ctx_handle;

	/* OA sampling state */
	पूर्णांक metrics_set;
	पूर्णांक oa_क्रमmat;
	bool oa_periodic;
	पूर्णांक oa_period_exponent;

	काष्ठा पूर्णांकel_engine_cs *engine;

	bool has_sseu;
	काष्ठा पूर्णांकel_sseu sseu;

	u64 poll_oa_period;
पूर्ण;

काष्ठा i915_oa_config_bo अणु
	काष्ठा llist_node node;

	काष्ठा i915_oa_config *oa_config;
	काष्ठा i915_vma *vma;
पूर्ण;

अटल काष्ठा ctl_table_header *sysctl_header;

अटल क्रमागत hrसमयr_restart oa_poll_check_समयr_cb(काष्ठा hrसमयr *hrसमयr);

व्योम i915_oa_config_release(काष्ठा kref *ref)
अणु
	काष्ठा i915_oa_config *oa_config =
		container_of(ref, typeof(*oa_config), ref);

	kमुक्त(oa_config->flex_regs);
	kमुक्त(oa_config->b_counter_regs);
	kमुक्त(oa_config->mux_regs);

	kमुक्त_rcu(oa_config, rcu);
पूर्ण

काष्ठा i915_oa_config *
i915_perf_get_oa_config(काष्ठा i915_perf *perf, पूर्णांक metrics_set)
अणु
	काष्ठा i915_oa_config *oa_config;

	rcu_पढ़ो_lock();
	oa_config = idr_find(&perf->metrics_idr, metrics_set);
	अगर (oa_config)
		oa_config = i915_oa_config_get(oa_config);
	rcu_पढ़ो_unlock();

	वापस oa_config;
पूर्ण

अटल व्योम मुक्त_oa_config_bo(काष्ठा i915_oa_config_bo *oa_bo)
अणु
	i915_oa_config_put(oa_bo->oa_config);
	i915_vma_put(oa_bo->vma);
	kमुक्त(oa_bo);
पूर्ण

अटल u32 gen12_oa_hw_tail_पढ़ो(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	वापस पूर्णांकel_uncore_पढ़ो(uncore, GEN12_OAG_OATAILPTR) &
	       GEN12_OAG_OATAILPTR_MASK;
पूर्ण

अटल u32 gen8_oa_hw_tail_पढ़ो(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	वापस पूर्णांकel_uncore_पढ़ो(uncore, GEN8_OATAILPTR) & GEN8_OATAILPTR_MASK;
पूर्ण

अटल u32 gen7_oa_hw_tail_पढ़ो(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	u32 oastatus1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_OASTATUS1);

	वापस oastatus1 & GEN7_OASTATUS1_TAIL_MASK;
पूर्ण

/**
 * oa_buffer_check_unlocked - check क्रम data and update tail ptr state
 * @stream: i915 stream instance
 *
 * This is either called via fops (क्रम blocking पढ़ोs in user ctx) or the poll
 * check hrसमयr (atomic ctx) to check the OA buffer tail poपूर्णांकer and check
 * अगर there is data available क्रम userspace to पढ़ो.
 *
 * This function is central to providing a workaround क्रम the OA unit tail
 * poपूर्णांकer having a race with respect to what data is visible to the CPU.
 * It is responsible क्रम पढ़ोing tail poपूर्णांकers from the hardware and giving
 * the poपूर्णांकers समय to 'age' beक्रमe they are made available क्रम पढ़ोing.
 * (See description of OA_TAIL_MARGIN_NSEC above क्रम further details.)
 *
 * Besides वापसing true when there is data available to पढ़ो() this function
 * also updates the tail, aging_tail and aging_बारtamp in the oa_buffer
 * object.
 *
 * Note: It's safe to पढ़ो OA config state here unlocked, assuming that this is
 * only called जबतक the stream is enabled, जबतक the global OA configuration
 * can't be modअगरied.
 *
 * Returns: %true अगर the OA buffer contains data, अन्यथा %false
 */
अटल bool oa_buffer_check_unlocked(काष्ठा i915_perf_stream *stream)
अणु
	u32 gtt_offset = i915_ggtt_offset(stream->oa_buffer.vma);
	पूर्णांक report_size = stream->oa_buffer.क्रमmat_size;
	अचिन्हित दीर्घ flags;
	bool pollin;
	u32 hw_tail;
	u64 now;

	/* We have to consider the (unlikely) possibility that पढ़ो() errors
	 * could result in an OA buffer reset which might reset the head and
	 * tail state.
	 */
	spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

	hw_tail = stream->perf->ops.oa_hw_tail_पढ़ो(stream);

	/* The tail poपूर्णांकer increases in 64 byte increments,
	 * not in report_size steps...
	 */
	hw_tail &= ~(report_size - 1);

	now = kसमय_get_mono_fast_ns();

	अगर (hw_tail == stream->oa_buffer.aging_tail &&
	    (now - stream->oa_buffer.aging_बारtamp) > OA_TAIL_MARGIN_NSEC) अणु
		/* If the HW tail hasn't move since the last check and the HW
		 * tail has been aging क्रम दीर्घ enough, declare it the new
		 * tail.
		 */
		stream->oa_buffer.tail = stream->oa_buffer.aging_tail;
	पूर्ण अन्यथा अणु
		u32 head, tail, aged_tail;

		/* NB: The head we observe here might effectively be a little
		 * out of date. If a पढ़ो() is in progress, the head could be
		 * anywhere between this head and stream->oa_buffer.tail.
		 */
		head = stream->oa_buffer.head - gtt_offset;
		aged_tail = stream->oa_buffer.tail - gtt_offset;

		hw_tail -= gtt_offset;
		tail = hw_tail;

		/* Walk the stream backward until we find a report with dword 0
		 * & 1 not at 0. Since the circular buffer poपूर्णांकers progress by
		 * increments of 64 bytes and that reports can be up to 256
		 * bytes दीर्घ, we can't tell whether a report has fully landed
		 * in memory beक्रमe the first 2 dwords of the following report
		 * have effectively landed.
		 *
		 * This is assuming that the ग_लिखोs of the OA unit land in
		 * memory in the order they were written to.
		 * If not : (ै/तओैँतओoञ	ै/oचग ैझैैझ
		 */
		जबतक (OA_TAKEN(tail, aged_tail) >= report_size) अणु
			u32 *report32 = (व्योम *)(stream->oa_buffer.vaddr + tail);

			अगर (report32[0] != 0 || report32[1] != 0)
				अवरोध;

			tail = (tail - report_size) & (OA_BUFFER_SIZE - 1);
		पूर्ण

		अगर (OA_TAKEN(hw_tail, tail) > report_size &&
		    __ratelimit(&stream->perf->tail_poपूर्णांकer_race))
			DRM_NOTE("unlanded report(s) head=0x%x "
				 "tail=0x%x hw_tail=0x%x\n",
				 head, tail, hw_tail);

		stream->oa_buffer.tail = gtt_offset + tail;
		stream->oa_buffer.aging_tail = gtt_offset + hw_tail;
		stream->oa_buffer.aging_बारtamp = now;
	पूर्ण

	pollin = OA_TAKEN(stream->oa_buffer.tail - gtt_offset,
			  stream->oa_buffer.head - gtt_offset) >= report_size;

	spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);

	वापस pollin;
पूर्ण

/**
 * append_oa_status - Appends a status record to a userspace पढ़ो() buffer.
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 * @buf: destination buffer given by userspace
 * @count: the number of bytes userspace wants to पढ़ो
 * @offset: (inout): the current position क्रम writing पूर्णांकo @buf
 * @type: The kind of status to report to userspace
 *
 * Writes a status record (such as `DRM_I915_PERF_RECORD_OA_REPORT_LOST`)
 * पूर्णांकo the userspace पढ़ो() buffer.
 *
 * The @buf @offset will only be updated on success.
 *
 * Returns: 0 on success, negative error code on failure.
 */
अटल पूर्णांक append_oa_status(काष्ठा i915_perf_stream *stream,
			    अक्षर __user *buf,
			    माप_प्रकार count,
			    माप_प्रकार *offset,
			    क्रमागत drm_i915_perf_record_type type)
अणु
	काष्ठा drm_i915_perf_record_header header = अणु type, 0, माप(header) पूर्ण;

	अगर ((count - *offset) < header.size)
		वापस -ENOSPC;

	अगर (copy_to_user(buf + *offset, &header, माप(header)))
		वापस -EFAULT;

	(*offset) += header.size;

	वापस 0;
पूर्ण

/**
 * append_oa_sample - Copies single OA report पूर्णांकo userspace पढ़ो() buffer.
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 * @buf: destination buffer given by userspace
 * @count: the number of bytes userspace wants to पढ़ो
 * @offset: (inout): the current position क्रम writing पूर्णांकo @buf
 * @report: A single OA report to (optionally) include as part of the sample
 *
 * The contents of a sample are configured through `DRM_I915_PERF_PROP_SAMPLE_*`
 * properties when खोलोing a stream, tracked as `stream->sample_flags`. This
 * function copies the requested components of a single sample to the given
 * पढ़ो() @buf.
 *
 * The @buf @offset will only be updated on success.
 *
 * Returns: 0 on success, negative error code on failure.
 */
अटल पूर्णांक append_oa_sample(काष्ठा i915_perf_stream *stream,
			    अक्षर __user *buf,
			    माप_प्रकार count,
			    माप_प्रकार *offset,
			    स्थिर u8 *report)
अणु
	पूर्णांक report_size = stream->oa_buffer.क्रमmat_size;
	काष्ठा drm_i915_perf_record_header header;

	header.type = DRM_I915_PERF_RECORD_SAMPLE;
	header.pad = 0;
	header.size = stream->sample_size;

	अगर ((count - *offset) < header.size)
		वापस -ENOSPC;

	buf += *offset;
	अगर (copy_to_user(buf, &header, माप(header)))
		वापस -EFAULT;
	buf += माप(header);

	अगर (copy_to_user(buf, report, report_size))
		वापस -EFAULT;

	(*offset) += header.size;

	वापस 0;
पूर्ण

/**
 * gen8_append_oa_reports - Copies all buffered OA reports पूर्णांकo
 *			    userspace पढ़ो() buffer.
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 * @buf: destination buffer given by userspace
 * @count: the number of bytes userspace wants to पढ़ो
 * @offset: (inout): the current position क्रम writing पूर्णांकo @buf
 *
 * Notably any error condition resulting in a लघु पढ़ो (-%ENOSPC or
 * -%EFAULT) will be वापसed even though one or more records may
 * have been successfully copied. In this हाल it's up to the caller
 * to decide अगर the error should be squashed beक्रमe वापसing to
 * userspace.
 *
 * Note: reports are consumed from the head, and appended to the
 * tail, so the tail chases the head?... If you think that's mad
 * and back-to-front you're not alone, but this follows the
 * Gen PRM naming convention.
 *
 * Returns: 0 on success, negative error code on failure.
 */
अटल पूर्णांक gen8_append_oa_reports(काष्ठा i915_perf_stream *stream,
				  अक्षर __user *buf,
				  माप_प्रकार count,
				  माप_प्रकार *offset)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	पूर्णांक report_size = stream->oa_buffer.क्रमmat_size;
	u8 *oa_buf_base = stream->oa_buffer.vaddr;
	u32 gtt_offset = i915_ggtt_offset(stream->oa_buffer.vma);
	u32 mask = (OA_BUFFER_SIZE - 1);
	माप_प्रकार start_offset = *offset;
	अचिन्हित दीर्घ flags;
	u32 head, tail;
	u32 taken;
	पूर्णांक ret = 0;

	अगर (drm_WARN_ON(&uncore->i915->drm, !stream->enabled))
		वापस -EIO;

	spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

	head = stream->oa_buffer.head;
	tail = stream->oa_buffer.tail;

	spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);

	/*
	 * NB: oa_buffer.head/tail include the gtt_offset which we करोn't want
	 * जबतक indexing relative to oa_buf_base.
	 */
	head -= gtt_offset;
	tail -= gtt_offset;

	/*
	 * An out of bounds or misaligned head or tail poपूर्णांकer implies a driver
	 * bug since we validate + align the tail poपूर्णांकers we पढ़ो from the
	 * hardware and we are in full control of the head poपूर्णांकer which should
	 * only be incremented by multiples of the report size (notably also
	 * all a घातer of two).
	 */
	अगर (drm_WARN_ONCE(&uncore->i915->drm,
			  head > OA_BUFFER_SIZE || head % report_size ||
			  tail > OA_BUFFER_SIZE || tail % report_size,
			  "Inconsistent OA buffer pointers: head = %u, tail = %u\n",
			  head, tail))
		वापस -EIO;


	क्रम (/* none */;
	     (taken = OA_TAKEN(tail, head));
	     head = (head + report_size) & mask) अणु
		u8 *report = oa_buf_base + head;
		u32 *report32 = (व्योम *)report;
		u32 ctx_id;
		u32 reason;

		/*
		 * All the report sizes factor neatly पूर्णांकo the buffer
		 * size so we never expect to see a report split
		 * between the beginning and end of the buffer.
		 *
		 * Given the initial alignment check a misalignment
		 * here would imply a driver bug that would result
		 * in an overrun.
		 */
		अगर (drm_WARN_ON(&uncore->i915->drm,
				(OA_BUFFER_SIZE - head) < report_size)) अणु
			drm_err(&uncore->i915->drm,
				"Spurious OA head ptr: non-integral report offset\n");
			अवरोध;
		पूर्ण

		/*
		 * The reason field includes flags identअगरying what
		 * triggered this specअगरic report (mostly समयr
		 * triggered or e.g. due to a context चयन).
		 *
		 * This field is never expected to be zero so we can
		 * check that the report isn't invalid beक्रमe copying
		 * it to userspace...
		 */
		reason = ((report32[0] >> OAREPORT_REASON_SHIFT) &
			  (IS_GEN(stream->perf->i915, 12) ?
			   OAREPORT_REASON_MASK_EXTENDED :
			   OAREPORT_REASON_MASK));

		ctx_id = report32[2] & stream->specअगरic_ctx_id_mask;

		/*
		 * Squash whatever is in the CTX_ID field अगर it's marked as
		 * invalid to be sure we aव्योम false-positive, single-context
		 * filtering below...
		 *
		 * Note: that we करोn't clear the valid_ctx_bit so userspace can
		 * understand that the ID has been squashed by the kernel.
		 */
		अगर (!(report32[0] & stream->perf->gen8_valid_ctx_bit) &&
		    INTEL_GEN(stream->perf->i915) <= 11)
			ctx_id = report32[2] = INVALID_CTX_ID;

		/*
		 * NB: For Gen 8 the OA unit no दीर्घer supports घड़ी gating
		 * off क्रम a specअगरic context and the kernel can't securely
		 * stop the counters from updating as प्रणाली-wide / global
		 * values.
		 *
		 * Automatic reports now include a context ID so reports can be
		 * filtered on the cpu but it's not worth trying to
		 * स्वतःmatically subtract/hide counter progress क्रम other
		 * contexts जबतक filtering since we can't stop userspace
		 * issuing MI_REPORT_PERF_COUNT commands which would still
		 * provide a side-band view of the real values.
		 *
		 * To allow userspace (such as Mesa/GL_INTEL_perक्रमmance_query)
		 * to normalize counters क्रम a single filtered context then it
		 * needs be क्रमwarded bookend context-चयन reports so that it
		 * can track चयनes in between MI_REPORT_PERF_COUNT commands
		 * and can itself subtract/ignore the progress of counters
		 * associated with other contexts. Note that the hardware
		 * स्वतःmatically triggers reports when चयनing to a new
		 * context which are tagged with the ID of the newly active
		 * context. To aव्योम the complनिकासy (and likely fragility) of
		 * पढ़ोing ahead जबतक parsing reports to try and minimize
		 * क्रमwarding redundant context चयन reports (i.e. between
		 * other, unrelated contexts) we simply elect to क्रमward them
		 * all.
		 *
		 * We करोn't rely solely on the reason field to identअगरy context
		 * चयनes since it's not-uncommon क्रम periodic samples to
		 * identअगरy a चयन beक्रमe any 'context switch' report.
		 */
		अगर (!stream->perf->exclusive_stream->ctx ||
		    stream->specअगरic_ctx_id == ctx_id ||
		    stream->oa_buffer.last_ctx_id == stream->specअगरic_ctx_id ||
		    reason & OAREPORT_REASON_CTX_SWITCH) अणु

			/*
			 * While filtering क्रम a single context we aव्योम
			 * leaking the IDs of other contexts.
			 */
			अगर (stream->perf->exclusive_stream->ctx &&
			    stream->specअगरic_ctx_id != ctx_id) अणु
				report32[2] = INVALID_CTX_ID;
			पूर्ण

			ret = append_oa_sample(stream, buf, count, offset,
					       report);
			अगर (ret)
				अवरोध;

			stream->oa_buffer.last_ctx_id = ctx_id;
		पूर्ण

		/*
		 * Clear out the first 2 dword as a mean to detect unlanded
		 * reports.
		 */
		report32[0] = 0;
		report32[1] = 0;
	पूर्ण

	अगर (start_offset != *offset) अणु
		i915_reg_t oaheadptr;

		oaheadptr = IS_GEN(stream->perf->i915, 12) ?
			    GEN12_OAG_OAHEADPTR : GEN8_OAHEADPTR;

		spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

		/*
		 * We हटाओd the gtt_offset क्रम the copy loop above, indexing
		 * relative to oa_buf_base so put back here...
		 */
		head += gtt_offset;
		पूर्णांकel_uncore_ग_लिखो(uncore, oaheadptr,
				   head & GEN12_OAG_OAHEADPTR_MASK);
		stream->oa_buffer.head = head;

		spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * gen8_oa_पढ़ो - copy status records then buffered OA reports
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 * @buf: destination buffer given by userspace
 * @count: the number of bytes userspace wants to पढ़ो
 * @offset: (inout): the current position क्रम writing पूर्णांकo @buf
 *
 * Checks OA unit status रेजिस्टरs and अगर necessary appends corresponding
 * status records क्रम userspace (such as क्रम a buffer full condition) and then
 * initiate appending any buffered OA reports.
 *
 * Updates @offset according to the number of bytes successfully copied पूर्णांकo
 * the userspace buffer.
 *
 * NB: some data may be successfully copied to the userspace buffer
 * even अगर an error is वापसed, and this is reflected in the
 * updated @offset.
 *
 * Returns: zero on success or a negative error code
 */
अटल पूर्णांक gen8_oa_पढ़ो(काष्ठा i915_perf_stream *stream,
			अक्षर __user *buf,
			माप_प्रकार count,
			माप_प्रकार *offset)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	u32 oastatus;
	i915_reg_t oastatus_reg;
	पूर्णांक ret;

	अगर (drm_WARN_ON(&uncore->i915->drm, !stream->oa_buffer.vaddr))
		वापस -EIO;

	oastatus_reg = IS_GEN(stream->perf->i915, 12) ?
		       GEN12_OAG_OASTATUS : GEN8_OASTATUS;

	oastatus = पूर्णांकel_uncore_पढ़ो(uncore, oastatus_reg);

	/*
	 * We treat OABUFFER_OVERFLOW as a signअगरicant error:
	 *
	 * Although theoretically we could handle this more gracefully
	 * someबार, some Gens करोn't correctly suppress certain
	 * स्वतःmatically triggered reports in this condition and so we
	 * have to assume that old reports are now being trampled
	 * over.
	 *
	 * Considering how we करोn't currently give userspace control
	 * over the OA buffer size and always configure a large 16MB
	 * buffer, then a buffer overflow करोes anyway likely indicate
	 * that something has gone quite badly wrong.
	 */
	अगर (oastatus & GEN8_OASTATUS_OABUFFER_OVERFLOW) अणु
		ret = append_oa_status(stream, buf, count, offset,
				       DRM_I915_PERF_RECORD_OA_BUFFER_LOST);
		अगर (ret)
			वापस ret;

		DRM_DEBUG("OA buffer overflow (exponent = %d): force restart\n",
			  stream->period_exponent);

		stream->perf->ops.oa_disable(stream);
		stream->perf->ops.oa_enable(stream);

		/*
		 * Note: .oa_enable() is expected to re-init the oabuffer and
		 * reset GEN8_OASTATUS क्रम us
		 */
		oastatus = पूर्णांकel_uncore_पढ़ो(uncore, oastatus_reg);
	पूर्ण

	अगर (oastatus & GEN8_OASTATUS_REPORT_LOST) अणु
		ret = append_oa_status(stream, buf, count, offset,
				       DRM_I915_PERF_RECORD_OA_REPORT_LOST);
		अगर (ret)
			वापस ret;

		पूर्णांकel_uncore_rmw(uncore, oastatus_reg,
				 GEN8_OASTATUS_COUNTER_OVERFLOW |
				 GEN8_OASTATUS_REPORT_LOST,
				 IS_GEN_RANGE(uncore->i915, 8, 11) ?
				 (GEN8_OASTATUS_HEAD_POINTER_WRAP |
				  GEN8_OASTATUS_TAIL_POINTER_WRAP) : 0);
	पूर्ण

	वापस gen8_append_oa_reports(stream, buf, count, offset);
पूर्ण

/**
 * gen7_append_oa_reports - Copies all buffered OA reports पूर्णांकo
 *			    userspace पढ़ो() buffer.
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 * @buf: destination buffer given by userspace
 * @count: the number of bytes userspace wants to पढ़ो
 * @offset: (inout): the current position क्रम writing पूर्णांकo @buf
 *
 * Notably any error condition resulting in a लघु पढ़ो (-%ENOSPC or
 * -%EFAULT) will be वापसed even though one or more records may
 * have been successfully copied. In this हाल it's up to the caller
 * to decide अगर the error should be squashed beक्रमe वापसing to
 * userspace.
 *
 * Note: reports are consumed from the head, and appended to the
 * tail, so the tail chases the head?... If you think that's mad
 * and back-to-front you're not alone, but this follows the
 * Gen PRM naming convention.
 *
 * Returns: 0 on success, negative error code on failure.
 */
अटल पूर्णांक gen7_append_oa_reports(काष्ठा i915_perf_stream *stream,
				  अक्षर __user *buf,
				  माप_प्रकार count,
				  माप_प्रकार *offset)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	पूर्णांक report_size = stream->oa_buffer.क्रमmat_size;
	u8 *oa_buf_base = stream->oa_buffer.vaddr;
	u32 gtt_offset = i915_ggtt_offset(stream->oa_buffer.vma);
	u32 mask = (OA_BUFFER_SIZE - 1);
	माप_प्रकार start_offset = *offset;
	अचिन्हित दीर्घ flags;
	u32 head, tail;
	u32 taken;
	पूर्णांक ret = 0;

	अगर (drm_WARN_ON(&uncore->i915->drm, !stream->enabled))
		वापस -EIO;

	spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

	head = stream->oa_buffer.head;
	tail = stream->oa_buffer.tail;

	spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);

	/* NB: oa_buffer.head/tail include the gtt_offset which we करोn't want
	 * जबतक indexing relative to oa_buf_base.
	 */
	head -= gtt_offset;
	tail -= gtt_offset;

	/* An out of bounds or misaligned head or tail poपूर्णांकer implies a driver
	 * bug since we validate + align the tail poपूर्णांकers we पढ़ो from the
	 * hardware and we are in full control of the head poपूर्णांकer which should
	 * only be incremented by multiples of the report size (notably also
	 * all a घातer of two).
	 */
	अगर (drm_WARN_ONCE(&uncore->i915->drm,
			  head > OA_BUFFER_SIZE || head % report_size ||
			  tail > OA_BUFFER_SIZE || tail % report_size,
			  "Inconsistent OA buffer pointers: head = %u, tail = %u\n",
			  head, tail))
		वापस -EIO;


	क्रम (/* none */;
	     (taken = OA_TAKEN(tail, head));
	     head = (head + report_size) & mask) अणु
		u8 *report = oa_buf_base + head;
		u32 *report32 = (व्योम *)report;

		/* All the report sizes factor neatly पूर्णांकo the buffer
		 * size so we never expect to see a report split
		 * between the beginning and end of the buffer.
		 *
		 * Given the initial alignment check a misalignment
		 * here would imply a driver bug that would result
		 * in an overrun.
		 */
		अगर (drm_WARN_ON(&uncore->i915->drm,
				(OA_BUFFER_SIZE - head) < report_size)) अणु
			drm_err(&uncore->i915->drm,
				"Spurious OA head ptr: non-integral report offset\n");
			अवरोध;
		पूर्ण

		/* The report-ID field क्रम periodic samples includes
		 * some unकरोcumented flags related to what triggered
		 * the report and is never expected to be zero so we
		 * can check that the report isn't invalid beक्रमe
		 * copying it to userspace...
		 */
		अगर (report32[0] == 0) अणु
			अगर (__ratelimit(&stream->perf->spurious_report_rs))
				DRM_NOTE("Skipping spurious, invalid OA report\n");
			जारी;
		पूर्ण

		ret = append_oa_sample(stream, buf, count, offset, report);
		अगर (ret)
			अवरोध;

		/* Clear out the first 2 dwords as a mean to detect unlanded
		 * reports.
		 */
		report32[0] = 0;
		report32[1] = 0;
	पूर्ण

	अगर (start_offset != *offset) अणु
		spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

		/* We हटाओd the gtt_offset क्रम the copy loop above, indexing
		 * relative to oa_buf_base so put back here...
		 */
		head += gtt_offset;

		पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_OASTATUS2,
				   (head & GEN7_OASTATUS2_HEAD_MASK) |
				   GEN7_OASTATUS2_MEM_SELECT_GGTT);
		stream->oa_buffer.head = head;

		spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * gen7_oa_पढ़ो - copy status records then buffered OA reports
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 * @buf: destination buffer given by userspace
 * @count: the number of bytes userspace wants to पढ़ो
 * @offset: (inout): the current position क्रम writing पूर्णांकo @buf
 *
 * Checks Gen 7 specअगरic OA unit status रेजिस्टरs and अगर necessary appends
 * corresponding status records क्रम userspace (such as क्रम a buffer full
 * condition) and then initiate appending any buffered OA reports.
 *
 * Updates @offset according to the number of bytes successfully copied पूर्णांकo
 * the userspace buffer.
 *
 * Returns: zero on success or a negative error code
 */
अटल पूर्णांक gen7_oa_पढ़ो(काष्ठा i915_perf_stream *stream,
			अक्षर __user *buf,
			माप_प्रकार count,
			माप_प्रकार *offset)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	u32 oastatus1;
	पूर्णांक ret;

	अगर (drm_WARN_ON(&uncore->i915->drm, !stream->oa_buffer.vaddr))
		वापस -EIO;

	oastatus1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_OASTATUS1);

	/* XXX: On Haswell we करोn't have a safe way to clear oastatus1
	 * bits जबतक the OA unit is enabled (जबतक the tail poपूर्णांकer
	 * may be updated asynchronously) so we ignore status bits
	 * that have alपढ़ोy been reported to userspace.
	 */
	oastatus1 &= ~stream->perf->gen7_latched_oastatus1;

	/* We treat OABUFFER_OVERFLOW as a signअगरicant error:
	 *
	 * - The status can be पूर्णांकerpreted to mean that the buffer is
	 *   currently full (with a higher precedence than OA_TAKEN()
	 *   which will start to report a near-empty buffer after an
	 *   overflow) but it's awkward that we can't clear the status
	 *   on Haswell, so without a reset we won't be able to catch
	 *   the state again.
	 *
	 * - Since it also implies the HW has started overwriting old
	 *   reports it may also affect our sanity checks क्रम invalid
	 *   reports when copying to userspace that assume new reports
	 *   are being written to cleared memory.
	 *
	 * - In the future we may want to पूर्णांकroduce a flight recorder
	 *   mode where the driver will स्वतःmatically मुख्यtain a safe
	 *   guard band between head/tail, aव्योमing this overflow
	 *   condition, but we aव्योम the added driver complनिकासy क्रम
	 *   now.
	 */
	अगर (unlikely(oastatus1 & GEN7_OASTATUS1_OABUFFER_OVERFLOW)) अणु
		ret = append_oa_status(stream, buf, count, offset,
				       DRM_I915_PERF_RECORD_OA_BUFFER_LOST);
		अगर (ret)
			वापस ret;

		DRM_DEBUG("OA buffer overflow (exponent = %d): force restart\n",
			  stream->period_exponent);

		stream->perf->ops.oa_disable(stream);
		stream->perf->ops.oa_enable(stream);

		oastatus1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_OASTATUS1);
	पूर्ण

	अगर (unlikely(oastatus1 & GEN7_OASTATUS1_REPORT_LOST)) अणु
		ret = append_oa_status(stream, buf, count, offset,
				       DRM_I915_PERF_RECORD_OA_REPORT_LOST);
		अगर (ret)
			वापस ret;
		stream->perf->gen7_latched_oastatus1 |=
			GEN7_OASTATUS1_REPORT_LOST;
	पूर्ण

	वापस gen7_append_oa_reports(stream, buf, count, offset);
पूर्ण

/**
 * i915_oa_रुको_unlocked - handles blocking IO until OA data available
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 *
 * Called when userspace tries to पढ़ो() from a blocking stream FD खोलोed
 * क्रम OA metrics. It रुकोs until the hrसमयr callback finds a non-empty
 * OA buffer and wakes us.
 *
 * Note: it's acceptable to have this वापस with some false positives
 * since any subsequent पढ़ो handling will वापस -EAGAIN अगर there isn't
 * really data पढ़ोy क्रम userspace yet.
 *
 * Returns: zero on success or a negative error code
 */
अटल पूर्णांक i915_oa_रुको_unlocked(काष्ठा i915_perf_stream *stream)
अणु
	/* We would रुको indefinitely अगर periodic sampling is not enabled */
	अगर (!stream->periodic)
		वापस -EIO;

	वापस रुको_event_पूर्णांकerruptible(stream->poll_wq,
					oa_buffer_check_unlocked(stream));
पूर्ण

/**
 * i915_oa_poll_रुको - call poll_रुको() क्रम an OA stream poll()
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 * @file: An i915 perf stream file
 * @रुको: poll() state table
 *
 * For handling userspace polling on an i915 perf stream खोलोed क्रम OA metrics,
 * this starts a poll_रुको with the रुको queue that our hrसमयr callback wakes
 * when it sees data पढ़ोy to पढ़ो in the circular OA buffer.
 */
अटल व्योम i915_oa_poll_रुको(काष्ठा i915_perf_stream *stream,
			      काष्ठा file *file,
			      poll_table *रुको)
अणु
	poll_रुको(file, &stream->poll_wq, रुको);
पूर्ण

/**
 * i915_oa_पढ़ो - just calls through to &i915_oa_ops->पढ़ो
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 * @buf: destination buffer given by userspace
 * @count: the number of bytes userspace wants to पढ़ो
 * @offset: (inout): the current position क्रम writing पूर्णांकo @buf
 *
 * Updates @offset according to the number of bytes successfully copied पूर्णांकo
 * the userspace buffer.
 *
 * Returns: zero on success or a negative error code
 */
अटल पूर्णांक i915_oa_पढ़ो(काष्ठा i915_perf_stream *stream,
			अक्षर __user *buf,
			माप_प्रकार count,
			माप_प्रकार *offset)
अणु
	वापस stream->perf->ops.पढ़ो(stream, buf, count, offset);
पूर्ण

अटल काष्ठा पूर्णांकel_context *oa_pin_context(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा i915_gem_engines_iter it;
	काष्ठा i915_gem_context *ctx = stream->ctx;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err = -ENODEV;

	क्रम_each_gem_engine(ce, i915_gem_context_lock_engines(ctx), it) अणु
		अगर (ce->engine != stream->engine) /* first match! */
			जारी;

		err = 0;
		अवरोध;
	पूर्ण
	i915_gem_context_unlock_engines(ctx);

	अगर (err)
		वापस ERR_PTR(err);

	i915_gem_ww_ctx_init(&ww, true);
retry:
	/*
	 * As the ID is the gtt offset of the context's vma we
	 * pin the vma to ensure the ID reमुख्यs fixed.
	 */
	err = पूर्णांकel_context_pin_ww(ce, &ww);
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);

	अगर (err)
		वापस ERR_PTR(err);

	stream->pinned_ctx = ce;
	वापस stream->pinned_ctx;
पूर्ण

/**
 * oa_get_render_ctx_id - determine and hold ctx hw id
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 *
 * Determine the render context hw id, and ensure it reमुख्यs fixed क्रम the
 * lअगरeसमय of the stream. This ensures that we करोn't have to worry about
 * updating the context ID in OACONTROL on the fly.
 *
 * Returns: zero on success or a negative error code
 */
अटल पूर्णांक oa_get_render_ctx_id(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_context *ce;

	ce = oa_pin_context(stream);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	चयन (INTEL_GEN(ce->engine->i915)) अणु
	हाल 7: अणु
		/*
		 * On Haswell we करोn't करो any post processing of the reports
		 * and करोn't need to use the mask.
		 */
		stream->specअगरic_ctx_id = i915_ggtt_offset(ce->state);
		stream->specअगरic_ctx_id_mask = 0;
		अवरोध;
	पूर्ण

	हाल 8:
	हाल 9:
	हाल 10:
		अगर (पूर्णांकel_engine_in_execlists_submission_mode(ce->engine)) अणु
			stream->specअगरic_ctx_id_mask =
				(1U << GEN8_CTX_ID_WIDTH) - 1;
			stream->specअगरic_ctx_id = stream->specअगरic_ctx_id_mask;
		पूर्ण अन्यथा अणु
			/*
			 * When using GuC, the context descriptor we ग_लिखो in
			 * i915 is पढ़ो by GuC and rewritten beक्रमe it's
			 * actually written पूर्णांकo the hardware. The LRCA is
			 * what is put पूर्णांकo the context id field of the
			 * context descriptor by GuC. Because it's aligned to
			 * a page, the lower 12bits are always at 0 and
			 * dropped by GuC. They won't be part of the context
			 * ID in the OA reports, so squash those lower bits.
			 */
			stream->specअगरic_ctx_id = ce->lrc.lrca >> 12;

			/*
			 * GuC uses the top bit to संकेत proxy submission, so
			 * ignore that bit.
			 */
			stream->specअगरic_ctx_id_mask =
				(1U << (GEN8_CTX_ID_WIDTH - 1)) - 1;
		पूर्ण
		अवरोध;

	हाल 11:
	हाल 12: अणु
		stream->specअगरic_ctx_id_mask =
			((1U << GEN11_SW_CTX_ID_WIDTH) - 1) << (GEN11_SW_CTX_ID_SHIFT - 32);
		/*
		 * Pick an unused context id
		 * 0 - BITS_PER_LONG are used by other contexts
		 * GEN12_MAX_CONTEXT_HW_ID (0x7ff) is used by idle context
		 */
		stream->specअगरic_ctx_id = (GEN12_MAX_CONTEXT_HW_ID - 1) << (GEN11_SW_CTX_ID_SHIFT - 32);
		अवरोध;
	पूर्ण

	शेष:
		MISSING_CASE(INTEL_GEN(ce->engine->i915));
	पूर्ण

	ce->tag = stream->specअगरic_ctx_id;

	drm_dbg(&stream->perf->i915->drm,
		"filtering on ctx_id=0x%x ctx_id_mask=0x%x\n",
		stream->specअगरic_ctx_id,
		stream->specअगरic_ctx_id_mask);

	वापस 0;
पूर्ण

/**
 * oa_put_render_ctx_id - counterpart to oa_get_render_ctx_id releases hold
 * @stream: An i915-perf stream खोलोed क्रम OA metrics
 *
 * In हाल anything needed करोing to ensure the context HW ID would reमुख्य valid
 * क्रम the lअगरeसमय of the stream, then that can be unकरोne here.
 */
अटल व्योम oa_put_render_ctx_id(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_context *ce;

	ce = fetch_and_zero(&stream->pinned_ctx);
	अगर (ce) अणु
		ce->tag = 0; /* recomputed on next submission after parking */
		पूर्णांकel_context_unpin(ce);
	पूर्ण

	stream->specअगरic_ctx_id = INVALID_CTX_ID;
	stream->specअगरic_ctx_id_mask = 0;
पूर्ण

अटल व्योम
मुक्त_oa_buffer(काष्ठा i915_perf_stream *stream)
अणु
	i915_vma_unpin_and_release(&stream->oa_buffer.vma,
				   I915_VMA_RELEASE_MAP);

	stream->oa_buffer.vaddr = शून्य;
पूर्ण

अटल व्योम
मुक्त_oa_configs(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा i915_oa_config_bo *oa_bo, *पंचांगp;

	i915_oa_config_put(stream->oa_config);
	llist_क्रम_each_entry_safe(oa_bo, पंचांगp, stream->oa_config_bos.first, node)
		मुक्त_oa_config_bo(oa_bo);
पूर्ण

अटल व्योम
मुक्त_noa_रुको(काष्ठा i915_perf_stream *stream)
अणु
	i915_vma_unpin_and_release(&stream->noa_रुको, 0);
पूर्ण

अटल व्योम i915_oa_stream_destroy(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा i915_perf *perf = stream->perf;

	BUG_ON(stream != perf->exclusive_stream);

	/*
	 * Unset exclusive_stream first, it will be checked जबतक disabling
	 * the metric set on gen8+.
	 *
	 * See i915_oa_init_reg_state() and lrc_configure_all_contexts()
	 */
	WRITE_ONCE(perf->exclusive_stream, शून्य);
	perf->ops.disable_metric_set(stream);

	मुक्त_oa_buffer(stream);

	पूर्णांकel_uncore_क्रमcewake_put(stream->uncore, FORCEWAKE_ALL);
	पूर्णांकel_engine_pm_put(stream->engine);

	अगर (stream->ctx)
		oa_put_render_ctx_id(stream);

	मुक्त_oa_configs(stream);
	मुक्त_noa_रुको(stream);

	अगर (perf->spurious_report_rs.missed) अणु
		DRM_NOTE("%d spurious OA report notices suppressed due to ratelimiting\n",
			 perf->spurious_report_rs.missed);
	पूर्ण
पूर्ण

अटल व्योम gen7_init_oa_buffer(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	u32 gtt_offset = i915_ggtt_offset(stream->oa_buffer.vma);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

	/* Pre-DevBDW: OABUFFER must be set with counters off,
	 * beक्रमe OASTATUS1, but after OASTATUS2
	 */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_OASTATUS2, /* head */
			   gtt_offset | GEN7_OASTATUS2_MEM_SELECT_GGTT);
	stream->oa_buffer.head = gtt_offset;

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_OABUFFER, gtt_offset);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_OASTATUS1, /* tail */
			   gtt_offset | OABUFFER_SIZE_16M);

	/* Mark that we need updated tail poपूर्णांकers to पढ़ो from... */
	stream->oa_buffer.aging_tail = INVALID_TAIL_PTR;
	stream->oa_buffer.tail = gtt_offset;

	spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);

	/* On Haswell we have to track which OASTATUS1 flags we've
	 * alपढ़ोy seen since they can't be cleared जबतक periodic
	 * sampling is enabled.
	 */
	stream->perf->gen7_latched_oastatus1 = 0;

	/* NB: although the OA buffer will initially be allocated
	 * zeroed via shmfs (and so this स_रखो is redundant when
	 * first allocating), we may re-init the OA buffer, either
	 * when re-enabling a stream or in error/reset paths.
	 *
	 * The reason we clear the buffer क्रम each re-init is क्रम the
	 * sanity check in gen7_append_oa_reports() that looks at the
	 * report-id field to make sure it's non-zero which relies on
	 * the assumption that new reports are being written to zeroed
	 * memory...
	 */
	स_रखो(stream->oa_buffer.vaddr, 0, OA_BUFFER_SIZE);
पूर्ण

अटल व्योम gen8_init_oa_buffer(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	u32 gtt_offset = i915_ggtt_offset(stream->oa_buffer.vma);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_OASTATUS, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_OAHEADPTR, gtt_offset);
	stream->oa_buffer.head = gtt_offset;

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_OABUFFER_UDW, 0);

	/*
	 * PRM says:
	 *
	 *  "This MMIO must be set beक्रमe the OATAILPTR
	 *  रेजिस्टर and after the OAHEADPTR रेजिस्टर. This is
	 *  to enable proper functionality of the overflow
	 *  bit."
	 */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_OABUFFER, gtt_offset |
		   OABUFFER_SIZE_16M | GEN8_OABUFFER_MEM_SELECT_GGTT);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_OATAILPTR, gtt_offset & GEN8_OATAILPTR_MASK);

	/* Mark that we need updated tail poपूर्णांकers to पढ़ो from... */
	stream->oa_buffer.aging_tail = INVALID_TAIL_PTR;
	stream->oa_buffer.tail = gtt_offset;

	/*
	 * Reset state used to recognise context चयनes, affecting which
	 * reports we will क्रमward to userspace जबतक filtering क्रम a single
	 * context.
	 */
	stream->oa_buffer.last_ctx_id = INVALID_CTX_ID;

	spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);

	/*
	 * NB: although the OA buffer will initially be allocated
	 * zeroed via shmfs (and so this स_रखो is redundant when
	 * first allocating), we may re-init the OA buffer, either
	 * when re-enabling a stream or in error/reset paths.
	 *
	 * The reason we clear the buffer क्रम each re-init is क्रम the
	 * sanity check in gen8_append_oa_reports() that looks at the
	 * reason field to make sure it's non-zero which relies on
	 * the assumption that new reports are being written to zeroed
	 * memory...
	 */
	स_रखो(stream->oa_buffer.vaddr, 0, OA_BUFFER_SIZE);
पूर्ण

अटल व्योम gen12_init_oa_buffer(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	u32 gtt_offset = i915_ggtt_offset(stream->oa_buffer.vma);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&stream->oa_buffer.ptr_lock, flags);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OAG_OASTATUS, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OAG_OAHEADPTR,
			   gtt_offset & GEN12_OAG_OAHEADPTR_MASK);
	stream->oa_buffer.head = gtt_offset;

	/*
	 * PRM says:
	 *
	 *  "This MMIO must be set beक्रमe the OATAILPTR
	 *  रेजिस्टर and after the OAHEADPTR रेजिस्टर. This is
	 *  to enable proper functionality of the overflow
	 *  bit."
	 */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OAG_OABUFFER, gtt_offset |
			   OABUFFER_SIZE_16M | GEN8_OABUFFER_MEM_SELECT_GGTT);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OAG_OATAILPTR,
			   gtt_offset & GEN12_OAG_OATAILPTR_MASK);

	/* Mark that we need updated tail poपूर्णांकers to पढ़ो from... */
	stream->oa_buffer.aging_tail = INVALID_TAIL_PTR;
	stream->oa_buffer.tail = gtt_offset;

	/*
	 * Reset state used to recognise context चयनes, affecting which
	 * reports we will क्रमward to userspace जबतक filtering क्रम a single
	 * context.
	 */
	stream->oa_buffer.last_ctx_id = INVALID_CTX_ID;

	spin_unlock_irqrestore(&stream->oa_buffer.ptr_lock, flags);

	/*
	 * NB: although the OA buffer will initially be allocated
	 * zeroed via shmfs (and so this स_रखो is redundant when
	 * first allocating), we may re-init the OA buffer, either
	 * when re-enabling a stream or in error/reset paths.
	 *
	 * The reason we clear the buffer क्रम each re-init is क्रम the
	 * sanity check in gen8_append_oa_reports() that looks at the
	 * reason field to make sure it's non-zero which relies on
	 * the assumption that new reports are being written to zeroed
	 * memory...
	 */
	स_रखो(stream->oa_buffer.vaddr, 0,
	       stream->oa_buffer.vma->size);
पूर्ण

अटल पूर्णांक alloc_oa_buffer(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा drm_i915_निजी *i915 = stream->perf->i915;
	काष्ठा drm_i915_gem_object *bo;
	काष्ठा i915_vma *vma;
	पूर्णांक ret;

	अगर (drm_WARN_ON(&i915->drm, stream->oa_buffer.vma))
		वापस -ENODEV;

	BUILD_BUG_ON_NOT_POWER_OF_2(OA_BUFFER_SIZE);
	BUILD_BUG_ON(OA_BUFFER_SIZE < SZ_128K || OA_BUFFER_SIZE > SZ_16M);

	bo = i915_gem_object_create_shmem(stream->perf->i915, OA_BUFFER_SIZE);
	अगर (IS_ERR(bo)) अणु
		drm_err(&i915->drm, "Failed to allocate OA buffer\n");
		वापस PTR_ERR(bo);
	पूर्ण

	i915_gem_object_set_cache_coherency(bo, I915_CACHE_LLC);

	/* PreHSW required 512K alignment, HSW requires 16M */
	vma = i915_gem_object_ggtt_pin(bo, शून्य, 0, SZ_16M, 0);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ err_unref;
	पूर्ण
	stream->oa_buffer.vma = vma;

	stream->oa_buffer.vaddr =
		i915_gem_object_pin_map_unlocked(bo, I915_MAP_WB);
	अगर (IS_ERR(stream->oa_buffer.vaddr)) अणु
		ret = PTR_ERR(stream->oa_buffer.vaddr);
		जाओ err_unpin;
	पूर्ण

	वापस 0;

err_unpin:
	__i915_vma_unpin(vma);

err_unref:
	i915_gem_object_put(bo);

	stream->oa_buffer.vaddr = शून्य;
	stream->oa_buffer.vma = शून्य;

	वापस ret;
पूर्ण

अटल u32 *save_restore_रेजिस्टर(काष्ठा i915_perf_stream *stream, u32 *cs,
				  bool save, i915_reg_t reg, u32 offset,
				  u32 dword_count)
अणु
	u32 cmd;
	u32 d;

	cmd = save ? MI_STORE_REGISTER_MEM : MI_LOAD_REGISTER_MEM;
	cmd |= MI_SRM_LRM_GLOBAL_GTT;
	अगर (INTEL_GEN(stream->perf->i915) >= 8)
		cmd++;

	क्रम (d = 0; d < dword_count; d++) अणु
		*cs++ = cmd;
		*cs++ = i915_mmio_reg_offset(reg) + 4 * d;
		*cs++ = पूर्णांकel_gt_scratch_offset(stream->engine->gt,
						offset) + 4 * d;
		*cs++ = 0;
	पूर्ण

	वापस cs;
पूर्ण

अटल पूर्णांक alloc_noa_रुको(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा drm_i915_निजी *i915 = stream->perf->i915;
	काष्ठा drm_i915_gem_object *bo;
	काष्ठा i915_vma *vma;
	स्थिर u64 delay_ticks = 0xffffffffffffffff -
		पूर्णांकel_gt_ns_to_घड़ी_पूर्णांकerval(stream->perf->i915->ggtt.vm.gt,
					      atomic64_पढ़ो(&stream->perf->noa_programming_delay));
	स्थिर u32 base = stream->engine->mmio_base;
#घोषणा CS_GPR(x) GEN8_RING_CS_GPR(base, x)
	u32 *batch, *ts0, *cs, *jump;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक ret, i;
	क्रमागत अणु
		START_TS,
		NOW_TS,
		DELTA_TS,
		JUMP_PREDICATE,
		DELTA_TARGET,
		N_CS_GPR
	पूर्ण;

	bo = i915_gem_object_create_पूर्णांकernal(i915, 4096);
	अगर (IS_ERR(bo)) अणु
		drm_err(&i915->drm,
			"Failed to allocate NOA wait batchbuffer\n");
		वापस PTR_ERR(bo);
	पूर्ण

	i915_gem_ww_ctx_init(&ww, true);
retry:
	ret = i915_gem_object_lock(bo, &ww);
	अगर (ret)
		जाओ out_ww;

	/*
	 * We pin in GGTT because we jump पूर्णांकo this buffer now because
	 * multiple OA config BOs will have a jump to this address and it
	 * needs to be fixed during the lअगरeसमय of the i915/perf stream.
	 */
	vma = i915_gem_object_ggtt_pin_ww(bo, &ww, शून्य, 0, 0, PIN_HIGH);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out_ww;
	पूर्ण

	batch = cs = i915_gem_object_pin_map(bo, I915_MAP_WB);
	अगर (IS_ERR(batch)) अणु
		ret = PTR_ERR(batch);
		जाओ err_unpin;
	पूर्ण

	/* Save रेजिस्टरs. */
	क्रम (i = 0; i < N_CS_GPR; i++)
		cs = save_restore_रेजिस्टर(
			stream, cs, true /* save */, CS_GPR(i),
			INTEL_GT_SCRATCH_FIELD_PERF_CS_GPR + 8 * i, 2);
	cs = save_restore_रेजिस्टर(
		stream, cs, true /* save */, MI_PREDICATE_RESULT_1,
		INTEL_GT_SCRATCH_FIELD_PERF_PREDICATE_RESULT_1, 1);

	/* First बारtamp snapshot location. */
	ts0 = cs;

	/*
	 * Initial snapshot of the बारtamp रेजिस्टर to implement the रुको.
	 * We work with 32b values, so clear out the top 32b bits of the
	 * रेजिस्टर because the ALU works 64bits.
	 */
	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(CS_GPR(START_TS)) + 4;
	*cs++ = 0;
	*cs++ = MI_LOAD_REGISTER_REG | (3 - 2);
	*cs++ = i915_mmio_reg_offset(RING_TIMESTAMP(base));
	*cs++ = i915_mmio_reg_offset(CS_GPR(START_TS));

	/*
	 * This is the location we're going to jump back पूर्णांकo until the
	 * required amount of समय has passed.
	 */
	jump = cs;

	/*
	 * Take another snapshot of the बारtamp रेजिस्टर. Take care to clear
	 * up the top 32bits of CS_GPR(1) as we're using it क्रम other
	 * operations below.
	 */
	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(CS_GPR(NOW_TS)) + 4;
	*cs++ = 0;
	*cs++ = MI_LOAD_REGISTER_REG | (3 - 2);
	*cs++ = i915_mmio_reg_offset(RING_TIMESTAMP(base));
	*cs++ = i915_mmio_reg_offset(CS_GPR(NOW_TS));

	/*
	 * Do a dअगरf between the 2 बारtamps and store the result back पूर्णांकo
	 * CS_GPR(1).
	 */
	*cs++ = MI_MATH(5);
	*cs++ = MI_MATH_LOAD(MI_MATH_REG_SRCA, MI_MATH_REG(NOW_TS));
	*cs++ = MI_MATH_LOAD(MI_MATH_REG_SRCB, MI_MATH_REG(START_TS));
	*cs++ = MI_MATH_SUB;
	*cs++ = MI_MATH_STORE(MI_MATH_REG(DELTA_TS), MI_MATH_REG_ACCU);
	*cs++ = MI_MATH_STORE(MI_MATH_REG(JUMP_PREDICATE), MI_MATH_REG_CF);

	/*
	 * Transfer the carry flag (set to 1 अगर ts1 < ts0, meaning the
	 * बारtamp have rolled over the 32bits) पूर्णांकo the predicate रेजिस्टर
	 * to be used क्रम the predicated jump.
	 */
	*cs++ = MI_LOAD_REGISTER_REG | (3 - 2);
	*cs++ = i915_mmio_reg_offset(CS_GPR(JUMP_PREDICATE));
	*cs++ = i915_mmio_reg_offset(MI_PREDICATE_RESULT_1);

	/* Restart from the beginning अगर we had बारtamps roll over. */
	*cs++ = (INTEL_GEN(i915) < 8 ?
		 MI_BATCH_BUFFER_START :
		 MI_BATCH_BUFFER_START_GEN8) |
		MI_BATCH_PREDICATE;
	*cs++ = i915_ggtt_offset(vma) + (ts0 - batch) * 4;
	*cs++ = 0;

	/*
	 * Now add the dअगरf between to previous बारtamps and add it to :
	 *      (((1 * << 64) - 1) - delay_ns)
	 *
	 * When the Carry Flag contains 1 this means the elapsed समय is
	 * दीर्घer than the expected delay, and we can निकास the रुको loop.
	 */
	*cs++ = MI_LOAD_REGISTER_IMM(2);
	*cs++ = i915_mmio_reg_offset(CS_GPR(DELTA_TARGET));
	*cs++ = lower_32_bits(delay_ticks);
	*cs++ = i915_mmio_reg_offset(CS_GPR(DELTA_TARGET)) + 4;
	*cs++ = upper_32_bits(delay_ticks);

	*cs++ = MI_MATH(4);
	*cs++ = MI_MATH_LOAD(MI_MATH_REG_SRCA, MI_MATH_REG(DELTA_TS));
	*cs++ = MI_MATH_LOAD(MI_MATH_REG_SRCB, MI_MATH_REG(DELTA_TARGET));
	*cs++ = MI_MATH_ADD;
	*cs++ = MI_MATH_STOREINV(MI_MATH_REG(JUMP_PREDICATE), MI_MATH_REG_CF);

	*cs++ = MI_ARB_CHECK;

	/*
	 * Transfer the result पूर्णांकo the predicate रेजिस्टर to be used क्रम the
	 * predicated jump.
	 */
	*cs++ = MI_LOAD_REGISTER_REG | (3 - 2);
	*cs++ = i915_mmio_reg_offset(CS_GPR(JUMP_PREDICATE));
	*cs++ = i915_mmio_reg_offset(MI_PREDICATE_RESULT_1);

	/* Predicate the jump.  */
	*cs++ = (INTEL_GEN(i915) < 8 ?
		 MI_BATCH_BUFFER_START :
		 MI_BATCH_BUFFER_START_GEN8) |
		MI_BATCH_PREDICATE;
	*cs++ = i915_ggtt_offset(vma) + (jump - batch) * 4;
	*cs++ = 0;

	/* Restore रेजिस्टरs. */
	क्रम (i = 0; i < N_CS_GPR; i++)
		cs = save_restore_रेजिस्टर(
			stream, cs, false /* restore */, CS_GPR(i),
			INTEL_GT_SCRATCH_FIELD_PERF_CS_GPR + 8 * i, 2);
	cs = save_restore_रेजिस्टर(
		stream, cs, false /* restore */, MI_PREDICATE_RESULT_1,
		INTEL_GT_SCRATCH_FIELD_PERF_PREDICATE_RESULT_1, 1);

	/* And वापस to the ring. */
	*cs++ = MI_BATCH_BUFFER_END;

	GEM_BUG_ON(cs - batch > PAGE_SIZE / माप(*batch));

	i915_gem_object_flush_map(bo);
	__i915_gem_object_release_map(bo);

	stream->noa_रुको = vma;
	जाओ out_ww;

err_unpin:
	i915_vma_unpin_and_release(&vma, 0);
out_ww:
	अगर (ret == -EDEADLK) अणु
		ret = i915_gem_ww_ctx_backoff(&ww);
		अगर (!ret)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	अगर (ret)
		i915_gem_object_put(bo);
	वापस ret;
पूर्ण

अटल u32 *ग_लिखो_cs_mi_lri(u32 *cs,
			    स्थिर काष्ठा i915_oa_reg *reg_data,
			    u32 n_regs)
अणु
	u32 i;

	क्रम (i = 0; i < n_regs; i++) अणु
		अगर ((i % MI_LOAD_REGISTER_IMM_MAX_REGS) == 0) अणु
			u32 n_lri = min_t(u32,
					  n_regs - i,
					  MI_LOAD_REGISTER_IMM_MAX_REGS);

			*cs++ = MI_LOAD_REGISTER_IMM(n_lri);
		पूर्ण
		*cs++ = i915_mmio_reg_offset(reg_data[i].addr);
		*cs++ = reg_data[i].value;
	पूर्ण

	वापस cs;
पूर्ण

अटल पूर्णांक num_lri_dwords(पूर्णांक num_regs)
अणु
	पूर्णांक count = 0;

	अगर (num_regs > 0) अणु
		count += DIV_ROUND_UP(num_regs, MI_LOAD_REGISTER_IMM_MAX_REGS);
		count += num_regs * 2;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा i915_oa_config_bo *
alloc_oa_config_buffer(काष्ठा i915_perf_stream *stream,
		       काष्ठा i915_oa_config *oa_config)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_oa_config_bo *oa_bo;
	काष्ठा i915_gem_ww_ctx ww;
	माप_प्रकार config_length = 0;
	u32 *cs;
	पूर्णांक err;

	oa_bo = kzalloc(माप(*oa_bo), GFP_KERNEL);
	अगर (!oa_bo)
		वापस ERR_PTR(-ENOMEM);

	config_length += num_lri_dwords(oa_config->mux_regs_len);
	config_length += num_lri_dwords(oa_config->b_counter_regs_len);
	config_length += num_lri_dwords(oa_config->flex_regs_len);
	config_length += 3; /* MI_BATCH_BUFFER_START */
	config_length = ALIGN(माप(u32) * config_length, I915_GTT_PAGE_SIZE);

	obj = i915_gem_object_create_shmem(stream->perf->i915, config_length);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ err_मुक्त;
	पूर्ण

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = i915_gem_object_lock(obj, &ww);
	अगर (err)
		जाओ out_ww;

	cs = i915_gem_object_pin_map(obj, I915_MAP_WB);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ out_ww;
	पूर्ण

	cs = ग_लिखो_cs_mi_lri(cs,
			     oa_config->mux_regs,
			     oa_config->mux_regs_len);
	cs = ग_लिखो_cs_mi_lri(cs,
			     oa_config->b_counter_regs,
			     oa_config->b_counter_regs_len);
	cs = ग_लिखो_cs_mi_lri(cs,
			     oa_config->flex_regs,
			     oa_config->flex_regs_len);

	/* Jump पूर्णांकo the active रुको. */
	*cs++ = (INTEL_GEN(stream->perf->i915) < 8 ?
		 MI_BATCH_BUFFER_START :
		 MI_BATCH_BUFFER_START_GEN8);
	*cs++ = i915_ggtt_offset(stream->noa_रुको);
	*cs++ = 0;

	i915_gem_object_flush_map(obj);
	__i915_gem_object_release_map(obj);

	oa_bo->vma = i915_vma_instance(obj,
				       &stream->engine->gt->ggtt->vm,
				       शून्य);
	अगर (IS_ERR(oa_bo->vma)) अणु
		err = PTR_ERR(oa_bo->vma);
		जाओ out_ww;
	पूर्ण

	oa_bo->oa_config = i915_oa_config_get(oa_config);
	llist_add(&oa_bo->node, &stream->oa_config_bos);

out_ww:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);

	अगर (err)
		i915_gem_object_put(obj);
err_मुक्त:
	अगर (err) अणु
		kमुक्त(oa_bo);
		वापस ERR_PTR(err);
	पूर्ण
	वापस oa_bo;
पूर्ण

अटल काष्ठा i915_vma *
get_oa_vma(काष्ठा i915_perf_stream *stream, काष्ठा i915_oa_config *oa_config)
अणु
	काष्ठा i915_oa_config_bo *oa_bo;

	/*
	 * Look क्रम the buffer in the alपढ़ोy allocated BOs attached
	 * to the stream.
	 */
	llist_क्रम_each_entry(oa_bo, stream->oa_config_bos.first, node) अणु
		अगर (oa_bo->oa_config == oa_config &&
		    स_भेद(oa_bo->oa_config->uuid,
			   oa_config->uuid,
			   माप(oa_config->uuid)) == 0)
			जाओ out;
	पूर्ण

	oa_bo = alloc_oa_config_buffer(stream, oa_config);
	अगर (IS_ERR(oa_bo))
		वापस ERR_CAST(oa_bo);

out:
	वापस i915_vma_get(oa_bo->vma);
पूर्ण

अटल पूर्णांक
emit_oa_config(काष्ठा i915_perf_stream *stream,
	       काष्ठा i915_oa_config *oa_config,
	       काष्ठा पूर्णांकel_context *ce,
	       काष्ठा i915_active *active)
अणु
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err;

	vma = get_oa_vma(stream, oa_config);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = i915_gem_object_lock(vma->obj, &ww);
	अगर (err)
		जाओ err;

	err = i915_vma_pin_ww(vma, &ww, 0, 0, PIN_GLOBAL | PIN_HIGH);
	अगर (err)
		जाओ err;

	पूर्णांकel_engine_pm_get(ce->engine);
	rq = i915_request_create(ce);
	पूर्णांकel_engine_pm_put(ce->engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_vma_unpin;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(active)) अणु
		/* After all inभागidual context modअगरications */
		err = i915_request_aरुको_active(rq, active,
						I915_ACTIVE_AWAIT_ACTIVE);
		अगर (err)
			जाओ err_add_request;

		err = i915_active_add_request(active, rq);
		अगर (err)
			जाओ err_add_request;
	पूर्ण

	err = i915_request_aरुको_object(rq, vma->obj, 0);
	अगर (!err)
		err = i915_vma_move_to_active(vma, rq, 0);
	अगर (err)
		जाओ err_add_request;

	err = rq->engine->emit_bb_start(rq,
					vma->node.start, 0,
					I915_DISPATCH_SECURE);
	अगर (err)
		जाओ err_add_request;

err_add_request:
	i915_request_add(rq);
err_vma_unpin:
	i915_vma_unpin(vma);
err:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण

	i915_gem_ww_ctx_fini(&ww);
	i915_vma_put(vma);
	वापस err;
पूर्ण

अटल काष्ठा पूर्णांकel_context *oa_context(काष्ठा i915_perf_stream *stream)
अणु
	वापस stream->pinned_ctx ?: stream->engine->kernel_context;
पूर्ण

अटल पूर्णांक
hsw_enable_metric_set(काष्ठा i915_perf_stream *stream,
		      काष्ठा i915_active *active)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	/*
	 * PRM:
	 *
	 * OA unit is using ै crclkै  क्रम its functionality. When trunk
	 * level घड़ी gating takes place, OA घड़ी would be gated,
	 * unable to count the events from non-render घड़ी करोमुख्य.
	 * Render घड़ी gating must be disabled when OA is enabled to
	 * count the events from non-render करोमुख्य. Unit level घड़ी
	 * gating क्रम RCS should also be disabled.
	 */
	पूर्णांकel_uncore_rmw(uncore, GEN7_MISCCPCTL,
			 GEN7_DOP_CLOCK_GATE_ENABLE, 0);
	पूर्णांकel_uncore_rmw(uncore, GEN6_UCGCTL1,
			 0, GEN6_CSUNIT_CLOCK_GATE_DISABLE);

	वापस emit_oa_config(stream,
			      stream->oa_config, oa_context(stream),
			      active);
पूर्ण

अटल व्योम hsw_disable_metric_set(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	पूर्णांकel_uncore_rmw(uncore, GEN6_UCGCTL1,
			 GEN6_CSUNIT_CLOCK_GATE_DISABLE, 0);
	पूर्णांकel_uncore_rmw(uncore, GEN7_MISCCPCTL,
			 0, GEN7_DOP_CLOCK_GATE_ENABLE);

	पूर्णांकel_uncore_rmw(uncore, GDT_CHICKEN_BITS, GT_NOA_ENABLE, 0);
पूर्ण

अटल u32 oa_config_flex_reg(स्थिर काष्ठा i915_oa_config *oa_config,
			      i915_reg_t reg)
अणु
	u32 mmio = i915_mmio_reg_offset(reg);
	पूर्णांक i;

	/*
	 * This arbitrary शेष will select the 'EU FPU0 Pipeline
	 * Active' event. In the future it's anticipated that there
	 * will be an explicit 'No Event' we can select, but not yet...
	 */
	अगर (!oa_config)
		वापस 0;

	क्रम (i = 0; i < oa_config->flex_regs_len; i++) अणु
		अगर (i915_mmio_reg_offset(oa_config->flex_regs[i].addr) == mmio)
			वापस oa_config->flex_regs[i].value;
	पूर्ण

	वापस 0;
पूर्ण
/*
 * NB: It must always reमुख्य poपूर्णांकer safe to run this even अगर the OA unit
 * has been disabled.
 *
 * It's fine to put out-of-date values पूर्णांकo these per-context रेजिस्टरs
 * in the हाल that the OA unit has been disabled.
 */
अटल व्योम
gen8_update_reg_state_unlocked(स्थिर काष्ठा पूर्णांकel_context *ce,
			       स्थिर काष्ठा i915_perf_stream *stream)
अणु
	u32 ctx_oactxctrl = stream->perf->ctx_oactxctrl_offset;
	u32 ctx_flexeu0 = stream->perf->ctx_flexeu0_offset;
	/* The MMIO offsets क्रम Flex EU रेजिस्टरs aren't contiguous */
	i915_reg_t flex_regs[] = अणु
		EU_PERF_CNTL0,
		EU_PERF_CNTL1,
		EU_PERF_CNTL2,
		EU_PERF_CNTL3,
		EU_PERF_CNTL4,
		EU_PERF_CNTL5,
		EU_PERF_CNTL6,
	पूर्ण;
	u32 *reg_state = ce->lrc_reg_state;
	पूर्णांक i;

	reg_state[ctx_oactxctrl + 1] =
		(stream->period_exponent << GEN8_OA_TIMER_PERIOD_SHIFT) |
		(stream->periodic ? GEN8_OA_TIMER_ENABLE : 0) |
		GEN8_OA_COUNTER_RESUME;

	क्रम (i = 0; i < ARRAY_SIZE(flex_regs); i++)
		reg_state[ctx_flexeu0 + i * 2 + 1] =
			oa_config_flex_reg(stream->oa_config, flex_regs[i]);
पूर्ण

काष्ठा flex अणु
	i915_reg_t reg;
	u32 offset;
	u32 value;
पूर्ण;

अटल पूर्णांक
gen8_store_flex(काष्ठा i915_request *rq,
		काष्ठा पूर्णांकel_context *ce,
		स्थिर काष्ठा flex *flex, अचिन्हित पूर्णांक count)
अणु
	u32 offset;
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 4 * count);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	offset = i915_ggtt_offset(ce->state) + LRC_STATE_OFFSET;
	करो अणु
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = offset + flex->offset * माप(u32);
		*cs++ = 0;
		*cs++ = flex->value;
	पूर्ण जबतक (flex++, --count);

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक
gen8_load_flex(काष्ठा i915_request *rq,
	       काष्ठा पूर्णांकel_context *ce,
	       स्थिर काष्ठा flex *flex, अचिन्हित पूर्णांक count)
अणु
	u32 *cs;

	GEM_BUG_ON(!count || count > 63);

	cs = पूर्णांकel_ring_begin(rq, 2 * count + 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(count);
	करो अणु
		*cs++ = i915_mmio_reg_offset(flex->reg);
		*cs++ = flex->value;
	पूर्ण जबतक (flex++, --count);
	*cs++ = MI_NOOP;

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक gen8_modअगरy_context(काष्ठा पूर्णांकel_context *ce,
			       स्थिर काष्ठा flex *flex, अचिन्हित पूर्णांक count)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	rq = पूर्णांकel_engine_create_kernel_request(ce->engine);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	/* Serialise with the remote context */
	err = पूर्णांकel_context_prepare_remote_request(ce, rq);
	अगर (err == 0)
		err = gen8_store_flex(rq, ce, flex, count);

	i915_request_add(rq);
	वापस err;
पूर्ण

अटल पूर्णांक
gen8_modअगरy_self(काष्ठा पूर्णांकel_context *ce,
		 स्थिर काष्ठा flex *flex, अचिन्हित पूर्णांक count,
		 काष्ठा i915_active *active)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	पूर्णांकel_engine_pm_get(ce->engine);
	rq = i915_request_create(ce);
	पूर्णांकel_engine_pm_put(ce->engine);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	अगर (!IS_ERR_OR_शून्य(active)) अणु
		err = i915_active_add_request(active, rq);
		अगर (err)
			जाओ err_add_request;
	पूर्ण

	err = gen8_load_flex(rq, ce, flex, count);
	अगर (err)
		जाओ err_add_request;

err_add_request:
	i915_request_add(rq);
	वापस err;
पूर्ण

अटल पूर्णांक gen8_configure_context(काष्ठा i915_gem_context *ctx,
				  काष्ठा flex *flex, अचिन्हित पूर्णांक count)
अणु
	काष्ठा i915_gem_engines_iter it;
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err = 0;

	क्रम_each_gem_engine(ce, i915_gem_context_lock_engines(ctx), it) अणु
		GEM_BUG_ON(ce == ce->engine->kernel_context);

		अगर (ce->engine->class != RENDER_CLASS)
			जारी;

		/* Otherwise OA settings will be set upon first use */
		अगर (!पूर्णांकel_context_pin_अगर_active(ce))
			जारी;

		flex->value = पूर्णांकel_sseu_make_rpcs(ce->engine->gt, &ce->sseu);
		err = gen8_modअगरy_context(ce, flex, count);

		पूर्णांकel_context_unpin(ce);
		अगर (err)
			अवरोध;
	पूर्ण
	i915_gem_context_unlock_engines(ctx);

	वापस err;
पूर्ण

अटल पूर्णांक gen12_configure_oar_context(काष्ठा i915_perf_stream *stream,
				       काष्ठा i915_active *active)
अणु
	पूर्णांक err;
	काष्ठा पूर्णांकel_context *ce = stream->pinned_ctx;
	u32 क्रमmat = stream->oa_buffer.क्रमmat;
	काष्ठा flex regs_context[] = अणु
		अणु
			GEN8_OACTXCONTROL,
			stream->perf->ctx_oactxctrl_offset + 1,
			active ? GEN8_OA_COUNTER_RESUME : 0,
		पूर्ण,
	पूर्ण;
	/* Offsets in regs_lri are not used since this configuration is only
	 * applied using LRI. Initialize the correct offsets क्रम posterity.
	 */
#घोषणा GEN12_OAR_OACONTROL_OFFSET 0x5B0
	काष्ठा flex regs_lri[] = अणु
		अणु
			GEN12_OAR_OACONTROL,
			GEN12_OAR_OACONTROL_OFFSET + 1,
			(क्रमmat << GEN12_OAR_OACONTROL_COUNTER_FORMAT_SHIFT) |
			(active ? GEN12_OAR_OACONTROL_COUNTER_ENABLE : 0)
		पूर्ण,
		अणु
			RING_CONTEXT_CONTROL(ce->engine->mmio_base),
			CTX_CONTEXT_CONTROL,
			_MASKED_FIELD(GEN12_CTX_CTRL_OAR_CONTEXT_ENABLE,
				      active ?
				      GEN12_CTX_CTRL_OAR_CONTEXT_ENABLE :
				      0)
		पूर्ण,
	पूर्ण;

	/* Modअगरy the context image of pinned context with regs_context*/
	err = पूर्णांकel_context_lock_pinned(ce);
	अगर (err)
		वापस err;

	err = gen8_modअगरy_context(ce, regs_context, ARRAY_SIZE(regs_context));
	पूर्णांकel_context_unlock_pinned(ce);
	अगर (err)
		वापस err;

	/* Apply regs_lri using LRI with pinned context */
	वापस gen8_modअगरy_self(ce, regs_lri, ARRAY_SIZE(regs_lri), active);
पूर्ण

/*
 * Manages updating the per-context aspects of the OA stream
 * configuration across all contexts.
 *
 * The awkward consideration here is that OACTXCONTROL controls the
 * exponent क्रम periodic sampling which is primarily used क्रम प्रणाली
 * wide profiling where we'd like a consistent sampling period even in
 * the face of context चयनes.
 *
 * Our approach of updating the रेजिस्टर state context (as opposed to
 * say using a workaround batch buffer) ensures that the hardware
 * won't स्वतःmatically reload an out-of-date समयr exponent even
 * transiently beक्रमe a WA BB could be parsed.
 *
 * This function needs to:
 * - Ensure the currently running context's per-context OA state is
 *   updated
 * - Ensure that all existing contexts will have the correct per-context
 *   OA state अगर they are scheduled क्रम use.
 * - Ensure any new contexts will be initialized with the correct
 *   per-context OA state.
 *
 * Note: it's only the RCS/Render context that has any OA state.
 * Note: the first flex रेजिस्टर passed must always be R_PWR_CLK_STATE
 */
अटल पूर्णांक
oa_configure_all_contexts(काष्ठा i915_perf_stream *stream,
			  काष्ठा flex *regs,
			  माप_प्रकार num_regs,
			  काष्ठा i915_active *active)
अणु
	काष्ठा drm_i915_निजी *i915 = stream->perf->i915;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_gem_context *ctx, *cn;
	पूर्णांक err;

	lockdep_निश्चित_held(&stream->perf->lock);

	/*
	 * The OA रेजिस्टर config is setup through the context image. This image
	 * might be written to by the GPU on context चयन (in particular on
	 * lite-restore). This means we can't safely update a context's image,
	 * अगर this context is scheduled/submitted to run on the GPU.
	 *
	 * We could emit the OA रेजिस्टर config through the batch buffer but
	 * this might leave small पूर्णांकerval of समय where the OA unit is
	 * configured at an invalid sampling period.
	 *
	 * Note that since we emit all requests from a single ring, there
	 * is still an implicit global barrier here that may cause a high
	 * priority context to रुको क्रम an otherwise independent low priority
	 * context. Contexts idle at the समय of reconfiguration are not
	 * trapped behind the barrier.
	 */
	spin_lock(&i915->gem.contexts.lock);
	list_क्रम_each_entry_safe(ctx, cn, &i915->gem.contexts.list, link) अणु
		अगर (!kref_get_unless_zero(&ctx->ref))
			जारी;

		spin_unlock(&i915->gem.contexts.lock);

		err = gen8_configure_context(ctx, regs, num_regs);
		अगर (err) अणु
			i915_gem_context_put(ctx);
			वापस err;
		पूर्ण

		spin_lock(&i915->gem.contexts.lock);
		list_safe_reset_next(ctx, cn, link);
		i915_gem_context_put(ctx);
	पूर्ण
	spin_unlock(&i915->gem.contexts.lock);

	/*
	 * After updating all other contexts, we need to modअगरy ourselves.
	 * If we करोn't modअगरy the kernel_context, we करो not get events जबतक
	 * idle.
	 */
	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा पूर्णांकel_context *ce = engine->kernel_context;

		अगर (engine->class != RENDER_CLASS)
			जारी;

		regs[0].value = पूर्णांकel_sseu_make_rpcs(engine->gt, &ce->sseu);

		err = gen8_modअगरy_self(ce, regs, num_regs, active);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gen12_configure_all_contexts(काष्ठा i915_perf_stream *stream,
			     स्थिर काष्ठा i915_oa_config *oa_config,
			     काष्ठा i915_active *active)
अणु
	काष्ठा flex regs[] = अणु
		अणु
			GEN8_R_PWR_CLK_STATE,
			CTX_R_PWR_CLK_STATE,
		पूर्ण,
	पूर्ण;

	वापस oa_configure_all_contexts(stream,
					 regs, ARRAY_SIZE(regs),
					 active);
पूर्ण

अटल पूर्णांक
lrc_configure_all_contexts(काष्ठा i915_perf_stream *stream,
			   स्थिर काष्ठा i915_oa_config *oa_config,
			   काष्ठा i915_active *active)
अणु
	/* The MMIO offsets क्रम Flex EU रेजिस्टरs aren't contiguous */
	स्थिर u32 ctx_flexeu0 = stream->perf->ctx_flexeu0_offset;
#घोषणा ctx_flexeuN(N) (ctx_flexeu0 + 2 * (N) + 1)
	काष्ठा flex regs[] = अणु
		अणु
			GEN8_R_PWR_CLK_STATE,
			CTX_R_PWR_CLK_STATE,
		पूर्ण,
		अणु
			GEN8_OACTXCONTROL,
			stream->perf->ctx_oactxctrl_offset + 1,
		पूर्ण,
		अणु EU_PERF_CNTL0, ctx_flexeuN(0) पूर्ण,
		अणु EU_PERF_CNTL1, ctx_flexeuN(1) पूर्ण,
		अणु EU_PERF_CNTL2, ctx_flexeuN(2) पूर्ण,
		अणु EU_PERF_CNTL3, ctx_flexeuN(3) पूर्ण,
		अणु EU_PERF_CNTL4, ctx_flexeuN(4) पूर्ण,
		अणु EU_PERF_CNTL5, ctx_flexeuN(5) पूर्ण,
		अणु EU_PERF_CNTL6, ctx_flexeuN(6) पूर्ण,
	पूर्ण;
#अघोषित ctx_flexeuN
	पूर्णांक i;

	regs[1].value =
		(stream->period_exponent << GEN8_OA_TIMER_PERIOD_SHIFT) |
		(stream->periodic ? GEN8_OA_TIMER_ENABLE : 0) |
		GEN8_OA_COUNTER_RESUME;

	क्रम (i = 2; i < ARRAY_SIZE(regs); i++)
		regs[i].value = oa_config_flex_reg(oa_config, regs[i].reg);

	वापस oa_configure_all_contexts(stream,
					 regs, ARRAY_SIZE(regs),
					 active);
पूर्ण

अटल पूर्णांक
gen8_enable_metric_set(काष्ठा i915_perf_stream *stream,
		       काष्ठा i915_active *active)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	काष्ठा i915_oa_config *oa_config = stream->oa_config;
	पूर्णांक ret;

	/*
	 * We disable slice/unslice घड़ी ratio change reports on SKL since
	 * they are too noisy. The HW generates a lot of redundant reports
	 * where the ratio hasn't really changed causing a lot of redundant
	 * work to processes and increasing the chances we'll hit buffer
	 * overruns.
	 *
	 * Although we करोn't currently use the 'disable overrun' OABUFFER
	 * feature it's worth noting that घड़ी ratio reports have to be
	 * disabled beक्रमe considering to use that feature since the HW करोesn't
	 * correctly block these reports.
	 *
	 * Currently none of the high-level metrics we have depend on knowing
	 * this ratio to normalize.
	 *
	 * Note: This रेजिस्टर is not घातer context saved and restored, but
	 * that's OK considering that we disable RC6 जबतक the OA unit is
	 * enabled.
	 *
	 * The _INCLUDE_CLK_RATIO bit allows the slice/unslice frequency to
	 * be पढ़ो back from स्वतःmatically triggered reports, as part of the
	 * RPT_ID field.
	 */
	अगर (IS_GEN_RANGE(stream->perf->i915, 9, 11)) अणु
		पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_OA_DEBUG,
				   _MASKED_BIT_ENABLE(GEN9_OA_DEBUG_DISABLE_CLK_RATIO_REPORTS |
						      GEN9_OA_DEBUG_INCLUDE_CLK_RATIO));
	पूर्ण

	/*
	 * Update all contexts prior writing the mux configurations as we need
	 * to make sure all slices/subslices are ON beक्रमe writing to NOA
	 * रेजिस्टरs.
	 */
	ret = lrc_configure_all_contexts(stream, oa_config, active);
	अगर (ret)
		वापस ret;

	वापस emit_oa_config(stream,
			      stream->oa_config, oa_context(stream),
			      active);
पूर्ण

अटल u32 oag_report_ctx_चयनes(स्थिर काष्ठा i915_perf_stream *stream)
अणु
	वापस _MASKED_FIELD(GEN12_OAG_OA_DEBUG_DISABLE_CTX_SWITCH_REPORTS,
			     (stream->sample_flags & SAMPLE_OA_REPORT) ?
			     0 : GEN12_OAG_OA_DEBUG_DISABLE_CTX_SWITCH_REPORTS);
पूर्ण

अटल पूर्णांक
gen12_enable_metric_set(काष्ठा i915_perf_stream *stream,
			काष्ठा i915_active *active)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	काष्ठा i915_oa_config *oa_config = stream->oa_config;
	bool periodic = stream->periodic;
	u32 period_exponent = stream->period_exponent;
	पूर्णांक ret;

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OAG_OA_DEBUG,
			   /* Disable clk ratio reports, like previous Gens. */
			   _MASKED_BIT_ENABLE(GEN12_OAG_OA_DEBUG_DISABLE_CLK_RATIO_REPORTS |
					      GEN12_OAG_OA_DEBUG_INCLUDE_CLK_RATIO) |
			   /*
			    * If the user didn't require OA reports, inकाष्ठा
			    * the hardware not to emit ctx चयन reports.
			    */
			   oag_report_ctx_चयनes(stream));

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OAG_OAGLBCTXCTRL, periodic ?
			   (GEN12_OAG_OAGLBCTXCTRL_COUNTER_RESUME |
			    GEN12_OAG_OAGLBCTXCTRL_TIMER_ENABLE |
			    (period_exponent << GEN12_OAG_OAGLBCTXCTRL_TIMER_PERIOD_SHIFT))
			    : 0);

	/*
	 * Update all contexts prior writing the mux configurations as we need
	 * to make sure all slices/subslices are ON beक्रमe writing to NOA
	 * रेजिस्टरs.
	 */
	ret = gen12_configure_all_contexts(stream, oa_config, active);
	अगर (ret)
		वापस ret;

	/*
	 * For Gen12, perक्रमmance counters are context
	 * saved/restored. Only enable it क्रम the context that
	 * requested this.
	 */
	अगर (stream->ctx) अणु
		ret = gen12_configure_oar_context(stream, active);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस emit_oa_config(stream,
			      stream->oa_config, oa_context(stream),
			      active);
पूर्ण

अटल व्योम gen8_disable_metric_set(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	/* Reset all contexts' slices/subslices configurations. */
	lrc_configure_all_contexts(stream, शून्य, शून्य);

	पूर्णांकel_uncore_rmw(uncore, GDT_CHICKEN_BITS, GT_NOA_ENABLE, 0);
पूर्ण

अटल व्योम gen10_disable_metric_set(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	/* Reset all contexts' slices/subslices configurations. */
	lrc_configure_all_contexts(stream, शून्य, शून्य);

	/* Make sure we disable noa to save घातer. */
	पूर्णांकel_uncore_rmw(uncore, RPM_CONFIG1, GEN10_GT_NOA_ENABLE, 0);
पूर्ण

अटल व्योम gen12_disable_metric_set(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	/* Reset all contexts' slices/subslices configurations. */
	gen12_configure_all_contexts(stream, शून्य, शून्य);

	/* disable the context save/restore or OAR counters */
	अगर (stream->ctx)
		gen12_configure_oar_context(stream, शून्य);

	/* Make sure we disable noa to save घातer. */
	पूर्णांकel_uncore_rmw(uncore, RPM_CONFIG1, GEN10_GT_NOA_ENABLE, 0);
पूर्ण

अटल व्योम gen7_oa_enable(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	काष्ठा i915_gem_context *ctx = stream->ctx;
	u32 ctx_id = stream->specअगरic_ctx_id;
	bool periodic = stream->periodic;
	u32 period_exponent = stream->period_exponent;
	u32 report_क्रमmat = stream->oa_buffer.क्रमmat;

	/*
	 * Reset buf poपूर्णांकers so we करोn't क्रमward reports from beक्रमe now.
	 *
	 * Think carefully अगर considering trying to aव्योम this, since it
	 * also ensures status flags and the buffer itself are cleared
	 * in error paths, and we have checks क्रम invalid reports based
	 * on the assumption that certain fields are written to zeroed
	 * memory which this helps मुख्यtains.
	 */
	gen7_init_oa_buffer(stream);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_OACONTROL,
			   (ctx_id & GEN7_OACONTROL_CTX_MASK) |
			   (period_exponent <<
			    GEN7_OACONTROL_TIMER_PERIOD_SHIFT) |
			   (periodic ? GEN7_OACONTROL_TIMER_ENABLE : 0) |
			   (report_क्रमmat << GEN7_OACONTROL_FORMAT_SHIFT) |
			   (ctx ? GEN7_OACONTROL_PER_CTX_ENABLE : 0) |
			   GEN7_OACONTROL_ENABLE);
पूर्ण

अटल व्योम gen8_oa_enable(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	u32 report_क्रमmat = stream->oa_buffer.क्रमmat;

	/*
	 * Reset buf poपूर्णांकers so we करोn't क्रमward reports from beक्रमe now.
	 *
	 * Think carefully अगर considering trying to aव्योम this, since it
	 * also ensures status flags and the buffer itself are cleared
	 * in error paths, and we have checks क्रम invalid reports based
	 * on the assumption that certain fields are written to zeroed
	 * memory which this helps मुख्यtains.
	 */
	gen8_init_oa_buffer(stream);

	/*
	 * Note: we करोn't rely on the hardware to perक्रमm single context
	 * filtering and instead filter on the cpu based on the context-id
	 * field of reports
	 */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_OACONTROL,
			   (report_क्रमmat << GEN8_OA_REPORT_FORMAT_SHIFT) |
			   GEN8_OA_COUNTER_ENABLE);
पूर्ण

अटल व्योम gen12_oa_enable(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;
	u32 report_क्रमmat = stream->oa_buffer.क्रमmat;

	/*
	 * If we करोn't want OA reports from the OA buffer, then we don't even
	 * need to program the OAG unit.
	 */
	अगर (!(stream->sample_flags & SAMPLE_OA_REPORT))
		वापस;

	gen12_init_oa_buffer(stream);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OAG_OACONTROL,
			   (report_क्रमmat << GEN12_OAG_OACONTROL_OA_COUNTER_FORMAT_SHIFT) |
			   GEN12_OAG_OACONTROL_OA_COUNTER_ENABLE);
पूर्ण

/**
 * i915_oa_stream_enable - handle `I915_PERF_IOCTL_ENABLE` क्रम OA stream
 * @stream: An i915 perf stream खोलोed क्रम OA metrics
 *
 * [Re]enables hardware periodic sampling according to the period configured
 * when खोलोing the stream. This also starts a hrसमयr that will periodically
 * check क्रम data in the circular OA buffer क्रम notअगरying userspace (e.g.
 * during a पढ़ो() or poll()).
 */
अटल व्योम i915_oa_stream_enable(काष्ठा i915_perf_stream *stream)
अणु
	stream->pollin = false;

	stream->perf->ops.oa_enable(stream);

	अगर (stream->sample_flags & SAMPLE_OA_REPORT)
		hrसमयr_start(&stream->poll_check_समयr,
			      ns_to_kसमय(stream->poll_oa_period),
			      HRTIMER_MODE_REL_PINNED);
पूर्ण

अटल व्योम gen7_oa_disable(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_OACONTROL, 0);
	अगर (पूर्णांकel_रुको_क्रम_रेजिस्टर(uncore,
				    GEN7_OACONTROL, GEN7_OACONTROL_ENABLE, 0,
				    50))
		drm_err(&stream->perf->i915->drm,
			"wait for OA to be disabled timed out\n");
पूर्ण

अटल व्योम gen8_oa_disable(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_OACONTROL, 0);
	अगर (पूर्णांकel_रुको_क्रम_रेजिस्टर(uncore,
				    GEN8_OACONTROL, GEN8_OA_COUNTER_ENABLE, 0,
				    50))
		drm_err(&stream->perf->i915->drm,
			"wait for OA to be disabled timed out\n");
पूर्ण

अटल व्योम gen12_oa_disable(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = stream->uncore;

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OAG_OACONTROL, 0);
	अगर (पूर्णांकel_रुको_क्रम_रेजिस्टर(uncore,
				    GEN12_OAG_OACONTROL,
				    GEN12_OAG_OACONTROL_OA_COUNTER_ENABLE, 0,
				    50))
		drm_err(&stream->perf->i915->drm,
			"wait for OA to be disabled timed out\n");

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_OA_TLB_INV_CR, 1);
	अगर (पूर्णांकel_रुको_क्रम_रेजिस्टर(uncore,
				    GEN12_OA_TLB_INV_CR,
				    1, 0,
				    50))
		drm_err(&stream->perf->i915->drm,
			"wait for OA tlb invalidate timed out\n");
पूर्ण

/**
 * i915_oa_stream_disable - handle `I915_PERF_IOCTL_DISABLE` क्रम OA stream
 * @stream: An i915 perf stream खोलोed क्रम OA metrics
 *
 * Stops the OA unit from periodically writing counter reports पूर्णांकo the
 * circular OA buffer. This also stops the hrसमयr that periodically checks क्रम
 * data in the circular OA buffer, क्रम notअगरying userspace.
 */
अटल व्योम i915_oa_stream_disable(काष्ठा i915_perf_stream *stream)
अणु
	stream->perf->ops.oa_disable(stream);

	अगर (stream->sample_flags & SAMPLE_OA_REPORT)
		hrसमयr_cancel(&stream->poll_check_समयr);
पूर्ण

अटल स्थिर काष्ठा i915_perf_stream_ops i915_oa_stream_ops = अणु
	.destroy = i915_oa_stream_destroy,
	.enable = i915_oa_stream_enable,
	.disable = i915_oa_stream_disable,
	.रुको_unlocked = i915_oa_रुको_unlocked,
	.poll_रुको = i915_oa_poll_रुको,
	.पढ़ो = i915_oa_पढ़ो,
पूर्ण;

अटल पूर्णांक i915_perf_stream_enable_sync(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा i915_active *active;
	पूर्णांक err;

	active = i915_active_create();
	अगर (!active)
		वापस -ENOMEM;

	err = stream->perf->ops.enable_metric_set(stream, active);
	अगर (err == 0)
		__i915_active_रुको(active, TASK_UNINTERRUPTIBLE);

	i915_active_put(active);
	वापस err;
पूर्ण

अटल व्योम
get_शेष_sseu_config(काष्ठा पूर्णांकel_sseu *out_sseu,
			काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर काष्ठा sseu_dev_info *devinfo_sseu = &engine->gt->info.sseu;

	*out_sseu = पूर्णांकel_sseu_from_device_info(devinfo_sseu);

	अगर (IS_GEN(engine->i915, 11)) अणु
		/*
		 * We only need subslice count so it करोesn't matter which ones
		 * we select - just turn off low bits in the amount of half of
		 * all available subslices per slice.
		 */
		out_sseu->subslice_mask =
			~(~0 << (hweight8(out_sseu->subslice_mask) / 2));
		out_sseu->slice_mask = 0x1;
	पूर्ण
पूर्ण

अटल पूर्णांक
get_sseu_config(काष्ठा पूर्णांकel_sseu *out_sseu,
		काष्ठा पूर्णांकel_engine_cs *engine,
		स्थिर काष्ठा drm_i915_gem_context_param_sseu *drm_sseu)
अणु
	अगर (drm_sseu->engine.engine_class != engine->uabi_class ||
	    drm_sseu->engine.engine_instance != engine->uabi_instance)
		वापस -EINVAL;

	वापस i915_gem_user_to_context_sseu(engine->gt, drm_sseu, out_sseu);
पूर्ण

/**
 * i915_oa_stream_init - validate combined props क्रम OA stream and init
 * @stream: An i915 perf stream
 * @param: The खोलो parameters passed to `DRM_I915_PERF_OPEN`
 * @props: The property state that configures stream (inभागidually validated)
 *
 * While पढ़ो_properties_unlocked() validates properties in isolation it
 * करोesn't ensure that the combination necessarily makes sense.
 *
 * At this poपूर्णांक it has been determined that userspace wants a stream of
 * OA metrics, but still we need to further validate the combined
 * properties are OK.
 *
 * If the configuration makes sense then we can allocate memory क्रम
 * a circular OA buffer and apply the requested metric set configuration.
 *
 * Returns: zero on success or a negative error code.
 */
अटल पूर्णांक i915_oa_stream_init(काष्ठा i915_perf_stream *stream,
			       काष्ठा drm_i915_perf_खोलो_param *param,
			       काष्ठा perf_खोलो_properties *props)
अणु
	काष्ठा drm_i915_निजी *i915 = stream->perf->i915;
	काष्ठा i915_perf *perf = stream->perf;
	पूर्णांक क्रमmat_size;
	पूर्णांक ret;

	अगर (!props->engine) अणु
		DRM_DEBUG("OA engine not specified\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * If the sysfs metrics/ directory wasn't रेजिस्टरed क्रम some
	 * reason then करोn't let userspace try their luck with config
	 * IDs
	 */
	अगर (!perf->metrics_kobj) अणु
		DRM_DEBUG("OA metrics weren't advertised via sysfs\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(props->sample_flags & SAMPLE_OA_REPORT) &&
	    (INTEL_GEN(perf->i915) < 12 || !stream->ctx)) अणु
		DRM_DEBUG("Only OA report sampling supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!perf->ops.enable_metric_set) अणु
		DRM_DEBUG("OA unit not supported\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * To aव्योम the complनिकासy of having to accurately filter
	 * counter reports and marshal to the appropriate client
	 * we currently only allow exclusive access
	 */
	अगर (perf->exclusive_stream) अणु
		DRM_DEBUG("OA unit already in use\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!props->oa_क्रमmat) अणु
		DRM_DEBUG("OA report format not specified\n");
		वापस -EINVAL;
	पूर्ण

	stream->engine = props->engine;
	stream->uncore = stream->engine->gt->uncore;

	stream->sample_size = माप(काष्ठा drm_i915_perf_record_header);

	क्रमmat_size = perf->oa_क्रमmats[props->oa_क्रमmat].size;

	stream->sample_flags = props->sample_flags;
	stream->sample_size += क्रमmat_size;

	stream->oa_buffer.क्रमmat_size = क्रमmat_size;
	अगर (drm_WARN_ON(&i915->drm, stream->oa_buffer.क्रमmat_size == 0))
		वापस -EINVAL;

	stream->hold_preemption = props->hold_preemption;

	stream->oa_buffer.क्रमmat =
		perf->oa_क्रमmats[props->oa_क्रमmat].क्रमmat;

	stream->periodic = props->oa_periodic;
	अगर (stream->periodic)
		stream->period_exponent = props->oa_period_exponent;

	अगर (stream->ctx) अणु
		ret = oa_get_render_ctx_id(stream);
		अगर (ret) अणु
			DRM_DEBUG("Invalid context id to filter with\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = alloc_noa_रुको(stream);
	अगर (ret) अणु
		DRM_DEBUG("Unable to allocate NOA wait batch buffer\n");
		जाओ err_noa_रुको_alloc;
	पूर्ण

	stream->oa_config = i915_perf_get_oa_config(perf, props->metrics_set);
	अगर (!stream->oa_config) अणु
		DRM_DEBUG("Invalid OA config id=%i\n", props->metrics_set);
		ret = -EINVAL;
		जाओ err_config;
	पूर्ण

	/* PRM - observability perक्रमmance counters:
	 *
	 *   OACONTROL, perक्रमmance counter enable, note:
	 *
	 *   "When this bit is set, in order to have coherent counts,
	 *   RC6 घातer state and trunk घड़ी gating must be disabled.
	 *   This can be achieved by programming MMIO रेजिस्टरs as
	 *   0xA094=0 and 0xA090[31]=1"
	 *
	 *   In our हाल we are expecting that taking pm + FORCEWAKE
	 *   references will effectively disable RC6.
	 */
	पूर्णांकel_engine_pm_get(stream->engine);
	पूर्णांकel_uncore_क्रमcewake_get(stream->uncore, FORCEWAKE_ALL);

	ret = alloc_oa_buffer(stream);
	अगर (ret)
		जाओ err_oa_buf_alloc;

	stream->ops = &i915_oa_stream_ops;

	perf->sseu = props->sseu;
	WRITE_ONCE(perf->exclusive_stream, stream);

	ret = i915_perf_stream_enable_sync(stream);
	अगर (ret) अणु
		DRM_DEBUG("Unable to enable metric set\n");
		जाओ err_enable;
	पूर्ण

	DRM_DEBUG("opening stream oa config uuid=%s\n",
		  stream->oa_config->uuid);

	hrसमयr_init(&stream->poll_check_समयr,
		     CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	stream->poll_check_समयr.function = oa_poll_check_समयr_cb;
	init_रुकोqueue_head(&stream->poll_wq);
	spin_lock_init(&stream->oa_buffer.ptr_lock);

	वापस 0;

err_enable:
	WRITE_ONCE(perf->exclusive_stream, शून्य);
	perf->ops.disable_metric_set(stream);

	मुक्त_oa_buffer(stream);

err_oa_buf_alloc:
	मुक्त_oa_configs(stream);

	पूर्णांकel_uncore_क्रमcewake_put(stream->uncore, FORCEWAKE_ALL);
	पूर्णांकel_engine_pm_put(stream->engine);

err_config:
	मुक्त_noa_रुको(stream);

err_noa_रुको_alloc:
	अगर (stream->ctx)
		oa_put_render_ctx_id(stream);

	वापस ret;
पूर्ण

व्योम i915_oa_init_reg_state(स्थिर काष्ठा पूर्णांकel_context *ce,
			    स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_perf_stream *stream;

	अगर (engine->class != RENDER_CLASS)
		वापस;

	/* perf.exclusive_stream serialised by lrc_configure_all_contexts() */
	stream = READ_ONCE(engine->i915->perf.exclusive_stream);
	अगर (stream && INTEL_GEN(stream->perf->i915) < 12)
		gen8_update_reg_state_unlocked(ce, stream);
पूर्ण

/**
 * i915_perf_पढ़ो - handles पढ़ो() FOP क्रम i915 perf stream FDs
 * @file: An i915 perf stream file
 * @buf: destination buffer given by userspace
 * @count: the number of bytes userspace wants to पढ़ो
 * @ppos: (inout) file seek position (unused)
 *
 * The entry poपूर्णांक क्रम handling a पढ़ो() on a stream file descriptor from
 * userspace. Most of the work is left to the i915_perf_पढ़ो_locked() and
 * &i915_perf_stream_ops->पढ़ो but to save having stream implementations (of
 * which we might have multiple later) we handle blocking पढ़ो here.
 *
 * We can also consistently treat trying to पढ़ो from a disabled stream
 * as an IO error so implementations can assume the stream is enabled
 * जबतक पढ़ोing.
 *
 * Returns: The number of bytes copied or a negative error code on failure.
 */
अटल sमाप_प्रकार i915_perf_पढ़ो(काष्ठा file *file,
			      अक्षर __user *buf,
			      माप_प्रकार count,
			      loff_t *ppos)
अणु
	काष्ठा i915_perf_stream *stream = file->निजी_data;
	काष्ठा i915_perf *perf = stream->perf;
	माप_प्रकार offset = 0;
	पूर्णांक ret;

	/* To ensure it's handled consistently we simply treat all पढ़ोs of a
	 * disabled stream as an error. In particular it might otherwise lead
	 * to a deadlock क्रम blocking file descriptors...
	 */
	अगर (!stream->enabled || !(stream->sample_flags & SAMPLE_OA_REPORT))
		वापस -EIO;

	अगर (!(file->f_flags & O_NONBLOCK)) अणु
		/* There's the small chance of false positives from
		 * stream->ops->रुको_unlocked.
		 *
		 * E.g. with single context filtering since we only रुको until
		 * oabuffer has >= 1 report we करोn't immediately know whether
		 * any reports really beदीर्घ to the current context
		 */
		करो अणु
			ret = stream->ops->रुको_unlocked(stream);
			अगर (ret)
				वापस ret;

			mutex_lock(&perf->lock);
			ret = stream->ops->पढ़ो(stream, buf, count, &offset);
			mutex_unlock(&perf->lock);
		पूर्ण जबतक (!offset && !ret);
	पूर्ण अन्यथा अणु
		mutex_lock(&perf->lock);
		ret = stream->ops->पढ़ो(stream, buf, count, &offset);
		mutex_unlock(&perf->lock);
	पूर्ण

	/* We allow the poll checking to someबार report false positive EPOLLIN
	 * events where we might actually report EAGAIN on पढ़ो() अगर there's
	 * not really any data available. In this situation though we करोn't
	 * want to enter a busy loop between poll() reporting a EPOLLIN event
	 * and पढ़ो() वापसing -EAGAIN. Clearing the oa.pollin state here
	 * effectively ensures we back off until the next hrसमयr callback
	 * beक्रमe reporting another EPOLLIN event.
	 * The exception to this is अगर ops->पढ़ो() वापसed -ENOSPC which means
	 * that more OA data is available than could fit in the user provided
	 * buffer. In this हाल we want the next poll() call to not block.
	 */
	अगर (ret != -ENOSPC)
		stream->pollin = false;

	/* Possible values क्रम ret are 0, -EFAULT, -ENOSPC, -EIO, ... */
	वापस offset ?: (ret ?: -EAGAIN);
पूर्ण

अटल क्रमागत hrसमयr_restart oa_poll_check_समयr_cb(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा i915_perf_stream *stream =
		container_of(hrसमयr, typeof(*stream), poll_check_समयr);

	अगर (oa_buffer_check_unlocked(stream)) अणु
		stream->pollin = true;
		wake_up(&stream->poll_wq);
	पूर्ण

	hrसमयr_क्रमward_now(hrसमयr,
			    ns_to_kसमय(stream->poll_oa_period));

	वापस HRTIMER_RESTART;
पूर्ण

/**
 * i915_perf_poll_locked - poll_रुको() with a suitable रुको queue क्रम stream
 * @stream: An i915 perf stream
 * @file: An i915 perf stream file
 * @रुको: poll() state table
 *
 * For handling userspace polling on an i915 perf stream, this calls through to
 * &i915_perf_stream_ops->poll_रुको to call poll_रुको() with a रुको queue that
 * will be woken क्रम new stream data.
 *
 * Note: The &perf->lock mutex has been taken to serialize
 * with any non-file-operation driver hooks.
 *
 * Returns: any poll events that are पढ़ोy without sleeping
 */
अटल __poll_t i915_perf_poll_locked(काष्ठा i915_perf_stream *stream,
				      काष्ठा file *file,
				      poll_table *रुको)
अणु
	__poll_t events = 0;

	stream->ops->poll_रुको(stream, file, रुको);

	/* Note: we करोn't explicitly check whether there's something to पढ़ो
	 * here since this path may be very hot depending on what अन्यथा
	 * userspace is polling, or on the समयout in use. We rely solely on
	 * the hrसमयr/oa_poll_check_समयr_cb to notअगरy us when there are
	 * samples to पढ़ो.
	 */
	अगर (stream->pollin)
		events |= EPOLLIN;

	वापस events;
पूर्ण

/**
 * i915_perf_poll - call poll_रुको() with a suitable रुको queue क्रम stream
 * @file: An i915 perf stream file
 * @रुको: poll() state table
 *
 * For handling userspace polling on an i915 perf stream, this ensures
 * poll_रुको() माला_लो called with a रुको queue that will be woken क्रम new stream
 * data.
 *
 * Note: Implementation deferred to i915_perf_poll_locked()
 *
 * Returns: any poll events that are पढ़ोy without sleeping
 */
अटल __poll_t i915_perf_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा i915_perf_stream *stream = file->निजी_data;
	काष्ठा i915_perf *perf = stream->perf;
	__poll_t ret;

	mutex_lock(&perf->lock);
	ret = i915_perf_poll_locked(stream, file, रुको);
	mutex_unlock(&perf->lock);

	वापस ret;
पूर्ण

/**
 * i915_perf_enable_locked - handle `I915_PERF_IOCTL_ENABLE` ioctl
 * @stream: A disabled i915 perf stream
 *
 * [Re]enables the associated capture of data क्रम this stream.
 *
 * If a stream was previously enabled then there's currently no पूर्णांकention
 * to provide userspace any guarantee about the preservation of previously
 * buffered data.
 */
अटल व्योम i915_perf_enable_locked(काष्ठा i915_perf_stream *stream)
अणु
	अगर (stream->enabled)
		वापस;

	/* Allow stream->ops->enable() to refer to this */
	stream->enabled = true;

	अगर (stream->ops->enable)
		stream->ops->enable(stream);

	अगर (stream->hold_preemption)
		पूर्णांकel_context_set_nopreempt(stream->pinned_ctx);
पूर्ण

/**
 * i915_perf_disable_locked - handle `I915_PERF_IOCTL_DISABLE` ioctl
 * @stream: An enabled i915 perf stream
 *
 * Disables the associated capture of data क्रम this stream.
 *
 * The पूर्णांकention is that disabling an re-enabling a stream will ideally be
 * cheaper than destroying and re-खोलोing a stream with the same configuration,
 * though there are no क्रमmal guarantees about what state or buffered data
 * must be retained between disabling and re-enabling a stream.
 *
 * Note: जबतक a stream is disabled it's considered an error क्रम userspace
 * to attempt to पढ़ो from the stream (-EIO).
 */
अटल व्योम i915_perf_disable_locked(काष्ठा i915_perf_stream *stream)
अणु
	अगर (!stream->enabled)
		वापस;

	/* Allow stream->ops->disable() to refer to this */
	stream->enabled = false;

	अगर (stream->hold_preemption)
		पूर्णांकel_context_clear_nopreempt(stream->pinned_ctx);

	अगर (stream->ops->disable)
		stream->ops->disable(stream);
पूर्ण

अटल दीर्घ i915_perf_config_locked(काष्ठा i915_perf_stream *stream,
				    अचिन्हित दीर्घ metrics_set)
अणु
	काष्ठा i915_oa_config *config;
	दीर्घ ret = stream->oa_config->id;

	config = i915_perf_get_oa_config(stream->perf, metrics_set);
	अगर (!config)
		वापस -EINVAL;

	अगर (config != stream->oa_config) अणु
		पूर्णांक err;

		/*
		 * If OA is bound to a specअगरic context, emit the
		 * reconfiguration अंतरभूत from that context. The update
		 * will then be ordered with respect to submission on that
		 * context.
		 *
		 * When set globally, we use a low priority kernel context,
		 * so it will effectively take effect when idle.
		 */
		err = emit_oa_config(stream, config, oa_context(stream), शून्य);
		अगर (!err)
			config = xchg(&stream->oa_config, config);
		अन्यथा
			ret = err;
	पूर्ण

	i915_oa_config_put(config);

	वापस ret;
पूर्ण

/**
 * i915_perf_ioctl_locked - support ioctl() usage with i915 perf stream FDs
 * @stream: An i915 perf stream
 * @cmd: the ioctl request
 * @arg: the ioctl data
 *
 * Note: The &perf->lock mutex has been taken to serialize
 * with any non-file-operation driver hooks.
 *
 * Returns: zero on success or a negative error code. Returns -EINVAL क्रम
 * an unknown ioctl request.
 */
अटल दीर्घ i915_perf_ioctl_locked(काष्ठा i915_perf_stream *stream,
				   अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल I915_PERF_IOCTL_ENABLE:
		i915_perf_enable_locked(stream);
		वापस 0;
	हाल I915_PERF_IOCTL_DISABLE:
		i915_perf_disable_locked(stream);
		वापस 0;
	हाल I915_PERF_IOCTL_CONFIG:
		वापस i915_perf_config_locked(stream, arg);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * i915_perf_ioctl - support ioctl() usage with i915 perf stream FDs
 * @file: An i915 perf stream file
 * @cmd: the ioctl request
 * @arg: the ioctl data
 *
 * Implementation deferred to i915_perf_ioctl_locked().
 *
 * Returns: zero on success or a negative error code. Returns -EINVAL क्रम
 * an unknown ioctl request.
 */
अटल दीर्घ i915_perf_ioctl(काष्ठा file *file,
			    अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा i915_perf_stream *stream = file->निजी_data;
	काष्ठा i915_perf *perf = stream->perf;
	दीर्घ ret;

	mutex_lock(&perf->lock);
	ret = i915_perf_ioctl_locked(stream, cmd, arg);
	mutex_unlock(&perf->lock);

	वापस ret;
पूर्ण

/**
 * i915_perf_destroy_locked - destroy an i915 perf stream
 * @stream: An i915 perf stream
 *
 * Frees all resources associated with the given i915 perf @stream, disabling
 * any associated data capture in the process.
 *
 * Note: The &perf->lock mutex has been taken to serialize
 * with any non-file-operation driver hooks.
 */
अटल व्योम i915_perf_destroy_locked(काष्ठा i915_perf_stream *stream)
अणु
	अगर (stream->enabled)
		i915_perf_disable_locked(stream);

	अगर (stream->ops->destroy)
		stream->ops->destroy(stream);

	अगर (stream->ctx)
		i915_gem_context_put(stream->ctx);

	kमुक्त(stream);
पूर्ण

/**
 * i915_perf_release - handles userspace बंद() of a stream file
 * @inode: anonymous inode associated with file
 * @file: An i915 perf stream file
 *
 * Cleans up any resources associated with an खोलो i915 perf stream file.
 *
 * NB: बंद() can't really fail from the userspace poपूर्णांक of view.
 *
 * Returns: zero on success or a negative error code.
 */
अटल पूर्णांक i915_perf_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा i915_perf_stream *stream = file->निजी_data;
	काष्ठा i915_perf *perf = stream->perf;

	mutex_lock(&perf->lock);
	i915_perf_destroy_locked(stream);
	mutex_unlock(&perf->lock);

	/* Release the reference the perf stream kept on the driver. */
	drm_dev_put(&perf->i915->drm);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.release	= i915_perf_release,
	.poll		= i915_perf_poll,
	.पढ़ो		= i915_perf_पढ़ो,
	.unlocked_ioctl	= i915_perf_ioctl,
	/* Our ioctl have no arguments, so it's safe to use the same function
	 * to handle 32bits compatibility.
	 */
	.compat_ioctl   = i915_perf_ioctl,
पूर्ण;


/**
 * i915_perf_खोलो_ioctl_locked - DRM ioctl() क्रम userspace to खोलो a stream FD
 * @perf: i915 perf instance
 * @param: The खोलो parameters passed to 'DRM_I915_PERF_OPEN`
 * @props: inभागidually validated u64 property value pairs
 * @file: drm file
 *
 * See i915_perf_ioctl_खोलो() क्रम पूर्णांकerface details.
 *
 * Implements further stream config validation and stream initialization on
 * behalf of i915_perf_खोलो_ioctl() with the &perf->lock mutex
 * taken to serialize with any non-file-operation driver hooks.
 *
 * Note: at this poपूर्णांक the @props have only been validated in isolation and
 * it's still necessary to validate that the combination of properties makes
 * sense.
 *
 * In the हाल where userspace is पूर्णांकerested in OA unit metrics then further
 * config validation and stream initialization details will be handled by
 * i915_oa_stream_init(). The code here should only validate config state that
 * will be relevant to all stream types / backends.
 *
 * Returns: zero on success or a negative error code.
 */
अटल पूर्णांक
i915_perf_खोलो_ioctl_locked(काष्ठा i915_perf *perf,
			    काष्ठा drm_i915_perf_खोलो_param *param,
			    काष्ठा perf_खोलो_properties *props,
			    काष्ठा drm_file *file)
अणु
	काष्ठा i915_gem_context *specअगरic_ctx = शून्य;
	काष्ठा i915_perf_stream *stream = शून्य;
	अचिन्हित दीर्घ f_flags = 0;
	bool privileged_op = true;
	पूर्णांक stream_fd;
	पूर्णांक ret;

	अगर (props->single_context) अणु
		u32 ctx_handle = props->ctx_handle;
		काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;

		specअगरic_ctx = i915_gem_context_lookup(file_priv, ctx_handle);
		अगर (!specअगरic_ctx) अणु
			DRM_DEBUG("Failed to look up context with ID %u for opening perf stream\n",
				  ctx_handle);
			ret = -ENOENT;
			जाओ err;
		पूर्ण
	पूर्ण

	/*
	 * On Haswell the OA unit supports घड़ी gating off क्रम a specअगरic
	 * context and in this mode there's no visibility of metrics क्रम the
	 * rest of the प्रणाली, which we consider acceptable क्रम a
	 * non-privileged client.
	 *
	 * For Gen8->11 the OA unit no दीर्घer supports घड़ी gating off क्रम a
	 * specअगरic context and the kernel can't securely stop the counters
	 * from updating as प्रणाली-wide / global values. Even though we can
	 * filter reports based on the included context ID we can't block
	 * clients from seeing the raw / global counter values via
	 * MI_REPORT_PERF_COUNT commands and so consider it a privileged op to
	 * enable the OA unit by शेष.
	 *
	 * For Gen12+ we gain a new OAR unit that only monitors the RCS on a
	 * per context basis. So we can relax requirements there अगर the user
	 * करोesn't request global stream access (i.e. query based sampling
	 * using MI_RECORD_PERF_COUNT.
	 */
	अगर (IS_HASWELL(perf->i915) && specअगरic_ctx)
		privileged_op = false;
	अन्यथा अगर (IS_GEN(perf->i915, 12) && specअगरic_ctx &&
		 (props->sample_flags & SAMPLE_OA_REPORT) == 0)
		privileged_op = false;

	अगर (props->hold_preemption) अणु
		अगर (!props->single_context) अणु
			DRM_DEBUG("preemption disable with no context\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		privileged_op = true;
	पूर्ण

	/*
	 * Asking क्रम SSEU configuration is a priviliged operation.
	 */
	अगर (props->has_sseu)
		privileged_op = true;
	अन्यथा
		get_शेष_sseu_config(&props->sseu, props->engine);

	/* Similar to perf's kernel.perf_paranoid_cpu sysctl option
	 * we check a dev.i915.perf_stream_paranoid sysctl option
	 * to determine अगर it's ok to access प्रणाली wide OA counters
	 * without CAP_PERFMON or CAP_SYS_ADMIN privileges.
	 */
	अगर (privileged_op &&
	    i915_perf_stream_paranoid && !perfmon_capable()) अणु
		DRM_DEBUG("Insufficient privileges to open i915 perf stream\n");
		ret = -EACCES;
		जाओ err_ctx;
	पूर्ण

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream) अणु
		ret = -ENOMEM;
		जाओ err_ctx;
	पूर्ण

	stream->perf = perf;
	stream->ctx = specअगरic_ctx;
	stream->poll_oa_period = props->poll_oa_period;

	ret = i915_oa_stream_init(stream, param, props);
	अगर (ret)
		जाओ err_alloc;

	/* we aव्योम simply assigning stream->sample_flags = props->sample_flags
	 * to have _stream_init check the combination of sample flags more
	 * thoroughly, but still this is the expected result at this poपूर्णांक.
	 */
	अगर (WARN_ON(stream->sample_flags != props->sample_flags)) अणु
		ret = -ENODEV;
		जाओ err_flags;
	पूर्ण

	अगर (param->flags & I915_PERF_FLAG_FD_CLOEXEC)
		f_flags |= O_CLOEXEC;
	अगर (param->flags & I915_PERF_FLAG_FD_NONBLOCK)
		f_flags |= O_NONBLOCK;

	stream_fd = anon_inode_getfd("[i915_perf]", &fops, stream, f_flags);
	अगर (stream_fd < 0) अणु
		ret = stream_fd;
		जाओ err_flags;
	पूर्ण

	अगर (!(param->flags & I915_PERF_FLAG_DISABLED))
		i915_perf_enable_locked(stream);

	/* Take a reference on the driver that will be kept with stream_fd
	 * until its release.
	 */
	drm_dev_get(&perf->i915->drm);

	वापस stream_fd;

err_flags:
	अगर (stream->ops->destroy)
		stream->ops->destroy(stream);
err_alloc:
	kमुक्त(stream);
err_ctx:
	अगर (specअगरic_ctx)
		i915_gem_context_put(specअगरic_ctx);
err:
	वापस ret;
पूर्ण

अटल u64 oa_exponent_to_ns(काष्ठा i915_perf *perf, पूर्णांक exponent)
अणु
	वापस पूर्णांकel_gt_घड़ी_पूर्णांकerval_to_ns(perf->i915->ggtt.vm.gt,
					     2ULL << exponent);
पूर्ण

अटल __always_अंतरभूत bool
oa_क्रमmat_valid(काष्ठा i915_perf *perf, क्रमागत drm_i915_oa_क्रमmat क्रमmat)
अणु
	वापस test_bit(क्रमmat, perf->क्रमmat_mask);
पूर्ण

अटल __always_अंतरभूत व्योम
oa_क्रमmat_add(काष्ठा i915_perf *perf, क्रमागत drm_i915_oa_क्रमmat क्रमmat)
अणु
	__set_bit(क्रमmat, perf->क्रमmat_mask);
पूर्ण

/**
 * पढ़ो_properties_unlocked - validate + copy userspace stream खोलो properties
 * @perf: i915 perf instance
 * @uprops: The array of u64 key value pairs given by userspace
 * @n_props: The number of key value pairs expected in @uprops
 * @props: The stream configuration built up जबतक validating properties
 *
 * Note this function only validates properties in isolation it करोesn't
 * validate that the combination of properties makes sense or that all
 * properties necessary क्रम a particular kind of stream have been set.
 *
 * Note that there currently aren't any ordering requirements क्रम properties so
 * we shouldn't validate or assume anything about ordering here. This doesn't
 * rule out defining new properties with ordering requirements in the future.
 */
अटल पूर्णांक पढ़ो_properties_unlocked(काष्ठा i915_perf *perf,
				    u64 __user *uprops,
				    u32 n_props,
				    काष्ठा perf_खोलो_properties *props)
अणु
	u64 __user *uprop = uprops;
	u32 i;
	पूर्णांक ret;

	स_रखो(props, 0, माप(काष्ठा perf_खोलो_properties));
	props->poll_oa_period = DEFAULT_POLL_PERIOD_NS;

	अगर (!n_props) अणु
		DRM_DEBUG("No i915 perf properties given\n");
		वापस -EINVAL;
	पूर्ण

	/* At the moment we only support using i915-perf on the RCS. */
	props->engine = पूर्णांकel_engine_lookup_user(perf->i915,
						 I915_ENGINE_CLASS_RENDER,
						 0);
	अगर (!props->engine) अणु
		DRM_DEBUG("No RENDER-capable engines\n");
		वापस -EINVAL;
	पूर्ण

	/* Considering that ID = 0 is reserved and assuming that we करोn't
	 * (currently) expect any configurations to ever specअगरy duplicate
	 * values क्रम a particular property ID then the last _PROP_MAX value is
	 * one greater than the maximum number of properties we expect to get
	 * from userspace.
	 */
	अगर (n_props >= DRM_I915_PERF_PROP_MAX) अणु
		DRM_DEBUG("More i915 perf properties specified than exist\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < n_props; i++) अणु
		u64 oa_period, oa_freq_hz;
		u64 id, value;

		ret = get_user(id, uprop);
		अगर (ret)
			वापस ret;

		ret = get_user(value, uprop + 1);
		अगर (ret)
			वापस ret;

		अगर (id == 0 || id >= DRM_I915_PERF_PROP_MAX) अणु
			DRM_DEBUG("Unknown i915 perf property ID\n");
			वापस -EINVAL;
		पूर्ण

		चयन ((क्रमागत drm_i915_perf_property_id)id) अणु
		हाल DRM_I915_PERF_PROP_CTX_HANDLE:
			props->single_context = 1;
			props->ctx_handle = value;
			अवरोध;
		हाल DRM_I915_PERF_PROP_SAMPLE_OA:
			अगर (value)
				props->sample_flags |= SAMPLE_OA_REPORT;
			अवरोध;
		हाल DRM_I915_PERF_PROP_OA_METRICS_SET:
			अगर (value == 0) अणु
				DRM_DEBUG("Unknown OA metric set ID\n");
				वापस -EINVAL;
			पूर्ण
			props->metrics_set = value;
			अवरोध;
		हाल DRM_I915_PERF_PROP_OA_FORMAT:
			अगर (value == 0 || value >= I915_OA_FORMAT_MAX) अणु
				DRM_DEBUG("Out-of-range OA report format %llu\n",
					  value);
				वापस -EINVAL;
			पूर्ण
			अगर (!oa_क्रमmat_valid(perf, value)) अणु
				DRM_DEBUG("Unsupported OA report format %llu\n",
					  value);
				वापस -EINVAL;
			पूर्ण
			props->oa_क्रमmat = value;
			अवरोध;
		हाल DRM_I915_PERF_PROP_OA_EXPONENT:
			अगर (value > OA_EXPONENT_MAX) अणु
				DRM_DEBUG("OA timer exponent too high (> %u)\n",
					 OA_EXPONENT_MAX);
				वापस -EINVAL;
			पूर्ण

			/* Theoretically we can program the OA unit to sample
			 * e.g. every 160ns क्रम HSW, 167ns क्रम BDW/SKL or 104ns
			 * क्रम BXT. We करोn't allow such high sampling
			 * frequencies by शेष unless root.
			 */

			BUILD_BUG_ON(माप(oa_period) != 8);
			oa_period = oa_exponent_to_ns(perf, value);

			/* This check is primarily to ensure that oa_period <=
			 * UINT32_MAX (beक्रमe passing to करो_भाग which only
			 * accepts a u32 denominator), but we can also skip
			 * checking anything < 1Hz which implicitly can't be
			 * limited via an पूर्णांकeger oa_max_sample_rate.
			 */
			अगर (oa_period <= NSEC_PER_SEC) अणु
				u64 पंचांगp = NSEC_PER_SEC;
				करो_भाग(पंचांगp, oa_period);
				oa_freq_hz = पंचांगp;
			पूर्ण अन्यथा
				oa_freq_hz = 0;

			अगर (oa_freq_hz > i915_oa_max_sample_rate && !perfmon_capable()) अणु
				DRM_DEBUG("OA exponent would exceed the max sampling frequency (sysctl dev.i915.oa_max_sample_rate) %uHz without CAP_PERFMON or CAP_SYS_ADMIN privileges\n",
					  i915_oa_max_sample_rate);
				वापस -EACCES;
			पूर्ण

			props->oa_periodic = true;
			props->oa_period_exponent = value;
			अवरोध;
		हाल DRM_I915_PERF_PROP_HOLD_PREEMPTION:
			props->hold_preemption = !!value;
			अवरोध;
		हाल DRM_I915_PERF_PROP_GLOBAL_SSEU: अणु
			काष्ठा drm_i915_gem_context_param_sseu user_sseu;

			अगर (copy_from_user(&user_sseu,
					   u64_to_user_ptr(value),
					   माप(user_sseu))) अणु
				DRM_DEBUG("Unable to copy global sseu parameter\n");
				वापस -EFAULT;
			पूर्ण

			ret = get_sseu_config(&props->sseu, props->engine, &user_sseu);
			अगर (ret) अणु
				DRM_DEBUG("Invalid SSEU configuration\n");
				वापस ret;
			पूर्ण
			props->has_sseu = true;
			अवरोध;
		पूर्ण
		हाल DRM_I915_PERF_PROP_POLL_OA_PERIOD:
			अगर (value < 100000 /* 100us */) अणु
				DRM_DEBUG("OA availability timer too small (%lluns < 100us)\n",
					  value);
				वापस -EINVAL;
			पूर्ण
			props->poll_oa_period = value;
			अवरोध;
		हाल DRM_I915_PERF_PROP_MAX:
			MISSING_CASE(id);
			वापस -EINVAL;
		पूर्ण

		uprop += 2;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i915_perf_खोलो_ioctl - DRM ioctl() क्रम userspace to खोलो a stream FD
 * @dev: drm device
 * @data: ioctl data copied from userspace (unvalidated)
 * @file: drm file
 *
 * Validates the stream खोलो parameters given by userspace including flags
 * and an array of u64 key, value pair properties.
 *
 * Very little is assumed up front about the nature of the stream being
 * खोलोed (क्रम instance we करोn't assume it's क्रम periodic OA unit metrics). An
 * i915-perf stream is expected to be a suitable पूर्णांकerface क्रम other क्रमms of
 * buffered data written by the GPU besides periodic OA metrics.
 *
 * Note we copy the properties from userspace outside of the i915 perf
 * mutex to aव्योम an awkward lockdep with mmap_lock.
 *
 * Most of the implementation details are handled by
 * i915_perf_खोलो_ioctl_locked() after taking the &perf->lock
 * mutex क्रम serializing with any non-file-operation driver hooks.
 *
 * Return: A newly खोलोed i915 Perf stream file descriptor or negative
 * error code on failure.
 */
पूर्णांक i915_perf_खोलो_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file)
अणु
	काष्ठा i915_perf *perf = &to_i915(dev)->perf;
	काष्ठा drm_i915_perf_खोलो_param *param = data;
	काष्ठा perf_खोलो_properties props;
	u32 known_खोलो_flags;
	पूर्णांक ret;

	अगर (!perf->i915) अणु
		DRM_DEBUG("i915 perf interface not available for this system\n");
		वापस -ENOTSUPP;
	पूर्ण

	known_खोलो_flags = I915_PERF_FLAG_FD_CLOEXEC |
			   I915_PERF_FLAG_FD_NONBLOCK |
			   I915_PERF_FLAG_DISABLED;
	अगर (param->flags & ~known_खोलो_flags) अणु
		DRM_DEBUG("Unknown drm_i915_perf_open_param flag\n");
		वापस -EINVAL;
	पूर्ण

	ret = पढ़ो_properties_unlocked(perf,
				       u64_to_user_ptr(param->properties_ptr),
				       param->num_properties,
				       &props);
	अगर (ret)
		वापस ret;

	mutex_lock(&perf->lock);
	ret = i915_perf_खोलो_ioctl_locked(perf, param, &props, file);
	mutex_unlock(&perf->lock);

	वापस ret;
पूर्ण

/**
 * i915_perf_रेजिस्टर - exposes i915-perf to userspace
 * @i915: i915 device instance
 *
 * In particular OA metric sets are advertised under a sysfs metrics/
 * directory allowing userspace to क्रमागतerate valid IDs that can be
 * used to खोलो an i915-perf stream.
 */
व्योम i915_perf_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_perf *perf = &i915->perf;

	अगर (!perf->i915)
		वापस;

	/* To be sure we're synchronized with an attempted
	 * i915_perf_खोलो_ioctl(); considering that we रेजिस्टर after
	 * being exposed to userspace.
	 */
	mutex_lock(&perf->lock);

	perf->metrics_kobj =
		kobject_create_and_add("metrics",
				       &i915->drm.primary->kdev->kobj);

	mutex_unlock(&perf->lock);
पूर्ण

/**
 * i915_perf_unरेजिस्टर - hide i915-perf from userspace
 * @i915: i915 device instance
 *
 * i915-perf state cleanup is split up पूर्णांकo an 'unregister' and
 * 'deinit' phase where the पूर्णांकerface is first hidden from
 * userspace by i915_perf_unरेजिस्टर() beक्रमe cleaning up
 * reमुख्यing state in i915_perf_fini().
 */
व्योम i915_perf_unरेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_perf *perf = &i915->perf;

	अगर (!perf->metrics_kobj)
		वापस;

	kobject_put(perf->metrics_kobj);
	perf->metrics_kobj = शून्य;
पूर्ण

अटल bool gen8_is_valid_flex_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	अटल स्थिर i915_reg_t flex_eu_regs[] = अणु
		EU_PERF_CNTL0,
		EU_PERF_CNTL1,
		EU_PERF_CNTL2,
		EU_PERF_CNTL3,
		EU_PERF_CNTL4,
		EU_PERF_CNTL5,
		EU_PERF_CNTL6,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(flex_eu_regs); i++) अणु
		अगर (i915_mmio_reg_offset(flex_eu_regs[i]) == addr)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

#घोषणा ADDR_IN_RANGE(addr, start, end) \
	((addr) >= (start) && \
	 (addr) <= (end))

#घोषणा REG_IN_RANGE(addr, start, end) \
	((addr) >= i915_mmio_reg_offset(start) && \
	 (addr) <= i915_mmio_reg_offset(end))

#घोषणा REG_EQUAL(addr, mmio) \
	((addr) == i915_mmio_reg_offset(mmio))

अटल bool gen7_is_valid_b_counter_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	वापस REG_IN_RANGE(addr, OASTARTTRIG1, OASTARTTRIG8) ||
	       REG_IN_RANGE(addr, OAREPORTTRIG1, OAREPORTTRIG8) ||
	       REG_IN_RANGE(addr, OACEC0_0, OACEC7_1);
पूर्ण

अटल bool gen7_is_valid_mux_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	वापस REG_EQUAL(addr, HALF_SLICE_CHICKEN2) ||
	       REG_IN_RANGE(addr, MICRO_BP0_0, NOA_WRITE) ||
	       REG_IN_RANGE(addr, OA_PERFCNT1_LO, OA_PERFCNT2_HI) ||
	       REG_IN_RANGE(addr, OA_PERFMATRIX_LO, OA_PERFMATRIX_HI);
पूर्ण

अटल bool gen8_is_valid_mux_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	वापस gen7_is_valid_mux_addr(perf, addr) ||
	       REG_EQUAL(addr, WAIT_FOR_RC6_EXIT) ||
	       REG_IN_RANGE(addr, RPM_CONFIG0, NOA_CONFIG(8));
पूर्ण

अटल bool gen10_is_valid_mux_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	वापस gen8_is_valid_mux_addr(perf, addr) ||
	       REG_EQUAL(addr, GEN10_NOA_WRITE_HIGH) ||
	       REG_IN_RANGE(addr, OA_PERFCNT3_LO, OA_PERFCNT4_HI);
पूर्ण

अटल bool hsw_is_valid_mux_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	वापस gen7_is_valid_mux_addr(perf, addr) ||
	       ADDR_IN_RANGE(addr, 0x25100, 0x2FF90) ||
	       REG_IN_RANGE(addr, HSW_MBVID2_NOA0, HSW_MBVID2_NOA9) ||
	       REG_EQUAL(addr, HSW_MBVID2_MISR0);
पूर्ण

अटल bool chv_is_valid_mux_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	वापस gen7_is_valid_mux_addr(perf, addr) ||
	       ADDR_IN_RANGE(addr, 0x182300, 0x1823A4);
पूर्ण

अटल bool gen12_is_valid_b_counter_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	वापस REG_IN_RANGE(addr, GEN12_OAG_OASTARTTRIG1, GEN12_OAG_OASTARTTRIG8) ||
	       REG_IN_RANGE(addr, GEN12_OAG_OAREPORTTRIG1, GEN12_OAG_OAREPORTTRIG8) ||
	       REG_IN_RANGE(addr, GEN12_OAG_CEC0_0, GEN12_OAG_CEC7_1) ||
	       REG_IN_RANGE(addr, GEN12_OAG_SCEC0_0, GEN12_OAG_SCEC7_1) ||
	       REG_EQUAL(addr, GEN12_OAA_DBG_REG) ||
	       REG_EQUAL(addr, GEN12_OAG_OA_PESS) ||
	       REG_EQUAL(addr, GEN12_OAG_SPCTR_CNF);
पूर्ण

अटल bool gen12_is_valid_mux_addr(काष्ठा i915_perf *perf, u32 addr)
अणु
	वापस REG_EQUAL(addr, NOA_WRITE) ||
	       REG_EQUAL(addr, GEN10_NOA_WRITE_HIGH) ||
	       REG_EQUAL(addr, GDT_CHICKEN_BITS) ||
	       REG_EQUAL(addr, WAIT_FOR_RC6_EXIT) ||
	       REG_EQUAL(addr, RPM_CONFIG0) ||
	       REG_EQUAL(addr, RPM_CONFIG1) ||
	       REG_IN_RANGE(addr, NOA_CONFIG(0), NOA_CONFIG(8));
पूर्ण

अटल u32 mask_reg_value(u32 reg, u32 val)
अणु
	/* HALF_SLICE_CHICKEN2 is programmed with a the
	 * WaDisableSTUnitPowerOptimization workaround. Make sure the value
	 * programmed by userspace करोesn't change this.
	 */
	अगर (REG_EQUAL(reg, HALF_SLICE_CHICKEN2))
		val = val & ~_MASKED_BIT_ENABLE(GEN8_ST_PO_DISABLE);

	/* WAIT_FOR_RC6_EXIT has only one bit fullfilling the function
	 * indicated by its name and a bunch of selection fields used by OA
	 * configs.
	 */
	अगर (REG_EQUAL(reg, WAIT_FOR_RC6_EXIT))
		val = val & ~_MASKED_BIT_ENABLE(HSW_WAIT_FOR_RC6_EXIT_ENABLE);

	वापस val;
पूर्ण

अटल काष्ठा i915_oa_reg *alloc_oa_regs(काष्ठा i915_perf *perf,
					 bool (*is_valid)(काष्ठा i915_perf *perf, u32 addr),
					 u32 __user *regs,
					 u32 n_regs)
अणु
	काष्ठा i915_oa_reg *oa_regs;
	पूर्णांक err;
	u32 i;

	अगर (!n_regs)
		वापस शून्य;

	/* No is_valid function means we're not allowing any रेजिस्टर to be programmed. */
	GEM_BUG_ON(!is_valid);
	अगर (!is_valid)
		वापस ERR_PTR(-EINVAL);

	oa_regs = kदो_स्मृति_array(n_regs, माप(*oa_regs), GFP_KERNEL);
	अगर (!oa_regs)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < n_regs; i++) अणु
		u32 addr, value;

		err = get_user(addr, regs);
		अगर (err)
			जाओ addr_err;

		अगर (!is_valid(perf, addr)) अणु
			DRM_DEBUG("Invalid oa_reg address: %X\n", addr);
			err = -EINVAL;
			जाओ addr_err;
		पूर्ण

		err = get_user(value, regs + 1);
		अगर (err)
			जाओ addr_err;

		oa_regs[i].addr = _MMIO(addr);
		oa_regs[i].value = mask_reg_value(addr, value);

		regs += 2;
	पूर्ण

	वापस oa_regs;

addr_err:
	kमुक्त(oa_regs);
	वापस ERR_PTR(err);
पूर्ण

अटल sमाप_प्रकार show_dynamic_id(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा i915_oa_config *oa_config =
		container_of(attr, typeof(*oa_config), sysfs_metric_id);

	वापस प्र_लिखो(buf, "%d\n", oa_config->id);
पूर्ण

अटल पूर्णांक create_dynamic_oa_sysfs_entry(काष्ठा i915_perf *perf,
					 काष्ठा i915_oa_config *oa_config)
अणु
	sysfs_attr_init(&oa_config->sysfs_metric_id.attr);
	oa_config->sysfs_metric_id.attr.name = "id";
	oa_config->sysfs_metric_id.attr.mode = S_IRUGO;
	oa_config->sysfs_metric_id.show = show_dynamic_id;
	oa_config->sysfs_metric_id.store = शून्य;

	oa_config->attrs[0] = &oa_config->sysfs_metric_id.attr;
	oa_config->attrs[1] = शून्य;

	oa_config->sysfs_metric.name = oa_config->uuid;
	oa_config->sysfs_metric.attrs = oa_config->attrs;

	वापस sysfs_create_group(perf->metrics_kobj,
				  &oa_config->sysfs_metric);
पूर्ण

/**
 * i915_perf_add_config_ioctl - DRM ioctl() क्रम userspace to add a new OA config
 * @dev: drm device
 * @data: ioctl data (poपूर्णांकer to काष्ठा drm_i915_perf_oa_config) copied from
 *        userspace (unvalidated)
 * @file: drm file
 *
 * Validates the submitted OA रेजिस्टर to be saved पूर्णांकo a new OA config that
 * can then be used क्रम programming the OA unit and its NOA network.
 *
 * Returns: A new allocated config number to be used with the perf खोलो ioctl
 * or a negative error code on failure.
 */
पूर्णांक i915_perf_add_config_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file)
अणु
	काष्ठा i915_perf *perf = &to_i915(dev)->perf;
	काष्ठा drm_i915_perf_oa_config *args = data;
	काष्ठा i915_oa_config *oa_config, *पंचांगp;
	काष्ठा i915_oa_reg *regs;
	पूर्णांक err, id;

	अगर (!perf->i915) अणु
		DRM_DEBUG("i915 perf interface not available for this system\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!perf->metrics_kobj) अणु
		DRM_DEBUG("OA metrics weren't advertised via sysfs\n");
		वापस -EINVAL;
	पूर्ण

	अगर (i915_perf_stream_paranoid && !perfmon_capable()) अणु
		DRM_DEBUG("Insufficient privileges to add i915 OA config\n");
		वापस -EACCES;
	पूर्ण

	अगर ((!args->mux_regs_ptr || !args->n_mux_regs) &&
	    (!args->boolean_regs_ptr || !args->n_boolean_regs) &&
	    (!args->flex_regs_ptr || !args->n_flex_regs)) अणु
		DRM_DEBUG("No OA registers given\n");
		वापस -EINVAL;
	पूर्ण

	oa_config = kzalloc(माप(*oa_config), GFP_KERNEL);
	अगर (!oa_config) अणु
		DRM_DEBUG("Failed to allocate memory for the OA config\n");
		वापस -ENOMEM;
	पूर्ण

	oa_config->perf = perf;
	kref_init(&oa_config->ref);

	अगर (!uuid_is_valid(args->uuid)) अणु
		DRM_DEBUG("Invalid uuid format for OA config\n");
		err = -EINVAL;
		जाओ reg_err;
	पूर्ण

	/* Last अक्षरacter in oa_config->uuid will be 0 because oa_config is
	 * kzalloc.
	 */
	स_नकल(oa_config->uuid, args->uuid, माप(args->uuid));

	oa_config->mux_regs_len = args->n_mux_regs;
	regs = alloc_oa_regs(perf,
			     perf->ops.is_valid_mux_reg,
			     u64_to_user_ptr(args->mux_regs_ptr),
			     args->n_mux_regs);

	अगर (IS_ERR(regs)) अणु
		DRM_DEBUG("Failed to create OA config for mux_regs\n");
		err = PTR_ERR(regs);
		जाओ reg_err;
	पूर्ण
	oa_config->mux_regs = regs;

	oa_config->b_counter_regs_len = args->n_boolean_regs;
	regs = alloc_oa_regs(perf,
			     perf->ops.is_valid_b_counter_reg,
			     u64_to_user_ptr(args->boolean_regs_ptr),
			     args->n_boolean_regs);

	अगर (IS_ERR(regs)) अणु
		DRM_DEBUG("Failed to create OA config for b_counter_regs\n");
		err = PTR_ERR(regs);
		जाओ reg_err;
	पूर्ण
	oa_config->b_counter_regs = regs;

	अगर (INTEL_GEN(perf->i915) < 8) अणु
		अगर (args->n_flex_regs != 0) अणु
			err = -EINVAL;
			जाओ reg_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		oa_config->flex_regs_len = args->n_flex_regs;
		regs = alloc_oa_regs(perf,
				     perf->ops.is_valid_flex_reg,
				     u64_to_user_ptr(args->flex_regs_ptr),
				     args->n_flex_regs);

		अगर (IS_ERR(regs)) अणु
			DRM_DEBUG("Failed to create OA config for flex_regs\n");
			err = PTR_ERR(regs);
			जाओ reg_err;
		पूर्ण
		oa_config->flex_regs = regs;
	पूर्ण

	err = mutex_lock_पूर्णांकerruptible(&perf->metrics_lock);
	अगर (err)
		जाओ reg_err;

	/* We shouldn't have too many configs, so this iteration shouldn't be
	 * too costly.
	 */
	idr_क्रम_each_entry(&perf->metrics_idr, पंचांगp, id) अणु
		अगर (!म_भेद(पंचांगp->uuid, oa_config->uuid)) अणु
			DRM_DEBUG("OA config already exists with this uuid\n");
			err = -EADDRINUSE;
			जाओ sysfs_err;
		पूर्ण
	पूर्ण

	err = create_dynamic_oa_sysfs_entry(perf, oa_config);
	अगर (err) अणु
		DRM_DEBUG("Failed to create sysfs entry for OA config\n");
		जाओ sysfs_err;
	पूर्ण

	/* Config id 0 is invalid, id 1 क्रम kernel stored test config. */
	oa_config->id = idr_alloc(&perf->metrics_idr,
				  oa_config, 2,
				  0, GFP_KERNEL);
	अगर (oa_config->id < 0) अणु
		DRM_DEBUG("Failed to create sysfs entry for OA config\n");
		err = oa_config->id;
		जाओ sysfs_err;
	पूर्ण

	mutex_unlock(&perf->metrics_lock);

	DRM_DEBUG("Added config %s id=%i\n", oa_config->uuid, oa_config->id);

	वापस oa_config->id;

sysfs_err:
	mutex_unlock(&perf->metrics_lock);
reg_err:
	i915_oa_config_put(oa_config);
	DRM_DEBUG("Failed to add new OA config\n");
	वापस err;
पूर्ण

/**
 * i915_perf_हटाओ_config_ioctl - DRM ioctl() क्रम userspace to हटाओ an OA config
 * @dev: drm device
 * @data: ioctl data (poपूर्णांकer to u64 पूर्णांकeger) copied from userspace
 * @file: drm file
 *
 * Configs can be हटाओd जबतक being used, the will stop appearing in sysfs
 * and their content will be मुक्तd when the stream using the config is बंदd.
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक i915_perf_हटाओ_config_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file)
अणु
	काष्ठा i915_perf *perf = &to_i915(dev)->perf;
	u64 *arg = data;
	काष्ठा i915_oa_config *oa_config;
	पूर्णांक ret;

	अगर (!perf->i915) अणु
		DRM_DEBUG("i915 perf interface not available for this system\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (i915_perf_stream_paranoid && !perfmon_capable()) अणु
		DRM_DEBUG("Insufficient privileges to remove i915 OA config\n");
		वापस -EACCES;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&perf->metrics_lock);
	अगर (ret)
		वापस ret;

	oa_config = idr_find(&perf->metrics_idr, *arg);
	अगर (!oa_config) अणु
		DRM_DEBUG("Failed to remove unknown OA config\n");
		ret = -ENOENT;
		जाओ err_unlock;
	पूर्ण

	GEM_BUG_ON(*arg != oa_config->id);

	sysfs_हटाओ_group(perf->metrics_kobj, &oa_config->sysfs_metric);

	idr_हटाओ(&perf->metrics_idr, *arg);

	mutex_unlock(&perf->metrics_lock);

	DRM_DEBUG("Removed config %s id=%i\n", oa_config->uuid, oa_config->id);

	i915_oa_config_put(oa_config);

	वापस 0;

err_unlock:
	mutex_unlock(&perf->metrics_lock);
	वापस ret;
पूर्ण

अटल काष्ठा ctl_table oa_table[] = अणु
	अणु
	 .procname = "perf_stream_paranoid",
	 .data = &i915_perf_stream_paranoid,
	 .maxlen = माप(i915_perf_stream_paranoid),
	 .mode = 0644,
	 .proc_handler = proc_करोपूर्णांकvec_minmax,
	 .extra1 = SYSCTL_ZERO,
	 .extra2 = SYSCTL_ONE,
	 पूर्ण,
	अणु
	 .procname = "oa_max_sample_rate",
	 .data = &i915_oa_max_sample_rate,
	 .maxlen = माप(i915_oa_max_sample_rate),
	 .mode = 0644,
	 .proc_handler = proc_करोपूर्णांकvec_minmax,
	 .extra1 = SYSCTL_ZERO,
	 .extra2 = &oa_sample_rate_hard_limit,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table i915_root[] = अणु
	अणु
	 .procname = "i915",
	 .maxlen = 0,
	 .mode = 0555,
	 .child = oa_table,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table dev_root[] = अणु
	अणु
	 .procname = "dev",
	 .maxlen = 0,
	 .mode = 0555,
	 .child = i915_root,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम oa_init_supported_क्रमmats(काष्ठा i915_perf *perf)
अणु
	काष्ठा drm_i915_निजी *i915 = perf->i915;
	क्रमागत पूर्णांकel_platक्रमm platक्रमm = INTEL_INFO(i915)->platक्रमm;

	चयन (platक्रमm) अणु
	हाल INTEL_HASWELL:
		oa_क्रमmat_add(perf, I915_OA_FORMAT_A13);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_A13);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_A29);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_A13_B8_C8);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_B4_C8);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_A45_B8_C8);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_B4_C8_A16);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_C4_B8);
		अवरोध;

	हाल INTEL_BROADWELL:
	हाल INTEL_CHERRYVIEW:
	हाल INTEL_SKYLAKE:
	हाल INTEL_BROXTON:
	हाल INTEL_KABYLAKE:
	हाल INTEL_GEMINILAKE:
	हाल INTEL_COFFEELAKE:
	हाल INTEL_COMETLAKE:
	हाल INTEL_CANNONLAKE:
	हाल INTEL_ICELAKE:
	हाल INTEL_ELKHARTLAKE:
	हाल INTEL_JASPERLAKE:
	हाल INTEL_TIGERLAKE:
	हाल INTEL_ROCKETLAKE:
	हाल INTEL_DG1:
	हाल INTEL_ALDERLAKE_S:
		oa_क्रमmat_add(perf, I915_OA_FORMAT_A12);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_A12_B8_C8);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_A32u40_A4u32_B8_C8);
		oa_क्रमmat_add(perf, I915_OA_FORMAT_C4_B8);
		अवरोध;

	शेष:
		MISSING_CASE(platक्रमm);
	पूर्ण
पूर्ण

/**
 * i915_perf_init - initialize i915-perf state on module bind
 * @i915: i915 device instance
 *
 * Initializes i915-perf state without exposing anything to userspace.
 *
 * Note: i915-perf initialization is split पूर्णांकo an 'init' and 'register'
 * phase with the i915_perf_रेजिस्टर() exposing state to userspace.
 */
व्योम i915_perf_init(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_perf *perf = &i915->perf;

	/* XXX स्थिर काष्ठा i915_perf_ops! */

	perf->oa_क्रमmats = oa_क्रमmats;
	अगर (IS_HASWELL(i915)) अणु
		perf->ops.is_valid_b_counter_reg = gen7_is_valid_b_counter_addr;
		perf->ops.is_valid_mux_reg = hsw_is_valid_mux_addr;
		perf->ops.is_valid_flex_reg = शून्य;
		perf->ops.enable_metric_set = hsw_enable_metric_set;
		perf->ops.disable_metric_set = hsw_disable_metric_set;
		perf->ops.oa_enable = gen7_oa_enable;
		perf->ops.oa_disable = gen7_oa_disable;
		perf->ops.पढ़ो = gen7_oa_पढ़ो;
		perf->ops.oa_hw_tail_पढ़ो = gen7_oa_hw_tail_पढ़ो;
	पूर्ण अन्यथा अगर (HAS_LOGICAL_RING_CONTEXTS(i915)) अणु
		/* Note: that although we could theoretically also support the
		 * legacy ringbuffer mode on BDW (and earlier iterations of
		 * this driver, beक्रमe upstreaming did this) it didn't seem
		 * worth the complनिकासy to मुख्यtain now that BDW+ enable
		 * execlist mode by शेष.
		 */
		perf->ops.पढ़ो = gen8_oa_पढ़ो;

		अगर (IS_GEN_RANGE(i915, 8, 9)) अणु
			perf->ops.is_valid_b_counter_reg =
				gen7_is_valid_b_counter_addr;
			perf->ops.is_valid_mux_reg =
				gen8_is_valid_mux_addr;
			perf->ops.is_valid_flex_reg =
				gen8_is_valid_flex_addr;

			अगर (IS_CHERRYVIEW(i915)) अणु
				perf->ops.is_valid_mux_reg =
					chv_is_valid_mux_addr;
			पूर्ण

			perf->ops.oa_enable = gen8_oa_enable;
			perf->ops.oa_disable = gen8_oa_disable;
			perf->ops.enable_metric_set = gen8_enable_metric_set;
			perf->ops.disable_metric_set = gen8_disable_metric_set;
			perf->ops.oa_hw_tail_पढ़ो = gen8_oa_hw_tail_पढ़ो;

			अगर (IS_GEN(i915, 8)) अणु
				perf->ctx_oactxctrl_offset = 0x120;
				perf->ctx_flexeu0_offset = 0x2ce;

				perf->gen8_valid_ctx_bit = BIT(25);
			पूर्ण अन्यथा अणु
				perf->ctx_oactxctrl_offset = 0x128;
				perf->ctx_flexeu0_offset = 0x3de;

				perf->gen8_valid_ctx_bit = BIT(16);
			पूर्ण
		पूर्ण अन्यथा अगर (IS_GEN_RANGE(i915, 10, 11)) अणु
			perf->ops.is_valid_b_counter_reg =
				gen7_is_valid_b_counter_addr;
			perf->ops.is_valid_mux_reg =
				gen10_is_valid_mux_addr;
			perf->ops.is_valid_flex_reg =
				gen8_is_valid_flex_addr;

			perf->ops.oa_enable = gen8_oa_enable;
			perf->ops.oa_disable = gen8_oa_disable;
			perf->ops.enable_metric_set = gen8_enable_metric_set;
			perf->ops.disable_metric_set = gen10_disable_metric_set;
			perf->ops.oa_hw_tail_पढ़ो = gen8_oa_hw_tail_पढ़ो;

			अगर (IS_GEN(i915, 10)) अणु
				perf->ctx_oactxctrl_offset = 0x128;
				perf->ctx_flexeu0_offset = 0x3de;
			पूर्ण अन्यथा अणु
				perf->ctx_oactxctrl_offset = 0x124;
				perf->ctx_flexeu0_offset = 0x78e;
			पूर्ण
			perf->gen8_valid_ctx_bit = BIT(16);
		पूर्ण अन्यथा अगर (IS_GEN(i915, 12)) अणु
			perf->ops.is_valid_b_counter_reg =
				gen12_is_valid_b_counter_addr;
			perf->ops.is_valid_mux_reg =
				gen12_is_valid_mux_addr;
			perf->ops.is_valid_flex_reg =
				gen8_is_valid_flex_addr;

			perf->ops.oa_enable = gen12_oa_enable;
			perf->ops.oa_disable = gen12_oa_disable;
			perf->ops.enable_metric_set = gen12_enable_metric_set;
			perf->ops.disable_metric_set = gen12_disable_metric_set;
			perf->ops.oa_hw_tail_पढ़ो = gen12_oa_hw_tail_पढ़ो;

			perf->ctx_flexeu0_offset = 0;
			perf->ctx_oactxctrl_offset = 0x144;
		पूर्ण
	पूर्ण

	अगर (perf->ops.enable_metric_set) अणु
		mutex_init(&perf->lock);

		/* Choose a representative limit */
		oa_sample_rate_hard_limit = i915->gt.घड़ी_frequency / 2;

		mutex_init(&perf->metrics_lock);
		idr_init_base(&perf->metrics_idr, 1);

		/* We set up some ratelimit state to potentially throttle any
		 * _NOTES about spurious, invalid OA reports which we करोn't
		 * क्रमward to userspace.
		 *
		 * We prपूर्णांक a _NOTE about any throttling when closing the
		 * stream instead of रुकोing until driver _fini which no one
		 * would ever see.
		 *
		 * Using the same limiting factors as prपूर्णांकk_ratelimit()
		 */
		ratelimit_state_init(&perf->spurious_report_rs, 5 * HZ, 10);
		/* Since we use a DRM_NOTE क्रम spurious reports it would be
		 * inconsistent to let __ratelimit() स्वतःmatically prपूर्णांक a
		 * warning क्रम throttling.
		 */
		ratelimit_set_flags(&perf->spurious_report_rs,
				    RATELIMIT_MSG_ON_RELEASE);

		ratelimit_state_init(&perf->tail_poपूर्णांकer_race,
				     5 * HZ, 10);
		ratelimit_set_flags(&perf->tail_poपूर्णांकer_race,
				    RATELIMIT_MSG_ON_RELEASE);

		atomic64_set(&perf->noa_programming_delay,
			     500 * 1000 /* 500us */);

		perf->i915 = i915;

		oa_init_supported_क्रमmats(perf);
	पूर्ण
पूर्ण

अटल पूर्णांक destroy_config(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	i915_oa_config_put(p);
	वापस 0;
पूर्ण

व्योम i915_perf_sysctl_रेजिस्टर(व्योम)
अणु
	sysctl_header = रेजिस्टर_sysctl_table(dev_root);
पूर्ण

व्योम i915_perf_sysctl_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_sysctl_table(sysctl_header);
पूर्ण

/**
 * i915_perf_fini - Counter part to i915_perf_init()
 * @i915: i915 device instance
 */
व्योम i915_perf_fini(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_perf *perf = &i915->perf;

	अगर (!perf->i915)
		वापस;

	idr_क्रम_each(&perf->metrics_idr, destroy_config, perf);
	idr_destroy(&perf->metrics_idr);

	स_रखो(&perf->ops, 0, माप(perf->ops));
	perf->i915 = शून्य;
पूर्ण

/**
 * i915_perf_ioctl_version - Version of the i915-perf subप्रणाली
 *
 * This version number is used by userspace to detect available features.
 */
पूर्णांक i915_perf_ioctl_version(व्योम)
अणु
	/*
	 * 1: Initial version
	 *   I915_PERF_IOCTL_ENABLE
	 *   I915_PERF_IOCTL_DISABLE
	 *
	 * 2: Added runसमय modअगरication of OA config.
	 *   I915_PERF_IOCTL_CONFIG
	 *
	 * 3: Add DRM_I915_PERF_PROP_HOLD_PREEMPTION parameter to hold
	 *    preemption on a particular context so that perक्रमmance data is
	 *    accessible from a delta of MI_RPC reports without looking at the
	 *    OA buffer.
	 *
	 * 4: Add DRM_I915_PERF_PROP_ALLOWED_SSEU to limit what contexts can
	 *    be run क्रम the duration of the perक्रमmance recording based on
	 *    their SSEU configuration.
	 *
	 * 5: Add DRM_I915_PERF_PROP_POLL_OA_PERIOD parameter that controls the
	 *    पूर्णांकerval क्रम the hrसमयr used to check क्रम OA data.
	 */
	वापस 5;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_perf.c"
#पूर्ण_अगर
