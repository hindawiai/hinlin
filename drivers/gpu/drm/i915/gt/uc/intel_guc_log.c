<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#समावेश <linux/debugfs.h>

#समावेश "gt/intel_gt.h"
#समावेश "i915_drv.h"
#समावेश "i915_memcpy.h"
#समावेश "intel_guc_log.h"

अटल व्योम guc_log_capture_logs(काष्ठा पूर्णांकel_guc_log *log);

/**
 * DOC: GuC firmware log
 *
 * Firmware log is enabled by setting i915.guc_log_level to the positive level.
 * Log data is prपूर्णांकed out via पढ़ोing debugfs i915_guc_log_dump. Reading from
 * i915_guc_load_status will prपूर्णांक out firmware loading status and scratch
 * रेजिस्टरs value.
 */

अटल पूर्णांक guc_action_flush_log_complete(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 action[] = अणु
		INTEL_GUC_ACTION_LOG_BUFFER_खाता_FLUSH_COMPLETE
	पूर्ण;

	वापस पूर्णांकel_guc_send(guc, action, ARRAY_SIZE(action));
पूर्ण

अटल पूर्णांक guc_action_flush_log(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 action[] = अणु
		INTEL_GUC_ACTION_FORCE_LOG_BUFFER_FLUSH,
		0
	पूर्ण;

	वापस पूर्णांकel_guc_send(guc, action, ARRAY_SIZE(action));
पूर्ण

अटल पूर्णांक guc_action_control_log(काष्ठा पूर्णांकel_guc *guc, bool enable,
				  bool शेष_logging, u32 verbosity)
अणु
	u32 action[] = अणु
		INTEL_GUC_ACTION_UK_LOG_ENABLE_LOGGING,
		(enable ? GUC_LOG_CONTROL_LOGGING_ENABLED : 0) |
		(verbosity << GUC_LOG_CONTROL_VERBOSITY_SHIFT) |
		(शेष_logging ? GUC_LOG_CONTROL_DEFAULT_LOGGING : 0)
	पूर्ण;

	GEM_BUG_ON(verbosity > GUC_LOG_VERBOSITY_MAX);

	वापस पूर्णांकel_guc_send(guc, action, ARRAY_SIZE(action));
पूर्ण

अटल व्योम guc_log_enable_flush_events(काष्ठा पूर्णांकel_guc_log *log)
अणु
	पूर्णांकel_guc_enable_msg(log_to_guc(log),
			     INTEL_GUC_RECV_MSG_FLUSH_LOG_BUFFER |
			     INTEL_GUC_RECV_MSG_CRASH_DUMP_POSTED);
पूर्ण

अटल व्योम guc_log_disable_flush_events(काष्ठा पूर्णांकel_guc_log *log)
अणु
	पूर्णांकel_guc_disable_msg(log_to_guc(log),
			      INTEL_GUC_RECV_MSG_FLUSH_LOG_BUFFER |
			      INTEL_GUC_RECV_MSG_CRASH_DUMP_POSTED);
पूर्ण

/*
 * Sub buffer चयन callback. Called whenever relay has to चयन to a new
 * sub buffer, relay stays on the same sub buffer अगर 0 is वापसed.
 */
अटल पूर्णांक subbuf_start_callback(काष्ठा rchan_buf *buf,
				 व्योम *subbuf,
				 व्योम *prev_subbuf,
				 माप_प्रकार prev_padding)
अणु
	/*
	 * Use no-overग_लिखो mode by शेष, where relay will stop accepting
	 * new data अगर there are no empty sub buffers left.
	 * There is no strict synchronization enक्रमced by relay between Consumer
	 * and Producer. In overग_लिखो mode, there is a possibility of getting
	 * inconsistent/garbled data, the producer could be writing on to the
	 * same sub buffer from which Consumer is पढ़ोing. This can't be aव्योमed
	 * unless Consumer is fast enough and can always run in tandem with
	 * Producer.
	 */
	अगर (relay_buf_full(buf))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * file_create() callback. Creates relay file in debugfs.
 */
अटल काष्ठा dentry *create_buf_file_callback(स्थिर अक्षर *filename,
					       काष्ठा dentry *parent,
					       umode_t mode,
					       काष्ठा rchan_buf *buf,
					       पूर्णांक *is_global)
अणु
	काष्ठा dentry *buf_file;

	/*
	 * This to enable the use of a single buffer क्रम the relay channel and
	 * correspondingly have a single file exposed to User, through which
	 * it can collect the logs in order without any post-processing.
	 * Need to set 'is_global' even अगर parent is शून्य क्रम early logging.
	 */
	*is_global = 1;

	अगर (!parent)
		वापस शून्य;

	buf_file = debugfs_create_file(filename, mode,
				       parent, buf, &relay_file_operations);
	अगर (IS_ERR(buf_file))
		वापस शून्य;

	वापस buf_file;
पूर्ण

/*
 * file_हटाओ() शेष callback. Removes relay file in debugfs.
 */
अटल पूर्णांक हटाओ_buf_file_callback(काष्ठा dentry *dentry)
अणु
	debugfs_हटाओ(dentry);
	वापस 0;
पूर्ण

/* relay channel callbacks */
अटल स्थिर काष्ठा rchan_callbacks relay_callbacks = अणु
	.subbuf_start = subbuf_start_callback,
	.create_buf_file = create_buf_file_callback,
	.हटाओ_buf_file = हटाओ_buf_file_callback,
पूर्ण;

अटल व्योम guc_move_to_next_buf(काष्ठा पूर्णांकel_guc_log *log)
अणु
	/*
	 * Make sure the updates made in the sub buffer are visible when
	 * Consumer sees the following update to offset inside the sub buffer.
	 */
	smp_wmb();

	/* All data has been written, so now move the offset of sub buffer. */
	relay_reserve(log->relay.channel, log->vma->obj->base.size);

	/* Switch to the next sub buffer */
	relay_flush(log->relay.channel);
पूर्ण

अटल व्योम *guc_get_ग_लिखो_buffer(काष्ठा पूर्णांकel_guc_log *log)
अणु
	/*
	 * Just get the base address of a new sub buffer and copy data पूर्णांकo it
	 * ourselves. शून्य will be वापसed in no-overग_लिखो mode, अगर all sub
	 * buffers are full. Could have used the relay_ग_लिखो() to indirectly
	 * copy the data, but that would have been bit convoluted, as we need to
	 * ग_लिखो to only certain locations inside a sub buffer which cannot be
	 * करोne without using relay_reserve() aदीर्घ with relay_ग_लिखो(). So its
	 * better to use relay_reserve() alone.
	 */
	वापस relay_reserve(log->relay.channel, 0);
पूर्ण

अटल bool guc_check_log_buf_overflow(काष्ठा पूर्णांकel_guc_log *log,
				       क्रमागत guc_log_buffer_type type,
				       अचिन्हित पूर्णांक full_cnt)
अणु
	अचिन्हित पूर्णांक prev_full_cnt = log->stats[type].sampled_overflow;
	bool overflow = false;

	अगर (full_cnt != prev_full_cnt) अणु
		overflow = true;

		log->stats[type].overflow = full_cnt;
		log->stats[type].sampled_overflow += full_cnt - prev_full_cnt;

		अगर (full_cnt < prev_full_cnt) अणु
			/* buffer_full_cnt is a 4 bit counter */
			log->stats[type].sampled_overflow += 16;
		पूर्ण

		dev_notice_ratelimited(guc_to_gt(log_to_guc(log))->i915->drm.dev,
				       "GuC log buffer overflow\n");
	पूर्ण

	वापस overflow;
पूर्ण

अटल अचिन्हित पूर्णांक guc_get_log_buffer_size(क्रमागत guc_log_buffer_type type)
अणु
	चयन (type) अणु
	हाल GUC_ISR_LOG_BUFFER:
		वापस ISR_BUFFER_SIZE;
	हाल GUC_DPC_LOG_BUFFER:
		वापस DPC_BUFFER_SIZE;
	हाल GUC_CRASH_DUMP_LOG_BUFFER:
		वापस CRASH_BUFFER_SIZE;
	शेष:
		MISSING_CASE(type);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम guc_पढ़ो_update_log_buffer(काष्ठा पूर्णांकel_guc_log *log)
अणु
	अचिन्हित पूर्णांक buffer_size, पढ़ो_offset, ग_लिखो_offset, bytes_to_copy, full_cnt;
	काष्ठा guc_log_buffer_state *log_buf_state, *log_buf_snapshot_state;
	काष्ठा guc_log_buffer_state log_buf_state_local;
	क्रमागत guc_log_buffer_type type;
	व्योम *src_data, *dst_data;
	bool new_overflow;

	mutex_lock(&log->relay.lock);

	अगर (WARN_ON(!पूर्णांकel_guc_log_relay_created(log)))
		जाओ out_unlock;

	/* Get the poपूर्णांकer to shared GuC log buffer */
	log_buf_state = src_data = log->relay.buf_addr;

	/* Get the poपूर्णांकer to local buffer to store the logs */
	log_buf_snapshot_state = dst_data = guc_get_ग_लिखो_buffer(log);

	अगर (unlikely(!log_buf_snapshot_state)) अणु
		/*
		 * Used rate limited to aव्योम deluge of messages, logs might be
		 * getting consumed by User at a slow rate.
		 */
		DRM_ERROR_RATELIMITED("no sub-buffer to capture logs\n");
		log->relay.full_count++;

		जाओ out_unlock;
	पूर्ण

	/* Actual logs are present from the 2nd page */
	src_data += PAGE_SIZE;
	dst_data += PAGE_SIZE;

	क्रम (type = GUC_ISR_LOG_BUFFER; type < GUC_MAX_LOG_BUFFER; type++) अणु
		/*
		 * Make a copy of the state काष्ठाure, inside GuC log buffer
		 * (which is uncached mapped), on the stack to aव्योम पढ़ोing
		 * from it multiple बार.
		 */
		स_नकल(&log_buf_state_local, log_buf_state,
		       माप(काष्ठा guc_log_buffer_state));
		buffer_size = guc_get_log_buffer_size(type);
		पढ़ो_offset = log_buf_state_local.पढ़ो_ptr;
		ग_लिखो_offset = log_buf_state_local.sampled_ग_लिखो_ptr;
		full_cnt = log_buf_state_local.buffer_full_cnt;

		/* Bookkeeping stuff */
		log->stats[type].flush += log_buf_state_local.flush_to_file;
		new_overflow = guc_check_log_buf_overflow(log, type, full_cnt);

		/* Update the state of shared log buffer */
		log_buf_state->पढ़ो_ptr = ग_लिखो_offset;
		log_buf_state->flush_to_file = 0;
		log_buf_state++;

		/* First copy the state काष्ठाure in snapshot buffer */
		स_नकल(log_buf_snapshot_state, &log_buf_state_local,
		       माप(काष्ठा guc_log_buffer_state));

		/*
		 * The ग_लिखो poपूर्णांकer could have been updated by GuC firmware,
		 * after sending the flush पूर्णांकerrupt to Host, क्रम consistency
		 * set ग_लिखो poपूर्णांकer value to same value of sampled_ग_लिखो_ptr
		 * in the snapshot buffer.
		 */
		log_buf_snapshot_state->ग_लिखो_ptr = ग_लिखो_offset;
		log_buf_snapshot_state++;

		/* Now copy the actual logs. */
		अगर (unlikely(new_overflow)) अणु
			/* copy the whole buffer in हाल of overflow */
			पढ़ो_offset = 0;
			ग_लिखो_offset = buffer_size;
		पूर्ण अन्यथा अगर (unlikely((पढ़ो_offset > buffer_size) ||
				    (ग_लिखो_offset > buffer_size))) अणु
			DRM_ERROR("invalid log buffer state\n");
			/* copy whole buffer as offsets are unreliable */
			पढ़ो_offset = 0;
			ग_लिखो_offset = buffer_size;
		पूर्ण

		/* Just copy the newly written data */
		अगर (पढ़ो_offset > ग_लिखो_offset) अणु
			i915_स_नकल_from_wc(dst_data, src_data, ग_लिखो_offset);
			bytes_to_copy = buffer_size - पढ़ो_offset;
		पूर्ण अन्यथा अणु
			bytes_to_copy = ग_लिखो_offset - पढ़ो_offset;
		पूर्ण
		i915_स_नकल_from_wc(dst_data + पढ़ो_offset,
				    src_data + पढ़ो_offset, bytes_to_copy);

		src_data += buffer_size;
		dst_data += buffer_size;
	पूर्ण

	guc_move_to_next_buf(log);

out_unlock:
	mutex_unlock(&log->relay.lock);
पूर्ण

अटल व्योम capture_logs_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_guc_log *log =
		container_of(work, काष्ठा पूर्णांकel_guc_log, relay.flush_work);

	guc_log_capture_logs(log);
पूर्ण

अटल पूर्णांक guc_log_map(काष्ठा पूर्णांकel_guc_log *log)
अणु
	व्योम *vaddr;

	lockdep_निश्चित_held(&log->relay.lock);

	अगर (!log->vma)
		वापस -ENODEV;

	/*
	 * Create a WC (Uncached क्रम पढ़ो) vदो_स्मृति mapping of log
	 * buffer pages, so that we can directly get the data
	 * (up-to-date) from memory.
	 */
	vaddr = i915_gem_object_pin_map_unlocked(log->vma->obj, I915_MAP_WC);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);

	log->relay.buf_addr = vaddr;

	वापस 0;
पूर्ण

अटल व्योम guc_log_unmap(काष्ठा पूर्णांकel_guc_log *log)
अणु
	lockdep_निश्चित_held(&log->relay.lock);

	i915_gem_object_unpin_map(log->vma->obj);
	log->relay.buf_addr = शून्य;
पूर्ण

व्योम पूर्णांकel_guc_log_init_early(काष्ठा पूर्णांकel_guc_log *log)
अणु
	mutex_init(&log->relay.lock);
	INIT_WORK(&log->relay.flush_work, capture_logs_work);
	log->relay.started = false;
पूर्ण

अटल पूर्णांक guc_log_relay_create(काष्ठा पूर्णांकel_guc_log *log)
अणु
	काष्ठा पूर्णांकel_guc *guc = log_to_guc(log);
	काष्ठा drm_i915_निजी *dev_priv = guc_to_gt(guc)->i915;
	काष्ठा rchan *guc_log_relay_chan;
	माप_प्रकार n_subbufs, subbuf_size;
	पूर्णांक ret;

	lockdep_निश्चित_held(&log->relay.lock);
	GEM_BUG_ON(!log->vma);

	 /* Keep the size of sub buffers same as shared log buffer */
	subbuf_size = log->vma->size;

	/*
	 * Store up to 8 snapshots, which is large enough to buffer sufficient
	 * boot समय logs and provides enough leeway to User, in terms of
	 * latency, क्रम consuming the logs from relay. Also करोesn't take
	 * up too much memory.
	 */
	n_subbufs = 8;

	guc_log_relay_chan = relay_खोलो("guc_log",
					dev_priv->drm.primary->debugfs_root,
					subbuf_size, n_subbufs,
					&relay_callbacks, dev_priv);
	अगर (!guc_log_relay_chan) अणु
		DRM_ERROR("Couldn't create relay chan for GuC logging\n");

		ret = -ENOMEM;
		वापस ret;
	पूर्ण

	GEM_BUG_ON(guc_log_relay_chan->subbuf_size < subbuf_size);
	log->relay.channel = guc_log_relay_chan;

	वापस 0;
पूर्ण

अटल व्योम guc_log_relay_destroy(काष्ठा पूर्णांकel_guc_log *log)
अणु
	lockdep_निश्चित_held(&log->relay.lock);

	relay_बंद(log->relay.channel);
	log->relay.channel = शून्य;
पूर्ण

अटल व्योम guc_log_capture_logs(काष्ठा पूर्णांकel_guc_log *log)
अणु
	काष्ठा पूर्णांकel_guc *guc = log_to_guc(log);
	काष्ठा drm_i915_निजी *dev_priv = guc_to_gt(guc)->i915;
	पूर्णांकel_wakeref_t wakeref;

	guc_पढ़ो_update_log_buffer(log);

	/*
	 * Generally device is expected to be active only at this
	 * समय, so get/put should be really quick.
	 */
	with_पूर्णांकel_runसमय_pm(&dev_priv->runसमय_pm, wakeref)
		guc_action_flush_log_complete(guc);
पूर्ण

अटल u32 __get_शेष_log_level(काष्ठा पूर्णांकel_guc_log *log)
अणु
	काष्ठा पूर्णांकel_guc *guc = log_to_guc(log);
	काष्ठा drm_i915_निजी *i915 = guc_to_gt(guc)->i915;

	/* A negative value means "use platform/config default" */
	अगर (i915->params.guc_log_level < 0) अणु
		वापस (IS_ENABLED(CONFIG_DRM_I915_DEBUG) ||
			IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)) ?
			GUC_LOG_LEVEL_MAX : GUC_LOG_LEVEL_NON_VERBOSE;
	पूर्ण

	अगर (i915->params.guc_log_level > GUC_LOG_LEVEL_MAX) अणु
		DRM_WARN("Incompatible option detected: %s=%d, %s!\n",
			 "guc_log_level", i915->params.guc_log_level,
			 "verbosity too high");
		वापस (IS_ENABLED(CONFIG_DRM_I915_DEBUG) ||
			IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)) ?
			GUC_LOG_LEVEL_MAX : GUC_LOG_LEVEL_DISABLED;
	पूर्ण

	GEM_BUG_ON(i915->params.guc_log_level < GUC_LOG_LEVEL_DISABLED);
	GEM_BUG_ON(i915->params.guc_log_level > GUC_LOG_LEVEL_MAX);
	वापस i915->params.guc_log_level;
