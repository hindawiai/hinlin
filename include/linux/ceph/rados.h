<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CEPH_RADOS_H
#घोषणा CEPH_RADOS_H

/*
 * Data types क्रम the Ceph distributed object storage layer RADOS
 * (Reliable Autonomic Distributed Object Store).
 */

#समावेश <linux/ceph/msgr.h>

/*
 * fs id
 */
काष्ठा ceph_fsid अणु
	अचिन्हित अक्षर fsid[16];
पूर्ण;

अटल अंतरभूत पूर्णांक ceph_fsid_compare(स्थिर काष्ठा ceph_fsid *a,
				    स्थिर काष्ठा ceph_fsid *b)
अणु
	वापस स_भेद(a, b, माप(*a));
पूर्ण

/*
 * ino, object, etc.
 */
प्रकार __le64 ceph_snapid_t;
#घोषणा CEPH_SNAPसूची ((__u64)(-1))  /* reserved क्रम hidden .snap dir */
#घोषणा CEPH_NOSNAP  ((__u64)(-2))  /* "head", "live" revision */
#घोषणा CEPH_MAXSNAP ((__u64)(-3))  /* largest valid snapid */

काष्ठा ceph_बारpec अणु
	__le32 tv_sec;
	__le32 tv_nsec;
पूर्ण __attribute__ ((packed));


/*
 * object layout - how objects are mapped पूर्णांकo PGs
 */
#घोषणा CEPH_OBJECT_LAYOUT_HASH     1
#घोषणा CEPH_OBJECT_LAYOUT_LINEAR   2
#घोषणा CEPH_OBJECT_LAYOUT_HASHINO  3

/*
 * pg layout -- how PGs are mapped onto (sets of) OSDs
 */
#घोषणा CEPH_PG_LAYOUT_CRUSH  0
#घोषणा CEPH_PG_LAYOUT_HASH   1
#घोषणा CEPH_PG_LAYOUT_LINEAR 2
#घोषणा CEPH_PG_LAYOUT_HYBRID 3

#घोषणा CEPH_PG_MAX_SIZE      32  /* max # osds in a single pg */

/*
 * placement group.
 * we encode this पूर्णांकo one __le64.
 */
काष्ठा ceph_pg_v1 अणु
	__le16 preferred; /* preferred primary osd */
	__le16 ps;        /* placement seed */
	__le32 pool;      /* object pool */
पूर्ण __attribute__ ((packed));

/*
 * pg_pool is a set of pgs storing a pool of objects
 *
 *  pg_num -- base number of pseuकरोअक्रमomly placed pgs
 *
 *  pgp_num -- effective number when calculating pg placement.  this
 * is used क्रम pg_num increases.  new pgs result in data being "split"
 * पूर्णांकo new pgs.  क्रम this to proceed smoothly, new pgs are पूर्णांकiially
 * colocated with their parents; that is, pgp_num करोesn't increase
 * until the new pgs have successfully split.  only _then_ are the new
 * pgs placed independently.
 *
 *  lpg_num -- localized pg count (per device).  replicas are अक्रमomly
 * selected.
 *
 *  lpgp_num -- as above.
 */
#घोषणा CEPH_NOPOOL  ((__u64) (-1))  /* pool id not defined */

#घोषणा CEPH_POOL_TYPE_REP     1
#घोषणा CEPH_POOL_TYPE_RAID4   2 /* never implemented */
#घोषणा CEPH_POOL_TYPE_EC      3

/*
 * stable_mod func is used to control number of placement groups.
 * similar to straight-up modulo, but produces a stable mapping as b
 * increases over समय.  b is the number of bins, and bmask is the
 * containing घातer of 2 minus 1.
 *
 * b <= bmask and bmask=(2**n)-1
 * e.g., b=12 -> bmask=15, b=123 -> bmask=127
 */
अटल अंतरभूत पूर्णांक ceph_stable_mod(पूर्णांक x, पूर्णांक b, पूर्णांक bmask)
अणु
	अगर ((x & bmask) < b)
		वापस x & bmask;
	अन्यथा
		वापस x & (bmask >> 1);
