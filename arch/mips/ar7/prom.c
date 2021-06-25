<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 *
 * Putting things on the screen/serial line using YAMONs facilities.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/पन.स>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/setup.h>

#समावेश <यंत्र/mach-ar7/ar7.h>
#समावेश <यंत्र/mach-ar7/prom.h>

#घोषणा MAX_ENTRY 80

काष्ठा env_var अणु
	अक्षर	*name;
	अक्षर	*value;
पूर्ण;

अटल काष्ठा env_var adam2_env[MAX_ENTRY];

अक्षर *prom_दो_पर्या(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; (i < MAX_ENTRY) && adam2_env[i].name; i++)
		अगर (!म_भेद(name, adam2_env[i].name))
			वापस adam2_env[i].value;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(prom_दो_पर्या);

अटल व्योम  __init ar7_init_cmdline(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक i;

	क्रम (i = 1; i < argc; i++) अणु
		strlcat(arcs_cmdline, argv[i], COMMAND_LINE_SIZE);
		अगर (i < (argc - 1))
			strlcat(arcs_cmdline, " ", COMMAND_LINE_SIZE);
	पूर्ण
पूर्ण

काष्ठा psbl_rec अणु
	u32	psbl_size;
	u32	env_base;
	u32	env_size;
	u32	ffs_base;
	u32	ffs_size;
पूर्ण;

अटल स्थिर अक्षर psp_env_version[] __initस्थिर = "TIENV0.8";

काष्ठा psp_env_chunk अणु
	u8	num;
	u8	ctrl;
	u16	csum;
	u8	len;
	अक्षर	data[11];
पूर्ण __packed;

काष्ठा psp_var_map_entry अणु
	u8	num;
	अक्षर	*value;
पूर्ण;

अटल स्थिर काष्ठा psp_var_map_entry psp_var_map[] = अणु
	अणु  1,	"cpufrequency" पूर्ण,
	अणु  2,	"memsize" पूर्ण,
	अणु  3,	"flashsize" पूर्ण,
	अणु  4,	"modetty0" पूर्ण,
	अणु  5,	"modetty1" पूर्ण,
	अणु  8,	"maca" पूर्ण,
	अणु  9,	"macb" पूर्ण,
	अणु 28,	"sysfrequency" पूर्ण,
	अणु 38,	"mipsfrequency" पूर्ण,
पूर्ण;

/*

Well-known variable (num is looked up in table above क्रम matching variable name)
Example: cpufrequency=211968000
+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+---
| 01 |CTRL|CHECKSUM | 01 | _2 | _1 | _1 | _9 | _6 | _8 | _0 | _0 | _0 | \0 | FF
+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+---

Name=Value pair in a single chunk
Example: NAME=VALUE
+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+---
| 00 |CTRL|CHECKSUM | 01 | _N | _A | _M | _E | _0 | _V | _A | _L | _U | _E | \0
+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+---

Name=Value pair in 2 chunks (len is the number of chunks)
Example: bootloaderVersion=1.3.7.15
+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+---
| 00 |CTRL|CHECKSUM | 02 | _b | _o | _o | _t | _l | _o | _a | _d | _e | _r | _V
+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+---
| _e | _r | _s | _i | _o | _n | \0 | _1 | _. | _3 | _. | _7 | _. | _1 | _5 | \0
+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+---

Data is padded with 0xFF

*/

#घोषणा PSP_ENV_SIZE  4096

अटल अक्षर psp_env_data[PSP_ENV_SIZE] = अणु 0, पूर्ण;

अटल अक्षर * __init lookup_psp_var_map(u8 num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(psp_var_map); i++)
		अगर (psp_var_map[i].num == num)
			वापस psp_var_map[i].value;

	वापस शून्य;
पूर्ण

अटल व्योम __init add_adam2_var(अक्षर *name, अक्षर *value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_ENTRY; i++) अणु
		अगर (!adam2_env[i].name) अणु
			adam2_env[i].name = name;
			adam2_env[i].value = value;
			वापस;
		पूर्ण अन्यथा अगर (!म_भेद(adam2_env[i].name, name)) अणु
			adam2_env[i].value = value;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init parse_psp_env(व्योम *psp_env_base)
अणु
	पूर्णांक i, n;
	अक्षर *name, *value;
	काष्ठा psp_env_chunk *chunks = (काष्ठा psp_env_chunk *)psp_env_data;

	स_नकल_fromio(chunks, psp_env_base, PSP_ENV_SIZE);

	i = 1;
	n = PSP_ENV_SIZE / माप(काष्ठा psp_env_chunk);
	जबतक (i < n) अणु
		अगर ((chunks[i].num == 0xff) || ((i + chunks[i].len) > n))
			अवरोध;
		value = chunks[i].data;
		अगर (chunks[i].num) अणु
			name = lookup_psp_var_map(chunks[i].num);
		पूर्ण अन्यथा अणु
			name = value;
			value += म_माप(name) + 1;
		पूर्ण
		अगर (name)
			add_adam2_var(name, value);
		i += chunks[i].len;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init ar7_init_env(काष्ठा env_var *env)
अणु
	पूर्णांक i;
	काष्ठा psbl_rec *psbl = (काष्ठा psbl_rec *)(KSEG1ADDR(0x14000300));
	व्योम *psp_env = (व्योम *)KSEG1ADDR(psbl->env_base);

	अगर (म_भेद(psp_env, psp_env_version) == 0) अणु
		parse_psp_env(psp_env);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < MAX_ENTRY; i++, env++)
			अगर (env->name)
				add_adam2_var(env->name, env->value);
	पूर्ण
