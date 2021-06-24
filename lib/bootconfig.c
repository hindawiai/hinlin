<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Extra Boot Config
 * Masami Hiramatsu <mhiramat@kernel.org>
 */

#घोषणा pr_fmt(fmt)    "bootconfig: " fmt

#समावेश <linux/bootconfig.h>
#समावेश <linux/bug.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/माला.स>

/*
 * Extra Boot Config (XBC) is given as tree-काष्ठाured ascii text of
 * key-value pairs on memory.
 * xbc_parse() parses the text to build a simple tree. Each tree node is
 * simply a key word or a value. A key node may have a next key node or/and
 * a child node (both key and value). A value node may have a next value
 * node (क्रम array).
 */

अटल काष्ठा xbc_node *xbc_nodes __initdata;
अटल पूर्णांक xbc_node_num __initdata;
अटल अक्षर *xbc_data __initdata;
अटल माप_प्रकार xbc_data_size __initdata;
अटल काष्ठा xbc_node *last_parent __initdata;
अटल स्थिर अक्षर *xbc_err_msg __initdata;
अटल पूर्णांक xbc_err_pos __initdata;
अटल पूर्णांक खोलो_brace[XBC_DEPTH_MAX] __initdata;
अटल पूर्णांक brace_index __initdata;

अटल पूर्णांक __init xbc_parse_error(स्थिर अक्षर *msg, स्थिर अक्षर *p)
अणु
	xbc_err_msg = msg;
	xbc_err_pos = (पूर्णांक)(p - xbc_data);

	वापस -EINVAL;
पूर्ण

/**
 * xbc_root_node() - Get the root node of extended boot config
 *
 * Return the address of root node of extended boot config. If the
 * extended boot config is not initiized, वापस शून्य.
 */
काष्ठा xbc_node * __init xbc_root_node(व्योम)
अणु
	अगर (unlikely(!xbc_data))
		वापस शून्य;

	वापस xbc_nodes;
पूर्ण

/**
 * xbc_node_index() - Get the index of XBC node
 * @node: A target node of getting index.
 *
 * Return the index number of @node in XBC node list.
 */
पूर्णांक __init xbc_node_index(काष्ठा xbc_node *node)
अणु
	वापस node - &xbc_nodes[0];
पूर्ण

/**
 * xbc_node_get_parent() - Get the parent XBC node
 * @node: An XBC node.
 *
 * Return the parent node of @node. If the node is top node of the tree,
 * वापस शून्य.
 */
काष्ठा xbc_node * __init xbc_node_get_parent(काष्ठा xbc_node *node)
अणु
	वापस node->parent == XBC_NODE_MAX ? शून्य : &xbc_nodes[node->parent];
पूर्ण

/**
 * xbc_node_get_child() - Get the child XBC node
 * @node: An XBC node.
 *
 * Return the first child node of @node. If the node has no child, वापस
 * शून्य.
 */
काष्ठा xbc_node * __init xbc_node_get_child(काष्ठा xbc_node *node)
अणु
	वापस node->child ? &xbc_nodes[node->child] : शून्य;
पूर्ण

/**
 * xbc_node_get_next() - Get the next sibling XBC node
 * @node: An XBC node.
 *
 * Return the NEXT sibling node of @node. If the node has no next sibling,
 * वापस शून्य. Note that even अगर this वापसs शून्य, it करोesn't mean @node
 * has no siblings. (You also has to check whether the parent's child node
 * is @node or not.)
 */
काष्ठा xbc_node * __init xbc_node_get_next(काष्ठा xbc_node *node)
अणु
	वापस node->next ? &xbc_nodes[node->next] : शून्य;
पूर्ण

/**
 * xbc_node_get_data() - Get the data of XBC node
 * @node: An XBC node.
 *
 * Return the data (which is always a null terminated string) of @node.
 * If the node has invalid data, warn and वापस शून्य.
 */
