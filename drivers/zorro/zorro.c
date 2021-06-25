<शैली गुरु>
/*
 *    Zorro Bus Services
 *
 *    Copyright (C) 1995-2003 Geert Uytterhoeven
 *
 *    This file is subject to the terms and conditions of the GNU General Public
 *    License.  See the file COPYING in the मुख्य directory of this archive
 *    क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/zorro.h>
#समावेश <linux/bitops.h>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/amigahw.h>

#समावेश "zorro.h"


    /*
     *  Zorro Expansion Devices
     */

अचिन्हित पूर्णांक zorro_num_स्वतःcon;
काष्ठा zorro_dev_init zorro_स्वतःcon_init[ZORRO_NUM_AUTO] __initdata;
काष्ठा zorro_dev *zorro_स्वतःcon;


    /*
     *  Zorro bus
     */

काष्ठा zorro_bus अणु
	काष्ठा device dev;
	काष्ठा zorro_dev devices[];
पूर्ण;


    /*
     *  Find Zorro Devices
     */

काष्ठा zorro_dev *zorro_find_device(zorro_id id, काष्ठा zorro_dev *from)
अणु
	काष्ठा zorro_dev *z;

	अगर (!zorro_num_स्वतःcon)
		वापस शून्य;

	क्रम (z = from ? from+1 : &zorro_स्वतःcon[0];
	     z < zorro_स्वतःcon+zorro_num_स्वतःcon;
	     z++)
		अगर (id == ZORRO_WILDCARD || id == z->id)
			वापस z;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(zorro_find_device);


    /*
     *  Biपंचांगask indicating portions of available Zorro II RAM that are unused
     *  by the प्रणाली. Every bit represents a 64K chunk, क्रम a maximum of 8MB
     *  (128 chunks, physical 0x00200000-0x009fffff).
     *
     *  If you want to use (= allocate) portions of this RAM, you should clear
     *  the corresponding bits.
     *
     *  Possible uses:
     *      - z2ram device
     *      - SCSI DMA bounce buffers
     *
     *  FIXME: use the normal resource management
     */

DECLARE_BITMAP(zorro_unused_z2ram, 128);
EXPORT_SYMBOL(zorro_unused_z2ram);


अटल व्योम __init mark_region(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			       पूर्णांक flag)
अणु
	अगर (flag)
		start += Z2RAM_CHUNKMASK;
	अन्यथा
		end += Z2RAM_CHUNKMASK;
	start &= ~Z2RAM_CHUNKMASK;
	end &= ~Z2RAM_CHUNKMASK;

	अगर (end <= Z2RAM_START || start >= Z2RAM_END)
		वापस;
	start = start < Z2RAM_START ? 0x00000000 : start-Z2RAM_START;
	end = end > Z2RAM_END ? Z2RAM_SIZE : end-Z2RAM_START;
	जबतक (start < end) अणु
		u32 chunk = start>>Z2RAM_CHUNKSHIFT;

		अगर (flag)
			set_bit(chunk, zorro_unused_z2ram);
		अन्यथा
			clear_bit(chunk, zorro_unused_z2ram);
		start += Z2RAM_CHUNKSIZE;
	पूर्ण
पूर्ण


अटल काष्ठा resource __init *zorro_find_parent_resource(
	काष्ठा platक्रमm_device *bridge, काष्ठा zorro_dev *z)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bridge->num_resources; i++) अणु
		काष्ठा resource *r = &bridge->resource[i];

		अगर (zorro_resource_start(z) >= r->start &&
		    zorro_resource_end(z) <= r->end)
			वापस r;
	पूर्ण
	वापस &iomem_resource;
पूर्ण



