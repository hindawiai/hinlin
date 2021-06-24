<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFT_REJECT_H_
#घोषणा _NFT_REJECT_H_

#समावेश <linux/types.h>
#समावेश <net/netlink.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <uapi/linux/netfilter/nf_tables.h>

काष्ठा nft_reject अणु
	क्रमागत nft_reject_types	type:8;
	u8			icmp_code;
पूर्ण;

बाह्य स्थिर काष्ठा nla_policy nft_reject_policy[];

पूर्णांक nft_reject_validate(स्थिर काष्ठा nft_ctx *ctx,
			स्थिर काष्ठा nft_expr *expr,
			स्थिर काष्ठा nft_data **data);

पूर्णांक nft_reject_init(स्थिर काष्ठा nft_ctx *ctx,
		    स्थिर काष्ठा nft_expr *expr,
		    स्थिर काष्ठा nlattr * स्थिर tb[]);

पूर्णांक nft_reject_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr);

पूर्णांक nft_reject_icmp_code(u8 code);
पूर्णांक nft_reject_icmpv6_code(u8 code);

#पूर्ण_अगर
