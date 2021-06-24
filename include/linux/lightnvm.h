<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित NVM_H
#घोषणा NVM_H

#समावेश <linux/blkdev.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/lightnvm.h>

क्रमागत अणु
	NVM_IO_OK = 0,
	NVM_IO_REQUEUE = 1,
	NVM_IO_DONE = 2,
	NVM_IO_ERR = 3,

	NVM_IOTYPE_NONE = 0,
	NVM_IOTYPE_GC = 1,
पूर्ण;

/* common क्रमmat */
#घोषणा NVM_GEN_CH_BITS  (8)
#घोषणा NVM_GEN_LUN_BITS (8)
#घोषणा NVM_GEN_BLK_BITS (16)
#घोषणा NVM_GEN_RESERVED (32)

/* 1.2 क्रमmat */
#घोषणा NVM_12_PG_BITS  (16)
#घोषणा NVM_12_PL_BITS  (4)
#घोषणा NVM_12_SEC_BITS (4)
#घोषणा NVM_12_RESERVED (8)

/* 2.0 क्रमmat */
#घोषणा NVM_20_SEC_BITS (24)
#घोषणा NVM_20_RESERVED (8)

क्रमागत अणु
	NVM_OCSSD_SPEC_12 = 12,
	NVM_OCSSD_SPEC_20 = 20,
पूर्ण;

काष्ठा ppa_addr अणु
	/* Generic काष्ठाure क्रम all addresses */
	जोड़ अणु
		/* generic device क्रमmat */
		काष्ठा अणु
			u64 ch		: NVM_GEN_CH_BITS;
			u64 lun		: NVM_GEN_LUN_BITS;
			u64 blk		: NVM_GEN_BLK_BITS;
			u64 reserved	: NVM_GEN_RESERVED;
		पूर्ण a;

		/* 1.2 device क्रमmat */
		काष्ठा अणु
			u64 ch		: NVM_GEN_CH_BITS;
			u64 lun		: NVM_GEN_LUN_BITS;
			u64 blk		: NVM_GEN_BLK_BITS;
			u64 pg		: NVM_12_PG_BITS;
			u64 pl		: NVM_12_PL_BITS;
			u64 sec		: NVM_12_SEC_BITS;
			u64 reserved	: NVM_12_RESERVED;
		पूर्ण g;

		/* 2.0 device क्रमmat */
		काष्ठा अणु
			u64 grp		: NVM_GEN_CH_BITS;
			u64 pu		: NVM_GEN_LUN_BITS;
			u64 chk		: NVM_GEN_BLK_BITS;
			u64 sec		: NVM_20_SEC_BITS;
			u64 reserved	: NVM_20_RESERVED;
		पूर्ण m;

		काष्ठा अणु
			u64 line	: 63;
			u64 is_cached	: 1;
		पूर्ण c;

		u64 ppa;
	पूर्ण;
पूर्ण;

काष्ठा nvm_rq;
काष्ठा nvm_id;
काष्ठा nvm_dev;
काष्ठा nvm_tgt_dev;
काष्ठा nvm_chk_meta;

प्रकार पूर्णांक (nvm_id_fn)(काष्ठा nvm_dev *);
प्रकार पूर्णांक (nvm_op_bb_tbl_fn)(काष्ठा nvm_dev *, काष्ठा ppa_addr, u8 *);
प्रकार पूर्णांक (nvm_op_set_bb_fn)(काष्ठा nvm_dev *, काष्ठा ppa_addr *, पूर्णांक, पूर्णांक);
प्रकार पूर्णांक (nvm_get_chk_meta_fn)(काष्ठा nvm_dev *, sector_t, पूर्णांक,
							काष्ठा nvm_chk_meta *);
