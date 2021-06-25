<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * adummy.c: a dummy ATM driver
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/sonet.h>

/* version definition */

#घोषणा DRV_VERSION "1.0"

#घोषणा DEV_LABEL "adummy"

#घोषणा ADUMMY_DEV(dev) ((काष्ठा adummy_dev *) (dev)->dev_data)

काष्ठा adummy_dev अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev;

	काष्ठा list_head entry;
पूर्ण;

/* globals */

अटल LIST_HEAD(adummy_devs);

अटल sमाप_प्रकार __set_संकेत(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev = container_of(dev, काष्ठा aपंचांग_dev, class_dev);
	पूर्णांक संकेत;

	अगर (माला_पूछो(buf, "%d", &संकेत) == 1) अणु

		अगर (संकेत < ATM_PHY_SIG_LOST || संकेत > ATM_PHY_SIG_FOUND)
			संकेत = ATM_PHY_SIG_UNKNOWN;

		aपंचांग_dev_संकेत_change(aपंचांग_dev, संकेत);
		वापस 1;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार __show_संकेत(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev = container_of(dev, काष्ठा aपंचांग_dev, class_dev);
	वापस प्र_लिखो(buf, "%d\n", aपंचांग_dev->संकेत);
पूर्ण
अटल DEVICE_ATTR(संकेत, 0644, __show_संकेत, __set_संकेत);

अटल काष्ठा attribute *adummy_attrs[] = अणु
	&dev_attr_संकेत.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adummy_group_attrs = अणु
	.name = शून्य, /* We want them in dev's root folder */
	.attrs = adummy_attrs
पूर्ण;

अटल पूर्णांक __init
adummy_start(काष्ठा aपंचांग_dev *dev)
अणु
	dev->ci_range.vpi_bits = 4;
	dev->ci_range.vci_bits = 12;

	वापस 0;
पूर्ण

अटल पूर्णांक
adummy_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	लघु vpi = vcc->vpi;
	पूर्णांक vci = vcc->vci;

	अगर (vci == ATM_VCI_UNSPEC || vpi == ATM_VPI_UNSPEC)
		वापस 0;

	set_bit(ATM_VF_ADDR, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	वापस 0;
पूर्ण

अटल व्योम
adummy_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	clear_bit(ATM_VF_READY, &vcc->flags);
	clear_bit(ATM_VF_ADDR, &vcc->flags);
पूर्ण

अटल पूर्णांक
adummy_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	अगर (vcc->pop)
		vcc->pop(vcc, skb);
	अन्यथा
		dev_kमुक्त_skb_any(skb);
	atomic_inc(&vcc->stats->tx);

	वापस 0;
पूर्ण

अटल पूर्णांक
adummy_proc_पढ़ो(काष्ठा aपंचांग_dev *dev, loff_t *pos, अक्षर *page)
अणु
	पूर्णांक left = *pos;

	अगर (!left--)
		वापस प्र_लिखो(page, "version %s\n", DRV_VERSION);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aपंचांगdev_ops adummy_ops =
अणु
	.खोलो =		adummy_खोलो,
	.बंद =	adummy_बंद,	
	.send =		adummy_send,
	.proc_पढ़ो =	adummy_proc_पढ़ो,
	.owner =	THIS_MODULE
पूर्ण;

अटल पूर्णांक __init adummy_init(व्योम)
अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev;
	काष्ठा adummy_dev *adummy_dev;
	पूर्णांक err = 0;

	prपूर्णांकk(KERN_ERR "adummy: version %s\n", DRV_VERSION);

	adummy_dev = kzalloc(माप(काष्ठा adummy_dev),
						   GFP_KERNEL);
	अगर (!adummy_dev) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL ": kzalloc() failed\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	aपंचांग_dev = aपंचांग_dev_रेजिस्टर(DEV_LABEL, शून्य, &adummy_ops, -1, शून्य);
	अगर (!aपंचांग_dev) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL ": atm_dev_register() failed\n");
		err = -ENODEV;
		जाओ out_kमुक्त;
	पूर्ण

	adummy_dev->aपंचांग_dev = aपंचांग_dev;
	aपंचांग_dev->dev_data = adummy_dev;

	अगर (sysfs_create_group(&aपंचांग_dev->class_dev.kobj, &adummy_group_attrs))
		dev_err(&aपंचांग_dev->class_dev, "Could not register attrs for adummy\n");

	अगर (adummy_start(aपंचांग_dev)) अणु
		prपूर्णांकk(KERN_ERR DEV_LABEL ": adummy_start() failed\n");
		err = -ENODEV;
		जाओ out_unरेजिस्टर;
	पूर्ण

	list_add(&adummy_dev->entry, &adummy_devs);
out:
	वापस err;

out_unरेजिस्टर:
	aपंचांग_dev_deरेजिस्टर(aपंचांग_dev);
out_kमुक्त:
	kमुक्त(adummy_dev);
	जाओ out;
पूर्ण

अटल व्योम __निकास adummy_cleanup(व्योम)
अणु
	काष्ठा adummy_dev *adummy_dev, *next;

	list_क्रम_each_entry_safe(adummy_dev, next, &adummy_devs, entry) अणु
		aपंचांग_dev_deरेजिस्टर(adummy_dev->aपंचांग_dev);
		kमुक्त(adummy_dev);
	पूर्ण
पूर्ण

module_init(adummy_init);
module_निकास(adummy_cleanup);

MODULE_AUTHOR("chas williams <chas@cmf.nrl.navy.mil>");
MODULE_DESCRIPTION("dummy ATM driver");
MODULE_LICENSE("GPL");
