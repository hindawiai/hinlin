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

#अगर_अघोषित _CQ_DESC_H_
#घोषणा _CQ_DESC_H_

/*
 * Completion queue descriptor types
 */
क्रमागत cq_desc_types अणु
	CQ_DESC_TYPE_WQ_ENET = 0,
	CQ_DESC_TYPE_DESC_COPY = 1,
	CQ_DESC_TYPE_WQ_EXCH = 2,
	CQ_DESC_TYPE_RQ_ENET = 3,
	CQ_DESC_TYPE_RQ_FCP = 4,
पूर्ण;

/* Completion queue descriptor: 16B
 *
 * All completion queues have this basic layout.  The
 * type_specfic area is unique क्रम each completion
 * queue type.
 */
काष्ठा cq_desc अणु
	__le16 completed_index;
	__le16 q_number;
	u8 type_specfic[11];
	u8 type_color;
पूर्ण;

#घोषणा CQ_DESC_TYPE_BITS        4
#घोषणा CQ_DESC_TYPE_MASK        ((1 << CQ_DESC_TYPE_BITS) - 1)
#घोषणा CQ_DESC_COLOR_MASK       1
#घोषणा CQ_DESC_COLOR_SHIFT      7
#घोषणा CQ_DESC_Q_NUM_BITS       10
#घोषणा CQ_DESC_Q_NUM_MASK       ((1 << CQ_DESC_Q_NUM_BITS) - 1)
#घोषणा CQ_DESC_COMP_NDX_BITS    12
#घोषणा CQ_DESC_COMP_NDX_MASK    ((1 << CQ_DESC_COMP_NDX_BITS) - 1)

अटल अंतरभूत व्योम cq_desc_dec(स्थिर काष्ठा cq_desc *desc_arg,
	u8 *type, u8 *color, u16 *q_number, u16 *completed_index)
अणु
	स्थिर काष्ठा cq_desc *desc = desc_arg;
	स्थिर u8 type_color = desc->type_color;

	*color = (type_color >> CQ_DESC_COLOR_SHIFT) & CQ_DESC_COLOR_MASK;

	/*
	 * Make sure color bit is पढ़ो from desc *beक्रमe* other fields
	 * are पढ़ो from desc.  Hardware guarantees color bit is last
	 * bit (byte) written.  Adding the rmb() prevents the compiler
	 * and/or CPU from reordering the पढ़ोs which would potentially
	 * result in पढ़ोing stale values.
	 */

	rmb();

	*type = type_color & CQ_DESC_TYPE_MASK;
	*q_number = le16_to_cpu(desc->q_number) & CQ_DESC_Q_NUM_MASK;
	*completed_index = le16_to_cpu(desc->completed_index) &
		CQ_DESC_COMP_NDX_MASK;
पूर्ण

#पूर्ण_अगर /* _CQ_DESC_H_ */
