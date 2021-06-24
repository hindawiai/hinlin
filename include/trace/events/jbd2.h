<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM jbd2

#अगर !defined(_TRACE_JBD2_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_JBD2_H

#समावेश <linux/jbd2.h>
#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा transaction_chp_stats_s;
काष्ठा transaction_run_stats_s;

TRACE_EVENT(jbd2_checkpoपूर्णांक,

	TP_PROTO(journal_t *journal, पूर्णांक result),

	TP_ARGS(journal, result),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	पूर्णांक,	result			)
	),

	TP_fast_assign(
		__entry->dev		= journal->j_fs_dev->bd_dev;
		__entry->result		= result;
	),

	TP_prपूर्णांकk("dev %d,%d result %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->result)
);

DECLARE_EVENT_CLASS(jbd2_commit,

	TP_PROTO(journal_t *journal, transaction_t *commit_transaction),

	TP_ARGS(journal, commit_transaction),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	अक्षर,	sync_commit		  )
		__field(	पूर्णांक,	transaction		  )
	),

	TP_fast_assign(
		__entry->dev		= journal->j_fs_dev->bd_dev;
		__entry->sync_commit = commit_transaction->t_synchronous_commit;
		__entry->transaction	= commit_transaction->t_tid;
	),

	TP_prपूर्णांकk("dev %d,%d transaction %d sync %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->transaction, __entry->sync_commit)
);

DEFINE_EVENT(jbd2_commit, jbd2_start_commit,

	TP_PROTO(journal_t *journal, transaction_t *commit_transaction),

	TP_ARGS(journal, commit_transaction)
);

DEFINE_EVENT(jbd2_commit, jbd2_commit_locking,

	TP_PROTO(journal_t *journal, transaction_t *commit_transaction),

	TP_ARGS(journal, commit_transaction)
);

DEFINE_EVENT(jbd2_commit, jbd2_commit_flushing,

	TP_PROTO(journal_t *journal, transaction_t *commit_transaction),

	TP_ARGS(journal, commit_transaction)
);

DEFINE_EVENT(jbd2_commit, jbd2_commit_logging,

	TP_PROTO(journal_t *journal, transaction_t *commit_transaction),

	TP_ARGS(journal, commit_transaction)
);

DEFINE_EVENT(jbd2_commit, jbd2_drop_transaction,

	TP_PROTO(journal_t *journal, transaction_t *commit_transaction),

	TP_ARGS(journal, commit_transaction)
);

TRACE_EVENT(jbd2_end_commit,
	TP_PROTO(journal_t *journal, transaction_t *commit_transaction),

	TP_ARGS(journal, commit_transaction),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	अक्षर,	sync_commit		  )
		__field(	पूर्णांक,	transaction		  )
		__field(	पूर्णांक,	head		  	  )
	),

	TP_fast_assign(
		__entry->dev		= journal->j_fs_dev->bd_dev;
		__entry->sync_commit = commit_transaction->t_synchronous_commit;
		__entry->transaction	= commit_transaction->t_tid;
		__entry->head		= journal->j_tail_sequence;
	),

	TP_prपूर्णांकk("dev %d,%d transaction %d sync %d head %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->transaction, __entry->sync_commit, __entry->head)
);

TRACE_EVENT(jbd2_submit_inode_data,
	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	ino_t,	ino			)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
	),

	TP_prपूर्णांकk("dev %d,%d ino %lu",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  (अचिन्हित दीर्घ) __entry->ino)
);

DECLARE_EVENT_CLASS(jbd2_handle_start_class,
	TP_PROTO(dev_t dev, अचिन्हित दीर्घ tid, अचिन्हित पूर्णांक type,
		 अचिन्हित पूर्णांक line_no, पूर्णांक requested_blocks),

	TP_ARGS(dev, tid, type, line_no, requested_blocks),

	TP_STRUCT__entry(
		__field(		dev_t,	dev		)
		__field(	अचिन्हित दीर्घ,	tid		)
		__field(	 अचिन्हित पूर्णांक,	type		)
		__field(	 अचिन्हित पूर्णांक,	line_no		)
		__field(		  पूर्णांक,	requested_blocks)
	),

	TP_fast_assign(
		__entry->dev		  = dev;
		__entry->tid		  = tid;
		__entry->type		  = type;
		__entry->line_no	  = line_no;
		__entry->requested_blocks = requested_blocks;
	),

	TP_prपूर्णांकk("dev %d,%d tid %lu type %u line_no %u "
		  "requested_blocks %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->tid,
		  __entry->type, __entry->line_no, __entry->requested_blocks)
);

DEFINE_EVENT(jbd2_handle_start_class, jbd2_handle_start,
	TP_PROTO(dev_t dev, अचिन्हित दीर्घ tid, अचिन्हित पूर्णांक type,
		 अचिन्हित पूर्णांक line_no, पूर्णांक requested_blocks),

	TP_ARGS(dev, tid, type, line_no, requested_blocks)
);

