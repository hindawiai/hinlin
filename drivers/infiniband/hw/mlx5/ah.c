<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
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

#समावेश "mlx5_ib.h"

अटल __be16 mlx5_ah_get_udp_sport(स्थिर काष्ठा mlx5_ib_dev *dev,
				  स्थिर काष्ठा rdma_ah_attr *ah_attr)
अणु
	क्रमागत ib_gid_type gid_type = ah_attr->grh.sgid_attr->gid_type;
	__be16 sport;

	अगर ((gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) &&
	    (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) &&
	    (ah_attr->grh.flow_label & IB_GRH_FLOWLABEL_MASK))
		sport = cpu_to_be16(
			rdma_flow_label_to_udp_sport(ah_attr->grh.flow_label));
	अन्यथा
		sport = mlx5_get_roce_udp_sport_min(dev,
						    ah_attr->grh.sgid_attr);

	वापस sport;
पूर्ण

अटल व्योम create_ib_ah(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_ah *ah,
			 काष्ठा rdma_ah_init_attr *init_attr)
अणु
	काष्ठा rdma_ah_attr *ah_attr = init_attr->ah_attr;
	क्रमागत ib_gid_type gid_type;

	अगर (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) अणु
		स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah_attr);

		स_नकल(ah->av.rgid, &grh->dgid, 16);
		ah->av.grh_gid_fl = cpu_to_be32(grh->flow_label |
						(1 << 30) |
						grh->sgid_index << 20);
		ah->av.hop_limit = grh->hop_limit;
		ah->av.tclass = grh->traffic_class;
	पूर्ण

	ah->av.stat_rate_sl = (rdma_ah_get_अटल_rate(ah_attr) << 4);

	अगर (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE) अणु
		अगर (init_attr->xmit_slave)
			ah->xmit_port =
				mlx5_lag_get_slave_port(dev->mdev,
							init_attr->xmit_slave);
		gid_type = ah_attr->grh.sgid_attr->gid_type;

		स_नकल(ah->av.rmac, ah_attr->roce.dmac,
		       माप(ah_attr->roce.dmac));
		ah->av.udp_sport = mlx5_ah_get_udp_sport(dev, ah_attr);
		ah->av.stat_rate_sl |= (rdma_ah_get_sl(ah_attr) & 0x7) << 1;
		अगर (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP)
#घोषणा MLX5_ECN_ENABLED BIT(1)
			ah->av.tclass |= MLX5_ECN_ENABLED;
	पूर्ण अन्यथा अणु
		ah->av.rlid = cpu_to_be16(rdma_ah_get_dlid(ah_attr));
		ah->av.fl_mlid = rdma_ah_get_path_bits(ah_attr) & 0x7f;
		ah->av.stat_rate_sl |= (rdma_ah_get_sl(ah_attr) & 0xf);
	पूर्ण
पूर्ण

पूर्णांक mlx5_ib_create_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_init_attr *init_attr,
		      काष्ठा ib_udata *udata)

अणु
	काष्ठा rdma_ah_attr *ah_attr = init_attr->ah_attr;
	काष्ठा mlx5_ib_ah *ah = to_mah(ibah);
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibah->device);
	क्रमागत rdma_ah_attr_type ah_type = ah_attr->type;

	अगर ((ah_type == RDMA_AH_ATTR_TYPE_ROCE) &&
	    !(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
		वापस -EINVAL;

	अगर (ah_type == RDMA_AH_ATTR_TYPE_ROCE && udata) अणु
		पूर्णांक err;
		काष्ठा mlx5_ib_create_ah_resp resp = अणुपूर्ण;
		u32 min_resp_len =
			दुरत्वend(काष्ठा mlx5_ib_create_ah_resp, dmac);

		अगर (udata->outlen < min_resp_len)
			वापस -EINVAL;

		resp.response_length = min_resp_len;

		स_नकल(resp.dmac, ah_attr->roce.dmac, ETH_ALEN);
		err = ib_copy_to_udata(udata, &resp, resp.response_length);
		अगर (err)
			वापस err;
	पूर्ण

	create_ib_ah(dev, ah, init_attr);
	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा mlx5_ib_ah *ah = to_mah(ibah);
	u32 पंचांगp;

	स_रखो(ah_attr, 0, माप(*ah_attr));
	ah_attr->type = ibah->type;

	पंचांगp = be32_to_cpu(ah->av.grh_gid_fl);
	अगर (पंचांगp & (1 << 30)) अणु
		rdma_ah_set_grh(ah_attr, शून्य,
				पंचांगp & 0xfffff,
				(पंचांगp >> 20) & 0xff,
				ah->av.hop_limit,
				ah->av.tclass);
		rdma_ah_set_dgid_raw(ah_attr, ah->av.rgid);
	पूर्ण
	rdma_ah_set_dlid(ah_attr, be16_to_cpu(ah->av.rlid));
	rdma_ah_set_अटल_rate(ah_attr, ah->av.stat_rate_sl >> 4);
	rdma_ah_set_sl(ah_attr, ah->av.stat_rate_sl & 0xf);

	वापस 0;
पूर्ण
