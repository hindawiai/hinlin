<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/seq_file.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"

काष्ठा device_node *
omapdss_of_get_next_port(स्थिर काष्ठा device_node *parent,
			 काष्ठा device_node *prev)
अणु
	काष्ठा device_node *port = शून्य;

	अगर (!parent)
		वापस शून्य;

	अगर (!prev) अणु
		काष्ठा device_node *ports;
		/*
		 * It's the first call, we have to find a port subnode
		 * within this node or within an optional 'ports' node.
		 */
		ports = of_get_child_by_name(parent, "ports");
		अगर (ports)
			parent = ports;

		port = of_get_child_by_name(parent, "port");

		/* release the 'ports' node */
		of_node_put(ports);
	पूर्ण अन्यथा अणु
		काष्ठा device_node *ports;

		ports = of_get_parent(prev);
		अगर (!ports)
			वापस शून्य;

		करो अणु
			port = of_get_next_child(ports, prev);
			अगर (!port) अणु
				of_node_put(ports);
				वापस शून्य;
			पूर्ण
			prev = port;
		पूर्ण जबतक (!of_node_name_eq(port, "port"));

		of_node_put(ports);
	पूर्ण

	वापस port;
पूर्ण
EXPORT_SYMBOL_GPL(omapdss_of_get_next_port);

काष्ठा device_node *
omapdss_of_get_next_endpoपूर्णांक(स्थिर काष्ठा device_node *parent,
			     काष्ठा device_node *prev)
अणु
	काष्ठा device_node *ep = शून्य;

	अगर (!parent)
		वापस शून्य;

	करो अणु
		ep = of_get_next_child(parent, prev);
		अगर (!ep)
			वापस शून्य;
		prev = ep;
	पूर्ण जबतक (!of_node_name_eq(ep, "endpoint"));

	वापस ep;
पूर्ण
EXPORT_SYMBOL_GPL(omapdss_of_get_next_endpoपूर्णांक);

काष्ठा device_node *dss_of_port_get_parent_device(काष्ठा device_node *port)
अणु
	काष्ठा device_node *np;
	पूर्णांक i;

	अगर (!port)
		वापस शून्य;

	np = of_get_parent(port);

	क्रम (i = 0; i < 2 && np; ++i) अणु
		काष्ठा property *prop;

		prop = of_find_property(np, "compatible", शून्य);

		अगर (prop)
			वापस np;

		np = of_get_next_parent(np);
	पूर्ण

	वापस शून्य;
पूर्ण

u32 dss_of_port_get_port_number(काष्ठा device_node *port)
अणु
	पूर्णांक r;
	u32 reg;

	r = of_property_पढ़ो_u32(port, "reg", &reg);
	अगर (r)
		reg = 0;

	वापस reg;
पूर्ण

अटल काष्ठा device_node *omapdss_of_get_remote_port(स्थिर काष्ठा device_node *node)
अणु
	काष्ठा device_node *np;

	np = of_graph_get_remote_endpoपूर्णांक(node);
	अगर (!np)
		वापस शून्य;

	np = of_get_next_parent(np);

	वापस np;
पूर्ण

काष्ठा device_node *
omapdss_of_get_first_endpoपूर्णांक(स्थिर काष्ठा device_node *parent)
अणु
	काष्ठा device_node *port, *ep;

	port = omapdss_of_get_next_port(parent, शून्य);

	अगर (!port)
		वापस शून्य;

	ep = omapdss_of_get_next_endpoपूर्णांक(port, शून्य);

	of_node_put(port);

	वापस ep;
पूर्ण
EXPORT_SYMBOL_GPL(omapdss_of_get_first_endpoपूर्णांक);

काष्ठा omap_dss_device *
omapdss_of_find_source_क्रम_first_ep(काष्ठा device_node *node)
अणु
	काष्ठा device_node *ep;
	काष्ठा device_node *src_port;
	काष्ठा omap_dss_device *src;

	ep = omapdss_of_get_first_endpoपूर्णांक(node);
	अगर (!ep)
		वापस ERR_PTR(-EINVAL);

	src_port = omapdss_of_get_remote_port(ep);
	अगर (!src_port) अणु
		of_node_put(ep);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	of_node_put(ep);

	src = omap_dss_find_output_by_port_node(src_port);

	of_node_put(src_port);

	वापस src ? src : ERR_PTR(-EPROBE_DEFER);
पूर्ण
EXPORT_SYMBOL_GPL(omapdss_of_find_source_क्रम_first_ep);