स्थिर अक्षर * __init xbc_node_get_data(काष्ठा xbc_node *node)
अणु
	पूर्णांक offset = node->data & ~XBC_VALUE;

	अगर (WARN_ON(offset >= xbc_data_size))
		वापस शून्य;

	वापस xbc_data + offset;
पूर्ण

अटल bool __init
xbc_node_match_prefix(काष्ठा xbc_node *node, स्थिर अक्षर **prefix)
अणु
	स्थिर अक्षर *p = xbc_node_get_data(node);
	पूर्णांक len = म_माप(p);

	अगर (म_भेदन(*prefix, p, len))
		वापस false;

	p = *prefix + len;
	अगर (*p == '.')
		p++;
	अन्यथा अगर (*p != '\0')
		वापस false;
	*prefix = p;

	वापस true;
पूर्ण

/**
 * xbc_node_find_child() - Find a child node which matches given key
 * @parent: An XBC node.
 * @key: A key string.
 *
 * Search a node under @parent which matches @key. The @key can contain
 * several words joपूर्णांकed with '.'. If @parent is शून्य, this searches the
 * node from whole tree. Return शून्य अगर no node is matched.
 */
काष्ठा xbc_node * __init
xbc_node_find_child(काष्ठा xbc_node *parent, स्थिर अक्षर *key)
अणु
	काष्ठा xbc_node *node;

	अगर (parent)
		node = xbc_node_get_child(parent);
	अन्यथा
		node = xbc_root_node();

	जबतक (node && xbc_node_is_key(node)) अणु
		अगर (!xbc_node_match_prefix(node, &key))
			node = xbc_node_get_next(node);
		अन्यथा अगर (*key != '\0')
			node = xbc_node_get_child(node);
		अन्यथा
			अवरोध;
	पूर्ण

	वापस node;
पूर्ण

/**
 * xbc_node_find_value() - Find a value node which matches given key
 * @parent: An XBC node.
 * @key: A key string.
 * @vnode: A container poपूर्णांकer of found XBC node.
 *
 * Search a value node under @parent whose (parent) key node matches @key,
 * store it in *@vnode, and वापसs the value string.
 * The @key can contain several words joपूर्णांकed with '.'. If @parent is शून्य,
 * this searches the node from whole tree. Return the value string अगर a
 * matched key found, वापस शून्य अगर no node is matched.
 * Note that this वापसs 0-length string and stores शून्य in *@vnode अगर the
 * key has no value. And also it will वापस the value of the first entry अगर
 * the value is an array.
 */
स्थिर अक्षर * __init
xbc_node_find_value(काष्ठा xbc_node *parent, स्थिर अक्षर *key,
		    काष्ठा xbc_node **vnode)
अणु
	काष्ठा xbc_node *node = xbc_node_find_child(parent, key);

	अगर (!node || !xbc_node_is_key(node))
		वापस शून्य;

	node = xbc_node_get_child(node);
	अगर (node && !xbc_node_is_value(node))
		वापस शून्य;

	अगर (vnode)
		*vnode = node;

	वापस node ? xbc_node_get_data(node) : "";
पूर्ण

/**
 * xbc_node_compose_key_after() - Compose partial key string of the XBC node
 * @root: Root XBC node
 * @node: Target XBC node.
 * @buf: A buffer to store the key.
 * @size: The size of the @buf.
 *
 * Compose the partial key of the @node पूर्णांकo @buf, which is starting right
 * after @root (@root is not included.) If @root is शून्य, this वापसs full
 * key words of @node.
 * Returns the total length of the key stored in @buf. Returns -EINVAL
 * अगर @node is शून्य or @root is not the ancestor of @node or @root is @node,
 * or वापसs -दुस्फल अगर the key depth is deeper than max depth.
 * This is expected to be used with xbc_find_node() to list up all (child)
 * keys under given key.
 */
पूर्णांक __init xbc_node_compose_key_after(काष्ठा xbc_node *root,
				      काष्ठा xbc_node *node,
				      अक्षर *buf, माप_प्रकार size)
