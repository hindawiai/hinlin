<शैली गुरु>
/*
 * MTD map driver क्रम flash on the DC21285 (the StrongARM-110 companion chip)
 *
 * (C) 2000  Nicolas Pitre <nico@fluxnic.net>
 *
 * This code is GPL
 */
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hardware/dec21285.h>
#समावेश <यंत्र/mach-types.h>


अटल काष्ठा mtd_info *dc21285_mtd;

#अगर_घोषित CONFIG_ARCH_NETWINDER
/*
 * This is really ugly, but it seams to be the only
 * realiable way to करो it, as the cpld state machine
 * is unpredictible. So we have a 25us penalty per
 * ग_लिखो access.
 */
अटल व्योम nw_en_ग_लिखो(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * we want to ग_लिखो a bit pattern XXX1 to Xilinx to enable
	 * the ग_लिखो gate, which will be खोलो क्रम about the next 2ms.
	 */
	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	nw_cpld_modअगरy(CPLD_FLASH_WR_ENABLE, CPLD_FLASH_WR_ENABLE);
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);

	/*
	 * let the ISA bus to catch on...
	 */
	udelay(25);
पूर्ण
#अन्यथा
#घोषणा nw_en_ग_लिखो() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल map_word dc21285_पढ़ो8(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	map_word val;
	val.x[0] = *(uपूर्णांक8_t*)(map->virt + ofs);
	वापस val;
पूर्ण