पूर्ण

पूर्णांक पूर्णांकel_guc_log_create(काष्ठा पूर्णांकel_guc_log *log)
अणु
	काष्ठा पूर्णांकel_guc *guc = log_to_guc(log);
	काष्ठा i915_vma *vma;
	u32 guc_log_size;
	पूर्णांक ret;

	GEM_BUG_ON(log->vma);

	/*
	 *  GuC Log buffer Layout
	 *
	 *  +===============================+ 00B
	 *  |    Crash dump state header    |
	 *  +-------------------------------+ 32B
	 *  |       DPC state header        |
	 *  +-------------------------------+ 64B
	 *  |       ISR state header        |
	 *  +-------------------------------+ 96B
	 *  |                               |
	 *  +===============================+ PAGE_SIZE (4KB)
	 *  |        Crash Dump logs        |
	 *  +===============================+ + CRASH_SIZE
	 *  |           DPC logs            |
	 *  +===============================+ + DPC_SIZE
	 *  |           ISR logs            |
	 *  +===============================+ + ISR_SIZE
	 */
	guc_log_size = PAGE_SIZE + CRASH_BUFFER_SIZE + DPC_BUFFER_SIZE +
			ISR_BUFFER_SIZE;

	vma = पूर्णांकel_guc_allocate_vma(guc, guc_log_size);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ err;
	पूर्ण

	log->vma = vma;

	log->level = __get_शेष_log_level(log);
	DRM_DEBUG_DRIVER("guc_log_level=%d (%s, verbose:%s, verbosity:%d)\n",
			 log->level, enableddisabled(log->level),
			 yesno(GUC_LOG_LEVEL_IS_VERBOSE(log->level)),
			 GUC_LOG_LEVEL_TO_VERBOSITY(log->level));

	वापस 0;

