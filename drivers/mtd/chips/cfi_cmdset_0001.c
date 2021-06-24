<शैली गुरु>
/*
 * Common Flash Interface support:
 *   Intel Extended Venकरोr Command Set (ID 0x0001)
 *
 * (C) 2000 Red Hat. GPL'd
 *
 *
 * 10/10/2000	Nicolas Pitre <nico@fluxnic.net>
 * 	- completely revamped method functions so they are aware and
 * 	  independent of the flash geometry (buswidth, पूर्णांकerleave, etc.)
 * 	- scalability vs code size is completely set at compile-समय
 * 	  (see include/linux/mtd/cfi.h क्रम selection)
 *	- optimized ग_लिखो buffer method
 * 02/05/2002	Christopher Hoover <ch@hpl.hp.com>/<ch@murgatroid.com>
 *	- reworked lock/unlock/erase support क्रम var size flash
 * 21/03/2007   Roकरोlfo Giometti <giometti@linux.it>
 * 	- स्वतः unlock sectors on resume क्रम स्वतः locking flash on घातer up
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
#समावेश <linux/reboot.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/mtd/xip.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/cfi.h>

/* #घोषणा CMDSET0001_DISABLE_ERASE_SUSPEND_ON_WRITE */
/* #घोषणा CMDSET0001_DISABLE_WRITE_SUSPEND */

// debugging, turns off buffer ग_लिखो mode अगर set to 1
#घोषणा FORCE_WORD_WRITE 0

/* Intel chips */
#घोषणा I82802AB	0x00ad
#घोषणा I82802AC	0x00ac
#घोषणा PF38F4476	0x881c
#घोषणा M28F00AP30	0x8963
/* STMicroelectronics chips */
#घोषणा M50LPW080       0x002F
#घोषणा M50FLW080A	0x0080
#घोषणा M50FLW080B	0x0081
/* Aपंचांगel chips */
#घोषणा AT49BV640D	0x02de
#घोषणा AT49BV640DT	0x02db
/* Sharp chips */
#घोषणा LH28F640BFHE_PTTL90	0x00b0
#घोषणा LH28F640BFHE_PBTL90	0x00b1
#घोषणा LH28F640BFHE_PTTL70A	0x00b2
#घोषणा LH28F640BFHE_PBTL70A	0x00b3

अटल पूर्णांक cfi_पूर्णांकelext_पढ़ो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक cfi_पूर्णांकelext_ग_लिखो_words(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);
अटल पूर्णांक cfi_पूर्णांकelext_ग_लिखो_buffers(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);
अटल पूर्णांक cfi_पूर्णांकelext_ग_लिखोv(काष्ठा mtd_info *, स्थिर काष्ठा kvec *, अचिन्हित दीर्घ, loff_t, माप_प्रकार *);
अटल पूर्णांक cfi_पूर्णांकelext_erase_varsize(काष्ठा mtd_info *, काष्ठा erase_info *);
अटल व्योम cfi_पूर्णांकelext_sync (काष्ठा mtd_info *);
अटल पूर्णांक cfi_पूर्णांकelext_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक cfi_पूर्णांकelext_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक cfi_पूर्णांकelext_is_locked(काष्ठा mtd_info *mtd, loff_t ofs,
				  uपूर्णांक64_t len);
