<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * auxtrace.h: AUX area trace support
 * Copyright (c) 2013-2015, Intel Corporation.
 */

#अगर_अघोषित __PERF_AUXTRACE_H
#घोषणा __PERF_AUXTRACE_H

#समावेश <sys/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स> // खाता
#समावेश <linux/list.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <यंत्र/barrier.h>

जोड़ perf_event;
काष्ठा perf_session;
काष्ठा evlist;
काष्ठा evsel;
काष्ठा perf_tool;
काष्ठा mmap;
काष्ठा perf_sample;
काष्ठा option;
काष्ठा record_opts;
काष्ठा perf_record_auxtrace_error;
काष्ठा perf_record_auxtrace_info;
काष्ठा events_stats;
काष्ठा perf_pmu;

क्रमागत auxtrace_error_type अणु
       PERF_AUXTRACE_ERROR_ITRACE  = 1,
       PERF_AUXTRACE_ERROR_MAX
पूर्ण;

/* Auxtrace records must have the same alignment as perf event records */
#घोषणा PERF_AUXTRACE_RECORD_ALIGNMENT 8

क्रमागत auxtrace_type अणु
	PERF_AUXTRACE_UNKNOWN,
	PERF_AUXTRACE_INTEL_PT,
	PERF_AUXTRACE_INTEL_BTS,
	PERF_AUXTRACE_CS_ETM,
	PERF_AUXTRACE_ARM_SPE,
	PERF_AUXTRACE_S390_CPUMSF,
पूर्ण;

क्रमागत itrace_period_type अणु
	PERF_ITRACE_PERIOD_INSTRUCTIONS,
	PERF_ITRACE_PERIOD_TICKS,
	PERF_ITRACE_PERIOD_न_अंकOSECS,
पूर्ण;

#घोषणा AUXTRACE_ERR_FLG_OVERFLOW	(1 << ('o' - 'a'))
#घोषणा AUXTRACE_ERR_FLG_DATA_LOST	(1 << ('l' - 'a'))

#घोषणा AUXTRACE_LOG_FLG_ALL_PERF_EVTS	(1 << ('a' - 'a'))

/**
 * काष्ठा itrace_synth_opts - AUX area tracing synthesis options.
 * @set: indicates whether or not options have been set
 * @शेष_no_sample: Default to no sampling.
 * @inject: indicates the event (not just the sample) must be fully synthesized
 *          because 'perf inject' will ग_लिखो it out
 * @inकाष्ठाions: whether to synthesize 'instructions' events
 * @branches: whether to synthesize 'branches' events
 *            (branch misses only क्रम Arm SPE)
 * @transactions: whether to synthesize events क्रम transactions
 * @ptग_लिखोs: whether to synthesize events क्रम ptग_लिखोs
 * @pwr_events: whether to synthesize घातer events
 * @other_events: whether to synthesize other events recorded due to the use of
 *                aux_output
 * @errors: whether to synthesize decoder error events
 * @करोnt_decode: whether to skip decoding entirely
 * @log: ग_लिखो a decoding log
 * @calls: limit branch samples to calls (can be combined with @वापसs)
 * @वापसs: limit branch samples to वापसs (can be combined with @calls)
 * @callchain: add callchain to 'instructions' events
 * @add_callchain: add callchain to existing event records
 * @thपढ़ो_stack: feed branches to the thपढ़ो_stack
 * @last_branch: add branch context to 'instruction' events
 * @add_last_branch: add branch context to existing event records
 * @flc: whether to synthesize first level cache events
 * @llc: whether to synthesize last level cache events
 * @tlb: whether to synthesize TLB events
 * @remote_access: whether to synthesize remote access events
 * @mem: whether to synthesize memory events
 * @callchain_sz: maximum callchain size
 * @last_branch_sz: branch context size
 * @period: 'instructions' events period
 * @period_type: 'instructions' events period type
 * @initial_skip: skip N events at the beginning.
 * @cpu_biपंचांगap: CPUs क्रम which to synthesize events, or शून्य क्रम all
 * @pसमय_range: समय पूर्णांकervals to trace or शून्य
 * @range_num: number of समय पूर्णांकervals to trace
 * @error_plus_flags: flags to affect what errors are reported
 * @error_minus_flags: flags to affect what errors are reported
 * @log_plus_flags: flags to affect what is logged
 * @log_minus_flags: flags to affect what is logged
 * @quick: quicker (less detailed) decoding
 */
काष्ठा itrace_synth_opts अणु
	bool			set;
	bool			शेष_no_sample;
	bool			inject;
	bool			inकाष्ठाions;
	bool			branches;
	bool			transactions;
	bool			ptग_लिखोs;
	bool			pwr_events;
	bool			other_events;
	bool			errors;
	bool			करोnt_decode;
	bool			log;
	bool			calls;
	bool			वापसs;
	bool			callchain;
	bool			add_callchain;
	bool			thपढ़ो_stack;
	bool			last_branch;
	bool			add_last_branch;
	bool			flc;
	bool			llc;
	bool			tlb;
	bool			remote_access;
	bool			mem;
	अचिन्हित पूर्णांक		callchain_sz;
	अचिन्हित पूर्णांक		last_branch_sz;
	अचिन्हित दीर्घ दीर्घ	period;
	क्रमागत itrace_period_type	period_type;
	अचिन्हित दीर्घ		initial_skip;
	अचिन्हित दीर्घ		*cpu_biपंचांगap;
	काष्ठा perf_समय_पूर्णांकerval *pसमय_range;
	पूर्णांक			range_num;
	अचिन्हित पूर्णांक		error_plus_flags;
	अचिन्हित पूर्णांक		error_minus_flags;
	अचिन्हित पूर्णांक		log_plus_flags;
	अचिन्हित पूर्णांक		log_minus_flags;
	अचिन्हित पूर्णांक		quick;
पूर्ण;

/**
 * काष्ठा auxtrace_index_entry - indexes a AUX area tracing event within a
 *                               perf.data file.
 * @file_offset: offset within the perf.data file
 * @sz: size of the event
 */
काष्ठा auxtrace_index_entry अणु
	u64			file_offset;
	u64			sz;
पूर्ण;

#घोषणा PERF_AUXTRACE_INDEX_ENTRY_COUNT 256

/**
 * काष्ठा auxtrace_index - index of AUX area tracing events within a perf.data
 *                         file.
 * @list: linking a number of arrays of entries
 * @nr: number of entries
 * @entries: array of entries
 */
काष्ठा auxtrace_index अणु
	काष्ठा list_head	list;
	माप_प्रकार			nr;
	काष्ठा auxtrace_index_entry entries[PERF_AUXTRACE_INDEX_ENTRY_COUNT];
पूर्ण;

/**
 * काष्ठा auxtrace - session callbacks to allow AUX area data decoding.
 * @process_event: lets the decoder see all session events
 * @process_auxtrace_event: process a PERF_RECORD_AUXTRACE event
 * @queue_data: queue an AUX sample or PERF_RECORD_AUXTRACE event क्रम later
 *              processing
 * @dump_auxtrace_sample: dump AUX area sample data
 * @flush_events: process any reमुख्यing data
 * @मुक्त_events: मुक्त resources associated with event processing
 * @मुक्त: मुक्त resources associated with the session
 */
काष्ठा auxtrace अणु
	पूर्णांक (*process_event)(काष्ठा perf_session *session,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा perf_tool *tool);
	पूर्णांक (*process_auxtrace_event)(काष्ठा perf_session *session,
				      जोड़ perf_event *event,
				      काष्ठा perf_tool *tool);
	पूर्णांक (*queue_data)(काष्ठा perf_session *session,
			  काष्ठा perf_sample *sample, जोड़ perf_event *event,
			  u64 data_offset);
	व्योम (*dump_auxtrace_sample)(काष्ठा perf_session *session,
				     काष्ठा perf_sample *sample);
	पूर्णांक (*flush_events)(काष्ठा perf_session *session,
			    काष्ठा perf_tool *tool);
	व्योम (*मुक्त_events)(काष्ठा perf_session *session);
	व्योम (*मुक्त)(काष्ठा perf_session *session);
	bool (*evsel_is_auxtrace)(काष्ठा perf_session *session,
				  काष्ठा evsel *evsel);
पूर्ण;

/**
 * काष्ठा auxtrace_buffer - a buffer containing AUX area tracing data.
 * @list: buffers are queued in a list held by काष्ठा auxtrace_queue
 * @size: size of the buffer in bytes
 * @pid: in per-thपढ़ो mode, the pid this buffer is associated with
 * @tid: in per-thपढ़ो mode, the tid this buffer is associated with
 * @cpu: in per-cpu mode, the cpu this buffer is associated with
 * @data: actual buffer data (can be null अगर the data has not been loaded)
 * @data_offset: file offset at which the buffer can be पढ़ो
 * @mmap_addr: mmap address at which the buffer can be पढ़ो
 * @mmap_size: size of the mmap at @mmap_addr
 * @data_needs_मुक्तing: @data was दो_स्मृति'd so मुक्त it when it is no दीर्घer
 *                      needed
 * @consecutive: the original data was split up and this buffer is consecutive
 *               to the previous buffer
 * @offset: offset as determined by aux_head / aux_tail members of काष्ठा
 *          perf_event_mmap_page
 * @reference: an implementation-specअगरic reference determined when the data is
 *             recorded
 * @buffer_nr: used to number each buffer
 * @use_size: implementation actually only uses this number of bytes
 * @use_data: implementation actually only uses data starting at this address
 */
