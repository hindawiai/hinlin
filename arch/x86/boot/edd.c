<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Get EDD BIOS disk inक्रमmation
 */

#समावेश "boot.h"
#समावेश <linux/edd.h>
#समावेश "string.h"

#अगर defined(CONFIG_EDD) || defined(CONFIG_EDD_MODULE)

/*
 * Read the MBR (first sector) from a specअगरic device.
 */
अटल पूर्णांक पढ़ो_mbr(u8 devno, व्योम *buf)
अणु
	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ax = 0x0201;		/* Legacy Read, one sector */
	ireg.cx = 0x0001;		/* Sector 0-0-1 */
	ireg.dl = devno;
	ireg.bx = (माप_प्रकार)buf;

	पूर्णांकcall(0x13, &ireg, &oreg);

	वापस -(oreg.eflags & X86_EFLAGS_CF); /* 0 or -1 */
पूर्ण

अटल u32 पढ़ो_mbr_sig(u8 devno, काष्ठा edd_info *ei, u32 *mbrsig)
अणु
	पूर्णांक sector_size;
	अक्षर *mbrbuf_ptr, *mbrbuf_end;
	u32 buf_base, mbr_base;
	बाह्य अक्षर _end[];
	u16 mbr_magic;

	sector_size = ei->params.bytes_per_sector;
	अगर (!sector_size)
		sector_size = 512; /* Best available guess */

	/* Produce a naturally aligned buffer on the heap */
	buf_base = (ds() << 4) + (u32)&_end;
	mbr_base = (buf_base+sector_size-1) & ~(sector_size-1);
	mbrbuf_ptr = _end + (mbr_base-buf_base);
	mbrbuf_end = mbrbuf_ptr + sector_size;

	/* Make sure we actually have space on the heap... */
	अगर (!(boot_params.hdr.loadflags & CAN_USE_HEAP))
		वापस -1;
	अगर (mbrbuf_end > (अक्षर *)(माप_प्रकार)boot_params.hdr.heap_end_ptr)
		वापस -1;

	स_रखो(mbrbuf_ptr, 0, sector_size);
	अगर (पढ़ो_mbr(devno, mbrbuf_ptr))
		वापस -1;

	*mbrsig = *(u32 *)&mbrbuf_ptr[EDD_MBR_SIG_OFFSET];
	mbr_magic = *(u16 *)&mbrbuf_ptr[510];

	/* check क्रम valid MBR magic */
	वापस mbr_magic == 0xAA55 ? 0 : -1;
पूर्ण

अटल पूर्णांक get_edd_info(u8 devno, काष्ठा edd_info *ei)
अणु
	काष्ठा biosregs ireg, oreg;

	स_रखो(ei, 0, माप(*ei));

	/* Check Extensions Present */

	initregs(&ireg);
	ireg.ah = 0x41;
	ireg.bx = EDDMAGIC1;
	ireg.dl = devno;
	पूर्णांकcall(0x13, &ireg, &oreg);

	अगर (oreg.eflags & X86_EFLAGS_CF)
		वापस -1;	/* No extended inक्रमmation */

	अगर (oreg.bx != EDDMAGIC2)
		वापस -1;

	ei->device  = devno;
	ei->version = oreg.ah;		 /* EDD version number */
	ei->पूर्णांकerface_support = oreg.cx; /* EDD functionality subsets */

	/* Extended Get Device Parameters */

	ei->params.length = माप(ei->params);
	ireg.ah = 0x48;
	ireg.si = (माप_प्रकार)&ei->params;
	पूर्णांकcall(0x13, &ireg, &oreg);

	/* Get legacy CHS parameters */

	/* Ralf Brown recommends setting ES:DI to 0:0 */
	ireg.ah = 0x08;
	ireg.es = 0;
	पूर्णांकcall(0x13, &ireg, &oreg);

	अगर (!(oreg.eflags & X86_EFLAGS_CF)) अणु
		ei->legacy_max_cylinder = oreg.ch + ((oreg.cl & 0xc0) << 2);
		ei->legacy_max_head = oreg.dh;
		ei->legacy_sectors_per_track = oreg.cl & 0x3f;
	पूर्ण

	वापस 0;
पूर्ण

व्योम query_edd(व्योम)
अणु
	अक्षर eddarg[8];
	पूर्णांक करो_mbr = 1;
#अगर_घोषित CONFIG_EDD_OFF
	पूर्णांक करो_edd = 0;
#अन्यथा
	पूर्णांक करो_edd = 1;
#पूर्ण_अगर
	पूर्णांक be_quiet;
	पूर्णांक devno;
	काष्ठा edd_info ei, *edp;
	u32 *mbrptr;

	अगर (cmdline_find_option("edd", eddarg, माप(eddarg)) > 0) अणु
		अगर (!म_भेद(eddarg, "skipmbr") || !म_भेद(eddarg, "skip")) अणु
			करो_edd = 1;
			करो_mbr = 0;
		पूर्ण
		अन्यथा अगर (!म_भेद(eddarg, "off"))
			करो_edd = 0;
		अन्यथा अगर (!म_भेद(eddarg, "on"))
			करो_edd = 1;
	पूर्ण

	be_quiet = cmdline_find_option_bool("quiet");

	edp    = boot_params.eddbuf;
	mbrptr = boot_params.edd_mbr_sig_buffer;

	अगर (!करो_edd)
		वापस;

	/* Bugs in OnBoard or AddOnCards Bios may hang the EDD probe,
	 * so give a hपूर्णांक अगर this happens.
	 */

	अगर (!be_quiet)
		म_लिखो("Probing EDD (edd=off to disable)... ");

	क्रम (devno = 0x80; devno < 0x80+EDD_MBR_SIG_MAX; devno++) अणु
		/*
		 * Scan the BIOS-supported hard disks and query EDD
		 * inक्रमmation...
		 */
		अगर (!get_edd_info(devno, &ei)
		    && boot_params.eddbuf_entries < EDDMAXNR) अणु
			स_नकल(edp, &ei, माप(ei));
			edp++;
			boot_params.eddbuf_entries++;
		पूर्ण

		अगर (करो_mbr && !पढ़ो_mbr_sig(devno, &ei, mbrptr++))
			boot_params.edd_mbr_sig_buf_entries = devno-0x80+1;
	पूर्ण

	अगर (!be_quiet)
		म_लिखो("ok\n");
पूर्ण

#पूर्ण_अगर
