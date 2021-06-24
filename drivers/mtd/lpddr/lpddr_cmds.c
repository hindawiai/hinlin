<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LPDDR flash memory device operations. This module provides पढ़ो, ग_लिखो,
 * erase, lock/unlock support क्रम LPDDR flash memories
 * (C) 2008 Korolev Alexey <akorolev@infradead.org>
 * (C) 2008 Vasiliy Leonenko <vasiliy.leonenko@gmail.com>
 * Many thanks to Roman Borisov क्रम initial enabling
 *
 * TODO:
 * Implement VPP management
 * Implement XIP support
 * Implement OTP support
 */
#समावेश <linux/mtd/pfow.h>
#समावेश <linux/mtd/qinfo.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

अटल पूर्णांक lpddr_पढ़ो(काष्ठा mtd_info *mtd, loff_t adr, माप_प्रकार len,
					माप_प्रकार *retlen, u_अक्षर *buf);
अटल पूर्णांक lpddr_ग_लिखो_buffers(काष्ठा mtd_info *mtd, loff_t to,
				माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf);
अटल पूर्णांक lpddr_ग_लिखोv(काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
				अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen);
अटल पूर्णांक lpddr_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr);
अटल पूर्णांक lpddr_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक lpddr_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक lpddr_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t adr, माप_प्रकार len,
			माप_प्रकार *retlen, व्योम **mtdbuf, resource_माप_प्रकार *phys);
अटल पूर्णांक lpddr_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t adr, माप_प्रकार len);
अटल पूर्णांक get_chip(काष्ठा map_info *map, काष्ठा flchip *chip, पूर्णांक mode);
अटल पूर्णांक chip_पढ़ोy(काष्ठा map_info *map, काष्ठा flchip *chip, पूर्णांक mode);
अटल व्योम put_chip(काष्ठा map_info *map, काष्ठा flchip *chip);

काष्ठा mtd_info *lpddr_cmdset(काष्ठा map_info *map)
अणु
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	काष्ठा flchip_shared *shared;
	काष्ठा flchip *chip;
	काष्ठा mtd_info *mtd;
	पूर्णांक numchips;
	पूर्णांक i, j;

	mtd = kzalloc(माप(*mtd), GFP_KERNEL);
	अगर (!mtd)
		वापस शून्य;
	mtd->priv = map;
	mtd->type = MTD_NORFLASH;

	/* Fill in the शेष mtd operations */
	mtd->_पढ़ो = lpddr_पढ़ो;
	mtd->type = MTD_NORFLASH;
	mtd->flags = MTD_CAP_NORFLASH;
	mtd->flags &= ~MTD_BIT_WRITEABLE;
	mtd->_erase = lpddr_erase;
	mtd->_ग_लिखो = lpddr_ग_लिखो_buffers;
	mtd->_ग_लिखोv = lpddr_ग_लिखोv;
	mtd->_lock = lpddr_lock;
	mtd->_unlock = lpddr_unlock;
	अगर (map_is_linear(map)) अणु
		mtd->_poपूर्णांक = lpddr_poपूर्णांक;
		mtd->_unpoपूर्णांक = lpddr_unpoपूर्णांक;
	पूर्ण
	mtd->size = 1 << lpddr->qinfo->DevSizeShअगरt;
	mtd->erasesize = 1 << lpddr->qinfo->UnअगरormBlockSizeShअगरt;
	mtd->ग_लिखोsize = 1 << lpddr->qinfo->BufSizeShअगरt;

	shared = kदो_स्मृति_array(lpddr->numchips, माप(काष्ठा flchip_shared),
						GFP_KERNEL);
	अगर (!shared) अणु
		kमुक्त(mtd);
		वापस शून्य;
	पूर्ण

	chip = &lpddr->chips[0];
	numchips = lpddr->numchips / lpddr->qinfo->HWPartsNum;
	क्रम (i = 0; i < numchips; i++) अणु
		shared[i].writing = shared[i].erasing = शून्य;
		mutex_init(&shared[i].lock);
		क्रम (j = 0; j < lpddr->qinfo->HWPartsNum; j++) अणु
			*chip = lpddr->chips[i];
			chip->start += j << lpddr->chipshअगरt;
			chip->oldstate = chip->state = FL_READY;
			chip->priv = &shared[i];
			/* those should be reset too since
			   they create memory references. */
			init_रुकोqueue_head(&chip->wq);
			mutex_init(&chip->mutex);
			chip++;
		पूर्ण
	पूर्ण

	वापस mtd;
