<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I/O Address Space ID allocator. There is one global IOASID space, split पूर्णांकo
 * subsets. Users create a subset with DECLARE_IOASID_SET, then allocate and
 * मुक्त IOASIDs with ioasid_alloc and ioasid_put.
 */
#समावेश <linux/ioasid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/xarray.h>

काष्ठा ioasid_data अणु
	ioasid_t id;
	काष्ठा ioasid_set *set;
	व्योम *निजी;
	काष्ठा rcu_head rcu;
	refcount_t refs;
पूर्ण;

/*
 * काष्ठा ioasid_allocator_data - Internal data काष्ठाure to hold inक्रमmation
 * about an allocator. There are two types of allocators:
 *
 * - Default allocator always has its own XArray to track the IOASIDs allocated.
 * - Custom allocators may share allocation helpers with dअगरferent निजी data.
 *   Custom allocators that share the same helper functions also share the same
 *   XArray.
 * Rules:
 * 1. Default allocator is always available, not dynamically रेजिस्टरed. This is
 *    to prevent race conditions with early boot code that want to रेजिस्टर
 *    custom allocators or allocate IOASIDs.
 * 2. Custom allocators take precedence over the शेष allocator.
 * 3. When all custom allocators sharing the same helper functions are
 *    unरेजिस्टरed (e.g. due to hotplug), all outstanding IOASIDs must be
 *    मुक्तd. Otherwise, outstanding IOASIDs will be lost and orphaned.
 * 4. When चयनing between custom allocators sharing the same helper
 *    functions, outstanding IOASIDs are preserved.
 * 5. When चयनing between custom allocator and शेष allocator, all IOASIDs
 *    must be मुक्तd to ensure unadulterated space क्रम the new allocator.
 *
 * @ops:	allocator helper functions and its data
 * @list:	रेजिस्टरed custom allocators
 * @slist:	allocators share the same ops but dअगरferent data
 * @flags:	attributes of the allocator
 * @xa:		xarray holds the IOASID space
 * @rcu:	used क्रम kमुक्त_rcu when unरेजिस्टरing allocator
 */
काष्ठा ioasid_allocator_data अणु
	काष्ठा ioasid_allocator_ops *ops;
	काष्ठा list_head list;
	काष्ठा list_head slist;
#घोषणा IOASID_ALLOCATOR_CUSTOM BIT(0) /* Needs framework to track results */
	अचिन्हित दीर्घ flags;
	काष्ठा xarray xa;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल DEFINE_SPINLOCK(ioasid_allocator_lock);
अटल LIST_HEAD(allocators_list);

अटल ioasid_t शेष_alloc(ioasid_t min, ioasid_t max, व्योम *opaque);
अटल व्योम शेष_मुक्त(ioasid_t ioasid, व्योम *opaque);

अटल काष्ठा ioasid_allocator_ops शेष_ops = अणु
	.alloc = शेष_alloc,
	.मुक्त = शेष_मुक्त,
पूर्ण;

अटल काष्ठा ioasid_allocator_data शेष_allocator = अणु
	.ops = &शेष_ops,
	.flags = 0,
	.xa = XARRAY_INIT(ioasid_xa, XA_FLAGS_ALLOC),
पूर्ण;

अटल काष्ठा ioasid_allocator_data *active_allocator = &शेष_allocator;

अटल ioasid_t शेष_alloc(ioasid_t min, ioasid_t max, व्योम *opaque)
अणु
	ioasid_t id;

	अगर (xa_alloc(&शेष_allocator.xa, &id, opaque, XA_LIMIT(min, max), GFP_ATOMIC)) अणु
		pr_err("Failed to alloc ioasid from %d to %d\n", min, max);
		वापस INVALID_IOASID;
	पूर्ण

	वापस id;
पूर्ण

अटल व्योम शेष_मुक्त(ioasid_t ioasid, व्योम *opaque)
अणु
	काष्ठा ioasid_data *ioasid_data;

	ioasid_data = xa_erase(&शेष_allocator.xa, ioasid);
	kमुक्त_rcu(ioasid_data, rcu);
पूर्ण

