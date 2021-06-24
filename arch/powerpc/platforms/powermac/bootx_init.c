<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Early boot support code क्रम BootX bootloader
 *
 *  Copyright (C) 2005 Ben. Herrenschmidt (benh@kernel.crashing.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <generated/utsrelease.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/bootx.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/setup.h>

#अघोषित DEBUG
#घोषणा SET_BOOT_BAT

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) करो अणु bootx_म_लिखो(fmt); पूर्ण जबतक(0)
#अन्यथा
#घोषणा DBG(fmt...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

बाह्य व्योम __start(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5);

अटल अचिन्हित दीर्घ __initdata bootx_dt_strbase;
अटल अचिन्हित दीर्घ __initdata bootx_dt_strend;
अटल अचिन्हित दीर्घ __initdata bootx_node_chosen;
अटल boot_infos_t * __initdata bootx_info;
अटल अक्षर __initdata bootx_disp_path[256];

/* Is boot-info compatible ? */
#घोषणा BOOT_INFO_IS_COMPATIBLE(bi) \
	((bi)->compatible_version <= BOOT_INFO_VERSION)
#घोषणा BOOT_INFO_IS_V2_COMPATIBLE(bi)	((bi)->version >= 2)
#घोषणा BOOT_INFO_IS_V4_COMPATIBLE(bi)	((bi)->version >= 4)

#अगर_घोषित CONFIG_BOOTX_TEXT
अटल व्योम __init bootx_म_लिखो(स्थिर अक्षर *क्रमmat, ...)
अणु
	स्थिर अक्षर *p, *q, *s;
	बहु_सूची args;
	अचिन्हित दीर्घ v;

	बहु_शुरू(args, क्रमmat);
	क्रम (p = क्रमmat; *p != 0; p = q) अणु
		क्रम (q = p; *q != 0 && *q != '\n' && *q != '%'; ++q)
			;
		अगर (q > p)
			btext_drawtext(p, q - p);
		अगर (*q == 0)
			अवरोध;
		अगर (*q == '\n') अणु
			++q;
			btext_flushline();
			btext_drawstring("\r\n");
			btext_flushline();
			जारी;
		पूर्ण
		++q;
		अगर (*q == 0)
			अवरोध;
		चयन (*q) अणु
		हाल 's':
			++q;
			s = बहु_तर्क(args, स्थिर अक्षर *);
			अगर (s == शून्य)
				s = "<NULL>";
			btext_drawstring(s);
			अवरोध;
		हाल 'x':
			++q;
			v = बहु_तर्क(args, अचिन्हित दीर्घ);
			btext_drawhex(v);
			अवरोध;
		पूर्ण
	पूर्ण
	बहु_पूर्ण(args);
पूर्ण
#अन्यथा /* CONFIG_BOOTX_TEXT */
अटल व्योम __init bootx_म_लिखो(स्थिर अक्षर *क्रमmat, ...) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_BOOTX_TEXT */

अटल व्योम * __init bootx_early_getprop(अचिन्हित दीर्घ base,
					 अचिन्हित दीर्घ node,
					 अक्षर *prop)
अणु
	काष्ठा bootx_dt_node *np = (काष्ठा bootx_dt_node *)(base + node);
	u32 *ppp = &np->properties;

	जबतक(*ppp) अणु
		काष्ठा bootx_dt_prop *pp =
			(काष्ठा bootx_dt_prop *)(base + *ppp);

		अगर (म_भेद((अक्षर *)((अचिन्हित दीर्घ)pp->name + base),
			   prop) == 0) अणु
			वापस (व्योम *)((अचिन्हित दीर्घ)pp->value + base);
		पूर्ण
		ppp = &pp->next;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा dt_push_token(token, mem) \
	करो अणु \
		*(mem) = ALIGN(*(mem),4); \
		*((u32 *)*(mem)) = token; \
		*(mem) += 4; \
	पूर्ण जबतक(0)

अटल अचिन्हित दीर्घ __init bootx_dt_find_string(अक्षर *str)
अणु
	अक्षर *s, *os;

	s = os = (अक्षर *)bootx_dt_strbase;
	s += 4;
	जबतक (s <  (अक्षर *)bootx_dt_strend) अणु
		अगर (म_भेद(s, str) == 0)
			वापस s - os;
		s += म_माप(s) + 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init bootx_dt_add_prop(अक्षर *name, व्योम *data, पूर्णांक size,
				  अचिन्हित दीर्घ *mem_end)
