<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 device registration routines.
 *
 *  Copyright (C) 2007 Sony Computer Entertainment Inc.
 *  Copyright 2007 Sony Corp.
 */

#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/reboot.h>
#समावेश <linux/rcuरुको.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3stor.h>

#समावेश "platform.h"

अटल पूर्णांक __init ps3_रेजिस्टर_lpm_devices(व्योम)
अणु
	पूर्णांक result;
	u64 पंचांगp1;
	u64 पंचांगp2;
	काष्ठा ps3_प्रणाली_bus_device *dev;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->match_id = PS3_MATCH_ID_LPM;
	dev->dev_type = PS3_DEVICE_TYPE_LPM;

	/* The current lpm driver only supports a single BE processor. */

	result = ps3_repository_पढ़ो_be_node_id(0, &dev->lpm.node_id);

	अगर (result) अणु
		pr_debug("%s:%d: ps3_repository_read_be_node_id failed \n",
			__func__, __LINE__);
		जाओ fail_पढ़ो_repo;
	पूर्ण

	result = ps3_repository_पढ़ो_lpm_privileges(dev->lpm.node_id, &पंचांगp1,
		&dev->lpm.rights);

	अगर (result) अणु
		pr_debug("%s:%d: ps3_repository_read_lpm_privileges failed\n",
			__func__, __LINE__);
		जाओ fail_पढ़ो_repo;
	पूर्ण

	lv1_get_logical_partition_id(&पंचांगp2);

	अगर (पंचांगp1 != पंचांगp2) अणु
		pr_debug("%s:%d: wrong lpar\n",
			__func__, __LINE__);
		result = -ENODEV;
		जाओ fail_rights;
	पूर्ण

	अगर (!(dev->lpm.rights & PS3_LPM_RIGHTS_USE_LPM)) अणु
		pr_debug("%s:%d: don't have rights to use lpm\n",
			__func__, __LINE__);
		result = -EPERM;
		जाओ fail_rights;
	पूर्ण

	pr_debug("%s:%d: pu_id %llu, rights %llu(%llxh)\n",
		__func__, __LINE__, dev->lpm.pu_id, dev->lpm.rights,
		dev->lpm.rights);

	result = ps3_repository_पढ़ो_pu_id(0, &dev->lpm.pu_id);

	अगर (result) अणु
		pr_debug("%s:%d: ps3_repository_read_pu_id failed \n",
			__func__, __LINE__);
		जाओ fail_पढ़ो_repo;
	पूर्ण

	result = ps3_प्रणाली_bus_device_रेजिस्टर(dev);

	अगर (result) अणु
		pr_debug("%s:%d ps3_system_bus_device_register failed\n",
			__func__, __LINE__);
		जाओ fail_रेजिस्टर;
	पूर्ण

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस 0;


fail_रेजिस्टर:
fail_rights:
fail_पढ़ो_repo:
	kमुक्त(dev);
	pr_debug(" <- %s:%d: failed\n", __func__, __LINE__);
	वापस result;
पूर्ण

/**
 * ps3_setup_gelic_device - Setup and रेजिस्टर a gelic device instance.
 *
 * Allocates memory क्रम a काष्ठा ps3_प्रणाली_bus_device instance, initialises the
 * काष्ठाure members, and रेजिस्टरs the device instance with the प्रणाली bus.
 */

अटल पूर्णांक __init ps3_setup_gelic_device(
	स्थिर काष्ठा ps3_repository_device *repo)
