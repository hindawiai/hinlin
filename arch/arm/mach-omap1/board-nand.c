<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-nand.c
 *
 * Common OMAP1 board न_अंकD code
 *
 * Copyright (C) 2004, 2012 Texas Instruments, Inc.
 * Copyright (C) 2002 MontaVista Software, Inc.
 * Copyright (C) 2001 RidgeRun, Inc.
 * Author: RidgeRun, Inc.
 *         Greg Lonnon (glonnon@ridgerun.com) or info@ridgerun.com
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>

#समावेश "common.h"

व्योम omap1_nand_cmd_ctl(काष्ठा nand_chip *this, पूर्णांक cmd, अचिन्हित पूर्णांक ctrl)
अणु
	अचिन्हित दीर्घ mask;

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	mask = (ctrl & न_अंकD_CLE) ? 0x02 : 0;
	अगर (ctrl & न_अंकD_ALE)
		mask |= 0x04;

	ग_लिखोb(cmd, this->legacy.IO_ADDR_W + mask);
पूर्ण

