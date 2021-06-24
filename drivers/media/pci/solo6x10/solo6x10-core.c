<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/delay.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>

#समावेश "solo6x10.h"
#समावेश "solo6x10-tw28.h"

MODULE_DESCRIPTION("Softlogic 6x10 MPEG4/H.264/G.723 CODEC V4L2/ALSA Driver");
MODULE_AUTHOR("Bluecherry <maintainers@bluecherrydvr.com>");
MODULE_VERSION(SOLO6X10_VERSION);
MODULE_LICENSE("GPL");

अटल अचिन्हित video_nr = -1;
module_param(video_nr, uपूर्णांक, 0644);
MODULE_PARM_DESC(video_nr, "videoX start number, -1 is autodetect (default)");

अटल पूर्णांक full_eeprom; /* शेष is only top 64B */
module_param(full_eeprom, uपूर्णांक, 0644);
MODULE_PARM_DESC(full_eeprom, "Allow access to full 128B EEPROM (dangerous)");


अटल व्योम solo_set_समय(काष्ठा solo_dev *solo_dev)
अणु
	काष्ठा बारpec64 ts;

	kसमय_get_ts64(&ts);

	/* no overflow because we use monotonic बारtamps */
	solo_reg_ग_लिखो(solo_dev, SOLO_TIMER_SEC, (u32)ts.tv_sec);
	solo_reg_ग_लिखो(solo_dev, SOLO_TIMER_USEC, (u32)ts.tv_nsec / NSEC_PER_USEC);
पूर्ण

अटल व्योम solo_समयr_sync(काष्ठा solo_dev *solo_dev)
अणु
	u32 sec, usec;
	काष्ठा बारpec64 ts;
	दीर्घ dअगरf;

	अगर (solo_dev->type != SOLO_DEV_6110)
		वापस;

	अगर (++solo_dev->समय_sync < 60)
		वापस;

	solo_dev->समय_sync = 0;

	sec = solo_reg_पढ़ो(solo_dev, SOLO_TIMER_SEC);
	usec = solo_reg_पढ़ो(solo_dev, SOLO_TIMER_USEC);

	kसमय_get_ts64(&ts);

	dअगरf = (s32)ts.tv_sec - (s32)sec;
	dअगरf = (dअगरf * 1000000)
		+ ((s32)(ts.tv_nsec / NSEC_PER_USEC) - (s32)usec);

	अगर (dअगरf > 1000 || dअगरf < -1000) अणु
		solo_set_समय(solo_dev);
	पूर्ण अन्यथा अगर (dअगरf) अणु
		दीर्घ usec_lsb = solo_dev->usec_lsb;

		usec_lsb -= dअगरf / 4;
		अगर (usec_lsb < 0)
			usec_lsb = 0;
		अन्यथा अगर (usec_lsb > 255)
			usec_lsb = 255;

		solo_dev->usec_lsb = usec_lsb;
		solo_reg_ग_लिखो(solo_dev, SOLO_TIMER_USEC_LSB,
			       solo_dev->usec_lsb);
	पूर्ण
पूर्ण

