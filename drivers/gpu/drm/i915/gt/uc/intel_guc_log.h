<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_GUC_LOG_H_
#घोषणा _INTEL_GUC_LOG_H_

#समावेश <linux/mutex.h>
#समावेश <linux/relay.h>
#समावेश <linux/workqueue.h>

#समावेश "intel_guc_fwif.h"
#समावेश "i915_gem.h"

काष्ठा पूर्णांकel_guc;

#अगर_घोषित CONFIG_DRM_I915_DEBUG_GUC
#घोषणा CRASH_BUFFER_SIZE	SZ_2M
#घोषणा DPC_BUFFER_SIZE		SZ_8M
#घोषणा ISR_BUFFER_SIZE		SZ_8M
#अन्यथा
#घोषणा CRASH_BUFFER_SIZE	SZ_8K
#घोषणा DPC_BUFFER_SIZE		SZ_32K
#घोषणा ISR_BUFFER_SIZE		SZ_32K
#पूर्ण_अगर

/*
 * While we're using plain log level in i915, GuC controls are much more...
 * "elaborate"? We have a couple of bits क्रम verbosity, separate bit क्रम actual
 * log enabling, and separate bit क्रम शेष logging - which "conveniently"
 * ignores the enable bit.
 */
#घोषणा GUC_LOG_LEVEL_DISABLED		0
#घोषणा GUC_LOG_LEVEL_NON_VERBOSE	1
#घोषणा GUC_LOG_LEVEL_IS_ENABLED(x)	((x) > GUC_LOG_LEVEL_DISABLED)
#घोषणा GUC_LOG_LEVEL_IS_VERBOSE(x)	((x) > GUC_LOG_LEVEL_NON_VERBOSE)
#घोषणा GUC_LOG_LEVEL_TO_VERBOSITY(x) (अणु		\
	typeof(x) _x = (x);				\
	GUC_LOG_LEVEL_IS_VERBOSE(_x) ? _x - 2 : 0;	\
पूर्ण)
#घोषणा GUC_VERBOSITY_TO_LOG_LEVEL(x)	((x) + 2)
#घोषणा GUC_LOG_LEVEL_MAX GUC_VERBOSITY_TO_LOG_LEVEL(GUC_LOG_VERBOSITY_MAX)

काष्ठा पूर्णांकel_guc_log अणु
	u32 level;
	काष्ठा i915_vma *vma;
	काष्ठा अणु
		व्योम *buf_addr;
		bool started;
		काष्ठा work_काष्ठा flush_work;
		काष्ठा rchan *channel;
		काष्ठा mutex lock;
		u32 full_count;
	पूर्ण relay;
	/* logging related stats */
	काष्ठा अणु
		u32 sampled_overflow;
		u32 overflow;
		u32 flush;
	पूर्ण stats[GUC_MAX_LOG_BUFFER];
पूर्ण;

व्योम पूर्णांकel_guc_log_init_early(काष्ठा पूर्णांकel_guc_log *log);
पूर्णांक पूर्णांकel_guc_log_create(काष्ठा पूर्णांकel_guc_log *log);
व्योम पूर्णांकel_guc_log_destroy(काष्ठा पूर्णांकel_guc_log *log);

पूर्णांक पूर्णांकel_guc_log_set_level(काष्ठा पूर्णांकel_guc_log *log, u32 level);
bool पूर्णांकel_guc_log_relay_created(स्थिर काष्ठा पूर्णांकel_guc_log *log);
पूर्णांक पूर्णांकel_guc_log_relay_खोलो(काष्ठा पूर्णांकel_guc_log *log);
पूर्णांक पूर्णांकel_guc_log_relay_start(काष्ठा पूर्णांकel_guc_log *log);
व्योम पूर्णांकel_guc_log_relay_flush(काष्ठा पूर्णांकel_guc_log *log);
व्योम पूर्णांकel_guc_log_relay_बंद(काष्ठा पूर्णांकel_guc_log *log);

व्योम पूर्णांकel_guc_log_handle_flush_event(काष्ठा पूर्णांकel_guc_log *log);

अटल अंतरभूत u32 पूर्णांकel_guc_log_get_level(काष्ठा पूर्णांकel_guc_log *log)
अणु
	वापस log->level;
पूर्ण

व्योम पूर्णांकel_guc_log_info(काष्ठा पूर्णांकel_guc_log *log, काष्ठा drm_prपूर्णांकer *p);
पूर्णांक पूर्णांकel_guc_log_dump(काष्ठा पूर्णांकel_guc_log *log, काष्ठा drm_prपूर्णांकer *p,
		       bool dump_load_err);

#पूर्ण_अगर
