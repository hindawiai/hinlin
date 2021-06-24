<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM gfs2

#अगर !defined(_TRACE_GFS2_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_GFS2_H

#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/dlmस्थिरants.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/iomap.h>
#समावेश "incore.h"
#समावेश "glock.h"
#समावेश "rgrp.h"

#घोषणा dlm_state_name(nn) अणु DLM_LOCK_##nn, #nn पूर्ण
#घोषणा glock_trace_name(x) __prपूर्णांक_symbolic(x,		\
			    dlm_state_name(IV),		\
			    dlm_state_name(NL),		\
			    dlm_state_name(CR),		\
			    dlm_state_name(CW),		\
			    dlm_state_name(PR),		\
			    dlm_state_name(PW),		\
			    dlm_state_name(EX))

#घोषणा block_state_name(x) __prपूर्णांक_symbolic(x,			\
			    अणु GFS2_BLKST_FREE, "free" पूर्ण,	\
			    अणु GFS2_BLKST_USED, "used" पूर्ण,	\
			    अणु GFS2_BLKST_DINODE, "dinode" पूर्ण,	\
			    अणु GFS2_BLKST_UNLINKED, "unlinked" पूर्ण)

#घोषणा TRACE_RS_DELETE  0
#घोषणा TRACE_RS_TREEDEL 1
#घोषणा TRACE_RS_INSERT  2
#घोषणा TRACE_RS_CLAIM   3

#घोषणा rs_func_name(x) __prपूर्णांक_symbolic(x,	\
					 अणु 0, "del " पूर्ण,	\
					 अणु 1, "tdel" पूर्ण,	\
					 अणु 2, "ins " पूर्ण,	\
					 अणु 3, "clm " पूर्ण)

#घोषणा show_glock_flags(flags) __prपूर्णांक_flags(flags, "",	\
	अणु(1UL << GLF_LOCK),			"l" पूर्ण,		\
	अणु(1UL << GLF_DEMOTE),			"D" पूर्ण,		\
	अणु(1UL << GLF_PENDING_DEMOTE),		"d" पूर्ण,		\
	अणु(1UL << GLF_DEMOTE_IN_PROGRESS),	"p" पूर्ण,		\
	अणु(1UL << GLF_सूचीTY),			"y" पूर्ण,		\
	अणु(1UL << GLF_LFLUSH),			"f" पूर्ण,		\
	अणु(1UL << GLF_INVALIDATE_IN_PROGRESS),	"i" पूर्ण,		\
	अणु(1UL << GLF_REPLY_PENDING),		"r" पूर्ण,		\
	अणु(1UL << GLF_INITIAL),			"I" पूर्ण,		\
	अणु(1UL << GLF_FROZEN),			"F" पूर्ण,		\
	अणु(1UL << GLF_LRU),			"L" पूर्ण,		\
	अणु(1UL << GLF_OBJECT),			"o" पूर्ण,		\
	अणु(1UL << GLF_BLOCKING),			"b" पूर्ण)

#अगर_अघोषित NUMPTY
#घोषणा NUMPTY
अटल अंतरभूत u8 glock_trace_state(अचिन्हित पूर्णांक state)
अणु
	चयन(state) अणु
	हाल LM_ST_SHARED:
		वापस DLM_LOCK_PR;
	हाल LM_ST_DEFERRED:
		वापस DLM_LOCK_CW;
	हाल LM_ST_EXCLUSIVE:
		वापस DLM_LOCK_EX;
	पूर्ण
	वापस DLM_LOCK_NL;
पूर्ण
#पूर्ण_अगर

/* Section 1 - Locking
 *
 * Objectives:
 * Latency: Remote demote request to state change
 * Latency: Local lock request to state change
 * Latency: State change to lock grant
 * Correctness: Ordering of local lock state vs. I/O requests
 * Correctness: Responses to remote demote requests
 */

