<शैली गुरु>
/*
 * Copyright (c) 2015 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *	- Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *	- Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
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
#अगर_अघोषित ISCSI_ISER_H
#घोषणा ISCSI_ISER_H

#घोषणा ISER_ZBVA_NOT_SUP		0x80
#घोषणा ISER_SEND_W_INV_NOT_SUP		0x40
#घोषणा ISERT_ZBVA_NOT_USED		0x80
#घोषणा ISERT_SEND_W_INV_NOT_USED	0x40

#घोषणा ISCSI_CTRL	0x10
#घोषणा ISER_HELLO	0x20
#घोषणा ISER_HELLORPLY	0x30

#घोषणा ISER_VER	0x10
#घोषणा ISER_WSV	0x08
#घोषणा ISER_RSV	0x04

/**
 * काष्ठा iser_cm_hdr - iSER CM header (from iSER Annex A12)
 *
 * @flags:        flags support (zbva, send_w_inv)
 * @rsvd:         reserved
 */
काष्ठा iser_cm_hdr अणु
	u8      flags;
	u8      rsvd[3];
पूर्ण __packed;

/**
 * काष्ठा iser_ctrl - iSER header of iSCSI control PDU
 *
 * @flags:        opcode and पढ़ो/ग_लिखो valid bits
 * @rsvd:         reserved
 * @ग_लिखो_stag:   ग_लिखो rkey
 * @ग_लिखो_va:     ग_लिखो भव address
 * @reaf_stag:    पढ़ो rkey
 * @पढ़ो_va:      पढ़ो भव address
 */
काष्ठा iser_ctrl अणु
	u8      flags;
	u8      rsvd[3];
	__be32  ग_लिखो_stag;
	__be64  ग_लिखो_va;
	__be32  पढ़ो_stag;
	__be64  पढ़ो_va;
पूर्ण __packed;

#पूर्ण_अगर /* ISCSI_ISER_H */
