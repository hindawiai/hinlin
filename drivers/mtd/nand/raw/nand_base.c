<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Overview:
 *   This is the generic MTD driver क्रम न_अंकD flash devices. It should be
 *   capable of working with almost all न_अंकD chips currently available.
 *
 *	Additional technical inक्रमmation is available on
 *	http://www.linux-mtd.infradead.org/करोc/nand.hपंचांगl
 *
 *  Copyright (C) 2000 Steven J. Hill (sjhill@realitydiluted.com)
 *		  2002-2006 Thomas Gleixner (tglx@linutronix.de)
 *
 *  Credits:
 *	David Woodhouse क्रम adding multichip support
 *
 *	Aleph One Ltd. and Toby Churchill Ltd. क्रम supporting the
 *	rework क्रम 2K page size chips
 *
 *  TODO:
 *	Enable cached programming क्रम 2k page size chips
 *	Check, अगर mtd->ecctype should be set to MTD_ECC_HW
 *	अगर we have HW ECC support.
 *	BBT table is not serialized, has to be fixed
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/nand-ecc-sw-bch.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "internals.h"

अटल पूर्णांक nand_pairing_dist3_get_info(काष्ठा mtd_info *mtd, पूर्णांक page,
				       काष्ठा mtd_pairing_info *info)
अणु
	पूर्णांक lastpage = (mtd->erasesize / mtd->ग_लिखोsize) - 1;
	पूर्णांक dist = 3;

	अगर (page == lastpage)
		dist = 2;

	अगर (!page || (page & 1)) अणु
		info->group = 0;
		info->pair = (page + 1) / 2;
	पूर्ण अन्यथा अणु
		info->group = 1;
		info->pair = (page + 1 - dist) / 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nand_pairing_dist3_get_wunit(काष्ठा mtd_info *mtd,
					स्थिर काष्ठा mtd_pairing_info *info)
अणु
	पूर्णांक lastpair = ((mtd->erasesize / mtd->ग_लिखोsize) - 1) / 2;
	पूर्णांक page = info->pair * 2;
	पूर्णांक dist = 3;

	अगर (!info->group && !info->pair)
		वापस 0;

	अगर (info->pair == lastpair && info->group)
		dist = 2;

	अगर (!info->group)
		page--;
	अन्यथा अगर (info->pair)
		page += dist - 1;

	अगर (page >= mtd->erasesize / mtd->ग_लिखोsize)
		वापस -EINVAL;

	वापस page;
पूर्ण

स्थिर काष्ठा mtd_pairing_scheme dist3_pairing_scheme = अणु
	.ngroups = 2,
	.get_info = nand_pairing_dist3_get_info,
	.get_wunit = nand_pairing_dist3_get_wunit,
पूर्ण;

अटल पूर्णांक check_offs_len(काष्ठा nand_chip *chip, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret = 0;

	/* Start address must align on block boundary */
	अगर (ofs & ((1ULL << chip->phys_erase_shअगरt) - 1)) अणु
		pr_debug("%s: unaligned address\n", __func__);
		ret = -EINVAL;
	पूर्ण

	/* Length must align on block boundary */
	अगर (len & ((1ULL << chip->phys_erase_shअगरt) - 1)) अणु
		pr_debug("%s: length not block aligned\n", __func__);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nand_extract_bits - Copy unaligned bits from one buffer to another one
 * @dst: destination buffer
 * @dst_off: bit offset at which the writing starts
 * @src: source buffer
 * @src_off: bit offset at which the पढ़ोing starts
 * @nbits: number of bits to copy from @src to @dst
 *
 * Copy bits from one memory region to another (overlap authorized).
 */
व्योम nand_extract_bits(u8 *dst, अचिन्हित पूर्णांक dst_off, स्थिर u8 *src,
		       अचिन्हित पूर्णांक src_off, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक पंचांगp, n;

	dst += dst_off / 8;
	dst_off %= 8;
	src += src_off / 8;
	src_off %= 8;

	जबतक (nbits) अणु
		n = min3(8 - dst_off, 8 - src_off, nbits);

		पंचांगp = (*src >> src_off) & GENMASK(n - 1, 0);
		*dst &= ~GENMASK(n - 1 + dst_off, dst_off);
		*dst |= पंचांगp << dst_off;

		dst_off += n;
		अगर (dst_off >= 8) अणु
			dst++;
			dst_off -= 8;
		पूर्ण

		src_off += n;
		अगर (src_off >= 8) अणु
			src++;
			src_off -= 8;
		पूर्ण

		nbits -= n;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nand_extract_bits);

/**
 * nand_select_target() - Select a न_अंकD target (A.K.A. die)
 * @chip: न_अंकD chip object
 * @cs: the CS line to select. Note that this CS id is always from the chip
 *	PoV, not the controller one
 *
 * Select a न_अंकD target so that further operations executed on @chip go to the
 * selected न_अंकD target.
 */
व्योम nand_select_target(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक cs)
अणु
	/*
	 * cs should always lie between 0 and nanddev_ntarमाला_लो(), when that's
	 * not the हाल it's a bug and the caller should be fixed.
	 */
	अगर (WARN_ON(cs > nanddev_ntarमाला_लो(&chip->base)))
		वापस;

	chip->cur_cs = cs;

	अगर (chip->legacy.select_chip)
		chip->legacy.select_chip(chip, cs);
पूर्ण
EXPORT_SYMBOL_GPL(nand_select_target);

/**
 * nand_deselect_target() - Deselect the currently selected target
 * @chip: न_अंकD chip object
 *
 * Deselect the currently selected न_अंकD target. The result of operations
 * executed on @chip after the target has been deselected is undefined.
 */
व्योम nand_deselect_target(काष्ठा nand_chip *chip)
अणु
	अगर (chip->legacy.select_chip)
		chip->legacy.select_chip(chip, -1);

	chip->cur_cs = -1;
पूर्ण
EXPORT_SYMBOL_GPL(nand_deselect_target);

/**
 * nand_release_device - [GENERIC] release chip
 * @chip: न_अंकD chip object
 *
 * Release chip lock and wake up anyone रुकोing on the device.
 */
अटल व्योम nand_release_device(काष्ठा nand_chip *chip)
अणु
	/* Release the controller and the chip */
	mutex_unlock(&chip->controller->lock);
	mutex_unlock(&chip->lock);
पूर्ण

/**
 * nand_bbm_get_next_page - Get the next page क्रम bad block markers
 * @chip: न_अंकD chip object
 * @page: First page to start checking क्रम bad block marker usage
 *
 * Returns an पूर्णांकeger that corresponds to the page offset within a block, क्रम
 * a page that is used to store bad block markers. If no more pages are
 * available, -EINVAL is वापसed.
 */
पूर्णांक nand_bbm_get_next_page(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक last_page = ((mtd->erasesize - mtd->ग_लिखोsize) >>
			 chip->page_shअगरt) & chip->pagemask;
	अचिन्हित पूर्णांक bbm_flags = न_अंकD_BBM_FIRSTPAGE | न_अंकD_BBM_SECONDPAGE
		| न_अंकD_BBM_LASTPAGE;

	अगर (page == 0 && !(chip->options & bbm_flags))
		वापस 0;
	अगर (page == 0 && chip->options & न_अंकD_BBM_FIRSTPAGE)
		वापस 0;
	अगर (page <= 1 && chip->options & न_अंकD_BBM_SECONDPAGE)
		वापस 1;
	अगर (page <= last_page && chip->options & न_अंकD_BBM_LASTPAGE)
		वापस last_page;

	वापस -EINVAL;
पूर्ण

/**
 * nand_block_bad - [DEFAULT] Read bad block marker from the chip
 * @chip: न_अंकD chip object
 * @ofs: offset from device start
 *
 * Check, अगर the block is bad.
 */
अटल पूर्णांक nand_block_bad(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	पूर्णांक first_page, page_offset;
	पूर्णांक res;
	u8 bad;

	first_page = (पूर्णांक)(ofs >> chip->page_shअगरt) & chip->pagemask;
	page_offset = nand_bbm_get_next_page(chip, 0);

	जबतक (page_offset >= 0) अणु
		res = chip->ecc.पढ़ो_oob(chip, first_page + page_offset);
		अगर (res < 0)
			वापस res;

		bad = chip->oob_poi[chip->badblockpos];

		अगर (likely(chip->badblockbits == 8))
			res = bad != 0xFF;
		अन्यथा
			res = hweight8(bad) < chip->badblockbits;
		अगर (res)
			वापस res;

		page_offset = nand_bbm_get_next_page(chip, page_offset + 1);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nand_region_is_secured() - Check अगर the region is secured
 * @chip: न_अंकD chip object
 * @offset: Offset of the region to check
 * @size: Size of the region to check
 *
 * Checks अगर the region is secured by comparing the offset and size with the
 * list of secure regions obtained from DT. Returns true अगर the region is
 * secured अन्यथा false.
 */
अटल bool nand_region_is_secured(काष्ठा nand_chip *chip, loff_t offset, u64 size)
अणु
	पूर्णांक i;

	/* Skip touching the secure regions अगर present */
	क्रम (i = 0; i < chip->nr_secure_regions; i++) अणु
		स्थिर काष्ठा nand_secure_region *region = &chip->secure_regions[i];

		अगर (offset + size <= region->offset ||
		    offset >= region->offset + region->size)
			जारी;

		pr_debug("%s: Region 0x%llx - 0x%llx is secured!",
			 __func__, offset, offset + size);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक nand_isbad_bbm(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (chip->options & न_अंकD_NO_BBM_QUIRK)
		वापस 0;

	/* Check अगर the region is secured */
	अगर (nand_region_is_secured(chip, ofs, mtd->erasesize))
		वापस -EIO;

	अगर (chip->legacy.block_bad)
		वापस chip->legacy.block_bad(chip, ofs);

	वापस nand_block_bad(chip, ofs);
पूर्ण

/**
 * nand_get_device - [GENERIC] Get chip क्रम selected access
 * @chip: न_अंकD chip काष्ठाure
 *
 * Lock the device and its controller क्रम exclusive access
 *
 * Return: -EBUSY अगर the chip has been suspended, 0 otherwise
 */
अटल पूर्णांक nand_get_device(काष्ठा nand_chip *chip)
अणु
	mutex_lock(&chip->lock);
	अगर (chip->suspended) अणु
		mutex_unlock(&chip->lock);
		वापस -EBUSY;
	पूर्ण
	mutex_lock(&chip->controller->lock);

	वापस 0;
पूर्ण

/**
 * nand_check_wp - [GENERIC] check अगर the chip is ग_लिखो रक्षित
 * @chip: न_अंकD chip object
 *
 * Check, अगर the device is ग_लिखो रक्षित. The function expects, that the
 * device is alपढ़ोy selected.
 */
अटल पूर्णांक nand_check_wp(काष्ठा nand_chip *chip)
अणु
	u8 status;
	पूर्णांक ret;

	/* Broken xD cards report WP despite being writable */
	अगर (chip->options & न_अंकD_BROKEN_XD)
		वापस 0;

	/* Check the WP bit */
	ret = nand_status_op(chip, &status);
	अगर (ret)
		वापस ret;

	वापस status & न_अंकD_STATUS_WP ? 0 : 1;
पूर्ण

/**
 * nand_fill_oob - [INTERN] Transfer client buffer to oob
 * @chip: न_अंकD chip object
 * @oob: oob data buffer
 * @len: oob data ग_लिखो length
 * @ops: oob ops काष्ठाure
 */
अटल uपूर्णांक8_t *nand_fill_oob(काष्ठा nand_chip *chip, uपूर्णांक8_t *oob, माप_प्रकार len,
			      काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	/*
	 * Initialise to all 0xFF, to aव्योम the possibility of left over OOB
	 * data from a previous OOB पढ़ो.
	 */
	स_रखो(chip->oob_poi, 0xff, mtd->oobsize);

	चयन (ops->mode) अणु

	हाल MTD_OPS_PLACE_OOB:
	हाल MTD_OPS_RAW:
		स_नकल(chip->oob_poi + ops->ooboffs, oob, len);
		वापस oob + len;

	हाल MTD_OPS_AUTO_OOB:
		ret = mtd_ooblayout_set_databytes(mtd, oob, chip->oob_poi,
						  ops->ooboffs, len);
		BUG_ON(ret);
		वापस oob + len;

	शेष:
		BUG();
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * nand_करो_ग_लिखो_oob - [MTD Interface] न_अंकD ग_लिखो out-of-band
 * @chip: न_अंकD chip object
 * @to: offset to ग_लिखो to
 * @ops: oob operation description काष्ठाure
 *
 * न_अंकD ग_लिखो out-of-band.
 */
अटल पूर्णांक nand_करो_ग_लिखो_oob(काष्ठा nand_chip *chip, loff_t to,
			     काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक chipnr, page, status, len, ret;

	pr_debug("%s: to = 0x%08x, len = %i\n",
			 __func__, (अचिन्हित पूर्णांक)to, (पूर्णांक)ops->ooblen);

	len = mtd_oobavail(mtd, ops);

	/* Do not allow ग_लिखो past end of page */
	अगर ((ops->ooboffs + ops->ooblen) > len) अणु
		pr_debug("%s: attempt to write past end of page\n",
				__func__);
		वापस -EINVAL;
	पूर्ण

	/* Check अगर the region is secured */
	अगर (nand_region_is_secured(chip, to, ops->ooblen))
		वापस -EIO;

	chipnr = (पूर्णांक)(to >> chip->chip_shअगरt);

	/*
	 * Reset the chip. Some chips (like the Toshiba TC5832DC found in one
	 * of my DiskOnChip 2000 test units) will clear the whole data page too
	 * अगर we करोn't do this. I have no clue why, but I seem to have 'fixed'
	 * it in the करोc2000 driver in August 1999.  dwmw2.
	 */
	ret = nand_reset(chip, chipnr);
	अगर (ret)
		वापस ret;

	nand_select_target(chip, chipnr);

	/* Shअगरt to get page */
	page = (पूर्णांक)(to >> chip->page_shअगरt);

	/* Check, अगर it is ग_लिखो रक्षित */
	अगर (nand_check_wp(chip)) अणु
		nand_deselect_target(chip);
		वापस -EROFS;
	पूर्ण

	/* Invalidate the page cache, अगर we ग_लिखो to the cached page */
	अगर (page == chip->pagecache.page)
		chip->pagecache.page = -1;

	nand_fill_oob(chip, ops->oobbuf, ops->ooblen, ops);

	अगर (ops->mode == MTD_OPS_RAW)
		status = chip->ecc.ग_लिखो_oob_raw(chip, page & chip->pagemask);
	अन्यथा
		status = chip->ecc.ग_लिखो_oob(chip, page & chip->pagemask);

	nand_deselect_target(chip);

	अगर (status)
		वापस status;

	ops->oobretlen = ops->ooblen;

	वापस 0;
पूर्ण

/**
 * nand_शेष_block_markbad - [DEFAULT] mark a block bad via bad block marker
 * @chip: न_अंकD chip object
 * @ofs: offset from device start
 *
 * This is the शेष implementation, which can be overridden by a hardware
 * specअगरic driver. It provides the details क्रम writing a bad block marker to a
 * block.
 */
अटल पूर्णांक nand_शेष_block_markbad(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mtd_oob_ops ops;
	uपूर्णांक8_t buf[2] = अणु 0, 0 पूर्ण;
	पूर्णांक ret = 0, res, page_offset;

	स_रखो(&ops, 0, माप(ops));
	ops.oobbuf = buf;
	ops.ooboffs = chip->badblockpos;
	अगर (chip->options & न_अंकD_BUSWIDTH_16) अणु
		ops.ooboffs &= ~0x01;
		ops.len = ops.ooblen = 2;
	पूर्ण अन्यथा अणु
		ops.len = ops.ooblen = 1;
	पूर्ण
	ops.mode = MTD_OPS_PLACE_OOB;

	page_offset = nand_bbm_get_next_page(chip, 0);

	जबतक (page_offset >= 0) अणु
		res = nand_करो_ग_लिखो_oob(chip,
					ofs + (page_offset * mtd->ग_लिखोsize),
					&ops);

		अगर (!ret)
			ret = res;

		page_offset = nand_bbm_get_next_page(chip, page_offset + 1);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nand_markbad_bbm - mark a block by updating the BBM
 * @chip: न_अंकD chip object
 * @ofs: offset of the block to mark bad
 */
पूर्णांक nand_markbad_bbm(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	अगर (chip->legacy.block_markbad)
		वापस chip->legacy.block_markbad(chip, ofs);

	वापस nand_शेष_block_markbad(chip, ofs);
पूर्ण

/**
 * nand_block_markbad_lowlevel - mark a block bad
 * @chip: न_अंकD chip object
 * @ofs: offset from device start
 *
 * This function perक्रमms the generic न_अंकD bad block marking steps (i.e., bad
 * block table(s) and/or marker(s)). We only allow the hardware driver to
 * specअगरy how to ग_लिखो bad block markers to OOB (chip->legacy.block_markbad).
 *
 * We try operations in the following order:
 *
 *  (1) erase the affected block, to allow OOB marker to be written cleanly
 *  (2) ग_लिखो bad block marker to OOB area of affected block (unless flag
 *      न_अंकD_BBT_NO_OOB_BBM is present)
 *  (3) update the BBT
 *
 * Note that we retain the first error encountered in (2) or (3), finish the
 * procedures, and dump the error in the end.
*/
अटल पूर्णांक nand_block_markbad_lowlevel(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक res, ret = 0;

	अगर (!(chip->bbt_options & न_अंकD_BBT_NO_OOB_BBM)) अणु
		काष्ठा erase_info einfo;

		/* Attempt erase beक्रमe marking OOB */
		स_रखो(&einfo, 0, माप(einfo));
		einfo.addr = ofs;
		einfo.len = 1ULL << chip->phys_erase_shअगरt;
		nand_erase_nand(chip, &einfo, 0);

		/* Write bad block marker to OOB */
		ret = nand_get_device(chip);
		अगर (ret)
			वापस ret;

		ret = nand_markbad_bbm(chip, ofs);
		nand_release_device(chip);
	पूर्ण

	/* Mark block bad in BBT */
	अगर (chip->bbt) अणु
		res = nand_markbad_bbt(chip, ofs);
		अगर (!ret)
			ret = res;
	पूर्ण

	अगर (!ret)
		mtd->ecc_stats.badblocks++;

	वापस ret;
पूर्ण

/**
 * nand_block_isreserved - [GENERIC] Check अगर a block is marked reserved.
 * @mtd: MTD device काष्ठाure
 * @ofs: offset from device start
 *
 * Check अगर the block is marked as reserved.
 */
अटल पूर्णांक nand_block_isreserved(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (!chip->bbt)
		वापस 0;
	/* Return info from the table */
	वापस nand_isreserved_bbt(chip, ofs);
पूर्ण

/**
 * nand_block_checkbad - [GENERIC] Check अगर a block is marked bad
 * @chip: न_अंकD chip object
 * @ofs: offset from device start
 * @allowbbt: 1, अगर its allowed to access the bbt area
 *
 * Check, अगर the block is bad. Either by पढ़ोing the bad block table or
 * calling of the scan function.
 */
अटल पूर्णांक nand_block_checkbad(काष्ठा nand_chip *chip, loff_t ofs, पूर्णांक allowbbt)
अणु
	/* Return info from the table */
	अगर (chip->bbt)
		वापस nand_isbad_bbt(chip, ofs, allowbbt);

	वापस nand_isbad_bbm(chip, ofs);
पूर्ण

/**
 * nand_soft_रुकोrdy - Poll STATUS reg until RDY bit is set to 1
 * @chip: न_अंकD chip काष्ठाure
 * @समयout_ms: Timeout in ms
 *
 * Poll the STATUS रेजिस्टर using ->exec_op() until the RDY bit becomes 1.
 * If that करोes not happen whitin the specअगरied समयout, -ETIMEDOUT is
 * वापसed.
 *
 * This helper is पूर्णांकended to be used when the controller करोes not have access
 * to the न_अंकD R/B pin.
 *
 * Be aware that calling this helper from an ->exec_op() implementation means
 * ->exec_op() must be re-entrant.
 *
 * Return 0 अगर the न_अंकD chip is पढ़ोy, a negative error otherwise.
 */
पूर्णांक nand_soft_रुकोrdy(काष्ठा nand_chip *chip, अचिन्हित दीर्घ समयout_ms)
अणु
	स्थिर काष्ठा nand_sdr_timings *timings;
	u8 status = 0;
	पूर्णांक ret;

	अगर (!nand_has_exec_op(chip))
		वापस -ENOTSUPP;

	/* Wait tWB beक्रमe polling the STATUS reg. */
	timings = nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
	ndelay(PSEC_TO_NSEC(timings->tWB_max));

	ret = nand_status_op(chip, शून्य);
	अगर (ret)
		वापस ret;

	/*
	 * +1 below is necessary because अगर we are now in the last fraction
	 * of jअगरfy and msecs_to_jअगरfies is 1 then we will रुको only that
	 * small jअगरfy fraction - possibly leading to false समयout
	 */
	समयout_ms = jअगरfies + msecs_to_jअगरfies(समयout_ms) + 1;
	करो अणु
		ret = nand_पढ़ो_data_op(chip, &status, माप(status), true,
					false);
		अगर (ret)
			अवरोध;

		अगर (status & न_अंकD_STATUS_READY)
			अवरोध;

		/*
		 * Typical lowest execution समय क्रम a tR on most न_अंकDs is 10us,
		 * use this as polling delay beक्रमe करोing something smarter (ie.
		 * deriving a delay from the समयout value, समयout_ms/ratio).
		 */
		udelay(10);
	पूर्ण जबतक	(समय_beक्रमe(jअगरfies, समयout_ms));

	/*
	 * We have to निकास READ_STATUS mode in order to पढ़ो real data on the
	 * bus in हाल the WAITRDY inकाष्ठाion is preceding a DATA_IN
	 * inकाष्ठाion.
	 */
	nand_निकास_status_op(chip);

	अगर (ret)
		वापस ret;

	वापस status & न_अंकD_STATUS_READY ? 0 : -ETIMEDOUT;
पूर्ण;
EXPORT_SYMBOL_GPL(nand_soft_रुकोrdy);

/**
 * nand_gpio_रुकोrdy - Poll R/B GPIO pin until पढ़ोy
 * @chip: न_अंकD chip काष्ठाure
 * @gpiod: GPIO descriptor of R/B pin
 * @समयout_ms: Timeout in ms
 *
 * Poll the R/B GPIO pin until it becomes पढ़ोy. If that करोes not happen
 * whitin the specअगरied समयout, -ETIMEDOUT is वापसed.
 *
 * This helper is पूर्णांकended to be used when the controller has access to the
 * न_अंकD R/B pin over GPIO.
 *
 * Return 0 अगर the R/B pin indicates chip is पढ़ोy, a negative error otherwise.
 */
पूर्णांक nand_gpio_रुकोrdy(काष्ठा nand_chip *chip, काष्ठा gpio_desc *gpiod,
		      अचिन्हित दीर्घ समयout_ms)
अणु

	/*
	 * Wait until R/B pin indicates chip is पढ़ोy or समयout occurs.
	 * +1 below is necessary because अगर we are now in the last fraction
	 * of jअगरfy and msecs_to_jअगरfies is 1 then we will रुको only that
	 * small jअगरfy fraction - possibly leading to false समयout.
	 */
	समयout_ms = jअगरfies + msecs_to_jअगरfies(समयout_ms) + 1;
	करो अणु
		अगर (gpiod_get_value_cansleep(gpiod))
			वापस 0;

		cond_resched();
	पूर्ण जबतक	(समय_beक्रमe(jअगरfies, समयout_ms));

	वापस gpiod_get_value_cansleep(gpiod) ? 0 : -ETIMEDOUT;
पूर्ण;
EXPORT_SYMBOL_GPL(nand_gpio_रुकोrdy);

/**
 * panic_nand_रुको - [GENERIC] रुको until the command is करोne
 * @chip: न_अंकD chip काष्ठाure
 * @समयo: समयout
 *
 * Wait क्रम command करोne. This is a helper function क्रम nand_रुको used when
 * we are in पूर्णांकerrupt context. May happen when in panic and trying to ग_लिखो
 * an oops through mtकरोops.
 */
व्योम panic_nand_रुको(काष्ठा nand_chip *chip, अचिन्हित दीर्घ समयo)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < समयo; i++) अणु
		अगर (chip->legacy.dev_पढ़ोy) अणु
			अगर (chip->legacy.dev_पढ़ोy(chip))
				अवरोध;
		पूर्ण अन्यथा अणु
			पूर्णांक ret;
			u8 status;

			ret = nand_पढ़ो_data_op(chip, &status, माप(status),
						true, false);
			अगर (ret)
				वापस;

			अगर (status & न_अंकD_STATUS_READY)
				अवरोध;
		पूर्ण
		mdelay(1);
	पूर्ण
पूर्ण

अटल bool nand_supports_get_features(काष्ठा nand_chip *chip, पूर्णांक addr)
अणु
	वापस (chip->parameters.supports_set_get_features &&
		test_bit(addr, chip->parameters.get_feature_list));
पूर्ण

अटल bool nand_supports_set_features(काष्ठा nand_chip *chip, पूर्णांक addr)
अणु
	वापस (chip->parameters.supports_set_get_features &&
		test_bit(addr, chip->parameters.set_feature_list));
पूर्ण

/**
 * nand_reset_पूर्णांकerface - Reset data पूर्णांकerface and timings
 * @chip: The न_अंकD chip
 * @chipnr: Internal die id
 *
 * Reset the Data पूर्णांकerface and timings to ONFI mode 0.
 *
 * Returns 0 क्रम success or negative error code otherwise.
 */
अटल पूर्णांक nand_reset_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr)
अणु
	स्थिर काष्ठा nand_controller_ops *ops = chip->controller->ops;
	पूर्णांक ret;

	अगर (!nand_controller_can_setup_पूर्णांकerface(chip))
		वापस 0;

	/*
	 * The ONFI specअगरication says:
	 * "
	 * To transition from NV-DDR or NV-DDR2 to the SDR data
	 * पूर्णांकerface, the host shall use the Reset (FFh) command
	 * using SDR timing mode 0. A device in any timing mode is
	 * required to recognize Reset (FFh) command issued in SDR
	 * timing mode 0.
	 * "
	 *
	 * Configure the data पूर्णांकerface in SDR mode and set the
	 * timings to timing mode 0.
	 */

	chip->current_पूर्णांकerface_config = nand_get_reset_पूर्णांकerface_config();
	ret = ops->setup_पूर्णांकerface(chip, chipnr,
				   chip->current_पूर्णांकerface_config);
	अगर (ret)
		pr_err("Failed to configure data interface to SDR timing mode 0\n");

	वापस ret;
पूर्ण

/**
 * nand_setup_पूर्णांकerface - Setup the best data पूर्णांकerface and timings
 * @chip: The न_अंकD chip
 * @chipnr: Internal die id
 *
 * Configure what has been reported to be the best data पूर्णांकerface and न_अंकD
 * timings supported by the chip and the driver.
 *
 * Returns 0 क्रम success or negative error code otherwise.
 */
अटल पूर्णांक nand_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr)
अणु
	स्थिर काष्ठा nand_controller_ops *ops = chip->controller->ops;
	u8 पंचांगode_param[ONFI_SUBFEATURE_PARAM_LEN] = अणु पूर्ण;
	पूर्णांक ret;

	अगर (!nand_controller_can_setup_पूर्णांकerface(chip))
		वापस 0;

	/*
	 * A nand_reset_पूर्णांकerface() put both the न_अंकD chip and the न_अंकD
	 * controller in timings mode 0. If the शेष mode क्रम this chip is
	 * also 0, no need to proceed to the change again. Plus, at probe समय,
	 * nand_setup_पूर्णांकerface() uses ->set/get_features() which would
	 * fail anyway as the parameter page is not available yet.
	 */
	अगर (!chip->best_पूर्णांकerface_config)
		वापस 0;

	पंचांगode_param[0] = chip->best_पूर्णांकerface_config->timings.mode;

	/* Change the mode on the chip side (अगर supported by the न_अंकD chip) */
	अगर (nand_supports_set_features(chip, ONFI_FEATURE_ADDR_TIMING_MODE)) अणु
		nand_select_target(chip, chipnr);
		ret = nand_set_features(chip, ONFI_FEATURE_ADDR_TIMING_MODE,
					पंचांगode_param);
		nand_deselect_target(chip);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Change the mode on the controller side */
	ret = ops->setup_पूर्णांकerface(chip, chipnr, chip->best_पूर्णांकerface_config);
	अगर (ret)
		वापस ret;

	/* Check the mode has been accepted by the chip, अगर supported */
	अगर (!nand_supports_get_features(chip, ONFI_FEATURE_ADDR_TIMING_MODE))
		जाओ update_पूर्णांकerface_config;

	स_रखो(पंचांगode_param, 0, ONFI_SUBFEATURE_PARAM_LEN);
	nand_select_target(chip, chipnr);
	ret = nand_get_features(chip, ONFI_FEATURE_ADDR_TIMING_MODE,
				पंचांगode_param);
	nand_deselect_target(chip);
	अगर (ret)
		जाओ err_reset_chip;

	अगर (पंचांगode_param[0] != chip->best_पूर्णांकerface_config->timings.mode) अणु
		pr_warn("timing mode %d not acknowledged by the NAND chip\n",
			chip->best_पूर्णांकerface_config->timings.mode);
		जाओ err_reset_chip;
	पूर्ण

update_पूर्णांकerface_config:
	chip->current_पूर्णांकerface_config = chip->best_पूर्णांकerface_config;

	वापस 0;

err_reset_chip:
	/*
	 * Fallback to mode 0 अगर the chip explicitly did not ack the chosen
	 * timing mode.
	 */
	nand_reset_पूर्णांकerface(chip, chipnr);
	nand_select_target(chip, chipnr);
	nand_reset_op(chip);
	nand_deselect_target(chip);

	वापस ret;
पूर्ण

/**
 * nand_choose_best_sdr_timings - Pick up the best SDR timings that both the
 *                                न_अंकD controller and the न_अंकD chip support
 * @chip: the न_अंकD chip
 * @अगरace: the पूर्णांकerface configuration (can eventually be updated)
 * @spec_timings: specअगरic timings, when not fitting the ONFI specअगरication
 *
 * If specअगरic timings are provided, use them. Otherwise, retrieve supported
 * timing modes from ONFI inक्रमmation.
 */
पूर्णांक nand_choose_best_sdr_timings(काष्ठा nand_chip *chip,
				 काष्ठा nand_पूर्णांकerface_config *अगरace,
				 काष्ठा nand_sdr_timings *spec_timings)
अणु
	स्थिर काष्ठा nand_controller_ops *ops = chip->controller->ops;
	पूर्णांक best_mode = 0, mode, ret;

	अगरace->type = न_अंकD_SDR_IFACE;

	अगर (spec_timings) अणु
		अगरace->timings.sdr = *spec_timings;
		अगरace->timings.mode = onfi_find_बंदst_sdr_mode(spec_timings);

		/* Verअगरy the controller supports the requested पूर्णांकerface */
		ret = ops->setup_पूर्णांकerface(chip, न_अंकD_DATA_IFACE_CHECK_ONLY,
					   अगरace);
		अगर (!ret) अणु
			chip->best_पूर्णांकerface_config = अगरace;
			वापस ret;
		पूर्ण

		/* Fallback to slower modes */
		best_mode = अगरace->timings.mode;
	पूर्ण अन्यथा अगर (chip->parameters.onfi) अणु
		best_mode = fls(chip->parameters.onfi->async_timing_mode) - 1;
	पूर्ण

	क्रम (mode = best_mode; mode >= 0; mode--) अणु
		onfi_fill_पूर्णांकerface_config(chip, अगरace, न_अंकD_SDR_IFACE, mode);

		ret = ops->setup_पूर्णांकerface(chip, न_अंकD_DATA_IFACE_CHECK_ONLY,
					   अगरace);
		अगर (!ret)
			अवरोध;
	पूर्ण

	chip->best_पूर्णांकerface_config = अगरace;

	वापस 0;
पूर्ण

/**
 * nand_choose_पूर्णांकerface_config - find the best data पूर्णांकerface and timings
 * @chip: The न_अंकD chip
 *
 * Find the best data पूर्णांकerface and न_अंकD timings supported by the chip
 * and the driver. Eventually let the न_अंकD manufacturer driver propose his own
 * set of timings.
 *
 * After this function nand_chip->पूर्णांकerface_config is initialized with the best
 * timing mode available.
 *
 * Returns 0 क्रम success or negative error code otherwise.
 */
अटल पूर्णांक nand_choose_पूर्णांकerface_config(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_पूर्णांकerface_config *अगरace;
	पूर्णांक ret;

	अगर (!nand_controller_can_setup_पूर्णांकerface(chip))
		वापस 0;

	अगरace = kzalloc(माप(*अगरace), GFP_KERNEL);
	अगर (!अगरace)
		वापस -ENOMEM;

	अगर (chip->ops.choose_पूर्णांकerface_config)
		ret = chip->ops.choose_पूर्णांकerface_config(chip, अगरace);
	अन्यथा
		ret = nand_choose_best_sdr_timings(chip, अगरace, शून्य);

	अगर (ret)
		kमुक्त(अगरace);

	वापस ret;
पूर्ण

/**
 * nand_fill_column_cycles - fill the column cycles of an address
 * @chip: The न_अंकD chip
 * @addrs: Array of address cycles to fill
 * @offset_in_page: The offset in the page
 *
 * Fills the first or the first two bytes of the @addrs field depending
 * on the न_अंकD bus width and the page size.
 *
 * Returns the number of cycles needed to encode the column, or a negative
 * error code in हाल one of the arguments is invalid.
 */
अटल पूर्णांक nand_fill_column_cycles(काष्ठा nand_chip *chip, u8 *addrs,
				   अचिन्हित पूर्णांक offset_in_page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/* Make sure the offset is less than the actual page size. */
	अगर (offset_in_page > mtd->ग_लिखोsize + mtd->oobsize)
		वापस -EINVAL;

	/*
	 * On small page न_अंकDs, there's a dedicated command to access the OOB
	 * area, and the column address is relative to the start of the OOB
	 * area, not the start of the page. Asjust the address accordingly.
	 */
	अगर (mtd->ग_लिखोsize <= 512 && offset_in_page >= mtd->ग_लिखोsize)
		offset_in_page -= mtd->ग_लिखोsize;

	/*
	 * The offset in page is expressed in bytes, अगर the न_अंकD bus is 16-bit
	 * wide, then it must be भागided by 2.
	 */
	अगर (chip->options & न_अंकD_BUSWIDTH_16) अणु
		अगर (WARN_ON(offset_in_page % 2))
			वापस -EINVAL;

		offset_in_page /= 2;
	पूर्ण

	addrs[0] = offset_in_page;

	/*
	 * Small page न_अंकDs use 1 cycle क्रम the columns, जबतक large page न_अंकDs
	 * need 2
	 */
	अगर (mtd->ग_लिखोsize <= 512)
		वापस 1;

	addrs[1] = offset_in_page >> 8;

	वापस 2;
पूर्ण

अटल पूर्णांक nand_sp_exec_पढ़ो_page_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
				     अचिन्हित पूर्णांक offset_in_page, व्योम *buf,
				     अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr =
		nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 addrs[4];
	काष्ठा nand_op_instr instrs[] = अणु
		न_अंकD_OP_CMD(न_अंकD_CMD_READ0, 0),
		न_अंकD_OP_ADDR(3, addrs, PSEC_TO_NSEC(sdr->tWB_max)),
		न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tR_max),
				 PSEC_TO_NSEC(sdr->tRR_min)),
		न_अंकD_OP_DATA_IN(len, buf, 0),
	पूर्ण;
	काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);
	पूर्णांक ret;

	/* Drop the DATA_IN inकाष्ठाion अगर len is set to 0. */
	अगर (!len)
		op.ninstrs--;

	अगर (offset_in_page >= mtd->ग_लिखोsize)
		instrs[0].ctx.cmd.opcode = न_अंकD_CMD_READOOB;
	अन्यथा अगर (offset_in_page >= 256 &&
		 !(chip->options & न_अंकD_BUSWIDTH_16))
		instrs[0].ctx.cmd.opcode = न_अंकD_CMD_READ1;

	ret = nand_fill_column_cycles(chip, addrs, offset_in_page);
	अगर (ret < 0)
		वापस ret;

	addrs[1] = page;
	addrs[2] = page >> 8;

	अगर (chip->options & न_अंकD_ROW_ADDR_3) अणु
		addrs[3] = page >> 16;
		instrs[1].ctx.addr.naddrs++;
	पूर्ण

	वापस nand_exec_op(chip, &op);
पूर्ण

अटल पूर्णांक nand_lp_exec_पढ़ो_page_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
				     अचिन्हित पूर्णांक offset_in_page, व्योम *buf,
				     अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr =
		nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
	u8 addrs[5];
	काष्ठा nand_op_instr instrs[] = अणु
		न_अंकD_OP_CMD(न_अंकD_CMD_READ0, 0),
		न_अंकD_OP_ADDR(4, addrs, 0),
		न_अंकD_OP_CMD(न_अंकD_CMD_READSTART, PSEC_TO_NSEC(sdr->tWB_max)),
		न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tR_max),
				 PSEC_TO_NSEC(sdr->tRR_min)),
		न_अंकD_OP_DATA_IN(len, buf, 0),
	पूर्ण;
	काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);
	पूर्णांक ret;

	/* Drop the DATA_IN inकाष्ठाion अगर len is set to 0. */
	अगर (!len)
		op.ninstrs--;

	ret = nand_fill_column_cycles(chip, addrs, offset_in_page);
	अगर (ret < 0)
		वापस ret;

	addrs[2] = page;
	addrs[3] = page >> 8;

	अगर (chip->options & न_अंकD_ROW_ADDR_3) अणु
		addrs[4] = page >> 16;
		instrs[1].ctx.addr.naddrs++;
	पूर्ण

	वापस nand_exec_op(chip, &op);
पूर्ण

/**
 * nand_पढ़ो_page_op - Do a READ PAGE operation
 * @chip: The न_अंकD chip
 * @page: page to पढ़ो
 * @offset_in_page: offset within the page
 * @buf: buffer used to store the data
 * @len: length of the buffer
 *
 * This function issues a READ PAGE operation.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_पढ़ो_page_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
		      अचिन्हित पूर्णांक offset_in_page, व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (len && !buf)
		वापस -EINVAL;

	अगर (offset_in_page + len > mtd->ग_लिखोsize + mtd->oobsize)
		वापस -EINVAL;

	अगर (nand_has_exec_op(chip)) अणु
		अगर (mtd->ग_लिखोsize > 512)
			वापस nand_lp_exec_पढ़ो_page_op(chip, page,
							 offset_in_page, buf,
							 len);

		वापस nand_sp_exec_पढ़ो_page_op(chip, page, offset_in_page,
						 buf, len);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_READ0, offset_in_page, page);
	अगर (len)
		chip->legacy.पढ़ो_buf(chip, buf, len);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_पढ़ो_page_op);

/**
 * nand_पढ़ो_param_page_op - Do a READ PARAMETER PAGE operation
 * @chip: The न_अंकD chip
 * @page: parameter page to पढ़ो
 * @buf: buffer used to store the data
 * @len: length of the buffer
 *
 * This function issues a READ PARAMETER PAGE operation.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_पढ़ो_param_page_op(काष्ठा nand_chip *chip, u8 page, व्योम *buf,
			    अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;
	u8 *p = buf;

	अगर (len && !buf)
		वापस -EINVAL;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_PARAM, 0),
			न_अंकD_OP_ADDR(1, &page, PSEC_TO_NSEC(sdr->tWB_max)),
			न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tR_max),
					 PSEC_TO_NSEC(sdr->tRR_min)),
			न_अंकD_OP_8BIT_DATA_IN(len, buf, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		/* Drop the DATA_IN inकाष्ठाion अगर len is set to 0. */
		अगर (!len)
			op.ninstrs--;

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_PARAM, page, -1);
	क्रम (i = 0; i < len; i++)
		p[i] = chip->legacy.पढ़ो_byte(chip);

	वापस 0;
पूर्ण

/**
 * nand_change_पढ़ो_column_op - Do a CHANGE READ COLUMN operation
 * @chip: The न_अंकD chip
 * @offset_in_page: offset within the page
 * @buf: buffer used to store the data
 * @len: length of the buffer
 * @क्रमce_8bit: क्रमce 8-bit bus access
 *
 * This function issues a CHANGE READ COLUMN operation.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_change_पढ़ो_column_op(काष्ठा nand_chip *chip,
			       अचिन्हित पूर्णांक offset_in_page, व्योम *buf,
			       अचिन्हित पूर्णांक len, bool क्रमce_8bit)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (len && !buf)
		वापस -EINVAL;

	अगर (offset_in_page + len > mtd->ग_लिखोsize + mtd->oobsize)
		वापस -EINVAL;

	/* Small page न_अंकDs करो not support column change. */
	अगर (mtd->ग_लिखोsize <= 512)
		वापस -ENOTSUPP;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		u8 addrs[2] = अणुपूर्ण;
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_RNDOUT, 0),
			न_अंकD_OP_ADDR(2, addrs, 0),
			न_अंकD_OP_CMD(न_अंकD_CMD_RNDOUTSTART,
				    PSEC_TO_NSEC(sdr->tCCS_min)),
			न_अंकD_OP_DATA_IN(len, buf, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);
		पूर्णांक ret;

		ret = nand_fill_column_cycles(chip, addrs, offset_in_page);
		अगर (ret < 0)
			वापस ret;

		/* Drop the DATA_IN inकाष्ठाion अगर len is set to 0. */
		अगर (!len)
			op.ninstrs--;

		instrs[3].ctx.data.क्रमce_8bit = क्रमce_8bit;

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_RNDOUT, offset_in_page, -1);
	अगर (len)
		chip->legacy.पढ़ो_buf(chip, buf, len);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_change_पढ़ो_column_op);

