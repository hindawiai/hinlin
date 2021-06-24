<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dspkginit - Completion of deferred package initialization
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acparser.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("dspkginit")

/* Local prototypes */
अटल व्योम
acpi_ds_resolve_package_element(जोड़ acpi_opeअक्रम_object **element);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_build_पूर्णांकernal_package_obj
 *
 * PARAMETERS:  walk_state      - Current walk state
 *              op              - Parser object to be translated
 *              element_count   - Number of elements in the package - this is
 *                                the num_elements argument to Package()
 *              obj_desc_ptr    - Where the ACPI पूर्णांकernal object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Translate a parser Op package object to the equivalent
 *              namespace object
 *
 * NOTE: The number of elements in the package will be always be the num_elements
 * count, regardless of the number of elements in the package list. If
 * num_elements is smaller, only that many package list elements are used.
 * अगर num_elements is larger, the Package object is padded out with
 * objects of type Uninitialized (as per ACPI spec.)
 *
 * Even though the ASL compilers करो not allow num_elements to be smaller
 * than the Package list length (क्रम the fixed length package opcode), some
 * BIOS code modअगरies the AML on the fly to adjust the num_elements, and
 * this code compensates क्रम that. This also provides compatibility with
 * other AML पूर्णांकerpreters.
 *
 ******************************************************************************/

acpi_status
acpi_ds_build_पूर्णांकernal_package_obj(काष्ठा acpi_walk_state *walk_state,
				   जोड़ acpi_parse_object *op,
				   u32 element_count,
				   जोड़ acpi_opeअक्रम_object **obj_desc_ptr)
