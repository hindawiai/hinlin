<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PS3 Storage Library
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2007 Sony Corp.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3stor.h>

/*
 * A workaround क्रम flash memory I/O errors when the पूर्णांकernal hard disk
 * has not been क्रमmatted क्रम OtherOS use.  Delay disk बंद until flash
 * memory is बंदd.
 */

अटल काष्ठा ps3_flash_workaround अणु
	पूर्णांक flash_खोलो;
	पूर्णांक disk_खोलो;
	काष्ठा ps3_प्रणाली_bus_device *disk_sbd;
पूर्ण ps3_flash_workaround;

अटल पूर्णांक ps3stor_खोलो_hv_device(काष्ठा ps3_प्रणाली_bus_device *sbd)
अणु
	पूर्णांक error = ps3_खोलो_hv_device(sbd);

	अगर (error)
		वापस error;

	अगर (sbd->match_id == PS3_MATCH_ID_STOR_FLASH)
		ps3_flash_workaround.flash_खोलो = 1;

	अगर (sbd->match_id == PS3_MATCH_ID_STOR_DISK)
		ps3_flash_workaround.disk_खोलो = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ps3stor_बंद_hv_device(काष्ठा ps3_प्रणाली_bus_device *sbd)
अणु
	पूर्णांक error;

	अगर (sbd->match_id == PS3_MATCH_ID_STOR_DISK
		&& ps3_flash_workaround.disk_खोलो
		&& ps3_flash_workaround.flash_खोलो) अणु
		ps3_flash_workaround.disk_sbd = sbd;
		वापस 0;
	पूर्ण

	error = ps3_बंद_hv_device(sbd);

	अगर (error)
		वापस error;

	अगर (sbd->match_id == PS3_MATCH_ID_STOR_DISK)
		ps3_flash_workaround.disk_खोलो = 0;

	अगर (sbd->match_id == PS3_MATCH_ID_STOR_FLASH) अणु
		ps3_flash_workaround.flash_खोलो = 0;

		अगर (ps3_flash_workaround.disk_sbd) अणु
			ps3_बंद_hv_device(ps3_flash_workaround.disk_sbd);
			ps3_flash_workaround.disk_खोलो = 0;
			ps3_flash_workaround.disk_sbd = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ps3stor_probe_access(काष्ठा ps3_storage_device *dev)
अणु
	पूर्णांक res, error;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ n;

	अगर (dev->sbd.match_id == PS3_MATCH_ID_STOR_ROM) अणु
		/* special हाल: CD-ROM is assumed always accessible */
		dev->accessible_regions = 1;
		वापस 0;
	पूर्ण

	error = -EPERM;
	क्रम (i = 0; i < dev->num_regions; i++) अणु
		dev_dbg(&dev->sbd.core,
			"%s:%u: checking accessibility of region %u\n",
			__func__, __LINE__, i);

		dev->region_idx = i;
		res = ps3stor_पढ़ो_ग_लिखो_sectors(dev, dev->bounce_lpar, 0, 1,
						 0);
		अगर (res) अणु
			dev_dbg(&dev->sbd.core, "%s:%u: read failed, "
				"region %u is not accessible\n", __func__,
				__LINE__, i);
			जारी;
		पूर्ण

		dev_dbg(&dev->sbd.core, "%s:%u: region %u is accessible\n",
			__func__, __LINE__, i);
		set_bit(i, &dev->accessible_regions);

		/* We can access at least one region */
		error = 0;
	पूर्ण
	अगर (error)
		वापस error;

	n = hweight_दीर्घ(dev->accessible_regions);
	अगर (n > 1)
		dev_info(&dev->sbd.core,
			 "%s:%u: %lu accessible regions found. Only the first "
			 "one will be used\n",
			 __func__, __LINE__, n);
	dev->region_idx = __ffs(dev->accessible_regions);
	dev_info(&dev->sbd.core,
		 "First accessible region has index %u start %llu size %llu\n",
		 dev->region_idx, dev->regions[dev->region_idx].start,
		 dev->regions[dev->region_idx].size);

	वापस 0;
पूर्ण


/**
 *	ps3stor_setup - Setup a storage device beक्रमe use
 *	@dev: Poपूर्णांकer to a काष्ठा ps3_storage_device
 *	@handler: Poपूर्णांकer to an पूर्णांकerrupt handler
 *
 *	Returns 0 क्रम success, or an error code
 */
