<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित FWH_LOCK_H
#घोषणा FWH_LOCK_H


क्रमागत fwh_lock_state अणु
        FWH_UNLOCKED   = 0,
	FWH_DENY_WRITE = 1,
	FWH_IMMUTABLE  = 2,
	FWH_DENY_READ  = 4,
पूर्ण;

काष्ठा fwh_xxlock_thunk अणु
	क्रमागत fwh_lock_state val;
	flstate_t state;
पूर्ण;


#घोषणा FWH_XXLOCK_ONEBLOCK_LOCK   ((काष्ठा fwh_xxlock_thunk)अणु FWH_DENY_WRITE, FL_LOCKINGपूर्ण)
#घोषणा FWH_XXLOCK_ONEBLOCK_UNLOCK ((काष्ठा fwh_xxlock_thunk)अणु FWH_UNLOCKED,   FL_UNLOCKINGपूर्ण)

/*
 * This locking/unlock is specअगरic to firmware hub parts.  Only one
 * is known that supports the Intel command set.    Firmware
 * hub parts cannot be पूर्णांकerleaved as they are on the LPC bus
 * so this code has not been tested with पूर्णांकerleaved chips,
 * and will likely fail in that context.
 */
अटल पूर्णांक fwh_xxlock_oneblock(काष्ठा map_info *map, काष्ठा flchip *chip,
	अचिन्हित दीर्घ adr, पूर्णांक len, व्योम *thunk)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा fwh_xxlock_thunk *xxlt = (काष्ठा fwh_xxlock_thunk *)thunk;
	पूर्णांक ret;

	/* Refuse the operation अगर the we cannot look behind the chip */
	अगर (chip->start < 0x400000) अणु
		pr_debug( "MTD %s(): chip->start: %lx wanted >= 0x400000\n",
			__func__, chip->start );
		वापस -EIO;
	पूर्ण
	/*
	 * lock block रेजिस्टरs:
	 * - on 64k boundariesand
	 * - bit 1 set high
	 * - block lock रेजिस्टरs are 4MiB lower - overflow subtract (danger)
	 *
	 * The address manipulation is first करोne on the logical address
	 * which is 0 at the start of the chip, and then the offset of
	 * the inभागidual chip is addted to it.  Any other order a weird
	 * map offset could cause problems.
	 */
	adr = (adr & ~0xffffUL) | 0x2;
	adr += chip->start - 0x400000;

	/*
	 * This is easy because these are ग_लिखोs to रेजिस्टरs and not ग_लिखोs
	 * to flash memory - that means that we करोn't have to check status
	 * and समयout.
	 */
	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, FL_LOCKING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	chip->oldstate = chip->state;
	chip->state = xxlt->state;
	map_ग_लिखो(map, CMD(xxlt->val), adr);

	/* Done and happy. */
	chip->state = chip->oldstate;
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण


अटल पूर्णांक fwh_lock_varsize(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

	ret = cfi_varsize_frob(mtd, fwh_xxlock_oneblock, ofs, len,
		(व्योम *)&FWH_XXLOCK_ONEBLOCK_LOCK);

	वापस ret;
पूर्ण


अटल पूर्णांक fwh_unlock_varsize(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

	ret = cfi_varsize_frob(mtd, fwh_xxlock_oneblock, ofs, len,
		(व्योम *)&FWH_XXLOCK_ONEBLOCK_UNLOCK);

	वापस ret;
पूर्ण

अटल व्योम fixup_use_fwh_lock(काष्ठा mtd_info *mtd)
अणु
	prपूर्णांकk(KERN_NOTICE "using fwh lock/unlock method\n");
	/* Setup क्रम the chips with the fwh lock method */
	mtd->_lock   = fwh_lock_varsize;
	mtd->_unlock = fwh_unlock_varsize;
पूर्ण
#पूर्ण_अगर /* FWH_LOCK_H */
