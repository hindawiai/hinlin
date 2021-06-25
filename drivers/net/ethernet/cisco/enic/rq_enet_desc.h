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

#अगर_अघोषित _RQ_ENET_DESC_H_
#घोषणा _RQ_ENET_DESC_H_

/* Ethernet receive queue descriptor: 16B */
काष्ठा rq_enet_desc अणु
	__le64 address;
	__le16 length_type;
	u8 reserved[6];
पूर्ण;

क्रमागत rq_enet_type_types अणु
	RQ_ENET_TYPE_ONLY_SOP = 0,
	RQ_ENET_TYPE_NOT_SOP = 1,
	RQ_ENET_TYPE_RESV2 = 2,
	RQ_ENET_TYPE_RESV3 = 3,
पूर्ण;

#घोषणा RQ_ENET_ADDR_BITS		64
#घोषणा RQ_ENET_LEN_BITS		14
#घोषणा RQ_ENET_LEN_MASK		((1 << RQ_ENET_LEN_BITS) - 1)
#घोषणा RQ_ENET_TYPE_BITS		2
#घोषणा RQ_ENET_TYPE_MASK		((1 << RQ_ENET_TYPE_BITS) - 1)

अटल अंतरभूत व्योम rq_enet_desc_enc(काष्ठा rq_enet_desc *desc,
	u64 address, u8 type, u16 length)
अणु
	desc->address = cpu_to_le64(address);
	desc->length_type = cpu_to_le16((length & RQ_ENET_LEN_MASK) |
		((type & RQ_ENET_TYPE_MASK) << RQ_ENET_LEN_BITS));
पूर्ण

अटल अंतरभूत व्योम rq_enet_desc_dec(काष्ठा rq_enet_desc *desc,
	u64 *address, u8 *type, u16 *length)
अणु
	*address = le64_to_cpu(desc->address);
	*length = le16_to_cpu(desc->length_type) & RQ_ENET_LEN_MASK;
	*type = (u8)((le16_to_cpu(desc->length_type) >> RQ_ENET_LEN_BITS) &
		RQ_ENET_TYPE_MASK);
पूर्ण

#पूर्ण_अगर /* _RQ_ENET_DESC_H_ */
