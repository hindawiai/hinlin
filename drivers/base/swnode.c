<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Software nodes क्रम the firmware node framework.
 *
 * Copyright (C) 2018, Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

काष्ठा swnode अणु
	काष्ठा kobject kobj;
	काष्ठा fwnode_handle fwnode;
	स्थिर काष्ठा software_node *node;
	पूर्णांक id;

	/* hierarchy */
	काष्ठा ida child_ids;
	काष्ठा list_head entry;
	काष्ठा list_head children;
	काष्ठा swnode *parent;

	अचिन्हित पूर्णांक allocated:1;
	अचिन्हित पूर्णांक managed:1;
पूर्ण;

अटल DEFINE_IDA(swnode_root_ids);
अटल काष्ठा kset *swnode_kset;

#घोषणा kobj_to_swnode(_kobj_) container_of(_kobj_, काष्ठा swnode, kobj)

अटल स्थिर काष्ठा fwnode_operations software_node_ops;

bool is_software_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस !IS_ERR_OR_शून्य(fwnode) && fwnode->ops == &software_node_ops;
पूर्ण
EXPORT_SYMBOL_GPL(is_software_node);

#घोषणा to_swnode(__fwnode)						\
	(अणु								\
		typeof(__fwnode) __to_swnode_fwnode = __fwnode;		\
									\
		is_software_node(__to_swnode_fwnode) ?			\
			container_of(__to_swnode_fwnode,		\
				     काष्ठा swnode, fwnode) : शून्य;	\
	पूर्ण)

अटल अंतरभूत काष्ठा swnode *dev_to_swnode(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);

	अगर (!fwnode)
		वापस शून्य;

	अगर (!is_software_node(fwnode))
		fwnode = fwnode->secondary;

	वापस to_swnode(fwnode);
पूर्ण

अटल काष्ठा swnode *
software_node_to_swnode(स्थिर काष्ठा software_node *node)
अणु
	काष्ठा swnode *swnode = शून्य;
	काष्ठा kobject *k;

	अगर (!node)
		वापस शून्य;

	spin_lock(&swnode_kset->list_lock);

	list_क्रम_each_entry(k, &swnode_kset->list, entry) अणु
		swnode = kobj_to_swnode(k);
		अगर (swnode->node == node)
			अवरोध;
		swnode = शून्य;
	पूर्ण

	spin_unlock(&swnode_kset->list_lock);

	वापस swnode;
पूर्ण

स्थिर काष्ठा software_node *to_software_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर काष्ठा swnode *swnode = to_swnode(fwnode);

	वापस swnode ? swnode->node : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(to_software_node);

काष्ठा fwnode_handle *software_node_fwnode(स्थिर काष्ठा software_node *node)
अणु
	काष्ठा swnode *swnode = software_node_to_swnode(node);

	वापस swnode ? &swnode->fwnode : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(software_node_fwnode);

/* -------------------------------------------------------------------------- */
/* property_entry processing */

अटल स्थिर काष्ठा property_entry *
property_entry_get(स्थिर काष्ठा property_entry *prop, स्थिर अक्षर *name)
अणु
	अगर (!prop)
		वापस शून्य;

	क्रम (; prop->name; prop++)
		अगर (!म_भेद(name, prop->name))
			वापस prop;

	वापस शून्य;
पूर्ण

अटल स्थिर व्योम *property_get_poपूर्णांकer(स्थिर काष्ठा property_entry *prop)
अणु
	अगर (!prop->length)
		वापस शून्य;

	वापस prop->is_अंतरभूत ? &prop->value : prop->poपूर्णांकer;
पूर्ण

अटल स्थिर व्योम *property_entry_find(स्थिर काष्ठा property_entry *props,
				       स्थिर अक्षर *propname, माप_प्रकार length)
अणु
	स्थिर काष्ठा property_entry *prop;
	स्थिर व्योम *poपूर्णांकer;

	prop = property_entry_get(props, propname);
	अगर (!prop)
		वापस ERR_PTR(-EINVAL);
	poपूर्णांकer = property_get_poपूर्णांकer(prop);
	अगर (!poपूर्णांकer)
		वापस ERR_PTR(-ENODATA);
	अगर (length > prop->length)
		वापस ERR_PTR(-EOVERFLOW);
	वापस poपूर्णांकer;
पूर्ण

अटल पूर्णांक
property_entry_count_elems_of_size(स्थिर काष्ठा property_entry *props,
				   स्थिर अक्षर *propname, माप_प्रकार length)
