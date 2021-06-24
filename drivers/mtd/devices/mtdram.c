<शैली गुरु>
/*
 * mtdram - a test mtd device
 * Author: Alexander Larsson <alex@cendio.se>
 *
 * Copyright (c) 1999 Alexander Larsson <alex@cendio.se>
 * Copyright (c) 2005 Joern Engel <joern@wh.fh-wedel.de>
 *
 * This code is GPL
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/mtdram.h>

अटल अचिन्हित दीर्घ total_size = CONFIG_MTDRAM_TOTAL_SIZE;
अटल अचिन्हित दीर्घ erase_size = CONFIG_MTDRAM_ERASE_SIZE;
अटल अचिन्हित दीर्घ ग_लिखोbuf_size = 64;
#घोषणा MTDRAM_TOTAL_SIZE (total_size * 1024)
#घोषणा MTDRAM_ERASE_SIZE (erase_size * 1024)

module_param(total_size, uदीर्घ, 0);
MODULE_PARM_DESC(total_size, "Total device size in KiB");
module_param(erase_size, uदीर्घ, 0);
MODULE_PARM_DESC(erase_size, "Device erase block size in KiB");
module_param(ग_लिखोbuf_size, uदीर्घ, 0);
MODULE_PARM_DESC(ग_लिखोbuf_size, "Device write buf size in Bytes (Default: 64)");

// We could store these in the mtd काष्ठाure, but we only support 1 device..
अटल काष्ठा mtd_info *mtd_info;

अटल पूर्णांक check_offs_len(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret = 0;

	/* Start address must align on block boundary */
	अगर (mtd_mod_by_eb(ofs, mtd)) अणु
		pr_debug("%s: unaligned address\n", __func__);
		ret = -EINVAL;
	पूर्ण

	/* Length must align on block boundary */
	अगर (mtd_mod_by_eb(len, mtd)) अणु
		pr_debug("%s: length not block aligned\n", __func__);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ram_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	अगर (check_offs_len(mtd, instr->addr, instr->len))
		वापस -EINVAL;
	स_रखो((अक्षर *)mtd->priv + instr->addr, 0xff, instr->len);

	वापस 0;
पूर्ण

अटल पूर्णांक ram_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys)
अणु
	*virt = mtd->priv + from;
	*retlen = len;

	अगर (phys) अणु
		/* limit retlen to the number of contiguous physical pages */
		अचिन्हित दीर्घ page_ofs = offset_in_page(*virt);
		व्योम *addr = *virt - page_ofs;
		अचिन्हित दीर्घ pfn1, pfn0 = vदो_स्मृति_to_pfn(addr);

		*phys = __pfn_to_phys(pfn0) + page_ofs;
		len += page_ofs;
		जबतक (len > PAGE_SIZE) अणु
			len -= PAGE_SIZE;
			addr += PAGE_SIZE;
			pfn0++;
			pfn1 = vदो_स्मृति_to_pfn(addr);
			अगर (pfn1 != pfn0) अणु
				*retlen = addr - *virt;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ram_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ram_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	स_नकल(buf, mtd->priv + from, len);
	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक ram_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	स_नकल((अक्षर *)mtd->priv + to, buf, len);
	*retlen = len;
	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_mtdram(व्योम)
अणु
	अगर (mtd_info) अणु
		mtd_device_unरेजिस्टर(mtd_info);
		vमुक्त(mtd_info->priv);
		kमुक्त(mtd_info);
	पूर्ण
पूर्ण

पूर्णांक mtdram_init_device(काष्ठा mtd_info *mtd, व्योम *mapped_address,
		अचिन्हित दीर्घ size, स्थिर अक्षर *name)
अणु
	स_रखो(mtd, 0, माप(*mtd));

	/* Setup the MTD काष्ठाure */
	mtd->name = name;
	mtd->type = MTD_RAM;
	mtd->flags = MTD_CAP_RAM;
	mtd->size = size;
	mtd->ग_लिखोsize = 1;
	mtd->ग_लिखोbufsize = ग_लिखोbuf_size;
	mtd->erasesize = MTDRAM_ERASE_SIZE;
	mtd->priv = mapped_address;

	mtd->owner = THIS_MODULE;
	mtd->_erase = ram_erase;
	mtd->_poपूर्णांक = ram_poपूर्णांक;
	mtd->_unpoपूर्णांक = ram_unpoपूर्णांक;
	mtd->_पढ़ो = ram_पढ़ो;
	mtd->_ग_लिखो = ram_ग_लिखो;

	अगर (mtd_device_रेजिस्टर(mtd, शून्य, 0))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक __init init_mtdram(व्योम)
अणु
	व्योम *addr;
	पूर्णांक err;

	अगर (!total_size)
		वापस -EINVAL;

	/* Allocate some memory */
	mtd_info = kदो_स्मृति(माप(काष्ठा mtd_info), GFP_KERNEL);
	अगर (!mtd_info)
		वापस -ENOMEM;

	addr = vदो_स्मृति(MTDRAM_TOTAL_SIZE);
	अगर (!addr) अणु
		kमुक्त(mtd_info);
		mtd_info = शून्य;
		वापस -ENOMEM;
	पूर्ण
	err = mtdram_init_device(mtd_info, addr, MTDRAM_TOTAL_SIZE, "mtdram test device");
	अगर (err) अणु
		vमुक्त(addr);
		kमुक्त(mtd_info);
		mtd_info = शून्य;
		वापस err;
	पूर्ण
	स_रखो(mtd_info->priv, 0xff, MTDRAM_TOTAL_SIZE);
	वापस err;
पूर्ण

module_init(init_mtdram);
module_निकास(cleanup_mtdram);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Larsson <alexl@redhat.com>");
MODULE_DESCRIPTION("Simulated MTD driver for testing");
