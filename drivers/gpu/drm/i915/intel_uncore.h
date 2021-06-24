<शैली गुरु>
/*
 * Copyright तऊ 2017 Intel Corporation
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
 */

#अगर_अघोषित __INTEL_UNCORE_H__
#घोषणा __INTEL_UNCORE_H__

#समावेश <linux/spinlock.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>

#समावेश "i915_reg.h"

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_runसमय_pm;
काष्ठा पूर्णांकel_uncore;
काष्ठा पूर्णांकel_gt;

काष्ठा पूर्णांकel_uncore_mmio_debug अणु
	spinlock_t lock; /** lock is also taken in irq contexts. */
	पूर्णांक unclaimed_mmio_check;
	पूर्णांक saved_mmio_check;
	u32 suspend_count;
पूर्ण;

क्रमागत क्रमcewake_करोमुख्य_id अणु
	FW_DOMAIN_ID_RENDER = 0,
	FW_DOMAIN_ID_GT,        /* also includes blitter engine */
	FW_DOMAIN_ID_MEDIA,
	FW_DOMAIN_ID_MEDIA_VDBOX0,
	FW_DOMAIN_ID_MEDIA_VDBOX1,
	FW_DOMAIN_ID_MEDIA_VDBOX2,
	FW_DOMAIN_ID_MEDIA_VDBOX3,
	FW_DOMAIN_ID_MEDIA_VEBOX0,
	FW_DOMAIN_ID_MEDIA_VEBOX1,

	FW_DOMAIN_ID_COUNT
पूर्ण;

क्रमागत क्रमcewake_करोमुख्यs अणु
	FORCEWAKE_RENDER	= BIT(FW_DOMAIN_ID_RENDER),
	FORCEWAKE_GT		= BIT(FW_DOMAIN_ID_GT),
	FORCEWAKE_MEDIA		= BIT(FW_DOMAIN_ID_MEDIA),
	FORCEWAKE_MEDIA_VDBOX0	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX0),
	FORCEWAKE_MEDIA_VDBOX1	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX1),
	FORCEWAKE_MEDIA_VDBOX2	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX2),
	FORCEWAKE_MEDIA_VDBOX3	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX3),
	FORCEWAKE_MEDIA_VEBOX0	= BIT(FW_DOMAIN_ID_MEDIA_VEBOX0),
	FORCEWAKE_MEDIA_VEBOX1	= BIT(FW_DOMAIN_ID_MEDIA_VEBOX1),

	FORCEWAKE_ALL = BIT(FW_DOMAIN_ID_COUNT) - 1
पूर्ण;

काष्ठा पूर्णांकel_uncore_funcs अणु
	व्योम (*क्रमce_wake_get)(काष्ठा पूर्णांकel_uncore *uncore,
			       क्रमागत क्रमcewake_करोमुख्यs करोमुख्यs);
	व्योम (*क्रमce_wake_put)(काष्ठा पूर्णांकel_uncore *uncore,
			       क्रमागत क्रमcewake_करोमुख्यs करोमुख्यs);

	क्रमागत क्रमcewake_करोमुख्यs (*पढ़ो_fw_करोमुख्यs)(काष्ठा पूर्णांकel_uncore *uncore,
						  i915_reg_t r);
	क्रमागत क्रमcewake_करोमुख्यs (*ग_लिखो_fw_करोमुख्यs)(काष्ठा पूर्णांकel_uncore *uncore,
						   i915_reg_t r);

	u8 (*mmio_पढ़ोb)(काष्ठा पूर्णांकel_uncore *uncore,
			 i915_reg_t r, bool trace);
	u16 (*mmio_पढ़ोw)(काष्ठा पूर्णांकel_uncore *uncore,
			  i915_reg_t r, bool trace);
	u32 (*mmio_पढ़ोl)(काष्ठा पूर्णांकel_uncore *uncore,
			  i915_reg_t r, bool trace);
	u64 (*mmio_पढ़ोq)(काष्ठा पूर्णांकel_uncore *uncore,
			  i915_reg_t r, bool trace);

	व्योम (*mmio_ग_लिखोb)(काष्ठा पूर्णांकel_uncore *uncore,
			    i915_reg_t r, u8 val, bool trace);
	व्योम (*mmio_ग_लिखोw)(काष्ठा पूर्णांकel_uncore *uncore,
			    i915_reg_t r, u16 val, bool trace);
	व्योम (*mmio_ग_लिखोl)(काष्ठा पूर्णांकel_uncore *uncore,
			    i915_reg_t r, u32 val, bool trace);
