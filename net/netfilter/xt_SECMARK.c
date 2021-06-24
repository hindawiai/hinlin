<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Module क्रम modअगरying the secmark field of the skb, क्रम use by
 * security subप्रणालीs.
 *
 * Based on the nfmark match by:
 * (C) 1999-2001 Marc Boucher <marc@mbsi.ca>
 *
 * (C) 2006,2008 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/security.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_SECMARK.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Morris <jmorris@redhat.com>");
MODULE_DESCRIPTION("Xtables: packet security mark modification");
MODULE_ALIAS("ipt_SECMARK");
MODULE_ALIAS("ip6t_SECMARK");

अटल u8 mode;

अटल अचिन्हित पूर्णांक
secmark_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_secmark_target_info_v1 *info)
अणु
	u32 secmark = 0;

	चयन (mode) अणु
	हाल SECMARK_MODE_SEL:
		secmark = info->secid;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	skb->secmark = secmark;
	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक checkentry_lsm(काष्ठा xt_secmark_target_info_v1 *info)
अणु
	पूर्णांक err;

	info->secctx[SECMARK_SECCTX_MAX - 1] = '\0';
	info->secid = 0;

	err = security_secctx_to_secid(info->secctx, म_माप(info->secctx),
				       &info->secid);
	अगर (err) अणु
		अगर (err == -EINVAL)
			pr_info_ratelimited("invalid security context \'%s\'\n",
					    info->secctx);
		वापस err;
	पूर्ण

	अगर (!info->secid) अणु
		pr_info_ratelimited("unable to map security context \'%s\'\n",
				    info->secctx);
		वापस -ENOENT;
	पूर्ण

	err = security_secmark_relabel_packet(info->secid);
	अगर (err) अणु
		pr_info_ratelimited("unable to obtain relabeling permission\n");
		वापस err;
	पूर्ण

	security_secmark_refcount_inc();
	वापस 0;
पूर्ण

अटल पूर्णांक
secmark_tg_check(स्थिर अक्षर *table, काष्ठा xt_secmark_target_info_v1 *info)
अणु
	पूर्णांक err;

	अगर (म_भेद(table, "mangle") != 0 &&
	    म_भेद(table, "security") != 0) अणु
		pr_info_ratelimited("only valid in \'mangle\' or \'security\' table, not \'%s\'\n",
				    table);
		वापस -EINVAL;
	पूर्ण

	अगर (mode && mode != info->mode) अणु
		pr_info_ratelimited("mode already set to %hu cannot mix with rules for mode %hu\n",
				    mode, info->mode);
		वापस -EINVAL;
	पूर्ण

	चयन (info->mode) अणु
	हाल SECMARK_MODE_SEL:
		अवरोध;
	शेष:
		pr_info_ratelimited("invalid mode: %hu\n", info->mode);
		वापस -EINVAL;
	पूर्ण

	err = checkentry_lsm(info);
	अगर (err)
		वापस err;

	अगर (!mode)
		mode = info->mode;
	वापस 0;
पूर्ण

अटल व्योम secmark_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	चयन (mode) अणु
	हाल SECMARK_MODE_SEL:
		security_secmark_refcount_dec();
	पूर्ण
पूर्ण

अटल पूर्णांक secmark_tg_check_v0(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा xt_secmark_target_info *info = par->targinfo;
	काष्ठा xt_secmark_target_info_v1 newinfo = अणु
		.mode	= info->mode,
	पूर्ण;
	पूर्णांक ret;

	स_नकल(newinfo.secctx, info->secctx, SECMARK_SECCTX_MAX);

	ret = secmark_tg_check(par->table, &newinfo);
	info->secid = newinfo.secid;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक
secmark_tg_v0(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_secmark_target_info *info = par->targinfo;
	काष्ठा xt_secmark_target_info_v1 newinfo = अणु
		.secid	= info->secid,
	पूर्ण;

	वापस secmark_tg(skb, &newinfo);
पूर्ण

अटल पूर्णांक secmark_tg_check_v1(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	वापस secmark_tg_check(par->table, par->targinfo);
पूर्ण

अटल अचिन्हित पूर्णांक
secmark_tg_v1(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	वापस secmark_tg(skb, par->targinfo);
पूर्ण

अटल काष्ठा xt_target secmark_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "SECMARK",
		.revision	= 0,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= secmark_tg_check_v0,
		.destroy	= secmark_tg_destroy,
		.target		= secmark_tg_v0,
		.tarमाला_लोize	= माप(काष्ठा xt_secmark_target_info),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "SECMARK",
		.revision	= 1,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= secmark_tg_check_v1,
		.destroy	= secmark_tg_destroy,
		.target		= secmark_tg_v1,
		.tarमाला_लोize	= माप(काष्ठा xt_secmark_target_info_v1),
		.usersize	= दुरत्व(काष्ठा xt_secmark_target_info_v1, secid),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init secmark_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(secmark_tg_reg, ARRAY_SIZE(secmark_tg_reg));
पूर्ण

अटल व्योम __निकास secmark_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(secmark_tg_reg, ARRAY_SIZE(secmark_tg_reg));
पूर्ण

module_init(secmark_tg_init);
module_निकास(secmark_tg_निकास);