अटल irqवापस_t solo_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा solo_dev *solo_dev = data;
	u32 status;
	पूर्णांक i;

	status = solo_reg_पढ़ो(solo_dev, SOLO_IRQ_STAT);
	अगर (!status)
		वापस IRQ_NONE;

	/* Acknowledge all पूर्णांकerrupts immediately */
	solo_reg_ग_लिखो(solo_dev, SOLO_IRQ_STAT, status);

	अगर (status & SOLO_IRQ_PCI_ERR)
		solo_p2m_error_isr(solo_dev);

	क्रम (i = 0; i < SOLO_NR_P2M; i++)
		अगर (status & SOLO_IRQ_P2M(i))
			solo_p2m_isr(solo_dev, i);

	अगर (status & SOLO_IRQ_IIC)
		solo_i2c_isr(solo_dev);

	अगर (status & SOLO_IRQ_VIDEO_IN) अणु
		solo_video_in_isr(solo_dev);
		solo_समयr_sync(solo_dev);
	पूर्ण

	अगर (status & SOLO_IRQ_ENCODER)
		solo_enc_v4l2_isr(solo_dev);

	अगर (status & SOLO_IRQ_G723)
		solo_g723_isr(solo_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम मुक्त_solo_dev(काष्ठा solo_dev *solo_dev)
अणु
	काष्ठा pci_dev *pdev = solo_dev->pdev;

	अगर (solo_dev->dev.parent)
		device_unरेजिस्टर(&solo_dev->dev);

	अगर (solo_dev->reg_base) अणु
		/* Bring करोwn the sub-devices first */
		solo_g723_निकास(solo_dev);
		solo_enc_v4l2_निकास(solo_dev);
		solo_enc_निकास(solo_dev);
		solo_v4l2_निकास(solo_dev);
		solo_disp_निकास(solo_dev);
		solo_gpio_निकास(solo_dev);
		solo_p2m_निकास(solo_dev);
		solo_i2c_निकास(solo_dev);

		/* Now cleanup the PCI device */
		solo_irq_off(solo_dev, ~0);
		मुक्त_irq(pdev->irq, solo_dev);
		pci_iounmap(pdev, solo_dev->reg_base);
	पूर्ण

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	v4l2_device_unरेजिस्टर(&solo_dev->v4l2_dev);
	pci_set_drvdata(pdev, शून्य);

	kमुक्त(solo_dev);
पूर्ण

अटल sमाप_प्रकार eeprom_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);
	u16 *p = (u16 *)buf;
	पूर्णांक i;

	अगर (count & 0x1)
		dev_warn(dev, "EEPROM Write not aligned (truncating)\n");

	अगर (!full_eeprom && count > 64) अणु
		dev_warn(dev, "EEPROM Write truncated to 64 bytes\n");
		count = 64;
	पूर्ण अन्यथा अगर (full_eeprom && count > 128) अणु
		dev_warn(dev, "EEPROM Write truncated to 128 bytes\n");
		count = 128;
	पूर्ण

	solo_eeprom_ewen(solo_dev, 1);

	क्रम (i = full_eeprom ? 0 : 32; i < min((पूर्णांक)(full_eeprom ? 64 : 32),
					       (पूर्णांक)(count / 2)); i++)
		solo_eeprom_ग_लिखो(solo_dev, i, cpu_to_be16(p[i]));

	solo_eeprom_ewen(solo_dev, 0);

	वापस count;
पूर्ण

अटल sमाप_प्रकार eeprom_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);
	u16 *p = (u16 *)buf;
	पूर्णांक count = (full_eeprom ? 128 : 64);
	पूर्णांक i;

	क्रम (i = (full_eeprom ? 0 : 32); i < (count / 2); i++)
		p[i] = be16_to_cpu(solo_eeprom_पढ़ो(solo_dev, i));

	वापस count;
पूर्ण

अटल sमाप_प्रकार p2m_समयouts_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);

	वापस प्र_लिखो(buf, "%d\n", solo_dev->p2m_समयouts);
पूर्ण

अटल sमाप_प्रकार sdram_size_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);

	वापस प्र_लिखो(buf, "%dMegs\n", solo_dev->sdram_size >> 20);
पूर्ण

अटल sमाप_प्रकार tw28xx_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);

	वापस प्र_लिखो(buf, "tw2815[%d] tw2864[%d] tw2865[%d]\n",
		       hweight32(solo_dev->tw2815),
		       hweight32(solo_dev->tw2864),
		       hweight32(solo_dev->tw2865));
पूर्ण

