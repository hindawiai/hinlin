<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: nsalloc - Namespace allocation and deletion utilities
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsalloc")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_create_node
 *
 * PARAMETERS:  name            - Name of the new node (4 अक्षर ACPI name)
 *
 * RETURN:      New namespace node (Null on failure)
 *
 * DESCRIPTION: Create a namespace node
 *
 ******************************************************************************/
काष्ठा acpi_namespace_node *acpi_ns_create_node(u32 name)
अणु
	काष्ठा acpi_namespace_node *node;
#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
	u32 temp;
#पूर्ण_अगर

	ACPI_FUNCTION_TRACE(ns_create_node);

	node = acpi_os_acquire_object(acpi_gbl_namespace_cache);
	अगर (!node) अणु
		वापस_PTR(शून्य);
	पूर्ण

	ACPI_MEM_TRACKING(acpi_gbl_ns_node_list->total_allocated++);

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
	temp = acpi_gbl_ns_node_list->total_allocated -
	    acpi_gbl_ns_node_list->total_मुक्तd;
	अगर (temp > acpi_gbl_ns_node_list->max_occupied) अणु
		acpi_gbl_ns_node_list->max_occupied = temp;
	पूर्ण
#पूर्ण_अगर

	node->name.पूर्णांकeger = name;
	ACPI_SET_DESCRIPTOR_TYPE(node, ACPI_DESC_TYPE_NAMED);
	वापस_PTR(node);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_delete_node
 *
 * PARAMETERS:  node            - Node to be deleted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete a namespace node. All node deletions must come through
 *              here. Detaches any attached objects, including any attached
 *              data. If a handler is associated with attached data, it is
 *              invoked beक्रमe the node is deleted.
 *
 ******************************************************************************/

व्योम acpi_ns_delete_node(काष्ठा acpi_namespace_node *node)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *next_desc;

	ACPI_FUNCTION_NAME(ns_delete_node);

	अगर (!node) अणु
		वापस_VOID;
	पूर्ण

	/* Detach an object अगर there is one */

	acpi_ns_detach_object(node);

	/*
	 * Delete an attached data object list अगर present (objects that were
	 * attached via acpi_attach_data). Note: After any normal object is
	 * detached above, the only possible reमुख्यing object(s) are data
	 * objects, in a linked list.
	 */
	obj_desc = node->object;
	जबतक (obj_desc && (obj_desc->common.type == ACPI_TYPE_LOCAL_DATA)) अणु

		/* Invoke the attached data deletion handler अगर present */

		अगर (obj_desc->data.handler) अणु
			obj_desc->data.handler(node, obj_desc->data.poपूर्णांकer);
		पूर्ण

		next_desc = obj_desc->common.next_object;
		acpi_ut_हटाओ_reference(obj_desc);
		obj_desc = next_desc;
	पूर्ण

	/* Special हाल क्रम the अटलally allocated root node */

	अगर (node == acpi_gbl_root_node) अणु
		वापस;
	पूर्ण

	/* Now we can delete the node */

	(व्योम)acpi_os_release_object(acpi_gbl_namespace_cache, node);

	ACPI_MEM_TRACKING(acpi_gbl_ns_node_list->total_मुक्तd++);
	ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS, "Node %p, Remaining %X\n",
			  node, acpi_gbl_current_node_count));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_हटाओ_node
 *
 * PARAMETERS:  node            - Node to be हटाओd/deleted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Remove (unlink) and delete a namespace node
 *
 ******************************************************************************/

