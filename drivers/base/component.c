<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Componentized device handling.
 *
 * This is work in progress.  We gather up the component devices पूर्णांकo a list,
 * and bind them when inकाष्ठाed.  At the moment, we're specअगरic to the DRM
 * subप्रणाली, and only handles one master device, but this करोesn't have to be
 * the हाल.
 */
#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>

/**
 * DOC: overview
 *
 * The component helper allows drivers to collect a pile of sub-devices,
 * including their bound drivers, पूर्णांकo an aggregate driver. Various subप्रणालीs
 * alपढ़ोy provide functions to get hold of such components, e.g.
 * of_clk_get_by_name(). The component helper can be used when such a
 * subप्रणाली-specअगरic way to find a device is not available: The component
 * helper fills the niche of aggregate drivers क्रम specअगरic hardware, where
 * further standardization पूर्णांकo a subप्रणाली would not be practical. The common
 * example is when a logical device (e.g. a DRM display driver) is spपढ़ो around
 * the SoC on various components (scanout engines, blending blocks, transcoders
 * क्रम various outमाला_दो and so on).
 *
 * The component helper also करोesn't solve runसमय dependencies, e.g. क्रम प्रणाली
 * suspend and resume operations. See also :ref:`device links<device_link>`.
 *
 * Components are रेजिस्टरed using component_add() and unरेजिस्टरed with
 * component_del(), usually from the driver's probe and disconnect functions.
 *
 * Aggregate drivers first assemble a component match list of what they need
 * using component_match_add(). This is then रेजिस्टरed as an aggregate driver
 * using component_master_add_with_match(), and unरेजिस्टरed using
 * component_master_del().
 */

काष्ठा component;

काष्ठा component_match_array अणु
	व्योम *data;
	पूर्णांक (*compare)(काष्ठा device *, व्योम *);
	पूर्णांक (*compare_typed)(काष्ठा device *, पूर्णांक, व्योम *);
	व्योम (*release)(काष्ठा device *, व्योम *);
	काष्ठा component *component;
	bool duplicate;
पूर्ण;

काष्ठा component_match अणु
	माप_प्रकार alloc;
	माप_प्रकार num;
	काष्ठा component_match_array *compare;
पूर्ण;

काष्ठा master अणु
	काष्ठा list_head node;
	bool bound;

	स्थिर काष्ठा component_master_ops *ops;
	काष्ठा device *dev;
	काष्ठा component_match *match;
पूर्ण;

काष्ठा component अणु
	काष्ठा list_head node;
	काष्ठा master *master;
	bool bound;

	स्थिर काष्ठा component_ops *ops;
	पूर्णांक subcomponent;
	काष्ठा device *dev;
पूर्ण;

अटल DEFINE_MUTEX(component_mutex);
अटल LIST_HEAD(component_list);
अटल LIST_HEAD(masters);

#अगर_घोषित CONFIG_DEBUG_FS

अटल काष्ठा dentry *component_debugfs_dir;

अटल पूर्णांक component_devices_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा master *m = s->निजी;
	काष्ठा component_match *match = m->match;
	माप_प्रकार i;

	mutex_lock(&component_mutex);
	seq_म_लिखो(s, "%-40s %20s\n", "master name", "status");
	seq_माला_दो(s, "-------------------------------------------------------------\n");
	seq_म_लिखो(s, "%-40s %20s\n\n",
		   dev_name(m->dev), m->bound ? "bound" : "not bound");

	seq_म_लिखो(s, "%-40s %20s\n", "device name", "status");
	seq_माला_दो(s, "-------------------------------------------------------------\n");
	क्रम (i = 0; i < match->num; i++) अणु
		काष्ठा component *component = match->compare[i].component;

		seq_म_लिखो(s, "%-40s %20s\n",
			   component ? dev_name(component->dev) : "(unknown)",
			   component ? (component->bound ? "bound" : "not bound") : "not registered");
	पूर्ण
	mutex_unlock(&component_mutex);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(component_devices);

अटल पूर्णांक __init component_debug_init(व्योम)
अणु
	component_debugfs_dir = debugfs_create_dir("device_component", शून्य);

	वापस 0;
