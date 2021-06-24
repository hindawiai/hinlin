<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RING_BUFFER_H
#घोषणा _LINUX_RING_BUFFER_H

#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/poll.h>

काष्ठा trace_buffer;
काष्ठा ring_buffer_iter;

/*
 * Don't refer to this काष्ठा directly, use functions below.
 */
काष्ठा ring_buffer_event अणु
	u32		type_len:5, समय_delta:27;

	u32		array[];
पूर्ण;

/**
 * क्रमागत ring_buffer_type - पूर्णांकernal ring buffer types
 *
 * @RINGBUF_TYPE_PADDING:	Left over page padding or discarded event
 *				 If समय_delta is 0:
 *				  array is ignored
 *				  size is variable depending on how much
 *				  padding is needed
 *				 If समय_delta is non zero:
 *				  array[0] holds the actual length
 *				  size = 4 + length (bytes)
 *
 * @RINGBUF_TYPE_TIME_EXTEND:	Extend the समय delta
 *				 array[0] = समय delta (28 .. 59)
 *				 size = 8 bytes
 *
 * @RINGBUF_TYPE_TIME_STAMP:	Absolute बारtamp
 *				 Same क्रमmat as TIME_EXTEND except that the
 *				 value is an असलolute बारtamp, not a delta
 *				 event.समय_delta contains bottom 27 bits
 *				 array[0] = top (28 .. 59) bits
 *				 size = 8 bytes
 *
 * <= @RINGBUF_TYPE_DATA_TYPE_LEN_MAX:
 *				Data record
 *				 If type_len is zero:
 *				  array[0] holds the actual length
 *				  array[1..(length+3)/4] holds data
 *				  size = 4 + length (bytes)
 *				 अन्यथा
 *				  length = type_len << 2
 *				  array[0..(length+3)/4-1] holds data
 *				  size = 4 + length (bytes)
 */
क्रमागत ring_buffer_type अणु
	RINGBUF_TYPE_DATA_TYPE_LEN_MAX = 28,
	RINGBUF_TYPE_PADDING,
	RINGBUF_TYPE_TIME_EXTEND,
	RINGBUF_TYPE_TIME_STAMP,
पूर्ण;

अचिन्हित ring_buffer_event_length(काष्ठा ring_buffer_event *event);
व्योम *ring_buffer_event_data(काष्ठा ring_buffer_event *event);
u64 ring_buffer_event_समय_stamp(काष्ठा trace_buffer *buffer,
				 काष्ठा ring_buffer_event *event);

/*
 * ring_buffer_discard_commit will हटाओ an event that has not
 *   been committed yet. If this is used, then ring_buffer_unlock_commit
 *   must not be called on the discarded event. This function
 *   will try to हटाओ the event from the ring buffer completely
 *   अगर another event has not been written after it.
 *
 * Example use:
 *
 *  अगर (some_condition)
 *    ring_buffer_discard_commit(buffer, event);
 *  अन्यथा
 *    ring_buffer_unlock_commit(buffer, event);
 */
व्योम ring_buffer_discard_commit(काष्ठा trace_buffer *buffer,
				काष्ठा ring_buffer_event *event);

/*
 * size is in bytes क्रम each per CPU buffer.
 */
काष्ठा trace_buffer *
__ring_buffer_alloc(अचिन्हित दीर्घ size, अचिन्हित flags, काष्ठा lock_class_key *key);

/*
 * Because the ring buffer is generic, अगर other users of the ring buffer get
 * traced by ftrace, it can produce lockdep warnings. We need to keep each
 * ring buffer's lock class separate.
 */
#घोषणा ring_buffer_alloc(size, flags)			\
(अणु							\
	अटल काष्ठा lock_class_key __key;		\
	__ring_buffer_alloc((size), (flags), &__key);	\
पूर्ण)

पूर्णांक ring_buffer_रुको(काष्ठा trace_buffer *buffer, पूर्णांक cpu, पूर्णांक full);
__poll_t ring_buffer_poll_रुको(काष्ठा trace_buffer *buffer, पूर्णांक cpu,
			  काष्ठा file *filp, poll_table *poll_table);


#घोषणा RING_BUFFER_ALL_CPUS -1

व्योम ring_buffer_मुक्त(काष्ठा trace_buffer *buffer);

पूर्णांक ring_buffer_resize(काष्ठा trace_buffer *buffer, अचिन्हित दीर्घ size, पूर्णांक cpu);

व्योम ring_buffer_change_overग_लिखो(काष्ठा trace_buffer *buffer, पूर्णांक val);

काष्ठा ring_buffer_event *ring_buffer_lock_reserve(काष्ठा trace_buffer *buffer,
						   अचिन्हित दीर्घ length);
पूर्णांक ring_buffer_unlock_commit(काष्ठा trace_buffer *buffer,
			      काष्ठा ring_buffer_event *event);
पूर्णांक ring_buffer_ग_लिखो(काष्ठा trace_buffer *buffer,
		      अचिन्हित दीर्घ length, व्योम *data);

व्योम ring_buffer_nest_start(काष्ठा trace_buffer *buffer);
व्योम ring_buffer_nest_end(काष्ठा trace_buffer *buffer);

काष्ठा ring_buffer_event *
ring_buffer_peek(काष्ठा trace_buffer *buffer, पूर्णांक cpu, u64 *ts,
		 अचिन्हित दीर्घ *lost_events);