अणु
	अचिन्हित दीर्घ soff = bootx_dt_find_string(name);
	अगर (data == शून्य)
		size = 0;
	अगर (soff == 0) अणु
		bootx_म_लिखो("WARNING: Can't find string index for <%s>\n",
			     name);
		वापस;
	पूर्ण
	अगर (size > 0x20000) अणु
		bootx_म_लिखो("WARNING: ignoring large property ");
		bootx_म_लिखो("%s length 0x%x\n", name, size);
		वापस;
	पूर्ण
	dt_push_token(OF_DT_PROP, mem_end);
	dt_push_token(size, mem_end);
	dt_push_token(soff, mem_end);

	/* push property content */
	अगर (size && data) अणु
		स_नकल((व्योम *)*mem_end, data, size);
		*mem_end = ALIGN(*mem_end + size, 4);
	पूर्ण
पूर्ण

अटल व्योम __init bootx_add_chosen_props(अचिन्हित दीर्घ base,
					  अचिन्हित दीर्घ *mem_end)
अणु
	u32 val;

	bootx_dt_add_prop("linux,bootx", शून्य, 0, mem_end);

	अगर (bootx_info->kernelParamsOffset) अणु
		अक्षर *args = (अक्षर *)((अचिन्हित दीर्घ)bootx_info) +
			bootx_info->kernelParamsOffset;
		bootx_dt_add_prop("bootargs", args, म_माप(args) + 1, mem_end);
	पूर्ण
	अगर (bootx_info->ramDisk) अणु
		val = ((अचिन्हित दीर्घ)bootx_info) + bootx_info->ramDisk;
		bootx_dt_add_prop("linux,initrd-start", &val, 4, mem_end);
		val += bootx_info->ramDiskSize;
		bootx_dt_add_prop("linux,initrd-end", &val, 4, mem_end);
	पूर्ण
	अगर (म_माप(bootx_disp_path))
		bootx_dt_add_prop("linux,stdout-path", bootx_disp_path,
				  म_माप(bootx_disp_path) + 1, mem_end);
पूर्ण

अटल व्योम __init bootx_add_display_props(अचिन्हित दीर्घ base,
					   अचिन्हित दीर्घ *mem_end,
					   पूर्णांक has_real_node)
अणु
	boot_infos_t *bi = bootx_info;
	u32 पंचांगp;

	अगर (has_real_node) अणु
		bootx_dt_add_prop("linux,boot-display", शून्य, 0, mem_end);
		bootx_dt_add_prop("linux,opened", शून्य, 0, mem_end);
	पूर्ण अन्यथा
		bootx_dt_add_prop("linux,bootx-noscreen", शून्य, 0, mem_end);

	पंचांगp = bi->dispDeviceDepth;
	bootx_dt_add_prop("linux,bootx-depth", &पंचांगp, 4, mem_end);
	पंचांगp = bi->dispDeviceRect[2] - bi->dispDeviceRect[0];
	bootx_dt_add_prop("linux,bootx-width", &पंचांगp, 4, mem_end);
	पंचांगp = bi->dispDeviceRect[3] - bi->dispDeviceRect[1];
	bootx_dt_add_prop("linux,bootx-height", &पंचांगp, 4, mem_end);
	पंचांगp = bi->dispDeviceRowBytes;
	bootx_dt_add_prop("linux,bootx-linebytes", &पंचांगp, 4, mem_end);
	पंचांगp = (u32)bi->dispDeviceBase;
	अगर (पंचांगp == 0)
		पंचांगp = (u32)bi->logicalDisplayBase;
	पंचांगp += bi->dispDeviceRect[1] * bi->dispDeviceRowBytes;
	पंचांगp += bi->dispDeviceRect[0] * ((bi->dispDeviceDepth + 7) / 8);
	bootx_dt_add_prop("linux,bootx-addr", &पंचांगp, 4, mem_end);
पूर्ण

