<शैली गुरु>
/****************************************************************************/

/*
 *	uclinux.c -- generic memory mapped MTD driver क्रम uclinux
 *
 *	(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)
 *
 *      License: GPL
 */

/****************************************************************************/

#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/major.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>

/****************************************************************************/

#अगर_घोषित CONFIG_MTD_ROM
#घोषणा MAP_NAME "rom"
#अन्यथा
#घोषणा MAP_NAME "ram"
#पूर्ण_अगर

अटल काष्ठा map_info uclinux_ram_map = अणु
	.name = MAP_NAME,
	.size = 0,
पूर्ण;

अटल अचिन्हित दीर्घ physaddr = -1;
module_param(physaddr, uदीर्घ, S_IRUGO);

अटल काष्ठा mtd_info *uclinux_ram_mtdinfo;

/****************************************************************************/

अटल स्थिर काष्ठा mtd_partition uclinux_romfs[] = अणु
	अणु .name = "ROMfs" पूर्ण
पूर्ण;

#घोषणा	NUM_PARTITIONS	ARRAY_SIZE(uclinux_romfs)

/****************************************************************************/

अटल पूर्णांक uclinux_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
	माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys)
अणु
	काष्ठा map_info *map = mtd->priv;
	*virt = map->virt + from;
	अगर (phys)
		*phys = map->phys + from;
	*retlen = len;
	वापस(0);
पूर्ण

/****************************************************************************/

अटल पूर्णांक __init uclinux_mtd_init(व्योम)
अणु
	काष्ठा mtd_info *mtd;
	काष्ठा map_info *mapp;

	mapp = &uclinux_ram_map;

	अगर (physaddr == -1)
		mapp->phys = (resource_माप_प्रकार)__bss_stop;
	अन्यथा
		mapp->phys = physaddr;

	अगर (!mapp->size)
		mapp->size = PAGE_ALIGN(ntohl(*((अचिन्हित दीर्घ *)(mapp->phys + 8))));
	mapp->bankwidth = 4;

	prपूर्णांकk("uclinux[mtd]: probe address=0x%x size=0x%x\n",
	       	(पूर्णांक) mapp->phys, (पूर्णांक) mapp->size);

	/*
	 * The fileप्रणाली is guaranteed to be in direct mapped memory. It is
	 * directly following the kernels own bss region. Following the same
	 * mechanism used by architectures setting up traditional initrds we
	 * use phys_to_virt to get the भव address of its start.
	 */
	mapp->virt = phys_to_virt(mapp->phys);

	अगर (mapp->virt == 0) अणु
		prपूर्णांकk("uclinux[mtd]: no virtual mapping?\n");
		वापस(-EIO);
	पूर्ण

	simple_map_init(mapp);

	mtd = करो_map_probe("map_" MAP_NAME, mapp);
	अगर (!mtd) अणु
		prपूर्णांकk("uclinux[mtd]: failed to find a mapping?\n");
		वापस(-ENXIO);
	पूर्ण

	mtd->owner = THIS_MODULE;
	mtd->_poपूर्णांक = uclinux_poपूर्णांक;
	mtd->priv = mapp;

	uclinux_ram_mtdinfo = mtd;
	mtd_device_रेजिस्टर(mtd, uclinux_romfs, NUM_PARTITIONS);

	वापस(0);
पूर्ण
device_initcall(uclinux_mtd_init);

/****************************************************************************/
