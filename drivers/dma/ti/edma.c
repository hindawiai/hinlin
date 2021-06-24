<शैली गुरु>
/*
 * TI EDMA DMA engine driver
 *
 * Copyright 2012 Texas Instruments
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/platक्रमm_data/edma.h>

#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

/* Offsets matching "struct edmacc_param" */
#घोषणा PARM_OPT		0x00
#घोषणा PARM_SRC		0x04
#घोषणा PARM_A_B_CNT		0x08
#घोषणा PARM_DST		0x0c
#घोषणा PARM_SRC_DST_BIDX	0x10
#घोषणा PARM_LINK_BCNTRLD	0x14
#घोषणा PARM_SRC_DST_CIDX	0x18
#घोषणा PARM_CCNT		0x1c

#घोषणा PARM_SIZE		0x20

/* Offsets क्रम EDMA CC global channel रेजिस्टरs and their shaकरोws */
#घोषणा SH_ER			0x00	/* 64 bits */
#घोषणा SH_ECR			0x08	/* 64 bits */
#घोषणा SH_ESR			0x10	/* 64 bits */
#घोषणा SH_CER			0x18	/* 64 bits */
#घोषणा SH_EER			0x20	/* 64 bits */
#घोषणा SH_EECR			0x28	/* 64 bits */
#घोषणा SH_EESR			0x30	/* 64 bits */
#घोषणा SH_SER			0x38	/* 64 bits */
#घोषणा SH_SECR			0x40	/* 64 bits */
#घोषणा SH_IER			0x50	/* 64 bits */
#घोषणा SH_IECR			0x58	/* 64 bits */
#घोषणा SH_IESR			0x60	/* 64 bits */
#घोषणा SH_IPR			0x68	/* 64 bits */
#घोषणा SH_ICR			0x70	/* 64 bits */
#घोषणा SH_IEVAL		0x78
#घोषणा SH_QER			0x80
#घोषणा SH_QEER			0x84
#घोषणा SH_QEECR		0x88
#घोषणा SH_QEESR		0x8c
#घोषणा SH_QSER			0x90
#घोषणा SH_QSECR		0x94
#घोषणा SH_SIZE			0x200

/* Offsets क्रम EDMA CC global रेजिस्टरs */
#घोषणा EDMA_REV		0x0000
#घोषणा EDMA_CCCFG		0x0004
#घोषणा EDMA_QCHMAP		0x0200	/* 8 रेजिस्टरs */
#घोषणा EDMA_DMAQNUM		0x0240	/* 8 रेजिस्टरs (4 on OMAP-L1xx) */
#घोषणा EDMA_QDMAQNUM		0x0260
#घोषणा EDMA_QUETCMAP		0x0280
#घोषणा EDMA_QUEPRI		0x0284
#घोषणा EDMA_EMR		0x0300	/* 64 bits */
#घोषणा EDMA_EMCR		0x0308	/* 64 bits */
#घोषणा EDMA_QEMR		0x0310
#घोषणा EDMA_QEMCR		0x0314
#घोषणा EDMA_CCERR		0x0318
#घोषणा EDMA_CCERRCLR		0x031c
#घोषणा EDMA_EEVAL		0x0320
#घोषणा EDMA_DRAE		0x0340	/* 4 x 64 bits*/
#घोषणा EDMA_QRAE		0x0380	/* 4 रेजिस्टरs */
#घोषणा EDMA_QUEEVTENTRY	0x0400	/* 2 x 16 रेजिस्टरs */
#घोषणा EDMA_QSTAT		0x0600	/* 2 रेजिस्टरs */
#घोषणा EDMA_QWMTHRA		0x0620
#घोषणा EDMA_QWMTHRB		0x0624
#घोषणा EDMA_CCSTAT		0x0640

#घोषणा EDMA_M			0x1000	/* global channel रेजिस्टरs */
#घोषणा EDMA_ECR		0x1008
#घोषणा EDMA_ECRH		0x100C
#घोषणा EDMA_SHADOW0		0x2000	/* 4 shaकरोw regions */
#घोषणा EDMA_PARM		0x4000	/* PaRAM entries */

#घोषणा PARM_OFFSET(param_no)	(EDMA_PARM + ((param_no) << 5))

#घोषणा EDMA_DCHMAP		0x0100  /* 64 रेजिस्टरs */

/* CCCFG रेजिस्टर */
#घोषणा GET_NUM_DMACH(x)	(x & 0x7) /* bits 0-2 */
#घोषणा GET_NUM_QDMACH(x)	((x & 0x70) >> 4) /* bits 4-6 */
#घोषणा GET_NUM_PAENTRY(x)	((x & 0x7000) >> 12) /* bits 12-14 */
#घोषणा GET_NUM_EVQUE(x)	((x & 0x70000) >> 16) /* bits 16-18 */
#घोषणा GET_NUM_REGN(x)		((x & 0x300000) >> 20) /* bits 20-21 */
#घोषणा CHMAP_EXIST		BIT(24)

/* CCSTAT रेजिस्टर */
#घोषणा EDMA_CCSTAT_ACTV	BIT(4)

/*
 * Max of 20 segments per channel to conserve PaRAM slots
 * Also note that MAX_NR_SG should be atleast the no.of periods
 * that are required क्रम ASoC, otherwise DMA prep calls will
 * fail. Today davinci-pcm is the only user of this driver and
 * requires atleast 17 slots, so we setup the शेष to 20.
 */
#घोषणा MAX_NR_SG		20
#घोषणा EDMA_MAX_SLOTS		MAX_NR_SG
#घोषणा EDMA_DESCRIPTORS	16

#घोषणा EDMA_CHANNEL_ANY		-1	/* क्रम edma_alloc_channel() */
#घोषणा EDMA_SLOT_ANY			-1	/* क्रम edma_alloc_slot() */
#घोषणा EDMA_CONT_PARAMS_ANY		 1001
#घोषणा EDMA_CONT_PARAMS_FIXED_EXACT	 1002
#घोषणा EDMA_CONT_PARAMS_FIXED_NOT_EXACT 1003

/*
 * 64bit array रेजिस्टरs are split पूर्णांकo two 32bit रेजिस्टरs:
 * reg0: channel/event 0-31
 * reg1: channel/event 32-63
 *
 * bit 5 in the channel number tells the array index (0/1)
 * bit 0-4 (0x1f) is the bit offset within the रेजिस्टर
 */
#घोषणा EDMA_REG_ARRAY_INDEX(channel)	((channel) >> 5)
#घोषणा EDMA_CHANNEL_BIT(channel)	(BIT((channel) & 0x1f))

/* PaRAM slots are laid out like this */
काष्ठा edmacc_param अणु
	u32 opt;
	u32 src;
	u32 a_b_cnt;
	u32 dst;
	u32 src_dst_bidx;
	u32 link_bcntrld;
	u32 src_dst_cidx;
	u32 ccnt;
पूर्ण __packed;

/* fields in edmacc_param.opt */
#घोषणा SAM		BIT(0)
#घोषणा DAM		BIT(1)
#घोषणा SYNCDIM		BIT(2)
#घोषणा STATIC		BIT(3)
#घोषणा EDMA_FWID	(0x07 << 8)
#घोषणा TCCMODE		BIT(11)
#घोषणा EDMA_TCC(t)	((t) << 12)
#घोषणा TCINTEN		BIT(20)
#घोषणा ITCINTEN	BIT(21)
#घोषणा TCCHEN		BIT(22)
#घोषणा ITCCHEN		BIT(23)

काष्ठा edma_pset अणु
	u32				len;
	dma_addr_t			addr;
	काष्ठा edmacc_param		param;
पूर्ण;

काष्ठा edma_desc अणु
	काष्ठा virt_dma_desc		vdesc;
	काष्ठा list_head		node;
	क्रमागत dma_transfer_direction	direction;
	पूर्णांक				cyclic;
	bool				polled;
	पूर्णांक				असलync;
	पूर्णांक				pset_nr;
	काष्ठा edma_chan		*echan;
	पूर्णांक				processed;

	/*
	 * The following 4 elements are used क्रम residue accounting.
	 *
	 * - processed_stat: the number of SG elements we have traversed
	 * so far to cover accounting. This is updated directly to processed
	 * during edma_callback and is always <= processed, because processed
	 * refers to the number of pending transfer (programmed to EDMA
	 * controller), where as processed_stat tracks number of transfers
	 * accounted क्रम so far.
	 *
	 * - residue: The amount of bytes we have left to transfer क्रम this desc
	 *
	 * - residue_stat: The residue in bytes of data we have covered
	 * so far क्रम accounting. This is updated directly to residue
	 * during callbacks to keep it current.
	 *
	 * - sg_len: Tracks the length of the current पूर्णांकermediate transfer,
	 * this is required to update the residue during पूर्णांकermediate transfer
	 * completion callback.
	 */
	पूर्णांक				processed_stat;
	u32				sg_len;
	u32				residue;
	u32				residue_stat;

	काष्ठा edma_pset		pset[];
पूर्ण;

काष्ठा edma_cc;

काष्ठा edma_tc अणु
	काष्ठा device_node		*node;
	u16				id;
पूर्ण;

काष्ठा edma_chan अणु
	काष्ठा virt_dma_chan		vchan;
	काष्ठा list_head		node;
	काष्ठा edma_desc		*edesc;
	काष्ठा edma_cc			*ecc;
	काष्ठा edma_tc			*tc;
	पूर्णांक				ch_num;
	bool				alloced;
	bool				hw_triggered;
	पूर्णांक				slot[EDMA_MAX_SLOTS];
	पूर्णांक				missed;
	काष्ठा dma_slave_config		cfg;
पूर्ण;

काष्ठा edma_cc अणु
	काष्ठा device			*dev;
	काष्ठा edma_soc_info		*info;
	व्योम __iomem			*base;
	पूर्णांक				id;
	bool				legacy_mode;

	/* eDMA3 resource inक्रमmation */
	अचिन्हित			num_channels;
	अचिन्हित			num_qchannels;
	अचिन्हित			num_region;
	अचिन्हित			num_slots;
	अचिन्हित			num_tc;
	bool				chmap_exist;
	क्रमागत dma_event_q		शेष_queue;

	अचिन्हित पूर्णांक			ccपूर्णांक;
	अचिन्हित पूर्णांक			ccerrपूर्णांक;

	/*
	 * The slot_inuse bit क्रम each PaRAM slot is clear unless the slot is
	 * in use by Linux or अगर it is allocated to be used by DSP.
	 */
	अचिन्हित दीर्घ *slot_inuse;

	/*
	 * For tracking reserved channels used by DSP.
	 * If the bit is cleared, the channel is allocated to be used by DSP
	 * and Linux must not touch it.
	 */
	अचिन्हित दीर्घ *channels_mask;

	काष्ठा dma_device		dma_slave;
	काष्ठा dma_device		*dma_स_नकल;
	काष्ठा edma_chan		*slave_chans;
	काष्ठा edma_tc			*tc_list;
	पूर्णांक				dummy_slot;
पूर्ण;

/* dummy param set used to (re)initialize parameter RAM slots */
अटल स्थिर काष्ठा edmacc_param dummy_paramset = अणु
	.link_bcntrld = 0xffff,
	.ccnt = 1,
पूर्ण;

#घोषणा EDMA_BINDING_LEGACY	0
#घोषणा EDMA_BINDING_TPCC	1
अटल स्थिर u32 edma_binding_type[] = अणु
	[EDMA_BINDING_LEGACY] = EDMA_BINDING_LEGACY,
	[EDMA_BINDING_TPCC] = EDMA_BINDING_TPCC,
पूर्ण;

अटल स्थिर काष्ठा of_device_id edma_of_ids[] = अणु
	अणु
		.compatible = "ti,edma3",
		.data = &edma_binding_type[EDMA_BINDING_LEGACY],
	पूर्ण,
	अणु
		.compatible = "ti,edma3-tpcc",
		.data = &edma_binding_type[EDMA_BINDING_TPCC],
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, edma_of_ids);

अटल स्थिर काष्ठा of_device_id edma_tptc_of_ids[] = अणु
	अणु .compatible = "ti,edma3-tptc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, edma_tptc_of_ids);

अटल अंतरभूत अचिन्हित पूर्णांक edma_पढ़ो(काष्ठा edma_cc *ecc, पूर्णांक offset)
अणु
	वापस (अचिन्हित पूर्णांक)__raw_पढ़ोl(ecc->base + offset);
पूर्ण

अटल अंतरभूत व्योम edma_ग_लिखो(काष्ठा edma_cc *ecc, पूर्णांक offset, पूर्णांक val)
अणु
	__raw_ग_लिखोl(val, ecc->base + offset);
पूर्ण

अटल अंतरभूत व्योम edma_modअगरy(काष्ठा edma_cc *ecc, पूर्णांक offset, अचिन्हित and,
			       अचिन्हित or)