अणु
	स्थिर काष्ठा property_entry *prop;

	prop = property_entry_get(props, propname);
	अगर (!prop)
		वापस -EINVAL;

	वापस prop->length / length;
पूर्ण

अटल पूर्णांक property_entry_पढ़ो_पूर्णांक_array(स्थिर काष्ठा property_entry *props,
					 स्थिर अक्षर *name,
					 अचिन्हित पूर्णांक elem_size, व्योम *val,
					 माप_प्रकार nval)
अणु
	स्थिर व्योम *poपूर्णांकer;
	माप_प्रकार length;

	अगर (!val)
		वापस property_entry_count_elems_of_size(props, name,
							  elem_size);

	अगर (!is_घातer_of_2(elem_size) || elem_size > माप(u64))
		वापस -ENXIO;

	length = nval * elem_size;

	poपूर्णांकer = property_entry_find(props, name, length);
	अगर (IS_ERR(poपूर्णांकer))
		वापस PTR_ERR(poपूर्णांकer);

	स_नकल(val, poपूर्णांकer, length);
	वापस 0;
पूर्ण

अटल पूर्णांक property_entry_पढ़ो_string_array(स्थिर काष्ठा property_entry *props,
					    स्थिर अक्षर *propname,
					    स्थिर अक्षर **strings, माप_प्रकार nval)
अणु
	स्थिर व्योम *poपूर्णांकer;
	माप_प्रकार length;
	पूर्णांक array_len;

	/* Find out the array length. */
	array_len = property_entry_count_elems_of_size(props, propname,
						       माप(स्थिर अक्षर *));
	अगर (array_len < 0)
		वापस array_len;

	/* Return how many there are अगर strings is शून्य. */
	अगर (!strings)
		वापस array_len;

	array_len = min_t(माप_प्रकार, nval, array_len);
	length = array_len * माप(*strings);

	poपूर्णांकer = property_entry_find(props, propname, length);
	अगर (IS_ERR(poपूर्णांकer))
		वापस PTR_ERR(poपूर्णांकer);

	स_नकल(strings, poपूर्णांकer, length);

	वापस array_len;
पूर्ण

अटल व्योम property_entry_मुक्त_data(स्थिर काष्ठा property_entry *p)
अणु
	स्थिर अक्षर * स्थिर *src_str;
	माप_प्रकार i, nval;

	अगर (p->type == DEV_PROP_STRING) अणु
		src_str = property_get_poपूर्णांकer(p);
		nval = p->length / माप(*src_str);
		क्रम (i = 0; i < nval; i++)
			kमुक्त(src_str[i]);
	पूर्ण

	अगर (!p->is_अंतरभूत)
		kमुक्त(p->poपूर्णांकer);

	kमुक्त(p->name);
पूर्ण

अटल bool property_copy_string_array(स्थिर अक्षर **dst_ptr,
				       स्थिर अक्षर * स्थिर *src_ptr,
				       माप_प्रकार nval)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nval; i++) अणु
		dst_ptr[i] = kstrdup(src_ptr[i], GFP_KERNEL);
		अगर (!dst_ptr[i] && src_ptr[i]) अणु
			जबतक (--i >= 0)
				kमुक्त(dst_ptr[i]);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक property_entry_copy_data(काष्ठा property_entry *dst,
				    स्थिर काष्ठा property_entry *src)
अणु
	स्थिर व्योम *poपूर्णांकer = property_get_poपूर्णांकer(src);
	व्योम *dst_ptr;
	माप_प्रकार nval;

	/*
	 * Properties with no data should not be marked as stored
	 * out of line.
	 */
	अगर (!src->is_अंतरभूत && !src->length)
		वापस -ENODATA;

	/*
	 * Reference properties are never stored अंतरभूत as
	 * they are too big.
	 */
	अगर (src->type == DEV_PROP_REF && src->is_अंतरभूत)
		वापस -EINVAL;

	अगर (src->length <= माप(dst->value)) अणु
		dst_ptr = &dst->value;
		dst->is_अंतरभूत = true;
	पूर्ण अन्यथा अणु
		dst_ptr = kदो_स्मृति(src->length, GFP_KERNEL);
		अगर (!dst_ptr)
			वापस -ENOMEM;
		dst->poपूर्णांकer = dst_ptr;
	पूर्ण

	अगर (src->type == DEV_PROP_STRING) अणु
		nval = src->length / माप(स्थिर अक्षर *);
		अगर (!property_copy_string_array(dst_ptr, poपूर्णांकer, nval)) अणु
			अगर (!dst->is_अंतरभूत)
				kमुक्त(dst->poपूर्णांकer);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(dst_ptr, poपूर्णांकer, src->length);
	पूर्ण

	dst->length = src->length;
	dst->type = src->type;
	dst->name = kstrdup(src->name, GFP_KERNEL);
	अगर (!dst->name) अणु
		property_entry_मुक्त_data(dst);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * property_entries_dup - duplicate array of properties
 * @properties: array of properties to copy
 *
 * This function creates a deep copy of the given शून्य-terminated array
 * of property entries.
 */
