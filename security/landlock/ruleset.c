<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Landlock LSM - Ruleset management
 *
 * Copyright तऊ 2016-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#समावेश <linux/bits.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler_types.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/overflow.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश "limits.h"
#समावेश "object.h"
#समावेश "ruleset.h"

अटल काष्ठा landlock_ruleset *create_ruleset(स्थिर u32 num_layers)
अणु
	काष्ठा landlock_ruleset *new_ruleset;

	new_ruleset = kzalloc(काष्ठा_size(new_ruleset, fs_access_masks,
				num_layers), GFP_KERNEL_ACCOUNT);
	अगर (!new_ruleset)
		वापस ERR_PTR(-ENOMEM);
	refcount_set(&new_ruleset->usage, 1);
	mutex_init(&new_ruleset->lock);
	new_ruleset->root = RB_ROOT;
	new_ruleset->num_layers = num_layers;
	/*
	 * hierarchy = शून्य
	 * num_rules = 0
	 * fs_access_masks[] = 0
	 */
	वापस new_ruleset;
पूर्ण

काष्ठा landlock_ruleset *landlock_create_ruleset(स्थिर u32 fs_access_mask)
अणु
	काष्ठा landlock_ruleset *new_ruleset;

	/* Inक्रमms about useless ruleset. */
	अगर (!fs_access_mask)
		वापस ERR_PTR(-ENOMSG);
	new_ruleset = create_ruleset(1);
	अगर (!IS_ERR(new_ruleset))
		new_ruleset->fs_access_masks[0] = fs_access_mask;
	वापस new_ruleset;
पूर्ण

अटल व्योम build_check_rule(व्योम)
अणु
	स्थिर काष्ठा landlock_rule rule = अणु
		.num_layers = ~0,
	पूर्ण;

	BUILD_BUG_ON(rule.num_layers < LANDLOCK_MAX_NUM_LAYERS);
पूर्ण

अटल काष्ठा landlock_rule *create_rule(
		काष्ठा landlock_object *स्थिर object,
		स्थिर काष्ठा landlock_layer (*स्थिर layers)[],
		स्थिर u32 num_layers,
		स्थिर काष्ठा landlock_layer *स्थिर new_layer)
अणु
	काष्ठा landlock_rule *new_rule;
	u32 new_num_layers;

	build_check_rule();
	अगर (new_layer) अणु
		/* Should alपढ़ोy be checked by landlock_merge_ruleset(). */
		अगर (WARN_ON_ONCE(num_layers >= LANDLOCK_MAX_NUM_LAYERS))
			वापस ERR_PTR(-E2BIG);
		new_num_layers = num_layers + 1;
	पूर्ण अन्यथा अणु
		new_num_layers = num_layers;
	पूर्ण
	new_rule = kzalloc(काष्ठा_size(new_rule, layers, new_num_layers),
			GFP_KERNEL_ACCOUNT);
	अगर (!new_rule)
		वापस ERR_PTR(-ENOMEM);
	RB_CLEAR_NODE(&new_rule->node);
	landlock_get_object(object);
	new_rule->object = object;
	new_rule->num_layers = new_num_layers;
	/* Copies the original layer stack. */
	स_नकल(new_rule->layers, layers,
			flex_array_size(new_rule, layers, num_layers));
	अगर (new_layer)
		/* Adds a copy of @new_layer on the layer stack. */
		new_rule->layers[new_rule->num_layers - 1] = *new_layer;
	वापस new_rule;
पूर्ण

अटल व्योम मुक्त_rule(काष्ठा landlock_rule *स्थिर rule)
अणु
	might_sleep();
	अगर (!rule)
		वापस;
	landlock_put_object(rule->object);
	kमुक्त(rule);
पूर्ण

अटल व्योम build_check_ruleset(व्योम)
अणु
	स्थिर काष्ठा landlock_ruleset ruleset = अणु
		.num_rules = ~0,
		.num_layers = ~0,
	पूर्ण;
	typeof(ruleset.fs_access_masks[0]) fs_access_mask = ~0;

	BUILD_BUG_ON(ruleset.num_rules < LANDLOCK_MAX_NUM_RULES);
	BUILD_BUG_ON(ruleset.num_layers < LANDLOCK_MAX_NUM_LAYERS);
	BUILD_BUG_ON(fs_access_mask < LANDLOCK_MASK_ACCESS_FS);
पूर्ण

