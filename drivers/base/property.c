<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * property.c - Unअगरied device property पूर्णांकerface.
 *
 * Copyright (C) 2014, Intel Corporation
 * Authors: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/property.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/phy.h>

काष्ठा fwnode_handle *dev_fwnode(काष्ठा device *dev)
अणु
	वापस IS_ENABLED(CONFIG_OF) && dev->of_node ?
		&dev->of_node->fwnode : dev->fwnode;
पूर्ण
EXPORT_SYMBOL_GPL(dev_fwnode);

/**
 * device_property_present - check अगर a property of a device is present
 * @dev: Device whose property is being checked
 * @propname: Name of the property
 *
 * Check अगर property @propname is present in the device firmware description.
 */
bool device_property_present(काष्ठा device *dev, स्थिर अक्षर *propname)
अणु
	वापस fwnode_property_present(dev_fwnode(dev), propname);
पूर्ण
EXPORT_SYMBOL_GPL(device_property_present);

/**
 * fwnode_property_present - check अगर a property of a firmware node is present
 * @fwnode: Firmware node whose property to check
 * @propname: Name of the property
 */
bool fwnode_property_present(स्थिर काष्ठा fwnode_handle *fwnode,
			     स्थिर अक्षर *propname)
अणु
	bool ret;

	ret = fwnode_call_bool_op(fwnode, property_present, propname);
	अगर (ret == false && !IS_ERR_OR_शून्य(fwnode) &&
	    !IS_ERR_OR_शून्य(fwnode->secondary))
		ret = fwnode_call_bool_op(fwnode->secondary, property_present,
					 propname);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_present);

