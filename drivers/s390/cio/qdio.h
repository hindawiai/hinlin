<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2000, 2009
 * Author(s): Utz Bacher <utz.bacher@de.ibm.com>
 *	      Jan Glauber <jang@linux.vnet.ibm.com>
 */
#अगर_अघोषित _CIO_QDIO_H
#घोषणा _CIO_QDIO_H

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/schid.h>
#समावेश <यंत्र/debug.h>
#समावेश "chsc.h"

#घोषणा QDIO_BUSY_BIT_PATIENCE		(100 << 12)	/* 100 microseconds */
#घोषणा QDIO_BUSY_BIT_RETRY_DELAY	10		/* 10 milliseconds */
#घोषणा QDIO_BUSY_BIT_RETRIES		1000		/* = 10s retry समय */

क्रमागत qdio_irq_states अणु
	QDIO_IRQ_STATE_INACTIVE,
	QDIO_IRQ_STATE_ESTABLISHED,
	QDIO_IRQ_STATE_ACTIVE,
	QDIO_IRQ_STATE_STOPPED,
	QDIO_IRQ_STATE_CLEANUP,
	QDIO_IRQ_STATE_ERR,
	NR_QDIO_IRQ_STATES,
पूर्ण;

/* used as पूर्णांकparm in करो_IO */
#घोषणा QDIO_DOING_ESTABLISH	1
#घोषणा QDIO_DOING_ACTIVATE	2
#घोषणा QDIO_DOING_CLEANUP	3

#घोषणा SLSB_STATE_NOT_INIT	0x0
#घोषणा SLSB_STATE_EMPTY	0x1
#घोषणा SLSB_STATE_PRIMED	0x2
#घोषणा SLSB_STATE_PENDING	0x3
#घोषणा SLSB_STATE_HALTED	0xe
#घोषणा SLSB_STATE_ERROR	0xf
#घोषणा SLSB_TYPE_INPUT		0x0
#घोषणा SLSB_TYPE_OUTPUT	0x20
#घोषणा SLSB_OWNER_PROG		0x80
#घोषणा SLSB_OWNER_CU		0x40

#घोषणा SLSB_P_INPUT_NOT_INIT	\
	(SLSB_OWNER_PROG | SLSB_TYPE_INPUT | SLSB_STATE_NOT_INIT)  /* 0x80 */
#घोषणा SLSB_P_INPUT_ACK	\
	(SLSB_OWNER_PROG | SLSB_TYPE_INPUT | SLSB_STATE_EMPTY)	   /* 0x81 */
#घोषणा SLSB_CU_INPUT_EMPTY	\
	(SLSB_OWNER_CU | SLSB_TYPE_INPUT | SLSB_STATE_EMPTY)	   /* 0x41 */
#घोषणा SLSB_P_INPUT_PRIMED	\
	(SLSB_OWNER_PROG | SLSB_TYPE_INPUT | SLSB_STATE_PRIMED)	   /* 0x82 */
#घोषणा SLSB_P_INPUT_HALTED	\
	(SLSB_OWNER_PROG | SLSB_TYPE_INPUT | SLSB_STATE_HALTED)	   /* 0x8e */
#घोषणा SLSB_P_INPUT_ERROR	\
	(SLSB_OWNER_PROG | SLSB_TYPE_INPUT | SLSB_STATE_ERROR)	   /* 0x8f */
#घोषणा SLSB_P_OUTPUT_NOT_INIT	\
	(SLSB_OWNER_PROG | SLSB_TYPE_OUTPUT | SLSB_STATE_NOT_INIT) /* 0xa0 */
#घोषणा SLSB_P_OUTPUT_EMPTY	\
	(SLSB_OWNER_PROG | SLSB_TYPE_OUTPUT | SLSB_STATE_EMPTY)	   /* 0xa1 */
#घोषणा SLSB_P_OUTPUT_PENDING \
	(SLSB_OWNER_PROG | SLSB_TYPE_OUTPUT | SLSB_STATE_PENDING)  /* 0xa3 */
