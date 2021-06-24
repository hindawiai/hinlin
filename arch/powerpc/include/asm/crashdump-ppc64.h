<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _ASM_POWERPC_CRASHDUMP_PPC64_H
#घोषणा _ASM_POWERPC_CRASHDUMP_PPC64_H

/*
 * Backup region - first 64KB of System RAM
 *
 * If ever the below macros are to be changed, please be judicious.
 * The implicit assumptions are:
 *     - start, end & size are less than UINT32_MAX.
 *     - start & size are at least 8 byte aligned.
 *
 * For implementation details: arch/घातerpc/purgatory/trampoline_64.S
 */
#घोषणा BACKUP_SRC_START	0
#घोषणा BACKUP_SRC_END		0xffff
#घोषणा BACKUP_SRC_SIZE		(BACKUP_SRC_END - BACKUP_SRC_START + 1)

#पूर्ण_अगर /* __ASM_POWERPC_CRASHDUMP_PPC64_H */
