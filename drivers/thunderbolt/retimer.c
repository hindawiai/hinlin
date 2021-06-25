<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt/USB4 reसमयr support.
 *
 * Copyright (C) 2020, Intel Corporation
 * Authors: Kranthi Kuntala <kranthi.kuntala@पूर्णांकel.com>
 *	    Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched/संकेत.स>

#समावेश "sb_regs.h"
#समावेश "tb.h"

#घोषणा TB_MAX_RETIMER_INDEX	6

अटल पूर्णांक tb_reसमयr_nvm_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			       माप_प्रकार bytes)
अणु
	काष्ठा tb_nvm *nvm = priv;
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(nvm->dev);
	पूर्णांक ret;

	pm_runसमय_get_sync(&rt->dev);

	अगर (!mutex_trylock(&rt->tb->lock)) अणु
		ret = restart_syscall();
		जाओ out;
	पूर्ण

	ret = usb4_port_reसमयr_nvm_पढ़ो(rt->port, rt->index, offset, val, bytes);
	mutex_unlock(&rt->tb->lock);

out:
	pm_runसमय_mark_last_busy(&rt->dev);
	pm_runसमय_put_स्वतःsuspend(&rt->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tb_reसमयr_nvm_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
				माप_प्रकार bytes)
अणु
	काष्ठा tb_nvm *nvm = priv;
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(nvm->dev);
	पूर्णांक ret = 0;

	अगर (!mutex_trylock(&rt->tb->lock))
		वापस restart_syscall();

	ret = tb_nvm_ग_लिखो_buf(nvm, offset, val, bytes);
	mutex_unlock(&rt->tb->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tb_reसमयr_nvm_add(काष्ठा tb_reसमयr *rt)
अणु
	काष्ठा tb_nvm *nvm;
	u32 val, nvm_size;
	पूर्णांक ret;

	nvm = tb_nvm_alloc(&rt->dev);
	अगर (IS_ERR(nvm))
		वापस PTR_ERR(nvm);

	ret = usb4_port_reसमयr_nvm_पढ़ो(rt->port, rt->index, NVM_VERSION, &val,
					 माप(val));
	अगर (ret)
		जाओ err_nvm;

	nvm->major = val >> 16;
	nvm->minor = val >> 8;

	ret = usb4_port_reसमयr_nvm_पढ़ो(rt->port, rt->index, NVM_FLASH_SIZE,
					 &val, माप(val));
	अगर (ret)
		जाओ err_nvm;

	nvm_size = (SZ_1M << (val & 7)) / 8;
	nvm_size = (nvm_size - SZ_16K) / 2;

	ret = tb_nvm_add_active(nvm, nvm_size, tb_reसमयr_nvm_पढ़ो);
	अगर (ret)
		जाओ err_nvm;

	ret = tb_nvm_add_non_active(nvm, NVM_MAX_SIZE, tb_reसमयr_nvm_ग_लिखो);
	अगर (ret)
		जाओ err_nvm;

	rt->nvm = nvm;
	वापस 0;

err_nvm:
	tb_nvm_मुक्त(nvm);
	वापस ret;
पूर्ण

अटल पूर्णांक tb_reसमयr_nvm_validate_and_ग_लिखो(काष्ठा tb_reसमयr *rt)
अणु
	अचिन्हित पूर्णांक image_size, hdr_size;
	स्थिर u8 *buf = rt->nvm->buf;
	u16 ds_size, device;

	image_size = rt->nvm->buf_data_size;
	अगर (image_size < NVM_MIN_SIZE || image_size > NVM_MAX_SIZE)
		वापस -EINVAL;

	/*
	 * FARB poपूर्णांकer must poपूर्णांक inside the image and must at least
	 * contain parts of the digital section we will be पढ़ोing here.
	 */
	hdr_size = (*(u32 *)buf) & 0xffffff;
	अगर (hdr_size + NVM_DEVID + 2 >= image_size)
		वापस -EINVAL;

	/* Digital section start should be aligned to 4k page */
	अगर (!IS_ALIGNED(hdr_size, SZ_4K))
		वापस -EINVAL;

	/*
	 * Read digital section size and check that it also fits inside
	 * the image.
	 */
	ds_size = *(u16 *)(buf + hdr_size);
	अगर (ds_size >= image_size)
		वापस -EINVAL;

	/*
	 * Make sure the device ID in the image matches the reसमयr
	 * hardware.
	 */
	device = *(u16 *)(buf + hdr_size + NVM_DEVID);
	अगर (device != rt->device)
		वापस -EINVAL;

	/* Skip headers in the image */
	buf += hdr_size;
	image_size -= hdr_size;

	वापस usb4_port_reसमयr_nvm_ग_लिखो(rt->port, rt->index, 0, buf,
					   image_size);
पूर्ण

अटल sमाप_प्रकार device_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(dev);

	वापस प्र_लिखो(buf, "%#x\n", rt->device);
पूर्ण
अटल DEVICE_ATTR_RO(device);

अटल sमाप_प्रकार nvm_authenticate_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(dev);
	पूर्णांक ret;

	अगर (!mutex_trylock(&rt->tb->lock))
		वापस restart_syscall();

	अगर (!rt->nvm)
		ret = -EAGAIN;
	अन्यथा
		ret = प्र_लिखो(buf, "%#x\n", rt->auth_status);

	mutex_unlock(&rt->tb->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार nvm_authenticate_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(dev);
	bool val;
	पूर्णांक ret;

	pm_runसमय_get_sync(&rt->dev);

	अगर (!mutex_trylock(&rt->tb->lock)) अणु
		ret = restart_syscall();
		जाओ निकास_rpm;
	पूर्ण

	अगर (!rt->nvm) अणु
		ret = -EAGAIN;
		जाओ निकास_unlock;
	पूर्ण

	ret = kstrtobool(buf, &val);
	अगर (ret)
		जाओ निकास_unlock;

	/* Always clear status */
	rt->auth_status = 0;

	अगर (val) अणु
		अगर (!rt->nvm->buf) अणु
			ret = -EINVAL;
			जाओ निकास_unlock;
		पूर्ण

		ret = tb_reसमयr_nvm_validate_and_ग_लिखो(rt);
		अगर (ret)
			जाओ निकास_unlock;

		ret = usb4_port_reसमयr_nvm_authenticate(rt->port, rt->index);
	पूर्ण

निकास_unlock:
	mutex_unlock(&rt->tb->lock);
निकास_rpm:
	pm_runसमय_mark_last_busy(&rt->dev);
	pm_runसमय_put_स्वतःsuspend(&rt->dev);

	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(nvm_authenticate);

अटल sमाप_प्रकार nvm_version_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(dev);
	पूर्णांक ret;

	अगर (!mutex_trylock(&rt->tb->lock))
		वापस restart_syscall();

	अगर (!rt->nvm)
		ret = -EAGAIN;
	अन्यथा
		ret = प्र_लिखो(buf, "%x.%x\n", rt->nvm->major, rt->nvm->minor);

	mutex_unlock(&rt->tb->lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(nvm_version);

अटल sमाप_प्रकार venकरोr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(dev);

	वापस प्र_लिखो(buf, "%#x\n", rt->venकरोr);
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr);

अटल काष्ठा attribute *reसमयr_attrs[] = अणु
	&dev_attr_device.attr,
	&dev_attr_nvm_authenticate.attr,
	&dev_attr_nvm_version.attr,
	&dev_attr_venकरोr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group reसमयr_group = अणु
	.attrs = reसमयr_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *reसमयr_groups[] = अणु
	&reसमयr_group,
	शून्य
पूर्ण;

अटल व्योम tb_reसमयr_release(काष्ठा device *dev)
अणु
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(dev);

	kमुक्त(rt);
पूर्ण

काष्ठा device_type tb_reसमयr_type = अणु
	.name = "thunderbolt_retimer",
	.groups = reसमयr_groups,
	.release = tb_reसमयr_release,
पूर्ण;

अटल पूर्णांक tb_reसमयr_add(काष्ठा tb_port *port, u8 index, u32 auth_status)
अणु
	काष्ठा tb_reसमयr *rt;
	u32 venकरोr, device;
	पूर्णांक ret;

	अगर (!port->cap_usb4)
		वापस -EINVAL;

	ret = usb4_port_reसमयr_पढ़ो(port, index, USB4_SB_VENDOR_ID, &venकरोr,
				     माप(venकरोr));
	अगर (ret) अणु
		अगर (ret != -ENODEV)
			tb_port_warn(port, "failed read retimer VendorId: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = usb4_port_reसमयr_पढ़ो(port, index, USB4_SB_PRODUCT_ID, &device,
				     माप(device));
	अगर (ret) अणु
		अगर (ret != -ENODEV)
			tb_port_warn(port, "failed read retimer ProductId: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (venकरोr != PCI_VENDOR_ID_INTEL && venकरोr != 0x8087) अणु
		tb_port_info(port, "retimer NVM format of vendor %#x is not supported\n",
			     venकरोr);
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * Check that it supports NVM operations. If not then करोn't add
	 * the device at all.
	 */
	ret = usb4_port_reसमयr_nvm_sector_size(port, index);
	अगर (ret < 0)
		वापस ret;

	rt = kzalloc(माप(*rt), GFP_KERNEL);
	अगर (!rt)
		वापस -ENOMEM;

	rt->index = index;
	rt->venकरोr = venकरोr;
	rt->device = device;
	rt->auth_status = auth_status;
	rt->port = port;
	rt->tb = port->sw->tb;

	rt->dev.parent = &port->sw->dev;
	rt->dev.bus = &tb_bus_type;
	rt->dev.type = &tb_reसमयr_type;
	dev_set_name(&rt->dev, "%s:%u.%u", dev_name(&port->sw->dev),
		     port->port, index);

	ret = device_रेजिस्टर(&rt->dev);
	अगर (ret) अणु
		dev_err(&rt->dev, "failed to register retimer: %d\n", ret);
		put_device(&rt->dev);
		वापस ret;
	पूर्ण

	ret = tb_reसमयr_nvm_add(rt);
	अगर (ret) अणु
		dev_err(&rt->dev, "failed to add NVM devices: %d\n", ret);
		device_unरेजिस्टर(&rt->dev);
		वापस ret;
	पूर्ण

	dev_info(&rt->dev, "new retimer found, vendor=%#x device=%#x\n",
		 rt->venकरोr, rt->device);

	pm_runसमय_no_callbacks(&rt->dev);
	pm_runसमय_set_active(&rt->dev);
	pm_runसमय_enable(&rt->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&rt->dev, TB_AUTOSUSPEND_DELAY);
	pm_runसमय_mark_last_busy(&rt->dev);
	pm_runसमय_use_स्वतःsuspend(&rt->dev);

	वापस 0;
पूर्ण

अटल व्योम tb_reसमयr_हटाओ(काष्ठा tb_reसमयr *rt)
अणु
	dev_info(&rt->dev, "retimer disconnected\n");
	tb_nvm_मुक्त(rt->nvm);
	device_unरेजिस्टर(&rt->dev);
पूर्ण

काष्ठा tb_reसमयr_lookup अणु
	स्थिर काष्ठा tb_port *port;
	u8 index;
पूर्ण;

अटल पूर्णांक reसमयr_match(काष्ठा device *dev, व्योम *data)
अणु
	स्थिर काष्ठा tb_reसमयr_lookup *lookup = data;
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(dev);

	वापस rt && rt->port == lookup->port && rt->index == lookup->index;
पूर्ण

अटल काष्ठा tb_reसमयr *tb_port_find_reसमयr(काष्ठा tb_port *port, u8 index)
अणु
	काष्ठा tb_reसमयr_lookup lookup = अणु .port = port, .index = index पूर्ण;
	काष्ठा device *dev;

	dev = device_find_child(&port->sw->dev, &lookup, reसमयr_match);
	अगर (dev)
		वापस tb_to_reसमयr(dev);

	वापस शून्य;
पूर्ण

/**
 * tb_reसमयr_scan() - Scan क्रम on-board reसमयrs under port
 * @port: USB4 port to scan
 *
 * Tries to क्रमागतerate on-board reसमयrs connected to @port. Found
 * reसमयrs are रेजिस्टरed as children of @port. Does not scan क्रम cable
 * reसमयrs क्रम now.
 */
पूर्णांक tb_reसमयr_scan(काष्ठा tb_port *port)
अणु
	u32 status[TB_MAX_RETIMER_INDEX + 1] = अणुपूर्ण;
	पूर्णांक ret, i, last_idx = 0;

	अगर (!port->cap_usb4)
		वापस 0;

	/*
	 * Send broadcast RT to make sure reसमयr indices facing this
	 * port are set.
	 */
	ret = usb4_port_क्रमागतerate_reसमयrs(port);
	अगर (ret)
		वापस ret;

	/*
	 * Beक्रमe करोing anything अन्यथा, पढ़ो the authentication status.
	 * If the reसमयr has it set, store it क्रम the new reसमयr
	 * device instance.
	 */
	क्रम (i = 1; i <= TB_MAX_RETIMER_INDEX; i++)
		usb4_port_reसमयr_nvm_authenticate_status(port, i, &status[i]);

	क्रम (i = 1; i <= TB_MAX_RETIMER_INDEX; i++) अणु
		/*
		 * Last reसमयr is true only क्रम the last on-board
		 * reसमयr (the one connected directly to the Type-C
		 * port).
		 */
		ret = usb4_port_reसमयr_is_last(port, i);
		अगर (ret > 0)
			last_idx = i;
		अन्यथा अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (!last_idx)
		वापस 0;

	/* Add on-board reसमयrs अगर they करो not exist alपढ़ोy */
	क्रम (i = 1; i <= last_idx; i++) अणु
		काष्ठा tb_reसमयr *rt;

		rt = tb_port_find_reसमयr(port, i);
		अगर (rt) अणु
			put_device(&rt->dev);
		पूर्ण अन्यथा अणु
			ret = tb_reसमयr_add(port, i, status[i]);
			अगर (ret && ret != -EOPNOTSUPP)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_reसमयr(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा tb_reसमयr *rt = tb_to_reसमयr(dev);
	काष्ठा tb_port *port = data;

	अगर (rt && rt->port == port)
		tb_reसमयr_हटाओ(rt);
	वापस 0;
पूर्ण

/**
 * tb_reसमयr_हटाओ_all() - Remove all reसमयrs under port
 * @port: USB4 port whose reसमयrs to हटाओ
 *
 * This हटाओs all previously added reसमयrs under @port.
 */
व्योम tb_reसमयr_हटाओ_all(काष्ठा tb_port *port)
अणु
	अगर (port->cap_usb4)
		device_क्रम_each_child_reverse(&port->sw->dev, port,
					      हटाओ_reसमयr);
पूर्ण
