<शैली गुरु>
/*
   Common Flash Interface probe code.
   (C) 2000 Red Hat. GPL'd.
*/

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mtd/xip.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/gen_probe.h>

//#घोषणा DEBUG_CFI

#अगर_घोषित DEBUG_CFI
अटल व्योम prपूर्णांक_cfi_ident(काष्ठा cfi_ident *);
#पूर्ण_अगर

अटल पूर्णांक cfi_probe_chip(काष्ठा map_info *map, __u32 base,
			  अचिन्हित दीर्घ *chip_map, काष्ठा cfi_निजी *cfi);
अटल पूर्णांक cfi_chip_setup(काष्ठा map_info *map, काष्ठा cfi_निजी *cfi);

काष्ठा mtd_info *cfi_probe(काष्ठा map_info *map);

#अगर_घोषित CONFIG_MTD_XIP

/* only needed क्रम लघु periods, so this is rather simple */
#घोषणा xip_disable()	local_irq_disable()

#घोषणा xip_allowed(base, map) \
करो अणु \
	(व्योम) map_पढ़ो(map, base); \
	xip_iprefetch(); \
	local_irq_enable(); \
पूर्ण जबतक (0)

#घोषणा xip_enable(base, map, cfi) \
करो अणु \
	cfi_qry_mode_off(base, map, cfi);		\
	xip_allowed(base, map); \
पूर्ण जबतक (0)

#घोषणा xip_disable_qry(base, map, cfi) \
करो अणु \
	xip_disable(); \
	cfi_qry_mode_on(base, map, cfi); \
पूर्ण जबतक (0)

#अन्यथा

#घोषणा xip_disable()			करो अणु पूर्ण जबतक (0)
#घोषणा xip_allowed(base, map)		करो अणु पूर्ण जबतक (0)
#घोषणा xip_enable(base, map, cfi)	करो अणु पूर्ण जबतक (0)
#घोषणा xip_disable_qry(base, map, cfi) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

/*
 * This fixup occurs immediately after पढ़ोing the CFI काष्ठाure and can affect
 * the number of chips detected, unlike cfi_fixup, which occurs after an
 * mtd_info काष्ठाure has been created क्रम the chip.
 */
काष्ठा cfi_early_fixup अणु
	uपूर्णांक16_t mfr;
	uपूर्णांक16_t id;
	व्योम (*fixup)(काष्ठा cfi_निजी *cfi);
पूर्ण;

अटल व्योम cfi_early_fixup(काष्ठा cfi_निजी *cfi,
			    स्थिर काष्ठा cfi_early_fixup *fixups)
अणु
	स्थिर काष्ठा cfi_early_fixup *f;

	क्रम (f = fixups; f->fixup; f++) अणु
		अगर (((f->mfr == CFI_MFR_ANY) || (f->mfr == cfi->mfr)) &&
		    ((f->id == CFI_ID_ANY) || (f->id == cfi->id))) अणु
			f->fixup(cfi);
		पूर्ण
	पूर्ण
पूर्ण

/* check क्रम QRY.
   in: पूर्णांकerleave,type,mode
   ret: table index, <0 क्रम error
 */

अटल पूर्णांक __xipram cfi_probe_chip(काष्ठा map_info *map, __u32 base,
				   अचिन्हित दीर्घ *chip_map, काष्ठा cfi_निजी *cfi)
