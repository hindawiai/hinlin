<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic ring buffer
 *
 * Copyright (C) 2008 Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <linux/trace_recursion.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/ring_buffer.h>
#समावेश <linux/trace_घड़ी.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/trace_seq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/security.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kthपढ़ो.h>	/* क्रम self test */
#समावेश <linux/module.h>
#समावेश <linux/percpu.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/hash.h>
#समावेश <linux/list.h>
#समावेश <linux/cpu.h>
#समावेश <linux/oom.h>

#समावेश <यंत्र/local.h>

अटल व्योम update_pages_handler(काष्ठा work_काष्ठा *work);

/*
 * The ring buffer header is special. We must manually up keep it.
 */
पूर्णांक ring_buffer_prपूर्णांक_entry_header(काष्ठा trace_seq *s)
अणु
	trace_seq_माला_दो(s, "# compressed entry header\n");
	trace_seq_माला_दो(s, "\ttype_len    :    5 bits\n");
	trace_seq_माला_दो(s, "\ttime_delta  :   27 bits\n");
	trace_seq_माला_दो(s, "\tarray       :   32 bits\n");
	trace_seq_अ_दो(s, '\n');
	trace_seq_म_लिखो(s, "\tpadding     : type == %d\n",
			 RINGBUF_TYPE_PADDING);
	trace_seq_म_लिखो(s, "\ttime_extend : type == %d\n",
			 RINGBUF_TYPE_TIME_EXTEND);
	trace_seq_म_लिखो(s, "\ttime_stamp : type == %d\n",
			 RINGBUF_TYPE_TIME_STAMP);
	trace_seq_म_लिखो(s, "\tdata max type_len  == %d\n",
			 RINGBUF_TYPE_DATA_TYPE_LEN_MAX);

	वापस !trace_seq_has_overflowed(s);
पूर्ण

/*
 * The ring buffer is made up of a list of pages. A separate list of pages is
 * allocated क्रम each CPU. A ग_लिखोr may only ग_लिखो to a buffer that is
 * associated with the CPU it is currently executing on.  A पढ़ोer may पढ़ो
 * from any per cpu buffer.
 *
 * The पढ़ोer is special. For each per cpu buffer, the पढ़ोer has its own
 * पढ़ोer page. When a पढ़ोer has पढ़ो the entire पढ़ोer page, this पढ़ोer
 * page is swapped with another page in the ring buffer.
 *
 * Now, as दीर्घ as the ग_लिखोr is off the पढ़ोer page, the पढ़ोer can करो what
 * ever it wants with that page. The ग_लिखोr will never ग_लिखो to that page
 * again (as दीर्घ as it is out of the ring buffer).
 *
 * Here's some silly ASCII art.
 *
 *   +------+
 *   |पढ़ोer|          RING BUFFER
 *   |page  |
 *   +------+        +---+   +---+   +---+
 *                   |   |-->|   |-->|   |
 *                   +---+   +---+   +---+
 *                     ^               |
 *                     |               |
 *                     +---------------+
 *
 *
 *   +------+
 *   |पढ़ोer|          RING BUFFER
 *   |page  |------------------v
 *   +------+        +---+   +---+   +---+
 *                   |   |-->|   |-->|   |
 *                   +---+   +---+   +---+
 *                     ^               |
 *                     |               |
 *                     +---------------+
 *
 *
 *   +------+
 *   |पढ़ोer|          RING BUFFER
 *   |page  |------------------v
 *   +------+        +---+   +---+   +---+
 *      ^            |   |-->|   |-->|   |
 *      |            +---+   +---+   +---+
 *      |                              |
 *      |                              |
 *      +------------------------------+
 *
 *
 *   +------+
 *   |buffer|          RING BUFFER
 *   |page  |------------------v
 *   +------+        +---+   +---+   +---+
 *      ^            |   |   |   |-->|   |
 *      |   New      +---+   +---+   +---+
 *      |  Reader------^               |
 *      |   page                       |
 *      +------------------------------+
 *
 *
 * After we make this swap, the पढ़ोer can hand this page off to the splice
 * code and be करोne with it. It can even allocate a new page अगर it needs to
 * and swap that पूर्णांकo the ring buffer.
 *
 * We will be using cmpxchg soon to make all this lockless.
 *
 */

/* Used क्रम inभागidual buffers (after the counter) */
#घोषणा RB_BUFFER_OFF		(1 << 20)

#घोषणा BUF_PAGE_HDR_SIZE दुरत्व(काष्ठा buffer_data_page, data)

#घोषणा RB_EVNT_HDR_SIZE (दुरत्व(काष्ठा ring_buffer_event, array))
#घोषणा RB_ALIGNMENT		4U
#घोषणा RB_MAX_SMALL_DATA	(RB_ALIGNMENT * RINGBUF_TYPE_DATA_TYPE_LEN_MAX)
#घोषणा RB_EVNT_MIN_SIZE	8U	/* two 32bit words */

#अगर_अघोषित CONFIG_HAVE_64BIT_ALIGNED_ACCESS
# define RB_FORCE_8BYTE_ALIGNMENT	0
# define RB_ARCH_ALIGNMENT		RB_ALIGNMENT
#अन्यथा
# define RB_FORCE_8BYTE_ALIGNMENT	1
# define RB_ARCH_ALIGNMENT		8U
#पूर्ण_अगर

#घोषणा RB_ALIGN_DATA		__aligned(RB_ARCH_ALIGNMENT)

/* define RINGBUF_TYPE_DATA क्रम 'case RINGBUF_TYPE_DATA:' */
#घोषणा RINGBUF_TYPE_DATA 0 ... RINGBUF_TYPE_DATA_TYPE_LEN_MAX

क्रमागत अणु
	RB_LEN_TIME_EXTEND = 8,
	RB_LEN_TIME_STAMP =  8,
पूर्ण;

#घोषणा skip_समय_extend(event) \
	((काष्ठा ring_buffer_event *)((अक्षर *)event + RB_LEN_TIME_EXTEND))

#घोषणा extended_समय(event) \
	(event->type_len >= RINGBUF_TYPE_TIME_EXTEND)

अटल अंतरभूत पूर्णांक rb_null_event(काष्ठा ring_buffer_event *event)
अणु
	वापस event->type_len == RINGBUF_TYPE_PADDING && !event->समय_delta;
पूर्ण

अटल व्योम rb_event_set_padding(काष्ठा ring_buffer_event *event)
अणु
	/* padding has a शून्य समय_delta */
	event->type_len = RINGBUF_TYPE_PADDING;
	event->समय_delta = 0;
पूर्ण

अटल अचिन्हित
rb_event_data_length(काष्ठा ring_buffer_event *event)
अणु
	अचिन्हित length;

	अगर (event->type_len)
		length = event->type_len * RB_ALIGNMENT;
	अन्यथा
		length = event->array[0];
	वापस length + RB_EVNT_HDR_SIZE;
पूर्ण

/*
 * Return the length of the given event. Will वापस
 * the length of the समय extend अगर the event is a
 * समय extend.
 */
अटल अंतरभूत अचिन्हित
rb_event_length(काष्ठा ring_buffer_event *event)
अणु
	चयन (event->type_len) अणु
	हाल RINGBUF_TYPE_PADDING:
		अगर (rb_null_event(event))
			/* undefined */
			वापस -1;
		वापस  event->array[0] + RB_EVNT_HDR_SIZE;

	हाल RINGBUF_TYPE_TIME_EXTEND:
		वापस RB_LEN_TIME_EXTEND;

	हाल RINGBUF_TYPE_TIME_STAMP:
		वापस RB_LEN_TIME_STAMP;

	हाल RINGBUF_TYPE_DATA:
		वापस rb_event_data_length(event);
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
	/* not hit */
	वापस 0;
पूर्ण

/*
 * Return total length of समय extend and data,
 *   or just the event length क्रम all other events.
 */
अटल अंतरभूत अचिन्हित
rb_event_ts_length(काष्ठा ring_buffer_event *event)
अणु
	अचिन्हित len = 0;

	अगर (extended_समय(event)) अणु
		/* समय extends include the data event after it */
		len = RB_LEN_TIME_EXTEND;
		event = skip_समय_extend(event);
	पूर्ण
	वापस len + rb_event_length(event);
पूर्ण

/**
 * ring_buffer_event_length - वापस the length of the event
 * @event: the event to get the length of
 *
 * Returns the size of the data load of a data event.
 * If the event is something other than a data event, it
 * वापसs the size of the event itself. With the exception
 * of a TIME EXTEND, where it still वापसs the size of the
 * data load of the data event after it.
 */
अचिन्हित ring_buffer_event_length(काष्ठा ring_buffer_event *event)
अणु
	अचिन्हित length;

	अगर (extended_समय(event))
		event = skip_समय_extend(event);

	length = rb_event_length(event);
	अगर (event->type_len > RINGBUF_TYPE_DATA_TYPE_LEN_MAX)
		वापस length;
	length -= RB_EVNT_HDR_SIZE;
	अगर (length > RB_MAX_SMALL_DATA + माप(event->array[0]))
                length -= माप(event->array[0]);
	वापस length;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_event_length);

/* अंतरभूत क्रम ring buffer fast paths */
अटल __always_अंतरभूत व्योम *
rb_event_data(काष्ठा ring_buffer_event *event)
अणु
	अगर (extended_समय(event))
		event = skip_समय_extend(event);
	WARN_ON_ONCE(event->type_len > RINGBUF_TYPE_DATA_TYPE_LEN_MAX);
	/* If length is in len field, then array[0] has the data */
	अगर (event->type_len)
		वापस (व्योम *)&event->array[0];
	/* Otherwise length is in array[0] and array[1] has the data */
	वापस (व्योम *)&event->array[1];
पूर्ण

/**
 * ring_buffer_event_data - वापस the data of the event
 * @event: the event to get the data from
 */
व्योम *ring_buffer_event_data(काष्ठा ring_buffer_event *event)
अणु
	वापस rb_event_data(event);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_event_data);

#घोषणा क्रम_each_buffer_cpu(buffer, cpu)		\
	क्रम_each_cpu(cpu, buffer->cpumask)

#घोषणा क्रम_each_online_buffer_cpu(buffer, cpu)		\
	क्रम_each_cpu_and(cpu, buffer->cpumask, cpu_online_mask)

#घोषणा TS_SHIFT	27
#घोषणा TS_MASK		((1ULL << TS_SHIFT) - 1)
#घोषणा TS_DELTA_TEST	(~TS_MASK)

अटल u64 rb_event_समय_stamp(काष्ठा ring_buffer_event *event)
अणु
	u64 ts;

	ts = event->array[0];
	ts <<= TS_SHIFT;
	ts += event->समय_delta;

	वापस ts;
पूर्ण

/* Flag when events were overwritten */
#घोषणा RB_MISSED_EVENTS	(1 << 31)
/* Missed count stored at end */
#घोषणा RB_MISSED_STORED	(1 << 30)

काष्ठा buffer_data_page अणु
	u64		 समय_stamp;	/* page समय stamp */
	local_t		 commit;	/* ग_लिखो committed index */
	अचिन्हित अक्षर	 data[] RB_ALIGN_DATA;	/* data of buffer page */
पूर्ण;

/*
 * Note, the buffer_page list must be first. The buffer pages
 * are allocated in cache lines, which means that each buffer
 * page will be at the beginning of a cache line, and thus
 * the least signअगरicant bits will be zero. We use this to
 * add flags in the list काष्ठा poपूर्णांकers, to make the ring buffer
 * lockless.
 */
काष्ठा buffer_page अणु
	काष्ठा list_head list;		/* list of buffer pages */
	local_t		 ग_लिखो;		/* index क्रम next ग_लिखो */
	अचिन्हित	 पढ़ो;		/* index क्रम next पढ़ो */
	local_t		 entries;	/* entries on this page */
	अचिन्हित दीर्घ	 real_end;	/* real end of data */
	काष्ठा buffer_data_page *page;	/* Actual data page */
पूर्ण;

/*
 * The buffer page counters, ग_लिखो and entries, must be reset
 * atomically when crossing page boundaries. To synchronize this
 * update, two counters are inserted पूर्णांकo the number. One is
 * the actual counter क्रम the ग_लिखो position or count on the page.
 *
 * The other is a counter of updaters. Beक्रमe an update happens
 * the update partition of the counter is incremented. This will
 * allow the updater to update the counter atomically.
 *
 * The counter is 20 bits, and the state data is 12.
 */
#घोषणा RB_WRITE_MASK		0xfffff
#घोषणा RB_WRITE_INTCNT		(1 << 20)

अटल व्योम rb_init_page(काष्ठा buffer_data_page *bpage)
अणु
	local_set(&bpage->commit, 0);
पूर्ण

/*
 * Also stolen from mm/slob.c. Thanks to Mathieu Desnoyers क्रम poपूर्णांकing
 * this issue out.
 */
अटल व्योम मुक्त_buffer_page(काष्ठा buffer_page *bpage)
अणु
	मुक्त_page((अचिन्हित दीर्घ)bpage->page);
	kमुक्त(bpage);
पूर्ण

/*
 * We need to fit the समय_stamp delta पूर्णांकo 27 bits.
 */
अटल अंतरभूत पूर्णांक test_समय_stamp(u64 delta)
अणु
	अगर (delta & TS_DELTA_TEST)
		वापस 1;
	वापस 0;
पूर्ण

#घोषणा BUF_PAGE_SIZE (PAGE_SIZE - BUF_PAGE_HDR_SIZE)

/* Max payload is BUF_PAGE_SIZE - header (8bytes) */
#घोषणा BUF_MAX_DATA_SIZE (BUF_PAGE_SIZE - (माप(u32) * 2))

पूर्णांक ring_buffer_prपूर्णांक_page_header(काष्ठा trace_seq *s)
अणु
	काष्ठा buffer_data_page field;

	trace_seq_म_लिखो(s, "\tfield: u64 timestamp;\t"
			 "offset:0;\tsize:%u;\tsigned:%u;\n",
			 (अचिन्हित पूर्णांक)माप(field.समय_stamp),
			 (अचिन्हित पूर्णांक)is_चिन्हित_type(u64));

	trace_seq_म_लिखो(s, "\tfield: local_t commit;\t"
			 "offset:%u;\tsize:%u;\tsigned:%u;\n",
			 (अचिन्हित पूर्णांक)दुरत्व(typeof(field), commit),
			 (अचिन्हित पूर्णांक)माप(field.commit),
			 (अचिन्हित पूर्णांक)is_चिन्हित_type(दीर्घ));

	trace_seq_म_लिखो(s, "\tfield: int overwrite;\t"
			 "offset:%u;\tsize:%u;\tsigned:%u;\n",
			 (अचिन्हित पूर्णांक)दुरत्व(typeof(field), commit),
			 1,
			 (अचिन्हित पूर्णांक)is_चिन्हित_type(दीर्घ));

	trace_seq_म_लिखो(s, "\tfield: char data;\t"
			 "offset:%u;\tsize:%u;\tsigned:%u;\n",
			 (अचिन्हित पूर्णांक)दुरत्व(typeof(field), data),
			 (अचिन्हित पूर्णांक)BUF_PAGE_SIZE,
			 (अचिन्हित पूर्णांक)is_चिन्हित_type(अक्षर));

	वापस !trace_seq_has_overflowed(s);
पूर्ण

काष्ठा rb_irq_work अणु
	काष्ठा irq_work			work;
	रुको_queue_head_t		रुकोers;
	रुको_queue_head_t		full_रुकोers;
	bool				रुकोers_pending;
	bool				full_रुकोers_pending;
	bool				wakeup_full;
पूर्ण;

/*
 * Structure to hold event state and handle nested events.
 */
काष्ठा rb_event_info अणु
	u64			ts;
	u64			delta;
	u64			beक्रमe;
	u64			after;
	अचिन्हित दीर्घ		length;
	काष्ठा buffer_page	*tail_page;
	पूर्णांक			add_बारtamp;
पूर्ण;

/*
 * Used क्रम the add_बारtamp
 *  NONE
 *  EXTEND - wants a समय extend
 *  ABSOLUTE - the buffer requests all events to have असलolute समय stamps
 *  FORCE - क्रमce a full समय stamp.
 */
क्रमागत अणु
	RB_ADD_STAMP_NONE		= 0,
	RB_ADD_STAMP_EXTEND		= BIT(1),
	RB_ADD_STAMP_ABSOLUTE		= BIT(2),
	RB_ADD_STAMP_FORCE		= BIT(3)
पूर्ण;
/*
 * Used क्रम which event context the event is in.
 *  TRANSITION = 0
 *  NMI     = 1
 *  IRQ     = 2
 *  SOFTIRQ = 3
 *  NORMAL  = 4
 *
 * See trace_recursive_lock() comment below क्रम more details.
 */
क्रमागत अणु
	RB_CTX_TRANSITION,
	RB_CTX_NMI,
	RB_CTX_IRQ,
	RB_CTX_SOFTIRQ,
	RB_CTX_NORMAL,
	RB_CTX_MAX
पूर्ण;

#अगर BITS_PER_LONG == 32
#घोषणा RB_TIME_32
#पूर्ण_अगर

/* To test on 64 bit machines */
//#घोषणा RB_TIME_32

#अगर_घोषित RB_TIME_32

काष्ठा rb_समय_काष्ठा अणु
	local_t		cnt;
	local_t		top;
	local_t		bottom;
पूर्ण;
#अन्यथा
#समावेश <यंत्र/local64.h>
काष्ठा rb_समय_काष्ठा अणु
	local64_t	समय;
पूर्ण;
#पूर्ण_अगर
प्रकार काष्ठा rb_समय_काष्ठा rb_समय_प्रकार;

#घोषणा MAX_NEST	5

/*
 * head_page == tail_page && head == tail then buffer is empty.
 */
काष्ठा ring_buffer_per_cpu अणु
	पूर्णांक				cpu;
	atomic_t			record_disabled;
	atomic_t			resize_disabled;
	काष्ठा trace_buffer	*buffer;
	raw_spinlock_t			पढ़ोer_lock;	/* serialize पढ़ोers */
	arch_spinlock_t			lock;
	काष्ठा lock_class_key		lock_key;
	काष्ठा buffer_data_page		*मुक्त_page;
	अचिन्हित दीर्घ			nr_pages;
	अचिन्हित पूर्णांक			current_context;
	काष्ठा list_head		*pages;
	काष्ठा buffer_page		*head_page;	/* पढ़ो from head */
	काष्ठा buffer_page		*tail_page;	/* ग_लिखो to tail */
	काष्ठा buffer_page		*commit_page;	/* committed pages */
	काष्ठा buffer_page		*पढ़ोer_page;
	अचिन्हित दीर्घ			lost_events;
	अचिन्हित दीर्घ			last_overrun;
	अचिन्हित दीर्घ			nest;
	local_t				entries_bytes;
	local_t				entries;
	local_t				overrun;
	local_t				commit_overrun;
	local_t				dropped_events;
	local_t				committing;
	local_t				commits;
	local_t				pages_touched;
	local_t				pages_पढ़ो;
	दीर्घ				last_pages_touch;
	माप_प्रकार				लघुest_full;
	अचिन्हित दीर्घ			पढ़ो;
	अचिन्हित दीर्घ			पढ़ो_bytes;
	rb_समय_प्रकार			ग_लिखो_stamp;
	rb_समय_प्रकार			beक्रमe_stamp;
	u64				event_stamp[MAX_NEST];
	u64				पढ़ो_stamp;
	/* ring buffer pages to update, > 0 to add, < 0 to हटाओ */
	दीर्घ				nr_pages_to_update;
	काष्ठा list_head		new_pages; /* new pages to add */
	काष्ठा work_काष्ठा		update_pages_work;
	काष्ठा completion		update_करोne;

	काष्ठा rb_irq_work		irq_work;
पूर्ण;

काष्ठा trace_buffer अणु
	अचिन्हित			flags;
	पूर्णांक				cpus;
	atomic_t			record_disabled;
	cpumask_var_t			cpumask;

	काष्ठा lock_class_key		*पढ़ोer_lock_key;

	काष्ठा mutex			mutex;

	काष्ठा ring_buffer_per_cpu	**buffers;

	काष्ठा hlist_node		node;
	u64				(*घड़ी)(व्योम);

	काष्ठा rb_irq_work		irq_work;
	bool				समय_stamp_असल;
पूर्ण;

काष्ठा ring_buffer_iter अणु
	काष्ठा ring_buffer_per_cpu	*cpu_buffer;
	अचिन्हित दीर्घ			head;
	अचिन्हित दीर्घ			next_event;
	काष्ठा buffer_page		*head_page;
	काष्ठा buffer_page		*cache_पढ़ोer_page;
	अचिन्हित दीर्घ			cache_पढ़ो;
	u64				पढ़ो_stamp;
	u64				page_stamp;
	काष्ठा ring_buffer_event	*event;
	पूर्णांक				missed_events;
पूर्ण;

#अगर_घोषित RB_TIME_32

/*
 * On 32 bit machines, local64_t is very expensive. As the ring
 * buffer करोesn't need all the features of a true 64 bit atomic,
 * on 32 bit, it uses these functions (64 still uses local64_t).
 *
 * For the ring buffer, 64 bit required operations क्रम the समय is
 * the following:
 *
 *  - Only need 59 bits (uses 60 to make it even).
 *  - Reads may fail अगर it पूर्णांकerrupted a modअगरication of the समय stamp.
 *      It will succeed अगर it did not पूर्णांकerrupt another ग_लिखो even अगर
 *      the पढ़ो itself is पूर्णांकerrupted by a ग_लिखो.
 *      It वापसs whether it was successful or not.
 *
 *  - Writes always succeed and will overग_लिखो other ग_लिखोs and ग_लिखोs
 *      that were करोne by events पूर्णांकerrupting the current ग_लिखो.
 *
 *  - A ग_लिखो followed by a पढ़ो of the same समय stamp will always succeed,
 *      but may not contain the same value.
 *
 *  - A cmpxchg will fail अगर it पूर्णांकerrupted another ग_लिखो or cmpxchg.
 *      Other than that, it acts like a normal cmpxchg.
 *
 * The 60 bit समय stamp is broken up by 30 bits in a top and bottom half
 *  (bottom being the least signअगरicant 30 bits of the 60 bit समय stamp).
 *
 * The two most signअगरicant bits of each half holds a 2 bit counter (0-3).
 * Each update will increment this counter by one.
 * When पढ़ोing the top and bottom, अगर the two counter bits match then the
 *  top and bottom together make a valid 60 bit number.
 */
#घोषणा RB_TIME_SHIFT	30
#घोषणा RB_TIME_VAL_MASK ((1 << RB_TIME_SHIFT) - 1)

अटल अंतरभूत पूर्णांक rb_समय_cnt(अचिन्हित दीर्घ val)
अणु
	वापस (val >> RB_TIME_SHIFT) & 3;
पूर्ण

अटल अंतरभूत u64 rb_समय_val(अचिन्हित दीर्घ top, अचिन्हित दीर्घ bottom)
अणु
	u64 val;

	val = top & RB_TIME_VAL_MASK;
	val <<= RB_TIME_SHIFT;
	val |= bottom & RB_TIME_VAL_MASK;

	वापस val;
पूर्ण

अटल अंतरभूत bool __rb_समय_पढ़ो(rb_समय_प्रकार *t, u64 *ret, अचिन्हित दीर्घ *cnt)
अणु
	अचिन्हित दीर्घ top, bottom;
	अचिन्हित दीर्घ c;

	/*
	 * If the पढ़ो is पूर्णांकerrupted by a ग_लिखो, then the cnt will
	 * be dअगरferent. Loop until both top and bottom have been पढ़ो
	 * without पूर्णांकerruption.
	 */
	करो अणु
		c = local_पढ़ो(&t->cnt);
		top = local_पढ़ो(&t->top);
		bottom = local_पढ़ो(&t->bottom);
	पूर्ण जबतक (c != local_पढ़ो(&t->cnt));

	*cnt = rb_समय_cnt(top);

	/* If top and bottom counts करोn't match, this पूर्णांकerrupted a ग_लिखो */
	अगर (*cnt != rb_समय_cnt(bottom))
		वापस false;

	*ret = rb_समय_val(top, bottom);
	वापस true;
पूर्ण

अटल bool rb_समय_पढ़ो(rb_समय_प्रकार *t, u64 *ret)
अणु
	अचिन्हित दीर्घ cnt;

	वापस __rb_समय_पढ़ो(t, ret, &cnt);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ rb_समय_val_cnt(अचिन्हित दीर्घ val, अचिन्हित दीर्घ cnt)
अणु
	वापस (val & RB_TIME_VAL_MASK) | ((cnt & 3) << RB_TIME_SHIFT);
पूर्ण

अटल अंतरभूत व्योम rb_समय_split(u64 val, अचिन्हित दीर्घ *top, अचिन्हित दीर्घ *bottom)
अणु
	*top = (अचिन्हित दीर्घ)((val >> RB_TIME_SHIFT) & RB_TIME_VAL_MASK);
	*bottom = (अचिन्हित दीर्घ)(val & RB_TIME_VAL_MASK);
पूर्ण

अटल अंतरभूत व्योम rb_समय_val_set(local_t *t, अचिन्हित दीर्घ val, अचिन्हित दीर्घ cnt)
अणु
	val = rb_समय_val_cnt(val, cnt);
	local_set(t, val);
पूर्ण

अटल व्योम rb_समय_set(rb_समय_प्रकार *t, u64 val)
अणु
	अचिन्हित दीर्घ cnt, top, bottom;

	rb_समय_split(val, &top, &bottom);

	/* Writes always succeed with a valid number even अगर it माला_लो पूर्णांकerrupted. */
	करो अणु
		cnt = local_inc_वापस(&t->cnt);
		rb_समय_val_set(&t->top, top, cnt);
		rb_समय_val_set(&t->bottom, bottom, cnt);
	पूर्ण जबतक (cnt != local_पढ़ो(&t->cnt));
पूर्ण

अटल अंतरभूत bool
rb_समय_पढ़ो_cmpxchg(local_t *l, अचिन्हित दीर्घ expect, अचिन्हित दीर्घ set)
अणु
	अचिन्हित दीर्घ ret;

	ret = local_cmpxchg(l, expect, set);
	वापस ret == expect;
पूर्ण