/**
 * device_property_पढ़ो_u8_array - वापस a u8 array property of a device
 * @dev: Device to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Function पढ़ोs an array of u8 properties with @propname from the device
 * firmware description and stores them to @val अगर found.
 *
 * Return: number of values अगर @val was %शून्य,
 *         %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of numbers,
 *	   %-EOVERFLOW अगर the size of the property is not as expected.
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक device_property_पढ़ो_u8_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				  u8 *val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_u8_array(dev_fwnode(dev), propname, val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(device_property_पढ़ो_u8_array);

/**
 * device_property_पढ़ो_u16_array - वापस a u16 array property of a device
 * @dev: Device to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Function पढ़ोs an array of u16 properties with @propname from the device
 * firmware description and stores them to @val अगर found.
 *
 * Return: number of values अगर @val was %शून्य,
 *         %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of numbers,
 *	   %-EOVERFLOW अगर the size of the property is not as expected.
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक device_property_पढ़ो_u16_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				   u16 *val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_u16_array(dev_fwnode(dev), propname, val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(device_property_पढ़ो_u16_array);

/**
 * device_property_पढ़ो_u32_array - वापस a u32 array property of a device
 * @dev: Device to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Function पढ़ोs an array of u32 properties with @propname from the device
 * firmware description and stores them to @val अगर found.
 *
 * Return: number of values अगर @val was %शून्य,
 *         %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of numbers,
 *	   %-EOVERFLOW अगर the size of the property is not as expected.
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक device_property_पढ़ो_u32_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				   u32 *val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_u32_array(dev_fwnode(dev), propname, val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(device_property_पढ़ो_u32_array);

/**
 * device_property_पढ़ो_u64_array - वापस a u64 array property of a device
 * @dev: Device to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Function पढ़ोs an array of u64 properties with @propname from the device
 * firmware description and stores them to @val अगर found.
 *
 * Return: number of values अगर @val was %शून्य,
 *         %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of numbers,
 *	   %-EOVERFLOW अगर the size of the property is not as expected.
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक device_property_पढ़ो_u64_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				   u64 *val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_u64_array(dev_fwnode(dev), propname, val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(device_property_पढ़ो_u64_array);

/**
 * device_property_पढ़ो_string_array - वापस a string array property of device
 * @dev: Device to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Function पढ़ोs an array of string properties with @propname from the device
 * firmware description and stores them to @val अगर found.
 *
 * Return: number of values पढ़ो on success अगर @val is non-शून्य,
 *	   number of values available on success अगर @val is शून्य,
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO or %-EILSEQ अगर the property is not an array of strings,
 *	   %-EOVERFLOW अगर the size of the property is not as expected.
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक device_property_पढ़ो_string_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				      स्थिर अक्षर **val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_string_array(dev_fwnode(dev), propname, val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(device_property_पढ़ो_string_array);

/**
 * device_property_पढ़ो_string - वापस a string property of a device
 * @dev: Device to get the property of
 * @propname: Name of the property
 * @val: The value is stored here
 *
 * Function पढ़ोs property @propname from the device firmware description and
 * stores the value पूर्णांकo @val अगर found. The value is checked to be a string.
 *
 * Return: %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO or %-EILSEQ अगर the property type is not a string.
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक device_property_पढ़ो_string(काष्ठा device *dev, स्थिर अक्षर *propname,
				स्थिर अक्षर **val)
अणु
	वापस fwnode_property_पढ़ो_string(dev_fwnode(dev), propname, val);
पूर्ण
EXPORT_SYMBOL_GPL(device_property_पढ़ो_string);

/**
 * device_property_match_string - find a string in an array and वापस index
 * @dev: Device to get the property of
 * @propname: Name of the property holding the array
 * @string: String to look क्रम
 *
 * Find a given string in a string array and अगर it is found वापस the
 * index back.
 *
 * Return: %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of strings,
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक device_property_match_string(काष्ठा device *dev, स्थिर अक्षर *propname,
				 स्थिर अक्षर *string)
अणु
	वापस fwnode_property_match_string(dev_fwnode(dev), propname, string);
पूर्ण
EXPORT_SYMBOL_GPL(device_property_match_string);

अटल पूर्णांक fwnode_property_पढ़ो_पूर्णांक_array(स्थिर काष्ठा fwnode_handle *fwnode,
					  स्थिर अक्षर *propname,
					  अचिन्हित पूर्णांक elem_size, व्योम *val,
					  माप_प्रकार nval)
अणु
	पूर्णांक ret;

	ret = fwnode_call_पूर्णांक_op(fwnode, property_पढ़ो_पूर्णांक_array, propname,
				 elem_size, val, nval);
	अगर (ret == -EINVAL && !IS_ERR_OR_शून्य(fwnode) &&
	    !IS_ERR_OR_शून्य(fwnode->secondary))
		ret = fwnode_call_पूर्णांक_op(
			fwnode->secondary, property_पढ़ो_पूर्णांक_array, propname,
			elem_size, val, nval);

	वापस ret;
पूर्ण

/**
 * fwnode_property_पढ़ो_u8_array - वापस a u8 array property of firmware node
 * @fwnode: Firmware node to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Read an array of u8 properties with @propname from @fwnode and stores them to
 * @val अगर found.
 *
 * Return: number of values अगर @val was %शून्य,
 *         %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of numbers,
 *	   %-EOVERFLOW अगर the size of the property is not as expected,
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक fwnode_property_पढ़ो_u8_array(स्थिर काष्ठा fwnode_handle *fwnode,
				  स्थिर अक्षर *propname, u8 *val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_पूर्णांक_array(fwnode, propname, माप(u8),
					      val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_पढ़ो_u8_array);

/**
 * fwnode_property_पढ़ो_u16_array - वापस a u16 array property of firmware node
 * @fwnode: Firmware node to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Read an array of u16 properties with @propname from @fwnode and store them to
 * @val अगर found.
 *
 * Return: number of values अगर @val was %शून्य,
 *         %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of numbers,
 *	   %-EOVERFLOW अगर the size of the property is not as expected,
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक fwnode_property_पढ़ो_u16_array(स्थिर काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *propname, u16 *val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_पूर्णांक_array(fwnode, propname, माप(u16),
					      val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_पढ़ो_u16_array);

/**
 * fwnode_property_पढ़ो_u32_array - वापस a u32 array property of firmware node
 * @fwnode: Firmware node to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Read an array of u32 properties with @propname from @fwnode store them to
 * @val अगर found.
 *
 * Return: number of values अगर @val was %शून्य,
 *         %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of numbers,
 *	   %-EOVERFLOW अगर the size of the property is not as expected,
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक fwnode_property_पढ़ो_u32_array(स्थिर काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *propname, u32 *val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_पूर्णांक_array(fwnode, propname, माप(u32),
					      val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_पढ़ो_u32_array);

/**
 * fwnode_property_पढ़ो_u64_array - वापस a u64 array property firmware node
 * @fwnode: Firmware node to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Read an array of u64 properties with @propname from @fwnode and store them to
 * @val अगर found.
 *
 * Return: number of values अगर @val was %शून्य,
 *         %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of numbers,
 *	   %-EOVERFLOW अगर the size of the property is not as expected,
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक fwnode_property_पढ़ो_u64_array(स्थिर काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *propname, u64 *val, माप_प्रकार nval)
अणु
	वापस fwnode_property_पढ़ो_पूर्णांक_array(fwnode, propname, माप(u64),
					      val, nval);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_पढ़ो_u64_array);

/**
 * fwnode_property_पढ़ो_string_array - वापस string array property of a node
 * @fwnode: Firmware node to get the property of
 * @propname: Name of the property
 * @val: The values are stored here or %शून्य to वापस the number of values
 * @nval: Size of the @val array
 *
 * Read an string list property @propname from the given firmware node and store
 * them to @val अगर found.
 *
 * Return: number of values पढ़ो on success अगर @val is non-शून्य,
 *	   number of values available on success अगर @val is शून्य,
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO or %-EILSEQ अगर the property is not an array of strings,
 *	   %-EOVERFLOW अगर the size of the property is not as expected,
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक fwnode_property_पढ़ो_string_array(स्थिर काष्ठा fwnode_handle *fwnode,
				      स्थिर अक्षर *propname, स्थिर अक्षर **val,
				      माप_प्रकार nval)
अणु
	पूर्णांक ret;

	ret = fwnode_call_पूर्णांक_op(fwnode, property_पढ़ो_string_array, propname,
				 val, nval);
	अगर (ret == -EINVAL && !IS_ERR_OR_शून्य(fwnode) &&
	    !IS_ERR_OR_शून्य(fwnode->secondary))
		ret = fwnode_call_पूर्णांक_op(fwnode->secondary,
					 property_पढ़ो_string_array, propname,
					 val, nval);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_पढ़ो_string_array);

/**
 * fwnode_property_पढ़ो_string - वापस a string property of a firmware node
 * @fwnode: Firmware node to get the property of
 * @propname: Name of the property
 * @val: The value is stored here
 *
 * Read property @propname from the given firmware node and store the value पूर्णांकo
 * @val अगर found.  The value is checked to be a string.
 *
 * Return: %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO or %-EILSEQ अगर the property is not a string,
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक fwnode_property_पढ़ो_string(स्थिर काष्ठा fwnode_handle *fwnode,
				स्थिर अक्षर *propname, स्थिर अक्षर **val)
अणु
	पूर्णांक ret = fwnode_property_पढ़ो_string_array(fwnode, propname, val, 1);

	वापस ret < 0 ? ret : 0;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_पढ़ो_string);

/**
 * fwnode_property_match_string - find a string in an array and वापस index
 * @fwnode: Firmware node to get the property of
 * @propname: Name of the property holding the array
 * @string: String to look क्रम
 *
 * Find a given string in a string array and अगर it is found वापस the
 * index back.
 *
 * Return: %0 अगर the property was found (success),
 *	   %-EINVAL अगर given arguments are not valid,
 *	   %-ENODATA अगर the property करोes not have a value,
 *	   %-EPROTO अगर the property is not an array of strings,
 *	   %-ENXIO अगर no suitable firmware पूर्णांकerface is present.
 */
पूर्णांक fwnode_property_match_string(स्थिर काष्ठा fwnode_handle *fwnode,
	स्थिर अक्षर *propname, स्थिर अक्षर *string)
अणु
	स्थिर अक्षर **values;
	पूर्णांक nval, ret;

	nval = fwnode_property_पढ़ो_string_array(fwnode, propname, शून्य, 0);
	अगर (nval < 0)
		वापस nval;

	अगर (nval == 0)
		वापस -ENODATA;

	values = kसुस्मृति(nval, माप(*values), GFP_KERNEL);
	अगर (!values)
		वापस -ENOMEM;

	ret = fwnode_property_पढ़ो_string_array(fwnode, propname, values, nval);
	अगर (ret < 0)
		जाओ out;

	ret = match_string(values, nval, string);
	अगर (ret < 0)
		ret = -ENODATA;
out:
	kमुक्त(values);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_match_string);

/**
 * fwnode_property_get_reference_args() - Find a reference with arguments
 * @fwnode:	Firmware node where to look क्रम the reference
 * @prop:	The name of the property
 * @nargs_prop:	The name of the property telling the number of
 *		arguments in the referred node. शून्य अगर @nargs is known,
 *		otherwise @nargs is ignored. Only relevant on OF.
 * @nargs:	Number of arguments. Ignored अगर @nargs_prop is non-शून्य.
 * @index:	Index of the reference, from zero onwards.
 * @args:	Result काष्ठाure with reference and पूर्णांकeger arguments.
 *
 * Obtain a reference based on a named property in an fwnode, with
 * पूर्णांकeger arguments.
 *
 * Caller is responsible to call fwnode_handle_put() on the वापसed
 * args->fwnode poपूर्णांकer.
 *
 * Returns: %0 on success
 *	    %-ENOENT when the index is out of bounds, the index has an empty
 *		     reference or the property was not found
 *	    %-EINVAL on parse error
 */
पूर्णांक fwnode_property_get_reference_args(स्थिर काष्ठा fwnode_handle *fwnode,
				       स्थिर अक्षर *prop, स्थिर अक्षर *nargs_prop,
				       अचिन्हित पूर्णांक nargs, अचिन्हित पूर्णांक index,
				       काष्ठा fwnode_reference_args *args)
अणु
	वापस fwnode_call_पूर्णांक_op(fwnode, get_reference_args, prop, nargs_prop,
				  nargs, index, args);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_property_get_reference_args);

/**
 * fwnode_find_reference - Find named reference to a fwnode_handle
 * @fwnode: Firmware node where to look क्रम the reference
 * @name: The name of the reference
 * @index: Index of the reference
 *
 * @index can be used when the named reference holds a table of references.
 *
 * Returns poपूर्णांकer to the reference fwnode, or ERR_PTR. Caller is responsible to
 * call fwnode_handle_put() on the वापसed fwnode poपूर्णांकer.
 */
काष्ठा fwnode_handle *fwnode_find_reference(स्थिर काष्ठा fwnode_handle *fwnode,
					    स्थिर अक्षर *name,
					    अचिन्हित पूर्णांक index)
अणु
	काष्ठा fwnode_reference_args args;
	पूर्णांक ret;

	ret = fwnode_property_get_reference_args(fwnode, name, शून्य, 0, index,
						 &args);
	वापस ret ? ERR_PTR(ret) : args.fwnode;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_find_reference);

/**
 * device_हटाओ_properties - Remove properties from a device object.
 * @dev: Device whose properties to हटाओ.
 *
 * The function हटाओs properties previously associated to the device
 * firmware node with device_add_properties(). Memory allocated to the
 * properties will also be released.
 */
व्योम device_हटाओ_properties(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);

	अगर (!fwnode)
		वापस;

	अगर (is_software_node(fwnode->secondary)) अणु
		fwnode_हटाओ_software_node(fwnode->secondary);
		set_secondary_fwnode(dev, शून्य);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(device_हटाओ_properties);

/**
 * device_add_properties - Add a collection of properties to a device object.
 * @dev: Device to add properties to.
 * @properties: Collection of properties to add.
 *
 * Associate a collection of device properties represented by @properties with
 * @dev. The function takes a copy of @properties.
 *
 * WARNING: The callers should not use this function अगर it is known that there
 * is no real firmware node associated with @dev! In that हाल the callers
 * should create a software node and assign it to @dev directly.
 */
पूर्णांक device_add_properties(काष्ठा device *dev,
			  स्थिर काष्ठा property_entry *properties)
अणु
	काष्ठा fwnode_handle *fwnode;

	fwnode = fwnode_create_software_node(properties, शून्य);
	अगर (IS_ERR(fwnode))
		वापस PTR_ERR(fwnode);

	set_secondary_fwnode(dev, fwnode);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(device_add_properties);

