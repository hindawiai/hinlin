<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: nssearch - Namespace search
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#अगर_घोषित ACPI_ASL_COMPILER
#समावेश "amlcode.h"
#पूर्ण_अगर

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nssearch")

/* Local prototypes */
अटल acpi_status
acpi_ns_search_parent_tree(u32 target_name,
			   काष्ठा acpi_namespace_node *node,
			   acpi_object_type type,
			   काष्ठा acpi_namespace_node **वापस_node);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_search_one_scope
 *
 * PARAMETERS:  target_name     - Ascii ACPI name to search क्रम
 *              parent_node     - Starting node where search will begin
 *              type            - Object type to match
 *              वापस_node     - Where the matched Named obj is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Search a single level of the namespace. Perक्रमms a
 *              simple search of the specअगरied level, and करोes not add
 *              entries or search parents.
 *
 *
 *      Named object lists are built (and subsequently dumped) in the
 *      order in which the names are encountered during the namespace load;
 *
 *      All namespace searching is linear in this implementation, but
 *      could be easily modअगरied to support any improved search
 *      algorithm. However, the linear search was chosen क्रम simplicity
 *      and because the trees are small and the other पूर्णांकerpreter
 *      execution overhead is relatively high.
 *
 *      Note: CPU execution analysis has shown that the AML पूर्णांकerpreter spends
 *      a very small percentage of its समय searching the namespace. Thereक्रमe,
 *      the linear search seems to be sufficient, as there would seem to be
 *      little value in improving the search.
 *
 ******************************************************************************/

acpi_status
acpi_ns_search_one_scope(u32 target_name,
			 काष्ठा acpi_namespace_node *parent_node,
			 acpi_object_type type,
			 काष्ठा acpi_namespace_node **वापस_node)
अणु
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(ns_search_one_scope);