प्रकार पूर्णांक (nvm_submit_io_fn)(काष्ठा nvm_dev *, काष्ठा nvm_rq *, व्योम *);
प्रकार व्योम *(nvm_create_dma_pool_fn)(काष्ठा nvm_dev *, अक्षर *, पूर्णांक);
प्रकार व्योम (nvm_destroy_dma_pool_fn)(व्योम *);
प्रकार व्योम *(nvm_dev_dma_alloc_fn)(काष्ठा nvm_dev *, व्योम *, gfp_t,
								dma_addr_t *);
प्रकार व्योम (nvm_dev_dma_मुक्त_fn)(व्योम *, व्योम*, dma_addr_t);

काष्ठा nvm_dev_ops अणु
	nvm_id_fn		*identity;
	nvm_op_bb_tbl_fn	*get_bb_tbl;
	nvm_op_set_bb_fn	*set_bb_tbl;

	nvm_get_chk_meta_fn	*get_chk_meta;

	nvm_submit_io_fn	*submit_io;

	nvm_create_dma_pool_fn	*create_dma_pool;
	nvm_destroy_dma_pool_fn	*destroy_dma_pool;
	nvm_dev_dma_alloc_fn	*dev_dma_alloc;
	nvm_dev_dma_मुक्त_fn	*dev_dma_मुक्त;
पूर्ण;

#अगर_घोषित CONFIG_NVM

#समावेश <linux/file.h>
#समावेश <linux/dmapool.h>

क्रमागत अणु
	/* HW Responsibilities */
	NVM_RSP_L2P	= 1 << 0,
	NVM_RSP_ECC	= 1 << 1,

	/* Physical Adressing Mode */
	NVM_ADDRMODE_LINEAR	= 0,
	NVM_ADDRMODE_CHANNEL	= 1,

	/* Plane programming mode क्रम LUN */
	NVM_PLANE_SINGLE	= 1,
	NVM_PLANE_DOUBLE	= 2,
	NVM_PLANE_QUAD		= 4,

	/* Status codes */
	NVM_RSP_SUCCESS		= 0x0,
	NVM_RSP_NOT_CHANGEABLE	= 0x1,
	NVM_RSP_ERR_FAILWRITE	= 0x40ff,
	NVM_RSP_ERR_EMPTYPAGE	= 0x42ff,
	NVM_RSP_ERR_FAILECC	= 0x4281,
	NVM_RSP_ERR_FAILCRC	= 0x4004,
	NVM_RSP_WARN_HIGHECC	= 0x4700,

	/* Device opcodes */
	NVM_OP_PWRITE		= 0x91,
	NVM_OP_PREAD		= 0x92,
	NVM_OP_ERASE		= 0x90,

	/* PPA Command Flags */
	NVM_IO_SNGL_ACCESS	= 0x0,
	NVM_IO_DUAL_ACCESS	= 0x1,
	NVM_IO_QUAD_ACCESS	= 0x2,

	/* न_अंकD Access Modes */
	NVM_IO_SUSPEND		= 0x80,
	NVM_IO_SLC_MODE		= 0x100,
	NVM_IO_SCRAMBLE_ENABLE	= 0x200,

	/* Block Types */
	NVM_BLK_T_FREE		= 0x0,
	NVM_BLK_T_BAD		= 0x1,
	NVM_BLK_T_GRWN_BAD	= 0x2,
	NVM_BLK_T_DEV		= 0x4,
	NVM_BLK_T_HOST		= 0x8,

	/* Memory capabilities */
	NVM_ID_CAP_SLC		= 0x1,
	NVM_ID_CAP_CMD_SUSPEND	= 0x2,
	NVM_ID_CAP_SCRAMBLE	= 0x4,
	NVM_ID_CAP_ENCRYPT	= 0x8,

	/* Memory types */
	NVM_ID_FMTYPE_SLC	= 0,
	NVM_ID_FMTYPE_MLC	= 1,

	/* Device capabilities */
	NVM_ID_DCAP_BBLKMGMT	= 0x1,
	NVM_UD_DCAP_ECC		= 0x2,
पूर्ण;

काष्ठा nvm_id_lp_mlc अणु
	u16	num_pairs;
	u8	pairs[886];
