<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_ROCCAT_COMMON_H
#घोषणा __HID_ROCCAT_COMMON_H

/*
 * Copyright (c) 2011 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/usb.h>
#समावेश <linux/types.h>

क्रमागत roccat_common2_commands अणु
	ROCCAT_COMMON_COMMAND_CONTROL = 0x4,
पूर्ण;

काष्ठा roccat_common2_control अणु
	uपूर्णांक8_t command;
	uपूर्णांक8_t value;
	uपूर्णांक8_t request; /* always 0 on requesting ग_लिखो check */
पूर्ण __packed;

पूर्णांक roccat_common2_receive(काष्ठा usb_device *usb_dev, uपूर्णांक report_id,
		व्योम *data, uपूर्णांक size);
पूर्णांक roccat_common2_send(काष्ठा usb_device *usb_dev, uपूर्णांक report_id,
		व्योम स्थिर *data, uपूर्णांक size);
पूर्णांक roccat_common2_send_with_status(काष्ठा usb_device *usb_dev,
		uपूर्णांक command, व्योम स्थिर *buf, uपूर्णांक size);

काष्ठा roccat_common2_device अणु
	पूर्णांक roccat_claimed;
	पूर्णांक chrdev_minor;
	काष्ठा mutex lock;
पूर्ण;

पूर्णांक roccat_common2_device_init_काष्ठा(काष्ठा usb_device *usb_dev,
		काष्ठा roccat_common2_device *dev);
sमाप_प्रकार roccat_common2_sysfs_पढ़ो(काष्ठा file *fp, काष्ठा kobject *kobj,
		अक्षर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command);
sमाप_प्रकार roccat_common2_sysfs_ग_लिखो(काष्ठा file *fp, काष्ठा kobject *kobj,
		व्योम स्थिर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command);

#घोषणा ROCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE) \
अटल sमाप_प्रकार roccat_common2_sysfs_ग_लिखो_ ## thingy(काष्ठा file *fp, \
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf, \
		loff_t off, माप_प्रकार count) \
अणु \
	वापस roccat_common2_sysfs_ग_लिखो(fp, kobj, buf, off, count, \
			SIZE, COMMAND); \
पूर्ण

#घोषणा ROCCAT_COMMON2_SYSFS_R(thingy, COMMAND, SIZE) \
अटल sमाप_प्रकार roccat_common2_sysfs_पढ़ो_ ## thingy(काष्ठा file *fp, \
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf, \
		loff_t off, माप_प्रकार count) \
अणु \
	वापस roccat_common2_sysfs_पढ़ो(fp, kobj, buf, off, count, \
			SIZE, COMMAND); \
पूर्ण

#घोषणा ROCCAT_COMMON2_SYSFS_RW(thingy, COMMAND, SIZE) \
ROCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE) \
ROCCAT_COMMON2_SYSFS_R(thingy, COMMAND, SIZE)

#घोषणा ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(thingy, COMMAND, SIZE) \
ROCCAT_COMMON2_SYSFS_RW(thingy, COMMAND, SIZE); \
अटल काष्ठा bin_attribute bin_attr_ ## thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0660 पूर्ण, \
	.size = SIZE, \
	.पढ़ो = roccat_common2_sysfs_पढ़ो_ ## thingy, \
	.ग_लिखो = roccat_common2_sysfs_ग_लिखो_ ## thingy \
पूर्ण

#घोषणा ROCCAT_COMMON2_BIN_ATTRIBUTE_R(thingy, COMMAND, SIZE) \
ROCCAT_COMMON2_SYSFS_R(thingy, COMMAND, SIZE); \
अटल काष्ठा bin_attribute bin_attr_ ## thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0440 पूर्ण, \
	.size = SIZE, \
	.पढ़ो = roccat_common2_sysfs_पढ़ो_ ## thingy, \
पूर्ण

#घोषणा ROCCAT_COMMON2_BIN_ATTRIBUTE_W(thingy, COMMAND, SIZE) \
ROCCAT_COMMON2_SYSFS_W(thingy, COMMAND, SIZE); \
अटल काष्ठा bin_attribute bin_attr_ ## thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0220 पूर्ण, \
	.size = SIZE, \
	.ग_लिखो = roccat_common2_sysfs_ग_लिखो_ ## thingy \
पूर्ण

#पूर्ण_अगर
