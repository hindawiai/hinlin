<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SPI NOR Software Write Protection logic.
 *
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल u8 spi_nor_get_sr_bp_mask(काष्ठा spi_nor *nor)
अणु
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;

	अगर (nor->flags & SNOR_F_HAS_SR_BP3_BIT6)
		वापस mask | SR_BP3_BIT6;

	अगर (nor->flags & SNOR_F_HAS_4BIT_BP)
		वापस mask | SR_BP3;

	वापस mask;
पूर्ण

अटल u8 spi_nor_get_sr_tb_mask(काष्ठा spi_nor *nor)
अणु
	अगर (nor->flags & SNOR_F_HAS_SR_TB_BIT6)
		वापस SR_TB_BIT6;
	अन्यथा
		वापस SR_TB_BIT5;
पूर्ण

अटल u64 spi_nor_get_min_prot_length_sr(काष्ठा spi_nor *nor)
अणु
	अचिन्हित पूर्णांक bp_slots, bp_slots_needed;
	u8 mask = spi_nor_get_sr_bp_mask(nor);

	/* Reserved one क्रम "protect none" and one क्रम "protect all". */
	bp_slots = (1 << hweight8(mask)) - 2;
	bp_slots_needed = ilog2(nor->info->n_sectors);

	अगर (bp_slots_needed > bp_slots)
		वापस nor->info->sector_size <<
			(bp_slots_needed - bp_slots);
	अन्यथा
		वापस nor->info->sector_size;
पूर्ण

अटल व्योम spi_nor_get_locked_range_sr(काष्ठा spi_nor *nor, u8 sr, loff_t *ofs,
					uपूर्णांक64_t *len)
अणु
	काष्ठा mtd_info *mtd = &nor->mtd;
	u64 min_prot_len;
	u8 mask = spi_nor_get_sr_bp_mask(nor);
	u8 tb_mask = spi_nor_get_sr_tb_mask(nor);
	u8 bp, val = sr & mask;

	अगर (nor->flags & SNOR_F_HAS_SR_BP3_BIT6 && val & SR_BP3_BIT6)
		val = (val & ~SR_BP3_BIT6) | SR_BP3;

	bp = val >> SR_BP_SHIFT;

	अगर (!bp) अणु
		/* No protection */
		*ofs = 0;
		*len = 0;
		वापस;
	पूर्ण

	min_prot_len = spi_nor_get_min_prot_length_sr(nor);
	*len = min_prot_len << (bp - 1);

	अगर (*len > mtd->size)
		*len = mtd->size;

	अगर (nor->flags & SNOR_F_HAS_SR_TB && sr & tb_mask)
		*ofs = 0;
	अन्यथा
		*ofs = mtd->size - *len;
पूर्ण

/*
 * Return true अगर the entire region is locked (अगर @locked is true) or unlocked
 * (अगर @locked is false); false otherwise.
 */
अटल bool spi_nor_check_lock_status_sr(काष्ठा spi_nor *nor, loff_t ofs,
					 uपूर्णांक64_t len, u8 sr, bool locked)
अणु
	loff_t lock_offs, lock_offs_max, offs_max;
	uपूर्णांक64_t lock_len;

	अगर (!len)
		वापस true;

	spi_nor_get_locked_range_sr(nor, sr, &lock_offs, &lock_len);

	lock_offs_max = lock_offs + lock_len;
	offs_max = ofs + len;

	अगर (locked)
		/* Requested range is a sub-range of locked range */
		वापस (offs_max <= lock_offs_max) && (ofs >= lock_offs);
	अन्यथा
		/* Requested range करोes not overlap with locked range */
		वापस (ofs >= lock_offs_max) || (offs_max <= lock_offs);
पूर्ण

अटल bool spi_nor_is_locked_sr(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len,
				 u8 sr)
अणु
	वापस spi_nor_check_lock_status_sr(nor, ofs, len, sr, true);
पूर्ण

अटल bool spi_nor_is_unlocked_sr(काष्ठा spi_nor *nor, loff_t ofs,
				   uपूर्णांक64_t len, u8 sr)
अणु
	वापस spi_nor_check_lock_status_sr(nor, ofs, len, sr, false);
पूर्ण

