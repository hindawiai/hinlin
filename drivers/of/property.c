<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/of/property.c - Procedures क्रम accessing and पूर्णांकerpreting
 *			   Devicetree properties and graphs.
 *
 * Initially created by copying procedures from drivers/of/base.c. This
 * file contains the OF property as well as the OF graph पूर्णांकerface
 * functions.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com
 *
 *  Adapted क्रम sparc and sparc64 by David S. Miller davem@davemloft.net
 *
 *  Reconsolidated from arch/x/kernel/prom.c by Stephen Rothwell and
 *  Grant Likely.
 */

#घोषणा pr_fmt(fmt)	"OF: " fmt

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/माला.स>
#समावेश <linux/moduleparam.h>

#समावेश "of_private.h"

/**
 * of_graph_is_present() - check graph's presence
 * @node: poपूर्णांकer to device_node containing graph port
 *
 * Return: True अगर @node has a port or ports (with a port) sub-node,
 * false otherwise.
 */
bool of_graph_is_present(स्थिर काष्ठा device_node *node)
अणु
	काष्ठा device_node *ports, *port;

	ports = of_get_child_by_name(node, "ports");
	अगर (ports)
		node = ports;

	port = of_get_child_by_name(node, "port");
	of_node_put(ports);
	of_node_put(port);

	वापस !!port;
पूर्ण
EXPORT_SYMBOL(of_graph_is_present);

/**
 * of_property_count_elems_of_size - Count the number of elements in a property
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @elem_size:	size of the inभागidual element
 *
 * Search क्रम a property in a device node and count the number of elements of
 * size elem_size in it.
 *
 * Return: The number of elements on sucess, -EINVAL अगर the property करोes not
 * exist or its length करोes not match a multiple of elem_size and -ENODATA अगर
 * the property करोes not have a value.
 */
पूर्णांक of_property_count_elems_of_size(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *propname, पूर्णांक elem_size)
अणु
	काष्ठा property *prop = of_find_property(np, propname, शून्य);

	अगर (!prop)
		वापस -EINVAL;
	अगर (!prop->value)
		वापस -ENODATA;

	अगर (prop->length % elem_size != 0) अणु
		pr_err("size of %s in node %pOF is not a multiple of %d\n",
		       propname, np, elem_size);
		वापस -EINVAL;
	पूर्ण

	वापस prop->length / elem_size;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_count_elems_of_size);

/**
 * of_find_property_value_of_size
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @min:	minimum allowed length of property value
 * @max:	maximum allowed length of property value (0 means unlimited)
 * @len:	अगर !=शून्य, actual length is written to here
 *
 * Search क्रम a property in a device node and valid the requested size.
 *
 * Return: The property value on success, -EINVAL अगर the property करोes not
 * exist, -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data is too small or too large.
 *
 */
अटल व्योम *of_find_property_value_of_size(स्थिर काष्ठा device_node *np,
			स्थिर अक्षर *propname, u32 min, u32 max, माप_प्रकार *len)
अणु
	काष्ठा property *prop = of_find_property(np, propname, शून्य);

	अगर (!prop)
		वापस ERR_PTR(-EINVAL);
	अगर (!prop->value)
		वापस ERR_PTR(-ENODATA);
	अगर (prop->length < min)
		वापस ERR_PTR(-EOVERFLOW);
	अगर (max && prop->length > max)
		वापस ERR_PTR(-EOVERFLOW);

	अगर (len)
		*len = prop->length;

	वापस prop->value;
पूर्ण

/**
 * of_property_पढ़ो_u32_index - Find and पढ़ो a u32 from a multi-value property.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @index:	index of the u32 in the list of values
 * @out_value:	poपूर्णांकer to वापस value, modअगरied only अगर no error.
 *
 * Search क्रम a property in a device node and पढ़ो nth 32-bit value from
 * it.
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist,
 * -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data isn't large enough.
 *
 * The out_value is modअगरied only अगर a valid u32 value can be decoded.
 */
पूर्णांक of_property_पढ़ो_u32_index(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname,
				       u32 index, u32 *out_value)
अणु
	स्थिर u32 *val = of_find_property_value_of_size(np, propname,
					((index + 1) * माप(*out_value)),
					0,
					शून्य);

	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	*out_value = be32_to_cpup(((__be32 *)val) + index);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_u32_index);

/**
 * of_property_पढ़ो_u64_index - Find and पढ़ो a u64 from a multi-value property.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @index:	index of the u64 in the list of values
 * @out_value:	poपूर्णांकer to वापस value, modअगरied only अगर no error.
 *
 * Search क्रम a property in a device node and पढ़ो nth 64-bit value from
 * it.
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist,
 * -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data isn't large enough.
 *
 * The out_value is modअगरied only अगर a valid u64 value can be decoded.
 */
पूर्णांक of_property_पढ़ो_u64_index(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname,
				       u32 index, u64 *out_value)
अणु
	स्थिर u64 *val = of_find_property_value_of_size(np, propname,
					((index + 1) * माप(*out_value)),
					0, शून्य);

	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	*out_value = be64_to_cpup(((__be64 *)val) + index);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_u64_index);

/**
 * of_property_पढ़ो_variable_u8_array - Find and पढ़ो an array of u8 from a
 * property, with bounds on the minimum and maximum array size.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_values:	poपूर्णांकer to found values.
 * @sz_min:	minimum number of array elements to पढ़ो
 * @sz_max:	maximum number of array elements to पढ़ो, अगर zero there is no
 *		upper limit on the number of elements in the dts entry but only
 *		sz_min will be पढ़ो.
 *
 * Search क्रम a property in a device node and पढ़ो 8-bit value(s) from
 * it.
 *
 * dts entry of array should be like:
 *  ``property = /bits/ 8 <0x50 0x60 0x70>;``
 *
 * Return: The number of elements पढ़ो on success, -EINVAL अगर the property
 * करोes not exist, -ENODATA अगर property करोes not have a value, and -EOVERFLOW
 * अगर the property data is smaller than sz_min or दीर्घer than sz_max.
 *
 * The out_values is modअगरied only अगर a valid u8 value can be decoded.
 */
पूर्णांक of_property_पढ़ो_variable_u8_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname, u8 *out_values,
					माप_प्रकार sz_min, माप_प्रकार sz_max)
अणु
	माप_प्रकार sz, count;
	स्थिर u8 *val = of_find_property_value_of_size(np, propname,
						(sz_min * माप(*out_values)),
						(sz_max * माप(*out_values)),
						&sz);

	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	अगर (!sz_max)
		sz = sz_min;
	अन्यथा
		sz /= माप(*out_values);

	count = sz;
	जबतक (count--)
		*out_values++ = *val++;

	वापस sz;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_variable_u8_array);