अणु
	पूर्णांक i;

	अगर ((base + 0) >= map->size) अणु
		prपूर्णांकk(KERN_NOTICE
			"Probe at base[0x00](0x%08lx) past the end of the map(0x%08lx)\n",
			(अचिन्हित दीर्घ)base, map->size -1);
		वापस 0;
	पूर्ण
	अगर ((base + 0xff) >= map->size) अणु
		prपूर्णांकk(KERN_NOTICE
			"Probe at base[0x55](0x%08lx) past the end of the map(0x%08lx)\n",
			(अचिन्हित दीर्घ)base + 0x55, map->size -1);
		वापस 0;
	पूर्ण

	xip_disable();
	अगर (!cfi_qry_mode_on(base, map, cfi)) अणु
		xip_enable(base, map, cfi);
		वापस 0;
	पूर्ण

	अगर (!cfi->numchips) अणु
		/* This is the first समय we're called. Set up the CFI
		   stuff accordingly and वापस */
		वापस cfi_chip_setup(map, cfi);
	पूर्ण

	/* Check each previous chip to see अगर it's an alias */
 	क्रम (i=0; i < (base >> cfi->chipshअगरt); i++) अणु
 		अचिन्हित दीर्घ start;
 		अगर(!test_bit(i, chip_map)) अणु
			/* Skip location; no valid chip at this address */
 			जारी;
 		पूर्ण
 		start = i << cfi->chipshअगरt;
		/* This chip should be in पढ़ो mode अगर it's one
		   we've alपढ़ोy touched. */
		अगर (cfi_qry_present(map, start, cfi)) अणु
			/* Eep. This chip also had the QRY marker.
			 * Is it an alias क्रम the new one? */
			cfi_qry_mode_off(start, map, cfi);

			/* If the QRY marker goes away, it's an alias */
			अगर (!cfi_qry_present(map, start, cfi)) अणु
				xip_allowed(base, map);
				prपूर्णांकk(KERN_DEBUG "%s: Found an alias at 0x%x for the chip at 0x%lx\n",
				       map->name, base, start);
				वापस 0;
			पूर्ण
			/* Yes, it's actually got QRY क्रम data. Most
			 * unक्रमtunate. Stick the new chip in पढ़ो mode
			 * too and अगर it's the same, assume it's an alias. */
			/* FIXME: Use other modes to करो a proper check */
			cfi_qry_mode_off(base, map, cfi);

			अगर (cfi_qry_present(map, base, cfi)) अणु
				xip_allowed(base, map);
				prपूर्णांकk(KERN_DEBUG "%s: Found an alias at 0x%x for the chip at 0x%lx\n",
				       map->name, base, start);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	/* OK, अगर we got to here, then none of the previous chips appear to
	   be aliases क्रम the current one. */
	set_bit((base >> cfi->chipshअगरt), chip_map); /* Update chip map */
	cfi->numchips++;

	/* Put it back पूर्णांकo Read Mode */
	cfi_qry_mode_off(base, map, cfi);
	xip_allowed(base, map);

	prपूर्णांकk(KERN_INFO "%s: Found %d x%d devices at 0x%x in %d-bit bank\n",
	       map->name, cfi->पूर्णांकerleave, cfi->device_type*8, base,
	       map->bankwidth*8);

	वापस 1;
पूर्ण

अटल व्योम fixup_s70gl02gs_chips(काष्ठा cfi_निजी *cfi)
अणु
	/*
	 * S70GL02GS flash reports a single 256 MiB chip, but is really made up
	 * of two 128 MiB chips with 1024 sectors each.
	 */
	cfi->cfiq->DevSize = 27;
	cfi->cfiq->EraseRegionInfo[0] = 0x20003ff;
	pr_warn("Bad S70GL02GS CFI data; adjust to detect 2 chips\n");
पूर्ण

अटल स्थिर काष्ठा cfi_early_fixup cfi_early_fixup_table[] = अणु
	अणु CFI_MFR_AMD, 0x4801, fixup_s70gl02gs_chips पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __xipram cfi_chip_setup(काष्ठा map_info *map,
				   काष्ठा cfi_निजी *cfi)
अणु
	पूर्णांक ofs_factor = cfi->पूर्णांकerleave*cfi->device_type;
	__u32 base = 0;
	पूर्णांक num_erase_regions = cfi_पढ़ो_query(map, base + (0x10 + 28)*ofs_factor);
	पूर्णांक i;
	पूर्णांक addr_unlock1 = 0x555, addr_unlock2 = 0x2AA;

	xip_enable(base, map, cfi);
#अगर_घोषित DEBUG_CFI
	prपूर्णांकk("Number of erase regions: %d\n", num_erase_regions);
