<शैली गुरु>
/*
 * Common Flash Interface support:
 *   Generic utility functions not dependent on command set
 *
 * Copyright (C) 2002 Red Hat
 * Copyright (C) 2003 STMicroelectronics Limited
 *
 * This code is covered by the GPL.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/xip.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>

व्योम cfi_udelay(पूर्णांक us)
अणु
	अगर (us >= 1000) अणु
		msleep(DIV_ROUND_UP(us, 1000));
	पूर्ण अन्यथा अणु
		udelay(us);
		cond_resched();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cfi_udelay);

/*
 * Returns the command address according to the given geometry.
 */
uपूर्णांक32_t cfi_build_cmd_addr(uपूर्णांक32_t cmd_ofs,
				काष्ठा map_info *map, काष्ठा cfi_निजी *cfi)
अणु
	अचिन्हित bankwidth = map_bankwidth(map);
	अचिन्हित पूर्णांकerleave = cfi_पूर्णांकerleave(cfi);
	अचिन्हित type = cfi->device_type;
	uपूर्णांक32_t addr;

	addr = (cmd_ofs * type) * पूर्णांकerleave;

	/* Modअगरy the unlock address अगर we are in compatibility mode.
	 * For 16bit devices on 8 bit busses
	 * and 32bit devices on 16 bit busses
	 * set the low bit of the alternating bit sequence of the address.
	 */
	अगर (((type * पूर्णांकerleave) > bankwidth) && ((cmd_ofs & 0xff) == 0xaa))
		addr |= (type >> 1)*पूर्णांकerleave;

	वापस  addr;
पूर्ण
EXPORT_SYMBOL(cfi_build_cmd_addr);

/*
 * Transक्रमms the CFI command क्रम the given geometry (bus width & पूर्णांकerleave).
 * It looks too दीर्घ to be अंतरभूत, but in the common हाल it should almost all
 * get optimised away.
 */
map_word cfi_build_cmd(u_दीर्घ cmd, काष्ठा map_info *map, काष्ठा cfi_निजी *cfi)
अणु
	map_word val = अणु अणु0पूर्ण पूर्ण;
	पूर्णांक wordwidth, words_per_bus, chip_mode, chips_per_word;
	अचिन्हित दीर्घ onecmd;
	पूर्णांक i;

	/* We करो it this way to give the compiler a fighting chance
	   of optimising away all the crap क्रम 'bankwidth' larger than
	   an अचिन्हित दीर्घ, in the common हाल where that support is
	   disabled */
	अगर (map_bankwidth_is_large(map)) अणु
		wordwidth = माप(अचिन्हित दीर्घ);
		words_per_bus = (map_bankwidth(map)) / wordwidth; // i.e. normally 1
	पूर्ण अन्यथा अणु
		wordwidth = map_bankwidth(map);
		words_per_bus = 1;
	पूर्ण

	chip_mode = map_bankwidth(map) / cfi_पूर्णांकerleave(cfi);
	chips_per_word = wordwidth * cfi_पूर्णांकerleave(cfi) / map_bankwidth(map);

	/* First, determine what the bit-pattern should be क्रम a single
	   device, according to chip mode and endianness... */
	चयन (chip_mode) अणु
	शेष: BUG();
	हाल 1:
		onecmd = cmd;
		अवरोध;
	हाल 2:
		onecmd = cpu_to_cfi16(map, cmd);
		अवरोध;
	हाल 4:
		onecmd = cpu_to_cfi32(map, cmd);
		अवरोध;
	पूर्ण

	/* Now replicate it across the size of an अचिन्हित दीर्घ, or
	   just to the bus width as appropriate */
	चयन (chips_per_word) अणु
	शेष: BUG();
#अगर BITS_PER_LONG >= 64
	हाल 8:
		onecmd |= (onecmd << (chip_mode * 32));
#पूर्ण_अगर
		fallthrough;
	हाल 4:
		onecmd |= (onecmd << (chip_mode * 16));
		fallthrough;
	हाल 2:
		onecmd |= (onecmd << (chip_mode * 8));
		fallthrough;
	हाल 1:
		;
	पूर्ण

	/* And finally, क्रम the multi-word हाल, replicate it
	   in all words in the काष्ठाure */
	क्रम (i=0; i < words_per_bus; i++) अणु
		val.x[i] = onecmd;
	पूर्ण

	वापस val;
पूर्ण
EXPORT_SYMBOL(cfi_build_cmd);

अचिन्हित दीर्घ cfi_merge_status(map_word val, काष्ठा map_info *map,
					   काष्ठा cfi_निजी *cfi)
