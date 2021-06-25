<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux क्रम s390 qdio support, buffer handling, qdio API and module support.
 *
 * Copyright IBM Corp. 2000, 2008
 * Author(s): Utz Bacher <utz.bacher@de.ibm.com>
 *	      Jan Glauber <jang@linux.vnet.ibm.com>
 * 2.6 cio पूर्णांकegration by Cornelia Huck <cornelia.huck@de.ibm.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/qdपन.स>
#समावेश <यंत्र/ipl.h>

#समावेश "cio.h"
#समावेश "css.h"
#समावेश "device.h"
#समावेश "qdio.h"
#समावेश "qdio_debug.h"

MODULE_AUTHOR("Utz Bacher <utz.bacher@de.ibm.com>,"\
	"Jan Glauber <jang@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("QDIO base support");
MODULE_LICENSE("GPL");

अटल अंतरभूत पूर्णांक करो_siga_sync(अचिन्हित दीर्घ schid,
			       अचिन्हित पूर्णांक out_mask, अचिन्हित पूर्णांक in_mask,
			       अचिन्हित पूर्णांक fc)
अणु
	रेजिस्टर अचिन्हित दीर्घ __fc यंत्र ("0") = fc;
	रेजिस्टर अचिन्हित दीर्घ __schid यंत्र ("1") = schid;
	रेजिस्टर अचिन्हित दीर्घ out यंत्र ("2") = out_mask;
	रेजिस्टर अचिन्हित दीर्घ in यंत्र ("3") = in_mask;
	पूर्णांक cc;

	यंत्र अस्थिर(
		"	siga	0\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc)
		: "d" (__fc), "d" (__schid), "d" (out), "d" (in) : "cc");
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक करो_siga_input(अचिन्हित दीर्घ schid, अचिन्हित पूर्णांक mask,
				अचिन्हित पूर्णांक fc)
अणु
	रेजिस्टर अचिन्हित दीर्घ __fc यंत्र ("0") = fc;
	रेजिस्टर अचिन्हित दीर्घ __schid यंत्र ("1") = schid;
	रेजिस्टर अचिन्हित दीर्घ __mask यंत्र ("2") = mask;
	पूर्णांक cc;

	यंत्र अस्थिर(
		"	siga	0\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc)
		: "d" (__fc), "d" (__schid), "d" (__mask) : "cc");
	वापस cc;
पूर्ण

/**
 * करो_siga_output - perक्रमm SIGA-w/wt function
 * @schid: subchannel id or in हाल of QEBSM the subchannel token
 * @mask: which output queues to process
 * @bb: busy bit indicator, set only अगर SIGA-w/wt could not access a buffer
 * @fc: function code to perक्रमm
 * @aob: asynchronous operation block
 *
 * Returns condition code.
 * Note: For IQDC unicast queues only the highest priority queue is processed.
 */
अटल अंतरभूत पूर्णांक करो_siga_output(अचिन्हित दीर्घ schid, अचिन्हित दीर्घ mask,
				 अचिन्हित पूर्णांक *bb, अचिन्हित पूर्णांक fc,
				 अचिन्हित दीर्घ aob)
अणु
	रेजिस्टर अचिन्हित दीर्घ __fc यंत्र("0") = fc;
	रेजिस्टर अचिन्हित दीर्घ __schid यंत्र("1") = schid;
	रेजिस्टर अचिन्हित दीर्घ __mask यंत्र("2") = mask;
	रेजिस्टर अचिन्हित दीर्घ __aob यंत्र("3") = aob;
	पूर्णांक cc;

	यंत्र अस्थिर(
		"	siga	0\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc), "+d" (__fc), "+d" (__aob)
		: "d" (__schid), "d" (__mask)
		: "cc");
	*bb = __fc >> 31;
	वापस cc;
पूर्ण

/**
 * qdio_करो_eqbs - extract buffer states क्रम QEBSM
 * @q: queue to manipulate
 * @state: state of the extracted buffers
 * @start: buffer number to start at
 * @count: count of buffers to examine
 * @स्वतः_ack: स्वतःmatically acknowledge buffers
 *
 * Returns the number of successfully extracted equal buffer states.
 * Stops processing अगर a state is dअगरferent from the last buffers state.
 */
अटल पूर्णांक qdio_करो_eqbs(काष्ठा qdio_q *q, अचिन्हित अक्षर *state,
			पूर्णांक start, पूर्णांक count, पूर्णांक स्वतः_ack)
अणु
	पूर्णांक पंचांगp_count = count, पंचांगp_start = start, nr = q->nr;
	अचिन्हित पूर्णांक ccq = 0;

	qperf_inc(q, eqbs);

	अगर (!q->is_input_q)
		nr += q->irq_ptr->nr_input_qs;
again:
	ccq = करो_eqbs(q->irq_ptr->sch_token, state, nr, &पंचांगp_start, &पंचांगp_count,
		      स्वतः_ack);

	चयन (ccq) अणु
	हाल 0:
	हाल 32:
		/* all करोne, or next buffer state dअगरferent */
		वापस count - पंचांगp_count;
	हाल 96:
		/* not all buffers processed */
		qperf_inc(q, eqbs_partial);
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "EQBS part:%02x",
			पंचांगp_count);
		वापस count - पंचांगp_count;
	हाल 97:
		/* no buffer processed */
		DBF_DEV_EVENT(DBF_WARN, q->irq_ptr, "EQBS again:%2d", ccq);
		जाओ again;
	शेष:
		DBF_ERROR("%4x ccq:%3d", SCH_NO(q), ccq);
		DBF_ERROR("%4x EQBS ERROR", SCH_NO(q));
		DBF_ERROR("%3d%3d%2d", count, पंचांगp_count, nr);
		q->handler(q->irq_ptr->cdev, QDIO_ERROR_GET_BUF_STATE, q->nr,
			   q->first_to_check, count, q->irq_ptr->पूर्णांक_parm);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * qdio_करो_sqbs - set buffer states क्रम QEBSM
 * @q: queue to manipulate
 * @state: new state of the buffers
 * @start: first buffer number to change
 * @count: how many buffers to change
 *
 * Returns the number of successfully changed buffers.
 * Does retrying until the specअगरied count of buffer states is set or an
 * error occurs.
 */
अटल पूर्णांक qdio_करो_sqbs(काष्ठा qdio_q *q, अचिन्हित अक्षर state, पूर्णांक start,
			पूर्णांक count)
अणु
	अचिन्हित पूर्णांक ccq = 0;
	पूर्णांक पंचांगp_count = count, पंचांगp_start = start;
	पूर्णांक nr = q->nr;

	अगर (!count)
		वापस 0;
	qperf_inc(q, sqbs);

	अगर (!q->is_input_q)
		nr += q->irq_ptr->nr_input_qs;
again:
	ccq = करो_sqbs(q->irq_ptr->sch_token, state, nr, &पंचांगp_start, &पंचांगp_count);

	चयन (ccq) अणु
	हाल 0:
	हाल 32:
		/* all करोne, or active buffer adapter-owned */
		WARN_ON_ONCE(पंचांगp_count);
		वापस count - पंचांगp_count;
	हाल 96:
		/* not all buffers processed */
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "SQBS again:%2d", ccq);
		qperf_inc(q, sqbs_partial);
		जाओ again;
	शेष:
		DBF_ERROR("%4x ccq:%3d", SCH_NO(q), ccq);
		DBF_ERROR("%4x SQBS ERROR", SCH_NO(q));
		DBF_ERROR("%3d%3d%2d", count, पंचांगp_count, nr);
		q->handler(q->irq_ptr->cdev, QDIO_ERROR_SET_BUF_STATE, q->nr,
			   q->first_to_check, count, q->irq_ptr->पूर्णांक_parm);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Returns number of examined buffers and their common state in *state.
 * Requested number of buffers-to-examine must be > 0.
 */
अटल अंतरभूत पूर्णांक get_buf_states(काष्ठा qdio_q *q, अचिन्हित पूर्णांक bufnr,
				 अचिन्हित अक्षर *state, अचिन्हित पूर्णांक count,
				 पूर्णांक स्वतः_ack)
अणु
	अचिन्हित अक्षर __state = 0;
	पूर्णांक i = 1;

	अगर (is_qebsm(q))
		वापस qdio_करो_eqbs(q, state, bufnr, count, स्वतः_ack);

	/* get initial state: */
	__state = q->slsb.val[bufnr];

	/* Bail out early अगर there is no work on the queue: */
	अगर (__state & SLSB_OWNER_CU)
		जाओ out;

	क्रम (; i < count; i++) अणु
		bufnr = next_buf(bufnr);

		/* stop अगर next state dअगरfers from initial state: */
		अगर (q->slsb.val[bufnr] != __state)
			अवरोध;
	पूर्ण

out:
	*state = __state;
	वापस i;
पूर्ण

अटल अंतरभूत पूर्णांक get_buf_state(काष्ठा qdio_q *q, अचिन्हित पूर्णांक bufnr,
				अचिन्हित अक्षर *state, पूर्णांक स्वतः_ack)
अणु
	वापस get_buf_states(q, bufnr, state, 1, स्वतः_ack);
पूर्ण

/* wrap-around safe setting of slsb states, वापसs number of changed buffers */
अटल अंतरभूत पूर्णांक set_buf_states(काष्ठा qdio_q *q, पूर्णांक bufnr,
				 अचिन्हित अक्षर state, पूर्णांक count)
अणु
	पूर्णांक i;

	अगर (is_qebsm(q))
		वापस qdio_करो_sqbs(q, state, bufnr, count);

	/* Ensure that all preceding changes to the SBALs are visible: */
	mb();

	क्रम (i = 0; i < count; i++) अणु
		WRITE_ONCE(q->slsb.val[bufnr], state);
		bufnr = next_buf(bufnr);
	पूर्ण

	/* Make our SLSB changes visible: */
	mb();

	वापस count;
पूर्ण

अटल अंतरभूत पूर्णांक set_buf_state(काष्ठा qdio_q *q, पूर्णांक bufnr,
				अचिन्हित अक्षर state)
अणु
	वापस set_buf_states(q, bufnr, state, 1);
पूर्ण

/* set slsb states to initial state */
अटल व्योम qdio_init_buf_states(काष्ठा qdio_irq *irq_ptr)
अणु
	काष्ठा qdio_q *q;
	पूर्णांक i;

	क्रम_each_input_queue(irq_ptr, q, i)
		set_buf_states(q, 0, SLSB_P_INPUT_NOT_INIT,
			       QDIO_MAX_BUFFERS_PER_Q);
	क्रम_each_output_queue(irq_ptr, q, i)
		set_buf_states(q, 0, SLSB_P_OUTPUT_NOT_INIT,
			       QDIO_MAX_BUFFERS_PER_Q);
पूर्ण

अटल अंतरभूत पूर्णांक qdio_siga_sync(काष्ठा qdio_q *q, अचिन्हित पूर्णांक output,
			  अचिन्हित पूर्णांक input)
अणु
	अचिन्हित दीर्घ schid = *((u32 *) &q->irq_ptr->schid);
	अचिन्हित पूर्णांक fc = QDIO_SIGA_SYNC;
	पूर्णांक cc;

	DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "siga-s:%1d", q->nr);
	qperf_inc(q, siga_sync);

	अगर (is_qebsm(q)) अणु
		schid = q->irq_ptr->sch_token;
		fc |= QDIO_SIGA_QEBSM_FLAG;
	पूर्ण

	cc = करो_siga_sync(schid, output, input, fc);
	अगर (unlikely(cc))
		DBF_ERROR("%4x SIGA-S:%2d", SCH_NO(q), cc);
	वापस (cc) ? -EIO : 0;
पूर्ण

अटल अंतरभूत पूर्णांक qdio_siga_sync_q(काष्ठा qdio_q *q)
अणु
	अगर (q->is_input_q)
		वापस qdio_siga_sync(q, 0, q->mask);
	अन्यथा
		वापस qdio_siga_sync(q, q->mask, 0);
पूर्ण

अटल पूर्णांक qdio_siga_output(काष्ठा qdio_q *q, अचिन्हित पूर्णांक count,
			    अचिन्हित पूर्णांक *busy_bit, अचिन्हित दीर्घ aob)
अणु
	अचिन्हित दीर्घ schid = *((u32 *) &q->irq_ptr->schid);
	अचिन्हित पूर्णांक fc = QDIO_SIGA_WRITE;
	u64 start_समय = 0;
	पूर्णांक retries = 0, cc;

	अगर (queue_type(q) == QDIO_IQDIO_QFMT && !multicast_outbound(q)) अणु
		अगर (count > 1)
			fc = QDIO_SIGA_WRITEM;
		अन्यथा अगर (aob)
			fc = QDIO_SIGA_WRITEQ;
	पूर्ण

	अगर (is_qebsm(q)) अणु
		schid = q->irq_ptr->sch_token;
		fc |= QDIO_SIGA_QEBSM_FLAG;
	पूर्ण
again:
	cc = करो_siga_output(schid, q->mask, busy_bit, fc, aob);

	/* hipersocket busy condition */
	अगर (unlikely(*busy_bit)) अणु
		retries++;

		अगर (!start_समय) अणु
			start_समय = get_tod_घड़ी_fast();
			जाओ again;
		पूर्ण
		अगर (get_tod_घड़ी_fast() - start_समय < QDIO_BUSY_BIT_PATIENCE)
			जाओ again;
	पूर्ण
	अगर (retries) अणु
		DBF_DEV_EVENT(DBF_WARN, q->irq_ptr,
			      "%4x cc2 BB1:%1d", SCH_NO(q), q->nr);
		DBF_DEV_EVENT(DBF_WARN, q->irq_ptr, "count:%u", retries);
	पूर्ण
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक qdio_siga_input(काष्ठा qdio_q *q)
अणु
	अचिन्हित दीर्घ schid = *((u32 *) &q->irq_ptr->schid);
	अचिन्हित पूर्णांक fc = QDIO_SIGA_READ;
	पूर्णांक cc;

	DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "siga-r:%1d", q->nr);
	qperf_inc(q, siga_पढ़ो);

	अगर (is_qebsm(q)) अणु
		schid = q->irq_ptr->sch_token;
		fc |= QDIO_SIGA_QEBSM_FLAG;
	पूर्ण

	cc = करो_siga_input(schid, q->mask, fc);
	अगर (unlikely(cc))
		DBF_ERROR("%4x SIGA-R:%2d", SCH_NO(q), cc);
	वापस (cc) ? -EIO : 0;