अणु
	पूर्णांक result;
	काष्ठा layout अणु
		काष्ठा ps3_प्रणाली_bus_device dev;
		काष्ठा ps3_dma_region d_region;
	पूर्ण *p;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	BUG_ON(repo->bus_type != PS3_BUS_TYPE_SB);
	BUG_ON(repo->dev_type != PS3_DEV_TYPE_SB_GELIC);

	p = kzalloc(माप(काष्ठा layout), GFP_KERNEL);

	अगर (!p) अणु
		result = -ENOMEM;
		जाओ fail_दो_स्मृति;
	पूर्ण

	p->dev.match_id = PS3_MATCH_ID_GELIC;
	p->dev.dev_type = PS3_DEVICE_TYPE_SB;
	p->dev.bus_id = repo->bus_id;
	p->dev.dev_id = repo->dev_id;
	p->dev.d_region = &p->d_region;

	result = ps3_repository_find_पूर्णांकerrupt(repo,
		PS3_INTERRUPT_TYPE_EVENT_PORT, &p->dev.पूर्णांकerrupt_id);

	अगर (result) अणु
		pr_debug("%s:%d ps3_repository_find_interrupt failed\n",
			__func__, __LINE__);
		जाओ fail_find_पूर्णांकerrupt;
	पूर्ण

	BUG_ON(p->dev.पूर्णांकerrupt_id != 0);

	result = ps3_dma_region_init(&p->dev, p->dev.d_region, PS3_DMA_64K,
		PS3_DMA_OTHER, शून्य, 0);

	अगर (result) अणु
		pr_debug("%s:%d ps3_dma_region_init failed\n",
			__func__, __LINE__);
		जाओ fail_dma_init;
	पूर्ण

	result = ps3_प्रणाली_bus_device_रेजिस्टर(&p->dev);

	अगर (result) अणु
		pr_debug("%s:%d ps3_system_bus_device_register failed\n",
			__func__, __LINE__);
		जाओ fail_device_रेजिस्टर;
	पूर्ण

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस result;

fail_device_रेजिस्टर:
fail_dma_init:
fail_find_पूर्णांकerrupt:
	kमुक्त(p);
fail_दो_स्मृति:
	pr_debug(" <- %s:%d: fail.\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक __ref ps3_setup_uhc_device(
	स्थिर काष्ठा ps3_repository_device *repo, क्रमागत ps3_match_id match_id,
	क्रमागत ps3_पूर्णांकerrupt_type पूर्णांकerrupt_type, क्रमागत ps3_reg_type reg_type)
अणु
	पूर्णांक result;
	काष्ठा layout अणु
		काष्ठा ps3_प्रणाली_bus_device dev;
		काष्ठा ps3_dma_region d_region;
		काष्ठा ps3_mmio_region m_region;
	पूर्ण *p;
	u64 bus_addr;
	u64 len;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	BUG_ON(repo->bus_type != PS3_BUS_TYPE_SB);
	BUG_ON(repo->dev_type != PS3_DEV_TYPE_SB_USB);

	p = kzalloc(माप(काष्ठा layout), GFP_KERNEL);

	अगर (!p) अणु
		result = -ENOMEM;
		जाओ fail_दो_स्मृति;
	पूर्ण

	p->dev.match_id = match_id;
	p->dev.dev_type = PS3_DEVICE_TYPE_SB;
	p->dev.bus_id = repo->bus_id;
	p->dev.dev_id = repo->dev_id;
	p->dev.d_region = &p->d_region;
	p->dev.m_region = &p->m_region;

	result = ps3_repository_find_पूर्णांकerrupt(repo,
		पूर्णांकerrupt_type, &p->dev.पूर्णांकerrupt_id);

	अगर (result) अणु
		pr_debug("%s:%d ps3_repository_find_interrupt failed\n",
			__func__, __LINE__);
		जाओ fail_find_पूर्णांकerrupt;
	पूर्ण

	result = ps3_repository_find_reg(repo, reg_type,
		&bus_addr, &len);

	अगर (result) अणु
		pr_debug("%s:%d ps3_repository_find_reg failed\n",
			__func__, __LINE__);
		जाओ fail_find_reg;
	पूर्ण

	result = ps3_dma_region_init(&p->dev, p->dev.d_region, PS3_DMA_64K,
		PS3_DMA_INTERNAL, शून्य, 0);

	अगर (result) अणु
		pr_debug("%s:%d ps3_dma_region_init failed\n",
			__func__, __LINE__);
		जाओ fail_dma_init;
	पूर्ण

	result = ps3_mmio_region_init(&p->dev, p->dev.m_region, bus_addr, len,
		PS3_MMIO_4K);

	अगर (result) अणु
		pr_debug("%s:%d ps3_mmio_region_init failed\n",
			__func__, __LINE__);
		जाओ fail_mmio_init;
	पूर्ण

	result = ps3_प्रणाली_bus_device_रेजिस्टर(&p->dev);

	अगर (result) अणु
		pr_debug("%s:%d ps3_system_bus_device_register failed\n",
			__func__, __LINE__);
		जाओ fail_device_रेजिस्टर;
	पूर्ण

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस result;