/* General glock state change (DLM lock request completes) */
TRACE_EVENT(gfs2_glock_state_change,

	TP_PROTO(स्थिर काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक new_state),

	TP_ARGS(gl, new_state),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	u64,	glnum			)
		__field(	u32,	gltype			)
		__field(	u8,	cur_state		)
		__field(	u8,	new_state		)
		__field(	u8,	dmt_state		)
		__field(	u8,	tgt_state		)
		__field(	अचिन्हित दीर्घ,	flags		)
	),

	TP_fast_assign(
		__entry->dev		= gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->glnum		= gl->gl_name.ln_number;
		__entry->gltype		= gl->gl_name.ln_type;
		__entry->cur_state	= glock_trace_state(gl->gl_state);
		__entry->new_state	= glock_trace_state(new_state);
		__entry->tgt_state	= glock_trace_state(gl->gl_target);
		__entry->dmt_state	= glock_trace_state(gl->gl_demote_state);
		__entry->flags		= gl->gl_flags | (gl->gl_object ? (1UL<<GLF_OBJECT) : 0);
	),

	TP_prपूर्णांकk("%u,%u glock %d:%lld state %s to %s tgt:%s dmt:%s flags:%s",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->gltype,
		 (अचिन्हित दीर्घ दीर्घ)__entry->glnum,
		  glock_trace_name(__entry->cur_state),
		  glock_trace_name(__entry->new_state),
		  glock_trace_name(__entry->tgt_state),
		  glock_trace_name(__entry->dmt_state),
		  show_glock_flags(__entry->flags))
);

/* State change -> unlocked, glock is being deallocated */
TRACE_EVENT(gfs2_glock_put,

	TP_PROTO(स्थिर काष्ठा gfs2_glock *gl),

	TP_ARGS(gl),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	u64,	glnum			)
		__field(	u32,	gltype			)
		__field(	u8,	cur_state		)
		__field(	अचिन्हित दीर्घ,	flags		)
	),

	TP_fast_assign(
		__entry->dev		= gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->gltype		= gl->gl_name.ln_type;
		__entry->glnum		= gl->gl_name.ln_number;
		__entry->cur_state	= glock_trace_state(gl->gl_state);
		__entry->flags		= gl->gl_flags  | (gl->gl_object ? (1UL<<GLF_OBJECT) : 0);
	),

	TP_prपूर्णांकk("%u,%u glock %d:%lld state %s => %s flags:%s",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
                  __entry->gltype, (अचिन्हित दीर्घ दीर्घ)__entry->glnum,
                  glock_trace_name(__entry->cur_state),
		  glock_trace_name(DLM_LOCK_IV),
		  show_glock_flags(__entry->flags))

);

/* Callback (local or remote) requesting lock demotion */
TRACE_EVENT(gfs2_demote_rq,

	TP_PROTO(स्थिर काष्ठा gfs2_glock *gl, bool remote),

	TP_ARGS(gl, remote),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	u64,	glnum			)
		__field(	u32,	gltype			)
		__field(	u8,	cur_state		)
		__field(	u8,	dmt_state		)
		__field(	अचिन्हित दीर्घ,	flags		)
		__field(	bool,	remote			)
	),

	TP_fast_assign(
		__entry->dev		= gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->gltype		= gl->gl_name.ln_type;
		__entry->glnum		= gl->gl_name.ln_number;
		__entry->cur_state	= glock_trace_state(gl->gl_state);
		__entry->dmt_state	= glock_trace_state(gl->gl_demote_state);
		__entry->flags		= gl->gl_flags  | (gl->gl_object ? (1UL<<GLF_OBJECT) : 0);
		__entry->remote		= remote;
	),

	TP_prपूर्णांकk("%u,%u glock %d:%lld demote %s to %s flags:%s %s",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->gltype,
		  (अचिन्हित दीर्घ दीर्घ)__entry->glnum,
                  glock_trace_name(__entry->cur_state),
                  glock_trace_name(__entry->dmt_state),
		  show_glock_flags(__entry->flags),
		  __entry->remote ? "remote" : "local")

);

/* Promotion/grant of a glock */
TRACE_EVENT(gfs2_promote,

	TP_PROTO(स्थिर काष्ठा gfs2_holder *gh, पूर्णांक first),

	TP_ARGS(gh, first),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	u64,	glnum			)
		__field(	u32,	gltype			)
		__field(	पूर्णांक,	first			)
		__field(	u8,	state			)
	),

	TP_fast_assign(
		__entry->dev	= gh->gh_gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->glnum	= gh->gh_gl->gl_name.ln_number;
		__entry->gltype	= gh->gh_gl->gl_name.ln_type;
		__entry->first	= first;
		__entry->state	= glock_trace_state(gh->gh_state);
	),

	TP_prपूर्णांकk("%u,%u glock %u:%llu promote %s %s",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->gltype,
		  (अचिन्हित दीर्घ दीर्घ)__entry->glnum,
		  __entry->first ? "first": "other",
		  glock_trace_name(__entry->state))
);

