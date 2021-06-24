<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Intel i7 core/Nehalem Memory Controller kernel module
 *
 * This driver supports the memory controllers found on the Intel
 * processor families i7core, i7core 7xx/8xx, i5core, Xeon 35xx,
 * Xeon 55xx and Xeon 56xx also known as Nehalem, Nehalem-EP, Lynnfield
 * and Wesपंचांगere-EP.
 *
 * Copyright (c) 2009-2010 by:
 *	 Mauro Carvalho Chehab
 *
 * Red Hat Inc. https://www.redhat.com
 *
 * Forked and adapted from the i5400_edac driver
 *
 * Based on the following खुला Intel datasheets:
 * Intel Core i7 Processor Extreme Edition and Intel Core i7 Processor
 * Datasheet, Volume 2:
 *	http://करोwnload.पूर्णांकel.com/design/processor/datashts/320835.pdf
 * Intel Xeon Processor 5500 Series Datasheet Volume 2
 *	http://www.पूर्णांकel.com/Assets/PDF/datasheet/321322.pdf
 * also available at:
 * 	http://www.arrownac.com/manufacturers/पूर्णांकel/s/nehalem/5500-datasheet-v2.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/edac.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "edac_module.h"

/* Static vars */
अटल LIST_HEAD(i7core_edac_list);
अटल DEFINE_MUTEX(i7core_edac_lock);
अटल पूर्णांक probed;

अटल पूर्णांक use_pci_fixup;
module_param(use_pci_fixup, पूर्णांक, 0444);
MODULE_PARM_DESC(use_pci_fixup, "Enable PCI fixup to seek for hidden devices");
/*
 * This is used क्रम Nehalem-EP and Nehalem-EX devices, where the non-core
 * रेजिस्टरs start at bus 255, and are not reported by BIOS.
 * We currently find devices with only 2 sockets. In order to support more QPI
 * Quick Path Interconnect, just increment this number.
 */
#घोषणा MAX_SOCKET_BUSES	2


/*
 * Alter this version क्रम the module when modअगरications are made
 */
#घोषणा I7CORE_REVISION    " Ver: 1.0.0"
#घोषणा EDAC_MOD_STR      "i7core_edac"

/*
 * Debug macros
 */
#घोषणा i7core_prपूर्णांकk(level, fmt, arg...)			\
	edac_prपूर्णांकk(level, "i7core", fmt, ##arg)

#घोषणा i7core_mc_prपूर्णांकk(mci, level, fmt, arg...)		\
	edac_mc_chipset_prपूर्णांकk(mci, level, "i7core", fmt, ##arg)

/*
 * i7core Memory Controller Registers
 */

	/* OFFSETS क्रम Device 0 Function 0 */

#घोषणा MC_CFG_CONTROL	0x90
  #घोषणा MC_CFG_UNLOCK		0x02
  #घोषणा MC_CFG_LOCK		0x00

	/* OFFSETS क्रम Device 3 Function 0 */

#घोषणा MC_CONTROL	0x48
#घोषणा MC_STATUS	0x4c
#घोषणा MC_MAX_DOD	0x64

/*
 * OFFSETS क्रम Device 3 Function 4, as indicated on Xeon 5500 datasheet:
 * http://www.arrownac.com/manufacturers/पूर्णांकel/s/nehalem/5500-datasheet-v2.pdf
 */

#घोषणा MC_TEST_ERR_RCV1	0x60
  #घोषणा DIMM2_COR_ERR(r)			((r) & 0x7fff)

#घोषणा MC_TEST_ERR_RCV0	0x64
  #घोषणा DIMM1_COR_ERR(r)			(((r) >> 16) & 0x7fff)
  #घोषणा DIMM0_COR_ERR(r)			((r) & 0x7fff)

/* OFFSETS क्रम Device 3 Function 2, as indicated on Xeon 5500 datasheet */
#घोषणा MC_SSRCONTROL		0x48
  #घोषणा SSR_MODE_DISABLE	0x00
  #घोषणा SSR_MODE_ENABLE	0x01
  #घोषणा SSR_MODE_MASK		0x03

#घोषणा MC_SCRUB_CONTROL	0x4c
  #घोषणा STARTSCRUB		(1 << 24)
  #घोषणा SCRUBINTERVAL_MASK    0xffffff

#घोषणा MC_COR_ECC_CNT_0	0x80
#घोषणा MC_COR_ECC_CNT_1	0x84
#घोषणा MC_COR_ECC_CNT_2	0x88
#घोषणा MC_COR_ECC_CNT_3	0x8c
#घोषणा MC_COR_ECC_CNT_4	0x90
#घोषणा MC_COR_ECC_CNT_5	0x94

#घोषणा DIMM_TOP_COR_ERR(r)			(((r) >> 16) & 0x7fff)
#घोषणा DIMM_BOT_COR_ERR(r)			((r) & 0x7fff)


	/* OFFSETS क्रम Devices 4,5 and 6 Function 0 */

#घोषणा MC_CHANNEL_DIMM_INIT_PARAMS 0x58
  #घोषणा THREE_DIMMS_PRESENT		(1 << 24)
  #घोषणा SINGLE_QUAD_RANK_PRESENT	(1 << 23)
  #घोषणा QUAD_RANK_PRESENT		(1 << 22)
  #घोषणा REGISTERED_DIMM		(1 << 15)

#घोषणा MC_CHANNEL_MAPPER	0x60
  #घोषणा RDLCH(r, ch)		((((r) >> (3 + (ch * 6))) & 0x07) - 1)
  #घोषणा WRLCH(r, ch)		((((r) >> (ch * 6)) & 0x07) - 1)

#घोषणा MC_CHANNEL_RANK_PRESENT 0x7c
  #घोषणा RANK_PRESENT_MASK		0xffff

#घोषणा MC_CHANNEL_ADDR_MATCH	0xf0
#घोषणा MC_CHANNEL_ERROR_MASK	0xf8
#घोषणा MC_CHANNEL_ERROR_INJECT	0xfc
  #घोषणा INJECT_ADDR_PARITY	0x10
  #घोषणा INJECT_ECC		0x08
  #घोषणा MASK_CACHELINE	0x06
  #घोषणा MASK_FULL_CACHELINE	0x06
  #घोषणा MASK_MSB32_CACHELINE	0x04
  #घोषणा MASK_LSB32_CACHELINE	0x02
  #घोषणा NO_MASK_CACHELINE	0x00
  #घोषणा REPEAT_EN		0x01

	/* OFFSETS क्रम Devices 4,5 and 6 Function 1 */

#घोषणा MC_DOD_CH_DIMM0		0x48
#घोषणा MC_DOD_CH_DIMM1		0x4c
#घोषणा MC_DOD_CH_DIMM2		0x50
  #घोषणा RANKOFFSET_MASK	((1 << 12) | (1 << 11) | (1 << 10))
  #घोषणा RANKOFFSET(x)		((x & RANKOFFSET_MASK) >> 10)
  #घोषणा DIMM_PRESENT_MASK	(1 << 9)
  #घोषणा DIMM_PRESENT(x)	(((x) & DIMM_PRESENT_MASK) >> 9)
  #घोषणा MC_DOD_NUMBANK_MASK		((1 << 8) | (1 << 7))
  #घोषणा MC_DOD_NUMBANK(x)		(((x) & MC_DOD_NUMBANK_MASK) >> 7)
  #घोषणा MC_DOD_NUMRANK_MASK		((1 << 6) | (1 << 5))
  #घोषणा MC_DOD_NUMRANK(x)		(((x) & MC_DOD_NUMRANK_MASK) >> 5)
  #घोषणा MC_DOD_NUMROW_MASK		((1 << 4) | (1 << 3) | (1 << 2))
  #घोषणा MC_DOD_NUMROW(x)		(((x) & MC_DOD_NUMROW_MASK) >> 2)
  #घोषणा MC_DOD_NUMCOL_MASK		3
  #घोषणा MC_DOD_NUMCOL(x)		((x) & MC_DOD_NUMCOL_MASK)

#घोषणा MC_RANK_PRESENT		0x7c

#घोषणा MC_SAG_CH_0	0x80
#घोषणा MC_SAG_CH_1	0x84
#घोषणा MC_SAG_CH_2	0x88
#घोषणा MC_SAG_CH_3	0x8c
#घोषणा MC_SAG_CH_4	0x90
#घोषणा MC_SAG_CH_5	0x94
#घोषणा MC_SAG_CH_6	0x98
#घोषणा MC_SAG_CH_7	0x9c

#घोषणा MC_RIR_LIMIT_CH_0	0x40
#घोषणा MC_RIR_LIMIT_CH_1	0x44
#घोषणा MC_RIR_LIMIT_CH_2	0x48
#घोषणा MC_RIR_LIMIT_CH_3	0x4C
#घोषणा MC_RIR_LIMIT_CH_4	0x50
#घोषणा MC_RIR_LIMIT_CH_5	0x54
#घोषणा MC_RIR_LIMIT_CH_6	0x58
#घोषणा MC_RIR_LIMIT_CH_7	0x5C
#घोषणा MC_RIR_LIMIT_MASK	((1 << 10) - 1)

#घोषणा MC_RIR_WAY_CH		0x80
  #घोषणा MC_RIR_WAY_OFFSET_MASK	(((1 << 14) - 1) & ~0x7)
  #घोषणा MC_RIR_WAY_RANK_MASK		0x7

/*
 * i7core काष्ठाs
 */

#घोषणा NUM_CHANS 3
#घोषणा MAX_DIMMS 3		/* Max DIMMS per channel */
#घोषणा MAX_MCR_FUNC  4
#घोषणा MAX_CHAN_FUNC 3

काष्ठा i7core_info अणु
	u32	mc_control;
	u32	mc_status;
	u32	max_करोd;
	u32	ch_map;
पूर्ण;


काष्ठा i7core_inject अणु
	पूर्णांक	enable;

	u32	section;
	u32	type;
	u32	eccmask;

	/* Error address mask */
	पूर्णांक channel, dimm, rank, bank, page, col;
पूर्ण;

काष्ठा i7core_channel अणु
	bool		is_3dimms_present;
	bool		is_single_4rank;
	bool		has_4rank;
	u32		dimms;
पूर्ण;

काष्ठा pci_id_descr अणु
	पूर्णांक			dev;
	पूर्णांक			func;
	पूर्णांक 			dev_id;
	पूर्णांक			optional;
पूर्ण;

काष्ठा pci_id_table अणु
	स्थिर काष्ठा pci_id_descr	*descr;
	पूर्णांक				n_devs;
पूर्ण;

काष्ठा i7core_dev अणु
	काष्ठा list_head	list;
	u8			socket;
	काष्ठा pci_dev		**pdev;
	पूर्णांक			n_devs;
	काष्ठा mem_ctl_info	*mci;
पूर्ण;

काष्ठा i7core_pvt अणु
	काष्ठा device *addrmatch_dev, *chancounts_dev;

	काष्ठा pci_dev	*pci_noncore;
	काष्ठा pci_dev	*pci_mcr[MAX_MCR_FUNC + 1];
	काष्ठा pci_dev	*pci_ch[NUM_CHANS][MAX_CHAN_FUNC + 1];

	काष्ठा i7core_dev *i7core_dev;

	काष्ठा i7core_info	info;
	काष्ठा i7core_inject	inject;
	काष्ठा i7core_channel	channel[NUM_CHANS];

	पूर्णांक		ce_count_available;

			/* ECC corrected errors counts per udimm */
	अचिन्हित दीर्घ	udimm_ce_count[MAX_DIMMS];
	पूर्णांक		udimm_last_ce_count[MAX_DIMMS];
			/* ECC corrected errors counts per rdimm */
	अचिन्हित दीर्घ	rdimm_ce_count[NUM_CHANS][MAX_DIMMS];
	पूर्णांक		rdimm_last_ce_count[NUM_CHANS][MAX_DIMMS];

	bool		is_रेजिस्टरed, enable_scrub;

	/* DCLK Frequency used क्रम computing scrub rate */
	पूर्णांक			dclk_freq;

	/* Struct to control EDAC polling */
	काष्ठा edac_pci_ctl_info *i7core_pci;
पूर्ण;

#घोषणा PCI_DESCR(device, function, device_id)	\
	.dev = (device),			\
	.func = (function),			\
	.dev_id = (device_id)

अटल स्थिर काष्ठा pci_id_descr pci_dev_descr_i7core_nehalem[] = अणु
		/* Memory controller */
	अणु PCI_DESCR(3, 0, PCI_DEVICE_ID_INTEL_I7_MCR)     पूर्ण,
	अणु PCI_DESCR(3, 1, PCI_DEVICE_ID_INTEL_I7_MC_TAD)  पूर्ण,
			/* Exists only क्रम RDIMM */
	अणु PCI_DESCR(3, 2, PCI_DEVICE_ID_INTEL_I7_MC_RAS), .optional = 1  पूर्ण,
	अणु PCI_DESCR(3, 4, PCI_DEVICE_ID_INTEL_I7_MC_TEST) पूर्ण,

		/* Channel 0 */
	अणु PCI_DESCR(4, 0, PCI_DEVICE_ID_INTEL_I7_MC_CH0_CTRL) पूर्ण,
	अणु PCI_DESCR(4, 1, PCI_DEVICE_ID_INTEL_I7_MC_CH0_ADDR) पूर्ण,
	अणु PCI_DESCR(4, 2, PCI_DEVICE_ID_INTEL_I7_MC_CH0_RANK) पूर्ण,
	अणु PCI_DESCR(4, 3, PCI_DEVICE_ID_INTEL_I7_MC_CH0_TC)   पूर्ण,

		/* Channel 1 */
	अणु PCI_DESCR(5, 0, PCI_DEVICE_ID_INTEL_I7_MC_CH1_CTRL) पूर्ण,
	अणु PCI_DESCR(5, 1, PCI_DEVICE_ID_INTEL_I7_MC_CH1_ADDR) पूर्ण,
	अणु PCI_DESCR(5, 2, PCI_DEVICE_ID_INTEL_I7_MC_CH1_RANK) पूर्ण,
	अणु PCI_DESCR(5, 3, PCI_DEVICE_ID_INTEL_I7_MC_CH1_TC)   पूर्ण,

		/* Channel 2 */
	अणु PCI_DESCR(6, 0, PCI_DEVICE_ID_INTEL_I7_MC_CH2_CTRL) पूर्ण,
	अणु PCI_DESCR(6, 1, PCI_DEVICE_ID_INTEL_I7_MC_CH2_ADDR) पूर्ण,
	अणु PCI_DESCR(6, 2, PCI_DEVICE_ID_INTEL_I7_MC_CH2_RANK) पूर्ण,
	अणु PCI_DESCR(6, 3, PCI_DEVICE_ID_INTEL_I7_MC_CH2_TC)   पूर्ण,

		/* Generic Non-core रेजिस्टरs */
	/*
	 * This is the PCI device on i7core and on Xeon 35xx (8086:2c41)
	 * On Xeon 55xx, however, it has a dअगरferent id (8086:2c40). So,
	 * the probing code needs to test क्रम the other address in हाल of
	 * failure of this one
	 */
	अणु PCI_DESCR(0, 0, PCI_DEVICE_ID_INTEL_I7_NONCORE)  पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा pci_id_descr pci_dev_descr_lynnfield[] = अणु
	अणु PCI_DESCR( 3, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_MCR)         पूर्ण,
	अणु PCI_DESCR( 3, 1, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_TAD)      पूर्ण,
	अणु PCI_DESCR( 3, 4, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_TEST)     पूर्ण,

	अणु PCI_DESCR( 4, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH0_CTRL) पूर्ण,
	अणु PCI_DESCR( 4, 1, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH0_ADDR) पूर्ण,
	अणु PCI_DESCR( 4, 2, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH0_RANK) पूर्ण,
	अणु PCI_DESCR( 4, 3, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH0_TC)   पूर्ण,

	अणु PCI_DESCR( 5, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH1_CTRL) पूर्ण,
	अणु PCI_DESCR( 5, 1, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH1_ADDR) पूर्ण,
	अणु PCI_DESCR( 5, 2, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH1_RANK) पूर्ण,
	अणु PCI_DESCR( 5, 3, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH1_TC)   पूर्ण,

	/*
	 * This is the PCI device has an alternate address on some
	 * processors like Core i7 860
	 */
	अणु PCI_DESCR( 0, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_NONCORE)     पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_id_descr pci_dev_descr_i7core_wesपंचांगere[] = अणु
		/* Memory controller */
	अणु PCI_DESCR(3, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_MCR_REV2)     पूर्ण,
	अणु PCI_DESCR(3, 1, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_TAD_REV2)  पूर्ण,
			/* Exists only क्रम RDIMM */
	अणु PCI_DESCR(3, 2, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_RAS_REV2), .optional = 1  पूर्ण,
	अणु PCI_DESCR(3, 4, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_TEST_REV2) पूर्ण,

		/* Channel 0 */
	अणु PCI_DESCR(4, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH0_CTRL_REV2) पूर्ण,
	अणु PCI_DESCR(4, 1, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH0_ADDR_REV2) पूर्ण,
	अणु PCI_DESCR(4, 2, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH0_RANK_REV2) पूर्ण,
	अणु PCI_DESCR(4, 3, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH0_TC_REV2)   पूर्ण,

		/* Channel 1 */
	अणु PCI_DESCR(5, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH1_CTRL_REV2) पूर्ण,
	अणु PCI_DESCR(5, 1, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH1_ADDR_REV2) पूर्ण,
	अणु PCI_DESCR(5, 2, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH1_RANK_REV2) पूर्ण,
	अणु PCI_DESCR(5, 3, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH1_TC_REV2)   पूर्ण,

		/* Channel 2 */
	अणु PCI_DESCR(6, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH2_CTRL_REV2) पूर्ण,
	अणु PCI_DESCR(6, 1, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH2_ADDR_REV2) पूर्ण,
	अणु PCI_DESCR(6, 2, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH2_RANK_REV2) पूर्ण,
	अणु PCI_DESCR(6, 3, PCI_DEVICE_ID_INTEL_LYNNFIELD_MC_CH2_TC_REV2)   पूर्ण,

		/* Generic Non-core रेजिस्टरs */
	अणु PCI_DESCR(0, 0, PCI_DEVICE_ID_INTEL_LYNNFIELD_NONCORE_REV2)  पूर्ण,

पूर्ण;

#घोषणा PCI_ID_TABLE_ENTRY(A) अणु .descr=A, .n_devs = ARRAY_SIZE(A) पूर्ण
अटल स्थिर काष्ठा pci_id_table pci_dev_table[] = अणु
	PCI_ID_TABLE_ENTRY(pci_dev_descr_i7core_nehalem),
	PCI_ID_TABLE_ENTRY(pci_dev_descr_lynnfield),
	PCI_ID_TABLE_ENTRY(pci_dev_descr_i7core_wesपंचांगere),
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

/*
 *	pci_device_id	table क्रम which devices we are looking क्रम
 */
अटल स्थिर काष्ठा pci_device_id i7core_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_X58_HUB_MGMT)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_LYNNFIELD_QPI_LINK0)पूर्ण,
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

