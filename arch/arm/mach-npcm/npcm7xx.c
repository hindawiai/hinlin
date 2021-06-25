<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Nuvoton Technology corporation.
// Copyright 2018 Google, Inc.

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

अटल स्थिर अक्षर *स्थिर npcm7xx_dt_match[] = अणु
	"nuvoton,npcm750",
	शून्य
पूर्ण;

DT_MACHINE_START(NPCM7XX_DT, "NPCM7XX Chip family")
	.atag_offset	= 0x100,
	.dt_compat	= npcm7xx_dt_match,
	.l2c_aux_val	= 0x0,
	.l2c_aux_mask	= ~0x0,
MACHINE_END
