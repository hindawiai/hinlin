<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * fwnode.h - Firmware device node object handle type definition.
 *
 * Copyright (C) 2015, Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#अगर_अघोषित _LINUX_FWNODE_H_
#घोषणा _LINUX_FWNODE_H_

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/err.h>

काष्ठा fwnode_operations;
काष्ठा device;

/*
 * fwnode link flags
 *
 * LINKS_ADDED:	The fwnode has alपढ़ोy be parsed to add fwnode links.
 * NOT_DEVICE:	The fwnode will never be populated as a काष्ठा device.
 * INITIALIZED: The hardware corresponding to fwnode has been initialized.
 */
#घोषणा FWNODE_FLAG_LINKS_ADDED		BIT(0)
#घोषणा FWNODE_FLAG_NOT_DEVICE		BIT(1)
#घोषणा FWNODE_FLAG_INITIALIZED		BIT(2)

काष्ठा fwnode_handle अणु
	काष्ठा fwnode_handle *secondary;
	स्थिर काष्ठा fwnode_operations *ops;
	काष्ठा device *dev;
	काष्ठा list_head suppliers;
	काष्ठा list_head consumers;
	u8 flags;
पूर्ण;

काष्ठा fwnode_link अणु
	काष्ठा fwnode_handle *supplier;
	काष्ठा list_head s_hook;
	काष्ठा fwnode_handle *consumer;
	काष्ठा list_head c_hook;
पूर्ण;

/**
 * काष्ठा fwnode_endpoपूर्णांक - Fwnode graph endpoपूर्णांक
 * @port: Port number
 * @id: Endpoपूर्णांक id
 * @local_fwnode: reference to the related fwnode
 */
काष्ठा fwnode_endpoपूर्णांक अणु
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक id;
	स्थिर काष्ठा fwnode_handle *local_fwnode;
पूर्ण;

/*
 * ports and endpoपूर्णांकs defined as software_nodes should all follow a common
 * naming scheme; use these macros to ensure commonality.
 */
#घोषणा SWNODE_GRAPH_PORT_NAME_FMT		"port@%u"
#घोषणा SWNODE_GRAPH_ENDPOINT_NAME_FMT		"endpoint@%u"

#घोषणा NR_FWNODE_REFERENCE_ARGS	8

/**
 * काष्ठा fwnode_reference_args - Fwnode reference with additional arguments
 * @fwnode:- A reference to the base fwnode
 * @nargs: Number of elements in @args array
 * @args: Integer arguments on the fwnode
 */
काष्ठा fwnode_reference_args अणु
	काष्ठा fwnode_handle *fwnode;
	अचिन्हित पूर्णांक nargs;
	u64 args[NR_FWNODE_REFERENCE_ARGS];
पूर्ण;

/**
 * काष्ठा fwnode_operations - Operations क्रम fwnode पूर्णांकerface
 * @get: Get a reference to an fwnode.
 * @put: Put a reference to an fwnode.
 * @device_is_available: Return true अगर the device is available.
 * @device_get_match_data: Return the device driver match data.
 * @property_present: Return true अगर a property is present.
 * @property_पढ़ो_पूर्णांक_array: Read an array of पूर्णांकeger properties. Return zero on
 *			     success, a negative error code otherwise.
 * @property_पढ़ो_string_array: Read an array of string properties. Return zero
 *				on success, a negative error code otherwise.
 * @get_name: Return the name of an fwnode.
 * @get_name_prefix: Get a prefix क्रम a node (क्रम prपूर्णांकing purposes).
 * @get_parent: Return the parent of an fwnode.
 * @get_next_child_node: Return the next child node in an iteration.
 * @get_named_child_node: Return a child node with a given name.
 * @get_reference_args: Return a reference poपूर्णांकed to by a property, with args
 * @graph_get_next_endpoपूर्णांक: Return an endpoपूर्णांक node in an iteration.
 * @graph_get_remote_endpoपूर्णांक: Return the remote endpoपूर्णांक node of a local
 *			       endpoपूर्णांक node.
 * @graph_get_port_parent: Return the parent node of a port node.
 * @graph_parse_endpoपूर्णांक: Parse endpoपूर्णांक क्रम port and endpoपूर्णांक id.
 * @add_links:	Create fwnode links to all the suppliers of the fwnode. Return
 *		zero on success, a negative error code otherwise.
 */
काष्ठा fwnode_operations अणु
	काष्ठा fwnode_handle *(*get)(काष्ठा fwnode_handle *fwnode);
	व्योम (*put)(काष्ठा fwnode_handle *fwnode);
	bool (*device_is_available)(स्थिर काष्ठा fwnode_handle *fwnode);
	स्थिर व्योम *(*device_get_match_data)(स्थिर काष्ठा fwnode_handle *fwnode,
					     स्थिर काष्ठा device *dev);
	bool (*property_present)(स्थिर काष्ठा fwnode_handle *fwnode,
				 स्थिर अक्षर *propname);
	पूर्णांक (*property_पढ़ो_पूर्णांक_array)(स्थिर काष्ठा fwnode_handle *fwnode,
				       स्थिर अक्षर *propname,
				       अचिन्हित पूर्णांक elem_size, व्योम *val,
				       माप_प्रकार nval);
	पूर्णांक
	(*property_पढ़ो_string_array)(स्थिर काष्ठा fwnode_handle *fwnode_handle,
				      स्थिर अक्षर *propname, स्थिर अक्षर **val,
				      माप_प्रकार nval);
	स्थिर अक्षर *(*get_name)(स्थिर काष्ठा fwnode_handle *fwnode);
	स्थिर अक्षर *(*get_name_prefix)(स्थिर काष्ठा fwnode_handle *fwnode);
	काष्ठा fwnode_handle *(*get_parent)(स्थिर काष्ठा fwnode_handle *fwnode);
	काष्ठा fwnode_handle *
	(*get_next_child_node)(स्थिर काष्ठा fwnode_handle *fwnode,
			       काष्ठा fwnode_handle *child);
	काष्ठा fwnode_handle *
	(*get_named_child_node)(स्थिर काष्ठा fwnode_handle *fwnode,
				स्थिर अक्षर *name);
	पूर्णांक (*get_reference_args)(स्थिर काष्ठा fwnode_handle *fwnode,
				  स्थिर अक्षर *prop, स्थिर अक्षर *nargs_prop,
				  अचिन्हित पूर्णांक nargs, अचिन्हित पूर्णांक index,
				  काष्ठा fwnode_reference_args *args);
	काष्ठा fwnode_handle *
	(*graph_get_next_endpoपूर्णांक)(स्थिर काष्ठा fwnode_handle *fwnode,
				   काष्ठा fwnode_handle *prev);
	काष्ठा fwnode_handle *
	(*graph_get_remote_endpoपूर्णांक)(स्थिर काष्ठा fwnode_handle *fwnode);
	काष्ठा fwnode_handle *
	(*graph_get_port_parent)(काष्ठा fwnode_handle *fwnode);
	पूर्णांक (*graph_parse_endpoपूर्णांक)(स्थिर काष्ठा fwnode_handle *fwnode,
				    काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक);
	पूर्णांक (*add_links)(काष्ठा fwnode_handle *fwnode);
पूर्ण;

#घोषणा fwnode_has_op(fwnode, op)				\
	((fwnode) && (fwnode)->ops && (fwnode)->ops->op)
#घोषणा fwnode_call_पूर्णांक_op(fwnode, op, ...)				\
	(fwnode ? (fwnode_has_op(fwnode, op) ?				\
		   (fwnode)->ops->op(fwnode, ## __VA_ARGS__) : -ENXIO) : \
	 -EINVAL)

#घोषणा fwnode_call_bool_op(fwnode, op, ...)		\
	(fwnode_has_op(fwnode, op) ?			\
	 (fwnode)->ops->op(fwnode, ## __VA_ARGS__) : false)

#घोषणा fwnode_call_ptr_op(fwnode, op, ...)		\
	(fwnode_has_op(fwnode, op) ?			\
	 (fwnode)->ops->op(fwnode, ## __VA_ARGS__) : शून्य)
#घोषणा fwnode_call_व्योम_op(fwnode, op, ...)				\
	करो अणु								\
		अगर (fwnode_has_op(fwnode, op))				\
			(fwnode)->ops->op(fwnode, ## __VA_ARGS__);	\
	पूर्ण जबतक (false)
#घोषणा get_dev_from_fwnode(fwnode)	get_device((fwnode)->dev)

अटल अंतरभूत व्योम fwnode_init(काष्ठा fwnode_handle *fwnode,
			       स्थिर काष्ठा fwnode_operations *ops)
अणु
	fwnode->ops = ops;
	INIT_LIST_HEAD(&fwnode->consumers);
	INIT_LIST_HEAD(&fwnode->suppliers);
पूर्ण

अटल अंतरभूत व्योम fwnode_dev_initialized(काष्ठा fwnode_handle *fwnode,
					  bool initialized)
अणु
	अगर (IS_ERR_OR_शून्य(fwnode))
		वापस;

	अगर (initialized)
		fwnode->flags |= FWNODE_FLAG_INITIALIZED;
	अन्यथा
		fwnode->flags &= ~FWNODE_FLAG_INITIALIZED;
पूर्ण

बाह्य u32 fw_devlink_get_flags(व्योम);
बाह्य bool fw_devlink_is_strict(व्योम);
पूर्णांक fwnode_link_add(काष्ठा fwnode_handle *con, काष्ठा fwnode_handle *sup);
व्योम fwnode_links_purge(काष्ठा fwnode_handle *fwnode);
व्योम fw_devlink_purge_असलent_suppliers(काष्ठा fwnode_handle *fwnode);

#पूर्ण_अगर