fail_device_रेजिस्टर:
fail_mmio_init:
fail_dma_init:
fail_find_reg:
fail_find_पूर्णांकerrupt:
	kमुक्त(p);
fail_दो_स्मृति:
	pr_debug(" <- %s:%d: fail.\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक __init ps3_setup_ehci_device(
	स्थिर काष्ठा ps3_repository_device *repo)
अणु
	वापस ps3_setup_uhc_device(repo, PS3_MATCH_ID_EHCI,
		PS3_INTERRUPT_TYPE_SB_EHCI, PS3_REG_TYPE_SB_EHCI);
पूर्ण

अटल पूर्णांक __init ps3_setup_ohci_device(
	स्थिर काष्ठा ps3_repository_device *repo)
अणु
	वापस ps3_setup_uhc_device(repo, PS3_MATCH_ID_OHCI,
		PS3_INTERRUPT_TYPE_SB_OHCI, PS3_REG_TYPE_SB_OHCI);
पूर्ण

अटल पूर्णांक __init ps3_setup_vuart_device(क्रमागत ps3_match_id match_id,
	अचिन्हित पूर्णांक port_number)
अणु
	पूर्णांक result;
	काष्ठा layout अणु
		काष्ठा ps3_प्रणाली_bus_device dev;
	पूर्ण *p;

	pr_debug(" -> %s:%d: match_id %u, port %u\n", __func__, __LINE__,
		match_id, port_number);

	p = kzalloc(माप(काष्ठा layout), GFP_KERNEL);

	अगर (!p)
		वापस -ENOMEM;

	p->dev.match_id = match_id;
	p->dev.dev_type = PS3_DEVICE_TYPE_VUART;
	p->dev.port_number = port_number;

	result = ps3_प्रणाली_bus_device_रेजिस्टर(&p->dev);

	अगर (result) अणु
		pr_debug("%s:%d ps3_system_bus_device_register failed\n",
			__func__, __LINE__);
		जाओ fail_device_रेजिस्टर;
	पूर्ण
	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस 0;

fail_device_रेजिस्टर:
	kमुक्त(p);
	pr_debug(" <- %s:%d fail\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक ps3_setup_storage_dev(स्थिर काष्ठा ps3_repository_device *repo,
				 क्रमागत ps3_match_id match_id)