#अगर_घोषित ACPI_DEBUG_OUTPUT
	अगर (ACPI_LV_NAMES & acpi_dbg_level) अणु
		अक्षर *scope_name;

		scope_name = acpi_ns_get_normalized_pathname(parent_node, TRUE);
		अगर (scope_name) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Searching %s (%p) For [%4.4s] (%s)\n",
					  scope_name, parent_node,
					  ACPI_CAST_PTR(अक्षर, &target_name),
					  acpi_ut_get_type_name(type)));

			ACPI_FREE(scope_name);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * Search क्रम name at this namespace level, which is to say that we
	 * must search क्रम the name among the children of this object
	 */
	node = parent_node->child;
	जबतक (node) अणु

		/* Check क्रम match against the name */

		अगर (node->name.पूर्णांकeger == target_name) अणु

			/* Resolve a control method alias अगर any */

			अगर (acpi_ns_get_type(node) ==
			    ACPI_TYPE_LOCAL_METHOD_ALIAS) अणु
				node =
				    ACPI_CAST_PTR(काष्ठा acpi_namespace_node,
						  node->object);
			पूर्ण

			/* Found matching entry */

			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Name [%4.4s] (%s) %p found in scope [%4.4s] %p\n",
					  ACPI_CAST_PTR(अक्षर, &target_name),
					  acpi_ut_get_type_name(node->type),
					  node,
					  acpi_ut_get_node_name(parent_node),
					  parent_node));

			*वापस_node = node;
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		/* Didn't match name, move on to the next peer object */

		node = node->peer;
	पूर्ण

	/* Searched entire namespace level, not found */

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
			  "Name [%4.4s] (%s) not found in search in scope [%4.4s] "
			  "%p first child %p\n",
			  ACPI_CAST_PTR(अक्षर, &target_name),
			  acpi_ut_get_type_name(type),
			  acpi_ut_get_node_name(parent_node), parent_node,
			  parent_node->child));

	वापस_ACPI_STATUS(AE_NOT_FOUND);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_search_parent_tree
 *
 * PARAMETERS:  target_name     - Ascii ACPI name to search क्रम
 *              node            - Starting node where search will begin
 *              type            - Object type to match
 *              वापस_node     - Where the matched Node is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Called when a name has not been found in the current namespace
 *              level. Beक्रमe adding it or giving up, ACPI scope rules require
 *              searching enclosing scopes in हालs identअगरied by acpi_ns_local().
 *
 *              "A name is located by finding the matching name in the current
 *              name space, and then in the parent name space. If the parent
 *              name space करोes not contain the name, the search जारीs
 *              recursively until either the name is found or the name space
 *              करोes not have a parent (the root of the name space). This
 *              indicates that the name is not found" (From ACPI Specअगरication,
 *              section 5.3)
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_search_parent_tree(u32 target_name,
			   काष्ठा acpi_namespace_node *node,
			   acpi_object_type type,
			   काष्ठा acpi_namespace_node **वापस_node)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *parent_node;

	ACPI_FUNCTION_TRACE(ns_search_parent_tree);

	parent_node = node->parent;

	/*
	 * If there is no parent (i.e., we are at the root) or type is "local",
	 * we won't be searching the parent tree.
	 */
	अगर (!parent_node) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_NAMES, "[%4.4s] has no parent\n",
				  ACPI_CAST_PTR(अक्षर, &target_name)));
		वापस_ACPI_STATUS(AE_NOT_FOUND);
	पूर्ण

	अगर (acpi_ns_local(type)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
				  "[%4.4s] type [%s] must be local to this scope (no parent search)\n",
				  ACPI_CAST_PTR(अक्षर, &target_name),
				  acpi_ut_get_type_name(type)));
		वापस_ACPI_STATUS(AE_NOT_FOUND);
	पूर्ण

	/* Search the parent tree */

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
			  "Searching parent [%4.4s] for [%4.4s]\n",
			  acpi_ut_get_node_name(parent_node),
			  ACPI_CAST_PTR(अक्षर, &target_name)));

	/* Search parents until target is found or we have backed up to the root */

	जबतक (parent_node) अणु
		/*
		 * Search parent scope. Use TYPE_ANY because we करोn't care about the
		 * object type at this poपूर्णांक, we only care about the existence of
		 * the actual name we are searching क्रम. Typechecking comes later.
		 */
		status =
		    acpi_ns_search_one_scope(target_name, parent_node,
					     ACPI_TYPE_ANY, वापस_node);
		अगर (ACPI_SUCCESS(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Not found here, go up another level (until we reach the root) */

		parent_node = parent_node->parent;
	पूर्ण

	/* Not found in parent tree */

	वापस_ACPI_STATUS(AE_NOT_FOUND);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_search_and_enter
 *
 * PARAMETERS:  target_name         - Ascii ACPI name to search क्रम (4 अक्षरs)
 *              walk_state          - Current state of the walk
 *              node                - Starting node where search will begin
 *              पूर्णांकerpreter_mode    - Add names only in ACPI_MODE_LOAD_PASS_x.
 *                                    Otherwise,search only.
 *              type                - Object type to match
 *              flags               - Flags describing the search restrictions
 *              वापस_node         - Where the Node is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Search क्रम a name segment in a single namespace level,
 *              optionally adding it अगर it is not found. If the passed
 *              Type is not Any and the type previously stored in the
 *              entry was Any (i.e. unknown), update the stored type.
 *
 *              In ACPI_IMODE_EXECUTE, search only.
 *              In other modes, search and add अगर not found.
 *
 ******************************************************************************/

acpi_status
acpi_ns_search_and_enter(u32 target_name,
			 काष्ठा acpi_walk_state *walk_state,
			 काष्ठा acpi_namespace_node *node,
			 acpi_पूर्णांकerpreter_mode पूर्णांकerpreter_mode,
			 acpi_object_type type,
			 u32 flags, काष्ठा acpi_namespace_node **वापस_node)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *new_node;

	ACPI_FUNCTION_TRACE(ns_search_and_enter);

	/* Parameter validation */

	अगर (!node || !target_name || !वापस_node) अणु
		ACPI_ERROR((AE_INFO,
			    "Null parameter: Node %p Name 0x%X ReturnNode %p",
			    node, target_name, वापस_node));
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Name must consist of valid ACPI अक्षरacters. We will repair the name अगर
	 * necessary because we करोn't want to पात because of this, but we want
	 * all namespace names to be prपूर्णांकable. A warning message is appropriate.
	 *
	 * This issue came up because there are in fact machines that exhibit
	 * this problem, and we want to be able to enable ACPI support क्रम them,
	 * even though there are a few bad names.
	 */
	acpi_ut_repair_name(ACPI_CAST_PTR(अक्षर, &target_name));

	/* Try to find the name in the namespace level specअगरied by the caller */

	*वापस_node = ACPI_ENTRY_NOT_FOUND;
	status = acpi_ns_search_one_scope(target_name, node, type, वापस_node);
	अगर (status != AE_NOT_FOUND) अणु
		/*
		 * If we found it AND the request specअगरies that a find is an error,
		 * वापस the error
		 */
		अगर (status == AE_OK) अणु

			/* The node was found in the namespace */

			/*
			 * If the namespace override feature is enabled क्रम this node,
			 * delete any existing attached sub-object and make the node
			 * look like a new node that is owned by the override table.
			 */
			अगर (flags & ACPI_NS_OVERRIDE_IF_FOUND) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
						  "Namespace override: %4.4s pass %u type %X Owner %X\n",
						  ACPI_CAST_PTR(अक्षर,
								&target_name),
						  पूर्णांकerpreter_mode,
						  (*वापस_node)->type,
						  walk_state->owner_id));

				acpi_ns_delete_children(*वापस_node);
				अगर (acpi_gbl_runसमय_namespace_override) अणु
					acpi_ut_हटाओ_reference((*वापस_node)->object);
					(*वापस_node)->object = शून्य;
					(*वापस_node)->owner_id =
					    walk_state->owner_id;
				पूर्ण अन्यथा अणु
					acpi_ns_हटाओ_node(*वापस_node);
					*वापस_node = ACPI_ENTRY_NOT_FOUND;
				पूर्ण
			पूर्ण

			/* Return an error अगर we करोn't expect to find the object */

			अन्यथा अगर (flags & ACPI_NS_ERROR_IF_FOUND) अणु
				status = AE_ALREADY_EXISTS;
			पूर्ण
		पूर्ण