अटल व्योम __init bootx_dt_add_string(अक्षर *s, अचिन्हित दीर्घ *mem_end)
अणु
	अचिन्हित पूर्णांक l = म_माप(s) + 1;
	स_नकल((व्योम *)*mem_end, s, l);
	bootx_dt_strend = *mem_end = *mem_end + l;
पूर्ण

अटल व्योम __init bootx_scan_dt_build_strings(अचिन्हित दीर्घ base,
					       अचिन्हित दीर्घ node,
					       अचिन्हित दीर्घ *mem_end)
अणु
	काष्ठा bootx_dt_node *np = (काष्ठा bootx_dt_node *)(base + node);
	u32 *cpp, *ppp = &np->properties;
	अचिन्हित दीर्घ soff;
	अक्षर *namep;

	/* Keep refs to known nodes */
	namep = np->full_name ? (अक्षर *)(base + np->full_name) : शून्य;
       	अगर (namep == शून्य) अणु
		bootx_म_लिखो("Node without a full name !\n");
		namep = "";
	पूर्ण
	DBG("* strings: %s\n", namep);

	अगर (!म_भेद(namep, "/chosen")) अणु
		DBG(" detected /chosen ! adding properties names !\n");
		bootx_dt_add_string("linux,bootx", mem_end);
		bootx_dt_add_string("linux,stdout-path", mem_end);
		bootx_dt_add_string("linux,initrd-start", mem_end);
		bootx_dt_add_string("linux,initrd-end", mem_end);
		bootx_dt_add_string("bootargs", mem_end);
		bootx_node_chosen = node;
	पूर्ण
	अगर (node == bootx_info->dispDeviceRegEntryOffset) अणु
		DBG(" detected display ! adding properties names !\n");
		bootx_dt_add_string("linux,boot-display", mem_end);
		bootx_dt_add_string("linux,opened", mem_end);
		strlcpy(bootx_disp_path, namep, माप(bootx_disp_path));
	पूर्ण

	/* get and store all property names */
	जबतक (*ppp) अणु
		काष्ठा bootx_dt_prop *pp =
			(काष्ठा bootx_dt_prop *)(base + *ppp);

		namep = pp->name ? (अक्षर *)(base + pp->name) : शून्य;
 		अगर (namep == शून्य || म_भेद(namep, "name") == 0)
 			जाओ next;
		/* get/create string entry */
		soff = bootx_dt_find_string(namep);
		अगर (soff == 0)
			bootx_dt_add_string(namep, mem_end);
	next:
		ppp = &pp->next;
	पूर्ण

	/* करो all our children */
	cpp = &np->child;
	जबतक(*cpp) अणु
		np = (काष्ठा bootx_dt_node *)(base + *cpp);
		bootx_scan_dt_build_strings(base, *cpp, mem_end);
		cpp = &np->sibling;
	पूर्ण
पूर्ण

अटल व्योम __init bootx_scan_dt_build_काष्ठा(अचिन्हित दीर्घ base,
					      अचिन्हित दीर्घ node,
					      अचिन्हित दीर्घ *mem_end)
