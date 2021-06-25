<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match FRAG parameters. */

/* (C) 2001-2002 Andras Kis-Szabo <kisza@sch.bme.hu>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/types.h>
#समावेश <net/checksum.h>
#समावेश <net/ipv6.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter_ipv6/ip6t_frag.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: IPv6 fragment match");
MODULE_AUTHOR("Andras Kis-Szabo <kisza@sch.bme.hu>");

/* Returns 1 अगर the id is matched by the range, 0 otherwise */
अटल अंतरभूत bool
id_match(u_पूर्णांक32_t min, u_पूर्णांक32_t max, u_पूर्णांक32_t id, bool invert)
अणु
	bool r;
	pr_debug("id_match:%c 0x%x <= 0x%x <= 0x%x\n", invert ? '!' : ' ',
		 min, id, max);
	r = (id >= min && id <= max) ^ invert;
	pr_debug(" result %s\n", r ? "PASS" : "FAILED");
	वापस r;
पूर्ण

अटल bool
frag_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा frag_hdr _frag;
	स्थिर काष्ठा frag_hdr *fh;
	स्थिर काष्ठा ip6t_frag *fraginfo = par->matchinfo;
	अचिन्हित पूर्णांक ptr = 0;
	पूर्णांक err;

	err = ipv6_find_hdr(skb, &ptr, NEXTHDR_FRAGMENT, शून्य, शून्य);
	अगर (err < 0) अणु
		अगर (err != -ENOENT)
			par->hotdrop = true;
		वापस false;
	पूर्ण

	fh = skb_header_poपूर्णांकer(skb, ptr, माप(_frag), &_frag);
	अगर (fh == शून्य) अणु
		par->hotdrop = true;
		वापस false;
	पूर्ण

	pr_debug("INFO %04X ", fh->frag_off);
	pr_debug("OFFSET %04X ", ntohs(fh->frag_off) & ~0x7);
	pr_debug("RES %02X %04X", fh->reserved, ntohs(fh->frag_off) & 0x6);
	pr_debug("MF %04X ", fh->frag_off & htons(IP6_MF));
	pr_debug("ID %u %08X\n", ntohl(fh->identअगरication),
		 ntohl(fh->identअगरication));

	pr_debug("IPv6 FRAG id %02X ",
		 id_match(fraginfo->ids[0], fraginfo->ids[1],
			  ntohl(fh->identअगरication),
			  !!(fraginfo->invflags & IP6T_FRAG_INV_IDS)));
	pr_debug("res %02X %02X%04X %02X ",
		 fraginfo->flags & IP6T_FRAG_RES, fh->reserved,
		 ntohs(fh->frag_off) & 0x6,
		 !((fraginfo->flags & IP6T_FRAG_RES) &&
		   (fh->reserved || (ntohs(fh->frag_off) & 0x06))));
	pr_debug("first %02X %02X %02X ",
		 fraginfo->flags & IP6T_FRAG_FST,
		 ntohs(fh->frag_off) & ~0x7,
		 !((fraginfo->flags & IP6T_FRAG_FST) &&
		   (ntohs(fh->frag_off) & ~0x7)));
	pr_debug("mf %02X %02X %02X ",
		 fraginfo->flags & IP6T_FRAG_MF,
		 ntohs(fh->frag_off) & IP6_MF,
		 !((fraginfo->flags & IP6T_FRAG_MF) &&
		   !((ntohs(fh->frag_off) & IP6_MF))));
	pr_debug("last %02X %02X %02X\n",
		 fraginfo->flags & IP6T_FRAG_NMF,
		 ntohs(fh->frag_off) & IP6_MF,
		 !((fraginfo->flags & IP6T_FRAG_NMF) &&
		   (ntohs(fh->frag_off) & IP6_MF)));

	वापस id_match(fraginfo->ids[0], fraginfo->ids[1],
			 ntohl(fh->identअगरication),
			 !!(fraginfo->invflags & IP6T_FRAG_INV_IDS)) &&
		!((fraginfo->flags & IP6T_FRAG_RES) &&
		  (fh->reserved || (ntohs(fh->frag_off) & 0x6))) &&
		!((fraginfo->flags & IP6T_FRAG_FST) &&
		  (ntohs(fh->frag_off) & ~0x7)) &&
		!((fraginfo->flags & IP6T_FRAG_MF) &&
		  !(ntohs(fh->frag_off) & IP6_MF)) &&
		!((fraginfo->flags & IP6T_FRAG_NMF) &&
		  (ntohs(fh->frag_off) & IP6_MF));
पूर्ण

अटल पूर्णांक frag_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_frag *fraginfo = par->matchinfo;

	अगर (fraginfo->invflags & ~IP6T_FRAG_INV_MASK) अणु
		pr_debug("unknown flags %X\n", fraginfo->invflags);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_match frag_mt6_reg __पढ़ो_mostly = अणु
	.name		= "frag",
	.family		= NFPROTO_IPV6,
	.match		= frag_mt6,
	.matchsize	= माप(काष्ठा ip6t_frag),
	.checkentry	= frag_mt6_check,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init frag_mt6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&frag_mt6_reg);
पूर्ण

अटल व्योम __निकास frag_mt6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&frag_mt6_reg);
पूर्ण

module_init(frag_mt6_init);
module_निकास(frag_mt6_निकास);