व्योम acpi_ns_हटाओ_node(काष्ठा acpi_namespace_node *node)
अणु
	काष्ठा acpi_namespace_node *parent_node;
	काष्ठा acpi_namespace_node *prev_node;
	काष्ठा acpi_namespace_node *next_node;

	ACPI_FUNCTION_TRACE_PTR(ns_हटाओ_node, node);

	parent_node = node->parent;

	prev_node = शून्य;
	next_node = parent_node->child;

	/* Find the node that is the previous peer in the parent's child list */

	जबतक (next_node != node) अणु
		prev_node = next_node;
		next_node = next_node->peer;
	पूर्ण

	अगर (prev_node) अणु

		/* Node is not first child, unlink it */

		prev_node->peer = node->peer;
	पूर्ण अन्यथा अणु
		/*
		 * Node is first child (has no previous peer).
		 * Link peer list to parent
		 */
		parent_node->child = node->peer;
	पूर्ण

	/* Delete the node and any attached objects */

	acpi_ns_delete_node(node);
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_install_node
 *
 * PARAMETERS:  walk_state      - Current state of the walk
 *              parent_node     - The parent of the new Node
 *              node            - The new Node to install
 *              type            - ACPI object type of the new Node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a new namespace node and install it amongst
 *              its peers.
 *
 *              Note: Current namespace lookup is linear search. This appears
 *              to be sufficient as namespace searches consume only a small
 *              fraction of the execution समय of the ACPI subप्रणाली.
 *
 ******************************************************************************/

व्योम acpi_ns_install_node(काष्ठा acpi_walk_state *walk_state, काष्ठा acpi_namespace_node *parent_node,	/* Parent */
			  काष्ठा acpi_namespace_node *node,	/* New Child */
			  acpi_object_type type)
अणु
	acpi_owner_id owner_id = 0;
	काष्ठा acpi_namespace_node *child_node;

	ACPI_FUNCTION_TRACE(ns_install_node);

	अगर (walk_state) अणु
		/*
		 * Get the owner ID from the Walk state. The owner ID is used to
		 * track table deletion and deletion of objects created by methods.
		 */
		owner_id = walk_state->owner_id;

		अगर ((walk_state->method_desc) &&
		    (parent_node != walk_state->method_node)) अणु
			/*
			 * A method is creating a new node that is not a child of the
			 * method (it is non-local). Mark the executing method as having
			 * modअगरied the namespace. This is used क्रम cleanup when the
			 * method निकासs.
			 */
			walk_state->method_desc->method.info_flags |=
			    ACPI_METHOD_MODIFIED_NAMESPACE;
		पूर्ण
	पूर्ण

	/* Link the new entry पूर्णांकo the parent and existing children */

	node->peer = शून्य;
	node->parent = parent_node;
	child_node = parent_node->child;

	अगर (!child_node) अणु
		parent_node->child = node;
	पूर्ण अन्यथा अणु
		/* Add node to the end of the peer list */

		जबतक (child_node->peer) अणु
			child_node = child_node->peer;
		पूर्ण

		child_node->peer = node;
	पूर्ण

	/* Init the new entry */

	node->owner_id = owner_id;
	node->type = (u8) type;

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
			  "%4.4s (%s) [Node %p Owner %3.3X] added to %4.4s (%s) [Node %p]\n",
			  acpi_ut_get_node_name(node),
			  acpi_ut_get_type_name(node->type), node, owner_id,
			  acpi_ut_get_node_name(parent_node),
			  acpi_ut_get_type_name(parent_node->type),
			  parent_node));

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_delete_children
 *
 * PARAMETERS:  parent_node     - Delete this objects children
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete all children of the parent object. In other words,
 *              deletes a "scope".
 *
 ******************************************************************************/

व्योम acpi_ns_delete_children(काष्ठा acpi_namespace_node *parent_node)
अणु
	काष्ठा acpi_namespace_node *next_node;
	काष्ठा acpi_namespace_node *node_to_delete;

	ACPI_FUNCTION_TRACE_PTR(ns_delete_children, parent_node);

	अगर (!parent_node) अणु
		वापस_VOID;
	पूर्ण

	/* Deallocate all children at this level */

	next_node = parent_node->child;
	जबतक (next_node) अणु

		/* Gअक्रमchildren should have all been deleted alपढ़ोy */

		अगर (next_node->child) अणु
			ACPI_ERROR((AE_INFO, "Found a grandchild! P=%p C=%p",
				    parent_node, next_node));
		पूर्ण

		/*
		 * Delete this child node and move on to the next child in the list.
		 * No need to unlink the node since we are deleting the entire branch.
		 */
		node_to_delete = next_node;
		next_node = next_node->peer;
		acpi_ns_delete_node(node_to_delete);
	पूर्ण

	/* Clear the parent's child poपूर्णांकer */

	parent_node->child = शून्य;
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_delete_namespace_subtree
 *
 * PARAMETERS:  parent_node     - Root of the subtree to be deleted
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a subtree of the namespace. This includes all objects
 *              stored within the subtree.
 *
 ******************************************************************************/

