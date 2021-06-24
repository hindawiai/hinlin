<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Intel Sandy Bridge -EN/-EP/-EX Memory Controller kernel module
 *
 * This driver supports the memory controllers found on the Intel
 * processor family Sandy Bridge.
 *
 * Copyright (c) 2011 by:
 *	 Mauro Carvalho Chehab
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/edac.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/smp.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/math64.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mce.h>

#समावेश "edac_module.h"

/* Static vars */
अटल LIST_HEAD(sbridge_edac_list);

/*
 * Alter this version क्रम the module when modअगरications are made
 */
#घोषणा SBRIDGE_REVISION    " Ver: 1.1.2 "
#घोषणा EDAC_MOD_STR	    "sb_edac"

/*
 * Debug macros
 */
#घोषणा sbridge_prपूर्णांकk(level, fmt, arg...)			\
	edac_prपूर्णांकk(level, "sbridge", fmt, ##arg)

#घोषणा sbridge_mc_prपूर्णांकk(mci, level, fmt, arg...)		\
	edac_mc_chipset_prपूर्णांकk(mci, level, "sbridge", fmt, ##arg)

/*
 * Get a bit field at रेजिस्टर value <v>, from bit <lo> to bit <hi>
 */
#घोषणा GET_BITFIELD(v, lo, hi)	\
	(((v) & GENMASK_ULL(hi, lo)) >> (lo))

/* Devices 12 Function 6, Offsets 0x80 to 0xcc */
अटल स्थिर u32 sbridge_dram_rule[] = अणु
	0x80, 0x88, 0x90, 0x98, 0xa0,
	0xa8, 0xb0, 0xb8, 0xc0, 0xc8,
पूर्ण;

अटल स्थिर u32 ibridge_dram_rule[] = अणु
	0x60, 0x68, 0x70, 0x78, 0x80,
	0x88, 0x90, 0x98, 0xa0,	0xa8,
	0xb0, 0xb8, 0xc0, 0xc8, 0xd0,
	0xd8, 0xe0, 0xe8, 0xf0, 0xf8,
पूर्ण;

अटल स्थिर u32 knl_dram_rule[] = अणु
	0x60, 0x68, 0x70, 0x78, 0x80, /* 0-4 */
	0x88, 0x90, 0x98, 0xa0, 0xa8, /* 5-9 */
	0xb0, 0xb8, 0xc0, 0xc8, 0xd0, /* 10-14 */
	0xd8, 0xe0, 0xe8, 0xf0, 0xf8, /* 15-19 */
	0x100, 0x108, 0x110, 0x118,   /* 20-23 */
पूर्ण;

#घोषणा DRAM_RULE_ENABLE(reg)	GET_BITFIELD(reg, 0,  0)
#घोषणा A7MODE(reg)		GET_BITFIELD(reg, 26, 26)

अटल अक्षर *show_dram_attr(u32 attr)
अणु
	चयन (attr) अणु
		हाल 0:
			वापस "DRAM";
		हाल 1:
			वापस "MMCFG";
		हाल 2:
			वापस "NXM";
		शेष:
			वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर u32 sbridge_पूर्णांकerleave_list[] = अणु
	0x84, 0x8c, 0x94, 0x9c, 0xa4,
	0xac, 0xb4, 0xbc, 0xc4, 0xcc,
पूर्ण;

अटल स्थिर u32 ibridge_पूर्णांकerleave_list[] = अणु
	0x64, 0x6c, 0x74, 0x7c, 0x84,
	0x8c, 0x94, 0x9c, 0xa4, 0xac,
	0xb4, 0xbc, 0xc4, 0xcc, 0xd4,
	0xdc, 0xe4, 0xec, 0xf4, 0xfc,
पूर्ण;

अटल स्थिर u32 knl_पूर्णांकerleave_list[] = अणु
	0x64, 0x6c, 0x74, 0x7c, 0x84, /* 0-4 */
	0x8c, 0x94, 0x9c, 0xa4, 0xac, /* 5-9 */
	0xb4, 0xbc, 0xc4, 0xcc, 0xd4, /* 10-14 */
	0xdc, 0xe4, 0xec, 0xf4, 0xfc, /* 15-19 */
	0x104, 0x10c, 0x114, 0x11c,   /* 20-23 */
पूर्ण;
#घोषणा MAX_INTERLEAVE							\
	(max_t(अचिन्हित पूर्णांक, ARRAY_SIZE(sbridge_पूर्णांकerleave_list),	\
	       max_t(अचिन्हित पूर्णांक, ARRAY_SIZE(ibridge_पूर्णांकerleave_list),	\
		     ARRAY_SIZE(knl_पूर्णांकerleave_list))))

काष्ठा पूर्णांकerleave_pkg अणु
	अचिन्हित अक्षर start;
	अचिन्हित अक्षर end;
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकerleave_pkg sbridge_पूर्णांकerleave_pkg[] = अणु
	अणु 0, 2 पूर्ण,
	अणु 3, 5 पूर्ण,
	अणु 8, 10 पूर्ण,
	अणु 11, 13 पूर्ण,
	अणु 16, 18 पूर्ण,
	अणु 19, 21 पूर्ण,
	अणु 24, 26 पूर्ण,
	अणु 27, 29 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकerleave_pkg ibridge_पूर्णांकerleave_pkg[] = अणु
	अणु 0, 3 पूर्ण,
	अणु 4, 7 पूर्ण,
	अणु 8, 11 पूर्ण,
	अणु 12, 15 पूर्ण,
	अणु 16, 19 पूर्ण,
	अणु 20, 23 पूर्ण,
	अणु 24, 27 पूर्ण,
	अणु 28, 31 पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक sad_pkg(स्थिर काष्ठा पूर्णांकerleave_pkg *table, u32 reg,
			  पूर्णांक पूर्णांकerleave)
अणु
	वापस GET_BITFIELD(reg, table[पूर्णांकerleave].start,
			    table[पूर्णांकerleave].end);
पूर्ण

/* Devices 12 Function 7 */

#घोषणा TOLM		0x80
#घोषणा TOHM		0x84
#घोषणा HASWELL_TOLM	0xd0
#घोषणा HASWELL_TOHM_0	0xd4
#घोषणा HASWELL_TOHM_1	0xd8
#घोषणा KNL_TOLM	0xd0
#घोषणा KNL_TOHM_0	0xd4
#घोषणा KNL_TOHM_1	0xd8

#घोषणा GET_TOLM(reg)		((GET_BITFIELD(reg, 0,  3) << 28) | 0x3ffffff)
#घोषणा GET_TOHM(reg)		((GET_BITFIELD(reg, 0, 20) << 25) | 0x3ffffff)

/* Device 13 Function 6 */

#घोषणा SAD_TARGET	0xf0

#घोषणा SOURCE_ID(reg)		GET_BITFIELD(reg, 9, 11)

#घोषणा SOURCE_ID_KNL(reg)	GET_BITFIELD(reg, 12, 14)

#घोषणा SAD_CONTROL	0xf4

/* Device 14 function 0 */

अटल स्थिर u32 tad_dram_rule[] = अणु
	0x40, 0x44, 0x48, 0x4c,
	0x50, 0x54, 0x58, 0x5c,
	0x60, 0x64, 0x68, 0x6c,
पूर्ण;
#घोषणा MAX_TAD	ARRAY_SIZE(tad_dram_rule)

#घोषणा TAD_LIMIT(reg)		((GET_BITFIELD(reg, 12, 31) << 26) | 0x3ffffff)
#घोषणा TAD_SOCK(reg)		GET_BITFIELD(reg, 10, 11)
#घोषणा TAD_CH(reg)		GET_BITFIELD(reg,  8,  9)
#घोषणा TAD_TGT3(reg)		GET_BITFIELD(reg,  6,  7)
#घोषणा TAD_TGT2(reg)		GET_BITFIELD(reg,  4,  5)
#घोषणा TAD_TGT1(reg)		GET_BITFIELD(reg,  2,  3)
#घोषणा TAD_TGT0(reg)		GET_BITFIELD(reg,  0,  1)

/* Device 15, function 0 */

#घोषणा MCMTR			0x7c
#घोषणा KNL_MCMTR		0x624

#घोषणा IS_ECC_ENABLED(mcmtr)		GET_BITFIELD(mcmtr, 2, 2)
#घोषणा IS_LOCKSTEP_ENABLED(mcmtr)	GET_BITFIELD(mcmtr, 1, 1)
#घोषणा IS_CLOSE_PG(mcmtr)		GET_BITFIELD(mcmtr, 0, 0)

/* Device 15, function 1 */

#घोषणा RASENABLES		0xac
#घोषणा IS_MIRROR_ENABLED(reg)		GET_BITFIELD(reg, 0, 0)

/* Device 15, functions 2-5 */

अटल स्थिर पूर्णांक mtr_regs[] = अणु
	0x80, 0x84, 0x88,
पूर्ण;

अटल स्थिर पूर्णांक knl_mtr_reg = 0xb60;

#घोषणा RANK_DISABLE(mtr)		GET_BITFIELD(mtr, 16, 19)
#घोषणा IS_DIMM_PRESENT(mtr)		GET_BITFIELD(mtr, 14, 14)
#घोषणा RANK_CNT_BITS(mtr)		GET_BITFIELD(mtr, 12, 13)
#घोषणा RANK_WIDTH_BITS(mtr)		GET_BITFIELD(mtr, 2, 4)
#घोषणा COL_WIDTH_BITS(mtr)		GET_BITFIELD(mtr, 0, 1)

अटल स्थिर u32 tad_ch_nilv_offset[] = अणु
	0x90, 0x94, 0x98, 0x9c,
	0xa0, 0xa4, 0xa8, 0xac,
	0xb0, 0xb4, 0xb8, 0xbc,
पूर्ण;
#घोषणा CHN_IDX_OFFSET(reg)		GET_BITFIELD(reg, 28, 29)
#घोषणा TAD_OFFSET(reg)			(GET_BITFIELD(reg,  6, 25) << 26)

अटल स्थिर u32 rir_way_limit[] = अणु
	0x108, 0x10c, 0x110, 0x114, 0x118,
पूर्ण;
#घोषणा MAX_RIR_RANGES ARRAY_SIZE(rir_way_limit)

#घोषणा IS_RIR_VALID(reg)	GET_BITFIELD(reg, 31, 31)
#घोषणा RIR_WAY(reg)		GET_BITFIELD(reg, 28, 29)

#घोषणा MAX_RIR_WAY	8

अटल स्थिर u32 rir_offset[MAX_RIR_RANGES][MAX_RIR_WAY] = अणु
	अणु 0x120, 0x124, 0x128, 0x12c, 0x130, 0x134, 0x138, 0x13c पूर्ण,
	अणु 0x140, 0x144, 0x148, 0x14c, 0x150, 0x154, 0x158, 0x15c पूर्ण,
	अणु 0x160, 0x164, 0x168, 0x16c, 0x170, 0x174, 0x178, 0x17c पूर्ण,
	अणु 0x180, 0x184, 0x188, 0x18c, 0x190, 0x194, 0x198, 0x19c पूर्ण,
	अणु 0x1a0, 0x1a4, 0x1a8, 0x1ac, 0x1b0, 0x1b4, 0x1b8, 0x1bc पूर्ण,
पूर्ण;

#घोषणा RIR_RNK_TGT(type, reg) (((type) == BROADWELL) ? \
	GET_BITFIELD(reg, 20, 23) : GET_BITFIELD(reg, 16, 19))

#घोषणा RIR_OFFSET(type, reg) (((type) == HASWELL || (type) == BROADWELL) ? \
	GET_BITFIELD(reg,  2, 15) : GET_BITFIELD(reg,  2, 14))

/* Device 16, functions 2-7 */

/*
 * FIXME: Implement the error count पढ़ोs directly
 */

#घोषणा RANK_ODD_OV(reg)		GET_BITFIELD(reg, 31, 31)
#घोषणा RANK_ODD_ERR_CNT(reg)		GET_BITFIELD(reg, 16, 30)
#घोषणा RANK_EVEN_OV(reg)		GET_BITFIELD(reg, 15, 15)
#घोषणा RANK_EVEN_ERR_CNT(reg)		GET_BITFIELD(reg,  0, 14)

#अगर 0 /* Currently unused*/
अटल स्थिर u32 correrrcnt[] = अणु
	0x104, 0x108, 0x10c, 0x110,
पूर्ण;

अटल स्थिर u32 correrrthrsld[] = अणु
	0x11c, 0x120, 0x124, 0x128,
पूर्ण;
#पूर्ण_अगर

#घोषणा RANK_ODD_ERR_THRSLD(reg)	GET_BITFIELD(reg, 16, 30)
#घोषणा RANK_EVEN_ERR_THRSLD(reg)	GET_BITFIELD(reg,  0, 14)


/* Device 17, function 0 */

#घोषणा SB_RANK_CFG_A		0x0328

#घोषणा IB_RANK_CFG_A		0x0320

/*
 * sbridge काष्ठाs
 */

#घोषणा NUM_CHANNELS		6	/* Max channels per MC */
#घोषणा MAX_DIMMS		3	/* Max DIMMS per channel */
#घोषणा KNL_MAX_CHAS		38	/* KNL max num. of Cache Home Agents */
#घोषणा KNL_MAX_CHANNELS	6	/* KNL max num. of PCI channels */
#घोषणा KNL_MAX_EDCS		8	/* Embedded DRAM controllers */
#घोषणा CHANNEL_UNSPECIFIED	0xf	/* Intel IA32 SDM 15-14 */

क्रमागत type अणु
	SANDY_BRIDGE,
	IVY_BRIDGE,
	HASWELL,
	BROADWELL,
	KNIGHTS_LANDING,
पूर्ण;

क्रमागत करोमुख्य अणु
	IMC0 = 0,
	IMC1,
	SOCK,
पूर्ण;

क्रमागत mirroring_mode अणु
	NON_MIRRORING,
	ADDR_RANGE_MIRRORING,
	FULL_MIRRORING,
पूर्ण;

काष्ठा sbridge_pvt;
काष्ठा sbridge_info अणु
	क्रमागत type	type;
	u32		mcmtr;
	u32		rankcfgr;
	u64		(*get_tolm)(काष्ठा sbridge_pvt *pvt);
	u64		(*get_tohm)(काष्ठा sbridge_pvt *pvt);
	u64		(*rir_limit)(u32 reg);
	u64		(*sad_limit)(u32 reg);
	u32		(*पूर्णांकerleave_mode)(u32 reg);
	u32		(*dram_attr)(u32 reg);
	स्थिर u32	*dram_rule;
	स्थिर u32	*पूर्णांकerleave_list;
	स्थिर काष्ठा पूर्णांकerleave_pkg *पूर्णांकerleave_pkg;
	u8		max_sad;
	u8		(*get_node_id)(काष्ठा sbridge_pvt *pvt);
	u8		(*get_ha)(u8 bank);
	क्रमागत mem_type	(*get_memory_type)(काष्ठा sbridge_pvt *pvt);
	क्रमागत dev_type	(*get_width)(काष्ठा sbridge_pvt *pvt, u32 mtr);
	काष्ठा pci_dev	*pci_vtd;
पूर्ण;

काष्ठा sbridge_channel अणु
	u32		ranks;
	u32		dimms;
पूर्ण;

काष्ठा pci_id_descr अणु
	पूर्णांक			dev_id;
	पूर्णांक			optional;
	क्रमागत करोमुख्य		करोm;
पूर्ण;

काष्ठा pci_id_table अणु
	स्थिर काष्ठा pci_id_descr	*descr;
	पूर्णांक				n_devs_per_imc;
	पूर्णांक				n_devs_per_sock;
	पूर्णांक				n_imcs_per_sock;
	क्रमागत type			type;
पूर्ण;

काष्ठा sbridge_dev अणु
	काष्ठा list_head	list;
	पूर्णांक			seg;
	u8			bus, mc;
	u8			node_id, source_id;
	काष्ठा pci_dev		**pdev;
	क्रमागत करोमुख्य		करोm;
	पूर्णांक			n_devs;
	पूर्णांक			i_devs;
	काष्ठा mem_ctl_info	*mci;
पूर्ण;

काष्ठा knl_pvt अणु
	काष्ठा pci_dev          *pci_cha[KNL_MAX_CHAS];
	काष्ठा pci_dev          *pci_channel[KNL_MAX_CHANNELS];
	काष्ठा pci_dev          *pci_mc0;
	काष्ठा pci_dev          *pci_mc1;
	काष्ठा pci_dev          *pci_mc0_misc;
	काष्ठा pci_dev          *pci_mc1_misc;
	काष्ठा pci_dev          *pci_mc_info; /* tolm, tohm */
पूर्ण;

