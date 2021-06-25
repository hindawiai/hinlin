<शैली गुरु>
/*
 *	TURBOchannel bus services.
 *
 *	Copyright (c) Harald Koerfgen, 1998
 *	Copyright (c) 2001, 2003, 2005, 2006, 2018  Maciej W. Rozycki
 *	Copyright (c) 2005  James Simmons
 *
 *	This file is subject to the terms and conditions of the GNU
 *	General Public License.  See the file "COPYING" in the मुख्य
 *	directory of this archive क्रम more details.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/tc.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>

अटल काष्ठा tc_bus tc_bus = अणु
	.name = "TURBOchannel",
पूर्ण;

/*
 * Probing क्रम TURBOchannel modules.
 */
अटल व्योम __init tc_bus_add_devices(काष्ठा tc_bus *tbus)
अणु
	resource_माप_प्रकार slotsize = tbus->info.slot_size << 20;
	resource_माप_प्रकार extslotsize = tbus->ext_slot_size;
	resource_माप_प्रकार slotaddr;
	resource_माप_प्रकार extslotaddr;
	resource_माप_प्रकार devsize;
	व्योम __iomem *module;
	काष्ठा tc_dev *tdev;
	पूर्णांक i, slot, err;
	u8 pattern[4];
	दीर्घ offset;

	क्रम (slot = 0; slot < tbus->num_tcslots; slot++) अणु
		slotaddr = tbus->slot_base + slot * slotsize;
		extslotaddr = tbus->ext_slot_base + slot * extslotsize;
		module = ioremap(slotaddr, slotsize);
		BUG_ON(!module);

		offset = TC_OLDCARD;

		err = 0;
		err |= tc_pपढ़ोb(pattern + 0, module + offset + TC_PATTERN0);
		err |= tc_pपढ़ोb(pattern + 1, module + offset + TC_PATTERN1);
		err |= tc_pपढ़ोb(pattern + 2, module + offset + TC_PATTERN2);
		err |= tc_pपढ़ोb(pattern + 3, module + offset + TC_PATTERN3);
		अगर (err)
			जाओ out_err;

		अगर (pattern[0] != 0x55 || pattern[1] != 0x00 ||
		    pattern[2] != 0xaa || pattern[3] != 0xff) अणु
			offset = TC_NEWCARD;

			err = 0;
			err |= tc_pपढ़ोb(pattern + 0,
					 module + offset + TC_PATTERN0);
			err |= tc_pपढ़ोb(pattern + 1,
					 module + offset + TC_PATTERN1);
			err |= tc_pपढ़ोb(pattern + 2,
					 module + offset + TC_PATTERN2);
			err |= tc_pपढ़ोb(pattern + 3,
					 module + offset + TC_PATTERN3);
			अगर (err)
				जाओ out_err;
		पूर्ण

		अगर (pattern[0] != 0x55 || pattern[1] != 0x00 ||
		    pattern[2] != 0xaa || pattern[3] != 0xff)
			जाओ out_err;

		/* Found a board, allocate it an entry in the list */
		tdev = kzalloc(माप(*tdev), GFP_KERNEL);
		अगर (!tdev) अणु
			pr_err("tc%x: unable to allocate tc_dev\n", slot);
			जाओ out_err;
		पूर्ण
		dev_set_name(&tdev->dev, "tc%x", slot);
		tdev->bus = tbus;
		tdev->dev.parent = &tbus->dev;
		tdev->dev.bus = &tc_bus_type;
		tdev->slot = slot;

		/* TURBOchannel has 34-bit DMA addressing (16GiB space). */
		tdev->dma_mask = DMA_BIT_MASK(34);
		tdev->dev.dma_mask = &tdev->dma_mask;
		tdev->dev.coherent_dma_mask = DMA_BIT_MASK(34);

		क्रम (i = 0; i < 8; i++) अणु
			tdev->firmware[i] =
				पढ़ोb(module + offset + TC_FIRM_VER + 4 * i);
			tdev->venकरोr[i] =
				पढ़ोb(module + offset + TC_VENDOR + 4 * i);
			tdev->name[i] =
				पढ़ोb(module + offset + TC_MODULE + 4 * i);
		पूर्ण
		tdev->firmware[8] = 0;
		tdev->venकरोr[8] = 0;
		tdev->name[8] = 0;

		pr_info("%s: %s %s %s\n", dev_name(&tdev->dev), tdev->venकरोr,
			tdev->name, tdev->firmware);

		devsize = पढ़ोb(module + offset + TC_SLOT_SIZE);
		devsize <<= 22;
		अगर (devsize <= slotsize) अणु
			tdev->resource.start = slotaddr;
			tdev->resource.end = slotaddr + devsize - 1;
		पूर्ण अन्यथा अगर (devsize <= extslotsize) अणु
			tdev->resource.start = extslotaddr;
			tdev->resource.end = extslotaddr + devsize - 1;
		पूर्ण अन्यथा अणु
			pr_err("%s: Cannot provide slot space "
			       "(%ldMiB required, up to %ldMiB supported)\n",
			       dev_name(&tdev->dev), (दीर्घ)(devsize >> 20),
			       (दीर्घ)(max(slotsize, extslotsize) >> 20));
			kमुक्त(tdev);
			जाओ out_err;
		पूर्ण
		tdev->resource.name = tdev->name;
		tdev->resource.flags = IORESOURCE_MEM;

		tc_device_get_irq(tdev);

		अगर (device_रेजिस्टर(&tdev->dev)) अणु
			put_device(&tdev->dev);
			जाओ out_err;
		पूर्ण
		list_add_tail(&tdev->node, &tbus->devices);