err:
	DRM_ERROR("Failed to allocate GuC log buffer. %d\n", ret);
	वापस ret;
पूर्ण

व्योम पूर्णांकel_guc_log_destroy(काष्ठा पूर्णांकel_guc_log *log)
अणु
	i915_vma_unpin_and_release(&log->vma, 0);
पूर्ण

पूर्णांक पूर्णांकel_guc_log_set_level(काष्ठा पूर्णांकel_guc_log *log, u32 level)
अणु
	काष्ठा पूर्णांकel_guc *guc = log_to_guc(log);
	काष्ठा drm_i915_निजी *dev_priv = guc_to_gt(guc)->i915;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक ret = 0;

	BUILD_BUG_ON(GUC_LOG_VERBOSITY_MIN != 0);
	GEM_BUG_ON(!log->vma);

	/*
	 * GuC is recognizing log levels starting from 0 to max, we're using 0
	 * as indication that logging should be disabled.
	 */
	अगर (level < GUC_LOG_LEVEL_DISABLED || level > GUC_LOG_LEVEL_MAX)
		वापस -EINVAL;

	mutex_lock(&dev_priv->drm.काष्ठा_mutex);

	अगर (log->level == level)
		जाओ out_unlock;

	with_पूर्णांकel_runसमय_pm(&dev_priv->runसमय_pm, wakeref)
		ret = guc_action_control_log(guc,
					     GUC_LOG_LEVEL_IS_VERBOSE(level),
					     GUC_LOG_LEVEL_IS_ENABLED(level),
					     GUC_LOG_LEVEL_TO_VERBOSITY(level));
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("guc_log_control action failed %d\n", ret);
		जाओ out_unlock;
	पूर्ण

	log->level = level;

