<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */

#समावेश <linux/fs.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>

काष्ठा bpf_iter_target_info अणु
	काष्ठा list_head list;
	स्थिर काष्ठा bpf_iter_reg *reg_info;
	u32 btf_id;	/* cached value */
पूर्ण;

काष्ठा bpf_iter_link अणु
	काष्ठा bpf_link link;
	काष्ठा bpf_iter_aux_info aux;
	काष्ठा bpf_iter_target_info *tinfo;
पूर्ण;

काष्ठा bpf_iter_priv_data अणु
	काष्ठा bpf_iter_target_info *tinfo;
	स्थिर काष्ठा bpf_iter_seq_info *seq_info;
	काष्ठा bpf_prog *prog;
	u64 session_id;
	u64 seq_num;
	bool करोne_stop;
	u8 target_निजी[] __aligned(8);
पूर्ण;

अटल काष्ठा list_head tarमाला_लो = LIST_HEAD_INIT(tarमाला_लो);
अटल DEFINE_MUTEX(tarमाला_लो_mutex);

/* protect bpf_iter_link changes */
अटल DEFINE_MUTEX(link_mutex);

/* incremented on every खोलोed seq_file */
अटल atomic64_t session_id;

अटल पूर्णांक prepare_seq_file(काष्ठा file *file, काष्ठा bpf_iter_link *link,
			    स्थिर काष्ठा bpf_iter_seq_info *seq_info);