काष्ठा ring_buffer_event *
ring_buffer_consume(काष्ठा trace_buffer *buffer, पूर्णांक cpu, u64 *ts,
		    अचिन्हित दीर्घ *lost_events);

काष्ठा ring_buffer_iter *
ring_buffer_पढ़ो_prepare(काष्ठा trace_buffer *buffer, पूर्णांक cpu, gfp_t flags);
व्योम ring_buffer_पढ़ो_prepare_sync(व्योम);
व्योम ring_buffer_पढ़ो_start(काष्ठा ring_buffer_iter *iter);
व्योम ring_buffer_पढ़ो_finish(काष्ठा ring_buffer_iter *iter);

काष्ठा ring_buffer_event *
ring_buffer_iter_peek(काष्ठा ring_buffer_iter *iter, u64 *ts);
व्योम ring_buffer_iter_advance(काष्ठा ring_buffer_iter *iter);
व्योम ring_buffer_iter_reset(काष्ठा ring_buffer_iter *iter);
पूर्णांक ring_buffer_iter_empty(काष्ठा ring_buffer_iter *iter);
bool ring_buffer_iter_dropped(काष्ठा ring_buffer_iter *iter);

अचिन्हित दीर्घ ring_buffer_size(काष्ठा trace_buffer *buffer, पूर्णांक cpu);

व्योम ring_buffer_reset_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
व्योम ring_buffer_reset_online_cpus(काष्ठा trace_buffer *buffer);
व्योम ring_buffer_reset(काष्ठा trace_buffer *buffer);

#अगर_घोषित CONFIG_RING_BUFFER_ALLOW_SWAP
पूर्णांक ring_buffer_swap_cpu(काष्ठा trace_buffer *buffer_a,
			 काष्ठा trace_buffer *buffer_b, पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत पूर्णांक
ring_buffer_swap_cpu(काष्ठा trace_buffer *buffer_a,
		     काष्ठा trace_buffer *buffer_b, पूर्णांक cpu)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

bool ring_buffer_empty(काष्ठा trace_buffer *buffer);
bool ring_buffer_empty_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);

व्योम ring_buffer_record_disable(काष्ठा trace_buffer *buffer);
व्योम ring_buffer_record_enable(काष्ठा trace_buffer *buffer);
व्योम ring_buffer_record_off(काष्ठा trace_buffer *buffer);
व्योम ring_buffer_record_on(काष्ठा trace_buffer *buffer);
bool ring_buffer_record_is_on(काष्ठा trace_buffer *buffer);
bool ring_buffer_record_is_set_on(काष्ठा trace_buffer *buffer);
व्योम ring_buffer_record_disable_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
व्योम ring_buffer_record_enable_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);

u64 ring_buffer_oldest_event_ts(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
अचिन्हित दीर्घ ring_buffer_bytes_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
अचिन्हित दीर्घ ring_buffer_entries(काष्ठा trace_buffer *buffer);
अचिन्हित दीर्घ ring_buffer_overruns(काष्ठा trace_buffer *buffer);
अचिन्हित दीर्घ ring_buffer_entries_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
अचिन्हित दीर्घ ring_buffer_overrun_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
अचिन्हित दीर्घ ring_buffer_commit_overrun_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
अचिन्हित दीर्घ ring_buffer_dropped_events_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
अचिन्हित दीर्घ ring_buffer_पढ़ो_events_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu);

u64 ring_buffer_समय_stamp(काष्ठा trace_buffer *buffer);
व्योम ring_buffer_normalize_समय_stamp(काष्ठा trace_buffer *buffer,
				      पूर्णांक cpu, u64 *ts);
व्योम ring_buffer_set_घड़ी(काष्ठा trace_buffer *buffer,
			   u64 (*घड़ी)(व्योम));
व्योम ring_buffer_set_समय_stamp_असल(काष्ठा trace_buffer *buffer, bool असल);
bool ring_buffer_समय_stamp_असल(काष्ठा trace_buffer *buffer);

माप_प्रकार ring_buffer_nr_pages(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
माप_प्रकार ring_buffer_nr_dirty_pages(काष्ठा trace_buffer *buffer, पूर्णांक cpu);

व्योम *ring_buffer_alloc_पढ़ो_page(काष्ठा trace_buffer *buffer, पूर्णांक cpu);
व्योम ring_buffer_मुक्त_पढ़ो_page(काष्ठा trace_buffer *buffer, पूर्णांक cpu, व्योम *data);
पूर्णांक ring_buffer_पढ़ो_page(काष्ठा trace_buffer *buffer, व्योम **data_page,
			  माप_प्रकार len, पूर्णांक cpu, पूर्णांक full);

काष्ठा trace_seq;

पूर्णांक ring_buffer_prपूर्णांक_entry_header(काष्ठा trace_seq *s);
पूर्णांक ring_buffer_prपूर्णांक_page_header(काष्ठा trace_seq *s);

क्रमागत ring_buffer_flags अणु
	RB_FL_OVERWRITE		= 1 << 0,
पूर्ण;

#अगर_घोषित CONFIG_RING_BUFFER
पूर्णांक trace_rb_cpu_prepare(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node);
#अन्यथा
#घोषणा trace_rb_cpu_prepare	शून्य
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_RING_BUFFER_H */
