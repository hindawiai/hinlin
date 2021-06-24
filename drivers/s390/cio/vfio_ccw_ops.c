<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Physical device callbacks क्रम vfio_ccw
 *
 * Copyright IBM Corp. 2017
 * Copyright Red Hat, Inc. 2019
 *
 * Author(s): Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>
 *            Xiao Feng Ren <renxiaof@linux.vnet.ibm.com>
 *            Cornelia Huck <cohuck@redhat.com>
 */

#समावेश <linux/vfपन.स>
#समावेश <linux/mdev.h>
#समावेश <linux/nospec.h>
#समावेश <linux/slab.h>

#समावेश "vfio_ccw_private.h"

अटल पूर्णांक vfio_ccw_mdev_reset(काष्ठा mdev_device *mdev)
अणु
	काष्ठा vfio_ccw_निजी *निजी;
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	निजी = dev_get_drvdata(mdev_parent_dev(mdev));
	sch = निजी->sch;
	/*
	 * TODO:
	 * In the cureent stage, some things like "no I/O running" and "no
	 * पूर्णांकerrupt pending" are clear, but we are not sure what other state
	 * we need to care about.
	 * There are still a lot more inकाष्ठाions need to be handled. We
	 * should come back here later.
	 */
	ret = vfio_ccw_sch_quiesce(sch);
	अगर (ret)
		वापस ret;

	ret = cio_enable_subchannel(sch, (u32)(अचिन्हित दीर्घ)sch);
	अगर (!ret)
		निजी->state = VFIO_CCW_STATE_IDLE;

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_ccw_mdev_notअगरier(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ action,
				  व्योम *data)
अणु
	काष्ठा vfio_ccw_निजी *निजी =
		container_of(nb, काष्ठा vfio_ccw_निजी, nb);

	/*
	 * Venकरोr drivers MUST unpin pages in response to an
	 * invalidation.
	 */
	अगर (action == VFIO_IOMMU_NOTIFY_DMA_UNMAP) अणु
		काष्ठा vfio_iommu_type1_dma_unmap *unmap = data;

		अगर (!cp_iova_pinned(&निजी->cp, unmap->iova))
			वापस NOTIFY_OK;

		अगर (vfio_ccw_mdev_reset(निजी->mdev))
			वापस NOTIFY_BAD;

		cp_मुक्त(&निजी->cp);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा mdev_type *mtype,
			 काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "I/O subchannel (Non-QDIO)\n");
पूर्ण
अटल MDEV_TYPE_ATTR_RO(name);

