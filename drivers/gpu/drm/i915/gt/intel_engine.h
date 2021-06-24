<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित _INTEL_RINGBUFFER_H_
#घोषणा _INTEL_RINGBUFFER_H_

#समावेश <drm/drm_util.h>

#समावेश <linux/hashtable.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/seqlock.h>

#समावेश "i915_pmu.h"
#समावेश "i915_reg.h"
#समावेश "i915_request.h"
#समावेश "i915_selftest.h"
#समावेश "gt/intel_timeline.h"
#समावेश "intel_engine_types.h"
#समावेश "intel_workarounds.h"

काष्ठा drm_prपूर्णांकer;
काष्ठा पूर्णांकel_gt;

/* Early gen2 devices have a cacheline of just 32 bytes, using 64 is overसमाप्त,
 * but keeps the logic simple. Indeed, the whole purpose of this macro is just
 * to give some inclination as to some of the magic values used in the various
 * workarounds!
 */
#घोषणा CACHELINE_BYTES 64
#घोषणा CACHELINE_DWORDS (CACHELINE_BYTES / माप(u32))

#घोषणा ENGINE_TRACE(e, fmt, ...) करो अणु					\
	स्थिर काष्ठा पूर्णांकel_engine_cs *e__ __maybe_unused = (e);		\
	GEM_TRACE("%s %s: " fmt,					\
		  dev_name(e__->i915->drm.dev), e__->name,		\
		  ##__VA_ARGS__);					\
पूर्ण जबतक (0)

/*
 * The रेजिस्टर defines to be used with the following macros need to accept a
 * base param, e.g:
 *
 * REG_FOO(base) _MMIO((base) + <relative offset>)
 * ENGINE_READ(engine, REG_FOO);
 *
 * रेजिस्टर arrays are to be defined and accessed as follows:
 *
 * REG_BAR(base, i) _MMIO((base) + <relative offset> + (i) * <shअगरt>)
 * ENGINE_READ_IDX(engine, REG_BAR, i)
 */

#घोषणा __ENGINE_REG_OP(op__, engine__, ...) \
	पूर्णांकel_uncore_##op__((engine__)->uncore, __VA_ARGS__)

#घोषणा __ENGINE_READ_OP(op__, engine__, reg__) \
	__ENGINE_REG_OP(op__, (engine__), reg__((engine__)->mmio_base))

#घोषणा ENGINE_READ16(...)	__ENGINE_READ_OP(पढ़ो16, __VA_ARGS__)
#घोषणा ENGINE_READ(...)	__ENGINE_READ_OP(पढ़ो, __VA_ARGS__)
#घोषणा ENGINE_READ_FW(...)	__ENGINE_READ_OP(पढ़ो_fw, __VA_ARGS__)
#घोषणा ENGINE_POSTING_READ(...) __ENGINE_READ_OP(posting_पढ़ो_fw, __VA_ARGS__)
#घोषणा ENGINE_POSTING_READ16(...) __ENGINE_READ_OP(posting_पढ़ो16, __VA_ARGS__)

#घोषणा ENGINE_READ64(engine__, lower_reg__, upper_reg__) \
	__ENGINE_REG_OP(पढ़ो64_2x32, (engine__), \
			lower_reg__((engine__)->mmio_base), \
			upper_reg__((engine__)->mmio_base))

#घोषणा ENGINE_READ_IDX(engine__, reg__, idx__) \
	__ENGINE_REG_OP(पढ़ो, (engine__), reg__((engine__)->mmio_base, (idx__)))

#घोषणा __ENGINE_WRITE_OP(op__, engine__, reg__, val__) \
	__ENGINE_REG_OP(op__, (engine__), reg__((engine__)->mmio_base), (val__))

#घोषणा ENGINE_WRITE16(...)	__ENGINE_WRITE_OP(ग_लिखो16, __VA_ARGS__)
#घोषणा ENGINE_WRITE(...)	__ENGINE_WRITE_OP(ग_लिखो, __VA_ARGS__)
#घोषणा ENGINE_WRITE_FW(...)	__ENGINE_WRITE_OP(ग_लिखो_fw, __VA_ARGS__)

#घोषणा GEN6_RING_FAULT_REG_READ(engine__) \
	पूर्णांकel_uncore_पढ़ो((engine__)->uncore, RING_FAULT_REG(engine__))

#घोषणा GEN6_RING_FAULT_REG_POSTING_READ(engine__) \
	पूर्णांकel_uncore_posting_पढ़ो((engine__)->uncore, RING_FAULT_REG(engine__))

#घोषणा GEN6_RING_FAULT_REG_RMW(engine__, clear__, set__) \
(अणु \
	u32 __val; \
\
	__val = पूर्णांकel_uncore_पढ़ो((engine__)->uncore, \
				  RING_FAULT_REG(engine__)); \
	__val &= ~(clear__); \
	__val |= (set__); \
	पूर्णांकel_uncore_ग_लिखो((engine__)->uncore, RING_FAULT_REG(engine__), \
			   __val); \
पूर्ण)

/* seqno size is actually only a uपूर्णांक32, but since we plan to use MI_FLUSH_DW to
 * करो the ग_लिखोs, and that must have qw aligned offsets, simply pretend it's 8b.
 */

अटल अंतरभूत अचिन्हित पूर्णांक
execlists_num_ports(स्थिर काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists)
अणु
	वापस execlists->port_mask + 1;
पूर्ण

अटल अंतरभूत काष्ठा i915_request *
execlists_active(स्थिर काष्ठा पूर्णांकel_engine_execlists *execlists)
अणु
	काष्ठा i915_request * स्थिर *cur, * स्थिर *old, *active;

	cur = READ_ONCE(execlists->active);
	smp_rmb(); /* pairs with overग_लिखो protection in process_csb() */
	करो अणु
		old = cur;

		active = READ_ONCE(*cur);
		cur = READ_ONCE(execlists->active);

		smp_rmb(); /* and complete the seqlock retry */
	पूर्ण जबतक (unlikely(cur != old));

	वापस active;
पूर्ण

अटल अंतरभूत व्योम
execlists_active_lock_bh(काष्ठा पूर्णांकel_engine_execlists *execlists)
अणु
	local_bh_disable(); /* prevent local softirq and lock recursion */
	tasklet_lock(&execlists->tasklet);
पूर्ण

अटल अंतरभूत व्योम
execlists_active_unlock_bh(काष्ठा पूर्णांकel_engine_execlists *execlists)
अणु
	tasklet_unlock(&execlists->tasklet);
	local_bh_enable(); /* restore softirq, and kick ksoftirqd! */
पूर्ण

काष्ठा i915_request *
execlists_unwind_incomplete_requests(काष्ठा पूर्णांकel_engine_execlists *execlists);

अटल अंतरभूत u32
पूर्णांकel_पढ़ो_status_page(स्थिर काष्ठा पूर्णांकel_engine_cs *engine, पूर्णांक reg)
अणु
	/* Ensure that the compiler करोesn't optimize away the load. */
	वापस READ_ONCE(engine->status_page.addr[reg]);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_ग_लिखो_status_page(काष्ठा पूर्णांकel_engine_cs *engine, पूर्णांक reg, u32 value)
अणु
	/* Writing पूर्णांकo the status page should be करोne sparingly. Since
	 * we करो when we are uncertain of the device state, we take a bit
	 * of extra paranoia to try and ensure that the HWS takes the value
	 * we give and that it करोesn't end up trapped inside the CPU!
	 */
	अगर (अटल_cpu_has(X86_FEATURE_CLFLUSH)) अणु
		mb();
		clflush(&engine->status_page.addr[reg]);
		engine->status_page.addr[reg] = value;
		clflush(&engine->status_page.addr[reg]);
		mb();
	पूर्ण अन्यथा अणु
		WRITE_ONCE(engine->status_page.addr[reg], value);
	पूर्ण
पूर्ण

/*
 * Reads a dword out of the status page, which is written to from the command
 * queue by स्वतःmatic updates, MI_REPORT_HEAD, MI_STORE_DATA_INDEX, or
 * MI_STORE_DATA_IMM.
 *
 * The following dwords have a reserved meaning:
 * 0x00: ISR copy, updated when an ISR bit not set in the HWSTAM changes.
 * 0x04: ring 0 head poपूर्णांकer
 * 0x05: ring 1 head poपूर्णांकer (915-class)
 * 0x06: ring 2 head poपूर्णांकer (915-class)
 * 0x10-0x1b: Context status DWords (GM45)
 * 0x1f: Last written status offset. (GM45)
 * 0x20-0x2f: Reserved (Gen6+)
 *
 * The area from dword 0x30 to 0x3ff is available क्रम driver usage.
 */
#घोषणा I915_GEM_HWS_PREEMPT		0x32
#घोषणा I915_GEM_HWS_PREEMPT_ADDR	(I915_GEM_HWS_PREEMPT * माप(u32))
#घोषणा I915_GEM_HWS_SEQNO		0x40
#घोषणा I915_GEM_HWS_SEQNO_ADDR		(I915_GEM_HWS_SEQNO * माप(u32))
#घोषणा I915_GEM_HWS_SCRATCH		0x80

#घोषणा I915_HWS_CSB_BUF0_INDEX		0x10
#घोषणा I915_HWS_CSB_WRITE_INDEX	0x1f
#घोषणा CNL_HWS_CSB_WRITE_INDEX		0x2f

व्योम पूर्णांकel_engine_stop(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_engine_cleanup(काष्ठा पूर्णांकel_engine_cs *engine);

पूर्णांक पूर्णांकel_engines_init_mmio(काष्ठा पूर्णांकel_gt *gt);
पूर्णांक पूर्णांकel_engines_init(काष्ठा पूर्णांकel_gt *gt);

व्योम पूर्णांकel_engine_मुक्त_request_pool(काष्ठा पूर्णांकel_engine_cs *engine);

व्योम पूर्णांकel_engines_release(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_engines_मुक्त(काष्ठा पूर्णांकel_gt *gt);

पूर्णांक पूर्णांकel_engine_init_common(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_engine_cleanup_common(काष्ठा पूर्णांकel_engine_cs *engine);

पूर्णांक पूर्णांकel_engine_resume(काष्ठा पूर्णांकel_engine_cs *engine);

पूर्णांक पूर्णांकel_ring_submission_setup(काष्ठा पूर्णांकel_engine_cs *engine);

पूर्णांक पूर्णांकel_engine_stop_cs(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_engine_cancel_stop_cs(काष्ठा पूर्णांकel_engine_cs *engine);

व्योम पूर्णांकel_engine_set_hwsp_ग_लिखोmask(काष्ठा पूर्णांकel_engine_cs *engine, u32 mask);

u64 पूर्णांकel_engine_get_active_head(स्थिर काष्ठा पूर्णांकel_engine_cs *engine);
u64 पूर्णांकel_engine_get_last_batch_head(स्थिर काष्ठा पूर्णांकel_engine_cs *engine);

व्योम पूर्णांकel_engine_get_instकरोne(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			       काष्ठा पूर्णांकel_instकरोne *instकरोne);

व्योम पूर्णांकel_engine_init_execlists(काष्ठा पूर्णांकel_engine_cs *engine);

अटल अंतरभूत व्योम __पूर्णांकel_engine_reset(काष्ठा पूर्णांकel_engine_cs *engine,
					bool stalled)
अणु
	अगर (engine->reset.शुरुआत)
		engine->reset.शुरुआत(engine, stalled);
	engine->serial++; /* contexts lost */
पूर्ण

bool पूर्णांकel_engines_are_idle(काष्ठा पूर्णांकel_gt *gt);
bool पूर्णांकel_engine_is_idle(काष्ठा पूर्णांकel_engine_cs *engine);

व्योम __पूर्णांकel_engine_flush_submission(काष्ठा पूर्णांकel_engine_cs *engine, bool sync);
अटल अंतरभूत व्योम पूर्णांकel_engine_flush_submission(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	__पूर्णांकel_engine_flush_submission(engine, true);
पूर्ण

व्योम पूर्णांकel_engines_reset_शेष_submission(काष्ठा पूर्णांकel_gt *gt);

bool पूर्णांकel_engine_can_store_dword(काष्ठा पूर्णांकel_engine_cs *engine);

__म_लिखो(3, 4)
व्योम पूर्णांकel_engine_dump(काष्ठा पूर्णांकel_engine_cs *engine,
		       काष्ठा drm_prपूर्णांकer *m,
		       स्थिर अक्षर *header, ...);

kसमय_प्रकार पूर्णांकel_engine_get_busy_समय(काष्ठा पूर्णांकel_engine_cs *engine,
				   kसमय_प्रकार *now);

काष्ठा i915_request *
पूर्णांकel_engine_find_active_request(काष्ठा पूर्णांकel_engine_cs *engine);

u32 पूर्णांकel_engine_context_size(काष्ठा पूर्णांकel_gt *gt, u8 class);

व्योम पूर्णांकel_engine_init_active(काष्ठा पूर्णांकel_engine_cs *engine,
			      अचिन्हित पूर्णांक subclass);
#घोषणा ENGINE_PHYSICAL	0
#घोषणा ENGINE_MOCK	1
#घोषणा ENGINE_VIRTUAL	2

अटल अंतरभूत bool
पूर्णांकel_engine_has_preempt_reset(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_PREEMPT_TIMEOUT))
		वापस false;

	वापस पूर्णांकel_engine_has_preemption(engine);
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_has_heartbeat(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_HEARTBEAT_INTERVAL))
		वापस false;

	वापस READ_ONCE(engine->props.heartbeat_पूर्णांकerval_ms);
पूर्ण

#पूर्ण_अगर /* _INTEL_RINGBUFFER_H_ */