#पूर्ण_अगर
	अगर (!num_erase_regions)
		वापस 0;

	cfi->cfiq = kदो_स्मृति(माप(काष्ठा cfi_ident) + num_erase_regions * 4, GFP_KERNEL);
	अगर (!cfi->cfiq)
		वापस 0;

	स_रखो(cfi->cfiq,0,माप(काष्ठा cfi_ident));

	cfi->cfi_mode = CFI_MODE_CFI;

	cfi->sector_erase_cmd = CMD(0x30);

	/* Read the CFI info काष्ठाure */
	xip_disable_qry(base, map, cfi);
	क्रम (i=0; i<(माप(काष्ठा cfi_ident) + num_erase_regions * 4); i++)
		((अचिन्हित अक्षर *)cfi->cfiq)[i] = cfi_पढ़ो_query(map,base + (0x10 + i)*ofs_factor);

	/* Do any necessary byteswapping */
	cfi->cfiq->P_ID = le16_to_cpu(cfi->cfiq->P_ID);

	cfi->cfiq->P_ADR = le16_to_cpu(cfi->cfiq->P_ADR);
	cfi->cfiq->A_ID = le16_to_cpu(cfi->cfiq->A_ID);
	cfi->cfiq->A_ADR = le16_to_cpu(cfi->cfiq->A_ADR);
	cfi->cfiq->InterfaceDesc = le16_to_cpu(cfi->cfiq->InterfaceDesc);
	cfi->cfiq->MaxBufWriteSize = le16_to_cpu(cfi->cfiq->MaxBufWriteSize);

#अगर_घोषित DEBUG_CFI
	/* Dump the inक्रमmation therein */
	prपूर्णांक_cfi_ident(cfi->cfiq);
#पूर्ण_अगर

	क्रम (i=0; i<cfi->cfiq->NumEraseRegions; i++) अणु
		cfi->cfiq->EraseRegionInfo[i] = le32_to_cpu(cfi->cfiq->EraseRegionInfo[i]);

#अगर_घोषित DEBUG_CFI
		prपूर्णांकk("  Erase Region #%d: BlockSize 0x%4.4X bytes, %d blocks\n",
		       i, (cfi->cfiq->EraseRegionInfo[i] >> 8) & ~0xff,
		       (cfi->cfiq->EraseRegionInfo[i] & 0xffff) + 1);
#पूर्ण_अगर
	पूर्ण

	अगर (cfi->cfiq->P_ID == P_ID_SST_OLD) अणु
		addr_unlock1 = 0x5555;
		addr_unlock2 = 0x2AAA;
	पूर्ण

	/*
	 * Note we put the device back पूर्णांकo Read Mode BEFORE going पूर्णांकo Auto
	 * Select Mode, as some devices support nesting of modes, others
	 * करोn't. This way should always work.
	 * On cmdset 0001 the ग_लिखोs of 0xaa and 0x55 are not needed, and
	 * so should be treated as nops or illegal (and so put the device
	 * back पूर्णांकo Read Mode, which is a nop in this हाल).
	 */
	cfi_send_gen_cmd(0xf0,     0, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0xaa, addr_unlock1, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x55, addr_unlock2, base, map, cfi, cfi->device_type, शून्य);
	cfi_send_gen_cmd(0x90, addr_unlock1, base, map, cfi, cfi->device_type, शून्य);
	cfi->mfr = cfi_पढ़ो_query16(map, base);
	cfi->id = cfi_पढ़ो_query16(map, base + ofs_factor);

	/* Get AMD/Spansion extended JEDEC ID */
	अगर (cfi->mfr == CFI_MFR_AMD && (cfi->id & 0xff) == 0x7e)
		cfi->id = cfi_पढ़ो_query(map, base + 0xe * ofs_factor) << 8 |
			  cfi_पढ़ो_query(map, base + 0xf * ofs_factor);

	/* Put it back पूर्णांकo Read Mode */
	cfi_qry_mode_off(base, map, cfi);
	xip_allowed(base, map);

	cfi_early_fixup(cfi, cfi_early_fixup_table);

	prपूर्णांकk(KERN_INFO "%s: Found %d x%d devices at 0x%x in %d-bit bank. Manufacturer ID %#08x Chip ID %#08x\n",
	       map->name, cfi->पूर्णांकerleave, cfi->device_type*8, base,
	       map->bankwidth*8, cfi->mfr, cfi->id);

	वापस 1;
