<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_XBC_H
#घोषणा _LINUX_XBC_H
/*
 * Extra Boot Config
 * Copyright (C) 2019 Linaro Ltd.
 * Author: Masami Hiramatsu <mhiramat@kernel.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#घोषणा BOOTCONFIG_MAGIC	"#BOOTCONFIG\n"
#घोषणा BOOTCONFIG_MAGIC_LEN	12
#घोषणा BOOTCONFIG_ALIGN_SHIFT	2
#घोषणा BOOTCONFIG_ALIGN	(1 << BOOTCONFIG_ALIGN_SHIFT)
#घोषणा BOOTCONFIG_ALIGN_MASK	(BOOTCONFIG_ALIGN - 1)

/* XBC tree node */
काष्ठा xbc_node अणु
	u16 next;
	u16 child;
	u16 parent;
	u16 data;
पूर्ण __attribute__ ((__packed__));

#घोषणा XBC_KEY		0
#घोषणा XBC_VALUE	(1 << 15)
/* Maximum size of boot config is 32KB - 1 */
#घोषणा XBC_DATA_MAX	(XBC_VALUE - 1)

#घोषणा XBC_NODE_MAX	1024
#घोषणा XBC_KEYLEN_MAX	256
#घोषणा XBC_DEPTH_MAX	16

/* Node tree access raw APIs */
काष्ठा xbc_node * __init xbc_root_node(व्योम);
पूर्णांक __init xbc_node_index(काष्ठा xbc_node *node);
काष्ठा xbc_node * __init xbc_node_get_parent(काष्ठा xbc_node *node);
काष्ठा xbc_node * __init xbc_node_get_child(काष्ठा xbc_node *node);
काष्ठा xbc_node * __init xbc_node_get_next(काष्ठा xbc_node *node);
स्थिर अक्षर * __init xbc_node_get_data(काष्ठा xbc_node *node);

/**
 * xbc_node_is_value() - Test the node is a value node
 * @node: An XBC node.
 *
 * Test the @node is a value node and वापस true अगर a value node, false अगर not.
 */
अटल अंतरभूत __init bool xbc_node_is_value(काष्ठा xbc_node *node)
अणु
	वापस node->data & XBC_VALUE;
पूर्ण

/**
 * xbc_node_is_key() - Test the node is a key node
 * @node: An XBC node.
 *
 * Test the @node is a key node and वापस true अगर a key node, false अगर not.
 */
अटल अंतरभूत __init bool xbc_node_is_key(काष्ठा xbc_node *node)
अणु
	वापस !xbc_node_is_value(node);
पूर्ण

/**
 * xbc_node_is_array() - Test the node is an arraied value node
 * @node: An XBC node.
 *
 * Test the @node is an arraied value node.
 */
अटल अंतरभूत __init bool xbc_node_is_array(काष्ठा xbc_node *node)
अणु
	वापस xbc_node_is_value(node) && node->next != 0;
पूर्ण

/**
 * xbc_node_is_leaf() - Test the node is a leaf key node
 * @node: An XBC node.
 *
 * Test the @node is a leaf key node which is a key node and has a value node
 * or no child. Returns true अगर it is a leaf node, or false अगर not.
 */
अटल अंतरभूत __init bool xbc_node_is_leaf(काष्ठा xbc_node *node)
अणु
	वापस xbc_node_is_key(node) &&
		(!node->child || xbc_node_is_value(xbc_node_get_child(node)));
पूर्ण

/* Tree-based key-value access APIs */
काष्ठा xbc_node * __init xbc_node_find_child(काष्ठा xbc_node *parent,
					     स्थिर अक्षर *key);

स्थिर अक्षर * __init xbc_node_find_value(काष्ठा xbc_node *parent,
					स्थिर अक्षर *key,
					काष्ठा xbc_node **vnode);

काष्ठा xbc_node * __init xbc_node_find_next_leaf(काष्ठा xbc_node *root,
						 काष्ठा xbc_node *leaf);

स्थिर अक्षर * __init xbc_node_find_next_key_value(काष्ठा xbc_node *root,
						 काष्ठा xbc_node **leaf);

/**
 * xbc_find_value() - Find a value which matches the key
 * @key: Search key
 * @vnode: A container poपूर्णांकer of XBC value node.
 *
 * Search a value whose key matches @key from whole of XBC tree and वापस
 * the value अगर found. Found value node is stored in *@vnode.
 * Note that this can वापस 0-length string and store शून्य in *@vnode क्रम
 * key-only (non-value) entry.
 */
अटल अंतरभूत स्थिर अक्षर * __init
xbc_find_value(स्थिर अक्षर *key, काष्ठा xbc_node **vnode)
अणु
	वापस xbc_node_find_value(शून्य, key, vnode);
