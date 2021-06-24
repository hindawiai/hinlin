<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Derived from IRIX <sys/SN/gda.h>.
 *
 * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.
 *
 * gda.h -- Contains the data काष्ठाure क्रम the global data area,
 *	The GDA contains inक्रमmation communicated between the
 *	PROM, SYMMON, and the kernel.
 */
#अगर_अघोषित _ASM_SN_GDA_H
#घोषणा _ASM_SN_GDA_H

#समावेश <यंत्र/sn/addrs.h>

#घोषणा GDA_MAGIC	0x58464552

/*
 * GDA Version History
 *
 * Version #	| Change
 * -------------+-------------------------------------------------------
 *	1	| Initial SN0 version
 *	2	| Prom sets g_partid field to the partition number. 0 IS
 *		| a valid partition #.
 */

#घोषणा GDA_VERSION	2	/* Current GDA version # */

#घोषणा G_MAGICOFF	0
#घोषणा G_VERSIONOFF	4
#घोषणा G_PROMOPOFF	6
#घोषणा G_MASTEROFF	8
#घोषणा G_VDSOFF	12
#घोषणा G_HKDNORMOFF	16
#घोषणा G_HKDUTLBOFF	24
#घोषणा G_HKDXUTLBOFF	32
#घोषणा G_PARTIDOFF	40
#घोषणा G_TABLखातापूर्णF	128

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा gda अणु
	u32	g_magic;	/* GDA magic number */
	u16	g_version;	/* Version of this काष्ठाure */
	u16	g_masterid;	/* The NASID:CPUNUM of the master cpu */
	u32	g_promop;	/* Passes requests from the kernel to prom */
	u32	g_vds;		/* Store the भव dipचयनes here */
	व्योम	**g_hooked_norm;/* ptr to pda loc क्रम norm hndlr */
	व्योम	**g_hooked_utlb;/* ptr to pda loc क्रम utlb hndlr */
	व्योम	**g_hooked_xtlb;/* ptr to pda loc क्रम xtlb hndlr */
	पूर्णांक	g_partid;	/* partition id */
	पूर्णांक	g_symmax;	/* Max symbols in name table. */
	व्योम	*g_dbstab;	/* Address of idbg symbol table */
	अक्षर	*g_nametab;	/* Address of idbg name table */
	व्योम	*g_ktext_repmask;
				/* Poपूर्णांकer to a mask of nodes with copies
				 * of the kernel. */
	अक्षर	g_padding[56];	/* pad out to 128 bytes */
	nasid_t g_nasidtable[MAX_NUMNODES]; /* NASID of each node */
पूर्ण gda_t;

#घोषणा GDA ((gda_t*) GDA_ADDR(get_nasid()))

#पूर्ण_अगर /* !__ASSEMBLY__ */
/*
 * Define:	PART_GDA_VERSION
 * Purpose:	Define the minimum version of the GDA required, lower
 *		revisions assume GDA is NOT set up, and पढ़ो partition
 *		inक्रमmation from the board info.
 */
#घोषणा PART_GDA_VERSION	2

/*
 * The following requests can be sent to the PROM during startup.
 */

#घोषणा PROMOP_MAGIC		0x0ead0000
#घोषणा PROMOP_MAGIC_MASK	0x0fff0000

#घोषणा PROMOP_BIST_SHIFT	11
#घोषणा PROMOP_BIST_MASK	(0x3 << 11)

#घोषणा PROMOP_REG		PI_ERR_STACK_ADDR_A

#घोषणा PROMOP_INVALID		(PROMOP_MAGIC | 0x00)
#घोषणा PROMOP_HALT		(PROMOP_MAGIC | 0x10)
#घोषणा PROMOP_POWERDOWN	(PROMOP_MAGIC | 0x20)
#घोषणा PROMOP_RESTART		(PROMOP_MAGIC | 0x30)
#घोषणा PROMOP_REBOOT		(PROMOP_MAGIC | 0x40)
#घोषणा PROMOP_IMODE		(PROMOP_MAGIC | 0x50)

#घोषणा PROMOP_CMD_MASK		0x00f0
#घोषणा PROMOP_OPTIONS_MASK	0xfff0

#घोषणा PROMOP_SKIP_DIAGS	0x0100		/* करोn't bother running diags */
#घोषणा PROMOP_SKIP_MEMINIT	0x0200		/* करोn't bother initing memory */
#घोषणा PROMOP_SKIP_DEVINIT	0x0400		/* करोn't bother initing devices */
#घोषणा PROMOP_BIST1		0x0800		/* keep track of which BIST ran */
#घोषणा PROMOP_BIST2		0x1000		/* keep track of which BIST ran */

#पूर्ण_अगर /* _ASM_SN_GDA_H */
