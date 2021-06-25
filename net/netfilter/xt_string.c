<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* String matching match क्रम iptables
 *
 * (C) 2005 Pablo Neira Ayuso <pablo@eurodev.net>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_माला.स>
#समावेश <linux/textsearch.h>

MODULE_AUTHOR("Pablo Neira Ayuso <pablo@eurodev.net>");
MODULE_DESCRIPTION("Xtables: string-based matching");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_string");
MODULE_ALIAS("ip6t_string");
MODULE_ALIAS("ebt_string");

अटल bool
string_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_string_info *conf = par->matchinfo;
	bool invert;

	invert = conf->u.v1.flags & XT_STRING_FLAG_INVERT;

	वापस (skb_find_text((काष्ठा sk_buff *)skb, conf->from_offset,
			     conf->to_offset, conf->config)
			     != अच_पूर्णांक_उच्च) ^ invert;
पूर्ण

#घोषणा STRING_TEXT_PRIV(m) ((काष्ठा xt_string_info *)(m))

अटल पूर्णांक string_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_string_info *conf = par->matchinfo;
	काष्ठा ts_config *ts_conf;
	पूर्णांक flags = TS_AUTOLOAD;

	/* Damn, can't handle this हाल properly with iptables... */
	अगर (conf->from_offset > conf->to_offset)
		वापस -EINVAL;
	अगर (conf->algo[XT_STRING_MAX_ALGO_NAME_SIZE - 1] != '\0')
		वापस -EINVAL;
	अगर (conf->patlen > XT_STRING_MAX_PATTERN_SIZE)
		वापस -EINVAL;
	अगर (conf->u.v1.flags &
	    ~(XT_STRING_FLAG_IGNORECASE | XT_STRING_FLAG_INVERT))
		वापस -EINVAL;
	अगर (conf->u.v1.flags & XT_STRING_FLAG_IGNORECASE)
		flags |= TS_IGNORECASE;
	ts_conf = textsearch_prepare(conf->algo, conf->pattern, conf->patlen,
				     GFP_KERNEL, flags);
	अगर (IS_ERR(ts_conf))
		वापस PTR_ERR(ts_conf);

	conf->config = ts_conf;
	वापस 0;
पूर्ण

अटल व्योम string_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	textsearch_destroy(STRING_TEXT_PRIV(par->matchinfo)->config);
पूर्ण

अटल काष्ठा xt_match xt_string_mt_reg __पढ़ो_mostly = अणु
	.name       = "string",
	.revision   = 1,
	.family     = NFPROTO_UNSPEC,
	.checkentry = string_mt_check,
	.match      = string_mt,
	.destroy    = string_mt_destroy,
	.matchsize  = माप(काष्ठा xt_string_info),
	.usersize   = दुरत्व(काष्ठा xt_string_info, config),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init string_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&xt_string_mt_reg);
पूर्ण

अटल व्योम __निकास string_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&xt_string_mt_reg);
पूर्ण

module_init(string_mt_init);
module_निकास(string_mt_निकास);