out_unlock:
	mutex_unlock(&dev_priv->drm.काष्ठा_mutex);

	वापस ret;
पूर्ण

bool पूर्णांकel_guc_log_relay_created(स्थिर काष्ठा पूर्णांकel_guc_log *log)
अणु
	वापस log->relay.buf_addr;
पूर्ण

पूर्णांक पूर्णांकel_guc_log_relay_खोलो(काष्ठा पूर्णांकel_guc_log *log)
अणु
	पूर्णांक ret;

	अगर (!log->vma)
		वापस -ENODEV;

	mutex_lock(&log->relay.lock);

	अगर (पूर्णांकel_guc_log_relay_created(log)) अणु
		ret = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	/*
	 * We require SSE 4.1 क्रम fast पढ़ोs from the GuC log buffer and
	 * it should be present on the chipsets supporting GuC based
	 * submisssions.
	 */
	अगर (!i915_has_स_नकल_from_wc()) अणु
		ret = -ENXIO;
		जाओ out_unlock;
	पूर्ण

	ret = guc_log_relay_create(log);
	अगर (ret)
		जाओ out_unlock;

	ret = guc_log_map(log);
	अगर (ret)
		जाओ out_relay;

	mutex_unlock(&log->relay.lock);

	वापस 0;

out_relay:
	guc_log_relay_destroy(log);
