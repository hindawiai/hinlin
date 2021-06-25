<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Functions to manage eBPF programs attached to cgroups
 *
 * Copyright (c) 2016 Daniel Mack
 */

#समावेश <linux/kernel.h>
#समावेश <linux/atomic.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/filter.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf-cgroup.h>
#समावेश <net/sock.h>
#समावेश <net/bpf_sk_storage.h>

#समावेश "../cgroup/cgroup-internal.h"

DEFINE_STATIC_KEY_ARRAY_FALSE(cgroup_bpf_enabled_key, MAX_BPF_ATTACH_TYPE);
EXPORT_SYMBOL(cgroup_bpf_enabled_key);

व्योम cgroup_bpf_offline(काष्ठा cgroup *cgrp)
अणु
	cgroup_get(cgrp);
	percpu_ref_समाप्त(&cgrp->bpf.refcnt);
पूर्ण

अटल व्योम bpf_cgroup_storages_मुक्त(काष्ठा bpf_cgroup_storage *storages[])
अणु
	क्रमागत bpf_cgroup_storage_type stype;

	क्रम_each_cgroup_storage_type(stype)
		bpf_cgroup_storage_मुक्त(storages[stype]);
पूर्ण

अटल पूर्णांक bpf_cgroup_storages_alloc(काष्ठा bpf_cgroup_storage *storages[],
				     काष्ठा bpf_cgroup_storage *new_storages[],
				     क्रमागत bpf_attach_type type,
				     काष्ठा bpf_prog *prog,
				     काष्ठा cgroup *cgrp)
अणु
	क्रमागत bpf_cgroup_storage_type stype;
	काष्ठा bpf_cgroup_storage_key key;
	काष्ठा bpf_map *map;

	key.cgroup_inode_id = cgroup_id(cgrp);
	key.attach_type = type;

	क्रम_each_cgroup_storage_type(stype) अणु
		map = prog->aux->cgroup_storage[stype];
		अगर (!map)
			जारी;

		storages[stype] = cgroup_storage_lookup((व्योम *)map, &key, false);
		अगर (storages[stype])
			जारी;

		storages[stype] = bpf_cgroup_storage_alloc(prog, stype);
		अगर (IS_ERR(storages[stype])) अणु
			bpf_cgroup_storages_मुक्त(new_storages);
			वापस -ENOMEM;
		पूर्ण

		new_storages[stype] = storages[stype];
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bpf_cgroup_storages_assign(काष्ठा bpf_cgroup_storage *dst[],
				       काष्ठा bpf_cgroup_storage *src[])
अणु
	क्रमागत bpf_cgroup_storage_type stype;

	क्रम_each_cgroup_storage_type(stype)
		dst[stype] = src[stype];
पूर्ण

अटल व्योम bpf_cgroup_storages_link(काष्ठा bpf_cgroup_storage *storages[],
				     काष्ठा cgroup *cgrp,
				     क्रमागत bpf_attach_type attach_type)
अणु
	क्रमागत bpf_cgroup_storage_type stype;

	क्रम_each_cgroup_storage_type(stype)
		bpf_cgroup_storage_link(storages[stype], cgrp, attach_type);
पूर्ण

/* Called when bpf_cgroup_link is स्वतः-detached from dying cgroup.
 * It drops cgroup and bpf_prog refcounts, and marks bpf_link as defunct. It
 * करोesn't free link memory, which will eventually be done by bpf_link's
 * release() callback, when its last FD is बंदd.
 */
अटल व्योम bpf_cgroup_link_स्वतः_detach(काष्ठा bpf_cgroup_link *link)
अणु
	cgroup_put(link->cgroup);
	link->cgroup = शून्य;
पूर्ण

/**
 * cgroup_bpf_release() - put references of all bpf programs and
 *                        release all cgroup bpf data
 * @work: work काष्ठाure embedded पूर्णांकo the cgroup to modअगरy
 */
