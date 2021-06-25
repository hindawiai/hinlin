<शैली गुरु>
/*
 * Copyright (C) 2017-2018 Netronome Systems, Inc.
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
#समावेश <linux/bug.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/rwsem.h>

/* Protects offdevs, members of bpf_offload_netdev and offload members
 * of all progs.
 * RTNL lock cannot be taken when holding this lock.
 */
अटल DECLARE_RWSEM(bpf_devs_lock);

काष्ठा bpf_offload_dev अणु
	स्थिर काष्ठा bpf_prog_offload_ops *ops;
	काष्ठा list_head netdevs;
	व्योम *priv;
पूर्ण;

काष्ठा bpf_offload_netdev अणु
	काष्ठा rhash_head l;
	काष्ठा net_device *netdev;
	काष्ठा bpf_offload_dev *offdev;
	काष्ठा list_head progs;
	काष्ठा list_head maps;
	काष्ठा list_head offdev_netdevs;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params offdevs_params = अणु
	.nelem_hपूर्णांक		= 4,
	.key_len		= माप(काष्ठा net_device *),
	.key_offset		= दुरत्व(काष्ठा bpf_offload_netdev, netdev),
	.head_offset		= दुरत्व(काष्ठा bpf_offload_netdev, l),
	.स्वतःmatic_shrinking	= true,
पूर्ण;

अटल काष्ठा rhashtable offdevs;
अटल bool offdevs_inited;

अटल पूर्णांक bpf_dev_offload_check(काष्ठा net_device *netdev)
अणु
	अगर (!netdev)
		वापस -EINVAL;
	अगर (!netdev->netdev_ops->nकरो_bpf)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल काष्ठा bpf_offload_netdev *
bpf_offload_find_netdev(काष्ठा net_device *netdev)
अणु
	lockdep_निश्चित_held(&bpf_devs_lock);

	अगर (!offdevs_inited)
		वापस शून्य;
	वापस rhashtable_lookup_fast(&offdevs, &netdev, offdevs_params);
पूर्ण

