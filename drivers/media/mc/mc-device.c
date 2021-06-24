<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Media device
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/compat.h>
#समावेश <linux/export.h>
#समावेश <linux/idr.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/media.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/usb.h>
#समावेश <linux/version.h>

#समावेश <media/media-device.h>
#समावेश <media/media-devnode.h>
#समावेश <media/media-entity.h>
#समावेश <media/media-request.h>

#अगर_घोषित CONFIG_MEDIA_CONTROLLER

/*
 * Legacy defines from linux/media.h. This is the only place we need this
 * so we just define it here. The media.h header करोesn't expose it to the
 * kernel to prevent it from being used by drivers, but here (and only here!)
 * we need it to handle the legacy behavior.
 */
#घोषणा MEDIA_ENT_SUBTYPE_MASK			0x0000ffff
#घोषणा MEDIA_ENT_T_DEVNODE_UNKNOWN		(MEDIA_ENT_F_OLD_BASE | \
						 MEDIA_ENT_SUBTYPE_MASK)

/* -----------------------------------------------------------------------------
 * Userspace API
 */

अटल अंतरभूत व्योम __user *media_get_uptr(__u64 arg)
अणु
	वापस (व्योम __user *)(uपूर्णांकptr_t)arg;
पूर्ण

अटल पूर्णांक media_device_खोलो(काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक media_device_बंद(काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल दीर्घ media_device_get_info(काष्ठा media_device *dev, व्योम *arg)
अणु
	काष्ठा media_device_info *info = arg;

	स_रखो(info, 0, माप(*info));

	अगर (dev->driver_name[0])
		strscpy(info->driver, dev->driver_name, माप(info->driver));
	अन्यथा
		strscpy(info->driver, dev->dev->driver->name,
			माप(info->driver));

	strscpy(info->model, dev->model, माप(info->model));
	strscpy(info->serial, dev->serial, माप(info->serial));
	strscpy(info->bus_info, dev->bus_info, माप(info->bus_info));

	info->media_version = LINUX_VERSION_CODE;
	info->driver_version = info->media_version;
	info->hw_revision = dev->hw_revision;

	वापस 0;
पूर्ण

अटल काष्ठा media_entity *find_entity(काष्ठा media_device *mdev, u32 id)
अणु
	काष्ठा media_entity *entity;
	पूर्णांक next = id & MEDIA_ENT_ID_FLAG_NEXT;

	id &= ~MEDIA_ENT_ID_FLAG_NEXT;

	media_device_क्रम_each_entity(entity, mdev) अणु
		अगर (((media_entity_id(entity) == id) && !next) ||
		    ((media_entity_id(entity) > id) && next)) अणु
			वापस entity;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल दीर्घ media_device_क्रमागत_entities(काष्ठा media_device *mdev, व्योम *arg)
अणु
	काष्ठा media_entity_desc *entd = arg;
	काष्ठा media_entity *ent;

	ent = find_entity(mdev, entd->id);
	अगर (ent == शून्य)
		वापस -EINVAL;

	स_रखो(entd, 0, माप(*entd));

	entd->id = media_entity_id(ent);
	अगर (ent->name)
		strscpy(entd->name, ent->name, माप(entd->name));
	entd->type = ent->function;
	entd->revision = 0;		/* Unused */
	entd->flags = ent->flags;
	entd->group_id = 0;		/* Unused */
	entd->pads = ent->num_pads;
	entd->links = ent->num_links - ent->num_backlinks;

	/*
	 * Workaround क्रम a bug at media-ctl <= v1.10 that makes it to
	 * करो the wrong thing अगर the entity function करोesn't beदीर्घ to
	 * either MEDIA_ENT_F_OLD_BASE or MEDIA_ENT_F_OLD_SUBDEV_BASE
	 * Ranges.
	 *
	 * Non-subdevices are expected to be at the MEDIA_ENT_F_OLD_BASE,
	 * or, otherwise, will be silently ignored by media-ctl when
	 * prपूर्णांकing the graphviz diagram. So, map them पूर्णांकo the devnode
	 * old range.
	 */
	अगर (ent->function < MEDIA_ENT_F_OLD_BASE ||
	    ent->function > MEDIA_ENT_F_TUNER) अणु
		अगर (is_media_entity_v4l2_subdev(ent))
			entd->type = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;
		अन्यथा अगर (ent->function != MEDIA_ENT_F_IO_V4L)
			entd->type = MEDIA_ENT_T_DEVNODE_UNKNOWN;
	पूर्ण

	स_नकल(&entd->raw, &ent->info, माप(ent->info));

	वापस 0;
पूर्ण

अटल व्योम media_device_kpad_to_upad(स्थिर काष्ठा media_pad *kpad,
				      काष्ठा media_pad_desc *upad)
अणु
	upad->entity = media_entity_id(kpad->entity);
	upad->index = kpad->index;
	upad->flags = kpad->flags;
पूर्ण

अटल दीर्घ media_device_क्रमागत_links(काष्ठा media_device *mdev, व्योम *arg)
अणु
	काष्ठा media_links_क्रमागत *links = arg;
	काष्ठा media_entity *entity;

	entity = find_entity(mdev, links->entity);
	अगर (entity == शून्य)
		वापस -EINVAL;

	अगर (links->pads) अणु
		अचिन्हित पूर्णांक p;

		क्रम (p = 0; p < entity->num_pads; p++) अणु
			काष्ठा media_pad_desc pad;

			स_रखो(&pad, 0, माप(pad));
			media_device_kpad_to_upad(&entity->pads[p], &pad);
			अगर (copy_to_user(&links->pads[p], &pad, माप(pad)))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (links->links) अणु
		काष्ठा media_link *link;
		काष्ठा media_link_desc __user *ulink_desc = links->links;

		list_क्रम_each_entry(link, &entity->links, list) अणु
			काष्ठा media_link_desc klink_desc;

			/* Ignore backlinks. */
			अगर (link->source->entity != entity)
				जारी;
			स_रखो(&klink_desc, 0, माप(klink_desc));
			media_device_kpad_to_upad(link->source,
						  &klink_desc.source);
			media_device_kpad_to_upad(link->sink,
						  &klink_desc.sink);
			klink_desc.flags = link->flags;
			अगर (copy_to_user(ulink_desc, &klink_desc,
					 माप(*ulink_desc)))
				वापस -EFAULT;
			ulink_desc++;
		पूर्ण
	पूर्ण
	स_रखो(links->reserved, 0, माप(links->reserved));

	वापस 0;
पूर्ण

अटल दीर्घ media_device_setup_link(काष्ठा media_device *mdev, व्योम *arg)
अणु
	काष्ठा media_link_desc *linkd = arg;
	काष्ठा media_link *link = शून्य;
	काष्ठा media_entity *source;
	काष्ठा media_entity *sink;

	/* Find the source and sink entities and link.
	 */
	source = find_entity(mdev, linkd->source.entity);
	sink = find_entity(mdev, linkd->sink.entity);

	अगर (source == शून्य || sink == शून्य)
		वापस -EINVAL;

	अगर (linkd->source.index >= source->num_pads ||
	    linkd->sink.index >= sink->num_pads)
		वापस -EINVAL;

	link = media_entity_find_link(&source->pads[linkd->source.index],
				      &sink->pads[linkd->sink.index]);
	अगर (link == शून्य)
		वापस -EINVAL;

	स_रखो(linkd->reserved, 0, माप(linkd->reserved));

	/* Setup the link on both entities. */
	वापस __media_entity_setup_link(link, linkd->flags);
पूर्ण

अटल दीर्घ media_device_get_topology(काष्ठा media_device *mdev, व्योम *arg)
अणु
	काष्ठा media_v2_topology *topo = arg;
	काष्ठा media_entity *entity;
	काष्ठा media_पूर्णांकerface *पूर्णांकf;
	काष्ठा media_pad *pad;
	काष्ठा media_link *link;
	काष्ठा media_v2_entity kentity, __user *uentity;
	काष्ठा media_v2_पूर्णांकerface kपूर्णांकf, __user *uपूर्णांकf;
	काष्ठा media_v2_pad kpad, __user *upad;
	काष्ठा media_v2_link klink, __user *ulink;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	topo->topology_version = mdev->topology_version;

	/* Get entities and number of entities */
	i = 0;
	uentity = media_get_uptr(topo->ptr_entities);
	media_device_क्रम_each_entity(entity, mdev) अणु
		i++;
		अगर (ret || !uentity)
			जारी;

		अगर (i > topo->num_entities) अणु
			ret = -ENOSPC;
			जारी;
		पूर्ण

		/* Copy fields to userspace काष्ठा अगर not error */
		स_रखो(&kentity, 0, माप(kentity));
		kentity.id = entity->graph_obj.id;
		kentity.function = entity->function;
		kentity.flags = entity->flags;
		strscpy(kentity.name, entity->name,
			माप(kentity.name));

		अगर (copy_to_user(uentity, &kentity, माप(kentity)))
			ret = -EFAULT;
		uentity++;
	पूर्ण
	topo->num_entities = i;
	topo->reserved1 = 0;

	/* Get पूर्णांकerfaces and number of पूर्णांकerfaces */
	i = 0;
	uपूर्णांकf = media_get_uptr(topo->ptr_पूर्णांकerfaces);
	media_device_क्रम_each_पूर्णांकf(पूर्णांकf, mdev) अणु
		i++;
		अगर (ret || !uपूर्णांकf)
			जारी;

		अगर (i > topo->num_पूर्णांकerfaces) अणु
			ret = -ENOSPC;
			जारी;
		पूर्ण

		स_रखो(&kपूर्णांकf, 0, माप(kपूर्णांकf));

		/* Copy पूर्णांकf fields to userspace काष्ठा */
		kपूर्णांकf.id = पूर्णांकf->graph_obj.id;
		kपूर्णांकf.पूर्णांकf_type = पूर्णांकf->type;
		kपूर्णांकf.flags = पूर्णांकf->flags;

		अगर (media_type(&पूर्णांकf->graph_obj) == MEDIA_GRAPH_INTF_DEVNODE) अणु
			काष्ठा media_पूर्णांकf_devnode *devnode;

			devnode = पूर्णांकf_to_devnode(पूर्णांकf);

			kपूर्णांकf.devnode.major = devnode->major;
			kपूर्णांकf.devnode.minor = devnode->minor;
		पूर्ण

		अगर (copy_to_user(uपूर्णांकf, &kपूर्णांकf, माप(kपूर्णांकf)))
			ret = -EFAULT;
		uपूर्णांकf++;
	पूर्ण
	topo->num_पूर्णांकerfaces = i;
	topo->reserved2 = 0;

	/* Get pads and number of pads */
	i = 0;
	upad = media_get_uptr(topo->ptr_pads);
	media_device_क्रम_each_pad(pad, mdev) अणु
		i++;
		अगर (ret || !upad)
			जारी;

		अगर (i > topo->num_pads) अणु
			ret = -ENOSPC;
			जारी;
		पूर्ण

		स_रखो(&kpad, 0, माप(kpad));

		/* Copy pad fields to userspace काष्ठा */
		kpad.id = pad->graph_obj.id;
		kpad.entity_id = pad->entity->graph_obj.id;
		kpad.flags = pad->flags;
		kpad.index = pad->index;

		अगर (copy_to_user(upad, &kpad, माप(kpad)))
			ret = -EFAULT;
		upad++;
	पूर्ण
	topo->num_pads = i;
	topo->reserved3 = 0;

	/* Get links and number of links */
	i = 0;
	ulink = media_get_uptr(topo->ptr_links);
	media_device_क्रम_each_link(link, mdev) अणु
		अगर (link->is_backlink)
			जारी;

		i++;

		अगर (ret || !ulink)
			जारी;

		अगर (i > topo->num_links) अणु
			ret = -ENOSPC;
			जारी;
		पूर्ण

		स_रखो(&klink, 0, माप(klink));

		/* Copy link fields to userspace काष्ठा */
		klink.id = link->graph_obj.id;
		klink.source_id = link->gobj0->id;
		klink.sink_id = link->gobj1->id;
		klink.flags = link->flags;

		अगर (copy_to_user(ulink, &klink, माप(klink)))
			ret = -EFAULT;
		ulink++;
	पूर्ण
	topo->num_links = i;
	topo->reserved4 = 0;

	वापस ret;
पूर्ण

अटल दीर्घ media_device_request_alloc(काष्ठा media_device *mdev, व्योम *arg)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_REQUEST_API
	पूर्णांक *alloc_fd = arg;

	अगर (!mdev->ops || !mdev->ops->req_validate || !mdev->ops->req_queue)
		वापस -ENOTTY;

	वापस media_request_alloc(mdev, alloc_fd);
#अन्यथा
	वापस -ENOTTY;
#पूर्ण_अगर
पूर्ण

अटल दीर्घ copy_arg_from_user(व्योम *karg, व्योम __user *uarg, अचिन्हित पूर्णांक cmd)
अणु
	अगर ((_IOC_सूची(cmd) & _IOC_WRITE) &&
	    copy_from_user(karg, uarg, _IOC_SIZE(cmd)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ copy_arg_to_user(व्योम __user *uarg, व्योम *karg, अचिन्हित पूर्णांक cmd)
अणु
	अगर ((_IOC_सूची(cmd) & _IOC_READ) &&
	    copy_to_user(uarg, karg, _IOC_SIZE(cmd)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* Do acquire the graph mutex */
#घोषणा MEDIA_IOC_FL_GRAPH_MUTEX	BIT(0)

#घोषणा MEDIA_IOC_ARG(__cmd, func, fl, from_user, to_user)		\
	[_IOC_NR(MEDIA_IOC_##__cmd)] = अणु				\
		.cmd = MEDIA_IOC_##__cmd,				\
		.fn = func,						\
		.flags = fl,						\
		.arg_from_user = from_user,				\
		.arg_to_user = to_user,					\
	पूर्ण

#घोषणा MEDIA_IOC(__cmd, func, fl)					\
	MEDIA_IOC_ARG(__cmd, func, fl, copy_arg_from_user, copy_arg_to_user)

/* the table is indexed by _IOC_NR(cmd) */
काष्ठा media_ioctl_info अणु
	अचिन्हित पूर्णांक cmd;
	अचिन्हित लघु flags;
	दीर्घ (*fn)(काष्ठा media_device *dev, व्योम *arg);
	दीर्घ (*arg_from_user)(व्योम *karg, व्योम __user *uarg, अचिन्हित पूर्णांक cmd);
	दीर्घ (*arg_to_user)(व्योम __user *uarg, व्योम *karg, अचिन्हित पूर्णांक cmd);
पूर्ण;

अटल स्थिर काष्ठा media_ioctl_info ioctl_info[] = अणु
	MEDIA_IOC(DEVICE_INFO, media_device_get_info, MEDIA_IOC_FL_GRAPH_MUTEX),
	MEDIA_IOC(ENUM_ENTITIES, media_device_क्रमागत_entities, MEDIA_IOC_FL_GRAPH_MUTEX),
	MEDIA_IOC(ENUM_LINKS, media_device_क्रमागत_links, MEDIA_IOC_FL_GRAPH_MUTEX),
	MEDIA_IOC(SETUP_LINK, media_device_setup_link, MEDIA_IOC_FL_GRAPH_MUTEX),
	MEDIA_IOC(G_TOPOLOGY, media_device_get_topology, MEDIA_IOC_FL_GRAPH_MUTEX),
	MEDIA_IOC(REQUEST_ALLOC, media_device_request_alloc, 0),
पूर्ण;

अटल दीर्घ media_device_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ __arg)
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);
	काष्ठा media_device *dev = devnode->media_dev;
	स्थिर काष्ठा media_ioctl_info *info;
	व्योम __user *arg = (व्योम __user *)__arg;
	अक्षर __karg[256], *karg = __karg;
	दीर्घ ret;

	अगर (_IOC_NR(cmd) >= ARRAY_SIZE(ioctl_info)
	    || ioctl_info[_IOC_NR(cmd)].cmd != cmd)
		वापस -ENOIOCTLCMD;

	info = &ioctl_info[_IOC_NR(cmd)];

	अगर (_IOC_SIZE(info->cmd) > माप(__karg)) अणु
		karg = kदो_स्मृति(_IOC_SIZE(info->cmd), GFP_KERNEL);
		अगर (!karg)
			वापस -ENOMEM;
	पूर्ण

	अगर (info->arg_from_user) अणु
		ret = info->arg_from_user(karg, arg, cmd);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	अगर (info->flags & MEDIA_IOC_FL_GRAPH_MUTEX)
		mutex_lock(&dev->graph_mutex);

	ret = info->fn(dev, karg);

	अगर (info->flags & MEDIA_IOC_FL_GRAPH_MUTEX)
		mutex_unlock(&dev->graph_mutex);

	अगर (!ret && info->arg_to_user)
		ret = info->arg_to_user(arg, karg, cmd);

out_मुक्त:
	अगर (karg != __karg)
		kमुक्त(karg);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा media_links_क्रमागत32 अणु
	__u32 entity;
	compat_uptr_t pads; /* काष्ठा media_pad_desc * */
	compat_uptr_t links; /* काष्ठा media_link_desc * */
	__u32 reserved[4];
पूर्ण;

अटल दीर्घ media_device_क्रमागत_links32(काष्ठा media_device *mdev,
				      काष्ठा media_links_क्रमागत32 __user *ulinks)
अणु
	काष्ठा media_links_क्रमागत links;
	compat_uptr_t pads_ptr, links_ptr;
	पूर्णांक ret;

	स_रखो(&links, 0, माप(links));

	अगर (get_user(links.entity, &ulinks->entity)
	    || get_user(pads_ptr, &ulinks->pads)
	    || get_user(links_ptr, &ulinks->links))
		वापस -EFAULT;

	links.pads = compat_ptr(pads_ptr);
	links.links = compat_ptr(links_ptr);

	ret = media_device_क्रमागत_links(mdev, &links);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(ulinks->reserved, links.reserved,
			 माप(ulinks->reserved)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

#घोषणा MEDIA_IOC_ENUM_LINKS32		_IOWR('|', 0x02, काष्ठा media_links_क्रमागत32)

अटल दीर्घ media_device_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ arg)
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);
	काष्ठा media_device *dev = devnode->media_dev;
	दीर्घ ret;

	चयन (cmd) अणु
	हाल MEDIA_IOC_ENUM_LINKS32:
		mutex_lock(&dev->graph_mutex);
		ret = media_device_क्रमागत_links32(dev,
				(काष्ठा media_links_क्रमागत32 __user *)arg);
		mutex_unlock(&dev->graph_mutex);
		अवरोध;

	शेष:
		वापस media_device_ioctl(filp, cmd, arg);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल स्थिर काष्ठा media_file_operations media_device_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = media_device_खोलो,
	.ioctl = media_device_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = media_device_compat_ioctl,
#पूर्ण_अगर /* CONFIG_COMPAT */
	.release = media_device_बंद,
पूर्ण;

/* -----------------------------------------------------------------------------
 * sysfs
 */

अटल sमाप_प्रकार show_model(काष्ठा device *cd,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा media_devnode *devnode = to_media_devnode(cd);
	काष्ठा media_device *mdev = devnode->media_dev;

	वापस प्र_लिखो(buf, "%.*s\n", (पूर्णांक)माप(mdev->model), mdev->model);
पूर्ण

अटल DEVICE_ATTR(model, S_IRUGO, show_model, शून्य);

/* -----------------------------------------------------------------------------
 * Registration/unregistration
 */

अटल व्योम media_device_release(काष्ठा media_devnode *devnode)
अणु
	dev_dbg(devnode->parent, "Media device released\n");
पूर्ण

अटल व्योम __media_device_unरेजिस्टर_entity(काष्ठा media_entity *entity)
अणु
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	काष्ठा media_link *link, *पंचांगp;
	काष्ठा media_पूर्णांकerface *पूर्णांकf;
	अचिन्हित पूर्णांक i;

	ida_मुक्त(&mdev->entity_पूर्णांकernal_idx, entity->पूर्णांकernal_idx);

	/* Remove all पूर्णांकerface links poपूर्णांकing to this entity */
	list_क्रम_each_entry(पूर्णांकf, &mdev->पूर्णांकerfaces, graph_obj.list) अणु
		list_क्रम_each_entry_safe(link, पंचांगp, &पूर्णांकf->links, list) अणु
			अगर (link->entity == entity)
				__media_हटाओ_पूर्णांकf_link(link);
		पूर्ण
	पूर्ण

	/* Remove all data links that beदीर्घ to this entity */
	__media_entity_हटाओ_links(entity);

	/* Remove all pads that beदीर्घ to this entity */
	क्रम (i = 0; i < entity->num_pads; i++)
		media_gobj_destroy(&entity->pads[i].graph_obj);

	/* Remove the entity */
	media_gobj_destroy(&entity->graph_obj);

	/* invoke entity_notअगरy callbacks to handle entity removal?? */

	entity->graph_obj.mdev = शून्य;
पूर्ण

/**
 * media_device_रेजिस्टर_entity - Register an entity with a media device
 * @mdev:	The media device
 * @entity:	The entity
 */
पूर्णांक __must_check media_device_रेजिस्टर_entity(काष्ठा media_device *mdev,
					      काष्ठा media_entity *entity)
अणु
	काष्ठा media_entity_notअगरy *notअगरy, *next;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (entity->function == MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN ||
	    entity->function == MEDIA_ENT_F_UNKNOWN)
		dev_warn(mdev->dev,
			 "Entity type for entity %s was not initialized!\n",
			 entity->name);

	/* Warn अगर we apparently re-रेजिस्टर an entity */
	WARN_ON(entity->graph_obj.mdev != शून्य);
	entity->graph_obj.mdev = mdev;
	INIT_LIST_HEAD(&entity->links);
	entity->num_links = 0;
	entity->num_backlinks = 0;

	ret = ida_alloc_min(&mdev->entity_पूर्णांकernal_idx, 1, GFP_KERNEL);
	अगर (ret < 0)
		वापस ret;
	entity->पूर्णांकernal_idx = ret;

	mutex_lock(&mdev->graph_mutex);
	mdev->entity_पूर्णांकernal_idx_max =
		max(mdev->entity_पूर्णांकernal_idx_max, entity->पूर्णांकernal_idx);

	/* Initialize media_gobj embedded at the entity */
	media_gobj_create(mdev, MEDIA_GRAPH_ENTITY, &entity->graph_obj);

	/* Initialize objects at the pads */
	क्रम (i = 0; i < entity->num_pads; i++)
		media_gobj_create(mdev, MEDIA_GRAPH_PAD,
			       &entity->pads[i].graph_obj);

	/* invoke entity_notअगरy callbacks */
	list_क्रम_each_entry_safe(notअगरy, next, &mdev->entity_notअगरy, list)
		notअगरy->notअगरy(entity, notअगरy->notअगरy_data);

	अगर (mdev->entity_पूर्णांकernal_idx_max
	    >= mdev->pm_count_walk.ent_क्रमागत.idx_max) अणु
		काष्ठा media_graph new = अणु .top = 0 पूर्ण;

		/*
		 * Initialise the new graph walk beक्रमe cleaning up
		 * the old one in order not to spoil the graph walk
		 * object of the media device अगर graph walk init fails.
		 */
		ret = media_graph_walk_init(&new, mdev);
		अगर (ret) अणु
			__media_device_unरेजिस्टर_entity(entity);
			mutex_unlock(&mdev->graph_mutex);
			वापस ret;
		पूर्ण
		media_graph_walk_cleanup(&mdev->pm_count_walk);
		mdev->pm_count_walk = new;
	पूर्ण
	mutex_unlock(&mdev->graph_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(media_device_रेजिस्टर_entity);

व्योम media_device_unरेजिस्टर_entity(काष्ठा media_entity *entity)
अणु
	काष्ठा media_device *mdev = entity->graph_obj.mdev;

	अगर (mdev == शून्य)
		वापस;

	mutex_lock(&mdev->graph_mutex);
	__media_device_unरेजिस्टर_entity(entity);
	mutex_unlock(&mdev->graph_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(media_device_unरेजिस्टर_entity);

/**
 * media_device_init() - initialize a media device
 * @mdev:	The media device
 *
 * The caller is responsible क्रम initializing the media device beक्रमe
 * registration. The following fields must be set:
 *
 * - dev must poपूर्णांक to the parent device
 * - model must be filled with the device model name
 */
व्योम media_device_init(काष्ठा media_device *mdev)
अणु
	INIT_LIST_HEAD(&mdev->entities);
	INIT_LIST_HEAD(&mdev->पूर्णांकerfaces);
	INIT_LIST_HEAD(&mdev->pads);
	INIT_LIST_HEAD(&mdev->links);
	INIT_LIST_HEAD(&mdev->entity_notअगरy);

	mutex_init(&mdev->req_queue_mutex);
	mutex_init(&mdev->graph_mutex);
	ida_init(&mdev->entity_पूर्णांकernal_idx);

	atomic_set(&mdev->request_id, 0);

	dev_dbg(mdev->dev, "Media device initialized\n");
पूर्ण
EXPORT_SYMBOL_GPL(media_device_init);

व्योम media_device_cleanup(काष्ठा media_device *mdev)
अणु
	ida_destroy(&mdev->entity_पूर्णांकernal_idx);
	mdev->entity_पूर्णांकernal_idx_max = 0;
	media_graph_walk_cleanup(&mdev->pm_count_walk);
	mutex_destroy(&mdev->graph_mutex);
	mutex_destroy(&mdev->req_queue_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(media_device_cleanup);

पूर्णांक __must_check __media_device_रेजिस्टर(काष्ठा media_device *mdev,
					 काष्ठा module *owner)
अणु
	काष्ठा media_devnode *devnode;
	पूर्णांक ret;

	devnode = kzalloc(माप(*devnode), GFP_KERNEL);
	अगर (!devnode)
		वापस -ENOMEM;

	/* Register the device node. */
	mdev->devnode = devnode;
	devnode->fops = &media_device_fops;
	devnode->parent = mdev->dev;
	devnode->release = media_device_release;

	/* Set version 0 to indicate user-space that the graph is अटल */
	mdev->topology_version = 0;

	ret = media_devnode_रेजिस्टर(mdev, devnode, owner);
	अगर (ret < 0) अणु
		/* devnode मुक्त is handled in media_devnode_*() */
		mdev->devnode = शून्य;
		वापस ret;
	पूर्ण

	ret = device_create_file(&devnode->dev, &dev_attr_model);
	अगर (ret < 0) अणु
		/* devnode मुक्त is handled in media_devnode_*() */
		mdev->devnode = शून्य;
		media_devnode_unरेजिस्टर_prepare(devnode);
		media_devnode_unरेजिस्टर(devnode);
		वापस ret;
	पूर्ण

	dev_dbg(mdev->dev, "Media device registered\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__media_device_रेजिस्टर);

पूर्णांक __must_check media_device_रेजिस्टर_entity_notअगरy(काष्ठा media_device *mdev,
					काष्ठा media_entity_notअगरy *nptr)
अणु
	mutex_lock(&mdev->graph_mutex);
	list_add_tail(&nptr->list, &mdev->entity_notअगरy);
	mutex_unlock(&mdev->graph_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(media_device_रेजिस्टर_entity_notअगरy);

/*
 * Note: Should be called with mdev->lock held.
 */
अटल व्योम __media_device_unरेजिस्टर_entity_notअगरy(काष्ठा media_device *mdev,
					काष्ठा media_entity_notअगरy *nptr)
अणु
	list_del(&nptr->list);
पूर्ण

व्योम media_device_unरेजिस्टर_entity_notअगरy(काष्ठा media_device *mdev,
					काष्ठा media_entity_notअगरy *nptr)
अणु
	mutex_lock(&mdev->graph_mutex);
	__media_device_unरेजिस्टर_entity_notअगरy(mdev, nptr);
	mutex_unlock(&mdev->graph_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(media_device_unरेजिस्टर_entity_notअगरy);

व्योम media_device_unरेजिस्टर(काष्ठा media_device *mdev)
अणु
	काष्ठा media_entity *entity;
	काष्ठा media_entity *next;
	काष्ठा media_पूर्णांकerface *पूर्णांकf, *पंचांगp_पूर्णांकf;
	काष्ठा media_entity_notअगरy *notअगरy, *nextp;

	अगर (mdev == शून्य)
		वापस;

	mutex_lock(&mdev->graph_mutex);

	/* Check अगर mdev was ever रेजिस्टरed at all */
	अगर (!media_devnode_is_रेजिस्टरed(mdev->devnode)) अणु
		mutex_unlock(&mdev->graph_mutex);
		वापस;
	पूर्ण

	/* Clear the devnode रेजिस्टर bit to aव्योम races with media dev खोलो */
	media_devnode_unरेजिस्टर_prepare(mdev->devnode);

	/* Remove all entities from the media device */
	list_क्रम_each_entry_safe(entity, next, &mdev->entities, graph_obj.list)
		__media_device_unरेजिस्टर_entity(entity);

	/* Remove all entity_notअगरy callbacks from the media device */
	list_क्रम_each_entry_safe(notअगरy, nextp, &mdev->entity_notअगरy, list)
		__media_device_unरेजिस्टर_entity_notअगरy(mdev, notअगरy);

	/* Remove all पूर्णांकerfaces from the media device */
	list_क्रम_each_entry_safe(पूर्णांकf, पंचांगp_पूर्णांकf, &mdev->पूर्णांकerfaces,
				 graph_obj.list) अणु
		/*
		 * Unlink the पूर्णांकerface, but करोn't मुक्त it here; the
		 * module which created it is responsible क्रम मुक्तing
		 * it
		 */
		__media_हटाओ_पूर्णांकf_links(पूर्णांकf);
		media_gobj_destroy(&पूर्णांकf->graph_obj);
	पूर्ण

	mutex_unlock(&mdev->graph_mutex);

	dev_dbg(mdev->dev, "Media device unregistered\n");

	device_हटाओ_file(&mdev->devnode->dev, &dev_attr_model);
	media_devnode_unरेजिस्टर(mdev->devnode);
	/* devnode मुक्त is handled in media_devnode_*() */
	mdev->devnode = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(media_device_unरेजिस्टर);

#अगर IS_ENABLED(CONFIG_PCI)
व्योम media_device_pci_init(काष्ठा media_device *mdev,
			   काष्ठा pci_dev *pci_dev,
			   स्थिर अक्षर *name)
अणु
	mdev->dev = &pci_dev->dev;

	अगर (name)
		strscpy(mdev->model, name, माप(mdev->model));
	अन्यथा
		strscpy(mdev->model, pci_name(pci_dev), माप(mdev->model));

	प्र_लिखो(mdev->bus_info, "PCI:%s", pci_name(pci_dev));

	mdev->hw_revision = (pci_dev->subप्रणाली_venकरोr << 16)
			    | pci_dev->subप्रणाली_device;

	media_device_init(mdev);
पूर्ण
EXPORT_SYMBOL_GPL(media_device_pci_init);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB)
व्योम __media_device_usb_init(काष्ठा media_device *mdev,
			     काष्ठा usb_device *udev,
			     स्थिर अक्षर *board_name,
			     स्थिर अक्षर *driver_name)
अणु
	mdev->dev = &udev->dev;

	अगर (driver_name)
		strscpy(mdev->driver_name, driver_name,
			माप(mdev->driver_name));

	अगर (board_name)
		strscpy(mdev->model, board_name, माप(mdev->model));
	अन्यथा अगर (udev->product)
		strscpy(mdev->model, udev->product, माप(mdev->model));
	अन्यथा
		strscpy(mdev->model, "unknown model", माप(mdev->model));
	अगर (udev->serial)
		strscpy(mdev->serial, udev->serial, माप(mdev->serial));
	usb_make_path(udev, mdev->bus_info, माप(mdev->bus_info));
	mdev->hw_revision = le16_to_cpu(udev->descriptor.bcdDevice);

	media_device_init(mdev);
पूर्ण
EXPORT_SYMBOL_GPL(__media_device_usb_init);
#पूर्ण_अगर


#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER */
