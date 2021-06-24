<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, Linaro Limited, All rights reserved.
 * Author: Mike Leach <mike.leach@linaro.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>

#समावेश "coresight-priv.h"

/*
 * Connections group - links attribute.
 * Count of created links between coresight components in the group.
 */
अटल sमाप_प्रकार nr_links_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा coresight_device *csdev = to_coresight_device(dev);

	वापस प्र_लिखो(buf, "%d\n", csdev->nr_links);
पूर्ण
अटल DEVICE_ATTR_RO(nr_links);

अटल काष्ठा attribute *coresight_conns_attrs[] = अणु
	&dev_attr_nr_links.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group coresight_conns_group = अणु
	.attrs = coresight_conns_attrs,
	.name = "connections",
पूर्ण;

/*
 * Create connections group क्रम CoreSight devices.
 * This group will then be used to collate the sysfs links between
 * devices.
 */
पूर्णांक coresight_create_conns_sysfs_group(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक ret = 0;

	अगर (!csdev)
		वापस -EINVAL;

	ret = sysfs_create_group(&csdev->dev.kobj, &coresight_conns_group);
	अगर (ret)
		वापस ret;

	csdev->has_conns_grp = true;
	वापस ret;
पूर्ण

व्योम coresight_हटाओ_conns_sysfs_group(काष्ठा coresight_device *csdev)
अणु
	अगर (!csdev)
		वापस;

	अगर (csdev->has_conns_grp) अणु
		sysfs_हटाओ_group(&csdev->dev.kobj, &coresight_conns_group);
		csdev->has_conns_grp = false;
	पूर्ण
पूर्ण

पूर्णांक coresight_add_sysfs_link(काष्ठा coresight_sysfs_link *info)
अणु
	पूर्णांक ret = 0;

	अगर (!info)
		वापस -EINVAL;
	अगर (!info->orig || !info->target ||
	    !info->orig_name || !info->target_name)
		वापस -EINVAL;
	अगर (!info->orig->has_conns_grp || !info->target->has_conns_grp)
		वापस -EINVAL;

	/* first link orig->target */
	ret = sysfs_add_link_to_group(&info->orig->dev.kobj,
				      coresight_conns_group.name,
				      &info->target->dev.kobj,
				      info->orig_name);
	अगर (ret)
		वापस ret;

	/* second link target->orig */
	ret = sysfs_add_link_to_group(&info->target->dev.kobj,
				      coresight_conns_group.name,
				      &info->orig->dev.kobj,
				      info->target_name);

	/* error in second link - हटाओ first - otherwise inc counts */
	अगर (ret) अणु
		sysfs_हटाओ_link_from_group(&info->orig->dev.kobj,
					     coresight_conns_group.name,
					     info->orig_name);
	पूर्ण अन्यथा अणु
		info->orig->nr_links++;
		info->target->nr_links++;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_add_sysfs_link);

व्योम coresight_हटाओ_sysfs_link(काष्ठा coresight_sysfs_link *info)
अणु
	अगर (!info)
		वापस;
	अगर (!info->orig || !info->target ||
	    !info->orig_name || !info->target_name)
		वापस;

	sysfs_हटाओ_link_from_group(&info->orig->dev.kobj,
				     coresight_conns_group.name,
				     info->orig_name);

	sysfs_हटाओ_link_from_group(&info->target->dev.kobj,
				     coresight_conns_group.name,
				     info->target_name);

	info->orig->nr_links--;
	info->target->nr_links--;
पूर्ण
EXPORT_SYMBOL_GPL(coresight_हटाओ_sysfs_link);

/*
 * coresight_make_links: Make a link क्रम a connection from a @orig
 * device to @target, represented by @conn.
 *
 *   e.g, क्रम devOrig[output_X] -> devTarget[input_Y] is represented
 *   as two symbolic links :
 *
 *	/sys/.../devOrig/out:X	-> /sys/.../devTarget/
 *	/sys/.../devTarget/in:Y	-> /sys/.../devOrig/
 *
 * The link names are allocated क्रम a device where it appears. i.e, the
 * "out" link on the master and "in" link on the slave device.
 * The link info is stored in the connection record क्रम aव्योमing
 * the reस्थिरruction of names क्रम removal.
 */
पूर्णांक coresight_make_links(काष्ठा coresight_device *orig,
			 काष्ठा coresight_connection *conn,
			 काष्ठा coresight_device *target)
अणु
	पूर्णांक ret = -ENOMEM;
	अक्षर *outs = शून्य, *ins = शून्य;
	काष्ठा coresight_sysfs_link *link = शून्य;

	करो अणु
		outs = devm_kaप्र_लिखो(&orig->dev, GFP_KERNEL,
				      "out:%d", conn->outport);
		अगर (!outs)
			अवरोध;
		ins = devm_kaप्र_लिखो(&target->dev, GFP_KERNEL,
				     "in:%d", conn->child_port);
		अगर (!ins)
			अवरोध;
		link = devm_kzalloc(&orig->dev,
				    माप(काष्ठा coresight_sysfs_link),
				    GFP_KERNEL);
		अगर (!link)
			अवरोध;

		link->orig = orig;
		link->target = target;
		link->orig_name = outs;
		link->target_name = ins;

		ret = coresight_add_sysfs_link(link);
		अगर (ret)
			अवरोध;

		conn->link = link;

		/*
		 * Install the device connection. This also indicates that
		 * the links are operational on both ends.
		 */
		conn->child_dev = target;
		वापस 0;
	पूर्ण जबतक (0);

	वापस ret;
पूर्ण

/*
 * coresight_हटाओ_links: Remove the sysfs links क्रम a given connection @conn,
 * from @orig device to @target device. See coresight_make_links() क्रम more
 * details.
 */
व्योम coresight_हटाओ_links(काष्ठा coresight_device *orig,
			    काष्ठा coresight_connection *conn)
अणु
	अगर (!orig || !conn->link)
		वापस;

	coresight_हटाओ_sysfs_link(conn->link);

	devm_kमुक्त(&conn->child_dev->dev, conn->link->target_name);
	devm_kमुक्त(&orig->dev, conn->link->orig_name);
	devm_kमुक्त(&orig->dev, conn->link);
	conn->link = शून्य;
	conn->child_dev = शून्य;
पूर्ण