अटल sमाप_प्रकार input_map_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);
	अचिन्हित पूर्णांक val;
	अक्षर *out = buf;

	val = solo_reg_पढ़ो(solo_dev, SOLO_VI_CH_SWITCH_0);
	out += प्र_लिखो(out, "Channel 0   => Input %d\n", val & 0x1f);
	out += प्र_लिखो(out, "Channel 1   => Input %d\n", (val >> 5) & 0x1f);
	out += प्र_लिखो(out, "Channel 2   => Input %d\n", (val >> 10) & 0x1f);
	out += प्र_लिखो(out, "Channel 3   => Input %d\n", (val >> 15) & 0x1f);
	out += प्र_लिखो(out, "Channel 4   => Input %d\n", (val >> 20) & 0x1f);
	out += प्र_लिखो(out, "Channel 5   => Input %d\n", (val >> 25) & 0x1f);

	val = solo_reg_पढ़ो(solo_dev, SOLO_VI_CH_SWITCH_1);
	out += प्र_लिखो(out, "Channel 6   => Input %d\n", val & 0x1f);
	out += प्र_लिखो(out, "Channel 7   => Input %d\n", (val >> 5) & 0x1f);
	out += प्र_लिखो(out, "Channel 8   => Input %d\n", (val >> 10) & 0x1f);
	out += प्र_लिखो(out, "Channel 9   => Input %d\n", (val >> 15) & 0x1f);
	out += प्र_लिखो(out, "Channel 10  => Input %d\n", (val >> 20) & 0x1f);
	out += प्र_लिखो(out, "Channel 11  => Input %d\n", (val >> 25) & 0x1f);

	val = solo_reg_पढ़ो(solo_dev, SOLO_VI_CH_SWITCH_2);
	out += प्र_लिखो(out, "Channel 12  => Input %d\n", val & 0x1f);
	out += प्र_लिखो(out, "Channel 13  => Input %d\n", (val >> 5) & 0x1f);
	out += प्र_लिखो(out, "Channel 14  => Input %d\n", (val >> 10) & 0x1f);
	out += प्र_लिखो(out, "Channel 15  => Input %d\n", (val >> 15) & 0x1f);
	out += प्र_लिखो(out, "Spot Output => Input %d\n", (val >> 20) & 0x1f);

	वापस out - buf;
पूर्ण

अटल sमाप_प्रकार p2m_समयout_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);
	अचिन्हित दीर्घ ms;
	पूर्णांक ret = kम_से_अदीर्घ(buf, 10, &ms);

	अगर (ret < 0 || ms > 200)
		वापस -EINVAL;
	solo_dev->p2m_jअगरfies = msecs_to_jअगरfies(ms);

	वापस count;
पूर्ण

अटल sमाप_प्रकार p2m_समयout_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);

	वापस प्र_लिखो(buf, "%ums\n", jअगरfies_to_msecs(solo_dev->p2m_jअगरfies));
पूर्ण

अटल sमाप_प्रकार पूर्णांकervals_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);
	अक्षर *out = buf;
	पूर्णांक fps = solo_dev->fps;
	पूर्णांक i;

	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		out += प्र_लिखो(out, "Channel %d: %d/%d (0x%08x)\n",
			       i, solo_dev->v4l2_enc[i]->पूर्णांकerval, fps,
			       solo_reg_पढ़ो(solo_dev, SOLO_CAP_CH_INTV(i)));
	पूर्ण

	वापस out - buf;
पूर्ण

अटल sमाप_प्रकार sdram_offsets_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);
	अक्षर *out = buf;

	out += प्र_लिखो(out, "DISP: 0x%08x @ 0x%08x\n",
		       SOLO_DISP_EXT_ADDR,
		       SOLO_DISP_EXT_SIZE);

	out += प्र_लिखो(out, "EOSD: 0x%08x @ 0x%08x (0x%08x * %d)\n",
		       SOLO_EOSD_EXT_ADDR,
		       SOLO_EOSD_EXT_AREA(solo_dev),
		       SOLO_EOSD_EXT_SIZE(solo_dev),
		       SOLO_EOSD_EXT_AREA(solo_dev) /
		       SOLO_EOSD_EXT_SIZE(solo_dev));

	out += प्र_लिखो(out, "MOTI: 0x%08x @ 0x%08x\n",
		       SOLO_MOTION_EXT_ADDR(solo_dev),
		       SOLO_MOTION_EXT_SIZE);

	out += प्र_लिखो(out, "G723: 0x%08x @ 0x%08x\n",
		       SOLO_G723_EXT_ADDR(solo_dev),
		       SOLO_G723_EXT_SIZE);

	out += प्र_लिखो(out, "CAPT: 0x%08x @ 0x%08x (0x%08x * %d)\n",
		       SOLO_CAP_EXT_ADDR(solo_dev),
		       SOLO_CAP_EXT_SIZE(solo_dev),
		       SOLO_CAP_PAGE_SIZE,
		       SOLO_CAP_EXT_SIZE(solo_dev) / SOLO_CAP_PAGE_SIZE);

	out += प्र_लिखो(out, "EREF: 0x%08x @ 0x%08x (0x%08x * %d)\n",
		       SOLO_EREF_EXT_ADDR(solo_dev),
		       SOLO_EREF_EXT_AREA(solo_dev),
		       SOLO_EREF_EXT_SIZE,
		       SOLO_EREF_EXT_AREA(solo_dev) / SOLO_EREF_EXT_SIZE);

	out += प्र_लिखो(out, "MPEG: 0x%08x @ 0x%08x\n",
		       SOLO_MP4E_EXT_ADDR(solo_dev),
		       SOLO_MP4E_EXT_SIZE(solo_dev));

	out += प्र_लिखो(out, "JPEG: 0x%08x @ 0x%08x\n",
		       SOLO_JPEG_EXT_ADDR(solo_dev),
		       SOLO_JPEG_EXT_SIZE(solo_dev));

	वापस out - buf;