पूर्ण;

काष्ठा nvm_id_lp_tbl अणु
	__u8	id[8];
	काष्ठा nvm_id_lp_mlc mlc;
पूर्ण;

काष्ठा nvm_addrf_12 अणु
	u8	ch_len;
	u8	lun_len;
	u8	blk_len;
	u8	pg_len;
	u8	pln_len;
	u8	sec_len;

	u8	ch_offset;
	u8	lun_offset;
	u8	blk_offset;
	u8	pg_offset;
	u8	pln_offset;
	u8	sec_offset;

	u64	ch_mask;
	u64	lun_mask;
	u64	blk_mask;
	u64	pg_mask;
	u64	pln_mask;
	u64	sec_mask;
पूर्ण;

काष्ठा nvm_addrf अणु
	u8	ch_len;
	u8	lun_len;
	u8	chk_len;
	u8	sec_len;
	u8	rsv_len[2];

	u8	ch_offset;
	u8	lun_offset;
	u8	chk_offset;
	u8	sec_offset;
	u8	rsv_off[2];

	u64	ch_mask;
	u64	lun_mask;
	u64	chk_mask;
	u64	sec_mask;
	u64	rsv_mask[2];
पूर्ण;

क्रमागत अणु
	/* Chunk states */
	NVM_CHK_ST_FREE =	1 << 0,
	NVM_CHK_ST_CLOSED =	1 << 1,
	NVM_CHK_ST_OPEN =	1 << 2,
	NVM_CHK_ST_OFFLINE =	1 << 3,

	/* Chunk types */
	NVM_CHK_TP_W_SEQ =	1 << 0,
	NVM_CHK_TP_W_RAN =	1 << 1,
	NVM_CHK_TP_SZ_SPEC =	1 << 4,
पूर्ण;

/*
 * Note: The काष्ठाure size is linked to nvme_nvm_chk_meta such that the same
 * buffer can be used when converting from little endian to cpu addressing.
 */
काष्ठा nvm_chk_meta अणु
	u8	state;
	u8	type;
	u8	wi;
	u8	rsvd[5];
	u64	slba;
	u64	cnlb;
	u64	wp;
पूर्ण;

काष्ठा nvm_target अणु
	काष्ठा list_head list;
	काष्ठा nvm_tgt_dev *dev;
	काष्ठा nvm_tgt_type *type;
	काष्ठा gendisk *disk;
पूर्ण;

#घोषणा ADDR_EMPTY (~0ULL)

#घोषणा NVM_TARGET_DEFAULT_OP (101)
#घोषणा NVM_TARGET_MIN_OP (3)
#घोषणा NVM_TARGET_MAX_OP (80)

#घोषणा NVM_VERSION_MAJOR 1
#घोषणा NVM_VERSION_MINOR 0
#घोषणा NVM_VERSION_PATCH 0

#घोषणा NVM_MAX_VLBA (64) /* max logical blocks in a vector command */

काष्ठा nvm_rq;
प्रकार व्योम (nvm_end_io_fn)(काष्ठा nvm_rq *);

काष्ठा nvm_rq अणु
	काष्ठा nvm_tgt_dev *dev;

	काष्ठा bio *bio;

	जोड़ अणु
		काष्ठा ppa_addr ppa_addr;
		dma_addr_t dma_ppa_list;
	पूर्ण;

	काष्ठा ppa_addr *ppa_list;

	व्योम *meta_list;
	dma_addr_t dma_meta_list;

	nvm_end_io_fn *end_io;

	uपूर्णांक8_t opcode;
	uपूर्णांक16_t nr_ppas;
	uपूर्णांक16_t flags;

	u64 ppa_status; /* ppa media status */
	पूर्णांक error;

	पूर्णांक is_seq; /* Sequential hपूर्णांक flag. 1.2 only */

	व्योम *निजी;
पूर्ण;

