<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RDMA resource limiting controller क्रम cgroups.
 *
 * Used to allow a cgroup hierarchy to stop processes from consuming
 * additional RDMA resources after a certain limit is reached.
 *
 * Copyright (C) 2016 Parav Pandit <pandit.parav@gmail.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/parser.h>
#समावेश <linux/cgroup_rdma.h>

#घोषणा RDMACG_MAX_STR "max"

/*
 * Protects list of resource pools मुख्यtained on per cgroup basis
 * and rdma device list.
 */
अटल DEFINE_MUTEX(rdmacg_mutex);
अटल LIST_HEAD(rdmacg_devices);

क्रमागत rdmacg_file_type अणु
	RDMACG_RESOURCE_TYPE_MAX,
	RDMACG_RESOURCE_TYPE_STAT,
पूर्ण;

/*
 * resource table definition as to be seen by the user.
 * Need to add entries to it when more resources are
 * added/defined at IB verb/core layer.
 */
अटल अक्षर स्थिर *rdmacg_resource_names[] = अणु
	[RDMACG_RESOURCE_HCA_HANDLE]	= "hca_handle",
	[RDMACG_RESOURCE_HCA_OBJECT]	= "hca_object",
पूर्ण;

/* resource tracker क्रम each resource of rdma cgroup */
काष्ठा rdmacg_resource अणु
	पूर्णांक max;
	पूर्णांक usage;
पूर्ण;

/*
 * resource pool object which represents per cgroup, per device
 * resources. There are multiple instances of this object per cgroup,
 * thereक्रमe it cannot be embedded within rdma_cgroup काष्ठाure. It
 * is मुख्यtained as list.
 */
काष्ठा rdmacg_resource_pool अणु
	काष्ठा rdmacg_device	*device;
	काष्ठा rdmacg_resource	resources[RDMACG_RESOURCE_MAX];

	काष्ठा list_head	cg_node;
	काष्ठा list_head	dev_node;

	/* count active user tasks of this pool */
	u64			usage_sum;
	/* total number counts which are set to max */
	पूर्णांक			num_max_cnt;
पूर्ण;

अटल काष्ठा rdma_cgroup *css_rdmacg(काष्ठा cgroup_subsys_state *css)
अणु
	वापस container_of(css, काष्ठा rdma_cgroup, css);
पूर्ण

अटल काष्ठा rdma_cgroup *parent_rdmacg(काष्ठा rdma_cgroup *cg)
अणु
	वापस css_rdmacg(cg->css.parent);
पूर्ण

अटल अंतरभूत काष्ठा rdma_cgroup *get_current_rdmacg(व्योम)
अणु
	वापस css_rdmacg(task_get_css(current, rdma_cgrp_id));
पूर्ण

अटल व्योम set_resource_limit(काष्ठा rdmacg_resource_pool *rpool,
			       पूर्णांक index, पूर्णांक new_max)
अणु
	अगर (new_max == S32_MAX) अणु
		अगर (rpool->resources[index].max != S32_MAX)
			rpool->num_max_cnt++;
	पूर्ण अन्यथा अणु
		अगर (rpool->resources[index].max == S32_MAX)
			rpool->num_max_cnt--;
	पूर्ण
	rpool->resources[index].max = new_max;
पूर्ण

अटल व्योम set_all_resource_max_limit(काष्ठा rdmacg_resource_pool *rpool)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RDMACG_RESOURCE_MAX; i++)
		set_resource_limit(rpool, i, S32_MAX);
पूर्ण

अटल व्योम मुक्त_cg_rpool_locked(काष्ठा rdmacg_resource_pool *rpool)
अणु
	lockdep_निश्चित_held(&rdmacg_mutex);

	list_del(&rpool->cg_node);
	list_del(&rpool->dev_node);
	kमुक्त(rpool);
पूर्ण

अटल काष्ठा rdmacg_resource_pool *
find_cg_rpool_locked(काष्ठा rdma_cgroup *cg,
		     काष्ठा rdmacg_device *device)

अणु
	काष्ठा rdmacg_resource_pool *pool;

	lockdep_निश्चित_held(&rdmacg_mutex);

	list_क्रम_each_entry(pool, &cg->rpools, cg_node)
		अगर (pool->device == device)
			वापस pool;

	वापस शून्य;
