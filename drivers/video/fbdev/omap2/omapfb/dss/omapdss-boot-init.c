<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

/*
 * As omapdss panel drivers are omapdss specअगरic, but we want to define the
 * DT-data in generic manner, we convert the compatible strings of the panel and
 * encoder nodes from "panel-foo" to "omapdss,panel-foo". This way we can have
 * both correct DT data and omapdss specअगरic drivers.
 *
 * When we get generic panel drivers to the kernel, this file will be हटाओd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>

अटल काष्ठा list_head dss_conv_list __initdata;

अटल स्थिर अक्षर prefix[] __initस्थिर = "omapdss,";

काष्ठा dss_conv_node अणु
	काष्ठा list_head list;
	काष्ठा device_node *node;
	bool root;
पूर्ण;

अटल पूर्णांक __init omapdss_count_strings(स्थिर काष्ठा property *prop)
अणु
	स्थिर अक्षर *p = prop->value;
	पूर्णांक l = 0, total = 0;
	पूर्णांक i;

	क्रम (i = 0; total < prop->length; total += l, p += l, i++)
		l = म_माप(p) + 1;

	वापस i;
पूर्ण

अटल व्योम __init omapdss_update_prop(काष्ठा device_node *node, अक्षर *compat,
	पूर्णांक len)
अणु
	काष्ठा property *prop;

	prop = kzalloc(माप(*prop), GFP_KERNEL);
	अगर (!prop)
		वापस;

	prop->name = "compatible";
	prop->value = compat;
	prop->length = len;

	of_update_property(node, prop);
पूर्ण

अटल व्योम __init omapdss_prefix_म_नकल(अक्षर *dst, पूर्णांक dst_len,
	स्थिर अक्षर *src, पूर्णांक src_len)
अणु
	माप_प्रकार total = 0;

	जबतक (total < src_len) अणु
		माप_प्रकार l = म_माप(src) + 1;

		म_नकल(dst, prefix);
		dst += म_माप(prefix);

		म_नकल(dst, src);
		dst += l;

		src += l;
		total += l;
	पूर्ण
पूर्ण

/* prepend compatible property strings with "omapdss," */
अटल व्योम __init omapdss_omapअगरy_node(काष्ठा device_node *node)
अणु
	काष्ठा property *prop;
	अक्षर *new_compat;
	पूर्णांक num_strs;
	पूर्णांक new_len;

	prop = of_find_property(node, "compatible", शून्य);

	अगर (!prop || !prop->value)
		वापस;

	अगर (strnlen(prop->value, prop->length) >= prop->length)
		वापस;

	/* is it alपढ़ोy prefixed? */
	अगर (म_भेदन(prefix, prop->value, म_माप(prefix)) == 0)
		वापस;

	num_strs = omapdss_count_strings(prop);

	new_len = prop->length + म_माप(prefix) * num_strs;
	new_compat = kदो_स्मृति(new_len, GFP_KERNEL);
	अगर (!new_compat)
		वापस;

	omapdss_prefix_म_नकल(new_compat, new_len, prop->value, prop->length);

	omapdss_update_prop(node, new_compat, new_len);
पूर्ण

अटल व्योम __init omapdss_add_to_list(काष्ठा device_node *node, bool root)
अणु
	काष्ठा dss_conv_node *n = kदो_स्मृति(माप(काष्ठा dss_conv_node),
		GFP_KERNEL);
	अगर (n) अणु
		n->node = node;
		n->root = root;
		list_add(&n->list, &dss_conv_list);
	पूर्ण
पूर्ण

अटल bool __init omapdss_list_contains(स्थिर काष्ठा device_node *node)
अणु
	काष्ठा dss_conv_node *n;

	list_क्रम_each_entry(n, &dss_conv_list, list) अणु
		अगर (n->node == node)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम __init omapdss_walk_device(काष्ठा device_node *node, bool root)
अणु
	काष्ठा device_node *n;

	omapdss_add_to_list(node, root);

	/*
	 * of_graph_get_remote_port_parent() prपूर्णांकs an error अगर there is no
	 * port/ports node. To aव्योम that, check first that there's the node.
	 */
	n = of_get_child_by_name(node, "ports");
	अगर (!n)
		n = of_get_child_by_name(node, "port");
	अगर (!n)
		वापस;

	of_node_put(n);

	n = शून्य;
	जबतक ((n = of_graph_get_next_endpoपूर्णांक(node, n)) != शून्य) अणु
		काष्ठा device_node *pn;

		pn = of_graph_get_remote_port_parent(n);

		अगर (!pn)
			जारी;

		अगर (!of_device_is_available(pn) || omapdss_list_contains(pn)) अणु
			of_node_put(pn);
			जारी;
		पूर्ण

		omapdss_walk_device(pn, false);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id omapdss_of_match[] __initस्थिर = अणु
	अणु .compatible = "ti,omap2-dss", पूर्ण,
	अणु .compatible = "ti,omap3-dss", पूर्ण,
	अणु .compatible = "ti,omap4-dss", पूर्ण,
	अणु .compatible = "ti,omap5-dss", पूर्ण,
	अणु .compatible = "ti,dra7-dss", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init omapdss_boot_init(व्योम)
अणु
	काष्ठा device_node *dss, *child;

	INIT_LIST_HEAD(&dss_conv_list);

	dss = of_find_matching_node(शून्य, omapdss_of_match);

	अगर (dss == शून्य || !of_device_is_available(dss)) अणु
		of_node_put(dss);
		वापस 0;
	पूर्ण

	omapdss_walk_device(dss, true);

	क्रम_each_available_child_of_node(dss, child) अणु
		अगर (!of_find_property(child, "compatible", शून्य))
			जारी;

		omapdss_walk_device(child, true);
	पूर्ण

	जबतक (!list_empty(&dss_conv_list)) अणु
		काष्ठा dss_conv_node *n;

		n = list_first_entry(&dss_conv_list, काष्ठा dss_conv_node,
			list);

		अगर (!n->root)
			omapdss_omapअगरy_node(n->node);

		list_del(&n->list);
		of_node_put(n->node);
		kमुक्त(n);
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(omapdss_boot_init);
