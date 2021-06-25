<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: nsxfobj - Public पूर्णांकerfaces to the ACPI subप्रणाली
 *                         ACPI Object oriented पूर्णांकerfaces
 *
 ******************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsxfobj")

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_type
 *
 * PARAMETERS:  handle          - Handle of object whose type is desired
 *              ret_type        - Where the type will be placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine वापसs the type associated with a particular
 *              handle
 *
 ******************************************************************************/
acpi_status acpi_get_type(acpi_handle handle, acpi_object_type *ret_type)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	/* Parameter Validation */

	अगर (!ret_type) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Special हाल क्रम the predefined Root Node (वापस type ANY) */

	अगर (handle == ACPI_ROOT_OBJECT) अणु
		*ret_type = ACPI_TYPE_ANY;
		वापस (AE_OK);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Convert and validate the handle */

	node = acpi_ns_validate_handle(handle);
	अगर (!node) अणु
		(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	*ret_type = node->type;

	status = acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_type)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_parent
 *
 * PARAMETERS:  handle          - Handle of object whose parent is desired
 *              ret_handle      - Where the parent handle will be placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns a handle to the parent of the object represented by
 *              Handle.
 *
 ******************************************************************************/
acpi_status acpi_get_parent(acpi_handle handle, acpi_handle *ret_handle)
अणु
	काष्ठा acpi_namespace_node *node;
	काष्ठा acpi_namespace_node *parent_node;
	acpi_status status;

	अगर (!ret_handle) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Special हाल क्रम the predefined Root Node (no parent) */

	अगर (handle == ACPI_ROOT_OBJECT) अणु
		वापस (AE_शून्य_ENTRY);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Convert and validate the handle */

	node = acpi_ns_validate_handle(handle);
	अगर (!node) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Get the parent entry */

	parent_node = node->parent;
	*ret_handle = ACPI_CAST_PTR(acpi_handle, parent_node);

	/* Return exception अगर parent is null */

	अगर (!parent_node) अणु
		status = AE_शून्य_ENTRY;
	पूर्ण

unlock_and_निकास:

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_parent)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_next_object
 *
 * PARAMETERS:  type            - Type of object to be searched क्रम
 *              parent          - Parent object whose children we are getting
 *              last_child      - Previous child that was found.
 *                                The NEXT child will be वापसed
 *              ret_handle      - Where handle to the next object is placed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return the next peer object within the namespace. If Handle is
 *              valid, Scope is ignored. Otherwise, the first object within
 *              Scope is वापसed.
 *
 ******************************************************************************/
acpi_status
acpi_get_next_object(acpi_object_type type,
		     acpi_handle parent,
		     acpi_handle child, acpi_handle *ret_handle)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	काष्ठा acpi_namespace_node *parent_node = शून्य;
	काष्ठा acpi_namespace_node *child_node = शून्य;

	/* Parameter validation */

	अगर (type > ACPI_TYPE_EXTERNAL_MAX) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* If null handle, use the parent */

	अगर (!child) अणु

		/* Start search at the beginning of the specअगरied scope */

		parent_node = acpi_ns_validate_handle(parent);
		अगर (!parent_node) अणु
			status = AE_BAD_PARAMETER;
			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non-null handle, ignore the parent */
		/* Convert and validate the handle */

		child_node = acpi_ns_validate_handle(child);
		अगर (!child_node) अणु
			status = AE_BAD_PARAMETER;
			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण

	/* Internal function करोes the real work */

	node = acpi_ns_get_next_node_typed(type, parent_node, child_node);
	अगर (!node) अणु
		status = AE_NOT_FOUND;
		जाओ unlock_and_निकास;
	पूर्ण

	अगर (ret_handle) अणु
		*ret_handle = ACPI_CAST_PTR(acpi_handle, node);
	पूर्ण

unlock_and_निकास:

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_next_object)
