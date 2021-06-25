<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
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

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>
#समावेश "hns_roce_device.h"

अटल अंतरभूत u16 get_ah_udp_sport(स्थिर काष्ठा rdma_ah_attr *ah_attr)
अणु
	u32 fl = ah_attr->grh.flow_label;
	u16 sport;

	अगर (!fl)
		sport = get_अक्रमom_u32() %
			(IB_ROCE_UDP_ENCAP_VALID_PORT_MAX + 1 -
			 IB_ROCE_UDP_ENCAP_VALID_PORT_MIN) +
			IB_ROCE_UDP_ENCAP_VALID_PORT_MIN;
	अन्यथा
		sport = rdma_flow_label_to_udp_sport(fl);

	वापस sport;
पूर्ण

पूर्णांक hns_roce_create_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_init_attr *init_attr,
		       काष्ठा ib_udata *udata)
अणु
	काष्ठा rdma_ah_attr *ah_attr = init_attr->ah_attr;
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah_attr);
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibah->device);
	काष्ठा hns_roce_ah *ah = to_hr_ah(ibah);
	पूर्णांक ret = 0;

	अगर (hr_dev->pci_dev->revision <= PCI_REVISION_ID_HIP08 && udata)
		वापस -EOPNOTSUPP;

	ah->av.port = rdma_ah_get_port_num(ah_attr);
	ah->av.gid_index = grh->sgid_index;

	अगर (rdma_ah_get_अटल_rate(ah_attr))
		ah->av.stat_rate = IB_RATE_10_GBPS;

	ah->av.hop_limit = grh->hop_limit;
	ah->av.flowlabel = grh->flow_label;
	ah->av.udp_sport = get_ah_udp_sport(ah_attr);
	ah->av.sl = rdma_ah_get_sl(ah_attr);
	ah->av.tclass = get_tclass(grh);

	स_नकल(ah->av.dgid, grh->dgid.raw, HNS_ROCE_GID_SIZE);
	स_नकल(ah->av.mac, ah_attr->roce.dmac, ETH_ALEN);

	/* HIP08 needs to record vlan info in Address Vector */
	अगर (hr_dev->pci_dev->revision <= PCI_REVISION_ID_HIP08) अणु
		ret = rdma_पढ़ो_gid_l2_fields(ah_attr->grh.sgid_attr,
					      &ah->av.vlan_id, शून्य);
		अगर (ret)
			वापस ret;

		ah->av.vlan_en = ah->av.vlan_id < VLAN_N_VID;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hns_roce_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा hns_roce_ah *ah = to_hr_ah(ibah);

	स_रखो(ah_attr, 0, माप(*ah_attr));

	rdma_ah_set_sl(ah_attr, ah->av.sl);
	rdma_ah_set_port_num(ah_attr, ah->av.port);
	rdma_ah_set_अटल_rate(ah_attr, ah->av.stat_rate);
	rdma_ah_set_grh(ah_attr, शून्य, ah->av.flowlabel,
			ah->av.gid_index, ah->av.hop_limit, ah->av.tclass);
	rdma_ah_set_dgid_raw(ah_attr, ah->av.dgid);

	वापस 0;
पूर्ण
