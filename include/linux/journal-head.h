<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/journal-head.h
 *
 * buffer_head fields क्रम JBD
 *
 * 27 May 2001 Andrew Morton
 *	Created - pulled out of fs.h
 */

#अगर_अघोषित JOURNAL_HEAD_H_INCLUDED
#घोषणा JOURNAL_HEAD_H_INCLUDED

#समावेश <linux/spinlock.h>

प्रकार अचिन्हित पूर्णांक		tid_t;		/* Unique transaction ID */
प्रकार काष्ठा transaction_s	transaction_t;	/* Compound transaction type */


काष्ठा buffer_head;

काष्ठा journal_head अणु
	/*
	 * Poपूर्णांकs back to our buffer_head. [jbd_lock_bh_journal_head()]
	 */
	काष्ठा buffer_head *b_bh;

	/*
	 * Protect the buffer head state
	 */
	spinlock_t b_state_lock;

	/*
	 * Reference count - see description in journal.c
	 * [jbd_lock_bh_journal_head()]
	 */
	पूर्णांक b_jcount;

	/*
	 * Journalling list क्रम this buffer [b_state_lock]
	 * NOTE: We *cannot* combine this with b_modअगरied पूर्णांकo a bitfield
	 * as gcc would then (which the C standard allows but which is
	 * very unuseful) make 64-bit accesses to the bitfield and clobber
	 * b_jcount अगर its update races with bitfield modअगरication.
	 */
	अचिन्हित b_jlist;

	/*
	 * This flag संकेतs the buffer has been modअगरied by
	 * the currently running transaction
	 * [b_state_lock]
	 */
	अचिन्हित b_modअगरied;

	/*
	 * Copy of the buffer data frozen क्रम writing to the log.
	 * [b_state_lock]
	 */
	अक्षर *b_frozen_data;

	/*
	 * Poपूर्णांकer to a saved copy of the buffer containing no uncommitted
	 * deallocation references, so that allocations can aव्योम overwriting
	 * uncommitted deletes. [b_state_lock]
	 */
	अक्षर *b_committed_data;

	/*
	 * Poपूर्णांकer to the compound transaction which owns this buffer's
	 * metadata: either the running transaction or the committing
	 * transaction (अगर there is one).  Only applies to buffers on a
	 * transaction's data or metadata journaling list.
	 * [j_list_lock] [b_state_lock]
	 * Either of these locks is enough क्रम पढ़ोing, both are needed क्रम
	 * changes.
	 */
	transaction_t *b_transaction;

	/*
	 * Poपूर्णांकer to the running compound transaction which is currently
	 * modअगरying the buffer's metadata, अगर there was alपढ़ोy a transaction
	 * committing it when the new transaction touched it.
	 * [t_list_lock] [b_state_lock]
	 */
	transaction_t *b_next_transaction;

	/*
	 * Doubly-linked list of buffers on a transaction's data, metadata or
	 * क्रमget queue. [t_list_lock] [b_state_lock]
	 */
	काष्ठा journal_head *b_tnext, *b_tprev;

	/*
	 * Poपूर्णांकer to the compound transaction against which this buffer
	 * is checkpoपूर्णांकed.  Only dirty buffers can be checkpoपूर्णांकed.
	 * [j_list_lock]
	 */
	transaction_t *b_cp_transaction;

	/*
	 * Doubly-linked list of buffers still reमुख्यing to be flushed
	 * beक्रमe an old transaction can be checkpoपूर्णांकed.
	 * [j_list_lock]
	 */
	काष्ठा journal_head *b_cpnext, *b_cpprev;

	/* Trigger type */
	काष्ठा jbd2_buffer_trigger_type *b_triggers;

	/* Trigger type क्रम the committing transaction's frozen data */
	काष्ठा jbd2_buffer_trigger_type *b_frozen_triggers;
पूर्ण;

#पूर्ण_अगर		/* JOURNAL_HEAD_H_INCLUDED */
