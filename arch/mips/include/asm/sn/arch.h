<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI specअगरic setup.
 *
 * Copyright (C) 1995 - 1997, 1999 Silcon Graphics, Inc.
 * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)
 */
#अगर_अघोषित _ASM_SN_ARCH_H
#घोषणा _ASM_SN_ARCH_H

#समावेश <linux/types.h>
#समावेश <यंत्र/sn/types.h>
#अगर_घोषित CONFIG_SGI_IP27
#समावेश <यंत्र/sn/sn0/arch.h>
#पूर्ण_अगर

#घोषणा cputonasid(cpu)		(sn_cpu_info[(cpu)].p_nasid)
#घोषणा cputoslice(cpu)		(sn_cpu_info[(cpu)].p_slice)

#घोषणा INVALID_NASID		(nasid_t)-1
#घोषणा INVALID_PNODEID		(pnodeid_t)-1
#घोषणा INVALID_MODULE		(moduleid_t)-1
#घोषणा INVALID_PARTID		(partid_t)-1

#पूर्ण_अगर /* _ASM_SN_ARCH_H */
