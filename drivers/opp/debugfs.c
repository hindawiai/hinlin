<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic OPP debugfs पूर्णांकerface
 *
 * Copyright (C) 2015-2016 Viresh Kumar <viresh.kumar@linaro.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/slab.h>

#समावेश "opp.h"

अटल काष्ठा dentry *rootdir;

अटल व्योम opp_set_dev_name(स्थिर काष्ठा device *dev, अक्षर *name)
अणु
	अगर (dev->parent)
		snम_लिखो(name, NAME_MAX, "%s-%s", dev_name(dev->parent),
			 dev_name(dev));
	अन्यथा
		snम_लिखो(name, NAME_MAX, "%s", dev_name(dev));
पूर्ण

व्योम opp_debug_हटाओ_one(काष्ठा dev_pm_opp *opp)
अणु
	debugfs_हटाओ_recursive(opp->dentry);
पूर्ण

अटल sमाप_प्रकार bw_name_पढ़ो(काष्ठा file *fp, अक्षर __user *userbuf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा icc_path *path = fp->निजी_data;
	अक्षर buf[64];
	पूर्णांक i;

	i = scnम_लिखो(buf, माप(buf), "%.62s\n", icc_get_name(path));

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, i);
पूर्ण

अटल स्थिर काष्ठा file_operations bw_name_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = bw_name_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम opp_debug_create_bw(काष्ठा dev_pm_opp *opp,
				काष्ठा opp_table *opp_table,
				काष्ठा dentry *pdentry)
अणु
	काष्ठा dentry *d;
	अक्षर name[11];
	पूर्णांक i;

	क्रम (i = 0; i < opp_table->path_count; i++) अणु
		snम_लिखो(name, माप(name), "icc-path-%.1d", i);

		/* Create per-path directory */
		d = debugfs_create_dir(name, pdentry);

		debugfs_create_file("name", S_IRUGO, d, opp_table->paths[i],
				    &bw_name_fops);
		debugfs_create_u32("peak_bw", S_IRUGO, d,
				   &opp->bandwidth[i].peak);
		debugfs_create_u32("avg_bw", S_IRUGO, d,
				   &opp->bandwidth[i].avg);
	पूर्ण
पूर्ण

अटल व्योम opp_debug_create_supplies(काष्ठा dev_pm_opp *opp,
				      काष्ठा opp_table *opp_table,
				      काष्ठा dentry *pdentry)
अणु
	काष्ठा dentry *d;
	पूर्णांक i;

	क्रम (i = 0; i < opp_table->regulator_count; i++) अणु
		अक्षर name[15];

		snम_लिखो(name, माप(name), "supply-%d", i);

		/* Create per-opp directory */
		d = debugfs_create_dir(name, pdentry);

		debugfs_create_uदीर्घ("u_volt_target", S_IRUGO, d,
				     &opp->supplies[i].u_volt);

		debugfs_create_uदीर्घ("u_volt_min", S_IRUGO, d,
				     &opp->supplies[i].u_volt_min);

		debugfs_create_uदीर्घ("u_volt_max", S_IRUGO, d,
				     &opp->supplies[i].u_volt_max);

		debugfs_create_uदीर्घ("u_amp", S_IRUGO, d,
				     &opp->supplies[i].u_amp);
	पूर्ण
पूर्ण

व्योम opp_debug_create_one(काष्ठा dev_pm_opp *opp, काष्ठा opp_table *opp_table)
अणु
	काष्ठा dentry *pdentry = opp_table->dentry;
	काष्ठा dentry *d;
	अचिन्हित दीर्घ id;
	अक्षर name[25];	/* 20 अक्षरs क्रम 64 bit value + 5 (opp:\0) */

	/*
	 * Get directory name क्रम OPP.
	 *
	 * - Normally rate is unique to each OPP, use it to get unique opp-name.
	 * - For some devices rate isn't available, use index instead.
	 */
	अगर (likely(opp->rate))
		id = opp->rate;
	अन्यथा
		id = _get_opp_count(opp_table);

	snम_लिखो(name, माप(name), "opp:%lu", id);

	/* Create per-opp directory */
	d = debugfs_create_dir(name, pdentry);

	debugfs_create_bool("available", S_IRUGO, d, &opp->available);
	debugfs_create_bool("dynamic", S_IRUGO, d, &opp->dynamic);
	debugfs_create_bool("turbo", S_IRUGO, d, &opp->turbo);
	debugfs_create_bool("suspend", S_IRUGO, d, &opp->suspend);
	debugfs_create_u32("performance_state", S_IRUGO, d, &opp->pstate);
	debugfs_create_uदीर्घ("rate_hz", S_IRUGO, d, &opp->rate);
	debugfs_create_uदीर्घ("clock_latency_ns", S_IRUGO, d,
			     &opp->घड़ी_latency_ns);

	opp_debug_create_supplies(opp, opp_table, d);
	opp_debug_create_bw(opp, opp_table, d);

	opp->dentry = d;
