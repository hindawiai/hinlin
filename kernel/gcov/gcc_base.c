<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश "gcov.h"

/*
 * __gcov_init is called by gcc-generated स्थिरructor code क्रम each object
 * file compiled with -fprofile-arcs.
 */
व्योम __gcov_init(काष्ठा gcov_info *info)
अणु
	अटल अचिन्हित पूर्णांक gcov_version;

	mutex_lock(&gcov_lock);
	अगर (gcov_version == 0) अणु
		gcov_version = gcov_info_version(info);
		/*
		 * Prपूर्णांकing gcc's version magic may prove useful क्रम debugging
		 * incompatibility reports.
		 */
		pr_info("version magic: 0x%x\n", gcov_version);
	पूर्ण
	/*
	 * Add new profiling data काष्ठाure to list and inक्रमm event
	 * listener.
	 */
	gcov_info_link(info);
	अगर (gcov_events_enabled)
		gcov_event(GCOV_ADD, info);
	mutex_unlock(&gcov_lock);
पूर्ण
EXPORT_SYMBOL(__gcov_init);

/*
 * These functions may be referenced by gcc-generated profiling code but serve
 * no function क्रम kernel profiling.
 */
व्योम __gcov_flush(व्योम)
अणु
	/* Unused. */
पूर्ण
EXPORT_SYMBOL(__gcov_flush);

व्योम __gcov_merge_add(gcov_type *counters, अचिन्हित पूर्णांक n_counters)
अणु
	/* Unused. */
पूर्ण
EXPORT_SYMBOL(__gcov_merge_add);

व्योम __gcov_merge_single(gcov_type *counters, अचिन्हित पूर्णांक n_counters)
अणु
	/* Unused. */
पूर्ण
EXPORT_SYMBOL(__gcov_merge_single);

व्योम __gcov_merge_delta(gcov_type *counters, अचिन्हित पूर्णांक n_counters)
अणु
	/* Unused. */
पूर्ण
EXPORT_SYMBOL(__gcov_merge_delta);

व्योम __gcov_merge_ior(gcov_type *counters, अचिन्हित पूर्णांक n_counters)
अणु
	/* Unused. */
पूर्ण
EXPORT_SYMBOL(__gcov_merge_ior);

व्योम __gcov_merge_समय_profile(gcov_type *counters, अचिन्हित पूर्णांक n_counters)
अणु
	/* Unused. */
पूर्ण
EXPORT_SYMBOL(__gcov_merge_समय_profile);

व्योम __gcov_merge_icall_topn(gcov_type *counters, अचिन्हित पूर्णांक n_counters)
अणु
	/* Unused. */
पूर्ण
EXPORT_SYMBOL(__gcov_merge_icall_topn);

व्योम __gcov_निकास(व्योम)
अणु
	/* Unused. */
पूर्ण
EXPORT_SYMBOL(__gcov_निकास);
