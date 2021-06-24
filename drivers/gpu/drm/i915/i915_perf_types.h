<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित _I915_PERF_TYPES_H_
#घोषणा _I915_PERF_TYPES_H_

#समावेश <linux/atomic.h>
#समावेश <linux/device.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/llist.h>
#समावेश <linux/poll.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/uuid.h>
#समावेश <linux/रुको.h>
#समावेश <uapi/drm/i915_drm.h>

#समावेश "gt/intel_sseu.h"
#समावेश "i915_reg.h"
#समावेश "intel_wakeref.h"

काष्ठा drm_i915_निजी;
काष्ठा file;
काष्ठा i915_active;
काष्ठा i915_gem_context;
काष्ठा i915_perf;
काष्ठा i915_vma;
काष्ठा पूर्णांकel_context;
काष्ठा पूर्णांकel_engine_cs;

काष्ठा i915_oa_क्रमmat अणु
	u32 क्रमmat;
	पूर्णांक size;
पूर्ण;

काष्ठा i915_oa_reg अणु
	i915_reg_t addr;
	u32 value;
पूर्ण;

काष्ठा i915_oa_config अणु
	काष्ठा i915_perf *perf;

	अक्षर uuid[UUID_STRING_LEN + 1];
	पूर्णांक id;

	स्थिर काष्ठा i915_oa_reg *mux_regs;
	u32 mux_regs_len;
	स्थिर काष्ठा i915_oa_reg *b_counter_regs;
	u32 b_counter_regs_len;
	स्थिर काष्ठा i915_oa_reg *flex_regs;
	u32 flex_regs_len;

	काष्ठा attribute_group sysfs_metric;
	काष्ठा attribute *attrs[2];
	काष्ठा device_attribute sysfs_metric_id;

	काष्ठा kref ref;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा i915_perf_stream;

/**
 * काष्ठा i915_perf_stream_ops - the OPs to support a specअगरic stream type
 */
काष्ठा i915_perf_stream_ops अणु
	/**
	 * @enable: Enables the collection of HW samples, either in response to
	 * `I915_PERF_IOCTL_ENABLE` or implicitly called when stream is खोलोed
	 * without `I915_PERF_FLAG_DISABLED`.
	 */
	व्योम (*enable)(काष्ठा i915_perf_stream *stream);

	/**
	 * @disable: Disables the collection of HW samples, either in response
	 * to `I915_PERF_IOCTL_DISABLE` or implicitly called beक्रमe destroying
	 * the stream.
	 */
	व्योम (*disable)(काष्ठा i915_perf_stream *stream);

	/**
	 * @poll_रुको: Call poll_रुको, passing a रुको queue that will be woken
	 * once there is something पढ़ोy to पढ़ो() क्रम the stream
	 */
	व्योम (*poll_रुको)(काष्ठा i915_perf_stream *stream,
			  काष्ठा file *file,
			  poll_table *रुको);

	/**
	 * @रुको_unlocked: For handling a blocking पढ़ो, रुको until there is
	 * something to पढ़ोy to पढ़ो() क्रम the stream. E.g. रुको on the same
	 * रुको queue that would be passed to poll_रुको().
	 */
	पूर्णांक (*रुको_unlocked)(काष्ठा i915_perf_stream *stream);

	/**
	 * @पढ़ो: Copy buffered metrics as records to userspace
	 * **buf**: the userspace, destination buffer
	 * **count**: the number of bytes to copy, requested by userspace
	 * **offset**: zero at the start of the पढ़ो, updated as the पढ़ो
	 * proceeds, it represents how many bytes have been copied so far and
	 * the buffer offset क्रम copying the next record.
	 *
	 * Copy as many buffered i915 perf samples and records क्रम this stream
	 * to userspace as will fit in the given buffer.
	 *
	 * Only ग_लिखो complete records; वापसing -%ENOSPC अगर there isn't room
	 * क्रम a complete record.
	 *
	 * Return any error condition that results in a लघु पढ़ो such as
	 * -%ENOSPC or -%EFAULT, even though these may be squashed beक्रमe
	 * वापसing to userspace.
	 */
	पूर्णांक (*पढ़ो)(काष्ठा i915_perf_stream *stream,
		    अक्षर __user *buf,
		    माप_प्रकार count,
		    माप_प्रकार *offset);

	/**
	 * @destroy: Cleanup any stream specअगरic resources.
	 *
	 * The stream will always be disabled beक्रमe this is called.
	 */
	व्योम (*destroy)(काष्ठा i915_perf_stream *stream);
