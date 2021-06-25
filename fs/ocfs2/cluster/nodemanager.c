<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004, 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/configfs.h>

#समावेश "tcp.h"
#समावेश "nodemanager.h"
#समावेश "heartbeat.h"
#समावेश "masklog.h"
#समावेश "sys.h"

/* क्रम now we operate under the निश्चितion that there can be only one
 * cluster active at a समय.  Changing this will require trickling
 * cluster references throughout where nodes are looked up */
काष्ठा o2nm_cluster *o2nm_single_cluster = शून्य;

अटल स्थिर अक्षर *o2nm_fence_method_desc[O2NM_FENCE_METHODS] = अणु
	"reset",	/* O2NM_FENCE_RESET */
	"panic",	/* O2NM_FENCE_PANIC */
पूर्ण;

अटल अंतरभूत व्योम o2nm_lock_subप्रणाली(व्योम);
अटल अंतरभूत व्योम o2nm_unlock_subप्रणाली(व्योम);

काष्ठा o2nm_node *o2nm_get_node_by_num(u8 node_num)
अणु
	काष्ठा o2nm_node *node = शून्य;

	अगर (node_num >= O2NM_MAX_NODES || o2nm_single_cluster == शून्य)
		जाओ out;

	पढ़ो_lock(&o2nm_single_cluster->cl_nodes_lock);
	node = o2nm_single_cluster->cl_nodes[node_num];
	अगर (node)
		config_item_get(&node->nd_item);
	पढ़ो_unlock(&o2nm_single_cluster->cl_nodes_lock);
out:
	वापस node;
पूर्ण
EXPORT_SYMBOL_GPL(o2nm_get_node_by_num);

पूर्णांक o2nm_configured_node_map(अचिन्हित दीर्घ *map, अचिन्हित bytes)
अणु
	काष्ठा o2nm_cluster *cluster = o2nm_single_cluster;

	BUG_ON(bytes < (माप(cluster->cl_nodes_biपंचांगap)));

	अगर (cluster == शून्य)
		वापस -EINVAL;

	पढ़ो_lock(&cluster->cl_nodes_lock);
	स_नकल(map, cluster->cl_nodes_biपंचांगap, माप(cluster->cl_nodes_biपंचांगap));
	पढ़ो_unlock(&cluster->cl_nodes_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(o2nm_configured_node_map);

अटल काष्ठा o2nm_node *o2nm_node_ip_tree_lookup(काष्ठा o2nm_cluster *cluster,
						  __be32 ip_needle,
						  काष्ठा rb_node ***ret_p,
						  काष्ठा rb_node **ret_parent)
अणु
	काष्ठा rb_node **p = &cluster->cl_node_ip_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा o2nm_node *node, *ret = शून्य;

	जबतक (*p) अणु
		पूर्णांक cmp;

		parent = *p;
		node = rb_entry(parent, काष्ठा o2nm_node, nd_ip_node);

		cmp = स_भेद(&ip_needle, &node->nd_ipv4_address,
				माप(ip_needle));
		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (cmp > 0)
			p = &(*p)->rb_right;
		अन्यथा अणु
			ret = node;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret_p != शून्य)
		*ret_p = p;
	अगर (ret_parent != शून्य)
		*ret_parent = parent;

	वापस ret;
पूर्ण

काष्ठा o2nm_node *o2nm_get_node_by_ip(__be32 addr)
अणु
	काष्ठा o2nm_node *node = शून्य;
	काष्ठा o2nm_cluster *cluster = o2nm_single_cluster;

	अगर (cluster == शून्य)
		जाओ out;

	पढ़ो_lock(&cluster->cl_nodes_lock);
	node = o2nm_node_ip_tree_lookup(cluster, addr, शून्य, शून्य);
	अगर (node)
		config_item_get(&node->nd_item);
	पढ़ो_unlock(&cluster->cl_nodes_lock);

out:
	वापस node;
पूर्ण
EXPORT_SYMBOL_GPL(o2nm_get_node_by_ip);

व्योम o2nm_node_put(काष्ठा o2nm_node *node)
अणु
	config_item_put(&node->nd_item);
पूर्ण
EXPORT_SYMBOL_GPL(o2nm_node_put);

व्योम o2nm_node_get(काष्ठा o2nm_node *node)
अणु
	config_item_get(&node->nd_item);
