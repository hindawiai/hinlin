<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "DISPLAY"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sysfs.h>

#समावेश <video/omapfb_dss.h>
#समावेश "dss.h"

अटल sमाप_प्रकार display_name_show(काष्ठा omap_dss_device *dssdev, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			dssdev->name ?
			dssdev->name : "");
पूर्ण

अटल sमाप_प्रकार display_enabled_show(काष्ठा omap_dss_device *dssdev, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			omapdss_device_is_enabled(dssdev));
पूर्ण

अटल sमाप_प्रकार display_enabled_store(काष्ठा omap_dss_device *dssdev,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r;
	bool enable;

	r = strtobool(buf, &enable);
	अगर (r)
		वापस r;

	अगर (enable == omapdss_device_is_enabled(dssdev))
		वापस size;

	अगर (omapdss_device_is_connected(dssdev) == false)
		वापस -ENODEV;

	अगर (enable) अणु
		r = dssdev->driver->enable(dssdev);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		dssdev->driver->disable(dssdev);
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार display_tear_show(काष्ठा omap_dss_device *dssdev, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			dssdev->driver->get_te ?
			dssdev->driver->get_te(dssdev) : 0);
पूर्ण

अटल sमाप_प्रकार display_tear_store(काष्ठा omap_dss_device *dssdev,
	स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r;
	bool te;

	अगर (!dssdev->driver->enable_te || !dssdev->driver->get_te)
		वापस -ENOENT;

	r = strtobool(buf, &te);
	अगर (r)
		वापस r;

	r = dssdev->driver->enable_te(dssdev, te);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार display_timings_show(काष्ठा omap_dss_device *dssdev, अक्षर *buf)
अणु
	काष्ठा omap_video_timings t;

	अगर (!dssdev->driver->get_timings)
		वापस -ENOENT;

	dssdev->driver->get_timings(dssdev, &t);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u,%u/%u/%u/%u,%u/%u/%u/%u\n",
			t.pixelघड़ी,
			t.x_res, t.hfp, t.hbp, t.hsw,
			t.y_res, t.vfp, t.vbp, t.vsw);
पूर्ण

अटल sमाप_प्रकार display_timings_store(काष्ठा omap_dss_device *dssdev,
	स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_video_timings t = dssdev->panel.timings;
	पूर्णांक r, found;

	अगर (!dssdev->driver->set_timings || !dssdev->driver->check_timings)
		वापस -ENOENT;

	found = 0;
#अगर_घोषित CONFIG_FB_OMAP2_DSS_VENC
	अगर (म_भेदन("pal", buf, 3) == 0) अणु
		t = omap_dss_pal_timings;
		found = 1;
	पूर्ण अन्यथा अगर (म_भेदन("ntsc", buf, 4) == 0) अणु
		t = omap_dss_ntsc_timings;
		found = 1;
	पूर्ण
#पूर्ण_अगर
	अगर (!found && माला_पूछो(buf, "%u,%hu/%hu/%hu/%hu,%hu/%hu/%hu/%hu",
				&t.pixelघड़ी,
				&t.x_res, &t.hfp, &t.hbp, &t.hsw,
				&t.y_res, &t.vfp, &t.vbp, &t.vsw) != 9)
		वापस -EINVAL;

	r = dssdev->driver->check_timings(dssdev, &t);
	अगर (r)
		वापस r;

	dssdev->driver->disable(dssdev);
	dssdev->driver->set_timings(dssdev, &t);
	r = dssdev->driver->enable(dssdev);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार display_rotate_show(काष्ठा omap_dss_device *dssdev, अक्षर *buf)
अणु
	पूर्णांक rotate;
	अगर (!dssdev->driver->get_rotate)
		वापस -ENOENT;
	rotate = dssdev->driver->get_rotate(dssdev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", rotate);
पूर्ण

अटल sमाप_प्रकार display_rotate_store(काष्ठा omap_dss_device *dssdev,
	स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक rot, r;

	अगर (!dssdev->driver->set_rotate || !dssdev->driver->get_rotate)
		वापस -ENOENT;

	r = kstrtoपूर्णांक(buf, 0, &rot);
	अगर (r)
		वापस r;

	r = dssdev->driver->set_rotate(dssdev, rot);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार display_mirror_show(काष्ठा omap_dss_device *dssdev, अक्षर *buf)
अणु
	पूर्णांक mirror;
	अगर (!dssdev->driver->get_mirror)
		वापस -ENOENT;
	mirror = dssdev->driver->get_mirror(dssdev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", mirror);
पूर्ण

अटल sमाप_प्रकार display_mirror_store(काष्ठा omap_dss_device *dssdev,
	स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक r;
	bool mirror;

	अगर (!dssdev->driver->set_mirror || !dssdev->driver->get_mirror)
		वापस -ENOENT;

	r = strtobool(buf, &mirror);
	अगर (r)
		वापस r;

	r = dssdev->driver->set_mirror(dssdev, mirror);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

अटल sमाप_प्रकार display_wss_show(काष्ठा omap_dss_device *dssdev, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक wss;

	अगर (!dssdev->driver->get_wss)
		वापस -ENOENT;

	wss = dssdev->driver->get_wss(dssdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%05x\n", wss);
पूर्ण

अटल sमाप_प्रकार display_wss_store(काष्ठा omap_dss_device *dssdev,
	स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u32 wss;
	पूर्णांक r;

	अगर (!dssdev->driver->get_wss || !dssdev->driver->set_wss)
		वापस -ENOENT;

	r = kstrtou32(buf, 0, &wss);
	अगर (r)
		वापस r;

	अगर (wss > 0xfffff)
		वापस -EINVAL;

	r = dssdev->driver->set_wss(dssdev, wss);
	अगर (r)
		वापस r;

	वापस size;
पूर्ण

काष्ठा display_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा omap_dss_device *, अक्षर *);
	sमाप_प्रकार	(*store)(काष्ठा omap_dss_device *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

#घोषणा DISPLAY_ATTR(_name, _mode, _show, _store) \
	काष्ठा display_attribute display_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

अटल DISPLAY_ATTR(name, S_IRUGO, display_name_show, शून्य);
अटल DISPLAY_ATTR(display_name, S_IRUGO, display_name_show, शून्य);
अटल DISPLAY_ATTR(enabled, S_IRUGO|S_IWUSR,
		display_enabled_show, display_enabled_store);
अटल DISPLAY_ATTR(tear_elim, S_IRUGO|S_IWUSR,
		display_tear_show, display_tear_store);
अटल DISPLAY_ATTR(timings, S_IRUGO|S_IWUSR,
		display_timings_show, display_timings_store);
अटल DISPLAY_ATTR(rotate, S_IRUGO|S_IWUSR,
		display_rotate_show, display_rotate_store);
अटल DISPLAY_ATTR(mirror, S_IRUGO|S_IWUSR,
		display_mirror_show, display_mirror_store);
अटल DISPLAY_ATTR(wss, S_IRUGO|S_IWUSR,
		display_wss_show, display_wss_store);

अटल काष्ठा attribute *display_sysfs_attrs[] = अणु
	&display_attr_name.attr,
	&display_attr_display_name.attr,
	&display_attr_enabled.attr,
	&display_attr_tear_elim.attr,
	&display_attr_timings.attr,
	&display_attr_rotate.attr,
	&display_attr_mirror.attr,
	&display_attr_wss.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार display_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा omap_dss_device *dssdev;
	काष्ठा display_attribute *display_attr;

	dssdev = container_of(kobj, काष्ठा omap_dss_device, kobj);
	display_attr = container_of(attr, काष्ठा display_attribute, attr);

	अगर (!display_attr->show)
		वापस -ENOENT;

	वापस display_attr->show(dssdev, buf);
पूर्ण

अटल sमाप_प्रकार display_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_dss_device *dssdev;
	काष्ठा display_attribute *display_attr;

	dssdev = container_of(kobj, काष्ठा omap_dss_device, kobj);
	display_attr = container_of(attr, काष्ठा display_attribute, attr);

	अगर (!display_attr->store)
		वापस -ENOENT;

	वापस display_attr->store(dssdev, buf, size);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops display_sysfs_ops = अणु
	.show = display_attr_show,
	.store = display_attr_store,
पूर्ण;

अटल काष्ठा kobj_type display_ktype = अणु
	.sysfs_ops = &display_sysfs_ops,
	.शेष_attrs = display_sysfs_attrs,
पूर्ण;

पूर्णांक display_init_sysfs(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *dssdev = शून्य;
	पूर्णांक r;

	क्रम_each_dss_dev(dssdev) अणु
		r = kobject_init_and_add(&dssdev->kobj, &display_ktype,
			&pdev->dev.kobj, "%s", dssdev->alias);
		अगर (r) अणु
			DSSERR("failed to create sysfs files\n");
			omap_dss_put_device(dssdev);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	display_uninit_sysfs(pdev);

	वापस r;
पूर्ण

व्योम display_uninit_sysfs(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *dssdev = शून्य;

	क्रम_each_dss_dev(dssdev) अणु
		अगर (kobject_name(&dssdev->kobj) == शून्य)
			जारी;

		kobject_del(&dssdev->kobj);
		kobject_put(&dssdev->kobj);

		स_रखो(&dssdev->kobj, 0, माप(dssdev->kobj));
	पूर्ण
पूर्ण