/**
 * nand_पढ़ो_oob_op - Do a READ OOB operation
 * @chip: The न_अंकD chip
 * @page: page to पढ़ो
 * @offset_in_oob: offset within the OOB area
 * @buf: buffer used to store the data
 * @len: length of the buffer
 *
 * This function issues a READ OOB operation.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_पढ़ो_oob_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
		     अचिन्हित पूर्णांक offset_in_oob, व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (len && !buf)
		वापस -EINVAL;

	अगर (offset_in_oob + len > mtd->oobsize)
		वापस -EINVAL;

	अगर (nand_has_exec_op(chip))
		वापस nand_पढ़ो_page_op(chip, page,
					 mtd->ग_लिखोsize + offset_in_oob,
					 buf, len);

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_READOOB, offset_in_oob, page);
	अगर (len)
		chip->legacy.पढ़ो_buf(chip, buf, len);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_पढ़ो_oob_op);

अटल पूर्णांक nand_exec_prog_page_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
				  अचिन्हित पूर्णांक offset_in_page, स्थिर व्योम *buf,
				  अचिन्हित पूर्णांक len, bool prog)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr =
		nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 addrs[5] = अणुपूर्ण;
	काष्ठा nand_op_instr instrs[] = अणु
		/*
		 * The first inकाष्ठाion will be dropped अगर we're dealing
		 * with a large page न_अंकD and adjusted अगर we're dealing
		 * with a small page न_अंकD and the page offset is > 255.
		 */
		न_अंकD_OP_CMD(न_अंकD_CMD_READ0, 0),
		न_अंकD_OP_CMD(न_अंकD_CMD_SEQIN, 0),
		न_अंकD_OP_ADDR(0, addrs, PSEC_TO_NSEC(sdr->tADL_min)),
		न_अंकD_OP_DATA_OUT(len, buf, 0),
		न_अंकD_OP_CMD(न_अंकD_CMD_PAGEPROG, PSEC_TO_NSEC(sdr->tWB_max)),
		न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tPROG_max), 0),
	पूर्ण;
	काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);
	पूर्णांक naddrs = nand_fill_column_cycles(chip, addrs, offset_in_page);

	अगर (naddrs < 0)
		वापस naddrs;

	addrs[naddrs++] = page;
	addrs[naddrs++] = page >> 8;
	अगर (chip->options & न_अंकD_ROW_ADDR_3)
		addrs[naddrs++] = page >> 16;

	instrs[2].ctx.addr.naddrs = naddrs;

	/* Drop the last two inकाष्ठाions अगर we're not programming the page. */
	अगर (!prog) अणु
		op.ninstrs -= 2;
		/* Also drop the DATA_OUT inकाष्ठाion अगर empty. */
		अगर (!len)
			op.ninstrs--;
	पूर्ण

	अगर (mtd->ग_लिखोsize <= 512) अणु
		/*
		 * Small pages need some more tweaking: we have to adjust the
		 * first inकाष्ठाion depending on the page offset we're trying
		 * to access.
		 */
		अगर (offset_in_page >= mtd->ग_लिखोsize)
			instrs[0].ctx.cmd.opcode = न_अंकD_CMD_READOOB;
		अन्यथा अगर (offset_in_page >= 256 &&
			 !(chip->options & न_अंकD_BUSWIDTH_16))
			instrs[0].ctx.cmd.opcode = न_अंकD_CMD_READ1;
	पूर्ण अन्यथा अणु
		/*
		 * Drop the first command अगर we're dealing with a large page
		 * न_अंकD.
		 */
		op.instrs++;
		op.ninstrs--;
	पूर्ण

	वापस nand_exec_op(chip, &op);
पूर्ण

/**
 * nand_prog_page_begin_op - starts a PROG PAGE operation
 * @chip: The न_अंकD chip
 * @page: page to ग_लिखो
 * @offset_in_page: offset within the page
 * @buf: buffer containing the data to ग_लिखो to the page
 * @len: length of the buffer
 *
 * This function issues the first half of a PROG PAGE operation.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_prog_page_begin_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
			    अचिन्हित पूर्णांक offset_in_page, स्थिर व्योम *buf,
			    अचिन्हित पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (len && !buf)
		वापस -EINVAL;

	अगर (offset_in_page + len > mtd->ग_लिखोsize + mtd->oobsize)
		वापस -EINVAL;

	अगर (nand_has_exec_op(chip))
		वापस nand_exec_prog_page_op(chip, page, offset_in_page, buf,
					      len, false);

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_SEQIN, offset_in_page, page);

	अगर (buf)
		chip->legacy.ग_लिखो_buf(chip, buf, len);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_prog_page_begin_op);

/**
 * nand_prog_page_end_op - ends a PROG PAGE operation
 * @chip: The न_अंकD chip
 *
 * This function issues the second half of a PROG PAGE operation.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_prog_page_end_op(काष्ठा nand_chip *chip)
अणु
	पूर्णांक ret;
	u8 status;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_PAGEPROG,
				    PSEC_TO_NSEC(sdr->tWB_max)),
			न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tPROG_max), 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		ret = nand_exec_op(chip, &op);
		अगर (ret)
			वापस ret;

		ret = nand_status_op(chip, &status);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		chip->legacy.cmdfunc(chip, न_अंकD_CMD_PAGEPROG, -1, -1);
		ret = chip->legacy.रुकोfunc(chip);
		अगर (ret < 0)
			वापस ret;

		status = ret;
	पूर्ण

	अगर (status & न_अंकD_STATUS_FAIL)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_prog_page_end_op);

/**
 * nand_prog_page_op - Do a full PROG PAGE operation
 * @chip: The न_अंकD chip
 * @page: page to ग_लिखो
 * @offset_in_page: offset within the page
 * @buf: buffer containing the data to ग_लिखो to the page
 * @len: length of the buffer
 *
 * This function issues a full PROG PAGE operation.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_prog_page_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
		      अचिन्हित पूर्णांक offset_in_page, स्थिर व्योम *buf,
		      अचिन्हित पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 status;
	पूर्णांक ret;

	अगर (!len || !buf)
		वापस -EINVAL;

	अगर (offset_in_page + len > mtd->ग_लिखोsize + mtd->oobsize)
		वापस -EINVAL;

	अगर (nand_has_exec_op(chip)) अणु
		ret = nand_exec_prog_page_op(chip, page, offset_in_page, buf,
						len, true);
		अगर (ret)
			वापस ret;

		ret = nand_status_op(chip, &status);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		chip->legacy.cmdfunc(chip, न_अंकD_CMD_SEQIN, offset_in_page,
				     page);
		chip->legacy.ग_लिखो_buf(chip, buf, len);
		chip->legacy.cmdfunc(chip, न_अंकD_CMD_PAGEPROG, -1, -1);
		ret = chip->legacy.रुकोfunc(chip);
		अगर (ret < 0)
			वापस ret;

		status = ret;
	पूर्ण

	अगर (status & न_अंकD_STATUS_FAIL)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_prog_page_op);

/**
 * nand_change_ग_लिखो_column_op - Do a CHANGE WRITE COLUMN operation
 * @chip: The न_अंकD chip
 * @offset_in_page: offset within the page
 * @buf: buffer containing the data to send to the न_अंकD
 * @len: length of the buffer
 * @क्रमce_8bit: क्रमce 8-bit bus access
 *
 * This function issues a CHANGE WRITE COLUMN operation.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_change_ग_लिखो_column_op(काष्ठा nand_chip *chip,
				अचिन्हित पूर्णांक offset_in_page,
				स्थिर व्योम *buf, अचिन्हित पूर्णांक len,
				bool क्रमce_8bit)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (len && !buf)
		वापस -EINVAL;

	अगर (offset_in_page + len > mtd->ग_लिखोsize + mtd->oobsize)
		वापस -EINVAL;

	/* Small page न_अंकDs करो not support column change. */
	अगर (mtd->ग_लिखोsize <= 512)
		वापस -ENOTSUPP;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		u8 addrs[2];
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_RNDIN, 0),
			न_अंकD_OP_ADDR(2, addrs, PSEC_TO_NSEC(sdr->tCCS_min)),
			न_अंकD_OP_DATA_OUT(len, buf, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);
		पूर्णांक ret;

		ret = nand_fill_column_cycles(chip, addrs, offset_in_page);
		अगर (ret < 0)
			वापस ret;

		instrs[2].ctx.data.क्रमce_8bit = क्रमce_8bit;

		/* Drop the DATA_OUT inकाष्ठाion अगर len is set to 0. */
		अगर (!len)
			op.ninstrs--;

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_RNDIN, offset_in_page, -1);
	अगर (len)
		chip->legacy.ग_लिखो_buf(chip, buf, len);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_change_ग_लिखो_column_op);

/**
 * nand_पढ़ोid_op - Do a READID operation
 * @chip: The न_अंकD chip
 * @addr: address cycle to pass after the READID command
 * @buf: buffer used to store the ID
 * @len: length of the buffer
 *
 * This function sends a READID command and पढ़ोs back the ID वापसed by the
 * न_अंकD.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_पढ़ोid_op(काष्ठा nand_chip *chip, u8 addr, व्योम *buf,
		   अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;
	u8 *id = buf;

	अगर (len && !buf)
		वापस -EINVAL;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_READID, 0),
			न_अंकD_OP_ADDR(1, &addr, PSEC_TO_NSEC(sdr->tADL_min)),
			न_अंकD_OP_8BIT_DATA_IN(len, buf, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		/* Drop the DATA_IN inकाष्ठाion अगर len is set to 0. */
		अगर (!len)
			op.ninstrs--;

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_READID, addr, -1);

	क्रम (i = 0; i < len; i++)
		id[i] = chip->legacy.पढ़ो_byte(chip);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_पढ़ोid_op);