पूर्ण
EXPORT_SYMBOL(lpddr_cmdset);

अटल व्योम prपूर्णांक_drs_error(अचिन्हित पूर्णांक dsr)
अणु
	पूर्णांक prog_status = (dsr & DSR_RPS) >> 8;

	अगर (!(dsr & DSR_AVAILABLE))
		pr_notice("DSR.15: (0) Device not Available\n");
	अगर ((prog_status & 0x03) == 0x03)
		pr_notice("DSR.9,8: (11) Attempt to program invalid half with 41h command\n");
	अन्यथा अगर (prog_status & 0x02)
		pr_notice("DSR.9,8: (10) Object Mode Program attempt in region with Control Mode data\n");
	अन्यथा अगर (prog_status &  0x01)
		pr_notice("DSR.9,8: (01) Program attempt in region with Object Mode data\n");
	अगर (!(dsr & DSR_READY_STATUS))
		pr_notice("DSR.7: (0) Device is Busy\n");
	अगर (dsr & DSR_ESS)
		pr_notice("DSR.6: (1) Erase Suspended\n");
	अगर (dsr & DSR_ERASE_STATUS)
		pr_notice("DSR.5: (1) Erase/Blank check error\n");
	अगर (dsr & DSR_PROGRAM_STATUS)
		pr_notice("DSR.4: (1) Program Error\n");
	अगर (dsr & DSR_VPPS)
		pr_notice("DSR.3: (1) Vpp low detect, operation aborted\n");
	अगर (dsr & DSR_PSS)
		pr_notice("DSR.2: (1) Program suspended\n");
	अगर (dsr & DSR_DPS)
		pr_notice("DSR.1: (1) Aborted Erase/Program attempt on locked block\n");
पूर्ण

अटल पूर्णांक रुको_क्रम_पढ़ोy(काष्ठा map_info *map, काष्ठा flchip *chip,
		अचिन्हित पूर्णांक chip_op_समय)
अणु
	अचिन्हित पूर्णांक समयo, reset_समयo, sleep_समय;
	अचिन्हित पूर्णांक dsr;
	flstate_t chip_state = chip->state;
	पूर्णांक ret = 0;

	/* set our समयout to 8 बार the expected delay */
	समयo = chip_op_समय * 8;
	अगर (!समयo)
		समयo = 500000;
	reset_समयo = समयo;
	sleep_समय = chip_op_समय / 2;

	क्रम (;;) अणु
		dsr = CMDVAL(map_पढ़ो(map, map->pfow_base + PFOW_DSR));
		अगर (dsr & DSR_READY_STATUS)
			अवरोध;
		अगर (!समयo) अणु
			prपूर्णांकk(KERN_ERR "%s: Flash timeout error state %d \n",
							map->name, chip_state);
			ret = -ETIME;
			अवरोध;
		पूर्ण

		/* OK Still रुकोing. Drop the lock, रुको a जबतक and retry. */
		mutex_unlock(&chip->mutex);
		अगर (sleep_समय >= 1000000/HZ) अणु
			/*
			 * Half of the normal delay still reमुख्यing
			 * can be perक्रमmed with a sleeping delay instead
			 * of busy रुकोing.
			 */
			msleep(sleep_समय/1000);
			समयo -= sleep_समय;
			sleep_समय = 1000000/HZ;
		पूर्ण अन्यथा अणु
			udelay(1);
			cond_resched();
			समयo--;
		पूर्ण
		mutex_lock(&chip->mutex);

		जबतक (chip->state != chip_state) अणु
			/* Someone's suspended the operation: sleep */
			DECLARE_WAITQUEUE(रुको, current);
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			mutex_lock(&chip->mutex);
		पूर्ण
		अगर (chip->erase_suspended || chip->ग_लिखो_suspended)  अणु
			/* Suspend has occurred जबतक sleep: reset समयout */
			समयo = reset_समयo;
			chip->erase_suspended = chip->ग_लिखो_suspended = 0;
		पूर्ण
	पूर्ण
	/* check status क्रम errors */
	अगर (dsr & DSR_ERR) अणु
		/* Clear DSR*/
		map_ग_लिखो(map, CMD(~(DSR_ERR)), map->pfow_base + PFOW_DSR);
		prपूर्णांकk(KERN_WARNING"%s: Bad status on wait: 0x%x \n",
				map->name, dsr);
		prपूर्णांक_drs_error(dsr);
		ret = -EIO;
	पूर्ण
	chip->state = FL_READY;
	वापस ret;