अणु
	पूर्णांक wordwidth, words_per_bus, chip_mode, chips_per_word;
	अचिन्हित दीर्घ onestat, res = 0;
	पूर्णांक i;

	/* We करो it this way to give the compiler a fighting chance
	   of optimising away all the crap क्रम 'bankwidth' larger than
	   an अचिन्हित दीर्घ, in the common हाल where that support is
	   disabled */
	अगर (map_bankwidth_is_large(map)) अणु
		wordwidth = माप(अचिन्हित दीर्घ);
		words_per_bus = (map_bankwidth(map)) / wordwidth; // i.e. normally 1
	पूर्ण अन्यथा अणु
		wordwidth = map_bankwidth(map);
		words_per_bus = 1;
	पूर्ण

	chip_mode = map_bankwidth(map) / cfi_पूर्णांकerleave(cfi);
	chips_per_word = wordwidth * cfi_पूर्णांकerleave(cfi) / map_bankwidth(map);

	onestat = val.x[0];
	/* Or all status words together */
	क्रम (i=1; i < words_per_bus; i++) अणु
		onestat |= val.x[i];
	पूर्ण

	res = onestat;
	चयन(chips_per_word) अणु
	शेष: BUG();
#अगर BITS_PER_LONG >= 64
	हाल 8:
		res |= (onestat >> (chip_mode * 32));
#पूर्ण_अगर
		fallthrough;
	हाल 4:
		res |= (onestat >> (chip_mode * 16));
		fallthrough;
	हाल 2:
		res |= (onestat >> (chip_mode * 8));
		fallthrough;
	हाल 1:
		;
	पूर्ण

	/* Last, determine what the bit-pattern should be क्रम a single
	   device, according to chip mode and endianness... */
	चयन (chip_mode) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		res = cfi16_to_cpu(map, res);
		अवरोध;
	हाल 4:
		res = cfi32_to_cpu(map, res);
		अवरोध;
	शेष: BUG();
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL(cfi_merge_status);

/*
 * Sends a CFI command to a bank of flash क्रम the given geometry.
 *
 * Returns the offset in flash where the command was written.
 * If prev_val is non-null, it will be set to the value at the command address,
 * beक्रमe the command was written.
 */
uपूर्णांक32_t cfi_send_gen_cmd(u_अक्षर cmd, uपूर्णांक32_t cmd_addr, uपूर्णांक32_t base,
				काष्ठा map_info *map, काष्ठा cfi_निजी *cfi,
				पूर्णांक type, map_word *prev_val)
अणु
	map_word val;
	uपूर्णांक32_t addr = base + cfi_build_cmd_addr(cmd_addr, map, cfi);
	val = cfi_build_cmd(cmd, map, cfi);

	अगर (prev_val)
		*prev_val = map_पढ़ो(map, addr);

	map_ग_लिखो(map, val, addr);

	वापस addr - base;
पूर्ण
EXPORT_SYMBOL(cfi_send_gen_cmd);

पूर्णांक __xipram cfi_qry_present(काष्ठा map_info *map, __u32 base,
			     काष्ठा cfi_निजी *cfi)
अणु
	पूर्णांक osf = cfi->पूर्णांकerleave * cfi->device_type;	/* scale factor */
	map_word val[3];
	map_word qry[3];

	qry[0] = cfi_build_cmd('Q', map, cfi);
	qry[1] = cfi_build_cmd('R', map, cfi);
	qry[2] = cfi_build_cmd('Y', map, cfi);

	val[0] = map_पढ़ो(map, base + osf*0x10);
	val[1] = map_पढ़ो(map, base + osf*0x11);
	val[2] = map_पढ़ो(map, base + osf*0x12);

	अगर (!map_word_equal(map, qry[0], val[0]))
		वापस 0;

	अगर (!map_word_equal(map, qry[1], val[1]))
		वापस 0;

	अगर (!map_word_equal(map, qry[2], val[2]))
		वापस 0;

	वापस 1; 	/* "QRY" found */
पूर्ण
EXPORT_SYMBOL_GPL(cfi_qry_present);

पूर्णांक __xipram cfi_qry_mode_on(uपूर्णांक32_t base, काष्ठा map_info *map,
			     काष्ठा cfi_निजी *cfi)
अणु
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x98, 0x55, base, map, cfi, cfi->device_type, शून्य);
	अगर (cfi_qry_present(map, base, cfi))
		वापस 1;
	/* QRY not found probably we deal with some odd CFI chips */
	/* Some revisions of some old Intel chips? */
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xFF, 0, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x98, 0x55, base, map, cfi, cfi->device_type, शून्य);
	अगर (cfi_qry_present(map, base, cfi))
		वापस 1;
	/* ST M29DW chips */
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x98, 0x555, base, map, cfi, cfi->device_type, शून्य);
	अगर (cfi_qry_present(map, base, cfi))
		वापस 1;
	/* some old SST chips, e.g. 39VF160x/39VF320x */
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xAA, 0x5555, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, 0x2AAA, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x98, 0x5555, base, map, cfi, cfi->device_type, शून्य);
	अगर (cfi_qry_present(map, base, cfi))
		वापस 1;
	/* SST 39VF640xB */
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xAA, 0x555, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, 0x2AA, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x98, 0x555, base, map, cfi, cfi->device_type, शून्य);
	अगर (cfi_qry_present(map, base, cfi))
		वापस 1;
	/* QRY not found */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cfi_qry_mode_on);

