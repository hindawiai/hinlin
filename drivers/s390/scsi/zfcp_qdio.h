<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zfcp device driver
 *
 * Header file क्रम zfcp qdio पूर्णांकerface
 *
 * Copyright IBM Corp. 2010
 */

#अगर_अघोषित ZFCP_QDIO_H
#घोषणा ZFCP_QDIO_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/qdपन.स>

#घोषणा ZFCP_QDIO_SBALE_LEN	PAGE_SIZE

/* Max SBALS क्रम chaining */
#घोषणा ZFCP_QDIO_MAX_SBALS_PER_REQ	36

/**
 * काष्ठा zfcp_qdio - basic qdio data काष्ठाure
 * @res_q: response queue
 * @req_q: request queue
 * @req_q_idx: index of next मुक्त buffer
 * @req_q_मुक्त: number of मुक्त buffers in queue
 * @stat_lock: lock to protect req_q_util and req_q_समय
 * @req_q_lock: lock to serialize access to request queue
 * @req_q_समय: समय of last fill level change
 * @req_q_util: used क्रम accounting
 * @req_q_full: queue full incidents
 * @req_q_wq: used to रुको क्रम SBAL availability
 * @irq_tasklet: used क्रम QDIO पूर्णांकerrupt processing
 * @request_tasklet: used क्रम Request Queue completion processing
 * @request_समयr: used to trigger the Request Queue completion processing
 * @adapter: adapter used in conjunction with this qdio काष्ठाure
 * @max_sbale_per_sbal: qdio limit per sbal
 * @max_sbale_per_req: qdio limit per request
 */
काष्ठा zfcp_qdio अणु
	काष्ठा qdio_buffer	*res_q[QDIO_MAX_BUFFERS_PER_Q];
	काष्ठा qdio_buffer	*req_q[QDIO_MAX_BUFFERS_PER_Q];
	u8			req_q_idx;
	atomic_t		req_q_मुक्त;
	spinlock_t		stat_lock;
	spinlock_t		req_q_lock;
	अचिन्हित दीर्घ दीर्घ	req_q_समय;
	u64			req_q_util;
	atomic_t		req_q_full;
	रुको_queue_head_t	req_q_wq;
	काष्ठा tasklet_काष्ठा	irq_tasklet;
	काष्ठा tasklet_काष्ठा	request_tasklet;
	काष्ठा समयr_list	request_समयr;
	काष्ठा zfcp_adapter	*adapter;
	u16			max_sbale_per_sbal;
	u16			max_sbale_per_req;
पूर्ण;

/**
 * काष्ठा zfcp_qdio_req - qdio queue related values क्रम a request
 * @sbtype: sbal type flags क्रम sbale 0
 * @sbal_number: number of मुक्त sbals
 * @sbal_first: first sbal क्रम this request
 * @sbal_last: last sbal क्रम this request
 * @sbal_limit: last possible sbal क्रम this request
 * @sbale_curr: current sbale at creation of this request
 * @qdio_outb_usage: usage of outbound queue
 */
काष्ठा zfcp_qdio_req अणु
	u8	sbtype;
	u8	sbal_number;
	u8	sbal_first;
	u8	sbal_last;
	u8	sbal_limit;
	u8	sbale_curr;
	u16	qdio_outb_usage;
पूर्ण;

/**
 * zfcp_qdio_sbale_req - वापस poपूर्णांकer to sbale on req_q क्रम a request
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: poपूर्णांकer to काष्ठा zfcp_qdio_req
 * Returns: poपूर्णांकer to qdio_buffer_element (sbale) काष्ठाure
 */
अटल अंतरभूत काष्ठा qdio_buffer_element *
zfcp_qdio_sbale_req(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req)
अणु
	वापस &qdio->req_q[q_req->sbal_last]->element[0];
पूर्ण

/**
 * zfcp_qdio_sbale_curr - वापस current sbale on req_q क्रम a request
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: poपूर्णांकer to काष्ठा zfcp_qdio_req
 * Returns: poपूर्णांकer to qdio_buffer_element (sbale) काष्ठाure
 */
अटल अंतरभूत काष्ठा qdio_buffer_element *
zfcp_qdio_sbale_curr(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req)
अणु
	वापस &qdio->req_q[q_req->sbal_last]->element[q_req->sbale_curr];
पूर्ण

/**
 * zfcp_qdio_req_init - initialize qdio request
 * @qdio: request queue where to start putting the request
 * @q_req: the qdio request to start
 * @req_id: The request id
 * @sbtype: type flags to set क्रम all sbals
 * @data: First data block
 * @len: Length of first data block
 *
 * This is the start of putting the request पूर्णांकo the queue, the last
 * step is passing the request to zfcp_qdio_send. The request queue
 * lock must be held during the whole process from init to send.
 */
अटल अंतरभूत
व्योम zfcp_qdio_req_init(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req,
			अचिन्हित दीर्घ req_id, u8 sbtype, व्योम *data, u32 len)