/**
 * of_property_पढ़ो_variable_u16_array - Find and पढ़ो an array of u16 from a
 * property, with bounds on the minimum and maximum array size.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_values:	poपूर्णांकer to found values.
 * @sz_min:	minimum number of array elements to पढ़ो
 * @sz_max:	maximum number of array elements to पढ़ो, अगर zero there is no
 *		upper limit on the number of elements in the dts entry but only
 *		sz_min will be पढ़ो.
 *
 * Search क्रम a property in a device node and पढ़ो 16-bit value(s) from
 * it.
 *
 * dts entry of array should be like:
 *  ``property = /bits/ 16 <0x5000 0x6000 0x7000>;``
 *
 * Return: The number of elements पढ़ो on success, -EINVAL अगर the property
 * करोes not exist, -ENODATA अगर property करोes not have a value, and -EOVERFLOW
 * अगर the property data is smaller than sz_min or दीर्घer than sz_max.
 *
 * The out_values is modअगरied only अगर a valid u16 value can be decoded.
 */
पूर्णांक of_property_पढ़ो_variable_u16_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname, u16 *out_values,
					माप_प्रकार sz_min, माप_प्रकार sz_max)
अणु
	माप_प्रकार sz, count;
	स्थिर __be16 *val = of_find_property_value_of_size(np, propname,
						(sz_min * माप(*out_values)),
						(sz_max * माप(*out_values)),
						&sz);

	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	अगर (!sz_max)
		sz = sz_min;
	अन्यथा
		sz /= माप(*out_values);

	count = sz;
	जबतक (count--)
		*out_values++ = be16_to_cpup(val++);

	वापस sz;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_variable_u16_array);

/**
 * of_property_पढ़ो_variable_u32_array - Find and पढ़ो an array of 32 bit
 * पूर्णांकegers from a property, with bounds on the minimum and maximum array size.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_values:	poपूर्णांकer to वापस found values.
 * @sz_min:	minimum number of array elements to पढ़ो
 * @sz_max:	maximum number of array elements to पढ़ो, अगर zero there is no
 *		upper limit on the number of elements in the dts entry but only
 *		sz_min will be पढ़ो.
 *
 * Search क्रम a property in a device node and पढ़ो 32-bit value(s) from
 * it.
 *
 * Return: The number of elements पढ़ो on success, -EINVAL अगर the property
 * करोes not exist, -ENODATA अगर property करोes not have a value, and -EOVERFLOW
 * अगर the property data is smaller than sz_min or दीर्घer than sz_max.
 *
 * The out_values is modअगरied only अगर a valid u32 value can be decoded.
 */
पूर्णांक of_property_पढ़ो_variable_u32_array(स्थिर काष्ठा device_node *np,
			       स्थिर अक्षर *propname, u32 *out_values,
			       माप_प्रकार sz_min, माप_प्रकार sz_max)
अणु
	माप_प्रकार sz, count;
	स्थिर __be32 *val = of_find_property_value_of_size(np, propname,
						(sz_min * माप(*out_values)),
						(sz_max * माप(*out_values)),
						&sz);

	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	अगर (!sz_max)
		sz = sz_min;
	अन्यथा
		sz /= माप(*out_values);

	count = sz;
	जबतक (count--)
		*out_values++ = be32_to_cpup(val++);

	वापस sz;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_variable_u32_array);

/**
 * of_property_पढ़ो_u64 - Find and पढ़ो a 64 bit पूर्णांकeger from a property
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_value:	poपूर्णांकer to वापस value, modअगरied only अगर वापस value is 0.
 *
 * Search क्रम a property in a device node and पढ़ो a 64-bit value from
 * it.
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist,
 * -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data isn't large enough.
 *
 * The out_value is modअगरied only अगर a valid u64 value can be decoded.
 */
पूर्णांक of_property_पढ़ो_u64(स्थिर काष्ठा device_node *np, स्थिर अक्षर *propname,
			 u64 *out_value)
अणु
	स्थिर __be32 *val = of_find_property_value_of_size(np, propname,
						माप(*out_value),
						0,
						शून्य);

	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	*out_value = of_पढ़ो_number(val, 2);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_u64);

/**
 * of_property_पढ़ो_variable_u64_array - Find and पढ़ो an array of 64 bit
 * पूर्णांकegers from a property, with bounds on the minimum and maximum array size.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_values:	poपूर्णांकer to found values.
 * @sz_min:	minimum number of array elements to पढ़ो
 * @sz_max:	maximum number of array elements to पढ़ो, अगर zero there is no
 *		upper limit on the number of elements in the dts entry but only
 *		sz_min will be पढ़ो.
 *
 * Search क्रम a property in a device node and पढ़ो 64-bit value(s) from
 * it.
 *
 * Return: The number of elements पढ़ो on success, -EINVAL अगर the property
 * करोes not exist, -ENODATA अगर property करोes not have a value, and -EOVERFLOW
 * अगर the property data is smaller than sz_min or दीर्घer than sz_max.
 *
 * The out_values is modअगरied only अगर a valid u64 value can be decoded.
 */
पूर्णांक of_property_पढ़ो_variable_u64_array(स्थिर काष्ठा device_node *np,
			       स्थिर अक्षर *propname, u64 *out_values,
			       माप_प्रकार sz_min, माप_प्रकार sz_max)
अणु
	माप_प्रकार sz, count;
	स्थिर __be32 *val = of_find_property_value_of_size(np, propname,
						(sz_min * माप(*out_values)),
						(sz_max * माप(*out_values)),
						&sz);

	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	अगर (!sz_max)
		sz = sz_min;
	अन्यथा
		sz /= माप(*out_values);

	count = sz;
	जबतक (count--) अणु
		*out_values++ = of_पढ़ो_number(val, 2);
		val += 2;
	पूर्ण

	वापस sz;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_variable_u64_array);

/**
 * of_property_पढ़ो_string - Find and पढ़ो a string from a property
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_string:	poपूर्णांकer to null terminated वापस string, modअगरied only अगर
 *		वापस value is 0.
 *
 * Search क्रम a property in a device tree node and retrieve a null
 * terminated string value (poपूर्णांकer to data, not a copy).
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist, -ENODATA अगर
 * property करोes not have a value, and -EILSEQ अगर the string is not
 * null-terminated within the length of the property data.
 *
 * The out_string poपूर्णांकer is modअगरied only अगर a valid string can be decoded.
 */
पूर्णांक of_property_पढ़ो_string(स्थिर काष्ठा device_node *np, स्थिर अक्षर *propname,
				स्थिर अक्षर **out_string)
