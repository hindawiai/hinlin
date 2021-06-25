<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/devres.c - device resource management
 *
 * Copyright (c) 2006  SUSE Linux Products GmbH
 * Copyright (c) 2006  Tejun Heo <teheo@suse.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/percpu.h>

#समावेश <यंत्र/sections.h>

#समावेश "base.h"

काष्ठा devres_node अणु
	काष्ठा list_head		entry;
	dr_release_t			release;
#अगर_घोषित CONFIG_DEBUG_DEVRES
	स्थिर अक्षर			*name;
	माप_प्रकार				size;
#पूर्ण_अगर
पूर्ण;

काष्ठा devres अणु
	काष्ठा devres_node		node;
	/*
	 * Some archs want to perक्रमm DMA पूर्णांकo kदो_स्मृति caches
	 * and need a guaranteed alignment larger than
	 * the alignment of a 64-bit पूर्णांकeger.
	 * Thus we use ARCH_KMALLOC_MINALIGN here and get exactly the same
	 * buffer alignment as अगर it was allocated by plain kदो_स्मृति().
	 */
	u8 __aligned(ARCH_KMALLOC_MINALIGN) data[];
पूर्ण;

काष्ठा devres_group अणु
	काष्ठा devres_node		node[2];
	व्योम				*id;
	पूर्णांक				color;
	/* -- 8 poपूर्णांकers */
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_DEVRES
अटल पूर्णांक log_devres = 0;
module_param_named(log, log_devres, पूर्णांक, S_IRUGO | S_IWUSR);

अटल व्योम set_node_dbginfo(काष्ठा devres_node *node, स्थिर अक्षर *name,
			     माप_प्रकार size)
अणु
	node->name = name;
	node->size = size;
पूर्ण

अटल व्योम devres_log(काष्ठा device *dev, काष्ठा devres_node *node,
		       स्थिर अक्षर *op)
अणु
	अगर (unlikely(log_devres))
		dev_err(dev, "DEVRES %3s %p %s (%zu bytes)\n",
			op, node, node->name, node->size);
पूर्ण
#अन्यथा /* CONFIG_DEBUG_DEVRES */
#घोषणा set_node_dbginfo(node, n, s)	करो अणुपूर्ण जबतक (0)
#घोषणा devres_log(dev, node, op)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_DEBUG_DEVRES */

/*
 * Release functions क्रम devres group.  These callbacks are used only
 * क्रम identअगरication.
 */
अटल व्योम group_खोलो_release(काष्ठा device *dev, व्योम *res)
अणु
	/* noop */
पूर्ण

अटल व्योम group_बंद_release(काष्ठा device *dev, व्योम *res)
अणु
	/* noop */
पूर्ण

अटल काष्ठा devres_group * node_to_group(काष्ठा devres_node *node)
अणु
	अगर (node->release == &group_खोलो_release)
		वापस container_of(node, काष्ठा devres_group, node[0]);
	अगर (node->release == &group_बंद_release)
		वापस container_of(node, काष्ठा devres_group, node[1]);
	वापस शून्य;
पूर्ण

अटल bool check_dr_size(माप_प्रकार size, माप_प्रकार *tot_size)
अणु
	/* We must catch any near-SIZE_MAX हालs that could overflow. */
	अगर (unlikely(check_add_overflow(माप(काष्ठा devres),
					size, tot_size)))
		वापस false;

	वापस true;
पूर्ण

अटल __always_अंतरभूत काष्ठा devres * alloc_dr(dr_release_t release,
						माप_प्रकार size, gfp_t gfp, पूर्णांक nid)
अणु
	माप_प्रकार tot_size;
	काष्ठा devres *dr;

	अगर (!check_dr_size(size, &tot_size))
		वापस शून्य;

	dr = kदो_स्मृति_node_track_caller(tot_size, gfp, nid);
	अगर (unlikely(!dr))
		वापस शून्य;

	स_रखो(dr, 0, दुरत्व(काष्ठा devres, data));

	INIT_LIST_HEAD(&dr->node.entry);
	dr->node.release = release;
	वापस dr;
पूर्ण

अटल व्योम add_dr(काष्ठा device *dev, काष्ठा devres_node *node)
अणु
	devres_log(dev, node, "ADD");
	BUG_ON(!list_empty(&node->entry));
	list_add_tail(&node->entry, &dev->devres_head);
पूर्ण

अटल व्योम replace_dr(काष्ठा device *dev,
		       काष्ठा devres_node *old, काष्ठा devres_node *new)
अणु
	devres_log(dev, old, "REPLACE");
	BUG_ON(!list_empty(&new->entry));
	list_replace(&old->entry, &new->entry);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_DEVRES
व्योम * __devres_alloc_node(dr_release_t release, माप_प्रकार size, gfp_t gfp, पूर्णांक nid,
		      स्थिर अक्षर *name)
अणु
	काष्ठा devres *dr;

	dr = alloc_dr(release, size, gfp | __GFP_ZERO, nid);
	अगर (unlikely(!dr))
		वापस शून्य;
	set_node_dbginfo(&dr->node, name, size);
	वापस dr->data;