काष्ठा property_entry *
property_entries_dup(स्थिर काष्ठा property_entry *properties)
अणु
	काष्ठा property_entry *p;
	पूर्णांक i, n = 0;
	पूर्णांक ret;

	अगर (!properties)
		वापस शून्य;

	जबतक (properties[n].name)
		n++;

	p = kसुस्मृति(n + 1, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < n; i++) अणु
		ret = property_entry_copy_data(&p[i], &properties[i]);
		अगर (ret) अणु
			जबतक (--i >= 0)
				property_entry_मुक्त_data(&p[i]);
			kमुक्त(p);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(property_entries_dup);

/**
 * property_entries_मुक्त - मुक्त previously allocated array of properties
 * @properties: array of properties to destroy
 *
 * This function मुक्तs given शून्य-terminated array of property entries,
 * aदीर्घ with their data.
 */
व्योम property_entries_मुक्त(स्थिर काष्ठा property_entry *properties)
अणु
	स्थिर काष्ठा property_entry *p;

	अगर (!properties)
		वापस;

	क्रम (p = properties; p->name; p++)
		property_entry_मुक्त_data(p);

	kमुक्त(properties);
पूर्ण
EXPORT_SYMBOL_GPL(property_entries_मुक्त);

/* -------------------------------------------------------------------------- */
/* fwnode operations */

अटल काष्ठा fwnode_handle *software_node_get(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);

	kobject_get(&swnode->kobj);

	वापस &swnode->fwnode;
पूर्ण

अटल व्योम software_node_put(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);

	kobject_put(&swnode->kobj);
पूर्ण

अटल bool software_node_property_present(स्थिर काष्ठा fwnode_handle *fwnode,
					   स्थिर अक्षर *propname)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);

	वापस !!property_entry_get(swnode->node->properties, propname);
पूर्ण

अटल पूर्णांक software_node_पढ़ो_पूर्णांक_array(स्थिर काष्ठा fwnode_handle *fwnode,
					स्थिर अक्षर *propname,
					अचिन्हित पूर्णांक elem_size, व्योम *val,
					माप_प्रकार nval)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);

	वापस property_entry_पढ़ो_पूर्णांक_array(swnode->node->properties, propname,
					     elem_size, val, nval);
पूर्ण

अटल पूर्णांक software_node_पढ़ो_string_array(स्थिर काष्ठा fwnode_handle *fwnode,
					   स्थिर अक्षर *propname,
					   स्थिर अक्षर **val, माप_प्रकार nval)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);

	वापस property_entry_पढ़ो_string_array(swnode->node->properties,
						propname, val, nval);
पूर्ण

