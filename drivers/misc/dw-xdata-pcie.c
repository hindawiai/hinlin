<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare xData driver
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#समावेश <linux/miscdevice.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/pci-epf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>

#घोषणा DW_XDATA_DRIVER_NAME		"dw-xdata-pcie"

#घोषणा DW_XDATA_EP_MEM_OFFSET		0x8000000

अटल DEFINE_IDA(xdata_ida);

#घोषणा STATUS_DONE			BIT(0)

#घोषणा CONTROL_DOORBELL		BIT(0)
#घोषणा CONTROL_IS_WRITE		BIT(1)
#घोषणा CONTROL_LENGTH(a)		FIELD_PREP(GENMASK(13, 2), a)
#घोषणा CONTROL_PATTERN_INC		BIT(16)
#घोषणा CONTROL_NO_ADDR_INC		BIT(18)

#घोषणा XPERF_CONTROL_ENABLE		BIT(5)

#घोषणा BURST_REPEAT			BIT(31)
#घोषणा BURST_VALUE			0x1001

#घोषणा PATTERN_VALUE			0x0

काष्ठा dw_xdata_regs अणु
	u32 addr_lsb;					/* 0x000 */
	u32 addr_msb;					/* 0x004 */
	u32 burst_cnt;					/* 0x008 */
	u32 control;					/* 0x00c */
	u32 pattern;					/* 0x010 */
	u32 status;					/* 0x014 */
	u32 RAM_addr;					/* 0x018 */
	u32 RAM_port;					/* 0x01c */
	u32 _reserved0[14];				/* 0x020..0x054 */
	u32 perf_control;				/* 0x058 */
	u32 _reserved1[41];				/* 0x05c..0x0fc */
	u32 wr_cnt_lsb;					/* 0x100 */
	u32 wr_cnt_msb;					/* 0x104 */
	u32 rd_cnt_lsb;					/* 0x108 */
	u32 rd_cnt_msb;					/* 0x10c */
पूर्ण __packed;

काष्ठा dw_xdata_region अणु
	phys_addr_t paddr;				/* physical address */
	व्योम __iomem *vaddr;				/* भव address */
पूर्ण;

काष्ठा dw_xdata अणु
	काष्ठा dw_xdata_region rg_region;		/* रेजिस्टरs */
	माप_प्रकार max_wr_len;				/* max wr xfer len */
	माप_प्रकार max_rd_len;				/* max rd xfer len */
	काष्ठा mutex mutex;
	काष्ठा pci_dev *pdev;
	काष्ठा miscdevice misc_dev;
पूर्ण;

अटल अंतरभूत काष्ठा dw_xdata_regs __iomem *__dw_regs(काष्ठा dw_xdata *dw)
अणु
	वापस dw->rg_region.vaddr;
पूर्ण

अटल व्योम dw_xdata_stop(काष्ठा dw_xdata *dw)
अणु
	u32 burst;

	mutex_lock(&dw->mutex);

	burst = पढ़ोl(&(__dw_regs(dw)->burst_cnt));

	अगर (burst & BURST_REPEAT) अणु
		burst &= ~(u32)BURST_REPEAT;
		ग_लिखोl(burst, &(__dw_regs(dw)->burst_cnt));
	पूर्ण

	mutex_unlock(&dw->mutex);
पूर्ण

अटल व्योम dw_xdata_start(काष्ठा dw_xdata *dw, bool ग_लिखो)
अणु
	काष्ठा device *dev = &dw->pdev->dev;
	u32 control, status;

	/* Stop first अगर xfer in progress */
	dw_xdata_stop(dw);

	mutex_lock(&dw->mutex);

	/* Clear status रेजिस्टर */
	ग_लिखोl(0x0, &(__dw_regs(dw)->status));

	/* Burst count रेजिस्टर set क्रम continuous until stopped */
	ग_लिखोl(BURST_REPEAT | BURST_VALUE, &(__dw_regs(dw)->burst_cnt));

	/* Pattern रेजिस्टर */
	ग_लिखोl(PATTERN_VALUE, &(__dw_regs(dw)->pattern));

	/* Control रेजिस्टर */
	control = CONTROL_DOORBELL | CONTROL_PATTERN_INC | CONTROL_NO_ADDR_INC;
	अगर (ग_लिखो) अणु
		control |= CONTROL_IS_WRITE;
		control |= CONTROL_LENGTH(dw->max_wr_len);
	पूर्ण अन्यथा अणु
		control |= CONTROL_LENGTH(dw->max_rd_len);
	पूर्ण
	ग_लिखोl(control, &(__dw_regs(dw)->control));

	/*
	 * The xData HW block needs about 100 ms to initiate the traffic
	 * generation according this HW block datasheet.
	 */
	usleep_range(100, 150);

	status = पढ़ोl(&(__dw_regs(dw)->status));

	mutex_unlock(&dw->mutex);

	अगर (!(status & STATUS_DONE))
		dev_dbg(dev, "xData: started %s direction\n",
			ग_लिखो ? "write" : "read");
