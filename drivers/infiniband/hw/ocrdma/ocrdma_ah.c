<शैली गुरु>
/* This file is part of the Emulex RoCE Device Driver क्रम
 * RoCE (RDMA over Converged Ethernet) adapters.
 * Copyright (C) 2012-2015 Emulex. All rights reserved.
 * EMULEX and SLI are trademarks of Emulex.
 * www.emulex.com
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the मुख्य
 * directory of this source tree, or the BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#समावेश <net/neighbour.h>
#समावेश <net/netevent.h>

#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_cache.h>

#समावेश "ocrdma.h"
#समावेश "ocrdma_verbs.h"
#समावेश "ocrdma_ah.h"
#समावेश "ocrdma_hw.h"
#समावेश "ocrdma_stats.h"

#घोषणा OCRDMA_VID_PCP_SHIFT	0xD

अटल u16 ocrdma_hdr_type_to_proto_num(पूर्णांक devid, u8 hdr_type)
अणु
	चयन (hdr_type) अणु
	हाल OCRDMA_L3_TYPE_IB_GRH:
		वापस (u16)ETH_P_IBOE;
	हाल OCRDMA_L3_TYPE_IPV4:
		वापस (u16)0x0800;
	हाल OCRDMA_L3_TYPE_IPV6:
		वापस (u16)0x86dd;
	शेष:
		pr_err("ocrdma%d: Invalid network header\n", devid);
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक set_av_attr(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_ah *ah,
			काष्ठा rdma_ah_attr *attr, स्थिर जोड़ ib_gid *sgid,
			पूर्णांक pdid, bool *isvlan, u16 vlan_tag)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_eth_vlan eth;
	काष्ठा ocrdma_grh grh;
	पूर्णांक eth_sz;
	u16 proto_num = 0;
	u8 nxthdr = 0x11;
	काष्ठा iphdr ipv4;
	स्थिर काष्ठा ib_global_route *ib_grh;
	जोड़ अणु
		काष्ठा sockaddr_in  _sockaddr_in;
		काष्ठा sockaddr_in6 _sockaddr_in6;
	पूर्ण sgid_addr, dgid_addr;

	स_रखो(&eth, 0, माप(eth));
	स_रखो(&grh, 0, माप(grh));

	/* Protocol Number */
	proto_num = ocrdma_hdr_type_to_proto_num(dev->id, ah->hdr_type);
	अगर (!proto_num)
		वापस -EINVAL;
	nxthdr = (proto_num == ETH_P_IBOE) ? 0x1b : 0x11;
	/* VLAN */
	अगर (!vlan_tag || (vlan_tag > 0xFFF))
		vlan_tag = dev->pvid;
	अगर (vlan_tag || dev->pfc_state) अणु
		अगर (!vlan_tag) अणु
			pr_err("ocrdma%d:Using VLAN with PFC is recommended\n",
				dev->id);
			pr_err("ocrdma%d:Using VLAN 0 for this connection\n",
				dev->id);
		पूर्ण
		eth.eth_type = cpu_to_be16(0x8100);
		eth.roce_eth_type = cpu_to_be16(proto_num);
		vlan_tag |= (dev->sl & 0x07) << OCRDMA_VID_PCP_SHIFT;
		eth.vlan_tag = cpu_to_be16(vlan_tag);
		eth_sz = माप(काष्ठा ocrdma_eth_vlan);
		*isvlan = true;
	पूर्ण अन्यथा अणु
		eth.eth_type = cpu_to_be16(proto_num);
		eth_sz = माप(काष्ठा ocrdma_eth_basic);
	पूर्ण
	/* MAC */
	स_नकल(&eth.smac[0], &dev->nic_info.mac_addr[0], ETH_ALEN);
	status = ocrdma_resolve_dmac(dev, attr, &eth.dmac[0]);
	अगर (status)
		वापस status;
	ib_grh = rdma_ah_पढ़ो_grh(attr);
	ah->sgid_index = ib_grh->sgid_index;
	/* Eth HDR */
	स_नकल(&ah->av->eth_hdr, &eth, eth_sz);
	अगर (ah->hdr_type == RDMA_NETWORK_IPV4) अणु
		*((__be16 *)&ipv4) = htons((4 << 12) | (5 << 8) |
					   ib_grh->traffic_class);
		ipv4.id = cpu_to_be16(pdid);
		ipv4.frag_off = htons(IP_DF);
		ipv4.tot_len = htons(0);
		ipv4.ttl = ib_grh->hop_limit;
		ipv4.protocol = nxthdr;
		rdma_gid2ip((काष्ठा sockaddr *)&sgid_addr, sgid);
		ipv4.saddr = sgid_addr._sockaddr_in.sin_addr.s_addr;
		rdma_gid2ip((काष्ठा sockaddr*)&dgid_addr, &ib_grh->dgid);
		ipv4.daddr = dgid_addr._sockaddr_in.sin_addr.s_addr;
		स_नकल((u8 *)ah->av + eth_sz, &ipv4, माप(काष्ठा iphdr));
	पूर्ण अन्यथा अणु
		स_नकल(&grh.sgid[0], sgid->raw, माप(जोड़ ib_gid));
		grh.tclass_flow = cpu_to_be32((6 << 28) |
					      (ib_grh->traffic_class << 24) |
					      ib_grh->flow_label);
		स_नकल(&grh.dgid[0], ib_grh->dgid.raw,
		       माप(ib_grh->dgid.raw));
		grh.pdid_hoplimit = cpu_to_be32((pdid << 16) |
						(nxthdr << 8) |
						ib_grh->hop_limit);
		स_नकल((u8 *)ah->av + eth_sz, &grh, माप(काष्ठा ocrdma_grh));
	पूर्ण
	अगर (*isvlan)
		ah->av->valid |= OCRDMA_AV_VLAN_VALID;
	ah->av->valid = cpu_to_le32(ah->av->valid);
	वापस status;