अटल व्योम cgroup_bpf_release(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cgroup *p, *cgrp = container_of(work, काष्ठा cgroup,
					       bpf.release_work);
	काष्ठा bpf_prog_array *old_array;
	काष्ठा list_head *storages = &cgrp->bpf.storages;
	काष्ठा bpf_cgroup_storage *storage, *sपंचांगp;

	अचिन्हित पूर्णांक type;

	mutex_lock(&cgroup_mutex);

	क्रम (type = 0; type < ARRAY_SIZE(cgrp->bpf.progs); type++) अणु
		काष्ठा list_head *progs = &cgrp->bpf.progs[type];
		काष्ठा bpf_prog_list *pl, *plपंचांगp;

		list_क्रम_each_entry_safe(pl, plपंचांगp, progs, node) अणु
			list_del(&pl->node);
			अगर (pl->prog)
				bpf_prog_put(pl->prog);
			अगर (pl->link)
				bpf_cgroup_link_स्वतः_detach(pl->link);
			kमुक्त(pl);
			अटल_branch_dec(&cgroup_bpf_enabled_key[type]);
		पूर्ण
		old_array = rcu_dereference_रक्षित(
				cgrp->bpf.effective[type],
				lockdep_is_held(&cgroup_mutex));
		bpf_prog_array_मुक्त(old_array);
	पूर्ण

	list_क्रम_each_entry_safe(storage, sपंचांगp, storages, list_cg) अणु
		bpf_cgroup_storage_unlink(storage);
		bpf_cgroup_storage_मुक्त(storage);
	पूर्ण

	mutex_unlock(&cgroup_mutex);

	क्रम (p = cgroup_parent(cgrp); p; p = cgroup_parent(p))
		cgroup_bpf_put(p);

	percpu_ref_निकास(&cgrp->bpf.refcnt);
	cgroup_put(cgrp);
पूर्ण

/**
 * cgroup_bpf_release_fn() - callback used to schedule releasing
 *                           of bpf cgroup data
 * @ref: percpu ref counter काष्ठाure
 */
अटल व्योम cgroup_bpf_release_fn(काष्ठा percpu_ref *ref)
अणु
	काष्ठा cgroup *cgrp = container_of(ref, काष्ठा cgroup, bpf.refcnt);

	INIT_WORK(&cgrp->bpf.release_work, cgroup_bpf_release);
	queue_work(प्रणाली_wq, &cgrp->bpf.release_work);
पूर्ण

/* Get underlying bpf_prog of bpf_prog_list entry, regardless अगर it's through
 * link or direct prog.
 */
अटल काष्ठा bpf_prog *prog_list_prog(काष्ठा bpf_prog_list *pl)
अणु
	अगर (pl->prog)
		वापस pl->prog;
	अगर (pl->link)
		वापस pl->link->link.prog;
	वापस शून्य;
पूर्ण

/* count number of elements in the list.
 * it's slow but the list cannot be दीर्घ
 */
अटल u32 prog_list_length(काष्ठा list_head *head)
अणु
	काष्ठा bpf_prog_list *pl;
	u32 cnt = 0;

	list_क्रम_each_entry(pl, head, node) अणु
		अगर (!prog_list_prog(pl))
			जारी;
		cnt++;
	पूर्ण
	वापस cnt;
पूर्ण

/* अगर parent has non-overridable prog attached,
 * disallow attaching new programs to the descendent cgroup.
 * अगर parent has overridable or multi-prog, allow attaching
 */
अटल bool hierarchy_allows_attach(काष्ठा cgroup *cgrp,
				    क्रमागत bpf_attach_type type)
अणु
	काष्ठा cgroup *p;

	p = cgroup_parent(cgrp);
	अगर (!p)
		वापस true;
	करो अणु
		u32 flags = p->bpf.flags[type];
		u32 cnt;

		अगर (flags & BPF_F_ALLOW_MULTI)
			वापस true;
		cnt = prog_list_length(&p->bpf.progs[type]);
		WARN_ON_ONCE(cnt > 1);
		अगर (cnt == 1)
			वापस !!(flags & BPF_F_ALLOW_OVERRIDE);
		p = cgroup_parent(p);
	पूर्ण जबतक (p);
	वापस true;
पूर्ण

/* compute a chain of effective programs क्रम a given cgroup:
 * start from the list of programs in this cgroup and add
 * all parent programs.
 * Note that parent's F_ALLOW_OVERRIDE-type program is yielding
 * to programs in this cgroup
 */
अटल पूर्णांक compute_effective_progs(काष्ठा cgroup *cgrp,
				   क्रमागत bpf_attach_type type,
				   काष्ठा bpf_prog_array **array)
अणु
	काष्ठा bpf_prog_array_item *item;
	काष्ठा bpf_prog_array *progs;
	काष्ठा bpf_prog_list *pl;
	काष्ठा cgroup *p = cgrp;
	पूर्णांक cnt = 0;

	/* count number of effective programs by walking parents */
	करो अणु
		अगर (cnt == 0 || (p->bpf.flags[type] & BPF_F_ALLOW_MULTI))
			cnt += prog_list_length(&p->bpf.progs[type]);
		p = cgroup_parent(p);
	पूर्ण जबतक (p);

	progs = bpf_prog_array_alloc(cnt, GFP_KERNEL);
	अगर (!progs)
		वापस -ENOMEM;

	/* populate the array with effective progs */
	cnt = 0;
	p = cgrp;
	करो अणु
		अगर (cnt > 0 && !(p->bpf.flags[type] & BPF_F_ALLOW_MULTI))
			जारी;

		list_क्रम_each_entry(pl, &p->bpf.progs[type], node) अणु
			अगर (!prog_list_prog(pl))
				जारी;

			item = &progs->items[cnt];
			item->prog = prog_list_prog(pl);
			bpf_cgroup_storages_assign(item->cgroup_storage,
						   pl->storage);
			cnt++;
		पूर्ण
	पूर्ण जबतक ((p = cgroup_parent(p)));

	*array = progs;
	वापस 0;
पूर्ण

अटल व्योम activate_effective_progs(काष्ठा cgroup *cgrp,
				     क्रमागत bpf_attach_type type,
				     काष्ठा bpf_prog_array *old_array)
अणु
	old_array = rcu_replace_poपूर्णांकer(cgrp->bpf.effective[type], old_array,
					lockdep_is_held(&cgroup_mutex));
	/* मुक्त prog array after grace period, since __cgroup_bpf_run_*()
	 * might be still walking the array
	 */
	bpf_prog_array_मुक्त(old_array);
पूर्ण

/**
 * cgroup_bpf_inherit() - inherit effective programs from parent
 * @cgrp: the cgroup to modअगरy
 */
पूर्णांक cgroup_bpf_inherit(काष्ठा cgroup *cgrp)
अणु
/* has to use marco instead of स्थिर पूर्णांक, since compiler thinks
 * that array below is variable length
 */
#घोषणा	NR ARRAY_SIZE(cgrp->bpf.effective)
	काष्ठा bpf_prog_array *arrays[NR] = अणुपूर्ण;
	काष्ठा cgroup *p;
	पूर्णांक ret, i;

	ret = percpu_ref_init(&cgrp->bpf.refcnt, cgroup_bpf_release_fn, 0,
			      GFP_KERNEL);
	अगर (ret)
		वापस ret;

	क्रम (p = cgroup_parent(cgrp); p; p = cgroup_parent(p))
		cgroup_bpf_get(p);

	क्रम (i = 0; i < NR; i++)
		INIT_LIST_HEAD(&cgrp->bpf.progs[i]);

	INIT_LIST_HEAD(&cgrp->bpf.storages);

	क्रम (i = 0; i < NR; i++)
		अगर (compute_effective_progs(cgrp, i, &arrays[i]))
			जाओ cleanup;

	क्रम (i = 0; i < NR; i++)
		activate_effective_progs(cgrp, i, arrays[i]);

	वापस 0;
cleanup:
	क्रम (i = 0; i < NR; i++)
		bpf_prog_array_मुक्त(arrays[i]);

	क्रम (p = cgroup_parent(cgrp); p; p = cgroup_parent(p))
		cgroup_bpf_put(p);

	percpu_ref_निकास(&cgrp->bpf.refcnt);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक update_effective_progs(काष्ठा cgroup *cgrp,
				  क्रमागत bpf_attach_type type)
अणु
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक err;

	/* allocate and recompute effective prog arrays */
	css_क्रम_each_descendant_pre(css, &cgrp->self) अणु
		काष्ठा cgroup *desc = container_of(css, काष्ठा cgroup, self);

		अगर (percpu_ref_is_zero(&desc->bpf.refcnt))
			जारी;

		err = compute_effective_progs(desc, type, &desc->bpf.inactive);
		अगर (err)
			जाओ cleanup;
	पूर्ण

	/* all allocations were successful. Activate all prog arrays */
	css_क्रम_each_descendant_pre(css, &cgrp->self) अणु
		काष्ठा cgroup *desc = container_of(css, काष्ठा cgroup, self);

		अगर (percpu_ref_is_zero(&desc->bpf.refcnt)) अणु
			अगर (unlikely(desc->bpf.inactive)) अणु
				bpf_prog_array_मुक्त(desc->bpf.inactive);
				desc->bpf.inactive = शून्य;
			पूर्ण
			जारी;
		पूर्ण

		activate_effective_progs(desc, type, desc->bpf.inactive);
		desc->bpf.inactive = शून्य;
	पूर्ण

	वापस 0;

cleanup:
	/* oom जबतक computing effective. Free all computed effective arrays
	 * since they were not activated
	 */
	css_क्रम_each_descendant_pre(css, &cgrp->self) अणु
		काष्ठा cgroup *desc = container_of(css, काष्ठा cgroup, self);

		bpf_prog_array_मुक्त(desc->bpf.inactive);
		desc->bpf.inactive = शून्य;
	पूर्ण

	वापस err;
पूर्ण

#घोषणा BPF_CGROUP_MAX_PROGS 64

अटल काष्ठा bpf_prog_list *find_attach_entry(काष्ठा list_head *progs,
					       काष्ठा bpf_prog *prog,
					       काष्ठा bpf_cgroup_link *link,
					       काष्ठा bpf_prog *replace_prog,
					       bool allow_multi)
अणु
	काष्ठा bpf_prog_list *pl;

	/* single-attach हाल */
	अगर (!allow_multi) अणु
		अगर (list_empty(progs))
			वापस शून्य;
		वापस list_first_entry(progs, typeof(*pl), node);
	पूर्ण

	list_क्रम_each_entry(pl, progs, node) अणु
		अगर (prog && pl->prog == prog && prog != replace_prog)
			/* disallow attaching the same prog twice */
			वापस ERR_PTR(-EINVAL);
		अगर (link && pl->link == link)
			/* disallow attaching the same link twice */
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* direct prog multi-attach w/ replacement हाल */
	अगर (replace_prog) अणु
		list_क्रम_each_entry(pl, progs, node) अणु
			अगर (pl->prog == replace_prog)
				/* a match found */
				वापस pl;
		पूर्ण
		/* prog to replace not found क्रम cgroup */
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __cgroup_bpf_attach() - Attach the program or the link to a cgroup, and
 *                         propagate the change to descendants
 * @cgrp: The cgroup which descendants to traverse
 * @prog: A program to attach
 * @link: A link to attach
 * @replace_prog: Previously attached program to replace अगर BPF_F_REPLACE is set
 * @type: Type of attach operation
 * @flags: Option flags
 *
 * Exactly one of @prog or @link can be non-null.
 * Must be called with cgroup_mutex held.
 */
पूर्णांक __cgroup_bpf_attach(काष्ठा cgroup *cgrp,
			काष्ठा bpf_prog *prog, काष्ठा bpf_prog *replace_prog,
			काष्ठा bpf_cgroup_link *link,
			क्रमागत bpf_attach_type type, u32 flags)
अणु
	u32 saved_flags = (flags & (BPF_F_ALLOW_OVERRIDE | BPF_F_ALLOW_MULTI));
	काष्ठा list_head *progs = &cgrp->bpf.progs[type];
	काष्ठा bpf_prog *old_prog = शून्य;
	काष्ठा bpf_cgroup_storage *storage[MAX_BPF_CGROUP_STORAGE_TYPE] = अणुपूर्ण;
	काष्ठा bpf_cgroup_storage *new_storage[MAX_BPF_CGROUP_STORAGE_TYPE] = अणुपूर्ण;
	काष्ठा bpf_prog_list *pl;
	पूर्णांक err;

	अगर (((flags & BPF_F_ALLOW_OVERRIDE) && (flags & BPF_F_ALLOW_MULTI)) ||
	    ((flags & BPF_F_REPLACE) && !(flags & BPF_F_ALLOW_MULTI)))
		/* invalid combination */
		वापस -EINVAL;
	अगर (link && (prog || replace_prog))
		/* only either link or prog/replace_prog can be specअगरied */
		वापस -EINVAL;
	अगर (!!replace_prog != !!(flags & BPF_F_REPLACE))
		/* replace_prog implies BPF_F_REPLACE, and vice versa */
		वापस -EINVAL;

	अगर (!hierarchy_allows_attach(cgrp, type))
		वापस -EPERM;

	अगर (!list_empty(progs) && cgrp->bpf.flags[type] != saved_flags)
		/* Disallow attaching non-overridable on top
		 * of existing overridable in this cgroup.
		 * Disallow attaching multi-prog अगर overridable or none
		 */
		वापस -EPERM;

	अगर (prog_list_length(progs) >= BPF_CGROUP_MAX_PROGS)
		वापस -E2BIG;

	pl = find_attach_entry(progs, prog, link, replace_prog,
			       flags & BPF_F_ALLOW_MULTI);
	अगर (IS_ERR(pl))
		वापस PTR_ERR(pl);

	अगर (bpf_cgroup_storages_alloc(storage, new_storage, type,
				      prog ? : link->link.prog, cgrp))
		वापस -ENOMEM;

	अगर (pl) अणु
		old_prog = pl->prog;
	पूर्ण अन्यथा अणु
		pl = kदो_स्मृति(माप(*pl), GFP_KERNEL);
		अगर (!pl) अणु
			bpf_cgroup_storages_मुक्त(new_storage);
			वापस -ENOMEM;
		पूर्ण
		list_add_tail(&pl->node, progs);
	पूर्ण

	pl->prog = prog;
	pl->link = link;
	bpf_cgroup_storages_assign(pl->storage, storage);
	cgrp->bpf.flags[type] = saved_flags;

	err = update_effective_progs(cgrp, type);
	अगर (err)
		जाओ cleanup;

	अगर (old_prog)
		bpf_prog_put(old_prog);
	अन्यथा
		अटल_branch_inc(&cgroup_bpf_enabled_key[type]);
	bpf_cgroup_storages_link(new_storage, cgrp, type);
	वापस 0;

cleanup:
	अगर (old_prog) अणु
		pl->prog = old_prog;
		pl->link = शून्य;
	पूर्ण
	bpf_cgroup_storages_मुक्त(new_storage);
	अगर (!old_prog) अणु
		list_del(&pl->node);
		kमुक्त(pl);
	पूर्ण
	वापस err;
पूर्ण

/* Swap updated BPF program क्रम given link in effective program arrays across
 * all descendant cgroups. This function is guaranteed to succeed.
 */
अटल व्योम replace_effective_prog(काष्ठा cgroup *cgrp,
				   क्रमागत bpf_attach_type type,
				   काष्ठा bpf_cgroup_link *link)
अणु
	काष्ठा bpf_prog_array_item *item;
	काष्ठा cgroup_subsys_state *css;
	काष्ठा bpf_prog_array *progs;
	काष्ठा bpf_prog_list *pl;
	काष्ठा list_head *head;
	काष्ठा cgroup *cg;
	पूर्णांक pos;

	css_क्रम_each_descendant_pre(css, &cgrp->self) अणु
		काष्ठा cgroup *desc = container_of(css, काष्ठा cgroup, self);

		अगर (percpu_ref_is_zero(&desc->bpf.refcnt))
			जारी;

		/* find position of link in effective progs array */
		क्रम (pos = 0, cg = desc; cg; cg = cgroup_parent(cg)) अणु
			अगर (pos && !(cg->bpf.flags[type] & BPF_F_ALLOW_MULTI))
				जारी;

			head = &cg->bpf.progs[type];
			list_क्रम_each_entry(pl, head, node) अणु
				अगर (!prog_list_prog(pl))
					जारी;
				अगर (pl->link == link)
					जाओ found;
				pos++;
			पूर्ण
		पूर्ण
found:
		BUG_ON(!cg);
		progs = rcu_dereference_रक्षित(
				desc->bpf.effective[type],
				lockdep_is_held(&cgroup_mutex));
		item = &progs->items[pos];
		WRITE_ONCE(item->prog, link->link.prog);
	पूर्ण
पूर्ण

/**
 * __cgroup_bpf_replace() - Replace link's program and propagate the change
 *                          to descendants
 * @cgrp: The cgroup which descendants to traverse
 * @link: A link क्रम which to replace BPF program
 * @type: Type of attach operation
 *
 * Must be called with cgroup_mutex held.
 */
अटल पूर्णांक __cgroup_bpf_replace(काष्ठा cgroup *cgrp,
				काष्ठा bpf_cgroup_link *link,
				काष्ठा bpf_prog *new_prog)
अणु
	काष्ठा list_head *progs = &cgrp->bpf.progs[link->type];
	काष्ठा bpf_prog *old_prog;
	काष्ठा bpf_prog_list *pl;
	bool found = false;

	अगर (link->link.prog->type != new_prog->type)
		वापस -EINVAL;

	list_क्रम_each_entry(pl, progs, node) अणु
		अगर (pl->link == link) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		वापस -ENOENT;

	old_prog = xchg(&link->link.prog, new_prog);
	replace_effective_prog(cgrp, link->type, link);
	bpf_prog_put(old_prog);
	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_bpf_replace(काष्ठा bpf_link *link, काष्ठा bpf_prog *new_prog,
			      काष्ठा bpf_prog *old_prog)
अणु
	काष्ठा bpf_cgroup_link *cg_link;
	पूर्णांक ret;

	cg_link = container_of(link, काष्ठा bpf_cgroup_link, link);

	mutex_lock(&cgroup_mutex);
	/* link might have been स्वतः-released by dying cgroup, so fail */
	अगर (!cg_link->cgroup) अणु
		ret = -ENOLINK;
		जाओ out_unlock;
	पूर्ण
	अगर (old_prog && link->prog != old_prog) अणु
		ret = -EPERM;
		जाओ out_unlock;
	पूर्ण
	ret = __cgroup_bpf_replace(cg_link->cgroup, cg_link, new_prog);
out_unlock:
	mutex_unlock(&cgroup_mutex);
	वापस ret;
पूर्ण

अटल काष्ठा bpf_prog_list *find_detach_entry(काष्ठा list_head *progs,
					       काष्ठा bpf_prog *prog,
					       काष्ठा bpf_cgroup_link *link,
					       bool allow_multi)
अणु
	काष्ठा bpf_prog_list *pl;

	अगर (!allow_multi) अणु
		अगर (list_empty(progs))
			/* report error when trying to detach and nothing is attached */
			वापस ERR_PTR(-ENOENT);

		/* to मुख्यtain backward compatibility NONE and OVERRIDE cgroups
		 * allow detaching with invalid FD (prog==शून्य) in legacy mode
		 */
		वापस list_first_entry(progs, typeof(*pl), node);
	पूर्ण

	अगर (!prog && !link)
		/* to detach MULTI prog the user has to specअगरy valid FD
		 * of the program or link to be detached
		 */
		वापस ERR_PTR(-EINVAL);

	/* find the prog or link and detach it */
	list_क्रम_each_entry(pl, progs, node) अणु
		अगर (pl->prog == prog && pl->link == link)
			वापस pl;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

/**
 * __cgroup_bpf_detach() - Detach the program or link from a cgroup, and
 *                         propagate the change to descendants
 * @cgrp: The cgroup which descendants to traverse
 * @prog: A program to detach or शून्य
 * @prog: A link to detach or शून्य
 * @type: Type of detach operation
 *
 * At most one of @prog or @link can be non-शून्य.
 * Must be called with cgroup_mutex held.
 */
पूर्णांक __cgroup_bpf_detach(काष्ठा cgroup *cgrp, काष्ठा bpf_prog *prog,
			काष्ठा bpf_cgroup_link *link, क्रमागत bpf_attach_type type)
अणु
	काष्ठा list_head *progs = &cgrp->bpf.progs[type];
	u32 flags = cgrp->bpf.flags[type];
	काष्ठा bpf_prog_list *pl;
	काष्ठा bpf_prog *old_prog;
	पूर्णांक err;

	अगर (prog && link)
		/* only one of prog or link can be specअगरied */
		वापस -EINVAL;

	pl = find_detach_entry(progs, prog, link, flags & BPF_F_ALLOW_MULTI);
	अगर (IS_ERR(pl))
		वापस PTR_ERR(pl);

	/* mark it deleted, so it's ignored जबतक recomputing effective */
	old_prog = pl->prog;
	pl->prog = शून्य;
	pl->link = शून्य;

	err = update_effective_progs(cgrp, type);
	अगर (err)
		जाओ cleanup;

	/* now can actually delete it from this cgroup list */
	list_del(&pl->node);
	kमुक्त(pl);
	अगर (list_empty(progs))
		/* last program was detached, reset flags to zero */
		cgrp->bpf.flags[type] = 0;
	अगर (old_prog)
		bpf_prog_put(old_prog);
	अटल_branch_dec(&cgroup_bpf_enabled_key[type]);
	वापस 0;

cleanup:
	/* restore back prog or link */
	pl->prog = old_prog;
	pl->link = link;
	वापस err;
पूर्ण

/* Must be called with cgroup_mutex held to aव्योम races. */
पूर्णांक __cgroup_bpf_query(काष्ठा cgroup *cgrp, स्थिर जोड़ bpf_attr *attr,
		       जोड़ bpf_attr __user *uattr)
अणु
	__u32 __user *prog_ids = u64_to_user_ptr(attr->query.prog_ids);
	क्रमागत bpf_attach_type type = attr->query.attach_type;
	काष्ठा list_head *progs = &cgrp->bpf.progs[type];
	u32 flags = cgrp->bpf.flags[type];
	काष्ठा bpf_prog_array *effective;
	काष्ठा bpf_prog *prog;
	पूर्णांक cnt, ret = 0, i;

	effective = rcu_dereference_रक्षित(cgrp->bpf.effective[type],
					      lockdep_is_held(&cgroup_mutex));

	अगर (attr->query.query_flags & BPF_F_QUERY_EFFECTIVE)
		cnt = bpf_prog_array_length(effective);
	अन्यथा
		cnt = prog_list_length(progs);

	अगर (copy_to_user(&uattr->query.attach_flags, &flags, माप(flags)))
		वापस -EFAULT;
	अगर (copy_to_user(&uattr->query.prog_cnt, &cnt, माप(cnt)))
		वापस -EFAULT;
	अगर (attr->query.prog_cnt == 0 || !prog_ids || !cnt)
		/* वापस early अगर user requested only program count + flags */
		वापस 0;
	अगर (attr->query.prog_cnt < cnt) अणु
		cnt = attr->query.prog_cnt;
		ret = -ENOSPC;
	पूर्ण

	अगर (attr->query.query_flags & BPF_F_QUERY_EFFECTIVE) अणु
		वापस bpf_prog_array_copy_to_user(effective, prog_ids, cnt);
	पूर्ण अन्यथा अणु
		काष्ठा bpf_prog_list *pl;
		u32 id;

		i = 0;
		list_क्रम_each_entry(pl, progs, node) अणु
			prog = prog_list_prog(pl);
			id = prog->aux->id;
			अगर (copy_to_user(prog_ids + i, &id, माप(id)))
				वापस -EFAULT;
			अगर (++i == cnt)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक cgroup_bpf_prog_attach(स्थिर जोड़ bpf_attr *attr,
			   क्रमागत bpf_prog_type ptype, काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *replace_prog = शून्य;
	काष्ठा cgroup *cgrp;
	पूर्णांक ret;

	cgrp = cgroup_get_from_fd(attr->target_fd);
	अगर (IS_ERR(cgrp))
		वापस PTR_ERR(cgrp);

	अगर ((attr->attach_flags & BPF_F_ALLOW_MULTI) &&
	    (attr->attach_flags & BPF_F_REPLACE)) अणु
		replace_prog = bpf_prog_get_type(attr->replace_bpf_fd, ptype);
		अगर (IS_ERR(replace_prog)) अणु
			cgroup_put(cgrp);
			वापस PTR_ERR(replace_prog);
		पूर्ण
	पूर्ण

	ret = cgroup_bpf_attach(cgrp, prog, replace_prog, शून्य,
				attr->attach_type, attr->attach_flags);

	अगर (replace_prog)
		bpf_prog_put(replace_prog);
	cgroup_put(cgrp);
	वापस ret;
पूर्ण

पूर्णांक cgroup_bpf_prog_detach(स्थिर जोड़ bpf_attr *attr, क्रमागत bpf_prog_type ptype)
अणु
	काष्ठा bpf_prog *prog;
	काष्ठा cgroup *cgrp;
	पूर्णांक ret;

	cgrp = cgroup_get_from_fd(attr->target_fd);
	अगर (IS_ERR(cgrp))
		वापस PTR_ERR(cgrp);

	prog = bpf_prog_get_type(attr->attach_bpf_fd, ptype);
	अगर (IS_ERR(prog))
		prog = शून्य;

	ret = cgroup_bpf_detach(cgrp, prog, attr->attach_type);
	अगर (prog)
		bpf_prog_put(prog);

	cgroup_put(cgrp);
	वापस ret;
पूर्ण

अटल व्योम bpf_cgroup_link_release(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_cgroup_link *cg_link =
		container_of(link, काष्ठा bpf_cgroup_link, link);
	काष्ठा cgroup *cg;

	/* link might have been स्वतः-detached by dying cgroup alपढ़ोy,
	 * in that हाल our work is करोne here
	 */
	अगर (!cg_link->cgroup)
		वापस;

	mutex_lock(&cgroup_mutex);

	/* re-check cgroup under lock again */
	अगर (!cg_link->cgroup) अणु
		mutex_unlock(&cgroup_mutex);
		वापस;
	पूर्ण

	WARN_ON(__cgroup_bpf_detach(cg_link->cgroup, शून्य, cg_link,
				    cg_link->type));

	cg = cg_link->cgroup;
	cg_link->cgroup = शून्य;

	mutex_unlock(&cgroup_mutex);

	cgroup_put(cg);
पूर्ण

अटल व्योम bpf_cgroup_link_dealloc(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_cgroup_link *cg_link =
		container_of(link, काष्ठा bpf_cgroup_link, link);

	kमुक्त(cg_link);
पूर्ण

अटल पूर्णांक bpf_cgroup_link_detach(काष्ठा bpf_link *link)
अणु
	bpf_cgroup_link_release(link);

	वापस 0;
पूर्ण

अटल व्योम bpf_cgroup_link_show_fdinfo(स्थिर काष्ठा bpf_link *link,
					काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_cgroup_link *cg_link =
		container_of(link, काष्ठा bpf_cgroup_link, link);
	u64 cg_id = 0;

	mutex_lock(&cgroup_mutex);
	अगर (cg_link->cgroup)
		cg_id = cgroup_id(cg_link->cgroup);
	mutex_unlock(&cgroup_mutex);

	seq_म_लिखो(seq,
		   "cgroup_id:\t%llu\n"
		   "attach_type:\t%d\n",
		   cg_id,
		   cg_link->type);
पूर्ण

अटल पूर्णांक bpf_cgroup_link_fill_link_info(स्थिर काष्ठा bpf_link *link,
					  काष्ठा bpf_link_info *info)
अणु
	काष्ठा bpf_cgroup_link *cg_link =
		container_of(link, काष्ठा bpf_cgroup_link, link);
	u64 cg_id = 0;

	mutex_lock(&cgroup_mutex);
	अगर (cg_link->cgroup)
		cg_id = cgroup_id(cg_link->cgroup);
	mutex_unlock(&cgroup_mutex);

	info->cgroup.cgroup_id = cg_id;
	info->cgroup.attach_type = cg_link->type;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_link_ops bpf_cgroup_link_lops = अणु
	.release = bpf_cgroup_link_release,
	.dealloc = bpf_cgroup_link_dealloc,
	.detach = bpf_cgroup_link_detach,
	.update_prog = cgroup_bpf_replace,
	.show_fdinfo = bpf_cgroup_link_show_fdinfo,
	.fill_link_info = bpf_cgroup_link_fill_link_info,
पूर्ण;

पूर्णांक cgroup_bpf_link_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_link_primer link_primer;
	काष्ठा bpf_cgroup_link *link;
	काष्ठा cgroup *cgrp;
	पूर्णांक err;

	अगर (attr->link_create.flags)
		वापस -EINVAL;

	cgrp = cgroup_get_from_fd(attr->link_create.target_fd);
	अगर (IS_ERR(cgrp))
		वापस PTR_ERR(cgrp);

	link = kzalloc(माप(*link), GFP_USER);
	अगर (!link) अणु
		err = -ENOMEM;
		जाओ out_put_cgroup;
	पूर्ण
	bpf_link_init(&link->link, BPF_LINK_TYPE_CGROUP, &bpf_cgroup_link_lops,
		      prog);
	link->cgroup = cgrp;
	link->type = attr->link_create.attach_type;

	err  = bpf_link_prime(&link->link, &link_primer);
	अगर (err) अणु
		kमुक्त(link);
		जाओ out_put_cgroup;
	पूर्ण

	err = cgroup_bpf_attach(cgrp, शून्य, शून्य, link, link->type,
				BPF_F_ALLOW_MULTI);
	अगर (err) अणु
		bpf_link_cleanup(&link_primer);
		जाओ out_put_cgroup;
	पूर्ण

	वापस bpf_link_settle(&link_primer);

out_put_cgroup:
	cgroup_put(cgrp);
	वापस err;
पूर्ण

पूर्णांक cgroup_bpf_prog_query(स्थिर जोड़ bpf_attr *attr,
			  जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा cgroup *cgrp;
	पूर्णांक ret;

	cgrp = cgroup_get_from_fd(attr->query.target_fd);
	अगर (IS_ERR(cgrp))
		वापस PTR_ERR(cgrp);

	ret = cgroup_bpf_query(cgrp, attr, uattr);

	cgroup_put(cgrp);
	वापस ret;
पूर्ण

/**
 * __cgroup_bpf_run_filter_skb() - Run a program क्रम packet filtering
 * @sk: The socket sending or receiving traffic
 * @skb: The skb that is being sent or received
 * @type: The type of program to be exectuted
 *
 * If no socket is passed, or the socket is not of type INET or INET6,
 * this function करोes nothing and वापसs 0.
 *
 * The program type passed in via @type must be suitable क्रम network
 * filtering. No further check is perक्रमmed to निश्चित that.
 *
 * For egress packets, this function can वापस:
 *   NET_XMIT_SUCCESS    (0)	- जारी with packet output
 *   NET_XMIT_DROP       (1)	- drop packet and notअगरy TCP to call cwr
 *   NET_XMIT_CN         (2)	- जारी with packet output and notअगरy TCP
 *				  to call cwr
 *   -EPERM			- drop packet
 *
 * For ingress packets, this function will वापस -EPERM अगर any
 * attached program was found and अगर it वापसed != 1 during execution.
 * Otherwise 0 is वापसed.
 */
पूर्णांक __cgroup_bpf_run_filter_skb(काष्ठा sock *sk,
				काष्ठा sk_buff *skb,
				क्रमागत bpf_attach_type type)
अणु
	अचिन्हित पूर्णांक offset = skb->data - skb_network_header(skb);
	काष्ठा sock *save_sk;
	व्योम *saved_data_end;
	काष्ठा cgroup *cgrp;
	पूर्णांक ret;

	अगर (!sk || !sk_fullsock(sk))
		वापस 0;

	अगर (sk->sk_family != AF_INET && sk->sk_family != AF_INET6)
		वापस 0;

	cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	save_sk = skb->sk;
	skb->sk = sk;
	__skb_push(skb, offset);

	/* compute poपूर्णांकers क्रम the bpf prog */
	bpf_compute_and_save_data_end(skb, &saved_data_end);

	अगर (type == BPF_CGROUP_INET_EGRESS) अणु
		ret = BPF_PROG_CGROUP_INET_EGRESS_RUN_ARRAY(
			cgrp->bpf.effective[type], skb, __bpf_prog_run_save_cb);
	पूर्ण अन्यथा अणु
		ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[type], skb,
					  __bpf_prog_run_save_cb);
		ret = (ret == 1 ? 0 : -EPERM);
	पूर्ण
	bpf_restore_data_end(skb, saved_data_end);
	__skb_pull(skb, offset);
	skb->sk = save_sk;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__cgroup_bpf_run_filter_skb);

/**
 * __cgroup_bpf_run_filter_sk() - Run a program on a sock
 * @sk: sock काष्ठाure to manipulate
 * @type: The type of program to be exectuted
 *
 * socket is passed is expected to be of type INET or INET6.
 *
 * The program type passed in via @type must be suitable क्रम sock
 * filtering. No further check is perक्रमmed to निश्चित that.
 *
 * This function will वापस %-EPERM अगर any अगर an attached program was found
 * and अगर it वापसed != 1 during execution. In all other हालs, 0 is वापसed.
 */
पूर्णांक __cgroup_bpf_run_filter_sk(काष्ठा sock *sk,
			       क्रमागत bpf_attach_type type)
अणु
	काष्ठा cgroup *cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	पूर्णांक ret;

	ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[type], sk, BPF_PROG_RUN);
	वापस ret == 1 ? 0 : -EPERM;
पूर्ण
EXPORT_SYMBOL(__cgroup_bpf_run_filter_sk);

/**
 * __cgroup_bpf_run_filter_sock_addr() - Run a program on a sock and
 *                                       provided by user sockaddr
 * @sk: sock काष्ठा that will use sockaddr
 * @uaddr: sockaddr काष्ठा provided by user
 * @type: The type of program to be exectuted
 * @t_ctx: Poपूर्णांकer to attach type specअगरic context
 * @flags: Poपूर्णांकer to u32 which contains higher bits of BPF program
 *         वापस value (OR'ed together).
 *
 * socket is expected to be of type INET or INET6.
 *
 * This function will वापस %-EPERM अगर an attached program is found and
 * वापसed value != 1 during execution. In all other हालs, 0 is वापसed.
 */
पूर्णांक __cgroup_bpf_run_filter_sock_addr(काष्ठा sock *sk,
				      काष्ठा sockaddr *uaddr,
				      क्रमागत bpf_attach_type type,
				      व्योम *t_ctx,
				      u32 *flags)
अणु
	काष्ठा bpf_sock_addr_kern ctx = अणु
		.sk = sk,
		.uaddr = uaddr,
		.t_ctx = t_ctx,
	पूर्ण;
	काष्ठा sockaddr_storage unspec;
	काष्ठा cgroup *cgrp;
	पूर्णांक ret;

	/* Check socket family since not all sockets represent network
	 * endpoपूर्णांक (e.g. AF_UNIX).
	 */
	अगर (sk->sk_family != AF_INET && sk->sk_family != AF_INET6)
		वापस 0;

	अगर (!ctx.uaddr) अणु
		स_रखो(&unspec, 0, माप(unspec));
		ctx.uaddr = (काष्ठा sockaddr *)&unspec;
	पूर्ण

	cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	ret = BPF_PROG_RUN_ARRAY_FLAGS(cgrp->bpf.effective[type], &ctx,
				       BPF_PROG_RUN, flags);

	वापस ret == 1 ? 0 : -EPERM;
पूर्ण
EXPORT_SYMBOL(__cgroup_bpf_run_filter_sock_addr);

/**
 * __cgroup_bpf_run_filter_sock_ops() - Run a program on a sock
 * @sk: socket to get cgroup from
 * @sock_ops: bpf_sock_ops_kern काष्ठा to pass to program. Contains
 * sk with connection inक्रमmation (IP addresses, etc.) May not contain
 * cgroup info अगर it is a req sock.
 * @type: The type of program to be exectuted
 *
 * socket passed is expected to be of type INET or INET6.
 *
 * The program type passed in via @type must be suitable क्रम sock_ops
 * filtering. No further check is perक्रमmed to निश्चित that.
 *
 * This function will वापस %-EPERM अगर any अगर an attached program was found
 * and अगर it वापसed != 1 during execution. In all other हालs, 0 is वापसed.
 */
पूर्णांक __cgroup_bpf_run_filter_sock_ops(काष्ठा sock *sk,
				     काष्ठा bpf_sock_ops_kern *sock_ops,
				     क्रमागत bpf_attach_type type)
अणु
	काष्ठा cgroup *cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	पूर्णांक ret;

	ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[type], sock_ops,
				 BPF_PROG_RUN);
	वापस ret == 1 ? 0 : -EPERM;
पूर्ण
EXPORT_SYMBOL(__cgroup_bpf_run_filter_sock_ops);

पूर्णांक __cgroup_bpf_check_dev_permission(लघु dev_type, u32 major, u32 minor,
				      लघु access, क्रमागत bpf_attach_type type)
अणु
	काष्ठा cgroup *cgrp;
	काष्ठा bpf_cgroup_dev_ctx ctx = अणु
		.access_type = (access << 16) | dev_type,
		.major = major,
		.minor = minor,
	पूर्ण;
	पूर्णांक allow = 1;

	rcu_पढ़ो_lock();
	cgrp = task_dfl_cgroup(current);
	allow = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[type], &ctx,
				   BPF_PROG_RUN);
	rcu_पढ़ो_unlock();

	वापस !allow;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
cgroup_base_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_get_current_uid_gid:
		वापस &bpf_get_current_uid_gid_proto;
	हाल BPF_FUNC_get_local_storage:
		वापस &bpf_get_local_storage_proto;
	हाल BPF_FUNC_get_current_cgroup_id:
		वापस &bpf_get_current_cgroup_id_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_event_output_data_proto;
	शेष:
		वापस bpf_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
cgroup_dev_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस cgroup_base_func_proto(func_id, prog);
पूर्ण

अटल bool cgroup_dev_is_valid_access(पूर्णांक off, पूर्णांक size,
				       क्रमागत bpf_access_type type,
				       स्थिर काष्ठा bpf_prog *prog,
				       काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_शेष = माप(__u32);

	अगर (type == BPF_WRITE)
		वापस false;

	अगर (off < 0 || off + size > माप(काष्ठा bpf_cgroup_dev_ctx))
		वापस false;
	/* The verअगरier guarantees that size > 0. */
	अगर (off % size != 0)
		वापस false;

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा bpf_cgroup_dev_ctx, access_type):
		bpf_ctx_record_field_size(info, size_शेष);
		अगर (!bpf_ctx_narrow_access_ok(off, size, size_शेष))
			वापस false;
		अवरोध;
	शेष:
		अगर (size != size_शेष)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

स्थिर काष्ठा bpf_prog_ops cg_dev_prog_ops = अणु
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops cg_dev_verअगरier_ops = अणु
	.get_func_proto		= cgroup_dev_func_proto,
	.is_valid_access	= cgroup_dev_is_valid_access,
पूर्ण;

/**
 * __cgroup_bpf_run_filter_sysctl - Run a program on sysctl
 *
 * @head: sysctl table header
 * @table: sysctl table
 * @ग_लिखो: sysctl is being पढ़ो (= 0) or written (= 1)
 * @buf: poपूर्णांकer to buffer (in and out)
 * @pcount: value-result argument: value is size of buffer poपूर्णांकed to by @buf,
 *	result is size of @new_buf अगर program set new value, initial value
 *	otherwise
 * @ppos: value-result argument: value is position at which पढ़ो from or ग_लिखो
 *	to sysctl is happening, result is new position अगर program overrode it,
 *	initial value otherwise
 * @type: type of program to be executed
 *
 * Program is run when sysctl is being accessed, either पढ़ो or written, and
 * can allow or deny such access.
 *
 * This function will वापस %-EPERM अगर an attached program is found and
 * वापसed value != 1 during execution. In all other हालs 0 is वापसed.
 */
पूर्णांक __cgroup_bpf_run_filter_sysctl(काष्ठा ctl_table_header *head,
				   काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				   अक्षर **buf, माप_प्रकार *pcount, loff_t *ppos,
				   क्रमागत bpf_attach_type type)
अणु
	काष्ठा bpf_sysctl_kern ctx = अणु
		.head = head,
		.table = table,
		.ग_लिखो = ग_लिखो,
		.ppos = ppos,
		.cur_val = शून्य,
		.cur_len = PAGE_SIZE,
		.new_val = शून्य,
		.new_len = 0,
		.new_updated = 0,
	पूर्ण;
	काष्ठा cgroup *cgrp;
	loff_t pos = 0;
	पूर्णांक ret;

	ctx.cur_val = kदो_स्मृति_track_caller(ctx.cur_len, GFP_KERNEL);
	अगर (!ctx.cur_val ||
	    table->proc_handler(table, 0, ctx.cur_val, &ctx.cur_len, &pos)) अणु
		/* Let BPF program decide how to proceed. */
		ctx.cur_len = 0;
	पूर्ण

	अगर (ग_लिखो && *buf && *pcount) अणु
		/* BPF program should be able to override new value with a
		 * buffer bigger than provided by user.
		 */
		ctx.new_val = kदो_स्मृति_track_caller(PAGE_SIZE, GFP_KERNEL);
		ctx.new_len = min_t(माप_प्रकार, PAGE_SIZE, *pcount);
		अगर (ctx.new_val) अणु
			स_नकल(ctx.new_val, *buf, ctx.new_len);
		पूर्ण अन्यथा अणु
			/* Let BPF program decide how to proceed. */
			ctx.new_len = 0;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	cgrp = task_dfl_cgroup(current);
	ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[type], &ctx, BPF_PROG_RUN);
	rcu_पढ़ो_unlock();

	kमुक्त(ctx.cur_val);

	अगर (ret == 1 && ctx.new_updated) अणु
		kमुक्त(*buf);
		*buf = ctx.new_val;
		*pcount = ctx.new_len;
	पूर्ण अन्यथा अणु
		kमुक्त(ctx.new_val);
	पूर्ण

	वापस ret == 1 ? 0 : -EPERM;