/****************************************************************************
			Ancillary status routines
 ****************************************************************************/

	/* MC_CONTROL bits */
#घोषणा CH_ACTIVE(pvt, ch)	((pvt)->info.mc_control & (1 << (8 + ch)))
#घोषणा ECCx8(pvt)		((pvt)->info.mc_control & (1 << 1))

	/* MC_STATUS bits */
#घोषणा ECC_ENABLED(pvt)	((pvt)->info.mc_status & (1 << 4))
#घोषणा CH_DISABLED(pvt, ch)	((pvt)->info.mc_status & (1 << ch))

	/* MC_MAX_DOD पढ़ो functions */
अटल अंतरभूत पूर्णांक numdimms(u32 dimms)
अणु
	वापस (dimms & 0x3) + 1;
पूर्ण

अटल अंतरभूत पूर्णांक numrank(u32 rank)
अणु
	अटल स्थिर पूर्णांक ranks[] = अणु 1, 2, 4, -EINVAL पूर्ण;

	वापस ranks[rank & 0x3];
पूर्ण

अटल अंतरभूत पूर्णांक numbank(u32 bank)
अणु
	अटल स्थिर पूर्णांक banks[] = अणु 4, 8, 16, -EINVAL पूर्ण;

	वापस banks[bank & 0x3];
पूर्ण

अटल अंतरभूत पूर्णांक numrow(u32 row)
अणु
	अटल स्थिर पूर्णांक rows[] = अणु
		1 << 12, 1 << 13, 1 << 14, 1 << 15,
		1 << 16, -EINVAL, -EINVAL, -EINVAL,
	पूर्ण;

	वापस rows[row & 0x7];
पूर्ण

अटल अंतरभूत पूर्णांक numcol(u32 col)
अणु
	अटल स्थिर पूर्णांक cols[] = अणु
		1 << 10, 1 << 11, 1 << 12, -EINVAL,
	पूर्ण;
	वापस cols[col & 0x3];
पूर्ण

अटल काष्ठा i7core_dev *get_i7core_dev(u8 socket)
अणु
	काष्ठा i7core_dev *i7core_dev;

	list_क्रम_each_entry(i7core_dev, &i7core_edac_list, list) अणु
		अगर (i7core_dev->socket == socket)
			वापस i7core_dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा i7core_dev *alloc_i7core_dev(u8 socket,
					   स्थिर काष्ठा pci_id_table *table)
अणु
	काष्ठा i7core_dev *i7core_dev;

	i7core_dev = kzalloc(माप(*i7core_dev), GFP_KERNEL);
	अगर (!i7core_dev)
		वापस शून्य;

	i7core_dev->pdev = kसुस्मृति(table->n_devs, माप(*i7core_dev->pdev),
				   GFP_KERNEL);
	अगर (!i7core_dev->pdev) अणु
		kमुक्त(i7core_dev);
		वापस शून्य;
	पूर्ण

	i7core_dev->socket = socket;
	i7core_dev->n_devs = table->n_devs;
	list_add_tail(&i7core_dev->list, &i7core_edac_list);

	वापस i7core_dev;
पूर्ण

अटल व्योम मुक्त_i7core_dev(काष्ठा i7core_dev *i7core_dev)
अणु
	list_del(&i7core_dev->list);
	kमुक्त(i7core_dev->pdev);
	kमुक्त(i7core_dev);
पूर्ण

/****************************************************************************
			Memory check routines
 ****************************************************************************/

