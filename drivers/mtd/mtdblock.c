<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Direct MTD block device access
 *
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org>
 * Copyright तऊ 2000-2003 Nicolas Pitre <nico@fluxnic.net>
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/blktrans.h>
#समावेश <linux/mutex.h>
#समावेश <linux/major.h>


काष्ठा mtdblk_dev अणु
	काष्ठा mtd_blktrans_dev mbd;
	पूर्णांक count;
	काष्ठा mutex cache_mutex;
	अचिन्हित अक्षर *cache_data;
	अचिन्हित दीर्घ cache_offset;
	अचिन्हित पूर्णांक cache_size;
	क्रमागत अणु STATE_EMPTY, STATE_CLEAN, STATE_सूचीTY पूर्ण cache_state;
पूर्ण;

/*
 * Cache stuff...
 *
 * Since typical flash erasable sectors are much larger than what Linux's
 * buffer cache can handle, we must implement पढ़ो-modअगरy-ग_लिखो on flash
 * sectors क्रम each block ग_लिखो requests.  To aव्योम over-erasing flash sectors
 * and to speed things up, we locally cache a whole flash sector जबतक it is
 * being written to until a dअगरferent sector is required.
 */

अटल पूर्णांक erase_ग_लिखो (काष्ठा mtd_info *mtd, अचिन्हित दीर्घ pos,
			अचिन्हित पूर्णांक len, स्थिर अक्षर *buf)
अणु
	काष्ठा erase_info erase;
	माप_प्रकार retlen;
	पूर्णांक ret;

	/*
	 * First, let's erase the flash block.
	 */
	erase.addr = pos;
	erase.len = len;

	ret = mtd_erase(mtd, &erase);
	अगर (ret) अणु
		prपूर्णांकk (KERN_WARNING "mtdblock: erase of region [0x%lx, 0x%x] "
				     "on \"%s\" failed\n",
			pos, len, mtd->name);
		वापस ret;
	पूर्ण

	/*
	 * Next, ग_लिखो the data to flash.
	 */

	ret = mtd_ग_लिखो(mtd, pos, len, &retlen, buf);
	अगर (ret)
		वापस ret;
	अगर (retlen != len)
		वापस -EIO;
	वापस 0;
पूर्ण


अटल पूर्णांक ग_लिखो_cached_data (काष्ठा mtdblk_dev *mtdblk)
अणु
	काष्ठा mtd_info *mtd = mtdblk->mbd.mtd;
	पूर्णांक ret;

	अगर (mtdblk->cache_state != STATE_सूचीTY)
		वापस 0;

	pr_debug("mtdblock: writing cached data for \"%s\" "
			"at 0x%lx, size 0x%x\n", mtd->name,
			mtdblk->cache_offset, mtdblk->cache_size);

	ret = erase_ग_लिखो (mtd, mtdblk->cache_offset,
			   mtdblk->cache_size, mtdblk->cache_data);

	/*
	 * Here we could arguably set the cache state to STATE_CLEAN.
	 * However this could lead to inconsistency since we will not
	 * be notअगरied अगर this content is altered on the flash by other
	 * means.  Let's declare it empty and leave buffering tasks to
	 * the buffer cache instead.
	 *
	 * If this cache_offset poपूर्णांकs to a bad block, data cannot be
	 * written to the device. Clear cache_state to aव्योम writing to
	 * bad blocks repeatedly.
	 */
	अगर (ret == 0 || ret == -EIO)
		mtdblk->cache_state = STATE_EMPTY;
	वापस ret;
पूर्ण