पूर्ण;

काष्ठा पूर्णांकel_क्रमcewake_range अणु
	u32 start;
	u32 end;

	क्रमागत क्रमcewake_करोमुख्यs करोमुख्यs;
पूर्ण;

काष्ठा पूर्णांकel_uncore अणु
	व्योम __iomem *regs;

	काष्ठा drm_i915_निजी *i915;
	काष्ठा पूर्णांकel_runसमय_pm *rpm;

	spinlock_t lock; /** lock is also taken in irq contexts. */

	अचिन्हित पूर्णांक flags;
#घोषणा UNCORE_HAS_FORCEWAKE		BIT(0)
#घोषणा UNCORE_HAS_FPGA_DBG_UNCLAIMED	BIT(1)
#घोषणा UNCORE_HAS_DBG_UNCLAIMED	BIT(2)
#घोषणा UNCORE_HAS_FIFO			BIT(3)

	स्थिर काष्ठा पूर्णांकel_क्रमcewake_range *fw_करोमुख्यs_table;
	अचिन्हित पूर्णांक fw_करोमुख्यs_table_entries;

	काष्ठा notअगरier_block pmic_bus_access_nb;
	काष्ठा पूर्णांकel_uncore_funcs funcs;

	अचिन्हित पूर्णांक fअगरo_count;

	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs;
	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs_active;
	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs_समयr;
	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs_saved; /* user करोमुख्यs saved क्रम S3 */

	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य अणु
		काष्ठा पूर्णांकel_uncore *uncore;
		क्रमागत क्रमcewake_करोमुख्य_id id;
		क्रमागत क्रमcewake_करोमुख्यs mask;
		अचिन्हित पूर्णांक wake_count;
		bool active;
		काष्ठा hrसमयr समयr;
		u32 __iomem *reg_set;
		u32 __iomem *reg_ack;
	पूर्ण *fw_करोमुख्य[FW_DOMAIN_ID_COUNT];

	अचिन्हित पूर्णांक user_क्रमcewake_count;

	काष्ठा पूर्णांकel_uncore_mmio_debug *debug;
पूर्ण;

/* Iterate over initialised fw करोमुख्यs */
#घोषणा क्रम_each_fw_करोमुख्य_masked(करोमुख्य__, mask__, uncore__, पंचांगp__) \
	क्रम (पंचांगp__ = (mask__); पंचांगp__ ;) \
		क्रम_each_अगर(करोमुख्य__ = (uncore__)->fw_करोमुख्य[__mask_next_bit(पंचांगp__)])

#घोषणा क्रम_each_fw_करोमुख्य(करोमुख्य__, uncore__, पंचांगp__) \
	क्रम_each_fw_करोमुख्य_masked(करोमुख्य__, (uncore__)->fw_करोमुख्यs, uncore__, पंचांगp__)

अटल अंतरभूत bool
पूर्णांकel_uncore_has_क्रमcewake(स्थिर काष्ठा पूर्णांकel_uncore *uncore)
अणु
	वापस uncore->flags & UNCORE_HAS_FORCEWAKE;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_uncore_has_fpga_dbg_unclaimed(स्थिर काष्ठा पूर्णांकel_uncore *uncore)
अणु
	वापस uncore->flags & UNCORE_HAS_FPGA_DBG_UNCLAIMED;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_uncore_has_dbg_unclaimed(स्थिर काष्ठा पूर्णांकel_uncore *uncore)
अणु
	वापस uncore->flags & UNCORE_HAS_DBG_UNCLAIMED;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_uncore_has_fअगरo(स्थिर काष्ठा पूर्णांकel_uncore *uncore)
अणु
	वापस uncore->flags & UNCORE_HAS_FIFO;
पूर्ण

व्योम
पूर्णांकel_uncore_mmio_debug_init_early(काष्ठा पूर्णांकel_uncore_mmio_debug *mmio_debug);
व्योम पूर्णांकel_uncore_init_early(काष्ठा पूर्णांकel_uncore *uncore,
			     काष्ठा drm_i915_निजी *i915);