पूर्ण

core_initcall(component_debug_init);

अटल व्योम component_master_debugfs_add(काष्ठा master *m)
अणु
	debugfs_create_file(dev_name(m->dev), 0444, component_debugfs_dir, m,
			    &component_devices_fops);
पूर्ण

अटल व्योम component_master_debugfs_del(काष्ठा master *m)
अणु
	debugfs_हटाओ(debugfs_lookup(dev_name(m->dev), component_debugfs_dir));
पूर्ण

#अन्यथा

अटल व्योम component_master_debugfs_add(काष्ठा master *m)
अणु पूर्ण

अटल व्योम component_master_debugfs_del(काष्ठा master *m)
अणु पूर्ण

#पूर्ण_अगर

अटल काष्ठा master *__master_find(काष्ठा device *dev,
	स्थिर काष्ठा component_master_ops *ops)
अणु
	काष्ठा master *m;

	list_क्रम_each_entry(m, &masters, node)
		अगर (m->dev == dev && (!ops || m->ops == ops))
			वापस m;

	वापस शून्य;
पूर्ण

अटल काष्ठा component *find_component(काष्ठा master *master,
	काष्ठा component_match_array *mc)
अणु
	काष्ठा component *c;

	list_क्रम_each_entry(c, &component_list, node) अणु
		अगर (c->master && c->master != master)
			जारी;

		अगर (mc->compare && mc->compare(c->dev, mc->data))
			वापस c;

		अगर (mc->compare_typed &&
		    mc->compare_typed(c->dev, c->subcomponent, mc->data))
			वापस c;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक find_components(काष्ठा master *master)
अणु
	काष्ठा component_match *match = master->match;
	माप_प्रकार i;
	पूर्णांक ret = 0;

	/*
	 * Scan the array of match functions and attach
	 * any components which are found to this master.
	 */
	क्रम (i = 0; i < match->num; i++) अणु
		काष्ठा component_match_array *mc = &match->compare[i];
		काष्ठा component *c;

		dev_dbg(master->dev, "Looking for component %zu\n", i);

		अगर (match->compare[i].component)
			जारी;

		c = find_component(master, mc);
		अगर (!c) अणु
			ret = -ENXIO;
			अवरोध;
		पूर्ण

		dev_dbg(master->dev, "found component %s, duplicate %u\n", dev_name(c->dev), !!c->master);

		/* Attach this component to the master */
		match->compare[i].duplicate = !!c->master;
		match->compare[i].component = c;
		c->master = master;
	पूर्ण
	वापस ret;
पूर्ण

/* Detach component from associated master */
अटल व्योम हटाओ_component(काष्ठा master *master, काष्ठा component *c)
अणु
	माप_प्रकार i;

	/* Detach the component from this master. */
	क्रम (i = 0; i < master->match->num; i++)
		अगर (master->match->compare[i].component == c)
			master->match->compare[i].component = शून्य;
पूर्ण

/*
 * Try to bring up a master.  If component is शून्य, we're पूर्णांकerested in
 * this master, otherwise it's a component which must be present to try
 * and bring up the master.
 *
 * Returns 1 क्रम successful bringup, 0 अगर not पढ़ोy, or -ve त्रुटि_सं.
 */
अटल पूर्णांक try_to_bring_up_master(काष्ठा master *master,
	काष्ठा component *component)
अणु
	पूर्णांक ret;

	dev_dbg(master->dev, "trying to bring up master\n");

	अगर (find_components(master)) अणु
		dev_dbg(master->dev, "master has incomplete components\n");
		वापस 0;
	पूर्ण

	अगर (component && component->master != master) अणु
		dev_dbg(master->dev, "master is not for this component (%s)\n",
			dev_name(component->dev));
		वापस 0;
	पूर्ण

	अगर (!devres_खोलो_group(master->dev, शून्य, GFP_KERNEL))
		वापस -ENOMEM;

	/* Found all components */
	ret = master->ops->bind(master->dev);
	अगर (ret < 0) अणु
		devres_release_group(master->dev, शून्य);
		अगर (ret != -EPROBE_DEFER)
			dev_info(master->dev, "master bind failed: %d\n", ret);
		वापस ret;
	पूर्ण

	master->bound = true;
	वापस 1;
पूर्ण

अटल पूर्णांक try_to_bring_up_masters(काष्ठा component *component)
अणु
	काष्ठा master *m;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(m, &masters, node) अणु
		अगर (!m->bound) अणु
			ret = try_to_bring_up_master(m, component);
			अगर (ret != 0)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम take_करोwn_master(काष्ठा master *master)
अणु
	अगर (master->bound) अणु
		master->ops->unbind(master->dev);
		devres_release_group(master->dev, शून्य);
		master->bound = false;
	पूर्ण
पूर्ण

अटल व्योम component_match_release(काष्ठा device *master,
	काष्ठा component_match *match)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < match->num; i++) अणु
		काष्ठा component_match_array *mc = &match->compare[i];

		अगर (mc->release)
			mc->release(master, mc->data);
	पूर्ण

	kमुक्त(match->compare);
पूर्ण

अटल व्योम devm_component_match_release(काष्ठा device *dev, व्योम *res)
अणु
	component_match_release(dev, res);
पूर्ण

अटल पूर्णांक component_match_पुनः_स्मृति(काष्ठा device *dev,
	काष्ठा component_match *match, माप_प्रकार num)
अणु
	काष्ठा component_match_array *new;

	अगर (match->alloc == num)
		वापस 0;

	new = kदो_स्मृति_array(num, माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	अगर (match->compare) अणु
		स_नकल(new, match->compare, माप(*new) *
					    min(match->num, num));
		kमुक्त(match->compare);
	पूर्ण
	match->compare = new;
	match->alloc = num;

	वापस 0;
पूर्ण

अटल व्योम __component_match_add(काष्ठा device *master,
	काष्ठा component_match **matchptr,
	व्योम (*release)(काष्ठा device *, व्योम *),
	पूर्णांक (*compare)(काष्ठा device *, व्योम *),
	पूर्णांक (*compare_typed)(काष्ठा device *, पूर्णांक, व्योम *),
	व्योम *compare_data)
अणु
	काष्ठा component_match *match = *matchptr;

	अगर (IS_ERR(match))
		वापस;

	अगर (!match) अणु
		match = devres_alloc(devm_component_match_release,
				     माप(*match), GFP_KERNEL);
		अगर (!match) अणु
			*matchptr = ERR_PTR(-ENOMEM);
			वापस;
		पूर्ण

		devres_add(master, match);

		*matchptr = match;
	पूर्ण

	अगर (match->num == match->alloc) अणु
		माप_प्रकार new_size = match->alloc + 16;
		पूर्णांक ret;

		ret = component_match_पुनः_स्मृति(master, match, new_size);
		अगर (ret) अणु
			*matchptr = ERR_PTR(ret);
			वापस;
		पूर्ण
	पूर्ण

	match->compare[match->num].compare = compare;
	match->compare[match->num].compare_typed = compare_typed;
	match->compare[match->num].release = release;
	match->compare[match->num].data = compare_data;
	match->compare[match->num].component = शून्य;
	match->num++;
पूर्ण

/**
 * component_match_add_release - add a component match entry with release callback
 * @master: device with the aggregate driver
 * @matchptr: poपूर्णांकer to the list of component matches
 * @release: release function क्रम @compare_data
 * @compare: compare function to match against all components
 * @compare_data: opaque poपूर्णांकer passed to the @compare function
 *
 * Adds a new component match to the list stored in @matchptr, which the @master
 * aggregate driver needs to function. The list of component matches poपूर्णांकed to
 * by @matchptr must be initialized to शून्य beक्रमe adding the first match. This
 * only matches against components added with component_add().
 *
 * The allocated match list in @matchptr is स्वतःmatically released using devm
 * actions, where upon @release will be called to मुक्त any references held by
 * @compare_data, e.g. when @compare_data is a &device_node that must be
 * released with of_node_put().
 *
 * See also component_match_add() and component_match_add_typed().
 */
व्योम component_match_add_release(काष्ठा device *master,
	काष्ठा component_match **matchptr,
	व्योम (*release)(काष्ठा device *, व्योम *),
	पूर्णांक (*compare)(काष्ठा device *, व्योम *), व्योम *compare_data)
अणु
	__component_match_add(master, matchptr, release, compare, शून्य,
			      compare_data);
पूर्ण
EXPORT_SYMBOL(component_match_add_release);

/**
 * component_match_add_typed - add a component match entry क्रम a typed component
 * @master: device with the aggregate driver
 * @matchptr: poपूर्णांकer to the list of component matches
 * @compare_typed: compare function to match against all typed components
 * @compare_data: opaque poपूर्णांकer passed to the @compare function
 *
 * Adds a new component match to the list stored in @matchptr, which the @master
 * aggregate driver needs to function. The list of component matches poपूर्णांकed to
 * by @matchptr must be initialized to शून्य beक्रमe adding the first match. This
 * only matches against components added with component_add_typed().
 *
 * The allocated match list in @matchptr is स्वतःmatically released using devm
 * actions.
 *
 * See also component_match_add_release() and component_match_add_typed().
 */
व्योम component_match_add_typed(काष्ठा device *master,
	काष्ठा component_match **matchptr,
	पूर्णांक (*compare_typed)(काष्ठा device *, पूर्णांक, व्योम *), व्योम *compare_data)
अणु
	__component_match_add(master, matchptr, शून्य, शून्य, compare_typed,
			      compare_data);
पूर्ण
EXPORT_SYMBOL(component_match_add_typed);

अटल व्योम मुक्त_master(काष्ठा master *master)
अणु
	काष्ठा component_match *match = master->match;
	पूर्णांक i;

	component_master_debugfs_del(master);
	list_del(&master->node);

	अगर (match) अणु
		क्रम (i = 0; i < match->num; i++) अणु
			काष्ठा component *c = match->compare[i].component;
			अगर (c)
				c->master = शून्य;
		पूर्ण
	पूर्ण

	kमुक्त(master);
पूर्ण

/**
 * component_master_add_with_match - रेजिस्टर an aggregate driver
 * @dev: device with the aggregate driver
 * @ops: callbacks क्रम the aggregate driver
 * @match: component match list क्रम the aggregate driver
 *
 * Registers a new aggregate driver consisting of the components added to @match
 * by calling one of the component_match_add() functions. Once all components in
 * @match are available, it will be assembled by calling
 * &component_master_ops.bind from @ops. Must be unरेजिस्टरed by calling
 * component_master_del().
 */
पूर्णांक component_master_add_with_match(काष्ठा device *dev,
	स्थिर काष्ठा component_master_ops *ops,
	काष्ठा component_match *match)
अणु
	काष्ठा master *master;
	पूर्णांक ret;

	/* Reallocate the match array क्रम its true size */
	ret = component_match_पुनः_स्मृति(dev, match, match->num);
	अगर (ret)
		वापस ret;

	master = kzalloc(माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस -ENOMEM;

	master->dev = dev;
	master->ops = ops;
	master->match = match;

	component_master_debugfs_add(master);
	/* Add to the list of available masters. */
	mutex_lock(&component_mutex);
	list_add(&master->node, &masters);

	ret = try_to_bring_up_master(master, शून्य);

	अगर (ret < 0)
		मुक्त_master(master);

	mutex_unlock(&component_mutex);

	वापस ret < 0 ? ret : 0;
पूर्ण
EXPORT_SYMBOL_GPL(component_master_add_with_match);

/**
 * component_master_del - unरेजिस्टर an aggregate driver
 * @dev: device with the aggregate driver
 * @ops: callbacks क्रम the aggregate driver
 *
 * Unरेजिस्टरs an aggregate driver रेजिस्टरed with
 * component_master_add_with_match(). If necessary the aggregate driver is first
 * disassembled by calling &component_master_ops.unbind from @ops.
 */
व्योम component_master_del(काष्ठा device *dev,
	स्थिर काष्ठा component_master_ops *ops)
अणु
	काष्ठा master *master;

	mutex_lock(&component_mutex);
	master = __master_find(dev, ops);
	अगर (master) अणु
		take_करोwn_master(master);
		मुक्त_master(master);
	पूर्ण
	mutex_unlock(&component_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(component_master_del);

अटल व्योम component_unbind(काष्ठा component *component,
	काष्ठा master *master, व्योम *data)
अणु
	WARN_ON(!component->bound);

	अगर (component->ops && component->ops->unbind)
		component->ops->unbind(component->dev, master->dev, data);
	component->bound = false;

	/* Release all resources claimed in the binding of this component */
	devres_release_group(component->dev, component);
पूर्ण

/**
 * component_unbind_all - unbind all components of an aggregate driver
 * @master_dev: device with the aggregate driver
 * @data: opaque poपूर्णांकer, passed to all components
 *
 * Unbinds all components of the aggregate @dev by passing @data to their
 * &component_ops.unbind functions. Should be called from
 * &component_master_ops.unbind.
 */
व्योम component_unbind_all(काष्ठा device *master_dev, व्योम *data)
अणु
	काष्ठा master *master;
	काष्ठा component *c;
	माप_प्रकार i;

	WARN_ON(!mutex_is_locked(&component_mutex));

	master = __master_find(master_dev, शून्य);
	अगर (!master)
		वापस;

	/* Unbind components in reverse order */
	क्रम (i = master->match->num; i--; )
		अगर (!master->match->compare[i].duplicate) अणु
			c = master->match->compare[i].component;
			component_unbind(c, master, data);
		पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(component_unbind_all);

अटल पूर्णांक component_bind(काष्ठा component *component, काष्ठा master *master,
	व्योम *data)
अणु
	पूर्णांक ret;

	/*
	 * Each component initialises inside its own devres group.
	 * This allows us to roll-back a failed component without
	 * affecting anything अन्यथा.
	 */
	अगर (!devres_खोलो_group(master->dev, शून्य, GFP_KERNEL))
		वापस -ENOMEM;

	/*
	 * Also खोलो a group क्रम the device itself: this allows us
	 * to release the resources claimed against the sub-device
	 * at the appropriate moment.
	 */
	अगर (!devres_खोलो_group(component->dev, component, GFP_KERNEL)) अणु
		devres_release_group(master->dev, शून्य);
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(master->dev, "binding %s (ops %ps)\n",
		dev_name(component->dev), component->ops);

	ret = component->ops->bind(component->dev, master->dev, data);
	अगर (!ret) अणु
		component->bound = true;

		/*
		 * Close the component device's group so that resources
		 * allocated in the binding are encapsulated क्रम removal
		 * at unbind.  Remove the group on the DRM device as we
		 * can clean those resources up independently.
		 */
		devres_बंद_group(component->dev, शून्य);
		devres_हटाओ_group(master->dev, शून्य);

		dev_info(master->dev, "bound %s (ops %ps)\n",
			 dev_name(component->dev), component->ops);
	पूर्ण अन्यथा अणु
		devres_release_group(component->dev, शून्य);
		devres_release_group(master->dev, शून्य);

		अगर (ret != -EPROBE_DEFER)
			dev_err(master->dev, "failed to bind %s (ops %ps): %d\n",
				dev_name(component->dev), component->ops, ret);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * component_bind_all - bind all components of an aggregate driver
 * @master_dev: device with the aggregate driver
 * @data: opaque poपूर्णांकer, passed to all components
 *
 * Binds all components of the aggregate @dev by passing @data to their
 * &component_ops.bind functions. Should be called from
 * &component_master_ops.bind.
 */
पूर्णांक component_bind_all(काष्ठा device *master_dev, व्योम *data)
अणु
	काष्ठा master *master;
	काष्ठा component *c;
	माप_प्रकार i;
	पूर्णांक ret = 0;

	WARN_ON(!mutex_is_locked(&component_mutex));

	master = __master_find(master_dev, शून्य);
	अगर (!master)
		वापस -EINVAL;

	/* Bind components in match order */
	क्रम (i = 0; i < master->match->num; i++)
		अगर (!master->match->compare[i].duplicate) अणु
			c = master->match->compare[i].component;
			ret = component_bind(c, master, data);
			अगर (ret)
				अवरोध;
		पूर्ण

	अगर (ret != 0) अणु
		क्रम (; i > 0; i--)
			अगर (!master->match->compare[i - 1].duplicate) अणु
				c = master->match->compare[i - 1].component;
				component_unbind(c, master, data);
			पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(component_bind_all);

अटल पूर्णांक __component_add(काष्ठा device *dev, स्थिर काष्ठा component_ops *ops,
	पूर्णांक subcomponent)
अणु
	काष्ठा component *component;
	पूर्णांक ret;

	component = kzalloc(माप(*component), GFP_KERNEL);
	अगर (!component)
		वापस -ENOMEM;

	component->ops = ops;
	component->dev = dev;
	component->subcomponent = subcomponent;

	dev_dbg(dev, "adding component (ops %ps)\n", ops);

	mutex_lock(&component_mutex);
	list_add_tail(&component->node, &component_list);

	ret = try_to_bring_up_masters(component);
	अगर (ret < 0) अणु
		अगर (component->master)
			हटाओ_component(component->master, component);
		list_del(&component->node);

		kमुक्त(component);
	पूर्ण
	mutex_unlock(&component_mutex);

	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * component_add_typed - रेजिस्टर a component
 * @dev: component device
 * @ops: component callbacks
 * @subcomponent: nonzero identअगरier क्रम subcomponents
 *
 * Register a new component क्रम @dev. Functions in @ops will be call when the
 * aggregate driver is पढ़ोy to bind the overall driver by calling
 * component_bind_all(). See also &काष्ठा component_ops.
 *
 * @subcomponent must be nonzero and is used to dअगरferentiate between multiple
 * components रेजिस्टरd on the same device @dev. These components are match
 * using component_match_add_typed().
 *
 * The component needs to be unरेजिस्टरed at driver unload/disconnect by
 * calling component_del().
 *
 * See also component_add().
 */
पूर्णांक component_add_typed(काष्ठा device *dev, स्थिर काष्ठा component_ops *ops,
	पूर्णांक subcomponent)
अणु
	अगर (WARN_ON(subcomponent == 0))
		वापस -EINVAL;

	वापस __component_add(dev, ops, subcomponent);
पूर्ण
EXPORT_SYMBOL_GPL(component_add_typed);

/**
 * component_add - रेजिस्टर a component
 * @dev: component device
 * @ops: component callbacks
 *
 * Register a new component क्रम @dev. Functions in @ops will be called when the
 * aggregate driver is पढ़ोy to bind the overall driver by calling
 * component_bind_all(). See also &काष्ठा component_ops.
 *
 * The component needs to be unरेजिस्टरed at driver unload/disconnect by
 * calling component_del().
 *
 * See also component_add_typed() क्रम a variant that allows multipled dअगरferent
 * components on the same device.
 */
पूर्णांक component_add(काष्ठा device *dev, स्थिर काष्ठा component_ops *ops)
अणु
	वापस __component_add(dev, ops, 0);
पूर्ण
EXPORT_SYMBOL_GPL(component_add);

/**
 * component_del - unरेजिस्टर a component
 * @dev: component device
 * @ops: component callbacks
 *
 * Unरेजिस्टर a component added with component_add(). If the component is bound
 * पूर्णांकo an aggregate driver, this will क्रमce the entire aggregate driver, including
 * all its components, to be unbound.
 */
व्योम component_del(काष्ठा device *dev, स्थिर काष्ठा component_ops *ops)
अणु
	काष्ठा component *c, *component = शून्य;

	mutex_lock(&component_mutex);
	list_क्रम_each_entry(c, &component_list, node)
		अगर (c->dev == dev && c->ops == ops) अणु
			list_del(&c->node);
			component = c;
			अवरोध;
		पूर्ण

	अगर (component && component->master) अणु
		take_करोwn_master(component->master);
		हटाओ_component(component->master, component);
	पूर्ण

	mutex_unlock(&component_mutex);

	WARN_ON(!component);
	kमुक्त(component);
पूर्ण
EXPORT_SYMBOL_GPL(component_del);
