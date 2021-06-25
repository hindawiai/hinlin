<शैली गुरु>
/*
 * Common Flash Interface support:
 *   ST Advanced Architecture Command Set (ID 0x0020)
 *
 * (C) 2000 Red Hat. GPL'd
 *
 * 10/10/2000	Nicolas Pitre <nico@fluxnic.net>
 * 	- completely revamped method functions so they are aware and
 * 	  independent of the flash geometry (buswidth, पूर्णांकerleave, etc.)
 * 	- scalability vs code size is completely set at compile-समय
 * 	  (see include/linux/mtd/cfi.h क्रम selection)
 *	- optimized ग_लिखो buffer method
 * 06/21/2002	Joern Engel <joern@wh.fh-wedel.de> and others
 *	- modअगरied Intel Command Set 0x0001 to support ST Advanced Architecture
 *	  (command set 0x0020)
 *	- added a ग_लिखोv function
 * 07/13/2005	Joern Engel <joern@wh.fh-wedel.de>
 * 	- Plugged memory leak in cfi_staa_ग_लिखोv().
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/mtd.h>


अटल पूर्णांक cfi_staa_पढ़ो(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक cfi_staa_ग_लिखो_buffers(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);
अटल पूर्णांक cfi_staa_ग_लिखोv(काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
		अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen);
अटल पूर्णांक cfi_staa_erase_varsize(काष्ठा mtd_info *, काष्ठा erase_info *);
अटल व्योम cfi_staa_sync (काष्ठा mtd_info *);
अटल पूर्णांक cfi_staa_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक cfi_staa_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक cfi_staa_suspend (काष्ठा mtd_info *);
अटल व्योम cfi_staa_resume (काष्ठा mtd_info *);

अटल व्योम cfi_staa_destroy(काष्ठा mtd_info *);

काष्ठा mtd_info *cfi_cmdset_0020(काष्ठा map_info *, पूर्णांक);

अटल काष्ठा mtd_info *cfi_staa_setup (काष्ठा map_info *);

अटल काष्ठा mtd_chip_driver cfi_staa_chipdrv = अणु
	.probe		= शून्य, /* Not usable directly */
	.destroy	= cfi_staa_destroy,
	.name		= "cfi_cmdset_0020",
	.module		= THIS_MODULE
पूर्ण;

/* #घोषणा DEBUG_LOCK_BITS */
//#घोषणा DEBUG_CFI_FEATURES

#अगर_घोषित DEBUG_CFI_FEATURES
अटल व्योम cfi_tell_features(काष्ठा cfi_pri_पूर्णांकelext *extp)
अणु
        पूर्णांक i;
        prपूर्णांकk("  Feature/Command Support: %4.4X\n", extp->FeatureSupport);
	prपूर्णांकk("     - Chip Erase:         %s\n", extp->FeatureSupport&1?"supported":"unsupported");
	prपूर्णांकk("     - Suspend Erase:      %s\n", extp->FeatureSupport&2?"supported":"unsupported");
	prपूर्णांकk("     - Suspend Program:    %s\n", extp->FeatureSupport&4?"supported":"unsupported");
	prपूर्णांकk("     - Legacy Lock/Unlock: %s\n", extp->FeatureSupport&8?"supported":"unsupported");
	prपूर्णांकk("     - Queued Erase:       %s\n", extp->FeatureSupport&16?"supported":"unsupported");
	prपूर्णांकk("     - Instant block lock: %s\n", extp->FeatureSupport&32?"supported":"unsupported");
	prपूर्णांकk("     - Protection Bits:    %s\n", extp->FeatureSupport&64?"supported":"unsupported");
	prपूर्णांकk("     - Page-mode read:     %s\n", extp->FeatureSupport&128?"supported":"unsupported");
	prपूर्णांकk("     - Synchronous read:   %s\n", extp->FeatureSupport&256?"supported":"unsupported");
	क्रम (i=9; i<32; i++) अणु
		अगर (extp->FeatureSupport & (1<<i))
			prपूर्णांकk("     - Unknown Bit %X:      supported\n", i);
	पूर्ण

	prपूर्णांकk("  Supported functions after Suspend: %2.2X\n", extp->SuspendCmdSupport);
	prपूर्णांकk("     - Program after Erase Suspend: %s\n", extp->SuspendCmdSupport&1?"supported":"unsupported");
	क्रम (i=1; i<8; i++) अणु
		अगर (extp->SuspendCmdSupport & (1<<i))
			prपूर्णांकk("     - Unknown Bit %X:               supported\n", i);
	पूर्ण

	prपूर्णांकk("  Block Status Register Mask: %4.4X\n", extp->BlkStatusRegMask);
	prपूर्णांकk("     - Lock Bit Active:      %s\n", extp->BlkStatusRegMask&1?"yes":"no");
	prपूर्णांकk("     - Valid Bit Active:     %s\n", extp->BlkStatusRegMask&2?"yes":"no");
	क्रम (i=2; i<16; i++) अणु
		अगर (extp->BlkStatusRegMask & (1<<i))
			prपूर्णांकk("     - Unknown Bit %X Active: yes\n",i);
	पूर्ण

	prपूर्णांकk("  Vcc Logic Supply Optimum Program/Erase Voltage: %d.%d V\n",
	       extp->VccOptimal >> 8, extp->VccOptimal & 0xf);
	अगर (extp->VppOptimal)
		prपूर्णांकk("  Vpp Programming Supply Optimum Program/Erase Voltage: %d.%d V\n",
		       extp->VppOptimal >> 8, extp->VppOptimal & 0xf);
पूर्ण
#पूर्ण_अगर

/* This routine is made available to other mtd code via
 * पूर्णांकer_module_रेजिस्टर.  It must only be accessed through
 * पूर्णांकer_module_get which will bump the use count of this module.  The
 * addresses passed back in cfi are valid as दीर्घ as the use count of
 * this module is non-zero, i.e. between पूर्णांकer_module_get and
 * पूर्णांकer_module_put.  Keith Owens <kaos@ocs.com.au> 29 Oct 2000.
 */
