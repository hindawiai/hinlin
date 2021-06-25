<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MTD device concatenation layer
 *
 * Copyright तऊ 2002 Robert Kaiser <rkaiser@sysgo.de>
 * Copyright तऊ 2002-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * न_अंकD support by Christian Gan <cgan@iders.ca>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/backing-dev.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/concat.h>

#समावेश <यंत्र/भाग64.h>

/*
 * Our storage काष्ठाure:
 * Subdev poपूर्णांकs to an array of poपूर्णांकers to काष्ठा mtd_info objects
 * which is allocated aदीर्घ with this काष्ठाure
 *
 */
काष्ठा mtd_concat अणु
	काष्ठा mtd_info mtd;
	पूर्णांक num_subdev;
	काष्ठा mtd_info **subdev;
पूर्ण;

/*
 * how to calculate the size required क्रम the above काष्ठाure,
 * including the poपूर्णांकer array subdev poपूर्णांकs to:
 */
#घोषणा SIZखातापूर्ण_STRUCT_MTD_CONCAT(num_subdev)	\
	((माप(काष्ठा mtd_concat) + (num_subdev) * माप(काष्ठा mtd_info *)))

/*
 * Given a poपूर्णांकer to the MTD object in the mtd_concat काष्ठाure,
 * we can retrieve the poपूर्णांकer to that काष्ठाure with this macro.
 */
#घोषणा CONCAT(x)  ((काष्ठा mtd_concat *)(x))

/*
 * MTD methods which look up the relevant subdevice, translate the
 * effective address and pass through to the subdevice.
 */

अटल पूर्णांक
concat_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
	    माप_प्रकार * retlen, u_अक्षर * buf)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक ret = 0, err;
	पूर्णांक i;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];
		माप_प्रकार size, retsize;

		अगर (from >= subdev->size) अणु
			/* Not destined क्रम this subdev */
			size = 0;
			from -= subdev->size;
			जारी;
		पूर्ण
		अगर (from + len > subdev->size)
			/* First part goes पूर्णांकo this subdev */
			size = subdev->size - from;
		अन्यथा
			/* Entire transaction goes पूर्णांकo this subdev */
			size = len;

		err = mtd_पढ़ो(subdev, from, size, &retsize, buf);

		/* Save inक्रमmation about bitflips! */
		अगर (unlikely(err)) अणु
			अगर (mtd_is_eccerr(err)) अणु
				mtd->ecc_stats.failed++;
				ret = err;
			पूर्ण अन्यथा अगर (mtd_is_bitflip(err)) अणु
				mtd->ecc_stats.corrected++;
				/* Do not overग_लिखो -EBADMSG !! */
				अगर (!ret)
					ret = err;
			पूर्ण अन्यथा
				वापस err;
		पूर्ण

		*retlen += retsize;
		len -= size;
		अगर (len == 0)
			वापस ret;

		buf += size;
		from = 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
concat_panic_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
	     माप_प्रकार * retlen, स्थिर u_अक्षर * buf)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक err = -EINVAL;
	पूर्णांक i;
	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];
		माप_प्रकार size, retsize;

		अगर (to >= subdev->size) अणु
			to -= subdev->size;
			जारी;
		पूर्ण
		अगर (to + len > subdev->size)
			size = subdev->size - to;
		अन्यथा
			size = len;

		err = mtd_panic_ग_लिखो(subdev, to, size, &retsize, buf);
		अगर (err == -EOPNOTSUPP) अणु
			prपूर्णांकk(KERN_ERR "mtdconcat: Cannot write from panic without panic_write\n");
			वापस err;
		पूर्ण
		अगर (err)
			अवरोध;

		*retlen += retsize;
		len -= size;
		अगर (len == 0)
			अवरोध;

		err = -EINVAL;
		buf += size;
		to = 0;
	पूर्ण
	वापस err;
पूर्ण


अटल पूर्णांक
concat_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
	     माप_प्रकार * retlen, स्थिर u_अक्षर * buf)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक err = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];
		माप_प्रकार size, retsize;

		अगर (to >= subdev->size) अणु
			size = 0;
			to -= subdev->size;
			जारी;
		पूर्ण
		अगर (to + len > subdev->size)
			size = subdev->size - to;
		अन्यथा
			size = len;

		err = mtd_ग_लिखो(subdev, to, size, &retsize, buf);
		अगर (err)
			अवरोध;

		*retlen += retsize;
		len -= size;
		अगर (len == 0)
			अवरोध;

		err = -EINVAL;
		buf += size;
		to = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
