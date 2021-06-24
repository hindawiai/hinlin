<शैली गुरु>
/*
 * Routines common to all CFI-type probes.
 * (C) 2001-2003 Red Hat, Inc.
 * GPL'd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/gen_probe.h>

अटल काष्ठा mtd_info *check_cmd_set(काष्ठा map_info *, पूर्णांक);
अटल काष्ठा cfi_निजी *genprobe_ident_chips(काष्ठा map_info *map,
						काष्ठा chip_probe *cp);
अटल पूर्णांक genprobe_new_chip(काष्ठा map_info *map, काष्ठा chip_probe *cp,
			     काष्ठा cfi_निजी *cfi);

काष्ठा mtd_info *mtd_करो_chip_probe(काष्ठा map_info *map, काष्ठा chip_probe *cp)
अणु
	काष्ठा mtd_info *mtd;
	काष्ठा cfi_निजी *cfi;

	/* First probe the map to see अगर we have CFI stuff there. */
	cfi = genprobe_ident_chips(map, cp);

	अगर (!cfi)
		वापस शून्य;

	map->fldrv_priv = cfi;
	/* OK we liked it. Now find a driver क्रम the command set it talks */

	mtd = check_cmd_set(map, 1); /* First the primary cmdset */
	अगर (!mtd)
		mtd = check_cmd_set(map, 0); /* Then the secondary */

	अगर (mtd) अणु
		अगर (mtd->size > map->size) अणु
			prपूर्णांकk(KERN_WARNING "Reducing visibility of %ldKiB chip to %ldKiB\n",
			       (अचिन्हित दीर्घ)mtd->size >> 10,
			       (अचिन्हित दीर्घ)map->size >> 10);
			mtd->size = map->size;
		पूर्ण
		वापस mtd;
	पूर्ण

	prपूर्णांकk(KERN_WARNING"gen_probe: No supported Vendor Command Set found\n");

	kमुक्त(cfi->cfiq);
	kमुक्त(cfi);
	map->fldrv_priv = शून्य;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mtd_करो_chip_probe);


अटल काष्ठा cfi_निजी *genprobe_ident_chips(काष्ठा map_info *map, काष्ठा chip_probe *cp)
अणु
	काष्ठा cfi_निजी cfi;
	काष्ठा cfi_निजी *retcfi;
	अचिन्हित दीर्घ *chip_map;
	पूर्णांक i, j, mapsize;
	पूर्णांक max_chips;

	स_रखो(&cfi, 0, माप(cfi));

	/* Call the probetype-specअगरic code with all permutations of
	   पूर्णांकerleave and device type, etc. */
	अगर (!genprobe_new_chip(map, cp, &cfi)) अणु
		/* The probe didn't like it */
		pr_debug("%s: Found no %s device at location zero\n",
			 cp->name, map->name);
		वापस शून्य;
	पूर्ण

#अगर 0 /* Let the CFI probe routine करो this sanity check. The Intel and AMD
	 probe routines won't ever वापस a broken CFI काष्ठाure anyway,
	 because they make them up themselves.
      */
	अगर (cfi.cfiq->NumEraseRegions == 0) अणु
		prपूर्णांकk(KERN_WARNING "Number of erase regions is zero\n");
		kमुक्त(cfi.cfiq);
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर
	cfi.chipshअगरt = cfi.cfiq->DevSize;

	अगर (cfi_पूर्णांकerleave_is_1(&cfi)) अणु
		;
	पूर्ण अन्यथा अगर (cfi_पूर्णांकerleave_is_2(&cfi)) अणु
		cfi.chipshअगरt++;
	पूर्ण अन्यथा अगर (cfi_पूर्णांकerleave_is_4((&cfi))) अणु
		cfi.chipshअगरt += 2;
	पूर्ण अन्यथा अगर (cfi_पूर्णांकerleave_is_8(&cfi)) अणु
		cfi.chipshअगरt += 3;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	cfi.numchips = 1;

	/*
	 * Allocate memory क्रम biपंचांगap of valid chips.
	 * Align biपंचांगap storage size to full byte.
	 */
	max_chips = map->size >> cfi.chipshअगरt;
	अगर (!max_chips) अणु
		prपूर्णांकk(KERN_WARNING "NOR chip too large to fit in mapping. Attempting to cope...\n");
		max_chips = 1;
	पूर्ण

	mapsize = माप(दीर्घ) * DIV_ROUND_UP(max_chips, BITS_PER_LONG);
	chip_map = kzalloc(mapsize, GFP_KERNEL);
	अगर (!chip_map) अणु
		kमुक्त(cfi.cfiq);
		वापस शून्य;
	पूर्ण

	set_bit(0, chip_map); /* Mark first chip valid */

	/*
	 * Now probe क्रम other chips, checking sensibly क्रम aliases जबतक
	 * we're at it. The new_chip probe above should have let the first
	 * chip in पढ़ो mode.
	 */

	क्रम (i = 1; i < max_chips; i++) अणु
		cp->probe_chip(map, i << cfi.chipshअगरt, chip_map, &cfi);
	पूर्ण

	/*
	 * Now allocate the space क्रम the काष्ठाures we need to वापस to
	 * our caller, and copy the appropriate data पूर्णांकo them.
	 */

	retcfi = kदो_स्मृति(काष्ठा_size(retcfi, chips, cfi.numchips), GFP_KERNEL);

	अगर (!retcfi) अणु
		kमुक्त(cfi.cfiq);
		kमुक्त(chip_map);
		वापस शून्य;
	पूर्ण

	स_नकल(retcfi, &cfi, माप(cfi));
	स_रखो(&retcfi->chips[0], 0, माप(काष्ठा flchip) * cfi.numchips);

	क्रम (i = 0, j = 0; (j < cfi.numchips) && (i < max_chips); i++) अणु
		अगर(test_bit(i, chip_map)) अणु
			काष्ठा flchip *pchip = &retcfi->chips[j++];

			pchip->start = (i << cfi.chipshअगरt);
			pchip->state = FL_READY;
			init_रुकोqueue_head(&pchip->wq);
			mutex_init(&pchip->mutex);
		पूर्ण
	पूर्ण

	kमुक्त(chip_map);
	वापस retcfi;