अटल स्थिर अक्षर *
software_node_get_name(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर काष्ठा swnode *swnode = to_swnode(fwnode);

	अगर (!swnode)
		वापस "(null)";

	वापस kobject_name(&swnode->kobj);
पूर्ण

अटल स्थिर अक्षर *
software_node_get_name_prefix(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *parent;
	स्थिर अक्षर *prefix;

	parent = fwnode_get_parent(fwnode);
	अगर (!parent)
		वापस "";

	/* Figure out the prefix from the parents. */
	जबतक (is_software_node(parent))
		parent = fwnode_get_next_parent(parent);

	prefix = fwnode_get_name_prefix(parent);
	fwnode_handle_put(parent);

	/* Guess something अगर prefix was शून्य. */
	वापस prefix ?: "/";
पूर्ण

अटल काष्ठा fwnode_handle *
software_node_get_parent(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);

	अगर (!swnode || !swnode->parent)
		वापस शून्य;

	वापस fwnode_handle_get(&swnode->parent->fwnode);
पूर्ण

अटल काष्ठा fwnode_handle *
software_node_get_next_child(स्थिर काष्ठा fwnode_handle *fwnode,
			     काष्ठा fwnode_handle *child)
अणु
	काष्ठा swnode *p = to_swnode(fwnode);
	काष्ठा swnode *c = to_swnode(child);

	अगर (!p || list_empty(&p->children) ||
	    (c && list_is_last(&c->entry, &p->children))) अणु
		fwnode_handle_put(child);
		वापस शून्य;
	पूर्ण

	अगर (c)
		c = list_next_entry(c, entry);
	अन्यथा
		c = list_first_entry(&p->children, काष्ठा swnode, entry);

	fwnode_handle_put(child);
	वापस fwnode_handle_get(&c->fwnode);
पूर्ण

अटल काष्ठा fwnode_handle *
software_node_get_named_child_node(स्थिर काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *childname)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);
	काष्ठा swnode *child;

	अगर (!swnode || list_empty(&swnode->children))
		वापस शून्य;

	list_क्रम_each_entry(child, &swnode->children, entry) अणु
		अगर (!म_भेद(childname, kobject_name(&child->kobj))) अणु
			kobject_get(&child->kobj);
			वापस &child->fwnode;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
software_node_get_reference_args(स्थिर काष्ठा fwnode_handle *fwnode,
				 स्थिर अक्षर *propname, स्थिर अक्षर *nargs_prop,
				 अचिन्हित पूर्णांक nargs, अचिन्हित पूर्णांक index,
				 काष्ठा fwnode_reference_args *args)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);
	स्थिर काष्ठा software_node_ref_args *ref_array;
	स्थिर काष्ठा software_node_ref_args *ref;
	स्थिर काष्ठा property_entry *prop;
	काष्ठा fwnode_handle *refnode;
	u32 nargs_prop_val;
	पूर्णांक error;
	पूर्णांक i;

	अगर (!swnode)
		वापस -ENOENT;

	prop = property_entry_get(swnode->node->properties, propname);
	अगर (!prop)
		वापस -ENOENT;

	अगर (prop->type != DEV_PROP_REF)
		वापस -EINVAL;

	/*
	 * We expect that references are never stored अंतरभूत, even
	 * single ones, as they are too big.
	 */
	अगर (prop->is_अंतरभूत)
		वापस -EINVAL;

	अगर (index * माप(*ref) >= prop->length)
		वापस -ENOENT;

	ref_array = prop->poपूर्णांकer;
	ref = &ref_array[index];

	refnode = software_node_fwnode(ref->node);
	अगर (!refnode)
		वापस -ENOENT;

	अगर (nargs_prop) अणु
		error = property_entry_पढ़ो_पूर्णांक_array(swnode->node->properties,
						      nargs_prop, माप(u32),
						      &nargs_prop_val, 1);
		अगर (error)
			वापस error;

		nargs = nargs_prop_val;
	पूर्ण

	अगर (nargs > NR_FWNODE_REFERENCE_ARGS)
		वापस -EINVAL;

	args->fwnode = software_node_get(refnode);
	args->nargs = nargs;

	क्रम (i = 0; i < nargs; i++)
		args->args[i] = ref->args[i];

	वापस 0;
पूर्ण

अटल काष्ठा fwnode_handle *
swnode_graph_find_next_port(स्थिर काष्ठा fwnode_handle *parent,
			    काष्ठा fwnode_handle *port)
अणु
	काष्ठा fwnode_handle *old = port;

	जबतक ((port = software_node_get_next_child(parent, old))) अणु
		/*
		 * fwnode ports have naming style "port@", so we search क्रम any
		 * children that follow that convention.
		 */
		अगर (!म_भेदन(to_swnode(port)->node->name, "port@",
			     म_माप("port@")))
			वापस port;
		old = port;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा fwnode_handle *
software_node_graph_get_next_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
				      काष्ठा fwnode_handle *endpoपूर्णांक)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);
	काष्ठा fwnode_handle *parent;
	काष्ठा fwnode_handle *port;

	अगर (!swnode)
		वापस शून्य;

	अगर (endpoपूर्णांक) अणु
		port = software_node_get_parent(endpoपूर्णांक);
		parent = software_node_get_parent(port);
	पूर्ण अन्यथा अणु
		parent = software_node_get_named_child_node(fwnode, "ports");
		अगर (!parent)
			parent = software_node_get(&swnode->fwnode);

		port = swnode_graph_find_next_port(parent, शून्य);
	पूर्ण

	क्रम (; port; port = swnode_graph_find_next_port(parent, port)) अणु
		endpoपूर्णांक = software_node_get_next_child(port, endpoपूर्णांक);
		अगर (endpoपूर्णांक) अणु
			fwnode_handle_put(port);
			अवरोध;
		पूर्ण
	पूर्ण

	fwnode_handle_put(parent);

	वापस endpoपूर्णांक;
पूर्ण

