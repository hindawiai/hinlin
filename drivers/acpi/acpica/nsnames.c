<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: nsnames - Name manipulation and search
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsnames")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_बाह्यal_pathname
 *
 * PARAMETERS:  node            - Namespace node whose pathname is needed
 *
 * RETURN:      Poपूर्णांकer to storage containing the fully qualअगरied name of
 *              the node, In बाह्यal क्रमmat (name segments separated by path
 *              separators.)
 *
 * DESCRIPTION: Used to obtain the full pathname to a namespace node, usually
 *              क्रम error and debug statements.
 *
 ******************************************************************************/
अक्षर *acpi_ns_get_बाह्यal_pathname(काष्ठा acpi_namespace_node *node)
अणु
	अक्षर *name_buffer;

	ACPI_FUNCTION_TRACE_PTR(ns_get_बाह्यal_pathname, node);

	name_buffer = acpi_ns_get_normalized_pathname(node, FALSE);
	वापस_PTR(name_buffer);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_pathname_length
 *
 * PARAMETERS:  node        - Namespace node
 *
 * RETURN:      Length of path, including prefix
 *
 * DESCRIPTION: Get the length of the pathname string क्रम this node
 *
 ******************************************************************************/

acpi_size acpi_ns_get_pathname_length(काष्ठा acpi_namespace_node *node)
अणु
	acpi_size size;

	/* Validate the Node */

	अगर (ACPI_GET_DESCRIPTOR_TYPE(node) != ACPI_DESC_TYPE_NAMED) अणु
		ACPI_ERROR((AE_INFO,
			    "Invalid/cached reference target node: %p, descriptor type %d",
			    node, ACPI_GET_DESCRIPTOR_TYPE(node)));
		वापस (0);
	पूर्ण

	size = acpi_ns_build_normalized_path(node, शून्य, 0, FALSE);
	वापस (size);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_handle_to_name
 *
 * PARAMETERS:  target_handle           - Handle of named object whose name is
 *                                        to be found
 *              buffer                  - Where the name is वापसed
 *
 * RETURN:      Status, Buffer is filled with name अगर status is AE_OK
 *
 * DESCRIPTION: Build and वापस a full namespace name
 *
 ******************************************************************************/

acpi_status
acpi_ns_handle_to_name(acpi_handle target_handle, काष्ठा acpi_buffer *buffer)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	स्थिर अक्षर *node_name;

	ACPI_FUNCTION_TRACE_PTR(ns_handle_to_name, target_handle);

	node = acpi_ns_validate_handle(target_handle);
	अगर (!node) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Validate/Allocate/Clear caller buffer */

	status = acpi_ut_initialize_buffer(buffer, ACPI_PATH_SEGMENT_LENGTH);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Just copy the ACPI name from the Node and zero terminate it */

	node_name = acpi_ut_get_node_name(node);
	ACPI_COPY_NAMESEG(buffer->poपूर्णांकer, node_name);
	((अक्षर *)buffer->poपूर्णांकer)[ACPI_NAMESEG_SIZE] = 0;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%4.4s\n", (अक्षर *)buffer->poपूर्णांकer));
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_handle_to_pathname
 *
 * PARAMETERS:  target_handle           - Handle of named object whose name is
 *                                        to be found
 *              buffer                  - Where the pathname is वापसed
 *              no_trailing             - Remove trailing '_' क्रम each name
 *                                        segment
 *
 * RETURN:      Status, Buffer is filled with pathname अगर status is AE_OK
 *
 * DESCRIPTION: Build and वापस a full namespace pathname
 *
 ******************************************************************************/

acpi_status
acpi_ns_handle_to_pathname(acpi_handle target_handle,
			   काष्ठा acpi_buffer *buffer, u8 no_trailing)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	acpi_size required_size;

	ACPI_FUNCTION_TRACE_PTR(ns_handle_to_pathname, target_handle);

	node = acpi_ns_validate_handle(target_handle);
	अगर (!node) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Determine size required क्रम the caller buffer */

	required_size =
	    acpi_ns_build_normalized_path(node, शून्य, 0, no_trailing);
	अगर (!required_size) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Validate/Allocate/Clear caller buffer */

	status = acpi_ut_initialize_buffer(buffer, required_size);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Build the path in the caller buffer */

	(व्योम)acpi_ns_build_normalized_path(node, buffer->poपूर्णांकer,
					    (u32)required_size, no_trailing);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%s [%X]\n",
			  (अक्षर *)buffer->poपूर्णांकer, (u32) required_size));
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_build_normalized_path
 *
 * PARAMETERS:  node        - Namespace node
 *              full_path   - Where the path name is वापसed
 *              path_size   - Size of वापसed path name buffer
 *              no_trailing - Remove trailing '_' from each name segment
 *
 * RETURN:      Return 1 अगर the AML path is empty, otherwise वापसing (length
 *              of pathname + 1) which means the 'FullPath' contains a trailing
 *              null.
 *
 * DESCRIPTION: Build and वापस a full namespace pathname.
 *              Note that अगर the size of 'FullPath' isn't large enough to
 *              contain the namespace node's path name, the actual required
 *              buffer length is वापसed, and it should be greater than
 *              'PathSize'. So callers are able to check the वापसing value
 *              to determine the buffer size of 'FullPath'.
 *
 ******************************************************************************/