अटल पूर्णांक करो_cached_ग_लिखो (काष्ठा mtdblk_dev *mtdblk, अचिन्हित दीर्घ pos,
			    पूर्णांक len, स्थिर अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = mtdblk->mbd.mtd;
	अचिन्हित पूर्णांक sect_size = mtdblk->cache_size;
	माप_प्रकार retlen;
	पूर्णांक ret;

	pr_debug("mtdblock: write on \"%s\" at 0x%lx, size 0x%x\n",
		mtd->name, pos, len);

	अगर (!sect_size)
		वापस mtd_ग_लिखो(mtd, pos, len, &retlen, buf);

	जबतक (len > 0) अणु
		अचिन्हित दीर्घ sect_start = (pos/sect_size)*sect_size;
		अचिन्हित पूर्णांक offset = pos - sect_start;
		अचिन्हित पूर्णांक size = sect_size - offset;
		अगर( size > len )
			size = len;

		अगर (size == sect_size) अणु
			/*
			 * We are covering a whole sector.  Thus there is no
			 * need to bother with the cache जबतक it may still be
			 * useful क्रम other partial ग_लिखोs.
			 */
			ret = erase_ग_लिखो (mtd, pos, size, buf);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			/* Partial sector: need to use the cache */

			अगर (mtdblk->cache_state == STATE_सूचीTY &&
			    mtdblk->cache_offset != sect_start) अणु
				ret = ग_लिखो_cached_data(mtdblk);
				अगर (ret)
					वापस ret;
			पूर्ण

			अगर (mtdblk->cache_state == STATE_EMPTY ||
			    mtdblk->cache_offset != sect_start) अणु
				/* fill the cache with the current sector */
				mtdblk->cache_state = STATE_EMPTY;
				ret = mtd_पढ़ो(mtd, sect_start, sect_size,
					       &retlen, mtdblk->cache_data);
				अगर (ret)
					वापस ret;
				अगर (retlen != sect_size)
					वापस -EIO;

				mtdblk->cache_offset = sect_start;
				mtdblk->cache_size = sect_size;
				mtdblk->cache_state = STATE_CLEAN;
			पूर्ण

			/* ग_लिखो data to our local cache */
			स_नकल (mtdblk->cache_data + offset, buf, size);
			mtdblk->cache_state = STATE_सूचीTY;
		पूर्ण

		buf += size;
		pos += size;
		len -= size;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक करो_cached_पढ़ो (काष्ठा mtdblk_dev *mtdblk, अचिन्हित दीर्घ pos,
			   पूर्णांक len, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = mtdblk->mbd.mtd;
	अचिन्हित पूर्णांक sect_size = mtdblk->cache_size;
	माप_प्रकार retlen;
	पूर्णांक ret;

	pr_debug("mtdblock: read on \"%s\" at 0x%lx, size 0x%x\n",
			mtd->name, pos, len);

	अगर (!sect_size)
		वापस mtd_पढ़ो(mtd, pos, len, &retlen, buf);

	जबतक (len > 0) अणु
		अचिन्हित दीर्घ sect_start = (pos/sect_size)*sect_size;
		अचिन्हित पूर्णांक offset = pos - sect_start;
		अचिन्हित पूर्णांक size = sect_size - offset;
		अगर (size > len)
			size = len;

		/*
		 * Check अगर the requested data is alपढ़ोy cached
		 * Read the requested amount of data from our पूर्णांकernal cache अगर it
		 * contains what we want, otherwise we पढ़ो the data directly
		 * from flash.
		 */
		अगर (mtdblk->cache_state != STATE_EMPTY &&
		    mtdblk->cache_offset == sect_start) अणु
			स_नकल (buf, mtdblk->cache_data + offset, size);
		पूर्ण अन्यथा अणु
			ret = mtd_पढ़ो(mtd, pos, size, &retlen, buf);
			अगर (ret)
				वापस ret;
			अगर (retlen != size)
				वापस -EIO;
		पूर्ण

		buf += size;
		pos += size;
		len -= size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtdblock_पढ़ोsect(काष्ठा mtd_blktrans_dev *dev,
			      अचिन्हित दीर्घ block, अक्षर *buf)
अणु
	काष्ठा mtdblk_dev *mtdblk = container_of(dev, काष्ठा mtdblk_dev, mbd);
	वापस करो_cached_पढ़ो(mtdblk, block<<9, 512, buf);
पूर्ण

अटल पूर्णांक mtdblock_ग_लिखोsect(काष्ठा mtd_blktrans_dev *dev,
			      अचिन्हित दीर्घ block, अक्षर *buf)
अणु
	काष्ठा mtdblk_dev *mtdblk = container_of(dev, काष्ठा mtdblk_dev, mbd);
	अगर (unlikely(!mtdblk->cache_data && mtdblk->cache_size)) अणु
		mtdblk->cache_data = vदो_स्मृति(mtdblk->mbd.mtd->erasesize);
		अगर (!mtdblk->cache_data)
			वापस -EINTR;
		/* -EINTR is not really correct, but it is the best match
		 * करोcumented in man 2 ग_लिखो क्रम all हालs.  We could also
		 * वापस -EAGAIN someबार, but why bother?
		 */
	पूर्ण
	वापस करो_cached_ग_लिखो(mtdblk, block<<9, 512, buf);
पूर्ण

अटल पूर्णांक mtdblock_खोलो(काष्ठा mtd_blktrans_dev *mbd)
अणु
	काष्ठा mtdblk_dev *mtdblk = container_of(mbd, काष्ठा mtdblk_dev, mbd);

	pr_debug("mtdblock_open\n");

	अगर (mtdblk->count) अणु
		mtdblk->count++;
		वापस 0;
	पूर्ण

	/* OK, it's not खोलो. Create cache info क्रम it */
	mtdblk->count = 1;
	mutex_init(&mtdblk->cache_mutex);
	mtdblk->cache_state = STATE_EMPTY;
	अगर (!(mbd->mtd->flags & MTD_NO_ERASE) && mbd->mtd->erasesize) अणु
		mtdblk->cache_size = mbd->mtd->erasesize;
		mtdblk->cache_data = शून्य;
	पूर्ण

	pr_debug("ok\n");

	वापस 0;
पूर्ण

अटल व्योम mtdblock_release(काष्ठा mtd_blktrans_dev *mbd)
अणु
	काष्ठा mtdblk_dev *mtdblk = container_of(mbd, काष्ठा mtdblk_dev, mbd);

	pr_debug("mtdblock_release\n");

	mutex_lock(&mtdblk->cache_mutex);
	ग_लिखो_cached_data(mtdblk);
	mutex_unlock(&mtdblk->cache_mutex);

	अगर (!--mtdblk->count) अणु
		/*
		 * It was the last usage. Free the cache, but only sync अगर
		 * खोलोed क्रम writing.
		 */
		अगर (mbd->file_mode & FMODE_WRITE)
			mtd_sync(mbd->mtd);
		vमुक्त(mtdblk->cache_data);
	पूर्ण

	pr_debug("ok\n");
पूर्ण

अटल पूर्णांक mtdblock_flush(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा mtdblk_dev *mtdblk = container_of(dev, काष्ठा mtdblk_dev, mbd);
	पूर्णांक ret;

	mutex_lock(&mtdblk->cache_mutex);
	ret = ग_लिखो_cached_data(mtdblk);
	mutex_unlock(&mtdblk->cache_mutex);
	mtd_sync(dev->mtd);
	वापस ret;
पूर्ण

अटल व्योम mtdblock_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtdblk_dev *dev = kzalloc(माप(*dev), GFP_KERNEL);

	अगर (!dev)
		वापस;

	dev->mbd.mtd = mtd;
	dev->mbd.devnum = mtd->index;

	dev->mbd.size = mtd->size >> 9;
	dev->mbd.tr = tr;

	अगर (!(mtd->flags & MTD_WRITEABLE))
		dev->mbd.पढ़ोonly = 1;

	अगर (add_mtd_blktrans_dev(&dev->mbd))
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
	.खोलो		= mtdblock_खोलो,
	.flush		= mtdblock_flush,
	.release	= mtdblock_release,
	.पढ़ोsect	= mtdblock_पढ़ोsect,
	.ग_लिखोsect	= mtdblock_ग_लिखोsect,
	.add_mtd	= mtdblock_add_mtd,
	.हटाओ_dev	= mtdblock_हटाओ_dev,
	.owner		= THIS_MODULE,
पूर्ण;

module_mtd_blktrans(mtdblock_tr);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nicolas Pitre <nico@fluxnic.net> et al.");
MODULE_DESCRIPTION("Caching read/erase/writeback block device emulation access to MTD devices");