पूर्ण

#घोषणा qdio_siga_sync_out(q) qdio_siga_sync(q, ~0U, 0)
#घोषणा qdio_siga_sync_all(q) qdio_siga_sync(q, ~0U, ~0U)

अटल अंतरभूत व्योम qdio_sync_queues(काष्ठा qdio_q *q)
अणु
	/* PCI capable outbound queues will also be scanned so sync them too */
	अगर (pci_out_supported(q->irq_ptr))
		qdio_siga_sync_all(q);
	अन्यथा
		qdio_siga_sync_q(q);
पूर्ण

पूर्णांक debug_get_buf_state(काष्ठा qdio_q *q, अचिन्हित पूर्णांक bufnr,
			अचिन्हित अक्षर *state)
अणु
	अगर (need_siga_sync(q))
		qdio_siga_sync_q(q);
	वापस get_buf_state(q, bufnr, state, 0);
पूर्ण

अटल अंतरभूत व्योम qdio_stop_polling(काष्ठा qdio_q *q)
अणु
	अगर (!q->u.in.batch_count)
		वापस;

	qperf_inc(q, stop_polling);

	/* show the card that we are not polling anymore */
	set_buf_states(q, q->u.in.batch_start, SLSB_P_INPUT_NOT_INIT,
		       q->u.in.batch_count);
	q->u.in.batch_count = 0;
पूर्ण

अटल अंतरभूत व्योम account_sbals(काष्ठा qdio_q *q, अचिन्हित पूर्णांक count)
अणु
	q->q_stats.nr_sbal_total += count;
	q->q_stats.nr_sbals[ilog2(count)]++;
पूर्ण

अटल व्योम process_buffer_error(काष्ठा qdio_q *q, अचिन्हित पूर्णांक start,
				 पूर्णांक count)
अणु
	/* special handling क्रम no target buffer empty */
	अगर (queue_type(q) == QDIO_IQDIO_QFMT && !q->is_input_q &&
	    q->sbal[start]->element[15].sflags == 0x10) अणु
		qperf_inc(q, target_full);
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "OUTFULL FTC:%02x", start);
		वापस;
	पूर्ण

	DBF_ERROR("%4x BUF ERROR", SCH_NO(q));
	DBF_ERROR((q->is_input_q) ? "IN:%2d" : "OUT:%2d", q->nr);
	DBF_ERROR("FTC:%3d C:%3d", start, count);
	DBF_ERROR("F14:%2x F15:%2x",
		  q->sbal[start]->element[14].sflags,
		  q->sbal[start]->element[15].sflags);
पूर्ण

अटल अंतरभूत व्योम inbound_handle_work(काष्ठा qdio_q *q, अचिन्हित पूर्णांक start,
				       पूर्णांक count, bool स्वतः_ack)
अणु
	/* ACK the newest SBAL: */
	अगर (!स्वतः_ack)
		set_buf_state(q, add_buf(start, count - 1), SLSB_P_INPUT_ACK);

	अगर (!q->u.in.batch_count)
		q->u.in.batch_start = start;
	q->u.in.batch_count += count;
पूर्ण

अटल पूर्णांक get_inbound_buffer_frontier(काष्ठा qdio_q *q, अचिन्हित पूर्णांक start,
				       अचिन्हित पूर्णांक *error)
अणु
	अचिन्हित अक्षर state = 0;
	पूर्णांक count;

	q->बारtamp = get_tod_घड़ी_fast();

	count = atomic_पढ़ो(&q->nr_buf_used);
	अगर (!count)
		वापस 0;

	/*
	 * No siga sync here, as a PCI or we after a thin पूर्णांकerrupt
	 * alपढ़ोy sync'ed the queues.
	 */
	count = get_buf_states(q, start, &state, count, 1);
	अगर (!count)
		वापस 0;

	चयन (state) अणु
	हाल SLSB_P_INPUT_PRIMED:
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "in prim:%1d %02x", q->nr,
			      count);

		inbound_handle_work(q, start, count, is_qebsm(q));
		अगर (atomic_sub_वापस(count, &q->nr_buf_used) == 0)
			qperf_inc(q, inbound_queue_full);
		अगर (q->irq_ptr->perf_stat_enabled)
			account_sbals(q, count);
		वापस count;
	हाल SLSB_P_INPUT_ERROR:
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "in err:%1d %02x", q->nr,
			      count);

		*error = QDIO_ERROR_SLSB_STATE;
		process_buffer_error(q, start, count);
		inbound_handle_work(q, start, count, false);
		अगर (atomic_sub_वापस(count, &q->nr_buf_used) == 0)
			qperf_inc(q, inbound_queue_full);
		अगर (q->irq_ptr->perf_stat_enabled)
			account_sbals_error(q, count);
		वापस count;
	हाल SLSB_CU_INPUT_EMPTY:
		अगर (q->irq_ptr->perf_stat_enabled)
			q->q_stats.nr_sbal_nop++;
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "in nop:%1d %#02x",
			      q->nr, start);
		वापस 0;
	हाल SLSB_P_INPUT_NOT_INIT:
	हाल SLSB_P_INPUT_ACK:
		/* We should never see this state, throw a WARN: */
	शेष:
		dev_WARN_ONCE(&q->irq_ptr->cdev->dev, 1,
			      "found state %#x at index %u on queue %u\n",
			      state, start, q->nr);
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक qdio_inbound_q_करोne(काष्ठा qdio_q *q, अचिन्हित पूर्णांक start)
अणु
	अचिन्हित अक्षर state = 0;

	अगर (!atomic_पढ़ो(&q->nr_buf_used))
		वापस 1;

	अगर (need_siga_sync(q))
		qdio_siga_sync_q(q);
	get_buf_state(q, start, &state, 0);

	अगर (state == SLSB_P_INPUT_PRIMED || state == SLSB_P_INPUT_ERROR)
		/* more work coming */
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक qdio_tasklet_schedule(काष्ठा qdio_q *q)
अणु
	अगर (likely(q->irq_ptr->state == QDIO_IRQ_STATE_ACTIVE)) अणु
		tasklet_schedule(&q->u.out.tasklet);
		वापस 0;
	पूर्ण
	वापस -EPERM;
पूर्ण

अटल पूर्णांक get_outbound_buffer_frontier(काष्ठा qdio_q *q, अचिन्हित पूर्णांक start,
					अचिन्हित पूर्णांक *error)