पूर्ण;

/**
 * काष्ठा i915_perf_stream - state क्रम a single खोलो stream FD
 */
काष्ठा i915_perf_stream अणु
	/**
	 * @perf: i915_perf backpoपूर्णांकer
	 */
	काष्ठा i915_perf *perf;

	/**
	 * @uncore: mmio access path
	 */
	काष्ठा पूर्णांकel_uncore *uncore;

	/**
	 * @engine: Engine associated with this perक्रमmance stream.
	 */
	काष्ठा पूर्णांकel_engine_cs *engine;

	/**
	 * @sample_flags: Flags representing the `DRM_I915_PERF_PROP_SAMPLE_*`
	 * properties given when खोलोing a stream, representing the contents
	 * of a single sample as पढ़ो() by userspace.
	 */
	u32 sample_flags;

	/**
	 * @sample_size: Considering the configured contents of a sample
	 * combined with the required header size, this is the total size
	 * of a single sample record.
	 */
	पूर्णांक sample_size;

	/**
	 * @ctx: %शून्य अगर measuring प्रणाली-wide across all contexts or a
	 * specअगरic context that is being monitored.
	 */
	काष्ठा i915_gem_context *ctx;

	/**
	 * @enabled: Whether the stream is currently enabled, considering
	 * whether the stream was खोलोed in a disabled state and based
	 * on `I915_PERF_IOCTL_ENABLE` and `I915_PERF_IOCTL_DISABLE` calls.
	 */
	bool enabled;

	/**
	 * @hold_preemption: Whether preemption is put on hold क्रम command
	 * submissions करोne on the @ctx. This is useful क्रम some drivers that
	 * cannot easily post process the OA buffer context to subtract delta
	 * of perक्रमmance counters not associated with @ctx.
	 */
	bool hold_preemption;

	/**
	 * @ops: The callbacks providing the implementation of this specअगरic
	 * type of configured stream.
	 */
	स्थिर काष्ठा i915_perf_stream_ops *ops;

	/**
	 * @oa_config: The OA configuration used by the stream.
	 */
	काष्ठा i915_oa_config *oa_config;

	/**
	 * @oa_config_bos: A list of काष्ठा i915_oa_config_bo allocated lazily
	 * each समय @oa_config changes.
	 */
	काष्ठा llist_head oa_config_bos;

	/**
	 * @pinned_ctx: The OA context specअगरic inक्रमmation.
	 */
	काष्ठा पूर्णांकel_context *pinned_ctx;

	/**
	 * @specअगरic_ctx_id: The id of the specअगरic context.
	 */
	u32 specअगरic_ctx_id;

	/**
	 * @specअगरic_ctx_id_mask: The mask used to masking specअगरic_ctx_id bits.
	 */
	u32 specअगरic_ctx_id_mask;

	/**
	 * @poll_check_समयr: High resolution समयr that will periodically
	 * check क्रम data in the circular OA buffer क्रम notअगरying userspace
	 * (e.g. during a पढ़ो() or poll()).
	 */
	काष्ठा hrसमयr poll_check_समयr;

	/**
	 * @poll_wq: The रुको queue that hrसमयr callback wakes when it
	 * sees data पढ़ोy to पढ़ो in the circular OA buffer.
	 */
	रुको_queue_head_t poll_wq;

	/**
	 * @pollin: Whether there is data available to पढ़ो.
	 */
	bool pollin;

	/**
	 * @periodic: Whether periodic sampling is currently enabled.
	 */
	bool periodic;

	/**
	 * @period_exponent: The OA unit sampling frequency is derived from this.
	 */
	पूर्णांक period_exponent;

	/**
	 * @oa_buffer: State of the OA buffer.
	 */
	काष्ठा अणु
		काष्ठा i915_vma *vma;
		u8 *vaddr;
		u32 last_ctx_id;
		पूर्णांक क्रमmat;
		पूर्णांक क्रमmat_size;
		पूर्णांक size_exponent;

		/**
		 * @ptr_lock: Locks पढ़ोs and ग_लिखोs to all head/tail state
		 *
		 * Consider: the head and tail poपूर्णांकer state needs to be पढ़ो
		 * consistently from a hrसमयr callback (atomic context) and
		 * पढ़ो() fop (user context) with tail poपूर्णांकer updates happening
		 * in atomic context and head updates in user context and the
		 * (unlikely) possibility of पढ़ो() errors needing to reset all
		 * head/tail state.
		 *
		 * Note: Contention/perक्रमmance aren't currently a signअगरicant
		 * concern here considering the relatively low frequency of
		 * hrसमयr callbacks (5ms period) and that पढ़ोs typically only
		 * happen in response to a hrसमयr event and likely complete
		 * beक्रमe the next callback.
		 *
		 * Note: This lock is not held *जबतक* पढ़ोing and copying data
		 * to userspace so the value of head observed in htrimer
		 * callbacks won't represent any partial consumption of data.
		 */
		spinlock_t ptr_lock;

		/**
		 * @aging_tail: The last HW tail reported by HW. The data
		 * might not have made it to memory yet though.
		 */
		u32 aging_tail;

		/**
		 * @aging_बारtamp: A monotonic बारtamp क्रम when the current aging tail poपूर्णांकer
		 * was पढ़ो; used to determine when it is old enough to trust.
		 */
		u64 aging_बारtamp;

		/**
		 * @head: Although we can always पढ़ो back the head poपूर्णांकer रेजिस्टर,
		 * we prefer to aव्योम trusting the HW state, just to aव्योम any
		 * risk that some hardware condition could * somehow bump the
		 * head poपूर्णांकer unpredictably and cause us to क्रमward the wrong
		 * OA buffer data to userspace.
		 */
		u32 head;

		/**
		 * @tail: The last verअगरied tail that can be पढ़ो by userspace.
		 */
		u32 tail;
	पूर्ण oa_buffer;

	/**
	 * @noa_रुको: A batch buffer करोing a रुको on the GPU क्रम the NOA logic to be
	 * reprogrammed.
	 */
	काष्ठा i915_vma *noa_रुको;

	/**
	 * @poll_oa_period: The period in nanoseconds at which the OA
	 * buffer should be checked क्रम available data.
	 */
	u64 poll_oa_period;
