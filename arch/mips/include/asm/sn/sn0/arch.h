<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI IP27 specअगरic setup.
 *
 * Copyright (C) 1995 - 1997, 1999 Silcon Graphics, Inc.
 * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)
 */
#अगर_अघोषित _ASM_SN_SN0_ARCH_H
#घोषणा _ASM_SN_SN0_ARCH_H


/*
 * MAXCPUS refers to the maximum number of CPUs in a single kernel.
 * This is not necessarily the same as MAXNODES * CPUS_PER_NODE
 */
#घोषणा MAXCPUS			(MAX_NUMNODES * CPUS_PER_NODE)

/*
 * This is the maximum number of NASIDS that can be present in a प्रणाली.
 * (Highest NASID plus one.)
 */
#घोषणा MAX_NASIDS		256

/*
 * MAX_REGIONS refers to the maximum number of hardware partitioned regions.
 */
#घोषणा MAX_REGIONS		64
#घोषणा MAX_NONPREMIUM_REGIONS	16
#घोषणा MAX_PREMIUM_REGIONS	MAX_REGIONS

/*
 * MAX_PARITIONS refers to the maximum number of logically defined
 * partitions the प्रणाली can support.
 */
#घोषणा MAX_PARTITIONS		MAX_REGIONS

#घोषणा NASID_MASK_BYTES	((MAX_NASIDS + 7) / 8)

/*
 * Slot स्थिरants क्रम SN0
 */
#अगर_घोषित CONFIG_SGI_SN_N_MODE
#घोषणा MAX_MEM_SLOTS	16			/* max slots per node */
#अन्यथा /* !CONFIG_SGI_SN_N_MODE, assume CONFIG_SGI_SN_M_MODE */
#घोषणा MAX_MEM_SLOTS	32			/* max slots per node */
#पूर्ण_अगर /* CONFIG_SGI_SN_M_MODE */

#घोषणा SLOT_SHIFT		(27)
#घोषणा SLOT_MIN_MEM_SIZE	(32*1024*1024)

#घोषणा CPUS_PER_NODE		2	/* CPUs on a single hub */

#पूर्ण_अगर /* _ASM_SN_SN0_ARCH_H */