out_err:
		iounmap(module);
	पूर्ण
पूर्ण

/*
 * The मुख्य entry.
 */
अटल पूर्णांक __init tc_init(व्योम)
अणु
	/* Initialize the TURBOchannel bus */
	अगर (tc_bus_get_info(&tc_bus))
		जाओ out_err;

	INIT_LIST_HEAD(&tc_bus.devices);
	dev_set_name(&tc_bus.dev, "tc");
	अगर (device_रेजिस्टर(&tc_bus.dev))
		जाओ out_err_device;

	अगर (tc_bus.info.slot_size) अणु
		अचिन्हित पूर्णांक tc_घड़ी = tc_get_speed(&tc_bus) / 100000;

		pr_info("tc: TURBOchannel rev. %d at %d.%d MHz "
			"(with%s parity)\n", tc_bus.info.revision,
			tc_घड़ी / 10, tc_घड़ी % 10,
			tc_bus.info.parity ? "" : "out");

		tc_bus.resource[0].start = tc_bus.slot_base;
		tc_bus.resource[0].end = tc_bus.slot_base +
					 (tc_bus.info.slot_size << 20) *
					 tc_bus.num_tcslots - 1;
		tc_bus.resource[0].name = tc_bus.name;
		tc_bus.resource[0].flags = IORESOURCE_MEM;
		अगर (request_resource(&iomem_resource,
				     &tc_bus.resource[0]) < 0) अणु
			pr_err("tc: Cannot reserve resource\n");
			जाओ out_err_device;
		पूर्ण
		अगर (tc_bus.ext_slot_size) अणु
			tc_bus.resource[1].start = tc_bus.ext_slot_base;
			tc_bus.resource[1].end = tc_bus.ext_slot_base +
						 tc_bus.ext_slot_size *
						 tc_bus.num_tcslots - 1;
			tc_bus.resource[1].name = tc_bus.name;
			tc_bus.resource[1].flags = IORESOURCE_MEM;
			अगर (request_resource(&iomem_resource,
					     &tc_bus.resource[1]) < 0) अणु
				pr_err("tc: Cannot reserve resource\n");
				जाओ out_err_resource;
			पूर्ण
		पूर्ण

		tc_bus_add_devices(&tc_bus);
	पूर्ण

	वापस 0;

out_err_resource:
	release_resource(&tc_bus.resource[0]);
out_err_device:
	put_device(&tc_bus.dev);
out_err:
	वापस 0;
पूर्ण

subsys_initcall(tc_init);