काष्ठा auxtrace_buffer अणु
	काष्ठा list_head	list;
	माप_प्रकार			size;
	pid_t			pid;
	pid_t			tid;
	पूर्णांक			cpu;
	व्योम			*data;
	off_t			data_offset;
	व्योम			*mmap_addr;
	माप_प्रकार			mmap_size;
	bool			data_needs_मुक्तing;
	bool			consecutive;
	u64			offset;
	u64			reference;
	u64			buffer_nr;
	माप_प्रकार			use_size;
	व्योम			*use_data;
पूर्ण;

/**
 * काष्ठा auxtrace_queue - a queue of AUX area tracing data buffers.
 * @head: head of buffer list
 * @tid: in per-thपढ़ो mode, the tid this queue is associated with
 * @cpu: in per-cpu mode, the cpu this queue is associated with
 * @set: %true once this queue has been dedicated to a specअगरic thपढ़ो or cpu
 * @priv: implementation-specअगरic data
 */
काष्ठा auxtrace_queue अणु
	काष्ठा list_head	head;
	pid_t			tid;
	पूर्णांक			cpu;
	bool			set;
	व्योम			*priv;
पूर्ण;

/**
 * काष्ठा auxtrace_queues - an array of AUX area tracing queues.
 * @queue_array: array of queues
 * @nr_queues: number of queues
 * @new_data: set whenever new data is queued
 * @populated: queues have been fully populated using the auxtrace_index
 * @next_buffer_nr: used to number each buffer
 */
काष्ठा auxtrace_queues अणु
	काष्ठा auxtrace_queue	*queue_array;
	अचिन्हित पूर्णांक		nr_queues;
	bool			new_data;
	bool			populated;
	u64			next_buffer_nr;
पूर्ण;

/**
 * काष्ठा auxtrace_heap_item - element of काष्ठा auxtrace_heap.
 * @queue_nr: queue number
 * @ordinal: value used क्रम sorting (lowest ordinal is top of the heap) expected
 *           to be a बारtamp
 */
काष्ठा auxtrace_heap_item अणु
	अचिन्हित पूर्णांक		queue_nr;
	u64			ordinal;
पूर्ण;

/**
 * काष्ठा auxtrace_heap - a heap suitable क्रम sorting AUX area tracing queues.
 * @heap_array: the heap
 * @heap_cnt: the number of elements in the heap
 * @heap_sz: maximum number of elements (grows as needed)
 */
काष्ठा auxtrace_heap अणु
	काष्ठा auxtrace_heap_item	*heap_array;
	अचिन्हित पूर्णांक		heap_cnt;
	अचिन्हित पूर्णांक		heap_sz;
पूर्ण;

/**
 * काष्ठा auxtrace_mmap - records an mmap of the auxtrace buffer.
 * @base: address of mapped area
 * @userpg: poपूर्णांकer to buffer's perf_event_mmap_page
 * @mask: %0 अगर @len is not a घातer of two, otherwise (@len - %1)
 * @len: size of mapped area
 * @prev: previous aux_head
 * @idx: index of this mmap
 * @tid: tid क्रम a per-thपढ़ो mmap (also set अगर there is only 1 tid on a per-cpu
 *       mmap) otherwise %0
 * @cpu: cpu number क्रम a per-cpu mmap otherwise %-1
 */
काष्ठा auxtrace_mmap अणु
	व्योम		*base;
	व्योम		*userpg;
	माप_प्रकार		mask;
	माप_प्रकार		len;
	u64		prev;
	पूर्णांक		idx;
	pid_t		tid;
	पूर्णांक		cpu;
पूर्ण;

/**
 * काष्ठा auxtrace_mmap_params - parameters to set up काष्ठा auxtrace_mmap.
 * @mask: %0 अगर @len is not a घातer of two, otherwise (@len - %1)
 * @offset: file offset of mapped area
 * @len: size of mapped area
 * @prot: mmap memory protection
 * @idx: index of this mmap
 * @tid: tid क्रम a per-thपढ़ो mmap (also set अगर there is only 1 tid on a per-cpu
 *       mmap) otherwise %0
 * @cpu: cpu number क्रम a per-cpu mmap otherwise %-1
 */