/**
 * fwnode_get_name - Return the name of a node
 * @fwnode: The firmware node
 *
 * Returns a poपूर्णांकer to the node name.
 */
स्थिर अक्षर *fwnode_get_name(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस fwnode_call_ptr_op(fwnode, get_name);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_name);

/**
 * fwnode_get_name_prefix - Return the prefix of node क्रम prपूर्णांकing purposes
 * @fwnode: The firmware node
 *
 * Returns the prefix of a node, पूर्णांकended to be prपूर्णांकed right beक्रमe the node.
 * The prefix works also as a separator between the nodes.
 */
स्थिर अक्षर *fwnode_get_name_prefix(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस fwnode_call_ptr_op(fwnode, get_name_prefix);
पूर्ण

/**
 * fwnode_get_parent - Return parent firwmare node
 * @fwnode: Firmware whose parent is retrieved
 *
 * Return parent firmware node of the given node अगर possible or %शून्य अगर no
 * parent was available.
 */
काष्ठा fwnode_handle *fwnode_get_parent(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस fwnode_call_ptr_op(fwnode, get_parent);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_parent);

/**
 * fwnode_get_next_parent - Iterate to the node's parent
 * @fwnode: Firmware whose parent is retrieved
 *
 * This is like fwnode_get_parent() except that it drops the refcount
 * on the passed node, making it suitable क्रम iterating through a
 * node's parents.
 *
 * Returns a node poपूर्णांकer with refcount incremented, use
 * fwnode_handle_node() on it when करोne.
 */
काष्ठा fwnode_handle *fwnode_get_next_parent(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *parent = fwnode_get_parent(fwnode);

	fwnode_handle_put(fwnode);

	वापस parent;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_next_parent);

/**
 * fwnode_get_next_parent_dev - Find device of बंदst ancestor fwnode
 * @fwnode: firmware node
 *
 * Given a firmware node (@fwnode), this function finds its बंदst ancestor
 * firmware node that has a corresponding काष्ठा device and वापसs that काष्ठा
 * device.
 *
 * The caller of this function is expected to call put_device() on the वापसed
 * device when they are करोne.
 */
काष्ठा device *fwnode_get_next_parent_dev(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev = शून्य;

	fwnode_handle_get(fwnode);
	करो अणु
		fwnode = fwnode_get_next_parent(fwnode);
		अगर (fwnode)
			dev = get_dev_from_fwnode(fwnode);
	पूर्ण जबतक (fwnode && !dev);
	fwnode_handle_put(fwnode);
	वापस dev;
पूर्ण

/**
 * fwnode_count_parents - Return the number of parents a node has
 * @fwnode: The node the parents of which are to be counted
 *
 * Returns the number of parents a node has.
 */
अचिन्हित पूर्णांक fwnode_count_parents(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *__fwnode;
	अचिन्हित पूर्णांक count;

	__fwnode = fwnode_get_parent(fwnode);

	क्रम (count = 0; __fwnode; count++)
		__fwnode = fwnode_get_next_parent(__fwnode);

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_count_parents);

/**
 * fwnode_get_nth_parent - Return an nth parent of a node
 * @fwnode: The node the parent of which is requested
 * @depth: Distance of the parent from the node
 *
 * Returns the nth parent of a node. If there is no parent at the requested
 * @depth, %शून्य is वापसed. If @depth is 0, the functionality is equivalent to
 * fwnode_handle_get(). For @depth == 1, it is fwnode_get_parent() and so on.
 *
 * The caller is responsible क्रम calling fwnode_handle_put() क्रम the वापसed
 * node.
 */
काष्ठा fwnode_handle *fwnode_get_nth_parent(काष्ठा fwnode_handle *fwnode,
					    अचिन्हित पूर्णांक depth)
अणु
	अचिन्हित पूर्णांक i;

	fwnode_handle_get(fwnode);

	क्रम (i = 0; i < depth && fwnode; i++)
		fwnode = fwnode_get_next_parent(fwnode);

	वापस fwnode;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_nth_parent);

/**
 * fwnode_is_ancestor_of - Test अगर @test_ancestor is ancestor of @test_child
 * @test_ancestor: Firmware which is tested क्रम being an ancestor
 * @test_child: Firmware which is tested क्रम being the child
 *
 * A node is considered an ancestor of itself too.
 *
 * Returns true अगर @test_ancestor is an ancestor of @test_child.
 * Otherwise, वापसs false.
 */
bool fwnode_is_ancestor_of(काष्ठा fwnode_handle *test_ancestor,
				  काष्ठा fwnode_handle *test_child)
अणु
	अगर (!test_ancestor)
		वापस false;

	fwnode_handle_get(test_child);
	जबतक (test_child) अणु
		अगर (test_child == test_ancestor) अणु
			fwnode_handle_put(test_child);
			वापस true;
		पूर्ण
		test_child = fwnode_get_next_parent(test_child);
	पूर्ण
	वापस false;
पूर्ण

/**
 * fwnode_get_next_child_node - Return the next child node handle क्रम a node
 * @fwnode: Firmware node to find the next child node क्रम.
 * @child: Handle to one of the node's child nodes or a %शून्य handle.
 */
काष्ठा fwnode_handle *
fwnode_get_next_child_node(स्थिर काष्ठा fwnode_handle *fwnode,
			   काष्ठा fwnode_handle *child)
अणु
	वापस fwnode_call_ptr_op(fwnode, get_next_child_node, child);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_next_child_node);