#घोषणा SLSB_CU_OUTPUT_PRIMED	\
	(SLSB_OWNER_CU | SLSB_TYPE_OUTPUT | SLSB_STATE_PRIMED)	   /* 0x62 */
#घोषणा SLSB_P_OUTPUT_HALTED	\
	(SLSB_OWNER_PROG | SLSB_TYPE_OUTPUT | SLSB_STATE_HALTED)   /* 0xae */
#घोषणा SLSB_P_OUTPUT_ERROR	\
	(SLSB_OWNER_PROG | SLSB_TYPE_OUTPUT | SLSB_STATE_ERROR)	   /* 0xaf */

#घोषणा SLSB_ERROR_DURING_LOOKUP  0xff

/* additional CIWs वापसed by extended Sense-ID */
#घोषणा CIW_TYPE_EQUEUE			0x3 /* establish QDIO queues */
#घोषणा CIW_TYPE_AQUEUE			0x4 /* activate QDIO queues */

/* flags क्रम st qdio sch data */
#घोषणा CHSC_FLAG_QDIO_CAPABILITY	0x80
#घोषणा CHSC_FLAG_VALIDITY		0x40

/* SIGA flags */
#घोषणा QDIO_SIGA_WRITE		0x00
#घोषणा QDIO_SIGA_READ		0x01
#घोषणा QDIO_SIGA_SYNC		0x02
#घोषणा QDIO_SIGA_WRITEM	0x03
#घोषणा QDIO_SIGA_WRITEQ	0x04
#घोषणा QDIO_SIGA_QEBSM_FLAG	0x80

अटल अंतरभूत पूर्णांक करो_sqbs(u64 token, अचिन्हित अक्षर state, पूर्णांक queue,
			  पूर्णांक *start, पूर्णांक *count)
अणु
	रेजिस्टर अचिन्हित दीर्घ _ccq यंत्र ("0") = *count;
	रेजिस्टर अचिन्हित दीर्घ _token यंत्र ("1") = token;
	अचिन्हित दीर्घ _queuestart = ((अचिन्हित दीर्घ)queue << 32) | *start;

	यंत्र अस्थिर(
		"	.insn	rsy,0xeb000000008A,%1,0,0(%2)"
		: "+d" (_ccq), "+d" (_queuestart)
		: "d" ((अचिन्हित दीर्घ)state), "d" (_token)
		: "memory", "cc");
	*count = _ccq & 0xff;
	*start = _queuestart & 0xff;

	वापस (_ccq >> 32) & 0xff;
पूर्ण

अटल अंतरभूत पूर्णांक करो_eqbs(u64 token, अचिन्हित अक्षर *state, पूर्णांक queue,
			  पूर्णांक *start, पूर्णांक *count, पूर्णांक ack)
अणु
	रेजिस्टर अचिन्हित दीर्घ _ccq यंत्र ("0") = *count;
	रेजिस्टर अचिन्हित दीर्घ _token यंत्र ("1") = token;
	अचिन्हित दीर्घ _queuestart = ((अचिन्हित दीर्घ)queue << 32) | *start;
	अचिन्हित दीर्घ _state = (अचिन्हित दीर्घ)ack << 63;

	यंत्र अस्थिर(
		"	.insn	rrf,0xB99c0000,%1,%2,0,0"
		: "+d" (_ccq), "+d" (_queuestart), "+d" (_state)
		: "d" (_token)
		: "memory", "cc");
	*count = _ccq & 0xff;
	*start = _queuestart & 0xff;
	*state = _state & 0xff;

	वापस (_ccq >> 32) & 0xff;
पूर्ण

काष्ठा qdio_irq;

काष्ठा siga_flag अणु
	u8 input:1;
	u8 output:1;
	u8 sync:1;
	u8 sync_after_ai:1;
	u8 sync_out_after_pci:1;
	u8:3;
पूर्ण __attribute__ ((packed));

