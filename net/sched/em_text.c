<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/em_text.c	Textsearch ematch
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/textsearch.h>
#समावेश <linux/tc_ematch/tc_em_text.h>
#समावेश <net/pkt_cls.h>

काष्ठा text_match अणु
	u16			from_offset;
	u16			to_offset;
	u8			from_layer;
	u8			to_layer;
	काष्ठा ts_config	*config;
पूर्ण;

#घोषणा EM_TEXT_PRIV(m) ((काष्ठा text_match *) (m)->data)

अटल पूर्णांक em_text_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *m,
			 काष्ठा tcf_pkt_info *info)
अणु
	काष्ठा text_match *पंचांग = EM_TEXT_PRIV(m);
	पूर्णांक from, to;

	from = tcf_get_base_ptr(skb, पंचांग->from_layer) - skb->data;
	from += पंचांग->from_offset;

	to = tcf_get_base_ptr(skb, पंचांग->to_layer) - skb->data;
	to += पंचांग->to_offset;

	वापस skb_find_text(skb, from, to, पंचांग->config) != अच_पूर्णांक_उच्च;
पूर्ण

अटल पूर्णांक em_text_change(काष्ठा net *net, व्योम *data, पूर्णांक len,
			  काष्ठा tcf_ematch *m)
अणु
	काष्ठा text_match *पंचांग;
	काष्ठा tcf_em_text *conf = data;
	काष्ठा ts_config *ts_conf;
	पूर्णांक flags = 0;

	अगर (len < माप(*conf) || len < (माप(*conf) + conf->pattern_len))
		वापस -EINVAL;

	अगर (conf->from_layer > conf->to_layer)
		वापस -EINVAL;

	अगर (conf->from_layer == conf->to_layer &&
	    conf->from_offset > conf->to_offset)
		वापस -EINVAL;

retry:
	ts_conf = textsearch_prepare(conf->algo, (u8 *) conf + माप(*conf),
				     conf->pattern_len, GFP_KERNEL, flags);

	अगर (flags & TS_AUTOLOAD)
		rtnl_lock();

	अगर (IS_ERR(ts_conf)) अणु
		अगर (PTR_ERR(ts_conf) == -ENOENT && !(flags & TS_AUTOLOAD)) अणु
			rtnl_unlock();
			flags |= TS_AUTOLOAD;
			जाओ retry;
		पूर्ण अन्यथा
			वापस PTR_ERR(ts_conf);
	पूर्ण अन्यथा अगर (flags & TS_AUTOLOAD) अणु
		textsearch_destroy(ts_conf);
		वापस -EAGAIN;
	पूर्ण

	पंचांग = kदो_स्मृति(माप(*पंचांग), GFP_KERNEL);
	अगर (पंचांग == शून्य) अणु
		textsearch_destroy(ts_conf);
		वापस -ENOBUFS;
	पूर्ण

	पंचांग->from_offset = conf->from_offset;
	पंचांग->to_offset   = conf->to_offset;
	पंचांग->from_layer  = conf->from_layer;
	पंचांग->to_layer    = conf->to_layer;
	पंचांग->config      = ts_conf;

	m->datalen = माप(*पंचांग);
	m->data = (अचिन्हित दीर्घ) पंचांग;

	वापस 0;
पूर्ण

अटल व्योम em_text_destroy(काष्ठा tcf_ematch *m)
अणु
	अगर (EM_TEXT_PRIV(m) && EM_TEXT_PRIV(m)->config)
		textsearch_destroy(EM_TEXT_PRIV(m)->config);
पूर्ण

अटल पूर्णांक em_text_dump(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *m)
अणु
	काष्ठा text_match *पंचांग = EM_TEXT_PRIV(m);
	काष्ठा tcf_em_text conf;

	म_नकलन(conf.algo, पंचांग->config->ops->name, माप(conf.algo) - 1);
	conf.from_offset = पंचांग->from_offset;
	conf.to_offset = पंचांग->to_offset;
	conf.from_layer = पंचांग->from_layer;
	conf.to_layer = पंचांग->to_layer;
	conf.pattern_len = textsearch_get_pattern_len(पंचांग->config);
	conf.pad = 0;

	अगर (nla_put_nohdr(skb, माप(conf), &conf) < 0)
		जाओ nla_put_failure;
	अगर (nla_append(skb, conf.pattern_len,
		       textsearch_get_pattern(पंचांग->config)) < 0)
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा tcf_ematch_ops em_text_ops = अणु
	.kind	  = TCF_EM_TEXT,
	.change	  = em_text_change,
	.match	  = em_text_match,
	.destroy  = em_text_destroy,
	.dump	  = em_text_dump,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_text_ops.link)
पूर्ण;

अटल पूर्णांक __init init_em_text(व्योम)
अणु
	वापस tcf_em_रेजिस्टर(&em_text_ops);
पूर्ण

अटल व्योम __निकास निकास_em_text(व्योम)
अणु
	tcf_em_unरेजिस्टर(&em_text_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_em_text);
module_निकास(निकास_em_text);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_TEXT);
