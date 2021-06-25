<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: nsaccess - Top-level functions क्रम accessing ACPI namespace
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acnamesp.h"
#समावेश "acdispat.h"

#अगर_घोषित ACPI_ASL_COMPILER
#समावेश "acdisasm.h"
#पूर्ण_अगर

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsaccess")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_root_initialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocate and initialize the शेष root named objects
 *
 * MUTEX:       Locks namespace क्रम entire execution
 *
 ******************************************************************************/
acpi_status acpi_ns_root_initialize(व्योम)
अणु
	acpi_status status;
	स्थिर काष्ठा acpi_predefined_names *init_val = शून्य;
	काष्ठा acpi_namespace_node *new_node;
	काष्ठा acpi_namespace_node *prev_node = शून्य;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_string val = शून्य;

	ACPI_FUNCTION_TRACE(ns_root_initialize);

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * The global root ptr is initially शून्य, so a non-शून्य value indicates
	 * that acpi_ns_root_initialize() has alपढ़ोy been called; just वापस.
	 */
	अगर (acpi_gbl_root_node) अणु
		status = AE_OK;
		जाओ unlock_and_निकास;
	पूर्ण

	/*
	 * Tell the rest of the subप्रणाली that the root is initialized
	 * (This is OK because the namespace is locked)
	 */
	acpi_gbl_root_node = &acpi_gbl_root_node_काष्ठा;

	/* Enter the predefined names in the name table */

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Entering predefined entries into namespace\n"));

	/*
	 * Create the initial (शेष) namespace.
	 * This namespace looks like something similar to this:
	 *
	 *   ACPI Namespace (from Namespace Root):
	 *    0  _GPE Scope        00203160 00
	 *    0  _PR_ Scope        002031D0 00
	 *    0  _SB_ Device       00203240 00 Notअगरy Object: 0020ADD8
	 *    0  _SI_ Scope        002032B0 00
	 *    0  _TZ_ Device       00203320 00
	 *    0  _REV Integer      00203390 00 = 0000000000000002
	 *    0  _OS_ String       00203488 00 Len 14 "Microsoft Windows NT"
	 *    0  _GL_ Mutex        00203580 00 Object 002035F0
	 *    0  _OSI Method       00203678 00 Args 1 Len 0000 Aml 00000000
	 */
	क्रम (init_val = acpi_gbl_pre_defined_names; init_val->name; init_val++) अणु
		status = AE_OK;

		/* _OSI is optional क्रम now, will be permanent later */

		अगर (!म_भेद(init_val->name, "_OSI")
		    && !acpi_gbl_create_osi_method) अणु
			जारी;
		पूर्ण

		/*
		 * Create, init, and link the new predefined name
		 * Note: No need to use acpi_ns_lookup here because all the
		 * predefined names are at the root level. It is much easier to
		 * just create and link the new node(s) here.
		 */
		new_node =
		    acpi_ns_create_node(*ACPI_CAST_PTR(u32, init_val->name));
		अगर (!new_node) अणु
			status = AE_NO_MEMORY;
			जाओ unlock_and_निकास;
		पूर्ण

		new_node->descriptor_type = ACPI_DESC_TYPE_NAMED;
		new_node->type = init_val->type;

		अगर (!prev_node) अणु
			acpi_gbl_root_node_काष्ठा.child = new_node;
		पूर्ण अन्यथा अणु
			prev_node->peer = new_node;
		पूर्ण

		new_node->parent = &acpi_gbl_root_node_काष्ठा;
		prev_node = new_node;

		/*
		 * Name entered successfully. If entry in pre_defined_names[] specअगरies
		 * an initial value, create the initial value.
		 */
		अगर (init_val->val) अणु
			status = acpi_os_predefined_override(init_val, &val);
			अगर (ACPI_FAILURE(status)) अणु
				ACPI_ERROR((AE_INFO,
					    "Could not override predefined %s",
					    init_val->name));
			पूर्ण

			अगर (!val) अणु
				val = init_val->val;
			पूर्ण

			/*
			 * Entry requests an initial value, allocate a
			 * descriptor क्रम it.
			 */
			obj_desc =
			    acpi_ut_create_पूर्णांकernal_object(init_val->type);
			अगर (!obj_desc) अणु
				status = AE_NO_MEMORY;
				जाओ unlock_and_निकास;
			पूर्ण

			/*
			 * Convert value string from table entry to
			 * पूर्णांकernal representation. Only types actually
			 * used क्रम initial values are implemented here.
			 */
			चयन (init_val->type) अणु
			हाल ACPI_TYPE_METHOD:

				obj_desc->method.param_count =
				    (u8) ACPI_TO_INTEGER(val);
				obj_desc->common.flags |= AOPOBJ_DATA_VALID;

