<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा dev_fmt(fmt) "mtdoops-pstore: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pstore_blk.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>

अटल काष्ठा mtdpstore_context अणु
	पूर्णांक index;
	काष्ठा pstore_blk_config info;
	काष्ठा pstore_device_info dev;
	काष्ठा mtd_info *mtd;
	अचिन्हित दीर्घ *rmmap;		/* हटाओd bit map */
	अचिन्हित दीर्घ *usedmap;		/* used bit map */
	/*
	 * used क्रम panic ग_लिखो
	 * As there are no block_isbad क्रम panic हाल, we should keep this
	 * status beक्रमe panic to ensure panic_ग_लिखो not failed.
	 */
	अचिन्हित दीर्घ *badmap;		/* bad block bit map */
पूर्ण oops_cxt;

अटल पूर्णांक mtdpstore_block_isbad(काष्ठा mtdpstore_context *cxt, loff_t off)
अणु
	पूर्णांक ret;
	काष्ठा mtd_info *mtd = cxt->mtd;
	u64 blknum;

	off = ALIGN_DOWN(off, mtd->erasesize);
	blknum = भाग_u64(off, mtd->erasesize);

	अगर (test_bit(blknum, cxt->badmap))
		वापस true;
	ret = mtd_block_isbad(mtd, off);
	अगर (ret < 0) अणु
		dev_err(&mtd->dev, "mtd_block_isbad failed, aborting\n");
		वापस ret;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		set_bit(blknum, cxt->badmap);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक mtdpstore_panic_block_isbad(काष्ठा mtdpstore_context *cxt,
		loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u64 blknum;

	off = ALIGN_DOWN(off, mtd->erasesize);
	blknum = भाग_u64(off, mtd->erasesize);
	वापस test_bit(blknum, cxt->badmap);
पूर्ण

अटल अंतरभूत व्योम mtdpstore_mark_used(काष्ठा mtdpstore_context *cxt,
		loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u64 zonक्रमागत = भाग_u64(off, cxt->info.kmsg_size);

	dev_dbg(&mtd->dev, "mark zone %llu used\n", zonक्रमागत);
	set_bit(zonक्रमागत, cxt->usedmap);
पूर्ण

अटल अंतरभूत व्योम mtdpstore_mark_unused(काष्ठा mtdpstore_context *cxt,
		loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u64 zonक्रमागत = भाग_u64(off, cxt->info.kmsg_size);

	dev_dbg(&mtd->dev, "mark zone %llu unused\n", zonक्रमागत);
	clear_bit(zonक्रमागत, cxt->usedmap);
पूर्ण

अटल अंतरभूत व्योम mtdpstore_block_mark_unused(काष्ठा mtdpstore_context *cxt,
		loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u32 zonecnt = mtd->erasesize / cxt->info.kmsg_size;
	u64 zonक्रमागत;

	off = ALIGN_DOWN(off, mtd->erasesize);
	zonक्रमागत = भाग_u64(off, cxt->info.kmsg_size);
	जबतक (zonecnt > 0) अणु
		dev_dbg(&mtd->dev, "mark zone %llu unused\n", zonक्रमागत);
		clear_bit(zonक्रमागत, cxt->usedmap);
		zonक्रमागत++;
		zonecnt--;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक mtdpstore_is_used(काष्ठा mtdpstore_context *cxt, loff_t off)
अणु
	u64 zonक्रमागत = भाग_u64(off, cxt->info.kmsg_size);
	u64 blknum = भाग_u64(off, cxt->mtd->erasesize);

	अगर (test_bit(blknum, cxt->badmap))
		वापस true;
	वापस test_bit(zonक्रमागत, cxt->usedmap);
पूर्ण

अटल पूर्णांक mtdpstore_block_is_used(काष्ठा mtdpstore_context *cxt,
		loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u32 zonecnt = mtd->erasesize / cxt->info.kmsg_size;
	u64 zonक्रमागत;

	off = ALIGN_DOWN(off, mtd->erasesize);
	zonक्रमागत = भाग_u64(off, cxt->info.kmsg_size);
	जबतक (zonecnt > 0) अणु
		अगर (test_bit(zonक्रमागत, cxt->usedmap))
			वापस true;
		zonक्रमागत++;
		zonecnt--;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक mtdpstore_is_empty(काष्ठा mtdpstore_context *cxt, अक्षर *buf,
		माप_प्रकार size)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	माप_प्रकार sz;
	पूर्णांक i;

	sz = min_t(uपूर्णांक32_t, size, mtd->ग_लिखोsize / 4);
	क्रम (i = 0; i < sz; i++) अणु
		अगर (buf[i] != (अक्षर)0xFF)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम mtdpstore_mark_हटाओd(काष्ठा mtdpstore_context *cxt, loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u64 zonक्रमागत = भाग_u64(off, cxt->info.kmsg_size);

	dev_dbg(&mtd->dev, "mark zone %llu removed\n", zonक्रमागत);
	set_bit(zonक्रमागत, cxt->rmmap);
पूर्ण

अटल व्योम mtdpstore_block_clear_हटाओd(काष्ठा mtdpstore_context *cxt,
		loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u32 zonecnt = mtd->erasesize / cxt->info.kmsg_size;
	u64 zonक्रमागत;

	off = ALIGN_DOWN(off, mtd->erasesize);
	zonक्रमागत = भाग_u64(off, cxt->info.kmsg_size);
	जबतक (zonecnt > 0) अणु
		clear_bit(zonक्रमागत, cxt->rmmap);
		zonक्रमागत++;
		zonecnt--;
	पूर्ण
पूर्ण

अटल पूर्णांक mtdpstore_block_is_हटाओd(काष्ठा mtdpstore_context *cxt,
		loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u32 zonecnt = mtd->erasesize / cxt->info.kmsg_size;
	u64 zonक्रमागत;

	off = ALIGN_DOWN(off, mtd->erasesize);
	zonक्रमागत = भाग_u64(off, cxt->info.kmsg_size);
	जबतक (zonecnt > 0) अणु
		अगर (test_bit(zonक्रमागत, cxt->rmmap))
			वापस true;
		zonक्रमागत++;
		zonecnt--;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक mtdpstore_erase_करो(काष्ठा mtdpstore_context *cxt, loff_t off)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	काष्ठा erase_info erase;
	पूर्णांक ret;

	off = ALIGN_DOWN(off, cxt->mtd->erasesize);
	dev_dbg(&mtd->dev, "try to erase off 0x%llx\n", off);
	erase.len = cxt->mtd->erasesize;
	erase.addr = off;
	ret = mtd_erase(cxt->mtd, &erase);
	अगर (!ret)
		mtdpstore_block_clear_हटाओd(cxt, off);
	अन्यथा
		dev_err(&mtd->dev, "erase of region [0x%llx, 0x%llx] on \"%s\" failed\n",
		       (अचिन्हित दीर्घ दीर्घ)erase.addr,
		       (अचिन्हित दीर्घ दीर्घ)erase.len, cxt->info.device);
	वापस ret;
पूर्ण

/*
 * called जबतक removing file
 *
 * Aव्योमing over erasing, करो erase block only when the whole block is unused.
 * If the block contains valid log, करो erase lazily on flush_हटाओd() when
 * unरेजिस्टर.
 */
अटल sमाप_प्रकार mtdpstore_erase(माप_प्रकार size, loff_t off)
अणु
	काष्ठा mtdpstore_context *cxt = &oops_cxt;

	अगर (mtdpstore_block_isbad(cxt, off))
		वापस -EIO;

	mtdpstore_mark_unused(cxt, off);

	/* If the block still has valid data, mtdpstore करो erase lazily */
	अगर (likely(mtdpstore_block_is_used(cxt, off))) अणु
		mtdpstore_mark_हटाओd(cxt, off);
		वापस 0;
	पूर्ण

	/* all zones are unused, erase it */
	वापस mtdpstore_erase_करो(cxt, off);
पूर्ण

/*
 * What is security क्रम mtdpstore?
 * As there is no erase क्रम panic हाल, we should ensure at least one zone
 * is writable. Otherwise, panic ग_लिखो will fail.
 * If zone is used, ग_लिखो operation will वापस -ENOMSG, which means that
 * pstore/blk will try one by one until माला_लो an empty zone. So, it is not
 * needed to ensure the next zone is empty, but at least one.
 */
अटल पूर्णांक mtdpstore_security(काष्ठा mtdpstore_context *cxt, loff_t off)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा mtd_info *mtd = cxt->mtd;
	u32 zonक्रमागत = (u32)भाग_u64(off, cxt->info.kmsg_size);
	u32 zonecnt = (u32)भाग_u64(cxt->mtd->size, cxt->info.kmsg_size);
	u32 blkcnt = (u32)भाग_u64(cxt->mtd->size, cxt->mtd->erasesize);
	u32 erasesize = cxt->mtd->erasesize;

	क्रम (i = 0; i < zonecnt; i++) अणु
		u32 num = (zonक्रमागत + i) % zonecnt;

		/* found empty zone */
		अगर (!test_bit(num, cxt->usedmap))
			वापस 0;
	पूर्ण

	/* If there is no any empty zone, we have no way but to करो erase */
	जबतक (blkcnt--) अणु
		भाग64_u64_rem(off + erasesize, cxt->mtd->size, (u64 *)&off);

		अगर (mtdpstore_block_isbad(cxt, off))
			जारी;

		ret = mtdpstore_erase_करो(cxt, off);
		अगर (!ret) अणु
			mtdpstore_block_mark_unused(cxt, off);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		dev_err(&mtd->dev, "all blocks bad!\n");
	dev_dbg(&mtd->dev, "end security\n");
	वापस ret;
पूर्ण

अटल sमाप_प्रकार mtdpstore_ग_लिखो(स्थिर अक्षर *buf, माप_प्रकार size, loff_t off)
अणु
	काष्ठा mtdpstore_context *cxt = &oops_cxt;
	काष्ठा mtd_info *mtd = cxt->mtd;
	माप_प्रकार retlen;
	पूर्णांक ret;

	अगर (mtdpstore_block_isbad(cxt, off))
		वापस -ENOMSG;

	/* zone is used, please try next one */
	अगर (mtdpstore_is_used(cxt, off))
		वापस -ENOMSG;

	dev_dbg(&mtd->dev, "try to write off 0x%llx size %zu\n", off, size);
	ret = mtd_ग_लिखो(cxt->mtd, off, size, &retlen, (u_अक्षर *)buf);
	अगर (ret < 0 || retlen != size) अणु
		dev_err(&mtd->dev, "write failure at %lld (%zu of %zu written), err %d\n",
				off, retlen, size, ret);
		वापस -EIO;
	पूर्ण
	mtdpstore_mark_used(cxt, off);

	mtdpstore_security(cxt, off);
	वापस retlen;
पूर्ण

अटल अंतरभूत bool mtdpstore_is_io_error(पूर्णांक ret)
अणु
	वापस ret < 0 && !mtd_is_bitflip(ret) && !mtd_is_eccerr(ret);
पूर्ण

/*
 * All zones will be पढ़ो as pstore/blk will पढ़ो zone one by one when करो
 * recover.
 */
अटल sमाप_प्रकार mtdpstore_पढ़ो(अक्षर *buf, माप_प्रकार size, loff_t off)
अणु
	काष्ठा mtdpstore_context *cxt = &oops_cxt;
	काष्ठा mtd_info *mtd = cxt->mtd;
	माप_प्रकार retlen, करोne;
	पूर्णांक ret;

	अगर (mtdpstore_block_isbad(cxt, off))
		वापस -ENOMSG;

	dev_dbg(&mtd->dev, "try to read off 0x%llx size %zu\n", off, size);
	क्रम (करोne = 0, retlen = 0; करोne < size; करोne += retlen) अणु
		retlen = 0;

		ret = mtd_पढ़ो(cxt->mtd, off + करोne, size - करोne, &retlen,
				(u_अक्षर *)buf + करोne);
		अगर (mtdpstore_is_io_error(ret)) अणु
			dev_err(&mtd->dev, "read failure at %lld (%zu of %zu read), err %d\n",
					off + करोne, retlen, size - करोne, ret);
			/* the zone may be broken, try next one */
			वापस -ENOMSG;
		पूर्ण

		/*
		 * ECC error. The impact on log data is so small. Maybe we can
		 * still पढ़ो it and try to understand. So mtdpstore just hands
		 * over what it माला_लो and user can judge whether the data is
		 * valid or not.
		 */
		अगर (mtd_is_eccerr(ret)) अणु
			dev_err(&mtd->dev, "ecc error at %lld (%zu of %zu read), err %d\n",
					off + करोne, retlen, size - करोne, ret);
			/* driver may not set retlen when ecc error */
			retlen = retlen == 0 ? size - करोne : retlen;
		पूर्ण
	पूर्ण

	अगर (mtdpstore_is_empty(cxt, buf, size))
		mtdpstore_mark_unused(cxt, off);
	अन्यथा
		mtdpstore_mark_used(cxt, off);

	mtdpstore_security(cxt, off);
	वापस retlen;
पूर्ण

अटल sमाप_प्रकार mtdpstore_panic_ग_लिखो(स्थिर अक्षर *buf, माप_प्रकार size, loff_t off)
अणु
	काष्ठा mtdpstore_context *cxt = &oops_cxt;
	काष्ठा mtd_info *mtd = cxt->mtd;
	माप_प्रकार retlen;
	पूर्णांक ret;

	अगर (mtdpstore_panic_block_isbad(cxt, off))
		वापस -ENOMSG;

	/* zone is used, please try next one */
	अगर (mtdpstore_is_used(cxt, off))
		वापस -ENOMSG;

	ret = mtd_panic_ग_लिखो(cxt->mtd, off, size, &retlen, (u_अक्षर *)buf);
	अगर (ret < 0 || size != retlen) अणु
		dev_err(&mtd->dev, "panic write failure at %lld (%zu of %zu read), err %d\n",
				off, retlen, size, ret);
		वापस -EIO;
	पूर्ण
	mtdpstore_mark_used(cxt, off);

	वापस retlen;
पूर्ण

अटल व्योम mtdpstore_notअगरy_add(काष्ठा mtd_info *mtd)
अणु
	पूर्णांक ret;
	काष्ठा mtdpstore_context *cxt = &oops_cxt;
	काष्ठा pstore_blk_config *info = &cxt->info;
	अचिन्हित दीर्घ दीर्घcnt;

	अगर (!म_भेद(mtd->name, info->device))
		cxt->index = mtd->index;

	अगर (mtd->index != cxt->index || cxt->index < 0)
		वापस;

	dev_dbg(&mtd->dev, "found matching MTD device %s\n", mtd->name);

	अगर (mtd->size < info->kmsg_size * 2) अणु
		dev_err(&mtd->dev, "MTD partition %d not big enough\n",
				mtd->index);
		वापस;
	पूर्ण
	/*
	 * kmsg_size must be aligned to 4096 Bytes, which is limited by
	 * psblk. The शेष value of kmsg_size is 64KB. If kmsg_size
	 * is larger than erasesize, some errors will occur since mtdpsotre
	 * is deचिन्हित on it.
	 */
	अगर (mtd->erasesize < info->kmsg_size) अणु
		dev_err(&mtd->dev, "eraseblock size of MTD partition %d too small\n",
				mtd->index);
		वापस;
	पूर्ण
	अगर (unlikely(info->kmsg_size % mtd->ग_लिखोsize)) अणु
		dev_err(&mtd->dev, "record size %lu KB must align to write size %d KB\n",
				info->kmsg_size / 1024,
				mtd->ग_लिखोsize / 1024);
		वापस;
	पूर्ण

	दीर्घcnt = BITS_TO_LONGS(भाग_u64(mtd->size, info->kmsg_size));
	cxt->rmmap = kसुस्मृति(दीर्घcnt, माप(दीर्घ), GFP_KERNEL);
	cxt->usedmap = kसुस्मृति(दीर्घcnt, माप(दीर्घ), GFP_KERNEL);

	दीर्घcnt = BITS_TO_LONGS(भाग_u64(mtd->size, mtd->erasesize));
	cxt->badmap = kसुस्मृति(दीर्घcnt, माप(दीर्घ), GFP_KERNEL);

	cxt->dev.total_size = mtd->size;
	/* just support dmesg right now */
	cxt->dev.flags = PSTORE_FLAGS_DMESG;
	cxt->dev.पढ़ो = mtdpstore_पढ़ो;
	cxt->dev.ग_लिखो = mtdpstore_ग_लिखो;
	cxt->dev.erase = mtdpstore_erase;
	cxt->dev.panic_ग_लिखो = mtdpstore_panic_ग_लिखो;

	ret = रेजिस्टर_pstore_device(&cxt->dev);
	अगर (ret) अणु
		dev_err(&mtd->dev, "mtd%d register to psblk failed\n",
				mtd->index);
		वापस;
	पूर्ण
	cxt->mtd = mtd;
	dev_info(&mtd->dev, "Attached to MTD device %d\n", mtd->index);
पूर्ण

अटल पूर्णांक mtdpstore_flush_हटाओd_करो(काष्ठा mtdpstore_context *cxt,
		loff_t off, माप_प्रकार size)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u_अक्षर *buf;
	पूर्णांक ret;
	माप_प्रकार retlen;
	काष्ठा erase_info erase;

	buf = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* 1st. पढ़ो to cache */
	ret = mtd_पढ़ो(mtd, off, mtd->erasesize, &retlen, buf);
	अगर (mtdpstore_is_io_error(ret))
		जाओ मुक्त;

	/* 2nd. erase block */
	erase.len = mtd->erasesize;
	erase.addr = off;
	ret = mtd_erase(mtd, &erase);
	अगर (ret)
		जाओ मुक्त;

	/* 3rd. ग_लिखो back */
	जबतक (size) अणु
		अचिन्हित पूर्णांक zonesize = cxt->info.kmsg_size;

		/* there is valid data on block, ग_लिखो back */
		अगर (mtdpstore_is_used(cxt, off)) अणु
			ret = mtd_ग_लिखो(mtd, off, zonesize, &retlen, buf);
			अगर (ret)
				dev_err(&mtd->dev, "write failure at %lld (%zu of %u written), err %d\n",
						off, retlen, zonesize, ret);
		पूर्ण

		off += zonesize;
		size -= min_t(अचिन्हित पूर्णांक, zonesize, size);
	पूर्ण

मुक्त:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * What करोes mtdpstore_flush_हटाओd() करो?
 * When user हटाओ any log file on pstore fileप्रणाली, mtdpstore should करो
 * something to ensure log file हटाओd. If the whole block is no दीर्घer used,
 * it's nice to erase the block. However अगर the block still contains valid log,
 * what mtdpstore can करो is to erase and ग_लिखो the valid log back.
 */
अटल पूर्णांक mtdpstore_flush_हटाओd(काष्ठा mtdpstore_context *cxt)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	पूर्णांक ret;
	loff_t off;
	u32 blkcnt = (u32)भाग_u64(mtd->size, mtd->erasesize);

	क्रम (off = 0; blkcnt > 0; blkcnt--, off += mtd->erasesize) अणु
		ret = mtdpstore_block_isbad(cxt, off);
		अगर (ret)
			जारी;

		ret = mtdpstore_block_is_हटाओd(cxt, off);
		अगर (!ret)
			जारी;

		ret = mtdpstore_flush_हटाओd_करो(cxt, off, mtd->erasesize);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mtdpstore_notअगरy_हटाओ(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtdpstore_context *cxt = &oops_cxt;

	अगर (mtd->index != cxt->index || cxt->index < 0)
		वापस;

	mtdpstore_flush_हटाओd(cxt);

	unरेजिस्टर_pstore_device(&cxt->dev);
	kमुक्त(cxt->badmap);
	kमुक्त(cxt->usedmap);
	kमुक्त(cxt->rmmap);
	cxt->mtd = शून्य;
	cxt->index = -1;
पूर्ण

अटल काष्ठा mtd_notअगरier mtdpstore_notअगरier = अणु
	.add	= mtdpstore_notअगरy_add,
	.हटाओ	= mtdpstore_notअगरy_हटाओ,
पूर्ण;

अटल पूर्णांक __init mtdpstore_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा mtdpstore_context *cxt = &oops_cxt;
	काष्ठा pstore_blk_config *info = &cxt->info;

	ret = pstore_blk_get_config(info);
	अगर (unlikely(ret))
		वापस ret;

	अगर (म_माप(info->device) == 0) अणु
		pr_err("mtd device must be supplied (device name is empty)\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!info->kmsg_size) अणु
		pr_err("no backend enabled (kmsg_size is 0)\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup the MTD device to use */
	ret = kstrtoपूर्णांक((अक्षर *)info->device, 0, &cxt->index);
	अगर (ret)
		cxt->index = -1;

	रेजिस्टर_mtd_user(&mtdpstore_notअगरier);
	वापस 0;
पूर्ण
module_init(mtdpstore_init);

अटल व्योम __निकास mtdpstore_निकास(व्योम)
अणु
	unरेजिस्टर_mtd_user(&mtdpstore_notअगरier);
पूर्ण
module_निकास(mtdpstore_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WeiXiong Liao <liaoweixiong@allwinnertech.com>");
MODULE_DESCRIPTION("MTD backend for pstore/blk");
