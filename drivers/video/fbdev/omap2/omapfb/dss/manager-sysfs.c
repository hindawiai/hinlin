<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "MANAGER"

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/jअगरfies.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

अटल sमाप_प्रकार manager_name_show(काष्ठा omap_overlay_manager *mgr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", mgr->name);
पूर्ण

अटल sमाप_प्रकार manager_display_show(काष्ठा omap_overlay_manager *mgr, अक्षर *buf)
अणु
	काष्ठा omap_dss_device *dssdev = mgr->get_device(mgr);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", dssdev ?
			dssdev->name : "<none>");
पूर्ण

अटल पूर्णांक manager_display_match(काष्ठा omap_dss_device *dssdev, व्योम *data)
अणु
	स्थिर अक्षर *str = data;

	वापस sysfs_streq(dssdev->name, str);
पूर्ण

अटल sमाप_प्रकार manager_display_store(काष्ठा omap_overlay_manager *mgr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r = 0;
	माप_प्रकार len = size;
	काष्ठा omap_dss_device *dssdev = शून्य;
	काष्ठा omap_dss_device *old_dssdev;

	अगर (buf[size-1] == '\n')
		--len;

	अगर (len > 0)
		dssdev = omap_dss_find_device((व्योम *)buf,
			manager_display_match);

	अगर (len > 0 && dssdev == शून्य)
		वापस -EINVAL;

	अगर (dssdev) अणु
		DSSDBG("display %s found\n", dssdev->name);

		अगर (omapdss_device_is_connected(dssdev)) अणु
			DSSERR("new display is already connected\n");
			r = -EINVAL;
			जाओ put_device;
		पूर्ण

		अगर (omapdss_device_is_enabled(dssdev)) अणु
			DSSERR("new display is not disabled\n");
			r = -EINVAL;
			जाओ put_device;
		पूर्ण
	पूर्ण

	old_dssdev = mgr->get_device(mgr);
	अगर (old_dssdev) अणु
		अगर (omapdss_device_is_enabled(old_dssdev)) अणु
			DSSERR("old display is not disabled\n");
			r = -EINVAL;
			जाओ put_device;
		पूर्ण

		old_dssdev->driver->disconnect(old_dssdev);
	पूर्ण

	अगर (dssdev) अणु
		r = dssdev->driver->connect(dssdev);
		अगर (r) अणु
			DSSERR("failed to connect new device\n");
			जाओ put_device;
		पूर्ण

		old_dssdev = mgr->get_device(mgr);
		अगर (old_dssdev != dssdev) अणु
			DSSERR("failed to connect device to this manager\n");
			dssdev->driver->disconnect(dssdev);
			जाओ put_device;
		पूर्ण

		r = mgr->apply(mgr);
		अगर (r) अणु
			DSSERR("failed to apply dispc config\n");
			जाओ put_device;
		पूर्ण
	पूर्ण

put_device:
	अगर (dssdev)
		omap_dss_put_device(dssdev);

	वापस r ? r : size;
पूर्ण

अटल sमाप_प्रकार manager_शेष_color_show(काष्ठा omap_overlay_manager *mgr,
					  अक्षर *buf)
अणु
	काष्ठा omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%#x\n", info.शेष_color);
पूर्ण

अटल sमाप_प्रकार manager_शेष_color_store(काष्ठा omap_overlay_manager *mgr,
					   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay_manager_info info;
	u32 color;
	पूर्णांक r;

	r = kstrtouपूर्णांक(buf, 0, &color);
	अगर (r)
		वापस r;

	mgr->get_manager_info(mgr, &info);

	info.शेष_color = color;

	r = mgr->set_manager_info(mgr, &info);
	अगर (r)
		वापस r;

	r = mgr->apply(mgr);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल स्थिर अक्षर *trans_key_type_str[] = अणु
	"gfx-destination",
	"video-source",
पूर्ण;

अटल sमाप_प्रकार manager_trans_key_type_show(काष्ठा omap_overlay_manager *mgr,
					   अक्षर *buf)
अणु
	क्रमागत omap_dss_trans_key_type key_type;
	काष्ठा omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	key_type = info.trans_key_type;
	BUG_ON(key_type >= ARRAY_SIZE(trans_key_type_str));

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", trans_key_type_str[key_type]);
पूर्ण

अटल sमाप_प्रकार manager_trans_key_type_store(काष्ठा omap_overlay_manager *mgr,
					    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay_manager_info info;
	पूर्णांक r;

	r = sysfs_match_string(trans_key_type_str, buf);
	अगर (r < 0)
		वापस r;

	mgr->get_manager_info(mgr, &info);

	info.trans_key_type = r;

	r = mgr->set_manager_info(mgr, &info);
	अगर (r)
		वापस r;

	r = mgr->apply(mgr);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार manager_trans_key_value_show(काष्ठा omap_overlay_manager *mgr,
					    अक्षर *buf)
अणु
	काष्ठा omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%#x\n", info.trans_key);
पूर्ण

अटल sमाप_प्रकार manager_trans_key_value_store(काष्ठा omap_overlay_manager *mgr,
					     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay_manager_info info;
	u32 key_value;
	पूर्णांक r;

	r = kstrtouपूर्णांक(buf, 0, &key_value);
	अगर (r)
		वापस r;

	mgr->get_manager_info(mgr, &info);

	info.trans_key = key_value;

	r = mgr->set_manager_info(mgr, &info);
	अगर (r)
		वापस r;

	r = mgr->apply(mgr);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार manager_trans_key_enabled_show(काष्ठा omap_overlay_manager *mgr,
					      अक्षर *buf)
अणु
	काष्ठा omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", info.trans_enabled);
पूर्ण

अटल sमाप_प्रकार manager_trans_key_enabled_store(काष्ठा omap_overlay_manager *mgr,
					       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay_manager_info info;
	bool enable;
	पूर्णांक r;

	r = strtobool(buf, &enable);
	अगर (r)
		वापस r;

	mgr->get_manager_info(mgr, &info);

	info.trans_enabled = enable;

	r = mgr->set_manager_info(mgr, &info);
	अगर (r)
		वापस r;

	r = mgr->apply(mgr);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार manager_alpha_blending_enabled_show(
		काष्ठा omap_overlay_manager *mgr, अक्षर *buf)
अणु
	काष्ठा omap_overlay_manager_info info;

	अगर(!dss_has_feature(FEAT_ALPHA_FIXED_ZORDER))
		वापस -ENODEV;

	mgr->get_manager_info(mgr, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
		info.partial_alpha_enabled);
पूर्ण

अटल sमाप_प्रकार manager_alpha_blending_enabled_store(
		काष्ठा omap_overlay_manager *mgr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay_manager_info info;
	bool enable;
	पूर्णांक r;

	अगर(!dss_has_feature(FEAT_ALPHA_FIXED_ZORDER))
		वापस -ENODEV;

	r = strtobool(buf, &enable);
	अगर (r)
		वापस r;

	mgr->get_manager_info(mgr, &info);

	info.partial_alpha_enabled = enable;

	r = mgr->set_manager_info(mgr, &info);
	अगर (r)
		वापस r;

	r = mgr->apply(mgr);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार manager_cpr_enable_show(काष्ठा omap_overlay_manager *mgr,
		अक्षर *buf)
अणु
	काष्ठा omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", info.cpr_enable);
पूर्ण

अटल sमाप_प्रकार manager_cpr_enable_store(काष्ठा omap_overlay_manager *mgr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay_manager_info info;
	पूर्णांक r;
	bool enable;

	अगर (!dss_has_feature(FEAT_CPR))
		वापस -ENODEV;

	r = strtobool(buf, &enable);
	अगर (r)
		वापस r;

	mgr->get_manager_info(mgr, &info);

	अगर (info.cpr_enable == enable)
		वापस size;

	info.cpr_enable = enable;

	r = mgr->set_manager_info(mgr, &info);
	अगर (r)
		वापस r;

	r = mgr->apply(mgr);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार manager_cpr_coef_show(काष्ठा omap_overlay_manager *mgr,
		अक्षर *buf)
अणु
	काष्ठा omap_overlay_manager_info info;

	mgr->get_manager_info(mgr, &info);

	वापस snम_लिखो(buf, PAGE_SIZE,
			"%d %d %d %d %d %d %d %d %d\n",
			info.cpr_coefs.rr,
			info.cpr_coefs.rg,
			info.cpr_coefs.rb,
			info.cpr_coefs.gr,
			info.cpr_coefs.gg,
			info.cpr_coefs.gb,
			info.cpr_coefs.br,
			info.cpr_coefs.bg,
			info.cpr_coefs.bb);
पूर्ण

अटल sमाप_प्रकार manager_cpr_coef_store(काष्ठा omap_overlay_manager *mgr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay_manager_info info;
	काष्ठा omap_dss_cpr_coefs coefs;
	पूर्णांक r, i;
	s16 *arr;

	अगर (!dss_has_feature(FEAT_CPR))
		वापस -ENODEV;

	अगर (माला_पूछो(buf, "%hd %hd %hd %hd %hd %hd %hd %hd %hd",
				&coefs.rr, &coefs.rg, &coefs.rb,
				&coefs.gr, &coefs.gg, &coefs.gb,
				&coefs.br, &coefs.bg, &coefs.bb) != 9)
		वापस -EINVAL;

	arr = (s16[])अणु coefs.rr, coefs.rg, coefs.rb,
		coefs.gr, coefs.gg, coefs.gb,
		coefs.br, coefs.bg, coefs.bb पूर्ण;

	क्रम (i = 0; i < 9; ++i) अणु
		अगर (arr[i] < -512 || arr[i] > 511)
			वापस -EINVAL;
	पूर्ण

	mgr->get_manager_info(mgr, &info);

	info.cpr_coefs = coefs;

	r = mgr->set_manager_info(mgr, &info);
	अगर (r)
		वापस r;

	r = mgr->apply(mgr);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

काष्ठा manager_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा omap_overlay_manager *, अक्षर *);
	sमाप_प्रकार	(*store)(काष्ठा omap_overlay_manager *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

#घोषणा MANAGER_ATTR(_name, _mode, _show, _store) \
	काष्ठा manager_attribute manager_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

अटल MANAGER_ATTR(name, S_IRUGO, manager_name_show, शून्य);
अटल MANAGER_ATTR(display, S_IRUGO|S_IWUSR,
		manager_display_show, manager_display_store);
अटल MANAGER_ATTR(शेष_color, S_IRUGO|S_IWUSR,
		manager_शेष_color_show, manager_शेष_color_store);
अटल MANAGER_ATTR(trans_key_type, S_IRUGO|S_IWUSR,
		manager_trans_key_type_show, manager_trans_key_type_store);
अटल MANAGER_ATTR(trans_key_value, S_IRUGO|S_IWUSR,
		manager_trans_key_value_show, manager_trans_key_value_store);
अटल MANAGER_ATTR(trans_key_enabled, S_IRUGO|S_IWUSR,
		manager_trans_key_enabled_show,
		manager_trans_key_enabled_store);
अटल MANAGER_ATTR(alpha_blending_enabled, S_IRUGO|S_IWUSR,
		manager_alpha_blending_enabled_show,
		manager_alpha_blending_enabled_store);
अटल MANAGER_ATTR(cpr_enable, S_IRUGO|S_IWUSR,
		manager_cpr_enable_show,
		manager_cpr_enable_store);
अटल MANAGER_ATTR(cpr_coef, S_IRUGO|S_IWUSR,
		manager_cpr_coef_show,
		manager_cpr_coef_store);


अटल काष्ठा attribute *manager_sysfs_attrs[] = अणु
	&manager_attr_name.attr,
	&manager_attr_display.attr,
	&manager_attr_शेष_color.attr,
	&manager_attr_trans_key_type.attr,
	&manager_attr_trans_key_value.attr,
	&manager_attr_trans_key_enabled.attr,
	&manager_attr_alpha_blending_enabled.attr,
	&manager_attr_cpr_enable.attr,
	&manager_attr_cpr_coef.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार manager_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा omap_overlay_manager *manager;
	काष्ठा manager_attribute *manager_attr;

	manager = container_of(kobj, काष्ठा omap_overlay_manager, kobj);
	manager_attr = container_of(attr, काष्ठा manager_attribute, attr);

	अगर (!manager_attr->show)
		वापस -ENOENT;

	वापस manager_attr->show(manager, buf);
पूर्ण

अटल sमाप_प्रकार manager_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_overlay_manager *manager;
	काष्ठा manager_attribute *manager_attr;

	manager = container_of(kobj, काष्ठा omap_overlay_manager, kobj);
	manager_attr = container_of(attr, काष्ठा manager_attribute, attr);

	अगर (!manager_attr->store)
		वापस -ENOENT;

	वापस manager_attr->store(manager, buf, size);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops manager_sysfs_ops = अणु
	.show = manager_attr_show,
	.store = manager_attr_store,
पूर्ण;

अटल काष्ठा kobj_type manager_ktype = अणु
	.sysfs_ops = &manager_sysfs_ops,
	.शेष_attrs = manager_sysfs_attrs,
पूर्ण;

पूर्णांक dss_manager_kobj_init(काष्ठा omap_overlay_manager *mgr,
		काष्ठा platक्रमm_device *pdev)
अणु
	वापस kobject_init_and_add(&mgr->kobj, &manager_ktype,
			&pdev->dev.kobj, "manager%d", mgr->id);
पूर्ण

व्योम dss_manager_kobj_uninit(काष्ठा omap_overlay_manager *mgr)
अणु
	kobject_del(&mgr->kobj);
	kobject_put(&mgr->kobj);

	स_रखो(&mgr->kobj, 0, माप(mgr->kobj));
पूर्ण