/* Allocate and initialize a new custom allocator with its helper functions */
अटल काष्ठा ioasid_allocator_data *ioasid_alloc_allocator(काष्ठा ioasid_allocator_ops *ops)
अणु
	काष्ठा ioasid_allocator_data *ia_data;

	ia_data = kzalloc(माप(*ia_data), GFP_ATOMIC);
	अगर (!ia_data)
		वापस शून्य;

	xa_init_flags(&ia_data->xa, XA_FLAGS_ALLOC);
	INIT_LIST_HEAD(&ia_data->slist);
	ia_data->flags |= IOASID_ALLOCATOR_CUSTOM;
	ia_data->ops = ops;

	/* For tracking custom allocators that share the same ops */
	list_add_tail(&ops->list, &ia_data->slist);

	वापस ia_data;
पूर्ण

अटल bool use_same_ops(काष्ठा ioasid_allocator_ops *a, काष्ठा ioasid_allocator_ops *b)
अणु
	वापस (a->मुक्त == b->मुक्त) && (a->alloc == b->alloc);
पूर्ण

/**
 * ioasid_रेजिस्टर_allocator - रेजिस्टर a custom allocator
 * @ops: the custom allocator ops to be रेजिस्टरed
 *
 * Custom allocators take precedence over the शेष xarray based allocator.
 * Private data associated with the IOASID allocated by the custom allocators
 * are managed by IOASID framework similar to data stored in xa by शेष
 * allocator.
 *
 * There can be multiple allocators रेजिस्टरed but only one is active. In हाल
 * of runसमय removal of a custom allocator, the next one is activated based
 * on the registration ordering.
 *
 * Multiple allocators can share the same alloc() function, in this हाल the
 * IOASID space is shared.
 */
पूर्णांक ioasid_रेजिस्टर_allocator(काष्ठा ioasid_allocator_ops *ops)
अणु
	काष्ठा ioasid_allocator_data *ia_data;
	काष्ठा ioasid_allocator_data *pallocator;
	पूर्णांक ret = 0;

	spin_lock(&ioasid_allocator_lock);

	ia_data = ioasid_alloc_allocator(ops);
	अगर (!ia_data) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	/*
	 * No particular preference, we activate the first one and keep
	 * the later रेजिस्टरed allocators in a list in हाल the first one माला_लो
	 * हटाओd due to hotplug.
	 */
	अगर (list_empty(&allocators_list)) अणु
		WARN_ON(active_allocator != &शेष_allocator);
		/* Use this new allocator अगर शेष is not active */
		अगर (xa_empty(&active_allocator->xa)) अणु
			rcu_assign_poपूर्णांकer(active_allocator, ia_data);
			list_add_tail(&ia_data->list, &allocators_list);
			जाओ out_unlock;
		पूर्ण
		pr_warn("Default allocator active with outstanding IOASID\n");
		ret = -EAGAIN;
		जाओ out_मुक्त;
	पूर्ण

	/* Check अगर the allocator is alपढ़ोy रेजिस्टरed */
	list_क्रम_each_entry(pallocator, &allocators_list, list) अणु
		अगर (pallocator->ops == ops) अणु
			pr_err("IOASID allocator already registered\n");
			ret = -EEXIST;
			जाओ out_मुक्त;
		पूर्ण अन्यथा अगर (use_same_ops(pallocator->ops, ops)) अणु
			/*
			 * If the new allocator shares the same ops,
			 * then they will share the same IOASID space.
			 * We should put them under the same xarray.
			 */
			list_add_tail(&ops->list, &pallocator->slist);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण
	list_add_tail(&ia_data->list, &allocators_list);

	spin_unlock(&ioasid_allocator_lock);
	वापस 0;
out_मुक्त:
	kमुक्त(ia_data);
out_unlock:
	spin_unlock(&ioasid_allocator_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ioasid_रेजिस्टर_allocator);

/**
 * ioasid_unरेजिस्टर_allocator - Remove a custom IOASID allocator ops
 * @ops: the custom allocator to be हटाओd
 *
 * Remove an allocator from the list, activate the next allocator in
 * the order it was रेजिस्टरed. Or revert to शेष allocator अगर all
 * custom allocators are unरेजिस्टरed without outstanding IOASIDs.
 */
