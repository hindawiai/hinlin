<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "qman_test.h"

#घोषणा CGR_ID		27
#घोषणा POOL_ID		2
#घोषणा FQ_FLAGS	QMAN_FQ_FLAG_DYNAMIC_FQID
#घोषणा NUM_ENQUEUES	10
#घोषणा NUM_PARTIAL	4
#घोषणा PORTAL_SDQCR	(QM_SDQCR_SOURCE_CHANNELS | \
			QM_SDQCR_TYPE_PRIO_QOS | \
			QM_SDQCR_TOKEN_SET(0x98) | \
			QM_SDQCR_CHANNELS_DEDICATED | \
			QM_SDQCR_CHANNELS_POOL(POOL_ID))
#घोषणा PORTAL_OPAQUE	((व्योम *)0xf00dbeef)
#घोषणा VDQCR_FLAGS	(QMAN_VOLATILE_FLAG_WAIT | QMAN_VOLATILE_FLAG_FINISH)

अटल क्रमागत qman_cb_dqrr_result cb_dqrr(काष्ठा qman_portal *,
					काष्ठा qman_fq *,
					स्थिर काष्ठा qm_dqrr_entry *,
					bool sched_napi);
अटल व्योम cb_ern(काष्ठा qman_portal *, काष्ठा qman_fq *,
		   स्थिर जोड़ qm_mr_entry *);
अटल व्योम cb_fqs(काष्ठा qman_portal *, काष्ठा qman_fq *,
		   स्थिर जोड़ qm_mr_entry *);

अटल काष्ठा qm_fd fd, fd_dq;
अटल काष्ठा qman_fq fq_base = अणु
	.cb.dqrr = cb_dqrr,
	.cb.ern = cb_ern,
	.cb.fqs = cb_fqs
पूर्ण;
अटल DECLARE_WAIT_QUEUE_HEAD(रुकोqueue);
अटल पूर्णांक retire_complete, sdqcr_complete;

/* Helpers क्रम initialising and "incrementing" a frame descriptor */
अटल व्योम fd_init(काष्ठा qm_fd *fd)
अणु
	qm_fd_addr_set64(fd, 0xabdeadbeefLLU);
	qm_fd_set_contig_big(fd, 0x0000ffff);
	fd->cmd = cpu_to_be32(0xfeedf00d);
पूर्ण

अटल व्योम fd_inc(काष्ठा qm_fd *fd)
अणु
	u64 t = qm_fd_addr_get64(fd);
	पूर्णांक z = t >> 40;
	अचिन्हित पूर्णांक len, off;
	क्रमागत qm_fd_क्रमmat fmt;

	t <<= 1;
	अगर (z)
		t |= 1;
	qm_fd_addr_set64(fd, t);

	fmt = qm_fd_get_क्रमmat(fd);
	off = qm_fd_get_offset(fd);
	len = qm_fd_get_length(fd);
	len--;
	qm_fd_set_param(fd, fmt, off, len);

	be32_add_cpu(&fd->cmd, 1);
पूर्ण

/* The only part of the 'fd' we can't स_भेद() is the ppid */
अटल bool fd_neq(स्थिर काष्ठा qm_fd *a, स्थिर काष्ठा qm_fd *b)
अणु
	bool neq = qm_fd_addr_get64(a) != qm_fd_addr_get64(b);

	neq |= qm_fd_get_क्रमmat(a) != qm_fd_get_क्रमmat(b);
	neq |= a->cfg != b->cfg;
	neq |= a->cmd != b->cmd;

	वापस neq;
पूर्ण

/* test */
अटल पूर्णांक करो_enqueues(काष्ठा qman_fq *fq)
अणु
	अचिन्हित पूर्णांक loop;
	पूर्णांक err = 0;

	क्रम (loop = 0; loop < NUM_ENQUEUES; loop++) अणु
		अगर (qman_enqueue(fq, &fd)) अणु
			pr_crit("qman_enqueue() failed\n");
			err = -EIO;
		पूर्ण
		fd_inc(&fd);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक qman_test_api(व्योम)