अटल अंतरभूत काष्ठा nvm_rq *nvm_rq_from_pdu(व्योम *pdu)
अणु
	वापस pdu - माप(काष्ठा nvm_rq);
पूर्ण

अटल अंतरभूत व्योम *nvm_rq_to_pdu(काष्ठा nvm_rq *rqdata)
अणु
	वापस rqdata + 1;
पूर्ण

अटल अंतरभूत काष्ठा ppa_addr *nvm_rq_to_ppa_list(काष्ठा nvm_rq *rqd)
अणु
	वापस (rqd->nr_ppas > 1) ? rqd->ppa_list : &rqd->ppa_addr;
पूर्ण

क्रमागत अणु
	NVM_BLK_ST_FREE =	0x1,	/* Free block */
	NVM_BLK_ST_TGT =	0x2,	/* Block in use by target */
	NVM_BLK_ST_BAD =	0x8,	/* Bad block */
पूर्ण;

/* Instance geometry */
काष्ठा nvm_geo अणु
	/* device reported version */
	u8	major_ver_id;
	u8	minor_ver_id;

	/* kernel लघु version */
	u8	version;

	/* instance specअगरic geometry */
	पूर्णांक num_ch;
	पूर्णांक num_lun;		/* per channel */

	/* calculated values */
	पूर्णांक all_luns;		/* across channels */
	पूर्णांक all_chunks;		/* across channels */

	पूर्णांक op;			/* over-provision in instance */

	sector_t total_secs;	/* across channels */

	/* chunk geometry */
	u32	num_chk;	/* chunks per lun */
	u32	clba;		/* sectors per chunk */
	u16	csecs;		/* sector size */
	u16	sos;		/* out-of-band area size */
	bool	ext;		/* metadata in extended data buffer */
	u32	mdts;		/* Max data transfer size*/

	/* device ग_लिखो स्थिरrains */
	u32	ws_min;		/* minimum ग_लिखो size */
	u32	ws_opt;		/* optimal ग_लिखो size */
	u32	mw_cunits;	/* distance required क्रम successful पढ़ो */
	u32	maxoc;		/* maximum खोलो chunks */
	u32	maxocpu;	/* maximum खोलो chunks per parallel unit */

	/* device capabilities */
	u32	mccap;

	/* device timings */
	u32	trdt;		/* Avg. Tपढ़ो (ns) */
	u32	trdm;		/* Max Tपढ़ो (ns) */
	u32	tprt;		/* Avg. Tprog (ns) */
	u32	tprm;		/* Max Tprog (ns) */
	u32	tbet;		/* Avg. Terase (ns) */
	u32	tbem;		/* Max Terase (ns) */

	/* generic address क्रमmat */
	काष्ठा nvm_addrf addrf;

	/* 1.2 compatibility */
	u8	vmnt;
	u32	cap;
	u32	करोm;

	u8	mtype;
	u8	fmtype;

	u16	cpar;
	u32	mpos;

	u8	num_pln;
	u8	pln_mode;
	u16	num_pg;
	u16	fpg_sz;
पूर्ण;

/* sub-device काष्ठाure */
काष्ठा nvm_tgt_dev अणु
	/* Device inक्रमmation */
	काष्ठा nvm_geo geo;

	/* Base ppas क्रम target LUNs */
	काष्ठा ppa_addr *luns;

	काष्ठा request_queue *q;

	काष्ठा nvm_dev *parent;
	व्योम *map;
पूर्ण;

काष्ठा nvm_dev अणु
	काष्ठा nvm_dev_ops *ops;

	काष्ठा list_head devices;

	/* Device inक्रमmation */
	काष्ठा nvm_geo geo;

	अचिन्हित दीर्घ *lun_map;
	व्योम *dma_pool;

	/* Backend device */
	काष्ठा request_queue *q;
	अक्षर name[DISK_NAME_LEN];
	व्योम *निजी_data;

	काष्ठा kref ref;
	व्योम *rmap;

	काष्ठा mutex mlock;
	spinlock_t lock;

	/* target management */
	काष्ठा list_head area_list;
	काष्ठा list_head tarमाला_लो;
पूर्ण;

अटल अंतरभूत काष्ठा ppa_addr generic_to_dev_addr(काष्ठा nvm_dev *dev,
						  काष्ठा ppa_addr r)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा ppa_addr l;

	अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
		काष्ठा nvm_addrf_12 *ppaf = (काष्ठा nvm_addrf_12 *)&geo->addrf;

		l.ppa = ((u64)r.g.ch) << ppaf->ch_offset;
		l.ppa |= ((u64)r.g.lun) << ppaf->lun_offset;
		l.ppa |= ((u64)r.g.blk) << ppaf->blk_offset;
		l.ppa |= ((u64)r.g.pg) << ppaf->pg_offset;
		l.ppa |= ((u64)r.g.pl) << ppaf->pln_offset;
		l.ppa |= ((u64)r.g.sec) << ppaf->sec_offset;
	पूर्ण अन्यथा अणु
		काष्ठा nvm_addrf *lbaf = &geo->addrf;

		l.ppa = ((u64)r.m.grp) << lbaf->ch_offset;
		l.ppa |= ((u64)r.m.pu) << lbaf->lun_offset;
		l.ppa |= ((u64)r.m.chk) << lbaf->chk_offset;
		l.ppa |= ((u64)r.m.sec) << lbaf->sec_offset;
	पूर्ण

	वापस l;
पूर्ण

अटल अंतरभूत काष्ठा ppa_addr dev_to_generic_addr(काष्ठा nvm_dev *dev,
						  काष्ठा ppa_addr r)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा ppa_addr l;

	l.ppa = 0;

	अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
		काष्ठा nvm_addrf_12 *ppaf = (काष्ठा nvm_addrf_12 *)&geo->addrf;

		l.g.ch = (r.ppa & ppaf->ch_mask) >> ppaf->ch_offset;
		l.g.lun = (r.ppa & ppaf->lun_mask) >> ppaf->lun_offset;
		l.g.blk = (r.ppa & ppaf->blk_mask) >> ppaf->blk_offset;
		l.g.pg = (r.ppa & ppaf->pg_mask) >> ppaf->pg_offset;
		l.g.pl = (r.ppa & ppaf->pln_mask) >> ppaf->pln_offset;
		l.g.sec = (r.ppa & ppaf->sec_mask) >> ppaf->sec_offset;
	पूर्ण अन्यथा अणु
		काष्ठा nvm_addrf *lbaf = &geo->addrf;

		l.m.grp = (r.ppa & lbaf->ch_mask) >> lbaf->ch_offset;
		l.m.pu = (r.ppa & lbaf->lun_mask) >> lbaf->lun_offset;
		l.m.chk = (r.ppa & lbaf->chk_mask) >> lbaf->chk_offset;
		l.m.sec = (r.ppa & lbaf->sec_mask) >> lbaf->sec_offset;
	पूर्ण

	वापस l;
पूर्ण

अटल अंतरभूत u64 dev_to_chunk_addr(काष्ठा nvm_dev *dev, व्योम *addrf,
				    काष्ठा ppa_addr p)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	u64 caddr;

	अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
		काष्ठा nvm_addrf_12 *ppaf = (काष्ठा nvm_addrf_12 *)addrf;

		caddr = (u64)p.g.pg << ppaf->pg_offset;
		caddr |= (u64)p.g.pl << ppaf->pln_offset;
		caddr |= (u64)p.g.sec << ppaf->sec_offset;
	पूर्ण अन्यथा अणु
		caddr = p.m.sec;
	पूर्ण

	वापस caddr;
पूर्ण

अटल अंतरभूत काष्ठा ppa_addr nvm_ppa32_to_ppa64(काष्ठा nvm_dev *dev,
						 व्योम *addrf, u32 ppa32)
