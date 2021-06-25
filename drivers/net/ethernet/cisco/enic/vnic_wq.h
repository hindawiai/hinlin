<शैली गुरु>
/*
 * Copyright 2008-2010 Cisco Systems, Inc.  All rights reserved.
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
 *
 */

#अगर_अघोषित _VNIC_WQ_H_
#घोषणा _VNIC_WQ_H_

#समावेश <linux/pci.h>

#समावेश "vnic_dev.h"
#समावेश "vnic_cq.h"

/* Work queue control */
काष्ठा vnic_wq_ctrl अणु
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
	u32 dca_value;			/* 0x38 */
	u32 pad6;
	u32 error_पूर्णांकerrupt_enable;	/* 0x40 */
	u32 pad7;
	u32 error_पूर्णांकerrupt_offset;	/* 0x48 */
	u32 pad8;
	u32 error_status;		/* 0x50 */
	u32 pad9;
पूर्ण;

काष्ठा vnic_wq_buf अणु
	काष्ठा vnic_wq_buf *next;
	dma_addr_t dma_addr;
	व्योम *os_buf;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक index;
	पूर्णांक sop;
	व्योम *desc;
	uपूर्णांक64_t wr_id; /* Cookie */
	uपूर्णांक8_t cq_entry; /* Gets completion event from hw */
	uपूर्णांक8_t desc_skip_cnt; /* Num descs to occupy */
	uपूर्णांक8_t compressed_send; /* Both hdr and payload in one desc */
	काष्ठा vnic_wq_buf *prev;
पूर्ण;

/* Break the vnic_wq_buf allocations पूर्णांकo blocks of 32/64 entries */
#घोषणा VNIC_WQ_BUF_MIN_BLK_ENTRIES 32
#घोषणा VNIC_WQ_BUF_DFLT_BLK_ENTRIES 64
#घोषणा VNIC_WQ_BUF_BLK_ENTRIES(entries) \
	((अचिन्हित पूर्णांक)((entries < VNIC_WQ_BUF_DFLT_BLK_ENTRIES) ? \
	VNIC_WQ_BUF_MIN_BLK_ENTRIES : VNIC_WQ_BUF_DFLT_BLK_ENTRIES))
#घोषणा VNIC_WQ_BUF_BLK_SZ(entries) \
	(VNIC_WQ_BUF_BLK_ENTRIES(entries) * माप(काष्ठा vnic_wq_buf))
#घोषणा VNIC_WQ_BUF_BLKS_NEEDED(entries) \
	DIV_ROUND_UP(entries, VNIC_WQ_BUF_BLK_ENTRIES(entries))
#घोषणा VNIC_WQ_BUF_BLKS_MAX VNIC_WQ_BUF_BLKS_NEEDED(4096)

काष्ठा vnic_wq अणु
	अचिन्हित पूर्णांक index;
	काष्ठा vnic_dev *vdev;
	काष्ठा vnic_wq_ctrl __iomem *ctrl;              /* memory-mapped */
	काष्ठा vnic_dev_ring ring;
	काष्ठा vnic_wq_buf *bufs[VNIC_WQ_BUF_BLKS_MAX];
	काष्ठा vnic_wq_buf *to_use;
	काष्ठा vnic_wq_buf *to_clean;
	अचिन्हित पूर्णांक pkts_outstanding;
पूर्ण;

काष्ठा devcmd2_controller अणु
	काष्ठा vnic_wq_ctrl __iomem *wq_ctrl;
	काष्ठा vnic_devcmd2 *cmd_ring;
	काष्ठा devcmd2_result *result;
	u16 next_result;
	u16 result_size;
	पूर्णांक color;
	काष्ठा vnic_dev_ring results_ring;
	काष्ठा vnic_wq wq;
	u32 posted;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक vnic_wq_desc_avail(काष्ठा vnic_wq *wq)
