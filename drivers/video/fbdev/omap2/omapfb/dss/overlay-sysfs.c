<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "OVERLAY"

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

अटल sमाप_प्रकार overlay_name_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ovl->name);
पूर्ण

अटल sमाप_प्रकार overlay_manager_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			ovl->manager ? ovl->manager->name : "<none>");
पूर्ण

अटल sमाप_प्रकार overlay_manager_store(काष्ठा omap_overlay *ovl, स्थिर अक्षर *buf,
		माप_प्रकार size)
अणु
	पूर्णांक i, r;
	काष्ठा omap_overlay_manager *mgr = शून्य;
	काष्ठा omap_overlay_manager *old_mgr;
	पूर्णांक len = size;

	अगर (buf[size-1] == '\n')
		--len;

	अगर (len > 0) अणु
		क्रम (i = 0; i < omap_dss_get_num_overlay_managers(); ++i) अणु
			mgr = omap_dss_get_overlay_manager(i);

			अगर (sysfs_streq(buf, mgr->name))
				अवरोध;

			mgr = शून्य;
		पूर्ण
	पूर्ण

	अगर (len > 0 && mgr == शून्य)
		वापस -EINVAL;

	अगर (mgr)
		DSSDBG("manager %s found\n", mgr->name);

	अगर (mgr == ovl->manager)
		वापस size;

	old_mgr = ovl->manager;

	r = dispc_runसमय_get();
	अगर (r)
		वापस r;

	/* detach old manager */
	अगर (old_mgr) अणु
		r = ovl->unset_manager(ovl);
		अगर (r) अणु
			DSSERR("detach failed\n");
			जाओ err;
		पूर्ण

		r = old_mgr->apply(old_mgr);
		अगर (r)
			जाओ err;
	पूर्ण

	अगर (mgr) अणु
		r = ovl->set_manager(ovl, mgr);
		अगर (r) अणु
			DSSERR("Failed to attach overlay\n");
			जाओ err;
		पूर्ण

		r = mgr->apply(mgr);
		अगर (r)
			जाओ err;
	पूर्ण

	dispc_runसमय_put();

	वापस size;

err:
	dispc_runसमय_put();
	वापस r;
पूर्ण

अटल sमाप_प्रकार overlay_input_size_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d,%d\n",
			info.width, info.height);
पूर्ण

अटल sमाप_प्रकार overlay_screen_width_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", info.screen_width);
पूर्ण

अटल sमाप_प्रकार overlay_position_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d,%d\n",
			info.pos_x, info.pos_y);
पूर्ण

अटल sमाप_प्रकार overlay_position_store(काष्ठा omap_overlay *ovl,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r;
	अक्षर *last;
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	info.pos_x = simple_म_से_अदीर्घ(buf, &last, 10);
	++last;
	अगर (last - buf >= size)
		वापस -EINVAL;

	info.pos_y = simple_म_से_अदीर्घ(last, &last, 10);

	r = ovl->set_overlay_info(ovl, &info);
	अगर (r)
		वापस r;

	अगर (ovl->manager) अणु
		r = ovl->manager->apply(ovl->manager);
		अगर (r)
			वापस r;
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार overlay_output_size_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d,%d\n",
			info.out_width, info.out_height);
पूर्ण

अटल sमाप_प्रकार overlay_output_size_store(काष्ठा omap_overlay *ovl,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r;
	अक्षर *last;
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	info.out_width = simple_म_से_अदीर्घ(buf, &last, 10);
	++last;
	अगर (last - buf >= size)
		वापस -EINVAL;

	info.out_height = simple_म_से_अदीर्घ(last, &last, 10);

	r = ovl->set_overlay_info(ovl, &info);
	अगर (r)
		वापस r;

	अगर (ovl->manager) अणु
		r = ovl->manager->apply(ovl->manager);
		अगर (r)
			वापस r;
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार overlay_enabled_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ovl->is_enabled(ovl));
पूर्ण

अटल sमाप_प्रकार overlay_enabled_store(काष्ठा omap_overlay *ovl, स्थिर अक्षर *buf,
		माप_प्रकार size)
अणु
	पूर्णांक r;
	bool enable;

	r = strtobool(buf, &enable);
	अगर (r)
		वापस r;

	अगर (enable)
		r = ovl->enable(ovl);
	अन्यथा
		r = ovl->disable(ovl);

	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार overlay_global_alpha_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			info.global_alpha);
पूर्ण

अटल sमाप_प्रकार overlay_global_alpha_store(काष्ठा omap_overlay *ovl,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r;
	u8 alpha;
	काष्ठा omap_overlay_info info;

	अगर ((ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA) == 0)
		वापस -ENODEV;

	r = kstrtou8(buf, 0, &alpha);
	अगर (r)
		वापस r;

	ovl->get_overlay_info(ovl, &info);

	info.global_alpha = alpha;

	r = ovl->set_overlay_info(ovl, &info);
	अगर (r)
		वापस r;

	अगर (ovl->manager) अणु
		r = ovl->manager->apply(ovl->manager);
		अगर (r)
			वापस r;
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार overlay_pre_mult_alpha_show(काष्ठा omap_overlay *ovl,
		अक्षर *buf)
अणु
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			info.pre_mult_alpha);
पूर्ण

