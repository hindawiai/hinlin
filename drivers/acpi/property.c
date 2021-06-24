<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI device specअगरic properties support.
 *
 * Copyright (C) 2014, Intel Corporation
 * All rights reserved.
 *
 * Authors: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *          Darren Hart <dvhart@linux.पूर्णांकel.com>
 *          Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>

#समावेश "internal.h"

अटल पूर्णांक acpi_data_get_property_array(स्थिर काष्ठा acpi_device_data *data,
					स्थिर अक्षर *name,
					acpi_object_type type,
					स्थिर जोड़ acpi_object **obj);

/*
 * The GUIDs here are made equivalent to each other in order to aव्योम extra
 * complनिकासy in the properties handling code, with the caveat that the
 * kernel will accept certain combinations of GUID and properties that are
 * not defined without a warning. For instance अगर any of the properties
 * from dअगरferent GUID appear in a property list of another, it will be
 * accepted by the kernel. Firmware validation tools should catch these.
 */
अटल स्थिर guid_t prp_guids[] = अणु
	/* ACPI _DSD device properties GUID: daffd814-6eba-4d8c-8a91-bc9bbf4aa301 */
	GUID_INIT(0xdaffd814, 0x6eba, 0x4d8c,
		  0x8a, 0x91, 0xbc, 0x9b, 0xbf, 0x4a, 0xa3, 0x01),
	/* Hotplug in D3 GUID: 6211e2c0-58a3-4af3-90e1-927a4e0c55a4 */
	GUID_INIT(0x6211e2c0, 0x58a3, 0x4af3,
		  0x90, 0xe1, 0x92, 0x7a, 0x4e, 0x0c, 0x55, 0xa4),
	/* External facing port GUID: efcc06cc-73ac-4bc3-bff0-76143807c389 */
	GUID_INIT(0xefcc06cc, 0x73ac, 0x4bc3,
		  0xbf, 0xf0, 0x76, 0x14, 0x38, 0x07, 0xc3, 0x89),
	/* Thunderbolt GUID क्रम IMR_VALID: c44d002f-69f9-4e7d-a904-a7baabdf43f7 */
	GUID_INIT(0xc44d002f, 0x69f9, 0x4e7d,
		  0xa9, 0x04, 0xa7, 0xba, 0xab, 0xdf, 0x43, 0xf7),
	/* Thunderbolt GUID क्रम WAKE_SUPPORTED: 6c501103-c189-4296-ba72-9bf5a26ebe5d */
	GUID_INIT(0x6c501103, 0xc189, 0x4296,
		  0xba, 0x72, 0x9b, 0xf5, 0xa2, 0x6e, 0xbe, 0x5d),
	/* Storage device needs D3 GUID: 5025030f-842f-4ab4-a561-99a5189762d0 */
	GUID_INIT(0x5025030f, 0x842f, 0x4ab4,
		  0xa5, 0x61, 0x99, 0xa5, 0x18, 0x97, 0x62, 0xd0),
पूर्ण;

/* ACPI _DSD data subnodes GUID: dbb8e3e6-5886-4ba6-8795-1319f52a966b */
अटल स्थिर guid_t ads_guid =
	GUID_INIT(0xdbb8e3e6, 0x5886, 0x4ba6,
		  0x87, 0x95, 0x13, 0x19, 0xf5, 0x2a, 0x96, 0x6b);

अटल bool acpi_क्रमागतerate_nondev_subnodes(acpi_handle scope,
					   स्थिर जोड़ acpi_object *desc,
					   काष्ठा acpi_device_data *data,
					   काष्ठा fwnode_handle *parent);
अटल bool acpi_extract_properties(स्थिर जोड़ acpi_object *desc,
				    काष्ठा acpi_device_data *data);

अटल bool acpi_nondev_subnode_extract(स्थिर जोड़ acpi_object *desc,
					acpi_handle handle,
					स्थिर जोड़ acpi_object *link,
					काष्ठा list_head *list,
					काष्ठा fwnode_handle *parent)
अणु
	काष्ठा acpi_data_node *dn;
	bool result;

	dn = kzalloc(माप(*dn), GFP_KERNEL);
	अगर (!dn)
		वापस false;

	dn->name = link->package.elements[0].string.poपूर्णांकer;
	fwnode_init(&dn->fwnode, &acpi_data_fwnode_ops);
	dn->parent = parent;
	INIT_LIST_HEAD(&dn->data.properties);
	INIT_LIST_HEAD(&dn->data.subnodes);

	result = acpi_extract_properties(desc, &dn->data);

	अगर (handle) अणु
		acpi_handle scope;
		acpi_status status;

		/*
		 * The scope क्रम the subnode object lookup is the one of the
		 * namespace node (device) containing the object that has
		 * वापसed the package.  That is, it's the scope of that
		 * object's parent.
		 */
		status = acpi_get_parent(handle, &scope);
		अगर (ACPI_SUCCESS(status)
		    && acpi_क्रमागतerate_nondev_subnodes(scope, desc, &dn->data,
						      &dn->fwnode))
			result = true;
	पूर्ण अन्यथा अगर (acpi_क्रमागतerate_nondev_subnodes(शून्य, desc, &dn->data,
						  &dn->fwnode)) अणु
		result = true;
	पूर्ण

	अगर (result) अणु
		dn->handle = handle;
		dn->data.poपूर्णांकer = desc;
		list_add_tail(&dn->sibling, list);
		वापस true;
	पूर्ण

	kमुक्त(dn);
	acpi_handle_debug(handle, "Invalid properties/subnodes data, skipping\n");
	वापस false;
पूर्ण

अटल bool acpi_nondev_subnode_data_ok(acpi_handle handle,
					स्थिर जोड़ acpi_object *link,
					काष्ठा list_head *list,
					काष्ठा fwnode_handle *parent)
अणु
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER पूर्ण;
	acpi_status status;

	status = acpi_evaluate_object_typed(handle, शून्य, शून्य, &buf,
					    ACPI_TYPE_PACKAGE);
	अगर (ACPI_FAILURE(status))
		वापस false;

	अगर (acpi_nondev_subnode_extract(buf.poपूर्णांकer, handle, link, list,
					parent))
		वापस true;

	ACPI_FREE(buf.poपूर्णांकer);
	वापस false;
पूर्ण

