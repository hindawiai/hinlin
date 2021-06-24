<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2019 Facebook */

#समावेश <linux/bpf.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <linux/btf.h>
#समावेश <linux/filter.h>
#समावेश <linux/slab.h>
#समावेश <linux/numa.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/refcount.h>
#समावेश <linux/mutex.h>

क्रमागत bpf_काष्ठा_ops_state अणु
	BPF_STRUCT_OPS_STATE_INIT,
	BPF_STRUCT_OPS_STATE_INUSE,
	BPF_STRUCT_OPS_STATE_TOBEFREE,
पूर्ण;

#घोषणा BPF_STRUCT_OPS_COMMON_VALUE			\
	refcount_t refcnt;				\
	क्रमागत bpf_काष्ठा_ops_state state

काष्ठा bpf_काष्ठा_ops_value अणु
	BPF_STRUCT_OPS_COMMON_VALUE;
	अक्षर data[] ____cacheline_aligned_in_smp;
पूर्ण;

काष्ठा bpf_काष्ठा_ops_map अणु
	काष्ठा bpf_map map;
	स्थिर काष्ठा bpf_काष्ठा_ops *st_ops;
	/* protect map_update */
	काष्ठा mutex lock;
	/* progs has all the bpf_prog that is populated
	 * to the func ptr of the kernel's काष्ठा
	 * (in kvalue.data).
	 */
	काष्ठा bpf_prog **progs;
	/* image is a page that has all the trampolines
	 * that stores the func args beक्रमe calling the bpf_prog.
	 * A PAGE_SIZE "image" is enough to store all trampoline क्रम
	 * "progs[]".
	 */
	व्योम *image;
	/* uvalue->data stores the kernel काष्ठा
	 * (e.g. tcp_congestion_ops) that is more useful
	 * to userspace than the kvalue.  For example,
	 * the bpf_prog's id is stored instead of the kernel
	 * address of a func ptr.
	 */
	काष्ठा bpf_काष्ठा_ops_value *uvalue;
	/* kvalue.data stores the actual kernel's काष्ठा
	 * (e.g. tcp_congestion_ops) that will be
	 * रेजिस्टरed to the kernel subप्रणाली.
	 */
	काष्ठा bpf_काष्ठा_ops_value kvalue;
पूर्ण;

#घोषणा VALUE_PREFIX "bpf_struct_ops_"
#घोषणा VALUE_PREFIX_LEN (माप(VALUE_PREFIX) - 1)

/* bpf_काष्ठा_ops_##_name (e.g. bpf_काष्ठा_ops_tcp_congestion_ops) is
 * the map's value exposed to the userspace and its btf-type-id is
 * stored at the map->btf_vmlinux_value_type_id.
 *
 */
#घोषणा BPF_STRUCT_OPS_TYPE(_name)				\
बाह्य काष्ठा bpf_काष्ठा_ops bpf_##_name;			\
								\
काष्ठा bpf_काष्ठा_ops_##_name अणु						\
	BPF_STRUCT_OPS_COMMON_VALUE;				\
	काष्ठा _name data ____cacheline_aligned_in_smp;		\
पूर्ण;
#समावेश "bpf_struct_ops_types.h"
#अघोषित BPF_STRUCT_OPS_TYPE

क्रमागत अणु
#घोषणा BPF_STRUCT_OPS_TYPE(_name) BPF_STRUCT_OPS_TYPE_##_name,
#समावेश "bpf_struct_ops_types.h"
#अघोषित BPF_STRUCT_OPS_TYPE
	__NR_BPF_STRUCT_OPS_TYPE,
पूर्ण;