पूर्ण

#अगर_घोषित CONFIG_NET
अटल bool __cgroup_bpf_prog_array_is_empty(काष्ठा cgroup *cgrp,
					     क्रमागत bpf_attach_type attach_type)
अणु
	काष्ठा bpf_prog_array *prog_array;
	bool empty;

	rcu_पढ़ो_lock();
	prog_array = rcu_dereference(cgrp->bpf.effective[attach_type]);
	empty = bpf_prog_array_is_empty(prog_array);
	rcu_पढ़ो_unlock();

	वापस empty;
पूर्ण

अटल पूर्णांक sockopt_alloc_buf(काष्ठा bpf_sockopt_kern *ctx, पूर्णांक max_optlen,
			     काष्ठा bpf_sockopt_buf *buf)
अणु
	अगर (unlikely(max_optlen < 0))
		वापस -EINVAL;

	अगर (unlikely(max_optlen > PAGE_SIZE)) अणु
		/* We करोn't expose optvals that are greater than PAGE_SIZE
		 * to the BPF program.
		 */
		max_optlen = PAGE_SIZE;
	पूर्ण

	अगर (max_optlen <= माप(buf->data)) अणु
		/* When the optval fits पूर्णांकo BPF_SOCKOPT_KERN_BUF_SIZE
		 * bytes aव्योम the cost of kzalloc.
		 */
		ctx->optval = buf->data;
		ctx->optval_end = ctx->optval + max_optlen;
		वापस max_optlen;
	पूर्ण

	ctx->optval = kzalloc(max_optlen, GFP_USER);
	अगर (!ctx->optval)
		वापस -ENOMEM;

	ctx->optval_end = ctx->optval + max_optlen;

	वापस max_optlen;
पूर्ण

अटल व्योम sockopt_मुक्त_buf(काष्ठा bpf_sockopt_kern *ctx,
			     काष्ठा bpf_sockopt_buf *buf)
अणु
	अगर (ctx->optval == buf->data)
		वापस;
	kमुक्त(ctx->optval);
पूर्ण

अटल bool sockopt_buf_allocated(काष्ठा bpf_sockopt_kern *ctx,
				  काष्ठा bpf_sockopt_buf *buf)
अणु
	वापस ctx->optval != buf->data;
पूर्ण

पूर्णांक __cgroup_bpf_run_filter_setsockopt(काष्ठा sock *sk, पूर्णांक *level,
				       पूर्णांक *optname, अक्षर __user *optval,
				       पूर्णांक *optlen, अक्षर **kernel_optval)
अणु
	काष्ठा cgroup *cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	काष्ठा bpf_sockopt_buf buf = अणुपूर्ण;
	काष्ठा bpf_sockopt_kern ctx = अणु
		.sk = sk,
		.level = *level,
		.optname = *optname,
	पूर्ण;
	पूर्णांक ret, max_optlen;

	/* Opportunistic check to see whether we have any BPF program
	 * attached to the hook so we करोn't waste समय allocating
	 * memory and locking the socket.
	 */
	अगर (__cgroup_bpf_prog_array_is_empty(cgrp, BPF_CGROUP_SETSOCKOPT))
		वापस 0;

	/* Allocate a bit more than the initial user buffer क्रम
	 * BPF program. The canonical use हाल is overriding
	 * TCP_CONGESTION(nv) to TCP_CONGESTION(cubic).
	 */
	max_optlen = max_t(पूर्णांक, 16, *optlen);

	max_optlen = sockopt_alloc_buf(&ctx, max_optlen, &buf);
	अगर (max_optlen < 0)
		वापस max_optlen;

	ctx.optlen = *optlen;

	अगर (copy_from_user(ctx.optval, optval, min(*optlen, max_optlen)) != 0) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	lock_sock(sk);
	ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[BPF_CGROUP_SETSOCKOPT],
				 &ctx, BPF_PROG_RUN);
	release_sock(sk);

	अगर (!ret) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	अगर (ctx.optlen == -1) अणु
		/* optlen set to -1, bypass kernel */
		ret = 1;
	पूर्ण अन्यथा अगर (ctx.optlen > max_optlen || ctx.optlen < -1) अणु
		/* optlen is out of bounds */
		ret = -EFAULT;
	पूर्ण अन्यथा अणु
		/* optlen within bounds, run kernel handler */
		ret = 0;

		/* export any potential modअगरications */
		*level = ctx.level;
		*optname = ctx.optname;

		/* optlen == 0 from BPF indicates that we should
		 * use original userspace data.
		 */
		अगर (ctx.optlen != 0) अणु
			*optlen = ctx.optlen;
			/* We've used bpf_sockopt_kern->buf as an पूर्णांकermediary
			 * storage, but the BPF program indicates that we need
			 * to pass this data to the kernel setsockopt handler.
			 * No way to export on-stack buf, have to allocate a
			 * new buffer.
			 */
			अगर (!sockopt_buf_allocated(&ctx, &buf)) अणु
				व्योम *p = kदो_स्मृति(ctx.optlen, GFP_USER);

				अगर (!p) अणु
					ret = -ENOMEM;
					जाओ out;
				पूर्ण
				स_नकल(p, ctx.optval, ctx.optlen);
				*kernel_optval = p;
			पूर्ण अन्यथा अणु
				*kernel_optval = ctx.optval;
			पूर्ण
			/* export and करोn't मुक्त sockopt buf */
			वापस 0;
		पूर्ण
	पूर्ण