अटल bool acpi_nondev_subnode_ok(acpi_handle scope,
				   स्थिर जोड़ acpi_object *link,
				   काष्ठा list_head *list,
				   काष्ठा fwnode_handle *parent)
अणु
	acpi_handle handle;
	acpi_status status;

	अगर (!scope)
		वापस false;

	status = acpi_get_handle(scope, link->package.elements[1].string.poपूर्णांकer,
				 &handle);
	अगर (ACPI_FAILURE(status))
		वापस false;

	वापस acpi_nondev_subnode_data_ok(handle, link, list, parent);
पूर्ण

अटल पूर्णांक acpi_add_nondev_subnodes(acpi_handle scope,
				    स्थिर जोड़ acpi_object *links,
				    काष्ठा list_head *list,
				    काष्ठा fwnode_handle *parent)
अणु
	bool ret = false;
	पूर्णांक i;

	क्रम (i = 0; i < links->package.count; i++) अणु
		स्थिर जोड़ acpi_object *link, *desc;
		acpi_handle handle;
		bool result;

		link = &links->package.elements[i];
		/* Only two elements allowed. */
		अगर (link->package.count != 2)
			जारी;

		/* The first one must be a string. */
		अगर (link->package.elements[0].type != ACPI_TYPE_STRING)
			जारी;

		/* The second one may be a string, a reference or a package. */
		चयन (link->package.elements[1].type) अणु
		हाल ACPI_TYPE_STRING:
			result = acpi_nondev_subnode_ok(scope, link, list,
							 parent);
			अवरोध;
		हाल ACPI_TYPE_LOCAL_REFERENCE:
			handle = link->package.elements[1].reference.handle;
			result = acpi_nondev_subnode_data_ok(handle, link, list,
							     parent);
			अवरोध;
		हाल ACPI_TYPE_PACKAGE:
			desc = &link->package.elements[1];
			result = acpi_nondev_subnode_extract(desc, शून्य, link,
							     list, parent);
			अवरोध;
		शेष:
			result = false;
			अवरोध;
		पूर्ण
		ret = ret || result;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool acpi_क्रमागतerate_nondev_subnodes(acpi_handle scope,
					   स्थिर जोड़ acpi_object *desc,
					   काष्ठा acpi_device_data *data,
					   काष्ठा fwnode_handle *parent)
अणु
	पूर्णांक i;

	/* Look क्रम the ACPI data subnodes GUID. */
	क्रम (i = 0; i < desc->package.count; i += 2) अणु
		स्थिर जोड़ acpi_object *guid, *links;

		guid = &desc->package.elements[i];
		links = &desc->package.elements[i + 1];

		/*
		 * The first element must be a GUID and the second one must be
		 * a package.
		 */
		अगर (guid->type != ACPI_TYPE_BUFFER ||
		    guid->buffer.length != 16 ||
		    links->type != ACPI_TYPE_PACKAGE)
			अवरोध;

		अगर (!guid_equal((guid_t *)guid->buffer.poपूर्णांकer, &ads_guid))
			जारी;

		वापस acpi_add_nondev_subnodes(scope, links, &data->subnodes,
						parent);
	पूर्ण

	वापस false;
पूर्ण