अणु
	अचिन्हित val = edma_पढ़ो(ecc, offset);

	val &= and;
	val |= or;
	edma_ग_लिखो(ecc, offset, val);
पूर्ण

अटल अंतरभूत व्योम edma_and(काष्ठा edma_cc *ecc, पूर्णांक offset, अचिन्हित and)
अणु
	अचिन्हित val = edma_पढ़ो(ecc, offset);

	val &= and;
	edma_ग_लिखो(ecc, offset, val);
पूर्ण

अटल अंतरभूत व्योम edma_or(काष्ठा edma_cc *ecc, पूर्णांक offset, अचिन्हित or)
अणु
	अचिन्हित val = edma_पढ़ो(ecc, offset);

	val |= or;
	edma_ग_लिखो(ecc, offset, val);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक edma_पढ़ो_array(काष्ठा edma_cc *ecc, पूर्णांक offset,
					   पूर्णांक i)
अणु
	वापस edma_पढ़ो(ecc, offset + (i << 2));
पूर्ण

अटल अंतरभूत व्योम edma_ग_लिखो_array(काष्ठा edma_cc *ecc, पूर्णांक offset, पूर्णांक i,
				    अचिन्हित val)
अणु
	edma_ग_लिखो(ecc, offset + (i << 2), val);
पूर्ण

अटल अंतरभूत व्योम edma_modअगरy_array(काष्ठा edma_cc *ecc, पूर्णांक offset, पूर्णांक i,
				     अचिन्हित and, अचिन्हित or)
अणु
	edma_modअगरy(ecc, offset + (i << 2), and, or);
पूर्ण

अटल अंतरभूत व्योम edma_or_array(काष्ठा edma_cc *ecc, पूर्णांक offset, पूर्णांक i,
				 अचिन्हित or)
अणु
	edma_or(ecc, offset + (i << 2), or);
पूर्ण

अटल अंतरभूत व्योम edma_or_array2(काष्ठा edma_cc *ecc, पूर्णांक offset, पूर्णांक i, पूर्णांक j,
				  अचिन्हित or)
अणु
	edma_or(ecc, offset + ((i * 2 + j) << 2), or);
पूर्ण

अटल अंतरभूत व्योम edma_ग_लिखो_array2(काष्ठा edma_cc *ecc, पूर्णांक offset, पूर्णांक i,
				     पूर्णांक j, अचिन्हित val)
अणु
	edma_ग_लिखो(ecc, offset + ((i * 2 + j) << 2), val);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक edma_shaकरोw0_पढ़ो(काष्ठा edma_cc *ecc, पूर्णांक offset)
अणु
	वापस edma_पढ़ो(ecc, EDMA_SHADOW0 + offset);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक edma_shaकरोw0_पढ़ो_array(काष्ठा edma_cc *ecc,
						   पूर्णांक offset, पूर्णांक i)
अणु
	वापस edma_पढ़ो(ecc, EDMA_SHADOW0 + offset + (i << 2));
पूर्ण

अटल अंतरभूत व्योम edma_shaकरोw0_ग_लिखो(काष्ठा edma_cc *ecc, पूर्णांक offset,
				      अचिन्हित val)
अणु
	edma_ग_लिखो(ecc, EDMA_SHADOW0 + offset, val);
पूर्ण

अटल अंतरभूत व्योम edma_shaकरोw0_ग_लिखो_array(काष्ठा edma_cc *ecc, पूर्णांक offset,
					    पूर्णांक i, अचिन्हित val)
अणु
	edma_ग_लिखो(ecc, EDMA_SHADOW0 + offset + (i << 2), val);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक edma_param_पढ़ो(काष्ठा edma_cc *ecc, पूर्णांक offset,
					   पूर्णांक param_no)
अणु
	वापस edma_पढ़ो(ecc, EDMA_PARM + offset + (param_no << 5));
पूर्ण

अटल अंतरभूत व्योम edma_param_ग_लिखो(काष्ठा edma_cc *ecc, पूर्णांक offset,
				    पूर्णांक param_no, अचिन्हित val)
अणु
	edma_ग_लिखो(ecc, EDMA_PARM + offset + (param_no << 5), val);
पूर्ण

अटल अंतरभूत व्योम edma_param_modअगरy(काष्ठा edma_cc *ecc, पूर्णांक offset,
				     पूर्णांक param_no, अचिन्हित and, अचिन्हित or)
अणु
	edma_modअगरy(ecc, EDMA_PARM + offset + (param_no << 5), and, or);
पूर्ण

अटल अंतरभूत व्योम edma_param_and(काष्ठा edma_cc *ecc, पूर्णांक offset, पूर्णांक param_no,
				  अचिन्हित and)
अणु
	edma_and(ecc, EDMA_PARM + offset + (param_no << 5), and);
पूर्ण

अटल अंतरभूत व्योम edma_param_or(काष्ठा edma_cc *ecc, पूर्णांक offset, पूर्णांक param_no,
				 अचिन्हित or)
अणु
	edma_or(ecc, EDMA_PARM + offset + (param_no << 5), or);
पूर्ण

अटल व्योम edma_assign_priority_to_queue(काष्ठा edma_cc *ecc, पूर्णांक queue_no,
					  पूर्णांक priority)
अणु
	पूर्णांक bit = queue_no * 4;

	edma_modअगरy(ecc, EDMA_QUEPRI, ~(0x7 << bit), ((priority & 0x7) << bit));
पूर्ण

अटल व्योम edma_set_chmap(काष्ठा edma_chan *echan, पूर्णांक slot)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);

	अगर (ecc->chmap_exist) अणु
		slot = EDMA_CHAN_SLOT(slot);
		edma_ग_लिखो_array(ecc, EDMA_DCHMAP, channel, (slot << 5));
	पूर्ण
पूर्ण

अटल व्योम edma_setup_पूर्णांकerrupt(काष्ठा edma_chan *echan, bool enable)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);
	पूर्णांक idx = EDMA_REG_ARRAY_INDEX(channel);
	पूर्णांक ch_bit = EDMA_CHANNEL_BIT(channel);

	अगर (enable) अणु
		edma_shaकरोw0_ग_लिखो_array(ecc, SH_ICR, idx, ch_bit);
		edma_shaकरोw0_ग_लिखो_array(ecc, SH_IESR, idx, ch_bit);
	पूर्ण अन्यथा अणु
		edma_shaकरोw0_ग_लिखो_array(ecc, SH_IECR, idx, ch_bit);
	पूर्ण
पूर्ण

/*
 * paRAM slot management functions
 */
अटल व्योम edma_ग_लिखो_slot(काष्ठा edma_cc *ecc, अचिन्हित slot,
			    स्थिर काष्ठा edmacc_param *param)
अणु
	slot = EDMA_CHAN_SLOT(slot);
	अगर (slot >= ecc->num_slots)
		वापस;
	स_नकल_toio(ecc->base + PARM_OFFSET(slot), param, PARM_SIZE);
पूर्ण

अटल पूर्णांक edma_पढ़ो_slot(काष्ठा edma_cc *ecc, अचिन्हित slot,
			   काष्ठा edmacc_param *param)
अणु
	slot = EDMA_CHAN_SLOT(slot);
	अगर (slot >= ecc->num_slots)
		वापस -EINVAL;
	स_नकल_fromio(param, ecc->base + PARM_OFFSET(slot), PARM_SIZE);

	वापस 0;
पूर्ण

/**
 * edma_alloc_slot - allocate DMA parameter RAM
 * @ecc: poपूर्णांकer to edma_cc काष्ठा
 * @slot: specअगरic slot to allocate; negative क्रम "any unused slot"
 *
 * This allocates a parameter RAM slot, initializing it to hold a
 * dummy transfer.  Slots allocated using this routine have not been
 * mapped to a hardware DMA channel, and will normally be used by
 * linking to them from a slot associated with a DMA channel.
 *
 * Normal use is to pass EDMA_SLOT_ANY as the @slot, but specअगरic
 * slots may be allocated on behalf of DSP firmware.
 *
 * Returns the number of the slot, अन्यथा negative त्रुटि_सं.
 */
अटल पूर्णांक edma_alloc_slot(काष्ठा edma_cc *ecc, पूर्णांक slot)
अणु
	अगर (slot >= 0) अणु
		slot = EDMA_CHAN_SLOT(slot);
		/* Requesting entry paRAM slot क्रम a HW triggered channel. */
		अगर (ecc->chmap_exist && slot < ecc->num_channels)
			slot = EDMA_SLOT_ANY;
	पूर्ण

	अगर (slot < 0) अणु
		अगर (ecc->chmap_exist)
			slot = 0;
		अन्यथा
			slot = ecc->num_channels;
		क्रम (;;) अणु
			slot = find_next_zero_bit(ecc->slot_inuse,
						  ecc->num_slots,
						  slot);
			अगर (slot == ecc->num_slots)
				वापस -ENOMEM;
			अगर (!test_and_set_bit(slot, ecc->slot_inuse))
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (slot >= ecc->num_slots) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (test_and_set_bit(slot, ecc->slot_inuse)) अणु
		वापस -EBUSY;
	पूर्ण

	edma_ग_लिखो_slot(ecc, slot, &dummy_paramset);

	वापस EDMA_CTLR_CHAN(ecc->id, slot);
पूर्ण

अटल व्योम edma_मुक्त_slot(काष्ठा edma_cc *ecc, अचिन्हित slot)
अणु
	slot = EDMA_CHAN_SLOT(slot);
	अगर (slot >= ecc->num_slots)
		वापस;

	edma_ग_लिखो_slot(ecc, slot, &dummy_paramset);
	clear_bit(slot, ecc->slot_inuse);
पूर्ण

/**
 * edma_link - link one parameter RAM slot to another
 * @ecc: poपूर्णांकer to edma_cc काष्ठा
 * @from: parameter RAM slot originating the link
 * @to: parameter RAM slot which is the link target
 *
 * The originating slot should not be part of any active DMA transfer.
 */
अटल व्योम edma_link(काष्ठा edma_cc *ecc, अचिन्हित from, अचिन्हित to)
अणु
	अगर (unlikely(EDMA_CTLR(from) != EDMA_CTLR(to)))
		dev_warn(ecc->dev, "Ignoring eDMA instance for linking\n");

	from = EDMA_CHAN_SLOT(from);
	to = EDMA_CHAN_SLOT(to);
	अगर (from >= ecc->num_slots || to >= ecc->num_slots)
		वापस;

	edma_param_modअगरy(ecc, PARM_LINK_BCNTRLD, from, 0xffff0000,
			  PARM_OFFSET(to));
पूर्ण

/**
 * edma_get_position - वापसs the current transfer poपूर्णांक
 * @ecc: poपूर्णांकer to edma_cc काष्ठा
 * @slot: parameter RAM slot being examined
 * @dst:  true selects the dest position, false the source
 *
 * Returns the position of the current active slot
 */
अटल dma_addr_t edma_get_position(काष्ठा edma_cc *ecc, अचिन्हित slot,
				    bool dst)
अणु
	u32 offs;

	slot = EDMA_CHAN_SLOT(slot);
	offs = PARM_OFFSET(slot);
	offs += dst ? PARM_DST : PARM_SRC;

	वापस edma_पढ़ो(ecc, offs);
पूर्ण

/*
 * Channels with event associations will be triggered by their hardware
 * events, and channels without such associations will be triggered by
 * software.  (At this writing there is no पूर्णांकerface क्रम using software
 * triggers except with channels that करोn't support hardware triggers.)
 */
अटल व्योम edma_start(काष्ठा edma_chan *echan)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);
	पूर्णांक idx = EDMA_REG_ARRAY_INDEX(channel);
	पूर्णांक ch_bit = EDMA_CHANNEL_BIT(channel);

	अगर (!echan->hw_triggered) अणु
		/* EDMA channels without event association */
		dev_dbg(ecc->dev, "ESR%d %08x\n", idx,
			edma_shaकरोw0_पढ़ो_array(ecc, SH_ESR, idx));
		edma_shaकरोw0_ग_लिखो_array(ecc, SH_ESR, idx, ch_bit);
	पूर्ण अन्यथा अणु
		/* EDMA channel with event association */
		dev_dbg(ecc->dev, "ER%d %08x\n", idx,
			edma_shaकरोw0_पढ़ो_array(ecc, SH_ER, idx));
		/* Clear any pending event or error */
		edma_ग_लिखो_array(ecc, EDMA_ECR, idx, ch_bit);
		edma_ग_लिखो_array(ecc, EDMA_EMCR, idx, ch_bit);
		/* Clear any SER */
		edma_shaकरोw0_ग_लिखो_array(ecc, SH_SECR, idx, ch_bit);
		edma_shaकरोw0_ग_लिखो_array(ecc, SH_EESR, idx, ch_bit);
		dev_dbg(ecc->dev, "EER%d %08x\n", idx,
			edma_shaकरोw0_पढ़ो_array(ecc, SH_EER, idx));
	पूर्ण