पूर्ण
EXPORT_SYMBOL_GPL(o2nm_node_get);

u8 o2nm_this_node(व्योम)
अणु
	u8 node_num = O2NM_MAX_NODES;

	अगर (o2nm_single_cluster && o2nm_single_cluster->cl_has_local)
		node_num = o2nm_single_cluster->cl_local_node;

	वापस node_num;
पूर्ण
EXPORT_SYMBOL_GPL(o2nm_this_node);

/* node configfs bits */

अटल काष्ठा o2nm_cluster *to_o2nm_cluster(काष्ठा config_item *item)
अणु
	वापस item ?
		container_of(to_config_group(item), काष्ठा o2nm_cluster,
			     cl_group)
		: शून्य;
पूर्ण

अटल काष्ठा o2nm_node *to_o2nm_node(काष्ठा config_item *item)
अणु
	वापस item ? container_of(item, काष्ठा o2nm_node, nd_item) : शून्य;
पूर्ण

अटल व्योम o2nm_node_release(काष्ठा config_item *item)
अणु
	काष्ठा o2nm_node *node = to_o2nm_node(item);
	kमुक्त(node);
पूर्ण

अटल sमाप_प्रकार o2nm_node_num_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", to_o2nm_node(item)->nd_num);
पूर्ण

अटल काष्ठा o2nm_cluster *to_o2nm_cluster_from_node(काष्ठा o2nm_node *node)
अणु
	/* through the first node_set .parent
	 * mycluster/nodes/mynode == o2nm_cluster->o2nm_node_group->o2nm_node */
	अगर (node->nd_item.ci_parent)
		वापस to_o2nm_cluster(node->nd_item.ci_parent->ci_parent);
	अन्यथा
		वापस शून्य;
पूर्ण

क्रमागत अणु
	O2NM_NODE_ATTR_NUM = 0,
	O2NM_NODE_ATTR_PORT,
	O2NM_NODE_ATTR_ADDRESS,
पूर्ण;

अटल sमाप_प्रकार o2nm_node_num_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				   माप_प्रकार count)
अणु
	काष्ठा o2nm_node *node = to_o2nm_node(item);
	काष्ठा o2nm_cluster *cluster;
	अचिन्हित दीर्घ पंचांगp;
	अक्षर *p = (अक्षर *)page;
	पूर्णांक ret = 0;

	पंचांगp = simple_म_से_अदीर्घ(p, &p, 0);
	अगर (!p || (*p && (*p != '\n')))
		वापस -EINVAL;

	अगर (पंचांगp >= O2NM_MAX_NODES)
		वापस -दुस्फल;

	/* once we're in the cl_nodes tree networking can look us up by
	 * node number and try to use our address and port attributes
	 * to connect to this node.. make sure that they've been set
	 * beक्रमe writing the node attribute? */
	अगर (!test_bit(O2NM_NODE_ATTR_ADDRESS, &node->nd_set_attributes) ||
	    !test_bit(O2NM_NODE_ATTR_PORT, &node->nd_set_attributes))
		वापस -EINVAL; /* XXX */

	o2nm_lock_subप्रणाली();
	cluster = to_o2nm_cluster_from_node(node);
	अगर (!cluster) अणु
		o2nm_unlock_subप्रणाली();
		वापस -EINVAL;
	पूर्ण

	ग_लिखो_lock(&cluster->cl_nodes_lock);
	अगर (cluster->cl_nodes[पंचांगp])
		ret = -EEXIST;
	अन्यथा अगर (test_and_set_bit(O2NM_NODE_ATTR_NUM,
			&node->nd_set_attributes))
		ret = -EBUSY;
	अन्यथा  अणु
		cluster->cl_nodes[पंचांगp] = node;
		node->nd_num = पंचांगp;
		set_bit(पंचांगp, cluster->cl_nodes_biपंचांगap);
	पूर्ण
	ग_लिखो_unlock(&cluster->cl_nodes_lock);
	o2nm_unlock_subप्रणाली();

	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल sमाप_प्रकार o2nm_node_ipv4_port_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", ntohs(to_o2nm_node(item)->nd_ipv4_port));
पूर्ण