अटल map_word dc21285_पढ़ो16(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	map_word val;
	val.x[0] = *(uपूर्णांक16_t*)(map->virt + ofs);
	वापस val;
पूर्ण

अटल map_word dc21285_पढ़ो32(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	map_word val;
	val.x[0] = *(uपूर्णांक32_t*)(map->virt + ofs);
	वापस val;
पूर्ण

अटल व्योम dc21285_copy_from(काष्ठा map_info *map, व्योम *to, अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	स_नकल(to, (व्योम*)(map->virt + from), len);
पूर्ण

अटल व्योम dc21285_ग_लिखो8(काष्ठा map_info *map, स्थिर map_word d, अचिन्हित दीर्घ adr)
अणु
	अगर (machine_is_netwinder())
		nw_en_ग_लिखो();
	*CSR_ROMWRITEREG = adr & 3;
	adr &= ~3;
	*(uपूर्णांक8_t*)(map->virt + adr) = d.x[0];
पूर्ण

अटल व्योम dc21285_ग_लिखो16(काष्ठा map_info *map, स्थिर map_word d, अचिन्हित दीर्घ adr)
अणु
	अगर (machine_is_netwinder())
		nw_en_ग_लिखो();
	*CSR_ROMWRITEREG = adr & 3;
	adr &= ~3;
	*(uपूर्णांक16_t*)(map->virt + adr) = d.x[0];
पूर्ण

अटल व्योम dc21285_ग_लिखो32(काष्ठा map_info *map, स्थिर map_word d, अचिन्हित दीर्घ adr)
अणु
	अगर (machine_is_netwinder())
		nw_en_ग_लिखो();
	*(uपूर्णांक32_t*)(map->virt + adr) = d.x[0];
पूर्ण

अटल व्योम dc21285_copy_to_32(काष्ठा map_info *map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	जबतक (len > 0) अणु
		map_word d;
		d.x[0] = *((uपूर्णांक32_t*)from);
		dc21285_ग_लिखो32(map, d, to);
		from += 4;
		to += 4;
		len -= 4;
	पूर्ण
पूर्ण

अटल व्योम dc21285_copy_to_16(काष्ठा map_info *map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	जबतक (len > 0) अणु
		map_word d;
		d.x[0] = *((uपूर्णांक16_t*)from);
		dc21285_ग_लिखो16(map, d, to);
		from += 2;
		to += 2;
		len -= 2;
	पूर्ण
पूर्ण

अटल व्योम dc21285_copy_to_8(काष्ठा map_info *map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	map_word d;
	d.x[0] = *((uपूर्णांक8_t*)from);
	dc21285_ग_लिखो8(map, d, to);
	from++;
	to++;
	len--;
पूर्ण

अटल काष्ठा map_info dc21285_map = अणु
	.name = "DC21285 flash",
	.phys = NO_XIP,
	.size = 16*1024*1024,
	.copy_from = dc21285_copy_from,
पूर्ण;

/* Partition stuff */
अटल स्थिर अक्षर * स्थिर probes[] = अणु "RedBoot", "cmdlinepart", शून्य पूर्ण;

अटल पूर्णांक __init init_dc21285(व्योम)
अणु
	/* Determine bankwidth */
	चयन (*CSR_SA110_CNTL & (3<<14)) अणु
		हाल SA110_CNTL_ROMWIDTH_8:
			dc21285_map.bankwidth = 1;
			dc21285_map.पढ़ो = dc21285_पढ़ो8;
			dc21285_map.ग_लिखो = dc21285_ग_लिखो8;
			dc21285_map.copy_to = dc21285_copy_to_8;
			अवरोध;
		हाल SA110_CNTL_ROMWIDTH_16:
			dc21285_map.bankwidth = 2;
			dc21285_map.पढ़ो = dc21285_पढ़ो16;
			dc21285_map.ग_लिखो = dc21285_ग_लिखो16;
			dc21285_map.copy_to = dc21285_copy_to_16;
			अवरोध;
		हाल SA110_CNTL_ROMWIDTH_32:
			dc21285_map.bankwidth = 4;
			dc21285_map.पढ़ो = dc21285_पढ़ो32;
			dc21285_map.ग_लिखो = dc21285_ग_लिखो32;
			dc21285_map.copy_to = dc21285_copy_to_32;
			अवरोध;
		शेष:
			prपूर्णांकk (KERN_ERR "DC21285 flash: undefined bankwidth\n");
			वापस -ENXIO;
	पूर्ण
	prपूर्णांकk (KERN_NOTICE "DC21285 flash support (%d-bit bankwidth)\n",
		dc21285_map.bankwidth*8);

	/* Let's map the flash area */
	dc21285_map.virt = ioremap(DC21285_FLASH, 16*1024*1024);
	अगर (!dc21285_map.virt) अणु
		prपूर्णांकk("Failed to ioremap\n");
		वापस -EIO;
	पूर्ण

	अगर (machine_is_ebsa285()) अणु
		dc21285_mtd = करो_map_probe("cfi_probe", &dc21285_map);
	पूर्ण अन्यथा अणु
		dc21285_mtd = करो_map_probe("jedec_probe", &dc21285_map);
	पूर्ण

	अगर (!dc21285_mtd) अणु
		iounmap(dc21285_map.virt);
		वापस -ENXIO;
	पूर्ण

	dc21285_mtd->owner = THIS_MODULE;

	mtd_device_parse_रेजिस्टर(dc21285_mtd, probes, शून्य, शून्य, 0);

	अगर(machine_is_ebsa285()) अणु
		/*
		 * Flash timing is determined with bits 19-16 of the
		 * CSR_SA110_CNTL.  The value is the number of रुको cycles, or
		 * 0 क्रम 16 cycles (the शेष).  Cycles are 20 ns.
		 * Here we use 7 क्रम 140 ns flash chips.
		 */
		/* access समय */
		*CSR_SA110_CNTL = ((*CSR_SA110_CNTL & ~0x000f0000) | (7 << 16));
		/* burst समय */
		*CSR_SA110_CNTL = ((*CSR_SA110_CNTL & ~0x00f00000) | (7 << 20));
		/* tristate समय */
		*CSR_SA110_CNTL = ((*CSR_SA110_CNTL & ~0x0f000000) | (7 << 24));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_dc21285(व्योम)
अणु
	mtd_device_unरेजिस्टर(dc21285_mtd);
	map_destroy(dc21285_mtd);
	iounmap(dc21285_map.virt);
पूर्ण

module_init(init_dc21285);
module_निकास(cleanup_dc21285);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nicolas Pitre <nico@fluxnic.net>");
MODULE_DESCRIPTION("MTD map driver for DC21285 boards");
