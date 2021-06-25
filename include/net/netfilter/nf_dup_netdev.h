<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_DUP_NETDEV_H_
#घोषणा _NF_DUP_NETDEV_H_

#समावेश <net/netfilter/nf_tables.h>

व्योम nf_dup_netdev_egress(स्थिर काष्ठा nft_pktinfo *pkt, पूर्णांक oअगर);
व्योम nf_fwd_netdev_egress(स्थिर काष्ठा nft_pktinfo *pkt, पूर्णांक oअगर);

काष्ठा nft_offload_ctx;
काष्ठा nft_flow_rule;

पूर्णांक nft_fwd_dup_netdev_offload(काष्ठा nft_offload_ctx *ctx,
			       काष्ठा nft_flow_rule *flow,
			       क्रमागत flow_action_id id, पूर्णांक oअगर);
#पूर्ण_अगर
