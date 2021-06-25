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

#अगर_अघोषित _ENIC_RES_H_
#घोषणा _ENIC_RES_H_

#समावेश "wq_enet_desc.h"
#समावेश "rq_enet_desc.h"
#समावेश "vnic_wq.h"
#समावेश "vnic_rq.h"

#घोषणा ENIC_MIN_WQ_DESCS		64
#घोषणा ENIC_MAX_WQ_DESCS		4096
#घोषणा ENIC_MIN_RQ_DESCS		64
#घोषणा ENIC_MAX_RQ_DESCS		4096

#घोषणा ENIC_MIN_MTU			ETH_MIN_MTU
#घोषणा ENIC_MAX_MTU			9000

#घोषणा ENIC_MULTICAST_PERFECT_FILTERS	32
#घोषणा ENIC_UNICAST_PERFECT_FILTERS	32

#घोषणा ENIC_NON_TSO_MAX_DESC		16

#घोषणा ENIC_SETTING(enic, f) ((enic->config.flags & VENETF_##f) ? 1 : 0)

अटल अंतरभूत व्योम enic_queue_wq_desc_ex(काष्ठा vnic_wq *wq,
	व्योम *os_buf, dma_addr_t dma_addr, अचिन्हित पूर्णांक len,
	अचिन्हित पूर्णांक mss_or_csum_offset, अचिन्हित पूर्णांक hdr_len,
	पूर्णांक vlan_tag_insert, अचिन्हित पूर्णांक vlan_tag,
	पूर्णांक offload_mode, पूर्णांक cq_entry, पूर्णांक sop, पूर्णांक eop, पूर्णांक loopback)
अणु
	काष्ठा wq_enet_desc *desc = vnic_wq_next_desc(wq);
	u8 desc_skip_cnt = 1;
	u8 compressed_send = 0;
	u64 wrid = 0;

	wq_enet_desc_enc(desc,
		(u64)dma_addr | VNIC_PADDR_TARGET,
		(u16)len,
		(u16)mss_or_csum_offset,
		(u16)hdr_len, (u8)offload_mode,
		(u8)eop, (u8)cq_entry,
		0, /* fcoe_encap */
		(u8)vlan_tag_insert,
		(u16)vlan_tag,
		(u8)loopback);

	vnic_wq_post(wq, os_buf, dma_addr, len, sop, eop, desc_skip_cnt,
			(u8)cq_entry, compressed_send, wrid);
पूर्ण

अटल अंतरभूत व्योम enic_queue_wq_desc_cont(काष्ठा vnic_wq *wq,
	व्योम *os_buf, dma_addr_t dma_addr, अचिन्हित पूर्णांक len,
	पूर्णांक eop, पूर्णांक loopback)
अणु
	enic_queue_wq_desc_ex(wq, os_buf, dma_addr, len,
		0, 0, 0, 0, 0,
		eop, 0 /* !SOP */, eop, loopback);
पूर्ण

अटल अंतरभूत व्योम enic_queue_wq_desc(काष्ठा vnic_wq *wq, व्योम *os_buf,
	dma_addr_t dma_addr, अचिन्हित पूर्णांक len, पूर्णांक vlan_tag_insert,
	अचिन्हित पूर्णांक vlan_tag, पूर्णांक eop, पूर्णांक loopback)
अणु
	enic_queue_wq_desc_ex(wq, os_buf, dma_addr, len,
		0, 0, vlan_tag_insert, vlan_tag,
		WQ_ENET_OFFLOAD_MODE_CSUM,
		eop, 1 /* SOP */, eop, loopback);
पूर्ण

अटल अंतरभूत व्योम enic_queue_wq_desc_csum(काष्ठा vnic_wq *wq,
	व्योम *os_buf, dma_addr_t dma_addr, अचिन्हित पूर्णांक len,
	पूर्णांक ip_csum, पूर्णांक tcpudp_csum, पूर्णांक vlan_tag_insert,
	अचिन्हित पूर्णांक vlan_tag, पूर्णांक eop, पूर्णांक loopback)