/**
 * nand_status_op - Do a STATUS operation
 * @chip: The न_अंकD chip
 * @status: out variable to store the न_अंकD status
 *
 * This function sends a STATUS command and पढ़ोs back the status वापसed by
 * the न_अंकD.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_status_op(काष्ठा nand_chip *chip, u8 *status)
अणु
	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_STATUS,
				    PSEC_TO_NSEC(sdr->tADL_min)),
			न_अंकD_OP_8BIT_DATA_IN(1, status, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		अगर (!status)
			op.ninstrs--;

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_STATUS, -1, -1);
	अगर (status)
		*status = chip->legacy.पढ़ो_byte(chip);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_status_op);

/**
 * nand_निकास_status_op - Exit a STATUS operation
 * @chip: The न_अंकD chip
 *
 * This function sends a READ0 command to cancel the effect of the STATUS
 * command to aव्योम पढ़ोing only the status until a new पढ़ो command is sent.
 *
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_निकास_status_op(काष्ठा nand_chip *chip)
अणु
	अगर (nand_has_exec_op(chip)) अणु
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_READ0, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_READ0, -1, -1);

	वापस 0;
पूर्ण

/**
 * nand_erase_op - Do an erase operation
 * @chip: The न_अंकD chip
 * @eraseblock: block to erase
 *
 * This function sends an ERASE command and रुकोs क्रम the न_अंकD to be पढ़ोy
 * beक्रमe वापसing.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_erase_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक eraseblock)
अणु
	अचिन्हित पूर्णांक page = eraseblock <<
			    (chip->phys_erase_shअगरt - chip->page_shअगरt);
	पूर्णांक ret;
	u8 status;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		u8 addrs[3] = अणु	page, page >> 8, page >> 16 पूर्ण;
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_ERASE1, 0),
			न_अंकD_OP_ADDR(2, addrs, 0),
			न_अंकD_OP_CMD(न_अंकD_CMD_ERASE2,
				    PSEC_TO_MSEC(sdr->tWB_max)),
			न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tBERS_max), 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		अगर (chip->options & न_अंकD_ROW_ADDR_3)
			instrs[1].ctx.addr.naddrs++;

		ret = nand_exec_op(chip, &op);
		अगर (ret)
			वापस ret;

		ret = nand_status_op(chip, &status);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		chip->legacy.cmdfunc(chip, न_अंकD_CMD_ERASE1, -1, page);
		chip->legacy.cmdfunc(chip, न_अंकD_CMD_ERASE2, -1, -1);

		ret = chip->legacy.रुकोfunc(chip);
		अगर (ret < 0)
			वापस ret;

		status = ret;
	पूर्ण

	अगर (status & न_अंकD_STATUS_FAIL)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_erase_op);

/**
 * nand_set_features_op - Do a SET FEATURES operation
 * @chip: The न_अंकD chip
 * @feature: feature id
 * @data: 4 bytes of data
 *
 * This function sends a SET FEATURES command and रुकोs क्रम the न_अंकD to be
 * पढ़ोy beक्रमe वापसing.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
अटल पूर्णांक nand_set_features_op(काष्ठा nand_chip *chip, u8 feature,
				स्थिर व्योम *data)
अणु
	स्थिर u8 *params = data;
	पूर्णांक i, ret;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_SET_FEATURES, 0),
			न_अंकD_OP_ADDR(1, &feature, PSEC_TO_NSEC(sdr->tADL_min)),
			न_अंकD_OP_8BIT_DATA_OUT(ONFI_SUBFEATURE_PARAM_LEN, data,
					      PSEC_TO_NSEC(sdr->tWB_max)),
			न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tFEAT_max), 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_SET_FEATURES, feature, -1);
	क्रम (i = 0; i < ONFI_SUBFEATURE_PARAM_LEN; ++i)
		chip->legacy.ग_लिखो_byte(chip, params[i]);

	ret = chip->legacy.रुकोfunc(chip);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & न_अंकD_STATUS_FAIL)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * nand_get_features_op - Do a GET FEATURES operation
 * @chip: The न_अंकD chip
 * @feature: feature id
 * @data: 4 bytes of data
 *
 * This function sends a GET FEATURES command and रुकोs क्रम the न_अंकD to be
 * पढ़ोy beक्रमe वापसing.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
अटल पूर्णांक nand_get_features_op(काष्ठा nand_chip *chip, u8 feature,
				व्योम *data)
अणु
	u8 *params = data;
	पूर्णांक i;

	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_GET_FEATURES, 0),
			न_अंकD_OP_ADDR(1, &feature, PSEC_TO_NSEC(sdr->tWB_max)),
			न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tFEAT_max),
					 PSEC_TO_NSEC(sdr->tRR_min)),
			न_अंकD_OP_8BIT_DATA_IN(ONFI_SUBFEATURE_PARAM_LEN,
					     data, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_GET_FEATURES, feature, -1);
	क्रम (i = 0; i < ONFI_SUBFEATURE_PARAM_LEN; ++i)
		params[i] = chip->legacy.पढ़ो_byte(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक nand_रुको_rdy_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक समयout_ms,
			    अचिन्हित पूर्णांक delay_ns)
अणु
	अगर (nand_has_exec_op(chip)) अणु
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(समयout_ms),
					 PSEC_TO_NSEC(delay_ns)),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	/* Apply delay or रुको क्रम पढ़ोy/busy pin */
	अगर (!chip->legacy.dev_पढ़ोy)
		udelay(chip->legacy.chip_delay);
	अन्यथा
		nand_रुको_पढ़ोy(chip);

	वापस 0;
पूर्ण

/**
 * nand_reset_op - Do a reset operation
 * @chip: The न_अंकD chip
 *
 * This function sends a RESET command and रुकोs क्रम the न_अंकD to be पढ़ोy
 * beक्रमe वापसing.
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_reset_op(काष्ठा nand_chip *chip)
अणु
	अगर (nand_has_exec_op(chip)) अणु
		स्थिर काष्ठा nand_sdr_timings *sdr =
			nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_CMD(न_अंकD_CMD_RESET, PSEC_TO_NSEC(sdr->tWB_max)),
			न_अंकD_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tRST_max), 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	chip->legacy.cmdfunc(chip, न_अंकD_CMD_RESET, -1, -1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_reset_op);

/**
 * nand_पढ़ो_data_op - Read data from the न_अंकD
 * @chip: The न_अंकD chip
 * @buf: buffer used to store the data
 * @len: length of the buffer
 * @क्रमce_8bit: क्रमce 8-bit bus access
 * @check_only: करो not actually run the command, only checks अगर the
 *              controller driver supports it
 *
 * This function करोes a raw data पढ़ो on the bus. Usually used after launching
 * another न_अंकD operation like nand_पढ़ो_page_op().
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_पढ़ो_data_op(काष्ठा nand_chip *chip, व्योम *buf, अचिन्हित पूर्णांक len,
		      bool क्रमce_8bit, bool check_only)
अणु
	अगर (!len || !buf)
		वापस -EINVAL;

	अगर (nand_has_exec_op(chip)) अणु
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_DATA_IN(len, buf, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		instrs[0].ctx.data.क्रमce_8bit = क्रमce_8bit;

		अगर (check_only)
			वापस nand_check_op(chip, &op);

		वापस nand_exec_op(chip, &op);
	पूर्ण

	अगर (check_only)
		वापस 0;

	अगर (क्रमce_8bit) अणु
		u8 *p = buf;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < len; i++)
			p[i] = chip->legacy.पढ़ो_byte(chip);
	पूर्ण अन्यथा अणु
		chip->legacy.पढ़ो_buf(chip, buf, len);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_पढ़ो_data_op);

/**
 * nand_ग_लिखो_data_op - Write data from the न_अंकD
 * @chip: The न_अंकD chip
 * @buf: buffer containing the data to send on the bus
 * @len: length of the buffer
 * @क्रमce_8bit: क्रमce 8-bit bus access
 *
 * This function करोes a raw data ग_लिखो on the bus. Usually used after launching
 * another न_अंकD operation like nand_ग_लिखो_page_begin_op().
 * This function करोes not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_ग_लिखो_data_op(काष्ठा nand_chip *chip, स्थिर व्योम *buf,
		       अचिन्हित पूर्णांक len, bool क्रमce_8bit)
अणु
	अगर (!len || !buf)
		वापस -EINVAL;

	अगर (nand_has_exec_op(chip)) अणु
		काष्ठा nand_op_instr instrs[] = अणु
			न_अंकD_OP_DATA_OUT(len, buf, 0),
		पूर्ण;
		काष्ठा nand_operation op = न_अंकD_OPERATION(chip->cur_cs, instrs);

		instrs[0].ctx.data.क्रमce_8bit = क्रमce_8bit;

		वापस nand_exec_op(chip, &op);
	पूर्ण

	अगर (क्रमce_8bit) अणु
		स्थिर u8 *p = buf;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < len; i++)
			chip->legacy.ग_लिखो_byte(chip, p[i]);
	पूर्ण अन्यथा अणु
		chip->legacy.ग_लिखो_buf(chip, buf, len);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_ग_लिखो_data_op);

/**
 * काष्ठा nand_op_parser_ctx - Context used by the parser
 * @instrs: array of all the inकाष्ठाions that must be addressed
 * @ninstrs: length of the @instrs array
 * @subop: Sub-operation to be passed to the न_अंकD controller
 *
 * This काष्ठाure is used by the core to split न_अंकD operations पूर्णांकo
 * sub-operations that can be handled by the न_अंकD controller.
 */
काष्ठा nand_op_parser_ctx अणु
	स्थिर काष्ठा nand_op_instr *instrs;
	अचिन्हित पूर्णांक ninstrs;
	काष्ठा nand_subop subop;
पूर्ण;

/**
 * nand_op_parser_must_split_instr - Checks अगर an inकाष्ठाion must be split
 * @pat: the parser pattern element that matches @instr
 * @instr: poपूर्णांकer to the inकाष्ठाion to check
 * @start_offset: this is an in/out parameter. If @instr has alपढ़ोy been
 *		  split, then @start_offset is the offset from which to start
 *		  (either an address cycle or an offset in the data buffer).
 *		  Conversely, अगर the function वापसs true (ie. instr must be
 *		  split), this parameter is updated to poपूर्णांक to the first
 *		  data/address cycle that has not been taken care of.
 *
 * Some न_अंकD controllers are limited and cannot send X address cycles with a
 * unique operation, or cannot पढ़ो/ग_लिखो more than Y bytes at the same समय.
 * In this हाल, split the inकाष्ठाion that करोes not fit in a single
 * controller-operation पूर्णांकo two or more chunks.
 *
 * Returns true अगर the inकाष्ठाion must be split, false otherwise.
 * The @start_offset parameter is also updated to the offset at which the next
 * bundle of inकाष्ठाion must start (अगर an address or a data inकाष्ठाion).
 */
अटल bool
nand_op_parser_must_split_instr(स्थिर काष्ठा nand_op_parser_pattern_elem *pat,
				स्थिर काष्ठा nand_op_instr *instr,
				अचिन्हित पूर्णांक *start_offset)
अणु
	चयन (pat->type) अणु
	हाल न_अंकD_OP_ADDR_INSTR:
		अगर (!pat->ctx.addr.maxcycles)
			अवरोध;

		अगर (instr->ctx.addr.naddrs - *start_offset >
		    pat->ctx.addr.maxcycles) अणु
			*start_offset += pat->ctx.addr.maxcycles;
			वापस true;
		पूर्ण
		अवरोध;

	हाल न_अंकD_OP_DATA_IN_INSTR:
	हाल न_अंकD_OP_DATA_OUT_INSTR:
		अगर (!pat->ctx.data.maxlen)
			अवरोध;

		अगर (instr->ctx.data.len - *start_offset >
		    pat->ctx.data.maxlen) अणु
			*start_offset += pat->ctx.data.maxlen;
			वापस true;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/**
 * nand_op_parser_match_pat - Checks अगर a pattern matches the inकाष्ठाions
 *			      reमुख्यing in the parser context
 * @pat: the pattern to test
 * @ctx: the parser context काष्ठाure to match with the pattern @pat
 *
 * Check अगर @pat matches the set or a sub-set of inकाष्ठाions reमुख्यing in @ctx.
 * Returns true अगर this is the हाल, false ortherwise. When true is वापसed,
 * @ctx->subop is updated with the set of inकाष्ठाions to be passed to the
 * controller driver.
 */
अटल bool
nand_op_parser_match_pat(स्थिर काष्ठा nand_op_parser_pattern *pat,
			 काष्ठा nand_op_parser_ctx *ctx)
अणु
	अचिन्हित पूर्णांक instr_offset = ctx->subop.first_instr_start_off;
	स्थिर काष्ठा nand_op_instr *end = ctx->instrs + ctx->ninstrs;
	स्थिर काष्ठा nand_op_instr *instr = ctx->subop.instrs;
	अचिन्हित पूर्णांक i, ninstrs;

	क्रम (i = 0, ninstrs = 0; i < pat->nelems && instr < end; i++) अणु
		/*
		 * The pattern inकाष्ठाion करोes not match the operation
		 * inकाष्ठाion. If the inकाष्ठाion is marked optional in the
		 * pattern definition, we skip the pattern element and जारी
		 * to the next one. If the element is mandatory, there's no
		 * match and we can वापस false directly.
		 */
		अगर (instr->type != pat->elems[i].type) अणु
			अगर (!pat->elems[i].optional)
				वापस false;

			जारी;
		पूर्ण

		/*
		 * Now check the pattern element स्थिरraपूर्णांकs. If the pattern is
		 * not able to handle the whole inकाष्ठाion in a single step,
		 * we have to split it.
		 * The last_instr_end_off value comes back updated to poपूर्णांक to
		 * the position where we have to split the inकाष्ठाion (the
		 * start of the next subop chunk).
		 */
		अगर (nand_op_parser_must_split_instr(&pat->elems[i], instr,
						    &instr_offset)) अणु
			ninstrs++;
			i++;
			अवरोध;
		पूर्ण

		instr++;
		ninstrs++;
		instr_offset = 0;
	पूर्ण

	/*
	 * This can happen अगर all inकाष्ठाions of a pattern are optional.
	 * Still, अगर there's not at least one inकाष्ठाion handled by this
	 * pattern, this is not a match, and we should try the next one (अगर
	 * any).
	 */
	अगर (!ninstrs)
		वापस false;

	/*
	 * We had a match on the pattern head, but the pattern may be दीर्घer
	 * than the inकाष्ठाions we're asked to execute. We need to make sure
	 * there's no mandatory elements in the pattern tail.
	 */
	क्रम (; i < pat->nelems; i++) अणु
		अगर (!pat->elems[i].optional)
			वापस false;
	पूर्ण

	/*
	 * We have a match: update the subop काष्ठाure accordingly and वापस
	 * true.
	 */
	ctx->subop.ninstrs = ninstrs;
	ctx->subop.last_instr_end_off = instr_offset;

	वापस true;
पूर्ण

#अगर IS_ENABLED(CONFIG_DYNAMIC_DEBUG) || defined(DEBUG)
अटल व्योम nand_op_parser_trace(स्थिर काष्ठा nand_op_parser_ctx *ctx)
अणु
	स्थिर काष्ठा nand_op_instr *instr;
	अक्षर *prefix = "      ";
	अचिन्हित पूर्णांक i;

	pr_debug("executing subop (CS%d):\n", ctx->subop.cs);

	क्रम (i = 0; i < ctx->ninstrs; i++) अणु
		instr = &ctx->instrs[i];

		अगर (instr == &ctx->subop.instrs[0])
			prefix = "    ->";

		nand_op_trace(prefix, instr);

		अगर (instr == &ctx->subop.instrs[ctx->subop.ninstrs - 1])
			prefix = "      ";
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम nand_op_parser_trace(स्थिर काष्ठा nand_op_parser_ctx *ctx)
अणु
	/* NOP */
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nand_op_parser_cmp_ctx(स्थिर काष्ठा nand_op_parser_ctx *a,
				  स्थिर काष्ठा nand_op_parser_ctx *b)
अणु
	अगर (a->subop.ninstrs < b->subop.ninstrs)
		वापस -1;
	अन्यथा अगर (a->subop.ninstrs > b->subop.ninstrs)
		वापस 1;

	अगर (a->subop.last_instr_end_off < b->subop.last_instr_end_off)
		वापस -1;
	अन्यथा अगर (a->subop.last_instr_end_off > b->subop.last_instr_end_off)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * nand_op_parser_exec_op - exec_op parser
 * @chip: the न_अंकD chip
 * @parser: patterns description provided by the controller driver
 * @op: the न_अंकD operation to address
 * @check_only: when true, the function only checks अगर @op can be handled but
 *		करोes not execute the operation
 *
 * Helper function deचिन्हित to ease पूर्णांकegration of न_अंकD controller drivers that
 * only support a limited set of inकाष्ठाion sequences. The supported sequences
 * are described in @parser, and the framework takes care of splitting @op पूर्णांकo
 * multiple sub-operations (अगर required) and pass them back to the ->exec()
 * callback of the matching pattern अगर @check_only is set to false.
 *
 * न_अंकD controller drivers should call this function from their own ->exec_op()
 * implementation.
 *
 * Returns 0 on success, a negative error code otherwise. A failure can be
 * caused by an unsupported operation (none of the supported patterns is able
 * to handle the requested operation), or an error वापसed by one of the
 * matching pattern->exec() hook.
 */
पूर्णांक nand_op_parser_exec_op(काष्ठा nand_chip *chip,
			   स्थिर काष्ठा nand_op_parser *parser,
			   स्थिर काष्ठा nand_operation *op, bool check_only)
अणु
	काष्ठा nand_op_parser_ctx ctx = अणु
		.subop.cs = op->cs,
		.subop.instrs = op->instrs,
		.instrs = op->instrs,
		.ninstrs = op->ninstrs,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	जबतक (ctx.subop.instrs < op->instrs + op->ninstrs) अणु
		स्थिर काष्ठा nand_op_parser_pattern *pattern;
		काष्ठा nand_op_parser_ctx best_ctx;
		पूर्णांक ret, best_pattern = -1;

		क्रम (i = 0; i < parser->npatterns; i++) अणु
			काष्ठा nand_op_parser_ctx test_ctx = ctx;

			pattern = &parser->patterns[i];
			अगर (!nand_op_parser_match_pat(pattern, &test_ctx))
				जारी;

			अगर (best_pattern >= 0 &&
			    nand_op_parser_cmp_ctx(&test_ctx, &best_ctx) <= 0)
				जारी;

			best_pattern = i;
			best_ctx = test_ctx;
		पूर्ण

		अगर (best_pattern < 0) अणु
			pr_debug("->exec_op() parser: pattern not found!\n");
			वापस -ENOTSUPP;
		पूर्ण

		ctx = best_ctx;
		nand_op_parser_trace(&ctx);

		अगर (!check_only) अणु
			pattern = &parser->patterns[best_pattern];
			ret = pattern->exec(chip, &ctx.subop);
			अगर (ret)
				वापस ret;
		पूर्ण

		/*
		 * Update the context काष्ठाure by poपूर्णांकing to the start of the
		 * next subop.
		 */
		ctx.subop.instrs = ctx.subop.instrs + ctx.subop.ninstrs;
		अगर (ctx.subop.last_instr_end_off)
			ctx.subop.instrs -= 1;

		ctx.subop.first_instr_start_off = ctx.subop.last_instr_end_off;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_op_parser_exec_op);

अटल bool nand_instr_is_data(स्थिर काष्ठा nand_op_instr *instr)
अणु
	वापस instr && (instr->type == न_अंकD_OP_DATA_IN_INSTR ||
			 instr->type == न_अंकD_OP_DATA_OUT_INSTR);
पूर्ण

अटल bool nand_subop_instr_is_valid(स्थिर काष्ठा nand_subop *subop,
				      अचिन्हित पूर्णांक instr_idx)
अणु
	वापस subop && instr_idx < subop->ninstrs;
पूर्ण

अटल अचिन्हित पूर्णांक nand_subop_get_start_off(स्थिर काष्ठा nand_subop *subop,
					     अचिन्हित पूर्णांक instr_idx)
अणु
	अगर (instr_idx)
		वापस 0;

	वापस subop->first_instr_start_off;
पूर्ण

/**
 * nand_subop_get_addr_start_off - Get the start offset in an address array
 * @subop: The entire sub-operation
 * @instr_idx: Index of the inकाष्ठाion inside the sub-operation
 *
 * During driver development, one could be tempted to directly use the
 * ->addr.addrs field of address inकाष्ठाions. This is wrong as address
 * inकाष्ठाions might be split.
 *
 * Given an address inकाष्ठाion, वापसs the offset of the first cycle to issue.
 */
अचिन्हित पूर्णांक nand_subop_get_addr_start_off(स्थिर काष्ठा nand_subop *subop,
					   अचिन्हित पूर्णांक instr_idx)
अणु
	अगर (WARN_ON(!nand_subop_instr_is_valid(subop, instr_idx) ||
		    subop->instrs[instr_idx].type != न_अंकD_OP_ADDR_INSTR))
		वापस 0;

	वापस nand_subop_get_start_off(subop, instr_idx);
पूर्ण
EXPORT_SYMBOL_GPL(nand_subop_get_addr_start_off);

/**
 * nand_subop_get_num_addr_cyc - Get the reमुख्यing address cycles to निश्चित
 * @subop: The entire sub-operation
 * @instr_idx: Index of the inकाष्ठाion inside the sub-operation
 *
 * During driver development, one could be tempted to directly use the
 * ->addr->naddrs field of a data inकाष्ठाion. This is wrong as inकाष्ठाions
 * might be split.
 *
 * Given an address inकाष्ठाion, वापसs the number of address cycle to issue.
 */
अचिन्हित पूर्णांक nand_subop_get_num_addr_cyc(स्थिर काष्ठा nand_subop *subop,
					 अचिन्हित पूर्णांक instr_idx)
अणु
	पूर्णांक start_off, end_off;

	अगर (WARN_ON(!nand_subop_instr_is_valid(subop, instr_idx) ||
		    subop->instrs[instr_idx].type != न_अंकD_OP_ADDR_INSTR))
		वापस 0;

	start_off = nand_subop_get_addr_start_off(subop, instr_idx);

	अगर (instr_idx == subop->ninstrs - 1 &&
	    subop->last_instr_end_off)
		end_off = subop->last_instr_end_off;
	अन्यथा
		end_off = subop->instrs[instr_idx].ctx.addr.naddrs;

	वापस end_off - start_off;
पूर्ण
EXPORT_SYMBOL_GPL(nand_subop_get_num_addr_cyc);

/**
 * nand_subop_get_data_start_off - Get the start offset in a data array
 * @subop: The entire sub-operation
 * @instr_idx: Index of the inकाष्ठाion inside the sub-operation
 *
 * During driver development, one could be tempted to directly use the
 * ->data->buf.अणुin,outपूर्ण field of data inकाष्ठाions. This is wrong as data
 * inकाष्ठाions might be split.
 *
 * Given a data inकाष्ठाion, वापसs the offset to start from.
 */
अचिन्हित पूर्णांक nand_subop_get_data_start_off(स्थिर काष्ठा nand_subop *subop,
					   अचिन्हित पूर्णांक instr_idx)
अणु
	अगर (WARN_ON(!nand_subop_instr_is_valid(subop, instr_idx) ||
		    !nand_instr_is_data(&subop->instrs[instr_idx])))
		वापस 0;

	वापस nand_subop_get_start_off(subop, instr_idx);
पूर्ण
EXPORT_SYMBOL_GPL(nand_subop_get_data_start_off);

/**
 * nand_subop_get_data_len - Get the number of bytes to retrieve
 * @subop: The entire sub-operation
 * @instr_idx: Index of the inकाष्ठाion inside the sub-operation
 *
 * During driver development, one could be tempted to directly use the
 * ->data->len field of a data inकाष्ठाion. This is wrong as data inकाष्ठाions
 * might be split.
 *
 * Returns the length of the chunk of data to send/receive.
 */
अचिन्हित पूर्णांक nand_subop_get_data_len(स्थिर काष्ठा nand_subop *subop,
				     अचिन्हित पूर्णांक instr_idx)
अणु
	पूर्णांक start_off = 0, end_off;

	अगर (WARN_ON(!nand_subop_instr_is_valid(subop, instr_idx) ||
		    !nand_instr_is_data(&subop->instrs[instr_idx])))
		वापस 0;

	start_off = nand_subop_get_data_start_off(subop, instr_idx);

	अगर (instr_idx == subop->ninstrs - 1 &&
	    subop->last_instr_end_off)
		end_off = subop->last_instr_end_off;
	अन्यथा
		end_off = subop->instrs[instr_idx].ctx.data.len;

	वापस end_off - start_off;
पूर्ण
EXPORT_SYMBOL_GPL(nand_subop_get_data_len);

/**
 * nand_reset - Reset and initialize a न_अंकD device
 * @chip: The न_अंकD chip
 * @chipnr: Internal die id
 *
 * Save the timings data काष्ठाure, then apply SDR timings mode 0 (see
 * nand_reset_पूर्णांकerface क्रम details), करो the reset operation, and apply
 * back the previous timings.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक nand_reset(काष्ठा nand_chip *chip, पूर्णांक chipnr)
अणु
	पूर्णांक ret;

	ret = nand_reset_पूर्णांकerface(chip, chipnr);
	अगर (ret)
		वापस ret;

	/*
	 * The CS line has to be released beक्रमe we can apply the new न_अंकD
	 * पूर्णांकerface settings, hence this weird nand_select_target()
	 * nand_deselect_target() dance.
	 */
	nand_select_target(chip, chipnr);
	ret = nand_reset_op(chip);
	nand_deselect_target(chip);
	अगर (ret)
		वापस ret;

	ret = nand_setup_पूर्णांकerface(chip, chipnr);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_reset);