DEFINE_EVENT(jbd2_handle_start_class, jbd2_handle_restart,
	TP_PROTO(dev_t dev, अचिन्हित दीर्घ tid, अचिन्हित पूर्णांक type,
		 अचिन्हित पूर्णांक line_no, पूर्णांक requested_blocks),

	TP_ARGS(dev, tid, type, line_no, requested_blocks)
);

TRACE_EVENT(jbd2_handle_extend,
	TP_PROTO(dev_t dev, अचिन्हित दीर्घ tid, अचिन्हित पूर्णांक type,
		 अचिन्हित पूर्णांक line_no, पूर्णांक buffer_credits,
		 पूर्णांक requested_blocks),

	TP_ARGS(dev, tid, type, line_no, buffer_credits, requested_blocks),

	TP_STRUCT__entry(
		__field(		dev_t,	dev		)
		__field(	अचिन्हित दीर्घ,	tid		)
		__field(	 अचिन्हित पूर्णांक,	type		)
		__field(	 अचिन्हित पूर्णांक,	line_no		)
		__field(		  पूर्णांक,	buffer_credits  )
		__field(		  पूर्णांक,	requested_blocks)
	),

	TP_fast_assign(
		__entry->dev		  = dev;
		__entry->tid		  = tid;
		__entry->type		  = type;
		__entry->line_no	  = line_no;
		__entry->buffer_credits   = buffer_credits;
		__entry->requested_blocks = requested_blocks;
	),

	TP_prपूर्णांकk("dev %d,%d tid %lu type %u line_no %u "
		  "buffer_credits %d requested_blocks %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->tid,
		  __entry->type, __entry->line_no, __entry->buffer_credits,
		  __entry->requested_blocks)
);

TRACE_EVENT(jbd2_handle_stats,
	TP_PROTO(dev_t dev, अचिन्हित दीर्घ tid, अचिन्हित पूर्णांक type,
		 अचिन्हित पूर्णांक line_no, पूर्णांक पूर्णांकerval, पूर्णांक sync,
		 पूर्णांक requested_blocks, पूर्णांक dirtied_blocks),

	TP_ARGS(dev, tid, type, line_no, पूर्णांकerval, sync,
		requested_blocks, dirtied_blocks),

	TP_STRUCT__entry(
		__field(		dev_t,	dev		)
		__field(	अचिन्हित दीर्घ,	tid		)
		__field(	 अचिन्हित पूर्णांक,	type		)
		__field(	 अचिन्हित पूर्णांक,	line_no		)
		__field(		  पूर्णांक,	पूर्णांकerval	)
		__field(		  पूर्णांक,	sync		)
		__field(		  पूर्णांक,	requested_blocks)
		__field(		  पूर्णांक,	dirtied_blocks	)
	),

	TP_fast_assign(
		__entry->dev		  = dev;
		__entry->tid		  = tid;
		__entry->type		  = type;
		__entry->line_no	  = line_no;
		__entry->पूर्णांकerval	  = पूर्णांकerval;
		__entry->sync		  = sync;
		__entry->requested_blocks = requested_blocks;
		__entry->dirtied_blocks	  = dirtied_blocks;
	),

	TP_prपूर्णांकk("dev %d,%d tid %lu type %u line_no %u interval %d "
		  "sync %d requested_blocks %d dirtied_blocks %d",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->tid,
		  __entry->type, __entry->line_no, __entry->पूर्णांकerval,
		  __entry->sync, __entry->requested_blocks,
		  __entry->dirtied_blocks)
);

TRACE_EVENT(jbd2_run_stats,
	TP_PROTO(dev_t dev, अचिन्हित दीर्घ tid,
		 काष्ठा transaction_run_stats_s *stats),

	TP_ARGS(dev, tid, stats),

	TP_STRUCT__entry(
		__field(		dev_t,	dev		)
		__field(	अचिन्हित दीर्घ,	tid		)
		__field(	अचिन्हित दीर्घ,	रुको		)
		__field(	अचिन्हित दीर्घ,	request_delay	)
		__field(	अचिन्हित दीर्घ,	running		)
		__field(	अचिन्हित दीर्घ,	locked		)
		__field(	अचिन्हित दीर्घ,	flushing	)
		__field(	अचिन्हित दीर्घ,	logging		)
		__field(		__u32,	handle_count	)
		__field(		__u32,	blocks		)
		__field(		__u32,	blocks_logged	)
	),

	TP_fast_assign(
		__entry->dev		= dev;
		__entry->tid		= tid;
		__entry->रुको		= stats->rs_रुको;
		__entry->request_delay	= stats->rs_request_delay;
		__entry->running	= stats->rs_running;
		__entry->locked		= stats->rs_locked;
		__entry->flushing	= stats->rs_flushing;
		__entry->logging	= stats->rs_logging;
		__entry->handle_count	= stats->rs_handle_count;
		__entry->blocks		= stats->rs_blocks;
		__entry->blocks_logged	= stats->rs_blocks_logged;
	),

	TP_prपूर्णांकk("dev %d,%d tid %lu wait %u request_delay %u running %u "
		  "locked %u flushing %u logging %u handle_count %u "
		  "blocks %u blocks_logged %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->tid,
		  jअगरfies_to_msecs(__entry->रुको),
		  jअगरfies_to_msecs(__entry->request_delay),
		  jअगरfies_to_msecs(__entry->running),
		  jअगरfies_to_msecs(__entry->locked),
		  jअगरfies_to_msecs(__entry->flushing),
		  jअगरfies_to_msecs(__entry->logging),
		  __entry->handle_count, __entry->blocks,
		  __entry->blocks_logged)
);