अणु
	अचिन्हित पूर्णांक flags, frmcnt;
	पूर्णांक err;
	काष्ठा qman_fq *fq = &fq_base;

	pr_info("%s(): Starting\n", __func__);
	fd_init(&fd);
	fd_init(&fd_dq);

	/* Initialise (parked) FQ */
	err = qman_create_fq(0, FQ_FLAGS, fq);
	अगर (err) अणु
		pr_crit("qman_create_fq() failed\n");
		जाओ failed;
	पूर्ण
	err = qman_init_fq(fq, QMAN_INITFQ_FLAG_LOCAL, शून्य);
	अगर (err) अणु
		pr_crit("qman_init_fq() failed\n");
		जाओ failed;
	पूर्ण
	/* Do enqueues + VDQCR, twice. (Parked FQ) */
	err = करो_enqueues(fq);
	अगर (err)
		जाओ failed;
	pr_info("VDQCR (till-empty);\n");
	frmcnt = QM_VDQCR_NUMFRAMES_TILLEMPTY;
	err = qman_अस्थिर_dequeue(fq, VDQCR_FLAGS, frmcnt);
	अगर (err) अणु
		pr_crit("qman_volatile_dequeue() failed\n");
		जाओ failed;
	पूर्ण
	err = करो_enqueues(fq);
	अगर (err)
		जाओ failed;
	pr_info("VDQCR (%d of %d);\n", NUM_PARTIAL, NUM_ENQUEUES);
	frmcnt = QM_VDQCR_NUMFRAMES_SET(NUM_PARTIAL);
	err = qman_अस्थिर_dequeue(fq, VDQCR_FLAGS, frmcnt);
	अगर (err) अणु
		pr_crit("qman_volatile_dequeue() failed\n");
		जाओ failed;
	पूर्ण
	pr_info("VDQCR (%d of %d);\n", NUM_ENQUEUES - NUM_PARTIAL,
		NUM_ENQUEUES);
	frmcnt = QM_VDQCR_NUMFRAMES_SET(NUM_ENQUEUES - NUM_PARTIAL);
	err = qman_अस्थिर_dequeue(fq, VDQCR_FLAGS, frmcnt);
	अगर (err) अणु
		pr_err("qman_volatile_dequeue() failed\n");
		जाओ failed;
	पूर्ण

	err = करो_enqueues(fq);
	अगर (err)
		जाओ failed;
	pr_info("scheduled dequeue (till-empty)\n");
	err = qman_schedule_fq(fq);
	अगर (err) अणु
		pr_crit("qman_schedule_fq() failed\n");
		जाओ failed;
	पूर्ण
	रुको_event(रुकोqueue, sdqcr_complete);

	/* Retire and OOS the FQ */
	err = qman_retire_fq(fq, &flags);
	अगर (err < 0) अणु
		pr_crit("qman_retire_fq() failed\n");
		जाओ failed;
	पूर्ण
	रुको_event(रुकोqueue, retire_complete);
	अगर (flags & QMAN_FQ_STATE_BLOCKOOS) अणु
		err = -EIO;
		pr_crit("leaking frames\n");
		जाओ failed;
	पूर्ण
	err = qman_oos_fq(fq);
	अगर (err) अणु
		pr_crit("qman_oos_fq() failed\n");
		जाओ failed;
	पूर्ण
	qman_destroy_fq(fq);
	pr_info("%s(): Finished\n", __func__);
	वापस 0;

failed:
	WARN_ON(1);
	वापस err;
पूर्ण

अटल क्रमागत qman_cb_dqrr_result cb_dqrr(काष्ठा qman_portal *p,
					काष्ठा qman_fq *fq,
					स्थिर काष्ठा qm_dqrr_entry *dq,
					bool sched_napi)
अणु
	अगर (WARN_ON(fd_neq(&fd_dq, &dq->fd))) अणु
		pr_err("BADNESS: dequeued frame doesn't match;\n");
		वापस qman_cb_dqrr_consume;
	पूर्ण
	fd_inc(&fd_dq);
	अगर (!(dq->stat & QM_DQRR_STAT_UNSCHEDULED) && !fd_neq(&fd_dq, &fd)) अणु
		sdqcr_complete = 1;
		wake_up(&रुकोqueue);
	पूर्ण
	वापस qman_cb_dqrr_consume;
पूर्ण

अटल व्योम cb_ern(काष्ठा qman_portal *p, काष्ठा qman_fq *fq,
		   स्थिर जोड़ qm_mr_entry *msg)
अणु
	pr_crit("cb_ern() unimplemented");
	WARN_ON(1);
पूर्ण

अटल व्योम cb_fqs(काष्ठा qman_portal *p, काष्ठा qman_fq *fq,
		   स्थिर जोड़ qm_mr_entry *msg)
अणु
	u8 verb = (msg->verb & QM_MR_VERB_TYPE_MASK);

	अगर ((verb != QM_MR_VERB_FQRN) && (verb != QM_MR_VERB_FQRNI)) अणु
		pr_crit("unexpected FQS message");
		WARN_ON(1);
		वापस;
	पूर्ण
	pr_info("Retirement message received\n");
	retire_complete = 1;
	wake_up(&रुकोqueue);
पूर्ण
