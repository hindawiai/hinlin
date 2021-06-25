<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFT_FIB_H_
#घोषणा _NFT_FIB_H_

#समावेश <net/netfilter/nf_tables.h>

काष्ठा nft_fib अणु
	u8			dreg;
	u8			result;
	u32			flags;
पूर्ण;

बाह्य स्थिर काष्ठा nla_policy nft_fib_policy[];

अटल अंतरभूत bool
nft_fib_is_loopback(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *in)
अणु
	वापस skb->pkt_type == PACKET_LOOPBACK || in->flags & IFF_LOOPBACK;
पूर्ण

पूर्णांक nft_fib_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr);
पूर्णांक nft_fib_init(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
		 स्थिर काष्ठा nlattr * स्थिर tb[]);
पूर्णांक nft_fib_validate(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
		     स्थिर काष्ठा nft_data **data);


व्योम nft_fib4_eval_type(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
			स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_fib4_eval(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
		   स्थिर काष्ठा nft_pktinfo *pkt);

व्योम nft_fib6_eval_type(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
			स्थिर काष्ठा nft_pktinfo *pkt);
व्योम nft_fib6_eval(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
		   स्थिर काष्ठा nft_pktinfo *pkt);

व्योम nft_fib_store_result(व्योम *reg, स्थिर काष्ठा nft_fib *priv,
			  स्थिर काष्ठा net_device *dev);
#पूर्ण_अगर
