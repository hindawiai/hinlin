<शैली गुरु>
/*
 * This file is part of the Chelsio T4/T5/T6 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2017 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CXGB4_SMT_H
#घोषणा __CXGB4_SMT_H

#समावेश <linux/spinlock.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/atomic.h>

काष्ठा adapter;
काष्ठा cpl_smt_ग_लिखो_rpl;

/* SMT related handling. Heavily adapted based on l2t ops in l2t.h/l2t.c
 */
क्रमागत अणु
	SMT_STATE_SWITCHING,
	SMT_STATE_UNUSED,
	SMT_STATE_ERROR
पूर्ण;

क्रमागत अणु
	SMT_SIZE = 256
पूर्ण;

काष्ठा smt_entry अणु
	u16 state;
	u16 idx;
	u16 pfvf;
	u8 src_mac[ETH_ALEN];
	पूर्णांक refcnt;
	spinlock_t lock;	/* protect smt entry add,removal */
पूर्ण;

काष्ठा smt_data अणु
	अचिन्हित पूर्णांक smt_size;
	rwlock_t lock;
	काष्ठा smt_entry smtab[];
पूर्ण;

काष्ठा smt_data *t4_init_smt(व्योम);
काष्ठा smt_entry *cxgb4_smt_alloc_चयनing(काष्ठा net_device *dev, u8 *smac);
व्योम cxgb4_smt_release(काष्ठा smt_entry *e);
व्योम करो_smt_ग_लिखो_rpl(काष्ठा adapter *p, स्थिर काष्ठा cpl_smt_ग_लिखो_rpl *rpl);
#पूर्ण_अगर /* __CXGB4_SMT_H */