काष्ठा auxtrace_mmap_params अणु
	माप_प्रकार		mask;
	off_t		offset;
	माप_प्रकार		len;
	पूर्णांक		prot;
	पूर्णांक		idx;
	pid_t		tid;
	पूर्णांक		cpu;
पूर्ण;

/**
 * काष्ठा auxtrace_record - callbacks क्रम recording AUX area data.
 * @recording_options: validate and process recording options
 * @info_priv_size: वापस the size of the निजी data in auxtrace_info_event
 * @info_fill: fill-in the निजी data in auxtrace_info_event
 * @मुक्त: मुक्त this auxtrace record काष्ठाure
 * @snapshot_start: starting a snapshot
 * @snapshot_finish: finishing a snapshot
 * @find_snapshot: find data to snapshot within auxtrace mmap
 * @parse_snapshot_options: parse snapshot options
 * @reference: provide a 64-bit reference number क्रम auxtrace_event
 * @पढ़ो_finish: called after पढ़ोing from an auxtrace mmap
 * @alignment: alignment (अगर any) क्रम AUX area data
 * @शेष_aux_sample_size: शेष sample size क्रम --aux sample option
 * @pmu: associated pmu
 * @evlist: selected events list
 */
काष्ठा auxtrace_record अणु
	पूर्णांक (*recording_options)(काष्ठा auxtrace_record *itr,
				 काष्ठा evlist *evlist,
				 काष्ठा record_opts *opts);
	माप_प्रकार (*info_priv_size)(काष्ठा auxtrace_record *itr,
				 काष्ठा evlist *evlist);
	पूर्णांक (*info_fill)(काष्ठा auxtrace_record *itr,
			 काष्ठा perf_session *session,
			 काष्ठा perf_record_auxtrace_info *auxtrace_info,
			 माप_प्रकार priv_size);
	व्योम (*मुक्त)(काष्ठा auxtrace_record *itr);
	पूर्णांक (*snapshot_start)(काष्ठा auxtrace_record *itr);
	पूर्णांक (*snapshot_finish)(काष्ठा auxtrace_record *itr);
	पूर्णांक (*find_snapshot)(काष्ठा auxtrace_record *itr, पूर्णांक idx,
			     काष्ठा auxtrace_mmap *mm, अचिन्हित अक्षर *data,
			     u64 *head, u64 *old);
	पूर्णांक (*parse_snapshot_options)(काष्ठा auxtrace_record *itr,
				      काष्ठा record_opts *opts,
				      स्थिर अक्षर *str);
	u64 (*reference)(काष्ठा auxtrace_record *itr);
	पूर्णांक (*पढ़ो_finish)(काष्ठा auxtrace_record *itr, पूर्णांक idx);
	अचिन्हित पूर्णांक alignment;
	अचिन्हित पूर्णांक शेष_aux_sample_size;
	काष्ठा perf_pmu *pmu;
	काष्ठा evlist *evlist;
पूर्ण;

/**
 * काष्ठा addr_filter - address filter.
 * @list: list node
 * @range: true अगर it is a range filter
 * @start: true अगर action is 'filter' or 'start'
 * @action: 'filter', 'start' or 'stop' ('tracestop' is accepted but converted
 *          to 'stop')
 * @sym_from: symbol name क्रम the filter address
 * @sym_to: symbol name that determines the filter size
 * @sym_from_idx: selects n'th from symbols with the same name (0 means global
 *                and less than 0 means symbol must be unique)
 * @sym_to_idx: same as @sym_from_idx but क्रम @sym_to
 * @addr: filter address
 * @size: filter region size (क्रम range filters)
 * @filename: DSO file name or शून्य क्रम the kernel
 * @str: allocated string that contains the other string members
 */
काष्ठा addr_filter अणु
	काष्ठा list_head	list;
	bool			range;
	bool			start;
	स्थिर अक्षर		*action;
	स्थिर अक्षर		*sym_from;
	स्थिर अक्षर		*sym_to;
	पूर्णांक			sym_from_idx;
	पूर्णांक			sym_to_idx;
	u64			addr;
	u64			size;
	स्थिर अक्षर		*filename;
	अक्षर			*str;
पूर्ण;

/**
 * काष्ठा addr_filters - list of address filters.
 * @head: list of address filters
 * @cnt: number of address filters
 */
काष्ठा addr_filters अणु
	काष्ठा list_head	head;
	पूर्णांक			cnt;
पूर्ण;

काष्ठा auxtrace_cache;

#अगर_घोषित HAVE_AUXTRACE_SUPPORT

/*
 * In snapshot mode the mmapped page is पढ़ो-only which makes using
 * __sync_val_compare_and_swap() problematic.  However, snapshot mode expects
 * the buffer is not updated जबतक the snapshot is made (e.g. Intel PT disables
 * the event) so there is not a race anyway.
 */
