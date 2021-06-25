<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2010-2012 Broadcom. All rights reserved. */

#अगर_अघोषित VCHIQ_CORE_H
#घोषणा VCHIQ_CORE_H

#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kref.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/रुको.h>
#समावेश <linux/raspberrypi/vchiq.h>

#समावेश "vchiq_cfg.h"


/* Do this so that we can test-build the code on non-rpi प्रणालीs */
#अगर IS_ENABLED(CONFIG_RASPBERRYPI_FIRMWARE)

#अन्यथा

#अगर_अघोषित dsb
#घोषणा dsb(a)
#पूर्ण_अगर

#पूर्ण_अगर	/* IS_ENABLED(CONFIG_RASPBERRYPI_FIRMWARE) */

#घोषणा VCHIQ_SERVICE_HANDLE_INVALID 0

#घोषणा VCHIQ_SLOT_SIZE     4096
#घोषणा VCHIQ_MAX_MSG_SIZE  (VCHIQ_SLOT_SIZE - माप(काष्ठा vchiq_header))

/* Run समय control of log level, based on KERN_XXX level. */
#घोषणा VCHIQ_LOG_DEFAULT  4
#घोषणा VCHIQ_LOG_ERROR    3
#घोषणा VCHIQ_LOG_WARNING  4
#घोषणा VCHIQ_LOG_INFO     6
#घोषणा VCHIQ_LOG_TRACE    7

#घोषणा VCHIQ_LOG_PREFIX   KERN_INFO "vchiq: "

