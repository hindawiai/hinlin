<शैली गुरु>
/******************************************************************************
 * Xen balloon driver - enables वापसing/claiming memory to/from Xen.
 *
 * Copyright (c) 2003, B Dragovic
 * Copyright (c) 2003-2004, M Williamson, K Fraser
 * Copyright (c) 2005 Dan M. Smith, IBM Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm_types.h>
#समावेश <linux/init.h>
#समावेश <linux/capability.h>
#समावेश <linux/memory_hotplug.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/balloon.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/features.h>
#समावेश <xen/page.h>
#समावेश <xen/mem-reservation.h>

#घोषणा PAGES2KB(_p) ((_p)<<(PAGE_SHIFT-10))

#घोषणा BALLOON_CLASS_NAME "xen_memory"

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
u64 xen_saved_max_mem_size = 0;
#पूर्ण_अगर

अटल काष्ठा device balloon_dev;

अटल पूर्णांक रेजिस्टर_balloon(काष्ठा device *dev);

/* React to a change in the target key */
अटल व्योम watch_target(काष्ठा xenbus_watch *watch,
			 स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	अचिन्हित दीर्घ दीर्घ new_target, अटल_max;
	पूर्णांक err;
	अटल bool watch_fired;
	अटल दीर्घ target_dअगरf;

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	/* The balloon driver will take care of adding memory now. */
	अगर (xen_saved_max_mem_size)
		max_mem_size = xen_saved_max_mem_size;
#पूर्ण_अगर

	err = xenbus_म_पूछो(XBT_NIL, "memory", "target", "%llu", &new_target);
	अगर (err != 1) अणु
		/* This is ok (क्रम करोमुख्य0 at least) - so just वापस */
		वापस;
	पूर्ण

	/* The given memory/target value is in KiB, so it needs converting to
	 * pages. PAGE_SHIFT converts bytes to pages, hence PAGE_SHIFT - 10.
	 */
	new_target >>= PAGE_SHIFT - 10;

	अगर (!watch_fired) अणु
		watch_fired = true;

		अगर ((xenbus_म_पूछो(XBT_NIL, "memory", "static-max",
				  "%llu", &अटल_max) == 1) ||
		    (xenbus_म_पूछो(XBT_NIL, "memory", "memory_static_max",
				  "%llu", &अटल_max) == 1))
			अटल_max >>= PAGE_SHIFT - 10;
		अन्यथा
			अटल_max = balloon_stats.current_pages;

		target_dअगरf = (xen_pv_करोमुख्य() || xen_initial_करोमुख्य()) ? 0
				: अटल_max - balloon_stats.target_pages;
	पूर्ण

	balloon_set_new_target(new_target - target_dअगरf);
पूर्ण
अटल काष्ठा xenbus_watch target_watch = अणु
	.node = "memory/target",
	.callback = watch_target,
पूर्ण;


अटल पूर्णांक balloon_init_watcher(काष्ठा notअगरier_block *notअगरier,
				अचिन्हित दीर्घ event,
				व्योम *data)
अणु
	पूर्णांक err;

	err = रेजिस्टर_xenbus_watch(&target_watch);
	अगर (err)
		pr_err("Failed to set balloon watcher\n");

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block xenstore_notअगरier = अणु
	.notअगरier_call = balloon_init_watcher,
पूर्ण;

व्योम xen_balloon_init(व्योम)
अणु
	रेजिस्टर_balloon(&balloon_dev);

	रेजिस्टर_xenstore_notअगरier(&xenstore_notअगरier);
पूर्ण
EXPORT_SYMBOL_GPL(xen_balloon_init);

#घोषणा BALLOON_SHOW(name, क्रमmat, args...)				\
	अटल sमाप_प्रकार show_##name(काष्ठा device *dev,			\
				   काष्ठा device_attribute *attr,	\
				   अक्षर *buf)				\
	अणु								\
		वापस प्र_लिखो(buf, क्रमmat, ##args);			\
	पूर्ण								\
	अटल DEVICE_ATTR(name, S_IRUGO, show_##name, शून्य)

BALLOON_SHOW(current_kb, "%lu\n", PAGES2KB(balloon_stats.current_pages));
BALLOON_SHOW(low_kb, "%lu\n", PAGES2KB(balloon_stats.balloon_low));
BALLOON_SHOW(high_kb, "%lu\n", PAGES2KB(balloon_stats.balloon_high));

अटल DEVICE_ULONG_ATTR(schedule_delay, 0444, balloon_stats.schedule_delay);
अटल DEVICE_ULONG_ATTR(max_schedule_delay, 0644, balloon_stats.max_schedule_delay);
अटल DEVICE_ULONG_ATTR(retry_count, 0444, balloon_stats.retry_count);
अटल DEVICE_ULONG_ATTR(max_retry_count, 0644, balloon_stats.max_retry_count);
अटल DEVICE_BOOL_ATTR(scrub_pages, 0644, xen_scrub_pages);

अटल sमाप_प्रकार show_target_kb(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", PAGES2KB(balloon_stats.target_pages));
पूर्ण

अटल sमाप_प्रकार store_target_kb(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	अक्षर *endअक्षर;
	अचिन्हित दीर्घ दीर्घ target_bytes;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	target_bytes = simple_म_से_अदीर्घl(buf, &endअक्षर, 0) * 1024;

	balloon_set_new_target(target_bytes >> PAGE_SHIFT);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(target_kb, S_IRUGO | S_IWUSR,
		   show_target_kb, store_target_kb);


अटल sमाप_प्रकार show_target(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)balloon_stats.target_pages
		       << PAGE_SHIFT);
पूर्ण

अटल sमाप_प्रकार store_target(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	अक्षर *endअक्षर;
	अचिन्हित दीर्घ दीर्घ target_bytes;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	target_bytes = memparse(buf, &endअक्षर);

	balloon_set_new_target(target_bytes >> PAGE_SHIFT);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(target, S_IRUGO | S_IWUSR,
		   show_target, store_target);


अटल काष्ठा attribute *balloon_attrs[] = अणु
	&dev_attr_target_kb.attr,
	&dev_attr_target.attr,
	&dev_attr_schedule_delay.attr.attr,
	&dev_attr_max_schedule_delay.attr.attr,
	&dev_attr_retry_count.attr.attr,
	&dev_attr_max_retry_count.attr.attr,
	&dev_attr_scrub_pages.attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group balloon_group = अणु
	.attrs = balloon_attrs
पूर्ण;

अटल काष्ठा attribute *balloon_info_attrs[] = अणु
	&dev_attr_current_kb.attr,
	&dev_attr_low_kb.attr,
	&dev_attr_high_kb.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group balloon_info_group = अणु
	.name = "info",
	.attrs = balloon_info_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *balloon_groups[] = अणु
	&balloon_group,
	&balloon_info_group,
	शून्य
पूर्ण;

अटल काष्ठा bus_type balloon_subsys = अणु
	.name = BALLOON_CLASS_NAME,
	.dev_name = BALLOON_CLASS_NAME,
पूर्ण;

अटल पूर्णांक रेजिस्टर_balloon(काष्ठा device *dev)
अणु
	पूर्णांक error;

	error = subsys_प्रणाली_रेजिस्टर(&balloon_subsys, शून्य);
	अगर (error)
		वापस error;

	dev->id = 0;
	dev->bus = &balloon_subsys;
	dev->groups = balloon_groups;

	error = device_रेजिस्टर(dev);
	अगर (error) अणु
		bus_unरेजिस्टर(&balloon_subsys);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण
