<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */
#समावेश <linux/bpf.h>
#समावेश <linux/fs.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>
#समावेश <linux/btf_ids.h>

काष्ठा bpf_iter_seq_prog_info अणु
	u32 prog_id;
पूर्ण;

अटल व्योम *bpf_prog_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_prog_info *info = seq->निजी;
	काष्ठा bpf_prog *prog;

	prog = bpf_prog_get_curr_or_next(&info->prog_id);
	अगर (!prog)
		वापस शून्य;

	अगर (*pos == 0)
		++*pos;
	वापस prog;
पूर्ण

अटल व्योम *bpf_prog_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_prog_info *info = seq->निजी;

	++*pos;
	++info->prog_id;
	bpf_prog_put((काष्ठा bpf_prog *)v);
	वापस bpf_prog_get_curr_or_next(&info->prog_id);
पूर्ण

काष्ठा bpf_iter__bpf_prog अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा bpf_prog *, prog);
पूर्ण;

DEFINE_BPF_ITER_FUNC(bpf_prog, काष्ठा bpf_iter_meta *meta, काष्ठा bpf_prog *prog)

अटल पूर्णांक __bpf_prog_seq_show(काष्ठा seq_file *seq, व्योम *v, bool in_stop)
अणु
	काष्ठा bpf_iter__bpf_prog ctx;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = 0;

	ctx.meta = &meta;
	ctx.prog = v;
	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, in_stop);
	अगर (prog)
		ret = bpf_iter_run_prog(prog, &ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक bpf_prog_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __bpf_prog_seq_show(seq, v, false);
पूर्ण

अटल व्योम bpf_prog_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (!v)
		(व्योम)__bpf_prog_seq_show(seq, v, true);
	अन्यथा
		bpf_prog_put((काष्ठा bpf_prog *)v);
पूर्ण

अटल स्थिर काष्ठा seq_operations bpf_prog_seq_ops = अणु
	.start	= bpf_prog_seq_start,
	.next	= bpf_prog_seq_next,
	.stop	= bpf_prog_seq_stop,
	.show	= bpf_prog_seq_show,
पूर्ण;

BTF_ID_LIST(btf_bpf_prog_id)
BTF_ID(काष्ठा, bpf_prog)

अटल स्थिर काष्ठा bpf_iter_seq_info bpf_prog_seq_info = अणु
	.seq_ops		= &bpf_prog_seq_ops,
	.init_seq_निजी	= शून्य,
	.fini_seq_निजी	= शून्य,
	.seq_priv_size		= माप(काष्ठा bpf_iter_seq_prog_info),
पूर्ण;

अटल काष्ठा bpf_iter_reg bpf_prog_reg_info = अणु
	.target			= "bpf_prog",
	.ctx_arg_info_size	= 1,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__bpf_prog, prog),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &bpf_prog_seq_info,
पूर्ण;

अटल पूर्णांक __init bpf_prog_iter_init(व्योम)
अणु
	bpf_prog_reg_info.ctx_arg_info[0].btf_id = *btf_bpf_prog_id;
	वापस bpf_iter_reg_target(&bpf_prog_reg_info);
पूर्ण

late_initcall(bpf_prog_iter_init);
