<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * processor thermal device mailbox driver क्रम Workload type hपूर्णांकs
 * Copyright (c) 2020, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "processor_thermal_device.h"

#घोषणा MBOX_CMD_WORKLOAD_TYPE_READ	0x0E
#घोषणा MBOX_CMD_WORKLOAD_TYPE_WRITE	0x0F

#घोषणा MBOX_OFFSET_DATA		0x5810
#घोषणा MBOX_OFFSET_INTERFACE		0x5818

#घोषणा MBOX_BUSY_BIT			31
#घोषणा MBOX_RETRY_COUNT		100

#घोषणा MBOX_DATA_BIT_VALID		31
#घोषणा MBOX_DATA_BIT_AC_DC		30

अटल DEFINE_MUTEX(mbox_lock);

अटल पूर्णांक send_mbox_cmd(काष्ठा pci_dev *pdev, u8 cmd_id, u32 cmd_data, u8 *cmd_resp)
अणु
	काष्ठा proc_thermal_device *proc_priv;
	u32 retries, data;
	पूर्णांक ret;

	mutex_lock(&mbox_lock);
	proc_priv = pci_get_drvdata(pdev);

	/* Poll क्रम rb bit == 0 */
	retries = MBOX_RETRY_COUNT;
	करो अणु
		data = पढ़ोl((व्योम __iomem *) (proc_priv->mmio_base + MBOX_OFFSET_INTERFACE));
		अगर (data & BIT_ULL(MBOX_BUSY_BIT)) अणु
			ret = -EBUSY;
			जारी;
		पूर्ण
		ret = 0;
		अवरोध;
	पूर्ण जबतक (--retries);

	अगर (ret)
		जाओ unlock_mbox;

	अगर (cmd_id == MBOX_CMD_WORKLOAD_TYPE_WRITE)
		ग_लिखोl(cmd_data, (व्योम __iomem *) ((proc_priv->mmio_base + MBOX_OFFSET_DATA)));

	/* Write command रेजिस्टर */
	data = BIT_ULL(MBOX_BUSY_BIT) | cmd_id;
	ग_लिखोl(data, (व्योम __iomem *) ((proc_priv->mmio_base + MBOX_OFFSET_INTERFACE)));

	/* Poll क्रम rb bit == 0 */
	retries = MBOX_RETRY_COUNT;
	करो अणु
		data = पढ़ोl((व्योम __iomem *) (proc_priv->mmio_base + MBOX_OFFSET_INTERFACE));
		अगर (data & BIT_ULL(MBOX_BUSY_BIT)) अणु
			ret = -EBUSY;
			जारी;
		पूर्ण

		अगर (data) अणु
			ret = -ENXIO;
			जाओ unlock_mbox;
		पूर्ण

		अगर (cmd_id == MBOX_CMD_WORKLOAD_TYPE_READ) अणु
			data = पढ़ोl((व्योम __iomem *) (proc_priv->mmio_base + MBOX_OFFSET_DATA));
			*cmd_resp = data & 0xff;
		पूर्ण

		ret = 0;
		अवरोध;
	पूर्ण जबतक (--retries);

unlock_mbox:
	mutex_unlock(&mbox_lock);
	वापस ret;
पूर्ण

/* List of workload types */
अटल स्थिर अक्षर * स्थिर workload_types[] = अणु
	"none",
	"idle",
	"semi_active",
	"bursty",
	"sustained",
	"battery_life",
	शून्य
पूर्ण;


अटल sमाप_प्रकार workload_available_types_show(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	पूर्णांक i = 0;
	पूर्णांक ret = 0;

	जबतक (workload_types[i] != शून्य)
		ret += प्र_लिखो(&buf[ret], "%s ", workload_types[i++]);

	ret += प्र_लिखो(&buf[ret], "\n");

	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(workload_available_types);

अटल sमाप_प्रकार workload_type_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	अक्षर str_preference[15];
	u32 data = 0;
	sमाप_प्रकार ret;

	ret = माला_पूछो(buf, "%14s", str_preference);
	अगर (ret != 1)
		वापस -EINVAL;

	ret = match_string(workload_types, -1, str_preference);
	अगर (ret < 0)
		वापस ret;

	ret &= 0xff;

	अगर (ret)
		data = BIT(MBOX_DATA_BIT_VALID) | BIT(MBOX_DATA_BIT_AC_DC);

	data |= ret;

	ret = send_mbox_cmd(pdev, MBOX_CMD_WORKLOAD_TYPE_WRITE, data, शून्य);
	अगर (ret)
		वापस false;

	वापस count;
पूर्ण

अटल sमाप_प्रकार workload_type_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	u8 cmd_resp;
	पूर्णांक ret;

	ret = send_mbox_cmd(pdev, MBOX_CMD_WORKLOAD_TYPE_READ, 0, &cmd_resp);
	अगर (ret)
		वापस false;

	cmd_resp &= 0xff;

	अगर (cmd_resp > ARRAY_SIZE(workload_types) - 1)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%s\n", workload_types[cmd_resp]);
पूर्ण

अटल DEVICE_ATTR_RW(workload_type);

अटल काष्ठा attribute *workload_req_attrs[] = अणु
	&dev_attr_workload_available_types.attr,
	&dev_attr_workload_type.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group workload_req_attribute_group = अणु
	.attrs = workload_req_attrs,
	.name = "workload_request"
पूर्ण;



अटल bool workload_req_created;

पूर्णांक proc_thermal_mbox_add(काष्ठा pci_dev *pdev, काष्ठा proc_thermal_device *proc_priv)
अणु
	u8 cmd_resp;
	पूर्णांक ret;

	/* Check अगर there is a mailbox support, अगर fails वापस success */
	ret = send_mbox_cmd(pdev, MBOX_CMD_WORKLOAD_TYPE_READ, 0, &cmd_resp);
	अगर (ret)
		वापस 0;

	ret = sysfs_create_group(&pdev->dev.kobj, &workload_req_attribute_group);
	अगर (ret)
		वापस ret;

	workload_req_created = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(proc_thermal_mbox_add);

व्योम proc_thermal_mbox_हटाओ(काष्ठा pci_dev *pdev)
अणु
	अगर (workload_req_created)
		sysfs_हटाओ_group(&pdev->dev.kobj, &workload_req_attribute_group);

	workload_req_created = false;

पूर्ण
EXPORT_SYMBOL_GPL(proc_thermal_mbox_हटाओ);

MODULE_LICENSE("GPL v2");
