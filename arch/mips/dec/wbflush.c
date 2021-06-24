<शैली गुरु>
/*
 * Setup the right wbflush routine क्रम the dअगरferent DECstations.
 *
 * Created with inक्रमmation from:
 *	DECstation 3100 Desktop Workstation Functional Specअगरication
 *	DECstation 5000/200 KN02 System Module Functional Specअगरication
 *	mipsel-linux-objdump --disassemble vmunix | grep "wbflush" :-)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998 Harald Koerfgen
 * Copyright (C) 2002 Maciej W. Rozycki
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/wbflush.h>
#समावेश <यंत्र/barrier.h>

अटल व्योम wbflush_kn01(व्योम);
अटल व्योम wbflush_kn210(व्योम);
अटल व्योम wbflush_mips(व्योम);

व्योम (*__wbflush) (व्योम);

व्योम __init wbflush_setup(व्योम)
अणु
	चयन (mips_machtype) अणु
	हाल MACH_DS23100:
	हाल MACH_DS5000_200:	/* DS5000 3max */
		__wbflush = wbflush_kn01;
		अवरोध;
	हाल MACH_DS5100:	/* DS5100 MIPSMATE */
		__wbflush = wbflush_kn210;
		अवरोध;
	हाल MACH_DS5000_1XX:	/* DS5000/100 3min */
	हाल MACH_DS5000_XX:	/* Personal DS5000/2x */
	हाल MACH_DS5000_2X0:	/* DS5000/240 3max+ */
	हाल MACH_DS5900:	/* DS5900 bigmax */
	शेष:
		__wbflush = wbflush_mips;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * For the DS3100 and DS5000/200 the R2020/R3220 ग_लिखोback buffer functions
 * as part of Coprocessor 0.
 */
अटल व्योम wbflush_kn01(व्योम)
अणु
    यंत्र(".set\tpush\n\t"
	".set\tnoreorder\n\t"
	"1:\tbc0f\t1b\n\t"
	"nop\n\t"
	".set\tpop");
पूर्ण

/*
 * For the DS5100 the ग_लिखोback buffer seems to be a part of Coprocessor 3.
 * But CP3 has to enabled first.
 */
अटल व्योम wbflush_kn210(व्योम)
अणु
    यंत्र(".set\tpush\n\t"
	".set\tnoreorder\n\t"
	"mfc0\t$2,$12\n\t"
	"lui\t$3,0x8000\n\t"
	"or\t$3,$2,$3\n\t"
	"mtc0\t$3,$12\n\t"
	"nop\n"
	"1:\tbc3f\t1b\n\t"
	"nop\n\t"
	"mtc0\t$2,$12\n\t"
	"nop\n\t"
	".set\tpop"
	: : : "$2", "$3");
पूर्ण

/*
 * I/O ASIC प्रणालीs use a standard ग_लिखोback buffer that माला_लो flushed
 * upon an uncached पढ़ो.
 */
अटल व्योम wbflush_mips(व्योम)
अणु
	__fast_iob();
पूर्ण
EXPORT_SYMBOL(__wbflush);