काष्ठा sbridge_pvt अणु
	/* Devices per socket */
	काष्ठा pci_dev		*pci_ddrio;
	काष्ठा pci_dev		*pci_sad0, *pci_sad1;
	काष्ठा pci_dev		*pci_br0, *pci_br1;
	/* Devices per memory controller */
	काष्ठा pci_dev		*pci_ha, *pci_ta, *pci_ras;
	काष्ठा pci_dev		*pci_tad[NUM_CHANNELS];

	काष्ठा sbridge_dev	*sbridge_dev;

	काष्ठा sbridge_info	info;
	काष्ठा sbridge_channel	channel[NUM_CHANNELS];

	/* Memory type detection */
	bool			is_cur_addr_mirrored, is_lockstep, is_बंद_pg;
	bool			is_chan_hash;
	क्रमागत mirroring_mode	mirror_mode;

	/* Memory description */
	u64			tolm, tohm;
	काष्ठा knl_pvt knl;
पूर्ण;

#घोषणा PCI_DESCR(device_id, opt, करोमुख्य)	\
	.dev_id = (device_id),		\
	.optional = opt,	\
	.करोm = करोमुख्य

अटल स्थिर काष्ठा pci_id_descr pci_dev_descr_sbridge[] = अणु
		/* Processor Home Agent */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_HA0,   0, IMC0) पूर्ण,

		/* Memory controller */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TA,    0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_RAS,   0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TAD0,  0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TAD1,  0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TAD2,  0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TAD3,  0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_DDRIO, 1, SOCK) पूर्ण,

		/* System Address Decoder */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_SAD0,      0, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_SAD1,      0, SOCK) पूर्ण,

		/* Broadcast Registers */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_SBRIDGE_BR,        0, SOCK) पूर्ण,
पूर्ण;

#घोषणा PCI_ID_TABLE_ENTRY(A, N, M, T) अणु	\
	.descr = A,			\
	.n_devs_per_imc = N,	\
	.n_devs_per_sock = ARRAY_SIZE(A),	\
	.n_imcs_per_sock = M,	\
	.type = T			\
पूर्ण

अटल स्थिर काष्ठा pci_id_table pci_dev_descr_sbridge_table[] = अणु
	PCI_ID_TABLE_ENTRY(pci_dev_descr_sbridge, ARRAY_SIZE(pci_dev_descr_sbridge), 1, SANDY_BRIDGE),
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

/* This changes depending अगर 1HA or 2HA:
 * 1HA:
 *	0x0eb8 (17.0) is DDRIO0
 * 2HA:
 *	0x0ebc (17.4) is DDRIO0
 */
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_1HA_DDRIO0	0x0eb8
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_2HA_DDRIO0	0x0ebc

/* pci ids */
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0		0x0ea0
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TA		0x0ea8
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_RAS		0x0e71
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD0	0x0eaa
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD1	0x0eab
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD2	0x0eac
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD3	0x0ead
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_SAD			0x0ec8
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_BR0			0x0ec9
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_BR1			0x0eca
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1		0x0e60
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TA		0x0e68
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_RAS		0x0e79
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD0	0x0e6a
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD1	0x0e6b
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD2	0x0e6c
#घोषणा PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD3	0x0e6d

अटल स्थिर काष्ठा pci_id_descr pci_dev_descr_ibridge[] = अणु
		/* Processor Home Agent */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0,        0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1,        1, IMC1) पूर्ण,

		/* Memory controller */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TA,     0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_RAS,    0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD0,   0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD1,   0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD2,   0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD3,   0, IMC0) पूर्ण,

		/* Optional, mode 2HA */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TA,     1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_RAS,    1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD0,   1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD1,   1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD2,   1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD3,   1, IMC1) पूर्ण,

	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_1HA_DDRIO0, 1, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_2HA_DDRIO0, 1, SOCK) पूर्ण,

		/* System Address Decoder */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_SAD,            0, SOCK) पूर्ण,

		/* Broadcast Registers */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_BR0,            1, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_IBRIDGE_BR1,            0, SOCK) पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा pci_id_table pci_dev_descr_ibridge_table[] = अणु
	PCI_ID_TABLE_ENTRY(pci_dev_descr_ibridge, 12, 2, IVY_BRIDGE),
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

/* Haswell support */
/* EN processor:
 *	- 1 IMC
 *	- 3 DDR3 channels, 2 DPC per channel
 * EP processor:
 *	- 1 or 2 IMC
 *	- 4 DDR4 channels, 3 DPC per channel
 * EP 4S processor:
 *	- 2 IMC
 *	- 4 DDR4 channels, 3 DPC per channel
 * EX processor:
 *	- 2 IMC
 *	- each IMC पूर्णांकerfaces with a SMI 2 channel
 *	- each SMI channel पूर्णांकerfaces with a scalable memory buffer
 *	- each scalable memory buffer supports 4 DDR3/DDR4 channels, 3 DPC
 */
#घोषणा HASWELL_DDRCRCLKCONTROLS 0xa10 /* Ditto on Broadwell */
#घोषणा HASWELL_HASYSDEFEATURE2 0x84
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_VTD_MISC 0x2f28
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0	0x2fa0
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1	0x2f60
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TA	0x2fa8
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TM	0x2f71
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TA	0x2f68
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TM	0x2f79
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD0 0x2ffc
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD1 0x2ffd
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD0 0x2faa
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD1 0x2fab
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD2 0x2fac
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD3 0x2fad
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD0 0x2f6a
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD1 0x2f6b
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD2 0x2f6c
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD3 0x2f6d
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO0 0x2fbd
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO1 0x2fbf
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO2 0x2fb9
#घोषणा PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO3 0x2fbb
अटल स्थिर काष्ठा pci_id_descr pci_dev_descr_haswell[] = अणु
	/* first item must be the HA */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0,      0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1,      1, IMC1) पूर्ण,

	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TA,   0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TM,   0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD0, 0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD1, 0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD2, 1, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD3, 1, IMC0) पूर्ण,

	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TA,   1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TM,   1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD0, 1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD1, 1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD2, 1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD3, 1, IMC1) पूर्ण,

	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD0, 0, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD1, 0, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO0,   1, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO1,   1, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO2,   1, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO3,   1, SOCK) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_id_table pci_dev_descr_haswell_table[] = अणु
	PCI_ID_TABLE_ENTRY(pci_dev_descr_haswell, 13, 2, HASWELL),
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

/* Knight's Landing Support */
/*
 * KNL's memory channels are swizzled between memory controllers.
 * MC0 is mapped to CH3,4,5 and MC1 is mapped to CH0,1,2
 */
#घोषणा knl_channel_remap(mc, chan) ((mc) ? (chan) : (chan) + 3)

/* Memory controller, TAD tables, error injection - 2-8-0, 2-9-0 (2 of these) */
#घोषणा PCI_DEVICE_ID_INTEL_KNL_IMC_MC       0x7840
/* DRAM channel stuff; bank addrs, dimmmtr, etc.. 2-8-2 - 2-9-4 (6 of these) */
#घोषणा PCI_DEVICE_ID_INTEL_KNL_IMC_CHAN     0x7843
/* kdrwdbu TAD limits/offsets, MCMTR - 2-10-1, 2-11-1 (2 of these) */
#घोषणा PCI_DEVICE_ID_INTEL_KNL_IMC_TA       0x7844
/* CHA broadcast रेजिस्टरs, dram rules - 1-29-0 (1 of these) */
#घोषणा PCI_DEVICE_ID_INTEL_KNL_IMC_SAD0     0x782a
/* SAD target - 1-29-1 (1 of these) */
#घोषणा PCI_DEVICE_ID_INTEL_KNL_IMC_SAD1     0x782b
/* Caching / Home Agent */
#घोषणा PCI_DEVICE_ID_INTEL_KNL_IMC_CHA      0x782c
/* Device with TOLM and TOHM, 0-5-0 (1 of these) */
#घोषणा PCI_DEVICE_ID_INTEL_KNL_IMC_TOLHM    0x7810

/*
 * KNL dअगरfers from SB, IB, and Haswell in that it has multiple
 * instances of the same device with the same device ID, so we handle that
 * by creating as many copies in the table as we expect to find.
 * (Like device ID must be grouped together.)
 */

अटल स्थिर काष्ठा pci_id_descr pci_dev_descr_knl[] = अणु
	[0 ... 1]   = अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_KNL_IMC_MC,    0, IMC0)पूर्ण,
	[2 ... 7]   = अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_KNL_IMC_CHAN,  0, IMC0) पूर्ण,
	[8]	    = अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_KNL_IMC_TA,    0, IMC0) पूर्ण,
	[9]	    = अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_KNL_IMC_TOLHM, 0, IMC0) पूर्ण,
	[10]	    = अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_KNL_IMC_SAD0,  0, SOCK) पूर्ण,
	[11]	    = अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_KNL_IMC_SAD1,  0, SOCK) पूर्ण,
	[12 ... 49] = अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_KNL_IMC_CHA,   0, SOCK) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_id_table pci_dev_descr_knl_table[] = अणु
	PCI_ID_TABLE_ENTRY(pci_dev_descr_knl, ARRAY_SIZE(pci_dev_descr_knl), 1, KNIGHTS_LANDING),
	अणु0,पूर्ण
पूर्ण;

/*
 * Broadwell support
 *
 * DE processor:
 *	- 1 IMC
 *	- 2 DDR3 channels, 2 DPC per channel
 * EP processor:
 *	- 1 or 2 IMC
 *	- 4 DDR4 channels, 3 DPC per channel
 * EP 4S processor:
 *	- 2 IMC
 *	- 4 DDR4 channels, 3 DPC per channel
 * EX processor:
 *	- 2 IMC
 *	- each IMC पूर्णांकerfaces with a SMI 2 channel
 *	- each SMI channel पूर्णांकerfaces with a scalable memory buffer
 *	- each scalable memory buffer supports 4 DDR3/DDR4 channels, 3 DPC
 */
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_VTD_MISC 0x6f28
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0	0x6fa0
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1	0x6f60
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TA	0x6fa8
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TM	0x6f71
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TA	0x6f68
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TM	0x6f79
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_CBO_SAD0 0x6ffc
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_CBO_SAD1 0x6ffd
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD0 0x6faa
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD1 0x6fab
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD2 0x6fac
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD3 0x6fad
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD0 0x6f6a
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD1 0x6f6b
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD2 0x6f6c
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD3 0x6f6d
#घोषणा PCI_DEVICE_ID_INTEL_BROADWELL_IMC_DDRIO0 0x6faf

अटल स्थिर काष्ठा pci_id_descr pci_dev_descr_broadwell[] = अणु
	/* first item must be the HA */
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0,      0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1,      1, IMC1) पूर्ण,

	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TA,   0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TM,   0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD0, 0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD1, 0, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD2, 1, IMC0) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD3, 1, IMC0) पूर्ण,

	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TA,   1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TM,   1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD0, 1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD1, 1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD2, 1, IMC1) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD3, 1, IMC1) पूर्ण,

	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_CBO_SAD0, 0, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_CBO_SAD1, 0, SOCK) पूर्ण,
	अणु PCI_DESCR(PCI_DEVICE_ID_INTEL_BROADWELL_IMC_DDRIO0,   1, SOCK) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_id_table pci_dev_descr_broadwell_table[] = अणु
	PCI_ID_TABLE_ENTRY(pci_dev_descr_broadwell, 10, 2, BROADWELL),
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;


/****************************************************************************
			Ancillary status routines
 ****************************************************************************/

अटल अंतरभूत पूर्णांक numrank(क्रमागत type type, u32 mtr)
अणु
	पूर्णांक ranks = (1 << RANK_CNT_BITS(mtr));
	पूर्णांक max = 4;

	अगर (type == HASWELL || type == BROADWELL || type == KNIGHTS_LANDING)
		max = 8;

	अगर (ranks > max) अणु
		edac_dbg(0, "Invalid number of ranks: %d (max = %i) raw value = %x (%04x)\n",
			 ranks, max, (अचिन्हित पूर्णांक)RANK_CNT_BITS(mtr), mtr);
		वापस -EINVAL;
	पूर्ण

	वापस ranks;
पूर्ण

अटल अंतरभूत पूर्णांक numrow(u32 mtr)
अणु
	पूर्णांक rows = (RANK_WIDTH_BITS(mtr) + 12);

	अगर (rows < 13 || rows > 18) अणु
		edac_dbg(0, "Invalid number of rows: %d (should be between 14 and 17) raw value = %x (%04x)\n",
			 rows, (अचिन्हित पूर्णांक)RANK_WIDTH_BITS(mtr), mtr);
		वापस -EINVAL;
	पूर्ण

	वापस 1 << rows;
पूर्ण

अटल अंतरभूत पूर्णांक numcol(u32 mtr)
अणु
	पूर्णांक cols = (COL_WIDTH_BITS(mtr) + 10);

	अगर (cols > 12) अणु
		edac_dbg(0, "Invalid number of cols: %d (max = 4) raw value = %x (%04x)\n",
			 cols, (अचिन्हित पूर्णांक)COL_WIDTH_BITS(mtr), mtr);
		वापस -EINVAL;
	पूर्ण

	वापस 1 << cols;
पूर्ण

अटल काष्ठा sbridge_dev *get_sbridge_dev(पूर्णांक seg, u8 bus, क्रमागत करोमुख्य करोm,
					   पूर्णांक multi_bus,
					   काष्ठा sbridge_dev *prev)
अणु
	काष्ठा sbridge_dev *sbridge_dev;

	/*
	 * If we have devices scattered across several busses that pertain
	 * to the same memory controller, we'll lump them all together.
	 */
	अगर (multi_bus) अणु
		वापस list_first_entry_or_null(&sbridge_edac_list,
				काष्ठा sbridge_dev, list);
	पूर्ण

	sbridge_dev = list_entry(prev ? prev->list.next
				      : sbridge_edac_list.next, काष्ठा sbridge_dev, list);

	list_क्रम_each_entry_from(sbridge_dev, &sbridge_edac_list, list) अणु
		अगर ((sbridge_dev->seg == seg) && (sbridge_dev->bus == bus) &&
				(करोm == SOCK || करोm == sbridge_dev->करोm))
			वापस sbridge_dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sbridge_dev *alloc_sbridge_dev(पूर्णांक seg, u8 bus, क्रमागत करोमुख्य करोm,
					     स्थिर काष्ठा pci_id_table *table)
अणु
	काष्ठा sbridge_dev *sbridge_dev;

	sbridge_dev = kzalloc(माप(*sbridge_dev), GFP_KERNEL);
	अगर (!sbridge_dev)
		वापस शून्य;

	sbridge_dev->pdev = kसुस्मृति(table->n_devs_per_imc,
				    माप(*sbridge_dev->pdev),
				    GFP_KERNEL);
	अगर (!sbridge_dev->pdev) अणु
		kमुक्त(sbridge_dev);
		वापस शून्य;
	पूर्ण

	sbridge_dev->seg = seg;
	sbridge_dev->bus = bus;
	sbridge_dev->करोm = करोm;
	sbridge_dev->n_devs = table->n_devs_per_imc;
	list_add_tail(&sbridge_dev->list, &sbridge_edac_list);

	वापस sbridge_dev;
पूर्ण

अटल व्योम मुक्त_sbridge_dev(काष्ठा sbridge_dev *sbridge_dev)
अणु
	list_del(&sbridge_dev->list);
	kमुक्त(sbridge_dev->pdev);
	kमुक्त(sbridge_dev);
पूर्ण