व्योम acpi_ns_delete_namespace_subtree(काष्ठा acpi_namespace_node *parent_node)
अणु
	काष्ठा acpi_namespace_node *child_node = शून्य;
	u32 level = 1;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_delete_namespace_subtree);

	अगर (!parent_node) अणु
		वापस_VOID;
	पूर्ण

	/* Lock namespace क्रम possible update */

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_VOID;
	पूर्ण

	/*
	 * Traverse the tree of objects until we bubble back up
	 * to where we started.
	 */
	जबतक (level > 0) अणु

		/* Get the next node in this scope (शून्य अगर none) */

		child_node = acpi_ns_get_next_node(parent_node, child_node);
		अगर (child_node) अणु

			/* Found a child node - detach any attached object */

			acpi_ns_detach_object(child_node);

			/* Check अगर this node has any children */

			अगर (child_node->child) अणु
				/*
				 * There is at least one child of this node,
				 * visit the node
				 */
				level++;
				parent_node = child_node;
				child_node = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * No more children of this parent node.
			 * Move up to the gअक्रमparent.
			 */
			level--;

			/*
			 * Now delete all of the children of this parent
			 * all at the same समय.
			 */
			acpi_ns_delete_children(parent_node);

			/* New "last child" is this parent node */

			child_node = parent_node;

			/* Move up the tree to the gअक्रमparent */

			parent_node = parent_node->parent;
		पूर्ण
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_delete_namespace_by_owner
 *
 * PARAMETERS:  owner_id    - All nodes with this owner will be deleted
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete entries within the namespace that are owned by a
 *              specअगरic ID. Used to delete entire ACPI tables. All
 *              reference counts are updated.
 *
 * MUTEX:       Locks namespace during deletion walk.
 *
 ******************************************************************************/

व्योम acpi_ns_delete_namespace_by_owner(acpi_owner_id owner_id)
अणु
	काष्ठा acpi_namespace_node *child_node;
	काष्ठा acpi_namespace_node *deletion_node;
	काष्ठा acpi_namespace_node *parent_node;
	u32 level;
	acpi_status status;

	ACPI_FUNCTION_TRACE_U32(ns_delete_namespace_by_owner, owner_id);

	अगर (owner_id == 0) अणु
		वापस_VOID;
	पूर्ण

	/* Lock namespace क्रम possible update */

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_VOID;
	पूर्ण

	deletion_node = शून्य;
	parent_node = acpi_gbl_root_node;
	child_node = शून्य;
	level = 1;

	/*
	 * Traverse the tree of nodes until we bubble back up
	 * to where we started.
	 */
	जबतक (level > 0) अणु
		/*
		 * Get the next child of this parent node. When child_node is शून्य,
		 * the first child of the parent is वापसed
		 */
		child_node = acpi_ns_get_next_node(parent_node, child_node);

		अगर (deletion_node) अणु
			acpi_ns_delete_children(deletion_node);
			acpi_ns_हटाओ_node(deletion_node);
			deletion_node = शून्य;
		पूर्ण

		अगर (child_node) अणु
			अगर (child_node->owner_id == owner_id) अणु

				/* Found a matching child node - detach any attached object */

				acpi_ns_detach_object(child_node);
			पूर्ण

			/* Check अगर this node has any children */

			अगर (child_node->child) अणु
				/*
				 * There is at least one child of this node,
				 * visit the node
				 */
				level++;
				parent_node = child_node;
				child_node = शून्य;
			पूर्ण अन्यथा अगर (child_node->owner_id == owner_id) अणु
				deletion_node = child_node;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * No more children of this parent node.
			 * Move up to the gअक्रमparent.
			 */
			level--;
			अगर (level != 0) अणु
				अगर (parent_node->owner_id == owner_id) अणु
					deletion_node = parent_node;
				पूर्ण
			पूर्ण

			/* New "last child" is this parent node */

			child_node = parent_node;

			/* Move up the tree to the gअक्रमparent */

			parent_node = parent_node->parent;
		पूर्ण
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_VOID;
पूर्ण