अणु
	काष्ठा ppa_addr ppa64;

	ppa64.ppa = 0;

	अगर (ppa32 == -1) अणु
		ppa64.ppa = ADDR_EMPTY;
	पूर्ण अन्यथा अगर (ppa32 & (1U << 31)) अणु
		ppa64.c.line = ppa32 & ((~0U) >> 1);
		ppa64.c.is_cached = 1;
	पूर्ण अन्यथा अणु
		काष्ठा nvm_geo *geo = &dev->geo;

		अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
			काष्ठा nvm_addrf_12 *ppaf = addrf;

			ppa64.g.ch = (ppa32 & ppaf->ch_mask) >>
							ppaf->ch_offset;
			ppa64.g.lun = (ppa32 & ppaf->lun_mask) >>
							ppaf->lun_offset;
			ppa64.g.blk = (ppa32 & ppaf->blk_mask) >>
							ppaf->blk_offset;
			ppa64.g.pg = (ppa32 & ppaf->pg_mask) >>
							ppaf->pg_offset;
			ppa64.g.pl = (ppa32 & ppaf->pln_mask) >>
							ppaf->pln_offset;
			ppa64.g.sec = (ppa32 & ppaf->sec_mask) >>
							ppaf->sec_offset;
		पूर्ण अन्यथा अणु
			काष्ठा nvm_addrf *lbaf = addrf;

			ppa64.m.grp = (ppa32 & lbaf->ch_mask) >>
							lbaf->ch_offset;
			ppa64.m.pu = (ppa32 & lbaf->lun_mask) >>
							lbaf->lun_offset;
			ppa64.m.chk = (ppa32 & lbaf->chk_mask) >>
							lbaf->chk_offset;
			ppa64.m.sec = (ppa32 & lbaf->sec_mask) >>
							lbaf->sec_offset;
		पूर्ण
	पूर्ण

	वापस ppa64;
पूर्ण

अटल अंतरभूत u32 nvm_ppa64_to_ppa32(काष्ठा nvm_dev *dev,
				     व्योम *addrf, काष्ठा ppa_addr ppa64)
अणु
	u32 ppa32 = 0;

	अगर (ppa64.ppa == ADDR_EMPTY) अणु
		ppa32 = ~0U;
	पूर्ण अन्यथा अगर (ppa64.c.is_cached) अणु
		ppa32 |= ppa64.c.line;
		ppa32 |= 1U << 31;
	पूर्ण अन्यथा अणु
		काष्ठा nvm_geo *geo = &dev->geo;

		अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
			काष्ठा nvm_addrf_12 *ppaf = addrf;

			ppa32 |= ppa64.g.ch << ppaf->ch_offset;
			ppa32 |= ppa64.g.lun << ppaf->lun_offset;
			ppa32 |= ppa64.g.blk << ppaf->blk_offset;
			ppa32 |= ppa64.g.pg << ppaf->pg_offset;
			ppa32 |= ppa64.g.pl << ppaf->pln_offset;
			ppa32 |= ppa64.g.sec << ppaf->sec_offset;
		पूर्ण अन्यथा अणु
			काष्ठा nvm_addrf *lbaf = addrf;

			ppa32 |= ppa64.m.grp << lbaf->ch_offset;
			ppa32 |= ppa64.m.pu << lbaf->lun_offset;
			ppa32 |= ppa64.m.chk << lbaf->chk_offset;
			ppa32 |= ppa64.m.sec << lbaf->sec_offset;
		पूर्ण
	पूर्ण

	वापस ppa32;
पूर्ण

अटल अंतरभूत पूर्णांक nvm_next_ppa_in_chk(काष्ठा nvm_tgt_dev *dev,
				      काष्ठा ppa_addr *ppa)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक last = 0;

	अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
		पूर्णांक sec = ppa->g.sec;

		sec++;
		अगर (sec == geo->ws_min) अणु
			पूर्णांक pg = ppa->g.pg;

			sec = 0;
			pg++;
			अगर (pg == geo->num_pg) अणु
				पूर्णांक pl = ppa->g.pl;

				pg = 0;
				pl++;
				अगर (pl == geo->num_pln)
					last = 1;

				ppa->g.pl = pl;
			पूर्ण
			ppa->g.pg = pg;
		पूर्ण
		ppa->g.sec = sec;
	पूर्ण अन्यथा अणु
		ppa->m.sec++;
		अगर (ppa->m.sec == geo->clba)
			last = 1;
	पूर्ण

	वापस last;