अणु
	काष्ठा bootx_dt_node *np = (काष्ठा bootx_dt_node *)(base + node);
	u32 *cpp, *ppp = &np->properties;
	अक्षर *namep, *p, *ep, *lp;
	पूर्णांक l;

	dt_push_token(OF_DT_BEGIN_NODE, mem_end);

	/* get the node's full name */
	namep = np->full_name ? (अक्षर *)(base + np->full_name) : शून्य;
	अगर (namep == शून्य)
		namep = "";
	l = म_माप(namep);

	DBG("* struct: %s\n", namep);

	/* Fixup an Apple bug where they have bogus \0 अक्षरs in the
	 * middle of the path in some properties, and extract
	 * the unit name (everything after the last '/').
	 */
	स_नकल((व्योम *)*mem_end, namep, l + 1);
	namep = (अक्षर *)*mem_end;
	क्रम (lp = p = namep, ep = namep + l; p < ep; p++) अणु
		अगर (*p == '/')
			lp = namep;
		अन्यथा अगर (*p != 0)
			*lp++ = *p;
	पूर्ण
	*lp = 0;
	*mem_end = ALIGN((अचिन्हित दीर्घ)lp + 1, 4);

	/* get and store all properties */
	जबतक (*ppp) अणु
		काष्ठा bootx_dt_prop *pp =
			(काष्ठा bootx_dt_prop *)(base + *ppp);

		namep = pp->name ? (अक्षर *)(base + pp->name) : शून्य;
		/* Skip "name" */
 		अगर (namep == शून्य || !म_भेद(namep, "name"))
 			जाओ next;
		/* Skip "bootargs" in /chosen too as we replace it */
		अगर (node == bootx_node_chosen && !म_भेद(namep, "bootargs"))
			जाओ next;

		/* push property head */
		bootx_dt_add_prop(namep,
				  pp->value ? (व्योम *)(base + pp->value): शून्य,
				  pp->length, mem_end);
	next:
		ppp = &pp->next;
	पूर्ण

	अगर (node == bootx_node_chosen) अणु
		bootx_add_chosen_props(base, mem_end);
		अगर (bootx_info->dispDeviceRegEntryOffset == 0)
			bootx_add_display_props(base, mem_end, 0);
	पूर्ण
	अन्यथा अगर (node == bootx_info->dispDeviceRegEntryOffset)
		bootx_add_display_props(base, mem_end, 1);

	/* करो all our children */
	cpp = &np->child;
	जबतक(*cpp) अणु
		np = (काष्ठा bootx_dt_node *)(base + *cpp);
		bootx_scan_dt_build_काष्ठा(base, *cpp, mem_end);
		cpp = &np->sibling;
	पूर्ण

	dt_push_token(OF_DT_END_NODE, mem_end);
पूर्ण

अटल अचिन्हित दीर्घ __init bootx_flatten_dt(अचिन्हित दीर्घ start)
अणु
	boot_infos_t *bi = bootx_info;
	अचिन्हित दीर्घ mem_start, mem_end;
	काष्ठा boot_param_header *hdr;
	अचिन्हित दीर्घ base;
	u64 *rsvmap;

	/* Start using memory after the big blob passed by BootX, get
	 * some space क्रम the header
	 */
	mem_start = mem_end = ALIGN(((अचिन्हित दीर्घ)bi) + start, 4);
	DBG("Boot params header at: %x\n", mem_start);
	hdr = (काष्ठा boot_param_header *)mem_start;
	mem_end += माप(काष्ठा boot_param_header);
	rsvmap = (u64 *)(ALIGN(mem_end, 8));
	hdr->off_mem_rsvmap = ((अचिन्हित दीर्घ)rsvmap) - mem_start;
	mem_end = ((अचिन्हित दीर्घ)rsvmap) + 8 * माप(u64);

	/* Get base of tree */
	base = ((अचिन्हित दीर्घ)bi) + bi->deviceTreeOffset;

	/* Build string array */
	DBG("Building string array at: %x\n", mem_end);
	DBG("Device Tree Base=%x\n", base);
	bootx_dt_strbase = mem_end;
	mem_end += 4;
	bootx_dt_strend = mem_end;
	bootx_scan_dt_build_strings(base, 4, &mem_end);
	/* Add some strings */
	bootx_dt_add_string("linux,bootx-noscreen", &mem_end);
	bootx_dt_add_string("linux,bootx-depth", &mem_end);
	bootx_dt_add_string("linux,bootx-width", &mem_end);
	bootx_dt_add_string("linux,bootx-height", &mem_end);
	bootx_dt_add_string("linux,bootx-linebytes", &mem_end);
	bootx_dt_add_string("linux,bootx-addr", &mem_end);
	/* Wrap up strings */
	hdr->off_dt_strings = bootx_dt_strbase - mem_start;
	hdr->dt_strings_size = bootx_dt_strend - bootx_dt_strbase;

	/* Build काष्ठाure */
	mem_end = ALIGN(mem_end, 16);
	DBG("Building device tree structure at: %x\n", mem_end);
	hdr->off_dt_काष्ठा = mem_end - mem_start;
	bootx_scan_dt_build_काष्ठा(base, 4, &mem_end);
	dt_push_token(OF_DT_END, &mem_end);

	/* Finish header */
	hdr->boot_cpuid_phys = 0;
	hdr->magic = OF_DT_HEADER;
	hdr->totalsize = mem_end - mem_start;
	hdr->version = OF_DT_VERSION;
	/* Version 16 is not backward compatible */
	hdr->last_comp_version = 0x10;

	/* Reserve the whole thing and copy the reserve map in, we
	 * also bump mem_reserve_cnt to cause further reservations to
	 * fail since it's too late.
	 */
	mem_end = ALIGN(mem_end, PAGE_SIZE);
	DBG("End of boot params: %x\n", mem_end);
	rsvmap[0] = mem_start;
	rsvmap[1] = mem_end;
	अगर (bootx_info->ramDisk) अणु
		rsvmap[2] = ((अचिन्हित दीर्घ)bootx_info) + bootx_info->ramDisk;
		rsvmap[3] = rsvmap[2] + bootx_info->ramDiskSize;
		rsvmap[4] = 0;
		rsvmap[5] = 0;
	पूर्ण अन्यथा अणु
		rsvmap[2] = 0;
		rsvmap[3] = 0;
	पूर्ण

	वापस (अचिन्हित दीर्घ)hdr;