out:
	sockopt_मुक्त_buf(&ctx, &buf);
	वापस ret;
पूर्ण

पूर्णांक __cgroup_bpf_run_filter_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level,
				       पूर्णांक optname, अक्षर __user *optval,
				       पूर्णांक __user *optlen, पूर्णांक max_optlen,
				       पूर्णांक retval)
अणु
	काष्ठा cgroup *cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	काष्ठा bpf_sockopt_buf buf = अणुपूर्ण;
	काष्ठा bpf_sockopt_kern ctx = अणु
		.sk = sk,
		.level = level,
		.optname = optname,
		.retval = retval,
	पूर्ण;
	पूर्णांक ret;

	/* Opportunistic check to see whether we have any BPF program
	 * attached to the hook so we करोn't waste समय allocating
	 * memory and locking the socket.
	 */
	अगर (__cgroup_bpf_prog_array_is_empty(cgrp, BPF_CGROUP_GETSOCKOPT))
		वापस retval;

	ctx.optlen = max_optlen;

	max_optlen = sockopt_alloc_buf(&ctx, max_optlen, &buf);
	अगर (max_optlen < 0)
		वापस max_optlen;

	अगर (!retval) अणु
		/* If kernel माला_लोockopt finished successfully,
		 * copy whatever was वापसed to the user back
		 * पूर्णांकo our temporary buffer. Set optlen to the
		 * one that kernel वापसed as well to let
		 * BPF programs inspect the value.
		 */

		अगर (get_user(ctx.optlen, optlen)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		अगर (ctx.optlen < 0) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		अगर (copy_from_user(ctx.optval, optval,
				   min(ctx.optlen, max_optlen)) != 0) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	lock_sock(sk);
	ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[BPF_CGROUP_GETSOCKOPT],
				 &ctx, BPF_PROG_RUN);
	release_sock(sk);

	अगर (!ret) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	अगर (ctx.optlen > max_optlen || ctx.optlen < 0) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/* BPF programs only allowed to set retval to 0, not some
	 * arbitrary value.
	 */
	अगर (ctx.retval != 0 && ctx.retval != retval) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (ctx.optlen != 0) अणु
		अगर (copy_to_user(optval, ctx.optval, ctx.optlen) ||
		    put_user(ctx.optlen, optlen)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ctx.retval;

out:
	sockopt_मुक्त_buf(&ctx, &buf);
	वापस ret;
पूर्ण

पूर्णांक __cgroup_bpf_run_filter_माला_लोockopt_kern(काष्ठा sock *sk, पूर्णांक level,
					    पूर्णांक optname, व्योम *optval,
					    पूर्णांक *optlen, पूर्णांक retval)
अणु
	काष्ठा cgroup *cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	काष्ठा bpf_sockopt_kern ctx = अणु
		.sk = sk,
		.level = level,
		.optname = optname,
		.retval = retval,
		.optlen = *optlen,
		.optval = optval,
		.optval_end = optval + *optlen,
	पूर्ण;
	पूर्णांक ret;

	/* Note that __cgroup_bpf_run_filter_माला_लोockopt करोesn't copy
	 * user data back पूर्णांकo BPF buffer when reval != 0. This is
	 * करोne as an optimization to aव्योम extra copy, assuming
	 * kernel won't populate the data in हाल of an error.
	 * Here we always pass the data and स_रखो() should
	 * be called अगर that data shouldn't be "exported".
	 */

	ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[BPF_CGROUP_GETSOCKOPT],
				 &ctx, BPF_PROG_RUN);
	अगर (!ret)
		वापस -EPERM;

	अगर (ctx.optlen > *optlen)
		वापस -EFAULT;

	/* BPF programs only allowed to set retval to 0, not some
	 * arbitrary value.
	 */
	अगर (ctx.retval != 0 && ctx.retval != retval)
		वापस -EFAULT;

	/* BPF programs can shrink the buffer, export the modअगरications.
	 */
	अगर (ctx.optlen != 0)
		*optlen = ctx.optlen;

	वापस ctx.retval;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार sysctl_cpy_dir(स्थिर काष्ठा ctl_dir *dir, अक्षर **bufp,
			      माप_प्रकार *lenp)