अटल काष्ठा fwnode_handle *
software_node_graph_get_remote_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);
	स्थिर काष्ठा software_node_ref_args *ref;
	स्थिर काष्ठा property_entry *prop;

	अगर (!swnode)
		वापस शून्य;

	prop = property_entry_get(swnode->node->properties, "remote-endpoint");
	अगर (!prop || prop->type != DEV_PROP_REF || prop->is_अंतरभूत)
		वापस शून्य;

	ref = prop->poपूर्णांकer;

	वापस software_node_get(software_node_fwnode(ref[0].node));
पूर्ण

अटल काष्ठा fwnode_handle *
software_node_graph_get_port_parent(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);

	swnode = swnode->parent;
	अगर (swnode && !म_भेद(swnode->node->name, "ports"))
		swnode = swnode->parent;

	वापस swnode ? software_node_get(&swnode->fwnode) : शून्य;
पूर्ण

अटल पूर्णांक
software_node_graph_parse_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
				   काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);
	स्थिर अक्षर *parent_name = swnode->parent->node->name;
	पूर्णांक ret;

	अगर (म_माप("port@") >= म_माप(parent_name) ||
	    म_भेदन(parent_name, "port@", म_माप("port@")))
		वापस -EINVAL;

	/* Ports have naming style "port@n", we need to select the n */
	ret = kstrtou32(parent_name + म_माप("port@"), 10, &endpoपूर्णांक->port);
	अगर (ret)
		वापस ret;

	endpoपूर्णांक->id = swnode->id;
	endpoपूर्णांक->local_fwnode = fwnode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fwnode_operations software_node_ops = अणु
	.get = software_node_get,
	.put = software_node_put,
	.property_present = software_node_property_present,
	.property_पढ़ो_पूर्णांक_array = software_node_पढ़ो_पूर्णांक_array,
	.property_पढ़ो_string_array = software_node_पढ़ो_string_array,
	.get_name = software_node_get_name,
	.get_name_prefix = software_node_get_name_prefix,
	.get_parent = software_node_get_parent,
	.get_next_child_node = software_node_get_next_child,
	.get_named_child_node = software_node_get_named_child_node,
	.get_reference_args = software_node_get_reference_args,
	.graph_get_next_endpoपूर्णांक = software_node_graph_get_next_endpoपूर्णांक,
	.graph_get_remote_endpoपूर्णांक = software_node_graph_get_remote_endpoपूर्णांक,
	.graph_get_port_parent = software_node_graph_get_port_parent,
	.graph_parse_endpoपूर्णांक = software_node_graph_parse_endpoपूर्णांक,
पूर्ण;

/* -------------------------------------------------------------------------- */

/**
 * software_node_find_by_name - Find software node by name
 * @parent: Parent of the software node
 * @name: Name of the software node
 *
 * The function will find a node that is child of @parent and that is named
 * @name. If no node is found, the function वापसs शून्य.
 *
 * NOTE: you will need to drop the reference with fwnode_handle_put() after use.
 */
स्थिर काष्ठा software_node *
software_node_find_by_name(स्थिर काष्ठा software_node *parent, स्थिर अक्षर *name)
अणु
	काष्ठा swnode *swnode = शून्य;
	काष्ठा kobject *k;

	अगर (!name)
		वापस शून्य;

	spin_lock(&swnode_kset->list_lock);

	list_क्रम_each_entry(k, &swnode_kset->list, entry) अणु
		swnode = kobj_to_swnode(k);
		अगर (parent == swnode->node->parent && swnode->node->name &&
		    !म_भेद(name, swnode->node->name)) अणु
			kobject_get(&swnode->kobj);
			अवरोध;
		पूर्ण
		swnode = शून्य;
	पूर्ण

	spin_unlock(&swnode_kset->list_lock);

	वापस swnode ? swnode->node : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(software_node_find_by_name);

अटल काष्ठा software_node *software_node_alloc(स्थिर काष्ठा property_entry *properties)
अणु
	काष्ठा property_entry *props;
	काष्ठा software_node *node;

	props = property_entries_dup(properties);
	अगर (IS_ERR(props))
		वापस ERR_CAST(props);

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node) अणु
		property_entries_मुक्त(props);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	node->properties = props;

	वापस node;
पूर्ण

अटल व्योम software_node_मुक्त(स्थिर काष्ठा software_node *node)
अणु
	property_entries_मुक्त(node->properties);
	kमुक्त(node);
पूर्ण