अणु
	u16 keys[XBC_DEPTH_MAX];
	पूर्णांक depth = 0, ret = 0, total = 0;

	अगर (!node || node == root)
		वापस -EINVAL;

	अगर (xbc_node_is_value(node))
		node = xbc_node_get_parent(node);

	जबतक (node && node != root) अणु
		keys[depth++] = xbc_node_index(node);
		अगर (depth == XBC_DEPTH_MAX)
			वापस -दुस्फल;
		node = xbc_node_get_parent(node);
	पूर्ण
	अगर (!node && root)
		वापस -EINVAL;

	जबतक (--depth >= 0) अणु
		node = xbc_nodes + keys[depth];
		ret = snम_लिखो(buf, size, "%s%s", xbc_node_get_data(node),
			       depth ? "." : "");
		अगर (ret < 0)
			वापस ret;
		अगर (ret > size) अणु
			size = 0;
		पूर्ण अन्यथा अणु
			size -= ret;
			buf += ret;
		पूर्ण
		total += ret;
	पूर्ण

	वापस total;
पूर्ण

/**
 * xbc_node_find_next_leaf() - Find the next leaf node under given node
 * @root: An XBC root node
 * @node: An XBC node which starts from.
 *
 * Search the next leaf node (which means the terminal key node) of @node
 * under @root node (including @root node itself).
 * Return the next node or शून्य अगर next leaf node is not found.
 */
काष्ठा xbc_node * __init xbc_node_find_next_leaf(काष्ठा xbc_node *root,
						 काष्ठा xbc_node *node)
अणु
	अगर (unlikely(!xbc_data))
		वापस शून्य;

	अगर (!node) अणु	/* First try */
		node = root;
		अगर (!node)
			node = xbc_nodes;
	पूर्ण अन्यथा अणु
		अगर (node == root)	/* @root was a leaf, no child node. */
			वापस शून्य;

		जबतक (!node->next) अणु
			node = xbc_node_get_parent(node);
			अगर (node == root)
				वापस शून्य;
			/* User passed a node which is not uder parent */
			अगर (WARN_ON(!node))
				वापस शून्य;
		पूर्ण
		node = xbc_node_get_next(node);
	पूर्ण

	जबतक (node && !xbc_node_is_leaf(node))
		node = xbc_node_get_child(node);

	वापस node;
पूर्ण

/**
 * xbc_node_find_next_key_value() - Find the next key-value pair nodes
 * @root: An XBC root node
 * @leaf: A container poपूर्णांकer of XBC node which starts from.
 *
 * Search the next leaf node (which means the terminal key node) of *@leaf
 * under @root node. Returns the value and update *@leaf अगर next leaf node
 * is found, or शून्य अगर no next leaf node is found.
 * Note that this वापसs 0-length string अगर the key has no value, or
 * the value of the first entry अगर the value is an array.
 */
स्थिर अक्षर * __init xbc_node_find_next_key_value(काष्ठा xbc_node *root,
						 काष्ठा xbc_node **leaf)
अणु
	/* tip must be passed */
	अगर (WARN_ON(!leaf))
		वापस शून्य;

	*leaf = xbc_node_find_next_leaf(root, *leaf);
	अगर (!*leaf)
		वापस शून्य;
	अगर ((*leaf)->child)
		वापस xbc_node_get_data(xbc_node_get_child(*leaf));
	अन्यथा
		वापस "";	/* No value key */
पूर्ण

/* XBC parse and tree build */

अटल पूर्णांक __init xbc_init_node(काष्ठा xbc_node *node, अक्षर *data, u32 flag)
अणु
	अचिन्हित दीर्घ offset = data - xbc_data;

	अगर (WARN_ON(offset >= XBC_DATA_MAX))
		वापस -EINVAL;

	node->data = (u16)offset | flag;
	node->child = 0;
	node->next = 0;

	वापस 0;
पूर्ण

अटल काष्ठा xbc_node * __init xbc_add_node(अक्षर *data, u32 flag)
अणु
	काष्ठा xbc_node *node;

	अगर (xbc_node_num == XBC_NODE_MAX)
		वापस शून्य;

	node = &xbc_nodes[xbc_node_num++];
	अगर (xbc_init_node(node, data, flag) < 0)
		वापस शून्य;

	वापस node;
पूर्ण

अटल अंतरभूत __init काष्ठा xbc_node *xbc_last_sibling(काष्ठा xbc_node *node)
अणु
	जबतक (node->next)
		node = xbc_node_get_next(node);

	वापस node;
पूर्ण

अटल काष्ठा xbc_node * __init xbc_add_sibling(अक्षर *data, u32 flag)
अणु
	काष्ठा xbc_node *sib, *node = xbc_add_node(data, flag);

	अगर (node) अणु
		अगर (!last_parent) अणु
			node->parent = XBC_NODE_MAX;
			sib = xbc_last_sibling(xbc_nodes);
			sib->next = xbc_node_index(node);
		पूर्ण अन्यथा अणु
			node->parent = xbc_node_index(last_parent);
			अगर (!last_parent->child) अणु
				last_parent->child = xbc_node_index(node);
			पूर्ण अन्यथा अणु
				sib = xbc_node_get_child(last_parent);
				sib = xbc_last_sibling(sib);
				sib->next = xbc_node_index(node);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		xbc_parse_error("Too many nodes", data);

	वापस node;
पूर्ण

अटल अंतरभूत __init काष्ठा xbc_node *xbc_add_child(अक्षर *data, u32 flag)
अणु
	काष्ठा xbc_node *node = xbc_add_sibling(data, flag);

	अगर (node)
		last_parent = node;

	वापस node;
पूर्ण

अटल अंतरभूत __init bool xbc_valid_keyword(अक्षर *key)
अणु
	अगर (key[0] == '\0')
		वापस false;

	जबतक (है_अक्षर_अंक(*key) || *key == '-' || *key == '_')
		key++;

	वापस *key == '\0';
पूर्ण

अटल अक्षर *skip_comment(अक्षर *p)
अणु
	अक्षर *ret;

	ret = म_अक्षर(p, '\n');
	अगर (!ret)
		ret = p + म_माप(p);
	अन्यथा
		ret++;

	वापस ret;
पूर्ण

अटल अक्षर *skip_spaces_until_newline(अक्षर *p)
अणु
	जबतक (है_खाली(*p) && *p != '\n')
		p++;
	वापस p;
पूर्ण

अटल पूर्णांक __init __xbc_खोलो_brace(अक्षर *p)
अणु
	/* Push the last key as खोलो brace */
	खोलो_brace[brace_index++] = xbc_node_index(last_parent);
	अगर (brace_index >= XBC_DEPTH_MAX)
		वापस xbc_parse_error("Exceed max depth of braces", p);

	वापस 0;
पूर्ण

अटल पूर्णांक __init __xbc_बंद_brace(अक्षर *p)
अणु
	brace_index--;
	अगर (!last_parent || brace_index < 0 ||
	    (खोलो_brace[brace_index] != xbc_node_index(last_parent)))
		वापस xbc_parse_error("Unexpected closing brace", p);

	अगर (brace_index == 0)
		last_parent = शून्य;
	अन्यथा
		last_parent = &xbc_nodes[खोलो_brace[brace_index - 1]];

	वापस 0;
पूर्ण

/*
 * Return delimiter or error, no node added. As same as lib/cmdline.c,
 * you can use " around spaces, but can't escape " क्रम value.
 */