अणु
	स्थिर काष्ठा property *prop = of_find_property(np, propname, शून्य);
	अगर (!prop)
		वापस -EINVAL;
	अगर (!prop->value)
		वापस -ENODATA;
	अगर (strnlen(prop->value, prop->length) >= prop->length)
		वापस -EILSEQ;
	*out_string = prop->value;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_string);

/**
 * of_property_match_string() - Find string in a list and वापस index
 * @np: poपूर्णांकer to node containing string list property
 * @propname: string list property name
 * @string: poपूर्णांकer to string to search क्रम in string list
 *
 * This function searches a string list property and वापसs the index
 * of a specअगरic string value.
 */
पूर्णांक of_property_match_string(स्थिर काष्ठा device_node *np, स्थिर अक्षर *propname,
			     स्थिर अक्षर *string)
अणु
	स्थिर काष्ठा property *prop = of_find_property(np, propname, शून्य);
	माप_प्रकार l;
	पूर्णांक i;
	स्थिर अक्षर *p, *end;

	अगर (!prop)
		वापस -EINVAL;
	अगर (!prop->value)
		वापस -ENODATA;

	p = prop->value;
	end = p + prop->length;

	क्रम (i = 0; p < end; i++, p += l) अणु
		l = strnlen(p, end - p) + 1;
		अगर (p + l > end)
			वापस -EILSEQ;
		pr_debug("comparing %s with %s\n", string, p);
		अगर (म_भेद(string, p) == 0)
			वापस i; /* Found it; वापस index */
	पूर्ण
	वापस -ENODATA;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_match_string);

/**
 * of_property_पढ़ो_string_helper() - Utility helper क्रम parsing string properties
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_strs:	output array of string poपूर्णांकers.
 * @sz:		number of array elements to पढ़ो.
 * @skip:	Number of strings to skip over at beginning of list.
 *
 * Don't call this function directly. It is a utility helper क्रम the
 * of_property_पढ़ो_string*() family of functions.
 */
पूर्णांक of_property_पढ़ो_string_helper(स्थिर काष्ठा device_node *np,
				   स्थिर अक्षर *propname, स्थिर अक्षर **out_strs,
				   माप_प्रकार sz, पूर्णांक skip)
अणु
	स्थिर काष्ठा property *prop = of_find_property(np, propname, शून्य);
	पूर्णांक l = 0, i = 0;
	स्थिर अक्षर *p, *end;

	अगर (!prop)
		वापस -EINVAL;
	अगर (!prop->value)
		वापस -ENODATA;
	p = prop->value;
	end = p + prop->length;

	क्रम (i = 0; p < end && (!out_strs || i < skip + sz); i++, p += l) अणु
		l = strnlen(p, end - p) + 1;
		अगर (p + l > end)
			वापस -EILSEQ;
		अगर (out_strs && i >= skip)
			*out_strs++ = p;
	पूर्ण
	i -= skip;
	वापस i <= 0 ? -ENODATA : i;
पूर्ण
EXPORT_SYMBOL_GPL(of_property_पढ़ो_string_helper);

स्थिर __be32 *of_prop_next_u32(काष्ठा property *prop, स्थिर __be32 *cur,
			       u32 *pu)
अणु
	स्थिर व्योम *curv = cur;

	अगर (!prop)
		वापस शून्य;

	अगर (!cur) अणु
		curv = prop->value;
		जाओ out_val;
	पूर्ण

	curv += माप(*cur);
	अगर (curv >= prop->value + prop->length)
		वापस शून्य;

out_val:
	*pu = be32_to_cpup(curv);
	वापस curv;
पूर्ण
EXPORT_SYMBOL_GPL(of_prop_next_u32);

स्थिर अक्षर *of_prop_next_string(काष्ठा property *prop, स्थिर अक्षर *cur)
अणु
	स्थिर व्योम *curv = cur;

	अगर (!prop)
		वापस शून्य;

	अगर (!cur)
		वापस prop->value;

	curv += म_माप(cur) + 1;
	अगर (curv >= prop->value + prop->length)
		वापस शून्य;

	वापस curv;
पूर्ण
EXPORT_SYMBOL_GPL(of_prop_next_string);

/**
 * of_graph_parse_endpoपूर्णांक() - parse common endpoपूर्णांक node properties
 * @node: poपूर्णांकer to endpoपूर्णांक device_node
 * @endpoपूर्णांक: poपूर्णांकer to the OF endpoपूर्णांक data काष्ठाure
 *
 * The caller should hold a reference to @node.
 */
