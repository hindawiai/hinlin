<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_INTERNAL_EVLIST_H
#घोषणा __LIBPERF_INTERNAL_EVLIST_H

#समावेश <linux/list.h>
#समावेश <api/fd/array.h>
#समावेश <पूर्णांकernal/evsel.h>

#घोषणा PERF_EVLIST__HLIST_BITS 8
#घोषणा PERF_EVLIST__HLIST_SIZE (1 << PERF_EVLIST__HLIST_BITS)

काष्ठा perf_cpu_map;
काष्ठा perf_thपढ़ो_map;
काष्ठा perf_mmap_param;

काष्ठा perf_evlist अणु
	काष्ठा list_head	 entries;
	पूर्णांक			 nr_entries;
	bool			 has_user_cpus;
	काष्ठा perf_cpu_map	*cpus;
	काष्ठा perf_cpu_map	*all_cpus;
	काष्ठा perf_thपढ़ो_map	*thपढ़ोs;
	पूर्णांक			 nr_mmaps;
	माप_प्रकार			 mmap_len;
	काष्ठा fdarray		 pollfd;
	काष्ठा hlist_head	 heads[PERF_EVLIST__HLIST_SIZE];
	काष्ठा perf_mmap	*mmap;
	काष्ठा perf_mmap	*mmap_ovw;
	काष्ठा perf_mmap	*mmap_first;
	काष्ठा perf_mmap	*mmap_ovw_first;
पूर्ण;

प्रकार व्योम
(*perf_evlist_mmap__cb_idx_t)(काष्ठा perf_evlist*, काष्ठा perf_mmap_param*, पूर्णांक, bool);
प्रकार काष्ठा perf_mmap*
(*perf_evlist_mmap__cb_get_t)(काष्ठा perf_evlist*, bool, पूर्णांक);
प्रकार पूर्णांक
(*perf_evlist_mmap__cb_mmap_t)(काष्ठा perf_mmap*, काष्ठा perf_mmap_param*, पूर्णांक, पूर्णांक);

काष्ठा perf_evlist_mmap_ops अणु
	perf_evlist_mmap__cb_idx_t	idx;
	perf_evlist_mmap__cb_get_t	get;
	perf_evlist_mmap__cb_mmap_t	mmap;
पूर्ण;

पूर्णांक perf_evlist__alloc_pollfd(काष्ठा perf_evlist *evlist);
पूर्णांक perf_evlist__add_pollfd(काष्ठा perf_evlist *evlist, पूर्णांक fd,
			    व्योम *ptr, लघु revent, क्रमागत fdarray_flags flags);

पूर्णांक perf_evlist__mmap_ops(काष्ठा perf_evlist *evlist,
			  काष्ठा perf_evlist_mmap_ops *ops,
			  काष्ठा perf_mmap_param *mp);

व्योम perf_evlist__init(काष्ठा perf_evlist *evlist);
व्योम perf_evlist__निकास(काष्ठा perf_evlist *evlist);

/**
 * __perf_evlist__क्रम_each_entry - iterate thru all the evsels
 * @list: list_head instance to iterate
 * @evsel: काष्ठा perf_evsel iterator
 */
#घोषणा __perf_evlist__क्रम_each_entry(list, evsel) \
	list_क्रम_each_entry(evsel, list, node)

/**
 * evlist__क्रम_each_entry - iterate thru all the evsels
 * @evlist: perf_evlist instance to iterate
 * @evsel: काष्ठा perf_evsel iterator
 */
#घोषणा perf_evlist__क्रम_each_entry(evlist, evsel) \
	__perf_evlist__क्रम_each_entry(&(evlist)->entries, evsel)

/**
 * __perf_evlist__क्रम_each_entry_reverse - iterate thru all the evsels in reverse order
 * @list: list_head instance to iterate
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा __perf_evlist__क्रम_each_entry_reverse(list, evsel) \
	list_क्रम_each_entry_reverse(evsel, list, node)

/**
 * perf_evlist__क्रम_each_entry_reverse - iterate thru all the evsels in reverse order
 * @evlist: evlist instance to iterate
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा perf_evlist__क्रम_each_entry_reverse(evlist, evsel) \
	__perf_evlist__क्रम_each_entry_reverse(&(evlist)->entries, evsel)

/**
 * __perf_evlist__क्रम_each_entry_safe - safely iterate thru all the evsels
 * @list: list_head instance to iterate
 * @पंचांगp: काष्ठा evsel temp iterator
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा __perf_evlist__क्रम_each_entry_safe(list, पंचांगp, evsel) \
	list_क्रम_each_entry_safe(evsel, पंचांगp, list, node)

/**
 * perf_evlist__क्रम_each_entry_safe - safely iterate thru all the evsels
 * @evlist: evlist instance to iterate
 * @evsel: काष्ठा evsel iterator
 * @पंचांगp: काष्ठा evsel temp iterator
 */
#घोषणा perf_evlist__क्रम_each_entry_safe(evlist, पंचांगp, evsel) \
	__perf_evlist__क्रम_each_entry_safe(&(evlist)->entries, पंचांगp, evsel)

अटल अंतरभूत काष्ठा perf_evsel *perf_evlist__first(काष्ठा perf_evlist *evlist)
अणु
	वापस list_entry(evlist->entries.next, काष्ठा perf_evsel, node);
पूर्ण

अटल अंतरभूत काष्ठा perf_evsel *perf_evlist__last(काष्ठा perf_evlist *evlist)
अणु
	वापस list_entry(evlist->entries.prev, काष्ठा perf_evsel, node);
पूर्ण

u64 perf_evlist__पढ़ो_क्रमmat(काष्ठा perf_evlist *evlist);

व्योम perf_evlist__id_add(काष्ठा perf_evlist *evlist,
			 काष्ठा perf_evsel *evsel,
			 पूर्णांक cpu, पूर्णांक thपढ़ो, u64 id);

पूर्णांक perf_evlist__id_add_fd(काष्ठा perf_evlist *evlist,
			   काष्ठा perf_evsel *evsel,
			   पूर्णांक cpu, पूर्णांक thपढ़ो, पूर्णांक fd);

व्योम perf_evlist__reset_id_hash(काष्ठा perf_evlist *evlist);

#पूर्ण_अगर /* __LIBPERF_INTERNAL_EVLIST_H */