पूर्ण

अटल काष्ठा rdmacg_resource_pool *
get_cg_rpool_locked(काष्ठा rdma_cgroup *cg, काष्ठा rdmacg_device *device)
अणु
	काष्ठा rdmacg_resource_pool *rpool;

	rpool = find_cg_rpool_locked(cg, device);
	अगर (rpool)
		वापस rpool;

	rpool = kzalloc(माप(*rpool), GFP_KERNEL);
	अगर (!rpool)
		वापस ERR_PTR(-ENOMEM);

	rpool->device = device;
	set_all_resource_max_limit(rpool);

	INIT_LIST_HEAD(&rpool->cg_node);
	INIT_LIST_HEAD(&rpool->dev_node);
	list_add_tail(&rpool->cg_node, &cg->rpools);
	list_add_tail(&rpool->dev_node, &device->rpools);
	वापस rpool;
पूर्ण

/**
 * unअक्षरge_cg_locked - unअक्षरge resource क्रम rdma cgroup
 * @cg: poपूर्णांकer to cg to unअक्षरge and all parents in hierarchy
 * @device: poपूर्णांकer to rdmacg device
 * @index: index of the resource to unअक्षरge in cg (resource pool)
 *
 * It also मुक्तs the resource pool which was created as part of
 * अक्षरging operation when there are no resources attached to
 * resource pool.
 */
अटल व्योम
unअक्षरge_cg_locked(काष्ठा rdma_cgroup *cg,
		   काष्ठा rdmacg_device *device,
		   क्रमागत rdmacg_resource_type index)
अणु
	काष्ठा rdmacg_resource_pool *rpool;

	rpool = find_cg_rpool_locked(cg, device);

	/*
	 * rpool cannot be null at this stage. Let kernel operate in हाल
	 * अगर there a bug in IB stack or rdma controller, instead of crashing
	 * the प्रणाली.
	 */
	अगर (unlikely(!rpool)) अणु
		pr_warn("Invalid device %p or rdma cgroup %p\n", cg, device);
		वापस;
	पूर्ण

	rpool->resources[index].usage--;

	/*
	 * A negative count (or overflow) is invalid,
	 * it indicates a bug in the rdma controller.
	 */
	WARN_ON_ONCE(rpool->resources[index].usage < 0);
	rpool->usage_sum--;
	अगर (rpool->usage_sum == 0 &&
	    rpool->num_max_cnt == RDMACG_RESOURCE_MAX) अणु
		/*
		 * No user of the rpool and all entries are set to max, so
		 * safe to delete this rpool.
		 */
		मुक्त_cg_rpool_locked(rpool);
	पूर्ण
पूर्ण

/**
 * rdmacg_unअक्षरge_hierarchy - hierarchically unअक्षरge rdma resource count
 * @device: poपूर्णांकer to rdmacg device
 * @stop_cg: जबतक traversing hirerchy, when meet with stop_cg cgroup
 *           stop unअक्षरging
 * @index: index of the resource to unअक्षरge in cg in given resource pool
 */
अटल व्योम rdmacg_unअक्षरge_hierarchy(काष्ठा rdma_cgroup *cg,
				     काष्ठा rdmacg_device *device,
				     काष्ठा rdma_cgroup *stop_cg,
				     क्रमागत rdmacg_resource_type index)
अणु
	काष्ठा rdma_cgroup *p;

	mutex_lock(&rdmacg_mutex);

	क्रम (p = cg; p != stop_cg; p = parent_rdmacg(p))
		unअक्षरge_cg_locked(p, device, index);

	mutex_unlock(&rdmacg_mutex);

	css_put(&cg->css);
पूर्ण

/**
 * rdmacg_unअक्षरge - hierarchically unअक्षरge rdma resource count
 * @device: poपूर्णांकer to rdmacg device
 * @index: index of the resource to unअक्षरge in cgroup in given resource pool
 */
व्योम rdmacg_unअक्षरge(काष्ठा rdma_cgroup *cg,
		     काष्ठा rdmacg_device *device,
		     क्रमागत rdmacg_resource_type index)
अणु
	अगर (index >= RDMACG_RESOURCE_MAX)
		वापस;

	rdmacg_unअक्षरge_hierarchy(cg, device, शून्य, index);
