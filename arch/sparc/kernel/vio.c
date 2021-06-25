<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* vio.c: Virtual I/O channel devices probing infraकाष्ठाure.
 *
 *    Copyright (c) 2003-2005 IBM Corp.
 *     Dave Engebretsen engebret@us.ibm.com
 *     Santiago Leon santil@us.ibm.com
 *     Hollis Blanअक्षरd <hollisb@us.ibm.com>
 *     Stephen Rothwell
 *
 * Adapted to sparc64 by David S. Miller davem@davemloft.net
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/mdesc.h>
#समावेश <यंत्र/vपन.स>

अटल स्थिर काष्ठा vio_device_id *vio_match_device(
	स्थिर काष्ठा vio_device_id *matches,
	स्थिर काष्ठा vio_dev *dev)
अणु
	स्थिर अक्षर *type, *compat;
	पूर्णांक len;

	type = dev->type;
	compat = dev->compat;
	len = dev->compat_len;

	जबतक (matches->type[0] || matches->compat[0]) अणु
		पूर्णांक match = 1;
		अगर (matches->type[0])
			match &= !म_भेद(matches->type, type);

		अगर (matches->compat[0]) अणु
			match &= len &&
				of_find_in_proplist(compat, matches->compat, len);
		पूर्ण
		अगर (match)
			वापस matches;
		matches++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक vio_hotplug(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	स्थिर काष्ठा vio_dev *vio_dev = to_vio_dev(dev);

	add_uevent_var(env, "MODALIAS=vio:T%sS%s", vio_dev->type, vio_dev->compat);
	वापस 0;
पूर्ण

अटल पूर्णांक vio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा vio_dev *vio_dev = to_vio_dev(dev);
	काष्ठा vio_driver *vio_drv = to_vio_driver(drv);
	स्थिर काष्ठा vio_device_id *matches = vio_drv->id_table;

	अगर (!matches)
		वापस 0;

	वापस vio_match_device(matches, vio_dev) != शून्य;
पूर्ण

अटल पूर्णांक vio_device_probe(काष्ठा device *dev)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	काष्ठा vio_driver *drv = to_vio_driver(dev->driver);
	स्थिर काष्ठा vio_device_id *id;

	अगर (!drv->probe)
		वापस -ENODEV;

	id = vio_match_device(drv->id_table, vdev);
	अगर (!id)
		वापस -ENODEV;

	/* alloc irqs (unless the driver specअगरied not to) */
	अगर (!drv->no_irq) अणु
		अगर (vdev->tx_irq == 0 && vdev->tx_ino != ~0UL)
			vdev->tx_irq = sun4v_build_virq(vdev->cdev_handle,
							vdev->tx_ino);

		अगर (vdev->rx_irq == 0 && vdev->rx_ino != ~0UL)
			vdev->rx_irq = sun4v_build_virq(vdev->cdev_handle,
							vdev->rx_ino);
	पूर्ण

	वापस drv->probe(vdev, id);
पूर्ण

अटल पूर्णांक vio_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	काष्ठा vio_driver *drv = to_vio_driver(dev->driver);

	अगर (drv->हटाओ) अणु
		/*
		 * Ideally, we would हटाओ/deallocate tx/rx virqs
		 * here - however, there are currently no support
		 * routines to करो so at the moment. TBD
		 */

		वापस drv->हटाओ(vdev);
	पूर्ण

	वापस 1;
पूर्ण

अटल sमाप_प्रकार devspec_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	स्थिर अक्षर *str = "none";

	अगर (!म_भेद(vdev->type, "vnet-port"))
		str = "vnet";
	अन्यथा अगर (!म_भेद(vdev->type, "vdc-port"))
		str = "vdisk";

	वापस प्र_लिखो(buf, "%s\n", str);
पूर्ण
अटल DEVICE_ATTR_RO(devspec);

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	वापस प्र_लिखो(buf, "%s\n", vdev->type);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	स्थिर काष्ठा vio_dev *vdev = to_vio_dev(dev);

	वापस प्र_लिखो(buf, "vio:T%sS%s\n", vdev->type, vdev->compat);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *vio_dev_attrs[] = अणु
	&dev_attr_devspec.attr,
	&dev_attr_type.attr,
	&dev_attr_modalias.attr,
	शून्य,
 पूर्ण;
ATTRIBUTE_GROUPS(vio_dev);

अटल काष्ठा bus_type vio_bus_type = अणु
	.name		= "vio",
	.dev_groups	= vio_dev_groups,
	.uevent         = vio_hotplug,
	.match		= vio_bus_match,
	.probe		= vio_device_probe,
	.हटाओ		= vio_device_हटाओ,
पूर्ण;

पूर्णांक __vio_रेजिस्टर_driver(काष्ठा vio_driver *viodrv, काष्ठा module *owner,
			स्थिर अक्षर *mod_name)
अणु
	viodrv->driver.bus = &vio_bus_type;
	viodrv->driver.name = viodrv->name;
	viodrv->driver.owner = owner;
	viodrv->driver.mod_name = mod_name;

	वापस driver_रेजिस्टर(&viodrv->driver);
पूर्ण
EXPORT_SYMBOL(__vio_रेजिस्टर_driver);

व्योम vio_unरेजिस्टर_driver(काष्ठा vio_driver *viodrv)
अणु
	driver_unरेजिस्टर(&viodrv->driver);
पूर्ण
EXPORT_SYMBOL(vio_unरेजिस्टर_driver);

अटल व्योम vio_dev_release(काष्ठा device *dev)
अणु
	kमुक्त(to_vio_dev(dev));
पूर्ण

अटल sमाप_प्रकार
show_pciobppath_attr(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा vio_dev *vdev;
	काष्ठा device_node *dp;

	vdev = to_vio_dev(dev);
	dp = vdev->dp;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%pOF\n", dp);
पूर्ण

अटल DEVICE_ATTR(obppath, S_IRUSR | S_IRGRP | S_IROTH,
		   show_pciobppath_attr, शून्य);

अटल काष्ठा device_node *cdev_node;

अटल काष्ठा vio_dev *root_vdev;
अटल u64 cdev_cfg_handle;

अटल स्थिर u64 *vio_cfg_handle(काष्ठा mdesc_handle *hp, u64 node)
अणु
	स्थिर u64 *cfg_handle = शून्य;
	u64 a;

	mdesc_क्रम_each_arc(a, hp, node, MDESC_ARC_TYPE_BACK) अणु
		u64 target;

		target = mdesc_arc_target(hp, a);
		cfg_handle = mdesc_get_property(hp, target,
						"cfg-handle", शून्य);
		अगर (cfg_handle)
			अवरोध;
	पूर्ण

	वापस cfg_handle;
पूर्ण

/**
 * vio_vdev_node() - Find VDEV node in MD
 * @hp:  Handle to the MD
 * @vdev:  Poपूर्णांकer to VDEV
 *
 * Find the node in the current MD which matches the given vio_dev. This
 * must be करोne dynamically since the node value can change अगर the MD
 * is updated.
 *
 * NOTE: the MD must be locked, using mdesc_grab(), when calling this routine
 *
 * Return: The VDEV node in MDESC
 */
u64 vio_vdev_node(काष्ठा mdesc_handle *hp, काष्ठा vio_dev *vdev)
अणु
	u64 node;

	अगर (vdev == शून्य)
		वापस MDESC_NODE_शून्य;

	node = mdesc_get_node(hp, (स्थिर अक्षर *)vdev->node_name,
			      &vdev->md_node_info);

	वापस node;
पूर्ण
EXPORT_SYMBOL(vio_vdev_node);

अटल व्योम vio_fill_channel_info(काष्ठा mdesc_handle *hp, u64 mp,
				  काष्ठा vio_dev *vdev)
अणु
	u64 a;

	vdev->tx_ino = ~0UL;
	vdev->rx_ino = ~0UL;
	vdev->channel_id = ~0UL;
	mdesc_क्रम_each_arc(a, hp, mp, MDESC_ARC_TYPE_FWD) अणु
		स्थिर u64 *chan_id;
		स्थिर u64 *irq;
		u64 target;

		target = mdesc_arc_target(hp, a);

		irq = mdesc_get_property(hp, target, "tx-ino", शून्य);
		अगर (irq)
			vdev->tx_ino = *irq;

		irq = mdesc_get_property(hp, target, "rx-ino", शून्य);
		अगर (irq)
			vdev->rx_ino = *irq;

		chan_id = mdesc_get_property(hp, target, "id", शून्य);
		अगर (chan_id)
			vdev->channel_id = *chan_id;
	पूर्ण

	vdev->cdev_handle = cdev_cfg_handle;
पूर्ण

पूर्णांक vio_set_पूर्णांकr(अचिन्हित दीर्घ dev_ino, पूर्णांक state)
अणु
	पूर्णांक err;

	err = sun4v_vपूर्णांकr_set_valid(cdev_cfg_handle, dev_ino, state);
	वापस err;
पूर्ण
EXPORT_SYMBOL(vio_set_पूर्णांकr);

अटल काष्ठा vio_dev *vio_create_one(काष्ठा mdesc_handle *hp, u64 mp,
				      स्थिर अक्षर *node_name,
				      काष्ठा device *parent)
अणु
	स्थिर अक्षर *type, *compat;
	काष्ठा device_node *dp;
	काष्ठा vio_dev *vdev;
	पूर्णांक err, tlen, clen;
	स्थिर u64 *id, *cfg_handle;

	type = mdesc_get_property(hp, mp, "device-type", &tlen);
	अगर (!type) अणु
		type = mdesc_get_property(hp, mp, "name", &tlen);
		अगर (!type) अणु
			type = mdesc_node_name(hp, mp);
			tlen = म_माप(type) + 1;
		पूर्ण
	पूर्ण
	अगर (tlen > VIO_MAX_TYPE_LEN || म_माप(type) >= VIO_MAX_TYPE_LEN) अणु
		prपूर्णांकk(KERN_ERR "VIO: Type string [%s] is too long.\n",
		       type);
		वापस शून्य;
	पूर्ण

	id = mdesc_get_property(hp, mp, "id", शून्य);

	cfg_handle = vio_cfg_handle(hp, mp);

	compat = mdesc_get_property(hp, mp, "device-type", &clen);
	अगर (!compat) अणु
		clen = 0;
	पूर्ण अन्यथा अगर (clen > VIO_MAX_COMPAT_LEN) अणु
		prपूर्णांकk(KERN_ERR "VIO: Compat len %d for [%s] is too long.\n",
		       clen, type);
		वापस शून्य;
	पूर्ण

	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev) अणु
		prपूर्णांकk(KERN_ERR "VIO: Could not allocate vio_dev\n");
		वापस शून्य;
	पूर्ण

	vdev->mp = mp;
	स_नकल(vdev->type, type, tlen);
	अगर (compat)
		स_नकल(vdev->compat, compat, clen);
	अन्यथा
		स_रखो(vdev->compat, 0, माप(vdev->compat));
	vdev->compat_len = clen;

	vdev->port_id = ~0UL;
	vdev->tx_irq = 0;
	vdev->rx_irq = 0;

	vio_fill_channel_info(hp, mp, vdev);

	अगर (!id) अणु
		dev_set_name(&vdev->dev, "%s", type);
		vdev->dev_no = ~(u64)0;
	पूर्ण अन्यथा अगर (!cfg_handle) अणु
		dev_set_name(&vdev->dev, "%s-%llu", type, *id);
		vdev->dev_no = *id;
	पूर्ण अन्यथा अणु
		dev_set_name(&vdev->dev, "%s-%llu-%llu", type,
			     *cfg_handle, *id);
		vdev->dev_no = *cfg_handle;
		vdev->port_id = *id;
	पूर्ण

	vdev->dev.parent = parent;
	vdev->dev.bus = &vio_bus_type;
	vdev->dev.release = vio_dev_release;

	अगर (parent == शून्य) अणु
		dp = cdev_node;
	पूर्ण अन्यथा अगर (to_vio_dev(parent) == root_vdev) अणु
		क्रम_each_child_of_node(cdev_node, dp) अणु
			अगर (of_node_is_type(dp, type))
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		dp = to_vio_dev(parent)->dp;
	पूर्ण
	vdev->dp = dp;

	/*
	 * node_name is शून्य क्रम the parent/channel-devices node and
	 * the parent करोesn't require the MD node info.
	 */
	अगर (node_name != शून्य) अणु
		(व्योम) snम_लिखो(vdev->node_name, VIO_MAX_NAME_LEN, "%s",
				node_name);

		err = mdesc_get_node_info(hp, mp, node_name,
					  &vdev->md_node_info);
		अगर (err) अणु
			pr_err("VIO: Could not get MD node info %s, err=%d\n",
			       dev_name(&vdev->dev), err);
			kमुक्त(vdev);
			वापस शून्य;
		पूर्ण
	पूर्ण

	pr_info("VIO: Adding device %s (tx_ino = %llx, rx_ino = %llx)\n",
		dev_name(&vdev->dev), vdev->tx_ino, vdev->rx_ino);

	err = device_रेजिस्टर(&vdev->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "VIO: Could not register device %s, err=%d\n",
		       dev_name(&vdev->dev), err);
		put_device(&vdev->dev);
		वापस शून्य;
	पूर्ण
	अगर (vdev->dp)
		err = sysfs_create_file(&vdev->dev.kobj,
					&dev_attr_obppath.attr);

	वापस vdev;
पूर्ण

अटल व्योम vio_add(काष्ठा mdesc_handle *hp, u64 node,
		    स्थिर अक्षर *node_name)
अणु
	(व्योम) vio_create_one(hp, node, node_name, &root_vdev->dev);
पूर्ण

काष्ठा vio_हटाओ_node_data अणु
	काष्ठा mdesc_handle *hp;
	u64 node;
पूर्ण;

अटल पूर्णांक vio_md_node_match(काष्ठा device *dev, व्योम *arg)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	काष्ठा vio_हटाओ_node_data *node_data;
	u64 node;

	node_data = (काष्ठा vio_हटाओ_node_data *)arg;

	node = vio_vdev_node(node_data->hp, vdev);

	अगर (node == node_data->node)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम vio_हटाओ(काष्ठा mdesc_handle *hp, u64 node, स्थिर अक्षर *node_name)
अणु
	काष्ठा vio_हटाओ_node_data node_data;
	काष्ठा device *dev;

	node_data.hp = hp;
	node_data.node = node;

	dev = device_find_child(&root_vdev->dev, (व्योम *)&node_data,
				vio_md_node_match);
	अगर (dev) अणु
		prपूर्णांकk(KERN_INFO "VIO: Removing device %s\n", dev_name(dev));

		device_unरेजिस्टर(dev);
		put_device(dev);
	पूर्ण अन्यथा अणु
		pr_err("VIO: %s node not found in MDESC\n", node_name);
	पूर्ण
पूर्ण

अटल काष्ठा mdesc_notअगरier_client vio_device_notअगरier = अणु
	.add		= vio_add,
	.हटाओ		= vio_हटाओ,
	.node_name	= "virtual-device-port",
पूर्ण;

/* We are only पूर्णांकerested in करोमुख्य service ports under the
 * "domain-services" node.  On control nodes there is another port
 * under "openboot" that we should not mess with as aparently that is
 * reserved exclusively क्रम OBP use.
 */
अटल व्योम vio_add_ds(काष्ठा mdesc_handle *hp, u64 node,
		       स्थिर अक्षर *node_name)
अणु
	पूर्णांक found;
	u64 a;

	found = 0;
	mdesc_क्रम_each_arc(a, hp, node, MDESC_ARC_TYPE_BACK) अणु
		u64 target = mdesc_arc_target(hp, a);
		स्थिर अक्षर *name = mdesc_node_name(hp, target);

		अगर (!म_भेद(name, "domain-services")) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found)
		(व्योम) vio_create_one(hp, node, node_name, &root_vdev->dev);