पूर्ण

#अगर_घोषित DEBUG_CFI
अटल अक्षर *venकरोrname(__u16 venकरोr)
अणु
	चयन (venकरोr) अणु
	हाल P_ID_NONE:
		वापस "None";

	हाल P_ID_INTEL_EXT:
		वापस "Intel/Sharp Extended";

	हाल P_ID_AMD_STD:
		वापस "AMD/Fujitsu Standard";

	हाल P_ID_INTEL_STD:
		वापस "Intel/Sharp Standard";

	हाल P_ID_AMD_EXT:
		वापस "AMD/Fujitsu Extended";

	हाल P_ID_WINBOND:
		वापस "Winbond Standard";

	हाल P_ID_ST_ADV:
		वापस "ST Advanced";

	हाल P_ID_MITSUBISHI_STD:
		वापस "Mitsubishi Standard";

	हाल P_ID_MITSUBISHI_EXT:
		वापस "Mitsubishi Extended";

	हाल P_ID_SST_PAGE:
		वापस "SST Page Write";

	हाल P_ID_SST_OLD:
		वापस "SST 39VF160x/39VF320x";

	हाल P_ID_INTEL_PERFORMANCE:
		वापस "Intel Performance Code";

	हाल P_ID_INTEL_DATA:
		वापस "Intel Data";

	हाल P_ID_RESERVED:
		वापस "Not Allowed / Reserved for Future Use";

	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण


अटल व्योम prपूर्णांक_cfi_ident(काष्ठा cfi_ident *cfip)
अणु
#अगर 0
	अगर (cfip->qry[0] != 'Q' || cfip->qry[1] != 'R' || cfip->qry[2] != 'Y') अणु
		prपूर्णांकk("Invalid CFI ident structure.\n");
		वापस;
	पूर्ण