पूर्णांक ps3stor_setup(काष्ठा ps3_storage_device *dev, irq_handler_t handler)
अणु
	पूर्णांक error, res, alignment;
	क्रमागत ps3_dma_page_size page_size;

	error = ps3stor_खोलो_hv_device(&dev->sbd);
	अगर (error) अणु
		dev_err(&dev->sbd.core,
			"%s:%u: ps3_open_hv_device failed %d\n", __func__,
			__LINE__, error);
		जाओ fail;
	पूर्ण

	error = ps3_sb_event_receive_port_setup(&dev->sbd, PS3_BINDING_CPU_ANY,
						&dev->irq);
	अगर (error) अणु
		dev_err(&dev->sbd.core,
			"%s:%u: ps3_sb_event_receive_port_setup failed %d\n",
		       __func__, __LINE__, error);
		जाओ fail_बंद_device;
	पूर्ण

	error = request_irq(dev->irq, handler, 0,
			    dev->sbd.core.driver->name, dev);
	अगर (error) अणु
		dev_err(&dev->sbd.core, "%s:%u: request_irq failed %d\n",
			__func__, __LINE__, error);
		जाओ fail_sb_event_receive_port_destroy;
	पूर्ण

	alignment = min(__ffs(dev->bounce_size),
			__ffs((अचिन्हित दीर्घ)dev->bounce_buf));
	अगर (alignment < 12) अणु
		dev_err(&dev->sbd.core,
			"%s:%u: bounce buffer not aligned (%lx at 0x%p)\n",
			__func__, __LINE__, dev->bounce_size, dev->bounce_buf);
		error = -EINVAL;
		जाओ fail_मुक्त_irq;
	पूर्ण अन्यथा अगर (alignment < 16)
		page_size = PS3_DMA_4K;
	अन्यथा
		page_size = PS3_DMA_64K;
	dev->sbd.d_region = &dev->dma_region;
	ps3_dma_region_init(&dev->sbd, &dev->dma_region, page_size,
			    PS3_DMA_OTHER, dev->bounce_buf, dev->bounce_size);
	res = ps3_dma_region_create(&dev->dma_region);
	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: cannot create DMA region\n",
			__func__, __LINE__);
		error = -ENOMEM;
		जाओ fail_मुक्त_irq;
	पूर्ण

	dev->bounce_lpar = ps3_mm_phys_to_lpar(__pa(dev->bounce_buf));
	dev->bounce_dma = dma_map_single(&dev->sbd.core, dev->bounce_buf,
					 dev->bounce_size, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&dev->sbd.core, dev->bounce_dma)) अणु
		dev_err(&dev->sbd.core, "%s:%u: map DMA region failed\n",
			__func__, __LINE__);
		error = -ENODEV;
		जाओ fail_मुक्त_dma;
	पूर्ण

	error = ps3stor_probe_access(dev);
	अगर (error) अणु
		dev_err(&dev->sbd.core, "%s:%u: No accessible regions found\n",
			__func__, __LINE__);
		जाओ fail_unmap_dma;
	पूर्ण
	वापस 0;

fail_unmap_dma:
	dma_unmap_single(&dev->sbd.core, dev->bounce_dma, dev->bounce_size,
			 DMA_BIसूचीECTIONAL);
fail_मुक्त_dma:
	ps3_dma_region_मुक्त(&dev->dma_region);
fail_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
fail_sb_event_receive_port_destroy:
	ps3_sb_event_receive_port_destroy(&dev->sbd, dev->irq);
fail_बंद_device:
	ps3stor_बंद_hv_device(&dev->sbd);
fail:
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(ps3stor_setup);


/**
 *	ps3stor_tearकरोwn - Tear करोwn a storage device after use
 *	@dev: Poपूर्णांकer to a काष्ठा ps3_storage_device
 */
व्योम ps3stor_tearकरोwn(काष्ठा ps3_storage_device *dev)
अणु
	पूर्णांक error;

	dma_unmap_single(&dev->sbd.core, dev->bounce_dma, dev->bounce_size,
			 DMA_BIसूचीECTIONAL);
	ps3_dma_region_मुक्त(&dev->dma_region);

	मुक्त_irq(dev->irq, dev);

	error = ps3_sb_event_receive_port_destroy(&dev->sbd, dev->irq);
	अगर (error)
		dev_err(&dev->sbd.core,
			"%s:%u: destroy event receive port failed %d\n",
			__func__, __LINE__, error);

	error = ps3stor_बंद_hv_device(&dev->sbd);
	अगर (error)
		dev_err(&dev->sbd.core,
			"%s:%u: ps3_close_hv_device failed %d\n", __func__,
			__LINE__, error);