पूर्ण

/*
 * object layout - how a given object should be stored.
 */
काष्ठा ceph_object_layout अणु
	काष्ठा ceph_pg_v1 ol_pgid;   /* raw pg, with _full_ ps precision. */
	__le32 ol_stripe_unit;    /* क्रम per-object parity, अगर any */
पूर्ण __attribute__ ((packed));

/*
 * compound epoch+version, used by storage layer to serialize mutations
 */
काष्ठा ceph_eversion अणु
	__le64 version;
	__le32 epoch;
पूर्ण __attribute__ ((packed));

/*
 * osd map bits
 */

/* status bits */
#घोषणा CEPH_OSD_EXISTS  (1<<0)
#घोषणा CEPH_OSD_UP      (1<<1)
#घोषणा CEPH_OSD_AUTOOUT (1<<2)  /* osd was स्वतःmatically marked out */
#घोषणा CEPH_OSD_NEW     (1<<3)  /* osd is new, never marked in */

बाह्य स्थिर अक्षर *ceph_osd_state_name(पूर्णांक s);

/* osd weights.  fixed poपूर्णांक value: 0x10000 == 1.0 ("in"), 0 == "out" */
#घोषणा CEPH_OSD_IN  0x10000
#घोषणा CEPH_OSD_OUT 0

/* osd primary-affinity.  fixed poपूर्णांक value: 0x10000 == baseline */
#घोषणा CEPH_OSD_MAX_PRIMARY_AFFINITY 0x10000
#घोषणा CEPH_OSD_DEFAULT_PRIMARY_AFFINITY 0x10000


/*
 * osd map flag bits
 */
#घोषणा CEPH_OSDMAP_NEARFULL (1<<0)  /* sync ग_लिखोs (near ENOSPC),
					not set since ~luminous */
#घोषणा CEPH_OSDMAP_FULL     (1<<1)  /* no data ग_लिखोs (ENOSPC),
					not set since ~luminous */
#घोषणा CEPH_OSDMAP_PAUSERD  (1<<2)  /* छोड़ो all पढ़ोs */
#घोषणा CEPH_OSDMAP_PAUSEWR  (1<<3)  /* छोड़ो all ग_लिखोs */
#घोषणा CEPH_OSDMAP_PAUSEREC (1<<4)  /* छोड़ो recovery */
#घोषणा CEPH_OSDMAP_NOUP     (1<<5)  /* block osd boot */
#घोषणा CEPH_OSDMAP_NODOWN   (1<<6)  /* block osd mark-करोwn/failure */
#घोषणा CEPH_OSDMAP_NOOUT    (1<<7)  /* block osd स्वतः mark-out */
#घोषणा CEPH_OSDMAP_NOIN     (1<<8)  /* block osd स्वतः mark-in */
#घोषणा CEPH_OSDMAP_NOBACKFILL (1<<9) /* block osd backfill */
#घोषणा CEPH_OSDMAP_NORECOVER (1<<10) /* block osd recovery and backfill */
#घोषणा CEPH_OSDMAP_NOSCRUB  (1<<11) /* block periodic scrub */
#घोषणा CEPH_OSDMAP_NODEEP_SCRUB (1<<12) /* block periodic deep-scrub */
#घोषणा CEPH_OSDMAP_NOTIERAGENT (1<<13) /* disable tiering agent */
#घोषणा CEPH_OSDMAP_NOREBALANCE (1<<14) /* block osd backfill unless pg is degraded */
#घोषणा CEPH_OSDMAP_SORTBITWISE (1<<15) /* use bitwise hobject_t sort */
#घोषणा CEPH_OSDMAP_REQUIRE_JEWEL    (1<<16) /* require jewel क्रम booting osds */
#घोषणा CEPH_OSDMAP_REQUIRE_KRAKEN   (1<<17) /* require kraken क्रम booting osds */
#घोषणा CEPH_OSDMAP_REQUIRE_LUMINOUS (1<<18) /* require l क्रम booting osds */
#घोषणा CEPH_OSDMAP_RECOVERY_DELETES (1<<19) /* deletes perक्रमmed during recovery instead of peering */