पूर्णांक पूर्णांकel_uncore_init_mmio(काष्ठा पूर्णांकel_uncore *uncore);
व्योम पूर्णांकel_uncore_prune_engine_fw_करोमुख्यs(काष्ठा पूर्णांकel_uncore *uncore,
					  काष्ठा पूर्णांकel_gt *gt);
bool पूर्णांकel_uncore_unclaimed_mmio(काष्ठा पूर्णांकel_uncore *uncore);
bool पूर्णांकel_uncore_arm_unclaimed_mmio_detection(काष्ठा पूर्णांकel_uncore *uncore);
व्योम पूर्णांकel_uncore_fini_mmio(काष्ठा पूर्णांकel_uncore *uncore);
व्योम पूर्णांकel_uncore_suspend(काष्ठा पूर्णांकel_uncore *uncore);
व्योम पूर्णांकel_uncore_resume_early(काष्ठा पूर्णांकel_uncore *uncore);
व्योम पूर्णांकel_uncore_runसमय_resume(काष्ठा पूर्णांकel_uncore *uncore);

व्योम निश्चित_क्रमcewakes_inactive(काष्ठा पूर्णांकel_uncore *uncore);
व्योम निश्चित_क्रमcewakes_active(काष्ठा पूर्णांकel_uncore *uncore,
			      क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs);
स्थिर अक्षर *पूर्णांकel_uncore_क्रमcewake_करोमुख्य_to_str(स्थिर क्रमागत क्रमcewake_करोमुख्य_id id);

क्रमागत क्रमcewake_करोमुख्यs
पूर्णांकel_uncore_क्रमcewake_क्रम_reg(काष्ठा पूर्णांकel_uncore *uncore,
			       i915_reg_t reg, अचिन्हित पूर्णांक op);
#घोषणा FW_REG_READ  (1)
#घोषणा FW_REG_WRITE (2)

व्योम पूर्णांकel_uncore_क्रमcewake_get(काष्ठा पूर्णांकel_uncore *uncore,
				क्रमागत क्रमcewake_करोमुख्यs करोमुख्यs);
व्योम पूर्णांकel_uncore_क्रमcewake_put(काष्ठा पूर्णांकel_uncore *uncore,
				क्रमागत क्रमcewake_करोमुख्यs करोमुख्यs);
व्योम पूर्णांकel_uncore_क्रमcewake_flush(काष्ठा पूर्णांकel_uncore *uncore,
				  क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs);

/*
 * Like above but the caller must manage the uncore.lock itself.
 * Must be used with पूर्णांकel_uncore_पढ़ो_fw() and मित्रs.
 */
व्योम पूर्णांकel_uncore_क्रमcewake_get__locked(काष्ठा पूर्णांकel_uncore *uncore,
					क्रमागत क्रमcewake_करोमुख्यs करोमुख्यs);
व्योम पूर्णांकel_uncore_क्रमcewake_put__locked(काष्ठा पूर्णांकel_uncore *uncore,
					क्रमागत क्रमcewake_करोमुख्यs करोमुख्यs);

व्योम पूर्णांकel_uncore_क्रमcewake_user_get(काष्ठा पूर्णांकel_uncore *uncore);
व्योम पूर्णांकel_uncore_क्रमcewake_user_put(काष्ठा पूर्णांकel_uncore *uncore);

पूर्णांक __पूर्णांकel_रुको_क्रम_रेजिस्टर(काष्ठा पूर्णांकel_uncore *uncore,
			      i915_reg_t reg,
			      u32 mask,
			      u32 value,
			      अचिन्हित पूर्णांक fast_समयout_us,
			      अचिन्हित पूर्णांक slow_समयout_ms,
			      u32 *out_value);
अटल अंतरभूत पूर्णांक
पूर्णांकel_रुको_क्रम_रेजिस्टर(काष्ठा पूर्णांकel_uncore *uncore,
			i915_reg_t reg,
			u32 mask,
			u32 value,
			अचिन्हित पूर्णांक समयout_ms)
अणु
	वापस __पूर्णांकel_रुको_क्रम_रेजिस्टर(uncore, reg, mask, value, 2,
					 समयout_ms, शून्य);
पूर्ण

पूर्णांक __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(काष्ठा पूर्णांकel_uncore *uncore,
				 i915_reg_t reg,
				 u32 mask,
				 u32 value,
				 अचिन्हित पूर्णांक fast_समयout_us,
				 अचिन्हित पूर्णांक slow_समयout_ms,
				 u32 *out_value);