अणु
	काष्ठा qdio_buffer_element *sbale;
	पूर्णांक count = min(atomic_पढ़ो(&qdio->req_q_मुक्त),
			ZFCP_QDIO_MAX_SBALS_PER_REQ);

	q_req->sbal_first = q_req->sbal_last = qdio->req_q_idx;
	q_req->sbal_number = 1;
	q_req->sbtype = sbtype;
	q_req->sbale_curr = 1;
	q_req->sbal_limit = (q_req->sbal_first + count - 1)
					% QDIO_MAX_BUFFERS_PER_Q;

	sbale = zfcp_qdio_sbale_req(qdio, q_req);
	sbale->addr = req_id;
	sbale->eflags = 0;
	sbale->sflags = SBAL_SFLAGS0_COMMAND | sbtype;

	अगर (unlikely(!data))
		वापस;
	sbale++;
	sbale->addr = virt_to_phys(data);
	sbale->length = len;
पूर्ण

/**
 * zfcp_qdio_fill_next - Fill next sbale, only क्रम single sbal requests
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: poपूर्णांकer to काष्ठा zfcp_queue_req
 * @data: poपूर्णांकer to data
 * @len: length of data
 *
 * This is only required क्रम single sbal requests, calling it when
 * wrapping around to the next sbal is a bug.
 */
अटल अंतरभूत
व्योम zfcp_qdio_fill_next(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req,
			 व्योम *data, u32 len)
अणु
	काष्ठा qdio_buffer_element *sbale;

	BUG_ON(q_req->sbale_curr == qdio->max_sbale_per_sbal - 1);
	q_req->sbale_curr++;
	sbale = zfcp_qdio_sbale_curr(qdio, q_req);
	sbale->addr = virt_to_phys(data);
	sbale->length = len;
पूर्ण

/**
 * zfcp_qdio_set_sbale_last - set last entry flag in current sbale
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: poपूर्णांकer to काष्ठा zfcp_queue_req
 */
अटल अंतरभूत
व्योम zfcp_qdio_set_sbale_last(काष्ठा zfcp_qdio *qdio,
			      काष्ठा zfcp_qdio_req *q_req)
अणु
	काष्ठा qdio_buffer_element *sbale;

	sbale = zfcp_qdio_sbale_curr(qdio, q_req);
	sbale->eflags |= SBAL_EFLAGS_LAST_ENTRY;
पूर्ण

/**
 * zfcp_qdio_sg_one_sbal - check अगर one sbale is enough क्रम sg data
 * @sg: The scatterlist where to check the data size
 *
 * Returns: 1 when one sbale is enough क्रम the data in the scatterlist,
 *	    0 अगर not.
 */
अटल अंतरभूत
पूर्णांक zfcp_qdio_sg_one_sbale(काष्ठा scatterlist *sg)
अणु
	वापस sg_is_last(sg) && sg->length <= ZFCP_QDIO_SBALE_LEN;
पूर्ण

/**
 * zfcp_qdio_skip_to_last_sbale - skip to last sbale in sbal
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: The current zfcp_qdio_req
 */
अटल अंतरभूत
व्योम zfcp_qdio_skip_to_last_sbale(काष्ठा zfcp_qdio *qdio,
				  काष्ठा zfcp_qdio_req *q_req)
अणु
	q_req->sbale_curr = qdio->max_sbale_per_sbal - 1;
पूर्ण

/**
 * zfcp_qdio_sbal_limit - set the sbal limit क्रम a request in q_req
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: The current zfcp_qdio_req
 * @max_sbals: maximum number of SBALs allowed
 */
अटल अंतरभूत
व्योम zfcp_qdio_sbal_limit(काष्ठा zfcp_qdio *qdio,
			  काष्ठा zfcp_qdio_req *q_req, पूर्णांक max_sbals)
अणु
	पूर्णांक count = min(atomic_पढ़ो(&qdio->req_q_मुक्त), max_sbals);

	q_req->sbal_limit = (q_req->sbal_first + count - 1) %
				QDIO_MAX_BUFFERS_PER_Q;
पूर्ण

/**
 * zfcp_qdio_set_data_भाग - set data भागision count
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: The current zfcp_qdio_req
 * @count: The data भागision count
 */
अटल अंतरभूत
व्योम zfcp_qdio_set_data_भाग(काष्ठा zfcp_qdio *qdio,
			    काष्ठा zfcp_qdio_req *q_req, u32 count)
अणु
	काष्ठा qdio_buffer_element *sbale;

	sbale = qdio->req_q[q_req->sbal_first]->element;
	sbale->length = count;
पूर्ण

/**
 * zfcp_qdio_real_bytes - count bytes used
 * @sg: poपूर्णांकer to काष्ठा scatterlist
 */
अटल अंतरभूत
अचिन्हित पूर्णांक zfcp_qdio_real_bytes(काष्ठा scatterlist *sg)
अणु
	अचिन्हित पूर्णांक real_bytes = 0;

	क्रम (; sg; sg = sg_next(sg))
		real_bytes += sg->length;

	वापस real_bytes;
पूर्ण

/**
 * zfcp_qdio_set_scount - set SBAL count value
 * @qdio: poपूर्णांकer to काष्ठा zfcp_qdio
 * @q_req: The current zfcp_qdio_req
 */
अटल अंतरभूत
व्योम zfcp_qdio_set_scount(काष्ठा zfcp_qdio *qdio, काष्ठा zfcp_qdio_req *q_req)
अणु
	काष्ठा qdio_buffer_element *sbale;

	sbale = qdio->req_q[q_req->sbal_first]->element;
	sbale->scount = q_req->sbal_number - 1;
पूर्ण

#पूर्ण_अगर /* ZFCP_QDIO_H */