काष्ठा qdio_dev_perf_stat अणु
	अचिन्हित पूर्णांक adapter_पूर्णांक;
	अचिन्हित पूर्णांक qdio_पूर्णांक;
	अचिन्हित पूर्णांक pci_request_पूर्णांक;

	अचिन्हित पूर्णांक tasklet_outbound;

	अचिन्हित पूर्णांक siga_पढ़ो;
	अचिन्हित पूर्णांक siga_ग_लिखो;
	अचिन्हित पूर्णांक siga_sync;

	अचिन्हित पूर्णांक inbound_call;
	अचिन्हित पूर्णांक stop_polling;
	अचिन्हित पूर्णांक inbound_queue_full;
	अचिन्हित पूर्णांक outbound_call;
	अचिन्हित पूर्णांक outbound_handler;
	अचिन्हित पूर्णांक outbound_queue_full;
	अचिन्हित पूर्णांक fast_requeue;
	अचिन्हित पूर्णांक target_full;
	अचिन्हित पूर्णांक eqbs;
	अचिन्हित पूर्णांक eqbs_partial;
	अचिन्हित पूर्णांक sqbs;
	अचिन्हित पूर्णांक sqbs_partial;
	अचिन्हित पूर्णांक पूर्णांक_discarded;
पूर्ण ____cacheline_aligned;

काष्ठा qdio_queue_perf_stat अणु
	/* Sorted पूर्णांकo order-2 buckets: 1, 2-3, 4-7, ... 64-127, 128. */
	अचिन्हित पूर्णांक nr_sbals[8];
	अचिन्हित पूर्णांक nr_sbal_error;
	अचिन्हित पूर्णांक nr_sbal_nop;
	अचिन्हित पूर्णांक nr_sbal_total;
पूर्ण;

क्रमागत qdio_irq_poll_states अणु
	QDIO_IRQ_DISABLED,
पूर्ण;

काष्ठा qdio_input_q अणु
	/* Batch of SBALs that we processed जबतक polling the queue: */
	अचिन्हित पूर्णांक batch_start;
	अचिन्हित पूर्णांक batch_count;
पूर्ण;

काष्ठा qdio_output_q अणु
	/* PCIs are enabled क्रम the queue */
	पूर्णांक pci_out_enabled;
	/* समयr to check क्रम more outbound work */
	काष्ठा समयr_list समयr;
	/* tasklet to check क्रम completions */
	काष्ठा tasklet_काष्ठा tasklet;
पूर्ण;

/*
 * Note on cache alignment: grouped slsb and ग_लिखो mostly data at the beginning
 * sbal[] is पढ़ो-only and starts on a new cacheline followed by पढ़ो mostly.
 */
काष्ठा qdio_q अणु
	काष्ठा slsb slsb;

	जोड़ अणु
		काष्ठा qdio_input_q in;
		काष्ठा qdio_output_q out;
	पूर्ण u;

	/*
	 * inbound: next buffer the program should check क्रम
	 * outbound: next buffer to check अगर adapter processed it
	 */
	पूर्णांक first_to_check;

	/* number of buffers in use by the adapter */
	atomic_t nr_buf_used;

	/* last scan of the queue */
	u64 बारtamp;

	काष्ठा qdio_queue_perf_stat q_stats;

	काष्ठा qdio_buffer *sbal[QDIO_MAX_BUFFERS_PER_Q] ____cacheline_aligned;

	/* queue number */
	पूर्णांक nr;

	/* biपंचांगask of queue number */
	पूर्णांक mask;

	/* input or output queue */
	पूर्णांक is_input_q;

	/* upper-layer program handler */
	qdio_handler_t (*handler);

	काष्ठा qdio_irq *irq_ptr;
	काष्ठा sl *sl;
	/*
	 * A page is allocated under this poपूर्णांकer and used क्रम slib and sl.
	 * slib is 2048 bytes big and sl poपूर्णांकs to offset PAGE_SIZE / 2.
	 */
	काष्ठा slib *slib;
पूर्ण __attribute__ ((aligned(256)));