out_unlock:
	mutex_unlock(&log->relay.lock);

	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_guc_log_relay_start(काष्ठा पूर्णांकel_guc_log *log)
अणु
	अगर (log->relay.started)
		वापस -EEXIST;

	guc_log_enable_flush_events(log);

	/*
	 * When GuC is logging without us relaying to userspace, we're ignoring
	 * the flush notअगरication. This means that we need to unconditionally
	 * flush on relay enabling, since GuC only notअगरies us once.
	 */
	queue_work(प्रणाली_highpri_wq, &log->relay.flush_work);

	log->relay.started = true;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_guc_log_relay_flush(काष्ठा पूर्णांकel_guc_log *log)
अणु
	काष्ठा पूर्णांकel_guc *guc = log_to_guc(log);
	पूर्णांकel_wakeref_t wakeref;

	अगर (!log->relay.started)
		वापस;

	/*
	 * Beक्रमe initiating the क्रमceful flush, रुको क्रम any pending/ongoing
	 * flush to complete otherwise क्रमceful flush may not actually happen.
	 */
	flush_work(&log->relay.flush_work);

	with_पूर्णांकel_runसमय_pm(guc_to_gt(guc)->uncore->rpm, wakeref)
		guc_action_flush_log(guc);

	/* GuC would have updated log buffer by now, so capture it */
	guc_log_capture_logs(log);
