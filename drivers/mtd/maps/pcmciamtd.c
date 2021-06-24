<शैली गुरु>
/*
 * pcmciamtd.c - MTD driver क्रम PCMCIA flash memory cards
 *
 * Author: Simon Evans <spse@secret.org.uk>
 *
 * Copyright (C) 2002 Simon Evans
 *
 * Licence: GPL
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/mtd.h>

#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "pcmciamtd: " क्रमmat "\n" , ## arg)

#घोषणा DRIVER_DESC	"PCMCIA Flash memory card driver"

/* Size of the PCMCIA address space: 26 bits = 64 MB */
#घोषणा MAX_PCMCIA_ADDR	0x4000000

काष्ठा pcmciamtd_dev अणु
	काष्ठा pcmcia_device	*p_dev;
	व्योम __iomem	*win_base;	/* ioremapped address of PCMCIA winकरोw */
	अचिन्हित पूर्णांक	win_size;	/* size of winकरोw */
	अचिन्हित पूर्णांक	offset;		/* offset पूर्णांकo card the winकरोw currently poपूर्णांकs at */
	काष्ठा map_info	pcmcia_map;
	काष्ठा mtd_info	*mtd_info;
	पूर्णांक		vpp;
	अक्षर		mtd_name[माप(काष्ठा cistpl_vers_1_t)];
पूर्ण;


/* Module parameters */

/* 2 = करो 16-bit transfers, 1 = करो 8-bit transfers */
अटल पूर्णांक bankwidth = 2;

/* Speed of memory accesses, in ns */
अटल पूर्णांक mem_speed;

/* Force the size of an SRAM card */
अटल पूर्णांक क्रमce_size;

/* Force Vpp */
अटल पूर्णांक vpp;

/* Set Vpp */
अटल पूर्णांक setvpp;

/* Force card to be treated as FLASH, ROM or RAM */
अटल पूर्णांक mem_type;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Simon Evans <spse@secret.org.uk>");
MODULE_DESCRIPTION(DRIVER_DESC);
module_param(bankwidth, पूर्णांक, 0);
MODULE_PARM_DESC(bankwidth, "Set bankwidth (1=8 bit, 2=16 bit, default=2)");
module_param(mem_speed, पूर्णांक, 0);
MODULE_PARM_DESC(mem_speed, "Set memory access speed in ns");
module_param(क्रमce_size, पूर्णांक, 0);
MODULE_PARM_DESC(क्रमce_size, "Force size of card in MiB (1-64)");
module_param(setvpp, पूर्णांक, 0);
MODULE_PARM_DESC(setvpp, "Set Vpp (0=Never, 1=On writes, 2=Always on, default=0)");
module_param(vpp, पूर्णांक, 0);
MODULE_PARM_DESC(vpp, "Vpp value in 1/10ths eg 33=3.3V 120=12V (Dangerous)");
module_param(mem_type, पूर्णांक, 0);
MODULE_PARM_DESC(mem_type, "Set Memory type (0=Flash, 1=RAM, 2=ROM, default=0)");


/* पढ़ो/ग_लिखोअणु8,16पूर्ण copy_अणुfrom,toपूर्ण routines with winकरोw remapping
 * to access whole card
 */
अटल व्योम __iomem *remap_winकरोw(काष्ठा map_info *map, अचिन्हित दीर्घ to)
अणु
	काष्ठा pcmciamtd_dev *dev = (काष्ठा pcmciamtd_dev *)map->map_priv_1;
	काष्ठा resource *win = (काष्ठा resource *) map->map_priv_2;
	अचिन्हित पूर्णांक offset;
	पूर्णांक ret;

	अगर (!pcmcia_dev_present(dev->p_dev)) अणु
		pr_debug("device removed\n");
		वापस शून्य;
	पूर्ण

	offset = to & ~(dev->win_size-1);
	अगर (offset != dev->offset) अणु
		pr_debug("Remapping window from 0x%8.8x to 0x%8.8x\n",
		      dev->offset, offset);
		ret = pcmcia_map_mem_page(dev->p_dev, win, offset);
		अगर (ret != 0)
			वापस शून्य;
		dev->offset = offset;
	पूर्ण
	वापस dev->win_base + (to & (dev->win_size-1));
