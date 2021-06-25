<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Platक्रमm Monitoring Technology Crashlog driver
 *
 * Copyright (c) 2020, Intel Corporation.
 * All Rights Reserved.
 *
 * Author: "Alexander Duyck" <alexander.h.duyck@linux.पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/overflow.h>

#समावेश "intel_pmt_class.h"

#घोषणा DRV_NAME		"pmt_crashlog"

/* Crashlog discovery header types */
#घोषणा CRASH_TYPE_OOBMSM	1

/* Control Flags */
#घोषणा CRASHLOG_FLAG_DISABLE		BIT(28)

/*
 * Bits 29 and 30 control the state of bit 31.
 *
 * Bit 29 will clear bit 31, अगर set, allowing a new crashlog to be captured.
 * Bit 30 will immediately trigger a crashlog to be generated, setting bit 31.
 * Bit 31 is the पढ़ो-only status with a 1 indicating log is complete.
 */
#घोषणा CRASHLOG_FLAG_TRIGGER_CLEAR	BIT(29)
#घोषणा CRASHLOG_FLAG_TRIGGER_EXECUTE	BIT(30)
#घोषणा CRASHLOG_FLAG_TRIGGER_COMPLETE	BIT(31)
#घोषणा CRASHLOG_FLAG_TRIGGER_MASK	GENMASK(31, 28)

/* Crashlog Discovery Header */
#घोषणा CONTROL_OFFSET		0x0
#घोषणा GUID_OFFSET		0x4
#घोषणा BASE_OFFSET		0x8
#घोषणा SIZE_OFFSET		0xC
#घोषणा GET_ACCESS(v)		((v) & GENMASK(3, 0))
#घोषणा GET_TYPE(v)		(((v) & GENMASK(7, 4)) >> 4)
#घोषणा GET_VERSION(v)		(((v) & GENMASK(19, 16)) >> 16)
/* size is in bytes */
#घोषणा GET_SIZE(v)		((v) * माप(u32))

काष्ठा crashlog_entry अणु
	/* entry must be first member of काष्ठा */
	काष्ठा पूर्णांकel_pmt_entry		entry;
	काष्ठा mutex			control_mutex;
पूर्ण;

काष्ठा pmt_crashlog_priv अणु
	पूर्णांक			num_entries;
	काष्ठा crashlog_entry	entry[];
पूर्ण;

/*
 * I/O
 */
अटल bool pmt_crashlog_complete(काष्ठा पूर्णांकel_pmt_entry *entry)
अणु
	u32 control = पढ़ोl(entry->disc_table + CONTROL_OFFSET);

	/* वापस current value of the crashlog complete flag */
	वापस !!(control & CRASHLOG_FLAG_TRIGGER_COMPLETE);
पूर्ण

अटल bool pmt_crashlog_disabled(काष्ठा पूर्णांकel_pmt_entry *entry)
अणु
	u32 control = पढ़ोl(entry->disc_table + CONTROL_OFFSET);

	/* वापस current value of the crashlog disabled flag */
	वापस !!(control & CRASHLOG_FLAG_DISABLE);
पूर्ण

अटल bool pmt_crashlog_supported(काष्ठा पूर्णांकel_pmt_entry *entry)
अणु
	u32 discovery_header = पढ़ोl(entry->disc_table + CONTROL_OFFSET);
	u32 crash_type, version;

	crash_type = GET_TYPE(discovery_header);
	version = GET_VERSION(discovery_header);

	/*
	 * Currently we only recognize OOBMSM version 0 devices.
	 * We can ignore all other crashlog devices in the प्रणाली.
	 */
	वापस crash_type == CRASH_TYPE_OOBMSM && version == 0;
पूर्ण

अटल व्योम pmt_crashlog_set_disable(काष्ठा पूर्णांकel_pmt_entry *entry,
				     bool disable)
अणु
	u32 control = पढ़ोl(entry->disc_table + CONTROL_OFFSET);

	/* clear trigger bits so we are only modअगरying disable flag */
	control &= ~CRASHLOG_FLAG_TRIGGER_MASK;

	अगर (disable)
		control |= CRASHLOG_FLAG_DISABLE;
	अन्यथा
		control &= ~CRASHLOG_FLAG_DISABLE;

	ग_लिखोl(control, entry->disc_table + CONTROL_OFFSET);
पूर्ण

अटल व्योम pmt_crashlog_set_clear(काष्ठा पूर्णांकel_pmt_entry *entry)
अणु
	u32 control = पढ़ोl(entry->disc_table + CONTROL_OFFSET);

	control &= ~CRASHLOG_FLAG_TRIGGER_MASK;
	control |= CRASHLOG_FLAG_TRIGGER_CLEAR;

	ग_लिखोl(control, entry->disc_table + CONTROL_OFFSET);
पूर्ण

अटल व्योम pmt_crashlog_set_execute(काष्ठा पूर्णांकel_pmt_entry *entry)
अणु
	u32 control = पढ़ोl(entry->disc_table + CONTROL_OFFSET);

	control &= ~CRASHLOG_FLAG_TRIGGER_MASK;
	control |= CRASHLOG_FLAG_TRIGGER_EXECUTE;

	ग_लिखोl(control, entry->disc_table + CONTROL_OFFSET);
पूर्ण

/*
 * sysfs
 */
अटल sमाप_प्रकार
enable_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_pmt_entry *entry = dev_get_drvdata(dev);
	पूर्णांक enabled = !pmt_crashlog_disabled(entry);

	वापस प्र_लिखो(buf, "%d\n", enabled);
