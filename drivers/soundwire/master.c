<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2019-2020 Intel Corporation.

#समावेश <linux/device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश "bus.h"

/*
 * The 3s value क्रम स्वतःsuspend will only be used अगर there are no
 * devices physically attached on a bus segment. In practice enabling
 * the bus operation will result in children devices become active and
 * the master device will only suspend when all its children are no
 * दीर्घer active.
 */
#घोषणा SDW_MASTER_SUSPEND_DELAY_MS 3000

/*
 * The sysfs क्रम properties reflects the MIPI description as given
 * in the MIPI DisCo spec
 *
 * Base file is:
 *	sdw-master-N
 *      |---- revision
 *      |---- clk_stop_modes
 *      |---- max_clk_freq
 *      |---- clk_freq
 *      |---- clk_gears
 *      |---- शेष_row
 *      |---- शेष_col
 *      |---- dynamic_shape
 *      |---- err_threshold
 */

#घोषणा sdw_master_attr(field, क्रमmat_string)				\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा sdw_master_device *md = dev_to_sdw_master_device(dev);	\
	वापस प्र_लिखो(buf, क्रमmat_string, md->bus->prop.field);	\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

sdw_master_attr(revision, "0x%x\n");
sdw_master_attr(clk_stop_modes, "0x%x\n");
sdw_master_attr(max_clk_freq, "%d\n");
sdw_master_attr(शेष_row, "%d\n");
sdw_master_attr(शेष_col, "%d\n");
sdw_master_attr(शेष_frame_rate, "%d\n");
sdw_master_attr(dynamic_frame, "%d\n");
sdw_master_attr(err_threshold, "%d\n");

अटल sमाप_प्रकार घड़ी_frequencies_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sdw_master_device *md = dev_to_sdw_master_device(dev);
	sमाप_प्रकार size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < md->bus->prop.num_clk_freq; i++)
		size += प्र_लिखो(buf + size, "%8d ",
				md->bus->prop.clk_freq[i]);
	size += प्र_लिखो(buf + size, "\n");

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RO(घड़ी_frequencies);

अटल sमाप_प्रकार घड़ी_gears_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sdw_master_device *md = dev_to_sdw_master_device(dev);
	sमाप_प्रकार size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < md->bus->prop.num_clk_gears; i++)
		size += प्र_लिखो(buf + size, "%8d ",
				md->bus->prop.clk_gears[i]);
	size += प्र_लिखो(buf + size, "\n");

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RO(घड़ी_gears);

अटल काष्ठा attribute *master_node_attrs[] = अणु
	&dev_attr_revision.attr,
	&dev_attr_clk_stop_modes.attr,
	&dev_attr_max_clk_freq.attr,
	&dev_attr_शेष_row.attr,
	&dev_attr_शेष_col.attr,
	&dev_attr_शेष_frame_rate.attr,
	&dev_attr_dynamic_frame.attr,
	&dev_attr_err_threshold.attr,
	&dev_attr_घड़ी_frequencies.attr,
	&dev_attr_घड़ी_gears.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(master_node);

अटल व्योम sdw_master_device_release(काष्ठा device *dev)
अणु
	काष्ठा sdw_master_device *md = dev_to_sdw_master_device(dev);

	kमुक्त(md);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops master_dev_pm = अणु
	SET_RUNTIME_PM_OPS(pm_generic_runसमय_suspend,
			   pm_generic_runसमय_resume, शून्य)
पूर्ण;

काष्ठा device_type sdw_master_type = अणु
	.name =		"soundwire_master",
	.release =	sdw_master_device_release,
	.pm = &master_dev_pm,
पूर्ण;

/**
 * sdw_master_device_add() - create a Linux Master Device representation.
 * @bus: SDW bus instance
 * @parent: parent device
 * @fwnode: firmware node handle
 */
पूर्णांक sdw_master_device_add(काष्ठा sdw_bus *bus, काष्ठा device *parent,
			  काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा sdw_master_device *md;
	पूर्णांक ret;

	अगर (!parent)
		वापस -EINVAL;

	md = kzalloc(माप(*md), GFP_KERNEL);
	अगर (!md)
		वापस -ENOMEM;

	md->dev.bus = &sdw_bus_type;
	md->dev.type = &sdw_master_type;
	md->dev.parent = parent;
	md->dev.groups = master_node_groups;
	md->dev.of_node = parent->of_node;
	md->dev.fwnode = fwnode;
	md->dev.dma_mask = parent->dma_mask;

	dev_set_name(&md->dev, "sdw-master-%d", bus->id);

	ret = device_रेजिस्टर(&md->dev);
	अगर (ret) अणु
		dev_err(parent, "Failed to add master: ret %d\n", ret);
		/*
		 * On err, करोn't मुक्त but drop ref as this will be मुक्तd
		 * when release method is invoked.
		 */
		put_device(&md->dev);
		जाओ device_रेजिस्टर_err;
	पूर्ण

	/* add लघुcuts to improve code पढ़ोability/compactness */
	md->bus = bus;
	bus->dev = &md->dev;
	bus->md = md;

	pm_runसमय_set_स्वतःsuspend_delay(&bus->md->dev, SDW_MASTER_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&bus->md->dev);
	pm_runसमय_mark_last_busy(&bus->md->dev);
	pm_runसमय_set_active(&bus->md->dev);
	pm_runसमय_enable(&bus->md->dev);
	pm_runसमय_idle(&bus->md->dev);
device_रेजिस्टर_err:
	वापस ret;
पूर्ण

/**
 * sdw_master_device_del() - delete a Linux Master Device representation.
 * @bus: bus handle
 *
 * This function is the dual of sdw_master_device_add()
 */
पूर्णांक sdw_master_device_del(काष्ठा sdw_bus *bus)
अणु
	pm_runसमय_disable(&bus->md->dev);
	device_unरेजिस्टर(bus->dev);

	वापस 0;
पूर्ण