पूर्ण


अटल map_word pcmcia_पढ़ो8_remap(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	व्योम __iomem *addr;
	map_word d = अणुअणु0पूर्णपूर्ण;

	addr = remap_winकरोw(map, ofs);
	अगर(!addr)
		वापस d;

	d.x[0] = पढ़ोb(addr);
	pr_debug("ofs = 0x%08lx (%p) data = 0x%02lx\n", ofs, addr, d.x[0]);
	वापस d;
पूर्ण


अटल map_word pcmcia_पढ़ो16_remap(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	व्योम __iomem *addr;
	map_word d = अणुअणु0पूर्णपूर्ण;

	addr = remap_winकरोw(map, ofs);
	अगर(!addr)
		वापस d;

	d.x[0] = पढ़ोw(addr);
	pr_debug("ofs = 0x%08lx (%p) data = 0x%04lx\n", ofs, addr, d.x[0]);
	वापस d;
पूर्ण


अटल व्योम pcmcia_copy_from_remap(काष्ठा map_info *map, व्योम *to, अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	काष्ठा pcmciamtd_dev *dev = (काष्ठा pcmciamtd_dev *)map->map_priv_1;
	अचिन्हित दीर्घ win_size = dev->win_size;

	pr_debug("to = %p from = %lu len = %zd\n", to, from, len);
	जबतक(len) अणु
		पूर्णांक toपढ़ो = win_size - (from & (win_size-1));
		व्योम __iomem *addr;

		अगर(toपढ़ो > len)
			toपढ़ो = len;

		addr = remap_winकरोw(map, from);
		अगर(!addr)
			वापस;

		pr_debug("memcpy from %p to %p len = %d\n", addr, to, toपढ़ो);
		स_नकल_fromio(to, addr, toपढ़ो);
		len -= toपढ़ो;
		to += toपढ़ो;
		from += toपढ़ो;
	पूर्ण
पूर्ण


अटल व्योम pcmcia_ग_लिखो8_remap(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	व्योम __iomem *addr = remap_winकरोw(map, adr);

	अगर(!addr)
		वापस;

	pr_debug("adr = 0x%08lx (%p)  data = 0x%02lx\n", adr, addr, d.x[0]);
	ग_लिखोb(d.x[0], addr);
पूर्ण


अटल व्योम pcmcia_ग_लिखो16_remap(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	व्योम __iomem *addr = remap_winकरोw(map, adr);
	अगर(!addr)
		वापस;

	pr_debug("adr = 0x%08lx (%p)  data = 0x%04lx\n", adr, addr, d.x[0]);
	ग_लिखोw(d.x[0], addr);
पूर्ण


अटल व्योम pcmcia_copy_to_remap(काष्ठा map_info *map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	काष्ठा pcmciamtd_dev *dev = (काष्ठा pcmciamtd_dev *)map->map_priv_1;
	अचिन्हित दीर्घ win_size = dev->win_size;

	pr_debug("to = %lu from = %p len = %zd\n", to, from, len);
	जबतक(len) अणु
		पूर्णांक toग_लिखो = win_size - (to & (win_size-1));
		व्योम __iomem *addr;

		अगर(toग_लिखो > len)
			toग_लिखो = len;

		addr = remap_winकरोw(map, to);
		अगर(!addr)
			वापस;

		pr_debug("memcpy from %p to %p len = %d\n", from, addr, toग_लिखो);
		स_नकल_toio(addr, from, toग_लिखो);
		len -= toग_लिखो;
		to += toग_लिखो;
		from += toग_लिखो;
	पूर्ण
पूर्ण


/* पढ़ो/ग_लिखोअणु8,16पूर्ण copy_अणुfrom,toपूर्ण routines with direct access */

#घोषणा DEV_REMOVED(x)  (!(pcmcia_dev_present(((काष्ठा pcmciamtd_dev *)map->map_priv_1)->p_dev)))

अटल map_word pcmcia_पढ़ो8(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	व्योम __iomem *win_base = (व्योम __iomem *)map->map_priv_2;
	map_word d = अणुअणु0पूर्णपूर्ण;

	अगर(DEV_REMOVED(map))
		वापस d;

	d.x[0] = पढ़ोb(win_base + ofs);
	pr_debug("ofs = 0x%08lx (%p) data = 0x%02lx\n",
	      ofs, win_base + ofs, d.x[0]);
	वापस d;
पूर्ण


अटल map_word pcmcia_पढ़ो16(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	व्योम __iomem *win_base = (व्योम __iomem *)map->map_priv_2;
	map_word d = अणुअणु0पूर्णपूर्ण;

	अगर(DEV_REMOVED(map))
		वापस d;

	d.x[0] = पढ़ोw(win_base + ofs);
	pr_debug("ofs = 0x%08lx (%p) data = 0x%04lx\n",
	      ofs, win_base + ofs, d.x[0]);
	वापस d;
पूर्ण


अटल व्योम pcmcia_copy_from(काष्ठा map_info *map, व्योम *to, अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	व्योम __iomem *win_base = (व्योम __iomem *)map->map_priv_2;

	अगर(DEV_REMOVED(map))
		वापस;

	pr_debug("to = %p from = %lu len = %zd\n", to, from, len);
	स_नकल_fromio(to, win_base + from, len);
पूर्ण


अटल व्योम pcmcia_ग_लिखो8(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	व्योम __iomem *win_base = (व्योम __iomem *)map->map_priv_2;

	अगर(DEV_REMOVED(map))
		वापस;

	pr_debug("adr = 0x%08lx (%p)  data = 0x%02lx\n",
	      adr, win_base + adr, d.x[0]);
	ग_लिखोb(d.x[0], win_base + adr);
पूर्ण


अटल व्योम pcmcia_ग_लिखो16(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	व्योम __iomem *win_base = (व्योम __iomem *)map->map_priv_2;

	अगर(DEV_REMOVED(map))
		वापस;

	pr_debug("adr = 0x%08lx (%p)  data = 0x%04lx\n",
	      adr, win_base + adr, d.x[0]);
	ग_लिखोw(d.x[0], win_base + adr);
पूर्ण


अटल व्योम pcmcia_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	व्योम __iomem *win_base = (व्योम __iomem *)map->map_priv_2;

	अगर(DEV_REMOVED(map))
		वापस;

	pr_debug("to = %lu from = %p len = %zd\n", to, from, len);
	स_नकल_toio(win_base + to, from, len);
पूर्ण


अटल DEFINE_MUTEX(pcmcia_vpp_lock);
अटल पूर्णांक pcmcia_vpp_refcnt;
अटल व्योम pcmciamtd_set_vpp(काष्ठा map_info *map, पूर्णांक on)
अणु
	काष्ठा pcmciamtd_dev *dev = (काष्ठा pcmciamtd_dev *)map->map_priv_1;
	काष्ठा pcmcia_device *link = dev->p_dev;

	pr_debug("dev = %p on = %d vpp = %d\n\n", dev, on, dev->vpp);
	mutex_lock(&pcmcia_vpp_lock);
	अगर (on) अणु
		अगर (++pcmcia_vpp_refcnt == 1)   /* first nested 'on' */
			pcmcia_fixup_vpp(link, dev->vpp);
	पूर्ण अन्यथा अणु
		अगर (--pcmcia_vpp_refcnt == 0)   /* last nested 'off' */
			pcmcia_fixup_vpp(link, 0);
	पूर्ण
	mutex_unlock(&pcmcia_vpp_lock);
पूर्ण


अटल व्योम pcmciamtd_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा pcmciamtd_dev *dev = link->priv;

	pr_debug("link = 0x%p\n", link);

	अगर (link->resource[2]->end) अणु
		अगर(dev->win_base) अणु
			iounmap(dev->win_base);
			dev->win_base = शून्य;
		पूर्ण
	पूर्ण
	pcmcia_disable_device(link);
पूर्ण


अटल पूर्णांक pcmciamtd_cistpl_क्रमmat(काष्ठा pcmcia_device *p_dev,
				tuple_t *tuple,
				व्योम *priv_data)
अणु
	cisparse_t parse;

	अगर (!pcmcia_parse_tuple(tuple, &parse)) अणु
		cistpl_क्रमmat_t *t = &parse.क्रमmat;
		(व्योम)t; /* Shut up, gcc */
		pr_debug("Format type: %u, Error Detection: %u, offset = %u, length =%u\n",
			t->type, t->edc, t->offset, t->length);
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक pcmciamtd_cistpl_jedec(काष्ठा pcmcia_device *p_dev,
				tuple_t *tuple,
				व्योम *priv_data)
अणु
	cisparse_t parse;
	पूर्णांक i;

	अगर (!pcmcia_parse_tuple(tuple, &parse)) अणु
		cistpl_jedec_t *t = &parse.jedec;
		क्रम (i = 0; i < t->nid; i++)
			pr_debug("JEDEC: 0x%02x 0x%02x\n",
			      t->id[i].mfr, t->id[i].info);
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक pcmciamtd_cistpl_device(काष्ठा pcmcia_device *p_dev,
				tuple_t *tuple,
				व्योम *priv_data)
अणु
	काष्ठा pcmciamtd_dev *dev = priv_data;
	cisparse_t parse;
	cistpl_device_t *t = &parse.device;
	पूर्णांक i;

	अगर (pcmcia_parse_tuple(tuple, &parse))
		वापस -EINVAL;

	pr_debug("Common memory:\n");
	dev->pcmcia_map.size = t->dev[0].size;
	/* from here on: DEBUG only */
	क्रम (i = 0; i < t->ndev; i++) अणु
		pr_debug("Region %d, type = %u\n", i, t->dev[i].type);
		pr_debug("Region %d, wp = %u\n", i, t->dev[i].wp);
		pr_debug("Region %d, speed = %u ns\n", i, t->dev[i].speed);
		pr_debug("Region %d, size = %u bytes\n", i, t->dev[i].size);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcmciamtd_cistpl_geo(काष्ठा pcmcia_device *p_dev,
				tuple_t *tuple,
				व्योम *priv_data)
अणु
	काष्ठा pcmciamtd_dev *dev = priv_data;
	cisparse_t parse;
	cistpl_device_geo_t *t = &parse.device_geo;
	पूर्णांक i;

	अगर (pcmcia_parse_tuple(tuple, &parse))
		वापस -EINVAL;

	dev->pcmcia_map.bankwidth = t->geo[0].buswidth;
	/* from here on: DEBUG only */
	क्रम (i = 0; i < t->ngeo; i++) अणु
		pr_debug("region: %d bankwidth = %u\n", i, t->geo[i].buswidth);
		pr_debug("region: %d erase_block = %u\n", i, t->geo[i].erase_block);
		pr_debug("region: %d read_block = %u\n", i, t->geo[i].पढ़ो_block);
		pr_debug("region: %d write_block = %u\n", i, t->geo[i].ग_लिखो_block);
		pr_debug("region: %d partition = %u\n", i, t->geo[i].partition);
		pr_debug("region: %d interleave = %u\n", i, t->geo[i].पूर्णांकerleave);
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम card_settings(काष्ठा pcmciamtd_dev *dev, काष्ठा pcmcia_device *p_dev, पूर्णांक *new_name)
अणु
	पूर्णांक i;

	अगर (p_dev->prod_id[0]) अणु
		dev->mtd_name[0] = '\0';
		क्रम (i = 0; i < 4; i++) अणु
			अगर (i)
				म_जोड़ो(dev->mtd_name, " ");
			अगर (p_dev->prod_id[i])
				म_जोड़ो(dev->mtd_name, p_dev->prod_id[i]);
		पूर्ण
		pr_debug("Found name: %s\n", dev->mtd_name);
	पूर्ण

	pcmcia_loop_tuple(p_dev, CISTPL_FORMAT, pcmciamtd_cistpl_क्रमmat, शून्य);
	pcmcia_loop_tuple(p_dev, CISTPL_JEDEC_C, pcmciamtd_cistpl_jedec, शून्य);
	pcmcia_loop_tuple(p_dev, CISTPL_DEVICE, pcmciamtd_cistpl_device, dev);
	pcmcia_loop_tuple(p_dev, CISTPL_DEVICE_GEO, pcmciamtd_cistpl_geo, dev);

	अगर(!dev->pcmcia_map.size)
		dev->pcmcia_map.size = MAX_PCMCIA_ADDR;

	अगर(!dev->pcmcia_map.bankwidth)
		dev->pcmcia_map.bankwidth = 2;

	अगर(क्रमce_size) अणु
		dev->pcmcia_map.size = क्रमce_size << 20;
		pr_debug("size forced to %dM\n", क्रमce_size);
	पूर्ण

	अगर(bankwidth) अणु
		dev->pcmcia_map.bankwidth = bankwidth;
		pr_debug("bankwidth forced to %d\n", bankwidth);
	पूर्ण

	dev->pcmcia_map.name = dev->mtd_name;
	अगर(!dev->mtd_name[0]) अणु
		म_नकल(dev->mtd_name, "PCMCIA Memory card");
		*new_name = 1;
	पूर्ण

	pr_debug("Device: Size: %lu Width:%d Name: %s\n",
	      dev->pcmcia_map.size,
	      dev->pcmcia_map.bankwidth << 3, dev->mtd_name);
पूर्ण


अटल पूर्णांक pcmciamtd_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा pcmciamtd_dev *dev = link->priv;
	काष्ठा mtd_info *mtd = शून्य;
	पूर्णांक ret;
	पूर्णांक i, j = 0;
	अटल अक्षर *probes[] = अणु "jedec_probe", "cfi_probe" पूर्ण;
	पूर्णांक new_name = 0;

	pr_debug("link=0x%p\n", link);

	card_settings(dev, link, &new_name);

	dev->pcmcia_map.phys = NO_XIP;
	dev->pcmcia_map.copy_from = pcmcia_copy_from_remap;
	dev->pcmcia_map.copy_to = pcmcia_copy_to_remap;
	अगर (dev->pcmcia_map.bankwidth == 1) अणु
		dev->pcmcia_map.पढ़ो = pcmcia_पढ़ो8_remap;
		dev->pcmcia_map.ग_लिखो = pcmcia_ग_लिखो8_remap;
	पूर्ण अन्यथा अणु
		dev->pcmcia_map.पढ़ो = pcmcia_पढ़ो16_remap;
		dev->pcmcia_map.ग_लिखो = pcmcia_ग_लिखो16_remap;
	पूर्ण
	अगर(setvpp == 1)
		dev->pcmcia_map.set_vpp = pcmciamtd_set_vpp;

	/* Request a memory winकरोw क्रम PCMCIA. Some architeures can map winकरोws
	 * up to the maximum that PCMCIA can support (64MiB) - this is ideal and
	 * we aim क्रम a winकरोw the size of the whole card - otherwise we try
	 * smaller winकरोws until we succeed
	 */

	link->resource[2]->flags |=  WIN_MEMORY_TYPE_CM | WIN_ENABLE;
	link->resource[2]->flags |= (dev->pcmcia_map.bankwidth == 1) ?
					WIN_DATA_WIDTH_8 : WIN_DATA_WIDTH_16;
	link->resource[2]->start = 0;
	link->resource[2]->end = (क्रमce_size) ? क्रमce_size << 20 :
					MAX_PCMCIA_ADDR;
	dev->win_size = 0;

	करो अणु
		पूर्णांक ret;
		pr_debug("requesting window with size = %luKiB memspeed = %d\n",
			(अचिन्हित दीर्घ) resource_size(link->resource[2]) >> 10,
			mem_speed);
		ret = pcmcia_request_winकरोw(link, link->resource[2], mem_speed);
		pr_debug("ret = %d dev->win_size = %d\n", ret, dev->win_size);
		अगर(ret) अणु
			j++;
			link->resource[2]->start = 0;
			link->resource[2]->end = (क्रमce_size) ?
					क्रमce_size << 20 : MAX_PCMCIA_ADDR;
			link->resource[2]->end >>= j;
		पूर्ण अन्यथा अणु
			pr_debug("Got window of size %luKiB\n", (अचिन्हित दीर्घ)
				resource_size(link->resource[2]) >> 10);
			dev->win_size = resource_size(link->resource[2]);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (link->resource[2]->end >= 0x1000);

	pr_debug("dev->win_size = %d\n", dev->win_size);

	अगर(!dev->win_size) अणु
		dev_err(&dev->p_dev->dev, "Cannot allocate memory window\n");
		pcmciamtd_release(link);
		वापस -ENODEV;
	पूर्ण
	pr_debug("Allocated a window of %dKiB\n", dev->win_size >> 10);

	/* Get ग_लिखो protect status */
	dev->win_base = ioremap(link->resource[2]->start,
				resource_size(link->resource[2]));
	अगर(!dev->win_base) अणु
		dev_err(&dev->p_dev->dev, "ioremap(%pR) failed\n",
			link->resource[2]);
		pcmciamtd_release(link);
		वापस -ENODEV;
	पूर्ण
	pr_debug("mapped window dev = %p @ %pR, base = %p\n",
	      dev, link->resource[2], dev->win_base);

	dev->offset = 0;
	dev->pcmcia_map.map_priv_1 = (अचिन्हित दीर्घ)dev;
	dev->pcmcia_map.map_priv_2 = (अचिन्हित दीर्घ)link->resource[2];

	dev->vpp = (vpp) ? vpp : link->socket->socket.Vpp;
	अगर(setvpp == 2) अणु
		link->vpp = dev->vpp;
	पूर्ण अन्यथा अणु
		link->vpp = 0;
	पूर्ण

	link->config_index = 0;
	pr_debug("Setting Configuration\n");
	ret = pcmcia_enable_device(link);
	अगर (ret != 0) अणु
		अगर (dev->win_base) अणु
			iounmap(dev->win_base);
			dev->win_base = शून्य;
		पूर्ण
		वापस -ENODEV;
	पूर्ण

	अगर(mem_type == 1) अणु
		mtd = करो_map_probe("map_ram", &dev->pcmcia_map);
	पूर्ण अन्यथा अगर(mem_type == 2) अणु
		mtd = करो_map_probe("map_rom", &dev->pcmcia_map);
	पूर्ण अन्यथा अणु
		क्रम(i = 0; i < ARRAY_SIZE(probes); i++) अणु
			pr_debug("Trying %s\n", probes[i]);
			mtd = करो_map_probe(probes[i], &dev->pcmcia_map);
			अगर(mtd)
				अवरोध;

			pr_debug("FAILED: %s\n", probes[i]);
		पूर्ण
	पूर्ण

	अगर(!mtd) अणु
		pr_debug("Can not find an MTD\n");
		pcmciamtd_release(link);
		वापस -ENODEV;
	पूर्ण

	dev->mtd_info = mtd;
	mtd->owner = THIS_MODULE;

	अगर(new_name) अणु
		पूर्णांक size = 0;
		अक्षर unit = ' ';
		/* Since we are using a शेष name, make it better by adding
		 * in the size
		 */
		अगर(mtd->size < 1048576) अणु /* <1MiB in size, show size in KiB */
			size = mtd->size >> 10;
			unit = 'K';
		पूर्ण अन्यथा अणु
			size = mtd->size >> 20;
			unit = 'M';
		पूर्ण
		snम_लिखो(dev->mtd_name, माप(dev->mtd_name), "%d%ciB %s", size, unit, "PCMCIA Memory card");
	पूर्ण

	/* If the memory found is fits completely पूर्णांकo the mapped PCMCIA winकरोw,
	   use the faster non-remapping पढ़ो/ग_लिखो functions */
	अगर(mtd->size <= dev->win_size) अणु
		pr_debug("Using non remapping memory functions\n");
		dev->pcmcia_map.map_priv_2 = (अचिन्हित दीर्घ)dev->win_base;
		अगर (dev->pcmcia_map.bankwidth == 1) अणु
			dev->pcmcia_map.पढ़ो = pcmcia_पढ़ो8;
			dev->pcmcia_map.ग_लिखो = pcmcia_ग_लिखो8;
		पूर्ण अन्यथा अणु
			dev->pcmcia_map.पढ़ो = pcmcia_पढ़ो16;
			dev->pcmcia_map.ग_लिखो = pcmcia_ग_लिखो16;
		पूर्ण
		dev->pcmcia_map.copy_from = pcmcia_copy_from;
		dev->pcmcia_map.copy_to = pcmcia_copy_to;
	पूर्ण

	अगर (mtd_device_रेजिस्टर(mtd, शून्य, 0)) अणु
		map_destroy(mtd);
		dev->mtd_info = शून्य;
		dev_err(&dev->p_dev->dev,
			"Could not register the MTD device\n");
		pcmciamtd_release(link);
		वापस -ENODEV;
	पूर्ण
	dev_info(&dev->p_dev->dev, "mtd%d: %s\n", mtd->index, mtd->name);
	वापस 0;
पूर्ण


अटल पूर्णांक pcmciamtd_suspend(काष्ठा pcmcia_device *dev)
अणु
	pr_debug("EVENT_PM_RESUME\n");

	/* get_lock(link); */

	वापस 0;
पूर्ण

अटल पूर्णांक pcmciamtd_resume(काष्ठा pcmcia_device *dev)
अणु
	pr_debug("EVENT_PM_SUSPEND\n");

	/* मुक्त_lock(link); */

	वापस 0;
पूर्ण


अटल व्योम pcmciamtd_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा pcmciamtd_dev *dev = link->priv;

	pr_debug("link=0x%p\n", link);

	अगर(dev->mtd_info) अणु
		mtd_device_unरेजिस्टर(dev->mtd_info);
		dev_info(&dev->p_dev->dev, "mtd%d: Removing\n",
			 dev->mtd_info->index);
		map_destroy(dev->mtd_info);
	पूर्ण

	pcmciamtd_release(link);
पूर्ण


अटल पूर्णांक pcmciamtd_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा pcmciamtd_dev *dev;

	/* Create new memory card device */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) वापस -ENOMEM;
	pr_debug("dev=0x%p\n", dev);

	dev->p_dev = link;
	link->priv = dev;

	वापस pcmciamtd_config(link);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id pcmciamtd_ids[] = अणु
	PCMCIA_DEVICE_FUNC_ID(1),
	PCMCIA_DEVICE_PROD_ID123("IO DATA", "PCS-2M", "2MB SRAM", 0x547e66dc, 0x1fed36cd, 0x36eadd21),
	PCMCIA_DEVICE_PROD_ID12("IBM", "2MB SRAM", 0xb569a6e5, 0x36eadd21),
	PCMCIA_DEVICE_PROD_ID12("IBM", "4MB FLASH", 0xb569a6e5, 0x8bc54d2a),
	PCMCIA_DEVICE_PROD_ID12("IBM", "8MB FLASH", 0xb569a6e5, 0x6df1be3e),
	PCMCIA_DEVICE_PROD_ID12("Intel", "S2E20SW", 0x816cc815, 0xd14c9dcf),
	PCMCIA_DEVICE_PROD_ID12("Intel", "S2E8 SW", 0x816cc815, 0xa2d7dedb),
	PCMCIA_DEVICE_PROD_ID12("intel", "SERIES2-02 ", 0x40ade711, 0x145cea5c),
	PCMCIA_DEVICE_PROD_ID12("intel", "SERIES2-04 ", 0x40ade711, 0x42064dda),
	PCMCIA_DEVICE_PROD_ID12("intel", "SERIES2-20 ", 0x40ade711, 0x25ee5cb0),
	PCMCIA_DEVICE_PROD_ID12("intel", "VALUE SERIES 100 ", 0x40ade711, 0xdf8506d8),
	PCMCIA_DEVICE_PROD_ID12("KINGMAX TECHNOLOGY INC.", "SRAM 256K Bytes", 0x54d0c69c, 0xad12c29c),
	PCMCIA_DEVICE_PROD_ID12("Maxtor", "MAXFL MobileMax Flash Memory Card", 0xb68968c8, 0x2dfb47b0),
	PCMCIA_DEVICE_PROD_ID123("M-Systems", "M-SYS Flash Memory Card", "(c) M-Systems", 0x7ed2ad87, 0x675dc3fb, 0x7aef3965),
	PCMCIA_DEVICE_PROD_ID12("PRETEC", "  2MB SRAM CARD", 0xebf91155, 0x805360ca),
	PCMCIA_DEVICE_PROD_ID12("PRETEC", "  4MB SRAM CARD", 0xebf91155, 0x20b6bf17),
	PCMCIA_DEVICE_PROD_ID12("SEIKO EPSON", "WWB101EN20", 0xf9876baf, 0xad0b207b),
	PCMCIA_DEVICE_PROD_ID12("SEIKO EPSON", "WWB513EN20", 0xf9876baf, 0xe8d884ad),
	PCMCIA_DEVICE_PROD_ID12("SMART Modular Technologies", " 4MB FLASH Card", 0x96fd8277, 0x737a5b05),
	PCMCIA_DEVICE_PROD_ID12("Starfish, Inc.", "REX-3000", 0x05ddca47, 0xe7d67bca),
	PCMCIA_DEVICE_PROD_ID12("Starfish, Inc.", "REX-4100", 0x05ddca47, 0x7bc32944),
	/* the following was commented out in pcmcia-cs-3.2.7 */
	/* PCMCIA_DEVICE_PROD_ID12("RATOC Systems,Inc.", "SmartMedia ADAPTER PC Card", 0xf4a2fefe, 0x5885b2ae), */
#अगर_घोषित CONFIG_MTD_PCMCIA_ANONYMOUS
	अणु .match_flags = PCMCIA_DEV_ID_MATCH_ANONYMOUS, पूर्ण,
#पूर्ण_अगर
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, pcmciamtd_ids);

अटल काष्ठा pcmcia_driver pcmciamtd_driver = अणु
	.name		= "pcmciamtd",
	.probe		= pcmciamtd_probe,
	.हटाओ		= pcmciamtd_detach,
	.owner		= THIS_MODULE,
	.id_table	= pcmciamtd_ids,
	.suspend	= pcmciamtd_suspend,
	.resume		= pcmciamtd_resume,
पूर्ण;


अटल पूर्णांक __init init_pcmciamtd(व्योम)
अणु
	अगर(bankwidth && bankwidth != 1 && bankwidth != 2) अणु
		info("bad bankwidth (%d), using default", bankwidth);
		bankwidth = 2;
	पूर्ण
	अगर(क्रमce_size && (क्रमce_size < 1 || क्रमce_size > 64)) अणु
		info("bad force_size (%d), using default", क्रमce_size);
		क्रमce_size = 0;
	पूर्ण
	अगर(mem_type && mem_type != 1 && mem_type != 2) अणु
		info("bad mem_type (%d), using default", mem_type);
		mem_type = 0;
	पूर्ण
	वापस pcmcia_रेजिस्टर_driver(&pcmciamtd_driver);
पूर्ण


अटल व्योम __निकास निकास_pcmciamtd(व्योम)
अणु
	pr_debug(DRIVER_DESC " unloading");
	pcmcia_unरेजिस्टर_driver(&pcmciamtd_driver);
पूर्ण

module_init(init_pcmciamtd);
module_निकास(निकास_pcmciamtd);