अणु
	पूर्णांक result;
	काष्ठा ps3_storage_device *p;
	u64 port, blk_size, num_blocks;
	अचिन्हित पूर्णांक num_regions, i;

	pr_debug(" -> %s:%u: match_id %u\n", __func__, __LINE__, match_id);

	result = ps3_repository_पढ़ो_stor_dev_info(repo->bus_index,
						   repo->dev_index, &port,
						   &blk_size, &num_blocks,
						   &num_regions);
	अगर (result) अणु
		prपूर्णांकk(KERN_ERR "%s:%u: _read_stor_dev_info failed %d\n",
		       __func__, __LINE__, result);
		वापस -ENODEV;
	पूर्ण

	pr_debug("%s:%u: (%u:%u:%u): port %llu blk_size %llu num_blocks %llu "
		 "num_regions %u\n", __func__, __LINE__, repo->bus_index,
		 repo->dev_index, repo->dev_type, port, blk_size, num_blocks,
		 num_regions);

	p = kzalloc(काष्ठा_size(p, regions, num_regions), GFP_KERNEL);
	अगर (!p) अणु
		result = -ENOMEM;
		जाओ fail_दो_स्मृति;
	पूर्ण

	p->sbd.match_id = match_id;
	p->sbd.dev_type = PS3_DEVICE_TYPE_SB;
	p->sbd.bus_id = repo->bus_id;
	p->sbd.dev_id = repo->dev_id;
	p->sbd.d_region = &p->dma_region;
	p->blk_size = blk_size;
	p->num_regions = num_regions;

	result = ps3_repository_find_पूर्णांकerrupt(repo,
					       PS3_INTERRUPT_TYPE_EVENT_PORT,
					       &p->sbd.पूर्णांकerrupt_id);
	अगर (result) अणु
		prपूर्णांकk(KERN_ERR "%s:%u: find_interrupt failed %d\n", __func__,
		       __LINE__, result);
		result = -ENODEV;
		जाओ fail_find_पूर्णांकerrupt;
	पूर्ण

	क्रम (i = 0; i < num_regions; i++) अणु
		अचिन्हित पूर्णांक id;
		u64 start, size;

		result = ps3_repository_पढ़ो_stor_dev_region(repo->bus_index,
							     repo->dev_index,
							     i, &id, &start,
							     &size);
		अगर (result) अणु
			prपूर्णांकk(KERN_ERR
			       "%s:%u: read_stor_dev_region failed %d\n",
			       __func__, __LINE__, result);
			result = -ENODEV;
			जाओ fail_पढ़ो_region;
		पूर्ण
		pr_debug("%s:%u: region %u: id %u start %llu size %llu\n",
			 __func__, __LINE__, i, id, start, size);

		p->regions[i].id = id;
		p->regions[i].start = start;
		p->regions[i].size = size;
	पूर्ण

	result = ps3_प्रणाली_bus_device_रेजिस्टर(&p->sbd);
	अगर (result) अणु
		pr_debug("%s:%u ps3_system_bus_device_register failed\n",
			 __func__, __LINE__);
		जाओ fail_device_रेजिस्टर;
	पूर्ण

	pr_debug(" <- %s:%u\n", __func__, __LINE__);
	वापस 0;

fail_device_रेजिस्टर:
fail_पढ़ो_region:
fail_find_पूर्णांकerrupt:
	kमुक्त(p);