अटल u64 sbridge_get_tolm(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;

	/* Address range is 32:28 */
	pci_पढ़ो_config_dword(pvt->pci_sad1, TOLM, &reg);
	वापस GET_TOLM(reg);
पूर्ण

अटल u64 sbridge_get_tohm(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;

	pci_पढ़ो_config_dword(pvt->pci_sad1, TOHM, &reg);
	वापस GET_TOHM(reg);
पूर्ण

अटल u64 ibridge_get_tolm(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;

	pci_पढ़ो_config_dword(pvt->pci_br1, TOLM, &reg);

	वापस GET_TOLM(reg);
पूर्ण

अटल u64 ibridge_get_tohm(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;

	pci_पढ़ो_config_dword(pvt->pci_br1, TOHM, &reg);

	वापस GET_TOHM(reg);
पूर्ण

अटल u64 rir_limit(u32 reg)
अणु
	वापस ((u64)GET_BITFIELD(reg,  1, 10) << 29) | 0x1fffffff;
पूर्ण

अटल u64 sad_limit(u32 reg)
अणु
	वापस (GET_BITFIELD(reg, 6, 25) << 26) | 0x3ffffff;
पूर्ण

अटल u32 पूर्णांकerleave_mode(u32 reg)
अणु
	वापस GET_BITFIELD(reg, 1, 1);
पूर्ण

अटल u32 dram_attr(u32 reg)
अणु
	वापस GET_BITFIELD(reg, 2, 3);
पूर्ण

अटल u64 knl_sad_limit(u32 reg)
अणु
	वापस (GET_BITFIELD(reg, 7, 26) << 26) | 0x3ffffff;
पूर्ण

अटल u32 knl_पूर्णांकerleave_mode(u32 reg)
अणु
	वापस GET_BITFIELD(reg, 1, 2);
पूर्ण

अटल स्थिर अक्षर * स्थिर knl_पूर्णांकlv_mode[] = अणु
	"[8:6]", "[10:8]", "[14:12]", "[32:30]"
पूर्ण;

अटल स्थिर अक्षर *get_पूर्णांकlv_mode_str(u32 reg, क्रमागत type t)
अणु
	अगर (t == KNIGHTS_LANDING)
		वापस knl_पूर्णांकlv_mode[knl_पूर्णांकerleave_mode(reg)];
	अन्यथा
		वापस पूर्णांकerleave_mode(reg) ? "[8:6]" : "[8:6]XOR[18:16]";
पूर्ण

अटल u32 dram_attr_knl(u32 reg)
अणु
	वापस GET_BITFIELD(reg, 3, 4);
पूर्ण


अटल क्रमागत mem_type get_memory_type(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;
	क्रमागत mem_type mtype;

	अगर (pvt->pci_ddrio) अणु
		pci_पढ़ो_config_dword(pvt->pci_ddrio, pvt->info.rankcfgr,
				      &reg);
		अगर (GET_BITFIELD(reg, 11, 11))
			/* FIXME: Can also be LRDIMM */
			mtype = MEM_RDDR3;
		अन्यथा
			mtype = MEM_DDR3;
	पूर्ण अन्यथा
		mtype = MEM_UNKNOWN;

	वापस mtype;
पूर्ण

अटल क्रमागत mem_type haswell_get_memory_type(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;
	bool रेजिस्टरed = false;
	क्रमागत mem_type mtype = MEM_UNKNOWN;

	अगर (!pvt->pci_ddrio)
		जाओ out;

	pci_पढ़ो_config_dword(pvt->pci_ddrio,
			      HASWELL_DDRCRCLKCONTROLS, &reg);
	/* Is_Rdimm */
	अगर (GET_BITFIELD(reg, 16, 16))
		रेजिस्टरed = true;

	pci_पढ़ो_config_dword(pvt->pci_ta, MCMTR, &reg);
	अगर (GET_BITFIELD(reg, 14, 14)) अणु
		अगर (रेजिस्टरed)
			mtype = MEM_RDDR4;
		अन्यथा
			mtype = MEM_DDR4;
	पूर्ण अन्यथा अणु
		अगर (रेजिस्टरed)
			mtype = MEM_RDDR3;
		अन्यथा
			mtype = MEM_DDR3;
	पूर्ण

out:
	वापस mtype;
पूर्ण

अटल क्रमागत dev_type knl_get_width(काष्ठा sbridge_pvt *pvt, u32 mtr)
अणु
	/* क्रम KNL value is fixed */
	वापस DEV_X16;
पूर्ण

अटल क्रमागत dev_type sbridge_get_width(काष्ठा sbridge_pvt *pvt, u32 mtr)
अणु
	/* there's no way to figure out */
	वापस DEV_UNKNOWN;
पूर्ण

अटल क्रमागत dev_type __ibridge_get_width(u32 mtr)
अणु
	क्रमागत dev_type type = DEV_UNKNOWN;

	चयन (mtr) अणु
	हाल 2:
		type = DEV_X16;
		अवरोध;
	हाल 1:
		type = DEV_X8;
		अवरोध;
	हाल 0:
		type = DEV_X4;
		अवरोध;
	पूर्ण

	वापस type;
पूर्ण

अटल क्रमागत dev_type ibridge_get_width(काष्ठा sbridge_pvt *pvt, u32 mtr)
अणु
	/*
	 * ddr3_width on the करोcumentation but also valid क्रम DDR4 on
	 * Haswell
	 */
	वापस __ibridge_get_width(GET_BITFIELD(mtr, 7, 8));
पूर्ण

अटल क्रमागत dev_type broadwell_get_width(काष्ठा sbridge_pvt *pvt, u32 mtr)
अणु
	/* ddr3_width on the करोcumentation but also valid क्रम DDR4 */
	वापस __ibridge_get_width(GET_BITFIELD(mtr, 8, 9));
पूर्ण

अटल क्रमागत mem_type knl_get_memory_type(काष्ठा sbridge_pvt *pvt)
अणु
	/* DDR4 RDIMMS and LRDIMMS are supported */
	वापस MEM_RDDR4;
पूर्ण

अटल u8 get_node_id(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;
	pci_पढ़ो_config_dword(pvt->pci_br0, SAD_CONTROL, &reg);
	वापस GET_BITFIELD(reg, 0, 2);
पूर्ण

अटल u8 haswell_get_node_id(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;

	pci_पढ़ो_config_dword(pvt->pci_sad1, SAD_CONTROL, &reg);
	वापस GET_BITFIELD(reg, 0, 3);
पूर्ण

अटल u8 knl_get_node_id(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;

	pci_पढ़ो_config_dword(pvt->pci_sad1, SAD_CONTROL, &reg);
	वापस GET_BITFIELD(reg, 0, 2);
पूर्ण

/*
 * Use the reporting bank number to determine which memory
 * controller (also known as "ha" क्रम "home agent"). Sandy
 * Bridge only has one memory controller per socket, so the
 * answer is always zero.
 */
अटल u8 sbridge_get_ha(u8 bank)
अणु
	वापस 0;
पूर्ण

/*
 * On Ivy Bridge, Haswell and Broadwell the error may be in a
 * home agent bank (7, 8), or one of the per-channel memory
 * controller banks (9 .. 16).
 */
अटल u8 ibridge_get_ha(u8 bank)
अणु
	चयन (bank) अणु
	हाल 7 ... 8:
		वापस bank - 7;
	हाल 9 ... 16:
		वापस (bank - 9) / 4;
	शेष:
		वापस 0xff;
	पूर्ण
पूर्ण

/* Not used, but included क्रम safety/symmetry */
अटल u8 knl_get_ha(u8 bank)
अणु
	वापस 0xff;
पूर्ण

अटल u64 haswell_get_tolm(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;

	pci_पढ़ो_config_dword(pvt->info.pci_vtd, HASWELL_TOLM, &reg);
	वापस (GET_BITFIELD(reg, 26, 31) << 26) | 0x3ffffff;
पूर्ण

अटल u64 haswell_get_tohm(काष्ठा sbridge_pvt *pvt)
अणु
	u64 rc;
	u32 reg;

	pci_पढ़ो_config_dword(pvt->info.pci_vtd, HASWELL_TOHM_0, &reg);
	rc = GET_BITFIELD(reg, 26, 31);
	pci_पढ़ो_config_dword(pvt->info.pci_vtd, HASWELL_TOHM_1, &reg);
	rc = ((reg << 6) | rc) << 26;

	वापस rc | 0x1ffffff;
पूर्ण

अटल u64 knl_get_tolm(काष्ठा sbridge_pvt *pvt)
अणु
	u32 reg;

	pci_पढ़ो_config_dword(pvt->knl.pci_mc_info, KNL_TOLM, &reg);
	वापस (GET_BITFIELD(reg, 26, 31) << 26) | 0x3ffffff;
पूर्ण

अटल u64 knl_get_tohm(काष्ठा sbridge_pvt *pvt)
अणु
	u64 rc;
	u32 reg_lo, reg_hi;

	pci_पढ़ो_config_dword(pvt->knl.pci_mc_info, KNL_TOHM_0, &reg_lo);
	pci_पढ़ो_config_dword(pvt->knl.pci_mc_info, KNL_TOHM_1, &reg_hi);
	rc = ((u64)reg_hi << 32) | reg_lo;
	वापस rc | 0x3ffffff;
पूर्ण


अटल u64 haswell_rir_limit(u32 reg)
अणु
	वापस (((u64)GET_BITFIELD(reg,  1, 11) + 1) << 29) - 1;
पूर्ण

अटल अंतरभूत u8 sad_pkg_socket(u8 pkg)
अणु
	/* on Ivy Bridge, nodeID is SASS, where A is HA and S is node id */
	वापस ((pkg >> 3) << 2) | (pkg & 0x3);
पूर्ण

अटल अंतरभूत u8 sad_pkg_ha(u8 pkg)
अणु
	वापस (pkg >> 2) & 0x1;
पूर्ण

अटल पूर्णांक haswell_chan_hash(पूर्णांक idx, u64 addr)
अणु
	पूर्णांक i;

	/*
	 * XOR even bits from 12:26 to bit0 of idx,
	 *     odd bits from 13:27 to bit1
	 */
	क्रम (i = 12; i < 28; i += 2)
		idx ^= (addr >> i) & 3;

	वापस idx;
पूर्ण

/* Low bits of TAD limit, and some metadata. */
अटल स्थिर u32 knl_tad_dram_limit_lo[] = अणु
	0x400, 0x500, 0x600, 0x700,
	0x800, 0x900, 0xa00, 0xb00,
पूर्ण;

/* Low bits of TAD offset. */
अटल स्थिर u32 knl_tad_dram_offset_lo[] = अणु
	0x404, 0x504, 0x604, 0x704,
	0x804, 0x904, 0xa04, 0xb04,
पूर्ण;

/* High 16 bits of TAD limit and offset. */
अटल स्थिर u32 knl_tad_dram_hi[] = अणु
	0x408, 0x508, 0x608, 0x708,
	0x808, 0x908, 0xa08, 0xb08,
पूर्ण;

/* Number of ways a tad entry is पूर्णांकerleaved. */
अटल स्थिर u32 knl_tad_ways[] = अणु
	8, 6, 4, 3, 2, 1,
पूर्ण;

/*
 * Retrieve the n'th Target Address Decode table entry
 * from the memory controller's TAD table.
 *
 * @pvt:	driver निजी data
 * @entry:	which entry you want to retrieve
 * @mc:		which memory controller (0 or 1)
 * @offset:	output tad range offset
 * @limit:	output address of first byte above tad range
 * @ways:	output number of पूर्णांकerleave ways
 *
 * The offset value has curious semantics.  It's a sort of running total
 * of the sizes of all the memory regions that aren't mapped in this
 * tad table.
 */
अटल पूर्णांक knl_get_tad(स्थिर काष्ठा sbridge_pvt *pvt,
		स्थिर पूर्णांक entry,
		स्थिर पूर्णांक mc,
		u64 *offset,
		u64 *limit,
		पूर्णांक *ways)
अणु
	u32 reg_limit_lo, reg_offset_lo, reg_hi;
	काष्ठा pci_dev *pci_mc;
	पूर्णांक way_id;

	चयन (mc) अणु
	हाल 0:
		pci_mc = pvt->knl.pci_mc0;
		अवरोध;
	हाल 1:
		pci_mc = pvt->knl.pci_mc1;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	pci_पढ़ो_config_dword(pci_mc,
			knl_tad_dram_limit_lo[entry], &reg_limit_lo);
	pci_पढ़ो_config_dword(pci_mc,
			knl_tad_dram_offset_lo[entry], &reg_offset_lo);
	pci_पढ़ो_config_dword(pci_mc,
			knl_tad_dram_hi[entry], &reg_hi);

	/* Is this TAD entry enabled? */
	अगर (!GET_BITFIELD(reg_limit_lo, 0, 0))
		वापस -ENODEV;

	way_id = GET_BITFIELD(reg_limit_lo, 3, 5);

	अगर (way_id < ARRAY_SIZE(knl_tad_ways)) अणु
		*ways = knl_tad_ways[way_id];
	पूर्ण अन्यथा अणु
		*ways = 0;
		sbridge_prपूर्णांकk(KERN_ERR,
				"Unexpected value %d in mc_tad_limit_lo wayness field\n",
				way_id);
		वापस -ENODEV;
	पूर्ण

	/*
	 * The least signअगरicant 6 bits of base and limit are truncated.
	 * For limit, we fill the missing bits with 1s.
	 */
	*offset = ((u64) GET_BITFIELD(reg_offset_lo, 6, 31) << 6) |
				((u64) GET_BITFIELD(reg_hi, 0,  15) << 32);
	*limit = ((u64) GET_BITFIELD(reg_limit_lo,  6, 31) << 6) | 63 |
				((u64) GET_BITFIELD(reg_hi, 16, 31) << 32);

	वापस 0;
पूर्ण

/* Determine which memory controller is responsible क्रम a given channel. */
अटल पूर्णांक knl_channel_mc(पूर्णांक channel)
अणु
	WARN_ON(channel < 0 || channel >= 6);

	वापस channel < 3 ? 1 : 0;
पूर्ण

/*
 * Get the Nth entry from EDC_ROUTE_TABLE रेजिस्टर.
 * (This is the per-tile mapping of logical पूर्णांकerleave tarमाला_लो to
 *  physical EDC modules.)
 *
 * entry 0: 0:2
 *       1: 3:5
 *       2: 6:8
 *       3: 9:11
 *       4: 12:14
 *       5: 15:17
 *       6: 18:20
 *       7: 21:23
 * reserved: 24:31
 */
अटल u32 knl_get_edc_route(पूर्णांक entry, u32 reg)
अणु
	WARN_ON(entry >= KNL_MAX_EDCS);
	वापस GET_BITFIELD(reg, entry*3, (entry*3)+2);
पूर्ण

/*
 * Get the Nth entry from MC_ROUTE_TABLE रेजिस्टर.
 * (This is the per-tile mapping of logical पूर्णांकerleave tarमाला_लो to
 *  physical DRAM channels modules.)
 *
 * entry 0: mc 0:2   channel 18:19
 *       1: mc 3:5   channel 20:21
 *       2: mc 6:8   channel 22:23
 *       3: mc 9:11  channel 24:25
 *       4: mc 12:14 channel 26:27
 *       5: mc 15:17 channel 28:29
 * reserved: 30:31
 *
 * Though we have 3 bits to identअगरy the MC, we should only see
 * the values 0 or 1.
 */

अटल u32 knl_get_mc_route(पूर्णांक entry, u32 reg)
अणु
	पूर्णांक mc, chan;

	WARN_ON(entry >= KNL_MAX_CHANNELS);

	mc = GET_BITFIELD(reg, entry*3, (entry*3)+2);
	chan = GET_BITFIELD(reg, (entry*2) + 18, (entry*2) + 18 + 1);

	वापस knl_channel_remap(mc, chan);
पूर्ण

/*
 * Render the EDC_ROUTE रेजिस्टर in human-पढ़ोable क्रमm.
 * Output string s should be at least KNL_MAX_EDCS*2 bytes.
 */
अटल व्योम knl_show_edc_route(u32 reg, अक्षर *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KNL_MAX_EDCS; i++) अणु
		s[i*2] = knl_get_edc_route(i, reg) + '0';
		s[i*2+1] = '-';
	पूर्ण

	s[KNL_MAX_EDCS*2 - 1] = '\0';
पूर्ण

/*
 * Render the MC_ROUTE रेजिस्टर in human-पढ़ोable क्रमm.
 * Output string s should be at least KNL_MAX_CHANNELS*2 bytes.
 */
अटल व्योम knl_show_mc_route(u32 reg, अक्षर *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KNL_MAX_CHANNELS; i++) अणु
		s[i*2] = knl_get_mc_route(i, reg) + '0';
		s[i*2+1] = '-';
	पूर्ण

	s[KNL_MAX_CHANNELS*2 - 1] = '\0';
पूर्ण

#घोषणा KNL_EDC_ROUTE 0xb8
#घोषणा KNL_MC_ROUTE 0xb4

/* Is this dram rule backed by regular DRAM in flat mode? */
#घोषणा KNL_EDRAM(reg) GET_BITFIELD(reg, 29, 29)

/* Is this dram rule cached? */
#घोषणा KNL_CACHEABLE(reg) GET_BITFIELD(reg, 28, 28)

/* Is this rule backed by edc ? */
#घोषणा KNL_EDRAM_ONLY(reg) GET_BITFIELD(reg, 29, 29)

/* Is this rule backed by DRAM, cacheable in EDRAM? */
#घोषणा KNL_CACHEABLE(reg) GET_BITFIELD(reg, 28, 28)

/* Is this rule mod3? */
#घोषणा KNL_MOD3(reg) GET_BITFIELD(reg, 27, 27)

/*
 * Figure out how big our RAM modules are.
 *
 * The DIMMMTR रेजिस्टर in KNL करोesn't tell us the size of the DIMMs, so we
 * have to figure this out from the SAD rules, पूर्णांकerleave lists, route tables,
 * and TAD rules.
 *
 * SAD rules can have holes in them (e.g. the 3G-4G hole), so we have to
 * inspect the TAD rules to figure out how large the SAD regions really are.
 *
 * When we know the real size of a SAD region and how many ways it's
 * पूर्णांकerleaved, we know the inभागidual contribution of each channel to
 * TAD is size/ways.
 *
 * Finally, we have to check whether each channel participates in each SAD
 * region.
 *
 * Fortunately, KNL only supports one DIMM per channel, so once we know how
 * much memory the channel uses, we know the DIMM is at least that large.
 * (The BIOS might possibly choose not to map all available memory, in which
 * हाल we will underreport the size of the DIMM.)
 *
 * In theory, we could try to determine the EDC sizes as well, but that would
 * only work in flat mode, not in cache mode.
 *
 * @mc_sizes: Output sizes of channels (must have space क्रम KNL_MAX_CHANNELS
 *            elements)
 */
अटल पूर्णांक knl_get_dimm_capacity(काष्ठा sbridge_pvt *pvt, u64 *mc_sizes)
अणु
	u64 sad_base, sad_limit = 0;
	u64 tad_base, tad_size, tad_limit, tad_deadspace, tad_livespace;
	पूर्णांक sad_rule = 0;
	पूर्णांक tad_rule = 0;
	पूर्णांक पूर्णांकrlv_ways, tad_ways;
	u32 first_pkg, pkg;
	पूर्णांक i;
	u64 sad_actual_size[2]; /* sad size accounting क्रम holes, per mc */
	u32 dram_rule, पूर्णांकerleave_reg;
	u32 mc_route_reg[KNL_MAX_CHAS];
	u32 edc_route_reg[KNL_MAX_CHAS];
	पूर्णांक edram_only;
	अक्षर edc_route_string[KNL_MAX_EDCS*2];
	अक्षर mc_route_string[KNL_MAX_CHANNELS*2];
	पूर्णांक cur_reg_start;
	पूर्णांक mc;
	पूर्णांक channel;
	पूर्णांक participants[KNL_MAX_CHANNELS];

	क्रम (i = 0; i < KNL_MAX_CHANNELS; i++)
		mc_sizes[i] = 0;

	/* Read the EDC route table in each CHA. */
	cur_reg_start = 0;
	क्रम (i = 0; i < KNL_MAX_CHAS; i++) अणु
		pci_पढ़ो_config_dword(pvt->knl.pci_cha[i],
				KNL_EDC_ROUTE, &edc_route_reg[i]);

		अगर (i > 0 && edc_route_reg[i] != edc_route_reg[i-1]) अणु
			knl_show_edc_route(edc_route_reg[i-1],
					edc_route_string);
			अगर (cur_reg_start == i-1)
				edac_dbg(0, "edc route table for CHA %d: %s\n",
					cur_reg_start, edc_route_string);
			अन्यथा
				edac_dbg(0, "edc route table for CHA %d-%d: %s\n",
					cur_reg_start, i-1, edc_route_string);
			cur_reg_start = i;
		पूर्ण
	पूर्ण
	knl_show_edc_route(edc_route_reg[i-1], edc_route_string);
	अगर (cur_reg_start == i-1)
		edac_dbg(0, "edc route table for CHA %d: %s\n",
			cur_reg_start, edc_route_string);
	अन्यथा
		edac_dbg(0, "edc route table for CHA %d-%d: %s\n",
			cur_reg_start, i-1, edc_route_string);

	/* Read the MC route table in each CHA. */
	cur_reg_start = 0;
	क्रम (i = 0; i < KNL_MAX_CHAS; i++) अणु
		pci_पढ़ो_config_dword(pvt->knl.pci_cha[i],
			KNL_MC_ROUTE, &mc_route_reg[i]);

		अगर (i > 0 && mc_route_reg[i] != mc_route_reg[i-1]) अणु
			knl_show_mc_route(mc_route_reg[i-1], mc_route_string);
			अगर (cur_reg_start == i-1)
				edac_dbg(0, "mc route table for CHA %d: %s\n",
					cur_reg_start, mc_route_string);
			अन्यथा
				edac_dbg(0, "mc route table for CHA %d-%d: %s\n",
					cur_reg_start, i-1, mc_route_string);
			cur_reg_start = i;
		पूर्ण
	पूर्ण
	knl_show_mc_route(mc_route_reg[i-1], mc_route_string);
	अगर (cur_reg_start == i-1)
		edac_dbg(0, "mc route table for CHA %d: %s\n",
			cur_reg_start, mc_route_string);
	अन्यथा
		edac_dbg(0, "mc route table for CHA %d-%d: %s\n",
			cur_reg_start, i-1, mc_route_string);

	/* Process DRAM rules */
	क्रम (sad_rule = 0; sad_rule < pvt->info.max_sad; sad_rule++) अणु
		/* previous limit becomes the new base */
		sad_base = sad_limit;

		pci_पढ़ो_config_dword(pvt->pci_sad0,
			pvt->info.dram_rule[sad_rule], &dram_rule);

		अगर (!DRAM_RULE_ENABLE(dram_rule))
			अवरोध;

		edram_only = KNL_EDRAM_ONLY(dram_rule);

		sad_limit = pvt->info.sad_limit(dram_rule)+1;

		pci_पढ़ो_config_dword(pvt->pci_sad0,
			pvt->info.पूर्णांकerleave_list[sad_rule], &पूर्णांकerleave_reg);

		/*
		 * Find out how many ways this dram rule is पूर्णांकerleaved.
		 * We stop when we see the first channel again.
		 */
		first_pkg = sad_pkg(pvt->info.पूर्णांकerleave_pkg,
						पूर्णांकerleave_reg, 0);
		क्रम (पूर्णांकrlv_ways = 1; पूर्णांकrlv_ways < 8; पूर्णांकrlv_ways++) अणु
			pkg = sad_pkg(pvt->info.पूर्णांकerleave_pkg,
						पूर्णांकerleave_reg, पूर्णांकrlv_ways);

			अगर ((pkg & 0x8) == 0) अणु
				/*
				 * 0 bit means memory is non-local,
				 * which KNL करोesn't support
				 */
				edac_dbg(0, "Unexpected interleave target %d\n",
					pkg);
				वापस -1;
			पूर्ण

			अगर (pkg == first_pkg)
				अवरोध;
		पूर्ण
		अगर (KNL_MOD3(dram_rule))
			पूर्णांकrlv_ways *= 3;

		edac_dbg(3, "dram rule %d (base 0x%llx, limit 0x%llx), %d way interleave%s\n",
			sad_rule,
			sad_base,
			sad_limit,
			पूर्णांकrlv_ways,
			edram_only ? ", EDRAM" : "");

		/*
		 * Find out how big the SAD region really is by iterating
		 * over TAD tables (SAD regions may contain holes).
		 * Each memory controller might have a dअगरferent TAD table, so
		 * we have to look at both.
		 *
		 * Livespace is the memory that's mapped in this TAD table,
		 * deadspace is the holes (this could be the MMIO hole, or it
		 * could be memory that's mapped by the other TAD table but
		 * not this one).
		 */
		क्रम (mc = 0; mc < 2; mc++) अणु
			sad_actual_size[mc] = 0;
			tad_livespace = 0;
			क्रम (tad_rule = 0;
					tad_rule < ARRAY_SIZE(
						knl_tad_dram_limit_lo);
					tad_rule++) अणु
				अगर (knl_get_tad(pvt,
						tad_rule,
						mc,
						&tad_deadspace,
						&tad_limit,
						&tad_ways))
					अवरोध;

				tad_size = (tad_limit+1) -
					(tad_livespace + tad_deadspace);
				tad_livespace += tad_size;
				tad_base = (tad_limit+1) - tad_size;

				अगर (tad_base < sad_base) अणु
					अगर (tad_limit > sad_base)
						edac_dbg(0, "TAD region overlaps lower SAD boundary -- TAD tables may be configured incorrectly.\n");
				पूर्ण अन्यथा अगर (tad_base < sad_limit) अणु
					अगर (tad_limit+1 > sad_limit) अणु
						edac_dbg(0, "TAD region overlaps upper SAD boundary -- TAD tables may be configured incorrectly.\n");
					पूर्ण अन्यथा अणु
						/* TAD region is completely inside SAD region */
						edac_dbg(3, "TAD region %d 0x%llx - 0x%llx (%lld bytes) table%d\n",
							tad_rule, tad_base,
							tad_limit, tad_size,
							mc);
						sad_actual_size[mc] += tad_size;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		क्रम (mc = 0; mc < 2; mc++) अणु
			edac_dbg(3, " total TAD DRAM footprint in table%d : 0x%llx (%lld bytes)\n",
				mc, sad_actual_size[mc], sad_actual_size[mc]);
		पूर्ण

		/* Ignore EDRAM rule */
		अगर (edram_only)
			जारी;

		/* Figure out which channels participate in पूर्णांकerleave. */
		क्रम (channel = 0; channel < KNL_MAX_CHANNELS; channel++)
			participants[channel] = 0;

		/* For each channel, करोes at least one CHA have
		 * this channel mapped to the given target?
		 */
		क्रम (channel = 0; channel < KNL_MAX_CHANNELS; channel++) अणु
			पूर्णांक target;
			पूर्णांक cha;

			क्रम (target = 0; target < KNL_MAX_CHANNELS; target++) अणु
				क्रम (cha = 0; cha < KNL_MAX_CHAS; cha++) अणु
					अगर (knl_get_mc_route(target,
						mc_route_reg[cha]) == channel
						&& !participants[channel]) अणु
						participants[channel] = 1;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		क्रम (channel = 0; channel < KNL_MAX_CHANNELS; channel++) अणु
			mc = knl_channel_mc(channel);
			अगर (participants[channel]) अणु
				edac_dbg(4, "mc channel %d contributes %lld bytes via sad entry %d\n",
					channel,
					sad_actual_size[mc]/पूर्णांकrlv_ways,
					sad_rule);
				mc_sizes[channel] +=
					sad_actual_size[mc]/पूर्णांकrlv_ways;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम get_source_id(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	u32 reg;

	अगर (pvt->info.type == HASWELL || pvt->info.type == BROADWELL ||
	    pvt->info.type == KNIGHTS_LANDING)
		pci_पढ़ो_config_dword(pvt->pci_sad1, SAD_TARGET, &reg);
	अन्यथा
		pci_पढ़ो_config_dword(pvt->pci_br0, SAD_TARGET, &reg);

	अगर (pvt->info.type == KNIGHTS_LANDING)
		pvt->sbridge_dev->source_id = SOURCE_ID_KNL(reg);
	अन्यथा
		pvt->sbridge_dev->source_id = SOURCE_ID(reg);
पूर्ण

अटल पूर्णांक __populate_dimms(काष्ठा mem_ctl_info *mci,
			    u64 knl_mc_sizes[KNL_MAX_CHANNELS],
			    क्रमागत edac_type mode)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	पूर्णांक channels = pvt->info.type == KNIGHTS_LANDING ? KNL_MAX_CHANNELS
							 : NUM_CHANNELS;
	अचिन्हित पूर्णांक i, j, banks, ranks, rows, cols, npages;
	काष्ठा dimm_info *dimm;
	क्रमागत mem_type mtype;
	u64 size;

	mtype = pvt->info.get_memory_type(pvt);
	अगर (mtype == MEM_RDDR3 || mtype == MEM_RDDR4)
		edac_dbg(0, "Memory is registered\n");
	अन्यथा अगर (mtype == MEM_UNKNOWN)
		edac_dbg(0, "Cannot determine memory type\n");
	अन्यथा
		edac_dbg(0, "Memory is unregistered\n");

	अगर (mtype == MEM_DDR4 || mtype == MEM_RDDR4)
		banks = 16;
	अन्यथा
		banks = 8;

	क्रम (i = 0; i < channels; i++) अणु
		u32 mtr;

		पूर्णांक max_dimms_per_channel;

		अगर (pvt->info.type == KNIGHTS_LANDING) अणु
			max_dimms_per_channel = 1;
			अगर (!pvt->knl.pci_channel[i])
				जारी;
		पूर्ण अन्यथा अणु
			max_dimms_per_channel = ARRAY_SIZE(mtr_regs);
			अगर (!pvt->pci_tad[i])
				जारी;
		पूर्ण

		क्रम (j = 0; j < max_dimms_per_channel; j++) अणु
			dimm = edac_get_dimm(mci, i, j, 0);
			अगर (pvt->info.type == KNIGHTS_LANDING) अणु
				pci_पढ़ो_config_dword(pvt->knl.pci_channel[i],
					knl_mtr_reg, &mtr);
			पूर्ण अन्यथा अणु
				pci_पढ़ो_config_dword(pvt->pci_tad[i],
					mtr_regs[j], &mtr);
			पूर्ण
			edac_dbg(4, "Channel #%d  MTR%d = %x\n", i, j, mtr);
			अगर (IS_DIMM_PRESENT(mtr)) अणु
				अगर (!IS_ECC_ENABLED(pvt->info.mcmtr)) अणु
					sbridge_prपूर्णांकk(KERN_ERR, "CPU SrcID #%d, Ha #%d, Channel #%d has DIMMs, but ECC is disabled\n",
						       pvt->sbridge_dev->source_id,
						       pvt->sbridge_dev->करोm, i);
					वापस -ENODEV;
				पूर्ण
				pvt->channel[i].dimms++;

				ranks = numrank(pvt->info.type, mtr);

				अगर (pvt->info.type == KNIGHTS_LANDING) अणु
					/* For DDR4, this is fixed. */
					cols = 1 << 10;
					rows = knl_mc_sizes[i] /
						((u64) cols * ranks * banks * 8);
				पूर्ण अन्यथा अणु
					rows = numrow(mtr);
					cols = numcol(mtr);
				पूर्ण

				size = ((u64)rows * cols * banks * ranks) >> (20 - 3);
				npages = MiB_TO_PAGES(size);

				edac_dbg(0, "mc#%d: ha %d channel %d, dimm %d, %lld MiB (%d pages) bank: %d, rank: %d, row: %#x, col: %#x\n",
					 pvt->sbridge_dev->mc, pvt->sbridge_dev->करोm, i, j,
					 size, npages,
					 banks, ranks, rows, cols);

				dimm->nr_pages = npages;
				dimm->grain = 32;
				dimm->dtype = pvt->info.get_width(pvt, mtr);
				dimm->mtype = mtype;
				dimm->edac_mode = mode;
				snम_लिखो(dimm->label, माप(dimm->label),
						 "CPU_SrcID#%u_Ha#%u_Chan#%u_DIMM#%u",
						 pvt->sbridge_dev->source_id, pvt->sbridge_dev->करोm, i, j);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_dimm_config(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	u64 knl_mc_sizes[KNL_MAX_CHANNELS];
	क्रमागत edac_type mode;
	u32 reg;

	pvt->sbridge_dev->node_id = pvt->info.get_node_id(pvt);
	edac_dbg(0, "mc#%d: Node ID: %d, source ID: %d\n",
		 pvt->sbridge_dev->mc,
		 pvt->sbridge_dev->node_id,
		 pvt->sbridge_dev->source_id);

	/* KNL करोesn't support mirroring or lockstep,
	 * and is always बंदd page
	 */
	अगर (pvt->info.type == KNIGHTS_LANDING) अणु
		mode = EDAC_S4ECD4ED;
		pvt->mirror_mode = NON_MIRRORING;
		pvt->is_cur_addr_mirrored = false;

		अगर (knl_get_dimm_capacity(pvt, knl_mc_sizes) != 0)
			वापस -1;
		अगर (pci_पढ़ो_config_dword(pvt->pci_ta, KNL_MCMTR, &pvt->info.mcmtr)) अणु
			edac_dbg(0, "Failed to read KNL_MCMTR register\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pvt->info.type == HASWELL || pvt->info.type == BROADWELL) अणु
			अगर (pci_पढ़ो_config_dword(pvt->pci_ha, HASWELL_HASYSDEFEATURE2, &reg)) अणु
				edac_dbg(0, "Failed to read HASWELL_HASYSDEFEATURE2 register\n");
				वापस -ENODEV;
			पूर्ण
			pvt->is_chan_hash = GET_BITFIELD(reg, 21, 21);
			अगर (GET_BITFIELD(reg, 28, 28)) अणु
				pvt->mirror_mode = ADDR_RANGE_MIRRORING;
				edac_dbg(0, "Address range partial memory mirroring is enabled\n");
				जाओ next;
			पूर्ण
		पूर्ण
		अगर (pci_पढ़ो_config_dword(pvt->pci_ras, RASENABLES, &reg)) अणु
			edac_dbg(0, "Failed to read RASENABLES register\n");
			वापस -ENODEV;
		पूर्ण
		अगर (IS_MIRROR_ENABLED(reg)) अणु
			pvt->mirror_mode = FULL_MIRRORING;
			edac_dbg(0, "Full memory mirroring is enabled\n");
		पूर्ण अन्यथा अणु
			pvt->mirror_mode = NON_MIRRORING;
			edac_dbg(0, "Memory mirroring is disabled\n");
		पूर्ण

next:
		अगर (pci_पढ़ो_config_dword(pvt->pci_ta, MCMTR, &pvt->info.mcmtr)) अणु
			edac_dbg(0, "Failed to read MCMTR register\n");
			वापस -ENODEV;
		पूर्ण
		अगर (IS_LOCKSTEP_ENABLED(pvt->info.mcmtr)) अणु
			edac_dbg(0, "Lockstep is enabled\n");
			mode = EDAC_S8ECD8ED;
			pvt->is_lockstep = true;
		पूर्ण अन्यथा अणु
			edac_dbg(0, "Lockstep is disabled\n");
			mode = EDAC_S4ECD4ED;
			pvt->is_lockstep = false;
		पूर्ण
		अगर (IS_CLOSE_PG(pvt->info.mcmtr)) अणु
			edac_dbg(0, "address map is on closed page mode\n");
			pvt->is_बंद_pg = true;
		पूर्ण अन्यथा अणु
			edac_dbg(0, "address map is on open page mode\n");
			pvt->is_बंद_pg = false;
		पूर्ण
	पूर्ण

	वापस __populate_dimms(mci, knl_mc_sizes, mode);
पूर्ण

अटल व्योम get_memory_layout(स्थिर काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	पूर्णांक i, j, k, n_sads, n_tads, sad_पूर्णांकerl;
	u32 reg;
	u64 limit, prv = 0;
	u64 पंचांगp_mb;
	u32 gb, mb;
	u32 rir_way;

	/*
	 * Step 1) Get TOLM/TOHM ranges
	 */

	pvt->tolm = pvt->info.get_tolm(pvt);
	पंचांगp_mb = (1 + pvt->tolm) >> 20;

	gb = भाग_u64_rem(पंचांगp_mb, 1024, &mb);
	edac_dbg(0, "TOLM: %u.%03u GB (0x%016Lx)\n",
		gb, (mb*1000)/1024, (u64)pvt->tolm);

	/* Address range is alपढ़ोy 45:25 */
	pvt->tohm = pvt->info.get_tohm(pvt);
	पंचांगp_mb = (1 + pvt->tohm) >> 20;

	gb = भाग_u64_rem(पंचांगp_mb, 1024, &mb);
	edac_dbg(0, "TOHM: %u.%03u GB (0x%016Lx)\n",
		gb, (mb*1000)/1024, (u64)pvt->tohm);

	/*
	 * Step 2) Get SAD range and SAD Interleave list
	 * TAD रेजिस्टरs contain the पूर्णांकerleave wayness. However, it
	 * seems simpler to just discover it indirectly, with the
	 * algorithm bellow.
	 */
	prv = 0;
	क्रम (n_sads = 0; n_sads < pvt->info.max_sad; n_sads++) अणु
		/* SAD_LIMIT Address range is 45:26 */
		pci_पढ़ो_config_dword(pvt->pci_sad0, pvt->info.dram_rule[n_sads],
				      &reg);
		limit = pvt->info.sad_limit(reg);

		अगर (!DRAM_RULE_ENABLE(reg))
			जारी;

		अगर (limit <= prv)
			अवरोध;

		पंचांगp_mb = (limit + 1) >> 20;
		gb = भाग_u64_rem(पंचांगp_mb, 1024, &mb);
		edac_dbg(0, "SAD#%d %s up to %u.%03u GB (0x%016Lx) Interleave: %s reg=0x%08x\n",
			 n_sads,
			 show_dram_attr(pvt->info.dram_attr(reg)),
			 gb, (mb*1000)/1024,
			 ((u64)पंचांगp_mb) << 20L,
			 get_पूर्णांकlv_mode_str(reg, pvt->info.type),
			 reg);
		prv = limit;

		pci_पढ़ो_config_dword(pvt->pci_sad0, pvt->info.पूर्णांकerleave_list[n_sads],
				      &reg);
		sad_पूर्णांकerl = sad_pkg(pvt->info.पूर्णांकerleave_pkg, reg, 0);
		क्रम (j = 0; j < 8; j++) अणु
			u32 pkg = sad_pkg(pvt->info.पूर्णांकerleave_pkg, reg, j);
			अगर (j > 0 && sad_पूर्णांकerl == pkg)
				अवरोध;

			edac_dbg(0, "SAD#%d, interleave #%d: %d\n",
				 n_sads, j, pkg);
		पूर्ण
	पूर्ण

	अगर (pvt->info.type == KNIGHTS_LANDING)
		वापस;

	/*
	 * Step 3) Get TAD range
	 */
	prv = 0;
	क्रम (n_tads = 0; n_tads < MAX_TAD; n_tads++) अणु
		pci_पढ़ो_config_dword(pvt->pci_ha, tad_dram_rule[n_tads], &reg);
		limit = TAD_LIMIT(reg);
		अगर (limit <= prv)
			अवरोध;
		पंचांगp_mb = (limit + 1) >> 20;

		gb = भाग_u64_rem(पंचांगp_mb, 1024, &mb);
		edac_dbg(0, "TAD#%d: up to %u.%03u GB (0x%016Lx), socket interleave %d, memory interleave %d, TGT: %d, %d, %d, %d, reg=0x%08x\n",
			 n_tads, gb, (mb*1000)/1024,
			 ((u64)पंचांगp_mb) << 20L,
			 (u32)(1 << TAD_SOCK(reg)),
			 (u32)TAD_CH(reg) + 1,
			 (u32)TAD_TGT0(reg),
			 (u32)TAD_TGT1(reg),
			 (u32)TAD_TGT2(reg),
			 (u32)TAD_TGT3(reg),
			 reg);
		prv = limit;
	पूर्ण

	/*
	 * Step 4) Get TAD offsets, per each channel
	 */
	क्रम (i = 0; i < NUM_CHANNELS; i++) अणु
		अगर (!pvt->channel[i].dimms)
			जारी;
		क्रम (j = 0; j < n_tads; j++) अणु
			pci_पढ़ो_config_dword(pvt->pci_tad[i],
					      tad_ch_nilv_offset[j],
					      &reg);
			पंचांगp_mb = TAD_OFFSET(reg) >> 20;
			gb = भाग_u64_rem(पंचांगp_mb, 1024, &mb);
			edac_dbg(0, "TAD CH#%d, offset #%d: %u.%03u GB (0x%016Lx), reg=0x%08x\n",
				 i, j,
				 gb, (mb*1000)/1024,
				 ((u64)पंचांगp_mb) << 20L,
				 reg);
		पूर्ण
	पूर्ण

	/*
	 * Step 6) Get RIR Wayness/Limit, per each channel
	 */
	क्रम (i = 0; i < NUM_CHANNELS; i++) अणु
		अगर (!pvt->channel[i].dimms)
			जारी;
		क्रम (j = 0; j < MAX_RIR_RANGES; j++) अणु
			pci_पढ़ो_config_dword(pvt->pci_tad[i],
					      rir_way_limit[j],
					      &reg);

			अगर (!IS_RIR_VALID(reg))
				जारी;

			पंचांगp_mb = pvt->info.rir_limit(reg) >> 20;
			rir_way = 1 << RIR_WAY(reg);
			gb = भाग_u64_rem(पंचांगp_mb, 1024, &mb);
			edac_dbg(0, "CH#%d RIR#%d, limit: %u.%03u GB (0x%016Lx), way: %d, reg=0x%08x\n",
				 i, j,
				 gb, (mb*1000)/1024,
				 ((u64)पंचांगp_mb) << 20L,
				 rir_way,
				 reg);

			क्रम (k = 0; k < rir_way; k++) अणु
				pci_पढ़ो_config_dword(pvt->pci_tad[i],
						      rir_offset[j][k],
						      &reg);
				पंचांगp_mb = RIR_OFFSET(pvt->info.type, reg) << 6;

				gb = भाग_u64_rem(पंचांगp_mb, 1024, &mb);
				edac_dbg(0, "CH#%d RIR#%d INTL#%d, offset %u.%03u GB (0x%016Lx), tgt: %d, reg=0x%08x\n",
					 i, j, k,
					 gb, (mb*1000)/1024,
					 ((u64)पंचांगp_mb) << 20L,
					 (u32)RIR_RNK_TGT(pvt->info.type, reg),
					 reg);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा mem_ctl_info *get_mci_क्रम_node_id(u8 node_id, u8 ha)
अणु
	काष्ठा sbridge_dev *sbridge_dev;

	list_क्रम_each_entry(sbridge_dev, &sbridge_edac_list, list) अणु
		अगर (sbridge_dev->node_id == node_id && sbridge_dev->करोm == ha)
			वापस sbridge_dev->mci;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक get_memory_error_data(काष्ठा mem_ctl_info *mci,
				 u64 addr,
				 u8 *socket, u8 *ha,
				 दीर्घ *channel_mask,
				 u8 *rank,
				 अक्षर **area_type, अक्षर *msg)
अणु
	काष्ठा mem_ctl_info	*new_mci;
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev		*pci_ha;
	पूर्णांक			n_rir, n_sads, n_tads, sad_way, sck_xch;
	पूर्णांक			sad_पूर्णांकerl, idx, base_ch;
	पूर्णांक			पूर्णांकerleave_mode, shअगरtup = 0;
	अचिन्हित पूर्णांक		sad_पूर्णांकerleave[MAX_INTERLEAVE];
	u32			reg, dram_rule;
	u8			ch_way, sck_way, pkg, sad_ha = 0;
	u32			tad_offset;
	u32			rir_way;
	u32			mb, gb;
	u64			ch_addr, offset, limit = 0, prv = 0;


	/*
	 * Step 0) Check अगर the address is at special memory ranges
	 * The check bellow is probably enough to fill all हालs where
	 * the error is not inside a memory, except क्रम the legacy
	 * range (e. g. VGA addresses). It is unlikely, however, that the
	 * memory controller would generate an error on that range.
	 */
	अगर ((addr > (u64) pvt->tolm) && (addr < (1LL << 32))) अणु
		प्र_लिखो(msg, "Error at TOLM area, on addr 0x%08Lx", addr);
		वापस -EINVAL;
	पूर्ण
	अगर (addr >= (u64)pvt->tohm) अणु
		प्र_लिखो(msg, "Error at MMIOH area, on addr 0x%016Lx", addr);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Step 1) Get socket
	 */
	क्रम (n_sads = 0; n_sads < pvt->info.max_sad; n_sads++) अणु
		pci_पढ़ो_config_dword(pvt->pci_sad0, pvt->info.dram_rule[n_sads],
				      &reg);

		अगर (!DRAM_RULE_ENABLE(reg))
			जारी;

		limit = pvt->info.sad_limit(reg);
		अगर (limit <= prv) अणु
			प्र_लिखो(msg, "Can't discover the memory socket");
			वापस -EINVAL;
		पूर्ण
		अगर  (addr <= limit)
			अवरोध;
		prv = limit;
	पूर्ण
	अगर (n_sads == pvt->info.max_sad) अणु
		प्र_लिखो(msg, "Can't discover the memory socket");
		वापस -EINVAL;
	पूर्ण
	dram_rule = reg;
	*area_type = show_dram_attr(pvt->info.dram_attr(dram_rule));
	पूर्णांकerleave_mode = pvt->info.पूर्णांकerleave_mode(dram_rule);

	pci_पढ़ो_config_dword(pvt->pci_sad0, pvt->info.पूर्णांकerleave_list[n_sads],
			      &reg);

	अगर (pvt->info.type == SANDY_BRIDGE) अणु
		sad_पूर्णांकerl = sad_pkg(pvt->info.पूर्णांकerleave_pkg, reg, 0);
		क्रम (sad_way = 0; sad_way < 8; sad_way++) अणु
			u32 pkg = sad_pkg(pvt->info.पूर्णांकerleave_pkg, reg, sad_way);
			अगर (sad_way > 0 && sad_पूर्णांकerl == pkg)
				अवरोध;
			sad_पूर्णांकerleave[sad_way] = pkg;
			edac_dbg(0, "SAD interleave #%d: %d\n",
				 sad_way, sad_पूर्णांकerleave[sad_way]);
		पूर्ण
		edac_dbg(0, "mc#%d: Error detected on SAD#%d: address 0x%016Lx < 0x%016Lx, Interleave [%d:6]%s\n",
			 pvt->sbridge_dev->mc,
			 n_sads,
			 addr,
			 limit,
			 sad_way + 7,
			 !पूर्णांकerleave_mode ? "" : "XOR[18:16]");
		अगर (पूर्णांकerleave_mode)
			idx = ((addr >> 6) ^ (addr >> 16)) & 7;
		अन्यथा
			idx = (addr >> 6) & 7;
		चयन (sad_way) अणु
		हाल 1:
			idx = 0;
			अवरोध;
		हाल 2:
			idx = idx & 1;
			अवरोध;
		हाल 4:
			idx = idx & 3;
			अवरोध;
		हाल 8:
			अवरोध;
		शेष:
			प्र_लिखो(msg, "Can't discover socket interleave");
			वापस -EINVAL;
		पूर्ण
		*socket = sad_पूर्णांकerleave[idx];
		edac_dbg(0, "SAD interleave index: %d (wayness %d) = CPU socket %d\n",
			 idx, sad_way, *socket);
	पूर्ण अन्यथा अगर (pvt->info.type == HASWELL || pvt->info.type == BROADWELL) अणु
		पूर्णांक bits, a7mode = A7MODE(dram_rule);

		अगर (a7mode) अणु
			/* A7 mode swaps P9 with P6 */
			bits = GET_BITFIELD(addr, 7, 8) << 1;
			bits |= GET_BITFIELD(addr, 9, 9);
		पूर्ण अन्यथा
			bits = GET_BITFIELD(addr, 6, 8);

		अगर (पूर्णांकerleave_mode == 0) अणु
			/* पूर्णांकerleave mode will XOR अणु8,7,6पूर्ण with अणु18,17,16पूर्ण */
			idx = GET_BITFIELD(addr, 16, 18);
			idx ^= bits;
		पूर्ण अन्यथा
			idx = bits;

		pkg = sad_pkg(pvt->info.पूर्णांकerleave_pkg, reg, idx);
		*socket = sad_pkg_socket(pkg);
		sad_ha = sad_pkg_ha(pkg);

		अगर (a7mode) अणु
			/* MCChanShअगरtUpEnable */
			pci_पढ़ो_config_dword(pvt->pci_ha, HASWELL_HASYSDEFEATURE2, &reg);
			shअगरtup = GET_BITFIELD(reg, 22, 22);
		पूर्ण

		edac_dbg(0, "SAD interleave package: %d = CPU socket %d, HA %i, shiftup: %i\n",
			 idx, *socket, sad_ha, shअगरtup);
	पूर्ण अन्यथा अणु
		/* Ivy Bridge's SAD mode doesn't support XOR पूर्णांकerleave mode */
		idx = (addr >> 6) & 7;
		pkg = sad_pkg(pvt->info.पूर्णांकerleave_pkg, reg, idx);
		*socket = sad_pkg_socket(pkg);
		sad_ha = sad_pkg_ha(pkg);
		edac_dbg(0, "SAD interleave package: %d = CPU socket %d, HA %d\n",
			 idx, *socket, sad_ha);
	पूर्ण

	*ha = sad_ha;

	/*
	 * Move to the proper node काष्ठाure, in order to access the
	 * right PCI रेजिस्टरs
	 */
	new_mci = get_mci_क्रम_node_id(*socket, sad_ha);
	अगर (!new_mci) अणु
		प्र_लिखो(msg, "Struct for socket #%u wasn't initialized",
			*socket);
		वापस -EINVAL;
	पूर्ण
	mci = new_mci;
	pvt = mci->pvt_info;

	/*
	 * Step 2) Get memory channel
	 */
	prv = 0;
	pci_ha = pvt->pci_ha;
	क्रम (n_tads = 0; n_tads < MAX_TAD; n_tads++) अणु
		pci_पढ़ो_config_dword(pci_ha, tad_dram_rule[n_tads], &reg);
		limit = TAD_LIMIT(reg);
		अगर (limit <= prv) अणु
			प्र_लिखो(msg, "Can't discover the memory channel");
			वापस -EINVAL;
		पूर्ण
		अगर  (addr <= limit)
			अवरोध;
		prv = limit;
	पूर्ण
	अगर (n_tads == MAX_TAD) अणु
		प्र_लिखो(msg, "Can't discover the memory channel");
		वापस -EINVAL;
	पूर्ण

	ch_way = TAD_CH(reg) + 1;
	sck_way = TAD_SOCK(reg);

	अगर (ch_way == 3)
		idx = addr >> 6;
	अन्यथा अणु
		idx = (addr >> (6 + sck_way + shअगरtup)) & 0x3;
		अगर (pvt->is_chan_hash)
			idx = haswell_chan_hash(idx, addr);
	पूर्ण
	idx = idx % ch_way;

	/*
	 * FIXME: Shouldn't we use CHN_IDX_OFFSET() here, when ch_way == 3 ???
	 */
	चयन (idx) अणु
	हाल 0:
		base_ch = TAD_TGT0(reg);
		अवरोध;
	हाल 1:
		base_ch = TAD_TGT1(reg);
		अवरोध;
	हाल 2:
		base_ch = TAD_TGT2(reg);
		अवरोध;
	हाल 3:
		base_ch = TAD_TGT3(reg);
		अवरोध;
	शेष:
		प्र_लिखो(msg, "Can't discover the TAD target");
		वापस -EINVAL;
	पूर्ण
	*channel_mask = 1 << base_ch;

	pci_पढ़ो_config_dword(pvt->pci_tad[base_ch], tad_ch_nilv_offset[n_tads], &tad_offset);

	अगर (pvt->mirror_mode == FULL_MIRRORING ||
	    (pvt->mirror_mode == ADDR_RANGE_MIRRORING && n_tads == 0)) अणु
		*channel_mask |= 1 << ((base_ch + 2) % 4);
		चयन(ch_way) अणु
		हाल 2:
		हाल 4:
			sck_xch = (1 << sck_way) * (ch_way >> 1);
			अवरोध;
		शेष:
			प्र_लिखो(msg, "Invalid mirror set. Can't decode addr");
			वापस -EINVAL;
		पूर्ण

		pvt->is_cur_addr_mirrored = true;
	पूर्ण अन्यथा अणु
		sck_xch = (1 << sck_way) * ch_way;
		pvt->is_cur_addr_mirrored = false;
	पूर्ण

	अगर (pvt->is_lockstep)
		*channel_mask |= 1 << ((base_ch + 1) % 4);

	offset = TAD_OFFSET(tad_offset);

	edac_dbg(0, "TAD#%d: address 0x%016Lx < 0x%016Lx, socket interleave %d, channel interleave %d (offset 0x%08Lx), index %d, base ch: %d, ch mask: 0x%02lx\n",
		 n_tads,
		 addr,
		 limit,
		 sck_way,
		 ch_way,
		 offset,
		 idx,
		 base_ch,
		 *channel_mask);

	/* Calculate channel address */
	/* Remove the TAD offset */

	अगर (offset > addr) अणु
		प्र_लिखो(msg, "Can't calculate ch addr: TAD offset 0x%08Lx is too high for addr 0x%08Lx!",
			offset, addr);
		वापस -EINVAL;
	पूर्ण

	ch_addr = addr - offset;
	ch_addr >>= (6 + shअगरtup);
	ch_addr /= sck_xch;
	ch_addr <<= (6 + shअगरtup);
	ch_addr |= addr & ((1 << (6 + shअगरtup)) - 1);

	/*
	 * Step 3) Decode rank
	 */
	क्रम (n_rir = 0; n_rir < MAX_RIR_RANGES; n_rir++) अणु
		pci_पढ़ो_config_dword(pvt->pci_tad[base_ch], rir_way_limit[n_rir], &reg);

		अगर (!IS_RIR_VALID(reg))
			जारी;

		limit = pvt->info.rir_limit(reg);
		gb = भाग_u64_rem(limit >> 20, 1024, &mb);
		edac_dbg(0, "RIR#%d, limit: %u.%03u GB (0x%016Lx), way: %d\n",
			 n_rir,
			 gb, (mb*1000)/1024,
			 limit,
			 1 << RIR_WAY(reg));
		अगर  (ch_addr <= limit)
			अवरोध;
	पूर्ण
	अगर (n_rir == MAX_RIR_RANGES) अणु
		प्र_लिखो(msg, "Can't discover the memory rank for ch addr 0x%08Lx",
			ch_addr);
		वापस -EINVAL;
	पूर्ण
	rir_way = RIR_WAY(reg);

	अगर (pvt->is_बंद_pg)
		idx = (ch_addr >> 6);
	अन्यथा
		idx = (ch_addr >> 13);	/* FIXME: Datasheet says to shअगरt by 15 */
	idx %= 1 << rir_way;

	pci_पढ़ो_config_dword(pvt->pci_tad[base_ch], rir_offset[n_rir][idx], &reg);
	*rank = RIR_RNK_TGT(pvt->info.type, reg);

	edac_dbg(0, "RIR#%d: channel address 0x%08Lx < 0x%08Lx, RIR interleave %d, index %d\n",
		 n_rir,
		 ch_addr,
		 limit,
		 rir_way,
		 idx);

	वापस 0;
पूर्ण

अटल पूर्णांक get_memory_error_data_from_mce(काष्ठा mem_ctl_info *mci,
					  स्थिर काष्ठा mce *m, u8 *socket,
					  u8 *ha, दीर्घ *channel_mask,
					  अक्षर *msg)
अणु
	u32 reg, channel = GET_BITFIELD(m->status, 0, 3);
	काष्ठा mem_ctl_info *new_mci;
	काष्ठा sbridge_pvt *pvt;
	काष्ठा pci_dev *pci_ha;
	bool tad0;

	अगर (channel >= NUM_CHANNELS) अणु
		प्र_लिखो(msg, "Invalid channel 0x%x", channel);
		वापस -EINVAL;
	पूर्ण

	pvt = mci->pvt_info;
	अगर (!pvt->info.get_ha) अणु
		प्र_लिखो(msg, "No get_ha()");
		वापस -EINVAL;
	पूर्ण
	*ha = pvt->info.get_ha(m->bank);
	अगर (*ha != 0 && *ha != 1) अणु
		प्र_लिखो(msg, "Impossible bank %d", m->bank);
		वापस -EINVAL;
	पूर्ण

	*socket = m->socketid;
	new_mci = get_mci_क्रम_node_id(*socket, *ha);
	अगर (!new_mci) अणु
		म_नकल(msg, "mci socket got corrupted!");
		वापस -EINVAL;
	पूर्ण

	pvt = new_mci->pvt_info;
	pci_ha = pvt->pci_ha;
	pci_पढ़ो_config_dword(pci_ha, tad_dram_rule[0], &reg);
	tad0 = m->addr <= TAD_LIMIT(reg);

	*channel_mask = 1 << channel;
	अगर (pvt->mirror_mode == FULL_MIRRORING ||
	    (pvt->mirror_mode == ADDR_RANGE_MIRRORING && tad0)) अणु
		*channel_mask |= 1 << ((channel + 2) % 4);
		pvt->is_cur_addr_mirrored = true;
	पूर्ण अन्यथा अणु
		pvt->is_cur_addr_mirrored = false;
	पूर्ण

	अगर (pvt->is_lockstep)
		*channel_mask |= 1 << ((channel + 1) % 4);

	वापस 0;
पूर्ण

/****************************************************************************
	Device initialization routines: put/get, init/निकास
 ****************************************************************************/

/*
 *	sbridge_put_all_devices	'put' all the devices that we have
 *				reserved via 'get'
 */
अटल व्योम sbridge_put_devices(काष्ठा sbridge_dev *sbridge_dev)
अणु
	पूर्णांक i;

	edac_dbg(0, "\n");
	क्रम (i = 0; i < sbridge_dev->n_devs; i++) अणु
		काष्ठा pci_dev *pdev = sbridge_dev->pdev[i];
		अगर (!pdev)
			जारी;
		edac_dbg(0, "Removing dev %02x:%02x.%d\n",
			 pdev->bus->number,
			 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));
		pci_dev_put(pdev);
	पूर्ण
पूर्ण

अटल व्योम sbridge_put_all_devices(व्योम)
अणु
	काष्ठा sbridge_dev *sbridge_dev, *पंचांगp;

	list_क्रम_each_entry_safe(sbridge_dev, पंचांगp, &sbridge_edac_list, list) अणु
		sbridge_put_devices(sbridge_dev);
		मुक्त_sbridge_dev(sbridge_dev);
	पूर्ण
पूर्ण

अटल पूर्णांक sbridge_get_onedevice(काष्ठा pci_dev **prev,
				 u8 *num_mc,
				 स्थिर काष्ठा pci_id_table *table,
				 स्थिर अचिन्हित devno,
				 स्थिर पूर्णांक multi_bus)
अणु
	काष्ठा sbridge_dev *sbridge_dev = शून्य;
	स्थिर काष्ठा pci_id_descr *dev_descr = &table->descr[devno];
	काष्ठा pci_dev *pdev = शून्य;
	पूर्णांक seg = 0;
	u8 bus = 0;
	पूर्णांक i = 0;

	sbridge_prपूर्णांकk(KERN_DEBUG,
		"Seeking for: PCI ID %04x:%04x\n",
		PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
			      dev_descr->dev_id, *prev);

	अगर (!pdev) अणु
		अगर (*prev) अणु
			*prev = pdev;
			वापस 0;
		पूर्ण

		अगर (dev_descr->optional)
			वापस 0;

		/* अगर the HA wasn't found */
		अगर (devno == 0)
			वापस -ENODEV;

		sbridge_prपूर्णांकk(KERN_INFO,
			"Device not found: %04x:%04x\n",
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

		/* End of list, leave */
		वापस -ENODEV;
	पूर्ण
	seg = pci_करोमुख्य_nr(pdev->bus);
	bus = pdev->bus->number;

next_imc:
	sbridge_dev = get_sbridge_dev(seg, bus, dev_descr->करोm,
				      multi_bus, sbridge_dev);
	अगर (!sbridge_dev) अणु
		/* If the HA1 wasn't found, don't create EDAC second memory controller */
		अगर (dev_descr->करोm == IMC1 && devno != 1) अणु
			edac_dbg(0, "Skip IMC1: %04x:%04x (since HA1 was absent)\n",
				 PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
			pci_dev_put(pdev);
			वापस 0;
		पूर्ण

		अगर (dev_descr->करोm == SOCK)
			जाओ out_imc;

		sbridge_dev = alloc_sbridge_dev(seg, bus, dev_descr->करोm, table);
		अगर (!sbridge_dev) अणु
			pci_dev_put(pdev);
			वापस -ENOMEM;
		पूर्ण
		(*num_mc)++;
	पूर्ण

	अगर (sbridge_dev->pdev[sbridge_dev->i_devs]) अणु
		sbridge_prपूर्णांकk(KERN_ERR,
			"Duplicated device for %04x:%04x\n",
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
		pci_dev_put(pdev);
		वापस -ENODEV;
	पूर्ण

	sbridge_dev->pdev[sbridge_dev->i_devs++] = pdev;

	/* pdev beदीर्घs to more than one IMC, करो extra माला_लो */
	अगर (++i > 1)
		pci_dev_get(pdev);

	अगर (dev_descr->करोm == SOCK && i < table->n_imcs_per_sock)
		जाओ next_imc;

out_imc:
	/* Be sure that the device is enabled */
	अगर (unlikely(pci_enable_device(pdev) < 0)) अणु
		sbridge_prपूर्णांकk(KERN_ERR,
			"Couldn't enable %04x:%04x\n",
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
		वापस -ENODEV;
	पूर्ण

	edac_dbg(0, "Detected %04x:%04x\n",
		 PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

	/*
	 * As stated on drivers/pci/search.c, the reference count क्रम
	 * @from is always decremented अगर it is not %शून्य. So, as we need
	 * to get all devices up to null, we need to करो a get क्रम the device
	 */
	pci_dev_get(pdev);

	*prev = pdev;

	वापस 0;
पूर्ण

/*
 * sbridge_get_all_devices - Find and perक्रमm 'get' operation on the MCH's
 *			     devices we want to reference क्रम this driver.
 * @num_mc: poपूर्णांकer to the memory controllers count, to be incremented in हाल
 *	    of success.
 * @table: model specअगरic table
 *
 * वापसs 0 in हाल of success or error code
 */
अटल पूर्णांक sbridge_get_all_devices(u8 *num_mc,
					स्थिर काष्ठा pci_id_table *table)
अणु
	पूर्णांक i, rc;
	काष्ठा pci_dev *pdev = शून्य;
	पूर्णांक allow_dups = 0;
	पूर्णांक multi_bus = 0;

	अगर (table->type == KNIGHTS_LANDING)
		allow_dups = multi_bus = 1;
	जबतक (table && table->descr) अणु
		क्रम (i = 0; i < table->n_devs_per_sock; i++) अणु
			अगर (!allow_dups || i == 0 ||
					table->descr[i].dev_id !=
						table->descr[i-1].dev_id) अणु
				pdev = शून्य;
			पूर्ण
			करो अणु
				rc = sbridge_get_onedevice(&pdev, num_mc,
							   table, i, multi_bus);
				अगर (rc < 0) अणु
					अगर (i == 0) अणु
						i = table->n_devs_per_sock;
						अवरोध;
					पूर्ण
					sbridge_put_all_devices();
					वापस -ENODEV;
				पूर्ण
			पूर्ण जबतक (pdev && !allow_dups);
		पूर्ण
		table++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Device IDs क्रम अणुSBRIDGE,IBRIDGE,HASWELL,BROADWELLपूर्ण_IMC_HA0_TAD0 are in
 * the क्रमmat: XXXa. So we can convert from a device to the corresponding
 * channel like this
 */
#घोषणा TAD_DEV_TO_CHAN(dev) (((dev) & 0xf) - 0xa)

अटल पूर्णांक sbridge_mci_bind_devs(काष्ठा mem_ctl_info *mci,
				 काष्ठा sbridge_dev *sbridge_dev)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	u8 saw_chan_mask = 0;
	पूर्णांक i;

	क्रम (i = 0; i < sbridge_dev->n_devs; i++) अणु
		pdev = sbridge_dev->pdev[i];
		अगर (!pdev)
			जारी;

		चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_SAD0:
			pvt->pci_sad0 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_SAD1:
			pvt->pci_sad1 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_BR:
			pvt->pci_br0 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_HA0:
			pvt->pci_ha = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TA:
			pvt->pci_ta = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_RAS:
			pvt->pci_ras = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TAD0:
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TAD1:
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TAD2:
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_TAD3:
		अणु
			पूर्णांक id = TAD_DEV_TO_CHAN(pdev->device);
			pvt->pci_tad[id] = pdev;
			saw_chan_mask |= 1 << id;
		पूर्ण
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_SBRIDGE_IMC_DDRIO:
			pvt->pci_ddrio = pdev;
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण

		edac_dbg(0, "Associated PCI %02x:%02x, bus %d with dev = %p\n",
			 pdev->venकरोr, pdev->device,
			 sbridge_dev->bus,
			 pdev);
	पूर्ण

	/* Check अगर everything were रेजिस्टरed */
	अगर (!pvt->pci_sad0 || !pvt->pci_sad1 || !pvt->pci_ha ||
	    !pvt->pci_ras || !pvt->pci_ta)
		जाओ enodev;

	अगर (saw_chan_mask != 0x0f)
		जाओ enodev;
	वापस 0;

enodev:
	sbridge_prपूर्णांकk(KERN_ERR, "Some needed devices are missing\n");
	वापस -ENODEV;

error:
	sbridge_prपूर्णांकk(KERN_ERR, "Unexpected device %02x:%02x\n",
		       PCI_VENDOR_ID_INTEL, pdev->device);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ibridge_mci_bind_devs(काष्ठा mem_ctl_info *mci,
				 काष्ठा sbridge_dev *sbridge_dev)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	u8 saw_chan_mask = 0;
	पूर्णांक i;

	क्रम (i = 0; i < sbridge_dev->n_devs; i++) अणु
		pdev = sbridge_dev->pdev[i];
		अगर (!pdev)
			जारी;

		चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1:
			pvt->pci_ha = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TA:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TA:
			pvt->pci_ta = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_RAS:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_RAS:
			pvt->pci_ras = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD0:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD1:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD2:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA0_TAD3:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD0:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD1:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD2:
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_HA1_TAD3:
		अणु
			पूर्णांक id = TAD_DEV_TO_CHAN(pdev->device);
			pvt->pci_tad[id] = pdev;
			saw_chan_mask |= 1 << id;
		पूर्ण
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_2HA_DDRIO0:
			pvt->pci_ddrio = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_IMC_1HA_DDRIO0:
			pvt->pci_ddrio = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_SAD:
			pvt->pci_sad0 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_BR0:
			pvt->pci_br0 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_IBRIDGE_BR1:
			pvt->pci_br1 = pdev;
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण

		edac_dbg(0, "Associated PCI %02x.%02d.%d with dev = %p\n",
			 sbridge_dev->bus,
			 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
			 pdev);
	पूर्ण

	/* Check अगर everything were रेजिस्टरed */
	अगर (!pvt->pci_sad0 || !pvt->pci_ha || !pvt->pci_br0 ||
	    !pvt->pci_br1 || !pvt->pci_ras || !pvt->pci_ta)
		जाओ enodev;

	अगर (saw_chan_mask != 0x0f && /* -EN/-EX */
	    saw_chan_mask != 0x03)   /* -EP */
		जाओ enodev;
	वापस 0;

enodev:
	sbridge_prपूर्णांकk(KERN_ERR, "Some needed devices are missing\n");
	वापस -ENODEV;

error:
	sbridge_prपूर्णांकk(KERN_ERR,
		       "Unexpected device %02x:%02x\n", PCI_VENDOR_ID_INTEL,
			pdev->device);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक haswell_mci_bind_devs(काष्ठा mem_ctl_info *mci,
				 काष्ठा sbridge_dev *sbridge_dev)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	u8 saw_chan_mask = 0;
	पूर्णांक i;

	/* there's only one device per प्रणाली; not tied to any bus */
	अगर (pvt->info.pci_vtd == शून्य)
		/* result will be checked later */
		pvt->info.pci_vtd = pci_get_device(PCI_VENDOR_ID_INTEL,
						   PCI_DEVICE_ID_INTEL_HASWELL_IMC_VTD_MISC,
						   शून्य);

	क्रम (i = 0; i < sbridge_dev->n_devs; i++) अणु
		pdev = sbridge_dev->pdev[i];
		अगर (!pdev)
			जारी;

		चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD0:
			pvt->pci_sad0 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD1:
			pvt->pci_sad1 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1:
			pvt->pci_ha = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TA:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TA:
			pvt->pci_ta = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TM:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TM:
			pvt->pci_ras = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD0:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD1:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD2:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD3:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD0:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD1:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD2:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD3:
		अणु
			पूर्णांक id = TAD_DEV_TO_CHAN(pdev->device);
			pvt->pci_tad[id] = pdev;
			saw_chan_mask |= 1 << id;
		पूर्ण
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO0:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO1:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO2:
		हाल PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO3:
			अगर (!pvt->pci_ddrio)
				pvt->pci_ddrio = pdev;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		edac_dbg(0, "Associated PCI %02x.%02d.%d with dev = %p\n",
			 sbridge_dev->bus,
			 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
			 pdev);
	पूर्ण

	/* Check अगर everything were रेजिस्टरed */
	अगर (!pvt->pci_sad0 || !pvt->pci_ha || !pvt->pci_sad1 ||
	    !pvt->pci_ras  || !pvt->pci_ta || !pvt->info.pci_vtd)
		जाओ enodev;

	अगर (saw_chan_mask != 0x0f && /* -EN/-EX */
	    saw_chan_mask != 0x03)   /* -EP */
		जाओ enodev;
	वापस 0;

enodev:
	sbridge_prपूर्णांकk(KERN_ERR, "Some needed devices are missing\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक broadwell_mci_bind_devs(काष्ठा mem_ctl_info *mci,
				 काष्ठा sbridge_dev *sbridge_dev)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	u8 saw_chan_mask = 0;
	पूर्णांक i;

	/* there's only one device per प्रणाली; not tied to any bus */
	अगर (pvt->info.pci_vtd == शून्य)
		/* result will be checked later */
		pvt->info.pci_vtd = pci_get_device(PCI_VENDOR_ID_INTEL,
						   PCI_DEVICE_ID_INTEL_BROADWELL_IMC_VTD_MISC,
						   शून्य);

	क्रम (i = 0; i < sbridge_dev->n_devs; i++) अणु
		pdev = sbridge_dev->pdev[i];
		अगर (!pdev)
			जारी;

		चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_CBO_SAD0:
			pvt->pci_sad0 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_CBO_SAD1:
			pvt->pci_sad1 = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1:
			pvt->pci_ha = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TA:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TA:
			pvt->pci_ta = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TM:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TM:
			pvt->pci_ras = pdev;
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD0:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD1:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD2:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD3:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD0:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD1:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD2:
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD3:
		अणु
			पूर्णांक id = TAD_DEV_TO_CHAN(pdev->device);
			pvt->pci_tad[id] = pdev;
			saw_chan_mask |= 1 << id;
		पूर्ण
			अवरोध;
		हाल PCI_DEVICE_ID_INTEL_BROADWELL_IMC_DDRIO0:
			pvt->pci_ddrio = pdev;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		edac_dbg(0, "Associated PCI %02x.%02d.%d with dev = %p\n",
			 sbridge_dev->bus,
			 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
			 pdev);
	पूर्ण

	/* Check अगर everything were रेजिस्टरed */
	अगर (!pvt->pci_sad0 || !pvt->pci_ha || !pvt->pci_sad1 ||
	    !pvt->pci_ras  || !pvt->pci_ta || !pvt->info.pci_vtd)
		जाओ enodev;

	अगर (saw_chan_mask != 0x0f && /* -EN/-EX */
	    saw_chan_mask != 0x03)   /* -EP */
		जाओ enodev;
	वापस 0;

enodev:
	sbridge_prपूर्णांकk(KERN_ERR, "Some needed devices are missing\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक knl_mci_bind_devs(काष्ठा mem_ctl_info *mci,
			काष्ठा sbridge_dev *sbridge_dev)
अणु
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	पूर्णांक dev, func;

	पूर्णांक i;
	पूर्णांक devidx;

	क्रम (i = 0; i < sbridge_dev->n_devs; i++) अणु
		pdev = sbridge_dev->pdev[i];
		अगर (!pdev)
			जारी;

		/* Extract PCI device and function. */
		dev = (pdev->devfn >> 3) & 0x1f;
		func = pdev->devfn & 0x7;

		चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_INTEL_KNL_IMC_MC:
			अगर (dev == 8)
				pvt->knl.pci_mc0 = pdev;
			अन्यथा अगर (dev == 9)
				pvt->knl.pci_mc1 = pdev;
			अन्यथा अणु
				sbridge_prपूर्णांकk(KERN_ERR,
					"Memory controller in unexpected place! (dev %d, fn %d)\n",
					dev, func);
				जारी;
			पूर्ण
			अवरोध;

		हाल PCI_DEVICE_ID_INTEL_KNL_IMC_SAD0:
			pvt->pci_sad0 = pdev;
			अवरोध;

		हाल PCI_DEVICE_ID_INTEL_KNL_IMC_SAD1:
			pvt->pci_sad1 = pdev;
			अवरोध;

		हाल PCI_DEVICE_ID_INTEL_KNL_IMC_CHA:
			/* There are one of these per tile, and range from
			 * 1.14.0 to 1.18.5.
			 */
			devidx = ((dev-14)*8)+func;

			अगर (devidx < 0 || devidx >= KNL_MAX_CHAS) अणु
				sbridge_prपूर्णांकk(KERN_ERR,
					"Caching and Home Agent in unexpected place! (dev %d, fn %d)\n",
					dev, func);
				जारी;
			पूर्ण

			WARN_ON(pvt->knl.pci_cha[devidx] != शून्य);

			pvt->knl.pci_cha[devidx] = pdev;
			अवरोध;

		हाल PCI_DEVICE_ID_INTEL_KNL_IMC_CHAN:
			devidx = -1;

			/*
			 *  MC0 channels 0-2 are device 9 function 2-4,
			 *  MC1 channels 3-5 are device 8 function 2-4.
			 */

			अगर (dev == 9)
				devidx = func-2;
			अन्यथा अगर (dev == 8)
				devidx = 3 + (func-2);

			अगर (devidx < 0 || devidx >= KNL_MAX_CHANNELS) अणु
				sbridge_prपूर्णांकk(KERN_ERR,
					"DRAM Channel Registers in unexpected place! (dev %d, fn %d)\n",
					dev, func);
				जारी;
			पूर्ण

			WARN_ON(pvt->knl.pci_channel[devidx] != शून्य);
			pvt->knl.pci_channel[devidx] = pdev;
			अवरोध;

		हाल PCI_DEVICE_ID_INTEL_KNL_IMC_TOLHM:
			pvt->knl.pci_mc_info = pdev;
			अवरोध;

		हाल PCI_DEVICE_ID_INTEL_KNL_IMC_TA:
			pvt->pci_ta = pdev;
			अवरोध;

		शेष:
			sbridge_prपूर्णांकk(KERN_ERR, "Unexpected device %d\n",
				pdev->device);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pvt->knl.pci_mc0  || !pvt->knl.pci_mc1 ||
	    !pvt->pci_sad0     || !pvt->pci_sad1    ||
	    !pvt->pci_ta) अणु
		जाओ enodev;
	पूर्ण

	क्रम (i = 0; i < KNL_MAX_CHANNELS; i++) अणु
		अगर (!pvt->knl.pci_channel[i]) अणु
			sbridge_prपूर्णांकk(KERN_ERR, "Missing channel %d\n", i);
			जाओ enodev;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < KNL_MAX_CHAS; i++) अणु
		अगर (!pvt->knl.pci_cha[i]) अणु
			sbridge_prपूर्णांकk(KERN_ERR, "Missing CHA %d\n", i);
			जाओ enodev;
		पूर्ण
	पूर्ण

	वापस 0;

enodev:
	sbridge_prपूर्णांकk(KERN_ERR, "Some needed devices are missing\n");
	वापस -ENODEV;
पूर्ण

/****************************************************************************
			Error check routines
 ****************************************************************************/

/*
 * While Sandy Bridge has error count रेजिस्टरs, SMI BIOS पढ़ो values from
 * and resets the counters. So, they are not reliable क्रम the OS to पढ़ो
 * from them. So, we have no option but to just trust on whatever MCE is
 * telling us about the errors.
 */
अटल व्योम sbridge_mce_output_error(काष्ठा mem_ctl_info *mci,
				    स्थिर काष्ठा mce *m)
अणु
	काष्ठा mem_ctl_info *new_mci;
	काष्ठा sbridge_pvt *pvt = mci->pvt_info;
	क्रमागत hw_event_mc_err_type tp_event;
	अक्षर *optype, msg[256];
	bool ripv = GET_BITFIELD(m->mcgstatus, 0, 0);
	bool overflow = GET_BITFIELD(m->status, 62, 62);
	bool uncorrected_error = GET_BITFIELD(m->status, 61, 61);
	bool recoverable;
	u32 core_err_cnt = GET_BITFIELD(m->status, 38, 52);
	u32 mscod = GET_BITFIELD(m->status, 16, 31);
	u32 errcode = GET_BITFIELD(m->status, 0, 15);
	u32 channel = GET_BITFIELD(m->status, 0, 3);
	u32 optypक्रमागत = GET_BITFIELD(m->status, 4, 6);
	/*
	 * Bits 5-0 of MCi_MISC give the least signअगरicant bit that is valid.
	 * A value 6 is क्रम cache line aligned address, a value 12 is क्रम page
	 * aligned address reported by patrol scrubber.
	 */
	u32 lsb = GET_BITFIELD(m->misc, 0, 5);
	दीर्घ channel_mask, first_channel;
	u8  rank = 0xff, socket, ha;
	पूर्णांक rc, dimm;
	अक्षर *area_type = "DRAM";

	अगर (pvt->info.type != SANDY_BRIDGE)
		recoverable = true;
	अन्यथा
		recoverable = GET_BITFIELD(m->status, 56, 56);

	अगर (uncorrected_error) अणु
		core_err_cnt = 1;
		अगर (ripv) अणु
			tp_event = HW_EVENT_ERR_UNCORRECTED;
		पूर्ण अन्यथा अणु
			tp_event = HW_EVENT_ERR_FATAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		tp_event = HW_EVENT_ERR_CORRECTED;
	पूर्ण

	/*
	 * According with Table 15-9 of the Intel Architecture spec vol 3A,
	 * memory errors should fit in this mask:
	 *	000f 0000 1mmm cccc (binary)
	 * where:
	 *	f = Correction Report Filtering Bit. If 1, subsequent errors
	 *	    won't be shown
	 *	mmm = error type
	 *	cccc = channel
	 * If the mask करोesn't match, report an error to the parsing logic
	 */
	चयन (optypक्रमागत) अणु
	हाल 0:
		optype = "generic undef request error";
		अवरोध;
	हाल 1:
		optype = "memory read error";
		अवरोध;
	हाल 2:
		optype = "memory write error";
		अवरोध;
	हाल 3:
		optype = "addr/cmd error";
		अवरोध;
	हाल 4:
		optype = "memory scrubbing error";
		अवरोध;
	शेष:
		optype = "reserved";
		अवरोध;
	पूर्ण

	अगर (pvt->info.type == KNIGHTS_LANDING) अणु
		अगर (channel == 14) अणु
			edac_dbg(0, "%s%s err_code:%04x:%04x EDRAM bank %d\n",
				overflow ? " OVERFLOW" : "",
				(uncorrected_error && recoverable)
				? " recoverable" : "",
				mscod, errcode,
				m->bank);
		पूर्ण अन्यथा अणु
			अक्षर A = *("A");

			/*
			 * Reported channel is in range 0-2, so we can't map it
			 * back to mc. To figure out mc we check machine check
			 * bank रेजिस्टर that reported this error.
			 * bank15 means mc0 and bank16 means mc1.
			 */
			channel = knl_channel_remap(m->bank == 16, channel);
			channel_mask = 1 << channel;

			snम_लिखो(msg, माप(msg),
				"%s%s err_code:%04x:%04x channel:%d (DIMM_%c)",
				overflow ? " OVERFLOW" : "",
				(uncorrected_error && recoverable)
				? " recoverable" : " ",
				mscod, errcode, channel, A + channel);
			edac_mc_handle_error(tp_event, mci, core_err_cnt,
				m->addr >> PAGE_SHIFT, m->addr & ~PAGE_MASK, 0,
				channel, 0, -1,
				optype, msg);
		पूर्ण
		वापस;
	पूर्ण अन्यथा अगर (lsb < 12) अणु
		rc = get_memory_error_data(mci, m->addr, &socket, &ha,
					   &channel_mask, &rank,
					   &area_type, msg);
	पूर्ण अन्यथा अणु
		rc = get_memory_error_data_from_mce(mci, m, &socket, &ha,
						    &channel_mask, msg);
	पूर्ण

	अगर (rc < 0)
		जाओ err_parsing;
	new_mci = get_mci_क्रम_node_id(socket, ha);
	अगर (!new_mci) अणु
		म_नकल(msg, "Error: socket got corrupted!");
		जाओ err_parsing;
	पूर्ण
	mci = new_mci;
	pvt = mci->pvt_info;

	first_channel = find_first_bit(&channel_mask, NUM_CHANNELS);

	अगर (rank == 0xff)
		dimm = -1;
	अन्यथा अगर (rank < 4)
		dimm = 0;
	अन्यथा अगर (rank < 8)
		dimm = 1;
	अन्यथा
		dimm = 2;

	/*
	 * FIXME: On some memory configurations (mirror, lockstep), the
	 * Memory Controller can't poपूर्णांक the error to a single DIMM. The
	 * EDAC core should be handling the channel mask, in order to poपूर्णांक
	 * to the group of dimm's where the error may be happening.
	 */
	अगर (!pvt->is_lockstep && !pvt->is_cur_addr_mirrored && !pvt->is_बंद_pg)
		channel = first_channel;

	snम_लिखो(msg, माप(msg),
		 "%s%s area:%s err_code:%04x:%04x socket:%d ha:%d channel_mask:%ld rank:%d",
		 overflow ? " OVERFLOW" : "",
		 (uncorrected_error && recoverable) ? " recoverable" : "",
		 area_type,
		 mscod, errcode,
		 socket, ha,
		 channel_mask,
		 rank);

	edac_dbg(0, "%s\n", msg);

	/* FIXME: need support क्रम channel mask */

	अगर (channel == CHANNEL_UNSPECIFIED)
		channel = -1;

	/* Call the helper to output message */
	edac_mc_handle_error(tp_event, mci, core_err_cnt,
			     m->addr >> PAGE_SHIFT, m->addr & ~PAGE_MASK, 0,
			     channel, dimm, -1,
			     optype, msg);
	वापस;
err_parsing:
	edac_mc_handle_error(tp_event, mci, core_err_cnt, 0, 0, 0,
			     -1, -1, -1,
			     msg, "");

पूर्ण

/*
 * Check that logging is enabled and that this is the right type
 * of error क्रम us to handle.
 */
अटल पूर्णांक sbridge_mce_check_error(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				   व्योम *data)
अणु
	काष्ठा mce *mce = (काष्ठा mce *)data;
	काष्ठा mem_ctl_info *mci;
	अक्षर *type;

	अगर (mce->kflags & MCE_HANDLED_CEC)
		वापस NOTIFY_DONE;

	/*
	 * Just let mcelog handle it अगर the error is
	 * outside the memory controller. A memory error
	 * is indicated by bit 7 = 1 and bits = 8-11,13-15 = 0.
	 * bit 12 has an special meaning.
	 */
	अगर ((mce->status & 0xefff) >> 7 != 1)
		वापस NOTIFY_DONE;

	/* Check ADDRV bit in STATUS */
	अगर (!GET_BITFIELD(mce->status, 58, 58))
		वापस NOTIFY_DONE;

	/* Check MISCV bit in STATUS */
	अगर (!GET_BITFIELD(mce->status, 59, 59))
		वापस NOTIFY_DONE;

	/* Check address type in MISC (physical address only) */
	अगर (GET_BITFIELD(mce->misc, 6, 8) != 2)
		वापस NOTIFY_DONE;

	mci = get_mci_क्रम_node_id(mce->socketid, IMC0);
	अगर (!mci)
		वापस NOTIFY_DONE;

	अगर (mce->mcgstatus & MCG_STATUS_MCIP)
		type = "Exception";
	अन्यथा
		type = "Event";

	sbridge_mc_prपूर्णांकk(mci, KERN_DEBUG, "HANDLING MCE MEMORY ERROR\n");

	sbridge_mc_prपूर्णांकk(mci, KERN_DEBUG, "CPU %d: Machine Check %s: %Lx "
			  "Bank %d: %016Lx\n", mce->extcpu, type,
			  mce->mcgstatus, mce->bank, mce->status);
	sbridge_mc_prपूर्णांकk(mci, KERN_DEBUG, "TSC %llx ", mce->tsc);
	sbridge_mc_prपूर्णांकk(mci, KERN_DEBUG, "ADDR %llx ", mce->addr);
	sbridge_mc_prपूर्णांकk(mci, KERN_DEBUG, "MISC %llx ", mce->misc);

	sbridge_mc_prपूर्णांकk(mci, KERN_DEBUG, "PROCESSOR %u:%x TIME %llu SOCKET "
			  "%u APIC %x\n", mce->cpuvenकरोr, mce->cpuid,
			  mce->समय, mce->socketid, mce->apicid);

	sbridge_mce_output_error(mci, mce);

	/* Advice mcelog that the error were handled */
	mce->kflags |= MCE_HANDLED_EDAC;
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block sbridge_mce_dec = अणु
	.notअगरier_call	= sbridge_mce_check_error,
	.priority	= MCE_PRIO_EDAC,
पूर्ण;

/****************************************************************************
			EDAC रेजिस्टर/unरेजिस्टर logic
 ****************************************************************************/

अटल व्योम sbridge_unरेजिस्टर_mci(काष्ठा sbridge_dev *sbridge_dev)
अणु
	काष्ठा mem_ctl_info *mci = sbridge_dev->mci;

	अगर (unlikely(!mci || !mci->pvt_info)) अणु
		edac_dbg(0, "MC: dev = %p\n", &sbridge_dev->pdev[0]->dev);

		sbridge_prपूर्णांकk(KERN_ERR, "Couldn't find mci handler\n");
		वापस;
	पूर्ण

	edac_dbg(0, "MC: mci = %p, dev = %p\n",
		 mci, &sbridge_dev->pdev[0]->dev);

	/* Remove MC sysfs nodes */
	edac_mc_del_mc(mci->pdev);

	edac_dbg(1, "%s: free mci struct\n", mci->ctl_name);
	kमुक्त(mci->ctl_name);
	edac_mc_मुक्त(mci);
	sbridge_dev->mci = शून्य;
पूर्ण

अटल पूर्णांक sbridge_रेजिस्टर_mci(काष्ठा sbridge_dev *sbridge_dev, क्रमागत type type)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा sbridge_pvt *pvt;
	काष्ठा pci_dev *pdev = sbridge_dev->pdev[0];
	पूर्णांक rc;

	/* allocate a new MC control काष्ठाure */
	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = type == KNIGHTS_LANDING ?
		KNL_MAX_CHANNELS : NUM_CHANNELS;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = type == KNIGHTS_LANDING ? 1 : MAX_DIMMS;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(sbridge_dev->mc, ARRAY_SIZE(layers), layers,
			    माप(*pvt));

	अगर (unlikely(!mci))
		वापस -ENOMEM;

	edac_dbg(0, "MC: mci = %p, dev = %p\n",
		 mci, &pdev->dev);

	pvt = mci->pvt_info;
	स_रखो(pvt, 0, माप(*pvt));

	/* Associate sbridge_dev and mci क्रम future usage */
	pvt->sbridge_dev = sbridge_dev;
	sbridge_dev->mci = mci;

	mci->mtype_cap = type == KNIGHTS_LANDING ?
		MEM_FLAG_DDR4 : MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = EDAC_MOD_STR;
	mci->dev_name = pci_name(pdev);
	mci->ctl_page_to_phys = शून्य;

	pvt->info.type = type;
	चयन (type) अणु
	हाल IVY_BRIDGE:
		pvt->info.rankcfgr = IB_RANK_CFG_A;
		pvt->info.get_tolm = ibridge_get_tolm;
		pvt->info.get_tohm = ibridge_get_tohm;
		pvt->info.dram_rule = ibridge_dram_rule;
		pvt->info.get_memory_type = get_memory_type;
		pvt->info.get_node_id = get_node_id;
		pvt->info.get_ha = ibridge_get_ha;
		pvt->info.rir_limit = rir_limit;
		pvt->info.sad_limit = sad_limit;
		pvt->info.पूर्णांकerleave_mode = पूर्णांकerleave_mode;
		pvt->info.dram_attr = dram_attr;
		pvt->info.max_sad = ARRAY_SIZE(ibridge_dram_rule);
		pvt->info.पूर्णांकerleave_list = ibridge_पूर्णांकerleave_list;
		pvt->info.पूर्णांकerleave_pkg = ibridge_पूर्णांकerleave_pkg;
		pvt->info.get_width = ibridge_get_width;

		/* Store pci devices at mci क्रम faster access */
		rc = ibridge_mci_bind_devs(mci, sbridge_dev);
		अगर (unlikely(rc < 0))
			जाओ fail0;
		get_source_id(mci);
		mci->ctl_name = kaप्र_लिखो(GFP_KERNEL, "Ivy Bridge SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->करोm);
		अवरोध;
	हाल SANDY_BRIDGE:
		pvt->info.rankcfgr = SB_RANK_CFG_A;
		pvt->info.get_tolm = sbridge_get_tolm;
		pvt->info.get_tohm = sbridge_get_tohm;
		pvt->info.dram_rule = sbridge_dram_rule;
		pvt->info.get_memory_type = get_memory_type;
		pvt->info.get_node_id = get_node_id;
		pvt->info.get_ha = sbridge_get_ha;
		pvt->info.rir_limit = rir_limit;
		pvt->info.sad_limit = sad_limit;
		pvt->info.पूर्णांकerleave_mode = पूर्णांकerleave_mode;
		pvt->info.dram_attr = dram_attr;
		pvt->info.max_sad = ARRAY_SIZE(sbridge_dram_rule);
		pvt->info.पूर्णांकerleave_list = sbridge_पूर्णांकerleave_list;
		pvt->info.पूर्णांकerleave_pkg = sbridge_पूर्णांकerleave_pkg;
		pvt->info.get_width = sbridge_get_width;

		/* Store pci devices at mci क्रम faster access */
		rc = sbridge_mci_bind_devs(mci, sbridge_dev);
		अगर (unlikely(rc < 0))
			जाओ fail0;
		get_source_id(mci);
		mci->ctl_name = kaप्र_लिखो(GFP_KERNEL, "Sandy Bridge SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->करोm);
		अवरोध;
	हाल HASWELL:
		/* rankcfgr isn't used */
		pvt->info.get_tolm = haswell_get_tolm;
		pvt->info.get_tohm = haswell_get_tohm;
		pvt->info.dram_rule = ibridge_dram_rule;
		pvt->info.get_memory_type = haswell_get_memory_type;
		pvt->info.get_node_id = haswell_get_node_id;
		pvt->info.get_ha = ibridge_get_ha;
		pvt->info.rir_limit = haswell_rir_limit;
		pvt->info.sad_limit = sad_limit;
		pvt->info.पूर्णांकerleave_mode = पूर्णांकerleave_mode;
		pvt->info.dram_attr = dram_attr;
		pvt->info.max_sad = ARRAY_SIZE(ibridge_dram_rule);
		pvt->info.पूर्णांकerleave_list = ibridge_पूर्णांकerleave_list;
		pvt->info.पूर्णांकerleave_pkg = ibridge_पूर्णांकerleave_pkg;
		pvt->info.get_width = ibridge_get_width;

		/* Store pci devices at mci क्रम faster access */
		rc = haswell_mci_bind_devs(mci, sbridge_dev);
		अगर (unlikely(rc < 0))
			जाओ fail0;
		get_source_id(mci);
		mci->ctl_name = kaप्र_लिखो(GFP_KERNEL, "Haswell SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->करोm);
		अवरोध;
	हाल BROADWELL:
		/* rankcfgr isn't used */
		pvt->info.get_tolm = haswell_get_tolm;
		pvt->info.get_tohm = haswell_get_tohm;
		pvt->info.dram_rule = ibridge_dram_rule;
		pvt->info.get_memory_type = haswell_get_memory_type;
		pvt->info.get_node_id = haswell_get_node_id;
		pvt->info.get_ha = ibridge_get_ha;
		pvt->info.rir_limit = haswell_rir_limit;
		pvt->info.sad_limit = sad_limit;
		pvt->info.पूर्णांकerleave_mode = पूर्णांकerleave_mode;
		pvt->info.dram_attr = dram_attr;
		pvt->info.max_sad = ARRAY_SIZE(ibridge_dram_rule);
		pvt->info.पूर्णांकerleave_list = ibridge_पूर्णांकerleave_list;
		pvt->info.पूर्णांकerleave_pkg = ibridge_पूर्णांकerleave_pkg;
		pvt->info.get_width = broadwell_get_width;

		/* Store pci devices at mci क्रम faster access */
		rc = broadwell_mci_bind_devs(mci, sbridge_dev);
		अगर (unlikely(rc < 0))
			जाओ fail0;
		get_source_id(mci);
		mci->ctl_name = kaप्र_लिखो(GFP_KERNEL, "Broadwell SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->करोm);
		अवरोध;
	हाल KNIGHTS_LANDING:
		/* pvt->info.rankcfgr == ??? */
		pvt->info.get_tolm = knl_get_tolm;
		pvt->info.get_tohm = knl_get_tohm;
		pvt->info.dram_rule = knl_dram_rule;
		pvt->info.get_memory_type = knl_get_memory_type;
		pvt->info.get_node_id = knl_get_node_id;
		pvt->info.get_ha = knl_get_ha;
		pvt->info.rir_limit = शून्य;
		pvt->info.sad_limit = knl_sad_limit;
		pvt->info.पूर्णांकerleave_mode = knl_पूर्णांकerleave_mode;
		pvt->info.dram_attr = dram_attr_knl;
		pvt->info.max_sad = ARRAY_SIZE(knl_dram_rule);
		pvt->info.पूर्णांकerleave_list = knl_पूर्णांकerleave_list;
		pvt->info.पूर्णांकerleave_pkg = ibridge_पूर्णांकerleave_pkg;
		pvt->info.get_width = knl_get_width;

		rc = knl_mci_bind_devs(mci, sbridge_dev);
		अगर (unlikely(rc < 0))
			जाओ fail0;
		get_source_id(mci);
		mci->ctl_name = kaप्र_लिखो(GFP_KERNEL, "Knights Landing SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->करोm);
		अवरोध;
	पूर्ण

	अगर (!mci->ctl_name) अणु
		rc = -ENOMEM;
		जाओ fail0;
	पूर्ण

	/* Get dimm basic config and the memory layout */
	rc = get_dimm_config(mci);
	अगर (rc < 0) अणु
		edac_dbg(0, "MC: failed to get_dimm_config()\n");
		जाओ fail;
	पूर्ण
	get_memory_layout(mci);

	/* record ptr to the generic device */
	mci->pdev = &pdev->dev;

	/* add this new MC control काष्ठाure to EDAC's list of MCs */
	अगर (unlikely(edac_mc_add_mc(mci))) अणु
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		rc = -EINVAL;
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	kमुक्त(mci->ctl_name);
fail0:
	edac_mc_मुक्त(mci);
	sbridge_dev->mci = शून्य;
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id sbridge_cpuids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE_X, &pci_dev_descr_sbridge_table),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE_X,	  &pci_dev_descr_ibridge_table),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_X,	  &pci_dev_descr_haswell_table),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X,	  &pci_dev_descr_broadwell_table),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_D,	  &pci_dev_descr_broadwell_table),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNL,  &pci_dev_descr_knl_table),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNM,  &pci_dev_descr_knl_table),
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, sbridge_cpuids);

/*
 *	sbridge_probe	Get all devices and रेजिस्टर memory controllers
 *			present.
 *	वापस:
 *		0 क्रम FOUND a device
 *		< 0 क्रम error code
 */

अटल पूर्णांक sbridge_probe(स्थिर काष्ठा x86_cpu_id *id)
अणु
	पूर्णांक rc = -ENODEV;
	u8 mc, num_mc = 0;
	काष्ठा sbridge_dev *sbridge_dev;
	काष्ठा pci_id_table *ptable = (काष्ठा pci_id_table *)id->driver_data;

	/* get the pci devices we want to reserve क्रम our use */
	rc = sbridge_get_all_devices(&num_mc, ptable);

	अगर (unlikely(rc < 0)) अणु
		edac_dbg(0, "couldn't get all devices\n");
		जाओ fail0;
	पूर्ण

	mc = 0;

	list_क्रम_each_entry(sbridge_dev, &sbridge_edac_list, list) अणु
		edac_dbg(0, "Registering MC#%d (%d of %d)\n",
			 mc, mc + 1, num_mc);

		sbridge_dev->mc = mc++;
		rc = sbridge_रेजिस्टर_mci(sbridge_dev, ptable->type);
		अगर (unlikely(rc < 0))
			जाओ fail1;
	पूर्ण

	sbridge_prपूर्णांकk(KERN_INFO, "%s\n", SBRIDGE_REVISION);

	वापस 0;

fail1:
	list_क्रम_each_entry(sbridge_dev, &sbridge_edac_list, list)
		sbridge_unरेजिस्टर_mci(sbridge_dev);

	sbridge_put_all_devices();
fail0:
	वापस rc;
पूर्ण

/*
 *	sbridge_हटाओ	cleanup
 *
 */
अटल व्योम sbridge_हटाओ(व्योम)
अणु
	काष्ठा sbridge_dev *sbridge_dev;

	edac_dbg(0, "\n");

	list_क्रम_each_entry(sbridge_dev, &sbridge_edac_list, list)
		sbridge_unरेजिस्टर_mci(sbridge_dev);

	/* Release PCI resources */
	sbridge_put_all_devices();
पूर्ण

/*
 *	sbridge_init		Module entry function
 *			Try to initialize this module क्रम its devices
 */
अटल पूर्णांक __init sbridge_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	स्थिर अक्षर *owner;
	पूर्णांक rc;

	edac_dbg(2, "\n");

	owner = edac_get_owner();
	अगर (owner && म_भेदन(owner, EDAC_MOD_STR, माप(EDAC_MOD_STR)))
		वापस -EBUSY;

	id = x86_match_cpu(sbridge_cpuids);
	अगर (!id)
		वापस -ENODEV;

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	rc = sbridge_probe(id);

	अगर (rc >= 0) अणु
		mce_रेजिस्टर_decode_chain(&sbridge_mce_dec);
		वापस 0;
	पूर्ण

	sbridge_prपूर्णांकk(KERN_ERR, "Failed to register device with error %d.\n",
		      rc);

	वापस rc;
पूर्ण

/*
 *	sbridge_निकास()	Module निकास function
 *			Unरेजिस्टर the driver
 */
अटल व्योम __निकास sbridge_निकास(व्योम)
अणु
	edac_dbg(2, "\n");
	sbridge_हटाओ();
	mce_unरेजिस्टर_decode_chain(&sbridge_mce_dec);
पूर्ण

module_init(sbridge_init);
module_निकास(sbridge_निकास);

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_AUTHOR("Red Hat Inc. (https://www.redhat.com)");
MODULE_DESCRIPTION("MC Driver for Intel Sandy Bridge and Ivy Bridge memory controllers - "
		   SBRIDGE_REVISION);