अणु
	sमाप_प्रकार पंचांगp_ret = 0, ret;

	अगर (dir->header.parent) अणु
		पंचांगp_ret = sysctl_cpy_dir(dir->header.parent, bufp, lenp);
		अगर (पंचांगp_ret < 0)
			वापस पंचांगp_ret;
	पूर्ण

	ret = strscpy(*bufp, dir->header.ctl_table[0].procname, *lenp);
	अगर (ret < 0)
		वापस ret;
	*bufp += ret;
	*lenp -= ret;
	ret += पंचांगp_ret;

	/* Aव्योम leading slash. */
	अगर (!ret)
		वापस ret;

	पंचांगp_ret = strscpy(*bufp, "/", *lenp);
	अगर (पंचांगp_ret < 0)
		वापस पंचांगp_ret;
	*bufp += पंचांगp_ret;
	*lenp -= पंचांगp_ret;

	वापस ret + पंचांगp_ret;
पूर्ण

BPF_CALL_4(bpf_sysctl_get_name, काष्ठा bpf_sysctl_kern *, ctx, अक्षर *, buf,
	   माप_प्रकार, buf_len, u64, flags)
अणु
	sमाप_प्रकार पंचांगp_ret = 0, ret;

	अगर (!buf)
		वापस -EINVAL;

	अगर (!(flags & BPF_F_SYSCTL_BASE_NAME)) अणु
		अगर (!ctx->head)
			वापस -EINVAL;
		पंचांगp_ret = sysctl_cpy_dir(ctx->head->parent, &buf, &buf_len);
		अगर (पंचांगp_ret < 0)
			वापस पंचांगp_ret;
	पूर्ण

	ret = strscpy(buf, ctx->table->procname, buf_len);

	वापस ret < 0 ? ret : पंचांगp_ret + ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sysctl_get_name_proto = अणु
	.func		= bpf_sysctl_get_name,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

