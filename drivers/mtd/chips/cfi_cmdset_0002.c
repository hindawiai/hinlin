<शैली गुरु>
/*
 * Common Flash Interface support:
 *   AMD & Fujitsu Standard Venकरोr Command Set (ID 0x0002)
 *
 * Copyright (C) 2000 Crossnet Co. <info@crossnet.co.jp>
 * Copyright (C) 2004 Arcom Control Systems Ltd <linux@arcom.com>
 * Copyright (C) 2005 MontaVista Software Inc. <source@mvista.com>
 *
 * 2_by_8 routines added by Simon Munton
 *
 * 4_by_16 work by Carolyn J. Smith
 *
 * XIP support hooks by Vitaly Wool (based on code क्रम Intel flash
 * by Nicolas Pitre)
 *
 * 25/09/2008 Christopher Moore: TopBottom fixup क्रम many Macronix with CFI V1.0
 *
 * Occasionally मुख्यtained by Thayne Harbaugh tharbaugh at lnxi करोt com
 *
 * This code is GPL
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
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/xip.h>

#घोषणा AMD_BOOTLOC_BUG
#घोषणा FORCE_WORD_WRITE 0

#घोषणा MAX_RETRIES 3

#घोषणा SST49LF004B		0x0060
#घोषणा SST49LF040B		0x0050
#घोषणा SST49LF008A		0x005a
#घोषणा AT49BV6416		0x00d6

/*
 * Status Register bit description. Used by flash devices that करोn't
 * support DQ polling (e.g. HyperFlash)
 */
#घोषणा CFI_SR_DRB		BIT(7)
#घोषणा CFI_SR_ESB		BIT(5)
#घोषणा CFI_SR_PSB		BIT(4)
#घोषणा CFI_SR_WBASB		BIT(3)
#घोषणा CFI_SR_SLSB		BIT(1)

अटल पूर्णांक cfi_amdstd_पढ़ो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक cfi_amdstd_ग_लिखो_words(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);
#अगर !FORCE_WORD_WRITE
अटल पूर्णांक cfi_amdstd_ग_लिखो_buffers(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);
#पूर्ण_अगर
अटल पूर्णांक cfi_amdstd_erase_chip(काष्ठा mtd_info *, काष्ठा erase_info *);
अटल पूर्णांक cfi_amdstd_erase_varsize(काष्ठा mtd_info *, काष्ठा erase_info *);
अटल व्योम cfi_amdstd_sync (काष्ठा mtd_info *);
अटल पूर्णांक cfi_amdstd_suspend (काष्ठा mtd_info *);
अटल व्योम cfi_amdstd_resume (काष्ठा mtd_info *);
अटल पूर्णांक cfi_amdstd_reboot(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल पूर्णांक cfi_amdstd_get_fact_prot_info(काष्ठा mtd_info *, माप_प्रकार,
					 माप_प्रकार *, काष्ठा otp_info *);
अटल पूर्णांक cfi_amdstd_get_user_prot_info(काष्ठा mtd_info *, माप_प्रकार,
					 माप_प्रकार *, काष्ठा otp_info *);
अटल पूर्णांक cfi_amdstd_secsi_पढ़ो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक cfi_amdstd_पढ़ो_fact_prot_reg(काष्ठा mtd_info *, loff_t, माप_प्रकार,
					 माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक cfi_amdstd_पढ़ो_user_prot_reg(काष्ठा mtd_info *, loff_t, माप_प्रकार,
					 माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक cfi_amdstd_ग_लिखो_user_prot_reg(काष्ठा mtd_info *, loff_t, माप_प्रकार,
					  माप_प्रकार *, स्थिर u_अक्षर *);
अटल पूर्णांक cfi_amdstd_lock_user_prot_reg(काष्ठा mtd_info *, loff_t, माप_प्रकार);

अटल पूर्णांक cfi_amdstd_panic_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
				  माप_प्रकार *retlen, स्थिर u_अक्षर *buf);

अटल व्योम cfi_amdstd_destroy(काष्ठा mtd_info *);

काष्ठा mtd_info *cfi_cmdset_0002(काष्ठा map_info *, पूर्णांक);
अटल काष्ठा mtd_info *cfi_amdstd_setup (काष्ठा mtd_info *);

अटल पूर्णांक get_chip(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr, पूर्णांक mode);
अटल व्योम put_chip(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr);
#समावेश "fwh_lock.h"

अटल पूर्णांक cfi_aपंचांगel_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक cfi_aपंचांगel_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);

अटल पूर्णांक cfi_ppb_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक cfi_ppb_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);
अटल पूर्णांक cfi_ppb_is_locked(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len);

अटल काष्ठा mtd_chip_driver cfi_amdstd_chipdrv = अणु
	.probe		= शून्य, /* Not usable directly */
	.destroy	= cfi_amdstd_destroy,
	.name		= "cfi_cmdset_0002",
	.module		= THIS_MODULE
पूर्ण;

/*
 * Use status रेजिस्टर to poll क्रम Erase/ग_लिखो completion when DQ is not
 * supported. This is indicated by Bit[1:0] of SoftwareFeatures field in
 * CFI Primary Venकरोr-Specअगरic Extended Query table 1.5
 */
अटल पूर्णांक cfi_use_status_reg(काष्ठा cfi_निजी *cfi)
अणु
	काष्ठा cfi_pri_amdstd *extp = cfi->cmdset_priv;
	u8 poll_mask = CFI_POLL_STATUS_REG | CFI_POLL_DQ;

	वापस extp->MinorVersion >= '5' &&
		(extp->SoftwareFeatures & poll_mask) == CFI_POLL_STATUS_REG;
पूर्ण