/**
 * insert_rule - Create and insert a rule in a ruleset
 *
 * @ruleset: The ruleset to be updated.
 * @object: The object to build the new rule with.  The underlying kernel
 *          object must be held by the caller.
 * @layers: One or multiple layers to be copied पूर्णांकo the new rule.
 * @num_layers: The number of @layers entries.
 *
 * When user space requests to add a new rule to a ruleset, @layers only
 * contains one entry and this entry is not asचिन्हित to any level.  In this
 * हाल, the new rule will extend @ruleset, similarly to a boolean OR between
 * access rights.
 *
 * When merging a ruleset in a करोमुख्य, or copying a करोमुख्य, @layers will be
 * added to @ruleset as new स्थिरraपूर्णांकs, similarly to a boolean AND between
 * access rights.
 */
अटल पूर्णांक insert_rule(काष्ठा landlock_ruleset *स्थिर ruleset,
		काष्ठा landlock_object *स्थिर object,
		स्थिर काष्ठा landlock_layer (*स्थिर layers)[],
		माप_प्रकार num_layers)
अणु
	काष्ठा rb_node **walker_node;
	काष्ठा rb_node *parent_node = शून्य;
	काष्ठा landlock_rule *new_rule;

	might_sleep();
	lockdep_निश्चित_held(&ruleset->lock);
	अगर (WARN_ON_ONCE(!object || !layers))
		वापस -ENOENT;
	walker_node = &(ruleset->root.rb_node);
	जबतक (*walker_node) अणु
		काष्ठा landlock_rule *स्थिर this = rb_entry(*walker_node,
				काष्ठा landlock_rule, node);

		अगर (this->object != object) अणु
			parent_node = *walker_node;
			अगर (this->object < object)
				walker_node = &((*walker_node)->rb_right);
			अन्यथा
				walker_node = &((*walker_node)->rb_left);
			जारी;
		पूर्ण

		/* Only a single-level layer should match an existing rule. */
		अगर (WARN_ON_ONCE(num_layers != 1))
			वापस -EINVAL;

		/* If there is a matching rule, updates it. */
		अगर ((*layers)[0].level == 0) अणु
			/*
			 * Extends access rights when the request comes from
			 * landlock_add_rule(2), i.e. @ruleset is not a करोमुख्य.
			 */
			अगर (WARN_ON_ONCE(this->num_layers != 1))
				वापस -EINVAL;
			अगर (WARN_ON_ONCE(this->layers[0].level != 0))
				वापस -EINVAL;
			this->layers[0].access |= (*layers)[0].access;
			वापस 0;
		पूर्ण

		अगर (WARN_ON_ONCE(this->layers[0].level == 0))
			वापस -EINVAL;

		/*
		 * Intersects access rights when it is a merge between a
		 * ruleset and a करोमुख्य.
		 */
		new_rule = create_rule(object, &this->layers, this->num_layers,
				&(*layers)[0]);
		अगर (IS_ERR(new_rule))
			वापस PTR_ERR(new_rule);
		rb_replace_node(&this->node, &new_rule->node, &ruleset->root);
		मुक्त_rule(this);
		वापस 0;
	पूर्ण

	/* There is no match क्रम @object. */
	build_check_ruleset();
	अगर (ruleset->num_rules >= LANDLOCK_MAX_NUM_RULES)
		वापस -E2BIG;
	new_rule = create_rule(object, layers, num_layers, शून्य);
	अगर (IS_ERR(new_rule))
		वापस PTR_ERR(new_rule);
	rb_link_node(&new_rule->node, parent_node, walker_node);
	rb_insert_color(&new_rule->node, &ruleset->root);
	ruleset->num_rules++;
	वापस 0;
पूर्ण

अटल व्योम build_check_layer(व्योम)
अणु
	स्थिर काष्ठा landlock_layer layer = अणु
		.level = ~0,
		.access = ~0,
	पूर्ण;

	BUILD_BUG_ON(layer.level < LANDLOCK_MAX_NUM_LAYERS);
	BUILD_BUG_ON(layer.access < LANDLOCK_MASK_ACCESS_FS);
पूर्ण

/* @ruleset must be locked by the caller. */
पूर्णांक landlock_insert_rule(काष्ठा landlock_ruleset *स्थिर ruleset,
		काष्ठा landlock_object *स्थिर object, स्थिर u32 access)
