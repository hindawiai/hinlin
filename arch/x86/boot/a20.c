<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007-2008 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Enable A20 gate (वापस -1 on failure)
 */

#समावेश "boot.h"

#घोषणा MAX_8042_LOOPS	100000
#घोषणा MAX_8042_FF	32

अटल पूर्णांक empty_8042(व्योम)
अणु
	u8 status;
	पूर्णांक loops = MAX_8042_LOOPS;
	पूर्णांक ffs   = MAX_8042_FF;

	जबतक (loops--) अणु
		io_delay();

		status = inb(0x64);
		अगर (status == 0xff) अणु
			/* FF is a plausible, but very unlikely status */
			अगर (!--ffs)
				वापस -1; /* Assume no KBC present */
		पूर्ण
		अगर (status & 1) अणु
			/* Read and discard input data */
			io_delay();
			(व्योम)inb(0x60);
		पूर्ण अन्यथा अगर (!(status & 2)) अणु
			/* Buffers empty, finished! */
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

/* Returns nonzero अगर the A20 line is enabled.  The memory address
   used as a test is the पूर्णांक $0x80 vector, which should be safe. */

#घोषणा A20_TEST_ADDR	(4*0x80)
#घोषणा A20_TEST_SHORT  32
#घोषणा A20_TEST_LONG	2097152	/* 2^21 */

अटल पूर्णांक a20_test(पूर्णांक loops)
अणु
	पूर्णांक ok = 0;
	पूर्णांक saved, ctr;

	set_fs(0x0000);
	set_gs(0xffff);

	saved = ctr = rdfs32(A20_TEST_ADDR);

	जबतक (loops--) अणु
		wrfs32(++ctr, A20_TEST_ADDR);
		io_delay();	/* Serialize and make delay स्थिरant */
		ok = rdgs32(A20_TEST_ADDR+0x10) ^ ctr;
		अगर (ok)
			अवरोध;
	पूर्ण

	wrfs32(saved, A20_TEST_ADDR);
	वापस ok;
पूर्ण

/* Quick test to see अगर A20 is alपढ़ोy enabled */
अटल पूर्णांक a20_test_लघु(व्योम)
अणु
	वापस a20_test(A20_TEST_SHORT);
पूर्ण

/* Longer test that actually रुकोs क्रम A20 to come on line; this
   is useful when dealing with the KBC or other slow बाह्यal circuitry. */
अटल पूर्णांक a20_test_दीर्घ(व्योम)
अणु
	वापस a20_test(A20_TEST_LONG);
पूर्ण

अटल व्योम enable_a20_bios(व्योम)
अणु
	काष्ठा biosregs ireg;

	initregs(&ireg);
	ireg.ax = 0x2401;
	पूर्णांकcall(0x15, &ireg, शून्य);
पूर्ण

अटल व्योम enable_a20_kbc(व्योम)
अणु
	empty_8042();

	outb(0xd1, 0x64);	/* Command ग_लिखो */
	empty_8042();

	outb(0xdf, 0x60);	/* A20 on */
	empty_8042();

	outb(0xff, 0x64);	/* Null command, but UHCI wants it */
	empty_8042();
पूर्ण

अटल व्योम enable_a20_fast(व्योम)
अणु
	u8 port_a;

	port_a = inb(0x92);	/* Configuration port A */
	port_a |=  0x02;	/* Enable A20 */
	port_a &= ~0x01;	/* Do not reset machine */
	outb(port_a, 0x92);
पूर्ण

/*
 * Actual routine to enable A20; वापस 0 on ok, -1 on failure
 */

#घोषणा A20_ENABLE_LOOPS 255	/* Number of बार to try */

पूर्णांक enable_a20(व्योम)
अणु
       पूर्णांक loops = A20_ENABLE_LOOPS;
       पूर्णांक kbc_err;

       जबतक (loops--) अणु
	       /* First, check to see अगर A20 is alपढ़ोy enabled
		  (legacy मुक्त, etc.) */
	       अगर (a20_test_लघु())
		       वापस 0;
	       
	       /* Next, try the BIOS (INT 0x15, AX=0x2401) */
	       enable_a20_bios();
	       अगर (a20_test_लघु())
		       वापस 0;
	       
	       /* Try enabling A20 through the keyboard controller */
	       kbc_err = empty_8042();

	       अगर (a20_test_लघु())
		       वापस 0; /* BIOS worked, but with delayed reaction */
	
	       अगर (!kbc_err) अणु
		       enable_a20_kbc();
		       अगर (a20_test_दीर्घ())
			       वापस 0;
	       पूर्ण
	       
	       /* Finally, try enabling the "fast A20 gate" */
	       enable_a20_fast();
	       अगर (a20_test_दीर्घ())
		       वापस 0;
       पूर्ण
       
       वापस -1;
पूर्ण
