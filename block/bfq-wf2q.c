<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hierarchical Budget Worst-हाल Fair Weighted Fair Queueing
 * (B-WF2Q+): hierarchical scheduling algorithm by which the BFQ I/O
 * scheduler schedules generic entities. The latter can represent
 * either single bfq queues (associated with processes) or groups of
 * bfq queues (associated with cgroups).
 */
#समावेश "bfq-iosched.h"

/**
 * bfq_gt - compare two बारtamps.
 * @a: first ts.
 * @b: second ts.
 *
 * Return @a > @b, dealing with wrapping correctly.
 */
अटल पूर्णांक bfq_gt(u64 a, u64 b)
अणु
	वापस (s64)(a - b) > 0;
पूर्ण

अटल काष्ठा bfq_entity *bfq_root_active_entity(काष्ठा rb_root *tree)
अणु
	काष्ठा rb_node *node = tree->rb_node;

	वापस rb_entry(node, काष्ठा bfq_entity, rb_node);
पूर्ण

अटल अचिन्हित पूर्णांक bfq_class_idx(काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	वापस bfqq ? bfqq->ioprio_class - 1 :
		BFQ_DEFAULT_GRP_CLASS - 1;
पूर्ण

अचिन्हित पूर्णांक bfq_tot_busy_queues(काष्ठा bfq_data *bfqd)
अणु
	वापस bfqd->busy_queues[0] + bfqd->busy_queues[1] +
		bfqd->busy_queues[2];
पूर्ण

अटल काष्ठा bfq_entity *bfq_lookup_next_entity(काष्ठा bfq_sched_data *sd,
						 bool expiration);

अटल bool bfq_update_parent_budget(काष्ठा bfq_entity *next_in_service);

/**
 * bfq_update_next_in_service - update sd->next_in_service
 * @sd: sched_data क्रम which to perक्रमm the update.
 * @new_entity: अगर not शून्य, poपूर्णांकer to the entity whose activation,
 *		requeueing or repositioning triggered the invocation of
 *		this function.
 * @expiration: id true, this function is being invoked after the
 *             expiration of the in-service entity
 *
 * This function is called to update sd->next_in_service, which, in
 * its turn, may change as a consequence of the insertion or
 * extraction of an entity पूर्णांकo/from one of the active trees of
 * sd. These insertions/extractions occur as a consequence of
 * activations/deactivations of entities, with some activations being
 * 'true' activations, and other activations being requeueings (i.e.,
 * implementing the second, requeueing phase of the mechanism used to
 * reposition an entity in its active tree; see comments on
 * __bfq_activate_entity and __bfq_requeue_entity क्रम details). In
 * both the last two activation sub-हालs, new_entity poपूर्णांकs to the
 * just activated or requeued entity.
 *
 * Returns true अगर sd->next_in_service changes in such a way that
 * entity->parent may become the next_in_service क्रम its parent
 * entity.
 */
अटल bool bfq_update_next_in_service(काष्ठा bfq_sched_data *sd,
				       काष्ठा bfq_entity *new_entity,
				       bool expiration)
अणु
	काष्ठा bfq_entity *next_in_service = sd->next_in_service;
	bool parent_sched_may_change = false;
	bool change_without_lookup = false;

	/*
	 * If this update is triggered by the activation, requeueing
	 * or repositioning of an entity that करोes not coincide with
	 * sd->next_in_service, then a full lookup in the active tree
	 * can be aव्योमed. In fact, it is enough to check whether the
	 * just-modअगरied entity has the same priority as
	 * sd->next_in_service, is eligible and has a lower भव
	 * finish समय than sd->next_in_service. If this compound
	 * condition holds, then the new entity becomes the new
	 * next_in_service. Otherwise no change is needed.
	 */
	अगर (new_entity && new_entity != sd->next_in_service) अणु
		/*
		 * Flag used to decide whether to replace
		 * sd->next_in_service with new_entity. Tentatively
		 * set to true, and left as true अगर
		 * sd->next_in_service is शून्य.
		 */
		change_without_lookup = true;

		/*
		 * If there is alपढ़ोy a next_in_service candidate
		 * entity, then compare बारtamps to decide whether
		 * to replace sd->service_tree with new_entity.
		 */
		अगर (next_in_service) अणु
			अचिन्हित पूर्णांक new_entity_class_idx =
				bfq_class_idx(new_entity);
			काष्ठा bfq_service_tree *st =
				sd->service_tree + new_entity_class_idx;

			change_without_lookup =
				(new_entity_class_idx ==
				 bfq_class_idx(next_in_service)
				 &&
				 !bfq_gt(new_entity->start, st->vसमय)
				 &&
				 bfq_gt(next_in_service->finish,
					new_entity->finish));
		पूर्ण

		अगर (change_without_lookup)
			next_in_service = new_entity;
	पूर्ण

	अगर (!change_without_lookup) /* lookup needed */
		next_in_service = bfq_lookup_next_entity(sd, expiration);

	अगर (next_in_service) अणु
		bool new_budget_triggers_change =
			bfq_update_parent_budget(next_in_service);

		parent_sched_may_change = !sd->next_in_service ||
			new_budget_triggers_change;
	पूर्ण

	sd->next_in_service = next_in_service;

	वापस parent_sched_may_change;
पूर्ण

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED

काष्ठा bfq_group *bfq_bfqq_to_bfqg(काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_entity *group_entity = bfqq->entity.parent;

	अगर (!group_entity)
		group_entity = &bfqq->bfqd->root_group->entity;

	वापस container_of(group_entity, काष्ठा bfq_group, entity);
पूर्ण

/*
 * Returns true अगर this budget changes may let next_in_service->parent
 * become the next_in_service entity क्रम its parent entity.
 */
अटल bool bfq_update_parent_budget(काष्ठा bfq_entity *next_in_service)
अणु
	काष्ठा bfq_entity *bfqg_entity;
	काष्ठा bfq_group *bfqg;
	काष्ठा bfq_sched_data *group_sd;
	bool ret = false;

	group_sd = next_in_service->sched_data;

	bfqg = container_of(group_sd, काष्ठा bfq_group, sched_data);
	/*
	 * bfq_group's my_entity field is not शून्य only अगर the group
	 * is not the root group. We must not touch the root entity
	 * as it must never become an in-service entity.
	 */
	bfqg_entity = bfqg->my_entity;
	अगर (bfqg_entity) अणु
		अगर (bfqg_entity->budget > next_in_service->budget)
			ret = true;
		bfqg_entity->budget = next_in_service->budget;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function tells whether entity stops being a candidate क्रम next
 * service, according to the restrictive definition of the field
 * next_in_service. In particular, this function is invoked क्रम an
 * entity that is about to be set in service.
 *
 * If entity is a queue, then the entity is no दीर्घer a candidate क्रम
 * next service according to the that definition, because entity is
 * about to become the in-service queue. This function then वापसs
 * true अगर entity is a queue.
 *
 * In contrast, entity could still be a candidate क्रम next service अगर
 * it is not a queue, and has more than one active child. In fact,
 * even अगर one of its children is about to be set in service, other
 * active children may still be the next to serve, क्रम the parent
 * entity, even according to the above definition. As a consequence, a
 * non-queue entity is not a candidate क्रम next-service only अगर it has
 * only one active child. And only अगर this condition holds, then this
 * function वापसs true क्रम a non-queue entity.
 */
अटल bool bfq_no_दीर्घer_next_in_service(काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_group *bfqg;

	अगर (bfq_entity_to_bfqq(entity))
		वापस true;

	bfqg = container_of(entity, काष्ठा bfq_group, entity);

	/*
	 * The field active_entities करोes not always contain the
	 * actual number of active children entities: it happens to
	 * not account क्रम the in-service entity in हाल the latter is
	 * हटाओd from its active tree (which may get करोne after
	 * invoking the function bfq_no_दीर्घer_next_in_service in
	 * bfq_get_next_queue). Fortunately, here, i.e., जबतक
	 * bfq_no_दीर्घer_next_in_service is not yet completed in
	 * bfq_get_next_queue, bfq_active_extract has not yet been
	 * invoked, and thus active_entities still coincides with the
	 * actual number of active entities.
	 */
	अगर (bfqg->active_entities == 1)
		वापस true;

	वापस false;
पूर्ण

#अन्यथा /* CONFIG_BFQ_GROUP_IOSCHED */

काष्ठा bfq_group *bfq_bfqq_to_bfqg(काष्ठा bfq_queue *bfqq)
अणु
	वापस bfqq->bfqd->root_group;
पूर्ण

अटल bool bfq_update_parent_budget(काष्ठा bfq_entity *next_in_service)
अणु
	वापस false;
पूर्ण

अटल bool bfq_no_दीर्घer_next_in_service(काष्ठा bfq_entity *entity)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* CONFIG_BFQ_GROUP_IOSCHED */

/*
 * Shअगरt क्रम बारtamp calculations.  This actually limits the maximum
 * service allowed in one बारtamp delta (small shअगरt values increase it),
 * the maximum total weight that can be used क्रम the queues in the प्रणाली
 * (big shअगरt values increase it), and the period of भव समय
 * wraparounds.
 */
#घोषणा WFQ_SERVICE_SHIFT	22

काष्ठा bfq_queue *bfq_entity_to_bfqq(काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_queue *bfqq = शून्य;

	अगर (!entity->my_sched_data)
		bfqq = container_of(entity, काष्ठा bfq_queue, entity);

	वापस bfqq;
पूर्ण


/**
 * bfq_delta - map service पूर्णांकo the भव समय करोमुख्य.
 * @service: amount of service.
 * @weight: scale factor (weight of an entity or weight sum).
 */
अटल u64 bfq_delta(अचिन्हित दीर्घ service, अचिन्हित दीर्घ weight)
अणु
	वापस भाग64_ul((u64)service << WFQ_SERVICE_SHIFT, weight);
पूर्ण

/**
 * bfq_calc_finish - assign the finish समय to an entity.
 * @entity: the entity to act upon.
 * @service: the service to be अक्षरged to the entity.
 */
अटल व्योम bfq_calc_finish(काष्ठा bfq_entity *entity, अचिन्हित दीर्घ service)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->finish = entity->start +
		bfq_delta(service, entity->weight);

	अगर (bfqq) अणु
		bfq_log_bfqq(bfqq->bfqd, bfqq,
			"calc_finish: serv %lu, w %d",
			service, entity->weight);
		bfq_log_bfqq(bfqq->bfqd, bfqq,
			"calc_finish: start %llu, finish %llu, delta %llu",
			entity->start, entity->finish,
			bfq_delta(service, entity->weight));
	पूर्ण
पूर्ण

/**
 * bfq_entity_of - get an entity from a node.
 * @node: the node field of the entity.
 *
 * Convert a node poपूर्णांकer to the relative entity.  This is used only
 * to simplअगरy the logic of some functions and not as the generic
 * conversion mechanism because, e.g., in the tree walking functions,
 * the check क्रम a %शून्य value would be redundant.
 */
काष्ठा bfq_entity *bfq_entity_of(काष्ठा rb_node *node)
अणु
	काष्ठा bfq_entity *entity = शून्य;

	अगर (node)
		entity = rb_entry(node, काष्ठा bfq_entity, rb_node);

	वापस entity;
पूर्ण

/**
 * bfq_extract - हटाओ an entity from a tree.
 * @root: the tree root.
 * @entity: the entity to हटाओ.
 */
अटल व्योम bfq_extract(काष्ठा rb_root *root, काष्ठा bfq_entity *entity)
अणु
	entity->tree = शून्य;
	rb_erase(&entity->rb_node, root);
पूर्ण

/**
 * bfq_idle_extract - extract an entity from the idle tree.
 * @st: the service tree of the owning @entity.
 * @entity: the entity being हटाओd.
 */
अटल व्योम bfq_idle_extract(काष्ठा bfq_service_tree *st,
			     काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	काष्ठा rb_node *next;

	अगर (entity == st->first_idle) अणु
		next = rb_next(&entity->rb_node);
		st->first_idle = bfq_entity_of(next);
	पूर्ण

	अगर (entity == st->last_idle) अणु
		next = rb_prev(&entity->rb_node);
		st->last_idle = bfq_entity_of(next);
	पूर्ण

	bfq_extract(&st->idle, entity);

	अगर (bfqq)
		list_del(&bfqq->bfqq_list);
पूर्ण

/**
 * bfq_insert - generic tree insertion.
 * @root: tree root.
 * @entity: entity to insert.
 *
 * This is used क्रम the idle and the active tree, since they are both
 * ordered by finish समय.
 */
अटल व्योम bfq_insert(काष्ठा rb_root *root, काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_entity *entry;
	काष्ठा rb_node **node = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;

	जबतक (*node) अणु
		parent = *node;
		entry = rb_entry(parent, काष्ठा bfq_entity, rb_node);

		अगर (bfq_gt(entry->finish, entity->finish))
			node = &parent->rb_left;
		अन्यथा
			node = &parent->rb_right;
	पूर्ण

	rb_link_node(&entity->rb_node, parent, node);
	rb_insert_color(&entity->rb_node, root);

	entity->tree = root;
पूर्ण

/**
 * bfq_update_min - update the min_start field of a entity.
 * @entity: the entity to update.
 * @node: one of its children.
 *
 * This function is called when @entity may store an invalid value क्रम
 * min_start due to updates to the active tree.  The function  assumes
 * that the subtree rooted at @node (which may be its left or its right
 * child) has a valid min_start value.
 */
अटल व्योम bfq_update_min(काष्ठा bfq_entity *entity, काष्ठा rb_node *node)
अणु
	काष्ठा bfq_entity *child;

	अगर (node) अणु
		child = rb_entry(node, काष्ठा bfq_entity, rb_node);
		अगर (bfq_gt(entity->min_start, child->min_start))
			entity->min_start = child->min_start;
	पूर्ण
पूर्ण

/**
 * bfq_update_active_node - recalculate min_start.
 * @node: the node to update.
 *
 * @node may have changed position or one of its children may have moved,
 * this function updates its min_start value.  The left and right subtrees
 * are assumed to hold a correct min_start value.
 */
अटल व्योम bfq_update_active_node(काष्ठा rb_node *node)
अणु
	काष्ठा bfq_entity *entity = rb_entry(node, काष्ठा bfq_entity, rb_node);

	entity->min_start = entity->start;
	bfq_update_min(entity, node->rb_right);
	bfq_update_min(entity, node->rb_left);
पूर्ण

/**
 * bfq_update_active_tree - update min_start क्रम the whole active tree.
 * @node: the starting node.
 *
 * @node must be the deepest modअगरied node after an update.  This function
 * updates its min_start using the values held by its children, assuming
 * that they did not change, and then updates all the nodes that may have
 * changed in the path to the root.  The only nodes that may have changed
 * are the ones in the path or their siblings.
 */
अटल व्योम bfq_update_active_tree(काष्ठा rb_node *node)
अणु
	काष्ठा rb_node *parent;

up:
	bfq_update_active_node(node);

	parent = rb_parent(node);
	अगर (!parent)
		वापस;

	अगर (node == parent->rb_left && parent->rb_right)
		bfq_update_active_node(parent->rb_right);
	अन्यथा अगर (parent->rb_left)
		bfq_update_active_node(parent->rb_left);

	node = parent;
	जाओ up;
पूर्ण

/**
 * bfq_active_insert - insert an entity in the active tree of its
 *                     group/device.
 * @st: the service tree of the entity.
 * @entity: the entity being inserted.
 *
 * The active tree is ordered by finish समय, but an extra key is kept
 * per each node, containing the minimum value क्रम the start बार of
 * its children (and the node itself), so it's possible to search क्रम
 * the eligible node with the lowest finish समय in logarithmic समय.
 */
अटल व्योम bfq_active_insert(काष्ठा bfq_service_tree *st,
			      काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	काष्ठा rb_node *node = &entity->rb_node;
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	काष्ठा bfq_sched_data *sd = शून्य;
	काष्ठा bfq_group *bfqg = शून्य;
	काष्ठा bfq_data *bfqd = शून्य;
#पूर्ण_अगर

	bfq_insert(&st->active, entity);

	अगर (node->rb_left)
		node = node->rb_left;
	अन्यथा अगर (node->rb_right)
		node = node->rb_right;

	bfq_update_active_tree(node);

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	sd = entity->sched_data;
	bfqg = container_of(sd, काष्ठा bfq_group, sched_data);
	bfqd = (काष्ठा bfq_data *)bfqg->bfqd;
#पूर्ण_अगर
	अगर (bfqq)
		list_add(&bfqq->bfqq_list, &bfqq->bfqd->active_list);
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	अगर (bfqg != bfqd->root_group)
		bfqg->active_entities++;
#पूर्ण_अगर
पूर्ण

/**
 * bfq_ioprio_to_weight - calc a weight from an ioprio.
 * @ioprio: the ioprio value to convert.
 */
अचिन्हित लघु bfq_ioprio_to_weight(पूर्णांक ioprio)
अणु
	वापस (IOPRIO_BE_NR - ioprio) * BFQ_WEIGHT_CONVERSION_COEFF;
पूर्ण

/**
 * bfq_weight_to_ioprio - calc an ioprio from a weight.
 * @weight: the weight value to convert.
 *
 * To preserve as much as possible the old only-ioprio user पूर्णांकerface,
 * 0 is used as an escape ioprio value क्रम weights (numerically) equal or
 * larger than IOPRIO_BE_NR * BFQ_WEIGHT_CONVERSION_COEFF.
 */
अटल अचिन्हित लघु bfq_weight_to_ioprio(पूर्णांक weight)
अणु
	वापस max_t(पूर्णांक, 0,
		     IOPRIO_BE_NR * BFQ_WEIGHT_CONVERSION_COEFF - weight);
पूर्ण

अटल व्योम bfq_get_entity(काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	अगर (bfqq) अणु
		bfqq->ref++;
		bfq_log_bfqq(bfqq->bfqd, bfqq, "get_entity: %p %d",
			     bfqq, bfqq->ref);
	पूर्ण
पूर्ण

/**
 * bfq_find_deepest - find the deepest node that an extraction can modअगरy.
 * @node: the node being हटाओd.
 *
 * Do the first step of an extraction in an rb tree, looking क्रम the
 * node that will replace @node, and वापसing the deepest node that
 * the following modअगरications to the tree can touch.  If @node is the
 * last node in the tree वापस %शून्य.
 */
अटल काष्ठा rb_node *bfq_find_deepest(काष्ठा rb_node *node)
अणु
	काष्ठा rb_node *deepest;

	अगर (!node->rb_right && !node->rb_left)
		deepest = rb_parent(node);
	अन्यथा अगर (!node->rb_right)
		deepest = node->rb_left;
	अन्यथा अगर (!node->rb_left)
		deepest = node->rb_right;
	अन्यथा अणु
		deepest = rb_next(node);
		अगर (deepest->rb_right)
			deepest = deepest->rb_right;
		अन्यथा अगर (rb_parent(deepest) != node)
			deepest = rb_parent(deepest);
	पूर्ण

	वापस deepest;
पूर्ण

/**
 * bfq_active_extract - हटाओ an entity from the active tree.
 * @st: the service_tree containing the tree.
 * @entity: the entity being हटाओd.
 */
अटल व्योम bfq_active_extract(काष्ठा bfq_service_tree *st,
			       काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	काष्ठा rb_node *node;
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	काष्ठा bfq_sched_data *sd = शून्य;
	काष्ठा bfq_group *bfqg = शून्य;
	काष्ठा bfq_data *bfqd = शून्य;
#पूर्ण_अगर

	node = bfq_find_deepest(&entity->rb_node);
	bfq_extract(&st->active, entity);

	अगर (node)
		bfq_update_active_tree(node);

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	sd = entity->sched_data;
	bfqg = container_of(sd, काष्ठा bfq_group, sched_data);
	bfqd = (काष्ठा bfq_data *)bfqg->bfqd;
#पूर्ण_अगर
	अगर (bfqq)
		list_del(&bfqq->bfqq_list);
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	अगर (bfqg != bfqd->root_group)
		bfqg->active_entities--;
#पूर्ण_अगर
पूर्ण

/**
 * bfq_idle_insert - insert an entity पूर्णांकo the idle tree.
 * @st: the service tree containing the tree.
 * @entity: the entity to insert.
 */
अटल व्योम bfq_idle_insert(काष्ठा bfq_service_tree *st,
			    काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	काष्ठा bfq_entity *first_idle = st->first_idle;
	काष्ठा bfq_entity *last_idle = st->last_idle;

	अगर (!first_idle || bfq_gt(first_idle->finish, entity->finish))
		st->first_idle = entity;
	अगर (!last_idle || bfq_gt(entity->finish, last_idle->finish))
		st->last_idle = entity;

	bfq_insert(&st->idle, entity);

	अगर (bfqq)
		list_add(&bfqq->bfqq_list, &bfqq->bfqd->idle_list);
पूर्ण

/**
 * bfq_क्रमget_entity - करो not consider entity any दीर्घer क्रम scheduling
 * @st: the service tree.
 * @entity: the entity being हटाओd.
 * @is_in_service: true अगर entity is currently the in-service entity.
 *
 * Forget everything about @entity. In addition, अगर entity represents
 * a queue, and the latter is not in service, then release the service
 * reference to the queue (the one taken through bfq_get_entity). In
 * fact, in this हाल, there is really no more service reference to
 * the queue, as the latter is also outside any service tree. If,
 * instead, the queue is in service, then __bfq_bfqd_reset_in_service
 * will take care of putting the reference when the queue finally
 * stops being served.
 */
अटल व्योम bfq_क्रमget_entity(काष्ठा bfq_service_tree *st,
			      काष्ठा bfq_entity *entity,
			      bool is_in_service)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->on_st_or_in_serv = false;
	st->wsum -= entity->weight;
	अगर (bfqq && !is_in_service)
		bfq_put_queue(bfqq);
पूर्ण

/**
 * bfq_put_idle_entity - release the idle tree ref of an entity.
 * @st: service tree क्रम the entity.
 * @entity: the entity being released.
 */
व्योम bfq_put_idle_entity(काष्ठा bfq_service_tree *st, काष्ठा bfq_entity *entity)
अणु
	bfq_idle_extract(st, entity);
	bfq_क्रमget_entity(st, entity,
			  entity == entity->sched_data->in_service_entity);
पूर्ण

/**
 * bfq_क्रमget_idle - update the idle tree अगर necessary.
 * @st: the service tree to act upon.
 *
 * To preserve the global O(log N) complनिकासy we only हटाओ one entry here;
 * as the idle tree will not grow indefinitely this can be करोne safely.
 */
अटल व्योम bfq_क्रमget_idle(काष्ठा bfq_service_tree *st)
अणु
	काष्ठा bfq_entity *first_idle = st->first_idle;
	काष्ठा bfq_entity *last_idle = st->last_idle;

	अगर (RB_EMPTY_ROOT(&st->active) && last_idle &&
	    !bfq_gt(last_idle->finish, st->vसमय)) अणु
		/*
		 * Forget the whole idle tree, increasing the vसमय past
		 * the last finish समय of idle entities.
		 */
		st->vसमय = last_idle->finish;
	पूर्ण

	अगर (first_idle && !bfq_gt(first_idle->finish, st->vसमय))
		bfq_put_idle_entity(st, first_idle);
पूर्ण

काष्ठा bfq_service_tree *bfq_entity_service_tree(काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_sched_data *sched_data = entity->sched_data;
	अचिन्हित पूर्णांक idx = bfq_class_idx(entity);

	वापस sched_data->service_tree + idx;
पूर्ण

/*
 * Update weight and priority of entity. If update_class_too is true,
 * then update the ioprio_class of entity too.
 *
 * The reason why the update of ioprio_class is controlled through the
 * last parameter is as follows. Changing the ioprio class of an
 * entity implies changing the destination service trees क्रम that
 * entity. If such a change occurred when the entity is alपढ़ोy on one
 * of the service trees क्रम its previous class, then the state of the
 * entity would become more complex: none of the new possible service
 * trees क्रम the entity, according to bfq_entity_service_tree(), would
 * match any of the possible service trees on which the entity
 * is. Complex operations involving these trees, such as entity
 * activations and deactivations, should take पूर्णांकo account this
 * additional complनिकासy.  To aव्योम this issue, this function is
 * invoked with update_class_too unset in the poपूर्णांकs in the code where
 * entity may happen to be on some tree.
 */
काष्ठा bfq_service_tree *
__bfq_entity_update_weight_prio(काष्ठा bfq_service_tree *old_st,
				काष्ठा bfq_entity *entity,
				bool update_class_too)
अणु
	काष्ठा bfq_service_tree *new_st = old_st;

	अगर (entity->prio_changed) अणु
		काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
		अचिन्हित पूर्णांक prev_weight, new_weight;
		काष्ठा bfq_data *bfqd = शून्य;
		काष्ठा rb_root_cached *root;
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
		काष्ठा bfq_sched_data *sd;
		काष्ठा bfq_group *bfqg;
#पूर्ण_अगर

		अगर (bfqq)
			bfqd = bfqq->bfqd;
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
		अन्यथा अणु
			sd = entity->my_sched_data;
			bfqg = container_of(sd, काष्ठा bfq_group, sched_data);
			bfqd = (काष्ठा bfq_data *)bfqg->bfqd;
		पूर्ण
#पूर्ण_अगर

		/* Matches the smp_wmb() in bfq_group_set_weight. */
		smp_rmb();
		old_st->wsum -= entity->weight;

		अगर (entity->new_weight != entity->orig_weight) अणु
			अगर (entity->new_weight < BFQ_MIN_WEIGHT ||
			    entity->new_weight > BFQ_MAX_WEIGHT) अणु
				pr_crit("update_weight_prio: new_weight %d\n",
					entity->new_weight);
				अगर (entity->new_weight < BFQ_MIN_WEIGHT)
					entity->new_weight = BFQ_MIN_WEIGHT;
				अन्यथा
					entity->new_weight = BFQ_MAX_WEIGHT;
			पूर्ण
			entity->orig_weight = entity->new_weight;
			अगर (bfqq)
				bfqq->ioprio =
				  bfq_weight_to_ioprio(entity->orig_weight);
		पूर्ण

		अगर (bfqq && update_class_too)
			bfqq->ioprio_class = bfqq->new_ioprio_class;

		/*
		 * Reset prio_changed only अगर the ioprio_class change
		 * is not pending any दीर्घer.
		 */
		अगर (!bfqq || bfqq->ioprio_class == bfqq->new_ioprio_class)
			entity->prio_changed = 0;

		/*
		 * NOTE: here we may be changing the weight too early,
		 * this will cause unfairness.  The correct approach
		 * would have required additional complनिकासy to defer
		 * weight changes to the proper समय instants (i.e.,
		 * when entity->finish <= old_st->vसमय).
		 */
		new_st = bfq_entity_service_tree(entity);

		prev_weight = entity->weight;
		new_weight = entity->orig_weight *
			     (bfqq ? bfqq->wr_coeff : 1);
		/*
		 * If the weight of the entity changes, and the entity is a
		 * queue, हटाओ the entity from its old weight counter (अगर
		 * there is a counter associated with the entity).
		 */
		अगर (prev_weight != new_weight && bfqq) अणु
			root = &bfqd->queue_weights_tree;
			__bfq_weights_tree_हटाओ(bfqd, bfqq, root);
		पूर्ण
		entity->weight = new_weight;
		/*
		 * Add the entity, अगर it is not a weight-उठाओd queue,
		 * to the counter associated with its new weight.
		 */
		अगर (prev_weight != new_weight && bfqq && bfqq->wr_coeff == 1) अणु
			/* If we get here, root has been initialized. */
			bfq_weights_tree_add(bfqd, bfqq, root);
		पूर्ण

		new_st->wsum += entity->weight;

		अगर (new_st != old_st)
			entity->start = new_st->vसमय;
	पूर्ण

	वापस new_st;
पूर्ण

/**
 * bfq_bfqq_served - update the scheduler status after selection क्रम
 *                   service.
 * @bfqq: the queue being served.
 * @served: bytes to transfer.
 *
 * NOTE: this can be optimized, as the बारtamps of upper level entities
 * are synchronized every समय a new bfqq is selected क्रम service.  By now,
 * we keep it to better check consistency.
 */
व्योम bfq_bfqq_served(काष्ठा bfq_queue *bfqq, पूर्णांक served)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;
	काष्ठा bfq_service_tree *st;

	अगर (!bfqq->service_from_backlogged)
		bfqq->first_IO_समय = jअगरfies;

	अगर (bfqq->wr_coeff > 1)
		bfqq->service_from_wr += served;

	bfqq->service_from_backlogged += served;
	क्रम_each_entity(entity) अणु
		st = bfq_entity_service_tree(entity);

		entity->service += served;

		st->vसमय += bfq_delta(served, st->wsum);
		bfq_क्रमget_idle(st);
	पूर्ण
	bfq_log_bfqq(bfqq->bfqd, bfqq, "bfqq_served %d secs", served);
पूर्ण

/**
 * bfq_bfqq_अक्षरge_समय - अक्षरge an amount of service equivalent to the length
 *			  of the समय पूर्णांकerval during which bfqq has been in
 *			  service.
 * @bfqd: the device
 * @bfqq: the queue that needs a service update.
 * @समय_ms: the amount of समय during which the queue has received service
 *
 * If a queue करोes not consume its budget fast enough, then providing
 * the queue with service fairness may impair throughput, more or less
 * severely. For this reason, queues that consume their budget slowly
 * are provided with समय fairness instead of service fairness. This
 * goal is achieved through the BFQ scheduling engine, even अगर such an
 * engine works in the service, and not in the समय करोमुख्य. The trick
 * is अक्षरging these queues with an inflated amount of service, equal
 * to the amount of service that they would have received during their
 * service slot अगर they had been fast, i.e., अगर their requests had
 * been dispatched at a rate equal to the estimated peak rate.
 *
 * It is worth noting that समय fairness can cause important
 * distortions in terms of bandwidth distribution, on devices with
 * पूर्णांकernal queueing. The reason is that I/O requests dispatched
 * during the service slot of a queue may be served after that service
 * slot is finished, and may have a total processing समय loosely
 * correlated with the duration of the service slot. This is
 * especially true क्रम लघु service slots.
 */
व्योम bfq_bfqq_अक्षरge_समय(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			  अचिन्हित दीर्घ समय_ms)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;
	अचिन्हित दीर्घ समयout_ms = jअगरfies_to_msecs(bfq_समयout);
	अचिन्हित दीर्घ bounded_समय_ms = min(समय_ms, समयout_ms);
	पूर्णांक serv_to_अक्षरge_क्रम_समय =
		(bfqd->bfq_max_budget * bounded_समय_ms) / समयout_ms;
	पूर्णांक tot_serv_to_अक्षरge = max(serv_to_अक्षरge_क्रम_समय, entity->service);

	/* Increase budget to aव्योम inconsistencies */
	अगर (tot_serv_to_अक्षरge > entity->budget)
		entity->budget = tot_serv_to_अक्षरge;

	bfq_bfqq_served(bfqq,
			max_t(पूर्णांक, 0, tot_serv_to_अक्षरge - entity->service));
पूर्ण

अटल व्योम bfq_update_fin_समय_enqueue(काष्ठा bfq_entity *entity,
					काष्ठा bfq_service_tree *st,
					bool backshअगरted)
अणु
	काष्ठा bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	/*
	 * When this function is invoked, entity is not in any service
	 * tree, then it is safe to invoke next function with the last
	 * parameter set (see the comments on the function).
	 */
	st = __bfq_entity_update_weight_prio(st, entity, true);
	bfq_calc_finish(entity, entity->budget);

	/*
	 * If some queues enjoy backshअगरting क्रम a जबतक, then their
	 * (भव) finish बारtamps may happen to become lower and
	 * lower than the प्रणाली भव समय.	In particular, अगर
	 * these queues often happen to be idle क्रम लघु समय
	 * periods, and during such समय periods other queues with
	 * higher बारtamps happen to be busy, then the backshअगरted
	 * बारtamps of the क्रमmer queues can become much lower than
	 * the प्रणाली भव समय. In fact, to serve the queues with
	 * higher बारtamps जबतक the ones with lower बारtamps are
	 * idle, the प्रणाली भव समय may be pushed-up to much
	 * higher values than the finish बारtamps of the idle
	 * queues. As a consequence, the finish बारtamps of all new
	 * or newly activated queues may end up being much larger than
	 * those of lucky queues with backshअगरted बारtamps. The
	 * latter queues may then monopolize the device क्रम a lot of
	 * समय. This would simply अवरोध service guarantees.
	 *
	 * To reduce this problem, push up a little bit the
	 * backshअगरted बारtamps of the queue associated with this
	 * entity (only a queue can happen to have the backshअगरted
	 * flag set): just enough to let the finish बारtamp of the
	 * queue be equal to the current value of the प्रणाली भव
	 * समय. This may पूर्णांकroduce a little unfairness among queues
	 * with backshअगरted बारtamps, but it करोes not अवरोध
	 * worst-हाल fairness guarantees.
	 *
	 * As a special हाल, अगर bfqq is weight-उठाओd, push up
	 * बारtamps much less, to keep very low the probability that
	 * this push up causes the backshअगरted finish बारtamps of
	 * weight-उठाओd queues to become higher than the backshअगरted
	 * finish बारtamps of non weight-उठाओd queues.
	 */
	अगर (backshअगरted && bfq_gt(st->vसमय, entity->finish)) अणु
		अचिन्हित दीर्घ delta = st->vसमय - entity->finish;

		अगर (bfqq)
			delta /= bfqq->wr_coeff;

		entity->start += delta;
		entity->finish += delta;
	पूर्ण

	bfq_active_insert(st, entity);
पूर्ण

/**
 * __bfq_activate_entity - handle activation of entity.
 * @entity: the entity being activated.
 * @non_blocking_रुको_rq: true अगर entity was रुकोing क्रम a request
 *
 * Called क्रम a 'true' activation, i.e., अगर entity is not active and
 * one of its children receives a new request.
 *
 * Basically, this function updates the बारtamps of entity and
 * inserts entity पूर्णांकo its active tree, after possibly extracting it
 * from its idle tree.
 */
अटल व्योम __bfq_activate_entity(काष्ठा bfq_entity *entity,
				  bool non_blocking_रुको_rq)
अणु
	काष्ठा bfq_service_tree *st = bfq_entity_service_tree(entity);
	bool backshअगरted = false;
	अचिन्हित दीर्घ दीर्घ min_vstart;

	/* See comments on bfq_fqq_update_budg_क्रम_activation */
	अगर (non_blocking_रुको_rq && bfq_gt(st->vसमय, entity->finish)) अणु
		backshअगरted = true;
		min_vstart = entity->finish;
	पूर्ण अन्यथा
		min_vstart = st->vसमय;

	अगर (entity->tree == &st->idle) अणु
		/*
		 * Must be on the idle tree, bfq_idle_extract() will
		 * check क्रम that.
		 */
		bfq_idle_extract(st, entity);
		entity->start = bfq_gt(min_vstart, entity->finish) ?
			min_vstart : entity->finish;
	पूर्ण अन्यथा अणु
		/*
		 * The finish समय of the entity may be invalid, and
		 * it is in the past क्रम sure, otherwise the queue
		 * would have been on the idle tree.
		 */
		entity->start = min_vstart;
		st->wsum += entity->weight;
		/*
		 * entity is about to be inserted पूर्णांकo a service tree,
		 * and then set in service: get a reference to make
		 * sure entity करोes not disappear until it is no
		 * दीर्घer in service or scheduled क्रम service.
		 */
		bfq_get_entity(entity);

		entity->on_st_or_in_serv = true;
	पूर्ण

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	अगर (!bfq_entity_to_bfqq(entity)) अणु /* bfq_group */
		काष्ठा bfq_group *bfqg =
			container_of(entity, काष्ठा bfq_group, entity);
		काष्ठा bfq_data *bfqd = bfqg->bfqd;

		अगर (!entity->in_groups_with_pending_reqs) अणु
			entity->in_groups_with_pending_reqs = true;
			bfqd->num_groups_with_pending_reqs++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	bfq_update_fin_समय_enqueue(entity, st, backshअगरted);
पूर्ण

/**
 * __bfq_requeue_entity - handle requeueing or repositioning of an entity.
 * @entity: the entity being requeued or repositioned.
 *
 * Requeueing is needed अगर this entity stops being served, which
 * happens अगर a leaf descendant entity has expired. On the other hand,
 * repositioning is needed अगर the next_inservice_entity क्रम the child
 * entity has changed. See the comments inside the function क्रम
 * details.
 *
 * Basically, this function: 1) हटाओs entity from its active tree अगर
 * present there, 2) updates the बारtamps of entity and 3) inserts
 * entity back पूर्णांकo its active tree (in the new, right position क्रम
 * the new values of the बारtamps).
 */
अटल व्योम __bfq_requeue_entity(काष्ठा bfq_entity *entity)
अणु
	काष्ठा bfq_sched_data *sd = entity->sched_data;
	काष्ठा bfq_service_tree *st = bfq_entity_service_tree(entity);

	अगर (entity == sd->in_service_entity) अणु
		/*
		 * We are requeueing the current in-service entity,
		 * which may have to be करोne क्रम one of the following
		 * reasons:
		 * - entity represents the in-service queue, and the
		 *   in-service queue is being requeued after an
		 *   expiration;
		 * - entity represents a group, and its budget has
		 *   changed because one of its child entities has
		 *   just been either activated or requeued क्रम some
		 *   reason; the बारtamps of the entity need then to
		 *   be updated, and the entity needs to be enqueued
		 *   or repositioned accordingly.
		 *
		 * In particular, beक्रमe requeueing, the start समय of
		 * the entity must be moved क्रमward to account क्रम the
		 * service that the entity has received जबतक in
		 * service. This is करोne by the next inकाष्ठाions. The
		 * finish समय will then be updated according to this
		 * new value of the start समय, and to the budget of
		 * the entity.
		 */
		bfq_calc_finish(entity, entity->service);
		entity->start = entity->finish;
		/*
		 * In addition, अगर the entity had more than one child
		 * when set in service, then it was not extracted from
		 * the active tree. This implies that the position of
		 * the entity in the active tree may need to be
		 * changed now, because we have just updated the start
		 * समय of the entity, and we will update its finish
		 * समय in a moment (the requeueing is then, more
		 * precisely, a repositioning in this हाल). To
		 * implement this repositioning, we: 1) dequeue the
		 * entity here, 2) update the finish समय and requeue
		 * the entity according to the new बारtamps below.
		 */
		अगर (entity->tree)
			bfq_active_extract(st, entity);
	पूर्ण अन्यथा अणु /* The entity is alपढ़ोy active, and not in service */
		/*
		 * In this हाल, this function माला_लो called only अगर the
		 * next_in_service entity below this entity has
		 * changed, and this change has caused the budget of
		 * this entity to change, which, finally implies that
		 * the finish समय of this entity must be
		 * updated. Such an update may cause the scheduling,
		 * i.e., the position in the active tree, of this
		 * entity to change. We handle this change by: 1)
		 * dequeueing the entity here, 2) updating the finish
		 * समय and requeueing the entity according to the new
		 * बारtamps below. This is the same approach as the
		 * non-extracted-entity sub-हाल above.
		 */
		bfq_active_extract(st, entity);
	पूर्ण

	bfq_update_fin_समय_enqueue(entity, st, false);
पूर्ण

अटल व्योम __bfq_activate_requeue_entity(काष्ठा bfq_entity *entity,
					  काष्ठा bfq_sched_data *sd,
					  bool non_blocking_रुको_rq)
अणु
	काष्ठा bfq_service_tree *st = bfq_entity_service_tree(entity);

	अगर (sd->in_service_entity == entity || entity->tree == &st->active)
		 /*
		  * in service or alपढ़ोy queued on the active tree,
		  * requeue or reposition
		  */
		__bfq_requeue_entity(entity);
	अन्यथा
		/*
		 * Not in service and not queued on its active tree:
		 * the activity is idle and this is a true activation.
		 */
		__bfq_activate_entity(entity, non_blocking_रुको_rq);
पूर्ण


/**
 * bfq_activate_requeue_entity - activate or requeue an entity representing a
 *				 bfq_queue, and activate, requeue or reposition
 *				 all ancestors क्रम which such an update becomes
 *				 necessary.
 * @entity: the entity to activate.
 * @non_blocking_रुको_rq: true अगर this entity was रुकोing क्रम a request
 * @requeue: true अगर this is a requeue, which implies that bfqq is
 *	     being expired; thus ALL its ancestors stop being served and must
 *	     thereक्रमe be requeued
 * @expiration: true अगर this function is being invoked in the expiration path
 *             of the in-service queue
 */
अटल व्योम bfq_activate_requeue_entity(काष्ठा bfq_entity *entity,
					bool non_blocking_रुको_rq,
					bool requeue, bool expiration)
अणु
	काष्ठा bfq_sched_data *sd;

	क्रम_each_entity(entity) अणु
		sd = entity->sched_data;
		__bfq_activate_requeue_entity(entity, sd, non_blocking_रुको_rq);

		अगर (!bfq_update_next_in_service(sd, entity, expiration) &&
		    !requeue)
			अवरोध;
	पूर्ण
पूर्ण

/**
 * __bfq_deactivate_entity - update sched_data and service trees क्रम
 * entity, so as to represent entity as inactive
 * @entity: the entity being deactivated.
 * @ins_पूर्णांकo_idle_tree: अगर false, the entity will not be put पूर्णांकo the
 *			idle tree.
 *
 * If necessary and allowed, माला_दो entity पूर्णांकo the idle tree. NOTE:
 * entity may be on no tree अगर in service.
 */
bool __bfq_deactivate_entity(काष्ठा bfq_entity *entity, bool ins_पूर्णांकo_idle_tree)
अणु
	काष्ठा bfq_sched_data *sd = entity->sched_data;
	काष्ठा bfq_service_tree *st;
	bool is_in_service;

	अगर (!entity->on_st_or_in_serv) /*
					* entity never activated, or
					* alपढ़ोy inactive
					*/
		वापस false;

	/*
	 * If we get here, then entity is active, which implies that
	 * bfq_group_set_parent has alपढ़ोy been invoked क्रम the group
	 * represented by entity. Thereक्रमe, the field
	 * entity->sched_data has been set, and we can safely use it.
	 */
	st = bfq_entity_service_tree(entity);
	is_in_service = entity == sd->in_service_entity;

	bfq_calc_finish(entity, entity->service);

	अगर (is_in_service)
		sd->in_service_entity = शून्य;
	अन्यथा
		/*
		 * Non in-service entity: nobody will take care of
		 * resetting its service counter on expiration. Do it
		 * now.
		 */
		entity->service = 0;

	अगर (entity->tree == &st->active)
		bfq_active_extract(st, entity);
	अन्यथा अगर (!is_in_service && entity->tree == &st->idle)
		bfq_idle_extract(st, entity);

	अगर (!ins_पूर्णांकo_idle_tree || !bfq_gt(entity->finish, st->vसमय))
		bfq_क्रमget_entity(st, entity, is_in_service);
	अन्यथा
		bfq_idle_insert(st, entity);

	वापस true;
पूर्ण

/**
 * bfq_deactivate_entity - deactivate an entity representing a bfq_queue.
 * @entity: the entity to deactivate.
 * @ins_पूर्णांकo_idle_tree: true अगर the entity can be put पूर्णांकo the idle tree
 * @expiration: true अगर this function is being invoked in the expiration path
 *             of the in-service queue
 */
अटल व्योम bfq_deactivate_entity(काष्ठा bfq_entity *entity,
				  bool ins_पूर्णांकo_idle_tree,
				  bool expiration)
अणु
	काष्ठा bfq_sched_data *sd;
	काष्ठा bfq_entity *parent = शून्य;

	क्रम_each_entity_safe(entity, parent) अणु
		sd = entity->sched_data;

		अगर (!__bfq_deactivate_entity(entity, ins_पूर्णांकo_idle_tree)) अणु
			/*
			 * entity is not in any tree any more, so
			 * this deactivation is a no-op, and there is
			 * nothing to change क्रम upper-level entities
			 * (in हाल of expiration, this can never
			 * happen).
			 */
			वापस;
		पूर्ण

		अगर (sd->next_in_service == entity)
			/*
			 * entity was the next_in_service entity,
			 * then, since entity has just been
			 * deactivated, a new one must be found.
			 */
			bfq_update_next_in_service(sd, शून्य, expiration);

		अगर (sd->next_in_service || sd->in_service_entity) अणु
			/*
			 * The parent entity is still active, because
			 * either next_in_service or in_service_entity
			 * is not शून्य. So, no further upwards
			 * deactivation must be perक्रमmed.  Yet,
			 * next_in_service has changed.	Then the
			 * schedule करोes need to be updated upwards.
			 *
			 * NOTE If in_service_entity is not शून्य, then
			 * next_in_service may happen to be शून्य,
			 * although the parent entity is evidently
			 * active. This happens अगर 1) the entity
			 * poपूर्णांकed by in_service_entity is the only
			 * active entity in the parent entity, and 2)
			 * according to the definition of
			 * next_in_service, the in_service_entity
			 * cannot be considered as
			 * next_in_service. See the comments on the
			 * definition of next_in_service क्रम details.
			 */
			अवरोध;
		पूर्ण

		/*
		 * If we get here, then the parent is no more
		 * backlogged and we need to propagate the
		 * deactivation upwards. Thus let the loop go on.
		 */

		/*
		 * Also let parent be queued पूर्णांकo the idle tree on
		 * deactivation, to preserve service guarantees, and
		 * assuming that who invoked this function करोes not
		 * need parent entities too to be हटाओd completely.
		 */
		ins_पूर्णांकo_idle_tree = true;
	पूर्ण

	/*
	 * If the deactivation loop is fully executed, then there are
	 * no more entities to touch and next loop is not executed at
	 * all. Otherwise, requeue reमुख्यing entities अगर they are
	 * about to stop receiving service, or reposition them अगर this
	 * is not the हाल.
	 */
	entity = parent;
	क्रम_each_entity(entity) अणु
		/*
		 * Invoke __bfq_requeue_entity on entity, even अगर
		 * alपढ़ोy active, to requeue/reposition it in the
		 * active tree (because sd->next_in_service has
		 * changed)
		 */
		__bfq_requeue_entity(entity);

		sd = entity->sched_data;
		अगर (!bfq_update_next_in_service(sd, entity, expiration) &&
		    !expiration)
			/*
			 * next_in_service unchanged or not causing
			 * any change in entity->parent->sd, and no
			 * requeueing needed क्रम expiration: stop
			 * here.
			 */
			अवरोध;
	पूर्ण
पूर्ण

/**
 * bfq_calc_vसमय_jump - compute the value to which the vसमय should jump,
 *                       अगर needed, to have at least one entity eligible.
 * @st: the service tree to act upon.
 *
 * Assumes that st is not empty.
 */
अटल u64 bfq_calc_vसमय_jump(काष्ठा bfq_service_tree *st)
अणु
	काष्ठा bfq_entity *root_entity = bfq_root_active_entity(&st->active);

	अगर (bfq_gt(root_entity->min_start, st->vसमय))
		वापस root_entity->min_start;

	वापस st->vसमय;
पूर्ण

अटल व्योम bfq_update_vसमय(काष्ठा bfq_service_tree *st, u64 new_value)
अणु
	अगर (new_value > st->vसमय) अणु
		st->vसमय = new_value;
		bfq_क्रमget_idle(st);
	पूर्ण
पूर्ण

/**
 * bfq_first_active_entity - find the eligible entity with
 *                           the smallest finish समय
 * @st: the service tree to select from.
 * @vसमय: the प्रणाली भव to use as a reference क्रम eligibility
 *
 * This function searches the first schedulable entity, starting from the
 * root of the tree and going on the left every समय on this side there is
 * a subtree with at least one eligible (start <= vसमय) entity. The path on
 * the right is followed only अगर a) the left subtree contains no eligible
 * entities and b) no eligible entity has been found yet.
 */
अटल काष्ठा bfq_entity *bfq_first_active_entity(काष्ठा bfq_service_tree *st,
						  u64 vसमय)
अणु
	काष्ठा bfq_entity *entry, *first = शून्य;
	काष्ठा rb_node *node = st->active.rb_node;

	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा bfq_entity, rb_node);
left:
		अगर (!bfq_gt(entry->start, vसमय))
			first = entry;

		अगर (node->rb_left) अणु
			entry = rb_entry(node->rb_left,
					 काष्ठा bfq_entity, rb_node);
			अगर (!bfq_gt(entry->min_start, vसमय)) अणु
				node = node->rb_left;
				जाओ left;
			पूर्ण
		पूर्ण
		अगर (first)
			अवरोध;
		node = node->rb_right;
	पूर्ण

	वापस first;
पूर्ण

/**
 * __bfq_lookup_next_entity - वापस the first eligible entity in @st.
 * @st: the service tree.
 *
 * If there is no in-service entity क्रम the sched_data st beदीर्घs to,
 * then वापस the entity that will be set in service अगर:
 * 1) the parent entity this st beदीर्घs to is set in service;
 * 2) no entity beदीर्घing to such parent entity undergoes a state change
 * that would influence the बारtamps of the entity (e.g., becomes idle,
 * becomes backlogged, changes its budget, ...).
 *
 * In this first हाल, update the भव समय in @st too (see the
 * comments on this update inside the function).
 *
 * In contrast, अगर there is an in-service entity, then वापस the
 * entity that would be set in service अगर not only the above
 * conditions, but also the next one held true: the currently
 * in-service entity, on expiration,
 * 1) माला_लो a finish समय equal to the current one, or
 * 2) is not eligible any more, or
 * 3) is idle.
 */
अटल काष्ठा bfq_entity *
__bfq_lookup_next_entity(काष्ठा bfq_service_tree *st, bool in_service)
अणु
	काष्ठा bfq_entity *entity;
	u64 new_vसमय;

	अगर (RB_EMPTY_ROOT(&st->active))
		वापस शून्य;

	/*
	 * Get the value of the प्रणाली भव समय क्रम which at
	 * least one entity is eligible.
	 */
	new_vसमय = bfq_calc_vसमय_jump(st);

	/*
	 * If there is no in-service entity क्रम the sched_data this
	 * active tree beदीर्घs to, then push the प्रणाली भव समय
	 * up to the value that guarantees that at least one entity is
	 * eligible. If, instead, there is an in-service entity, then
	 * करो not make any such update, because there is alपढ़ोy an
	 * eligible entity, namely the in-service one (even अगर the
	 * entity is not on st, because it was extracted when set in
	 * service).
	 */
	अगर (!in_service)
		bfq_update_vसमय(st, new_vसमय);

	entity = bfq_first_active_entity(st, new_vसमय);

	वापस entity;
पूर्ण

/**
 * bfq_lookup_next_entity - वापस the first eligible entity in @sd.
 * @sd: the sched_data.
 * @expiration: true अगर we are on the expiration path of the in-service queue
 *
 * This function is invoked when there has been a change in the trees
 * क्रम sd, and we need to know what is the new next entity to serve
 * after this change.
 */
अटल काष्ठा bfq_entity *bfq_lookup_next_entity(काष्ठा bfq_sched_data *sd,
						 bool expiration)
अणु
	काष्ठा bfq_service_tree *st = sd->service_tree;
	काष्ठा bfq_service_tree *idle_class_st = st + (BFQ_IOPRIO_CLASSES - 1);
	काष्ठा bfq_entity *entity = शून्य;
	पूर्णांक class_idx = 0;

	/*
	 * Choose from idle class, अगर needed to guarantee a minimum
	 * bandwidth to this class (and अगर there is some active entity
	 * in idle class). This should also mitigate
	 * priority-inversion problems in हाल a low priority task is
	 * holding file प्रणाली resources.
	 */
	अगर (समय_is_beक्रमe_jअगरfies(sd->bfq_class_idle_last_service +
				   BFQ_CL_IDLE_TIMEOUT)) अणु
		अगर (!RB_EMPTY_ROOT(&idle_class_st->active))
			class_idx = BFQ_IOPRIO_CLASSES - 1;
		/* About to be served अगर backlogged, or not yet backlogged */
		sd->bfq_class_idle_last_service = jअगरfies;
	पूर्ण

	/*
	 * Find the next entity to serve क्रम the highest-priority
	 * class, unless the idle class needs to be served.
	 */
	क्रम (; class_idx < BFQ_IOPRIO_CLASSES; class_idx++) अणु
		/*
		 * If expiration is true, then bfq_lookup_next_entity
		 * is being invoked as a part of the expiration path
		 * of the in-service queue. In this हाल, even अगर
		 * sd->in_service_entity is not शून्य,
		 * sd->in_service_entity at this poपूर्णांक is actually not
		 * in service any more, and, अगर needed, has alपढ़ोy
		 * been properly queued or requeued पूर्णांकo the right
		 * tree. The reason why sd->in_service_entity is still
		 * not शून्य here, even अगर expiration is true, is that
		 * sd->in_service_entity is reset as a last step in the
		 * expiration path. So, अगर expiration is true, tell
		 * __bfq_lookup_next_entity that there is no
		 * sd->in_service_entity.
		 */
		entity = __bfq_lookup_next_entity(st + class_idx,
						  sd->in_service_entity &&
						  !expiration);

		अगर (entity)
			अवरोध;
	पूर्ण

	अगर (!entity)
		वापस शून्य;

	वापस entity;
पूर्ण

bool next_queue_may_preempt(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_sched_data *sd = &bfqd->root_group->sched_data;

	वापस sd->next_in_service != sd->in_service_entity;
पूर्ण

/*
 * Get next queue क्रम service.
 */
काष्ठा bfq_queue *bfq_get_next_queue(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_entity *entity = शून्य;
	काष्ठा bfq_sched_data *sd;
	काष्ठा bfq_queue *bfqq;

	अगर (bfq_tot_busy_queues(bfqd) == 0)
		वापस शून्य;

	/*
	 * Traverse the path from the root to the leaf entity to
	 * serve. Set in service all the entities visited aदीर्घ the
	 * way.
	 */
	sd = &bfqd->root_group->sched_data;
	क्रम (; sd ; sd = entity->my_sched_data) अणु
		/*
		 * WARNING. We are about to set the in-service entity
		 * to sd->next_in_service, i.e., to the (cached) value
		 * वापसed by bfq_lookup_next_entity(sd) the last
		 * समय it was invoked, i.e., the last समय when the
		 * service order in sd changed as a consequence of the
		 * activation or deactivation of an entity. In this
		 * respect, अगर we execute bfq_lookup_next_entity(sd)
		 * in this very moment, it may, although with low
		 * probability, yield a dअगरferent entity than that
		 * poपूर्णांकed to by sd->next_in_service. This rare event
		 * happens in हाल there was no CLASS_IDLE entity to
		 * serve क्रम sd when bfq_lookup_next_entity(sd) was
		 * invoked क्रम the last समय, जबतक there is now one
		 * such entity.
		 *
		 * If the above event happens, then the scheduling of
		 * such entity in CLASS_IDLE is postponed until the
		 * service of the sd->next_in_service entity
		 * finishes. In fact, when the latter is expired,
		 * bfq_lookup_next_entity(sd) माला_लो called again,
		 * exactly to update sd->next_in_service.
		 */

		/* Make next_in_service entity become in_service_entity */
		entity = sd->next_in_service;
		sd->in_service_entity = entity;

		/*
		 * If entity is no दीर्घer a candidate क्रम next
		 * service, then it must be extracted from its active
		 * tree, so as to make sure that it won't be
		 * considered when computing next_in_service. See the
		 * comments on the function
		 * bfq_no_दीर्घer_next_in_service() क्रम details.
		 */
		अगर (bfq_no_दीर्घer_next_in_service(entity))
			bfq_active_extract(bfq_entity_service_tree(entity),
					   entity);

		/*
		 * Even अगर entity is not to be extracted according to
		 * the above check, a descendant entity may get
		 * extracted in one of the next iterations of this
		 * loop. Such an event could cause a change in
		 * next_in_service क्रम the level of the descendant
		 * entity, and thus possibly back to this level.
		 *
		 * However, we cannot perक्रमm the resulting needed
		 * update of next_in_service क्रम this level beक्रमe the
		 * end of the whole loop, because, to know which is
		 * the correct next-to-serve candidate entity क्रम each
		 * level, we need first to find the leaf entity to set
		 * in service. In fact, only after we know which is
		 * the next-to-serve leaf entity, we can discover
		 * whether the parent entity of the leaf entity
		 * becomes the next-to-serve, and so on.
		 */
	पूर्ण

	bfqq = bfq_entity_to_bfqq(entity);

	/*
	 * We can finally update all next-to-serve entities aदीर्घ the
	 * path from the leaf entity just set in service to the root.
	 */
	क्रम_each_entity(entity) अणु
		काष्ठा bfq_sched_data *sd = entity->sched_data;

		अगर (!bfq_update_next_in_service(sd, शून्य, false))
			अवरोध;
	पूर्ण

	वापस bfqq;
पूर्ण

/* वापसs true अगर the in-service queue माला_लो मुक्तd */
bool __bfq_bfqd_reset_in_service(काष्ठा bfq_data *bfqd)
अणु
	काष्ठा bfq_queue *in_serv_bfqq = bfqd->in_service_queue;
	काष्ठा bfq_entity *in_serv_entity = &in_serv_bfqq->entity;
	काष्ठा bfq_entity *entity = in_serv_entity;

	bfq_clear_bfqq_रुको_request(in_serv_bfqq);
	hrसमयr_try_to_cancel(&bfqd->idle_slice_समयr);
	bfqd->in_service_queue = शून्य;

	/*
	 * When this function is called, all in-service entities have
	 * been properly deactivated or requeued, so we can safely
	 * execute the final step: reset in_service_entity aदीर्घ the
	 * path from entity to the root.
	 */
	क्रम_each_entity(entity)
		entity->sched_data->in_service_entity = शून्य;

	/*
	 * in_serv_entity is no दीर्घer in service, so, अगर it is in no
	 * service tree either, then release the service reference to
	 * the queue it represents (taken with bfq_get_entity).
	 */
	अगर (!in_serv_entity->on_st_or_in_serv) अणु
		/*
		 * If no process is referencing in_serv_bfqq any
		 * दीर्घer, then the service reference may be the only
		 * reference to the queue. If this is the हाल, then
		 * bfqq माला_लो मुक्तd here.
		 */
		पूर्णांक ref = in_serv_bfqq->ref;
		bfq_put_queue(in_serv_bfqq);
		अगर (ref == 1)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम bfq_deactivate_bfqq(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			 bool ins_पूर्णांकo_idle_tree, bool expiration)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;

	bfq_deactivate_entity(entity, ins_पूर्णांकo_idle_tree, expiration);
पूर्ण

व्योम bfq_activate_bfqq(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;

	bfq_activate_requeue_entity(entity, bfq_bfqq_non_blocking_रुको_rq(bfqq),
				    false, false);
	bfq_clear_bfqq_non_blocking_रुको_rq(bfqq);
पूर्ण

व्योम bfq_requeue_bfqq(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		      bool expiration)
अणु
	काष्ठा bfq_entity *entity = &bfqq->entity;

	bfq_activate_requeue_entity(entity, false,
				    bfqq == bfqd->in_service_queue, expiration);
पूर्ण

/*
 * Called when the bfqq no दीर्घer has requests pending, हटाओ it from
 * the service tree. As a special हाल, it can be invoked during an
 * expiration.
 */
व्योम bfq_del_bfqq_busy(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		       bool expiration)
अणु
	bfq_log_bfqq(bfqd, bfqq, "del from busy");

	bfq_clear_bfqq_busy(bfqq);

	bfqd->busy_queues[bfqq->ioprio_class - 1]--;

	अगर (bfqq->wr_coeff > 1)
		bfqd->wr_busy_queues--;

	bfqg_stats_update_dequeue(bfqq_group(bfqq));

	bfq_deactivate_bfqq(bfqd, bfqq, true, expiration);

	अगर (!bfqq->dispatched)
		bfq_weights_tree_हटाओ(bfqd, bfqq);
पूर्ण

/*
 * Called when an inactive queue receives a new request.
 */
व्योम bfq_add_bfqq_busy(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq)
अणु
	bfq_log_bfqq(bfqd, bfqq, "add to busy");

	bfq_activate_bfqq(bfqd, bfqq);

	bfq_mark_bfqq_busy(bfqq);
	bfqd->busy_queues[bfqq->ioprio_class - 1]++;

	अगर (!bfqq->dispatched)
		अगर (bfqq->wr_coeff == 1)
			bfq_weights_tree_add(bfqd, bfqq,
					     &bfqd->queue_weights_tree);

	अगर (bfqq->wr_coeff > 1)
		bfqd->wr_busy_queues++;

	/* Move bfqq to the head of the woken list of its waker */
	अगर (!hlist_unhashed(&bfqq->woken_list_node) &&
	    &bfqq->woken_list_node != bfqq->waker_bfqq->woken_list.first) अणु
		hlist_del_init(&bfqq->woken_list_node);
		hlist_add_head(&bfqq->woken_list_node,
			       &bfqq->waker_bfqq->woken_list);
	पूर्ण
पूर्ण