काष्ठा mtd_info *cfi_cmdset_0020(काष्ठा map_info *map, पूर्णांक primary)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक i;

	अगर (cfi->cfi_mode) अणु
		/*
		 * It's a real CFI chip, not one क्रम which the probe
		 * routine faked a CFI काष्ठाure. So we पढ़ो the feature
		 * table from it.
		 */
		__u16 adr = primary?cfi->cfiq->P_ADR:cfi->cfiq->A_ADR;
		काष्ठा cfi_pri_पूर्णांकelext *extp;

		extp = (काष्ठा cfi_pri_पूर्णांकelext*)cfi_पढ़ो_pri(map, adr, माप(*extp), "ST Microelectronics");
		अगर (!extp)
			वापस शून्य;

		अगर (extp->MajorVersion != '1' ||
		    (extp->MinorVersion < '0' || extp->MinorVersion > '3')) अणु
			prपूर्णांकk(KERN_ERR "  Unknown ST Microelectronics"
			       " Extended Query version %c.%c.\n",
			       extp->MajorVersion, extp->MinorVersion);
			kमुक्त(extp);
			वापस शून्य;
		पूर्ण

		/* Do some byteswapping अगर necessary */
		extp->FeatureSupport = cfi32_to_cpu(map, extp->FeatureSupport);
		extp->BlkStatusRegMask = cfi32_to_cpu(map,
						extp->BlkStatusRegMask);

#अगर_घोषित DEBUG_CFI_FEATURES
		/* Tell the user about it in lots of lovely detail */
		cfi_tell_features(extp);
#पूर्ण_अगर

		/* Install our own निजी info काष्ठाure */
		cfi->cmdset_priv = extp;
	पूर्ण

	क्रम (i=0; i< cfi->numchips; i++) अणु
		cfi->chips[i].word_ग_लिखो_समय = 128;
		cfi->chips[i].buffer_ग_लिखो_समय = 128;
		cfi->chips[i].erase_समय = 1024;
		cfi->chips[i].ref_poपूर्णांक_counter = 0;
		init_रुकोqueue_head(&(cfi->chips[i].wq));
	पूर्ण

	वापस cfi_staa_setup(map);
पूर्ण
EXPORT_SYMBOL_GPL(cfi_cmdset_0020);

अटल काष्ठा mtd_info *cfi_staa_setup(काष्ठा map_info *map)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा mtd_info *mtd;
	अचिन्हित दीर्घ offset = 0;
	पूर्णांक i,j;
	अचिन्हित दीर्घ devsize = (1<<cfi->cfiq->DevSize) * cfi->पूर्णांकerleave;

	mtd = kzalloc(माप(*mtd), GFP_KERNEL);
	//prपूर्णांकk(KERN_DEBUG "number of CFI chips: %d\n", cfi->numchips);

	अगर (!mtd) अणु
		kमुक्त(cfi->cmdset_priv);
		वापस शून्य;
	पूर्ण

	mtd->priv = map;
	mtd->type = MTD_NORFLASH;
	mtd->size = devsize * cfi->numchips;

	mtd->numeraseregions = cfi->cfiq->NumEraseRegions * cfi->numchips;
	mtd->eraseregions = kदो_स्मृति_array(mtd->numeraseregions,
					  माप(काष्ठा mtd_erase_region_info),
					  GFP_KERNEL);
	अगर (!mtd->eraseregions) अणु
		kमुक्त(cfi->cmdset_priv);
		kमुक्त(mtd);
		वापस शून्य;
	पूर्ण

	क्रम (i=0; i<cfi->cfiq->NumEraseRegions; i++) अणु
		अचिन्हित दीर्घ ernum, ersize;
		ersize = ((cfi->cfiq->EraseRegionInfo[i] >> 8) & ~0xff) * cfi->पूर्णांकerleave;
		ernum = (cfi->cfiq->EraseRegionInfo[i] & 0xffff) + 1;

		अगर (mtd->erasesize < ersize) अणु
			mtd->erasesize = ersize;
		पूर्ण
		क्रम (j=0; j<cfi->numchips; j++) अणु
			mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].offset = (j*devsize)+offset;
			mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].erasesize = ersize;
			mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].numblocks = ernum;
		पूर्ण
		offset += (ersize * ernum);
	पूर्ण

	अगर (offset != devsize) अणु
		/* Argh */
		prपूर्णांकk(KERN_WARNING "Sum of regions (%lx) != total size of set of interleaved chips (%lx)\n", offset, devsize);
		kमुक्त(mtd->eraseregions);
		kमुक्त(cfi->cmdset_priv);
		kमुक्त(mtd);
		वापस शून्य;
	पूर्ण

	क्रम (i=0; i<mtd->numeraseregions;i++)अणु
		prपूर्णांकk(KERN_DEBUG "%d: offset=0x%llx,size=0x%x,blocks=%d\n",
		       i, (अचिन्हित दीर्घ दीर्घ)mtd->eraseregions[i].offset,
		       mtd->eraseregions[i].erasesize,
		       mtd->eraseregions[i].numblocks);
	पूर्ण

	/* Also select the correct geometry setup too */
	mtd->_erase = cfi_staa_erase_varsize;
	mtd->_पढ़ो = cfi_staa_पढ़ो;
	mtd->_ग_लिखो = cfi_staa_ग_लिखो_buffers;
	mtd->_ग_लिखोv = cfi_staa_ग_लिखोv;
	mtd->_sync = cfi_staa_sync;
	mtd->_lock = cfi_staa_lock;
	mtd->_unlock = cfi_staa_unlock;
	mtd->_suspend = cfi_staa_suspend;
	mtd->_resume = cfi_staa_resume;
	mtd->flags = MTD_CAP_NORFLASH & ~MTD_BIT_WRITEABLE;
	mtd->ग_लिखोsize = 8; /* FIXME: Should be 0 क्रम STMicro flashes w/out ECC */
	mtd->ग_लिखोbufsize = cfi_पूर्णांकerleave(cfi) << cfi->cfiq->MaxBufWriteSize;
	map->fldrv = &cfi_staa_chipdrv;
	__module_get(THIS_MODULE);
	mtd->name = map->name;
	वापस mtd;
पूर्ण