concat_ग_लिखोv(काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
		अचिन्हित दीर्घ count, loff_t to, माप_प्रकार * retlen)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	काष्ठा kvec *vecs_copy;
	अचिन्हित दीर्घ entry_low, entry_high;
	माप_प्रकार total_len = 0;
	पूर्णांक i;
	पूर्णांक err = -EINVAL;

	/* Calculate total length of data */
	क्रम (i = 0; i < count; i++)
		total_len += vecs[i].iov_len;

	/* Check alignment */
	अगर (mtd->ग_लिखोsize > 1) अणु
		uपूर्णांक64_t __to = to;
		अगर (करो_भाग(__to, mtd->ग_लिखोsize) || (total_len % mtd->ग_लिखोsize))
			वापस -EINVAL;
	पूर्ण

	/* make a copy of vecs */
	vecs_copy = kmemdup(vecs, माप(काष्ठा kvec) * count, GFP_KERNEL);
	अगर (!vecs_copy)
		वापस -ENOMEM;

	entry_low = 0;
	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];
		माप_प्रकार size, wsize, retsize, old_iov_len;

		अगर (to >= subdev->size) अणु
			to -= subdev->size;
			जारी;
		पूर्ण

		size = min_t(uपूर्णांक64_t, total_len, subdev->size - to);
		wsize = size; /* store क्रम future use */

		entry_high = entry_low;
		जबतक (entry_high < count) अणु
			अगर (size <= vecs_copy[entry_high].iov_len)
				अवरोध;
			size -= vecs_copy[entry_high++].iov_len;
		पूर्ण

		old_iov_len = vecs_copy[entry_high].iov_len;
		vecs_copy[entry_high].iov_len = size;

		err = mtd_ग_लिखोv(subdev, &vecs_copy[entry_low],
				 entry_high - entry_low + 1, to, &retsize);

		vecs_copy[entry_high].iov_len = old_iov_len - size;
		vecs_copy[entry_high].iov_base += size;

		entry_low = entry_high;

		अगर (err)
			अवरोध;

		*retlen += retsize;
		total_len -= wsize;

		अगर (total_len == 0)
			अवरोध;

		err = -EINVAL;
		to = 0;
	पूर्ण

	kमुक्त(vecs_copy);
	वापस err;
पूर्ण

अटल पूर्णांक
concat_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t from, काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	काष्ठा mtd_oob_ops devops = *ops;
	पूर्णांक i, err, ret = 0;

	ops->retlen = ops->oobretlen = 0;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];

		अगर (from >= subdev->size) अणु
			from -= subdev->size;
			जारी;
		पूर्ण

		/* partial पढ़ो ? */
		अगर (from + devops.len > subdev->size)
			devops.len = subdev->size - from;

		err = mtd_पढ़ो_oob(subdev, from, &devops);
		ops->retlen += devops.retlen;
		ops->oobretlen += devops.oobretlen;

		/* Save inक्रमmation about bitflips! */
		अगर (unlikely(err)) अणु
			अगर (mtd_is_eccerr(err)) अणु
				mtd->ecc_stats.failed++;
				ret = err;
			पूर्ण अन्यथा अगर (mtd_is_bitflip(err)) अणु
				mtd->ecc_stats.corrected++;
				/* Do not overग_लिखो -EBADMSG !! */
				अगर (!ret)
					ret = err;
			पूर्ण अन्यथा
				वापस err;
		पूर्ण

		अगर (devops.datbuf) अणु
			devops.len = ops->len - ops->retlen;
			अगर (!devops.len)
				वापस ret;
			devops.datbuf += devops.retlen;
		पूर्ण
		अगर (devops.oobbuf) अणु
			devops.ooblen = ops->ooblen - ops->oobretlen;
			अगर (!devops.ooblen)
				वापस ret;
			devops.oobbuf += ops->oobretlen;
		पूर्ण

		from = 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