अटल पूर्णांक __init __xbc_parse_value(अक्षर **__v, अक्षर **__n)
अणु
	अक्षर *p, *v = *__v;
	पूर्णांक c, quotes = 0;

	v = skip_spaces(v);
	जबतक (*v == '#') अणु
		v = skip_comment(v);
		v = skip_spaces(v);
	पूर्ण
	अगर (*v == '"' || *v == '\'') अणु
		quotes = *v;
		v++;
	पूर्ण
	p = v - 1;
	जबतक ((c = *++p)) अणु
		अगर (!है_छाप(c) && !है_खाली(c))
			वापस xbc_parse_error("Non printable value", p);
		अगर (quotes) अणु
			अगर (c != quotes)
				जारी;
			quotes = 0;
			*p++ = '\0';
			p = skip_spaces_until_newline(p);
			c = *p;
			अगर (c && !म_अक्षर(",;\n#}", c))
				वापस xbc_parse_error("No value delimiter", p);
			अगर (*p)
				p++;
			अवरोध;
		पूर्ण
		अगर (म_अक्षर(",;\n#}", c)) अणु
			*p++ = '\0';
			v = strim(v);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (quotes)
		वापस xbc_parse_error("No closing quotes", p);
	अगर (c == '#') अणु
		p = skip_comment(p);
		c = '\n';	/* A comment must be treated as a newline */
	पूर्ण
	*__n = p;
	*__v = v;

	वापस c;
पूर्ण

अटल पूर्णांक __init xbc_parse_array(अक्षर **__v)
अणु
	काष्ठा xbc_node *node;
	अक्षर *next;
	पूर्णांक c = 0;

	करो अणु
		c = __xbc_parse_value(__v, &next);
		अगर (c < 0)
			वापस c;

		node = xbc_add_sibling(*__v, XBC_VALUE);
		अगर (!node)
			वापस -ENOMEM;
		*__v = next;
	पूर्ण जबतक (c == ',');
	node->next = 0;

	वापस c;
पूर्ण

अटल अंतरभूत __init
काष्ठा xbc_node *find_match_node(काष्ठा xbc_node *node, अक्षर *k)
अणु
	जबतक (node) अणु
		अगर (!म_भेद(xbc_node_get_data(node), k))
			अवरोध;
		node = xbc_node_get_next(node);
	पूर्ण
	वापस node;
पूर्ण

अटल पूर्णांक __init __xbc_add_key(अक्षर *k)
अणु
	काष्ठा xbc_node *node, *child;

	अगर (!xbc_valid_keyword(k))
		वापस xbc_parse_error("Invalid keyword", k);

	अगर (unlikely(xbc_node_num == 0))
		जाओ add_node;

	अगर (!last_parent)	/* the first level */
		node = find_match_node(xbc_nodes, k);
	अन्यथा अणु
		child = xbc_node_get_child(last_parent);
		अगर (child && xbc_node_is_value(child))
			वापस xbc_parse_error("Subkey is mixed with value", k);
		node = find_match_node(child, k);
	पूर्ण

	अगर (node)
		last_parent = node;
	अन्यथा अणु
add_node:
		node = xbc_add_child(k, XBC_KEY);
		अगर (!node)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init __xbc_parse_keys(अक्षर *k)
अणु
	अक्षर *p;
	पूर्णांक ret;

	k = strim(k);
	जबतक ((p = म_अक्षर(k, '.'))) अणु
		*p++ = '\0';
		ret = __xbc_add_key(k);
		अगर (ret)
			वापस ret;
		k = p;
	पूर्ण

	वापस __xbc_add_key(k);
पूर्ण