अटल पूर्णांक copy_sysctl_value(अक्षर *dst, माप_प्रकार dst_len, अक्षर *src,
			     माप_प्रकार src_len)
अणु
	अगर (!dst)
		वापस -EINVAL;

	अगर (!dst_len)
		वापस -E2BIG;

	अगर (!src || !src_len) अणु
		स_रखो(dst, 0, dst_len);
		वापस -EINVAL;
	पूर्ण

	स_नकल(dst, src, min(dst_len, src_len));

	अगर (dst_len > src_len) अणु
		स_रखो(dst + src_len, '\0', dst_len - src_len);
		वापस src_len;
	पूर्ण

	dst[dst_len - 1] = '\0';

	वापस -E2BIG;
पूर्ण

BPF_CALL_3(bpf_sysctl_get_current_value, काष्ठा bpf_sysctl_kern *, ctx,
	   अक्षर *, buf, माप_प्रकार, buf_len)
अणु
	वापस copy_sysctl_value(buf, buf_len, ctx->cur_val, ctx->cur_len);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sysctl_get_current_value_proto = अणु
	.func		= bpf_sysctl_get_current_value,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_3(bpf_sysctl_get_new_value, काष्ठा bpf_sysctl_kern *, ctx, अक्षर *, buf,
	   माप_प्रकार, buf_len)
अणु
	अगर (!ctx->ग_लिखो) अणु
		अगर (buf && buf_len)
			स_रखो(buf, '\0', buf_len);
		वापस -EINVAL;
	पूर्ण
	वापस copy_sysctl_value(buf, buf_len, ctx->new_val, ctx->new_len);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sysctl_get_new_value_proto = अणु
	.func		= bpf_sysctl_get_new_value,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_3(bpf_sysctl_set_new_value, काष्ठा bpf_sysctl_kern *, ctx,
	   स्थिर अक्षर *, buf, माप_प्रकार, buf_len)
अणु
	अगर (!ctx->ग_लिखो || !ctx->new_val || !ctx->new_len || !buf || !buf_len)
		वापस -EINVAL;

	अगर (buf_len > PAGE_SIZE - 1)
		वापस -E2BIG;

	स_नकल(ctx->new_val, buf, buf_len);
	ctx->new_len = buf_len;
	ctx->new_updated = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sysctl_set_new_value_proto = अणु
	.func		= bpf_sysctl_set_new_value,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