पूर्ण
EXPORT_SYMBOL_GPL(__devres_alloc_node);
#अन्यथा
/**
 * devres_alloc_node - Allocate device resource data
 * @release: Release function devres will be associated with
 * @size: Allocation size
 * @gfp: Allocation flags
 * @nid: NUMA node
 *
 * Allocate devres of @size bytes.  The allocated area is zeroed, then
 * associated with @release.  The वापसed poपूर्णांकer can be passed to
 * other devres_*() functions.
 *
 * RETURNS:
 * Poपूर्णांकer to allocated devres on success, शून्य on failure.
 */
व्योम * devres_alloc_node(dr_release_t release, माप_प्रकार size, gfp_t gfp, पूर्णांक nid)
अणु
	काष्ठा devres *dr;

	dr = alloc_dr(release, size, gfp | __GFP_ZERO, nid);
	अगर (unlikely(!dr))
		वापस शून्य;
	वापस dr->data;
पूर्ण
EXPORT_SYMBOL_GPL(devres_alloc_node);
#पूर्ण_अगर

/**
 * devres_क्रम_each_res - Resource iterator
 * @dev: Device to iterate resource from
 * @release: Look क्रम resources associated with this release function
 * @match: Match function (optional)
 * @match_data: Data क्रम the match function
 * @fn: Function to be called क्रम each matched resource.
 * @data: Data क्रम @fn, the 3rd parameter of @fn
 *
 * Call @fn क्रम each devres of @dev which is associated with @release
 * and क्रम which @match वापसs 1.
 *
 * RETURNS:
 * 	व्योम
 */
व्योम devres_क्रम_each_res(काष्ठा device *dev, dr_release_t release,
			dr_match_t match, व्योम *match_data,
			व्योम (*fn)(काष्ठा device *, व्योम *, व्योम *),
			व्योम *data)
अणु
	काष्ठा devres_node *node;
	काष्ठा devres_node *पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (!fn)
		वापस;

	spin_lock_irqsave(&dev->devres_lock, flags);
	list_क्रम_each_entry_safe_reverse(node, पंचांगp,
			&dev->devres_head, entry) अणु
		काष्ठा devres *dr = container_of(node, काष्ठा devres, node);

		अगर (node->release != release)
			जारी;
		अगर (match && !match(dev, dr->data, match_data))
			जारी;
		fn(dev, dr->data, data);
	पूर्ण
	spin_unlock_irqrestore(&dev->devres_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(devres_क्रम_each_res);

/**
 * devres_मुक्त - Free device resource data
 * @res: Poपूर्णांकer to devres data to मुक्त
 *
 * Free devres created with devres_alloc().
 */
व्योम devres_मुक्त(व्योम *res)
अणु
	अगर (res) अणु
		काष्ठा devres *dr = container_of(res, काष्ठा devres, data);

		BUG_ON(!list_empty(&dr->node.entry));
		kमुक्त(dr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(devres_मुक्त);

/**
 * devres_add - Register device resource
 * @dev: Device to add resource to
 * @res: Resource to रेजिस्टर
 *
 * Register devres @res to @dev.  @res should have been allocated
 * using devres_alloc().  On driver detach, the associated release
 * function will be invoked and devres will be मुक्तd स्वतःmatically.
 */
व्योम devres_add(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा devres *dr = container_of(res, काष्ठा devres, data);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->devres_lock, flags);
	add_dr(dev, &dr->node);
	spin_unlock_irqrestore(&dev->devres_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(devres_add);

अटल काष्ठा devres *find_dr(काष्ठा device *dev, dr_release_t release,
			      dr_match_t match, व्योम *match_data)
अणु
	काष्ठा devres_node *node;

	list_क्रम_each_entry_reverse(node, &dev->devres_head, entry) अणु
		काष्ठा devres *dr = container_of(node, काष्ठा devres, node);

		अगर (node->release != release)
			जारी;
		अगर (match && !match(dev, dr->data, match_data))
			जारी;
		वापस dr;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * devres_find - Find device resource
 * @dev: Device to lookup resource from
 * @release: Look क्रम resources associated with this release function
 * @match: Match function (optional)
 * @match_data: Data क्रम the match function
 *
 * Find the latest devres of @dev which is associated with @release
 * and क्रम which @match वापसs 1.  If @match is शून्य, it's considered
 * to match all.
 *
 * RETURNS:
 * Poपूर्णांकer to found devres, शून्य अगर not found.
 */
व्योम * devres_find(काष्ठा device *dev, dr_release_t release,
		   dr_match_t match, व्योम *match_data)
अणु
	काष्ठा devres *dr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->devres_lock, flags);
	dr = find_dr(dev, release, match, match_data);
	spin_unlock_irqrestore(&dev->devres_lock, flags);

	अगर (dr)
		वापस dr->data;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(devres_find);

/**
 * devres_get - Find devres, अगर non-existent, add one atomically
 * @dev: Device to lookup or add devres क्रम
 * @new_res: Poपूर्णांकer to new initialized devres to add अगर not found
 * @match: Match function (optional)
 * @match_data: Data क्रम the match function
 *
 * Find the latest devres of @dev which has the same release function
 * as @new_res and क्रम which @match वापस 1.  If found, @new_res is
 * मुक्तd; otherwise, @new_res is added atomically.
 *
 * RETURNS:
 * Poपूर्णांकer to found or added devres.
 */
व्योम * devres_get(काष्ठा device *dev, व्योम *new_res,
		  dr_match_t match, व्योम *match_data)
अणु
	काष्ठा devres *new_dr = container_of(new_res, काष्ठा devres, data);
	काष्ठा devres *dr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->devres_lock, flags);
	dr = find_dr(dev, new_dr->node.release, match, match_data);
	अगर (!dr) अणु
		add_dr(dev, &new_dr->node);
		dr = new_dr;
		new_res = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&dev->devres_lock, flags);
	devres_मुक्त(new_res);

	वापस dr->data;