/**
 * fwnode_get_next_available_child_node - Return the next
 * available child node handle क्रम a node
 * @fwnode: Firmware node to find the next child node क्रम.
 * @child: Handle to one of the node's child nodes or a %शून्य handle.
 */
काष्ठा fwnode_handle *
fwnode_get_next_available_child_node(स्थिर काष्ठा fwnode_handle *fwnode,
				     काष्ठा fwnode_handle *child)
अणु
	काष्ठा fwnode_handle *next_child = child;

	अगर (!fwnode)
		वापस शून्य;

	करो अणु
		next_child = fwnode_get_next_child_node(fwnode, next_child);

		अगर (!next_child || fwnode_device_is_available(next_child))
			अवरोध;
	पूर्ण जबतक (next_child);

	वापस next_child;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_next_available_child_node);

/**
 * device_get_next_child_node - Return the next child node handle क्रम a device
 * @dev: Device to find the next child node क्रम.
 * @child: Handle to one of the device's child nodes or a null handle.
 */
काष्ठा fwnode_handle *device_get_next_child_node(काष्ठा device *dev,
						 काष्ठा fwnode_handle *child)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	काष्ठा fwnode_handle *fwnode = शून्य, *next;

	अगर (dev->of_node)
		fwnode = &dev->of_node->fwnode;
	अन्यथा अगर (adev)
		fwnode = acpi_fwnode_handle(adev);

	/* Try to find a child in primary fwnode */
	next = fwnode_get_next_child_node(fwnode, child);
	अगर (next)
		वापस next;

	/* When no more children in primary, जारी with secondary */
	अगर (fwnode && !IS_ERR_OR_शून्य(fwnode->secondary))
		next = fwnode_get_next_child_node(fwnode->secondary, child);

	वापस next;
पूर्ण
EXPORT_SYMBOL_GPL(device_get_next_child_node);

/**
 * fwnode_get_named_child_node - Return first matching named child node handle
 * @fwnode: Firmware node to find the named child node क्रम.
 * @childname: String to match child node name against.
 */
काष्ठा fwnode_handle *
fwnode_get_named_child_node(स्थिर काष्ठा fwnode_handle *fwnode,
			    स्थिर अक्षर *childname)
अणु
	वापस fwnode_call_ptr_op(fwnode, get_named_child_node, childname);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_named_child_node);

/**
 * device_get_named_child_node - Return first matching named child node handle
 * @dev: Device to find the named child node क्रम.
 * @childname: String to match child node name against.
 */
काष्ठा fwnode_handle *device_get_named_child_node(काष्ठा device *dev,
						  स्थिर अक्षर *childname)
अणु
	वापस fwnode_get_named_child_node(dev_fwnode(dev), childname);
पूर्ण
EXPORT_SYMBOL_GPL(device_get_named_child_node);

/**
 * fwnode_handle_get - Obtain a reference to a device node
 * @fwnode: Poपूर्णांकer to the device node to obtain the reference to.
 *
 * Returns the fwnode handle.
 */
काष्ठा fwnode_handle *fwnode_handle_get(काष्ठा fwnode_handle *fwnode)
अणु
	अगर (!fwnode_has_op(fwnode, get))
		वापस fwnode;

	वापस fwnode_call_ptr_op(fwnode, get);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_handle_get);

/**
 * fwnode_handle_put - Drop reference to a device node
 * @fwnode: Poपूर्णांकer to the device node to drop the reference to.
 *
 * This has to be used when terminating device_क्रम_each_child_node() iteration
 * with अवरोध or वापस to prevent stale device node references from being left
 * behind.
 */
व्योम fwnode_handle_put(काष्ठा fwnode_handle *fwnode)
अणु
	fwnode_call_व्योम_op(fwnode, put);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_handle_put);

/**
 * fwnode_device_is_available - check अगर a device is available क्रम use
 * @fwnode: Poपूर्णांकer to the fwnode of the device.
 *
 * For fwnode node types that करोn't implement the .device_is_available()
 * operation, this function वापसs true.
 */
bool fwnode_device_is_available(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	अगर (!fwnode_has_op(fwnode, device_is_available))
		वापस true;

	वापस fwnode_call_bool_op(fwnode, device_is_available);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_device_is_available);

/**
 * device_get_child_node_count - वापस the number of child nodes क्रम device
 * @dev: Device to cound the child nodes क्रम
 */
अचिन्हित पूर्णांक device_get_child_node_count(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *child;
	अचिन्हित पूर्णांक count = 0;

	device_क्रम_each_child_node(dev, child)
		count++;

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(device_get_child_node_count);

bool device_dma_supported(काष्ठा device *dev)
अणु
	/* For DT, this is always supported.
	 * For ACPI, this depends on CCA, which
	 * is determined by the acpi_dma_supported().
	 */
	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node)
		वापस true;

	वापस acpi_dma_supported(ACPI_COMPANION(dev));
पूर्ण
EXPORT_SYMBOL_GPL(device_dma_supported);

क्रमागत dev_dma_attr device_get_dma_attr(काष्ठा device *dev)
अणु
	क्रमागत dev_dma_attr attr = DEV_DMA_NOT_SUPPORTED;

	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node) अणु
		अगर (of_dma_is_coherent(dev->of_node))
			attr = DEV_DMA_COHERENT;
		अन्यथा
			attr = DEV_DMA_NON_COHERENT;
	पूर्ण अन्यथा
		attr = acpi_get_dma_attr(ACPI_COMPANION(dev));

	वापस attr;
पूर्ण
EXPORT_SYMBOL_GPL(device_get_dma_attr);