अटल bool acpi_property_value_ok(स्थिर जोड़ acpi_object *value)
अणु
	पूर्णांक j;

	/*
	 * The value must be an पूर्णांकeger, a string, a reference, or a package
	 * whose every element must be an पूर्णांकeger, a string, or a reference.
	 */
	चयन (value->type) अणु
	हाल ACPI_TYPE_INTEGER:
	हाल ACPI_TYPE_STRING:
	हाल ACPI_TYPE_LOCAL_REFERENCE:
		वापस true;

	हाल ACPI_TYPE_PACKAGE:
		क्रम (j = 0; j < value->package.count; j++)
			चयन (value->package.elements[j].type) अणु
			हाल ACPI_TYPE_INTEGER:
			हाल ACPI_TYPE_STRING:
			हाल ACPI_TYPE_LOCAL_REFERENCE:
				जारी;

			शेष:
				वापस false;
			पूर्ण

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool acpi_properties_क्रमmat_valid(स्थिर जोड़ acpi_object *properties)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < properties->package.count; i++) अणु
		स्थिर जोड़ acpi_object *property;

		property = &properties->package.elements[i];
		/*
		 * Only two elements allowed, the first one must be a string and
		 * the second one has to satisfy certain conditions.
		 */
		अगर (property->package.count != 2
		    || property->package.elements[0].type != ACPI_TYPE_STRING
		    || !acpi_property_value_ok(&property->package.elements[1]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम acpi_init_of_compatible(काष्ठा acpi_device *adev)
अणु
	स्थिर जोड़ acpi_object *of_compatible;
	पूर्णांक ret;

	ret = acpi_data_get_property_array(&adev->data, "compatible",
					   ACPI_TYPE_STRING, &of_compatible);
	अगर (ret) अणु
		ret = acpi_dev_get_property(adev, "compatible",
					    ACPI_TYPE_STRING, &of_compatible);
		अगर (ret) अणु
			अगर (adev->parent
			    && adev->parent->flags.of_compatible_ok)
				जाओ out;

			वापस;
		पूर्ण
	पूर्ण
	adev->data.of_compatible = of_compatible;

 out:
	adev->flags.of_compatible_ok = 1;
पूर्ण

अटल bool acpi_is_property_guid(स्थिर guid_t *guid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(prp_guids); i++) अणु
		अगर (guid_equal(guid, &prp_guids[i]))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

काष्ठा acpi_device_properties *
acpi_data_add_props(काष्ठा acpi_device_data *data, स्थिर guid_t *guid,
		    स्थिर जोड़ acpi_object *properties)
अणु
	काष्ठा acpi_device_properties *props;

	props = kzalloc(माप(*props), GFP_KERNEL);
	अगर (props) अणु
		INIT_LIST_HEAD(&props->list);
		props->guid = guid;
		props->properties = properties;
		list_add_tail(&props->list, &data->properties);
	पूर्ण

	वापस props;
पूर्ण

अटल bool acpi_extract_properties(स्थिर जोड़ acpi_object *desc,
				    काष्ठा acpi_device_data *data)
अणु
	पूर्णांक i;

	अगर (desc->package.count % 2)
		वापस false;

	/* Look क्रम the device properties GUID. */
	क्रम (i = 0; i < desc->package.count; i += 2) अणु
		स्थिर जोड़ acpi_object *guid, *properties;

		guid = &desc->package.elements[i];
		properties = &desc->package.elements[i + 1];

		/*
		 * The first element must be a GUID and the second one must be
		 * a package.
		 */
		अगर (guid->type != ACPI_TYPE_BUFFER ||
		    guid->buffer.length != 16 ||
		    properties->type != ACPI_TYPE_PACKAGE)
			अवरोध;

		अगर (!acpi_is_property_guid((guid_t *)guid->buffer.poपूर्णांकer))
			जारी;

		/*
		 * We found the matching GUID. Now validate the क्रमmat of the
		 * package immediately following it.
		 */
		अगर (!acpi_properties_क्रमmat_valid(properties))
			जारी;

		acpi_data_add_props(data, (स्थिर guid_t *)guid->buffer.poपूर्णांकer,
				    properties);
	पूर्ण

	वापस !list_empty(&data->properties);
पूर्ण

व्योम acpi_init_properties(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER पूर्ण;
	काष्ठा acpi_hardware_id *hwid;
	acpi_status status;
	bool acpi_of = false;

	INIT_LIST_HEAD(&adev->data.properties);
	INIT_LIST_HEAD(&adev->data.subnodes);

	अगर (!adev->handle)
		वापस;

	/*
	 * Check अगर ACPI_DT_NAMESPACE_HID is present and पूर्णांकhat हाल we fill in
	 * Device Tree compatible properties क्रम this device.
	 */
	list_क्रम_each_entry(hwid, &adev->pnp.ids, list) अणु
		अगर (!म_भेद(hwid->id, ACPI_DT_NAMESPACE_HID)) अणु
			acpi_of = true;
			अवरोध;
		पूर्ण
	पूर्ण

	status = acpi_evaluate_object_typed(adev->handle, "_DSD", शून्य, &buf,
					    ACPI_TYPE_PACKAGE);
	अगर (ACPI_FAILURE(status))
		जाओ out;

	अगर (acpi_extract_properties(buf.poपूर्णांकer, &adev->data)) अणु
		adev->data.poपूर्णांकer = buf.poपूर्णांकer;
		अगर (acpi_of)
			acpi_init_of_compatible(adev);
	पूर्ण
	अगर (acpi_क्रमागतerate_nondev_subnodes(adev->handle, buf.poपूर्णांकer,
					&adev->data, acpi_fwnode_handle(adev)))
		adev->data.poपूर्णांकer = buf.poपूर्णांकer;

	अगर (!adev->data.poपूर्णांकer) अणु
		acpi_handle_debug(adev->handle, "Invalid _DSD data, skipping\n");
		ACPI_FREE(buf.poपूर्णांकer);
	पूर्ण

 out:
	अगर (acpi_of && !adev->flags.of_compatible_ok)
		acpi_handle_info(adev->handle,
			 ACPI_DT_NAMESPACE_HID " requires 'compatible' property\n");

	अगर (!adev->data.poपूर्णांकer)
		acpi_extract_apple_properties(adev);
पूर्ण

अटल व्योम acpi_destroy_nondev_subnodes(काष्ठा list_head *list)
अणु
	काष्ठा acpi_data_node *dn, *next;

	अगर (list_empty(list))
		वापस;

	list_क्रम_each_entry_safe_reverse(dn, next, list, sibling) अणु
		acpi_destroy_nondev_subnodes(&dn->data.subnodes);
		रुको_क्रम_completion(&dn->kobj_करोne);
		list_del(&dn->sibling);
		ACPI_FREE((व्योम *)dn->data.poपूर्णांकer);
		kमुक्त(dn);
	पूर्ण
पूर्ण

व्योम acpi_मुक्त_properties(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_device_properties *props, *पंचांगp;

	acpi_destroy_nondev_subnodes(&adev->data.subnodes);
	ACPI_FREE((व्योम *)adev->data.poपूर्णांकer);
	adev->data.of_compatible = शून्य;
	adev->data.poपूर्णांकer = शून्य;
	list_क्रम_each_entry_safe(props, पंचांगp, &adev->data.properties, list) अणु
		list_del(&props->list);
		kमुक्त(props);
	पूर्ण
पूर्ण

/**
 * acpi_data_get_property - वापस an ACPI property with given name
 * @data: ACPI device deta object to get the property from
 * @name: Name of the property
 * @type: Expected property type
 * @obj: Location to store the property value (अगर not %शून्य)
 *
 * Look up a property with @name and store a poपूर्णांकer to the resulting ACPI
 * object at the location poपूर्णांकed to by @obj अगर found.
 *
 * Callers must not attempt to मुक्त the वापसed objects.  These objects will be
 * मुक्तd by the ACPI core स्वतःmatically during the removal of @data.
 *
 * Return: %0 अगर property with @name has been found (success),
 *         %-EINVAL अगर the arguments are invalid,
 *         %-EINVAL अगर the property करोesn't exist,
 *         %-EPROTO अगर the property value type करोesn't match @type.
 */
अटल पूर्णांक acpi_data_get_property(स्थिर काष्ठा acpi_device_data *data,
				  स्थिर अक्षर *name, acpi_object_type type,
				  स्थिर जोड़ acpi_object **obj)
अणु
	स्थिर काष्ठा acpi_device_properties *props;

	अगर (!data || !name)
		वापस -EINVAL;

	अगर (!data->poपूर्णांकer || list_empty(&data->properties))
		वापस -EINVAL;

	list_क्रम_each_entry(props, &data->properties, list) अणु
		स्थिर जोड़ acpi_object *properties;
		अचिन्हित पूर्णांक i;

		properties = props->properties;
		क्रम (i = 0; i < properties->package.count; i++) अणु
			स्थिर जोड़ acpi_object *propname, *propvalue;
			स्थिर जोड़ acpi_object *property;

			property = &properties->package.elements[i];

			propname = &property->package.elements[0];
			propvalue = &property->package.elements[1];

			अगर (!म_भेद(name, propname->string.poपूर्णांकer)) अणु
				अगर (type != ACPI_TYPE_ANY &&
				    propvalue->type != type)
					वापस -EPROTO;
				अगर (obj)
					*obj = propvalue;

				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * acpi_dev_get_property - वापस an ACPI property with given name.
 * @adev: ACPI device to get the property from.
 * @name: Name of the property.
 * @type: Expected property type.
 * @obj: Location to store the property value (अगर not %शून्य).
 */
पूर्णांक acpi_dev_get_property(स्थिर काष्ठा acpi_device *adev, स्थिर अक्षर *name,
			  acpi_object_type type, स्थिर जोड़ acpi_object **obj)
अणु
	वापस adev ? acpi_data_get_property(&adev->data, name, type, obj) : -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_get_property);

अटल स्थिर काष्ठा acpi_device_data *
acpi_device_data_of_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	अगर (is_acpi_device_node(fwnode)) अणु
		स्थिर काष्ठा acpi_device *adev = to_acpi_device_node(fwnode);
		वापस &adev->data;
	पूर्ण अन्यथा अगर (is_acpi_data_node(fwnode)) अणु
		स्थिर काष्ठा acpi_data_node *dn = to_acpi_data_node(fwnode);
		वापस &dn->data;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * acpi_node_prop_get - वापस an ACPI property with given name.
 * @fwnode: Firmware node to get the property from.
 * @propname: Name of the property.
 * @valptr: Location to store a poपूर्णांकer to the property value (अगर not %शून्य).
 */
पूर्णांक acpi_node_prop_get(स्थिर काष्ठा fwnode_handle *fwnode,
		       स्थिर अक्षर *propname, व्योम **valptr)
अणु
	वापस acpi_data_get_property(acpi_device_data_of_node(fwnode),
				      propname, ACPI_TYPE_ANY,
				      (स्थिर जोड़ acpi_object **)valptr);
पूर्ण

/**
 * acpi_data_get_property_array - वापस an ACPI array property with given name
 * @data: ACPI data object to get the property from
 * @name: Name of the property
 * @type: Expected type of array elements
 * @obj: Location to store a poपूर्णांकer to the property value (अगर not शून्य)
 *
 * Look up an array property with @name and store a poपूर्णांकer to the resulting
 * ACPI object at the location poपूर्णांकed to by @obj अगर found.
 *
 * Callers must not attempt to मुक्त the वापसed objects.  Those objects will be
 * मुक्तd by the ACPI core स्वतःmatically during the removal of @data.
 *
 * Return: %0 अगर array property (package) with @name has been found (success),
 *         %-EINVAL अगर the arguments are invalid,
 *         %-EINVAL अगर the property करोesn't exist,
 *         %-EPROTO अगर the property is not a package or the type of its elements
 *           करोesn't match @type.
 */
अटल पूर्णांक acpi_data_get_property_array(स्थिर काष्ठा acpi_device_data *data,
					स्थिर अक्षर *name,
					acpi_object_type type,
					स्थिर जोड़ acpi_object **obj)
अणु
	स्थिर जोड़ acpi_object *prop;
	पूर्णांक ret, i;

	ret = acpi_data_get_property(data, name, ACPI_TYPE_PACKAGE, &prop);
	अगर (ret)
		वापस ret;

	अगर (type != ACPI_TYPE_ANY) अणु
		/* Check that all elements are of correct type. */
		क्रम (i = 0; i < prop->package.count; i++)
			अगर (prop->package.elements[i].type != type)
				वापस -EPROTO;
	पूर्ण
	अगर (obj)
		*obj = prop;

	वापस 0;
पूर्ण

अटल काष्ठा fwnode_handle *
acpi_fwnode_get_named_child_node(स्थिर काष्ठा fwnode_handle *fwnode,
				 स्थिर अक्षर *childname)
अणु
	काष्ठा fwnode_handle *child;

	fwnode_क्रम_each_child_node(fwnode, child) अणु
		अगर (is_acpi_data_node(child)) अणु
			अगर (acpi_data_node_match(child, childname))
				वापस child;
			जारी;
		पूर्ण

		अगर (!म_भेदन(acpi_device_bid(to_acpi_device_node(child)),
			     childname, ACPI_NAMESEG_SIZE))
			वापस child;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __acpi_node_get_property_reference - वापसs handle to the referenced object
 * @fwnode: Firmware node to get the property from
 * @propname: Name of the property
 * @index: Index of the reference to वापस
 * @num_args: Maximum number of arguments after each reference
 * @args: Location to store the वापसed reference with optional arguments
 *
 * Find property with @name, verअगरअगरy that it is a package containing at least
 * one object reference and अगर so, store the ACPI device object poपूर्णांकer to the
 * target object in @args->adev.  If the reference includes arguments, store
 * them in the @args->args[] array.
 *
 * If there's more than one reference in the property value package, @index is
 * used to select the one to वापस.
 *
 * It is possible to leave holes in the property value set like in the
 * example below:
 *
 * Package () अणु
 *     "cs-gpios",
 *     Package () अणु
 *        ^GPIO, 19, 0, 0,
 *        ^GPIO, 20, 0, 0,
 *        0,
 *        ^GPIO, 21, 0, 0,
 *     पूर्ण
 * पूर्ण
 *
 * Calling this function with index %2 or index %3 वापस %-ENOENT. If the
 * property करोes not contain any more values %-ENOENT is वापसed. The शून्य
 * entry must be single पूर्णांकeger and preferably contain value %0.
 *
 * Return: %0 on success, negative error code on failure.
 */
पूर्णांक __acpi_node_get_property_reference(स्थिर काष्ठा fwnode_handle *fwnode,
	स्थिर अक्षर *propname, माप_प्रकार index, माप_प्रकार num_args,
	काष्ठा fwnode_reference_args *args)
अणु
	स्थिर जोड़ acpi_object *element, *end;
	स्थिर जोड़ acpi_object *obj;
	स्थिर काष्ठा acpi_device_data *data;
	काष्ठा acpi_device *device;
	पूर्णांक ret, idx = 0;

	data = acpi_device_data_of_node(fwnode);
	अगर (!data)
		वापस -ENOENT;

	ret = acpi_data_get_property(data, propname, ACPI_TYPE_ANY, &obj);
	अगर (ret)
		वापस ret == -EINVAL ? -ENOENT : -EINVAL;

	/*
	 * The simplest हाल is when the value is a single reference.  Just
	 * वापस that reference then.
	 */
	अगर (obj->type == ACPI_TYPE_LOCAL_REFERENCE) अणु
		अगर (index)
			वापस -EINVAL;

		ret = acpi_bus_get_device(obj->reference.handle, &device);
		अगर (ret)
			वापस ret == -ENODEV ? -EINVAL : ret;

		args->fwnode = acpi_fwnode_handle(device);
		args->nargs = 0;
		वापस 0;
	पूर्ण

	/*
	 * If it is not a single reference, then it is a package of
	 * references followed by number of पूर्णांकs as follows:
	 *
	 *  Package () अणु REF, INT, REF, INT, INT पूर्ण
	 *
	 * The index argument is then used to determine which reference
	 * the caller wants (aदीर्घ with the arguments).
	 */
	अगर (obj->type != ACPI_TYPE_PACKAGE)
		वापस -EINVAL;
	अगर (index >= obj->package.count)
		वापस -ENOENT;

	element = obj->package.elements;
	end = element + obj->package.count;

	जबतक (element < end) अणु
		u32 nargs, i;

		अगर (element->type == ACPI_TYPE_LOCAL_REFERENCE) अणु
			काष्ठा fwnode_handle *ref_fwnode;

			ret = acpi_bus_get_device(element->reference.handle,
						  &device);
			अगर (ret)
				वापस -EINVAL;

			nargs = 0;
			element++;

			/*
			 * Find the referred data extension node under the
			 * referred device node.
			 */
			क्रम (ref_fwnode = acpi_fwnode_handle(device);
			     element < end && element->type == ACPI_TYPE_STRING;
			     element++) अणु
				ref_fwnode = acpi_fwnode_get_named_child_node(
					ref_fwnode, element->string.poपूर्णांकer);
				अगर (!ref_fwnode)
					वापस -EINVAL;
			पूर्ण

			/* assume following पूर्णांकeger elements are all args */
			क्रम (i = 0; element + i < end && i < num_args; i++) अणु
				पूर्णांक type = element[i].type;

				अगर (type == ACPI_TYPE_INTEGER)
					nargs++;
				अन्यथा अगर (type == ACPI_TYPE_LOCAL_REFERENCE)
					अवरोध;
				अन्यथा
					वापस -EINVAL;
			पूर्ण

			अगर (nargs > NR_FWNODE_REFERENCE_ARGS)
				वापस -EINVAL;

			अगर (idx == index) अणु
				args->fwnode = ref_fwnode;
				args->nargs = nargs;
				क्रम (i = 0; i < nargs; i++)
					args->args[i] = element[i].पूर्णांकeger.value;

				वापस 0;
			पूर्ण

			element += nargs;
		पूर्ण अन्यथा अगर (element->type == ACPI_TYPE_INTEGER) अणु
			अगर (idx == index)
				वापस -ENOENT;
			element++;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		idx++;
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(__acpi_node_get_property_reference);

अटल पूर्णांक acpi_data_prop_पढ़ो_single(स्थिर काष्ठा acpi_device_data *data,
				      स्थिर अक्षर *propname,
				      क्रमागत dev_prop_type proptype, व्योम *val)
अणु
	स्थिर जोड़ acpi_object *obj;
	पूर्णांक ret;

	अगर (proptype >= DEV_PROP_U8 && proptype <= DEV_PROP_U64) अणु
		ret = acpi_data_get_property(data, propname, ACPI_TYPE_INTEGER, &obj);
		अगर (ret)
			वापस ret;

		चयन (proptype) अणु
		हाल DEV_PROP_U8:
			अगर (obj->पूर्णांकeger.value > U8_MAX)
				वापस -EOVERFLOW;

			अगर (val)
				*(u8 *)val = obj->पूर्णांकeger.value;

			अवरोध;
		हाल DEV_PROP_U16:
			अगर (obj->पूर्णांकeger.value > U16_MAX)
				वापस -EOVERFLOW;

			अगर (val)
				*(u16 *)val = obj->पूर्णांकeger.value;

			अवरोध;
		हाल DEV_PROP_U32:
			अगर (obj->पूर्णांकeger.value > U32_MAX)
				वापस -EOVERFLOW;

			अगर (val)
				*(u32 *)val = obj->पूर्णांकeger.value;

			अवरोध;
		शेष:
			अगर (val)
				*(u64 *)val = obj->पूर्णांकeger.value;

			अवरोध;
		पूर्ण

		अगर (!val)
			वापस 1;
	पूर्ण अन्यथा अगर (proptype == DEV_PROP_STRING) अणु
		ret = acpi_data_get_property(data, propname, ACPI_TYPE_STRING, &obj);
		अगर (ret)
			वापस ret;

		अगर (val)
			*(अक्षर **)val = obj->string.poपूर्णांकer;

		वापस 1;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_copy_property_array_u8(स्थिर जोड़ acpi_object *items, u8 *val,
				       माप_प्रकार nval)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nval; i++) अणु
		अगर (items[i].type != ACPI_TYPE_INTEGER)
			वापस -EPROTO;
		अगर (items[i].पूर्णांकeger.value > U8_MAX)
			वापस -EOVERFLOW;

		val[i] = items[i].पूर्णांकeger.value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_copy_property_array_u16(स्थिर जोड़ acpi_object *items,
					u16 *val, माप_प्रकार nval)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nval; i++) अणु
		अगर (items[i].type != ACPI_TYPE_INTEGER)
			वापस -EPROTO;
		अगर (items[i].पूर्णांकeger.value > U16_MAX)
			वापस -EOVERFLOW;

		val[i] = items[i].पूर्णांकeger.value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_copy_property_array_u32(स्थिर जोड़ acpi_object *items,
					u32 *val, माप_प्रकार nval)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nval; i++) अणु
		अगर (items[i].type != ACPI_TYPE_INTEGER)
			वापस -EPROTO;
		अगर (items[i].पूर्णांकeger.value > U32_MAX)
			वापस -EOVERFLOW;

		val[i] = items[i].पूर्णांकeger.value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_copy_property_array_u64(स्थिर जोड़ acpi_object *items,
					u64 *val, माप_प्रकार nval)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nval; i++) अणु
		अगर (items[i].type != ACPI_TYPE_INTEGER)
			वापस -EPROTO;

		val[i] = items[i].पूर्णांकeger.value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_copy_property_array_string(स्थिर जोड़ acpi_object *items,
					   अक्षर **val, माप_प्रकार nval)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nval; i++) अणु
		अगर (items[i].type != ACPI_TYPE_STRING)
			वापस -EPROTO;

		val[i] = items[i].string.poपूर्णांकer;
	पूर्ण
	वापस nval;