/**
 * nand_get_features - wrapper to perक्रमm a GET_FEATURE
 * @chip: न_अंकD chip info काष्ठाure
 * @addr: feature address
 * @subfeature_param: the subfeature parameters, a four bytes array
 *
 * Returns 0 क्रम success, a negative error otherwise. Returns -ENOTSUPP अगर the
 * operation cannot be handled.
 */
पूर्णांक nand_get_features(काष्ठा nand_chip *chip, पूर्णांक addr,
		      u8 *subfeature_param)
अणु
	अगर (!nand_supports_get_features(chip, addr))
		वापस -ENOTSUPP;

	अगर (chip->legacy.get_features)
		वापस chip->legacy.get_features(chip, addr, subfeature_param);

	वापस nand_get_features_op(chip, addr, subfeature_param);
पूर्ण

/**
 * nand_set_features - wrapper to perक्रमm a SET_FEATURE
 * @chip: न_अंकD chip info काष्ठाure
 * @addr: feature address
 * @subfeature_param: the subfeature parameters, a four bytes array
 *
 * Returns 0 क्रम success, a negative error otherwise. Returns -ENOTSUPP अगर the
 * operation cannot be handled.
 */
पूर्णांक nand_set_features(काष्ठा nand_chip *chip, पूर्णांक addr,
		      u8 *subfeature_param)
अणु
	अगर (!nand_supports_set_features(chip, addr))
		वापस -ENOTSUPP;

	अगर (chip->legacy.set_features)
		वापस chip->legacy.set_features(chip, addr, subfeature_param);

	वापस nand_set_features_op(chip, addr, subfeature_param);
पूर्ण

/**
 * nand_check_erased_buf - check अगर a buffer contains (almost) only 0xff data
 * @buf: buffer to test
 * @len: buffer length
 * @bitflips_threshold: maximum number of bitflips
 *
 * Check अगर a buffer contains only 0xff, which means the underlying region
 * has been erased and is पढ़ोy to be programmed.
 * The bitflips_threshold specअगरy the maximum number of bitflips beक्रमe
 * considering the region is not erased.
 * Note: The logic of this function has been extracted from the memweight
 * implementation, except that nand_check_erased_buf function निकास beक्रमe
 * testing the whole buffer अगर the number of bitflips exceed the
 * bitflips_threshold value.
 *
 * Returns a positive number of bitflips less than or equal to
 * bitflips_threshold, or -ERROR_CODE क्रम bitflips in excess of the
 * threshold.
 */
अटल पूर्णांक nand_check_erased_buf(व्योम *buf, पूर्णांक len, पूर्णांक bitflips_threshold)
अणु
	स्थिर अचिन्हित अक्षर *biपंचांगap = buf;
	पूर्णांक bitflips = 0;
	पूर्णांक weight;

	क्रम (; len && ((uपूर्णांकptr_t)biपंचांगap) % माप(दीर्घ);
	     len--, biपंचांगap++) अणु
		weight = hweight8(*biपंचांगap);
		bitflips += BITS_PER_BYTE - weight;
		अगर (unlikely(bitflips > bitflips_threshold))
			वापस -EBADMSG;
	पूर्ण

	क्रम (; len >= माप(दीर्घ);
	     len -= माप(दीर्घ), biपंचांगap += माप(दीर्घ)) अणु
		अचिन्हित दीर्घ d = *((अचिन्हित दीर्घ *)biपंचांगap);
		अगर (d == ~0UL)
			जारी;
		weight = hweight_दीर्घ(d);
		bitflips += BITS_PER_LONG - weight;
		अगर (unlikely(bitflips > bitflips_threshold))
			वापस -EBADMSG;
	पूर्ण

	क्रम (; len > 0; len--, biपंचांगap++) अणु
		weight = hweight8(*biपंचांगap);
		bitflips += BITS_PER_BYTE - weight;
		अगर (unlikely(bitflips > bitflips_threshold))
			वापस -EBADMSG;
	पूर्ण

	वापस bitflips;
पूर्ण

/**
 * nand_check_erased_ecc_chunk - check अगर an ECC chunk contains (almost) only
 *				 0xff data
 * @data: data buffer to test
 * @datalen: data length
 * @ecc: ECC buffer
 * @ecclen: ECC length
 * @extraoob: extra OOB buffer
 * @extraooblen: extra OOB length
 * @bitflips_threshold: maximum number of bitflips
 *
 * Check अगर a data buffer and its associated ECC and OOB data contains only
 * 0xff pattern, which means the underlying region has been erased and is
 * पढ़ोy to be programmed.
 * The bitflips_threshold specअगरy the maximum number of bitflips beक्रमe
 * considering the region as not erased.
 *
 * Note:
 * 1/ ECC algorithms are working on pre-defined block sizes which are usually
 *    dअगरferent from the न_अंकD page size. When fixing bitflips, ECC engines will
 *    report the number of errors per chunk, and the न_अंकD core infraकाष्ठाure
 *    expect you to वापस the maximum number of bitflips क्रम the whole page.
 *    This is why you should always use this function on a single chunk and
 *    not on the whole page. After checking each chunk you should update your
 *    max_bitflips value accordingly.
 * 2/ When checking क्रम bitflips in erased pages you should not only check
 *    the payload data but also their associated ECC data, because a user might
 *    have programmed almost all bits to 1 but a few. In this हाल, we
 *    shouldn't consider the chunk as erased, and checking ECC bytes prevent
 *    this हाल.
 * 3/ The extraoob argument is optional, and should be used अगर some of your OOB
 *    data are रक्षित by the ECC engine.
 *    It could also be used अगर you support subpages and want to attach some
 *    extra OOB data to an ECC chunk.
 *
 * Returns a positive number of bitflips less than or equal to
 * bitflips_threshold, or -ERROR_CODE क्रम bitflips in excess of the
 * threshold. In हाल of success, the passed buffers are filled with 0xff.
 */
पूर्णांक nand_check_erased_ecc_chunk(व्योम *data, पूर्णांक datalen,
				व्योम *ecc, पूर्णांक ecclen,
				व्योम *extraoob, पूर्णांक extraooblen,
				पूर्णांक bitflips_threshold)
अणु
	पूर्णांक data_bitflips = 0, ecc_bitflips = 0, extraoob_bitflips = 0;

	data_bitflips = nand_check_erased_buf(data, datalen,
					      bitflips_threshold);
	अगर (data_bitflips < 0)
		वापस data_bitflips;

	bitflips_threshold -= data_bitflips;

	ecc_bitflips = nand_check_erased_buf(ecc, ecclen, bitflips_threshold);
	अगर (ecc_bitflips < 0)
		वापस ecc_bitflips;

	bitflips_threshold -= ecc_bitflips;

	extraoob_bitflips = nand_check_erased_buf(extraoob, extraooblen,
						  bitflips_threshold);
	अगर (extraoob_bitflips < 0)
		वापस extraoob_bitflips;

	अगर (data_bitflips)
		स_रखो(data, 0xff, datalen);

	अगर (ecc_bitflips)
		स_रखो(ecc, 0xff, ecclen);

	अगर (extraoob_bitflips)
		स_रखो(extraoob, 0xff, extraooblen);

	वापस data_bitflips + ecc_bitflips + extraoob_bitflips;
पूर्ण
EXPORT_SYMBOL(nand_check_erased_ecc_chunk);

/**
 * nand_पढ़ो_page_raw_notsupp - dummy पढ़ो raw page function
 * @chip: nand chip info काष्ठाure
 * @buf: buffer to store पढ़ो data
 * @oob_required: caller requires OOB data पढ़ो to chip->oob_poi
 * @page: page number to पढ़ो
 *
 * Returns -ENOTSUPP unconditionally.
 */
