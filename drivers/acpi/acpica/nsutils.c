<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsutils - Utilities क्रम accessing ACPI namespace, accessing
 *                        parents and siblings and Scope manipulation
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsutils")

/* Local prototypes */
#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
acpi_name acpi_ns_find_parent_name(काष्ठा acpi_namespace_node *node_to_search);
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_prपूर्णांक_node_pathname
 *
 * PARAMETERS:  node            - Object
 *              message         - Prefix message
 *
 * DESCRIPTION: Prपूर्णांक an object's full namespace pathname
 *              Manages allocation/मुक्तing of a pathname buffer
 *
 ******************************************************************************/

व्योम
acpi_ns_prपूर्णांक_node_pathname(काष्ठा acpi_namespace_node *node,
			    स्थिर अक्षर *message)
अणु
	काष्ठा acpi_buffer buffer;
	acpi_status status;

	अगर (!node) अणु
		acpi_os_म_लिखो("[NULL NAME]");
		वापस;
	पूर्ण

	/* Convert handle to full pathname and prपूर्णांक it (with supplied message) */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;

	status = acpi_ns_handle_to_pathname(node, &buffer, TRUE);
	अगर (ACPI_SUCCESS(status)) अणु
		अगर (message) अणु
			acpi_os_म_लिखो("%s ", message);
		पूर्ण

		acpi_os_म_लिखो("%s", (अक्षर *)buffer.poपूर्णांकer);
		ACPI_FREE(buffer.poपूर्णांकer);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_type
 *
 * PARAMETERS:  node        - Parent Node to be examined
 *
 * RETURN:      Type field from Node whose handle is passed
 *
 * DESCRIPTION: Return the type of a Namespace node
 *
 ******************************************************************************/

acpi_object_type acpi_ns_get_type(काष्ठा acpi_namespace_node * node)
अणु
	ACPI_FUNCTION_TRACE(ns_get_type);

	अगर (!node) अणु
		ACPI_WARNING((AE_INFO, "Null Node parameter"));
		वापस_UINT8(ACPI_TYPE_ANY);
	पूर्ण

	वापस_UINT8(node->type);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_local
 *
 * PARAMETERS:  type        - A namespace object type
 *
 * RETURN:      LOCAL अगर names must be found locally in objects of the
 *              passed type, 0 अगर enclosing scopes should be searched
 *
 * DESCRIPTION: Returns scope rule क्रम the given object type.
 *
 ******************************************************************************/

u32 acpi_ns_local(acpi_object_type type)
अणु
	ACPI_FUNCTION_TRACE(ns_local);

	अगर (!acpi_ut_valid_object_type(type)) अणु

		/* Type code out of range  */

		ACPI_WARNING((AE_INFO, "Invalid Object Type 0x%X", type));
		वापस_UINT32(ACPI_NS_NORMAL);
	पूर्ण

	वापस_UINT32(acpi_gbl_ns_properties[type] & ACPI_NS_LOCAL);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_पूर्णांकernal_name_length
 *
 * PARAMETERS:  info            - Info काष्ठा initialized with the
 *                                बाह्यal name poपूर्णांकer.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Calculate the length of the पूर्णांकernal (AML) namestring
 *              corresponding to the बाह्यal (ASL) namestring.
 *
 ******************************************************************************/

