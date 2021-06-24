<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Manager Core
 *
 *  Copyright (C) 2013-2015 Altera Corporation
 *  Copyright (C) 2017 Intel Corporation
 *
 * With code from the mailing list:
 * Copyright (C) 2013 Xilinx, Inc.
 */
#समावेश <linux/firmware.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/idr.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>

अटल DEFINE_IDA(fpga_mgr_ida);
अटल काष्ठा class *fpga_mgr_class;

काष्ठा fpga_mgr_devres अणु
	काष्ठा fpga_manager *mgr;
पूर्ण;

/**
 * fpga_image_info_alloc - Allocate a FPGA image info काष्ठा
 * @dev: owning device
 *
 * Return: काष्ठा fpga_image_info or शून्य
 */
काष्ठा fpga_image_info *fpga_image_info_alloc(काष्ठा device *dev)
अणु
	काष्ठा fpga_image_info *info;

	get_device(dev);

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		put_device(dev);
		वापस शून्य;
	पूर्ण

	info->dev = dev;

	वापस info;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_image_info_alloc);

/**
 * fpga_image_info_मुक्त - Free a FPGA image info काष्ठा
 * @info: FPGA image info काष्ठा to मुक्त
 */
व्योम fpga_image_info_मुक्त(काष्ठा fpga_image_info *info)
अणु
	काष्ठा device *dev;

	अगर (!info)
		वापस;

	dev = info->dev;
	अगर (info->firmware_name)
		devm_kमुक्त(dev, info->firmware_name);

	devm_kमुक्त(dev, info);
	put_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_image_info_मुक्त);

/*
 * Call the low level driver's ग_लिखो_init function.  This will करो the
 * device-specअगरic things to get the FPGA पूर्णांकo the state where it is पढ़ोy to
 * receive an FPGA image. The low level driver only माला_लो to see the first
 * initial_header_size bytes in the buffer.
 */