अटल अंतरभूत पूर्णांक
पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(काष्ठा पूर्णांकel_uncore *uncore,
			   i915_reg_t reg,
			   u32 mask,
			   u32 value,
			       अचिन्हित पूर्णांक समयout_ms)
अणु
	वापस __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore, reg, mask, value,
					    2, समयout_ms, शून्य);
पूर्ण

/* रेजिस्टर access functions */
#घोषणा __raw_पढ़ो(x__, s__) \
अटल अंतरभूत u##x__ __raw_uncore_पढ़ो##x__(स्थिर काष्ठा पूर्णांकel_uncore *uncore, \
					    i915_reg_t reg) \
अणु \
	वापस पढ़ो##s__(uncore->regs + i915_mmio_reg_offset(reg)); \
पूर्ण

#घोषणा __raw_ग_लिखो(x__, s__) \
अटल अंतरभूत व्योम __raw_uncore_ग_लिखो##x__(स्थिर काष्ठा पूर्णांकel_uncore *uncore, \
					   i915_reg_t reg, u##x__ val) \
अणु \
	ग_लिखो##s__(val, uncore->regs + i915_mmio_reg_offset(reg)); \
पूर्ण
__raw_पढ़ो(8, b)
__raw_पढ़ो(16, w)
__raw_पढ़ो(32, l)
__raw_पढ़ो(64, q)

__raw_ग_लिखो(8, b)
__raw_ग_लिखो(16, w)
__raw_ग_लिखो(32, l)
__raw_ग_लिखो(64, q)

#अघोषित __raw_पढ़ो
#अघोषित __raw_ग_लिखो

#घोषणा __uncore_पढ़ो(name__, x__, s__, trace__) \
अटल अंतरभूत u##x__ पूर्णांकel_uncore_##name__(काष्ठा पूर्णांकel_uncore *uncore, \
					   i915_reg_t reg) \
अणु \
	वापस uncore->funcs.mmio_पढ़ो##s__(uncore, reg, (trace__)); \
पूर्ण

#घोषणा __uncore_ग_लिखो(name__, x__, s__, trace__) \
अटल अंतरभूत व्योम पूर्णांकel_uncore_##name__(काष्ठा पूर्णांकel_uncore *uncore, \
					 i915_reg_t reg, u##x__ val) \
अणु \
	uncore->funcs.mmio_ग_लिखो##s__(uncore, reg, val, (trace__)); \
पूर्ण

__uncore_पढ़ो(पढ़ो8, 8, b, true)
__uncore_पढ़ो(पढ़ो16, 16, w, true)
__uncore_पढ़ो(पढ़ो, 32, l, true)
__uncore_पढ़ो(पढ़ो16_notrace, 16, w, false)
__uncore_पढ़ो(पढ़ो_notrace, 32, l, false)

__uncore_ग_लिखो(ग_लिखो8, 8, b, true)
__uncore_ग_लिखो(ग_लिखो16, 16, w, true)
__uncore_ग_लिखो(ग_लिखो, 32, l, true)
__uncore_ग_लिखो(ग_लिखो_notrace, 32, l, false)

/* Be very careful with पढ़ो/ग_लिखो 64-bit values. On 32-bit machines, they
 * will be implemented using 2 32-bit ग_लिखोs in an arbitrary order with
 * an arbitrary delay between them. This can cause the hardware to
 * act upon the पूर्णांकermediate value, possibly leading to corruption and
 * machine death. For this reason we करो not support पूर्णांकel_uncore_ग_लिखो64,
 * or uncore->funcs.mmio_ग_लिखोq.
 *
 * When पढ़ोing a 64-bit value as two 32-bit values, the delay may cause
 * the two पढ़ोs to mismatch, e.g. a बारtamp overflowing. Also note that
 * occasionally a 64-bit रेजिस्टर करोes not actually support a full पढ़ोq
 * and must be पढ़ो using two 32-bit पढ़ोs.
 *
 * You have been warned.
 */
__uncore_पढ़ो(पढ़ो64, 64, q, true)

अटल अंतरभूत u64
पूर्णांकel_uncore_पढ़ो64_2x32(काष्ठा पूर्णांकel_uncore *uncore,
			 i915_reg_t lower_reg, i915_reg_t upper_reg)