अटल पूर्णांक rb_समय_cmpxchg(rb_समय_प्रकार *t, u64 expect, u64 set)
अणु
	अचिन्हित दीर्घ cnt, top, bottom;
	अचिन्हित दीर्घ cnt2, top2, bottom2;
	u64 val;

	/* The cmpxchg always fails अगर it पूर्णांकerrupted an update */
	 अगर (!__rb_समय_पढ़ो(t, &val, &cnt2))
		 वापस false;

	 अगर (val != expect)
		 वापस false;

	 cnt = local_पढ़ो(&t->cnt);
	 अगर ((cnt & 3) != cnt2)
		 वापस false;

	 cnt2 = cnt + 1;

	 rb_समय_split(val, &top, &bottom);
	 top = rb_समय_val_cnt(top, cnt);
	 bottom = rb_समय_val_cnt(bottom, cnt);

	 rb_समय_split(set, &top2, &bottom2);
	 top2 = rb_समय_val_cnt(top2, cnt2);
	 bottom2 = rb_समय_val_cnt(bottom2, cnt2);

	अगर (!rb_समय_पढ़ो_cmpxchg(&t->cnt, cnt, cnt2))
		वापस false;
	अगर (!rb_समय_पढ़ो_cmpxchg(&t->top, top, top2))
		वापस false;
	अगर (!rb_समय_पढ़ो_cmpxchg(&t->bottom, bottom, bottom2))
		वापस false;
	वापस true;
पूर्ण

#अन्यथा /* 64 bits */

/* local64_t always succeeds */

अटल अंतरभूत bool rb_समय_पढ़ो(rb_समय_प्रकार *t, u64 *ret)
अणु
	*ret = local64_पढ़ो(&t->समय);
	वापस true;
पूर्ण
अटल व्योम rb_समय_set(rb_समय_प्रकार *t, u64 val)
अणु
	local64_set(&t->समय, val);
पूर्ण

अटल bool rb_समय_cmpxchg(rb_समय_प्रकार *t, u64 expect, u64 set)
अणु
	u64 val;
	val = local64_cmpxchg(&t->समय, expect, set);
	वापस val == expect;
पूर्ण
#पूर्ण_अगर

/*
 * Enable this to make sure that the event passed to
 * ring_buffer_event_समय_stamp() is not committed and also
 * is on the buffer that it passed in.
 */
//#घोषणा RB_VERIFY_EVENT
#अगर_घोषित RB_VERIFY_EVENT
अटल काष्ठा list_head *rb_list_head(काष्ठा list_head *list);
अटल व्योम verअगरy_event(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			 व्योम *event)
अणु
	काष्ठा buffer_page *page = cpu_buffer->commit_page;
	काष्ठा buffer_page *tail_page = READ_ONCE(cpu_buffer->tail_page);
	काष्ठा list_head *next;
	दीर्घ commit, ग_लिखो;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)event;
	bool करोne = false;
	पूर्णांक stop = 0;

	/* Make sure the event exists and is not committed yet */
	करो अणु
		अगर (page == tail_page || WARN_ON_ONCE(stop++ > 100))
			करोne = true;
		commit = local_पढ़ो(&page->page->commit);
		ग_लिखो = local_पढ़ो(&page->ग_लिखो);
		अगर (addr >= (अचिन्हित दीर्घ)&page->page->data[commit] &&
		    addr < (अचिन्हित दीर्घ)&page->page->data[ग_लिखो])
			वापस;

		next = rb_list_head(page->list.next);
		page = list_entry(next, काष्ठा buffer_page, list);
	पूर्ण जबतक (!करोne);
	WARN_ON_ONCE(1);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम verअगरy_event(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			 व्योम *event)
अणु
पूर्ण
#पूर्ण_अगर


अटल अंतरभूत u64 rb_समय_stamp(काष्ठा trace_buffer *buffer);

/**
 * ring_buffer_event_समय_stamp - वापस the event's current समय stamp
 * @buffer: The buffer that the event is on
 * @event: the event to get the समय stamp of
 *
 * Note, this must be called after @event is reserved, and beक्रमe it is
 * committed to the ring buffer. And must be called from the same
 * context where the event was reserved (normal, softirq, irq, etc).
 *
 * Returns the समय stamp associated with the current event.
 * If the event has an extended समय stamp, then that is used as
 * the समय stamp to वापस.
 * In the highly unlikely हाल that the event was nested more than
 * the max nesting, then the ग_लिखो_stamp of the buffer is वापसed,
 * otherwise  current समय is वापसed, but that really neither of
 * the last two हालs should ever happen.
 */
u64 ring_buffer_event_समय_stamp(काष्ठा trace_buffer *buffer,
				 काष्ठा ring_buffer_event *event)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = buffer->buffers[smp_processor_id()];
	अचिन्हित पूर्णांक nest;
	u64 ts;

	/* If the event includes an असलolute समय, then just use that */
	अगर (event->type_len == RINGBUF_TYPE_TIME_STAMP)
		वापस rb_event_समय_stamp(event);

	nest = local_पढ़ो(&cpu_buffer->committing);
	verअगरy_event(cpu_buffer, event);
	अगर (WARN_ON_ONCE(!nest))
		जाओ fail;

	/* Read the current saved nesting level समय stamp */
	अगर (likely(--nest < MAX_NEST))
		वापस cpu_buffer->event_stamp[nest];

	/* Shouldn't happen, warn अगर it करोes */
	WARN_ONCE(1, "nest (%d) greater than max", nest);

 fail:
	/* Can only fail on 32 bit */
	अगर (!rb_समय_पढ़ो(&cpu_buffer->ग_लिखो_stamp, &ts))
		/* Screw it, just पढ़ो the current समय */
		ts = rb_समय_stamp(cpu_buffer->buffer);

	वापस ts;
पूर्ण

/**
 * ring_buffer_nr_pages - get the number of buffer pages in the ring buffer
 * @buffer: The ring_buffer to get the number of pages from
 * @cpu: The cpu of the ring_buffer to get the number of pages from
 *
 * Returns the number of pages used by a per_cpu buffer of the ring buffer.
 */
माप_प्रकार ring_buffer_nr_pages(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	वापस buffer->buffers[cpu]->nr_pages;
पूर्ण

/**
 * ring_buffer_nr_pages_dirty - get the number of used pages in the ring buffer
 * @buffer: The ring_buffer to get the number of pages from
 * @cpu: The cpu of the ring_buffer to get the number of pages from
 *
 * Returns the number of pages that have content in the ring buffer.
 */
माप_प्रकार ring_buffer_nr_dirty_pages(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	माप_प्रकार पढ़ो;
	माप_प्रकार cnt;

	पढ़ो = local_पढ़ो(&buffer->buffers[cpu]->pages_पढ़ो);
	cnt = local_पढ़ो(&buffer->buffers[cpu]->pages_touched);
	/* The पढ़ोer can पढ़ो an empty page, but not more than that */
	अगर (cnt < पढ़ो) अणु
		WARN_ON_ONCE(पढ़ो > cnt + 1);
		वापस 0;
	पूर्ण

	वापस cnt - पढ़ो;
पूर्ण

/*
 * rb_wake_up_रुकोers - wake up tasks रुकोing क्रम ring buffer input
 *
 * Schedules a delayed work to wake up any task that is blocked on the
 * ring buffer रुकोers queue.
 */
अटल व्योम rb_wake_up_रुकोers(काष्ठा irq_work *work)
अणु
	काष्ठा rb_irq_work *rbwork = container_of(work, काष्ठा rb_irq_work, work);

	wake_up_all(&rbwork->रुकोers);
	अगर (rbwork->wakeup_full) अणु
		rbwork->wakeup_full = false;
		wake_up_all(&rbwork->full_रुकोers);
	पूर्ण
पूर्ण

/**
 * ring_buffer_रुको - रुको क्रम input to the ring buffer
 * @buffer: buffer to रुको on
 * @cpu: the cpu buffer to रुको on
 * @full: रुको until the percentage of pages are available, अगर @cpu != RING_BUFFER_ALL_CPUS
 *
 * If @cpu == RING_BUFFER_ALL_CPUS then the task will wake up as soon
 * as data is added to any of the @buffer's cpu buffers. Otherwise
 * it will रुको क्रम data to be added to a specअगरic cpu buffer.
 */
पूर्णांक ring_buffer_रुको(काष्ठा trace_buffer *buffer, पूर्णांक cpu, पूर्णांक full)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	DEFINE_WAIT(रुको);
	काष्ठा rb_irq_work *work;
	पूर्णांक ret = 0;

	/*
	 * Depending on what the caller is रुकोing क्रम, either any
	 * data in any cpu buffer, or a specअगरic buffer, put the
	 * caller on the appropriate रुको queue.
	 */
	अगर (cpu == RING_BUFFER_ALL_CPUS) अणु
		work = &buffer->irq_work;
		/* Full only makes sense on per cpu पढ़ोs */
		full = 0;
	पूर्ण अन्यथा अणु
		अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
			वापस -ENODEV;
		cpu_buffer = buffer->buffers[cpu];
		work = &cpu_buffer->irq_work;
	पूर्ण


	जबतक (true) अणु
		अगर (full)
			prepare_to_रुको(&work->full_रुकोers, &रुको, TASK_INTERRUPTIBLE);
		अन्यथा
			prepare_to_रुको(&work->रुकोers, &रुको, TASK_INTERRUPTIBLE);

		/*
		 * The events can happen in critical sections where
		 * checking a work queue can cause deadlocks.
		 * After adding a task to the queue, this flag is set
		 * only to notअगरy events to try to wake up the queue
		 * using irq_work.
		 *
		 * We करोn't clear it even अगर the buffer is no दीर्घer
		 * empty. The flag only causes the next event to run
		 * irq_work to करो the work queue wake up. The worse
		 * that can happen अगर we race with !trace_empty() is that
		 * an event will cause an irq_work to try to wake up
		 * an empty queue.
		 *
		 * There's no reason to protect this flag either, as
		 * the work queue and irq_work logic will करो the necessary
		 * synchronization क्रम the wake ups. The only thing
		 * that is necessary is that the wake up happens after
		 * a task has been queued. It's OK क्रम spurious wake ups.
		 */
		अगर (full)
			work->full_रुकोers_pending = true;
		अन्यथा
			work->रुकोers_pending = true;

		अगर (संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण

		अगर (cpu == RING_BUFFER_ALL_CPUS && !ring_buffer_empty(buffer))
			अवरोध;

		अगर (cpu != RING_BUFFER_ALL_CPUS &&
		    !ring_buffer_empty_cpu(buffer, cpu)) अणु
			अचिन्हित दीर्घ flags;
			bool pagebusy;
			माप_प्रकार nr_pages;
			माप_प्रकार dirty;

			अगर (!full)
				अवरोध;

			raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);
			pagebusy = cpu_buffer->पढ़ोer_page == cpu_buffer->commit_page;
			nr_pages = cpu_buffer->nr_pages;
			dirty = ring_buffer_nr_dirty_pages(buffer, cpu);
			अगर (!cpu_buffer->लघुest_full ||
			    cpu_buffer->लघुest_full < full)
				cpu_buffer->लघुest_full = full;
			raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);
			अगर (!pagebusy &&
			    (!nr_pages || (dirty * 100) > full * nr_pages))
				अवरोध;
		पूर्ण

		schedule();
	पूर्ण

	अगर (full)
		finish_रुको(&work->full_रुकोers, &रुको);
	अन्यथा
		finish_रुको(&work->रुकोers, &रुको);

	वापस ret;
पूर्ण

/**
 * ring_buffer_poll_रुको - poll on buffer input
 * @buffer: buffer to रुको on
 * @cpu: the cpu buffer to रुको on
 * @filp: the file descriptor
 * @poll_table: The poll descriptor
 *
 * If @cpu == RING_BUFFER_ALL_CPUS then the task will wake up as soon
 * as data is added to any of the @buffer's cpu buffers. Otherwise
 * it will रुको क्रम data to be added to a specअगरic cpu buffer.
 *
 * Returns EPOLLIN | EPOLLRDNORM अगर data exists in the buffers,
 * zero otherwise.
 */
__poll_t ring_buffer_poll_रुको(काष्ठा trace_buffer *buffer, पूर्णांक cpu,
			  काष्ठा file *filp, poll_table *poll_table)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा rb_irq_work *work;

	अगर (cpu == RING_BUFFER_ALL_CPUS)
		work = &buffer->irq_work;
	अन्यथा अणु
		अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
			वापस -EINVAL;

		cpu_buffer = buffer->buffers[cpu];
		work = &cpu_buffer->irq_work;
	पूर्ण

	poll_रुको(filp, &work->रुकोers, poll_table);
	work->रुकोers_pending = true;
	/*
	 * There's a tight race between setting the रुकोers_pending and
	 * checking अगर the ring buffer is empty.  Once the रुकोers_pending bit
	 * is set, the next event will wake the task up, but we can get stuck
	 * अगर there's only a single event in.
	 *
	 * FIXME: Ideally, we need a memory barrier on the ग_लिखोr side as well,
	 * but adding a memory barrier to all events will cause too much of a
	 * perक्रमmance hit in the fast path.  We only need a memory barrier when
	 * the buffer goes from empty to having content.  But as this race is
	 * extremely small, and it's not a problem अगर another event comes in, we
	 * will fix it later.
	 */
	smp_mb();

	अगर ((cpu == RING_BUFFER_ALL_CPUS && !ring_buffer_empty(buffer)) ||
	    (cpu != RING_BUFFER_ALL_CPUS && !ring_buffer_empty_cpu(buffer, cpu)))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

/* buffer may be either ring_buffer or ring_buffer_per_cpu */
#घोषणा RB_WARN_ON(b, cond)						\
	(अणु								\
		पूर्णांक _____ret = unlikely(cond);				\
		अगर (_____ret) अणु						\
			अगर (__same_type(*(b), काष्ठा ring_buffer_per_cpu)) अणु \
				काष्ठा ring_buffer_per_cpu *__b =	\
					(व्योम *)b;			\
				atomic_inc(&__b->buffer->record_disabled); \
			पूर्ण अन्यथा						\
				atomic_inc(&b->record_disabled);	\
			WARN_ON(1);					\
		पूर्ण							\
		_____ret;						\
	पूर्ण)

/* Up this अगर you want to test the TIME_EXTENTS and normalization */
#घोषणा DEBUG_SHIFT 0

अटल अंतरभूत u64 rb_समय_stamp(काष्ठा trace_buffer *buffer)
अणु
	u64 ts;

	/* Skip retpolines :-( */
	अगर (IS_ENABLED(CONFIG_RETPOLINE) && likely(buffer->घड़ी == trace_घड़ी_local))
		ts = trace_घड़ी_local();
	अन्यथा
		ts = buffer->घड़ी();

	/* shअगरt to debug/test normalization and TIME_EXTENTS */
	वापस ts << DEBUG_SHIFT;
पूर्ण

u64 ring_buffer_समय_stamp(काष्ठा trace_buffer *buffer)
अणु
	u64 समय;

	preempt_disable_notrace();
	समय = rb_समय_stamp(buffer);
	preempt_enable_notrace();

	वापस समय;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_समय_stamp);

व्योम ring_buffer_normalize_समय_stamp(काष्ठा trace_buffer *buffer,
				      पूर्णांक cpu, u64 *ts)
अणु
	/* Just stupid testing the normalize function and deltas */
	*ts >>= DEBUG_SHIFT;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_normalize_समय_stamp);

/*
 * Making the ring buffer lockless makes things tricky.
 * Although ग_लिखोs only happen on the CPU that they are on,
 * and they only need to worry about पूर्णांकerrupts. Reads can
 * happen on any CPU.
 *
 * The पढ़ोer page is always off the ring buffer, but when the
 * पढ़ोer finishes with a page, it needs to swap its page with
 * a new one from the buffer. The पढ़ोer needs to take from
 * the head (ग_लिखोs go to the tail). But अगर a ग_लिखोr is in overग_लिखो
 * mode and wraps, it must push the head page क्रमward.
 *
 * Here lies the problem.
 *
 * The पढ़ोer must be careful to replace only the head page, and
 * not another one. As described at the top of the file in the
 * ASCII art, the पढ़ोer sets its old page to poपूर्णांक to the next
 * page after head. It then sets the page after head to poपूर्णांक to
 * the old पढ़ोer page. But अगर the ग_लिखोr moves the head page
 * during this operation, the पढ़ोer could end up with the tail.
 *
 * We use cmpxchg to help prevent this race. We also करो something
 * special with the page beक्रमe head. We set the LSB to 1.
 *
 * When the ग_लिखोr must push the page क्रमward, it will clear the
 * bit that poपूर्णांकs to the head page, move the head, and then set
 * the bit that poपूर्णांकs to the new head page.
 *
 * We also करोn't want an पूर्णांकerrupt coming in and moving the head
 * page on another ग_लिखोr. Thus we use the second LSB to catch
 * that too. Thus:
 *
 * head->list->prev->next        bit 1          bit 0
 *                              -------        -------
 * Normal page                     0              0
 * Poपूर्णांकs to head page             0              1
 * New head page                   1              0
 *
 * Note we can not trust the prev poपूर्णांकer of the head page, because:
 *
 * +----+       +-----+        +-----+
 * |    |------>|  T  |---X--->|  N  |
 * |    |<------|     |        |     |
 * +----+       +-----+        +-----+
 *   ^                           ^ |
 *   |          +-----+          | |
 *   +----------|  R  |----------+ |
 *              |     |<-----------+
 *              +-----+
 *
 * Key:  ---X-->  HEAD flag set in poपूर्णांकer
 *         T      Tail page
 *         R      Reader page
 *         N      Next page
 *
 * (see __rb_reserve_next() to see where this happens)
 *
 *  What the above shows is that the पढ़ोer just swapped out
 *  the पढ़ोer page with a page in the buffer, but beक्रमe it
 *  could make the new header poपूर्णांक back to the new page added
 *  it was preempted by a ग_लिखोr. The ग_लिखोr moved क्रमward onto
 *  the new page added by the पढ़ोer and is about to move क्रमward
 *  again.
 *
 *  You can see, it is legitimate क्रम the previous poपूर्णांकer of
 *  the head (or any page) not to poपूर्णांक back to itself. But only
 *  temporarily.
 */

#घोषणा RB_PAGE_NORMAL		0UL
#घोषणा RB_PAGE_HEAD		1UL
#घोषणा RB_PAGE_UPDATE		2UL


#घोषणा RB_FLAG_MASK		3UL

/* PAGE_MOVED is not part of the mask */
#घोषणा RB_PAGE_MOVED		4UL

/*
 * rb_list_head - हटाओ any bit
 */
अटल काष्ठा list_head *rb_list_head(काष्ठा list_head *list)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)list;

	वापस (काष्ठा list_head *)(val & ~RB_FLAG_MASK);
पूर्ण

/*
 * rb_is_head_page - test अगर the given page is the head page
 *
 * Because the पढ़ोer may move the head_page poपूर्णांकer, we can
 * not trust what the head page is (it may be poपूर्णांकing to
 * the पढ़ोer page). But अगर the next page is a header page,
 * its flags will be non zero.
 */
अटल अंतरभूत पूर्णांक
rb_is_head_page(काष्ठा buffer_page *page, काष्ठा list_head *list)
अणु
	अचिन्हित दीर्घ val;

	val = (अचिन्हित दीर्घ)list->next;

	अगर ((val & ~RB_FLAG_MASK) != (अचिन्हित दीर्घ)&page->list)
		वापस RB_PAGE_MOVED;

	वापस val & RB_FLAG_MASK;
पूर्ण

/*
 * rb_is_पढ़ोer_page
 *
 * The unique thing about the पढ़ोer page, is that, अगर the
 * ग_लिखोr is ever on it, the previous poपूर्णांकer never poपूर्णांकs
 * back to the पढ़ोer page.
 */
अटल bool rb_is_पढ़ोer_page(काष्ठा buffer_page *page)
अणु
	काष्ठा list_head *list = page->list.prev;

	वापस rb_list_head(list->next) != &page->list;
पूर्ण

/*
 * rb_set_list_to_head - set a list_head to be poपूर्णांकing to head.
 */
अटल व्योम rb_set_list_to_head(काष्ठा list_head *list)
अणु
	अचिन्हित दीर्घ *ptr;

	ptr = (अचिन्हित दीर्घ *)&list->next;
	*ptr |= RB_PAGE_HEAD;
	*ptr &= ~RB_PAGE_UPDATE;
पूर्ण

/*
 * rb_head_page_activate - sets up head page
 */
अटल व्योम rb_head_page_activate(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा buffer_page *head;

	head = cpu_buffer->head_page;
	अगर (!head)
		वापस;

	/*
	 * Set the previous list poपूर्णांकer to have the HEAD flag.
	 */
	rb_set_list_to_head(head->list.prev);
पूर्ण

अटल व्योम rb_list_head_clear(काष्ठा list_head *list)
अणु
	अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)&list->next;

	*ptr &= ~RB_FLAG_MASK;
पूर्ण

/*
 * rb_head_page_deactivate - clears head page ptr (क्रम मुक्त list)
 */
अटल व्योम
rb_head_page_deactivate(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा list_head *hd;

	/* Go through the whole list and clear any poपूर्णांकers found. */
	rb_list_head_clear(cpu_buffer->pages);

	list_क्रम_each(hd, cpu_buffer->pages)
		rb_list_head_clear(hd);
पूर्ण

अटल पूर्णांक rb_head_page_set(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			    काष्ठा buffer_page *head,
			    काष्ठा buffer_page *prev,
			    पूर्णांक old_flag, पूर्णांक new_flag)
अणु
	काष्ठा list_head *list;
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)&head->list;
	अचिन्हित दीर्घ ret;

	list = &prev->list;

	val &= ~RB_FLAG_MASK;

	ret = cmpxchg((अचिन्हित दीर्घ *)&list->next,
		      val | old_flag, val | new_flag);

	/* check अगर the पढ़ोer took the page */
	अगर ((ret & ~RB_FLAG_MASK) != val)
		वापस RB_PAGE_MOVED;

	वापस ret & RB_FLAG_MASK;
पूर्ण

अटल पूर्णांक rb_head_page_set_update(काष्ठा ring_buffer_per_cpu *cpu_buffer,
				   काष्ठा buffer_page *head,
				   काष्ठा buffer_page *prev,
				   पूर्णांक old_flag)
अणु
	वापस rb_head_page_set(cpu_buffer, head, prev,
				old_flag, RB_PAGE_UPDATE);
पूर्ण

अटल पूर्णांक rb_head_page_set_head(काष्ठा ring_buffer_per_cpu *cpu_buffer,
				 काष्ठा buffer_page *head,
				 काष्ठा buffer_page *prev,
				 पूर्णांक old_flag)
अणु
	वापस rb_head_page_set(cpu_buffer, head, prev,
				old_flag, RB_PAGE_HEAD);
पूर्ण

अटल पूर्णांक rb_head_page_set_normal(काष्ठा ring_buffer_per_cpu *cpu_buffer,
				   काष्ठा buffer_page *head,
				   काष्ठा buffer_page *prev,
				   पूर्णांक old_flag)
अणु
	वापस rb_head_page_set(cpu_buffer, head, prev,
				old_flag, RB_PAGE_NORMAL);
पूर्ण

अटल अंतरभूत व्योम rb_inc_page(काष्ठा buffer_page **bpage)
अणु
	काष्ठा list_head *p = rb_list_head((*bpage)->list.next);

	*bpage = list_entry(p, काष्ठा buffer_page, list);
पूर्ण

अटल काष्ठा buffer_page *
rb_set_head_page(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा buffer_page *head;
	काष्ठा buffer_page *page;
	काष्ठा list_head *list;
	पूर्णांक i;

	अगर (RB_WARN_ON(cpu_buffer, !cpu_buffer->head_page))
		वापस शून्य;

	/* sanity check */
	list = cpu_buffer->pages;
	अगर (RB_WARN_ON(cpu_buffer, rb_list_head(list->prev->next) != list))
		वापस शून्य;

	page = head = cpu_buffer->head_page;
	/*
	 * It is possible that the ग_लिखोr moves the header behind
	 * where we started, and we miss in one loop.
	 * A second loop should grab the header, but we'll करो
	 * three loops just because I'm paranoid.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		करो अणु
			अगर (rb_is_head_page(page, page->list.prev)) अणु
				cpu_buffer->head_page = page;
				वापस page;
			पूर्ण
			rb_inc_page(&page);
		पूर्ण जबतक (page != head);
	पूर्ण

	RB_WARN_ON(cpu_buffer, 1);

	वापस शून्य;
पूर्ण

अटल पूर्णांक rb_head_page_replace(काष्ठा buffer_page *old,
				काष्ठा buffer_page *new)
अणु
	अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)&old->list.prev->next;
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ ret;

	val = *ptr & ~RB_FLAG_MASK;
	val |= RB_PAGE_HEAD;

	ret = cmpxchg(ptr, val, (अचिन्हित दीर्घ)&new->list);

	वापस ret == val;
पूर्ण

/*
 * rb_tail_page_update - move the tail page क्रमward
 */
अटल व्योम rb_tail_page_update(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			       काष्ठा buffer_page *tail_page,
			       काष्ठा buffer_page *next_page)
अणु
	अचिन्हित दीर्घ old_entries;
	अचिन्हित दीर्घ old_ग_लिखो;

	/*
	 * The tail page now needs to be moved क्रमward.
	 *
	 * We need to reset the tail page, but without messing
	 * with possible erasing of data brought in by पूर्णांकerrupts
	 * that have moved the tail page and are currently on it.
	 *
	 * We add a counter to the ग_लिखो field to denote this.
	 */
	old_ग_लिखो = local_add_वापस(RB_WRITE_INTCNT, &next_page->ग_लिखो);
	old_entries = local_add_वापस(RB_WRITE_INTCNT, &next_page->entries);

	local_inc(&cpu_buffer->pages_touched);
	/*
	 * Just make sure we have seen our old_ग_लिखो and synchronize
	 * with any पूर्णांकerrupts that come in.
	 */
	barrier();

	/*
	 * If the tail page is still the same as what we think
	 * it is, then it is up to us to update the tail
	 * poपूर्णांकer.
	 */
	अगर (tail_page == READ_ONCE(cpu_buffer->tail_page)) अणु
		/* Zero the ग_लिखो counter */
		अचिन्हित दीर्घ val = old_ग_लिखो & ~RB_WRITE_MASK;
		अचिन्हित दीर्घ eval = old_entries & ~RB_WRITE_MASK;

		/*
		 * This will only succeed अगर an पूर्णांकerrupt did
		 * not come in and change it. In which हाल, we
		 * करो not want to modअगरy it.
		 *
		 * We add (व्योम) to let the compiler know that we करो not care
		 * about the वापस value of these functions. We use the
		 * cmpxchg to only update अगर an पूर्णांकerrupt did not alपढ़ोy
		 * करो it क्रम us. If the cmpxchg fails, we करोn't care.
		 */
		(व्योम)local_cmpxchg(&next_page->ग_लिखो, old_ग_लिखो, val);
		(व्योम)local_cmpxchg(&next_page->entries, old_entries, eval);

		/*
		 * No need to worry about races with clearing out the commit.
		 * it only can increment when a commit takes place. But that
		 * only happens in the outer most nested commit.
		 */
		local_set(&next_page->page->commit, 0);

		/* Again, either we update tail_page or an पूर्णांकerrupt करोes */
		(व्योम)cmpxchg(&cpu_buffer->tail_page, tail_page, next_page);
	पूर्ण
पूर्ण

अटल पूर्णांक rb_check_bpage(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			  काष्ठा buffer_page *bpage)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)bpage;

	अगर (RB_WARN_ON(cpu_buffer, val & RB_FLAG_MASK))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * rb_check_list - make sure a poपूर्णांकer to a list has the last bits zero
 */
