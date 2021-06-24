<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2013 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_MIPS_CPS_H__
# error Please include यंत्र/mips-cps.h rather than यंत्र/mips-cpc.h
#पूर्ण_अगर

#अगर_अघोषित __MIPS_ASM_MIPS_CPC_H__
#घोषणा __MIPS_ASM_MIPS_CPC_H__

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>

/* The base address of the CPC रेजिस्टरs */
बाह्य व्योम __iomem *mips_cpc_base;

/**
 * mips_cpc_शेष_phys_base - retrieve the शेष physical base address of
 *                              the CPC
 *
 * Returns the शेष physical base address of the Cluster Power Controller
 * memory mapped रेजिस्टरs. This is platक्रमm dependant & must thereक्रमe be
 * implemented per-platक्रमm.
 */
बाह्य phys_addr_t mips_cpc_शेष_phys_base(व्योम);

/**
 * mips_cpc_probe - probe क्रम a Cluster Power Controller
 *
 * Attempt to detect the presence of a Cluster Power Controller. Returns 0 अगर
 * a CPC is successfully detected, अन्यथा -त्रुटि_सं.
 */
#अगर_घोषित CONFIG_MIPS_CPC
बाह्य पूर्णांक mips_cpc_probe(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक mips_cpc_probe(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

/**
 * mips_cpc_present - determine whether a Cluster Power Controller is present
 *
 * Returns true अगर a CPC is present in the प्रणाली, अन्यथा false.
 */
अटल अंतरभूत bool mips_cpc_present(व्योम)
अणु
#अगर_घोषित CONFIG_MIPS_CPC
	वापस mips_cpc_base != शून्य;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/* Offsets from the CPC base address to various control blocks */
#घोषणा MIPS_CPC_GCB_OFS	0x0000
#घोषणा MIPS_CPC_CLCB_OFS	0x2000
#घोषणा MIPS_CPC_COCB_OFS	0x4000

#घोषणा CPC_ACCESSOR_RO(sz, off, name)					\
	CPS_ACCESSOR_RO(cpc, sz, MIPS_CPC_GCB_OFS + off, name)		\
	CPS_ACCESSOR_RO(cpc, sz, MIPS_CPC_COCB_OFS + off, redir_##name)

#घोषणा CPC_ACCESSOR_RW(sz, off, name)					\
	CPS_ACCESSOR_RW(cpc, sz, MIPS_CPC_GCB_OFS + off, name)		\
	CPS_ACCESSOR_RW(cpc, sz, MIPS_CPC_COCB_OFS + off, redir_##name)

#घोषणा CPC_CX_ACCESSOR_RO(sz, off, name)				\
	CPS_ACCESSOR_RO(cpc, sz, MIPS_CPC_CLCB_OFS + off, cl_##name)	\
	CPS_ACCESSOR_RO(cpc, sz, MIPS_CPC_COCB_OFS + off, co_##name)

#घोषणा CPC_CX_ACCESSOR_RW(sz, off, name)				\
	CPS_ACCESSOR_RW(cpc, sz, MIPS_CPC_CLCB_OFS + off, cl_##name)	\
	CPS_ACCESSOR_RW(cpc, sz, MIPS_CPC_COCB_OFS + off, co_##name)

/* CPC_ACCESS - Control core/IOCU access to CPC रेजिस्टरs prior to CM 3 */
CPC_ACCESSOR_RW(32, 0x000, access)

/* CPC_SEQDEL - Configure delays between command sequencer steps */
CPC_ACCESSOR_RW(32, 0x008, seqdel)

/* CPC_RAIL - Configure the delay from rail घातer-up to stability */
CPC_ACCESSOR_RW(32, 0x010, rail)

/* CPC_RESETLEN - Configure the length of reset sequences */
CPC_ACCESSOR_RW(32, 0x018, resetlen)

/* CPC_REVISION - Indicates the revisison of the CPC */
CPC_ACCESSOR_RO(32, 0x020, revision)

/* CPC_PWRUP_CTL - Control घातer to the Coherence Manager (CM) */
CPC_ACCESSOR_RW(32, 0x030, pwrup_ctl)
#घोषणा CPC_PWRUP_CTL_CM_PWRUP			BIT(0)

/* CPC_CONFIG - Mirrors GCR_CONFIG */
CPC_ACCESSOR_RW(64, 0x138, config)

/* CPC_SYS_CONFIG - Control cluster endianness */
CPC_ACCESSOR_RW(32, 0x140, sys_config)
#घोषणा CPC_SYS_CONFIG_BE_IMMEDIATE		BIT(2)
#घोषणा CPC_SYS_CONFIG_BE_STATUS		BIT(1)
#घोषणा CPC_SYS_CONFIG_BE			BIT(0)

/* CPC_Cx_CMD - Inकाष्ठा the CPC to take action on a core */
CPC_CX_ACCESSOR_RW(32, 0x000, cmd)
#घोषणा CPC_Cx_CMD				GENMASK(3, 0)
#घोषणा  CPC_Cx_CMD_CLOCKOFF			0x1
#घोषणा  CPC_Cx_CMD_PWRDOWN			0x2
#घोषणा  CPC_Cx_CMD_PWRUP			0x3
#घोषणा  CPC_Cx_CMD_RESET			0x4

/* CPC_Cx_STAT_CONF - Indicates core configuration & state */
CPC_CX_ACCESSOR_RW(32, 0x008, stat_conf)
#घोषणा CPC_Cx_STAT_CONF_PWRUPE			BIT(23)
#घोषणा CPC_Cx_STAT_CONF_SEQSTATE		GENMASK(22, 19)
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_D0		0x0
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_U0		0x1
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_U1		0x2
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_U2		0x3
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_U3		0x4
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_U4		0x5
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_U5		0x6
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_U6		0x7
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_D1		0x8
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_D3		0x9
#घोषणा  CPC_Cx_STAT_CONF_SEQSTATE_D2		0xa
#घोषणा CPC_Cx_STAT_CONF_CLKGAT_IMPL		BIT(17)
#घोषणा CPC_Cx_STAT_CONF_PWRDN_IMPL		BIT(16)
#घोषणा CPC_Cx_STAT_CONF_EJTAG_PROBE		BIT(15)

/* CPC_Cx_OTHER - Configure the core-other रेजिस्टर block prior to CM 3 */
CPC_CX_ACCESSOR_RW(32, 0x010, other)
#घोषणा CPC_Cx_OTHER_CORENUM			GENMASK(23, 16)

/* CPC_Cx_VP_STOP - Stop Virtual Processors (VPs) within a core from running */
CPC_CX_ACCESSOR_RW(32, 0x020, vp_stop)

/* CPC_Cx_VP_START - Start Virtual Processors (VPs) within a core running */
CPC_CX_ACCESSOR_RW(32, 0x028, vp_run)

/* CPC_Cx_VP_RUNNING - Indicate which Virtual Processors (VPs) are running */
CPC_CX_ACCESSOR_RW(32, 0x030, vp_running)

/* CPC_Cx_CONFIG - Mirrors GCR_Cx_CONFIG */
CPC_CX_ACCESSOR_RW(32, 0x090, config)

#अगर_घोषित CONFIG_MIPS_CPC

/**
 * mips_cpc_lock_other - lock access to another core
 * core: the other core to be accessed
 *
 * Call beक्रमe operating upon a core via the 'other' रेजिस्टर region in
 * order to prevent the region being moved during access. Must be called
 * within the bounds of a mips_cm_अणुlock,unlockपूर्ण_other pair, and followed
 * by a call to mips_cpc_unlock_other.
 */
बाह्य व्योम mips_cpc_lock_other(अचिन्हित पूर्णांक core);

/**
 * mips_cpc_unlock_other - unlock access to another core
 *
 * Call after operating upon another core via the 'other' रेजिस्टर region.
 * Must be called after mips_cpc_lock_other.
 */
बाह्य व्योम mips_cpc_unlock_other(व्योम);

#अन्यथा /* !CONFIG_MIPS_CPC */

अटल अंतरभूत व्योम mips_cpc_lock_other(अचिन्हित पूर्णांक core) अणु पूर्ण
अटल अंतरभूत व्योम mips_cpc_unlock_other(व्योम) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_MIPS_CPC */

#पूर्ण_अगर /* __MIPS_ASM_MIPS_CPC_H__ */