पूर्ण

अटल sमाप_प्रकार sdram_show(काष्ठा file *file, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *a, अक्षर *buf,
			  loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा solo_dev *solo_dev =
		container_of(dev, काष्ठा solo_dev, dev);
	स्थिर पूर्णांक size = solo_dev->sdram_size;

	अगर (off >= size)
		वापस 0;

	अगर (off + count > size)
		count = size - off;

	अगर (solo_p2m_dma(solo_dev, 0, buf, off, count, 0, 0))
		वापस -EIO;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा device_attribute solo_dev_attrs[] = अणु
	__ATTR(eeprom, 0640, eeprom_show, eeprom_store),
	__ATTR(p2m_समयout, 0644, p2m_समयout_show, p2m_समयout_store),
	__ATTR_RO(p2m_समयouts),
	__ATTR_RO(sdram_size),
	__ATTR_RO(tw28xx),
	__ATTR_RO(input_map),
	__ATTR_RO(पूर्णांकervals),
	__ATTR_RO(sdram_offsets),
पूर्ण;

अटल व्योम solo_device_release(काष्ठा device *dev)
अणु
	/* Do nothing */
पूर्ण

अटल पूर्णांक solo_sysfs_init(काष्ठा solo_dev *solo_dev)
अणु
	काष्ठा bin_attribute *sdram_attr = &solo_dev->sdram_attr;
	काष्ठा device *dev = &solo_dev->dev;
	स्थिर अक्षर *driver;
	पूर्णांक i;

	अगर (solo_dev->type == SOLO_DEV_6110)
		driver = "solo6110";
	अन्यथा
		driver = "solo6010";

	dev->release = solo_device_release;
	dev->parent = &solo_dev->pdev->dev;
	set_dev_node(dev, dev_to_node(&solo_dev->pdev->dev));
	dev_set_name(dev, "%s-%d-%d", driver, solo_dev->vfd->num,
		     solo_dev->nr_chans);

	अगर (device_रेजिस्टर(dev)) अणु
		dev->parent = शून्य;
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(solo_dev_attrs); i++) अणु
		अगर (device_create_file(dev, &solo_dev_attrs[i])) अणु
			device_unरेजिस्टर(dev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	sysfs_attr_init(&sdram_attr->attr);
	sdram_attr->attr.name = "sdram";
	sdram_attr->attr.mode = 0440;
	sdram_attr->पढ़ो = sdram_show;
	sdram_attr->size = solo_dev->sdram_size;

	अगर (device_create_bin_file(dev, sdram_attr)) अणु
		device_unरेजिस्टर(dev);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक solo_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा solo_dev *solo_dev;
	पूर्णांक ret;
	u8 chip_id;

	solo_dev = kzalloc(माप(*solo_dev), GFP_KERNEL);
	अगर (solo_dev == शून्य)
		वापस -ENOMEM;

	अगर (id->driver_data == SOLO_DEV_6010)
		dev_info(&pdev->dev, "Probing Softlogic 6010\n");
	अन्यथा
		dev_info(&pdev->dev, "Probing Softlogic 6110\n");

	solo_dev->type = id->driver_data;
	solo_dev->pdev = pdev;
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &solo_dev->v4l2_dev);
	अगर (ret)
		जाओ fail_probe;

	/* Only क्रम during init */
	solo_dev->p2m_jअगरfies = msecs_to_jअगरfies(100);

	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ fail_probe;

	pci_set_master(pdev);

	/* RETRY/TRDY Timeout disabled */
	pci_ग_लिखो_config_byte(pdev, 0x40, 0x00);
	pci_ग_लिखो_config_byte(pdev, 0x41, 0x00);

	ret = pci_request_regions(pdev, SOLO6X10_NAME);
	अगर (ret)
		जाओ fail_probe;

	solo_dev->reg_base = pci_ioremap_bar(pdev, 0);
	अगर (solo_dev->reg_base == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail_probe;
	पूर्ण

	chip_id = solo_reg_पढ़ो(solo_dev, SOLO_CHIP_OPTION) &
				SOLO_CHIP_ID_MASK;
	चयन (chip_id) अणु
	हाल 7:
		solo_dev->nr_chans = 16;
		solo_dev->nr_ext = 5;
		अवरोध;
	हाल 6:
		solo_dev->nr_chans = 8;
		solo_dev->nr_ext = 2;
		अवरोध;
	शेष:
		dev_warn(&pdev->dev, "Invalid chip_id 0x%02x, assuming 4 ch\n",
			 chip_id);
		fallthrough;
	हाल 5:
		solo_dev->nr_chans = 4;
		solo_dev->nr_ext = 1;
	पूर्ण

	/* Disable all पूर्णांकerrupts to start */
	solo_irq_off(solo_dev, ~0);

	/* Initial global settings */
	अगर (solo_dev->type == SOLO_DEV_6010) अणु
		solo_dev->घड़ी_mhz = 108;
		solo_dev->sys_config = SOLO_SYS_CFG_SDRAM64BIT
			| SOLO_SYS_CFG_INPUTDIV(25)
			| SOLO_SYS_CFG_FEEDBACKDIV(solo_dev->घड़ी_mhz * 2 - 2)
			| SOLO_SYS_CFG_OUTDIV(3);
		solo_reg_ग_लिखो(solo_dev, SOLO_SYS_CFG, solo_dev->sys_config);
	पूर्ण अन्यथा अणु
		u32 भागq, भागf;

		solo_dev->घड़ी_mhz = 135;

		अगर (solo_dev->घड़ी_mhz < 125) अणु
			भागq = 3;
			भागf = (solo_dev->घड़ी_mhz * 4) / 3 - 1;
		पूर्ण अन्यथा अणु
			भागq = 2;
			भागf = (solo_dev->घड़ी_mhz * 2) / 3 - 1;
		पूर्ण

		solo_reg_ग_लिखो(solo_dev, SOLO_PLL_CONFIG,
			       (1 << 20) | /* PLL_RANGE */
			       (8 << 15) | /* PLL_DIVR  */
			       (भागq << 12) |
			       (भागf <<  4) |
			       (1 <<  1)   /* PLL_FSEN */);

		solo_dev->sys_config = SOLO_SYS_CFG_SDRAM64BIT;
	पूर्ण

	solo_reg_ग_लिखो(solo_dev, SOLO_SYS_CFG, solo_dev->sys_config);
	solo_reg_ग_लिखो(solo_dev, SOLO_TIMER_CLOCK_NUM,
		       solo_dev->घड़ी_mhz - 1);

	/* PLL locking समय of 1ms */
	mdelay(1);

	ret = request_irq(pdev->irq, solo_isr, IRQF_SHARED, SOLO6X10_NAME,
			  solo_dev);
	अगर (ret)
		जाओ fail_probe;

	/* Handle this from the start */
	solo_irq_on(solo_dev, SOLO_IRQ_PCI_ERR);

	ret = solo_i2c_init(solo_dev);
	अगर (ret)
		जाओ fail_probe;

	/* Setup the DMA engine */
	solo_reg_ग_लिखो(solo_dev, SOLO_DMA_CTRL,
		       SOLO_DMA_CTRL_REFRESH_CYCLE(1) |
		       SOLO_DMA_CTRL_SDRAM_SIZE(2) |
		       SOLO_DMA_CTRL_SDRAM_CLK_INVERT |
		       SOLO_DMA_CTRL_READ_CLK_SELECT |
		       SOLO_DMA_CTRL_LATENCY(1));

	/* Unकरोcumented crap */
	solo_reg_ग_लिखो(solo_dev, SOLO_DMA_CTRL1,
		       solo_dev->type == SOLO_DEV_6010 ? 0x100 : 0x300);

	अगर (solo_dev->type != SOLO_DEV_6010) अणु
		solo_dev->usec_lsb = 0x3f;
		solo_set_समय(solo_dev);
	पूर्ण

	/* Disable watchकरोg */
	solo_reg_ग_लिखो(solo_dev, SOLO_WATCHDOG, 0);

	/* Initialize sub components */

	ret = solo_p2m_init(solo_dev);
	अगर (ret)
		जाओ fail_probe;

	ret = solo_disp_init(solo_dev);
	अगर (ret)
		जाओ fail_probe;

	ret = solo_gpio_init(solo_dev);
	अगर (ret)
		जाओ fail_probe;

	ret = solo_tw28_init(solo_dev);
	अगर (ret)
		जाओ fail_probe;

	ret = solo_v4l2_init(solo_dev, video_nr);
	अगर (ret)
		जाओ fail_probe;

	ret = solo_enc_init(solo_dev);
	अगर (ret)
		जाओ fail_probe;

	ret = solo_enc_v4l2_init(solo_dev, video_nr);
	अगर (ret)
		जाओ fail_probe;

	ret = solo_g723_init(solo_dev);
	अगर (ret)
		जाओ fail_probe;

	ret = solo_sysfs_init(solo_dev);
	अगर (ret)
		जाओ fail_probe;

	/* Now that init is over, set this lower */
	solo_dev->p2m_jअगरfies = msecs_to_jअगरfies(20);

	वापस 0;

fail_probe:
	मुक्त_solo_dev(solo_dev);
	वापस ret;
पूर्ण

अटल व्योम solo_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pdev);
	काष्ठा solo_dev *solo_dev = container_of(v4l2_dev, काष्ठा solo_dev, v4l2_dev);

	मुक्त_solo_dev(solo_dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id solo_id_table[] = अणु
	/* 6010 based cards */
	अणु PCI_DEVICE(PCI_VENDOR_ID_SOFTLOGIC, PCI_DEVICE_ID_SOLO6010),
	  .driver_data = SOLO_DEV_6010 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_NEUSOLO_4),
	  .driver_data = SOLO_DEV_6010 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_NEUSOLO_9),
	  .driver_data = SOLO_DEV_6010 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_NEUSOLO_16),
	  .driver_data = SOLO_DEV_6010 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_BC_SOLO_4),
	  .driver_data = SOLO_DEV_6010 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_BC_SOLO_9),
	  .driver_data = SOLO_DEV_6010 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_BC_SOLO_16),
	  .driver_data = SOLO_DEV_6010 पूर्ण,
	/* 6110 based cards */
	अणु PCI_DEVICE(PCI_VENDOR_ID_SOFTLOGIC, PCI_DEVICE_ID_SOLO6110),
	  .driver_data = SOLO_DEV_6110 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_BC_6110_4),
	  .driver_data = SOLO_DEV_6110 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_BC_6110_8),
	  .driver_data = SOLO_DEV_6110 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BLUECHERRY, PCI_DEVICE_ID_BC_6110_16),
	  .driver_data = SOLO_DEV_6110 पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, solo_id_table);

अटल काष्ठा pci_driver solo_pci_driver = अणु
	.name = SOLO6X10_NAME,
	.id_table = solo_id_table,
	.probe = solo_pci_probe,
	.हटाओ = solo_pci_हटाओ,
पूर्ण;

module_pci_driver(solo_pci_driver);