पूर्ण

अटल व्योम edma_stop(काष्ठा edma_chan *echan)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);
	पूर्णांक idx = EDMA_REG_ARRAY_INDEX(channel);
	पूर्णांक ch_bit = EDMA_CHANNEL_BIT(channel);

	edma_shaकरोw0_ग_लिखो_array(ecc, SH_EECR, idx, ch_bit);
	edma_shaकरोw0_ग_लिखो_array(ecc, SH_ECR, idx, ch_bit);
	edma_shaकरोw0_ग_लिखो_array(ecc, SH_SECR, idx, ch_bit);
	edma_ग_लिखो_array(ecc, EDMA_EMCR, idx, ch_bit);

	/* clear possibly pending completion पूर्णांकerrupt */
	edma_shaकरोw0_ग_लिखो_array(ecc, SH_ICR, idx, ch_bit);

	dev_dbg(ecc->dev, "EER%d %08x\n", idx,
		edma_shaकरोw0_पढ़ो_array(ecc, SH_EER, idx));

	/* REVISIT:  consider guarding against inappropriate event
	 * chaining by overwriting with dummy_paramset.
	 */
पूर्ण

/*
 * Temporarily disable EDMA hardware events on the specअगरied channel,
 * preventing them from triggering new transfers
 */
अटल व्योम edma_छोड़ो(काष्ठा edma_chan *echan)
अणु
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);

	edma_shaकरोw0_ग_लिखो_array(echan->ecc, SH_EECR,
				 EDMA_REG_ARRAY_INDEX(channel),
				 EDMA_CHANNEL_BIT(channel));
पूर्ण

/* Re-enable EDMA hardware events on the specअगरied channel.  */
अटल व्योम edma_resume(काष्ठा edma_chan *echan)
अणु
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);

	edma_shaकरोw0_ग_लिखो_array(echan->ecc, SH_EESR,
				 EDMA_REG_ARRAY_INDEX(channel),
				 EDMA_CHANNEL_BIT(channel));
पूर्ण

अटल व्योम edma_trigger_channel(काष्ठा edma_chan *echan)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);
	पूर्णांक idx = EDMA_REG_ARRAY_INDEX(channel);
	पूर्णांक ch_bit = EDMA_CHANNEL_BIT(channel);

	edma_shaकरोw0_ग_लिखो_array(ecc, SH_ESR, idx, ch_bit);

	dev_dbg(ecc->dev, "ESR%d %08x\n", idx,
		edma_shaकरोw0_पढ़ो_array(ecc, SH_ESR, idx));
पूर्ण

अटल व्योम edma_clean_channel(काष्ठा edma_chan *echan)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);
	पूर्णांक idx = EDMA_REG_ARRAY_INDEX(channel);
	पूर्णांक ch_bit = EDMA_CHANNEL_BIT(channel);

	dev_dbg(ecc->dev, "EMR%d %08x\n", idx,
		edma_पढ़ो_array(ecc, EDMA_EMR, idx));
	edma_shaकरोw0_ग_लिखो_array(ecc, SH_ECR, idx, ch_bit);
	/* Clear the corresponding EMR bits */
	edma_ग_लिखो_array(ecc, EDMA_EMCR, idx, ch_bit);
	/* Clear any SER */
	edma_shaकरोw0_ग_लिखो_array(ecc, SH_SECR, idx, ch_bit);
	edma_ग_लिखो(ecc, EDMA_CCERRCLR, BIT(16) | BIT(1) | BIT(0));
पूर्ण

/* Move channel to a specअगरic event queue */
अटल व्योम edma_assign_channel_eventq(काष्ठा edma_chan *echan,
				       क्रमागत dma_event_q eventq_no)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);
	पूर्णांक bit = (channel & 0x7) * 4;

	/* शेष to low priority queue */
	अगर (eventq_no == EVENTQ_DEFAULT)
		eventq_no = ecc->शेष_queue;
	अगर (eventq_no >= ecc->num_tc)
		वापस;

	eventq_no &= 7;
	edma_modअगरy_array(ecc, EDMA_DMAQNUM, (channel >> 3), ~(0x7 << bit),
			  eventq_no << bit);
पूर्ण

अटल पूर्णांक edma_alloc_channel(काष्ठा edma_chan *echan,
			      क्रमागत dma_event_q eventq_no)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);

	अगर (!test_bit(echan->ch_num, ecc->channels_mask)) अणु
		dev_err(ecc->dev, "Channel%d is reserved, can not be used!\n",
			echan->ch_num);
		वापस -EINVAL;
	पूर्ण

	/* ensure access through shaकरोw region 0 */
	edma_or_array2(ecc, EDMA_DRAE, 0, EDMA_REG_ARRAY_INDEX(channel),
		       EDMA_CHANNEL_BIT(channel));

	/* ensure no events are pending */
	edma_stop(echan);

	edma_setup_पूर्णांकerrupt(echan, true);

	edma_assign_channel_eventq(echan, eventq_no);

	वापस 0;
पूर्ण

अटल व्योम edma_मुक्त_channel(काष्ठा edma_chan *echan)
अणु
	/* ensure no events are pending */
	edma_stop(echan);
	/* REVISIT should probably take out of shaकरोw region 0 */
	edma_setup_पूर्णांकerrupt(echan, false);
पूर्ण

अटल अंतरभूत काष्ठा edma_cc *to_edma_cc(काष्ठा dma_device *d)
अणु
	वापस container_of(d, काष्ठा edma_cc, dma_slave);
पूर्ण

अटल अंतरभूत काष्ठा edma_chan *to_edma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा edma_chan, vchan.chan);
पूर्ण

अटल अंतरभूत काष्ठा edma_desc *to_edma_desc(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस container_of(tx, काष्ठा edma_desc, vdesc.tx);
पूर्ण

अटल व्योम edma_desc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	kमुक्त(container_of(vdesc, काष्ठा edma_desc, vdesc));
पूर्ण

/* Dispatch a queued descriptor to the controller (caller holds lock) */
अटल व्योम edma_execute(काष्ठा edma_chan *echan)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	काष्ठा virt_dma_desc *vdesc;
	काष्ठा edma_desc *edesc;
	काष्ठा device *dev = echan->vchan.chan.device->dev;
	पूर्णांक i, j, left, nslots;

	अगर (!echan->edesc) अणु
		/* Setup is needed क्रम the first transfer */
		vdesc = vchan_next_desc(&echan->vchan);
		अगर (!vdesc)
			वापस;
		list_del(&vdesc->node);
		echan->edesc = to_edma_desc(&vdesc->tx);
	पूर्ण

	edesc = echan->edesc;

	/* Find out how many left */
	left = edesc->pset_nr - edesc->processed;
	nslots = min(MAX_NR_SG, left);
	edesc->sg_len = 0;

	/* Write descriptor PaRAM set(s) */
	क्रम (i = 0; i < nslots; i++) अणु
		j = i + edesc->processed;
		edma_ग_लिखो_slot(ecc, echan->slot[i], &edesc->pset[j].param);
		edesc->sg_len += edesc->pset[j].len;
		dev_vdbg(dev,
			 "\n pset[%d]:\n"
			 "  chnum\t%d\n"
			 "  slot\t%d\n"
			 "  opt\t%08x\n"
			 "  src\t%08x\n"
			 "  dst\t%08x\n"
			 "  abcnt\t%08x\n"
			 "  ccnt\t%08x\n"
			 "  bidx\t%08x\n"
			 "  cidx\t%08x\n"
			 "  lkrld\t%08x\n",
			 j, echan->ch_num, echan->slot[i],
			 edesc->pset[j].param.opt,
			 edesc->pset[j].param.src,
			 edesc->pset[j].param.dst,
			 edesc->pset[j].param.a_b_cnt,
			 edesc->pset[j].param.ccnt,
			 edesc->pset[j].param.src_dst_bidx,
			 edesc->pset[j].param.src_dst_cidx,
			 edesc->pset[j].param.link_bcntrld);
		/* Link to the previous slot अगर not the last set */
		अगर (i != (nslots - 1))
			edma_link(ecc, echan->slot[i], echan->slot[i + 1]);
	पूर्ण

	edesc->processed += nslots;

	/*
	 * If this is either the last set in a set of SG-list transactions
	 * then setup a link to the dummy slot, this results in all future
	 * events being असलorbed and that's OK because we're करोne
	 */
	अगर (edesc->processed == edesc->pset_nr) अणु
		अगर (edesc->cyclic)
			edma_link(ecc, echan->slot[nslots - 1], echan->slot[1]);
		अन्यथा
			edma_link(ecc, echan->slot[nslots - 1],
				  echan->ecc->dummy_slot);
	पूर्ण

	अगर (echan->missed) अणु
		/*
		 * This happens due to setup बार between पूर्णांकermediate
		 * transfers in दीर्घ SG lists which have to be broken up पूर्णांकo
		 * transfers of MAX_NR_SG
		 */
		dev_dbg(dev, "missed event on channel %d\n", echan->ch_num);
		edma_clean_channel(echan);
		edma_stop(echan);
		edma_start(echan);
		edma_trigger_channel(echan);
		echan->missed = 0;
	पूर्ण अन्यथा अगर (edesc->processed <= MAX_NR_SG) अणु
		dev_dbg(dev, "first transfer starting on channel %d\n",
			echan->ch_num);
		edma_start(echan);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "chan: %d: completed %d elements, resuming\n",
			echan->ch_num, edesc->processed);
		edma_resume(echan);
	पूर्ण
पूर्ण

अटल पूर्णांक edma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&echan->vchan.lock, flags);

	/*
	 * Stop DMA activity: we assume the callback will not be called
	 * after edma_dma() वापसs (even अगर it करोes, it will see
	 * echan->edesc is शून्य and निकास.)
	 */
	अगर (echan->edesc) अणु
		edma_stop(echan);
		/* Move the cyclic channel back to शेष queue */
		अगर (!echan->tc && echan->edesc->cyclic)
			edma_assign_channel_eventq(echan, EVENTQ_DEFAULT);

		vchan_terminate_vdesc(&echan->edesc->vdesc);
		echan->edesc = शून्य;
	पूर्ण

	vchan_get_all_descriptors(&echan->vchan, &head);
	spin_unlock_irqrestore(&echan->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&echan->vchan, &head);

	वापस 0;
पूर्ण

अटल व्योम edma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);

	vchan_synchronize(&echan->vchan);
पूर्ण

अटल पूर्णांक edma_slave_config(काष्ठा dma_chan *chan,
	काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);

	अगर (cfg->src_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES ||
	    cfg->dst_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES)
		वापस -EINVAL;

	अगर (cfg->src_maxburst > chan->device->max_burst ||
	    cfg->dst_maxburst > chan->device->max_burst)
		वापस -EINVAL;

	स_नकल(&echan->cfg, cfg, माप(echan->cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक edma_dma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);

	अगर (!echan->edesc)
		वापस -EINVAL;

	edma_छोड़ो(echan);
	वापस 0;
पूर्ण

अटल पूर्णांक edma_dma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);

	edma_resume(echan);
	वापस 0;
पूर्ण

/*
 * A PaRAM set configuration असलtraction used by other modes
 * @chan: Channel who's PaRAM set we're configuring
 * @pset: PaRAM set to initialize and setup.
 * @src_addr: Source address of the DMA
 * @dst_addr: Destination address of the DMA
 * @burst: In units of dev_width, how much to send
 * @dev_width: How much is the dev_width
 * @dma_length: Total length of the DMA transfer
 * @direction: Direction of the transfer
 */