#अगर defined (ACPI_ASL_COMPILER)

				/* Save the parameter count क्रम the iASL compiler */

				new_node->value = obj_desc->method.param_count;
#अन्यथा
				/* Mark this as a very SPECIAL method (_OSI) */

				obj_desc->method.info_flags =
				    ACPI_METHOD_INTERNAL_ONLY;
				obj_desc->method.dispatch.implementation =
				    acpi_ut_osi_implementation;
#पूर्ण_अगर
				अवरोध;

			हाल ACPI_TYPE_INTEGER:

				obj_desc->पूर्णांकeger.value = ACPI_TO_INTEGER(val);
				अवरोध;

			हाल ACPI_TYPE_STRING:

				/* Build an object around the अटल string */

				obj_desc->string.length = (u32)म_माप(val);
				obj_desc->string.poपूर्णांकer = val;
				obj_desc->common.flags |= AOPOBJ_STATIC_POINTER;
				अवरोध;

			हाल ACPI_TYPE_MUTEX:

				obj_desc->mutex.node = new_node;
				obj_desc->mutex.sync_level =
				    (u8) (ACPI_TO_INTEGER(val) - 1);

				/* Create a mutex */

				status =
				    acpi_os_create_mutex(&obj_desc->mutex.
							 os_mutex);
				अगर (ACPI_FAILURE(status)) अणु
					acpi_ut_हटाओ_reference(obj_desc);
					जाओ unlock_and_निकास;
				पूर्ण

				/* Special हाल क्रम ACPI Global Lock */

				अगर (म_भेद(init_val->name, "_GL_") == 0) अणु
					acpi_gbl_global_lock_mutex = obj_desc;

					/* Create additional counting semaphore क्रम global lock */

					status =
					    acpi_os_create_semaphore(1, 0,
								     &acpi_gbl_global_lock_semaphore);
					अगर (ACPI_FAILURE(status)) अणु
						acpi_ut_हटाओ_reference
						    (obj_desc);
						जाओ unlock_and_निकास;
					पूर्ण
				पूर्ण
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Unsupported initial type value 0x%X",
					    init_val->type));
				acpi_ut_हटाओ_reference(obj_desc);
				obj_desc = शून्य;
				जारी;
			पूर्ण

			/* Store poपूर्णांकer to value descriptor in the Node */

			status = acpi_ns_attach_object(new_node, obj_desc,
						       obj_desc->common.type);

			/* Remove local reference to the object */

			acpi_ut_हटाओ_reference(obj_desc);
		पूर्ण
	पूर्ण

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	/* Save a handle to "_GPE", it is always present */

	अगर (ACPI_SUCCESS(status)) अणु
		status = acpi_ns_get_node(शून्य, "\\_GPE", ACPI_NS_NO_UPSEARCH,
					  &acpi_gbl_fadt_gpe_device);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_lookup
 *
 * PARAMETERS:  scope_info      - Current scope info block
 *              pathname        - Search pathname, in पूर्णांकernal क्रमmat
 *                                (as represented in the AML stream)
 *              type            - Type associated with name
 *              पूर्णांकerpreter_mode - IMODE_LOAD_PASS2 => add name अगर not found
 *              flags           - Flags describing the search restrictions
 *              walk_state      - Current state of the walk
 *              वापस_node     - Where the Node is placed (अगर found
 *                                or created successfully)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find or enter the passed name in the name space.
 *              Log an error अगर name not found in Exec mode.
 *
 * MUTEX:       Assumes namespace is locked.
 *
 ******************************************************************************/