अणु
	काष्ठा landlock_layer layers[] = अणुअणु
		.access = access,
		/* When @level is zero, insert_rule() extends @ruleset. */
		.level = 0,
	पूर्णपूर्ण;

	build_check_layer();
	वापस insert_rule(ruleset, object, &layers, ARRAY_SIZE(layers));
पूर्ण

अटल अंतरभूत व्योम get_hierarchy(काष्ठा landlock_hierarchy *स्थिर hierarchy)
अणु
	अगर (hierarchy)
		refcount_inc(&hierarchy->usage);
पूर्ण

अटल व्योम put_hierarchy(काष्ठा landlock_hierarchy *hierarchy)
अणु
	जबतक (hierarchy && refcount_dec_and_test(&hierarchy->usage)) अणु
		स्थिर काष्ठा landlock_hierarchy *स्थिर मुक्तme = hierarchy;

		hierarchy = hierarchy->parent;
		kमुक्त(मुक्तme);
	पूर्ण
पूर्ण

अटल पूर्णांक merge_ruleset(काष्ठा landlock_ruleset *स्थिर dst,
		काष्ठा landlock_ruleset *स्थिर src)
अणु
	काष्ठा landlock_rule *walker_rule, *next_rule;
	पूर्णांक err = 0;

	might_sleep();
	/* Should alपढ़ोy be checked by landlock_merge_ruleset() */
	अगर (WARN_ON_ONCE(!src))
		वापस 0;
	/* Only merge पूर्णांकo a करोमुख्य. */
	अगर (WARN_ON_ONCE(!dst || !dst->hierarchy))
		वापस -EINVAL;

	/* Locks @dst first because we are its only owner. */
	mutex_lock(&dst->lock);
	mutex_lock_nested(&src->lock, SINGLE_DEPTH_NESTING);

	/* Stacks the new layer. */
	अगर (WARN_ON_ONCE(src->num_layers != 1 || dst->num_layers < 1)) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	dst->fs_access_masks[dst->num_layers - 1] = src->fs_access_masks[0];

	/* Merges the @src tree. */
	rbtree_postorder_क्रम_each_entry_safe(walker_rule, next_rule,
			&src->root, node) अणु
		काष्ठा landlock_layer layers[] = अणुअणु
			.level = dst->num_layers,
		पूर्णपूर्ण;

		अगर (WARN_ON_ONCE(walker_rule->num_layers != 1)) अणु
			err = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		अगर (WARN_ON_ONCE(walker_rule->layers[0].level != 0)) अणु
			err = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		layers[0].access = walker_rule->layers[0].access;
		err = insert_rule(dst, walker_rule->object, &layers,
				ARRAY_SIZE(layers));
		अगर (err)
			जाओ out_unlock;
	पूर्ण

out_unlock:
	mutex_unlock(&src->lock);
	mutex_unlock(&dst->lock);
	वापस err;
पूर्ण

अटल पूर्णांक inherit_ruleset(काष्ठा landlock_ruleset *स्थिर parent,
		काष्ठा landlock_ruleset *स्थिर child)
अणु
	काष्ठा landlock_rule *walker_rule, *next_rule;
	पूर्णांक err = 0;

	might_sleep();
	अगर (!parent)
		वापस 0;

	/* Locks @child first because we are its only owner. */
	mutex_lock(&child->lock);
	mutex_lock_nested(&parent->lock, SINGLE_DEPTH_NESTING);

	/* Copies the @parent tree. */
	rbtree_postorder_क्रम_each_entry_safe(walker_rule, next_rule,
			&parent->root, node) अणु
		err = insert_rule(child, walker_rule->object,
				&walker_rule->layers, walker_rule->num_layers);
		अगर (err)
			जाओ out_unlock;
	पूर्ण

	अगर (WARN_ON_ONCE(child->num_layers <= parent->num_layers)) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	/* Copies the parent layer stack and leaves a space क्रम the new layer. */
	स_नकल(child->fs_access_masks, parent->fs_access_masks,
			flex_array_size(parent, fs_access_masks, parent->num_layers));

	अगर (WARN_ON_ONCE(!parent->hierarchy)) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	get_hierarchy(parent->hierarchy);
	child->hierarchy->parent = parent->hierarchy;

out_unlock:
	mutex_unlock(&parent->lock);
	mutex_unlock(&child->lock);
	वापस err;
पूर्ण