अटल पूर्णांक edma_config_pset(काष्ठा dma_chan *chan, काष्ठा edma_pset *epset,
			    dma_addr_t src_addr, dma_addr_t dst_addr, u32 burst,
			    अचिन्हित पूर्णांक acnt, अचिन्हित पूर्णांक dma_length,
			    क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	काष्ठा device *dev = chan->device->dev;
	काष्ठा edmacc_param *param = &epset->param;
	पूर्णांक bcnt, ccnt, cidx;
	पूर्णांक src_bidx, dst_bidx, src_cidx, dst_cidx;
	पूर्णांक असलync;

	/* src/dst_maxburst == 0 is the same हाल as src/dst_maxburst == 1 */
	अगर (!burst)
		burst = 1;
	/*
	 * If the maxburst is equal to the fअगरo width, use
	 * A-synced transfers. This allows क्रम large contiguous
	 * buffer transfers using only one PaRAM set.
	 */
	अगर (burst == 1) अणु
		/*
		 * For the A-sync हाल, bcnt and ccnt are the reमुख्यder
		 * and quotient respectively of the भागision of:
		 * (dma_length / acnt) by (SZ_64K -1). This is so
		 * that in हाल bcnt over flows, we have ccnt to use.
		 * Note: In A-sync tranfer only, bcntrld is used, but it
		 * only applies क्रम sg_dma_len(sg) >= SZ_64K.
		 * In this हाल, the best way aकरोpted is- bccnt क्रम the
		 * first frame will be the reमुख्यder below. Then क्रम
		 * every successive frame, bcnt will be SZ_64K-1. This
		 * is assured as bcntrld = 0xffff in end of function.
		 */
		असलync = false;
		ccnt = dma_length / acnt / (SZ_64K - 1);
		bcnt = dma_length / acnt - ccnt * (SZ_64K - 1);
		/*
		 * If bcnt is non-zero, we have a reमुख्यder and hence an
		 * extra frame to transfer, so increment ccnt.
		 */
		अगर (bcnt)
			ccnt++;
		अन्यथा
			bcnt = SZ_64K - 1;
		cidx = acnt;
	पूर्ण अन्यथा अणु
		/*
		 * If maxburst is greater than the fअगरo address_width,
		 * use AB-synced transfers where A count is the fअगरo
		 * address_width and B count is the maxburst. In this
		 * हाल, we are limited to transfers of C count frames
		 * of (address_width * maxburst) where C count is limited
		 * to SZ_64K-1. This places an upper bound on the length
		 * of an SG segment that can be handled.
		 */
		असलync = true;
		bcnt = burst;
		ccnt = dma_length / (acnt * bcnt);
		अगर (ccnt > (SZ_64K - 1)) अणु
			dev_err(dev, "Exceeded max SG segment size\n");
			वापस -EINVAL;
		पूर्ण
		cidx = acnt * bcnt;
	पूर्ण

	epset->len = dma_length;

	अगर (direction == DMA_MEM_TO_DEV) अणु
		src_bidx = acnt;
		src_cidx = cidx;
		dst_bidx = 0;
		dst_cidx = 0;
		epset->addr = src_addr;
	पूर्ण अन्यथा अगर (direction == DMA_DEV_TO_MEM)  अणु
		src_bidx = 0;
		src_cidx = 0;
		dst_bidx = acnt;
		dst_cidx = cidx;
		epset->addr = dst_addr;
	पूर्ण अन्यथा अगर (direction == DMA_MEM_TO_MEM)  अणु
		src_bidx = acnt;
		src_cidx = cidx;
		dst_bidx = acnt;
		dst_cidx = cidx;
		epset->addr = src_addr;
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s: direction not implemented yet\n", __func__);
		वापस -EINVAL;
	पूर्ण

	param->opt = EDMA_TCC(EDMA_CHAN_SLOT(echan->ch_num));
	/* Configure A or AB synchronized transfers */
	अगर (असलync)
		param->opt |= SYNCDIM;

	param->src = src_addr;
	param->dst = dst_addr;

	param->src_dst_bidx = (dst_bidx << 16) | src_bidx;
	param->src_dst_cidx = (dst_cidx << 16) | src_cidx;

	param->a_b_cnt = bcnt << 16 | acnt;
	param->ccnt = ccnt;
	/*
	 * Only समय when (bcntrld) स्वतः reload is required is क्रम
	 * A-sync हाल, and in this हाल, a requirement of reload value
	 * of SZ_64K-1 only is assured. 'link' is initially set to शून्य
	 * and then later will be populated by edma_execute.
	 */
	param->link_bcntrld = 0xffffffff;
	वापस असलync;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *edma_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
	अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	काष्ठा device *dev = chan->device->dev;
	काष्ठा edma_desc *edesc;
	dma_addr_t src_addr = 0, dst_addr = 0;
	क्रमागत dma_slave_buswidth dev_width;
	u32 burst;
	काष्ठा scatterlist *sg;
	पूर्णांक i, nslots, ret;

	अगर (unlikely(!echan || !sgl || !sg_len))
		वापस शून्य;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		src_addr = echan->cfg.src_addr;
		dev_width = echan->cfg.src_addr_width;
		burst = echan->cfg.src_maxburst;
	पूर्ण अन्यथा अगर (direction == DMA_MEM_TO_DEV) अणु
		dst_addr = echan->cfg.dst_addr;
		dev_width = echan->cfg.dst_addr_width;
		burst = echan->cfg.dst_maxburst;
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s: bad direction: %d\n", __func__, direction);
		वापस शून्य;
	पूर्ण

	अगर (dev_width == DMA_SLAVE_BUSWIDTH_UNDEFINED) अणु
		dev_err(dev, "%s: Undefined slave buswidth\n", __func__);
		वापस शून्य;
	पूर्ण

	edesc = kzalloc(काष्ठा_size(edesc, pset, sg_len), GFP_ATOMIC);
	अगर (!edesc)
		वापस शून्य;

	edesc->pset_nr = sg_len;
	edesc->residue = 0;
	edesc->direction = direction;
	edesc->echan = echan;

	/* Allocate a PaRAM slot, अगर needed */
	nslots = min_t(अचिन्हित, MAX_NR_SG, sg_len);

	क्रम (i = 0; i < nslots; i++) अणु
		अगर (echan->slot[i] < 0) अणु
			echan->slot[i] =
				edma_alloc_slot(echan->ecc, EDMA_SLOT_ANY);
			अगर (echan->slot[i] < 0) अणु
				kमुक्त(edesc);
				dev_err(dev, "%s: Failed to allocate slot\n",
					__func__);
				वापस शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Configure PaRAM sets क्रम each SG */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		/* Get address क्रम each SG */
		अगर (direction == DMA_DEV_TO_MEM)
			dst_addr = sg_dma_address(sg);
		अन्यथा
			src_addr = sg_dma_address(sg);

		ret = edma_config_pset(chan, &edesc->pset[i], src_addr,
				       dst_addr, burst, dev_width,
				       sg_dma_len(sg), direction);
		अगर (ret < 0) अणु
			kमुक्त(edesc);
			वापस शून्य;
		पूर्ण

		edesc->असलync = ret;
		edesc->residue += sg_dma_len(sg);

		अगर (i == sg_len - 1)
			/* Enable completion पूर्णांकerrupt */
			edesc->pset[i].param.opt |= TCINTEN;
		अन्यथा अगर (!((i+1) % MAX_NR_SG))
			/*
			 * Enable early completion पूर्णांकerrupt क्रम the
			 * पूर्णांकermediateset. In this हाल the driver will be
			 * notअगरied when the paRAM set is submitted to TC. This
			 * will allow more समय to set up the next set of slots.
			 */
			edesc->pset[i].param.opt |= (TCINTEN | TCCMODE);
	पूर्ण
	edesc->residue_stat = edesc->residue;

	वापस vchan_tx_prep(&echan->vchan, &edesc->vdesc, tx_flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *edma_prep_dma_स_नकल(
	काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
	माप_प्रकार len, अचिन्हित दीर्घ tx_flags)
अणु
	पूर्णांक ret, nslots;
	काष्ठा edma_desc *edesc;
	काष्ठा device *dev = chan->device->dev;
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	अचिन्हित पूर्णांक width, pset_len, array_size;

	अगर (unlikely(!echan || !len))
		वापस शून्य;

	/* Align the array size (acnt block) with the transfer properties */
	चयन (__ffs((src | dest | len))) अणु
	हाल 0:
		array_size = SZ_32K - 1;
		अवरोध;
	हाल 1:
		array_size = SZ_32K - 2;
		अवरोध;
	शेष:
		array_size = SZ_32K - 4;
		अवरोध;
	पूर्ण

	अगर (len < SZ_64K) अणु
		/*
		 * Transfer size less than 64K can be handled with one paRAM
		 * slot and with one burst.
		 * ACNT = length
		 */
		width = len;
		pset_len = len;
		nslots = 1;
	पूर्ण अन्यथा अणु
		/*
		 * Transfer size bigger than 64K will be handled with maximum of
		 * two paRAM slots.
		 * slot1: (full_length / 32767) बार 32767 bytes bursts.
		 *	  ACNT = 32767, length1: (full_length / 32767) * 32767
		 * slot2: the reमुख्यing amount of data after slot1.
		 *	  ACNT = full_length - length1, length2 = ACNT
		 *
		 * When the full_length is multibple of 32767 one slot can be
		 * used to complete the transfer.
		 */
		width = array_size;
		pset_len = roundकरोwn(len, width);
		/* One slot is enough क्रम lengths multiple of (SZ_32K -1) */
		अगर (unlikely(pset_len == len))
			nslots = 1;
		अन्यथा
			nslots = 2;
	पूर्ण

	edesc = kzalloc(काष्ठा_size(edesc, pset, nslots), GFP_ATOMIC);
	अगर (!edesc)
		वापस शून्य;

	edesc->pset_nr = nslots;
	edesc->residue = edesc->residue_stat = len;
	edesc->direction = DMA_MEM_TO_MEM;
	edesc->echan = echan;

	ret = edma_config_pset(chan, &edesc->pset[0], src, dest, 1,
			       width, pset_len, DMA_MEM_TO_MEM);
	अगर (ret < 0) अणु
		kमुक्त(edesc);
		वापस शून्य;
	पूर्ण

	edesc->असलync = ret;

	edesc->pset[0].param.opt |= ITCCHEN;
	अगर (nslots == 1) अणु
		/* Enable transfer complete पूर्णांकerrupt अगर requested */
		अगर (tx_flags & DMA_PREP_INTERRUPT)
			edesc->pset[0].param.opt |= TCINTEN;
	पूर्ण अन्यथा अणु
		/* Enable transfer complete chaining क्रम the first slot */
		edesc->pset[0].param.opt |= TCCHEN;

		अगर (echan->slot[1] < 0) अणु
			echan->slot[1] = edma_alloc_slot(echan->ecc,
							 EDMA_SLOT_ANY);
			अगर (echan->slot[1] < 0) अणु
				kमुक्त(edesc);
				dev_err(dev, "%s: Failed to allocate slot\n",
					__func__);
				वापस शून्य;
			पूर्ण
		पूर्ण
		dest += pset_len;
		src += pset_len;
		pset_len = width = len % array_size;

		ret = edma_config_pset(chan, &edesc->pset[1], src, dest, 1,
				       width, pset_len, DMA_MEM_TO_MEM);
		अगर (ret < 0) अणु
			kमुक्त(edesc);
			वापस शून्य;
		पूर्ण

		edesc->pset[1].param.opt |= ITCCHEN;
		/* Enable transfer complete पूर्णांकerrupt अगर requested */
		अगर (tx_flags & DMA_PREP_INTERRUPT)
			edesc->pset[1].param.opt |= TCINTEN;
	पूर्ण

	अगर (!(tx_flags & DMA_PREP_INTERRUPT))
		edesc->polled = true;

	वापस vchan_tx_prep(&echan->vchan, &edesc->vdesc, tx_flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
edma_prep_dma_पूर्णांकerleaved(काष्ठा dma_chan *chan,
			  काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
			  अचिन्हित दीर्घ tx_flags)
अणु
	काष्ठा device *dev = chan->device->dev;
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	काष्ठा edmacc_param *param;
	काष्ठा edma_desc *edesc;
	माप_प्रकार src_icg, dst_icg;
	पूर्णांक src_bidx, dst_bidx;

	/* Slave mode is not supported */
	अगर (is_slave_direction(xt->dir))
		वापस शून्य;

	अगर (xt->frame_size != 1 || xt->numf == 0)
		वापस शून्य;

	अगर (xt->sgl[0].size > SZ_64K || xt->numf > SZ_64K)
		वापस शून्य;

	src_icg = dmaengine_get_src_icg(xt, &xt->sgl[0]);
	अगर (src_icg) अणु
		src_bidx = src_icg + xt->sgl[0].size;
	पूर्ण अन्यथा अगर (xt->src_inc) अणु
		src_bidx = xt->sgl[0].size;
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s: SRC constant addressing is not supported\n",
			__func__);
		वापस शून्य;
	पूर्ण

	dst_icg = dmaengine_get_dst_icg(xt, &xt->sgl[0]);
	अगर (dst_icg) अणु
		dst_bidx = dst_icg + xt->sgl[0].size;
	पूर्ण अन्यथा अगर (xt->dst_inc) अणु
		dst_bidx = xt->sgl[0].size;
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s: DST constant addressing is not supported\n",
			__func__);
		वापस शून्य;
	पूर्ण

	अगर (src_bidx > SZ_64K || dst_bidx > SZ_64K)
		वापस शून्य;

	edesc = kzalloc(काष्ठा_size(edesc, pset, 1), GFP_ATOMIC);
	अगर (!edesc)
		वापस शून्य;

	edesc->direction = DMA_MEM_TO_MEM;
	edesc->echan = echan;
	edesc->pset_nr = 1;

	param = &edesc->pset[0].param;

	param->src = xt->src_start;
	param->dst = xt->dst_start;
	param->a_b_cnt = xt->numf << 16 | xt->sgl[0].size;
	param->ccnt = 1;
	param->src_dst_bidx = (dst_bidx << 16) | src_bidx;
	param->src_dst_cidx = 0;

	param->opt = EDMA_TCC(EDMA_CHAN_SLOT(echan->ch_num));
	param->opt |= ITCCHEN;
	/* Enable transfer complete पूर्णांकerrupt अगर requested */
	अगर (tx_flags & DMA_PREP_INTERRUPT)
		param->opt |= TCINTEN;
	अन्यथा
		edesc->polled = true;

	वापस vchan_tx_prep(&echan->vchan, &edesc->vdesc, tx_flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *edma_prep_dma_cyclic(
	काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ tx_flags)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	काष्ठा device *dev = chan->device->dev;
	काष्ठा edma_desc *edesc;
	dma_addr_t src_addr, dst_addr;
	क्रमागत dma_slave_buswidth dev_width;
	bool use_पूर्णांकermediate = false;
	u32 burst;
	पूर्णांक i, ret, nslots;

	अगर (unlikely(!echan || !buf_len || !period_len))
		वापस शून्य;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		src_addr = echan->cfg.src_addr;
		dst_addr = buf_addr;
		dev_width = echan->cfg.src_addr_width;
		burst = echan->cfg.src_maxburst;
	पूर्ण अन्यथा अगर (direction == DMA_MEM_TO_DEV) अणु
		src_addr = buf_addr;
		dst_addr = echan->cfg.dst_addr;
		dev_width = echan->cfg.dst_addr_width;
		burst = echan->cfg.dst_maxburst;
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s: bad direction: %d\n", __func__, direction);
		वापस शून्य;
	पूर्ण

	अगर (dev_width == DMA_SLAVE_BUSWIDTH_UNDEFINED) अणु
		dev_err(dev, "%s: Undefined slave buswidth\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (unlikely(buf_len % period_len)) अणु
		dev_err(dev, "Period should be multiple of Buffer length\n");
		वापस शून्य;
	पूर्ण

	nslots = (buf_len / period_len) + 1;

	/*
	 * Cyclic DMA users such as audio cannot tolerate delays पूर्णांकroduced
	 * by हालs where the number of periods is more than the maximum
	 * number of SGs the EDMA driver can handle at a समय. For DMA types
	 * such as Slave SGs, such delays are tolerable and synchronized,
	 * but the synchronization is dअगरficult to achieve with Cyclic and
	 * cannot be guaranteed, so we error out early.
	 */
	अगर (nslots > MAX_NR_SG) अणु
		/*
		 * If the burst and period sizes are the same, we can put
		 * the full buffer पूर्णांकo a single period and activate
		 * पूर्णांकermediate पूर्णांकerrupts. This will produce पूर्णांकerrupts
		 * after each burst, which is also after each desired period.
		 */
		अगर (burst == period_len) अणु
			period_len = buf_len;
			nslots = 2;
			use_पूर्णांकermediate = true;
		पूर्ण अन्यथा अणु
			वापस शून्य;
		पूर्ण
	पूर्ण

	edesc = kzalloc(काष्ठा_size(edesc, pset, nslots), GFP_ATOMIC);
	अगर (!edesc)
		वापस शून्य;

	edesc->cyclic = 1;
	edesc->pset_nr = nslots;
	edesc->residue = edesc->residue_stat = buf_len;
	edesc->direction = direction;
	edesc->echan = echan;

	dev_dbg(dev, "%s: channel=%d nslots=%d period_len=%zu buf_len=%zu\n",
		__func__, echan->ch_num, nslots, period_len, buf_len);

	क्रम (i = 0; i < nslots; i++) अणु
		/* Allocate a PaRAM slot, अगर needed */
		अगर (echan->slot[i] < 0) अणु
			echan->slot[i] =
				edma_alloc_slot(echan->ecc, EDMA_SLOT_ANY);
			अगर (echan->slot[i] < 0) अणु
				kमुक्त(edesc);
				dev_err(dev, "%s: Failed to allocate slot\n",
					__func__);
				वापस शून्य;
			पूर्ण
		पूर्ण

		अगर (i == nslots - 1) अणु
			स_नकल(&edesc->pset[i], &edesc->pset[0],
			       माप(edesc->pset[0]));
			अवरोध;
		पूर्ण

		ret = edma_config_pset(chan, &edesc->pset[i], src_addr,
				       dst_addr, burst, dev_width, period_len,
				       direction);
		अगर (ret < 0) अणु
			kमुक्त(edesc);
			वापस शून्य;
		पूर्ण

		अगर (direction == DMA_DEV_TO_MEM)
			dst_addr += period_len;
		अन्यथा
			src_addr += period_len;

		dev_vdbg(dev, "%s: Configure period %d of buf:\n", __func__, i);
		dev_vdbg(dev,
			"\n pset[%d]:\n"
			"  chnum\t%d\n"
			"  slot\t%d\n"
			"  opt\t%08x\n"
			"  src\t%08x\n"
			"  dst\t%08x\n"
			"  abcnt\t%08x\n"
			"  ccnt\t%08x\n"
			"  bidx\t%08x\n"
			"  cidx\t%08x\n"
			"  lkrld\t%08x\n",
			i, echan->ch_num, echan->slot[i],
			edesc->pset[i].param.opt,
			edesc->pset[i].param.src,
			edesc->pset[i].param.dst,
			edesc->pset[i].param.a_b_cnt,
			edesc->pset[i].param.ccnt,
			edesc->pset[i].param.src_dst_bidx,
			edesc->pset[i].param.src_dst_cidx,
			edesc->pset[i].param.link_bcntrld);

		edesc->असलync = ret;

		/*
		 * Enable period पूर्णांकerrupt only अगर it is requested
		 */
		अगर (tx_flags & DMA_PREP_INTERRUPT) अणु
			edesc->pset[i].param.opt |= TCINTEN;

			/* Also enable पूर्णांकermediate पूर्णांकerrupts अगर necessary */
			अगर (use_पूर्णांकermediate)
				edesc->pset[i].param.opt |= ITCINTEN;
		पूर्ण
	पूर्ण

	/* Place the cyclic channel to highest priority queue */
	अगर (!echan->tc)
		edma_assign_channel_eventq(echan, EVENTQ_0);

	वापस vchan_tx_prep(&echan->vchan, &edesc->vdesc, tx_flags);
पूर्ण

अटल व्योम edma_completion_handler(काष्ठा edma_chan *echan)
अणु
	काष्ठा device *dev = echan->vchan.chan.device->dev;
	काष्ठा edma_desc *edesc;

	spin_lock(&echan->vchan.lock);
	edesc = echan->edesc;
	अगर (edesc) अणु
		अगर (edesc->cyclic) अणु
			vchan_cyclic_callback(&edesc->vdesc);
			spin_unlock(&echan->vchan.lock);
			वापस;
		पूर्ण अन्यथा अगर (edesc->processed == edesc->pset_nr) अणु
			edesc->residue = 0;
			edma_stop(echan);
			vchan_cookie_complete(&edesc->vdesc);
			echan->edesc = शून्य;

			dev_dbg(dev, "Transfer completed on channel %d\n",
				echan->ch_num);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "Sub transfer completed on channel %d\n",
				echan->ch_num);

			edma_छोड़ो(echan);

			/* Update statistics क्रम tx_status */
			edesc->residue -= edesc->sg_len;
			edesc->residue_stat = edesc->residue;
			edesc->processed_stat = edesc->processed;
		पूर्ण
		edma_execute(echan);
	पूर्ण

	spin_unlock(&echan->vchan.lock);
पूर्ण

/* eDMA पूर्णांकerrupt handler */
अटल irqवापस_t dma_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा edma_cc *ecc = data;
	पूर्णांक ctlr;
	u32 sh_ier;
	u32 sh_ipr;
	u32 bank;

	ctlr = ecc->id;
	अगर (ctlr < 0)
		वापस IRQ_NONE;

	dev_vdbg(ecc->dev, "dma_irq_handler\n");

	sh_ipr = edma_shaकरोw0_पढ़ो_array(ecc, SH_IPR, 0);
	अगर (!sh_ipr) अणु
		sh_ipr = edma_shaकरोw0_पढ़ो_array(ecc, SH_IPR, 1);
		अगर (!sh_ipr)
			वापस IRQ_NONE;
		sh_ier = edma_shaकरोw0_पढ़ो_array(ecc, SH_IER, 1);
		bank = 1;
	पूर्ण अन्यथा अणु
		sh_ier = edma_shaकरोw0_पढ़ो_array(ecc, SH_IER, 0);
		bank = 0;
	पूर्ण

	करो अणु
		u32 slot;
		u32 channel;

		slot = __ffs(sh_ipr);
		sh_ipr &= ~(BIT(slot));

		अगर (sh_ier & BIT(slot)) अणु
			channel = (bank << 5) | slot;
			/* Clear the corresponding IPR bits */
			edma_shaकरोw0_ग_लिखो_array(ecc, SH_ICR, bank, BIT(slot));
			edma_completion_handler(&ecc->slave_chans[channel]);
		पूर्ण
	पूर्ण जबतक (sh_ipr);

	edma_shaकरोw0_ग_लिखो(ecc, SH_IEVAL, 1);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम edma_error_handler(काष्ठा edma_chan *echan)
अणु
	काष्ठा edma_cc *ecc = echan->ecc;
	काष्ठा device *dev = echan->vchan.chan.device->dev;
	काष्ठा edmacc_param p;
	पूर्णांक err;

	अगर (!echan->edesc)
		वापस;

	spin_lock(&echan->vchan.lock);

	err = edma_पढ़ो_slot(ecc, echan->slot[0], &p);

	/*
	 * Issue later based on missed flag which will be sure
	 * to happen as:
	 * (1) we finished transmitting an पूर्णांकermediate slot and
	 *     edma_execute is coming up.
	 * (2) or we finished current transfer and issue will
	 *     call edma_execute.
	 *
	 * Important note: issuing can be dangerous here and
	 * lead to some nasty recursion when we are in a शून्य
	 * slot. So we aव्योम करोing so and set the missed flag.
	 */
	अगर (err || (p.a_b_cnt == 0 && p.ccnt == 0)) अणु
		dev_dbg(dev, "Error on null slot, setting miss\n");
		echan->missed = 1;
	पूर्ण अन्यथा अणु
		/*
		 * The slot is alपढ़ोy programmed but the event got
		 * missed, so its safe to issue it here.
		 */
		dev_dbg(dev, "Missed event, TRIGGERING\n");
		edma_clean_channel(echan);
		edma_stop(echan);
		edma_start(echan);
		edma_trigger_channel(echan);
	पूर्ण
	spin_unlock(&echan->vchan.lock);
पूर्ण

अटल अंतरभूत bool edma_error_pending(काष्ठा edma_cc *ecc)
अणु
	अगर (edma_पढ़ो_array(ecc, EDMA_EMR, 0) ||
	    edma_पढ़ो_array(ecc, EDMA_EMR, 1) ||
	    edma_पढ़ो(ecc, EDMA_QEMR) || edma_पढ़ो(ecc, EDMA_CCERR))
		वापस true;

	वापस false;
पूर्ण

/* eDMA error पूर्णांकerrupt handler */
अटल irqवापस_t dma_ccerr_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा edma_cc *ecc = data;
	पूर्णांक i, j;
	पूर्णांक ctlr;
	अचिन्हित पूर्णांक cnt = 0;
	अचिन्हित पूर्णांक val;

	ctlr = ecc->id;
	अगर (ctlr < 0)
		वापस IRQ_NONE;

	dev_vdbg(ecc->dev, "dma_ccerr_handler\n");

	अगर (!edma_error_pending(ecc)) अणु
		/*
		 * The रेजिस्टरs indicate no pending error event but the irq
		 * handler has been called.
		 * Ask eDMA to re-evaluate the error रेजिस्टरs.
		 */
		dev_err(ecc->dev, "%s: Error interrupt without error event!\n",
			__func__);
		edma_ग_लिखो(ecc, EDMA_EEVAL, 1);
		वापस IRQ_NONE;
	पूर्ण

	जबतक (1) अणु
		/* Event missed रेजिस्टर(s) */
		क्रम (j = 0; j < 2; j++) अणु
			अचिन्हित दीर्घ emr;

			val = edma_पढ़ो_array(ecc, EDMA_EMR, j);
			अगर (!val)
				जारी;

			dev_dbg(ecc->dev, "EMR%d 0x%08x\n", j, val);
			emr = val;
			क्रम (i = find_next_bit(&emr, 32, 0); i < 32;
			     i = find_next_bit(&emr, 32, i + 1)) अणु
				पूर्णांक k = (j << 5) + i;

				/* Clear the corresponding EMR bits */
				edma_ग_लिखो_array(ecc, EDMA_EMCR, j, BIT(i));
				/* Clear any SER */
				edma_shaकरोw0_ग_लिखो_array(ecc, SH_SECR, j,
							 BIT(i));
				edma_error_handler(&ecc->slave_chans[k]);
			पूर्ण
		पूर्ण

		val = edma_पढ़ो(ecc, EDMA_QEMR);
		अगर (val) अणु
			dev_dbg(ecc->dev, "QEMR 0x%02x\n", val);
			/* Not reported, just clear the पूर्णांकerrupt reason. */
			edma_ग_लिखो(ecc, EDMA_QEMCR, val);
			edma_shaकरोw0_ग_लिखो(ecc, SH_QSECR, val);
		पूर्ण

		val = edma_पढ़ो(ecc, EDMA_CCERR);
		अगर (val) अणु
			dev_warn(ecc->dev, "CCERR 0x%08x\n", val);
			/* Not reported, just clear the पूर्णांकerrupt reason. */
			edma_ग_लिखो(ecc, EDMA_CCERRCLR, val);
		पूर्ण

		अगर (!edma_error_pending(ecc))
			अवरोध;
		cnt++;
		अगर (cnt > 10)
			अवरोध;
	पूर्ण
	edma_ग_लिखो(ecc, EDMA_EEVAL, 1);
	वापस IRQ_HANDLED;
पूर्ण

/* Alloc channel resources */
अटल पूर्णांक edma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	काष्ठा edma_cc *ecc = echan->ecc;
	काष्ठा device *dev = ecc->dev;
	क्रमागत dma_event_q eventq_no = EVENTQ_DEFAULT;
	पूर्णांक ret;

	अगर (echan->tc) अणु
		eventq_no = echan->tc->id;
	पूर्ण अन्यथा अगर (ecc->tc_list) अणु
		/* स_नकल channel */
		echan->tc = &ecc->tc_list[ecc->info->शेष_queue];
		eventq_no = echan->tc->id;
	पूर्ण

	ret = edma_alloc_channel(echan, eventq_no);
	अगर (ret)
		वापस ret;

	echan->slot[0] = edma_alloc_slot(ecc, echan->ch_num);
	अगर (echan->slot[0] < 0) अणु
		dev_err(dev, "Entry slot allocation failed for channel %u\n",
			EDMA_CHAN_SLOT(echan->ch_num));
		ret = echan->slot[0];
		जाओ err_slot;
	पूर्ण

	/* Set up channel -> slot mapping क्रम the entry slot */
	edma_set_chmap(echan, echan->slot[0]);
	echan->alloced = true;

	dev_dbg(dev, "Got eDMA channel %d for virt channel %d (%s trigger)\n",
		EDMA_CHAN_SLOT(echan->ch_num), chan->chan_id,
		echan->hw_triggered ? "HW" : "SW");

	वापस 0;

err_slot:
	edma_मुक्त_channel(echan);
	वापस ret;
पूर्ण

/* Free channel resources */
अटल व्योम edma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	काष्ठा device *dev = echan->ecc->dev;
	पूर्णांक i;

	/* Terminate transfers */
	edma_stop(echan);

	vchan_मुक्त_chan_resources(&echan->vchan);

	/* Free EDMA PaRAM slots */
	क्रम (i = 0; i < EDMA_MAX_SLOTS; i++) अणु
		अगर (echan->slot[i] >= 0) अणु
			edma_मुक्त_slot(echan->ecc, echan->slot[i]);
			echan->slot[i] = -1;
		पूर्ण
	पूर्ण

	/* Set entry slot to the dummy slot */
	edma_set_chmap(echan, echan->ecc->dummy_slot);

	/* Free EDMA channel */
	अगर (echan->alloced) अणु
		edma_मुक्त_channel(echan);
		echan->alloced = false;
	पूर्ण

	echan->tc = शून्य;
	echan->hw_triggered = false;

	dev_dbg(dev, "Free eDMA channel %d for virt channel %d\n",
		EDMA_CHAN_SLOT(echan->ch_num), chan->chan_id);
पूर्ण

/* Send pending descriptor to hardware */
अटल व्योम edma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&echan->vchan.lock, flags);
	अगर (vchan_issue_pending(&echan->vchan) && !echan->edesc)
		edma_execute(echan);
	spin_unlock_irqrestore(&echan->vchan.lock, flags);
पूर्ण

/*
 * This limit exists to aव्योम a possible infinite loop when रुकोing क्रम proof
 * that a particular transfer is completed. This limit can be hit अगर there
 * are large bursts to/from slow devices or the CPU is never able to catch
 * the DMA hardware idle. On an AM335x transfering 48 bytes from the UART
 * RX-FIFO, as many as 55 loops have been seen.
 */
#घोषणा EDMA_MAX_TR_WAIT_LOOPS 1000

अटल u32 edma_residue(काष्ठा edma_desc *edesc)
अणु
	bool dst = edesc->direction == DMA_DEV_TO_MEM;
	पूर्णांक loop_count = EDMA_MAX_TR_WAIT_LOOPS;
	काष्ठा edma_chan *echan = edesc->echan;
	काष्ठा edma_pset *pset = edesc->pset;
	dma_addr_t करोne, pos, pos_old;
	पूर्णांक channel = EDMA_CHAN_SLOT(echan->ch_num);
	पूर्णांक idx = EDMA_REG_ARRAY_INDEX(channel);
	पूर्णांक ch_bit = EDMA_CHANNEL_BIT(channel);
	पूर्णांक event_reg;
	पूर्णांक i;

	/*
	 * We always पढ़ो the dst/src position from the first RamPar
	 * pset. That's the one which is active now.
	 */
	pos = edma_get_position(echan->ecc, echan->slot[0], dst);

	/*
	 * "pos" may represent a transfer request that is still being
	 * processed by the EDMACC or EDMATC. We will busy रुको until
	 * any one of the situations occurs:
	 *   1. जबतक and event is pending क्रम the channel
	 *   2. a position updated
	 *   3. we hit the loop limit
	 */
	अगर (is_slave_direction(edesc->direction))
		event_reg = SH_ER;
	अन्यथा
		event_reg = SH_ESR;

	pos_old = pos;
	जबतक (edma_shaकरोw0_पढ़ो_array(echan->ecc, event_reg, idx) & ch_bit) अणु
		pos = edma_get_position(echan->ecc, echan->slot[0], dst);
		अगर (pos != pos_old)
			अवरोध;

		अगर (!--loop_count) अणु
			dev_dbg_ratelimited(echan->vchan.chan.device->dev,
				"%s: timeout waiting for PaRAM update\n",
				__func__);
			अवरोध;
		पूर्ण

		cpu_relax();
	पूर्ण

	/*
	 * Cyclic is simple. Just subtract pset[0].addr from pos.
	 *
	 * We never update edesc->residue in the cyclic हाल, so we
	 * can tell the reमुख्यing room to the end of the circular
	 * buffer.
	 */
	अगर (edesc->cyclic) अणु
		करोne = pos - pset->addr;
		edesc->residue_stat = edesc->residue - करोne;
		वापस edesc->residue_stat;
	पूर्ण

	/*
	 * If the position is 0, then EDMA loaded the closing dummy slot, the
	 * transfer is completed
	 */
	अगर (!pos)
		वापस 0;
	/*
	 * For SG operation we catch up with the last processed
	 * status.
	 */
	pset += edesc->processed_stat;

	क्रम (i = edesc->processed_stat; i < edesc->processed; i++, pset++) अणु
		/*
		 * If we are inside this pset address range, we know
		 * this is the active one. Get the current delta and
		 * stop walking the psets.
		 */
		अगर (pos >= pset->addr && pos < pset->addr + pset->len)
			वापस edesc->residue_stat - (pos - pset->addr);

		/* Otherwise mark it करोne and update residue_stat. */
		edesc->processed_stat++;
		edesc->residue_stat -= pset->len;
	पूर्ण
	वापस edesc->residue_stat;
पूर्ण

/* Check request completion status */
अटल क्रमागत dma_status edma_tx_status(काष्ठा dma_chan *chan,
				      dma_cookie_t cookie,
				      काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा edma_chan *echan = to_edma_chan(chan);
	काष्ठा dma_tx_state txstate_पंचांगp;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;

	ret = dma_cookie_status(chan, cookie, txstate);

	अगर (ret == DMA_COMPLETE)
		वापस ret;

	/* Provide a dummy dma_tx_state क्रम completion checking */
	अगर (!txstate)
		txstate = &txstate_पंचांगp;

	spin_lock_irqsave(&echan->vchan.lock, flags);
	अगर (echan->edesc && echan->edesc->vdesc.tx.cookie == cookie) अणु
		txstate->residue = edma_residue(echan->edesc);
	पूर्ण अन्यथा अणु
		काष्ठा virt_dma_desc *vdesc = vchan_find_desc(&echan->vchan,
							      cookie);

		अगर (vdesc)
			txstate->residue = to_edma_desc(&vdesc->tx)->residue;
		अन्यथा
			txstate->residue = 0;
	पूर्ण

	/*
	 * Mark the cookie completed अगर the residue is 0 क्रम non cyclic
	 * transfers
	 */
	अगर (ret != DMA_COMPLETE && !txstate->residue &&
	    echan->edesc && echan->edesc->polled &&
	    echan->edesc->vdesc.tx.cookie == cookie) अणु
		edma_stop(echan);
		vchan_cookie_complete(&echan->edesc->vdesc);
		echan->edesc = शून्य;
		edma_execute(echan);
		ret = DMA_COMPLETE;
	पूर्ण

	spin_unlock_irqrestore(&echan->vchan.lock, flags);

	वापस ret;
पूर्ण

अटल bool edma_is_स_नकल_channel(पूर्णांक ch_num, s32 *स_नकल_channels)
अणु
	अगर (!स_नकल_channels)
		वापस false;
	जबतक (*स_नकल_channels != -1) अणु
		अगर (*स_नकल_channels == ch_num)
			वापस true;
		स_नकल_channels++;
	पूर्ण
	वापस false;
पूर्ण

#घोषणा EDMA_DMA_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_3_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

अटल व्योम edma_dma_init(काष्ठा edma_cc *ecc, bool legacy_mode)
अणु
	काष्ठा dma_device *s_ddev = &ecc->dma_slave;
	काष्ठा dma_device *m_ddev = शून्य;
	s32 *स_नकल_channels = ecc->info->स_नकल_channels;
	पूर्णांक i, j;

	dma_cap_zero(s_ddev->cap_mask);
	dma_cap_set(DMA_SLAVE, s_ddev->cap_mask);
	dma_cap_set(DMA_CYCLIC, s_ddev->cap_mask);
	अगर (ecc->legacy_mode && !स_नकल_channels) अणु
		dev_warn(ecc->dev,
			 "Legacy memcpy is enabled, things might not work\n");

		dma_cap_set(DMA_MEMCPY, s_ddev->cap_mask);
		dma_cap_set(DMA_INTERLEAVE, s_ddev->cap_mask);
		s_ddev->device_prep_dma_स_नकल = edma_prep_dma_स_नकल;
		s_ddev->device_prep_पूर्णांकerleaved_dma = edma_prep_dma_पूर्णांकerleaved;
		s_ddev->directions = BIT(DMA_MEM_TO_MEM);
	पूर्ण

	s_ddev->device_prep_slave_sg = edma_prep_slave_sg;
	s_ddev->device_prep_dma_cyclic = edma_prep_dma_cyclic;
	s_ddev->device_alloc_chan_resources = edma_alloc_chan_resources;
	s_ddev->device_मुक्त_chan_resources = edma_मुक्त_chan_resources;
	s_ddev->device_issue_pending = edma_issue_pending;
	s_ddev->device_tx_status = edma_tx_status;
	s_ddev->device_config = edma_slave_config;
	s_ddev->device_छोड़ो = edma_dma_छोड़ो;
	s_ddev->device_resume = edma_dma_resume;
	s_ddev->device_terminate_all = edma_terminate_all;
	s_ddev->device_synchronize = edma_synchronize;

	s_ddev->src_addr_widths = EDMA_DMA_BUSWIDTHS;
	s_ddev->dst_addr_widths = EDMA_DMA_BUSWIDTHS;
	s_ddev->directions |= (BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV));
	s_ddev->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	s_ddev->max_burst = SZ_32K - 1; /* CIDX: 16bit चिन्हित */

	s_ddev->dev = ecc->dev;
	INIT_LIST_HEAD(&s_ddev->channels);

	अगर (स_नकल_channels) अणु
		m_ddev = devm_kzalloc(ecc->dev, माप(*m_ddev), GFP_KERNEL);
		अगर (!m_ddev) अणु
			dev_warn(ecc->dev, "memcpy is disabled due to OoM\n");
			स_नकल_channels = शून्य;
			जाओ ch_setup;
		पूर्ण
		ecc->dma_स_नकल = m_ddev;

		dma_cap_zero(m_ddev->cap_mask);
		dma_cap_set(DMA_MEMCPY, m_ddev->cap_mask);
		dma_cap_set(DMA_INTERLEAVE, m_ddev->cap_mask);

		m_ddev->device_prep_dma_स_नकल = edma_prep_dma_स_नकल;
		m_ddev->device_prep_पूर्णांकerleaved_dma = edma_prep_dma_पूर्णांकerleaved;
		m_ddev->device_alloc_chan_resources = edma_alloc_chan_resources;
		m_ddev->device_मुक्त_chan_resources = edma_मुक्त_chan_resources;
		m_ddev->device_issue_pending = edma_issue_pending;
		m_ddev->device_tx_status = edma_tx_status;
		m_ddev->device_config = edma_slave_config;
		m_ddev->device_छोड़ो = edma_dma_छोड़ो;
		m_ddev->device_resume = edma_dma_resume;
		m_ddev->device_terminate_all = edma_terminate_all;
		m_ddev->device_synchronize = edma_synchronize;

		m_ddev->src_addr_widths = EDMA_DMA_BUSWIDTHS;
		m_ddev->dst_addr_widths = EDMA_DMA_BUSWIDTHS;
		m_ddev->directions = BIT(DMA_MEM_TO_MEM);
		m_ddev->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

		m_ddev->dev = ecc->dev;
		INIT_LIST_HEAD(&m_ddev->channels);
	पूर्ण अन्यथा अगर (!ecc->legacy_mode) अणु
		dev_info(ecc->dev, "memcpy is disabled\n");
	पूर्ण

ch_setup:
	क्रम (i = 0; i < ecc->num_channels; i++) अणु
		काष्ठा edma_chan *echan = &ecc->slave_chans[i];
		echan->ch_num = EDMA_CTLR_CHAN(ecc->id, i);
		echan->ecc = ecc;
		echan->vchan.desc_मुक्त = edma_desc_मुक्त;

		अगर (m_ddev && edma_is_स_नकल_channel(i, स_नकल_channels))
			vchan_init(&echan->vchan, m_ddev);
		अन्यथा
			vchan_init(&echan->vchan, s_ddev);

		INIT_LIST_HEAD(&echan->node);
		क्रम (j = 0; j < EDMA_MAX_SLOTS; j++)
			echan->slot[j] = -1;
	पूर्ण
पूर्ण

अटल पूर्णांक edma_setup_from_hw(काष्ठा device *dev, काष्ठा edma_soc_info *pdata,
			      काष्ठा edma_cc *ecc)
अणु
	पूर्णांक i;
	u32 value, cccfg;
	s8 (*queue_priority_map)[2];

	/* Decode the eDMA3 configuration from CCCFG रेजिस्टर */
	cccfg = edma_पढ़ो(ecc, EDMA_CCCFG);

	value = GET_NUM_REGN(cccfg);
	ecc->num_region = BIT(value);

	value = GET_NUM_DMACH(cccfg);
	ecc->num_channels = BIT(value + 1);

	value = GET_NUM_QDMACH(cccfg);
	ecc->num_qchannels = value * 2;

	value = GET_NUM_PAENTRY(cccfg);
	ecc->num_slots = BIT(value + 4);

	value = GET_NUM_EVQUE(cccfg);
	ecc->num_tc = value + 1;

	ecc->chmap_exist = (cccfg & CHMAP_EXIST) ? true : false;

	dev_dbg(dev, "eDMA3 CC HW configuration (cccfg: 0x%08x):\n", cccfg);
	dev_dbg(dev, "num_region: %u\n", ecc->num_region);
	dev_dbg(dev, "num_channels: %u\n", ecc->num_channels);
	dev_dbg(dev, "num_qchannels: %u\n", ecc->num_qchannels);
	dev_dbg(dev, "num_slots: %u\n", ecc->num_slots);
	dev_dbg(dev, "num_tc: %u\n", ecc->num_tc);
	dev_dbg(dev, "chmap_exist: %s\n", ecc->chmap_exist ? "yes" : "no");

	/* Nothing need to be करोne अगर queue priority is provided */
	अगर (pdata->queue_priority_mapping)
		वापस 0;

	/*
	 * Configure TC/queue priority as follows:
	 * Q0 - priority 0
	 * Q1 - priority 1
	 * Q2 - priority 2
	 * ...
	 * The meaning of priority numbers: 0 highest priority, 7 lowest
	 * priority. So Q0 is the highest priority queue and the last queue has
	 * the lowest priority.
	 */
	queue_priority_map = devm_kसुस्मृति(dev, ecc->num_tc + 1, माप(s8),
					  GFP_KERNEL);
	अगर (!queue_priority_map)
		वापस -ENOMEM;

	क्रम (i = 0; i < ecc->num_tc; i++) अणु
		queue_priority_map[i][0] = i;
		queue_priority_map[i][1] = i;
	पूर्ण
	queue_priority_map[i][0] = -1;
	queue_priority_map[i][1] = -1;

	pdata->queue_priority_mapping = queue_priority_map;
	/* Default queue has the lowest priority */
	pdata->शेष_queue = i - 1;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF)
