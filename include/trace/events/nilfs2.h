<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nilfs2

#अगर !defined(_TRACE_NILFS2_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NILFS2_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा nilfs_sc_info;

#घोषणा show_collection_stage(type)					\
	__prपूर्णांक_symbolic(type,						\
	अणु NILFS_ST_INIT, "ST_INIT" पूर्ण,					\
	अणु NILFS_ST_GC, "ST_GC" पूर्ण,					\
	अणु NILFS_ST_खाता, "ST_FILE" पूर्ण,					\
	अणु NILFS_ST_Iखाता, "ST_IFILE" पूर्ण,					\
	अणु NILFS_ST_CPखाता, "ST_CPFILE" पूर्ण,				\
	अणु NILFS_ST_SUखाता, "ST_SUFILE" पूर्ण,				\
	अणु NILFS_ST_DAT, "ST_DAT" पूर्ण,					\
	अणु NILFS_ST_SR, "ST_SR" पूर्ण,					\
	अणु NILFS_ST_DSYNC, "ST_DSYNC" पूर्ण,					\
	अणु NILFS_ST_DONE, "ST_DONE"पूर्ण)

TRACE_EVENT(nilfs2_collection_stage_transition,

	    TP_PROTO(काष्ठा nilfs_sc_info *sci),

	    TP_ARGS(sci),

	    TP_STRUCT__entry(
		    __field(व्योम *, sci)
		    __field(पूर्णांक, stage)
	    ),

	    TP_fast_assign(
			__entry->sci = sci;
			__entry->stage = sci->sc_stage.scnt;
		    ),

	    TP_prपूर्णांकk("sci = %p stage = %s",
		      __entry->sci,
		      show_collection_stage(__entry->stage))
);

#अगर_अघोषित TRACE_HEADER_MULTI_READ
क्रमागत nilfs2_transaction_transition_state अणु
	TRACE_NILFS2_TRANSACTION_BEGIN,
	TRACE_NILFS2_TRANSACTION_COMMIT,
	TRACE_NILFS2_TRANSACTION_ABORT,
	TRACE_NILFS2_TRANSACTION_TRYLOCK,
	TRACE_NILFS2_TRANSACTION_LOCK,
	TRACE_NILFS2_TRANSACTION_UNLOCK,
पूर्ण;
#पूर्ण_अगर

#घोषणा show_transaction_state(type)					\
	__prपूर्णांक_symbolic(type,						\
			 अणु TRACE_NILFS2_TRANSACTION_BEGIN, "BEGIN" पूर्ण,	\
			 अणु TRACE_NILFS2_TRANSACTION_COMMIT, "COMMIT" पूर्ण,	\
			 अणु TRACE_NILFS2_TRANSACTION_ABORT, "ABORT" पूर्ण,	\
			 अणु TRACE_NILFS2_TRANSACTION_TRYLOCK, "TRYLOCK" पूर्ण, \
			 अणु TRACE_NILFS2_TRANSACTION_LOCK, "LOCK" पूर्ण,	\
			 अणु TRACE_NILFS2_TRANSACTION_UNLOCK, "UNLOCK" पूर्ण)

TRACE_EVENT(nilfs2_transaction_transition,
	    TP_PROTO(काष्ठा super_block *sb,
		     काष्ठा nilfs_transaction_info *ti,
		     पूर्णांक count,
		     अचिन्हित पूर्णांक flags,
		     क्रमागत nilfs2_transaction_transition_state state),

	    TP_ARGS(sb, ti, count, flags, state),

	    TP_STRUCT__entry(
		    __field(व्योम *, sb)
		    __field(व्योम *, ti)
		    __field(पूर्णांक, count)
		    __field(अचिन्हित पूर्णांक, flags)
		    __field(पूर्णांक, state)
	    ),

	    TP_fast_assign(
		    __entry->sb = sb;
		    __entry->ti = ti;
		    __entry->count = count;
		    __entry->flags = flags;
		    __entry->state = state;
		    ),

	    TP_prपूर्णांकk("sb = %p ti = %p count = %d flags = %x state = %s",
		      __entry->sb,
		      __entry->ti,
		      __entry->count,
		      __entry->flags,
		      show_transaction_state(__entry->state))
);

