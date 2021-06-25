<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * Description: CoreSight Trace Memory Controller driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/coresight.h>
#समावेश <linux/amba/bus.h>

#समावेश "coresight-priv.h"
#समावेश "coresight-tmc.h"

DEFINE_CORESIGHT_DEVLIST(etb_devs, "tmc_etb");
DEFINE_CORESIGHT_DEVLIST(etf_devs, "tmc_etf");
DEFINE_CORESIGHT_DEVLIST(etr_devs, "tmc_etr");

व्योम पंचांगc_रुको_क्रम_पंचांगcपढ़ोy(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	काष्ठा coresight_device *csdev = drvdata->csdev;
	काष्ठा csdev_access *csa = &csdev->access;

	/* Ensure क्रमmatter, unक्रमmatter and hardware fअगरo are empty */
	अगर (coresight_समयout(csa, TMC_STS, TMC_STS_TMCREADY_BIT, 1)) अणु
		dev_err(&csdev->dev,
			"timeout while waiting for TMC to be Ready\n");
	पूर्ण
पूर्ण

व्योम पंचांगc_flush_and_stop(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	काष्ठा coresight_device *csdev = drvdata->csdev;
	काष्ठा csdev_access *csa = &csdev->access;
	u32 ffcr;

	ffcr = पढ़ोl_relaxed(drvdata->base + TMC_FFCR);
	ffcr |= TMC_FFCR_STOP_ON_FLUSH;
	ग_लिखोl_relaxed(ffcr, drvdata->base + TMC_FFCR);
	ffcr |= BIT(TMC_FFCR_FLUSHMAN_BIT);
	ग_लिखोl_relaxed(ffcr, drvdata->base + TMC_FFCR);
	/* Ensure flush completes */
	अगर (coresight_समयout(csa, TMC_FFCR, TMC_FFCR_FLUSHMAN_BIT, 0)) अणु
		dev_err(&csdev->dev,
		"timeout while waiting for completion of Manual Flush\n");
	पूर्ण

	पंचांगc_रुको_क्रम_पंचांगcपढ़ोy(drvdata);
पूर्ण

व्योम पंचांगc_enable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	ग_लिखोl_relaxed(TMC_CTL_CAPT_EN, drvdata->base + TMC_CTL);
पूर्ण

व्योम पंचांगc_disable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	ग_लिखोl_relaxed(0x0, drvdata->base + TMC_CTL);
पूर्ण

u32 पंचांगc_get_memwidth_mask(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	u32 mask = 0;

	/*
	 * When moving RRP or an offset address क्रमward, the new values must
	 * be byte-address aligned to the width of the trace memory databus
	 * _and_ to a frame boundary (16 byte), whichever is the biggest. For
	 * example, क्रम 32-bit, 64-bit and 128-bit wide trace memory, the four
	 * LSBs must be 0s. For 256-bit wide trace memory, the five LSBs must
	 * be 0s.
	 */
	चयन (drvdata->memwidth) अणु
	हाल TMC_MEM_INTF_WIDTH_32BITS:
	हाल TMC_MEM_INTF_WIDTH_64BITS:
	हाल TMC_MEM_INTF_WIDTH_128BITS:
		mask = GENMASK(31, 4);
		अवरोध;
	हाल TMC_MEM_INTF_WIDTH_256BITS:
		mask = GENMASK(31, 5);
		अवरोध;
	पूर्ण

	वापस mask;
पूर्ण

अटल पूर्णांक पंचांगc_पढ़ो_prepare(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	पूर्णांक ret = 0;

	चयन (drvdata->config_type) अणु
	हाल TMC_CONFIG_TYPE_ETB:
	हाल TMC_CONFIG_TYPE_ETF:
		ret = पंचांगc_पढ़ो_prepare_etb(drvdata);
		अवरोध;
	हाल TMC_CONFIG_TYPE_ETR:
		ret = पंचांगc_पढ़ो_prepare_etr(drvdata);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (!ret)
		dev_dbg(&drvdata->csdev->dev, "TMC read start\n");

	वापस ret;
पूर्ण

अटल पूर्णांक पंचांगc_पढ़ो_unprepare(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	पूर्णांक ret = 0;

	चयन (drvdata->config_type) अणु
	हाल TMC_CONFIG_TYPE_ETB:
	हाल TMC_CONFIG_TYPE_ETF:
		ret = पंचांगc_पढ़ो_unprepare_etb(drvdata);
		अवरोध;
	हाल TMC_CONFIG_TYPE_ETR:
		ret = पंचांगc_पढ़ो_unprepare_etr(drvdata);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (!ret)
		dev_dbg(&drvdata->csdev->dev, "TMC read end\n");

	वापस ret;
पूर्ण

अटल पूर्णांक पंचांगc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा पंचांगc_drvdata *drvdata = container_of(file->निजी_data,
						   काष्ठा पंचांगc_drvdata, miscdev);

	ret = पंचांगc_पढ़ो_prepare(drvdata);
	अगर (ret)
		वापस ret;

	nonseekable_खोलो(inode, file);

	dev_dbg(&drvdata->csdev->dev, "%s: successfully opened\n", __func__);
	वापस 0;
पूर्ण

अटल अंतरभूत sमाप_प्रकार पंचांगc_get_sysfs_trace(काष्ठा पंचांगc_drvdata *drvdata,
					  loff_t pos, माप_प्रकार len, अक्षर **bufpp)
अणु
	चयन (drvdata->config_type) अणु
	हाल TMC_CONFIG_TYPE_ETB:
	हाल TMC_CONFIG_TYPE_ETF:
		वापस पंचांगc_etb_get_sysfs_trace(drvdata, pos, len, bufpp);
	हाल TMC_CONFIG_TYPE_ETR:
		वापस पंचांगc_etr_get_sysfs_trace(drvdata, pos, len, bufpp);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार पंचांगc_पढ़ो(काष्ठा file *file, अक्षर __user *data, माप_प्रकार len,
			loff_t *ppos)
अणु
	अक्षर *bufp;
	sमाप_प्रकार actual;
	काष्ठा पंचांगc_drvdata *drvdata = container_of(file->निजी_data,
						   काष्ठा पंचांगc_drvdata, miscdev);
	actual = पंचांगc_get_sysfs_trace(drvdata, *ppos, len, &bufp);
	अगर (actual <= 0)
		वापस 0;

	अगर (copy_to_user(data, bufp, actual)) अणु
		dev_dbg(&drvdata->csdev->dev,
			"%s: copy_to_user failed\n", __func__);
		वापस -EFAULT;
	पूर्ण

	*ppos += actual;
	dev_dbg(&drvdata->csdev->dev, "%zu bytes copied\n", actual);

	वापस actual;
पूर्ण

अटल पूर्णांक पंचांगc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा पंचांगc_drvdata *drvdata = container_of(file->निजी_data,
						   काष्ठा पंचांगc_drvdata, miscdev);

	ret = पंचांगc_पढ़ो_unprepare(drvdata);
	अगर (ret)
		वापस ret;

	dev_dbg(&drvdata->csdev->dev, "%s: released\n", __func__);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations पंचांगc_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= पंचांगc_खोलो,
	.पढ़ो		= पंचांगc_पढ़ो,
	.release	= पंचांगc_release,
	.llseek		= no_llseek,
पूर्ण;

अटल क्रमागत पंचांगc_mem_पूर्णांकf_width पंचांगc_get_memwidth(u32 devid)
अणु
	क्रमागत पंचांगc_mem_पूर्णांकf_width memwidth;

	/*
	 * Excerpt from the TRM:
	 *
	 * DEVID::MEMWIDTH[10:8]
	 * 0x2 Memory पूर्णांकerface databus is 32 bits wide.
	 * 0x3 Memory पूर्णांकerface databus is 64 bits wide.
	 * 0x4 Memory पूर्णांकerface databus is 128 bits wide.
	 * 0x5 Memory पूर्णांकerface databus is 256 bits wide.
	 */
	चयन (BMVAL(devid, 8, 10)) अणु
	हाल 0x2:
		memwidth = TMC_MEM_INTF_WIDTH_32BITS;
		अवरोध;
	हाल 0x3:
		memwidth = TMC_MEM_INTF_WIDTH_64BITS;
		अवरोध;
	हाल 0x4:
		memwidth = TMC_MEM_INTF_WIDTH_128BITS;
		अवरोध;
	हाल 0x5:
		memwidth = TMC_MEM_INTF_WIDTH_256BITS;
		अवरोध;
	शेष:
		memwidth = 0;
	पूर्ण

	वापस memwidth;
पूर्ण

#घोषणा coresight_पंचांगc_reg(name, offset)			\
	coresight_simple_reg32(काष्ठा पंचांगc_drvdata, name, offset)
#घोषणा coresight_पंचांगc_reg64(name, lo_off, hi_off)	\
	coresight_simple_reg64(काष्ठा पंचांगc_drvdata, name, lo_off, hi_off)

coresight_पंचांगc_reg(rsz, TMC_RSZ);
coresight_पंचांगc_reg(sts, TMC_STS);
coresight_पंचांगc_reg(trg, TMC_TRG);
coresight_पंचांगc_reg(ctl, TMC_CTL);
coresight_पंचांगc_reg(ffsr, TMC_FFSR);
coresight_पंचांगc_reg(ffcr, TMC_FFCR);
coresight_पंचांगc_reg(mode, TMC_MODE);
coresight_पंचांगc_reg(pscr, TMC_PSCR);
coresight_पंचांगc_reg(axictl, TMC_AXICTL);
coresight_पंचांगc_reg(authstatus, TMC_AUTHSTATUS);
coresight_पंचांगc_reg(devid, CORESIGHT_DEVID);
coresight_पंचांगc_reg64(rrp, TMC_RRP, TMC_RRPHI);
coresight_पंचांगc_reg64(rwp, TMC_RWP, TMC_RWPHI);
coresight_पंचांगc_reg64(dba, TMC_DBALO, TMC_DBAHI);

अटल काष्ठा attribute *coresight_पंचांगc_mgmt_attrs[] = अणु
	&dev_attr_rsz.attr,
	&dev_attr_sts.attr,
	&dev_attr_rrp.attr,
	&dev_attr_rwp.attr,
	&dev_attr_trg.attr,
	&dev_attr_ctl.attr,
	&dev_attr_ffsr.attr,
	&dev_attr_ffcr.attr,
	&dev_attr_mode.attr,
	&dev_attr_pscr.attr,
	&dev_attr_devid.attr,
	&dev_attr_dba.attr,
	&dev_attr_axictl.attr,
	&dev_attr_authstatus.attr,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार trigger_cntr_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val = drvdata->trigger_cntr;

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार trigger_cntr_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	drvdata->trigger_cntr = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(trigger_cntr);

अटल sमाप_प्रकार buffer_size_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(dev->parent);

	वापस प्र_लिखो(buf, "%#x\n", drvdata->size);
पूर्ण

अटल sमाप_प्रकार buffer_size_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(dev->parent);

	/* Only permitted क्रम TMC-ETRs */
	अगर (drvdata->config_type != TMC_CONFIG_TYPE_ETR)
		वापस -EPERM;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;
	/* The buffer size should be page aligned */
	अगर (val & (PAGE_SIZE - 1))
		वापस -EINVAL;
	drvdata->size = val;
	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(buffer_size);

अटल काष्ठा attribute *coresight_पंचांगc_attrs[] = अणु
	&dev_attr_trigger_cntr.attr,
	&dev_attr_buffer_size.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_पंचांगc_group = अणु
	.attrs = coresight_पंचांगc_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_पंचांगc_mgmt_group = अणु
	.attrs = coresight_पंचांगc_mgmt_attrs,
	.name = "mgmt",
पूर्ण;

अटल स्थिर काष्ठा attribute_group *coresight_पंचांगc_groups[] = अणु
	&coresight_पंचांगc_group,
	&coresight_पंचांगc_mgmt_group,
	शून्य,
पूर्ण;

अटल अंतरभूत bool पंचांगc_etr_can_use_sg(काष्ठा device *dev)
अणु
	वापस fwnode_property_present(dev->fwnode, "arm,scatter-gather");
पूर्ण

अटल अंतरभूत bool पंचांगc_etr_has_non_secure_access(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	u32 auth = पढ़ोl_relaxed(drvdata->base + TMC_AUTHSTATUS);

	वापस (auth & TMC_AUTH_NSID_MASK) == 0x3;
पूर्ण

/* Detect and initialise the capabilities of a TMC ETR */
अटल पूर्णांक पंचांगc_etr_setup_caps(काष्ठा device *parent, u32 devid, व्योम *dev_caps)
अणु
	पूर्णांक rc;
	u32 dma_mask = 0;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(parent);

	अगर (!पंचांगc_etr_has_non_secure_access(drvdata))
		वापस -EACCES;

	/* Set the unadvertised capabilities */
	पंचांगc_etr_init_caps(drvdata, (u32)(अचिन्हित दीर्घ)dev_caps);

	अगर (!(devid & TMC_DEVID_NOSCAT) && पंचांगc_etr_can_use_sg(parent))
		पंचांगc_etr_set_cap(drvdata, TMC_ETR_SG);

	/* Check अगर the AXI address width is available */
	अगर (devid & TMC_DEVID_AXIAW_VALID)
		dma_mask = ((devid >> TMC_DEVID_AXIAW_SHIFT) &
				TMC_DEVID_AXIAW_MASK);

	/*
	 * Unless specअगरied in the device configuration, ETR uses a 40-bit
	 * AXI master in place of the embedded SRAM of ETB/ETF.
	 */
	चयन (dma_mask) अणु
	हाल 32:
	हाल 40:
	हाल 44:
	हाल 48:
	हाल 52:
		dev_info(parent, "Detected dma mask %dbits\n", dma_mask);
		अवरोध;
	शेष:
		dma_mask = 40;
	पूर्ण

	rc = dma_set_mask_and_coherent(parent, DMA_BIT_MASK(dma_mask));
	अगर (rc)
		dev_err(parent, "Failed to setup DMA mask: %d\n", rc);
	वापस rc;
पूर्ण

अटल u32 पंचांगc_etr_get_शेष_buffer_size(काष्ठा device *dev)
अणु
	u32 size;

	अगर (fwnode_property_पढ़ो_u32(dev->fwnode, "arm,buffer-size", &size))
		size = SZ_1M;
	वापस size;
पूर्ण

अटल पूर्णांक पंचांगc_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret = 0;
	u32 devid;
	व्योम __iomem *base;
	काष्ठा device *dev = &adev->dev;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा पंचांगc_drvdata *drvdata;
	काष्ठा resource *res = &adev->res;
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;
	काष्ठा coresight_dev_list *dev_list = शून्य;

	ret = -ENOMEM;
	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		जाओ out;

	dev_set_drvdata(dev, drvdata);

	/* Validity क्रम the resource is alपढ़ोy checked by the AMBA core */
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		जाओ out;
	पूर्ण

	drvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	spin_lock_init(&drvdata->spinlock);

	devid = पढ़ोl_relaxed(drvdata->base + CORESIGHT_DEVID);
	drvdata->config_type = BMVAL(devid, 6, 7);
	drvdata->memwidth = पंचांगc_get_memwidth(devid);
	/* This device is not associated with a session */
	drvdata->pid = -1;

	अगर (drvdata->config_type == TMC_CONFIG_TYPE_ETR)
		drvdata->size = पंचांगc_etr_get_शेष_buffer_size(dev);
	अन्यथा
		drvdata->size = पढ़ोl_relaxed(drvdata->base + TMC_RSZ) * 4;

	desc.dev = dev;
	desc.groups = coresight_पंचांगc_groups;

	चयन (drvdata->config_type) अणु
	हाल TMC_CONFIG_TYPE_ETB:
		desc.type = CORESIGHT_DEV_TYPE_SINK;
		desc.subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_BUFFER;
		desc.ops = &पंचांगc_etb_cs_ops;
		dev_list = &etb_devs;
		अवरोध;
	हाल TMC_CONFIG_TYPE_ETR:
		desc.type = CORESIGHT_DEV_TYPE_SINK;
		desc.subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_SYSMEM;
		desc.ops = &पंचांगc_etr_cs_ops;
		ret = पंचांगc_etr_setup_caps(dev, devid,
					 coresight_get_uci_data(id));
		अगर (ret)
			जाओ out;
		idr_init(&drvdata->idr);
		mutex_init(&drvdata->idr_mutex);
		dev_list = &etr_devs;
		अवरोध;
	हाल TMC_CONFIG_TYPE_ETF:
		desc.type = CORESIGHT_DEV_TYPE_LINKSINK;
		desc.subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_BUFFER;
		desc.subtype.link_subtype = CORESIGHT_DEV_SUBTYPE_LINK_FIFO;
		desc.ops = &पंचांगc_etf_cs_ops;
		dev_list = &etf_devs;
		अवरोध;
	शेष:
		pr_err("%s: Unsupported TMC config\n", desc.name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	desc.name = coresight_alloc_device_name(dev_list, dev);
	अगर (!desc.name) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata)) अणु
		ret = PTR_ERR(pdata);
		जाओ out;
	पूर्ण
	adev->dev.platक्रमm_data = pdata;
	desc.pdata = pdata;

	drvdata->csdev = coresight_रेजिस्टर(&desc);
	अगर (IS_ERR(drvdata->csdev)) अणु
		ret = PTR_ERR(drvdata->csdev);
		जाओ out;
	पूर्ण

	drvdata->miscdev.name = desc.name;
	drvdata->miscdev.minor = MISC_DYNAMIC_MINOR;
	drvdata->miscdev.fops = &पंचांगc_fops;
	ret = misc_रेजिस्टर(&drvdata->miscdev);
	अगर (ret)
		coresight_unरेजिस्टर(drvdata->csdev);
	अन्यथा
		pm_runसमय_put(&adev->dev);
out:
	वापस ret;
पूर्ण

अटल व्योम पंचांगc_shutकरोwn(काष्ठा amba_device *adev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = amba_get_drvdata(adev);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	अगर (drvdata->mode == CS_MODE_DISABLED)
		जाओ out;

	अगर (drvdata->config_type == TMC_CONFIG_TYPE_ETR)
		पंचांगc_etr_disable_hw(drvdata);

	/*
	 * We करो not care about coresight unरेजिस्टर here unlike हटाओ
	 * callback which is required क्रम making coresight modular since
	 * the प्रणाली is going करोwn after this.
	 */
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
पूर्ण

अटल व्योम पंचांगc_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(&adev->dev);

	/*
	 * Since misc_खोलो() holds a refcount on the f_ops, which is
	 * etb fops in this हाल, device is there until last file
	 * handler to this device is बंदd.
	 */
	misc_deरेजिस्टर(&drvdata->miscdev);
	coresight_unरेजिस्टर(drvdata->csdev);
पूर्ण

अटल स्थिर काष्ठा amba_id पंचांगc_ids[] = अणु
	CS_AMBA_ID(0x000bb961),
	/* Coresight SoC 600 TMC-ETR/ETS */
	CS_AMBA_ID_DATA(0x000bb9e8, (अचिन्हित दीर्घ)CORESIGHT_SOC_600_ETR_CAPS),
	/* Coresight SoC 600 TMC-ETB */
	CS_AMBA_ID(0x000bb9e9),
	/* Coresight SoC 600 TMC-ETF */
	CS_AMBA_ID(0x000bb9ea),
	अणु 0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, पंचांगc_ids);

अटल काष्ठा amba_driver पंचांगc_driver = अणु
	.drv = अणु
		.name   = "coresight-tmc",
		.owner  = THIS_MODULE,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= पंचांगc_probe,
	.shutकरोwn	= पंचांगc_shutकरोwn,
	.हटाओ		= पंचांगc_हटाओ,
	.id_table	= पंचांगc_ids,
पूर्ण;

module_amba_driver(पंचांगc_driver);

MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_DESCRIPTION("Arm CoreSight Trace Memory Controller driver");
MODULE_LICENSE("GPL v2");