पूर्ण


#अगर_घोषित CONFIG_BOOTX_TEXT
अटल व्योम __init btext_welcome(boot_infos_t *bi)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ pvr;

	bootx_म_लिखो("Welcome to Linux, kernel " UTS_RELEASE "\n");
	bootx_म_लिखो("\nlinked at        : 0x%x", KERNELBASE);
	bootx_म_लिखो("\nframe buffer at  : 0x%x", bi->dispDeviceBase);
	bootx_म_लिखो(" (phys), 0x%x", bi->logicalDisplayBase);
	bootx_म_लिखो(" (log)");
	bootx_म_लिखो("\nklimit           : 0x%x",(अचिन्हित दीर्घ)klimit);
	bootx_म_लिखो("\nboot_info at     : 0x%x", bi);
	__यंत्र__ __अस्थिर__ ("mfmsr %0" : "=r" (flags));
	bootx_म_लिखो("\nMSR              : 0x%x", flags);
	__यंत्र__ __अस्थिर__ ("mfspr %0, 287" : "=r" (pvr));
	bootx_म_लिखो("\nPVR              : 0x%x", pvr);
	pvr >>= 16;
	अगर (pvr > 1) अणु
	    __यंत्र__ __अस्थिर__ ("mfspr %0, 1008" : "=r" (flags));
	    bootx_म_लिखो("\nHID0             : 0x%x", flags);
	पूर्ण
	अगर (pvr == 8 || pvr == 12 || pvr == 0x800c) अणु
	    __यंत्र__ __अस्थिर__ ("mfspr %0, 1019" : "=r" (flags));
	    bootx_म_लिखो("\nICTC             : 0x%x", flags);
	पूर्ण
#अगर_घोषित DEBUG
	bootx_म_लिखो("\n\n");
	bootx_म_लिखो("bi->deviceTreeOffset   : 0x%x\n",
		     bi->deviceTreeOffset);
	bootx_म_लिखो("bi->deviceTreeSize     : 0x%x\n",
		     bi->deviceTreeSize);
#पूर्ण_अगर
	bootx_म_लिखो("\n\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_BOOTX_TEXT */

व्योम __init bootx_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4)
अणु
	boot_infos_t *bi = (boot_infos_t *) r4;
	अचिन्हित दीर्घ hdr;
	अचिन्हित दीर्घ space;
	अचिन्हित दीर्घ ptr;
	अक्षर *model;
	अचिन्हित दीर्घ offset = reloc_offset();

	reloc_got2(offset);

	bootx_info = bi;

	/* We haven't cleared any bss at this poपूर्णांक, make sure
	 * what we need is initialized
	 */
	bootx_dt_strbase = bootx_dt_strend = 0;
	bootx_node_chosen = 0;
	bootx_disp_path[0] = 0;

	अगर (!BOOT_INFO_IS_V2_COMPATIBLE(bi))
		bi->logicalDisplayBase = bi->dispDeviceBase;

	/* Fixup depth 16 -> 15 as that's what MacOS calls 16bpp */
	अगर (bi->dispDeviceDepth == 16)
		bi->dispDeviceDepth = 15;