fail_दो_स्मृति:
	pr_debug(" <- %s:%u: fail.\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक __init ps3_रेजिस्टर_vuart_devices(व्योम)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक port_number;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	result = ps3_repository_पढ़ो_vuart_av_port(&port_number);
	अगर (result)
		port_number = 0; /* av शेष */

	result = ps3_setup_vuart_device(PS3_MATCH_ID_AV_SETTINGS, port_number);
	WARN_ON(result);

	result = ps3_repository_पढ़ो_vuart_sysmgr_port(&port_number);
	अगर (result)
		port_number = 2; /* sysmgr शेष */

	result = ps3_setup_vuart_device(PS3_MATCH_ID_SYSTEM_MANAGER,
		port_number);
	WARN_ON(result);

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक __init ps3_रेजिस्टर_sound_devices(व्योम)
अणु
	पूर्णांक result;
	काष्ठा layout अणु
		काष्ठा ps3_प्रणाली_bus_device dev;
		काष्ठा ps3_dma_region d_region;
		काष्ठा ps3_mmio_region m_region;
	पूर्ण *p;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->dev.match_id = PS3_MATCH_ID_SOUND;
	p->dev.dev_type = PS3_DEVICE_TYPE_IOC0;
	p->dev.d_region = &p->d_region;
	p->dev.m_region = &p->m_region;

	result = ps3_प्रणाली_bus_device_रेजिस्टर(&p->dev);

	अगर (result) अणु
		pr_debug("%s:%d ps3_system_bus_device_register failed\n",
			__func__, __LINE__);
		जाओ fail_device_रेजिस्टर;
	पूर्ण
	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस 0;

fail_device_रेजिस्टर:
	kमुक्त(p);
	pr_debug(" <- %s:%d failed\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक __init ps3_रेजिस्टर_graphics_devices(व्योम)
अणु
	पूर्णांक result;
	काष्ठा layout अणु
		काष्ठा ps3_प्रणाली_bus_device dev;
	पूर्ण *p;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	p = kzalloc(माप(काष्ठा layout), GFP_KERNEL);

	अगर (!p)
		वापस -ENOMEM;

	p->dev.match_id = PS3_MATCH_ID_GPU;
	p->dev.match_sub_id = PS3_MATCH_SUB_ID_GPU_FB;
	p->dev.dev_type = PS3_DEVICE_TYPE_IOC0;

	result = ps3_प्रणाली_bus_device_रेजिस्टर(&p->dev);

	अगर (result) अणु
		pr_debug("%s:%d ps3_system_bus_device_register failed\n",
			__func__, __LINE__);
		जाओ fail_device_रेजिस्टर;
	पूर्ण

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस 0;

fail_device_रेजिस्टर:
	kमुक्त(p);
	pr_debug(" <- %s:%d failed\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक __init ps3_रेजिस्टर_ramdisk_device(व्योम)
अणु
	पूर्णांक result;
	काष्ठा layout अणु
		काष्ठा ps3_प्रणाली_bus_device dev;
	पूर्ण *p;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	p = kzalloc(माप(काष्ठा layout), GFP_KERNEL);

	अगर (!p)
		वापस -ENOMEM;

	p->dev.match_id = PS3_MATCH_ID_GPU;
	p->dev.match_sub_id = PS3_MATCH_SUB_ID_GPU_RAMDISK;
	p->dev.dev_type = PS3_DEVICE_TYPE_IOC0;

	result = ps3_प्रणाली_bus_device_रेजिस्टर(&p->dev);

	अगर (result) अणु
		pr_debug("%s:%d ps3_system_bus_device_register failed\n",
			__func__, __LINE__);
		जाओ fail_device_रेजिस्टर;
	पूर्ण

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस 0;

fail_device_रेजिस्टर:
	kमुक्त(p);
	pr_debug(" <- %s:%d failed\n", __func__, __LINE__);
	वापस result;
पूर्ण

/**
 * ps3_setup_dynamic_device - Setup a dynamic device from the repository
 */

अटल पूर्णांक ps3_setup_dynamic_device(स्थिर काष्ठा ps3_repository_device *repo)
अणु
	पूर्णांक result;

	चयन (repo->dev_type) अणु
	हाल PS3_DEV_TYPE_STOR_DISK:
		result = ps3_setup_storage_dev(repo, PS3_MATCH_ID_STOR_DISK);

		/* Some devices are not accessible from the Other OS lpar. */
		अगर (result == -ENODEV) अणु
			result = 0;
			pr_debug("%s:%u: not accessible\n", __func__,
				 __LINE__);
		पूर्ण

		अगर (result)
			pr_debug("%s:%u ps3_setup_storage_dev failed\n",
				 __func__, __LINE__);
		अवरोध;

	हाल PS3_DEV_TYPE_STOR_ROM:
		result = ps3_setup_storage_dev(repo, PS3_MATCH_ID_STOR_ROM);
		अगर (result)
			pr_debug("%s:%u ps3_setup_storage_dev failed\n",
				 __func__, __LINE__);
		अवरोध;

	हाल PS3_DEV_TYPE_STOR_FLASH:
		result = ps3_setup_storage_dev(repo, PS3_MATCH_ID_STOR_FLASH);
		अगर (result)
			pr_debug("%s:%u ps3_setup_storage_dev failed\n",
				 __func__, __LINE__);
		अवरोध;

	शेष:
		result = 0;
		pr_debug("%s:%u: unsupported dev_type %u\n", __func__, __LINE__,
			repo->dev_type);
	पूर्ण

	वापस result;
पूर्ण

/**
 * ps3_setup_अटल_device - Setup a अटल device from the repository
 */

अटल पूर्णांक __init ps3_setup_अटल_device(स्थिर काष्ठा ps3_repository_device *repo)
अणु
	पूर्णांक result;

	चयन (repo->dev_type) अणु
	हाल PS3_DEV_TYPE_SB_GELIC:
		result = ps3_setup_gelic_device(repo);
		अगर (result) अणु
			pr_debug("%s:%d ps3_setup_gelic_device failed\n",
				__func__, __LINE__);
		पूर्ण
		अवरोध;
	हाल PS3_DEV_TYPE_SB_USB:

		/* Each USB device has both an EHCI and an OHCI HC */

		result = ps3_setup_ehci_device(repo);

		अगर (result) अणु
			pr_debug("%s:%d ps3_setup_ehci_device failed\n",
				__func__, __LINE__);
		पूर्ण

		result = ps3_setup_ohci_device(repo);

		अगर (result) अणु
			pr_debug("%s:%d ps3_setup_ohci_device failed\n",
				__func__, __LINE__);
		पूर्ण
		अवरोध;

	शेष:
		वापस ps3_setup_dynamic_device(repo);
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम ps3_find_and_add_device(u64 bus_id, u64 dev_id)
अणु
	काष्ठा ps3_repository_device repo;
	पूर्णांक res;
	अचिन्हित पूर्णांक retries;
	अचिन्हित दीर्घ rem;

	/*
	 * On some firmware versions (e.g. 1.90), the device may not show up
	 * in the repository immediately
	 */
	क्रम (retries = 0; retries < 10; retries++) अणु
		res = ps3_repository_find_device_by_id(&repo, bus_id, dev_id);
		अगर (!res)
			जाओ found;

		rem = msleep_पूर्णांकerruptible(100);
		अगर (rem)
			अवरोध;
	पूर्ण
	pr_warn("%s:%u: device %llu:%llu not found\n",
		__func__, __LINE__, bus_id, dev_id);
	वापस;

found:
	अगर (retries)
		pr_debug("%s:%u: device %llu:%llu found after %u retries\n",
			 __func__, __LINE__, bus_id, dev_id, retries);

	ps3_setup_dynamic_device(&repo);
	वापस;
पूर्ण

#घोषणा PS3_NOTIFICATION_DEV_ID		अच_दीर्घ_उच्च
#घोषणा PS3_NOTIFICATION_INTERRUPT_ID	0

काष्ठा ps3_notअगरication_device अणु
	काष्ठा ps3_प्रणाली_bus_device sbd;
	spinlock_t lock;
	u64 tag;
	u64 lv1_status;
	काष्ठा rcuरुको रुको;
	bool करोne;
पूर्ण;

क्रमागत ps3_notअगरy_type अणु
	notअगरy_device_पढ़ोy = 0,
	notअगरy_region_probe = 1,
	notअगरy_region_update = 2,
पूर्ण;

काष्ठा ps3_notअगरy_cmd अणु
	u64 operation_code;		/* must be zero */
	u64 event_mask;			/* OR of 1UL << क्रमागत ps3_notअगरy_type */
पूर्ण;

काष्ठा ps3_notअगरy_event अणु
	u64 event_type;			/* क्रमागत ps3_notअगरy_type */
	u64 bus_id;
	u64 dev_id;
	u64 dev_type;
	u64 dev_port;
पूर्ण;

अटल irqवापस_t ps3_notअगरication_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ps3_notअगरication_device *dev = data;
	पूर्णांक res;
	u64 tag, status;

	spin_lock(&dev->lock);
	res = lv1_storage_get_async_status(PS3_NOTIFICATION_DEV_ID, &tag,
					   &status);
	अगर (tag != dev->tag)
		pr_err("%s:%u: tag mismatch, got %llx, expected %llx\n",
		       __func__, __LINE__, tag, dev->tag);

	अगर (res) अणु
		pr_err("%s:%u: res %d status 0x%llx\n", __func__, __LINE__, res,
		       status);
	पूर्ण अन्यथा अणु
		pr_debug("%s:%u: completed, status 0x%llx\n", __func__,
			 __LINE__, status);
		dev->lv1_status = status;
		dev->करोne = true;
		rcuरुको_wake_up(&dev->रुको);
	पूर्ण
	spin_unlock(&dev->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ps3_notअगरication_पढ़ो_ग_लिखो(काष्ठा ps3_notअगरication_device *dev,
				       u64 lpar, पूर्णांक ग_लिखो)
अणु
	स्थिर अक्षर *op = ग_लिखो ? "write" : "read";
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	spin_lock_irqsave(&dev->lock, flags);
	res = ग_लिखो ? lv1_storage_ग_लिखो(dev->sbd.dev_id, 0, 0, 1, 0, lpar,
					&dev->tag)
		    : lv1_storage_पढ़ो(dev->sbd.dev_id, 0, 0, 1, 0, lpar,
				       &dev->tag);
	dev->करोne = false;
	spin_unlock_irqrestore(&dev->lock, flags);
	अगर (res) अणु
		pr_err("%s:%u: %s failed %d\n", __func__, __LINE__, op, res);
		वापस -EPERM;
	पूर्ण
	pr_debug("%s:%u: notification %s issued\n", __func__, __LINE__, op);

	rcuरुको_रुको_event(&dev->रुको, dev->करोne || kthपढ़ो_should_stop(), TASK_IDLE);

	अगर (kthपढ़ो_should_stop())
		res = -EINTR;

	अगर (dev->lv1_status) अणु
		pr_err("%s:%u: %s not completed, status 0x%llx\n", __func__,
		       __LINE__, op, dev->lv1_status);
		वापस -EIO;
	पूर्ण
	pr_debug("%s:%u: notification %s completed\n", __func__, __LINE__, op);

	वापस 0;
पूर्ण

अटल काष्ठा task_काष्ठा *probe_task;

/**
 * ps3_probe_thपढ़ो - Background repository probing at प्रणाली startup.
 *
 * This implementation only supports background probing on a single bus.
 * It uses the hypervisor's storage device notअगरication mechanism to रुको until
 * a storage device is पढ़ोy.  The device notअगरication mechanism uses a
 * pseuकरो device to asynchronously notअगरy the guest when storage devices become
 * पढ़ोy.  The notअगरication device has a block size of 512 bytes.
 */

अटल पूर्णांक ps3_probe_thपढ़ो(व्योम *data)
अणु
	काष्ठा ps3_notअगरication_device dev;
	पूर्णांक res;
	अचिन्हित पूर्णांक irq;
	u64 lpar;
	व्योम *buf;
	काष्ठा ps3_notअगरy_cmd *notअगरy_cmd;
	काष्ठा ps3_notअगरy_event *notअगरy_event;

	pr_debug(" -> %s:%u: kthread started\n", __func__, __LINE__);

	buf = kzalloc(512, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	lpar = ps3_mm_phys_to_lpar(__pa(buf));
	notअगरy_cmd = buf;
	notअगरy_event = buf;

	/* dummy प्रणाली bus device */
	dev.sbd.bus_id = (u64)data;
	dev.sbd.dev_id = PS3_NOTIFICATION_DEV_ID;
	dev.sbd.पूर्णांकerrupt_id = PS3_NOTIFICATION_INTERRUPT_ID;

	res = lv1_खोलो_device(dev.sbd.bus_id, dev.sbd.dev_id, 0);
	अगर (res) अणु
		pr_err("%s:%u: lv1_open_device failed %s\n", __func__,
		       __LINE__, ps3_result(res));
		जाओ fail_मुक्त;
	पूर्ण

	res = ps3_sb_event_receive_port_setup(&dev.sbd, PS3_BINDING_CPU_ANY,
					      &irq);
	अगर (res) अणु
		pr_err("%s:%u: ps3_sb_event_receive_port_setup failed %d\n",
		       __func__, __LINE__, res);
	       जाओ fail_बंद_device;
	पूर्ण

	spin_lock_init(&dev.lock);
	rcuरुको_init(&dev.रुको);

	res = request_irq(irq, ps3_notअगरication_पूर्णांकerrupt, 0,
			  "ps3_notification", &dev);
	अगर (res) अणु
		pr_err("%s:%u: request_irq failed %d\n", __func__, __LINE__,
		       res);
		जाओ fail_sb_event_receive_port_destroy;
	पूर्ण

	/* Setup and ग_लिखो the request क्रम device notअगरication. */
	notअगरy_cmd->operation_code = 0; /* must be zero */
	notअगरy_cmd->event_mask = 1UL << notअगरy_region_probe;

	res = ps3_notअगरication_पढ़ो_ग_लिखो(&dev, lpar, 1);
	अगर (res)
		जाओ fail_मुक्त_irq;

	/* Loop here processing the requested notअगरication events. */
	करो अणु
		try_to_मुक्तze();

		स_रखो(notअगरy_event, 0, माप(*notअगरy_event));

		res = ps3_notअगरication_पढ़ो_ग_लिखो(&dev, lpar, 0);
		अगर (res)
			अवरोध;

		pr_debug("%s:%u: notify event type 0x%llx bus id %llu dev id %llu"
			 " type %llu port %llu\n", __func__, __LINE__,
			 notअगरy_event->event_type, notअगरy_event->bus_id,
			 notअगरy_event->dev_id, notअगरy_event->dev_type,
			 notअगरy_event->dev_port);

		अगर (notअगरy_event->event_type != notअगरy_region_probe ||
		    notअगरy_event->bus_id != dev.sbd.bus_id) अणु
			pr_warn("%s:%u: bad notify_event: event %llu, dev_id %llu, dev_type %llu\n",
				__func__, __LINE__, notअगरy_event->event_type,
				notअगरy_event->dev_id, notअगरy_event->dev_type);
			जारी;
		पूर्ण

		ps3_find_and_add_device(dev.sbd.bus_id, notअगरy_event->dev_id);

	पूर्ण जबतक (!kthपढ़ो_should_stop());

fail_मुक्त_irq:
	मुक्त_irq(irq, &dev);
fail_sb_event_receive_port_destroy:
	ps3_sb_event_receive_port_destroy(&dev.sbd, irq);
fail_बंद_device:
	lv1_बंद_device(dev.sbd.bus_id, dev.sbd.dev_id);
fail_मुक्त:
	kमुक्त(buf);

	probe_task = शून्य;

	pr_debug(" <- %s:%u: kthread finished\n", __func__, __LINE__);

	वापस 0;
पूर्ण

/**
 * ps3_stop_probe_thपढ़ो - Stops the background probe thपढ़ो.
 *
 */

अटल पूर्णांक ps3_stop_probe_thपढ़ो(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ code,
				 व्योम *data)
अणु
	अगर (probe_task)
		kthपढ़ो_stop(probe_task);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block nb = अणु
	.notअगरier_call = ps3_stop_probe_thपढ़ो
पूर्ण;

/**
 * ps3_start_probe_thपढ़ो - Starts the background probe thपढ़ो.
 *
 */

अटल पूर्णांक __init ps3_start_probe_thपढ़ो(क्रमागत ps3_bus_type bus_type)
अणु
	पूर्णांक result;
	काष्ठा task_काष्ठा *task;
	काष्ठा ps3_repository_device repo;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	स_रखो(&repo, 0, माप(repo));

	repo.bus_type = bus_type;

	result = ps3_repository_find_bus(repo.bus_type, 0, &repo.bus_index);

	अगर (result) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot find bus (%d)\n", __func__, result);
		वापस -ENODEV;
	पूर्ण

	result = ps3_repository_पढ़ो_bus_id(repo.bus_index, &repo.bus_id);

	अगर (result) अणु
		prपूर्णांकk(KERN_ERR "%s: read_bus_id failed %d\n", __func__,
			result);
		वापस -ENODEV;
	पूर्ण

	task = kthपढ़ो_run(ps3_probe_thपढ़ो, (व्योम *)repo.bus_id,
			   "ps3-probe-%u", bus_type);

	अगर (IS_ERR(task)) अणु
		result = PTR_ERR(task);
		prपूर्णांकk(KERN_ERR "%s: kthread_run failed %d\n", __func__,
		       result);
		वापस result;
	पूर्ण

	probe_task = task;
	रेजिस्टर_reboot_notअगरier(&nb);

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस 0;
पूर्ण

/**
 * ps3_रेजिस्टर_devices - Probe the प्रणाली and रेजिस्टर devices found.
 *
 * A device_initcall() routine.
 */

अटल पूर्णांक __init ps3_रेजिस्टर_devices(व्योम)
अणु
	पूर्णांक result;

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	/* ps3_repository_dump_bus_info(); */

	result = ps3_start_probe_thपढ़ो(PS3_BUS_TYPE_STORAGE);

	ps3_रेजिस्टर_vuart_devices();

	ps3_रेजिस्टर_graphics_devices();

	ps3_repository_find_devices(PS3_BUS_TYPE_SB, ps3_setup_अटल_device);

	ps3_रेजिस्टर_sound_devices();

	ps3_रेजिस्टर_lpm_devices();

	ps3_रेजिस्टर_ramdisk_device();

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस 0;
पूर्ण

device_initcall(ps3_रेजिस्टर_devices);
