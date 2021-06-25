<शैली गुरु>
/* Copyright (c) 2013 Coraid, Inc.  See COPYING क्रम GPL terms. */
#समावेश <linux/blk-mq.h>

#घोषणा VERSION "85"
#घोषणा AOE_MAJOR 152
#घोषणा DEVICE_NAME "aoe"

/* set AOE_PARTITIONS to 1 to use whole-disks only
 * शेष is 16, which is 15 partitions plus the whole disk
 */
#अगर_अघोषित AOE_PARTITIONS
#घोषणा AOE_PARTITIONS (16)
#पूर्ण_अगर

#घोषणा WHITESPACE " \t\v\f\n,"

क्रमागत अणु
	AOECMD_ATA,
	AOECMD_CFG,
	AOECMD_VEND_MIN = 0xf0,

	AOEFL_RSP = (1<<3),
	AOEFL_ERR = (1<<2),

	AOEAFL_EXT = (1<<6),
	AOEAFL_DEV = (1<<4),
	AOEAFL_ASYNC = (1<<1),
	AOEAFL_WRITE = (1<<0),

	AOECCMD_READ = 0,
	AOECCMD_TEST,
	AOECCMD_PTEST,
	AOECCMD_SET,
	AOECCMD_FSET,

	AOE_HVER = 0x10,
पूर्ण;

काष्ठा aoe_hdr अणु
	अचिन्हित अक्षर dst[6];
	अचिन्हित अक्षर src[6];
	__be16 type;
	अचिन्हित अक्षर verfl;
	अचिन्हित अक्षर err;
	__be16 major;
	अचिन्हित अक्षर minor;
	अचिन्हित अक्षर cmd;
	__be32 tag;
पूर्ण;

काष्ठा aoe_atahdr अणु
	अचिन्हित अक्षर aflags;
	अचिन्हित अक्षर errfeat;
	अचिन्हित अक्षर scnt;
	अचिन्हित अक्षर cmdstat;
	अचिन्हित अक्षर lba0;
	अचिन्हित अक्षर lba1;
	अचिन्हित अक्षर lba2;
	अचिन्हित अक्षर lba3;
	अचिन्हित अक्षर lba4;
	अचिन्हित अक्षर lba5;
	अचिन्हित अक्षर res[2];
पूर्ण;

काष्ठा aoe_cfghdr अणु
	__be16 bufcnt;
	__be16 fwver;
	अचिन्हित अक्षर scnt;
	अचिन्हित अक्षर aoeccmd;
	अचिन्हित अक्षर cslen[2];
पूर्ण;

क्रमागत अणु
	DEVFL_UP = 1,	/* device is installed in प्रणाली and पढ़ोy क्रम AoE->ATA commands */
	DEVFL_TKILL = (1<<1),	/* flag क्रम समयr to know when to समाप्त self */
	DEVFL_EXT = (1<<2),	/* device accepts lba48 commands */
	DEVFL_GDALLOC = (1<<3),	/* need to alloc gendisk */
	DEVFL_GD_NOW = (1<<4),	/* allocating gendisk */
	DEVFL_KICKME = (1<<5),	/* slow polling network card catch */
	DEVFL_NEWSIZE = (1<<6),	/* need to update dev size in block layer */
	DEVFL_FREEING = (1<<7),	/* set when device is being cleaned up */
	DEVFL_FREED = (1<<8),	/* device has been cleaned up */
पूर्ण;

क्रमागत अणु
	DEFAULTBCNT = 2 * 512,	/* 2 sectors */
	MIN_BUFS = 16,
	NTARGETS = 4,
	NAOEIFS = 8,
	NSKBPOOLMAX = 256,
	NFACTIVE = 61,

	TIMERTICK = HZ / 10,
	RTTSCALE = 8,
	RTTDSCALE = 3,
	RTTAVG_INIT = USEC_PER_SEC / 4 << RTTSCALE,
	RTTDEV_INIT = RTTAVG_INIT / 4,

	HARD_SCORN_SECS = 10,	/* try another remote port after this */
	MAX_TAINT = 1000,	/* cap on aoetgt taपूर्णांक */
पूर्ण;

काष्ठा aoe_req अणु
	अचिन्हित दीर्घ nr_bios;
पूर्ण;

काष्ठा buf अणु
	uदीर्घ nframesout;
	काष्ठा bio *bio;
	काष्ठा bvec_iter iter;
	काष्ठा request *rq;
पूर्ण;

क्रमागत frame_flags अणु
	FFL_PROBE = 1,
पूर्ण;

काष्ठा frame अणु
	काष्ठा list_head head;
	u32 tag;
	kसमय_प्रकार sent;			/* high-res समय packet was sent */
	uदीर्घ रुकोed;
	uदीर्घ रुकोed_total;
	काष्ठा aoetgt *t;		/* parent target I beदीर्घ to */
	काष्ठा sk_buff *skb;		/* command skb मुक्तd on module निकास */
	काष्ठा sk_buff *r_skb;		/* response skb क्रम async processing */
	काष्ठा buf *buf;
	काष्ठा bvec_iter iter;
	अक्षर flags;
पूर्ण;

काष्ठा aoeअगर अणु
	काष्ठा net_device *nd;
	uदीर्घ lost;
	पूर्णांक bcnt;
पूर्ण;