/*
 * Lock a region of the flash. Compatible with ST Micro and similar flash.
 * Supports the block protection bits BPअणु0,1,2पूर्ण/BPअणु0,1,2,3पूर्ण in the status
 * रेजिस्टर
 * (SR). Does not support these features found in newer SR bitfields:
 *   - SEC: sector/block protect - only handle SEC=0 (block protect)
 *   - CMP: complement protect - only support CMP=0 (range is not complemented)
 *
 * Support क्रम the following is provided conditionally क्रम some flash:
 *   - TB: top/bottom protect
 *
 * Sample table portion क्रम 8MB flash (Winbond w25q64fw):
 *
 *   SEC  |  TB   |  BP2  |  BP1  |  BP0  |  Prot Length  | Protected Portion
 *  --------------------------------------------------------------------------
 *    X   |   X   |   0   |   0   |   0   |  NONE         | NONE
 *    0   |   0   |   0   |   0   |   1   |  128 KB       | Upper 1/64
 *    0   |   0   |   0   |   1   |   0   |  256 KB       | Upper 1/32
 *    0   |   0   |   0   |   1   |   1   |  512 KB       | Upper 1/16
 *    0   |   0   |   1   |   0   |   0   |  1 MB         | Upper 1/8
 *    0   |   0   |   1   |   0   |   1   |  2 MB         | Upper 1/4
 *    0   |   0   |   1   |   1   |   0   |  4 MB         | Upper 1/2
 *    X   |   X   |   1   |   1   |   1   |  8 MB         | ALL
 *  ------|-------|-------|-------|-------|---------------|-------------------
 *    0   |   1   |   0   |   0   |   1   |  128 KB       | Lower 1/64
 *    0   |   1   |   0   |   1   |   0   |  256 KB       | Lower 1/32
 *    0   |   1   |   0   |   1   |   1   |  512 KB       | Lower 1/16
 *    0   |   1   |   1   |   0   |   0   |  1 MB         | Lower 1/8
 *    0   |   1   |   1   |   0   |   1   |  2 MB         | Lower 1/4
 *    0   |   1   |   1   |   1   |   0   |  4 MB         | Lower 1/2
 *
 * Returns negative on errors, 0 on success.
 */