अणु
	अचिन्हित अक्षर state = 0;
	पूर्णांक count;

	q->बारtamp = get_tod_घड़ी_fast();

	अगर (need_siga_sync(q))
		अगर (((queue_type(q) != QDIO_IQDIO_QFMT) &&
		    !pci_out_supported(q->irq_ptr)) ||
		    (queue_type(q) == QDIO_IQDIO_QFMT &&
		    multicast_outbound(q)))
			qdio_siga_sync_q(q);

	count = atomic_पढ़ो(&q->nr_buf_used);
	अगर (!count)
		वापस 0;

	count = get_buf_states(q, start, &state, count, 0);
	अगर (!count)
		वापस 0;

	चयन (state) अणु
	हाल SLSB_P_OUTPUT_PENDING:
		*error = QDIO_ERROR_SLSB_PENDING;
		fallthrough;
	हाल SLSB_P_OUTPUT_EMPTY:
		/* the adapter got it */
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr,
			"out empty:%1d %02x", q->nr, count);

		atomic_sub(count, &q->nr_buf_used);
		अगर (q->irq_ptr->perf_stat_enabled)
			account_sbals(q, count);
		वापस count;
	हाल SLSB_P_OUTPUT_ERROR:
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "out error:%1d %02x",
			      q->nr, count);

		*error = QDIO_ERROR_SLSB_STATE;
		process_buffer_error(q, start, count);
		atomic_sub(count, &q->nr_buf_used);
		अगर (q->irq_ptr->perf_stat_enabled)
			account_sbals_error(q, count);
		वापस count;
	हाल SLSB_CU_OUTPUT_PRIMED:
		/* the adapter has not fetched the output yet */
		अगर (q->irq_ptr->perf_stat_enabled)
			q->q_stats.nr_sbal_nop++;
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "out primed:%1d",
			      q->nr);
		वापस 0;
	हाल SLSB_P_OUTPUT_HALTED:
		वापस 0;
	हाल SLSB_P_OUTPUT_NOT_INIT:
		/* We should never see this state, throw a WARN: */
	शेष:
		dev_WARN_ONCE(&q->irq_ptr->cdev->dev, 1,
			      "found state %#x at index %u on queue %u\n",
			      state, start, q->nr);
		वापस 0;
	पूर्ण
पूर्ण

/* all buffers processed? */
अटल अंतरभूत पूर्णांक qdio_outbound_q_करोne(काष्ठा qdio_q *q)
अणु
	वापस atomic_पढ़ो(&q->nr_buf_used) == 0;
पूर्ण

अटल पूर्णांक qdio_kick_outbound_q(काष्ठा qdio_q *q, अचिन्हित पूर्णांक count,
				अचिन्हित दीर्घ aob)
अणु
	पूर्णांक retries = 0, cc;
	अचिन्हित पूर्णांक busy_bit;

	अगर (!need_siga_out(q))
		वापस 0;

	DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "siga-w:%1d", q->nr);
retry:
	qperf_inc(q, siga_ग_लिखो);

	cc = qdio_siga_output(q, count, &busy_bit, aob);
	चयन (cc) अणु
	हाल 0:
		अवरोध;
	हाल 2:
		अगर (busy_bit) अणु
			जबतक (++retries < QDIO_BUSY_BIT_RETRIES) अणु
				mdelay(QDIO_BUSY_BIT_RETRY_DELAY);
				जाओ retry;
			पूर्ण
			DBF_ERROR("%4x cc2 BBC:%1d", SCH_NO(q), q->nr);
			cc = -EBUSY;
		पूर्ण अन्यथा अणु
			DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "siga-w cc2:%1d", q->nr);
			cc = -ENOBUFS;
		पूर्ण
		अवरोध;
	हाल 1:
	हाल 3:
		DBF_ERROR("%4x SIGA-W:%1d", SCH_NO(q), cc);
		cc = -EIO;
		अवरोध;
	पूर्ण
	अगर (retries) अणु
		DBF_ERROR("%4x cc2 BB2:%1d", SCH_NO(q), q->nr);
		DBF_ERROR("count:%u", retries);
	पूर्ण
	वापस cc;
पूर्ण

व्योम qdio_outbound_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा qdio_output_q *out_q = from_tasklet(out_q, t, tasklet);
	काष्ठा qdio_q *q = container_of(out_q, काष्ठा qdio_q, u.out);
	अचिन्हित पूर्णांक start = q->first_to_check;
	अचिन्हित पूर्णांक error = 0;
	पूर्णांक count;

	qperf_inc(q, tasklet_outbound);
	WARN_ON_ONCE(atomic_पढ़ो(&q->nr_buf_used) < 0);

	count = get_outbound_buffer_frontier(q, start, &error);
	अगर (count) अणु
		q->first_to_check = add_buf(start, count);

		अगर (q->irq_ptr->state == QDIO_IRQ_STATE_ACTIVE) अणु
			qperf_inc(q, outbound_handler);
			DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "koh: s:%02x c:%02x",
				      start, count);

			q->handler(q->irq_ptr->cdev, error, q->nr, start,
				   count, q->irq_ptr->पूर्णांक_parm);
		पूर्ण
	पूर्ण

	अगर (queue_type(q) == QDIO_ZFCP_QFMT && !pci_out_supported(q->irq_ptr) &&
	    !qdio_outbound_q_करोne(q))
		जाओ sched;

	अगर (q->u.out.pci_out_enabled)
		वापस;

	/*
	 * Now we know that queue type is either qeth without pci enabled
	 * or HiperSockets. Make sure buffer चयन from PRIMED to EMPTY
	 * is noticed and outbound_handler is called after some समय.
	 */
	अगर (qdio_outbound_q_करोne(q))
		del_समयr_sync(&q->u.out.समयr);
	अन्यथा
		अगर (!समयr_pending(&q->u.out.समयr) &&
		    likely(q->irq_ptr->state == QDIO_IRQ_STATE_ACTIVE))
			mod_समयr(&q->u.out.समयr, jअगरfies + 10 * HZ);
	वापस;

sched:
	qdio_tasklet_schedule(q);
पूर्ण

व्योम qdio_outbound_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा qdio_q *q = from_समयr(q, t, u.out.समयr);

	qdio_tasklet_schedule(q);
पूर्ण

अटल अंतरभूत व्योम qdio_check_outbound_pci_queues(काष्ठा qdio_irq *irq)
अणु
	काष्ठा qdio_q *out;
	पूर्णांक i;

	अगर (!pci_out_supported(irq) || !irq->scan_threshold)
		वापस;

	क्रम_each_output_queue(irq, out, i)
		अगर (!qdio_outbound_q_करोne(out))
			qdio_tasklet_schedule(out);
पूर्ण

अटल अंतरभूत व्योम qdio_set_state(काष्ठा qdio_irq *irq_ptr,
				  क्रमागत qdio_irq_states state)
अणु
	DBF_DEV_EVENT(DBF_INFO, irq_ptr, "newstate: %1d", state);

	irq_ptr->state = state;
	mb();
पूर्ण

अटल व्योम qdio_irq_check_sense(काष्ठा qdio_irq *irq_ptr, काष्ठा irb *irb)
अणु
	अगर (irb->esw.esw0.erw.cons) अणु
		DBF_ERROR("%4x sense:", irq_ptr->schid.sch_no);
		DBF_ERROR_HEX(irb, 64);
		DBF_ERROR_HEX(irb->ecw, 64);
	पूर्ण
पूर्ण

/* PCI पूर्णांकerrupt handler */
अटल व्योम qdio_पूर्णांक_handler_pci(काष्ठा qdio_irq *irq_ptr)
अणु
	पूर्णांक i;
	काष्ठा qdio_q *q;

	अगर (unlikely(irq_ptr->state != QDIO_IRQ_STATE_ACTIVE))
		वापस;

	qdio_deliver_irq(irq_ptr);
	irq_ptr->last_data_irq_समय = S390_lowcore.पूर्णांक_घड़ी;

	अगर (!pci_out_supported(irq_ptr) || !irq_ptr->scan_threshold)
		वापस;

	क्रम_each_output_queue(irq_ptr, q, i) अणु
		अगर (qdio_outbound_q_करोne(q))
			जारी;
		अगर (need_siga_sync(q) && need_siga_sync_out_after_pci(q))
			qdio_siga_sync_q(q);
		qdio_tasklet_schedule(q);
	पूर्ण