व्योम acpi_ns_get_पूर्णांकernal_name_length(काष्ठा acpi_namestring_info *info)
अणु
	स्थिर अक्षर *next_बाह्यal_अक्षर;
	u32 i;

	ACPI_FUNCTION_ENTRY();

	next_बाह्यal_अक्षर = info->बाह्यal_name;
	info->num_carats = 0;
	info->num_segments = 0;
	info->fully_qualअगरied = FALSE;

	/*
	 * For the पूर्णांकernal name, the required length is 4 bytes per segment,
	 * plus 1 each क्रम root_prefix, multi_name_prefix_op, segment count,
	 * trailing null (which is not really needed, but no there's harm in
	 * putting it there)
	 *
	 * म_माप() + 1 covers the first name_seg, which has no path separator
	 */
	अगर (ACPI_IS_ROOT_PREFIX(*next_बाह्यal_अक्षर)) अणु
		info->fully_qualअगरied = TRUE;
		next_बाह्यal_अक्षर++;

		/* Skip redundant root_prefix, like \\_SB.PCI0.SBRG.EC0 */

		जबतक (ACPI_IS_ROOT_PREFIX(*next_बाह्यal_अक्षर)) अणु
			next_बाह्यal_अक्षर++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Handle Carat prefixes */

		जबतक (ACPI_IS_PARENT_PREFIX(*next_बाह्यal_अक्षर)) अणु
			info->num_carats++;
			next_बाह्यal_अक्षर++;
		पूर्ण
	पूर्ण

	/*
	 * Determine the number of ACPI name "segments" by counting the number of
	 * path separators within the string. Start with one segment since the
	 * segment count is [(# separators) + 1], and zero separators is ok.
	 */
	अगर (*next_बाह्यal_अक्षर) अणु
		info->num_segments = 1;
		क्रम (i = 0; next_बाह्यal_अक्षर[i]; i++) अणु
			अगर (ACPI_IS_PATH_SEPARATOR(next_बाह्यal_अक्षर[i])) अणु
				info->num_segments++;
			पूर्ण
		पूर्ण
	पूर्ण

	info->length = (ACPI_NAMESEG_SIZE * info->num_segments) +
	    4 + info->num_carats;

	info->next_बाह्यal_अक्षर = next_बाह्यal_अक्षर;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_build_पूर्णांकernal_name
 *
 * PARAMETERS:  info            - Info काष्ठा fully initialized
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Conकाष्ठा the पूर्णांकernal (AML) namestring
 *              corresponding to the बाह्यal (ASL) namestring.
 *
 ******************************************************************************/

acpi_status acpi_ns_build_पूर्णांकernal_name(काष्ठा acpi_namestring_info *info)
अणु
	u32 num_segments = info->num_segments;
	अक्षर *पूर्णांकernal_name = info->पूर्णांकernal_name;
	स्थिर अक्षर *बाह्यal_name = info->next_बाह्यal_अक्षर;
	अक्षर *result = शून्य;
	u32 i;

	ACPI_FUNCTION_TRACE(ns_build_पूर्णांकernal_name);

	/* Setup the correct prefixes, counts, and poपूर्णांकers */

	अगर (info->fully_qualअगरied) अणु
		पूर्णांकernal_name[0] = AML_ROOT_PREFIX;

		अगर (num_segments <= 1) अणु
			result = &पूर्णांकernal_name[1];
		पूर्ण अन्यथा अगर (num_segments == 2) अणु
			पूर्णांकernal_name[1] = AML_DUAL_NAME_PREFIX;
			result = &पूर्णांकernal_name[2];
		पूर्ण अन्यथा अणु
			पूर्णांकernal_name[1] = AML_MULTI_NAME_PREFIX;
			पूर्णांकernal_name[2] = (अक्षर)num_segments;
			result = &पूर्णांकernal_name[3];
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Not fully qualअगरied.
		 * Handle Carats first, then append the name segments
		 */
		i = 0;
		अगर (info->num_carats) अणु
			क्रम (i = 0; i < info->num_carats; i++) अणु
				पूर्णांकernal_name[i] = AML_PARENT_PREFIX;
			पूर्ण
		पूर्ण

		अगर (num_segments <= 1) अणु
			result = &पूर्णांकernal_name[i];
		पूर्ण अन्यथा अगर (num_segments == 2) अणु
			पूर्णांकernal_name[i] = AML_DUAL_NAME_PREFIX;
			result = &पूर्णांकernal_name[(acpi_size)i + 1];
		पूर्ण अन्यथा अणु
			पूर्णांकernal_name[i] = AML_MULTI_NAME_PREFIX;
			पूर्णांकernal_name[(acpi_size)i + 1] = (अक्षर)num_segments;
			result = &पूर्णांकernal_name[(acpi_size)i + 2];
		पूर्ण
	पूर्ण

	/* Build the name (minus path separators) */

	क्रम (; num_segments; num_segments--) अणु
		क्रम (i = 0; i < ACPI_NAMESEG_SIZE; i++) अणु
			अगर (ACPI_IS_PATH_SEPARATOR(*बाह्यal_name) ||
			    (*बाह्यal_name == 0)) अणु

				/* Pad the segment with underscore(s) अगर segment is लघु */

				result[i] = '_';
			पूर्ण अन्यथा अणु
				/* Convert the अक्षरacter to upperहाल and save it */

				result[i] = (अक्षर)बड़े((पूर्णांक)*बाह्यal_name);
				बाह्यal_name++;
			पूर्ण
		पूर्ण

		/* Now we must have a path separator, or the pathname is bad */

		अगर (!ACPI_IS_PATH_SEPARATOR(*बाह्यal_name) &&
		    (*बाह्यal_name != 0)) अणु
			वापस_ACPI_STATUS(AE_BAD_PATHNAME);
		पूर्ण

		/* Move on the next segment */

		बाह्यal_name++;
		result += ACPI_NAMESEG_SIZE;
	पूर्ण

	/* Terminate the string */

	*result = 0;

	अगर (info->fully_qualअगरied) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Returning [%p] (abs) \"\\%s\"\n",
				  पूर्णांकernal_name, पूर्णांकernal_name));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Returning [%p] (rel) \"%s\"\n",
				  पूर्णांकernal_name, पूर्णांकernal_name));
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_पूर्णांकernalize_name
 *
 * PARAMETERS:  *बाह्यal_name          - External representation of name
 *              **Converted name        - Where to वापस the resulting
 *                                        पूर्णांकernal represention of the name
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an बाह्यal representation (e.g. "\_PR_.CPU0")
 *              to पूर्णांकernal क्रमm (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *
 *******************************************************************************/

acpi_status
acpi_ns_पूर्णांकernalize_name(स्थिर अक्षर *बाह्यal_name, अक्षर **converted_name)
अणु
	अक्षर *पूर्णांकernal_name;
	काष्ठा acpi_namestring_info info;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_पूर्णांकernalize_name);

	अगर ((!बाह्यal_name) || (*बाह्यal_name == 0) || (!converted_name)) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Get the length of the new पूर्णांकernal name */

	info.बाह्यal_name = बाह्यal_name;
	acpi_ns_get_पूर्णांकernal_name_length(&info);

	/* We need a segment to store the पूर्णांकernal  name */

	पूर्णांकernal_name = ACPI_ALLOCATE_ZEROED(info.length);
	अगर (!पूर्णांकernal_name) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Build the name */

	info.पूर्णांकernal_name = पूर्णांकernal_name;
	status = acpi_ns_build_पूर्णांकernal_name(&info);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(पूर्णांकernal_name);
		वापस_ACPI_STATUS(status);
	पूर्ण

	*converted_name = पूर्णांकernal_name;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_बाह्यalize_name
 *
 * PARAMETERS:  पूर्णांकernal_name_length - Length of the पूर्णांकernal name below
 *              पूर्णांकernal_name       - Internal representation of name
 *              converted_name_length - Where the length is वापसed
 *              converted_name      - Where the resulting बाह्यal name
 *                                    is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert पूर्णांकernal name (e.g. 5c 2f 02 5f 50 52 5f 43 50 55 30)
 *              to its बाह्यal (prपूर्णांकable) क्रमm (e.g. "\_PR_.CPU0")
 *
 ******************************************************************************/