अटल काष्ठा bpf_काष्ठा_ops * स्थिर bpf_काष्ठा_ops[] = अणु
#घोषणा BPF_STRUCT_OPS_TYPE(_name)				\
	[BPF_STRUCT_OPS_TYPE_##_name] = &bpf_##_name,
#समावेश "bpf_struct_ops_types.h"
#अघोषित BPF_STRUCT_OPS_TYPE
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops bpf_काष्ठा_ops_verअगरier_ops = अणु
पूर्ण;

स्थिर काष्ठा bpf_prog_ops bpf_काष्ठा_ops_prog_ops = अणु
पूर्ण;

अटल स्थिर काष्ठा btf_type *module_type;

व्योम bpf_काष्ठा_ops_init(काष्ठा btf *btf, काष्ठा bpf_verअगरier_log *log)
अणु
	s32 type_id, value_id, module_id;
	स्थिर काष्ठा btf_member *member;
	काष्ठा bpf_काष्ठा_ops *st_ops;
	स्थिर काष्ठा btf_type *t;
	अक्षर value_name[128];
	स्थिर अक्षर *mname;
	u32 i, j;

	/* Ensure BTF type is emitted क्रम "struct bpf_struct_ops_##_name" */
#घोषणा BPF_STRUCT_OPS_TYPE(_name) BTF_TYPE_EMIT(काष्ठा bpf_काष्ठा_ops_##_name);
#समावेश "bpf_struct_ops_types.h"
#अघोषित BPF_STRUCT_OPS_TYPE

	module_id = btf_find_by_name_kind(btf, "module", BTF_KIND_STRUCT);
	अगर (module_id < 0) अणु
		pr_warn("Cannot find struct module in btf_vmlinux\n");
		वापस;
	पूर्ण
	module_type = btf_type_by_id(btf, module_id);

	क्रम (i = 0; i < ARRAY_SIZE(bpf_काष्ठा_ops); i++) अणु
		st_ops = bpf_काष्ठा_ops[i];

		अगर (म_माप(st_ops->name) + VALUE_PREFIX_LEN >=
		    माप(value_name)) अणु
			pr_warn("struct_ops name %s is too long\n",
				st_ops->name);
			जारी;
		पूर्ण
		प्र_लिखो(value_name, "%s%s", VALUE_PREFIX, st_ops->name);

		value_id = btf_find_by_name_kind(btf, value_name,
						 BTF_KIND_STRUCT);
		अगर (value_id < 0) अणु
			pr_warn("Cannot find struct %s in btf_vmlinux\n",
				value_name);
			जारी;
		पूर्ण

		type_id = btf_find_by_name_kind(btf, st_ops->name,
						BTF_KIND_STRUCT);
		अगर (type_id < 0) अणु
			pr_warn("Cannot find struct %s in btf_vmlinux\n",
				st_ops->name);
			जारी;
		पूर्ण
		t = btf_type_by_id(btf, type_id);
		अगर (btf_type_vlen(t) > BPF_STRUCT_OPS_MAX_NR_MEMBERS) अणु
			pr_warn("Cannot support #%u members in struct %s\n",
				btf_type_vlen(t), st_ops->name);
			जारी;
		पूर्ण

		क्रम_each_member(j, t, member) अणु
			स्थिर काष्ठा btf_type *func_proto;

			mname = btf_name_by_offset(btf, member->name_off);
			अगर (!*mname) अणु
				pr_warn("anon member in struct %s is not supported\n",
					st_ops->name);
				अवरोध;
			पूर्ण

			अगर (btf_member_bitfield_size(t, member)) अणु
				pr_warn("bit field member %s in struct %s is not supported\n",
					mname, st_ops->name);
				अवरोध;
			पूर्ण

			func_proto = btf_type_resolve_func_ptr(btf,
							       member->type,
							       शून्य);
			अगर (func_proto &&
			    btf_distill_func_proto(log, btf,
						   func_proto, mname,
						   &st_ops->func_models[j])) अणु
				pr_warn("Error in parsing func ptr %s in struct %s\n",
					mname, st_ops->name);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (j == btf_type_vlen(t)) अणु
			अगर (st_ops->init(btf)) अणु
				pr_warn("Error in init bpf_struct_ops %s\n",
					st_ops->name);
			पूर्ण अन्यथा अणु
				st_ops->type_id = type_id;
				st_ops->type = t;
				st_ops->value_id = value_id;
				st_ops->value_type = btf_type_by_id(btf,
								    value_id);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

बाह्य काष्ठा btf *btf_vmlinux;

अटल स्थिर काष्ठा bpf_काष्ठा_ops *
bpf_काष्ठा_ops_find_value(u32 value_id)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!value_id || !btf_vmlinux)
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(bpf_काष्ठा_ops); i++) अणु
		अगर (bpf_काष्ठा_ops[i]->value_id == value_id)
			वापस bpf_काष्ठा_ops[i];
	पूर्ण

	वापस शून्य;
पूर्ण

स्थिर काष्ठा bpf_काष्ठा_ops *bpf_काष्ठा_ops_find(u32 type_id)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!type_id || !btf_vmlinux)
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(bpf_काष्ठा_ops); i++) अणु
		अगर (bpf_काष्ठा_ops[i]->type_id == type_id)
			वापस bpf_काष्ठा_ops[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक bpf_काष्ठा_ops_map_get_next_key(काष्ठा bpf_map *map, व्योम *key,
					   व्योम *next_key)
अणु
	अगर (key && *(u32 *)key == 0)
		वापस -ENOENT;

	*(u32 *)next_key = 0;
	वापस 0;
पूर्ण

पूर्णांक bpf_काष्ठा_ops_map_sys_lookup_elem(काष्ठा bpf_map *map, व्योम *key,
				       व्योम *value)
अणु
	काष्ठा bpf_काष्ठा_ops_map *st_map = (काष्ठा bpf_काष्ठा_ops_map *)map;
	काष्ठा bpf_काष्ठा_ops_value *uvalue, *kvalue;
	क्रमागत bpf_काष्ठा_ops_state state;

	अगर (unlikely(*(u32 *)key != 0))
		वापस -ENOENT;

	kvalue = &st_map->kvalue;
	/* Pair with smp_store_release() during map_update */
	state = smp_load_acquire(&kvalue->state);
	अगर (state == BPF_STRUCT_OPS_STATE_INIT) अणु
		स_रखो(value, 0, map->value_size);
		वापस 0;
	पूर्ण

	/* No lock is needed.  state and refcnt करो not need
	 * to be updated together under atomic context.
	 */
	uvalue = (काष्ठा bpf_काष्ठा_ops_value *)value;
	स_नकल(uvalue, st_map->uvalue, map->value_size);
	uvalue->state = state;
	refcount_set(&uvalue->refcnt, refcount_पढ़ो(&kvalue->refcnt));

	वापस 0;
पूर्ण

अटल व्योम *bpf_काष्ठा_ops_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम bpf_काष्ठा_ops_map_put_progs(काष्ठा bpf_काष्ठा_ops_map *st_map)
अणु
	स्थिर काष्ठा btf_type *t = st_map->st_ops->type;
	u32 i;

	क्रम (i = 0; i < btf_type_vlen(t); i++) अणु
		अगर (st_map->progs[i]) अणु
			bpf_prog_put(st_map->progs[i]);
			st_map->progs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक check_zero_holes(स्थिर काष्ठा btf_type *t, व्योम *data)
अणु
	स्थिर काष्ठा btf_member *member;
	u32 i, moff, msize, prev_mend = 0;
	स्थिर काष्ठा btf_type *mtype;

	क्रम_each_member(i, t, member) अणु
		moff = btf_member_bit_offset(t, member) / 8;
		अगर (moff > prev_mend &&
		    स_प्रथम_inv(data + prev_mend, 0, moff - prev_mend))
			वापस -EINVAL;

		mtype = btf_type_by_id(btf_vmlinux, member->type);
		mtype = btf_resolve_size(btf_vmlinux, mtype, &msize);
		अगर (IS_ERR(mtype))
			वापस PTR_ERR(mtype);
		prev_mend = moff + msize;
	पूर्ण

	अगर (t->size > prev_mend &&
	    स_प्रथम_inv(data + prev_mend, 0, t->size - prev_mend))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_काष्ठा_ops_map_update_elem(काष्ठा bpf_map *map, व्योम *key,
					  व्योम *value, u64 flags)
अणु
	काष्ठा bpf_काष्ठा_ops_map *st_map = (काष्ठा bpf_काष्ठा_ops_map *)map;
	स्थिर काष्ठा bpf_काष्ठा_ops *st_ops = st_map->st_ops;
	काष्ठा bpf_काष्ठा_ops_value *uvalue, *kvalue;
	स्थिर काष्ठा btf_member *member;
	स्थिर काष्ठा btf_type *t = st_ops->type;
	काष्ठा bpf_tramp_progs *tprogs = शून्य;
	व्योम *udata, *kdata;
	पूर्णांक prog_fd, err = 0;
	व्योम *image;
	u32 i;

	अगर (flags)
		वापस -EINVAL;

	अगर (*(u32 *)key != 0)
		वापस -E2BIG;

	err = check_zero_holes(st_ops->value_type, value);
	अगर (err)
		वापस err;

	uvalue = (काष्ठा bpf_काष्ठा_ops_value *)value;
	err = check_zero_holes(t, uvalue->data);
	अगर (err)
		वापस err;

	अगर (uvalue->state || refcount_पढ़ो(&uvalue->refcnt))
		वापस -EINVAL;

	tprogs = kसुस्मृति(BPF_TRAMP_MAX, माप(*tprogs), GFP_KERNEL);
	अगर (!tprogs)
		वापस -ENOMEM;

	uvalue = (काष्ठा bpf_काष्ठा_ops_value *)st_map->uvalue;
	kvalue = (काष्ठा bpf_काष्ठा_ops_value *)&st_map->kvalue;

	mutex_lock(&st_map->lock);

	अगर (kvalue->state != BPF_STRUCT_OPS_STATE_INIT) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	स_नकल(uvalue, value, map->value_size);

	udata = &uvalue->data;
	kdata = &kvalue->data;
	image = st_map->image;

	क्रम_each_member(i, t, member) अणु
		स्थिर काष्ठा btf_type *mtype, *ptype;
		काष्ठा bpf_prog *prog;
		u32 moff;

		moff = btf_member_bit_offset(t, member) / 8;
		ptype = btf_type_resolve_ptr(btf_vmlinux, member->type, शून्य);
		अगर (ptype == module_type) अणु
			अगर (*(व्योम **)(udata + moff))
				जाओ reset_unlock;
			*(व्योम **)(kdata + moff) = BPF_MODULE_OWNER;
			जारी;
		पूर्ण

		err = st_ops->init_member(t, member, kdata, udata);
		अगर (err < 0)
			जाओ reset_unlock;

		/* The ->init_member() has handled this member */
		अगर (err > 0)
			जारी;

		/* If st_ops->init_member करोes not handle it,
		 * we will only handle func ptrs and zero-ed members
		 * here.  Reject everything अन्यथा.
		 */

		/* All non func ptr member must be 0 */
		अगर (!ptype || !btf_type_is_func_proto(ptype)) अणु
			u32 msize;

			mtype = btf_type_by_id(btf_vmlinux, member->type);
			mtype = btf_resolve_size(btf_vmlinux, mtype, &msize);
			अगर (IS_ERR(mtype)) अणु
				err = PTR_ERR(mtype);
				जाओ reset_unlock;
			पूर्ण

			अगर (स_प्रथम_inv(udata + moff, 0, msize)) अणु
				err = -EINVAL;
				जाओ reset_unlock;
			पूर्ण

			जारी;
		पूर्ण

		prog_fd = (पूर्णांक)(*(अचिन्हित दीर्घ *)(udata + moff));
		/* Similar check as the attr->attach_prog_fd */
		अगर (!prog_fd)
			जारी;

		prog = bpf_prog_get(prog_fd);
		अगर (IS_ERR(prog)) अणु
			err = PTR_ERR(prog);
			जाओ reset_unlock;
		पूर्ण
		st_map->progs[i] = prog;

		अगर (prog->type != BPF_PROG_TYPE_STRUCT_OPS ||
		    prog->aux->attach_btf_id != st_ops->type_id ||
		    prog->expected_attach_type != i) अणु
			err = -EINVAL;
			जाओ reset_unlock;
		पूर्ण

		tprogs[BPF_TRAMP_FENTRY].progs[0] = prog;
		tprogs[BPF_TRAMP_FENTRY].nr_progs = 1;
		err = arch_prepare_bpf_trampoline(शून्य, image,
						  st_map->image + PAGE_SIZE,
						  &st_ops->func_models[i], 0,
						  tprogs, शून्य);
		अगर (err < 0)
			जाओ reset_unlock;

		*(व्योम **)(kdata + moff) = image;
		image += err;

		/* put prog_id to udata */
		*(अचिन्हित दीर्घ *)(udata + moff) = prog->aux->id;
	पूर्ण

	refcount_set(&kvalue->refcnt, 1);
	bpf_map_inc(map);

	set_memory_ro((दीर्घ)st_map->image, 1);
	set_memory_x((दीर्घ)st_map->image, 1);
	err = st_ops->reg(kdata);
	अगर (likely(!err)) अणु
		/* Pair with smp_load_acquire() during lookup_elem().
		 * It ensures the above udata updates (e.g. prog->aux->id)
		 * can be seen once BPF_STRUCT_OPS_STATE_INUSE is set.
		 */
		smp_store_release(&kvalue->state, BPF_STRUCT_OPS_STATE_INUSE);
		जाओ unlock;
	पूर्ण

	/* Error during st_ops->reg().  It is very unlikely since
	 * the above init_member() should have caught it earlier
	 * beक्रमe reg().  The only possibility is अगर there was a race
	 * in रेजिस्टरing the काष्ठा_ops (under the same name) to
	 * a sub-प्रणाली through dअगरferent काष्ठा_ops's maps.
	 */
	set_memory_nx((दीर्घ)st_map->image, 1);
	set_memory_rw((दीर्घ)st_map->image, 1);
	bpf_map_put(map);

reset_unlock:
	bpf_काष्ठा_ops_map_put_progs(st_map);
	स_रखो(uvalue, 0, map->value_size);
	स_रखो(kvalue, 0, map->value_size);
unlock:
	kमुक्त(tprogs);
	mutex_unlock(&st_map->lock);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_काष्ठा_ops_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	क्रमागत bpf_काष्ठा_ops_state prev_state;
	काष्ठा bpf_काष्ठा_ops_map *st_map;

	st_map = (काष्ठा bpf_काष्ठा_ops_map *)map;
	prev_state = cmpxchg(&st_map->kvalue.state,
			     BPF_STRUCT_OPS_STATE_INUSE,
			     BPF_STRUCT_OPS_STATE_TOBEFREE);
	चयन (prev_state) अणु
	हाल BPF_STRUCT_OPS_STATE_INUSE:
		st_map->st_ops->unreg(&st_map->kvalue.data);
		अगर (refcount_dec_and_test(&st_map->kvalue.refcnt))
			bpf_map_put(map);
		वापस 0;
	हाल BPF_STRUCT_OPS_STATE_TOBEFREE:
		वापस -EINPROGRESS;
	हाल BPF_STRUCT_OPS_STATE_INIT:
		वापस -ENOENT;
	शेष:
		WARN_ON_ONCE(1);
		/* Should never happen.  Treat it as not found. */
		वापस -ENOENT;
	पूर्ण
पूर्ण

अटल व्योम bpf_काष्ठा_ops_map_seq_show_elem(काष्ठा bpf_map *map, व्योम *key,
					     काष्ठा seq_file *m)
अणु
	व्योम *value;
	पूर्णांक err;

	value = kदो_स्मृति(map->value_size, GFP_USER | __GFP_NOWARN);
	अगर (!value)
		वापस;

	err = bpf_काष्ठा_ops_map_sys_lookup_elem(map, key, value);
	अगर (!err) अणु
		btf_type_seq_show(btf_vmlinux, map->btf_vmlinux_value_type_id,
				  value, m);
		seq_माला_दो(m, "\n");
	पूर्ण

	kमुक्त(value);
पूर्ण

अटल व्योम bpf_काष्ठा_ops_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_काष्ठा_ops_map *st_map = (काष्ठा bpf_काष्ठा_ops_map *)map;

	अगर (st_map->progs)
		bpf_काष्ठा_ops_map_put_progs(st_map);
	bpf_map_area_मुक्त(st_map->progs);
	bpf_jit_मुक्त_exec(st_map->image);
	bpf_map_area_मुक्त(st_map->uvalue);
	bpf_map_area_मुक्त(st_map);
पूर्ण

अटल पूर्णांक bpf_काष्ठा_ops_map_alloc_check(जोड़ bpf_attr *attr)
अणु
	अगर (attr->key_size != माप(अचिन्हित पूर्णांक) || attr->max_entries != 1 ||
	    attr->map_flags || !attr->btf_vmlinux_value_type_id)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा bpf_map *bpf_काष्ठा_ops_map_alloc(जोड़ bpf_attr *attr)
अणु
	स्थिर काष्ठा bpf_काष्ठा_ops *st_ops;
	माप_प्रकार st_map_size;
	काष्ठा bpf_काष्ठा_ops_map *st_map;
	स्थिर काष्ठा btf_type *t, *vt;
	काष्ठा bpf_map *map;

	अगर (!bpf_capable())
		वापस ERR_PTR(-EPERM);

	st_ops = bpf_काष्ठा_ops_find_value(attr->btf_vmlinux_value_type_id);
	अगर (!st_ops)
		वापस ERR_PTR(-ENOTSUPP);

	vt = st_ops->value_type;
	अगर (attr->value_size != vt->size)
		वापस ERR_PTR(-EINVAL);

	t = st_ops->type;

	st_map_size = माप(*st_map) +
		/* kvalue stores the
		 * काष्ठा bpf_काष्ठा_ops_tcp_congestions_ops
		 */
		(vt->size - माप(काष्ठा bpf_काष्ठा_ops_value));

	st_map = bpf_map_area_alloc(st_map_size, NUMA_NO_NODE);
	अगर (!st_map)
		वापस ERR_PTR(-ENOMEM);

	st_map->st_ops = st_ops;
	map = &st_map->map;

	st_map->uvalue = bpf_map_area_alloc(vt->size, NUMA_NO_NODE);
	st_map->progs =
		bpf_map_area_alloc(btf_type_vlen(t) * माप(काष्ठा bpf_prog *),
				   NUMA_NO_NODE);
	st_map->image = bpf_jit_alloc_exec(PAGE_SIZE);
	अगर (!st_map->uvalue || !st_map->progs || !st_map->image) अणु
		bpf_काष्ठा_ops_map_मुक्त(map);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mutex_init(&st_map->lock);
	set_vm_flush_reset_perms(st_map->image);
	bpf_map_init_from_attr(map, attr);

	वापस map;
पूर्ण

अटल पूर्णांक bpf_काष्ठा_ops_map_btf_id;
स्थिर काष्ठा bpf_map_ops bpf_काष्ठा_ops_map_ops = अणु
	.map_alloc_check = bpf_काष्ठा_ops_map_alloc_check,
	.map_alloc = bpf_काष्ठा_ops_map_alloc,
	.map_मुक्त = bpf_काष्ठा_ops_map_मुक्त,
	.map_get_next_key = bpf_काष्ठा_ops_map_get_next_key,
	.map_lookup_elem = bpf_काष्ठा_ops_map_lookup_elem,
	.map_delete_elem = bpf_काष्ठा_ops_map_delete_elem,
	.map_update_elem = bpf_काष्ठा_ops_map_update_elem,
	.map_seq_show_elem = bpf_काष्ठा_ops_map_seq_show_elem,
	.map_btf_name = "bpf_struct_ops_map",
	.map_btf_id = &bpf_काष्ठा_ops_map_btf_id,
पूर्ण;

/* "const void *" because some subप्रणाली is
 * passing a स्थिर (e.g. स्थिर काष्ठा tcp_congestion_ops *)
 */
bool bpf_काष्ठा_ops_get(स्थिर व्योम *kdata)
अणु
	काष्ठा bpf_काष्ठा_ops_value *kvalue;

	kvalue = container_of(kdata, काष्ठा bpf_काष्ठा_ops_value, data);

	वापस refcount_inc_not_zero(&kvalue->refcnt);
पूर्ण

व्योम bpf_काष्ठा_ops_put(स्थिर व्योम *kdata)
अणु
	काष्ठा bpf_काष्ठा_ops_value *kvalue;

	kvalue = container_of(kdata, काष्ठा bpf_काष्ठा_ops_value, data);
	अगर (refcount_dec_and_test(&kvalue->refcnt)) अणु
		काष्ठा bpf_काष्ठा_ops_map *st_map;

		st_map = container_of(kvalue, काष्ठा bpf_काष्ठा_ops_map,
				      kvalue);
		bpf_map_put(&st_map->map);
	पूर्ण
पूर्ण