अटल पूर्णांक edma_xbar_event_map(काष्ठा device *dev, काष्ठा edma_soc_info *pdata,
			       माप_प्रकार sz)
अणु
	स्थिर अक्षर pname[] = "ti,edma-xbar-event-map";
	काष्ठा resource res;
	व्योम __iomem *xbar;
	s16 (*xbar_chans)[2];
	माप_प्रकार nelm = sz / माप(s16);
	u32 shअगरt, offset, mux;
	पूर्णांक ret, i;

	xbar_chans = devm_kसुस्मृति(dev, nelm + 2, माप(s16), GFP_KERNEL);
	अगर (!xbar_chans)
		वापस -ENOMEM;

	ret = of_address_to_resource(dev->of_node, 1, &res);
	अगर (ret)
		वापस -ENOMEM;

	xbar = devm_ioremap(dev, res.start, resource_size(&res));
	अगर (!xbar)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u16_array(dev->of_node, pname, (u16 *)xbar_chans,
					 nelm);
	अगर (ret)
		वापस -EIO;

	/* Invalidate last entry क्रम the other user of this mess */
	nelm >>= 1;
	xbar_chans[nelm][0] = -1;
	xbar_chans[nelm][1] = -1;

	क्रम (i = 0; i < nelm; i++) अणु
		shअगरt = (xbar_chans[i][1] & 0x03) << 3;
		offset = xbar_chans[i][1] & 0xfffffffc;
		mux = पढ़ोl(xbar + offset);
		mux &= ~(0xff << shअगरt);
		mux |= xbar_chans[i][0] << shअगरt;
		ग_लिखोl(mux, (xbar + offset));
	पूर्ण

	pdata->xbar_chans = (स्थिर s16 (*)[2]) xbar_chans;
	वापस 0;
