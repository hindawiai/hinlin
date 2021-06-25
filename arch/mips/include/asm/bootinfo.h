<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 2003 by Ralf Baechle
 * Copyright (C) 1995, 1996 Andreas Busse
 * Copyright (C) 1995, 1996 Stoned Elipot
 * Copyright (C) 1995, 1996 Paul M. Antoine.
 * Copyright (C) 2009       Zhang Le
 */
#अगर_अघोषित _ASM_BOOTINFO_H
#घोषणा _ASM_BOOTINFO_H

#समावेश <linux/types.h>
#समावेश <यंत्र/setup.h>

/*
 * The MACH_ IDs are sort of equivalent to PCI product IDs.  As such the
 * numbers करो not necessarily reflect technical relations or similarities
 * between प्रणालीs.
 */

/*
 * Valid machtype values क्रम group unknown
 */
#घोषणा  MACH_UNKNOWN		0	/* whatever...			*/

/*
 * Valid machtype क्रम group DEC
 */
#घोषणा  MACH_DSUNKNOWN		0
#घोषणा  MACH_DS23100		1	/* DECstation 2100 or 3100	*/
#घोषणा  MACH_DS5100		2	/* DECप्रणाली 5100		*/
#घोषणा  MACH_DS5000_200	3	/* DECstation 5000/200		*/
#घोषणा  MACH_DS5000_1XX	4	/* DECstation 5000/120, 125, 133, 150 */
#घोषणा  MACH_DS5000_XX		5	/* DECstation 5000/20, 25, 33, 50 */
#घोषणा  MACH_DS5000_2X0	6	/* DECstation 5000/240, 260	*/
#घोषणा  MACH_DS5400		7	/* DECप्रणाली 5400		*/
#घोषणा  MACH_DS5500		8	/* DECप्रणाली 5500		*/
#घोषणा  MACH_DS5800		9	/* DECप्रणाली 5800		*/
#घोषणा  MACH_DS5900		10	/* DECप्रणाली 5900		*/

/*
 * Valid machtype क्रम group Mikrotik
 */
#घोषणा MACH_MIKROTIK_RB532	0	/* Mikrotik RouterBoard 532	*/
#घोषणा MACH_MIKROTIK_RB532A	1	/* Mikrotik RouterBoard 532A	*/

/*
 * Valid machtype क्रम Loongson family
 */
क्रमागत loongson2ef_machine_type अणु
	MACH_LOONGSON_UNKNOWN,
	MACH_LEMOTE_FL2E,
	MACH_LEMOTE_FL2F,
	MACH_LEMOTE_ML2F7,
	MACH_LEMOTE_YL2F89,
	MACH_DEXXON_GDIUM2F10,
	MACH_LEMOTE_NAS,
	MACH_LEMOTE_LL2F,
	MACH_LOONGSON_END
पूर्ण;

/*
 * Valid machtype क्रम group INGENIC
 */
क्रमागत ingenic_machine_type अणु
	MACH_INGENIC_UNKNOWN,
	MACH_INGENIC_JZ4720,
	MACH_INGENIC_JZ4725,
	MACH_INGENIC_JZ4725B,
	MACH_INGENIC_JZ4730,
	MACH_INGENIC_JZ4740,
	MACH_INGENIC_JZ4750,
	MACH_INGENIC_JZ4755,
	MACH_INGENIC_JZ4760,
	MACH_INGENIC_JZ4770,
	MACH_INGENIC_JZ4775,
	MACH_INGENIC_JZ4780,
	MACH_INGENIC_X1000,
	MACH_INGENIC_X1000E,
	MACH_INGENIC_X1830,
	MACH_INGENIC_X2000,
	MACH_INGENIC_X2000E,
पूर्ण;

बाह्य अक्षर *प्रणाली_type;
स्थिर अक्षर *get_प्रणाली_type(व्योम);

बाह्य अचिन्हित दीर्घ mips_machtype;

बाह्य व्योम detect_memory_region(phys_addr_t start, phys_addr_t sz_min,  phys_addr_t sz_max);

बाह्य व्योम prom_init(व्योम);
बाह्य व्योम prom_मुक्त_prom_memory(व्योम);
बाह्य व्योम prom_cleanup(व्योम);

बाह्य व्योम मुक्त_init_pages(स्थिर अक्षर *what,
			    अचिन्हित दीर्घ begin, अचिन्हित दीर्घ end);

बाह्य व्योम (*मुक्त_init_pages_eva)(व्योम *begin, व्योम *end);

/*
 * Initial kernel command line, usually setup by prom_init()
 */
बाह्य अक्षर arcs_cmdline[COMMAND_LINE_SIZE];

/*
 * Registers a0, a1, a2 and a3 as passed to the kernel entry by firmware
 */
बाह्य अचिन्हित दीर्घ fw_arg0, fw_arg1, fw_arg2, fw_arg3;

#अगर_घोषित CONFIG_USE_OF
#समावेश <linux/libfdt.h>
#समावेश <linux/of_fdt.h>

बाह्य अक्षर __appended_dtb[];

अटल अंतरभूत व्योम *get_fdt(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_MIPS_RAW_APPENDED_DTB) ||
	    IS_ENABLED(CONFIG_MIPS_ELF_APPENDED_DTB))
		अगर (fdt_magic(&__appended_dtb) == FDT_MAGIC)
			वापस &__appended_dtb;

	अगर (fw_arg0 == -2) /* UHI पूर्णांकerface */
		वापस (व्योम *)fw_arg1;

	अगर (IS_ENABLED(CONFIG_BUILTIN_DTB))
		अगर (&__dtb_start != &__dtb_end)
			वापस &__dtb_start;

	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/*
 * Platक्रमm memory detection hook called by arch_mem_init()
 */
बाह्य व्योम plat_mem_setup(व्योम);

#अगर_घोषित CONFIG_SWIOTLB
/*
 * Optional platक्रमm hook to call swiotlb_setup().
 */
बाह्य व्योम plat_swiotlb_setup(व्योम);

#अन्यथा

अटल अंतरभूत व्योम plat_swiotlb_setup(व्योम) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_SWIOTLB */

#अगर_घोषित CONFIG_USE_OF
/**
 * plat_get_fdt() - Return a poपूर्णांकer to the platक्रमm's device tree blob
 *
 * This function provides a platक्रमm independent API to get a poपूर्णांकer to the
 * flattened device tree blob. The पूर्णांकerface between bootloader and kernel
 * is not consistent across platक्रमms so it is necessary to provide this
 * API such that common startup code can locate the FDT.
 *
 * This is used by the KASLR code to get command line arguments and अक्रमom
 * seed from the device tree. Any platक्रमm wishing to use KASLR should
 * provide this API and select SYS_SUPPORTS_RELOCATABLE.
 *
 * Return: Poपूर्णांकer to the flattened device tree blob.
 */
बाह्य व्योम *plat_get_fdt(व्योम);

#अगर_घोषित CONFIG_RELOCATABLE

/**
 * plat_fdt_relocated() - Update platक्रमm's inक्रमmation about relocated dtb
 *
 * This function provides a platक्रमm-independent API to set platक्रमm's
 * inक्रमmation about relocated DTB अगर it needs to be moved due to kernel
 * relocation occurring at boot.
 */
व्योम plat_fdt_relocated(व्योम *new_location);

#पूर्ण_अगर /* CONFIG_RELOCATABLE */
#पूर्ण_अगर /* CONFIG_USE_OF */

#पूर्ण_अगर /* _ASM_BOOTINFO_H */
