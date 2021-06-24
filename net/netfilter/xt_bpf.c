<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Xtables module to match packets using a BPF filter.
 * Copyright 2013 Google Inc.
 * Written by Willem de Bruijn <willemb@google.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>

#समावेश <linux/netfilter/xt_bpf.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_AUTHOR("Willem de Bruijn <willemb@google.com>");
MODULE_DESCRIPTION("Xtables: BPF filter match");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_bpf");
MODULE_ALIAS("ip6t_bpf");

अटल पूर्णांक __bpf_mt_check_bytecode(काष्ठा sock_filter *insns, __u16 len,
				   काष्ठा bpf_prog **ret)
अणु
	काष्ठा sock_fprog_kern program;

	अगर (len > XT_BPF_MAX_NUM_INSTR)
		वापस -EINVAL;

	program.len = len;
	program.filter = insns;

	अगर (bpf_prog_create(ret, &program)) अणु
		pr_info_ratelimited("check failed: parse error\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __bpf_mt_check_fd(पूर्णांक fd, काष्ठा bpf_prog **ret)
अणु
	काष्ठा bpf_prog *prog;

	prog = bpf_prog_get_type(fd, BPF_PROG_TYPE_SOCKET_FILTER);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	*ret = prog;
	वापस 0;
पूर्ण

अटल पूर्णांक __bpf_mt_check_path(स्थिर अक्षर *path, काष्ठा bpf_prog **ret)
अणु
	अगर (strnlen(path, XT_BPF_PATH_MAX) == XT_BPF_PATH_MAX)
		वापस -EINVAL;

	*ret = bpf_prog_get_type_path(path, BPF_PROG_TYPE_SOCKET_FILTER);
	वापस PTR_ERR_OR_ZERO(*ret);
पूर्ण

अटल पूर्णांक bpf_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_bpf_info *info = par->matchinfo;

	वापस __bpf_mt_check_bytecode(info->bpf_program,
				       info->bpf_program_num_elem,
				       &info->filter);
पूर्ण

अटल पूर्णांक bpf_mt_check_v1(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_bpf_info_v1 *info = par->matchinfo;

	अगर (info->mode == XT_BPF_MODE_BYTECODE)
		वापस __bpf_mt_check_bytecode(info->bpf_program,
					       info->bpf_program_num_elem,
					       &info->filter);
	अन्यथा अगर (info->mode == XT_BPF_MODE_FD_ELF)
		वापस __bpf_mt_check_fd(info->fd, &info->filter);
	अन्यथा अगर (info->mode == XT_BPF_MODE_PATH_PINNED)
		वापस __bpf_mt_check_path(info->path, &info->filter);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल bool bpf_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_bpf_info *info = par->matchinfo;

	वापस BPF_PROG_RUN(info->filter, skb);
पूर्ण

अटल bool bpf_mt_v1(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_bpf_info_v1 *info = par->matchinfo;

	वापस !!bpf_prog_run_save_cb(info->filter, (काष्ठा sk_buff *) skb);
पूर्ण

अटल व्योम bpf_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_bpf_info *info = par->matchinfo;

	bpf_prog_destroy(info->filter);
पूर्ण

अटल व्योम bpf_mt_destroy_v1(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_bpf_info_v1 *info = par->matchinfo;

	bpf_prog_destroy(info->filter);
पूर्ण

अटल काष्ठा xt_match bpf_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "bpf",
		.revision	= 0,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= bpf_mt_check,
		.match		= bpf_mt,
		.destroy	= bpf_mt_destroy,
		.matchsize	= माप(काष्ठा xt_bpf_info),
		.usersize	= दुरत्व(काष्ठा xt_bpf_info, filter),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "bpf",
		.revision	= 1,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= bpf_mt_check_v1,
		.match		= bpf_mt_v1,
		.destroy	= bpf_mt_destroy_v1,
		.matchsize	= माप(काष्ठा xt_bpf_info_v1),
		.usersize	= दुरत्व(काष्ठा xt_bpf_info_v1, filter),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init bpf_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(bpf_mt_reg, ARRAY_SIZE(bpf_mt_reg));
पूर्ण

अटल व्योम __निकास bpf_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(bpf_mt_reg, ARRAY_SIZE(bpf_mt_reg));
पूर्ण

module_init(bpf_mt_init);
module_निकास(bpf_mt_निकास);