concat_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t to, काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	काष्ठा mtd_oob_ops devops = *ops;
	पूर्णांक i, err;

	अगर (!(mtd->flags & MTD_WRITEABLE))
		वापस -EROFS;

	ops->retlen = ops->oobretlen = 0;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];

		अगर (to >= subdev->size) अणु
			to -= subdev->size;
			जारी;
		पूर्ण

		/* partial ग_लिखो ? */
		अगर (to + devops.len > subdev->size)
			devops.len = subdev->size - to;

		err = mtd_ग_लिखो_oob(subdev, to, &devops);
		ops->retlen += devops.retlen;
		ops->oobretlen += devops.oobretlen;
		अगर (err)
			वापस err;

		अगर (devops.datbuf) अणु
			devops.len = ops->len - ops->retlen;
			अगर (!devops.len)
				वापस 0;
			devops.datbuf += devops.retlen;
		पूर्ण
		अगर (devops.oobbuf) अणु
			devops.ooblen = ops->ooblen - ops->oobretlen;
			अगर (!devops.ooblen)
				वापस 0;
			devops.oobbuf += devops.oobretlen;
		पूर्ण
		to = 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक concat_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	काष्ठा mtd_info *subdev;
	पूर्णांक i, err;
	uपूर्णांक64_t length, offset = 0;
	काष्ठा erase_info *erase;

	/*
	 * Check क्रम proper erase block alignment of the to-be-erased area.
	 * It is easier to करो this based on the super device's erase
	 * region info rather than looking at each particular sub-device
	 * in turn.
	 */
	अगर (!concat->mtd.numeraseregions) अणु
		/* the easy हाल: device has unअगरorm erase block size */
		अगर (instr->addr & (concat->mtd.erasesize - 1))
			वापस -EINVAL;
		अगर (instr->len & (concat->mtd.erasesize - 1))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* device has variable erase size */
		काष्ठा mtd_erase_region_info *erase_regions =
		    concat->mtd.eraseregions;

		/*
		 * Find the erase region where the to-be-erased area begins:
		 */
		क्रम (i = 0; i < concat->mtd.numeraseregions &&
		     instr->addr >= erase_regions[i].offset; i++) ;
		--i;

		/*
		 * Now erase_regions[i] is the region in which the
		 * to-be-erased area begins. Verअगरy that the starting
		 * offset is aligned to this region's erase size:
		 */
		अगर (i < 0 || instr->addr & (erase_regions[i].erasesize - 1))
			वापस -EINVAL;

		/*
		 * now find the erase region where the to-be-erased area ends:
		 */
		क्रम (; i < concat->mtd.numeraseregions &&
		     (instr->addr + instr->len) >= erase_regions[i].offset;
		     ++i) ;
		--i;
		/*
		 * check अगर the ending offset is aligned to this region's erase size
		 */
		अगर (i < 0 || ((instr->addr + instr->len) &
					(erase_regions[i].erasesize - 1)))
			वापस -EINVAL;
	पूर्ण

	/* make a local copy of instr to aव्योम modअगरying the caller's काष्ठा */
	erase = kदो_स्मृति(माप (काष्ठा erase_info), GFP_KERNEL);

	अगर (!erase)
		वापस -ENOMEM;

	*erase = *instr;
	length = instr->len;

	/*
	 * find the subdevice where the to-be-erased area begins, adjust
	 * starting offset to be relative to the subdevice start
	 */
	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		subdev = concat->subdev[i];
		अगर (subdev->size <= erase->addr) अणु
			erase->addr -= subdev->size;
			offset += subdev->size;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* must never happen since size limit has been verअगरied above */
	BUG_ON(i >= concat->num_subdev);

	/* now करो the erase: */
	err = 0;
	क्रम (; length > 0; i++) अणु
		/* loop क्रम all subdevices affected by this request */
		subdev = concat->subdev[i];	/* get current subdevice */

		/* limit length to subdevice's size: */
		अगर (erase->addr + length > subdev->size)
			erase->len = subdev->size - erase->addr;
		अन्यथा
			erase->len = length;

		length -= erase->len;
		अगर ((err = mtd_erase(subdev, erase))) अणु
			/* sanity check: should never happen since
			 * block alignment has been checked above */
			BUG_ON(err == -EINVAL);
			अगर (erase->fail_addr != MTD_FAIL_ADDR_UNKNOWN)
				instr->fail_addr = erase->fail_addr + offset;
			अवरोध;
		पूर्ण
		/*
		 * erase->addr specअगरies the offset of the area to be
		 * erased *within the current subdevice*. It can be
		 * non-zero only the first समय through this loop, i.e.
		 * क्रम the first subdevice where blocks need to be erased.
		 * All the following erases must begin at the start of the
		 * current subdevice, i.e. at offset zero.
		 */
		erase->addr = 0;
		offset += subdev->size;
	पूर्ण
	kमुक्त(erase);

	वापस err;
पूर्ण