अटल sमाप_प्रकार device_api_show(काष्ठा mdev_type *mtype,
			       काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", VFIO_DEVICE_API_CCW_STRING);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(device_api);

अटल sमाप_प्रकार available_instances_show(काष्ठा mdev_type *mtype,
					काष्ठा mdev_type_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा vfio_ccw_निजी *निजी =
		dev_get_drvdata(mtype_get_parent_dev(mtype));

	वापस प्र_लिखो(buf, "%d\n", atomic_पढ़ो(&निजी->avail));
पूर्ण
अटल MDEV_TYPE_ATTR_RO(available_instances);

अटल काष्ठा attribute *mdev_types_attrs[] = अणु
	&mdev_type_attr_name.attr,
	&mdev_type_attr_device_api.attr,
	&mdev_type_attr_available_instances.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group = अणु
	.name  = "io",
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group *mdev_type_groups[] = अणु
	&mdev_type_group,
	शून्य,
पूर्ण;

अटल पूर्णांक vfio_ccw_mdev_create(काष्ठा mdev_device *mdev)
अणु
	काष्ठा vfio_ccw_निजी *निजी =
		dev_get_drvdata(mdev_parent_dev(mdev));

	अगर (निजी->state == VFIO_CCW_STATE_NOT_OPER)
		वापस -ENODEV;

	अगर (atomic_dec_अगर_positive(&निजी->avail) < 0)
		वापस -EPERM;

	निजी->mdev = mdev;
	निजी->state = VFIO_CCW_STATE_IDLE;

	VFIO_CCW_MSG_EVENT(2, "mdev %pUl, sch %x.%x.%04x: create\n",
			   mdev_uuid(mdev), निजी->sch->schid.cssid,
			   निजी->sch->schid.ssid,
			   निजी->sch->schid.sch_no);

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_ccw_mdev_हटाओ(काष्ठा mdev_device *mdev)
अणु
	काष्ठा vfio_ccw_निजी *निजी =
		dev_get_drvdata(mdev_parent_dev(mdev));

	VFIO_CCW_MSG_EVENT(2, "mdev %pUl, sch %x.%x.%04x: remove\n",
			   mdev_uuid(mdev), निजी->sch->schid.cssid,
			   निजी->sch->schid.ssid,
			   निजी->sch->schid.sch_no);

	अगर ((निजी->state != VFIO_CCW_STATE_NOT_OPER) &&
	    (निजी->state != VFIO_CCW_STATE_STANDBY)) अणु
		अगर (!vfio_ccw_sch_quiesce(निजी->sch))
			निजी->state = VFIO_CCW_STATE_STANDBY;
		/* The state will be NOT_OPER on error. */
	पूर्ण

	cp_मुक्त(&निजी->cp);
	निजी->mdev = शून्य;
	atomic_inc(&निजी->avail);

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_ccw_mdev_खोलो(काष्ठा mdev_device *mdev)
अणु
	काष्ठा vfio_ccw_निजी *निजी =
		dev_get_drvdata(mdev_parent_dev(mdev));
	अचिन्हित दीर्घ events = VFIO_IOMMU_NOTIFY_DMA_UNMAP;
	पूर्णांक ret;

	निजी->nb.notअगरier_call = vfio_ccw_mdev_notअगरier;

	ret = vfio_रेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				     &events, &निजी->nb);
	अगर (ret)
		वापस ret;

	ret = vfio_ccw_रेजिस्टर_async_dev_regions(निजी);
	अगर (ret)
		जाओ out_unरेजिस्टर;

	ret = vfio_ccw_रेजिस्टर_schib_dev_regions(निजी);
	अगर (ret)
		जाओ out_unरेजिस्टर;

	ret = vfio_ccw_रेजिस्टर_crw_dev_regions(निजी);
	अगर (ret)
		जाओ out_unरेजिस्टर;

	वापस ret;

out_unरेजिस्टर:
	vfio_ccw_unरेजिस्टर_dev_regions(निजी);
	vfio_unरेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				 &निजी->nb);
	वापस ret;
पूर्ण

अटल व्योम vfio_ccw_mdev_release(काष्ठा mdev_device *mdev)
अणु
	काष्ठा vfio_ccw_निजी *निजी =
		dev_get_drvdata(mdev_parent_dev(mdev));

	अगर ((निजी->state != VFIO_CCW_STATE_NOT_OPER) &&
	    (निजी->state != VFIO_CCW_STATE_STANDBY)) अणु
		अगर (!vfio_ccw_mdev_reset(mdev))
			निजी->state = VFIO_CCW_STATE_STANDBY;
		/* The state will be NOT_OPER on error. */
	पूर्ण

	cp_मुक्त(&निजी->cp);
	vfio_ccw_unरेजिस्टर_dev_regions(निजी);
	vfio_unरेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				 &निजी->nb);
पूर्ण

अटल sमाप_प्रकार vfio_ccw_mdev_पढ़ो_io_region(काष्ठा vfio_ccw_निजी *निजी,
					    अक्षर __user *buf, माप_प्रकार count,
					    loff_t *ppos)