पूर्ण

अटल व्योम dw_xdata_perf_meas(काष्ठा dw_xdata *dw, u64 *data, bool ग_लिखो)
अणु
	अगर (ग_लिखो) अणु
		*data = पढ़ोl(&(__dw_regs(dw)->wr_cnt_msb));
		*data <<= 32;
		*data |= पढ़ोl(&(__dw_regs(dw)->wr_cnt_lsb));
	पूर्ण अन्यथा अणु
		*data = पढ़ोl(&(__dw_regs(dw)->rd_cnt_msb));
		*data <<= 32;
		*data |= पढ़ोl(&(__dw_regs(dw)->rd_cnt_lsb));
	पूर्ण
पूर्ण

अटल u64 dw_xdata_perf_dअगरf(u64 *m1, u64 *m2, u64 समय)
अणु
	u64 rate = (*m1 - *m2);

	rate *= (1000 * 1000 * 1000);
	rate >>= 20;
	rate = DIV_ROUND_CLOSEST_ULL(rate, समय);

	वापस rate;
पूर्ण

अटल व्योम dw_xdata_perf(काष्ठा dw_xdata *dw, u64 *rate, bool ग_लिखो)
अणु
	काष्ठा device *dev = &dw->pdev->dev;
	u64 data[2], समय[2], dअगरf;

	mutex_lock(&dw->mutex);

	/* First acquisition of current count frames */
	ग_लिखोl(0x0, &(__dw_regs(dw)->perf_control));
	dw_xdata_perf_meas(dw, &data[0], ग_लिखो);
	समय[0] = jअगरfies;
	ग_लिखोl((u32)XPERF_CONTROL_ENABLE, &(__dw_regs(dw)->perf_control));

	/*
	 * Wait 100ms between the 1st count frame acquisition and the 2nd
	 * count frame acquisition, in order to calculate the speed later
	 */
	mdelay(100);

	/* Second acquisition of current count frames */
	ग_लिखोl(0x0, &(__dw_regs(dw)->perf_control));
	dw_xdata_perf_meas(dw, &data[1], ग_लिखो);
	समय[1] = jअगरfies;
	ग_लिखोl((u32)XPERF_CONTROL_ENABLE, &(__dw_regs(dw)->perf_control));

	/*
	 * Speed calculation
	 *
	 * rate = (2nd count frames - 1st count frames) / (समय elapsed)
	 */
	dअगरf = jअगरfies_to_nsecs(समय[1] - समय[0]);
	*rate = dw_xdata_perf_dअगरf(&data[1], &data[0], dअगरf);

	mutex_unlock(&dw->mutex);

	dev_dbg(dev, "xData: time=%llu us, %s=%llu MB/s\n",
		dअगरf, ग_लिखो ? "write" : "read", *rate);
पूर्ण

अटल काष्ठा dw_xdata *misc_dev_to_dw(काष्ठा miscdevice *misc_dev)
अणु
	वापस container_of(misc_dev, काष्ठा dw_xdata, misc_dev);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा miscdevice *misc_dev = dev_get_drvdata(dev);
	काष्ठा dw_xdata *dw = misc_dev_to_dw(misc_dev);
	u64 rate;

	dw_xdata_perf(dw, &rate, true);

	वापस sysfs_emit(buf, "%llu\n", rate);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा miscdevice *misc_dev = dev_get_drvdata(dev);
	काष्ठा dw_xdata *dw = misc_dev_to_dw(misc_dev);
	bool enabled;
	पूर्णांक ret;

	ret = kstrtobool(buf, &enabled);
	अगर (ret < 0)
		वापस ret;

	अगर (enabled) अणु
		dev_dbg(dev, "xData: requested write transfer\n");
		dw_xdata_start(dw, true);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "xData: requested stop transfer\n");
		dw_xdata_stop(dw);
	पूर्ण

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(ग_लिखो);

अटल sमाप_प्रकार पढ़ो_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा miscdevice *misc_dev = dev_get_drvdata(dev);
	काष्ठा dw_xdata *dw = misc_dev_to_dw(misc_dev);
	u64 rate;

	dw_xdata_perf(dw, &rate, false);

	वापस sysfs_emit(buf, "%llu\n", rate);
पूर्ण

अटल sमाप_प्रकार पढ़ो_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा miscdevice *misc_dev = dev_get_drvdata(dev);
	काष्ठा dw_xdata *dw = misc_dev_to_dw(misc_dev);
	bool enabled;
	पूर्णांक ret;

	ret = kstrtobool(buf, &enabled);
	अगर (ret < 0)
		वापस ret;

	अगर (enabled) अणु
		dev_dbg(dev, "xData: requested read transfer\n");
		dw_xdata_start(dw, false);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "xData: requested stop transfer\n");
		dw_xdata_stop(dw);
	पूर्ण

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(पढ़ो);