पूर्ण

अटल पूर्णांक acpi_data_prop_पढ़ो(स्थिर काष्ठा acpi_device_data *data,
			       स्थिर अक्षर *propname,
			       क्रमागत dev_prop_type proptype,
			       व्योम *val, माप_प्रकार nval)
अणु
	स्थिर जोड़ acpi_object *obj;
	स्थिर जोड़ acpi_object *items;
	पूर्णांक ret;

	अगर (nval == 1 || !val) अणु
		ret = acpi_data_prop_पढ़ो_single(data, propname, proptype, val);
		/*
		 * The overflow error means that the property is there and it is
		 * single-value, but its type करोes not match, so वापस.
		 */
		अगर (ret >= 0 || ret == -EOVERFLOW)
			वापस ret;

		/*
		 * Reading this property as a single-value one failed, but its
		 * value may still be represented as one-element array, so
		 * जारी.
		 */
	पूर्ण

	ret = acpi_data_get_property_array(data, propname, ACPI_TYPE_ANY, &obj);
	अगर (ret)
		वापस ret;

	अगर (!val)
		वापस obj->package.count;

	अगर (proptype != DEV_PROP_STRING && nval > obj->package.count)
		वापस -EOVERFLOW;
	अन्यथा अगर (nval <= 0)
		वापस -EINVAL;

	items = obj->package.elements;

	चयन (proptype) अणु
	हाल DEV_PROP_U8:
		ret = acpi_copy_property_array_u8(items, (u8 *)val, nval);
		अवरोध;
	हाल DEV_PROP_U16:
		ret = acpi_copy_property_array_u16(items, (u16 *)val, nval);
		अवरोध;
	हाल DEV_PROP_U32:
		ret = acpi_copy_property_array_u32(items, (u32 *)val, nval);
		अवरोध;
	हाल DEV_PROP_U64:
		ret = acpi_copy_property_array_u64(items, (u64 *)val, nval);
		अवरोध;
	हाल DEV_PROP_STRING:
		ret = acpi_copy_property_array_string(
			items, (अक्षर **)val,
			min_t(u32, nval, obj->package.count));
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * acpi_node_prop_पढ़ो - retrieve the value of an ACPI property with given name.
 * @fwnode: Firmware node to get the property from.
 * @propname: Name of the property.
 * @proptype: Expected property type.
 * @val: Location to store the property value (अगर not %शून्य).
 * @nval: Size of the array poपूर्णांकed to by @val.
 *
 * If @val is %शून्य, वापस the number of array elements comprising the value
 * of the property.  Otherwise, पढ़ो at most @nval values to the array at the
 * location poपूर्णांकed to by @val.
 */
