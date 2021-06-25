<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * raid_class.c - implementation of a simple raid visualisation class
 *
 * Copyright (c) 2005 - James Bottomley <James.Bottomley@steeleye.com>
 *
 * This class is deचिन्हित to allow raid attributes to be visualised and
 * manipulated in a क्रमm independent of the underlying raid.  Ultimately this
 * should work क्रम both hardware and software raids.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/raid_class.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#घोषणा RAID_NUM_ATTRS	3

काष्ठा raid_पूर्णांकernal अणु
	काष्ठा raid_ढाँचा r;
	काष्ठा raid_function_ढाँचा *f;
	/* The actual attributes */
	काष्ठा device_attribute निजी_attrs[RAID_NUM_ATTRS];
	/* The array of null terminated poपूर्णांकers to attributes 
	 * needed by scsi_sysfs.c */
	काष्ठा device_attribute *attrs[RAID_NUM_ATTRS + 1];
पूर्ण;

काष्ठा raid_component अणु
	काष्ठा list_head node;
	काष्ठा device dev;
	पूर्णांक num;
पूर्ण;

#घोषणा to_raid_पूर्णांकernal(पंचांगpl)	container_of(पंचांगpl, काष्ठा raid_पूर्णांकernal, r)

#घोषणा tc_to_raid_पूर्णांकernal(tcont) (अणु					\
	काष्ठा raid_ढाँचा *r =					\
		container_of(tcont, काष्ठा raid_ढाँचा, raid_attrs);	\
	to_raid_पूर्णांकernal(r);						\
पूर्ण)

#घोषणा ac_to_raid_पूर्णांकernal(acont) (अणु					\
	काष्ठा transport_container *tc =				\
		container_of(acont, काष्ठा transport_container, ac);	\
	tc_to_raid_पूर्णांकernal(tc);					\
पूर्ण)

#घोषणा device_to_raid_पूर्णांकernal(dev) (अणु				\
	काष्ठा attribute_container *ac =				\
		attribute_container_classdev_to_container(dev);	\
	ac_to_raid_पूर्णांकernal(ac);					\
पूर्ण)
	

अटल पूर्णांक raid_match(काष्ठा attribute_container *cont, काष्ठा device *dev)
अणु
	/* We have to look क्रम every subप्रणाली that could house
	 * emulated RAID devices, so start with SCSI */
	काष्ठा raid_पूर्णांकernal *i = ac_to_raid_पूर्णांकernal(cont);

	अगर (IS_ENABLED(CONFIG_SCSI) && scsi_is_sdev_device(dev)) अणु
		काष्ठा scsi_device *sdev = to_scsi_device(dev);

		अगर (i->f->cookie != sdev->host->hostt)
			वापस 0;

		वापस i->f->is_raid(dev);
	पूर्ण
	/* FIXME: look at other subप्रणालीs too */
	वापस 0;
पूर्ण

अटल पूर्णांक raid_setup(काष्ठा transport_container *tc, काष्ठा device *dev,
		       काष्ठा device *cdev)
अणु
	काष्ठा raid_data *rd;

	BUG_ON(dev_get_drvdata(cdev));

	rd = kzalloc(माप(*rd), GFP_KERNEL);
	अगर (!rd)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&rd->component_list);
	dev_set_drvdata(cdev, rd);
		
	वापस 0;
पूर्ण

अटल पूर्णांक raid_हटाओ(काष्ठा transport_container *tc, काष्ठा device *dev,
		       काष्ठा device *cdev)
अणु
	काष्ठा raid_data *rd = dev_get_drvdata(cdev);
	काष्ठा raid_component *rc, *next;
	dev_prपूर्णांकk(KERN_ERR, dev, "RAID REMOVE\n");
	dev_set_drvdata(cdev, शून्य);
	list_क्रम_each_entry_safe(rc, next, &rd->component_list, node) अणु
		list_del(&rc->node);
		dev_prपूर्णांकk(KERN_ERR, rc->dev.parent, "RAID COMPONENT REMOVE\n");
		device_unरेजिस्टर(&rc->dev);
	पूर्ण
	dev_prपूर्णांकk(KERN_ERR, dev, "RAID REMOVE DONE\n");
	kमुक्त(rd);
	वापस 0;
