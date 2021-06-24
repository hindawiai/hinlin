<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
  drbd_पूर्णांक.h

  This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

  Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
  Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
  Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


*/

#अगर_अघोषित _DRBD_INT_H
#घोषणा _DRBD_INT_H

#समावेश <crypto/hash.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/tcp.h>
#समावेश <linux/mutex.h>
#समावेश <linux/major.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/genhd.h>
#समावेश <linux/idr.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <net/tcp.h>
#समावेश <linux/lru_cache.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/drbd_genl_api.h>
#समावेश <linux/drbd.h>
#समावेश "drbd_strings.h"
#समावेश "drbd_state.h"
#समावेश "drbd_protocol.h"

#अगर_घोषित __CHECKER__
# define __रक्षित_by(x)       __attribute__((require_context(x,1,999,"rdwr")))
# define __रक्षित_पढ़ो_by(x)  __attribute__((require_context(x,1,999,"read")))
# define __रक्षित_ग_लिखो_by(x) __attribute__((require_context(x,1,999,"write")))
#अन्यथा
# define __रक्षित_by(x)
# define __रक्षित_पढ़ो_by(x)
# define __रक्षित_ग_लिखो_by(x)
#पूर्ण_अगर

/* shared module parameters, defined in drbd_मुख्य.c */
#अगर_घोषित CONFIG_DRBD_FAULT_INJECTION
बाह्य पूर्णांक drbd_enable_faults;
बाह्य पूर्णांक drbd_fault_rate;
#पूर्ण_अगर

बाह्य अचिन्हित पूर्णांक drbd_minor_count;
बाह्य अक्षर drbd_usermode_helper[];
बाह्य पूर्णांक drbd_proc_details;


/* This is used to stop/restart our thपढ़ोs.
 * Cannot use संक_इति nor SIGKILL, since these
 * are sent out by init on runlevel changes
 * I choose SIGHUP क्रम now.
 */
#घोषणा DRBD_SIGKILL SIGHUP

#घोषणा ID_IN_SYNC      (4711ULL)
#घोषणा ID_OUT_OF_SYNC  (4712ULL)
#घोषणा ID_SYNCER (-1ULL)

#घोषणा UUID_NEW_BM_OFFSET ((u64)0x0001000000000000ULL)

काष्ठा drbd_device;
काष्ठा drbd_connection;