अटल पूर्णांक acpi_node_prop_पढ़ो(स्थिर काष्ठा fwnode_handle *fwnode,
			       स्थिर अक्षर *propname, क्रमागत dev_prop_type proptype,
			       व्योम *val, माप_प्रकार nval)
अणु
	वापस acpi_data_prop_पढ़ो(acpi_device_data_of_node(fwnode),
				   propname, proptype, val, nval);
पूर्ण

/**
 * acpi_get_next_subnode - Return the next child node handle क्रम a fwnode
 * @fwnode: Firmware node to find the next child node क्रम.
 * @child: Handle to one of the device's child nodes or a null handle.
 */
काष्ठा fwnode_handle *acpi_get_next_subnode(स्थिर काष्ठा fwnode_handle *fwnode,
					    काष्ठा fwnode_handle *child)
अणु
	स्थिर काष्ठा acpi_device *adev = to_acpi_device_node(fwnode);
	स्थिर काष्ठा list_head *head;
	काष्ठा list_head *next;

	अगर (!child || is_acpi_device_node(child)) अणु
		काष्ठा acpi_device *child_adev;

		अगर (adev)
			head = &adev->children;
		अन्यथा
			जाओ nondev;

		अगर (list_empty(head))
			जाओ nondev;

		अगर (child) अणु
			adev = to_acpi_device_node(child);
			next = adev->node.next;
			अगर (next == head) अणु
				child = शून्य;
				जाओ nondev;
			पूर्ण
			child_adev = list_entry(next, काष्ठा acpi_device, node);
		पूर्ण अन्यथा अणु
			child_adev = list_first_entry(head, काष्ठा acpi_device,
						      node);
		पूर्ण
		वापस acpi_fwnode_handle(child_adev);
	पूर्ण

 nondev:
	अगर (!child || is_acpi_data_node(child)) अणु
		स्थिर काष्ठा acpi_data_node *data = to_acpi_data_node(fwnode);
		काष्ठा acpi_data_node *dn;

		/*
		 * We can have a combination of device and data nodes, e.g. with
		 * hierarchical _DSD properties. Make sure the adev poपूर्णांकer is
		 * restored beक्रमe going through data nodes, otherwise we will
		 * be looking क्रम data_nodes below the last device found instead
		 * of the common fwnode shared by device_nodes and data_nodes.
		 */
		adev = to_acpi_device_node(fwnode);
		अगर (adev)
			head = &adev->data.subnodes;
		अन्यथा अगर (data)
			head = &data->data.subnodes;
		अन्यथा
			वापस शून्य;

		अगर (list_empty(head))
			वापस शून्य;

		अगर (child) अणु
			dn = to_acpi_data_node(child);
			next = dn->sibling.next;
			अगर (next == head)
				वापस शून्य;

			dn = list_entry(next, काष्ठा acpi_data_node, sibling);
		पूर्ण अन्यथा अणु
			dn = list_first_entry(head, काष्ठा acpi_data_node, sibling);
		पूर्ण
		वापस &dn->fwnode;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * acpi_node_get_parent - Return parent fwnode of this fwnode
 * @fwnode: Firmware node whose parent to get
 *
 * Returns parent node of an ACPI device or data firmware node or %शून्य अगर
 * not available.
 */