अटल काष्ठा attribute *xdata_attrs[] = अणु
	&dev_attr_ग_लिखो.attr,
	&dev_attr_पढ़ो.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(xdata);

अटल पूर्णांक dw_xdata_pcie_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *pid)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_xdata *dw;
	अक्षर name[24];
	u64 addr;
	पूर्णांक err;
	पूर्णांक id;

	/* Enable PCI device */
	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "enabling device failed\n");
		वापस err;
	पूर्ण

	/* Mapping PCI BAR regions */
	err = pcim_iomap_regions(pdev, BIT(BAR_0), pci_name(pdev));
	अगर (err) अणु
		dev_err(dev, "xData BAR I/O remapping failed\n");
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	/* Allocate memory */
	dw = devm_kzalloc(dev, माप(*dw), GFP_KERNEL);
	अगर (!dw)
		वापस -ENOMEM;

	/* Data काष्ठाure initialization */
	mutex_init(&dw->mutex);

	dw->rg_region.vaddr = pcim_iomap_table(pdev)[BAR_0];
	अगर (!dw->rg_region.vaddr)
		वापस -ENOMEM;

	dw->rg_region.paddr = pdev->resource[BAR_0].start;

	dw->max_wr_len = pcie_get_mps(pdev);
	dw->max_wr_len >>= 2;

	dw->max_rd_len = pcie_get_पढ़ोrq(pdev);
	dw->max_rd_len >>= 2;

	dw->pdev = pdev;

	id = ida_simple_get(&xdata_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		dev_err(dev, "xData: unable to get id\n");
		वापस id;
	पूर्ण

	snम_लिखो(name, माप(name), DW_XDATA_DRIVER_NAME ".%d", id);
	dw->misc_dev.name = kstrdup(name, GFP_KERNEL);
	अगर (!dw->misc_dev.name) अणु
		err = -ENOMEM;
		जाओ err_ida_हटाओ;
	पूर्ण

	dw->misc_dev.minor = MISC_DYNAMIC_MINOR;
	dw->misc_dev.parent = dev;
	dw->misc_dev.groups = xdata_groups;

	ग_लिखोl(0x0, &(__dw_regs(dw)->RAM_addr));
	ग_लिखोl(0x0, &(__dw_regs(dw)->RAM_port));

	addr = dw->rg_region.paddr + DW_XDATA_EP_MEM_OFFSET;
	ग_लिखोl(lower_32_bits(addr), &(__dw_regs(dw)->addr_lsb));
	ग_लिखोl(upper_32_bits(addr), &(__dw_regs(dw)->addr_msb));
	dev_dbg(dev, "xData: target address = 0x%.16llx\n", addr);

	dev_dbg(dev, "xData: wr_len = %zu, rd_len = %zu\n",
		dw->max_wr_len * 4, dw->max_rd_len * 4);

	/* Saving data काष्ठाure reference */
	pci_set_drvdata(pdev, dw);

	/* Register misc device */
	err = misc_रेजिस्टर(&dw->misc_dev);
	अगर (err) अणु
		dev_err(dev, "xData: failed to register device\n");
		जाओ err_kमुक्त_name;
	पूर्ण

	वापस 0;

err_kमुक्त_name:
	kमुक्त(dw->misc_dev.name);

err_ida_हटाओ:
	ida_simple_हटाओ(&xdata_ida, id);

	वापस err;
पूर्ण

अटल व्योम dw_xdata_pcie_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा dw_xdata *dw = pci_get_drvdata(pdev);
	पूर्णांक id;

	अगर (माला_पूछो(dw->misc_dev.name, DW_XDATA_DRIVER_NAME ".%d", &id) != 1)
		वापस;

	अगर (id < 0)
		वापस;

	dw_xdata_stop(dw);
	misc_deरेजिस्टर(&dw->misc_dev);
	kमुक्त(dw->misc_dev.name);
	ida_simple_हटाओ(&xdata_ida, id);
पूर्ण

अटल स्थिर काष्ठा pci_device_id dw_xdata_pcie_id_table[] = अणु
	अणु PCI_DEVICE_DATA(SYNOPSYS, EDDA, शून्य) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dw_xdata_pcie_id_table);

अटल काष्ठा pci_driver dw_xdata_pcie_driver = अणु
	.name		= DW_XDATA_DRIVER_NAME,
	.id_table	= dw_xdata_pcie_id_table,
	.probe		= dw_xdata_pcie_probe,
	.हटाओ		= dw_xdata_pcie_हटाओ,
पूर्ण;

module_pci_driver(dw_xdata_pcie_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Synopsys DesignWare xData PCIe driver");
MODULE_AUTHOR("Gustavo Pimentel <gustavo.pimentel@synopsys.com>");

