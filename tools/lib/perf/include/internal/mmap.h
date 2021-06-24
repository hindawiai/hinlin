<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_INTERNAL_MMAP_H
#घोषणा __LIBPERF_INTERNAL_MMAP_H

#समावेश <linux/compiler.h>
#समावेश <linux/refcount.h>
#समावेश <linux/types.h>
#समावेश <stdbool.h>

/* perf sample has 16 bits size limit */
#घोषणा PERF_SAMPLE_MAX_SIZE (1 << 16)

काष्ठा perf_mmap;
काष्ठा perf_counts_values;

प्रकार व्योम (*libperf_unmap_cb_t)(काष्ठा perf_mmap *map);

/**
 * काष्ठा perf_mmap - perf's ring buffer mmap details
 *
 * @refcnt - e.g. code using PERF_EVENT_IOC_SET_OUTPUT to share this
 */
काष्ठा perf_mmap अणु
	व्योम			*base;
	पूर्णांक			 mask;
	पूर्णांक			 fd;
	पूर्णांक			 cpu;
	refcount_t		 refcnt;
	u64			 prev;
	u64			 start;
	u64			 end;
	bool			 overग_लिखो;
	u64			 flush;
	libperf_unmap_cb_t	 unmap_cb;
	अक्षर			 event_copy[PERF_SAMPLE_MAX_SIZE] __aligned(8);
	काष्ठा perf_mmap	*next;
पूर्ण;

काष्ठा perf_mmap_param अणु
	पूर्णांक	prot;
	पूर्णांक	mask;
पूर्ण;

माप_प्रकार perf_mmap__mmap_len(काष्ठा perf_mmap *map);

व्योम perf_mmap__init(काष्ठा perf_mmap *map, काष्ठा perf_mmap *prev,
		     bool overग_लिखो, libperf_unmap_cb_t unmap_cb);
पूर्णांक perf_mmap__mmap(काष्ठा perf_mmap *map, काष्ठा perf_mmap_param *mp,
		    पूर्णांक fd, पूर्णांक cpu);
व्योम perf_mmap__munmap(काष्ठा perf_mmap *map);
व्योम perf_mmap__get(काष्ठा perf_mmap *map);
व्योम perf_mmap__put(काष्ठा perf_mmap *map);

u64 perf_mmap__पढ़ो_head(काष्ठा perf_mmap *map);

पूर्णांक perf_mmap__पढ़ो_self(काष्ठा perf_mmap *map, काष्ठा perf_counts_values *count);

#पूर्ण_अगर /* __LIBPERF_INTERNAL_MMAP_H */
