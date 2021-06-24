<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPIBLKTRACE_H
#घोषणा _UAPIBLKTRACE_H

#समावेश <linux/types.h>

/*
 * Trace categories
 */
क्रमागत blktrace_cat अणु
	BLK_TC_READ	= 1 << 0,	/* पढ़ोs */
	BLK_TC_WRITE	= 1 << 1,	/* ग_लिखोs */
	BLK_TC_FLUSH	= 1 << 2,	/* flush */
	BLK_TC_SYNC	= 1 << 3,	/* sync IO */
	BLK_TC_SYNCIO	= BLK_TC_SYNC,
	BLK_TC_QUEUE	= 1 << 4,	/* queueing/merging */
	BLK_TC_REQUEUE	= 1 << 5,	/* requeueing */
	BLK_TC_ISSUE	= 1 << 6,	/* issue */
	BLK_TC_COMPLETE	= 1 << 7,	/* completions */
	BLK_TC_FS	= 1 << 8,	/* fs requests */
	BLK_TC_PC	= 1 << 9,	/* pc requests */
	BLK_TC_NOTIFY	= 1 << 10,	/* special message */
	BLK_TC_AHEAD	= 1 << 11,	/* पढ़ोahead */
	BLK_TC_META	= 1 << 12,	/* metadata */
	BLK_TC_DISCARD	= 1 << 13,	/* discard requests */
	BLK_TC_DRV_DATA	= 1 << 14,	/* binary per-driver data */
	BLK_TC_FUA	= 1 << 15,	/* fua requests */

	BLK_TC_END	= 1 << 15,	/* we've run out of bits! */
पूर्ण;

#घोषणा BLK_TC_SHIFT		(16)
#घोषणा BLK_TC_ACT(act)		((act) << BLK_TC_SHIFT)

/*
 * Basic trace actions
 */
क्रमागत blktrace_act अणु
	__BLK_TA_QUEUE = 1,		/* queued */
	__BLK_TA_BACKMERGE,		/* back merged to existing rq */
	__BLK_TA_FRONTMERGE,		/* front merge to existing rq */
	__BLK_TA_GETRQ,			/* allocated new request */
	__BLK_TA_SLEEPRQ,		/* sleeping on rq allocation */
	__BLK_TA_REQUEUE,		/* request requeued */
	__BLK_TA_ISSUE,			/* sent to driver */
	__BLK_TA_COMPLETE,		/* completed by driver */
	__BLK_TA_PLUG,			/* queue was plugged */
	__BLK_TA_UNPLUG_IO,		/* queue was unplugged by io */
	__BLK_TA_UNPLUG_TIMER,		/* queue was unplugged by समयr */
	__BLK_TA_INSERT,		/* insert request */
	__BLK_TA_SPLIT,			/* bio was split */
	__BLK_TA_BOUNCE,		/* bio was bounced */
	__BLK_TA_REMAP,			/* bio was remapped */
	__BLK_TA_ABORT,			/* request पातed */
	__BLK_TA_DRV_DATA,		/* driver-specअगरic binary data */
	__BLK_TA_CGROUP = 1 << 8,	/* from a cgroup*/
पूर्ण;

/*
 * Notअगरy events.
 */
क्रमागत blktrace_notअगरy अणु
	__BLK_TN_PROCESS = 0,		/* establish pid/name mapping */
	__BLK_TN_TIMESTAMP,		/* include प्रणाली घड़ी */
	__BLK_TN_MESSAGE,		/* Character string message */
	__BLK_TN_CGROUP = __BLK_TA_CGROUP, /* from a cgroup */
पूर्ण;


/*
 * Trace actions in full. Additionally, पढ़ो or ग_लिखो is masked
 */
#घोषणा BLK_TA_QUEUE		(__BLK_TA_QUEUE | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा BLK_TA_BACKMERGE	(__BLK_TA_BACKMERGE | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा BLK_TA_FRONTMERGE	(__BLK_TA_FRONTMERGE | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा	BLK_TA_GETRQ		(__BLK_TA_GETRQ | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा	BLK_TA_SLEEPRQ		(__BLK_TA_SLEEPRQ | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा	BLK_TA_REQUEUE		(__BLK_TA_REQUEUE | BLK_TC_ACT(BLK_TC_REQUEUE))
#घोषणा BLK_TA_ISSUE		(__BLK_TA_ISSUE | BLK_TC_ACT(BLK_TC_ISSUE))
#घोषणा BLK_TA_COMPLETE		(__BLK_TA_COMPLETE| BLK_TC_ACT(BLK_TC_COMPLETE))
#घोषणा BLK_TA_PLUG		(__BLK_TA_PLUG | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा BLK_TA_UNPLUG_IO	(__BLK_TA_UNPLUG_IO | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा BLK_TA_UNPLUG_TIMER	(__BLK_TA_UNPLUG_TIMER | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा BLK_TA_INSERT		(__BLK_TA_INSERT | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा BLK_TA_SPLIT		(__BLK_TA_SPLIT)
#घोषणा BLK_TA_BOUNCE		(__BLK_TA_BOUNCE)
#घोषणा BLK_TA_REMAP		(__BLK_TA_REMAP | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा BLK_TA_ABORT		(__BLK_TA_ABORT | BLK_TC_ACT(BLK_TC_QUEUE))
#घोषणा BLK_TA_DRV_DATA	(__BLK_TA_DRV_DATA | BLK_TC_ACT(BLK_TC_DRV_DATA))

#घोषणा BLK_TN_PROCESS		(__BLK_TN_PROCESS | BLK_TC_ACT(BLK_TC_NOTIFY))
#घोषणा BLK_TN_TIMESTAMP	(__BLK_TN_TIMESTAMP | BLK_TC_ACT(BLK_TC_NOTIFY))
#घोषणा BLK_TN_MESSAGE		(__BLK_TN_MESSAGE | BLK_TC_ACT(BLK_TC_NOTIFY))

#घोषणा BLK_IO_TRACE_MAGIC	0x65617400
#घोषणा BLK_IO_TRACE_VERSION	0x07

/*
 * The trace itself
 */
काष्ठा blk_io_trace अणु
	__u32 magic;		/* MAGIC << 8 | version */
	__u32 sequence;		/* event number */
	__u64 समय;		/* in nanoseconds */
	__u64 sector;		/* disk offset */
	__u32 bytes;		/* transfer length */
	__u32 action;		/* what happened */
	__u32 pid;		/* who did it */
	__u32 device;		/* device number */
	__u32 cpu;		/* on what cpu did it happen */
	__u16 error;		/* completion error */
	__u16 pdu_len;		/* length of data after this trace */
	/* cgroup id will be stored here अगर exists */
पूर्ण;

/*
 * The remap event
 */
काष्ठा blk_io_trace_remap अणु
	__be32 device_from;
	__be32 device_to;
	__be64 sector_from;
पूर्ण;

क्रमागत अणु
	Blktrace_setup = 1,
	Blktrace_running,
	Blktrace_stopped,
पूर्ण;

#घोषणा BLKTRACE_BDEV_SIZE	32

/*
 * User setup काष्ठाure passed with BLKTRACESETUP
 */
काष्ठा blk_user_trace_setup अणु
	अक्षर name[BLKTRACE_BDEV_SIZE];	/* output */
	__u16 act_mask;			/* input */
	__u32 buf_size;			/* input */
	__u32 buf_nr;			/* input */
	__u64 start_lba;
	__u64 end_lba;
	__u32 pid;
पूर्ण;

#पूर्ण_अगर /* _UAPIBLKTRACE_H */