acpi_status
acpi_ns_बाह्यalize_name(u32 पूर्णांकernal_name_length,
			 स्थिर अक्षर *पूर्णांकernal_name,
			 u32 * converted_name_length, अक्षर **converted_name)
अणु
	u32 names_index = 0;
	u32 num_segments = 0;
	u32 required_length;
	u32 prefix_length = 0;
	u32 i = 0;
	u32 j = 0;

	ACPI_FUNCTION_TRACE(ns_बाह्यalize_name);

	अगर (!पूर्णांकernal_name_length || !पूर्णांकernal_name || !converted_name) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Check क्रम a prefix (one '\' | one or more '^') */

	चयन (पूर्णांकernal_name[0]) अणु
	हाल AML_ROOT_PREFIX:

		prefix_length = 1;
		अवरोध;

	हाल AML_PARENT_PREFIX:

		क्रम (i = 0; i < पूर्णांकernal_name_length; i++) अणु
			अगर (ACPI_IS_PARENT_PREFIX(पूर्णांकernal_name[i])) अणु
				prefix_length = i + 1;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == पूर्णांकernal_name_length) अणु
			prefix_length = i;
		पूर्ण

		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	/*
	 * Check क्रम object names. Note that there could be 0-255 of these
	 * 4-byte elements.
	 */
	अगर (prefix_length < पूर्णांकernal_name_length) अणु
		चयन (पूर्णांकernal_name[prefix_length]) अणु
		हाल AML_MULTI_NAME_PREFIX:

			/* <count> 4-byte names */

			names_index = prefix_length + 2;
			num_segments = (u8)
			    पूर्णांकernal_name[(acpi_size)prefix_length + 1];
			अवरोध;

		हाल AML_DUAL_NAME_PREFIX:

			/* Two 4-byte names */

			names_index = prefix_length + 1;
			num_segments = 2;
			अवरोध;

		हाल 0:

			/* null_name */

			names_index = 0;
			num_segments = 0;
			अवरोध;

		शेष:

			/* one 4-byte name */

			names_index = prefix_length;
			num_segments = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Calculate the length of converted_name, which equals the length
	 * of the prefix, length of all object names, length of any required
	 * punctuation ('.') between object names, plus the शून्य terminator.
	 */
	required_length = prefix_length + (4 * num_segments) +
	    ((num_segments > 0) ? (num_segments - 1) : 0) + 1;

	/*
	 * Check to see अगर we're still in bounds. If not, there's a problem
	 * with पूर्णांकernal_name (invalid क्रमmat).
	 */
	अगर (required_length > पूर्णांकernal_name_length) अणु
		ACPI_ERROR((AE_INFO, "Invalid internal name"));
		वापस_ACPI_STATUS(AE_BAD_PATHNAME);
	पूर्ण

	/* Build the converted_name */

	*converted_name = ACPI_ALLOCATE_ZEROED(required_length);
	अगर (!(*converted_name)) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	j = 0;

	क्रम (i = 0; i < prefix_length; i++) अणु
		(*converted_name)[j++] = पूर्णांकernal_name[i];
	पूर्ण

	अगर (num_segments > 0) अणु
		क्रम (i = 0; i < num_segments; i++) अणु
			अगर (i > 0) अणु
				(*converted_name)[j++] = '.';
			पूर्ण

			/* Copy and validate the 4-अक्षर name segment */

			ACPI_COPY_NAMESEG(&(*converted_name)[j],
					  &पूर्णांकernal_name[names_index]);
			acpi_ut_repair_name(&(*converted_name)[j]);

			j += ACPI_NAMESEG_SIZE;
			names_index += ACPI_NAMESEG_SIZE;
		पूर्ण
	पूर्ण

	अगर (converted_name_length) अणु
		*converted_name_length = (u32) required_length;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_validate_handle
 *
 * PARAMETERS:  handle          - Handle to be validated and typecast to a
 *                                namespace node.
 *
 * RETURN:      A poपूर्णांकer to a namespace node
 *
 * DESCRIPTION: Convert a namespace handle to a namespace node. Handles special
 *              हालs क्रम the root node.
 *
 * NOTE: Real पूर्णांकeger handles would allow क्रम more verअगरication
 *       and keep all poपूर्णांकers within this subप्रणाली - however this पूर्णांकroduces
 *       more overhead and has not been necessary to this poपूर्णांक. Drivers
 *       holding handles are typically notअगरied beक्रमe a node becomes invalid
 *       due to a table unload.
 *
 ******************************************************************************/