/*
 * The error code to वापस when an OSD can't handle a ग_लिखो
 * because it is too large.
 */
#घोषणा OSD_WRITETOOBIG EMSGSIZE

/*
 * osd ops
 *
 * WARNING: करो not use these op codes directly.  Use the helpers
 * defined below instead.  In certain हालs, op code behavior was
 * redefined, resulting in special-हालs in the helpers.
 */
#घोषणा CEPH_OSD_OP_MODE       0xf000
#घोषणा CEPH_OSD_OP_MODE_RD    0x1000
#घोषणा CEPH_OSD_OP_MODE_WR    0x2000
#घोषणा CEPH_OSD_OP_MODE_RMW   0x3000
#घोषणा CEPH_OSD_OP_MODE_SUB   0x4000
#घोषणा CEPH_OSD_OP_MODE_CACHE 0x8000

#घोषणा CEPH_OSD_OP_TYPE       0x0f00
#घोषणा CEPH_OSD_OP_TYPE_LOCK  0x0100
#घोषणा CEPH_OSD_OP_TYPE_DATA  0x0200
#घोषणा CEPH_OSD_OP_TYPE_ATTR  0x0300
#घोषणा CEPH_OSD_OP_TYPE_EXEC  0x0400
#घोषणा CEPH_OSD_OP_TYPE_PG    0x0500
#घोषणा CEPH_OSD_OP_TYPE_MULTI 0x0600 /* multiobject */