पूर्ण

अटल व्योम qdio_handle_activate_check(काष्ठा qdio_irq *irq_ptr,
				       अचिन्हित दीर्घ पूर्णांकparm, पूर्णांक cstat,
				       पूर्णांक dstat)
अणु
	काष्ठा qdio_q *q;

	DBF_ERROR("%4x ACT CHECK", irq_ptr->schid.sch_no);
	DBF_ERROR("intp :%lx", पूर्णांकparm);
	DBF_ERROR("ds: %2x cs:%2x", dstat, cstat);

	अगर (irq_ptr->nr_input_qs) अणु
		q = irq_ptr->input_qs[0];
	पूर्ण अन्यथा अगर (irq_ptr->nr_output_qs) अणु
		q = irq_ptr->output_qs[0];
	पूर्ण अन्यथा अणु
		dump_stack();
		जाओ no_handler;
	पूर्ण

	q->handler(q->irq_ptr->cdev, QDIO_ERROR_ACTIVATE,
		   q->nr, q->first_to_check, 0, irq_ptr->पूर्णांक_parm);
no_handler:
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_STOPPED);
	/*
	 * In हाल of z/VM LGR (Live Guest Migration) QDIO recovery will happen.
	 * Thereक्रमe we call the LGR detection function here.
	 */
	lgr_info_log();
पूर्ण

अटल व्योम qdio_establish_handle_irq(काष्ठा qdio_irq *irq_ptr, पूर्णांक cstat,
				      पूर्णांक dstat)
अणु
	DBF_DEV_EVENT(DBF_INFO, irq_ptr, "qest irq");

	अगर (cstat)
		जाओ error;
	अगर (dstat & ~(DEV_STAT_DEV_END | DEV_STAT_CHN_END))
		जाओ error;
	अगर (!(dstat & DEV_STAT_DEV_END))
		जाओ error;
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_ESTABLISHED);
	वापस;

error:
	DBF_ERROR("%4x EQ:error", irq_ptr->schid.sch_no);
	DBF_ERROR("ds: %2x cs:%2x", dstat, cstat);
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_ERR);
पूर्ण

/* qdio पूर्णांकerrupt handler */
व्योम qdio_पूर्णांक_handler(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm,
		      काष्ठा irb *irb)
अणु
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;
	काष्ठा subchannel_id schid;
	पूर्णांक cstat, dstat;

	अगर (!पूर्णांकparm || !irq_ptr) अणु
		ccw_device_get_schid(cdev, &schid);
		DBF_ERROR("qint:%4x", schid.sch_no);
		वापस;
	पूर्ण

	अगर (irq_ptr->perf_stat_enabled)
		irq_ptr->perf_stat.qdio_पूर्णांक++;

	अगर (IS_ERR(irb)) अणु
		DBF_ERROR("%4x IO error", irq_ptr->schid.sch_no);
		qdio_set_state(irq_ptr, QDIO_IRQ_STATE_ERR);
		wake_up(&cdev->निजी->रुको_q);
		वापस;
	पूर्ण
	qdio_irq_check_sense(irq_ptr, irb);
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	चयन (irq_ptr->state) अणु
	हाल QDIO_IRQ_STATE_INACTIVE:
		qdio_establish_handle_irq(irq_ptr, cstat, dstat);
		अवरोध;
	हाल QDIO_IRQ_STATE_CLEANUP:
		qdio_set_state(irq_ptr, QDIO_IRQ_STATE_INACTIVE);
		अवरोध;
	हाल QDIO_IRQ_STATE_ESTABLISHED:
	हाल QDIO_IRQ_STATE_ACTIVE:
		अगर (cstat & SCHN_STAT_PCI) अणु
			qdio_पूर्णांक_handler_pci(irq_ptr);
			वापस;
		पूर्ण
		अगर (cstat || dstat)
			qdio_handle_activate_check(irq_ptr, पूर्णांकparm, cstat,
						   dstat);
		अवरोध;
	हाल QDIO_IRQ_STATE_STOPPED:
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
	wake_up(&cdev->निजी->रुको_q);
पूर्ण

/**
 * qdio_get_ssqd_desc - get qdio subchannel description
 * @cdev: ccw device to get description क्रम
 * @data: where to store the ssqd
 *
 * Returns 0 or an error code. The results of the chsc are stored in the
 * specअगरied काष्ठाure.
 */
पूर्णांक qdio_get_ssqd_desc(काष्ठा ccw_device *cdev,
		       काष्ठा qdio_ssqd_desc *data)
अणु
	काष्ठा subchannel_id schid;

	अगर (!cdev || !cdev->निजी)
		वापस -EINVAL;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("get ssqd:%4x", schid.sch_no);
	वापस qdio_setup_get_ssqd(शून्य, &schid, data);
पूर्ण
EXPORT_SYMBOL_GPL(qdio_get_ssqd_desc);

अटल व्योम qdio_shutकरोwn_queues(काष्ठा qdio_irq *irq_ptr)
अणु
	काष्ठा qdio_q *q;
	पूर्णांक i;

	क्रम_each_output_queue(irq_ptr, q, i) अणु
		del_समयr_sync(&q->u.out.समयr);
		tasklet_समाप्त(&q->u.out.tasklet);
	पूर्ण
पूर्ण

/**
 * qdio_shutकरोwn - shut करोwn a qdio subchannel
 * @cdev: associated ccw device
 * @how: use halt or clear to shutकरोwn
 */
पूर्णांक qdio_shutकरोwn(काष्ठा ccw_device *cdev, पूर्णांक how)
अणु
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;
	काष्ठा subchannel_id schid;
	पूर्णांक rc;

	अगर (!irq_ptr)
		वापस -ENODEV;

	WARN_ON_ONCE(irqs_disabled());
	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qshutdown:%4x", schid.sch_no);

	mutex_lock(&irq_ptr->setup_mutex);
	/*
	 * Subchannel was alपढ़ोy shot करोwn. We cannot prevent being called
	 * twice since cio may trigger a shutकरोwn asynchronously.
	 */
	अगर (irq_ptr->state == QDIO_IRQ_STATE_INACTIVE) अणु
		mutex_unlock(&irq_ptr->setup_mutex);
		वापस 0;
	पूर्ण

	/*
	 * Indicate that the device is going करोwn. Scheduling the queue
	 * tasklets is क्रमbidden from here on.
	 */
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_STOPPED);

	qdio_shutकरोwn_queues(irq_ptr);
	qdio_shutकरोwn_debug_entries(irq_ptr);

	/* cleanup subchannel */
	spin_lock_irq(get_ccwdev_lock(cdev));
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_CLEANUP);
	अगर (how & QDIO_FLAG_CLEANUP_USING_CLEAR)
		rc = ccw_device_clear(cdev, QDIO_DOING_CLEANUP);
	अन्यथा
		/* शेष behaviour is halt */
		rc = ccw_device_halt(cdev, QDIO_DOING_CLEANUP);
	spin_unlock_irq(get_ccwdev_lock(cdev));
	अगर (rc) अणु
		DBF_ERROR("%4x SHUTD ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%4d", rc);
		जाओ no_cleanup;
	पूर्ण

	रुको_event_पूर्णांकerruptible_समयout(cdev->निजी->रुको_q,
		irq_ptr->state == QDIO_IRQ_STATE_INACTIVE ||
		irq_ptr->state == QDIO_IRQ_STATE_ERR,
		10 * HZ);