पूर्ण

अटल पूर्णांक get_chip(काष्ठा map_info *map, काष्ठा flchip *chip, पूर्णांक mode)
अणु
	पूर्णांक ret;
	DECLARE_WAITQUEUE(रुको, current);

 retry:
	अगर (chip->priv && (mode == FL_WRITING || mode == FL_ERASING)
		&& chip->state != FL_SYNCING) अणु
		/*
		 * OK. We have possibility क्रम contension on the ग_लिखो/erase
		 * operations which are global to the real chip and not per
		 * partition.  So let's fight it over in the partition which
		 * currently has authority on the operation.
		 *
		 * The rules are as follows:
		 *
		 * - any ग_लिखो operation must own shared->writing.
		 *
		 * - any erase operation must own _both_ shared->writing and
		 *   shared->erasing.
		 *
		 * - contension arbitration is handled in the owner's context.
		 *
		 * The 'shared' काष्ठा can be पढ़ो and/or written only when
		 * its lock is taken.
		 */
		काष्ठा flchip_shared *shared = chip->priv;
		काष्ठा flchip *contender;
		mutex_lock(&shared->lock);
		contender = shared->writing;
		अगर (contender && contender != chip) अणु
			/*
			 * The engine to perक्रमm desired operation on this
			 * partition is alपढ़ोy in use by someone अन्यथा.
			 * Let's fight over it in the context of the chip
			 * currently using it.  If it is possible to suspend,
			 * that other partition will करो just that, otherwise
			 * it'll happily send us to sleep.  In any हाल, when
			 * get_chip वापसs success we're clear to go ahead.
			 */
			ret = mutex_trylock(&contender->mutex);
			mutex_unlock(&shared->lock);
			अगर (!ret)
				जाओ retry;
			mutex_unlock(&chip->mutex);
			ret = chip_पढ़ोy(map, contender, mode);
			mutex_lock(&chip->mutex);

			अगर (ret == -EAGAIN) अणु
				mutex_unlock(&contender->mutex);
				जाओ retry;
			पूर्ण
			अगर (ret) अणु
				mutex_unlock(&contender->mutex);
				वापस ret;
			पूर्ण
			mutex_lock(&shared->lock);

			/* We should not own chip अगर it is alपढ़ोy in FL_SYNCING
			 * state. Put contender and retry. */
			अगर (chip->state == FL_SYNCING) अणु
				put_chip(map, contender);
				mutex_unlock(&contender->mutex);
				जाओ retry;
			पूर्ण
			mutex_unlock(&contender->mutex);
		पूर्ण

		/* Check अगर we have suspended erase on this chip.
		   Must sleep in such a हाल. */
		अगर (mode == FL_ERASING && shared->erasing
		    && shared->erasing->oldstate == FL_ERASING) अणु
			mutex_unlock(&shared->lock);
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			mutex_lock(&chip->mutex);
			जाओ retry;
		पूर्ण

		/* We now own it */
		shared->writing = chip;
		अगर (mode == FL_ERASING)
			shared->erasing = chip;
		mutex_unlock(&shared->lock);
	पूर्ण

	ret = chip_पढ़ोy(map, chip, mode);
	अगर (ret == -EAGAIN)
		जाओ retry;

	वापस ret;
पूर्ण

अटल पूर्णांक chip_पढ़ोy(काष्ठा map_info *map, काष्ठा flchip *chip, पूर्णांक mode)
अणु
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	पूर्णांक ret = 0;
	DECLARE_WAITQUEUE(रुको, current);

	/* Prevent setting state FL_SYNCING क्रम chip in suspended state. */
	अगर (FL_SYNCING == mode && FL_READY != chip->oldstate)
		जाओ sleep;

	चयन (chip->state) अणु
	हाल FL_READY:
	हाल FL_JEDEC_QUERY:
		वापस 0;

	हाल FL_ERASING:
		अगर (!lpddr->qinfo->SuspEraseSupp ||
			!(mode == FL_READY || mode == FL_POINT))
			जाओ sleep;

		map_ग_लिखो(map, CMD(LPDDR_SUSPEND),
			map->pfow_base + PFOW_PROGRAM_ERASE_SUSPEND);
		chip->oldstate = FL_ERASING;
		chip->state = FL_ERASE_SUSPENDING;
		ret = रुको_क्रम_पढ़ोy(map, chip, 0);
		अगर (ret) अणु
			/* Oops. something got wrong. */
			/* Resume and pretend we weren't here.  */
			put_chip(map, chip);
			prपूर्णांकk(KERN_ERR "%s: suspend operation failed."
					"State may be wrong \n", map->name);
			वापस -EIO;
		पूर्ण
		chip->erase_suspended = 1;
		chip->state = FL_READY;
		वापस 0;
		/* Erase suspend */
	हाल FL_POINT:
		/* Only अगर there's no operation suspended... */
		अगर (mode == FL_READY && chip->oldstate == FL_READY)
			वापस 0;
		fallthrough;
	शेष:
sleep:
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&chip->wq, &रुको);
		mutex_unlock(&chip->mutex);
		schedule();
		हटाओ_रुको_queue(&chip->wq, &रुको);
		mutex_lock(&chip->mutex);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

अटल व्योम put_chip(काष्ठा map_info *map, काष्ठा flchip *chip)
अणु
	अगर (chip->priv) अणु
		काष्ठा flchip_shared *shared = chip->priv;
		mutex_lock(&shared->lock);
		अगर (shared->writing == chip && chip->oldstate == FL_READY) अणु
			/* We own the ability to ग_लिखो, but we're करोne */
			shared->writing = shared->erasing;
			अगर (shared->writing && shared->writing != chip) अणु
				/* give back the ownership */
				काष्ठा flchip *loaner = shared->writing;
				mutex_lock(&loaner->mutex);
				mutex_unlock(&shared->lock);
				mutex_unlock(&chip->mutex);
				put_chip(map, loaner);
				mutex_lock(&chip->mutex);
				mutex_unlock(&loaner->mutex);
				wake_up(&chip->wq);
				वापस;
			पूर्ण
			shared->erasing = शून्य;
			shared->writing = शून्य;
		पूर्ण अन्यथा अगर (shared->erasing == chip && shared->writing != chip) अणु
			/*
			 * We own the ability to erase without the ability
			 * to ग_लिखो, which means the erase was suspended
			 * and some other partition is currently writing.
			 * Don't let the चयन below mess things up since
			 * we करोn't have ownership to resume anything.
			 */
			mutex_unlock(&shared->lock);
			wake_up(&chip->wq);
			वापस;
		पूर्ण
		mutex_unlock(&shared->lock);
	पूर्ण

	चयन (chip->oldstate) अणु
	हाल FL_ERASING:
		map_ग_लिखो(map, CMD(LPDDR_RESUME),
				map->pfow_base + PFOW_COMMAND_CODE);
		map_ग_लिखो(map, CMD(LPDDR_START_EXECUTION),
				map->pfow_base + PFOW_COMMAND_EXECUTE);
		chip->oldstate = FL_READY;
		chip->state = FL_ERASING;
		अवरोध;
	हाल FL_READY:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: put_chip() called with oldstate %d!\n",
				map->name, chip->oldstate);
	पूर्ण
	wake_up(&chip->wq);