पूर्ण

/*
 * Stops the relay log. Called from पूर्णांकel_guc_log_relay_बंद(), so no
 * possibility of race with start/flush since relay_ग_लिखो cannot race
 * relay_बंद.
 */
अटल व्योम guc_log_relay_stop(काष्ठा पूर्णांकel_guc_log *log)
अणु
	काष्ठा पूर्णांकel_guc *guc = log_to_guc(log);
	काष्ठा drm_i915_निजी *i915 = guc_to_gt(guc)->i915;

	अगर (!log->relay.started)
		वापस;

	guc_log_disable_flush_events(log);
	पूर्णांकel_synchronize_irq(i915);

	flush_work(&log->relay.flush_work);

	log->relay.started = false;
पूर्ण

व्योम पूर्णांकel_guc_log_relay_बंद(काष्ठा पूर्णांकel_guc_log *log)
अणु
	guc_log_relay_stop(log);

	mutex_lock(&log->relay.lock);
	GEM_BUG_ON(!पूर्णांकel_guc_log_relay_created(log));
	guc_log_unmap(log);
	guc_log_relay_destroy(log);
	mutex_unlock(&log->relay.lock);
पूर्ण

व्योम पूर्णांकel_guc_log_handle_flush_event(काष्ठा पूर्णांकel_guc_log *log)
अणु
	queue_work(प्रणाली_highpri_wq, &log->relay.flush_work);
