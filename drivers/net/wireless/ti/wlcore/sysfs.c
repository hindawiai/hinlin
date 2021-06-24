<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wlcore
 *
 * Copyright (C) 2013 Texas Instruments Inc.
 */

#समावेश <linux/pm_runसमय.स>

#समावेश "acx.h"
#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "sysfs.h"

अटल sमाप_प्रकार wl1271_sysfs_show_bt_coex_state(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा wl1271 *wl = dev_get_drvdata(dev);
	sमाप_प्रकार len;

	len = PAGE_SIZE;

	mutex_lock(&wl->mutex);
	len = snम_लिखो(buf, len, "%d\n\n0 - off\n1 - on\n",
		       wl->sg_enabled);
	mutex_unlock(&wl->mutex);

	वापस len;

पूर्ण

अटल sमाप_प्रकार wl1271_sysfs_store_bt_coex_state(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा wl1271 *wl = dev_get_drvdata(dev);
	अचिन्हित दीर्घ res;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &res);
	अगर (ret < 0) अणु
		wl1271_warning("incorrect value written to bt_coex_mode");
		वापस count;
	पूर्ण

	mutex_lock(&wl->mutex);

	res = !!res;

	अगर (res == wl->sg_enabled)
		जाओ out;

	wl->sg_enabled = res;

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl1271_acx_sg_enable(wl, wl->sg_enabled);
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

 out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(bt_coex_state, 0644,
		   wl1271_sysfs_show_bt_coex_state,
		   wl1271_sysfs_store_bt_coex_state);

अटल sमाप_प्रकार wl1271_sysfs_show_hw_pg_ver(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा wl1271 *wl = dev_get_drvdata(dev);
	sमाप_प्रकार len;

	len = PAGE_SIZE;

	mutex_lock(&wl->mutex);
	अगर (wl->hw_pg_ver >= 0)
		len = snम_लिखो(buf, len, "%d\n", wl->hw_pg_ver);
	अन्यथा
		len = snम_लिखो(buf, len, "n/a\n");
	mutex_unlock(&wl->mutex);

	वापस len;
पूर्ण

अटल DEVICE_ATTR(hw_pg_ver, 0444, wl1271_sysfs_show_hw_pg_ver, शून्य);

अटल sमाप_प्रकार wl1271_sysfs_पढ़ो_fwlog(काष्ठा file *filp, काष्ठा kobject *kobj,
				       काष्ठा bin_attribute *bin_attr,
				       अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा wl1271 *wl = dev_get_drvdata(dev);
	sमाप_प्रकार len;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&wl->mutex);
	अगर (ret < 0)
		वापस -ERESTARTSYS;

	/* Check अगर the fwlog is still valid */
	अगर (wl->fwlog_size < 0) अणु
		mutex_unlock(&wl->mutex);
		वापस 0;
	पूर्ण

	/* Seeking is not supported - old logs are not kept. Disregard pos. */
	len = min_t(माप_प्रकार, count, wl->fwlog_size);
	wl->fwlog_size -= len;
	स_नकल(buffer, wl->fwlog, len);

	/* Make room क्रम new messages */
	स_हटाओ(wl->fwlog, wl->fwlog + len, wl->fwlog_size);

	mutex_unlock(&wl->mutex);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा bin_attribute fwlog_attr = अणु
	.attr = अणु .name = "fwlog", .mode = 0400 पूर्ण,
	.पढ़ो = wl1271_sysfs_पढ़ो_fwlog,
पूर्ण;

पूर्णांक wlcore_sysfs_init(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	/* Create sysfs file to control bt coex state */
	ret = device_create_file(wl->dev, &dev_attr_bt_coex_state);
	अगर (ret < 0) अणु
		wl1271_error("failed to create sysfs file bt_coex_state");
		जाओ out;
	पूर्ण

	/* Create sysfs file to get HW PG version */
	ret = device_create_file(wl->dev, &dev_attr_hw_pg_ver);
	अगर (ret < 0) अणु
		wl1271_error("failed to create sysfs file hw_pg_ver");
		जाओ out_bt_coex_state;
	पूर्ण

	/* Create sysfs file क्रम the FW log */
	ret = device_create_bin_file(wl->dev, &fwlog_attr);
	अगर (ret < 0) अणु
		wl1271_error("failed to create sysfs file fwlog");
		जाओ out_hw_pg_ver;
	पूर्ण

	जाओ out;

out_hw_pg_ver:
	device_हटाओ_file(wl->dev, &dev_attr_hw_pg_ver);

out_bt_coex_state:
	device_हटाओ_file(wl->dev, &dev_attr_bt_coex_state);

out:
	वापस ret;
पूर्ण

व्योम wlcore_sysfs_मुक्त(काष्ठा wl1271 *wl)
अणु
	device_हटाओ_bin_file(wl->dev, &fwlog_attr);

	device_हटाओ_file(wl->dev, &dev_attr_hw_pg_ver);

	device_हटाओ_file(wl->dev, &dev_attr_bt_coex_state);
पूर्ण
