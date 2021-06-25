<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_IFE_H
#घोषणा __NET_TC_IFE_H

#समावेश <net/act_api.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>

काष्ठा module;

काष्ठा tcf_अगरe_params अणु
	u8 eth_dst[ETH_ALEN];
	u8 eth_src[ETH_ALEN];
	u16 eth_type;
	u16 flags;

	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा tcf_अगरe_info अणु
	काष्ठा tc_action common;
	काष्ठा tcf_अगरe_params __rcu *params;
	/* list of metaids allowed */
	काष्ठा list_head metalist;
पूर्ण;
#घोषणा to_अगरe(a) ((काष्ठा tcf_अगरe_info *)a)

काष्ठा tcf_meta_info अणु
	स्थिर काष्ठा tcf_meta_ops *ops;
	व्योम *metaval;
	u16 metaid;
	काष्ठा list_head metalist;
पूर्ण;

काष्ठा tcf_meta_ops अणु
	u16 metaid; /*Maपूर्णांकainer provided ID */
	u16 metatype; /*netlink attribute type (look at net/netlink.h) */
	स्थिर अक्षर *name;
	स्थिर अक्षर *synopsis;
	काष्ठा list_head list;
	पूर्णांक	(*check_presence)(काष्ठा sk_buff *, काष्ठा tcf_meta_info *);
	पूर्णांक	(*encode)(काष्ठा sk_buff *, व्योम *, काष्ठा tcf_meta_info *);
	पूर्णांक	(*decode)(काष्ठा sk_buff *, व्योम *, u16 len);
	पूर्णांक	(*get)(काष्ठा sk_buff *skb, काष्ठा tcf_meta_info *mi);
	पूर्णांक	(*alloc)(काष्ठा tcf_meta_info *, व्योम *, gfp_t);
	व्योम	(*release)(काष्ठा tcf_meta_info *);
	पूर्णांक	(*validate)(व्योम *val, पूर्णांक len);
	काष्ठा module	*owner;
पूर्ण;

#घोषणा MODULE_ALIAS_IFE_META(metan)   MODULE_ALIAS("ife-meta-" metan)

पूर्णांक अगरe_get_meta_u32(काष्ठा sk_buff *skb, काष्ठा tcf_meta_info *mi);
पूर्णांक अगरe_get_meta_u16(काष्ठा sk_buff *skb, काष्ठा tcf_meta_info *mi);
पूर्णांक अगरe_alloc_meta_u32(काष्ठा tcf_meta_info *mi, व्योम *metaval, gfp_t gfp);
पूर्णांक अगरe_alloc_meta_u16(काष्ठा tcf_meta_info *mi, व्योम *metaval, gfp_t gfp);
पूर्णांक अगरe_check_meta_u32(u32 metaval, काष्ठा tcf_meta_info *mi);
पूर्णांक अगरe_check_meta_u16(u16 metaval, काष्ठा tcf_meta_info *mi);
पूर्णांक अगरe_encode_meta_u32(u32 metaval, व्योम *skbdata, काष्ठा tcf_meta_info *mi);
पूर्णांक अगरe_validate_meta_u32(व्योम *val, पूर्णांक len);
पूर्णांक अगरe_validate_meta_u16(व्योम *val, पूर्णांक len);
पूर्णांक अगरe_encode_meta_u16(u16 metaval, व्योम *skbdata, काष्ठा tcf_meta_info *mi);
व्योम अगरe_release_meta_gen(काष्ठा tcf_meta_info *mi);
पूर्णांक रेजिस्टर_अगरe_op(काष्ठा tcf_meta_ops *mops);
पूर्णांक unरेजिस्टर_अगरe_op(काष्ठा tcf_meta_ops *mops);

#पूर्ण_अगर /* __NET_TC_IFE_H */