#घोषणा __CEPH_OSD_OP1(mode, nr) \
	(CEPH_OSD_OP_MODE_##mode | (nr))

#घोषणा __CEPH_OSD_OP(mode, type, nr) \
	(CEPH_OSD_OP_MODE_##mode | CEPH_OSD_OP_TYPE_##type | (nr))

#घोषणा __CEPH_FORALL_OSD_OPS(f)					    \
	/** data **/							    \
	/* पढ़ो */							    \
	f(READ,		__CEPH_OSD_OP(RD, DATA, 1),	"read")		    \
	f(STAT,		__CEPH_OSD_OP(RD, DATA, 2),	"stat")		    \
	f(MAPEXT,	__CEPH_OSD_OP(RD, DATA, 3),	"mapext")	    \
									    \
	/* fancy पढ़ो */						    \
	f(MASKTRUNC,	__CEPH_OSD_OP(RD, DATA, 4),	"masktrunc")	    \
	f(SPARSE_READ,	__CEPH_OSD_OP(RD, DATA, 5),	"sparse-read")	    \
									    \
	f(NOTIFY,	__CEPH_OSD_OP(RD, DATA, 6),	"notify")	    \
	f(NOTIFY_ACK,	__CEPH_OSD_OP(RD, DATA, 7),	"notify-ack")	    \
									    \
	/* versioning */						    \
	f(ASSERT_VER,	__CEPH_OSD_OP(RD, DATA, 8),	"assert-version")   \
									    \
	f(LIST_WATCHERS, __CEPH_OSD_OP(RD, DATA, 9),	"list-watchers")    \
									    \
	f(LIST_SNAPS,	__CEPH_OSD_OP(RD, DATA, 10),	"list-snaps")	    \
									    \
	/* sync */							    \
	f(SYNC_READ,	__CEPH_OSD_OP(RD, DATA, 11),	"sync_read")	    \
									    \
	/* ग_लिखो */							    \
	f(WRITE,	__CEPH_OSD_OP(WR, DATA, 1),	"write")	    \
	f(WRITEFULL,	__CEPH_OSD_OP(WR, DATA, 2),	"writefull")	    \
	f(TRUNCATE,	__CEPH_OSD_OP(WR, DATA, 3),	"truncate")	    \
	f(ZERO,		__CEPH_OSD_OP(WR, DATA, 4),	"zero")		    \
	f(DELETE,	__CEPH_OSD_OP(WR, DATA, 5),	"delete")	    \
									    \
	/* fancy ग_लिखो */						    \
	f(APPEND,	__CEPH_OSD_OP(WR, DATA, 6),	"append")	    \
	f(SETTRUNC,	__CEPH_OSD_OP(WR, DATA, 8),	"settrunc")	    \
	f(TRIMTRUNC,	__CEPH_OSD_OP(WR, DATA, 9),	"trimtrunc")	    \
									    \
	f(TMAPUP,	__CEPH_OSD_OP(RMW, DATA, 10),	"tmapup")	    \
	f(TMAPPUT,	__CEPH_OSD_OP(WR, DATA, 11),	"tmapput")	    \
	f(TMAPGET,	__CEPH_OSD_OP(RD, DATA, 12),	"tmapget")	    \
									    \
	f(CREATE,	__CEPH_OSD_OP(WR, DATA, 13),	"create")	    \
	f(ROLLBACK,	__CEPH_OSD_OP(WR, DATA, 14),	"rollback")	    \
									    \
	f(WATCH,	__CEPH_OSD_OP(WR, DATA, 15),	"watch")	    \
									    \
	/* omap */							    \
	f(OMAPGETKEYS,	__CEPH_OSD_OP(RD, DATA, 17),	"omap-get-keys")    \
	f(OMAPGETVALS,	__CEPH_OSD_OP(RD, DATA, 18),	"omap-get-vals")    \
	f(OMAPGETHEADER, __CEPH_OSD_OP(RD, DATA, 19),	"omap-get-header")  \
	f(OMAPGETVALSBYKEYS, __CEPH_OSD_OP(RD, DATA, 20), "omap-get-vals-by-keys") \
	f(OMAPSETVALS,	__CEPH_OSD_OP(WR, DATA, 21),	"omap-set-vals")    \
	f(OMAPSETHEADER, __CEPH_OSD_OP(WR, DATA, 22),	"omap-set-header")  \
	f(OMAPCLEAR,	__CEPH_OSD_OP(WR, DATA, 23),	"omap-clear")	    \
	f(OMAPRMKEYS,	__CEPH_OSD_OP(WR, DATA, 24),	"omap-rm-keys")	    \
	f(OMAP_CMP,	__CEPH_OSD_OP(RD, DATA, 25),	"omap-cmp")	    \
									    \
	/* tiering */							    \
	f(COPY_FROM,	__CEPH_OSD_OP(WR, DATA, 26),	"copy-from")	    \
	f(COPY_FROM2,	__CEPH_OSD_OP(WR, DATA, 45),	"copy-from2")	    \
	f(COPY_GET_CLASSIC, __CEPH_OSD_OP(RD, DATA, 27), "copy-get-classic") \
	f(UNसूचीTY,	__CEPH_OSD_OP(WR, DATA, 28),	"undirty")	    \
	f(ISसूचीTY,	__CEPH_OSD_OP(RD, DATA, 29),	"isdirty")	    \
	f(COPY_GET,	__CEPH_OSD_OP(RD, DATA, 30),	"copy-get")	    \
	f(CACHE_FLUSH,	__CEPH_OSD_OP(CACHE, DATA, 31),	"cache-flush")	    \
	f(CACHE_EVICT,	__CEPH_OSD_OP(CACHE, DATA, 32),	"cache-evict")	    \
	f(CACHE_TRY_FLUSH, __CEPH_OSD_OP(CACHE, DATA, 33), "cache-try-flush") \
									    \
	/* convert पंचांगap to omap */					    \
	f(TMAP2OMAP,	__CEPH_OSD_OP(RMW, DATA, 34),	"tmap2omap")	    \
									    \
	/* hपूर्णांकs */							    \
	f(SETALLOCHINT,	__CEPH_OSD_OP(WR, DATA, 35),	"set-alloc-hint")   \
									    \
	/** multi **/							    \
	f(CLONदुस्फल,	__CEPH_OSD_OP(WR, MULTI, 1),	"clonerange")	    \
	f(ASSERT_SRC_VERSION, __CEPH_OSD_OP(RD, MULTI, 2), "assert-src-version") \
	f(SRC_CMPXATTR,	__CEPH_OSD_OP(RD, MULTI, 3),	"src-cmpxattr")	    \
									    \
	/** attrs **/							    \
	/* पढ़ो */							    \
	f(GETXATTR,	__CEPH_OSD_OP(RD, ATTR, 1),	"getxattr")	    \
	f(GETXATTRS,	__CEPH_OSD_OP(RD, ATTR, 2),	"getxattrs")	    \
	f(CMPXATTR,	__CEPH_OSD_OP(RD, ATTR, 3),	"cmpxattr")	    \
									    \
	/* ग_लिखो */							    \
	f(SETXATTR,	__CEPH_OSD_OP(WR, ATTR, 1),	"setxattr")	    \
	f(SETXATTRS,	__CEPH_OSD_OP(WR, ATTR, 2),	"setxattrs")	    \
	f(RESETXATTRS,	__CEPH_OSD_OP(WR, ATTR, 3),	"resetxattrs")	    \
	f(RMXATTR,	__CEPH_OSD_OP(WR, ATTR, 4),	"rmxattr")	    \
									    \
	/** subop **/							    \
	f(PULL,		__CEPH_OSD_OP1(SUB, 1),		"pull")		    \
	f(PUSH,		__CEPH_OSD_OP1(SUB, 2),		"push")		    \
	f(BALANCEREADS,	__CEPH_OSD_OP1(SUB, 3),		"balance-reads")    \
	f(UNBALANCEREADS, __CEPH_OSD_OP1(SUB, 4),	"unbalance-reads")  \
	f(SCRUB,	__CEPH_OSD_OP1(SUB, 5),		"scrub")	    \
	f(SCRUB_RESERVE, __CEPH_OSD_OP1(SUB, 6),	"scrub-reserve")    \
	f(SCRUB_UNRESERVE, __CEPH_OSD_OP1(SUB, 7),	"scrub-unreserve")  \
	f(SCRUB_STOP,	__CEPH_OSD_OP1(SUB, 8),		"scrub-stop")	    \
	f(SCRUB_MAP,	__CEPH_OSD_OP1(SUB, 9),		"scrub-map")	    \
									    \
	/** lock **/							    \
	f(WRLOCK,	__CEPH_OSD_OP(WR, LOCK, 1),	"wrlock")	    \
	f(WRUNLOCK,	__CEPH_OSD_OP(WR, LOCK, 2),	"wrunlock")	    \
	f(RDLOCK,	__CEPH_OSD_OP(WR, LOCK, 3),	"rdlock")	    \
	f(RDUNLOCK,	__CEPH_OSD_OP(WR, LOCK, 4),	"rdunlock")	    \
	f(UPLOCK,	__CEPH_OSD_OP(WR, LOCK, 5),	"uplock")	    \
	f(DNLOCK,	__CEPH_OSD_OP(WR, LOCK, 6),	"dnlock")	    \
									    \
	/** exec **/							    \
	/* note: the RD bit here is wrong; see special-हाल below in helper */ \
	f(CALL,		__CEPH_OSD_OP(RD, EXEC, 1),	"call")		    \
									    \
	/** pg **/							    \
	f(PGLS,		__CEPH_OSD_OP(RD, PG, 1),	"pgls")		    \
	f(PGLS_FILTER,	__CEPH_OSD_OP(RD, PG, 2),	"pgls-filter")	    \
	f(PG_HITSET_LS,	__CEPH_OSD_OP(RD, PG, 3),	"pg-hitset-ls")	    \
	f(PG_HITSET_GET, __CEPH_OSD_OP(RD, PG, 4),	"pg-hitset-get")

क्रमागत अणु
#घोषणा GENERATE_ENUM_ENTRY(op, opcode, str)	CEPH_OSD_OP_##op = (opcode),
__CEPH_FORALL_OSD_OPS(GENERATE_ENUM_ENTRY)
#अघोषित GENERATE_ENUM_ENTRY
पूर्ण;

अटल अंतरभूत पूर्णांक ceph_osd_op_type_lock(पूर्णांक op)
अणु
	वापस (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_LOCK;
पूर्ण
अटल अंतरभूत पूर्णांक ceph_osd_op_type_data(पूर्णांक op)
अणु
	वापस (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_DATA;
पूर्ण
अटल अंतरभूत पूर्णांक ceph_osd_op_type_attr(पूर्णांक op)
अणु
	वापस (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_ATTR;
पूर्ण
अटल अंतरभूत पूर्णांक ceph_osd_op_type_exec(पूर्णांक op)
अणु
	वापस (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_EXEC;
पूर्ण
अटल अंतरभूत पूर्णांक ceph_osd_op_type_pg(पूर्णांक op)
अणु
	वापस (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_PG;
पूर्ण
अटल अंतरभूत पूर्णांक ceph_osd_op_type_multi(पूर्णांक op)
अणु
	वापस (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_MULTI;
पूर्ण

अटल अंतरभूत पूर्णांक ceph_osd_op_mode_subop(पूर्णांक op)
अणु
	वापस (op & CEPH_OSD_OP_MODE) == CEPH_OSD_OP_MODE_SUB;
पूर्ण
अटल अंतरभूत पूर्णांक ceph_osd_op_mode_पढ़ो(पूर्णांक op)
अणु
	वापस (op & CEPH_OSD_OP_MODE_RD) &&
		op != CEPH_OSD_OP_CALL;
पूर्ण
अटल अंतरभूत पूर्णांक ceph_osd_op_mode_modअगरy(पूर्णांक op)
अणु
	वापस op & CEPH_OSD_OP_MODE_WR;
पूर्ण

/*
 * note that the following पंचांगap stuff is also defined in the ceph libraडॉस.स
 * any modअगरication here needs to be updated there
 */
#घोषणा CEPH_OSD_TMAP_HDR 'h'
#घोषणा CEPH_OSD_TMAP_SET 's'
#घोषणा CEPH_OSD_TMAP_CREATE 'c' /* create key */
#घोषणा CEPH_OSD_TMAP_RM  'r'
#घोषणा CEPH_OSD_TMAP_RMSLOPPY 'R'

बाह्य स्थिर अक्षर *ceph_osd_op_name(पूर्णांक op);

/*
 * osd op flags
 *
 * An op may be READ, WRITE, or READ|WRITE.
 */
क्रमागत अणु
	CEPH_OSD_FLAG_ACK =            0x0001,  /* want (or is) "ack" ack */
	CEPH_OSD_FLAG_ONNVRAM =        0x0002,  /* want (or is) "onnvram" ack */
	CEPH_OSD_FLAG_ONDISK =         0x0004,  /* want (or is) "ondisk" ack */
	CEPH_OSD_FLAG_RETRY =          0x0008,  /* resend attempt */
	CEPH_OSD_FLAG_READ =           0x0010,  /* op may पढ़ो */
	CEPH_OSD_FLAG_WRITE =          0x0020,  /* op may ग_लिखो */
	CEPH_OSD_FLAG_ORDERSNAP =      0x0040,  /* EOLDSNAP अगर snapc is out of order */
	CEPH_OSD_FLAG_PEERSTAT_OLD =   0x0080,  /* DEPRECATED msg includes osd_peer_stat */
	CEPH_OSD_FLAG_BALANCE_READS =  0x0100,
	CEPH_OSD_FLAG_PARALLELEXEC =   0x0200,  /* execute op in parallel */
	CEPH_OSD_FLAG_PGOP =           0x0400,  /* pg op, no object */
	CEPH_OSD_FLAG_EXEC =           0x0800,  /* op may exec */
	CEPH_OSD_FLAG_EXEC_PUBLIC =    0x1000,  /* DEPRECATED op may exec (खुला) */
	CEPH_OSD_FLAG_LOCALIZE_READS = 0x2000,  /* पढ़ो from nearby replica, अगर any */
	CEPH_OSD_FLAG_RWORDERED =      0x4000,  /* order wrt concurrent पढ़ोs */
	CEPH_OSD_FLAG_IGNORE_CACHE =   0x8000,  /* ignore cache logic */
	CEPH_OSD_FLAG_SKIPRWLOCKS =   0x10000,  /* skip rw locks */
	CEPH_OSD_FLAG_IGNORE_OVERLAY = 0x20000, /* ignore pool overlay */
	CEPH_OSD_FLAG_FLUSH =         0x40000,  /* this is part of flush */
	CEPH_OSD_FLAG_MAP_SNAP_CLONE = 0x80000,  /* map snap direct to clone id */
	CEPH_OSD_FLAG_ENFORCE_SNAPC   = 0x100000,  /* use snapc provided even अगर
						      pool uses pool snaps */
	CEPH_OSD_FLAG_REसूचीECTED   = 0x200000,  /* op has been redirected */
	CEPH_OSD_FLAG_KNOWN_REसूची = 0x400000,  /* redirect bit is authoritative */
	CEPH_OSD_FLAG_FULL_TRY =    0x800000,  /* try op despite full flag */
	CEPH_OSD_FLAG_FULL_FORCE = 0x1000000,  /* क्रमce op despite full flag */
पूर्ण;

क्रमागत अणु
	CEPH_OSD_OP_FLAG_EXCL = 1,      /* EXCL object create */
	CEPH_OSD_OP_FLAG_FAILOK = 2,    /* जारी despite failure */
	CEPH_OSD_OP_FLAG_FADVISE_RANDOM	    = 0x4, /* the op is अक्रमom */
	CEPH_OSD_OP_FLAG_FADVISE_SEQUENTIAL = 0x8, /* the op is sequential */
	CEPH_OSD_OP_FLAG_FADVISE_WILLNEED   = 0x10,/* data will be accessed in
						      the near future */
	CEPH_OSD_OP_FLAG_FADVISE_DONTNEED   = 0x20,/* data will not be accessed
						      in the near future */
	CEPH_OSD_OP_FLAG_FADVISE_NOCACHE    = 0x40,/* data will be accessed only
						      once by this client */
पूर्ण;

#घोषणा EOLDSNAPC    ERESTART  /* ORDERSNAP flag set; ग_लिखोr has old snapc*/
#घोषणा EBLOCKLISTED ESHUTDOWN /* blocklisted */

/* xattr comparison */
क्रमागत अणु
	CEPH_OSD_CMPXATTR_OP_NOP = 0,
	CEPH_OSD_CMPXATTR_OP_EQ  = 1,
	CEPH_OSD_CMPXATTR_OP_NE  = 2,
	CEPH_OSD_CMPXATTR_OP_GT  = 3,
	CEPH_OSD_CMPXATTR_OP_GTE = 4,
	CEPH_OSD_CMPXATTR_OP_LT  = 5,
	CEPH_OSD_CMPXATTR_OP_LTE = 6
पूर्ण;

क्रमागत अणु
	CEPH_OSD_CMPXATTR_MODE_STRING = 1,
	CEPH_OSD_CMPXATTR_MODE_U64    = 2
पूर्ण;

क्रमागत अणु
	CEPH_OSD_COPY_FROM_FLAG_FLUSH = 1,       /* part of a flush operation */
	CEPH_OSD_COPY_FROM_FLAG_IGNORE_OVERLAY = 2, /* ignore pool overlay */
	CEPH_OSD_COPY_FROM_FLAG_IGNORE_CACHE = 4,   /* ignore osd cache logic */
	CEPH_OSD_COPY_FROM_FLAG_MAP_SNAP_CLONE = 8, /* map snap direct to
						     * cloneid */
	CEPH_OSD_COPY_FROM_FLAG_RWORDERED = 16,     /* order with ग_लिखो */
	CEPH_OSD_COPY_FROM_FLAG_TRUNCATE_SEQ = 32,  /* send truncate_अणुseq,sizeपूर्ण */
पूर्ण;

क्रमागत अणु
	CEPH_OSD_WATCH_OP_UNWATCH = 0,
	CEPH_OSD_WATCH_OP_LEGACY_WATCH = 1,
	/* note: use only ODD ids to prevent pre-giant code from
	   पूर्णांकerpreting the op as UNWATCH */
	CEPH_OSD_WATCH_OP_WATCH = 3,
	CEPH_OSD_WATCH_OP_RECONNECT = 5,
	CEPH_OSD_WATCH_OP_PING = 7,
पूर्ण;

स्थिर अक्षर *ceph_osd_watch_op_name(पूर्णांक o);

क्रमागत अणु
	CEPH_OSD_ALLOC_HINT_FLAG_SEQUENTIAL_WRITE = 1,
	CEPH_OSD_ALLOC_HINT_FLAG_RANDOM_WRITE = 2,
	CEPH_OSD_ALLOC_HINT_FLAG_SEQUENTIAL_READ = 4,
	CEPH_OSD_ALLOC_HINT_FLAG_RANDOM_READ = 8,
	CEPH_OSD_ALLOC_HINT_FLAG_APPEND_ONLY = 16,
	CEPH_OSD_ALLOC_HINT_FLAG_IMMUTABLE = 32,
	CEPH_OSD_ALLOC_HINT_FLAG_SHORTLIVED = 64,
	CEPH_OSD_ALLOC_HINT_FLAG_LONGLIVED = 128,
	CEPH_OSD_ALLOC_HINT_FLAG_COMPRESSIBLE = 256,
	CEPH_OSD_ALLOC_HINT_FLAG_INCOMPRESSIBLE = 512,
पूर्ण;

क्रमागत अणु
	CEPH_OSD_BACKOFF_OP_BLOCK = 1,
	CEPH_OSD_BACKOFF_OP_ACK_BLOCK = 2,
	CEPH_OSD_BACKOFF_OP_UNBLOCK = 3,
पूर्ण;

/*
 * an inभागidual object operation.  each may be accompanied by some data
 * payload
 */
काष्ठा ceph_osd_op अणु
	__le16 op;           /* CEPH_OSD_OP_* */
	__le32 flags;        /* CEPH_OSD_OP_FLAG_* */
	जोड़ अणु
		काष्ठा अणु
			__le64 offset, length;
			__le64 truncate_size;
			__le32 truncate_seq;
		पूर्ण __attribute__ ((packed)) extent;
		काष्ठा अणु
			__le32 name_len;
			__le32 value_len;
			__u8 cmp_op;       /* CEPH_OSD_CMPXATTR_OP_* */
			__u8 cmp_mode;     /* CEPH_OSD_CMPXATTR_MODE_* */
		पूर्ण __attribute__ ((packed)) xattr;
		काष्ठा अणु
			__u8 class_len;
			__u8 method_len;
			__u8 argc;
			__le32 indata_len;
		पूर्ण __attribute__ ((packed)) cls;
		काष्ठा अणु
			__le64 cookie, count;
		पूर्ण __attribute__ ((packed)) pgls;
	        काष्ठा अणु
		        __le64 snapid;
	        पूर्ण __attribute__ ((packed)) snap;
		काष्ठा अणु
			__le64 cookie;
			__le64 ver;     /* no दीर्घer used */
			__u8 op;	/* CEPH_OSD_WATCH_OP_* */
			__le32 gen;     /* registration generation */
		पूर्ण __attribute__ ((packed)) watch;
		काष्ठा अणु
			__le64 cookie;
		पूर्ण __attribute__ ((packed)) notअगरy;
		काष्ठा अणु
			__le64 offset, length;
			__le64 src_offset;
		पूर्ण __attribute__ ((packed)) clonerange;
		काष्ठा अणु
			__le64 expected_object_size;
			__le64 expected_ग_लिखो_size;
			__le32 flags;  /* CEPH_OSD_OP_ALLOC_HINT_FLAG_* */
		पूर्ण __attribute__ ((packed)) alloc_hपूर्णांक;
		काष्ठा अणु
			__le64 snapid;
			__le64 src_version;
			__u8 flags; /* CEPH_OSD_COPY_FROM_FLAG_* */
			/*
			 * CEPH_OSD_OP_FLAG_FADVISE_*: fadvise flags
			 * क्रम src object, flags क्रम dest object are in
			 * ceph_osd_op::flags.
			 */
			__le32 src_fadvise_flags;
		पूर्ण __attribute__ ((packed)) copy_from;
	पूर्ण;
	__le32 payload_len;
पूर्ण __attribute__ ((packed));


#पूर्ण_अगर