acpi_status
acpi_ns_lookup(जोड़ acpi_generic_state *scope_info,
	       अक्षर *pathname,
	       acpi_object_type type,
	       acpi_पूर्णांकerpreter_mode पूर्णांकerpreter_mode,
	       u32 flags,
	       काष्ठा acpi_walk_state *walk_state,
	       काष्ठा acpi_namespace_node **वापस_node)
अणु
	acpi_status status;
	अक्षर *path = pathname;
	अक्षर *बाह्यal_path;
	काष्ठा acpi_namespace_node *prefix_node;
	काष्ठा acpi_namespace_node *current_node = शून्य;
	काष्ठा acpi_namespace_node *this_node = शून्य;
	u32 num_segments;
	u32 num_carats;
	acpi_name simple_name;
	acpi_object_type type_to_check_क्रम;
	acpi_object_type this_search_type;
	u32 search_parent_flag = ACPI_NS_SEARCH_PARENT;
	u32 local_flags;
	acpi_पूर्णांकerpreter_mode local_पूर्णांकerpreter_mode;

	ACPI_FUNCTION_TRACE(ns_lookup);

	अगर (!वापस_node) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	local_flags = flags &
	    ~(ACPI_NS_ERROR_IF_FOUND | ACPI_NS_OVERRIDE_IF_FOUND |
	      ACPI_NS_SEARCH_PARENT);
	*वापस_node = ACPI_ENTRY_NOT_FOUND;
	acpi_gbl_ns_lookup_count++;

	अगर (!acpi_gbl_root_node) अणु
		वापस_ACPI_STATUS(AE_NO_NAMESPACE);
	पूर्ण

	/* Get the prefix scope. A null scope means use the root scope */

	अगर ((!scope_info) || (!scope_info->scope.node)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
				  "Null scope prefix, using root node (%p)\n",
				  acpi_gbl_root_node));

		prefix_node = acpi_gbl_root_node;
	पूर्ण अन्यथा अणु
		prefix_node = scope_info->scope.node;
		अगर (ACPI_GET_DESCRIPTOR_TYPE(prefix_node) !=
		    ACPI_DESC_TYPE_NAMED) अणु
			ACPI_ERROR((AE_INFO, "%p is not a namespace node [%s]",
				    prefix_node,
				    acpi_ut_get_descriptor_name(prefix_node)));
			वापस_ACPI_STATUS(AE_AML_INTERNAL);
		पूर्ण

		अगर (!(flags & ACPI_NS_PREFIX_IS_SCOPE)) अणु
			/*
			 * This node might not be a actual "scope" node (such as a
			 * Device/Method, etc.)  It could be a Package or other object
			 * node. Backup up the tree to find the containing scope node.
			 */
			जबतक (!acpi_ns_खोलोs_scope(prefix_node->type) &&
			       prefix_node->type != ACPI_TYPE_ANY) अणु
				prefix_node = prefix_node->parent;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Save type. TBD: may be no दीर्घer necessary */

	type_to_check_क्रम = type;

	/*
	 * Begin examination of the actual pathname
	 */
	अगर (!pathname) अणु

		/* A Null name_path is allowed and refers to the root */

		num_segments = 0;
		this_node = acpi_gbl_root_node;
		path = "";

		ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
				  "Null Pathname (Zero segments), Flags=%X\n",
				  flags));
	पूर्ण अन्यथा अणु
		/*
		 * Name poपूर्णांकer is valid (and must be in पूर्णांकernal name क्रमmat)
		 *
		 * Check क्रम scope prefixes:
		 *
		 * As represented in the AML stream, a namepath consists of an
		 * optional scope prefix followed by a name segment part.
		 *
		 * If present, the scope prefix is either a Root Prefix (in
		 * which हाल the name is fully qualअगरied), or one or more
		 * Parent Prefixes (in which हाल the name's scope is relative
		 * to the current scope).
		 */
		अगर (*path == (u8) AML_ROOT_PREFIX) अणु

			/* Pathname is fully qualअगरied, start from the root */

			this_node = acpi_gbl_root_node;
			search_parent_flag = ACPI_NS_NO_UPSEARCH;

			/* Poपूर्णांक to name segment part */

			path++;

			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Path is absolute from root [%p]\n",
					  this_node));
		पूर्ण अन्यथा अणु
			/* Pathname is relative to current scope, start there */

			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Searching relative to prefix scope [%4.4s] (%p)\n",
					  acpi_ut_get_node_name(prefix_node),
					  prefix_node));

			/*
			 * Handle multiple Parent Prefixes (carat) by just getting
			 * the parent node क्रम each prefix instance.
			 */
			this_node = prefix_node;
			num_carats = 0;
			जबतक (*path == (u8) AML_PARENT_PREFIX) अणु

				/* Name is fully qualअगरied, no search rules apply */

				search_parent_flag = ACPI_NS_NO_UPSEARCH;

				/*
				 * Poपूर्णांक past this prefix to the name segment
				 * part or the next Parent Prefix
				 */
				path++;

				/* Backup to the parent node */

				num_carats++;
				this_node = this_node->parent;
				अगर (!this_node) अणु
					/*
					 * Current scope has no parent scope. Externalize
					 * the पूर्णांकernal path क्रम error message.
					 */
					status =
					    acpi_ns_बाह्यalize_name
					    (ACPI_UINT32_MAX, pathname, शून्य,
					     &बाह्यal_path);
					अगर (ACPI_SUCCESS(status)) अणु
						ACPI_ERROR((AE_INFO,
							    "%s: Path has too many parent prefixes (^)",
							    बाह्यal_path));

						ACPI_FREE(बाह्यal_path);
					पूर्ण

					वापस_ACPI_STATUS(AE_NOT_FOUND);
				पूर्ण
			पूर्ण

			अगर (search_parent_flag == ACPI_NS_NO_UPSEARCH) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
						  "Search scope is [%4.4s], path has %u carat(s)\n",
						  acpi_ut_get_node_name
						  (this_node), num_carats));
			पूर्ण
		पूर्ण

		/*
		 * Determine the number of ACPI name segments in this pathname.
		 *
		 * The segment part consists of either:
		 *  - A Null name segment (0)
		 *  - A dual_name_prefix followed by two 4-byte name segments
		 *  - A multi_name_prefix followed by a byte indicating the
		 *      number of segments and the segments themselves.
		 *  - A single 4-byte name segment
		 *
		 * Examine the name prefix opcode, अगर any, to determine the number of
		 * segments.
		 */
		चयन (*path) अणु
		हाल 0:
			/*
			 * Null name after a root or parent prefixes. We alपढ़ोy
			 * have the correct target node and there are no name segments.
			 */
			num_segments = 0;
			type = this_node->type;

			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Prefix-only Pathname (Zero name segments), Flags=%X\n",
					  flags));
			अवरोध;

		हाल AML_DUAL_NAME_PREFIX:

			/* More than one name_seg, search rules करो not apply */

			search_parent_flag = ACPI_NS_NO_UPSEARCH;

			/* Two segments, poपूर्णांक to first name segment */

			num_segments = 2;
			path++;

			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Dual Pathname (2 segments, Flags=%X)\n",
					  flags));
			अवरोध;

		हाल AML_MULTI_NAME_PREFIX:

			/* More than one name_seg, search rules करो not apply */

			search_parent_flag = ACPI_NS_NO_UPSEARCH;

			/* Extract segment count, poपूर्णांक to first name segment */

			path++;
			num_segments = (u32) (u8) * path;
			path++;

			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Multi Pathname (%u Segments, Flags=%X)\n",
					  num_segments, flags));
			अवरोध;

		शेष:
			/*
			 * Not a Null name, no Dual or Multi prefix, hence there is
			 * only one name segment and Pathname is alपढ़ोy poपूर्णांकing to it.
			 */
			num_segments = 1;

			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Simple Pathname (1 segment, Flags=%X)\n",
					  flags));
			अवरोध;
		पूर्ण

		ACPI_DEBUG_EXEC(acpi_ns_prपूर्णांक_pathname(num_segments, path));
	पूर्ण

	/*
	 * Search namespace क्रम each segment of the name. Loop through and
	 * verअगरy (or add to the namespace) each name segment.
	 *
	 * The object type is signअगरicant only at the last name
	 * segment. (We करोn't care about the types aदीर्घ the path, only
	 * the type of the final target object.)
	 */
	this_search_type = ACPI_TYPE_ANY;
	current_node = this_node;

	जबतक (num_segments && current_node) अणु
		num_segments--;
		अगर (!num_segments) अणु

			/* This is the last segment, enable typechecking */

			this_search_type = type;

			/*
			 * Only allow स्वतःmatic parent search (search rules) अगर the caller
			 * requested it AND we have a single, non-fully-qualअगरied name_seg
			 */
			अगर ((search_parent_flag != ACPI_NS_NO_UPSEARCH) &&
			    (flags & ACPI_NS_SEARCH_PARENT)) अणु
				local_flags |= ACPI_NS_SEARCH_PARENT;
			पूर्ण

			/* Set error flag according to caller */

			अगर (flags & ACPI_NS_ERROR_IF_FOUND) अणु
				local_flags |= ACPI_NS_ERROR_IF_FOUND;
			पूर्ण

			/* Set override flag according to caller */

			अगर (flags & ACPI_NS_OVERRIDE_IF_FOUND) अणु
				local_flags |= ACPI_NS_OVERRIDE_IF_FOUND;
			पूर्ण
		पूर्ण

		/* Handle opcodes that create a new name_seg via a full name_path */

		local_पूर्णांकerpreter_mode = पूर्णांकerpreter_mode;
		अगर ((flags & ACPI_NS_PREFIX_MUST_EXIST) && (num_segments > 0)) अणु

			/* Every element of the path must exist (except क्रम the final name_seg) */

			local_पूर्णांकerpreter_mode = ACPI_IMODE_EXECUTE;
		पूर्ण

		/* Extract one ACPI name from the front of the pathname */

		ACPI_MOVE_32_TO_32(&simple_name, path);

		/* Try to find the single (4 अक्षरacter) ACPI name */

		status =
		    acpi_ns_search_and_enter(simple_name, walk_state,
					     current_node,
					     local_पूर्णांकerpreter_mode,
					     this_search_type, local_flags,
					     &this_node);
		अगर (ACPI_FAILURE(status)) अणु
			अगर (status == AE_NOT_FOUND) अणु
