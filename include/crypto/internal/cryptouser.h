<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/cryptouser.h>
#समावेश <net/netlink.h>

काष्ठा crypto_alg *crypto_alg_match(काष्ठा crypto_user_alg *p, पूर्णांक exact);

#अगर_घोषित CONFIG_CRYPTO_STATS
पूर्णांक crypto_reportstat(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *in_nlh, काष्ठा nlattr **attrs);
#अन्यथा
अटल अंतरभूत पूर्णांक crypto_reportstat(काष्ठा sk_buff *in_skb,
				    काष्ठा nlmsghdr *in_nlh,
				    काष्ठा nlattr **attrs)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर
