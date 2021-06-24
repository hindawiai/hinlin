<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP Display Subप्रणाली Base
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - https://www.ti.com/
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "dss.h"
#समावेश "omapdss.h"

काष्ठा dispc_device *dispc_get_dispc(काष्ठा dss_device *dss)
अणु
	वापस dss->dispc;
पूर्ण

/* -----------------------------------------------------------------------------
 * OMAP DSS Devices Handling
 */

अटल LIST_HEAD(omapdss_devices_list);
अटल DEFINE_MUTEX(omapdss_devices_lock);

व्योम omapdss_device_रेजिस्टर(काष्ठा omap_dss_device *dssdev)
अणु
	mutex_lock(&omapdss_devices_lock);
	list_add_tail(&dssdev->list, &omapdss_devices_list);
	mutex_unlock(&omapdss_devices_lock);
पूर्ण

व्योम omapdss_device_unरेजिस्टर(काष्ठा omap_dss_device *dssdev)
अणु
	mutex_lock(&omapdss_devices_lock);
	list_del(&dssdev->list);
	mutex_unlock(&omapdss_devices_lock);
पूर्ण

अटल bool omapdss_device_is_रेजिस्टरed(काष्ठा device_node *node)
अणु
	काष्ठा omap_dss_device *dssdev;
	bool found = false;

	mutex_lock(&omapdss_devices_lock);

	list_क्रम_each_entry(dssdev, &omapdss_devices_list, list) अणु
		अगर (dssdev->dev->of_node == node) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&omapdss_devices_lock);
	वापस found;
पूर्ण

काष्ठा omap_dss_device *omapdss_device_get(काष्ठा omap_dss_device *dssdev)
अणु
	अगर (get_device(dssdev->dev) == शून्य)
		वापस शून्य;

	वापस dssdev;
पूर्ण

व्योम omapdss_device_put(काष्ठा omap_dss_device *dssdev)
अणु
	put_device(dssdev->dev);
पूर्ण

काष्ठा omap_dss_device *omapdss_find_device_by_node(काष्ठा device_node *node)
अणु
	काष्ठा omap_dss_device *dssdev;

	list_क्रम_each_entry(dssdev, &omapdss_devices_list, list) अणु
		अगर (dssdev->dev->of_node == node)
			वापस omapdss_device_get(dssdev);
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Search क्रम the next output device starting at @from. Release the reference to
 * the @from device, and acquire a reference to the वापसed device अगर found.
 */
काष्ठा omap_dss_device *omapdss_device_next_output(काष्ठा omap_dss_device *from)
अणु
	काष्ठा omap_dss_device *dssdev;
	काष्ठा list_head *list;

	mutex_lock(&omapdss_devices_lock);

	अगर (list_empty(&omapdss_devices_list)) अणु
		dssdev = शून्य;
		जाओ करोne;
	पूर्ण

	/*
	 * Start from the from entry अगर given or from omapdss_devices_list
	 * otherwise.
	 */
	list = from ? &from->list : &omapdss_devices_list;

	list_क्रम_each_entry(dssdev, list, list) अणु
		/*
		 * Stop अगर we reach the omapdss_devices_list, that's the end of
		 * the list.
		 */
		अगर (&dssdev->list == &omapdss_devices_list) अणु
			dssdev = शून्य;
			जाओ करोne;
		पूर्ण

		अगर (dssdev->id && dssdev->bridge)
			जाओ करोne;
	पूर्ण

	dssdev = शून्य;

करोne:
	अगर (from)
		omapdss_device_put(from);
	अगर (dssdev)
		omapdss_device_get(dssdev);

	mutex_unlock(&omapdss_devices_lock);
	वापस dssdev;
पूर्ण

अटल bool omapdss_device_is_connected(काष्ठा omap_dss_device *dssdev)
अणु
	वापस dssdev->dss;
पूर्ण

पूर्णांक omapdss_device_connect(काष्ठा dss_device *dss,
			   काष्ठा omap_dss_device *src,
			   काष्ठा omap_dss_device *dst)