पूर्ण;

/**
 * काष्ठा i915_oa_ops - Gen specअगरic implementation of an OA unit stream
 */
काष्ठा i915_oa_ops अणु
	/**
	 * @is_valid_b_counter_reg: Validates रेजिस्टर's address क्रम
	 * programming boolean counters क्रम a particular platक्रमm.
	 */
	bool (*is_valid_b_counter_reg)(काष्ठा i915_perf *perf, u32 addr);

	/**
	 * @is_valid_mux_reg: Validates रेजिस्टर's address क्रम programming mux
	 * क्रम a particular platक्रमm.
	 */
	bool (*is_valid_mux_reg)(काष्ठा i915_perf *perf, u32 addr);

	/**
	 * @is_valid_flex_reg: Validates रेजिस्टर's address क्रम programming
	 * flex EU filtering क्रम a particular platक्रमm.
	 */
	bool (*is_valid_flex_reg)(काष्ठा i915_perf *perf, u32 addr);

	/**
	 * @enable_metric_set: Selects and applies any MUX configuration to set
	 * up the Boolean and Custom (B/C) counters that are part of the
	 * counter reports being sampled. May apply प्रणाली स्थिरraपूर्णांकs such as
	 * disabling EU घड़ी gating as required.
	 */
	पूर्णांक (*enable_metric_set)(काष्ठा i915_perf_stream *stream,
				 काष्ठा i915_active *active);

	/**
	 * @disable_metric_set: Remove प्रणाली स्थिरraपूर्णांकs associated with using
	 * the OA unit.
	 */
	व्योम (*disable_metric_set)(काष्ठा i915_perf_stream *stream);

	/**
	 * @oa_enable: Enable periodic sampling
	 */
	व्योम (*oa_enable)(काष्ठा i915_perf_stream *stream);

	/**
	 * @oa_disable: Disable periodic sampling
	 */
	व्योम (*oa_disable)(काष्ठा i915_perf_stream *stream);

	/**
	 * @पढ़ो: Copy data from the circular OA buffer पूर्णांकo a given userspace
	 * buffer.
	 */
	पूर्णांक (*पढ़ो)(काष्ठा i915_perf_stream *stream,
		    अक्षर __user *buf,
		    माप_प्रकार count,
		    माप_प्रकार *offset);

	/**
	 * @oa_hw_tail_पढ़ो: पढ़ो the OA tail poपूर्णांकer रेजिस्टर
	 *
	 * In particular this enables us to share all the fiddly code क्रम
	 * handling the OA unit tail poपूर्णांकer race that affects multiple
	 * generations.
	 */
	u32 (*oa_hw_tail_पढ़ो)(काष्ठा i915_perf_stream *stream);