पूर्ण

/**
 * xbc_find_node() - Find a node which matches the key
 * @key: Search key
 *
 * Search a (key) node whose key matches @key from whole of XBC tree and
 * वापस the node अगर found. If not found, वापसs शून्य.
 */
अटल अंतरभूत काष्ठा xbc_node * __init xbc_find_node(स्थिर अक्षर *key)
अणु
	वापस xbc_node_find_child(शून्य, key);
पूर्ण

/**
 * xbc_array_क्रम_each_value() - Iterate value nodes on an array
 * @anode: An XBC arraied value node
 * @value: A value
 *
 * Iterate array value nodes and values starts from @anode. This is expected to
 * be used with xbc_find_value() and xbc_node_find_value(), so that user can
 * process each array entry node.
 */
#घोषणा xbc_array_क्रम_each_value(anode, value)				\
	क्रम (value = xbc_node_get_data(anode); anode != शून्य ;		\
	     anode = xbc_node_get_next(anode),				\
	     value = anode ? xbc_node_get_data(anode) : शून्य)

/**
 * xbc_node_क्रम_each_child() - Iterate child nodes
 * @parent: An XBC node.
 * @child: Iterated XBC node.
 *
 * Iterate child nodes of @parent. Each child nodes are stored to @child.
 */
#घोषणा xbc_node_क्रम_each_child(parent, child)				\
	क्रम (child = xbc_node_get_child(parent); child != शून्य ;	\
	     child = xbc_node_get_next(child))

/**
 * xbc_node_क्रम_each_array_value() - Iterate array entries of geven key
 * @node: An XBC node.
 * @key: A key string searched under @node
 * @anode: Iterated XBC node of array entry.
 * @value: Iterated value of array entry.
 *
 * Iterate array entries of given @key under @node. Each array entry node
 * is stroed to @anode and @value. If the @node करोesn't have @key node,
 * it करोes nothing.
 * Note that even अगर the found key node has only one value (not array)
 * this executes block once. Hoever, अगर the found key node has no value
 * (key-only node), this करोes nothing. So करोn't use this क्रम testing the
 * key-value pair existence.
 */
#घोषणा xbc_node_क्रम_each_array_value(node, key, anode, value)		\
	क्रम (value = xbc_node_find_value(node, key, &anode); value != शून्य; \
	     anode = xbc_node_get_next(anode),				\
	     value = anode ? xbc_node_get_data(anode) : शून्य)

/**
 * xbc_node_क्रम_each_key_value() - Iterate key-value pairs under a node
 * @node: An XBC node.
 * @knode: Iterated key node
 * @value: Iterated value string
 *
 * Iterate key-value pairs under @node. Each key node and value string are
 * stored in @knode and @value respectively.
 */
#घोषणा xbc_node_क्रम_each_key_value(node, knode, value)			\
	क्रम (knode = शून्य, value = xbc_node_find_next_key_value(node, &knode);\
	     knode != शून्य; value = xbc_node_find_next_key_value(node, &knode))

/**
 * xbc_क्रम_each_key_value() - Iterate key-value pairs
 * @knode: Iterated key node
 * @value: Iterated value string
 *
 * Iterate key-value pairs in whole XBC tree. Each key node and value string
 * are stored in @knode and @value respectively.
 */
#घोषणा xbc_क्रम_each_key_value(knode, value)				\
	xbc_node_क्रम_each_key_value(शून्य, knode, value)

/* Compose partial key */
पूर्णांक __init xbc_node_compose_key_after(काष्ठा xbc_node *root,
			काष्ठा xbc_node *node, अक्षर *buf, माप_प्रकार size);

/**
 * xbc_node_compose_key() - Compose full key string of the XBC node
 * @node: An XBC node.
 * @buf: A buffer to store the key.
 * @size: The size of the @buf.
 *
 * Compose the full-length key of the @node पूर्णांकo @buf. Returns the total
 * length of the key stored in @buf. Or वापसs -EINVAL अगर @node is शून्य,
 * and -दुस्फल अगर the key depth is deeper than max depth.
 */
अटल अंतरभूत पूर्णांक __init xbc_node_compose_key(काष्ठा xbc_node *node,
					      अक्षर *buf, माप_प्रकार size)
अणु
	वापस xbc_node_compose_key_after(शून्य, node, buf, size);
पूर्ण

/* XBC node initializer */
पूर्णांक __init xbc_init(अक्षर *buf, स्थिर अक्षर **emsg, पूर्णांक *epos);


/* XBC cleanup data काष्ठाures */
व्योम __init xbc_destroy_all(व्योम);

/* Debug dump functions */
व्योम __init xbc_debug_dump(व्योम);

#पूर्ण_अगर