पूर्ण
EXPORT_SYMBOL(rdmacg_unअक्षरge);

/**
 * rdmacg_try_अक्षरge - hierarchically try to अक्षरge the rdma resource
 * @rdmacg: poपूर्णांकer to rdma cgroup which will own this resource
 * @device: poपूर्णांकer to rdmacg device
 * @index: index of the resource to अक्षरge in cgroup (resource pool)
 *
 * This function follows अक्षरging resource in hierarchical way.
 * It will fail अगर the अक्षरge would cause the new value to exceed the
 * hierarchical limit.
 * Returns 0 अगर the अक्षरge succeeded, otherwise -EAGAIN, -ENOMEM or -EINVAL.
 * Returns poपूर्णांकer to rdmacg क्रम this resource when अक्षरging is successful.
 *
 * Charger needs to account resources on two criteria.
 * (a) per cgroup & (b) per device resource usage.
 * Per cgroup resource usage ensures that tasks of cgroup करोesn't cross
 * the configured limits. Per device provides granular configuration
 * in multi device usage. It allocates resource pool in the hierarchy
 * क्रम each parent it come across क्रम first resource. Later on resource
 * pool will be available. Thereक्रमe it will be much faster thereon
 * to अक्षरge/unअक्षरge.
 */
पूर्णांक rdmacg_try_अक्षरge(काष्ठा rdma_cgroup **rdmacg,
		      काष्ठा rdmacg_device *device,
		      क्रमागत rdmacg_resource_type index)
अणु
	काष्ठा rdma_cgroup *cg, *p;
	काष्ठा rdmacg_resource_pool *rpool;
	s64 new;
	पूर्णांक ret = 0;

	अगर (index >= RDMACG_RESOURCE_MAX)
		वापस -EINVAL;

	/*
	 * hold on to css, as cgroup can be हटाओd but resource
	 * accounting happens on css.
	 */
	cg = get_current_rdmacg();

	mutex_lock(&rdmacg_mutex);
	क्रम (p = cg; p; p = parent_rdmacg(p)) अणु
		rpool = get_cg_rpool_locked(p, device);
		अगर (IS_ERR(rpool)) अणु
			ret = PTR_ERR(rpool);
			जाओ err;
		पूर्ण अन्यथा अणु
			new = rpool->resources[index].usage + 1;
			अगर (new > rpool->resources[index].max) अणु
				ret = -EAGAIN;
				जाओ err;
			पूर्ण अन्यथा अणु
				rpool->resources[index].usage = new;
				rpool->usage_sum++;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&rdmacg_mutex);

	*rdmacg = cg;
	वापस 0;

err:
	mutex_unlock(&rdmacg_mutex);
	rdmacg_unअक्षरge_hierarchy(cg, device, p, index);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdmacg_try_अक्षरge);

/**
 * rdmacg_रेजिस्टर_device - रेजिस्टर rdmacg device to rdma controller.
 * @device: poपूर्णांकer to rdmacg device whose resources need to be accounted.
 *
 * If IB stack wish a device to participate in rdma cgroup resource
 * tracking, it must invoke this API to रेजिस्टर with rdma cgroup beक्रमe
 * any user space application can start using the RDMA resources.
 */
व्योम rdmacg_रेजिस्टर_device(काष्ठा rdmacg_device *device)
अणु
	INIT_LIST_HEAD(&device->dev_node);
	INIT_LIST_HEAD(&device->rpools);

	mutex_lock(&rdmacg_mutex);
	list_add_tail(&device->dev_node, &rdmacg_devices);
	mutex_unlock(&rdmacg_mutex);
पूर्ण
EXPORT_SYMBOL(rdmacg_रेजिस्टर_device);

/**
 * rdmacg_unरेजिस्टर_device - unरेजिस्टर rdmacg device from rdma controller.
 * @device: poपूर्णांकer to rdmacg device which was previously रेजिस्टरed with rdma
 *          controller using rdmacg_रेजिस्टर_device().
 *
 * IB stack must invoke this after all the resources of the IB device
 * are destroyed and after ensuring that no more resources will be created
 * when this API is invoked.
 */