अटल पूर्णांक rb_check_list(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			 काष्ठा list_head *list)
अणु
	अगर (RB_WARN_ON(cpu_buffer, rb_list_head(list->prev) != list->prev))
		वापस 1;
	अगर (RB_WARN_ON(cpu_buffer, rb_list_head(list->next) != list->next))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * rb_check_pages - पूर्णांकegrity check of buffer pages
 * @cpu_buffer: CPU buffer with pages to test
 *
 * As a safety measure we check to make sure the data pages have not
 * been corrupted.
 */
अटल पूर्णांक rb_check_pages(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा list_head *head = cpu_buffer->pages;
	काष्ठा buffer_page *bpage, *पंचांगp;

	/* Reset the head page अगर it exists */
	अगर (cpu_buffer->head_page)
		rb_set_head_page(cpu_buffer);

	rb_head_page_deactivate(cpu_buffer);

	अगर (RB_WARN_ON(cpu_buffer, head->next->prev != head))
		वापस -1;
	अगर (RB_WARN_ON(cpu_buffer, head->prev->next != head))
		वापस -1;

	अगर (rb_check_list(cpu_buffer, head))
		वापस -1;

	list_क्रम_each_entry_safe(bpage, पंचांगp, head, list) अणु
		अगर (RB_WARN_ON(cpu_buffer,
			       bpage->list.next->prev != &bpage->list))
			वापस -1;
		अगर (RB_WARN_ON(cpu_buffer,
			       bpage->list.prev->next != &bpage->list))
			वापस -1;
		अगर (rb_check_list(cpu_buffer, &bpage->list))
			वापस -1;
	पूर्ण

	rb_head_page_activate(cpu_buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक __rb_allocate_pages(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		दीर्घ nr_pages, काष्ठा list_head *pages)
अणु
	काष्ठा buffer_page *bpage, *पंचांगp;
	bool user_thपढ़ो = current->mm != शून्य;
	gfp_t mflags;
	दीर्घ i;

	/*
	 * Check अगर the available memory is there first.
	 * Note, si_mem_available() only gives us a rough estimate of available
	 * memory. It may not be accurate. But we करोn't care, we just want
	 * to prevent करोing any allocation when it is obvious that it is
	 * not going to succeed.
	 */
	i = si_mem_available();
	अगर (i < nr_pages)
		वापस -ENOMEM;

	/*
	 * __GFP_RETRY_MAYFAIL flag makes sure that the allocation fails
	 * gracefully without invoking oom-समाप्तer and the प्रणाली is not
	 * destabilized.
	 */
	mflags = GFP_KERNEL | __GFP_RETRY_MAYFAIL;

	/*
	 * If a user thपढ़ो allocates too much, and si_mem_available()
	 * reports there's enough memory, even though there is not.
	 * Make sure the OOM समाप्तer समाप्तs this thपढ़ो. This can happen
	 * even with RETRY_MAYFAIL because another task may be करोing
	 * an allocation after this task has taken all memory.
	 * This is the task the OOM समाप्तer needs to take out during this
	 * loop, even अगर it was triggered by an allocation somewhere अन्यथा.
	 */
	अगर (user_thपढ़ो)
		set_current_oom_origin();
	क्रम (i = 0; i < nr_pages; i++) अणु
		काष्ठा page *page;

		bpage = kzalloc_node(ALIGN(माप(*bpage), cache_line_size()),
				    mflags, cpu_to_node(cpu_buffer->cpu));
		अगर (!bpage)
			जाओ मुक्त_pages;

		rb_check_bpage(cpu_buffer, bpage);

		list_add(&bpage->list, pages);

		page = alloc_pages_node(cpu_to_node(cpu_buffer->cpu), mflags, 0);
		अगर (!page)
			जाओ मुक्त_pages;
		bpage->page = page_address(page);
		rb_init_page(bpage->page);

		अगर (user_thपढ़ो && fatal_संकेत_pending(current))
			जाओ मुक्त_pages;
	पूर्ण
	अगर (user_thपढ़ो)
		clear_current_oom_origin();

	वापस 0;

मुक्त_pages:
	list_क्रम_each_entry_safe(bpage, पंचांगp, pages, list) अणु
		list_del_init(&bpage->list);
		मुक्त_buffer_page(bpage);
	पूर्ण
	अगर (user_thपढ़ो)
		clear_current_oom_origin();

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक rb_allocate_pages(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			     अचिन्हित दीर्घ nr_pages)
अणु
	LIST_HEAD(pages);

	WARN_ON(!nr_pages);

	अगर (__rb_allocate_pages(cpu_buffer, nr_pages, &pages))
		वापस -ENOMEM;

	/*
	 * The ring buffer page list is a circular list that करोes not
	 * start and end with a list head. All page list items poपूर्णांक to
	 * other pages.
	 */
	cpu_buffer->pages = pages.next;
	list_del(&pages);

	cpu_buffer->nr_pages = nr_pages;

	rb_check_pages(cpu_buffer);

	वापस 0;
पूर्ण

अटल काष्ठा ring_buffer_per_cpu *
rb_allocate_cpu_buffer(काष्ठा trace_buffer *buffer, दीर्घ nr_pages, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा buffer_page *bpage;
	काष्ठा page *page;
	पूर्णांक ret;

	cpu_buffer = kzalloc_node(ALIGN(माप(*cpu_buffer), cache_line_size()),
				  GFP_KERNEL, cpu_to_node(cpu));
	अगर (!cpu_buffer)
		वापस शून्य;

	cpu_buffer->cpu = cpu;
	cpu_buffer->buffer = buffer;
	raw_spin_lock_init(&cpu_buffer->पढ़ोer_lock);
	lockdep_set_class(&cpu_buffer->पढ़ोer_lock, buffer->पढ़ोer_lock_key);
	cpu_buffer->lock = (arch_spinlock_t)__ARCH_SPIN_LOCK_UNLOCKED;
	INIT_WORK(&cpu_buffer->update_pages_work, update_pages_handler);
	init_completion(&cpu_buffer->update_करोne);
	init_irq_work(&cpu_buffer->irq_work.work, rb_wake_up_रुकोers);
	init_रुकोqueue_head(&cpu_buffer->irq_work.रुकोers);
	init_रुकोqueue_head(&cpu_buffer->irq_work.full_रुकोers);

	bpage = kzalloc_node(ALIGN(माप(*bpage), cache_line_size()),
			    GFP_KERNEL, cpu_to_node(cpu));
	अगर (!bpage)
		जाओ fail_मुक्त_buffer;

	rb_check_bpage(cpu_buffer, bpage);

	cpu_buffer->पढ़ोer_page = bpage;
	page = alloc_pages_node(cpu_to_node(cpu), GFP_KERNEL, 0);
	अगर (!page)
		जाओ fail_मुक्त_पढ़ोer;
	bpage->page = page_address(page);
	rb_init_page(bpage->page);

	INIT_LIST_HEAD(&cpu_buffer->पढ़ोer_page->list);
	INIT_LIST_HEAD(&cpu_buffer->new_pages);

	ret = rb_allocate_pages(cpu_buffer, nr_pages);
	अगर (ret < 0)
		जाओ fail_मुक्त_पढ़ोer;

	cpu_buffer->head_page
		= list_entry(cpu_buffer->pages, काष्ठा buffer_page, list);
	cpu_buffer->tail_page = cpu_buffer->commit_page = cpu_buffer->head_page;

	rb_head_page_activate(cpu_buffer);

	वापस cpu_buffer;

 fail_मुक्त_पढ़ोer:
	मुक्त_buffer_page(cpu_buffer->पढ़ोer_page);

 fail_मुक्त_buffer:
	kमुक्त(cpu_buffer);
	वापस शून्य;
पूर्ण

अटल व्योम rb_मुक्त_cpu_buffer(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा list_head *head = cpu_buffer->pages;
	काष्ठा buffer_page *bpage, *पंचांगp;

	मुक्त_buffer_page(cpu_buffer->पढ़ोer_page);

	rb_head_page_deactivate(cpu_buffer);

	अगर (head) अणु
		list_क्रम_each_entry_safe(bpage, पंचांगp, head, list) अणु
			list_del_init(&bpage->list);
			मुक्त_buffer_page(bpage);
		पूर्ण
		bpage = list_entry(head, काष्ठा buffer_page, list);
		मुक्त_buffer_page(bpage);
	पूर्ण

	kमुक्त(cpu_buffer);
पूर्ण

/**
 * __ring_buffer_alloc - allocate a new ring_buffer
 * @size: the size in bytes per cpu that is needed.
 * @flags: attributes to set क्रम the ring buffer.
 * @key: ring buffer पढ़ोer_lock_key.
 *
 * Currently the only flag that is available is the RB_FL_OVERWRITE
 * flag. This flag means that the buffer will overग_लिखो old data
 * when the buffer wraps. If this flag is not set, the buffer will
 * drop data when the tail hits the head.
 */
काष्ठा trace_buffer *__ring_buffer_alloc(अचिन्हित दीर्घ size, अचिन्हित flags,
					काष्ठा lock_class_key *key)
अणु
	काष्ठा trace_buffer *buffer;
	दीर्घ nr_pages;
	पूर्णांक bsize;
	पूर्णांक cpu;
	पूर्णांक ret;

	/* keep it in its own cache line */
	buffer = kzalloc(ALIGN(माप(*buffer), cache_line_size()),
			 GFP_KERNEL);
	अगर (!buffer)
		वापस शून्य;

	अगर (!zalloc_cpumask_var(&buffer->cpumask, GFP_KERNEL))
		जाओ fail_मुक्त_buffer;

	nr_pages = DIV_ROUND_UP(size, BUF_PAGE_SIZE);
	buffer->flags = flags;
	buffer->घड़ी = trace_घड़ी_local;
	buffer->पढ़ोer_lock_key = key;

	init_irq_work(&buffer->irq_work.work, rb_wake_up_रुकोers);
	init_रुकोqueue_head(&buffer->irq_work.रुकोers);

	/* need at least two pages */
	अगर (nr_pages < 2)
		nr_pages = 2;

	buffer->cpus = nr_cpu_ids;

	bsize = माप(व्योम *) * nr_cpu_ids;
	buffer->buffers = kzalloc(ALIGN(bsize, cache_line_size()),
				  GFP_KERNEL);
	अगर (!buffer->buffers)
		जाओ fail_मुक्त_cpumask;

	cpu = raw_smp_processor_id();
	cpumask_set_cpu(cpu, buffer->cpumask);
	buffer->buffers[cpu] = rb_allocate_cpu_buffer(buffer, nr_pages, cpu);
	अगर (!buffer->buffers[cpu])
		जाओ fail_मुक्त_buffers;

	ret = cpuhp_state_add_instance(CPUHP_TRACE_RB_PREPARE, &buffer->node);
	अगर (ret < 0)
		जाओ fail_मुक्त_buffers;

	mutex_init(&buffer->mutex);

	वापस buffer;

 fail_मुक्त_buffers:
	क्रम_each_buffer_cpu(buffer, cpu) अणु
		अगर (buffer->buffers[cpu])
			rb_मुक्त_cpu_buffer(buffer->buffers[cpu]);
	पूर्ण
	kमुक्त(buffer->buffers);

 fail_मुक्त_cpumask:
	मुक्त_cpumask_var(buffer->cpumask);

 fail_मुक्त_buffer:
	kमुक्त(buffer);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(__ring_buffer_alloc);

/**
 * ring_buffer_मुक्त - मुक्त a ring buffer.
 * @buffer: the buffer to मुक्त.
 */
व्योम
ring_buffer_मुक्त(काष्ठा trace_buffer *buffer)
अणु
	पूर्णांक cpu;

	cpuhp_state_हटाओ_instance(CPUHP_TRACE_RB_PREPARE, &buffer->node);

	क्रम_each_buffer_cpu(buffer, cpu)
		rb_मुक्त_cpu_buffer(buffer->buffers[cpu]);

	kमुक्त(buffer->buffers);
	मुक्त_cpumask_var(buffer->cpumask);

	kमुक्त(buffer);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_मुक्त);

व्योम ring_buffer_set_घड़ी(काष्ठा trace_buffer *buffer,
			   u64 (*घड़ी)(व्योम))
अणु
	buffer->घड़ी = घड़ी;
पूर्ण

व्योम ring_buffer_set_समय_stamp_असल(काष्ठा trace_buffer *buffer, bool असल)
अणु
	buffer->समय_stamp_असल = असल;
पूर्ण

bool ring_buffer_समय_stamp_असल(काष्ठा trace_buffer *buffer)
अणु
	वापस buffer->समय_stamp_असल;
पूर्ण

अटल व्योम rb_reset_cpu(काष्ठा ring_buffer_per_cpu *cpu_buffer);

अटल अंतरभूत अचिन्हित दीर्घ rb_page_entries(काष्ठा buffer_page *bpage)
अणु
	वापस local_पढ़ो(&bpage->entries) & RB_WRITE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ rb_page_ग_लिखो(काष्ठा buffer_page *bpage)
अणु
	वापस local_पढ़ो(&bpage->ग_लिखो) & RB_WRITE_MASK;
पूर्ण

अटल पूर्णांक
rb_हटाओ_pages(काष्ठा ring_buffer_per_cpu *cpu_buffer, अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा list_head *tail_page, *to_हटाओ, *next_page;
	काष्ठा buffer_page *to_हटाओ_page, *पंचांगp_iter_page;
	काष्ठा buffer_page *last_page, *first_page;
	अचिन्हित दीर्घ nr_हटाओd;
	अचिन्हित दीर्घ head_bit;
	पूर्णांक page_entries;

	head_bit = 0;

	raw_spin_lock_irq(&cpu_buffer->पढ़ोer_lock);
	atomic_inc(&cpu_buffer->record_disabled);
	/*
	 * We करोn't race with the पढ़ोers since we have acquired the पढ़ोer
	 * lock. We also करोn't race with ग_लिखोrs after disabling recording.
	 * This makes it easy to figure out the first and the last page to be
	 * हटाओd from the list. We unlink all the pages in between including
	 * the first and last pages. This is करोne in a busy loop so that we
	 * lose the least number of traces.
	 * The pages are मुक्तd after we restart recording and unlock पढ़ोers.
	 */
	tail_page = &cpu_buffer->tail_page->list;

	/*
	 * tail page might be on पढ़ोer page, we हटाओ the next page
	 * from the ring buffer
	 */
	अगर (cpu_buffer->tail_page == cpu_buffer->पढ़ोer_page)
		tail_page = rb_list_head(tail_page->next);
	to_हटाओ = tail_page;

	/* start of pages to हटाओ */
	first_page = list_entry(rb_list_head(to_हटाओ->next),
				काष्ठा buffer_page, list);

	क्रम (nr_हटाओd = 0; nr_हटाओd < nr_pages; nr_हटाओd++) अणु
		to_हटाओ = rb_list_head(to_हटाओ)->next;
		head_bit |= (अचिन्हित दीर्घ)to_हटाओ & RB_PAGE_HEAD;
	पूर्ण

	next_page = rb_list_head(to_हटाओ)->next;

	/*
	 * Now we हटाओ all pages between tail_page and next_page.
	 * Make sure that we have head_bit value preserved क्रम the
	 * next page
	 */
	tail_page->next = (काष्ठा list_head *)((अचिन्हित दीर्घ)next_page |
						head_bit);
	next_page = rb_list_head(next_page);
	next_page->prev = tail_page;

	/* make sure pages poपूर्णांकs to a valid page in the ring buffer */
	cpu_buffer->pages = next_page;

	/* update head page */
	अगर (head_bit)
		cpu_buffer->head_page = list_entry(next_page,
						काष्ठा buffer_page, list);

	/*
	 * change पढ़ो poपूर्णांकer to make sure any पढ़ो iterators reset
	 * themselves
	 */
	cpu_buffer->पढ़ो = 0;

	/* pages are हटाओd, resume tracing and then मुक्त the pages */
	atomic_dec(&cpu_buffer->record_disabled);
	raw_spin_unlock_irq(&cpu_buffer->पढ़ोer_lock);

	RB_WARN_ON(cpu_buffer, list_empty(cpu_buffer->pages));

	/* last buffer page to हटाओ */
	last_page = list_entry(rb_list_head(to_हटाओ), काष्ठा buffer_page,
				list);
	पंचांगp_iter_page = first_page;

	करो अणु
		cond_resched();

		to_हटाओ_page = पंचांगp_iter_page;
		rb_inc_page(&पंचांगp_iter_page);

		/* update the counters */
		page_entries = rb_page_entries(to_हटाओ_page);
		अगर (page_entries) अणु
			/*
			 * If something was added to this page, it was full
			 * since it is not the tail page. So we deduct the
			 * bytes consumed in ring buffer from here.
			 * Increment overrun to account क्रम the lost events.
			 */
			local_add(page_entries, &cpu_buffer->overrun);
			local_sub(BUF_PAGE_SIZE, &cpu_buffer->entries_bytes);
		पूर्ण

		/*
		 * We have alपढ़ोy हटाओd references to this list item, just
		 * मुक्त up the buffer_page and its page
		 */
		मुक्त_buffer_page(to_हटाओ_page);
		nr_हटाओd--;

	पूर्ण जबतक (to_हटाओ_page != last_page);

	RB_WARN_ON(cpu_buffer, nr_हटाओd);

	वापस nr_हटाओd == 0;
पूर्ण

अटल पूर्णांक
rb_insert_pages(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा list_head *pages = &cpu_buffer->new_pages;
	पूर्णांक retries, success;

	raw_spin_lock_irq(&cpu_buffer->पढ़ोer_lock);
	/*
	 * We are holding the पढ़ोer lock, so the पढ़ोer page won't be swapped
	 * in the ring buffer. Now we are racing with the ग_लिखोr trying to
	 * move head page and the tail page.
	 * We are going to adapt the पढ़ोer page update process where:
	 * 1. We first splice the start and end of list of new pages between
	 *    the head page and its previous page.
	 * 2. We cmpxchg the prev_page->next to poपूर्णांक from head page to the
	 *    start of new pages list.
	 * 3. Finally, we update the head->prev to the end of new list.
	 *
	 * We will try this process 10 बार, to make sure that we करोn't keep
	 * spinning.
	 */
	retries = 10;
	success = 0;
	जबतक (retries--) अणु
		काष्ठा list_head *head_page, *prev_page, *r;
		काष्ठा list_head *last_page, *first_page;
		काष्ठा list_head *head_page_with_bit;

		head_page = &rb_set_head_page(cpu_buffer)->list;
		अगर (!head_page)
			अवरोध;
		prev_page = head_page->prev;

		first_page = pages->next;
		last_page  = pages->prev;

		head_page_with_bit = (काष्ठा list_head *)
				     ((अचिन्हित दीर्घ)head_page | RB_PAGE_HEAD);

		last_page->next = head_page_with_bit;
		first_page->prev = prev_page;

		r = cmpxchg(&prev_page->next, head_page_with_bit, first_page);

		अगर (r == head_page_with_bit) अणु
			/*
			 * yay, we replaced the page poपूर्णांकer to our new list,
			 * now, we just have to update to head page's prev
			 * poपूर्णांकer to poपूर्णांक to end of list
			 */
			head_page->prev = last_page;
			success = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (success)
		INIT_LIST_HEAD(pages);
	/*
	 * If we weren't successful in adding in new pages, warn and stop
	 * tracing
	 */
	RB_WARN_ON(cpu_buffer, !success);
	raw_spin_unlock_irq(&cpu_buffer->पढ़ोer_lock);

	/* मुक्त pages अगर they weren't inserted */
	अगर (!success) अणु
		काष्ठा buffer_page *bpage, *पंचांगp;
		list_क्रम_each_entry_safe(bpage, पंचांगp, &cpu_buffer->new_pages,
					 list) अणु
			list_del_init(&bpage->list);
			मुक्त_buffer_page(bpage);
		पूर्ण
	पूर्ण
	वापस success;
पूर्ण

अटल व्योम rb_update_pages(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	पूर्णांक success;

	अगर (cpu_buffer->nr_pages_to_update > 0)
		success = rb_insert_pages(cpu_buffer);
	अन्यथा
		success = rb_हटाओ_pages(cpu_buffer,
					-cpu_buffer->nr_pages_to_update);

	अगर (success)
		cpu_buffer->nr_pages += cpu_buffer->nr_pages_to_update;
पूर्ण

अटल व्योम update_pages_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = container_of(work,
			काष्ठा ring_buffer_per_cpu, update_pages_work);
	rb_update_pages(cpu_buffer);
	complete(&cpu_buffer->update_करोne);
पूर्ण

/**
 * ring_buffer_resize - resize the ring buffer
 * @buffer: the buffer to resize.
 * @size: the new size.
 * @cpu_id: the cpu buffer to resize
 *
 * Minimum size is 2 * BUF_PAGE_SIZE.
 *
 * Returns 0 on success and < 0 on failure.
 */
पूर्णांक ring_buffer_resize(काष्ठा trace_buffer *buffer, अचिन्हित दीर्घ size,
			पूर्णांक cpu_id)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ nr_pages;
	पूर्णांक cpu, err;

	/*
	 * Always succeed at resizing a non-existent buffer:
	 */
	अगर (!buffer)
		वापस 0;

	/* Make sure the requested buffer exists */
	अगर (cpu_id != RING_BUFFER_ALL_CPUS &&
	    !cpumask_test_cpu(cpu_id, buffer->cpumask))
		वापस 0;

	nr_pages = DIV_ROUND_UP(size, BUF_PAGE_SIZE);

	/* we need a minimum of two pages */
	अगर (nr_pages < 2)
		nr_pages = 2;

	/* prevent another thपढ़ो from changing buffer sizes */
	mutex_lock(&buffer->mutex);


	अगर (cpu_id == RING_BUFFER_ALL_CPUS) अणु
		/*
		 * Don't succeed अगर resizing is disabled, as a पढ़ोer might be
		 * manipulating the ring buffer and is expecting a sane state जबतक
		 * this is true.
		 */
		क्रम_each_buffer_cpu(buffer, cpu) अणु
			cpu_buffer = buffer->buffers[cpu];
			अगर (atomic_पढ़ो(&cpu_buffer->resize_disabled)) अणु
				err = -EBUSY;
				जाओ out_err_unlock;
			पूर्ण
		पूर्ण

		/* calculate the pages to update */
		क्रम_each_buffer_cpu(buffer, cpu) अणु
			cpu_buffer = buffer->buffers[cpu];

			cpu_buffer->nr_pages_to_update = nr_pages -
							cpu_buffer->nr_pages;
			/*
			 * nothing more to करो क्रम removing pages or no update
			 */
			अगर (cpu_buffer->nr_pages_to_update <= 0)
				जारी;
			/*
			 * to add pages, make sure all new pages can be
			 * allocated without receiving ENOMEM
			 */
			INIT_LIST_HEAD(&cpu_buffer->new_pages);
			अगर (__rb_allocate_pages(cpu_buffer, cpu_buffer->nr_pages_to_update,
						&cpu_buffer->new_pages)) अणु
				/* not enough memory क्रम new pages */
				err = -ENOMEM;
				जाओ out_err;
			पूर्ण
		पूर्ण

		get_online_cpus();
		/*
		 * Fire off all the required work handlers
		 * We can't schedule on offline CPUs, but it's not necessary
		 * since we can change their buffer sizes without any race.
		 */
		क्रम_each_buffer_cpu(buffer, cpu) अणु
			cpu_buffer = buffer->buffers[cpu];
			अगर (!cpu_buffer->nr_pages_to_update)
				जारी;

			/* Can't run something on an offline CPU. */
			अगर (!cpu_online(cpu)) अणु
				rb_update_pages(cpu_buffer);
				cpu_buffer->nr_pages_to_update = 0;
			पूर्ण अन्यथा अणु
				schedule_work_on(cpu,
						&cpu_buffer->update_pages_work);
			पूर्ण
		पूर्ण

		/* रुको क्रम all the updates to complete */
		क्रम_each_buffer_cpu(buffer, cpu) अणु
			cpu_buffer = buffer->buffers[cpu];
			अगर (!cpu_buffer->nr_pages_to_update)
				जारी;

			अगर (cpu_online(cpu))
				रुको_क्रम_completion(&cpu_buffer->update_करोne);
			cpu_buffer->nr_pages_to_update = 0;
		पूर्ण

		put_online_cpus();
	पूर्ण अन्यथा अणु
		cpu_buffer = buffer->buffers[cpu_id];

		अगर (nr_pages == cpu_buffer->nr_pages)
			जाओ out;

		/*
		 * Don't succeed अगर resizing is disabled, as a पढ़ोer might be
		 * manipulating the ring buffer and is expecting a sane state जबतक
		 * this is true.
		 */
		अगर (atomic_पढ़ो(&cpu_buffer->resize_disabled)) अणु
			err = -EBUSY;
			जाओ out_err_unlock;
		पूर्ण

		cpu_buffer->nr_pages_to_update = nr_pages -
						cpu_buffer->nr_pages;

		INIT_LIST_HEAD(&cpu_buffer->new_pages);
		अगर (cpu_buffer->nr_pages_to_update > 0 &&
			__rb_allocate_pages(cpu_buffer, cpu_buffer->nr_pages_to_update,
					    &cpu_buffer->new_pages)) अणु
			err = -ENOMEM;
			जाओ out_err;
		पूर्ण

		get_online_cpus();

		/* Can't run something on an offline CPU. */
		अगर (!cpu_online(cpu_id))
			rb_update_pages(cpu_buffer);
		अन्यथा अणु
			schedule_work_on(cpu_id,
					 &cpu_buffer->update_pages_work);
			रुको_क्रम_completion(&cpu_buffer->update_करोne);
		पूर्ण

		cpu_buffer->nr_pages_to_update = 0;
		put_online_cpus();
	पूर्ण

 out:
	/*
	 * The ring buffer resize can happen with the ring buffer
	 * enabled, so that the update disturbs the tracing as little
	 * as possible. But अगर the buffer is disabled, we करो not need
	 * to worry about that, and we can take the समय to verअगरy
	 * that the buffer is not corrupt.
	 */
	अगर (atomic_पढ़ो(&buffer->record_disabled)) अणु
		atomic_inc(&buffer->record_disabled);
		/*
		 * Even though the buffer was disabled, we must make sure
		 * that it is truly disabled beक्रमe calling rb_check_pages.
		 * There could have been a race between checking
		 * record_disable and incrementing it.
		 */
		synchronize_rcu();
		क्रम_each_buffer_cpu(buffer, cpu) अणु
			cpu_buffer = buffer->buffers[cpu];
			rb_check_pages(cpu_buffer);
		पूर्ण
		atomic_dec(&buffer->record_disabled);
	पूर्ण

	mutex_unlock(&buffer->mutex);
	वापस 0;

 out_err:
	क्रम_each_buffer_cpu(buffer, cpu) अणु
		काष्ठा buffer_page *bpage, *पंचांगp;

		cpu_buffer = buffer->buffers[cpu];
		cpu_buffer->nr_pages_to_update = 0;

		अगर (list_empty(&cpu_buffer->new_pages))
			जारी;

		list_क्रम_each_entry_safe(bpage, पंचांगp, &cpu_buffer->new_pages,
					list) अणु
			list_del_init(&bpage->list);
			मुक्त_buffer_page(bpage);
		पूर्ण
	पूर्ण
 out_err_unlock:
	mutex_unlock(&buffer->mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_resize);

व्योम ring_buffer_change_overग_लिखो(काष्ठा trace_buffer *buffer, पूर्णांक val)
अणु
	mutex_lock(&buffer->mutex);
	अगर (val)
		buffer->flags |= RB_FL_OVERWRITE;
	अन्यथा
		buffer->flags &= ~RB_FL_OVERWRITE;
	mutex_unlock(&buffer->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_change_overग_लिखो);

अटल __always_अंतरभूत व्योम *__rb_page_index(काष्ठा buffer_page *bpage, अचिन्हित index)
अणु
	वापस bpage->page->data + index;
पूर्ण

अटल __always_अंतरभूत काष्ठा ring_buffer_event *
rb_पढ़ोer_event(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	वापस __rb_page_index(cpu_buffer->पढ़ोer_page,
			       cpu_buffer->पढ़ोer_page->पढ़ो);
पूर्ण

अटल __always_अंतरभूत अचिन्हित rb_page_commit(काष्ठा buffer_page *bpage)
अणु
	वापस local_पढ़ो(&bpage->page->commit);
पूर्ण

अटल काष्ठा ring_buffer_event *
rb_iter_head_event(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा buffer_page *iter_head_page = iter->head_page;
	अचिन्हित दीर्घ commit;
	अचिन्हित length;

	अगर (iter->head != iter->next_event)
		वापस iter->event;

	/*
	 * When the ग_लिखोr goes across pages, it issues a cmpxchg which
	 * is a mb(), which will synchronize with the rmb here.
	 * (see rb_tail_page_update() and __rb_reserve_next())
	 */
	commit = rb_page_commit(iter_head_page);
	smp_rmb();
	event = __rb_page_index(iter_head_page, iter->head);
	length = rb_event_length(event);

	/*
	 * READ_ONCE() करोesn't work on functions and we don't want the
	 * compiler करोing any crazy optimizations with length.
	 */
	barrier();

	अगर ((iter->head + length) > commit || length > BUF_MAX_DATA_SIZE)
		/* Writer corrupted the पढ़ो? */
		जाओ reset;

	स_नकल(iter->event, event, length);
	/*
	 * If the page stamp is still the same after this rmb() then the
	 * event was safely copied without the ग_लिखोr entering the page.
	 */
	smp_rmb();

	/* Make sure the page didn't change since we पढ़ो this */
	अगर (iter->page_stamp != iter_head_page->page->समय_stamp ||
	    commit > rb_page_commit(iter_head_page))
		जाओ reset;

	iter->next_event = iter->head + length;
	वापस iter->event;
 reset:
	/* Reset to the beginning */
	iter->page_stamp = iter->पढ़ो_stamp = iter->head_page->page->समय_stamp;
	iter->head = 0;
	iter->next_event = 0;
	iter->missed_events = 1;
	वापस शून्य;
पूर्ण

/* Size is determined by what has been committed */
अटल __always_अंतरभूत अचिन्हित rb_page_size(काष्ठा buffer_page *bpage)
अणु
	वापस rb_page_commit(bpage);
पूर्ण

अटल __always_अंतरभूत अचिन्हित
rb_commit_index(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	वापस rb_page_commit(cpu_buffer->commit_page);
पूर्ण

अटल __always_अंतरभूत अचिन्हित
rb_event_index(काष्ठा ring_buffer_event *event)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)event;

	वापस (addr & ~PAGE_MASK) - BUF_PAGE_HDR_SIZE;
पूर्ण

अटल व्योम rb_inc_iter(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = iter->cpu_buffer;

	/*
	 * The iterator could be on the पढ़ोer page (it starts there).
	 * But the head could have moved, since the पढ़ोer was
	 * found. Check क्रम this हाल and assign the iterator
	 * to the head page instead of next.
	 */
	अगर (iter->head_page == cpu_buffer->पढ़ोer_page)
		iter->head_page = rb_set_head_page(cpu_buffer);
	अन्यथा
		rb_inc_page(&iter->head_page);

	iter->page_stamp = iter->पढ़ो_stamp = iter->head_page->page->समय_stamp;
	iter->head = 0;
	iter->next_event = 0;
पूर्ण

/*
 * rb_handle_head_page - ग_लिखोr hit the head page
 *
 * Returns: +1 to retry page
 *           0 to जारी
 *          -1 on error
 */
अटल पूर्णांक
rb_handle_head_page(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		    काष्ठा buffer_page *tail_page,
		    काष्ठा buffer_page *next_page)
अणु
	काष्ठा buffer_page *new_head;
	पूर्णांक entries;
	पूर्णांक type;
	पूर्णांक ret;

	entries = rb_page_entries(next_page);

	/*
	 * The hard part is here. We need to move the head
	 * क्रमward, and protect against both पढ़ोers on
	 * other CPUs and ग_लिखोrs coming in via पूर्णांकerrupts.
	 */
	type = rb_head_page_set_update(cpu_buffer, next_page, tail_page,
				       RB_PAGE_HEAD);

	/*
	 * type can be one of four:
	 *  NORMAL - an पूर्णांकerrupt alपढ़ोy moved it क्रम us
	 *  HEAD   - we are the first to get here.
	 *  UPDATE - we are the पूर्णांकerrupt पूर्णांकerrupting
	 *           a current move.
	 *  MOVED  - a पढ़ोer on another CPU moved the next
	 *           poपूर्णांकer to its पढ़ोer page. Give up
	 *           and try again.
	 */

	चयन (type) अणु
	हाल RB_PAGE_HEAD:
		/*
		 * We changed the head to UPDATE, thus
		 * it is our responsibility to update
		 * the counters.
		 */
		local_add(entries, &cpu_buffer->overrun);
		local_sub(BUF_PAGE_SIZE, &cpu_buffer->entries_bytes);

		/*
		 * The entries will be zeroed out when we move the
		 * tail page.
		 */

		/* still more to करो */
		अवरोध;

	हाल RB_PAGE_UPDATE:
		/*
		 * This is an पूर्णांकerrupt that पूर्णांकerrupt the
		 * previous update. Still more to करो.
		 */
		अवरोध;
	हाल RB_PAGE_NORMAL:
		/*
		 * An पूर्णांकerrupt came in beक्रमe the update
		 * and processed this क्रम us.
		 * Nothing left to करो.
		 */
		वापस 1;
	हाल RB_PAGE_MOVED:
		/*
		 * The पढ़ोer is on another CPU and just did
		 * a swap with our next_page.
		 * Try again.
		 */
		वापस 1;
	शेष:
		RB_WARN_ON(cpu_buffer, 1); /* WTF??? */
		वापस -1;
	पूर्ण

	/*
	 * Now that we are here, the old head poपूर्णांकer is
	 * set to UPDATE. This will keep the पढ़ोer from
	 * swapping the head page with the पढ़ोer page.
	 * The पढ़ोer (on another CPU) will spin till
	 * we are finished.
	 *
	 * We just need to protect against पूर्णांकerrupts
	 * करोing the job. We will set the next poपूर्णांकer
	 * to HEAD. After that, we set the old poपूर्णांकer
	 * to NORMAL, but only अगर it was HEAD beक्रमe.
	 * otherwise we are an पूर्णांकerrupt, and only
	 * want the outer most commit to reset it.
	 */
	new_head = next_page;
	rb_inc_page(&new_head);

	ret = rb_head_page_set_head(cpu_buffer, new_head, next_page,
				    RB_PAGE_NORMAL);

	/*
	 * Valid वापसs are:
	 *  HEAD   - an पूर्णांकerrupt came in and alपढ़ोy set it.
	 *  NORMAL - One of two things:
	 *            1) We really set it.
	 *            2) A bunch of पूर्णांकerrupts came in and moved
	 *               the page क्रमward again.
	 */
	चयन (ret) अणु
	हाल RB_PAGE_HEAD:
	हाल RB_PAGE_NORMAL:
		/* OK */
		अवरोध;
	शेष:
		RB_WARN_ON(cpu_buffer, 1);
		वापस -1;
	पूर्ण

	/*
	 * It is possible that an पूर्णांकerrupt came in,
	 * set the head up, then more पूर्णांकerrupts came in
	 * and moved it again. When we get back here,
	 * the page would have been set to NORMAL but we
	 * just set it back to HEAD.
	 *
	 * How करो you detect this? Well, अगर that happened
	 * the tail page would have moved.
	 */
	अगर (ret == RB_PAGE_NORMAL) अणु
		काष्ठा buffer_page *buffer_tail_page;

		buffer_tail_page = READ_ONCE(cpu_buffer->tail_page);
		/*
		 * If the tail had moved passed next, then we need
		 * to reset the poपूर्णांकer.
		 */
		अगर (buffer_tail_page != tail_page &&
		    buffer_tail_page != next_page)
			rb_head_page_set_normal(cpu_buffer, new_head,
						next_page,
						RB_PAGE_HEAD);
	पूर्ण

	/*
	 * If this was the outer most commit (the one that
	 * changed the original poपूर्णांकer from HEAD to UPDATE),
	 * then it is up to us to reset it to NORMAL.
	 */
	अगर (type == RB_PAGE_HEAD) अणु
		ret = rb_head_page_set_normal(cpu_buffer, next_page,
					      tail_page,
					      RB_PAGE_UPDATE);
		अगर (RB_WARN_ON(cpu_buffer,
			       ret != RB_PAGE_UPDATE))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
rb_reset_tail(काष्ठा ring_buffer_per_cpu *cpu_buffer,
	      अचिन्हित दीर्घ tail, काष्ठा rb_event_info *info)
अणु
	काष्ठा buffer_page *tail_page = info->tail_page;
	काष्ठा ring_buffer_event *event;
	अचिन्हित दीर्घ length = info->length;

	/*
	 * Only the event that crossed the page boundary
	 * must fill the old tail_page with padding.
	 */
	अगर (tail >= BUF_PAGE_SIZE) अणु
		/*
		 * If the page was filled, then we still need
		 * to update the real_end. Reset it to zero
		 * and the पढ़ोer will ignore it.
		 */
		अगर (tail == BUF_PAGE_SIZE)
			tail_page->real_end = 0;

		local_sub(length, &tail_page->ग_लिखो);
		वापस;
	पूर्ण

	event = __rb_page_index(tail_page, tail);

	/* account क्रम padding bytes */
	local_add(BUF_PAGE_SIZE - tail, &cpu_buffer->entries_bytes);

	/*
	 * Save the original length to the meta data.
	 * This will be used by the पढ़ोer to add lost event
	 * counter.
	 */
	tail_page->real_end = tail;

	/*
	 * If this event is bigger than the minimum size, then
	 * we need to be careful that we करोn't subtract the
	 * ग_लिखो counter enough to allow another ग_लिखोr to slip
	 * in on this page.
	 * We put in a discarded commit instead, to make sure
	 * that this space is not used again.
	 *
	 * If we are less than the minimum size, we करोn't need to
	 * worry about it.
	 */
	अगर (tail > (BUF_PAGE_SIZE - RB_EVNT_MIN_SIZE)) अणु
		/* No room क्रम any events */

		/* Mark the rest of the page with padding */
		rb_event_set_padding(event);

		/* Set the ग_लिखो back to the previous setting */
		local_sub(length, &tail_page->ग_लिखो);
		वापस;
	पूर्ण

	/* Put in a discarded event */
	event->array[0] = (BUF_PAGE_SIZE - tail) - RB_EVNT_HDR_SIZE;
	event->type_len = RINGBUF_TYPE_PADDING;
	/* समय delta must be non zero */
	event->समय_delta = 1;

	/* Set ग_लिखो to end of buffer */
	length = (tail + length) - BUF_PAGE_SIZE;
	local_sub(length, &tail_page->ग_लिखो);
पूर्ण

अटल अंतरभूत व्योम rb_end_commit(काष्ठा ring_buffer_per_cpu *cpu_buffer);

/*
 * This is the slow path, क्रमce gcc not to अंतरभूत it.
 */
अटल noअंतरभूत काष्ठा ring_buffer_event *
rb_move_tail(काष्ठा ring_buffer_per_cpu *cpu_buffer,
	     अचिन्हित दीर्घ tail, काष्ठा rb_event_info *info)
अणु
	काष्ठा buffer_page *tail_page = info->tail_page;
	काष्ठा buffer_page *commit_page = cpu_buffer->commit_page;
	काष्ठा trace_buffer *buffer = cpu_buffer->buffer;
	काष्ठा buffer_page *next_page;
	पूर्णांक ret;

	next_page = tail_page;

	rb_inc_page(&next_page);

	/*
	 * If क्रम some reason, we had an पूर्णांकerrupt storm that made
	 * it all the way around the buffer, bail, and warn
	 * about it.
	 */
	अगर (unlikely(next_page == commit_page)) अणु
		local_inc(&cpu_buffer->commit_overrun);
		जाओ out_reset;
	पूर्ण

	/*
	 * This is where the fun begins!
	 *
	 * We are fighting against races between a पढ़ोer that
	 * could be on another CPU trying to swap its पढ़ोer
	 * page with the buffer head.
	 *
	 * We are also fighting against पूर्णांकerrupts coming in and
	 * moving the head or tail on us as well.
	 *
	 * If the next page is the head page then we have filled
	 * the buffer, unless the commit page is still on the
	 * पढ़ोer page.
	 */
	अगर (rb_is_head_page(next_page, &tail_page->list)) अणु

		/*
		 * If the commit is not on the पढ़ोer page, then
		 * move the header page.
		 */
		अगर (!rb_is_पढ़ोer_page(cpu_buffer->commit_page)) अणु
			/*
			 * If we are not in overग_लिखो mode,
			 * this is easy, just stop here.
			 */
			अगर (!(buffer->flags & RB_FL_OVERWRITE)) अणु
				local_inc(&cpu_buffer->dropped_events);
				जाओ out_reset;
			पूर्ण

			ret = rb_handle_head_page(cpu_buffer,
						  tail_page,
						  next_page);
			अगर (ret < 0)
				जाओ out_reset;
			अगर (ret)
				जाओ out_again;
		पूर्ण अन्यथा अणु
			/*
			 * We need to be careful here too. The
			 * commit page could still be on the पढ़ोer
			 * page. We could have a small buffer, and
			 * have filled up the buffer with events
			 * from पूर्णांकerrupts and such, and wrapped.
			 *
			 * Note, अगर the tail page is also on the
			 * पढ़ोer_page, we let it move out.
			 */
			अगर (unlikely((cpu_buffer->commit_page !=
				      cpu_buffer->tail_page) &&
				     (cpu_buffer->commit_page ==
				      cpu_buffer->पढ़ोer_page))) अणु
				local_inc(&cpu_buffer->commit_overrun);
				जाओ out_reset;
			पूर्ण
		पूर्ण
	पूर्ण

	rb_tail_page_update(cpu_buffer, tail_page, next_page);

 out_again:

	rb_reset_tail(cpu_buffer, tail, info);

	/* Commit what we have क्रम now. */
	rb_end_commit(cpu_buffer);
	/* rb_end_commit() decs committing */
	local_inc(&cpu_buffer->committing);

	/* fail and let the caller try again */
	वापस ERR_PTR(-EAGAIN);

 out_reset:
	/* reset ग_लिखो */
	rb_reset_tail(cpu_buffer, tail, info);

	वापस शून्य;
पूर्ण

/* Slow path */
अटल काष्ठा ring_buffer_event *
rb_add_समय_stamp(काष्ठा ring_buffer_event *event, u64 delta, bool असल)
अणु
	अगर (असल)
		event->type_len = RINGBUF_TYPE_TIME_STAMP;
	अन्यथा
		event->type_len = RINGBUF_TYPE_TIME_EXTEND;

	/* Not the first event on the page, or not delta? */
	अगर (असल || rb_event_index(event)) अणु
		event->समय_delta = delta & TS_MASK;
		event->array[0] = delta >> TS_SHIFT;
	पूर्ण अन्यथा अणु
		/* nope, just zero it */
		event->समय_delta = 0;
		event->array[0] = 0;
	पूर्ण

	वापस skip_समय_extend(event);
पूर्ण

#अगर_अघोषित CONFIG_HAVE_UNSTABLE_SCHED_CLOCK
अटल अंतरभूत bool sched_घड़ी_stable(व्योम)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल व्योम
rb_check_बारtamp(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		   काष्ठा rb_event_info *info)
अणु
	u64 ग_लिखो_stamp;

	WARN_ONCE(1, "Delta way too big! %llu ts=%llu before=%llu after=%llu write stamp=%llu\n%s",
		  (अचिन्हित दीर्घ दीर्घ)info->delta,
		  (अचिन्हित दीर्घ दीर्घ)info->ts,
		  (अचिन्हित दीर्घ दीर्घ)info->beक्रमe,
		  (अचिन्हित दीर्घ दीर्घ)info->after,
		  (अचिन्हित दीर्घ दीर्घ)(rb_समय_पढ़ो(&cpu_buffer->ग_लिखो_stamp, &ग_लिखो_stamp) ? ग_लिखो_stamp : 0),
		  sched_घड़ी_stable() ? "" :
		  "If you just came from a suspend/resume,\n"
		  "please switch to the trace global clock:\n"
		  "  echo global > /sys/kernel/debug/tracing/trace_clock\n"
		  "or add trace_clock=global to the kernel command line\n");
पूर्ण

अटल व्योम rb_add_बारtamp(काष्ठा ring_buffer_per_cpu *cpu_buffer,
				      काष्ठा ring_buffer_event **event,
				      काष्ठा rb_event_info *info,
				      u64 *delta,
				      अचिन्हित पूर्णांक *length)
अणु
	bool असल = info->add_बारtamp &
		(RB_ADD_STAMP_FORCE | RB_ADD_STAMP_ABSOLUTE);

	अगर (unlikely(info->delta > (1ULL << 59))) अणु
		/* did the घड़ी go backwards */
		अगर (info->beक्रमe == info->after && info->beक्रमe > info->ts) अणु
			/* not पूर्णांकerrupted */
			अटल पूर्णांक once;

			/*
			 * This is possible with a recalibrating of the TSC.
			 * Do not produce a call stack, but just report it.
			 */
			अगर (!once) अणु
				once++;
				pr_warn("Ring buffer clock went backwards: %llu -> %llu\n",
					info->beक्रमe, info->ts);
			पूर्ण
		पूर्ण अन्यथा
			rb_check_बारtamp(cpu_buffer, info);
		अगर (!असल)
			info->delta = 0;
	पूर्ण
	*event = rb_add_समय_stamp(*event, info->delta, असल);
	*length -= RB_LEN_TIME_EXTEND;
	*delta = 0;
पूर्ण

/**
 * rb_update_event - update event type and data
 * @cpu_buffer: The per cpu buffer of the @event
 * @event: the event to update
 * @info: The info to update the @event with (contains length and delta)
 *
 * Update the type and data fields of the @event. The length
 * is the actual size that is written to the ring buffer,
 * and with this, we can determine what to place पूर्णांकo the
 * data field.
 */
अटल व्योम
rb_update_event(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		काष्ठा ring_buffer_event *event,
		काष्ठा rb_event_info *info)
अणु
	अचिन्हित length = info->length;
	u64 delta = info->delta;
	अचिन्हित पूर्णांक nest = local_पढ़ो(&cpu_buffer->committing) - 1;

	अगर (!WARN_ON_ONCE(nest >= MAX_NEST))
		cpu_buffer->event_stamp[nest] = info->ts;

	/*
	 * If we need to add a बारtamp, then we
	 * add it to the start of the reserved space.
	 */
	अगर (unlikely(info->add_बारtamp))
		rb_add_बारtamp(cpu_buffer, &event, info, &delta, &length);

	event->समय_delta = delta;
	length -= RB_EVNT_HDR_SIZE;
	अगर (length > RB_MAX_SMALL_DATA || RB_FORCE_8BYTE_ALIGNMENT) अणु
		event->type_len = 0;
		event->array[0] = length;
	पूर्ण अन्यथा
		event->type_len = DIV_ROUND_UP(length, RB_ALIGNMENT);
पूर्ण

अटल अचिन्हित rb_calculate_event_length(अचिन्हित length)
अणु
	काष्ठा ring_buffer_event event; /* Used only क्रम माप array */

	/* zero length can cause confusions */
	अगर (!length)
		length++;

	अगर (length > RB_MAX_SMALL_DATA || RB_FORCE_8BYTE_ALIGNMENT)
		length += माप(event.array[0]);

	length += RB_EVNT_HDR_SIZE;
	length = ALIGN(length, RB_ARCH_ALIGNMENT);

	/*
	 * In हाल the समय delta is larger than the 27 bits क्रम it
	 * in the header, we need to add a बारtamp. If another
	 * event comes in when trying to discard this one to increase
	 * the length, then the बारtamp will be added in the allocated
	 * space of this event. If length is bigger than the size needed
	 * क्रम the TIME_EXTEND, then padding has to be used. The events
	 * length must be either RB_LEN_TIME_EXTEND, or greater than or equal
	 * to RB_LEN_TIME_EXTEND + 8, as 8 is the minimum size क्रम padding.
	 * As length is a multiple of 4, we only need to worry अगर it
	 * is 12 (RB_LEN_TIME_EXTEND + 4).
	 */
	अगर (length == RB_LEN_TIME_EXTEND + RB_ALIGNMENT)
		length += RB_ALIGNMENT;

	वापस length;
पूर्ण

अटल u64 rb_समय_delta(काष्ठा ring_buffer_event *event)
अणु
	चयन (event->type_len) अणु
	हाल RINGBUF_TYPE_PADDING:
		वापस 0;

	हाल RINGBUF_TYPE_TIME_EXTEND:
		वापस rb_event_समय_stamp(event);

	हाल RINGBUF_TYPE_TIME_STAMP:
		वापस 0;

	हाल RINGBUF_TYPE_DATA:
		वापस event->समय_delta;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
rb_try_to_discard(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		  काष्ठा ring_buffer_event *event)
अणु
	अचिन्हित दीर्घ new_index, old_index;
	काष्ठा buffer_page *bpage;
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ addr;
	u64 ग_लिखो_stamp;
	u64 delta;

	new_index = rb_event_index(event);
	old_index = new_index + rb_event_ts_length(event);
	addr = (अचिन्हित दीर्घ)event;
	addr &= PAGE_MASK;

	bpage = READ_ONCE(cpu_buffer->tail_page);

	delta = rb_समय_delta(event);

	अगर (!rb_समय_पढ़ो(&cpu_buffer->ग_लिखो_stamp, &ग_लिखो_stamp))
		वापस 0;

	/* Make sure the ग_लिखो stamp is पढ़ो beक्रमe testing the location */
	barrier();

	अगर (bpage->page == (व्योम *)addr && rb_page_ग_लिखो(bpage) == old_index) अणु
		अचिन्हित दीर्घ ग_लिखो_mask =
			local_पढ़ो(&bpage->ग_लिखो) & ~RB_WRITE_MASK;
		अचिन्हित दीर्घ event_length = rb_event_length(event);

		/* Something came in, can't discard */
		अगर (!rb_समय_cmpxchg(&cpu_buffer->ग_लिखो_stamp,
				       ग_लिखो_stamp, ग_लिखो_stamp - delta))
			वापस 0;

		/*
		 * It's possible that the event समय delta is zero
		 * (has the same समय stamp as the previous event)
		 * in which हाल ग_लिखो_stamp and beक्रमe_stamp could
		 * be the same. In such a हाल, क्रमce beक्रमe_stamp
		 * to be dअगरferent than ग_लिखो_stamp. It करोesn't
		 * matter what it is, as दीर्घ as its dअगरferent.
		 */
		अगर (!delta)
			rb_समय_set(&cpu_buffer->beक्रमe_stamp, 0);

		/*
		 * If an event were to come in now, it would see that the
		 * ग_लिखो_stamp and the beक्रमe_stamp are dअगरferent, and assume
		 * that this event just added itself beक्रमe updating
		 * the ग_लिखो stamp. The पूर्णांकerrupting event will fix the
		 * ग_लिखो stamp क्रम us, and use the beक्रमe stamp as its delta.
		 */

		/*
		 * This is on the tail page. It is possible that
		 * a ग_लिखो could come in and move the tail page
		 * and ग_लिखो to the next page. That is fine
		 * because we just लघुen what is on this page.
		 */
		old_index += ग_लिखो_mask;
		new_index += ग_लिखो_mask;
		index = local_cmpxchg(&bpage->ग_लिखो, old_index, new_index);
		अगर (index == old_index) अणु
			/* update counters */
			local_sub(event_length, &cpu_buffer->entries_bytes);
			वापस 1;
		पूर्ण
	पूर्ण

	/* could not discard */
	वापस 0;
पूर्ण

अटल व्योम rb_start_commit(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	local_inc(&cpu_buffer->committing);
	local_inc(&cpu_buffer->commits);
पूर्ण

अटल __always_अंतरभूत व्योम
rb_set_commit_to_ग_लिखो(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	अचिन्हित दीर्घ max_count;

	/*
	 * We only race with पूर्णांकerrupts and NMIs on this CPU.
	 * If we own the commit event, then we can commit
	 * all others that पूर्णांकerrupted us, since the पूर्णांकerruptions
	 * are in stack क्रमmat (they finish beक्रमe they come
	 * back to us). This allows us to करो a simple loop to
	 * assign the commit to the tail.
	 */
 again:
	max_count = cpu_buffer->nr_pages * 100;

	जबतक (cpu_buffer->commit_page != READ_ONCE(cpu_buffer->tail_page)) अणु
		अगर (RB_WARN_ON(cpu_buffer, !(--max_count)))
			वापस;
		अगर (RB_WARN_ON(cpu_buffer,
			       rb_is_पढ़ोer_page(cpu_buffer->tail_page)))
			वापस;
		local_set(&cpu_buffer->commit_page->page->commit,
			  rb_page_ग_लिखो(cpu_buffer->commit_page));
		rb_inc_page(&cpu_buffer->commit_page);
		/* add barrier to keep gcc from optimizing too much */
		barrier();
	पूर्ण
	जबतक (rb_commit_index(cpu_buffer) !=
	       rb_page_ग_लिखो(cpu_buffer->commit_page)) अणु

		local_set(&cpu_buffer->commit_page->page->commit,
			  rb_page_ग_लिखो(cpu_buffer->commit_page));
		RB_WARN_ON(cpu_buffer,
			   local_पढ़ो(&cpu_buffer->commit_page->page->commit) &
			   ~RB_WRITE_MASK);
		barrier();
	पूर्ण

	/* again, keep gcc from optimizing */
	barrier();

	/*
	 * If an पूर्णांकerrupt came in just after the first जबतक loop
	 * and pushed the tail page क्रमward, we will be left with
	 * a dangling commit that will never go क्रमward.
	 */
	अगर (unlikely(cpu_buffer->commit_page != READ_ONCE(cpu_buffer->tail_page)))
		जाओ again;
पूर्ण

अटल __always_अंतरभूत व्योम rb_end_commit(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	अचिन्हित दीर्घ commits;

	अगर (RB_WARN_ON(cpu_buffer,
		       !local_पढ़ो(&cpu_buffer->committing)))
		वापस;

 again:
	commits = local_पढ़ो(&cpu_buffer->commits);
	/* synchronize with पूर्णांकerrupts */
	barrier();
	अगर (local_पढ़ो(&cpu_buffer->committing) == 1)
		rb_set_commit_to_ग_लिखो(cpu_buffer);

	local_dec(&cpu_buffer->committing);

	/* synchronize with पूर्णांकerrupts */
	barrier();

	/*
	 * Need to account क्रम पूर्णांकerrupts coming in between the
	 * updating of the commit page and the clearing of the
	 * committing counter.
	 */
	अगर (unlikely(local_पढ़ो(&cpu_buffer->commits) != commits) &&
	    !local_पढ़ो(&cpu_buffer->committing)) अणु
		local_inc(&cpu_buffer->committing);
		जाओ again;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rb_event_discard(काष्ठा ring_buffer_event *event)
अणु
	अगर (extended_समय(event))
		event = skip_समय_extend(event);

	/* array[0] holds the actual length क्रम the discarded event */
	event->array[0] = rb_event_data_length(event) - RB_EVNT_HDR_SIZE;
	event->type_len = RINGBUF_TYPE_PADDING;
	/* समय delta must be non zero */
	अगर (!event->समय_delta)
		event->समय_delta = 1;
पूर्ण

अटल व्योम rb_commit(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		      काष्ठा ring_buffer_event *event)
अणु
	local_inc(&cpu_buffer->entries);
	rb_end_commit(cpu_buffer);
पूर्ण

अटल __always_अंतरभूत व्योम
rb_wakeups(काष्ठा trace_buffer *buffer, काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	माप_प्रकार nr_pages;
	माप_प्रकार dirty;
	माप_प्रकार full;

	अगर (buffer->irq_work.रुकोers_pending) अणु
		buffer->irq_work.रुकोers_pending = false;
		/* irq_work_queue() supplies it's own memory barriers */
		irq_work_queue(&buffer->irq_work.work);
	पूर्ण

	अगर (cpu_buffer->irq_work.रुकोers_pending) अणु
		cpu_buffer->irq_work.रुकोers_pending = false;
		/* irq_work_queue() supplies it's own memory barriers */
		irq_work_queue(&cpu_buffer->irq_work.work);
	पूर्ण

	अगर (cpu_buffer->last_pages_touch == local_पढ़ो(&cpu_buffer->pages_touched))
		वापस;

	अगर (cpu_buffer->पढ़ोer_page == cpu_buffer->commit_page)
		वापस;

	अगर (!cpu_buffer->irq_work.full_रुकोers_pending)
		वापस;

	cpu_buffer->last_pages_touch = local_पढ़ो(&cpu_buffer->pages_touched);

	full = cpu_buffer->लघुest_full;
	nr_pages = cpu_buffer->nr_pages;
	dirty = ring_buffer_nr_dirty_pages(buffer, cpu_buffer->cpu);
	अगर (full && nr_pages && (dirty * 100) <= full * nr_pages)
		वापस;

	cpu_buffer->irq_work.wakeup_full = true;
	cpu_buffer->irq_work.full_रुकोers_pending = false;
	/* irq_work_queue() supplies it's own memory barriers */
	irq_work_queue(&cpu_buffer->irq_work.work);
पूर्ण

#अगर_घोषित CONFIG_RING_BUFFER_RECORD_RECURSION
# define करो_ring_buffer_record_recursion()	\
	करो_ftrace_record_recursion(_THIS_IP_, _RET_IP_)
#अन्यथा
# define करो_ring_buffer_record_recursion() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * The lock and unlock are करोne within a preempt disable section.
 * The current_context per_cpu variable can only be modअगरied
 * by the current task between lock and unlock. But it can
 * be modअगरied more than once via an पूर्णांकerrupt. To pass this
 * inक्रमmation from the lock to the unlock without having to
 * access the 'in_interrupt()' functions again (which करो show
 * a bit of overhead in something as critical as function tracing,
 * we use a biपंचांगask trick.
 *
 *  bit 1 =  NMI context
 *  bit 2 =  IRQ context
 *  bit 3 =  SoftIRQ context
 *  bit 4 =  normal context.
 *
 * This works because this is the order of contexts that can
 * preempt other contexts. A SoftIRQ never preempts an IRQ
 * context.
 *
 * When the context is determined, the corresponding bit is
 * checked and set (अगर it was set, then a recursion of that context
 * happened).
 *
 * On unlock, we need to clear this bit. To करो so, just subtract
 * 1 from the current_context and AND it to itself.
 *
 * (binary)
 *  101 - 1 = 100
 *  101 & 100 = 100 (clearing bit zero)
 *
 *  1010 - 1 = 1001
 *  1010 & 1001 = 1000 (clearing bit 1)
 *
 * The least signअगरicant bit can be cleared this way, and it
 * just so happens that it is the same bit corresponding to
 * the current context.
 *
 * Now the TRANSITION bit अवरोधs the above slightly. The TRANSITION bit
 * is set when a recursion is detected at the current context, and अगर
 * the TRANSITION bit is alपढ़ोy set, it will fail the recursion.
 * This is needed because there's a lag between the changing of
 * पूर्णांकerrupt context and updating the preempt count. In this हाल,
 * a false positive will be found. To handle this, one extra recursion
 * is allowed, and this is करोne by the TRANSITION bit. If the TRANSITION
 * bit is alपढ़ोy set, then it is considered a recursion and the function
 * ends. Otherwise, the TRANSITION bit is set, and that bit is वापसed.
 *
 * On the trace_recursive_unlock(), the TRANSITION bit will be the first
 * to be cleared. Even अगर it wasn't the context that set it. That is,
 * अगर an पूर्णांकerrupt comes in जबतक NORMAL bit is set and the ring buffer
 * is called beक्रमe preempt_count() is updated, since the check will
 * be on the NORMAL bit, the TRANSITION bit will then be set. If an
 * NMI then comes in, it will set the NMI bit, but when the NMI code
 * करोes the trace_recursive_unlock() it will clear the TRANSITION bit
 * and leave the NMI bit set. But this is fine, because the पूर्णांकerrupt
 * code that set the TRANSITION bit will then clear the NMI bit when it
 * calls trace_recursive_unlock(). If another NMI comes in, it will
 * set the TRANSITION bit and जारी.
 *
 * Note: The TRANSITION bit only handles a single transition between context.
 */

अटल __always_अंतरभूत पूर्णांक
trace_recursive_lock(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	अचिन्हित पूर्णांक val = cpu_buffer->current_context;
	अचिन्हित दीर्घ pc = preempt_count();
	पूर्णांक bit;

	अगर (!(pc & (NMI_MASK | HARसूचीQ_MASK | SOFTIRQ_OFFSET)))
		bit = RB_CTX_NORMAL;
	अन्यथा
		bit = pc & NMI_MASK ? RB_CTX_NMI :
			pc & HARसूचीQ_MASK ? RB_CTX_IRQ : RB_CTX_SOFTIRQ;

	अगर (unlikely(val & (1 << (bit + cpu_buffer->nest)))) अणु
		/*
		 * It is possible that this was called by transitioning
		 * between पूर्णांकerrupt context, and preempt_count() has not
		 * been updated yet. In this हाल, use the TRANSITION bit.
		 */
		bit = RB_CTX_TRANSITION;
		अगर (val & (1 << (bit + cpu_buffer->nest))) अणु
			करो_ring_buffer_record_recursion();
			वापस 1;
		पूर्ण
	पूर्ण

	val |= (1 << (bit + cpu_buffer->nest));
	cpu_buffer->current_context = val;

	वापस 0;
पूर्ण

अटल __always_अंतरभूत व्योम
trace_recursive_unlock(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	cpu_buffer->current_context &=
		cpu_buffer->current_context - (1 << cpu_buffer->nest);
पूर्ण

/* The recursive locking above uses 5 bits */
#घोषणा NESTED_BITS 5

/**
 * ring_buffer_nest_start - Allow to trace जबतक nested
 * @buffer: The ring buffer to modअगरy
 *
 * The ring buffer has a safety mechanism to prevent recursion.
 * But there may be a हाल where a trace needs to be करोne जबतक
 * tracing something अन्यथा. In this हाल, calling this function
 * will allow this function to nest within a currently active
 * ring_buffer_lock_reserve().
 *
 * Call this function beक्रमe calling another ring_buffer_lock_reserve() and
 * call ring_buffer_nest_end() after the nested ring_buffer_unlock_commit().
 */
व्योम ring_buffer_nest_start(काष्ठा trace_buffer *buffer)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	पूर्णांक cpu;

	/* Enabled by ring_buffer_nest_end() */
	preempt_disable_notrace();
	cpu = raw_smp_processor_id();
	cpu_buffer = buffer->buffers[cpu];
	/* This is the shअगरt value क्रम the above recursive locking */
	cpu_buffer->nest += NESTED_BITS;
पूर्ण

/**
 * ring_buffer_nest_end - Allow to trace जबतक nested
 * @buffer: The ring buffer to modअगरy
 *
 * Must be called after ring_buffer_nest_start() and after the
 * ring_buffer_unlock_commit().
 */
व्योम ring_buffer_nest_end(काष्ठा trace_buffer *buffer)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	पूर्णांक cpu;

	/* disabled by ring_buffer_nest_start() */
	cpu = raw_smp_processor_id();
	cpu_buffer = buffer->buffers[cpu];
	/* This is the shअगरt value क्रम the above recursive locking */
	cpu_buffer->nest -= NESTED_BITS;
	preempt_enable_notrace();
पूर्ण

/**
 * ring_buffer_unlock_commit - commit a reserved
 * @buffer: The buffer to commit to
 * @event: The event poपूर्णांकer to commit.
 *
 * This commits the data to the ring buffer, and releases any locks held.
 *
 * Must be paired with ring_buffer_lock_reserve.
 */
पूर्णांक ring_buffer_unlock_commit(काष्ठा trace_buffer *buffer,
			      काष्ठा ring_buffer_event *event)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	पूर्णांक cpu = raw_smp_processor_id();

	cpu_buffer = buffer->buffers[cpu];

	rb_commit(cpu_buffer, event);

	rb_wakeups(buffer, cpu_buffer);

	trace_recursive_unlock(cpu_buffer);

	preempt_enable_notrace();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_unlock_commit);

/* Special value to validate all deltas on a page. */
#घोषणा CHECK_FULL_PAGE		1L

#अगर_घोषित CONFIG_RING_BUFFER_VALIDATE_TIME_DELTAS
अटल व्योम dump_buffer_page(काष्ठा buffer_data_page *bpage,
			     काष्ठा rb_event_info *info,
			     अचिन्हित दीर्घ tail)
अणु
	काष्ठा ring_buffer_event *event;
	u64 ts, delta;
	पूर्णांक e;

	ts = bpage->समय_stamp;
	pr_warn("  [%lld] PAGE TIME STAMP\n", ts);

	क्रम (e = 0; e < tail; e += rb_event_length(event)) अणु

		event = (काष्ठा ring_buffer_event *)(bpage->data + e);

		चयन (event->type_len) अणु

		हाल RINGBUF_TYPE_TIME_EXTEND:
			delta = rb_event_समय_stamp(event);
			ts += delta;
			pr_warn("  [%lld] delta:%lld TIME EXTEND\n", ts, delta);
			अवरोध;

		हाल RINGBUF_TYPE_TIME_STAMP:
			delta = rb_event_समय_stamp(event);
			ts = delta;
			pr_warn("  [%lld] absolute:%lld TIME STAMP\n", ts, delta);
			अवरोध;

		हाल RINGBUF_TYPE_PADDING:
			ts += event->समय_delta;
			pr_warn("  [%lld] delta:%d PADDING\n", ts, event->समय_delta);
			अवरोध;

		हाल RINGBUF_TYPE_DATA:
			ts += event->समय_delta;
			pr_warn("  [%lld] delta:%d\n", ts, event->समय_delta);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल DEFINE_PER_CPU(atomic_t, checking);
अटल atomic_t ts_dump;

/*
 * Check अगर the current event समय stamp matches the deltas on
 * the buffer page.
 */
अटल व्योम check_buffer(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			 काष्ठा rb_event_info *info,
			 अचिन्हित दीर्घ tail)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा buffer_data_page *bpage;
	u64 ts, delta;
	bool full = false;
	पूर्णांक e;

	bpage = info->tail_page->page;

	अगर (tail == CHECK_FULL_PAGE) अणु
		full = true;
		tail = local_पढ़ो(&bpage->commit);
	पूर्ण अन्यथा अगर (info->add_बारtamp &
		   (RB_ADD_STAMP_FORCE | RB_ADD_STAMP_ABSOLUTE)) अणु
		/* Ignore events with असलolute समय stamps */
		वापस;
	पूर्ण

	/*
	 * Do not check the first event (skip possible extends too).
	 * Also करो not check अगर previous events have not been committed.
	 */
	अगर (tail <= 8 || tail > local_पढ़ो(&bpage->commit))
		वापस;

	/*
	 * If this पूर्णांकerrupted another event, 
	 */
	अगर (atomic_inc_वापस(this_cpu_ptr(&checking)) != 1)
		जाओ out;

	ts = bpage->समय_stamp;

	क्रम (e = 0; e < tail; e += rb_event_length(event)) अणु

		event = (काष्ठा ring_buffer_event *)(bpage->data + e);

		चयन (event->type_len) अणु

		हाल RINGBUF_TYPE_TIME_EXTEND:
			delta = rb_event_समय_stamp(event);
			ts += delta;
			अवरोध;

		हाल RINGBUF_TYPE_TIME_STAMP:
			delta = rb_event_समय_stamp(event);
			ts = delta;
			अवरोध;

		हाल RINGBUF_TYPE_PADDING:
			अगर (event->समय_delta == 1)
				अवरोध;
			/* fall through */
		हाल RINGBUF_TYPE_DATA:
			ts += event->समय_delta;
			अवरोध;

		शेष:
			RB_WARN_ON(cpu_buffer, 1);
		पूर्ण
	पूर्ण
	अगर ((full && ts > info->ts) ||
	    (!full && ts + info->delta != info->ts)) अणु
		/* If another report is happening, ignore this one */
		अगर (atomic_inc_वापस(&ts_dump) != 1) अणु
			atomic_dec(&ts_dump);
			जाओ out;
		पूर्ण
		atomic_inc(&cpu_buffer->record_disabled);
		/* There's some हालs in boot up that this can happen */
		WARN_ON_ONCE(प्रणाली_state != SYSTEM_BOOTING);
		pr_warn("[CPU: %d]TIME DOES NOT MATCH expected:%lld actual:%lld delta:%lld before:%lld after:%lld%s\n",
			cpu_buffer->cpu,
			ts + info->delta, info->ts, info->delta,
			info->beक्रमe, info->after,
			full ? " (full)" : "");
		dump_buffer_page(bpage, info, tail);
		atomic_dec(&ts_dump);
		/* Do not re-enable checking */
		वापस;
	पूर्ण
out:
	atomic_dec(this_cpu_ptr(&checking));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम check_buffer(काष्ठा ring_buffer_per_cpu *cpu_buffer,
			 काष्ठा rb_event_info *info,
			 अचिन्हित दीर्घ tail)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_RING_BUFFER_VALIDATE_TIME_DELTAS */

अटल काष्ठा ring_buffer_event *
__rb_reserve_next(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		  काष्ठा rb_event_info *info)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा buffer_page *tail_page;
	अचिन्हित दीर्घ tail, ग_लिखो, w;
	bool a_ok;
	bool b_ok;

	/* Don't let the compiler play games with cpu_buffer->tail_page */
	tail_page = info->tail_page = READ_ONCE(cpu_buffer->tail_page);

 /*A*/	w = local_पढ़ो(&tail_page->ग_लिखो) & RB_WRITE_MASK;
	barrier();
	b_ok = rb_समय_पढ़ो(&cpu_buffer->beक्रमe_stamp, &info->beक्रमe);
	a_ok = rb_समय_पढ़ो(&cpu_buffer->ग_लिखो_stamp, &info->after);
	barrier();
	info->ts = rb_समय_stamp(cpu_buffer->buffer);

	अगर ((info->add_बारtamp & RB_ADD_STAMP_ABSOLUTE)) अणु
		info->delta = info->ts;
	पूर्ण अन्यथा अणु
		/*
		 * If पूर्णांकerrupting an event समय update, we may need an
		 * असलolute बारtamp.
		 * Don't bother अगर this is the start of a new page (w == 0).
		 */
		अगर (unlikely(!a_ok || !b_ok || (info->beक्रमe != info->after && w))) अणु
			info->add_बारtamp |= RB_ADD_STAMP_FORCE | RB_ADD_STAMP_EXTEND;
			info->length += RB_LEN_TIME_EXTEND;
		पूर्ण अन्यथा अणु
			info->delta = info->ts - info->after;
			अगर (unlikely(test_समय_stamp(info->delta))) अणु
				info->add_बारtamp |= RB_ADD_STAMP_EXTEND;
				info->length += RB_LEN_TIME_EXTEND;
			पूर्ण
		पूर्ण
	पूर्ण

 /*B*/	rb_समय_set(&cpu_buffer->beक्रमe_stamp, info->ts);

 /*C*/	ग_लिखो = local_add_वापस(info->length, &tail_page->ग_लिखो);

	/* set ग_लिखो to only the index of the ग_लिखो */
	ग_लिखो &= RB_WRITE_MASK;

	tail = ग_लिखो - info->length;

	/* See अगर we shot pass the end of this buffer page */
	अगर (unlikely(ग_लिखो > BUF_PAGE_SIZE)) अणु
		/* beक्रमe and after may now dअगरferent, fix it up*/
		b_ok = rb_समय_पढ़ो(&cpu_buffer->beक्रमe_stamp, &info->beक्रमe);
		a_ok = rb_समय_पढ़ो(&cpu_buffer->ग_लिखो_stamp, &info->after);
		अगर (a_ok && b_ok && info->beक्रमe != info->after)
			(व्योम)rb_समय_cmpxchg(&cpu_buffer->beक्रमe_stamp,
					      info->beक्रमe, info->after);
		अगर (a_ok && b_ok)
			check_buffer(cpu_buffer, info, CHECK_FULL_PAGE);
		वापस rb_move_tail(cpu_buffer, tail, info);
	पूर्ण

	अगर (likely(tail == w)) अणु
		u64 save_beक्रमe;
		bool s_ok;

		/* Nothing पूर्णांकerrupted us between A and C */
 /*D*/		rb_समय_set(&cpu_buffer->ग_लिखो_stamp, info->ts);
		barrier();
 /*E*/		s_ok = rb_समय_पढ़ो(&cpu_buffer->beक्रमe_stamp, &save_beक्रमe);
		RB_WARN_ON(cpu_buffer, !s_ok);
		अगर (likely(!(info->add_बारtamp &
			     (RB_ADD_STAMP_FORCE | RB_ADD_STAMP_ABSOLUTE))))
			/* This did not पूर्णांकerrupt any समय update */
			info->delta = info->ts - info->after;
		अन्यथा
			/* Just use full बारtamp क्रम पूर्णांकerrupting event */
			info->delta = info->ts;
		barrier();
		check_buffer(cpu_buffer, info, tail);
		अगर (unlikely(info->ts != save_beक्रमe)) अणु
			/* SLOW PATH - Interrupted between C and E */

			a_ok = rb_समय_पढ़ो(&cpu_buffer->ग_लिखो_stamp, &info->after);
			RB_WARN_ON(cpu_buffer, !a_ok);

			/* Write stamp must only go क्रमward */
			अगर (save_beक्रमe > info->after) अणु
				/*
				 * We करो not care about the result, only that
				 * it माला_लो updated atomically.
				 */
				(व्योम)rb_समय_cmpxchg(&cpu_buffer->ग_लिखो_stamp,
						      info->after, save_beक्रमe);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		u64 ts;
		/* SLOW PATH - Interrupted between A and C */
		a_ok = rb_समय_पढ़ो(&cpu_buffer->ग_लिखो_stamp, &info->after);
		/* Was पूर्णांकerrupted beक्रमe here, ग_लिखो_stamp must be valid */
		RB_WARN_ON(cpu_buffer, !a_ok);
		ts = rb_समय_stamp(cpu_buffer->buffer);
		barrier();
 /*E*/		अगर (ग_लिखो == (local_पढ़ो(&tail_page->ग_लिखो) & RB_WRITE_MASK) &&
		    info->after < ts &&
		    rb_समय_cmpxchg(&cpu_buffer->ग_लिखो_stamp,
				    info->after, ts)) अणु
			/* Nothing came after this event between C and E */
			info->delta = ts - info->after;
		पूर्ण अन्यथा अणु
			/*
			 * Interrupted between C and E:
			 * Lost the previous events समय stamp. Just set the
			 * delta to zero, and this will be the same समय as
			 * the event this event पूर्णांकerrupted. And the events that
			 * came after this will still be correct (as they would
			 * have built their delta on the previous event.
			 */
			info->delta = 0;
		पूर्ण
		info->ts = ts;
		info->add_बारtamp &= ~RB_ADD_STAMP_FORCE;
	पूर्ण

	/*
	 * If this is the first commit on the page, then it has the same
	 * बारtamp as the page itself.
	 */
	अगर (unlikely(!tail && !(info->add_बारtamp &
				(RB_ADD_STAMP_FORCE | RB_ADD_STAMP_ABSOLUTE))))
		info->delta = 0;

	/* We reserved something on the buffer */

	event = __rb_page_index(tail_page, tail);
	rb_update_event(cpu_buffer, event, info);

	local_inc(&tail_page->entries);

	/*
	 * If this is the first commit on the page, then update
	 * its बारtamp.
	 */
	अगर (unlikely(!tail))
		tail_page->page->समय_stamp = info->ts;

	/* account क्रम these added bytes */
	local_add(info->length, &cpu_buffer->entries_bytes);

	वापस event;
पूर्ण

अटल __always_अंतरभूत काष्ठा ring_buffer_event *
rb_reserve_next_event(काष्ठा trace_buffer *buffer,
		      काष्ठा ring_buffer_per_cpu *cpu_buffer,
		      अचिन्हित दीर्घ length)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा rb_event_info info;
	पूर्णांक nr_loops = 0;
	पूर्णांक add_ts_शेष;

	rb_start_commit(cpu_buffer);
	/* The commit page can not change after this */

#अगर_घोषित CONFIG_RING_BUFFER_ALLOW_SWAP
	/*
	 * Due to the ability to swap a cpu buffer from a buffer
	 * it is possible it was swapped beक्रमe we committed.
	 * (committing stops a swap). We check क्रम it here and
	 * अगर it happened, we have to fail the ग_लिखो.
	 */
	barrier();
	अगर (unlikely(READ_ONCE(cpu_buffer->buffer) != buffer)) अणु
		local_dec(&cpu_buffer->committing);
		local_dec(&cpu_buffer->commits);
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर

	info.length = rb_calculate_event_length(length);

	अगर (ring_buffer_समय_stamp_असल(cpu_buffer->buffer)) अणु
		add_ts_शेष = RB_ADD_STAMP_ABSOLUTE;
		info.length += RB_LEN_TIME_EXTEND;
	पूर्ण अन्यथा अणु
		add_ts_शेष = RB_ADD_STAMP_NONE;
	पूर्ण

 again:
	info.add_बारtamp = add_ts_शेष;
	info.delta = 0;

	/*
	 * We allow क्रम पूर्णांकerrupts to reenter here and करो a trace.
	 * If one करोes, it will cause this original code to loop
	 * back here. Even with heavy पूर्णांकerrupts happening, this
	 * should only happen a few बार in a row. If this happens
	 * 1000 बार in a row, there must be either an पूर्णांकerrupt
	 * storm or we have something buggy.
	 * Bail!
	 */
	अगर (RB_WARN_ON(cpu_buffer, ++nr_loops > 1000))
		जाओ out_fail;

	event = __rb_reserve_next(cpu_buffer, &info);

	अगर (unlikely(PTR_ERR(event) == -EAGAIN)) अणु
		अगर (info.add_बारtamp & (RB_ADD_STAMP_FORCE | RB_ADD_STAMP_EXTEND))
			info.length -= RB_LEN_TIME_EXTEND;
		जाओ again;
	पूर्ण

	अगर (likely(event))
		वापस event;
 out_fail:
	rb_end_commit(cpu_buffer);
	वापस शून्य;
पूर्ण

/**
 * ring_buffer_lock_reserve - reserve a part of the buffer
 * @buffer: the ring buffer to reserve from
 * @length: the length of the data to reserve (excluding event header)
 *
 * Returns a reserved event on the ring buffer to copy directly to.
 * The user of this पूर्णांकerface will need to get the body to ग_लिखो पूर्णांकo
 * and can use the ring_buffer_event_data() पूर्णांकerface.
 *
 * The length is the length of the data needed, not the event length
 * which also includes the event header.
 *
 * Must be paired with ring_buffer_unlock_commit, unless शून्य is वापसed.
 * If शून्य is वापसed, then nothing has been allocated or locked.
 */
काष्ठा ring_buffer_event *
ring_buffer_lock_reserve(काष्ठा trace_buffer *buffer, अचिन्हित दीर्घ length)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा ring_buffer_event *event;
	पूर्णांक cpu;

	/* If we are tracing schedule, we करोn't want to recurse */
	preempt_disable_notrace();

	अगर (unlikely(atomic_पढ़ो(&buffer->record_disabled)))
		जाओ out;

	cpu = raw_smp_processor_id();

	अगर (unlikely(!cpumask_test_cpu(cpu, buffer->cpumask)))
		जाओ out;

	cpu_buffer = buffer->buffers[cpu];

	अगर (unlikely(atomic_पढ़ो(&cpu_buffer->record_disabled)))
		जाओ out;

	अगर (unlikely(length > BUF_MAX_DATA_SIZE))
		जाओ out;

	अगर (unlikely(trace_recursive_lock(cpu_buffer)))
		जाओ out;

	event = rb_reserve_next_event(buffer, cpu_buffer, length);
	अगर (!event)
		जाओ out_unlock;

	वापस event;

 out_unlock:
	trace_recursive_unlock(cpu_buffer);
 out:
	preempt_enable_notrace();
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_lock_reserve);

/*
 * Decrement the entries to the page that an event is on.
 * The event करोes not even need to exist, only the poपूर्णांकer
 * to the page it is on. This may only be called beक्रमe the commit
 * takes place.
 */
अटल अंतरभूत व्योम
rb_decrement_entry(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		   काष्ठा ring_buffer_event *event)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)event;
	काष्ठा buffer_page *bpage = cpu_buffer->commit_page;
	काष्ठा buffer_page *start;

	addr &= PAGE_MASK;

	/* Do the likely हाल first */
	अगर (likely(bpage->page == (व्योम *)addr)) अणु
		local_dec(&bpage->entries);
		वापस;
	पूर्ण

	/*
	 * Because the commit page may be on the पढ़ोer page we
	 * start with the next page and check the end loop there.
	 */
	rb_inc_page(&bpage);
	start = bpage;
	करो अणु
		अगर (bpage->page == (व्योम *)addr) अणु
			local_dec(&bpage->entries);
			वापस;
		पूर्ण
		rb_inc_page(&bpage);
	पूर्ण जबतक (bpage != start);

	/* commit not part of this buffer?? */
	RB_WARN_ON(cpu_buffer, 1);
पूर्ण

/**
 * ring_buffer_discard_commit - discard an event that has not been committed
 * @buffer: the ring buffer
 * @event: non committed event to discard
 *
 * Someबार an event that is in the ring buffer needs to be ignored.
 * This function lets the user discard an event in the ring buffer
 * and then that event will not be पढ़ो later.
 *
 * This function only works अगर it is called beक्रमe the item has been
 * committed. It will try to मुक्त the event from the ring buffer
 * अगर another event has not been added behind it.
 *
 * If another event has been added behind it, it will set the event
 * up as discarded, and perक्रमm the commit.
 *
 * If this function is called, करो not call ring_buffer_unlock_commit on
 * the event.
 */
व्योम ring_buffer_discard_commit(काष्ठा trace_buffer *buffer,
				काष्ठा ring_buffer_event *event)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	पूर्णांक cpu;

	/* The event is discarded regardless */
	rb_event_discard(event);

	cpu = smp_processor_id();
	cpu_buffer = buffer->buffers[cpu];

	/*
	 * This must only be called अगर the event has not been
	 * committed yet. Thus we can assume that preemption
	 * is still disabled.
	 */
	RB_WARN_ON(buffer, !local_पढ़ो(&cpu_buffer->committing));

	rb_decrement_entry(cpu_buffer, event);
	अगर (rb_try_to_discard(cpu_buffer, event))
		जाओ out;

 out:
	rb_end_commit(cpu_buffer);

	trace_recursive_unlock(cpu_buffer);

	preempt_enable_notrace();

पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_discard_commit);

/**
 * ring_buffer_ग_लिखो - ग_लिखो data to the buffer without reserving
 * @buffer: The ring buffer to ग_लिखो to.
 * @length: The length of the data being written (excluding the event header)
 * @data: The data to ग_लिखो to the buffer.
 *
 * This is like ring_buffer_lock_reserve and ring_buffer_unlock_commit as
 * one function. If you alपढ़ोy have the data to ग_लिखो to the buffer, it
 * may be easier to simply call this function.
 *
 * Note, like ring_buffer_lock_reserve, the length is the length of the data
 * and not the length of the event which would hold the header.
 */
पूर्णांक ring_buffer_ग_लिखो(काष्ठा trace_buffer *buffer,
		      अचिन्हित दीर्घ length,
		      व्योम *data)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा ring_buffer_event *event;
	व्योम *body;
	पूर्णांक ret = -EBUSY;
	पूर्णांक cpu;

	preempt_disable_notrace();

	अगर (atomic_पढ़ो(&buffer->record_disabled))
		जाओ out;

	cpu = raw_smp_processor_id();

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		जाओ out;

	cpu_buffer = buffer->buffers[cpu];

	अगर (atomic_पढ़ो(&cpu_buffer->record_disabled))
		जाओ out;

	अगर (length > BUF_MAX_DATA_SIZE)
		जाओ out;

	अगर (unlikely(trace_recursive_lock(cpu_buffer)))
		जाओ out;

	event = rb_reserve_next_event(buffer, cpu_buffer, length);
	अगर (!event)
		जाओ out_unlock;

	body = rb_event_data(event);

	स_नकल(body, data, length);

	rb_commit(cpu_buffer, event);

	rb_wakeups(buffer, cpu_buffer);

	ret = 0;

 out_unlock:
	trace_recursive_unlock(cpu_buffer);

 out:
	preempt_enable_notrace();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_ग_लिखो);

अटल bool rb_per_cpu_empty(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा buffer_page *पढ़ोer = cpu_buffer->पढ़ोer_page;
	काष्ठा buffer_page *head = rb_set_head_page(cpu_buffer);
	काष्ठा buffer_page *commit = cpu_buffer->commit_page;

	/* In हाल of error, head will be शून्य */
	अगर (unlikely(!head))
		वापस true;

	वापस पढ़ोer->पढ़ो == rb_page_commit(पढ़ोer) &&
		(commit == पढ़ोer ||
		 (commit == head &&
		  head->पढ़ो == rb_page_commit(commit)));
पूर्ण

/**
 * ring_buffer_record_disable - stop all ग_लिखोs पूर्णांकo the buffer
 * @buffer: The ring buffer to stop ग_लिखोs to.
 *
 * This prevents all ग_लिखोs to the buffer. Any attempt to ग_लिखो
 * to the buffer after this will fail and वापस शून्य.
 *
 * The caller should call synchronize_rcu() after this.
 */
व्योम ring_buffer_record_disable(काष्ठा trace_buffer *buffer)
अणु
	atomic_inc(&buffer->record_disabled);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_record_disable);

/**
 * ring_buffer_record_enable - enable ग_लिखोs to the buffer
 * @buffer: The ring buffer to enable ग_लिखोs
 *
 * Note, multiple disables will need the same number of enables
 * to truly enable the writing (much like preempt_disable).
 */
व्योम ring_buffer_record_enable(काष्ठा trace_buffer *buffer)
अणु
	atomic_dec(&buffer->record_disabled);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_record_enable);

/**
 * ring_buffer_record_off - stop all ग_लिखोs पूर्णांकo the buffer
 * @buffer: The ring buffer to stop ग_लिखोs to.
 *
 * This prevents all ग_लिखोs to the buffer. Any attempt to ग_लिखो
 * to the buffer after this will fail and वापस शून्य.
 *
 * This is dअगरferent than ring_buffer_record_disable() as
 * it works like an on/off चयन, where as the disable() version
 * must be paired with a enable().
 */
व्योम ring_buffer_record_off(काष्ठा trace_buffer *buffer)
अणु
	अचिन्हित पूर्णांक rd;
	अचिन्हित पूर्णांक new_rd;

	करो अणु
		rd = atomic_पढ़ो(&buffer->record_disabled);
		new_rd = rd | RB_BUFFER_OFF;
	पूर्ण जबतक (atomic_cmpxchg(&buffer->record_disabled, rd, new_rd) != rd);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_record_off);

/**
 * ring_buffer_record_on - restart ग_लिखोs पूर्णांकo the buffer
 * @buffer: The ring buffer to start ग_लिखोs to.
 *
 * This enables all ग_लिखोs to the buffer that was disabled by
 * ring_buffer_record_off().
 *
 * This is dअगरferent than ring_buffer_record_enable() as
 * it works like an on/off चयन, where as the enable() version
 * must be paired with a disable().
 */
व्योम ring_buffer_record_on(काष्ठा trace_buffer *buffer)
अणु
	अचिन्हित पूर्णांक rd;
	अचिन्हित पूर्णांक new_rd;

	करो अणु
		rd = atomic_पढ़ो(&buffer->record_disabled);
		new_rd = rd & ~RB_BUFFER_OFF;
	पूर्ण जबतक (atomic_cmpxchg(&buffer->record_disabled, rd, new_rd) != rd);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_record_on);

/**
 * ring_buffer_record_is_on - वापस true अगर the ring buffer can ग_लिखो
 * @buffer: The ring buffer to see अगर ग_लिखो is enabled
 *
 * Returns true अगर the ring buffer is in a state that it accepts ग_लिखोs.
 */
bool ring_buffer_record_is_on(काष्ठा trace_buffer *buffer)
अणु
	वापस !atomic_पढ़ो(&buffer->record_disabled);
पूर्ण

/**
 * ring_buffer_record_is_set_on - वापस true अगर the ring buffer is set writable
 * @buffer: The ring buffer to see अगर ग_लिखो is set enabled
 *
 * Returns true अगर the ring buffer is set writable by ring_buffer_record_on().
 * Note that this करोes NOT mean it is in a writable state.
 *
 * It may वापस true when the ring buffer has been disabled by
 * ring_buffer_record_disable(), as that is a temporary disabling of
 * the ring buffer.
 */
bool ring_buffer_record_is_set_on(काष्ठा trace_buffer *buffer)
अणु
	वापस !(atomic_पढ़ो(&buffer->record_disabled) & RB_BUFFER_OFF);
पूर्ण

/**
 * ring_buffer_record_disable_cpu - stop all ग_लिखोs पूर्णांकo the cpu_buffer
 * @buffer: The ring buffer to stop ग_लिखोs to.
 * @cpu: The CPU buffer to stop
 *
 * This prevents all ग_लिखोs to the buffer. Any attempt to ग_लिखो
 * to the buffer after this will fail and वापस शून्य.
 *
 * The caller should call synchronize_rcu() after this.
 */
व्योम ring_buffer_record_disable_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस;

	cpu_buffer = buffer->buffers[cpu];
	atomic_inc(&cpu_buffer->record_disabled);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_record_disable_cpu);

/**
 * ring_buffer_record_enable_cpu - enable ग_लिखोs to the buffer
 * @buffer: The ring buffer to enable ग_लिखोs
 * @cpu: The CPU to enable.
 *
 * Note, multiple disables will need the same number of enables
 * to truly enable the writing (much like preempt_disable).
 */
व्योम ring_buffer_record_enable_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस;

	cpu_buffer = buffer->buffers[cpu];
	atomic_dec(&cpu_buffer->record_disabled);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_record_enable_cpu);

/*
 * The total entries in the ring buffer is the running counter
 * of entries entered पूर्णांकo the ring buffer, minus the sum of
 * the entries पढ़ो from the ring buffer and the number of
 * entries that were overwritten.
 */
अटल अंतरभूत अचिन्हित दीर्घ
rb_num_of_entries(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	वापस local_पढ़ो(&cpu_buffer->entries) -
		(local_पढ़ो(&cpu_buffer->overrun) + cpu_buffer->पढ़ो);
पूर्ण

/**
 * ring_buffer_oldest_event_ts - get the oldest event बारtamp from the buffer
 * @buffer: The ring buffer
 * @cpu: The per CPU buffer to पढ़ो from.
 */
u64 ring_buffer_oldest_event_ts(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा buffer_page *bpage;
	u64 ret = 0;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	cpu_buffer = buffer->buffers[cpu];
	raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);
	/*
	 * अगर the tail is on पढ़ोer_page, oldest समय stamp is on the पढ़ोer
	 * page
	 */
	अगर (cpu_buffer->tail_page == cpu_buffer->पढ़ोer_page)
		bpage = cpu_buffer->पढ़ोer_page;
	अन्यथा
		bpage = rb_set_head_page(cpu_buffer);
	अगर (bpage)
		ret = bpage->page->समय_stamp;
	raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_oldest_event_ts);

/**
 * ring_buffer_bytes_cpu - get the number of bytes consumed in a cpu buffer
 * @buffer: The ring buffer
 * @cpu: The per CPU buffer to पढ़ो from.
 */
अचिन्हित दीर्घ ring_buffer_bytes_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ ret;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	cpu_buffer = buffer->buffers[cpu];
	ret = local_पढ़ो(&cpu_buffer->entries_bytes) - cpu_buffer->पढ़ो_bytes;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_bytes_cpu);

/**
 * ring_buffer_entries_cpu - get the number of entries in a cpu buffer
 * @buffer: The ring buffer
 * @cpu: The per CPU buffer to get the entries from.
 */
अचिन्हित दीर्घ ring_buffer_entries_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	cpu_buffer = buffer->buffers[cpu];

	वापस rb_num_of_entries(cpu_buffer);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_entries_cpu);

/**
 * ring_buffer_overrun_cpu - get the number of overruns caused by the ring
 * buffer wrapping around (only अगर RB_FL_OVERWRITE is on).
 * @buffer: The ring buffer
 * @cpu: The per CPU buffer to get the number of overruns from
 */
अचिन्हित दीर्घ ring_buffer_overrun_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ ret;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	cpu_buffer = buffer->buffers[cpu];
	ret = local_पढ़ो(&cpu_buffer->overrun);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_overrun_cpu);

/**
 * ring_buffer_commit_overrun_cpu - get the number of overruns caused by
 * commits failing due to the buffer wrapping around जबतक there are uncommitted
 * events, such as during an पूर्णांकerrupt storm.
 * @buffer: The ring buffer
 * @cpu: The per CPU buffer to get the number of overruns from
 */
अचिन्हित दीर्घ
ring_buffer_commit_overrun_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ ret;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	cpu_buffer = buffer->buffers[cpu];
	ret = local_पढ़ो(&cpu_buffer->commit_overrun);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_commit_overrun_cpu);

/**
 * ring_buffer_dropped_events_cpu - get the number of dropped events caused by
 * the ring buffer filling up (only अगर RB_FL_OVERWRITE is off).
 * @buffer: The ring buffer
 * @cpu: The per CPU buffer to get the number of overruns from
 */
अचिन्हित दीर्घ
ring_buffer_dropped_events_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ ret;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	cpu_buffer = buffer->buffers[cpu];
	ret = local_पढ़ो(&cpu_buffer->dropped_events);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_dropped_events_cpu);

/**
 * ring_buffer_पढ़ो_events_cpu - get the number of events successfully पढ़ो
 * @buffer: The ring buffer
 * @cpu: The per CPU buffer to get the number of events पढ़ो
 */
अचिन्हित दीर्घ
ring_buffer_पढ़ो_events_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	cpu_buffer = buffer->buffers[cpu];
	वापस cpu_buffer->पढ़ो;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_पढ़ो_events_cpu);