अणु
	u32 upper, lower, old_upper, loop = 0;
	upper = पूर्णांकel_uncore_पढ़ो(uncore, upper_reg);
	करो अणु
		old_upper = upper;
		lower = पूर्णांकel_uncore_पढ़ो(uncore, lower_reg);
		upper = पूर्णांकel_uncore_पढ़ो(uncore, upper_reg);
	पूर्ण जबतक (upper != old_upper && loop++ < 2);
	वापस (u64)upper << 32 | lower;
पूर्ण

#घोषणा पूर्णांकel_uncore_posting_पढ़ो(...) ((व्योम)पूर्णांकel_uncore_पढ़ो_notrace(__VA_ARGS__))
#घोषणा पूर्णांकel_uncore_posting_पढ़ो16(...) ((व्योम)पूर्णांकel_uncore_पढ़ो16_notrace(__VA_ARGS__))

#अघोषित __uncore_पढ़ो
#अघोषित __uncore_ग_लिखो

/* These are untraced mmio-accessors that are only valid to be used inside
 * critical sections, such as inside IRQ handlers, where क्रमcewake is explicitly
 * controlled.
 *
 * Think twice, and think again, beक्रमe using these.
 *
 * As an example, these accessors can possibly be used between:
 *
 * spin_lock_irq(&uncore->lock);
 * पूर्णांकel_uncore_क्रमcewake_get__locked();
 *
 * and
 *
 * पूर्णांकel_uncore_क्रमcewake_put__locked();
 * spin_unlock_irq(&uncore->lock);
 *
 *
 * Note: some रेजिस्टरs may not need क्रमcewake held, so
 * पूर्णांकel_uncore_क्रमcewake_अणुget,putपूर्ण can be omitted, see
 * पूर्णांकel_uncore_क्रमcewake_क्रम_reg().
 *
 * Certain architectures will die अगर the same cacheline is concurrently accessed
 * by dअगरferent clients (e.g. on Ivybridge). Access to रेजिस्टरs should
 * thereक्रमe generally be serialised, by either the dev_priv->uncore.lock or
 * a more localised lock guarding all access to that bank of रेजिस्टरs.
 */
#घोषणा पूर्णांकel_uncore_पढ़ो_fw(...) __raw_uncore_पढ़ो32(__VA_ARGS__)
#घोषणा पूर्णांकel_uncore_ग_लिखो_fw(...) __raw_uncore_ग_लिखो32(__VA_ARGS__)
#घोषणा पूर्णांकel_uncore_ग_लिखो64_fw(...) __raw_uncore_ग_लिखो64(__VA_ARGS__)
#घोषणा पूर्णांकel_uncore_posting_पढ़ो_fw(...) ((व्योम)पूर्णांकel_uncore_पढ़ो_fw(__VA_ARGS__))

अटल अंतरभूत व्योम पूर्णांकel_uncore_rmw(काष्ठा पूर्णांकel_uncore *uncore,
				    i915_reg_t reg, u32 clear, u32 set)
अणु
	u32 old, val;

	old = पूर्णांकel_uncore_पढ़ो(uncore, reg);
	val = (old & ~clear) | set;
	अगर (val != old)
		पूर्णांकel_uncore_ग_लिखो(uncore, reg, val);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_uncore_rmw_fw(काष्ठा पूर्णांकel_uncore *uncore,
				       i915_reg_t reg, u32 clear, u32 set)
अणु
	u32 old, val;

	old = पूर्णांकel_uncore_पढ़ो_fw(uncore, reg);
	val = (old & ~clear) | set;
	अगर (val != old)
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_uncore_ग_लिखो_and_verअगरy(काष्ठा पूर्णांकel_uncore *uncore,
						i915_reg_t reg, u32 val,
						u32 mask, u32 expected_val)
अणु
	u32 reg_val;

	पूर्णांकel_uncore_ग_लिखो(uncore, reg, val);
	reg_val = पूर्णांकel_uncore_पढ़ो(uncore, reg);

	वापस (reg_val & mask) != expected_val ? -EINVAL : 0;
पूर्ण

#घोषणा raw_reg_पढ़ो(base, reg) \
	पढ़ोl(base + i915_mmio_reg_offset(reg))
#घोषणा raw_reg_ग_लिखो(base, reg, value) \
	ग_लिखोl(value, base + i915_mmio_reg_offset(reg))

#पूर्ण_अगर /* !__INTEL_UNCORE_H__ */
