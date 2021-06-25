<शैली गुरु>
#अगर_अघोषित _NET_NF_TABLES_OFFLOAD_H
#घोषणा _NET_NF_TABLES_OFFLOAD_H

#समावेश <net/flow_offload.h>
#समावेश <net/netfilter/nf_tables.h>

क्रमागत nft_offload_reg_flags अणु
	NFT_OFFLOAD_F_NETWORK2HOST	= (1 << 0),
पूर्ण;

काष्ठा nft_offload_reg अणु
	u32		key;
	u32		len;
	u32		base_offset;
	u32		offset;
	u32		flags;
	काष्ठा nft_data data;
	काष्ठा nft_data	mask;
पूर्ण;

क्रमागत nft_offload_dep_type अणु
	NFT_OFFLOAD_DEP_UNSPEC	= 0,
	NFT_OFFLOAD_DEP_NETWORK,
	NFT_OFFLOAD_DEP_TRANSPORT,
पूर्ण;

काष्ठा nft_offload_ctx अणु
	काष्ठा अणु
		क्रमागत nft_offload_dep_type	type;
		__be16				l3num;
		u8				protonum;
	पूर्ण dep;
	अचिन्हित पूर्णांक				num_actions;
	काष्ठा net				*net;
	काष्ठा nft_offload_reg			regs[NFT_REG32_15 + 1];
पूर्ण;

व्योम nft_offload_set_dependency(काष्ठा nft_offload_ctx *ctx,
				क्रमागत nft_offload_dep_type type);
व्योम nft_offload_update_dependency(काष्ठा nft_offload_ctx *ctx,
				   स्थिर व्योम *data, u32 len);

काष्ठा nft_flow_key अणु
	काष्ठा flow_dissector_key_basic			basic;
	काष्ठा flow_dissector_key_control		control;
	जोड़ अणु
		काष्ठा flow_dissector_key_ipv4_addrs	ipv4;
		काष्ठा flow_dissector_key_ipv6_addrs	ipv6;
	पूर्ण;
	काष्ठा flow_dissector_key_ports			tp;
	काष्ठा flow_dissector_key_ip			ip;
	काष्ठा flow_dissector_key_vlan			vlan;
	काष्ठा flow_dissector_key_vlan			cvlan;
	काष्ठा flow_dissector_key_eth_addrs		eth_addrs;
	काष्ठा flow_dissector_key_meta			meta;
पूर्ण __aligned(BITS_PER_LONG / 8); /* Ensure that we can करो comparisons as दीर्घs. */

काष्ठा nft_flow_match अणु
	काष्ठा flow_dissector	dissector;
	काष्ठा nft_flow_key	key;
	काष्ठा nft_flow_key	mask;
पूर्ण;

काष्ठा nft_flow_rule अणु
	__be16			proto;
	काष्ठा nft_flow_match	match;
	काष्ठा flow_rule	*rule;
पूर्ण;

#घोषणा NFT_OFFLOAD_F_ACTION	(1 << 0)

व्योम nft_flow_rule_set_addr_type(काष्ठा nft_flow_rule *flow,
				 क्रमागत flow_dissector_key_id addr_type);

काष्ठा nft_rule;
काष्ठा nft_flow_rule *nft_flow_rule_create(काष्ठा net *net, स्थिर काष्ठा nft_rule *rule);
पूर्णांक nft_flow_rule_stats(स्थिर काष्ठा nft_chain *chain, स्थिर काष्ठा nft_rule *rule);
व्योम nft_flow_rule_destroy(काष्ठा nft_flow_rule *flow);
पूर्णांक nft_flow_rule_offload_commit(काष्ठा net *net);

#घोषणा NFT_OFFLOAD_MATCH_FLAGS(__key, __base, __field, __len, __reg, __flags)	\
	(__reg)->base_offset	=					\
		दुरत्व(काष्ठा nft_flow_key, __base);			\
	(__reg)->offset		=					\
		दुरत्व(काष्ठा nft_flow_key, __base.__field);		\
	(__reg)->len		= __len;				\
	(__reg)->key		= __key;				\
	(__reg)->flags		= __flags;

#घोषणा NFT_OFFLOAD_MATCH(__key, __base, __field, __len, __reg)		\
	NFT_OFFLOAD_MATCH_FLAGS(__key, __base, __field, __len, __reg, 0)

#घोषणा NFT_OFFLOAD_MATCH_EXACT(__key, __base, __field, __len, __reg)	\
	NFT_OFFLOAD_MATCH(__key, __base, __field, __len, __reg)		\
	स_रखो(&(__reg)->mask, 0xff, (__reg)->len);

पूर्णांक nft_chain_offload_priority(काष्ठा nft_base_chain *basechain);

पूर्णांक nft_offload_init(व्योम);
व्योम nft_offload_निकास(व्योम);

#पूर्ण_अगर
