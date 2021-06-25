<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm Technologies HIDMA Management SYS पूर्णांकerface
 *
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/sysfs.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "hidma_mgmt.h"

काष्ठा hidma_chan_attr अणु
	काष्ठा hidma_mgmt_dev *mdev;
	पूर्णांक index;
	काष्ठा kobj_attribute attr;
पूर्ण;

काष्ठा hidma_mgmt_fileinfo अणु
	अक्षर *name;
	पूर्णांक mode;
	पूर्णांक (*get)(काष्ठा hidma_mgmt_dev *mdev);
	पूर्णांक (*set)(काष्ठा hidma_mgmt_dev *mdev, u64 val);
पूर्ण;

#घोषणा IMPLEMENT_GETSET(name)					\
अटल पूर्णांक get_##name(काष्ठा hidma_mgmt_dev *mdev)		\
अणु								\
	वापस mdev->name;					\
पूर्ण								\
अटल पूर्णांक set_##name(काष्ठा hidma_mgmt_dev *mdev, u64 val)	\
अणु								\
	u64 पंचांगp;						\
	पूर्णांक rc;							\
								\
	पंचांगp = mdev->name;					\
	mdev->name = val;					\
	rc = hidma_mgmt_setup(mdev);				\
	अगर (rc)							\
		mdev->name = पंचांगp;				\
	वापस rc;						\
पूर्ण

#घोषणा DECLARE_ATTRIBUTE(name, mode)				\
	अणु#name, mode, get_##name, set_##nameपूर्ण

IMPLEMENT_GETSET(hw_version_major)
IMPLEMENT_GETSET(hw_version_minor)
IMPLEMENT_GETSET(max_wr_xactions)
IMPLEMENT_GETSET(max_rd_xactions)
IMPLEMENT_GETSET(max_ग_लिखो_request)
IMPLEMENT_GETSET(max_पढ़ो_request)
IMPLEMENT_GETSET(dma_channels)
IMPLEMENT_GETSET(chreset_समयout_cycles)

अटल पूर्णांक set_priority(काष्ठा hidma_mgmt_dev *mdev, अचिन्हित पूर्णांक i, u64 val)
अणु
	u64 पंचांगp;
	पूर्णांक rc;

	अगर (i >= mdev->dma_channels)
		वापस -EINVAL;

	पंचांगp = mdev->priority[i];
	mdev->priority[i] = val;
	rc = hidma_mgmt_setup(mdev);
	अगर (rc)
		mdev->priority[i] = पंचांगp;
	वापस rc;
पूर्ण

अटल पूर्णांक set_weight(काष्ठा hidma_mgmt_dev *mdev, अचिन्हित पूर्णांक i, u64 val)
अणु
	u64 पंचांगp;
	पूर्णांक rc;

	अगर (i >= mdev->dma_channels)
		वापस -EINVAL;

	पंचांगp = mdev->weight[i];
	mdev->weight[i] = val;
	rc = hidma_mgmt_setup(mdev);
	अगर (rc)
		mdev->weight[i] = पंचांगp;
	वापस rc;
पूर्ण

अटल काष्ठा hidma_mgmt_fileinfo hidma_mgmt_files[] = अणु
	DECLARE_ATTRIBUTE(hw_version_major, S_IRUGO),
	DECLARE_ATTRIBUTE(hw_version_minor, S_IRUGO),
	DECLARE_ATTRIBUTE(dma_channels, S_IRUGO),
	DECLARE_ATTRIBUTE(chreset_समयout_cycles, S_IRUGO),
	DECLARE_ATTRIBUTE(max_wr_xactions, S_IRUGO),
	DECLARE_ATTRIBUTE(max_rd_xactions, S_IRUGO),
	DECLARE_ATTRIBUTE(max_ग_लिखो_request, S_IRUGO),
	DECLARE_ATTRIBUTE(max_पढ़ो_request, S_IRUGO),
पूर्ण;