u32
acpi_ns_build_normalized_path(काष्ठा acpi_namespace_node *node,
			      अक्षर *full_path, u32 path_size, u8 no_trailing)
अणु
	u32 length = 0, i;
	अक्षर name[ACPI_NAMESEG_SIZE];
	u8 करो_no_trailing;
	अक्षर c, *left, *right;
	काष्ठा acpi_namespace_node *next_node;

	ACPI_FUNCTION_TRACE_PTR(ns_build_normalized_path, node);

#घोषणा ACPI_PATH_PUT8(path, size, byte, length)    \
	करो अणु                                            \
		अगर ((length) < (size))                      \
		अणु                                           \
			(path)[(length)] = (byte);              \
		पूर्ण                                           \
		(length)++;                                 \
	पूर्ण जबतक (0)

	/*
	 * Make sure the path_size is correct, so that we करोn't need to
	 * validate both full_path and path_size.
	 */
	अगर (!full_path) अणु
		path_size = 0;
	पूर्ण

	अगर (!node) अणु
		जाओ build_trailing_null;
	पूर्ण

	next_node = node;
	जबतक (next_node && next_node != acpi_gbl_root_node) अणु
		अगर (next_node != node) अणु
			ACPI_PATH_PUT8(full_path, path_size,
				       AML_DUAL_NAME_PREFIX, length);
		पूर्ण

		ACPI_MOVE_32_TO_32(name, &next_node->name);
		करो_no_trailing = no_trailing;
		क्रम (i = 0; i < 4; i++) अणु
			c = name[4 - i - 1];
			अगर (करो_no_trailing && c != '_') अणु
				करो_no_trailing = FALSE;
			पूर्ण
			अगर (!करो_no_trailing) अणु
				ACPI_PATH_PUT8(full_path, path_size, c, length);
			पूर्ण
		पूर्ण

		next_node = next_node->parent;
	पूर्ण

	ACPI_PATH_PUT8(full_path, path_size, AML_ROOT_PREFIX, length);

	/* Reverse the path string */

	अगर (length <= path_size) अणु
		left = full_path;
		right = full_path + length - 1;

		जबतक (left < right) अणु
			c = *left;
			*left++ = *right;
			*right-- = c;
		पूर्ण
	पूर्ण

	/* Append the trailing null */

build_trailing_null:
	ACPI_PATH_PUT8(full_path, path_size, '\0', length);

#अघोषित ACPI_PATH_PUT8

	वापस_UINT32(length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_normalized_pathname
 *
 * PARAMETERS:  node            - Namespace node whose pathname is needed
 *              no_trailing     - Remove trailing '_' from each name segment
 *
 * RETURN:      Poपूर्णांकer to storage containing the fully qualअगरied name of
 *              the node, In बाह्यal क्रमmat (name segments separated by path
 *              separators.)
 *
 * DESCRIPTION: Used to obtain the full pathname to a namespace node, usually
 *              क्रम error and debug statements. All trailing '_' will be
 *              हटाओd from the full pathname अगर 'NoTrailing' is specअगरied..
 *
 ******************************************************************************/

अक्षर *acpi_ns_get_normalized_pathname(काष्ठा acpi_namespace_node *node,
				      u8 no_trailing)
अणु
	अक्षर *name_buffer;
	acpi_size size;

	ACPI_FUNCTION_TRACE_PTR(ns_get_normalized_pathname, node);

	/* Calculate required buffer size based on depth below root */

	size = acpi_ns_build_normalized_path(node, शून्य, 0, no_trailing);
	अगर (!size) अणु
		वापस_PTR(शून्य);
	पूर्ण

	/* Allocate a buffer to be वापसed to caller */

	name_buffer = ACPI_ALLOCATE_ZEROED(size);
	अगर (!name_buffer) अणु
		ACPI_ERROR((AE_INFO, "Could not allocate %u bytes", (u32)size));
		वापस_PTR(शून्य);
	पूर्ण

	/* Build the path in the allocated buffer */

	(व्योम)acpi_ns_build_normalized_path(node, name_buffer, (u32)size,
					    no_trailing);

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_NAMES, "%s: Path \"%s\"\n",
			      ACPI_GET_FUNCTION_NAME, name_buffer));

	वापस_PTR(name_buffer);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_build_prefixed_pathname
 *
 * PARAMETERS:  prefix_scope        - Scope/Path that prefixes the पूर्णांकernal path
 *              पूर्णांकernal_path       - Name or path of the namespace node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Conकाष्ठा a fully qualअगरied pathname from a concatenation of:
 *              1) Path associated with the prefix_scope namespace node
 *              2) External path representation of the Internal path
 *
 ******************************************************************************/

