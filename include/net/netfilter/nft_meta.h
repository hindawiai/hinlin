<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFT_META_H_
#घोषणा _NFT_META_H_

#समावेश <net/netfilter/nf_tables.h>

काष्ठा nft_meta अणु
	क्रमागत nft_meta_keys	key:8;
	जोड़ अणु
		u8		dreg;
		u8		sreg;
	पूर्ण;
पूर्ण;

बाह्य स्थिर काष्ठा nla_policy nft_meta_policy[];

पूर्णांक nft_meta_get_init(स्थिर काष्ठा nft_ctx *ctx,
		      स्थिर काष्ठा nft_expr *expr,
		      स्थिर काष्ठा nlattr * स्थिर tb[]);

पूर्णांक nft_meta_set_init(स्थिर काष्ठा nft_ctx *ctx,
		      स्थिर काष्ठा nft_expr *expr,
		      स्थिर काष्ठा nlattr * स्थिर tb[]);

पूर्णांक nft_meta_get_dump(काष्ठा sk_buff *skb,
		      स्थिर काष्ठा nft_expr *expr);

पूर्णांक nft_meta_set_dump(काष्ठा sk_buff *skb,
		      स्थिर काष्ठा nft_expr *expr);

व्योम nft_meta_get_eval(स्थिर काष्ठा nft_expr *expr,
		       काष्ठा nft_regs *regs,
		       स्थिर काष्ठा nft_pktinfo *pkt);

व्योम nft_meta_set_eval(स्थिर काष्ठा nft_expr *expr,
		       काष्ठा nft_regs *regs,
		       स्थिर काष्ठा nft_pktinfo *pkt);

व्योम nft_meta_set_destroy(स्थिर काष्ठा nft_ctx *ctx,
			  स्थिर काष्ठा nft_expr *expr);

पूर्णांक nft_meta_set_validate(स्थिर काष्ठा nft_ctx *ctx,
			  स्थिर काष्ठा nft_expr *expr,
			  स्थिर काष्ठा nft_data **data);

#पूर्ण_अगर