पूर्णांक of_graph_parse_endpoपूर्णांक(स्थिर काष्ठा device_node *node,
			    काष्ठा of_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा device_node *port_node = of_get_parent(node);

	WARN_ONCE(!port_node, "%s(): endpoint %pOF has no parent node\n",
		  __func__, node);

	स_रखो(endpoपूर्णांक, 0, माप(*endpoपूर्णांक));

	endpoपूर्णांक->local_node = node;
	/*
	 * It करोesn't matter whether the two calls below succeed.
	 * If they करोn't then the शेष value 0 is used.
	 */
	of_property_पढ़ो_u32(port_node, "reg", &endpoपूर्णांक->port);
	of_property_पढ़ो_u32(node, "reg", &endpoपूर्णांक->id);

	of_node_put(port_node);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(of_graph_parse_endpoपूर्णांक);

/**
 * of_graph_get_port_by_id() - get the port matching a given id
 * @parent: poपूर्णांकer to the parent device node
 * @id: id of the port
 *
 * Return: A 'port' node poपूर्णांकer with refcount incremented. The caller
 * has to use of_node_put() on it when करोne.
 */
काष्ठा device_node *of_graph_get_port_by_id(काष्ठा device_node *parent, u32 id)
अणु
	काष्ठा device_node *node, *port;

	node = of_get_child_by_name(parent, "ports");
	अगर (node)
		parent = node;

	क्रम_each_child_of_node(parent, port) अणु
		u32 port_id = 0;

		अगर (!of_node_name_eq(port, "port"))
			जारी;
		of_property_पढ़ो_u32(port, "reg", &port_id);
		अगर (id == port_id)
			अवरोध;
	पूर्ण

	of_node_put(node);

	वापस port;
पूर्ण
EXPORT_SYMBOL(of_graph_get_port_by_id);

/**
 * of_graph_get_next_endpoपूर्णांक() - get next endpoपूर्णांक node
 * @parent: poपूर्णांकer to the parent device node
 * @prev: previous endpoपूर्णांक node, or शून्य to get first
 *
 * Return: An 'endpoint' node poपूर्णांकer with refcount incremented. Refcount
 * of the passed @prev node is decremented.
 */
काष्ठा device_node *of_graph_get_next_endpoपूर्णांक(स्थिर काष्ठा device_node *parent,
					काष्ठा device_node *prev)
अणु
	काष्ठा device_node *endpoपूर्णांक;
	काष्ठा device_node *port;

	अगर (!parent)
		वापस शून्य;

	/*
	 * Start by locating the port node. If no previous endpoपूर्णांक is specअगरied
	 * search क्रम the first port node, otherwise get the previous endpoपूर्णांक
	 * parent port node.
	 */
	अगर (!prev) अणु
		काष्ठा device_node *node;

		node = of_get_child_by_name(parent, "ports");
		अगर (node)
			parent = node;

		port = of_get_child_by_name(parent, "port");
		of_node_put(node);

		अगर (!port) अणु
			pr_err("graph: no port node found in %pOF\n", parent);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		port = of_get_parent(prev);
		अगर (WARN_ONCE(!port, "%s(): endpoint %pOF has no parent node\n",
			      __func__, prev))
			वापस शून्य;
	पूर्ण

	जबतक (1) अणु
		/*
		 * Now that we have a port node, get the next endpoपूर्णांक by
		 * getting the next child. If the previous endpoपूर्णांक is शून्य this
		 * will वापस the first child.
		 */
		endpoपूर्णांक = of_get_next_child(port, prev);
		अगर (endpoपूर्णांक) अणु
			of_node_put(port);
			वापस endpoपूर्णांक;
		पूर्ण

		/* No more endpoपूर्णांकs under this port, try the next one. */
		prev = शून्य;

		करो अणु
			port = of_get_next_child(parent, port);
			अगर (!port)
				वापस शून्य;
		पूर्ण जबतक (!of_node_name_eq(port, "port"));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(of_graph_get_next_endpoपूर्णांक);

/**
 * of_graph_get_endpoपूर्णांक_by_regs() - get endpoपूर्णांक node of specअगरic identअगरiers
 * @parent: poपूर्णांकer to the parent device node
 * @port_reg: identअगरier (value of reg property) of the parent port node
 * @reg: identअगरier (value of reg property) of the endpoपूर्णांक node
 *
 * Return: An 'endpoint' node poपूर्णांकer which is identअगरied by reg and at the same
 * is the child of a port node identअगरied by port_reg. reg and port_reg are
 * ignored when they are -1. Use of_node_put() on the poपूर्णांकer when करोne.
 */
काष्ठा device_node *of_graph_get_endpoपूर्णांक_by_regs(
	स्थिर काष्ठा device_node *parent, पूर्णांक port_reg, पूर्णांक reg)
अणु
	काष्ठा of_endpoपूर्णांक endpoपूर्णांक;
	काष्ठा device_node *node = शून्य;

	क्रम_each_endpoपूर्णांक_of_node(parent, node) अणु
		of_graph_parse_endpoपूर्णांक(node, &endpoपूर्णांक);
		अगर (((port_reg == -1) || (endpoपूर्णांक.port == port_reg)) &&
			((reg == -1) || (endpoपूर्णांक.id == reg)))
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_graph_get_endpoपूर्णांक_by_regs);

/**
 * of_graph_get_remote_endpoपूर्णांक() - get remote endpoपूर्णांक node
 * @node: poपूर्णांकer to a local endpoपूर्णांक device_node
 *
 * Return: Remote endpoपूर्णांक node associated with remote endpoपूर्णांक node linked
 *	   to @node. Use of_node_put() on it when करोne.
 */
काष्ठा device_node *of_graph_get_remote_endpoपूर्णांक(स्थिर काष्ठा device_node *node)
अणु
	/* Get remote endpoपूर्णांक node. */
	वापस of_parse_phandle(node, "remote-endpoint", 0);
पूर्ण
EXPORT_SYMBOL(of_graph_get_remote_endpoपूर्णांक);

/**
 * of_graph_get_port_parent() - get port's parent node
 * @node: poपूर्णांकer to a local endpoपूर्णांक device_node
 *
 * Return: device node associated with endpoपूर्णांक node linked
 *	   to @node. Use of_node_put() on it when करोne.
 */