काष्ठा acpi_namespace_node *acpi_ns_validate_handle(acpi_handle handle)
अणु

	ACPI_FUNCTION_ENTRY();

	/* Parameter validation */

	अगर ((!handle) || (handle == ACPI_ROOT_OBJECT)) अणु
		वापस (acpi_gbl_root_node);
	पूर्ण

	/* We can at least attempt to verअगरy the handle */

	अगर (ACPI_GET_DESCRIPTOR_TYPE(handle) != ACPI_DESC_TYPE_NAMED) अणु
		वापस (शून्य);
	पूर्ण

	वापस (ACPI_CAST_PTR(काष्ठा acpi_namespace_node, handle));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_terminate
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: मुक्त memory allocated क्रम namespace and ACPI table storage.
 *
 ******************************************************************************/

व्योम acpi_ns_terminate(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_terminate);

	/*
	 * Free the entire namespace -- all nodes and all objects
	 * attached to the nodes
	 */
	acpi_ns_delete_namespace_subtree(acpi_gbl_root_node);

	/* Delete any objects attached to the root node */

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_VOID;
	पूर्ण

	acpi_ns_delete_node(acpi_gbl_root_node);
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Namespace freed\n"));
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_खोलोs_scope
 *
 * PARAMETERS:  type        - A valid namespace type
 *
 * RETURN:      NEWSCOPE अगर the passed type "opens a name scope" according
 *              to the ACPI specअगरication, अन्यथा 0
 *
 ******************************************************************************/