अटल व्योम bpf_iter_inc_seq_num(काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_iter_priv_data *iter_priv;

	iter_priv = container_of(seq->निजी, काष्ठा bpf_iter_priv_data,
				 target_निजी);
	iter_priv->seq_num++;
पूर्ण

अटल व्योम bpf_iter_dec_seq_num(काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_iter_priv_data *iter_priv;

	iter_priv = container_of(seq->निजी, काष्ठा bpf_iter_priv_data,
				 target_निजी);
	iter_priv->seq_num--;
पूर्ण

अटल व्योम bpf_iter_करोne_stop(काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_iter_priv_data *iter_priv;

	iter_priv = container_of(seq->निजी, काष्ठा bpf_iter_priv_data,
				 target_निजी);
	iter_priv->करोne_stop = true;
पूर्ण

अटल bool bpf_iter_support_resched(काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_iter_priv_data *iter_priv;

	iter_priv = container_of(seq->निजी, काष्ठा bpf_iter_priv_data,
				 target_निजी);
	वापस iter_priv->tinfo->reg_info->feature & BPF_ITER_RESCHED;
पूर्ण

/* maximum visited objects beक्रमe bailing out */
#घोषणा MAX_ITER_OBJECTS	1000000

/* bpf_seq_पढ़ो, a customized and simpler version क्रम bpf iterator.
 * no_llseek is assumed क्रम this file.
 * The following are dअगरferences from seq_पढ़ो():
 *  . fixed buffer size (PAGE_SIZE)
 *  . assuming no_llseek
 *  . stop() may call bpf program, handling potential overflow there
 */
अटल sमाप_प्रकार bpf_seq_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size,
			    loff_t *ppos)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	माप_प्रकार n, offs, copied = 0;
	पूर्णांक err = 0, num_objs = 0;
	bool can_resched;
	व्योम *p;

	mutex_lock(&seq->lock);

	अगर (!seq->buf) अणु
		seq->size = PAGE_SIZE << 3;
		seq->buf = kvदो_स्मृति(seq->size, GFP_KERNEL);
		अगर (!seq->buf) अणु
			err = -ENOMEM;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (seq->count) अणु
		n = min(seq->count, size);
		err = copy_to_user(buf, seq->buf + seq->from, n);
		अगर (err) अणु
			err = -EFAULT;
			जाओ करोne;
		पूर्ण
		seq->count -= n;
		seq->from += n;
		copied = n;
		जाओ करोne;
	पूर्ण

	seq->from = 0;
	p = seq->op->start(seq, &seq->index);
	अगर (!p)
		जाओ stop;
	अगर (IS_ERR(p)) अणु
		err = PTR_ERR(p);
		seq->op->stop(seq, p);
		seq->count = 0;
		जाओ करोne;
	पूर्ण

	err = seq->op->show(seq, p);
	अगर (err > 0) अणु
		/* object is skipped, decrease seq_num, so next
		 * valid object can reuse the same seq_num.
		 */
		bpf_iter_dec_seq_num(seq);
		seq->count = 0;
	पूर्ण अन्यथा अगर (err < 0 || seq_has_overflowed(seq)) अणु
		अगर (!err)
			err = -E2BIG;
		seq->op->stop(seq, p);
		seq->count = 0;
		जाओ करोne;
	पूर्ण

	can_resched = bpf_iter_support_resched(seq);
	जबतक (1) अणु
		loff_t pos = seq->index;

		num_objs++;
		offs = seq->count;
		p = seq->op->next(seq, p, &seq->index);
		अगर (pos == seq->index) अणु
			pr_info_ratelimited("buggy seq_file .next function %ps "
				"did not updated position index\n",
				seq->op->next);
			seq->index++;
		पूर्ण

		अगर (IS_ERR_OR_शून्य(p))
			अवरोध;

		/* got a valid next object, increase seq_num */
		bpf_iter_inc_seq_num(seq);

		अगर (seq->count >= size)
			अवरोध;

		अगर (num_objs >= MAX_ITER_OBJECTS) अणु
			अगर (offs == 0) अणु
				err = -EAGAIN;
				seq->op->stop(seq, p);
				जाओ करोne;
			पूर्ण
			अवरोध;
		पूर्ण

		err = seq->op->show(seq, p);
		अगर (err > 0) अणु
			bpf_iter_dec_seq_num(seq);
			seq->count = offs;
		पूर्ण अन्यथा अगर (err < 0 || seq_has_overflowed(seq)) अणु
			seq->count = offs;
			अगर (offs == 0) अणु
				अगर (!err)
					err = -E2BIG;
				seq->op->stop(seq, p);
				जाओ करोne;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (can_resched)
			cond_resched();
	पूर्ण
stop:
	offs = seq->count;
	/* bpf program called अगर !p */
	seq->op->stop(seq, p);
	अगर (!p) अणु
		अगर (!seq_has_overflowed(seq)) अणु
			bpf_iter_करोne_stop(seq);
		पूर्ण अन्यथा अणु
			seq->count = offs;
			अगर (offs == 0) अणु
				err = -E2BIG;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	n = min(seq->count, size);
	err = copy_to_user(buf, seq->buf, n);
	अगर (err) अणु
		err = -EFAULT;
		जाओ करोne;
	पूर्ण
	copied = n;
	seq->count -= n;
	seq->from = n;
करोne:
	अगर (!copied)
		copied = err;
	अन्यथा
		*ppos += copied;
	mutex_unlock(&seq->lock);
	वापस copied;
पूर्ण

अटल स्थिर काष्ठा bpf_iter_seq_info *
__get_seq_info(काष्ठा bpf_iter_link *link)
अणु
	स्थिर काष्ठा bpf_iter_seq_info *seq_info;

	अगर (link->aux.map) अणु
		seq_info = link->aux.map->ops->iter_seq_info;
		अगर (seq_info)
			वापस seq_info;
	पूर्ण

	वापस link->tinfo->reg_info->seq_info;
पूर्ण

अटल पूर्णांक iter_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bpf_iter_link *link = inode->i_निजी;

	वापस prepare_seq_file(file, link, __get_seq_info(link));
पूर्ण

अटल पूर्णांक iter_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bpf_iter_priv_data *iter_priv;
	काष्ठा seq_file *seq;

	seq = file->निजी_data;
	अगर (!seq)
		वापस 0;

	iter_priv = container_of(seq->निजी, काष्ठा bpf_iter_priv_data,
				 target_निजी);

	अगर (iter_priv->seq_info->fini_seq_निजी)
		iter_priv->seq_info->fini_seq_निजी(seq->निजी);

	bpf_prog_put(iter_priv->prog);
	seq->निजी = iter_priv;

	वापस seq_release_निजी(inode, file);
पूर्ण

स्थिर काष्ठा file_operations bpf_iter_fops = अणु
	.खोलो		= iter_खोलो,
	.llseek		= no_llseek,
	.पढ़ो		= bpf_seq_पढ़ो,
	.release	= iter_release,
पूर्ण;

/* The argument reg_info will be cached in bpf_iter_target_info.
 * The common practice is to declare target reg_info as
 * a स्थिर अटल variable and passed as an argument to
 * bpf_iter_reg_target().
 */
पूर्णांक bpf_iter_reg_target(स्थिर काष्ठा bpf_iter_reg *reg_info)
अणु
	काष्ठा bpf_iter_target_info *tinfo;

	tinfo = kzalloc(माप(*tinfo), GFP_KERNEL);
	अगर (!tinfo)
		वापस -ENOMEM;

	tinfo->reg_info = reg_info;
	INIT_LIST_HEAD(&tinfo->list);

	mutex_lock(&tarमाला_लो_mutex);
	list_add(&tinfo->list, &tarमाला_लो);
	mutex_unlock(&tarमाला_लो_mutex);

	वापस 0;
पूर्ण

व्योम bpf_iter_unreg_target(स्थिर काष्ठा bpf_iter_reg *reg_info)
अणु
	काष्ठा bpf_iter_target_info *tinfo;
	bool found = false;

	mutex_lock(&tarमाला_लो_mutex);
	list_क्रम_each_entry(tinfo, &tarमाला_लो, list) अणु
		अगर (reg_info == tinfo->reg_info) अणु
			list_del(&tinfo->list);
			kमुक्त(tinfo);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tarमाला_लो_mutex);

	WARN_ON(found == false);
पूर्ण

अटल व्योम cache_btf_id(काष्ठा bpf_iter_target_info *tinfo,
			 काष्ठा bpf_prog *prog)
अणु
	tinfo->btf_id = prog->aux->attach_btf_id;
पूर्ण

bool bpf_iter_prog_supported(काष्ठा bpf_prog *prog)
अणु
	स्थिर अक्षर *attach_fname = prog->aux->attach_func_name;
	u32 prog_btf_id = prog->aux->attach_btf_id;
	स्थिर अक्षर *prefix = BPF_ITER_FUNC_PREFIX;
	काष्ठा bpf_iter_target_info *tinfo;
	पूर्णांक prefix_len = म_माप(prefix);
	bool supported = false;

	अगर (म_भेदन(attach_fname, prefix, prefix_len))
		वापस false;

	mutex_lock(&tarमाला_लो_mutex);
	list_क्रम_each_entry(tinfo, &tarमाला_लो, list) अणु
		अगर (tinfo->btf_id && tinfo->btf_id == prog_btf_id) अणु
			supported = true;
			अवरोध;
		पूर्ण
		अगर (!म_भेद(attach_fname + prefix_len, tinfo->reg_info->target)) अणु
			cache_btf_id(tinfo, prog);
			supported = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tarमाला_लो_mutex);

	अगर (supported) अणु
		prog->aux->ctx_arg_info_size = tinfo->reg_info->ctx_arg_info_size;
		prog->aux->ctx_arg_info = tinfo->reg_info->ctx_arg_info;
	पूर्ण

	वापस supported;
पूर्ण

अटल व्योम bpf_iter_link_release(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_iter_link *iter_link =
		container_of(link, काष्ठा bpf_iter_link, link);

	अगर (iter_link->tinfo->reg_info->detach_target)
		iter_link->tinfo->reg_info->detach_target(&iter_link->aux);
पूर्ण

अटल व्योम bpf_iter_link_dealloc(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_iter_link *iter_link =
		container_of(link, काष्ठा bpf_iter_link, link);

	kमुक्त(iter_link);
पूर्ण

अटल पूर्णांक bpf_iter_link_replace(काष्ठा bpf_link *link,
				 काष्ठा bpf_prog *new_prog,
				 काष्ठा bpf_prog *old_prog)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&link_mutex);
	अगर (old_prog && link->prog != old_prog) अणु
		ret = -EPERM;
		जाओ out_unlock;
	पूर्ण

	अगर (link->prog->type != new_prog->type ||
	    link->prog->expected_attach_type != new_prog->expected_attach_type ||
	    link->prog->aux->attach_btf_id != new_prog->aux->attach_btf_id) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	old_prog = xchg(&link->prog, new_prog);
	bpf_prog_put(old_prog);

out_unlock:
	mutex_unlock(&link_mutex);
	वापस ret;
पूर्ण

अटल व्योम bpf_iter_link_show_fdinfo(स्थिर काष्ठा bpf_link *link,
				      काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_iter_link *iter_link =
		container_of(link, काष्ठा bpf_iter_link, link);
	bpf_iter_show_fdinfo_t show_fdinfo;

	seq_म_लिखो(seq,
		   "target_name:\t%s\n",
		   iter_link->tinfo->reg_info->target);

	show_fdinfo = iter_link->tinfo->reg_info->show_fdinfo;
	अगर (show_fdinfo)
		show_fdinfo(&iter_link->aux, seq);
पूर्ण

अटल पूर्णांक bpf_iter_link_fill_link_info(स्थिर काष्ठा bpf_link *link,
					काष्ठा bpf_link_info *info)
अणु
	काष्ठा bpf_iter_link *iter_link =
		container_of(link, काष्ठा bpf_iter_link, link);
	अक्षर __user *ubuf = u64_to_user_ptr(info->iter.target_name);
	bpf_iter_fill_link_info_t fill_link_info;
	u32 ulen = info->iter.target_name_len;
	स्थिर अक्षर *target_name;
	u32 target_len;

	अगर (!ulen ^ !ubuf)
		वापस -EINVAL;

	target_name = iter_link->tinfo->reg_info->target;
	target_len =  म_माप(target_name);
	info->iter.target_name_len = target_len + 1;

	अगर (ubuf) अणु
		अगर (ulen >= target_len + 1) अणु
			अगर (copy_to_user(ubuf, target_name, target_len + 1))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			अक्षर zero = '\0';

			अगर (copy_to_user(ubuf, target_name, ulen - 1))
				वापस -EFAULT;
			अगर (put_user(zero, ubuf + ulen - 1))
				वापस -EFAULT;
			वापस -ENOSPC;
		पूर्ण
	पूर्ण

	fill_link_info = iter_link->tinfo->reg_info->fill_link_info;
	अगर (fill_link_info)
		वापस fill_link_info(&iter_link->aux, info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_link_ops bpf_iter_link_lops = अणु
	.release = bpf_iter_link_release,
	.dealloc = bpf_iter_link_dealloc,
	.update_prog = bpf_iter_link_replace,
	.show_fdinfo = bpf_iter_link_show_fdinfo,
	.fill_link_info = bpf_iter_link_fill_link_info,
पूर्ण;

bool bpf_link_is_iter(काष्ठा bpf_link *link)
अणु
	वापस link->ops == &bpf_iter_link_lops;
पूर्ण

पूर्णांक bpf_iter_link_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog)
अणु
	जोड़ bpf_iter_link_info __user *ulinfo;
	काष्ठा bpf_link_primer link_primer;
	काष्ठा bpf_iter_target_info *tinfo;
	जोड़ bpf_iter_link_info linfo;
	काष्ठा bpf_iter_link *link;
	u32 prog_btf_id, linfo_len;
	bool existed = false;
	पूर्णांक err;

	अगर (attr->link_create.target_fd || attr->link_create.flags)
		वापस -EINVAL;

	स_रखो(&linfo, 0, माप(जोड़ bpf_iter_link_info));

	ulinfo = u64_to_user_ptr(attr->link_create.iter_info);
	linfo_len = attr->link_create.iter_info_len;
	अगर (!ulinfo ^ !linfo_len)
		वापस -EINVAL;

	अगर (ulinfo) अणु
		err = bpf_check_uarg_tail_zero(ulinfo, माप(linfo),
					       linfo_len);
		अगर (err)
			वापस err;
		linfo_len = min_t(u32, linfo_len, माप(linfo));
		अगर (copy_from_user(&linfo, ulinfo, linfo_len))
			वापस -EFAULT;
	पूर्ण

	prog_btf_id = prog->aux->attach_btf_id;
	mutex_lock(&tarमाला_लो_mutex);
	list_क्रम_each_entry(tinfo, &tarमाला_लो, list) अणु
		अगर (tinfo->btf_id == prog_btf_id) अणु
			existed = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tarमाला_लो_mutex);
	अगर (!existed)
		वापस -ENOENT;

	link = kzalloc(माप(*link), GFP_USER | __GFP_NOWARN);
	अगर (!link)
		वापस -ENOMEM;

	bpf_link_init(&link->link, BPF_LINK_TYPE_ITER, &bpf_iter_link_lops, prog);
	link->tinfo = tinfo;

	err  = bpf_link_prime(&link->link, &link_primer);
	अगर (err) अणु
		kमुक्त(link);
		वापस err;
	पूर्ण

	अगर (tinfo->reg_info->attach_target) अणु
		err = tinfo->reg_info->attach_target(prog, &linfo, &link->aux);
		अगर (err) अणु
			bpf_link_cleanup(&link_primer);
			वापस err;
		पूर्ण
	पूर्ण

	वापस bpf_link_settle(&link_primer);
पूर्ण

अटल व्योम init_seq_meta(काष्ठा bpf_iter_priv_data *priv_data,
			  काष्ठा bpf_iter_target_info *tinfo,
			  स्थिर काष्ठा bpf_iter_seq_info *seq_info,
			  काष्ठा bpf_prog *prog)
अणु
	priv_data->tinfo = tinfo;
	priv_data->seq_info = seq_info;
	priv_data->prog = prog;
	priv_data->session_id = atomic64_inc_वापस(&session_id);
	priv_data->seq_num = 0;
	priv_data->करोne_stop = false;
पूर्ण

अटल पूर्णांक prepare_seq_file(काष्ठा file *file, काष्ठा bpf_iter_link *link,
			    स्थिर काष्ठा bpf_iter_seq_info *seq_info)
अणु
	काष्ठा bpf_iter_priv_data *priv_data;
	काष्ठा bpf_iter_target_info *tinfo;
	काष्ठा bpf_prog *prog;
	u32 total_priv_dsize;
	काष्ठा seq_file *seq;
	पूर्णांक err = 0;

	mutex_lock(&link_mutex);
	prog = link->link.prog;
	bpf_prog_inc(prog);
	mutex_unlock(&link_mutex);

	tinfo = link->tinfo;
	total_priv_dsize = दुरत्व(काष्ठा bpf_iter_priv_data, target_निजी) +
			   seq_info->seq_priv_size;
	priv_data = __seq_खोलो_निजी(file, seq_info->seq_ops,
				       total_priv_dsize);
	अगर (!priv_data) अणु
		err = -ENOMEM;
		जाओ release_prog;
	पूर्ण

	अगर (seq_info->init_seq_निजी) अणु
		err = seq_info->init_seq_निजी(priv_data->target_निजी, &link->aux);
		अगर (err)
			जाओ release_seq_file;
	पूर्ण

	init_seq_meta(priv_data, tinfo, seq_info, prog);
	seq = file->निजी_data;
	seq->निजी = priv_data->target_निजी;

	वापस 0;

release_seq_file:
	seq_release_निजी(file->f_inode, file);
	file->निजी_data = शून्य;
release_prog:
	bpf_prog_put(prog);
	वापस err;
पूर्ण

पूर्णांक bpf_iter_new_fd(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_iter_link *iter_link;
	काष्ठा file *file;
	अचिन्हित पूर्णांक flags;
	पूर्णांक err, fd;

	अगर (link->ops != &bpf_iter_link_lops)
		वापस -EINVAL;

	flags = O_RDONLY | O_CLOEXEC;
	fd = get_unused_fd_flags(flags);
	अगर (fd < 0)
		वापस fd;

	file = anon_inode_getfile("bpf_iter", &bpf_iter_fops, शून्य, flags);
	अगर (IS_ERR(file)) अणु
		err = PTR_ERR(file);
		जाओ मुक्त_fd;
	पूर्ण

	iter_link = container_of(link, काष्ठा bpf_iter_link, link);
	err = prepare_seq_file(file, iter_link, __get_seq_info(iter_link));
	अगर (err)
		जाओ मुक्त_file;

	fd_install(fd, file);
	वापस fd;

मुक्त_file:
	fput(file);
मुक्त_fd:
	put_unused_fd(fd);
	वापस err;
पूर्ण

काष्ठा bpf_prog *bpf_iter_get_info(काष्ठा bpf_iter_meta *meta, bool in_stop)
अणु
	काष्ठा bpf_iter_priv_data *iter_priv;
	काष्ठा seq_file *seq;
	व्योम *seq_priv;

	seq = meta->seq;
	अगर (seq->file->f_op != &bpf_iter_fops)
		वापस शून्य;

	seq_priv = seq->निजी;
	iter_priv = container_of(seq_priv, काष्ठा bpf_iter_priv_data,
				 target_निजी);

	अगर (in_stop && iter_priv->करोne_stop)
		वापस शून्य;

	meta->session_id = iter_priv->session_id;
	meta->seq_num = iter_priv->seq_num;

	वापस iter_priv->prog;
पूर्ण

पूर्णांक bpf_iter_run_prog(काष्ठा bpf_prog *prog, व्योम *ctx)
अणु
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	migrate_disable();
	ret = BPF_PROG_RUN(prog, ctx);
	migrate_enable();
	rcu_पढ़ो_unlock();

	/* bpf program can only वापस 0 or 1:
	 *  0 : okay
	 *  1 : retry the same object
	 * The bpf_iter_run_prog() वापस value
	 * will be seq_ops->show() वापस value.
	 */
	वापस ret == 0 ? 0 : -EAGAIN;
पूर्ण

BPF_CALL_4(bpf_क्रम_each_map_elem, काष्ठा bpf_map *, map, व्योम *, callback_fn,
	   व्योम *, callback_ctx, u64, flags)
अणु
	वापस map->ops->map_क्रम_each_callback(map, callback_fn, callback_ctx, flags);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_क्रम_each_map_elem_proto = अणु
	.func		= bpf_क्रम_each_map_elem,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_FUNC,
	.arg3_type	= ARG_PTR_TO_STACK_OR_शून्य,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;
