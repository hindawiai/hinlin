<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_stp
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *	Stephen Hemminger <shemminger@osdl.org>
 *
 *  July, 2003
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_stp.h>

#घोषणा BPDU_TYPE_CONFIG 0

काष्ठा stp_header अणु
	u8 dsap;
	u8 ssap;
	u8 ctrl;
	u8 pid;
	u8 vers;
	u8 type;
पूर्ण;

काष्ठा stp_config_pdu अणु
	u8 flags;
	u8 root[8];
	u8 root_cost[4];
	u8 sender[8];
	u8 port[2];
	u8 msg_age[2];
	u8 max_age[2];
	u8 hello_समय[2];
	u8 क्रमward_delay[2];
पूर्ण;

#घोषणा NR16(p) (p[0] << 8 | p[1])
#घोषणा NR32(p) ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3])

अटल bool ebt_filter_config(स्थिर काष्ठा ebt_stp_info *info,
			      स्थिर काष्ठा stp_config_pdu *stpc)
अणु
	स्थिर काष्ठा ebt_stp_config_info *c;
	u16 v16;
	u32 v32;

	c = &info->config;
	अगर ((info->biपंचांगask & EBT_STP_FLAGS) &&
	    NF_INVF(info, EBT_STP_FLAGS, c->flags != stpc->flags))
		वापस false;
	अगर (info->biपंचांगask & EBT_STP_ROOTPRIO) अणु
		v16 = NR16(stpc->root);
		अगर (NF_INVF(info, EBT_STP_ROOTPRIO,
			    v16 < c->root_priol || v16 > c->root_priou))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_ROOTADDR) अणु
		अगर (NF_INVF(info, EBT_STP_ROOTADDR,
			    !ether_addr_equal_masked(&stpc->root[2],
						     c->root_addr,
						     c->root_addrmsk)))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_ROOTCOST) अणु
		v32 = NR32(stpc->root_cost);
		अगर (NF_INVF(info, EBT_STP_ROOTCOST,
			    v32 < c->root_costl || v32 > c->root_costu))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_SENDERPRIO) अणु
		v16 = NR16(stpc->sender);
		अगर (NF_INVF(info, EBT_STP_SENDERPRIO,
			    v16 < c->sender_priol || v16 > c->sender_priou))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_SENDERADDR) अणु
		अगर (NF_INVF(info, EBT_STP_SENDERADDR,
			    !ether_addr_equal_masked(&stpc->sender[2],
						     c->sender_addr,
						     c->sender_addrmsk)))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_PORT) अणु
		v16 = NR16(stpc->port);
		अगर (NF_INVF(info, EBT_STP_PORT,
			    v16 < c->portl || v16 > c->portu))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_MSGAGE) अणु
		v16 = NR16(stpc->msg_age);
		अगर (NF_INVF(info, EBT_STP_MSGAGE,
			    v16 < c->msg_agel || v16 > c->msg_ageu))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_MAXAGE) अणु
		v16 = NR16(stpc->max_age);
		अगर (NF_INVF(info, EBT_STP_MAXAGE,
			    v16 < c->max_agel || v16 > c->max_ageu))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_HELLOTIME) अणु
		v16 = NR16(stpc->hello_समय);
		अगर (NF_INVF(info, EBT_STP_HELLOTIME,
			    v16 < c->hello_समयl || v16 > c->hello_समयu))
			वापस false;
	पूर्ण
	अगर (info->biपंचांगask & EBT_STP_FWDD) अणु
		v16 = NR16(stpc->क्रमward_delay);
		अगर (NF_INVF(info, EBT_STP_FWDD,
			    v16 < c->क्रमward_delayl || v16 > c->क्रमward_delayu))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool
ebt_stp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_stp_info *info = par->matchinfo;
	स्थिर काष्ठा stp_header *sp;
	काष्ठा stp_header _stph;
	स्थिर u8 header[6] = अणु0x42, 0x42, 0x03, 0x00, 0x00, 0x00पूर्ण;

	sp = skb_header_poपूर्णांकer(skb, 0, माप(_stph), &_stph);
	अगर (sp == शून्य)
		वापस false;

	/* The stp code only considers these */
	अगर (स_भेद(sp, header, माप(header)))
		वापस false;

	अगर ((info->biपंचांगask & EBT_STP_TYPE) &&
	    NF_INVF(info, EBT_STP_TYPE, info->type != sp->type))
		वापस false;

	अगर (sp->type == BPDU_TYPE_CONFIG &&
	    info->biपंचांगask & EBT_STP_CONFIG_MASK) अणु
		स्थिर काष्ठा stp_config_pdu *st;
		काष्ठा stp_config_pdu _stpc;

		st = skb_header_poपूर्णांकer(skb, माप(_stph),
					माप(_stpc), &_stpc);
		अगर (st == शून्य)
			वापस false;
		वापस ebt_filter_config(info, st);
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक ebt_stp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ebt_stp_info *info = par->matchinfo;
	स्थिर काष्ठा ebt_entry *e = par->entryinfo;

	अगर (info->biपंचांगask & ~EBT_STP_MASK || info->invflags & ~EBT_STP_MASK ||
	    !(info->biपंचांगask & EBT_STP_MASK))
		वापस -EINVAL;
	/* Make sure the match only receives stp frames */
	अगर (!par->nft_compat &&
	    (!ether_addr_equal(e->desपंचांगac, eth_stp_addr) ||
	     !(e->biपंचांगask & EBT_DESTMAC) ||
	     !is_broadcast_ether_addr(e->desपंचांगsk)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा xt_match ebt_stp_mt_reg __पढ़ो_mostly = अणु
	.name		= "stp",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_stp_mt,
	.checkentry	= ebt_stp_mt_check,
	.matchsize	= माप(काष्ठा ebt_stp_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_stp_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_stp_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_stp_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_stp_mt_reg);
पूर्ण

module_init(ebt_stp_init);
module_निकास(ebt_stp_fini);
MODULE_DESCRIPTION("Ebtables: Spanning Tree Protocol packet match");
MODULE_LICENSE("GPL");