u32 acpi_ns_खोलोs_scope(acpi_object_type type)
अणु
	ACPI_FUNCTION_ENTRY();

	अगर (type > ACPI_TYPE_LOCAL_MAX) अणु

		/* type code out of range  */

		ACPI_WARNING((AE_INFO, "Invalid Object Type 0x%X", type));
		वापस (ACPI_NS_NORMAL);
	पूर्ण

	वापस (((u32)acpi_gbl_ns_properties[type]) & ACPI_NS_NEWSCOPE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_node_unlocked
 *
 * PARAMETERS:  *pathname   - Name to be found, in बाह्यal (ASL) क्रमmat. The
 *                            \ (backslash) and ^ (carat) prefixes, and the
 *                            . (period) to separate segments are supported.
 *              prefix_node  - Root of subtree to be searched, or NS_ALL क्रम the
 *                            root of the name space. If Name is fully
 *                            qualअगरied (first s8 is '\'), the passed value
 *                            of Scope will not be accessed.
 *              flags       - Used to indicate whether to perक्रमm upsearch or
 *                            not.
 *              वापस_node - Where the Node is वापसed
 *
 * DESCRIPTION: Look up a name relative to a given scope and वापस the
 *              corresponding Node. NOTE: Scope can be null.
 *
 * MUTEX:       Doesn't locks namespace
 *
 ******************************************************************************/

acpi_status
acpi_ns_get_node_unlocked(काष्ठा acpi_namespace_node *prefix_node,
			  स्थिर अक्षर *pathname,
			  u32 flags, काष्ठा acpi_namespace_node **वापस_node)
अणु
	जोड़ acpi_generic_state scope_info;
	acpi_status status;
	अक्षर *पूर्णांकernal_path;

	ACPI_FUNCTION_TRACE_PTR(ns_get_node_unlocked,
				ACPI_CAST_PTR(अक्षर, pathname));

	/* Simplest हाल is a null pathname */

	अगर (!pathname) अणु
		*वापस_node = prefix_node;
		अगर (!prefix_node) अणु
			*वापस_node = acpi_gbl_root_node;
		पूर्ण

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Quick check क्रम a reference to the root */

	अगर (ACPI_IS_ROOT_PREFIX(pathname[0]) && (!pathname[1])) अणु
		*वापस_node = acpi_gbl_root_node;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Convert path to पूर्णांकernal representation */

	status = acpi_ns_पूर्णांकernalize_name(pathname, &पूर्णांकernal_path);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Setup lookup scope (search starting poपूर्णांक) */

	scope_info.scope.node = prefix_node;

	/* Lookup the name in the namespace */

	status = acpi_ns_lookup(&scope_info, पूर्णांकernal_path, ACPI_TYPE_ANY,
				ACPI_IMODE_EXECUTE,
				(flags | ACPI_NS_DONT_OPEN_SCOPE), शून्य,
				वापस_node);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%s, %s\n",
				  pathname, acpi_क्रमmat_exception(status)));
	पूर्ण

	ACPI_FREE(पूर्णांकernal_path);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_node
 *
 * PARAMETERS:  *pathname   - Name to be found, in बाह्यal (ASL) क्रमmat. The
 *                            \ (backslash) and ^ (carat) prefixes, and the
 *                            . (period) to separate segments are supported.
 *              prefix_node  - Root of subtree to be searched, or NS_ALL क्रम the
 *                            root of the name space. If Name is fully
 *                            qualअगरied (first s8 is '\'), the passed value
 *                            of Scope will not be accessed.
 *              flags       - Used to indicate whether to perक्रमm upsearch or
 *                            not.
 *              वापस_node - Where the Node is वापसed
 *
 * DESCRIPTION: Look up a name relative to a given scope and वापस the
 *              corresponding Node. NOTE: Scope can be null.
 *
 * MUTEX:       Locks namespace
 *
 ******************************************************************************/

acpi_status
acpi_ns_get_node(काष्ठा acpi_namespace_node *prefix_node,
		 स्थिर अक्षर *pathname,
		 u32 flags, काष्ठा acpi_namespace_node **वापस_node)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ns_get_node, ACPI_CAST_PTR(अक्षर, pathname));

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ns_get_node_unlocked(prefix_node, pathname,
					   flags, वापस_node);

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण
