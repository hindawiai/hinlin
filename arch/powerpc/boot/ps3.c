<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 bootwrapper support.
 *
 *  Copyright (C) 2007 Sony Computer Entertainment Inc.
 *  Copyright 2007 Sony Corp.
 */

#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "elf.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "page.h"
#समावेश "ops.h"

बाह्य पूर्णांक lv1_panic(u64 in_1);
बाह्य पूर्णांक lv1_get_logical_partition_id(u64 *out_1);
बाह्य पूर्णांक lv1_get_logical_ppe_id(u64 *out_1);
बाह्य पूर्णांक lv1_get_repository_node_value(u64 in_1, u64 in_2, u64 in_3,
	u64 in_4, u64 in_5, u64 *out_1, u64 *out_2);

BSS_STACK(4096);

/* A buffer that may be edited by tools operating on a zImage binary so as to
 * edit the command line passed to vmlinux (by setting /chosen/bootargs).
 * The buffer is put in it's own section so that tools may locate it easier.
 */

अटल अक्षर cmdline[BOOT_COMMAND_LINE_SIZE]
	__attribute__((__section__("__builtin_cmdline")));

अटल व्योम prep_cmdline(व्योम *chosen)
अणु
	अगर (cmdline[0] == '\0')
		getprop(chosen, "bootargs", cmdline, BOOT_COMMAND_LINE_SIZE-1);
	अन्यथा
		setprop_str(chosen, "bootargs", cmdline);

	म_लिखो("cmdline: '%s'\n", cmdline);
पूर्ण

अटल व्योम ps3_console_ग_लिखो(स्थिर अक्षर *buf, पूर्णांक len)
अणु
पूर्ण

अटल व्योम ps3_निकास(व्योम)
अणु
	म_लिखो("ps3_exit\n");

	/* lv1_panic will shutकरोwn the lpar. */

	lv1_panic(0); /* zero = करो not reboot */
	जबतक (1);
पूर्ण

अटल पूर्णांक ps3_repository_पढ़ो_rm_size(u64 *rm_size)
अणु
	पूर्णांक result;
	u64 lpar_id;
	u64 ppe_id;
	u64 v2;

	result = lv1_get_logical_partition_id(&lpar_id);

	अगर (result)
		वापस -1;

	result = lv1_get_logical_ppe_id(&ppe_id);

	अगर (result)
		वापस -1;

	/*
	 * n1: 0000000062690000 : ....bi..
	 * n2: 7075000000000000 : pu......
	 * n3: 0000000000000001 : ........
	 * n4: 726d5f73697a6500 : rm_size.
	*/

	result = lv1_get_repository_node_value(lpar_id, 0x0000000062690000ULL,
		0x7075000000000000ULL, ppe_id, 0x726d5f73697a6500ULL, rm_size,
		&v2);

	म_लिखो("%s:%d: ppe_id  %lu \n", __func__, __LINE__,
		(अचिन्हित दीर्घ)ppe_id);
	म_लिखो("%s:%d: lpar_id %lu \n", __func__, __LINE__,
		(अचिन्हित दीर्घ)lpar_id);
	म_लिखो("%s:%d: rm_size %llxh \n", __func__, __LINE__, *rm_size);

	वापस result ? -1 : 0;
पूर्ण

व्योम ps3_copy_vectors(व्योम)
अणु
	बाह्य अक्षर __प्रणाली_reset_kernel[];

	स_नकल((व्योम *)0x100, __प्रणाली_reset_kernel, 512);
	flush_cache((व्योम *)0x100, 512);
पूर्ण

व्योम platक्रमm_init(व्योम)
अणु
	स्थिर u32 heapsize = 0x1000000 - (u32)_end; /* 16MiB */
	व्योम *chosen;
	अचिन्हित दीर्घ ft_addr;
	u64 rm_size;

	console_ops.ग_लिखो = ps3_console_ग_लिखो;
	platक्रमm_ops.निकास = ps3_निकास;

	म_लिखो("\n-- PS3 bootwrapper --\n");

	simple_alloc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_start);

	chosen = finddevice("/chosen");

	ps3_repository_पढ़ो_rm_size(&rm_size);
	dt_fixup_memory(0, rm_size);

	अगर (&_initrd_end > &_initrd_start) अणु
		setprop_val(chosen, "linux,initrd-start", (u32)(_initrd_start));
		setprop_val(chosen, "linux,initrd-end", (u32)(_initrd_end));
	पूर्ण

	prep_cmdline(chosen);

	ft_addr = dt_ops.finalize();

	ps3_copy_vectors();

	म_लिखो(" flat tree at 0x%lx\n\r", ft_addr);

	((kernel_entry_t)0)(ft_addr, 0, शून्य);

	ps3_निकास();
पूर्ण