पूर्ण
EXPORT_SYMBOL_GPL(devres_get);

/**
 * devres_हटाओ - Find a device resource and हटाओ it
 * @dev: Device to find resource from
 * @release: Look क्रम resources associated with this release function
 * @match: Match function (optional)
 * @match_data: Data क्रम the match function
 *
 * Find the latest devres of @dev associated with @release and क्रम
 * which @match वापसs 1.  If @match is शून्य, it's considered to
 * match all.  If found, the resource is हटाओd atomically and
 * वापसed.
 *
 * RETURNS:
 * Poपूर्णांकer to हटाओd devres on success, शून्य अगर not found.
 */
व्योम * devres_हटाओ(काष्ठा device *dev, dr_release_t release,
		     dr_match_t match, व्योम *match_data)
अणु
	काष्ठा devres *dr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->devres_lock, flags);
	dr = find_dr(dev, release, match, match_data);
	अगर (dr) अणु
		list_del_init(&dr->node.entry);
		devres_log(dev, &dr->node, "REM");
	पूर्ण
	spin_unlock_irqrestore(&dev->devres_lock, flags);

	अगर (dr)
		वापस dr->data;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(devres_हटाओ);

/**
 * devres_destroy - Find a device resource and destroy it
 * @dev: Device to find resource from
 * @release: Look क्रम resources associated with this release function
 * @match: Match function (optional)
 * @match_data: Data क्रम the match function
 *
 * Find the latest devres of @dev associated with @release and क्रम
 * which @match वापसs 1.  If @match is शून्य, it's considered to
 * match all.  If found, the resource is हटाओd atomically and मुक्तd.
 *
 * Note that the release function क्रम the resource will not be called,
 * only the devres-allocated data will be मुक्तd.  The caller becomes
 * responsible क्रम मुक्तing any other data.
 *
 * RETURNS:
 * 0 अगर devres is found and मुक्तd, -ENOENT अगर not found.
 */
पूर्णांक devres_destroy(काष्ठा device *dev, dr_release_t release,
		   dr_match_t match, व्योम *match_data)
अणु
	व्योम *res;

	res = devres_हटाओ(dev, release, match, match_data);
	अगर (unlikely(!res))
		वापस -ENOENT;

	devres_मुक्त(res);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devres_destroy);


/**
 * devres_release - Find a device resource and destroy it, calling release
 * @dev: Device to find resource from
 * @release: Look क्रम resources associated with this release function
 * @match: Match function (optional)
 * @match_data: Data क्रम the match function
 *
 * Find the latest devres of @dev associated with @release and क्रम
 * which @match वापसs 1.  If @match is शून्य, it's considered to
 * match all.  If found, the resource is हटाओd atomically, the
 * release function called and the resource मुक्तd.
 *
 * RETURNS:
 * 0 अगर devres is found and मुक्तd, -ENOENT अगर not found.
 */
पूर्णांक devres_release(काष्ठा device *dev, dr_release_t release,
		   dr_match_t match, व्योम *match_data)
अणु
	व्योम *res;

	res = devres_हटाओ(dev, release, match, match_data);
	अगर (unlikely(!res))
		वापस -ENOENT;

	(*release)(dev, res);
	devres_मुक्त(res);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devres_release);

अटल पूर्णांक हटाओ_nodes(काष्ठा device *dev,
			काष्ठा list_head *first, काष्ठा list_head *end,
			काष्ठा list_head *toकरो)
अणु
	पूर्णांक cnt = 0, nr_groups = 0;
	काष्ठा list_head *cur;

	/* First pass - move normal devres entries to @toकरो and clear
	 * devres_group colors.
	 */
	cur = first;
	जबतक (cur != end) अणु
		काष्ठा devres_node *node;
		काष्ठा devres_group *grp;

		node = list_entry(cur, काष्ठा devres_node, entry);
		cur = cur->next;

		grp = node_to_group(node);
		अगर (grp) अणु
			/* clear color of group markers in the first pass */
			grp->color = 0;
			nr_groups++;
		पूर्ण अन्यथा अणु
			/* regular devres entry */
			अगर (&node->entry == first)
				first = first->next;
			list_move_tail(&node->entry, toकरो);
			cnt++;
		पूर्ण
	पूर्ण

	अगर (!nr_groups)
		वापस cnt;

	/* Second pass - Scan groups and color them.  A group माला_लो
	 * color value of two अगरf the group is wholly contained in
	 * [cur, end).  That is, क्रम a बंदd group, both खोलोing and
	 * closing markers should be in the range, जबतक just the
	 * खोलोing marker is enough क्रम an खोलो group.
	 */
	cur = first;
	जबतक (cur != end) अणु
		काष्ठा devres_node *node;
		काष्ठा devres_group *grp;

		node = list_entry(cur, काष्ठा devres_node, entry);
		cur = cur->next;

		grp = node_to_group(node);
		BUG_ON(!grp || list_empty(&grp->node[0].entry));

		grp->color++;
		अगर (list_empty(&grp->node[1].entry))
			grp->color++;

		BUG_ON(grp->color <= 0 || grp->color > 2);
		अगर (grp->color == 2) अणु
			/* No need to update cur or end.  The हटाओd
			 * nodes are always beक्रमe both.
			 */
			list_move_tail(&grp->node[0].entry, toकरो);
			list_del_init(&grp->node[1].entry);
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण

अटल पूर्णांक release_nodes(काष्ठा device *dev, काष्ठा list_head *first,
			 काष्ठा list_head *end, अचिन्हित दीर्घ flags)
	__releases(&dev->devres_lock)
अणु
	LIST_HEAD(toकरो);
	पूर्णांक cnt;
	काष्ठा devres *dr, *पंचांगp;

	cnt = हटाओ_nodes(dev, first, end, &toकरो);

	spin_unlock_irqrestore(&dev->devres_lock, flags);

	/* Release.  Note that both devres and devres_group are
	 * handled as devres in the following loop.  This is safe.
	 */
	list_क्रम_each_entry_safe_reverse(dr, पंचांगp, &toकरो, node.entry) अणु
		devres_log(dev, &dr->node, "REL");
		dr->node.release(dev, dr->data);
		kमुक्त(dr);
	पूर्ण

	वापस cnt;
पूर्ण

/**
 * devres_release_all - Release all managed resources
 * @dev: Device to release resources क्रम
 *
 * Release all resources associated with @dev.  This function is
 * called on driver detach.
 */
पूर्णांक devres_release_all(काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ flags;

	/* Looks like an uninitialized device काष्ठाure */
	अगर (WARN_ON(dev->devres_head.next == शून्य))
		वापस -ENODEV;
	spin_lock_irqsave(&dev->devres_lock, flags);
	वापस release_nodes(dev, dev->devres_head.next, &dev->devres_head,
			     flags);
पूर्ण

/**
 * devres_खोलो_group - Open a new devres group
 * @dev: Device to खोलो devres group क्रम
 * @id: Separator ID
 * @gfp: Allocation flags
 *
 * Open a new devres group क्रम @dev with @id.  For @id, using a
 * poपूर्णांकer to an object which won't be used क्रम another group is
 * recommended.  If @id is शून्य, address-wise unique ID is created.
 *
 * RETURNS:
 * ID of the new group, शून्य on failure.
 */
व्योम * devres_खोलो_group(काष्ठा device *dev, व्योम *id, gfp_t gfp)
अणु
	काष्ठा devres_group *grp;
	अचिन्हित दीर्घ flags;

	grp = kदो_स्मृति(माप(*grp), gfp);
	अगर (unlikely(!grp))
		वापस शून्य;

	grp->node[0].release = &group_खोलो_release;
	grp->node[1].release = &group_बंद_release;
	INIT_LIST_HEAD(&grp->node[0].entry);
	INIT_LIST_HEAD(&grp->node[1].entry);
	set_node_dbginfo(&grp->node[0], "grp<", 0);
	set_node_dbginfo(&grp->node[1], "grp>", 0);
	grp->id = grp;
	अगर (id)
		grp->id = id;

	spin_lock_irqsave(&dev->devres_lock, flags);
	add_dr(dev, &grp->node[0]);
	spin_unlock_irqrestore(&dev->devres_lock, flags);
	वापस grp->id;
पूर्ण
EXPORT_SYMBOL_GPL(devres_खोलो_group);

/* Find devres group with ID @id.  If @id is शून्य, look क्रम the latest. */
अटल काष्ठा devres_group * find_group(काष्ठा device *dev, व्योम *id)
अणु
	काष्ठा devres_node *node;

	list_क्रम_each_entry_reverse(node, &dev->devres_head, entry) अणु
		काष्ठा devres_group *grp;

		अगर (node->release != &group_खोलो_release)
			जारी;

		grp = container_of(node, काष्ठा devres_group, node[0]);

		अगर (id) अणु
			अगर (grp->id == id)
				वापस grp;
		पूर्ण अन्यथा अगर (list_empty(&grp->node[1].entry))
			वापस grp;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * devres_बंद_group - Close a devres group
 * @dev: Device to बंद devres group क्रम
 * @id: ID of target group, can be शून्य
 *
 * Close the group identअगरied by @id.  If @id is शून्य, the latest खोलो
 * group is selected.
 */
व्योम devres_बंद_group(काष्ठा device *dev, व्योम *id)
अणु
	काष्ठा devres_group *grp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->devres_lock, flags);

	grp = find_group(dev, id);
	अगर (grp)
		add_dr(dev, &grp->node[1]);
	अन्यथा
		WARN_ON(1);

	spin_unlock_irqrestore(&dev->devres_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(devres_बंद_group);

/**
 * devres_हटाओ_group - Remove a devres group
 * @dev: Device to हटाओ group क्रम
 * @id: ID of target group, can be शून्य
 *
 * Remove the group identअगरied by @id.  If @id is शून्य, the latest
 * खोलो group is selected.  Note that removing a group करोesn't affect
 * any other resources.
 */
व्योम devres_हटाओ_group(काष्ठा device *dev, व्योम *id)
अणु
	काष्ठा devres_group *grp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->devres_lock, flags);

	grp = find_group(dev, id);
	अगर (grp) अणु
		list_del_init(&grp->node[0].entry);
		list_del_init(&grp->node[1].entry);
		devres_log(dev, &grp->node[0], "REM");
	पूर्ण अन्यथा
		WARN_ON(1);

	spin_unlock_irqrestore(&dev->devres_lock, flags);

	kमुक्त(grp);
