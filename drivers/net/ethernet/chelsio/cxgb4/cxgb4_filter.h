<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CXGB4_FILTER_H
#घोषणा __CXGB4_FILTER_H

#समावेश "t4_msg.h"

#घोषणा WORD_MASK	0xffffffff

व्योम filter_rpl(काष्ठा adapter *adap, स्थिर काष्ठा cpl_set_tcb_rpl *rpl);
व्योम hash_filter_rpl(काष्ठा adapter *adap, स्थिर काष्ठा cpl_act_खोलो_rpl *rpl);
व्योम hash_del_filter_rpl(काष्ठा adapter *adap,
			 स्थिर काष्ठा cpl_पात_rpl_rss *rpl);
व्योम clear_filter(काष्ठा adapter *adap, काष्ठा filter_entry *f);

पूर्णांक set_filter_wr(काष्ठा adapter *adapter, पूर्णांक fidx);
पूर्णांक delete_filter(काष्ठा adapter *adapter, अचिन्हित पूर्णांक fidx);

पूर्णांक writable_filter(काष्ठा filter_entry *f);
व्योम clear_all_filters(काष्ठा adapter *adapter);
व्योम init_hash_filter(काष्ठा adapter *adap);
bool is_filter_exact_match(काष्ठा adapter *adap,
			   काष्ठा ch_filter_specअगरication *fs);
व्योम cxgb4_cleanup_ethtool_filters(काष्ठा adapter *adap);
पूर्णांक cxgb4_init_ethtool_filters(काष्ठा adapter *adap);
#पूर्ण_अगर /* __CXGB4_FILTER_H */