no_cleanup:
	qdio_shutकरोwn_thinपूर्णांक(irq_ptr);
	qdio_shutकरोwn_irq(irq_ptr);

	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_INACTIVE);
	mutex_unlock(&irq_ptr->setup_mutex);
	अगर (rc)
		वापस rc;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qdio_shutकरोwn);

/**
 * qdio_मुक्त - मुक्त data काष्ठाures क्रम a qdio subchannel
 * @cdev: associated ccw device
 */
पूर्णांक qdio_मुक्त(काष्ठा ccw_device *cdev)
अणु
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;
	काष्ठा subchannel_id schid;

	अगर (!irq_ptr)
		वापस -ENODEV;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qfree:%4x", schid.sch_no);
	DBF_DEV_EVENT(DBF_ERR, irq_ptr, "dbf abandoned");
	mutex_lock(&irq_ptr->setup_mutex);

	irq_ptr->debug_area = शून्य;
	cdev->निजी->qdio_data = शून्य;
	mutex_unlock(&irq_ptr->setup_mutex);

	qdio_मुक्त_queues(irq_ptr);
	मुक्त_page((अचिन्हित दीर्घ) irq_ptr->qdr);
	मुक्त_page(irq_ptr->chsc_page);
	मुक्त_page((अचिन्हित दीर्घ) irq_ptr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qdio_मुक्त);

/**
 * qdio_allocate - allocate qdio queues and associated data
 * @cdev: associated ccw device
 * @no_input_qs: allocate this number of Input Queues
 * @no_output_qs: allocate this number of Output Queues
 */
पूर्णांक qdio_allocate(काष्ठा ccw_device *cdev, अचिन्हित पूर्णांक no_input_qs,
		  अचिन्हित पूर्णांक no_output_qs)
अणु
	काष्ठा subchannel_id schid;
	काष्ठा qdio_irq *irq_ptr;
	पूर्णांक rc = -ENOMEM;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qallocate:%4x", schid.sch_no);

	अगर (no_input_qs > QDIO_MAX_QUEUES_PER_IRQ ||
	    no_output_qs > QDIO_MAX_QUEUES_PER_IRQ)
		वापस -EINVAL;

	/* irq_ptr must be in GFP_DMA since it contains ccw1.cda */
	irq_ptr = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!irq_ptr)
		वापस -ENOMEM;

	irq_ptr->cdev = cdev;
	mutex_init(&irq_ptr->setup_mutex);
	अगर (qdio_allocate_dbf(irq_ptr))
		जाओ err_dbf;

	DBF_DEV_EVENT(DBF_ERR, irq_ptr, "alloc niq:%1u noq:%1u", no_input_qs,
		      no_output_qs);

	/*
	 * Allocate a page क्रम the chsc calls in qdio_establish.
	 * Must be pre-allocated since a zfcp recovery will call
	 * qdio_establish. In हाल of low memory and swap on a zfcp disk
	 * we may not be able to allocate memory otherwise.
	 */
	irq_ptr->chsc_page = get_zeroed_page(GFP_KERNEL);
	अगर (!irq_ptr->chsc_page)
		जाओ err_chsc;

	/* qdr is used in ccw1.cda which is u32 */
	irq_ptr->qdr = (काष्ठा qdr *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!irq_ptr->qdr)
		जाओ err_qdr;

	rc = qdio_allocate_qs(irq_ptr, no_input_qs, no_output_qs);
	अगर (rc)
		जाओ err_queues;

	cdev->निजी->qdio_data = irq_ptr;
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_INACTIVE);
	वापस 0;

err_queues:
	मुक्त_page((अचिन्हित दीर्घ) irq_ptr->qdr);
err_qdr:
	मुक्त_page(irq_ptr->chsc_page);
err_chsc:
err_dbf:
	मुक्त_page((अचिन्हित दीर्घ) irq_ptr);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qdio_allocate);

अटल व्योम qdio_trace_init_data(काष्ठा qdio_irq *irq,
				 काष्ठा qdio_initialize *data)
अणु
	DBF_DEV_EVENT(DBF_ERR, irq, "qfmt:%1u", data->q_क्रमmat);
	DBF_DEV_EVENT(DBF_ERR, irq, "qpff%4x", data->qib_param_field_क्रमmat);
	DBF_DEV_HEX(irq, &data->qib_param_field, माप(व्योम *), DBF_ERR);
	DBF_DEV_HEX(irq, &data->input_slib_elements, माप(व्योम *), DBF_ERR);
	DBF_DEV_HEX(irq, &data->output_slib_elements, माप(व्योम *), DBF_ERR);
	DBF_DEV_EVENT(DBF_ERR, irq, "niq:%1u noq:%1u", data->no_input_qs,
		      data->no_output_qs);
	DBF_DEV_HEX(irq, &data->input_handler, माप(व्योम *), DBF_ERR);
	DBF_DEV_HEX(irq, &data->output_handler, माप(व्योम *), DBF_ERR);
	DBF_DEV_HEX(irq, &data->पूर्णांक_parm, माप(दीर्घ), DBF_ERR);
	DBF_DEV_HEX(irq, &data->input_sbal_addr_array, माप(व्योम *), DBF_ERR);
	DBF_DEV_HEX(irq, &data->output_sbal_addr_array, माप(व्योम *),
		    DBF_ERR);
पूर्ण

/**
 * qdio_establish - establish queues on a qdio subchannel
 * @cdev: associated ccw device
 * @init_data: initialization data
 */
पूर्णांक qdio_establish(काष्ठा ccw_device *cdev,
		   काष्ठा qdio_initialize *init_data)