पूर्ण
EXPORT_SYMBOL_GPL(devres_हटाओ_group);

/**
 * devres_release_group - Release resources in a devres group
 * @dev: Device to release group क्रम
 * @id: ID of target group, can be शून्य
 *
 * Release all resources in the group identअगरied by @id.  If @id is
 * शून्य, the latest खोलो group is selected.  The selected group and
 * groups properly nested inside the selected group are हटाओd.
 *
 * RETURNS:
 * The number of released non-group resources.
 */
पूर्णांक devres_release_group(काष्ठा device *dev, व्योम *id)
अणु
	काष्ठा devres_group *grp;
	अचिन्हित दीर्घ flags;
	पूर्णांक cnt = 0;

	spin_lock_irqsave(&dev->devres_lock, flags);

	grp = find_group(dev, id);
	अगर (grp) अणु
		काष्ठा list_head *first = &grp->node[0].entry;
		काष्ठा list_head *end = &dev->devres_head;

		अगर (!list_empty(&grp->node[1].entry))
			end = grp->node[1].entry.next;

		cnt = release_nodes(dev, first, end, flags);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		spin_unlock_irqrestore(&dev->devres_lock, flags);
	पूर्ण

	वापस cnt;
पूर्ण
EXPORT_SYMBOL_GPL(devres_release_group);

/*
 * Custom devres actions allow inserting a simple function call
 * पूर्णांकo the teaकरोwn sequence.
 */

काष्ठा action_devres अणु
	व्योम *data;
	व्योम (*action)(व्योम *);
पूर्ण;

अटल पूर्णांक devm_action_match(काष्ठा device *dev, व्योम *res, व्योम *p)
अणु
	काष्ठा action_devres *devres = res;
	काष्ठा action_devres *target = p;

	वापस devres->action == target->action &&
	       devres->data == target->data;
पूर्ण

अटल व्योम devm_action_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा action_devres *devres = res;

	devres->action(devres->data);
पूर्ण

/**
 * devm_add_action() - add a custom action to list of managed resources
 * @dev: Device that owns the action
 * @action: Function that should be called
 * @data: Poपूर्णांकer to data passed to @action implementation
 *
 * This adds a custom action to the list of managed resources so that
 * it माला_लो executed as part of standard resource unwinding.
 */
पूर्णांक devm_add_action(काष्ठा device *dev, व्योम (*action)(व्योम *), व्योम *data)
अणु
	काष्ठा action_devres *devres;

	devres = devres_alloc(devm_action_release,
			      माप(काष्ठा action_devres), GFP_KERNEL);
	अगर (!devres)
		वापस -ENOMEM;

	devres->data = data;
	devres->action = action;

	devres_add(dev, devres);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_add_action);

/**
 * devm_हटाओ_action() - हटाओs previously added custom action
 * @dev: Device that owns the action
 * @action: Function implementing the action
 * @data: Poपूर्णांकer to data passed to @action implementation
 *
 * Removes instance of @action previously added by devm_add_action().
 * Both action and data should match one of the existing entries.
 */
व्योम devm_हटाओ_action(काष्ठा device *dev, व्योम (*action)(व्योम *), व्योम *data)
अणु
	काष्ठा action_devres devres = अणु
		.data = data,
		.action = action,
	पूर्ण;

	WARN_ON(devres_destroy(dev, devm_action_release, devm_action_match,
			       &devres));
पूर्ण
EXPORT_SYMBOL_GPL(devm_हटाओ_action);

/**
 * devm_release_action() - release previously added custom action
 * @dev: Device that owns the action
 * @action: Function implementing the action
 * @data: Poपूर्णांकer to data passed to @action implementation
 *
 * Releases and हटाओs instance of @action previously added by
 * devm_add_action().  Both action and data should match one of the
 * existing entries.
 */
व्योम devm_release_action(काष्ठा device *dev, व्योम (*action)(व्योम *), व्योम *data)
अणु
	काष्ठा action_devres devres = अणु
		.data = data,
		.action = action,
	पूर्ण;

	WARN_ON(devres_release(dev, devm_action_release, devm_action_match,
			       &devres));

पूर्ण
EXPORT_SYMBOL_GPL(devm_release_action);

/*
 * Managed kदो_स्मृति/kमुक्त
 */
अटल व्योम devm_kदो_स्मृति_release(काष्ठा device *dev, व्योम *res)
अणु
	/* noop */
