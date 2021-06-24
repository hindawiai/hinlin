<शैली गुरु>
/*
 * Common code to handle map devices which are simple ROM
 * (C) 2000 Red Hat. GPL'd.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>

अटल पूर्णांक maprom_पढ़ो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक maprom_ग_लिखो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);
अटल व्योम maprom_nop (काष्ठा mtd_info *);
अटल काष्ठा mtd_info *map_rom_probe(काष्ठा map_info *map);
अटल पूर्णांक maprom_erase (काष्ठा mtd_info *mtd, काष्ठा erase_info *info);
अटल पूर्णांक maprom_poपूर्णांक (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			 माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys);
अटल पूर्णांक maprom_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len);


अटल काष्ठा mtd_chip_driver maprom_chipdrv = अणु
	.probe	= map_rom_probe,
	.name	= "map_rom",
	.module	= THIS_MODULE
पूर्ण;

अटल अचिन्हित पूर्णांक शेष_erasesize(काष्ठा map_info *map)
अणु
	स्थिर __be32 *erase_size = शून्य;

	erase_size = of_get_property(map->device_node, "erase-size", शून्य);

	वापस !erase_size ? map->size : be32_to_cpu(*erase_size);
पूर्ण

अटल काष्ठा mtd_info *map_rom_probe(काष्ठा map_info *map)
अणु
	काष्ठा mtd_info *mtd;

	mtd = kzalloc(माप(*mtd), GFP_KERNEL);
	अगर (!mtd)
		वापस शून्य;

	map->fldrv = &maprom_chipdrv;
	mtd->priv = map;
	mtd->name = map->name;
	mtd->type = MTD_ROM;
	mtd->size = map->size;
	mtd->_poपूर्णांक = maprom_poपूर्णांक;
	mtd->_unpoपूर्णांक = maprom_unpoपूर्णांक;
	mtd->_पढ़ो = maprom_पढ़ो;
	mtd->_ग_लिखो = maprom_ग_लिखो;
	mtd->_sync = maprom_nop;
	mtd->_erase = maprom_erase;
	mtd->flags = MTD_CAP_ROM;
	mtd->erasesize = शेष_erasesize(map);
	mtd->ग_लिखोsize = 1;
	mtd->ग_लिखोbufsize = 1;

	__module_get(THIS_MODULE);
	वापस mtd;
पूर्ण


अटल पूर्णांक maprom_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys)
अणु
	काष्ठा map_info *map = mtd->priv;

	अगर (!map->virt)
		वापस -EINVAL;
	*virt = map->virt + from;
	अगर (phys)
		*phys = map->phys + from;
	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक maprom_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक maprom_पढ़ो (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;

	map_copy_from(map, buf, from, len);
	*retlen = len;
	वापस 0;
पूर्ण

अटल व्योम maprom_nop(काष्ठा mtd_info *mtd)
अणु
	/* Nothing to see here */
पूर्ण

अटल पूर्णांक maprom_ग_लिखो (काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	वापस -EROFS;
पूर्ण

अटल पूर्णांक maprom_erase (काष्ठा mtd_info *mtd, काष्ठा erase_info *info)
अणु
	/* We करो our best 8) */
	वापस -EROFS;
पूर्ण

अटल पूर्णांक __init map_rom_init(व्योम)
अणु
	रेजिस्टर_mtd_chip_driver(&maprom_chipdrv);
	वापस 0;
पूर्ण

अटल व्योम __निकास map_rom_निकास(व्योम)
अणु
	unरेजिस्टर_mtd_chip_driver(&maprom_chipdrv);
पूर्ण

module_init(map_rom_init);
module_निकास(map_rom_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("MTD chip driver for ROM chips");
