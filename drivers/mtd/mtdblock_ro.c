<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Simple पढ़ो-only (writable only क्रम RAM) mtdblock driver
 *
 * Copyright तऊ 2001-2010 David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/blktrans.h>
#समावेश <linux/module.h>
#समावेश <linux/major.h>

अटल पूर्णांक mtdblock_पढ़ोsect(काष्ठा mtd_blktrans_dev *dev,
			      अचिन्हित दीर्घ block, अक्षर *buf)
अणु
	माप_प्रकार retlen;

	अगर (mtd_पढ़ो(dev->mtd, (block * 512), 512, &retlen, buf))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक mtdblock_ग_लिखोsect(काष्ठा mtd_blktrans_dev *dev,
			      अचिन्हित दीर्घ block, अक्षर *buf)
अणु
	माप_प्रकार retlen;

	अगर (mtd_ग_लिखो(dev->mtd, (block * 512), 512, &retlen, buf))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम mtdblock_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_blktrans_dev *dev = kzalloc(माप(*dev), GFP_KERNEL);

	अगर (!dev)
		वापस;

	dev->mtd = mtd;
	dev->devnum = mtd->index;

	dev->size = mtd->size >> 9;
	dev->tr = tr;
	dev->पढ़ोonly = 1;

	अगर (add_mtd_blktrans_dev(dev))
		kमुक्त(dev);
पूर्ण

अटल व्योम mtdblock_हटाओ_dev(काष्ठा mtd_blktrans_dev *dev)
अणु
	del_mtd_blktrans_dev(dev);
पूर्ण

अटल काष्ठा mtd_blktrans_ops mtdblock_tr = अणु
	.name		= "mtdblock",
	.major		= MTD_BLOCK_MAJOR,
	.part_bits	= 0,
	.blksize 	= 512,
	.पढ़ोsect	= mtdblock_पढ़ोsect,
	.ग_लिखोsect	= mtdblock_ग_लिखोsect,
	.add_mtd	= mtdblock_add_mtd,
	.हटाओ_dev	= mtdblock_हटाओ_dev,
	.owner		= THIS_MODULE,
पूर्ण;

module_mtd_blktrans(mtdblock_tr);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("Simple read-only block device emulation access to MTD devices");