पूर्ण

अटल पूर्णांक devm_kदो_स्मृति_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	वापस res == data;
पूर्ण

/**
 * devm_kदो_स्मृति - Resource-managed kदो_स्मृति
 * @dev: Device to allocate memory क्रम
 * @size: Allocation size
 * @gfp: Allocation gfp flags
 *
 * Managed kदो_स्मृति.  Memory allocated with this function is
 * स्वतःmatically मुक्तd on driver detach.  Like all other devres
 * resources, guaranteed alignment is अचिन्हित दीर्घ दीर्घ.
 *
 * RETURNS:
 * Poपूर्णांकer to allocated memory on success, शून्य on failure.
 */
व्योम *devm_kदो_स्मृति(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp)
अणु
	काष्ठा devres *dr;

	अगर (unlikely(!size))
		वापस ZERO_SIZE_PTR;

	/* use raw alloc_dr क्रम kदो_स्मृति caller tracing */
	dr = alloc_dr(devm_kदो_स्मृति_release, size, gfp, dev_to_node(dev));
	अगर (unlikely(!dr))
		वापस शून्य;

	/*
	 * This is named devm_kzalloc_release क्रम historical reasons
	 * The initial implementation did not support kदो_स्मृति, only kzalloc
	 */
	set_node_dbginfo(&dr->node, "devm_kzalloc_release", size);
	devres_add(dev, dr->data);
	वापस dr->data;
पूर्ण
EXPORT_SYMBOL_GPL(devm_kदो_स्मृति);

/**
 * devm_kपुनः_स्मृति - Resource-managed kपुनः_स्मृति()
 * @dev: Device to re-allocate memory क्रम
 * @ptr: Poपूर्णांकer to the memory chunk to re-allocate
 * @new_size: New allocation size
 * @gfp: Allocation gfp flags
 *
 * Managed kपुनः_स्मृति(). Resizes the memory chunk allocated with devm_kदो_स्मृति().
 * Behaves similarly to regular kपुनः_स्मृति(): अगर @ptr is शून्य or ZERO_SIZE_PTR,
 * it's the equivalent of devm_kदो_स्मृति(). If new_size is zero, it मुक्तs the
 * previously allocated memory and वापसs ZERO_SIZE_PTR. This function करोesn't
 * change the order in which the release callback क्रम the re-alloc'ed devres
 * will be called (except when falling back to devm_kदो_स्मृति() or when मुक्तing
 * resources when new_size is zero). The contents of the memory are preserved
 * up to the lesser of new and old sizes.
 */
व्योम *devm_kपुनः_स्मृति(काष्ठा device *dev, व्योम *ptr, माप_प्रकार new_size, gfp_t gfp)
अणु
	माप_प्रकार total_new_size, total_old_size;
	काष्ठा devres *old_dr, *new_dr;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!new_size)) अणु
		devm_kमुक्त(dev, ptr);
		वापस ZERO_SIZE_PTR;
	पूर्ण

	अगर (unlikely(ZERO_OR_शून्य_PTR(ptr)))
		वापस devm_kदो_स्मृति(dev, new_size, gfp);

	अगर (WARN_ON(is_kernel_rodata((अचिन्हित दीर्घ)ptr)))
		/*
		 * We cannot reliably पुनः_स्मृति a स्थिर string वापसed by
		 * devm_kstrdup_स्थिर().
		 */
		वापस शून्य;

	अगर (!check_dr_size(new_size, &total_new_size))
		वापस शून्य;

	total_old_size = ksize(container_of(ptr, काष्ठा devres, data));
	अगर (total_old_size == 0) अणु
		WARN(1, "Pointer doesn't point to dynamically allocated memory.");
		वापस शून्य;
	पूर्ण

	/*
	 * If new size is smaller or equal to the actual number of bytes
	 * allocated previously - just वापस the same poपूर्णांकer.
	 */
	अगर (total_new_size <= total_old_size)
		वापस ptr;

	/*
	 * Otherwise: allocate new, larger chunk. We need to allocate beक्रमe
	 * taking the lock as most probably the caller uses GFP_KERNEL.
	 */
	new_dr = alloc_dr(devm_kदो_स्मृति_release,
			  total_new_size, gfp, dev_to_node(dev));
	अगर (!new_dr)
		वापस शून्य;

	/*
	 * The spinlock protects the linked list against concurrent
	 * modअगरications but not the resource itself.
	 */
	spin_lock_irqsave(&dev->devres_lock, flags);

	old_dr = find_dr(dev, devm_kदो_स्मृति_release, devm_kदो_स्मृति_match, ptr);
	अगर (!old_dr) अणु
		spin_unlock_irqrestore(&dev->devres_lock, flags);
		kमुक्त(new_dr);
		WARN(1, "Memory chunk not managed or managed by a different device.");
		वापस शून्य;
	पूर्ण

	replace_dr(dev, &old_dr->node, &new_dr->node);

	spin_unlock_irqrestore(&dev->devres_lock, flags);

	/*
	 * We can copy the memory contents after releasing the lock as we're
	 * no दीर्घer modyfing the list links.
	 */
	स_नकल(new_dr->data, old_dr->data,
	       total_old_size - दुरत्व(काष्ठा devres, data));
	/*
	 * Same क्रम releasing the old devres - it's now been हटाओd from the
	 * list. This is also the reason why we must not use devm_kमुक्त() - the
	 * links are no दीर्घer valid.
	 */
	kमुक्त(old_dr);

	वापस new_dr->data;