अटल sमाप_प्रकार show_values(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा hidma_mgmt_dev *mdev = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	buf[0] = 0;

	क्रम (i = 0; i < ARRAY_SIZE(hidma_mgmt_files); i++) अणु
		अगर (म_भेद(attr->attr.name, hidma_mgmt_files[i].name) == 0) अणु
			प्र_लिखो(buf, "%d\n", hidma_mgmt_files[i].get(mdev));
			अवरोध;
		पूर्ण
	पूर्ण
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार set_values(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hidma_mgmt_dev *mdev = dev_get_drvdata(dev);
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 0, &पंचांगp);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < ARRAY_SIZE(hidma_mgmt_files); i++) अणु
		अगर (म_भेद(attr->attr.name, hidma_mgmt_files[i].name) == 0) अणु
			rc = hidma_mgmt_files[i].set(mdev, पंचांगp);
			अगर (rc)
				वापस rc;

			अवरोध;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_values_channel(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hidma_chan_attr *chattr;
	काष्ठा hidma_mgmt_dev *mdev;

	buf[0] = 0;
	chattr = container_of(attr, काष्ठा hidma_chan_attr, attr);
	mdev = chattr->mdev;
	अगर (म_भेद(attr->attr.name, "priority") == 0)
		प्र_लिखो(buf, "%d\n", mdev->priority[chattr->index]);
	अन्यथा अगर (म_भेद(attr->attr.name, "weight") == 0)
		प्र_लिखो(buf, "%d\n", mdev->weight[chattr->index]);

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार set_values_channel(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	काष्ठा hidma_chan_attr *chattr;
	काष्ठा hidma_mgmt_dev *mdev;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक rc;

	chattr = container_of(attr, काष्ठा hidma_chan_attr, attr);
	mdev = chattr->mdev;

	rc = kम_से_अदीर्घ(buf, 0, &पंचांगp);
	अगर (rc)
		वापस rc;

	अगर (म_भेद(attr->attr.name, "priority") == 0) अणु
		rc = set_priority(mdev, chattr->index, पंचांगp);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अगर (म_भेद(attr->attr.name, "weight") == 0) अणु
		rc = set_weight(mdev, chattr->index, पंचांगp);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक create_sysfs_entry(काष्ठा hidma_mgmt_dev *dev, अक्षर *name, पूर्णांक mode)
अणु
	काष्ठा device_attribute *attrs;
	अक्षर *name_copy;

	attrs = devm_kदो_स्मृति(&dev->pdev->dev,
			     माप(काष्ठा device_attribute), GFP_KERNEL);
	अगर (!attrs)
		वापस -ENOMEM;

	name_copy = devm_kstrdup(&dev->pdev->dev, name, GFP_KERNEL);
	अगर (!name_copy)
		वापस -ENOMEM;

	attrs->attr.name = name_copy;
	attrs->attr.mode = mode;
	attrs->show = show_values;
	attrs->store = set_values;
	sysfs_attr_init(&attrs->attr);

	वापस device_create_file(&dev->pdev->dev, attrs);
पूर्ण

अटल पूर्णांक create_sysfs_entry_channel(काष्ठा hidma_mgmt_dev *mdev, अक्षर *name,
				      पूर्णांक mode, पूर्णांक index,
				      काष्ठा kobject *parent)
अणु
	काष्ठा hidma_chan_attr *chattr;
	अक्षर *name_copy;

	chattr = devm_kदो_स्मृति(&mdev->pdev->dev, माप(*chattr), GFP_KERNEL);
	अगर (!chattr)
		वापस -ENOMEM;

	name_copy = devm_kstrdup(&mdev->pdev->dev, name, GFP_KERNEL);
	अगर (!name_copy)
		वापस -ENOMEM;

	chattr->mdev = mdev;
	chattr->index = index;
	chattr->attr.attr.name = name_copy;
	chattr->attr.attr.mode = mode;
	chattr->attr.show = show_values_channel;
	chattr->attr.store = set_values_channel;
	sysfs_attr_init(&chattr->attr.attr);

	वापस sysfs_create_file(parent, &chattr->attr.attr);
पूर्ण

पूर्णांक hidma_mgmt_init_sys(काष्ठा hidma_mgmt_dev *mdev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;
	पूर्णांक required;
	काष्ठा kobject *chanops;

	required = माप(*mdev->chroots) * mdev->dma_channels;
	mdev->chroots = devm_kदो_स्मृति(&mdev->pdev->dev, required, GFP_KERNEL);
	अगर (!mdev->chroots)
		वापस -ENOMEM;

	chanops = kobject_create_and_add("chanops", &mdev->pdev->dev.kobj);
	अगर (!chanops)
		वापस -ENOMEM;

	/* create each channel directory here */
	क्रम (i = 0; i < mdev->dma_channels; i++) अणु
		अक्षर name[20];

		snम_लिखो(name, माप(name), "chan%d", i);
		mdev->chroots[i] = kobject_create_and_add(name, chanops);
		अगर (!mdev->chroots[i])
			वापस -ENOMEM;
	पूर्ण

	/* populate common parameters */
	क्रम (i = 0; i < ARRAY_SIZE(hidma_mgmt_files); i++) अणु
		rc = create_sysfs_entry(mdev, hidma_mgmt_files[i].name,
					hidma_mgmt_files[i].mode);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* populate parameters that are per channel */
	क्रम (i = 0; i < mdev->dma_channels; i++) अणु
		rc = create_sysfs_entry_channel(mdev, "priority",
						(S_IRUGO | S_IWUGO), i,
						mdev->chroots[i]);
		अगर (rc)
			वापस rc;

		rc = create_sysfs_entry_channel(mdev, "weight",
						(S_IRUGO | S_IWUGO), i,
						mdev->chroots[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hidma_mgmt_init_sys);
