<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2003  Bruno Ducrot
 *  (C) 2004  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 *
 * Based on code found in
 * linux/include/यंत्र-i386/ist.h and linux/arch/i386/kernel/setup.c
 * and originally developed by Andy Grover <andrew.grover@पूर्णांकel.com>
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <lrmi.h>

पूर्णांक मुख्य (व्योम)
अणु
	काष्ठा LRMI_regs	r;
	पूर्णांक			retval;

	अगर (!LRMI_init())
		वापस 0;

	स_रखो(&r, 0, माप(r));

	r.eax = 0x0000E980;
	r.edx = 0x47534943;

	retval = LRMI_पूर्णांक(0x15, &r);

	अगर (!retval) अणु
		म_लिखो("Failed!\n");
		वापस 0;
	पूर्ण
	अगर (r.eax == 0x47534943) अणु
		म_लिखो("BIOS supports GSIC call:\n");
		म_लिखो("\tsignature: %c%c%c%c\n",
		       (r.eax >> 24) & 0xff,
		       (r.eax >> 16) & 0xff,
		       (r.eax >> 8) & 0xff,
		       (r.eax) & 0xff);
		म_लिखो("\tcommand port = 0x%.4x\n",
		       r.ebx & 0xffff);
		म_लिखो("\tcommand =      0x%.4x\n",
		       (r.ebx >> 16) & 0xffff);
		म_लिखो("\tevent port =   0x%.8x\n", r.ecx);
		म_लिखो("\tflags =        0x%.8x\n", r.edx);
		अगर (((r.ebx >> 16) & 0xffff) != 0x82) अणु
			म_लिखो("non-default command value. If speedstep-smi "
			       "doesn't work out of the box,\nyou may want to "
			       "try out the default value by passing "
			       "smi_cmd=0x82 to the module\n ON YOUR OWN "
			       "RISK.\n");
		पूर्ण
		अगर ((r.ebx & 0xffff) != 0xb2) अणु
			म_लिखो("non-default command port. If speedstep-smi "
			       "doesn't work out of the box,\nyou may want to "
			       "try out the default value by passing "
			       "smi_port=0x82 to the module\n ON YOUR OWN "
			       "RISK.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		म_लिखो("BIOS DOES NOT support GSIC call.  Dumping registers anyway:\n");
		म_लिखो("eax = 0x%.8x\n", r.eax);
		म_लिखो("ebx = 0x%.8x\n", r.ebx);
		म_लिखो("ecx = 0x%.8x\n", r.ecx);
		म_लिखो("edx = 0x%.8x\n", r.edx);
		म_लिखो("Note also that some BIOS do not support the initial "
		       "GSIC call, but the newer\nspeedstep-smi driver may "
		       "work.\nFor this, you need to pass some arguments to "
		       "the speedstep-smi driver:\n");
		म_लिखो("\tsmi_cmd=0x?? smi_port=0x?? smi_sig=1\n");
		म_लिखो("\nUnfortunately, you have to know what exactly are "
		       "smi_cmd and smi_port, and this\nis system "
		       "dependent.\n");
	पूर्ण
	वापस 1;
पूर्ण
