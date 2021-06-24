<शैली गुरु>
/*
 * Copyright (C) 2017 Netronome Systems, Inc.
 *
 * This software is licensed under the GNU General License Version 2,
 * June 1991 as shown in the file COPYING in the top-level directory of this
 * source tree.
 *
 * THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS"
 * WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE
 * OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME
 * THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 */

#समावेश <linux/bpf.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/pkt_cls.h>

#समावेश "netdevsim.h"

#घोषणा pr_vlog(env, fmt, ...)	\
	bpf_verअगरier_log_ग_लिखो(env, "[netdevsim] " fmt, ##__VA_ARGS__)

काष्ठा nsim_bpf_bound_prog अणु
	काष्ठा nsim_dev *nsim_dev;
	काष्ठा bpf_prog *prog;
	काष्ठा dentry *ddir;
	स्थिर अक्षर *state;
	bool is_loaded;
	काष्ठा list_head l;
पूर्ण;

#घोषणा NSIM_BPF_MAX_KEYS		2

काष्ठा nsim_bpf_bound_map अणु
	काष्ठा netdevsim *ns;
	काष्ठा bpf_offloaded_map *map;
	काष्ठा mutex mutex;
	काष्ठा nsim_map_entry अणु
		व्योम *key;
		व्योम *value;
	पूर्ण entry[NSIM_BPF_MAX_KEYS];
	काष्ठा list_head l;
पूर्ण;

अटल पूर्णांक nsim_bpf_string_show(काष्ठा seq_file *file, व्योम *data)
अणु
	स्थिर अक्षर **str = file->निजी;

	अगर (*str)
		seq_म_लिखो(file, "%s\n", *str);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(nsim_bpf_string);

अटल पूर्णांक
nsim_bpf_verअगरy_insn(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx, पूर्णांक prev_insn)
अणु
	काष्ठा nsim_bpf_bound_prog *state;
	पूर्णांक ret = 0;

	state = env->prog->aux->offload->dev_priv;
	अगर (state->nsim_dev->bpf_bind_verअगरier_delay && !insn_idx)
		msleep(state->nsim_dev->bpf_bind_verअगरier_delay);

	अगर (insn_idx == env->prog->len - 1) अणु
		pr_vlog(env, "Hello from netdevsim!\n");

		अगर (!state->nsim_dev->bpf_bind_verअगरier_accept)
			ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nsim_bpf_finalize(काष्ठा bpf_verअगरier_env *env)
अणु
	वापस 0;
पूर्ण

अटल bool nsim_xdp_offload_active(काष्ठा netdevsim *ns)
अणु
	वापस ns->xdp_hw.prog;
पूर्ण

अटल व्योम nsim_prog_set_loaded(काष्ठा bpf_prog *prog, bool loaded)
अणु
	काष्ठा nsim_bpf_bound_prog *state;

	अगर (!prog || !prog->aux->offload)
		वापस;

	state = prog->aux->offload->dev_priv;
	state->is_loaded = loaded;
पूर्ण

अटल पूर्णांक
nsim_bpf_offload(काष्ठा netdevsim *ns, काष्ठा bpf_prog *prog, bool oldprog)
अणु
	nsim_prog_set_loaded(ns->bpf_offloaded, false);

	WARN(!!ns->bpf_offloaded != oldprog,
	     "bad offload state, expected offload %sto be active",
	     oldprog ? "" : "not ");
	ns->bpf_offloaded = prog;
	ns->bpf_offloaded_id = prog ? prog->aux->id : 0;
	nsim_prog_set_loaded(prog, true);

	वापस 0;
पूर्ण

पूर्णांक nsim_bpf_setup_tc_block_cb(क्रमागत tc_setup_type type,
			       व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा tc_cls_bpf_offload *cls_bpf = type_data;
	काष्ठा bpf_prog *prog = cls_bpf->prog;
	काष्ठा netdevsim *ns = cb_priv;
	काष्ठा bpf_prog *oldprog;

	अगर (type != TC_SETUP_CLSBPF) अणु
		NSIM_EA(cls_bpf->common.extack,
			"only offload of BPF classifiers supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!tc_cls_can_offload_and_chain0(ns->netdev, &cls_bpf->common))
		वापस -EOPNOTSUPP;

	अगर (cls_bpf->common.protocol != htons(ETH_P_ALL)) अणु
		NSIM_EA(cls_bpf->common.extack,
			"only ETH_P_ALL supported as filter protocol");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!ns->bpf_tc_accept) अणु
		NSIM_EA(cls_bpf->common.extack,
			"netdevsim configured to reject BPF TC offload");
		वापस -EOPNOTSUPP;
	पूर्ण
	/* Note: progs without skip_sw will probably not be dev bound */
	अगर (prog && !prog->aux->offload && !ns->bpf_tc_non_bound_accept) अणु
		NSIM_EA(cls_bpf->common.extack,
			"netdevsim configured to reject unbound programs");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (cls_bpf->command != TC_CLSBPF_OFFLOAD)
		वापस -EOPNOTSUPP;

	oldprog = cls_bpf->oldprog;

	/* Don't remove if oldprog doesn't match driver's state */
	अगर (ns->bpf_offloaded != oldprog) अणु
		oldprog = शून्य;
		अगर (!cls_bpf->prog)
			वापस 0;
		अगर (ns->bpf_offloaded) अणु
			NSIM_EA(cls_bpf->common.extack,
				"driver and netdev offload states mismatch");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस nsim_bpf_offload(ns, cls_bpf->prog, oldprog);
पूर्ण

पूर्णांक nsim_bpf_disable_tc(काष्ठा netdevsim *ns)
अणु
	अगर (ns->bpf_offloaded && !nsim_xdp_offload_active(ns))
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक nsim_xdp_offload_prog(काष्ठा netdevsim *ns, काष्ठा netdev_bpf *bpf)
अणु
	अगर (!nsim_xdp_offload_active(ns) && !bpf->prog)
		वापस 0;
	अगर (!nsim_xdp_offload_active(ns) && bpf->prog && ns->bpf_offloaded) अणु
		NSIM_EA(bpf->extack, "TC program is already loaded");
		वापस -EBUSY;
	पूर्ण

	वापस nsim_bpf_offload(ns, bpf->prog, nsim_xdp_offload_active(ns));
पूर्ण

अटल पूर्णांक
nsim_xdp_set_prog(काष्ठा netdevsim *ns, काष्ठा netdev_bpf *bpf,
		  काष्ठा xdp_attachment_info *xdp)
अणु
	पूर्णांक err;

	अगर (bpf->command == XDP_SETUP_PROG && !ns->bpf_xdpdrv_accept) अणु
		NSIM_EA(bpf->extack, "driver XDP disabled in DebugFS");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (bpf->command == XDP_SETUP_PROG_HW && !ns->bpf_xdpoffload_accept) अणु
		NSIM_EA(bpf->extack, "XDP offload disabled in DebugFS");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (bpf->command == XDP_SETUP_PROG_HW) अणु
		err = nsim_xdp_offload_prog(ns, bpf);
		अगर (err)
			वापस err;
	पूर्ण

	xdp_attachment_setup(xdp, bpf);

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_bpf_create_prog(काष्ठा nsim_dev *nsim_dev,
				काष्ठा bpf_prog *prog)
अणु
	काष्ठा nsim_bpf_bound_prog *state;
	अक्षर name[16];
	पूर्णांक ret;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->nsim_dev = nsim_dev;
	state->prog = prog;
	state->state = "verify";

	/* Program id is not populated yet when we create the state. */
	प्र_लिखो(name, "%u", nsim_dev->prog_id_gen++);
	state->ddir = debugfs_create_dir(name, nsim_dev->ddir_bpf_bound_progs);
	अगर (IS_ERR(state->ddir)) अणु
		ret = PTR_ERR(state->ddir);
		kमुक्त(state);
		वापस ret;
	पूर्ण

	debugfs_create_u32("id", 0400, state->ddir, &prog->aux->id);
	debugfs_create_file("state", 0400, state->ddir,
			    &state->state, &nsim_bpf_string_fops);
	debugfs_create_bool("loaded", 0400, state->ddir, &state->is_loaded);

	list_add_tail(&state->l, &nsim_dev->bpf_bound_progs);

	prog->aux->offload->dev_priv = state;

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_bpf_verअगरier_prep(काष्ठा bpf_prog *prog)
अणु
	काष्ठा nsim_dev *nsim_dev =
			bpf_offload_dev_priv(prog->aux->offload->offdev);

	अगर (!nsim_dev->bpf_bind_accept)
		वापस -EOPNOTSUPP;

	वापस nsim_bpf_create_prog(nsim_dev, prog);
पूर्ण

अटल पूर्णांक nsim_bpf_translate(काष्ठा bpf_prog *prog)
अणु
	काष्ठा nsim_bpf_bound_prog *state = prog->aux->offload->dev_priv;

	state->state = "xlated";
	वापस 0;
पूर्ण

अटल व्योम nsim_bpf_destroy_prog(काष्ठा bpf_prog *prog)
अणु
	काष्ठा nsim_bpf_bound_prog *state;

	state = prog->aux->offload->dev_priv;
	WARN(state->is_loaded,
	     "offload state destroyed while program still bound");
	debugfs_हटाओ_recursive(state->ddir);
	list_del(&state->l);
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा bpf_prog_offload_ops nsim_bpf_dev_ops = अणु
	.insn_hook	= nsim_bpf_verअगरy_insn,
	.finalize	= nsim_bpf_finalize,
	.prepare	= nsim_bpf_verअगरier_prep,
	.translate	= nsim_bpf_translate,
	.destroy	= nsim_bpf_destroy_prog,
पूर्ण;

अटल पूर्णांक nsim_setup_prog_checks(काष्ठा netdevsim *ns, काष्ठा netdev_bpf *bpf)
अणु
	अगर (bpf->prog && bpf->prog->aux->offload) अणु
		NSIM_EA(bpf->extack, "attempt to load offloaded prog to drv");
		वापस -EINVAL;
	पूर्ण
	अगर (ns->netdev->mtu > NSIM_XDP_MAX_MTU) अणु
		NSIM_EA(bpf->extack, "MTU too large w/ XDP enabled");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_setup_prog_hw_checks(काष्ठा netdevsim *ns, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा nsim_bpf_bound_prog *state;

	अगर (!bpf->prog)
		वापस 0;

	अगर (!bpf->prog->aux->offload) अणु
		NSIM_EA(bpf->extack, "xdpoffload of non-bound program");
		वापस -EINVAL;
	पूर्ण
	अगर (!bpf_offload_dev_match(bpf->prog, ns->netdev)) अणु
		NSIM_EA(bpf->extack, "program bound to different dev");
		वापस -EINVAL;
	पूर्ण

	state = bpf->prog->aux->offload->dev_priv;
	अगर (WARN_ON(म_भेद(state->state, "xlated"))) अणु
		NSIM_EA(bpf->extack, "offloading program in bad state");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool
nsim_map_key_match(काष्ठा bpf_map *map, काष्ठा nsim_map_entry *e, व्योम *key)
अणु
	वापस e->key && !स_भेद(key, e->key, map->key_size);
पूर्ण

अटल पूर्णांक nsim_map_key_find(काष्ठा bpf_offloaded_map *offmap, व्योम *key)
अणु
	काष्ठा nsim_bpf_bound_map *nmap = offmap->dev_priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nmap->entry); i++)
		अगर (nsim_map_key_match(&offmap->map, &nmap->entry[i], key))
			वापस i;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
nsim_map_alloc_elem(काष्ठा bpf_offloaded_map *offmap, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा nsim_bpf_bound_map *nmap = offmap->dev_priv;

	nmap->entry[idx].key = kदो_स्मृति(offmap->map.key_size, GFP_USER);
	अगर (!nmap->entry[idx].key)
		वापस -ENOMEM;
	nmap->entry[idx].value = kदो_स्मृति(offmap->map.value_size, GFP_USER);
	अगर (!nmap->entry[idx].value) अणु
		kमुक्त(nmap->entry[idx].key);
		nmap->entry[idx].key = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_map_get_next_key(काष्ठा bpf_offloaded_map *offmap,
		      व्योम *key, व्योम *next_key)
अणु
	काष्ठा nsim_bpf_bound_map *nmap = offmap->dev_priv;
	पूर्णांक idx = -ENOENT;

	mutex_lock(&nmap->mutex);

	अगर (key)
		idx = nsim_map_key_find(offmap, key);
	अगर (idx == -ENOENT)
		idx = 0;
	अन्यथा
		idx++;

	क्रम (; idx < ARRAY_SIZE(nmap->entry); idx++) अणु
		अगर (nmap->entry[idx].key) अणु
			स_नकल(next_key, nmap->entry[idx].key,
			       offmap->map.key_size);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&nmap->mutex);

	अगर (idx == ARRAY_SIZE(nmap->entry))
		वापस -ENOENT;
	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_map_lookup_elem(काष्ठा bpf_offloaded_map *offmap, व्योम *key, व्योम *value)
अणु
	काष्ठा nsim_bpf_bound_map *nmap = offmap->dev_priv;
	पूर्णांक idx;

	mutex_lock(&nmap->mutex);

	idx = nsim_map_key_find(offmap, key);
	अगर (idx >= 0)
		स_नकल(value, nmap->entry[idx].value, offmap->map.value_size);

	mutex_unlock(&nmap->mutex);

	वापस idx < 0 ? idx : 0;
पूर्ण

अटल पूर्णांक
nsim_map_update_elem(काष्ठा bpf_offloaded_map *offmap,
		     व्योम *key, व्योम *value, u64 flags)
अणु
	काष्ठा nsim_bpf_bound_map *nmap = offmap->dev_priv;
	पूर्णांक idx, err = 0;

	mutex_lock(&nmap->mutex);

	idx = nsim_map_key_find(offmap, key);
	अगर (idx < 0 && flags == BPF_EXIST) अणु
		err = idx;
		जाओ निकास_unlock;
	पूर्ण
	अगर (idx >= 0 && flags == BPF_NOEXIST) अणु
		err = -EEXIST;
		जाओ निकास_unlock;
	पूर्ण

	अगर (idx < 0) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(nmap->entry); idx++)
			अगर (!nmap->entry[idx].key)
				अवरोध;
		अगर (idx == ARRAY_SIZE(nmap->entry)) अणु
			err = -E2BIG;
			जाओ निकास_unlock;
		पूर्ण

		err = nsim_map_alloc_elem(offmap, idx);
		अगर (err)
			जाओ निकास_unlock;
	पूर्ण

	स_नकल(nmap->entry[idx].key, key, offmap->map.key_size);
	स_नकल(nmap->entry[idx].value, value, offmap->map.value_size);
निकास_unlock:
	mutex_unlock(&nmap->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक nsim_map_delete_elem(काष्ठा bpf_offloaded_map *offmap, व्योम *key)
अणु
	काष्ठा nsim_bpf_bound_map *nmap = offmap->dev_priv;
	पूर्णांक idx;

	अगर (offmap->map.map_type == BPF_MAP_TYPE_ARRAY)
		वापस -EINVAL;

	mutex_lock(&nmap->mutex);

	idx = nsim_map_key_find(offmap, key);
	अगर (idx >= 0) अणु
		kमुक्त(nmap->entry[idx].key);
		kमुक्त(nmap->entry[idx].value);
		स_रखो(&nmap->entry[idx], 0, माप(nmap->entry[idx]));
	पूर्ण

	mutex_unlock(&nmap->mutex);

	वापस idx < 0 ? idx : 0;
पूर्ण

अटल स्थिर काष्ठा bpf_map_dev_ops nsim_bpf_map_ops = अणु
	.map_get_next_key	= nsim_map_get_next_key,
	.map_lookup_elem	= nsim_map_lookup_elem,
	.map_update_elem	= nsim_map_update_elem,
	.map_delete_elem	= nsim_map_delete_elem,
पूर्ण;

अटल पूर्णांक
nsim_bpf_map_alloc(काष्ठा netdevsim *ns, काष्ठा bpf_offloaded_map *offmap)
अणु
	काष्ठा nsim_bpf_bound_map *nmap;
	पूर्णांक i, err;

	अगर (WARN_ON(offmap->map.map_type != BPF_MAP_TYPE_ARRAY &&
		    offmap->map.map_type != BPF_MAP_TYPE_HASH))
		वापस -EINVAL;
	अगर (offmap->map.max_entries > NSIM_BPF_MAX_KEYS)
		वापस -ENOMEM;
	अगर (offmap->map.map_flags)
		वापस -EINVAL;

	nmap = kzalloc(माप(*nmap), GFP_USER);
	अगर (!nmap)
		वापस -ENOMEM;

	offmap->dev_priv = nmap;
	nmap->ns = ns;
	nmap->map = offmap;
	mutex_init(&nmap->mutex);

	अगर (offmap->map.map_type == BPF_MAP_TYPE_ARRAY) अणु
		क्रम (i = 0; i < ARRAY_SIZE(nmap->entry); i++) अणु
			u32 *key;

			err = nsim_map_alloc_elem(offmap, i);
			अगर (err)
				जाओ err_मुक्त;
			key = nmap->entry[i].key;
			*key = i;
		पूर्ण
	पूर्ण

	offmap->dev_ops = &nsim_bpf_map_ops;
	list_add_tail(&nmap->l, &ns->nsim_dev->bpf_bound_maps);

	वापस 0;

err_मुक्त:
	जबतक (--i >= 0) अणु
		kमुक्त(nmap->entry[i].key);
		kमुक्त(nmap->entry[i].value);
	पूर्ण
	kमुक्त(nmap);
	वापस err;
पूर्ण

अटल व्योम nsim_bpf_map_मुक्त(काष्ठा bpf_offloaded_map *offmap)
अणु
	काष्ठा nsim_bpf_bound_map *nmap = offmap->dev_priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nmap->entry); i++) अणु
		kमुक्त(nmap->entry[i].key);
		kमुक्त(nmap->entry[i].value);
	पूर्ण
	list_del_init(&nmap->l);
	mutex_destroy(&nmap->mutex);
	kमुक्त(nmap);