काष्ठा qdio_irq अणु
	काष्ठा qib qib;
	u32 *dsci;		/* address of device state change indicator */
	काष्ठा ccw_device *cdev;
	काष्ठा list_head entry;		/* list of thinपूर्णांक devices */
	काष्ठा dentry *debugfs_dev;
	u64 last_data_irq_समय;

	अचिन्हित दीर्घ पूर्णांक_parm;
	काष्ठा subchannel_id schid;
	अचिन्हित दीर्घ sch_token;	/* QEBSM facility */

	क्रमागत qdio_irq_states state;

	काष्ठा siga_flag siga_flag;	/* siga sync inक्रमmation from qdioac */

	पूर्णांक nr_input_qs;
	पूर्णांक nr_output_qs;

	काष्ठा ccw1 ccw;
	काष्ठा ciw equeue;
	काष्ठा ciw aqueue;

	काष्ठा qdio_ssqd_desc ssqd_desc;
	व्योम (*orig_handler) (काष्ठा ccw_device *, अचिन्हित दीर्घ, काष्ठा irb *);

	अचिन्हित पूर्णांक scan_threshold;	/* used SBALs beक्रमe tasklet schedule */
	पूर्णांक perf_stat_enabled;

	काष्ठा qdr *qdr;
	अचिन्हित दीर्घ chsc_page;

	काष्ठा qdio_q *input_qs[QDIO_MAX_QUEUES_PER_IRQ];
	काष्ठा qdio_q *output_qs[QDIO_MAX_QUEUES_PER_IRQ];
	अचिन्हित पूर्णांक max_input_qs;
	अचिन्हित पूर्णांक max_output_qs;

	व्योम (*irq_poll)(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ data);
	अचिन्हित दीर्घ poll_state;

	debug_info_t *debug_area;
	काष्ठा mutex setup_mutex;
	काष्ठा qdio_dev_perf_stat perf_stat;
पूर्ण;

/* helper functions */
#घोषणा queue_type(q)	q->irq_ptr->qib.qfmt
#घोषणा SCH_NO(q)	(q->irq_ptr->schid.sch_no)

#घोषणा is_thinपूर्णांक_irq(irq) \
	(irq->qib.qfmt == QDIO_IQDIO_QFMT || \
	 css_general_अक्षरacteristics.aअगर_osa)

#घोषणा qperf(__qdev, __attr)	((__qdev)->perf_stat.(__attr))

#घोषणा QDIO_PERF_STAT_INC(__irq, __attr)				\
(अणु									\
	काष्ठा qdio_irq *qdev = __irq;					\
	अगर (qdev->perf_stat_enabled)					\
		(qdev->perf_stat.__attr)++;				\
पूर्ण)

#घोषणा qperf_inc(__q, __attr)	QDIO_PERF_STAT_INC((__q)->irq_ptr, __attr)

अटल अंतरभूत व्योम account_sbals_error(काष्ठा qdio_q *q, पूर्णांक count)
अणु
	q->q_stats.nr_sbal_error += count;
	q->q_stats.nr_sbal_total += count;
पूर्ण

/* the highest iqdio queue is used क्रम multicast */
अटल अंतरभूत पूर्णांक multicast_outbound(काष्ठा qdio_q *q)
अणु
	वापस (q->irq_ptr->nr_output_qs > 1) &&
	       (q->nr == q->irq_ptr->nr_output_qs - 1);
पूर्ण

अटल अंतरभूत व्योम qdio_deliver_irq(काष्ठा qdio_irq *irq)
अणु
	अगर (!test_and_set_bit(QDIO_IRQ_DISABLED, &irq->poll_state))
		irq->irq_poll(irq->cdev, irq->पूर्णांक_parm);
	अन्यथा
		QDIO_PERF_STAT_INC(irq, पूर्णांक_discarded);
पूर्ण

#घोषणा pci_out_supported(irq) ((irq)->qib.ac & QIB_AC_OUTBOUND_PCI_SUPPORTED)
#घोषणा is_qebsm(q)			(q->irq_ptr->sch_token != 0)