पूर्ण

अटल स्थिर अक्षर *
stringअगरy_guc_log_type(क्रमागत guc_log_buffer_type type)
अणु
	चयन (type) अणु
	हाल GUC_ISR_LOG_BUFFER:
		वापस "ISR";
	हाल GUC_DPC_LOG_BUFFER:
		वापस "DPC";
	हाल GUC_CRASH_DUMP_LOG_BUFFER:
		वापस "CRASH";
	शेष:
		MISSING_CASE(type);
	पूर्ण

	वापस "";
पूर्ण

/**
 * पूर्णांकel_guc_log_info - dump inक्रमmation about GuC log relay
 * @log: the GuC log
 * @p: the &drm_prपूर्णांकer
 *
 * Pretty prपूर्णांकer क्रम GuC log info
 */
व्योम पूर्णांकel_guc_log_info(काष्ठा पूर्णांकel_guc_log *log, काष्ठा drm_prपूर्णांकer *p)
अणु
	क्रमागत guc_log_buffer_type type;

	अगर (!पूर्णांकel_guc_log_relay_created(log)) अणु
		drm_माला_दो(p, "GuC log relay not created\n");
		वापस;
	पूर्ण

	drm_माला_दो(p, "GuC logging stats:\n");

	drm_म_लिखो(p, "\tRelay full count: %u\n", log->relay.full_count);

	क्रम (type = GUC_ISR_LOG_BUFFER; type < GUC_MAX_LOG_BUFFER; type++) अणु
		drm_म_लिखो(p, "\t%s:\tflush count %10u, overflow count %10u\n",
			   stringअगरy_guc_log_type(type),
			   log->stats[type].flush,
			   log->stats[type].sampled_overflow);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_guc_log_dump - dump the contents of the GuC log
 * @log: the GuC log
 * @p: the &drm_prपूर्णांकer
 * @dump_load_err: dump the log saved on GuC load error
 *
 * Pretty prपूर्णांकer क्रम the GuC log
 */
पूर्णांक पूर्णांकel_guc_log_dump(काष्ठा पूर्णांकel_guc_log *log, काष्ठा drm_prपूर्णांकer *p,
		       bool dump_load_err)
अणु
	काष्ठा पूर्णांकel_guc *guc = log_to_guc(log);
	काष्ठा पूर्णांकel_uc *uc = container_of(guc, काष्ठा पूर्णांकel_uc, guc);
	काष्ठा drm_i915_gem_object *obj = शून्य;
	u32 *map;
	पूर्णांक i = 0;

	अगर (!पूर्णांकel_guc_is_supported(guc))
		वापस -ENODEV;

	अगर (dump_load_err)
		obj = uc->load_err_log;
	अन्यथा अगर (guc->log.vma)
		obj = guc->log.vma->obj;

	अगर (!obj)
		वापस 0;

	map = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(map)) अणु
		DRM_DEBUG("Failed to pin object\n");
		drm_माला_दो(p, "(log data unaccessible)\n");
		वापस PTR_ERR(map);
	पूर्ण

	क्रम (i = 0; i < obj->base.size / माप(u32); i += 4)
		drm_म_लिखो(p, "0x%08x 0x%08x 0x%08x 0x%08x\n",
			   *(map + i), *(map + i + 1),
			   *(map + i + 2), *(map + i + 3));

	drm_माला_दो(p, "\n");

	i915_gem_object_unpin_map(obj);

	वापस 0;
पूर्ण
