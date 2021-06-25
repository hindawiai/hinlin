<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CXGB4_TC_U32_H
#घोषणा __CXGB4_TC_U32_H

#समावेश <net/pkt_cls.h>

अटल अंतरभूत bool can_tc_u32_offload(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	वापस (dev->features & NETIF_F_HW_TC) && adap->tc_u32 ? true : false;
पूर्ण

पूर्णांक cxgb4_config_knode(काष्ठा net_device *dev, काष्ठा tc_cls_u32_offload *cls);
पूर्णांक cxgb4_delete_knode(काष्ठा net_device *dev, काष्ठा tc_cls_u32_offload *cls);

व्योम cxgb4_cleanup_tc_u32(काष्ठा adapter *adapter);
काष्ठा cxgb4_tc_u32_table *cxgb4_init_tc_u32(काष्ठा adapter *adap);
#पूर्ण_अगर /* __CXGB4_TC_U32_H */
