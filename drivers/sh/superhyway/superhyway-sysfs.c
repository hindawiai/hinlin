<शैली गुरु>
/*
 * drivers/sh/superhyway/superhyway-sysfs.c
 *
 * SuperHyway Bus sysfs पूर्णांकerface
 *
 * Copyright (C) 2004, 2005  Paul Mundt <lethal@linux-sh.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/superhyway.h>

#घोषणा superhyway_ro_attr(name, fmt, field)				\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा superhyway_device *s = to_superhyway_device(dev);	\
	वापस प्र_लिखो(buf, fmt, s->field);				\
पूर्ण									\
अटल DEVICE_ATTR_RO(name);

/* VCR flags */
superhyway_ro_attr(perr_flags, "0x%02x\n", vcr.perr_flags);
superhyway_ro_attr(merr_flags, "0x%02x\n", vcr.merr_flags);
superhyway_ro_attr(mod_vers, "0x%04x\n", vcr.mod_vers);
superhyway_ro_attr(mod_id, "0x%04x\n", vcr.mod_id);
superhyway_ro_attr(bot_mb, "0x%02x\n", vcr.bot_mb);
superhyway_ro_attr(top_mb, "0x%02x\n", vcr.top_mb);

/* Misc */
superhyway_ro_attr(resource, "0x%08lx\n", resource[0].start);

अटल काष्ठा attribute *superhyway_dev_attrs[] = अणु
	&dev_attr_perr_flags.attr,
	&dev_attr_merr_flags.attr,
	&dev_attr_mod_vers.attr,
	&dev_attr_mod_id.attr,
	&dev_attr_bot_mb.attr,
	&dev_attr_top_mb.attr,
	&dev_attr_resource.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group superhyway_dev_group = अणु
	.attrs = superhyway_dev_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *superhyway_dev_groups[] = अणु
	&superhyway_dev_group,
	शून्य,
पूर्ण;