#घोषणा __drbd_prपूर्णांकk_device(level, device, fmt, args...) \
	dev_prपूर्णांकk(level, disk_to_dev((device)->vdisk), fmt, ## args)
#घोषणा __drbd_prपूर्णांकk_peer_device(level, peer_device, fmt, args...) \
	dev_prपूर्णांकk(level, disk_to_dev((peer_device)->device->vdisk), fmt, ## args)
#घोषणा __drbd_prपूर्णांकk_resource(level, resource, fmt, args...) \
	prपूर्णांकk(level "drbd %s: " fmt, (resource)->name, ## args)
#घोषणा __drbd_prपूर्णांकk_connection(level, connection, fmt, args...) \
	prपूर्णांकk(level "drbd %s: " fmt, (connection)->resource->name, ## args)

व्योम drbd_prपूर्णांकk_with_wrong_object_type(व्योम);

#घोषणा __drbd_prपूर्णांकk_अगर_same_type(obj, type, func, level, fmt, args...) \
	(__builtin_types_compatible_p(typeof(obj), type) || \
	 __builtin_types_compatible_p(typeof(obj), स्थिर type)), \
	func(level, (स्थिर type)(obj), fmt, ## args)

#घोषणा drbd_prपूर्णांकk(level, obj, fmt, args...) \
	__builtin_choose_expr( \
	  __drbd_prपूर्णांकk_अगर_same_type(obj, काष्ठा drbd_device *, \
			     __drbd_prपूर्णांकk_device, level, fmt, ## args), \
	  __builtin_choose_expr( \
	    __drbd_prपूर्णांकk_अगर_same_type(obj, काष्ठा drbd_resource *, \
			       __drbd_prपूर्णांकk_resource, level, fmt, ## args), \
	    __builtin_choose_expr( \
	      __drbd_prपूर्णांकk_अगर_same_type(obj, काष्ठा drbd_connection *, \
				 __drbd_prपूर्णांकk_connection, level, fmt, ## args), \
	      __builtin_choose_expr( \
		__drbd_prपूर्णांकk_अगर_same_type(obj, काष्ठा drbd_peer_device *, \
				 __drbd_prपूर्णांकk_peer_device, level, fmt, ## args), \
		drbd_prपूर्णांकk_with_wrong_object_type()))))

#घोषणा drbd_dbg(obj, fmt, args...) \
	drbd_prपूर्णांकk(KERN_DEBUG, obj, fmt, ## args)
#घोषणा drbd_alert(obj, fmt, args...) \
	drbd_prपूर्णांकk(KERN_ALERT, obj, fmt, ## args)
#घोषणा drbd_err(obj, fmt, args...) \
	drbd_prपूर्णांकk(KERN_ERR, obj, fmt, ## args)
#घोषणा drbd_warn(obj, fmt, args...) \
	drbd_prपूर्णांकk(KERN_WARNING, obj, fmt, ## args)
#घोषणा drbd_info(obj, fmt, args...) \
	drbd_prपूर्णांकk(KERN_INFO, obj, fmt, ## args)
#घोषणा drbd_emerg(obj, fmt, args...) \
	drbd_prपूर्णांकk(KERN_EMERG, obj, fmt, ## args)

#घोषणा dynamic_drbd_dbg(device, fmt, args...) \
	dynamic_dev_dbg(disk_to_dev(device->vdisk), fmt, ## args)

#घोषणा D_ASSERT(device, exp)	करो अणु \
	अगर (!(exp)) \
		drbd_err(device, "ASSERT( " #exp " ) in %s:%d\n", __खाता__, __LINE__); \
	पूर्ण जबतक (0)

/**
 * expect  -  Make an निश्चितion
 *
 * Unlike the निश्चित macro, this macro वापसs a boolean result.
 */
#घोषणा expect(exp) (अणु								\
		bool _bool = (exp);						\
		अगर (!_bool)							\
			drbd_err(device, "ASSERTION %s FAILED in %s\n",		\
			        #exp, __func__);				\
		_bool;								\
		पूर्ण)

/* Defines to control fault insertion */
क्रमागत अणु
	DRBD_FAULT_MD_WR = 0,	/* meta data ग_लिखो */
	DRBD_FAULT_MD_RD = 1,	/*           पढ़ो  */
	DRBD_FAULT_RS_WR = 2,	/* resync          */
	DRBD_FAULT_RS_RD = 3,
	DRBD_FAULT_DT_WR = 4,	/* data            */
	DRBD_FAULT_DT_RD = 5,
	DRBD_FAULT_DT_RA = 6,	/* data पढ़ो ahead */
	DRBD_FAULT_BM_ALLOC = 7,	/* biपंचांगap allocation */
	DRBD_FAULT_AL_EE = 8,	/* alloc ee */
	DRBD_FAULT_RECEIVE = 9, /* Changes some bytes upon receiving a [rs]data block */

	DRBD_FAULT_MAX,
पूर्ण;

बाह्य अचिन्हित पूर्णांक
_drbd_insert_fault(काष्ठा drbd_device *device, अचिन्हित पूर्णांक type);

अटल अंतरभूत पूर्णांक
drbd_insert_fault(काष्ठा drbd_device *device, अचिन्हित पूर्णांक type) अणु
#अगर_घोषित CONFIG_DRBD_FAULT_INJECTION
	वापस drbd_fault_rate &&
		(drbd_enable_faults & (1<<type)) &&
		_drbd_insert_fault(device, type);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* पूर्णांकeger भागision, round _UP_ to the next पूर्णांकeger */
#घोषणा भाग_उच्चमान(A, B) ((A)/(B) + ((A)%(B) ? 1 : 0))
/* usual पूर्णांकeger भागision */
#घोषणा भाग_न्यूनमान(A, B) ((A)/(B))

बाह्य काष्ठा ratelimit_state drbd_ratelimit_state;
बाह्य काष्ठा idr drbd_devices; /* RCU, updates: genl_lock() */
बाह्य काष्ठा list_head drbd_resources; /* RCU, updates: genl_lock() */

बाह्य स्थिर अक्षर *cmdname(क्रमागत drbd_packet cmd);

/* क्रम sending/receiving the biपंचांगap,
 * possibly in some encoding scheme */
काष्ठा bm_xfer_ctx अणु
	/* "const"
	 * stores total bits and दीर्घ words
	 * of the biपंचांगap, so we करोn't need to
	 * call the accessor functions over and again. */
	अचिन्हित दीर्घ bm_bits;
	अचिन्हित दीर्घ bm_words;
	/* during xfer, current position within the biपंचांगap */
	अचिन्हित दीर्घ bit_offset;
	अचिन्हित दीर्घ word_offset;

	/* statistics; index: (h->command == P_BITMAP) */
	अचिन्हित packets[2];
	अचिन्हित bytes[2];
पूर्ण;

बाह्य व्योम INFO_bm_xfer_stats(काष्ठा drbd_device *device,
		स्थिर अक्षर *direction, काष्ठा bm_xfer_ctx *c);

अटल अंतरभूत व्योम bm_xfer_ctx_bit_to_word_offset(काष्ठा bm_xfer_ctx *c)
अणु
	/* word_offset counts "native long words" (32 or 64 bit),
	 * aligned at 64 bit.
	 * Encoded packet may end at an unaligned bit offset.
	 * In हाल a fallback clear text packet is transmitted in
	 * between, we adjust this offset back to the last 64bit
	 * aligned "native long word", which makes coding and decoding
	 * the plain text biपंचांगap much more convenient.  */
#अगर BITS_PER_LONG == 64
	c->word_offset = c->bit_offset >> 6;
#या_अगर BITS_PER_LONG == 32
	c->word_offset = c->bit_offset >> 5;
	c->word_offset &= ~(1UL);
#अन्यथा
# error "unsupported BITS_PER_LONG"
#पूर्ण_अगर
पूर्ण

बाह्य अचिन्हित पूर्णांक drbd_header_size(काष्ठा drbd_connection *connection);

/**********************************************************************/
क्रमागत drbd_thपढ़ो_state अणु
	NONE,
	RUNNING,
	EXITING,
	RESTARTING
पूर्ण;

काष्ठा drbd_thपढ़ो अणु
	spinlock_t t_lock;
	काष्ठा task_काष्ठा *task;
	काष्ठा completion stop;
	क्रमागत drbd_thपढ़ो_state t_state;
	पूर्णांक (*function) (काष्ठा drbd_thपढ़ो *);
	काष्ठा drbd_resource *resource;
	काष्ठा drbd_connection *connection;
	पूर्णांक reset_cpu_mask;
	स्थिर अक्षर *name;
पूर्ण;

अटल अंतरभूत क्रमागत drbd_thपढ़ो_state get_t_state(काष्ठा drbd_thपढ़ो *thi)
अणु
	/* THINK testing the t_state seems to be uncritical in all हालs
	 * (but thपढ़ो_अणुstart,stopपूर्ण), so we can पढ़ो it *without* the lock.
	 *	--lge */

	smp_rmb();
	वापस thi->t_state;
पूर्ण

काष्ठा drbd_work अणु
	काष्ठा list_head list;
	पूर्णांक (*cb)(काष्ठा drbd_work *, पूर्णांक cancel);
पूर्ण;

काष्ठा drbd_device_work अणु
	काष्ठा drbd_work w;
	काष्ठा drbd_device *device;
पूर्ण;

#समावेश "drbd_interval.h"

बाह्य पूर्णांक drbd_रुको_misc(काष्ठा drbd_device *, काष्ठा drbd_पूर्णांकerval *);

बाह्य व्योम lock_all_resources(व्योम);
बाह्य व्योम unlock_all_resources(व्योम);

काष्ठा drbd_request अणु
	काष्ठा drbd_work w;
	काष्ठा drbd_device *device;

	/* अगर local IO is not allowed, will be शून्य.
	 * अगर local IO _is_ allowed, holds the locally submitted bio clone,
	 * or, after local IO completion, the ERR_PTR(error).
	 * see drbd_request_endio(). */
	काष्ठा bio *निजी_bio;

	काष्ठा drbd_पूर्णांकerval i;

	/* epoch: used to check on "completion" whether this req was in
	 * the current epoch, and we thereक्रमe have to बंद it,
	 * causing a p_barrier packet to be send, starting a new epoch.
	 *
	 * This corresponds to "barrier" in काष्ठा p_barrier[_ack],
	 * and to "barrier_nr" in काष्ठा drbd_epoch (and various
	 * comments/function parameters/local variable names).
	 */
	अचिन्हित पूर्णांक epoch;

	काष्ठा list_head tl_requests; /* ring list in the transfer log */
	काष्ठा bio *master_bio;       /* master bio poपूर्णांकer */

	/* see काष्ठा drbd_device */
	काष्ठा list_head req_pending_master_completion;
	काष्ठा list_head req_pending_local;

	/* क्रम generic IO accounting */
	अचिन्हित दीर्घ start_jअगर;

	/* क्रम DRBD पूर्णांकernal statistics */

	/* Minimal set of समय stamps to determine अगर we रुको क्रम activity log
	 * transactions, local disk or peer.  32 bit "jiffies" are good enough,
	 * we करोn't expect a DRBD request to be stalled क्रम several month.
	 */

	/* beक्रमe actual request processing */
	अचिन्हित दीर्घ in_actlog_jअगर;

	/* local disk */
	अचिन्हित दीर्घ pre_submit_jअगर;

	/* per connection */
	अचिन्हित दीर्घ pre_send_jअगर;
	अचिन्हित दीर्घ acked_jअगर;
	अचिन्हित दीर्घ net_करोne_jअगर;

	/* Possibly even more detail to track each phase:
	 *  master_completion_jअगर
	 *      how दीर्घ did it take to complete the master bio
	 *      (application visible latency)
	 *  allocated_jअगर
	 *      how दीर्घ the master bio was blocked until we finally allocated
	 *      a tracking काष्ठा
	 *  in_actlog_jअगर
	 *      how दीर्घ did we रुको क्रम activity log transactions
	 *
	 *  net_queued_jअगर
	 *      when did we finally queue it क्रम sending
	 *  pre_send_jअगर
	 *      when did we start sending it
	 *  post_send_jअगर
	 *      how दीर्घ did we block in the network stack trying to send it
	 *  acked_jअगर
	 *      when did we receive (or fake, in protocol A) a remote ACK
	 *  net_करोne_jअगर
	 *      when did we receive final acknowledgement (P_BARRIER_ACK),
	 *      or decide, e.g. on connection loss, that we करो no दीर्घer expect
	 *      anything from this peer क्रम this request.
	 *
	 *  pre_submit_jअगर
	 *  post_sub_jअगर
	 *      when did we start submiting to the lower level device,
	 *      and how दीर्घ did we block in that submit function
	 *  local_completion_jअगर
	 *      how दीर्घ did it take the lower level device to complete this request
	 */


	/* once it hits 0, we may complete the master_bio */
	atomic_t completion_ref;
	/* once it hits 0, we may destroy this drbd_request object */
	काष्ठा kref kref;

	अचिन्हित rq_state; /* see comments above _req_mod() */
पूर्ण;

काष्ठा drbd_epoch अणु
	काष्ठा drbd_connection *connection;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक barrier_nr;
	atomic_t epoch_size; /* increased on every request added. */
	atomic_t active;     /* increased on every req. added, and dec on every finished. */
	अचिन्हित दीर्घ flags;
पूर्ण;

/* Prototype declaration of function defined in drbd_receiver.c */
पूर्णांक drbdd_init(काष्ठा drbd_thपढ़ो *);
पूर्णांक drbd_asender(काष्ठा drbd_thपढ़ो *);

/* drbd_epoch flag bits */
क्रमागत अणु
	DE_HAVE_BARRIER_NUMBER,
पूर्ण;

क्रमागत epoch_event अणु
	EV_PUT,
	EV_GOT_BARRIER_NR,
	EV_BECAME_LAST,
	EV_CLEANUP = 32, /* used as flag */
पूर्ण;

काष्ठा digest_info अणु
	पूर्णांक digest_size;
	व्योम *digest;
पूर्ण;

काष्ठा drbd_peer_request अणु
	काष्ठा drbd_work w;
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_epoch *epoch; /* क्रम ग_लिखोs */
	काष्ठा page *pages;
	atomic_t pending_bios;
	काष्ठा drbd_पूर्णांकerval i;
	/* see comments on ee flag bits below */
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ submit_jअगर;
	जोड़ अणु
		u64 block_id;
		काष्ठा digest_info *digest;
	पूर्ण;
पूर्ण;

/* ee flag bits.
 * While corresponding bios are in flight, the only modअगरication will be
 * set_bit WAS_ERROR, which has to be atomic.
 * If no bios are in flight yet, or all have been completed,
 * non-atomic modअगरication to ee->flags is ok.
 */
क्रमागत अणु
	__EE_CALL_AL_COMPLETE_IO,
	__EE_MAY_SET_IN_SYNC,

	/* is this a TRIM aka REQ_OP_DISCARD? */
	__EE_TRIM,
	/* explicit zero-out requested, or
	 * our lower level cannot handle trim,
	 * and we want to fall back to zeroout instead */
	__EE_ZEROOUT,

	/* In हाल a barrier failed,
	 * we need to resubmit without the barrier flag. */
	__EE_RESUBMITTED,

	/* we may have several bios per peer request.
	 * अगर any of those fail, we set this flag atomically
	 * from the endio callback */
	__EE_WAS_ERROR,

	/* This ee has a poपूर्णांकer to a digest instead of a block id */
	__EE_HAS_DIGEST,

	/* Conflicting local requests need to be restarted after this request */
	__EE_RESTART_REQUESTS,

	/* The peer wants a ग_लिखो ACK क्रम this (wire proto C) */
	__EE_SEND_WRITE_ACK,

	/* Is set when net_conf had two_primaries set जबतक creating this peer_req */
	__EE_IN_INTERVAL_TREE,

	/* क्रम debugfs: */
	/* has this been submitted, or करोes it still रुको क्रम something अन्यथा? */
	__EE_SUBMITTED,

	/* this is/was a ग_लिखो request */
	__EE_WRITE,

	/* this is/was a ग_लिखो same request */
	__EE_WRITE_SAME,

	/* this originates from application on peer
	 * (not some resync or verअगरy or other DRBD पूर्णांकernal request) */
	__EE_APPLICATION,

	/* If it contains only 0 bytes, send back P_RS_DEALLOCATED */
	__EE_RS_THIN_REQ,
पूर्ण;
#घोषणा EE_CALL_AL_COMPLETE_IO (1<<__EE_CALL_AL_COMPLETE_IO)
#घोषणा EE_MAY_SET_IN_SYNC     (1<<__EE_MAY_SET_IN_SYNC)
#घोषणा EE_TRIM                (1<<__EE_TRIM)
#घोषणा EE_ZEROOUT             (1<<__EE_ZEROOUT)
#घोषणा EE_RESUBMITTED         (1<<__EE_RESUBMITTED)
#घोषणा EE_WAS_ERROR           (1<<__EE_WAS_ERROR)
#घोषणा EE_HAS_DIGEST          (1<<__EE_HAS_DIGEST)
#घोषणा EE_RESTART_REQUESTS	(1<<__EE_RESTART_REQUESTS)
#घोषणा EE_SEND_WRITE_ACK	(1<<__EE_SEND_WRITE_ACK)
#घोषणा EE_IN_INTERVAL_TREE	(1<<__EE_IN_INTERVAL_TREE)
#घोषणा EE_SUBMITTED		(1<<__EE_SUBMITTED)
#घोषणा EE_WRITE		(1<<__EE_WRITE)
#घोषणा EE_WRITE_SAME		(1<<__EE_WRITE_SAME)
#घोषणा EE_APPLICATION		(1<<__EE_APPLICATION)
#घोषणा EE_RS_THIN_REQ		(1<<__EE_RS_THIN_REQ)

/* flag bits per device */
क्रमागत अणु
	UNPLUG_REMOTE,		/* sending a "UnplugRemote" could help */
	MD_सूचीTY,		/* current uuids and flags not yet on disk */
	USE_DEGR_WFC_T,		/* degr-wfc-समयout instead of wfc-समयout. */
	CL_ST_CHG_SUCCESS,
	CL_ST_CHG_FAIL,
	CRASHED_PRIMARY,	/* This node was a crashed primary.
				 * Gets cleared when the state.conn
				 * goes पूर्णांकo C_CONNECTED state. */
	CONSIDER_RESYNC,

	MD_NO_FUA,		/* Users wants us to not use FUA/FLUSH on meta data dev */

	BITMAP_IO,		/* suspend application io;
				   once no more io in flight, start biपंचांगap io */
	BITMAP_IO_QUEUED,       /* Started biपंचांगap IO */
	WAS_IO_ERROR,		/* Local disk failed, वापसed IO error */
	WAS_READ_ERROR,		/* Local disk READ failed (set additionally to the above) */
	FORCE_DETACH,		/* Force-detach from local disk, पातing any pending local IO */
	RESYNC_AFTER_NEG,       /* Resync after online grow after the attach&negotiate finished. */
	RESIZE_PENDING,		/* Size change detected locally, रुकोing क्रम the response from
				 * the peer, अगर it changed there as well. */
	NEW_CUR_UUID,		/* Create new current UUID when thawing IO */
	AL_SUSPENDED,		/* Activity logging is currently suspended. */
	AHEAD_TO_SYNC_SOURCE,   /* Ahead -> SyncSource queued */
	B_RS_H_DONE,		/* Beक्रमe resync handler करोne (alपढ़ोy executed) */
	DISCARD_MY_DATA,	/* discard_my_data flag per volume */
	READ_BALANCE_RR,

	FLUSH_PENDING,		/* अगर set, device->flush_jअगर is when we submitted that flush
				 * from drbd_flush_after_epoch() */

	/* cleared only after backing device related काष्ठाures have been destroyed. */
	GOING_DISKLESS,		/* Disk is being detached, because of io-error, or admin request. */

	/* to be used in drbd_device_post_work() */
	GO_DISKLESS,		/* tell worker to schedule cleanup beक्रमe detach */
	DESTROY_DISK,		/* tell worker to बंद backing devices and destroy related काष्ठाures. */
	MD_SYNC,		/* tell worker to call drbd_md_sync() */
	RS_START,		/* tell worker to start resync/OV */
	RS_PROGRESS,		/* tell worker that resync made signअगरicant progress */
	RS_DONE,		/* tell worker that resync is करोne */
पूर्ण;

काष्ठा drbd_biपंचांगap; /* opaque क्रम drbd_device */

/* definition of bits in bm_flags to be used in drbd_bm_lock
 * and drbd_biपंचांगap_io and मित्रs. */
क्रमागत bm_flag अणु
	/* currently locked क्रम bulk operation */
	BM_LOCKED_MASK = 0xf,

	/* in detail, that is: */
	BM_DONT_CLEAR = 0x1,
	BM_DONT_SET   = 0x2,
	BM_DONT_TEST  = 0x4,

	/* so we can mark it locked क्रम bulk operation,
	 * and still allow all non-bulk operations */
	BM_IS_LOCKED  = 0x8,

	/* (test bit, count bit) allowed (common हाल) */
	BM_LOCKED_TEST_ALLOWED = BM_DONT_CLEAR | BM_DONT_SET | BM_IS_LOCKED,

	/* testing bits, as well as setting new bits allowed, but clearing bits
	 * would be unexpected.  Used during biपंचांगap receive.  Setting new bits
	 * requires sending of "out-of-sync" inक्रमmation, though. */
	BM_LOCKED_SET_ALLOWED = BM_DONT_CLEAR | BM_IS_LOCKED,

	/* क्रम drbd_bm_ग_लिखो_copy_pages, everything is allowed,
	 * only concurrent bulk operations are locked out. */
	BM_LOCKED_CHANGE_ALLOWED = BM_IS_LOCKED,
पूर्ण;

काष्ठा drbd_work_queue अणु
	काष्ठा list_head q;
	spinlock_t q_lock;  /* to protect the list. */
	रुको_queue_head_t q_रुको;
पूर्ण;

काष्ठा drbd_socket अणु
	काष्ठा mutex mutex;
	काष्ठा socket    *socket;
	/* this way we get our
	 * send/receive buffers off the stack */
	व्योम *sbuf;
	व्योम *rbuf;
पूर्ण;

काष्ठा drbd_md अणु
	u64 md_offset;		/* sector offset to 'super' block */

	u64 la_size_sect;	/* last agreed size, unit sectors */
	spinlock_t uuid_lock;
	u64 uuid[UI_SIZE];
	u64 device_uuid;
	u32 flags;
	u32 md_size_sect;

	s32 al_offset;	/* चिन्हित relative sector offset to activity log */
	s32 bm_offset;	/* चिन्हित relative sector offset to biपंचांगap */

	/* cached value of bdev->disk_conf->meta_dev_idx (see below) */
	s32 meta_dev_idx;

	/* see al_tr_number_to_on_disk_sector() */
	u32 al_stripes;
	u32 al_stripe_size_4k;
	u32 al_size_4k; /* cached product of the above */
पूर्ण;

काष्ठा drbd_backing_dev अणु
	काष्ठा block_device *backing_bdev;
	काष्ठा block_device *md_bdev;
	काष्ठा drbd_md md;
	काष्ठा disk_conf *disk_conf; /* RCU, क्रम updates: resource->conf_update */
	sector_t known_size; /* last known size of that backing device */
पूर्ण;

काष्ठा drbd_md_io अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ start_jअगर;	/* last call to drbd_md_get_buffer */
	अचिन्हित दीर्घ submit_jअगर;	/* last _drbd_md_sync_page_io() submit */
	स्थिर अक्षर *current_use;
	atomic_t in_use;
	अचिन्हित पूर्णांक करोne;
	पूर्णांक error;
पूर्ण;

काष्ठा bm_io_work अणु
	काष्ठा drbd_work w;
	अक्षर *why;
	क्रमागत bm_flag flags;
	पूर्णांक (*io_fn)(काष्ठा drbd_device *device);
	व्योम (*करोne)(काष्ठा drbd_device *device, पूर्णांक rv);
पूर्ण;

काष्ठा fअगरo_buffer अणु
	अचिन्हित पूर्णांक head_index;
	अचिन्हित पूर्णांक size;
	पूर्णांक total; /* sum of all values */
	पूर्णांक values[];
पूर्ण;
बाह्य काष्ठा fअगरo_buffer *fअगरo_alloc(अचिन्हित पूर्णांक fअगरo_size);

/* flag bits per connection */
क्रमागत अणु
	NET_CONGESTED,		/* The data socket is congested */
	RESOLVE_CONFLICTS,	/* Set on one node, cleared on the peer! */
	SEND_PING,
	GOT_PING_ACK,		/* set when we receive a ping_ack packet, ping_रुको माला_लो woken */
	CONN_WD_ST_CHG_REQ,	/* A cluster wide state change on the connection is active */
	CONN_WD_ST_CHG_OKAY,
	CONN_WD_ST_CHG_FAIL,
	CONN_DRY_RUN,		/* Expect disconnect after resync handshake. */
	CREATE_BARRIER,		/* next P_DATA is preceded by a P_BARRIER */
	STATE_SENT,		/* Do not change state/UUIDs जबतक this is set */
	CALLBACK_PENDING,	/* Whether we have a call_usermodehelper(, UMH_WAIT_PROC)
				 * pending, from drbd worker context.
				 * If set, bdi_ग_लिखो_congested() वापसs true,
				 * so shrink_page_list() would not recurse पूर्णांकo,
				 * and potentially deadlock on, this drbd worker.
				 */
	DISCONNECT_SENT,

	DEVICE_WORK_PENDING,	/* tell worker that some device has pending work */
पूर्ण;

क्रमागत which_state अणु NOW, OLD = NOW, NEW पूर्ण;

काष्ठा drbd_resource अणु
	अक्षर *name;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_res;
	काष्ठा dentry *debugfs_res_volumes;
	काष्ठा dentry *debugfs_res_connections;
	काष्ठा dentry *debugfs_res_in_flight_summary;
#पूर्ण_अगर
	काष्ठा kref kref;
	काष्ठा idr devices;		/* volume number to device mapping */
	काष्ठा list_head connections;
	काष्ठा list_head resources;
	काष्ठा res_opts res_opts;
	काष्ठा mutex conf_update;	/* mutex क्रम पढ़ोy-copy-update of net_conf and disk_conf */
	काष्ठा mutex adm_mutex;		/* mutex to serialize administrative requests */
	spinlock_t req_lock;

	अचिन्हित susp:1;		/* IO suspended by user */
	अचिन्हित susp_nod:1;		/* IO suspended because no data */
	अचिन्हित susp_fen:1;		/* IO suspended because fence peer handler runs */

	क्रमागत ग_लिखो_ordering_e ग_लिखो_ordering;

	cpumask_var_t cpu_mask;
पूर्ण;

काष्ठा drbd_thपढ़ो_timing_details
अणु
	अचिन्हित दीर्घ start_jअगर;
	व्योम *cb_addr;
	स्थिर अक्षर *caller_fn;
	अचिन्हित पूर्णांक line;
	अचिन्हित पूर्णांक cb_nr;
पूर्ण;

काष्ठा drbd_connection अणु
	काष्ठा list_head connections;
	काष्ठा drbd_resource *resource;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_conn;
	काष्ठा dentry *debugfs_conn_callback_history;
	काष्ठा dentry *debugfs_conn_oldest_requests;
#पूर्ण_अगर
	काष्ठा kref kref;
	काष्ठा idr peer_devices;	/* volume number to peer device mapping */
	क्रमागत drbd_conns cstate;		/* Only C_STANDALONE to C_WF_REPORT_PARAMS */
	काष्ठा mutex cstate_mutex;	/* Protects graceful disconnects */
	अचिन्हित पूर्णांक connect_cnt;	/* Inc each समय a connection is established */

	अचिन्हित दीर्घ flags;
	काष्ठा net_conf *net_conf;	/* content रक्षित by rcu */
	रुको_queue_head_t ping_रुको;	/* Woken upon reception of a ping, and a state change */

	काष्ठा sockaddr_storage my_addr;
	पूर्णांक my_addr_len;
	काष्ठा sockaddr_storage peer_addr;
	पूर्णांक peer_addr_len;

	काष्ठा drbd_socket data;	/* data/barrier/cstate/parameter packets */
	काष्ठा drbd_socket meta;	/* ping/ack (metadata) packets */
	पूर्णांक agreed_pro_version;		/* actually used protocol version */
	u32 agreed_features;
	अचिन्हित दीर्घ last_received;	/* in jअगरfies, either socket */
	अचिन्हित पूर्णांक ko_count;

	काष्ठा list_head transfer_log;	/* all requests not yet fully processed */

	काष्ठा crypto_shash *cram_hmac_tfm;
	काष्ठा crypto_shash *पूर्णांकegrity_tfm;  /* checksums we compute, updates रक्षित by connection->data->mutex */
	काष्ठा crypto_shash *peer_पूर्णांकegrity_tfm;  /* checksums we verअगरy, only accessed from receiver thपढ़ो  */
	काष्ठा crypto_shash *csums_tfm;
	काष्ठा crypto_shash *verअगरy_tfm;
	व्योम *पूर्णांक_dig_in;
	व्योम *पूर्णांक_dig_vv;

	/* receiver side */
	काष्ठा drbd_epoch *current_epoch;
	spinlock_t epoch_lock;
	अचिन्हित पूर्णांक epochs;
	atomic_t current_tle_nr;	/* transfer log epoch number */
	अचिन्हित current_tle_ग_लिखोs;	/* ग_लिखोs seen within this tl epoch */

	अचिन्हित दीर्घ last_reconnect_jअगर;
	/* empty member on older kernels without blk_start_plug() */
	काष्ठा blk_plug receiver_plug;
	काष्ठा drbd_thपढ़ो receiver;
	काष्ठा drbd_thपढ़ो worker;
	काष्ठा drbd_thपढ़ो ack_receiver;
	काष्ठा workqueue_काष्ठा *ack_sender;

	/* cached poपूर्णांकers,
	 * so we can look up the oldest pending requests more quickly.
	 * रक्षित by resource->req_lock */
	काष्ठा drbd_request *req_next; /* DRBD 9: toकरो.req_next */
	काष्ठा drbd_request *req_ack_pending;
	काष्ठा drbd_request *req_not_net_करोne;

	/* sender side */
	काष्ठा drbd_work_queue sender_work;

#घोषणा DRBD_THREAD_DETAILS_HIST	16
	अचिन्हित पूर्णांक w_cb_nr; /* keeps counting up */
	अचिन्हित पूर्णांक r_cb_nr; /* keeps counting up */
	काष्ठा drbd_thपढ़ो_timing_details w_timing_details[DRBD_THREAD_DETAILS_HIST];
	काष्ठा drbd_thपढ़ो_timing_details r_timing_details[DRBD_THREAD_DETAILS_HIST];

	काष्ठा अणु
		अचिन्हित दीर्घ last_sent_barrier_jअगर;

		/* whether this sender thपढ़ो
		 * has processed a single ग_लिखो yet. */
		bool seen_any_ग_लिखो_yet;

		/* Which barrier number to send with the next P_BARRIER */
		पूर्णांक current_epoch_nr;

		/* how many ग_लिखो requests have been sent
		 * with req->epoch == current_epoch_nr.
		 * If none, no P_BARRIER will be sent. */
		अचिन्हित current_epoch_ग_लिखोs;
	पूर्ण send;
पूर्ण;

अटल अंतरभूत bool has_net_conf(काष्ठा drbd_connection *connection)
अणु
	bool has_net_conf;

	rcu_पढ़ो_lock();
	has_net_conf = rcu_dereference(connection->net_conf);
	rcu_पढ़ो_unlock();

	वापस has_net_conf;
पूर्ण

व्योम __update_timing_details(
		काष्ठा drbd_thपढ़ो_timing_details *tdp,
		अचिन्हित पूर्णांक *cb_nr,
		व्योम *cb,
		स्थिर अक्षर *fn, स्थिर अचिन्हित पूर्णांक line);

#घोषणा update_worker_timing_details(c, cb) \
	__update_timing_details(c->w_timing_details, &c->w_cb_nr, cb, __func__ , __LINE__ )
#घोषणा update_receiver_timing_details(c, cb) \
	__update_timing_details(c->r_timing_details, &c->r_cb_nr, cb, __func__ , __LINE__ )

काष्ठा submit_worker अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा worker;

	/* रक्षित by ..->resource->req_lock */
	काष्ठा list_head ग_लिखोs;
पूर्ण;

काष्ठा drbd_peer_device अणु
	काष्ठा list_head peer_devices;
	काष्ठा drbd_device *device;
	काष्ठा drbd_connection *connection;
	काष्ठा work_काष्ठा send_acks_work;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_peer_dev;
#पूर्ण_अगर
पूर्ण;

काष्ठा drbd_device अणु
	काष्ठा drbd_resource *resource;
	काष्ठा list_head peer_devices;
	काष्ठा list_head pending_biपंचांगap_io;

	अचिन्हित दीर्घ flush_jअगर;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_minor;
	काष्ठा dentry *debugfs_vol;
	काष्ठा dentry *debugfs_vol_oldest_requests;
	काष्ठा dentry *debugfs_vol_act_log_extents;
	काष्ठा dentry *debugfs_vol_resync_extents;
	काष्ठा dentry *debugfs_vol_data_gen_id;
	काष्ठा dentry *debugfs_vol_ed_gen_id;
#पूर्ण_अगर

	अचिन्हित पूर्णांक vnr;	/* volume number within the connection */
	अचिन्हित पूर्णांक minor;	/* device minor number */

	काष्ठा kref kref;

	/* things that are stored as / पढ़ो from meta data on disk */
	अचिन्हित दीर्घ flags;

	/* configured by drbdsetup */
	काष्ठा drbd_backing_dev *ldev __रक्षित_by(local);

	sector_t p_size;     /* partner's disk size */
	काष्ठा request_queue *rq_queue;
	काष्ठा gendisk	    *vdisk;

	अचिन्हित दीर्घ last_reattach_jअगर;
	काष्ठा drbd_work resync_work;
	काष्ठा drbd_work unplug_work;
	काष्ठा समयr_list resync_समयr;
	काष्ठा समयr_list md_sync_समयr;
	काष्ठा समयr_list start_resync_समयr;
	काष्ठा समयr_list request_समयr;

	/* Used after attach जबतक negotiating new disk state. */
	जोड़ drbd_state new_state_पंचांगp;

	जोड़ drbd_dev_state state;
	रुको_queue_head_t misc_रुको;
	रुको_queue_head_t state_रुको;  /* upon each state change. */
	अचिन्हित पूर्णांक send_cnt;
	अचिन्हित पूर्णांक recv_cnt;
	अचिन्हित पूर्णांक पढ़ो_cnt;
	अचिन्हित पूर्णांक writ_cnt;
	अचिन्हित पूर्णांक al_writ_cnt;
	अचिन्हित पूर्णांक bm_writ_cnt;
	atomic_t ap_bio_cnt;	 /* Requests we need to complete */
	atomic_t ap_actlog_cnt;  /* Requests रुकोing क्रम activity log */
	atomic_t ap_pending_cnt; /* AP data packets on the wire, ack expected */
	atomic_t rs_pending_cnt; /* RS request/data packets on the wire */
	atomic_t unacked_cnt;	 /* Need to send replies क्रम */
	atomic_t local_cnt;	 /* Waiting क्रम local completion */
	atomic_t suspend_cnt;

	/* Interval tree of pending local requests */
	काष्ठा rb_root पढ़ो_requests;
	काष्ठा rb_root ग_लिखो_requests;

	/* क्रम statistics and समयouts */
	/* [0] पढ़ो, [1] ग_लिखो */
	काष्ठा list_head pending_master_completion[2];
	काष्ठा list_head pending_completion[2];

	/* use checksums क्रम *this* resync */
	bool use_csums;
	/* blocks to resync in this run [unit BM_BLOCK_SIZE] */
	अचिन्हित दीर्घ rs_total;
	/* number of resync blocks that failed in this run */
	अचिन्हित दीर्घ rs_failed;
	/* Syncer's start समय [unit jअगरfies] */
	अचिन्हित दीर्घ rs_start;
	/* cumulated समय in PausedSyncX state [unit jअगरfies] */
	अचिन्हित दीर्घ rs_छोड़ोd;
	/* skipped because csum was equal [unit BM_BLOCK_SIZE] */
	अचिन्हित दीर्घ rs_same_csum;
#घोषणा DRBD_SYNC_MARKS 8
#घोषणा DRBD_SYNC_MARK_STEP (3*HZ)
	/* block not up-to-date at mark [unit BM_BLOCK_SIZE] */
	अचिन्हित दीर्घ rs_mark_left[DRBD_SYNC_MARKS];
	/* marks's समय [unit jअगरfies] */
	अचिन्हित दीर्घ rs_mark_समय[DRBD_SYNC_MARKS];
	/* current index पूर्णांकo rs_mark_अणुleft,समयपूर्ण */
	पूर्णांक rs_last_mark;
	अचिन्हित दीर्घ rs_last_bcast; /* [unit jअगरfies] */

	/* where करोes the admin want us to start? (sector) */
	sector_t ov_start_sector;
	sector_t ov_stop_sector;
	/* where are we now? (sector) */
	sector_t ov_position;
	/* Start sector of out of sync range (to merge prपूर्णांकk reporting). */
	sector_t ov_last_oos_start;
	/* size of out-of-sync range in sectors. */
	sector_t ov_last_oos_size;
	अचिन्हित दीर्घ ov_left; /* in bits */

	काष्ठा drbd_biपंचांगap *biपंचांगap;
	अचिन्हित दीर्घ bm_resync_fo; /* bit offset क्रम drbd_bm_find_next */

	/* Used to track operations of resync... */
	काष्ठा lru_cache *resync;
	/* Number of locked elements in resync LRU */
	अचिन्हित पूर्णांक resync_locked;
	/* resync extent number रुकोing क्रम application requests */
	अचिन्हित पूर्णांक resync_wenr;

	पूर्णांक खोलो_cnt;
	u64 *p_uuid;

	काष्ठा list_head active_ee; /* IO in progress (P_DATA माला_लो written to disk) */
	काष्ठा list_head sync_ee;   /* IO in progress (P_RS_DATA_REPLY माला_लो written to disk) */
	काष्ठा list_head करोne_ee;   /* need to send P_WRITE_ACK */
	काष्ठा list_head पढ़ो_ee;   /* [RS]P_DATA_REQUEST being पढ़ो */
	काष्ठा list_head net_ee;    /* zero-copy network send in progress */

	पूर्णांक next_barrier_nr;
	काष्ठा list_head resync_पढ़ोs;
	atomic_t pp_in_use;		/* allocated from page pool */
	atomic_t pp_in_use_by_net;	/* sendpage()d, still referenced by tcp */
	रुको_queue_head_t ee_रुको;
	काष्ठा drbd_md_io md_io;
	spinlock_t al_lock;
	रुको_queue_head_t al_रुको;
	काष्ठा lru_cache *act_log;	/* activity log */
	अचिन्हित पूर्णांक al_tr_number;
	पूर्णांक al_tr_cycle;
	रुको_queue_head_t seq_रुको;
	atomic_t packet_seq;
	अचिन्हित पूर्णांक peer_seq;
	spinlock_t peer_seq_lock;
	अचिन्हित दीर्घ comm_bm_set; /* communicated number of set bits. */
	काष्ठा bm_io_work bm_io_work;
	u64 ed_uuid; /* UUID of the exposed data */
	काष्ठा mutex own_state_mutex;
	काष्ठा mutex *state_mutex; /* either own_state_mutex or first_peer_device(device)->connection->cstate_mutex */
	अक्षर congestion_reason;  /* Why we where congested... */
	atomic_t rs_sect_in; /* क्रम incoming resync data rate, SyncTarget */
	atomic_t rs_sect_ev; /* क्रम submitted resync data rate, both */
	पूर्णांक rs_last_sect_ev; /* counter to compare with */
	पूर्णांक rs_last_events;  /* counter of पढ़ो or ग_लिखो "events" (unit sectors)
			      * on the lower level device when we last looked. */
	पूर्णांक c_sync_rate; /* current resync rate after syncer throttle magic */
	काष्ठा fअगरo_buffer *rs_plan_s; /* correction values of resync planer (RCU, connection->conn_update) */
	पूर्णांक rs_in_flight; /* resync sectors in flight (to proxy, in proxy and from proxy) */
	atomic_t ap_in_flight; /* App sectors in flight (रुकोing क्रम ack) */
	अचिन्हित पूर्णांक peer_max_bio_size;
	अचिन्हित पूर्णांक local_max_bio_size;

	/* any requests that would block in drbd_make_request()
	 * are deferred to this single-thपढ़ोed work queue */
	काष्ठा submit_worker submit;
पूर्ण;

काष्ठा drbd_bm_aio_ctx अणु
	काष्ठा drbd_device *device;
	काष्ठा list_head list; /* on device->pending_biपंचांगap_io */;
	अचिन्हित दीर्घ start_jअगर;
	atomic_t in_flight;
	अचिन्हित पूर्णांक करोne;
	अचिन्हित flags;
#घोषणा BM_AIO_COPY_PAGES	1
#घोषणा BM_AIO_WRITE_HINTED	2
#घोषणा BM_AIO_WRITE_ALL_PAGES	4
#घोषणा BM_AIO_READ		8
	पूर्णांक error;
	काष्ठा kref kref;
पूर्ण;

काष्ठा drbd_config_context अणु
	/* asचिन्हित from drbd_genlmsghdr */
	अचिन्हित पूर्णांक minor;
	/* asचिन्हित from request attributes, अगर present */
	अचिन्हित पूर्णांक volume;
#घोषणा VOLUME_UNSPECIFIED		(-1U)
	/* poपूर्णांकer पूर्णांकo the request skb,
	 * limited lअगरeसमय! */
	अक्षर *resource_name;
	काष्ठा nlattr *my_addr;
	काष्ठा nlattr *peer_addr;

	/* reply buffer */
	काष्ठा sk_buff *reply_skb;
	/* poपूर्णांकer पूर्णांकo reply buffer */
	काष्ठा drbd_genlmsghdr *reply_dh;
	/* resolved from attributes, अगर possible */
	काष्ठा drbd_device *device;
	काष्ठा drbd_resource *resource;
	काष्ठा drbd_connection *connection;
पूर्ण;

अटल अंतरभूत काष्ठा drbd_device *minor_to_device(अचिन्हित पूर्णांक minor)
अणु
	वापस (काष्ठा drbd_device *)idr_find(&drbd_devices, minor);
पूर्ण

अटल अंतरभूत काष्ठा drbd_peer_device *first_peer_device(काष्ठा drbd_device *device)
अणु
	वापस list_first_entry_or_null(&device->peer_devices, काष्ठा drbd_peer_device, peer_devices);
पूर्ण

अटल अंतरभूत काष्ठा drbd_peer_device *
conn_peer_device(काष्ठा drbd_connection *connection, पूर्णांक volume_number)
अणु
	वापस idr_find(&connection->peer_devices, volume_number);
पूर्ण

#घोषणा क्रम_each_resource(resource, _resources) \
	list_क्रम_each_entry(resource, _resources, resources)

#घोषणा क्रम_each_resource_rcu(resource, _resources) \
	list_क्रम_each_entry_rcu(resource, _resources, resources)

#घोषणा क्रम_each_resource_safe(resource, पंचांगp, _resources) \
	list_क्रम_each_entry_safe(resource, पंचांगp, _resources, resources)

#घोषणा क्रम_each_connection(connection, resource) \
	list_क्रम_each_entry(connection, &resource->connections, connections)

#घोषणा क्रम_each_connection_rcu(connection, resource) \
	list_क्रम_each_entry_rcu(connection, &resource->connections, connections)

#घोषणा क्रम_each_connection_safe(connection, पंचांगp, resource) \
	list_क्रम_each_entry_safe(connection, पंचांगp, &resource->connections, connections)

#घोषणा क्रम_each_peer_device(peer_device, device) \
	list_क्रम_each_entry(peer_device, &device->peer_devices, peer_devices)

#घोषणा क्रम_each_peer_device_rcu(peer_device, device) \
	list_क्रम_each_entry_rcu(peer_device, &device->peer_devices, peer_devices)

#घोषणा क्रम_each_peer_device_safe(peer_device, पंचांगp, device) \
	list_क्रम_each_entry_safe(peer_device, पंचांगp, &device->peer_devices, peer_devices)

अटल अंतरभूत अचिन्हित पूर्णांक device_to_minor(काष्ठा drbd_device *device)
अणु
	वापस device->minor;
पूर्ण

/*
 * function declarations
 *************************/

/* drbd_मुख्य.c */

क्रमागत dds_flags अणु
	DDSF_FORCED    = 1,
	DDSF_NO_RESYNC = 2, /* Do not run a resync क्रम the new space */
पूर्ण;

बाह्य व्योम drbd_init_set_शेषs(काष्ठा drbd_device *device);
बाह्य पूर्णांक  drbd_thपढ़ो_start(काष्ठा drbd_thपढ़ो *thi);
बाह्य व्योम _drbd_thपढ़ो_stop(काष्ठा drbd_thपढ़ो *thi, पूर्णांक restart, पूर्णांक रुको);
#अगर_घोषित CONFIG_SMP
बाह्य व्योम drbd_thपढ़ो_current_set_cpu(काष्ठा drbd_thपढ़ो *thi);
#अन्यथा
#घोषणा drbd_thपढ़ो_current_set_cpu(A) (अणुपूर्ण)
#पूर्ण_अगर
बाह्य व्योम tl_release(काष्ठा drbd_connection *, अचिन्हित पूर्णांक barrier_nr,
		       अचिन्हित पूर्णांक set_size);
बाह्य व्योम tl_clear(काष्ठा drbd_connection *);
बाह्य व्योम drbd_मुक्त_sock(काष्ठा drbd_connection *connection);
बाह्य पूर्णांक drbd_send(काष्ठा drbd_connection *connection, काष्ठा socket *sock,
		     व्योम *buf, माप_प्रकार size, अचिन्हित msg_flags);
बाह्य पूर्णांक drbd_send_all(काष्ठा drbd_connection *, काष्ठा socket *, व्योम *, माप_प्रकार,
			 अचिन्हित);

बाह्य पूर्णांक __drbd_send_protocol(काष्ठा drbd_connection *connection, क्रमागत drbd_packet cmd);
बाह्य पूर्णांक drbd_send_protocol(काष्ठा drbd_connection *connection);
बाह्य पूर्णांक drbd_send_uuids(काष्ठा drbd_peer_device *);
बाह्य पूर्णांक drbd_send_uuids_skip_initial_sync(काष्ठा drbd_peer_device *);
बाह्य व्योम drbd_gen_and_send_sync_uuid(काष्ठा drbd_peer_device *);
बाह्य पूर्णांक drbd_send_sizes(काष्ठा drbd_peer_device *, पूर्णांक trigger_reply, क्रमागत dds_flags flags);
बाह्य पूर्णांक drbd_send_state(काष्ठा drbd_peer_device *, जोड़ drbd_state s);
बाह्य पूर्णांक drbd_send_current_state(काष्ठा drbd_peer_device *);
बाह्य पूर्णांक drbd_send_sync_param(काष्ठा drbd_peer_device *);
बाह्य व्योम drbd_send_b_ack(काष्ठा drbd_connection *connection, u32 barrier_nr,
			    u32 set_size);
बाह्य पूर्णांक drbd_send_ack(काष्ठा drbd_peer_device *, क्रमागत drbd_packet,
			 काष्ठा drbd_peer_request *);
बाह्य व्योम drbd_send_ack_rp(काष्ठा drbd_peer_device *, क्रमागत drbd_packet,
			     काष्ठा p_block_req *rp);
बाह्य व्योम drbd_send_ack_dp(काष्ठा drbd_peer_device *, क्रमागत drbd_packet,
			     काष्ठा p_data *dp, पूर्णांक data_size);
बाह्य पूर्णांक drbd_send_ack_ex(काष्ठा drbd_peer_device *, क्रमागत drbd_packet,
			    sector_t sector, पूर्णांक blksize, u64 block_id);
बाह्य पूर्णांक drbd_send_out_of_sync(काष्ठा drbd_peer_device *, काष्ठा drbd_request *);
बाह्य पूर्णांक drbd_send_block(काष्ठा drbd_peer_device *, क्रमागत drbd_packet,
			   काष्ठा drbd_peer_request *);
बाह्य पूर्णांक drbd_send_dblock(काष्ठा drbd_peer_device *, काष्ठा drbd_request *req);
बाह्य पूर्णांक drbd_send_drequest(काष्ठा drbd_peer_device *, पूर्णांक cmd,
			      sector_t sector, पूर्णांक size, u64 block_id);
बाह्य पूर्णांक drbd_send_drequest_csum(काष्ठा drbd_peer_device *, sector_t sector,
				   पूर्णांक size, व्योम *digest, पूर्णांक digest_size,
				   क्रमागत drbd_packet cmd);
बाह्य पूर्णांक drbd_send_ov_request(काष्ठा drbd_peer_device *, sector_t sector, पूर्णांक size);

बाह्य पूर्णांक drbd_send_biपंचांगap(काष्ठा drbd_device *device);
बाह्य व्योम drbd_send_sr_reply(काष्ठा drbd_peer_device *, क्रमागत drbd_state_rv retcode);
बाह्य व्योम conn_send_sr_reply(काष्ठा drbd_connection *connection, क्रमागत drbd_state_rv retcode);
बाह्य पूर्णांक drbd_send_rs_deallocated(काष्ठा drbd_peer_device *, काष्ठा drbd_peer_request *);
बाह्य व्योम drbd_backing_dev_मुक्त(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *ldev);
बाह्य व्योम drbd_device_cleanup(काष्ठा drbd_device *device);
बाह्य व्योम drbd_prपूर्णांक_uuids(काष्ठा drbd_device *device, स्थिर अक्षर *text);
बाह्य व्योम drbd_queue_unplug(काष्ठा drbd_device *device);

बाह्य व्योम conn_md_sync(काष्ठा drbd_connection *connection);
बाह्य व्योम drbd_md_ग_लिखो(काष्ठा drbd_device *device, व्योम *buffer);
बाह्य व्योम drbd_md_sync(काष्ठा drbd_device *device);
बाह्य पूर्णांक  drbd_md_पढ़ो(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *bdev);
बाह्य व्योम drbd_uuid_set(काष्ठा drbd_device *device, पूर्णांक idx, u64 val) __must_hold(local);
बाह्य व्योम _drbd_uuid_set(काष्ठा drbd_device *device, पूर्णांक idx, u64 val) __must_hold(local);
बाह्य व्योम drbd_uuid_new_current(काष्ठा drbd_device *device) __must_hold(local);
बाह्य व्योम drbd_uuid_set_bm(काष्ठा drbd_device *device, u64 val) __must_hold(local);
बाह्य व्योम drbd_uuid_move_history(काष्ठा drbd_device *device) __must_hold(local);
बाह्य व्योम __drbd_uuid_set(काष्ठा drbd_device *device, पूर्णांक idx, u64 val) __must_hold(local);
बाह्य व्योम drbd_md_set_flag(काष्ठा drbd_device *device, पूर्णांक flags) __must_hold(local);
बाह्य व्योम drbd_md_clear_flag(काष्ठा drbd_device *device, पूर्णांक flags)__must_hold(local);
बाह्य पूर्णांक drbd_md_test_flag(काष्ठा drbd_backing_dev *, पूर्णांक);
बाह्य व्योम drbd_md_mark_dirty(काष्ठा drbd_device *device);
बाह्य व्योम drbd_queue_biपंचांगap_io(काष्ठा drbd_device *device,
				 पूर्णांक (*io_fn)(काष्ठा drbd_device *),
				 व्योम (*करोne)(काष्ठा drbd_device *, पूर्णांक),
				 अक्षर *why, क्रमागत bm_flag flags);
बाह्य पूर्णांक drbd_biपंचांगap_io(काष्ठा drbd_device *device,
		पूर्णांक (*io_fn)(काष्ठा drbd_device *),
		अक्षर *why, क्रमागत bm_flag flags);
बाह्य पूर्णांक drbd_biपंचांगap_io_from_worker(काष्ठा drbd_device *device,
		पूर्णांक (*io_fn)(काष्ठा drbd_device *),
		अक्षर *why, क्रमागत bm_flag flags);
बाह्य पूर्णांक drbd_bmio_set_n_ग_लिखो(काष्ठा drbd_device *device) __must_hold(local);
बाह्य पूर्णांक drbd_bmio_clear_n_ग_लिखो(काष्ठा drbd_device *device) __must_hold(local);

/* Meta data layout
 *
 * We currently have two possible layouts.
 * Offsets in (512 byte) sectors.
 * बाह्यal:
 *   |----------- md_size_sect ------------------|
 *   [ 4k superblock ][ activity log ][  Biपंचांगap  ]
 *   | al_offset == 8 |
 *   | bm_offset = al_offset + X      |
 *  ==> biपंचांगap sectors = md_size_sect - bm_offset
 *
 *  Variants:
 *     old, indexed fixed size meta data:
 *
 * पूर्णांकernal:
 *            |----------- md_size_sect ------------------|
 * [data.....][  Biपंचांगap  ][ activity log ][ 4k superblock ][padding*]
 *                        | al_offset < 0 |
 *            | bm_offset = al_offset - Y |
 *  ==> biपंचांगap sectors = Y = al_offset - bm_offset
 *
 *  [padding*] are zero or up to 7 unused 512 Byte sectors to the
 *  end of the device, so that the [4k superblock] will be 4k aligned.
 *
 *  The activity log consists of 4k transaction blocks,
 *  which are written in a ring-buffer, or striped ring-buffer like fashion,
 *  which are writtensize used to be fixed 32kB,
 *  but is about to become configurable.
 */

/* Our old fixed size meta data layout
 * allows up to about 3.8TB, so अगर you want more,
 * you need to use the "flexible" meta data क्रमmat. */
#घोषणा MD_128MB_SECT (128LLU << 11)  /* 128 MB, unit sectors */
#घोषणा MD_4kB_SECT	 8
#घोषणा MD_32kB_SECT	64

/* One activity log extent represents 4M of storage */
#घोषणा AL_EXTENT_SHIFT 22
#घोषणा AL_EXTENT_SIZE (1<<AL_EXTENT_SHIFT)

/* We could make these currently hardcoded स्थिरants configurable
 * variables at create-md समय (or even re-configurable at runसमय?).
 * Which will require some more changes to the DRBD "super block"
 * and attach code.
 *
 * updates per transaction:
 *   This many changes to the active set can be logged with one transaction.
 *   This number is arbitrary.
 * context per transaction:
 *   This many context extent numbers are logged with each transaction.
 *   This number is resulting from the transaction block size (4k), the layout
 *   of the transaction header, and the number of updates per transaction.
 *   See drbd_actlog.c:काष्ठा al_transaction_on_disk
 * */
#घोषणा AL_UPDATES_PER_TRANSACTION	 64	// arbitrary
#घोषणा AL_CONTEXT_PER_TRANSACTION	919	// (4096 - 36 - 6*64)/4

#अगर BITS_PER_LONG == 32
#घोषणा LN2_BPL 5
#घोषणा cpu_to_lel(A) cpu_to_le32(A)
#घोषणा lel_to_cpu(A) le32_to_cpu(A)
#या_अगर BITS_PER_LONG == 64
#घोषणा LN2_BPL 6
#घोषणा cpu_to_lel(A) cpu_to_le64(A)
#घोषणा lel_to_cpu(A) le64_to_cpu(A)
#अन्यथा
#त्रुटि "LN2 of BITS_PER_LONG unknown!"
#पूर्ण_अगर

/* resync biपंचांगap */
/* 16MB sized 'bitmap extent' to track syncer usage */
काष्ठा bm_extent अणु
	पूर्णांक rs_left; /* number of bits set (out of sync) in this extent. */
	पूर्णांक rs_failed; /* number of failed resync requests in this extent. */
	अचिन्हित दीर्घ flags;
	काष्ठा lc_element lce;
पूर्ण;

#घोषणा BME_NO_WRITES  0  /* bm_extent.flags: no more requests on this one! */
#घोषणा BME_LOCKED     1  /* bm_extent.flags: syncer active on this one. */
#घोषणा BME_PRIORITY   2  /* finish resync IO on this extent ASAP! App IO रुकोing! */

/* drbd_biपंचांगap.c */
/*
 * We need to store one bit क्रम a block.
 * Example: 1GB disk @ 4096 byte blocks ==> we need 32 KB biपंचांगap.
 * Bit 0 ==> local node thinks this block is binary identical on both nodes
 * Bit 1 ==> local node thinks this block needs to be synced.
 */

#घोषणा SLEEP_TIME (HZ/10)

/* We करो biपंचांगap IO in units of 4k blocks.
 * We also still have a hardcoded 4k per bit relation. */
#घोषणा BM_BLOCK_SHIFT	12			 /* 4k per bit */
#घोषणा BM_BLOCK_SIZE	 (1<<BM_BLOCK_SHIFT)
/* mostly arbitrarily set the represented size of one biपंचांगap extent,
 * aka resync extent, to 16 MiB (which is also 512 Byte worth of biपंचांगap
 * at 4k per bit resolution) */
#घोषणा BM_EXT_SHIFT	 24	/* 16 MiB per resync extent */
#घोषणा BM_EXT_SIZE	 (1<<BM_EXT_SHIFT)

#अगर (BM_EXT_SHIFT != 24) || (BM_BLOCK_SHIFT != 12)
#त्रुटि "HAVE YOU FIXED drbdmeta AS WELL??"
#पूर्ण_अगर

/* thus many _storage_ sectors are described by one bit */
#घोषणा BM_SECT_TO_BIT(x)   ((x)>>(BM_BLOCK_SHIFT-9))
#घोषणा BM_BIT_TO_SECT(x)   ((sector_t)(x)<<(BM_BLOCK_SHIFT-9))
#घोषणा BM_SECT_PER_BIT     BM_BIT_TO_SECT(1)

/* bit to represented kilo byte conversion */
#घोषणा Bit2KB(bits) ((bits)<<(BM_BLOCK_SHIFT-10))

/* in which _biपंचांगap_ extent (resp. sector) the bit क्रम a certain
 * _storage_ sector is located in */
#घोषणा BM_SECT_TO_EXT(x)   ((x)>>(BM_EXT_SHIFT-9))
#घोषणा BM_BIT_TO_EXT(x)    ((x) >> (BM_EXT_SHIFT - BM_BLOCK_SHIFT))

/* first storage sector a biपंचांगap extent corresponds to */
#घोषणा BM_EXT_TO_SECT(x)   ((sector_t)(x) << (BM_EXT_SHIFT-9))
/* how much _storage_ sectors we have per biपंचांगap extent */
#घोषणा BM_SECT_PER_EXT     BM_EXT_TO_SECT(1)
/* how many bits are covered by one biपंचांगap extent (resync extent) */
#घोषणा BM_BITS_PER_EXT     (1UL << (BM_EXT_SHIFT - BM_BLOCK_SHIFT))

#घोषणा BM_BLOCKS_PER_BM_EXT_MASK  (BM_BITS_PER_EXT - 1)


/* in one sector of the biपंचांगap, we have this many activity_log extents. */
#घोषणा AL_EXT_PER_BM_SECT  (1 << (BM_EXT_SHIFT - AL_EXTENT_SHIFT))

/* the extent in "PER_EXTENT" below is an activity log extent
 * we need that many (दीर्घ words/bytes) to store the biपंचांगap
 *		     of one AL_EXTENT_SIZE chunk of storage.
 * we can store the biपंचांगap क्रम that many AL_EXTENTS within
 * one sector of the _on_disk_ biपंचांगap:
 * bit	 0	  bit 37   bit 38	     bit (512*8)-1
 *	     ...|........|........|.. // ..|........|
 * sect. 0	 `296	  `304			   ^(512*8*8)-1
 *
#घोषणा BM_WORDS_PER_EXT    ( (AL_EXT_SIZE/BM_BLOCK_SIZE) / BITS_PER_LONG )
#घोषणा BM_BYTES_PER_EXT    ( (AL_EXT_SIZE/BM_BLOCK_SIZE) / 8 )  // 128
#घोषणा BM_EXT_PER_SECT	    ( 512 / BM_BYTES_PER_EXTENT )	 //   4
 */

#घोषणा DRBD_MAX_SECTORS_32 (0xffffffffLU)
/* we have a certain meta data variant that has a fixed on-disk size of 128
 * MiB, of which 4k are our "superblock", and 32k are the fixed size activity
 * log, leaving this many sectors क्रम the biपंचांगap.
 */

#घोषणा DRBD_MAX_SECTORS_FIXED_BM \
	  ((MD_128MB_SECT - MD_32kB_SECT - MD_4kB_SECT) * (1LL<<(BM_EXT_SHIFT-9)))
#घोषणा DRBD_MAX_SECTORS      DRBD_MAX_SECTORS_FIXED_BM
/* 16 TB in units of sectors */
#अगर BITS_PER_LONG == 32
/* adjust by one page worth of biपंचांगap,
 * so we won't wrap around in drbd_bm_find_next_bit.
 * you should use 64bit OS क्रम that much storage, anyways. */
#घोषणा DRBD_MAX_SECTORS_FLEX BM_BIT_TO_SECT(0xffff7fff)
#अन्यथा
/* we allow up to 1 PiB now on 64bit architecture with "flexible" meta data */
#घोषणा DRBD_MAX_SECTORS_FLEX (1UL << 51)
/* corresponds to (1UL << 38) bits right now. */
#पूर्ण_अगर

/* Estimate max bio size as 256 * PAGE_SIZE,
 * so क्रम typical PAGE_SIZE of 4k, that is (1<<20) Byte.
 * Since we may live in a mixed-platक्रमm cluster,
 * we limit us to a platक्रमm agnostic स्थिरant here क्रम now.
 * A followup commit may allow even bigger BIO sizes,
 * once we thought that through. */
#घोषणा DRBD_MAX_BIO_SIZE (1U << 20)
#अगर DRBD_MAX_BIO_SIZE > (BIO_MAX_VECS << PAGE_SHIFT)
#त्रुटि Architecture not supported: DRBD_MAX_BIO_SIZE > BIO_MAX_SIZE
#पूर्ण_अगर
#घोषणा DRBD_MAX_BIO_SIZE_SAFE (1U << 12)       /* Works always = 4k */

#घोषणा DRBD_MAX_SIZE_H80_PACKET (1U << 15) /* Header 80 only allows packets up to 32KiB data */
#घोषणा DRBD_MAX_BIO_SIZE_P95    (1U << 17) /* Protocol 95 to 99 allows bios up to 128KiB */

/* For now, करोn't allow more than half of what we can "activate" in one
 * activity log transaction to be discarded in one go. We may need to rework
 * drbd_al_begin_io() to allow क्रम even larger discard ranges */
#घोषणा DRBD_MAX_BATCH_BIO_SIZE	 (AL_UPDATES_PER_TRANSACTION/2*AL_EXTENT_SIZE)
#घोषणा DRBD_MAX_BBIO_SECTORS    (DRBD_MAX_BATCH_BIO_SIZE >> 9)

बाह्य पूर्णांक  drbd_bm_init(काष्ठा drbd_device *device);
बाह्य पूर्णांक  drbd_bm_resize(काष्ठा drbd_device *device, sector_t sectors, पूर्णांक set_new_bits);
बाह्य व्योम drbd_bm_cleanup(काष्ठा drbd_device *device);
बाह्य व्योम drbd_bm_set_all(काष्ठा drbd_device *device);
बाह्य व्योम drbd_bm_clear_all(काष्ठा drbd_device *device);
/* set/clear/test only a few bits at a समय */
बाह्य पूर्णांक  drbd_bm_set_bits(
		काष्ठा drbd_device *device, अचिन्हित दीर्घ s, अचिन्हित दीर्घ e);
बाह्य पूर्णांक  drbd_bm_clear_bits(
		काष्ठा drbd_device *device, अचिन्हित दीर्घ s, अचिन्हित दीर्घ e);
बाह्य पूर्णांक drbd_bm_count_bits(
	काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ s, स्थिर अचिन्हित दीर्घ e);
/* bm_set_bits variant क्रम use जबतक holding drbd_bm_lock,
 * may process the whole biपंचांगap in one go */
बाह्य व्योम _drbd_bm_set_bits(काष्ठा drbd_device *device,
		स्थिर अचिन्हित दीर्घ s, स्थिर अचिन्हित दीर्घ e);
बाह्य पूर्णांक  drbd_bm_test_bit(काष्ठा drbd_device *device, अचिन्हित दीर्घ bitnr);
बाह्य पूर्णांक  drbd_bm_e_weight(काष्ठा drbd_device *device, अचिन्हित दीर्घ enr);
बाह्य पूर्णांक  drbd_bm_पढ़ो(काष्ठा drbd_device *device) __must_hold(local);
बाह्य व्योम drbd_bm_mark_क्रम_ग_लिखोout(काष्ठा drbd_device *device, पूर्णांक page_nr);
बाह्य पूर्णांक  drbd_bm_ग_लिखो(काष्ठा drbd_device *device) __must_hold(local);
बाह्य व्योम drbd_bm_reset_al_hपूर्णांकs(काष्ठा drbd_device *device) __must_hold(local);
बाह्य पूर्णांक  drbd_bm_ग_लिखो_hपूर्णांकed(काष्ठा drbd_device *device) __must_hold(local);
बाह्य पूर्णांक  drbd_bm_ग_लिखो_lazy(काष्ठा drbd_device *device, अचिन्हित upper_idx) __must_hold(local);
बाह्य पूर्णांक drbd_bm_ग_लिखो_all(काष्ठा drbd_device *device) __must_hold(local);
बाह्य पूर्णांक  drbd_bm_ग_लिखो_copy_pages(काष्ठा drbd_device *device) __must_hold(local);
बाह्य माप_प्रकार	     drbd_bm_words(काष्ठा drbd_device *device);
बाह्य अचिन्हित दीर्घ drbd_bm_bits(काष्ठा drbd_device *device);
बाह्य sector_t      drbd_bm_capacity(काष्ठा drbd_device *device);

#घोषणा DRBD_END_OF_BITMAP	(~(अचिन्हित दीर्घ)0)
बाह्य अचिन्हित दीर्घ drbd_bm_find_next(काष्ठा drbd_device *device, अचिन्हित दीर्घ bm_fo);
/* bm_find_next variants क्रम use जबतक you hold drbd_bm_lock() */
बाह्य अचिन्हित दीर्घ _drbd_bm_find_next(काष्ठा drbd_device *device, अचिन्हित दीर्घ bm_fo);
बाह्य अचिन्हित दीर्घ _drbd_bm_find_next_zero(काष्ठा drbd_device *device, अचिन्हित दीर्घ bm_fo);
बाह्य अचिन्हित दीर्घ _drbd_bm_total_weight(काष्ठा drbd_device *device);
बाह्य अचिन्हित दीर्घ drbd_bm_total_weight(काष्ठा drbd_device *device);
/* क्रम receive_biपंचांगap */
बाह्य व्योम drbd_bm_merge_lel(काष्ठा drbd_device *device, माप_प्रकार offset,
		माप_प्रकार number, अचिन्हित दीर्घ *buffer);
/* क्रम _drbd_send_biपंचांगap */
बाह्य व्योम drbd_bm_get_lel(काष्ठा drbd_device *device, माप_प्रकार offset,
		माप_प्रकार number, अचिन्हित दीर्घ *buffer);

बाह्य व्योम drbd_bm_lock(काष्ठा drbd_device *device, अक्षर *why, क्रमागत bm_flag flags);
बाह्य व्योम drbd_bm_unlock(काष्ठा drbd_device *device);
/* drbd_मुख्य.c */

बाह्य काष्ठा kmem_cache *drbd_request_cache;
बाह्य काष्ठा kmem_cache *drbd_ee_cache;	/* peer requests */
बाह्य काष्ठा kmem_cache *drbd_bm_ext_cache;	/* biपंचांगap extents */
बाह्य काष्ठा kmem_cache *drbd_al_ext_cache;	/* activity log extents */
बाह्य mempool_t drbd_request_mempool;
बाह्य mempool_t drbd_ee_mempool;

/* drbd's page pool, used to buffer data received from the peer,
 * or data requested by the peer.
 *
 * This करोes not have an emergency reserve.
 *
 * When allocating from this pool, it first takes pages from the pool.
 * Only अगर the pool is depleted will try to allocate from the प्रणाली.
 *
 * The assumption is that pages taken from this pool will be processed,
 * and given back, "quickly", and then can be recycled, so we can aव्योम
 * frequent calls to alloc_page(), and still will be able to make progress even
 * under memory pressure.
 */
बाह्य काष्ठा page *drbd_pp_pool;
बाह्य spinlock_t   drbd_pp_lock;
बाह्य पूर्णांक	    drbd_pp_vacant;
बाह्य रुको_queue_head_t drbd_pp_रुको;

/* We also need a standard (emergency-reserve backed) page pool
 * क्रम meta data IO (activity log, biपंचांगap).
 * We can keep it global, as दीर्घ as it is used as "N pages at a time".
 * 128 should be plenty, currently we probably can get away with as few as 1.
 */
#घोषणा DRBD_MIN_POOL_PAGES	128
बाह्य mempool_t drbd_md_io_page_pool;

/* We also need to make sure we get a bio
 * when we need it क्रम housekeeping purposes */
बाह्य काष्ठा bio_set drbd_md_io_bio_set;

/* And a bio_set क्रम cloning */
बाह्य काष्ठा bio_set drbd_io_bio_set;

बाह्य काष्ठा mutex resources_mutex;

बाह्य पूर्णांक conn_lowest_minor(काष्ठा drbd_connection *connection);
बाह्य क्रमागत drbd_ret_code drbd_create_device(काष्ठा drbd_config_context *adm_ctx, अचिन्हित पूर्णांक minor);
बाह्य व्योम drbd_destroy_device(काष्ठा kref *kref);
बाह्य व्योम drbd_delete_device(काष्ठा drbd_device *device);

बाह्य काष्ठा drbd_resource *drbd_create_resource(स्थिर अक्षर *name);
बाह्य व्योम drbd_मुक्त_resource(काष्ठा drbd_resource *resource);

बाह्य पूर्णांक set_resource_options(काष्ठा drbd_resource *resource, काष्ठा res_opts *res_opts);
बाह्य काष्ठा drbd_connection *conn_create(स्थिर अक्षर *name, काष्ठा res_opts *res_opts);
बाह्य व्योम drbd_destroy_connection(काष्ठा kref *kref);
बाह्य काष्ठा drbd_connection *conn_get_by_addrs(व्योम *my_addr, पूर्णांक my_addr_len,
					    व्योम *peer_addr, पूर्णांक peer_addr_len);
बाह्य काष्ठा drbd_resource *drbd_find_resource(स्थिर अक्षर *name);
बाह्य व्योम drbd_destroy_resource(काष्ठा kref *kref);
बाह्य व्योम conn_मुक्त_crypto(काष्ठा drbd_connection *connection);

/* drbd_req */
बाह्य व्योम करो_submit(काष्ठा work_काष्ठा *ws);
बाह्य व्योम __drbd_make_request(काष्ठा drbd_device *, काष्ठा bio *);
बाह्य blk_qc_t drbd_submit_bio(काष्ठा bio *bio);
बाह्य पूर्णांक drbd_पढ़ो_remote(काष्ठा drbd_device *device, काष्ठा drbd_request *req);
बाह्य पूर्णांक is_valid_ar_handle(काष्ठा drbd_request *, sector_t);


/* drbd_nl.c */

बाह्य काष्ठा mutex notअगरication_mutex;

बाह्य व्योम drbd_suspend_io(काष्ठा drbd_device *device);
बाह्य व्योम drbd_resume_io(काष्ठा drbd_device *device);
बाह्य अक्षर *ppsize(अक्षर *buf, अचिन्हित दीर्घ दीर्घ size);
बाह्य sector_t drbd_new_dev_size(काष्ठा drbd_device *, काष्ठा drbd_backing_dev *, sector_t, पूर्णांक);
क्रमागत determine_dev_size अणु
	DS_ERROR_SHRINK = -3,
	DS_ERROR_SPACE_MD = -2,
	DS_ERROR = -1,
	DS_UNCHANGED = 0,
	DS_SHRUNK = 1,
	DS_GREW = 2,
	DS_GREW_FROM_ZERO = 3,
पूर्ण;
बाह्य क्रमागत determine_dev_size
drbd_determine_dev_size(काष्ठा drbd_device *, क्रमागत dds_flags, काष्ठा resize_parms *) __must_hold(local);
बाह्य व्योम resync_after_online_grow(काष्ठा drbd_device *);
बाह्य व्योम drbd_reconsider_queue_parameters(काष्ठा drbd_device *device,
			काष्ठा drbd_backing_dev *bdev, काष्ठा o_qlim *o);
बाह्य क्रमागत drbd_state_rv drbd_set_role(काष्ठा drbd_device *device,
					क्रमागत drbd_role new_role,
					पूर्णांक क्रमce);
बाह्य bool conn_try_outdate_peer(काष्ठा drbd_connection *connection);
बाह्य व्योम conn_try_outdate_peer_async(काष्ठा drbd_connection *connection);
बाह्य क्रमागत drbd_peer_state conn_khelper(काष्ठा drbd_connection *connection, अक्षर *cmd);
बाह्य पूर्णांक drbd_khelper(काष्ठा drbd_device *device, अक्षर *cmd);

/* drbd_worker.c */
/* bi_end_io handlers */
बाह्य व्योम drbd_md_endio(काष्ठा bio *bio);
बाह्य व्योम drbd_peer_request_endio(काष्ठा bio *bio);
बाह्य व्योम drbd_request_endio(काष्ठा bio *bio);
बाह्य पूर्णांक drbd_worker(काष्ठा drbd_thपढ़ो *thi);
क्रमागत drbd_ret_code drbd_resync_after_valid(काष्ठा drbd_device *device, पूर्णांक o_minor);
व्योम drbd_resync_after_changed(काष्ठा drbd_device *device);
बाह्य व्योम drbd_start_resync(काष्ठा drbd_device *device, क्रमागत drbd_conns side);
बाह्य व्योम resume_next_sg(काष्ठा drbd_device *device);
बाह्य व्योम suspend_other_sg(काष्ठा drbd_device *device);
बाह्य पूर्णांक drbd_resync_finished(काष्ठा drbd_device *device);
/* maybe rather drbd_मुख्य.c ? */
बाह्य व्योम *drbd_md_get_buffer(काष्ठा drbd_device *device, स्थिर अक्षर *पूर्णांकent);
बाह्य व्योम drbd_md_put_buffer(काष्ठा drbd_device *device);
बाह्य पूर्णांक drbd_md_sync_page_io(काष्ठा drbd_device *device,
		काष्ठा drbd_backing_dev *bdev, sector_t sector, पूर्णांक op);
बाह्य व्योम drbd_ov_out_of_sync_found(काष्ठा drbd_device *, sector_t, पूर्णांक);
बाह्य व्योम रुको_until_करोne_or_क्रमce_detached(काष्ठा drbd_device *device,
		काष्ठा drbd_backing_dev *bdev, अचिन्हित पूर्णांक *करोne);
बाह्य व्योम drbd_rs_controller_reset(काष्ठा drbd_device *device);

अटल अंतरभूत व्योम ov_out_of_sync_prपूर्णांक(काष्ठा drbd_device *device)
अणु
	अगर (device->ov_last_oos_size) अणु
		drbd_err(device, "Out of sync: start=%llu, size=%lu (sectors)\n",
		     (अचिन्हित दीर्घ दीर्घ)device->ov_last_oos_start,
		     (अचिन्हित दीर्घ)device->ov_last_oos_size);
	पूर्ण
	device->ov_last_oos_size = 0;
पूर्ण


बाह्य व्योम drbd_csum_bio(काष्ठा crypto_shash *, काष्ठा bio *, व्योम *);
बाह्य व्योम drbd_csum_ee(काष्ठा crypto_shash *, काष्ठा drbd_peer_request *,
			 व्योम *);
/* worker callbacks */
बाह्य पूर्णांक w_e_end_data_req(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_e_end_rsdata_req(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_e_end_csum_rs_req(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_e_end_ov_reply(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_e_end_ov_req(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_ov_finished(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_resync_समयr(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_send_ग_लिखो_hपूर्णांक(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_send_dblock(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_send_पढ़ो_req(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_e_reissue(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_restart_disk_io(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_send_out_of_sync(काष्ठा drbd_work *, पूर्णांक);
बाह्य पूर्णांक w_start_resync(काष्ठा drbd_work *, पूर्णांक);

बाह्य व्योम resync_समयr_fn(काष्ठा समयr_list *t);
बाह्य व्योम start_resync_समयr_fn(काष्ठा समयr_list *t);

बाह्य व्योम drbd_endio_ग_लिखो_sec_final(काष्ठा drbd_peer_request *peer_req);

/* drbd_receiver.c */
बाह्य पूर्णांक drbd_issue_discard_or_zero_out(काष्ठा drbd_device *device,
		sector_t start, अचिन्हित पूर्णांक nr_sectors, पूर्णांक flags);
बाह्य पूर्णांक drbd_receiver(काष्ठा drbd_thपढ़ो *thi);
बाह्य पूर्णांक drbd_ack_receiver(काष्ठा drbd_thपढ़ो *thi);
बाह्य व्योम drbd_send_ping_wf(काष्ठा work_काष्ठा *ws);
बाह्य व्योम drbd_send_acks_wf(काष्ठा work_काष्ठा *ws);
बाह्य bool drbd_rs_c_min_rate_throttle(काष्ठा drbd_device *device);
बाह्य bool drbd_rs_should_slow_करोwn(काष्ठा drbd_device *device, sector_t sector,
		bool throttle_अगर_app_is_रुकोing);
बाह्य पूर्णांक drbd_submit_peer_request(काष्ठा drbd_device *,
				    काष्ठा drbd_peer_request *, स्थिर अचिन्हित,
				    स्थिर अचिन्हित, स्थिर पूर्णांक);
बाह्य पूर्णांक drbd_मुक्त_peer_reqs(काष्ठा drbd_device *, काष्ठा list_head *);
बाह्य काष्ठा drbd_peer_request *drbd_alloc_peer_req(काष्ठा drbd_peer_device *, u64,
						     sector_t, अचिन्हित पूर्णांक,
						     अचिन्हित पूर्णांक,
						     gfp_t) __must_hold(local);
बाह्य व्योम __drbd_मुक्त_peer_req(काष्ठा drbd_device *, काष्ठा drbd_peer_request *,
				 पूर्णांक);
#घोषणा drbd_मुक्त_peer_req(m,e) __drbd_मुक्त_peer_req(m, e, 0)
#घोषणा drbd_मुक्त_net_peer_req(m,e) __drbd_मुक्त_peer_req(m, e, 1)
बाह्य काष्ठा page *drbd_alloc_pages(काष्ठा drbd_peer_device *, अचिन्हित पूर्णांक, bool);
बाह्य व्योम drbd_set_recv_tcq(काष्ठा drbd_device *device, पूर्णांक tcq_enabled);
बाह्य व्योम _drbd_clear_करोne_ee(काष्ठा drbd_device *device, काष्ठा list_head *to_be_मुक्तd);
बाह्य पूर्णांक drbd_connected(काष्ठा drbd_peer_device *);

/* sets the number of 512 byte sectors of our भव device */
व्योम drbd_set_my_capacity(काष्ठा drbd_device *device, sector_t size);

/*
 * used to submit our निजी bio
 */
अटल अंतरभूत व्योम drbd_submit_bio_noacct(काष्ठा drbd_device *device,
					     पूर्णांक fault_type, काष्ठा bio *bio)
अणु
	__release(local);
	अगर (!bio->bi_bdev) अणु
		drbd_err(device, "drbd_submit_bio_noacct: bio->bi_bdev == NULL\n");
		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		वापस;
	पूर्ण

	अगर (drbd_insert_fault(device, fault_type))
		bio_io_error(bio);
	अन्यथा
		submit_bio_noacct(bio);
पूर्ण

व्योम drbd_bump_ग_लिखो_ordering(काष्ठा drbd_resource *resource, काष्ठा drbd_backing_dev *bdev,
			      क्रमागत ग_लिखो_ordering_e wo);

/* drbd_proc.c */
बाह्य काष्ठा proc_dir_entry *drbd_proc;
पूर्णांक drbd_seq_show(काष्ठा seq_file *seq, व्योम *v);

/* drbd_actlog.c */
बाह्य bool drbd_al_begin_io_prepare(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i);
बाह्य पूर्णांक drbd_al_begin_io_nonblock(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i);
बाह्य व्योम drbd_al_begin_io_commit(काष्ठा drbd_device *device);
बाह्य bool drbd_al_begin_io_fastpath(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i);
बाह्य व्योम drbd_al_begin_io(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i);
बाह्य व्योम drbd_al_complete_io(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i);
बाह्य व्योम drbd_rs_complete_io(काष्ठा drbd_device *device, sector_t sector);
बाह्य पूर्णांक drbd_rs_begin_io(काष्ठा drbd_device *device, sector_t sector);
बाह्य पूर्णांक drbd_try_rs_begin_io(काष्ठा drbd_device *device, sector_t sector);
बाह्य व्योम drbd_rs_cancel_all(काष्ठा drbd_device *device);
बाह्य पूर्णांक drbd_rs_del_all(काष्ठा drbd_device *device);
बाह्य व्योम drbd_rs_failed_io(काष्ठा drbd_device *device,
		sector_t sector, पूर्णांक size);
बाह्य व्योम drbd_advance_rs_marks(काष्ठा drbd_device *device, अचिन्हित दीर्घ still_to_go);

क्रमागत update_sync_bits_mode अणु RECORD_RS_FAILED, SET_OUT_OF_SYNC, SET_IN_SYNC पूर्ण;
बाह्य पूर्णांक __drbd_change_sync(काष्ठा drbd_device *device, sector_t sector, पूर्णांक size,
		क्रमागत update_sync_bits_mode mode);
#घोषणा drbd_set_in_sync(device, sector, size) \
	__drbd_change_sync(device, sector, size, SET_IN_SYNC)
#घोषणा drbd_set_out_of_sync(device, sector, size) \
	__drbd_change_sync(device, sector, size, SET_OUT_OF_SYNC)
#घोषणा drbd_rs_failed_io(device, sector, size) \
	__drbd_change_sync(device, sector, size, RECORD_RS_FAILED)
बाह्य व्योम drbd_al_shrink(काष्ठा drbd_device *device);
बाह्य पूर्णांक drbd_al_initialize(काष्ठा drbd_device *, व्योम *);

/* drbd_nl.c */
/* state info broadcast */
काष्ठा sib_info अणु
	क्रमागत drbd_state_info_bcast_reason sib_reason;
	जोड़ अणु
		काष्ठा अणु
			अक्षर *helper_name;
			अचिन्हित helper_निकास_code;
		पूर्ण;
		काष्ठा अणु
			जोड़ drbd_state os;
			जोड़ drbd_state ns;
		पूर्ण;
	पूर्ण;
पूर्ण;
व्योम drbd_bcast_event(काष्ठा drbd_device *device, स्थिर काष्ठा sib_info *sib);

बाह्य व्योम notअगरy_resource_state(काष्ठा sk_buff *,
				  अचिन्हित पूर्णांक,
				  काष्ठा drbd_resource *,
				  काष्ठा resource_info *,
				  क्रमागत drbd_notअगरication_type);
बाह्य व्योम notअगरy_device_state(काष्ठा sk_buff *,
				अचिन्हित पूर्णांक,
				काष्ठा drbd_device *,
				काष्ठा device_info *,
				क्रमागत drbd_notअगरication_type);
बाह्य व्योम notअगरy_connection_state(काष्ठा sk_buff *,
				    अचिन्हित पूर्णांक,
				    काष्ठा drbd_connection *,
				    काष्ठा connection_info *,
				    क्रमागत drbd_notअगरication_type);
बाह्य व्योम notअगरy_peer_device_state(काष्ठा sk_buff *,
				     अचिन्हित पूर्णांक,
				     काष्ठा drbd_peer_device *,
				     काष्ठा peer_device_info *,
				     क्रमागत drbd_notअगरication_type);
बाह्य व्योम notअगरy_helper(क्रमागत drbd_notअगरication_type, काष्ठा drbd_device *,
			  काष्ठा drbd_connection *, स्थिर अक्षर *, पूर्णांक);

/*
 * अंतरभूत helper functions
 *************************/

/* see also page_chain_add and मित्रs in drbd_receiver.c */
अटल अंतरभूत काष्ठा page *page_chain_next(काष्ठा page *page)
अणु
	वापस (काष्ठा page *)page_निजी(page);
पूर्ण
#घोषणा page_chain_क्रम_each(page) \
	क्रम (; page && (अणु prefetch(page_chain_next(page)); 1; पूर्ण); \
			page = page_chain_next(page))
#घोषणा page_chain_क्रम_each_safe(page, n) \
	क्रम (; page && (अणु n = page_chain_next(page); 1; पूर्ण); page = n)


अटल अंतरभूत पूर्णांक drbd_peer_req_has_active_page(काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा page *page = peer_req->pages;
	page_chain_क्रम_each(page) अणु
		अगर (page_count(page) > 1)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत जोड़ drbd_state drbd_पढ़ो_state(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_resource *resource = device->resource;
	जोड़ drbd_state rv;

	rv.i = device->state.i;
	rv.susp = resource->susp;
	rv.susp_nod = resource->susp_nod;
	rv.susp_fen = resource->susp_fen;

	वापस rv;
पूर्ण

क्रमागत drbd_क्रमce_detach_flags अणु
	DRBD_READ_ERROR,
	DRBD_WRITE_ERROR,
	DRBD_META_IO_ERROR,
	DRBD_FORCE_DETACH,
पूर्ण;

#घोषणा __drbd_chk_io_error(m,f) __drbd_chk_io_error_(m,f, __func__)
अटल अंतरभूत व्योम __drbd_chk_io_error_(काष्ठा drbd_device *device,
		क्रमागत drbd_क्रमce_detach_flags df,
		स्थिर अक्षर *where)
अणु
	क्रमागत drbd_io_error_p ep;

	rcu_पढ़ो_lock();
	ep = rcu_dereference(device->ldev->disk_conf)->on_io_error;
	rcu_पढ़ो_unlock();
	चयन (ep) अणु
	हाल EP_PASS_ON: /* FIXME would this be better named "Ignore"? */
		अगर (df == DRBD_READ_ERROR || df == DRBD_WRITE_ERROR) अणु
			अगर (__ratelimit(&drbd_ratelimit_state))
				drbd_err(device, "Local IO failed in %s.\n", where);
			अगर (device->state.disk > D_INCONSISTENT)
				_drbd_set_state(_NS(device, disk, D_INCONSISTENT), CS_HARD, शून्य);
			अवरोध;
		पूर्ण
		fallthrough;	/* क्रम DRBD_META_IO_ERROR or DRBD_FORCE_DETACH */
	हाल EP_DETACH:
	हाल EP_CALL_HELPER:
		/* Remember whether we saw a READ or WRITE error.
		 *
		 * Recovery of the affected area क्रम WRITE failure is covered
		 * by the activity log.
		 * READ errors may fall outside that area though. Certain READ
		 * errors can be "healed" by writing good data to the affected
		 * blocks, which triggers block re-allocation in lower layers.
		 *
		 * If we can not ग_लिखो the biपंचांगap after a READ error,
		 * we may need to trigger a full sync (see w_go_diskless()).
		 *
		 * Force-detach is not really an IO error, but rather a
		 * desperate measure to try to deal with a completely
		 * unresponsive lower level IO stack.
		 * Still it should be treated as a WRITE error.
		 *
		 * Meta IO error is always WRITE error:
		 * we पढ़ो meta data only once during attach,
		 * which will fail in हाल of errors.
		 */
		set_bit(WAS_IO_ERROR, &device->flags);
		अगर (df == DRBD_READ_ERROR)
			set_bit(WAS_READ_ERROR, &device->flags);
		अगर (df == DRBD_FORCE_DETACH)
			set_bit(FORCE_DETACH, &device->flags);
		अगर (device->state.disk > D_FAILED) अणु
			_drbd_set_state(_NS(device, disk, D_FAILED), CS_HARD, शून्य);
			drbd_err(device,
				"Local IO failed in %s. Detaching...\n", where);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/**
 * drbd_chk_io_error: Handle the on_io_error setting, should be called from all io completion handlers
 * @device:	 DRBD device.
 * @error:	 Error code passed to the IO completion callback
 * @क्रमcedetach: Force detach. I.e. the error happened जबतक accessing the meta data
 *
 * See also drbd_मुख्य.c:after_state_ch() अगर (os.disk > D_FAILED && ns.disk == D_FAILED)
 */
#घोषणा drbd_chk_io_error(m,e,f) drbd_chk_io_error_(m,e,f, __func__)
अटल अंतरभूत व्योम drbd_chk_io_error_(काष्ठा drbd_device *device,
	पूर्णांक error, क्रमागत drbd_क्रमce_detach_flags क्रमcedetach, स्थिर अक्षर *where)
अणु
	अगर (error) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&device->resource->req_lock, flags);
		__drbd_chk_io_error_(device, क्रमcedetach, where);
		spin_unlock_irqrestore(&device->resource->req_lock, flags);
	पूर्ण
पूर्ण


/**
 * drbd_md_first_sector() - Returns the first sector number of the meta data area
 * @bdev:	Meta data block device.
 *
 * BTW, क्रम पूर्णांकernal meta data, this happens to be the maximum capacity
 * we could agree upon with our peer node.
 */
अटल अंतरभूत sector_t drbd_md_first_sector(काष्ठा drbd_backing_dev *bdev)
अणु
	चयन (bdev->md.meta_dev_idx) अणु
	हाल DRBD_MD_INDEX_INTERNAL:
	हाल DRBD_MD_INDEX_FLEX_INT:
		वापस bdev->md.md_offset + bdev->md.bm_offset;
	हाल DRBD_MD_INDEX_FLEX_EXT:
	शेष:
		वापस bdev->md.md_offset;
	पूर्ण
पूर्ण

/**
 * drbd_md_last_sector() - Return the last sector number of the meta data area
 * @bdev:	Meta data block device.
 */
अटल अंतरभूत sector_t drbd_md_last_sector(काष्ठा drbd_backing_dev *bdev)
अणु
	चयन (bdev->md.meta_dev_idx) अणु
	हाल DRBD_MD_INDEX_INTERNAL:
	हाल DRBD_MD_INDEX_FLEX_INT:
		वापस bdev->md.md_offset + MD_4kB_SECT -1;
	हाल DRBD_MD_INDEX_FLEX_EXT:
	शेष:
		वापस bdev->md.md_offset + bdev->md.md_size_sect -1;
	पूर्ण
पूर्ण

/* Returns the number of 512 byte sectors of the device */
अटल अंतरभूत sector_t drbd_get_capacity(काष्ठा block_device *bdev)
अणु
	/* वापस bdev ? get_capacity(bdev->bd_disk) : 0; */
	वापस bdev ? i_size_पढ़ो(bdev->bd_inode) >> 9 : 0;
पूर्ण

/**
 * drbd_get_max_capacity() - Returns the capacity we announce to out peer
 * @bdev:	Meta data block device.
 *
 * वापसs the capacity we announce to out peer.  we clip ourselves at the
 * various MAX_SECTORS, because अगर we करोn't, current implementation will
 * oops sooner or later
 */
अटल अंतरभूत sector_t drbd_get_max_capacity(काष्ठा drbd_backing_dev *bdev)
अणु
	sector_t s;

	चयन (bdev->md.meta_dev_idx) अणु
	हाल DRBD_MD_INDEX_INTERNAL:
	हाल DRBD_MD_INDEX_FLEX_INT:
		s = drbd_get_capacity(bdev->backing_bdev)
			? min_t(sector_t, DRBD_MAX_SECTORS_FLEX,
				drbd_md_first_sector(bdev))
			: 0;
		अवरोध;
	हाल DRBD_MD_INDEX_FLEX_EXT:
		s = min_t(sector_t, DRBD_MAX_SECTORS_FLEX,
				drbd_get_capacity(bdev->backing_bdev));
		/* clip at maximum size the meta device can support */
		s = min_t(sector_t, s,
			BM_EXT_TO_SECT(bdev->md.md_size_sect
				     - bdev->md.bm_offset));
		अवरोध;
	शेष:
		s = min_t(sector_t, DRBD_MAX_SECTORS,
				drbd_get_capacity(bdev->backing_bdev));
	पूर्ण
	वापस s;
पूर्ण

/**
 * drbd_md_ss() - Return the sector number of our meta data super block
 * @bdev:	Meta data block device.
 */
अटल अंतरभूत sector_t drbd_md_ss(काष्ठा drbd_backing_dev *bdev)
अणु
	स्थिर पूर्णांक meta_dev_idx = bdev->md.meta_dev_idx;

	अगर (meta_dev_idx == DRBD_MD_INDEX_FLEX_EXT)
		वापस 0;

	/* Since drbd08, पूर्णांकernal meta data is always "flexible".
	 * position: last 4k aligned block of 4k size */
	अगर (meta_dev_idx == DRBD_MD_INDEX_INTERNAL ||
	    meta_dev_idx == DRBD_MD_INDEX_FLEX_INT)
		वापस (drbd_get_capacity(bdev->backing_bdev) & ~7ULL) - 8;

	/* बाह्यal, some index; this is the old fixed size layout */
	वापस MD_128MB_SECT * bdev->md.meta_dev_idx;
पूर्ण

अटल अंतरभूत व्योम
drbd_queue_work(काष्ठा drbd_work_queue *q, काष्ठा drbd_work *w)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&q->q_lock, flags);
	list_add_tail(&w->list, &q->q);
	spin_unlock_irqrestore(&q->q_lock, flags);
	wake_up(&q->q_रुको);
पूर्ण

अटल अंतरभूत व्योम
drbd_queue_work_अगर_unqueued(काष्ठा drbd_work_queue *q, काष्ठा drbd_work *w)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&q->q_lock, flags);
	अगर (list_empty_careful(&w->list))
		list_add_tail(&w->list, &q->q);
	spin_unlock_irqrestore(&q->q_lock, flags);
	wake_up(&q->q_रुको);
पूर्ण

अटल अंतरभूत व्योम
drbd_device_post_work(काष्ठा drbd_device *device, पूर्णांक work_bit)
अणु
	अगर (!test_and_set_bit(work_bit, &device->flags)) अणु
		काष्ठा drbd_connection *connection =
			first_peer_device(device)->connection;
		काष्ठा drbd_work_queue *q = &connection->sender_work;
		अगर (!test_and_set_bit(DEVICE_WORK_PENDING, &connection->flags))
			wake_up(&q->q_रुको);
	पूर्ण
पूर्ण

बाह्य व्योम drbd_flush_workqueue(काष्ठा drbd_work_queue *work_queue);

/* To get the ack_receiver out of the blocking network stack,
 * so it can change its sk_rcvसमयo from idle- to ping-समयout,
 * and send a ping, we need to send a संकेत.
 * Which संकेत we send is irrelevant. */
अटल अंतरभूत व्योम wake_ack_receiver(काष्ठा drbd_connection *connection)
अणु
	काष्ठा task_काष्ठा *task = connection->ack_receiver.task;
	अगर (task && get_t_state(&connection->ack_receiver) == RUNNING)
		send_sig(SIGXCPU, task, 1);
पूर्ण

अटल अंतरभूत व्योम request_ping(काष्ठा drbd_connection *connection)
अणु
	set_bit(SEND_PING, &connection->flags);
	wake_ack_receiver(connection);
पूर्ण

बाह्य व्योम *conn_prepare_command(काष्ठा drbd_connection *, काष्ठा drbd_socket *);
बाह्य व्योम *drbd_prepare_command(काष्ठा drbd_peer_device *, काष्ठा drbd_socket *);
बाह्य पूर्णांक conn_send_command(काष्ठा drbd_connection *, काष्ठा drbd_socket *,
			     क्रमागत drbd_packet, अचिन्हित पूर्णांक, व्योम *,
			     अचिन्हित पूर्णांक);
बाह्य पूर्णांक drbd_send_command(काष्ठा drbd_peer_device *, काष्ठा drbd_socket *,
			     क्रमागत drbd_packet, अचिन्हित पूर्णांक, व्योम *,
			     अचिन्हित पूर्णांक);

बाह्य पूर्णांक drbd_send_ping(काष्ठा drbd_connection *connection);
बाह्य पूर्णांक drbd_send_ping_ack(काष्ठा drbd_connection *connection);
बाह्य पूर्णांक drbd_send_state_req(काष्ठा drbd_peer_device *, जोड़ drbd_state, जोड़ drbd_state);
बाह्य पूर्णांक conn_send_state_req(काष्ठा drbd_connection *, जोड़ drbd_state, जोड़ drbd_state);

अटल अंतरभूत व्योम drbd_thपढ़ो_stop(काष्ठा drbd_thपढ़ो *thi)
अणु
	_drbd_thपढ़ो_stop(thi, false, true);
पूर्ण

अटल अंतरभूत व्योम drbd_thपढ़ो_stop_noरुको(काष्ठा drbd_thपढ़ो *thi)
अणु
	_drbd_thपढ़ो_stop(thi, false, false);
पूर्ण

अटल अंतरभूत व्योम drbd_thपढ़ो_restart_noरुको(काष्ठा drbd_thपढ़ो *thi)
अणु
	_drbd_thपढ़ो_stop(thi, true, false);
पूर्ण

/* counts how many answer packets packets we expect from our peer,
 * क्रम either explicit application requests,
 * or implicit barrier packets as necessary.
 * increased:
 *  w_send_barrier
 *  _req_mod(req, QUEUE_FOR_NET_WRITE or QUEUE_FOR_NET_READ);
 *    it is much easier and equally valid to count what we queue क्रम the
 *    worker, even beक्रमe it actually was queued or send.
 *    (drbd_make_request_common; recovery path on पढ़ो io-error)
 * decreased:
 *  got_BarrierAck (respective tl_clear, tl_clear_barrier)
 *  _req_mod(req, DATA_RECEIVED)
 *     [from receive_DataReply]
 *  _req_mod(req, WRITE_ACKED_BY_PEER or RECV_ACKED_BY_PEER or NEG_ACKED)
 *     [from got_BlockAck (P_WRITE_ACK, P_RECV_ACK)]
 *     क्रम some reason it is NOT decreased in got_NegAck,
 *     but in the resulting cleanup code from report_params.
 *     we should try to remember the reason क्रम that...
 *  _req_mod(req, SEND_FAILED or SEND_CANCELED)
 *  _req_mod(req, CONNECTION_LOST_WHILE_PENDING)
 *     [from tl_clear_barrier]
 */
अटल अंतरभूत व्योम inc_ap_pending(काष्ठा drbd_device *device)
अणु
	atomic_inc(&device->ap_pending_cnt);
पूर्ण

#घोषणा ERR_IF_CNT_IS_NEGATIVE(which, func, line)			\
	अगर (atomic_पढ़ो(&device->which) < 0)				\
		drbd_err(device, "in %s:%d: " #which " = %d < 0 !\n",	\
			func, line,					\
			atomic_पढ़ो(&device->which))

#घोषणा dec_ap_pending(device) _dec_ap_pending(device, __func__, __LINE__)
अटल अंतरभूत व्योम _dec_ap_pending(काष्ठा drbd_device *device, स्थिर अक्षर *func, पूर्णांक line)
अणु
	अगर (atomic_dec_and_test(&device->ap_pending_cnt))
		wake_up(&device->misc_रुको);
	ERR_IF_CNT_IS_NEGATIVE(ap_pending_cnt, func, line);
पूर्ण

/* counts how many resync-related answers we still expect from the peer
 *		     increase			decrease
 * C_SYNC_TARGET sends P_RS_DATA_REQUEST (and expects P_RS_DATA_REPLY)
 * C_SYNC_SOURCE sends P_RS_DATA_REPLY   (and expects P_WRITE_ACK with ID_SYNCER)
 *					   (or P_NEG_ACK with ID_SYNCER)
 */
अटल अंतरभूत व्योम inc_rs_pending(काष्ठा drbd_device *device)
अणु
	atomic_inc(&device->rs_pending_cnt);
पूर्ण

#घोषणा dec_rs_pending(device) _dec_rs_pending(device, __func__, __LINE__)
अटल अंतरभूत व्योम _dec_rs_pending(काष्ठा drbd_device *device, स्थिर अक्षर *func, पूर्णांक line)
अणु
	atomic_dec(&device->rs_pending_cnt);
	ERR_IF_CNT_IS_NEGATIVE(rs_pending_cnt, func, line);
पूर्ण

/* counts how many answers we still need to send to the peer.
 * increased on
 *  receive_Data	unless protocol A;
 *			we need to send a P_RECV_ACK (proto B)
 *			or P_WRITE_ACK (proto C)
 *  receive_RSDataReply (recv_resync_पढ़ो) we need to send a P_WRITE_ACK
 *  receive_DataRequest (receive_RSDataRequest) we need to send back P_DATA
 *  receive_Barrier_*	we need to send a P_BARRIER_ACK
 */
अटल अंतरभूत व्योम inc_unacked(काष्ठा drbd_device *device)
अणु
	atomic_inc(&device->unacked_cnt);
पूर्ण

#घोषणा dec_unacked(device) _dec_unacked(device, __func__, __LINE__)
अटल अंतरभूत व्योम _dec_unacked(काष्ठा drbd_device *device, स्थिर अक्षर *func, पूर्णांक line)
अणु
	atomic_dec(&device->unacked_cnt);
	ERR_IF_CNT_IS_NEGATIVE(unacked_cnt, func, line);
पूर्ण

#घोषणा sub_unacked(device, n) _sub_unacked(device, n, __func__, __LINE__)
अटल अंतरभूत व्योम _sub_unacked(काष्ठा drbd_device *device, पूर्णांक n, स्थिर अक्षर *func, पूर्णांक line)
अणु
	atomic_sub(n, &device->unacked_cnt);
	ERR_IF_CNT_IS_NEGATIVE(unacked_cnt, func, line);
पूर्ण

अटल अंतरभूत bool is_sync_target_state(क्रमागत drbd_conns connection_state)
अणु
	वापस	connection_state == C_SYNC_TARGET ||
		connection_state == C_PAUSED_SYNC_T;
पूर्ण

अटल अंतरभूत bool is_sync_source_state(क्रमागत drbd_conns connection_state)
अणु
	वापस	connection_state == C_SYNC_SOURCE ||
		connection_state == C_PAUSED_SYNC_S;
पूर्ण

अटल अंतरभूत bool is_sync_state(क्रमागत drbd_conns connection_state)
अणु
	वापस	is_sync_source_state(connection_state) ||
		is_sync_target_state(connection_state);
पूर्ण

/**
 * get_ldev() - Increase the ref count on device->ldev. Returns 0 अगर there is no ldev
 * @_device:		DRBD device.
 * @_min_state:		Minimum device state required क्रम success.
 *
 * You have to call put_ldev() when finished working with device->ldev.
 */
#घोषणा get_ldev_अगर_state(_device, _min_state)				\
	(_get_ldev_अगर_state((_device), (_min_state)) ?			\
	 (अणु __acquire(x); true; पूर्ण) : false)
#घोषणा get_ldev(_device) get_ldev_अगर_state(_device, D_INCONSISTENT)

अटल अंतरभूत व्योम put_ldev(काष्ठा drbd_device *device)
अणु
	क्रमागत drbd_disk_state disk_state = device->state.disk;
	/* We must check the state *beक्रमe* the atomic_dec becomes visible,
	 * or we have a theoretical race where someone hitting zero,
	 * जबतक state still D_FAILED, will then see D_DISKLESS in the
	 * condition below and calling पूर्णांकo destroy, where he must not, yet. */
	पूर्णांक i = atomic_dec_वापस(&device->local_cnt);

	/* This may be called from some endio handler,
	 * so we must not sleep here. */

	__release(local);
	D_ASSERT(device, i >= 0);
	अगर (i == 0) अणु
		अगर (disk_state == D_DISKLESS)
			/* even पूर्णांकernal references gone, safe to destroy */
			drbd_device_post_work(device, DESTROY_DISK);
		अगर (disk_state == D_FAILED)
			/* all application IO references gone. */
			अगर (!test_and_set_bit(GOING_DISKLESS, &device->flags))
				drbd_device_post_work(device, GO_DISKLESS);
		wake_up(&device->misc_रुको);
	पूर्ण
पूर्ण

#अगर_अघोषित __CHECKER__
अटल अंतरभूत पूर्णांक _get_ldev_अगर_state(काष्ठा drbd_device *device, क्रमागत drbd_disk_state mins)
अणु
	पूर्णांक io_allowed;

	/* never get a reference जबतक D_DISKLESS */
	अगर (device->state.disk == D_DISKLESS)
		वापस 0;

	atomic_inc(&device->local_cnt);
	io_allowed = (device->state.disk >= mins);
	अगर (!io_allowed)
		put_ldev(device);
	वापस io_allowed;
पूर्ण
#अन्यथा
बाह्य पूर्णांक _get_ldev_अगर_state(काष्ठा drbd_device *device, क्रमागत drbd_disk_state mins);
#पूर्ण_अगर

/* this throttles on-the-fly application requests
 * according to max_buffers settings;
 * maybe re-implement using semaphores? */
अटल अंतरभूत पूर्णांक drbd_get_max_buffers(काष्ठा drbd_device *device)
अणु
	काष्ठा net_conf *nc;
	पूर्णांक mxb;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(first_peer_device(device)->connection->net_conf);
	mxb = nc ? nc->max_buffers : 1000000;  /* arbitrary limit on खोलो requests */
	rcu_पढ़ो_unlock();

	वापस mxb;
पूर्ण

अटल अंतरभूत पूर्णांक drbd_state_is_stable(काष्ठा drbd_device *device)
अणु
	जोड़ drbd_dev_state s = device->state;

	/* DO NOT add a शेष clause, we want the compiler to warn us
	 * क्रम any newly पूर्णांकroduced state we may have क्रमgotten to add here */

	चयन ((क्रमागत drbd_conns)s.conn) अणु
	/* new io only accepted when there is no connection, ... */
	हाल C_STANDALONE:
	हाल C_WF_CONNECTION:
	/* ... or there is a well established connection. */
	हाल C_CONNECTED:
	हाल C_SYNC_SOURCE:
	हाल C_SYNC_TARGET:
	हाल C_VERIFY_S:
	हाल C_VERIFY_T:
	हाल C_PAUSED_SYNC_S:
	हाल C_PAUSED_SYNC_T:
	हाल C_AHEAD:
	हाल C_BEHIND:
		/* transitional states, IO allowed */
	हाल C_DISCONNECTING:
	हाल C_UNCONNECTED:
	हाल C_TIMEOUT:
	हाल C_BROKEN_PIPE:
	हाल C_NETWORK_FAILURE:
	हाल C_PROTOCOL_ERROR:
	हाल C_TEAR_DOWN:
	हाल C_WF_REPORT_PARAMS:
	हाल C_STARTING_SYNC_S:
	हाल C_STARTING_SYNC_T:
		अवरोध;

		/* Allow IO in BM exchange states with new protocols */
	हाल C_WF_BITMAP_S:
		अगर (first_peer_device(device)->connection->agreed_pro_version < 96)
			वापस 0;
		अवरोध;

		/* no new io accepted in these states */
	हाल C_WF_BITMAP_T:
	हाल C_WF_SYNC_UUID:
	हाल C_MASK:
		/* not "stable" */
		वापस 0;
	पूर्ण

	चयन ((क्रमागत drbd_disk_state)s.disk) अणु
	हाल D_DISKLESS:
	हाल D_INCONSISTENT:
	हाल D_OUTDATED:
	हाल D_CONSISTENT:
	हाल D_UP_TO_DATE:
	हाल D_FAILED:
		/* disk state is stable as well. */
		अवरोध;

	/* no new io accepted during transitional states */
	हाल D_ATTACHING:
	हाल D_NEGOTIATING:
	हाल D_UNKNOWN:
	हाल D_MASK:
		/* not "stable" */
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक drbd_suspended(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_resource *resource = device->resource;

	वापस resource->susp || resource->susp_fen || resource->susp_nod;
पूर्ण

अटल अंतरभूत bool may_inc_ap_bio(काष्ठा drbd_device *device)
अणु
	पूर्णांक mxb = drbd_get_max_buffers(device);

	अगर (drbd_suspended(device))
		वापस false;
	अगर (atomic_पढ़ो(&device->suspend_cnt))
		वापस false;

	/* to aव्योम potential deadlock or biपंचांगap corruption,
	 * in various places, we only allow new application io
	 * to start during "stable" states. */

	/* no new io accepted when attaching or detaching the disk */
	अगर (!drbd_state_is_stable(device))
		वापस false;

	/* since some older kernels करोn't have atomic_add_unless,
	 * and we are within the spinlock anyways, we have this workaround.  */
	अगर (atomic_पढ़ो(&device->ap_bio_cnt) > mxb)
		वापस false;
	अगर (test_bit(BITMAP_IO, &device->flags))
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool inc_ap_bio_cond(काष्ठा drbd_device *device)
अणु
	bool rv = false;

	spin_lock_irq(&device->resource->req_lock);
	rv = may_inc_ap_bio(device);
	अगर (rv)
		atomic_inc(&device->ap_bio_cnt);
	spin_unlock_irq(&device->resource->req_lock);

	वापस rv;
पूर्ण

अटल अंतरभूत व्योम inc_ap_bio(काष्ठा drbd_device *device)
अणु
	/* we रुको here
	 *    as दीर्घ as the device is suspended
	 *    until the biपंचांगap is no दीर्घer on the fly during connection
	 *    handshake as दीर्घ as we would exceed the max_buffer limit.
	 *
	 * to aव्योम races with the reconnect code,
	 * we need to atomic_inc within the spinlock. */

	रुको_event(device->misc_रुको, inc_ap_bio_cond(device));
पूर्ण

अटल अंतरभूत व्योम dec_ap_bio(काष्ठा drbd_device *device)
अणु
	पूर्णांक mxb = drbd_get_max_buffers(device);
	पूर्णांक ap_bio = atomic_dec_वापस(&device->ap_bio_cnt);

	D_ASSERT(device, ap_bio >= 0);

	अगर (ap_bio == 0 && test_bit(BITMAP_IO, &device->flags)) अणु
		अगर (!test_and_set_bit(BITMAP_IO_QUEUED, &device->flags))
			drbd_queue_work(&first_peer_device(device)->
				connection->sender_work,
				&device->bm_io_work.w);
	पूर्ण

	/* this currently करोes wake_up क्रम every dec_ap_bio!
	 * maybe rather पूर्णांकroduce some type of hysteresis?
	 * e.g. (ap_bio == mxb/2 || ap_bio == 0) ? */
	अगर (ap_bio < mxb)
		wake_up(&device->misc_रुको);
पूर्ण

अटल अंतरभूत bool verअगरy_can_करो_stop_sector(काष्ठा drbd_device *device)
अणु
	वापस first_peer_device(device)->connection->agreed_pro_version >= 97 &&
		first_peer_device(device)->connection->agreed_pro_version != 100;
पूर्ण

अटल अंतरभूत पूर्णांक drbd_set_ed_uuid(काष्ठा drbd_device *device, u64 val)
अणु
	पूर्णांक changed = device->ed_uuid != val;
	device->ed_uuid = val;
	वापस changed;
पूर्ण

अटल अंतरभूत पूर्णांक drbd_queue_order_type(काष्ठा drbd_device *device)
अणु
	/* sorry, we currently have no working implementation
	 * of distributed TCQ stuff */
#अगर_अघोषित QUEUE_ORDERED_NONE
#घोषणा QUEUE_ORDERED_NONE 0
#पूर्ण_अगर
	वापस QUEUE_ORDERED_NONE;
पूर्ण

अटल अंतरभूत काष्ठा drbd_connection *first_connection(काष्ठा drbd_resource *resource)
अणु
	वापस list_first_entry_or_null(&resource->connections,
				काष्ठा drbd_connection, connections);
पूर्ण

#पूर्ण_अगर