अटल अंतरभूत u64 auxtrace_mmap__पढ़ो_snapshot_head(काष्ठा auxtrace_mmap *mm)
अणु
	काष्ठा perf_event_mmap_page *pc = mm->userpg;
	u64 head = READ_ONCE(pc->aux_head);

	/* Ensure all पढ़ोs are करोne after we पढ़ो the head */
	rmb();
	वापस head;
पूर्ण

अटल अंतरभूत u64 auxtrace_mmap__पढ़ो_head(काष्ठा auxtrace_mmap *mm)
अणु
	काष्ठा perf_event_mmap_page *pc = mm->userpg;
#अगर BITS_PER_LONG == 64 || !defined(HAVE_SYNC_COMPARE_AND_SWAP_SUPPORT)
	u64 head = READ_ONCE(pc->aux_head);
#अन्यथा
	u64 head = __sync_val_compare_and_swap(&pc->aux_head, 0, 0);
#पूर्ण_अगर

	/* Ensure all पढ़ोs are करोne after we पढ़ो the head */
	rmb();
	वापस head;
पूर्ण

अटल अंतरभूत व्योम auxtrace_mmap__ग_लिखो_tail(काष्ठा auxtrace_mmap *mm, u64 tail)
अणु
	काष्ठा perf_event_mmap_page *pc = mm->userpg;
#अगर BITS_PER_LONG != 64 && defined(HAVE_SYNC_COMPARE_AND_SWAP_SUPPORT)
	u64 old_tail;
#पूर्ण_अगर

	/* Ensure all पढ़ोs are करोne beक्रमe we ग_लिखो the tail out */
	mb();
#अगर BITS_PER_LONG == 64 || !defined(HAVE_SYNC_COMPARE_AND_SWAP_SUPPORT)
	pc->aux_tail = tail;
#अन्यथा
	करो अणु
		old_tail = __sync_val_compare_and_swap(&pc->aux_tail, 0, 0);
	पूर्ण जबतक (!__sync_bool_compare_and_swap(&pc->aux_tail, old_tail, tail));
#पूर्ण_अगर
पूर्ण

पूर्णांक auxtrace_mmap__mmap(काष्ठा auxtrace_mmap *mm,
			काष्ठा auxtrace_mmap_params *mp,
			व्योम *userpg, पूर्णांक fd);
व्योम auxtrace_mmap__munmap(काष्ठा auxtrace_mmap *mm);
व्योम auxtrace_mmap_params__init(काष्ठा auxtrace_mmap_params *mp,
				off_t auxtrace_offset,
				अचिन्हित पूर्णांक auxtrace_pages,
				bool auxtrace_overग_लिखो);
व्योम auxtrace_mmap_params__set_idx(काष्ठा auxtrace_mmap_params *mp,
				   काष्ठा evlist *evlist, पूर्णांक idx,
				   bool per_cpu);

प्रकार पूर्णांक (*process_auxtrace_t)(काष्ठा perf_tool *tool,
				  काष्ठा mmap *map,
				  जोड़ perf_event *event, व्योम *data1,
				  माप_प्रकार len1, व्योम *data2, माप_प्रकार len2);

पूर्णांक auxtrace_mmap__पढ़ो(काष्ठा mmap *map, काष्ठा auxtrace_record *itr,
			काष्ठा perf_tool *tool, process_auxtrace_t fn);

पूर्णांक auxtrace_mmap__पढ़ो_snapshot(काष्ठा mmap *map,
				 काष्ठा auxtrace_record *itr,
				 काष्ठा perf_tool *tool, process_auxtrace_t fn,
				 माप_प्रकार snapshot_size);

पूर्णांक auxtrace_queues__init(काष्ठा auxtrace_queues *queues);
पूर्णांक auxtrace_queues__add_event(काष्ठा auxtrace_queues *queues,
			       काष्ठा perf_session *session,
			       जोड़ perf_event *event, off_t data_offset,
			       काष्ठा auxtrace_buffer **buffer_ptr);
काष्ठा auxtrace_queue *
auxtrace_queues__sample_queue(काष्ठा auxtrace_queues *queues,
			      काष्ठा perf_sample *sample,
			      काष्ठा perf_session *session);
पूर्णांक auxtrace_queues__add_sample(काष्ठा auxtrace_queues *queues,
				काष्ठा perf_session *session,
				काष्ठा perf_sample *sample, u64 data_offset,
				u64 reference);
व्योम auxtrace_queues__मुक्त(काष्ठा auxtrace_queues *queues);
पूर्णांक auxtrace_queues__process_index(काष्ठा auxtrace_queues *queues,
				   काष्ठा perf_session *session);