व्योम rdmacg_unरेजिस्टर_device(काष्ठा rdmacg_device *device)
अणु
	काष्ठा rdmacg_resource_pool *rpool, *पंचांगp;

	/*
	 * Synchronize with any active resource settings,
	 * usage query happening via configfs.
	 */
	mutex_lock(&rdmacg_mutex);
	list_del_init(&device->dev_node);

	/*
	 * Now that this device is off the cgroup list, its safe to मुक्त
	 * all the rpool resources.
	 */
	list_क्रम_each_entry_safe(rpool, पंचांगp, &device->rpools, dev_node)
		मुक्त_cg_rpool_locked(rpool);

	mutex_unlock(&rdmacg_mutex);
पूर्ण
EXPORT_SYMBOL(rdmacg_unरेजिस्टर_device);

अटल पूर्णांक parse_resource(अक्षर *c, पूर्णांक *पूर्णांकval)
अणु
	substring_t argstr;
	अक्षर *name, *value = c;
	माप_प्रकार len;
	पूर्णांक ret, i;

	name = strsep(&value, "=");
	अगर (!name || !value)
		वापस -EINVAL;

	i = match_string(rdmacg_resource_names, RDMACG_RESOURCE_MAX, name);
	अगर (i < 0)
		वापस i;

	len = म_माप(value);

	argstr.from = value;
	argstr.to = value + len;

	ret = match_पूर्णांक(&argstr, पूर्णांकval);
	अगर (ret >= 0) अणु
		अगर (*पूर्णांकval < 0)
			वापस -EINVAL;
		वापस i;
	पूर्ण
	अगर (म_भेदन(value, RDMACG_MAX_STR, len) == 0) अणु
		*पूर्णांकval = S32_MAX;
		वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rdmacg_parse_limits(अक्षर *options,
			       पूर्णांक *new_limits, अचिन्हित दीर्घ *enables)
अणु
	अक्षर *c;
	पूर्णांक err = -EINVAL;

	/* parse resource options */
	जबतक ((c = strsep(&options, " ")) != शून्य) अणु
		पूर्णांक index, पूर्णांकval;

		index = parse_resource(c, &पूर्णांकval);
		अगर (index < 0)
			जाओ err;

		new_limits[index] = पूर्णांकval;
		*enables |= BIT(index);
	पूर्ण
	वापस 0;

err:
	वापस err;
पूर्ण

अटल काष्ठा rdmacg_device *rdmacg_get_device_locked(स्थिर अक्षर *name)
अणु
	काष्ठा rdmacg_device *device;

	lockdep_निश्चित_held(&rdmacg_mutex);

	list_क्रम_each_entry(device, &rdmacg_devices, dev_node)
		अगर (!म_भेद(name, device->name))
			वापस device;

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार rdmacg_resource_set_max(काष्ठा kernfs_खोलो_file *of,
				       अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा rdma_cgroup *cg = css_rdmacg(of_css(of));
	स्थिर अक्षर *dev_name;
	काष्ठा rdmacg_resource_pool *rpool;
	काष्ठा rdmacg_device *device;
	अक्षर *options = म_मालाip(buf);
	पूर्णांक *new_limits;
	अचिन्हित दीर्घ enables = 0;
	पूर्णांक i = 0, ret = 0;

	/* extract the device name first */
	dev_name = strsep(&options, " ");
	अगर (!dev_name) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	new_limits = kसुस्मृति(RDMACG_RESOURCE_MAX, माप(पूर्णांक), GFP_KERNEL);
	अगर (!new_limits) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = rdmacg_parse_limits(options, new_limits, &enables);
	अगर (ret)
		जाओ parse_err;

	/* acquire lock to synchronize with hot plug devices */
	mutex_lock(&rdmacg_mutex);

	device = rdmacg_get_device_locked(dev_name);
	अगर (!device) अणु
		ret = -ENODEV;
		जाओ dev_err;
	पूर्ण

	rpool = get_cg_rpool_locked(cg, device);
	अगर (IS_ERR(rpool)) अणु
		ret = PTR_ERR(rpool);
		जाओ dev_err;
	पूर्ण

	/* now set the new limits of the rpool */
	क्रम_each_set_bit(i, &enables, RDMACG_RESOURCE_MAX)
		set_resource_limit(rpool, i, new_limits[i]);

	अगर (rpool->usage_sum == 0 &&
	    rpool->num_max_cnt == RDMACG_RESOURCE_MAX) अणु
		/*
		 * No user of the rpool and all entries are set to max, so
		 * safe to delete this rpool.
		 */
		मुक्त_cg_rpool_locked(rpool);
	पूर्ण

dev_err:
	mutex_unlock(&rdmacg_mutex);

parse_err:
	kमुक्त(new_limits);

err:
	वापस ret ?: nbytes;
पूर्ण

अटल व्योम prपूर्णांक_rpool_values(काष्ठा seq_file *sf,
			       काष्ठा rdmacg_resource_pool *rpool)
अणु
	क्रमागत rdmacg_file_type sf_type;
	पूर्णांक i;
	u32 value;

	sf_type = seq_cft(sf)->निजी;

	क्रम (i = 0; i < RDMACG_RESOURCE_MAX; i++) अणु
		seq_माला_दो(sf, rdmacg_resource_names[i]);
		seq_अ_दो(sf, '=');
		अगर (sf_type == RDMACG_RESOURCE_TYPE_MAX) अणु
			अगर (rpool)
				value = rpool->resources[i].max;
			अन्यथा
				value = S32_MAX;
		पूर्ण अन्यथा अणु
			अगर (rpool)
				value = rpool->resources[i].usage;
			अन्यथा
				value = 0;
		पूर्ण

		अगर (value == S32_MAX)
			seq_माला_दो(sf, RDMACG_MAX_STR);
		अन्यथा
			seq_म_लिखो(sf, "%d", value);
		seq_अ_दो(sf, ' ');
	पूर्ण
पूर्ण

अटल पूर्णांक rdmacg_resource_पढ़ो(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा rdmacg_device *device;
	काष्ठा rdmacg_resource_pool *rpool;
	काष्ठा rdma_cgroup *cg = css_rdmacg(seq_css(sf));

	mutex_lock(&rdmacg_mutex);

	list_क्रम_each_entry(device, &rdmacg_devices, dev_node) अणु
		seq_म_लिखो(sf, "%s ", device->name);

		rpool = find_cg_rpool_locked(cg, device);
		prपूर्णांक_rpool_values(sf, rpool);

		seq_अ_दो(sf, '\n');
	पूर्ण

	mutex_unlock(&rdmacg_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा cftype rdmacg_files[] = अणु
	अणु
		.name = "max",
		.ग_लिखो = rdmacg_resource_set_max,
		.seq_show = rdmacg_resource_पढ़ो,
		.निजी = RDMACG_RESOURCE_TYPE_MAX,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,
	अणु
		.name = "current",
		.seq_show = rdmacg_resource_पढ़ो,
		.निजी = RDMACG_RESOURCE_TYPE_STAT,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

अटल काष्ठा cgroup_subsys_state *
rdmacg_css_alloc(काष्ठा cgroup_subsys_state *parent)
अणु
	काष्ठा rdma_cgroup *cg;

	cg = kzalloc(माप(*cg), GFP_KERNEL);
	अगर (!cg)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&cg->rpools);
	वापस &cg->css;
पूर्ण

अटल व्योम rdmacg_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा rdma_cgroup *cg = css_rdmacg(css);

	kमुक्त(cg);
पूर्ण

/**
 * rdmacg_css_offline - cgroup css_offline callback
 * @css: css of पूर्णांकerest
 *
 * This function is called when @css is about to go away and responsible
 * क्रम shooting करोwn all rdmacg associated with @css. As part of that it
 * marks all the resource pool entries to max value, so that when resources are
 * unअक्षरged, associated resource pool can be मुक्तd as well.
 */
अटल व्योम rdmacg_css_offline(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा rdma_cgroup *cg = css_rdmacg(css);
	काष्ठा rdmacg_resource_pool *rpool;

	mutex_lock(&rdmacg_mutex);

	list_क्रम_each_entry(rpool, &cg->rpools, cg_node)
		set_all_resource_max_limit(rpool);

	mutex_unlock(&rdmacg_mutex);
पूर्ण

काष्ठा cgroup_subsys rdma_cgrp_subsys = अणु
	.css_alloc	= rdmacg_css_alloc,
	.css_मुक्त	= rdmacg_css_मुक्त,
	.css_offline	= rdmacg_css_offline,
	.legacy_cftypes	= rdmacg_files,
	.dfl_cftypes	= rdmacg_files,
पूर्ण;