#अगर !defined ACPI_ASL_COMPILER	/* Note: iASL reports this error by itself, not needed here */
				अगर (flags & ACPI_NS_PREFIX_MUST_EXIST) अणु
					acpi_os_म_लिखो(ACPI_MSG_BIOS_ERROR
						       "Object does not exist: %4.4s\n",
						       (अक्षर *)&simple_name);
				पूर्ण
#पूर्ण_अगर
				/* Name not found in ACPI namespace */

				ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
						  "Name [%4.4s] not found in scope [%4.4s] %p\n",
						  (अक्षर *)&simple_name,
						  (अक्षर *)&current_node->name,
						  current_node));
			पूर्ण
#अगर_घोषित ACPI_EXEC_APP
			अगर ((status == AE_ALREADY_EXISTS) &&
			    (this_node->flags & ANOBJ_NODE_EARLY_INIT)) अणु
				this_node->flags &= ~ANOBJ_NODE_EARLY_INIT;
				status = AE_OK;
			पूर्ण
#पूर्ण_अगर

#अगर_घोषित ACPI_ASL_COMPILER
			/*
			 * If this ACPI name alपढ़ोy exists within the namespace as an
			 * बाह्यal declaration, then mark the बाह्यal as a conflicting
			 * declaration and proceed to process the current node as अगर it did
			 * not exist in the namespace. If this node is not processed as
			 * normal, then it could cause improper namespace resolution
			 * by failing to खोलो a new scope.
			 */
			अगर (acpi_gbl_disयंत्र_flag &&
			    (status == AE_ALREADY_EXISTS) &&
			    ((this_node->flags & ANOBJ_IS_EXTERNAL) ||
			     (walk_state
			      && walk_state->opcode == AML_EXTERNAL_OP))) अणु
				this_node->flags &= ~ANOBJ_IS_EXTERNAL;
				this_node->type = (u8)this_search_type;
				अगर (walk_state->opcode != AML_EXTERNAL_OP) अणु
					acpi_dm_mark_बाह्यal_conflict
					    (this_node);
				पूर्ण
				अवरोध;
			पूर्ण