पूर्णांक auxtrace_queue_data(काष्ठा perf_session *session, bool samples,
			bool events);
काष्ठा auxtrace_buffer *auxtrace_buffer__next(काष्ठा auxtrace_queue *queue,
					      काष्ठा auxtrace_buffer *buffer);
व्योम *auxtrace_buffer__get_data(काष्ठा auxtrace_buffer *buffer, पूर्णांक fd);
व्योम auxtrace_buffer__put_data(काष्ठा auxtrace_buffer *buffer);
व्योम auxtrace_buffer__drop_data(काष्ठा auxtrace_buffer *buffer);
व्योम auxtrace_buffer__मुक्त(काष्ठा auxtrace_buffer *buffer);

पूर्णांक auxtrace_heap__add(काष्ठा auxtrace_heap *heap, अचिन्हित पूर्णांक queue_nr,
		       u64 ordinal);
व्योम auxtrace_heap__pop(काष्ठा auxtrace_heap *heap);
व्योम auxtrace_heap__मुक्त(काष्ठा auxtrace_heap *heap);

काष्ठा auxtrace_cache_entry अणु
	काष्ठा hlist_node hash;
	u32 key;
पूर्ण;

काष्ठा auxtrace_cache *auxtrace_cache__new(अचिन्हित पूर्णांक bits, माप_प्रकार entry_size,
					   अचिन्हित पूर्णांक limit_percent);
व्योम auxtrace_cache__मुक्त(काष्ठा auxtrace_cache *auxtrace_cache);
व्योम *auxtrace_cache__alloc_entry(काष्ठा auxtrace_cache *c);
व्योम auxtrace_cache__मुक्त_entry(काष्ठा auxtrace_cache *c, व्योम *entry);
पूर्णांक auxtrace_cache__add(काष्ठा auxtrace_cache *c, u32 key,
			काष्ठा auxtrace_cache_entry *entry);
व्योम auxtrace_cache__हटाओ(काष्ठा auxtrace_cache *c, u32 key);
व्योम *auxtrace_cache__lookup(काष्ठा auxtrace_cache *c, u32 key);

काष्ठा auxtrace_record *auxtrace_record__init(काष्ठा evlist *evlist,
					      पूर्णांक *err);

पूर्णांक auxtrace_parse_snapshot_options(काष्ठा auxtrace_record *itr,
				    काष्ठा record_opts *opts,
				    स्थिर अक्षर *str);
पूर्णांक auxtrace_parse_sample_options(काष्ठा auxtrace_record *itr,
				  काष्ठा evlist *evlist,
				  काष्ठा record_opts *opts, स्थिर अक्षर *str);
व्योम auxtrace_regroup_aux_output(काष्ठा evlist *evlist);
पूर्णांक auxtrace_record__options(काष्ठा auxtrace_record *itr,
			     काष्ठा evlist *evlist,
			     काष्ठा record_opts *opts);
माप_प्रकार auxtrace_record__info_priv_size(काष्ठा auxtrace_record *itr,
				       काष्ठा evlist *evlist);
पूर्णांक auxtrace_record__info_fill(काष्ठा auxtrace_record *itr,
			       काष्ठा perf_session *session,
			       काष्ठा perf_record_auxtrace_info *auxtrace_info,
			       माप_प्रकार priv_size);
व्योम auxtrace_record__मुक्त(काष्ठा auxtrace_record *itr);
पूर्णांक auxtrace_record__snapshot_start(काष्ठा auxtrace_record *itr);
पूर्णांक auxtrace_record__snapshot_finish(काष्ठा auxtrace_record *itr, bool on_निकास);
पूर्णांक auxtrace_record__find_snapshot(काष्ठा auxtrace_record *itr, पूर्णांक idx,
				   काष्ठा auxtrace_mmap *mm,
				   अचिन्हित अक्षर *data, u64 *head, u64 *old);
u64 auxtrace_record__reference(काष्ठा auxtrace_record *itr);
पूर्णांक auxtrace_record__पढ़ो_finish(काष्ठा auxtrace_record *itr, पूर्णांक idx);

पूर्णांक auxtrace_index__auxtrace_event(काष्ठा list_head *head, जोड़ perf_event *event,
				   off_t file_offset);
पूर्णांक auxtrace_index__ग_लिखो(पूर्णांक fd, काष्ठा list_head *head);
पूर्णांक auxtrace_index__process(पूर्णांक fd, u64 size, काष्ठा perf_session *session,
			    bool needs_swap);
व्योम auxtrace_index__मुक्त(काष्ठा list_head *head);