/**
 * fwnode_get_phy_mode - Get phy mode क्रम given firmware node
 * @fwnode:	Poपूर्णांकer to the given node
 *
 * The function माला_लो phy पूर्णांकerface string from property 'phy-mode' or
 * 'phy-connection-type', and वापस its index in phy_modes table, or त्रुटि_सं in
 * error हाल.
 */
पूर्णांक fwnode_get_phy_mode(काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर अक्षर *pm;
	पूर्णांक err, i;

	err = fwnode_property_पढ़ो_string(fwnode, "phy-mode", &pm);
	अगर (err < 0)
		err = fwnode_property_पढ़ो_string(fwnode,
						  "phy-connection-type", &pm);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < PHY_INTERFACE_MODE_MAX; i++)
		अगर (!strहालcmp(pm, phy_modes(i)))
			वापस i;

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_phy_mode);

/**
 * device_get_phy_mode - Get phy mode क्रम given device
 * @dev:	Poपूर्णांकer to the given device
 *
 * The function माला_लो phy पूर्णांकerface string from property 'phy-mode' or
 * 'phy-connection-type', and वापस its index in phy_modes table, or त्रुटि_सं in
 * error हाल.
 */
पूर्णांक device_get_phy_mode(काष्ठा device *dev)
अणु
	वापस fwnode_get_phy_mode(dev_fwnode(dev));
पूर्ण
EXPORT_SYMBOL_GPL(device_get_phy_mode);

अटल व्योम *fwnode_get_mac_addr(काष्ठा fwnode_handle *fwnode,
				 स्थिर अक्षर *name, अक्षर *addr,
				 पूर्णांक alen)
अणु
	पूर्णांक ret = fwnode_property_पढ़ो_u8_array(fwnode, name, addr, alen);

	अगर (ret == 0 && alen == ETH_ALEN && is_valid_ether_addr(addr))
		वापस addr;
	वापस शून्य;
पूर्ण

/**
 * fwnode_get_mac_address - Get the MAC from the firmware node
 * @fwnode:	Poपूर्णांकer to the firmware node
 * @addr:	Address of buffer to store the MAC in
 * @alen:	Length of the buffer poपूर्णांकed to by addr, should be ETH_ALEN
 *
 * Search the firmware node क्रम the best MAC address to use.  'mac-address' is
 * checked first, because that is supposed to contain to "most recent" MAC
 * address. If that isn't set, then 'local-mac-address' is checked next,
 * because that is the शेष address.  If that isn't set, then the obsolete
 * 'address' is checked, just in case we're using an old device tree.
 *
 * Note that the 'address' property is supposed to contain a भव address of
 * the रेजिस्टर set, but some DTS files have redefined that property to be the
 * MAC address.
 *
 * All-zero MAC addresses are rejected, because those could be properties that
 * exist in the firmware tables, but were not updated by the firmware.  For
 * example, the DTS could define 'mac-address' and 'local-mac-address', with
 * zero MAC addresses.  Some older U-Boots only initialized 'local-mac-address'.
 * In this हाल, the real MAC is in 'local-mac-address', and 'mac-address'
 * exists but is all zeros.
*/
व्योम *fwnode_get_mac_address(काष्ठा fwnode_handle *fwnode, अक्षर *addr, पूर्णांक alen)
अणु
	अक्षर *res;

	res = fwnode_get_mac_addr(fwnode, "mac-address", addr, alen);
	अगर (res)
		वापस res;

	res = fwnode_get_mac_addr(fwnode, "local-mac-address", addr, alen);
	अगर (res)
		वापस res;

	वापस fwnode_get_mac_addr(fwnode, "address", addr, alen);
पूर्ण
EXPORT_SYMBOL(fwnode_get_mac_address);

/**
 * device_get_mac_address - Get the MAC क्रम a given device
 * @dev:	Poपूर्णांकer to the device
 * @addr:	Address of buffer to store the MAC in
 * @alen:	Length of the buffer poपूर्णांकed to by addr, should be ETH_ALEN
 */
व्योम *device_get_mac_address(काष्ठा device *dev, अक्षर *addr, पूर्णांक alen)
अणु
	वापस fwnode_get_mac_address(dev_fwnode(dev), addr, alen);
पूर्ण
EXPORT_SYMBOL(device_get_mac_address);

/**
 * fwnode_irq_get - Get IRQ directly from a fwnode
 * @fwnode:	Poपूर्णांकer to the firmware node
 * @index:	Zero-based index of the IRQ
 *
 * Returns Linux IRQ number on success. Other values are determined
 * accordingly to acpi_/of_ irq_get() operation.
 */
पूर्णांक fwnode_irq_get(काष्ठा fwnode_handle *fwnode, अचिन्हित पूर्णांक index)
अणु
	काष्ठा device_node *of_node = to_of_node(fwnode);
	काष्ठा resource res;
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_OF) && of_node)
		वापस of_irq_get(of_node, index);

	ret = acpi_irq_get(ACPI_HANDLE_FWNODE(fwnode), index, &res);
	अगर (ret)
		वापस ret;

	वापस res.start;
पूर्ण
EXPORT_SYMBOL(fwnode_irq_get);

/**
 * fwnode_graph_get_next_endpoपूर्णांक - Get next endpoपूर्णांक firmware node
 * @fwnode: Poपूर्णांकer to the parent firmware node
 * @prev: Previous endpoपूर्णांक node or %शून्य to get the first
 *
 * Returns an endpoपूर्णांक firmware node poपूर्णांकer or %शून्य अगर no more endpoपूर्णांकs
 * are available.
 */
