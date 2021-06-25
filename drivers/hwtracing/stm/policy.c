<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Trace Module (STM) master/channel allocation policy management
 * Copyright (c) 2014, Intel Corporation.
 *
 * A master/channel allocation policy allows mapping string identअगरiers to
 * master and channel ranges, where allocation can be करोne.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/configfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांग.h>
#समावेश "stm.h"

/*
 * STP Master/Channel allocation policy configfs layout.
 */

काष्ठा stp_policy अणु
	काष्ठा config_group	group;
	काष्ठा sपंचांग_device	*sपंचांग;
पूर्ण;

काष्ठा stp_policy_node अणु
	काष्ठा config_group	group;
	काष्ठा stp_policy	*policy;
	अचिन्हित पूर्णांक		first_master;
	अचिन्हित पूर्णांक		last_master;
	अचिन्हित पूर्णांक		first_channel;
	अचिन्हित पूर्णांक		last_channel;
	/* this is the one that's exposed to the attributes */
	अचिन्हित अक्षर		priv[];
पूर्ण;

व्योम *stp_policy_node_priv(काष्ठा stp_policy_node *pn)
अणु
	अगर (!pn)
		वापस शून्य;

	वापस pn->priv;
पूर्ण

अटल काष्ठा configfs_subप्रणाली stp_policy_subsys;

व्योम stp_policy_node_get_ranges(काष्ठा stp_policy_node *policy_node,
				अचिन्हित पूर्णांक *mstart, अचिन्हित पूर्णांक *mend,
				अचिन्हित पूर्णांक *cstart, अचिन्हित पूर्णांक *cend)
अणु
	*mstart	= policy_node->first_master;
	*mend	= policy_node->last_master;
	*cstart	= policy_node->first_channel;
	*cend	= policy_node->last_channel;
पूर्ण

अटल अंतरभूत काष्ठा stp_policy *to_stp_policy(काष्ठा config_item *item)
अणु
	वापस item ?
		container_of(to_config_group(item), काष्ठा stp_policy, group) :
		शून्य;
पूर्ण

अटल अंतरभूत काष्ठा stp_policy_node *
to_stp_policy_node(काष्ठा config_item *item)
अणु
	वापस item ?
		container_of(to_config_group(item), काष्ठा stp_policy_node,
			     group) :
		शून्य;
पूर्ण

व्योम *to_pdrv_policy_node(काष्ठा config_item *item)
अणु
	काष्ठा stp_policy_node *node = to_stp_policy_node(item);

	वापस stp_policy_node_priv(node);
पूर्ण
EXPORT_SYMBOL_GPL(to_pdrv_policy_node);

अटल sमाप_प्रकार
stp_policy_node_masters_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा stp_policy_node *policy_node = to_stp_policy_node(item);
	sमाप_प्रकार count;

	count = प्र_लिखो(page, "%u %u\n", policy_node->first_master,
			policy_node->last_master);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
stp_policy_node_masters_store(काष्ठा config_item *item, स्थिर अक्षर *page,
			      माप_प्रकार count)
अणु
	काष्ठा stp_policy_node *policy_node = to_stp_policy_node(item);
	अचिन्हित पूर्णांक first, last;
	काष्ठा sपंचांग_device *sपंचांग;
	अक्षर *p = (अक्षर *)page;
	sमाप_प्रकार ret = -ENODEV;

	अगर (माला_पूछो(p, "%u %u", &first, &last) != 2)
		वापस -EINVAL;

	mutex_lock(&stp_policy_subsys.su_mutex);
	sपंचांग = policy_node->policy->sपंचांग;
	अगर (!sपंचांग)
		जाओ unlock;

	/* must be within [sw_start..sw_end], which is an inclusive range */
	अगर (first > last || first < sपंचांग->data->sw_start ||
	    last > sपंचांग->data->sw_end) अणु
		ret = -दुस्फल;
		जाओ unlock;
	पूर्ण

	ret = count;
	policy_node->first_master = first;
	policy_node->last_master = last;

unlock:
	mutex_unlock(&stp_policy_subsys.su_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
stp_policy_node_channels_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा stp_policy_node *policy_node = to_stp_policy_node(item);
	sमाप_प्रकार count;

	count = प्र_लिखो(page, "%u %u\n", policy_node->first_channel,
			policy_node->last_channel);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
stp_policy_node_channels_store(काष्ठा config_item *item, स्थिर अक्षर *page,
			       माप_प्रकार count)
अणु
	काष्ठा stp_policy_node *policy_node = to_stp_policy_node(item);
	अचिन्हित पूर्णांक first, last;
	काष्ठा sपंचांग_device *sपंचांग;
	अक्षर *p = (अक्षर *)page;
	sमाप_प्रकार ret = -ENODEV;

	अगर (माला_पूछो(p, "%u %u", &first, &last) != 2)
		वापस -EINVAL;

	mutex_lock(&stp_policy_subsys.su_mutex);
	sपंचांग = policy_node->policy->sपंचांग;
	अगर (!sपंचांग)
		जाओ unlock;

	अगर (first > पूर्णांक_उच्च || last > पूर्णांक_उच्च || first > last ||
	    last >= sपंचांग->data->sw_nchannels) अणु
		ret = -दुस्फल;
		जाओ unlock;
	पूर्ण

	ret = count;
	policy_node->first_channel = first;
	policy_node->last_channel = last;

unlock:
	mutex_unlock(&stp_policy_subsys.su_mutex);

	वापस ret;
पूर्ण

अटल व्योम stp_policy_node_release(काष्ठा config_item *item)
अणु
	काष्ठा stp_policy_node *node = to_stp_policy_node(item);

	kमुक्त(node);
पूर्ण

अटल काष्ठा configfs_item_operations stp_policy_node_item_ops = अणु
	.release		= stp_policy_node_release,
पूर्ण;

CONFIGFS_ATTR(stp_policy_node_, masters);
CONFIGFS_ATTR(stp_policy_node_, channels);

अटल काष्ठा configfs_attribute *stp_policy_node_attrs[] = अणु
	&stp_policy_node_attr_masters,
	&stp_policy_node_attr_channels,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type stp_policy_type;
अटल स्थिर काष्ठा config_item_type stp_policy_node_type;

स्थिर काष्ठा config_item_type *
get_policy_node_type(काष्ठा configfs_attribute **attrs)
अणु
	काष्ठा config_item_type *type;
	काष्ठा configfs_attribute **merged;

	type = kmemdup(&stp_policy_node_type, माप(stp_policy_node_type),
		       GFP_KERNEL);
	अगर (!type)
		वापस शून्य;

	merged = memcat_p(stp_policy_node_attrs, attrs);
	अगर (!merged) अणु
		kमुक्त(type);
		वापस शून्य;
	पूर्ण

	type->ct_attrs = merged;

	वापस type;
पूर्ण

अटल काष्ठा config_group *
stp_policy_node_make(काष्ठा config_group *group, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा config_item_type *type = &stp_policy_node_type;
	काष्ठा stp_policy_node *policy_node, *parent_node;
	स्थिर काष्ठा sपंचांग_protocol_driver *pdrv;
	काष्ठा stp_policy *policy;

	अगर (group->cg_item.ci_type == &stp_policy_type) अणु
		policy = container_of(group, काष्ठा stp_policy, group);
	पूर्ण अन्यथा अणु
		parent_node = container_of(group, काष्ठा stp_policy_node,
					   group);
		policy = parent_node->policy;
	पूर्ण

	अगर (!policy->sपंचांग)
		वापस ERR_PTR(-ENODEV);

	pdrv = policy->sपंचांग->pdrv;
	policy_node =
		kzalloc(दुरत्व(काष्ठा stp_policy_node, priv[pdrv->priv_sz]),
			GFP_KERNEL);
	अगर (!policy_node)
		वापस ERR_PTR(-ENOMEM);

	अगर (pdrv->policy_node_init)
		pdrv->policy_node_init((व्योम *)policy_node->priv);

	अगर (policy->sपंचांग->pdrv_node_type)
		type = policy->sपंचांग->pdrv_node_type;

	config_group_init_type_name(&policy_node->group, name, type);

	policy_node->policy = policy;

	/* शेष values क्रम the attributes */
	policy_node->first_master = policy->sपंचांग->data->sw_start;
	policy_node->last_master = policy->sपंचांग->data->sw_end;
	policy_node->first_channel = 0;
	policy_node->last_channel = policy->sपंचांग->data->sw_nchannels - 1;

	वापस &policy_node->group;
पूर्ण

अटल व्योम
stp_policy_node_drop(काष्ठा config_group *group, काष्ठा config_item *item)
अणु
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations stp_policy_node_group_ops = अणु
	.make_group	= stp_policy_node_make,
	.drop_item	= stp_policy_node_drop,
पूर्ण;

अटल स्थिर काष्ठा config_item_type stp_policy_node_type = अणु
	.ct_item_ops	= &stp_policy_node_item_ops,
	.ct_group_ops	= &stp_policy_node_group_ops,
	.ct_attrs	= stp_policy_node_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/*
 * Root group: policies.
 */
अटल sमाप_प्रकार stp_policy_device_show(काष्ठा config_item *item,
				      अक्षर *page)
अणु
	काष्ठा stp_policy *policy = to_stp_policy(item);
	sमाप_प्रकार count;

	count = प्र_लिखो(page, "%s\n",
			(policy && policy->sपंचांग) ?
			policy->sपंचांग->data->name :
			"<none>");

	वापस count;
पूर्ण

CONFIGFS_ATTR_RO(stp_policy_, device);

अटल sमाप_प्रकार stp_policy_protocol_show(काष्ठा config_item *item,
					अक्षर *page)
अणु
	काष्ठा stp_policy *policy = to_stp_policy(item);
	sमाप_प्रकार count;

	count = प्र_लिखो(page, "%s\n",
			(policy && policy->sपंचांग) ?
			policy->sपंचांग->pdrv->name :
			"<none>");

	वापस count;
पूर्ण

CONFIGFS_ATTR_RO(stp_policy_, protocol);

अटल काष्ठा configfs_attribute *stp_policy_attrs[] = अणु
	&stp_policy_attr_device,
	&stp_policy_attr_protocol,
	शून्य,
पूर्ण;

व्योम stp_policy_unbind(काष्ठा stp_policy *policy)
अणु
	काष्ठा sपंचांग_device *sपंचांग = policy->sपंचांग;

	/*
	 * stp_policy_release() will not call here अगर the policy is alपढ़ोy
	 * unbound; other users should not either, as no link exists between
	 * this policy and anything अन्यथा in that हाल
	 */
	अगर (WARN_ON_ONCE(!policy->sपंचांग))
		वापस;

	lockdep_निश्चित_held(&sपंचांग->policy_mutex);

	sपंचांग->policy = शून्य;
	policy->sपंचांग = शून्य;

	/*
	 * Drop the reference on the protocol driver and lose the link.
	 */
	sपंचांग_put_protocol(sपंचांग->pdrv);
	sपंचांग->pdrv = शून्य;
	sपंचांग_put_device(sपंचांग);
पूर्ण

अटल व्योम stp_policy_release(काष्ठा config_item *item)
अणु
	काष्ठा stp_policy *policy = to_stp_policy(item);
	काष्ठा sपंचांग_device *sपंचांग = policy->sपंचांग;

	/* a policy *can* be unbound and still exist in configfs tree */
	अगर (!sपंचांग)
		वापस;

	mutex_lock(&sपंचांग->policy_mutex);
	stp_policy_unbind(policy);
	mutex_unlock(&sपंचांग->policy_mutex);

	kमुक्त(policy);
पूर्ण

अटल काष्ठा configfs_item_operations stp_policy_item_ops = अणु
	.release		= stp_policy_release,
पूर्ण;

अटल काष्ठा configfs_group_operations stp_policy_group_ops = अणु
	.make_group	= stp_policy_node_make,
पूर्ण;

अटल स्थिर काष्ठा config_item_type stp_policy_type = अणु
	.ct_item_ops	= &stp_policy_item_ops,
	.ct_group_ops	= &stp_policy_group_ops,
	.ct_attrs	= stp_policy_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *
stp_policy_make(काष्ठा config_group *group, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा config_item_type *pdrv_node_type;
	स्थिर काष्ठा sपंचांग_protocol_driver *pdrv;
	अक्षर *devname, *proto, *p;
	काष्ठा config_group *ret;
	काष्ठा sपंचांग_device *sपंचांग;
	पूर्णांक err;

	devname = kaप्र_लिखो(GFP_KERNEL, "%s", name);
	अगर (!devname)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * node must look like <device_name>.<policy_name>, where
	 * <device_name> is the name of an existing sपंचांग device; may
	 *               contain करोts;
	 * <policy_name> is an arbitrary string; may not contain करोts
	 * <device_name>:<protocol_name>.<policy_name>
	 */
	p = म_खोजप(devname, '.');
	अगर (!p) अणु
		kमुक्त(devname);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	*p = '\0';

	/*
	 * look क्रम ":<protocol_name>":
	 *  + no protocol suffix: fall back to whatever is available;
	 *  + unknown protocol: fail the whole thing
	 */
	proto = म_खोजप(devname, ':');
	अगर (proto)
		*proto++ = '\0';

	sपंचांग = sपंचांग_find_device(devname);
	अगर (!sपंचांग) अणु
		kमुक्त(devname);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	err = sपंचांग_lookup_protocol(proto, &pdrv, &pdrv_node_type);
	kमुक्त(devname);

	अगर (err) अणु
		sपंचांग_put_device(sपंचांग);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	mutex_lock(&sपंचांग->policy_mutex);
	अगर (sपंचांग->policy) अणु
		ret = ERR_PTR(-EBUSY);
		जाओ unlock_policy;
	पूर्ण

	sपंचांग->policy = kzalloc(माप(*sपंचांग->policy), GFP_KERNEL);
	अगर (!sपंचांग->policy) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ unlock_policy;
	पूर्ण

	config_group_init_type_name(&sपंचांग->policy->group, name,
				    &stp_policy_type);

	sपंचांग->pdrv = pdrv;
	sपंचांग->pdrv_node_type = pdrv_node_type;
	sपंचांग->policy->sपंचांग = sपंचांग;
	ret = &sपंचांग->policy->group;

unlock_policy:
	mutex_unlock(&sपंचांग->policy_mutex);

	अगर (IS_ERR(ret)) अणु
		/*
		 * pdrv and sपंचांग->pdrv at this poपूर्णांक can be quite dअगरferent,
		 * and only one of them needs to be 'put'
		 */
		sपंचांग_put_protocol(pdrv);
		sपंचांग_put_device(sपंचांग);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा configfs_group_operations stp_policy_root_group_ops = अणु
	.make_group	= stp_policy_make,
पूर्ण;

अटल स्थिर काष्ठा config_item_type stp_policy_root_type = अणु
	.ct_group_ops	= &stp_policy_root_group_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली stp_policy_subsys = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf	= "stp-policy",
			.ci_type	= &stp_policy_root_type,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * Lock the policy mutex from the outside
 */
अटल काष्ठा stp_policy_node *
__stp_policy_node_lookup(काष्ठा stp_policy *policy, अक्षर *s)
अणु
	काष्ठा stp_policy_node *policy_node, *ret = शून्य;
	काष्ठा list_head *head = &policy->group.cg_children;
	काष्ठा config_item *item;
	अक्षर *start, *end = s;

	अगर (list_empty(head))
		वापस शून्य;

next:
	क्रम (;;) अणु
		start = strsep(&end, "/");
		अगर (!start)
			अवरोध;

		अगर (!*start)
			जारी;

		list_क्रम_each_entry(item, head, ci_entry) अणु
			policy_node = to_stp_policy_node(item);

			अगर (!म_भेद(start,
				    policy_node->group.cg_item.ci_name)) अणु
				ret = policy_node;

				अगर (!end)
					जाओ out;

				head = &policy_node->group.cg_children;
				जाओ next;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

out:
	वापस ret;
पूर्ण


काष्ठा stp_policy_node *
stp_policy_node_lookup(काष्ठा sपंचांग_device *sपंचांग, अक्षर *s)
अणु
	काष्ठा stp_policy_node *policy_node = शून्य;

	mutex_lock(&stp_policy_subsys.su_mutex);

	mutex_lock(&sपंचांग->policy_mutex);
	अगर (sपंचांग->policy)
		policy_node = __stp_policy_node_lookup(sपंचांग->policy, s);
	mutex_unlock(&sपंचांग->policy_mutex);

	अगर (policy_node)
		config_item_get(&policy_node->group.cg_item);
	अन्यथा
		mutex_unlock(&stp_policy_subsys.su_mutex);

	वापस policy_node;
पूर्ण

व्योम stp_policy_node_put(काष्ठा stp_policy_node *policy_node)
अणु
	lockdep_निश्चित_held(&stp_policy_subsys.su_mutex);

	mutex_unlock(&stp_policy_subsys.su_mutex);
	config_item_put(&policy_node->group.cg_item);
पूर्ण

पूर्णांक __init stp_configfs_init(व्योम)
अणु
	config_group_init(&stp_policy_subsys.su_group);
	mutex_init(&stp_policy_subsys.su_mutex);
	वापस configfs_रेजिस्टर_subप्रणाली(&stp_policy_subsys);
पूर्ण

व्योम __निकास stp_configfs_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_subप्रणाली(&stp_policy_subsys);
पूर्ण