sysctl_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_म_से_दीर्घ:
		वापस &bpf_म_से_दीर्घ_proto;
	हाल BPF_FUNC_म_से_अदीर्घ:
		वापस &bpf_म_से_अदीर्घ_proto;
	हाल BPF_FUNC_sysctl_get_name:
		वापस &bpf_sysctl_get_name_proto;
	हाल BPF_FUNC_sysctl_get_current_value:
		वापस &bpf_sysctl_get_current_value_proto;
	हाल BPF_FUNC_sysctl_get_new_value:
		वापस &bpf_sysctl_get_new_value_proto;
	हाल BPF_FUNC_sysctl_set_new_value:
		वापस &bpf_sysctl_set_new_value_proto;
	शेष:
		वापस cgroup_base_func_proto(func_id, prog);
	पूर्ण
पूर्ण

अटल bool sysctl_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				   स्थिर काष्ठा bpf_prog *prog,
				   काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_शेष = माप(__u32);

	अगर (off < 0 || off + size > माप(काष्ठा bpf_sysctl) || off % size)
		वापस false;

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा bpf_sysctl, ग_लिखो):
		अगर (type != BPF_READ)
			वापस false;
		bpf_ctx_record_field_size(info, size_शेष);
		वापस bpf_ctx_narrow_access_ok(off, size, size_शेष);
	हाल bpf_ctx_range(काष्ठा bpf_sysctl, file_pos):
		अगर (type == BPF_READ) अणु
			bpf_ctx_record_field_size(info, size_शेष);
			वापस bpf_ctx_narrow_access_ok(off, size, size_शेष);
		पूर्ण अन्यथा अणु
			वापस size == size_शेष;
		पूर्ण
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u32 sysctl_convert_ctx_access(क्रमागत bpf_access_type type,
				     स्थिर काष्ठा bpf_insn *si,
				     काष्ठा bpf_insn *insn_buf,
				     काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;
	u32 पढ़ो_size;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_sysctl, ग_लिखो):
		*insn++ = BPF_LDX_MEM(
			BPF_SIZE(si->code), si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा bpf_sysctl_kern, ग_लिखो,
				       माप_field(काष्ठा bpf_sysctl_kern,
						    ग_लिखो),
				       target_size));
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sysctl, file_pos):
		/* ppos is a poपूर्णांकer so it should be accessed via indirect
		 * loads and stores. Also क्रम stores additional temporary
		 * रेजिस्टर is used since neither src_reg nor dst_reg can be
		 * overridden.
		 */
		अगर (type == BPF_WRITE) अणु
			पूर्णांक treg = BPF_REG_9;

			अगर (si->src_reg == treg || si->dst_reg == treg)
				--treg;
			अगर (si->src_reg == treg || si->dst_reg == treg)
				--treg;
			*insn++ = BPF_STX_MEM(
				BPF_DW, si->dst_reg, treg,
				दुरत्व(काष्ठा bpf_sysctl_kern, पंचांगp_reg));
			*insn++ = BPF_LDX_MEM(
				BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sysctl_kern, ppos),
				treg, si->dst_reg,
				दुरत्व(काष्ठा bpf_sysctl_kern, ppos));
			*insn++ = BPF_STX_MEM(
				BPF_SIZखातापूर्ण(u32), treg, si->src_reg,
				bpf_ctx_narrow_access_offset(
					0, माप(u32), माप(loff_t)));
			*insn++ = BPF_LDX_MEM(
				BPF_DW, treg, si->dst_reg,
				दुरत्व(काष्ठा bpf_sysctl_kern, पंचांगp_reg));
		पूर्ण अन्यथा अणु
			*insn++ = BPF_LDX_MEM(
				BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sysctl_kern, ppos),
				si->dst_reg, si->src_reg,
				दुरत्व(काष्ठा bpf_sysctl_kern, ppos));
			पढ़ो_size = bpf_माप_प्रकारo_bytes(BPF_SIZE(si->code));
			*insn++ = BPF_LDX_MEM(
				BPF_SIZE(si->code), si->dst_reg, si->dst_reg,
				bpf_ctx_narrow_access_offset(
					0, पढ़ो_size, माप(loff_t)));
		पूर्ण
		*target_size = माप(u32);
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops cg_sysctl_verअगरier_ops = अणु
	.get_func_proto		= sysctl_func_proto,
	.is_valid_access	= sysctl_is_valid_access,
	.convert_ctx_access	= sysctl_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops cg_sysctl_prog_ops = अणु
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
cg_sockopt_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
#अगर_घोषित CONFIG_NET
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_INET
	हाल BPF_FUNC_tcp_sock:
		वापस &bpf_tcp_sock_proto;
#पूर्ण_अगर
	शेष:
		वापस cgroup_base_func_proto(func_id, prog);
	पूर्ण
पूर्ण

अटल bool cg_sockopt_is_valid_access(पूर्णांक off, पूर्णांक size,
				       क्रमागत bpf_access_type type,
				       स्थिर काष्ठा bpf_prog *prog,
				       काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_शेष = माप(__u32);

	अगर (off < 0 || off >= माप(काष्ठा bpf_sockopt))
		वापस false;

	अगर (off % size != 0)
		वापस false;

	अगर (type == BPF_WRITE) अणु
		चयन (off) अणु
		हाल दुरत्व(काष्ठा bpf_sockopt, retval):
			अगर (size != size_शेष)
				वापस false;
			वापस prog->expected_attach_type ==
				BPF_CGROUP_GETSOCKOPT;
		हाल दुरत्व(काष्ठा bpf_sockopt, optname):
			fallthrough;
		हाल दुरत्व(काष्ठा bpf_sockopt, level):
			अगर (size != size_शेष)
				वापस false;
			वापस prog->expected_attach_type ==
				BPF_CGROUP_SETSOCKOPT;
		हाल दुरत्व(काष्ठा bpf_sockopt, optlen):
			वापस size == size_शेष;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	चयन (off) अणु
	हाल दुरत्व(काष्ठा bpf_sockopt, sk):
		अगर (size != माप(__u64))
			वापस false;
		info->reg_type = PTR_TO_SOCKET;
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, optval):
		अगर (size != माप(__u64))
			वापस false;
		info->reg_type = PTR_TO_PACKET;
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, optval_end):
		अगर (size != माप(__u64))
			वापस false;
		info->reg_type = PTR_TO_PACKET_END;
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, retval):
		अगर (size != size_शेष)
			वापस false;
		वापस prog->expected_attach_type == BPF_CGROUP_GETSOCKOPT;
	शेष:
		अगर (size != size_शेष)
			वापस false;
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

#घोषणा CG_SOCKOPT_ACCESS_FIELD(T, F)					\
	T(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sockopt_kern, F),			\
	  si->dst_reg, si->src_reg,					\
	  दुरत्व(काष्ठा bpf_sockopt_kern, F))

अटल u32 cg_sockopt_convert_ctx_access(क्रमागत bpf_access_type type,
					 स्थिर काष्ठा bpf_insn *si,
					 काष्ठा bpf_insn *insn_buf,
					 काष्ठा bpf_prog *prog,
					 u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_sockopt, sk):
		*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_LDX_MEM, sk);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, level):
		अगर (type == BPF_WRITE)
			*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_STX_MEM, level);
		अन्यथा
			*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_LDX_MEM, level);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, optname):
		अगर (type == BPF_WRITE)
			*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_STX_MEM, optname);
		अन्यथा
			*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_LDX_MEM, optname);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, optlen):
		अगर (type == BPF_WRITE)
			*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_STX_MEM, optlen);
		अन्यथा
			*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_LDX_MEM, optlen);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, retval):
		अगर (type == BPF_WRITE)
			*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_STX_MEM, retval);
		अन्यथा
			*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_LDX_MEM, retval);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, optval):
		*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_LDX_MEM, optval);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sockopt, optval_end):
		*insn++ = CG_SOCKOPT_ACCESS_FIELD(BPF_LDX_MEM, optval_end);
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

अटल पूर्णांक cg_sockopt_get_prologue(काष्ठा bpf_insn *insn_buf,
				   bool direct_ग_लिखो,
				   स्थिर काष्ठा bpf_prog *prog)
अणु
	/* Nothing to करो क्रम sockopt argument. The data is kzalloc'ated.
	 */
	वापस 0;
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops cg_sockopt_verअगरier_ops = अणु
	.get_func_proto		= cg_sockopt_func_proto,
	.is_valid_access	= cg_sockopt_is_valid_access,
	.convert_ctx_access	= cg_sockopt_convert_ctx_access,
	.gen_prologue		= cg_sockopt_get_prologue,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops cg_sockopt_prog_ops = अणु
पूर्ण;