काष्ठा fwnode_handle *acpi_node_get_parent(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	अगर (is_acpi_data_node(fwnode)) अणु
		/* All data nodes have parent poपूर्णांकer so just वापस that */
		वापस to_acpi_data_node(fwnode)->parent;
	पूर्ण अन्यथा अगर (is_acpi_device_node(fwnode)) अणु
		acpi_handle handle, parent_handle;

		handle = to_acpi_device_node(fwnode)->handle;
		अगर (ACPI_SUCCESS(acpi_get_parent(handle, &parent_handle))) अणु
			काष्ठा acpi_device *adev;

			अगर (!acpi_bus_get_device(parent_handle, &adev))
				वापस acpi_fwnode_handle(adev);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Return true अगर the node is an ACPI graph node. Called on either ports
 * or endpoपूर्णांकs.
 */
अटल bool is_acpi_graph_node(काष्ठा fwnode_handle *fwnode,
			       स्थिर अक्षर *str)
अणु
	अचिन्हित पूर्णांक len = म_माप(str);
	स्थिर अक्षर *name;

	अगर (!len || !is_acpi_data_node(fwnode))
		वापस false;

	name = to_acpi_data_node(fwnode)->name;

	वापस (fwnode_property_present(fwnode, "reg") &&
		!म_भेदन(name, str, len) && name[len] == '@') ||
		fwnode_property_present(fwnode, str);
पूर्ण

/**
 * acpi_graph_get_next_endpoपूर्णांक - Get next endpoपूर्णांक ACPI firmware node
 * @fwnode: Poपूर्णांकer to the parent firmware node
 * @prev: Previous endpoपूर्णांक node or %शून्य to get the first
 *
 * Looks up next endpoपूर्णांक ACPI firmware node below a given @fwnode. Returns
 * %शून्य अगर there is no next endpoपूर्णांक or in हाल of error. In हाल of success
 * the next endpoपूर्णांक is वापसed.
 */
अटल काष्ठा fwnode_handle *acpi_graph_get_next_endpoपूर्णांक(
	स्थिर काष्ठा fwnode_handle *fwnode, काष्ठा fwnode_handle *prev)
अणु
	काष्ठा fwnode_handle *port = शून्य;
	काष्ठा fwnode_handle *endpoपूर्णांक;

	अगर (!prev) अणु
		करो अणु
			port = fwnode_get_next_child_node(fwnode, port);
			/*
			 * The names of the port nodes begin with "port@"
			 * followed by the number of the port node and they also
			 * have a "reg" property that also has the number of the
			 * port node. For compatibility reasons a node is also
			 * recognised as a port node from the "port" property.
			 */
			अगर (is_acpi_graph_node(port, "port"))
				अवरोध;
		पूर्ण जबतक (port);
	पूर्ण अन्यथा अणु
		port = fwnode_get_parent(prev);
	पूर्ण

	अगर (!port)
		वापस शून्य;

	endpoपूर्णांक = fwnode_get_next_child_node(port, prev);
	जबतक (!endpoपूर्णांक) अणु
		port = fwnode_get_next_child_node(fwnode, port);
		अगर (!port)
			अवरोध;
		अगर (is_acpi_graph_node(port, "port"))
			endpoपूर्णांक = fwnode_get_next_child_node(port, शून्य);
	पूर्ण

	/*
	 * The names of the endpoपूर्णांक nodes begin with "endpoint@" followed by
	 * the number of the endpoपूर्णांक node and they also have a "reg" property
	 * that also has the number of the endpoपूर्णांक node. For compatibility
	 * reasons a node is also recognised as an endpoपूर्णांक node from the
	 * "endpoint" property.
	 */
	अगर (!is_acpi_graph_node(endpoपूर्णांक, "endpoint"))
		वापस शून्य;

	वापस endpoपूर्णांक;
पूर्ण

/**
 * acpi_graph_get_child_prop_value - Return a child with a given property value
 * @fwnode: device fwnode
 * @prop_name: The name of the property to look क्रम
 * @val: the desired property value
 *
 * Return the port node corresponding to a given port number. Returns
 * the child node on success, शून्य otherwise.
 */
अटल काष्ठा fwnode_handle *acpi_graph_get_child_prop_value(
	स्थिर काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *prop_name,
	अचिन्हित पूर्णांक val)
अणु
	काष्ठा fwnode_handle *child;

	fwnode_क्रम_each_child_node(fwnode, child) अणु
		u32 nr;

		अगर (fwnode_property_पढ़ो_u32(child, prop_name, &nr))
			जारी;

		अगर (val == nr)
			वापस child;
	पूर्ण

	वापस शून्य;
पूर्ण


/**
 * acpi_graph_get_remote_endpoपूर्णांक - Parses and वापसs remote end of an endpoपूर्णांक
 * @__fwnode: Endpoपूर्णांक firmware node poपूर्णांकing to a remote device
 *
 * Returns the remote endpoपूर्णांक corresponding to @__fwnode. शून्य on error.
 */
अटल काष्ठा fwnode_handle *
acpi_graph_get_remote_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *__fwnode)
अणु
	काष्ठा fwnode_handle *fwnode;
	अचिन्हित पूर्णांक port_nr, endpoपूर्णांक_nr;
	काष्ठा fwnode_reference_args args;
	पूर्णांक ret;

	स_रखो(&args, 0, माप(args));
	ret = acpi_node_get_property_reference(__fwnode, "remote-endpoint", 0,
					       &args);
	अगर (ret)
		वापस शून्य;

	/* Direct endpoपूर्णांक reference? */
	अगर (!is_acpi_device_node(args.fwnode))
		वापस args.nargs ? शून्य : args.fwnode;

	/*
	 * Always require two arguments with the reference: port and
	 * endpoपूर्णांक indices.
	 */
	अगर (args.nargs != 2)
		वापस शून्य;

	fwnode = args.fwnode;
	port_nr = args.args[0];
	endpoपूर्णांक_nr = args.args[1];

	fwnode = acpi_graph_get_child_prop_value(fwnode, "port", port_nr);

	वापस acpi_graph_get_child_prop_value(fwnode, "endpoint", endpoपूर्णांक_nr);