/* Queue/dequeue a lock request */
TRACE_EVENT(gfs2_glock_queue,

	TP_PROTO(स्थिर काष्ठा gfs2_holder *gh, पूर्णांक queue),

	TP_ARGS(gh, queue),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	u64,	glnum			)
		__field(	u32,	gltype			)
		__field(	पूर्णांक,	queue			)
		__field(	u8,	state			)
	),

	TP_fast_assign(
		__entry->dev	= gh->gh_gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->glnum	= gh->gh_gl->gl_name.ln_number;
		__entry->gltype	= gh->gh_gl->gl_name.ln_type;
		__entry->queue	= queue;
		__entry->state	= glock_trace_state(gh->gh_state);
	),

	TP_prपूर्णांकk("%u,%u glock %u:%llu %squeue %s",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->gltype,
		  (अचिन्हित दीर्घ दीर्घ)__entry->glnum,
		  __entry->queue ? "" : "de",
		  glock_trace_name(__entry->state))
);

/* DLM sends a reply to GFS2 */
TRACE_EVENT(gfs2_glock_lock_समय,

	TP_PROTO(स्थिर काष्ठा gfs2_glock *gl, s64 tdअगरf),

	TP_ARGS(gl, tdअगरf),

	TP_STRUCT__entry(
		__field(	dev_t,	dev		)
		__field(	u64,	glnum		)
		__field(	u32,	gltype		)
		__field(	पूर्णांक,	status		)
		__field(	अक्षर,	flags		)
		__field(	s64,	tdअगरf		)
		__field(	u64,	srtt		)
		__field(	u64,	srttvar		)
		__field(	u64,	srttb		)
		__field(	u64,	srttvarb	)
		__field(	u64,	sirt		)
		__field(	u64,	sirtvar		)
		__field(	u64,	dcount		)
		__field(	u64,	qcount		)
	),

	TP_fast_assign(
		__entry->dev            = gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->glnum          = gl->gl_name.ln_number;
		__entry->gltype         = gl->gl_name.ln_type;
		__entry->status		= gl->gl_lksb.sb_status;
		__entry->flags		= gl->gl_lksb.sb_flags;
		__entry->tdअगरf		= tdअगरf;
		__entry->srtt		= gl->gl_stats.stats[GFS2_LKS_SRTT];
		__entry->srttvar	= gl->gl_stats.stats[GFS2_LKS_SRTTVAR];
		__entry->srttb		= gl->gl_stats.stats[GFS2_LKS_SRTTB];
		__entry->srttvarb	= gl->gl_stats.stats[GFS2_LKS_SRTTVARB];
		__entry->sirt		= gl->gl_stats.stats[GFS2_LKS_SIRT];
		__entry->sirtvar	= gl->gl_stats.stats[GFS2_LKS_SIRTVAR];
		__entry->dcount		= gl->gl_stats.stats[GFS2_LKS_DCOUNT];
		__entry->qcount		= gl->gl_stats.stats[GFS2_LKS_QCOUNT];
	),

	TP_prपूर्णांकk("%u,%u glock %d:%lld status:%d flags:%02x tdiff:%lld srtt:%lld/%lld srttb:%lld/%lld sirt:%lld/%lld dcnt:%lld qcnt:%lld",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->gltype,
		  (अचिन्हित दीर्घ दीर्घ)__entry->glnum,
		  __entry->status, __entry->flags,
		  (दीर्घ दीर्घ)__entry->tdअगरf,
		  (दीर्घ दीर्घ)__entry->srtt,
		  (दीर्घ दीर्घ)__entry->srttvar,
		  (दीर्घ दीर्घ)__entry->srttb,
		  (दीर्घ दीर्घ)__entry->srttvarb,
		  (दीर्घ दीर्घ)__entry->sirt,
		  (दीर्घ दीर्घ)__entry->sirtvar,
		  (दीर्घ दीर्घ)__entry->dcount,
		  (दीर्घ दीर्घ)__entry->qcount)
);