#अगर_घोषित ACPI_ASL_COMPILER
		अगर (*वापस_node && (*वापस_node)->type == ACPI_TYPE_ANY) अणु
			(*वापस_node)->flags |= ANOBJ_IS_EXTERNAL;
		पूर्ण
#पूर्ण_अगर

		/* Either found it or there was an error: finished either way */

		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * The name was not found. If we are NOT perक्रमming the first pass
	 * (name entry) of loading the namespace, search the parent tree (all the
	 * way to the root अगर necessary.) We करोn't want to perक्रमm the parent
	 * search when the namespace is actually being loaded. We want to perक्रमm
	 * the search when namespace references are being resolved (load pass 2)
	 * and during the execution phase.
	 */
	अगर ((पूर्णांकerpreter_mode != ACPI_IMODE_LOAD_PASS1) &&
	    (flags & ACPI_NS_SEARCH_PARENT)) अणु
		/*
		 * Not found at this level - search parent tree according to the
		 * ACPI specअगरication
		 */
		status =
		    acpi_ns_search_parent_tree(target_name, node, type,
					       वापस_node);
		अगर (ACPI_SUCCESS(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/* In execute mode, just search, never add names. Exit now */

	अगर (पूर्णांकerpreter_mode == ACPI_IMODE_EXECUTE) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
				  "%4.4s Not found in %p [Not adding]\n",
				  ACPI_CAST_PTR(अक्षर, &target_name), node));

		वापस_ACPI_STATUS(AE_NOT_FOUND);
	पूर्ण

	/* Create the new named object */

	new_node = acpi_ns_create_node(target_name);
	अगर (!new_node) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण
#अगर_घोषित ACPI_ASL_COMPILER

	/* Node is an object defined by an External() statement */

	अगर (flags & ACPI_NS_EXTERNAL ||
	    (walk_state && walk_state->opcode == AML_SCOPE_OP)) अणु
		new_node->flags |= ANOBJ_IS_EXTERNAL;
	पूर्ण
#पूर्ण_अगर

	अगर (flags & ACPI_NS_TEMPORARY) अणु
		new_node->flags |= ANOBJ_TEMPORARY;
	पूर्ण

	/* Install the new object पूर्णांकo the parent's list of children */

	acpi_ns_install_node(walk_state, node, new_node, type);
	*वापस_node = new_node;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