पूर्ण

पूर्णांक nsim_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	पूर्णांक err;

	ASSERT_RTNL();

	चयन (bpf->command) अणु
	हाल XDP_SETUP_PROG:
		err = nsim_setup_prog_checks(ns, bpf);
		अगर (err)
			वापस err;

		वापस nsim_xdp_set_prog(ns, bpf, &ns->xdp);
	हाल XDP_SETUP_PROG_HW:
		err = nsim_setup_prog_hw_checks(ns, bpf);
		अगर (err)
			वापस err;

		वापस nsim_xdp_set_prog(ns, bpf, &ns->xdp_hw);
	हाल BPF_OFFLOAD_MAP_ALLOC:
		अगर (!ns->bpf_map_accept)
			वापस -EOPNOTSUPP;

		वापस nsim_bpf_map_alloc(ns, bpf->offmap);
	हाल BPF_OFFLOAD_MAP_FREE:
		nsim_bpf_map_मुक्त(bpf->offmap);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक nsim_bpf_dev_init(काष्ठा nsim_dev *nsim_dev)
अणु
	पूर्णांक err;

	INIT_LIST_HEAD(&nsim_dev->bpf_bound_progs);
	INIT_LIST_HEAD(&nsim_dev->bpf_bound_maps);

	nsim_dev->ddir_bpf_bound_progs = debugfs_create_dir("bpf_bound_progs",
							    nsim_dev->ddir);
	अगर (IS_ERR(nsim_dev->ddir_bpf_bound_progs))
		वापस PTR_ERR(nsim_dev->ddir_bpf_bound_progs);

	nsim_dev->bpf_dev = bpf_offload_dev_create(&nsim_bpf_dev_ops, nsim_dev);
	err = PTR_ERR_OR_ZERO(nsim_dev->bpf_dev);
	अगर (err)
		वापस err;

	nsim_dev->bpf_bind_accept = true;
	debugfs_create_bool("bpf_bind_accept", 0600, nsim_dev->ddir,
			    &nsim_dev->bpf_bind_accept);
	debugfs_create_u32("bpf_bind_verifier_delay", 0600, nsim_dev->ddir,
			   &nsim_dev->bpf_bind_verअगरier_delay);
	nsim_dev->bpf_bind_verअगरier_accept = true;
	debugfs_create_bool("bpf_bind_verifier_accept", 0600, nsim_dev->ddir,
			    &nsim_dev->bpf_bind_verअगरier_accept);
	वापस 0;