काष्ठा fwnode_handle *
fwnode_graph_get_next_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
			       काष्ठा fwnode_handle *prev)
अणु
	वापस fwnode_call_ptr_op(fwnode, graph_get_next_endpoपूर्णांक, prev);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_graph_get_next_endpoपूर्णांक);

/**
 * fwnode_graph_get_port_parent - Return the device fwnode of a port endpoपूर्णांक
 * @endpoपूर्णांक: Endpoपूर्णांक firmware node of the port
 *
 * Return: the firmware node of the device the @endpoपूर्णांक beदीर्घs to.
 */
काष्ठा fwnode_handle *
fwnode_graph_get_port_parent(स्थिर काष्ठा fwnode_handle *endpoपूर्णांक)
अणु
	काष्ठा fwnode_handle *port, *parent;

	port = fwnode_get_parent(endpoपूर्णांक);
	parent = fwnode_call_ptr_op(port, graph_get_port_parent);

	fwnode_handle_put(port);

	वापस parent;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_graph_get_port_parent);

/**
 * fwnode_graph_get_remote_port_parent - Return fwnode of a remote device
 * @fwnode: Endpoपूर्णांक firmware node poपूर्णांकing to the remote endpoपूर्णांक
 *
 * Extracts firmware node of a remote device the @fwnode poपूर्णांकs to.
 */
काष्ठा fwnode_handle *
fwnode_graph_get_remote_port_parent(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *endpoपूर्णांक, *parent;

	endpoपूर्णांक = fwnode_graph_get_remote_endpoपूर्णांक(fwnode);
	parent = fwnode_graph_get_port_parent(endpoपूर्णांक);

	fwnode_handle_put(endpoपूर्णांक);

	वापस parent;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_graph_get_remote_port_parent);

/**
 * fwnode_graph_get_remote_port - Return fwnode of a remote port
 * @fwnode: Endpoपूर्णांक firmware node poपूर्णांकing to the remote endpoपूर्णांक
 *
 * Extracts firmware node of a remote port the @fwnode poपूर्णांकs to.
 */
काष्ठा fwnode_handle *
fwnode_graph_get_remote_port(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस fwnode_get_next_parent(fwnode_graph_get_remote_endpoपूर्णांक(fwnode));
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_graph_get_remote_port);

/**
 * fwnode_graph_get_remote_endpoपूर्णांक - Return fwnode of a remote endpoपूर्णांक
 * @fwnode: Endpoपूर्णांक firmware node poपूर्णांकing to the remote endpoपूर्णांक
 *
 * Extracts firmware node of a remote endpoपूर्णांक the @fwnode poपूर्णांकs to.
 */
काष्ठा fwnode_handle *
fwnode_graph_get_remote_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस fwnode_call_ptr_op(fwnode, graph_get_remote_endpoपूर्णांक);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_graph_get_remote_endpoपूर्णांक);

/**
 * fwnode_graph_get_remote_node - get remote parent node क्रम given port/endpoपूर्णांक
 * @fwnode: poपूर्णांकer to parent fwnode_handle containing graph port/endpoपूर्णांक
 * @port_id: identअगरier of the parent port node
 * @endpoपूर्णांक_id: identअगरier of the endpoपूर्णांक node
 *
 * Return: Remote fwnode handle associated with remote endpoपूर्णांक node linked
 *	   to @node. Use fwnode_node_put() on it when करोne.
 */
काष्ठा fwnode_handle *
fwnode_graph_get_remote_node(स्थिर काष्ठा fwnode_handle *fwnode, u32 port_id,
			     u32 endpoपूर्णांक_id)
अणु
	काष्ठा fwnode_handle *endpoपूर्णांक = शून्य;

	जबतक ((endpoपूर्णांक = fwnode_graph_get_next_endpoपूर्णांक(fwnode, endpoपूर्णांक))) अणु
		काष्ठा fwnode_endpoपूर्णांक fwnode_ep;
		काष्ठा fwnode_handle *remote;
		पूर्णांक ret;

		ret = fwnode_graph_parse_endpoपूर्णांक(endpoपूर्णांक, &fwnode_ep);
		अगर (ret < 0)
			जारी;

		अगर (fwnode_ep.port != port_id || fwnode_ep.id != endpoपूर्णांक_id)
			जारी;

		remote = fwnode_graph_get_remote_port_parent(endpoपूर्णांक);
		अगर (!remote)
			वापस शून्य;

		वापस fwnode_device_is_available(remote) ? remote : शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_graph_get_remote_node);

/**
 * fwnode_graph_get_endpoपूर्णांक_by_id - get endpoपूर्णांक by port and endpoपूर्णांक numbers
 * @fwnode: parent fwnode_handle containing the graph
 * @port: identअगरier of the port node
 * @endpoपूर्णांक: identअगरier of the endpoपूर्णांक node under the port node
 * @flags: fwnode lookup flags
 *
 * Return the fwnode handle of the local endpoपूर्णांक corresponding the port and
 * endpoपूर्णांक IDs or शून्य अगर not found.
 *
 * If FWNODE_GRAPH_ENDPOINT_NEXT is passed in @flags and the specअगरied endpoपूर्णांक
 * has not been found, look क्रम the बंदst endpoपूर्णांक ID greater than the
 * specअगरied one and वापस the endpoपूर्णांक that corresponds to it, अगर present.
 *
 * Do not वापस endpoपूर्णांकs that beदीर्घ to disabled devices, unless
 * FWNODE_GRAPH_DEVICE_DISABLED is passed in @flags.
 *
 * The वापसed endpoपूर्णांक needs to be released by calling fwnode_handle_put() on
 * it when it is not needed any more.
 */