पूर्ण

अटल bool acpi_fwnode_device_is_available(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	अगर (!is_acpi_device_node(fwnode))
		वापस false;

	वापस acpi_device_is_present(to_acpi_device_node(fwnode));
पूर्ण

अटल bool acpi_fwnode_property_present(स्थिर काष्ठा fwnode_handle *fwnode,
					 स्थिर अक्षर *propname)
अणु
	वापस !acpi_node_prop_get(fwnode, propname, शून्य);
पूर्ण

अटल पूर्णांक
acpi_fwnode_property_पढ़ो_पूर्णांक_array(स्थिर काष्ठा fwnode_handle *fwnode,
				    स्थिर अक्षर *propname,
				    अचिन्हित पूर्णांक elem_size, व्योम *val,
				    माप_प्रकार nval)
अणु
	क्रमागत dev_prop_type type;

	चयन (elem_size) अणु
	हाल माप(u8):
		type = DEV_PROP_U8;
		अवरोध;
	हाल माप(u16):
		type = DEV_PROP_U16;
		अवरोध;
	हाल माप(u32):
		type = DEV_PROP_U32;
		अवरोध;
	हाल माप(u64):
		type = DEV_PROP_U64;
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	वापस acpi_node_prop_पढ़ो(fwnode, propname, type, val, nval);
पूर्ण

अटल पूर्णांक
acpi_fwnode_property_पढ़ो_string_array(स्थिर काष्ठा fwnode_handle *fwnode,
				       स्थिर अक्षर *propname, स्थिर अक्षर **val,
				       माप_प्रकार nval)
अणु
	वापस acpi_node_prop_पढ़ो(fwnode, propname, DEV_PROP_STRING,
				   val, nval);
पूर्ण

अटल पूर्णांक
acpi_fwnode_get_reference_args(स्थिर काष्ठा fwnode_handle *fwnode,
			       स्थिर अक्षर *prop, स्थिर अक्षर *nargs_prop,
			       अचिन्हित पूर्णांक args_count, अचिन्हित पूर्णांक index,
			       काष्ठा fwnode_reference_args *args)
अणु
	वापस __acpi_node_get_property_reference(fwnode, prop, index,
						  args_count, args);
पूर्ण

अटल स्थिर अक्षर *acpi_fwnode_get_name(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर काष्ठा acpi_device *adev;
	काष्ठा fwnode_handle *parent;

	/* Is this the root node? */
	parent = fwnode_get_parent(fwnode);
	अगर (!parent)
		वापस "\\";

	fwnode_handle_put(parent);

	अगर (is_acpi_data_node(fwnode)) अणु
		स्थिर काष्ठा acpi_data_node *dn = to_acpi_data_node(fwnode);

		वापस dn->name;
	पूर्ण

	adev = to_acpi_device_node(fwnode);
	अगर (WARN_ON(!adev))
		वापस शून्य;

	वापस acpi_device_bid(adev);
पूर्ण

अटल स्थिर अक्षर *
acpi_fwnode_get_name_prefix(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *parent;

	/* Is this the root node? */
	parent = fwnode_get_parent(fwnode);
	अगर (!parent)
		वापस "";

	/* Is this 2nd node from the root? */
	parent = fwnode_get_next_parent(parent);
	अगर (!parent)
		वापस "";

	fwnode_handle_put(parent);

	/* ACPI device or data node. */
	वापस ".";
पूर्ण

अटल काष्ठा fwnode_handle *
acpi_fwnode_get_parent(काष्ठा fwnode_handle *fwnode)
अणु
	वापस acpi_node_get_parent(fwnode);
पूर्ण

अटल पूर्णांक acpi_fwnode_graph_parse_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
					    काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा fwnode_handle *port_fwnode = fwnode_get_parent(fwnode);

	endpoपूर्णांक->local_fwnode = fwnode;

	अगर (fwnode_property_पढ़ो_u32(port_fwnode, "reg", &endpoपूर्णांक->port))
		fwnode_property_पढ़ो_u32(port_fwnode, "port", &endpoपूर्णांक->port);
	अगर (fwnode_property_पढ़ो_u32(fwnode, "reg", &endpoपूर्णांक->id))
		fwnode_property_पढ़ो_u32(fwnode, "endpoint", &endpoपूर्णांक->id);

	वापस 0;
पूर्ण

अटल स्थिर व्योम *
acpi_fwnode_device_get_match_data(स्थिर काष्ठा fwnode_handle *fwnode,
				  स्थिर काष्ठा device *dev)
अणु
	वापस acpi_device_get_match_data(dev);
पूर्ण

#घोषणा DECLARE_ACPI_FWNODE_OPS(ops) \
	स्थिर काष्ठा fwnode_operations ops = अणु				\
		.device_is_available = acpi_fwnode_device_is_available, \
		.device_get_match_data = acpi_fwnode_device_get_match_data, \
		.property_present = acpi_fwnode_property_present,	\
		.property_पढ़ो_पूर्णांक_array =				\
			acpi_fwnode_property_पढ़ो_पूर्णांक_array,		\
		.property_पढ़ो_string_array =				\
			acpi_fwnode_property_पढ़ो_string_array,		\
		.get_parent = acpi_node_get_parent,			\
		.get_next_child_node = acpi_get_next_subnode,		\
		.get_named_child_node = acpi_fwnode_get_named_child_node, \
		.get_name = acpi_fwnode_get_name,			\
		.get_name_prefix = acpi_fwnode_get_name_prefix,		\
		.get_reference_args = acpi_fwnode_get_reference_args,	\
		.graph_get_next_endpoपूर्णांक =				\
			acpi_graph_get_next_endpoपूर्णांक,			\
		.graph_get_remote_endpoपूर्णांक =				\
			acpi_graph_get_remote_endpoपूर्णांक,			\
		.graph_get_port_parent = acpi_fwnode_get_parent,	\
		.graph_parse_endpoपूर्णांक = acpi_fwnode_graph_parse_endpoपूर्णांक, \
	पूर्ण;								\
	EXPORT_SYMBOL_GPL(ops)

DECLARE_ACPI_FWNODE_OPS(acpi_device_fwnode_ops);
DECLARE_ACPI_FWNODE_OPS(acpi_data_fwnode_ops);
स्थिर काष्ठा fwnode_operations acpi_अटल_fwnode_ops;

bool is_acpi_device_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस !IS_ERR_OR_शून्य(fwnode) &&
		fwnode->ops == &acpi_device_fwnode_ops;
पूर्ण
EXPORT_SYMBOL(is_acpi_device_node);

bool is_acpi_data_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस !IS_ERR_OR_शून्य(fwnode) && fwnode->ops == &acpi_data_fwnode_ops;
पूर्ण
EXPORT_SYMBOL(is_acpi_data_node);