अणु
	enic_queue_wq_desc_ex(wq, os_buf, dma_addr, len,
		(ip_csum ? 1 : 0) + (tcpudp_csum ? 2 : 0),
		0, vlan_tag_insert, vlan_tag,
		WQ_ENET_OFFLOAD_MODE_CSUM,
		eop, 1 /* SOP */, eop, loopback);
पूर्ण

अटल अंतरभूत व्योम enic_queue_wq_desc_csum_l4(काष्ठा vnic_wq *wq,
	व्योम *os_buf, dma_addr_t dma_addr, अचिन्हित पूर्णांक len,
	अचिन्हित पूर्णांक csum_offset, अचिन्हित पूर्णांक hdr_len,
	पूर्णांक vlan_tag_insert, अचिन्हित पूर्णांक vlan_tag, पूर्णांक eop, पूर्णांक loopback)
अणु
	enic_queue_wq_desc_ex(wq, os_buf, dma_addr, len,
		csum_offset, hdr_len, vlan_tag_insert, vlan_tag,
		WQ_ENET_OFFLOAD_MODE_CSUM_L4,
		eop, 1 /* SOP */, eop, loopback);
पूर्ण

अटल अंतरभूत व्योम enic_queue_wq_desc_tso(काष्ठा vnic_wq *wq,
	व्योम *os_buf, dma_addr_t dma_addr, अचिन्हित पूर्णांक len,
	अचिन्हित पूर्णांक mss, अचिन्हित पूर्णांक hdr_len, पूर्णांक vlan_tag_insert,
	अचिन्हित पूर्णांक vlan_tag, पूर्णांक eop, पूर्णांक loopback)
अणु
	enic_queue_wq_desc_ex(wq, os_buf, dma_addr, len,
		mss, hdr_len, vlan_tag_insert, vlan_tag,
		WQ_ENET_OFFLOAD_MODE_TSO,
		eop, 1 /* SOP */, eop, loopback);
पूर्ण

अटल अंतरभूत व्योम enic_queue_rq_desc(काष्ठा vnic_rq *rq,
	व्योम *os_buf, अचिन्हित पूर्णांक os_buf_index,
	dma_addr_t dma_addr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rq_enet_desc *desc = vnic_rq_next_desc(rq);
	u64 wrid = 0;
	u8 type = os_buf_index ?
		RQ_ENET_TYPE_NOT_SOP : RQ_ENET_TYPE_ONLY_SOP;

	rq_enet_desc_enc(desc,
		(u64)dma_addr | VNIC_PADDR_TARGET,
		type, (u16)len);

	vnic_rq_post(rq, os_buf, os_buf_index, dma_addr, len, wrid);
पूर्ण

काष्ठा enic;

पूर्णांक enic_get_vnic_config(काष्ठा enic *);
पूर्णांक enic_add_vlan(काष्ठा enic *enic, u16 vlanid);
पूर्णांक enic_del_vlan(काष्ठा enic *enic, u16 vlanid);
पूर्णांक enic_set_nic_cfg(काष्ठा enic *enic, u8 rss_शेष_cpu, u8 rss_hash_type,
	u8 rss_hash_bits, u8 rss_base_cpu, u8 rss_enable, u8 tso_ipid_split_en,
	u8 ig_vlan_strip_en);
पूर्णांक enic_set_rss_key(काष्ठा enic *enic, dma_addr_t key_pa, u64 len);
पूर्णांक enic_set_rss_cpu(काष्ठा enic *enic, dma_addr_t cpu_pa, u64 len);
व्योम enic_get_res_counts(काष्ठा enic *enic);
व्योम enic_init_vnic_resources(काष्ठा enic *enic);
पूर्णांक enic_alloc_vnic_resources(काष्ठा enic *);
व्योम enic_मुक्त_vnic_resources(काष्ठा enic *);

#पूर्ण_अगर /* _ENIC_RES_H_ */