पूर्ण

अटल DECLARE_TRANSPORT_CLASS(raid_class,
			       "raid_devices",
			       raid_setup,
			       raid_हटाओ,
			       शून्य);

अटल स्थिर काष्ठा अणु
	क्रमागत raid_state	value;
	अक्षर		*name;
पूर्ण raid_states[] = अणु
	अणु RAID_STATE_UNKNOWN, "unknown" पूर्ण,
	अणु RAID_STATE_ACTIVE, "active" पूर्ण,
	अणु RAID_STATE_DEGRADED, "degraded" पूर्ण,
	अणु RAID_STATE_RESYNCING, "resyncing" पूर्ण,
	अणु RAID_STATE_OFFLINE, "offline" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *raid_state_name(क्रमागत raid_state state)
अणु
	पूर्णांक i;
	अक्षर *name = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(raid_states); i++) अणु
		अगर (raid_states[i].value == state) अणु
			name = raid_states[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस name;
पूर्ण

अटल काष्ठा अणु
	क्रमागत raid_level value;
	अक्षर *name;
पूर्ण raid_levels[] = अणु
	अणु RAID_LEVEL_UNKNOWN, "unknown" पूर्ण,
	अणु RAID_LEVEL_LINEAR, "linear" पूर्ण,
	अणु RAID_LEVEL_0, "raid0" पूर्ण,
	अणु RAID_LEVEL_1, "raid1" पूर्ण,
	अणु RAID_LEVEL_10, "raid10" पूर्ण,
	अणु RAID_LEVEL_1E, "raid1e" पूर्ण,
	अणु RAID_LEVEL_3, "raid3" पूर्ण,
	अणु RAID_LEVEL_4, "raid4" पूर्ण,
	अणु RAID_LEVEL_5, "raid5" पूर्ण,
	अणु RAID_LEVEL_50, "raid50" पूर्ण,
	अणु RAID_LEVEL_6, "raid6" पूर्ण,
	अणु RAID_LEVEL_JBOD, "jbod" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *raid_level_name(क्रमागत raid_level level)
अणु
	पूर्णांक i;
	अक्षर *name = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(raid_levels); i++) अणु
		अगर (raid_levels[i].value == level) अणु
			name = raid_levels[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस name;
पूर्ण

#घोषणा raid_attr_show_पूर्णांकernal(attr, fmt, var, code)			\
अटल sमाप_प्रकार raid_show_##attr(काष्ठा device *dev, 			\
				काष्ठा device_attribute *attr, 		\
				अक्षर *buf)				\
