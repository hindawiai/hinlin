<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Declarations क्रम to Hexagon Virtal Machine.
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ASM_HEXAGON_VM_H
#घोषणा ASM_HEXAGON_VM_H

/*
 * In principle, a Linux kernel क्रम the VM could
 * selectively define the भव inकाष्ठाions
 * as अंतरभूत assembler macros, but क्रम a first pass,
 * we'll use subroutines क्रम both the VM and the native
 * kernels.  It's costing a subroutine call/वापस,
 * but it makes क्रम a single set of entry poपूर्णांकs
 * क्रम tracing/debugging.
 */

#घोषणा HVM_TRAP1_VMVERSION		0
#घोषणा HVM_TRAP1_VMRTE			1
#घोषणा HVM_TRAP1_VMSETVEC		2
#घोषणा HVM_TRAP1_VMSETIE		3
#घोषणा HVM_TRAP1_VMGETIE		4
#घोषणा HVM_TRAP1_VMINTOP		5
#घोषणा HVM_TRAP1_VMCLRMAP		10
#घोषणा HVM_TRAP1_VMNEWMAP		11
#घोषणा HVM_TRAP1_FORMERLY_VMWIRE	12
#घोषणा HVM_TRAP1_VMCACHE		13
#घोषणा HVM_TRAP1_VMGETTIME		14
#घोषणा HVM_TRAP1_VMSETTIME		15
#घोषणा HVM_TRAP1_VMWAIT		16
#घोषणा HVM_TRAP1_VMYIELD		17
#घोषणा HVM_TRAP1_VMSTART		18
#घोषणा HVM_TRAP1_VMSTOP		19
#घोषणा HVM_TRAP1_VMVPID		20
#घोषणा HVM_TRAP1_VMSETREGS		21
#घोषणा HVM_TRAP1_VMGETREGS		22
#घोषणा HVM_TRAP1_VMTIMEROP		24

#अगर_अघोषित __ASSEMBLY__

क्रमागत VM_CACHE_OPS अणु
	hvmc_icसमाप्त,
	hvmc_dcसमाप्त,
	hvmc_l2समाप्त,
	hvmc_dccleaninva,
	hvmc_icinva,
	hvmc_idsync,
	hvmc_fetch_cfg
पूर्ण;

क्रमागत VM_INT_OPS अणु
	hvmi_nop,
	hvmi_globen,
	hvmi_globdis,
	hvmi_locen,
	hvmi_locdis,
	hvmi_affinity,
	hvmi_get,
	hvmi_peek,
	hvmi_status,
	hvmi_post,
	hvmi_clear
पूर्ण;

बाह्य व्योम _K_VM_event_vector(व्योम);

व्योम __vmrte(व्योम);
दीर्घ __vmsetvec(व्योम *);
दीर्घ __vmsetie(दीर्घ);
दीर्घ __vmgetie(व्योम);
दीर्घ __vmपूर्णांकop(क्रमागत VM_INT_OPS, दीर्घ, दीर्घ, दीर्घ, दीर्घ);
दीर्घ __vmclrmap(व्योम *, अचिन्हित दीर्घ);
दीर्घ __vmnewmap(व्योम *);
दीर्घ __vmcache(क्रमागत VM_CACHE_OPS op, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len);
अचिन्हित दीर्घ दीर्घ __vmसमय_लो(व्योम);
दीर्घ __vmसमय_रखो(अचिन्हित दीर्घ दीर्घ);
दीर्घ __vmstart(व्योम *, व्योम *);
व्योम __vmstop(व्योम);
दीर्घ __vmरुको(व्योम);
व्योम __vmyield(व्योम);
दीर्घ __vmvpid(व्योम);

