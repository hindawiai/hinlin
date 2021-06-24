<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * memconsole-x86-legacy.c
 *
 * EBDA specअगरic parts of the memory based BIOS console.
 *
 * Copyright 2017 Google Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/dmi.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/bios_ebda.h>
#समावेश <linux/acpi.h>

#समावेश "memconsole.h"

#घोषणा BIOS_MEMCONSOLE_V1_MAGIC	0xDEADBABE
#घोषणा BIOS_MEMCONSOLE_V2_MAGIC	(('M')|('C'<<8)|('O'<<16)|('N'<<24))

काष्ठा biosmemcon_ebda अणु
	u32 signature;
	जोड़ अणु
		काष्ठा अणु
			u8  enabled;
			u32 buffer_addr;
			u16 start;
			u16 end;
			u16 num_अक्षरs;
			u8  wrapped;
		पूर्ण __packed v1;
		काष्ठा अणु
			u32 buffer_addr;
			/* Misकरोcumented as number of pages! */
			u16 num_bytes;
			u16 start;
			u16 end;
		पूर्ण __packed v2;
	पूर्ण;
पूर्ण __packed;

अटल अक्षर *memconsole_baseaddr;
अटल माप_प्रकार memconsole_length;

अटल sमाप_प्रकार memconsole_पढ़ो(अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	वापस memory_पढ़ो_from_buffer(buf, count, &pos, memconsole_baseaddr,
				       memconsole_length);
पूर्ण

अटल व्योम found_v1_header(काष्ठा biosmemcon_ebda *hdr)
अणु
	pr_info("memconsole: BIOS console v1 EBDA structure found at %p\n",
		hdr);
	pr_info("memconsole: BIOS console buffer at 0x%.8x, start = %d, end = %d, num = %d\n",
		hdr->v1.buffer_addr, hdr->v1.start,
		hdr->v1.end, hdr->v1.num_अक्षरs);

	memconsole_baseaddr = phys_to_virt(hdr->v1.buffer_addr);
	memconsole_length = hdr->v1.num_अक्षरs;
	memconsole_setup(memconsole_पढ़ो);
पूर्ण

अटल व्योम found_v2_header(काष्ठा biosmemcon_ebda *hdr)
अणु
	pr_info("memconsole: BIOS console v2 EBDA structure found at %p\n",
		hdr);
	pr_info("memconsole: BIOS console buffer at 0x%.8x, start = %d, end = %d, num_bytes = %d\n",
		hdr->v2.buffer_addr, hdr->v2.start,
		hdr->v2.end, hdr->v2.num_bytes);

	memconsole_baseaddr = phys_to_virt(hdr->v2.buffer_addr + hdr->v2.start);
	memconsole_length = hdr->v2.end - hdr->v2.start;
	memconsole_setup(memconsole_पढ़ो);
पूर्ण

/*
 * Search through the EBDA क्रम the BIOS Memory Console, and
 * set the global variables to poपूर्णांक to it.  Return true अगर found.
 */
अटल bool memconsole_ebda_init(व्योम)
अणु
	अचिन्हित पूर्णांक address;
	माप_प्रकार length, cur;

	address = get_bios_ebda();
	अगर (!address) अणु
		pr_info("memconsole: BIOS EBDA non-existent.\n");
		वापस false;
	पूर्ण

	/* EBDA length is byte 0 of EBDA (in KB) */
	length = *(u8 *)phys_to_virt(address);
	length <<= 10; /* convert to bytes */

	/*
	 * Search through EBDA क्रम BIOS memory console काष्ठाure
	 * note: signature is not necessarily dword-aligned
	 */
	क्रम (cur = 0; cur < length; cur++) अणु
		काष्ठा biosmemcon_ebda *hdr = phys_to_virt(address + cur);

		/* memconsole v1 */
		अगर (hdr->signature == BIOS_MEMCONSOLE_V1_MAGIC) अणु
			found_v1_header(hdr);
			वापस true;
		पूर्ण

		/* memconsole v2 */
		अगर (hdr->signature == BIOS_MEMCONSOLE_V2_MAGIC) अणु
			found_v2_header(hdr);
			वापस true;
		पूर्ण
	पूर्ण

	pr_info("memconsole: BIOS console EBDA structure not found!\n");
	वापस false;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id memconsole_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Google Board",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Google, Inc."),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, memconsole_dmi_table);

अटल bool __init memconsole_find(व्योम)
अणु
	अगर (!dmi_check_प्रणाली(memconsole_dmi_table))
		वापस false;

	वापस memconsole_ebda_init();
पूर्ण

अटल पूर्णांक __init memconsole_x86_init(व्योम)
अणु
	अगर (!memconsole_find())
		वापस -ENODEV;

	वापस memconsole_sysfs_init();
पूर्ण

अटल व्योम __निकास memconsole_x86_निकास(व्योम)
अणु
	memconsole_निकास();
पूर्ण

module_init(memconsole_x86_init);
module_निकास(memconsole_x86_निकास);

MODULE_AUTHOR("Google, Inc.");
MODULE_LICENSE("GPL");