अटल पूर्णांक __init amiga_zorro_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zorro_bus *bus;
	काष्ठा zorro_dev_init *zi;
	काष्ठा zorro_dev *z;
	काष्ठा resource *r;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;

	/* Initialize the Zorro bus */
	bus = kzalloc(काष्ठा_size(bus, devices, zorro_num_स्वतःcon),
		      GFP_KERNEL);
	अगर (!bus)
		वापस -ENOMEM;

	zorro_स्वतःcon = bus->devices;
	bus->dev.parent = &pdev->dev;
	dev_set_name(&bus->dev, zorro_bus_type.name);
	error = device_रेजिस्टर(&bus->dev);
	अगर (error) अणु
		pr_err("Zorro: Error registering zorro_bus\n");
		put_device(&bus->dev);
		kमुक्त(bus);
		वापस error;
	पूर्ण
	platक्रमm_set_drvdata(pdev, bus);

	pr_info("Zorro: Probing AutoConfig expansion devices: %u device%s\n",
		 zorro_num_स्वतःcon, zorro_num_स्वतःcon == 1 ? "" : "s");

	/* First identअगरy all devices ... */
	क्रम (i = 0; i < zorro_num_स्वतःcon; i++) अणु
		zi = &zorro_स्वतःcon_init[i];
		z = &zorro_स्वतःcon[i];

		z->rom = zi->rom;
		z->id = (be16_to_cpu(z->rom.er_Manufacturer) << 16) |
			(z->rom.er_Product << 8);
		अगर (z->id == ZORRO_PROD_GVP_EPC_BASE) अणु
			/* GVP quirk */
			अचिन्हित दीर्घ magic = zi->boardaddr + 0x8000;

			z->id |= *(u16 *)ZTWO_VADDR(magic) & GVP_PRODMASK;
		पूर्ण
		z->slotaddr = zi->slotaddr;
		z->slotsize = zi->slotsize;
		प्र_लिखो(z->name, "Zorro device %08x", z->id);
		zorro_name_device(z);
		z->resource.start = zi->boardaddr;
		z->resource.end = zi->boardaddr + zi->boardsize - 1;
		z->resource.name = z->name;
		r = zorro_find_parent_resource(pdev, z);
		error = request_resource(r, &z->resource);
		अगर (error && !(z->rom.er_Type & ERTF_MEMLIST))
			dev_err(&bus->dev,
				"Address space collision on device %s %pR\n",
				z->name, &z->resource);
		z->dev.parent = &bus->dev;
		z->dev.bus = &zorro_bus_type;
		z->dev.id = i;
		चयन (z->rom.er_Type & ERT_TYPEMASK) अणु
		हाल ERT_ZORROIII:
			z->dev.coherent_dma_mask = DMA_BIT_MASK(32);
			अवरोध;

		हाल ERT_ZORROII:
		शेष:
			z->dev.coherent_dma_mask = DMA_BIT_MASK(24);
			अवरोध;
		पूर्ण
		z->dev.dma_mask = &z->dev.coherent_dma_mask;
	पूर्ण

	/* ... then रेजिस्टर them */
	क्रम (i = 0; i < zorro_num_स्वतःcon; i++) अणु
		z = &zorro_स्वतःcon[i];
		error = device_रेजिस्टर(&z->dev);
		अगर (error) अणु
			dev_err(&bus->dev, "Error registering device %s\n",
				z->name);
			put_device(&z->dev);
			जारी;
		पूर्ण
	पूर्ण

	/* Mark all available Zorro II memory */
	zorro_क्रम_each_dev(z) अणु
		अगर (z->rom.er_Type & ERTF_MEMLIST)
			mark_region(zorro_resource_start(z),
				    zorro_resource_end(z)+1, 1);
	पूर्ण

	/* Unmark all used Zorro II memory */
	क्रम (i = 0; i < m68k_num_memory; i++)
		अगर (m68k_memory[i].addr < 16*1024*1024)
			mark_region(m68k_memory[i].addr,
				    m68k_memory[i].addr+m68k_memory[i].size,
				    0);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amiga_zorro_driver = अणु
	.driver   = अणु
		.name	= "amiga-zorro",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init amiga_zorro_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&amiga_zorro_driver, amiga_zorro_probe);
पूर्ण

module_init(amiga_zorro_init);

MODULE_LICENSE("GPL");