/**
 * ring_buffer_entries - get the number of entries in a buffer
 * @buffer: The ring buffer
 *
 * Returns the total number of entries in the ring buffer
 * (all CPU entries)
 */
अचिन्हित दीर्घ ring_buffer_entries(काष्ठा trace_buffer *buffer)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ entries = 0;
	पूर्णांक cpu;

	/* अगर you care about this being correct, lock the buffer */
	क्रम_each_buffer_cpu(buffer, cpu) अणु
		cpu_buffer = buffer->buffers[cpu];
		entries += rb_num_of_entries(cpu_buffer);
	पूर्ण

	वापस entries;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_entries);

/**
 * ring_buffer_overruns - get the number of overruns in buffer
 * @buffer: The ring buffer
 *
 * Returns the total number of overruns in the ring buffer
 * (all CPU entries)
 */
अचिन्हित दीर्घ ring_buffer_overruns(काष्ठा trace_buffer *buffer)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ overruns = 0;
	पूर्णांक cpu;

	/* अगर you care about this being correct, lock the buffer */
	क्रम_each_buffer_cpu(buffer, cpu) अणु
		cpu_buffer = buffer->buffers[cpu];
		overruns += local_पढ़ो(&cpu_buffer->overrun);
	पूर्ण

	वापस overruns;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_overruns);

