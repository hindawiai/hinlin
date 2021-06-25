<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 *   Original APM BIOS checking by Stephen Rothwell, May 1994
 *   (sfr@canb.auug.org.au)
 *
 * ----------------------------------------------------------------------- */

/*
 * Get APM BIOS inक्रमmation
 */

#समावेश "boot.h"

पूर्णांक query_apm_bios(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	/* APM BIOS installation check */
	initregs(&ireg);
	ireg.ah = 0x53;
	पूर्णांकcall(0x15, &ireg, &oreg);

	अगर (oreg.flags & X86_EFLAGS_CF)
		वापस -1;		/* No APM BIOS */

	अगर (oreg.bx != 0x504d)		/* "PM" signature */
		वापस -1;

	अगर (!(oreg.cx & 0x02))		/* 32 bits supported? */
		वापस -1;

	/* Disconnect first, just in हाल */
	ireg.al = 0x04;
	पूर्णांकcall(0x15, &ireg, शून्य);

	/* 32-bit connect */
	ireg.al = 0x03;
	पूर्णांकcall(0x15, &ireg, &oreg);

	boot_params.apm_bios_info.cseg        = oreg.ax;
	boot_params.apm_bios_info.offset      = oreg.ebx;
	boot_params.apm_bios_info.cseg_16     = oreg.cx;
	boot_params.apm_bios_info.dseg        = oreg.dx;
	boot_params.apm_bios_info.cseg_len    = oreg.si;
	boot_params.apm_bios_info.cseg_16_len = oreg.hsi;
	boot_params.apm_bios_info.dseg_len    = oreg.di;

	अगर (oreg.flags & X86_EFLAGS_CF)
		वापस -1;

	/* Reकरो the installation check as the 32-bit connect;
	   some BIOSes वापस dअगरferent flags this way... */

	ireg.al = 0x00;
	पूर्णांकcall(0x15, &ireg, &oreg);

	अगर ((oreg.eflags & X86_EFLAGS_CF) || oreg.bx != 0x504d) अणु
		/* Failure with 32-bit connect, try to disconnect and ignore */
		ireg.al = 0x04;
		पूर्णांकcall(0x15, &ireg, शून्य);
		वापस -1;
	पूर्ण

	boot_params.apm_bios_info.version = oreg.ax;
	boot_params.apm_bios_info.flags   = oreg.cx;
	वापस 0;
पूर्ण