अटल पूर्णांक get_dimm_config(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	पूर्णांक i, j;
	क्रमागत edac_type mode;
	क्रमागत mem_type mtype;
	काष्ठा dimm_info *dimm;

	/* Get data from the MC रेजिस्टर, function 0 */
	pdev = pvt->pci_mcr[0];
	अगर (!pdev)
		वापस -ENODEV;

	/* Device 3 function 0 पढ़ोs */
	pci_पढ़ो_config_dword(pdev, MC_CONTROL, &pvt->info.mc_control);
	pci_पढ़ो_config_dword(pdev, MC_STATUS, &pvt->info.mc_status);
	pci_पढ़ो_config_dword(pdev, MC_MAX_DOD, &pvt->info.max_करोd);
	pci_पढ़ो_config_dword(pdev, MC_CHANNEL_MAPPER, &pvt->info.ch_map);

	edac_dbg(0, "QPI %d control=0x%08x status=0x%08x dod=0x%08x map=0x%08x\n",
		 pvt->i7core_dev->socket, pvt->info.mc_control,
		 pvt->info.mc_status, pvt->info.max_करोd, pvt->info.ch_map);

	अगर (ECC_ENABLED(pvt)) अणु
		edac_dbg(0, "ECC enabled with x%d SDCC\n", ECCx8(pvt) ? 8 : 4);
		अगर (ECCx8(pvt))
			mode = EDAC_S8ECD8ED;
		अन्यथा
			mode = EDAC_S4ECD4ED;
	पूर्ण अन्यथा अणु
		edac_dbg(0, "ECC disabled\n");
		mode = EDAC_NONE;
	पूर्ण

	/* FIXME: need to handle the error codes */
	edac_dbg(0, "DOD Max limits: DIMMS: %d, %d-ranked, %d-banked x%x x 0x%x\n",
		 numdimms(pvt->info.max_करोd),
		 numrank(pvt->info.max_करोd >> 2),
		 numbank(pvt->info.max_करोd >> 4),
		 numrow(pvt->info.max_करोd >> 6),
		 numcol(pvt->info.max_करोd >> 9));

	क्रम (i = 0; i < NUM_CHANS; i++) अणु
		u32 data, dimm_करोd[3], value[8];

		अगर (!pvt->pci_ch[i][0])
			जारी;

		अगर (!CH_ACTIVE(pvt, i)) अणु
			edac_dbg(0, "Channel %i is not active\n", i);
			जारी;
		पूर्ण
		अगर (CH_DISABLED(pvt, i)) अणु
			edac_dbg(0, "Channel %i is disabled\n", i);
			जारी;
		पूर्ण

		/* Devices 4-6 function 0 */
		pci_पढ़ो_config_dword(pvt->pci_ch[i][0],
				MC_CHANNEL_DIMM_INIT_PARAMS, &data);


		अगर (data & THREE_DIMMS_PRESENT)
			pvt->channel[i].is_3dimms_present = true;

		अगर (data & SINGLE_QUAD_RANK_PRESENT)
			pvt->channel[i].is_single_4rank = true;

		अगर (data & QUAD_RANK_PRESENT)
			pvt->channel[i].has_4rank = true;

		अगर (data & REGISTERED_DIMM)
			mtype = MEM_RDDR3;
		अन्यथा
			mtype = MEM_DDR3;

		/* Devices 4-6 function 1 */
		pci_पढ़ो_config_dword(pvt->pci_ch[i][1],
				MC_DOD_CH_DIMM0, &dimm_करोd[0]);
		pci_पढ़ो_config_dword(pvt->pci_ch[i][1],
				MC_DOD_CH_DIMM1, &dimm_करोd[1]);
		pci_पढ़ो_config_dword(pvt->pci_ch[i][1],
				MC_DOD_CH_DIMM2, &dimm_करोd[2]);

		edac_dbg(0, "Ch%d phy rd%d, wr%d (0x%08x): %s%s%s%cDIMMs\n",
			 i,
			 RDLCH(pvt->info.ch_map, i), WRLCH(pvt->info.ch_map, i),
			 data,
			 pvt->channel[i].is_3dimms_present ? "3DIMMS " : "",
			 pvt->channel[i].is_3dimms_present ? "SINGLE_4R " : "",
			 pvt->channel[i].has_4rank ? "HAS_4R " : "",
			 (data & REGISTERED_DIMM) ? 'R' : 'U');

		क्रम (j = 0; j < 3; j++) अणु
			u32 banks, ranks, rows, cols;
			u32 size, npages;

			अगर (!DIMM_PRESENT(dimm_करोd[j]))
				जारी;

			dimm = edac_get_dimm(mci, i, j, 0);
			banks = numbank(MC_DOD_NUMBANK(dimm_करोd[j]));
			ranks = numrank(MC_DOD_NUMRANK(dimm_करोd[j]));
			rows = numrow(MC_DOD_NUMROW(dimm_करोd[j]));
			cols = numcol(MC_DOD_NUMCOL(dimm_करोd[j]));

			/* DDR3 has 8 I/O banks */
			size = (rows * cols * banks * ranks) >> (20 - 3);

			edac_dbg(0, "\tdimm %d %d MiB offset: %x, bank: %d, rank: %d, row: %#x, col: %#x\n",
				 j, size,
				 RANKOFFSET(dimm_करोd[j]),
				 banks, ranks, rows, cols);

			npages = MiB_TO_PAGES(size);

			dimm->nr_pages = npages;

			चयन (banks) अणु
			हाल 4:
				dimm->dtype = DEV_X4;
				अवरोध;
			हाल 8:
				dimm->dtype = DEV_X8;
				अवरोध;
			हाल 16:
				dimm->dtype = DEV_X16;
				अवरोध;
			शेष:
				dimm->dtype = DEV_UNKNOWN;
			पूर्ण

			snम_लिखो(dimm->label, माप(dimm->label),
				 "CPU#%uChannel#%u_DIMM#%u",
				 pvt->i7core_dev->socket, i, j);
			dimm->grain = 8;
			dimm->edac_mode = mode;
			dimm->mtype = mtype;
		पूर्ण

		pci_पढ़ो_config_dword(pdev, MC_SAG_CH_0, &value[0]);
		pci_पढ़ो_config_dword(pdev, MC_SAG_CH_1, &value[1]);
		pci_पढ़ो_config_dword(pdev, MC_SAG_CH_2, &value[2]);
		pci_पढ़ो_config_dword(pdev, MC_SAG_CH_3, &value[3]);
		pci_पढ़ो_config_dword(pdev, MC_SAG_CH_4, &value[4]);
		pci_पढ़ो_config_dword(pdev, MC_SAG_CH_5, &value[5]);
		pci_पढ़ो_config_dword(pdev, MC_SAG_CH_6, &value[6]);
		pci_पढ़ो_config_dword(pdev, MC_SAG_CH_7, &value[7]);
		edac_dbg(1, "\t[%i] DIVBY3\tREMOVED\tOFFSET\n", i);
		क्रम (j = 0; j < 8; j++)
			edac_dbg(1, "\t\t%#x\t%#x\t%#x\n",
				 (value[j] >> 27) & 0x1,
				 (value[j] >> 24) & 0x7,
				 (value[j] & ((1 << 24) - 1)));
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************
			Error insertion routines
 ****************************************************************************/

#घोषणा to_mci(k) container_of(k, काष्ठा mem_ctl_info, dev)

/* The i7core has independent error injection features per channel.
   However, to have a simpler code, we करोn't allow enabling error injection
   on more than one channel.
   Also, since a change at an inject parameter will be applied only at enable,
   we're disabling error injection on all ग_लिखो calls to the sysfs nodes that
   controls the error code injection.
 */
अटल पूर्णांक disable_inject(स्थिर काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;

	pvt->inject.enable = 0;

	अगर (!pvt->pci_ch[pvt->inject.channel][0])
		वापस -ENODEV;

	pci_ग_लिखो_config_dword(pvt->pci_ch[pvt->inject.channel][0],
				MC_CHANNEL_ERROR_INJECT, 0);

	वापस 0;
पूर्ण

/*
 * i7core inject inject.section
 *
 *	accept and store error injection inject.section value
 *	bit 0 - refers to the lower 32-byte half cacheline
 *	bit 1 - refers to the upper 32-byte half cacheline
 */
अटल sमाप_प्रकार i7core_inject_section_store(काष्ठा device *dev,
					   काष्ठा device_attribute *mattr,
					   स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	अचिन्हित दीर्घ value;
	पूर्णांक rc;

	अगर (pvt->inject.enable)
		disable_inject(mci);

	rc = kम_से_अदीर्घ(data, 10, &value);
	अगर ((rc < 0) || (value > 3))
		वापस -EIO;

	pvt->inject.section = (u32) value;
	वापस count;
पूर्ण

अटल sमाप_प्रकार i7core_inject_section_show(काष्ठा device *dev,
					  काष्ठा device_attribute *mattr,
					  अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	वापस प्र_लिखो(data, "0x%08x\n", pvt->inject.section);
पूर्ण

/*
 * i7core inject.type
 *
 *	accept and store error injection inject.section value
 *	bit 0 - repeat enable - Enable error repetition
 *	bit 1 - inject ECC error
 *	bit 2 - inject parity error
 */
अटल sमाप_प्रकार i7core_inject_type_store(काष्ठा device *dev,
					काष्ठा device_attribute *mattr,
					स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	अचिन्हित दीर्घ value;
	पूर्णांक rc;

	अगर (pvt->inject.enable)
		disable_inject(mci);

	rc = kम_से_अदीर्घ(data, 10, &value);
	अगर ((rc < 0) || (value > 7))
		वापस -EIO;

	pvt->inject.type = (u32) value;
	वापस count;
पूर्ण

अटल sमाप_प्रकार i7core_inject_type_show(काष्ठा device *dev,
				       काष्ठा device_attribute *mattr,
				       अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा i7core_pvt *pvt = mci->pvt_info;

	वापस प्र_लिखो(data, "0x%08x\n", pvt->inject.type);
पूर्ण

/*
 * i7core_inject_inject.eccmask_store
 *
 * The type of error (UE/CE) will depend on the inject.eccmask value:
 *   Any bits set to a 1 will flip the corresponding ECC bit
 *   Correctable errors can be injected by flipping 1 bit or the bits within
 *   a symbol pair (2 consecutive aligned 8-bit pairs - i.e. 7:0 and 15:8 or
 *   23:16 and 31:24). Flipping bits in two symbol pairs will cause an
 *   uncorrectable error to be injected.
 */
अटल sमाप_प्रकार i7core_inject_eccmask_store(काष्ठा device *dev,
					   काष्ठा device_attribute *mattr,
					   स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	अचिन्हित दीर्घ value;
	पूर्णांक rc;

	अगर (pvt->inject.enable)
		disable_inject(mci);

	rc = kम_से_अदीर्घ(data, 10, &value);
	अगर (rc < 0)
		वापस -EIO;

	pvt->inject.eccmask = (u32) value;
	वापस count;
पूर्ण

अटल sमाप_प्रकार i7core_inject_eccmask_show(काष्ठा device *dev,
					  काष्ठा device_attribute *mattr,
					  अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा i7core_pvt *pvt = mci->pvt_info;

	वापस प्र_लिखो(data, "0x%08x\n", pvt->inject.eccmask);
पूर्ण

/*
 * i7core_addrmatch
 *
 * The type of error (UE/CE) will depend on the inject.eccmask value:
 *   Any bits set to a 1 will flip the corresponding ECC bit
 *   Correctable errors can be injected by flipping 1 bit or the bits within
 *   a symbol pair (2 consecutive aligned 8-bit pairs - i.e. 7:0 and 15:8 or
 *   23:16 and 31:24). Flipping bits in two symbol pairs will cause an
 *   uncorrectable error to be injected.
 */

#घोषणा DECLARE_ADDR_MATCH(param, limit)			\
अटल sमाप_प्रकार i7core_inject_store_##param(			\
	काष्ठा device *dev,					\
	काष्ठा device_attribute *mattr,				\
	स्थिर अक्षर *data, माप_प्रकार count)				\
अणु								\
	काष्ठा mem_ctl_info *mci = dev_get_drvdata(dev);	\
	काष्ठा i7core_pvt *pvt;					\
	दीर्घ value;						\
	पूर्णांक rc;							\
								\
	edac_dbg(1, "\n");					\
	pvt = mci->pvt_info;					\
								\
	अगर (pvt->inject.enable)					\
		disable_inject(mci);				\
								\
	अगर (!strहालcmp(data, "any") || !strहालcmp(data, "any\n"))\
		value = -1;					\
	अन्यथा अणु							\
		rc = kम_से_अदीर्घ(data, 10, &value);		\
		अगर ((rc < 0) || (value >= limit))		\
			वापस -EIO;				\
	पूर्ण							\
								\
	pvt->inject.param = value;				\
								\
	वापस count;						\
पूर्ण								\
								\
अटल sमाप_प्रकार i7core_inject_show_##param(			\
	काष्ठा device *dev,					\
	काष्ठा device_attribute *mattr,				\
	अक्षर *data)						\
अणु								\
	काष्ठा mem_ctl_info *mci = dev_get_drvdata(dev);	\
	काष्ठा i7core_pvt *pvt;					\
								\
	pvt = mci->pvt_info;					\
	edac_dbg(1, "pvt=%p\n", pvt);				\
	अगर (pvt->inject.param < 0)				\
		वापस प्र_लिखो(data, "any\n");			\
	अन्यथा							\
		वापस प्र_लिखो(data, "%d\n", pvt->inject.param);\
पूर्ण

#घोषणा ATTR_ADDR_MATCH(param)					\
	अटल DEVICE_ATTR(param, S_IRUGO | S_IWUSR,		\
		    i7core_inject_show_##param,			\
		    i7core_inject_store_##param)

DECLARE_ADDR_MATCH(channel, 3);
DECLARE_ADDR_MATCH(dimm, 3);
DECLARE_ADDR_MATCH(rank, 4);
DECLARE_ADDR_MATCH(bank, 32);
DECLARE_ADDR_MATCH(page, 0x10000);
DECLARE_ADDR_MATCH(col, 0x4000);

ATTR_ADDR_MATCH(channel);
ATTR_ADDR_MATCH(dimm);
ATTR_ADDR_MATCH(rank);
ATTR_ADDR_MATCH(bank);
ATTR_ADDR_MATCH(page);
ATTR_ADDR_MATCH(col);

अटल पूर्णांक ग_लिखो_and_test(काष्ठा pci_dev *dev, स्थिर पूर्णांक where, स्थिर u32 val)
अणु
	u32 पढ़ो;
	पूर्णांक count;

	edac_dbg(0, "setting pci %02x:%02x.%x reg=%02x value=%08x\n",
		 dev->bus->number, PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn),
		 where, val);

	क्रम (count = 0; count < 10; count++) अणु
		अगर (count)
			msleep(100);
		pci_ग_लिखो_config_dword(dev, where, val);
		pci_पढ़ो_config_dword(dev, where, &पढ़ो);

		अगर (पढ़ो == val)
			वापस 0;
	पूर्ण

	i7core_prपूर्णांकk(KERN_ERR, "Error during set pci %02x:%02x.%x reg=%02x "
		"write=%08x. Read=%08x\n",
		dev->bus->number, PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn),
		where, val, पढ़ो);

	वापस -EINVAL;
पूर्ण

/*
 * This routine prepares the Memory Controller क्रम error injection.
 * The error will be injected when some process tries to ग_लिखो to the
 * memory that matches the given criteria.
 * The criteria can be set in terms of a mask where dimm, rank, bank, page
 * and col can be specअगरied.
 * A -1 value क्रम any of the mask items will make the MCU to ignore
 * that matching criteria क्रम error injection.
 *
 * It should be noticed that the error will only happen after a ग_लिखो operation
 * on a memory that matches the condition. अगर REPEAT_EN is not enabled at
 * inject mask, then it will produce just one error. Otherwise, it will repeat
 * until the injecपंचांगask would be cleaned.
 *
 * FIXME: This routine assumes that MAXNUMDIMMS value of MC_MAX_DOD
 *    is reliable enough to check अगर the MC is using the
 *    three channels. However, this is not clear at the datasheet.
 */
अटल sमाप_प्रकार i7core_inject_enable_store(काष्ठा device *dev,
					  काष्ठा device_attribute *mattr,
					  स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	u32 injecपंचांगask;
	u64 mask = 0;
	पूर्णांक  rc;
	दीर्घ enable;

	अगर (!pvt->pci_ch[pvt->inject.channel][0])
		वापस 0;

	rc = kम_से_अदीर्घ(data, 10, &enable);
	अगर ((rc < 0))
		वापस 0;

	अगर (enable) अणु
		pvt->inject.enable = 1;
	पूर्ण अन्यथा अणु
		disable_inject(mci);
		वापस count;
	पूर्ण

	/* Sets pvt->inject.dimm mask */
	अगर (pvt->inject.dimm < 0)
		mask |= 1LL << 41;
	अन्यथा अणु
		अगर (pvt->channel[pvt->inject.channel].dimms > 2)
			mask |= (pvt->inject.dimm & 0x3LL) << 35;
		अन्यथा
			mask |= (pvt->inject.dimm & 0x1LL) << 36;
	पूर्ण

	/* Sets pvt->inject.rank mask */
	अगर (pvt->inject.rank < 0)
		mask |= 1LL << 40;
	अन्यथा अणु
		अगर (pvt->channel[pvt->inject.channel].dimms > 2)
			mask |= (pvt->inject.rank & 0x1LL) << 34;
		अन्यथा
			mask |= (pvt->inject.rank & 0x3LL) << 34;
	पूर्ण

	/* Sets pvt->inject.bank mask */
	अगर (pvt->inject.bank < 0)
		mask |= 1LL << 39;
	अन्यथा
		mask |= (pvt->inject.bank & 0x15LL) << 30;

	/* Sets pvt->inject.page mask */
	अगर (pvt->inject.page < 0)
		mask |= 1LL << 38;
	अन्यथा
		mask |= (pvt->inject.page & 0xffff) << 14;

	/* Sets pvt->inject.column mask */
	अगर (pvt->inject.col < 0)
		mask |= 1LL << 37;
	अन्यथा
		mask |= (pvt->inject.col & 0x3fff);

	/*
	 * bit    0: REPEAT_EN
	 * bits 1-2: MASK_HALF_CACHELINE
	 * bit    3: INJECT_ECC
	 * bit    4: INJECT_ADDR_PARITY
	 */

	injecपंचांगask = (pvt->inject.type & 1) |
		     (pvt->inject.section & 0x3) << 1 |
		     (pvt->inject.type & 0x6) << (3 - 1);

	/* Unlock ग_लिखोs to रेजिस्टरs - this रेजिस्टर is ग_लिखो only */
	pci_ग_लिखो_config_dword(pvt->pci_noncore,
			       MC_CFG_CONTROL, 0x2);

	ग_लिखो_and_test(pvt->pci_ch[pvt->inject.channel][0],
			       MC_CHANNEL_ADDR_MATCH, mask);
	ग_लिखो_and_test(pvt->pci_ch[pvt->inject.channel][0],
			       MC_CHANNEL_ADDR_MATCH + 4, mask >> 32L);

	ग_लिखो_and_test(pvt->pci_ch[pvt->inject.channel][0],
			       MC_CHANNEL_ERROR_MASK, pvt->inject.eccmask);

	ग_लिखो_and_test(pvt->pci_ch[pvt->inject.channel][0],
			       MC_CHANNEL_ERROR_INJECT, injecपंचांगask);

	/*
	 * This is something unकरोcumented, based on my tests
	 * Without writing 8 to this रेजिस्टर, errors aren't injected. Not sure
	 * why.
	 */
	pci_ग_लिखो_config_dword(pvt->pci_noncore,
			       MC_CFG_CONTROL, 8);

	edac_dbg(0, "Error inject addr match 0x%016llx, ecc 0x%08x, inject 0x%08x\n",
		 mask, pvt->inject.eccmask, injecपंचांगask);


	वापस count;
पूर्ण

अटल sमाप_प्रकार i7core_inject_enable_show(काष्ठा device *dev,
					 काष्ठा device_attribute *mattr,
					 अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	u32 injecपंचांगask;

	अगर (!pvt->pci_ch[pvt->inject.channel][0])
		वापस 0;

	pci_पढ़ो_config_dword(pvt->pci_ch[pvt->inject.channel][0],
			       MC_CHANNEL_ERROR_INJECT, &injecपंचांगask);

	edac_dbg(0, "Inject error read: 0x%018x\n", injecपंचांगask);

	अगर (injecपंचांगask & 0x0c)
		pvt->inject.enable = 1;

	वापस प्र_लिखो(data, "%d\n", pvt->inject.enable);
पूर्ण

#घोषणा DECLARE_COUNTER(param)					\
अटल sमाप_प्रकार i7core_show_counter_##param(			\
	काष्ठा device *dev,					\
	काष्ठा device_attribute *mattr,				\
	अक्षर *data)						\
अणु								\
	काष्ठा mem_ctl_info *mci = dev_get_drvdata(dev);	\
	काष्ठा i7core_pvt *pvt = mci->pvt_info;			\
								\
	edac_dbg(1, "\n");					\
	अगर (!pvt->ce_count_available || (pvt->is_रेजिस्टरed))	\
		वापस प्र_लिखो(data, "data unavailable\n");	\
	वापस प्र_लिखो(data, "%lu\n",				\
			pvt->udimm_ce_count[param]);		\
पूर्ण

#घोषणा ATTR_COUNTER(param)					\
	अटल DEVICE_ATTR(udimm##param, S_IRUGO | S_IWUSR,	\
		    i7core_show_counter_##param,		\
		    शून्य)

DECLARE_COUNTER(0);
DECLARE_COUNTER(1);
DECLARE_COUNTER(2);

ATTR_COUNTER(0);
ATTR_COUNTER(1);
ATTR_COUNTER(2);

/*
 * inject_addrmatch device sysfs काष्ठा
 */

अटल काष्ठा attribute *i7core_addrmatch_attrs[] = अणु
	&dev_attr_channel.attr,
	&dev_attr_dimm.attr,
	&dev_attr_rank.attr,
	&dev_attr_bank.attr,
	&dev_attr_page.attr,
	&dev_attr_col.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group addrmatch_grp = अणु
	.attrs	= i7core_addrmatch_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *addrmatch_groups[] = अणु
	&addrmatch_grp,
	शून्य
पूर्ण;

अटल व्योम addrmatch_release(काष्ठा device *device)
अणु
	edac_dbg(1, "Releasing device %s\n", dev_name(device));
	kमुक्त(device);
पूर्ण

अटल स्थिर काष्ठा device_type addrmatch_type = अणु
	.groups		= addrmatch_groups,
	.release	= addrmatch_release,
पूर्ण;

/*
 * all_channel_counts sysfs काष्ठा
 */

अटल काष्ठा attribute *i7core_udimm_counters_attrs[] = अणु
	&dev_attr_udimm0.attr,
	&dev_attr_udimm1.attr,
	&dev_attr_udimm2.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group all_channel_counts_grp = अणु
	.attrs	= i7core_udimm_counters_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *all_channel_counts_groups[] = अणु
	&all_channel_counts_grp,
	शून्य
पूर्ण;

अटल व्योम all_channel_counts_release(काष्ठा device *device)
अणु
	edac_dbg(1, "Releasing device %s\n", dev_name(device));
	kमुक्त(device);
पूर्ण

अटल स्थिर काष्ठा device_type all_channel_counts_type = अणु
	.groups		= all_channel_counts_groups,
	.release	= all_channel_counts_release,
पूर्ण;

/*
 * inject sysfs attributes
 */

अटल DEVICE_ATTR(inject_section, S_IRUGO | S_IWUSR,
		   i7core_inject_section_show, i7core_inject_section_store);

अटल DEVICE_ATTR(inject_type, S_IRUGO | S_IWUSR,
		   i7core_inject_type_show, i7core_inject_type_store);


अटल DEVICE_ATTR(inject_eccmask, S_IRUGO | S_IWUSR,
		   i7core_inject_eccmask_show, i7core_inject_eccmask_store);

अटल DEVICE_ATTR(inject_enable, S_IRUGO | S_IWUSR,
		   i7core_inject_enable_show, i7core_inject_enable_store);

अटल काष्ठा attribute *i7core_dev_attrs[] = अणु
	&dev_attr_inject_section.attr,
	&dev_attr_inject_type.attr,
	&dev_attr_inject_eccmask.attr,
	&dev_attr_inject_enable.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(i7core_dev);

अटल पूर्णांक i7core_create_sysfs_devices(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	पूर्णांक rc;

	pvt->addrmatch_dev = kzalloc(माप(*pvt->addrmatch_dev), GFP_KERNEL);
	अगर (!pvt->addrmatch_dev)
		वापस -ENOMEM;

	pvt->addrmatch_dev->type = &addrmatch_type;
	pvt->addrmatch_dev->bus = mci->dev.bus;
	device_initialize(pvt->addrmatch_dev);
	pvt->addrmatch_dev->parent = &mci->dev;
	dev_set_name(pvt->addrmatch_dev, "inject_addrmatch");
	dev_set_drvdata(pvt->addrmatch_dev, mci);

	edac_dbg(1, "creating %s\n", dev_name(pvt->addrmatch_dev));

	rc = device_add(pvt->addrmatch_dev);
	अगर (rc < 0)
		जाओ err_put_addrmatch;

	अगर (!pvt->is_रेजिस्टरed) अणु
		pvt->chancounts_dev = kzalloc(माप(*pvt->chancounts_dev),
					      GFP_KERNEL);
		अगर (!pvt->chancounts_dev) अणु
			rc = -ENOMEM;
			जाओ err_del_addrmatch;
		पूर्ण

		pvt->chancounts_dev->type = &all_channel_counts_type;
		pvt->chancounts_dev->bus = mci->dev.bus;
		device_initialize(pvt->chancounts_dev);
		pvt->chancounts_dev->parent = &mci->dev;
		dev_set_name(pvt->chancounts_dev, "all_channel_counts");
		dev_set_drvdata(pvt->chancounts_dev, mci);

		edac_dbg(1, "creating %s\n", dev_name(pvt->chancounts_dev));

		rc = device_add(pvt->chancounts_dev);
		अगर (rc < 0)
			जाओ err_put_chancounts;
	पूर्ण
	वापस 0;

err_put_chancounts:
	put_device(pvt->chancounts_dev);
err_del_addrmatch:
	device_del(pvt->addrmatch_dev);
err_put_addrmatch:
	put_device(pvt->addrmatch_dev);

	वापस rc;
पूर्ण

अटल व्योम i7core_delete_sysfs_devices(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;

	edac_dbg(1, "\n");

	अगर (!pvt->is_रेजिस्टरed) अणु
		device_del(pvt->chancounts_dev);
		put_device(pvt->chancounts_dev);
	पूर्ण
	device_del(pvt->addrmatch_dev);
	put_device(pvt->addrmatch_dev);
पूर्ण

/****************************************************************************
	Device initialization routines: put/get, init/निकास
 ****************************************************************************/

/*
 *	i7core_put_all_devices	'put' all the devices that we have
 *				reserved via 'get'
 */
अटल व्योम i7core_put_devices(काष्ठा i7core_dev *i7core_dev)
अणु
	पूर्णांक i;

	edac_dbg(0, "\n");
	क्रम (i = 0; i < i7core_dev->n_devs; i++) अणु
		काष्ठा pci_dev *pdev = i7core_dev->pdev[i];
		अगर (!pdev)
			जारी;
		edac_dbg(0, "Removing dev %02x:%02x.%d\n",
			 pdev->bus->number,
			 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));
		pci_dev_put(pdev);
	पूर्ण
पूर्ण

अटल व्योम i7core_put_all_devices(व्योम)
अणु
	काष्ठा i7core_dev *i7core_dev, *पंचांगp;

	list_क्रम_each_entry_safe(i7core_dev, पंचांगp, &i7core_edac_list, list) अणु
		i7core_put_devices(i7core_dev);
		मुक्त_i7core_dev(i7core_dev);
	पूर्ण
पूर्ण

अटल व्योम __init i7core_xeon_pci_fixup(स्थिर काष्ठा pci_id_table *table)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	पूर्णांक i;

	/*
	 * On Xeon 55xx, the Intel Quick Path Arch Generic Non-core pci buses
	 * aren't announced by acpi. So, we need to use a legacy scan probing
	 * to detect them
	 */
	जबतक (table && table->descr) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL, table->descr[0].dev_id, शून्य);
		अगर (unlikely(!pdev)) अणु
			क्रम (i = 0; i < MAX_SOCKET_BUSES; i++)
				pcibios_scan_specअगरic_bus(255-i);
		पूर्ण
		pci_dev_put(pdev);
		table++;
	पूर्ण
पूर्ण

अटल अचिन्हित i7core_pci_lastbus(व्योम)
अणु
	पूर्णांक last_bus = 0, bus;
	काष्ठा pci_bus *b = शून्य;

	जबतक ((b = pci_find_next_bus(b)) != शून्य) अणु
		bus = b->number;
		edac_dbg(0, "Found bus %d\n", bus);
		अगर (bus > last_bus)
			last_bus = bus;
	पूर्ण

	edac_dbg(0, "Last bus %d\n", last_bus);

	वापस last_bus;
पूर्ण

/*
 *	i7core_get_all_devices	Find and perक्रमm 'get' operation on the MCH's
 *			device/functions we want to reference क्रम this driver
 *
 *			Need to 'get' device 16 func 1 and func 2
 */
अटल पूर्णांक i7core_get_onedevice(काष्ठा pci_dev **prev,
				स्थिर काष्ठा pci_id_table *table,
				स्थिर अचिन्हित devno,
				स्थिर अचिन्हित last_bus)
अणु
	काष्ठा i7core_dev *i7core_dev;
	स्थिर काष्ठा pci_id_descr *dev_descr = &table->descr[devno];

	काष्ठा pci_dev *pdev = शून्य;
	u8 bus = 0;
	u8 socket = 0;

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
			      dev_descr->dev_id, *prev);

	/*
	 * On Xeon 55xx, the Intel QuickPath Arch Generic Non-core regs
	 * is at addr 8086:2c40, instead of 8086:2c41. So, we need
	 * to probe क्रम the alternate address in हाल of failure
	 */
	अगर (dev_descr->dev_id == PCI_DEVICE_ID_INTEL_I7_NONCORE && !pdev) अणु
		pci_dev_get(*prev);	/* pci_get_device will put it */
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				      PCI_DEVICE_ID_INTEL_I7_NONCORE_ALT, *prev);
	पूर्ण

	अगर (dev_descr->dev_id == PCI_DEVICE_ID_INTEL_LYNNFIELD_NONCORE &&
	    !pdev) अणु
		pci_dev_get(*prev);	/* pci_get_device will put it */
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				      PCI_DEVICE_ID_INTEL_LYNNFIELD_NONCORE_ALT,
				      *prev);
	पूर्ण

	अगर (!pdev) अणु
		अगर (*prev) अणु
			*prev = pdev;
			वापस 0;
		पूर्ण

		अगर (dev_descr->optional)
			वापस 0;

		अगर (devno == 0)
			वापस -ENODEV;

		i7core_prपूर्णांकk(KERN_INFO,
			"Device not found: dev %02x.%d PCI ID %04x:%04x\n",
			dev_descr->dev, dev_descr->func,
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

		/* End of list, leave */
		वापस -ENODEV;
	पूर्ण
	bus = pdev->bus->number;

	socket = last_bus - bus;

	i7core_dev = get_i7core_dev(socket);
	अगर (!i7core_dev) अणु
		i7core_dev = alloc_i7core_dev(socket, table);
		अगर (!i7core_dev) अणु
			pci_dev_put(pdev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (i7core_dev->pdev[devno]) अणु
		i7core_prपूर्णांकk(KERN_ERR,
			"Duplicated device for "
			"dev %02x:%02x.%d PCI ID %04x:%04x\n",
			bus, dev_descr->dev, dev_descr->func,
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
		pci_dev_put(pdev);
		वापस -ENODEV;
	पूर्ण

	i7core_dev->pdev[devno] = pdev;

	/* Sanity check */
	अगर (unlikely(PCI_SLOT(pdev->devfn) != dev_descr->dev ||
			PCI_FUNC(pdev->devfn) != dev_descr->func)) अणु
		i7core_prपूर्णांकk(KERN_ERR,
			"Device PCI ID %04x:%04x "
			"has dev %02x:%02x.%d instead of dev %02x:%02x.%d\n",
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id,
			bus, PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
			bus, dev_descr->dev, dev_descr->func);
		वापस -ENODEV;
	पूर्ण

	/* Be sure that the device is enabled */
	अगर (unlikely(pci_enable_device(pdev) < 0)) अणु
		i7core_prपूर्णांकk(KERN_ERR,
			"Couldn't enable "
			"dev %02x:%02x.%d PCI ID %04x:%04x\n",
			bus, dev_descr->dev, dev_descr->func,
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
		वापस -ENODEV;
	पूर्ण

	edac_dbg(0, "Detected socket %d dev %02x:%02x.%d PCI ID %04x:%04x\n",
		 socket, bus, dev_descr->dev,
		 dev_descr->func,
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

अटल पूर्णांक i7core_get_all_devices(व्योम)
अणु
	पूर्णांक i, rc, last_bus;
	काष्ठा pci_dev *pdev = शून्य;
	स्थिर काष्ठा pci_id_table *table = pci_dev_table;

	last_bus = i7core_pci_lastbus();

	जबतक (table && table->descr) अणु
		क्रम (i = 0; i < table->n_devs; i++) अणु
			pdev = शून्य;
			करो अणु
				rc = i7core_get_onedevice(&pdev, table, i,
							  last_bus);
				अगर (rc < 0) अणु
					अगर (i == 0) अणु
						i = table->n_devs;
						अवरोध;
					पूर्ण
					i7core_put_all_devices();
					वापस -ENODEV;
				पूर्ण
			पूर्ण जबतक (pdev);
		पूर्ण
		table++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mci_bind_devs(काष्ठा mem_ctl_info *mci,
			 काष्ठा i7core_dev *i7core_dev)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	पूर्णांक i, func, slot;
	अक्षर *family;

	pvt->is_रेजिस्टरed = false;
	pvt->enable_scrub  = false;
	क्रम (i = 0; i < i7core_dev->n_devs; i++) अणु
		pdev = i7core_dev->pdev[i];
		अगर (!pdev)
			जारी;

		func = PCI_FUNC(pdev->devfn);
		slot = PCI_SLOT(pdev->devfn);
		अगर (slot == 3) अणु
			अगर (unlikely(func > MAX_MCR_FUNC))
				जाओ error;
			pvt->pci_mcr[func] = pdev;
		पूर्ण अन्यथा अगर (likely(slot >= 4 && slot < 4 + NUM_CHANS)) अणु
			अगर (unlikely(func > MAX_CHAN_FUNC))
				जाओ error;
			pvt->pci_ch[slot - 4][func] = pdev;
		पूर्ण अन्यथा अगर (!slot && !func) अणु
			pvt->pci_noncore = pdev;

			/* Detect the processor family */
			चयन (pdev->device) अणु
			हाल PCI_DEVICE_ID_INTEL_I7_NONCORE:
				family = "Xeon 35xx/ i7core";
				pvt->enable_scrub = false;
				अवरोध;
			हाल PCI_DEVICE_ID_INTEL_LYNNFIELD_NONCORE_ALT:
				family = "i7-800/i5-700";
				pvt->enable_scrub = false;
				अवरोध;
			हाल PCI_DEVICE_ID_INTEL_LYNNFIELD_NONCORE:
				family = "Xeon 34xx";
				pvt->enable_scrub = false;
				अवरोध;
			हाल PCI_DEVICE_ID_INTEL_I7_NONCORE_ALT:
				family = "Xeon 55xx";
				pvt->enable_scrub = true;
				अवरोध;
			हाल PCI_DEVICE_ID_INTEL_LYNNFIELD_NONCORE_REV2:
				family = "Xeon 56xx / i7-900";
				pvt->enable_scrub = true;
				अवरोध;
			शेष:
				family = "unknown";
				pvt->enable_scrub = false;
			पूर्ण
			edac_dbg(0, "Detected a processor type %s\n", family);
		पूर्ण अन्यथा
			जाओ error;

		edac_dbg(0, "Associated fn %d.%d, dev = %p, socket %d\n",
			 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
			 pdev, i7core_dev->socket);

		अगर (PCI_SLOT(pdev->devfn) == 3 &&
			PCI_FUNC(pdev->devfn) == 2)
			pvt->is_रेजिस्टरed = true;
	पूर्ण

	वापस 0;

error:
	i7core_prपूर्णांकk(KERN_ERR, "Device %d, function %d "
		      "is out of the expected range\n",
		      slot, func);
	वापस -EINVAL;
पूर्ण

/****************************************************************************
			Error check routines
 ****************************************************************************/

अटल व्योम i7core_rdimm_update_ce_count(काष्ठा mem_ctl_info *mci,
					 स्थिर पूर्णांक chan,
					 स्थिर पूर्णांक new0,
					 स्थिर पूर्णांक new1,
					 स्थिर पूर्णांक new2)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	पूर्णांक add0 = 0, add1 = 0, add2 = 0;
	/* Updates CE counters अगर it is not the first समय here */
	अगर (pvt->ce_count_available) अणु
		/* Updates CE counters */

		add2 = new2 - pvt->rdimm_last_ce_count[chan][2];
		add1 = new1 - pvt->rdimm_last_ce_count[chan][1];
		add0 = new0 - pvt->rdimm_last_ce_count[chan][0];

		अगर (add2 < 0)
			add2 += 0x7fff;
		pvt->rdimm_ce_count[chan][2] += add2;

		अगर (add1 < 0)
			add1 += 0x7fff;
		pvt->rdimm_ce_count[chan][1] += add1;

		अगर (add0 < 0)
			add0 += 0x7fff;
		pvt->rdimm_ce_count[chan][0] += add0;
	पूर्ण अन्यथा
		pvt->ce_count_available = 1;

	/* Store the new values */
	pvt->rdimm_last_ce_count[chan][2] = new2;
	pvt->rdimm_last_ce_count[chan][1] = new1;
	pvt->rdimm_last_ce_count[chan][0] = new0;

	/*updated the edac core */
	अगर (add0 != 0)
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, add0,
				     0, 0, 0,
				     chan, 0, -1, "error", "");
	अगर (add1 != 0)
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, add1,
				     0, 0, 0,
				     chan, 1, -1, "error", "");
	अगर (add2 != 0)
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, add2,
				     0, 0, 0,
				     chan, 2, -1, "error", "");
पूर्ण

अटल व्योम i7core_rdimm_check_mc_ecc_err(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	u32 rcv[3][2];
	पूर्णांक i, new0, new1, new2;

	/*Read DEV 3: FUN 2:  MC_COR_ECC_CNT regs directly*/
	pci_पढ़ो_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_0,
								&rcv[0][0]);
	pci_पढ़ो_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_1,
								&rcv[0][1]);
	pci_पढ़ो_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_2,
								&rcv[1][0]);
	pci_पढ़ो_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_3,
								&rcv[1][1]);
	pci_पढ़ो_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_4,
								&rcv[2][0]);
	pci_पढ़ो_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_5,
								&rcv[2][1]);
	क्रम (i = 0 ; i < 3; i++) अणु
		edac_dbg(3, "MC_COR_ECC_CNT%d = 0x%x; MC_COR_ECC_CNT%d = 0x%x\n",
			 (i * 2), rcv[i][0], (i * 2) + 1, rcv[i][1]);
		/*अगर the channel has 3 dimms*/
		अगर (pvt->channel[i].dimms > 2) अणु
			new0 = DIMM_BOT_COR_ERR(rcv[i][0]);
			new1 = DIMM_TOP_COR_ERR(rcv[i][0]);
			new2 = DIMM_BOT_COR_ERR(rcv[i][1]);
		पूर्ण अन्यथा अणु
			new0 = DIMM_TOP_COR_ERR(rcv[i][0]) +
					DIMM_BOT_COR_ERR(rcv[i][0]);
			new1 = DIMM_TOP_COR_ERR(rcv[i][1]) +
					DIMM_BOT_COR_ERR(rcv[i][1]);
			new2 = 0;
		पूर्ण

		i7core_rdimm_update_ce_count(mci, i, new0, new1, new2);
	पूर्ण
