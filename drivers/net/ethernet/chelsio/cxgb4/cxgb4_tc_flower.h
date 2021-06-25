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

#अगर_अघोषित __CXGB4_TC_FLOWER_H
#घोषणा __CXGB4_TC_FLOWER_H

#समावेश <net/pkt_cls.h>

काष्ठा ch_tc_flower_stats अणु
	u64 prev_packet_count;
	u64 packet_count;
	u64 byte_count;
	u64 last_used;
पूर्ण;

काष्ठा ch_tc_flower_entry अणु
	काष्ठा ch_filter_specअगरication fs;
	काष्ठा ch_tc_flower_stats stats;
	अचिन्हित दीर्घ tc_flower_cookie;
	काष्ठा rhash_head node;
	काष्ठा rcu_head rcu;
	spinlock_t lock; /* lock क्रम stats */
	u32 filter_id;
पूर्ण;

क्रमागत अणु
	ETH_DMAC_31_0,	/* dmac bits 0.. 31 */
	ETH_DMAC_47_32,	/* dmac bits 32..47 */
	ETH_SMAC_15_0,	/* smac bits 0.. 15 */
	ETH_SMAC_47_16,	/* smac bits 16..47 */

	IP4_SRC,	/* 32-bit IPv4 src  */
	IP4_DST,	/* 32-bit IPv4 dst  */

	IP6_SRC_31_0,	/* src bits 0..  31 */
	IP6_SRC_63_32,	/* src bits 63.. 32 */
	IP6_SRC_95_64,	/* src bits 95.. 64 */
	IP6_SRC_127_96,	/* src bits 127..96 */

	IP6_DST_31_0,	/* dst bits 0..  31 */
	IP6_DST_63_32,	/* dst bits 63.. 32 */
	IP6_DST_95_64,	/* dst bits 95.. 64 */
	IP6_DST_127_96,	/* dst bits 127..96 */

	TCP_SPORT,	/* 16-bit TCP sport */
	TCP_DPORT,	/* 16-bit TCP dport */

	UDP_SPORT,	/* 16-bit UDP sport */
	UDP_DPORT,	/* 16-bit UDP dport */
पूर्ण;

काष्ठा ch_tc_pedit_fields अणु
	u8 field;
	u8 size;
	u32 offset;
पूर्ण;

#घोषणा PEDIT_FIELDS(type, field, size, fs_field, offset) \
	अणु type## field, size, \
		दुरत्व(काष्ठा ch_filter_specअगरication, fs_field) + (offset) पूर्ण

#घोषणा PEDIT_ETH_DMAC_MASK		0xffff
#घोषणा PEDIT_TCP_UDP_SPORT_MASK	0xffff
#घोषणा PEDIT_ETH_DMAC_31_0		0x0
#घोषणा PEDIT_ETH_DMAC_47_32_SMAC_15_0	0x4
#घोषणा PEDIT_ETH_SMAC_47_16		0x8
#घोषणा PEDIT_IP4_SRC			0xC
#घोषणा PEDIT_IP4_DST			0x10
#घोषणा PEDIT_IP6_SRC_31_0		0x8
#घोषणा PEDIT_IP6_SRC_63_32		0xC
#घोषणा PEDIT_IP6_SRC_95_64		0x10
#घोषणा PEDIT_IP6_SRC_127_96		0x14
#घोषणा PEDIT_IP6_DST_31_0		0x18
#घोषणा PEDIT_IP6_DST_63_32		0x1C
#घोषणा PEDIT_IP6_DST_95_64		0x20
#घोषणा PEDIT_IP6_DST_127_96		0x24
#घोषणा PEDIT_TCP_SPORT_DPORT		0x0
#घोषणा PEDIT_UDP_SPORT_DPORT		0x0

क्रमागत cxgb4_action_naपंचांगode_flags अणु
	CXGB4_ACTION_NATMODE_NONE = 0,
	CXGB4_ACTION_NATMODE_DIP = (1 << 0),
	CXGB4_ACTION_NATMODE_SIP = (1 << 1),
	CXGB4_ACTION_NATMODE_DPORT = (1 << 2),
	CXGB4_ACTION_NATMODE_SPORT = (1 << 3),
पूर्ण;

/* TC PEDIT action to NATMODE translation entry */
काष्ठा cxgb4_naपंचांगode_config अणु
	क्रमागत chip_type chip;
	u8 flags;
	u8 naपंचांगode;
पूर्ण;

व्योम cxgb4_process_flow_actions(काष्ठा net_device *in,
				काष्ठा flow_action *actions,
				काष्ठा ch_filter_specअगरication *fs);
पूर्णांक cxgb4_validate_flow_actions(काष्ठा net_device *dev,
				काष्ठा flow_action *actions,
				काष्ठा netlink_ext_ack *extack,
				u8 matchall_filter);

पूर्णांक cxgb4_tc_flower_replace(काष्ठा net_device *dev,
			    काष्ठा flow_cls_offload *cls);
पूर्णांक cxgb4_tc_flower_destroy(काष्ठा net_device *dev,
			    काष्ठा flow_cls_offload *cls);
पूर्णांक cxgb4_tc_flower_stats(काष्ठा net_device *dev,
			  काष्ठा flow_cls_offload *cls);
पूर्णांक cxgb4_flow_rule_replace(काष्ठा net_device *dev, काष्ठा flow_rule *rule,
			    u32 tc_prio, काष्ठा netlink_ext_ack *extack,
			    काष्ठा ch_filter_specअगरication *fs, u32 *tid);
पूर्णांक cxgb4_flow_rule_destroy(काष्ठा net_device *dev, u32 tc_prio,
			    काष्ठा ch_filter_specअगरication *fs, पूर्णांक tid);

पूर्णांक cxgb4_init_tc_flower(काष्ठा adapter *adap);
व्योम cxgb4_cleanup_tc_flower(काष्ठा adapter *adap);
#पूर्ण_अगर /* __CXGB4_TC_FLOWER_H */