व्योम auxtrace_synth_error(काष्ठा perf_record_auxtrace_error *auxtrace_error, पूर्णांक type,
			  पूर्णांक code, पूर्णांक cpu, pid_t pid, pid_t tid, u64 ip,
			  स्थिर अक्षर *msg, u64 बारtamp);

पूर्णांक perf_event__process_auxtrace_info(काष्ठा perf_session *session,
				      जोड़ perf_event *event);
s64 perf_event__process_auxtrace(काष्ठा perf_session *session,
				 जोड़ perf_event *event);
पूर्णांक perf_event__process_auxtrace_error(काष्ठा perf_session *session,
				       जोड़ perf_event *event);
पूर्णांक itrace_parse_synth_opts(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			    पूर्णांक unset);
व्योम itrace_synth_opts__set_शेष(काष्ठा itrace_synth_opts *synth_opts,
				    bool no_sample);

माप_प्रकार perf_event__ख_लिखो_auxtrace_error(जोड़ perf_event *event, खाता *fp);
व्योम perf_session__auxtrace_error_inc(काष्ठा perf_session *session,
				      जोड़ perf_event *event);
व्योम events_stats__auxtrace_error_warn(स्थिर काष्ठा events_stats *stats);

व्योम addr_filters__init(काष्ठा addr_filters *filts);
व्योम addr_filters__निकास(काष्ठा addr_filters *filts);
पूर्णांक addr_filters__parse_bare_filter(काष्ठा addr_filters *filts,
				    स्थिर अक्षर *filter);
पूर्णांक auxtrace_parse_filters(काष्ठा evlist *evlist);

पूर्णांक auxtrace__process_event(काष्ठा perf_session *session, जोड़ perf_event *event,
			    काष्ठा perf_sample *sample, काष्ठा perf_tool *tool);
व्योम auxtrace__dump_auxtrace_sample(काष्ठा perf_session *session,
				    काष्ठा perf_sample *sample);
पूर्णांक auxtrace__flush_events(काष्ठा perf_session *session, काष्ठा perf_tool *tool);
व्योम auxtrace__मुक्त_events(काष्ठा perf_session *session);
व्योम auxtrace__मुक्त(काष्ठा perf_session *session);
bool auxtrace__evsel_is_auxtrace(काष्ठा perf_session *session,
				 काष्ठा evsel *evsel);

#घोषणा ITRACE_HELP \
"				i[period]:    		synthesize instructions events\n" \
"				b:	    		synthesize branches events (branch misses for Arm SPE)\n" \
"				c:	    		synthesize branches events (calls only)\n"	\
"				r:	    		synthesize branches events (returns only)\n" \
"				x:	    		synthesize transactions events\n"		\
"				w:	    		synthesize ptwrite events\n"		\
"				p:	    		synthesize power events\n"			\
"				o:			synthesize other events recorded due to the use\n" \
"							of aux-output (refer to perf record)\n"	\
"				e[flags]:		synthesize error events\n" \
"							each flag must be preceded by + or -\n" \
"							error flags are: o (overflow)\n" \
"									 l (data lost)\n" \
"				d[flags]:		create a debug log\n" \
"							each flag must be preceded by + or -\n" \
"							log flags are: a (all perf events)\n" \
"				f:	    		synthesize first level cache events\n" \
"				m:	    		synthesize last level cache events\n" \
"				t:	    		synthesize TLB events\n" \
"				a:	    		synthesize remote access events\n" \
"				g[len]:     		synthesize a call chain (use with i or x)\n" \
"				G[len]:			synthesize a call chain on existing event records\n" \
"				l[len]:     		synthesize last branch entries (use with i or x)\n" \
"				L[len]:			synthesize last branch entries on existing event records\n" \
"				sNUMBER:    		skip initial number of events\n"		\
"				q:			quicker (less detailed) decoding\n" \
"				PERIOD[ns|us|ms|i|t]:   specify period to sample stream\n" \
"				concatenate multiple options. Default is ibxwpe or cewp\n"

अटल अंतरभूत
व्योम itrace_synth_opts__set_समय_range(काष्ठा itrace_synth_opts *opts,
				       काष्ठा perf_समय_पूर्णांकerval *pसमय_range,
				       पूर्णांक range_num)
अणु
	opts->pसमय_range = pसमय_range;
	opts->range_num = range_num;
पूर्ण

अटल अंतरभूत
व्योम itrace_synth_opts__clear_समय_range(काष्ठा itrace_synth_opts *opts)
अणु
	opts->pसमय_range = शून्य;
	opts->range_num = 0;
पूर्ण

#अन्यथा
#समावेश "debug.h"