पूर्ण

अटल पूर्णांक करो_ग_लिखो_buffer(काष्ठा map_info *map, काष्ठा flchip *chip,
			अचिन्हित दीर्घ adr, स्थिर काष्ठा kvec **pvec,
			अचिन्हित दीर्घ *pvec_seek, पूर्णांक len)
अणु
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	map_word datum;
	पूर्णांक ret, wbufsize, word_gap, words;
	स्थिर काष्ठा kvec *vec;
	अचिन्हित दीर्घ vec_seek;
	अचिन्हित दीर्घ prog_buf_ofs;

	wbufsize = 1 << lpddr->qinfo->BufSizeShअगरt;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, FL_WRITING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण
	/* Figure out the number of words to ग_लिखो */
	word_gap = (-adr & (map_bankwidth(map)-1));
	words = (len - word_gap + map_bankwidth(map) - 1) / map_bankwidth(map);
	अगर (!word_gap) अणु
		words--;
	पूर्ण अन्यथा अणु
		word_gap = map_bankwidth(map) - word_gap;
		adr -= word_gap;
		datum = map_word_ff(map);
	पूर्ण
	/* Write data */
	/* Get the program buffer offset from PFOW रेजिस्टर data first*/
	prog_buf_ofs = map->pfow_base + CMDVAL(map_पढ़ो(map,
				map->pfow_base + PFOW_PROGRAM_BUFFER_OFFSET));
	vec = *pvec;
	vec_seek = *pvec_seek;
	करो अणु
		पूर्णांक n = map_bankwidth(map) - word_gap;

		अगर (n > vec->iov_len - vec_seek)
			n = vec->iov_len - vec_seek;
		अगर (n > len)
			n = len;

		अगर (!word_gap && (len < map_bankwidth(map)))
			datum = map_word_ff(map);

		datum = map_word_load_partial(map, datum,
				vec->iov_base + vec_seek, word_gap, n);

		len -= n;
		word_gap += n;
		अगर (!len || word_gap == map_bankwidth(map)) अणु
			map_ग_लिखो(map, datum, prog_buf_ofs);
			prog_buf_ofs += map_bankwidth(map);
			word_gap = 0;
		पूर्ण

		vec_seek += n;
		अगर (vec_seek == vec->iov_len) अणु
			vec++;
			vec_seek = 0;
		पूर्ण
	पूर्ण जबतक (len);
	*pvec = vec;
	*pvec_seek = vec_seek;

	/* GO GO GO */
	send_pfow_command(map, LPDDR_BUFF_PROGRAM, adr, wbufsize, शून्य);
	chip->state = FL_WRITING;
	ret = रुको_क्रम_पढ़ोy(map, chip, (1<<lpddr->qinfo->ProgBufferTime));
	अगर (ret)	अणु
		prपूर्णांकk(KERN_WARNING"%s Buffer program error: %d at %lx; \n",
			map->name, ret, adr);
		जाओ out;
	पूर्ण

 out:	put_chip(map, chip);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_erase_oneblock(काष्ठा mtd_info *mtd, loff_t adr)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	पूर्णांक chipnum = adr >> lpddr->chipshअगरt;
	काष्ठा flchip *chip = &lpddr->chips[chipnum];
	पूर्णांक ret;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, FL_ERASING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण
	send_pfow_command(map, LPDDR_BLOCK_ERASE, adr, 0, शून्य);
	chip->state = FL_ERASING;
	ret = रुको_क्रम_पढ़ोy(map, chip, (1<<lpddr->qinfo->BlockEraseTime)*1000);
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING"%s Erase block error %d at : %llx\n",
			map->name, ret, adr);
		जाओ out;
	पूर्ण
 out:	put_chip(map, chip);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक lpddr_पढ़ो(काष्ठा mtd_info *mtd, loff_t adr, माप_प्रकार len,
			माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	पूर्णांक chipnum = adr >> lpddr->chipshअगरt;
	काष्ठा flchip *chip = &lpddr->chips[chipnum];
	पूर्णांक ret = 0;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, FL_READY);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	map_copy_from(map, buf, adr, len);
	*retlen = len;

	put_chip(map, chip);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक lpddr_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t adr, माप_प्रकार len,
			माप_प्रकार *retlen, व्योम **mtdbuf, resource_माप_प्रकार *phys)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	पूर्णांक chipnum = adr >> lpddr->chipshअगरt;
	अचिन्हित दीर्घ ofs, last_end = 0;
	काष्ठा flchip *chip = &lpddr->chips[chipnum];
	पूर्णांक ret = 0;

	अगर (!map->virt)
		वापस -EINVAL;

	/* ofs: offset within the first chip that the first पढ़ो should start */
	ofs = adr - (chipnum << lpddr->chipshअगरt);
	*mtdbuf = (व्योम *)map->virt + chip->start + ofs;

	जबतक (len) अणु
		अचिन्हित दीर्घ thislen;

		अगर (chipnum >= lpddr->numchips)
			अवरोध;

		/* We cannot poपूर्णांक across chips that are भवly disjoपूर्णांक */
		अगर (!last_end)
			last_end = chip->start;
		अन्यथा अगर (chip->start != last_end)
			अवरोध;

		अगर ((len + ofs - 1) >> lpddr->chipshअगरt)
			thislen = (1<<lpddr->chipshअगरt) - ofs;
		अन्यथा
			thislen = len;
		/* get the chip */
		mutex_lock(&chip->mutex);
		ret = get_chip(map, chip, FL_POINT);
		mutex_unlock(&chip->mutex);
		अगर (ret)
			अवरोध;

		chip->state = FL_POINT;
		chip->ref_poपूर्णांक_counter++;
		*retlen += thislen;
		len -= thislen;

		ofs = 0;
		last_end += 1 << lpddr->chipshअगरt;
		chipnum++;
		chip = &lpddr->chips[chipnum];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lpddr_unpoपूर्णांक (काष्ठा mtd_info *mtd, loff_t adr, माप_प्रकार len)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	पूर्णांक chipnum = adr >> lpddr->chipshअगरt, err = 0;
	अचिन्हित दीर्घ ofs;

	/* ofs: offset within the first chip that the first पढ़ो should start */
	ofs = adr - (chipnum << lpddr->chipshअगरt);

	जबतक (len) अणु
		अचिन्हित दीर्घ thislen;
		काष्ठा flchip *chip;

		chip = &lpddr->chips[chipnum];
		अगर (chipnum >= lpddr->numchips)
			अवरोध;

		अगर ((len + ofs - 1) >> lpddr->chipshअगरt)
			thislen = (1<<lpddr->chipshअगरt) - ofs;
		अन्यथा
			thislen = len;

		mutex_lock(&chip->mutex);
		अगर (chip->state == FL_POINT) अणु
			chip->ref_poपूर्णांक_counter--;
			अगर (chip->ref_poपूर्णांक_counter == 0)
				chip->state = FL_READY;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "%s: Warning: unpoint called on non"
					"pointed region\n", map->name);
			err = -EINVAL;
		पूर्ण

		put_chip(map, chip);
		mutex_unlock(&chip->mutex);

		len -= thislen;
		ofs = 0;
		chipnum++;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक lpddr_ग_लिखो_buffers(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
				माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा kvec vec;

	vec.iov_base = (व्योम *) buf;
	vec.iov_len = len;

	वापस lpddr_ग_लिखोv(mtd, &vec, 1, to, retlen);
पूर्ण


अटल पूर्णांक lpddr_ग_लिखोv(काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
				अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	पूर्णांक ret = 0;
	पूर्णांक chipnum;
	अचिन्हित दीर्घ ofs, vec_seek, i;
	पूर्णांक wbufsize = 1 << lpddr->qinfo->BufSizeShअगरt;
	माप_प्रकार len = 0;

	क्रम (i = 0; i < count; i++)
		len += vecs[i].iov_len;

	अगर (!len)
		वापस 0;

	chipnum = to >> lpddr->chipshअगरt;

	ofs = to;
	vec_seek = 0;

	करो अणु
		/* We must not cross ग_लिखो block boundaries */
		पूर्णांक size = wbufsize - (ofs & (wbufsize-1));

		अगर (size > len)
			size = len;

		ret = करो_ग_लिखो_buffer(map, &lpddr->chips[chipnum],
					  ofs, &vecs, &vec_seek, size);
		अगर (ret)
			वापस ret;

		ofs += size;
		(*retlen) += size;
		len -= size;

		/* Be nice and reschedule with the chip in a usable
		 * state क्रम other processes */
		cond_resched();

	पूर्ण जबतक (len);

	वापस 0;
पूर्ण

अटल पूर्णांक lpddr_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	अचिन्हित दीर्घ ofs, len;
	पूर्णांक ret;
	काष्ठा map_info *map = mtd->priv;
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	पूर्णांक size = 1 << lpddr->qinfo->UnअगरormBlockSizeShअगरt;

	ofs = instr->addr;
	len = instr->len;

	जबतक (len > 0) अणु
		ret = करो_erase_oneblock(mtd, ofs);
		अगर (ret)
			वापस ret;
		ofs += size;
		len -= size;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DO_XXLOCK_LOCK		1
#घोषणा DO_XXLOCK_UNLOCK	2
अटल पूर्णांक करो_xxlock(काष्ठा mtd_info *mtd, loff_t adr, uपूर्णांक32_t len, पूर्णांक thunk)
अणु
	पूर्णांक ret = 0;
	काष्ठा map_info *map = mtd->priv;
	काष्ठा lpddr_निजी *lpddr = map->fldrv_priv;
	पूर्णांक chipnum = adr >> lpddr->chipshअगरt;
	काष्ठा flchip *chip = &lpddr->chips[chipnum];

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, FL_LOCKING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	अगर (thunk == DO_XXLOCK_LOCK) अणु
		send_pfow_command(map, LPDDR_LOCK_BLOCK, adr, adr + len, शून्य);
		chip->state = FL_LOCKING;
	पूर्ण अन्यथा अगर (thunk == DO_XXLOCK_UNLOCK) अणु
		send_pfow_command(map, LPDDR_UNLOCK_BLOCK, adr, adr + len, शून्य);
		chip->state = FL_UNLOCKING;
	पूर्ण अन्यथा
		BUG();

	ret = रुको_क्रम_पढ़ोy(map, chip, 1);
	अगर (ret)	अणु
		prपूर्णांकk(KERN_ERR "%s: block unlock error status %d \n",
				map->name, ret);
		जाओ out;
	पूर्ण
out:	put_chip(map, chip);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक lpddr_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस करो_xxlock(mtd, ofs, len, DO_XXLOCK_LOCK);
पूर्ण

अटल पूर्णांक lpddr_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस करो_xxlock(mtd, ofs, len, DO_XXLOCK_UNLOCK);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexey Korolev <akorolev@infradead.org>");
MODULE_DESCRIPTION("MTD driver for LPDDR flash chips");