TRACE_EVENT(jbd2_checkpoपूर्णांक_stats,
	TP_PROTO(dev_t dev, अचिन्हित दीर्घ tid,
		 काष्ठा transaction_chp_stats_s *stats),

	TP_ARGS(dev, tid, stats),

	TP_STRUCT__entry(
		__field(		dev_t,	dev		)
		__field(	अचिन्हित दीर्घ,	tid		)
		__field(	अचिन्हित दीर्घ,	chp_समय	)
		__field(		__u32,	क्रमced_to_बंद	)
		__field(		__u32,	written		)
		__field(		__u32,	dropped		)
	),

	TP_fast_assign(
		__entry->dev		= dev;
		__entry->tid		= tid;
		__entry->chp_समय	= stats->cs_chp_समय;
		__entry->क्रमced_to_बंद= stats->cs_क्रमced_to_बंद;
		__entry->written	= stats->cs_written;
		__entry->dropped	= stats->cs_dropped;
	),

	TP_prपूर्णांकk("dev %d,%d tid %lu chp_time %u forced_to_close %u "
		  "written %u dropped %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->tid,
		  jअगरfies_to_msecs(__entry->chp_समय),
		  __entry->क्रमced_to_बंद, __entry->written, __entry->dropped)
);

TRACE_EVENT(jbd2_update_log_tail,

	TP_PROTO(journal_t *journal, tid_t first_tid,
		 अचिन्हित दीर्घ block_nr, अचिन्हित दीर्घ मुक्तd),

	TP_ARGS(journal, first_tid, block_nr, मुक्तd),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	tid_t,	tail_sequence		)
		__field(	tid_t,	first_tid		)
		__field(अचिन्हित दीर्घ,	block_nr		)
		__field(अचिन्हित दीर्घ,	मुक्तd			)
	),

	TP_fast_assign(
		__entry->dev		= journal->j_fs_dev->bd_dev;
		__entry->tail_sequence	= journal->j_tail_sequence;
		__entry->first_tid	= first_tid;
		__entry->block_nr	= block_nr;
		__entry->मुक्तd		= मुक्तd;
	),

	TP_prपूर्णांकk("dev %d,%d from %u to %u offset %lu freed %lu",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->tail_sequence, __entry->first_tid,
		  __entry->block_nr, __entry->मुक्तd)
);

TRACE_EVENT(jbd2_ग_लिखो_superblock,

	TP_PROTO(journal_t *journal, पूर्णांक ग_लिखो_op),

	TP_ARGS(journal, ग_लिखो_op),

	TP_STRUCT__entry(
		__field(	dev_t,  dev			)
		__field(	  पूर्णांक,  ग_लिखो_op		)
	),

	TP_fast_assign(
		__entry->dev		= journal->j_fs_dev->bd_dev;
		__entry->ग_लिखो_op	= ग_लिखो_op;
	),

	TP_prपूर्णांकk("dev %d,%d write_op %x", MAJOR(__entry->dev),
		  MINOR(__entry->dev), __entry->ग_लिखो_op)
);

TRACE_EVENT(jbd2_lock_buffer_stall,

	TP_PROTO(dev_t dev, अचिन्हित दीर्घ stall_ms),

	TP_ARGS(dev, stall_ms),

	TP_STRUCT__entry(
		__field(        dev_t, dev	)
		__field(अचिन्हित दीर्घ, stall_ms	)
	),

	TP_fast_assign(
		__entry->dev		= dev;
		__entry->stall_ms	= stall_ms;
	),

	TP_prपूर्णांकk("dev %d,%d stall_ms %lu",
		MAJOR(__entry->dev), MINOR(__entry->dev),
		__entry->stall_ms)
);

#पूर्ण_अगर /* _TRACE_JBD2_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
