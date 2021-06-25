<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2004 Liu Peng Infineon IFAP DC COM CPE
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/of.h>

#समावेश <lantiq_soc.h>

/*
 * The NOR flash is connected to the same बाह्यal bus unit (EBU) as PCI.
 * To make PCI work we need to enable the endianness swapping क्रम the address
 * written to the EBU. This endianness swapping works क्रम PCI correctly but
 * fails क्रम attached NOR devices. To workaround this we need to use a complex
 * map. The workaround involves swapping all addresses whilst probing the chip.
 * Once probing is complete we stop swapping the addresses but swizzle the
 * unlock addresses to ensure that access to the NOR device works correctly.
 */

क्रमागत अणु
	LTQ_NOR_PROBING,
	LTQ_NOR_NORMAL
पूर्ण;

काष्ठा ltq_mtd अणु
	काष्ठा resource *res;
	काष्ठा mtd_info *mtd;
	काष्ठा map_info *map;
पूर्ण;

अटल स्थिर अक्षर ltq_map_name[] = "ltq_nor";

अटल map_word
ltq_पढ़ो16(काष्ठा map_info *map, अचिन्हित दीर्घ adr)
अणु
	अचिन्हित दीर्घ flags;
	map_word temp;

	अगर (map->map_priv_1 == LTQ_NOR_PROBING)
		adr ^= 2;
	spin_lock_irqsave(&ebu_lock, flags);
	temp.x[0] = *(u16 *)(map->virt + adr);
	spin_unlock_irqrestore(&ebu_lock, flags);
	वापस temp;
पूर्ण

अटल व्योम
ltq_ग_लिखो16(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	अचिन्हित दीर्घ flags;

	अगर (map->map_priv_1 == LTQ_NOR_PROBING)
		adr ^= 2;
	spin_lock_irqsave(&ebu_lock, flags);
	*(u16 *)(map->virt + adr) = d.x[0];
	spin_unlock_irqrestore(&ebu_lock, flags);
पूर्ण

/*
 * The following 2 functions copy data between iomem and a cached memory
 * section. As स_नकल() makes use of pre-fetching we cannot use it here.
 * The normal alternative of using स_नकल_अणुto,fromपूर्णio also makes use of
 * स_नकल() on MIPS so it is not applicable either. We are thereक्रमe stuck
 * with having to use our own loop.
 */
अटल व्योम
ltq_copy_from(काष्ठा map_info *map, व्योम *to,
	अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	अचिन्हित अक्षर *f = (अचिन्हित अक्षर *)map->virt + from;
	अचिन्हित अक्षर *t = (अचिन्हित अक्षर *)to;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ebu_lock, flags);
	जबतक (len--)
		*t++ = *f++;
	spin_unlock_irqrestore(&ebu_lock, flags);
पूर्ण

अटल व्योम
ltq_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ to,
	स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	अचिन्हित अक्षर *f = (अचिन्हित अक्षर *)from;
	अचिन्हित अक्षर *t = (अचिन्हित अक्षर *)map->virt + to;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ebu_lock, flags);
	जबतक (len--)
		*t++ = *f++;
	spin_unlock_irqrestore(&ebu_lock, flags);
पूर्ण

अटल पूर्णांक
ltq_mtd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ltq_mtd *ltq_mtd;
	काष्ठा cfi_निजी *cfi;
	पूर्णांक err;

	ltq_mtd = devm_kzalloc(&pdev->dev, माप(काष्ठा ltq_mtd), GFP_KERNEL);
	अगर (!ltq_mtd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ltq_mtd);

	ltq_mtd->res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!ltq_mtd->res) अणु
		dev_err(&pdev->dev, "failed to get memory resource\n");
		वापस -ENOENT;
	पूर्ण

	ltq_mtd->map = devm_kzalloc(&pdev->dev, माप(काष्ठा map_info),
				    GFP_KERNEL);
	अगर (!ltq_mtd->map)
		वापस -ENOMEM;

	ltq_mtd->map->phys = ltq_mtd->res->start;
	ltq_mtd->map->size = resource_size(ltq_mtd->res);
	ltq_mtd->map->virt = devm_ioremap_resource(&pdev->dev, ltq_mtd->res);
	अगर (IS_ERR(ltq_mtd->map->virt))
		वापस PTR_ERR(ltq_mtd->map->virt);

	ltq_mtd->map->name = ltq_map_name;
	ltq_mtd->map->bankwidth = 2;
	ltq_mtd->map->पढ़ो = ltq_पढ़ो16;
	ltq_mtd->map->ग_लिखो = ltq_ग_लिखो16;
	ltq_mtd->map->copy_from = ltq_copy_from;
	ltq_mtd->map->copy_to = ltq_copy_to;

	ltq_mtd->map->map_priv_1 = LTQ_NOR_PROBING;
	ltq_mtd->mtd = करो_map_probe("cfi_probe", ltq_mtd->map);
	ltq_mtd->map->map_priv_1 = LTQ_NOR_NORMAL;

	अगर (!ltq_mtd->mtd) अणु
		dev_err(&pdev->dev, "probing failed\n");
		वापस -ENXIO;
	पूर्ण

	ltq_mtd->mtd->dev.parent = &pdev->dev;
	mtd_set_of_node(ltq_mtd->mtd, pdev->dev.of_node);

	cfi = ltq_mtd->map->fldrv_priv;
	cfi->addr_unlock1 ^= 1;
	cfi->addr_unlock2 ^= 1;

	err = mtd_device_रेजिस्टर(ltq_mtd->mtd, शून्य, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to add partitions\n");
		जाओ err_destroy;
	पूर्ण

	वापस 0;

err_destroy:
	map_destroy(ltq_mtd->mtd);
	वापस err;
पूर्ण

अटल पूर्णांक
ltq_mtd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ltq_mtd *ltq_mtd = platक्रमm_get_drvdata(pdev);

	अगर (ltq_mtd && ltq_mtd->mtd) अणु
		mtd_device_unरेजिस्टर(ltq_mtd->mtd);
		map_destroy(ltq_mtd->mtd);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ltq_mtd_match[] = अणु
	अणु .compatible = "lantiq,nor" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltq_mtd_match);

अटल काष्ठा platक्रमm_driver ltq_mtd_driver = अणु
	.probe = ltq_mtd_probe,
	.हटाओ = ltq_mtd_हटाओ,
	.driver = अणु
		.name = "ltq-nor",
		.of_match_table = ltq_mtd_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ltq_mtd_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Crispin <john@phrozen.org>");
MODULE_DESCRIPTION("Lantiq SoC NOR");