अणु
	जोड़ acpi_parse_object *arg;
	जोड़ acpi_parse_object *parent;
	जोड़ acpi_opeअक्रम_object *obj_desc = शून्य;
	acpi_status status = AE_OK;
	u8 module_level_code = FALSE;
	u16 reference_count;
	u32 index;
	u32 i;

	ACPI_FUNCTION_TRACE(ds_build_पूर्णांकernal_package_obj);

	/* Check अगर we are executing module level code */

	अगर (walk_state->parse_flags & ACPI_PARSE_MODULE_LEVEL) अणु
		module_level_code = TRUE;
	पूर्ण

	/* Find the parent of a possibly nested package */

	parent = op->common.parent;
	जबतक ((parent->common.aml_opcode == AML_PACKAGE_OP) ||
	       (parent->common.aml_opcode == AML_VARIABLE_PACKAGE_OP)) अणु
		parent = parent->common.parent;
	पूर्ण

	/*
	 * If we are evaluating a Named package object of the क्रमm:
	 *      Name (xxxx, Package)
	 * the package object alपढ़ोy exists, otherwise it must be created.
	 */
	obj_desc = *obj_desc_ptr;
	अगर (!obj_desc) अणु
		obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_PACKAGE);
		*obj_desc_ptr = obj_desc;
		अगर (!obj_desc) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		obj_desc->package.node = parent->common.node;
	पूर्ण

	अगर (obj_desc->package.flags & AOPOBJ_DATA_VALID) अणु	/* Just in हाल */
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Allocate the element array (array of poपूर्णांकers to the inभागidual
	 * objects) अगर necessary. the count is based on the num_elements
	 * parameter. Add an extra poपूर्णांकer slot so that the list is always
	 * null terminated.
	 */
	अगर (!obj_desc->package.elements) अणु
		obj_desc->package.elements = ACPI_ALLOCATE_ZEROED(((acpi_size)
								   element_count
								   +
								   1) *
								  माप(व्योम
									 *));

		अगर (!obj_desc->package.elements) अणु
			acpi_ut_delete_object_desc(obj_desc);
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		obj_desc->package.count = element_count;
	पूर्ण

	/* First arg is element count. Second arg begins the initializer list */

	arg = op->common.value.arg;
	arg = arg->common.next;

	/*
	 * If we are executing module-level code, we will defer the
	 * full resolution of the package elements in order to support
	 * क्रमward references from the elements. This provides
	 * compatibility with other ACPI implementations.
	 */
	अगर (module_level_code) अणु
		obj_desc->package.aml_start = walk_state->aml;
		obj_desc->package.aml_length = 0;

		ACPI_DEBUG_PRINT_RAW((ACPI_DB_PARSE,
				      "%s: Deferring resolution of Package elements\n",
				      ACPI_GET_FUNCTION_NAME));
	पूर्ण

	/*
	 * Initialize the elements of the package, up to the num_elements count.
	 * Package is स्वतःmatically padded with uninitialized (शून्य) elements
	 * अगर num_elements is greater than the package list length. Likewise,
	 * Package is truncated अगर num_elements is less than the list length.
	 */
	क्रम (i = 0; arg && (i < element_count); i++) अणु
		अगर (arg->common.aml_opcode == AML_INT_RETURN_VALUE_OP) अणु
			अगर (!arg->common.node) अणु
				/*
				 * This is the हाल where an expression has वापसed a value.
				 * The use of expressions (term_args) within inभागidual
				 * package elements is not supported by the AML पूर्णांकerpreter,
				 * even though the ASL grammar supports it. Example:
				 *
				 *      Name (INT1, 0x1234)
				 *
				 *      Name (PKG3, Package () अणु
				 *          Add (INT1, 0xAAAA0000)
				 *      पूर्ण)
				 *
				 *  1) No known AML पूर्णांकerpreter supports this type of स्थिरruct
				 *  2) This fixes a fault अगर the स्थिरruct is encountered
				 */
				ACPI_EXCEPTION((AE_INFO, AE_SUPPORT,
						"Expressions within package elements are not supported"));

				/* Cleanup the वापस object, it is not needed */

				acpi_ut_हटाओ_reference(walk_state->results->
							 results.obj_desc[0]);
				वापस_ACPI_STATUS(AE_SUPPORT);
			पूर्ण

			अगर (arg->common.node->type == ACPI_TYPE_METHOD) अणु
				/*
				 * A method reference "looks" to the parser to be a method
				 * invocation, so we special हाल it here
				 */
				arg->common.aml_opcode = AML_INT_NAMEPATH_OP;
				status =
				    acpi_ds_build_पूर्णांकernal_object(walk_state,
								  arg,
								  &obj_desc->
								  package.
								  elements[i]);
			पूर्ण अन्यथा अणु
				/* This package element is alपढ़ोy built, just get it */

				obj_desc->package.elements[i] =
				    ACPI_CAST_PTR(जोड़ acpi_opeअक्रम_object,
						  arg->common.node);
			पूर्ण
		पूर्ण अन्यथा अणु
			status =
			    acpi_ds_build_पूर्णांकernal_object(walk_state, arg,
							  &obj_desc->package.
							  elements[i]);
			अगर (status == AE_NOT_FOUND) अणु
				ACPI_ERROR((AE_INFO, "%-48s",
					    "****DS namepath not found"));
			पूर्ण

			अगर (!module_level_code) अणु
				/*
				 * Initialize this package element. This function handles the
				 * resolution of named references within the package.
				 * Forward references from module-level code are deferred
				 * until all ACPI tables are loaded.
				 */
				acpi_ds_init_package_element(0,
							     obj_desc->package.
							     elements[i], शून्य,
							     &obj_desc->package.
							     elements[i]);
			पूर्ण
		पूर्ण

		अगर (*obj_desc_ptr) अणु

			/* Existing package, get existing reference count */

			reference_count =
			    (*obj_desc_ptr)->common.reference_count;
			अगर (reference_count > 1) अणु

				/* Make new element ref count match original ref count */
				/* TBD: Probably need an acpi_ut_add_references function */

				क्रम (index = 0;
				     index < ((u32)reference_count - 1);
				     index++) अणु
					acpi_ut_add_reference((obj_desc->
							       package.
							       elements[i]));
				पूर्ण
			पूर्ण
		पूर्ण

		arg = arg->common.next;
	पूर्ण

	/* Check क्रम match between num_elements and actual length of package_list */

	अगर (arg) अणु
		/*
		 * num_elements was exhausted, but there are reमुख्यing elements in
		 * the package_list. Truncate the package to num_elements.
		 *
		 * Note: technically, this is an error, from ACPI spec: "It is an
		 * error क्रम NumElements to be less than the number of elements in
		 * the PackageList". However, we just prपूर्णांक a message and no
		 * exception is वापसed. This provides compatibility with other
		 * ACPI implementations. Some firmware implementations will alter
		 * the num_elements on the fly, possibly creating this type of
		 * ill-क्रमmed package object.
		 */
		जबतक (arg) अणु
			/*
			 * We must delete any package elements that were created earlier
			 * and are not going to be used because of the package truncation.
			 */
			अगर (arg->common.node) अणु
				acpi_ut_हटाओ_reference(ACPI_CAST_PTR
							 (जोड़
							  acpi_opeअक्रम_object,
							  arg->common.node));
				arg->common.node = शून्य;
			पूर्ण

			/* Find out how many elements there really are */

			i++;
			arg = arg->common.next;
		पूर्ण

		ACPI_INFO(("Actual Package length (%u) is larger than "
			   "NumElements field (%u), truncated",
			   i, element_count));
	पूर्ण अन्यथा अगर (i < element_count) अणु
		/*
		 * Arg list (elements) was exhausted, but we did not reach
		 * num_elements count.
		 *
		 * Note: this is not an error, the package is padded out
		 * with शून्यs as per the ACPI specअगरication.
		 */
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_INFO,
				      "%s: Package List length (%u) smaller than NumElements "
				      "count (%u), padded with null elements\n",
				      ACPI_GET_FUNCTION_NAME, i,
				      element_count));
	पूर्ण

	/* Module-level packages will be resolved later */

	अगर (!module_level_code) अणु
		obj_desc->package.flags |= AOPOBJ_DATA_VALID;
	पूर्ण

	op->common.node = ACPI_CAST_PTR(काष्ठा acpi_namespace_node, obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_package_element
 *
 * PARAMETERS:  acpi_pkg_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Resolve a named reference element within a package object
 *
 ******************************************************************************/

acpi_status
acpi_ds_init_package_element(u8 object_type,
			     जोड़ acpi_opeअक्रम_object *source_object,
			     जोड़ acpi_generic_state *state, व्योम *context)
अणु
	जोड़ acpi_opeअक्रम_object **element_ptr;

	ACPI_FUNCTION_TRACE(ds_init_package_element);

	अगर (!source_object) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * The following code is a bit of a hack to workaround a (current)
	 * limitation of the acpi_pkg_callback पूर्णांकerface. We need a poपूर्णांकer
	 * to the location within the element array because a new object
	 * may be created and stored there.
	 */
	अगर (context) अणु

		/* A direct call was made to this function */

		element_ptr = (जोड़ acpi_opeअक्रम_object **)context;
	पूर्ण अन्यथा अणु
		/* Call came from acpi_ut_walk_package_tree */

		element_ptr = state->pkg.this_target_obj;
	पूर्ण

	/* We are only पूर्णांकerested in reference objects/elements */

	अगर (source_object->common.type == ACPI_TYPE_LOCAL_REFERENCE) अणु

		/* Attempt to resolve the (named) reference to a namespace node */

		acpi_ds_resolve_package_element(element_ptr);
	पूर्ण अन्यथा अगर (source_object->common.type == ACPI_TYPE_PACKAGE) अणु
		source_object->package.flags |= AOPOBJ_DATA_VALID;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_resolve_package_element
 *
 * PARAMETERS:  element_ptr         - Poपूर्णांकer to a reference object
 *
 * RETURN:      Possible new element is stored to the indirect element_ptr
 *
 * DESCRIPTION: Resolve a package element that is a reference to a named
 *              object.
 *
 ******************************************************************************/

अटल व्योम
acpi_ds_resolve_package_element(जोड़ acpi_opeअक्रम_object **element_ptr)
अणु
	acpi_status status;
	acpi_status status2;
	जोड़ acpi_generic_state scope_info;
	जोड़ acpi_opeअक्रम_object *element = *element_ptr;
	काष्ठा acpi_namespace_node *resolved_node;
	काष्ठा acpi_namespace_node *original_node;
	अक्षर *बाह्यal_path = "";
	acpi_object_type type;

	ACPI_FUNCTION_TRACE(ds_resolve_package_element);

	/* Check अगर reference element is alपढ़ोy resolved */

	अगर (element->reference.resolved) अणु
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_PARSE,
				      "%s: Package element is already resolved\n",
				      ACPI_GET_FUNCTION_NAME));

		वापस_VOID;
	पूर्ण

	/* Element must be a reference object of correct type */

	scope_info.scope.node = element->reference.node;	/* Prefix node */

	status = acpi_ns_lookup(&scope_info, (अक्षर *)element->reference.aml,
				ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
				ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE,
				शून्य, &resolved_node);
	अगर (ACPI_FAILURE(status)) अणु
		अगर ((status == AE_NOT_FOUND)
		    && acpi_gbl_ignore_package_resolution_errors) अणु
			/*
			 * Optionally be silent about the NOT_FOUND हाल क्रम the referenced
			 * name. Although this is potentially a serious problem,
			 * it can generate a lot of noise/errors on platक्रमms whose
			 * firmware carries around a bunch of unused Package objects.
			 * To disable these errors, set this global to TRUE:
			 *     acpi_gbl_ignore_package_resolution_errors
			 *
			 * If the AML actually tries to use such a package, the unresolved
			 * element(s) will be replaced with शून्य elements.
			 */

			/* Referenced name not found, set the element to शून्य */

			acpi_ut_हटाओ_reference(*element_ptr);
			*element_ptr = शून्य;
			वापस_VOID;
		पूर्ण

		status2 = acpi_ns_बाह्यalize_name(ACPI_UINT32_MAX,
						   (अक्षर *)element->reference.
						   aml, शून्य, &बाह्यal_path);

		ACPI_EXCEPTION((AE_INFO, status,
				"While resolving a named reference package element - %s",
				बाह्यal_path));
		अगर (ACPI_SUCCESS(status2)) अणु
			ACPI_FREE(बाह्यal_path);
		पूर्ण

		/* Could not resolve name, set the element to शून्य */

		acpi_ut_हटाओ_reference(*element_ptr);
		*element_ptr = शून्य;
		वापस_VOID;
	पूर्ण अन्यथा अगर (resolved_node->type == ACPI_TYPE_ANY) अणु

		/* Named reference not resolved, वापस a शून्य package element */

		ACPI_ERROR((AE_INFO,
			    "Could not resolve named package element [%4.4s] in [%4.4s]",
			    resolved_node->name.ascii,
			    scope_info.scope.node->name.ascii));
		*element_ptr = शून्य;
		वापस_VOID;
	पूर्ण

	/*
	 * Special handling क्रम Alias objects. We need resolved_node to poपूर्णांक
	 * to the Alias target. This effectively "resolves" the alias.
	 */
	अगर (resolved_node->type == ACPI_TYPE_LOCAL_ALIAS) अणु
		resolved_node = ACPI_CAST_PTR(काष्ठा acpi_namespace_node,
					      resolved_node->object);
	पूर्ण

	/* Update the reference object */

	element->reference.resolved = TRUE;
	element->reference.node = resolved_node;
	type = element->reference.node->type;

	/*
	 * Attempt to resolve the node to a value beक्रमe we insert it पूर्णांकo
	 * the package. If this is a reference to a common data type,
	 * resolve it immediately. According to the ACPI spec, package
	 * elements can only be "data objects" or method references.
	 * Attempt to resolve to an Integer, Buffer, String or Package.
	 * If cannot, वापस the named reference (क्रम things like Devices,
	 * Methods, etc.) Buffer Fields and Fields will resolve to simple
	 * objects (पूर्णांक/buf/str/pkg).
	 *
	 * NOTE: References to things like Devices, Methods, Mutexes, etc.
	 * will reमुख्य as named references. This behavior is not described
	 * in the ACPI spec, but it appears to be an oversight.
	 */
	original_node = resolved_node;
	status = acpi_ex_resolve_node_to_value(&resolved_node, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_VOID;
	पूर्ण

	चयन (type) अणु
		/*
		 * These object types are a result of named references, so we will
		 * leave them as reference objects. In other words, these types
		 * have no पूर्णांकrinsic "value".
		 */
	हाल ACPI_TYPE_DEVICE:
	हाल ACPI_TYPE_THERMAL:
	हाल ACPI_TYPE_METHOD:
		अवरोध;

	हाल ACPI_TYPE_MUTEX:
	हाल ACPI_TYPE_POWER:
	हाल ACPI_TYPE_PROCESSOR:
	हाल ACPI_TYPE_EVENT:
	हाल ACPI_TYPE_REGION:

		/* acpi_ex_resolve_node_to_value gave these an extra reference */

		acpi_ut_हटाओ_reference(original_node->object);
		अवरोध;

	शेष:
		/*
		 * For all other types - the node was resolved to an actual
		 * opeअक्रम object with a value, वापस the object. Remove
		 * a reference on the existing object.
		 */
		acpi_ut_हटाओ_reference(element);
		*element_ptr = (जोड़ acpi_opeअक्रम_object *)resolved_node;
		अवरोध;
	पूर्ण

	वापस_VOID;
पूर्ण