अणु									\
	काष्ठा raid_data *rd = dev_get_drvdata(dev);			\
	code								\
	वापस snम_लिखो(buf, 20, #fmt "\n", var);			\
पूर्ण

#घोषणा raid_attr_ro_states(attr, states, code)				\
raid_attr_show_पूर्णांकernal(attr, %s, name,					\
	स्थिर अक्षर *name;						\
	code								\
	name = raid_##states##_name(rd->attr);				\
)									\
अटल DEVICE_ATTR(attr, S_IRUGO, raid_show_##attr, शून्य)


#घोषणा raid_attr_ro_पूर्णांकernal(attr, code)				\
raid_attr_show_पूर्णांकernal(attr, %d, rd->attr, code)			\
अटल DEVICE_ATTR(attr, S_IRUGO, raid_show_##attr, शून्य)

#घोषणा ATTR_CODE(attr)							\
	काष्ठा raid_पूर्णांकernal *i = device_to_raid_पूर्णांकernal(dev);		\
	अगर (i->f->get_##attr)						\
		i->f->get_##attr(dev->parent);

#घोषणा raid_attr_ro(attr)	raid_attr_ro_पूर्णांकernal(attr, )
#घोषणा raid_attr_ro_fn(attr)	raid_attr_ro_पूर्णांकernal(attr, ATTR_CODE(attr))
#घोषणा raid_attr_ro_state(attr)	raid_attr_ro_states(attr, attr, )
#घोषणा raid_attr_ro_state_fn(attr)	raid_attr_ro_states(attr, attr, ATTR_CODE(attr))


raid_attr_ro_state(level);
raid_attr_ro_fn(resync);
raid_attr_ro_state_fn(state);

अटल व्योम raid_component_release(काष्ठा device *dev)
अणु
	काष्ठा raid_component *rc =
		container_of(dev, काष्ठा raid_component, dev);
	dev_prपूर्णांकk(KERN_ERR, rc->dev.parent, "COMPONENT RELEASE\n");
	put_device(rc->dev.parent);
	kमुक्त(rc);
पूर्ण

पूर्णांक raid_component_add(काष्ठा raid_ढाँचा *r,काष्ठा device *raid_dev,
		       काष्ठा device *component_dev)
अणु
	काष्ठा device *cdev =
		attribute_container_find_class_device(&r->raid_attrs.ac,
						      raid_dev);
	काष्ठा raid_component *rc;
	काष्ठा raid_data *rd = dev_get_drvdata(cdev);
	पूर्णांक err;

	rc = kzalloc(माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&rc->node);
	device_initialize(&rc->dev);
	rc->dev.release = raid_component_release;
	rc->dev.parent = get_device(component_dev);
	rc->num = rd->component_count++;

	dev_set_name(&rc->dev, "component-%d", rc->num);
	list_add_tail(&rc->node, &rd->component_list);
	rc->dev.class = &raid_class.class;
	err = device_add(&rc->dev);
	अगर (err)
		जाओ err_out;

	वापस 0;

err_out:
	list_del(&rc->node);
	rd->component_count--;
	put_device(component_dev);
	kमुक्त(rc);
	वापस err;
पूर्ण
EXPORT_SYMBOL(raid_component_add);

काष्ठा raid_ढाँचा *
raid_class_attach(काष्ठा raid_function_ढाँचा *ft)
अणु
	काष्ठा raid_पूर्णांकernal *i = kzalloc(माप(काष्ठा raid_पूर्णांकernal),
					  GFP_KERNEL);
	पूर्णांक count = 0;

	अगर (unlikely(!i))
		वापस शून्य;

	i->f = ft;

	i->r.raid_attrs.ac.class = &raid_class.class;
	i->r.raid_attrs.ac.match = raid_match;
	i->r.raid_attrs.ac.attrs = &i->attrs[0];

	attribute_container_रेजिस्टर(&i->r.raid_attrs.ac);

	i->attrs[count++] = &dev_attr_level;
	i->attrs[count++] = &dev_attr_resync;
	i->attrs[count++] = &dev_attr_state;

	i->attrs[count] = शून्य;
	BUG_ON(count > RAID_NUM_ATTRS);

	वापस &i->r;
पूर्ण
EXPORT_SYMBOL(raid_class_attach);

व्योम
raid_class_release(काष्ठा raid_ढाँचा *r)
अणु
	काष्ठा raid_पूर्णांकernal *i = to_raid_पूर्णांकernal(r);

	BUG_ON(attribute_container_unरेजिस्टर(&i->r.raid_attrs.ac));

	kमुक्त(i);
पूर्ण
EXPORT_SYMBOL(raid_class_release);

अटल __init पूर्णांक raid_init(व्योम)
अणु
	वापस transport_class_रेजिस्टर(&raid_class);
पूर्ण

अटल __निकास व्योम raid_निकास(व्योम)
अणु
	transport_class_unरेजिस्टर(&raid_class);
पूर्ण

MODULE_AUTHOR("James Bottomley");
MODULE_DESCRIPTION("RAID device class");
MODULE_LICENSE("GPL");

module_init(raid_init);
module_निकास(raid_निकास);

