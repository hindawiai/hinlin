<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ATM driver model support. */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/kobject.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश "common.h"
#समावेश "resources.h"

#घोषणा to_aपंचांग_dev(cldev) container_of(cldev, काष्ठा aपंचांग_dev, class_dev)

अटल sमाप_प्रकार show_type(काष्ठा device *cdev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aपंचांग_dev *adev = to_aपंचांग_dev(cdev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", adev->type);
पूर्ण

अटल sमाप_प्रकार show_address(काष्ठा device *cdev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aपंचांग_dev *adev = to_aपंचांग_dev(cdev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%pM\n", adev->esi);
पूर्ण

अटल sमाप_प्रकार show_aपंचांगaddress(काष्ठा device *cdev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा aपंचांग_dev *adev = to_aपंचांग_dev(cdev);
	काष्ठा aपंचांग_dev_addr *aaddr;
	पूर्णांक count = 0;

	spin_lock_irqsave(&adev->lock, flags);
	list_क्रम_each_entry(aaddr, &adev->local, entry) अणु
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "%1phN.%2phN.%10phN.%6phN.%1phN\n",
				   &aaddr->addr.sas_addr.prv[0],
				   &aaddr->addr.sas_addr.prv[1],
				   &aaddr->addr.sas_addr.prv[3],
				   &aaddr->addr.sas_addr.prv[13],
				   &aaddr->addr.sas_addr.prv[19]);
	पूर्ण
	spin_unlock_irqrestore(&adev->lock, flags);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_aपंचांगindex(काष्ठा device *cdev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aपंचांग_dev *adev = to_aपंचांग_dev(cdev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", adev->number);
पूर्ण

अटल sमाप_प्रकार show_carrier(काष्ठा device *cdev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aपंचांग_dev *adev = to_aपंचांग_dev(cdev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			 adev->संकेत == ATM_PHY_SIG_LOST ? 0 : 1);
पूर्ण

अटल sमाप_प्रकार show_link_rate(काष्ठा device *cdev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aपंचांग_dev *adev = to_aपंचांग_dev(cdev);
	पूर्णांक link_rate;

	/* show the link rate, not the data rate */
	चयन (adev->link_rate) अणु
	हाल ATM_OC3_PCR:
		link_rate = 155520000;
		अवरोध;
	हाल ATM_OC12_PCR:
		link_rate = 622080000;
		अवरोध;
	हाल ATM_25_PCR:
		link_rate = 25600000;
		अवरोध;
	शेष:
		link_rate = adev->link_rate * 8 * 53;
	पूर्ण
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", link_rate);
पूर्ण

अटल DEVICE_ATTR(address, 0444, show_address, शून्य);
अटल DEVICE_ATTR(aपंचांगaddress, 0444, show_aपंचांगaddress, शून्य);
अटल DEVICE_ATTR(aपंचांगindex, 0444, show_aपंचांगindex, शून्य);
अटल DEVICE_ATTR(carrier, 0444, show_carrier, शून्य);
अटल DEVICE_ATTR(type, 0444, show_type, शून्य);
अटल DEVICE_ATTR(link_rate, 0444, show_link_rate, शून्य);

अटल काष्ठा device_attribute *aपंचांग_attrs[] = अणु
	&dev_attr_aपंचांगaddress,
	&dev_attr_address,
	&dev_attr_aपंचांगindex,
	&dev_attr_carrier,
	&dev_attr_type,
	&dev_attr_link_rate,
	शून्य
पूर्ण;


अटल पूर्णांक aपंचांग_uevent(काष्ठा device *cdev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा aपंचांग_dev *adev;

	अगर (!cdev)
		वापस -ENODEV;

	adev = to_aपंचांग_dev(cdev);
	अगर (!adev)
		वापस -ENODEV;

	अगर (add_uevent_var(env, "NAME=%s%d", adev->type, adev->number))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम aपंचांग_release(काष्ठा device *cdev)
अणु
	काष्ठा aपंचांग_dev *adev = to_aपंचांग_dev(cdev);

	kमुक्त(adev);
पूर्ण

अटल काष्ठा class aपंचांग_class = अणु
	.name		= "atm",
	.dev_release	= aपंचांग_release,
	.dev_uevent		= aपंचांग_uevent,
पूर्ण;

पूर्णांक aपंचांग_रेजिस्टर_sysfs(काष्ठा aपंचांग_dev *adev, काष्ठा device *parent)
अणु
	काष्ठा device *cdev = &adev->class_dev;
	पूर्णांक i, j, err;

	cdev->class = &aपंचांग_class;
	cdev->parent = parent;
	dev_set_drvdata(cdev, adev);

	dev_set_name(cdev, "%s%d", adev->type, adev->number);
	err = device_रेजिस्टर(cdev);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; aपंचांग_attrs[i]; i++) अणु
		err = device_create_file(cdev, aपंचांग_attrs[i]);
		अगर (err)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	क्रम (j = 0; j < i; j++)
		device_हटाओ_file(cdev, aपंचांग_attrs[j]);
	device_del(cdev);
	वापस err;
पूर्ण

व्योम aपंचांग_unरेजिस्टर_sysfs(काष्ठा aपंचांग_dev *adev)
अणु
	काष्ठा device *cdev = &adev->class_dev;

	device_del(cdev);
पूर्ण

पूर्णांक __init aपंचांग_sysfs_init(व्योम)
अणु
	वापस class_रेजिस्टर(&aपंचांग_class);
पूर्ण

व्योम __निकास aपंचांग_sysfs_निकास(व्योम)
अणु
	class_unरेजिस्टर(&aपंचांग_class);
पूर्ण