अणु
	loff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	काष्ठा ccw_io_region *region;
	पूर्णांक ret;

	अगर (pos + count > माप(*region))
		वापस -EINVAL;

	mutex_lock(&निजी->io_mutex);
	region = निजी->io_region;
	अगर (copy_to_user(buf, (व्योम *)region + pos, count))
		ret = -EFAULT;
	अन्यथा
		ret = count;
	mutex_unlock(&निजी->io_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार vfio_ccw_mdev_पढ़ो(काष्ठा mdev_device *mdev,
				  अक्षर __user *buf,
				  माप_प्रकार count,
				  loff_t *ppos)
अणु
	अचिन्हित पूर्णांक index = VFIO_CCW_OFFSET_TO_INDEX(*ppos);
	काष्ठा vfio_ccw_निजी *निजी;

	निजी = dev_get_drvdata(mdev_parent_dev(mdev));

	अगर (index >= VFIO_CCW_NUM_REGIONS + निजी->num_regions)
		वापस -EINVAL;

	चयन (index) अणु
	हाल VFIO_CCW_CONFIG_REGION_INDEX:
		वापस vfio_ccw_mdev_पढ़ो_io_region(निजी, buf, count, ppos);
	शेष:
		index -= VFIO_CCW_NUM_REGIONS;
		वापस निजी->region[index].ops->पढ़ो(निजी, buf, count,
							ppos);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार vfio_ccw_mdev_ग_लिखो_io_region(काष्ठा vfio_ccw_निजी *निजी,
					     स्थिर अक्षर __user *buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	loff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	काष्ठा ccw_io_region *region;
	पूर्णांक ret;

	अगर (pos + count > माप(*region))
		वापस -EINVAL;

	अगर (!mutex_trylock(&निजी->io_mutex))
		वापस -EAGAIN;

	region = निजी->io_region;
	अगर (copy_from_user((व्योम *)region + pos, buf, count)) अणु
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	vfio_ccw_fsm_event(निजी, VFIO_CCW_EVENT_IO_REQ);
	ret = (region->ret_code != 0) ? region->ret_code : count;

out_unlock:
	mutex_unlock(&निजी->io_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार vfio_ccw_mdev_ग_लिखो(काष्ठा mdev_device *mdev,
				   स्थिर अक्षर __user *buf,
				   माप_प्रकार count,
				   loff_t *ppos)
अणु
	अचिन्हित पूर्णांक index = VFIO_CCW_OFFSET_TO_INDEX(*ppos);
	काष्ठा vfio_ccw_निजी *निजी;

	निजी = dev_get_drvdata(mdev_parent_dev(mdev));

	अगर (index >= VFIO_CCW_NUM_REGIONS + निजी->num_regions)
		वापस -EINVAL;

	चयन (index) अणु
	हाल VFIO_CCW_CONFIG_REGION_INDEX:
		वापस vfio_ccw_mdev_ग_लिखो_io_region(निजी, buf, count, ppos);
	शेष:
		index -= VFIO_CCW_NUM_REGIONS;
		वापस निजी->region[index].ops->ग_लिखो(निजी, buf, count,
							 ppos);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vfio_ccw_mdev_get_device_info(काष्ठा vfio_device_info *info,
					 काष्ठा mdev_device *mdev)
अणु
	काष्ठा vfio_ccw_निजी *निजी;

	निजी = dev_get_drvdata(mdev_parent_dev(mdev));
	info->flags = VFIO_DEVICE_FLAGS_CCW | VFIO_DEVICE_FLAGS_RESET;
	info->num_regions = VFIO_CCW_NUM_REGIONS + निजी->num_regions;
	info->num_irqs = VFIO_CCW_NUM_IRQS;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_ccw_mdev_get_region_info(काष्ठा vfio_region_info *info,
					 काष्ठा mdev_device *mdev,
					 अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_ccw_निजी *निजी;
	पूर्णांक i;

	निजी = dev_get_drvdata(mdev_parent_dev(mdev));
	चयन (info->index) अणु
	हाल VFIO_CCW_CONFIG_REGION_INDEX:
		info->offset = 0;
		info->size = माप(काष्ठा ccw_io_region);
		info->flags = VFIO_REGION_INFO_FLAG_READ
			      | VFIO_REGION_INFO_FLAG_WRITE;
		वापस 0;
	शेष: /* all other regions are handled via capability chain */
	अणु
		काष्ठा vfio_info_cap caps = अणु .buf = शून्य, .size = 0 पूर्ण;
		काष्ठा vfio_region_info_cap_type cap_type = अणु
			.header.id = VFIO_REGION_INFO_CAP_TYPE,
			.header.version = 1 पूर्ण;
		पूर्णांक ret;

		अगर (info->index >=
		    VFIO_CCW_NUM_REGIONS + निजी->num_regions)
			वापस -EINVAL;

		info->index = array_index_nospec(info->index,
						 VFIO_CCW_NUM_REGIONS +
						 निजी->num_regions);

		i = info->index - VFIO_CCW_NUM_REGIONS;

		info->offset = VFIO_CCW_INDEX_TO_OFFSET(info->index);
		info->size = निजी->region[i].size;
		info->flags = निजी->region[i].flags;

		cap_type.type = निजी->region[i].type;
		cap_type.subtype = निजी->region[i].subtype;

		ret = vfio_info_add_capability(&caps, &cap_type.header,
					       माप(cap_type));
		अगर (ret)
			वापस ret;

		info->flags |= VFIO_REGION_INFO_FLAG_CAPS;
		अगर (info->argsz < माप(*info) + caps.size) अणु
			info->argsz = माप(*info) + caps.size;
			info->cap_offset = 0;
		पूर्ण अन्यथा अणु
			vfio_info_cap_shअगरt(&caps, माप(*info));
			अगर (copy_to_user((व्योम __user *)arg + माप(*info),
					 caps.buf, caps.size)) अणु
				kमुक्त(caps.buf);
				वापस -EFAULT;
			पूर्ण
			info->cap_offset = माप(*info);
		पूर्ण

		kमुक्त(caps.buf);

	पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_ccw_mdev_get_irq_info(काष्ठा vfio_irq_info *info)
अणु
	चयन (info->index) अणु
	हाल VFIO_CCW_IO_IRQ_INDEX:
	हाल VFIO_CCW_CRW_IRQ_INDEX:
	हाल VFIO_CCW_REQ_IRQ_INDEX:
		info->count = 1;
		info->flags = VFIO_IRQ_INFO_EVENTFD;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_ccw_mdev_set_irqs(काष्ठा mdev_device *mdev,
				  uपूर्णांक32_t flags,
				  uपूर्णांक32_t index,
				  व्योम __user *data)
अणु
	काष्ठा vfio_ccw_निजी *निजी;
	काष्ठा eventfd_ctx **ctx;

	अगर (!(flags & VFIO_IRQ_SET_ACTION_TRIGGER))
		वापस -EINVAL;

	निजी = dev_get_drvdata(mdev_parent_dev(mdev));

	चयन (index) अणु
	हाल VFIO_CCW_IO_IRQ_INDEX:
		ctx = &निजी->io_trigger;
		अवरोध;
	हाल VFIO_CCW_CRW_IRQ_INDEX:
		ctx = &निजी->crw_trigger;
		अवरोध;
	हाल VFIO_CCW_REQ_IRQ_INDEX:
		ctx = &निजी->req_trigger;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (flags & VFIO_IRQ_SET_DATA_TYPE_MASK) अणु
	हाल VFIO_IRQ_SET_DATA_NONE:
	अणु
		अगर (*ctx)
			eventfd_संकेत(*ctx, 1);
		वापस 0;
	पूर्ण
	हाल VFIO_IRQ_SET_DATA_BOOL:
	अणु
		uपूर्णांक8_t trigger;

		अगर (get_user(trigger, (uपूर्णांक8_t __user *)data))
			वापस -EFAULT;

		अगर (trigger && *ctx)
			eventfd_संकेत(*ctx, 1);
		वापस 0;
	पूर्ण
	हाल VFIO_IRQ_SET_DATA_EVENTFD:
	अणु
		पूर्णांक32_t fd;

		अगर (get_user(fd, (पूर्णांक32_t __user *)data))
			वापस -EFAULT;

		अगर (fd == -1) अणु
			अगर (*ctx)
				eventfd_ctx_put(*ctx);
			*ctx = शून्य;
		पूर्ण अन्यथा अगर (fd >= 0) अणु
			काष्ठा eventfd_ctx *efdctx;

			efdctx = eventfd_ctx_fdget(fd);
			अगर (IS_ERR(efdctx))
				वापस PTR_ERR(efdctx);

			अगर (*ctx)
				eventfd_ctx_put(*ctx);

			*ctx = efdctx;
		पूर्ण अन्यथा
			वापस -EINVAL;

		वापस 0;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक vfio_ccw_रेजिस्टर_dev_region(काष्ठा vfio_ccw_निजी *निजी,
				 अचिन्हित पूर्णांक subtype,
				 स्थिर काष्ठा vfio_ccw_regops *ops,
				 माप_प्रकार size, u32 flags, व्योम *data)
अणु
	काष्ठा vfio_ccw_region *region;

	region = kपुनः_स्मृति(निजी->region,
			  (निजी->num_regions + 1) * माप(*region),
			  GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	निजी->region = region;
	निजी->region[निजी->num_regions].type = VFIO_REGION_TYPE_CCW;
	निजी->region[निजी->num_regions].subtype = subtype;
	निजी->region[निजी->num_regions].ops = ops;
	निजी->region[निजी->num_regions].size = size;
	निजी->region[निजी->num_regions].flags = flags;
	निजी->region[निजी->num_regions].data = data;

	निजी->num_regions++;

	वापस 0;
पूर्ण

व्योम vfio_ccw_unरेजिस्टर_dev_regions(काष्ठा vfio_ccw_निजी *निजी)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < निजी->num_regions; i++)
		निजी->region[i].ops->release(निजी, &निजी->region[i]);
	निजी->num_regions = 0;
	kमुक्त(निजी->region);
	निजी->region = शून्य;
पूर्ण

अटल sमाप_प्रकार vfio_ccw_mdev_ioctl(काष्ठा mdev_device *mdev,
				   अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ minsz;

	चयन (cmd) अणु
	हाल VFIO_DEVICE_GET_INFO:
	अणु
		काष्ठा vfio_device_info info;

		minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		ret = vfio_ccw_mdev_get_device_info(&info, mdev);
		अगर (ret)
			वापस ret;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ? -EFAULT : 0;
	पूर्ण
	हाल VFIO_DEVICE_GET_REGION_INFO:
	अणु
		काष्ठा vfio_region_info info;

		minsz = दुरत्वend(काष्ठा vfio_region_info, offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		ret = vfio_ccw_mdev_get_region_info(&info, mdev, arg);
		अगर (ret)
			वापस ret;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ? -EFAULT : 0;
	पूर्ण
	हाल VFIO_DEVICE_GET_IRQ_INFO:
	अणु
		काष्ठा vfio_irq_info info;

		minsz = दुरत्वend(काष्ठा vfio_irq_info, count);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz || info.index >= VFIO_CCW_NUM_IRQS)
			वापस -EINVAL;

		ret = vfio_ccw_mdev_get_irq_info(&info);
		अगर (ret)
			वापस ret;

		अगर (info.count == -1)
			वापस -EINVAL;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ? -EFAULT : 0;
	पूर्ण
	हाल VFIO_DEVICE_SET_IRQS:
	अणु
		काष्ठा vfio_irq_set hdr;
		माप_प्रकार data_size;
		व्योम __user *data;

		minsz = दुरत्वend(काष्ठा vfio_irq_set, count);

		अगर (copy_from_user(&hdr, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		ret = vfio_set_irqs_validate_and_prepare(&hdr, 1,
							 VFIO_CCW_NUM_IRQS,
							 &data_size);
		अगर (ret)
			वापस ret;

		data = (व्योम __user *)(arg + minsz);
		वापस vfio_ccw_mdev_set_irqs(mdev, hdr.flags, hdr.index, data);
	पूर्ण
	हाल VFIO_DEVICE_RESET:
		वापस vfio_ccw_mdev_reset(mdev);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/* Request removal of the device*/
अटल व्योम vfio_ccw_mdev_request(काष्ठा mdev_device *mdev, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vfio_ccw_निजी *निजी = dev_get_drvdata(mdev_parent_dev(mdev));

	अगर (!निजी)
		वापस;

	अगर (निजी->req_trigger) अणु
		अगर (!(count % 10))
			dev_notice_ratelimited(mdev_dev(निजी->mdev),
					       "Relaying device request to user (#%u)\n",
					       count);

		eventfd_संकेत(निजी->req_trigger, 1);
	पूर्ण अन्यथा अगर (count == 0) अणु
		dev_notice(mdev_dev(निजी->mdev),
			   "No device request channel registered, blocked until released by user\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mdev_parent_ops vfio_ccw_mdev_ops = अणु
	.owner			= THIS_MODULE,
	.supported_type_groups  = mdev_type_groups,
	.create			= vfio_ccw_mdev_create,
	.हटाओ			= vfio_ccw_mdev_हटाओ,
	.खोलो			= vfio_ccw_mdev_खोलो,
	.release		= vfio_ccw_mdev_release,
	.पढ़ो			= vfio_ccw_mdev_पढ़ो,
	.ग_लिखो			= vfio_ccw_mdev_ग_लिखो,
	.ioctl			= vfio_ccw_mdev_ioctl,
	.request		= vfio_ccw_mdev_request,
पूर्ण;

पूर्णांक vfio_ccw_mdev_reg(काष्ठा subchannel *sch)
अणु
	वापस mdev_रेजिस्टर_device(&sch->dev, &vfio_ccw_mdev_ops);
पूर्ण

व्योम vfio_ccw_mdev_unreg(काष्ठा subchannel *sch)
अणु
	mdev_unरेजिस्टर_device(&sch->dev);
पूर्ण
