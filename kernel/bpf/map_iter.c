<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */
#समावेश <linux/bpf.h>
#समावेश <linux/fs.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>
#समावेश <linux/btf_ids.h>

काष्ठा bpf_iter_seq_map_info अणु
	u32 map_id;
पूर्ण;

अटल व्योम *bpf_map_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_map_info *info = seq->निजी;
	काष्ठा bpf_map *map;

	map = bpf_map_get_curr_or_next(&info->map_id);
	अगर (!map)
		वापस शून्य;

	अगर (*pos == 0)
		++*pos;
	वापस map;
पूर्ण

अटल व्योम *bpf_map_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_map_info *info = seq->निजी;

	++*pos;
	++info->map_id;
	bpf_map_put((काष्ठा bpf_map *)v);
	वापस bpf_map_get_curr_or_next(&info->map_id);
पूर्ण

काष्ठा bpf_iter__bpf_map अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा bpf_map *, map);
पूर्ण;

DEFINE_BPF_ITER_FUNC(bpf_map, काष्ठा bpf_iter_meta *meta, काष्ठा bpf_map *map)

अटल पूर्णांक __bpf_map_seq_show(काष्ठा seq_file *seq, व्योम *v, bool in_stop)
अणु
	काष्ठा bpf_iter__bpf_map ctx;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = 0;

	ctx.meta = &meta;
	ctx.map = v;
	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, in_stop);
	अगर (prog)
		ret = bpf_iter_run_prog(prog, &ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक bpf_map_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __bpf_map_seq_show(seq, v, false);
पूर्ण

अटल व्योम bpf_map_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (!v)
		(व्योम)__bpf_map_seq_show(seq, v, true);
	अन्यथा
		bpf_map_put((काष्ठा bpf_map *)v);
पूर्ण

अटल स्थिर काष्ठा seq_operations bpf_map_seq_ops = अणु
	.start	= bpf_map_seq_start,
	.next	= bpf_map_seq_next,
	.stop	= bpf_map_seq_stop,
	.show	= bpf_map_seq_show,
पूर्ण;

BTF_ID_LIST(btf_bpf_map_id)
BTF_ID(काष्ठा, bpf_map)

अटल स्थिर काष्ठा bpf_iter_seq_info bpf_map_seq_info = अणु
	.seq_ops		= &bpf_map_seq_ops,
	.init_seq_निजी	= शून्य,
	.fini_seq_निजी	= शून्य,
	.seq_priv_size		= माप(काष्ठा bpf_iter_seq_map_info),
पूर्ण;

अटल काष्ठा bpf_iter_reg bpf_map_reg_info = अणु
	.target			= "bpf_map",
	.ctx_arg_info_size	= 1,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__bpf_map, map),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &bpf_map_seq_info,
पूर्ण;

अटल पूर्णांक bpf_iter_attach_map(काष्ठा bpf_prog *prog,
			       जोड़ bpf_iter_link_info *linfo,
			       काष्ठा bpf_iter_aux_info *aux)
अणु
	u32 key_acc_size, value_acc_size, key_size, value_size;
	काष्ठा bpf_map *map;
	bool is_percpu = false;
	पूर्णांक err = -EINVAL;

	अगर (!linfo->map.map_fd)
		वापस -EBADF;

	map = bpf_map_get_with_uref(linfo->map.map_fd);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	अगर (map->map_type == BPF_MAP_TYPE_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_PERCPU_ARRAY)
		is_percpu = true;
	अन्यथा अगर (map->map_type != BPF_MAP_TYPE_HASH &&
		 map->map_type != BPF_MAP_TYPE_LRU_HASH &&
		 map->map_type != BPF_MAP_TYPE_ARRAY)
		जाओ put_map;

	key_acc_size = prog->aux->max_rकरोnly_access;
	value_acc_size = prog->aux->max_rdwr_access;
	key_size = map->key_size;
	अगर (!is_percpu)
		value_size = map->value_size;
	अन्यथा
		value_size = round_up(map->value_size, 8) * num_possible_cpus();

	अगर (key_acc_size > key_size || value_acc_size > value_size) अणु
		err = -EACCES;
		जाओ put_map;
	पूर्ण

	aux->map = map;
	वापस 0;

put_map:
	bpf_map_put_with_uref(map);
	वापस err;
पूर्ण

अटल व्योम bpf_iter_detach_map(काष्ठा bpf_iter_aux_info *aux)
अणु
	bpf_map_put_with_uref(aux->map);
पूर्ण

व्योम bpf_iter_map_show_fdinfo(स्थिर काष्ठा bpf_iter_aux_info *aux,
			      काष्ठा seq_file *seq)
अणु
	seq_म_लिखो(seq, "map_id:\t%u\n", aux->map->id);
पूर्ण

पूर्णांक bpf_iter_map_fill_link_info(स्थिर काष्ठा bpf_iter_aux_info *aux,
				काष्ठा bpf_link_info *info)
अणु
	info->iter.map.map_id = aux->map->id;
	वापस 0;
पूर्ण

DEFINE_BPF_ITER_FUNC(bpf_map_elem, काष्ठा bpf_iter_meta *meta,
		     काष्ठा bpf_map *map, व्योम *key, व्योम *value)

अटल स्थिर काष्ठा bpf_iter_reg bpf_map_elem_reg_info = अणु
	.target			= "bpf_map_elem",
	.attach_target		= bpf_iter_attach_map,
	.detach_target		= bpf_iter_detach_map,
	.show_fdinfo		= bpf_iter_map_show_fdinfo,
	.fill_link_info		= bpf_iter_map_fill_link_info,
	.ctx_arg_info_size	= 2,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__bpf_map_elem, key),
		  PTR_TO_RDONLY_BUF_OR_शून्य पूर्ण,
		अणु दुरत्व(काष्ठा bpf_iter__bpf_map_elem, value),
		  PTR_TO_RDWR_BUF_OR_शून्य पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init bpf_map_iter_init(व्योम)
अणु
	पूर्णांक ret;

	bpf_map_reg_info.ctx_arg_info[0].btf_id = *btf_bpf_map_id;
	ret = bpf_iter_reg_target(&bpf_map_reg_info);
	अगर (ret)
		वापस ret;

	वापस bpf_iter_reg_target(&bpf_map_elem_reg_info);
पूर्ण

late_initcall(bpf_map_iter_init);