अटल व्योम software_node_release(काष्ठा kobject *kobj)
अणु
	काष्ठा swnode *swnode = kobj_to_swnode(kobj);

	अगर (swnode->parent) अणु
		ida_simple_हटाओ(&swnode->parent->child_ids, swnode->id);
		list_del(&swnode->entry);
	पूर्ण अन्यथा अणु
		ida_simple_हटाओ(&swnode_root_ids, swnode->id);
	पूर्ण

	अगर (swnode->allocated)
		software_node_मुक्त(swnode->node);

	ida_destroy(&swnode->child_ids);
	kमुक्त(swnode);
पूर्ण

अटल काष्ठा kobj_type software_node_type = अणु
	.release = software_node_release,
	.sysfs_ops = &kobj_sysfs_ops,
पूर्ण;

अटल काष्ठा fwnode_handle *
swnode_रेजिस्टर(स्थिर काष्ठा software_node *node, काष्ठा swnode *parent,
		अचिन्हित पूर्णांक allocated)
अणु
	काष्ठा swnode *swnode;
	पूर्णांक ret;

	swnode = kzalloc(माप(*swnode), GFP_KERNEL);
	अगर (!swnode)
		वापस ERR_PTR(-ENOMEM);

	ret = ida_simple_get(parent ? &parent->child_ids : &swnode_root_ids,
			     0, 0, GFP_KERNEL);
	अगर (ret < 0) अणु
		kमुक्त(swnode);
		वापस ERR_PTR(ret);
	पूर्ण

	swnode->id = ret;
	swnode->node = node;
	swnode->parent = parent;
	swnode->kobj.kset = swnode_kset;
	fwnode_init(&swnode->fwnode, &software_node_ops);

	ida_init(&swnode->child_ids);
	INIT_LIST_HEAD(&swnode->entry);
	INIT_LIST_HEAD(&swnode->children);

	अगर (node->name)
		ret = kobject_init_and_add(&swnode->kobj, &software_node_type,
					   parent ? &parent->kobj : शून्य,
					   "%s", node->name);
	अन्यथा
		ret = kobject_init_and_add(&swnode->kobj, &software_node_type,
					   parent ? &parent->kobj : शून्य,
					   "node%d", swnode->id);
	अगर (ret) अणु
		kobject_put(&swnode->kobj);
		वापस ERR_PTR(ret);
	पूर्ण

	/*
	 * Assign the flag only in the successful हाल, so
	 * the above kobject_put() won't mess up with properties.
	 */
	swnode->allocated = allocated;

	अगर (parent)
		list_add_tail(&swnode->entry, &parent->children);

	kobject_uevent(&swnode->kobj, KOBJ_ADD);
	वापस &swnode->fwnode;
पूर्ण

/**
 * software_node_रेजिस्टर_nodes - Register an array of software nodes
 * @nodes: Zero terminated array of software nodes to be रेजिस्टरed
 *
 * Register multiple software nodes at once. If any node in the array
 * has its .parent poपूर्णांकer set (which can only be to another software_node),
 * then its parent **must** have been रेजिस्टरed beक्रमe it is; either outside
 * of this function or by ordering the array such that parent comes beक्रमe
 * child.
 */
पूर्णांक software_node_रेजिस्टर_nodes(स्थिर काष्ठा software_node *nodes)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; nodes[i].name; i++) अणु
		स्थिर काष्ठा software_node *parent = nodes[i].parent;

		अगर (parent && !software_node_to_swnode(parent)) अणु
			ret = -EINVAL;
			जाओ err_unरेजिस्टर_nodes;
		पूर्ण

		ret = software_node_रेजिस्टर(&nodes[i]);
		अगर (ret)
			जाओ err_unरेजिस्टर_nodes;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_nodes:
	software_node_unरेजिस्टर_nodes(nodes);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(software_node_रेजिस्टर_nodes);

/**
 * software_node_unरेजिस्टर_nodes - Unरेजिस्टर an array of software nodes
 * @nodes: Zero terminated array of software nodes to be unरेजिस्टरed
 *
 * Unरेजिस्टर multiple software nodes at once. If parent poपूर्णांकers are set up
 * in any of the software nodes then the array **must** be ordered such that
 * parents come beक्रमe their children.
 *
 * NOTE: If you are uncertain whether the array is ordered such that
 * parents will be unरेजिस्टरed beक्रमe their children, it is wiser to
 * हटाओ the nodes inभागidually, in the correct order (child beक्रमe
 * parent).
 */
व्योम software_node_unरेजिस्टर_nodes(स्थिर काष्ठा software_node *nodes)
अणु
	अचिन्हित पूर्णांक i = 0;

	जबतक (nodes[i].name)
		i++;

	जबतक (i--)
		software_node_unरेजिस्टर(&nodes[i]);