अटल पूर्णांक spi_nor_sr_lock(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा mtd_info *mtd = &nor->mtd;
	u64 min_prot_len;
	पूर्णांक ret, status_old, status_new;
	u8 mask = spi_nor_get_sr_bp_mask(nor);
	u8 tb_mask = spi_nor_get_sr_tb_mask(nor);
	u8 घात, val;
	loff_t lock_len;
	bool can_be_top = true, can_be_bottom = nor->flags & SNOR_F_HAS_SR_TB;
	bool use_top;

	ret = spi_nor_पढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	status_old = nor->bouncebuf[0];

	/* If nothing in our range is unlocked, we करोn't need to करो anything */
	अगर (spi_nor_is_locked_sr(nor, ofs, len, status_old))
		वापस 0;

	/* If anything below us is unlocked, we can't use 'bottom' protection */
	अगर (!spi_nor_is_locked_sr(nor, 0, ofs, status_old))
		can_be_bottom = false;

	/* If anything above us is unlocked, we can't use 'top' protection */
	अगर (!spi_nor_is_locked_sr(nor, ofs + len, mtd->size - (ofs + len),
				  status_old))
		can_be_top = false;

	अगर (!can_be_bottom && !can_be_top)
		वापस -EINVAL;

	/* Prefer top, अगर both are valid */
	use_top = can_be_top;

	/* lock_len: length of region that should end up locked */
	अगर (use_top)
		lock_len = mtd->size - ofs;
	अन्यथा
		lock_len = ofs + len;

	अगर (lock_len == mtd->size) अणु
		val = mask;
	पूर्ण अन्यथा अणु
		min_prot_len = spi_nor_get_min_prot_length_sr(nor);
		घात = ilog2(lock_len) - ilog2(min_prot_len) + 1;
		val = घात << SR_BP_SHIFT;

		अगर (nor->flags & SNOR_F_HAS_SR_BP3_BIT6 && val & SR_BP3)
			val = (val & ~SR_BP3) | SR_BP3_BIT6;

		अगर (val & ~mask)
			वापस -EINVAL;

		/* Don't "lock" with no region! */
		अगर (!(val & mask))
			वापस -EINVAL;
	पूर्ण

	status_new = (status_old & ~mask & ~tb_mask) | val;

	/* Disallow further ग_लिखोs अगर WP pin is निश्चितed */
	status_new |= SR_SRWD;

	अगर (!use_top)
		status_new |= tb_mask;

	/* Don't bother if they're the same */
	अगर (status_new == status_old)
		वापस 0;

	/* Only modअगरy protection अगर it will not unlock other areas */
	अगर ((status_new & mask) < (status_old & mask))
		वापस -EINVAL;

	वापस spi_nor_ग_लिखो_sr_and_check(nor, status_new);
पूर्ण

/*
 * Unlock a region of the flash. See spi_nor_sr_lock() क्रम more info
 *
 * Returns negative on errors, 0 on success.
 */
अटल पूर्णांक spi_nor_sr_unlock(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा mtd_info *mtd = &nor->mtd;
	u64 min_prot_len;
	पूर्णांक ret, status_old, status_new;
	u8 mask = spi_nor_get_sr_bp_mask(nor);
	u8 tb_mask = spi_nor_get_sr_tb_mask(nor);
	u8 घात, val;
	loff_t lock_len;
	bool can_be_top = true, can_be_bottom = nor->flags & SNOR_F_HAS_SR_TB;
	bool use_top;

	ret = spi_nor_पढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	status_old = nor->bouncebuf[0];

	/* If nothing in our range is locked, we करोn't need to करो anything */
	अगर (spi_nor_is_unlocked_sr(nor, ofs, len, status_old))
		वापस 0;

	/* If anything below us is locked, we can't use 'top' protection */
	अगर (!spi_nor_is_unlocked_sr(nor, 0, ofs, status_old))
		can_be_top = false;

	/* If anything above us is locked, we can't use 'bottom' protection */
	अगर (!spi_nor_is_unlocked_sr(nor, ofs + len, mtd->size - (ofs + len),
				    status_old))
		can_be_bottom = false;

	अगर (!can_be_bottom && !can_be_top)
		वापस -EINVAL;

	/* Prefer top, अगर both are valid */
	use_top = can_be_top;

	/* lock_len: length of region that should reमुख्य locked */
	अगर (use_top)
		lock_len = mtd->size - (ofs + len);
	अन्यथा
		lock_len = ofs;

	अगर (lock_len == 0) अणु
		val = 0; /* fully unlocked */
	पूर्ण अन्यथा अणु
		min_prot_len = spi_nor_get_min_prot_length_sr(nor);
		घात = ilog2(lock_len) - ilog2(min_prot_len) + 1;
		val = घात << SR_BP_SHIFT;

		अगर (nor->flags & SNOR_F_HAS_SR_BP3_BIT6 && val & SR_BP3)
			val = (val & ~SR_BP3) | SR_BP3_BIT6;

		/* Some घातer-of-two sizes are not supported */
		अगर (val & ~mask)
			वापस -EINVAL;
	पूर्ण

	status_new = (status_old & ~mask & ~tb_mask) | val;

	/* Don't protect status register if we're fully unlocked */
	अगर (lock_len == 0)
		status_new &= ~SR_SRWD;

	अगर (!use_top)
		status_new |= tb_mask;

	/* Don't bother if they're the same */
	अगर (status_new == status_old)
		वापस 0;

	/* Only modअगरy protection अगर it will not lock other areas */
	अगर ((status_new & mask) > (status_old & mask))
		वापस -EINVAL;

	वापस spi_nor_ग_लिखो_sr_and_check(nor, status_new);
पूर्ण

/*
 * Check अगर a region of the flash is (completely) locked. See spi_nor_sr_lock()
 * क्रम more info.
 *
 * Returns 1 अगर entire region is locked, 0 अगर any portion is unlocked, and
 * negative on errors.
 */
अटल पूर्णांक spi_nor_sr_is_locked(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

	ret = spi_nor_पढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	वापस spi_nor_is_locked_sr(nor, ofs, len, nor->bouncebuf[0]);
पूर्ण

अटल स्थिर काष्ठा spi_nor_locking_ops spi_nor_sr_locking_ops = अणु
	.lock = spi_nor_sr_lock,
	.unlock = spi_nor_sr_unlock,
	.is_locked = spi_nor_sr_is_locked,
पूर्ण;

व्योम spi_nor_init_शेष_locking_ops(काष्ठा spi_nor *nor)
अणु
	nor->params->locking_ops = &spi_nor_sr_locking_ops;
पूर्ण

अटल पूर्णांक spi_nor_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	पूर्णांक ret;

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	ret = nor->params->locking_ops->lock(nor, ofs, len);

	spi_nor_unlock_and_unprep(nor);
	वापस ret;
पूर्ण

अटल पूर्णांक spi_nor_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	पूर्णांक ret;

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	ret = nor->params->locking_ops->unlock(nor, ofs, len);

	spi_nor_unlock_and_unprep(nor);
	वापस ret;
पूर्ण

अटल पूर्णांक spi_nor_is_locked(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा spi_nor *nor = mtd_to_spi_nor(mtd);
	पूर्णांक ret;

	ret = spi_nor_lock_and_prep(nor);
	अगर (ret)
		वापस ret;

	ret = nor->params->locking_ops->is_locked(nor, ofs, len);

	spi_nor_unlock_and_unprep(nor);
	वापस ret;
पूर्ण

/**
 * spi_nor_try_unlock_all() - Tries to unlock the entire flash memory array.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'.
 *
 * Some SPI NOR flashes are ग_लिखो रक्षित by शेष after a घातer-on reset
 * cycle, in order to aव्योम inadvertent ग_लिखोs during घातer-up. Backward
 * compatibility imposes to unlock the entire flash memory array at घातer-up
 * by शेष.
 *
 * Unprotecting the entire flash array will fail क्रम boards which are hardware
 * ग_लिखो-रक्षित. Thus any errors are ignored.
 */
व्योम spi_nor_try_unlock_all(काष्ठा spi_nor *nor)
अणु
	पूर्णांक ret;

	अगर (!(nor->flags & SNOR_F_HAS_LOCK))
		वापस;

	dev_dbg(nor->dev, "Unprotecting entire flash array\n");

	ret = spi_nor_unlock(&nor->mtd, 0, nor->params->size);
	अगर (ret)
		dev_dbg(nor->dev, "Failed to unlock the entire flash memory array\n");
पूर्ण

व्योम spi_nor_रेजिस्टर_locking_ops(काष्ठा spi_nor *nor)
अणु
	काष्ठा mtd_info *mtd = &nor->mtd;

	अगर (!nor->params->locking_ops)
		वापस;

	mtd->_lock = spi_nor_lock;
	mtd->_unlock = spi_nor_unlock;
	mtd->_is_locked = spi_nor_is_locked;
पूर्ण