पूर्ण

पूर्णांक ocrdma_create_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_init_attr *init_attr,
		     काष्ठा ib_udata *udata)
अणु
	u32 *ahid_addr;
	पूर्णांक status;
	काष्ठा ocrdma_ah *ah = get_ocrdma_ah(ibah);
	bool isvlan = false;
	u16 vlan_tag = 0xffff;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	काष्ठा ocrdma_pd *pd = get_ocrdma_pd(ibah->pd);
	काष्ठा rdma_ah_attr *attr = init_attr->ah_attr;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibah->device);

	अगर ((attr->type != RDMA_AH_ATTR_TYPE_ROCE) ||
	    !(rdma_ah_get_ah_flags(attr) & IB_AH_GRH))
		वापस -EINVAL;

	अगर (atomic_cmpxchg(&dev->update_sl, 1, 0))
		ocrdma_init_service_level(dev);

	sgid_attr = attr->grh.sgid_attr;
	status = rdma_पढ़ो_gid_l2_fields(sgid_attr, &vlan_tag, शून्य);
	अगर (status)
		वापस status;

	status = ocrdma_alloc_av(dev, ah);
	अगर (status)
		जाओ av_err;

	/* Get network header type क्रम this GID */
	ah->hdr_type = rdma_gid_attr_network_type(sgid_attr);

	status = set_av_attr(dev, ah, attr, &sgid_attr->gid, pd->id,
			     &isvlan, vlan_tag);
	अगर (status)
		जाओ av_conf_err;

	/* अगर pd is क्रम the user process, pass the ah_id to user space */
	अगर ((pd->uctx) && (pd->uctx->ah_tbl.va)) अणु
		ahid_addr = pd->uctx->ah_tbl.va + rdma_ah_get_dlid(attr);
		*ahid_addr = 0;
		*ahid_addr |= ah->id & OCRDMA_AH_ID_MASK;
		अगर (ocrdma_is_udp_encap_supported(dev)) अणु
			*ahid_addr |= ((u32)ah->hdr_type &
				       OCRDMA_AH_L3_TYPE_MASK) <<
				       OCRDMA_AH_L3_TYPE_SHIFT;
		पूर्ण
		अगर (isvlan)
			*ahid_addr |= (OCRDMA_AH_VLAN_VALID_MASK <<
				       OCRDMA_AH_VLAN_VALID_SHIFT);
	पूर्ण

	वापस 0;

av_conf_err:
	ocrdma_मुक्त_av(dev, ah);
av_err:
	वापस status;
पूर्ण

पूर्णांक ocrdma_destroy_ah(काष्ठा ib_ah *ibah, u32 flags)
अणु
	काष्ठा ocrdma_ah *ah = get_ocrdma_ah(ibah);
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(ibah->device);

	ocrdma_मुक्त_av(dev, ah);
	वापस 0;
पूर्ण

पूर्णांक ocrdma_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *attr)
अणु
	काष्ठा ocrdma_ah *ah = get_ocrdma_ah(ibah);
	काष्ठा ocrdma_av *av = ah->av;
	काष्ठा ocrdma_grh *grh;

	attr->type = ibah->type;
	अगर (ah->av->valid & OCRDMA_AV_VALID) अणु
		grh = (काष्ठा ocrdma_grh *)((u8 *)ah->av +
				माप(काष्ठा ocrdma_eth_vlan));
		rdma_ah_set_sl(attr, be16_to_cpu(av->eth_hdr.vlan_tag) >> 13);
	पूर्ण अन्यथा अणु
		grh = (काष्ठा ocrdma_grh *)((u8 *)ah->av +
					माप(काष्ठा ocrdma_eth_basic));
		rdma_ah_set_sl(attr, 0);
	पूर्ण
	rdma_ah_set_grh(attr, शून्य,
			be32_to_cpu(grh->tclass_flow) & 0xffffffff,
			ah->sgid_index,
			be32_to_cpu(grh->pdid_hoplimit) & 0xff,
			be32_to_cpu(grh->tclass_flow) >> 24);
	rdma_ah_set_dgid_raw(attr, &grh->dgid[0]);
	वापस 0;
पूर्ण

पूर्णांक ocrdma_process_mad(काष्ठा ib_device *ibdev, पूर्णांक process_mad_flags,
		       u32 port_num, स्थिर काष्ठा ib_wc *in_wc,
		       स्थिर काष्ठा ib_grh *in_grh, स्थिर काष्ठा ib_mad *in,
		       काष्ठा ib_mad *out, माप_प्रकार *out_mad_size,
		       u16 *out_mad_pkey_index)
अणु
	पूर्णांक status = IB_MAD_RESULT_SUCCESS;
	काष्ठा ocrdma_dev *dev;

	अगर (in->mad_hdr.mgmt_class == IB_MGMT_CLASS_PERF_MGMT) अणु
		dev = get_ocrdma_dev(ibdev);
		ocrdma_pma_counters(dev, out);
		status |= IB_MAD_RESULT_REPLY;
	पूर्ण

	वापस status;
पूर्ण