व्योम __xipram cfi_qry_mode_off(uपूर्णांक32_t base, काष्ठा map_info *map,
			       काष्ठा cfi_निजी *cfi)
अणु
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xFF, 0, base, map, cfi, cfi->device_type, शून्य);
	/* M29W128G flashes require an additional reset command
	   when निकास qry mode */
	अगर ((cfi->mfr == CFI_MFR_ST) && (cfi->id == 0x227E || cfi->id == 0x7E))
		cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(cfi_qry_mode_off);

काष्ठा cfi_extquery *
__xipram cfi_पढ़ो_pri(काष्ठा map_info *map, __u16 adr, __u16 size, स्थिर अक्षर* name)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	__u32 base = 0; // cfi->chips[0].start;
	पूर्णांक ofs_factor = cfi->पूर्णांकerleave * cfi->device_type;
	पूर्णांक i;
	काष्ठा cfi_extquery *extp = शून्य;

	अगर (!adr)
		जाओ out;

	prपूर्णांकk(KERN_INFO "%s Extended Query Table at 0x%4.4X\n", name, adr);

	extp = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!extp)
		जाओ out;

#अगर_घोषित CONFIG_MTD_XIP
	local_irq_disable();
#पूर्ण_अगर

	/* Switch it पूर्णांकo Query Mode */
	cfi_qry_mode_on(base, map, cfi);
	/* Read in the Extended Query Table */
	क्रम (i=0; i<size; i++) अणु
		((अचिन्हित अक्षर *)extp)[i] =
			cfi_पढ़ो_query(map, base+((adr+i)*ofs_factor));
	पूर्ण

	/* Make sure it वापसs to पढ़ो mode */
	cfi_qry_mode_off(base, map, cfi);

#अगर_घोषित CONFIG_MTD_XIP
	(व्योम) map_पढ़ो(map, base);
	xip_iprefetch();
	local_irq_enable();
#पूर्ण_अगर

 out:	वापस extp;
पूर्ण

EXPORT_SYMBOL(cfi_पढ़ो_pri);

व्योम cfi_fixup(काष्ठा mtd_info *mtd, काष्ठा cfi_fixup *fixups)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	काष्ठा cfi_fixup *f;

	क्रम (f=fixups; f->fixup; f++) अणु
		अगर (((f->mfr == CFI_MFR_ANY) || (f->mfr == cfi->mfr)) &&
		    ((f->id  == CFI_ID_ANY)  || (f->id  == cfi->id))) अणु
			f->fixup(mtd);
		पूर्ण
	पूर्ण
पूर्ण

EXPORT_SYMBOL(cfi_fixup);

पूर्णांक cfi_varsize_frob(काष्ठा mtd_info *mtd, varsize_frob_t frob,
				     loff_t ofs, माप_प्रकार len, व्योम *thunk)
अणु
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	अचिन्हित दीर्घ adr;
	पूर्णांक chipnum, ret = 0;
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

	जबतक (i < mtd->numeraseregions && ofs >= regions[i].offset)
	       i++;
	i--;

	/* OK, now i is poपूर्णांकing at the erase region in which this
	   erase request starts. Check the start of the requested
	   erase range is aligned with the erase size which is in
	   effect here.
	*/

	अगर (ofs & (regions[i].erasesize-1))
		वापस -EINVAL;

	/* Remember the erase region we start on */
	first = i;

	/* Next, check that the end of the requested erase is aligned
	 * with the erase region at that address.
	 */

	जबतक (i<mtd->numeraseregions && (ofs + len) >= regions[i].offset)
		i++;

	/* As beक्रमe, drop back one to poपूर्णांक at the region in which
	   the address actually falls
	*/
	i--;

	अगर ((ofs + len) & (regions[i].erasesize-1))
		वापस -EINVAL;

	chipnum = ofs >> cfi->chipshअगरt;
	adr = ofs - (chipnum << cfi->chipshअगरt);

	i=first;

	जबतक(len) अणु
		पूर्णांक size = regions[i].erasesize;

		ret = (*frob)(map, &cfi->chips[chipnum], adr, size, thunk);

		अगर (ret)
			वापस ret;

		adr += size;
		ofs += size;
		len -= size;

		अगर (ofs == regions[i].offset + size * regions[i].numblocks)
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

EXPORT_SYMBOL(cfi_varsize_frob);

MODULE_LICENSE("GPL");
