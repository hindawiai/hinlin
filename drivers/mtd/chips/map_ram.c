<शैली गुरु>
/*
 * Common code to handle map devices which are simple RAM
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
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>


अटल पूर्णांक mapram_पढ़ो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक mapram_ग_लिखो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);
अटल पूर्णांक mapram_erase (काष्ठा mtd_info *, काष्ठा erase_info *);
अटल व्योम mapram_nop (काष्ठा mtd_info *);
अटल काष्ठा mtd_info *map_ram_probe(काष्ठा map_info *map);
अटल पूर्णांक mapram_poपूर्णांक (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			 माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys);
अटल पूर्णांक mapram_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len);


अटल काष्ठा mtd_chip_driver mapram_chipdrv = अणु
	.probe	= map_ram_probe,
	.name	= "map_ram",
	.module	= THIS_MODULE
पूर्ण;

अटल काष्ठा mtd_info *map_ram_probe(काष्ठा map_info *map)
अणु
	काष्ठा mtd_info *mtd;

	/* Check the first byte is RAM */
#अगर 0
	map_ग_लिखो8(map, 0x55, 0);
	अगर (map_पढ़ो8(map, 0) != 0x55)
		वापस शून्य;

	map_ग_लिखो8(map, 0xAA, 0);
	अगर (map_पढ़ो8(map, 0) != 0xAA)
		वापस शून्य;

	/* Check the last byte is RAM */
	map_ग_लिखो8(map, 0x55, map->size-1);
	अगर (map_पढ़ो8(map, map->size-1) != 0x55)
		वापस शून्य;

	map_ग_लिखो8(map, 0xAA, map->size-1);
	अगर (map_पढ़ो8(map, map->size-1) != 0xAA)
		वापस शून्य;
#पूर्ण_अगर
	/* OK. It seems to be RAM. */

	mtd = kzalloc(माप(*mtd), GFP_KERNEL);
	अगर (!mtd)
		वापस शून्य;

	map->fldrv = &mapram_chipdrv;
	mtd->priv = map;
	mtd->name = map->name;
	mtd->type = MTD_RAM;
	mtd->size = map->size;
	mtd->_erase = mapram_erase;
	mtd->_पढ़ो = mapram_पढ़ो;
	mtd->_ग_लिखो = mapram_ग_लिखो;
	mtd->_panic_ग_लिखो = mapram_ग_लिखो;
	mtd->_poपूर्णांक = mapram_poपूर्णांक;
	mtd->_sync = mapram_nop;
	mtd->_unpoपूर्णांक = mapram_unpoपूर्णांक;
	mtd->flags = MTD_CAP_RAM;
	mtd->ग_लिखोsize = 1;

	mtd->erasesize = PAGE_SIZE;
 	जबतक(mtd->size & (mtd->erasesize - 1))
		mtd->erasesize >>= 1;

	__module_get(THIS_MODULE);
	वापस mtd;
पूर्ण

अटल पूर्णांक mapram_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
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

अटल पूर्णांक mapram_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mapram_पढ़ो (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;

	map_copy_from(map, buf, from, len);
	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक mapram_ग_लिखो (काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;

	map_copy_to(map, to, buf, len);
	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक mapram_erase (काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	/* Yeah, it's inefficient. Who cares? It's faster than a _real_
	   flash erase. */
	काष्ठा map_info *map = mtd->priv;
	map_word allff;
	अचिन्हित दीर्घ i;

	allff = map_word_ff(map);
	क्रम (i=0; i<instr->len; i += map_bankwidth(map))
		map_ग_लिखो(map, allff, instr->addr + i);
	वापस 0;
पूर्ण

अटल व्योम mapram_nop(काष्ठा mtd_info *mtd)
अणु
	/* Nothing to see here */
पूर्ण

अटल पूर्णांक __init map_ram_init(व्योम)
अणु
	रेजिस्टर_mtd_chip_driver(&mapram_chipdrv);
	वापस 0;
पूर्ण

अटल व्योम __निकास map_ram_निकास(व्योम)
अणु
	unरेजिस्टर_mtd_chip_driver(&mapram_chipdrv);
पूर्ण

module_init(map_ram_init);
module_निकास(map_ram_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("MTD chip driver for RAM chips");