पूर्ण

प्रकार sector_t (nvm_tgt_capacity_fn)(व्योम *);
प्रकार व्योम *(nvm_tgt_init_fn)(काष्ठा nvm_tgt_dev *, काष्ठा gendisk *,
				पूर्णांक flags);
प्रकार व्योम (nvm_tgt_निकास_fn)(व्योम *, bool);
प्रकार पूर्णांक (nvm_tgt_sysfs_init_fn)(काष्ठा gendisk *);
प्रकार व्योम (nvm_tgt_sysfs_निकास_fn)(काष्ठा gendisk *);

क्रमागत अणु
	NVM_TGT_F_DEV_L2P = 0,
	NVM_TGT_F_HOST_L2P = 1 << 0,
पूर्ण;

काष्ठा nvm_tgt_type अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक version[3];
	पूर्णांक flags;

	/* target entry poपूर्णांकs */
	स्थिर काष्ठा block_device_operations *bops;
	nvm_tgt_capacity_fn *capacity;

	/* module-specअगरic init/tearकरोwn */
	nvm_tgt_init_fn *init;
	nvm_tgt_निकास_fn *निकास;

	/* sysfs */
	nvm_tgt_sysfs_init_fn *sysfs_init;
	nvm_tgt_sysfs_निकास_fn *sysfs_निकास;

	/* For पूर्णांकernal use */
	काष्ठा list_head list;
	काष्ठा module *owner;
पूर्ण;

बाह्य पूर्णांक nvm_रेजिस्टर_tgt_type(काष्ठा nvm_tgt_type *);
बाह्य व्योम nvm_unरेजिस्टर_tgt_type(काष्ठा nvm_tgt_type *);

बाह्य व्योम *nvm_dev_dma_alloc(काष्ठा nvm_dev *, gfp_t, dma_addr_t *);
बाह्य व्योम nvm_dev_dma_मुक्त(काष्ठा nvm_dev *, व्योम *, dma_addr_t);

बाह्य काष्ठा nvm_dev *nvm_alloc_dev(पूर्णांक);
बाह्य पूर्णांक nvm_रेजिस्टर(काष्ठा nvm_dev *);
बाह्य व्योम nvm_unरेजिस्टर(काष्ठा nvm_dev *);

बाह्य पूर्णांक nvm_get_chunk_meta(काष्ठा nvm_tgt_dev *, काष्ठा ppa_addr,
			      पूर्णांक, काष्ठा nvm_chk_meta *);
बाह्य पूर्णांक nvm_set_chunk_meta(काष्ठा nvm_tgt_dev *, काष्ठा ppa_addr *,
			      पूर्णांक, पूर्णांक);
बाह्य पूर्णांक nvm_submit_io(काष्ठा nvm_tgt_dev *, काष्ठा nvm_rq *, व्योम *);
बाह्य पूर्णांक nvm_submit_io_sync(काष्ठा nvm_tgt_dev *, काष्ठा nvm_rq *, व्योम *);
बाह्य व्योम nvm_end_io(काष्ठा nvm_rq *);

#अन्यथा /* CONFIG_NVM */
काष्ठा nvm_dev_ops;

अटल अंतरभूत काष्ठा nvm_dev *nvm_alloc_dev(पूर्णांक node)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत पूर्णांक nvm_रेजिस्टर(काष्ठा nvm_dev *dev)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम nvm_unरेजिस्टर(काष्ठा nvm_dev *dev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_NVM */
#पूर्ण_अगर /* LIGHTNVM.H */
