<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mISDNअगर.h>
#समावेश "core.h"

अटल u_पूर्णांक debug;

MODULE_AUTHOR("Karsten Keil");
MODULE_LICENSE("GPL");
module_param(debug, uपूर्णांक, S_IRUGO | S_IWUSR);

अटल u64		device_ids;
#घोषणा MAX_DEVICE_ID	63

अटल LIST_HEAD(Bprotocols);
अटल DEFINE_RWLOCK(bp_lock);

अटल व्योम mISDN_dev_release(काष्ठा device *dev)
अणु
	/* nothing to करो: the device is part of its parent's data काष्ठाure */
पूर्ण

अटल sमाप_प्रकार id_show(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mISDNdevice *mdev = dev_to_mISDN(dev);

	अगर (!mdev)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", mdev->id);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल sमाप_प्रकार nrbchan_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mISDNdevice *mdev = dev_to_mISDN(dev);

	अगर (!mdev)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", mdev->nrbchan);
पूर्ण
अटल DEVICE_ATTR_RO(nrbchan);

अटल sमाप_प्रकार d_protocols_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mISDNdevice *mdev = dev_to_mISDN(dev);

	अगर (!mdev)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", mdev->Dprotocols);
पूर्ण
अटल DEVICE_ATTR_RO(d_protocols);

अटल sमाप_प्रकार b_protocols_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mISDNdevice *mdev = dev_to_mISDN(dev);

	अगर (!mdev)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", mdev->Bprotocols | get_all_Bprotocols());
पूर्ण
अटल DEVICE_ATTR_RO(b_protocols);

अटल sमाप_प्रकार protocol_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mISDNdevice *mdev = dev_to_mISDN(dev);

	अगर (!mdev)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", mdev->D.protocol);
पूर्ण
अटल DEVICE_ATTR_RO(protocol);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	म_नकल(buf, dev_name(dev));
	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR_RO(name);

#अगर 0 /* hangs */
अटल sमाप_प्रकार name_set(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err = 0;
	अक्षर *out = kदो_स्मृति(count + 1, GFP_KERNEL);

	अगर (!out)
		वापस -ENOMEM;

	स_नकल(out, buf, count);
	अगर (count && out[count - 1] == '\n')
		out[--count] = 0;
	अगर (count)
		err = device_नाम(dev, out);
	kमुक्त(out);

	वापस (err < 0) ? err : count;
पूर्ण
अटल DEVICE_ATTR_RW(name);
#पूर्ण_अगर

अटल sमाप_प्रकार channelmap_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mISDNdevice *mdev = dev_to_mISDN(dev);
	अक्षर *bp = buf;
	पूर्णांक i;

	क्रम (i = 0; i <= mdev->nrbchan; i++)
		*bp++ = test_channelmap(i, mdev->channelmap) ? '1' : '0';

	वापस bp - buf;
पूर्ण
अटल DEVICE_ATTR_RO(channelmap);

अटल काष्ठा attribute *mISDN_attrs[] = अणु
	&dev_attr_id.attr,
	&dev_attr_d_protocols.attr,
	&dev_attr_b_protocols.attr,
	&dev_attr_protocol.attr,
	&dev_attr_channelmap.attr,
	&dev_attr_nrbchan.attr,
	&dev_attr_name.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(mISDN);

अटल पूर्णांक mISDN_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा mISDNdevice *mdev = dev_to_mISDN(dev);

	अगर (!mdev)
		वापस 0;

	अगर (add_uevent_var(env, "nchans=%d", mdev->nrbchan))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mISDN_class_release(काष्ठा class *cls)
अणु
	/* करो nothing, it's अटल */
पूर्ण

अटल काष्ठा class mISDN_class = अणु
	.name = "mISDN",
	.owner = THIS_MODULE,
	.dev_uevent = mISDN_uevent,
	.dev_groups = mISDN_groups,
	.dev_release = mISDN_dev_release,
	.class_release = mISDN_class_release,
पूर्ण;

अटल पूर्णांक
_get_mdevice(काष्ठा device *dev, स्थिर व्योम *id)
अणु
	काष्ठा mISDNdevice *mdev = dev_to_mISDN(dev);

	अगर (!mdev)
		वापस 0;
	अगर (mdev->id != *(स्थिर u_पूर्णांक *)id)
		वापस 0;
	वापस 1;
पूर्ण

काष्ठा mISDNdevice
*get_mdevice(u_पूर्णांक id)
अणु
	वापस dev_to_mISDN(class_find_device(&mISDN_class, शून्य, &id,
					      _get_mdevice));
पूर्ण

अटल पूर्णांक
_get_mdevice_count(काष्ठा device *dev, व्योम *cnt)
अणु
	*(पूर्णांक *)cnt += 1;
	वापस 0;
पूर्ण

पूर्णांक
get_mdevice_count(व्योम)
अणु
	पूर्णांक cnt = 0;

	class_क्रम_each_device(&mISDN_class, शून्य, &cnt, _get_mdevice_count);
	वापस cnt;
पूर्ण

अटल पूर्णांक
get_मुक्त_devid(व्योम)
अणु
	u_पूर्णांक	i;

	क्रम (i = 0; i <= MAX_DEVICE_ID; i++)
		अगर (!test_and_set_bit(i, (u_दीर्घ *)&device_ids))
			अवरोध;
	अगर (i > MAX_DEVICE_ID)
		वापस -EBUSY;
	वापस i;
पूर्ण

पूर्णांक
mISDN_रेजिस्टर_device(काष्ठा mISDNdevice *dev,
		      काष्ठा device *parent, अक्षर *name)
अणु
	पूर्णांक	err;

	err = get_मुक्त_devid();
	अगर (err < 0)
		जाओ error1;
	dev->id = err;

	device_initialize(&dev->dev);
	अगर (name && name[0])
		dev_set_name(&dev->dev, "%s", name);
	अन्यथा
		dev_set_name(&dev->dev, "mISDN%d", dev->id);
	अगर (debug & DEBUG_CORE)
		prपूर्णांकk(KERN_DEBUG "mISDN_register %s %d\n",
		       dev_name(&dev->dev), dev->id);
	err = create_stack(dev);
	अगर (err)
		जाओ error1;

	dev->dev.class = &mISDN_class;
	dev->dev.platक्रमm_data = dev;
	dev->dev.parent = parent;
	dev_set_drvdata(&dev->dev, dev);

	err = device_add(&dev->dev);
	अगर (err)
		जाओ error3;
	वापस 0;

error3:
	delete_stack(dev);
	वापस err;
error1:
	वापस err;

पूर्ण
EXPORT_SYMBOL(mISDN_रेजिस्टर_device);

व्योम
mISDN_unरेजिस्टर_device(काष्ठा mISDNdevice *dev) अणु
	अगर (debug & DEBUG_CORE)
		prपूर्णांकk(KERN_DEBUG "mISDN_unregister %s %d\n",
		       dev_name(&dev->dev), dev->id);
	/* sysfs_हटाओ_link(&dev->dev.kobj, "device"); */
	device_del(&dev->dev);
	dev_set_drvdata(&dev->dev, शून्य);

	test_and_clear_bit(dev->id, (u_दीर्घ *)&device_ids);
	delete_stack(dev);
	put_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL(mISDN_unरेजिस्टर_device);

u_पूर्णांक
get_all_Bprotocols(व्योम)
अणु
	काष्ठा Bprotocol	*bp;
	u_पूर्णांक	m = 0;

	पढ़ो_lock(&bp_lock);
	list_क्रम_each_entry(bp, &Bprotocols, list)
		m |= bp->Bprotocols;
	पढ़ो_unlock(&bp_lock);
	वापस m;
पूर्ण

काष्ठा Bprotocol *
get_Bprotocol4mask(u_पूर्णांक m)
अणु
	काष्ठा Bprotocol	*bp;

	पढ़ो_lock(&bp_lock);
	list_क्रम_each_entry(bp, &Bprotocols, list)
		अगर (bp->Bprotocols & m) अणु
			पढ़ो_unlock(&bp_lock);
			वापस bp;
		पूर्ण
	पढ़ो_unlock(&bp_lock);
	वापस शून्य;
पूर्ण

काष्ठा Bprotocol *
get_Bprotocol4id(u_पूर्णांक id)
अणु
	u_पूर्णांक	m;

	अगर (id < ISDN_P_B_START || id > 63) अणु
		prपूर्णांकk(KERN_WARNING "%s id not in range  %d\n",
		       __func__, id);
		वापस शून्य;
	पूर्ण
	m = 1 << (id & ISDN_P_B_MASK);
	वापस get_Bprotocol4mask(m);
पूर्ण

पूर्णांक
mISDN_रेजिस्टर_Bprotocol(काष्ठा Bprotocol *bp)
अणु
	u_दीर्घ			flags;
	काष्ठा Bprotocol	*old;

	अगर (debug & DEBUG_CORE)
		prपूर्णांकk(KERN_DEBUG "%s: %s/%x\n", __func__,
		       bp->name, bp->Bprotocols);
	old = get_Bprotocol4mask(bp->Bprotocols);
	अगर (old) अणु
		prपूर्णांकk(KERN_WARNING
		       "register duplicate protocol old %s/%x new %s/%x\n",
		       old->name, old->Bprotocols, bp->name, bp->Bprotocols);
		वापस -EBUSY;
	पूर्ण
	ग_लिखो_lock_irqsave(&bp_lock, flags);
	list_add_tail(&bp->list, &Bprotocols);
	ग_लिखो_unlock_irqrestore(&bp_lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mISDN_रेजिस्टर_Bprotocol);

व्योम
mISDN_unरेजिस्टर_Bprotocol(काष्ठा Bprotocol *bp)
अणु
	u_दीर्घ	flags;

	अगर (debug & DEBUG_CORE)
		prपूर्णांकk(KERN_DEBUG "%s: %s/%x\n", __func__, bp->name,
		       bp->Bprotocols);
	ग_लिखो_lock_irqsave(&bp_lock, flags);
	list_del(&bp->list);
	ग_लिखो_unlock_irqrestore(&bp_lock, flags);
पूर्ण
EXPORT_SYMBOL(mISDN_unरेजिस्टर_Bprotocol);

अटल स्थिर अक्षर *msg_no_channel = "<no channel>";
अटल स्थिर अक्षर *msg_no_stack = "<no stack>";
अटल स्थिर अक्षर *msg_no_stackdev = "<no stack device>";

स्थिर अक्षर *mISDNDevName4ch(काष्ठा mISDNchannel *ch)
अणु
	अगर (!ch)
		वापस msg_no_channel;
	अगर (!ch->st)
		वापस msg_no_stack;
	अगर (!ch->st->dev)
		वापस msg_no_stackdev;
	वापस dev_name(&ch->st->dev->dev);
पूर्ण;
EXPORT_SYMBOL(mISDNDevName4ch);

अटल पूर्णांक
mISDNInit(व्योम)
अणु
	पूर्णांक	err;

	prपूर्णांकk(KERN_INFO "Modular ISDN core version %d.%d.%d\n",
	       MISDN_MAJOR_VERSION, MISDN_MINOR_VERSION, MISDN_RELEASE);
	mISDN_init_घड़ी(&debug);
	mISDN_initstack(&debug);
	err = class_रेजिस्टर(&mISDN_class);
	अगर (err)
		जाओ error1;
	err = mISDN_initसमयr(&debug);
	अगर (err)
		जाओ error2;
	err = l1_init(&debug);
	अगर (err)
		जाओ error3;
	err = Isdnl2_Init(&debug);
	अगर (err)
		जाओ error4;
	err = misdn_sock_init(&debug);
	अगर (err)
		जाओ error5;
	वापस 0;

error5:
	Isdnl2_cleanup();
error4:
	l1_cleanup();
error3:
	mISDN_समयr_cleanup();
error2:
	class_unरेजिस्टर(&mISDN_class);
error1:
	वापस err;
पूर्ण

अटल व्योम mISDN_cleanup(व्योम)
अणु
	misdn_sock_cleanup();
	Isdnl2_cleanup();
	l1_cleanup();
	mISDN_समयr_cleanup();
	class_unरेजिस्टर(&mISDN_class);

	prपूर्णांकk(KERN_DEBUG "mISDNcore unloaded\n");
पूर्ण

module_init(mISDNInit);
module_निकास(mISDN_cleanup);
