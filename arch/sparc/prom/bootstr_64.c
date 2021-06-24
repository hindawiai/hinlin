<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bootstr.c:  Boot string/argument acquisition from the PROM.
 *
 * Copyright(C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright(C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <यंत्र/oplib.h>

/* WARNING: The boot loader knows that these next three variables come one right
 *          after another in the .data section.  Do not move this stuff पूर्णांकo
 *          the .bss section or it will अवरोध things.
 */

/* We limit BARG_LEN to 1024 because this is the size of the
 * 'barg_out' command line buffer in the SILO bootloader.
 */
#घोषणा BARG_LEN 1024
काष्ठा अणु
	पूर्णांक bootstr_len;
	पूर्णांक bootstr_valid;
	अक्षर bootstr_buf[BARG_LEN];
पूर्ण bootstr_info = अणु
	.bootstr_len = BARG_LEN,
#अगर_घोषित CONFIG_CMDLINE
	.bootstr_valid = 1,
	.bootstr_buf = CONFIG_CMDLINE,
#पूर्ण_अगर
पूर्ण;

अक्षर * __init
prom_getbootargs(व्योम)
अणु
	/* This check saves us from a panic when bootfd patches args. */
	अगर (bootstr_info.bootstr_valid)
		वापस bootstr_info.bootstr_buf;
	prom_माला_लोtring(prom_chosen_node, "bootargs",
		       bootstr_info.bootstr_buf, BARG_LEN);
	bootstr_info.bootstr_valid = 1;
	वापस bootstr_info.bootstr_buf;
पूर्ण