अटल व्योम rb_iter_reset(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = iter->cpu_buffer;

	/* Iterator usage is expected to have record disabled */
	iter->head_page = cpu_buffer->पढ़ोer_page;
	iter->head = cpu_buffer->पढ़ोer_page->पढ़ो;
	iter->next_event = iter->head;

	iter->cache_पढ़ोer_page = iter->head_page;
	iter->cache_पढ़ो = cpu_buffer->पढ़ो;

	अगर (iter->head) अणु
		iter->पढ़ो_stamp = cpu_buffer->पढ़ो_stamp;
		iter->page_stamp = cpu_buffer->पढ़ोer_page->page->समय_stamp;
	पूर्ण अन्यथा अणु
		iter->पढ़ो_stamp = iter->head_page->page->समय_stamp;
		iter->page_stamp = iter->पढ़ो_stamp;
	पूर्ण
पूर्ण

/**
 * ring_buffer_iter_reset - reset an iterator
 * @iter: The iterator to reset
 *
 * Resets the iterator, so that it will start from the beginning
 * again.
 */
व्योम ring_buffer_iter_reset(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ flags;

	अगर (!iter)
		वापस;

	cpu_buffer = iter->cpu_buffer;

	raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);
	rb_iter_reset(iter);
	raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_iter_reset);

