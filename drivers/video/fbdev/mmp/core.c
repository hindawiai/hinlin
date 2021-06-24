<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/video/mmp/common.c
 * This driver is a common framework क्रम Marvell Display Controller
 *
 * Copyright (C) 2012 Marvell Technology Group Ltd.
 * Authors: Zhou Zhu <zzhu3@marvell.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <video/mmp_disp.h>

अटल काष्ठा mmp_overlay *path_get_overlay(काष्ठा mmp_path *path,
		पूर्णांक overlay_id)
अणु
	अगर (path && overlay_id < path->overlay_num)
		वापस &path->overlays[overlay_id];
	वापस शून्य;
पूर्ण

अटल पूर्णांक path_check_status(काष्ठा mmp_path *path)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < path->overlay_num; i++)
		अगर (path->overlays[i].status)
			वापस 1;

	वापस 0;
पूर्ण

/*
 * Get modelist ग_लिखो poपूर्णांकer of modelist.
 * It also वापसs modelist number
 * this function fetches modelist from phy/panel:
 *   क्रम HDMI/parallel or dsi to hdmi हालs, get from phy
 *   or get from panel
 */
अटल पूर्णांक path_get_modelist(काष्ठा mmp_path *path,
		काष्ठा mmp_mode **modelist)
अणु
	BUG_ON(!path || !modelist);

	अगर (path->panel && path->panel->get_modelist)
		वापस path->panel->get_modelist(path->panel, modelist);

	वापस 0;
पूर्ण

/*
 * panel list is used to pair panel/path when path/panel रेजिस्टरed
 * path list is used क्रम both buffer driver and platdriver
 * plat driver करो path रेजिस्टर/unरेजिस्टर
 * panel driver करो panel रेजिस्टर/unरेजिस्टर
 * buffer driver get रेजिस्टरed path
 */
अटल LIST_HEAD(panel_list);
अटल LIST_HEAD(path_list);
अटल DEFINE_MUTEX(disp_lock);

/*
 * mmp_रेजिस्टर_panel - रेजिस्टर panel to panel_list and connect to path
 * @p: panel to be रेजिस्टरed
 *
 * this function provides पूर्णांकerface क्रम panel drivers to रेजिस्टर panel
 * to panel_list and connect to path which matchs panel->plat_path_name.
 * no error वापसs when no matching path is found as path रेजिस्टर after
 * panel रेजिस्टर is permitted.
 */
व्योम mmp_रेजिस्टर_panel(काष्ठा mmp_panel *panel)
अणु
	काष्ठा mmp_path *path;

	mutex_lock(&disp_lock);

	/* add */
	list_add_tail(&panel->node, &panel_list);

	/* try to रेजिस्टर to path */
	list_क्रम_each_entry(path, &path_list, node) अणु
		अगर (!म_भेद(panel->plat_path_name, path->name)) अणु
			dev_info(panel->dev, "connect to path %s\n",
				path->name);
			path->panel = panel;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&disp_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mmp_रेजिस्टर_panel);

/*
 * mmp_unरेजिस्टर_panel - unरेजिस्टर panel from panel_list and disconnect
 * @p: panel to be unरेजिस्टरed
 *
 * this function provides पूर्णांकerface क्रम panel drivers to unरेजिस्टर panel
 * from panel_list and disconnect from path.
 */
व्योम mmp_unरेजिस्टर_panel(काष्ठा mmp_panel *panel)
अणु
	काष्ठा mmp_path *path;

	mutex_lock(&disp_lock);
	list_del(&panel->node);

	list_क्रम_each_entry(path, &path_list, node) अणु
		अगर (path->panel && path->panel == panel) अणु
			dev_info(panel->dev, "disconnect from path %s\n",
				path->name);
			path->panel = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&disp_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mmp_unरेजिस्टर_panel);

/*
 * mmp_get_path - get path by name
 * @p: path name
 *
 * this function checks path name in path_list and वापस matching path
 * वापस शून्य अगर no matching path
 */
काष्ठा mmp_path *mmp_get_path(स्थिर अक्षर *name)
अणु
	काष्ठा mmp_path *path;
	पूर्णांक found = 0;

	mutex_lock(&disp_lock);
	list_क्रम_each_entry(path, &path_list, node) अणु
		अगर (!म_भेद(name, path->name)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&disp_lock);

	वापस found ? path : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(mmp_get_path);

/*
 * mmp_रेजिस्टर_path - init and रेजिस्टर path by path_info
 * @p: path info provided by display controller
 *
 * this function init by path info and रेजिस्टर path to path_list
 * this function also try to connect path with panel by name
 */
काष्ठा mmp_path *mmp_रेजिस्टर_path(काष्ठा mmp_path_info *info)
अणु
	पूर्णांक i;
	काष्ठा mmp_path *path = शून्य;
	काष्ठा mmp_panel *panel;

	path = kzalloc(काष्ठा_size(path, overlays, info->overlay_num),
		       GFP_KERNEL);
	अगर (!path)
		वापस शून्य;

	/* path set */
	mutex_init(&path->access_ok);
	path->dev = info->dev;
	path->id = info->id;
	path->name = info->name;
	path->output_type = info->output_type;
	path->overlay_num = info->overlay_num;
	path->plat_data = info->plat_data;
	path->ops.set_mode = info->set_mode;

	mutex_lock(&disp_lock);
	/* get panel */
	list_क्रम_each_entry(panel, &panel_list, node) अणु
		अगर (!म_भेद(info->name, panel->plat_path_name)) अणु
			dev_info(path->dev, "get panel %s\n", panel->name);
			path->panel = panel;
			अवरोध;
		पूर्ण
	पूर्ण

	dev_info(path->dev, "register %s, overlay_num %d\n",
			path->name, path->overlay_num);

	/* शेष op set: अगर alपढ़ोy set by driver, never cover it */
	अगर (!path->ops.check_status)
		path->ops.check_status = path_check_status;
	अगर (!path->ops.get_overlay)
		path->ops.get_overlay = path_get_overlay;
	अगर (!path->ops.get_modelist)
		path->ops.get_modelist = path_get_modelist;

	/* step3: init overlays */
	क्रम (i = 0; i < path->overlay_num; i++) अणु
		path->overlays[i].path = path;
		path->overlays[i].id = i;
		mutex_init(&path->overlays[i].access_ok);
		path->overlays[i].ops = info->overlay_ops;
	पूर्ण

	/* add to pathlist */
	list_add_tail(&path->node, &path_list);

	mutex_unlock(&disp_lock);
	वापस path;
पूर्ण
EXPORT_SYMBOL_GPL(mmp_रेजिस्टर_path);

/*
 * mmp_unरेजिस्टर_path - unरेजिस्टर and destroy path
 * @p: path to be destroyed.
 *
 * this function रेजिस्टरs path and destroys it.
 */
व्योम mmp_unरेजिस्टर_path(काष्ठा mmp_path *path)
अणु
	पूर्णांक i;

	अगर (!path)
		वापस;

	mutex_lock(&disp_lock);
	/* del from pathlist */
	list_del(&path->node);

	/* deinit overlays */
	क्रम (i = 0; i < path->overlay_num; i++)
		mutex_destroy(&path->overlays[i].access_ok);

	mutex_destroy(&path->access_ok);

	kमुक्त(path);
	mutex_unlock(&disp_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mmp_unरेजिस्टर_path);

MODULE_AUTHOR("Zhou Zhu <zzhu3@marvell.com>");
MODULE_DESCRIPTION("Marvell MMP display framework");
MODULE_LICENSE("GPL");