पूर्ण

अटल काष्ठा edma_soc_info *edma_setup_info_from_dt(काष्ठा device *dev,
						     bool legacy_mode)
अणु
	काष्ठा edma_soc_info *info;
	काष्ठा property *prop;
	पूर्णांक sz, ret;

	info = devm_kzalloc(dev, माप(काष्ठा edma_soc_info), GFP_KERNEL);
	अगर (!info)
		वापस ERR_PTR(-ENOMEM);

	अगर (legacy_mode) अणु
		prop = of_find_property(dev->of_node, "ti,edma-xbar-event-map",
					&sz);
		अगर (prop) अणु
			ret = edma_xbar_event_map(dev, info, sz);
			अगर (ret)
				वापस ERR_PTR(ret);
		पूर्ण
		वापस info;
	पूर्ण

	/* Get the list of channels allocated to be used क्रम स_नकल */
	prop = of_find_property(dev->of_node, "ti,edma-memcpy-channels", &sz);
	अगर (prop) अणु
		स्थिर अक्षर pname[] = "ti,edma-memcpy-channels";
		माप_प्रकार nelm = sz / माप(s32);
		s32 *स_नकल_ch;

		स_नकल_ch = devm_kसुस्मृति(dev, nelm + 1, माप(s32),
					 GFP_KERNEL);
		अगर (!स_नकल_ch)
			वापस ERR_PTR(-ENOMEM);

		ret = of_property_पढ़ो_u32_array(dev->of_node, pname,
						 (u32 *)स_नकल_ch, nelm);
		अगर (ret)
			वापस ERR_PTR(ret);

		स_नकल_ch[nelm] = -1;
		info->स_नकल_channels = स_नकल_ch;
	पूर्ण

	prop = of_find_property(dev->of_node, "ti,edma-reserved-slot-ranges",
				&sz);
	अगर (prop) अणु
		स्थिर अक्षर pname[] = "ti,edma-reserved-slot-ranges";
		u32 (*पंचांगp)[2];
		s16 (*rsv_slots)[2];
		माप_प्रकार nelm = sz / माप(*पंचांगp);
		काष्ठा edma_rsv_info *rsv_info;
		पूर्णांक i;

		अगर (!nelm)
			वापस info;

		पंचांगp = kसुस्मृति(nelm, माप(*पंचांगp), GFP_KERNEL);
		अगर (!पंचांगp)
			वापस ERR_PTR(-ENOMEM);

		rsv_info = devm_kzalloc(dev, माप(*rsv_info), GFP_KERNEL);
		अगर (!rsv_info) अणु
			kमुक्त(पंचांगp);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		rsv_slots = devm_kसुस्मृति(dev, nelm + 1, माप(*rsv_slots),
					 GFP_KERNEL);
		अगर (!rsv_slots) अणु
			kमुक्त(पंचांगp);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		ret = of_property_पढ़ो_u32_array(dev->of_node, pname,
						 (u32 *)पंचांगp, nelm * 2);
		अगर (ret) अणु
			kमुक्त(पंचांगp);
			वापस ERR_PTR(ret);
		पूर्ण

		क्रम (i = 0; i < nelm; i++) अणु
			rsv_slots[i][0] = पंचांगp[i][0];
			rsv_slots[i][1] = पंचांगp[i][1];
		पूर्ण
		rsv_slots[nelm][0] = -1;
		rsv_slots[nelm][1] = -1;

		info->rsv = rsv_info;
		info->rsv->rsv_slots = (स्थिर s16 (*)[2])rsv_slots;

		kमुक्त(पंचांगp);
	पूर्ण

	वापस info;