काष्ठा fwnode_handle *
fwnode_graph_get_endpoपूर्णांक_by_id(स्थिर काष्ठा fwnode_handle *fwnode,
				u32 port, u32 endpoपूर्णांक, अचिन्हित दीर्घ flags)
अणु
	काष्ठा fwnode_handle *ep = शून्य, *best_ep = शून्य;
	अचिन्हित पूर्णांक best_ep_id = 0;
	bool endpoपूर्णांक_next = flags & FWNODE_GRAPH_ENDPOINT_NEXT;
	bool enabled_only = !(flags & FWNODE_GRAPH_DEVICE_DISABLED);

	जबतक ((ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, ep))) अणु
		काष्ठा fwnode_endpoपूर्णांक fwnode_ep = अणु 0 पूर्ण;
		पूर्णांक ret;

		अगर (enabled_only) अणु
			काष्ठा fwnode_handle *dev_node;
			bool available;

			dev_node = fwnode_graph_get_remote_port_parent(ep);
			available = fwnode_device_is_available(dev_node);
			fwnode_handle_put(dev_node);
			अगर (!available)
				जारी;
		पूर्ण

		ret = fwnode_graph_parse_endpoपूर्णांक(ep, &fwnode_ep);
		अगर (ret < 0)
			जारी;

		अगर (fwnode_ep.port != port)
			जारी;

		अगर (fwnode_ep.id == endpoपूर्णांक)
			वापस ep;

		अगर (!endpoपूर्णांक_next)
			जारी;

		/*
		 * If the endpoपूर्णांक that has just been found is not the first
		 * matching one and the ID of the one found previously is बंदr
		 * to the requested endpoपूर्णांक ID, skip it.
		 */
		अगर (fwnode_ep.id < endpoपूर्णांक ||
		    (best_ep && best_ep_id < fwnode_ep.id))
			जारी;

		fwnode_handle_put(best_ep);
		best_ep = fwnode_handle_get(ep);
		best_ep_id = fwnode_ep.id;
	पूर्ण

	अगर (best_ep)
		वापस best_ep;

	अगर (fwnode && !IS_ERR_OR_शून्य(fwnode->secondary))
		वापस fwnode_graph_get_endpoपूर्णांक_by_id(fwnode->secondary, port,
						       endpoपूर्णांक, flags);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_graph_get_endpoपूर्णांक_by_id);

/**
 * fwnode_graph_parse_endpoपूर्णांक - parse common endpoपूर्णांक node properties
 * @fwnode: poपूर्णांकer to endpoपूर्णांक fwnode_handle
 * @endpoपूर्णांक: poपूर्णांकer to the fwnode endpoपूर्णांक data काष्ठाure
 *
 * Parse @fwnode representing a graph endpoपूर्णांक node and store the
 * inक्रमmation in @endpoपूर्णांक. The caller must hold a reference to
 * @fwnode.
 */
पूर्णांक fwnode_graph_parse_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
				काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक)
अणु
	स_रखो(endpoपूर्णांक, 0, माप(*endpoपूर्णांक));

	वापस fwnode_call_पूर्णांक_op(fwnode, graph_parse_endpoपूर्णांक, endpoपूर्णांक);
पूर्ण
EXPORT_SYMBOL(fwnode_graph_parse_endpoपूर्णांक);

स्थिर व्योम *device_get_match_data(काष्ठा device *dev)
अणु
	वापस fwnode_call_ptr_op(dev_fwnode(dev), device_get_match_data, dev);
पूर्ण
EXPORT_SYMBOL_GPL(device_get_match_data);

अटल व्योम *
fwnode_graph_devcon_match(काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *con_id,
			  व्योम *data, devcon_match_fn_t match)
अणु
	काष्ठा fwnode_handle *node;
	काष्ठा fwnode_handle *ep;
	व्योम *ret;

	fwnode_graph_क्रम_each_endpoपूर्णांक(fwnode, ep) अणु
		node = fwnode_graph_get_remote_port_parent(ep);
		अगर (!fwnode_device_is_available(node))
			जारी;

		ret = match(node, con_id, data);
		fwnode_handle_put(node);
		अगर (ret) अणु
			fwnode_handle_put(ep);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *
fwnode_devcon_match(काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *con_id,
		    व्योम *data, devcon_match_fn_t match)
अणु
	काष्ठा fwnode_handle *node;
	व्योम *ret;
	पूर्णांक i;

	क्रम (i = 0; ; i++) अणु
		node = fwnode_find_reference(fwnode, con_id, i);
		अगर (IS_ERR(node))
			अवरोध;

		ret = match(node, शून्य, data);
		fwnode_handle_put(node);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * fwnode_connection_find_match - Find connection from a device node
 * @fwnode: Device node with the connection
 * @con_id: Identअगरier क्रम the connection
 * @data: Data क्रम the match function
 * @match: Function to check and convert the connection description
 *
 * Find a connection with unique identअगरier @con_id between @fwnode and another
 * device node. @match will be used to convert the connection description to
 * data the caller is expecting to be वापसed.
 */
व्योम *fwnode_connection_find_match(काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *con_id, व्योम *data,
				   devcon_match_fn_t match)
अणु
	व्योम *ret;

	अगर (!fwnode || !match)
		वापस शून्य;

	ret = fwnode_graph_devcon_match(fwnode, con_id, data, match);
	अगर (ret)
		वापस ret;

	वापस fwnode_devcon_match(fwnode, con_id, data, match);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_connection_find_match);