पूर्ण
EXPORT_SYMBOL_GPL(devm_kपुनः_स्मृति);

/**
 * devm_kstrdup - Allocate resource managed space and
 *                copy an existing string पूर्णांकo that.
 * @dev: Device to allocate memory क्रम
 * @s: the string to duplicate
 * @gfp: the GFP mask used in the devm_kदो_स्मृति() call when
 *       allocating memory
 * RETURNS:
 * Poपूर्णांकer to allocated string on success, शून्य on failure.
 */
अक्षर *devm_kstrdup(काष्ठा device *dev, स्थिर अक्षर *s, gfp_t gfp)
अणु
	माप_प्रकार size;
	अक्षर *buf;

	अगर (!s)
		वापस शून्य;

	size = म_माप(s) + 1;
	buf = devm_kदो_स्मृति(dev, size, gfp);
	अगर (buf)
		स_नकल(buf, s, size);
	वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(devm_kstrdup);

/**
 * devm_kstrdup_स्थिर - resource managed conditional string duplication
 * @dev: device क्रम which to duplicate the string
 * @s: the string to duplicate
 * @gfp: the GFP mask used in the kदो_स्मृति() call when allocating memory
 *
 * Strings allocated by devm_kstrdup_स्थिर will be स्वतःmatically मुक्तd when
 * the associated device is detached.
 *
 * RETURNS:
 * Source string अगर it is in .rodata section otherwise it falls back to
 * devm_kstrdup.
 */