पूर्ण;

काष्ठा i915_perf अणु
	काष्ठा drm_i915_निजी *i915;

	काष्ठा kobject *metrics_kobj;

	/*
	 * Lock associated with adding/modअगरying/removing OA configs
	 * in perf->metrics_idr.
	 */
	काष्ठा mutex metrics_lock;

	/*
	 * List of dynamic configurations (काष्ठा i915_oa_config), you
	 * need to hold perf->metrics_lock to access it.
	 */
	काष्ठा idr metrics_idr;

	/*
	 * Lock associated with anything below within this काष्ठाure
	 * except exclusive_stream.
	 */
	काष्ठा mutex lock;

	/*
	 * The stream currently using the OA unit. If accessed
	 * outside a syscall associated to its file
	 * descriptor.
	 */
	काष्ठा i915_perf_stream *exclusive_stream;

	/**
	 * @sseu: sseu configuration selected to run जबतक perf is active,
	 * applies to all contexts.
	 */
	काष्ठा पूर्णांकel_sseu sseu;

	/**
	 * For rate limiting any notअगरications of spurious
	 * invalid OA reports
	 */
	काष्ठा ratelimit_state spurious_report_rs;

	/**
	 * For rate limiting any notअगरications of tail poपूर्णांकer
	 * race.
	 */
	काष्ठा ratelimit_state tail_poपूर्णांकer_race;

	u32 gen7_latched_oastatus1;
	u32 ctx_oactxctrl_offset;
	u32 ctx_flexeu0_offset;

	/**
	 * The RPT_ID/reason field क्रम Gen8+ includes a bit
	 * to determine अगर the CTX ID in the report is valid
	 * but the specअगरic bit dअगरfers between Gen 8 and 9
	 */
	u32 gen8_valid_ctx_bit;

	काष्ठा i915_oa_ops ops;
	स्थिर काष्ठा i915_oa_क्रमmat *oa_क्रमmats;

	/**
	 * Use a क्रमmat mask to store the supported क्रमmats
	 * क्रम a platक्रमm.
	 */
#घोषणा FORMAT_MASK_SIZE DIV_ROUND_UP(I915_OA_FORMAT_MAX - 1, BITS_PER_LONG)
	अचिन्हित दीर्घ क्रमmat_mask[FORMAT_MASK_SIZE];

	atomic64_t noa_programming_delay;
पूर्ण;

#पूर्ण_अगर /* _I915_PERF_TYPES_H_ */
