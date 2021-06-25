<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/sctp/sctp.h>
#समावेश <linux/sctp.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_sctp.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kiran Kumar Immidi");
MODULE_DESCRIPTION("Xtables: SCTP protocol packet match");
MODULE_ALIAS("ipt_sctp");
MODULE_ALIAS("ip6t_sctp");

#घोषणा SCCHECK(cond, option, flag, invflag) (!((flag) & (option)) \
					      || (!!((invflag) & (option)) ^ (cond)))

अटल bool
match_flags(स्थिर काष्ठा xt_sctp_flag_info *flag_info,
	    स्थिर पूर्णांक flag_count,
	    u_पूर्णांक8_t chunktype,
	    u_पूर्णांक8_t chunkflags)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < flag_count; i++)
		अगर (flag_info[i].chunktype == chunktype)
			वापस (chunkflags & flag_info[i].flag_mask) == flag_info[i].flag;

	वापस true;
पूर्ण

अटल अंतरभूत bool
match_packet(स्थिर काष्ठा sk_buff *skb,
	     अचिन्हित पूर्णांक offset,
	     स्थिर काष्ठा xt_sctp_info *info,
	     bool *hotdrop)
अणु
	u_पूर्णांक32_t chunkmapcopy[256 / माप (u_पूर्णांक32_t)];
	स्थिर काष्ठा sctp_chunkhdr *sch;
	काष्ठा sctp_chunkhdr _sch;
	पूर्णांक chunk_match_type = info->chunk_match_type;
	स्थिर काष्ठा xt_sctp_flag_info *flag_info = info->flag_info;
	पूर्णांक flag_count = info->flag_count;

#अगर_घोषित DEBUG
	पूर्णांक i = 0;
#पूर्ण_अगर

	अगर (chunk_match_type == SCTP_CHUNK_MATCH_ALL)
		SCTP_CHUNKMAP_COPY(chunkmapcopy, info->chunkmap);

	करो अणु
		sch = skb_header_poपूर्णांकer(skb, offset, माप(_sch), &_sch);
		अगर (sch == शून्य || sch->length == 0) अणु
			pr_debug("Dropping invalid SCTP packet.\n");
			*hotdrop = true;
			वापस false;
		पूर्ण
#अगर_घोषित DEBUG
		pr_debug("Chunk num: %d\toffset: %d\ttype: %d\tlength: %d"
			 "\tflags: %x\n",
			 ++i, offset, sch->type, htons(sch->length),
			 sch->flags);
#पूर्ण_अगर
		offset += SCTP_PAD4(ntohs(sch->length));

		pr_debug("skb->len: %d\toffset: %d\n", skb->len, offset);

		अगर (SCTP_CHUNKMAP_IS_SET(info->chunkmap, sch->type)) अणु
			चयन (chunk_match_type) अणु
			हाल SCTP_CHUNK_MATCH_ANY:
				अगर (match_flags(flag_info, flag_count,
					sch->type, sch->flags)) अणु
					वापस true;
				पूर्ण
				अवरोध;

			हाल SCTP_CHUNK_MATCH_ALL:
				अगर (match_flags(flag_info, flag_count,
				    sch->type, sch->flags))
					SCTP_CHUNKMAP_CLEAR(chunkmapcopy, sch->type);
				अवरोध;

			हाल SCTP_CHUNK_MATCH_ONLY:
				अगर (!match_flags(flag_info, flag_count,
				    sch->type, sch->flags))
					वापस false;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (chunk_match_type) अणु
			हाल SCTP_CHUNK_MATCH_ONLY:
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (offset < skb->len);

	चयन (chunk_match_type) अणु
	हाल SCTP_CHUNK_MATCH_ALL:
		वापस SCTP_CHUNKMAP_IS_CLEAR(chunkmapcopy);
	हाल SCTP_CHUNK_MATCH_ANY:
		वापस false;
	हाल SCTP_CHUNK_MATCH_ONLY:
		वापस true;
	पूर्ण

	/* This will never be reached, but required to stop compiler whine */
	वापस false;
पूर्ण

अटल bool
sctp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_sctp_info *info = par->matchinfo;
	स्थिर काष्ठा sctphdr *sh;
	काष्ठा sctphdr _sh;

	अगर (par->fragoff != 0) अणु
		pr_debug("Dropping non-first fragment.. FIXME\n");
		वापस false;
	पूर्ण

	sh = skb_header_poपूर्णांकer(skb, par->thoff, माप(_sh), &_sh);
	अगर (sh == शून्य) अणु
		pr_debug("Dropping evil TCP offset=0 tinygram.\n");
		par->hotdrop = true;
		वापस false;
	पूर्ण
	pr_debug("spt: %d\tdpt: %d\n", ntohs(sh->source), ntohs(sh->dest));

	वापस  SCCHECK(ntohs(sh->source) >= info->spts[0]
			&& ntohs(sh->source) <= info->spts[1],
			XT_SCTP_SRC_PORTS, info->flags, info->invflags) &&
		SCCHECK(ntohs(sh->dest) >= info->dpts[0]
			&& ntohs(sh->dest) <= info->dpts[1],
			XT_SCTP_DEST_PORTS, info->flags, info->invflags) &&
		SCCHECK(match_packet(skb, par->thoff + माप(_sh),
				     info, &par->hotdrop),
			XT_SCTP_CHUNK_TYPES, info->flags, info->invflags);
पूर्ण

अटल पूर्णांक sctp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_sctp_info *info = par->matchinfo;

	अगर (info->flags & ~XT_SCTP_VALID_FLAGS)
		वापस -EINVAL;
	अगर (info->invflags & ~XT_SCTP_VALID_FLAGS)
		वापस -EINVAL;
	अगर (info->invflags & ~info->flags)
		वापस -EINVAL;
	अगर (!(info->flags & XT_SCTP_CHUNK_TYPES))
		वापस 0;
	अगर (info->chunk_match_type & (SCTP_CHUNK_MATCH_ALL |
	    SCTP_CHUNK_MATCH_ANY | SCTP_CHUNK_MATCH_ONLY))
		वापस 0;
	वापस -EINVAL;
पूर्ण

अटल काष्ठा xt_match sctp_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "sctp",
		.family		= NFPROTO_IPV4,
		.checkentry	= sctp_mt_check,
		.match		= sctp_mt,
		.matchsize	= माप(काष्ठा xt_sctp_info),
		.proto		= IPPROTO_SCTP,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "sctp",
		.family		= NFPROTO_IPV6,
		.checkentry	= sctp_mt_check,
		.match		= sctp_mt,
		.matchsize	= माप(काष्ठा xt_sctp_info),
		.proto		= IPPROTO_SCTP,
		.me		= THIS_MODULE
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sctp_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(sctp_mt_reg, ARRAY_SIZE(sctp_mt_reg));
पूर्ण

अटल व्योम __निकास sctp_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(sctp_mt_reg, ARRAY_SIZE(sctp_mt_reg));
पूर्ण

module_init(sctp_mt_init);
module_निकास(sctp_mt_निकास);
