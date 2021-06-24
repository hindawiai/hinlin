<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#अगर_अघोषित _VNIC_RQ_H_
#घोषणा _VNIC_RQ_H_

#समावेश <linux/pci.h>
#समावेश "vnic_dev.h"
#समावेश "vnic_cq.h"

/*
 * These defines aव्योम symbol clash between fnic and enic (Cisco 10G Eth
 * Driver) when both are built with CONFIG options =y
 */
#घोषणा vnic_rq_desc_avail fnic_rq_desc_avail
#घोषणा vnic_rq_desc_used fnic_rq_desc_used
#घोषणा vnic_rq_next_desc fnic_rq_next_desc
#घोषणा vnic_rq_next_index fnic_rq_next_index
#घोषणा vnic_rq_next_buf_index fnic_rq_next_buf_index
#घोषणा vnic_rq_post fnic_rq_post
#घोषणा vnic_rq_posting_soon fnic_rq_posting_soon
#घोषणा vnic_rq_वापस_descs fnic_rq_वापस_descs
#घोषणा vnic_rq_service fnic_rq_service
#घोषणा vnic_rq_fill fnic_rq_fill
#घोषणा vnic_rq_मुक्त fnic_rq_मुक्त
#घोषणा vnic_rq_alloc fnic_rq_alloc
#घोषणा vnic_rq_init fnic_rq_init
#घोषणा vnic_rq_error_status fnic_rq_error_status
#घोषणा vnic_rq_enable fnic_rq_enable
#घोषणा vnic_rq_disable fnic_rq_disable
#घोषणा vnic_rq_clean fnic_rq_clean

/* Receive queue control */
काष्ठा vnic_rq_ctrl अणु
	u64 ring_base;			/* 0x00 */
	u32 ring_size;			/* 0x08 */
	u32 pad0;
	u32 posted_index;		/* 0x10 */
	u32 pad1;
	u32 cq_index;			/* 0x18 */
	u32 pad2;
	u32 enable;			/* 0x20 */
	u32 pad3;
	u32 running;			/* 0x28 */
	u32 pad4;
	u32 fetch_index;		/* 0x30 */
	u32 pad5;
	u32 error_पूर्णांकerrupt_enable;	/* 0x38 */
	u32 pad6;
	u32 error_पूर्णांकerrupt_offset;	/* 0x40 */
	u32 pad7;
	u32 error_status;		/* 0x48 */
	u32 pad8;
	u32 dropped_packet_count;	/* 0x50 */
	u32 pad9;
	u32 dropped_packet_count_rc;	/* 0x58 */
	u32 pad10;
पूर्ण;

/* Break the vnic_rq_buf allocations पूर्णांकo blocks of 64 entries */
#घोषणा VNIC_RQ_BUF_BLK_ENTRIES 64
#घोषणा VNIC_RQ_BUF_BLK_SZ \
	(VNIC_RQ_BUF_BLK_ENTRIES * माप(काष्ठा vnic_rq_buf))
#घोषणा VNIC_RQ_BUF_BLKS_NEEDED(entries) \
	DIV_ROUND_UP(entries, VNIC_RQ_BUF_BLK_ENTRIES)
#घोषणा VNIC_RQ_BUF_BLKS_MAX VNIC_RQ_BUF_BLKS_NEEDED(4096)

काष्ठा vnic_rq_buf अणु
	काष्ठा vnic_rq_buf *next;
	dma_addr_t dma_addr;
	व्योम *os_buf;
	अचिन्हित पूर्णांक os_buf_index;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक index;
	व्योम *desc;
पूर्ण;

काष्ठा vnic_rq अणु
	अचिन्हित पूर्णांक index;
	काष्ठा vnic_dev *vdev;
	काष्ठा vnic_rq_ctrl __iomem *ctrl;	/* memory-mapped */
	काष्ठा vnic_dev_ring ring;
	काष्ठा vnic_rq_buf *bufs[VNIC_RQ_BUF_BLKS_MAX];
	काष्ठा vnic_rq_buf *to_use;
	काष्ठा vnic_rq_buf *to_clean;
	व्योम *os_buf_head;
	अचिन्हित पूर्णांक buf_index;
	अचिन्हित पूर्णांक pkts_outstanding;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक vnic_rq_desc_avail(काष्ठा vnic_rq *rq)
अणु
	/* how many करोes SW own? */
	वापस rq->ring.desc_avail;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vnic_rq_desc_used(काष्ठा vnic_rq *rq)