अणु
	dev_dbg(&dss->pdev->dev, "connect(%s, %s)\n",
		src ? dev_name(src->dev) : "NULL",
		dst ? dev_name(dst->dev) : "NULL");

	अगर (!dst) अणु
		/*
		 * The destination is शून्य when the source is connected to a
		 * bridge instead of a DSS device. Stop here, we will attach
		 * the bridge later when we will have a DRM encoder.
		 */
		वापस src && src->bridge ? 0 : -EINVAL;
	पूर्ण

	अगर (omapdss_device_is_connected(dst))
		वापस -EBUSY;

	dst->dss = dss;

	वापस 0;
पूर्ण

व्योम omapdss_device_disconnect(काष्ठा omap_dss_device *src,
			       काष्ठा omap_dss_device *dst)
अणु
	काष्ठा dss_device *dss = src ? src->dss : dst->dss;

	dev_dbg(&dss->pdev->dev, "disconnect(%s, %s)\n",
		src ? dev_name(src->dev) : "NULL",
		dst ? dev_name(dst->dev) : "NULL");

	अगर (!dst) अणु
		WARN_ON(!src->bridge);
		वापस;
	पूर्ण

	अगर (!dst->id && !omapdss_device_is_connected(dst)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	dst->dss = शून्य;
पूर्ण

/* -----------------------------------------------------------------------------
 * Components Handling
 */

अटल काष्ठा list_head omapdss_comp_list;

काष्ठा omapdss_comp_node अणु
	काष्ठा list_head list;
	काष्ठा device_node *node;
	bool dss_core_component;
	स्थिर अक्षर *compat;
पूर्ण;

अटल bool omapdss_list_contains(स्थिर काष्ठा device_node *node)
अणु
	काष्ठा omapdss_comp_node *comp;

	list_क्रम_each_entry(comp, &omapdss_comp_list, list) अणु
		अगर (comp->node == node)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम omapdss_walk_device(काष्ठा device *dev, काष्ठा device_node *node,
				bool dss_core)
अणु
	काष्ठा omapdss_comp_node *comp;
	काष्ठा device_node *n;
	स्थिर अक्षर *compat;
	पूर्णांक ret;

	ret = of_property_पढ़ो_string(node, "compatible", &compat);
	अगर (ret < 0)
		वापस;

	comp = devm_kzalloc(dev, माप(*comp), GFP_KERNEL);
	अगर (comp) अणु
		comp->node = node;
		comp->dss_core_component = dss_core;
		comp->compat = compat;
		list_add(&comp->list, &omapdss_comp_list);
	पूर्ण

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
		काष्ठा device_node *pn = of_graph_get_remote_port_parent(n);

		अगर (!pn)
			जारी;

		अगर (!of_device_is_available(pn) || omapdss_list_contains(pn)) अणु
			of_node_put(pn);
			जारी;
		पूर्ण

		omapdss_walk_device(dev, pn, false);
	पूर्ण
पूर्ण

व्योम omapdss_gather_components(काष्ठा device *dev)
अणु
	काष्ठा device_node *child;

	INIT_LIST_HEAD(&omapdss_comp_list);

	omapdss_walk_device(dev, dev->of_node, true);

	क्रम_each_available_child_of_node(dev->of_node, child)
		omapdss_walk_device(dev, child, true);
पूर्ण

अटल bool omapdss_component_is_loaded(काष्ठा omapdss_comp_node *comp)
अणु
	अगर (comp->dss_core_component)
		वापस true;
	अगर (!strstarts(comp->compat, "omapdss,"))
		वापस true;
	अगर (omapdss_device_is_रेजिस्टरed(comp->node))
		वापस true;

	वापस false;
पूर्ण

bool omapdss_stack_is_पढ़ोy(व्योम)
अणु
	काष्ठा omapdss_comp_node *comp;

	list_क्रम_each_entry(comp, &omapdss_comp_list, list) अणु
		अगर (!omapdss_component_is_loaded(comp))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
