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
 * Very simple screen and serial I/O
 */

#समावेश "boot.h"

पूर्णांक early_serial_base;

#घोषणा XMTRDY          0x20

#घोषणा TXR             0       /*  Transmit रेजिस्टर (WRITE) */
#घोषणा LSR             5       /*  Line Status               */

/*
 * These functions are in .inittext so they can be used to संकेत
 * error during initialization.
 */

अटल व्योम __section(".inittext") serial_अक्षर_दो(पूर्णांक ch)
अणु
	अचिन्हित समयout = 0xffff;

	जबतक ((inb(early_serial_base + LSR) & XMTRDY) == 0 && --समयout)
		cpu_relax();

	outb(ch, early_serial_base + TXR);
पूर्ण

अटल व्योम __section(".inittext") bios_अक्षर_दो(पूर्णांक ch)
अणु
	काष्ठा biosregs ireg;

	initregs(&ireg);
	ireg.bx = 0x0007;
	ireg.cx = 0x0001;
	ireg.ah = 0x0e;
	ireg.al = ch;
	पूर्णांकcall(0x10, &ireg, शून्य);
पूर्ण

व्योम __section(".inittext") अक्षर_दो(पूर्णांक ch)
अणु
	अगर (ch == '\n')
		अक्षर_दो('\r');	/* \न -> \ल\न */

	bios_अक्षर_दो(ch);

	अगर (early_serial_base != 0)
		serial_अक्षर_दो(ch);
पूर्ण

व्योम __section(".inittext") माला_दो(स्थिर अक्षर *str)
अणु
	जबतक (*str)
		अक्षर_दो(*str++);
पूर्ण

/*
 * Read the CMOS घड़ी through the BIOS, and वापस the
 * seconds in BCD.
 */

अटल u8 समय_लो(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ah = 0x02;
	पूर्णांकcall(0x1a, &ireg, &oreg);

	वापस oreg.dh;
पूर्ण

/*
 * Read from the keyboard
 */
पूर्णांक अक्षर_लो(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);
	/* ireg.ah = 0x00; */
	पूर्णांकcall(0x16, &ireg, &oreg);

	वापस oreg.al;
पूर्ण

अटल पूर्णांक kbd_pending(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ah = 0x01;
	पूर्णांकcall(0x16, &ireg, &oreg);

	वापस !(oreg.eflags & X86_EFLAGS_ZF);
पूर्ण

व्योम kbd_flush(व्योम)
अणु
	क्रम (;;) अणु
		अगर (!kbd_pending())
			अवरोध;
		अक्षर_लो();
	पूर्ण
पूर्ण

पूर्णांक अक्षर_लो_समयout(व्योम)
अणु
	पूर्णांक cnt = 30;
	पूर्णांक t0, t1;

	t0 = समय_लो();

	जबतक (cnt) अणु
		अगर (kbd_pending())
			वापस अक्षर_लो();

		t1 = समय_लो();
		अगर (t0 != t1) अणु
			cnt--;
			t0 = t1;
		पूर्ण
	पूर्ण

	वापस 0;		/* Timeout! */
पूर्ण