TRACE_EVENT(nilfs2_segment_usage_check,
	    TP_PROTO(काष्ठा inode *sufile,
		     __u64 segnum,
		     अचिन्हित दीर्घ cnt),

	    TP_ARGS(sufile, segnum, cnt),

	    TP_STRUCT__entry(
		    __field(काष्ठा inode *, sufile)
		    __field(__u64, segnum)
		    __field(अचिन्हित दीर्घ, cnt)
	    ),

	    TP_fast_assign(
		    __entry->sufile = sufile;
		    __entry->segnum = segnum;
		    __entry->cnt = cnt;
		    ),

	    TP_prपूर्णांकk("sufile = %p segnum = %llu cnt = %lu",
		      __entry->sufile,
		      __entry->segnum,
		      __entry->cnt)
);

TRACE_EVENT(nilfs2_segment_usage_allocated,
	    TP_PROTO(काष्ठा inode *sufile,
		     __u64 segnum),

	    TP_ARGS(sufile, segnum),

	    TP_STRUCT__entry(
		    __field(काष्ठा inode *, sufile)
		    __field(__u64, segnum)
	    ),

	    TP_fast_assign(
		    __entry->sufile = sufile;
		    __entry->segnum = segnum;
		    ),

	    TP_prपूर्णांकk("sufile = %p segnum = %llu",
		      __entry->sufile,
		      __entry->segnum)
);

TRACE_EVENT(nilfs2_segment_usage_मुक्तd,
	    TP_PROTO(काष्ठा inode *sufile,
		     __u64 segnum),

	    TP_ARGS(sufile, segnum),

	    TP_STRUCT__entry(
		    __field(काष्ठा inode *, sufile)
		    __field(__u64, segnum)
	    ),

	    TP_fast_assign(
		    __entry->sufile = sufile;
		    __entry->segnum = segnum;
		    ),

	    TP_prपूर्णांकk("sufile = %p segnum = %llu",
		      __entry->sufile,
		      __entry->segnum)
);

TRACE_EVENT(nilfs2_mdt_insert_new_block,
	    TP_PROTO(काष्ठा inode *inode,
		     अचिन्हित दीर्घ ino,
		     अचिन्हित दीर्घ block),

	    TP_ARGS(inode, ino, block),

	    TP_STRUCT__entry(
		    __field(काष्ठा inode *, inode)
		    __field(अचिन्हित दीर्घ, ino)
		    __field(अचिन्हित दीर्घ, block)
	    ),

	    TP_fast_assign(
		    __entry->inode = inode;
		    __entry->ino = ino;
		    __entry->block = block;
		    ),

	    TP_prपूर्णांकk("inode = %p ino = %lu block = %lu",
		      __entry->inode,
		      __entry->ino,
		      __entry->block)
);

TRACE_EVENT(nilfs2_mdt_submit_block,
	    TP_PROTO(काष्ठा inode *inode,
		     अचिन्हित दीर्घ ino,
		     अचिन्हित दीर्घ blkoff,
		     पूर्णांक mode),

	    TP_ARGS(inode, ino, blkoff, mode),

	    TP_STRUCT__entry(
		    __field(काष्ठा inode *, inode)
		    __field(अचिन्हित दीर्घ, ino)
		    __field(अचिन्हित दीर्घ, blkoff)
		    __field(पूर्णांक, mode)
	    ),

	    TP_fast_assign(
		    __entry->inode = inode;
		    __entry->ino = ino;
		    __entry->blkoff = blkoff;
		    __entry->mode = mode;
		    ),

	    TP_prपूर्णांकk("inode = %p ino = %lu blkoff = %lu mode = %x",
		      __entry->inode,
		      __entry->ino,
		      __entry->blkoff,
		      __entry->mode)
);

#पूर्ण_अगर /* _TRACE_NILFS2_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता nilfs2
#समावेश <trace/define_trace.h>
