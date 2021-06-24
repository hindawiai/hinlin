<शैली गुरु>
/*
 * This file is part of the Chelsio T6 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2017-2018 Chelsio Communications, Inc. All rights reserved.
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
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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

#अगर_अघोषित __CXGB4_SRQ_H
#घोषणा __CXGB4_SRQ_H

काष्ठा adapter;
काष्ठा cpl_srq_table_rpl;

#घोषणा SRQ_WAIT_TO	(HZ * 5)

काष्ठा srq_entry अणु
	u8 valid;
	u8 idx;
	u8 qlen;
	u16 pdid;
	u16 cur_msn;
	u16 max_msn;
	u32 qbase;
पूर्ण;

काष्ठा srq_data अणु
	अचिन्हित पूर्णांक srq_size;
	काष्ठा srq_entry *entryp;
	काष्ठा completion comp;
	काष्ठा mutex lock; /* generic mutex क्रम srq data */
पूर्ण;

काष्ठा srq_data *t4_init_srq(पूर्णांक srq_size);
पूर्णांक cxgb4_get_srq_entry(काष्ठा net_device *dev,
			पूर्णांक srq_idx, काष्ठा srq_entry *entryp);
व्योम करो_srq_table_rpl(काष्ठा adapter *adap,
		      स्थिर काष्ठा cpl_srq_table_rpl *rpl);
#पूर्ण_अगर  /* __CXGB4_SRQ_H */