काष्ठा device_node *of_graph_get_port_parent(काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक depth;

	अगर (!node)
		वापस शून्य;

	/*
	 * Preserve usecount क्रम passed in node as of_get_next_parent()
	 * will करो of_node_put() on it.
	 */
	of_node_get(node);

	/* Walk 3 levels up only अगर there is 'ports' node. */
	क्रम (depth = 3; depth && node; depth--) अणु
		node = of_get_next_parent(node);
		अगर (depth == 2 && !of_node_name_eq(node, "ports"))
			अवरोध;
	पूर्ण
	वापस node;
पूर्ण
EXPORT_SYMBOL(of_graph_get_port_parent);

/**
 * of_graph_get_remote_port_parent() - get remote port's parent node
 * @node: poपूर्णांकer to a local endpoपूर्णांक device_node
 *
 * Return: Remote device node associated with remote endpoपूर्णांक node linked
 *	   to @node. Use of_node_put() on it when करोne.
 */
काष्ठा device_node *of_graph_get_remote_port_parent(
			       स्थिर काष्ठा device_node *node)
अणु
	काष्ठा device_node *np, *pp;

	/* Get remote endpoपूर्णांक node. */
	np = of_graph_get_remote_endpoपूर्णांक(node);

	pp = of_graph_get_port_parent(np);

	of_node_put(np);

	वापस pp;
पूर्ण
EXPORT_SYMBOL(of_graph_get_remote_port_parent);

/**
 * of_graph_get_remote_port() - get remote port node
 * @node: poपूर्णांकer to a local endpoपूर्णांक device_node
 *
 * Return: Remote port node associated with remote endpoपूर्णांक node linked
 * to @node. Use of_node_put() on it when करोne.
 */
काष्ठा device_node *of_graph_get_remote_port(स्थिर काष्ठा device_node *node)
अणु
	काष्ठा device_node *np;

	/* Get remote endpoपूर्णांक node. */
	np = of_graph_get_remote_endpoपूर्णांक(node);
	अगर (!np)
		वापस शून्य;
	वापस of_get_next_parent(np);
पूर्ण
EXPORT_SYMBOL(of_graph_get_remote_port);

पूर्णांक of_graph_get_endpoपूर्णांक_count(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा device_node *endpoपूर्णांक;
	पूर्णांक num = 0;

	क्रम_each_endpoपूर्णांक_of_node(np, endpoपूर्णांक)
		num++;

	वापस num;
पूर्ण
EXPORT_SYMBOL(of_graph_get_endpoपूर्णांक_count);

/**
 * of_graph_get_remote_node() - get remote parent device_node क्रम given port/endpoपूर्णांक
 * @node: poपूर्णांकer to parent device_node containing graph port/endpoपूर्णांक
 * @port: identअगरier (value of reg property) of the parent port node
 * @endpoपूर्णांक: identअगरier (value of reg property) of the endpoपूर्णांक node
 *
 * Return: Remote device node associated with remote endpoपूर्णांक node linked
 * to @node. Use of_node_put() on it when करोne.
 */
काष्ठा device_node *of_graph_get_remote_node(स्थिर काष्ठा device_node *node,
					     u32 port, u32 endpoपूर्णांक)
अणु
	काष्ठा device_node *endpoपूर्णांक_node, *remote;

	endpoपूर्णांक_node = of_graph_get_endpoपूर्णांक_by_regs(node, port, endpoपूर्णांक);
	अगर (!endpoपूर्णांक_node) अणु
		pr_debug("no valid endpoint (%d, %d) for node %pOF\n",
			 port, endpoपूर्णांक, node);
		वापस शून्य;
	पूर्ण

	remote = of_graph_get_remote_port_parent(endpoपूर्णांक_node);
	of_node_put(endpoपूर्णांक_node);
	अगर (!remote) अणु
		pr_debug("no valid remote node\n");
		वापस शून्य;
	पूर्ण

	अगर (!of_device_is_available(remote)) अणु
		pr_debug("not available for remote node\n");
		of_node_put(remote);
		वापस शून्य;
	पूर्ण

	वापस remote;
पूर्ण
EXPORT_SYMBOL(of_graph_get_remote_node);

अटल काष्ठा fwnode_handle *of_fwnode_get(काष्ठा fwnode_handle *fwnode)
अणु
	वापस of_fwnode_handle(of_node_get(to_of_node(fwnode)));
पूर्ण

अटल व्योम of_fwnode_put(काष्ठा fwnode_handle *fwnode)
अणु
	of_node_put(to_of_node(fwnode));
पूर्ण

अटल bool of_fwnode_device_is_available(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस of_device_is_available(to_of_node(fwnode));
पूर्ण

अटल bool of_fwnode_property_present(स्थिर काष्ठा fwnode_handle *fwnode,
				       स्थिर अक्षर *propname)
अणु
	वापस of_property_पढ़ो_bool(to_of_node(fwnode), propname);
पूर्ण

अटल पूर्णांक of_fwnode_property_पढ़ो_पूर्णांक_array(स्थिर काष्ठा fwnode_handle *fwnode,
					     स्थिर अक्षर *propname,
					     अचिन्हित पूर्णांक elem_size, व्योम *val,
					     माप_प्रकार nval)
अणु
	स्थिर काष्ठा device_node *node = to_of_node(fwnode);

	अगर (!val)
		वापस of_property_count_elems_of_size(node, propname,
						       elem_size);

	चयन (elem_size) अणु
	हाल माप(u8):
		वापस of_property_पढ़ो_u8_array(node, propname, val, nval);
	हाल माप(u16):
		वापस of_property_पढ़ो_u16_array(node, propname, val, nval);
	हाल माप(u32):
		वापस of_property_पढ़ो_u32_array(node, propname, val, nval);
	हाल माप(u64):
		वापस of_property_पढ़ो_u64_array(node, propname, val, nval);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक
of_fwnode_property_पढ़ो_string_array(स्थिर काष्ठा fwnode_handle *fwnode,
				     स्थिर अक्षर *propname, स्थिर अक्षर **val,
				     माप_प्रकार nval)
अणु
	स्थिर काष्ठा device_node *node = to_of_node(fwnode);

	वापस val ?
		of_property_पढ़ो_string_array(node, propname, val, nval) :
		of_property_count_strings(node, propname);
पूर्ण

अटल स्थिर अक्षर *of_fwnode_get_name(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस kbasename(to_of_node(fwnode)->full_name);
पूर्ण

अटल स्थिर अक्षर *of_fwnode_get_name_prefix(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	/* Root needs no prefix here (its name is "/"). */
	अगर (!to_of_node(fwnode)->parent)
		वापस "";

	वापस "/";
पूर्ण

अटल काष्ठा fwnode_handle *
of_fwnode_get_parent(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस of_fwnode_handle(of_get_parent(to_of_node(fwnode)));
पूर्ण

अटल काष्ठा fwnode_handle *
of_fwnode_get_next_child_node(स्थिर काष्ठा fwnode_handle *fwnode,
			      काष्ठा fwnode_handle *child)
अणु
	वापस of_fwnode_handle(of_get_next_available_child(to_of_node(fwnode),
							    to_of_node(child)));
पूर्ण

अटल काष्ठा fwnode_handle *
of_fwnode_get_named_child_node(स्थिर काष्ठा fwnode_handle *fwnode,
			       स्थिर अक्षर *childname)
अणु
	स्थिर काष्ठा device_node *node = to_of_node(fwnode);
	काष्ठा device_node *child;

	क्रम_each_available_child_of_node(node, child)
		अगर (of_node_name_eq(child, childname))
			वापस of_fwnode_handle(child);

	वापस शून्य;
पूर्ण

अटल पूर्णांक
of_fwnode_get_reference_args(स्थिर काष्ठा fwnode_handle *fwnode,
			     स्थिर अक्षर *prop, स्थिर अक्षर *nargs_prop,
			     अचिन्हित पूर्णांक nargs, अचिन्हित पूर्णांक index,
			     काष्ठा fwnode_reference_args *args)
अणु
	काष्ठा of_phandle_args of_args;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (nargs_prop)
		ret = of_parse_phandle_with_args(to_of_node(fwnode), prop,
						 nargs_prop, index, &of_args);
	अन्यथा
		ret = of_parse_phandle_with_fixed_args(to_of_node(fwnode), prop,
						       nargs, index, &of_args);
	अगर (ret < 0)
		वापस ret;
	अगर (!args)
		वापस 0;

	args->nargs = of_args.args_count;
	args->fwnode = of_fwnode_handle(of_args.np);

	क्रम (i = 0; i < NR_FWNODE_REFERENCE_ARGS; i++)
		args->args[i] = i < of_args.args_count ? of_args.args[i] : 0;

	वापस 0;
पूर्ण

अटल काष्ठा fwnode_handle *
of_fwnode_graph_get_next_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
				  काष्ठा fwnode_handle *prev)
अणु
	वापस of_fwnode_handle(of_graph_get_next_endpoपूर्णांक(to_of_node(fwnode),
							   to_of_node(prev)));
पूर्ण

अटल काष्ठा fwnode_handle *
of_fwnode_graph_get_remote_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस of_fwnode_handle(
		of_graph_get_remote_endpoपूर्णांक(to_of_node(fwnode)));
पूर्ण

अटल काष्ठा fwnode_handle *
of_fwnode_graph_get_port_parent(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device_node *np;

	/* Get the parent of the port */
	np = of_get_parent(to_of_node(fwnode));
	अगर (!np)
		वापस शून्य;

	/* Is this the "ports" node? If not, it's the port parent. */
	अगर (!of_node_name_eq(np, "ports"))
		वापस of_fwnode_handle(np);

	वापस of_fwnode_handle(of_get_next_parent(np));
पूर्ण

अटल पूर्णांक of_fwnode_graph_parse_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
					  काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक)
अणु
	स्थिर काष्ठा device_node *node = to_of_node(fwnode);
	काष्ठा device_node *port_node = of_get_parent(node);

	endpoपूर्णांक->local_fwnode = fwnode;

	of_property_पढ़ो_u32(port_node, "reg", &endpoपूर्णांक->port);
	of_property_पढ़ो_u32(node, "reg", &endpoपूर्णांक->id);

	of_node_put(port_node);

	वापस 0;
पूर्ण

अटल स्थिर व्योम *
of_fwnode_device_get_match_data(स्थिर काष्ठा fwnode_handle *fwnode,
				स्थिर काष्ठा device *dev)
अणु
	वापस of_device_get_match_data(dev);
पूर्ण

अटल bool of_is_ancestor_of(काष्ठा device_node *test_ancestor,
			      काष्ठा device_node *child)
अणु
	of_node_get(child);
	जबतक (child) अणु
		अगर (child == test_ancestor) अणु
			of_node_put(child);
			वापस true;
		पूर्ण
		child = of_get_next_parent(child);
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा device_node *of_get_compat_node(काष्ठा device_node *np)
अणु
	of_node_get(np);

	जबतक (np) अणु
		अगर (!of_device_is_available(np)) अणु
			of_node_put(np);
			np = शून्य;
		पूर्ण

		अगर (of_find_property(np, "compatible", शून्य))
			अवरोध;

		np = of_get_next_parent(np);
	पूर्ण

	वापस np;
पूर्ण

/**
 * of_link_to_phandle - Add fwnode link to supplier from supplier phandle
 * @con_np: consumer device tree node
 * @sup_np: supplier device tree node
 *
 * Given a phandle to a supplier device tree node (@sup_np), this function
 * finds the device that owns the supplier device tree node and creates a
 * device link from @dev consumer device to the supplier device. This function
 * करोesn't create device links क्रम invalid scenarios such as trying to create a
 * link with a parent device as the consumer of its child device. In such
 * हालs, it वापसs an error.
 *
 * Returns:
 * - 0 अगर fwnode link successfully created to supplier
 * - -EINVAL अगर the supplier link is invalid and should not be created
 * - -ENODEV अगर काष्ठा device will never be create क्रम supplier
 */
अटल पूर्णांक of_link_to_phandle(काष्ठा device_node *con_np,
			      काष्ठा device_node *sup_np)
अणु
	काष्ठा device *sup_dev;
	काष्ठा device_node *पंचांगp_np = sup_np;

	/*
	 * Find the device node that contains the supplier phandle.  It may be
	 * @sup_np or it may be an ancestor of @sup_np.
	 */
	sup_np = of_get_compat_node(sup_np);
	अगर (!sup_np) अणु
		pr_debug("Not linking %pOFP to %pOFP - No device\n",
			 con_np, पंचांगp_np);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Don't allow linking a device node as a consumer of one of its
	 * descendant nodes. By definition, a child node can't be a functional
	 * dependency क्रम the parent node.
	 */
	अगर (of_is_ancestor_of(con_np, sup_np)) अणु
		pr_debug("Not linking %pOFP to %pOFP - is descendant\n",
			 con_np, sup_np);
		of_node_put(sup_np);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Don't create links to "early devices" that won't have काष्ठा devices
	 * created क्रम them.
	 */
	sup_dev = get_dev_from_fwnode(&sup_np->fwnode);
	अगर (!sup_dev &&
	    (of_node_check_flag(sup_np, OF_POPULATED) ||
	     sup_np->fwnode.flags & FWNODE_FLAG_NOT_DEVICE)) अणु
		pr_debug("Not linking %pOFP to %pOFP - No struct device\n",
			 con_np, sup_np);
		of_node_put(sup_np);
		वापस -ENODEV;
	पूर्ण
	put_device(sup_dev);

	fwnode_link_add(of_fwnode_handle(con_np), of_fwnode_handle(sup_np));
	of_node_put(sup_np);

	वापस 0;
पूर्ण

/**
 * parse_prop_cells - Property parsing function क्रम suppliers
 *
 * @np:		Poपूर्णांकer to device tree node containing a list
 * @prop_name:	Name of property to be parsed. Expected to hold phandle values
 * @index:	For properties holding a list of phandles, this is the index
 *		पूर्णांकo the list.
 * @list_name:	Property name that is known to contain list of phandle(s) to
 *		supplier(s)
 * @cells_name:	property name that specअगरies phandles' arguments count
 *
 * This is a helper function to parse properties that have a known fixed name
 * and are a list of phandles and phandle arguments.
 *
 * Returns:
 * - phandle node poपूर्णांकer with refcount incremented. Caller must of_node_put()
 *   on it when करोne.
 * - शून्य अगर no phandle found at index
 */
अटल काष्ठा device_node *parse_prop_cells(काष्ठा device_node *np,
					    स्थिर अक्षर *prop_name, पूर्णांक index,
					    स्थिर अक्षर *list_name,
					    स्थिर अक्षर *cells_name)
अणु
	काष्ठा of_phandle_args sup_args;

	अगर (म_भेद(prop_name, list_name))
		वापस शून्य;

	अगर (of_parse_phandle_with_args(np, list_name, cells_name, index,
				       &sup_args))
		वापस शून्य;

	वापस sup_args.np;
पूर्ण

#घोषणा DEFINE_SIMPLE_PROP(fname, name, cells)				  \
अटल काष्ठा device_node *parse_##fname(काष्ठा device_node *np,	  \
					स्थिर अक्षर *prop_name, पूर्णांक index) \
अणु									  \
	वापस parse_prop_cells(np, prop_name, index, name, cells);	  \
पूर्ण

अटल पूर्णांक म_भेद_suffix(स्थिर अक्षर *str, स्थिर अक्षर *suffix)
अणु
	अचिन्हित पूर्णांक len, suffix_len;

	len = म_माप(str);
	suffix_len = म_माप(suffix);
	अगर (len <= suffix_len)
		वापस -1;
	वापस म_भेद(str + len - suffix_len, suffix);
पूर्ण

/**
 * parse_suffix_prop_cells - Suffix property parsing function क्रम suppliers
 *
 * @np:		Poपूर्णांकer to device tree node containing a list
 * @prop_name:	Name of property to be parsed. Expected to hold phandle values
 * @index:	For properties holding a list of phandles, this is the index
 *		पूर्णांकo the list.
 * @suffix:	Property suffix that is known to contain list of phandle(s) to
 *		supplier(s)
 * @cells_name:	property name that specअगरies phandles' arguments count
 *
 * This is a helper function to parse properties that have a known fixed suffix
 * and are a list of phandles and phandle arguments.
 *
 * Returns:
 * - phandle node poपूर्णांकer with refcount incremented. Caller must of_node_put()
 *   on it when करोne.
 * - शून्य अगर no phandle found at index
 */
अटल काष्ठा device_node *parse_suffix_prop_cells(काष्ठा device_node *np,
					    स्थिर अक्षर *prop_name, पूर्णांक index,
					    स्थिर अक्षर *suffix,
					    स्थिर अक्षर *cells_name)
अणु
	काष्ठा of_phandle_args sup_args;

	अगर (म_भेद_suffix(prop_name, suffix))
		वापस शून्य;

	अगर (of_parse_phandle_with_args(np, prop_name, cells_name, index,
				       &sup_args))
		वापस शून्य;

	वापस sup_args.np;
पूर्ण

#घोषणा DEFINE_SUFFIX_PROP(fname, suffix, cells)			     \
अटल काष्ठा device_node *parse_##fname(काष्ठा device_node *np,	     \
					स्थिर अक्षर *prop_name, पूर्णांक index)    \
अणु									     \
	वापस parse_suffix_prop_cells(np, prop_name, index, suffix, cells); \
पूर्ण

/**
 * काष्ठा supplier_bindings - Property parsing functions क्रम suppliers
 *
 * @parse_prop: function name
 *	parse_prop() finds the node corresponding to a supplier phandle
 * @parse_prop.np: Poपूर्णांकer to device node holding supplier phandle property
 * @parse_prop.prop_name: Name of property holding a phandle value
 * @parse_prop.index: For properties holding a list of phandles, this is the
 *		      index पूर्णांकo the list
 * @optional: Describes whether a supplier is mandatory or not
 * @node_not_dev: The consumer node containing the property is never a device.
 *
 * Returns:
 * parse_prop() वापस values are
 * - phandle node poपूर्णांकer with refcount incremented. Caller must of_node_put()
 *   on it when करोne.
 * - शून्य अगर no phandle found at index
 */
काष्ठा supplier_bindings अणु
	काष्ठा device_node *(*parse_prop)(काष्ठा device_node *np,
					  स्थिर अक्षर *prop_name, पूर्णांक index);
	bool optional;
	bool node_not_dev;
पूर्ण;

DEFINE_SIMPLE_PROP(घड़ीs, "clocks", "#clock-cells")
DEFINE_SIMPLE_PROP(पूर्णांकerconnects, "interconnects", "#interconnect-cells")
DEFINE_SIMPLE_PROP(iommus, "iommus", "#iommu-cells")
DEFINE_SIMPLE_PROP(mboxes, "mboxes", "#mbox-cells")
DEFINE_SIMPLE_PROP(io_channels, "io-channel", "#io-channel-cells")
DEFINE_SIMPLE_PROP(पूर्णांकerrupt_parent, "interrupt-parent", शून्य)
DEFINE_SIMPLE_PROP(dmas, "dmas", "#dma-cells")
DEFINE_SIMPLE_PROP(घातer_करोमुख्यs, "power-domains", "#power-domain-cells")
DEFINE_SIMPLE_PROP(hwlocks, "hwlocks", "#hwlock-cells")
DEFINE_SIMPLE_PROP(extcon, "extcon", शून्य)
DEFINE_SIMPLE_PROP(nvmem_cells, "nvmem-cells", शून्य)
DEFINE_SIMPLE_PROP(phys, "phys", "#phy-cells")
DEFINE_SIMPLE_PROP(wakeup_parent, "wakeup-parent", शून्य)
DEFINE_SIMPLE_PROP(pinctrl0, "pinctrl-0", शून्य)
DEFINE_SIMPLE_PROP(pinctrl1, "pinctrl-1", शून्य)
DEFINE_SIMPLE_PROP(pinctrl2, "pinctrl-2", शून्य)
DEFINE_SIMPLE_PROP(pinctrl3, "pinctrl-3", शून्य)
DEFINE_SIMPLE_PROP(pinctrl4, "pinctrl-4", शून्य)
DEFINE_SIMPLE_PROP(pinctrl5, "pinctrl-5", शून्य)
DEFINE_SIMPLE_PROP(pinctrl6, "pinctrl-6", शून्य)
DEFINE_SIMPLE_PROP(pinctrl7, "pinctrl-7", शून्य)
DEFINE_SIMPLE_PROP(pinctrl8, "pinctrl-8", शून्य)
DEFINE_SIMPLE_PROP(remote_endpoपूर्णांक, "remote-endpoint", शून्य)
DEFINE_SUFFIX_PROP(regulators, "-supply", शून्य)
DEFINE_SUFFIX_PROP(gpio, "-gpio", "#gpio-cells")

अटल काष्ठा device_node *parse_gpios(काष्ठा device_node *np,
				       स्थिर अक्षर *prop_name, पूर्णांक index)
अणु
	अगर (!म_भेद_suffix(prop_name, ",nr-gpios"))
		वापस शून्य;

	वापस parse_suffix_prop_cells(np, prop_name, index, "-gpios",
				       "#gpio-cells");
पूर्ण

अटल काष्ठा device_node *parse_iommu_maps(काष्ठा device_node *np,
					    स्थिर अक्षर *prop_name, पूर्णांक index)
अणु
	अगर (म_भेद(prop_name, "iommu-map"))
		वापस शून्य;

	वापस of_parse_phandle(np, prop_name, (index * 4) + 1);
पूर्ण

अटल काष्ठा device_node *parse_gpio_compat(काष्ठा device_node *np,
					     स्थिर अक्षर *prop_name, पूर्णांक index)
अणु
	काष्ठा of_phandle_args sup_args;

	अगर (म_भेद(prop_name, "gpio") && म_भेद(prop_name, "gpios"))
		वापस शून्य;

	/*
	 * Ignore node with gpio-hog property since its gpios are all provided
	 * by its parent.
	 */
	अगर (of_find_property(np, "gpio-hog", शून्य))
		वापस शून्य;

	अगर (of_parse_phandle_with_args(np, prop_name, "#gpio-cells", index,
				       &sup_args))
		वापस शून्य;

	वापस sup_args.np;
पूर्ण

अटल काष्ठा device_node *parse_पूर्णांकerrupts(काष्ठा device_node *np,
					    स्थिर अक्षर *prop_name, पूर्णांक index)
अणु
	काष्ठा of_phandle_args sup_args;

	अगर (!IS_ENABLED(CONFIG_OF_IRQ) || IS_ENABLED(CONFIG_PPC))
		वापस शून्य;

	अगर (म_भेद(prop_name, "interrupts") &&
	    म_भेद(prop_name, "interrupts-extended"))
		वापस शून्य;

	वापस of_irq_parse_one(np, index, &sup_args) ? शून्य : sup_args.np;
पूर्ण

अटल स्थिर काष्ठा supplier_bindings of_supplier_bindings[] = अणु
	अणु .parse_prop = parse_घड़ीs, पूर्ण,
	अणु .parse_prop = parse_पूर्णांकerconnects, पूर्ण,
	अणु .parse_prop = parse_iommus, .optional = true, पूर्ण,
	अणु .parse_prop = parse_iommu_maps, .optional = true, पूर्ण,
	अणु .parse_prop = parse_mboxes, पूर्ण,
	अणु .parse_prop = parse_io_channels, पूर्ण,
	अणु .parse_prop = parse_पूर्णांकerrupt_parent, पूर्ण,
	अणु .parse_prop = parse_dmas, .optional = true, पूर्ण,
	अणु .parse_prop = parse_घातer_करोमुख्यs, पूर्ण,
	अणु .parse_prop = parse_hwlocks, पूर्ण,
	अणु .parse_prop = parse_extcon, पूर्ण,
	अणु .parse_prop = parse_nvmem_cells, पूर्ण,
	अणु .parse_prop = parse_phys, पूर्ण,
	अणु .parse_prop = parse_wakeup_parent, पूर्ण,
	अणु .parse_prop = parse_pinctrl0, पूर्ण,
	अणु .parse_prop = parse_pinctrl1, पूर्ण,
	अणु .parse_prop = parse_pinctrl2, पूर्ण,
	अणु .parse_prop = parse_pinctrl3, पूर्ण,
	अणु .parse_prop = parse_pinctrl4, पूर्ण,
	अणु .parse_prop = parse_pinctrl5, पूर्ण,
	अणु .parse_prop = parse_pinctrl6, पूर्ण,
	अणु .parse_prop = parse_pinctrl7, पूर्ण,
	अणु .parse_prop = parse_pinctrl8, पूर्ण,
	अणु .parse_prop = parse_remote_endpoपूर्णांक, .node_not_dev = true, पूर्ण,
	अणु .parse_prop = parse_gpio_compat, पूर्ण,
	अणु .parse_prop = parse_पूर्णांकerrupts, पूर्ण,
	अणु .parse_prop = parse_regulators, पूर्ण,
	अणु .parse_prop = parse_gpio, पूर्ण,
	अणु .parse_prop = parse_gpios, पूर्ण,
	अणुपूर्ण
पूर्ण;

/**
 * of_link_property - Create device links to suppliers listed in a property
 * @con_np: The consumer device tree node which contains the property
 * @prop_name: Name of property to be parsed
 *
 * This function checks अगर the property @prop_name that is present in the
 * @con_np device tree node is one of the known common device tree bindings
 * that list phandles to suppliers. If @prop_name isn't one, this function
 * करोesn't करो anything.
 *
 * If @prop_name is one, this function attempts to create fwnode links from the
 * consumer device tree node @con_np to all the suppliers device tree nodes
 * listed in @prop_name.
 *
 * Any failed attempt to create a fwnode link will NOT result in an immediate
 * वापस.  of_link_property() must create links to all the available supplier
 * device tree nodes even when attempts to create a link to one or more
 * suppliers fail.
 */
अटल पूर्णांक of_link_property(काष्ठा device_node *con_np, स्थिर अक्षर *prop_name)
अणु
	काष्ठा device_node *phandle;
	स्थिर काष्ठा supplier_bindings *s = of_supplier_bindings;
	अचिन्हित पूर्णांक i = 0;
	bool matched = false;

	/* Do not stop at first failed link, link all available suppliers. */
	जबतक (!matched && s->parse_prop) अणु
		अगर (s->optional && !fw_devlink_is_strict()) अणु
			s++;
			जारी;
		पूर्ण

		जबतक ((phandle = s->parse_prop(con_np, prop_name, i))) अणु
			काष्ठा device_node *con_dev_np;

			con_dev_np = s->node_not_dev
					? of_get_compat_node(con_np)
					: of_node_get(con_np);
			matched = true;
			i++;
			of_link_to_phandle(con_dev_np, phandle);
			of_node_put(phandle);
			of_node_put(con_dev_np);
		पूर्ण
		s++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक of_fwnode_add_links(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा property *p;
	काष्ठा device_node *con_np = to_of_node(fwnode);

	अगर (!con_np)
		वापस -EINVAL;

	क्रम_each_property_of_node(con_np, p)
		of_link_property(con_np, p->name);

	वापस 0;
पूर्ण

स्थिर काष्ठा fwnode_operations of_fwnode_ops = अणु
	.get = of_fwnode_get,
	.put = of_fwnode_put,
	.device_is_available = of_fwnode_device_is_available,
	.device_get_match_data = of_fwnode_device_get_match_data,
	.property_present = of_fwnode_property_present,
	.property_पढ़ो_पूर्णांक_array = of_fwnode_property_पढ़ो_पूर्णांक_array,
	.property_पढ़ो_string_array = of_fwnode_property_पढ़ो_string_array,
	.get_name = of_fwnode_get_name,
	.get_name_prefix = of_fwnode_get_name_prefix,
	.get_parent = of_fwnode_get_parent,
	.get_next_child_node = of_fwnode_get_next_child_node,
	.get_named_child_node = of_fwnode_get_named_child_node,
	.get_reference_args = of_fwnode_get_reference_args,
	.graph_get_next_endpoपूर्णांक = of_fwnode_graph_get_next_endpoपूर्णांक,
	.graph_get_remote_endpoपूर्णांक = of_fwnode_graph_get_remote_endpoपूर्णांक,
	.graph_get_port_parent = of_fwnode_graph_get_port_parent,
	.graph_parse_endpoपूर्णांक = of_fwnode_graph_parse_endpoपूर्णांक,
	.add_links = of_fwnode_add_links,
पूर्ण;
EXPORT_SYMBOL_GPL(of_fwnode_ops);
