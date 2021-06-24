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

#अगर_अघोषित _VNIC_CQ_H_
#घोषणा _VNIC_CQ_H_

#समावेश "cq_desc.h"
#समावेश "vnic_dev.h"

/* Completion queue control */
काष्ठा vnic_cq_ctrl अणु
	u64 ring_base;			/* 0x00 */
	u32 ring_size;			/* 0x08 */
	u32 pad0;
	u32 flow_control_enable;	/* 0x10 */
	u32 pad1;
	u32 color_enable;		/* 0x18 */
	u32 pad2;
	u32 cq_head;			/* 0x20 */
	u32 pad3;
	u32 cq_tail;			/* 0x28 */
	u32 pad4;
	u32 cq_tail_color;		/* 0x30 */
	u32 pad5;
	u32 पूर्णांकerrupt_enable;		/* 0x38 */
	u32 pad6;
	u32 cq_entry_enable;		/* 0x40 */
	u32 pad7;
	u32 cq_message_enable;		/* 0x48 */
	u32 pad8;
	u32 पूर्णांकerrupt_offset;		/* 0x50 */
	u32 pad9;
	u64 cq_message_addr;		/* 0x58 */
	u32 pad10;
पूर्ण;

काष्ठा vnic_rx_bytes_counter अणु
	अचिन्हित पूर्णांक small_pkt_bytes_cnt;
	अचिन्हित पूर्णांक large_pkt_bytes_cnt;
पूर्ण;

काष्ठा vnic_cq अणु
	अचिन्हित पूर्णांक index;
	काष्ठा vnic_dev *vdev;
	काष्ठा vnic_cq_ctrl __iomem *ctrl;              /* memory-mapped */
	काष्ठा vnic_dev_ring ring;
	अचिन्हित पूर्णांक to_clean;
	अचिन्हित पूर्णांक last_color;
	अचिन्हित पूर्णांक पूर्णांकerrupt_offset;
	काष्ठा vnic_rx_bytes_counter pkt_size_counter;
	अचिन्हित पूर्णांक cur_rx_coal_समयval;
	अचिन्हित पूर्णांक tobe_rx_coal_समयval;
	kसमय_प्रकार prev_ts;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक vnic_cq_service(काष्ठा vnic_cq *cq,
	अचिन्हित पूर्णांक work_to_करो,
	पूर्णांक (*q_service)(काष्ठा vnic_dev *vdev, काष्ठा cq_desc *cq_desc,
	u8 type, u16 q_number, u16 completed_index, व्योम *opaque),
	व्योम *opaque)
अणु
	काष्ठा cq_desc *cq_desc;
	अचिन्हित पूर्णांक work_करोne = 0;
	u16 q_number, completed_index;
	u8 type, color;

	cq_desc = (काष्ठा cq_desc *)((u8 *)cq->ring.descs +
		cq->ring.desc_size * cq->to_clean);
	cq_desc_dec(cq_desc, &type, &color,
		&q_number, &completed_index);

	जबतक (color != cq->last_color) अणु

		अगर ((*q_service)(cq->vdev, cq_desc, type,
			q_number, completed_index, opaque))
			अवरोध;

		cq->to_clean++;
		अगर (cq->to_clean == cq->ring.desc_count) अणु
			cq->to_clean = 0;
			cq->last_color = cq->last_color ? 0 : 1;
		पूर्ण

		cq_desc = (काष्ठा cq_desc *)((u8 *)cq->ring.descs +
			cq->ring.desc_size * cq->to_clean);
		cq_desc_dec(cq_desc, &type, &color,
			&q_number, &completed_index);

		work_करोne++;
		अगर (work_करोne >= work_to_करो)
			अवरोध;
	पूर्ण

	वापस work_करोne;
पूर्ण

व्योम vnic_cq_मुक्त(काष्ठा vnic_cq *cq);
पूर्णांक vnic_cq_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_cq *cq, अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size);
व्योम vnic_cq_init(काष्ठा vnic_cq *cq, अचिन्हित पूर्णांक flow_control_enable,
	अचिन्हित पूर्णांक color_enable, अचिन्हित पूर्णांक cq_head, अचिन्हित पूर्णांक cq_tail,
	अचिन्हित पूर्णांक cq_tail_color, अचिन्हित पूर्णांक पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक cq_entry_enable, अचिन्हित पूर्णांक message_enable,
	अचिन्हित पूर्णांक पूर्णांकerrupt_offset, u64 message_addr);
व्योम vnic_cq_clean(काष्ठा vnic_cq *cq);

#पूर्ण_अगर /* _VNIC_CQ_H_ */