अटल sमाप_प्रकार o2nm_node_ipv4_port_store(काष्ठा config_item *item,
					 स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा o2nm_node *node = to_o2nm_node(item);
	अचिन्हित दीर्घ पंचांगp;
	अक्षर *p = (अक्षर *)page;

	पंचांगp = simple_म_से_अदीर्घ(p, &p, 0);
	अगर (!p || (*p && (*p != '\n')))
		वापस -EINVAL;

	अगर (पंचांगp == 0)
		वापस -EINVAL;
	अगर (पंचांगp >= (u16)-1)
		वापस -दुस्फल;

	अगर (test_and_set_bit(O2NM_NODE_ATTR_PORT, &node->nd_set_attributes))
		वापस -EBUSY;
	node->nd_ipv4_port = htons(पंचांगp);

	वापस count;
पूर्ण

अटल sमाप_प्रकार o2nm_node_ipv4_address_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%pI4\n", &to_o2nm_node(item)->nd_ipv4_address);
पूर्ण

अटल sमाप_प्रकार o2nm_node_ipv4_address_store(काष्ठा config_item *item,
					    स्थिर अक्षर *page,
					    माप_प्रकार count)
अणु
	काष्ठा o2nm_node *node = to_o2nm_node(item);
	काष्ठा o2nm_cluster *cluster;
	पूर्णांक ret, i;
	काष्ठा rb_node **p, *parent;
	अचिन्हित पूर्णांक octets[4];
	__be32 ipv4_addr = 0;

	ret = माला_पूछो(page, "%3u.%3u.%3u.%3u", &octets[3], &octets[2],
		     &octets[1], &octets[0]);
	अगर (ret != 4)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(octets); i++) अणु
		अगर (octets[i] > 255)
			वापस -दुस्फल;
		be32_add_cpu(&ipv4_addr, octets[i] << (i * 8));
	पूर्ण

	o2nm_lock_subप्रणाली();
	cluster = to_o2nm_cluster_from_node(node);
	अगर (!cluster) अणु
		o2nm_unlock_subप्रणाली();
		वापस -EINVAL;
	पूर्ण

	ret = 0;
	ग_लिखो_lock(&cluster->cl_nodes_lock);
	अगर (o2nm_node_ip_tree_lookup(cluster, ipv4_addr, &p, &parent))
		ret = -EEXIST;
	अन्यथा अगर (test_and_set_bit(O2NM_NODE_ATTR_ADDRESS,
			&node->nd_set_attributes))
		ret = -EBUSY;
	अन्यथा अणु
		rb_link_node(&node->nd_ip_node, parent, p);
		rb_insert_color(&node->nd_ip_node, &cluster->cl_node_ip_tree);
	पूर्ण
	ग_लिखो_unlock(&cluster->cl_nodes_lock);
	o2nm_unlock_subप्रणाली();

	अगर (ret)
		वापस ret;

	स_नकल(&node->nd_ipv4_address, &ipv4_addr, माप(ipv4_addr));

	वापस count;
पूर्ण

अटल sमाप_प्रकार o2nm_node_local_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", to_o2nm_node(item)->nd_local);
पूर्ण

अटल sमाप_प्रकार o2nm_node_local_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				     माप_प्रकार count)
अणु
	काष्ठा o2nm_node *node = to_o2nm_node(item);
	काष्ठा o2nm_cluster *cluster;
	अचिन्हित दीर्घ पंचांगp;
	अक्षर *p = (अक्षर *)page;
	sमाप_प्रकार ret;

	पंचांगp = simple_म_से_अदीर्घ(p, &p, 0);
	अगर (!p || (*p && (*p != '\n')))
		वापस -EINVAL;

	पंचांगp = !!पंचांगp; /* boolean of whether this node wants to be local */

	/* setting local turns on networking rx क्रम now so we require having
	 * set everything अन्यथा first */
	अगर (!test_bit(O2NM_NODE_ATTR_ADDRESS, &node->nd_set_attributes) ||
	    !test_bit(O2NM_NODE_ATTR_NUM, &node->nd_set_attributes) ||
	    !test_bit(O2NM_NODE_ATTR_PORT, &node->nd_set_attributes))
		वापस -EINVAL; /* XXX */

	o2nm_lock_subप्रणाली();
	cluster = to_o2nm_cluster_from_node(node);
	अगर (!cluster) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* the only failure हाल is trying to set a new local node
	 * when a dअगरferent one is alपढ़ोy set */
	अगर (पंचांगp && पंचांगp == cluster->cl_has_local &&
	    cluster->cl_local_node != node->nd_num) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* bring up the rx thपढ़ो अगर we're setting the new local node. */
	अगर (पंचांगp && !cluster->cl_has_local) अणु
		ret = o2net_start_listening(node);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (!पंचांगp && cluster->cl_has_local &&
	    cluster->cl_local_node == node->nd_num) अणु
		o2net_stop_listening(node);
		cluster->cl_local_node = O2NM_INVALID_NODE_NUM;
	पूर्ण

	node->nd_local = पंचांगp;
	अगर (node->nd_local) अणु
		cluster->cl_has_local = पंचांगp;
		cluster->cl_local_node = node->nd_num;
	पूर्ण

	ret = count;