पूर्ण

अटल काष्ठा mdesc_notअगरier_client vio_ds_notअगरier = अणु
	.add		= vio_add_ds,
	.हटाओ		= vio_हटाओ,
	.node_name	= "domain-services-port",
पूर्ण;

अटल स्थिर अक्षर *channel_devices_node = "channel-devices";
अटल स्थिर अक्षर *channel_devices_compat = "SUNW,sun4v-channel-devices";
अटल स्थिर अक्षर *cfg_handle_prop = "cfg-handle";

अटल पूर्णांक __init vio_init(व्योम)
अणु
	काष्ठा mdesc_handle *hp;
	स्थिर अक्षर *compat;
	स्थिर u64 *cfg_handle;
	पूर्णांक err, len;
	u64 root;

	err = bus_रेजिस्टर(&vio_bus_type);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "VIO: Could not register bus type err=%d\n",
		       err);
		वापस err;
	पूर्ण

	hp = mdesc_grab();
	अगर (!hp)
		वापस 0;

	root = mdesc_node_by_name(hp, MDESC_NODE_शून्य, channel_devices_node);
	अगर (root == MDESC_NODE_शून्य) अणु
		prपूर्णांकk(KERN_INFO "VIO: No channel-devices MDESC node.\n");
		mdesc_release(hp);
		वापस 0;
	पूर्ण

	cdev_node = of_find_node_by_name(शून्य, "channel-devices");
	err = -ENODEV;
	अगर (!cdev_node) अणु
		prपूर्णांकk(KERN_INFO "VIO: No channel-devices OBP node.\n");
		जाओ out_release;
	पूर्ण

	compat = mdesc_get_property(hp, root, "compatible", &len);
	अगर (!compat) अणु
		prपूर्णांकk(KERN_ERR "VIO: Channel devices lacks compatible "
		       "property\n");
		जाओ out_release;
	पूर्ण
	अगर (!of_find_in_proplist(compat, channel_devices_compat, len)) अणु
		prपूर्णांकk(KERN_ERR "VIO: Channel devices node lacks (%s) "
		       "compat entry.\n", channel_devices_compat);
		जाओ out_release;
	पूर्ण

	cfg_handle = mdesc_get_property(hp, root, cfg_handle_prop, शून्य);
	अगर (!cfg_handle) अणु
		prपूर्णांकk(KERN_ERR "VIO: Channel devices lacks %s property\n",
		       cfg_handle_prop);
		जाओ out_release;
	पूर्ण

	cdev_cfg_handle = *cfg_handle;

	root_vdev = vio_create_one(hp, root, शून्य, शून्य);
	err = -ENODEV;
	अगर (!root_vdev) अणु
		prपूर्णांकk(KERN_ERR "VIO: Could not create root device.\n");
		जाओ out_release;
	पूर्ण

	mdesc_रेजिस्टर_notअगरier(&vio_device_notअगरier);
	mdesc_रेजिस्टर_notअगरier(&vio_ds_notअगरier);

	mdesc_release(hp);

	वापस err;

out_release:
	mdesc_release(hp);
	वापस err;
पूर्ण

postcore_initcall(vio_init);