/**
 * ring_buffer_iter_empty - check अगर an iterator has no more to पढ़ो
 * @iter: The iterator to check
 */
पूर्णांक ring_buffer_iter_empty(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा buffer_page *पढ़ोer;
	काष्ठा buffer_page *head_page;
	काष्ठा buffer_page *commit_page;
	काष्ठा buffer_page *curr_commit_page;
	अचिन्हित commit;
	u64 curr_commit_ts;
	u64 commit_ts;

	cpu_buffer = iter->cpu_buffer;
	पढ़ोer = cpu_buffer->पढ़ोer_page;
	head_page = cpu_buffer->head_page;
	commit_page = cpu_buffer->commit_page;
	commit_ts = commit_page->page->समय_stamp;

	/*
	 * When the ग_लिखोr goes across pages, it issues a cmpxchg which
	 * is a mb(), which will synchronize with the rmb here.
	 * (see rb_tail_page_update())
	 */
	smp_rmb();
	commit = rb_page_commit(commit_page);
	/* We want to make sure that the commit page करोesn't change */
	smp_rmb();

	/* Make sure commit page didn't change */
	curr_commit_page = READ_ONCE(cpu_buffer->commit_page);
	curr_commit_ts = READ_ONCE(curr_commit_page->page->समय_stamp);

	/* If the commit page changed, then there's more data */
	अगर (curr_commit_page != commit_page ||
	    curr_commit_ts != commit_ts)
		वापस 0;

	/* Still racy, as it may वापस a false positive, but that's OK */
	वापस ((iter->head_page == commit_page && iter->head >= commit) ||
		(iter->head_page == पढ़ोer && commit_page == head_page &&
		 head_page->पढ़ो == commit &&
		 iter->head == rb_page_commit(cpu_buffer->पढ़ोer_page)));
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_iter_empty);

अटल व्योम
rb_update_पढ़ो_stamp(काष्ठा ring_buffer_per_cpu *cpu_buffer,
		     काष्ठा ring_buffer_event *event)
अणु
	u64 delta;

	चयन (event->type_len) अणु
	हाल RINGBUF_TYPE_PADDING:
		वापस;

	हाल RINGBUF_TYPE_TIME_EXTEND:
		delta = rb_event_समय_stamp(event);
		cpu_buffer->पढ़ो_stamp += delta;
		वापस;

	हाल RINGBUF_TYPE_TIME_STAMP:
		delta = rb_event_समय_stamp(event);
		cpu_buffer->पढ़ो_stamp = delta;
		वापस;

	हाल RINGBUF_TYPE_DATA:
		cpu_buffer->पढ़ो_stamp += event->समय_delta;
		वापस;

	शेष:
		RB_WARN_ON(cpu_buffer, 1);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम
rb_update_iter_पढ़ो_stamp(काष्ठा ring_buffer_iter *iter,
			  काष्ठा ring_buffer_event *event)
अणु
	u64 delta;

	चयन (event->type_len) अणु
	हाल RINGBUF_TYPE_PADDING:
		वापस;

	हाल RINGBUF_TYPE_TIME_EXTEND:
		delta = rb_event_समय_stamp(event);
		iter->पढ़ो_stamp += delta;
		वापस;

	हाल RINGBUF_TYPE_TIME_STAMP:
		delta = rb_event_समय_stamp(event);
		iter->पढ़ो_stamp = delta;
		वापस;

	हाल RINGBUF_TYPE_DATA:
		iter->पढ़ो_stamp += event->समय_delta;
		वापस;

	शेष:
		RB_WARN_ON(iter->cpu_buffer, 1);
	पूर्ण
	वापस;
पूर्ण