out:
	o2nm_unlock_subप्रणाली();
	वापस ret;
पूर्ण

CONFIGFS_ATTR(o2nm_node_, num);
CONFIGFS_ATTR(o2nm_node_, ipv4_port);
CONFIGFS_ATTR(o2nm_node_, ipv4_address);
CONFIGFS_ATTR(o2nm_node_, local);

अटल काष्ठा configfs_attribute *o2nm_node_attrs[] = अणु
	&o2nm_node_attr_num,
	&o2nm_node_attr_ipv4_port,
	&o2nm_node_attr_ipv4_address,
	&o2nm_node_attr_local,
	शून्य,
पूर्ण;

अटल काष्ठा configfs_item_operations o2nm_node_item_ops = अणु
	.release		= o2nm_node_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type o2nm_node_type = अणु
	.ct_item_ops	= &o2nm_node_item_ops,
	.ct_attrs	= o2nm_node_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* node set */

काष्ठा o2nm_node_group अणु
	काष्ठा config_group ns_group;
	/* some stuff? */
पूर्ण;

#अगर 0
अटल काष्ठा o2nm_node_group *to_o2nm_node_group(काष्ठा config_group *group)
अणु
	वापस group ?
		container_of(group, काष्ठा o2nm_node_group, ns_group)
		: शून्य;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार o2nm_cluster_attr_ग_लिखो(स्थिर अक्षर *page, sमाप_प्रकार count,
                                       अचिन्हित पूर्णांक *val)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अक्षर *p = (अक्षर *)page;

	पंचांगp = simple_म_से_अदीर्घ(p, &p, 0);
	अगर (!p || (*p && (*p != '\n')))
		वापस -EINVAL;

	अगर (पंचांगp == 0)
		वापस -EINVAL;
	अगर (पंचांगp >= (u32)-1)
		वापस -दुस्फल;

	*val = पंचांगp;

	वापस count;
पूर्ण

अटल sमाप_प्रकार o2nm_cluster_idle_समयout_ms_show(काष्ठा config_item *item,
	अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_o2nm_cluster(item)->cl_idle_समयout_ms);
पूर्ण

अटल sमाप_प्रकार o2nm_cluster_idle_समयout_ms_store(काष्ठा config_item *item,
	स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा o2nm_cluster *cluster = to_o2nm_cluster(item);
	sमाप_प्रकार ret;
	अचिन्हित पूर्णांक val;

	ret =  o2nm_cluster_attr_ग_लिखो(page, count, &val);

	अगर (ret > 0) अणु
		अगर (cluster->cl_idle_समयout_ms != val
			&& o2net_num_connected_peers()) अणु
			mlog(ML_NOTICE,
			     "o2net: cannot change idle timeout after "
			     "the first peer has agreed to it."
			     "  %d connected peers\n",
			     o2net_num_connected_peers());
			ret = -EINVAL;
		पूर्ण अन्यथा अगर (val <= cluster->cl_keepalive_delay_ms) अणु
			mlog(ML_NOTICE, "o2net: idle timeout must be larger "
			     "than keepalive delay\n");
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			cluster->cl_idle_समयout_ms = val;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार o2nm_cluster_keepalive_delay_ms_show(
	काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n",
			to_o2nm_cluster(item)->cl_keepalive_delay_ms);
पूर्ण

अटल sमाप_प्रकार o2nm_cluster_keepalive_delay_ms_store(
	काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा o2nm_cluster *cluster = to_o2nm_cluster(item);
	sमाप_प्रकार ret;
	अचिन्हित पूर्णांक val;

	ret =  o2nm_cluster_attr_ग_लिखो(page, count, &val);

	अगर (ret > 0) अणु
		अगर (cluster->cl_keepalive_delay_ms != val
		    && o2net_num_connected_peers()) अणु
			mlog(ML_NOTICE,
			     "o2net: cannot change keepalive delay after"
			     " the first peer has agreed to it."
			     "  %d connected peers\n",
			     o2net_num_connected_peers());
			ret = -EINVAL;
		पूर्ण अन्यथा अगर (val >= cluster->cl_idle_समयout_ms) अणु
			mlog(ML_NOTICE, "o2net: keepalive delay must be "
			     "smaller than idle timeout\n");
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			cluster->cl_keepalive_delay_ms = val;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार o2nm_cluster_reconnect_delay_ms_show(
	काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n",
			to_o2nm_cluster(item)->cl_reconnect_delay_ms);
पूर्ण

अटल sमाप_प्रकार o2nm_cluster_reconnect_delay_ms_store(
	काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस o2nm_cluster_attr_ग_लिखो(page, count,
                               &to_o2nm_cluster(item)->cl_reconnect_delay_ms);
पूर्ण

अटल sमाप_प्रकार o2nm_cluster_fence_method_show(
	काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा o2nm_cluster *cluster = to_o2nm_cluster(item);
	sमाप_प्रकार ret = 0;

	अगर (cluster)
		ret = प्र_लिखो(page, "%s\n",
			      o2nm_fence_method_desc[cluster->cl_fence_method]);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार o2nm_cluster_fence_method_store(
	काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक i;

	अगर (page[count - 1] != '\n')
		जाओ bail;

	क्रम (i = 0; i < O2NM_FENCE_METHODS; ++i) अणु
		अगर (count != म_माप(o2nm_fence_method_desc[i]) + 1)
			जारी;
		अगर (strnहालcmp(page, o2nm_fence_method_desc[i], count - 1))
			जारी;
		अगर (to_o2nm_cluster(item)->cl_fence_method != i) अणु
			prपूर्णांकk(KERN_INFO "ocfs2: Changing fence method to %s\n",
			       o2nm_fence_method_desc[i]);
			to_o2nm_cluster(item)->cl_fence_method = i;
		पूर्ण
		वापस count;
	पूर्ण

bail:
	वापस -EINVAL;
पूर्ण

CONFIGFS_ATTR(o2nm_cluster_, idle_समयout_ms);
CONFIGFS_ATTR(o2nm_cluster_, keepalive_delay_ms);
CONFIGFS_ATTR(o2nm_cluster_, reconnect_delay_ms);
CONFIGFS_ATTR(o2nm_cluster_, fence_method);

अटल काष्ठा configfs_attribute *o2nm_cluster_attrs[] = अणु
	&o2nm_cluster_attr_idle_समयout_ms,
	&o2nm_cluster_attr_keepalive_delay_ms,
	&o2nm_cluster_attr_reconnect_delay_ms,
	&o2nm_cluster_attr_fence_method,
	शून्य,
पूर्ण;

अटल काष्ठा config_item *o2nm_node_group_make_item(काष्ठा config_group *group,
						     स्थिर अक्षर *name)
अणु
	काष्ठा o2nm_node *node = शून्य;

	अगर (म_माप(name) > O2NM_MAX_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	node = kzalloc(माप(काष्ठा o2nm_node), GFP_KERNEL);
	अगर (node == शून्य)
		वापस ERR_PTR(-ENOMEM);

	म_नकल(node->nd_name, name); /* use item.ci_namebuf instead? */
	config_item_init_type_name(&node->nd_item, name, &o2nm_node_type);
	spin_lock_init(&node->nd_lock);

	mlog(ML_CLUSTER, "o2nm: Registering node %s\n", name);

	वापस &node->nd_item;
पूर्ण

अटल व्योम o2nm_node_group_drop_item(काष्ठा config_group *group,
				      काष्ठा config_item *item)
अणु
	काष्ठा o2nm_node *node = to_o2nm_node(item);
	काष्ठा o2nm_cluster *cluster = to_o2nm_cluster(group->cg_item.ci_parent);

	अगर (cluster->cl_nodes[node->nd_num] == node) अणु
		o2net_disconnect_node(node);

		अगर (cluster->cl_has_local &&
		    (cluster->cl_local_node == node->nd_num)) अणु
			cluster->cl_has_local = 0;
			cluster->cl_local_node = O2NM_INVALID_NODE_NUM;
			o2net_stop_listening(node);
		पूर्ण
	पूर्ण

	/* XXX call पूर्णांकo net to stop this node from trading messages */

	ग_लिखो_lock(&cluster->cl_nodes_lock);

	/* XXX sloppy */
	अगर (node->nd_ipv4_address)
		rb_erase(&node->nd_ip_node, &cluster->cl_node_ip_tree);

	/* nd_num might be 0 अगर the node number hasn't been set.. */
	अगर (cluster->cl_nodes[node->nd_num] == node) अणु
		cluster->cl_nodes[node->nd_num] = शून्य;
		clear_bit(node->nd_num, cluster->cl_nodes_biपंचांगap);
	पूर्ण
	ग_लिखो_unlock(&cluster->cl_nodes_lock);

	mlog(ML_CLUSTER, "o2nm: Unregistered node %s\n",
	     config_item_name(&node->nd_item));

	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations o2nm_node_group_group_ops = अणु
	.make_item	= o2nm_node_group_make_item,
	.drop_item	= o2nm_node_group_drop_item,
पूर्ण;

अटल स्थिर काष्ठा config_item_type o2nm_node_group_type = अणु
	.ct_group_ops	= &o2nm_node_group_group_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* cluster */

अटल व्योम o2nm_cluster_release(काष्ठा config_item *item)
अणु
	काष्ठा o2nm_cluster *cluster = to_o2nm_cluster(item);

	kमुक्त(cluster);
पूर्ण

अटल काष्ठा configfs_item_operations o2nm_cluster_item_ops = अणु
	.release	= o2nm_cluster_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type o2nm_cluster_type = अणु
	.ct_item_ops	= &o2nm_cluster_item_ops,
	.ct_attrs	= o2nm_cluster_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* cluster set */

काष्ठा o2nm_cluster_group अणु
	काष्ठा configfs_subप्रणाली cs_subsys;
	/* some stuff? */
पूर्ण;

#अगर 0
अटल काष्ठा o2nm_cluster_group *to_o2nm_cluster_group(काष्ठा config_group *group)
अणु
	वापस group ?
		container_of(to_configfs_subप्रणाली(group), काष्ठा o2nm_cluster_group, cs_subsys)
	       : शून्य;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा config_group *o2nm_cluster_group_make_group(काष्ठा config_group *group,
							  स्थिर अक्षर *name)
अणु
	काष्ठा o2nm_cluster *cluster = शून्य;
	काष्ठा o2nm_node_group *ns = शून्य;
	काष्ठा config_group *o2hb_group = शून्य, *ret = शून्य;

	/* this runs under the parent dir's i_mutex; there can be only
	 * one caller in here at a समय */
	अगर (o2nm_single_cluster)
		वापस ERR_PTR(-ENOSPC);

	cluster = kzalloc(माप(काष्ठा o2nm_cluster), GFP_KERNEL);
	ns = kzalloc(माप(काष्ठा o2nm_node_group), GFP_KERNEL);
	o2hb_group = o2hb_alloc_hb_set();
	अगर (cluster == शून्य || ns == शून्य || o2hb_group == शून्य)
		जाओ out;

	config_group_init_type_name(&cluster->cl_group, name,
				    &o2nm_cluster_type);
	configfs_add_शेष_group(&ns->ns_group, &cluster->cl_group);

	config_group_init_type_name(&ns->ns_group, "node",
				    &o2nm_node_group_type);
	configfs_add_शेष_group(o2hb_group, &cluster->cl_group);

	rwlock_init(&cluster->cl_nodes_lock);
	cluster->cl_node_ip_tree = RB_ROOT;
	cluster->cl_reconnect_delay_ms = O2NET_RECONNECT_DELAY_MS_DEFAULT;
	cluster->cl_idle_समयout_ms    = O2NET_IDLE_TIMEOUT_MS_DEFAULT;
	cluster->cl_keepalive_delay_ms = O2NET_KEEPALIVE_DELAY_MS_DEFAULT;
	cluster->cl_fence_method       = O2NM_FENCE_RESET;

	ret = &cluster->cl_group;
	o2nm_single_cluster = cluster;

out:
	अगर (ret == शून्य) अणु
		kमुक्त(cluster);
		kमुक्त(ns);
		o2hb_मुक्त_hb_set(o2hb_group);
		ret = ERR_PTR(-ENOMEM);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम o2nm_cluster_group_drop_item(काष्ठा config_group *group, काष्ठा config_item *item)
अणु
	काष्ठा o2nm_cluster *cluster = to_o2nm_cluster(item);

	BUG_ON(o2nm_single_cluster != cluster);
	o2nm_single_cluster = शून्य;

	configfs_हटाओ_शेष_groups(&cluster->cl_group);
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations o2nm_cluster_group_group_ops = अणु
	.make_group	= o2nm_cluster_group_make_group,
	.drop_item	= o2nm_cluster_group_drop_item,
पूर्ण;

अटल स्थिर काष्ठा config_item_type o2nm_cluster_group_type = अणु
	.ct_group_ops	= &o2nm_cluster_group_group_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा o2nm_cluster_group o2nm_cluster_group = अणु
	.cs_subsys = अणु
		.su_group = अणु
			.cg_item = अणु
				.ci_namebuf = "cluster",
				.ci_type = &o2nm_cluster_group_type,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम o2nm_lock_subप्रणाली(व्योम)
अणु
	mutex_lock(&o2nm_cluster_group.cs_subsys.su_mutex);
पूर्ण

अटल अंतरभूत व्योम o2nm_unlock_subप्रणाली(व्योम)
अणु
	mutex_unlock(&o2nm_cluster_group.cs_subsys.su_mutex);
पूर्ण

पूर्णांक o2nm_depend_item(काष्ठा config_item *item)
अणु
	वापस configfs_depend_item(&o2nm_cluster_group.cs_subsys, item);
पूर्ण

व्योम o2nm_undepend_item(काष्ठा config_item *item)
अणु
	configfs_undepend_item(item);
पूर्ण

पूर्णांक o2nm_depend_this_node(व्योम)
अणु
	पूर्णांक ret = 0;
	काष्ठा o2nm_node *local_node;

	local_node = o2nm_get_node_by_num(o2nm_this_node());
	अगर (!local_node) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = o2nm_depend_item(&local_node->nd_item);
	o2nm_node_put(local_node);

out:
	वापस ret;
पूर्ण

व्योम o2nm_undepend_this_node(व्योम)
अणु
	काष्ठा o2nm_node *local_node;

	local_node = o2nm_get_node_by_num(o2nm_this_node());
	BUG_ON(!local_node);

	o2nm_undepend_item(&local_node->nd_item);
	o2nm_node_put(local_node);
पूर्ण


अटल व्योम __निकास निकास_o2nm(व्योम)
अणु
	/* XXX sync with hb callbacks and shut करोwn hb? */
	o2net_unरेजिस्टर_hb_callbacks();
	configfs_unरेजिस्टर_subप्रणाली(&o2nm_cluster_group.cs_subsys);
	o2cb_sys_shutकरोwn();

	o2net_निकास();
	o2hb_निकास();
पूर्ण

अटल पूर्णांक __init init_o2nm(व्योम)
अणु
	पूर्णांक ret = -1;

	o2hb_init();

	ret = o2net_init();
	अगर (ret)
		जाओ out_o2hb;

	ret = o2net_रेजिस्टर_hb_callbacks();
	अगर (ret)
		जाओ out_o2net;

	config_group_init(&o2nm_cluster_group.cs_subsys.su_group);
	mutex_init(&o2nm_cluster_group.cs_subsys.su_mutex);
	ret = configfs_रेजिस्टर_subप्रणाली(&o2nm_cluster_group.cs_subsys);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "nodemanager: Registration returned %d\n", ret);
		जाओ out_callbacks;
	पूर्ण

	ret = o2cb_sys_init();
	अगर (!ret)
		जाओ out;

	configfs_unरेजिस्टर_subप्रणाली(&o2nm_cluster_group.cs_subsys);
out_callbacks:
	o2net_unरेजिस्टर_hb_callbacks();
out_o2net:
	o2net_निकास();
out_o2hb:
	o2hb_निकास();
out:
	वापस ret;
पूर्ण

MODULE_AUTHOR("Oracle");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OCFS2 cluster management");

module_init(init_o2nm)
module_निकास(निकास_o2nm)
