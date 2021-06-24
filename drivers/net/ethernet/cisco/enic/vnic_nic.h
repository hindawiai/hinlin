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

#अगर_अघोषित _VNIC_NIC_H_
#घोषणा _VNIC_NIC_H_

#घोषणा NIC_CFG_RSS_DEFAULT_CPU_MASK_FIELD	0xffUL
#घोषणा NIC_CFG_RSS_DEFAULT_CPU_SHIFT		0
#घोषणा NIC_CFG_RSS_HASH_TYPE			(0xffUL << 8)
#घोषणा NIC_CFG_RSS_HASH_TYPE_MASK_FIELD	0xffUL
#घोषणा NIC_CFG_RSS_HASH_TYPE_SHIFT		8
#घोषणा NIC_CFG_RSS_HASH_BITS			(7UL << 16)
#घोषणा NIC_CFG_RSS_HASH_BITS_MASK_FIELD	7UL
#घोषणा NIC_CFG_RSS_HASH_BITS_SHIFT		16
#घोषणा NIC_CFG_RSS_BASE_CPU			(7UL << 19)
#घोषणा NIC_CFG_RSS_BASE_CPU_MASK_FIELD		7UL
#घोषणा NIC_CFG_RSS_BASE_CPU_SHIFT		19
#घोषणा NIC_CFG_RSS_ENABLE			(1UL << 22)
#घोषणा NIC_CFG_RSS_ENABLE_MASK_FIELD		1UL
#घोषणा NIC_CFG_RSS_ENABLE_SHIFT		22
#घोषणा NIC_CFG_TSO_IPID_SPLIT_EN		(1UL << 23)
#घोषणा NIC_CFG_TSO_IPID_SPLIT_EN_MASK_FIELD	1UL
#घोषणा NIC_CFG_TSO_IPID_SPLIT_EN_SHIFT		23
#घोषणा NIC_CFG_IG_VLAN_STRIP_EN		(1UL << 24)
#घोषणा NIC_CFG_IG_VLAN_STRIP_EN_MASK_FIELD	1UL
#घोषणा NIC_CFG_IG_VLAN_STRIP_EN_SHIFT		24

#घोषणा NIC_CFG_RSS_HASH_TYPE_UDP_IPV4		(1 << 0)
#घोषणा NIC_CFG_RSS_HASH_TYPE_IPV4		(1 << 1)
#घोषणा NIC_CFG_RSS_HASH_TYPE_TCP_IPV4		(1 << 2)
#घोषणा NIC_CFG_RSS_HASH_TYPE_IPV6		(1 << 3)
#घोषणा NIC_CFG_RSS_HASH_TYPE_TCP_IPV6		(1 << 4)
#घोषणा NIC_CFG_RSS_HASH_TYPE_IPV6_EX		(1 << 5)
#घोषणा NIC_CFG_RSS_HASH_TYPE_TCP_IPV6_EX	(1 << 6)
#घोषणा NIC_CFG_RSS_HASH_TYPE_UDP_IPV6		(1 << 7)

अटल अंतरभूत व्योम vnic_set_nic_cfg(u32 *nic_cfg,
	u8 rss_शेष_cpu, u8 rss_hash_type,
	u8 rss_hash_bits, u8 rss_base_cpu,
	u8 rss_enable, u8 tso_ipid_split_en,
	u8 ig_vlan_strip_en)
अणु
	*nic_cfg = (rss_शेष_cpu & NIC_CFG_RSS_DEFAULT_CPU_MASK_FIELD) |
		((rss_hash_type & NIC_CFG_RSS_HASH_TYPE_MASK_FIELD)
			<< NIC_CFG_RSS_HASH_TYPE_SHIFT) |
		((rss_hash_bits & NIC_CFG_RSS_HASH_BITS_MASK_FIELD)
			<< NIC_CFG_RSS_HASH_BITS_SHIFT) |
		((rss_base_cpu & NIC_CFG_RSS_BASE_CPU_MASK_FIELD)
			<< NIC_CFG_RSS_BASE_CPU_SHIFT) |
		((rss_enable & NIC_CFG_RSS_ENABLE_MASK_FIELD)
			<< NIC_CFG_RSS_ENABLE_SHIFT) |
		((tso_ipid_split_en & NIC_CFG_TSO_IPID_SPLIT_EN_MASK_FIELD)
			<< NIC_CFG_TSO_IPID_SPLIT_EN_SHIFT) |
		((ig_vlan_strip_en & NIC_CFG_IG_VLAN_STRIP_EN_MASK_FIELD)
			<< NIC_CFG_IG_VLAN_STRIP_EN_SHIFT);
पूर्ण

#पूर्ण_अगर /* _VNIC_NIC_H_ */