पूर्ण

अटल sमाप_प्रकार
enable_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा crashlog_entry *entry;
	bool enabled;
	पूर्णांक result;

	entry = dev_get_drvdata(dev);

	result = kstrtobool(buf, &enabled);
	अगर (result)
		वापस result;

	mutex_lock(&entry->control_mutex);
	pmt_crashlog_set_disable(&entry->entry, !enabled);
	mutex_unlock(&entry->control_mutex);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(enable);

अटल sमाप_प्रकार
trigger_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_pmt_entry *entry;
	पूर्णांक trigger;

	entry = dev_get_drvdata(dev);
	trigger = pmt_crashlog_complete(entry);

	वापस प्र_लिखो(buf, "%d\n", trigger);
पूर्ण

अटल sमाप_प्रकार
trigger_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा crashlog_entry *entry;
	bool trigger;
	पूर्णांक result;

	entry = dev_get_drvdata(dev);

	result = kstrtobool(buf, &trigger);
	अगर (result)
		वापस result;

	mutex_lock(&entry->control_mutex);

	अगर (!trigger) अणु
		pmt_crashlog_set_clear(&entry->entry);
	पूर्ण अन्यथा अगर (pmt_crashlog_complete(&entry->entry)) अणु
		/* we cannot trigger a new crash अगर one is still pending */
		result = -EEXIST;
		जाओ err;
	पूर्ण अन्यथा अगर (pmt_crashlog_disabled(&entry->entry)) अणु
		/* अगर device is currently disabled, वापस busy */
		result = -EBUSY;
		जाओ err;
	पूर्ण अन्यथा अणु
		pmt_crashlog_set_execute(&entry->entry);
	पूर्ण

	result = count;
err:
	mutex_unlock(&entry->control_mutex);
	वापस result;
पूर्ण
अटल DEVICE_ATTR_RW(trigger);

अटल काष्ठा attribute *pmt_crashlog_attrs[] = अणु
	&dev_attr_enable.attr,
	&dev_attr_trigger.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group pmt_crashlog_group = अणु
	.attrs	= pmt_crashlog_attrs,
पूर्ण;

अटल पूर्णांक pmt_crashlog_header_decode(काष्ठा पूर्णांकel_pmt_entry *entry,
				      काष्ठा पूर्णांकel_pmt_header *header,
				      काष्ठा device *dev)
अणु
	व्योम __iomem *disc_table = entry->disc_table;
	काष्ठा crashlog_entry *crashlog;

	अगर (!pmt_crashlog_supported(entry))
		वापस 1;

	/* initialize control mutex */
	crashlog = container_of(entry, काष्ठा crashlog_entry, entry);
	mutex_init(&crashlog->control_mutex);

	header->access_type = GET_ACCESS(पढ़ोl(disc_table));
	header->guid = पढ़ोl(disc_table + GUID_OFFSET);
	header->base_offset = पढ़ोl(disc_table + BASE_OFFSET);

	/* Size is measured in DWORDS, but accessor वापसs bytes */
	header->size = GET_SIZE(पढ़ोl(disc_table + SIZE_OFFSET));

	वापस 0;
पूर्ण

अटल DEFINE_XARRAY_ALLOC(crashlog_array);
अटल काष्ठा पूर्णांकel_pmt_namespace pmt_crashlog_ns = अणु
	.name = "crashlog",
	.xa = &crashlog_array,
	.attr_grp = &pmt_crashlog_group,
	.pmt_header_decode = pmt_crashlog_header_decode,
पूर्ण;

/*
 * initialization
 */
अटल पूर्णांक pmt_crashlog_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmt_crashlog_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_entries; i++)
		पूर्णांकel_pmt_dev_destroy(&priv->entry[i].entry, &pmt_crashlog_ns);

	वापस 0;
पूर्ण

अटल पूर्णांक pmt_crashlog_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmt_crashlog_priv *priv;
	माप_प्रकार size;
	पूर्णांक i, ret;

	size = काष्ठा_size(priv, entry, pdev->num_resources);
	priv = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	क्रम (i = 0; i < pdev->num_resources; i++) अणु
		काष्ठा पूर्णांकel_pmt_entry *entry = &priv->entry[i].entry;

		ret = पूर्णांकel_pmt_dev_create(entry, &pmt_crashlog_ns, pdev, i);
		अगर (ret < 0)
			जाओ पात_probe;
		अगर (ret)
			जारी;

		priv->num_entries++;
	पूर्ण

	वापस 0;
पात_probe:
	pmt_crashlog_हटाओ(pdev);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver pmt_crashlog_driver = अणु
	.driver = अणु
		.name   = DRV_NAME,
	पूर्ण,
	.हटाओ = pmt_crashlog_हटाओ,
	.probe  = pmt_crashlog_probe,
पूर्ण;

अटल पूर्णांक __init pmt_crashlog_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pmt_crashlog_driver);
पूर्ण

अटल व्योम __निकास pmt_crashlog_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pmt_crashlog_driver);
	xa_destroy(&crashlog_array);
पूर्ण

module_init(pmt_crashlog_init);
module_निकास(pmt_crashlog_निकास);

MODULE_AUTHOR("Alexander Duyck <alexander.h.duyck@linux.intel.com>");
MODULE_DESCRIPTION("Intel PMT Crashlog driver");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_LICENSE("GPL v2");