अटल sमाप_प्रकार overlay_pre_mult_alpha_store(काष्ठा omap_overlay *ovl,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r;
	u8 alpha;
	काष्ठा omap_overlay_info info;

	अगर ((ovl->caps & OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA) == 0)
		वापस -ENODEV;

	r = kstrtou8(buf, 0, &alpha);
	अगर (r)
		वापस r;

	ovl->get_overlay_info(ovl, &info);

	info.pre_mult_alpha = alpha;

	r = ovl->set_overlay_info(ovl, &info);
	अगर (r)
		वापस r;

	अगर (ovl->manager) अणु
		r = ovl->manager->apply(ovl->manager);
		अगर (r)
			वापस r;
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार overlay_zorder_show(काष्ठा omap_overlay *ovl, अक्षर *buf)
अणु
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", info.zorder);
पूर्ण

अटल sमाप_प्रकार overlay_zorder_store(काष्ठा omap_overlay *ovl,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r;
	u8 zorder;
	काष्ठा omap_overlay_info info;

	अगर ((ovl->caps & OMAP_DSS_OVL_CAP_ZORDER) == 0)
		वापस -ENODEV;

	r = kstrtou8(buf, 0, &zorder);
	अगर (r)
		वापस r;

	ovl->get_overlay_info(ovl, &info);

	info.zorder = zorder;

	r = ovl->set_overlay_info(ovl, &info);
	अगर (r)
		वापस r;

	अगर (ovl->manager) अणु
		r = ovl->manager->apply(ovl->manager);
		अगर (r)
			वापस r;
	पूर्ण

	वापस size;
पूर्ण

काष्ठा overlay_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा omap_overlay *, अक्षर *);
	sमाप_प्रकार	(*store)(काष्ठा omap_overlay *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

#घोषणा OVERLAY_ATTR(_name, _mode, _show, _store) \
	काष्ठा overlay_attribute overlay_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

अटल OVERLAY_ATTR(name, S_IRUGO, overlay_name_show, शून्य);
अटल OVERLAY_ATTR(manager, S_IRUGO|S_IWUSR,
		overlay_manager_show, overlay_manager_store);
अटल OVERLAY_ATTR(input_size, S_IRUGO, overlay_input_size_show, शून्य);
अटल OVERLAY_ATTR(screen_width, S_IRUGO, overlay_screen_width_show, शून्य);
अटल OVERLAY_ATTR(position, S_IRUGO|S_IWUSR,
		overlay_position_show, overlay_position_store);
अटल OVERLAY_ATTR(output_size, S_IRUGO|S_IWUSR,
		overlay_output_size_show, overlay_output_size_store);
अटल OVERLAY_ATTR(enabled, S_IRUGO|S_IWUSR,
		overlay_enabled_show, overlay_enabled_store);
अटल OVERLAY_ATTR(global_alpha, S_IRUGO|S_IWUSR,
		overlay_global_alpha_show, overlay_global_alpha_store);
अटल OVERLAY_ATTR(pre_mult_alpha, S_IRUGO|S_IWUSR,
		overlay_pre_mult_alpha_show,
		overlay_pre_mult_alpha_store);
अटल OVERLAY_ATTR(zorder, S_IRUGO|S_IWUSR,
		overlay_zorder_show, overlay_zorder_store);

अटल काष्ठा attribute *overlay_sysfs_attrs[] = अणु
	&overlay_attr_name.attr,
	&overlay_attr_manager.attr,
	&overlay_attr_input_size.attr,
	&overlay_attr_screen_width.attr,
	&overlay_attr_position.attr,
	&overlay_attr_output_size.attr,
	&overlay_attr_enabled.attr,
	&overlay_attr_global_alpha.attr,
	&overlay_attr_pre_mult_alpha.attr,
	&overlay_attr_zorder.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार overlay_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा omap_overlay *overlay;
	काष्ठा overlay_attribute *overlay_attr;

	overlay = container_of(kobj, काष्ठा omap_overlay, kobj);
	overlay_attr = container_of(attr, काष्ठा overlay_attribute, attr);

	अगर (!overlay_attr->show)
		वापस -ENOENT;

	वापस overlay_attr->show(overlay, buf);
पूर्ण

अटल sमाप_प्रकार overlay_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay *overlay;
	काष्ठा overlay_attribute *overlay_attr;

	overlay = container_of(kobj, काष्ठा omap_overlay, kobj);
	overlay_attr = container_of(attr, काष्ठा overlay_attribute, attr);

	अगर (!overlay_attr->store)
		वापस -ENOENT;

	वापस overlay_attr->store(overlay, buf, size);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops overlay_sysfs_ops = अणु
	.show = overlay_attr_show,
	.store = overlay_attr_store,
पूर्ण;

अटल काष्ठा kobj_type overlay_ktype = अणु
	.sysfs_ops = &overlay_sysfs_ops,
	.शेष_attrs = overlay_sysfs_attrs,
पूर्ण;

पूर्णांक dss_overlay_kobj_init(काष्ठा omap_overlay *ovl,
		काष्ठा platक्रमm_device *pdev)
अणु
	वापस kobject_init_and_add(&ovl->kobj, &overlay_ktype,
			&pdev->dev.kobj, "overlay%d", ovl->id);
पूर्ण

व्योम dss_overlay_kobj_uninit(काष्ठा omap_overlay *ovl)
अणु
	kobject_del(&ovl->kobj);
	kobject_put(&ovl->kobj);
पूर्ण