पूर्ण
EXPORT_SYMBOL_GPL(software_node_unरेजिस्टर_nodes);

/**
 * software_node_रेजिस्टर_node_group - Register a group of software nodes
 * @node_group: शून्य terminated array of software node poपूर्णांकers to be रेजिस्टरed
 *
 * Register multiple software nodes at once. If any node in the array
 * has its .parent poपूर्णांकer set (which can only be to another software_node),
 * then its parent **must** have been रेजिस्टरed beक्रमe it is; either outside
 * of this function or by ordering the array such that parent comes beक्रमe
 * child.
 */
पूर्णांक software_node_रेजिस्टर_node_group(स्थिर काष्ठा software_node **node_group)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!node_group)
		वापस 0;

	क्रम (i = 0; node_group[i]; i++) अणु
		ret = software_node_रेजिस्टर(node_group[i]);
		अगर (ret) अणु
			software_node_unरेजिस्टर_node_group(node_group);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(software_node_रेजिस्टर_node_group);

/**
 * software_node_unरेजिस्टर_node_group - Unरेजिस्टर a group of software nodes
 * @node_group: शून्य terminated array of software node poपूर्णांकers to be unरेजिस्टरed
 *
 * Unरेजिस्टर multiple software nodes at once. If parent poपूर्णांकers are set up
 * in any of the software nodes then the array **must** be ordered such that
 * parents come beक्रमe their children.
 *
 * NOTE: If you are uncertain whether the array is ordered such that
 * parents will be unरेजिस्टरed beक्रमe their children, it is wiser to
 * हटाओ the nodes inभागidually, in the correct order (child beक्रमe
 * parent).
 */
व्योम software_node_unरेजिस्टर_node_group(
		स्थिर काष्ठा software_node **node_group)
अणु
	अचिन्हित पूर्णांक i = 0;

	अगर (!node_group)
		वापस;

	जबतक (node_group[i])
		i++;

	जबतक (i--)
		software_node_unरेजिस्टर(node_group[i]);
पूर्ण
EXPORT_SYMBOL_GPL(software_node_unरेजिस्टर_node_group);

/**
 * software_node_रेजिस्टर - Register अटल software node
 * @node: The software node to be रेजिस्टरed
 */
पूर्णांक software_node_रेजिस्टर(स्थिर काष्ठा software_node *node)
अणु
	काष्ठा swnode *parent = software_node_to_swnode(node->parent);

	अगर (software_node_to_swnode(node))
		वापस -EEXIST;

	अगर (node->parent && !parent)
		वापस -EINVAL;

	वापस PTR_ERR_OR_ZERO(swnode_रेजिस्टर(node, parent, 0));
पूर्ण
EXPORT_SYMBOL_GPL(software_node_रेजिस्टर);

/**
 * software_node_unरेजिस्टर - Unरेजिस्टर अटल software node
 * @node: The software node to be unरेजिस्टरed
 */
व्योम software_node_unरेजिस्टर(स्थिर काष्ठा software_node *node)
अणु
	काष्ठा swnode *swnode;

	swnode = software_node_to_swnode(node);
	अगर (swnode)
		fwnode_हटाओ_software_node(&swnode->fwnode);
पूर्ण
EXPORT_SYMBOL_GPL(software_node_unरेजिस्टर);

काष्ठा fwnode_handle *
fwnode_create_software_node(स्थिर काष्ठा property_entry *properties,
			    स्थिर काष्ठा fwnode_handle *parent)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा software_node *node;
	काष्ठा swnode *p;

	अगर (IS_ERR(parent))
		वापस ERR_CAST(parent);

	p = to_swnode(parent);
	अगर (parent && !p)
		वापस ERR_PTR(-EINVAL);

	node = software_node_alloc(properties);
	अगर (IS_ERR(node))
		वापस ERR_CAST(node);

	node->parent = p ? p->node : शून्य;

	fwnode = swnode_रेजिस्टर(node, p, 1);
	अगर (IS_ERR(fwnode))
		software_node_मुक्त(node);

	वापस fwnode;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_create_software_node);

व्योम fwnode_हटाओ_software_node(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा swnode *swnode = to_swnode(fwnode);

	अगर (!swnode)
		वापस;

	kobject_put(&swnode->kobj);
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_हटाओ_software_node);

/**
 * device_add_software_node - Assign software node to a device
 * @dev: The device the software node is meant क्रम.
 * @node: The software node.
 *
 * This function will make @node the secondary firmware node poपूर्णांकer of @dev. If
 * @dev has no primary node, then @node will become the primary node. The
 * function will रेजिस्टर @node स्वतःmatically अगर it wasn't alपढ़ोy रेजिस्टरed.
 */