अणु
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;
	काष्ठा subchannel_id schid;
	पूर्णांक rc;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qestablish:%4x", schid.sch_no);

	अगर (!irq_ptr)
		वापस -ENODEV;

	अगर (init_data->no_input_qs > irq_ptr->max_input_qs ||
	    init_data->no_output_qs > irq_ptr->max_output_qs)
		वापस -EINVAL;

	अगर ((init_data->no_input_qs && !init_data->input_handler) ||
	    (init_data->no_output_qs && !init_data->output_handler))
		वापस -EINVAL;

	अगर (!init_data->input_sbal_addr_array ||
	    !init_data->output_sbal_addr_array)
		वापस -EINVAL;

	अगर (!init_data->irq_poll)
		वापस -EINVAL;

	mutex_lock(&irq_ptr->setup_mutex);
	qdio_trace_init_data(irq_ptr, init_data);
	qdio_setup_irq(irq_ptr, init_data);

	rc = qdio_establish_thinपूर्णांक(irq_ptr);
	अगर (rc) अणु
		qdio_shutकरोwn_irq(irq_ptr);
		mutex_unlock(&irq_ptr->setup_mutex);
		वापस rc;
	पूर्ण

	/* establish q */
	irq_ptr->ccw.cmd_code = irq_ptr->equeue.cmd;
	irq_ptr->ccw.flags = CCW_FLAG_SLI;
	irq_ptr->ccw.count = irq_ptr->equeue.count;
	irq_ptr->ccw.cda = (u32)((addr_t)irq_ptr->qdr);

	spin_lock_irq(get_ccwdev_lock(cdev));
	ccw_device_set_options_mask(cdev, 0);

	rc = ccw_device_start(cdev, &irq_ptr->ccw, QDIO_DOING_ESTABLISH, 0, 0);
	spin_unlock_irq(get_ccwdev_lock(cdev));
	अगर (rc) अणु
		DBF_ERROR("%4x est IO ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%4x", rc);
		qdio_shutकरोwn_thinपूर्णांक(irq_ptr);
		qdio_shutकरोwn_irq(irq_ptr);
		mutex_unlock(&irq_ptr->setup_mutex);
		वापस rc;
	पूर्ण

	रुको_event_पूर्णांकerruptible_समयout(cdev->निजी->रुको_q,
		irq_ptr->state == QDIO_IRQ_STATE_ESTABLISHED ||
		irq_ptr->state == QDIO_IRQ_STATE_ERR, HZ);

	अगर (irq_ptr->state != QDIO_IRQ_STATE_ESTABLISHED) अणु
		mutex_unlock(&irq_ptr->setup_mutex);
		qdio_shutकरोwn(cdev, QDIO_FLAG_CLEANUP_USING_CLEAR);
		वापस -EIO;
	पूर्ण

	qdio_setup_ssqd_info(irq_ptr);

	/* qebsm is now setup अगर available, initialize buffer states */
	qdio_init_buf_states(irq_ptr);

	mutex_unlock(&irq_ptr->setup_mutex);
	qdio_prपूर्णांक_subchannel_info(irq_ptr);
	qdio_setup_debug_entries(irq_ptr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qdio_establish);

/**
 * qdio_activate - activate queues on a qdio subchannel
 * @cdev: associated cdev
 */
पूर्णांक qdio_activate(काष्ठा ccw_device *cdev)
अणु
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;
	काष्ठा subchannel_id schid;
	पूर्णांक rc;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qactivate:%4x", schid.sch_no);

	अगर (!irq_ptr)
		वापस -ENODEV;

	mutex_lock(&irq_ptr->setup_mutex);
	अगर (irq_ptr->state == QDIO_IRQ_STATE_INACTIVE) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	irq_ptr->ccw.cmd_code = irq_ptr->aqueue.cmd;
	irq_ptr->ccw.flags = CCW_FLAG_SLI;
	irq_ptr->ccw.count = irq_ptr->aqueue.count;
	irq_ptr->ccw.cda = 0;

	spin_lock_irq(get_ccwdev_lock(cdev));
	ccw_device_set_options(cdev, CCWDEV_REPORT_ALL);

	rc = ccw_device_start(cdev, &irq_ptr->ccw, QDIO_DOING_ACTIVATE,
			      0, DOIO_DENY_PREFETCH);
	spin_unlock_irq(get_ccwdev_lock(cdev));
	अगर (rc) अणु
		DBF_ERROR("%4x act IO ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%4x", rc);
		जाओ out;
	पूर्ण

	/* रुको क्रम subchannel to become active */
	msleep(5);

	चयन (irq_ptr->state) अणु
	हाल QDIO_IRQ_STATE_STOPPED:
	हाल QDIO_IRQ_STATE_ERR:
		rc = -EIO;
		अवरोध;
	शेष:
		qdio_set_state(irq_ptr, QDIO_IRQ_STATE_ACTIVE);
		rc = 0;
	पूर्ण
out:
	mutex_unlock(&irq_ptr->setup_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qdio_activate);

/**
 * handle_inbound - reset processed input buffers
 * @q: queue containing the buffers
 * @callflags: flags
 * @bufnr: first buffer to process
 * @count: how many buffers are emptied
 */
अटल पूर्णांक handle_inbound(काष्ठा qdio_q *q, अचिन्हित पूर्णांक callflags,
			  पूर्णांक bufnr, पूर्णांक count)
अणु
	पूर्णांक overlap;

	qperf_inc(q, inbound_call);

	/* If any processed SBALs are वापसed to HW, adjust our tracking: */
	overlap = min_t(पूर्णांक, count - sub_buf(q->u.in.batch_start, bufnr),
			     q->u.in.batch_count);
	अगर (overlap > 0) अणु
		q->u.in.batch_start = add_buf(q->u.in.batch_start, overlap);
		q->u.in.batch_count -= overlap;
	पूर्ण

	count = set_buf_states(q, bufnr, SLSB_CU_INPUT_EMPTY, count);
	atomic_add(count, &q->nr_buf_used);

	अगर (need_siga_in(q))
		वापस qdio_siga_input(q);

	वापस 0;
पूर्ण

/**
 * handle_outbound - process filled outbound buffers
 * @q: queue containing the buffers
 * @callflags: flags
 * @bufnr: first buffer to process
 * @count: how many buffers are filled
 * @aob: asynchronous operation block
 */
अटल पूर्णांक handle_outbound(काष्ठा qdio_q *q, अचिन्हित पूर्णांक callflags,
			   अचिन्हित पूर्णांक bufnr, अचिन्हित पूर्णांक count,
			   काष्ठा qaob *aob)
अणु
	स्थिर अचिन्हित पूर्णांक scan_threshold = q->irq_ptr->scan_threshold;
	अचिन्हित अक्षर state = 0;
	पूर्णांक used, rc = 0;

	qperf_inc(q, outbound_call);

	count = set_buf_states(q, bufnr, SLSB_CU_OUTPUT_PRIMED, count);
	used = atomic_add_वापस(count, &q->nr_buf_used);

	अगर (used == QDIO_MAX_BUFFERS_PER_Q)
		qperf_inc(q, outbound_queue_full);

	अगर (callflags & QDIO_FLAG_PCI_OUT) अणु
		q->u.out.pci_out_enabled = 1;
		qperf_inc(q, pci_request_पूर्णांक);
	पूर्ण अन्यथा
		q->u.out.pci_out_enabled = 0;

	अगर (queue_type(q) == QDIO_IQDIO_QFMT) अणु
		अचिन्हित दीर्घ phys_aob = aob ? virt_to_phys(aob) : 0;

		WARN_ON_ONCE(!IS_ALIGNED(phys_aob, 256));
		rc = qdio_kick_outbound_q(q, count, phys_aob);
	पूर्ण अन्यथा अगर (need_siga_sync(q)) अणु
		rc = qdio_siga_sync_q(q);
	पूर्ण अन्यथा अगर (count < QDIO_MAX_BUFFERS_PER_Q &&
		   get_buf_state(q, prev_buf(bufnr), &state, 0) > 0 &&
		   state == SLSB_CU_OUTPUT_PRIMED) अणु
		/* The previous buffer is not processed yet, tack on. */
		qperf_inc(q, fast_requeue);
	पूर्ण अन्यथा अणु
		rc = qdio_kick_outbound_q(q, count, 0);
	पूर्ण

	/* Let drivers implement their own completion scanning: */
	अगर (!scan_threshold)
		वापस rc;

	/* in हाल of SIGA errors we must process the error immediately */
	अगर (used >= scan_threshold || rc)
		qdio_tasklet_schedule(q);
	अन्यथा
		/* मुक्त the SBALs in हाल of no further traffic */
		अगर (!समयr_pending(&q->u.out.समयr) &&
		    likely(q->irq_ptr->state == QDIO_IRQ_STATE_ACTIVE))
			mod_समयr(&q->u.out.समयr, jअगरfies + HZ);
	वापस rc;