पूर्णांक bpf_prog_offload_init(काष्ठा bpf_prog *prog, जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_offload_netdev *ondev;
	काष्ठा bpf_prog_offload *offload;
	पूर्णांक err;

	अगर (attr->prog_type != BPF_PROG_TYPE_SCHED_CLS &&
	    attr->prog_type != BPF_PROG_TYPE_XDP)
		वापस -EINVAL;

	अगर (attr->prog_flags)
		वापस -EINVAL;

	offload = kzalloc(माप(*offload), GFP_USER);
	अगर (!offload)
		वापस -ENOMEM;

	offload->prog = prog;

	offload->netdev = dev_get_by_index(current->nsproxy->net_ns,
					   attr->prog_अगरindex);
	err = bpf_dev_offload_check(offload->netdev);
	अगर (err)
		जाओ err_maybe_put;

	करोwn_ग_लिखो(&bpf_devs_lock);
	ondev = bpf_offload_find_netdev(offload->netdev);
	अगर (!ondev) अणु
		err = -EINVAL;
		जाओ err_unlock;
	पूर्ण
	offload->offdev = ondev->offdev;
	prog->aux->offload = offload;
	list_add_tail(&offload->offloads, &ondev->progs);
	dev_put(offload->netdev);
	up_ग_लिखो(&bpf_devs_lock);

	वापस 0;
err_unlock:
	up_ग_लिखो(&bpf_devs_lock);
err_maybe_put:
	अगर (offload->netdev)
		dev_put(offload->netdev);
	kमुक्त(offload);
	वापस err;
पूर्ण

पूर्णांक bpf_prog_offload_verअगरier_prep(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_offload *offload;
	पूर्णांक ret = -ENODEV;

	करोwn_पढ़ो(&bpf_devs_lock);
	offload = prog->aux->offload;
	अगर (offload) अणु
		ret = offload->offdev->ops->prepare(prog);
		offload->dev_state = !ret;
	पूर्ण
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

पूर्णांक bpf_prog_offload_verअगरy_insn(काष्ठा bpf_verअगरier_env *env,
				 पूर्णांक insn_idx, पूर्णांक prev_insn_idx)
अणु
	काष्ठा bpf_prog_offload *offload;
	पूर्णांक ret = -ENODEV;

	करोwn_पढ़ो(&bpf_devs_lock);
	offload = env->prog->aux->offload;
	अगर (offload)
		ret = offload->offdev->ops->insn_hook(env, insn_idx,
						      prev_insn_idx);
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

पूर्णांक bpf_prog_offload_finalize(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_prog_offload *offload;
	पूर्णांक ret = -ENODEV;

	करोwn_पढ़ो(&bpf_devs_lock);
	offload = env->prog->aux->offload;
	अगर (offload) अणु
		अगर (offload->offdev->ops->finalize)
			ret = offload->offdev->ops->finalize(env);
		अन्यथा
			ret = 0;
	पूर्ण
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

व्योम
bpf_prog_offload_replace_insn(काष्ठा bpf_verअगरier_env *env, u32 off,
			      काष्ठा bpf_insn *insn)
अणु
	स्थिर काष्ठा bpf_prog_offload_ops *ops;
	काष्ठा bpf_prog_offload *offload;
	पूर्णांक ret = -EOPNOTSUPP;

	करोwn_पढ़ो(&bpf_devs_lock);
	offload = env->prog->aux->offload;
	अगर (offload) अणु
		ops = offload->offdev->ops;
		अगर (!offload->opt_failed && ops->replace_insn)
			ret = ops->replace_insn(env, off, insn);
		offload->opt_failed |= ret;
	पूर्ण
	up_पढ़ो(&bpf_devs_lock);
पूर्ण

व्योम
bpf_prog_offload_हटाओ_insns(काष्ठा bpf_verअगरier_env *env, u32 off, u32 cnt)
अणु
	काष्ठा bpf_prog_offload *offload;
	पूर्णांक ret = -EOPNOTSUPP;

	करोwn_पढ़ो(&bpf_devs_lock);
	offload = env->prog->aux->offload;
	अगर (offload) अणु
		अगर (!offload->opt_failed && offload->offdev->ops->हटाओ_insns)
			ret = offload->offdev->ops->हटाओ_insns(env, off, cnt);
		offload->opt_failed |= ret;
	पूर्ण
	up_पढ़ो(&bpf_devs_lock);
पूर्ण

अटल व्योम __bpf_prog_offload_destroy(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_offload *offload = prog->aux->offload;

	अगर (offload->dev_state)
		offload->offdev->ops->destroy(prog);

	/* Make sure BPF_PROG_GET_NEXT_ID can't find this dead program */
	bpf_prog_मुक्त_id(prog, true);

	list_del_init(&offload->offloads);
	kमुक्त(offload);
	prog->aux->offload = शून्य;
पूर्ण

व्योम bpf_prog_offload_destroy(काष्ठा bpf_prog *prog)
अणु
	करोwn_ग_लिखो(&bpf_devs_lock);
	अगर (prog->aux->offload)
		__bpf_prog_offload_destroy(prog);
	up_ग_लिखो(&bpf_devs_lock);
पूर्ण

अटल पूर्णांक bpf_prog_offload_translate(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_offload *offload;
	पूर्णांक ret = -ENODEV;

	करोwn_पढ़ो(&bpf_devs_lock);
	offload = prog->aux->offload;
	अगर (offload)
		ret = offload->offdev->ops->translate(prog);
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक bpf_prog_warn_on_exec(स्थिर व्योम *ctx,
					  स्थिर काष्ठा bpf_insn *insn)
अणु
	WARN(1, "attempt to execute device eBPF program on the host!");
	वापस 0;
पूर्ण

पूर्णांक bpf_prog_offload_compile(काष्ठा bpf_prog *prog)
अणु
	prog->bpf_func = bpf_prog_warn_on_exec;

	वापस bpf_prog_offload_translate(prog);
पूर्ण

काष्ठा ns_get_path_bpf_prog_args अणु
	काष्ठा bpf_prog *prog;
	काष्ठा bpf_prog_info *info;
पूर्ण;

अटल काष्ठा ns_common *bpf_prog_offload_info_fill_ns(व्योम *निजी_data)
अणु
	काष्ठा ns_get_path_bpf_prog_args *args = निजी_data;
	काष्ठा bpf_prog_aux *aux = args->prog->aux;
	काष्ठा ns_common *ns;
	काष्ठा net *net;

	rtnl_lock();
	करोwn_पढ़ो(&bpf_devs_lock);

	अगर (aux->offload) अणु
		args->info->अगरindex = aux->offload->netdev->अगरindex;
		net = dev_net(aux->offload->netdev);
		get_net(net);
		ns = &net->ns;
	पूर्ण अन्यथा अणु
		args->info->अगरindex = 0;
		ns = शून्य;
	पूर्ण

	up_पढ़ो(&bpf_devs_lock);
	rtnl_unlock();

	वापस ns;
पूर्ण

पूर्णांक bpf_prog_offload_info_fill(काष्ठा bpf_prog_info *info,
			       काष्ठा bpf_prog *prog)
अणु
	काष्ठा ns_get_path_bpf_prog_args args = अणु
		.prog	= prog,
		.info	= info,
	पूर्ण;
	काष्ठा bpf_prog_aux *aux = prog->aux;
	काष्ठा inode *ns_inode;
	काष्ठा path ns_path;
	अक्षर __user *uinsns;
	पूर्णांक res;
	u32 ulen;

	res = ns_get_path_cb(&ns_path, bpf_prog_offload_info_fill_ns, &args);
	अगर (res) अणु
		अगर (!info->अगरindex)
			वापस -ENODEV;
		वापस res;
	पूर्ण

	करोwn_पढ़ो(&bpf_devs_lock);

	अगर (!aux->offload) अणु
		up_पढ़ो(&bpf_devs_lock);
		वापस -ENODEV;
	पूर्ण

	ulen = info->jited_prog_len;
	info->jited_prog_len = aux->offload->jited_len;
	अगर (info->jited_prog_len && ulen) अणु
		uinsns = u64_to_user_ptr(info->jited_prog_insns);
		ulen = min_t(u32, info->jited_prog_len, ulen);
		अगर (copy_to_user(uinsns, aux->offload->jited_image, ulen)) अणु
			up_पढ़ो(&bpf_devs_lock);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	up_पढ़ो(&bpf_devs_lock);

	ns_inode = ns_path.dentry->d_inode;
	info->netns_dev = new_encode_dev(ns_inode->i_sb->s_dev);
	info->netns_ino = ns_inode->i_ino;
	path_put(&ns_path);

	वापस 0;
पूर्ण

स्थिर काष्ठा bpf_prog_ops bpf_offload_prog_ops = अणु
पूर्ण;

अटल पूर्णांक bpf_map_offload_nकरो(काष्ठा bpf_offloaded_map *offmap,
			       क्रमागत bpf_netdev_command cmd)
अणु
	काष्ठा netdev_bpf data = अणुपूर्ण;
	काष्ठा net_device *netdev;

	ASSERT_RTNL();

	data.command = cmd;
	data.offmap = offmap;
	/* Caller must make sure netdev is valid */
	netdev = offmap->netdev;

	वापस netdev->netdev_ops->nकरो_bpf(netdev, &data);
पूर्ण

काष्ठा bpf_map *bpf_map_offload_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	काष्ठा bpf_offload_netdev *ondev;
	काष्ठा bpf_offloaded_map *offmap;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस ERR_PTR(-EPERM);
	अगर (attr->map_type != BPF_MAP_TYPE_ARRAY &&
	    attr->map_type != BPF_MAP_TYPE_HASH)
		वापस ERR_PTR(-EINVAL);

	offmap = kzalloc(माप(*offmap), GFP_USER);
	अगर (!offmap)
		वापस ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&offmap->map, attr);

	rtnl_lock();
	करोwn_ग_लिखो(&bpf_devs_lock);
	offmap->netdev = __dev_get_by_index(net, attr->map_अगरindex);
	err = bpf_dev_offload_check(offmap->netdev);
	अगर (err)
		जाओ err_unlock;

	ondev = bpf_offload_find_netdev(offmap->netdev);
	अगर (!ondev) अणु
		err = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	err = bpf_map_offload_nकरो(offmap, BPF_OFFLOAD_MAP_ALLOC);
	अगर (err)
		जाओ err_unlock;

	list_add_tail(&offmap->offloads, &ondev->maps);
	up_ग_लिखो(&bpf_devs_lock);
	rtnl_unlock();

	वापस &offmap->map;

err_unlock:
	up_ग_लिखो(&bpf_devs_lock);
	rtnl_unlock();
	kमुक्त(offmap);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम __bpf_map_offload_destroy(काष्ठा bpf_offloaded_map *offmap)
अणु
	WARN_ON(bpf_map_offload_nकरो(offmap, BPF_OFFLOAD_MAP_FREE));
	/* Make sure BPF_MAP_GET_NEXT_ID can't find this dead map */
	bpf_map_मुक्त_id(&offmap->map, true);
	list_del_init(&offmap->offloads);
	offmap->netdev = शून्य;
पूर्ण

व्योम bpf_map_offload_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_offloaded_map *offmap = map_to_offmap(map);

	rtnl_lock();
	करोwn_ग_लिखो(&bpf_devs_lock);
	अगर (offmap->netdev)
		__bpf_map_offload_destroy(offmap);
	up_ग_लिखो(&bpf_devs_lock);
	rtnl_unlock();

	kमुक्त(offmap);
पूर्ण

पूर्णांक bpf_map_offload_lookup_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value)
अणु
	काष्ठा bpf_offloaded_map *offmap = map_to_offmap(map);
	पूर्णांक ret = -ENODEV;

	करोwn_पढ़ो(&bpf_devs_lock);
	अगर (offmap->netdev)
		ret = offmap->dev_ops->map_lookup_elem(offmap, key, value);
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

पूर्णांक bpf_map_offload_update_elem(काष्ठा bpf_map *map,
				व्योम *key, व्योम *value, u64 flags)
अणु
	काष्ठा bpf_offloaded_map *offmap = map_to_offmap(map);
	पूर्णांक ret = -ENODEV;

	अगर (unlikely(flags > BPF_EXIST))
		वापस -EINVAL;

	करोwn_पढ़ो(&bpf_devs_lock);
	अगर (offmap->netdev)
		ret = offmap->dev_ops->map_update_elem(offmap, key, value,
						       flags);
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

पूर्णांक bpf_map_offload_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_offloaded_map *offmap = map_to_offmap(map);
	पूर्णांक ret = -ENODEV;

	करोwn_पढ़ो(&bpf_devs_lock);
	अगर (offmap->netdev)
		ret = offmap->dev_ops->map_delete_elem(offmap, key);
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

पूर्णांक bpf_map_offload_get_next_key(काष्ठा bpf_map *map, व्योम *key, व्योम *next_key)
अणु
	काष्ठा bpf_offloaded_map *offmap = map_to_offmap(map);
	पूर्णांक ret = -ENODEV;

	करोwn_पढ़ो(&bpf_devs_lock);
	अगर (offmap->netdev)
		ret = offmap->dev_ops->map_get_next_key(offmap, key, next_key);
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

काष्ठा ns_get_path_bpf_map_args अणु
	काष्ठा bpf_offloaded_map *offmap;
	काष्ठा bpf_map_info *info;
पूर्ण;

अटल काष्ठा ns_common *bpf_map_offload_info_fill_ns(व्योम *निजी_data)
अणु
	काष्ठा ns_get_path_bpf_map_args *args = निजी_data;
	काष्ठा ns_common *ns;
	काष्ठा net *net;

	rtnl_lock();
	करोwn_पढ़ो(&bpf_devs_lock);

	अगर (args->offmap->netdev) अणु
		args->info->अगरindex = args->offmap->netdev->अगरindex;
		net = dev_net(args->offmap->netdev);
		get_net(net);
		ns = &net->ns;
	पूर्ण अन्यथा अणु
		args->info->अगरindex = 0;
		ns = शून्य;
	पूर्ण

	up_पढ़ो(&bpf_devs_lock);
	rtnl_unlock();

	वापस ns;
पूर्ण

पूर्णांक bpf_map_offload_info_fill(काष्ठा bpf_map_info *info, काष्ठा bpf_map *map)
अणु
	काष्ठा ns_get_path_bpf_map_args args = अणु
		.offmap	= map_to_offmap(map),
		.info	= info,
	पूर्ण;
	काष्ठा inode *ns_inode;
	काष्ठा path ns_path;
	पूर्णांक res;

	res = ns_get_path_cb(&ns_path, bpf_map_offload_info_fill_ns, &args);
	अगर (res) अणु
		अगर (!info->अगरindex)
			वापस -ENODEV;
		वापस res;
	पूर्ण

	ns_inode = ns_path.dentry->d_inode;
	info->netns_dev = new_encode_dev(ns_inode->i_sb->s_dev);
	info->netns_ino = ns_inode->i_ino;
	path_put(&ns_path);

	वापस 0;
पूर्ण

अटल bool __bpf_offload_dev_match(काष्ठा bpf_prog *prog,
				    काष्ठा net_device *netdev)
अणु
	काष्ठा bpf_offload_netdev *ondev1, *ondev2;
	काष्ठा bpf_prog_offload *offload;

	अगर (!bpf_prog_is_dev_bound(prog->aux))
		वापस false;

	offload = prog->aux->offload;
	अगर (!offload)
		वापस false;
	अगर (offload->netdev == netdev)
		वापस true;

	ondev1 = bpf_offload_find_netdev(offload->netdev);
	ondev2 = bpf_offload_find_netdev(netdev);

	वापस ondev1 && ondev2 && ondev1->offdev == ondev2->offdev;
पूर्ण

bool bpf_offload_dev_match(काष्ठा bpf_prog *prog, काष्ठा net_device *netdev)
अणु
	bool ret;

	करोwn_पढ़ो(&bpf_devs_lock);
	ret = __bpf_offload_dev_match(prog, netdev);
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_offload_dev_match);

bool bpf_offload_prog_map_match(काष्ठा bpf_prog *prog, काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_offloaded_map *offmap;
	bool ret;

	अगर (!bpf_map_is_dev_bound(map))
		वापस bpf_map_offload_neutral(map);
	offmap = map_to_offmap(map);

	करोwn_पढ़ो(&bpf_devs_lock);
	ret = __bpf_offload_dev_match(prog, offmap->netdev);
	up_पढ़ो(&bpf_devs_lock);

	वापस ret;
पूर्ण

पूर्णांक bpf_offload_dev_netdev_रेजिस्टर(काष्ठा bpf_offload_dev *offdev,
				    काष्ठा net_device *netdev)
अणु
	काष्ठा bpf_offload_netdev *ondev;
	पूर्णांक err;

	ondev = kzalloc(माप(*ondev), GFP_KERNEL);
	अगर (!ondev)
		वापस -ENOMEM;

	ondev->netdev = netdev;
	ondev->offdev = offdev;
	INIT_LIST_HEAD(&ondev->progs);
	INIT_LIST_HEAD(&ondev->maps);

	करोwn_ग_लिखो(&bpf_devs_lock);
	err = rhashtable_insert_fast(&offdevs, &ondev->l, offdevs_params);
	अगर (err) अणु
		netdev_warn(netdev, "failed to register for BPF offload\n");
		जाओ err_unlock_मुक्त;
	पूर्ण

	list_add(&ondev->offdev_netdevs, &offdev->netdevs);
	up_ग_लिखो(&bpf_devs_lock);
	वापस 0;

err_unlock_मुक्त:
	up_ग_लिखो(&bpf_devs_lock);
	kमुक्त(ondev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_offload_dev_netdev_रेजिस्टर);

व्योम bpf_offload_dev_netdev_unरेजिस्टर(काष्ठा bpf_offload_dev *offdev,
				       काष्ठा net_device *netdev)
अणु
	काष्ठा bpf_offload_netdev *ondev, *altdev;
	काष्ठा bpf_offloaded_map *offmap, *mपंचांगp;
	काष्ठा bpf_prog_offload *offload, *pपंचांगp;

	ASSERT_RTNL();

	करोwn_ग_लिखो(&bpf_devs_lock);
	ondev = rhashtable_lookup_fast(&offdevs, &netdev, offdevs_params);
	अगर (WARN_ON(!ondev))
		जाओ unlock;

	WARN_ON(rhashtable_हटाओ_fast(&offdevs, &ondev->l, offdevs_params));
	list_del(&ondev->offdev_netdevs);

	/* Try to move the objects to another netdev of the device */
	altdev = list_first_entry_or_null(&offdev->netdevs,
					  काष्ठा bpf_offload_netdev,
					  offdev_netdevs);
	अगर (altdev) अणु
		list_क्रम_each_entry(offload, &ondev->progs, offloads)
			offload->netdev = altdev->netdev;
		list_splice_init(&ondev->progs, &altdev->progs);

		list_क्रम_each_entry(offmap, &ondev->maps, offloads)
			offmap->netdev = altdev->netdev;
		list_splice_init(&ondev->maps, &altdev->maps);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_safe(offload, pपंचांगp, &ondev->progs, offloads)
			__bpf_prog_offload_destroy(offload->prog);
		list_क्रम_each_entry_safe(offmap, mपंचांगp, &ondev->maps, offloads)
			__bpf_map_offload_destroy(offmap);
	पूर्ण

	WARN_ON(!list_empty(&ondev->progs));
	WARN_ON(!list_empty(&ondev->maps));
	kमुक्त(ondev);
unlock:
	up_ग_लिखो(&bpf_devs_lock);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_offload_dev_netdev_unरेजिस्टर);

काष्ठा bpf_offload_dev *
bpf_offload_dev_create(स्थिर काष्ठा bpf_prog_offload_ops *ops, व्योम *priv)
अणु
	काष्ठा bpf_offload_dev *offdev;
	पूर्णांक err;

	करोwn_ग_लिखो(&bpf_devs_lock);
	अगर (!offdevs_inited) अणु
		err = rhashtable_init(&offdevs, &offdevs_params);
		अगर (err) अणु
			up_ग_लिखो(&bpf_devs_lock);
			वापस ERR_PTR(err);
		पूर्ण
		offdevs_inited = true;
	पूर्ण
	up_ग_लिखो(&bpf_devs_lock);

	offdev = kzalloc(माप(*offdev), GFP_KERNEL);
	अगर (!offdev)
		वापस ERR_PTR(-ENOMEM);

	offdev->ops = ops;
	offdev->priv = priv;
	INIT_LIST_HEAD(&offdev->netdevs);

	वापस offdev;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_offload_dev_create);

व्योम bpf_offload_dev_destroy(काष्ठा bpf_offload_dev *offdev)
अणु
	WARN_ON(!list_empty(&offdev->netdevs));
	kमुक्त(offdev);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_offload_dev_destroy);

व्योम *bpf_offload_dev_priv(काष्ठा bpf_offload_dev *offdev)
अणु
	वापस offdev->priv;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_offload_dev_priv);