अटल व्योम मुक्त_ruleset(काष्ठा landlock_ruleset *स्थिर ruleset)
अणु
	काष्ठा landlock_rule *मुक्तme, *next;

	might_sleep();
	rbtree_postorder_क्रम_each_entry_safe(मुक्तme, next, &ruleset->root,
			node)
		मुक्त_rule(मुक्तme);
	put_hierarchy(ruleset->hierarchy);
	kमुक्त(ruleset);
पूर्ण

व्योम landlock_put_ruleset(काष्ठा landlock_ruleset *स्थिर ruleset)
अणु
	might_sleep();
	अगर (ruleset && refcount_dec_and_test(&ruleset->usage))
		मुक्त_ruleset(ruleset);
पूर्ण

अटल व्योम मुक्त_ruleset_work(काष्ठा work_काष्ठा *स्थिर work)
अणु
	काष्ठा landlock_ruleset *ruleset;

	ruleset = container_of(work, काष्ठा landlock_ruleset, work_मुक्त);
	मुक्त_ruleset(ruleset);
पूर्ण

व्योम landlock_put_ruleset_deferred(काष्ठा landlock_ruleset *स्थिर ruleset)
अणु
	अगर (ruleset && refcount_dec_and_test(&ruleset->usage)) अणु
		INIT_WORK(&ruleset->work_मुक्त, मुक्त_ruleset_work);
		schedule_work(&ruleset->work_मुक्त);
	पूर्ण
पूर्ण

/**
 * landlock_merge_ruleset - Merge a ruleset with a करोमुख्य
 *
 * @parent: Parent करोमुख्य.
 * @ruleset: New ruleset to be merged.
 *
 * Returns the पूर्णांकersection of @parent and @ruleset, or वापसs @parent अगर
 * @ruleset is empty, or वापसs a duplicate of @ruleset अगर @parent is empty.
 */
काष्ठा landlock_ruleset *landlock_merge_ruleset(
		काष्ठा landlock_ruleset *स्थिर parent,
		काष्ठा landlock_ruleset *स्थिर ruleset)
अणु
	काष्ठा landlock_ruleset *new_करोm;
	u32 num_layers;
	पूर्णांक err;

	might_sleep();
	अगर (WARN_ON_ONCE(!ruleset || parent == ruleset))
		वापस ERR_PTR(-EINVAL);

	अगर (parent) अणु
		अगर (parent->num_layers >= LANDLOCK_MAX_NUM_LAYERS)
			वापस ERR_PTR(-E2BIG);
		num_layers = parent->num_layers + 1;
	पूर्ण अन्यथा अणु
		num_layers = 1;
	पूर्ण

	/* Creates a new करोमुख्य... */
	new_करोm = create_ruleset(num_layers);
	अगर (IS_ERR(new_करोm))
		वापस new_करोm;
	new_करोm->hierarchy = kzalloc(माप(*new_करोm->hierarchy),
			GFP_KERNEL_ACCOUNT);
	अगर (!new_करोm->hierarchy) अणु
		err = -ENOMEM;
		जाओ out_put_करोm;
	पूर्ण
	refcount_set(&new_करोm->hierarchy->usage, 1);

	/* ...as a child of @parent... */
	err = inherit_ruleset(parent, new_करोm);
	अगर (err)
		जाओ out_put_करोm;

	/* ...and including @ruleset. */
	err = merge_ruleset(new_करोm, ruleset);
	अगर (err)
		जाओ out_put_करोm;

	वापस new_करोm;

out_put_करोm:
	landlock_put_ruleset(new_करोm);
	वापस ERR_PTR(err);
पूर्ण

/*
 * The वापसed access has the same lअगरeसमय as @ruleset.
 */
स्थिर काष्ठा landlock_rule *landlock_find_rule(
		स्थिर काष्ठा landlock_ruleset *स्थिर ruleset,
		स्थिर काष्ठा landlock_object *स्थिर object)
अणु
	स्थिर काष्ठा rb_node *node;

	अगर (!object)
		वापस शून्य;
	node = ruleset->root.rb_node;
	जबतक (node) अणु
		काष्ठा landlock_rule *this = rb_entry(node,
				काष्ठा landlock_rule, node);

		अगर (this->object == object)
			वापस this;
		अगर (this->object < object)
			node = node->rb_right;
		अन्यथा
			node = node->rb_left;
	पूर्ण
	वापस शून्य;
पूर्ण