अटल पूर्णांक fpga_mgr_ग_लिखो_init_buf(काष्ठा fpga_manager *mgr,
				   काष्ठा fpga_image_info *info,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	mgr->state = FPGA_MGR_STATE_WRITE_INIT;
	अगर (!mgr->mops->initial_header_size)
		ret = mgr->mops->ग_लिखो_init(mgr, info, शून्य, 0);
	अन्यथा
		ret = mgr->mops->ग_लिखो_init(
		    mgr, info, buf, min(mgr->mops->initial_header_size, count));

	अगर (ret) अणु
		dev_err(&mgr->dev, "Error preparing FPGA for writing\n");
		mgr->state = FPGA_MGR_STATE_WRITE_INIT_ERR;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fpga_mgr_ग_लिखो_init_sg(काष्ठा fpga_manager *mgr,
				  काष्ठा fpga_image_info *info,
				  काष्ठा sg_table *sgt)
अणु
	काष्ठा sg_mapping_iter miter;
	माप_प्रकार len;
	अक्षर *buf;
	पूर्णांक ret;

	अगर (!mgr->mops->initial_header_size)
		वापस fpga_mgr_ग_लिखो_init_buf(mgr, info, शून्य, 0);

	/*
	 * First try to use miter to map the first fragment to access the
	 * header, this is the typical path.
	 */
	sg_miter_start(&miter, sgt->sgl, sgt->nents, SG_MITER_FROM_SG);
	अगर (sg_miter_next(&miter) &&
	    miter.length >= mgr->mops->initial_header_size) अणु
		ret = fpga_mgr_ग_लिखो_init_buf(mgr, info, miter.addr,
					      miter.length);
		sg_miter_stop(&miter);
		वापस ret;
	पूर्ण
	sg_miter_stop(&miter);

	/* Otherwise copy the fragments पूर्णांकo temporary memory. */
	buf = kदो_स्मृति(mgr->mops->initial_header_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len = sg_copy_to_buffer(sgt->sgl, sgt->nents, buf,
				mgr->mops->initial_header_size);
	ret = fpga_mgr_ग_लिखो_init_buf(mgr, info, buf, len);

	kमुक्त(buf);

	वापस ret;
पूर्ण

/*
 * After all the FPGA image has been written, करो the device specअगरic steps to
 * finish and set the FPGA पूर्णांकo operating mode.
 */
अटल पूर्णांक fpga_mgr_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				   काष्ठा fpga_image_info *info)
अणु
	पूर्णांक ret;

	mgr->state = FPGA_MGR_STATE_WRITE_COMPLETE;
	ret = mgr->mops->ग_लिखो_complete(mgr, info);
	अगर (ret) अणु
		dev_err(&mgr->dev, "Error after writing image data to FPGA\n");
		mgr->state = FPGA_MGR_STATE_WRITE_COMPLETE_ERR;
		वापस ret;
	पूर्ण
	mgr->state = FPGA_MGR_STATE_OPERATING;

	वापस 0;
पूर्ण

/**
 * fpga_mgr_buf_load_sg - load fpga from image in buffer from a scatter list
 * @mgr:	fpga manager
 * @info:	fpga image specअगरic inक्रमmation
 * @sgt:	scatterlist table
 *
 * Step the low level fpga manager through the device-specअगरic steps of getting
 * an FPGA पढ़ोy to be configured, writing the image to it, then करोing whatever
 * post-configuration steps necessary.  This code assumes the caller got the
 * mgr poपूर्णांकer from of_fpga_mgr_get() or fpga_mgr_get() and checked that it is
 * not an error code.
 *
 * This is the preferred entry poपूर्णांक क्रम FPGA programming, it करोes not require
 * any contiguous kernel memory.
 *
 * Return: 0 on success, negative error code otherwise.
 */
अटल पूर्णांक fpga_mgr_buf_load_sg(काष्ठा fpga_manager *mgr,
				काष्ठा fpga_image_info *info,
				काष्ठा sg_table *sgt)
अणु
	पूर्णांक ret;

	ret = fpga_mgr_ग_लिखो_init_sg(mgr, info, sgt);
	अगर (ret)
		वापस ret;

	/* Write the FPGA image to the FPGA. */
	mgr->state = FPGA_MGR_STATE_WRITE;
	अगर (mgr->mops->ग_लिखो_sg) अणु
		ret = mgr->mops->ग_लिखो_sg(mgr, sgt);
	पूर्ण अन्यथा अणु
		काष्ठा sg_mapping_iter miter;

		sg_miter_start(&miter, sgt->sgl, sgt->nents, SG_MITER_FROM_SG);
		जबतक (sg_miter_next(&miter)) अणु
			ret = mgr->mops->ग_लिखो(mgr, miter.addr, miter.length);
			अगर (ret)
				अवरोध;
		पूर्ण
		sg_miter_stop(&miter);
	पूर्ण

	अगर (ret) अणु
		dev_err(&mgr->dev, "Error while writing image data to FPGA\n");
		mgr->state = FPGA_MGR_STATE_WRITE_ERR;
		वापस ret;
	पूर्ण

	वापस fpga_mgr_ग_लिखो_complete(mgr, info);
पूर्ण

अटल पूर्णांक fpga_mgr_buf_load_mapped(काष्ठा fpga_manager *mgr,
				    काष्ठा fpga_image_info *info,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = fpga_mgr_ग_लिखो_init_buf(mgr, info, buf, count);
	अगर (ret)
		वापस ret;

	/*
	 * Write the FPGA image to the FPGA.
	 */
	mgr->state = FPGA_MGR_STATE_WRITE;
	ret = mgr->mops->ग_लिखो(mgr, buf, count);
	अगर (ret) अणु
		dev_err(&mgr->dev, "Error while writing image data to FPGA\n");
		mgr->state = FPGA_MGR_STATE_WRITE_ERR;
		वापस ret;
	पूर्ण

	वापस fpga_mgr_ग_लिखो_complete(mgr, info);
पूर्ण

/**
 * fpga_mgr_buf_load - load fpga from image in buffer
 * @mgr:	fpga manager
 * @info:	fpga image info
 * @buf:	buffer contain fpga image
 * @count:	byte count of buf
 *
 * Step the low level fpga manager through the device-specअगरic steps of getting
 * an FPGA पढ़ोy to be configured, writing the image to it, then करोing whatever
 * post-configuration steps necessary.  This code assumes the caller got the
 * mgr poपूर्णांकer from of_fpga_mgr_get() and checked that it is not an error code.
 *
 * Return: 0 on success, negative error code otherwise.
 */
अटल पूर्णांक fpga_mgr_buf_load(काष्ठा fpga_manager *mgr,
			     काष्ठा fpga_image_info *info,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा page **pages;
	काष्ठा sg_table sgt;
	स्थिर व्योम *p;
	पूर्णांक nr_pages;
	पूर्णांक index;
	पूर्णांक rc;

	/*
	 * This is just a fast path अगर the caller has alपढ़ोy created a
	 * contiguous kernel buffer and the driver करोesn't require SG, non-SG
	 * drivers will still work on the slow path.
	 */
	अगर (mgr->mops->ग_लिखो)
		वापस fpga_mgr_buf_load_mapped(mgr, info, buf, count);

	/*
	 * Convert the linear kernel poपूर्णांकer पूर्णांकo a sg_table of pages क्रम use
	 * by the driver.
	 */
	nr_pages = DIV_ROUND_UP((अचिन्हित दीर्घ)buf + count, PAGE_SIZE) -
		   (अचिन्हित दीर्घ)buf / PAGE_SIZE;
	pages = kदो_स्मृति_array(nr_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	p = buf - offset_in_page(buf);
	क्रम (index = 0; index < nr_pages; index++) अणु
		अगर (is_vदो_स्मृति_addr(p))
			pages[index] = vदो_स्मृति_to_page(p);
		अन्यथा
			pages[index] = kmap_to_page((व्योम *)p);
		अगर (!pages[index]) अणु
			kमुक्त(pages);
			वापस -EFAULT;
		पूर्ण
		p += PAGE_SIZE;
	पूर्ण

	/*
	 * The temporary pages list is used to code share the merging algorithm
	 * in sg_alloc_table_from_pages
	 */
	rc = sg_alloc_table_from_pages(&sgt, pages, index, offset_in_page(buf),
				       count, GFP_KERNEL);
	kमुक्त(pages);
	अगर (rc)
		वापस rc;

	rc = fpga_mgr_buf_load_sg(mgr, info, &sgt);
	sg_मुक्त_table(&sgt);

	वापस rc;
पूर्ण

/**
 * fpga_mgr_firmware_load - request firmware and load to fpga
 * @mgr:	fpga manager
 * @info:	fpga image specअगरic inक्रमmation
 * @image_name:	name of image file on the firmware search path
 *
 * Request an FPGA image using the firmware class, then ग_लिखो out to the FPGA.
 * Update the state beक्रमe each step to provide info on what step failed अगर
 * there is a failure.  This code assumes the caller got the mgr poपूर्णांकer
 * from of_fpga_mgr_get() or fpga_mgr_get() and checked that it is not an error
 * code.
 *
 * Return: 0 on success, negative error code otherwise.
 */
अटल पूर्णांक fpga_mgr_firmware_load(काष्ठा fpga_manager *mgr,
				  काष्ठा fpga_image_info *info,
				  स्थिर अक्षर *image_name)
अणु
	काष्ठा device *dev = &mgr->dev;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	dev_info(dev, "writing %s to %s\n", image_name, mgr->name);

	mgr->state = FPGA_MGR_STATE_FIRMWARE_REQ;

	ret = request_firmware(&fw, image_name, dev);
	अगर (ret) अणु
		mgr->state = FPGA_MGR_STATE_FIRMWARE_REQ_ERR;
		dev_err(dev, "Error requesting firmware %s\n", image_name);
		वापस ret;
	पूर्ण

	ret = fpga_mgr_buf_load(mgr, info, fw->data, fw->size);

	release_firmware(fw);

	वापस ret;
पूर्ण

/**
 * fpga_mgr_load - load FPGA from scatter/gather table, buffer, or firmware
 * @mgr:	fpga manager
 * @info:	fpga image inक्रमmation.
 *
 * Load the FPGA from an image which is indicated in @info.  If successful, the
 * FPGA ends up in operating mode.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक fpga_mgr_load(काष्ठा fpga_manager *mgr, काष्ठा fpga_image_info *info)
अणु
	अगर (info->sgt)
		वापस fpga_mgr_buf_load_sg(mgr, info, info->sgt);
	अगर (info->buf && info->count)
		वापस fpga_mgr_buf_load(mgr, info, info->buf, info->count);
	अगर (info->firmware_name)
		वापस fpga_mgr_firmware_load(mgr, info, info->firmware_name);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_load);

अटल स्थिर अक्षर * स्थिर state_str[] = अणु
	[FPGA_MGR_STATE_UNKNOWN] =		"unknown",
	[FPGA_MGR_STATE_POWER_OFF] =		"power off",
	[FPGA_MGR_STATE_POWER_UP] =		"power up",
	[FPGA_MGR_STATE_RESET] =		"reset",

	/* requesting FPGA image from firmware */
	[FPGA_MGR_STATE_FIRMWARE_REQ] =		"firmware request",
	[FPGA_MGR_STATE_FIRMWARE_REQ_ERR] =	"firmware request error",

	/* Preparing FPGA to receive image */
	[FPGA_MGR_STATE_WRITE_INIT] =		"write init",
	[FPGA_MGR_STATE_WRITE_INIT_ERR] =	"write init error",

	/* Writing image to FPGA */
	[FPGA_MGR_STATE_WRITE] =		"write",
	[FPGA_MGR_STATE_WRITE_ERR] =		"write error",

	/* Finishing configuration after image has been written */
	[FPGA_MGR_STATE_WRITE_COMPLETE] =	"write complete",
	[FPGA_MGR_STATE_WRITE_COMPLETE_ERR] =	"write complete error",

	/* FPGA reports to be in normal operating mode */
	[FPGA_MGR_STATE_OPERATING] =		"operating",
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fpga_manager *mgr = to_fpga_manager(dev);

	वापस प्र_लिखो(buf, "%s\n", mgr->name);
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fpga_manager *mgr = to_fpga_manager(dev);

	वापस प्र_लिखो(buf, "%s\n", state_str[mgr->state]);
पूर्ण

अटल sमाप_प्रकार status_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fpga_manager *mgr = to_fpga_manager(dev);
	u64 status;
	पूर्णांक len = 0;

	अगर (!mgr->mops->status)
		वापस -ENOENT;

	status = mgr->mops->status(mgr);

	अगर (status & FPGA_MGR_STATUS_OPERATION_ERR)
		len += प्र_लिखो(buf + len, "reconfig operation error\n");
	अगर (status & FPGA_MGR_STATUS_CRC_ERR)
		len += प्र_लिखो(buf + len, "reconfig CRC error\n");
	अगर (status & FPGA_MGR_STATUS_INCOMPATIBLE_IMAGE_ERR)
		len += प्र_लिखो(buf + len, "reconfig incompatible image\n");
	अगर (status & FPGA_MGR_STATUS_IP_PROTOCOL_ERR)
		len += प्र_लिखो(buf + len, "reconfig IP protocol error\n");
	अगर (status & FPGA_MGR_STATUS_FIFO_OVERFLOW_ERR)
		len += प्र_लिखो(buf + len, "reconfig fifo overflow error\n");

	वापस len;
पूर्ण

अटल DEVICE_ATTR_RO(name);
अटल DEVICE_ATTR_RO(state);
अटल DEVICE_ATTR_RO(status);

अटल काष्ठा attribute *fpga_mgr_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_state.attr,
	&dev_attr_status.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(fpga_mgr);

अटल काष्ठा fpga_manager *__fpga_mgr_get(काष्ठा device *dev)
अणु
	काष्ठा fpga_manager *mgr;

	mgr = to_fpga_manager(dev);

	अगर (!try_module_get(dev->parent->driver->owner))
		जाओ err_dev;

	वापस mgr;

err_dev:
	put_device(dev);
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक fpga_mgr_dev_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस dev->parent == data;
पूर्ण

/**
 * fpga_mgr_get - Given a device, get a reference to a fpga mgr.
 * @dev:	parent device that fpga mgr was रेजिस्टरed with
 *
 * Return: fpga manager काष्ठा or IS_ERR() condition containing error code.
 */
काष्ठा fpga_manager *fpga_mgr_get(काष्ठा device *dev)
अणु
	काष्ठा device *mgr_dev = class_find_device(fpga_mgr_class, शून्य, dev,
						   fpga_mgr_dev_match);
	अगर (!mgr_dev)
		वापस ERR_PTR(-ENODEV);

	वापस __fpga_mgr_get(mgr_dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_get);

/**
 * of_fpga_mgr_get - Given a device node, get a reference to a fpga mgr.
 *
 * @node:	device node
 *
 * Return: fpga manager काष्ठा or IS_ERR() condition containing error code.
 */
काष्ठा fpga_manager *of_fpga_mgr_get(काष्ठा device_node *node)
अणु
	काष्ठा device *dev;

	dev = class_find_device_by_of_node(fpga_mgr_class, node);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	वापस __fpga_mgr_get(dev);
पूर्ण
EXPORT_SYMBOL_GPL(of_fpga_mgr_get);

/**
 * fpga_mgr_put - release a reference to a fpga manager
 * @mgr:	fpga manager काष्ठाure
 */
व्योम fpga_mgr_put(काष्ठा fpga_manager *mgr)
अणु
	module_put(mgr->dev.parent->driver->owner);
	put_device(&mgr->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_put);

/**
 * fpga_mgr_lock - Lock FPGA manager क्रम exclusive use
 * @mgr:	fpga manager
 *
 * Given a poपूर्णांकer to FPGA Manager (from fpga_mgr_get() or
 * of_fpga_mgr_put()) attempt to get the mutex. The user should call
 * fpga_mgr_lock() and verअगरy that it वापसs 0 beक्रमe attempting to
 * program the FPGA.  Likewise, the user should call fpga_mgr_unlock
 * when करोne programming the FPGA.
 *
 * Return: 0 क्रम success or -EBUSY
 */
पूर्णांक fpga_mgr_lock(काष्ठा fpga_manager *mgr)
अणु
	अगर (!mutex_trylock(&mgr->ref_mutex)) अणु
		dev_err(&mgr->dev, "FPGA manager is in use.\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_lock);

/**
 * fpga_mgr_unlock - Unlock FPGA manager after करोne programming
 * @mgr:	fpga manager
 */
व्योम fpga_mgr_unlock(काष्ठा fpga_manager *mgr)
अणु
	mutex_unlock(&mgr->ref_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_unlock);

/**
 * fpga_mgr_create - create and initialize a FPGA manager काष्ठा
 * @dev:	fpga manager device from pdev
 * @name:	fpga manager name
 * @mops:	poपूर्णांकer to काष्ठाure of fpga manager ops
 * @priv:	fpga manager निजी data
 *
 * The caller of this function is responsible क्रम मुक्तing the काष्ठा with
 * fpga_mgr_मुक्त().  Using devm_fpga_mgr_create() instead is recommended.
 *
 * Return: poपूर्णांकer to काष्ठा fpga_manager or शून्य
 */
काष्ठा fpga_manager *fpga_mgr_create(काष्ठा device *dev, स्थिर अक्षर *name,
				     स्थिर काष्ठा fpga_manager_ops *mops,
				     व्योम *priv)
अणु
	काष्ठा fpga_manager *mgr;
	पूर्णांक id, ret;

	अगर (!mops || !mops->ग_लिखो_complete || !mops->state ||
	    !mops->ग_लिखो_init || (!mops->ग_लिखो && !mops->ग_लिखो_sg) ||
	    (mops->ग_लिखो && mops->ग_लिखो_sg)) अणु
		dev_err(dev, "Attempt to register without fpga_manager_ops\n");
		वापस शून्य;
	पूर्ण

	अगर (!name || !म_माप(name)) अणु
		dev_err(dev, "Attempt to register with no name!\n");
		वापस शून्य;
	पूर्ण

	mgr = kzalloc(माप(*mgr), GFP_KERNEL);
	अगर (!mgr)
		वापस शून्य;

	id = ida_simple_get(&fpga_mgr_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		जाओ error_kमुक्त;

	mutex_init(&mgr->ref_mutex);

	mgr->name = name;
	mgr->mops = mops;
	mgr->priv = priv;

	device_initialize(&mgr->dev);
	mgr->dev.class = fpga_mgr_class;
	mgr->dev.groups = mops->groups;
	mgr->dev.parent = dev;
	mgr->dev.of_node = dev->of_node;
	mgr->dev.id = id;

	ret = dev_set_name(&mgr->dev, "fpga%d", id);
	अगर (ret)
		जाओ error_device;

	वापस mgr;

error_device:
	ida_simple_हटाओ(&fpga_mgr_ida, id);
error_kमुक्त:
	kमुक्त(mgr);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_create);

/**
 * fpga_mgr_मुक्त - मुक्त a FPGA manager created with fpga_mgr_create()
 * @mgr:	fpga manager काष्ठा
 */
व्योम fpga_mgr_मुक्त(काष्ठा fpga_manager *mgr)
अणु
	ida_simple_हटाओ(&fpga_mgr_ida, mgr->dev.id);
	kमुक्त(mgr);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_मुक्त);

अटल व्योम devm_fpga_mgr_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा fpga_mgr_devres *dr = res;

	fpga_mgr_मुक्त(dr->mgr);
पूर्ण

/**
 * devm_fpga_mgr_create - create and initialize a managed FPGA manager काष्ठा
 * @dev:	fpga manager device from pdev
 * @name:	fpga manager name
 * @mops:	poपूर्णांकer to काष्ठाure of fpga manager ops
 * @priv:	fpga manager निजी data
 *
 * This function is पूर्णांकended क्रम use in a FPGA manager driver's probe function.
 * After the manager driver creates the manager काष्ठा with
 * devm_fpga_mgr_create(), it should रेजिस्टर it with fpga_mgr_रेजिस्टर().  The
 * manager driver's हटाओ function should call fpga_mgr_unरेजिस्टर().  The
 * manager काष्ठा allocated with this function will be मुक्तd स्वतःmatically on
 * driver detach.  This includes the हाल of a probe function वापसing error
 * beक्रमe calling fpga_mgr_रेजिस्टर(), the काष्ठा will still get cleaned up.
 *
 * Return: poपूर्णांकer to काष्ठा fpga_manager or शून्य
 */
काष्ठा fpga_manager *devm_fpga_mgr_create(काष्ठा device *dev, स्थिर अक्षर *name,
					  स्थिर काष्ठा fpga_manager_ops *mops,
					  व्योम *priv)
अणु
	काष्ठा fpga_mgr_devres *dr;

	dr = devres_alloc(devm_fpga_mgr_release, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस शून्य;

	dr->mgr = fpga_mgr_create(dev, name, mops, priv);
	अगर (!dr->mgr) अणु
		devres_मुक्त(dr);
		वापस शून्य;
	पूर्ण

	devres_add(dev, dr);

	वापस dr->mgr;
पूर्ण
EXPORT_SYMBOL_GPL(devm_fpga_mgr_create);

/**
 * fpga_mgr_रेजिस्टर - रेजिस्टर a FPGA manager
 * @mgr: fpga manager काष्ठा
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक fpga_mgr_रेजिस्टर(काष्ठा fpga_manager *mgr)
अणु
	पूर्णांक ret;

	/*
	 * Initialize framework state by requesting low level driver पढ़ो state
	 * from device.  FPGA may be in reset mode or may have been programmed
	 * by bootloader or EEPROM.
	 */
	mgr->state = mgr->mops->state(mgr);

	ret = device_add(&mgr->dev);
	अगर (ret)
		जाओ error_device;

	dev_info(&mgr->dev, "%s registered\n", mgr->name);

	वापस 0;

error_device:
	ida_simple_हटाओ(&fpga_mgr_ida, mgr->dev.id);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_रेजिस्टर);

/**
 * fpga_mgr_unरेजिस्टर - unरेजिस्टर a FPGA manager
 * @mgr: fpga manager काष्ठा
 *
 * This function is पूर्णांकended क्रम use in a FPGA manager driver's हटाओ function.
 */
व्योम fpga_mgr_unरेजिस्टर(काष्ठा fpga_manager *mgr)
अणु
	dev_info(&mgr->dev, "%s %s\n", __func__, mgr->name);

	/*
	 * If the low level driver provides a method क्रम putting fpga पूर्णांकo
	 * a desired state upon unरेजिस्टर, करो it.
	 */
	अगर (mgr->mops->fpga_हटाओ)
		mgr->mops->fpga_हटाओ(mgr);

	device_unरेजिस्टर(&mgr->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_mgr_unरेजिस्टर);

अटल पूर्णांक fpga_mgr_devres_match(काष्ठा device *dev, व्योम *res,
				 व्योम *match_data)
अणु
	काष्ठा fpga_mgr_devres *dr = res;

	वापस match_data == dr->mgr;
पूर्ण

अटल व्योम devm_fpga_mgr_unरेजिस्टर(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा fpga_mgr_devres *dr = res;

	fpga_mgr_unरेजिस्टर(dr->mgr);
पूर्ण

/**
 * devm_fpga_mgr_रेजिस्टर - resource managed variant of fpga_mgr_रेजिस्टर()
 * @dev: managing device क्रम this FPGA manager
 * @mgr: fpga manager काष्ठा
 *
 * This is the devres variant of fpga_mgr_रेजिस्टर() क्रम which the unरेजिस्टर
 * function will be called स्वतःmatically when the managing device is detached.
 */
पूर्णांक devm_fpga_mgr_रेजिस्टर(काष्ठा device *dev, काष्ठा fpga_manager *mgr)
अणु
	काष्ठा fpga_mgr_devres *dr;
	पूर्णांक ret;

	/*
	 * Make sure that the काष्ठा fpga_manager * that is passed in is
	 * managed itself.
	 */
	अगर (WARN_ON(!devres_find(dev, devm_fpga_mgr_release,
				 fpga_mgr_devres_match, mgr)))
		वापस -EINVAL;

	dr = devres_alloc(devm_fpga_mgr_unरेजिस्टर, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	ret = fpga_mgr_रेजिस्टर(mgr);
	अगर (ret) अणु
		devres_मुक्त(dr);
		वापस ret;
	पूर्ण

	dr->mgr = mgr;
	devres_add(dev, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_fpga_mgr_रेजिस्टर);

अटल व्योम fpga_mgr_dev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल पूर्णांक __init fpga_mgr_class_init(व्योम)
अणु
	pr_info("FPGA manager framework\n");

	fpga_mgr_class = class_create(THIS_MODULE, "fpga_manager");
	अगर (IS_ERR(fpga_mgr_class))
		वापस PTR_ERR(fpga_mgr_class);

	fpga_mgr_class->dev_groups = fpga_mgr_groups;
	fpga_mgr_class->dev_release = fpga_mgr_dev_release;

	वापस 0;
पूर्ण

अटल व्योम __निकास fpga_mgr_class_निकास(व्योम)
अणु
	class_destroy(fpga_mgr_class);
	ida_destroy(&fpga_mgr_ida);
पूर्ण

MODULE_AUTHOR("Alan Tull <atull@kernel.org>");
MODULE_DESCRIPTION("FPGA manager framework");
MODULE_LICENSE("GPL v2");

subsys_initcall(fpga_mgr_class_init);
module_निकास(fpga_mgr_class_निकास);