/* Section 2 - Log/journal
 *
 * Objectives:
 * Latency: Log flush समय
 * Correctness: pin/unpin vs. disk I/O ordering
 * Perक्रमmance: Log usage stats
 */

/* Pin/unpin a block in the log */
TRACE_EVENT(gfs2_pin,

	TP_PROTO(स्थिर काष्ठा gfs2_bufdata *bd, पूर्णांक pin),

	TP_ARGS(bd, pin),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	पूर्णांक,	pin			)
		__field(	u32,	len			)
		__field(	sector_t,	block		)
		__field(	u64,	ino			)
	),

	TP_fast_assign(
		__entry->dev		= bd->bd_gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->pin		= pin;
		__entry->len		= bd->bd_bh->b_size;
		__entry->block		= bd->bd_bh->b_blocknr;
		__entry->ino		= bd->bd_gl->gl_name.ln_number;
	),

	TP_prपूर्णांकk("%u,%u log %s %llu/%lu inode %llu",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->pin ? "pin" : "unpin",
		  (अचिन्हित दीर्घ दीर्घ)__entry->block,
		  (अचिन्हित दीर्घ)__entry->len,
		  (अचिन्हित दीर्घ दीर्घ)__entry->ino)
);

/* Flushing the log */
TRACE_EVENT(gfs2_log_flush,

	TP_PROTO(स्थिर काष्ठा gfs2_sbd *sdp, पूर्णांक start, u32 flags),

	TP_ARGS(sdp, start, flags),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	पूर्णांक,	start			)
		__field(	u64,	log_seq			)
		__field(	u32,	flags			)
	),

	TP_fast_assign(
		__entry->dev            = sdp->sd_vfs->s_dev;
		__entry->start		= start;
		__entry->log_seq	= sdp->sd_log_sequence;
		__entry->flags		= flags;
	),

	TP_prपूर्णांकk("%u,%u log flush %s %llu %llx",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->start ? "start" : "end",
		  (अचिन्हित दीर्घ दीर्घ)__entry->log_seq,
		  (अचिन्हित दीर्घ दीर्घ)__entry->flags)
);

/* Reserving/releasing blocks in the log */
TRACE_EVENT(gfs2_log_blocks,

	TP_PROTO(स्थिर काष्ठा gfs2_sbd *sdp, पूर्णांक blocks),

	TP_ARGS(sdp, blocks),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	पूर्णांक,	blocks			)
		__field(	पूर्णांक,	blks_मुक्त		)
	),

	TP_fast_assign(
		__entry->dev		= sdp->sd_vfs->s_dev;
		__entry->blocks		= blocks;
		__entry->blks_मुक्त	= atomic_पढ़ो(&sdp->sd_log_blks_मुक्त);
	),

	TP_prपूर्णांकk("%u,%u log reserve %d %d", MAJOR(__entry->dev),
		  MINOR(__entry->dev), __entry->blocks, __entry->blks_मुक्त)
);

/* Writing back the AIL */
TRACE_EVENT(gfs2_ail_flush,

	TP_PROTO(स्थिर काष्ठा gfs2_sbd *sdp, स्थिर काष्ठा ग_लिखोback_control *wbc, पूर्णांक start),

	TP_ARGS(sdp, wbc, start),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	पूर्णांक, start			)
		__field(	पूर्णांक, sync_mode			)
		__field(	दीर्घ, nr_to_ग_लिखो		)
	),

	TP_fast_assign(
		__entry->dev		= sdp->sd_vfs->s_dev;
		__entry->start		= start;
		__entry->sync_mode	= wbc->sync_mode;
		__entry->nr_to_ग_लिखो	= wbc->nr_to_ग_लिखो;
	),

	TP_prपूर्णांकk("%u,%u ail flush %s %s %ld", MAJOR(__entry->dev),
		  MINOR(__entry->dev), __entry->start ? "start" : "end",
		  __entry->sync_mode == WB_SYNC_ALL ? "all" : "none",
		  __entry->nr_to_ग_लिखो)
);

/* Section 3 - bmap
 *
 * Objectives:
 * Latency: Bmap request समय
 * Perक्रमmance: Block allocator tracing
 * Correctness: Test of disard generation vs. blocks allocated
 */

/* Map an extent of blocks, possibly a new allocation */
TRACE_EVENT(gfs2_bmap,

	TP_PROTO(स्थिर काष्ठा gfs2_inode *ip, स्थिर काष्ठा buffer_head *bh,
		sector_t lblock, पूर्णांक create, पूर्णांक त्रुटि_सं),

	TP_ARGS(ip, bh, lblock, create, त्रुटि_सं),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	sector_t, lblock		)
		__field(	sector_t, pblock		)
		__field(	u64,	inum			)
		__field(	अचिन्हित दीर्घ, state		)
		__field(	u32,	len			)
		__field(	पूर्णांक,	create			)
		__field(	पूर्णांक,	त्रुटि_सं			)
	),

	TP_fast_assign(
		__entry->dev            = ip->i_gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->lblock		= lblock;
		__entry->pblock		= buffer_mapped(bh) ?  bh->b_blocknr : 0;
		__entry->inum		= ip->i_no_addr;
		__entry->state		= bh->b_state;
		__entry->len		= bh->b_size;
		__entry->create		= create;
		__entry->त्रुटि_सं		= त्रुटि_सं;
	),

	TP_prपूर्णांकk("%u,%u bmap %llu map %llu/%lu to %llu flags:%08lx %s %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  (अचिन्हित दीर्घ दीर्घ)__entry->inum,
		  (अचिन्हित दीर्घ दीर्घ)__entry->lblock,
		  (अचिन्हित दीर्घ)__entry->len,
		  (अचिन्हित दीर्घ दीर्घ)__entry->pblock,
		  __entry->state, __entry->create ? "create " : "nocreate",
		  __entry->त्रुटि_सं)
);

TRACE_EVENT(gfs2_iomap_start,

	TP_PROTO(स्थिर काष्ठा gfs2_inode *ip, loff_t pos, sमाप_प्रकार length,
		 u16 flags),

	TP_ARGS(ip, pos, length, flags),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	u64,	inum			)
		__field(	loff_t, pos			)
		__field(	sमाप_प्रकार, length			)
		__field(	u16,	flags			)
	),

	TP_fast_assign(
		__entry->dev            = ip->i_gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->inum		= ip->i_no_addr;
		__entry->pos		= pos;
		__entry->length		= length;
		__entry->flags		= flags;
	),

	TP_prपूर्णांकk("%u,%u bmap %llu iomap start %llu/%lu flags:%08x",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  (अचिन्हित दीर्घ दीर्घ)__entry->inum,
		  (अचिन्हित दीर्घ दीर्घ)__entry->pos,
		  (अचिन्हित दीर्घ)__entry->length, (u16)__entry->flags)
);

TRACE_EVENT(gfs2_iomap_end,

	TP_PROTO(स्थिर काष्ठा gfs2_inode *ip, काष्ठा iomap *iomap, पूर्णांक ret),

	TP_ARGS(ip, iomap, ret),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	u64,	inum			)
		__field(	loff_t, offset			)
		__field(	sमाप_प्रकार, length			)
		__field(	sector_t, pblock		)
		__field(	u16,	flags			)
		__field(	u16,	type			)
		__field(	पूर्णांक,	ret			)
	),

	TP_fast_assign(
		__entry->dev            = ip->i_gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->inum		= ip->i_no_addr;
		__entry->offset		= iomap->offset;
		__entry->length		= iomap->length;
		__entry->pblock		= iomap->addr == IOMAP_शून्य_ADDR ? 0 :
					 (iomap->addr >> ip->i_inode.i_blkbits);
		__entry->flags		= iomap->flags;
		__entry->type		= iomap->type;
		__entry->ret		= ret;
	),

	TP_prपूर्णांकk("%u,%u bmap %llu iomap end %llu/%lu to %llu ty:%d flags:%08x rc:%d",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  (अचिन्हित दीर्घ दीर्घ)__entry->inum,
		  (अचिन्हित दीर्घ दीर्घ)__entry->offset,
		  (अचिन्हित दीर्घ)__entry->length,
		  (दीर्घ दीर्घ)__entry->pblock,
		  (u16)__entry->type,
		  (u16)__entry->flags, __entry->ret)
);

