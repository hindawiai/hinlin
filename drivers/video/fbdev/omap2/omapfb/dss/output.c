<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Texas Instruments Ltd
 * Author: Archit Taneja <archit@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"

अटल LIST_HEAD(output_list);
अटल DEFINE_MUTEX(output_lock);

पूर्णांक omapdss_output_set_device(काष्ठा omap_dss_device *out,
		काष्ठा omap_dss_device *dssdev)
अणु
	पूर्णांक r;

	mutex_lock(&output_lock);

	अगर (out->dst) अणु
		DSSERR("output already has device %s connected to it\n",
			out->dst->name);
		r = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (out->output_type != dssdev->type) अणु
		DSSERR("output type and display type don't match\n");
		r = -EINVAL;
		जाओ err;
	पूर्ण

	out->dst = dssdev;
	dssdev->src = out;

	mutex_unlock(&output_lock);

	वापस 0;
err:
	mutex_unlock(&output_lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL(omapdss_output_set_device);

पूर्णांक omapdss_output_unset_device(काष्ठा omap_dss_device *out)
अणु
	पूर्णांक r;

	mutex_lock(&output_lock);

	अगर (!out->dst) अणु
		DSSERR("output doesn't have a device connected to it\n");
		r = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (out->dst->state != OMAP_DSS_DISPLAY_DISABLED) अणु
		DSSERR("device %s is not disabled, cannot unset device\n",
				out->dst->name);
		r = -EINVAL;
		जाओ err;
	पूर्ण

	out->dst->src = शून्य;
	out->dst = शून्य;

	mutex_unlock(&output_lock);

	वापस 0;
err:
	mutex_unlock(&output_lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL(omapdss_output_unset_device);

पूर्णांक omapdss_रेजिस्टर_output(काष्ठा omap_dss_device *out)
अणु
	list_add_tail(&out->list, &output_list);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(omapdss_रेजिस्टर_output);

व्योम omapdss_unरेजिस्टर_output(काष्ठा omap_dss_device *out)
अणु
	list_del(&out->list);
पूर्ण
EXPORT_SYMBOL(omapdss_unरेजिस्टर_output);

काष्ठा omap_dss_device *omap_dss_get_output(क्रमागत omap_dss_output_id id)
अणु
	काष्ठा omap_dss_device *out;

	list_क्रम_each_entry(out, &output_list, list) अणु
		अगर (out->id == id)
			वापस out;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(omap_dss_get_output);

काष्ठा omap_dss_device *omap_dss_find_output(स्थिर अक्षर *name)
अणु
	काष्ठा omap_dss_device *out;

	list_क्रम_each_entry(out, &output_list, list) अणु
		अगर (म_भेद(out->name, name) == 0)
			वापस omap_dss_get_device(out);
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(omap_dss_find_output);

काष्ठा omap_dss_device *omap_dss_find_output_by_port_node(काष्ठा device_node *port)
अणु
	काष्ठा device_node *src_node;
	काष्ठा omap_dss_device *out;
	u32 reg;

	src_node = dss_of_port_get_parent_device(port);
	अगर (!src_node)
		वापस शून्य;

	reg = dss_of_port_get_port_number(port);

	list_क्रम_each_entry(out, &output_list, list) अणु
		अगर (out->dev->of_node == src_node && out->port_num == reg) अणु
			of_node_put(src_node);
			वापस omap_dss_get_device(out);
		पूर्ण
	पूर्ण

	of_node_put(src_node);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(omap_dss_find_output_by_port_node);

काष्ठा omap_dss_device *omapdss_find_output_from_display(काष्ठा omap_dss_device *dssdev)
अणु
	जबतक (dssdev->src)
		dssdev = dssdev->src;

	अगर (dssdev->id != 0)
		वापस omap_dss_get_device(dssdev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(omapdss_find_output_from_display);

काष्ठा omap_overlay_manager *omapdss_find_mgr_from_display(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_dss_device *out;
	काष्ठा omap_overlay_manager *mgr;

	out = omapdss_find_output_from_display(dssdev);

	अगर (out == शून्य)
		वापस शून्य;

	mgr = out->manager;

	omap_dss_put_device(out);

	वापस mgr;
पूर्ण
EXPORT_SYMBOL(omapdss_find_mgr_from_display);

अटल स्थिर काष्ठा dss_mgr_ops *dss_mgr_ops;

पूर्णांक dss_install_mgr_ops(स्थिर काष्ठा dss_mgr_ops *mgr_ops)
अणु
	अगर (dss_mgr_ops)
		वापस -EBUSY;

	dss_mgr_ops = mgr_ops;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dss_install_mgr_ops);

व्योम dss_uninstall_mgr_ops(व्योम)
अणु
	dss_mgr_ops = शून्य;
पूर्ण
EXPORT_SYMBOL(dss_uninstall_mgr_ops);

पूर्णांक dss_mgr_connect(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *dst)
अणु
	वापस dss_mgr_ops->connect(mgr, dst);
पूर्ण
EXPORT_SYMBOL(dss_mgr_connect);

व्योम dss_mgr_disconnect(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *dst)
अणु
	dss_mgr_ops->disconnect(mgr, dst);
पूर्ण
EXPORT_SYMBOL(dss_mgr_disconnect);

व्योम dss_mgr_set_timings(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा omap_video_timings *timings)
अणु
	dss_mgr_ops->set_timings(mgr, timings);
पूर्ण
EXPORT_SYMBOL(dss_mgr_set_timings);

व्योम dss_mgr_set_lcd_config(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा dss_lcd_mgr_config *config)
अणु
	dss_mgr_ops->set_lcd_config(mgr, config);
पूर्ण
EXPORT_SYMBOL(dss_mgr_set_lcd_config);

पूर्णांक dss_mgr_enable(काष्ठा omap_overlay_manager *mgr)
अणु
	वापस dss_mgr_ops->enable(mgr);
पूर्ण
EXPORT_SYMBOL(dss_mgr_enable);

व्योम dss_mgr_disable(काष्ठा omap_overlay_manager *mgr)
अणु
	dss_mgr_ops->disable(mgr);
पूर्ण
EXPORT_SYMBOL(dss_mgr_disable);

व्योम dss_mgr_start_update(काष्ठा omap_overlay_manager *mgr)
अणु
	dss_mgr_ops->start_update(mgr);
पूर्ण
EXPORT_SYMBOL(dss_mgr_start_update);

पूर्णांक dss_mgr_रेजिस्टर_frameकरोne_handler(काष्ठा omap_overlay_manager *mgr,
		व्योम (*handler)(व्योम *), व्योम *data)
अणु
	वापस dss_mgr_ops->रेजिस्टर_frameकरोne_handler(mgr, handler, data);
पूर्ण
EXPORT_SYMBOL(dss_mgr_रेजिस्टर_frameकरोne_handler);

व्योम dss_mgr_unरेजिस्टर_frameकरोne_handler(काष्ठा omap_overlay_manager *mgr,
		व्योम (*handler)(व्योम *), व्योम *data)
अणु
	dss_mgr_ops->unरेजिस्टर_frameकरोne_handler(mgr, handler, data);
पूर्ण
EXPORT_SYMBOL(dss_mgr_unरेजिस्टर_frameकरोne_handler);