पूर्ण


अटल पूर्णांक genprobe_new_chip(काष्ठा map_info *map, काष्ठा chip_probe *cp,
			     काष्ठा cfi_निजी *cfi)
अणु
	पूर्णांक min_chips = (map_bankwidth(map)/4?:1); /* At most 4-bytes wide. */
	पूर्णांक max_chips = map_bankwidth(map); /* And minimum 1 */
	पूर्णांक nr_chips, type;

	क्रम (nr_chips = max_chips; nr_chips >= min_chips; nr_chips >>= 1) अणु

		अगर (!cfi_पूर्णांकerleave_supported(nr_chips))
		    जारी;

		cfi->पूर्णांकerleave = nr_chips;

		/* Minimum device size. Don't look क्रम one 8-bit device
		   in a 16-bit bus, etc. */
		type = map_bankwidth(map) / nr_chips;

		क्रम (; type <= CFI_DEVICETYPE_X32; type<<=1) अणु
			cfi->device_type = type;

			अगर (cp->probe_chip(map, 0, शून्य, cfi))
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

प्रकार काष्ठा mtd_info *cfi_cmdset_fn_t(काष्ठा map_info *, पूर्णांक);

बाह्य cfi_cmdset_fn_t cfi_cmdset_0001;
बाह्य cfi_cmdset_fn_t cfi_cmdset_0002;
बाह्य cfi_cmdset_fn_t cfi_cmdset_0020;

अटल अंतरभूत काष्ठा mtd_info *cfi_cmdset_unknown(काष्ठा map_info *map,
						  पूर्णांक primary)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	__u16 type = primary?cfi->cfiq->P_ID:cfi->cfiq->A_ID;
#अगर_घोषित CONFIG_MODULES
	cfi_cmdset_fn_t *probe_function;
	अक्षर *probename;

	probename = kaप्र_लिखो(GFP_KERNEL, "cfi_cmdset_%4.4X", type);
	अगर (!probename)
		वापस शून्य;

	probe_function = __symbol_get(probename);
	अगर (!probe_function) अणु
		request_module("cfi_cmdset_%4.4X", type);
		probe_function = __symbol_get(probename);
	पूर्ण
	kमुक्त(probename);

	अगर (probe_function) अणु
		काष्ठा mtd_info *mtd;

		mtd = (*probe_function)(map, primary);
		/* If it was happy, it'll have increased its own use count */
		symbol_put_addr(probe_function);
		वापस mtd;
	पूर्ण
#पूर्ण_अगर
	prपूर्णांकk(KERN_NOTICE "Support for command set %04X not present\n", type);

	वापस शून्य;
पूर्ण

अटल काष्ठा mtd_info *check_cmd_set(काष्ठा map_info *map, पूर्णांक primary)
अणु
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;
	__u16 type = primary?cfi->cfiq->P_ID:cfi->cfiq->A_ID;

	अगर (type == P_ID_NONE || type == P_ID_RESERVED)
		वापस शून्य;

	चयन(type)अणु
		/* We need these क्रम the !CONFIG_MODULES हाल,
		   because symbol_get() करोesn't work there */
#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
	हाल P_ID_INTEL_EXT:
	हाल P_ID_INTEL_STD:
	हाल P_ID_INTEL_PERFORMANCE:
		वापस cfi_cmdset_0001(map, primary);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_CFI_AMDSTD
	हाल P_ID_AMD_STD:
	हाल P_ID_SST_OLD:
	हाल P_ID_WINBOND:
		वापस cfi_cmdset_0002(map, primary);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_CFI_STAA
        हाल P_ID_ST_ADV:
		वापस cfi_cmdset_0020(map, primary);
#पूर्ण_अगर
	शेष:
		वापस cfi_cmdset_unknown(map, primary);
	पूर्ण
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("Helper routines for flash chip probe code");