अटल पूर्णांक __init xbc_parse_kv(अक्षर **k, अक्षर *v, पूर्णांक op)
अणु
	काष्ठा xbc_node *prev_parent = last_parent;
	काष्ठा xbc_node *child;
	अक्षर *next;
	पूर्णांक c, ret;

	ret = __xbc_parse_keys(*k);
	अगर (ret)
		वापस ret;

	child = xbc_node_get_child(last_parent);
	अगर (child) अणु
		अगर (xbc_node_is_key(child))
			वापस xbc_parse_error("Value is mixed with subkey", v);
		अन्यथा अगर (op == '=')
			वापस xbc_parse_error("Value is redefined", v);
	पूर्ण

	c = __xbc_parse_value(&v, &next);
	अगर (c < 0)
		वापस c;

	अगर (op == ':' && child) अणु
		xbc_init_node(child, v, XBC_VALUE);
	पूर्ण अन्यथा अगर (!xbc_add_sibling(v, XBC_VALUE))
		वापस -ENOMEM;

	अगर (c == ',') अणु	/* Array */
		c = xbc_parse_array(&next);
		अगर (c < 0)
			वापस c;
	पूर्ण

	last_parent = prev_parent;

	अगर (c == '}') अणु
		ret = __xbc_बंद_brace(next - 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	*k = next;

	वापस 0;
पूर्ण

अटल पूर्णांक __init xbc_parse_key(अक्षर **k, अक्षर *n)
अणु
	काष्ठा xbc_node *prev_parent = last_parent;
	पूर्णांक ret;

	*k = strim(*k);
	अगर (**k != '\0') अणु
		ret = __xbc_parse_keys(*k);
		अगर (ret)
			वापस ret;
		last_parent = prev_parent;
	पूर्ण
	*k = n;

	वापस 0;
पूर्ण

अटल पूर्णांक __init xbc_खोलो_brace(अक्षर **k, अक्षर *n)
अणु
	पूर्णांक ret;

	ret = __xbc_parse_keys(*k);
	अगर (ret)
		वापस ret;
	*k = n;

	वापस __xbc_खोलो_brace(n - 1);
पूर्ण

अटल पूर्णांक __init xbc_बंद_brace(अक्षर **k, अक्षर *n)
अणु
	पूर्णांक ret;

	ret = xbc_parse_key(k, n);
	अगर (ret)
		वापस ret;
	/* k is updated in xbc_parse_key() */

	वापस __xbc_बंद_brace(n - 1);
पूर्ण

अटल पूर्णांक __init xbc_verअगरy_tree(व्योम)
अणु
	पूर्णांक i, depth, len, wlen;
	काष्ठा xbc_node *n, *m;

	/* Brace closing */
	अगर (brace_index) अणु
		n = &xbc_nodes[खोलो_brace[brace_index]];
		वापस xbc_parse_error("Brace is not closed",
					xbc_node_get_data(n));
	पूर्ण

	/* Empty tree */
	अगर (xbc_node_num == 0) अणु
		xbc_parse_error("Empty config", xbc_data);
		वापस -ENOENT;
	पूर्ण

	क्रम (i = 0; i < xbc_node_num; i++) अणु
		अगर (xbc_nodes[i].next > xbc_node_num) अणु
			वापस xbc_parse_error("No closing brace",
				xbc_node_get_data(xbc_nodes + i));
		पूर्ण
	पूर्ण

	/* Key tree limitation check */
	n = &xbc_nodes[0];
	depth = 1;
	len = 0;

	जबतक (n) अणु
		wlen = म_माप(xbc_node_get_data(n)) + 1;
		len += wlen;
		अगर (len > XBC_KEYLEN_MAX)
			वापस xbc_parse_error("Too long key length",
				xbc_node_get_data(n));

		m = xbc_node_get_child(n);
		अगर (m && xbc_node_is_key(m)) अणु
			n = m;
			depth++;
			अगर (depth > XBC_DEPTH_MAX)
				वापस xbc_parse_error("Too many key words",
						xbc_node_get_data(n));
			जारी;
		पूर्ण
		len -= wlen;
		m = xbc_node_get_next(n);
		जबतक (!m) अणु
			n = xbc_node_get_parent(n);
			अगर (!n)
				अवरोध;
			len -= म_माप(xbc_node_get_data(n)) + 1;
			depth--;
			m = xbc_node_get_next(n);
		पूर्ण
		n = m;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xbc_destroy_all() - Clean up all parsed bootconfig
 *
 * This clears all data काष्ठाures of parsed bootconfig on memory.
 * If you need to reuse xbc_init() with new boot config, you can
 * use this.
 */
व्योम __init xbc_destroy_all(व्योम)
अणु
	xbc_data = शून्य;
	xbc_data_size = 0;
	xbc_node_num = 0;
	memblock_मुक्त(__pa(xbc_nodes), माप(काष्ठा xbc_node) * XBC_NODE_MAX);
	xbc_nodes = शून्य;
	brace_index = 0;
पूर्ण

/**
 * xbc_init() - Parse given XBC file and build XBC पूर्णांकernal tree
 * @buf: boot config text
 * @emsg: A poपूर्णांकer of स्थिर अक्षर * to store the error message
 * @epos: A poपूर्णांकer of पूर्णांक to store the error position
 *
 * This parses the boot config text in @buf. @buf must be a
 * null terminated string and smaller than XBC_DATA_MAX.
 * Return the number of stored nodes (>0) अगर succeeded, or -त्रुटि_सं
 * अगर there is any error.
 * In error हालs, @emsg will be updated with an error message and
 * @epos will be updated with the error position which is the byte offset
 * of @buf. If the error is not a parser error, @epos will be -1.
 */
पूर्णांक __init xbc_init(अक्षर *buf, स्थिर अक्षर **emsg, पूर्णांक *epos)
अणु
	अक्षर *p, *q;
	पूर्णांक ret, c;

	अगर (epos)
		*epos = -1;

	अगर (xbc_data) अणु
		अगर (emsg)
			*emsg = "Bootconfig is already initialized";
		वापस -EBUSY;
	पूर्ण

	ret = म_माप(buf);
	अगर (ret > XBC_DATA_MAX - 1 || ret == 0) अणु
		अगर (emsg)
			*emsg = ret ? "Config data is too big" :
				"Config data is empty";
		वापस -दुस्फल;
	पूर्ण

	xbc_nodes = memblock_alloc(माप(काष्ठा xbc_node) * XBC_NODE_MAX,
				   SMP_CACHE_BYTES);
	अगर (!xbc_nodes) अणु
		अगर (emsg)
			*emsg = "Failed to allocate bootconfig nodes";
		वापस -ENOMEM;
	पूर्ण
	स_रखो(xbc_nodes, 0, माप(काष्ठा xbc_node) * XBC_NODE_MAX);
	xbc_data = buf;
	xbc_data_size = ret + 1;
	last_parent = शून्य;

	p = buf;
	करो अणु
		q = strpbrk(p, "{}=+;:\n#");
		अगर (!q) अणु
			p = skip_spaces(p);
			अगर (*p != '\0')
				ret = xbc_parse_error("No delimiter", p);
			अवरोध;
		पूर्ण

		c = *q;
		*q++ = '\0';
		चयन (c) अणु
		हाल ':':
		हाल '+':
			अगर (*q++ != '=') अणु
				ret = xbc_parse_error(c == '+' ?
						"Wrong '+' operator" :
						"Wrong ':' operator",
							q - 2);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल '=':
			ret = xbc_parse_kv(&p, q, c);
			अवरोध;
		हाल '{':
			ret = xbc_खोलो_brace(&p, q);
			अवरोध;
		हाल '#':
			q = skip_comment(q);
			fallthrough;
		हाल ';':
		हाल '\n':
			ret = xbc_parse_key(&p, q);
			अवरोध;
		हाल '}':
			ret = xbc_बंद_brace(&p, q);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!ret);

	अगर (!ret)
		ret = xbc_verअगरy_tree();

	अगर (ret < 0) अणु
		अगर (epos)
			*epos = xbc_err_pos;
		अगर (emsg)
			*emsg = xbc_err_msg;
		xbc_destroy_all();
	पूर्ण अन्यथा
		ret = xbc_node_num;

	वापस ret;
पूर्ण

/**
 * xbc_debug_dump() - Dump current XBC node list
 *
 * Dump the current XBC node list on prपूर्णांकk buffer क्रम debug.
 */
व्योम __init xbc_debug_dump(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < xbc_node_num; i++) अणु
		pr_debug("[%d] %s (%s) .next=%d, .child=%d .parent=%d\n", i,
			xbc_node_get_data(xbc_nodes + i),
			xbc_node_is_value(xbc_nodes + i) ? "value" : "key",
			xbc_nodes[i].next, xbc_nodes[i].child,
			xbc_nodes[i].parent);
	पूर्ण
पूर्ण