पूर्ण

अटल व्योम __init console_config(व्योम)
अणु
#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
	अक्षर console_string[40];
	पूर्णांक baud = 0;
	अक्षर parity = '\0', bits = '\0', flow = '\0';
	अक्षर *s, *p;

	अगर (म_माला(arcs_cmdline, "console="))
		वापस;

	s = prom_दो_पर्या("modetty0");
	अगर (s) अणु
		baud = simple_म_से_अदीर्घ(s, &p, 10);
		s = p;
		अगर (*s == ',')
			s++;
		अगर (*s)
			parity = *s++;
		अगर (*s == ',')
			s++;
		अगर (*s)
			bits = *s++;
		अगर (*s == ',')
			s++;
		अगर (*s == 'h')
			flow = 'r';
	पूर्ण

	अगर (baud == 0)
		baud = 38400;
	अगर (parity != 'n' && parity != 'o' && parity != 'e')
		parity = 'n';
	अगर (bits != '7' && bits != '8')
		bits = '8';

	अगर (flow == 'r')
		प्र_लिखो(console_string, " console=ttyS0,%d%c%c%c", baud,
			parity, bits, flow);
	अन्यथा
		प्र_लिखो(console_string, " console=ttyS0,%d%c%c", baud, parity,
			bits);
	strlcat(arcs_cmdline, console_string, COMMAND_LINE_SIZE);
#पूर्ण_अगर
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	ar7_init_cmdline(fw_arg0, (अक्षर **)fw_arg1);
	ar7_init_env((काष्ठा env_var *)fw_arg2);
	console_config();
पूर्ण

#घोषणा PORT(offset) (KSEG1ADDR(AR7_REGS_UART0 + (offset * 4)))
अटल अंतरभूत अचिन्हित पूर्णांक serial_in(पूर्णांक offset)
अणु
	वापस पढ़ोl((व्योम *)PORT(offset));
पूर्ण

अटल अंतरभूत व्योम serial_out(पूर्णांक offset, पूर्णांक value)
अणु
	ग_लिखोl(value, (व्योम *)PORT(offset));
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	जबतक ((serial_in(UART_LSR) & UART_LSR_TEMT) == 0)
		;
	serial_out(UART_TX, c);
पूर्ण