अणु
	/* how many करोes SW own? */
	वापस wq->ring.desc_avail;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vnic_wq_desc_used(काष्ठा vnic_wq *wq)
अणु
	/* how many करोes HW own? */
	वापस wq->ring.desc_count - wq->ring.desc_avail - 1;
पूर्ण

अटल अंतरभूत व्योम *vnic_wq_next_desc(काष्ठा vnic_wq *wq)
अणु
	वापस wq->to_use->desc;
पूर्ण

अटल अंतरभूत व्योम vnic_wq_करोorbell(काष्ठा vnic_wq *wq)
अणु
	/* Adding ग_लिखो memory barrier prevents compiler and/or CPU
	 * reordering, thus aव्योमing descriptor posting beक्रमe
	 * descriptor is initialized. Otherwise, hardware can पढ़ो
	 * stale descriptor fields.
	 */
	wmb();
	ioग_लिखो32(wq->to_use->index, &wq->ctrl->posted_index);
पूर्ण

अटल अंतरभूत व्योम vnic_wq_post(काष्ठा vnic_wq *wq,
	व्योम *os_buf, dma_addr_t dma_addr,
	अचिन्हित पूर्णांक len, पूर्णांक sop, पूर्णांक eop,
	uपूर्णांक8_t desc_skip_cnt, uपूर्णांक8_t cq_entry,
	uपूर्णांक8_t compressed_send, uपूर्णांक64_t wrid)
अणु
	काष्ठा vnic_wq_buf *buf = wq->to_use;

	buf->sop = sop;
	buf->cq_entry = cq_entry;
	buf->compressed_send = compressed_send;
	buf->desc_skip_cnt = desc_skip_cnt;
	buf->os_buf = eop ? os_buf : शून्य;
	buf->dma_addr = dma_addr;
	buf->len = len;
	buf->wr_id = wrid;

	buf = buf->next;
	wq->to_use = buf;

	wq->ring.desc_avail -= desc_skip_cnt;
पूर्ण

अटल अंतरभूत व्योम vnic_wq_service(काष्ठा vnic_wq *wq,
	काष्ठा cq_desc *cq_desc, u16 completed_index,
	व्योम (*buf_service)(काष्ठा vnic_wq *wq,
	काष्ठा cq_desc *cq_desc, काष्ठा vnic_wq_buf *buf, व्योम *opaque),
	व्योम *opaque)
अणु
	काष्ठा vnic_wq_buf *buf;

	buf = wq->to_clean;
	जबतक (1) अणु

		(*buf_service)(wq, cq_desc, buf, opaque);

		wq->ring.desc_avail++;

		wq->to_clean = buf->next;

		अगर (buf->index == completed_index)
			अवरोध;

		buf = wq->to_clean;
	पूर्ण
पूर्ण

व्योम vnic_wq_मुक्त(काष्ठा vnic_wq *wq);
पूर्णांक vnic_wq_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq *wq, अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size);
व्योम vnic_wq_init(काष्ठा vnic_wq *wq, अचिन्हित पूर्णांक cq_index,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset);
अचिन्हित पूर्णांक vnic_wq_error_status(काष्ठा vnic_wq *wq);
व्योम vnic_wq_enable(काष्ठा vnic_wq *wq);
पूर्णांक vnic_wq_disable(काष्ठा vnic_wq *wq);
व्योम vnic_wq_clean(काष्ठा vnic_wq *wq,
	व्योम (*buf_clean)(काष्ठा vnic_wq *wq, काष्ठा vnic_wq_buf *buf));
पूर्णांक enic_wq_devcmd2_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq *wq,
			  अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size);
व्योम enic_wq_init_start(काष्ठा vnic_wq *wq, अचिन्हित पूर्णांक cq_index,
			अचिन्हित पूर्णांक fetch_index, अचिन्हित पूर्णांक posted_index,
			अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
			अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset);

#पूर्ण_अगर /* _VNIC_WQ_H_ */