#पूर्ण_अगर
	prपूर्णांकk("Primary Vendor Command Set: %4.4X (%s)\n", cfip->P_ID, venकरोrname(cfip->P_ID));
	अगर (cfip->P_ADR)
		prपूर्णांकk("Primary Algorithm Table at %4.4X\n", cfip->P_ADR);
	अन्यथा
		prपूर्णांकk("No Primary Algorithm Table\n");

	prपूर्णांकk("Alternative Vendor Command Set: %4.4X (%s)\n", cfip->A_ID, venकरोrname(cfip->A_ID));
	अगर (cfip->A_ADR)
		prपूर्णांकk("Alternate Algorithm Table at %4.4X\n", cfip->A_ADR);
	अन्यथा
		prपूर्णांकk("No Alternate Algorithm Table\n");


	prपूर्णांकk("Vcc Minimum: %2d.%d V\n", cfip->VccMin >> 4, cfip->VccMin & 0xf);
	prपूर्णांकk("Vcc Maximum: %2d.%d V\n", cfip->VccMax >> 4, cfip->VccMax & 0xf);
	अगर (cfip->VppMin) अणु
		prपूर्णांकk("Vpp Minimum: %2d.%d V\n", cfip->VppMin >> 4, cfip->VppMin & 0xf);
		prपूर्णांकk("Vpp Maximum: %2d.%d V\n", cfip->VppMax >> 4, cfip->VppMax & 0xf);
	पूर्ण
	अन्यथा
		prपूर्णांकk("No Vpp line\n");

	prपूर्णांकk("Typical byte/word write timeout: %d तगs\n", 1<<cfip->WordWriteTimeoutTyp);
	prपूर्णांकk("Maximum byte/word write timeout: %d तगs\n", (1<<cfip->WordWriteTimeoutMax) * (1<<cfip->WordWriteTimeoutTyp));

	अगर (cfip->BufWriteTimeoutTyp || cfip->BufWriteTimeoutMax) अणु
		prपूर्णांकk("Typical full buffer write timeout: %d तगs\n", 1<<cfip->BufWriteTimeoutTyp);
		prपूर्णांकk("Maximum full buffer write timeout: %d तगs\n", (1<<cfip->BufWriteTimeoutMax) * (1<<cfip->BufWriteTimeoutTyp));
	पूर्ण
	अन्यथा
		prपूर्णांकk("Full buffer write not supported\n");

	prपूर्णांकk("Typical block erase timeout: %d ms\n", 1<<cfip->BlockEraseTimeoutTyp);
	prपूर्णांकk("Maximum block erase timeout: %d ms\n", (1<<cfip->BlockEraseTimeoutMax) * (1<<cfip->BlockEraseTimeoutTyp));
	अगर (cfip->ChipEraseTimeoutTyp || cfip->ChipEraseTimeoutMax) अणु
		prपूर्णांकk("Typical chip erase timeout: %d ms\n", 1<<cfip->ChipEraseTimeoutTyp);
		prपूर्णांकk("Maximum chip erase timeout: %d ms\n", (1<<cfip->ChipEraseTimeoutMax) * (1<<cfip->ChipEraseTimeoutTyp));
	पूर्ण
	अन्यथा
		prपूर्णांकk("Chip erase not supported\n");

	prपूर्णांकk("Device size: 0x%X bytes (%d MiB)\n", 1 << cfip->DevSize, 1<< (cfip->DevSize - 20));
	prपूर्णांकk("Flash Device Interface description: 0x%4.4X\n", cfip->InterfaceDesc);
	चयन(cfip->InterfaceDesc) अणु
	हाल CFI_INTERFACE_X8_ASYNC:
		prपूर्णांकk("  - x8-only asynchronous interface\n");
		अवरोध;

	हाल CFI_INTERFACE_X16_ASYNC:
		prपूर्णांकk("  - x16-only asynchronous interface\n");
		अवरोध;

	हाल CFI_INTERFACE_X8_BY_X16_ASYNC:
		prपूर्णांकk("  - supports x8 and x16 via BYTE# with asynchronous interface\n");
		अवरोध;

	हाल CFI_INTERFACE_X32_ASYNC:
		prपूर्णांकk("  - x32-only asynchronous interface\n");
		अवरोध;

	हाल CFI_INTERFACE_X16_BY_X32_ASYNC:
		prपूर्णांकk("  - supports x16 and x32 via Word# with asynchronous interface\n");
		अवरोध;

	हाल CFI_INTERFACE_NOT_ALLOWED:
		prपूर्णांकk("  - Not Allowed / Reserved\n");
		अवरोध;

	शेष:
		prपूर्णांकk("  - Unknown\n");
		अवरोध;
	पूर्ण

	prपूर्णांकk("Max. bytes in buffer write: 0x%x\n", 1<< cfip->MaxBufWriteSize);
	prपूर्णांकk("Number of Erase Block Regions: %d\n", cfip->NumEraseRegions);

पूर्ण
#पूर्ण_अगर /* DEBUG_CFI */

अटल काष्ठा chip_probe cfi_chip_probe = अणु
	.name		= "CFI",
	.probe_chip	= cfi_probe_chip
पूर्ण;

काष्ठा mtd_info *cfi_probe(काष्ठा map_info *map)
अणु
	/*
	 * Just use the generic probe stuff to call our CFI-specअगरic
	 * chip_probe routine in all the possible permutations, etc.
	 */
	वापस mtd_करो_chip_probe(map, &cfi_chip_probe);
पूर्ण

अटल काष्ठा mtd_chip_driver cfi_chipdrv = अणु
	.probe		= cfi_probe,
	.name		= "cfi_probe",
	.module		= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init cfi_probe_init(व्योम)
अणु
	रेजिस्टर_mtd_chip_driver(&cfi_chipdrv);
	वापस 0;
पूर्ण

अटल व्योम __निकास cfi_probe_निकास(व्योम)
अणु
	unरेजिस्टर_mtd_chip_driver(&cfi_chipdrv);
पूर्ण

module_init(cfi_probe_init);
module_निकास(cfi_probe_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org> et al.");
MODULE_DESCRIPTION("Probe code for CFI-compliant flash chips");
