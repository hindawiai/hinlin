<शैली गुरु>
/*
 * uboot.c -- uboot arguments support
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/console.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/memblock.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/sections.h>

/*
 * parse_uboot_commandline
 *
 * Copies u-boot commandline arguments and store them in the proper linux
 * variables.
 *
 * Assumes:
 *	_init_sp global contains the address in the stack poपूर्णांकer when the
 *	kernel starts (see head.S::_start)
 *
 *	U-Boot calling convention:
 *	(*kernel) (kbd, initrd_start, initrd_end, cmd_start, cmd_end);
 *
 *	_init_sp can be parsed as such
 *
 *	_init_sp+00 = u-boot cmd after jsr पूर्णांकo kernel (skip)
 *	_init_sp+04 = &kernel board_info (residual data)
 *	_init_sp+08 = &initrd_start
 *	_init_sp+12 = &initrd_end
 *	_init_sp+16 = &cmd_start
 *	_init_sp+20 = &cmd_end
 *
 *	This also assumes that the memory locations poपूर्णांकed to are still
 *	unmodअगरied. U-boot places them near the end of बाह्यal SDRAM.
 *
 * Argument(s):
 *	commandp = the linux commandline arg container to fill.
 *	size     = the माप commandp.
 *
 * Returns:
 */
अटल व्योम __init parse_uboot_commandline(अक्षर *commandp, पूर्णांक size)
अणु
	बाह्य अचिन्हित दीर्घ _init_sp;
	अचिन्हित दीर्घ *sp;
	अचिन्हित दीर्घ uboot_kbd;
	अचिन्हित दीर्घ uboot_initrd_start, uboot_initrd_end;
	अचिन्हित दीर्घ uboot_cmd_start, uboot_cmd_end;

	sp = (अचिन्हित दीर्घ *)_init_sp;
	uboot_kbd = sp[1];
	uboot_initrd_start = sp[2];
	uboot_initrd_end = sp[3];
	uboot_cmd_start = sp[4];
	uboot_cmd_end = sp[5];

	अगर (uboot_cmd_start && uboot_cmd_end)
		म_नकलन(commandp, (स्थिर अक्षर *)uboot_cmd_start, size);
#अगर defined(CONFIG_BLK_DEV_INITRD)
	अगर (uboot_initrd_start && uboot_initrd_end &&
	    (uboot_initrd_end > uboot_initrd_start)) अणु
		initrd_start = uboot_initrd_start;
		initrd_end = uboot_initrd_end;
		ROOT_DEV = Root_RAM0;
		pr_info("initrd at 0x%lx:0x%lx\n", initrd_start, initrd_end);
	पूर्ण
#पूर्ण_अगर /* अगर defined(CONFIG_BLK_DEV_INITRD) */
पूर्ण

__init व्योम process_uboot_commandline(अक्षर *commandp, पूर्णांक size)
अणु
	पूर्णांक len, n;

	n = strnlen(commandp, size);
	commandp += n;
	len = size - n;
	अगर (len) अणु
		/* Add the whitespace separator */
		*commandp++ = ' ';
		len--;
	पूर्ण

	parse_uboot_commandline(commandp, len);
	commandp[len - 1] = 0;
पूर्ण