पूर्ण
EXPORT_SYMBOL_GPL(ps3stor_tearकरोwn);


/**
 *	ps3stor_पढ़ो_ग_लिखो_sectors - पढ़ो/ग_लिखो from/to a storage device
 *	@dev: Poपूर्णांकer to a काष्ठा ps3_storage_device
 *	@lpar: HV logical partition address
 *	@start_sector: First sector to पढ़ो/ग_लिखो
 *	@sectors: Number of sectors to पढ़ो/ग_लिखो
 *	@ग_लिखो: Flag indicating ग_लिखो (non-zero) or पढ़ो (zero)
 *
 *	Returns 0 क्रम success, -1 in हाल of failure to submit the command, or
 *	an LV1 status value in हाल of other errors
 */
u64 ps3stor_पढ़ो_ग_लिखो_sectors(काष्ठा ps3_storage_device *dev, u64 lpar,
			       u64 start_sector, u64 sectors, पूर्णांक ग_लिखो)
अणु
	अचिन्हित पूर्णांक region_id = dev->regions[dev->region_idx].id;
	स्थिर अक्षर *op = ग_लिखो ? "write" : "read";
	पूर्णांक res;

	dev_dbg(&dev->sbd.core, "%s:%u: %s %llu sectors starting at %llu\n",
		__func__, __LINE__, op, sectors, start_sector);

	init_completion(&dev->करोne);
	res = ग_लिखो ? lv1_storage_ग_लिखो(dev->sbd.dev_id, region_id,
					start_sector, sectors, 0, lpar,
					&dev->tag)
		    : lv1_storage_पढ़ो(dev->sbd.dev_id, region_id,
				       start_sector, sectors, 0, lpar,
				       &dev->tag);
	अगर (res) अणु
		dev_dbg(&dev->sbd.core, "%s:%u: %s failed %d\n", __func__,
			__LINE__, op, res);
		वापस -1;
	पूर्ण

	रुको_क्रम_completion(&dev->करोne);
	अगर (dev->lv1_status) अणु
		dev_dbg(&dev->sbd.core, "%s:%u: %s failed 0x%llx\n", __func__,
			__LINE__, op, dev->lv1_status);
		वापस dev->lv1_status;
	पूर्ण

	dev_dbg(&dev->sbd.core, "%s:%u: %s completed\n", __func__, __LINE__,
		op);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3stor_पढ़ो_ग_लिखो_sectors);


/**
 *	ps3stor_send_command - send a device command to a storage device
 *	@dev: Poपूर्णांकer to a काष्ठा ps3_storage_device
 *	@cmd: Command number
 *	@arg1: First command argument
 *	@arg2: Second command argument
 *	@arg3: Third command argument
 *	@arg4: Fourth command argument
 *
 *	Returns 0 क्रम success, -1 in हाल of failure to submit the command, or
 *	an LV1 status value in हाल of other errors
 */
u64 ps3stor_send_command(काष्ठा ps3_storage_device *dev, u64 cmd, u64 arg1,
			 u64 arg2, u64 arg3, u64 arg4)
अणु
	पूर्णांक res;

	dev_dbg(&dev->sbd.core, "%s:%u: send device command 0x%llx\n", __func__,
		__LINE__, cmd);

	init_completion(&dev->करोne);

	res = lv1_storage_send_device_command(dev->sbd.dev_id, cmd, arg1,
					      arg2, arg3, arg4, &dev->tag);
	अगर (res) अणु
		dev_err(&dev->sbd.core,
			"%s:%u: send_device_command 0x%llx failed %d\n",
			__func__, __LINE__, cmd, res);
		वापस -1;
	पूर्ण

	रुको_क्रम_completion(&dev->करोne);
	अगर (dev->lv1_status) अणु
		dev_dbg(&dev->sbd.core, "%s:%u: command 0x%llx failed 0x%llx\n",
			__func__, __LINE__, cmd, dev->lv1_status);
		वापस dev->lv1_status;
	पूर्ण

	dev_dbg(&dev->sbd.core, "%s:%u: command 0x%llx completed\n", __func__,
		__LINE__, cmd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3stor_send_command);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS3 Storage Bus Library");
MODULE_AUTHOR("Sony Corporation");