अटल अंतरभूत काष्ठा auxtrace_record *
auxtrace_record__init(काष्ठा evlist *evlist __maybe_unused,
		      पूर्णांक *err)
अणु
	*err = 0;
	वापस शून्य;
पूर्ण

अटल अंतरभूत
व्योम auxtrace_record__मुक्त(काष्ठा auxtrace_record *itr __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace_record__options(काष्ठा auxtrace_record *itr __maybe_unused,
			     काष्ठा evlist *evlist __maybe_unused,
			     काष्ठा record_opts *opts __maybe_unused)
अणु
	वापस 0;
पूर्ण

#घोषणा perf_event__process_auxtrace_info		0
#घोषणा perf_event__process_auxtrace			0
#घोषणा perf_event__process_auxtrace_error		0

अटल अंतरभूत
व्योम perf_session__auxtrace_error_inc(काष्ठा perf_session *session
				      __maybe_unused,
				      जोड़ perf_event *event
				      __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
व्योम events_stats__auxtrace_error_warn(स्थिर काष्ठा events_stats *stats
				       __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
पूर्णांक itrace_parse_synth_opts(स्थिर काष्ठा option *opt __maybe_unused,
			    स्थिर अक्षर *str __maybe_unused,
			    पूर्णांक unset __maybe_unused)
अणु
	pr_err("AUX area tracing not supported\n");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace_parse_snapshot_options(काष्ठा auxtrace_record *itr __maybe_unused,
				    काष्ठा record_opts *opts __maybe_unused,
				    स्थिर अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	pr_err("AUX area tracing not supported\n");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace_parse_sample_options(काष्ठा auxtrace_record *itr __maybe_unused,
				  काष्ठा evlist *evlist __maybe_unused,
				  काष्ठा record_opts *opts __maybe_unused,
				  स्थिर अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	pr_err("AUX area tracing not supported\n");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत
व्योम auxtrace_regroup_aux_output(काष्ठा evlist *evlist __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace__process_event(काष्ठा perf_session *session __maybe_unused,
			    जोड़ perf_event *event __maybe_unused,
			    काष्ठा perf_sample *sample __maybe_unused,
			    काष्ठा perf_tool *tool __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम auxtrace__dump_auxtrace_sample(काष्ठा perf_session *session __maybe_unused,
				    काष्ठा perf_sample *sample __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace__flush_events(काष्ठा perf_session *session __maybe_unused,
			   काष्ठा perf_tool *tool __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम auxtrace__मुक्त_events(काष्ठा perf_session *session __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
व्योम auxtrace_cache__मुक्त(काष्ठा auxtrace_cache *auxtrace_cache __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
व्योम auxtrace__मुक्त(काष्ठा perf_session *session __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace_index__ग_लिखो(पूर्णांक fd __maybe_unused,
			  काष्ठा list_head *head __maybe_unused)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace_index__process(पूर्णांक fd __maybe_unused,
			    u64 size __maybe_unused,
			    काष्ठा perf_session *session __maybe_unused,
			    bool needs_swap __maybe_unused)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत
व्योम auxtrace_index__मुक्त(काष्ठा list_head *head __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
bool auxtrace__evsel_is_auxtrace(काष्ठा perf_session *session __maybe_unused,
				 काष्ठा evsel *evsel __maybe_unused)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत
पूर्णांक auxtrace_parse_filters(काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस 0;
पूर्ण

पूर्णांक auxtrace_mmap__mmap(काष्ठा auxtrace_mmap *mm,
			काष्ठा auxtrace_mmap_params *mp,
			व्योम *userpg, पूर्णांक fd);
व्योम auxtrace_mmap__munmap(काष्ठा auxtrace_mmap *mm);
व्योम auxtrace_mmap_params__init(काष्ठा auxtrace_mmap_params *mp,
				off_t auxtrace_offset,
				अचिन्हित पूर्णांक auxtrace_pages,
				bool auxtrace_overग_लिखो);
व्योम auxtrace_mmap_params__set_idx(काष्ठा auxtrace_mmap_params *mp,
				   काष्ठा evlist *evlist, पूर्णांक idx,
				   bool per_cpu);

#घोषणा ITRACE_HELP ""

अटल अंतरभूत
व्योम itrace_synth_opts__set_समय_range(काष्ठा itrace_synth_opts *opts
				       __maybe_unused,
				       काष्ठा perf_समय_पूर्णांकerval *pसमय_range
				       __maybe_unused,
				       पूर्णांक range_num __maybe_unused)
अणु
पूर्ण

अटल अंतरभूत
व्योम itrace_synth_opts__clear_समय_range(काष्ठा itrace_synth_opts *opts
					 __maybe_unused)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