पूर्ण

अटल काष्ठा dma_chan *of_edma_xlate(काष्ठा of_phandle_args *dma_spec,
				      काष्ठा of_dma *ofdma)
अणु
	काष्ठा edma_cc *ecc = ofdma->of_dma_data;
	काष्ठा dma_chan *chan = शून्य;
	काष्ठा edma_chan *echan;
	पूर्णांक i;

	अगर (!ecc || dma_spec->args_count < 1)
		वापस शून्य;

	क्रम (i = 0; i < ecc->num_channels; i++) अणु
		echan = &ecc->slave_chans[i];
		अगर (echan->ch_num == dma_spec->args[0]) अणु
			chan = &echan->vchan.chan;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!chan)
		वापस शून्य;

	अगर (echan->ecc->legacy_mode && dma_spec->args_count == 1)
		जाओ out;

	अगर (!echan->ecc->legacy_mode && dma_spec->args_count == 2 &&
	    dma_spec->args[1] < echan->ecc->num_tc) अणु
		echan->tc = &echan->ecc->tc_list[dma_spec->args[1]];
		जाओ out;
	पूर्ण

	वापस शून्य;
out:
	/* The channel is going to be used as HW synchronized */
	echan->hw_triggered = true;
	वापस dma_get_slave_channel(chan);
पूर्ण
#अन्यथा
अटल काष्ठा edma_soc_info *edma_setup_info_from_dt(काष्ठा device *dev,
						     bool legacy_mode)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा dma_chan *of_edma_xlate(काष्ठा of_phandle_args *dma_spec,
				      काष्ठा of_dma *ofdma)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल bool edma_filter_fn(काष्ठा dma_chan *chan, व्योम *param);