#अगर_अघोषित vchiq_log_error
#घोषणा vchiq_log_error(cat, fmt, ...) \
	करो अणु अगर (cat >= VCHIQ_LOG_ERROR) \
		prपूर्णांकk(VCHIQ_LOG_PREFIX fmt "\n", ##__VA_ARGS__); पूर्ण जबतक (0)
#पूर्ण_अगर
#अगर_अघोषित vchiq_log_warning
#घोषणा vchiq_log_warning(cat, fmt, ...) \
	करो अणु अगर (cat >= VCHIQ_LOG_WARNING) \
		 prपूर्णांकk(VCHIQ_LOG_PREFIX fmt "\n", ##__VA_ARGS__); पूर्ण जबतक (0)
#पूर्ण_अगर
#अगर_अघोषित vchiq_log_info
#घोषणा vchiq_log_info(cat, fmt, ...) \
	करो अणु अगर (cat >= VCHIQ_LOG_INFO) \
		prपूर्णांकk(VCHIQ_LOG_PREFIX fmt "\n", ##__VA_ARGS__); पूर्ण जबतक (0)
#पूर्ण_अगर
#अगर_अघोषित vchiq_log_trace
#घोषणा vchiq_log_trace(cat, fmt, ...) \
	करो अणु अगर (cat >= VCHIQ_LOG_TRACE) \
		prपूर्णांकk(VCHIQ_LOG_PREFIX fmt "\n", ##__VA_ARGS__); पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा vchiq_loud_error(...) \
	vchiq_log_error(vchiq_core_log_level, "===== " __VA_ARGS__)

#अगर_अघोषित vchiq_अटल_निश्चित
#घोषणा vchiq_अटल_निश्चित(cond) __attribute__((unused)) \
	बाह्य पूर्णांक vchiq_अटल_निश्चित[(cond) ? 1 : -1]
#पूर्ण_अगर

#घोषणा IS_POW2(x) (x && ((x & (x - 1)) == 0))

/* Ensure that the slot size and maximum number of slots are घातers of 2 */
vchiq_अटल_निश्चित(IS_POW2(VCHIQ_SLOT_SIZE));
vchiq_अटल_निश्चित(IS_POW2(VCHIQ_MAX_SLOTS));
vchiq_अटल_निश्चित(IS_POW2(VCHIQ_MAX_SLOTS_PER_SIDE));

#घोषणा VCHIQ_SLOT_MASK        (VCHIQ_SLOT_SIZE - 1)
#घोषणा VCHIQ_SLOT_QUEUE_MASK  (VCHIQ_MAX_SLOTS_PER_SIDE - 1)
#घोषणा VCHIQ_SLOT_ZERO_SLOTS  DIV_ROUND_UP(माप(काष्ठा vchiq_slot_zero), \
					    VCHIQ_SLOT_SIZE)

#घोषणा VCHIQ_MSG_PADDING            0  /* -                                 */
#घोषणा VCHIQ_MSG_CONNECT            1  /* -                                 */
#घोषणा VCHIQ_MSG_OPEN               2  /* + (srcport, -), fourcc, client_id */
#घोषणा VCHIQ_MSG_OPENACK            3  /* + (srcport, dstport)              */
#घोषणा VCHIQ_MSG_CLOSE              4  /* + (srcport, dstport)              */
#घोषणा VCHIQ_MSG_DATA               5  /* + (srcport, dstport)              */
#घोषणा VCHIQ_MSG_BULK_RX            6  /* + (srcport, dstport), data, size  */
#घोषणा VCHIQ_MSG_BULK_TX            7  /* + (srcport, dstport), data, size  */
#घोषणा VCHIQ_MSG_BULK_RX_DONE       8  /* + (srcport, dstport), actual      */
#घोषणा VCHIQ_MSG_BULK_TX_DONE       9  /* + (srcport, dstport), actual      */
#घोषणा VCHIQ_MSG_PAUSE             10  /* -                                 */
#घोषणा VCHIQ_MSG_RESUME            11  /* -                                 */
#घोषणा VCHIQ_MSG_REMOTE_USE        12  /* -                                 */
#घोषणा VCHIQ_MSG_REMOTE_RELEASE    13  /* -                                 */
#घोषणा VCHIQ_MSG_REMOTE_USE_ACTIVE 14  /* -                                 */

#घोषणा VCHIQ_PORT_MAX                 (VCHIQ_MAX_SERVICES - 1)
#घोषणा VCHIQ_PORT_FREE                0x1000
#घोषणा VCHIQ_PORT_IS_VALID(port)      (port < VCHIQ_PORT_FREE)
#घोषणा VCHIQ_MAKE_MSG(type, srcport, dstport) \
	((type<<24) | (srcport<<12) | (dstport<<0))
#घोषणा VCHIQ_MSG_TYPE(msgid)          ((अचिन्हित पूर्णांक)msgid >> 24)
#घोषणा VCHIQ_MSG_SRCPORT(msgid) \
	(अचिन्हित लघु)(((अचिन्हित पूर्णांक)msgid >> 12) & 0xfff)
#घोषणा VCHIQ_MSG_DSTPORT(msgid) \
	((अचिन्हित लघु)msgid & 0xfff)

#घोषणा VCHIQ_FOURCC_AS_4CHARS(fourcc)	\
	((fourcc) >> 24) & 0xff, \
	((fourcc) >> 16) & 0xff, \
	((fourcc) >>  8) & 0xff, \
	(fourcc) & 0xff

/* Ensure the fields are wide enough */
vchiq_अटल_निश्चित(VCHIQ_MSG_SRCPORT(VCHIQ_MAKE_MSG(0, 0, VCHIQ_PORT_MAX))
	== 0);
vchiq_अटल_निश्चित(VCHIQ_MSG_TYPE(VCHIQ_MAKE_MSG(0, VCHIQ_PORT_MAX, 0)) == 0);
vchiq_अटल_निश्चित((अचिन्हित पूर्णांक)VCHIQ_PORT_MAX <
	(अचिन्हित पूर्णांक)VCHIQ_PORT_FREE);

#घोषणा VCHIQ_MSGID_PADDING            VCHIQ_MAKE_MSG(VCHIQ_MSG_PADDING, 0, 0)
#घोषणा VCHIQ_MSGID_CLAIMED            0x40000000

#घोषणा VCHIQ_FOURCC_INVALID           0x00000000
#घोषणा VCHIQ_FOURCC_IS_LEGAL(fourcc)  (fourcc != VCHIQ_FOURCC_INVALID)

#घोषणा VCHIQ_BULK_ACTUAL_ABORTED -1

प्रकार uपूर्णांक32_t BITSET_T;

vchiq_अटल_निश्चित((माप(BITSET_T) * 8) == 32);

#घोषणा BITSET_SIZE(b)        ((b + 31) >> 5)
#घोषणा BITSET_WORD(b)        (b >> 5)
#घोषणा BITSET_BIT(b)         (1 << (b & 31))
#घोषणा BITSET_IS_SET(bs, b)  (bs[BITSET_WORD(b)] & BITSET_BIT(b))
#घोषणा BITSET_SET(bs, b)     (bs[BITSET_WORD(b)] |= BITSET_BIT(b))
#घोषणा BITSET_CLR(bs, b)     (bs[BITSET_WORD(b)] &= ~BITSET_BIT(b))

#अगर VCHIQ_ENABLE_STATS
#घोषणा VCHIQ_STATS_INC(state, stat) (state->stats. stat++)
#घोषणा VCHIQ_SERVICE_STATS_INC(service, stat) (service->stats. stat++)
#घोषणा VCHIQ_SERVICE_STATS_ADD(service, stat, addend) \
	(service->stats. stat += addend)
#अन्यथा
#घोषणा VCHIQ_STATS_INC(state, stat) ((व्योम)0)
#घोषणा VCHIQ_SERVICE_STATS_INC(service, stat) ((व्योम)0)
#घोषणा VCHIQ_SERVICE_STATS_ADD(service, stat, addend) ((व्योम)0)
#पूर्ण_अगर

क्रमागत अणु
	DEBUG_ENTRIES,
#अगर VCHIQ_ENABLE_DEBUG
	DEBUG_SLOT_HANDLER_COUNT,
	DEBUG_SLOT_HANDLER_LINE,
	DEBUG_PARSE_LINE,
	DEBUG_PARSE_HEADER,
	DEBUG_PARSE_MSGID,
	DEBUG_AWAIT_COMPLETION_LINE,
	DEBUG_DEQUEUE_MESSAGE_LINE,
	DEBUG_SERVICE_CALLBACK_LINE,
	DEBUG_MSG_QUEUE_FULL_COUNT,
	DEBUG_COMPLETION_QUEUE_FULL_COUNT,
#पूर्ण_अगर
	DEBUG_MAX
पूर्ण;

#अगर VCHIQ_ENABLE_DEBUG

#घोषणा DEBUG_INITIALISE(local) पूर्णांक *debug_ptr = (local)->debug;
#घोषणा DEBUG_TRACE(d) \
	करो अणु debug_ptr[DEBUG_ ## d] = __LINE__; dsb(sy); पूर्ण जबतक (0)
#घोषणा DEBUG_VALUE(d, v) \
	करो अणु debug_ptr[DEBUG_ ## d] = (v); dsb(sy); पूर्ण जबतक (0)
#घोषणा DEBUG_COUNT(d) \
	करो अणु debug_ptr[DEBUG_ ## d]++; dsb(sy); पूर्ण जबतक (0)

#अन्यथा /* VCHIQ_ENABLE_DEBUG */

#घोषणा DEBUG_INITIALISE(local)
#घोषणा DEBUG_TRACE(d)
#घोषणा DEBUG_VALUE(d, v)
#घोषणा DEBUG_COUNT(d)

#पूर्ण_अगर /* VCHIQ_ENABLE_DEBUG */

क्रमागत vchiq_connstate अणु
	VCHIQ_CONNSTATE_DISCONNECTED,
	VCHIQ_CONNSTATE_CONNECTING,
	VCHIQ_CONNSTATE_CONNECTED,
	VCHIQ_CONNSTATE_PAUSING,
	VCHIQ_CONNSTATE_PAUSE_SENT,
	VCHIQ_CONNSTATE_PAUSED,
	VCHIQ_CONNSTATE_RESUMING,
	VCHIQ_CONNSTATE_PAUSE_TIMEOUT,
	VCHIQ_CONNSTATE_RESUME_TIMEOUT
पूर्ण;

क्रमागत अणु
	VCHIQ_SRVSTATE_FREE,
	VCHIQ_SRVSTATE_HIDDEN,
	VCHIQ_SRVSTATE_LISTENING,
	VCHIQ_SRVSTATE_OPENING,
	VCHIQ_SRVSTATE_OPEN,
	VCHIQ_SRVSTATE_OPENSYNC,
	VCHIQ_SRVSTATE_CLOSESENT,
	VCHIQ_SRVSTATE_CLOSERECVD,
	VCHIQ_SRVSTATE_CLOSEWAIT,
	VCHIQ_SRVSTATE_CLOSED
पूर्ण;

क्रमागत अणु
	VCHIQ_POLL_TERMINATE,
	VCHIQ_POLL_REMOVE,
	VCHIQ_POLL_TXNOTIFY,
	VCHIQ_POLL_RXNOTIFY,
	VCHIQ_POLL_COUNT
पूर्ण;

क्रमागत vchiq_bulk_dir अणु
	VCHIQ_BULK_TRANSMIT,
	VCHIQ_BULK_RECEIVE
पूर्ण;

प्रकार व्योम (*vchiq_userdata_term)(व्योम *userdata);

काष्ठा vchiq_bulk अणु
	लघु mode;
	लघु dir;
	व्योम *userdata;
	dma_addr_t data;
	पूर्णांक size;
	व्योम *remote_data;
	पूर्णांक remote_size;
	पूर्णांक actual;
पूर्ण;

काष्ठा vchiq_bulk_queue अणु
	पूर्णांक local_insert;  /* Where to insert the next local bulk */
	पूर्णांक remote_insert; /* Where to insert the next remote bulk (master) */
	पूर्णांक process;       /* Bulk to transfer next */
	पूर्णांक remote_notअगरy; /* Bulk to notअगरy the remote client of next (mstr) */
	पूर्णांक हटाओ;        /* Bulk to notअगरy the local client of, and हटाओ, next */
	काष्ठा vchiq_bulk bulks[VCHIQ_NUM_SERVICE_BULKS];
पूर्ण;

काष्ठा remote_event अणु
	पूर्णांक armed;
	पूर्णांक fired;
	u32 __unused;
पूर्ण;

काष्ठा opaque_platक्रमm_state;

काष्ठा vchiq_slot अणु
	अक्षर data[VCHIQ_SLOT_SIZE];
पूर्ण;

काष्ठा vchiq_slot_info अणु
	/* Use two counters rather than one to aव्योम the need क्रम a mutex. */
	लघु use_count;
	लघु release_count;
पूर्ण;

काष्ठा vchiq_service अणु
	काष्ठा vchiq_service_base base;
	अचिन्हित पूर्णांक handle;
	काष्ठा kref ref_count;
	काष्ठा rcu_head rcu;
	पूर्णांक srvstate;
	vchiq_userdata_term userdata_term;
	अचिन्हित पूर्णांक localport;
	अचिन्हित पूर्णांक remoteport;
	पूर्णांक खुला_fourcc;
	पूर्णांक client_id;
	अक्षर स्वतः_बंद;
	अक्षर sync;
	अक्षर closing;
	अक्षर trace;
	atomic_t poll_flags;
	लघु version;
	लघु version_min;
	लघु peer_version;

	काष्ठा vchiq_state *state;
	काष्ठा vchiq_instance *instance;

	पूर्णांक service_use_count;

	काष्ठा vchiq_bulk_queue bulk_tx;
	काष्ठा vchiq_bulk_queue bulk_rx;

	काष्ठा completion हटाओ_event;
	काष्ठा completion bulk_हटाओ_event;
	काष्ठा mutex bulk_mutex;

	काष्ठा service_stats_काष्ठा अणु
		पूर्णांक quota_stalls;
		पूर्णांक slot_stalls;
		पूर्णांक bulk_stalls;
		पूर्णांक error_count;
		पूर्णांक ctrl_tx_count;
		पूर्णांक ctrl_rx_count;
		पूर्णांक bulk_tx_count;
		पूर्णांक bulk_rx_count;
		पूर्णांक bulk_पातed_count;
		uपूर्णांक64_t ctrl_tx_bytes;
		uपूर्णांक64_t ctrl_rx_bytes;
		uपूर्णांक64_t bulk_tx_bytes;
		uपूर्णांक64_t bulk_rx_bytes;
	पूर्ण stats;

	पूर्णांक msg_queue_पढ़ो;
	पूर्णांक msg_queue_ग_लिखो;
	काष्ठा completion msg_queue_pop;
	काष्ठा completion msg_queue_push;
	काष्ठा vchiq_header *msg_queue[VCHIQ_MAX_SLOTS];
पूर्ण;

/*
 * The quota inक्रमmation is outside काष्ठा vchiq_service so that it can
 * be अटलally allocated, since क्रम accounting reasons a service's slot
 * usage is carried over between users of the same port number.
 */
काष्ठा vchiq_service_quota अणु
	अचिन्हित लघु slot_quota;
	अचिन्हित लघु slot_use_count;
	अचिन्हित लघु message_quota;
	अचिन्हित लघु message_use_count;
	काष्ठा completion quota_event;
	पूर्णांक previous_tx_index;
पूर्ण;

काष्ठा vchiq_shared_state अणु

	/* A non-zero value here indicates that the content is valid. */
	पूर्णांक initialised;

	/* The first and last (inclusive) slots allocated to the owner. */
	पूर्णांक slot_first;
	पूर्णांक slot_last;

	/* The slot allocated to synchronous messages from the owner. */
	पूर्णांक slot_sync;

	/*
	 * Signalling this event indicates that owner's slot handler thपढ़ो
	 * should run.
	 */
	काष्ठा remote_event trigger;

	/*
	 * Indicates the byte position within the stream where the next message
	 * will be written. The least signअगरicant bits are an index पूर्णांकo the
	 * slot. The next bits are the index of the slot in slot_queue.
	 */
	पूर्णांक tx_pos;

	/* This event should be संकेतled when a slot is recycled. */
	काष्ठा remote_event recycle;

	/* The slot_queue index where the next recycled slot will be written. */
	पूर्णांक slot_queue_recycle;

	/* This event should be संकेतled when a synchronous message is sent. */
	काष्ठा remote_event sync_trigger;

	/*
	 * This event should be संकेतled when a synchronous message has been
	 * released.
	 */
	काष्ठा remote_event sync_release;

	/* A circular buffer of slot indexes. */
	पूर्णांक slot_queue[VCHIQ_MAX_SLOTS_PER_SIDE];

	/* Debugging state */
	पूर्णांक debug[DEBUG_MAX];
पूर्ण;

काष्ठा vchiq_slot_zero अणु
	पूर्णांक magic;
	लघु version;
	लघु version_min;
	पूर्णांक slot_zero_size;
	पूर्णांक slot_size;
	पूर्णांक max_slots;
	पूर्णांक max_slots_per_side;
	पूर्णांक platक्रमm_data[2];
	काष्ठा vchiq_shared_state master;
	काष्ठा vchiq_shared_state slave;
	काष्ठा vchiq_slot_info slots[VCHIQ_MAX_SLOTS];
पूर्ण;

काष्ठा vchiq_state अणु
	पूर्णांक id;
	पूर्णांक initialised;
	क्रमागत vchiq_connstate conn_state;
	लघु version_common;

	काष्ठा vchiq_shared_state *local;
	काष्ठा vchiq_shared_state *remote;
	काष्ठा vchiq_slot *slot_data;

	अचिन्हित लघु शेष_slot_quota;
	अचिन्हित लघु शेष_message_quota;

	/* Event indicating connect message received */
	काष्ठा completion connect;

	/* Mutex protecting services */
	काष्ठा mutex mutex;
	काष्ठा vchiq_instance **instance;

	/* Processes incoming messages */
	काष्ठा task_काष्ठा *slot_handler_thपढ़ो;

	/* Processes recycled slots */
	काष्ठा task_काष्ठा *recycle_thपढ़ो;

	/* Processes synchronous messages */
	काष्ठा task_काष्ठा *sync_thपढ़ो;

	/* Local implementation of the trigger remote event */
	रुको_queue_head_t trigger_event;

	/* Local implementation of the recycle remote event */
	रुको_queue_head_t recycle_event;

	/* Local implementation of the sync trigger remote event */
	रुको_queue_head_t sync_trigger_event;

	/* Local implementation of the sync release remote event */
	रुको_queue_head_t sync_release_event;

	अक्षर *tx_data;
	अक्षर *rx_data;
	काष्ठा vchiq_slot_info *rx_info;

	काष्ठा mutex slot_mutex;

	काष्ठा mutex recycle_mutex;

	काष्ठा mutex sync_mutex;

	काष्ठा mutex bulk_transfer_mutex;

	/*
	 * Indicates the byte position within the stream from where the next
	 * message will be पढ़ो. The least signअगरicant bits are an index पूर्णांकo
	 * the slot.The next bits are the index of the slot in
	 * remote->slot_queue.
	 */
	पूर्णांक rx_pos;

	/*
	 * A cached copy of local->tx_pos. Only ग_लिखो to local->tx_pos, and पढ़ो
	 * from remote->tx_pos.
	 */
	पूर्णांक local_tx_pos;

	/* The slot_queue index of the slot to become available next. */
	पूर्णांक slot_queue_available;

	/* A flag to indicate अगर any poll has been requested */
	पूर्णांक poll_needed;

	/* Ths index of the previous slot used क्रम data messages. */
	पूर्णांक previous_data_index;

	/* The number of slots occupied by data messages. */
	अचिन्हित लघु data_use_count;

	/* The maximum number of slots to be occupied by data messages. */
	अचिन्हित लघु data_quota;

	/* An array of bit sets indicating which services must be polled. */
	atomic_t poll_services[BITSET_SIZE(VCHIQ_MAX_SERVICES)];

	/* The number of the first unused service */
	पूर्णांक unused_service;

	/* Signalled when a मुक्त slot becomes available. */
	काष्ठा completion slot_available_event;

	काष्ठा completion slot_हटाओ_event;

	/* Signalled when a मुक्त data slot becomes available. */
	काष्ठा completion data_quota_event;

	काष्ठा state_stats_काष्ठा अणु
		पूर्णांक slot_stalls;
		पूर्णांक data_stalls;
		पूर्णांक ctrl_tx_count;
		पूर्णांक ctrl_rx_count;
		पूर्णांक error_count;
	पूर्ण stats;

	काष्ठा vchiq_service __rcu *services[VCHIQ_MAX_SERVICES];
	काष्ठा vchiq_service_quota service_quotas[VCHIQ_MAX_SERVICES];
	काष्ठा vchiq_slot_info slot_info[VCHIQ_MAX_SLOTS];

	काष्ठा opaque_platक्रमm_state *platक्रमm_state;
पूर्ण;

काष्ठा bulk_रुकोer अणु
	काष्ठा vchiq_bulk *bulk;
	काष्ठा completion event;
	पूर्णांक actual;
पूर्ण;

काष्ठा vchiq_config अणु
	अचिन्हित पूर्णांक max_msg_size;
	अचिन्हित पूर्णांक bulk_threshold;	/* The message size above which it
					 * is better to use a bulk transfer
					 * (<= max_msg_size)
					 */
	अचिन्हित पूर्णांक max_outstanding_bulks;
	अचिन्हित पूर्णांक max_services;
	लघु version;      /* The version of VCHIQ */
	लघु version_min;  /* The minimum compatible version of VCHIQ */
पूर्ण;


बाह्य spinlock_t bulk_रुकोer_spinlock;

बाह्य पूर्णांक vchiq_core_log_level;
बाह्य पूर्णांक vchiq_core_msg_log_level;
बाह्य पूर्णांक vchiq_sync_log_level;

बाह्य काष्ठा vchiq_state *vchiq_states[VCHIQ_MAX_STATES];

बाह्य स्थिर अक्षर *
get_conn_state_name(क्रमागत vchiq_connstate conn_state);

बाह्य काष्ठा vchiq_slot_zero *
vchiq_init_slots(व्योम *mem_base, पूर्णांक mem_size);

बाह्य क्रमागत vchiq_status
vchiq_init_state(काष्ठा vchiq_state *state, काष्ठा vchiq_slot_zero *slot_zero);

बाह्य क्रमागत vchiq_status
vchiq_connect_पूर्णांकernal(काष्ठा vchiq_state *state, काष्ठा vchiq_instance *instance);

काष्ठा vchiq_service *
vchiq_add_service_पूर्णांकernal(काष्ठा vchiq_state *state,
			   स्थिर काष्ठा vchiq_service_params_kernel *params,
			   पूर्णांक srvstate, काष्ठा vchiq_instance *instance,
			   vchiq_userdata_term userdata_term);

बाह्य क्रमागत vchiq_status
vchiq_खोलो_service_पूर्णांकernal(काष्ठा vchiq_service *service, पूर्णांक client_id);

बाह्य क्रमागत vchiq_status
vchiq_बंद_service_पूर्णांकernal(काष्ठा vchiq_service *service, पूर्णांक बंद_recvd);

बाह्य व्योम
vchiq_terminate_service_पूर्णांकernal(काष्ठा vchiq_service *service);

बाह्य व्योम
vchiq_मुक्त_service_पूर्णांकernal(काष्ठा vchiq_service *service);

बाह्य क्रमागत vchiq_status
vchiq_shutकरोwn_पूर्णांकernal(काष्ठा vchiq_state *state, काष्ठा vchiq_instance *instance);

बाह्य व्योम
remote_event_pollall(काष्ठा vchiq_state *state);

बाह्य क्रमागत vchiq_status
vchiq_bulk_transfer(अचिन्हित पूर्णांक handle, व्योम *offset, व्योम __user *uoffset,
		    पूर्णांक size, व्योम *userdata, क्रमागत vchiq_bulk_mode mode,
		    क्रमागत vchiq_bulk_dir dir);

बाह्य पूर्णांक
vchiq_dump_state(व्योम *dump_context, काष्ठा vchiq_state *state);

बाह्य पूर्णांक
vchiq_dump_service_state(व्योम *dump_context, काष्ठा vchiq_service *service);

बाह्य व्योम
vchiq_loud_error_header(व्योम);

बाह्य व्योम
vchiq_loud_error_footer(व्योम);

बाह्य व्योम
request_poll(काष्ठा vchiq_state *state, काष्ठा vchiq_service *service,
	     पूर्णांक poll_type);

अटल अंतरभूत काष्ठा vchiq_service *
handle_to_service(अचिन्हित पूर्णांक handle)
अणु
	पूर्णांक idx = handle & (VCHIQ_MAX_SERVICES - 1);
	काष्ठा vchiq_state *state = vchiq_states[(handle / VCHIQ_MAX_SERVICES) &
		(VCHIQ_MAX_STATES - 1)];

	अगर (!state)
		वापस शून्य;
	वापस rcu_dereference(state->services[idx]);
पूर्ण

बाह्य काष्ठा vchiq_service *
find_service_by_handle(अचिन्हित पूर्णांक handle);

बाह्य काष्ठा vchiq_service *
find_service_by_port(काष्ठा vchiq_state *state, पूर्णांक localport);

बाह्य काष्ठा vchiq_service *
find_service_क्रम_instance(काष्ठा vchiq_instance *instance,
	अचिन्हित पूर्णांक handle);

बाह्य काष्ठा vchiq_service *
find_बंदd_service_क्रम_instance(काष्ठा vchiq_instance *instance,
	अचिन्हित पूर्णांक handle);

बाह्य काष्ठा vchiq_service *
__next_service_by_instance(काष्ठा vchiq_state *state,
			   काष्ठा vchiq_instance *instance,
			   पूर्णांक *pidx);

बाह्य काष्ठा vchiq_service *
next_service_by_instance(काष्ठा vchiq_state *state,
			 काष्ठा vchiq_instance *instance,
			 पूर्णांक *pidx);

बाह्य व्योम
lock_service(काष्ठा vchiq_service *service);

बाह्य व्योम
unlock_service(काष्ठा vchiq_service *service);

बाह्य क्रमागत vchiq_status
vchiq_queue_message(अचिन्हित पूर्णांक handle,
		    sमाप_प्रकार (*copy_callback)(व्योम *context, व्योम *dest,
					     माप_प्रकार offset, माप_प्रकार maxsize),
		    व्योम *context,
		    माप_प्रकार size);

/*
 * The following functions are called from vchiq_core, and बाह्यal
 * implementations must be provided.
 */

बाह्य क्रमागत vchiq_status
vchiq_prepare_bulk_data(काष्ठा vchiq_bulk *bulk, व्योम *offset,
			व्योम __user *uoffset, पूर्णांक size, पूर्णांक dir);

बाह्य व्योम
vchiq_complete_bulk(काष्ठा vchiq_bulk *bulk);

बाह्य व्योम
remote_event_संकेत(काष्ठा remote_event *event);

बाह्य पूर्णांक
vchiq_dump(व्योम *dump_context, स्थिर अक्षर *str, पूर्णांक len);

बाह्य पूर्णांक
vchiq_dump_platक्रमm_state(व्योम *dump_context);

बाह्य पूर्णांक
vchiq_dump_platक्रमm_instances(व्योम *dump_context);

बाह्य पूर्णांक
vchiq_dump_platक्रमm_service_state(व्योम *dump_context,
	काष्ठा vchiq_service *service);

बाह्य क्रमागत vchiq_status
vchiq_use_service_पूर्णांकernal(काष्ठा vchiq_service *service);

बाह्य क्रमागत vchiq_status
vchiq_release_service_पूर्णांकernal(काष्ठा vchiq_service *service);

बाह्य व्योम
vchiq_on_remote_use(काष्ठा vchiq_state *state);

बाह्य व्योम
vchiq_on_remote_release(काष्ठा vchiq_state *state);

बाह्य क्रमागत vchiq_status
vchiq_platक्रमm_init_state(काष्ठा vchiq_state *state);

बाह्य क्रमागत vchiq_status
vchiq_check_service(काष्ठा vchiq_service *service);

बाह्य व्योम
vchiq_on_remote_use_active(काष्ठा vchiq_state *state);

बाह्य क्रमागत vchiq_status
vchiq_send_remote_use(काष्ठा vchiq_state *state);

बाह्य क्रमागत vchiq_status
vchiq_send_remote_use_active(काष्ठा vchiq_state *state);

बाह्य व्योम
vchiq_platक्रमm_conn_state_changed(काष्ठा vchiq_state *state,
				  क्रमागत vchiq_connstate oldstate,
				  क्रमागत vchiq_connstate newstate);

बाह्य व्योम
vchiq_set_conn_state(काष्ठा vchiq_state *state, क्रमागत vchiq_connstate newstate);

बाह्य व्योम
vchiq_log_dump_mem(स्थिर अक्षर *label, uपूर्णांक32_t addr, स्थिर व्योम *व्योमMem,
	माप_प्रकार numBytes);

बाह्य क्रमागत vchiq_status vchiq_हटाओ_service(अचिन्हित पूर्णांक service);

बाह्य पूर्णांक vchiq_get_client_id(अचिन्हित पूर्णांक service);

बाह्य व्योम vchiq_get_config(काष्ठा vchiq_config *config);

बाह्य क्रमागत vchiq_status
vchiq_set_service_option(अचिन्हित पूर्णांक service, क्रमागत vchiq_service_option option,
			 पूर्णांक value);

#पूर्ण_अगर
