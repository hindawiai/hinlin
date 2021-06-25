<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * restart.c
 *
 * Copyright (C) 2001 MontaVista Software, Inc.
 */
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश "hardware.h"
#समावेश "iop3xx.h"

व्योम iop3xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	*IOP3XX_PCSR = 0x30;

	/* Jump पूर्णांकo ROM at address 0 */
	soft_restart(0);
पूर्ण