/* Keep track of blocks as they are allocated/मुक्तd */
TRACE_EVENT(gfs2_block_alloc,

	TP_PROTO(स्थिर काष्ठा gfs2_inode *ip, काष्ठा gfs2_rgrpd *rgd,
		 u64 block, अचिन्हित len, u8 block_state),

	TP_ARGS(ip, rgd, block, len, block_state),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	u64,	start			)
		__field(	u64,	inum			)
		__field(	u32,	len			)
		__field(	u8,	block_state		)
		__field(        u64,	rd_addr			)
		__field(        u32,	rd_मुक्त_clone		)
		__field(	u32,	rd_requested		)
		__field(	u32,	rd_reserved		)
	),

	TP_fast_assign(
		__entry->dev		= rgd->rd_gl->gl_name.ln_sbd->sd_vfs->s_dev;
		__entry->start		= block;
		__entry->inum		= ip->i_no_addr;
		__entry->len		= len;
		__entry->block_state	= block_state;
		__entry->rd_addr	= rgd->rd_addr;
		__entry->rd_मुक्त_clone	= rgd->rd_मुक्त_clone;
		__entry->rd_requested	= rgd->rd_requested;
		__entry->rd_reserved	= rgd->rd_reserved;
	),

	TP_prपूर्णांकk("%u,%u bmap %llu alloc %llu/%lu %s rg:%llu rf:%u rq:%u rr:%u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  (अचिन्हित दीर्घ दीर्घ)__entry->inum,
		  (अचिन्हित दीर्घ दीर्घ)__entry->start,
		  (अचिन्हित दीर्घ)__entry->len,
		  block_state_name(__entry->block_state),
		  (अचिन्हित दीर्घ दीर्घ)__entry->rd_addr,
		  __entry->rd_मुक्त_clone,
		  __entry->rd_requested,
		  __entry->rd_reserved)
);

/* Keep track of multi-block reservations as they are allocated/मुक्तd */
TRACE_EVENT(gfs2_rs,

	TP_PROTO(स्थिर काष्ठा gfs2_blkreserv *rs, u8 func),

	TP_ARGS(rs, func),

	TP_STRUCT__entry(
		__field(        dev_t,  dev                     )
		__field(	u64,	rd_addr			)
		__field(	u32,	rd_मुक्त_clone		)
		__field(	u32,	rd_requested		)
		__field(	u32,	rd_reserved		)
		__field(	u64,	inum			)
		__field(	u64,	start			)
		__field(	u32,	requested		)
		__field(	u32,	reserved		)
		__field(	u8,	func			)
	),

	TP_fast_assign(
		__entry->dev		= rs->rs_rgd->rd_sbd->sd_vfs->s_dev;
		__entry->rd_addr	= rs->rs_rgd->rd_addr;
		__entry->rd_मुक्त_clone	= rs->rs_rgd->rd_मुक्त_clone;
		__entry->rd_requested	= rs->rs_rgd->rd_requested;
		__entry->rd_reserved	= rs->rs_rgd->rd_reserved;
		__entry->inum		= container_of(rs, काष्ठा gfs2_inode,
						       i_res)->i_no_addr;
		__entry->start		= rs->rs_start;
		__entry->requested	= rs->rs_requested;
		__entry->reserved	= rs->rs_reserved;
		__entry->func		= func;
	),

	TP_prपूर्णांकk("%u,%u bmap %llu resrv %llu rg:%llu rf:%u rq:%u rr:%u %s q:%u r:%u",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  (अचिन्हित दीर्घ दीर्घ)__entry->inum,
		  (अचिन्हित दीर्घ दीर्घ)__entry->start,
		  (अचिन्हित दीर्घ दीर्घ)__entry->rd_addr,
		  __entry->rd_मुक्त_clone,
		  __entry->rd_requested,
		  __entry->rd_reserved,
		  rs_func_name(__entry->func),
		  __entry->requested,
		  __entry->reserved)
);

#पूर्ण_अगर /* _TRACE_GFS2_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_gfs2
#समावेश <trace/define_trace.h>

