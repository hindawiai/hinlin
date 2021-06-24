<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nswalk - Functions क्रम walking the ACPI namespace
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nswalk")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_next_node
 *
 * PARAMETERS:  parent_node         - Parent node whose children we are
 *                                    getting
 *              child_node          - Previous child that was found.
 *                                    The NEXT child will be वापसed
 *
 * RETURN:      काष्ठा acpi_namespace_node - Poपूर्णांकer to the NEXT child or शून्य अगर
 *                                    none is found.
 *
 * DESCRIPTION: Return the next peer node within the namespace. If Handle
 *              is valid, Scope is ignored. Otherwise, the first node
 *              within Scope is वापसed.
 *
 ******************************************************************************/
काष्ठा acpi_namespace_node *acpi_ns_get_next_node(काष्ठा acpi_namespace_node
						  *parent_node,
						  काष्ठा acpi_namespace_node
						  *child_node)
अणु
	ACPI_FUNCTION_ENTRY();

	अगर (!child_node) अणु

		/* It's really the parent's _scope_ that we want */

		वापस (parent_node->child);
	पूर्ण

	/* Otherwise just वापस the next peer */

	वापस (child_node->peer);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_next_node_typed
 *
 * PARAMETERS:  type                - Type of node to be searched क्रम
 *              parent_node         - Parent node whose children we are
 *                                    getting
 *              child_node          - Previous child that was found.
 *                                    The NEXT child will be वापसed
 *
 * RETURN:      काष्ठा acpi_namespace_node - Poपूर्णांकer to the NEXT child or शून्य अगर
 *                                    none is found.
 *
 * DESCRIPTION: Return the next peer node within the namespace. If Handle
 *              is valid, Scope is ignored. Otherwise, the first node
 *              within Scope is वापसed.
 *
 ******************************************************************************/

काष्ठा acpi_namespace_node *acpi_ns_get_next_node_typed(acpi_object_type type,
							काष्ठा
							acpi_namespace_node
							*parent_node,
							काष्ठा
							acpi_namespace_node
							*child_node)
अणु
	काष्ठा acpi_namespace_node *next_node = शून्य;

	ACPI_FUNCTION_ENTRY();

	next_node = acpi_ns_get_next_node(parent_node, child_node);


	/* If any type is OK, we are करोne */

	अगर (type == ACPI_TYPE_ANY) अणु

		/* next_node is शून्य अगर we are at the end-of-list */

		वापस (next_node);
	पूर्ण

	/* Must search क्रम the node -- but within this scope only */

	जबतक (next_node) अणु

		/* If type matches, we are करोne */

		अगर (next_node->type == type) अणु
			वापस (next_node);
		पूर्ण

		/* Otherwise, move on to the next peer node */

		next_node = next_node->peer;
	पूर्ण

	/* Not found */

	वापस (शून्य);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_walk_namespace
 *
 * PARAMETERS:  type                - acpi_object_type to search क्रम
 *              start_node          - Handle in namespace where search begins
 *              max_depth           - Depth to which search is to reach
 *              flags               - Whether to unlock the NS beक्रमe invoking
 *                                    the callback routine
 *              descending_callback - Called during tree descent
 *                                    when an object of "Type" is found
 *              ascending_callback  - Called during tree ascent
 *                                    when an object of "Type" is found
 *              context             - Passed to user function(s) above
 *              वापस_value        - from the user_function अगर terminated
 *                                    early. Otherwise, वापसs शून्य.
 * RETURNS:     Status
 *
 * DESCRIPTION: Perक्रमms a modअगरied depth-first walk of the namespace tree,
 *              starting (and ending) at the node specअगरied by start_handle.
 *              The callback function is called whenever a node that matches
 *              the type parameter is found. If the callback function वापसs
 *              a non-zero value, the search is terminated immediately and
 *              this value is वापसed to the caller.
 *
 *              The poपूर्णांक of this procedure is to provide a generic namespace
 *              walk routine that can be called from multiple places to
 *              provide multiple services; the callback function(s) can be
 *              tailored to each task, whether it is a prपूर्णांक function,
 *              a compare function, etc.
 *
 ******************************************************************************/

acpi_status
acpi_ns_walk_namespace(acpi_object_type type,
		       acpi_handle start_node,
		       u32 max_depth,
		       u32 flags,
		       acpi_walk_callback descending_callback,
		       acpi_walk_callback ascending_callback,
		       व्योम *context, व्योम **वापस_value)
