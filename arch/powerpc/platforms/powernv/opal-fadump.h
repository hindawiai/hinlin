<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Firmware-Assisted Dump support on POWER platक्रमm (OPAL).
 *
 * Copyright 2019, Hari Bathini, IBM Corporation.
 */

#अगर_अघोषित _POWERNV_OPAL_FADUMP_H
#घोषणा _POWERNV_OPAL_FADUMP_H

#समावेश <यंत्र/reg.h>

/*
 * With kernel & initrd loaded at 512MB (with 256MB size), enक्रमce a minimum
 * boot memory size of 768MB to ensure f/w loading kernel and initrd करोesn't
 * mess with crash'ed kernel's memory during MPIPL.
 */
#घोषणा OPAL_FADUMP_MIN_BOOT_MEM		(0x30000000UL)

/*
 * OPAL FADump metadata काष्ठाure क्रमmat version
 *
 * OPAL FADump kernel metadata काष्ठाure stores kernel metadata needed to
 * रेजिस्टर-क्रम/process crash dump. Format version is used to keep a tab on
 * the changes in the काष्ठाure क्रमmat. The changes, अगर any, to the क्रमmat
 * are expected to be minimal and backward compatible.
 */
#घोषणा OPAL_FADUMP_VERSION			0x1

/*
 * OPAL FADump kernel metadata
 *
 * The address of this काष्ठाure will be रेजिस्टरed with f/w क्रम retrieving
 * and processing during crash dump.
 */
काष्ठा opal_fadump_mem_काष्ठा अणु
	u8	version;
	u8	reserved[3];
	u16	region_cnt;		/* number of regions */
	u16	रेजिस्टरed_regions;	/* Regions रेजिस्टरed क्रम MPIPL */
	u64	fadumphdr_addr;
	काष्ठा opal_mpipl_region	rgn[FADUMP_MAX_MEM_REGS];
पूर्ण __packed;

/*
 * CPU state data
 *
 * CPU state data inक्रमmation is provided by f/w. The क्रमmat क्रम this data
 * is defined in the HDAT spec. Version is used to keep a tab on the changes
 * in this CPU state data क्रमmat. Changes to this क्रमmat are unlikely, but
 * अगर there are any changes, please refer to latest HDAT specअगरication.
 */
#घोषणा HDAT_FADUMP_CPU_DATA_VER		1

#घोषणा HDAT_FADUMP_CORE_INACTIVE		(0x0F)

/* HDAT thपढ़ो header क्रम रेजिस्टर entries */
काष्ठा hdat_fadump_thपढ़ो_hdr अणु
	__be32  pir;
	/* 0x00 - 0x0F - The corresponding stop state of the core */
	u8      core_state;
	u8      reserved[3];

	__be32	offset;	/* Offset to Register Entries array */
	__be32	ecnt;	/* Number of entries */
	__be32	esize;	/* Alloc size of each array entry in bytes */
	__be32	eactsz;	/* Actual size of each array entry in bytes */
पूर्ण __packed;

/* Register types populated by f/w */
#घोषणा HDAT_FADUMP_REG_TYPE_GPR		0x01
#घोषणा HDAT_FADUMP_REG_TYPE_SPR		0x02

/* ID numbers used by f/w जबतक populating certain रेजिस्टरs */
#घोषणा HDAT_FADUMP_REG_ID_NIP			0x7D0
#घोषणा HDAT_FADUMP_REG_ID_MSR			0x7D1
#घोषणा HDAT_FADUMP_REG_ID_CCR			0x7D2

/* HDAT रेजिस्टर entry. */
काष्ठा hdat_fadump_reg_entry अणु
	__be32		reg_type;
	__be32		reg_num;
	__be64		reg_val;
पूर्ण __packed;

अटल अंतरभूत व्योम opal_fadump_set_regval_regnum(काष्ठा pt_regs *regs,
						 u32 reg_type, u32 reg_num,
						 u64 reg_val)
अणु
	अगर (reg_type == HDAT_FADUMP_REG_TYPE_GPR) अणु
		अगर (reg_num < 32)
			regs->gpr[reg_num] = reg_val;
		वापस;
	पूर्ण

	चयन (reg_num) अणु
	हाल SPRN_CTR:
		regs->ctr = reg_val;
		अवरोध;
	हाल SPRN_LR:
		regs->link = reg_val;
		अवरोध;
	हाल SPRN_XER:
		regs->xer = reg_val;
		अवरोध;
	हाल SPRN_DAR:
		regs->dar = reg_val;
		अवरोध;
	हाल SPRN_DSISR:
		regs->dsisr = reg_val;
		अवरोध;
	हाल HDAT_FADUMP_REG_ID_NIP:
		regs->nip = reg_val;
		अवरोध;
	हाल HDAT_FADUMP_REG_ID_MSR:
		regs->msr = reg_val;
		अवरोध;
	हाल HDAT_FADUMP_REG_ID_CCR:
		regs->ccr = reg_val;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम opal_fadump_पढ़ो_regs(अक्षर *bufp, अचिन्हित पूर्णांक regs_cnt,
					 अचिन्हित पूर्णांक reg_entry_size,
					 bool cpu_endian,
					 काष्ठा pt_regs *regs)
अणु
	काष्ठा hdat_fadump_reg_entry *reg_entry;
	u64 val;
	पूर्णांक i;

	स_रखो(regs, 0, माप(काष्ठा pt_regs));

	क्रम (i = 0; i < regs_cnt; i++, bufp += reg_entry_size) अणु
		reg_entry = (काष्ठा hdat_fadump_reg_entry *)bufp;
		val = (cpu_endian ? be64_to_cpu(reg_entry->reg_val) :
		       reg_entry->reg_val);
		opal_fadump_set_regval_regnum(regs,
					      be32_to_cpu(reg_entry->reg_type),
					      be32_to_cpu(reg_entry->reg_num),
					      val);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _POWERNV_OPAL_FADUMP_H */
