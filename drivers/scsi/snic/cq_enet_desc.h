<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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

#अगर_अघोषित _CQ_ENET_DESC_H_
#घोषणा _CQ_ENET_DESC_H_

#समावेश "cq_desc.h"

/* Ethernet completion queue descriptor: 16B */
काष्ठा cq_enet_wq_desc अणु
	__le16 completed_index;
	__le16 q_number;
	u8 reserved[11];
	u8 type_color;
पूर्ण;

अटल अंतरभूत व्योम cq_enet_wq_desc_dec(काष्ठा cq_enet_wq_desc *desc,
	u8 *type, u8 *color, u16 *q_number, u16 *completed_index)
अणु
	cq_desc_dec((काष्ठा cq_desc *)desc, type,
		color, q_number, completed_index);
पूर्ण

#पूर्ण_अगर /* _CQ_ENET_DESC_H_ */