अटल पूर्णांक cfi_check_err_status(काष्ठा map_info *map, काष्ठा flchip *chip,
				अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word status;

	अगर (!cfi_use_status_reg(cfi))
		वापस 0;

	cfi_send_gen_cmd(0x70, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	status = map_पढ़ो(map, adr);

	/* The error bits are invalid जबतक the chip's busy */
	अगर (!map_word_bitsset(map, status, CMD(CFI_SR_DRB)))
		वापस 0;

	अगर (map_word_bitsset(map, status, CMD(0x3a))) अणु
		अचिन्हित दीर्घ chipstatus = MERGESTATUS(status);

		अगर (chipstatus & CFI_SR_ESB)
			pr_err("%s erase operation failed, status %lx\n",
			       map->name, chipstatus);
		अगर (chipstatus & CFI_SR_PSB)
			pr_err("%s program operation failed, status %lx\n",
			       map->name, chipstatus);
		अगर (chipstatus & CFI_SR_WBASB)
			pr_err("%s buffer program command aborted, status %lx\n",
			       map->name, chipstatus);
		अगर (chipstatus & CFI_SR_SLSB)
			pr_err("%s sector write protected, status %lx\n",
			       map->name, chipstatus);

		/* Erase/Program status bits are set on the operation failure */
		अगर (chipstatus & (CFI_SR_ESB | CFI_SR_PSB))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* #घोषणा DEBUG_CFI_FEATURES */


#अगर_घोषित DEBUG_CFI_FEATURES
अटल व्योम cfi_tell_features(काष्ठा cfi_pri_amdstd *extp)
अणु
	स्थिर अक्षर* erase_suspend[3] = अणु
		"Not supported", "Read only", "Read/write"
	पूर्ण;
	स्थिर अक्षर* top_bottom[6] = अणु
		"No WP", "8x8KiB sectors at top & bottom, no WP",
		"Bottom boot", "Top boot",
		"Uniform, Bottom WP", "Uniform, Top WP"
	पूर्ण;

	prपूर्णांकk("  Silicon revision: %d\n", extp->SiliconRevision >> 1);
	prपूर्णांकk("  Address sensitive unlock: %s\n",
	       (extp->SiliconRevision & 1) ? "Not required" : "Required");

	अगर (extp->EraseSuspend < ARRAY_SIZE(erase_suspend))
		prपूर्णांकk("  Erase Suspend: %s\n", erase_suspend[extp->EraseSuspend]);
	अन्यथा
		prपूर्णांकk("  Erase Suspend: Unknown value %d\n", extp->EraseSuspend);

	अगर (extp->BlkProt == 0)
		prपूर्णांकk("  Block protection: Not supported\n");
	अन्यथा
		prपूर्णांकk("  Block protection: %d sectors per group\n", extp->BlkProt);


	prपूर्णांकk("  Temporary block unprotect: %s\n",
	       extp->TmpBlkUnprotect ? "Supported" : "Not supported");
	prपूर्णांकk("  Block protect/unprotect scheme: %d\n", extp->BlkProtUnprot);
	prपूर्णांकk("  Number of simultaneous operations: %d\n", extp->SimultaneousOps);
	prपूर्णांकk("  Burst mode: %s\n",
	       extp->BurstMode ? "Supported" : "Not supported");
	अगर (extp->PageMode == 0)
		prपूर्णांकk("  Page mode: Not supported\n");
	अन्यथा
		prपूर्णांकk("  Page mode: %d word page\n", extp->PageMode << 2);

	prपूर्णांकk("  Vpp Supply Minimum Program/Erase Voltage: %d.%d V\n",
	       extp->VppMin >> 4, extp->VppMin & 0xf);
	prपूर्णांकk("  Vpp Supply Maximum Program/Erase Voltage: %d.%d V\n",
	       extp->VppMax >> 4, extp->VppMax & 0xf);

	अगर (extp->TopBottom < ARRAY_SIZE(top_bottom))
		prपूर्णांकk("  Top/Bottom Boot Block: %s\n", top_bottom[extp->TopBottom]);
	अन्यथा
		prपूर्णांकk("  Top/Bottom Boot Block: Unknown value %d\n", extp->TopBottom);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित AMD_BOOTLOC_BUG
/* Wheee. Bring me the head of someone at AMD. */
अटल व्योम fixup_amd_bootblock(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_amdstd *extp = cfi->cmdset_priv;
	__u8 major = extp->MajorVersion;
	__u8 minor = extp->MinorVersion;

	अगर (((major << 8) | minor) < 0x3131) अणु
		/* CFI version 1.0 => करोn't trust bootloc */

		pr_debug("%s: JEDEC Vendor ID is 0x%02X Device ID is 0x%02X\n",
			map->name, cfi->mfr, cfi->id);

		/* AFAICS all 29LV400 with a bottom boot block have a device ID
		 * of 0x22BA in 16-bit mode and 0xBA in 8-bit mode.
		 * These were badly detected as they have the 0x80 bit set
		 * so treat them as a special हाल.
		 */
		अगर (((cfi->id == 0xBA) || (cfi->id == 0x22BA)) &&

			/* Macronix added CFI to their 2nd generation
			 * MX29LV400C B/T but AFAICS no other 29LV400 (AMD,
			 * Fujitsu, Spansion, EON, ESI and older Macronix)
			 * has CFI.
			 *
			 * Thereक्रमe also check the manufacturer.
			 * This reduces the risk of false detection due to
			 * the 8-bit device ID.
			 */
			(cfi->mfr == CFI_MFR_MACRONIX)) अणु
			pr_debug("%s: Macronix MX29LV400C with bottom boot block"
				" detected\n", map->name);
			extp->TopBottom = 2;	/* bottom boot */
		पूर्ण अन्यथा
		अगर (cfi->id & 0x80) अणु
			prपूर्णांकk(KERN_WARNING "%s: JEDEC Device ID is 0x%02X. Assuming broken CFI table.\n", map->name, cfi->id);
			extp->TopBottom = 3;	/* top boot */
		पूर्ण अन्यथा अणु
			extp->TopBottom = 2;	/* bottom boot */
		पूर्ण

		pr_debug("%s: AMD CFI PRI V%c.%c has no boot block field;"
			" deduced %s from Device ID\n", map->name, major, minor,
			extp->TopBottom == 2 ? "bottom" : "top");
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर !FORCE_WORD_WRITE
अटल व्योम fixup_use_ग_लिखो_buffers(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	अगर (cfi->mfr == CFI_MFR_AMD && cfi->id == 0x2201)
		वापस;

	अगर (cfi->cfiq->BufWriteTimeoutTyp) अणु
		pr_debug("Using buffer write method\n");
		mtd->_ग_लिखो = cfi_amdstd_ग_लिखो_buffers;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* !FORCE_WORD_WRITE */

/* Aपंचांगel chips करोn't use the same PRI क्रमmat as AMD chips */
अटल व्योम fixup_convert_aपंचांगel_pri(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_amdstd *extp = cfi->cmdset_priv;
	काष्ठा cfi_pri_aपंचांगel aपंचांगel_pri;

	स_नकल(&aपंचांगel_pri, extp, माप(aपंचांगel_pri));
	स_रखो((अक्षर *)extp + 5, 0, माप(*extp) - 5);

	अगर (aपंचांगel_pri.Features & 0x02)
		extp->EraseSuspend = 2;

	/* Some chips got it backwards... */
	अगर (cfi->id == AT49BV6416) अणु
		अगर (aपंचांगel_pri.BottomBoot)
			extp->TopBottom = 3;
		अन्यथा
			extp->TopBottom = 2;
	पूर्ण अन्यथा अणु
		अगर (aपंचांगel_pri.BottomBoot)
			extp->TopBottom = 2;
		अन्यथा
			extp->TopBottom = 3;
	पूर्ण

	/* burst ग_लिखो mode not supported */
	cfi->cfiq->BufWriteTimeoutTyp = 0;
	cfi->cfiq->BufWriteTimeoutMax = 0;
पूर्ण

अटल व्योम fixup_use_secsi(काष्ठा mtd_info *mtd)
अणु
	/* Setup क्रम chips with a secsi area */
	mtd->_पढ़ो_user_prot_reg = cfi_amdstd_secsi_पढ़ो;
	mtd->_पढ़ो_fact_prot_reg = cfi_amdstd_secsi_पढ़ो;
पूर्ण

अटल व्योम fixup_use_erase_chip(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अगर ((cfi->cfiq->NumEraseRegions == 1) &&
		((cfi->cfiq->EraseRegionInfo[0] & 0xffff) == 0)) अणु
		mtd->_erase = cfi_amdstd_erase_chip;
	पूर्ण

पूर्ण

/*
 * Some Aपंचांगel chips (e.g. the AT49BV6416) घातer-up with all sectors
 * locked by शेष.
 */
अटल व्योम fixup_use_aपंचांगel_lock(काष्ठा mtd_info *mtd)
अणु
	mtd->_lock = cfi_aपंचांगel_lock;
	mtd->_unlock = cfi_aपंचांगel_unlock;
	mtd->flags |= MTD_POWERUP_LOCK;
पूर्ण

अटल व्योम fixup_old_sst_eraseregion(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	/*
	 * These flashes report two separate eraseblock regions based on the
	 * sector_erase-size and block_erase-size, although they both operate on the
	 * same memory. This is not allowed according to CFI, so we just pick the
	 * sector_erase-size.
	 */
	cfi->cfiq->NumEraseRegions = 1;
पूर्ण

अटल व्योम fixup_sst39vf(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	fixup_old_sst_eraseregion(mtd);

	cfi->addr_unlock1 = 0x5555;
	cfi->addr_unlock2 = 0x2AAA;
पूर्ण

अटल व्योम fixup_sst39vf_rev_b(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	fixup_old_sst_eraseregion(mtd);

	cfi->addr_unlock1 = 0x555;
	cfi->addr_unlock2 = 0x2AA;

	cfi->sector_erase_cmd = CMD(0x50);
पूर्ण

अटल व्योम fixup_sst38vf640x_sectorsize(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	fixup_sst39vf_rev_b(mtd);

	/*
	 * CFI reports 1024 sectors (0x03ff+1) of 64KBytes (0x0100*256) where
	 * it should report a size of 8KBytes (0x0020*256).
	 */
	cfi->cfiq->EraseRegionInfo[0] = 0x002003ff;
	pr_warn("%s: Bad 38VF640x CFI data; adjusting sector size from 64 to 8KiB\n",
		mtd->name);
पूर्ण

अटल व्योम fixup_s29gl064n_sectors(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	अगर ((cfi->cfiq->EraseRegionInfo[0] & 0xffff) == 0x003f) अणु
		cfi->cfiq->EraseRegionInfo[0] |= 0x0040;
		pr_warn("%s: Bad S29GL064N CFI data; adjust from 64 to 128 sectors\n",
			mtd->name);
	पूर्ण
पूर्ण

अटल व्योम fixup_s29gl032n_sectors(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	अगर ((cfi->cfiq->EraseRegionInfo[1] & 0xffff) == 0x007e) अणु
		cfi->cfiq->EraseRegionInfo[1] &= ~0x0040;
		pr_warn("%s: Bad S29GL032N CFI data; adjust from 127 to 63 sectors\n",
			mtd->name);
	पूर्ण
पूर्ण

अटल व्योम fixup_s29ns512p_sectors(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	/*
	 *  S29NS512P flash uses more than 8bits to report number of sectors,
	 * which is not permitted by CFI.
	 */
	cfi->cfiq->EraseRegionInfo[0] = 0x020001ff;
	pr_warn("%s: Bad S29NS512P CFI data; adjust to 512 sectors\n",
		mtd->name);
पूर्ण

/* Used to fix CFI-Tables of chips without Extended Query Tables */
अटल काष्ठा cfi_fixup cfi_nopri_fixup_table[] = अणु
	अणु CFI_MFR_SST, 0x234a, fixup_sst39vf पूर्ण, /* SST39VF1602 */
	अणु CFI_MFR_SST, 0x234b, fixup_sst39vf पूर्ण, /* SST39VF1601 */
	अणु CFI_MFR_SST, 0x235a, fixup_sst39vf पूर्ण, /* SST39VF3202 */
	अणु CFI_MFR_SST, 0x235b, fixup_sst39vf पूर्ण, /* SST39VF3201 */
	अणु CFI_MFR_SST, 0x235c, fixup_sst39vf_rev_b पूर्ण, /* SST39VF3202B */
	अणु CFI_MFR_SST, 0x235d, fixup_sst39vf_rev_b पूर्ण, /* SST39VF3201B */
	अणु CFI_MFR_SST, 0x236c, fixup_sst39vf_rev_b पूर्ण, /* SST39VF6402B */
	अणु CFI_MFR_SST, 0x236d, fixup_sst39vf_rev_b पूर्ण, /* SST39VF6401B */
	अणु 0, 0, शून्य पूर्ण
पूर्ण;

अटल काष्ठा cfi_fixup cfi_fixup_table[] = अणु
	अणु CFI_MFR_ATMEL, CFI_ID_ANY, fixup_convert_aपंचांगel_pri पूर्ण,
#अगर_घोषित AMD_BOOTLOC_BUG
	अणु CFI_MFR_AMD, CFI_ID_ANY, fixup_amd_bootblock पूर्ण,
	अणु CFI_MFR_AMIC, CFI_ID_ANY, fixup_amd_bootblock पूर्ण,
	अणु CFI_MFR_MACRONIX, CFI_ID_ANY, fixup_amd_bootblock पूर्ण,
#पूर्ण_अगर
	अणु CFI_MFR_AMD, 0x0050, fixup_use_secsi पूर्ण,
	अणु CFI_MFR_AMD, 0x0053, fixup_use_secsi पूर्ण,
	अणु CFI_MFR_AMD, 0x0055, fixup_use_secsi पूर्ण,
	अणु CFI_MFR_AMD, 0x0056, fixup_use_secsi पूर्ण,
	अणु CFI_MFR_AMD, 0x005C, fixup_use_secsi पूर्ण,
	अणु CFI_MFR_AMD, 0x005F, fixup_use_secsi पूर्ण,
	अणु CFI_MFR_AMD, 0x0c01, fixup_s29gl064n_sectors पूर्ण,
	अणु CFI_MFR_AMD, 0x1301, fixup_s29gl064n_sectors पूर्ण,
	अणु CFI_MFR_AMD, 0x1a00, fixup_s29gl032n_sectors पूर्ण,
	अणु CFI_MFR_AMD, 0x1a01, fixup_s29gl032n_sectors पूर्ण,
	अणु CFI_MFR_AMD, 0x3f00, fixup_s29ns512p_sectors पूर्ण,
	अणु CFI_MFR_SST, 0x536a, fixup_sst38vf640x_sectorsize पूर्ण, /* SST38VF6402 */
	अणु CFI_MFR_SST, 0x536b, fixup_sst38vf640x_sectorsize पूर्ण, /* SST38VF6401 */
	अणु CFI_MFR_SST, 0x536c, fixup_sst38vf640x_sectorsize पूर्ण, /* SST38VF6404 */
	अणु CFI_MFR_SST, 0x536d, fixup_sst38vf640x_sectorsize पूर्ण, /* SST38VF6403 */
#अगर !FORCE_WORD_WRITE
	अणु CFI_MFR_ANY, CFI_ID_ANY, fixup_use_ग_लिखो_buffers पूर्ण,
#पूर्ण_अगर
	अणु 0, 0, शून्य पूर्ण
पूर्ण;
अटल काष्ठा cfi_fixup jedec_fixup_table[] = अणु
	अणु CFI_MFR_SST, SST49LF004B, fixup_use_fwh_lock पूर्ण,
	अणु CFI_MFR_SST, SST49LF040B, fixup_use_fwh_lock पूर्ण,
	अणु CFI_MFR_SST, SST49LF008A, fixup_use_fwh_lock पूर्ण,
	अणु 0, 0, शून्य पूर्ण
पूर्ण;

अटल काष्ठा cfi_fixup fixup_table[] = अणु
	/* The CFI venकरोr ids and the JEDEC venकरोr IDs appear
	 * to be common.  It is like the devices id's are as
	 * well.  This table is to pick all हालs where
	 * we know that is the हाल.
	 */
	अणु CFI_MFR_ANY, CFI_ID_ANY, fixup_use_erase_chip पूर्ण,
	अणु CFI_MFR_ATMEL, AT49BV6416, fixup_use_aपंचांगel_lock पूर्ण,
	अणु 0, 0, शून्य पूर्ण
पूर्ण;


अटल व्योम cfi_fixup_major_minor(काष्ठा cfi_निजी *cfi,
				  काष्ठा cfi_pri_amdstd *extp)
अणु
	अगर (cfi->mfr == CFI_MFR_SAMSUNG) अणु
		अगर ((extp->MajorVersion == '0' && extp->MinorVersion == '0') ||
		    (extp->MajorVersion == '3' && extp->MinorVersion == '3')) अणु
			/*
			 * Samsung K8P2815UQB and K8D6x16UxM chips
			 * report major=0 / minor=0.
			 * K8D3x16UxC chips report major=3 / minor=3.
			 */
			prपूर्णांकk(KERN_NOTICE "  Fixing Samsung's Amd/Fujitsu"
			       " Extended Query version to 1.%c\n",
			       extp->MinorVersion);
			extp->MajorVersion = '1';
		पूर्ण
	पूर्ण

	/*
	 * SST 38VF640x chips report major=0xFF / minor=0xFF.
	 */
	अगर (cfi->mfr == CFI_MFR_SST && (cfi->id >> 4) == 0x0536) अणु
		extp->MajorVersion = '1';
		extp->MinorVersion = '0';
	पूर्ण
पूर्ण

अटल पूर्णांक is_m29ew(काष्ठा cfi_निजी *cfi)
अणु
	अगर (cfi->mfr == CFI_MFR_INTEL &&
	    ((cfi->device_type == CFI_DEVICETYPE_X8 && (cfi->id & 0xff) == 0x7e) ||
	     (cfi->device_type == CFI_DEVICETYPE_X16 && cfi->id == 0x227e)))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * From TN-13-07: Patching the Linux Kernel and U-Boot क्रम M29 Flash, page 20:
 * Some revisions of the M29EW suffer from erase suspend hang ups. In
 * particular, it can occur when the sequence
 * Erase Confirm -> Suspend -> Program -> Resume
 * causes a lockup due to पूर्णांकernal timing issues. The consequence is that the
 * erase cannot be resumed without inserting a dummy command after programming
 * and prior to resuming. [...] The work-around is to issue a dummy ग_लिखो cycle
 * that ग_लिखोs an F0 command code beक्रमe the RESUME command.
 */
अटल व्योम cfi_fixup_m29ew_erase_suspend(काष्ठा map_info *map,
					  अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	/* beक्रमe resume, insert a dummy 0xF0 cycle क्रम Micron M29EW devices */
	अगर (is_m29ew(cfi))
		map_ग_लिखो(map, CMD(0xF0), adr);
पूर्ण

/*
 * From TN-13-07: Patching the Linux Kernel and U-Boot क्रम M29 Flash, page 22:
 *
 * Some revisions of the M29EW (क्रम example, A1 and A2 step revisions)
 * are affected by a problem that could cause a hang up when an ERASE SUSPEND
 * command is issued after an ERASE RESUME operation without रुकोing क्रम a
 * minimum delay.  The result is that once the ERASE seems to be completed
 * (no bits are toggling), the contents of the Flash memory block on which
 * the erase was ongoing could be inconsistent with the expected values
 * (typically, the array value is stuck to the 0xC0, 0xC4, 0x80, or 0x84
 * values), causing a consequent failure of the ERASE operation.
 * The occurrence of this issue could be high, especially when file प्रणाली
 * operations on the Flash are पूर्णांकensive.  As a result, it is recommended
 * that a patch be applied.  Intensive file प्रणाली operations can cause many
 * calls to the garbage routine to मुक्त Flash space (also by erasing physical
 * Flash blocks) and as a result, many consecutive SUSPEND and RESUME
 * commands can occur.  The problem disappears when a delay is inserted after
 * the RESUME command by using the udelay() function available in Linux.
 * The DELAY value must be tuned based on the customer's platक्रमm.
 * The maximum value that fixes the problem in all हालs is 500us.
 * But, in our experience, a delay of 30 तगs to 50 तगs is sufficient
 * in most हालs.
 * We have chosen 500तगs because this latency is acceptable.
 */
अटल व्योम cfi_fixup_m29ew_delay_after_resume(काष्ठा cfi_निजी *cfi)
अणु
	/*
	 * Resolving the Delay After Resume Issue see Micron TN-13-07
	 * Worst हाल delay must be 500तगs but 30-50तगs should be ok as well
	 */
	अगर (is_m29ew(cfi))
		cfi_udelay(500);
पूर्ण

काष्ठा mtd_info *cfi_cmdset_0002(काष्ठा map_info *map, पूर्णांक primary)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा device_node __maybe_unused *np = map->device_node;
	काष्ठा mtd_info *mtd;
	पूर्णांक i;

	mtd = kzalloc(माप(*mtd), GFP_KERNEL);
	अगर (!mtd)
		वापस शून्य;
	mtd->priv = map;
	mtd->type = MTD_NORFLASH;

	/* Fill in the शेष mtd operations */
	mtd->_erase   = cfi_amdstd_erase_varsize;
	mtd->_ग_लिखो   = cfi_amdstd_ग_लिखो_words;
	mtd->_पढ़ो    = cfi_amdstd_पढ़ो;
	mtd->_sync    = cfi_amdstd_sync;
	mtd->_suspend = cfi_amdstd_suspend;
	mtd->_resume  = cfi_amdstd_resume;
	mtd->_पढ़ो_user_prot_reg = cfi_amdstd_पढ़ो_user_prot_reg;
	mtd->_पढ़ो_fact_prot_reg = cfi_amdstd_पढ़ो_fact_prot_reg;
	mtd->_get_fact_prot_info = cfi_amdstd_get_fact_prot_info;
	mtd->_get_user_prot_info = cfi_amdstd_get_user_prot_info;
	mtd->_ग_लिखो_user_prot_reg = cfi_amdstd_ग_लिखो_user_prot_reg;
	mtd->_lock_user_prot_reg = cfi_amdstd_lock_user_prot_reg;
	mtd->flags   = MTD_CAP_NORFLASH;
	mtd->name    = map->name;
	mtd->ग_लिखोsize = 1;
	mtd->ग_लिखोbufsize = cfi_पूर्णांकerleave(cfi) << cfi->cfiq->MaxBufWriteSize;

	pr_debug("MTD %s(): write buffer size %d\n", __func__,
			mtd->ग_लिखोbufsize);

	mtd->_panic_ग_लिखो = cfi_amdstd_panic_ग_लिखो;
	mtd->reboot_notअगरier.notअगरier_call = cfi_amdstd_reboot;

	अगर (cfi->cfi_mode==CFI_MODE_CFI)अणु
		अचिन्हित अक्षर bootloc;
		__u16 adr = primary?cfi->cfiq->P_ADR:cfi->cfiq->A_ADR;
		काष्ठा cfi_pri_amdstd *extp;

		extp = (काष्ठा cfi_pri_amdstd*)cfi_पढ़ो_pri(map, adr, माप(*extp), "Amd/Fujitsu");
		अगर (extp) अणु
			/*
			 * It's a real CFI chip, not one क्रम which the probe
			 * routine faked a CFI काष्ठाure.
			 */
			cfi_fixup_major_minor(cfi, extp);

			/*
			 * Valid primary extension versions are: 1.0, 1.1, 1.2, 1.3, 1.4, 1.5
			 * see: http://cs.ozerki.net/zap/pub/axim-x5/करोcs/cfi_r20.pdf, page 19 
			 *      http://www.spansion.com/Support/AppNotes/cfi_100_20011201.pdf
			 *      http://www.spansion.com/Support/Datasheets/s29ws-p_00_a12_e.pdf
			 *      http://www.spansion.com/Support/Datasheets/S29GL_128S_01GS_00_02_e.pdf
			 */
			अगर (extp->MajorVersion != '1' ||
			    (extp->MajorVersion == '1' && (extp->MinorVersion < '0' || extp->MinorVersion > '5'))) अणु
				prपूर्णांकk(KERN_ERR "  Unknown Amd/Fujitsu Extended Query "
				       "version %c.%c (%#02x/%#02x).\n",
				       extp->MajorVersion, extp->MinorVersion,
				       extp->MajorVersion, extp->MinorVersion);
				kमुक्त(extp);
				kमुक्त(mtd);
				वापस शून्य;
			पूर्ण

			prपूर्णांकk(KERN_INFO "  Amd/Fujitsu Extended Query version %c.%c.\n",
			       extp->MajorVersion, extp->MinorVersion);

			/* Install our own निजी info काष्ठाure */
			cfi->cmdset_priv = extp;

			/* Apply cfi device specअगरic fixups */
			cfi_fixup(mtd, cfi_fixup_table);

#अगर_घोषित DEBUG_CFI_FEATURES
			/* Tell the user about it in lots of lovely detail */
			cfi_tell_features(extp);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
			अगर (np && of_property_पढ़ो_bool(
				    np, "use-advanced-sector-protection")
			    && extp->BlkProtUnprot == 8) अणु
				prपूर्णांकk(KERN_INFO "  Advanced Sector Protection (PPB Locking) supported\n");
				mtd->_lock = cfi_ppb_lock;
				mtd->_unlock = cfi_ppb_unlock;
				mtd->_is_locked = cfi_ppb_is_locked;
			पूर्ण
#पूर्ण_अगर

			bootloc = extp->TopBottom;
			अगर ((bootloc < 2) || (bootloc > 5)) अणु
				prपूर्णांकk(KERN_WARNING "%s: CFI contains unrecognised boot "
				       "bank location (%d). Assuming bottom.\n",
				       map->name, bootloc);
				bootloc = 2;
			पूर्ण

			अगर (bootloc == 3 && cfi->cfiq->NumEraseRegions > 1) अणु
				prपूर्णांकk(KERN_WARNING "%s: Swapping erase regions for top-boot CFI table.\n", map->name);

				क्रम (i=0; i<cfi->cfiq->NumEraseRegions / 2; i++) अणु
					पूर्णांक j = (cfi->cfiq->NumEraseRegions-1)-i;

					swap(cfi->cfiq->EraseRegionInfo[i],
					     cfi->cfiq->EraseRegionInfo[j]);
				पूर्ण
			पूर्ण
			/* Set the शेष CFI lock/unlock addresses */
			cfi->addr_unlock1 = 0x555;
			cfi->addr_unlock2 = 0x2aa;
		पूर्ण
		cfi_fixup(mtd, cfi_nopri_fixup_table);

		अगर (!cfi->addr_unlock1 || !cfi->addr_unlock2) अणु
			kमुक्त(mtd);
			वापस शून्य;
		पूर्ण

	पूर्ण /* CFI mode */
	अन्यथा अगर (cfi->cfi_mode == CFI_MODE_JEDEC) अणु
		/* Apply jedec specअगरic fixups */
		cfi_fixup(mtd, jedec_fixup_table);
	पूर्ण
	/* Apply generic fixups */
	cfi_fixup(mtd, fixup_table);

	क्रम (i=0; i< cfi->numchips; i++) अणु
		cfi->chips[i].word_ग_लिखो_समय = 1<<cfi->cfiq->WordWriteTimeoutTyp;
		cfi->chips[i].buffer_ग_लिखो_समय = 1<<cfi->cfiq->BufWriteTimeoutTyp;
		cfi->chips[i].erase_समय = 1<<cfi->cfiq->BlockEraseTimeoutTyp;
		/*
		 * First calculate the समयout max according to समयout field
		 * of काष्ठा cfi_ident that probed from chip's CFI aera, अगर
		 * available. Specअगरy a minimum of 2000us, in हाल the CFI data
		 * is wrong.
		 */
		अगर (cfi->cfiq->BufWriteTimeoutTyp &&
		    cfi->cfiq->BufWriteTimeoutMax)
			cfi->chips[i].buffer_ग_लिखो_समय_max =
				1 << (cfi->cfiq->BufWriteTimeoutTyp +
				      cfi->cfiq->BufWriteTimeoutMax);
		अन्यथा
			cfi->chips[i].buffer_ग_लिखो_समय_max = 0;

		cfi->chips[i].buffer_ग_लिखो_समय_max =
			max(cfi->chips[i].buffer_ग_लिखो_समय_max, 2000);

		cfi->chips[i].ref_poपूर्णांक_counter = 0;
		init_रुकोqueue_head(&(cfi->chips[i].wq));
	पूर्ण

	map->fldrv = &cfi_amdstd_chipdrv;

	वापस cfi_amdstd_setup(mtd);
पूर्ण
काष्ठा mtd_info *cfi_cmdset_0006(काष्ठा map_info *map, पूर्णांक primary) __attribute__((alias("cfi_cmdset_0002")));
काष्ठा mtd_info *cfi_cmdset_0701(काष्ठा map_info *map, पूर्णांक primary) __attribute__((alias("cfi_cmdset_0002")));
EXPORT_SYMBOL_GPL(cfi_cmdset_0002);
EXPORT_SYMBOL_GPL(cfi_cmdset_0006);
EXPORT_SYMBOL_GPL(cfi_cmdset_0701);

अटल काष्ठा mtd_info *cfi_amdstd_setup(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ devsize = (1<<cfi->cfiq->DevSize) * cfi->पूर्णांकerleave;
	अचिन्हित दीर्घ offset = 0;
	पूर्णांक i,j;

	prपूर्णांकk(KERN_NOTICE "number of %s chips: %d\n",
	       (cfi->cfi_mode == CFI_MODE_CFI)?"CFI":"JEDEC",cfi->numchips);
	/* Select the correct geometry setup */
	mtd->size = devsize * cfi->numchips;

	mtd->numeraseregions = cfi->cfiq->NumEraseRegions * cfi->numchips;
	mtd->eraseregions = kदो_स्मृति_array(mtd->numeraseregions,
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
		पूर्ण
		offset += (ersize * ernum);
	पूर्ण
	अगर (offset != devsize) अणु
		/* Argh */
		prपूर्णांकk(KERN_WARNING "Sum of regions (%lx) != total size of set of interleaved chips (%lx)\n", offset, devsize);
		जाओ setup_err;
	पूर्ण

	__module_get(THIS_MODULE);
	रेजिस्टर_reboot_notअगरier(&mtd->reboot_notअगरier);
	वापस mtd;

 setup_err:
	kमुक्त(mtd->eraseregions);
	kमुक्त(mtd);
	kमुक्त(cfi->cmdset_priv);
	वापस शून्य;
पूर्ण

/*
 * Return true अगर the chip is पढ़ोy.
 *
 * Ready is one of: पढ़ो mode, query mode, erase-suspend-पढ़ो mode (in any
 * non-suspended sector) and is indicated by no toggle bits toggling.
 *
 * Note that anything more complicated than checking अगर no bits are toggling
 * (including checking DQ5 क्रम an error status) is tricky to get working
 * correctly and is thereक्रमe not करोne	(particularly with पूर्णांकerleaved chips
 * as each chip must be checked independently of the others).
 */
अटल पूर्णांक __xipram chip_पढ़ोy(काष्ठा map_info *map, काष्ठा flchip *chip,
			       अचिन्हित दीर्घ addr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word d, t;

	अगर (cfi_use_status_reg(cfi)) अणु
		map_word पढ़ोy = CMD(CFI_SR_DRB);
		/*
		 * For chips that support status रेजिस्टर, check device
		 * पढ़ोy bit
		 */
		cfi_send_gen_cmd(0x70, cfi->addr_unlock1, chip->start, map, cfi,
				 cfi->device_type, शून्य);
		d = map_पढ़ो(map, addr);

		वापस map_word_andequal(map, d, पढ़ोy, पढ़ोy);
	पूर्ण

	d = map_पढ़ो(map, addr);
	t = map_पढ़ो(map, addr);

	वापस map_word_equal(map, d, t);
पूर्ण

/*
 * Return true अगर the chip is पढ़ोy and has the correct value.
 *
 * Ready is one of: पढ़ो mode, query mode, erase-suspend-पढ़ो mode (in any
 * non-suspended sector) and it is indicated by no bits toggling.
 *
 * Error are indicated by toggling bits or bits held with the wrong value,
 * or with bits toggling.
 *
 * Note that anything more complicated than checking अगर no bits are toggling
 * (including checking DQ5 क्रम an error status) is tricky to get working
 * correctly and is thereक्रमe not करोne	(particularly with पूर्णांकerleaved chips
 * as each chip must be checked independently of the others).
 *
 */
अटल पूर्णांक __xipram chip_good(काष्ठा map_info *map, काष्ठा flchip *chip,
			      अचिन्हित दीर्घ addr, map_word expected)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	map_word oldd, curd;

	अगर (cfi_use_status_reg(cfi)) अणु
		map_word पढ़ोy = CMD(CFI_SR_DRB);

		/*
		 * For chips that support status रेजिस्टर, check device
		 * पढ़ोy bit
		 */
		cfi_send_gen_cmd(0x70, cfi->addr_unlock1, chip->start, map, cfi,
				 cfi->device_type, शून्य);
		curd = map_पढ़ो(map, addr);

		वापस map_word_andequal(map, curd, पढ़ोy, पढ़ोy);
	पूर्ण

	oldd = map_पढ़ो(map, addr);
	curd = map_पढ़ो(map, addr);

	वापस	map_word_equal(map, oldd, curd) &&
		map_word_equal(map, curd, expected);
पूर्ण

अटल पूर्णांक get_chip(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr, पूर्णांक mode)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ समयo;
	काष्ठा cfi_pri_amdstd *cfip = (काष्ठा cfi_pri_amdstd *)cfi->cmdset_priv;

 reसमय_रखो:
	समयo = jअगरfies + HZ;
 retry:
	चयन (chip->state) अणु

	हाल FL_STATUS:
		क्रम (;;) अणु
			अगर (chip_पढ़ोy(map, chip, adr))
				अवरोध;

			अगर (समय_after(jअगरfies, समयo)) अणु
				prपूर्णांकk(KERN_ERR "Waiting for chip to be ready timed out.\n");
				वापस -EIO;
			पूर्ण
			mutex_unlock(&chip->mutex);
			cfi_udelay(1);
			mutex_lock(&chip->mutex);
			/* Someone अन्यथा might have been playing with it. */
			जाओ retry;
		पूर्ण
		वापस 0;

	हाल FL_READY:
	हाल FL_CFI_QUERY:
	हाल FL_JEDEC_QUERY:
		वापस 0;

	हाल FL_ERASING:
		अगर (!cfip || !(cfip->EraseSuspend & (0x1|0x2)) ||
		    !(mode == FL_READY || mode == FL_POINT ||
		    (mode == FL_WRITING && (cfip->EraseSuspend & 0x2))))
			जाओ sleep;

		/* Do not allow suspend अगरf पढ़ो/ग_लिखो to EB address */
		अगर ((adr & chip->in_progress_block_mask) ==
		    chip->in_progress_block_addr)
			जाओ sleep;

		/* Erase suspend */
		/* It's harmless to issue the Erase-Suspend and Erase-Resume
		 * commands when the erase algorithm isn't in progress. */
		map_ग_लिखो(map, CMD(0xB0), chip->in_progress_block_addr);
		chip->oldstate = FL_ERASING;
		chip->state = FL_ERASE_SUSPENDING;
		chip->erase_suspended = 1;
		क्रम (;;) अणु
			अगर (chip_पढ़ोy(map, chip, adr))
				अवरोध;

			अगर (समय_after(jअगरfies, समयo)) अणु
				/* Should have suspended the erase by now.
				 * Send an Erase-Resume command as either
				 * there was an error (so leave the erase
				 * routine to recover from it) or we trying to
				 * use the erase-in-progress sector. */
				put_chip(map, chip, adr);
				prपूर्णांकk(KERN_ERR "MTD %s(): chip not ready after erase suspend\n", __func__);
				वापस -EIO;
			पूर्ण

			mutex_unlock(&chip->mutex);
			cfi_udelay(1);
			mutex_lock(&chip->mutex);
			/* Nobody will touch it जबतक it's in state FL_ERASE_SUSPENDING.
			   So we can just loop here. */
		पूर्ण
		chip->state = FL_READY;
		वापस 0;

	हाल FL_XIP_WHILE_ERASING:
		अगर (mode != FL_READY && mode != FL_POINT &&
		    (!cfip || !(cfip->EraseSuspend&2)))
			जाओ sleep;
		chip->oldstate = chip->state;
		chip->state = FL_READY;
		वापस 0;

	हाल FL_SHUTDOWN:
		/* The machine is rebooting */
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
		जाओ reसमय_रखो;
	पूर्ण
पूर्ण


अटल व्योम put_chip(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	चयन(chip->oldstate) अणु
	हाल FL_ERASING:
		cfi_fixup_m29ew_erase_suspend(map,
			chip->in_progress_block_addr);
		map_ग_लिखो(map, cfi->sector_erase_cmd, chip->in_progress_block_addr);
		cfi_fixup_m29ew_delay_after_resume(cfi);
		chip->oldstate = FL_READY;
		chip->state = FL_ERASING;
		अवरोध;

	हाल FL_XIP_WHILE_ERASING:
		chip->state = chip->oldstate;
		chip->oldstate = FL_READY;
		अवरोध;

	हाल FL_READY:
	हाल FL_STATUS:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "MTD: put_chip() called with oldstate %d!!\n", chip->oldstate);
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
		map_ग_लिखो(map, CMD(0xf0), adr);
		chip->state = FL_READY;
	पूर्ण
	(व्योम) map_पढ़ो(map, adr);
	xip_iprefetch();
	local_irq_enable();
पूर्ण

/*
 * When a delay is required क्रम the flash operation to complete, the
 * xip_udelay() function is polling क्रम both the given समयout and pending
 * (but still masked) hardware पूर्णांकerrupts.  Whenever there is an पूर्णांकerrupt
 * pending then the flash erase operation is suspended, array mode restored
 * and पूर्णांकerrupts unmasked.  Task scheduling might also happen at that
 * poपूर्णांक.  The CPU eventually वापसs from the पूर्णांकerrupt or the call to
 * schedule() and the suspended flash operation is resumed क्रम the reमुख्यing
 * of the delay period.
 *
 * Warning: this function _will_ fool पूर्णांकerrupt latency tracing tools.
 */

अटल व्योम __xipram xip_udelay(काष्ठा map_info *map, काष्ठा flchip *chip,
				अचिन्हित दीर्घ adr, पूर्णांक usec)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_pri_amdstd *extp = cfi->cmdset_priv;
	map_word status, OK = CMD(0x80);
	अचिन्हित दीर्घ suspended, start = xip_currसमय();
	flstate_t oldstate;

	करो अणु
		cpu_relax();
		अगर (xip_irqpending() && extp &&
		    ((chip->state == FL_ERASING && (extp->EraseSuspend & 2))) &&
		    (cfi_पूर्णांकerleave_is_1(cfi) || chip->oldstate == FL_READY)) अणु
			/*
			 * Let's suspend the erase operation when supported.
			 * Note that we currently करोn't try to suspend
			 * पूर्णांकerleaved chips अगर there is alपढ़ोy another
			 * operation suspended (imagine what happens
			 * when one chip was alपढ़ोy करोne with the current
			 * operation जबतक another chip suspended it, then
			 * we resume the whole thing at once).  Yes, it
			 * can happen!
			 */
			map_ग_लिखो(map, CMD(0xb0), adr);
			usec -= xip_elapsed_since(start);
			suspended = xip_currसमय();
			करो अणु
				अगर (xip_elapsed_since(suspended) > 100000) अणु
					/*
					 * The chip करोesn't want to suspend
					 * after रुकोing क्रम 100 msecs.
					 * This is a critical error but there
					 * is not much we can करो here.
					 */
					वापस;
				पूर्ण
				status = map_पढ़ो(map, adr);
			पूर्ण जबतक (!map_word_andequal(map, status, OK, OK));

			/* Suspend succeeded */
			oldstate = chip->state;
			अगर (!map_word_bitsset(map, status, CMD(0x40)))
				अवरोध;
			chip->state = FL_XIP_WHILE_ERASING;
			chip->erase_suspended = 1;
			map_ग_लिखो(map, CMD(0xf0), adr);
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
			जबतक (chip->state != FL_XIP_WHILE_ERASING) अणु
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

			/* Correct Erase Suspend Hangups क्रम M29EW */
			cfi_fixup_m29ew_erase_suspend(map, adr);
			/* Resume the ग_लिखो or erase operation */
			map_ग_लिखो(map, cfi->sector_erase_cmd, adr);
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
	पूर्ण जबतक (!map_word_andequal(map, status, OK, OK)
		 && xip_elapsed_since(start) < usec);
पूर्ण

#घोषणा UDELAY(map, chip, adr, usec)  xip_udelay(map, chip, adr, usec)

/*
 * The INVALIDATE_CACHED_RANGE() macro is normally used in parallel जबतक
 * the flash is actively programming or erasing since we have to poll क्रम
 * the operation to complete anyway.  We can't करो that in a generic way with
 * a XIP setup so करो it beक्रमe the actual flash operation in this हाल
 * and stub it out from INVALIDATE_CACHE_UDELAY.
 */
#घोषणा XIP_INVAL_CACHED_RANGE(map, from, size)  \
	INVALIDATE_CACHED_RANGE(map, from, size)

#घोषणा INVALIDATE_CACHE_UDELAY(map, chip, adr, len, usec)  \
	UDELAY(map, chip, adr, usec)

/*
 * Extra notes:
 *
 * Activating this XIP support changes the way the code works a bit.  For
 * example the code to suspend the current process when concurrent access
 * happens is never executed because xip_udelay() will always वापस with the
 * same chip state as it was entered with.  This is why there is no care क्रम
 * the presence of add_रुको_queue() or schedule() calls from within a couple
 * xip_disable()'d  areas of code, like in करो_erase_oneblock क्रम example.
 * The queueing and scheduling are always happening within xip_udelay().
 *
 * Similarly, get_chip() and put_chip() just happen to always be executed
 * with chip->state set to FL_READY (or FL_XIP_WHILE_*) where flash state
 * is in array mode, thereक्रमe never executing many हालs therein and not
 * causing any problem with XIP.
 */

#अन्यथा

#घोषणा xip_disable(map, chip, adr)
#घोषणा xip_enable(map, chip, adr)
#घोषणा XIP_INVAL_CACHED_RANGE(x...)

#घोषणा UDELAY(map, chip, adr, usec)  \
करो अणु  \
	mutex_unlock(&chip->mutex);  \
	cfi_udelay(usec);  \
	mutex_lock(&chip->mutex);  \
पूर्ण जबतक (0)

#घोषणा INVALIDATE_CACHE_UDELAY(map, chip, adr, len, usec)  \
करो अणु  \
	mutex_unlock(&chip->mutex);  \
	INVALIDATE_CACHED_RANGE(map, adr, len);  \
	cfi_udelay(usec);  \
	mutex_lock(&chip->mutex);  \
पूर्ण जबतक (0)

#पूर्ण_अगर

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
		map_ग_लिखो(map, CMD(0xf0), cmd_addr);
		chip->state = FL_READY;
	पूर्ण

	map_copy_from(map, buf, adr, len);

	put_chip(map, chip, cmd_addr);

	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण


अटल पूर्णांक cfi_amdstd_पढ़ो (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
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

प्रकार पूर्णांक (*otp_op_t)(काष्ठा map_info *map, काष्ठा flchip *chip,
			loff_t adr, माप_प्रकार len, u_अक्षर *buf, माप_प्रकार grouplen);

अटल अंतरभूत व्योम otp_enter(काष्ठा map_info *map, काष्ठा flchip *chip,
			     loff_t adr, माप_प्रकार len)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x88, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);

	INVALIDATE_CACHED_RANGE(map, chip->start + adr, len);
पूर्ण

अटल अंतरभूत व्योम otp_निकास(काष्ठा map_info *map, काष्ठा flchip *chip,
			    loff_t adr, माप_प्रकार len)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x90, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x00, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);

	INVALIDATE_CACHED_RANGE(map, chip->start + adr, len);
पूर्ण

अटल अंतरभूत पूर्णांक करो_पढ़ो_secsi_onechip(काष्ठा map_info *map,
					काष्ठा flchip *chip, loff_t adr,
					माप_प्रकार len, u_अक्षर *buf,
					माप_प्रकार grouplen)
अणु
	DECLARE_WAITQUEUE(रुको, current);

 retry:
	mutex_lock(&chip->mutex);

	अगर (chip->state != FL_READY)अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&chip->wq, &रुको);

		mutex_unlock(&chip->mutex);

		schedule();
		हटाओ_रुको_queue(&chip->wq, &रुको);

		जाओ retry;
	पूर्ण

	adr += chip->start;

	chip->state = FL_READY;

	otp_enter(map, chip, adr, len);
	map_copy_from(map, buf, adr, len);
	otp_निकास(map, chip, adr, len);

	wake_up(&chip->wq);
	mutex_unlock(&chip->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक cfi_amdstd_secsi_पढ़ो (काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ ofs;
	पूर्णांक chipnum;
	पूर्णांक ret = 0;

	/* ofs: offset within the first chip that the first पढ़ो should start */
	/* 8 secsi bytes per chip */
	chipnum=from>>3;
	ofs=from & 7;

	जबतक (len) अणु
		अचिन्हित दीर्घ thislen;

		अगर (chipnum >= cfi->numchips)
			अवरोध;

		अगर ((len + ofs -1) >> 3)
			thislen = (1<<3) - ofs;
		अन्यथा
			thislen = len;

		ret = करो_पढ़ो_secsi_onechip(map, &cfi->chips[chipnum], ofs,
					    thislen, buf, 0);
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
				     अचिन्हित दीर्घ adr, map_word datum,
				     पूर्णांक mode);

अटल पूर्णांक करो_otp_ग_लिखो(काष्ठा map_info *map, काष्ठा flchip *chip, loff_t adr,
			माप_प्रकार len, u_अक्षर *buf, माप_प्रकार grouplen)
अणु
	पूर्णांक ret;
	जबतक (len) अणु
		अचिन्हित दीर्घ bus_ofs = adr & ~(map_bankwidth(map)-1);
		पूर्णांक gap = adr - bus_ofs;
		पूर्णांक n = min_t(पूर्णांक, len, map_bankwidth(map) - gap);
		map_word datum = map_word_ff(map);

		अगर (n != map_bankwidth(map)) अणु
			/* partial ग_लिखो of a word, load old contents */
			otp_enter(map, chip, bus_ofs, map_bankwidth(map));
			datum = map_पढ़ो(map, bus_ofs);
			otp_निकास(map, chip, bus_ofs, map_bankwidth(map));
		पूर्ण

		datum = map_word_load_partial(map, datum, buf, gap, n);
		ret = करो_ग_लिखो_oneword(map, chip, bus_ofs, datum, FL_OTP_WRITE);
		अगर (ret)
			वापस ret;

		adr += n;
		buf += n;
		len -= n;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_otp_lock(काष्ठा map_info *map, काष्ठा flchip *chip, loff_t adr,
		       माप_प्रकार len, u_अक्षर *buf, माप_प्रकार grouplen)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	uपूर्णांक8_t lockreg;
	अचिन्हित दीर्घ समयo;
	पूर्णांक ret;

	/* make sure area matches group boundaries */
	अगर ((adr != 0) || (len != grouplen))
		वापस -EINVAL;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, chip->start, FL_LOCKING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण
	chip->state = FL_LOCKING;

	/* Enter lock रेजिस्टर command */
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x40, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);

	/* पढ़ो lock रेजिस्टर */
	lockreg = cfi_पढ़ो_query(map, 0);

	/* set bit 0 to protect extended memory block */
	lockreg &= ~0x01;

	/* set bit 0 to protect extended memory block */
	/* ग_लिखो lock रेजिस्टर */
	map_ग_लिखो(map, CMD(0xA0), chip->start);
	map_ग_लिखो(map, CMD(lockreg), chip->start);

	/* रुको क्रम chip to become पढ़ोy */
	समयo = jअगरfies + msecs_to_jअगरfies(2);
	क्रम (;;) अणु
		अगर (chip_पढ़ोy(map, chip, adr))
			अवरोध;

		अगर (समय_after(jअगरfies, समयo)) अणु
			pr_err("Waiting for chip to be ready timed out.\n");
			ret = -EIO;
			अवरोध;
		पूर्ण
		UDELAY(map, chip, 0, 1);
	पूर्ण

	/* निकास protection commands */
	map_ग_लिखो(map, CMD(0x90), chip->start);
	map_ग_लिखो(map, CMD(0x00), chip->start);

	chip->state = FL_READY;
	put_chip(map, chip, chip->start);
	mutex_unlock(&chip->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक cfi_amdstd_otp_walk(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			       माप_प्रकार *retlen, u_अक्षर *buf,
			       otp_op_t action, पूर्णांक user_regs)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ofs_factor = cfi->पूर्णांकerleave * cfi->device_type;
	अचिन्हित दीर्घ base;
	पूर्णांक chipnum;
	काष्ठा flchip *chip;
	uपूर्णांक8_t otp, lockreg;
	पूर्णांक ret;

	माप_प्रकार user_size, factory_size, otpsize;
	loff_t user_offset, factory_offset, otpoffset;
	पूर्णांक user_locked = 0, otplocked;

	*retlen = 0;

	क्रम (chipnum = 0; chipnum < cfi->numchips; chipnum++) अणु
		chip = &cfi->chips[chipnum];
		factory_size = 0;
		user_size = 0;

		/* Micron M29EW family */
		अगर (is_m29ew(cfi)) अणु
			base = chip->start;

			/* check whether secsi area is factory locked
			   or user lockable */
			mutex_lock(&chip->mutex);
			ret = get_chip(map, chip, base, FL_CFI_QUERY);
			अगर (ret) अणु
				mutex_unlock(&chip->mutex);
				वापस ret;
			पूर्ण
			cfi_qry_mode_on(base, map, cfi);
			otp = cfi_पढ़ो_query(map, base + 0x3 * ofs_factor);
			cfi_qry_mode_off(base, map, cfi);
			put_chip(map, chip, base);
			mutex_unlock(&chip->mutex);

			अगर (otp & 0x80) अणु
				/* factory locked */
				factory_offset = 0;
				factory_size = 0x100;
			पूर्ण अन्यथा अणु
				/* customer lockable */
				user_offset = 0;
				user_size = 0x100;

				mutex_lock(&chip->mutex);
				ret = get_chip(map, chip, base, FL_LOCKING);
				अगर (ret) अणु
					mutex_unlock(&chip->mutex);
					वापस ret;
				पूर्ण

				/* Enter lock रेजिस्टर command */
				cfi_send_gen_cmd(0xAA, cfi->addr_unlock1,
						 chip->start, map, cfi,
						 cfi->device_type, शून्य);
				cfi_send_gen_cmd(0x55, cfi->addr_unlock2,
						 chip->start, map, cfi,
						 cfi->device_type, शून्य);
				cfi_send_gen_cmd(0x40, cfi->addr_unlock1,
						 chip->start, map, cfi,
						 cfi->device_type, शून्य);
				/* पढ़ो lock रेजिस्टर */
				lockreg = cfi_पढ़ो_query(map, 0);
				/* निकास protection commands */
				map_ग_लिखो(map, CMD(0x90), chip->start);
				map_ग_लिखो(map, CMD(0x00), chip->start);
				put_chip(map, chip, chip->start);
				mutex_unlock(&chip->mutex);

				user_locked = ((lockreg & 0x01) == 0x00);
			पूर्ण
		पूर्ण

		otpsize = user_regs ? user_size : factory_size;
		अगर (!otpsize)
			जारी;
		otpoffset = user_regs ? user_offset : factory_offset;
		otplocked = user_regs ? user_locked : 1;

		अगर (!action) अणु
			/* वापस otpinfo */
			काष्ठा otp_info *otpinfo;
			len -= माप(*otpinfo);
			अगर (len <= 0)
				वापस -ENOSPC;
			otpinfo = (काष्ठा otp_info *)buf;
			otpinfo->start = from;
			otpinfo->length = otpsize;
			otpinfo->locked = otplocked;
			buf += माप(*otpinfo);
			*retlen += माप(*otpinfo);
			from += otpsize;
		पूर्ण अन्यथा अगर ((from < otpsize) && (len > 0)) अणु
			माप_प्रकार size;
			size = (len < otpsize - from) ? len : otpsize - from;
			ret = action(map, chip, otpoffset + from, size, buf,
				     otpsize);
			अगर (ret < 0)
				वापस ret;

			buf += size;
			len -= size;
			*retlen += size;
			from = 0;
		पूर्ण अन्यथा अणु
			from -= otpsize;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cfi_amdstd_get_fact_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len,
					 माप_प्रकार *retlen, काष्ठा otp_info *buf)
अणु
	वापस cfi_amdstd_otp_walk(mtd, 0, len, retlen, (u_अक्षर *)buf,
				   शून्य, 0);
पूर्ण

अटल पूर्णांक cfi_amdstd_get_user_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len,
					 माप_प्रकार *retlen, काष्ठा otp_info *buf)
अणु
	वापस cfi_amdstd_otp_walk(mtd, 0, len, retlen, (u_अक्षर *)buf,
				   शून्य, 1);
पूर्ण

अटल पूर्णांक cfi_amdstd_पढ़ो_fact_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
					 माप_प्रकार len, माप_प्रकार *retlen,
					 u_अक्षर *buf)
अणु
	वापस cfi_amdstd_otp_walk(mtd, from, len, retlen,
				   buf, करो_पढ़ो_secsi_onechip, 0);
पूर्ण

अटल पूर्णांक cfi_amdstd_पढ़ो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
					 माप_प्रकार len, माप_प्रकार *retlen,
					 u_अक्षर *buf)
अणु
	वापस cfi_amdstd_otp_walk(mtd, from, len, retlen,
				   buf, करो_पढ़ो_secsi_onechip, 1);
पूर्ण

अटल पूर्णांक cfi_amdstd_ग_लिखो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
					  माप_प्रकार len, माप_प्रकार *retlen,
					  स्थिर u_अक्षर *buf)
अणु
	वापस cfi_amdstd_otp_walk(mtd, from, len, retlen, (u_अक्षर *)buf,
				   करो_otp_ग_लिखो, 1);
पूर्ण

अटल पूर्णांक cfi_amdstd_lock_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
					 माप_प्रकार len)
अणु
	माप_प्रकार retlen;
	वापस cfi_amdstd_otp_walk(mtd, from, len, &retlen, शून्य,
				   करो_otp_lock, 1);
पूर्ण

अटल पूर्णांक __xipram करो_ग_लिखो_oneword_once(काष्ठा map_info *map,
					  काष्ठा flchip *chip,
					  अचिन्हित दीर्घ adr, map_word datum,
					  पूर्णांक mode, काष्ठा cfi_निजी *cfi)
अणु
	अचिन्हित दीर्घ समयo;
	/*
	 * We use a 1ms + 1 jअगरfies generic समयout क्रम ग_लिखोs (most devices
	 * have a max ग_लिखो समय of a few hundreds usec). However, we should
	 * use the maximum समयout value given by the chip at probe समय
	 * instead.  Unक्रमtunately, काष्ठा flchip करोes have a field क्रम
	 * maximum समयout, only क्रम typical which can be far too लघु
	 * depending of the conditions.	 The ' + 1' is to aव्योम having a
	 * समयout of 0 jअगरfies अगर HZ is smaller than 1000.
	 */
	अचिन्हित दीर्घ uWriteTimeout = (HZ / 1000) + 1;
	पूर्णांक ret = 0;

	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xA0, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	map_ग_लिखो(map, datum, adr);
	chip->state = mode;

	INVALIDATE_CACHE_UDELAY(map, chip,
				adr, map_bankwidth(map),
				chip->word_ग_लिखो_समय);

	/* See comment above क्रम समयout value. */
	समयo = jअगरfies + uWriteTimeout;
	क्रम (;;) अणु
		अगर (chip->state != mode) अणु
			/* Someone's suspended the ग_लिखो. Sleep */
			DECLARE_WAITQUEUE(रुको, current);

			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			समयo = jअगरfies + (HZ / 2); /* FIXME */
			mutex_lock(&chip->mutex);
			जारी;
		पूर्ण

		/*
		 * We check "time_after" and "!chip_good" beक्रमe checking
		 * "chip_good" to aव्योम the failure due to scheduling.
		 */
		अगर (समय_after(jअगरfies, समयo) &&
		    !chip_good(map, chip, adr, datum)) अणु
			xip_enable(map, chip, adr);
			prपूर्णांकk(KERN_WARNING "MTD %s(): software timeout\n", __func__);
			xip_disable(map, chip, adr);
			ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (chip_good(map, chip, adr, datum)) अणु
			अगर (cfi_check_err_status(map, chip, adr))
				ret = -EIO;
			अवरोध;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		UDELAY(map, chip, adr, 1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __xipram करो_ग_लिखो_oneword_start(काष्ठा map_info *map,
					   काष्ठा flchip *chip,
					   अचिन्हित दीर्घ adr, पूर्णांक mode)
अणु
	पूर्णांक ret;

	mutex_lock(&chip->mutex);

	ret = get_chip(map, chip, adr, mode);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	अगर (mode == FL_OTP_WRITE)
		otp_enter(map, chip, adr, map_bankwidth(map));

	वापस ret;
पूर्ण

अटल व्योम __xipram करो_ग_लिखो_oneword_करोne(काष्ठा map_info *map,
					   काष्ठा flchip *chip,
					   अचिन्हित दीर्घ adr, पूर्णांक mode)
अणु
	अगर (mode == FL_OTP_WRITE)
		otp_निकास(map, chip, adr, map_bankwidth(map));

	chip->state = FL_READY;
	DISABLE_VPP(map);
	put_chip(map, chip, adr);

	mutex_unlock(&chip->mutex);
पूर्ण

अटल पूर्णांक __xipram करो_ग_लिखो_oneword_retry(काष्ठा map_info *map,
					   काष्ठा flchip *chip,
					   अचिन्हित दीर्घ adr, map_word datum,
					   पूर्णांक mode)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret = 0;
	map_word oldd;
	पूर्णांक retry_cnt = 0;

	/*
	 * Check क्रम a NOP क्रम the हाल when the datum to ग_लिखो is alपढ़ोy
	 * present - it saves समय and works around buggy chips that corrupt
	 * data at other locations when 0xff is written to a location that
	 * alपढ़ोy contains 0xff.
	 */
	oldd = map_पढ़ो(map, adr);
	अगर (map_word_equal(map, oldd, datum)) अणु
		pr_debug("MTD %s(): NOP\n", __func__);
		वापस ret;
	पूर्ण

	XIP_INVAL_CACHED_RANGE(map, adr, map_bankwidth(map));
	ENABLE_VPP(map);
	xip_disable(map, chip, adr);

 retry:
	ret = करो_ग_लिखो_oneword_once(map, chip, adr, datum, mode, cfi);
	अगर (ret) अणु
		/* reset on all failures. */
		map_ग_लिखो(map, CMD(0xF0), chip->start);
		/* FIXME - should have reset delay beक्रमe continuing */

		अगर (++retry_cnt <= MAX_RETRIES) अणु
			ret = 0;
			जाओ retry;
		पूर्ण
	पूर्ण
	xip_enable(map, chip, adr);

	वापस ret;
पूर्ण

अटल पूर्णांक __xipram करो_ग_लिखो_oneword(काष्ठा map_info *map, काष्ठा flchip *chip,
				     अचिन्हित दीर्घ adr, map_word datum,
				     पूर्णांक mode)
अणु
	पूर्णांक ret;

	adr += chip->start;

	pr_debug("MTD %s(): WRITE 0x%.8lx(0x%.8lx)\n", __func__, adr,
		 datum.x[0]);

	ret = करो_ग_लिखो_oneword_start(map, chip, adr, mode);
	अगर (ret)
		वापस ret;

	ret = करो_ग_लिखो_oneword_retry(map, chip, adr, datum, mode);

	करो_ग_लिखो_oneword_करोne(map, chip, adr, mode);

	वापस ret;
पूर्ण


अटल पूर्णांक cfi_amdstd_ग_लिखो_words(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
				  माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret;
	पूर्णांक chipnum;
	अचिन्हित दीर्घ ofs, chipstart;
	DECLARE_WAITQUEUE(रुको, current);

	chipnum = to >> cfi->chipshअगरt;
	ofs = to  - (chipnum << cfi->chipshअगरt);
	chipstart = cfi->chips[chipnum].start;

	/* If it's not bus-aligned, करो the first byte ग_लिखो */
	अगर (ofs & (map_bankwidth(map)-1)) अणु
		अचिन्हित दीर्घ bus_ofs = ofs & ~(map_bankwidth(map)-1);
		पूर्णांक i = ofs - bus_ofs;
		पूर्णांक n = 0;
		map_word पंचांगp_buf;

 retry:
		mutex_lock(&cfi->chips[chipnum].mutex);

		अगर (cfi->chips[chipnum].state != FL_READY) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&cfi->chips[chipnum].wq, &रुको);

			mutex_unlock(&cfi->chips[chipnum].mutex);

			schedule();
			हटाओ_रुको_queue(&cfi->chips[chipnum].wq, &रुको);
			जाओ retry;
		पूर्ण

		/* Load 'tmp_buf' with old contents of flash */
		पंचांगp_buf = map_पढ़ो(map, bus_ofs+chipstart);

		mutex_unlock(&cfi->chips[chipnum].mutex);

		/* Number of bytes to copy from buffer */
		n = min_t(पूर्णांक, len, map_bankwidth(map)-i);

		पंचांगp_buf = map_word_load_partial(map, पंचांगp_buf, buf, i, n);

		ret = करो_ग_लिखो_oneword(map, &cfi->chips[chipnum],
				       bus_ofs, पंचांगp_buf, FL_WRITING);
		अगर (ret)
			वापस ret;

		ofs += n;
		buf += n;
		(*retlen) += n;
		len -= n;

		अगर (ofs >> cfi->chipshअगरt) अणु
			chipnum ++;
			ofs = 0;
			अगर (chipnum == cfi->numchips)
				वापस 0;
		पूर्ण
	पूर्ण

	/* We are now aligned, ग_लिखो as much as possible */
	जबतक(len >= map_bankwidth(map)) अणु
		map_word datum;

		datum = map_word_load(map, buf);

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
			chipstart = cfi->chips[chipnum].start;
		पूर्ण
	पूर्ण

	/* Write the trailing bytes अगर any */
	अगर (len & (map_bankwidth(map)-1)) अणु
		map_word पंचांगp_buf;

 retry1:
		mutex_lock(&cfi->chips[chipnum].mutex);

		अगर (cfi->chips[chipnum].state != FL_READY) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&cfi->chips[chipnum].wq, &रुको);

			mutex_unlock(&cfi->chips[chipnum].mutex);

			schedule();
			हटाओ_रुको_queue(&cfi->chips[chipnum].wq, &रुको);
			जाओ retry1;
		पूर्ण

		पंचांगp_buf = map_पढ़ो(map, ofs + chipstart);

		mutex_unlock(&cfi->chips[chipnum].mutex);

		पंचांगp_buf = map_word_load_partial(map, पंचांगp_buf, buf, 0, len);

		ret = करो_ग_लिखो_oneword(map, &cfi->chips[chipnum],
				       ofs, पंचांगp_buf, FL_WRITING);
		अगर (ret)
			वापस ret;

		(*retlen) += len;
	पूर्ण

	वापस 0;
पूर्ण

#अगर !FORCE_WORD_WRITE
अटल पूर्णांक __xipram करो_ग_लिखो_buffer_रुको(काष्ठा map_info *map,
					 काष्ठा flchip *chip, अचिन्हित दीर्घ adr,
					 map_word datum)
अणु
	अचिन्हित दीर्घ समयo;
	अचिन्हित दीर्घ u_ग_लिखो_समयout;
	पूर्णांक ret = 0;

	/*
	 * Timeout is calculated according to CFI data, अगर available.
	 * See more comments in cfi_cmdset_0002().
	 */
	u_ग_लिखो_समयout = usecs_to_jअगरfies(chip->buffer_ग_लिखो_समय_max);
	समयo = jअगरfies + u_ग_लिखो_समयout;

	क्रम (;;) अणु
		अगर (chip->state != FL_WRITING) अणु
			/* Someone's suspended the ग_लिखो. Sleep */
			DECLARE_WAITQUEUE(रुको, current);

			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			समयo = jअगरfies + (HZ / 2); /* FIXME */
			mutex_lock(&chip->mutex);
			जारी;
		पूर्ण

		/*
		 * We check "time_after" and "!chip_good" beक्रमe checking
		 * "chip_good" to aव्योम the failure due to scheduling.
		 */
		अगर (समय_after(jअगरfies, समयo) &&
		    !chip_good(map, chip, adr, datum)) अणु
			pr_err("MTD %s(): software timeout, address:0x%.8lx.\n",
			       __func__, adr);
			ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (chip_good(map, chip, adr, datum)) अणु
			अगर (cfi_check_err_status(map, chip, adr))
				ret = -EIO;
			अवरोध;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		UDELAY(map, chip, adr, 1);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __xipram करो_ग_लिखो_buffer_reset(काष्ठा map_info *map,
					   काष्ठा flchip *chip,
					   काष्ठा cfi_निजी *cfi)
अणु
	/*
	 * Recovery from ग_लिखो-buffer programming failures requires
	 * the ग_लिखो-to-buffer-reset sequence.  Since the last part
	 * of the sequence also works as a normal reset, we can run
	 * the same commands regardless of why we are here.
	 * See e.g.
	 * http://www.spansion.com/Support/Application%20Notes/MirrorBit_Write_Buffer_Prog_Page_Buffer_Read_AN.pdf
	 */
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xF0, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);

	/* FIXME - should have reset delay beक्रमe continuing */
पूर्ण

/*
 * FIXME: पूर्णांकerleaved mode not tested, and probably not supported!
 */
अटल पूर्णांक __xipram करो_ग_लिखो_buffer(काष्ठा map_info *map, काष्ठा flchip *chip,
				    अचिन्हित दीर्घ adr, स्थिर u_अक्षर *buf,
				    पूर्णांक len)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret;
	अचिन्हित दीर्घ cmd_adr;
	पूर्णांक z, words;
	map_word datum;

	adr += chip->start;
	cmd_adr = adr;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, FL_WRITING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	datum = map_word_load(map, buf);

	pr_debug("MTD %s(): WRITE 0x%.8lx(0x%.8lx)\n",
		 __func__, adr, datum.x[0]);

	XIP_INVAL_CACHED_RANGE(map, adr, len);
	ENABLE_VPP(map);
	xip_disable(map, chip, cmd_adr);

	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi, cfi->device_type, शून्य);

	/* Write Buffer Load */
	map_ग_लिखो(map, CMD(0x25), cmd_adr);

	chip->state = FL_WRITING_TO_BUFFER;

	/* Write length of data to come */
	words = len / map_bankwidth(map);
	map_ग_लिखो(map, CMD(words - 1), cmd_adr);
	/* Write data */
	z = 0;
	जबतक(z < words * map_bankwidth(map)) अणु
		datum = map_word_load(map, buf);
		map_ग_लिखो(map, datum, adr + z);

		z += map_bankwidth(map);
		buf += map_bankwidth(map);
	पूर्ण
	z -= map_bankwidth(map);

	adr += z;

	/* Write Buffer Program Confirm: GO GO GO */
	map_ग_लिखो(map, CMD(0x29), cmd_adr);
	chip->state = FL_WRITING;

	INVALIDATE_CACHE_UDELAY(map, chip,
				adr, map_bankwidth(map),
				chip->word_ग_लिखो_समय);

	ret = करो_ग_लिखो_buffer_रुको(map, chip, adr, datum);
	अगर (ret)
		करो_ग_लिखो_buffer_reset(map, chip, cfi);

	xip_enable(map, chip, adr);

	chip->state = FL_READY;
	DISABLE_VPP(map);
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);

	वापस ret;
पूर्ण


अटल पूर्णांक cfi_amdstd_ग_लिखो_buffers(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
				    माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक wbufsize = cfi_पूर्णांकerleave(cfi) << cfi->cfiq->MaxBufWriteSize;
	पूर्णांक ret;
	पूर्णांक chipnum;
	अचिन्हित दीर्घ ofs;

	chipnum = to >> cfi->chipshअगरt;
	ofs = to  - (chipnum << cfi->chipshअगरt);

	/* If it's not bus-aligned, करो the first word ग_लिखो */
	अगर (ofs & (map_bankwidth(map)-1)) अणु
		माप_प्रकार local_len = (-ofs)&(map_bankwidth(map)-1);
		अगर (local_len > len)
			local_len = len;
		ret = cfi_amdstd_ग_लिखो_words(mtd, ofs + (chipnum<<cfi->chipshअगरt),
					     local_len, retlen, buf);
		अगर (ret)
			वापस ret;
		ofs += local_len;
		buf += local_len;
		len -= local_len;

		अगर (ofs >> cfi->chipshअगरt) अणु
			chipnum ++;
			ofs = 0;
			अगर (chipnum == cfi->numchips)
				वापस 0;
		पूर्ण
	पूर्ण

	/* Write buffer is worth it only अगर more than one word to ग_लिखो... */
	जबतक (len >= map_bankwidth(map) * 2) अणु
		/* We must not cross ग_लिखो block boundaries */
		पूर्णांक size = wbufsize - (ofs & (wbufsize-1));

		अगर (size > len)
			size = len;
		अगर (size % map_bankwidth(map))
			size -= size % map_bankwidth(map);

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

	अगर (len) अणु
		माप_प्रकार retlen_dregs = 0;

		ret = cfi_amdstd_ग_लिखो_words(mtd, ofs + (chipnum<<cfi->chipshअगरt),
					     len, &retlen_dregs, buf);

		*retlen += retlen_dregs;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* !FORCE_WORD_WRITE */

/*
 * Wait क्रम the flash chip to become पढ़ोy to ग_लिखो data
 *
 * This is only called during the panic_ग_लिखो() path. When panic_ग_लिखो()
 * is called, the kernel is in the process of a panic, and will soon be
 * dead. Thereक्रमe we करोn't take any locks, and attempt to get access
 * to the chip as soon as possible.
 */
अटल पूर्णांक cfi_amdstd_panic_रुको(काष्ठा map_info *map, काष्ठा flchip *chip,
				 अचिन्हित दीर्घ adr)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक retries = 10;
	पूर्णांक i;

	/*
	 * If the driver thinks the chip is idle, and no toggle bits
	 * are changing, then the chip is actually idle क्रम sure.
	 */
	अगर (chip->state == FL_READY && chip_पढ़ोy(map, chip, adr))
		वापस 0;

	/*
	 * Try several बार to reset the chip and then रुको क्रम it
	 * to become idle. The upper limit of a few milliseconds of
	 * delay isn't a big problem: the kernel is dying anyway. It
	 * is more important to save the messages.
	 */
	जबतक (retries > 0) अणु
		स्थिर अचिन्हित दीर्घ समयo = (HZ / 1000) + 1;

		/* send the reset command */
		map_ग_लिखो(map, CMD(0xF0), chip->start);

		/* रुको क्रम the chip to become पढ़ोy */
		क्रम (i = 0; i < jअगरfies_to_usecs(समयo); i++) अणु
			अगर (chip_पढ़ोy(map, chip, adr))
				वापस 0;

			udelay(1);
		पूर्ण

		retries--;
	पूर्ण

	/* the chip never became पढ़ोy */
	वापस -EBUSY;
पूर्ण

/*
 * Write out one word of data to a single flash chip during a kernel panic
 *
 * This is only called during the panic_ग_लिखो() path. When panic_ग_लिखो()
 * is called, the kernel is in the process of a panic, and will soon be
 * dead. Thereक्रमe we करोn't take any locks, and attempt to get access
 * to the chip as soon as possible.
 *
 * The implementation of this routine is पूर्णांकentionally similar to
 * करो_ग_लिखो_oneword(), in order to ease code मुख्यtenance.
 */
अटल पूर्णांक करो_panic_ग_लिखो_oneword(काष्ठा map_info *map, काष्ठा flchip *chip,
				  अचिन्हित दीर्घ adr, map_word datum)
अणु
	स्थिर अचिन्हित दीर्घ uWriteTimeout = (HZ / 1000) + 1;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक retry_cnt = 0;
	map_word oldd;
	पूर्णांक ret;
	पूर्णांक i;

	adr += chip->start;

	ret = cfi_amdstd_panic_रुको(map, chip, adr);
	अगर (ret)
		वापस ret;

	pr_debug("MTD %s(): PANIC WRITE 0x%.8lx(0x%.8lx)\n",
			__func__, adr, datum.x[0]);

	/*
	 * Check क्रम a NOP क्रम the हाल when the datum to ग_लिखो is alपढ़ोy
	 * present - it saves समय and works around buggy chips that corrupt
	 * data at other locations when 0xff is written to a location that
	 * alपढ़ोy contains 0xff.
	 */
	oldd = map_पढ़ो(map, adr);
	अगर (map_word_equal(map, oldd, datum)) अणु
		pr_debug("MTD %s(): NOP\n", __func__);
		जाओ op_करोne;
	पूर्ण

	ENABLE_VPP(map);

retry:
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xA0, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	map_ग_लिखो(map, datum, adr);

	क्रम (i = 0; i < jअगरfies_to_usecs(uWriteTimeout); i++) अणु
		अगर (chip_पढ़ोy(map, chip, adr))
			अवरोध;

		udelay(1);
	पूर्ण

	अगर (!chip_good(map, chip, adr, datum) ||
	    cfi_check_err_status(map, chip, adr)) अणु
		/* reset on all failures. */
		map_ग_लिखो(map, CMD(0xF0), chip->start);
		/* FIXME - should have reset delay beक्रमe continuing */

		अगर (++retry_cnt <= MAX_RETRIES)
			जाओ retry;

		ret = -EIO;
	पूर्ण

op_करोne:
	DISABLE_VPP(map);
	वापस ret;
पूर्ण

/*
 * Write out some data during a kernel panic
 *
 * This is used by the mtकरोops driver to save the dying messages from a
 * kernel which has panic'd.
 *
 * This routine ignores all of the locking used throughout the rest of the
 * driver, in order to ensure that the data माला_लो written out no matter what
 * state this driver (and the flash chip itself) was in when the kernel crashed.
 *
 * The implementation of this routine is पूर्णांकentionally similar to
 * cfi_amdstd_ग_लिखो_words(), in order to ease code मुख्यtenance.
 */
अटल पूर्णांक cfi_amdstd_panic_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
				  माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ ofs, chipstart;
	पूर्णांक ret;
	पूर्णांक chipnum;

	chipnum = to >> cfi->chipshअगरt;
	ofs = to - (chipnum << cfi->chipshअगरt);
	chipstart = cfi->chips[chipnum].start;

	/* If it's not bus aligned, करो the first byte ग_लिखो */
	अगर (ofs & (map_bankwidth(map) - 1)) अणु
		अचिन्हित दीर्घ bus_ofs = ofs & ~(map_bankwidth(map) - 1);
		पूर्णांक i = ofs - bus_ofs;
		पूर्णांक n = 0;
		map_word पंचांगp_buf;

		ret = cfi_amdstd_panic_रुको(map, &cfi->chips[chipnum], bus_ofs);
		अगर (ret)
			वापस ret;

		/* Load 'tmp_buf' with old contents of flash */
		पंचांगp_buf = map_पढ़ो(map, bus_ofs + chipstart);

		/* Number of bytes to copy from buffer */
		n = min_t(पूर्णांक, len, map_bankwidth(map) - i);

		पंचांगp_buf = map_word_load_partial(map, पंचांगp_buf, buf, i, n);

		ret = करो_panic_ग_लिखो_oneword(map, &cfi->chips[chipnum],
					     bus_ofs, पंचांगp_buf);
		अगर (ret)
			वापस ret;

		ofs += n;
		buf += n;
		(*retlen) += n;
		len -= n;

		अगर (ofs >> cfi->chipshअगरt) अणु
			chipnum++;
			ofs = 0;
			अगर (chipnum == cfi->numchips)
				वापस 0;
		पूर्ण
	पूर्ण

	/* We are now aligned, ग_लिखो as much as possible */
	जबतक (len >= map_bankwidth(map)) अणु
		map_word datum;

		datum = map_word_load(map, buf);

		ret = करो_panic_ग_लिखो_oneword(map, &cfi->chips[chipnum],
					     ofs, datum);
		अगर (ret)
			वापस ret;

		ofs += map_bankwidth(map);
		buf += map_bankwidth(map);
		(*retlen) += map_bankwidth(map);
		len -= map_bankwidth(map);

		अगर (ofs >> cfi->chipshअगरt) अणु
			chipnum++;
			ofs = 0;
			अगर (chipnum == cfi->numchips)
				वापस 0;

			chipstart = cfi->chips[chipnum].start;
		पूर्ण
	पूर्ण

	/* Write the trailing bytes अगर any */
	अगर (len & (map_bankwidth(map) - 1)) अणु
		map_word पंचांगp_buf;

		ret = cfi_amdstd_panic_रुको(map, &cfi->chips[chipnum], ofs);
		अगर (ret)
			वापस ret;

		पंचांगp_buf = map_पढ़ो(map, ofs + chipstart);

		पंचांगp_buf = map_word_load_partial(map, पंचांगp_buf, buf, 0, len);

		ret = करो_panic_ग_लिखो_oneword(map, &cfi->chips[chipnum],
					     ofs, पंचांगp_buf);
		अगर (ret)
			वापस ret;

		(*retlen) += len;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Handle devices with one erase region, that only implement
 * the chip erase command.
 */
अटल पूर्णांक __xipram करो_erase_chip(काष्ठा map_info *map, काष्ठा flchip *chip)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ समयo = jअगरfies + HZ;
	अचिन्हित दीर्घ पूर्णांक adr;
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक ret;
	पूर्णांक retry_cnt = 0;

	adr = cfi->addr_unlock1;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, FL_ERASING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	pr_debug("MTD %s(): ERASE 0x%.8lx\n",
	       __func__, chip->start);

	XIP_INVAL_CACHED_RANGE(map, adr, map->size);
	ENABLE_VPP(map);
	xip_disable(map, chip, adr);

 retry:
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x80, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x10, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);

	chip->state = FL_ERASING;
	chip->erase_suspended = 0;
	chip->in_progress_block_addr = adr;
	chip->in_progress_block_mask = ~(map->size - 1);

	INVALIDATE_CACHE_UDELAY(map, chip,
				adr, map->size,
				chip->erase_समय*500);

	समयo = jअगरfies + (HZ*20);

	क्रम (;;) अणु
		अगर (chip->state != FL_ERASING) अणु
			/* Someone's suspended the erase. Sleep */
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			mutex_lock(&chip->mutex);
			जारी;
		पूर्ण
		अगर (chip->erase_suspended) अणु
			/* This erase was suspended and resumed.
			   Adjust the समयout */
			समयo = jअगरfies + (HZ*20); /* FIXME */
			chip->erase_suspended = 0;
		पूर्ण

		अगर (chip_good(map, chip, adr, map_word_ff(map))) अणु
			अगर (cfi_check_err_status(map, chip, adr))
				ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (समय_after(jअगरfies, समयo)) अणु
			prपूर्णांकk(KERN_WARNING "MTD %s(): software timeout\n",
			       __func__);
			ret = -EIO;
			अवरोध;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		UDELAY(map, chip, adr, 1000000/HZ);
	पूर्ण
	/* Did we succeed? */
	अगर (ret) अणु
		/* reset on all failures. */
		map_ग_लिखो(map, CMD(0xF0), chip->start);
		/* FIXME - should have reset delay beक्रमe continuing */

		अगर (++retry_cnt <= MAX_RETRIES) अणु
			ret = 0;
			जाओ retry;
		पूर्ण
	पूर्ण

	chip->state = FL_READY;
	xip_enable(map, chip, adr);
	DISABLE_VPP(map);
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);

	वापस ret;
पूर्ण


अटल पूर्णांक __xipram करो_erase_oneblock(काष्ठा map_info *map, काष्ठा flchip *chip, अचिन्हित दीर्घ adr, पूर्णांक len, व्योम *thunk)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ समयo = jअगरfies + HZ;
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक ret;
	पूर्णांक retry_cnt = 0;

	adr += chip->start;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, FL_ERASING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	pr_debug("MTD %s(): ERASE 0x%.8lx\n",
		 __func__, adr);

	XIP_INVAL_CACHED_RANGE(map, adr, len);
	ENABLE_VPP(map);
	xip_disable(map, chip, adr);

 retry:
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x80, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi, cfi->device_type, शून्य);
	map_ग_लिखो(map, cfi->sector_erase_cmd, adr);

	chip->state = FL_ERASING;
	chip->erase_suspended = 0;
	chip->in_progress_block_addr = adr;
	chip->in_progress_block_mask = ~(len - 1);

	INVALIDATE_CACHE_UDELAY(map, chip,
				adr, len,
				chip->erase_समय*500);

	समयo = jअगरfies + (HZ*20);

	क्रम (;;) अणु
		अगर (chip->state != FL_ERASING) अणु
			/* Someone's suspended the erase. Sleep */
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(&chip->wq, &रुको);
			mutex_unlock(&chip->mutex);
			schedule();
			हटाओ_रुको_queue(&chip->wq, &रुको);
			mutex_lock(&chip->mutex);
			जारी;
		पूर्ण
		अगर (chip->erase_suspended) अणु
			/* This erase was suspended and resumed.
			   Adjust the समयout */
			समयo = jअगरfies + (HZ*20); /* FIXME */
			chip->erase_suspended = 0;
		पूर्ण

		अगर (chip_good(map, chip, adr, map_word_ff(map))) अणु
			अगर (cfi_check_err_status(map, chip, adr))
				ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (समय_after(jअगरfies, समयo)) अणु
			prपूर्णांकk(KERN_WARNING "MTD %s(): software timeout\n",
			       __func__);
			ret = -EIO;
			अवरोध;
		पूर्ण

		/* Latency issues. Drop the lock, रुको a जबतक and retry */
		UDELAY(map, chip, adr, 1000000/HZ);
	पूर्ण
	/* Did we succeed? */
	अगर (ret) अणु
		/* reset on all failures. */
		map_ग_लिखो(map, CMD(0xF0), chip->start);
		/* FIXME - should have reset delay beक्रमe continuing */

		अगर (++retry_cnt <= MAX_RETRIES) अणु
			ret = 0;
			जाओ retry;
		पूर्ण
	पूर्ण

	chip->state = FL_READY;
	xip_enable(map, chip, adr);
	DISABLE_VPP(map);
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण


अटल पूर्णांक cfi_amdstd_erase_varsize(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	वापस cfi_varsize_frob(mtd, करो_erase_oneblock, instr->addr,
				instr->len, शून्य);
पूर्ण


अटल पूर्णांक cfi_amdstd_erase_chip(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	अगर (instr->addr != 0)
		वापस -EINVAL;

	अगर (instr->len != mtd->size)
		वापस -EINVAL;

	वापस करो_erase_chip(map, &cfi->chips[0]);
पूर्ण

अटल पूर्णांक करो_aपंचांगel_lock(काष्ठा map_info *map, काष्ठा flchip *chip,
			 अचिन्हित दीर्घ adr, पूर्णांक len, व्योम *thunk)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr + chip->start, FL_LOCKING);
	अगर (ret)
		जाओ out_unlock;
	chip->state = FL_LOCKING;

	pr_debug("MTD %s(): LOCK 0x%08lx len %d\n", __func__, adr, len);

	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x80, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	map_ग_लिखो(map, CMD(0x40), chip->start + adr);

	chip->state = FL_READY;
	put_chip(map, chip, adr + chip->start);
	ret = 0;

out_unlock:
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_aपंचांगel_unlock(काष्ठा map_info *map, काष्ठा flchip *chip,
			   अचिन्हित दीर्घ adr, पूर्णांक len, व्योम *thunk)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक ret;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr + chip->start, FL_UNLOCKING);
	अगर (ret)
		जाओ out_unlock;
	chip->state = FL_UNLOCKING;

	pr_debug("MTD %s(): LOCK 0x%08lx len %d\n", __func__, adr, len);

	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	map_ग_लिखो(map, CMD(0x70), adr);

	chip->state = FL_READY;
	put_chip(map, chip, adr + chip->start);
	ret = 0;

out_unlock:
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cfi_aपंचांगel_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस cfi_varsize_frob(mtd, करो_aपंचांगel_lock, ofs, len, शून्य);
पूर्ण

अटल पूर्णांक cfi_aपंचांगel_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	वापस cfi_varsize_frob(mtd, करो_aपंचांगel_unlock, ofs, len, शून्य);
पूर्ण

/*
 * Advanced Sector Protection - PPB (Persistent Protection Bit) locking
 */

काष्ठा ppb_lock अणु
	काष्ठा flchip *chip;
	अचिन्हित दीर्घ adr;
	पूर्णांक locked;
पूर्ण;

#घोषणा DO_XXLOCK_ONEBLOCK_LOCK		((व्योम *)1)
#घोषणा DO_XXLOCK_ONEBLOCK_UNLOCK	((व्योम *)2)
#घोषणा DO_XXLOCK_ONEBLOCK_GETLOCK	((व्योम *)3)

अटल पूर्णांक __maybe_unused करो_ppb_xxlock(काष्ठा map_info *map,
					काष्ठा flchip *chip,
					अचिन्हित दीर्घ adr, पूर्णांक len, व्योम *thunk)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ समयo;
	पूर्णांक ret;

	adr += chip->start;
	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, adr, FL_LOCKING);
	अगर (ret) अणु
		mutex_unlock(&chip->mutex);
		वापस ret;
	पूर्ण

	pr_debug("MTD %s(): XXLOCK 0x%08lx len %d\n", __func__, adr, len);

	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, शून्य);
	/* PPB entry command */
	cfi_send_gen_cmd(0xC0, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, शून्य);

	अगर (thunk == DO_XXLOCK_ONEBLOCK_LOCK) अणु
		chip->state = FL_LOCKING;
		map_ग_लिखो(map, CMD(0xA0), adr);
		map_ग_लिखो(map, CMD(0x00), adr);
	पूर्ण अन्यथा अगर (thunk == DO_XXLOCK_ONEBLOCK_UNLOCK) अणु
		/*
		 * Unlocking of one specअगरic sector is not supported, so we
		 * have to unlock all sectors of this device instead
		 */
		chip->state = FL_UNLOCKING;
		map_ग_लिखो(map, CMD(0x80), chip->start);
		map_ग_लिखो(map, CMD(0x30), chip->start);
	पूर्ण अन्यथा अगर (thunk == DO_XXLOCK_ONEBLOCK_GETLOCK) अणु
		chip->state = FL_JEDEC_QUERY;
		/* Return locked status: 0->locked, 1->unlocked */
		ret = !cfi_पढ़ो_query(map, adr);
	पूर्ण अन्यथा
		BUG();

	/*
	 * Wait क्रम some समय as unlocking of all sectors takes quite दीर्घ
	 */
	समयo = jअगरfies + msecs_to_jअगरfies(2000);	/* 2s max (un)locking */
	क्रम (;;) अणु
		अगर (chip_पढ़ोy(map, chip, adr))
			अवरोध;

		अगर (समय_after(jअगरfies, समयo)) अणु
			prपूर्णांकk(KERN_ERR "Waiting for chip to be ready timed out.\n");
			ret = -EIO;
			अवरोध;
		पूर्ण

		UDELAY(map, chip, adr, 1);
	पूर्ण

	/* Exit BC commands */
	map_ग_लिखो(map, CMD(0x90), chip->start);
	map_ग_लिखो(map, CMD(0x00), chip->start);

	chip->state = FL_READY;
	put_chip(map, chip, adr);
	mutex_unlock(&chip->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused cfi_ppb_lock(काष्ठा mtd_info *mtd, loff_t ofs,
				       uपूर्णांक64_t len)
अणु
	वापस cfi_varsize_frob(mtd, करो_ppb_xxlock, ofs, len,
				DO_XXLOCK_ONEBLOCK_LOCK);
पूर्ण

अटल पूर्णांक __maybe_unused cfi_ppb_unlock(काष्ठा mtd_info *mtd, loff_t ofs,
					 uपूर्णांक64_t len)
अणु
	काष्ठा mtd_erase_region_info *regions = mtd->eraseregions;
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा ppb_lock *sect;
	अचिन्हित दीर्घ adr;
	loff_t offset;
	uपूर्णांक64_t length;
	पूर्णांक chipnum;
	पूर्णांक i;
	पूर्णांक sectors;
	पूर्णांक ret;
	पूर्णांक max_sectors;

	/*
	 * PPB unlocking always unlocks all sectors of the flash chip.
	 * We need to re-lock all previously locked sectors. So lets
	 * first check the locking status of all sectors and save
	 * it क्रम future use.
	 */
	max_sectors = 0;
	क्रम (i = 0; i < mtd->numeraseregions; i++)
		max_sectors += regions[i].numblocks;

	sect = kसुस्मृति(max_sectors, माप(काष्ठा ppb_lock), GFP_KERNEL);
	अगर (!sect)
		वापस -ENOMEM;

	/*
	 * This code to walk all sectors is a slightly modअगरied version
	 * of the cfi_varsize_frob() code.
	 */
	i = 0;
	chipnum = 0;
	adr = 0;
	sectors = 0;
	offset = 0;
	length = mtd->size;

	जबतक (length) अणु
		पूर्णांक size = regions[i].erasesize;

		/*
		 * Only test sectors that shall not be unlocked. The other
		 * sectors shall be unlocked, so lets keep their locking
		 * status at "unlocked" (locked=0) क्रम the final re-locking.
		 */
		अगर ((offset < ofs) || (offset >= (ofs + len))) अणु
			sect[sectors].chip = &cfi->chips[chipnum];
			sect[sectors].adr = adr;
			sect[sectors].locked = करो_ppb_xxlock(
				map, &cfi->chips[chipnum], adr, 0,
				DO_XXLOCK_ONEBLOCK_GETLOCK);
		पूर्ण

		adr += size;
		offset += size;
		length -= size;

		अगर (offset == regions[i].offset + size * regions[i].numblocks)
			i++;

		अगर (adr >> cfi->chipshअगरt) अणु
			अगर (offset >= (ofs + len))
				अवरोध;
			adr = 0;
			chipnum++;

			अगर (chipnum >= cfi->numchips)
				अवरोध;
		पूर्ण

		sectors++;
		अगर (sectors >= max_sectors) अणु
			prपूर्णांकk(KERN_ERR "Only %d sectors for PPB locking supported!\n",
			       max_sectors);
			kमुक्त(sect);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Now unlock the whole chip */
	ret = cfi_varsize_frob(mtd, करो_ppb_xxlock, ofs, len,
			       DO_XXLOCK_ONEBLOCK_UNLOCK);
	अगर (ret) अणु
		kमुक्त(sect);
		वापस ret;
	पूर्ण

	/*
	 * PPB unlocking always unlocks all sectors of the flash chip.
	 * We need to re-lock all previously locked sectors.
	 */
	क्रम (i = 0; i < sectors; i++) अणु
		अगर (sect[i].locked)
			करो_ppb_xxlock(map, sect[i].chip, sect[i].adr, 0,
				      DO_XXLOCK_ONEBLOCK_LOCK);
	पूर्ण

	kमुक्त(sect);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused cfi_ppb_is_locked(काष्ठा mtd_info *mtd, loff_t ofs,
					    uपूर्णांक64_t len)
अणु
	वापस cfi_varsize_frob(mtd, करो_ppb_xxlock, ofs, len,
				DO_XXLOCK_ONEBLOCK_GETLOCK) ? 1 : 0;
पूर्ण

अटल व्योम cfi_amdstd_sync (काष्ठा mtd_info *mtd)
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


अटल पूर्णांक cfi_amdstd_suspend(काष्ठा mtd_info *mtd)
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
				chip->state = chip->oldstate;
				wake_up(&chip->wq);
			पूर्ण
			mutex_unlock(&chip->mutex);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण


अटल व्योम cfi_amdstd_resume(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक i;
	काष्ठा flchip *chip;

	क्रम (i=0; i<cfi->numchips; i++) अणु

		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		अगर (chip->state == FL_PM_SUSPENDED) अणु
			chip->state = FL_READY;
			map_ग_लिखो(map, CMD(0xF0), chip->start);
			wake_up(&chip->wq);
		पूर्ण
		अन्यथा
			prपूर्णांकk(KERN_ERR "Argh. Chip not in PM_SUSPENDED state upon resume()\n");

		mutex_unlock(&chip->mutex);
	पूर्ण
पूर्ण


/*
 * Ensure that the flash device is put back पूर्णांकo पढ़ो array mode beक्रमe
 * unloading the driver or rebooting.  On some प्रणालीs, rebooting जबतक
 * the flash is in query/program/erase mode will prevent the CPU from
 * fetching the bootloader code, requiring a hard reset or घातer cycle.
 */
अटल पूर्णांक cfi_amdstd_reset(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	पूर्णांक i, ret;
	काष्ठा flchip *chip;

	क्रम (i = 0; i < cfi->numchips; i++) अणु

		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		ret = get_chip(map, chip, chip->start, FL_SHUTDOWN);
		अगर (!ret) अणु
			map_ग_लिखो(map, CMD(0xF0), chip->start);
			chip->state = FL_SHUTDOWN;
			put_chip(map, chip, chip->start);
		पूर्ण

		mutex_unlock(&chip->mutex);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक cfi_amdstd_reboot(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			       व्योम *v)
अणु
	काष्ठा mtd_info *mtd;

	mtd = container_of(nb, काष्ठा mtd_info, reboot_notअगरier);
	cfi_amdstd_reset(mtd);
	वापस NOTIFY_DONE;
पूर्ण


अटल व्योम cfi_amdstd_destroy(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	cfi_amdstd_reset(mtd);
	unरेजिस्टर_reboot_notअगरier(&mtd->reboot_notअगरier);
	kमुक्त(cfi->cmdset_priv);
	kमुक्त(cfi->cfiq);
	kमुक्त(cfi);
	kमुक्त(mtd->eraseregions);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Crossnet Co. <info@crossnet.co.jp> et al.");
MODULE_DESCRIPTION("MTD chip driver for AMD/Fujitsu flash chips");
MODULE_ALIAS("cfi_cmdset_0006");
MODULE_ALIAS("cfi_cmdset_0701");