अटल काष्ठा buffer_page *
rb_get_पढ़ोer_page(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा buffer_page *पढ़ोer = शून्य;
	अचिन्हित दीर्घ overग_लिखो;
	अचिन्हित दीर्घ flags;
	पूर्णांक nr_loops = 0;
	पूर्णांक ret;

	local_irq_save(flags);
	arch_spin_lock(&cpu_buffer->lock);

 again:
	/*
	 * This should normally only loop twice. But because the
	 * start of the पढ़ोer inserts an empty page, it causes
	 * a हाल where we will loop three बार. There should be no
	 * reason to loop four बार (that I know of).
	 */
	अगर (RB_WARN_ON(cpu_buffer, ++nr_loops > 3)) अणु
		पढ़ोer = शून्य;
		जाओ out;
	पूर्ण

	पढ़ोer = cpu_buffer->पढ़ोer_page;

	/* If there's more to पढ़ो, वापस this page */
	अगर (cpu_buffer->पढ़ोer_page->पढ़ो < rb_page_size(पढ़ोer))
		जाओ out;

	/* Never should we have an index greater than the size */
	अगर (RB_WARN_ON(cpu_buffer,
		       cpu_buffer->पढ़ोer_page->पढ़ो > rb_page_size(पढ़ोer)))
		जाओ out;

	/* check अगर we caught up to the tail */
	पढ़ोer = शून्य;
	अगर (cpu_buffer->commit_page == cpu_buffer->पढ़ोer_page)
		जाओ out;

	/* Don't bother swapping अगर the ring buffer is empty */
	अगर (rb_num_of_entries(cpu_buffer) == 0)
		जाओ out;

	/*
	 * Reset the पढ़ोer page to size zero.
	 */
	local_set(&cpu_buffer->पढ़ोer_page->ग_लिखो, 0);
	local_set(&cpu_buffer->पढ़ोer_page->entries, 0);
	local_set(&cpu_buffer->पढ़ोer_page->page->commit, 0);
	cpu_buffer->पढ़ोer_page->real_end = 0;

 spin:
	/*
	 * Splice the empty पढ़ोer page पूर्णांकo the list around the head.
	 */
	पढ़ोer = rb_set_head_page(cpu_buffer);
	अगर (!पढ़ोer)
		जाओ out;
	cpu_buffer->पढ़ोer_page->list.next = rb_list_head(पढ़ोer->list.next);
	cpu_buffer->पढ़ोer_page->list.prev = पढ़ोer->list.prev;

	/*
	 * cpu_buffer->pages just needs to poपूर्णांक to the buffer, it
	 *  has no specअगरic buffer page to poपूर्णांक to. Lets move it out
	 *  of our way so we करोn't accidentally swap it.
	 */
	cpu_buffer->pages = पढ़ोer->list.prev;

	/* The पढ़ोer page will be poपूर्णांकing to the new head */
	rb_set_list_to_head(&cpu_buffer->पढ़ोer_page->list);

	/*
	 * We want to make sure we पढ़ो the overruns after we set up our
	 * poपूर्णांकers to the next object. The ग_लिखोr side करोes a
	 * cmpxchg to cross pages which acts as the mb on the ग_लिखोr
	 * side. Note, the पढ़ोer will स्थिरantly fail the swap
	 * जबतक the ग_लिखोr is updating the poपूर्णांकers, so this
	 * guarantees that the overग_लिखो recorded here is the one we
	 * want to compare with the last_overrun.
	 */
	smp_mb();
	overग_लिखो = local_पढ़ो(&(cpu_buffer->overrun));

	/*
	 * Here's the tricky part.
	 *
	 * We need to move the poपूर्णांकer past the header page.
	 * But we can only करो that अगर a ग_लिखोr is not currently
	 * moving it. The page beक्रमe the header page has the
	 * flag bit '1' set अगर it is poपूर्णांकing to the page we want.
	 * but अगर the ग_लिखोr is in the process of moving it
	 * than it will be '2' or already moved '0'.
	 */

	ret = rb_head_page_replace(पढ़ोer, cpu_buffer->पढ़ोer_page);

	/*
	 * If we did not convert it, then we must try again.
	 */
	अगर (!ret)
		जाओ spin;

	/*
	 * Yay! We succeeded in replacing the page.
	 *
	 * Now make the new head poपूर्णांक back to the पढ़ोer page.
	 */
	rb_list_head(पढ़ोer->list.next)->prev = &cpu_buffer->पढ़ोer_page->list;
	rb_inc_page(&cpu_buffer->head_page);

	local_inc(&cpu_buffer->pages_पढ़ो);

	/* Finally update the पढ़ोer page to the new head */
	cpu_buffer->पढ़ोer_page = पढ़ोer;
	cpu_buffer->पढ़ोer_page->पढ़ो = 0;

	अगर (overग_लिखो != cpu_buffer->last_overrun) अणु
		cpu_buffer->lost_events = overग_लिखो - cpu_buffer->last_overrun;
		cpu_buffer->last_overrun = overग_लिखो;
	पूर्ण

	जाओ again;

 out:
	/* Update the पढ़ो_stamp on the first event */
	अगर (पढ़ोer && पढ़ोer->पढ़ो == 0)
		cpu_buffer->पढ़ो_stamp = पढ़ोer->page->समय_stamp;

	arch_spin_unlock(&cpu_buffer->lock);
	local_irq_restore(flags);

	वापस पढ़ोer;
पूर्ण

अटल व्योम rb_advance_पढ़ोer(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा buffer_page *पढ़ोer;
	अचिन्हित length;

	पढ़ोer = rb_get_पढ़ोer_page(cpu_buffer);

	/* This function should not be called when buffer is empty */
	अगर (RB_WARN_ON(cpu_buffer, !पढ़ोer))
		वापस;

	event = rb_पढ़ोer_event(cpu_buffer);

	अगर (event->type_len <= RINGBUF_TYPE_DATA_TYPE_LEN_MAX)
		cpu_buffer->पढ़ो++;

	rb_update_पढ़ो_stamp(cpu_buffer, event);

	length = rb_event_length(event);
	cpu_buffer->पढ़ोer_page->पढ़ो += length;
पूर्ण

अटल व्योम rb_advance_iter(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;

	cpu_buffer = iter->cpu_buffer;

	/* If head == next_event then we need to jump to the next event */
	अगर (iter->head == iter->next_event) अणु
		/* If the event माला_लो overwritten again, there's nothing to करो */
		अगर (rb_iter_head_event(iter) == शून्य)
			वापस;
	पूर्ण

	iter->head = iter->next_event;

	/*
	 * Check अगर we are at the end of the buffer.
	 */
	अगर (iter->next_event >= rb_page_size(iter->head_page)) अणु
		/* discarded commits can make the page empty */
		अगर (iter->head_page == cpu_buffer->commit_page)
			वापस;
		rb_inc_iter(iter);
		वापस;
	पूर्ण

	rb_update_iter_पढ़ो_stamp(iter, iter->event);
पूर्ण

अटल पूर्णांक rb_lost_events(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	वापस cpu_buffer->lost_events;
पूर्ण

अटल काष्ठा ring_buffer_event *
rb_buffer_peek(काष्ठा ring_buffer_per_cpu *cpu_buffer, u64 *ts,
	       अचिन्हित दीर्घ *lost_events)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा buffer_page *पढ़ोer;
	पूर्णांक nr_loops = 0;

	अगर (ts)
		*ts = 0;
 again:
	/*
	 * We repeat when a समय extend is encountered.
	 * Since the समय extend is always attached to a data event,
	 * we should never loop more than once.
	 * (We never hit the following condition more than twice).
	 */
	अगर (RB_WARN_ON(cpu_buffer, ++nr_loops > 2))
		वापस शून्य;

	पढ़ोer = rb_get_पढ़ोer_page(cpu_buffer);
	अगर (!पढ़ोer)
		वापस शून्य;

	event = rb_पढ़ोer_event(cpu_buffer);

	चयन (event->type_len) अणु
	हाल RINGBUF_TYPE_PADDING:
		अगर (rb_null_event(event))
			RB_WARN_ON(cpu_buffer, 1);
		/*
		 * Because the ग_लिखोr could be discarding every
		 * event it creates (which would probably be bad)
		 * अगर we were to go back to "again" then we may never
		 * catch up, and will trigger the warn on, or lock
		 * the box. Return the padding, and we will release
		 * the current locks, and try again.
		 */
		वापस event;

	हाल RINGBUF_TYPE_TIME_EXTEND:
		/* Internal data, OK to advance */
		rb_advance_पढ़ोer(cpu_buffer);
		जाओ again;

	हाल RINGBUF_TYPE_TIME_STAMP:
		अगर (ts) अणु
			*ts = rb_event_समय_stamp(event);
			ring_buffer_normalize_समय_stamp(cpu_buffer->buffer,
							 cpu_buffer->cpu, ts);
		पूर्ण
		/* Internal data, OK to advance */
		rb_advance_पढ़ोer(cpu_buffer);
		जाओ again;

	हाल RINGBUF_TYPE_DATA:
		अगर (ts && !(*ts)) अणु
			*ts = cpu_buffer->पढ़ो_stamp + event->समय_delta;
			ring_buffer_normalize_समय_stamp(cpu_buffer->buffer,
							 cpu_buffer->cpu, ts);
		पूर्ण
		अगर (lost_events)
			*lost_events = rb_lost_events(cpu_buffer);
		वापस event;

	शेष:
		RB_WARN_ON(cpu_buffer, 1);
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_peek);

अटल काष्ठा ring_buffer_event *
rb_iter_peek(काष्ठा ring_buffer_iter *iter, u64 *ts)
अणु
	काष्ठा trace_buffer *buffer;
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा ring_buffer_event *event;
	पूर्णांक nr_loops = 0;

	अगर (ts)
		*ts = 0;

	cpu_buffer = iter->cpu_buffer;
	buffer = cpu_buffer->buffer;

	/*
	 * Check अगर someone perक्रमmed a consuming पढ़ो to
	 * the buffer. A consuming पढ़ो invalidates the iterator
	 * and we need to reset the iterator in this हाल.
	 */
	अगर (unlikely(iter->cache_पढ़ो != cpu_buffer->पढ़ो ||
		     iter->cache_पढ़ोer_page != cpu_buffer->पढ़ोer_page))
		rb_iter_reset(iter);

 again:
	अगर (ring_buffer_iter_empty(iter))
		वापस शून्य;

	/*
	 * As the ग_लिखोr can mess with what the iterator is trying
	 * to पढ़ो, just give up अगर we fail to get an event after
	 * three tries. The iterator is not as reliable when पढ़ोing
	 * the ring buffer with an active ग_लिखो as the consumer is.
	 * Do not warn अगर the three failures is reached.
	 */
	अगर (++nr_loops > 3)
		वापस शून्य;

	अगर (rb_per_cpu_empty(cpu_buffer))
		वापस शून्य;

	अगर (iter->head >= rb_page_size(iter->head_page)) अणु
		rb_inc_iter(iter);
		जाओ again;
	पूर्ण

	event = rb_iter_head_event(iter);
	अगर (!event)
		जाओ again;

	चयन (event->type_len) अणु
	हाल RINGBUF_TYPE_PADDING:
		अगर (rb_null_event(event)) अणु
			rb_inc_iter(iter);
			जाओ again;
		पूर्ण
		rb_advance_iter(iter);
		वापस event;

	हाल RINGBUF_TYPE_TIME_EXTEND:
		/* Internal data, OK to advance */
		rb_advance_iter(iter);
		जाओ again;

	हाल RINGBUF_TYPE_TIME_STAMP:
		अगर (ts) अणु
			*ts = rb_event_समय_stamp(event);
			ring_buffer_normalize_समय_stamp(cpu_buffer->buffer,
							 cpu_buffer->cpu, ts);
		पूर्ण
		/* Internal data, OK to advance */
		rb_advance_iter(iter);
		जाओ again;

	हाल RINGBUF_TYPE_DATA:
		अगर (ts && !(*ts)) अणु
			*ts = iter->पढ़ो_stamp + event->समय_delta;
			ring_buffer_normalize_समय_stamp(buffer,
							 cpu_buffer->cpu, ts);
		पूर्ण
		वापस event;

	शेष:
		RB_WARN_ON(cpu_buffer, 1);
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_iter_peek);

अटल अंतरभूत bool rb_पढ़ोer_lock(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	अगर (likely(!in_nmi())) अणु
		raw_spin_lock(&cpu_buffer->पढ़ोer_lock);
		वापस true;
	पूर्ण

	/*
	 * If an NMI die dumps out the content of the ring buffer
	 * trylock must be used to prevent a deadlock अगर the NMI
	 * preempted a task that holds the ring buffer locks. If
	 * we get the lock then all is fine, अगर not, then जारी
	 * to करो the पढ़ो, but this can corrupt the ring buffer,
	 * so it must be permanently disabled from future ग_लिखोs.
	 * Reading from NMI is a oneshot deal.
	 */
	अगर (raw_spin_trylock(&cpu_buffer->पढ़ोer_lock))
		वापस true;

	/* Continue without locking, but disable the ring buffer */
	atomic_inc(&cpu_buffer->record_disabled);
	वापस false;
पूर्ण

अटल अंतरभूत व्योम
rb_पढ़ोer_unlock(काष्ठा ring_buffer_per_cpu *cpu_buffer, bool locked)
अणु
	अगर (likely(locked))
		raw_spin_unlock(&cpu_buffer->पढ़ोer_lock);
	वापस;
पूर्ण

/**
 * ring_buffer_peek - peek at the next event to be पढ़ो
 * @buffer: The ring buffer to पढ़ो
 * @cpu: The cpu to peak at
 * @ts: The बारtamp counter of this event.
 * @lost_events: a variable to store अगर events were lost (may be शून्य)
 *
 * This will वापस the event that will be पढ़ो next, but करोes
 * not consume the data.
 */
काष्ठा ring_buffer_event *
ring_buffer_peek(काष्ठा trace_buffer *buffer, पूर्णांक cpu, u64 *ts,
		 अचिन्हित दीर्घ *lost_events)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = buffer->buffers[cpu];
	काष्ठा ring_buffer_event *event;
	अचिन्हित दीर्घ flags;
	bool करोlock;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस शून्य;

 again:
	local_irq_save(flags);
	करोlock = rb_पढ़ोer_lock(cpu_buffer);
	event = rb_buffer_peek(cpu_buffer, ts, lost_events);
	अगर (event && event->type_len == RINGBUF_TYPE_PADDING)
		rb_advance_पढ़ोer(cpu_buffer);
	rb_पढ़ोer_unlock(cpu_buffer, करोlock);
	local_irq_restore(flags);

	अगर (event && event->type_len == RINGBUF_TYPE_PADDING)
		जाओ again;

	वापस event;
पूर्ण

/** ring_buffer_iter_dropped - report अगर there are dropped events
 * @iter: The ring buffer iterator
 *
 * Returns true अगर there was dropped events since the last peek.
 */
bool ring_buffer_iter_dropped(काष्ठा ring_buffer_iter *iter)
अणु
	bool ret = iter->missed_events != 0;

	iter->missed_events = 0;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_iter_dropped);

/**
 * ring_buffer_iter_peek - peek at the next event to be पढ़ो
 * @iter: The ring buffer iterator
 * @ts: The बारtamp counter of this event.
 *
 * This will वापस the event that will be पढ़ो next, but करोes
 * not increment the iterator.
 */
काष्ठा ring_buffer_event *
ring_buffer_iter_peek(काष्ठा ring_buffer_iter *iter, u64 *ts)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = iter->cpu_buffer;
	काष्ठा ring_buffer_event *event;
	अचिन्हित दीर्घ flags;

 again:
	raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);
	event = rb_iter_peek(iter, ts);
	raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);

	अगर (event && event->type_len == RINGBUF_TYPE_PADDING)
		जाओ again;

	वापस event;
पूर्ण

/**
 * ring_buffer_consume - वापस an event and consume it
 * @buffer: The ring buffer to get the next event from
 * @cpu: the cpu to पढ़ो the buffer from
 * @ts: a variable to store the बारtamp (may be शून्य)
 * @lost_events: a variable to store अगर events were lost (may be शून्य)
 *
 * Returns the next event in the ring buffer, and that event is consumed.
 * Meaning, that sequential पढ़ोs will keep वापसing a dअगरferent event,
 * and eventually empty the ring buffer अगर the producer is slower.
 */
काष्ठा ring_buffer_event *
ring_buffer_consume(काष्ठा trace_buffer *buffer, पूर्णांक cpu, u64 *ts,
		    अचिन्हित दीर्घ *lost_events)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा ring_buffer_event *event = शून्य;
	अचिन्हित दीर्घ flags;
	bool करोlock;

 again:
	/* might be called in atomic */
	preempt_disable();

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		जाओ out;

	cpu_buffer = buffer->buffers[cpu];
	local_irq_save(flags);
	करोlock = rb_पढ़ोer_lock(cpu_buffer);

	event = rb_buffer_peek(cpu_buffer, ts, lost_events);
	अगर (event) अणु
		cpu_buffer->lost_events = 0;
		rb_advance_पढ़ोer(cpu_buffer);
	पूर्ण

	rb_पढ़ोer_unlock(cpu_buffer, करोlock);
	local_irq_restore(flags);

 out:
	preempt_enable();

	अगर (event && event->type_len == RINGBUF_TYPE_PADDING)
		जाओ again;

	वापस event;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_consume);

/**
 * ring_buffer_पढ़ो_prepare - Prepare क्रम a non consuming पढ़ो of the buffer
 * @buffer: The ring buffer to पढ़ो from
 * @cpu: The cpu buffer to iterate over
 * @flags: gfp flags to use क्रम memory allocation
 *
 * This perक्रमms the initial preparations necessary to iterate
 * through the buffer.  Memory is allocated, buffer recording
 * is disabled, and the iterator poपूर्णांकer is वापसed to the caller.
 *
 * Disabling buffer recording prevents the पढ़ोing from being
 * corrupted. This is not a consuming पढ़ो, so a producer is not
 * expected.
 *
 * After a sequence of ring_buffer_पढ़ो_prepare calls, the user is
 * expected to make at least one call to ring_buffer_पढ़ो_prepare_sync.
 * Afterwards, ring_buffer_पढ़ो_start is invoked to get things going
 * क्रम real.
 *
 * This overall must be paired with ring_buffer_पढ़ो_finish.
 */
काष्ठा ring_buffer_iter *
ring_buffer_पढ़ो_prepare(काष्ठा trace_buffer *buffer, पूर्णांक cpu, gfp_t flags)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा ring_buffer_iter *iter;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस शून्य;

	iter = kzalloc(माप(*iter), flags);
	अगर (!iter)
		वापस शून्य;

	iter->event = kदो_स्मृति(BUF_MAX_DATA_SIZE, flags);
	अगर (!iter->event) अणु
		kमुक्त(iter);
		वापस शून्य;
	पूर्ण

	cpu_buffer = buffer->buffers[cpu];

	iter->cpu_buffer = cpu_buffer;

	atomic_inc(&cpu_buffer->resize_disabled);

	वापस iter;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_पढ़ो_prepare);

/**
 * ring_buffer_पढ़ो_prepare_sync - Synchronize a set of prepare calls
 *
 * All previously invoked ring_buffer_पढ़ो_prepare calls to prepare
 * iterators will be synchronized.  Afterwards, पढ़ो_buffer_पढ़ो_start
 * calls on those iterators are allowed.
 */
व्योम
ring_buffer_पढ़ो_prepare_sync(व्योम)
अणु
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_पढ़ो_prepare_sync);

/**
 * ring_buffer_पढ़ो_start - start a non consuming पढ़ो of the buffer
 * @iter: The iterator वापसed by ring_buffer_पढ़ो_prepare
 *
 * This finalizes the startup of an iteration through the buffer.
 * The iterator comes from a call to ring_buffer_पढ़ो_prepare and
 * an पूर्णांकervening ring_buffer_पढ़ो_prepare_sync must have been
 * perक्रमmed.
 *
 * Must be paired with ring_buffer_पढ़ो_finish.
 */
व्योम
ring_buffer_पढ़ो_start(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ flags;

	अगर (!iter)
		वापस;

	cpu_buffer = iter->cpu_buffer;

	raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);
	arch_spin_lock(&cpu_buffer->lock);
	rb_iter_reset(iter);
	arch_spin_unlock(&cpu_buffer->lock);
	raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_पढ़ो_start);

/**
 * ring_buffer_पढ़ो_finish - finish पढ़ोing the iterator of the buffer
 * @iter: The iterator retrieved by ring_buffer_start
 *
 * This re-enables the recording to the buffer, and मुक्तs the
 * iterator.
 */
व्योम
ring_buffer_पढ़ो_finish(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = iter->cpu_buffer;
	अचिन्हित दीर्घ flags;

	/*
	 * Ring buffer is disabled from recording, here's a good place
	 * to check the पूर्णांकegrity of the ring buffer.
	 * Must prevent पढ़ोers from trying to पढ़ो, as the check
	 * clears the HEAD page and पढ़ोers require it.
	 */
	raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);
	rb_check_pages(cpu_buffer);
	raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);

	atomic_dec(&cpu_buffer->resize_disabled);
	kमुक्त(iter->event);
	kमुक्त(iter);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_पढ़ो_finish);

/**
 * ring_buffer_iter_advance - advance the iterator to the next location
 * @iter: The ring buffer iterator
 *
 * Move the location of the iterator such that the next पढ़ो will
 * be the next location of the iterator.
 */
व्योम ring_buffer_iter_advance(काष्ठा ring_buffer_iter *iter)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = iter->cpu_buffer;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);

	rb_advance_iter(iter);

	raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_iter_advance);

/**
 * ring_buffer_size - वापस the size of the ring buffer (in bytes)
 * @buffer: The ring buffer.
 * @cpu: The CPU to get ring buffer size from.
 */
अचिन्हित दीर्घ ring_buffer_size(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	/*
	 * Earlier, this method वापसed
	 *	BUF_PAGE_SIZE * buffer->nr_pages
	 * Since the nr_pages field is now हटाओd, we have converted this to
	 * वापस the per cpu buffer value.
	 */
	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	वापस BUF_PAGE_SIZE * buffer->buffers[cpu]->nr_pages;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_size);

अटल व्योम
rb_reset_cpu(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	rb_head_page_deactivate(cpu_buffer);

	cpu_buffer->head_page
		= list_entry(cpu_buffer->pages, काष्ठा buffer_page, list);
	local_set(&cpu_buffer->head_page->ग_लिखो, 0);
	local_set(&cpu_buffer->head_page->entries, 0);
	local_set(&cpu_buffer->head_page->page->commit, 0);

	cpu_buffer->head_page->पढ़ो = 0;

	cpu_buffer->tail_page = cpu_buffer->head_page;
	cpu_buffer->commit_page = cpu_buffer->head_page;

	INIT_LIST_HEAD(&cpu_buffer->पढ़ोer_page->list);
	INIT_LIST_HEAD(&cpu_buffer->new_pages);
	local_set(&cpu_buffer->पढ़ोer_page->ग_लिखो, 0);
	local_set(&cpu_buffer->पढ़ोer_page->entries, 0);
	local_set(&cpu_buffer->पढ़ोer_page->page->commit, 0);
	cpu_buffer->पढ़ोer_page->पढ़ो = 0;

	local_set(&cpu_buffer->entries_bytes, 0);
	local_set(&cpu_buffer->overrun, 0);
	local_set(&cpu_buffer->commit_overrun, 0);
	local_set(&cpu_buffer->dropped_events, 0);
	local_set(&cpu_buffer->entries, 0);
	local_set(&cpu_buffer->committing, 0);
	local_set(&cpu_buffer->commits, 0);
	local_set(&cpu_buffer->pages_touched, 0);
	local_set(&cpu_buffer->pages_पढ़ो, 0);
	cpu_buffer->last_pages_touch = 0;
	cpu_buffer->लघुest_full = 0;
	cpu_buffer->पढ़ो = 0;
	cpu_buffer->पढ़ो_bytes = 0;

	rb_समय_set(&cpu_buffer->ग_लिखो_stamp, 0);
	rb_समय_set(&cpu_buffer->beक्रमe_stamp, 0);

	स_रखो(cpu_buffer->event_stamp, 0, माप(cpu_buffer->event_stamp));

	cpu_buffer->lost_events = 0;
	cpu_buffer->last_overrun = 0;

	rb_head_page_activate(cpu_buffer);
पूर्ण

/* Must have disabled the cpu buffer then करोne a synchronize_rcu */
अटल व्योम reset_disabled_cpu_buffer(काष्ठा ring_buffer_per_cpu *cpu_buffer)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);

	अगर (RB_WARN_ON(cpu_buffer, local_पढ़ो(&cpu_buffer->committing)))
		जाओ out;

	arch_spin_lock(&cpu_buffer->lock);

	rb_reset_cpu(cpu_buffer);

	arch_spin_unlock(&cpu_buffer->lock);

 out:
	raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);
पूर्ण

/**
 * ring_buffer_reset_cpu - reset a ring buffer per CPU buffer
 * @buffer: The ring buffer to reset a per cpu buffer of
 * @cpu: The CPU buffer to be reset
 */
व्योम ring_buffer_reset_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = buffer->buffers[cpu];

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस;

	/* prevent another thपढ़ो from changing buffer sizes */
	mutex_lock(&buffer->mutex);

	atomic_inc(&cpu_buffer->resize_disabled);
	atomic_inc(&cpu_buffer->record_disabled);

	/* Make sure all commits have finished */
	synchronize_rcu();

	reset_disabled_cpu_buffer(cpu_buffer);

	atomic_dec(&cpu_buffer->record_disabled);
	atomic_dec(&cpu_buffer->resize_disabled);

	mutex_unlock(&buffer->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_reset_cpu);

/**
 * ring_buffer_reset_cpu - reset a ring buffer per CPU buffer
 * @buffer: The ring buffer to reset a per cpu buffer of
 * @cpu: The CPU buffer to be reset
 */
व्योम ring_buffer_reset_online_cpus(काष्ठा trace_buffer *buffer)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	पूर्णांक cpu;

	/* prevent another thपढ़ो from changing buffer sizes */
	mutex_lock(&buffer->mutex);

	क्रम_each_online_buffer_cpu(buffer, cpu) अणु
		cpu_buffer = buffer->buffers[cpu];

		atomic_inc(&cpu_buffer->resize_disabled);
		atomic_inc(&cpu_buffer->record_disabled);
	पूर्ण

	/* Make sure all commits have finished */
	synchronize_rcu();

	क्रम_each_online_buffer_cpu(buffer, cpu) अणु
		cpu_buffer = buffer->buffers[cpu];

		reset_disabled_cpu_buffer(cpu_buffer);

		atomic_dec(&cpu_buffer->record_disabled);
		atomic_dec(&cpu_buffer->resize_disabled);
	पूर्ण

	mutex_unlock(&buffer->mutex);
पूर्ण

/**
 * ring_buffer_reset - reset a ring buffer
 * @buffer: The ring buffer to reset all cpu buffers
 */
व्योम ring_buffer_reset(काष्ठा trace_buffer *buffer)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	पूर्णांक cpu;

	क्रम_each_buffer_cpu(buffer, cpu) अणु
		cpu_buffer = buffer->buffers[cpu];

		atomic_inc(&cpu_buffer->resize_disabled);
		atomic_inc(&cpu_buffer->record_disabled);
	पूर्ण

	/* Make sure all commits have finished */
	synchronize_rcu();

	क्रम_each_buffer_cpu(buffer, cpu) अणु
		cpu_buffer = buffer->buffers[cpu];

		reset_disabled_cpu_buffer(cpu_buffer);

		atomic_dec(&cpu_buffer->record_disabled);
		atomic_dec(&cpu_buffer->resize_disabled);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_reset);

/**
 * rind_buffer_empty - is the ring buffer empty?
 * @buffer: The ring buffer to test
 */
bool ring_buffer_empty(काष्ठा trace_buffer *buffer)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ flags;
	bool करोlock;
	पूर्णांक cpu;
	पूर्णांक ret;

	/* yes this is racy, but अगर you करोn't like the race, lock the buffer */
	क्रम_each_buffer_cpu(buffer, cpu) अणु
		cpu_buffer = buffer->buffers[cpu];
		local_irq_save(flags);
		करोlock = rb_पढ़ोer_lock(cpu_buffer);
		ret = rb_per_cpu_empty(cpu_buffer);
		rb_पढ़ोer_unlock(cpu_buffer, करोlock);
		local_irq_restore(flags);

		अगर (!ret)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_empty);

/**
 * ring_buffer_empty_cpu - is a cpu buffer of a ring buffer empty?
 * @buffer: The ring buffer
 * @cpu: The CPU buffer to test
 */