अटल पूर्णांक edma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edma_soc_info	*info = pdev->dev.platक्रमm_data;
	s8			(*queue_priority_mapping)[2];
	स्थिर s16		(*reserved)[2];
	पूर्णांक			i, irq;
	अक्षर			*irq_name;
	काष्ठा resource		*mem;
	काष्ठा device_node	*node = pdev->dev.of_node;
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा edma_cc		*ecc;
	bool			legacy_mode = true;
	पूर्णांक ret;

	अगर (node) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(edma_of_ids, node);
		अगर (match && (*(u32 *)match->data) == EDMA_BINDING_TPCC)
			legacy_mode = false;

		info = edma_setup_info_from_dt(dev, legacy_mode);
		अगर (IS_ERR(info)) अणु
			dev_err(dev, "failed to get DT data\n");
			वापस PTR_ERR(info);
		पूर्ण
	पूर्ण

	अगर (!info)
		वापस -ENODEV;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	ecc = devm_kzalloc(dev, माप(*ecc), GFP_KERNEL);
	अगर (!ecc)
		वापस -ENOMEM;

	ecc->dev = dev;
	ecc->id = pdev->id;
	ecc->legacy_mode = legacy_mode;
	/* When booting with DT the pdev->id is -1 */
	अगर (ecc->id < 0)
		ecc->id = 0;

	mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "edma3_cc");
	अगर (!mem) अणु
		dev_dbg(dev, "mem resource not found, using index 0\n");
		mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (!mem) अणु
			dev_err(dev, "no mem resource?\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	ecc->base = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(ecc->base))
		वापस PTR_ERR(ecc->base);

	platक्रमm_set_drvdata(pdev, ecc);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync() failed\n");
		pm_runसमय_disable(dev);
		वापस ret;
	पूर्ण

	/* Get eDMA3 configuration from IP */
	ret = edma_setup_from_hw(dev, info, ecc);
	अगर (ret)
		जाओ err_disable_pm;

	/* Allocate memory based on the inक्रमmation we got from the IP */
	ecc->slave_chans = devm_kसुस्मृति(dev, ecc->num_channels,
					माप(*ecc->slave_chans), GFP_KERNEL);

	ecc->slot_inuse = devm_kसुस्मृति(dev, BITS_TO_LONGS(ecc->num_slots),
				       माप(अचिन्हित दीर्घ), GFP_KERNEL);

	ecc->channels_mask = devm_kसुस्मृति(dev,
					   BITS_TO_LONGS(ecc->num_channels),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!ecc->slave_chans || !ecc->slot_inuse || !ecc->channels_mask) अणु
		ret = -ENOMEM;
		जाओ err_disable_pm;
	पूर्ण

	/* Mark all channels available initially */
	biपंचांगap_fill(ecc->channels_mask, ecc->num_channels);

	ecc->शेष_queue = info->शेष_queue;

	अगर (info->rsv) अणु
		/* Set the reserved slots in inuse list */
		reserved = info->rsv->rsv_slots;
		अगर (reserved) अणु
			क्रम (i = 0; reserved[i][0] != -1; i++)
				biपंचांगap_set(ecc->slot_inuse, reserved[i][0],
					   reserved[i][1]);
		पूर्ण

		/* Clear channels not usable क्रम Linux */
		reserved = info->rsv->rsv_chans;
		अगर (reserved) अणु
			क्रम (i = 0; reserved[i][0] != -1; i++)
				biपंचांगap_clear(ecc->channels_mask, reserved[i][0],
					     reserved[i][1]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ecc->num_slots; i++) अणु
		/* Reset only unused - not reserved - paRAM slots */
		अगर (!test_bit(i, ecc->slot_inuse))
			edma_ग_लिखो_slot(ecc, i, &dummy_paramset);
	पूर्ण

	irq = platक्रमm_get_irq_byname(pdev, "edma3_ccint");
	अगर (irq < 0 && node)
		irq = irq_of_parse_and_map(node, 0);

	अगर (irq >= 0) अणु
		irq_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s_ccint",
					  dev_name(dev));
		ret = devm_request_irq(dev, irq, dma_irq_handler, 0, irq_name,
				       ecc);
		अगर (ret) अणु
			dev_err(dev, "CCINT (%d) failed --> %d\n", irq, ret);
			जाओ err_disable_pm;
		पूर्ण
		ecc->ccपूर्णांक = irq;
	पूर्ण

	irq = platक्रमm_get_irq_byname(pdev, "edma3_ccerrint");
	अगर (irq < 0 && node)
		irq = irq_of_parse_and_map(node, 2);

	अगर (irq >= 0) अणु
		irq_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s_ccerrint",
					  dev_name(dev));
		ret = devm_request_irq(dev, irq, dma_ccerr_handler, 0, irq_name,
				       ecc);
		अगर (ret) अणु
			dev_err(dev, "CCERRINT (%d) failed --> %d\n", irq, ret);
			जाओ err_disable_pm;
		पूर्ण
		ecc->ccerrपूर्णांक = irq;
	पूर्ण

	ecc->dummy_slot = edma_alloc_slot(ecc, EDMA_SLOT_ANY);
	अगर (ecc->dummy_slot < 0) अणु
		dev_err(dev, "Can't allocate PaRAM dummy slot\n");
		ret = ecc->dummy_slot;
		जाओ err_disable_pm;
	पूर्ण

	queue_priority_mapping = info->queue_priority_mapping;

	अगर (!ecc->legacy_mode) अणु
		पूर्णांक lowest_priority = 0;
		अचिन्हित पूर्णांक array_max;
		काष्ठा of_phandle_args tc_args;

		ecc->tc_list = devm_kसुस्मृति(dev, ecc->num_tc,
					    माप(*ecc->tc_list), GFP_KERNEL);
		अगर (!ecc->tc_list) अणु
			ret = -ENOMEM;
			जाओ err_reg1;
		पूर्ण

		क्रम (i = 0;; i++) अणु
			ret = of_parse_phandle_with_fixed_args(node, "ti,tptcs",
							       1, i, &tc_args);
			अगर (ret || i == ecc->num_tc)
				अवरोध;

			ecc->tc_list[i].node = tc_args.np;
			ecc->tc_list[i].id = i;
			queue_priority_mapping[i][1] = tc_args.args[0];
			अगर (queue_priority_mapping[i][1] > lowest_priority) अणु
				lowest_priority = queue_priority_mapping[i][1];
				info->शेष_queue = i;
			पूर्ण
		पूर्ण

		/* See अगर we have optional dma-channel-mask array */
		array_max = DIV_ROUND_UP(ecc->num_channels, BITS_PER_TYPE(u32));
		ret = of_property_पढ़ो_variable_u32_array(node,
						"dma-channel-mask",
						(u32 *)ecc->channels_mask,
						1, array_max);
		अगर (ret > 0 && ret != array_max)
			dev_warn(dev, "dma-channel-mask is not complete.\n");
		अन्यथा अगर (ret == -EOVERFLOW || ret == -ENODATA)
			dev_warn(dev,
				 "dma-channel-mask is out of range or empty\n");
	पूर्ण

	/* Event queue priority mapping */
	क्रम (i = 0; queue_priority_mapping[i][0] != -1; i++)
		edma_assign_priority_to_queue(ecc, queue_priority_mapping[i][0],
					      queue_priority_mapping[i][1]);

	edma_ग_लिखो_array2(ecc, EDMA_DRAE, 0, 0, 0x0);
	edma_ग_लिखो_array2(ecc, EDMA_DRAE, 0, 1, 0x0);
	edma_ग_लिखो_array(ecc, EDMA_QRAE, 0, 0x0);

	ecc->info = info;

	/* Init the dma device and channels */
	edma_dma_init(ecc, legacy_mode);

	क्रम (i = 0; i < ecc->num_channels; i++) अणु
		/* Do not touch reserved channels */
		अगर (!test_bit(i, ecc->channels_mask))
			जारी;

		/* Assign all channels to the शेष queue */
		edma_assign_channel_eventq(&ecc->slave_chans[i],
					   info->शेष_queue);
		/* Set entry slot to the dummy slot */
		edma_set_chmap(&ecc->slave_chans[i], ecc->dummy_slot);
	पूर्ण

	ecc->dma_slave.filter.map = info->slave_map;
	ecc->dma_slave.filter.mapcnt = info->slavecnt;
	ecc->dma_slave.filter.fn = edma_filter_fn;

	ret = dma_async_device_रेजिस्टर(&ecc->dma_slave);
	अगर (ret) अणु
		dev_err(dev, "slave ddev registration failed (%d)\n", ret);
		जाओ err_reg1;
	पूर्ण

	अगर (ecc->dma_स_नकल) अणु
		ret = dma_async_device_रेजिस्टर(ecc->dma_स_नकल);
		अगर (ret) अणु
			dev_err(dev, "memcpy ddev registration failed (%d)\n",
				ret);
			dma_async_device_unरेजिस्टर(&ecc->dma_slave);
			जाओ err_reg1;
		पूर्ण
	पूर्ण

	अगर (node)
		of_dma_controller_रेजिस्टर(node, of_edma_xlate, ecc);

	dev_info(dev, "TI EDMA DMA engine driver\n");

	वापस 0;

err_reg1:
	edma_मुक्त_slot(ecc, ecc->dummy_slot);
err_disable_pm:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल व्योम edma_cleanupp_vchan(काष्ठा dma_device *dmadev)
अणु
	काष्ठा edma_chan *echan, *_echan;

	list_क्रम_each_entry_safe(echan, _echan,
			&dmadev->channels, vchan.chan.device_node) अणु
		list_del(&echan->vchan.chan.device_node);
		tasklet_समाप्त(&echan->vchan.task);
	पूर्ण
पूर्ण

अटल पूर्णांक edma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा edma_cc *ecc = dev_get_drvdata(dev);

	devm_मुक्त_irq(dev, ecc->ccपूर्णांक, ecc);
	devm_मुक्त_irq(dev, ecc->ccerrपूर्णांक, ecc);

	edma_cleanupp_vchan(&ecc->dma_slave);

	अगर (dev->of_node)
		of_dma_controller_मुक्त(dev->of_node);
	dma_async_device_unरेजिस्टर(&ecc->dma_slave);
	अगर (ecc->dma_स_नकल)
		dma_async_device_unरेजिस्टर(ecc->dma_स_नकल);
	edma_मुक्त_slot(ecc, ecc->dummy_slot);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक edma_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा edma_cc *ecc = dev_get_drvdata(dev);
	काष्ठा edma_chan *echan = ecc->slave_chans;
	पूर्णांक i;

	क्रम (i = 0; i < ecc->num_channels; i++) अणु
		अगर (echan[i].alloced)
			edma_setup_पूर्णांकerrupt(&echan[i], false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक edma_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा edma_cc *ecc = dev_get_drvdata(dev);
	काष्ठा edma_chan *echan = ecc->slave_chans;
	पूर्णांक i;
	s8 (*queue_priority_mapping)[2];

	/* re initialize dummy slot to dummy param set */
	edma_ग_लिखो_slot(ecc, ecc->dummy_slot, &dummy_paramset);

	queue_priority_mapping = ecc->info->queue_priority_mapping;

	/* Event queue priority mapping */
	क्रम (i = 0; queue_priority_mapping[i][0] != -1; i++)
		edma_assign_priority_to_queue(ecc, queue_priority_mapping[i][0],
					      queue_priority_mapping[i][1]);

	क्रम (i = 0; i < ecc->num_channels; i++) अणु
		अगर (echan[i].alloced) अणु
			/* ensure access through shaकरोw region 0 */
			edma_or_array2(ecc, EDMA_DRAE, 0,
				       EDMA_REG_ARRAY_INDEX(i),
				       EDMA_CHANNEL_BIT(i));

			edma_setup_पूर्णांकerrupt(&echan[i], true);

			/* Set up channel -> slot mapping क्रम the entry slot */
			edma_set_chmap(&echan[i], echan[i].slot[0]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops edma_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(edma_pm_suspend, edma_pm_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver edma_driver = अणु
	.probe		= edma_probe,
	.हटाओ		= edma_हटाओ,
	.driver = अणु
		.name	= "edma",
		.pm	= &edma_pm_ops,
		.of_match_table = edma_of_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक edma_tptc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_enable(&pdev->dev);
	वापस pm_runसमय_get_sync(&pdev->dev);
पूर्ण

अटल काष्ठा platक्रमm_driver edma_tptc_driver = अणु
	.probe		= edma_tptc_probe,
	.driver = अणु
		.name	= "edma3-tptc",
		.of_match_table = edma_tptc_of_ids,
	पूर्ण,
पूर्ण;

अटल bool edma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	bool match = false;

	अगर (chan->device->dev->driver == &edma_driver.driver) अणु
		काष्ठा edma_chan *echan = to_edma_chan(chan);
		अचिन्हित ch_req = *(अचिन्हित *)param;
		अगर (ch_req == echan->ch_num) अणु
			/* The channel is going to be used as HW synchronized */
			echan->hw_triggered = true;
			match = true;
		पूर्ण
	पूर्ण
	वापस match;
पूर्ण

अटल पूर्णांक edma_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&edma_tptc_driver);
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&edma_driver);
पूर्ण
subsys_initcall(edma_init);

अटल व्योम __निकास edma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&edma_driver);
	platक्रमm_driver_unरेजिस्टर(&edma_tptc_driver);
पूर्ण
module_निकास(edma_निकास);

MODULE_AUTHOR("Matt Porter <matt.porter@linaro.org>");
MODULE_DESCRIPTION("TI EDMA DMA engine driver");
MODULE_LICENSE("GPL v2");