पूर्ण

/**
 * करो_QDIO - process input or output buffers
 * @cdev: associated ccw_device क्रम the qdio subchannel
 * @callflags: input or output and special flags from the program
 * @q_nr: queue number
 * @bufnr: buffer number
 * @count: how many buffers to process
 * @aob: asynchronous operation block (outbound only)
 */
पूर्णांक करो_QDIO(काष्ठा ccw_device *cdev, अचिन्हित पूर्णांक callflags,
	    पूर्णांक q_nr, अचिन्हित पूर्णांक bufnr, अचिन्हित पूर्णांक count, काष्ठा qaob *aob)
अणु
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;

	अगर (bufnr >= QDIO_MAX_BUFFERS_PER_Q || count > QDIO_MAX_BUFFERS_PER_Q)
		वापस -EINVAL;

	अगर (!irq_ptr)
		वापस -ENODEV;

	DBF_DEV_EVENT(DBF_INFO, irq_ptr,
		      "do%02x b:%02x c:%02x", callflags, bufnr, count);

	अगर (irq_ptr->state != QDIO_IRQ_STATE_ACTIVE)
		वापस -EIO;
	अगर (!count)
		वापस 0;
	अगर (callflags & QDIO_FLAG_SYNC_INPUT)
		वापस handle_inbound(irq_ptr->input_qs[q_nr],
				      callflags, bufnr, count);
	अन्यथा अगर (callflags & QDIO_FLAG_SYNC_OUTPUT)
		वापस handle_outbound(irq_ptr->output_qs[q_nr],
				       callflags, bufnr, count, aob);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(करो_QDIO);

/**
 * qdio_start_irq - enable पूर्णांकerrupt processing क्रम the device
 * @cdev: associated ccw_device क्रम the qdio subchannel
 *
 * Return codes
 *   0 - success
 *   1 - irqs not started since new data is available
 */
पूर्णांक qdio_start_irq(काष्ठा ccw_device *cdev)
अणु
	काष्ठा qdio_q *q;
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;
	अचिन्हित पूर्णांक i;

	अगर (!irq_ptr)
		वापस -ENODEV;

	क्रम_each_input_queue(irq_ptr, q, i)
		qdio_stop_polling(q);

	clear_bit(QDIO_IRQ_DISABLED, &irq_ptr->poll_state);

	/*
	 * We need to check again to not lose initiative after
	 * resetting the ACK state.
	 */
	अगर (test_nonshared_ind(irq_ptr))
		जाओ rescan;

	क्रम_each_input_queue(irq_ptr, q, i) अणु
		अगर (!qdio_inbound_q_करोne(q, q->first_to_check))
			जाओ rescan;
	पूर्ण

	वापस 0;

rescan:
	अगर (test_and_set_bit(QDIO_IRQ_DISABLED, &irq_ptr->poll_state))
		वापस 0;
	अन्यथा
		वापस 1;

पूर्ण
EXPORT_SYMBOL(qdio_start_irq);

अटल पूर्णांक __qdio_inspect_queue(काष्ठा qdio_q *q, अचिन्हित पूर्णांक *bufnr,
				अचिन्हित पूर्णांक *error)
अणु
	अचिन्हित पूर्णांक start = q->first_to_check;
	पूर्णांक count;

	*error = 0;
	count = q->is_input_q ? get_inbound_buffer_frontier(q, start, error) :
				get_outbound_buffer_frontier(q, start, error);
	अगर (count == 0)
		वापस 0;

	*bufnr = start;

	/* क्रम the next समय */
	q->first_to_check = add_buf(start, count);

	वापस count;
पूर्ण

पूर्णांक qdio_inspect_queue(काष्ठा ccw_device *cdev, अचिन्हित पूर्णांक nr, bool is_input,
		       अचिन्हित पूर्णांक *bufnr, अचिन्हित पूर्णांक *error)
अणु
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;
	काष्ठा qdio_q *q;

	अगर (!irq_ptr)
		वापस -ENODEV;
	q = is_input ? irq_ptr->input_qs[nr] : irq_ptr->output_qs[nr];

	अगर (need_siga_sync(q))
		qdio_siga_sync_q(q);

	वापस __qdio_inspect_queue(q, bufnr, error);
पूर्ण
EXPORT_SYMBOL_GPL(qdio_inspect_queue);

/**
 * qdio_get_next_buffers - process input buffers
 * @cdev: associated ccw_device क्रम the qdio subchannel
 * @nr: input queue number
 * @bufnr: first filled buffer number
 * @error: buffers are in error state
 *
 * Return codes
 *   < 0 - error
 *   = 0 - no new buffers found
 *   > 0 - number of processed buffers
 */
पूर्णांक qdio_get_next_buffers(काष्ठा ccw_device *cdev, पूर्णांक nr, पूर्णांक *bufnr,
			  पूर्णांक *error)
अणु
	काष्ठा qdio_q *q;
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;

	अगर (!irq_ptr)
		वापस -ENODEV;
	q = irq_ptr->input_qs[nr];

	/*
	 * Cannot rely on स्वतःmatic sync after पूर्णांकerrupt since queues may
	 * also be examined without पूर्णांकerrupt.
	 */
	अगर (need_siga_sync(q))
		qdio_sync_queues(q);

	qdio_check_outbound_pci_queues(irq_ptr);

	/* Note: upper-layer MUST stop processing immediately here ... */
	अगर (unlikely(q->irq_ptr->state != QDIO_IRQ_STATE_ACTIVE))
		वापस -EIO;

	वापस __qdio_inspect_queue(q, bufnr, error);
पूर्ण
EXPORT_SYMBOL(qdio_get_next_buffers);

/**
 * qdio_stop_irq - disable पूर्णांकerrupt processing क्रम the device
 * @cdev: associated ccw_device क्रम the qdio subchannel
 *
 * Return codes
 *   0 - पूर्णांकerrupts were alपढ़ोy disabled
 *   1 - पूर्णांकerrupts successfully disabled
 */
पूर्णांक qdio_stop_irq(काष्ठा ccw_device *cdev)
अणु
	काष्ठा qdio_irq *irq_ptr = cdev->निजी->qdio_data;

	अगर (!irq_ptr)
		वापस -ENODEV;

	अगर (test_and_set_bit(QDIO_IRQ_DISABLED, &irq_ptr->poll_state))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण
EXPORT_SYMBOL(qdio_stop_irq);

अटल पूर्णांक __init init_QDIO(व्योम)
अणु
	पूर्णांक rc;

	rc = qdio_debug_init();
	अगर (rc)
		वापस rc;
	rc = qdio_setup_init();
	अगर (rc)
		जाओ out_debug;
	rc = qdio_thinपूर्णांक_init();
	अगर (rc)
		जाओ out_cache;
	वापस 0;

out_cache:
	qdio_setup_निकास();
out_debug:
	qdio_debug_निकास();
	वापस rc;
पूर्ण

अटल व्योम __निकास निकास_QDIO(व्योम)
अणु
	qdio_thinपूर्णांक_निकास();
	qdio_setup_निकास();
	qdio_debug_निकास();
पूर्ण

module_init(init_QDIO);
module_निकास(निकास_QDIO);