bool ring_buffer_empty_cpu(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	अचिन्हित दीर्घ flags;
	bool करोlock;
	पूर्णांक ret;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस true;

	cpu_buffer = buffer->buffers[cpu];
	local_irq_save(flags);
	करोlock = rb_पढ़ोer_lock(cpu_buffer);
	ret = rb_per_cpu_empty(cpu_buffer);
	rb_पढ़ोer_unlock(cpu_buffer, करोlock);
	local_irq_restore(flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_empty_cpu);

#अगर_घोषित CONFIG_RING_BUFFER_ALLOW_SWAP
/**
 * ring_buffer_swap_cpu - swap a CPU buffer between two ring buffers
 * @buffer_a: One buffer to swap with
 * @buffer_b: The other buffer to swap with
 * @cpu: the CPU of the buffers to swap
 *
 * This function is useful क्रम tracers that want to take a "snapshot"
 * of a CPU buffer and has another back up buffer lying around.
 * it is expected that the tracer handles the cpu buffer not being
 * used at the moment.
 */
पूर्णांक ring_buffer_swap_cpu(काष्ठा trace_buffer *buffer_a,
			 काष्ठा trace_buffer *buffer_b, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer_a;
	काष्ठा ring_buffer_per_cpu *cpu_buffer_b;
	पूर्णांक ret = -EINVAL;

	अगर (!cpumask_test_cpu(cpu, buffer_a->cpumask) ||
	    !cpumask_test_cpu(cpu, buffer_b->cpumask))
		जाओ out;

	cpu_buffer_a = buffer_a->buffers[cpu];
	cpu_buffer_b = buffer_b->buffers[cpu];

	/* At least make sure the two buffers are somewhat the same */
	अगर (cpu_buffer_a->nr_pages != cpu_buffer_b->nr_pages)
		जाओ out;

	ret = -EAGAIN;

	अगर (atomic_पढ़ो(&buffer_a->record_disabled))
		जाओ out;

	अगर (atomic_पढ़ो(&buffer_b->record_disabled))
		जाओ out;

	अगर (atomic_पढ़ो(&cpu_buffer_a->record_disabled))
		जाओ out;

	अगर (atomic_पढ़ो(&cpu_buffer_b->record_disabled))
		जाओ out;

	/*
	 * We can't करो a synchronize_rcu here because this
	 * function can be called in atomic context.
	 * Normally this will be called from the same CPU as cpu.
	 * If not it's up to the caller to protect this.
	 */
	atomic_inc(&cpu_buffer_a->record_disabled);
	atomic_inc(&cpu_buffer_b->record_disabled);

	ret = -EBUSY;
	अगर (local_पढ़ो(&cpu_buffer_a->committing))
		जाओ out_dec;
	अगर (local_पढ़ो(&cpu_buffer_b->committing))
		जाओ out_dec;

	buffer_a->buffers[cpu] = cpu_buffer_b;
	buffer_b->buffers[cpu] = cpu_buffer_a;

	cpu_buffer_b->buffer = buffer_a;
	cpu_buffer_a->buffer = buffer_b;

	ret = 0;

out_dec:
	atomic_dec(&cpu_buffer_a->record_disabled);
	atomic_dec(&cpu_buffer_b->record_disabled);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_swap_cpu);
#पूर्ण_अगर /* CONFIG_RING_BUFFER_ALLOW_SWAP */

/**
 * ring_buffer_alloc_पढ़ो_page - allocate a page to पढ़ो from buffer
 * @buffer: the buffer to allocate क्रम.
 * @cpu: the cpu buffer to allocate.
 *
 * This function is used in conjunction with ring_buffer_पढ़ो_page.
 * When पढ़ोing a full page from the ring buffer, these functions
 * can be used to speed up the process. The calling function should
 * allocate a few pages first with this function. Then when it
 * needs to get pages from the ring buffer, it passes the result
 * of this function पूर्णांकo ring_buffer_पढ़ो_page, which will swap
 * the page that was allocated, with the पढ़ो page of the buffer.
 *
 * Returns:
 *  The page allocated, or ERR_PTR
 */
व्योम *ring_buffer_alloc_पढ़ो_page(काष्ठा trace_buffer *buffer, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer;
	काष्ठा buffer_data_page *bpage = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा page *page;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		वापस ERR_PTR(-ENODEV);

	cpu_buffer = buffer->buffers[cpu];
	local_irq_save(flags);
	arch_spin_lock(&cpu_buffer->lock);

	अगर (cpu_buffer->मुक्त_page) अणु
		bpage = cpu_buffer->मुक्त_page;
		cpu_buffer->मुक्त_page = शून्य;
	पूर्ण

	arch_spin_unlock(&cpu_buffer->lock);
	local_irq_restore(flags);

	अगर (bpage)
		जाओ out;

	page = alloc_pages_node(cpu_to_node(cpu),
				GFP_KERNEL | __GFP_NORETRY, 0);
	अगर (!page)
		वापस ERR_PTR(-ENOMEM);

	bpage = page_address(page);

 out:
	rb_init_page(bpage);

	वापस bpage;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_alloc_पढ़ो_page);

/**
 * ring_buffer_मुक्त_पढ़ो_page - मुक्त an allocated पढ़ो page
 * @buffer: the buffer the page was allocate क्रम
 * @cpu: the cpu buffer the page came from
 * @data: the page to मुक्त
 *
 * Free a page allocated from ring_buffer_alloc_पढ़ो_page.
 */
व्योम ring_buffer_मुक्त_पढ़ो_page(काष्ठा trace_buffer *buffer, पूर्णांक cpu, व्योम *data)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = buffer->buffers[cpu];
	काष्ठा buffer_data_page *bpage = data;
	काष्ठा page *page = virt_to_page(bpage);
	अचिन्हित दीर्घ flags;

	/* If the page is still in use someplace अन्यथा, we can't reuse it */
	अगर (page_ref_count(page) > 1)
		जाओ out;

	local_irq_save(flags);
	arch_spin_lock(&cpu_buffer->lock);

	अगर (!cpu_buffer->मुक्त_page) अणु
		cpu_buffer->मुक्त_page = bpage;
		bpage = शून्य;
	पूर्ण

	arch_spin_unlock(&cpu_buffer->lock);
	local_irq_restore(flags);

 out:
	मुक्त_page((अचिन्हित दीर्घ)bpage);
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_मुक्त_पढ़ो_page);

/**
 * ring_buffer_पढ़ो_page - extract a page from the ring buffer
 * @buffer: buffer to extract from
 * @data_page: the page to use allocated from ring_buffer_alloc_पढ़ो_page
 * @len: amount to extract
 * @cpu: the cpu of the buffer to extract
 * @full: should the extraction only happen when the page is full.
 *
 * This function will pull out a page from the ring buffer and consume it.
 * @data_page must be the address of the variable that was वापसed
 * from ring_buffer_alloc_पढ़ो_page. This is because the page might be used
 * to swap with a page in the ring buffer.
 *
 * क्रम example:
 *	rpage = ring_buffer_alloc_पढ़ो_page(buffer, cpu);
 *	अगर (IS_ERR(rpage))
 *		वापस PTR_ERR(rpage);
 *	ret = ring_buffer_पढ़ो_page(buffer, &rpage, len, cpu, 0);
 *	अगर (ret >= 0)
 *		process_page(rpage, ret);
 *
 * When @full is set, the function will not वापस true unless
 * the ग_लिखोr is off the पढ़ोer page.
 *
 * Note: it is up to the calling functions to handle sleeps and wakeups.
 *  The ring buffer can be used anywhere in the kernel and can not
 *  blindly call wake_up. The layer that uses the ring buffer must be
 *  responsible क्रम that.
 *
 * Returns:
 *  >=0 अगर data has been transferred, वापसs the offset of consumed data.
 *  <0 अगर no data has been transferred.
 */
पूर्णांक ring_buffer_पढ़ो_page(काष्ठा trace_buffer *buffer,
			  व्योम **data_page, माप_प्रकार len, पूर्णांक cpu, पूर्णांक full)
अणु
	काष्ठा ring_buffer_per_cpu *cpu_buffer = buffer->buffers[cpu];
	काष्ठा ring_buffer_event *event;
	काष्ठा buffer_data_page *bpage;
	काष्ठा buffer_page *पढ़ोer;
	अचिन्हित दीर्घ missed_events;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक commit;
	अचिन्हित पूर्णांक पढ़ो;
	u64 save_बारtamp;
	पूर्णांक ret = -1;

	अगर (!cpumask_test_cpu(cpu, buffer->cpumask))
		जाओ out;

	/*
	 * If len is not big enough to hold the page header, then
	 * we can not copy anything.
	 */
	अगर (len <= BUF_PAGE_HDR_SIZE)
		जाओ out;

	len -= BUF_PAGE_HDR_SIZE;

	अगर (!data_page)
		जाओ out;

	bpage = *data_page;
	अगर (!bpage)
		जाओ out;

	raw_spin_lock_irqsave(&cpu_buffer->पढ़ोer_lock, flags);

	पढ़ोer = rb_get_पढ़ोer_page(cpu_buffer);
	अगर (!पढ़ोer)
		जाओ out_unlock;

	event = rb_पढ़ोer_event(cpu_buffer);

	पढ़ो = पढ़ोer->पढ़ो;
	commit = rb_page_commit(पढ़ोer);

	/* Check अगर any events were dropped */
	missed_events = cpu_buffer->lost_events;

	/*
	 * If this page has been partially पढ़ो or
	 * अगर len is not big enough to पढ़ो the rest of the page or
	 * a ग_लिखोr is still on the page, then
	 * we must copy the data from the page to the buffer.
	 * Otherwise, we can simply swap the page with the one passed in.
	 */
	अगर (पढ़ो || (len < (commit - पढ़ो)) ||
	    cpu_buffer->पढ़ोer_page == cpu_buffer->commit_page) अणु
		काष्ठा buffer_data_page *rpage = cpu_buffer->पढ़ोer_page->page;
		अचिन्हित पूर्णांक rpos = पढ़ो;
		अचिन्हित पूर्णांक pos = 0;
		अचिन्हित पूर्णांक size;

		अगर (full)
			जाओ out_unlock;

		अगर (len > (commit - पढ़ो))
			len = (commit - पढ़ो);

		/* Always keep the समय extend and data together */
		size = rb_event_ts_length(event);

		अगर (len < size)
			जाओ out_unlock;

		/* save the current बारtamp, since the user will need it */
		save_बारtamp = cpu_buffer->पढ़ो_stamp;

		/* Need to copy one event at a समय */
		करो अणु
			/* We need the size of one event, because
			 * rb_advance_पढ़ोer only advances by one event,
			 * whereas rb_event_ts_length may include the size of
			 * one or two events.
			 * We have alपढ़ोy ensured there's enough space अगर this
			 * is a समय extend. */
			size = rb_event_length(event);
			स_नकल(bpage->data + pos, rpage->data + rpos, size);

			len -= size;

			rb_advance_पढ़ोer(cpu_buffer);
			rpos = पढ़ोer->पढ़ो;
			pos += size;

			अगर (rpos >= commit)
				अवरोध;

			event = rb_पढ़ोer_event(cpu_buffer);
			/* Always keep the समय extend and data together */
			size = rb_event_ts_length(event);
		पूर्ण जबतक (len >= size);

		/* update bpage */
		local_set(&bpage->commit, pos);
		bpage->समय_stamp = save_बारtamp;

		/* we copied everything to the beginning */
		पढ़ो = 0;
	पूर्ण अन्यथा अणु
		/* update the entry counter */
		cpu_buffer->पढ़ो += rb_page_entries(पढ़ोer);
		cpu_buffer->पढ़ो_bytes += BUF_PAGE_SIZE;

		/* swap the pages */
		rb_init_page(bpage);
		bpage = पढ़ोer->page;
		पढ़ोer->page = *data_page;
		local_set(&पढ़ोer->ग_लिखो, 0);
		local_set(&पढ़ोer->entries, 0);
		पढ़ोer->पढ़ो = 0;
		*data_page = bpage;

		/*
		 * Use the real_end क्रम the data size,
		 * This gives us a chance to store the lost events
		 * on the page.
		 */
		अगर (पढ़ोer->real_end)
			local_set(&bpage->commit, पढ़ोer->real_end);
	पूर्ण
	ret = पढ़ो;

	cpu_buffer->lost_events = 0;

	commit = local_पढ़ो(&bpage->commit);
	/*
	 * Set a flag in the commit field अगर we lost events
	 */
	अगर (missed_events) अणु
		/* If there is room at the end of the page to save the
		 * missed events, then record it there.
		 */
		अगर (BUF_PAGE_SIZE - commit >= माप(missed_events)) अणु
			स_नकल(&bpage->data[commit], &missed_events,
			       माप(missed_events));
			local_add(RB_MISSED_STORED, &bpage->commit);
			commit += माप(missed_events);
		पूर्ण
		local_add(RB_MISSED_EVENTS, &bpage->commit);
	पूर्ण

	/*
	 * This page may be off to user land. Zero it out here.
	 */
	अगर (commit < BUF_PAGE_SIZE)
		स_रखो(&bpage->data[commit], 0, BUF_PAGE_SIZE - commit);

 out_unlock:
	raw_spin_unlock_irqrestore(&cpu_buffer->पढ़ोer_lock, flags);

 out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ring_buffer_पढ़ो_page);

/*
 * We only allocate new buffers, never मुक्त them अगर the CPU goes करोwn.
 * If we were to मुक्त the buffer, then the user would lose any trace that was in
 * the buffer.
 */
पूर्णांक trace_rb_cpu_prepare(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा trace_buffer *buffer;
	दीर्घ nr_pages_same;
	पूर्णांक cpu_i;
	अचिन्हित दीर्घ nr_pages;

	buffer = container_of(node, काष्ठा trace_buffer, node);
	अगर (cpumask_test_cpu(cpu, buffer->cpumask))
		वापस 0;

	nr_pages = 0;
	nr_pages_same = 1;
	/* check अगर all cpu sizes are same */
	क्रम_each_buffer_cpu(buffer, cpu_i) अणु
		/* fill in the size from first enabled cpu */
		अगर (nr_pages == 0)
			nr_pages = buffer->buffers[cpu_i]->nr_pages;
		अगर (nr_pages != buffer->buffers[cpu_i]->nr_pages) अणु
			nr_pages_same = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	/* allocate minimum pages, user can later expand it */
	अगर (!nr_pages_same)
		nr_pages = 2;
	buffer->buffers[cpu] =
		rb_allocate_cpu_buffer(buffer, nr_pages, cpu);
	अगर (!buffer->buffers[cpu]) अणु
		WARN(1, "failed to allocate ring buffer on CPU %u\n",
		     cpu);
		वापस -ENOMEM;
	पूर्ण
	smp_wmb();
	cpumask_set_cpu(cpu, buffer->cpumask);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_RING_BUFFER_STARTUP_TEST
/*
 * This is a basic पूर्णांकegrity check of the ring buffer.
 * Late in the boot cycle this test will run when configured in.
 * It will kick off a thपढ़ो per CPU that will go पूर्णांकo a loop
 * writing to the per cpu ring buffer various sizes of data.
 * Some of the data will be large items, some small.
 *
 * Another thपढ़ो is created that goes पूर्णांकo a spin, sending out
 * IPIs to the other CPUs to also ग_लिखो पूर्णांकo the ring buffer.
 * this is to test the nesting ability of the buffer.
 *
 * Basic stats are recorded and reported. If something in the
 * ring buffer should happen that's not expected, a big warning
 * is displayed and all ring buffers are disabled.
 */
अटल काष्ठा task_काष्ठा *rb_thपढ़ोs[NR_CPUS] __initdata;

काष्ठा rb_test_data अणु
	काष्ठा trace_buffer *buffer;
	अचिन्हित दीर्घ		events;
	अचिन्हित दीर्घ		bytes_written;
	अचिन्हित दीर्घ		bytes_alloc;
	अचिन्हित दीर्घ		bytes_dropped;
	अचिन्हित दीर्घ		events_nested;
	अचिन्हित दीर्घ		bytes_written_nested;
	अचिन्हित दीर्घ		bytes_alloc_nested;
	अचिन्हित दीर्घ		bytes_dropped_nested;
	पूर्णांक			min_size_nested;
	पूर्णांक			max_size_nested;
	पूर्णांक			max_size;
	पूर्णांक			min_size;
	पूर्णांक			cpu;
	पूर्णांक			cnt;
पूर्ण;

अटल काष्ठा rb_test_data rb_data[NR_CPUS] __initdata;

/* 1 meg per cpu */
#घोषणा RB_TEST_BUFFER_SIZE	1048576

अटल अक्षर rb_string[] __initdata =
	"abcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()?+\\"
	"?+|:';\",.<>/?abcdefghijklmnopqrstuvwxyz1234567890"
	"!@#$%^&*()?+\\?+|:';\",.<>/?abcdefghijklmnopqrstuv";

अटल bool rb_test_started __initdata;

काष्ठा rb_item अणु
	पूर्णांक size;
	अक्षर str[];
पूर्ण;

अटल __init पूर्णांक rb_ग_लिखो_something(काष्ठा rb_test_data *data, bool nested)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा rb_item *item;
	bool started;
	पूर्णांक event_len;
	पूर्णांक size;
	पूर्णांक len;
	पूर्णांक cnt;

	/* Have nested ग_लिखोs dअगरferent that what is written */
	cnt = data->cnt + (nested ? 27 : 0);

	/* Multiply cnt by ~e, to make some unique increment */
	size = (cnt * 68 / 25) % (माप(rb_string) - 1);

	len = size + माप(काष्ठा rb_item);

	started = rb_test_started;
	/* पढ़ो rb_test_started beक्रमe checking buffer enabled */
	smp_rmb();

	event = ring_buffer_lock_reserve(data->buffer, len);
	अगर (!event) अणु
		/* Ignore dropped events beक्रमe test starts. */
		अगर (started) अणु
			अगर (nested)
				data->bytes_dropped += len;
			अन्यथा
				data->bytes_dropped_nested += len;
		पूर्ण
		वापस len;
	पूर्ण

	event_len = ring_buffer_event_length(event);

	अगर (RB_WARN_ON(data->buffer, event_len < len))
		जाओ out;

	item = ring_buffer_event_data(event);
	item->size = size;
	स_नकल(item->str, rb_string, size);

	अगर (nested) अणु
		data->bytes_alloc_nested += event_len;
		data->bytes_written_nested += len;
		data->events_nested++;
		अगर (!data->min_size_nested || len < data->min_size_nested)
			data->min_size_nested = len;
		अगर (len > data->max_size_nested)
			data->max_size_nested = len;
	पूर्ण अन्यथा अणु
		data->bytes_alloc += event_len;
		data->bytes_written += len;
		data->events++;
		अगर (!data->min_size || len < data->min_size)
			data->max_size = len;
		अगर (len > data->max_size)
			data->max_size = len;
	पूर्ण

 out:
	ring_buffer_unlock_commit(data->buffer, event);

	वापस 0;
पूर्ण

अटल __init पूर्णांक rb_test(व्योम *arg)
अणु
	काष्ठा rb_test_data *data = arg;

	जबतक (!kthपढ़ो_should_stop()) अणु
		rb_ग_लिखो_something(data, false);
		data->cnt++;

		set_current_state(TASK_INTERRUPTIBLE);
		/* Now sleep between a min of 100-300us and a max of 1ms */
		usleep_range(((data->cnt % 3) + 1) * 100, 1000);
	पूर्ण

	वापस 0;
पूर्ण

अटल __init व्योम rb_ipi(व्योम *ignore)
अणु
	काष्ठा rb_test_data *data;
	पूर्णांक cpu = smp_processor_id();

	data = &rb_data[cpu];
	rb_ग_लिखो_something(data, true);
पूर्ण

अटल __init पूर्णांक rb_hammer_test(व्योम *arg)
अणु
	जबतक (!kthपढ़ो_should_stop()) अणु

		/* Send an IPI to all cpus to ग_लिखो data! */
		smp_call_function(rb_ipi, शून्य, 1);
		/* No sleep, but क्रम non preempt, let others run */
		schedule();
	पूर्ण

	वापस 0;
पूर्ण

अटल __init पूर्णांक test_ringbuffer(व्योम)
अणु
	काष्ठा task_काष्ठा *rb_hammer;
	काष्ठा trace_buffer *buffer;
	पूर्णांक cpu;
	पूर्णांक ret = 0;

	अगर (security_locked_करोwn(LOCKDOWN_TRACEFS)) अणु
		pr_warn("Lockdown is enabled, skipping ring buffer tests\n");
		वापस 0;
	पूर्ण

	pr_info("Running ring buffer tests...\n");

	buffer = ring_buffer_alloc(RB_TEST_BUFFER_SIZE, RB_FL_OVERWRITE);
	अगर (WARN_ON(!buffer))
		वापस 0;

	/* Disable buffer so that thपढ़ोs can't ग_लिखो to it yet */
	ring_buffer_record_off(buffer);

	क्रम_each_online_cpu(cpu) अणु
		rb_data[cpu].buffer = buffer;
		rb_data[cpu].cpu = cpu;
		rb_data[cpu].cnt = cpu;
		rb_thपढ़ोs[cpu] = kthपढ़ो_create(rb_test, &rb_data[cpu],
						 "rbtester/%d", cpu);
		अगर (WARN_ON(IS_ERR(rb_thपढ़ोs[cpu]))) अणु
			pr_cont("FAILED\n");
			ret = PTR_ERR(rb_thपढ़ोs[cpu]);
			जाओ out_मुक्त;
		पूर्ण

		kthपढ़ो_bind(rb_thपढ़ोs[cpu], cpu);
 		wake_up_process(rb_thपढ़ोs[cpu]);
	पूर्ण

	/* Now create the rb hammer! */
	rb_hammer = kthपढ़ो_run(rb_hammer_test, शून्य, "rbhammer");
	अगर (WARN_ON(IS_ERR(rb_hammer))) अणु
		pr_cont("FAILED\n");
		ret = PTR_ERR(rb_hammer);
		जाओ out_मुक्त;
	पूर्ण

	ring_buffer_record_on(buffer);
	/*
	 * Show buffer is enabled beक्रमe setting rb_test_started.
	 * Yes there's a small race winकरोw where events could be
	 * dropped and the thपढ़ो wont catch it. But when a ring
	 * buffer माला_लो enabled, there will always be some kind of
	 * delay beक्रमe other CPUs see it. Thus, we करोn't care about
	 * those dropped events. We care about events dropped after
	 * the thपढ़ोs see that the buffer is active.
	 */
	smp_wmb();
	rb_test_started = true;

	set_current_state(TASK_INTERRUPTIBLE);
	/* Just run क्रम 10 seconds */;
	schedule_समयout(10 * HZ);

	kthपढ़ो_stop(rb_hammer);

 out_मुक्त:
	क्रम_each_online_cpu(cpu) अणु
		अगर (!rb_thपढ़ोs[cpu])
			अवरोध;
		kthपढ़ो_stop(rb_thपढ़ोs[cpu]);
	पूर्ण
	अगर (ret) अणु
		ring_buffer_मुक्त(buffer);
		वापस ret;
	पूर्ण

	/* Report! */
	pr_info("finished\n");
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा ring_buffer_event *event;
		काष्ठा rb_test_data *data = &rb_data[cpu];
		काष्ठा rb_item *item;
		अचिन्हित दीर्घ total_events;
		अचिन्हित दीर्घ total_dropped;
		अचिन्हित दीर्घ total_written;
		अचिन्हित दीर्घ total_alloc;
		अचिन्हित दीर्घ total_पढ़ो = 0;
		अचिन्हित दीर्घ total_size = 0;
		अचिन्हित दीर्घ total_len = 0;
		अचिन्हित दीर्घ total_lost = 0;
		अचिन्हित दीर्घ lost;
		पूर्णांक big_event_size;
		पूर्णांक small_event_size;

		ret = -1;

		total_events = data->events + data->events_nested;
		total_written = data->bytes_written + data->bytes_written_nested;
		total_alloc = data->bytes_alloc + data->bytes_alloc_nested;
		total_dropped = data->bytes_dropped + data->bytes_dropped_nested;

		big_event_size = data->max_size + data->max_size_nested;
		small_event_size = data->min_size + data->min_size_nested;

		pr_info("CPU %d:\n", cpu);
		pr_info("              events:    %ld\n", total_events);
		pr_info("       dropped bytes:    %ld\n", total_dropped);
		pr_info("       alloced bytes:    %ld\n", total_alloc);
		pr_info("       written bytes:    %ld\n", total_written);
		pr_info("       biggest event:    %d\n", big_event_size);
		pr_info("      smallest event:    %d\n", small_event_size);

		अगर (RB_WARN_ON(buffer, total_dropped))
			अवरोध;

		ret = 0;

		जबतक ((event = ring_buffer_consume(buffer, cpu, शून्य, &lost))) अणु
			total_lost += lost;
			item = ring_buffer_event_data(event);
			total_len += ring_buffer_event_length(event);
			total_size += item->size + माप(काष्ठा rb_item);
			अगर (स_भेद(&item->str[0], rb_string, item->size) != 0) अणु
				pr_info("FAILED!\n");
				pr_info("buffer had: %.*s\n", item->size, item->str);
				pr_info("expected:   %.*s\n", item->size, rb_string);
				RB_WARN_ON(buffer, 1);
				ret = -1;
				अवरोध;
			पूर्ण
			total_पढ़ो++;
		पूर्ण
		अगर (ret)
			अवरोध;

		ret = -1;

		pr_info("         read events:   %ld\n", total_पढ़ो);
		pr_info("         lost events:   %ld\n", total_lost);
		pr_info("        total events:   %ld\n", total_lost + total_पढ़ो);
		pr_info("  recorded len bytes:   %ld\n", total_len);
		pr_info(" recorded size bytes:   %ld\n", total_size);
		अगर (total_lost)
			pr_info(" With dropped events, record len and size may not match\n"
				" alloced and written from above\n");
		अगर (!total_lost) अणु
			अगर (RB_WARN_ON(buffer, total_len != total_alloc ||
				       total_size != total_written))
				अवरोध;
		पूर्ण
		अगर (RB_WARN_ON(buffer, total_lost + total_पढ़ो != total_events))
			अवरोध;

		ret = 0;
	पूर्ण
	अगर (!ret)
		pr_info("Ring buffer PASSED!\n");

	ring_buffer_मुक्त(buffer);
	वापस 0;
पूर्ण

late_initcall(test_ringbuffer);
#पूर्ण_अगर /* CONFIG_RING_BUFFER_STARTUP_TEST */
