<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश "rxe.h"
#समावेश "rxe_loc.h"

व्योम rxe_init_av(काष्ठा rdma_ah_attr *attr, काष्ठा rxe_av *av)
अणु
	rxe_av_from_attr(rdma_ah_get_port_num(attr), av, attr);
	rxe_av_fill_ip_info(av, attr);
	स_नकल(av->dmac, attr->roce.dmac, ETH_ALEN);
पूर्ण

पूर्णांक rxe_av_chk_attr(काष्ठा rxe_dev *rxe, काष्ठा rdma_ah_attr *attr)
अणु
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(attr);
	काष्ठा rxe_port *port;
	पूर्णांक type;

	port = &rxe->port;

	अगर (rdma_ah_get_ah_flags(attr) & IB_AH_GRH) अणु
		अगर (grh->sgid_index > port->attr.gid_tbl_len) अणु
			pr_warn("invalid sgid index = %d\n",
					grh->sgid_index);
			वापस -EINVAL;
		पूर्ण

		type = rdma_gid_attr_network_type(grh->sgid_attr);
		अगर (type < RDMA_NETWORK_IPV4 ||
		    type > RDMA_NETWORK_IPV6) अणु
			pr_warn("invalid network type for rdma_rxe = %d\n",
					type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम rxe_av_from_attr(u8 port_num, काष्ठा rxe_av *av,
		     काष्ठा rdma_ah_attr *attr)
अणु
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(attr);

	स_रखो(av, 0, माप(*av));
	स_नकल(av->grh.dgid.raw, grh->dgid.raw, माप(grh->dgid.raw));
	av->grh.flow_label = grh->flow_label;
	av->grh.sgid_index = grh->sgid_index;
	av->grh.hop_limit = grh->hop_limit;
	av->grh.traffic_class = grh->traffic_class;
	av->port_num = port_num;
पूर्ण

व्योम rxe_av_to_attr(काष्ठा rxe_av *av, काष्ठा rdma_ah_attr *attr)
अणु
	काष्ठा ib_global_route *grh = rdma_ah_retrieve_grh(attr);

	attr->type = RDMA_AH_ATTR_TYPE_ROCE;

	स_नकल(grh->dgid.raw, av->grh.dgid.raw, माप(av->grh.dgid.raw));
	grh->flow_label = av->grh.flow_label;
	grh->sgid_index = av->grh.sgid_index;
	grh->hop_limit = av->grh.hop_limit;
	grh->traffic_class = av->grh.traffic_class;

	rdma_ah_set_ah_flags(attr, IB_AH_GRH);
	rdma_ah_set_port_num(attr, av->port_num);
पूर्ण

व्योम rxe_av_fill_ip_info(काष्ठा rxe_av *av, काष्ठा rdma_ah_attr *attr)
अणु
	स्थिर काष्ठा ib_gid_attr *sgid_attr = attr->grh.sgid_attr;
	पूर्णांक ibtype;
	पूर्णांक type;

	rdma_gid2ip((काष्ठा sockaddr *)&av->sgid_addr, &sgid_attr->gid);
	rdma_gid2ip((काष्ठा sockaddr *)&av->dgid_addr,
		    &rdma_ah_पढ़ो_grh(attr)->dgid);

	ibtype = rdma_gid_attr_network_type(sgid_attr);

	चयन (ibtype) अणु
	हाल RDMA_NETWORK_IPV4:
		type = RXE_NETWORK_TYPE_IPV4;
		अवरोध;
	हाल RDMA_NETWORK_IPV6:
		type = RXE_NETWORK_TYPE_IPV6;
		अवरोध;
	शेष:
		/* not reached - checked in rxe_av_chk_attr */
		type = 0;
		अवरोध;
	पूर्ण

	av->network_type = type;
पूर्ण

काष्ठा rxe_av *rxe_get_av(काष्ठा rxe_pkt_info *pkt)
अणु
	अगर (!pkt || !pkt->qp)
		वापस शून्य;

	अगर (qp_type(pkt->qp) == IB_QPT_RC || qp_type(pkt->qp) == IB_QPT_UC)
		वापस &pkt->qp->pri_av;

	वापस (pkt->wqe) ? &pkt->wqe->av : शून्य;
पूर्ण