#घोषणा need_siga_in(q)			(q->irq_ptr->siga_flag.input)
#घोषणा need_siga_out(q)		(q->irq_ptr->siga_flag.output)
#घोषणा need_siga_sync(q)		(unlikely(q->irq_ptr->siga_flag.sync))
#घोषणा need_siga_sync_after_ai(q)	\
	(unlikely(q->irq_ptr->siga_flag.sync_after_ai))
#घोषणा need_siga_sync_out_after_pci(q)	\
	(unlikely(q->irq_ptr->siga_flag.sync_out_after_pci))

#घोषणा क्रम_each_input_queue(irq_ptr, q, i)		\
	क्रम (i = 0; i < irq_ptr->nr_input_qs &&		\
		(अणु q = irq_ptr->input_qs[i]; 1; पूर्ण); i++)
#घोषणा क्रम_each_output_queue(irq_ptr, q, i)		\
	क्रम (i = 0; i < irq_ptr->nr_output_qs &&	\
		(अणु q = irq_ptr->output_qs[i]; 1; पूर्ण); i++)

#घोषणा add_buf(bufnr, inc)	QDIO_BUFNR((bufnr) + (inc))
#घोषणा next_buf(bufnr)		add_buf(bufnr, 1)
#घोषणा sub_buf(bufnr, dec)	QDIO_BUFNR((bufnr) - (dec))
#घोषणा prev_buf(bufnr)		sub_buf(bufnr, 1)

#घोषणा queue_irqs_enabled(q)			\
	(test_bit(QDIO_QUEUE_IRQS_DISABLED, &q->u.in.queue_irq_state) == 0)
#घोषणा queue_irqs_disabled(q)			\
	(test_bit(QDIO_QUEUE_IRQS_DISABLED, &q->u.in.queue_irq_state) != 0)

बाह्य u64 last_ai_समय;

/* prototypes क्रम thin पूर्णांकerrupt */
पूर्णांक qdio_establish_thinपूर्णांक(काष्ठा qdio_irq *irq_ptr);
व्योम qdio_shutकरोwn_thinपूर्णांक(काष्ठा qdio_irq *irq_ptr);
पूर्णांक qdio_thinपूर्णांक_init(व्योम);
व्योम qdio_thinपूर्णांक_निकास(व्योम);
पूर्णांक test_nonshared_ind(काष्ठा qdio_irq *);

/* prototypes क्रम setup */
व्योम qdio_outbound_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम qdio_outbound_समयr(काष्ठा समयr_list *t);
व्योम qdio_पूर्णांक_handler(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm,
		      काष्ठा irb *irb);
पूर्णांक qdio_allocate_qs(काष्ठा qdio_irq *irq_ptr, पूर्णांक nr_input_qs,
		     पूर्णांक nr_output_qs);
व्योम qdio_setup_ssqd_info(काष्ठा qdio_irq *irq_ptr);
पूर्णांक qdio_setup_get_ssqd(काष्ठा qdio_irq *irq_ptr,
			काष्ठा subchannel_id *schid,
			काष्ठा qdio_ssqd_desc *data);
पूर्णांक qdio_setup_irq(काष्ठा qdio_irq *irq_ptr, काष्ठा qdio_initialize *init_data);
व्योम qdio_shutकरोwn_irq(काष्ठा qdio_irq *irq);
व्योम qdio_prपूर्णांक_subchannel_info(काष्ठा qdio_irq *irq_ptr);
व्योम qdio_मुक्त_queues(काष्ठा qdio_irq *irq_ptr);
पूर्णांक qdio_setup_init(व्योम);
व्योम qdio_setup_निकास(व्योम);

पूर्णांक debug_get_buf_state(काष्ठा qdio_q *q, अचिन्हित पूर्णांक bufnr,
			अचिन्हित अक्षर *state);
#पूर्ण_अगर /* _CIO_QDIO_H */
