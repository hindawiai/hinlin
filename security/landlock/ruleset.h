<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Landlock LSM - Ruleset management
 *
 * Copyright तऊ 2016-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#अगर_अघोषित _SECURITY_LANDLOCK_RULESET_H
#घोषणा _SECURITY_LANDLOCK_RULESET_H

#समावेश <linux/mutex.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/refcount.h>
#समावेश <linux/workqueue.h>

#समावेश "object.h"

/**
 * काष्ठा landlock_layer - Access rights क्रम a given layer
 */
काष्ठा landlock_layer अणु
	/**
	 * @level: Position of this layer in the layer stack.
	 */
	u16 level;
	/**
	 * @access: Bitfield of allowed actions on the kernel object.  They are
	 * relative to the object type (e.g. %LANDLOCK_ACTION_FS_READ).
	 */
	u16 access;
पूर्ण;

/**
 * काष्ठा landlock_rule - Access rights tied to an object
 */
काष्ठा landlock_rule अणु
	/**
	 * @node: Node in the ruleset's red-black tree.
	 */
	काष्ठा rb_node node;
	/**
	 * @object: Poपूर्णांकer to identअगरy a kernel object (e.g. an inode).  This
	 * is used as a key क्रम this ruleset element.  This poपूर्णांकer is set once
	 * and never modअगरied.  It always poपूर्णांकs to an allocated object because
	 * each rule increments the refcount of its object.
	 */
	काष्ठा landlock_object *object;
	/**
	 * @num_layers: Number of entries in @layers.
	 */
	u32 num_layers;
	/**
	 * @layers: Stack of layers, from the latest to the newest, implemented
	 * as a flexible array member (FAM).
	 */
	काष्ठा landlock_layer layers[];
पूर्ण;

/**
 * काष्ठा landlock_hierarchy - Node in a ruleset hierarchy
 */
काष्ठा landlock_hierarchy अणु
	/**
	 * @parent: Poपूर्णांकer to the parent node, or शून्य अगर it is a root
	 * Landlock करोमुख्य.
	 */
	काष्ठा landlock_hierarchy *parent;
	/**
	 * @usage: Number of potential children करोमुख्यs plus their parent
	 * करोमुख्य.
	 */
	refcount_t usage;
पूर्ण;

/**
 * काष्ठा landlock_ruleset - Landlock ruleset
 *
 * This data काष्ठाure must contain unique entries, be updatable, and quick to
 * match an object.
 */
काष्ठा landlock_ruleset अणु
	/**
	 * @root: Root of a red-black tree containing &काष्ठा landlock_rule
	 * nodes.  Once a ruleset is tied to a process (i.e. as a करोमुख्य), this
	 * tree is immutable until @usage reaches zero.
	 */
	काष्ठा rb_root root;
	/**
	 * @hierarchy: Enables hierarchy identअगरication even when a parent
	 * करोमुख्य vanishes.  This is needed क्रम the ptrace protection.
	 */
	काष्ठा landlock_hierarchy *hierarchy;
	जोड़ अणु
		/**
		 * @work_मुक्त: Enables to मुक्त a ruleset within a lockless
		 * section.  This is only used by
		 * landlock_put_ruleset_deferred() when @usage reaches zero.
		 * The fields @lock, @usage, @num_rules, @num_layers and
		 * @fs_access_masks are then unused.
		 */
		काष्ठा work_काष्ठा work_मुक्त;
		काष्ठा अणु
			/**
			 * @lock: Protects against concurrent modअगरications of
			 * @root, अगर @usage is greater than zero.
			 */
			काष्ठा mutex lock;
			/**
			 * @usage: Number of processes (i.e. करोमुख्यs) or file
			 * descriptors referencing this ruleset.
			 */
			refcount_t usage;
			/**
			 * @num_rules: Number of non-overlapping (i.e. not क्रम
			 * the same object) rules in this ruleset.
			 */
			u32 num_rules;
			/**
			 * @num_layers: Number of layers that are used in this
			 * ruleset.  This enables to check that all the layers
			 * allow an access request.  A value of 0 identअगरies a
			 * non-merged ruleset (i.e. not a करोमुख्य).
			 */
			u32 num_layers;
			/**
			 * @fs_access_masks: Contains the subset of fileप्रणाली
			 * actions that are restricted by a ruleset.  A करोमुख्य
			 * saves all layers of merged rulesets in a stack
			 * (FAM), starting from the first layer to the last
			 * one.  These layers are used when merging rulesets,
			 * क्रम user space backward compatibility (i.e.
			 * future-proof), and to properly handle merged
			 * rulesets without overlapping access rights.  These
			 * layers are set once and never changed क्रम the
			 * lअगरeसमय of the ruleset.
			 */
			u16 fs_access_masks[];
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा landlock_ruleset *landlock_create_ruleset(स्थिर u32 fs_access_mask);

व्योम landlock_put_ruleset(काष्ठा landlock_ruleset *स्थिर ruleset);
व्योम landlock_put_ruleset_deferred(काष्ठा landlock_ruleset *स्थिर ruleset);

पूर्णांक landlock_insert_rule(काष्ठा landlock_ruleset *स्थिर ruleset,
		काष्ठा landlock_object *स्थिर object, स्थिर u32 access);

काष्ठा landlock_ruleset *landlock_merge_ruleset(
		काष्ठा landlock_ruleset *स्थिर parent,
		काष्ठा landlock_ruleset *स्थिर ruleset);

स्थिर काष्ठा landlock_rule *landlock_find_rule(
		स्थिर काष्ठा landlock_ruleset *स्थिर ruleset,
		स्थिर काष्ठा landlock_object *स्थिर object);

अटल अंतरभूत व्योम landlock_get_ruleset(काष्ठा landlock_ruleset *स्थिर ruleset)
अणु
	अगर (ruleset)
		refcount_inc(&ruleset->usage);
पूर्ण

#पूर्ण_अगर /* _SECURITY_LANDLOCK_RULESET_H */