अटल अंतरभूत पूर्णांक करो_पढ़ो_onechip(काष्ठा map_info *map, काष्ठा flchip *chip, loff_t adr, माप_प्रकार len, u_अक्षर *buf)
अणु
	map_word status, status_OK;
	अचिन्हित दीर्घ समयo;
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक suspended = 0;
	अचिन्हित दीर्घ cmd_addr;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	adr += chip->start;

	/* Ensure cmd पढ़ो/ग_लिखोs are aligned. */
	cmd_addr = adr & ~(map_bankwidth(map)-1);

	/* Let's determine this according to the पूर्णांकerleave only once */
	status_OK = CMD(0x80);

	समयo = jअगरfies + HZ;
 retry:
	mutex_lock(&chip->mutex);

	/* Check that the chip's पढ़ोy to talk to us.
	 * If it's in FL_ERASING state, suspend it and make it talk now.
	 */
	चयन (chip->state) अणु
	हाल FL_ERASING:
		अगर (!(((काष्ठा cfi_pri_पूर्णांकelext *)cfi->cmdset_priv)->FeatureSupport & 2))
			जाओ sleep; /* We करोn't support erase suspend */

		map_ग_लिखो (map, CMD(0xb0), cmd_addr);
		/* If the flash has finished erasing, then 'erase suspend'
		 * appears to make some (28F320) flash devices चयन to
		 * 'read' mode.  Make sure that we switch to 'read status'
		 * mode so we get the right data. --rmk
		 */
		map_ग_लिखो(map, CMD(0x70), cmd_addr);
		chip->oldstate = FL_ERASING;
		chip->state = FL_ERASE_SUSPENDING;
		//		prपूर्णांकk("Erase suspending at 0x%lx\n", cmd_addr);
		क्रम (;;) अणु
			status = map_पढ़ो(map, cmd_addr);
			अगर (map_word_andequal(map, status, status_OK, status_OK))
				अवरोध;

			अगर (समय_after(jअगरfies, समयo)) अणु
				/* Urgh */
				map_ग_लिखो(map, CMD(0xd0), cmd_addr);
				/* make sure we're in 'read status' mode */
				map_ग_लिखो(map, CMD(0x70), cmd_addr);
				chip->state = FL_ERASING;
				wake_up(&chip->wq);
				mutex_unlock(&chip->mutex);
				prपूर्णांकk(KERN_ERR "Chip not ready after erase "
				       "suspended: status = 0x%lx\n", status.x[0]);
				वापस -EIO;
			पूर्ण

			mutex_unlock(&chip->mutex);
			cfi_udelay(1);
			mutex_lock(&chip->mutex);
		पूर्ण

		suspended = 1;
		map_ग_लिखो(map, CMD(0xff), cmd_addr);
		chip->state = FL_READY;
		अवरोध;

#अगर 0
	हाल FL_WRITING:
		/* Not quite yet */