स्थिर अक्षर *devm_kstrdup_स्थिर(काष्ठा device *dev, स्थिर अक्षर *s, gfp_t gfp)
अणु
	अगर (is_kernel_rodata((अचिन्हित दीर्घ)s))
		वापस s;

	वापस devm_kstrdup(dev, s, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(devm_kstrdup_स्थिर);

/**
 * devm_kvaप्र_लिखो - Allocate resource managed space and क्रमmat a string
 *		     पूर्णांकo that.
 * @dev: Device to allocate memory क्रम
 * @gfp: the GFP mask used in the devm_kदो_स्मृति() call when
 *       allocating memory
 * @fmt: The म_लिखो()-style क्रमmat string
 * @ap: Arguments क्रम the क्रमmat string
 * RETURNS:
 * Poपूर्णांकer to allocated string on success, शून्य on failure.
 */
अक्षर *devm_kvaप्र_लिखो(काष्ठा device *dev, gfp_t gfp, स्थिर अक्षर *fmt,
		      बहु_सूची ap)
अणु
	अचिन्हित पूर्णांक len;
	अक्षर *p;
	बहु_सूची aq;

	va_copy(aq, ap);
	len = vsnम_लिखो(शून्य, 0, fmt, aq);
	बहु_पूर्ण(aq);

	p = devm_kदो_स्मृति(dev, len+1, gfp);
	अगर (!p)
		वापस शून्य;

	vsnम_लिखो(p, len+1, fmt, ap);

	वापस p;
पूर्ण
EXPORT_SYMBOL(devm_kvaप्र_लिखो);

/**
 * devm_kaप्र_लिखो - Allocate resource managed space and क्रमmat a string
 *		    पूर्णांकo that.
 * @dev: Device to allocate memory क्रम
 * @gfp: the GFP mask used in the devm_kदो_स्मृति() call when
 *       allocating memory
 * @fmt: The म_लिखो()-style क्रमmat string
 * @...: Arguments क्रम the क्रमmat string
 * RETURNS:
 * Poपूर्णांकer to allocated string on success, शून्य on failure.
 */
अक्षर *devm_kaप्र_लिखो(काष्ठा device *dev, gfp_t gfp, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर *p;

	बहु_शुरू(ap, fmt);
	p = devm_kvaप्र_लिखो(dev, gfp, fmt, ap);
	बहु_पूर्ण(ap);

	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(devm_kaप्र_लिखो);

/**
 * devm_kमुक्त - Resource-managed kमुक्त
 * @dev: Device this memory beदीर्घs to
 * @p: Memory to मुक्त
 *
 * Free memory allocated with devm_kदो_स्मृति().
 */
व्योम devm_kमुक्त(काष्ठा device *dev, स्थिर व्योम *p)
अणु
	पूर्णांक rc;

	/*
	 * Special हालs: poपूर्णांकer to a string in .rodata वापसed by
	 * devm_kstrdup_स्थिर() or शून्य/ZERO ptr.
	 */
	अगर (unlikely(is_kernel_rodata((अचिन्हित दीर्घ)p) || ZERO_OR_शून्य_PTR(p)))
		वापस;

	rc = devres_destroy(dev, devm_kदो_स्मृति_release,
			    devm_kदो_स्मृति_match, (व्योम *)p);
	WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_kमुक्त);

/**
 * devm_kmemdup - Resource-managed kmemdup
 * @dev: Device this memory beदीर्घs to
 * @src: Memory region to duplicate
 * @len: Memory region length
 * @gfp: GFP mask to use
 *
 * Duplicate region of a memory using resource managed kदो_स्मृति
 */
व्योम *devm_kmemdup(काष्ठा device *dev, स्थिर व्योम *src, माप_प्रकार len, gfp_t gfp)
अणु
	व्योम *p;

	p = devm_kदो_स्मृति(dev, len, gfp);
	अगर (p)
		स_नकल(p, src, len);

	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(devm_kmemdup);

काष्ठा pages_devres अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक order;
पूर्ण;

अटल पूर्णांक devm_pages_match(काष्ठा device *dev, व्योम *res, व्योम *p)
अणु
	काष्ठा pages_devres *devres = res;
	काष्ठा pages_devres *target = p;

	वापस devres->addr == target->addr;
पूर्ण

अटल व्योम devm_pages_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा pages_devres *devres = res;

	मुक्त_pages(devres->addr, devres->order);
पूर्ण

/**
 * devm_get_मुक्त_pages - Resource-managed __get_मुक्त_pages
 * @dev: Device to allocate memory क्रम
 * @gfp_mask: Allocation gfp flags
 * @order: Allocation size is (1 << order) pages
 *
 * Managed get_मुक्त_pages.  Memory allocated with this function is
 * स्वतःmatically मुक्तd on driver detach.
 *
 * RETURNS:
 * Address of allocated memory on success, 0 on failure.
 */

अचिन्हित दीर्घ devm_get_मुक्त_pages(काष्ठा device *dev,
				  gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	काष्ठा pages_devres *devres;
	अचिन्हित दीर्घ addr;

	addr = __get_मुक्त_pages(gfp_mask, order);

	अगर (unlikely(!addr))
		वापस 0;

	devres = devres_alloc(devm_pages_release,
			      माप(काष्ठा pages_devres), GFP_KERNEL);
	अगर (unlikely(!devres)) अणु
		मुक्त_pages(addr, order);
		वापस 0;
	पूर्ण

	devres->addr = addr;
	devres->order = order;

	devres_add(dev, devres);
	वापस addr;
पूर्ण
EXPORT_SYMBOL_GPL(devm_get_मुक्त_pages);

/**
 * devm_मुक्त_pages - Resource-managed मुक्त_pages
 * @dev: Device this memory beदीर्घs to
 * @addr: Memory to मुक्त
 *
 * Free memory allocated with devm_get_मुक्त_pages(). Unlike मुक्त_pages,
 * there is no need to supply the @order.
 */
व्योम devm_मुक्त_pages(काष्ठा device *dev, अचिन्हित दीर्घ addr)
अणु
	काष्ठा pages_devres devres = अणु .addr = addr पूर्ण;

	WARN_ON(devres_release(dev, devm_pages_release, devm_pages_match,
			       &devres));
पूर्ण
EXPORT_SYMBOL_GPL(devm_मुक्त_pages);

अटल व्योम devm_percpu_release(काष्ठा device *dev, व्योम *pdata)
अणु
	व्योम __percpu *p;

	p = *(व्योम __percpu **)pdata;
	मुक्त_percpu(p);
पूर्ण

अटल पूर्णांक devm_percpu_match(काष्ठा device *dev, व्योम *data, व्योम *p)
अणु
	काष्ठा devres *devr = container_of(data, काष्ठा devres, data);

	वापस *(व्योम **)devr->data == p;
पूर्ण

/**
 * __devm_alloc_percpu - Resource-managed alloc_percpu
 * @dev: Device to allocate per-cpu memory क्रम
 * @size: Size of per-cpu memory to allocate
 * @align: Alignment of per-cpu memory to allocate
 *
 * Managed alloc_percpu. Per-cpu memory allocated with this function is
 * स्वतःmatically मुक्तd on driver detach.
 *
 * RETURNS:
 * Poपूर्णांकer to allocated memory on success, शून्य on failure.
 */
व्योम __percpu *__devm_alloc_percpu(काष्ठा device *dev, माप_प्रकार size,
		माप_प्रकार align)
अणु
	व्योम *p;
	व्योम __percpu *pcpu;

	pcpu = __alloc_percpu(size, align);
	अगर (!pcpu)
		वापस शून्य;

	p = devres_alloc(devm_percpu_release, माप(व्योम *), GFP_KERNEL);
	अगर (!p) अणु
		मुक्त_percpu(pcpu);
		वापस शून्य;
	पूर्ण

	*(व्योम __percpu **)p = pcpu;

	devres_add(dev, p);

	वापस pcpu;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_alloc_percpu);

/**
 * devm_मुक्त_percpu - Resource-managed मुक्त_percpu
 * @dev: Device this memory beदीर्घs to
 * @pdata: Per-cpu memory to मुक्त
 *
 * Free memory allocated with devm_alloc_percpu().
 */
व्योम devm_मुक्त_percpu(काष्ठा device *dev, व्योम __percpu *pdata)
अणु
	WARN_ON(devres_destroy(dev, devm_percpu_release, devm_percpu_match,
			       (__क्रमce व्योम *)pdata));
पूर्ण
EXPORT_SYMBOL_GPL(devm_मुक्त_percpu);
