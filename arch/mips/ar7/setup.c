<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pm.h>
#समावेश <linux/समय.स>

#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/mach-ar7/ar7.h>
#समावेश <यंत्र/mach-ar7/prom.h>

अटल व्योम ar7_machine_restart(अक्षर *command)
अणु
	u32 *softres_reg = ioremap(AR7_REGS_RESET + AR7_RESET_SOFTWARE, 1);

	ग_लिखोl(1, softres_reg);
पूर्ण

अटल व्योम ar7_machine_halt(व्योम)
अणु
	जबतक (1)
		;
पूर्ण

अटल व्योम ar7_machine_घातer_off(व्योम)
अणु
	u32 *घातer_reg = (u32 *)ioremap(AR7_REGS_POWER, 1);
	u32 घातer_state = पढ़ोl(घातer_reg) | (3 << 30);

	ग_लिखोl(घातer_state, घातer_reg);
	ar7_machine_halt();
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	u16 chip_id = ar7_chip_id();
	u16 titan_variant_id = titan_chip_id();

	चयन (chip_id) अणु
	हाल AR7_CHIP_7100:
		वापस "TI AR7 (TNETD7100)";
	हाल AR7_CHIP_7200:
		वापस "TI AR7 (TNETD7200)";
	हाल AR7_CHIP_7300:
		वापस "TI AR7 (TNETD7300)";
	हाल AR7_CHIP_TITAN:
		चयन (titan_variant_id) अणु
		हाल TITAN_CHIP_1050:
			वापस "TI AR7 (TNETV1050)";
		हाल TITAN_CHIP_1055:
			वापस "TI AR7 (TNETV1055)";
		हाल TITAN_CHIP_1056:
			वापस "TI AR7 (TNETV1056)";
		हाल TITAN_CHIP_1060:
			वापस "TI AR7 (TNETV1060)";
		पूर्ण
		fallthrough;
	शेष:
		वापस "TI AR7 (unknown)";
	पूर्ण
पूर्ण

अटल पूर्णांक __init ar7_init_console(व्योम)
अणु
	वापस 0;
पूर्ण
console_initcall(ar7_init_console);

/*
 * Initializes basic routines and काष्ठाures poपूर्णांकers, memory size (as
 * given by the bios and saves the command line.
 */
व्योम __init plat_mem_setup(व्योम)
अणु
	अचिन्हित दीर्घ io_base;

	_machine_restart = ar7_machine_restart;
	_machine_halt = ar7_machine_halt;
	pm_घातer_off = ar7_machine_घातer_off;

	io_base = (अचिन्हित दीर्घ)ioremap(AR7_REGS_BASE, 0x10000);
	अगर (!io_base)
		panic("Can't remap IO base!");
	set_io_port_base(io_base);

	prom_meminit();

	prपूर्णांकk(KERN_INFO "%s, ID: 0x%04x, Revision: 0x%02x\n",
			get_प्रणाली_type(), ar7_chip_id(), ar7_chip_rev());
पूर्ण