अक्षर *acpi_ns_build_prefixed_pathname(जोड़ acpi_generic_state *prefix_scope,
				      स्थिर अक्षर *पूर्णांकernal_path)
अणु
	acpi_status status;
	अक्षर *full_path = शून्य;
	अक्षर *बाह्यal_path = शून्य;
	अक्षर *prefix_path = शून्य;
	acpi_size prefix_path_length = 0;

	/* If there is a prefix, get the pathname to it */

	अगर (prefix_scope && prefix_scope->scope.node) अणु
		prefix_path =
		    acpi_ns_get_normalized_pathname(prefix_scope->scope.node,
						    TRUE);
		अगर (prefix_path) अणु
			prefix_path_length = म_माप(prefix_path);
		पूर्ण
	पूर्ण

	status = acpi_ns_बाह्यalize_name(ACPI_UINT32_MAX, पूर्णांकernal_path,
					  शून्य, &बाह्यal_path);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	/* Merge the prefix path and the path. 2 is क्रम one करोt and trailing null */

	full_path =
	    ACPI_ALLOCATE_ZEROED(prefix_path_length + म_माप(बाह्यal_path) +
				 2);
	अगर (!full_path) अणु
		जाओ cleanup;
	पूर्ण

	/* Don't merge अगर the External path is alपढ़ोy fully qualअगरied */

	अगर (prefix_path && (*बाह्यal_path != '\\') && (*external_path != '^')) अणु
		म_जोड़ो(full_path, prefix_path);
		अगर (prefix_path[1]) अणु
			म_जोड़ो(full_path, ".");
		पूर्ण
	पूर्ण

	acpi_ns_normalize_pathname(बाह्यal_path);
	म_जोड़ो(full_path, बाह्यal_path);

cleanup:
	अगर (prefix_path) अणु
		ACPI_FREE(prefix_path);
	पूर्ण
	अगर (बाह्यal_path) अणु
		ACPI_FREE(बाह्यal_path);
	पूर्ण

	वापस (full_path);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_normalize_pathname
 *
 * PARAMETERS:  original_path       - Path to be normalized, in External क्रमmat
 *
 * RETURN:      The original path is processed in-place
 *
 * DESCRIPTION: Remove trailing underscores from each element of a path.
 *
 *              For example:  \A___.B___.C___ becomes \A.B.C
 *
 ******************************************************************************/

व्योम acpi_ns_normalize_pathname(अक्षर *original_path)
अणु
	अक्षर *input_path = original_path;
	अक्षर *new_path_buffer;
	अक्षर *new_path;
	u32 i;

	/* Allocate a temp buffer in which to स्थिरruct the new path */

	new_path_buffer = ACPI_ALLOCATE_ZEROED(म_माप(input_path) + 1);
	new_path = new_path_buffer;
	अगर (!new_path_buffer) अणु
		वापस;
	पूर्ण

	/* Special अक्षरacters may appear at the beginning of the path */

	अगर (*input_path == '\\') अणु
		*new_path = *input_path;
		new_path++;
		input_path++;
	पूर्ण

	जबतक (*input_path == '^') अणु
		*new_path = *input_path;
		new_path++;
		input_path++;
	पूर्ण

	/* Reमुख्यder of the path */

	जबतक (*input_path) अणु

		/* Do one nameseg at a समय */

		क्रम (i = 0; (i < ACPI_NAMESEG_SIZE) && *input_path; i++) अणु
			अगर ((i == 0) || (*input_path != '_')) अणु	/* First अक्षर is allowed to be underscore */
				*new_path = *input_path;
				new_path++;
			पूर्ण

			input_path++;
		पूर्ण

		/* Dot means that there are more namesegs to come */

		अगर (*input_path == '.') अणु
			*new_path = *input_path;
			new_path++;
			input_path++;
		पूर्ण
	पूर्ण

	*new_path = 0;
	म_नकल(original_path, new_path_buffer);
	ACPI_FREE(new_path_buffer);
पूर्ण