व्योम ioasid_unरेजिस्टर_allocator(काष्ठा ioasid_allocator_ops *ops)
अणु
	काष्ठा ioasid_allocator_data *pallocator;
	काष्ठा ioasid_allocator_ops *sops;

	spin_lock(&ioasid_allocator_lock);
	अगर (list_empty(&allocators_list)) अणु
		pr_warn("No custom IOASID allocators active!\n");
		जाओ निकास_unlock;
	पूर्ण

	list_क्रम_each_entry(pallocator, &allocators_list, list) अणु
		अगर (!use_same_ops(pallocator->ops, ops))
			जारी;

		अगर (list_is_singular(&pallocator->slist)) अणु
			/* No shared helper functions */
			list_del(&pallocator->list);
			/*
			 * All IOASIDs should have been मुक्तd beक्रमe
			 * the last allocator that shares the same ops
			 * is unरेजिस्टरed.
			 */
			WARN_ON(!xa_empty(&pallocator->xa));
			अगर (list_empty(&allocators_list)) अणु
				pr_info("No custom IOASID allocators, switch to default.\n");
				rcu_assign_poपूर्णांकer(active_allocator, &शेष_allocator);
			पूर्ण अन्यथा अगर (pallocator == active_allocator) अणु
				rcu_assign_poपूर्णांकer(active_allocator,
						list_first_entry(&allocators_list,
								काष्ठा ioasid_allocator_data, list));
				pr_info("IOASID allocator changed");
			पूर्ण
			kमुक्त_rcu(pallocator, rcu);
			अवरोध;
		पूर्ण
		/*
		 * Find the matching shared ops to delete,
		 * but keep outstanding IOASIDs
		 */
		list_क्रम_each_entry(sops, &pallocator->slist, list) अणु
			अगर (sops == ops) अणु
				list_del(&ops->list);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

निकास_unlock:
	spin_unlock(&ioasid_allocator_lock);
पूर्ण
EXPORT_SYMBOL_GPL(ioasid_unरेजिस्टर_allocator);

/**
 * ioasid_set_data - Set निजी data क्रम an allocated ioasid
 * @ioasid: the ID to set data
 * @data:   the निजी data
 *
 * For IOASID that is alपढ़ोy allocated, निजी data can be set
 * via this API. Future lookup can be करोne via ioasid_find.
 */
पूर्णांक ioasid_set_data(ioasid_t ioasid, व्योम *data)
अणु
	काष्ठा ioasid_data *ioasid_data;
	पूर्णांक ret = 0;

	spin_lock(&ioasid_allocator_lock);
	ioasid_data = xa_load(&active_allocator->xa, ioasid);
	अगर (ioasid_data)
		rcu_assign_poपूर्णांकer(ioasid_data->निजी, data);
	अन्यथा
		ret = -ENOENT;
	spin_unlock(&ioasid_allocator_lock);

	/*
	 * Wait क्रम पढ़ोers to stop accessing the old निजी data, so the
	 * caller can मुक्त it.
	 */
	अगर (!ret)
		synchronize_rcu();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ioasid_set_data);

/**
 * ioasid_alloc - Allocate an IOASID
 * @set: the IOASID set
 * @min: the minimum ID (inclusive)
 * @max: the maximum ID (inclusive)
 * @निजी: data निजी to the caller
 *
 * Allocate an ID between @min and @max. The @निजी poपूर्णांकer is stored
 * पूर्णांकernally and can be retrieved with ioasid_find().
 *
 * Return: the allocated ID on success, or %INVALID_IOASID on failure.
 */
ioasid_t ioasid_alloc(काष्ठा ioasid_set *set, ioasid_t min, ioasid_t max,
		      व्योम *निजी)
अणु
	काष्ठा ioasid_data *data;
	व्योम *adata;
	ioasid_t id;

	data = kzalloc(माप(*data), GFP_ATOMIC);
	अगर (!data)
		वापस INVALID_IOASID;

	data->set = set;
	data->निजी = निजी;
	refcount_set(&data->refs, 1);

	/*
	 * Custom allocator needs allocator data to perक्रमm platक्रमm specअगरic
	 * operations.
	 */
	spin_lock(&ioasid_allocator_lock);
	adata = active_allocator->flags & IOASID_ALLOCATOR_CUSTOM ? active_allocator->ops->pdata : data;
	id = active_allocator->ops->alloc(min, max, adata);
	अगर (id == INVALID_IOASID) अणु
		pr_err("Failed ASID allocation %lu\n", active_allocator->flags);
		जाओ निकास_मुक्त;
	पूर्ण

	अगर ((active_allocator->flags & IOASID_ALLOCATOR_CUSTOM) &&
	     xa_alloc(&active_allocator->xa, &id, data, XA_LIMIT(id, id), GFP_ATOMIC)) अणु
		/* Custom allocator needs framework to store and track allocation results */
		pr_err("Failed to alloc ioasid from %d\n", id);
		active_allocator->ops->मुक्त(id, active_allocator->ops->pdata);
		जाओ निकास_मुक्त;
	पूर्ण
	data->id = id;

	spin_unlock(&ioasid_allocator_lock);
	वापस id;