अणु
	acpi_status status;
	acpi_status mutex_status;
	काष्ठा acpi_namespace_node *child_node;
	काष्ठा acpi_namespace_node *parent_node;
	acpi_object_type child_type;
	u32 level;
	u8 node_previously_visited = FALSE;

	ACPI_FUNCTION_TRACE(ns_walk_namespace);

	/* Special हाल क्रम the namespace Root Node */

	अगर (start_node == ACPI_ROOT_OBJECT) अणु
		start_node = acpi_gbl_root_node;
	पूर्ण

	/* Null child means "get first node" */

	parent_node = start_node;
	child_node = acpi_ns_get_next_node(parent_node, शून्य);
	child_type = ACPI_TYPE_ANY;
	level = 1;

	/*
	 * Traverse the tree of nodes until we bubble back up to where we
	 * started. When Level is zero, the loop is करोne because we have
	 * bubbled up to (and passed) the original parent handle (start_entry)
	 */
	जबतक (level > 0 && child_node) अणु
		status = AE_OK;

		/* Found next child, get the type अगर we are not searching क्रम ANY */

		अगर (type != ACPI_TYPE_ANY) अणु
			child_type = child_node->type;
		पूर्ण

		/*
		 * Ignore all temporary namespace nodes (created during control
		 * method execution) unless told otherwise. These temporary nodes
		 * can cause a race condition because they can be deleted during
		 * the execution of the user function (अगर the namespace is
		 * unlocked beक्रमe invocation of the user function.) Only the
		 * debugger namespace dump will examine the temporary nodes.
		 */
		अगर ((child_node->flags & ANOBJ_TEMPORARY) &&
		    !(flags & ACPI_NS_WALK_TEMP_NODES)) अणु
			status = AE_CTRL_DEPTH;
		पूर्ण

		/* Type must match requested type */

		अन्यथा अगर (child_type == type) अणु
			/*
			 * Found a matching node, invoke the user callback function.
			 * Unlock the namespace अगर flag is set.
			 */
			अगर (flags & ACPI_NS_WALK_UNLOCK) अणु
				mutex_status =
				    acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
				अगर (ACPI_FAILURE(mutex_status)) अणु
					वापस_ACPI_STATUS(mutex_status);
				पूर्ण
			पूर्ण

			/*
			 * Invoke the user function, either descending, ascending,
			 * or both.
			 */
			अगर (!node_previously_visited) अणु
				अगर (descending_callback) अणु
					status =
					    descending_callback(child_node,
								level, context,
								वापस_value);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (ascending_callback) अणु
					status =
					    ascending_callback(child_node,
							       level, context,
							       वापस_value);
				पूर्ण
			पूर्ण

			अगर (flags & ACPI_NS_WALK_UNLOCK) अणु
				mutex_status =
				    acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
				अगर (ACPI_FAILURE(mutex_status)) अणु
					वापस_ACPI_STATUS(mutex_status);
				पूर्ण
			पूर्ण

			चयन (status) अणु
			हाल AE_OK:
			हाल AE_CTRL_DEPTH:

				/* Just keep going */
				अवरोध;

			हाल AE_CTRL_TERMINATE:

				/* Exit now, with OK status */

				वापस_ACPI_STATUS(AE_OK);

			शेष:

				/* All others are valid exceptions */

				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण

		/*
		 * Depth first search: Attempt to go करोwn another level in the
		 * namespace अगर we are allowed to. Don't go any further अगर we have
		 * reached the caller specअगरied maximum depth or अगर the user
		 * function has specअगरied that the maximum depth has been reached.
		 */
		अगर (!node_previously_visited &&
		    (level < max_depth) && (status != AE_CTRL_DEPTH)) अणु
			अगर (child_node->child) अणु

				/* There is at least one child of this node, visit it */

				level++;
				parent_node = child_node;
				child_node =
				    acpi_ns_get_next_node(parent_node, शून्य);
				जारी;
			पूर्ण
		पूर्ण

		/* No more children, re-visit this node */

		अगर (!node_previously_visited) अणु
			node_previously_visited = TRUE;
			जारी;
		पूर्ण

		/* No more children, visit peers */

		child_node = acpi_ns_get_next_node(parent_node, child_node);
		अगर (child_node) अणु
			node_previously_visited = FALSE;
		पूर्ण

		/* No peers, re-visit parent */

		अन्यथा अणु
			/*
			 * No more children of this node (acpi_ns_get_next_node failed), go
			 * back upwards in the namespace tree to the node's parent.
			 */
			level--;
			child_node = parent_node;
			parent_node = parent_node->parent;

			node_previously_visited = TRUE;
		पूर्ण
	पूर्ण

	/* Complete walk, not terminated by user function */

	वापस_ACPI_STATUS(AE_OK);
पूर्ण
