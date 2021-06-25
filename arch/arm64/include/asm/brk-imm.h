<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */

#अगर_अघोषित __ASM_BRK_IMM_H
#घोषणा __ASM_BRK_IMM_H

/*
 * #imm16 values used क्रम BRK inकाष्ठाion generation
 * 0x004: क्रम installing kprobes
 * 0x005: क्रम installing uprobes
 * 0x006: क्रम kprobe software single-step
 * Allowed values क्रम kgdb are 0x400 - 0x7ff
 * 0x100: क्रम triggering a fault on purpose (reserved)
 * 0x400: क्रम dynamic BRK inकाष्ठाion
 * 0x401: क्रम compile समय BRK inकाष्ठाion
 * 0x800: kernel-mode BUG() and WARN() traps
 * 0x9xx: tag-based KASAN trap (allowed values 0x900 - 0x9ff)
 */
#घोषणा KPROBES_BRK_IMM			0x004
#घोषणा UPROBES_BRK_IMM			0x005
#घोषणा KPROBES_BRK_SS_IMM		0x006
#घोषणा FAULT_BRK_IMM			0x100
#घोषणा KGDB_DYN_DBG_BRK_IMM		0x400
#घोषणा KGDB_COMPILED_DBG_BRK_IMM	0x401
#घोषणा BUG_BRK_IMM			0x800
#घोषणा KASAN_BRK_IMM			0x900
#घोषणा KASAN_BRK_MASK			0x0ff

#पूर्ण_अगर