पूर्ण

/* This function is based on the device 3 function 4 रेजिस्टरs as described on:
 * Intel Xeon Processor 5500 Series Datasheet Volume 2
 *	http://www.पूर्णांकel.com/Assets/PDF/datasheet/321322.pdf
 * also available at:
 * 	http://www.arrownac.com/manufacturers/पूर्णांकel/s/nehalem/5500-datasheet-v2.pdf
 */
अटल व्योम i7core_udimm_check_mc_ecc_err(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	u32 rcv1, rcv0;
	पूर्णांक new0, new1, new2;

	अगर (!pvt->pci_mcr[4]) अणु
		edac_dbg(0, "MCR registers not found\n");
		वापस;
	पूर्ण

	/* Corrected test errors */
	pci_पढ़ो_config_dword(pvt->pci_mcr[4], MC_TEST_ERR_RCV1, &rcv1);
	pci_पढ़ो_config_dword(pvt->pci_mcr[4], MC_TEST_ERR_RCV0, &rcv0);

	/* Store the new values */
	new2 = DIMM2_COR_ERR(rcv1);
	new1 = DIMM1_COR_ERR(rcv0);
	new0 = DIMM0_COR_ERR(rcv0);

	/* Updates CE counters अगर it is not the first समय here */
	अगर (pvt->ce_count_available) अणु
		/* Updates CE counters */
		पूर्णांक add0, add1, add2;

		add2 = new2 - pvt->udimm_last_ce_count[2];
		add1 = new1 - pvt->udimm_last_ce_count[1];
		add0 = new0 - pvt->udimm_last_ce_count[0];

		अगर (add2 < 0)
			add2 += 0x7fff;
		pvt->udimm_ce_count[2] += add2;

		अगर (add1 < 0)
			add1 += 0x7fff;
		pvt->udimm_ce_count[1] += add1;

		अगर (add0 < 0)
			add0 += 0x7fff;
		pvt->udimm_ce_count[0] += add0;

		अगर (add0 | add1 | add2)
			i7core_prपूर्णांकk(KERN_ERR, "New Corrected error(s): "
				      "dimm0: +%d, dimm1: +%d, dimm2 +%d\n",
				      add0, add1, add2);
	पूर्ण अन्यथा
		pvt->ce_count_available = 1;

	/* Store the new values */
	pvt->udimm_last_ce_count[2] = new2;
	pvt->udimm_last_ce_count[1] = new1;
	pvt->udimm_last_ce_count[0] = new0;
पूर्ण

/*
 * According with tables E-11 and E-12 of chapter E.3.3 of Intel 64 and IA-32
 * Architectures Software Developerै s Manual Volume 3B.
 * Nehalem are defined as family 0x06, model 0x1a
 *
 * The MCA रेजिस्टरs used here are the following ones:
 *     काष्ठा mce field	MCA Register
 *     m->status	MSR_IA32_MC8_STATUS
 *     m->addr		MSR_IA32_MC8_ADDR
 *     m->misc		MSR_IA32_MC8_MISC
 * In the हाल of Nehalem, the error inक्रमmation is masked at .status and .misc
 * fields
 */
अटल व्योम i7core_mce_output_error(काष्ठा mem_ctl_info *mci,
				    स्थिर काष्ठा mce *m)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	अक्षर *optype, *err;
	क्रमागत hw_event_mc_err_type tp_event;
	अचिन्हित दीर्घ error = m->status & 0x1ff0000l;
	bool uncorrected_error = m->mcgstatus & 1ll << 61;
	bool ripv = m->mcgstatus & 1;
	u32 optypक्रमागत = (m->status >> 4) & 0x07;
	u32 core_err_cnt = (m->status >> 38) & 0x7fff;
	u32 dimm = (m->misc >> 16) & 0x3;
	u32 channel = (m->misc >> 18) & 0x3;
	u32 syndrome = m->misc >> 32;
	u32 errnum = find_first_bit(&error, 32);

	अगर (uncorrected_error) अणु
		core_err_cnt = 1;
		अगर (ripv)
			tp_event = HW_EVENT_ERR_UNCORRECTED;
		अन्यथा
			tp_event = HW_EVENT_ERR_FATAL;
	पूर्ण अन्यथा अणु
		tp_event = HW_EVENT_ERR_CORRECTED;
	पूर्ण

	चयन (optypक्रमागत) अणु
	हाल 0:
		optype = "generic undef request";
		अवरोध;
	हाल 1:
		optype = "read error";
		अवरोध;
	हाल 2:
		optype = "write error";
		अवरोध;
	हाल 3:
		optype = "addr/cmd error";
		अवरोध;
	हाल 4:
		optype = "scrubbing error";
		अवरोध;
	शेष:
		optype = "reserved";
		अवरोध;
	पूर्ण

	चयन (errnum) अणु
	हाल 16:
		err = "read ECC error";
		अवरोध;
	हाल 17:
		err = "RAS ECC error";
		अवरोध;
	हाल 18:
		err = "write parity error";
		अवरोध;
	हाल 19:
		err = "redundancy loss";
		अवरोध;
	हाल 20:
		err = "reserved";
		अवरोध;
	हाल 21:
		err = "memory range error";
		अवरोध;
	हाल 22:
		err = "RTID out of range";
		अवरोध;
	हाल 23:
		err = "address parity error";
		अवरोध;
	हाल 24:
		err = "byte enable parity error";
		अवरोध;
	शेष:
		err = "unknown";
	पूर्ण

	/*
	 * Call the helper to output message
	 * FIXME: what to करो अगर core_err_cnt > 1? Currently, it generates
	 * only one event
	 */
	अगर (uncorrected_error || !pvt->is_रेजिस्टरed)
		edac_mc_handle_error(tp_event, mci, core_err_cnt,
				     m->addr >> PAGE_SHIFT,
				     m->addr & ~PAGE_MASK,
				     syndrome,
				     channel, dimm, -1,
				     err, optype);
पूर्ण

/*
 *	i7core_check_error	Retrieve and process errors reported by the
 *				hardware. Called by the Core module.
 */
अटल व्योम i7core_check_error(काष्ठा mem_ctl_info *mci, काष्ठा mce *m)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;

	i7core_mce_output_error(mci, m);

	/*
	 * Now, let's increment CE error counts
	 */
	अगर (!pvt->is_रेजिस्टरed)
		i7core_udimm_check_mc_ecc_err(mci);
	अन्यथा
		i7core_rdimm_check_mc_ecc_err(mci);
पूर्ण

/*
 * Check that logging is enabled and that this is the right type
 * of error क्रम us to handle.
 */
अटल पूर्णांक i7core_mce_check_error(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				  व्योम *data)
अणु
	काष्ठा mce *mce = (काष्ठा mce *)data;
	काष्ठा i7core_dev *i7_dev;
	काष्ठा mem_ctl_info *mci;

	i7_dev = get_i7core_dev(mce->socketid);
	अगर (!i7_dev || (mce->kflags & MCE_HANDLED_CEC))
		वापस NOTIFY_DONE;

	mci = i7_dev->mci;

	/*
	 * Just let mcelog handle it अगर the error is
	 * outside the memory controller
	 */
	अगर (((mce->status & 0xffff) >> 7) != 1)
		वापस NOTIFY_DONE;

	/* Bank 8 रेजिस्टरs are the only ones that we know how to handle */
	अगर (mce->bank != 8)
		वापस NOTIFY_DONE;

	i7core_check_error(mci, mce);

	/* Advise mcelog that the errors were handled */
	mce->kflags |= MCE_HANDLED_EDAC;
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block i7_mce_dec = अणु
	.notअगरier_call	= i7core_mce_check_error,
	.priority	= MCE_PRIO_EDAC,
पूर्ण;

काष्ठा memdev_dmi_entry अणु
	u8 type;
	u8 length;
	u16 handle;
	u16 phys_mem_array_handle;
	u16 mem_err_info_handle;
	u16 total_width;
	u16 data_width;
	u16 size;
	u8 क्रमm;
	u8 device_set;
	u8 device_locator;
	u8 bank_locator;
	u8 memory_type;
	u16 type_detail;
	u16 speed;
	u8 manufacturer;
	u8 serial_number;
	u8 asset_tag;
	u8 part_number;
	u8 attributes;
	u32 extended_size;
	u16 conf_mem_clk_speed;
पूर्ण __attribute__((__packed__));


/*
 * Decode the DRAM Clock Frequency, be paranoid, make sure that all
 * memory devices show the same speed, and अगर they करोn't then consider
 * all speeds to be invalid.
 */
अटल व्योम decode_dclk(स्थिर काष्ठा dmi_header *dh, व्योम *_dclk_freq)
अणु
	पूर्णांक *dclk_freq = _dclk_freq;
	u16 dmi_mem_clk_speed;

	अगर (*dclk_freq == -1)
		वापस;

	अगर (dh->type == DMI_ENTRY_MEM_DEVICE) अणु
		काष्ठा memdev_dmi_entry *memdev_dmi_entry =
			(काष्ठा memdev_dmi_entry *)dh;
		अचिन्हित दीर्घ conf_mem_clk_speed_offset =
			(अचिन्हित दीर्घ)&memdev_dmi_entry->conf_mem_clk_speed -
			(अचिन्हित दीर्घ)&memdev_dmi_entry->type;
		अचिन्हित दीर्घ speed_offset =
			(अचिन्हित दीर्घ)&memdev_dmi_entry->speed -
			(अचिन्हित दीर्घ)&memdev_dmi_entry->type;

		/* Check that a DIMM is present */
		अगर (memdev_dmi_entry->size == 0)
			वापस;

		/*
		 * Pick the configured speed अगर it's available, otherwise
		 * pick the DIMM speed, or we करोn't have a speed.
		 */
		अगर (memdev_dmi_entry->length > conf_mem_clk_speed_offset) अणु
			dmi_mem_clk_speed =
				memdev_dmi_entry->conf_mem_clk_speed;
		पूर्ण अन्यथा अगर (memdev_dmi_entry->length > speed_offset) अणु
			dmi_mem_clk_speed = memdev_dmi_entry->speed;
		पूर्ण अन्यथा अणु
			*dclk_freq = -1;
			वापस;
		पूर्ण

		अगर (*dclk_freq == 0) अणु
			/* First pass, speed was 0 */
			अगर (dmi_mem_clk_speed > 0) अणु
				/* Set speed अगर a valid speed is पढ़ो */
				*dclk_freq = dmi_mem_clk_speed;
			पूर्ण अन्यथा अणु
				/* Otherwise we करोn't have a valid speed */
				*dclk_freq = -1;
			पूर्ण
		पूर्ण अन्यथा अगर (*dclk_freq > 0 &&
			   *dclk_freq != dmi_mem_clk_speed) अणु
			/*
			 * If we have a speed, check that all DIMMS are the same
			 * speed, otherwise set the speed as invalid.
			 */
			*dclk_freq = -1;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The शेष DCLK frequency is used as a fallback अगर we
 * fail to find anything reliable in the DMI. The value
 * is taken straight from the datasheet.
 */
#घोषणा DEFAULT_DCLK_FREQ 800

अटल पूर्णांक get_dclk_freq(व्योम)
अणु
	पूर्णांक dclk_freq = 0;

	dmi_walk(decode_dclk, (व्योम *)&dclk_freq);

	अगर (dclk_freq < 1)
		वापस DEFAULT_DCLK_FREQ;

	वापस dclk_freq;
पूर्ण

/*
 * set_sdram_scrub_rate		This routine sets byte/sec bandwidth scrub rate
 *				to hardware according to SCRUBINTERVAL क्रमmula
 *				found in datasheet.
 */
अटल पूर्णांक set_sdram_scrub_rate(काष्ठा mem_ctl_info *mci, u32 new_bw)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	u32 dw_scrub;
	u32 dw_ssr;

	/* Get data from the MC रेजिस्टर, function 2 */
	pdev = pvt->pci_mcr[2];
	अगर (!pdev)
		वापस -ENODEV;

	pci_पढ़ो_config_dword(pdev, MC_SCRUB_CONTROL, &dw_scrub);

	अगर (new_bw == 0) अणु
		/* Prepare to disable petrol scrub */
		dw_scrub &= ~STARTSCRUB;
		/* Stop the patrol scrub engine */
		ग_लिखो_and_test(pdev, MC_SCRUB_CONTROL,
			       dw_scrub & ~SCRUBINTERVAL_MASK);

		/* Get current status of scrub rate and set bit to disable */
		pci_पढ़ो_config_dword(pdev, MC_SSRCONTROL, &dw_ssr);
		dw_ssr &= ~SSR_MODE_MASK;
		dw_ssr |= SSR_MODE_DISABLE;
	पूर्ण अन्यथा अणु
		स्थिर पूर्णांक cache_line_size = 64;
		स्थिर u32 freq_dclk_mhz = pvt->dclk_freq;
		अचिन्हित दीर्घ दीर्घ scrub_पूर्णांकerval;
		/*
		 * Translate the desired scrub rate to a रेजिस्टर value and
		 * program the corresponding रेजिस्टर value.
		 */
		scrub_पूर्णांकerval = (अचिन्हित दीर्घ दीर्घ)freq_dclk_mhz *
			cache_line_size * 1000000;
		करो_भाग(scrub_पूर्णांकerval, new_bw);

		अगर (!scrub_पूर्णांकerval || scrub_पूर्णांकerval > SCRUBINTERVAL_MASK)
			वापस -EINVAL;

		dw_scrub = SCRUBINTERVAL_MASK & scrub_पूर्णांकerval;

		/* Start the patrol scrub engine */
		pci_ग_लिखो_config_dword(pdev, MC_SCRUB_CONTROL,
				       STARTSCRUB | dw_scrub);

		/* Get current status of scrub rate and set bit to enable */
		pci_पढ़ो_config_dword(pdev, MC_SSRCONTROL, &dw_ssr);
		dw_ssr &= ~SSR_MODE_MASK;
		dw_ssr |= SSR_MODE_ENABLE;
	पूर्ण
	/* Disable or enable scrubbing */
	pci_ग_लिखो_config_dword(pdev, MC_SSRCONTROL, dw_ssr);

	वापस new_bw;
पूर्ण

/*
 * get_sdram_scrub_rate		This routine convert current scrub rate value
 *				पूर्णांकo byte/sec bandwidth according to
 *				SCRUBINTERVAL क्रमmula found in datasheet.
 */
अटल पूर्णांक get_sdram_scrub_rate(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	काष्ठा pci_dev *pdev;
	स्थिर u32 cache_line_size = 64;
	स्थिर u32 freq_dclk_mhz = pvt->dclk_freq;
	अचिन्हित दीर्घ दीर्घ scrub_rate;
	u32 scrubval;

	/* Get data from the MC रेजिस्टर, function 2 */
	pdev = pvt->pci_mcr[2];
	अगर (!pdev)
		वापस -ENODEV;

	/* Get current scrub control data */
	pci_पढ़ो_config_dword(pdev, MC_SCRUB_CONTROL, &scrubval);

	/* Mask highest 8-bits to 0 */
	scrubval &=  SCRUBINTERVAL_MASK;
	अगर (!scrubval)
		वापस 0;

	/* Calculate scrub rate value पूर्णांकo byte/sec bandwidth */
	scrub_rate =  (अचिन्हित दीर्घ दीर्घ)freq_dclk_mhz *
		1000000 * cache_line_size;
	करो_भाग(scrub_rate, scrubval);
	वापस (पूर्णांक)scrub_rate;
पूर्ण

अटल व्योम enable_sdram_scrub_setting(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	u32 pci_lock;

	/* Unlock ग_लिखोs to pci रेजिस्टरs */
	pci_पढ़ो_config_dword(pvt->pci_noncore, MC_CFG_CONTROL, &pci_lock);
	pci_lock &= ~0x3;
	pci_ग_लिखो_config_dword(pvt->pci_noncore, MC_CFG_CONTROL,
			       pci_lock | MC_CFG_UNLOCK);

	mci->set_sdram_scrub_rate = set_sdram_scrub_rate;
	mci->get_sdram_scrub_rate = get_sdram_scrub_rate;
पूर्ण

अटल व्योम disable_sdram_scrub_setting(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7core_pvt *pvt = mci->pvt_info;
	u32 pci_lock;

	/* Lock ग_लिखोs to pci रेजिस्टरs */
	pci_पढ़ो_config_dword(pvt->pci_noncore, MC_CFG_CONTROL, &pci_lock);
	pci_lock &= ~0x3;
	pci_ग_लिखो_config_dword(pvt->pci_noncore, MC_CFG_CONTROL,
			       pci_lock | MC_CFG_LOCK);
पूर्ण

अटल व्योम i7core_pci_ctl_create(काष्ठा i7core_pvt *pvt)
अणु
	pvt->i7core_pci = edac_pci_create_generic_ctl(
						&pvt->i7core_dev->pdev[0]->dev,
						EDAC_MOD_STR);
	अगर (unlikely(!pvt->i7core_pci))
		i7core_prपूर्णांकk(KERN_WARNING,
			      "Unable to setup PCI error report via EDAC\n");
पूर्ण

अटल व्योम i7core_pci_ctl_release(काष्ठा i7core_pvt *pvt)
अणु
	अगर (likely(pvt->i7core_pci))
		edac_pci_release_generic_ctl(pvt->i7core_pci);
	अन्यथा
		i7core_prपूर्णांकk(KERN_ERR,
				"Couldn't find mem_ctl_info for socket %d\n",
				pvt->i7core_dev->socket);
	pvt->i7core_pci = शून्य;
पूर्ण

अटल व्योम i7core_unरेजिस्टर_mci(काष्ठा i7core_dev *i7core_dev)
अणु
	काष्ठा mem_ctl_info *mci = i7core_dev->mci;
	काष्ठा i7core_pvt *pvt;

	अगर (unlikely(!mci || !mci->pvt_info)) अणु
		edac_dbg(0, "MC: dev = %p\n", &i7core_dev->pdev[0]->dev);

		i7core_prपूर्णांकk(KERN_ERR, "Couldn't find mci handler\n");
		वापस;
	पूर्ण

	pvt = mci->pvt_info;

	edac_dbg(0, "MC: mci = %p, dev = %p\n", mci, &i7core_dev->pdev[0]->dev);

	/* Disable scrubrate setting */
	अगर (pvt->enable_scrub)
		disable_sdram_scrub_setting(mci);

	/* Disable EDAC polling */
	i7core_pci_ctl_release(pvt);

	/* Remove MC sysfs nodes */
	i7core_delete_sysfs_devices(mci);
	edac_mc_del_mc(mci->pdev);

	edac_dbg(1, "%s: free mci struct\n", mci->ctl_name);
	kमुक्त(mci->ctl_name);
	edac_mc_मुक्त(mci);
	i7core_dev->mci = शून्य;
पूर्ण

अटल पूर्णांक i7core_रेजिस्टर_mci(काष्ठा i7core_dev *i7core_dev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा i7core_pvt *pvt;
	पूर्णांक rc;
	काष्ठा edac_mc_layer layers[2];

	/* allocate a new MC control काष्ठाure */

	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = NUM_CHANS;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = MAX_DIMMS;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(i7core_dev->socket, ARRAY_SIZE(layers), layers,
			    माप(*pvt));
	अगर (unlikely(!mci))
		वापस -ENOMEM;

	edac_dbg(0, "MC: mci = %p, dev = %p\n", mci, &i7core_dev->pdev[0]->dev);

	pvt = mci->pvt_info;
	स_रखो(pvt, 0, माप(*pvt));

	/* Associates i7core_dev and mci क्रम future usage */
	pvt->i7core_dev = i7core_dev;
	i7core_dev->mci = mci;

	/*
	 * FIXME: how to handle RDDR3 at MCI level? It is possible to have
	 * Mixed RDDR3/UDDR3 with Nehalem, provided that they are on dअगरferent
	 * memory channels
	 */
	mci->mtype_cap = MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = "i7core_edac.c";

	mci->ctl_name = kaप्र_लिखो(GFP_KERNEL, "i7 core #%d", i7core_dev->socket);
	अगर (!mci->ctl_name) अणु
		rc = -ENOMEM;
		जाओ fail1;
	पूर्ण

	mci->dev_name = pci_name(i7core_dev->pdev[0]);
	mci->ctl_page_to_phys = शून्य;

	/* Store pci devices at mci क्रम faster access */
	rc = mci_bind_devs(mci, i7core_dev);
	अगर (unlikely(rc < 0))
		जाओ fail0;


	/* Get dimm basic config */
	get_dimm_config(mci);
	/* record ptr to the generic device */
	mci->pdev = &i7core_dev->pdev[0]->dev;

	/* Enable scrubrate setting */
	अगर (pvt->enable_scrub)
		enable_sdram_scrub_setting(mci);

	/* add this new MC control काष्ठाure to EDAC's list of MCs */
	अगर (unlikely(edac_mc_add_mc_with_groups(mci, i7core_dev_groups))) अणु
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		/* FIXME: perhaps some code should go here that disables error
		 * reporting अगर we just enabled it
		 */

		rc = -EINVAL;
		जाओ fail0;
	पूर्ण
	अगर (i7core_create_sysfs_devices(mci)) अणु
		edac_dbg(0, "MC: failed to create sysfs nodes\n");
		edac_mc_del_mc(mci->pdev);
		rc = -EINVAL;
		जाओ fail0;
	पूर्ण

	/* Default error mask is any memory */
	pvt->inject.channel = 0;
	pvt->inject.dimm = -1;
	pvt->inject.rank = -1;
	pvt->inject.bank = -1;
	pvt->inject.page = -1;
	pvt->inject.col = -1;

	/* allocating generic PCI control info */
	i7core_pci_ctl_create(pvt);

	/* DCLK क्रम scrub rate setting */
	pvt->dclk_freq = get_dclk_freq();

	वापस 0;

fail0:
	kमुक्त(mci->ctl_name);

fail1:
	edac_mc_मुक्त(mci);
	i7core_dev->mci = शून्य;
	वापस rc;
पूर्ण

/*
 *	i7core_probe	Probe क्रम ONE instance of device to see अगर it is
 *			present.
 *	वापस:
 *		0 क्रम FOUND a device
 *		< 0 क्रम error code
 */

अटल पूर्णांक i7core_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rc, count = 0;
	काष्ठा i7core_dev *i7core_dev;

	/* get the pci devices we want to reserve क्रम our use */
	mutex_lock(&i7core_edac_lock);

	/*
	 * All memory controllers are allocated at the first pass.
	 */
	अगर (unlikely(probed >= 1)) अणु
		mutex_unlock(&i7core_edac_lock);
		वापस -ENODEV;
	पूर्ण
	probed++;

	rc = i7core_get_all_devices();
	अगर (unlikely(rc < 0))
		जाओ fail0;

	list_क्रम_each_entry(i7core_dev, &i7core_edac_list, list) अणु
		count++;
		rc = i7core_रेजिस्टर_mci(i7core_dev);
		अगर (unlikely(rc < 0))
			जाओ fail1;
	पूर्ण

	/*
	 * Nehalem-EX uses a dअगरferent memory controller. However, as the
	 * memory controller is not visible on some Nehalem/Nehalem-EP, we
	 * need to indirectly probe via a X58 PCI device. The same devices
	 * are found on (some) Nehalem-EX. So, on those machines, the
	 * probe routine needs to वापस -ENODEV, as the actual Memory
	 * Controller रेजिस्टरs won't be detected.
	 */
	अगर (!count) अणु
		rc = -ENODEV;
		जाओ fail1;
	पूर्ण

	i7core_prपूर्णांकk(KERN_INFO,
		      "Driver loaded, %d memory controller(s) found.\n",
		      count);

	mutex_unlock(&i7core_edac_lock);
	वापस 0;

fail1:
	list_क्रम_each_entry(i7core_dev, &i7core_edac_list, list)
		i7core_unरेजिस्टर_mci(i7core_dev);

	i7core_put_all_devices();
fail0:
	mutex_unlock(&i7core_edac_lock);
	वापस rc;
पूर्ण

/*
 *	i7core_हटाओ	deकाष्ठाor क्रम one instance of device
 *
 */
अटल व्योम i7core_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा i7core_dev *i7core_dev;

	edac_dbg(0, "\n");

	/*
	 * we have a trouble here: pdev value क्रम removal will be wrong, since
	 * it will poपूर्णांक to the X58 रेजिस्टर used to detect that the machine
	 * is a Nehalem or upper design. However, due to the way several PCI
	 * devices are grouped together to provide MC functionality, we need
	 * to use a dअगरferent method क्रम releasing the devices
	 */

	mutex_lock(&i7core_edac_lock);

	अगर (unlikely(!probed)) अणु
		mutex_unlock(&i7core_edac_lock);
		वापस;
	पूर्ण

	list_क्रम_each_entry(i7core_dev, &i7core_edac_list, list)
		i7core_unरेजिस्टर_mci(i7core_dev);

	/* Release PCI resources */
	i7core_put_all_devices();

	probed--;

	mutex_unlock(&i7core_edac_lock);
पूर्ण

MODULE_DEVICE_TABLE(pci, i7core_pci_tbl);

/*
 *	i7core_driver	pci_driver काष्ठाure क्रम this module
 *
 */
अटल काष्ठा pci_driver i7core_driver = अणु
	.name     = "i7core_edac",
	.probe    = i7core_probe,
	.हटाओ   = i7core_हटाओ,
	.id_table = i7core_pci_tbl,
पूर्ण;

/*
 *	i7core_init		Module entry function
 *			Try to initialize this module क्रम its devices
 */
अटल पूर्णांक __init i7core_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(2, "\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	अगर (use_pci_fixup)
		i7core_xeon_pci_fixup(pci_dev_table);

	pci_rc = pci_रेजिस्टर_driver(&i7core_driver);

	अगर (pci_rc >= 0) अणु
		mce_रेजिस्टर_decode_chain(&i7_mce_dec);
		वापस 0;
	पूर्ण

	i7core_prपूर्णांकk(KERN_ERR, "Failed to register device with error %d.\n",
		      pci_rc);

	वापस pci_rc;
पूर्ण

/*
 *	i7core_निकास()	Module निकास function
 *			Unरेजिस्टर the driver
 */
अटल व्योम __निकास i7core_निकास(व्योम)
अणु
	edac_dbg(2, "\n");
	pci_unरेजिस्टर_driver(&i7core_driver);
	mce_unरेजिस्टर_decode_chain(&i7_mce_dec);
पूर्ण

module_init(i7core_init);
module_निकास(i7core_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_AUTHOR("Red Hat Inc. (https://www.redhat.com)");
MODULE_DESCRIPTION("MC Driver for Intel i7 Core memory controllers - "
		   I7CORE_REVISION);

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