पूर्ण

व्योम nsim_bpf_dev_निकास(काष्ठा nsim_dev *nsim_dev)
अणु
	WARN_ON(!list_empty(&nsim_dev->bpf_bound_progs));
	WARN_ON(!list_empty(&nsim_dev->bpf_bound_maps));
	bpf_offload_dev_destroy(nsim_dev->bpf_dev);
पूर्ण

पूर्णांक nsim_bpf_init(काष्ठा netdevsim *ns)
अणु
	काष्ठा dentry *ddir = ns->nsim_dev_port->ddir;
	पूर्णांक err;

	err = bpf_offload_dev_netdev_रेजिस्टर(ns->nsim_dev->bpf_dev,
					      ns->netdev);
	अगर (err)
		वापस err;

	debugfs_create_u32("bpf_offloaded_id", 0400, ddir,
			   &ns->bpf_offloaded_id);

	ns->bpf_tc_accept = true;
	debugfs_create_bool("bpf_tc_accept", 0600, ddir,
			    &ns->bpf_tc_accept);
	debugfs_create_bool("bpf_tc_non_bound_accept", 0600, ddir,
			    &ns->bpf_tc_non_bound_accept);
	ns->bpf_xdpdrv_accept = true;
	debugfs_create_bool("bpf_xdpdrv_accept", 0600, ddir,
			    &ns->bpf_xdpdrv_accept);
	ns->bpf_xdpoffload_accept = true;
	debugfs_create_bool("bpf_xdpoffload_accept", 0600, ddir,
			    &ns->bpf_xdpoffload_accept);

	ns->bpf_map_accept = true;
	debugfs_create_bool("bpf_map_accept", 0600, ddir,
			    &ns->bpf_map_accept);

	वापस 0;
पूर्ण

व्योम nsim_bpf_uninit(काष्ठा netdevsim *ns)
अणु
	WARN_ON(ns->xdp.prog);
	WARN_ON(ns->xdp_hw.prog);
	WARN_ON(ns->bpf_offloaded);
	bpf_offload_dev_netdev_unरेजिस्टर(ns->nsim_dev->bpf_dev, ns->netdev);
पूर्ण