अटल पूर्णांक concat_xxlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len,
			 bool is_lock)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक i, err = -EINVAL;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];
		uपूर्णांक64_t size;

		अगर (ofs >= subdev->size) अणु
			size = 0;
			ofs -= subdev->size;
			जारी;
		पूर्ण
		अगर (ofs + len > subdev->size)
			size = subdev->size - ofs;
		अन्यथा
			size = len;

		अगर (is_lock)
			err = mtd_lock(subdev, ofs, size);
		अन्यथा
			err = mtd_unlock(subdev, ofs, size);
		अगर (err)
			अवरोध;

		len -= size;
		अगर (len == 0)
			अवरोध;

		err = -EINVAL;
		ofs = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक concat_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस concat_xxlock(mtd, ofs, len, true);
पूर्ण

अटल पूर्णांक concat_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस concat_xxlock(mtd, ofs, len, false);
पूर्ण

अटल पूर्णांक concat_is_locked(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक i, err = -EINVAL;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];

		अगर (ofs >= subdev->size) अणु
			ofs -= subdev->size;
			जारी;
		पूर्ण

		अगर (ofs + len > subdev->size)
			अवरोध;

		वापस mtd_is_locked(subdev, ofs, len);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम concat_sync(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक i;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];
		mtd_sync(subdev);
	पूर्ण
पूर्ण

अटल पूर्णांक concat_suspend(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];
		अगर ((rc = mtd_suspend(subdev)) < 0)
			वापस rc;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम concat_resume(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक i;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];
		mtd_resume(subdev);
	पूर्ण
पूर्ण