पूर्ण

अटल व्योम opp_list_debug_create_dir(काष्ठा opp_device *opp_dev,
				      काष्ठा opp_table *opp_table)
अणु
	स्थिर काष्ठा device *dev = opp_dev->dev;
	काष्ठा dentry *d;

	opp_set_dev_name(dev, opp_table->dentry_name);

	/* Create device specअगरic directory */
	d = debugfs_create_dir(opp_table->dentry_name, rootdir);

	opp_dev->dentry = d;
	opp_table->dentry = d;
पूर्ण

अटल व्योम opp_list_debug_create_link(काष्ठा opp_device *opp_dev,
				       काष्ठा opp_table *opp_table)
अणु
	अक्षर name[NAME_MAX];

	opp_set_dev_name(opp_dev->dev, name);

	/* Create device specअगरic directory link */
	opp_dev->dentry = debugfs_create_symlink(name, rootdir,
						 opp_table->dentry_name);
पूर्ण

/**
 * opp_debug_रेजिस्टर - add a device opp node to the debugfs 'opp' directory
 * @opp_dev: opp-dev poपूर्णांकer क्रम device
 * @opp_table: the device-opp being added
 *
 * Dynamically adds device specअगरic directory in debugfs 'opp' directory. If the
 * device-opp is shared with other devices, then links will be created क्रम all
 * devices except the first.
 */
व्योम opp_debug_रेजिस्टर(काष्ठा opp_device *opp_dev, काष्ठा opp_table *opp_table)
अणु
	अगर (opp_table->dentry)
		opp_list_debug_create_link(opp_dev, opp_table);
	अन्यथा
		opp_list_debug_create_dir(opp_dev, opp_table);
पूर्ण

अटल व्योम opp_migrate_dentry(काष्ठा opp_device *opp_dev,
			       काष्ठा opp_table *opp_table)
अणु
	काष्ठा opp_device *new_dev;
	स्थिर काष्ठा device *dev;
	काष्ठा dentry *dentry;

	/* Look क्रम next opp-dev */
	list_क्रम_each_entry(new_dev, &opp_table->dev_list, node)
		अगर (new_dev != opp_dev)
			अवरोध;

	/* new_dev is guaranteed to be valid here */
	dev = new_dev->dev;
	debugfs_हटाओ_recursive(new_dev->dentry);

	opp_set_dev_name(dev, opp_table->dentry_name);

	dentry = debugfs_नाम(rootdir, opp_dev->dentry, rootdir,
				opp_table->dentry_name);
	अगर (!dentry) अणु
		dev_err(dev, "%s: Failed to rename link from: %s to %s\n",
			__func__, dev_name(opp_dev->dev), dev_name(dev));
		वापस;
	पूर्ण

	new_dev->dentry = dentry;
	opp_table->dentry = dentry;
पूर्ण

/**
 * opp_debug_unरेजिस्टर - हटाओ a device opp node from debugfs opp directory
 * @opp_dev: opp-dev poपूर्णांकer क्रम device
 * @opp_table: the device-opp being हटाओd
 *
 * Dynamically हटाओs device specअगरic directory from debugfs 'opp' directory.
 */
व्योम opp_debug_unरेजिस्टर(काष्ठा opp_device *opp_dev,
			  काष्ठा opp_table *opp_table)
अणु
	अगर (opp_dev->dentry == opp_table->dentry) अणु
		/* Move the real dentry object under another device */
		अगर (!list_is_singular(&opp_table->dev_list)) अणु
			opp_migrate_dentry(opp_dev, opp_table);
			जाओ out;
		पूर्ण
		opp_table->dentry = शून्य;
	पूर्ण

	debugfs_हटाओ_recursive(opp_dev->dentry);

out:
	opp_dev->dentry = शून्य;
पूर्ण

अटल पूर्णांक __init opp_debug_init(व्योम)
अणु
	/* Create /sys/kernel/debug/opp directory */
	rootdir = debugfs_create_dir("opp", शून्य);

	वापस 0;
पूर्ण
core_initcall(opp_debug_init);
