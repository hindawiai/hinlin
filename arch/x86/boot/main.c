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
 * Main module क्रम the real-mode kernel code
 */
#समावेश <linux/build_bug.h>

#समावेश "boot.h"
#समावेश "string.h"

काष्ठा boot_params boot_params __attribute__((aligned(16)));

अक्षर *HEAP = _end;
अक्षर *heap_end = _end;		/* Default end of heap = no heap */

/*
 * Copy the header पूर्णांकo the boot parameter block.  Since this
 * screws up the old-style command line protocol, adjust by
 * filling in the new-style command line poपूर्णांकer instead.
 */

अटल व्योम copy_boot_params(व्योम)
अणु
	काष्ठा old_cmdline अणु
		u16 cl_magic;
		u16 cl_offset;
	पूर्ण;
	स्थिर काष्ठा old_cmdline * स्थिर oldcmd =
		(स्थिर काष्ठा old_cmdline *)OLD_CL_ADDRESS;

	BUILD_BUG_ON(माप(boot_params) != 4096);
	स_नकल(&boot_params.hdr, &hdr, माप(hdr));

	अगर (!boot_params.hdr.cmd_line_ptr &&
	    oldcmd->cl_magic == OLD_CL_MAGIC) अणु
		/* Old-style command line protocol. */
		u16 cmdline_seg;

		/* Figure out अगर the command line falls in the region
		   of memory that an old kernel would have copied up
		   to 0x90000... */
		अगर (oldcmd->cl_offset < boot_params.hdr.setup_move_size)
			cmdline_seg = ds();
		अन्यथा
			cmdline_seg = 0x9000;

		boot_params.hdr.cmd_line_ptr =
			(cmdline_seg << 4) + oldcmd->cl_offset;
	पूर्ण
पूर्ण

/*
 * Query the keyboard lock status as given by the BIOS, and
 * set the keyboard repeat rate to maximum.  Unclear why the latter
 * is करोne here; this might be possible to समाप्त off as stale code.
 */
अटल व्योम keyboard_init(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;
	initregs(&ireg);

	ireg.ah = 0x02;		/* Get keyboard status */
	पूर्णांकcall(0x16, &ireg, &oreg);
	boot_params.kbd_status = oreg.al;

	ireg.ax = 0x0305;	/* Set keyboard repeat rate */
	पूर्णांकcall(0x16, &ireg, शून्य);
पूर्ण

/*
 * Get Intel SpeedStep (IST) inक्रमmation.
 */
अटल व्योम query_ist(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	/* Some older BIOSes apparently crash on this call, so filter
	   it from machines too old to have SpeedStep at all. */
	अगर (cpu.level < 6)
		वापस;

	initregs(&ireg);
	ireg.ax  = 0xe980;	 /* IST Support */
	ireg.edx = 0x47534943;	 /* Request value */
	पूर्णांकcall(0x15, &ireg, &oreg);

	boot_params.ist_info.signature  = oreg.eax;
	boot_params.ist_info.command    = oreg.ebx;
	boot_params.ist_info.event      = oreg.ecx;
	boot_params.ist_info.perf_level = oreg.edx;
पूर्ण

/*
 * Tell the BIOS what CPU mode we पूर्णांकend to run in.
 */
अटल व्योम set_bios_mode(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	काष्ठा biosregs ireg;

	initregs(&ireg);
	ireg.ax = 0xec00;
	ireg.bx = 2;
	पूर्णांकcall(0x15, &ireg, शून्य);
#पूर्ण_अगर
पूर्ण

अटल व्योम init_heap(व्योम)
अणु
	अक्षर *stack_end;

	अगर (boot_params.hdr.loadflags & CAN_USE_HEAP) अणु
		यंत्र("leal %P1(%%esp),%0"
		    : "=r" (stack_end) : "i" (-STACK_SIZE));

		heap_end = (अक्षर *)
			((माप_प्रकार)boot_params.hdr.heap_end_ptr + 0x200);
		अगर (heap_end > stack_end)
			heap_end = stack_end;
	पूर्ण अन्यथा अणु
		/* Boot protocol 2.00 only, no heap available */
		माला_दो("WARNING: Ancient bootloader, some functionality "
		     "may be limited!\n");
	पूर्ण
पूर्ण

व्योम मुख्य(व्योम)
अणु
	/* First, copy the boot header पूर्णांकo the "zeropage" */
	copy_boot_params();

	/* Initialize the early-boot console */
	console_init();
	अगर (cmdline_find_option_bool("debug"))
		माला_दो("early console in setup code\n");

	/* End of heap check */
	init_heap();

	/* Make sure we have all the proper CPU support */
	अगर (validate_cpu()) अणु
		माला_दो("Unable to boot - please use a kernel appropriate "
		     "for your CPU.\n");
		die();
	पूर्ण

	/* Tell the BIOS what CPU mode we पूर्णांकend to run in. */
	set_bios_mode();

	/* Detect memory layout */
	detect_memory();

	/* Set keyboard repeat rate (why?) and query the lock flags */
	keyboard_init();

	/* Query Intel SpeedStep (IST) inक्रमmation */
	query_ist();

	/* Query APM inक्रमmation */
#अगर defined(CONFIG_APM) || defined(CONFIG_APM_MODULE)
	query_apm_bios();
#पूर्ण_अगर

	/* Query EDD inक्रमmation */
#अगर defined(CONFIG_EDD) || defined(CONFIG_EDD_MODULE)
	query_edd();
#पूर्ण_अगर

	/* Set the video mode */
	set_video();

	/* Do the last things and invoke रक्षित mode */
	go_to_रक्षित_mode();
पूर्ण