अटल अंतरभूत दीर्घ __vmcache_icसमाप्त(व्योम)
अणु
	वापस __vmcache(hvmc_icसमाप्त, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmcache_dcसमाप्त(व्योम)
अणु
	वापस __vmcache(hvmc_dcसमाप्त, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmcache_l2समाप्त(व्योम)
अणु
	वापस __vmcache(hvmc_l2समाप्त, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmcache_dccleaninva(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस __vmcache(hvmc_dccleaninva, addr, len);
पूर्ण

अटल अंतरभूत दीर्घ __vmcache_icinva(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस __vmcache(hvmc_icinva, addr, len);
पूर्ण

अटल अंतरभूत दीर्घ __vmcache_idsync(अचिन्हित दीर्घ addr,
					   अचिन्हित दीर्घ len)
अणु
	वापस __vmcache(hvmc_idsync, addr, len);
पूर्ण

अटल अंतरभूत दीर्घ __vmcache_fetch_cfg(अचिन्हित दीर्घ val)
अणु
	वापस __vmcache(hvmc_fetch_cfg, val, 0);
पूर्ण

/* पूर्णांकerrupt operations  */

अटल अंतरभूत दीर्घ __vmपूर्णांकop_nop(व्योम)
अणु
	वापस __vmपूर्णांकop(hvmi_nop, 0, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_globen(दीर्घ i)
अणु
	वापस __vmपूर्णांकop(hvmi_globen, i, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_globdis(दीर्घ i)
अणु
	वापस __vmपूर्णांकop(hvmi_globdis, i, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_locen(दीर्घ i)
अणु
	वापस __vmपूर्णांकop(hvmi_locen, i, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_locdis(दीर्घ i)
अणु
	वापस __vmपूर्णांकop(hvmi_locdis, i, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_affinity(दीर्घ i, दीर्घ cpu)
अणु
	वापस __vmपूर्णांकop(hvmi_affinity, i, cpu, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_get(व्योम)
अणु
	वापस __vmपूर्णांकop(hvmi_get, 0, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_peek(व्योम)
अणु
	वापस __vmपूर्णांकop(hvmi_peek, 0, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_status(दीर्घ i)
अणु
	वापस __vmपूर्णांकop(hvmi_status, i, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_post(दीर्घ i)
अणु
	वापस __vmपूर्णांकop(hvmi_post, i, 0, 0, 0);
पूर्ण

अटल अंतरभूत दीर्घ __vmपूर्णांकop_clear(दीर्घ i)
अणु
	वापस __vmपूर्णांकop(hvmi_clear, i, 0, 0, 0);
पूर्ण

#अन्यथा /* Only assembly code should reference these */

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Constants क्रम भव inकाष्ठाion parameters and वापस values
 */

/* vmnewmap arguments */

#घोषणा VM_TRANS_TYPE_LINEAR 0
#घोषणा VM_TRANS_TYPE_TABLE 1
#घोषणा VM_TLB_INVALIDATE_FALSE 0
#घोषणा VM_TLB_INVALIDATE_TRUE 1

/* vmsetie arguments */

#घोषणा VM_INT_DISABLE	0
#घोषणा VM_INT_ENABLE	1

/* vmsetimask arguments */

#घोषणा VM_INT_UNMASK	0
#घोषणा VM_INT_MASK	1

#घोषणा VM_NEWMAP_TYPE_LINEAR	0
#घोषणा VM_NEWMAP_TYPE_PGTABLES	1


/*
 * Event Record definitions useful to both C and Assembler
 */

/* VMEST Layout */

#घोषणा HVM_VMEST_UM_SFT	31
#घोषणा HVM_VMEST_UM_MSK	1
#घोषणा HVM_VMEST_IE_SFT	30
#घोषणा HVM_VMEST_IE_MSK	1
#घोषणा HVM_VMEST_SS_SFT	29
#घोषणा HVM_VMEST_SS_MSK	1
#घोषणा HVM_VMEST_EVENTNUM_SFT	16
#घोषणा HVM_VMEST_EVENTNUM_MSK	0xff
#घोषणा HVM_VMEST_CAUSE_SFT	0
#घोषणा HVM_VMEST_CAUSE_MSK	0xffff

/*
 * The initial program माला_लो to find a प्रणाली environment descriptor
 * on its stack when it begins execution. The first word is a version
 * code to indicate what is there.  Zero means nothing more.
 */

#घोषणा HEXAGON_VM_SED_शून्य	0

/*
 * Event numbers क्रम vector binding
 */

#घोषणा HVM_EV_RESET		0
#घोषणा HVM_EV_MACHCHECK	1
#घोषणा HVM_EV_GENEX		2
#घोषणा HVM_EV_TRAP		8
#घोषणा HVM_EV_INTR		15
/* These shoud be nuked as soon as we know the VM is up to spec v0.1.1 */
#घोषणा HVM_EV_INTR_0		16
#घोषणा HVM_MAX_INTR		240

/*
 * Cause values क्रम General Exception
 */

#घोषणा HVM_GE_C_BUS	0x01
#घोषणा HVM_GE_C_XPROT	0x11
#घोषणा HVM_GE_C_XUSER	0x14
#घोषणा HVM_GE_C_INVI	0x15
#घोषणा HVM_GE_C_PRIVI	0x1B
#घोषणा HVM_GE_C_XMAL	0x1C
#घोषणा HVM_GE_C_WREG	0x1D
#घोषणा HVM_GE_C_PCAL	0x1E
#घोषणा HVM_GE_C_RMAL	0x20
#घोषणा HVM_GE_C_WMAL	0x21
#घोषणा HVM_GE_C_RPROT	0x22
#घोषणा HVM_GE_C_WPROT	0x23
#घोषणा HVM_GE_C_RUSER	0x24
#घोषणा HVM_GE_C_WUSER	0x25
#घोषणा HVM_GE_C_CACHE	0x28

/*
 * Cause codes क्रम Machine Check
 */

#घोषणा	HVM_MCHK_C_DOWN		0x00
#घोषणा	HVM_MCHK_C_BADSP	0x01
#घोषणा	HVM_MCHK_C_BADEX	0x02
#घोषणा	HVM_MCHK_C_BADPT	0x03
#घोषणा	HVM_MCHK_C_REGWR	0x29

#पूर्ण_अगर