पूर्णांक device_add_software_node(काष्ठा device *dev, स्थिर काष्ठा software_node *node)
अणु
	काष्ठा swnode *swnode;
	पूर्णांक ret;

	/* Only one software node per device. */
	अगर (dev_to_swnode(dev))
		वापस -EBUSY;

	swnode = software_node_to_swnode(node);
	अगर (swnode) अणु
		kobject_get(&swnode->kobj);
	पूर्ण अन्यथा अणु
		ret = software_node_रेजिस्टर(node);
		अगर (ret)
			वापस ret;

		swnode = software_node_to_swnode(node);
	पूर्ण

	set_secondary_fwnode(dev, &swnode->fwnode);
	software_node_notअगरy(dev, KOBJ_ADD);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(device_add_software_node);

/**
 * device_हटाओ_software_node - Remove device's software node
 * @dev: The device with the software node.
 *
 * This function will unरेजिस्टर the software node of @dev.
 */
व्योम device_हटाओ_software_node(काष्ठा device *dev)
अणु
	काष्ठा swnode *swnode;

	swnode = dev_to_swnode(dev);
	अगर (!swnode)
		वापस;

	software_node_notअगरy(dev, KOBJ_REMOVE);
	set_secondary_fwnode(dev, शून्य);
	kobject_put(&swnode->kobj);
पूर्ण
EXPORT_SYMBOL_GPL(device_हटाओ_software_node);

/**
 * device_create_managed_software_node - Create a software node क्रम a device
 * @dev: The device the software node is asचिन्हित to.
 * @properties: Device properties क्रम the software node.
 * @parent: Parent of the software node.
 *
 * Creates a software node as a managed resource क्रम @dev, which means the
 * lअगरeसमय of the newly created software node is tied to the lअगरeसमय of @dev.
 * Software nodes created with this function should not be reused or shared
 * because of that. The function takes a deep copy of @properties क्रम the
 * software node.
 *
 * Since the new software node is asचिन्हित directly to @dev, and since it should
 * not be shared, it is not वापसed to the caller. The function वापसs 0 on
 * success, and त्रुटि_सं in हाल of an error.
 */
पूर्णांक device_create_managed_software_node(काष्ठा device *dev,
					स्थिर काष्ठा property_entry *properties,
					स्थिर काष्ठा software_node *parent)
अणु
	काष्ठा fwnode_handle *p = software_node_fwnode(parent);
	काष्ठा fwnode_handle *fwnode;

	अगर (parent && !p)
		वापस -EINVAL;

	fwnode = fwnode_create_software_node(properties, p);
	अगर (IS_ERR(fwnode))
		वापस PTR_ERR(fwnode);

	to_swnode(fwnode)->managed = true;
	set_secondary_fwnode(dev, fwnode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(device_create_managed_software_node);

पूर्णांक software_node_notअगरy(काष्ठा device *dev, अचिन्हित दीर्घ action)
अणु
	काष्ठा swnode *swnode;
	पूर्णांक ret;

	swnode = dev_to_swnode(dev);
	अगर (!swnode)
		वापस 0;

	चयन (action) अणु
	हाल KOBJ_ADD:
		ret = sysfs_create_link_nowarn(&dev->kobj, &swnode->kobj,
					       "software_node");
		अगर (ret)
			अवरोध;

		ret = sysfs_create_link(&swnode->kobj, &dev->kobj,
					dev_name(dev));
		अगर (ret) अणु
			sysfs_हटाओ_link(&dev->kobj, "software_node");
			अवरोध;
		पूर्ण
		kobject_get(&swnode->kobj);
		अवरोध;
	हाल KOBJ_REMOVE:
		sysfs_हटाओ_link(&swnode->kobj, dev_name(dev));
		sysfs_हटाओ_link(&dev->kobj, "software_node");
		kobject_put(&swnode->kobj);

		अगर (swnode->managed) अणु
			set_secondary_fwnode(dev, शून्य);
			kobject_put(&swnode->kobj);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init software_node_init(व्योम)
अणु
	swnode_kset = kset_create_and_add("software_nodes", शून्य, kernel_kobj);
	अगर (!swnode_kset)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
postcore_initcall(software_node_init);

अटल व्योम __निकास software_node_निकास(व्योम)
अणु
	ida_destroy(&swnode_root_ids);
	kset_unरेजिस्टर(swnode_kset);
पूर्ण
__निकासcall(software_node_निकास);