#अगर_घोषित CONFIG_MTD_OTP
अटल पूर्णांक cfi_पूर्णांकelext_पढ़ो_fact_prot_reg (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक cfi_पूर्णांकelext_पढ़ो_user_prot_reg (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक cfi_पूर्णांकelext_ग_लिखो_user_prot_reg(काष्ठा mtd_info *, loff_t, माप_प्रकार,
					    माप_प्रकार *, स्थिर u_अक्षर *);
अटल पूर्णांक cfi_पूर्णांकelext_lock_user_prot_reg (काष्ठा mtd_info *, loff_t, माप_प्रकार);
अटल पूर्णांक cfi_पूर्णांकelext_get_fact_prot_info(काष्ठा mtd_info *, माप_प्रकार,
					   माप_प्रकार *, काष्ठा otp_info *);
अटल पूर्णांक cfi_पूर्णांकelext_get_user_prot_info(काष्ठा mtd_info *, माप_प्रकार,
					   माप_प्रकार *, काष्ठा otp_info *);
#पूर्ण_अगर
अटल पूर्णांक cfi_पूर्णांकelext_suspend (काष्ठा mtd_info *);
अटल व्योम cfi_पूर्णांकelext_resume (काष्ठा mtd_info *);
अटल पूर्णांक cfi_पूर्णांकelext_reboot (काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);

अटल व्योम cfi_पूर्णांकelext_destroy(काष्ठा mtd_info *);

काष्ठा mtd_info *cfi_cmdset_0001(काष्ठा map_info *, पूर्णांक);

अटल काष्ठा mtd_info *cfi_पूर्णांकelext_setup (काष्ठा mtd_info *);
अटल पूर्णांक cfi_पूर्णांकelext_partition_fixup(काष्ठा mtd_info *, काष्ठा cfi_निजी **);

अटल पूर्णांक cfi_पूर्णांकelext_poपूर्णांक (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		     माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys);
अटल पूर्णांक cfi_पूर्णांकelext_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len);

अटल पूर्णांक chip_पढ़ोy (काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr, पूर्णांक mode);
अटल पूर्णांक get_chip(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr, पूर्णांक mode);
अटल व्योम put_chip(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr);
#समावेश "fwh_lock.h"



/*
 *  *********** SETUP AND PROBE BITS  ***********
 */

अटल काष्ठा mtd_chip_driver cfi_पूर्णांकelext_chipdrv = अणु
	.probe		= शून्य, /* Not usable directly */
	.destroy	= cfi_पूर्णांकelext_destroy,
	.name		= "cfi_cmdset_0001",
	.module		= THIS_MODULE
पूर्ण;

/* #घोषणा DEBUG_LOCK_BITS */
/* #घोषणा DEBUG_CFI_FEATURES */

#अगर_घोषित DEBUG_CFI_FEATURES
अटल व्योम cfi_tell_features(काष्ठा cfi_pri_पूर्णांकelext *extp)
अणु
	पूर्णांक i;
	prपूर्णांकk("  Extended Query version %c.%c\n", extp->MajorVersion, extp->MinorVersion);
	prपूर्णांकk("  Feature/Command Support:      %4.4X\n", extp->FeatureSupport);
	prपूर्णांकk("     - Chip Erase:              %s\n", extp->FeatureSupport&1?"supported":"unsupported");
	prपूर्णांकk("     - Suspend Erase:           %s\n", extp->FeatureSupport&2?"supported":"unsupported");
	prपूर्णांकk("     - Suspend Program:         %s\n", extp->FeatureSupport&4?"supported":"unsupported");
	prपूर्णांकk("     - Legacy Lock/Unlock:      %s\n", extp->FeatureSupport&8?"supported":"unsupported");
	prपूर्णांकk("     - Queued Erase:            %s\n", extp->FeatureSupport&16?"supported":"unsupported");
	prपूर्णांकk("     - Instant block lock:      %s\n", extp->FeatureSupport&32?"supported":"unsupported");
	prपूर्णांकk("     - Protection Bits:         %s\n", extp->FeatureSupport&64?"supported":"unsupported");
	prपूर्णांकk("     - Page-mode read:          %s\n", extp->FeatureSupport&128?"supported":"unsupported");
	prपूर्णांकk("     - Synchronous read:        %s\n", extp->FeatureSupport&256?"supported":"unsupported");
	prपूर्णांकk("     - Simultaneous operations: %s\n", extp->FeatureSupport&512?"supported":"unsupported");
	prपूर्णांकk("     - Extended Flash Array:    %s\n", extp->FeatureSupport&1024?"supported":"unsupported");
	क्रम (i=11; i<32; i++) अणु
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
	prपूर्णांकk("     - Lock-Down Bit Active: %s\n", extp->BlkStatusRegMask&2?"yes":"no");
	क्रम (i=2; i<3; i++) अणु
		अगर (extp->BlkStatusRegMask & (1<<i))
			prपूर्णांकk("     - Unknown Bit %X Active: yes\n",i);
	पूर्ण
	prपूर्णांकk("     - EFA Lock Bit:         %s\n", extp->BlkStatusRegMask&16?"yes":"no");
	prपूर्णांकk("     - EFA Lock-Down Bit:    %s\n", extp->BlkStatusRegMask&32?"yes":"no");
	क्रम (i=6; i<16; i++) अणु
		अगर (extp->BlkStatusRegMask & (1<<i))
			prपूर्णांकk("     - Unknown Bit %X Active: yes\n",i);
	पूर्ण

	prपूर्णांकk("  Vcc Logic Supply Optimum Program/Erase Voltage: %d.%d V\n",
	       extp->VccOptimal >> 4, extp->VccOptimal & 0xf);
	अगर (extp->VppOptimal)
		prपूर्णांकk("  Vpp Programming Supply Optimum Program/Erase Voltage: %d.%d V\n",
		       extp->VppOptimal >> 4, extp->VppOptimal & 0xf);
पूर्ण
#पूर्ण_अगर

/* Aपंचांगel chips करोn't use the same PRI क्रमmat as Intel chips */
अटल व्योम fixup_convert_aपंचांगel_pri(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *extp = cfi->cmdset_priv;
	काष्ठा cfi_pri_aपंचांगel aपंचांगel_pri;
	uपूर्णांक32_t features = 0;

	/* Reverse byteswapping */
	extp->FeatureSupport = cpu_to_le32(extp->FeatureSupport);
	extp->BlkStatusRegMask = cpu_to_le16(extp->BlkStatusRegMask);
	extp->ProtRegAddr = cpu_to_le16(extp->ProtRegAddr);

	स_नकल(&aपंचांगel_pri, extp, माप(aपंचांगel_pri));
	स_रखो((अक्षर *)extp + 5, 0, माप(*extp) - 5);

	prपूर्णांकk(KERN_ERR "atmel Features: %02x\n", aपंचांगel_pri.Features);

	अगर (aपंचांगel_pri.Features & 0x01) /* chip erase supported */
		features |= (1<<0);
	अगर (aपंचांगel_pri.Features & 0x02) /* erase suspend supported */
		features |= (1<<1);
	अगर (aपंचांगel_pri.Features & 0x04) /* program suspend supported */
		features |= (1<<2);
	अगर (aपंचांगel_pri.Features & 0x08) /* simultaneous operations supported */
		features |= (1<<9);
	अगर (aपंचांगel_pri.Features & 0x20) /* page mode पढ़ो supported */
		features |= (1<<7);
	अगर (aपंचांगel_pri.Features & 0x40) /* queued erase supported */
		features |= (1<<4);
	अगर (aपंचांगel_pri.Features & 0x80) /* Protection bits supported */
		features |= (1<<6);

	extp->FeatureSupport = features;

	/* burst ग_लिखो mode not supported */
	cfi->cfiq->BufWriteTimeoutTyp = 0;
	cfi->cfiq->BufWriteTimeoutMax = 0;
पूर्ण

अटल व्योम fixup_at49bv640dx_lock(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *cfip = cfi->cmdset_priv;

	cfip->FeatureSupport |= (1 << 5);
	mtd->flags |= MTD_POWERUP_LOCK;
पूर्ण

#अगर_घोषित CMDSET0001_DISABLE_ERASE_SUSPEND_ON_WRITE
/* Some Intel Strata Flash prior to FPO revision C has bugs in this area */
अटल व्योम fixup_पूर्णांकel_strataflash(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *extp = cfi->cmdset_priv;

	prपूर्णांकk(KERN_WARNING "cfi_cmdset_0001: Suspend "
	                    "erase on write disabled.\n");
	extp->SuspendCmdSupport &= ~1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CMDSET0001_DISABLE_WRITE_SUSPEND
अटल व्योम fixup_no_ग_लिखो_suspend(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *cfip = cfi->cmdset_priv;

	अगर (cfip && (cfip->FeatureSupport&4)) अणु
		cfip->FeatureSupport &= ~4;
		prपूर्णांकk(KERN_WARNING "cfi_cmdset_0001: write suspend disabled\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम fixup_st_m28w320ct(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	cfi->cfiq->BufWriteTimeoutTyp = 0;	/* Not supported */
	cfi->cfiq->BufWriteTimeoutMax = 0;	/* Not supported */
पूर्ण

अटल व्योम fixup_st_m28w320cb(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	/* Note this is करोne after the region info is endian swapped */
	cfi->cfiq->EraseRegionInfo[1] =
		(cfi->cfiq->EraseRegionInfo[1] & 0xffff0000) | 0x3e;
पूर्ण;

अटल पूर्णांक is_LH28F640BF(काष्ठा cfi_निजी *cfi)
अणु
	/* Sharp LH28F640BF Family */
	अगर (cfi->mfr == CFI_MFR_SHARP && (
	    cfi->id == LH28F640BFHE_PTTL90 || cfi->id == LH28F640BFHE_PBTL90 ||
	    cfi->id == LH28F640BFHE_PTTL70A || cfi->id == LH28F640BFHE_PBTL70A))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम fixup_LH28F640BF(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *extp = cfi->cmdset_priv;

	/* Reset the Partition Configuration Register on LH28F640BF
	 * to a single partition (PCR = 0x000): PCR is embedded पूर्णांकo A0-A15. */
	अगर (is_LH28F640BF(cfi)) अणु
		prपूर्णांकk(KERN_INFO "Reset Partition Config. Register: 1 Partition of 4 planes\n");
		map_ग_लिखो(map, CMD(0x60), 0);
		map_ग_लिखो(map, CMD(0x04), 0);

		/* We have set one single partition thus
		 * Simultaneous Operations are not allowed */
		prपूर्णांकk(KERN_INFO "cfi_cmdset_0001: Simultaneous Operations disabled\n");
		extp->FeatureSupport &= ~512;
	पूर्ण
पूर्ण

अटल व्योम fixup_use_poपूर्णांक(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	अगर (!mtd->_poपूर्णांक && map_is_linear(map)) अणु
		mtd->_poपूर्णांक   = cfi_पूर्णांकelext_poपूर्णांक;
		mtd->_unpoपूर्णांक = cfi_पूर्णांकelext_unpoपूर्णांक;
	पूर्ण
पूर्ण

अटल व्योम fixup_use_ग_लिखो_buffers(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अगर (cfi->cfiq->BufWriteTimeoutTyp) अणु
		prपूर्णांकk(KERN_INFO "Using buffer write method\n" );
		mtd->_ग_लिखो = cfi_पूर्णांकelext_ग_लिखो_buffers;
		mtd->_ग_लिखोv = cfi_पूर्णांकelext_ग_लिखोv;
	पूर्ण
पूर्ण

/*
 * Some chips घातer-up with all sectors locked by शेष.
 */
अटल व्योम fixup_unlock_घातerup_lock(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *cfip = cfi->cmdset_priv;

	अगर (cfip->FeatureSupport&32) अणु
		prपूर्णांकk(KERN_INFO "Using auto-unlock on power-up/resume\n" );
		mtd->flags |= MTD_POWERUP_LOCK;
	पूर्ण
पूर्ण

अटल काष्ठा cfi_fixup cfi_fixup_table[] = अणु
	अणु CFI_MFR_ATMEL, CFI_ID_ANY, fixup_convert_aपंचांगel_pri पूर्ण,
	अणु CFI_MFR_ATMEL, AT49BV640D, fixup_at49bv640dx_lock पूर्ण,
	अणु CFI_MFR_ATMEL, AT49BV640DT, fixup_at49bv640dx_lock पूर्ण,
#अगर_घोषित CMDSET0001_DISABLE_ERASE_SUSPEND_ON_WRITE
	अणु CFI_MFR_ANY, CFI_ID_ANY, fixup_पूर्णांकel_strataflash पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CMDSET0001_DISABLE_WRITE_SUSPEND
	अणु CFI_MFR_ANY, CFI_ID_ANY, fixup_no_ग_लिखो_suspend पूर्ण,
#पूर्ण_अगर
#अगर !FORCE_WORD_WRITE
	अणु CFI_MFR_ANY, CFI_ID_ANY, fixup_use_ग_लिखो_buffers पूर्ण,
#पूर्ण_अगर
	अणु CFI_MFR_ST, 0x00ba, /* M28W320CT */ fixup_st_m28w320ct पूर्ण,
	अणु CFI_MFR_ST, 0x00bb, /* M28W320CB */ fixup_st_m28w320cb पूर्ण,
	अणु CFI_MFR_INTEL, CFI_ID_ANY, fixup_unlock_घातerup_lock पूर्ण,
	अणु CFI_MFR_SHARP, CFI_ID_ANY, fixup_unlock_घातerup_lock पूर्ण,
	अणु CFI_MFR_SHARP, CFI_ID_ANY, fixup_LH28F640BF पूर्ण,
	अणु 0, 0, शून्य पूर्ण
पूर्ण;

अटल काष्ठा cfi_fixup jedec_fixup_table[] = अणु
	अणु CFI_MFR_INTEL, I82802AB,   fixup_use_fwh_lock पूर्ण,
	अणु CFI_MFR_INTEL, I82802AC,   fixup_use_fwh_lock पूर्ण,
	अणु CFI_MFR_ST,    M50LPW080,  fixup_use_fwh_lock पूर्ण,
	अणु CFI_MFR_ST,    M50FLW080A, fixup_use_fwh_lock पूर्ण,
	अणु CFI_MFR_ST,    M50FLW080B, fixup_use_fwh_lock पूर्ण,
	अणु 0, 0, शून्य पूर्ण
पूर्ण;
अटल काष्ठा cfi_fixup fixup_table[] = अणु
	/* The CFI venकरोr ids and the JEDEC venकरोr IDs appear
	 * to be common.  It is like the devices id's are as
	 * well.  This table is to pick all हालs where
	 * we know that is the हाल.
	 */
	अणु CFI_MFR_ANY, CFI_ID_ANY, fixup_use_poपूर्णांक पूर्ण,
	अणु 0, 0, शून्य पूर्ण
पूर्ण;

अटल व्योम cfi_fixup_major_minor(काष्ठा cfi_निजी *cfi,
						काष्ठा cfi_pri_पूर्णांकelext *extp)
अणु
	अगर (cfi->mfr == CFI_MFR_INTEL &&
			cfi->id == PF38F4476 && extp->MinorVersion == '3')
		extp->MinorVersion = '1';
पूर्ण

अटल पूर्णांक cfi_is_micron_28F00AP30(काष्ठा cfi_निजी *cfi, काष्ठा flchip *chip)
अणु
	/*
	 * Micron(was Numonyx) 1Gbit bottom boot are buggy w.r.t
	 * Erase Supend क्रम their small Erase Blocks(0x8000)
	 */
	अगर (cfi->mfr == CFI_MFR_INTEL && cfi->id == M28F00AP30)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा cfi_pri_पूर्णांकelext *
पढ़ो_pri_पूर्णांकelext(काष्ठा map_info *map, __u16 adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *extp;
	अचिन्हित पूर्णांक extra_size = 0;
	अचिन्हित पूर्णांक extp_size = माप(*extp);

 again:
	extp = (काष्ठा cfi_pri_पूर्णांकelext *)cfi_पढ़ो_pri(map, adr, extp_size, "Intel/Sharp");
	अगर (!extp)
		वापस शून्य;

	cfi_fixup_major_minor(cfi, extp);

	अगर (extp->MajorVersion != '1' ||
	    (extp->MinorVersion < '0' || extp->MinorVersion > '5')) अणु
		prपूर्णांकk(KERN_ERR "  Unknown Intel/Sharp Extended Query "
		       "version %c.%c.\n",  extp->MajorVersion,
		       extp->MinorVersion);
		kमुक्त(extp);
		वापस शून्य;
	पूर्ण

	/* Do some byteswapping अगर necessary */
	extp->FeatureSupport = le32_to_cpu(extp->FeatureSupport);
	extp->BlkStatusRegMask = le16_to_cpu(extp->BlkStatusRegMask);
	extp->ProtRegAddr = le16_to_cpu(extp->ProtRegAddr);

	अगर (extp->MinorVersion >= '0') अणु
		extra_size = 0;

		/* Protection Register info */
		अगर (extp->NumProtectionFields)
			extra_size += (extp->NumProtectionFields - 1) *
				      माप(काष्ठा cfi_पूर्णांकelext_otpinfo);
	पूर्ण

	अगर (extp->MinorVersion >= '1') अणु
		/* Burst Read info */
		extra_size += 2;
		अगर (extp_size < माप(*extp) + extra_size)
			जाओ need_more;
		extra_size += extp->extra[extra_size - 1];
	पूर्ण

	अगर (extp->MinorVersion >= '3') अणु
		पूर्णांक nb_parts, i;

		/* Number of hardware-partitions */
		extra_size += 1;
		अगर (extp_size < माप(*extp) + extra_size)
			जाओ need_more;
		nb_parts = extp->extra[extra_size - 1];

		/* skip the माप(partregion) field in CFI 1.4 */
		अगर (extp->MinorVersion >= '4')
			extra_size += 2;

		क्रम (i = 0; i < nb_parts; i++) अणु
			काष्ठा cfi_पूर्णांकelext_regioninfo *rinfo;
			rinfo = (काष्ठा cfi_पूर्णांकelext_regioninfo *)&extp->extra[extra_size];
			extra_size += माप(*rinfo);
			अगर (extp_size < माप(*extp) + extra_size)
				जाओ need_more;
			rinfo->NumIdentPartitions=le16_to_cpu(rinfo->NumIdentPartitions);
			extra_size += (rinfo->NumBlockTypes - 1)
				      * माप(काष्ठा cfi_पूर्णांकelext_blockinfo);
		पूर्ण

		अगर (extp->MinorVersion >= '4')
			extra_size += माप(काष्ठा cfi_पूर्णांकelext_programming_regioninfo);

		अगर (extp_size < माप(*extp) + extra_size) अणु
			need_more:
			extp_size = माप(*extp) + extra_size;
			kमुक्त(extp);
			अगर (extp_size > 4096) अणु
				prपूर्णांकk(KERN_ERR
					"%s: cfi_pri_intelext is too fat\n",
					__func__);
				वापस शून्य;
			पूर्ण
			जाओ again;
		पूर्ण
	पूर्ण

	वापस extp;
पूर्ण

काष्ठा mtd_info *cfi_cmdset_0001(काष्ठा map_info *map, पूर्णांक primary)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा mtd_info *mtd;
	पूर्णांक i;

	mtd = kzalloc(माप(*mtd), GFP_KERNEL);
	अगर (!mtd)
		वापस शून्य;
	mtd->priv = map;
	mtd->type = MTD_NORFLASH;

	/* Fill in the शेष mtd operations */
	mtd->_erase   = cfi_पूर्णांकelext_erase_varsize;
	mtd->_पढ़ो    = cfi_पूर्णांकelext_पढ़ो;
	mtd->_ग_लिखो   = cfi_पूर्णांकelext_ग_लिखो_words;
	mtd->_sync    = cfi_पूर्णांकelext_sync;
	mtd->_lock    = cfi_पूर्णांकelext_lock;
	mtd->_unlock  = cfi_पूर्णांकelext_unlock;
	mtd->_is_locked = cfi_पूर्णांकelext_is_locked;
	mtd->_suspend = cfi_पूर्णांकelext_suspend;
	mtd->_resume  = cfi_पूर्णांकelext_resume;
	mtd->flags   = MTD_CAP_NORFLASH;
	mtd->name    = map->name;
	mtd->ग_लिखोsize = 1;
	mtd->ग_लिखोbufsize = cfi_पूर्णांकerleave(cfi) << cfi->cfiq->MaxBufWriteSize;

	mtd->reboot_notअगरier.notअगरier_call = cfi_पूर्णांकelext_reboot;

	अगर (cfi->cfi_mode == CFI_MODE_CFI) अणु
		/*
		 * It's a real CFI chip, not one क्रम which the probe
		 * routine faked a CFI काष्ठाure. So we पढ़ो the feature
		 * table from it.
		 */
		__u16 adr = primary?cfi->cfiq->P_ADR:cfi->cfiq->A_ADR;
		काष्ठा cfi_pri_पूर्णांकelext *extp;

		extp = पढ़ो_pri_पूर्णांकelext(map, adr);
		अगर (!extp) अणु
			kमुक्त(mtd);
			वापस शून्य;
		पूर्ण

		/* Install our own निजी info काष्ठाure */
		cfi->cmdset_priv = extp;

		cfi_fixup(mtd, cfi_fixup_table);

#अगर_घोषित DEBUG_CFI_FEATURES
		/* Tell the user about it in lots of lovely detail */
		cfi_tell_features(extp);
#पूर्ण_अगर

		अगर(extp->SuspendCmdSupport & 1) अणु
			prपूर्णांकk(KERN_NOTICE "cfi_cmdset_0001: Erase suspend on write enabled\n");
		पूर्ण
	पूर्ण
	अन्यथा अगर (cfi->cfi_mode == CFI_MODE_JEDEC) अणु
		/* Apply jedec specअगरic fixups */
		cfi_fixup(mtd, jedec_fixup_table);
	पूर्ण
	/* Apply generic fixups */
	cfi_fixup(mtd, fixup_table);

	क्रम (i=0; i< cfi->numchips; i++) अणु
		अगर (cfi->cfiq->WordWriteTimeoutTyp)
			cfi->chips[i].word_ग_लिखो_समय =
				1<<cfi->cfiq->WordWriteTimeoutTyp;
		अन्यथा
			cfi->chips[i].word_ग_लिखो_समय = 50000;

		अगर (cfi->cfiq->BufWriteTimeoutTyp)
			cfi->chips[i].buffer_ग_लिखो_समय =
				1<<cfi->cfiq->BufWriteTimeoutTyp;
		/* No शेष; अगर it isn't specified, we won't use it */

		अगर (cfi->cfiq->BlockEraseTimeoutTyp)
			cfi->chips[i].erase_समय =
				1000<<cfi->cfiq->BlockEraseTimeoutTyp;
		अन्यथा
			cfi->chips[i].erase_समय = 2000000;

		अगर (cfi->cfiq->WordWriteTimeoutTyp &&
		    cfi->cfiq->WordWriteTimeoutMax)
			cfi->chips[i].word_ग_लिखो_समय_max =
				1<<(cfi->cfiq->WordWriteTimeoutTyp +
				    cfi->cfiq->WordWriteTimeoutMax);
		अन्यथा
			cfi->chips[i].word_ग_लिखो_समय_max = 50000 * 8;

		अगर (cfi->cfiq->BufWriteTimeoutTyp &&
		    cfi->cfiq->BufWriteTimeoutMax)
			cfi->chips[i].buffer_ग_लिखो_समय_max =
				1<<(cfi->cfiq->BufWriteTimeoutTyp +
				    cfi->cfiq->BufWriteTimeoutMax);

		अगर (cfi->cfiq->BlockEraseTimeoutTyp &&
		    cfi->cfiq->BlockEraseTimeoutMax)
			cfi->chips[i].erase_समय_max =
				1000<<(cfi->cfiq->BlockEraseTimeoutTyp +
				       cfi->cfiq->BlockEraseTimeoutMax);
		अन्यथा
			cfi->chips[i].erase_समय_max = 2000000 * 8;

		cfi->chips[i].ref_poपूर्णांक_counter = 0;
		init_रुकोqueue_head(&(cfi->chips[i].wq));
	पूर्ण

	map->fldrv = &cfi_पूर्णांकelext_chipdrv;

	वापस cfi_पूर्णांकelext_setup(mtd);
पूर्ण
काष्ठा mtd_info *cfi_cmdset_0003(काष्ठा map_info *map, पूर्णांक primary) __attribute__((alias("cfi_cmdset_0001")));
काष्ठा mtd_info *cfi_cmdset_0200(काष्ठा map_info *map, पूर्णांक primary) __attribute__((alias("cfi_cmdset_0001")));
EXPORT_SYMBOL_GPL(cfi_cmdset_0001);
EXPORT_SYMBOL_GPL(cfi_cmdset_0003);
EXPORT_SYMBOL_GPL(cfi_cmdset_0200);

अटल काष्ठा mtd_info *cfi_पूर्णांकelext_setup(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ offset = 0;
	पूर्णांक i,j;
	अचिन्हित दीर्घ devsize = (1<<cfi->cfiq->DevSize) * cfi->पूर्णांकerleave;

	//prपूर्णांकk(KERN_DEBUG "number of CFI chips: %d\n", cfi->numchips);

	mtd->size = devsize * cfi->numchips;

	mtd->numeraseregions = cfi->cfiq->NumEraseRegions * cfi->numchips;
	mtd->eraseregions = kसुस्मृति(mtd->numeraseregions,
				    माप(काष्ठा mtd_erase_region_info),
				    GFP_KERNEL);
	अगर (!mtd->eraseregions)
		जाओ setup_err;

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
			mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].lockmap = kदो_स्मृति(ernum / 8 + 1, GFP_KERNEL);
			अगर (!mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].lockmap)
				जाओ setup_err;
		पूर्ण
		offset += (ersize * ernum);
	पूर्ण

	अगर (offset != devsize) अणु
		/* Argh */
		prपूर्णांकk(KERN_WARNING "Sum of regions (%lx) != total size of set of interleaved chips (%lx)\n", offset, devsize);
		जाओ setup_err;
	पूर्ण

	क्रम (i=0; i<mtd->numeraseregions;i++)अणु
		prपूर्णांकk(KERN_DEBUG "erase region %d: offset=0x%llx,size=0x%x,blocks=%d\n",
		       i,(अचिन्हित दीर्घ दीर्घ)mtd->eraseregions[i].offset,
		       mtd->eraseregions[i].erasesize,
		       mtd->eraseregions[i].numblocks);
	पूर्ण

#अगर_घोषित CONFIG_MTD_OTP
	mtd->_पढ़ो_fact_prot_reg = cfi_पूर्णांकelext_पढ़ो_fact_prot_reg;
	mtd->_पढ़ो_user_prot_reg = cfi_पूर्णांकelext_पढ़ो_user_prot_reg;
	mtd->_ग_लिखो_user_prot_reg = cfi_पूर्णांकelext_ग_लिखो_user_prot_reg;
	mtd->_lock_user_prot_reg = cfi_पूर्णांकelext_lock_user_prot_reg;
	mtd->_get_fact_prot_info = cfi_पूर्णांकelext_get_fact_prot_info;
	mtd->_get_user_prot_info = cfi_पूर्णांकelext_get_user_prot_info;
#पूर्ण_अगर

	/* This function has the potential to distort the reality
	   a bit and thereक्रमe should be called last. */
	अगर (cfi_पूर्णांकelext_partition_fixup(mtd, &cfi) != 0)
		जाओ setup_err;

	__module_get(THIS_MODULE);
	रेजिस्टर_reboot_notअगरier(&mtd->reboot_notअगरier);
	वापस mtd;

 setup_err:
	अगर (mtd->eraseregions)
		क्रम (i=0; i<cfi->cfiq->NumEraseRegions; i++)
			क्रम (j=0; j<cfi->numchips; j++)
				kमुक्त(mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].lockmap);
	kमुक्त(mtd->eraseregions);
	kमुक्त(mtd);
	kमुक्त(cfi->cmdset_priv);
	वापस शून्य;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_partition_fixup(काष्ठा mtd_info *mtd,
					काष्ठा cfi_निजी **pcfi)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = *pcfi;
	काष्ठा cfi_pri_पूर्णांकelext *extp = cfi->cmdset_priv;

	/*
	 * Probing of multi-partition flash chips.
	 *
	 * To support multiple partitions when available, we simply arrange
	 * क्रम each of them to have their own flchip काष्ठाure even अगर they
	 * are on the same physical chip.  This means completely recreating
	 * a new cfi_निजी काष्ठाure right here which is a blatent code
	 * layering violation, but this is still the least पूर्णांकrusive
	 * arrangement at this poपूर्णांक. This can be rearranged in the future
	 * अगर someone feels motivated enough.  --nico
	 */
	अगर (extp && extp->MajorVersion == '1' && extp->MinorVersion >= '3'
	    && extp->FeatureSupport & (1 << 9)) अणु
		पूर्णांक offs = 0;
		काष्ठा cfi_निजी *newcfi;
		काष्ठा flchip *chip;
		काष्ठा flchip_shared *shared;
		पूर्णांक numregions, numparts, partshअगरt, numvirtchips, i, j;

		/* Protection Register info */
		अगर (extp->NumProtectionFields)
			offs = (extp->NumProtectionFields - 1) *
			       माप(काष्ठा cfi_पूर्णांकelext_otpinfo);

		/* Burst Read info */
		offs += extp->extra[offs+1]+2;

		/* Number of partition regions */
		numregions = extp->extra[offs];
		offs += 1;

		/* skip the माप(partregion) field in CFI 1.4 */
		अगर (extp->MinorVersion >= '4')
			offs += 2;

		/* Number of hardware partitions */
		numparts = 0;
		क्रम (i = 0; i < numregions; i++) अणु
			काष्ठा cfi_पूर्णांकelext_regioninfo *rinfo;
			rinfo = (काष्ठा cfi_पूर्णांकelext_regioninfo *)&extp->extra[offs];
			numparts += rinfo->NumIdentPartitions;
			offs += माप(*rinfo)
				+ (rinfo->NumBlockTypes - 1) *
				  माप(काष्ठा cfi_पूर्णांकelext_blockinfo);
		पूर्ण

		अगर (!numparts)
			numparts = 1;

		/* Programming Region info */
		अगर (extp->MinorVersion >= '4') अणु
			काष्ठा cfi_पूर्णांकelext_programming_regioninfo *prinfo;
			prinfo = (काष्ठा cfi_पूर्णांकelext_programming_regioninfo *)&extp->extra[offs];
			mtd->ग_लिखोsize = cfi->पूर्णांकerleave << prinfo->ProgRegShअगरt;
			mtd->flags &= ~MTD_BIT_WRITEABLE;
			prपूर्णांकk(KERN_DEBUG "%s: program region size/ctrl_valid/ctrl_inval = %d/%d/%d\n",
			       map->name, mtd->ग_लिखोsize,
			       cfi->पूर्णांकerleave * prinfo->ControlValid,
			       cfi->पूर्णांकerleave * prinfo->ControlInvalid);
		पूर्ण

		/*
		 * All functions below currently rely on all chips having
		 * the same geometry so we'll just assume that all hardware
		 * partitions are of the same size too.
		 */
		partshअगरt = cfi->chipshअगरt - __ffs(numparts);

		अगर ((1 << partshअगरt) < mtd->erasesize) अणु
			prपूर्णांकk( KERN_ERR
				"%s: bad number of hw partitions (%d)\n",
				__func__, numparts);
			वापस -EINVAL;
		पूर्ण

		numvirtchips = cfi->numchips * numparts;
		newcfi = kदो_स्मृति(काष्ठा_size(newcfi, chips, numvirtchips),
				 GFP_KERNEL);
		अगर (!newcfi)
			वापस -ENOMEM;
		shared = kदो_स्मृति_array(cfi->numchips,
				       माप(काष्ठा flchip_shared),
				       GFP_KERNEL);
		अगर (!shared) अणु
			kमुक्त(newcfi);
			वापस -ENOMEM;
		पूर्ण
		स_नकल(newcfi, cfi, माप(काष्ठा cfi_निजी));
		newcfi->numchips = numvirtchips;
		newcfi->chipshअगरt = partshअगरt;

		chip = &newcfi->chips[0];
		क्रम (i = 0; i < cfi->numchips; i++) अणु
			shared[i].writing = shared[i].erasing = शून्य;
			mutex_init(&shared[i].lock);
			क्रम (j = 0; j < numparts; j++) अणु
				*chip = cfi->chips[i];
				chip->start += j << partshअगरt;
				chip->priv = &shared[i];
				/* those should be reset too since
				   they create memory references. */
				init_रुकोqueue_head(&chip->wq);
				mutex_init(&chip->mutex);
				chip++;
			पूर्ण
		पूर्ण

		prपूर्णांकk(KERN_DEBUG "%s: %d set(s) of %d interleaved chips "
				  "--> %d partitions of %d KiB\n",
				  map->name, cfi->numchips, cfi->पूर्णांकerleave,
				  newcfi->numchips, 1<<(newcfi->chipshअगरt-10));

		map->fldrv_priv = newcfi;
		*pcfi = newcfi;
		kमुक्त(cfi);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  *********** CHIP ACCESS FUNCTIONS ***********
 */
अटल पूर्णांक chip_पढ़ोy (काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr, पूर्णांक mode)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status, status_OK = CMD(0x80), status_PWS = CMD(0x01);
	काष्ठा cfi_pri_पूर्णांकelext *cfip = cfi->cmdset_priv;
	अचिन्हित दीर्घ समयo = jअगरfies + HZ;

	/* Prevent setting state FL_SYNCING क्रम chip in suspended state. */
	अगर (mode == FL_SYNCING && chip->oldstate != FL_READY)
		जाओ sleep;

	चयन (chip->state) अणु

	हाल FL_STATUS:
		क्रम (;;) अणु
			status = map_पढ़ो(map, adr);
			अगर (map_word_andequal(map, status, status_OK, status_OK))
				अवरोध;

			/* At this poपूर्णांक we're fine with ग_लिखो operations
			   in other partitions as they करोn't conflict. */
			अगर (chip->priv && map_word_andequal(map, status, status_PWS, status_PWS))
				अवरोध;

			mutex_unlock(&chip->mutex);
			cfi_udelay(1);
			mutex_lock(&chip->mutex);
			/* Someone अन्यथा might have been playing with it. */
			वापस -EAGAIN;
		पूर्ण
		fallthrough;
	हाल FL_READY:
	हाल FL_CFI_QUERY:
	हाल FL_JEDEC_QUERY:
		वापस 0;

	हाल FL_ERASING:
		अगर (!cfip ||
		    !(cfip->FeatureSupport & 2) ||
		    !(mode == FL_READY || mode == FL_POINT ||
		     (mode == FL_WRITING && (cfip->SuspendCmdSupport & 1))))
			जाओ sleep;

		/* Do not allow suspend अगरf पढ़ो/ग_लिखो to EB address */
		अगर ((adr & chip->in_progress_block_mask) ==
		    chip->in_progress_block_addr)
			जाओ sleep;

		/* करो not suspend small EBs, buggy Micron Chips */
		अगर (cfi_is_micron_28F00AP30(cfi, chip) &&
		    (chip->in_progress_block_mask == ~(0x8000-1)))
			जाओ sleep;

		/* Erase suspend */
		map_ग_लिखो(map, CMD(0xB0), chip->in_progress_block_addr);

		/* If the flash has finished erasing, then 'erase suspend'
		 * appears to make some (28F320) flash devices चयन to
		 * 'read' mode.  Make sure that we switch to 'read status'
		 * mode so we get the right data. --rmk
		 */
		map_ग_लिखो(map, CMD(0x70), chip->in_progress_block_addr);
		chip->oldstate = FL_ERASING;
		chip->state = FL_ERASE_SUSPENDING;
		chip->erase_suspended = 1;
		क्रम (;;) अणु
			status = map_पढ़ो(map, chip->in_progress_block_addr);
			अगर (map_word_andequal(map, status, status_OK, status_OK))
			        अवरोध;

			अगर (समय_after(jअगरfies, समयo)) अणु
				/* Urgh. Resume and pretend we weren't here.
				 * Make sure we're in 'read status' mode अगर it had finished */
				put_chip(map, chip, adr);
				prपूर्णांकk(KERN_ERR "%s: Chip not ready after erase "
				       "suspended: status = 0x%lx\n", map->name, status.x[0]);
				वापस -EIO;
			पूर्ण

			mutex_unlock(&chip->mutex);
			cfi_udelay(1);
			mutex_lock(&chip->mutex);
			/* Nobody will touch it जबतक it's in state FL_ERASE_SUSPENDING.
			   So we can just loop here. */
		पूर्ण
		chip->state = FL_STATUS;
		वापस 0;

	हाल FL_XIP_WHILE_ERASING:
		अगर (mode != FL_READY && mode != FL_POINT &&
		    (mode != FL_WRITING || !cfip || !(cfip->SuspendCmdSupport&1)))
			जाओ sleep;
		chip->oldstate = chip->state;
		chip->state = FL_READY;
		वापस 0;

	हाल FL_SHUTDOWN:
		/* The machine is rebooting now,so no one can get chip anymore */
		वापस -EIO;
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

अटल पूर्णांक get_chip(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr, पूर्णांक mode)
अणु
	पूर्णांक ret;
	DECLARE_WAITQUEUE(रुको, current);

 retry:
	अगर (chip->priv &&
	    (mode == FL_WRITING || mode == FL_ERASING || mode == FL_OTP_WRITE
	    || mode == FL_SHUTDOWN) && chip->state != FL_SYNCING) अणु
		/*
		 * OK. We have possibility क्रम contention on the ग_लिखो/erase
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
		 * - contention arbitration is handled in the owner's context.
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
			ret = chip_पढ़ोy(map, contender, contender->start, mode);
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

			/* We should not own chip अगर it is alपढ़ोy
			 * in FL_SYNCING state. Put contender and retry. */
			अगर (chip->state == FL_SYNCING) अणु
				put_chip(map, contender, contender->start);
				mutex_unlock(&contender->mutex);
				जाओ retry;
			पूर्ण
			mutex_unlock(&contender->mutex);
		पूर्ण

		/* Check अगर we alपढ़ोy have suspended erase
		 * on this chip. Sleep. */
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
	ret = chip_पढ़ोy(map, chip, adr, mode);
	अगर (ret == -EAGAIN)
		जाओ retry;

	वापस ret;
पूर्ण

अटल व्योम put_chip(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	अगर (chip->priv) अणु
		काष्ठा flchip_shared *shared = chip->priv;
		mutex_lock(&shared->lock);
		अगर (shared->writing == chip && chip->oldstate == FL_READY) अणु
			/* We own the ability to ग_लिखो, but we're करोne */
			shared->writing = shared->erasing;
			अगर (shared->writing && shared->writing != chip) अणु
				/* give back ownership to who we loaned it from */
				काष्ठा flchip *loaner = shared->writing;
				mutex_lock(&loaner->mutex);
				mutex_unlock(&shared->lock);
				mutex_unlock(&chip->mutex);
				put_chip(map, loaner, loaner->start);
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

	चयन(chip->oldstate) अणु
	हाल FL_ERASING:
		/* What अगर one पूर्णांकerleaved chip has finished and the
		   other hasn't? The old code would leave the finished
		   one in READY mode. That's bad, and caused -EROFS
		   errors to be वापसed from करो_erase_oneblock because
		   that's the only bit it checked क्रम at the समय.
		   As the state machine appears to explicitly allow
		   sending the 0x70 (Read Status) command to an erasing
		   chip and expecting it to be ignored, that's what we
		   करो. */
		map_ग_लिखो(map, CMD(0xd0), chip->in_progress_block_addr);
		map_ग_लिखो(map, CMD(0x70), chip->in_progress_block_addr);
		chip->oldstate = FL_READY;
		chip->state = FL_ERASING;
		अवरोध;

	हाल FL_XIP_WHILE_ERASING:
		chip->state = chip->oldstate;
		chip->oldstate = FL_READY;
		अवरोध;

	हाल FL_READY:
	हाल FL_STATUS:
	हाल FL_JEDEC_QUERY:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: put_chip() called with oldstate %d!!\n", map->name, chip->oldstate);
	पूर्ण
	wake_up(&chip->wq);
पूर्ण

#अगर_घोषित CONFIG_MTD_XIP

/*
 * No पूर्णांकerrupt what so ever can be serviced जबतक the flash isn't in array
 * mode.  This is ensured by the xip_disable() and xip_enable() functions
 * enclosing any code path where the flash is known not to be in array mode.
 * And within a XIP disabled code path, only functions marked with __xipram
 * may be called and nothing अन्यथा (it's a good thing to inspect generated
 * assembly to make sure अंतरभूत functions were actually अंतरभूतd and that gcc
 * didn't emit calls to its own support functions). Also configuring MTD CFI
 * support to a single buswidth and a single पूर्णांकerleave is also recommended.
 */

अटल व्योम xip_disable(काष्ठा map_info *map, काष्ठा flchip *chip,
			अचिन्हित दीर्घ adr)
अणु
	/* TODO: chips with no XIP use should ignore and वापस */
	(व्योम) map_पढ़ो(map, adr); /* ensure mmu mapping is up to date */
	local_irq_disable();
पूर्ण

अटल व्योम __xipram xip_enable(काष्ठा map_info *map, काष्ठा flchip *chip,
				अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अगर (chip->state != FL_POINT && chip->state != FL_READY) अणु
		map_ग_लिखो(map, CMD(0xff), adr);
		chip->state = FL_READY;
	पूर्ण
	(व्योम) map_पढ़ो(map, adr);
	xip_iprefetch();
	local_irq_enable();
पूर्ण

/*
 * When a delay is required क्रम the flash operation to complete, the
 * xip_रुको_क्रम_operation() function is polling क्रम both the given समयout
 * and pending (but still masked) hardware पूर्णांकerrupts.  Whenever there is an
 * पूर्णांकerrupt pending then the flash erase or ग_लिखो operation is suspended,
 * array mode restored and पूर्णांकerrupts unmasked.  Task scheduling might also
 * happen at that poपूर्णांक.  The CPU eventually वापसs from the पूर्णांकerrupt or
 * the call to schedule() and the suspended flash operation is resumed क्रम
 * the reमुख्यing of the delay period.
 *
 * Warning: this function _will_ fool पूर्णांकerrupt latency tracing tools.
 */

अटल पूर्णांक __xipram xip_रुको_क्रम_operation(
		काष्ठा map_info *map, काष्ठा flchip *chip,
		अचिन्हित दीर्घ adr, अचिन्हित पूर्णांक chip_op_समय_max)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *cfip = cfi->cmdset_priv;
	map_word status, OK = CMD(0x80);
	अचिन्हित दीर्घ usec, suspended, start, करोne;
	flstate_t oldstate, newstate;

       	start = xip_currसमय();
	usec = chip_op_समय_max;
	अगर (usec == 0)
		usec = 500000;
	करोne = 0;

	करो अणु
		cpu_relax();
		अगर (xip_irqpending() && cfip &&
		    ((chip->state == FL_ERASING && (cfip->FeatureSupport&2)) ||
		     (chip->state == FL_WRITING && (cfip->FeatureSupport&4))) &&
		    (cfi_पूर्णांकerleave_is_1(cfi) || chip->oldstate == FL_READY)) अणु
			/*
			 * Let's suspend the erase or ग_लिखो operation when
			 * supported.  Note that we currently करोn't try to
			 * suspend पूर्णांकerleaved chips अगर there is alपढ़ोy
			 * another operation suspended (imagine what happens
			 * when one chip was alपढ़ोy करोne with the current
			 * operation जबतक another chip suspended it, then
			 * we resume the whole thing at once).  Yes, it
			 * can happen!
			 */
			usec -= करोne;
			map_ग_लिखो(map, CMD(0xb0), adr);
			map_ग_लिखो(map, CMD(0x70), adr);
			suspended = xip_currसमय();
			करो अणु
				अगर (xip_elapsed_since(suspended) > 100000) अणु
					/*
					 * The chip करोesn't want to suspend
					 * after रुकोing क्रम 100 msecs.
					 * This is a critical error but there
					 * is not much we can करो here.
					 */
					वापस -EIO;
				पूर्ण
				status = map_पढ़ो(map, adr);
			पूर्ण जबतक (!map_word_andequal(map, status, OK, OK));

			/* Suspend succeeded */
			oldstate = chip->state;
			अगर (oldstate == FL_ERASING) अणु
				अगर (!map_word_bitsset(map, status, CMD(0x40)))
					अवरोध;
				newstate = FL_XIP_WHILE_ERASING;
				chip->erase_suspended = 1;
			पूर्ण अन्यथा अणु
				अगर (!map_word_bitsset(map, status, CMD(0x04)))
					अवरोध;
				newstate = FL_XIP_WHILE_WRITING;
				chip->ग_लिखो_suspended = 1;
			पूर्ण
			chip->state = newstate;
			map_ग_लिखो(map, CMD(0xff), adr);
			(व्योम) map_पढ़ो(map, adr);
			xip_iprefetch();
			local_irq_enable();
			mutex_unlock(&chip->mutex);
			xip_iprefetch();
			cond_resched();

			/*
			 * We're back.  However someone अन्यथा might have
			 * decided to go ग_लिखो to the chip अगर we are in
			 * a suspended erase state.  If so let's रुको
			 * until it's करोne.
			 */
			mutex_lock(&chip->mutex);
			जबतक (chip->state != newstate) अणु
				DECLARE_WAITQUEUE(रुको, current);
				set_current_state(TASK_UNINTERRUPTIBLE);
				add_रुको_queue(&chip->wq, &रुको);
				mutex_unlock(&chip->mutex);
				schedule();
				हटाओ_रुको_queue(&chip->wq, &रुको);
				mutex_lock(&chip->mutex);
			पूर्ण
			/* Disallow XIP again */
			local_irq_disable();

			/* Resume the ग_लिखो or erase operation */
			map_ग_लिखो(map, CMD(0xd0), adr);
			map_ग_लिखो(map, CMD(0x70), adr);
			chip->state = oldstate;
			start = xip_currसमय();
		पूर्ण अन्यथा अगर (usec >= 1000000/HZ) अणु
			/*
			 * Try to save on CPU घातer when रुकोing delay
			 * is at least a प्रणाली समयr tick period.
			 * No need to be extremely accurate here.
			 */
			xip_cpu_idle();
		पूर्ण
		status = map_पढ़ो(map, adr);
		करोne = xip_elapsed_since(start);
	पूर्ण जबतक (!map_word_andequal(map, status, OK, OK)
		 && करोne < usec);

	वापस (करोne >= usec) ? -ETIME : 0;
पूर्ण

/*
 * The INVALIDATE_CACHED_RANGE() macro is normally used in parallel जबतक
 * the flash is actively programming or erasing since we have to poll क्रम
 * the operation to complete anyway.  We can't करो that in a generic way with
 * a XIP setup so करो it beक्रमe the actual flash operation in this हाल
 * and stub it out from INVAL_CACHE_AND_WAIT.
 */
#घोषणा XIP_INVAL_CACHED_RANGE(map, from, size)  \
	INVALIDATE_CACHED_RANGE(map, from, size)

#घोषणा INVAL_CACHE_AND_WAIT(map, chip, cmd_adr, inval_adr, inval_len, usec, usec_max) \
	xip_रुको_क्रम_operation(map, chip, cmd_adr, usec_max)

#अन्यथा

#घोषणा xip_disable(map, chip, adr)
#घोषणा xip_enable(map, chip, adr)
#घोषणा XIP_INVAL_CACHED_RANGE(x...)
#घोषणा INVAL_CACHE_AND_WAIT inval_cache_and_रुको_क्रम_operation

अटल पूर्णांक inval_cache_and_रुको_क्रम_operation(
		काष्ठा map_info *map, काष्ठा flchip *chip,
		अचिन्हित दीर्घ cmd_adr, अचिन्हित दीर्घ inval_adr, पूर्णांक inval_len,
		अचिन्हित पूर्णांक chip_op_समय, अचिन्हित पूर्णांक chip_op_समय_max)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status, status_OK = CMD(0x80);
	पूर्णांक chip_state = chip->state;
	अचिन्हित पूर्णांक समयo, sleep_समय, reset_समयo;

	mutex_unlock(&chip->mutex);
	अगर (inval_len)
		INVALIDATE_CACHED_RANGE(map, inval_adr, inval_len);
	mutex_lock(&chip->mutex);

	समयo = chip_op_समय_max;
	अगर (!समयo)
		समयo = 500000;
	reset_समयo = समयo;
	sleep_समय = chip_op_समय / 2;

	क्रम (;;) अणु
		अगर (chip->state != chip_state) अणु
			/* Someone's suspended the operation: sleep */
			DECLARE_WAITQUEUE(रुको, current);
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			mutex_lock(&chip->mutex);
			जारी;
		पूर्ण

		status = map_पढ़ो(map, cmd_adr);
		अगर (map_word_andequal(map, status, status_OK, status_OK))
			अवरोध;

		अगर (chip->erase_suspended && chip_state == FL_ERASING)  अणु
			/* Erase suspend occurred जबतक sleep: reset समयout */
			समयo = reset_समयo;
			chip->erase_suspended = 0;
		पूर्ण
		अगर (chip->ग_लिखो_suspended && chip_state == FL_WRITING)  अणु
			/* Write suspend occurred जबतक sleep: reset समयout */
			समयo = reset_समयo;
			chip->ग_लिखो_suspended = 0;
		पूर्ण
		अगर (!समयo) अणु
			map_ग_लिखो(map, CMD(0x70), cmd_adr);
			chip->state = FL_STATUS;
			वापस -ETIME;
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
	पूर्ण

	/* Done and happy. */
 	chip->state = FL_STATUS;
	वापस 0;
पूर्ण

#पूर्ण_अगर

#घोषणा WAIT_TIMEOUT(map, chip, adr, udelay, udelay_max) \
	INVAL_CACHE_AND_WAIT(map, chip, adr, 0, 0, udelay, udelay_max);


अटल पूर्णांक करो_poपूर्णांक_onechip (काष्ठा map_info *map, काष्ठा flchip *chip, loff_t adr, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ cmd_addr;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret;

	adr += chip->start;

	/* Ensure cmd पढ़ो/ग_लिखोs are aligned. */
	cmd_addr = adr & ~(map_bankwidth(map)-1);

	mutex_lock(&chip->mutex);

	ret = get_chip(map, chip, cmd_addr, FL_POINT);

	अगर (!ret) अणु
		अगर (chip->state != FL_POINT && chip->state != FL_READY)
			map_ग_लिखो(map, CMD(0xff), cmd_addr);

		chip->state = FL_POINT;
		chip->ref_poपूर्णांक_counter++;
	पूर्ण
	mutex_unlock(&chip->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ ofs, last_end = 0;
	पूर्णांक chipnum;
	पूर्णांक ret;

	अगर (!map->virt)
		वापस -EINVAL;

	/* Now lock the chip(s) to POINT state */

	/* ofs: offset within the first chip that the first पढ़ो should start */
	chipnum = (from >> cfi->chipshअगरt);
	ofs = from - (chipnum << cfi->chipshअगरt);

	*virt = map->virt + cfi->chips[chipnum].start + ofs;
	अगर (phys)
		*phys = map->phys + cfi->chips[chipnum].start + ofs;

	जबतक (len) अणु
		अचिन्हित दीर्घ thislen;

		अगर (chipnum >= cfi->numchips)
			अवरोध;

		/* We cannot poपूर्णांक across chips that are भवly disjoपूर्णांक */
		अगर (!last_end)
			last_end = cfi->chips[chipnum].start;
		अन्यथा अगर (cfi->chips[chipnum].start != last_end)
			अवरोध;

		अगर ((len + ofs -1) >> cfi->chipshअगरt)
			thislen = (1<<cfi->chipshअगरt) - ofs;
		अन्यथा
			thislen = len;

		ret = करो_poपूर्णांक_onechip(map, &cfi->chips[chipnum], ofs, thislen);
		अगर (ret)
			अवरोध;

		*retlen += thislen;
		len -= thislen;

		ofs = 0;
		last_end += 1 << cfi->chipshअगरt;
		chipnum++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ ofs;
	पूर्णांक chipnum, err = 0;

	/* Now unlock the chip(s) POINT state */

	/* ofs: offset within the first chip that the first पढ़ो should start */
	chipnum = (from >> cfi->chipshअगरt);
	ofs = from - (chipnum <<  cfi->chipshअगरt);

	जबतक (len && !err) अणु
		अचिन्हित दीर्घ thislen;
		काष्ठा flchip *chip;

		chip = &cfi->chips[chipnum];
		अगर (chipnum >= cfi->numchips)
			अवरोध;

		अगर ((len + ofs -1) >> cfi->chipshअगरt)
			thislen = (1<<cfi->chipshअगरt) - ofs;
		अन्यथा
			thislen = len;

		mutex_lock(&chip->mutex);
		अगर (chip->state == FL_POINT) अणु
			chip->ref_poपूर्णांक_counter--;
			अगर(chip->ref_poपूर्णांक_counter == 0)
				chip->state = FL_READY;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "%s: Error: unpoint called on non pointed region\n", map->name);
			err = -EINVAL;
		पूर्ण

		put_chip(map, chip, chip->start);
		mutex_unlock(&chip->mutex);

		len -= thislen;
		ofs = 0;
		chipnum++;
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक करो_पढ़ो_onechip(काष्ठा map_info *map, काष्ठा flchip *chip, loff_t adr, माप_प्रकार len, u_अक्षर *buf)
अणु
	अचिन्हित दीर्घ cmd_addr;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret;

	adr += chip->start;

	/* Ensure cmd पढ़ो/ग_लिखोs are aligned. */
	cmd_addr = adr & ~(map_bankwidth(map)-1);

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, cmd_addr, FL_READY);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	अगर (chip->state != FL_POINT && chip->state != FL_READY) अणु
		map_ग_लिखो(map, CMD(0xff), cmd_addr);

		chip->state = FL_READY;
	पूर्ण

	map_copy_from(map, buf, adr, len);

	put_chip(map, chip, cmd_addr);

	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_पढ़ो (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
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

अटल पूर्णांक __xipram करो_ग_लिखो_oneword(काष्ठा map_info *map, काष्ठा flchip *chip,
				     अचिन्हित दीर्घ adr, map_word datum, पूर्णांक mode)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status, ग_लिखो_cmd;
	पूर्णांक ret;

	adr += chip->start;

	चयन (mode) अणु
	हाल FL_WRITING:
		ग_लिखो_cmd = (cfi->cfiq->P_ID != P_ID_INTEL_PERFORMANCE) ? CMD(0x40) : CMD(0x41);
		अवरोध;
	हाल FL_OTP_WRITE:
		ग_लिखो_cmd = CMD(0xc0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, mode);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	XIP_INVAL_CACHED_RANGE(map, adr, map_bankwidth(map));
	ENABLE_VPP(map);
	xip_disable(map, chip, adr);
	map_ग_लिखो(map, ग_लिखो_cmd, adr);
	map_ग_लिखो(map, datum, adr);
	chip->state = mode;

	ret = INVAL_CACHE_AND_WAIT(map, chip, adr,
				   adr, map_bankwidth(map),
				   chip->word_ग_लिखो_समय,
				   chip->word_ग_लिखो_समय_max);
	अगर (ret) अणु
		xip_enable(map, chip, adr);
		prपूर्णांकk(KERN_ERR "%s: word write error (status timeout)\n", map->name);
		जाओ out;
	पूर्ण

	/* check क्रम errors */
	status = map_पढ़ो(map, adr);
	अगर (map_word_bitsset(map, status, CMD(0x1a))) अणु
		अचिन्हित दीर्घ chipstatus = MERGESTATUS(status);

		/* reset status */
		map_ग_लिखो(map, CMD(0x50), adr);
		map_ग_लिखो(map, CMD(0x70), adr);
		xip_enable(map, chip, adr);

		अगर (chipstatus & 0x02) अणु
			ret = -EROFS;
		पूर्ण अन्यथा अगर (chipstatus & 0x08) अणु
			prपूर्णांकk(KERN_ERR "%s: word write error (bad VPP)\n", map->name);
			ret = -EIO;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "%s: word write error (status 0x%lx)\n", map->name, chipstatus);
			ret = -EINVAL;
		पूर्ण

		जाओ out;
	पूर्ण

	xip_enable(map, chip, adr);
 out:	DISABLE_VPP(map);
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण


अटल पूर्णांक cfi_पूर्णांकelext_ग_लिखो_words (काष्ठा mtd_info *mtd, loff_t to , माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret;
	पूर्णांक chipnum;
	अचिन्हित दीर्घ ofs;

	chipnum = to >> cfi->chipshअगरt;
	ofs = to  - (chipnum << cfi->chipshअगरt);

	/* If it's not bus-aligned, करो the first byte ग_लिखो */
	अगर (ofs & (map_bankwidth(map)-1)) अणु
		अचिन्हित दीर्घ bus_ofs = ofs & ~(map_bankwidth(map)-1);
		पूर्णांक gap = ofs - bus_ofs;
		पूर्णांक n;
		map_word datum;

		n = min_t(पूर्णांक, len, map_bankwidth(map)-gap);
		datum = map_word_ff(map);
		datum = map_word_load_partial(map, datum, buf, gap, n);

		ret = करो_ग_लिखो_oneword(map, &cfi->chips[chipnum],
					       bus_ofs, datum, FL_WRITING);
		अगर (ret)
			वापस ret;

		len -= n;
		ofs += n;
		buf += n;
		(*retlen) += n;

		अगर (ofs >> cfi->chipshअगरt) अणु
			chipnum ++;
			ofs = 0;
			अगर (chipnum == cfi->numchips)
				वापस 0;
		पूर्ण
	पूर्ण

	जबतक(len >= map_bankwidth(map)) अणु
		map_word datum = map_word_load(map, buf);

		ret = करो_ग_लिखो_oneword(map, &cfi->chips[chipnum],
				       ofs, datum, FL_WRITING);
		अगर (ret)
			वापस ret;

		ofs += map_bankwidth(map);
		buf += map_bankwidth(map);
		(*retlen) += map_bankwidth(map);
		len -= map_bankwidth(map);

		अगर (ofs >> cfi->chipshअगरt) अणु
			chipnum ++;
			ofs = 0;
			अगर (chipnum == cfi->numchips)
				वापस 0;
		पूर्ण
	पूर्ण

	अगर (len & (map_bankwidth(map)-1)) अणु
		map_word datum;

		datum = map_word_ff(map);
		datum = map_word_load_partial(map, datum, buf, 0, len);

		ret = करो_ग_लिखो_oneword(map, &cfi->chips[chipnum],
				       ofs, datum, FL_WRITING);
		अगर (ret)
			वापस ret;

		(*retlen) += len;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक __xipram करो_ग_लिखो_buffer(काष्ठा map_info *map, काष्ठा flchip *chip,
				    अचिन्हित दीर्घ adr, स्थिर काष्ठा kvec **pvec,
				    अचिन्हित दीर्घ *pvec_seek, पूर्णांक len)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status, ग_लिखो_cmd, datum;
	अचिन्हित दीर्घ cmd_adr;
	पूर्णांक ret, wbufsize, word_gap, words;
	स्थिर काष्ठा kvec *vec;
	अचिन्हित दीर्घ vec_seek;
	अचिन्हित दीर्घ initial_adr;
	पूर्णांक initial_len = len;

	wbufsize = cfi_पूर्णांकerleave(cfi) << cfi->cfiq->MaxBufWriteSize;
	adr += chip->start;
	initial_adr = adr;
	cmd_adr = adr & ~(wbufsize-1);

	/* Sharp LH28F640BF chips need the first address क्रम the
	 * Page Buffer Program command. See Table 5 of
	 * LH28F320BF, LH28F640BF, LH28F128BF Series (Appendix FUM00701) */
	अगर (is_LH28F640BF(cfi))
		cmd_adr = adr;

	/* Let's determine this according to the पूर्णांकerleave only once */
	ग_लिखो_cmd = (cfi->cfiq->P_ID != P_ID_INTEL_PERFORMANCE) ? CMD(0xe8) : CMD(0xe9);

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, cmd_adr, FL_WRITING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	XIP_INVAL_CACHED_RANGE(map, initial_adr, initial_len);
	ENABLE_VPP(map);
	xip_disable(map, chip, cmd_adr);

	/* तई4.8 of the 28FxxxJ3A datasheet says "Any समय SR.4 and/or SR.5 is set
	   [...], the device will not accept any more Write to Buffer commands".
	   So we must check here and reset those bits अगर they're set. Otherwise
	   we're just pissing in the wind */
	अगर (chip->state != FL_STATUS) अणु
		map_ग_लिखो(map, CMD(0x70), cmd_adr);
		chip->state = FL_STATUS;
	पूर्ण
	status = map_पढ़ो(map, cmd_adr);
	अगर (map_word_bitsset(map, status, CMD(0x30))) अणु
		xip_enable(map, chip, cmd_adr);
		prपूर्णांकk(KERN_WARNING "SR.4 or SR.5 bits set in buffer write (status %lx). Clearing.\n", status.x[0]);
		xip_disable(map, chip, cmd_adr);
		map_ग_लिखो(map, CMD(0x50), cmd_adr);
		map_ग_लिखो(map, CMD(0x70), cmd_adr);
	पूर्ण

	chip->state = FL_WRITING_TO_BUFFER;
	map_ग_लिखो(map, ग_लिखो_cmd, cmd_adr);
	ret = WAIT_TIMEOUT(map, chip, cmd_adr, 0, 0);
	अगर (ret) अणु
		/* Argh. Not पढ़ोy क्रम ग_लिखो to buffer */
		map_word Xstatus = map_पढ़ो(map, cmd_adr);
		map_ग_लिखो(map, CMD(0x70), cmd_adr);
		chip->state = FL_STATUS;
		status = map_पढ़ो(map, cmd_adr);
		map_ग_लिखो(map, CMD(0x50), cmd_adr);
		map_ग_लिखो(map, CMD(0x70), cmd_adr);
		xip_enable(map, chip, cmd_adr);
		prपूर्णांकk(KERN_ERR "%s: Chip not ready for buffer write. Xstatus = %lx, status = %lx\n",
				map->name, Xstatus.x[0], status.x[0]);
		जाओ out;
	पूर्ण

	/* Figure out the number of words to ग_लिखो */
	word_gap = (-adr & (map_bankwidth(map)-1));
	words = DIV_ROUND_UP(len - word_gap, map_bankwidth(map));
	अगर (!word_gap) अणु
		words--;
	पूर्ण अन्यथा अणु
		word_gap = map_bankwidth(map) - word_gap;
		adr -= word_gap;
		datum = map_word_ff(map);
	पूर्ण

	/* Write length of data to come */
	map_ग_लिखो(map, CMD(words), cmd_adr );

	/* Write data */
	vec = *pvec;
	vec_seek = *pvec_seek;
	करो अणु
		पूर्णांक n = map_bankwidth(map) - word_gap;
		अगर (n > vec->iov_len - vec_seek)
			n = vec->iov_len - vec_seek;
		अगर (n > len)
			n = len;

		अगर (!word_gap && len < map_bankwidth(map))
			datum = map_word_ff(map);

		datum = map_word_load_partial(map, datum,
					      vec->iov_base + vec_seek,
					      word_gap, n);

		len -= n;
		word_gap += n;
		अगर (!len || word_gap == map_bankwidth(map)) अणु
			map_ग_लिखो(map, datum, adr);
			adr += map_bankwidth(map);
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
	map_ग_लिखो(map, CMD(0xd0), cmd_adr);
	chip->state = FL_WRITING;

	ret = INVAL_CACHE_AND_WAIT(map, chip, cmd_adr,
				   initial_adr, initial_len,
				   chip->buffer_ग_लिखो_समय,
				   chip->buffer_ग_लिखो_समय_max);
	अगर (ret) अणु
		map_ग_लिखो(map, CMD(0x70), cmd_adr);
		chip->state = FL_STATUS;
		xip_enable(map, chip, cmd_adr);
		prपूर्णांकk(KERN_ERR "%s: buffer write error (status timeout)\n", map->name);
		जाओ out;
	पूर्ण

	/* check क्रम errors */
	status = map_पढ़ो(map, cmd_adr);
	अगर (map_word_bitsset(map, status, CMD(0x1a))) अणु
		अचिन्हित दीर्घ chipstatus = MERGESTATUS(status);

		/* reset status */
		map_ग_लिखो(map, CMD(0x50), cmd_adr);
		map_ग_लिखो(map, CMD(0x70), cmd_adr);
		xip_enable(map, chip, cmd_adr);

		अगर (chipstatus & 0x02) अणु
			ret = -EROFS;
		पूर्ण अन्यथा अगर (chipstatus & 0x08) अणु
			prपूर्णांकk(KERN_ERR "%s: buffer write error (bad VPP)\n", map->name);
			ret = -EIO;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "%s: buffer write error (status 0x%lx)\n", map->name, chipstatus);
			ret = -EINVAL;
		पूर्ण

		जाओ out;
	पूर्ण

	xip_enable(map, chip, cmd_adr);
 out:	DISABLE_VPP(map);
	put_chip(map, chip, cmd_adr);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_ग_लिखोv (काष्ठा mtd_info *mtd, स्थिर काष्ठा kvec *vecs,
				अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक wbufsize = cfi_पूर्णांकerleave(cfi) << cfi->cfiq->MaxBufWriteSize;
	पूर्णांक ret;
	पूर्णांक chipnum;
	अचिन्हित दीर्घ ofs, vec_seek, i;
	माप_प्रकार len = 0;

	क्रम (i = 0; i < count; i++)
		len += vecs[i].iov_len;

	अगर (!len)
		वापस 0;

	chipnum = to >> cfi->chipshअगरt;
	ofs = to - (chipnum << cfi->chipshअगरt);
	vec_seek = 0;

	करो अणु
		/* We must not cross ग_लिखो block boundaries */
		पूर्णांक size = wbufsize - (ofs & (wbufsize-1));

		अगर (size > len)
			size = len;
		ret = करो_ग_लिखो_buffer(map, &cfi->chips[chipnum],
				      ofs, &vecs, &vec_seek, size);
		अगर (ret)
			वापस ret;

		ofs += size;
		(*retlen) += size;
		len -= size;

		अगर (ofs >> cfi->chipshअगरt) अणु
			chipnum ++;
			ofs = 0;
			अगर (chipnum == cfi->numchips)
				वापस 0;
		पूर्ण

		/* Be nice and reschedule with the chip in a usable state क्रम other
		   processes. */
		cond_resched();

	पूर्ण जबतक (len);

	वापस 0;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_ग_लिखो_buffers (काष्ठा mtd_info *mtd, loff_t to,
				       माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा kvec vec;

	vec.iov_base = (व्योम *) buf;
	vec.iov_len = len;

	वापस cfi_पूर्णांकelext_ग_लिखोv(mtd, &vec, 1, to, retlen);
पूर्ण

अटल पूर्णांक __xipram करो_erase_oneblock(काष्ठा map_info *map, काष्ठा flchip *chip,
				      अचिन्हित दीर्घ adr, पूर्णांक len, व्योम *thunk)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status;
	पूर्णांक retries = 3;
	पूर्णांक ret;

	adr += chip->start;

 retry:
	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, FL_ERASING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	XIP_INVAL_CACHED_RANGE(map, adr, len);
	ENABLE_VPP(map);
	xip_disable(map, chip, adr);

	/* Clear the status रेजिस्टर first */
	map_ग_लिखो(map, CMD(0x50), adr);

	/* Now erase */
	map_ग_लिखो(map, CMD(0x20), adr);
	map_ग_लिखो(map, CMD(0xD0), adr);
	chip->state = FL_ERASING;
	chip->erase_suspended = 0;
	chip->in_progress_block_addr = adr;
	chip->in_progress_block_mask = ~(len - 1);

	ret = INVAL_CACHE_AND_WAIT(map, chip, adr,
				   adr, len,
				   chip->erase_समय,
				   chip->erase_समय_max);
	अगर (ret) अणु
		map_ग_लिखो(map, CMD(0x70), adr);
		chip->state = FL_STATUS;
		xip_enable(map, chip, adr);
		prपूर्णांकk(KERN_ERR "%s: block erase error: (status timeout)\n", map->name);
		जाओ out;
	पूर्ण

	/* We've broken this before. It doesn't hurt to be safe */
	map_ग_लिखो(map, CMD(0x70), adr);
	chip->state = FL_STATUS;
	status = map_पढ़ो(map, adr);

	/* check क्रम errors */
	अगर (map_word_bitsset(map, status, CMD(0x3a))) अणु
		अचिन्हित दीर्घ chipstatus = MERGESTATUS(status);

		/* Reset the error bits */
		map_ग_लिखो(map, CMD(0x50), adr);
		map_ग_लिखो(map, CMD(0x70), adr);
		xip_enable(map, chip, adr);

		अगर ((chipstatus & 0x30) == 0x30) अणु
			prपूर्णांकk(KERN_ERR "%s: block erase error: (bad command sequence, status 0x%lx)\n", map->name, chipstatus);
			ret = -EINVAL;
		पूर्ण अन्यथा अगर (chipstatus & 0x02) अणु
			/* Protection bit set */
			ret = -EROFS;
		पूर्ण अन्यथा अगर (chipstatus & 0x8) अणु
			/* Voltage */
			prपूर्णांकk(KERN_ERR "%s: block erase error: (bad VPP)\n", map->name);
			ret = -EIO;
		पूर्ण अन्यथा अगर (chipstatus & 0x20 && retries--) अणु
			prपूर्णांकk(KERN_DEBUG "block erase failed at 0x%08lx: status 0x%lx. Retrying...\n", adr, chipstatus);
			DISABLE_VPP(map);
			put_chip(map, chip, adr);
			mutex_unlock(&chip->mutex);
			जाओ retry;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "%s: block erase failed at 0x%08lx (status 0x%lx)\n", map->name, adr, chipstatus);
			ret = -EIO;
		पूर्ण

		जाओ out;
	पूर्ण

	xip_enable(map, chip, adr);
 out:	DISABLE_VPP(map);
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_erase_varsize(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	वापस cfi_varsize_frob(mtd, करो_erase_oneblock, instr->addr,
				instr->len, शून्य);
पूर्ण

अटल व्योम cfi_पूर्णांकelext_sync (काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक i;
	काष्ठा flchip *chip;
	पूर्णांक ret = 0;

	क्रम (i=0; !ret && i<cfi->numchips; i++) अणु
		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);
		ret = get_chip(map, chip, chip->start, FL_SYNCING);

		अगर (!ret) अणु
			chip->oldstate = chip->state;
			chip->state = FL_SYNCING;
			/* No need to wake_up() on this state change -
			 * as the whole poपूर्णांक is that nobody can करो anything
			 * with the chip now anyway.
			 */
		पूर्ण
		mutex_unlock(&chip->mutex);
	पूर्ण

	/* Unlock the chips again */

	क्रम (i--; i >=0; i--) अणु
		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		अगर (chip->state == FL_SYNCING) अणु
			chip->state = chip->oldstate;
			chip->oldstate = FL_READY;
			wake_up(&chip->wq);
		पूर्ण
		mutex_unlock(&chip->mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक __xipram करो_getlockstatus_oneblock(काष्ठा map_info *map,
						काष्ठा flchip *chip,
						अचिन्हित दीर्घ adr,
						पूर्णांक len, व्योम *thunk)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक status, ofs_factor = cfi->पूर्णांकerleave * cfi->device_type;

	adr += chip->start;
	xip_disable(map, chip, adr+(2*ofs_factor));
	map_ग_लिखो(map, CMD(0x90), adr+(2*ofs_factor));
	chip->state = FL_JEDEC_QUERY;
	status = cfi_पढ़ो_query(map, adr+(2*ofs_factor));
	xip_enable(map, chip, 0);
	वापस status;
पूर्ण

#अगर_घोषित DEBUG_LOCK_BITS
अटल पूर्णांक __xipram करो_prपूर्णांकlockstatus_oneblock(काष्ठा map_info *map,
						काष्ठा flchip *chip,
						अचिन्हित दीर्घ adr,
						पूर्णांक len, व्योम *thunk)
अणु
	prपूर्णांकk(KERN_DEBUG "block status register for 0x%08lx is %x\n",
	       adr, करो_getlockstatus_oneblock(map, chip, adr, len, thunk));
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा DO_XXLOCK_ONEBLOCK_LOCK		((व्योम *) 1)
#घोषणा DO_XXLOCK_ONEBLOCK_UNLOCK	((व्योम *) 2)

अटल पूर्णांक __xipram करो_xxlock_oneblock(काष्ठा map_info *map, काष्ठा flchip *chip,
				       अचिन्हित दीर्घ adr, पूर्णांक len, व्योम *thunk)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *extp = cfi->cmdset_priv;
	पूर्णांक mdelay;
	पूर्णांक ret;

	adr += chip->start;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, FL_LOCKING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	ENABLE_VPP(map);
	xip_disable(map, chip, adr);

	map_ग_लिखो(map, CMD(0x60), adr);
	अगर (thunk == DO_XXLOCK_ONEBLOCK_LOCK) अणु
		map_ग_लिखो(map, CMD(0x01), adr);
		chip->state = FL_LOCKING;
	पूर्ण अन्यथा अगर (thunk == DO_XXLOCK_ONEBLOCK_UNLOCK) अणु
		map_ग_लिखो(map, CMD(0xD0), adr);
		chip->state = FL_UNLOCKING;
	पूर्ण अन्यथा
		BUG();

	/*
	 * If Instant Inभागidual Block Locking supported then no need
	 * to delay.
	 */
	/*
	 * Unlocking may take up to 1.4 seconds on some Intel flashes. So
	 * lets use a max of 1.5 seconds (1500ms) as समयout.
	 *
	 * See "Clear Block Lock-Bits Time" on page 40 in
	 * "3 Volt Intel StrataFlash Memory" 28F128J3,28F640J3,28F320J3 manual
	 * from February 2003
	 */
	mdelay = (!extp || !(extp->FeatureSupport & (1 << 5))) ? 1500 : 0;

	ret = WAIT_TIMEOUT(map, chip, adr, mdelay, mdelay * 1000);
	अगर (ret) अणु
		map_ग_लिखो(map, CMD(0x70), adr);
		chip->state = FL_STATUS;
		xip_enable(map, chip, adr);
		prपूर्णांकk(KERN_ERR "%s: block unlock error: (status timeout)\n", map->name);
		जाओ out;
	पूर्ण

	xip_enable(map, chip, adr);
 out:	DISABLE_VPP(map);
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

#अगर_घोषित DEBUG_LOCK_BITS
	prपूर्णांकk(KERN_DEBUG "%s: lock status before, ofs=0x%08llx, len=0x%08X\n",
	       __func__, ofs, len);
	cfi_varsize_frob(mtd, करो_prपूर्णांकlockstatus_oneblock,
		ofs, len, शून्य);
#पूर्ण_अगर

	ret = cfi_varsize_frob(mtd, करो_xxlock_oneblock,
		ofs, len, DO_XXLOCK_ONEBLOCK_LOCK);

#अगर_घोषित DEBUG_LOCK_BITS
	prपूर्णांकk(KERN_DEBUG "%s: lock status after, ret=%d\n",
	       __func__, ret);
	cfi_varsize_frob(mtd, करो_prपूर्णांकlockstatus_oneblock,
		ofs, len, शून्य);
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

#अगर_घोषित DEBUG_LOCK_BITS
	prपूर्णांकk(KERN_DEBUG "%s: lock status before, ofs=0x%08llx, len=0x%08X\n",
	       __func__, ofs, len);
	cfi_varsize_frob(mtd, करो_prपूर्णांकlockstatus_oneblock,
		ofs, len, शून्य);
#पूर्ण_अगर

	ret = cfi_varsize_frob(mtd, करो_xxlock_oneblock,
					ofs, len, DO_XXLOCK_ONEBLOCK_UNLOCK);

#अगर_घोषित DEBUG_LOCK_BITS
	prपूर्णांकk(KERN_DEBUG "%s: lock status after, ret=%d\n",
	       __func__, ret);
	cfi_varsize_frob(mtd, करो_prपूर्णांकlockstatus_oneblock,
		ofs, len, शून्य);
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_is_locked(काष्ठा mtd_info *mtd, loff_t ofs,
				  uपूर्णांक64_t len)
अणु
	वापस cfi_varsize_frob(mtd, करो_getlockstatus_oneblock,
				ofs, len, शून्य) ? 1 : 0;
पूर्ण

#अगर_घोषित CONFIG_MTD_OTP

प्रकार पूर्णांक (*otp_op_t)(काष्ठा map_info *map, काष्ठा flchip *chip,
			u_दीर्घ data_offset, u_अक्षर *buf, u_पूर्णांक size,
			u_दीर्घ prot_offset, u_पूर्णांक groupno, u_पूर्णांक groupsize);

अटल पूर्णांक __xipram
करो_otp_पढ़ो(काष्ठा map_info *map, काष्ठा flchip *chip, u_दीर्घ offset,
	    u_अक्षर *buf, u_पूर्णांक size, u_दीर्घ prot, u_पूर्णांक grpno, u_पूर्णांक grpsz)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, chip->start, FL_JEDEC_QUERY);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	/* let's ensure we're not पढ़ोing back cached data from array mode */
	INVALIDATE_CACHED_RANGE(map, chip->start + offset, size);

	xip_disable(map, chip, chip->start);
	अगर (chip->state != FL_JEDEC_QUERY) अणु
		map_ग_लिखो(map, CMD(0x90), chip->start);
		chip->state = FL_JEDEC_QUERY;
	पूर्ण
	map_copy_from(map, buf, chip->start + offset, size);
	xip_enable(map, chip, chip->start);

	/* then ensure we करोn't keep OTP data in the cache */
	INVALIDATE_CACHED_RANGE(map, chip->start + offset, size);

	put_chip(map, chip, chip->start);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक
करो_otp_ग_लिखो(काष्ठा map_info *map, काष्ठा flchip *chip, u_दीर्घ offset,
	     u_अक्षर *buf, u_पूर्णांक size, u_दीर्घ prot, u_पूर्णांक grpno, u_पूर्णांक grpsz)
अणु
	पूर्णांक ret;

	जबतक (size) अणु
		अचिन्हित दीर्घ bus_ofs = offset & ~(map_bankwidth(map)-1);
		पूर्णांक gap = offset - bus_ofs;
		पूर्णांक n = min_t(पूर्णांक, size, map_bankwidth(map)-gap);
		map_word datum = map_word_ff(map);

		datum = map_word_load_partial(map, datum, buf, gap, n);
		ret = करो_ग_लिखो_oneword(map, chip, bus_ofs, datum, FL_OTP_WRITE);
		अगर (ret)
			वापस ret;

		offset += n;
		buf += n;
		size -= n;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
करो_otp_lock(काष्ठा map_info *map, काष्ठा flchip *chip, u_दीर्घ offset,
	    u_अक्षर *buf, u_पूर्णांक size, u_दीर्घ prot, u_पूर्णांक grpno, u_पूर्णांक grpsz)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word datum;

	/* make sure area matches group boundaries */
	अगर (size != grpsz)
		वापस -EXDEV;

	datum = map_word_ff(map);
	datum = map_word_clr(map, datum, CMD(1 << grpno));
	वापस करो_ग_लिखो_oneword(map, chip, prot, datum, FL_OTP_WRITE);
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_otp_walk(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
				 माप_प्रकार *retlen, u_अक्षर *buf,
				 otp_op_t action, पूर्णांक user_regs)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *extp = cfi->cmdset_priv;
	काष्ठा flchip *chip;
	काष्ठा cfi_पूर्णांकelext_otpinfo *otp;
	u_दीर्घ devsize, reg_prot_offset, data_offset;
	u_पूर्णांक chip_num, chip_step, field, reg_fact_size, reg_user_size;
	u_पूर्णांक groups, groupno, groupsize, reg_fact_groups, reg_user_groups;
	पूर्णांक ret;

	*retlen = 0;

	/* Check that we actually have some OTP रेजिस्टरs */
	अगर (!extp || !(extp->FeatureSupport & 64) || !extp->NumProtectionFields)
		वापस -ENODATA;

	/* we need real chips here not भव ones */
	devsize = (1 << cfi->cfiq->DevSize) * cfi->पूर्णांकerleave;
	chip_step = devsize >> cfi->chipshअगरt;
	chip_num = 0;

	/* Some chips have OTP located in the _top_ partition only.
	   For example: Intel 28F256L18T (T means top-parameter device) */
	अगर (cfi->mfr == CFI_MFR_INTEL) अणु
		चयन (cfi->id) अणु
		हाल 0x880b:
		हाल 0x880c:
		हाल 0x880d:
			chip_num = chip_step - 1;
		पूर्ण
	पूर्ण

	क्रम ( ; chip_num < cfi->numchips; chip_num += chip_step) अणु
		chip = &cfi->chips[chip_num];
		otp = (काष्ठा cfi_पूर्णांकelext_otpinfo *)&extp->extra[0];

		/* first OTP region */
		field = 0;
		reg_prot_offset = extp->ProtRegAddr;
		reg_fact_groups = 1;
		reg_fact_size = 1 << extp->FactProtRegSize;
		reg_user_groups = 1;
		reg_user_size = 1 << extp->UserProtRegSize;

		जबतक (len > 0) अणु
			/* flash geometry fixup */
			data_offset = reg_prot_offset + 1;
			data_offset *= cfi->पूर्णांकerleave * cfi->device_type;
			reg_prot_offset *= cfi->पूर्णांकerleave * cfi->device_type;
			reg_fact_size *= cfi->पूर्णांकerleave;
			reg_user_size *= cfi->पूर्णांकerleave;

			अगर (user_regs) अणु
				groups = reg_user_groups;
				groupsize = reg_user_size;
				/* skip over factory reg area */
				groupno = reg_fact_groups;
				data_offset += reg_fact_groups * reg_fact_size;
			पूर्ण अन्यथा अणु
				groups = reg_fact_groups;
				groupsize = reg_fact_size;
				groupno = 0;
			पूर्ण

			जबतक (len > 0 && groups > 0) अणु
				अगर (!action) अणु
					/*
					 * Special हाल: अगर action is शून्य
					 * we fill buf with otp_info records.
					 */
					काष्ठा otp_info *otpinfo;
					map_word lockword;
					len -= माप(काष्ठा otp_info);
					अगर (len <= 0)
						वापस -ENOSPC;
					ret = करो_otp_पढ़ो(map, chip,
							  reg_prot_offset,
							  (u_अक्षर *)&lockword,
							  map_bankwidth(map),
							  0, 0,  0);
					अगर (ret)
						वापस ret;
					otpinfo = (काष्ठा otp_info *)buf;
					otpinfo->start = from;
					otpinfo->length = groupsize;
					otpinfo->locked =
					   !map_word_bitsset(map, lockword,
							     CMD(1 << groupno));
					from += groupsize;
					buf += माप(*otpinfo);
					*retlen += माप(*otpinfo);
				पूर्ण अन्यथा अगर (from >= groupsize) अणु
					from -= groupsize;
					data_offset += groupsize;
				पूर्ण अन्यथा अणु
					पूर्णांक size = groupsize;
					data_offset += from;
					size -= from;
					from = 0;
					अगर (size > len)
						size = len;
					ret = action(map, chip, data_offset,
						     buf, size, reg_prot_offset,
						     groupno, groupsize);
					अगर (ret < 0)
						वापस ret;
					buf += size;
					len -= size;
					*retlen += size;
					data_offset += size;
				पूर्ण
				groupno++;
				groups--;
			पूर्ण

			/* next OTP region */
			अगर (++field == extp->NumProtectionFields)
				अवरोध;
			reg_prot_offset = otp->ProtRegAddr;
			reg_fact_groups = otp->FactGroups;
			reg_fact_size = 1 << otp->FactProtRegSize;
			reg_user_groups = otp->UserGroups;
			reg_user_size = 1 << otp->UserProtRegSize;
			otp++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_पढ़ो_fact_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
					   माप_प्रकार len, माप_प्रकार *retlen,
					    u_अक्षर *buf)
अणु
	वापस cfi_पूर्णांकelext_otp_walk(mtd, from, len, retlen,
				     buf, करो_otp_पढ़ो, 0);
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_पढ़ो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
					   माप_प्रकार len, माप_प्रकार *retlen,
					    u_अक्षर *buf)
अणु
	वापस cfi_पूर्णांकelext_otp_walk(mtd, from, len, retlen,
				     buf, करो_otp_पढ़ो, 1);
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_ग_लिखो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
					    माप_प्रकार len, माप_प्रकार *retlen,
					    स्थिर u_अक्षर *buf)
अणु
	वापस cfi_पूर्णांकelext_otp_walk(mtd, from, len, retlen,
				     (u_अक्षर *)buf, करो_otp_ग_लिखो, 1);
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_lock_user_prot_reg(काष्ठा mtd_info *mtd,
					   loff_t from, माप_प्रकार len)
अणु
	माप_प्रकार retlen;
	वापस cfi_पूर्णांकelext_otp_walk(mtd, from, len, &retlen,
				     शून्य, करो_otp_lock, 1);
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_get_fact_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len,
					   माप_प्रकार *retlen, काष्ठा otp_info *buf)

अणु
	वापस cfi_पूर्णांकelext_otp_walk(mtd, 0, len, retlen, (u_अक्षर *)buf,
				     शून्य, 0);
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_get_user_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len,
					   माप_प्रकार *retlen, काष्ठा otp_info *buf)
अणु
	वापस cfi_पूर्णांकelext_otp_walk(mtd, 0, len, retlen, (u_अक्षर *)buf,
				     शून्य, 1);
पूर्ण

#पूर्ण_अगर

अटल व्योम cfi_पूर्णांकelext_save_locks(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_erase_region_info *region;
	पूर्णांक block, status, i;
	अचिन्हित दीर्घ adr;
	माप_प्रकार len;

	क्रम (i = 0; i < mtd->numeraseregions; i++) अणु
		region = &mtd->eraseregions[i];
		अगर (!region->lockmap)
			जारी;

		क्रम (block = 0; block < region->numblocks; block++)अणु
			len = region->erasesize;
			adr = region->offset + block * len;

			status = cfi_varsize_frob(mtd,
					करो_getlockstatus_oneblock, adr, len, शून्य);
			अगर (status)
				set_bit(block, region->lockmap);
			अन्यथा
				clear_bit(block, region->lockmap);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_suspend(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *extp = cfi->cmdset_priv;
	पूर्णांक i;
	काष्ठा flchip *chip;
	पूर्णांक ret = 0;

	अगर ((mtd->flags & MTD_POWERUP_LOCK)
	    && extp && (extp->FeatureSupport & (1 << 5)))
		cfi_पूर्णांकelext_save_locks(mtd);

	क्रम (i=0; !ret && i<cfi->numchips; i++) अणु
		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		चयन (chip->state) अणु
		हाल FL_READY:
		हाल FL_STATUS:
		हाल FL_CFI_QUERY:
		हाल FL_JEDEC_QUERY:
			अगर (chip->oldstate == FL_READY) अणु
				/* place the chip in a known state beक्रमe suspend */
				map_ग_लिखो(map, CMD(0xFF), cfi->chips[i].start);
				chip->oldstate = chip->state;
				chip->state = FL_PM_SUSPENDED;
				/* No need to wake_up() on this state change -
				 * as the whole poपूर्णांक is that nobody can करो anything
				 * with the chip now anyway.
				 */
			पूर्ण अन्यथा अणु
				/* There seems to be an operation pending. We must रुको क्रम it. */
				prपूर्णांकk(KERN_NOTICE "Flash device refused suspend due to pending operation (oldstate %d)\n", chip->oldstate);
				ret = -EAGAIN;
			पूर्ण
			अवरोध;
		शेष:
			/* Should we actually रुको? Once upon a समय these routines weren't
			   allowed to. Or should we वापस -EAGAIN, because the upper layers
			   ought to have alपढ़ोy shut करोwn anything which was using the device
			   anyway? The latter क्रम now. */
			prपूर्णांकk(KERN_NOTICE "Flash device refused suspend due to active operation (state %d)\n", chip->state);
			ret = -EAGAIN;
			अवरोध;
		हाल FL_PM_SUSPENDED:
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
				chip->oldstate = FL_READY;
				wake_up(&chip->wq);
			पूर्ण
			mutex_unlock(&chip->mutex);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cfi_पूर्णांकelext_restore_locks(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_erase_region_info *region;
	पूर्णांक block, i;
	अचिन्हित दीर्घ adr;
	माप_प्रकार len;

	क्रम (i = 0; i < mtd->numeraseregions; i++) अणु
		region = &mtd->eraseregions[i];
		अगर (!region->lockmap)
			जारी;

		क्रम_each_clear_bit(block, region->lockmap, region->numblocks) अणु
			len = region->erasesize;
			adr = region->offset + block * len;
			cfi_पूर्णांकelext_unlock(mtd, adr, len);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cfi_पूर्णांकelext_resume(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_पूर्णांकelext *extp = cfi->cmdset_priv;
	पूर्णांक i;
	काष्ठा flchip *chip;

	क्रम (i=0; i<cfi->numchips; i++) अणु

		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		/* Go to known state. Chip may have been घातer cycled */
		अगर (chip->state == FL_PM_SUSPENDED) अणु
			/* Refresh LH28F640BF Partition Config. Register */
			fixup_LH28F640BF(mtd);
			map_ग_लिखो(map, CMD(0xFF), cfi->chips[i].start);
			chip->oldstate = chip->state = FL_READY;
			wake_up(&chip->wq);
		पूर्ण

		mutex_unlock(&chip->mutex);
	पूर्ण

	अगर ((mtd->flags & MTD_POWERUP_LOCK)
	    && extp && (extp->FeatureSupport & (1 << 5)))
		cfi_पूर्णांकelext_restore_locks(mtd);
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_reset(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक i, ret;

	क्रम (i=0; i < cfi->numchips; i++) अणु
		काष्ठा flchip *chip = &cfi->chips[i];

		/* क्रमce the completion of any ongoing operation
		   and चयन to array mode so any bootloader in
		   flash is accessible क्रम soft reboot. */
		mutex_lock(&chip->mutex);
		ret = get_chip(map, chip, chip->start, FL_SHUTDOWN);
		अगर (!ret) अणु
			map_ग_लिखो(map, CMD(0xff), chip->start);
			chip->state = FL_SHUTDOWN;
			put_chip(map, chip, chip->start);
		पूर्ण
		mutex_unlock(&chip->mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cfi_पूर्णांकelext_reboot(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			       व्योम *v)
अणु
	काष्ठा mtd_info *mtd;

	mtd = container_of(nb, काष्ठा mtd_info, reboot_notअगरier);
	cfi_पूर्णांकelext_reset(mtd);
	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम cfi_पूर्णांकelext_destroy(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा mtd_erase_region_info *region;
	पूर्णांक i;
	cfi_पूर्णांकelext_reset(mtd);
	unरेजिस्टर_reboot_notअगरier(&mtd->reboot_notअगरier);
	kमुक्त(cfi->cmdset_priv);
	kमुक्त(cfi->cfiq);
	kमुक्त(cfi->chips[0].priv);
	kमुक्त(cfi);
	क्रम (i = 0; i < mtd->numeraseregions; i++) अणु
		region = &mtd->eraseregions[i];
		kमुक्त(region->lockmap);
	पूर्ण
	kमुक्त(mtd->eraseregions);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org> et al.");
MODULE_DESCRIPTION("MTD chip driver for Intel/Sharp flash chips");
MODULE_ALIAS("cfi_cmdset_0003");
MODULE_ALIAS("cfi_cmdset_0200");