#पूर्ण_अगर

	हाल FL_READY:
		अवरोध;

	हाल FL_CFI_QUERY:
	हाल FL_JEDEC_QUERY:
		map_ग_लिखो(map, CMD(0x70), cmd_addr);
		chip->state = FL_STATUS;
		fallthrough;
	हाल FL_STATUS:
		status = map_पढ़ो(map, cmd_addr);
		अगर (map_word_andequal(map, status, status_OK, status_OK)) अणु
			map_ग_लिखो(map, CMD(0xff), cmd_addr);
			chip->state = FL_READY;
			अवरोध;
		पूर्ण

		/* Urgh. Chip not yet पढ़ोy to talk to us. */
		अगर (समय_after(jअगरfies, समयo)) अणु
			mutex_unlock(&chip->mutex);
			prपूर्णांकk(KERN_ERR "waiting for chip to be ready timed out in read. WSM status = %lx\n", status.x[0]);
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		जाओ retry;

	शेष:
	sleep:
		/* Stick ourselves on a रुको queue to be woken when
		   someone changes the status */
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&chip->wq, &रुको);
		mutex_unlock(&chip->mutex);
		schedule();
		हटाओ_रुको_queue(&chip->wq, &रुको);
		समयo = jअगरfies + HZ;
		जाओ retry;
	पूर्ण

	map_copy_from(map, buf, adr, len);

	अगर (suspended) अणु
		chip->state = chip->oldstate;
		/* What अगर one पूर्णांकerleaved chip has finished and the
		   other hasn't? The old code would leave the finished
		   one in READY mode. That's bad, and caused -EROFS
		   errors to be वापसed from करो_erase_oneblock because
		   that's the only bit it checked क्रम at the समय.
		   As the state machine appears to explicitly allow
		   sending the 0x70 (Read Status) command to an erasing
		   chip and expecting it to be ignored, that's what we
		   करो. */
		map_ग_लिखो(map, CMD(0xd0), cmd_addr);
		map_ग_लिखो(map, CMD(0x70), cmd_addr);
	पूर्ण

	wake_up(&chip->wq);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक cfi_staa_पढ़ो (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ ofs;
	पूर्णांक chipnum;
	पूर्णांक ret = 0;

	/* ofs: offset within the first chip that the first पढ़ो should start */
	chipnum = (from >> cfi->chipshअगरt);
	ofs = from - (chipnum <<  cfi->chipshअगरt);

	जबतक (len) अणु
		अचिन्हित दीर्घ thislen;

		अगर (chipnum >= cfi->numchips)
			अवरोध;

		अगर ((len + ofs -1) >> cfi->chipshअगरt)
			thislen = (1<<cfi->chipshअगरt) - ofs;
		अन्यथा
			thislen = len;

		ret = करो_पढ़ो_onechip(map, &cfi->chips[chipnum], ofs, thislen, buf);
		अगर (ret)
			अवरोध;

		*retlen += thislen;
		len -= thislen;
		buf += thislen;

		ofs = 0;
		chipnum++;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक करो_ग_लिखो_buffer(काष्ठा map_info *map, काष्ठा flchip *chip,
				  अचिन्हित दीर्घ adr, स्थिर u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status, status_OK;
	अचिन्हित दीर्घ cmd_adr, समयo;
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक wbufsize, z;

        /* M58LW064A requires bus alignment क्रम buffer wriets -- saw */
        अगर (adr & (map_bankwidth(map)-1))
            वापस -EINVAL;

        wbufsize = cfi_पूर्णांकerleave(cfi) << cfi->cfiq->MaxBufWriteSize;
        adr += chip->start;
	cmd_adr = adr & ~(wbufsize-1);

	/* Let's determine this according to the पूर्णांकerleave only once */
        status_OK = CMD(0x80);

	समयo = jअगरfies + HZ;
 retry:

#अगर_घोषित DEBUG_CFI_FEATURES
       prपूर्णांकk("%s: chip->state[%d]\n", __func__, chip->state);
#पूर्ण_अगर
	mutex_lock(&chip->mutex);

	/* Check that the chip's पढ़ोy to talk to us.
	 * Later, we can actually think about पूर्णांकerrupting it
	 * अगर it's in FL_ERASING state.
	 * Not just yet, though.
	 */
	चयन (chip->state) अणु
	हाल FL_READY:
		अवरोध;

	हाल FL_CFI_QUERY:
	हाल FL_JEDEC_QUERY:
		map_ग_लिखो(map, CMD(0x70), cmd_adr);
                chip->state = FL_STATUS;
#अगर_घोषित DEBUG_CFI_FEATURES
	prपूर्णांकk("%s: 1 status[%x]\n", __func__, map_पढ़ो(map, cmd_adr));
#पूर्ण_अगर
		fallthrough;
	हाल FL_STATUS:
		status = map_पढ़ो(map, cmd_adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;
		/* Urgh. Chip not yet पढ़ोy to talk to us. */
		अगर (समय_after(jअगरfies, समयo)) अणु
			mutex_unlock(&chip->mutex);
                        prपूर्णांकk(KERN_ERR "waiting for chip to be ready timed out in buffer write Xstatus = %lx, status = %lx\n",
                               status.x[0], map_पढ़ो(map, cmd_adr).x[0]);
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		जाओ retry;

	शेष:
		/* Stick ourselves on a रुको queue to be woken when
		   someone changes the status */
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&chip->wq, &रुको);
		mutex_unlock(&chip->mutex);
		schedule();
		हटाओ_रुको_queue(&chip->wq, &रुको);
		समयo = jअगरfies + HZ;
		जाओ retry;
	पूर्ण

	ENABLE_VPP(map);
	map_ग_लिखो(map, CMD(0xe8), cmd_adr);
	chip->state = FL_WRITING_TO_BUFFER;

	z = 0;
	क्रम (;;) अणु
		status = map_पढ़ो(map, cmd_adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		mutex_lock(&chip->mutex);

		अगर (++z > 100) अणु
			/* Argh. Not पढ़ोy क्रम ग_लिखो to buffer */
			DISABLE_VPP(map);
                        map_ग_लिखो(map, CMD(0x70), cmd_adr);
			chip->state = FL_STATUS;
			mutex_unlock(&chip->mutex);
			prपूर्णांकk(KERN_ERR "Chip not ready for buffer write. Xstatus = %lx\n", status.x[0]);
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* Write length of data to come */
	map_ग_लिखो(map, CMD(len/map_bankwidth(map)-1), cmd_adr );

	/* Write data */
	क्रम (z = 0; z < len;
	     z += map_bankwidth(map), buf += map_bankwidth(map)) अणु
		map_word d;
		d = map_word_load(map, buf);
		map_ग_लिखो(map, d, adr+z);
	पूर्ण
	/* GO GO GO */
	map_ग_लिखो(map, CMD(0xd0), cmd_adr);
	chip->state = FL_WRITING;

	mutex_unlock(&chip->mutex);
	cfi_udelay(chip->buffer_ग_लिखो_समय);
	mutex_lock(&chip->mutex);

	समयo = jअगरfies + (HZ/2);
	z = 0;
	क्रम (;;) अणु
		अगर (chip->state != FL_WRITING) अणु
			/* Someone's suspended the ग_लिखो. Sleep */
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			समयo = jअगरfies + (HZ / 2); /* FIXME */
			mutex_lock(&chip->mutex);
			जारी;
		पूर्ण

		status = map_पढ़ो(map, cmd_adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		/* OK Still रुकोing */
		अगर (समय_after(jअगरfies, समयo)) अणु
                        /* clear status */
                        map_ग_लिखो(map, CMD(0x50), cmd_adr);
                        /* put back पूर्णांकo पढ़ो status रेजिस्टर mode */
                        map_ग_लिखो(map, CMD(0x70), adr);
			chip->state = FL_STATUS;
			DISABLE_VPP(map);
			mutex_unlock(&chip->mutex);
			prपूर्णांकk(KERN_ERR "waiting for chip to be ready timed out in bufwrite\n");
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		z++;
		mutex_lock(&chip->mutex);
	पूर्ण
	अगर (!z) अणु
		chip->buffer_ग_लिखो_समय--;
		अगर (!chip->buffer_ग_लिखो_समय)
			chip->buffer_ग_लिखो_समय++;
	पूर्ण
	अगर (z > 1)
		chip->buffer_ग_लिखो_समय++;

	/* Done and happy. */
	DISABLE_VPP(map);
	chip->state = FL_STATUS;

        /* check क्रम errors: 'lock bit', 'VPP', 'dead cell'/'unerased cell' or 'incorrect cmd' -- saw */
        अगर (map_word_bitsset(map, status, CMD(0x3a))) अणु
#अगर_घोषित DEBUG_CFI_FEATURES
		prपूर्णांकk("%s: 2 status[%lx]\n", __func__, status.x[0]);
#पूर्ण_अगर
		/* clear status */
		map_ग_लिखो(map, CMD(0x50), cmd_adr);
		/* put back पूर्णांकo पढ़ो status रेजिस्टर mode */
		map_ग_लिखो(map, CMD(0x70), adr);
		wake_up(&chip->wq);
		mutex_unlock(&chip->mutex);
		वापस map_word_bitsset(map, status, CMD(0x02)) ? -EROFS : -EIO;
	पूर्ण
	wake_up(&chip->wq);
	mutex_unlock(&chip->mutex);

        वापस 0;
पूर्ण

अटल पूर्णांक cfi_staa_ग_लिखो_buffers (काष्ठा mtd_info *mtd, loff_t to,
				       माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक wbufsize = cfi_पूर्णांकerleave(cfi) << cfi->cfiq->MaxBufWriteSize;
	पूर्णांक ret;
	पूर्णांक chipnum;
	अचिन्हित दीर्घ ofs;

	chipnum = to >> cfi->chipshअगरt;
	ofs = to  - (chipnum << cfi->chipshअगरt);

#अगर_घोषित DEBUG_CFI_FEATURES
	prपूर्णांकk("%s: map_bankwidth(map)[%x]\n", __func__, map_bankwidth(map));
	prपूर्णांकk("%s: chipnum[%x] wbufsize[%x]\n", __func__, chipnum, wbufsize);
	prपूर्णांकk("%s: ofs[%x] len[%x]\n", __func__, ofs, len);
#पूर्ण_अगर

        /* Write buffer is worth it only अगर more than one word to ग_लिखो... */
        जबतक (len > 0) अणु
		/* We must not cross ग_लिखो block boundaries */
		पूर्णांक size = wbufsize - (ofs & (wbufsize-1));

                अगर (size > len)
                    size = len;

                ret = करो_ग_लिखो_buffer(map, &cfi->chips[chipnum],
				      ofs, buf, size);
		अगर (ret)
			वापस ret;

		ofs += size;
		buf += size;
		(*retlen) += size;
		len -= size;

		अगर (ofs >> cfi->chipshअगरt) अणु
			chipnum ++;
			ofs = 0;
			अगर (chipnum == cfi->numchips)
				वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Writev क्रम ECC-Flashes is a little more complicated. We need to मुख्यtain
 * a small buffer क्रम this.
 * XXX: If the buffer size is not a multiple of 2, this will अवरोध
 */
#घोषणा ECCBUF_SIZE (mtd->ग_लिखोsize)
#घोषणा ECCBUF_DIV(x) ((x) & ~(ECCBUF_SIZE - 1))
#घोषणा ECCBUF_MOD(x) ((x) &  (ECCBUF_SIZE - 1))
अटल पूर्णांक
cfi_staa_ग_लिखोv(काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
		अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen)
अणु
	अचिन्हित दीर्घ i;
	माप_प्रकार	 totlen = 0, thislen;
	पूर्णांक	 ret = 0;
	माप_प्रकार	 buflen = 0;
	अक्षर *buffer;

	अगर (!ECCBUF_SIZE) अणु
		/* We should fall back to a general ग_लिखोv implementation.
		 * Until that is written, just अवरोध.
		 */
		वापस -EIO;
	पूर्ण
	buffer = kदो_स्मृति(ECCBUF_SIZE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	क्रम (i=0; i<count; i++) अणु
		माप_प्रकार elem_len = vecs[i].iov_len;
		व्योम *elem_base = vecs[i].iov_base;
		अगर (!elem_len) /* FIXME: Might be unnecessary. Check that */
			जारी;
		अगर (buflen) अणु /* cut off head */
			अगर (buflen + elem_len < ECCBUF_SIZE) अणु /* just accumulate */
				स_नकल(buffer+buflen, elem_base, elem_len);
				buflen += elem_len;
				जारी;
			पूर्ण
			स_नकल(buffer+buflen, elem_base, ECCBUF_SIZE-buflen);
			ret = mtd_ग_लिखो(mtd, to, ECCBUF_SIZE, &thislen,
					buffer);
			totlen += thislen;
			अगर (ret || thislen != ECCBUF_SIZE)
				जाओ ग_लिखो_error;
			elem_len -= thislen-buflen;
			elem_base += thislen-buflen;
			to += ECCBUF_SIZE;
		पूर्ण
		अगर (ECCBUF_DIV(elem_len)) अणु /* ग_लिखो clean aligned data */
			ret = mtd_ग_लिखो(mtd, to, ECCBUF_DIV(elem_len),
					&thislen, elem_base);
			totlen += thislen;
			अगर (ret || thislen != ECCBUF_DIV(elem_len))
				जाओ ग_लिखो_error;
			to += thislen;
		पूर्ण
		buflen = ECCBUF_MOD(elem_len); /* cut off tail */
		अगर (buflen) अणु
			स_रखो(buffer, 0xff, ECCBUF_SIZE);
			स_नकल(buffer, elem_base + thislen, buflen);
		पूर्ण
	पूर्ण
	अगर (buflen) अणु /* flush last page, even अगर not full */
		/* This is someबार पूर्णांकended behaviour, really */
		ret = mtd_ग_लिखो(mtd, to, buflen, &thislen, buffer);
		totlen += thislen;
		अगर (ret || thislen != ECCBUF_SIZE)
			जाओ ग_लिखो_error;
	पूर्ण
ग_लिखो_error:
	अगर (retlen)
		*retlen = totlen;
	kमुक्त(buffer);
	वापस ret;
पूर्ण


अटल अंतरभूत पूर्णांक करो_erase_oneblock(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status, status_OK;
	अचिन्हित दीर्घ समयo;
	पूर्णांक retries = 3;
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक ret = 0;

	adr += chip->start;

	/* Let's determine this according to the पूर्णांकerleave only once */
	status_OK = CMD(0x80);

	समयo = jअगरfies + HZ;
retry:
	mutex_lock(&chip->mutex);

	/* Check that the chip's पढ़ोy to talk to us. */
	चयन (chip->state) अणु
	हाल FL_CFI_QUERY:
	हाल FL_JEDEC_QUERY:
	हाल FL_READY:
		map_ग_लिखो(map, CMD(0x70), adr);
		chip->state = FL_STATUS;
		fallthrough;
	हाल FL_STATUS:
		status = map_पढ़ो(map, adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		/* Urgh. Chip not yet पढ़ोy to talk to us. */
		अगर (समय_after(jअगरfies, समयo)) अणु
			mutex_unlock(&chip->mutex);
			prपूर्णांकk(KERN_ERR "waiting for chip to be ready timed out in erase\n");
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		जाओ retry;

	शेष:
		/* Stick ourselves on a रुको queue to be woken when
		   someone changes the status */
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&chip->wq, &रुको);
		mutex_unlock(&chip->mutex);
		schedule();
		हटाओ_रुको_queue(&chip->wq, &रुको);
		समयo = jअगरfies + HZ;
		जाओ retry;
	पूर्ण

	ENABLE_VPP(map);
	/* Clear the status रेजिस्टर first */
	map_ग_लिखो(map, CMD(0x50), adr);

	/* Now erase */
	map_ग_लिखो(map, CMD(0x20), adr);
	map_ग_लिखो(map, CMD(0xD0), adr);
	chip->state = FL_ERASING;

	mutex_unlock(&chip->mutex);
	msleep(1000);
	mutex_lock(&chip->mutex);

	/* FIXME. Use a समयr to check this, and वापस immediately. */
	/* Once the state machine's known to be working I'll करो that */

	समयo = jअगरfies + (HZ*20);
	क्रम (;;) अणु
		अगर (chip->state != FL_ERASING) अणु
			/* Someone's suspended the erase. Sleep */
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			समयo = jअगरfies + (HZ*20); /* FIXME */
			mutex_lock(&chip->mutex);
			जारी;
		पूर्ण

		status = map_पढ़ो(map, adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		/* OK Still रुकोing */
		अगर (समय_after(jअगरfies, समयo)) अणु
			map_ग_लिखो(map, CMD(0x70), adr);
			chip->state = FL_STATUS;
			prपूर्णांकk(KERN_ERR "waiting for erase to complete timed out. Xstatus = %lx, status = %lx.\n", status.x[0], map_पढ़ो(map, adr).x[0]);
			DISABLE_VPP(map);
			mutex_unlock(&chip->mutex);
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		mutex_lock(&chip->mutex);
	पूर्ण

	DISABLE_VPP(map);
	ret = 0;

	/* We've broken this before. It doesn't hurt to be safe */
	map_ग_लिखो(map, CMD(0x70), adr);
	chip->state = FL_STATUS;
	status = map_पढ़ो(map, adr);

	/* check क्रम lock bit */
	अगर (map_word_bitsset(map, status, CMD(0x3a))) अणु
		अचिन्हित अक्षर chipstatus = status.x[0];
		अगर (!map_word_equal(map, status, CMD(chipstatus))) अणु
			पूर्णांक i, w;
			क्रम (w=0; w<map_words(map); w++) अणु
				क्रम (i = 0; i<cfi_पूर्णांकerleave(cfi); i++) अणु
					chipstatus |= status.x[w] >> (cfi->device_type * 8);
				पूर्ण
			पूर्ण
			prपूर्णांकk(KERN_WARNING "Status is not identical for all chips: 0x%lx. Merging to give 0x%02x\n",
			       status.x[0], chipstatus);
		पूर्ण
		/* Reset the error bits */
		map_ग_लिखो(map, CMD(0x50), adr);
		map_ग_लिखो(map, CMD(0x70), adr);

		अगर ((chipstatus & 0x30) == 0x30) अणु
			prपूर्णांकk(KERN_NOTICE "Chip reports improper command sequence: status 0x%x\n", chipstatus);
			ret = -EIO;
		पूर्ण अन्यथा अगर (chipstatus & 0x02) अणु
			/* Protection bit set */
			ret = -EROFS;
		पूर्ण अन्यथा अगर (chipstatus & 0x8) अणु
			/* Voltage */
			prपूर्णांकk(KERN_WARNING "Chip reports voltage low on erase: status 0x%x\n", chipstatus);
			ret = -EIO;
		पूर्ण अन्यथा अगर (chipstatus & 0x20) अणु
			अगर (retries--) अणु
				prपूर्णांकk(KERN_DEBUG "Chip erase failed at 0x%08lx: status 0x%x. Retrying...\n", adr, chipstatus);
				समयo = jअगरfies + HZ;
				chip->state = FL_STATUS;
				mutex_unlock(&chip->mutex);
				जाओ retry;
			पूर्ण
			prपूर्णांकk(KERN_DEBUG "Chip erase failed at 0x%08lx: status 0x%x\n", adr, chipstatus);
			ret = -EIO;
		पूर्ण
	पूर्ण

	wake_up(&chip->wq);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cfi_staa_erase_varsize(काष्ठा mtd_info *mtd,
				  काष्ठा erase_info *instr)
अणु	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ adr, len;
	पूर्णांक chipnum, ret;
	पूर्णांक i, first;
	काष्ठा mtd_erase_region_info *regions = mtd->eraseregions;

	/* Check that both start and end of the requested erase are
	 * aligned with the erasesize at the appropriate addresses.
	 */

	i = 0;

	/* Skip all erase regions which are ended beक्रमe the start of
	   the requested erase. Actually, to save on the calculations,
	   we skip to the first erase region which starts after the
	   start of the requested erase, and then go back one.
	*/

	जबतक (i < mtd->numeraseregions && instr->addr >= regions[i].offset)
	       i++;
	i--;

	/* OK, now i is poपूर्णांकing at the erase region in which this
	   erase request starts. Check the start of the requested
	   erase range is aligned with the erase size which is in
	   effect here.
	*/

	अगर (instr->addr & (regions[i].erasesize-1))
		वापस -EINVAL;

	/* Remember the erase region we start on */
	first = i;

	/* Next, check that the end of the requested erase is aligned
	 * with the erase region at that address.
	 */

	जबतक (i<mtd->numeraseregions && (instr->addr + instr->len) >= regions[i].offset)
		i++;

	/* As beक्रमe, drop back one to poपूर्णांक at the region in which
	   the address actually falls
	*/
	i--;

	अगर ((instr->addr + instr->len) & (regions[i].erasesize-1))
		वापस -EINVAL;

	chipnum = instr->addr >> cfi->chipshअगरt;
	adr = instr->addr - (chipnum << cfi->chipshअगरt);
	len = instr->len;

	i=first;

	जबतक(len) अणु
		ret = करो_erase_oneblock(map, &cfi->chips[chipnum], adr);

		अगर (ret)
			वापस ret;

		adr += regions[i].erasesize;
		len -= regions[i].erasesize;

		अगर (adr % (1<< cfi->chipshअगरt) == (((अचिन्हित दीर्घ)regions[i].offset + (regions[i].erasesize * regions[i].numblocks)) %( 1<< cfi->chipshअगरt)))
			i++;

		अगर (adr >> cfi->chipshअगरt) अणु
			adr = 0;
			chipnum++;

			अगर (chipnum >= cfi->numchips)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cfi_staa_sync (काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक i;
	काष्ठा flchip *chip;
	पूर्णांक ret = 0;
	DECLARE_WAITQUEUE(रुको, current);

	क्रम (i=0; !ret && i<cfi->numchips; i++) अणु
		chip = &cfi->chips[i];

	retry:
		mutex_lock(&chip->mutex);

		चयन(chip->state) अणु
		हाल FL_READY:
		हाल FL_STATUS:
		हाल FL_CFI_QUERY:
		हाल FL_JEDEC_QUERY:
			chip->oldstate = chip->state;
			chip->state = FL_SYNCING;
			/* No need to wake_up() on this state change -
			 * as the whole poपूर्णांक is that nobody can करो anything
			 * with the chip now anyway.
			 */
			fallthrough;
		हाल FL_SYNCING:
			mutex_unlock(&chip->mutex);
			अवरोध;

		शेष:
			/* Not an idle state */
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);

			mutex_unlock(&chip->mutex);
			schedule();
		        हटाओ_रुको_queue(&chip->wq, &रुको);

			जाओ retry;
		पूर्ण
	पूर्ण

	/* Unlock the chips again */

	क्रम (i--; i >=0; i--) अणु
		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		अगर (chip->state == FL_SYNCING) अणु
			chip->state = chip->oldstate;
			wake_up(&chip->wq);
		पूर्ण
		mutex_unlock(&chip->mutex);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक करो_lock_oneblock(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status, status_OK;
	अचिन्हित दीर्घ समयo = jअगरfies + HZ;
	DECLARE_WAITQUEUE(रुको, current);

	adr += chip->start;

	/* Let's determine this according to the पूर्णांकerleave only once */
	status_OK = CMD(0x80);

	समयo = jअगरfies + HZ;
retry:
	mutex_lock(&chip->mutex);

	/* Check that the chip's पढ़ोy to talk to us. */
	चयन (chip->state) अणु
	हाल FL_CFI_QUERY:
	हाल FL_JEDEC_QUERY:
	हाल FL_READY:
		map_ग_लिखो(map, CMD(0x70), adr);
		chip->state = FL_STATUS;
		fallthrough;
	हाल FL_STATUS:
		status = map_पढ़ो(map, adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		/* Urgh. Chip not yet पढ़ोy to talk to us. */
		अगर (समय_after(jअगरfies, समयo)) अणु
			mutex_unlock(&chip->mutex);
			prपूर्णांकk(KERN_ERR "waiting for chip to be ready timed out in lock\n");
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		जाओ retry;

	शेष:
		/* Stick ourselves on a रुको queue to be woken when
		   someone changes the status */
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&chip->wq, &रुको);
		mutex_unlock(&chip->mutex);
		schedule();
		हटाओ_रुको_queue(&chip->wq, &रुको);
		समयo = jअगरfies + HZ;
		जाओ retry;
	पूर्ण

	ENABLE_VPP(map);
	map_ग_लिखो(map, CMD(0x60), adr);
	map_ग_लिखो(map, CMD(0x01), adr);
	chip->state = FL_LOCKING;

	mutex_unlock(&chip->mutex);
	msleep(1000);
	mutex_lock(&chip->mutex);

	/* FIXME. Use a समयr to check this, and वापस immediately. */
	/* Once the state machine's known to be working I'll करो that */

	समयo = jअगरfies + (HZ*2);
	क्रम (;;) अणु

		status = map_पढ़ो(map, adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		/* OK Still रुकोing */
		अगर (समय_after(jअगरfies, समयo)) अणु
			map_ग_लिखो(map, CMD(0x70), adr);
			chip->state = FL_STATUS;
			prपूर्णांकk(KERN_ERR "waiting for lock to complete timed out. Xstatus = %lx, status = %lx.\n", status.x[0], map_पढ़ो(map, adr).x[0]);
			DISABLE_VPP(map);
			mutex_unlock(&chip->mutex);
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		mutex_lock(&chip->mutex);
	पूर्ण

	/* Done and happy. */
	chip->state = FL_STATUS;
	DISABLE_VPP(map);
	wake_up(&chip->wq);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण
अटल पूर्णांक cfi_staa_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ adr;
	पूर्णांक chipnum, ret;
#अगर_घोषित DEBUG_LOCK_BITS
	पूर्णांक ofs_factor = cfi->पूर्णांकerleave * cfi->device_type;
#पूर्ण_अगर

	अगर (ofs & (mtd->erasesize - 1))
		वापस -EINVAL;

	अगर (len & (mtd->erasesize -1))
		वापस -EINVAL;

	chipnum = ofs >> cfi->chipshअगरt;
	adr = ofs - (chipnum << cfi->chipshअगरt);

	जबतक(len) अणु

#अगर_घोषित DEBUG_LOCK_BITS
		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, शून्य);
		prपूर्णांकk("before lock: block status register is %x\n",cfi_पढ़ो_query(map, adr+(2*ofs_factor)));
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, शून्य);
#पूर्ण_अगर

		ret = करो_lock_oneblock(map, &cfi->chips[chipnum], adr);

#अगर_घोषित DEBUG_LOCK_BITS
		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, शून्य);
		prपूर्णांकk("after lock: block status register is %x\n",cfi_पढ़ो_query(map, adr+(2*ofs_factor)));
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, शून्य);
#पूर्ण_अगर

		अगर (ret)
			वापस ret;

		adr += mtd->erasesize;
		len -= mtd->erasesize;

		अगर (adr >> cfi->chipshअगरt) अणु
			adr = 0;
			chipnum++;

			अगर (chipnum >= cfi->numchips)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक करो_unlock_oneblock(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status, status_OK;
	अचिन्हित दीर्घ समयo = jअगरfies + HZ;
	DECLARE_WAITQUEUE(रुको, current);

	adr += chip->start;

	/* Let's determine this according to the पूर्णांकerleave only once */
	status_OK = CMD(0x80);

	समयo = jअगरfies + HZ;
retry:
	mutex_lock(&chip->mutex);

	/* Check that the chip's पढ़ोy to talk to us. */
	चयन (chip->state) अणु
	हाल FL_CFI_QUERY:
	हाल FL_JEDEC_QUERY:
	हाल FL_READY:
		map_ग_लिखो(map, CMD(0x70), adr);
		chip->state = FL_STATUS;
		fallthrough;
	हाल FL_STATUS:
		status = map_पढ़ो(map, adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		/* Urgh. Chip not yet पढ़ोy to talk to us. */
		अगर (समय_after(jअगरfies, समयo)) अणु
			mutex_unlock(&chip->mutex);
			prपूर्णांकk(KERN_ERR "waiting for chip to be ready timed out in unlock\n");
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		जाओ retry;

	शेष:
		/* Stick ourselves on a रुको queue to be woken when
		   someone changes the status */
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&chip->wq, &रुको);
		mutex_unlock(&chip->mutex);
		schedule();
		हटाओ_रुको_queue(&chip->wq, &रुको);
		समयo = jअगरfies + HZ;
		जाओ retry;
	पूर्ण

	ENABLE_VPP(map);
	map_ग_लिखो(map, CMD(0x60), adr);
	map_ग_लिखो(map, CMD(0xD0), adr);
	chip->state = FL_UNLOCKING;

	mutex_unlock(&chip->mutex);
	msleep(1000);
	mutex_lock(&chip->mutex);

	/* FIXME. Use a समयr to check this, and वापस immediately. */
	/* Once the state machine's known to be working I'll करो that */

	समयo = jअगरfies + (HZ*2);
	क्रम (;;) अणु

		status = map_पढ़ो(map, adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		/* OK Still रुकोing */
		अगर (समय_after(jअगरfies, समयo)) अणु
			map_ग_लिखो(map, CMD(0x70), adr);
			chip->state = FL_STATUS;
			prपूर्णांकk(KERN_ERR "waiting for unlock to complete timed out. Xstatus = %lx, status = %lx.\n", status.x[0], map_पढ़ो(map, adr).x[0]);
			DISABLE_VPP(map);
			mutex_unlock(&chip->mutex);
			वापस -EIO;
		पूर्ण

		/* Latency issues. Drop the unlock, रुको a जबतक and retry */
		mutex_unlock(&chip->mutex);
		cfi_udelay(1);
		mutex_lock(&chip->mutex);
	पूर्ण

	/* Done and happy. */
	chip->state = FL_STATUS;
	DISABLE_VPP(map);
	wake_up(&chip->wq);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण
अटल पूर्णांक cfi_staa_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ adr;
	पूर्णांक chipnum, ret;
#अगर_घोषित DEBUG_LOCK_BITS
	पूर्णांक ofs_factor = cfi->पूर्णांकerleave * cfi->device_type;
#पूर्ण_अगर

	chipnum = ofs >> cfi->chipshअगरt;
	adr = ofs - (chipnum << cfi->chipshअगरt);

#अगर_घोषित DEBUG_LOCK_BITS
	अणु
		अचिन्हित दीर्घ temp_adr = adr;
		अचिन्हित दीर्घ temp_len = len;

		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, शून्य);
                जबतक (temp_len) अणु
			prपूर्णांकk("before unlock %x: block status register is %x\n",temp_adr,cfi_पढ़ो_query(map, temp_adr+(2*ofs_factor)));
			temp_adr += mtd->erasesize;
			temp_len -= mtd->erasesize;
		पूर्ण
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, शून्य);
	पूर्ण
#पूर्ण_अगर

	ret = करो_unlock_oneblock(map, &cfi->chips[chipnum], adr);

#अगर_घोषित DEBUG_LOCK_BITS
	cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, शून्य);
	prपूर्णांकk("after unlock: block status register is %x\n",cfi_पढ़ो_query(map, adr+(2*ofs_factor)));
	cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, शून्य);
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक cfi_staa_suspend(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक i;
	काष्ठा flchip *chip;
	पूर्णांक ret = 0;

	क्रम (i=0; !ret && i<cfi->numchips; i++) अणु
		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		चयन(chip->state) अणु
		हाल FL_READY:
		हाल FL_STATUS:
		हाल FL_CFI_QUERY:
		हाल FL_JEDEC_QUERY:
			chip->oldstate = chip->state;
			chip->state = FL_PM_SUSPENDED;
			/* No need to wake_up() on this state change -
			 * as the whole poपूर्णांक is that nobody can करो anything
			 * with the chip now anyway.
			 */
			अवरोध;

		हाल FL_PM_SUSPENDED:
			अवरोध;

		शेष:
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		mutex_unlock(&chip->mutex);
	पूर्ण

	/* Unlock the chips again */

	अगर (ret) अणु
		क्रम (i--; i >=0; i--) अणु
			chip = &cfi->chips[i];

			mutex_lock(&chip->mutex);

			अगर (chip->state == FL_PM_SUSPENDED) अणु
				/* No need to क्रमce it पूर्णांकo a known state here,
				   because we're returning failure, and it didn't
				   get घातer cycled */
				chip->state = chip->oldstate;
				wake_up(&chip->wq);
			पूर्ण
			mutex_unlock(&chip->mutex);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cfi_staa_resume(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक i;
	काष्ठा flchip *chip;

	क्रम (i=0; i<cfi->numchips; i++) अणु

		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		/* Go to known state. Chip may have been घातer cycled */
		अगर (chip->state == FL_PM_SUSPENDED) अणु
			map_ग_लिखो(map, CMD(0xFF), 0);
			chip->state = FL_READY;
			wake_up(&chip->wq);
		पूर्ण

		mutex_unlock(&chip->mutex);
	पूर्ण
पूर्ण

अटल व्योम cfi_staa_destroy(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	kमुक्त(cfi->cmdset_priv);
	kमुक्त(cfi);
पूर्ण

MODULE_LICENSE("GPL");