#अगर_घोषित CONFIG_BOOTX_TEXT
	ptr = (अचिन्हित दीर्घ)bi->logicalDisplayBase;
	ptr += bi->dispDeviceRect[1] * bi->dispDeviceRowBytes;
	ptr += bi->dispDeviceRect[0] * ((bi->dispDeviceDepth + 7) / 8);
	btext_setup_display(bi->dispDeviceRect[2] - bi->dispDeviceRect[0],
			    bi->dispDeviceRect[3] - bi->dispDeviceRect[1],
			    bi->dispDeviceDepth, bi->dispDeviceRowBytes,
			    (अचिन्हित दीर्घ)bi->logicalDisplayBase);
	btext_clearscreen();
	btext_flushscreen();
#पूर्ण_अगर /* CONFIG_BOOTX_TEXT */

	/*
	 * Test अगर boot-info is compatible.  Done only in config
	 * CONFIG_BOOTX_TEXT since there is nothing much we can करो
	 * with an incompatible version, except display a message
	 * and eventually hang the processor...
	 *
	 * I'll try to keep enough of boot-info compatible in the
	 * future to always allow display of this message;
	 */
	अगर (!BOOT_INFO_IS_COMPATIBLE(bi)) अणु
		bootx_म_लिखो(" !!! WARNING - Incompatible version"
			     " of BootX !!!\n\n\n");
		क्रम (;;)
			;
	पूर्ण
	अगर (bi->architecture != BOOT_ARCH_PCI) अणु
		bootx_म_लिखो(" !!! WARNING - Unsupported machine"
			     " architecture !\n");
		क्रम (;;)
			;
	पूर्ण

#अगर_घोषित CONFIG_BOOTX_TEXT
	btext_welcome(bi);
#पूर्ण_अगर

	/* New BootX enters kernel with MMU off, i/os are not allowed
	 * here. This hack will have been करोne by the boostrap anyway.
	 */
	अगर (bi->version < 4) अणु
		/*
		 * XXX If this is an iMac, turn off the USB controller.
		 */
		model = (अक्षर *) bootx_early_getprop(r4 + bi->deviceTreeOffset,
						     4, "model");
		अगर (model
		    && (म_भेद(model, "iMac,1") == 0
			|| म_भेद(model, "PowerMac1,1") == 0)) अणु
			bootx_म_लिखो("iMac,1 detected, shutting down USB\n");
			out_le32((अचिन्हित __iomem *)0x80880008, 1);	/* XXX */
		पूर्ण
	पूर्ण

	/* Get a poपूर्णांकer that poपूर्णांकs above the device tree, args, ramdisk,
	 * etc... to use क्रम generating the flattened tree
	 */
	अगर (bi->version < 5) अणु
		space = bi->deviceTreeOffset + bi->deviceTreeSize;
		अगर (bi->ramDisk >= space)
			space = bi->ramDisk + bi->ramDiskSize;
	पूर्ण अन्यथा
		space = bi->totalParamsSize;

	bootx_म_लिखो("Total space used by parameters & ramdisk: 0x%x\n", space);

	/* New BootX will have flushed all TLBs and enters kernel with
	 * MMU चयनed OFF, so this should not be useful anymore.
	 */
	अगर (bi->version < 4) अणु
		अचिन्हित दीर्घ x __maybe_unused;

		bootx_म_लिखो("Touching pages...\n");

		/*
		 * Touch each page to make sure the PTEs क्रम them
		 * are in the hash table - the aim is to try to aव्योम
		 * getting DSI exceptions जबतक copying the kernel image.
		 */
		क्रम (ptr = ((अचिन्हित दीर्घ) &_stext) & PAGE_MASK;
		     ptr < (अचिन्हित दीर्घ)bi + space; ptr += PAGE_SIZE)
			x = *(अस्थिर अचिन्हित दीर्घ *)ptr;
	पूर्ण

	/* Ok, now we need to generate a flattened device-tree to pass
	 * to the kernel
	 */
	bootx_म_लिखो("Preparing boot params...\n");

	hdr = bootx_flatten_dt(space);

#अगर_घोषित CONFIG_BOOTX_TEXT
#अगर_घोषित SET_BOOT_BAT
	bootx_म_लिखो("Preparing BAT...\n");
	btext_prepare_BAT();
#अन्यथा
	btext_unmap();
#पूर्ण_अगर
#पूर्ण_अगर

	reloc_got2(-offset);

	__start(hdr, KERNELBASE + offset, 0);
पूर्ण