काष्ठा aoetgt अणु
	अचिन्हित अक्षर addr[6];
	uलघु nframes;		/* cap on frames to use */
	काष्ठा aoedev *d;			/* parent device I beदीर्घ to */
	काष्ठा list_head fमुक्त;			/* list of मुक्त frames */
	काष्ठा aoeअगर अगरs[NAOEIFS];
	काष्ठा aoeअगर *अगरp;	/* current aoeअगर in use */
	uलघु nout;		/* number of AoE commands outstanding */
	uलघु maxout;		/* current value क्रम max outstanding */
	uलघु next_cwnd;	/* incr maxout after decrementing to zero */
	uलघु ssthresh;	/* slow start threshold */
	uदीर्घ falloc;		/* number of allocated frames */
	पूर्णांक taपूर्णांक;		/* how much we want to aव्योम this aoetgt */
	पूर्णांक minbcnt;
	पूर्णांक wpkts, rpkts;
	अक्षर nout_probes;
पूर्ण;

काष्ठा aoedev अणु
	काष्ठा aoedev *next;
	uदीर्घ sysminor;
	uदीर्घ aoemajor;
	u32 rttavg;		/* scaled AoE round trip समय average */
	u32 rttdev;		/* scaled round trip समय mean deviation */
	u16 aoeminor;
	u16 flags;
	u16 nखोलो;		/* (bd_खोलोers isn't available without sleeping) */
	u16 fw_ver;		/* version of blade's firmware */
	u16 lasttag;		/* last tag sent */
	u16 useme;
	uदीर्घ ref;
	काष्ठा work_काष्ठा work;/* disk create work काष्ठा */
	काष्ठा gendisk *gd;
	काष्ठा dentry *debugfs;
	काष्ठा request_queue *blkq;
	काष्ठा list_head rq_list;
	काष्ठा blk_mq_tag_set tag_set;
	काष्ठा hd_geometry geo;
	sector_t ssize;
	काष्ठा समयr_list समयr;
	spinlock_t lock;
	काष्ठा sk_buff_head skbpool;
	mempool_t *bufpool;	/* क्रम deadlock-मुक्त Buf allocation */
	काष्ठा अणु		/* poपूर्णांकers to work in progress */
		काष्ठा buf *buf;
		काष्ठा bio *nxbio;
		काष्ठा request *rq;
	पूर्ण ip;
	uदीर्घ maxbcnt;
	काष्ठा list_head factive[NFACTIVE];	/* hash of active frames */
	काष्ठा list_head rexmitq; /* deferred retransmissions */
	काष्ठा aoetgt **tarमाला_लो;
	uदीर्घ ntarमाला_लो;		/* number of allocated aoetgt poपूर्णांकers */
	काष्ठा aoetgt **tgt;	/* target in use when working */
	uदीर्घ kicked;
	अक्षर ident[512];
पूर्ण;

/* kthपढ़ो tracking */
काष्ठा ktstate अणु
	काष्ठा completion rendez;
	काष्ठा task_काष्ठा *task;
	रुको_queue_head_t *रुकोq;
	पूर्णांक (*fn) (पूर्णांक);
	अक्षर name[12];
	spinlock_t *lock;
	पूर्णांक id;
	पूर्णांक active;
पूर्ण;

पूर्णांक aoeblk_init(व्योम);
व्योम aoeblk_निकास(व्योम);
व्योम aoeblk_gdalloc(व्योम *);
व्योम aoedisk_rm_debugfs(काष्ठा aoedev *d);

पूर्णांक aoechr_init(व्योम);
व्योम aoechr_निकास(व्योम);
व्योम aoechr_error(अक्षर *);

व्योम aoecmd_work(काष्ठा aoedev *d);
व्योम aoecmd_cfg(uलघु aoemajor, अचिन्हित अक्षर aoeminor);
काष्ठा sk_buff *aoecmd_ata_rsp(काष्ठा sk_buff *);
व्योम aoecmd_cfg_rsp(काष्ठा sk_buff *);
व्योम aoecmd_sleepwork(काष्ठा work_काष्ठा *);
व्योम aoecmd_wreset(काष्ठा aoetgt *t);
व्योम aoecmd_cleanslate(काष्ठा aoedev *);
व्योम aoecmd_निकास(व्योम);
पूर्णांक aoecmd_init(व्योम);
काष्ठा sk_buff *aoecmd_ata_id(काष्ठा aoedev *);
व्योम aoe_मुक्तtframe(काष्ठा frame *);
व्योम aoe_flush_iocq(व्योम);
व्योम aoe_flush_iocq_by_index(पूर्णांक);
व्योम aoe_end_request(काष्ठा aoedev *, काष्ठा request *, पूर्णांक);
पूर्णांक aoe_ktstart(काष्ठा ktstate *k);
व्योम aoe_ktstop(काष्ठा ktstate *k);

पूर्णांक aoedev_init(व्योम);
व्योम aoedev_निकास(व्योम);
काष्ठा aoedev *aoedev_by_aoeaddr(uदीर्घ maj, पूर्णांक min, पूर्णांक करो_alloc);
व्योम aoedev_करोwndev(काष्ठा aoedev *d);
पूर्णांक aoedev_flush(स्थिर अक्षर __user *str, माप_प्रकार size);
व्योम aoe_failbuf(काष्ठा aoedev *, काष्ठा buf *);
व्योम aoedev_put(काष्ठा aoedev *);

पूर्णांक aoenet_init(व्योम);
व्योम aoenet_निकास(व्योम);
व्योम aoenet_xmit(काष्ठा sk_buff_head *);
पूर्णांक is_aoe_netअगर(काष्ठा net_device *अगरp);
पूर्णांक set_aoe_अगरlist(स्थिर अक्षर __user *str, माप_प्रकार size);