निकास_मुक्त:
	spin_unlock(&ioasid_allocator_lock);
	kमुक्त(data);
	वापस INVALID_IOASID;
पूर्ण
EXPORT_SYMBOL_GPL(ioasid_alloc);

/**
 * ioasid_get - obtain a reference to the IOASID
 */
व्योम ioasid_get(ioasid_t ioasid)
अणु
	काष्ठा ioasid_data *ioasid_data;

	spin_lock(&ioasid_allocator_lock);
	ioasid_data = xa_load(&active_allocator->xa, ioasid);
	अगर (ioasid_data)
		refcount_inc(&ioasid_data->refs);
	अन्यथा
		WARN_ON(1);
	spin_unlock(&ioasid_allocator_lock);
पूर्ण
EXPORT_SYMBOL_GPL(ioasid_get);

/**
 * ioasid_put - Release a reference to an ioasid
 * @ioasid: the ID to हटाओ
 *
 * Put a reference to the IOASID, मुक्त it when the number of references drops to
 * zero.
 *
 * Return: %true अगर the IOASID was मुक्तd, %false otherwise.
 */
bool ioasid_put(ioasid_t ioasid)
अणु
	bool मुक्त = false;
	काष्ठा ioasid_data *ioasid_data;

	spin_lock(&ioasid_allocator_lock);
	ioasid_data = xa_load(&active_allocator->xa, ioasid);
	अगर (!ioasid_data) अणु
		pr_err("Trying to free unknown IOASID %u\n", ioasid);
		जाओ निकास_unlock;
	पूर्ण

	मुक्त = refcount_dec_and_test(&ioasid_data->refs);
	अगर (!मुक्त)
		जाओ निकास_unlock;

	active_allocator->ops->मुक्त(ioasid, active_allocator->ops->pdata);
	/* Custom allocator needs additional steps to मुक्त the xa element */
	अगर (active_allocator->flags & IOASID_ALLOCATOR_CUSTOM) अणु
		ioasid_data = xa_erase(&active_allocator->xa, ioasid);
		kमुक्त_rcu(ioasid_data, rcu);
	पूर्ण

निकास_unlock:
	spin_unlock(&ioasid_allocator_lock);
	वापस मुक्त;
पूर्ण
EXPORT_SYMBOL_GPL(ioasid_put);

/**
 * ioasid_find - Find IOASID data
 * @set: the IOASID set
 * @ioasid: the IOASID to find
 * @getter: function to call on the found object
 *
 * The optional getter function allows to take a reference to the found object
 * under the rcu lock. The function can also check अगर the object is still valid:
 * अगर @getter वापसs false, then the object is invalid and शून्य is वापसed.
 *
 * If the IOASID exists, वापस the निजी poपूर्णांकer passed to ioasid_alloc.
 * Private data can be शून्य अगर not set. Return an error अगर the IOASID is not
 * found, or अगर @set is not शून्य and the IOASID करोes not beदीर्घ to the set.
 */
व्योम *ioasid_find(काष्ठा ioasid_set *set, ioasid_t ioasid,
		  bool (*getter)(व्योम *))
अणु
	व्योम *priv;
	काष्ठा ioasid_data *ioasid_data;
	काष्ठा ioasid_allocator_data *idata;

	rcu_पढ़ो_lock();
	idata = rcu_dereference(active_allocator);
	ioasid_data = xa_load(&idata->xa, ioasid);
	अगर (!ioasid_data) अणु
		priv = ERR_PTR(-ENOENT);
		जाओ unlock;
	पूर्ण
	अगर (set && ioasid_data->set != set) अणु
		/* data found but करोes not beदीर्घ to the set */
		priv = ERR_PTR(-EACCES);
		जाओ unlock;
	पूर्ण
	/* Now IOASID and its set is verअगरied, we can वापस the निजी data */
	priv = rcu_dereference(ioasid_data->निजी);
	अगर (getter && !getter(priv))
		priv = शून्य;
unlock:
	rcu_पढ़ो_unlock();

	वापस priv;
पूर्ण
EXPORT_SYMBOL_GPL(ioasid_find);

MODULE_AUTHOR("Jean-Philippe Brucker <jean-philippe.brucker@arm.com>");
MODULE_AUTHOR("Jacob Pan <jacob.jun.pan@linux.intel.com>");
MODULE_DESCRIPTION("IO Address Space ID (IOASID) allocator");
MODULE_LICENSE("GPL");