#पूर्ण_अगर

			*वापस_node = this_node;
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* More segments to follow? */

		अगर (num_segments > 0) अणु
			/*
			 * If we have an alias to an object that खोलोs a scope (such as a
			 * device or processor), we need to dereference the alias here so
			 * that we can access any children of the original node (via the
			 * reमुख्यing segments).
			 */
			अगर (this_node->type == ACPI_TYPE_LOCAL_ALIAS) अणु
				अगर (!this_node->object) अणु
					वापस_ACPI_STATUS(AE_NOT_EXIST);
				पूर्ण

				अगर (acpi_ns_खोलोs_scope
				    (((काष्ठा acpi_namespace_node *)
				      this_node->object)->type)) अणु
					this_node =
					    (काष्ठा acpi_namespace_node *)
					    this_node->object;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Special handling क्रम the last segment (num_segments == 0) */

		अन्यथा अणु
			/*
			 * Sanity typecheck of the target object:
			 *
			 * If 1) This is the last segment (num_segments == 0)
			 *    2) And we are looking क्रम a specअगरic type
			 *       (Not checking क्रम TYPE_ANY)
			 *    3) Which is not an alias
			 *    4) Which is not a local type (TYPE_SCOPE)
			 *    5) And the type of target object is known (not TYPE_ANY)
			 *    6) And target object करोes not match what we are looking क्रम
			 *
			 * Then we have a type mismatch. Just warn and ignore it.
			 */
			अगर ((type_to_check_क्रम != ACPI_TYPE_ANY) &&
			    (type_to_check_क्रम != ACPI_TYPE_LOCAL_ALIAS) &&
			    (type_to_check_क्रम != ACPI_TYPE_LOCAL_METHOD_ALIAS)
			    && (type_to_check_क्रम != ACPI_TYPE_LOCAL_SCOPE)
			    && (this_node->type != ACPI_TYPE_ANY)
			    && (this_node->type != type_to_check_क्रम)) अणु

				/* Complain about a type mismatch */

				ACPI_WARNING((AE_INFO,
					      "NsLookup: Type mismatch on %4.4s (%s), searching for (%s)",
					      ACPI_CAST_PTR(अक्षर, &simple_name),
					      acpi_ut_get_type_name(this_node->
								    type),
					      acpi_ut_get_type_name
					      (type_to_check_क्रम)));
			पूर्ण

			/*
			 * If this is the last name segment and we are not looking क्रम a
			 * specअगरic type, but the type of found object is known, use that
			 * type to (later) see अगर it खोलोs a scope.
			 */
			अगर (type == ACPI_TYPE_ANY) अणु
				type = this_node->type;
			पूर्ण
		पूर्ण

		/* Poपूर्णांक to next name segment and make this node current */

		path += ACPI_NAMESEG_SIZE;
		current_node = this_node;
	पूर्ण

	/* Always check अगर we need to खोलो a new scope */

	अगर (!(flags & ACPI_NS_DONT_OPEN_SCOPE) && (walk_state)) अणु
		/*
		 * If entry is a type which खोलोs a scope, push the new scope on the
		 * scope stack.
		 */
		अगर (acpi_ns_खोलोs_scope(type)) अणु
			status =
			    acpi_ds_scope_stack_push(this_node, type,
						     walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण
	पूर्ण
#अगर_घोषित ACPI_EXEC_APP
	अगर (flags & ACPI_NS_EARLY_INIT) अणु
		this_node->flags |= ANOBJ_NODE_EARLY_INIT;
	पूर्ण
#पूर्ण_अगर

	*वापस_node = this_node;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