पूर्णांक nand_पढ़ो_page_raw_notsupp(काष्ठा nand_chip *chip, u8 *buf,
			       पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस -ENOTSUPP;
पूर्ण

/**
 * nand_पढ़ो_page_raw - [INTERN] पढ़ो raw page data without ecc
 * @chip: nand chip info काष्ठाure
 * @buf: buffer to store पढ़ो data
 * @oob_required: caller requires OOB data पढ़ो to chip->oob_poi
 * @page: page number to पढ़ो
 *
 * Not क्रम syndrome calculating ECC controllers, which use a special oob layout.
 */
पूर्णांक nand_पढ़ो_page_raw(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक oob_required,
		       पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = nand_पढ़ो_page_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	अगर (ret)
		वापस ret;

	अगर (oob_required) अणु
		ret = nand_पढ़ो_data_op(chip, chip->oob_poi, mtd->oobsize,
					false, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nand_पढ़ो_page_raw);

/**
 * nand_monolithic_पढ़ो_page_raw - Monolithic page पढ़ो in raw mode
 * @chip: न_अंकD chip info काष्ठाure
 * @buf: buffer to store पढ़ो data
 * @oob_required: caller requires OOB data पढ़ो to chip->oob_poi
 * @page: page number to पढ़ो
 *
 * This is a raw page पढ़ो, ie. without any error detection/correction.
 * Monolithic means we are requesting all the relevant data (मुख्य plus
 * eventually OOB) to be loaded in the न_अंकD cache and sent over the
 * bus (from the न_अंकD chip to the न_अंकD controller) in a single
 * operation. This is an alternative to nand_पढ़ो_page_raw(), which
 * first पढ़ोs the मुख्य data, and अगर the OOB data is requested too,
 * then पढ़ोs more data on the bus.
 */
पूर्णांक nand_monolithic_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित पूर्णांक size = mtd->ग_लिखोsize;
	u8 *पढ़ो_buf = buf;
	पूर्णांक ret;

	अगर (oob_required) अणु
		size += mtd->oobsize;

		अगर (buf != chip->data_buf)
			पढ़ो_buf = nand_get_data_buf(chip);
	पूर्ण

	ret = nand_पढ़ो_page_op(chip, page, 0, पढ़ो_buf, size);
	अगर (ret)
		वापस ret;

	अगर (buf != chip->data_buf)
		स_नकल(buf, पढ़ो_buf, mtd->ग_लिखोsize);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nand_monolithic_पढ़ो_page_raw);

/**
 * nand_पढ़ो_page_raw_syndrome - [INTERN] पढ़ो raw page data without ecc
 * @chip: nand chip info काष्ठाure
 * @buf: buffer to store पढ़ो data
 * @oob_required: caller requires OOB data पढ़ो to chip->oob_poi
 * @page: page number to पढ़ो
 *
 * We need a special oob layout and handling even when OOB isn't used.
 */
अटल पूर्णांक nand_पढ़ो_page_raw_syndrome(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				       पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक eccsize = chip->ecc.size;
	पूर्णांक eccbytes = chip->ecc.bytes;
	uपूर्णांक8_t *oob = chip->oob_poi;
	पूर्णांक steps, size, ret;

	ret = nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (steps = chip->ecc.steps; steps > 0; steps--) अणु
		ret = nand_पढ़ो_data_op(chip, buf, eccsize, false, false);
		अगर (ret)
			वापस ret;

		buf += eccsize;

		अगर (chip->ecc.prepad) अणु
			ret = nand_पढ़ो_data_op(chip, oob, chip->ecc.prepad,
						false, false);
			अगर (ret)
				वापस ret;

			oob += chip->ecc.prepad;
		पूर्ण

		ret = nand_पढ़ो_data_op(chip, oob, eccbytes, false, false);
		अगर (ret)
			वापस ret;

		oob += eccbytes;

		अगर (chip->ecc.postpad) अणु
			ret = nand_पढ़ो_data_op(chip, oob, chip->ecc.postpad,
						false, false);
			अगर (ret)
				वापस ret;

			oob += chip->ecc.postpad;
		पूर्ण
	पूर्ण

	size = mtd->oobsize - (oob - chip->oob_poi);
	अगर (size) अणु
		ret = nand_पढ़ो_data_op(chip, oob, size, false, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nand_पढ़ो_page_swecc - [REPLACEABLE] software ECC based page पढ़ो function
 * @chip: nand chip info काष्ठाure
 * @buf: buffer to store पढ़ो data
 * @oob_required: caller requires OOB data पढ़ो to chip->oob_poi
 * @page: page number to पढ़ो
 */
अटल पूर्णांक nand_पढ़ो_page_swecc(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक i, eccsize = chip->ecc.size, ret;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	uपूर्णांक8_t *p = buf;
	uपूर्णांक8_t *ecc_calc = chip->ecc.calc_buf;
	uपूर्णांक8_t *ecc_code = chip->ecc.code_buf;
	अचिन्हित पूर्णांक max_bitflips = 0;

	chip->ecc.पढ़ो_page_raw(chip, buf, 1, page);

	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->ecc.calculate(chip, p, &ecc_calc[i]);

	ret = mtd_ooblayout_get_eccbytes(mtd, ecc_code, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	eccsteps = chip->ecc.steps;
	p = buf;

	क्रम (i = 0 ; eccsteps; eccsteps--, i += eccbytes, p += eccsize) अणु
		पूर्णांक stat;

		stat = chip->ecc.correct(chip, p, &ecc_code[i], &ecc_calc[i]);
		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण
	वापस max_bitflips;
पूर्ण

/**
 * nand_पढ़ो_subpage - [REPLACEABLE] ECC based sub-page पढ़ो function
 * @chip: nand chip info काष्ठाure
 * @data_offs: offset of requested data within the page
 * @पढ़ोlen: data length
 * @bufpoi: buffer to store पढ़ो data
 * @page: page number to पढ़ो
 */
अटल पूर्णांक nand_पढ़ो_subpage(काष्ठा nand_chip *chip, uपूर्णांक32_t data_offs,
			     uपूर्णांक32_t पढ़ोlen, uपूर्णांक8_t *bufpoi, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक start_step, end_step, num_steps, ret;
	uपूर्णांक8_t *p;
	पूर्णांक data_col_addr, i, gaps = 0;
	पूर्णांक datafrag_len, eccfrag_len, aligned_len, aligned_pos;
	पूर्णांक busw = (chip->options & न_अंकD_BUSWIDTH_16) ? 2 : 1;
	पूर्णांक index, section = 0;
	अचिन्हित पूर्णांक max_bitflips = 0;
	काष्ठा mtd_oob_region oobregion = अणु पूर्ण;

	/* Column address within the page aligned to ECC size (256bytes) */
	start_step = data_offs / chip->ecc.size;
	end_step = (data_offs + पढ़ोlen - 1) / chip->ecc.size;
	num_steps = end_step - start_step + 1;
	index = start_step * chip->ecc.bytes;

	/* Data size aligned to ECC ecc.size */
	datafrag_len = num_steps * chip->ecc.size;
	eccfrag_len = num_steps * chip->ecc.bytes;

	data_col_addr = start_step * chip->ecc.size;
	/* If we पढ़ो not a page aligned data */
	p = bufpoi + data_col_addr;
	ret = nand_पढ़ो_page_op(chip, page, data_col_addr, p, datafrag_len);
	अगर (ret)
		वापस ret;

	/* Calculate ECC */
	क्रम (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size)
		chip->ecc.calculate(chip, p, &chip->ecc.calc_buf[i]);

	/*
	 * The perक्रमmance is faster अगर we position offsets according to
	 * ecc.pos. Let's make sure that there are no gaps in ECC positions.
	 */
	ret = mtd_ooblayout_find_eccregion(mtd, index, &section, &oobregion);
	अगर (ret)
		वापस ret;

	अगर (oobregion.length < eccfrag_len)
		gaps = 1;

	अगर (gaps) अणु
		ret = nand_change_पढ़ो_column_op(chip, mtd->ग_लिखोsize,
						 chip->oob_poi, mtd->oobsize,
						 false);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/*
		 * Send the command to पढ़ो the particular ECC bytes take care
		 * about buswidth alignment in पढ़ो_buf.
		 */
		aligned_pos = oobregion.offset & ~(busw - 1);
		aligned_len = eccfrag_len;
		अगर (oobregion.offset & (busw - 1))
			aligned_len++;
		अगर ((oobregion.offset + (num_steps * chip->ecc.bytes)) &
		    (busw - 1))
			aligned_len++;

		ret = nand_change_पढ़ो_column_op(chip,
						 mtd->ग_लिखोsize + aligned_pos,
						 &chip->oob_poi[aligned_pos],
						 aligned_len, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mtd_ooblayout_get_eccbytes(mtd, chip->ecc.code_buf,
					 chip->oob_poi, index, eccfrag_len);
	अगर (ret)
		वापस ret;

	p = bufpoi + data_col_addr;
	क्रम (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size) अणु
		पूर्णांक stat;

		stat = chip->ecc.correct(chip, p, &chip->ecc.code_buf[i],
					 &chip->ecc.calc_buf[i]);
		अगर (stat == -EBADMSG &&
		    (chip->ecc.options & न_अंकD_ECC_GENERIC_ERASED_CHECK)) अणु
			/* check क्रम empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, chip->ecc.size,
						&chip->ecc.code_buf[i],
						chip->ecc.bytes,
						शून्य, 0,
						chip->ecc.strength);
		पूर्ण

		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण
	वापस max_bitflips;
पूर्ण

/**
 * nand_पढ़ो_page_hwecc - [REPLACEABLE] hardware ECC based page पढ़ो function
 * @chip: nand chip info काष्ठाure
 * @buf: buffer to store पढ़ो data
 * @oob_required: caller requires OOB data पढ़ो to chip->oob_poi
 * @page: page number to पढ़ो
 *
 * Not क्रम syndrome calculating ECC controllers which need a special oob layout.
 */
अटल पूर्णांक nand_पढ़ो_page_hwecc(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक i, eccsize = chip->ecc.size, ret;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	uपूर्णांक8_t *p = buf;
	uपूर्णांक8_t *ecc_calc = chip->ecc.calc_buf;
	uपूर्णांक8_t *ecc_code = chip->ecc.code_buf;
	अचिन्हित पूर्णांक max_bitflips = 0;

	ret = nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) अणु
		chip->ecc.hwctl(chip, न_अंकD_ECC_READ);

		ret = nand_पढ़ो_data_op(chip, p, eccsize, false, false);
		अगर (ret)
			वापस ret;

		chip->ecc.calculate(chip, p, &ecc_calc[i]);
	पूर्ण

	ret = nand_पढ़ो_data_op(chip, chip->oob_poi, mtd->oobsize, false,
				false);
	अगर (ret)
		वापस ret;

	ret = mtd_ooblayout_get_eccbytes(mtd, ecc_code, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	eccsteps = chip->ecc.steps;
	p = buf;

	क्रम (i = 0 ; eccsteps; eccsteps--, i += eccbytes, p += eccsize) अणु
		पूर्णांक stat;

		stat = chip->ecc.correct(chip, p, &ecc_code[i], &ecc_calc[i]);
		अगर (stat == -EBADMSG &&
		    (chip->ecc.options & न_अंकD_ECC_GENERIC_ERASED_CHECK)) अणु
			/* check क्रम empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, eccsize,
						&ecc_code[i], eccbytes,
						शून्य, 0,
						chip->ecc.strength);
		पूर्ण

		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण
	वापस max_bitflips;
पूर्ण

/**
 * nand_पढ़ो_page_syndrome - [REPLACEABLE] hardware ECC syndrome based page पढ़ो
 * @chip: nand chip info काष्ठाure
 * @buf: buffer to store पढ़ो data
 * @oob_required: caller requires OOB data पढ़ो to chip->oob_poi
 * @page: page number to पढ़ो
 *
 * The hw generator calculates the error syndrome स्वतःmatically. Thereक्रमe we
 * need a special oob layout and handling.
 */
अटल पूर्णांक nand_पढ़ो_page_syndrome(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				   पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret, i, eccsize = chip->ecc.size;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	पूर्णांक eccpadbytes = eccbytes + chip->ecc.prepad + chip->ecc.postpad;
	uपूर्णांक8_t *p = buf;
	uपूर्णांक8_t *oob = chip->oob_poi;
	अचिन्हित पूर्णांक max_bitflips = 0;

	ret = nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) अणु
		पूर्णांक stat;

		chip->ecc.hwctl(chip, न_अंकD_ECC_READ);

		ret = nand_पढ़ो_data_op(chip, p, eccsize, false, false);
		अगर (ret)
			वापस ret;

		अगर (chip->ecc.prepad) अणु
			ret = nand_पढ़ो_data_op(chip, oob, chip->ecc.prepad,
						false, false);
			अगर (ret)
				वापस ret;

			oob += chip->ecc.prepad;
		पूर्ण

		chip->ecc.hwctl(chip, न_अंकD_ECC_READSYN);

		ret = nand_पढ़ो_data_op(chip, oob, eccbytes, false, false);
		अगर (ret)
			वापस ret;

		stat = chip->ecc.correct(chip, p, oob, शून्य);

		oob += eccbytes;

		अगर (chip->ecc.postpad) अणु
			ret = nand_पढ़ो_data_op(chip, oob, chip->ecc.postpad,
						false, false);
			अगर (ret)
				वापस ret;

			oob += chip->ecc.postpad;
		पूर्ण

		अगर (stat == -EBADMSG &&
		    (chip->ecc.options & न_अंकD_ECC_GENERIC_ERASED_CHECK)) अणु
			/* check क्रम empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, chip->ecc.size,
							   oob - eccpadbytes,
							   eccpadbytes,
							   शून्य, 0,
							   chip->ecc.strength);
		पूर्ण

		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण

	/* Calculate reमुख्यing oob bytes */
	i = mtd->oobsize - (oob - chip->oob_poi);
	अगर (i) अणु
		ret = nand_पढ़ो_data_op(chip, oob, i, false, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस max_bitflips;
पूर्ण

/**
 * nand_transfer_oob - [INTERN] Transfer oob to client buffer
 * @chip: न_अंकD chip object
 * @oob: oob destination address
 * @ops: oob ops काष्ठाure
 * @len: size of oob to transfer
 */
अटल uपूर्णांक8_t *nand_transfer_oob(काष्ठा nand_chip *chip, uपूर्णांक8_t *oob,
				  काष्ठा mtd_oob_ops *ops, माप_प्रकार len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	चयन (ops->mode) अणु

	हाल MTD_OPS_PLACE_OOB:
	हाल MTD_OPS_RAW:
		स_नकल(oob, chip->oob_poi + ops->ooboffs, len);
		वापस oob + len;

	हाल MTD_OPS_AUTO_OOB:
		ret = mtd_ooblayout_get_databytes(mtd, oob, chip->oob_poi,
						  ops->ooboffs, len);
		BUG_ON(ret);
		वापस oob + len;

	शेष:
		BUG();
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * nand_setup_पढ़ो_retry - [INTERN] Set the READ RETRY mode
 * @chip: न_अंकD chip object
 * @retry_mode: the retry mode to use
 *
 * Some venकरोrs supply a special command to shअगरt the Vt threshold, to be used
 * when there are too many bitflips in a page (i.e., ECC error). After setting
 * a new threshold, the host should retry पढ़ोing the page.
 */
अटल पूर्णांक nand_setup_पढ़ो_retry(काष्ठा nand_chip *chip, पूर्णांक retry_mode)
अणु
	pr_debug("setting READ RETRY mode %d\n", retry_mode);

	अगर (retry_mode >= chip->पढ़ो_retries)
		वापस -EINVAL;

	अगर (!chip->ops.setup_पढ़ो_retry)
		वापस -EOPNOTSUPP;

	वापस chip->ops.setup_पढ़ो_retry(chip, retry_mode);
पूर्ण

अटल व्योम nand_रुको_पढ़ोrdy(काष्ठा nand_chip *chip)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr;

	अगर (!(chip->options & न_अंकD_NEED_READRDY))
		वापस;

	sdr = nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
	WARN_ON(nand_रुको_rdy_op(chip, PSEC_TO_MSEC(sdr->tR_max), 0));
पूर्ण

/**
 * nand_करो_पढ़ो_ops - [INTERN] Read data with ECC
 * @chip: न_अंकD chip object
 * @from: offset to पढ़ो from
 * @ops: oob ops काष्ठाure
 *
 * Internal function. Called with chip held.
 */
अटल पूर्णांक nand_करो_पढ़ो_ops(काष्ठा nand_chip *chip, loff_t from,
			    काष्ठा mtd_oob_ops *ops)
अणु
	पूर्णांक chipnr, page, realpage, col, bytes, aligned, oob_required;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret = 0;
	uपूर्णांक32_t पढ़ोlen = ops->len;
	uपूर्णांक32_t oobपढ़ोlen = ops->ooblen;
	uपूर्णांक32_t max_oobsize = mtd_oobavail(mtd, ops);

	uपूर्णांक8_t *bufpoi, *oob, *buf;
	पूर्णांक use_bounce_buf;
	अचिन्हित पूर्णांक max_bitflips = 0;
	पूर्णांक retry_mode = 0;
	bool ecc_fail = false;

	/* Check अगर the region is secured */
	अगर (nand_region_is_secured(chip, from, पढ़ोlen))
		वापस -EIO;

	chipnr = (पूर्णांक)(from >> chip->chip_shअगरt);
	nand_select_target(chip, chipnr);

	realpage = (पूर्णांक)(from >> chip->page_shअगरt);
	page = realpage & chip->pagemask;

	col = (पूर्णांक)(from & (mtd->ग_लिखोsize - 1));

	buf = ops->datbuf;
	oob = ops->oobbuf;
	oob_required = oob ? 1 : 0;

	जबतक (1) अणु
		काष्ठा mtd_ecc_stats ecc_stats = mtd->ecc_stats;

		bytes = min(mtd->ग_लिखोsize - col, पढ़ोlen);
		aligned = (bytes == mtd->ग_लिखोsize);

		अगर (!aligned)
			use_bounce_buf = 1;
		अन्यथा अगर (chip->options & न_अंकD_USES_DMA)
			use_bounce_buf = !virt_addr_valid(buf) ||
					 !IS_ALIGNED((अचिन्हित दीर्घ)buf,
						     chip->buf_align);
		अन्यथा
			use_bounce_buf = 0;

		/* Is the current page in the buffer? */
		अगर (realpage != chip->pagecache.page || oob) अणु
			bufpoi = use_bounce_buf ? chip->data_buf : buf;

			अगर (use_bounce_buf && aligned)
				pr_debug("%s: using read bounce buffer for buf@%p\n",
						 __func__, buf);

पढ़ो_retry:
			/*
			 * Now पढ़ो the page पूर्णांकo the buffer.  Absent an error,
			 * the पढ़ो methods वापस max bitflips per ecc step.
			 */
			अगर (unlikely(ops->mode == MTD_OPS_RAW))
				ret = chip->ecc.पढ़ो_page_raw(chip, bufpoi,
							      oob_required,
							      page);
			अन्यथा अगर (!aligned && न_अंकD_HAS_SUBPAGE_READ(chip) &&
				 !oob)
				ret = chip->ecc.पढ़ो_subpage(chip, col, bytes,
							     bufpoi, page);
			अन्यथा
				ret = chip->ecc.पढ़ो_page(chip, bufpoi,
							  oob_required, page);
			अगर (ret < 0) अणु
				अगर (use_bounce_buf)
					/* Invalidate page cache */
					chip->pagecache.page = -1;
				अवरोध;
			पूर्ण

			/*
			 * Copy back the data in the initial buffer when पढ़ोing
			 * partial pages or when a bounce buffer is required.
			 */
			अगर (use_bounce_buf) अणु
				अगर (!न_अंकD_HAS_SUBPAGE_READ(chip) && !oob &&
				    !(mtd->ecc_stats.failed - ecc_stats.failed) &&
				    (ops->mode != MTD_OPS_RAW)) अणु
					chip->pagecache.page = realpage;
					chip->pagecache.bitflips = ret;
				पूर्ण अन्यथा अणु
					/* Invalidate page cache */
					chip->pagecache.page = -1;
				पूर्ण
				स_नकल(buf, bufpoi + col, bytes);
			पूर्ण

			अगर (unlikely(oob)) अणु
				पूर्णांक toपढ़ो = min(oobपढ़ोlen, max_oobsize);

				अगर (toपढ़ो) अणु
					oob = nand_transfer_oob(chip, oob, ops,
								toपढ़ो);
					oobपढ़ोlen -= toपढ़ो;
				पूर्ण
			पूर्ण

			nand_रुको_पढ़ोrdy(chip);

			अगर (mtd->ecc_stats.failed - ecc_stats.failed) अणु
				अगर (retry_mode + 1 < chip->पढ़ो_retries) अणु
					retry_mode++;
					ret = nand_setup_पढ़ो_retry(chip,
							retry_mode);
					अगर (ret < 0)
						अवरोध;

					/* Reset ecc_stats; retry */
					mtd->ecc_stats = ecc_stats;
					जाओ पढ़ो_retry;
				पूर्ण अन्यथा अणु
					/* No more retry modes; real failure */
					ecc_fail = true;
				पूर्ण
			पूर्ण

			buf += bytes;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, ret);
		पूर्ण अन्यथा अणु
			स_नकल(buf, chip->data_buf + col, bytes);
			buf += bytes;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips,
					     chip->pagecache.bitflips);
		पूर्ण

		पढ़ोlen -= bytes;

		/* Reset to retry mode 0 */
		अगर (retry_mode) अणु
			ret = nand_setup_पढ़ो_retry(chip, 0);
			अगर (ret < 0)
				अवरोध;
			retry_mode = 0;
		पूर्ण

		अगर (!पढ़ोlen)
			अवरोध;

		/* For subsequent पढ़ोs align to page boundary */
		col = 0;
		/* Increment page address */
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, अगर we cross a chip boundary */
		अगर (!page) अणु
			chipnr++;
			nand_deselect_target(chip);
			nand_select_target(chip, chipnr);
		पूर्ण
	पूर्ण
	nand_deselect_target(chip);

	ops->retlen = ops->len - (माप_प्रकार) पढ़ोlen;
	अगर (oob)
		ops->oobretlen = ops->ooblen - oobपढ़ोlen;

	अगर (ret < 0)
		वापस ret;

	अगर (ecc_fail)
		वापस -EBADMSG;

	वापस max_bitflips;
पूर्ण

/**
 * nand_पढ़ो_oob_std - [REPLACEABLE] the most common OOB data पढ़ो function
 * @chip: nand chip info काष्ठाure
 * @page: page number to पढ़ो
 */
पूर्णांक nand_पढ़ो_oob_std(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस nand_पढ़ो_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
पूर्ण
EXPORT_SYMBOL(nand_पढ़ो_oob_std);

/**
 * nand_पढ़ो_oob_syndrome - [REPLACEABLE] OOB data पढ़ो function क्रम HW ECC
 *			    with syndromes
 * @chip: nand chip info काष्ठाure
 * @page: page number to पढ़ो
 */
अटल पूर्णांक nand_पढ़ो_oob_syndrome(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक length = mtd->oobsize;
	पूर्णांक chunk = chip->ecc.bytes + chip->ecc.prepad + chip->ecc.postpad;
	पूर्णांक eccsize = chip->ecc.size;
	uपूर्णांक8_t *bufpoi = chip->oob_poi;
	पूर्णांक i, toपढ़ो, sndrnd = 0, pos, ret;

	ret = nand_पढ़ो_page_op(chip, page, chip->ecc.size, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		अगर (sndrnd) अणु
			पूर्णांक ret;

			pos = eccsize + i * (eccsize + chunk);
			अगर (mtd->ग_लिखोsize > 512)
				ret = nand_change_पढ़ो_column_op(chip, pos,
								 शून्य, 0,
								 false);
			अन्यथा
				ret = nand_पढ़ो_page_op(chip, page, pos, शून्य,
							0);

			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा
			sndrnd = 1;
		toपढ़ो = min_t(पूर्णांक, length, chunk);

		ret = nand_पढ़ो_data_op(chip, bufpoi, toपढ़ो, false, false);
		अगर (ret)
			वापस ret;

		bufpoi += toपढ़ो;
		length -= toपढ़ो;
	पूर्ण
	अगर (length > 0) अणु
		ret = nand_पढ़ो_data_op(chip, bufpoi, length, false, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nand_ग_लिखो_oob_std - [REPLACEABLE] the most common OOB data ग_लिखो function
 * @chip: nand chip info काष्ठाure
 * @page: page number to ग_लिखो
 */
पूर्णांक nand_ग_लिखो_oob_std(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस nand_prog_page_op(chip, page, mtd->ग_लिखोsize, chip->oob_poi,
				 mtd->oobsize);
पूर्ण
EXPORT_SYMBOL(nand_ग_लिखो_oob_std);

/**
 * nand_ग_लिखो_oob_syndrome - [REPLACEABLE] OOB data ग_लिखो function क्रम HW ECC
 *			     with syndrome - only क्रम large page flash
 * @chip: nand chip info काष्ठाure
 * @page: page number to ग_लिखो
 */
अटल पूर्णांक nand_ग_लिखो_oob_syndrome(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक chunk = chip->ecc.bytes + chip->ecc.prepad + chip->ecc.postpad;
	पूर्णांक eccsize = chip->ecc.size, length = mtd->oobsize;
	पूर्णांक ret, i, len, pos, sndcmd = 0, steps = chip->ecc.steps;
	स्थिर uपूर्णांक8_t *bufpoi = chip->oob_poi;

	/*
	 * data-ecc-data-ecc ... ecc-oob
	 * or
	 * data-pad-ecc-pad-data-pad .... ecc-pad-oob
	 */
	अगर (!chip->ecc.prepad && !chip->ecc.postpad) अणु
		pos = steps * (eccsize + chunk);
		steps = 0;
	पूर्ण अन्यथा
		pos = eccsize;

	ret = nand_prog_page_begin_op(chip, page, pos, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < steps; i++) अणु
		अगर (sndcmd) अणु
			अगर (mtd->ग_लिखोsize <= 512) अणु
				uपूर्णांक32_t fill = 0xFFFFFFFF;

				len = eccsize;
				जबतक (len > 0) अणु
					पूर्णांक num = min_t(पूर्णांक, len, 4);

					ret = nand_ग_लिखो_data_op(chip, &fill,
								 num, false);
					अगर (ret)
						वापस ret;

					len -= num;
				पूर्ण
			पूर्ण अन्यथा अणु
				pos = eccsize + i * (eccsize + chunk);
				ret = nand_change_ग_लिखो_column_op(chip, pos,
								  शून्य, 0,
								  false);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण अन्यथा
			sndcmd = 1;
		len = min_t(पूर्णांक, length, chunk);

		ret = nand_ग_लिखो_data_op(chip, bufpoi, len, false);
		अगर (ret)
			वापस ret;

		bufpoi += len;
		length -= len;
	पूर्ण
	अगर (length > 0) अणु
		ret = nand_ग_लिखो_data_op(chip, bufpoi, length, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

/**
 * nand_करो_पढ़ो_oob - [INTERN] न_अंकD पढ़ो out-of-band
 * @chip: न_अंकD chip object
 * @from: offset to पढ़ो from
 * @ops: oob operations description काष्ठाure
 *
 * न_अंकD पढ़ो out-of-band data from the spare area.
 */
अटल पूर्णांक nand_करो_पढ़ो_oob(काष्ठा nand_chip *chip, loff_t from,
			    काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित पूर्णांक max_bitflips = 0;
	पूर्णांक page, realpage, chipnr;
	काष्ठा mtd_ecc_stats stats;
	पूर्णांक पढ़ोlen = ops->ooblen;
	पूर्णांक len;
	uपूर्णांक8_t *buf = ops->oobbuf;
	पूर्णांक ret = 0;

	pr_debug("%s: from = 0x%08Lx, len = %i\n",
			__func__, (अचिन्हित दीर्घ दीर्घ)from, पढ़ोlen);

	/* Check अगर the region is secured */
	अगर (nand_region_is_secured(chip, from, पढ़ोlen))
		वापस -EIO;

	stats = mtd->ecc_stats;

	len = mtd_oobavail(mtd, ops);

	chipnr = (पूर्णांक)(from >> chip->chip_shअगरt);
	nand_select_target(chip, chipnr);

	/* Shअगरt to get page */
	realpage = (पूर्णांक)(from >> chip->page_shअगरt);
	page = realpage & chip->pagemask;

	जबतक (1) अणु
		अगर (ops->mode == MTD_OPS_RAW)
			ret = chip->ecc.पढ़ो_oob_raw(chip, page);
		अन्यथा
			ret = chip->ecc.पढ़ो_oob(chip, page);

		अगर (ret < 0)
			अवरोध;

		len = min(len, पढ़ोlen);
		buf = nand_transfer_oob(chip, buf, ops, len);

		nand_रुको_पढ़ोrdy(chip);

		max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, ret);

		पढ़ोlen -= len;
		अगर (!पढ़ोlen)
			अवरोध;

		/* Increment page address */
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, अगर we cross a chip boundary */
		अगर (!page) अणु
			chipnr++;
			nand_deselect_target(chip);
			nand_select_target(chip, chipnr);
		पूर्ण
	पूर्ण
	nand_deselect_target(chip);

	ops->oobretlen = ops->ooblen - पढ़ोlen;

	अगर (ret < 0)
		वापस ret;

	अगर (mtd->ecc_stats.failed - stats.failed)
		वापस -EBADMSG;

	वापस max_bitflips;
पूर्ण

/**
 * nand_पढ़ो_oob - [MTD Interface] न_अंकD पढ़ो data and/or out-of-band
 * @mtd: MTD device काष्ठाure
 * @from: offset to पढ़ो from
 * @ops: oob operation description काष्ठाure
 *
 * न_अंकD पढ़ो data and/or out-of-band data.
 */
अटल पूर्णांक nand_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t from,
			 काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	पूर्णांक ret;

	ops->retlen = 0;

	अगर (ops->mode != MTD_OPS_PLACE_OOB &&
	    ops->mode != MTD_OPS_AUTO_OOB &&
	    ops->mode != MTD_OPS_RAW)
		वापस -ENOTSUPP;

	ret = nand_get_device(chip);
	अगर (ret)
		वापस ret;

	अगर (!ops->datbuf)
		ret = nand_करो_पढ़ो_oob(chip, from, ops);
	अन्यथा
		ret = nand_करो_पढ़ो_ops(chip, from, ops);

	nand_release_device(chip);
	वापस ret;
पूर्ण

/**
 * nand_ग_लिखो_page_raw_notsupp - dummy raw page ग_लिखो function
 * @chip: nand chip info काष्ठाure
 * @buf: data buffer
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 *
 * Returns -ENOTSUPP unconditionally.
 */
पूर्णांक nand_ग_लिखो_page_raw_notsupp(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस -ENOTSUPP;
पूर्ण

/**
 * nand_ग_लिखो_page_raw - [INTERN] raw page ग_लिखो function
 * @chip: nand chip info काष्ठाure
 * @buf: data buffer
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 *
 * Not क्रम syndrome calculating ECC controllers, which use a special oob layout.
 */
पूर्णांक nand_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = nand_prog_page_begin_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	अगर (ret)
		वापस ret;

	अगर (oob_required) अणु
		ret = nand_ग_लिखो_data_op(chip, chip->oob_poi, mtd->oobsize,
					 false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण
EXPORT_SYMBOL(nand_ग_लिखो_page_raw);

/**
 * nand_monolithic_ग_लिखो_page_raw - Monolithic page ग_लिखो in raw mode
 * @chip: न_अंकD chip info काष्ठाure
 * @buf: data buffer to ग_लिखो
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 *
 * This is a raw page ग_लिखो, ie. without any error detection/correction.
 * Monolithic means we are requesting all the relevant data (मुख्य plus
 * eventually OOB) to be sent over the bus and effectively programmed
 * पूर्णांकo the न_अंकD chip arrays in a single operation. This is an
 * alternative to nand_ग_लिखो_page_raw(), which first sends the मुख्य
 * data, then eventually send the OOB data by latching more data
 * cycles on the न_अंकD bus, and finally sends the program command to
 * synchronyze the न_अंकD chip cache.
 */
पूर्णांक nand_monolithic_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				   पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित पूर्णांक size = mtd->ग_लिखोsize;
	u8 *ग_लिखो_buf = (u8 *)buf;

	अगर (oob_required) अणु
		size += mtd->oobsize;

		अगर (buf != chip->data_buf) अणु
			ग_लिखो_buf = nand_get_data_buf(chip);
			स_नकल(ग_लिखो_buf, buf, mtd->ग_लिखोsize);
		पूर्ण
	पूर्ण

	वापस nand_prog_page_op(chip, page, 0, ग_लिखो_buf, size);
पूर्ण
EXPORT_SYMBOL(nand_monolithic_ग_लिखो_page_raw);

/**
 * nand_ग_लिखो_page_raw_syndrome - [INTERN] raw page ग_लिखो function
 * @chip: nand chip info काष्ठाure
 * @buf: data buffer
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 *
 * We need a special oob layout and handling even when ECC isn't checked.
 */
अटल पूर्णांक nand_ग_लिखो_page_raw_syndrome(काष्ठा nand_chip *chip,
					स्थिर uपूर्णांक8_t *buf, पूर्णांक oob_required,
					पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक eccsize = chip->ecc.size;
	पूर्णांक eccbytes = chip->ecc.bytes;
	uपूर्णांक8_t *oob = chip->oob_poi;
	पूर्णांक steps, size, ret;

	ret = nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (steps = chip->ecc.steps; steps > 0; steps--) अणु
		ret = nand_ग_लिखो_data_op(chip, buf, eccsize, false);
		अगर (ret)
			वापस ret;

		buf += eccsize;

		अगर (chip->ecc.prepad) अणु
			ret = nand_ग_लिखो_data_op(chip, oob, chip->ecc.prepad,
						 false);
			अगर (ret)
				वापस ret;

			oob += chip->ecc.prepad;
		पूर्ण

		ret = nand_ग_लिखो_data_op(chip, oob, eccbytes, false);
		अगर (ret)
			वापस ret;

		oob += eccbytes;

		अगर (chip->ecc.postpad) अणु
			ret = nand_ग_लिखो_data_op(chip, oob, chip->ecc.postpad,
						 false);
			अगर (ret)
				वापस ret;

			oob += chip->ecc.postpad;
		पूर्ण
	पूर्ण

	size = mtd->oobsize - (oob - chip->oob_poi);
	अगर (size) अणु
		ret = nand_ग_लिखो_data_op(chip, oob, size, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण
/**
 * nand_ग_लिखो_page_swecc - [REPLACEABLE] software ECC based page ग_लिखो function
 * @chip: nand chip info काष्ठाure
 * @buf: data buffer
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 */
अटल पूर्णांक nand_ग_लिखो_page_swecc(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				 पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक i, eccsize = chip->ecc.size, ret;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	uपूर्णांक8_t *ecc_calc = chip->ecc.calc_buf;
	स्थिर uपूर्णांक8_t *p = buf;

	/* Software ECC calculation */
	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->ecc.calculate(chip, p, &ecc_calc[i]);

	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	वापस chip->ecc.ग_लिखो_page_raw(chip, buf, 1, page);
पूर्ण

/**
 * nand_ग_लिखो_page_hwecc - [REPLACEABLE] hardware ECC based page ग_लिखो function
 * @chip: nand chip info काष्ठाure
 * @buf: data buffer
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 */
अटल पूर्णांक nand_ग_लिखो_page_hwecc(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				 पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक i, eccsize = chip->ecc.size, ret;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	uपूर्णांक8_t *ecc_calc = chip->ecc.calc_buf;
	स्थिर uपूर्णांक8_t *p = buf;

	ret = nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) अणु
		chip->ecc.hwctl(chip, न_अंकD_ECC_WRITE);

		ret = nand_ग_लिखो_data_op(chip, p, eccsize, false);
		अगर (ret)
			वापस ret;

		chip->ecc.calculate(chip, p, &ecc_calc[i]);
	पूर्ण

	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	ret = nand_ग_लिखो_data_op(chip, chip->oob_poi, mtd->oobsize, false);
	अगर (ret)
		वापस ret;

	वापस nand_prog_page_end_op(chip);
पूर्ण


/**
 * nand_ग_लिखो_subpage_hwecc - [REPLACEABLE] hardware ECC based subpage ग_लिखो
 * @chip:	nand chip info काष्ठाure
 * @offset:	column address of subpage within the page
 * @data_len:	data length
 * @buf:	data buffer
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 */
अटल पूर्णांक nand_ग_लिखो_subpage_hwecc(काष्ठा nand_chip *chip, uपूर्णांक32_t offset,
				    uपूर्णांक32_t data_len, स्थिर uपूर्णांक8_t *buf,
				    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	uपूर्णांक8_t *oob_buf  = chip->oob_poi;
	uपूर्णांक8_t *ecc_calc = chip->ecc.calc_buf;
	पूर्णांक ecc_size      = chip->ecc.size;
	पूर्णांक ecc_bytes     = chip->ecc.bytes;
	पूर्णांक ecc_steps     = chip->ecc.steps;
	uपूर्णांक32_t start_step = offset / ecc_size;
	uपूर्णांक32_t end_step   = (offset + data_len - 1) / ecc_size;
	पूर्णांक oob_bytes       = mtd->oobsize / ecc_steps;
	पूर्णांक step, ret;

	ret = nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (step = 0; step < ecc_steps; step++) अणु
		/* configure controller क्रम WRITE access */
		chip->ecc.hwctl(chip, न_अंकD_ECC_WRITE);

		/* ग_लिखो data (untouched subpages alपढ़ोy masked by 0xFF) */
		ret = nand_ग_लिखो_data_op(chip, buf, ecc_size, false);
		अगर (ret)
			वापस ret;

		/* mask ECC of un-touched subpages by padding 0xFF */
		अगर ((step < start_step) || (step > end_step))
			स_रखो(ecc_calc, 0xff, ecc_bytes);
		अन्यथा
			chip->ecc.calculate(chip, buf, ecc_calc);

		/* mask OOB of un-touched subpages by padding 0xFF */
		/* अगर oob_required, preserve OOB metadata of written subpage */
		अगर (!oob_required || (step < start_step) || (step > end_step))
			स_रखो(oob_buf, 0xff, oob_bytes);

		buf += ecc_size;
		ecc_calc += ecc_bytes;
		oob_buf  += oob_bytes;
	पूर्ण

	/* copy calculated ECC क्रम whole page to chip->buffer->oob */
	/* this include masked-value(0xFF) क्रम unwritten subpages */
	ecc_calc = chip->ecc.calc_buf;
	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	/* ग_लिखो OOB buffer to न_अंकD device */
	ret = nand_ग_लिखो_data_op(chip, chip->oob_poi, mtd->oobsize, false);
	अगर (ret)
		वापस ret;

	वापस nand_prog_page_end_op(chip);
पूर्ण


/**
 * nand_ग_लिखो_page_syndrome - [REPLACEABLE] hardware ECC syndrome based page ग_लिखो
 * @chip: nand chip info काष्ठाure
 * @buf: data buffer
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 *
 * The hw generator calculates the error syndrome स्वतःmatically. Thereक्रमe we
 * need a special oob layout and handling.
 */
अटल पूर्णांक nand_ग_लिखो_page_syndrome(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक i, eccsize = chip->ecc.size;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	स्थिर uपूर्णांक8_t *p = buf;
	uपूर्णांक8_t *oob = chip->oob_poi;
	पूर्णांक ret;

	ret = nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) अणु
		chip->ecc.hwctl(chip, न_अंकD_ECC_WRITE);

		ret = nand_ग_लिखो_data_op(chip, p, eccsize, false);
		अगर (ret)
			वापस ret;

		अगर (chip->ecc.prepad) अणु
			ret = nand_ग_लिखो_data_op(chip, oob, chip->ecc.prepad,
						 false);
			अगर (ret)
				वापस ret;

			oob += chip->ecc.prepad;
		पूर्ण

		chip->ecc.calculate(chip, p, oob);

		ret = nand_ग_लिखो_data_op(chip, oob, eccbytes, false);
		अगर (ret)
			वापस ret;

		oob += eccbytes;

		अगर (chip->ecc.postpad) अणु
			ret = nand_ग_लिखो_data_op(chip, oob, chip->ecc.postpad,
						 false);
			अगर (ret)
				वापस ret;

			oob += chip->ecc.postpad;
		पूर्ण
	पूर्ण

	/* Calculate reमुख्यing oob bytes */
	i = mtd->oobsize - (oob - chip->oob_poi);
	अगर (i) अणु
		ret = nand_ग_लिखो_data_op(chip, oob, i, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

/**
 * nand_ग_लिखो_page - ग_लिखो one page
 * @chip: न_अंकD chip descriptor
 * @offset: address offset within the page
 * @data_len: length of actual data to be written
 * @buf: the data to ग_लिखो
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 * @raw: use _raw version of ग_लिखो_page
 */
अटल पूर्णांक nand_ग_लिखो_page(काष्ठा nand_chip *chip, uपूर्णांक32_t offset,
			   पूर्णांक data_len, स्थिर uपूर्णांक8_t *buf, पूर्णांक oob_required,
			   पूर्णांक page, पूर्णांक raw)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक status, subpage;

	अगर (!(chip->options & न_अंकD_NO_SUBPAGE_WRITE) &&
		chip->ecc.ग_लिखो_subpage)
		subpage = offset || (data_len < mtd->ग_लिखोsize);
	अन्यथा
		subpage = 0;

	अगर (unlikely(raw))
		status = chip->ecc.ग_लिखो_page_raw(chip, buf, oob_required,
						  page);
	अन्यथा अगर (subpage)
		status = chip->ecc.ग_लिखो_subpage(chip, offset, data_len, buf,
						 oob_required, page);
	अन्यथा
		status = chip->ecc.ग_लिखो_page(chip, buf, oob_required, page);

	अगर (status < 0)
		वापस status;

	वापस 0;
पूर्ण

#घोषणा NOTALIGNED(x)	((x & (chip->subpagesize - 1)) != 0)

/**
 * nand_करो_ग_लिखो_ops - [INTERN] न_अंकD ग_लिखो with ECC
 * @chip: न_अंकD chip object
 * @to: offset to ग_लिखो to
 * @ops: oob operations description काष्ठाure
 *
 * न_अंकD ग_लिखो with ECC.
 */
अटल पूर्णांक nand_करो_ग_लिखो_ops(काष्ठा nand_chip *chip, loff_t to,
			     काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक chipnr, realpage, page, column;
	uपूर्णांक32_t ग_लिखोlen = ops->len;

	uपूर्णांक32_t oobग_लिखोlen = ops->ooblen;
	uपूर्णांक32_t oobmaxlen = mtd_oobavail(mtd, ops);

	uपूर्णांक8_t *oob = ops->oobbuf;
	uपूर्णांक8_t *buf = ops->datbuf;
	पूर्णांक ret;
	पूर्णांक oob_required = oob ? 1 : 0;

	ops->retlen = 0;
	अगर (!ग_लिखोlen)
		वापस 0;

	/* Reject ग_लिखोs, which are not page aligned */
	अगर (NOTALIGNED(to) || NOTALIGNED(ops->len)) अणु
		pr_notice("%s: attempt to write non page aligned data\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	/* Check अगर the region is secured */
	अगर (nand_region_is_secured(chip, to, ग_लिखोlen))
		वापस -EIO;

	column = to & (mtd->ग_लिखोsize - 1);

	chipnr = (पूर्णांक)(to >> chip->chip_shअगरt);
	nand_select_target(chip, chipnr);

	/* Check, अगर it is ग_लिखो रक्षित */
	अगर (nand_check_wp(chip)) अणु
		ret = -EIO;
		जाओ err_out;
	पूर्ण

	realpage = (पूर्णांक)(to >> chip->page_shअगरt);
	page = realpage & chip->pagemask;

	/* Invalidate the page cache, when we ग_लिखो to the cached page */
	अगर (to <= ((loff_t)chip->pagecache.page << chip->page_shअगरt) &&
	    ((loff_t)chip->pagecache.page << chip->page_shअगरt) < (to + ops->len))
		chip->pagecache.page = -1;

	/* Don't allow multipage oob ग_लिखोs with offset */
	अगर (oob && ops->ooboffs && (ops->ooboffs + ops->ooblen > oobmaxlen)) अणु
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	जबतक (1) अणु
		पूर्णांक bytes = mtd->ग_लिखोsize;
		uपूर्णांक8_t *wbuf = buf;
		पूर्णांक use_bounce_buf;
		पूर्णांक part_pagewr = (column || ग_लिखोlen < mtd->ग_लिखोsize);

		अगर (part_pagewr)
			use_bounce_buf = 1;
		अन्यथा अगर (chip->options & न_अंकD_USES_DMA)
			use_bounce_buf = !virt_addr_valid(buf) ||
					 !IS_ALIGNED((अचिन्हित दीर्घ)buf,
						     chip->buf_align);
		अन्यथा
			use_bounce_buf = 0;

		/*
		 * Copy the data from the initial buffer when करोing partial page
		 * ग_लिखोs or when a bounce buffer is required.
		 */
		अगर (use_bounce_buf) अणु
			pr_debug("%s: using write bounce buffer for buf@%p\n",
					 __func__, buf);
			अगर (part_pagewr)
				bytes = min_t(पूर्णांक, bytes - column, ग_लिखोlen);
			wbuf = nand_get_data_buf(chip);
			स_रखो(wbuf, 0xff, mtd->ग_लिखोsize);
			स_नकल(&wbuf[column], buf, bytes);
		पूर्ण

		अगर (unlikely(oob)) अणु
			माप_प्रकार len = min(oobग_लिखोlen, oobmaxlen);
			oob = nand_fill_oob(chip, oob, len, ops);
			oobग_लिखोlen -= len;
		पूर्ण अन्यथा अणु
			/* We still need to erase leftover OOB data */
			स_रखो(chip->oob_poi, 0xff, mtd->oobsize);
		पूर्ण

		ret = nand_ग_लिखो_page(chip, column, bytes, wbuf,
				      oob_required, page,
				      (ops->mode == MTD_OPS_RAW));
		अगर (ret)
			अवरोध;

		ग_लिखोlen -= bytes;
		अगर (!ग_लिखोlen)
			अवरोध;

		column = 0;
		buf += bytes;
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, अगर we cross a chip boundary */
		अगर (!page) अणु
			chipnr++;
			nand_deselect_target(chip);
			nand_select_target(chip, chipnr);
		पूर्ण
	पूर्ण

	ops->retlen = ops->len - ग_लिखोlen;
	अगर (unlikely(oob))
		ops->oobretlen = ops->ooblen;

err_out:
	nand_deselect_target(chip);
	वापस ret;
पूर्ण

/**
 * panic_nand_ग_लिखो - [MTD Interface] न_अंकD ग_लिखो with ECC
 * @mtd: MTD device काष्ठाure
 * @to: offset to ग_लिखो to
 * @len: number of bytes to ग_लिखो
 * @retlen: poपूर्णांकer to variable to store the number of written bytes
 * @buf: the data to ग_लिखो
 *
 * न_अंकD ग_लिखो with ECC. Used when perक्रमming ग_लिखोs in पूर्णांकerrupt context, this
 * may क्रम example be called by mtकरोops when writing an oops जबतक in panic.
 */
अटल पूर्णांक panic_nand_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			    माप_प्रकार *retlen, स्थिर uपूर्णांक8_t *buf)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	पूर्णांक chipnr = (पूर्णांक)(to >> chip->chip_shअगरt);
	काष्ठा mtd_oob_ops ops;
	पूर्णांक ret;

	nand_select_target(chip, chipnr);

	/* Wait क्रम the device to get पढ़ोy */
	panic_nand_रुको(chip, 400);

	स_रखो(&ops, 0, माप(ops));
	ops.len = len;
	ops.datbuf = (uपूर्णांक8_t *)buf;
	ops.mode = MTD_OPS_PLACE_OOB;

	ret = nand_करो_ग_लिखो_ops(chip, to, &ops);

	*retlen = ops.retlen;
	वापस ret;
पूर्ण

/**
 * nand_ग_लिखो_oob - [MTD Interface] न_अंकD ग_लिखो data and/or out-of-band
 * @mtd: MTD device काष्ठाure
 * @to: offset to ग_लिखो to
 * @ops: oob operation description काष्ठाure
 */
अटल पूर्णांक nand_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t to,
			  काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	पूर्णांक ret;

	ops->retlen = 0;

	ret = nand_get_device(chip);
	अगर (ret)
		वापस ret;

	चयन (ops->mode) अणु
	हाल MTD_OPS_PLACE_OOB:
	हाल MTD_OPS_AUTO_OOB:
	हाल MTD_OPS_RAW:
		अवरोध;

	शेष:
		जाओ out;
	पूर्ण

	अगर (!ops->datbuf)
		ret = nand_करो_ग_लिखो_oob(chip, to, ops);
	अन्यथा
		ret = nand_करो_ग_लिखो_ops(chip, to, ops);

out:
	nand_release_device(chip);
	वापस ret;
पूर्ण

/**
 * nand_erase - [MTD Interface] erase block(s)
 * @mtd: MTD device काष्ठाure
 * @instr: erase inकाष्ठाion
 *
 * Erase one ore more blocks.
 */
अटल पूर्णांक nand_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	वापस nand_erase_nand(mtd_to_nand(mtd), instr, 0);
पूर्ण

/**
 * nand_erase_nand - [INTERN] erase block(s)
 * @chip: न_अंकD chip object
 * @instr: erase inकाष्ठाion
 * @allowbbt: allow erasing the bbt area
 *
 * Erase one ore more blocks.
 */
पूर्णांक nand_erase_nand(काष्ठा nand_chip *chip, काष्ठा erase_info *instr,
		    पूर्णांक allowbbt)
अणु
	पूर्णांक page, pages_per_block, ret, chipnr;
	loff_t len;

	pr_debug("%s: start = 0x%012llx, len = %llu\n",
			__func__, (अचिन्हित दीर्घ दीर्घ)instr->addr,
			(अचिन्हित दीर्घ दीर्घ)instr->len);

	अगर (check_offs_len(chip, instr->addr, instr->len))
		वापस -EINVAL;

	/* Check अगर the region is secured */
	अगर (nand_region_is_secured(chip, instr->addr, instr->len))
		वापस -EIO;

	/* Grab the lock and see अगर the device is available */
	ret = nand_get_device(chip);
	अगर (ret)
		वापस ret;

	/* Shअगरt to get first page */
	page = (पूर्णांक)(instr->addr >> chip->page_shअगरt);
	chipnr = (पूर्णांक)(instr->addr >> chip->chip_shअगरt);

	/* Calculate pages in each block */
	pages_per_block = 1 << (chip->phys_erase_shअगरt - chip->page_shअगरt);

	/* Select the न_अंकD device */
	nand_select_target(chip, chipnr);

	/* Check, अगर it is ग_लिखो रक्षित */
	अगर (nand_check_wp(chip)) अणु
		pr_debug("%s: device is write protected!\n",
				__func__);
		ret = -EIO;
		जाओ erase_निकास;
	पूर्ण

	/* Loop through the pages */
	len = instr->len;

	जबतक (len) अणु
		/* Check अगर we have a bad block, we करो not erase bad blocks! */
		अगर (nand_block_checkbad(chip, ((loff_t) page) <<
					chip->page_shअगरt, allowbbt)) अणु
			pr_warn("%s: attempt to erase a bad block at page 0x%08x\n",
				    __func__, page);
			ret = -EIO;
			जाओ erase_निकास;
		पूर्ण

		/*
		 * Invalidate the page cache, अगर we erase the block which
		 * contains the current cached page.
		 */
		अगर (page <= chip->pagecache.page && chip->pagecache.page <
		    (page + pages_per_block))
			chip->pagecache.page = -1;

		ret = nand_erase_op(chip, (page & chip->pagemask) >>
				    (chip->phys_erase_shअगरt - chip->page_shअगरt));
		अगर (ret) अणु
			pr_debug("%s: failed erase, page 0x%08x\n",
					__func__, page);
			instr->fail_addr =
				((loff_t)page << chip->page_shअगरt);
			जाओ erase_निकास;
		पूर्ण

		/* Increment page address and decrement length */
		len -= (1ULL << chip->phys_erase_shअगरt);
		page += pages_per_block;

		/* Check, अगर we cross a chip boundary */
		अगर (len && !(page & chip->pagemask)) अणु
			chipnr++;
			nand_deselect_target(chip);
			nand_select_target(chip, chipnr);
		पूर्ण
	पूर्ण

	ret = 0;
erase_निकास:

	/* Deselect and wake up anyone रुकोing on the device */
	nand_deselect_target(chip);
	nand_release_device(chip);

	/* Return more or less happy */
	वापस ret;
पूर्ण

/**
 * nand_sync - [MTD Interface] sync
 * @mtd: MTD device काष्ठाure
 *
 * Sync is actually a रुको क्रम chip पढ़ोy function.
 */
अटल व्योम nand_sync(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	pr_debug("%s: called\n", __func__);

	/* Grab the lock and see अगर the device is available */
	WARN_ON(nand_get_device(chip));
	/* Release it and go back */
	nand_release_device(chip);
पूर्ण

/**
 * nand_block_isbad - [MTD Interface] Check अगर block at offset is bad
 * @mtd: MTD device काष्ठाure
 * @offs: offset relative to mtd start
 */
अटल पूर्णांक nand_block_isbad(काष्ठा mtd_info *mtd, loff_t offs)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	पूर्णांक chipnr = (पूर्णांक)(offs >> chip->chip_shअगरt);
	पूर्णांक ret;

	/* Select the न_अंकD device */
	ret = nand_get_device(chip);
	अगर (ret)
		वापस ret;

	nand_select_target(chip, chipnr);

	ret = nand_block_checkbad(chip, offs, 0);

	nand_deselect_target(chip);
	nand_release_device(chip);

	वापस ret;
पूर्ण

/**
 * nand_block_markbad - [MTD Interface] Mark block at the given offset as bad
 * @mtd: MTD device काष्ठाure
 * @ofs: offset relative to mtd start
 */
अटल पूर्णांक nand_block_markbad(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	पूर्णांक ret;

	ret = nand_block_isbad(mtd, ofs);
	अगर (ret) अणु
		/* If it was bad alपढ़ोy, वापस success and करो nothing */
		अगर (ret > 0)
			वापस 0;
		वापस ret;
	पूर्ण

	वापस nand_block_markbad_lowlevel(mtd_to_nand(mtd), ofs);
पूर्ण

/**
 * nand_suspend - [MTD Interface] Suspend the न_अंकD flash
 * @mtd: MTD device काष्ठाure
 *
 * Returns 0 क्रम success or negative error code otherwise.
 */
अटल पूर्णांक nand_suspend(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);
	अगर (chip->ops.suspend)
		ret = chip->ops.suspend(chip);
	अगर (!ret)
		chip->suspended = 1;
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

/**
 * nand_resume - [MTD Interface] Resume the न_अंकD flash
 * @mtd: MTD device काष्ठाure
 */
अटल व्योम nand_resume(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	mutex_lock(&chip->lock);
	अगर (chip->suspended) अणु
		अगर (chip->ops.resume)
			chip->ops.resume(chip);
		chip->suspended = 0;
	पूर्ण अन्यथा अणु
		pr_err("%s called for a chip which is not in suspended state\n",
			__func__);
	पूर्ण
	mutex_unlock(&chip->lock);
पूर्ण

/**
 * nand_shutकरोwn - [MTD Interface] Finish the current न_अंकD operation and
 *                 prevent further operations
 * @mtd: MTD device काष्ठाure
 */
अटल व्योम nand_shutकरोwn(काष्ठा mtd_info *mtd)
अणु
	nand_suspend(mtd);
पूर्ण

/**
 * nand_lock - [MTD Interface] Lock the न_अंकD flash
 * @mtd: MTD device काष्ठाure
 * @ofs: offset byte address
 * @len: number of bytes to lock (must be a multiple of block/page size)
 */
अटल पूर्णांक nand_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (!chip->ops.lock_area)
		वापस -ENOTSUPP;

	वापस chip->ops.lock_area(chip, ofs, len);
पूर्ण

/**
 * nand_unlock - [MTD Interface] Unlock the न_अंकD flash
 * @mtd: MTD device काष्ठाure
 * @ofs: offset byte address
 * @len: number of bytes to unlock (must be a multiple of block/page size)
 */
अटल पूर्णांक nand_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (!chip->ops.unlock_area)
		वापस -ENOTSUPP;

	वापस chip->ops.unlock_area(chip, ofs, len);
पूर्ण

/* Set शेष functions */
अटल व्योम nand_set_शेषs(काष्ठा nand_chip *chip)
अणु
	/* If no controller is provided, use the dummy, legacy one. */
	अगर (!chip->controller) अणु
		chip->controller = &chip->legacy.dummy_controller;
		nand_controller_init(chip->controller);
	पूर्ण

	nand_legacy_set_शेषs(chip);

	अगर (!chip->buf_align)
		chip->buf_align = 1;
पूर्ण

/* Sanitize ONFI strings so we can safely prपूर्णांक them */
व्योम sanitize_string(uपूर्णांक8_t *s, माप_प्रकार len)
अणु
	sमाप_प्रकार i;

	/* Null terminate */
	s[len - 1] = 0;

	/* Remove non prपूर्णांकable अक्षरs */
	क्रम (i = 0; i < len - 1; i++) अणु
		अगर (s[i] < ' ' || s[i] > 127)
			s[i] = '?';
	पूर्ण

	/* Remove trailing spaces */
	strim(s);
पूर्ण

/*
 * nand_id_has_period - Check अगर an ID string has a given wraparound period
 * @id_data: the ID string
 * @arrlen: the length of the @id_data array
 * @period: the period of repitition
 *
 * Check अगर an ID string is repeated within a given sequence of bytes at
 * specअगरic repetition पूर्णांकerval period (e.g., अणु0x20,0x01,0x7F,0x20पूर्ण has a
 * period of 3). This is a helper function क्रम nand_id_len(). Returns non-zero
 * अगर the repetition has a period of @period; otherwise, वापसs zero.
 */
अटल पूर्णांक nand_id_has_period(u8 *id_data, पूर्णांक arrlen, पूर्णांक period)
अणु
	पूर्णांक i, j;
	क्रम (i = 0; i < period; i++)
		क्रम (j = i + period; j < arrlen; j += period)
			अगर (id_data[i] != id_data[j])
				वापस 0;
	वापस 1;
पूर्ण

/*
 * nand_id_len - Get the length of an ID string वापसed by CMD_READID
 * @id_data: the ID string
 * @arrlen: the length of the @id_data array

 * Returns the length of the ID string, according to known wraparound/trailing
 * zero patterns. If no pattern exists, वापसs the length of the array.
 */
अटल पूर्णांक nand_id_len(u8 *id_data, पूर्णांक arrlen)
अणु
	पूर्णांक last_nonzero, period;

	/* Find last non-zero byte */
	क्रम (last_nonzero = arrlen - 1; last_nonzero >= 0; last_nonzero--)
		अगर (id_data[last_nonzero])
			अवरोध;

	/* All zeros */
	अगर (last_nonzero < 0)
		वापस 0;

	/* Calculate wraparound period */
	क्रम (period = 1; period < arrlen; period++)
		अगर (nand_id_has_period(id_data, arrlen, period))
			अवरोध;

	/* There's a repeated pattern */
	अगर (period < arrlen)
		वापस period;

	/* There are trailing zeros */
	अगर (last_nonzero < arrlen - 1)
		वापस last_nonzero + 1;

	/* No pattern detected */
	वापस arrlen;
पूर्ण

/* Extract the bits of per cell from the 3rd byte of the extended ID */
अटल पूर्णांक nand_get_bits_per_cell(u8 cellinfo)
अणु
	पूर्णांक bits;

	bits = cellinfo & न_अंकD_CI_CELLTYPE_MSK;
	bits >>= न_अंकD_CI_CELLTYPE_SHIFT;
	वापस bits + 1;
पूर्ण

/*
 * Many new न_अंकD share similar device ID codes, which represent the size of the
 * chip. The rest of the parameters must be decoded according to generic or
 * manufacturer-specअगरic "extended ID" decoding patterns.
 */
व्योम nand_decode_ext_id(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_memory_organization *memorg;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक extid;
	u8 *id_data = chip->id.data;

	memorg = nanddev_get_memorg(&chip->base);

	/* The 3rd id byte holds MLC / multichip data */
	memorg->bits_per_cell = nand_get_bits_per_cell(id_data[2]);
	/* The 4th id byte is the important one */
	extid = id_data[3];

	/* Calc pagesize */
	memorg->pagesize = 1024 << (extid & 0x03);
	mtd->ग_लिखोsize = memorg->pagesize;
	extid >>= 2;
	/* Calc oobsize */
	memorg->oobsize = (8 << (extid & 0x01)) * (mtd->ग_लिखोsize >> 9);
	mtd->oobsize = memorg->oobsize;
	extid >>= 2;
	/* Calc blocksize. Blocksize is multiples of 64KiB */
	memorg->pages_per_eraseblock = ((64 * 1024) << (extid & 0x03)) /
				       memorg->pagesize;
	mtd->erasesize = (64 * 1024) << (extid & 0x03);
	extid >>= 2;
	/* Get buswidth inक्रमmation */
	अगर (extid & 0x1)
		chip->options |= न_अंकD_BUSWIDTH_16;
पूर्ण
EXPORT_SYMBOL_GPL(nand_decode_ext_id);

/*
 * Old devices have chip data hardcoded in the device ID table. nand_decode_id
 * decodes a matching ID table entry and assigns the MTD size parameters क्रम
 * the chip.
 */
अटल व्योम nand_decode_id(काष्ठा nand_chip *chip, काष्ठा nand_flash_dev *type)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;

	memorg = nanddev_get_memorg(&chip->base);

	memorg->pages_per_eraseblock = type->erasesize / type->pagesize;
	mtd->erasesize = type->erasesize;
	memorg->pagesize = type->pagesize;
	mtd->ग_लिखोsize = memorg->pagesize;
	memorg->oobsize = memorg->pagesize / 32;
	mtd->oobsize = memorg->oobsize;

	/* All legacy ID न_अंकD are small-page, SLC */
	memorg->bits_per_cell = 1;
पूर्ण

/*
 * Set the bad block marker/indicator (BBM/BBI) patterns according to some
 * heuristic patterns using various detected parameters (e.g., manufacturer,
 * page size, cell-type inक्रमmation).
 */
अटल व्योम nand_decode_bbm_options(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/* Set the bad block position */
	अगर (mtd->ग_लिखोsize > 512 || (chip->options & न_अंकD_BUSWIDTH_16))
		chip->badblockpos = न_अंकD_BBM_POS_LARGE;
	अन्यथा
		chip->badblockpos = न_अंकD_BBM_POS_SMALL;
पूर्ण

अटल अंतरभूत bool is_full_id_nand(काष्ठा nand_flash_dev *type)
अणु
	वापस type->id_len;
पूर्ण

अटल bool find_full_id_nand(काष्ठा nand_chip *chip,
			      काष्ठा nand_flash_dev *type)
अणु
	काष्ठा nand_device *base = &chip->base;
	काष्ठा nand_ecc_props requirements;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;
	u8 *id_data = chip->id.data;

	memorg = nanddev_get_memorg(&chip->base);

	अगर (!म_भेदन(type->id, id_data, type->id_len)) अणु
		memorg->pagesize = type->pagesize;
		mtd->ग_लिखोsize = memorg->pagesize;
		memorg->pages_per_eraseblock = type->erasesize /
					       type->pagesize;
		mtd->erasesize = type->erasesize;
		memorg->oobsize = type->oobsize;
		mtd->oobsize = memorg->oobsize;

		memorg->bits_per_cell = nand_get_bits_per_cell(id_data[2]);
		memorg->eraseblocks_per_lun =
			DIV_ROUND_DOWN_ULL((u64)type->chipsize << 20,
					   memorg->pagesize *
					   memorg->pages_per_eraseblock);
		chip->options |= type->options;
		requirements.strength = न_अंकD_ECC_STRENGTH(type);
		requirements.step_size = न_अंकD_ECC_STEP(type);
		nanddev_set_ecc_requirements(base, &requirements);

		chip->parameters.model = kstrdup(type->name, GFP_KERNEL);
		अगर (!chip->parameters.model)
			वापस false;

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Manufacturer detection. Only used when the न_अंकD is not ONFI or JEDEC
 * compliant and करोes not have a full-id or legacy-id entry in the nand_ids
 * table.
 */
अटल व्योम nand_manufacturer_detect(काष्ठा nand_chip *chip)
अणु
	/*
	 * Try manufacturer detection अगर available and use
	 * nand_decode_ext_id() otherwise.
	 */
	अगर (chip->manufacturer.desc && chip->manufacturer.desc->ops &&
	    chip->manufacturer.desc->ops->detect) अणु
		काष्ठा nand_memory_organization *memorg;

		memorg = nanddev_get_memorg(&chip->base);

		/* The 3rd id byte holds MLC / multichip data */
		memorg->bits_per_cell = nand_get_bits_per_cell(chip->id.data[2]);
		chip->manufacturer.desc->ops->detect(chip);
	पूर्ण अन्यथा अणु
		nand_decode_ext_id(chip);
	पूर्ण
पूर्ण

/*
 * Manufacturer initialization. This function is called क्रम all न_अंकDs including
 * ONFI and JEDEC compliant ones.
 * Manufacturer drivers should put all their specअगरic initialization code in
 * their ->init() hook.
 */
अटल पूर्णांक nand_manufacturer_init(काष्ठा nand_chip *chip)
अणु
	अगर (!chip->manufacturer.desc || !chip->manufacturer.desc->ops ||
	    !chip->manufacturer.desc->ops->init)
		वापस 0;

	वापस chip->manufacturer.desc->ops->init(chip);
पूर्ण

/*
 * Manufacturer cleanup. This function is called क्रम all न_अंकDs including
 * ONFI and JEDEC compliant ones.
 * Manufacturer drivers should put all their specअगरic cleanup code in their
 * ->cleanup() hook.
 */
अटल व्योम nand_manufacturer_cleanup(काष्ठा nand_chip *chip)
अणु
	/* Release manufacturer निजी data */
	अगर (chip->manufacturer.desc && chip->manufacturer.desc->ops &&
	    chip->manufacturer.desc->ops->cleanup)
		chip->manufacturer.desc->ops->cleanup(chip);
पूर्ण

अटल स्थिर अक्षर *
nand_manufacturer_name(स्थिर काष्ठा nand_manufacturer_desc *manufacturer_desc)
अणु
	वापस manufacturer_desc ? manufacturer_desc->name : "Unknown";
पूर्ण

/*
 * Get the flash and manufacturer id and lookup अगर the type is supported.
 */
अटल पूर्णांक nand_detect(काष्ठा nand_chip *chip, काष्ठा nand_flash_dev *type)
अणु
	स्थिर काष्ठा nand_manufacturer_desc *manufacturer_desc;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;
	पूर्णांक busw, ret;
	u8 *id_data = chip->id.data;
	u8 maf_id, dev_id;
	u64 tarमाला_लोize;

	/*
	 * Let's start by initializing memorg fields that might be left
	 * unasचिन्हित by the ID-based detection logic.
	 */
	memorg = nanddev_get_memorg(&chip->base);
	memorg->planes_per_lun = 1;
	memorg->luns_per_target = 1;

	/*
	 * Reset the chip, required by some chips (e.g. Micron MT29FxGxxxxx)
	 * after घातer-up.
	 */
	ret = nand_reset(chip, 0);
	अगर (ret)
		वापस ret;

	/* Select the device */
	nand_select_target(chip, 0);

	/* Send the command क्रम पढ़ोing device ID */
	ret = nand_पढ़ोid_op(chip, 0, id_data, 2);
	अगर (ret)
		वापस ret;

	/* Read manufacturer and device IDs */
	maf_id = id_data[0];
	dev_id = id_data[1];

	/*
	 * Try again to make sure, as some प्रणालीs the bus-hold or other
	 * पूर्णांकerface concerns can cause अक्रमom data which looks like a
	 * possibly credible न_अंकD flash to appear. If the two results करो
	 * not match, ignore the device completely.
	 */

	/* Read entire ID string */
	ret = nand_पढ़ोid_op(chip, 0, id_data, माप(chip->id.data));
	अगर (ret)
		वापस ret;

	अगर (id_data[0] != maf_id || id_data[1] != dev_id) अणु
		pr_info("second ID read did not match %02x,%02x against %02x,%02x\n",
			maf_id, dev_id, id_data[0], id_data[1]);
		वापस -ENODEV;
	पूर्ण

	chip->id.len = nand_id_len(id_data, ARRAY_SIZE(chip->id.data));

	/* Try to identअगरy manufacturer */
	manufacturer_desc = nand_get_manufacturer_desc(maf_id);
	chip->manufacturer.desc = manufacturer_desc;

	अगर (!type)
		type = nand_flash_ids;

	/*
	 * Save the न_अंकD_BUSWIDTH_16 flag beक्रमe letting स्वतः-detection logic
	 * override it.
	 * This is required to make sure initial न_अंकD bus width set by the
	 * न_अंकD controller driver is coherent with the real न_अंकD bus width
	 * (extracted by स्वतः-detection code).
	 */
	busw = chip->options & न_अंकD_BUSWIDTH_16;

	/*
	 * The flag is only set (never cleared), reset it to its शेष value
	 * beक्रमe starting स्वतः-detection.
	 */
	chip->options &= ~न_अंकD_BUSWIDTH_16;

	क्रम (; type->name != शून्य; type++) अणु
		अगर (is_full_id_nand(type)) अणु
			अगर (find_full_id_nand(chip, type))
				जाओ ident_करोne;
		पूर्ण अन्यथा अगर (dev_id == type->dev_id) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!type->name || !type->pagesize) अणु
		/* Check अगर the chip is ONFI compliant */
		ret = nand_onfi_detect(chip);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret)
			जाओ ident_करोne;

		/* Check अगर the chip is JEDEC compliant */
		ret = nand_jedec_detect(chip);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret)
			जाओ ident_करोne;
	पूर्ण

	अगर (!type->name)
		वापस -ENODEV;

	chip->parameters.model = kstrdup(type->name, GFP_KERNEL);
	अगर (!chip->parameters.model)
		वापस -ENOMEM;

	अगर (!type->pagesize)
		nand_manufacturer_detect(chip);
	अन्यथा
		nand_decode_id(chip, type);

	/* Get chip options */
	chip->options |= type->options;

	memorg->eraseblocks_per_lun =
			DIV_ROUND_DOWN_ULL((u64)type->chipsize << 20,
					   memorg->pagesize *
					   memorg->pages_per_eraseblock);

ident_करोne:
	अगर (!mtd->name)
		mtd->name = chip->parameters.model;

	अगर (chip->options & न_अंकD_BUSWIDTH_AUTO) अणु
		WARN_ON(busw & न_अंकD_BUSWIDTH_16);
		nand_set_शेषs(chip);
	पूर्ण अन्यथा अगर (busw != (chip->options & न_अंकD_BUSWIDTH_16)) अणु
		/*
		 * Check, अगर buswidth is correct. Hardware drivers should set
		 * chip correct!
		 */
		pr_info("device found, Manufacturer ID: 0x%02x, Chip ID: 0x%02x\n",
			maf_id, dev_id);
		pr_info("%s %s\n", nand_manufacturer_name(manufacturer_desc),
			mtd->name);
		pr_warn("bus width %d instead of %d bits\n", busw ? 16 : 8,
			(chip->options & न_अंकD_BUSWIDTH_16) ? 16 : 8);
		ret = -EINVAL;

		जाओ मुक्त_detect_allocation;
	पूर्ण

	nand_decode_bbm_options(chip);

	/* Calculate the address shअगरt from the page size */
	chip->page_shअगरt = ffs(mtd->ग_लिखोsize) - 1;
	/* Convert chipsize to number of pages per chip -1 */
	tarमाला_लोize = nanddev_target_size(&chip->base);
	chip->pagemask = (tarमाला_लोize >> chip->page_shअगरt) - 1;

	chip->bbt_erase_shअगरt = chip->phys_erase_shअगरt =
		ffs(mtd->erasesize) - 1;
	अगर (tarमाला_लोize & 0xffffffff)
		chip->chip_shअगरt = ffs((अचिन्हित)tarमाला_लोize) - 1;
	अन्यथा अणु
		chip->chip_shअगरt = ffs((अचिन्हित)(tarमाला_लोize >> 32));
		chip->chip_shअगरt += 32 - 1;
	पूर्ण

	अगर (chip->chip_shअगरt - chip->page_shअगरt > 16)
		chip->options |= न_अंकD_ROW_ADDR_3;

	chip->badblockbits = 8;

	nand_legacy_adjust_cmdfunc(chip);

	pr_info("device found, Manufacturer ID: 0x%02x, Chip ID: 0x%02x\n",
		maf_id, dev_id);
	pr_info("%s %s\n", nand_manufacturer_name(manufacturer_desc),
		chip->parameters.model);
	pr_info("%d MiB, %s, erase size: %d KiB, page size: %d, OOB size: %d\n",
		(पूर्णांक)(tarमाला_लोize >> 20), nand_is_slc(chip) ? "SLC" : "MLC",
		mtd->erasesize >> 10, mtd->ग_लिखोsize, mtd->oobsize);
	वापस 0;

मुक्त_detect_allocation:
	kमुक्त(chip->parameters.model);

	वापस ret;
पूर्ण

अटल क्रमागत nand_ecc_engine_type
of_get_rawnand_ecc_engine_type_legacy(काष्ठा device_node *np)
अणु
	क्रमागत nand_ecc_legacy_mode अणु
		न_अंकD_ECC_INVALID,
		न_अंकD_ECC_NONE,
		न_अंकD_ECC_SOFT,
		न_अंकD_ECC_SOFT_BCH,
		न_अंकD_ECC_HW,
		न_अंकD_ECC_HW_SYNDROME,
		न_अंकD_ECC_ON_DIE,
	पूर्ण;
	स्थिर अक्षर * स्थिर nand_ecc_legacy_modes[] = अणु
		[न_अंकD_ECC_NONE]		= "none",
		[न_अंकD_ECC_SOFT]		= "soft",
		[न_अंकD_ECC_SOFT_BCH]	= "soft_bch",
		[न_अंकD_ECC_HW]		= "hw",
		[न_अंकD_ECC_HW_SYNDROME]	= "hw_syndrome",
		[न_अंकD_ECC_ON_DIE]	= "on-die",
	पूर्ण;
	क्रमागत nand_ecc_legacy_mode eng_type;
	स्थिर अक्षर *pm;
	पूर्णांक err;

	err = of_property_पढ़ो_string(np, "nand-ecc-mode", &pm);
	अगर (err)
		वापस न_अंकD_ECC_ENGINE_TYPE_INVALID;

	क्रम (eng_type = न_अंकD_ECC_NONE;
	     eng_type < ARRAY_SIZE(nand_ecc_legacy_modes); eng_type++) अणु
		अगर (!strहालcmp(pm, nand_ecc_legacy_modes[eng_type])) अणु
			चयन (eng_type) अणु
			हाल न_अंकD_ECC_NONE:
				वापस न_अंकD_ECC_ENGINE_TYPE_NONE;
			हाल न_अंकD_ECC_SOFT:
			हाल न_अंकD_ECC_SOFT_BCH:
				वापस न_अंकD_ECC_ENGINE_TYPE_SOFT;
			हाल न_अंकD_ECC_HW:
			हाल न_अंकD_ECC_HW_SYNDROME:
				वापस न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
			हाल न_अंकD_ECC_ON_DIE:
				वापस न_अंकD_ECC_ENGINE_TYPE_ON_DIE;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस न_अंकD_ECC_ENGINE_TYPE_INVALID;
पूर्ण

अटल क्रमागत nand_ecc_placement
of_get_rawnand_ecc_placement_legacy(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *pm;
	पूर्णांक err;

	err = of_property_पढ़ो_string(np, "nand-ecc-mode", &pm);
	अगर (!err) अणु
		अगर (!strहालcmp(pm, "hw_syndrome"))
			वापस न_अंकD_ECC_PLACEMENT_INTERLEAVED;
	पूर्ण

	वापस न_अंकD_ECC_PLACEMENT_UNKNOWN;
पूर्ण

अटल क्रमागत nand_ecc_algo of_get_rawnand_ecc_algo_legacy(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *pm;
	पूर्णांक err;

	err = of_property_पढ़ो_string(np, "nand-ecc-mode", &pm);
	अगर (!err) अणु
		अगर (!strहालcmp(pm, "soft"))
			वापस न_अंकD_ECC_ALGO_HAMMING;
		अन्यथा अगर (!strहालcmp(pm, "soft_bch"))
			वापस न_अंकD_ECC_ALGO_BCH;
	पूर्ण

	वापस न_अंकD_ECC_ALGO_UNKNOWN;
पूर्ण

अटल व्योम of_get_nand_ecc_legacy_user_config(काष्ठा nand_chip *chip)
अणु
	काष्ठा device_node *dn = nand_get_flash_node(chip);
	काष्ठा nand_ecc_props *user_conf = &chip->base.ecc.user_conf;

	अगर (user_conf->engine_type == न_अंकD_ECC_ENGINE_TYPE_INVALID)
		user_conf->engine_type = of_get_rawnand_ecc_engine_type_legacy(dn);

	अगर (user_conf->algo == न_अंकD_ECC_ALGO_UNKNOWN)
		user_conf->algo = of_get_rawnand_ecc_algo_legacy(dn);

	अगर (user_conf->placement == न_अंकD_ECC_PLACEMENT_UNKNOWN)
		user_conf->placement = of_get_rawnand_ecc_placement_legacy(dn);
पूर्ण

अटल पूर्णांक of_get_nand_bus_width(काष्ठा device_node *np)
अणु
	u32 val;

	अगर (of_property_पढ़ो_u32(np, "nand-bus-width", &val))
		वापस 8;

	चयन (val) अणु
	हाल 8:
	हाल 16:
		वापस val;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल bool of_get_nand_on_flash_bbt(काष्ठा device_node *np)
अणु
	वापस of_property_पढ़ो_bool(np, "nand-on-flash-bbt");
पूर्ण

अटल पूर्णांक of_get_nand_secure_regions(काष्ठा nand_chip *chip)
अणु
	काष्ठा device_node *dn = nand_get_flash_node(chip);
	पूर्णांक nr_elem, i, j;

	nr_elem = of_property_count_elems_of_size(dn, "secure-regions", माप(u64));
	अगर (!nr_elem)
		वापस 0;

	chip->nr_secure_regions = nr_elem / 2;
	chip->secure_regions = kसुस्मृति(chip->nr_secure_regions, माप(*chip->secure_regions),
				       GFP_KERNEL);
	अगर (!chip->secure_regions)
		वापस -ENOMEM;

	क्रम (i = 0, j = 0; i < chip->nr_secure_regions; i++, j += 2) अणु
		of_property_पढ़ो_u64_index(dn, "secure-regions", j,
					   &chip->secure_regions[i].offset);
		of_property_पढ़ो_u64_index(dn, "secure-regions", j + 1,
					   &chip->secure_regions[i].size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rawnand_dt_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(nand_to_mtd(chip));
	काष्ठा device_node *dn = nand_get_flash_node(chip);

	अगर (!dn)
		वापस 0;

	अगर (of_get_nand_bus_width(dn) == 16)
		chip->options |= न_अंकD_BUSWIDTH_16;

	अगर (of_property_पढ़ो_bool(dn, "nand-is-boot-medium"))
		chip->options |= न_अंकD_IS_BOOT_MEDIUM;

	अगर (of_get_nand_on_flash_bbt(dn))
		chip->bbt_options |= न_अंकD_BBT_USE_FLASH;

	of_get_nand_ecc_user_config(nand);
	of_get_nand_ecc_legacy_user_config(chip);

	/*
	 * If neither the user nor the न_अंकD controller have requested a specअगरic
	 * ECC engine type, we will शेष to न_अंकD_ECC_ENGINE_TYPE_ON_HOST.
	 */
	nand->ecc.शेषs.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;

	/*
	 * Use the user requested engine type, unless there is none, in this
	 * हाल शेष to the न_अंकD controller choice, otherwise fallback to
	 * the raw न_अंकD शेष one.
	 */
	अगर (nand->ecc.user_conf.engine_type != न_अंकD_ECC_ENGINE_TYPE_INVALID)
		chip->ecc.engine_type = nand->ecc.user_conf.engine_type;
	अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_INVALID)
		chip->ecc.engine_type = nand->ecc.शेषs.engine_type;

	chip->ecc.placement = nand->ecc.user_conf.placement;
	chip->ecc.algo = nand->ecc.user_conf.algo;
	chip->ecc.strength = nand->ecc.user_conf.strength;
	chip->ecc.size = nand->ecc.user_conf.step_size;

	वापस 0;
पूर्ण

/**
 * nand_scan_ident - Scan क्रम the न_अंकD device
 * @chip: न_अंकD chip object
 * @maxchips: number of chips to scan क्रम
 * @table: alternative न_अंकD ID table
 *
 * This is the first phase of the normal nand_scan() function. It पढ़ोs the
 * flash ID and sets up MTD fields accordingly.
 *
 * This helper used to be called directly from controller drivers that needed
 * to tweak some ECC-related parameters beक्रमe nand_scan_tail(). This separation
 * prevented dynamic allocations during this phase which was unconvenient and
 * as been banned क्रम the benefit of the ->init_ecc()/cleanup_ecc() hooks.
 */
अटल पूर्णांक nand_scan_ident(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक maxchips,
			   काष्ठा nand_flash_dev *table)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;
	पूर्णांक nand_maf_id, nand_dev_id;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	memorg = nanddev_get_memorg(&chip->base);

	/* Assume all dies are deselected when we enter nand_scan_ident(). */
	chip->cur_cs = -1;

	mutex_init(&chip->lock);

	/* Enक्रमce the right timings क्रम reset/detection */
	chip->current_पूर्णांकerface_config = nand_get_reset_पूर्णांकerface_config();

	ret = rawnand_dt_init(chip);
	अगर (ret)
		वापस ret;

	अगर (!mtd->name && mtd->dev.parent)
		mtd->name = dev_name(mtd->dev.parent);

	/* Set the शेष functions */
	nand_set_शेषs(chip);

	ret = nand_legacy_check_hooks(chip);
	अगर (ret)
		वापस ret;

	memorg->ntarमाला_लो = maxchips;

	/* Read the flash type */
	ret = nand_detect(chip, table);
	अगर (ret) अणु
		अगर (!(chip->options & न_अंकD_SCAN_SILENT_NODEV))
			pr_warn("No NAND device found\n");
		nand_deselect_target(chip);
		वापस ret;
	पूर्ण

	nand_maf_id = chip->id.data[0];
	nand_dev_id = chip->id.data[1];

	nand_deselect_target(chip);

	/* Check क्रम a chip array */
	क्रम (i = 1; i < maxchips; i++) अणु
		u8 id[2];

		/* See comment in nand_get_flash_type क्रम reset */
		ret = nand_reset(chip, i);
		अगर (ret)
			अवरोध;

		nand_select_target(chip, i);
		/* Send the command क्रम पढ़ोing device ID */
		ret = nand_पढ़ोid_op(chip, 0, id, माप(id));
		अगर (ret)
			अवरोध;
		/* Read manufacturer and device IDs */
		अगर (nand_maf_id != id[0] || nand_dev_id != id[1]) अणु
			nand_deselect_target(chip);
			अवरोध;
		पूर्ण
		nand_deselect_target(chip);
	पूर्ण
	अगर (i > 1)
		pr_info("%d chips detected\n", i);

	/* Store the number of chips and calc total size क्रम mtd */
	memorg->ntarमाला_लो = i;
	mtd->size = i * nanddev_target_size(&chip->base);

	वापस 0;
पूर्ण

अटल व्योम nand_scan_ident_cleanup(काष्ठा nand_chip *chip)
अणु
	kमुक्त(chip->parameters.model);
	kमुक्त(chip->parameters.onfi);
पूर्ण

पूर्णांक rawnand_sw_hamming_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_ecc_sw_hamming_conf *engine_conf;
	काष्ठा nand_device *base = &chip->base;
	पूर्णांक ret;

	base->ecc.user_conf.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
	base->ecc.user_conf.algo = न_अंकD_ECC_ALGO_HAMMING;
	base->ecc.user_conf.strength = chip->ecc.strength;
	base->ecc.user_conf.step_size = chip->ecc.size;

	ret = nand_ecc_sw_hamming_init_ctx(base);
	अगर (ret)
		वापस ret;

	engine_conf = base->ecc.ctx.priv;

	अगर (chip->ecc.options & न_अंकD_ECC_SOFT_HAMMING_SM_ORDER)
		engine_conf->sm_order = true;

	chip->ecc.size = base->ecc.ctx.conf.step_size;
	chip->ecc.strength = base->ecc.ctx.conf.strength;
	chip->ecc.total = base->ecc.ctx.total;
	chip->ecc.steps = nanddev_get_ecc_nsteps(base);
	chip->ecc.bytes = base->ecc.ctx.total / nanddev_get_ecc_nsteps(base);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rawnand_sw_hamming_init);

पूर्णांक rawnand_sw_hamming_calculate(काष्ठा nand_chip *chip,
				 स्थिर अचिन्हित अक्षर *buf,
				 अचिन्हित अक्षर *code)
अणु
	काष्ठा nand_device *base = &chip->base;

	वापस nand_ecc_sw_hamming_calculate(base, buf, code);
पूर्ण
EXPORT_SYMBOL(rawnand_sw_hamming_calculate);

पूर्णांक rawnand_sw_hamming_correct(काष्ठा nand_chip *chip,
			       अचिन्हित अक्षर *buf,
			       अचिन्हित अक्षर *पढ़ो_ecc,
			       अचिन्हित अक्षर *calc_ecc)
अणु
	काष्ठा nand_device *base = &chip->base;

	वापस nand_ecc_sw_hamming_correct(base, buf, पढ़ो_ecc, calc_ecc);
पूर्ण
EXPORT_SYMBOL(rawnand_sw_hamming_correct);

व्योम rawnand_sw_hamming_cleanup(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;

	nand_ecc_sw_hamming_cleanup_ctx(base);
पूर्ण
EXPORT_SYMBOL(rawnand_sw_hamming_cleanup);

पूर्णांक rawnand_sw_bch_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;
	स्थिर काष्ठा nand_ecc_props *ecc_conf = nanddev_get_ecc_conf(base);
	पूर्णांक ret;

	base->ecc.user_conf.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
	base->ecc.user_conf.algo = न_अंकD_ECC_ALGO_BCH;
	base->ecc.user_conf.step_size = chip->ecc.size;
	base->ecc.user_conf.strength = chip->ecc.strength;

	ret = nand_ecc_sw_bch_init_ctx(base);
	अगर (ret)
		वापस ret;

	chip->ecc.size = ecc_conf->step_size;
	chip->ecc.strength = ecc_conf->strength;
	chip->ecc.total = base->ecc.ctx.total;
	chip->ecc.steps = nanddev_get_ecc_nsteps(base);
	chip->ecc.bytes = base->ecc.ctx.total / nanddev_get_ecc_nsteps(base);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rawnand_sw_bch_init);

अटल पूर्णांक rawnand_sw_bch_calculate(काष्ठा nand_chip *chip,
				    स्थिर अचिन्हित अक्षर *buf,
				    अचिन्हित अक्षर *code)
अणु
	काष्ठा nand_device *base = &chip->base;

	वापस nand_ecc_sw_bch_calculate(base, buf, code);
पूर्ण

पूर्णांक rawnand_sw_bch_correct(काष्ठा nand_chip *chip, अचिन्हित अक्षर *buf,
			   अचिन्हित अक्षर *पढ़ो_ecc, अचिन्हित अक्षर *calc_ecc)
अणु
	काष्ठा nand_device *base = &chip->base;

	वापस nand_ecc_sw_bch_correct(base, buf, पढ़ो_ecc, calc_ecc);
पूर्ण
EXPORT_SYMBOL(rawnand_sw_bch_correct);

व्योम rawnand_sw_bch_cleanup(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_device *base = &chip->base;

	nand_ecc_sw_bch_cleanup_ctx(base);
पूर्ण
EXPORT_SYMBOL(rawnand_sw_bch_cleanup);

अटल पूर्णांक nand_set_ecc_on_host_ops(काष्ठा nand_chip *chip)
अणु
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	चयन (ecc->placement) अणु
	हाल न_अंकD_ECC_PLACEMENT_UNKNOWN:
	हाल न_अंकD_ECC_PLACEMENT_OOB:
		/* Use standard hwecc पढ़ो page function? */
		अगर (!ecc->पढ़ो_page)
			ecc->पढ़ो_page = nand_पढ़ो_page_hwecc;
		अगर (!ecc->ग_लिखो_page)
			ecc->ग_लिखो_page = nand_ग_लिखो_page_hwecc;
		अगर (!ecc->पढ़ो_page_raw)
			ecc->पढ़ो_page_raw = nand_पढ़ो_page_raw;
		अगर (!ecc->ग_लिखो_page_raw)
			ecc->ग_लिखो_page_raw = nand_ग_लिखो_page_raw;
		अगर (!ecc->पढ़ो_oob)
			ecc->पढ़ो_oob = nand_पढ़ो_oob_std;
		अगर (!ecc->ग_लिखो_oob)
			ecc->ग_लिखो_oob = nand_ग_लिखो_oob_std;
		अगर (!ecc->पढ़ो_subpage)
			ecc->पढ़ो_subpage = nand_पढ़ो_subpage;
		अगर (!ecc->ग_लिखो_subpage && ecc->hwctl && ecc->calculate)
			ecc->ग_लिखो_subpage = nand_ग_लिखो_subpage_hwecc;
		fallthrough;

	हाल न_अंकD_ECC_PLACEMENT_INTERLEAVED:
		अगर ((!ecc->calculate || !ecc->correct || !ecc->hwctl) &&
		    (!ecc->पढ़ो_page ||
		     ecc->पढ़ो_page == nand_पढ़ो_page_hwecc ||
		     !ecc->ग_लिखो_page ||
		     ecc->ग_लिखो_page == nand_ग_लिखो_page_hwecc)) अणु
			WARN(1, "No ECC functions supplied; hardware ECC not possible\n");
			वापस -EINVAL;
		पूर्ण
		/* Use standard syndrome पढ़ो/ग_लिखो page function? */
		अगर (!ecc->पढ़ो_page)
			ecc->पढ़ो_page = nand_पढ़ो_page_syndrome;
		अगर (!ecc->ग_लिखो_page)
			ecc->ग_लिखो_page = nand_ग_लिखो_page_syndrome;
		अगर (!ecc->पढ़ो_page_raw)
			ecc->पढ़ो_page_raw = nand_पढ़ो_page_raw_syndrome;
		अगर (!ecc->ग_लिखो_page_raw)
			ecc->ग_लिखो_page_raw = nand_ग_लिखो_page_raw_syndrome;
		अगर (!ecc->पढ़ो_oob)
			ecc->पढ़ो_oob = nand_पढ़ो_oob_syndrome;
		अगर (!ecc->ग_लिखो_oob)
			ecc->ग_लिखो_oob = nand_ग_लिखो_oob_syndrome;
		अवरोध;

	शेष:
		pr_warn("Invalid NAND_ECC_PLACEMENT %d\n",
			ecc->placement);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nand_set_ecc_soft_ops(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_device *nanddev = mtd_to_nanddev(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक ret;

	अगर (WARN_ON(ecc->engine_type != न_अंकD_ECC_ENGINE_TYPE_SOFT))
		वापस -EINVAL;

	चयन (ecc->algo) अणु
	हाल न_अंकD_ECC_ALGO_HAMMING:
		ecc->calculate = rawnand_sw_hamming_calculate;
		ecc->correct = rawnand_sw_hamming_correct;
		ecc->पढ़ो_page = nand_पढ़ो_page_swecc;
		ecc->पढ़ो_subpage = nand_पढ़ो_subpage;
		ecc->ग_लिखो_page = nand_ग_लिखो_page_swecc;
		अगर (!ecc->पढ़ो_page_raw)
			ecc->पढ़ो_page_raw = nand_पढ़ो_page_raw;
		अगर (!ecc->ग_लिखो_page_raw)
			ecc->ग_लिखो_page_raw = nand_ग_लिखो_page_raw;
		ecc->पढ़ो_oob = nand_पढ़ो_oob_std;
		ecc->ग_लिखो_oob = nand_ग_लिखो_oob_std;
		अगर (!ecc->size)
			ecc->size = 256;
		ecc->bytes = 3;
		ecc->strength = 1;

		अगर (IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING_SMC))
			ecc->options |= न_अंकD_ECC_SOFT_HAMMING_SM_ORDER;

		ret = rawnand_sw_hamming_init(chip);
		अगर (ret) अणु
			WARN(1, "Hamming ECC initialization failed!\n");
			वापस ret;
		पूर्ण

		वापस 0;
	हाल न_अंकD_ECC_ALGO_BCH:
		अगर (!IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_BCH)) अणु
			WARN(1, "CONFIG_MTD_NAND_ECC_SW_BCH not enabled\n");
			वापस -EINVAL;
		पूर्ण
		ecc->calculate = rawnand_sw_bch_calculate;
		ecc->correct = rawnand_sw_bch_correct;
		ecc->पढ़ो_page = nand_पढ़ो_page_swecc;
		ecc->पढ़ो_subpage = nand_पढ़ो_subpage;
		ecc->ग_लिखो_page = nand_ग_लिखो_page_swecc;
		अगर (!ecc->पढ़ो_page_raw)
			ecc->पढ़ो_page_raw = nand_पढ़ो_page_raw;
		अगर (!ecc->ग_लिखो_page_raw)
			ecc->ग_लिखो_page_raw = nand_ग_लिखो_page_raw;
		ecc->पढ़ो_oob = nand_पढ़ो_oob_std;
		ecc->ग_लिखो_oob = nand_ग_लिखो_oob_std;

		/*
		 * We can only maximize ECC config when the शेष layout is
		 * used, otherwise we करोn't know how many bytes can really be
		 * used.
		 */
		अगर (nanddev->ecc.user_conf.flags & न_अंकD_ECC_MAXIMIZE_STRENGTH &&
		    mtd->ooblayout != nand_get_large_page_ooblayout())
			nanddev->ecc.user_conf.flags &= ~न_अंकD_ECC_MAXIMIZE_STRENGTH;

		ret = rawnand_sw_bch_init(chip);
		अगर (ret) अणु
			WARN(1, "BCH ECC initialization failed!\n");
			वापस ret;
		पूर्ण

		वापस 0;
	शेष:
		WARN(1, "Unsupported ECC algorithm!\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * nand_check_ecc_caps - check the sanity of preset ECC settings
 * @chip: nand chip info काष्ठाure
 * @caps: ECC caps info काष्ठाure
 * @oobavail: OOB size that the ECC engine can use
 *
 * When ECC step size and strength are alपढ़ोy set, check अगर they are supported
 * by the controller and the calculated ECC bytes fit within the chip's OOB.
 * On success, the calculated ECC bytes is set.
 */
अटल पूर्णांक
nand_check_ecc_caps(काष्ठा nand_chip *chip,
		    स्थिर काष्ठा nand_ecc_caps *caps, पूर्णांक oobavail)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	स्थिर काष्ठा nand_ecc_step_info *stepinfo;
	पूर्णांक preset_step = chip->ecc.size;
	पूर्णांक preset_strength = chip->ecc.strength;
	पूर्णांक ecc_bytes, nsteps = mtd->ग_लिखोsize / preset_step;
	पूर्णांक i, j;

	क्रम (i = 0; i < caps->nstepinfos; i++) अणु
		stepinfo = &caps->stepinfos[i];

		अगर (stepinfo->stepsize != preset_step)
			जारी;

		क्रम (j = 0; j < stepinfo->nstrengths; j++) अणु
			अगर (stepinfo->strengths[j] != preset_strength)
				जारी;

			ecc_bytes = caps->calc_ecc_bytes(preset_step,
							 preset_strength);
			अगर (WARN_ON_ONCE(ecc_bytes < 0))
				वापस ecc_bytes;

			अगर (ecc_bytes * nsteps > oobavail) अणु
				pr_err("ECC (step, strength) = (%d, %d) does not fit in OOB",
				       preset_step, preset_strength);
				वापस -ENOSPC;
			पूर्ण

			chip->ecc.bytes = ecc_bytes;

			वापस 0;
		पूर्ण
	पूर्ण

	pr_err("ECC (step, strength) = (%d, %d) not supported on this controller",
	       preset_step, preset_strength);

	वापस -ENOTSUPP;
पूर्ण

/**
 * nand_match_ecc_req - meet the chip's requirement with least ECC bytes
 * @chip: nand chip info काष्ठाure
 * @caps: ECC engine caps info काष्ठाure
 * @oobavail: OOB size that the ECC engine can use
 *
 * If a chip's ECC requirement is provided, try to meet it with the least
 * number of ECC bytes (i.e. with the largest number of OOB-मुक्त bytes).
 * On success, the chosen ECC settings are set.
 */
अटल पूर्णांक
nand_match_ecc_req(काष्ठा nand_chip *chip,
		   स्थिर काष्ठा nand_ecc_caps *caps, पूर्णांक oobavail)
अणु
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&chip->base);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	स्थिर काष्ठा nand_ecc_step_info *stepinfo;
	पूर्णांक req_step = requirements->step_size;
	पूर्णांक req_strength = requirements->strength;
	पूर्णांक req_corr, step_size, strength, nsteps, ecc_bytes, ecc_bytes_total;
	पूर्णांक best_step, best_strength, best_ecc_bytes;
	पूर्णांक best_ecc_bytes_total = पूर्णांक_उच्च;
	पूर्णांक i, j;

	/* No inक्रमmation provided by the न_अंकD chip */
	अगर (!req_step || !req_strength)
		वापस -ENOTSUPP;

	/* number of correctable bits the chip requires in a page */
	req_corr = mtd->ग_लिखोsize / req_step * req_strength;

	क्रम (i = 0; i < caps->nstepinfos; i++) अणु
		stepinfo = &caps->stepinfos[i];
		step_size = stepinfo->stepsize;

		क्रम (j = 0; j < stepinfo->nstrengths; j++) अणु
			strength = stepinfo->strengths[j];

			/*
			 * If both step size and strength are smaller than the
			 * chip's requirement, it is not easy to compare the
			 * resulted reliability.
			 */
			अगर (step_size < req_step && strength < req_strength)
				जारी;

			अगर (mtd->ग_लिखोsize % step_size)
				जारी;

			nsteps = mtd->ग_लिखोsize / step_size;

			ecc_bytes = caps->calc_ecc_bytes(step_size, strength);
			अगर (WARN_ON_ONCE(ecc_bytes < 0))
				जारी;
			ecc_bytes_total = ecc_bytes * nsteps;

			अगर (ecc_bytes_total > oobavail ||
			    strength * nsteps < req_corr)
				जारी;

			/*
			 * We assume the best is to meet the chip's requrement
			 * with the least number of ECC bytes.
			 */
			अगर (ecc_bytes_total < best_ecc_bytes_total) अणु
				best_ecc_bytes_total = ecc_bytes_total;
				best_step = step_size;
				best_strength = strength;
				best_ecc_bytes = ecc_bytes;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (best_ecc_bytes_total == पूर्णांक_उच्च)
		वापस -ENOTSUPP;

	chip->ecc.size = best_step;
	chip->ecc.strength = best_strength;
	chip->ecc.bytes = best_ecc_bytes;

	वापस 0;
पूर्ण

/**
 * nand_maximize_ecc - choose the max ECC strength available
 * @chip: nand chip info काष्ठाure
 * @caps: ECC engine caps info काष्ठाure
 * @oobavail: OOB size that the ECC engine can use
 *
 * Choose the max ECC strength that is supported on the controller, and can fit
 * within the chip's OOB.  On success, the chosen ECC settings are set.
 */
अटल पूर्णांक
nand_maximize_ecc(काष्ठा nand_chip *chip,
		  स्थिर काष्ठा nand_ecc_caps *caps, पूर्णांक oobavail)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	स्थिर काष्ठा nand_ecc_step_info *stepinfo;
	पूर्णांक step_size, strength, nsteps, ecc_bytes, corr;
	पूर्णांक best_corr = 0;
	पूर्णांक best_step = 0;
	पूर्णांक best_strength, best_ecc_bytes;
	पूर्णांक i, j;

	क्रम (i = 0; i < caps->nstepinfos; i++) अणु
		stepinfo = &caps->stepinfos[i];
		step_size = stepinfo->stepsize;

		/* If chip->ecc.size is alपढ़ोy set, respect it */
		अगर (chip->ecc.size && step_size != chip->ecc.size)
			जारी;

		क्रम (j = 0; j < stepinfo->nstrengths; j++) अणु
			strength = stepinfo->strengths[j];

			अगर (mtd->ग_लिखोsize % step_size)
				जारी;

			nsteps = mtd->ग_लिखोsize / step_size;

			ecc_bytes = caps->calc_ecc_bytes(step_size, strength);
			अगर (WARN_ON_ONCE(ecc_bytes < 0))
				जारी;

			अगर (ecc_bytes * nsteps > oobavail)
				जारी;

			corr = strength * nsteps;

			/*
			 * If the number of correctable bits is the same,
			 * bigger step_size has more reliability.
			 */
			अगर (corr > best_corr ||
			    (corr == best_corr && step_size > best_step)) अणु
				best_corr = corr;
				best_step = step_size;
				best_strength = strength;
				best_ecc_bytes = ecc_bytes;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!best_corr)
		वापस -ENOTSUPP;

	chip->ecc.size = best_step;
	chip->ecc.strength = best_strength;
	chip->ecc.bytes = best_ecc_bytes;

	वापस 0;
पूर्ण

/**
 * nand_ecc_choose_conf - Set the ECC strength and ECC step size
 * @chip: nand chip info काष्ठाure
 * @caps: ECC engine caps info काष्ठाure
 * @oobavail: OOB size that the ECC engine can use
 *
 * Choose the ECC configuration according to following logic.
 *
 * 1. If both ECC step size and ECC strength are alपढ़ोy set (usually by DT)
 *    then check अगर it is supported by this controller.
 * 2. If the user provided the nand-ecc-maximize property, then select maximum
 *    ECC strength.
 * 3. Otherwise, try to match the ECC step size and ECC strength बंदst
 *    to the chip's requirement. If available OOB size can't fit the chip
 *    requirement then fallback to the maximum ECC step size and ECC strength.
 *
 * On success, the chosen ECC settings are set.
 */
पूर्णांक nand_ecc_choose_conf(काष्ठा nand_chip *chip,
			 स्थिर काष्ठा nand_ecc_caps *caps, पूर्णांक oobavail)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_device *nanddev = mtd_to_nanddev(mtd);

	अगर (WARN_ON(oobavail < 0 || oobavail > mtd->oobsize))
		वापस -EINVAL;

	अगर (chip->ecc.size && chip->ecc.strength)
		वापस nand_check_ecc_caps(chip, caps, oobavail);

	अगर (nanddev->ecc.user_conf.flags & न_अंकD_ECC_MAXIMIZE_STRENGTH)
		वापस nand_maximize_ecc(chip, caps, oobavail);

	अगर (!nand_match_ecc_req(chip, caps, oobavail))
		वापस 0;

	वापस nand_maximize_ecc(chip, caps, oobavail);
पूर्ण
EXPORT_SYMBOL_GPL(nand_ecc_choose_conf);

अटल पूर्णांक rawnand_erase(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	काष्ठा nand_chip *chip = container_of(nand, काष्ठा nand_chip,
					      base);
	अचिन्हित पूर्णांक eb = nanddev_pos_to_row(nand, pos);
	पूर्णांक ret;

	eb >>= nand->rowconv.eraseblock_addr_shअगरt;

	nand_select_target(chip, pos->target);
	ret = nand_erase_op(chip, eb);
	nand_deselect_target(chip);

	वापस ret;
पूर्ण

अटल पूर्णांक rawnand_markbad(काष्ठा nand_device *nand,
			   स्थिर काष्ठा nand_pos *pos)
अणु
	काष्ठा nand_chip *chip = container_of(nand, काष्ठा nand_chip,
					      base);

	वापस nand_markbad_bbm(chip, nanddev_pos_to_offs(nand, pos));
पूर्ण

अटल bool rawnand_isbad(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	काष्ठा nand_chip *chip = container_of(nand, काष्ठा nand_chip,
					      base);
	पूर्णांक ret;

	nand_select_target(chip, pos->target);
	ret = nand_isbad_bbm(chip, nanddev_pos_to_offs(nand, pos));
	nand_deselect_target(chip);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nand_ops rawnand_ops = अणु
	.erase = rawnand_erase,
	.markbad = rawnand_markbad,
	.isbad = rawnand_isbad,
पूर्ण;

/**
 * nand_scan_tail - Scan क्रम the न_अंकD device
 * @chip: न_अंकD chip object
 *
 * This is the second phase of the normal nand_scan() function. It fills out
 * all the uninitialized function poपूर्णांकers with the शेषs and scans क्रम a
 * bad block table अगर appropriate.
 */
अटल पूर्णांक nand_scan_tail(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक ret, i;

	/* New bad blocks should be marked in OOB, flash-based BBT, or both */
	अगर (WARN_ON((chip->bbt_options & न_अंकD_BBT_NO_OOB_BBM) &&
		   !(chip->bbt_options & न_अंकD_BBT_USE_FLASH))) अणु
		वापस -EINVAL;
	पूर्ण

	chip->data_buf = kदो_स्मृति(mtd->ग_लिखोsize + mtd->oobsize, GFP_KERNEL);
	अगर (!chip->data_buf)
		वापस -ENOMEM;

	/*
	 * FIXME: some न_अंकD manufacturer drivers expect the first die to be
	 * selected when manufacturer->init() is called. They should be fixed
	 * to explictly select the relevant die when पूर्णांकeracting with the न_अंकD
	 * chip.
	 */
	nand_select_target(chip, 0);
	ret = nand_manufacturer_init(chip);
	nand_deselect_target(chip);
	अगर (ret)
		जाओ err_मुक्त_buf;

	/* Set the पूर्णांकernal oob buffer location, just after the page data */
	chip->oob_poi = chip->data_buf + mtd->ग_लिखोsize;

	/*
	 * If no शेष placement scheme is given, select an appropriate one.
	 */
	अगर (!mtd->ooblayout &&
	    !(ecc->engine_type == न_अंकD_ECC_ENGINE_TYPE_SOFT &&
	      ecc->algo == न_अंकD_ECC_ALGO_BCH) &&
	    !(ecc->engine_type == न_अंकD_ECC_ENGINE_TYPE_SOFT &&
	      ecc->algo == न_अंकD_ECC_ALGO_HAMMING)) अणु
		चयन (mtd->oobsize) अणु
		हाल 8:
		हाल 16:
			mtd_set_ooblayout(mtd, nand_get_small_page_ooblayout());
			अवरोध;
		हाल 64:
		हाल 128:
			mtd_set_ooblayout(mtd,
					  nand_get_large_page_hamming_ooblayout());
			अवरोध;
		शेष:
			/*
			 * Expose the whole OOB area to users अगर ECC_NONE
			 * is passed. We could करो that क्रम all kind of
			 * ->oobsize, but we must keep the old large/small
			 * page with ECC layout when ->oobsize <= 128 क्रम
			 * compatibility reasons.
			 */
			अगर (ecc->engine_type == न_अंकD_ECC_ENGINE_TYPE_NONE) अणु
				mtd_set_ooblayout(mtd,
						  nand_get_large_page_ooblayout());
				अवरोध;
			पूर्ण

			WARN(1, "No oob scheme defined for oobsize %d\n",
				mtd->oobsize);
			ret = -EINVAL;
			जाओ err_nand_manuf_cleanup;
		पूर्ण
	पूर्ण

	/*
	 * Check ECC mode, शेष to software अगर 3byte/512byte hardware ECC is
	 * selected and we have 256 byte pagesize fallback to software ECC
	 */

	चयन (ecc->engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		ret = nand_set_ecc_on_host_ops(chip);
		अगर (ret)
			जाओ err_nand_manuf_cleanup;

		अगर (mtd->ग_लिखोsize >= ecc->size) अणु
			अगर (!ecc->strength) अणु
				WARN(1, "Driver must set ecc.strength when using hardware ECC\n");
				ret = -EINVAL;
				जाओ err_nand_manuf_cleanup;
			पूर्ण
			अवरोध;
		पूर्ण
		pr_warn("%d byte HW ECC not possible on %d byte page size, fallback to SW ECC\n",
			ecc->size, mtd->ग_लिखोsize);
		ecc->engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
		ecc->algo = न_अंकD_ECC_ALGO_HAMMING;
		fallthrough;

	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		ret = nand_set_ecc_soft_ops(chip);
		अगर (ret)
			जाओ err_nand_manuf_cleanup;
		अवरोध;

	हाल न_अंकD_ECC_ENGINE_TYPE_ON_DIE:
		अगर (!ecc->पढ़ो_page || !ecc->ग_लिखो_page) अणु
			WARN(1, "No ECC functions supplied; on-die ECC not possible\n");
			ret = -EINVAL;
			जाओ err_nand_manuf_cleanup;
		पूर्ण
		अगर (!ecc->पढ़ो_oob)
			ecc->पढ़ो_oob = nand_पढ़ो_oob_std;
		अगर (!ecc->ग_लिखो_oob)
			ecc->ग_लिखो_oob = nand_ग_लिखो_oob_std;
		अवरोध;

	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
		pr_warn("NAND_ECC_ENGINE_TYPE_NONE selected by board driver. This is not recommended!\n");
		ecc->पढ़ो_page = nand_पढ़ो_page_raw;
		ecc->ग_लिखो_page = nand_ग_लिखो_page_raw;
		ecc->पढ़ो_oob = nand_पढ़ो_oob_std;
		ecc->पढ़ो_page_raw = nand_पढ़ो_page_raw;
		ecc->ग_लिखो_page_raw = nand_ग_लिखो_page_raw;
		ecc->ग_लिखो_oob = nand_ग_लिखो_oob_std;
		ecc->size = mtd->ग_लिखोsize;
		ecc->bytes = 0;
		ecc->strength = 0;
		अवरोध;

	शेष:
		WARN(1, "Invalid NAND_ECC_MODE %d\n", ecc->engine_type);
		ret = -EINVAL;
		जाओ err_nand_manuf_cleanup;
	पूर्ण

	अगर (ecc->correct || ecc->calculate) अणु
		ecc->calc_buf = kदो_स्मृति(mtd->oobsize, GFP_KERNEL);
		ecc->code_buf = kदो_स्मृति(mtd->oobsize, GFP_KERNEL);
		अगर (!ecc->calc_buf || !ecc->code_buf) अणु
			ret = -ENOMEM;
			जाओ err_nand_manuf_cleanup;
		पूर्ण
	पूर्ण

	/* For many प्रणालीs, the standard OOB ग_लिखो also works क्रम raw */
	अगर (!ecc->पढ़ो_oob_raw)
		ecc->पढ़ो_oob_raw = ecc->पढ़ो_oob;
	अगर (!ecc->ग_लिखो_oob_raw)
		ecc->ग_लिखो_oob_raw = ecc->ग_लिखो_oob;

	/* propagate ecc info to mtd_info */
	mtd->ecc_strength = ecc->strength;
	mtd->ecc_step_size = ecc->size;

	/*
	 * Set the number of पढ़ो / ग_लिखो steps क्रम one page depending on ECC
	 * mode.
	 */
	अगर (!ecc->steps)
		ecc->steps = mtd->ग_लिखोsize / ecc->size;
	अगर (ecc->steps * ecc->size != mtd->ग_लिखोsize) अणु
		WARN(1, "Invalid ECC parameters\n");
		ret = -EINVAL;
		जाओ err_nand_manuf_cleanup;
	पूर्ण

	अगर (!ecc->total) अणु
		ecc->total = ecc->steps * ecc->bytes;
		chip->base.ecc.ctx.total = ecc->total;
	पूर्ण

	अगर (ecc->total > mtd->oobsize) अणु
		WARN(1, "Total number of ECC bytes exceeded oobsize\n");
		ret = -EINVAL;
		जाओ err_nand_manuf_cleanup;
	पूर्ण

	/*
	 * The number of bytes available क्रम a client to place data पूर्णांकo
	 * the out of band area.
	 */
	ret = mtd_ooblayout_count_मुक्तbytes(mtd);
	अगर (ret < 0)
		ret = 0;

	mtd->oobavail = ret;

	/* ECC sanity check: warn अगर it's too weak */
	अगर (!nand_ecc_is_strong_enough(&chip->base))
		pr_warn("WARNING: %s: the ECC used on your system (%db/%dB) is too weak compared to the one required by the NAND chip (%db/%dB)\n",
			mtd->name, chip->ecc.strength, chip->ecc.size,
			nanddev_get_ecc_requirements(&chip->base)->strength,
			nanddev_get_ecc_requirements(&chip->base)->step_size);

	/* Allow subpage ग_लिखोs up to ecc.steps. Not possible क्रम MLC flash */
	अगर (!(chip->options & न_अंकD_NO_SUBPAGE_WRITE) && nand_is_slc(chip)) अणु
		चयन (ecc->steps) अणु
		हाल 2:
			mtd->subpage_sft = 1;
			अवरोध;
		हाल 4:
		हाल 8:
		हाल 16:
			mtd->subpage_sft = 2;
			अवरोध;
		पूर्ण
	पूर्ण
	chip->subpagesize = mtd->ग_लिखोsize >> mtd->subpage_sft;

	/* Invalidate the pagebuffer reference */
	chip->pagecache.page = -1;

	/* Large page न_अंकD with SOFT_ECC should support subpage पढ़ोs */
	चयन (ecc->engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		अगर (chip->page_shअगरt > 9)
			chip->options |= न_अंकD_SUBPAGE_READ;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	ret = nanddev_init(&chip->base, &rawnand_ops, mtd->owner);
	अगर (ret)
		जाओ err_nand_manuf_cleanup;

	/* Adjust the MTD_CAP_ flags when न_अंकD_ROM is set. */
	अगर (chip->options & न_अंकD_ROM)
		mtd->flags = MTD_CAP_ROM;

	/* Fill in reमुख्यing MTD driver data */
	mtd->_erase = nand_erase;
	mtd->_poपूर्णांक = शून्य;
	mtd->_unpoपूर्णांक = शून्य;
	mtd->_panic_ग_लिखो = panic_nand_ग_लिखो;
	mtd->_पढ़ो_oob = nand_पढ़ो_oob;
	mtd->_ग_लिखो_oob = nand_ग_लिखो_oob;
	mtd->_sync = nand_sync;
	mtd->_lock = nand_lock;
	mtd->_unlock = nand_unlock;
	mtd->_suspend = nand_suspend;
	mtd->_resume = nand_resume;
	mtd->_reboot = nand_shutकरोwn;
	mtd->_block_isreserved = nand_block_isreserved;
	mtd->_block_isbad = nand_block_isbad;
	mtd->_block_markbad = nand_block_markbad;
	mtd->_max_bad_blocks = nanddev_mtd_max_bad_blocks;

	/*
	 * Initialize bitflip_threshold to its शेष prior scan_bbt() call.
	 * scan_bbt() might invoke mtd_पढ़ो(), thus bitflip_threshold must be
	 * properly set.
	 */
	अगर (!mtd->bitflip_threshold)
		mtd->bitflip_threshold = DIV_ROUND_UP(mtd->ecc_strength * 3, 4);

	/* Find the fastest data पूर्णांकerface क्रम this chip */
	ret = nand_choose_पूर्णांकerface_config(chip);
	अगर (ret)
		जाओ err_nanddev_cleanup;

	/* Enter fastest possible mode on all dies. */
	क्रम (i = 0; i < nanddev_ntarमाला_लो(&chip->base); i++) अणु
		ret = nand_setup_पूर्णांकerface(chip, i);
		अगर (ret)
			जाओ err_मुक्त_पूर्णांकerface_config;
	पूर्ण

	/*
	 * Look क्रम secure regions in the न_अंकD chip. These regions are supposed
	 * to be रक्षित by a secure element like Trustzone. So the पढ़ो/ग_लिखो
	 * accesses to these regions will be blocked in the runसमय by this
	 * driver.
	 */
	ret = of_get_nand_secure_regions(chip);
	अगर (ret)
		जाओ err_मुक्त_पूर्णांकerface_config;

	/* Check, अगर we should skip the bad block table scan */
	अगर (chip->options & न_अंकD_SKIP_BBTSCAN)
		वापस 0;

	/* Build bad block table */
	ret = nand_create_bbt(chip);
	अगर (ret)
		जाओ err_मुक्त_secure_regions;

	वापस 0;

err_मुक्त_secure_regions:
	kमुक्त(chip->secure_regions);

err_मुक्त_पूर्णांकerface_config:
	kमुक्त(chip->best_पूर्णांकerface_config);

err_nanddev_cleanup:
	nanddev_cleanup(&chip->base);

err_nand_manuf_cleanup:
	nand_manufacturer_cleanup(chip);

err_मुक्त_buf:
	kमुक्त(chip->data_buf);
	kमुक्त(ecc->code_buf);
	kमुक्त(ecc->calc_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक nand_attach(काष्ठा nand_chip *chip)
अणु
	अगर (chip->controller->ops && chip->controller->ops->attach_chip)
		वापस chip->controller->ops->attach_chip(chip);

	वापस 0;
पूर्ण

अटल व्योम nand_detach(काष्ठा nand_chip *chip)
अणु
	अगर (chip->controller->ops && chip->controller->ops->detach_chip)
		chip->controller->ops->detach_chip(chip);
पूर्ण

/**
 * nand_scan_with_ids - [न_अंकD Interface] Scan क्रम the न_अंकD device
 * @chip: न_अंकD chip object
 * @maxchips: number of chips to scan क्रम.
 * @ids: optional flash IDs table
 *
 * This fills out all the uninitialized function poपूर्णांकers with the शेषs.
 * The flash ID is पढ़ो and the mtd/chip काष्ठाures are filled with the
 * appropriate values.
 */
पूर्णांक nand_scan_with_ids(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक maxchips,
		       काष्ठा nand_flash_dev *ids)
अणु
	पूर्णांक ret;

	अगर (!maxchips)
		वापस -EINVAL;

	ret = nand_scan_ident(chip, maxchips, ids);
	अगर (ret)
		वापस ret;

	ret = nand_attach(chip);
	अगर (ret)
		जाओ cleanup_ident;

	ret = nand_scan_tail(chip);
	अगर (ret)
		जाओ detach_chip;

	वापस 0;

detach_chip:
	nand_detach(chip);
cleanup_ident:
	nand_scan_ident_cleanup(chip);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(nand_scan_with_ids);

/**
 * nand_cleanup - [न_अंकD Interface] Free resources held by the न_अंकD device
 * @chip: न_अंकD chip object
 */
व्योम nand_cleanup(काष्ठा nand_chip *chip)
अणु
	अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_SOFT) अणु
		अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_HAMMING)
			rawnand_sw_hamming_cleanup(chip);
		अन्यथा अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_BCH)
			rawnand_sw_bch_cleanup(chip);
	पूर्ण

	nanddev_cleanup(&chip->base);

	/* Free secure regions data */
	kमुक्त(chip->secure_regions);

	/* Free bad block table memory */
	kमुक्त(chip->bbt);
	kमुक्त(chip->data_buf);
	kमुक्त(chip->ecc.code_buf);
	kमुक्त(chip->ecc.calc_buf);

	/* Free bad block descriptor memory */
	अगर (chip->badblock_pattern && chip->badblock_pattern->options
			& न_अंकD_BBT_DYNAMICSTRUCT)
		kमुक्त(chip->badblock_pattern);

	/* Free the data पूर्णांकerface */
	kमुक्त(chip->best_पूर्णांकerface_config);

	/* Free manufacturer priv data. */
	nand_manufacturer_cleanup(chip);

	/* Free controller specअगरic allocations after chip identअगरication */
	nand_detach(chip);

	/* Free identअगरication phase allocations */
	nand_scan_ident_cleanup(chip);
पूर्ण

EXPORT_SYMBOL_GPL(nand_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Steven J. Hill <sjhill@realitydiluted.com>");
MODULE_AUTHOR("Thomas Gleixner <tglx@linutronix.de>");
MODULE_DESCRIPTION("Generic NAND flash driver code");
