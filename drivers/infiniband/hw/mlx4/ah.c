<शैली गुरु>
/*
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
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

#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>

#समावेश <linux/slab.h>
#समावेश <linux/inet.h>
#समावेश <linux/माला.स>
#समावेश <linux/mlx4/driver.h>

#समावेश "mlx4_ib.h"

अटल व्योम create_ib_ah(काष्ठा ib_ah *ib_ah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा mlx4_ib_ah *ah = to_mah(ib_ah);
	काष्ठा mlx4_dev *dev = to_mdev(ib_ah->device)->dev;

	ah->av.ib.port_pd = cpu_to_be32(to_mpd(ib_ah->pd)->pdn |
			    (rdma_ah_get_port_num(ah_attr) << 24));
	ah->av.ib.g_slid  = rdma_ah_get_path_bits(ah_attr);
	ah->av.ib.sl_tclass_flowlabel =
			cpu_to_be32(rdma_ah_get_sl(ah_attr) << 28);
	अगर (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) अणु
		स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah_attr);

		ah->av.ib.g_slid   |= 0x80;
		ah->av.ib.gid_index = grh->sgid_index;
		ah->av.ib.hop_limit = grh->hop_limit;
		ah->av.ib.sl_tclass_flowlabel |=
			cpu_to_be32((grh->traffic_class << 20) |
				    grh->flow_label);
		स_नकल(ah->av.ib.dgid, grh->dgid.raw, 16);
	पूर्ण

	ah->av.ib.dlid = cpu_to_be16(rdma_ah_get_dlid(ah_attr));
	अगर (rdma_ah_get_अटल_rate(ah_attr)) अणु
		u8 अटल_rate = rdma_ah_get_अटल_rate(ah_attr) +
					MLX4_STAT_RATE_OFFSET;

		जबतक (अटल_rate > IB_RATE_2_5_GBPS + MLX4_STAT_RATE_OFFSET &&
		       !(1 << अटल_rate & dev->caps.stat_rate_support))
			--अटल_rate;
		ah->av.ib.stat_rate = अटल_rate;
	पूर्ण
पूर्ण

अटल पूर्णांक create_iboe_ah(काष्ठा ib_ah *ib_ah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा mlx4_ib_dev *ibdev = to_mdev(ib_ah->device);
	काष्ठा mlx4_ib_ah *ah = to_mah(ib_ah);
	स्थिर काष्ठा ib_gid_attr *gid_attr;
	काष्ठा mlx4_dev *dev = ibdev->dev;
	पूर्णांक is_mcast = 0;
	काष्ठा in6_addr in6;
	u16 vlan_tag = 0xffff;
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah_attr);
	पूर्णांक ret;

	स_नकल(&in6, grh->dgid.raw, माप(in6));
	अगर (rdma_is_multicast_addr(&in6))
		is_mcast = 1;

	स_नकल(ah->av.eth.mac, ah_attr->roce.dmac, ETH_ALEN);
	eth_zero_addr(ah->av.eth.s_mac);

	/*
	 * If sgid_attr is शून्य we are being called by mlx4_ib_create_ah_slave
	 * and we are directly creating an AV क्रम a slave's gid_index.
	 */
	gid_attr = ah_attr->grh.sgid_attr;
	अगर (gid_attr) अणु
		ret = rdma_पढ़ो_gid_l2_fields(gid_attr, &vlan_tag,
					      &ah->av.eth.s_mac[0]);
		अगर (ret)
			वापस ret;

		ret = mlx4_ib_gid_index_to_real_index(ibdev, gid_attr);
		अगर (ret < 0)
			वापस ret;
		ah->av.eth.gid_index = ret;
	पूर्ण अन्यथा अणु
		/* mlx4_ib_create_ah_slave fills in the s_mac and the vlan */
		ah->av.eth.gid_index = ah_attr->grh.sgid_index;
	पूर्ण

	अगर (vlan_tag < 0x1000)
		vlan_tag |= (rdma_ah_get_sl(ah_attr) & 7) << 13;
	ah->av.eth.port_pd = cpu_to_be32(to_mpd(ib_ah->pd)->pdn |
					 (rdma_ah_get_port_num(ah_attr) << 24));
	ah->av.eth.vlan = cpu_to_be16(vlan_tag);
	ah->av.eth.hop_limit = grh->hop_limit;
	अगर (rdma_ah_get_अटल_rate(ah_attr)) अणु
		ah->av.eth.stat_rate = rdma_ah_get_अटल_rate(ah_attr) +
					MLX4_STAT_RATE_OFFSET;
		जबतक (ah->av.eth.stat_rate > IB_RATE_2_5_GBPS + MLX4_STAT_RATE_OFFSET &&
		       !(1 << ah->av.eth.stat_rate & dev->caps.stat_rate_support))
			--ah->av.eth.stat_rate;
	पूर्ण
	ah->av.eth.sl_tclass_flowlabel |=
			cpu_to_be32((grh->traffic_class << 20) |
				    grh->flow_label);
	/*
	 * HW requires multicast LID so we just choose one.
	 */
	अगर (is_mcast)
		ah->av.ib.dlid = cpu_to_be16(0xc000);

	स_नकल(ah->av.eth.dgid, grh->dgid.raw, 16);
	ah->av.eth.sl_tclass_flowlabel |= cpu_to_be32(rdma_ah_get_sl(ah_attr)
						      << 29);
	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_create_ah(काष्ठा ib_ah *ib_ah, काष्ठा rdma_ah_init_attr *init_attr,
		      काष्ठा ib_udata *udata)
अणु
	काष्ठा rdma_ah_attr *ah_attr = init_attr->ah_attr;

	अगर (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE) अणु
		अगर (!(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
			वापस -EINVAL;
		/*
		 * TBD: need to handle the हाल when we get
		 * called in an atomic context and there we
		 * might sleep.  We करोn't expect this
		 * currently since we're working with link
		 * local addresses which we can translate
		 * without going to sleep.
		 */
		वापस create_iboe_ah(ib_ah, ah_attr);
	पूर्ण

	create_ib_ah(ib_ah, ah_attr);
	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_create_ah_slave(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr,
			    पूर्णांक slave_sgid_index, u8 *s_mac, u16 vlan_tag)
अणु
	काष्ठा rdma_ah_attr slave_attr = *ah_attr;
	काष्ठा rdma_ah_init_attr init_attr = अणुपूर्ण;
	काष्ठा mlx4_ib_ah *mah = to_mah(ah);
	पूर्णांक ret;

	slave_attr.grh.sgid_attr = शून्य;
	slave_attr.grh.sgid_index = slave_sgid_index;
	init_attr.ah_attr = &slave_attr;
	ret = mlx4_ib_create_ah(ah, &init_attr, शून्य);
	अगर (ret)
		वापस ret;

	ah->type = ah_attr->type;

	/* get rid of क्रमce-loopback bit */
	mah->av.ib.port_pd &= cpu_to_be32(0x7FFFFFFF);

	अगर (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE)
		स_नकल(mah->av.eth.s_mac, s_mac, 6);

	अगर (vlan_tag < 0x1000)
		vlan_tag |= (rdma_ah_get_sl(ah_attr) & 7) << 13;
	mah->av.eth.vlan = cpu_to_be16(vlan_tag);

	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा mlx4_ib_ah *ah = to_mah(ibah);
	पूर्णांक port_num = be32_to_cpu(ah->av.ib.port_pd) >> 24;

	स_रखो(ah_attr, 0, माप *ah_attr);
	ah_attr->type = ibah->type;

	अगर (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE) अणु
		rdma_ah_set_dlid(ah_attr, 0);
		rdma_ah_set_sl(ah_attr,
			       be32_to_cpu(ah->av.eth.sl_tclass_flowlabel)
			       >> 29);
	पूर्ण अन्यथा अणु
		rdma_ah_set_dlid(ah_attr, be16_to_cpu(ah->av.ib.dlid));
		rdma_ah_set_sl(ah_attr,
			       be32_to_cpu(ah->av.ib.sl_tclass_flowlabel)
			       >> 28);
	पूर्ण

	rdma_ah_set_port_num(ah_attr, port_num);
	अगर (ah->av.ib.stat_rate)
		rdma_ah_set_अटल_rate(ah_attr,
					ah->av.ib.stat_rate -
					MLX4_STAT_RATE_OFFSET);
	rdma_ah_set_path_bits(ah_attr, ah->av.ib.g_slid & 0x7F);
	अगर (mlx4_ib_ah_grh_present(ah)) अणु
		u32 tc_fl = be32_to_cpu(ah->av.ib.sl_tclass_flowlabel);

		rdma_ah_set_grh(ah_attr, शून्य,
				tc_fl & 0xfffff, ah->av.ib.gid_index,
				ah->av.ib.hop_limit,
				tc_fl >> 20);
		rdma_ah_set_dgid_raw(ah_attr, ah->av.ib.dgid);
	पूर्ण

	वापस 0;
पूर्ण