अणु
	/* how many करोes HW own? */
	वापस rq->ring.desc_count - rq->ring.desc_avail - 1;
पूर्ण

अटल अंतरभूत व्योम *vnic_rq_next_desc(काष्ठा vnic_rq *rq)
अणु
	वापस rq->to_use->desc;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vnic_rq_next_index(काष्ठा vnic_rq *rq)
अणु
	वापस rq->to_use->index;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vnic_rq_next_buf_index(काष्ठा vnic_rq *rq)
अणु
	वापस rq->buf_index++;
पूर्ण

अटल अंतरभूत व्योम vnic_rq_post(काष्ठा vnic_rq *rq,
	व्योम *os_buf, अचिन्हित पूर्णांक os_buf_index,
	dma_addr_t dma_addr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vnic_rq_buf *buf = rq->to_use;

	buf->os_buf = os_buf;
	buf->os_buf_index = os_buf_index;
	buf->dma_addr = dma_addr;
	buf->len = len;

	buf = buf->next;
	rq->to_use = buf;
	rq->ring.desc_avail--;

	/* Move the posted_index every nth descriptor
	 */

#अगर_अघोषित VNIC_RQ_RETURN_RATE
#घोषणा VNIC_RQ_RETURN_RATE		0xf	/* keep 2^n - 1 */
#पूर्ण_अगर

	अगर ((buf->index & VNIC_RQ_RETURN_RATE) == 0) अणु
		/* Adding ग_लिखो memory barrier prevents compiler and/or CPU
		 * reordering, thus aव्योमing descriptor posting beक्रमe
		 * descriptor is initialized. Otherwise, hardware can पढ़ो
		 * stale descriptor fields.
		 */
		wmb();
		ioग_लिखो32(buf->index, &rq->ctrl->posted_index);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक vnic_rq_posting_soon(काष्ठा vnic_rq *rq)
अणु
	वापस (rq->to_use->index & VNIC_RQ_RETURN_RATE) == 0;
पूर्ण

अटल अंतरभूत व्योम vnic_rq_वापस_descs(काष्ठा vnic_rq *rq, अचिन्हित पूर्णांक count)
अणु
	rq->ring.desc_avail += count;
पूर्ण

क्रमागत desc_वापस_options अणु
	VNIC_RQ_RETURN_DESC,
	VNIC_RQ_DEFER_RETURN_DESC,
पूर्ण;

अटल अंतरभूत व्योम vnic_rq_service(काष्ठा vnic_rq *rq,
	काष्ठा cq_desc *cq_desc, u16 completed_index,
	पूर्णांक desc_वापस, व्योम (*buf_service)(काष्ठा vnic_rq *rq,
	काष्ठा cq_desc *cq_desc, काष्ठा vnic_rq_buf *buf,
	पूर्णांक skipped, व्योम *opaque), व्योम *opaque)
अणु
	काष्ठा vnic_rq_buf *buf;
	पूर्णांक skipped;

	buf = rq->to_clean;
	जबतक (1) अणु

		skipped = (buf->index != completed_index);

		(*buf_service)(rq, cq_desc, buf, skipped, opaque);

		अगर (desc_वापस == VNIC_RQ_RETURN_DESC)
			rq->ring.desc_avail++;

		rq->to_clean = buf->next;

		अगर (!skipped)
			अवरोध;

		buf = rq->to_clean;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक vnic_rq_fill(काष्ठा vnic_rq *rq,
	पूर्णांक (*buf_fill)(काष्ठा vnic_rq *rq))
अणु
	पूर्णांक err;

	जबतक (vnic_rq_desc_avail(rq) > 1) अणु

		err = (*buf_fill)(rq);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम vnic_rq_मुक्त(काष्ठा vnic_rq *rq);
पूर्णांक vnic_rq_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_rq *rq, अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size);
व्योम vnic_rq_init(काष्ठा vnic_rq *rq, अचिन्हित पूर्णांक cq_index,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset);
अचिन्हित पूर्णांक vnic_rq_error_status(काष्ठा vnic_rq *rq);
व्योम vnic_rq_enable(काष्ठा vnic_rq *rq);
पूर्णांक vnic_rq_disable(काष्ठा vnic_rq *rq);
व्योम vnic_rq_clean(काष्ठा vnic_rq *rq,
	व्योम (*buf_clean)(काष्ठा vnic_rq *rq, काष्ठा vnic_rq_buf *buf));

#पूर्ण_अगर /* _VNIC_RQ_H_ */