अटल पूर्णांक concat_block_isbad(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक i, res = 0;

	अगर (!mtd_can_have_bb(concat->subdev[0]))
		वापस res;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];

		अगर (ofs >= subdev->size) अणु
			ofs -= subdev->size;
			जारी;
		पूर्ण

		res = mtd_block_isbad(subdev, ofs);
		अवरोध;
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक concat_block_markbad(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	पूर्णांक i, err = -EINVAL;

	क्रम (i = 0; i < concat->num_subdev; i++) अणु
		काष्ठा mtd_info *subdev = concat->subdev[i];

		अगर (ofs >= subdev->size) अणु
			ofs -= subdev->size;
			जारी;
		पूर्ण

		err = mtd_block_markbad(subdev, ofs);
		अगर (!err)
			mtd->ecc_stats.badblocks++;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/*
 * This function स्थिरructs a भव MTD device by concatenating
 * num_devs MTD devices. A poपूर्णांकer to the new device object is
 * stored to *new_dev upon success. This function करोes _not_
 * रेजिस्टर any devices: this is the caller's responsibility.
 */
काष्ठा mtd_info *mtd_concat_create(काष्ठा mtd_info *subdev[],	/* subdevices to concatenate */
				   पूर्णांक num_devs,	/* number of subdevices      */
				   स्थिर अक्षर *name)
अणु				/* name क्रम the new device   */
	पूर्णांक i;
	माप_प्रकार size;
	काष्ठा mtd_concat *concat;
	uपूर्णांक32_t max_erasesize, curr_erasesize;
	पूर्णांक num_erase_region;
	पूर्णांक max_ग_लिखोbufsize = 0;

	prपूर्णांकk(KERN_NOTICE "Concatenating MTD devices:\n");
	क्रम (i = 0; i < num_devs; i++)
		prपूर्णांकk(KERN_NOTICE "(%d): \"%s\"\n", i, subdev[i]->name);
	prपूर्णांकk(KERN_NOTICE "into device \"%s\"\n", name);

	/* allocate the device काष्ठाure */
	size = SIZखातापूर्ण_STRUCT_MTD_CONCAT(num_devs);
	concat = kzalloc(size, GFP_KERNEL);
	अगर (!concat) अणु
		prपूर्णांकk
		    ("memory allocation error while creating concatenated device \"%s\"\n",
		     name);
		वापस शून्य;
	पूर्ण
	concat->subdev = (काष्ठा mtd_info **) (concat + 1);

	/*
	 * Set up the new "super" device's MTD object काष्ठाure, check क्रम
	 * incompatibilities between the subdevices.
	 */
	concat->mtd.type = subdev[0]->type;
	concat->mtd.flags = subdev[0]->flags;
	concat->mtd.size = subdev[0]->size;
	concat->mtd.erasesize = subdev[0]->erasesize;
	concat->mtd.ग_लिखोsize = subdev[0]->ग_लिखोsize;

	क्रम (i = 0; i < num_devs; i++)
		अगर (max_ग_लिखोbufsize < subdev[i]->ग_लिखोbufsize)
			max_ग_लिखोbufsize = subdev[i]->ग_लिखोbufsize;
	concat->mtd.ग_लिखोbufsize = max_ग_लिखोbufsize;

	concat->mtd.subpage_sft = subdev[0]->subpage_sft;
	concat->mtd.oobsize = subdev[0]->oobsize;
	concat->mtd.oobavail = subdev[0]->oobavail;
	अगर (subdev[0]->_ग_लिखोv)
		concat->mtd._ग_लिखोv = concat_ग_लिखोv;
	अगर (subdev[0]->_पढ़ो_oob)
		concat->mtd._पढ़ो_oob = concat_पढ़ो_oob;
	अगर (subdev[0]->_ग_लिखो_oob)
		concat->mtd._ग_लिखो_oob = concat_ग_लिखो_oob;
	अगर (subdev[0]->_block_isbad)
		concat->mtd._block_isbad = concat_block_isbad;
	अगर (subdev[0]->_block_markbad)
		concat->mtd._block_markbad = concat_block_markbad;
	अगर (subdev[0]->_panic_ग_लिखो)
		concat->mtd._panic_ग_लिखो = concat_panic_ग_लिखो;

	concat->mtd.ecc_stats.badblocks = subdev[0]->ecc_stats.badblocks;

	concat->subdev[0] = subdev[0];

	क्रम (i = 1; i < num_devs; i++) अणु
		अगर (concat->mtd.type != subdev[i]->type) अणु
			kमुक्त(concat);
			prपूर्णांकk("Incompatible device type on \"%s\"\n",
			       subdev[i]->name);
			वापस शून्य;
		पूर्ण
		अगर (concat->mtd.flags != subdev[i]->flags) अणु
			/*
			 * Expect all flags except MTD_WRITEABLE to be
			 * equal on all subdevices.
			 */
			अगर ((concat->mtd.flags ^ subdev[i]->
			     flags) & ~MTD_WRITEABLE) अणु
				kमुक्त(concat);
				prपूर्णांकk("Incompatible device flags on \"%s\"\n",
				       subdev[i]->name);
				वापस शून्य;
			पूर्ण अन्यथा
				/* अगर ग_लिखोable attribute dअगरfers,
				   make super device ग_लिखोable */
				concat->mtd.flags |=
				    subdev[i]->flags & MTD_WRITEABLE;
		पूर्ण

		concat->mtd.size += subdev[i]->size;
		concat->mtd.ecc_stats.badblocks +=
			subdev[i]->ecc_stats.badblocks;
		अगर (concat->mtd.ग_लिखोsize   !=  subdev[i]->ग_लिखोsize ||
		    concat->mtd.subpage_sft != subdev[i]->subpage_sft ||
		    concat->mtd.oobsize    !=  subdev[i]->oobsize ||
		    !concat->mtd._पढ़ो_oob  != !subdev[i]->_पढ़ो_oob ||
		    !concat->mtd._ग_लिखो_oob != !subdev[i]->_ग_लिखो_oob) अणु
			kमुक्त(concat);
			prपूर्णांकk("Incompatible OOB or ECC data on \"%s\"\n",
			       subdev[i]->name);
			वापस शून्य;
		पूर्ण
		concat->subdev[i] = subdev[i];

	पूर्ण

	mtd_set_ooblayout(&concat->mtd, subdev[0]->ooblayout);

	concat->num_subdev = num_devs;
	concat->mtd.name = name;

	concat->mtd._erase = concat_erase;
	concat->mtd._पढ़ो = concat_पढ़ो;
	concat->mtd._ग_लिखो = concat_ग_लिखो;
	concat->mtd._sync = concat_sync;
	concat->mtd._lock = concat_lock;
	concat->mtd._unlock = concat_unlock;
	concat->mtd._is_locked = concat_is_locked;
	concat->mtd._suspend = concat_suspend;
	concat->mtd._resume = concat_resume;

	/*
	 * Combine the erase block size info of the subdevices:
	 *
	 * first, walk the map of the new device and see how
	 * many changes in erase size we have
	 */
	max_erasesize = curr_erasesize = subdev[0]->erasesize;
	num_erase_region = 1;
	क्रम (i = 0; i < num_devs; i++) अणु
		अगर (subdev[i]->numeraseregions == 0) अणु
			/* current subdevice has unअगरorm erase size */
			अगर (subdev[i]->erasesize != curr_erasesize) अणु
				/* अगर it dअगरfers from the last subdevice's erase size, count it */
				++num_erase_region;
				curr_erasesize = subdev[i]->erasesize;
				अगर (curr_erasesize > max_erasesize)
					max_erasesize = curr_erasesize;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* current subdevice has variable erase size */
			पूर्णांक j;
			क्रम (j = 0; j < subdev[i]->numeraseregions; j++) अणु

				/* walk the list of erase regions, count any changes */
				अगर (subdev[i]->eraseregions[j].erasesize !=
				    curr_erasesize) अणु
					++num_erase_region;
					curr_erasesize =
					    subdev[i]->eraseregions[j].
					    erasesize;
					अगर (curr_erasesize > max_erasesize)
						max_erasesize = curr_erasesize;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (num_erase_region == 1) अणु
		/*
		 * All subdevices have the same unअगरorm erase size.
		 * This is easy:
		 */
		concat->mtd.erasesize = curr_erasesize;
		concat->mtd.numeraseregions = 0;
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t पंचांगp64;

		/*
		 * erase block size varies across the subdevices: allocate
		 * space to store the data describing the variable erase regions
		 */
		काष्ठा mtd_erase_region_info *erase_region_p;
		uपूर्णांक64_t begin, position;

		concat->mtd.erasesize = max_erasesize;
		concat->mtd.numeraseregions = num_erase_region;
		concat->mtd.eraseregions = erase_region_p =
		    kदो_स्मृति_array(num_erase_region,
				  माप(काष्ठा mtd_erase_region_info),
				  GFP_KERNEL);
		अगर (!erase_region_p) अणु
			kमुक्त(concat);
			prपूर्णांकk
			    ("memory allocation error while creating erase region list"
			     " for device \"%s\"\n", name);
			वापस शून्य;
		पूर्ण

		/*
		 * walk the map of the new device once more and fill in
		 * in erase region info:
		 */
		curr_erasesize = subdev[0]->erasesize;
		begin = position = 0;
		क्रम (i = 0; i < num_devs; i++) अणु
			अगर (subdev[i]->numeraseregions == 0) अणु
				/* current subdevice has unअगरorm erase size */
				अगर (subdev[i]->erasesize != curr_erasesize) अणु
					/*
					 *  fill in an mtd_erase_region_info काष्ठाure क्रम the area
					 *  we have walked so far:
					 */
					erase_region_p->offset = begin;
					erase_region_p->erasesize =
					    curr_erasesize;
					पंचांगp64 = position - begin;
					करो_भाग(पंचांगp64, curr_erasesize);
					erase_region_p->numblocks = पंचांगp64;
					begin = position;

					curr_erasesize = subdev[i]->erasesize;
					++erase_region_p;
				पूर्ण
				position += subdev[i]->size;
			पूर्ण अन्यथा अणु
				/* current subdevice has variable erase size */
				पूर्णांक j;
				क्रम (j = 0; j < subdev[i]->numeraseregions; j++) अणु
					/* walk the list of erase regions, count any changes */
					अगर (subdev[i]->eraseregions[j].
					    erasesize != curr_erasesize) अणु
						erase_region_p->offset = begin;
						erase_region_p->erasesize =
						    curr_erasesize;
						पंचांगp64 = position - begin;
						करो_भाग(पंचांगp64, curr_erasesize);
						erase_region_p->numblocks = पंचांगp64;
						begin = position;

						curr_erasesize =
						    subdev[i]->eraseregions[j].
						    erasesize;
						++erase_region_p;
					पूर्ण
					position +=
					    subdev[i]->eraseregions[j].
					    numblocks * (uपूर्णांक64_t)curr_erasesize;
				पूर्ण
			पूर्ण
		पूर्ण
		/* Now ग_लिखो the final entry */
		erase_region_p->offset = begin;
		erase_region_p->erasesize = curr_erasesize;
		पंचांगp64 = position - begin;
		करो_भाग(पंचांगp64, curr_erasesize);
		erase_region_p->numblocks = पंचांगp64;
	पूर्ण

	वापस &concat->mtd;
पूर्ण

/* Cleans the context obtained from mtd_concat_create() */
व्योम mtd_concat_destroy(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_concat *concat = CONCAT(mtd);
	अगर (concat->mtd.numeraseregions)
		kमुक्त(concat->mtd.eraseregions);
	kमुक्त(concat);
पूर्ण

EXPORT_SYMBOL(mtd_concat_create);
EXPORT_SYMBOL(mtd_concat_destroy);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robert Kaiser <rkaiser@sysgo.de>");
MODULE_DESCRIPTION("Generic support for concatenating of MTD devices");
