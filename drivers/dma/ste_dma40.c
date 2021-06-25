<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Ericsson AB 2007-2008
 * Copyright (C) ST-Ericsson SA 2008-2010
 * Author: Per Forlin <per.क्रमlin@stericsson.com> क्रम ST-Ericsson
 * Author: Jonas Aaberg <jonas.aberg@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/platक्रमm_data/dma-ste-dma40.h>

#समावेश "dmaengine.h"
#समावेश "ste_dma40_ll.h"

#घोषणा D40_NAME "dma40"

#घोषणा D40_PHY_CHAN -1

/* For masking out/in 2 bit channel positions */
#घोषणा D40_CHAN_POS(chan)  (2 * (chan / 2))
#घोषणा D40_CHAN_POS_MASK(chan) (0x3 << D40_CHAN_POS(chan))

/* Maximum iterations taken beक्रमe giving up suspending a channel */
#घोषणा D40_SUSPEND_MAX_IT 500

/* Milliseconds */
#घोषणा DMA40_AUTOSUSPEND_DELAY	100

/* Hardware requirement on LCLA alignment */
#घोषणा LCLA_ALIGNMENT 0x40000

/* Max number of links per event group */
#घोषणा D40_LCLA_LINK_PER_EVENT_GRP 128
#घोषणा D40_LCLA_END D40_LCLA_LINK_PER_EVENT_GRP

/* Max number of logical channels per physical channel */
#घोषणा D40_MAX_LOG_CHAN_PER_PHY 32

/* Attempts beक्रमe giving up to trying to get pages that are aligned */
#घोषणा MAX_LCLA_ALLOC_ATTEMPTS 256

/* Bit markings क्रम allocation map */
#घोषणा D40_ALLOC_FREE		BIT(31)
#घोषणा D40_ALLOC_PHY		BIT(30)
#घोषणा D40_ALLOC_LOG_FREE	0

#घोषणा D40_MEMCPY_MAX_CHANS	8

/* Reserved event lines क्रम स_नकल only. */
#घोषणा DB8500_DMA_MEMCPY_EV_0	51
#घोषणा DB8500_DMA_MEMCPY_EV_1	56
#घोषणा DB8500_DMA_MEMCPY_EV_2	57
#घोषणा DB8500_DMA_MEMCPY_EV_3	58
#घोषणा DB8500_DMA_MEMCPY_EV_4	59
#घोषणा DB8500_DMA_MEMCPY_EV_5	60

अटल पूर्णांक dma40_स_नकल_channels[] = अणु
	DB8500_DMA_MEMCPY_EV_0,
	DB8500_DMA_MEMCPY_EV_1,
	DB8500_DMA_MEMCPY_EV_2,
	DB8500_DMA_MEMCPY_EV_3,
	DB8500_DMA_MEMCPY_EV_4,
	DB8500_DMA_MEMCPY_EV_5,
पूर्ण;

/* Default configuration क्रम physical स_नकल */
अटल स्थिर काष्ठा stedma40_chan_cfg dma40_स_नकल_conf_phy = अणु
	.mode = STEDMA40_MODE_PHYSICAL,
	.dir = DMA_MEM_TO_MEM,

	.src_info.data_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
	.src_info.psize = STEDMA40_PSIZE_PHY_1,
	.src_info.flow_ctrl = STEDMA40_NO_FLOW_CTRL,

	.dst_info.data_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
	.dst_info.psize = STEDMA40_PSIZE_PHY_1,
	.dst_info.flow_ctrl = STEDMA40_NO_FLOW_CTRL,
पूर्ण;

/* Default configuration क्रम logical स_नकल */
अटल स्थिर काष्ठा stedma40_chan_cfg dma40_स_नकल_conf_log = अणु
	.mode = STEDMA40_MODE_LOGICAL,
	.dir = DMA_MEM_TO_MEM,

	.src_info.data_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
	.src_info.psize = STEDMA40_PSIZE_LOG_1,
	.src_info.flow_ctrl = STEDMA40_NO_FLOW_CTRL,

	.dst_info.data_width = DMA_SLAVE_BUSWIDTH_1_BYTE,
	.dst_info.psize = STEDMA40_PSIZE_LOG_1,
	.dst_info.flow_ctrl = STEDMA40_NO_FLOW_CTRL,
पूर्ण;

/**
 * क्रमागत 40_command - The dअगरferent commands and/or statuses.
 *
 * @D40_DMA_STOP: DMA channel command STOP or status STOPPED,
 * @D40_DMA_RUN: The DMA channel is RUNNING of the command RUN.
 * @D40_DMA_SUSPEND_REQ: Request the DMA to SUSPEND as soon as possible.
 * @D40_DMA_SUSPENDED: The DMA channel is SUSPENDED.
 */
क्रमागत d40_command अणु
	D40_DMA_STOP		= 0,
	D40_DMA_RUN		= 1,
	D40_DMA_SUSPEND_REQ	= 2,
	D40_DMA_SUSPENDED	= 3
पूर्ण;

/*
 * क्रमागत d40_events - The dअगरferent Event Enables क्रम the event lines.
 *
 * @D40_DEACTIVATE_EVENTLINE: De-activate Event line, stopping the logical chan.
 * @D40_ACTIVATE_EVENTLINE: Activate the Event line, to start a logical chan.
 * @D40_SUSPEND_REQ_EVENTLINE: Requesting क्रम suspending a event line.
 * @D40_ROUND_EVENTLINE: Status check क्रम event line.
 */

क्रमागत d40_events अणु
	D40_DEACTIVATE_EVENTLINE	= 0,
	D40_ACTIVATE_EVENTLINE		= 1,
	D40_SUSPEND_REQ_EVENTLINE	= 2,
	D40_ROUND_EVENTLINE		= 3
पूर्ण;

/*
 * These are the रेजिस्टरs that has to be saved and later restored
 * when the DMA hw is घातered off.
 * TODO: Add save/restore of D40_DREG_GCC on dma40 v3 or later, अगर that works.
 */
अटल __maybe_unused u32 d40_backup_regs[] = अणु
	D40_DREG_LCPA,
	D40_DREG_LCLA,
	D40_DREG_PRMSE,
	D40_DREG_PRMSO,
	D40_DREG_PRMOE,
	D40_DREG_PRMOO,
पूर्ण;

#घोषणा BACKUP_REGS_SZ ARRAY_SIZE(d40_backup_regs)

/*
 * since 9540 and 8540 has the same HW revision
 * use v4a क्रम 9540 or ealier
 * use v4b क्रम 8540 or later
 * HW revision:
 * DB8500ed has revision 0
 * DB8500v1 has revision 2
 * DB8500v2 has revision 3
 * AP9540v1 has revision 4
 * DB8540v1 has revision 4
 * TODO: Check अगर all these रेजिस्टरs have to be saved/restored on dma40 v4a
 */
अटल u32 d40_backup_regs_v4a[] = अणु
	D40_DREG_PSEG1,
	D40_DREG_PSEG2,
	D40_DREG_PSEG3,
	D40_DREG_PSEG4,
	D40_DREG_PCEG1,
	D40_DREG_PCEG2,
	D40_DREG_PCEG3,
	D40_DREG_PCEG4,
	D40_DREG_RSEG1,
	D40_DREG_RSEG2,
	D40_DREG_RSEG3,
	D40_DREG_RSEG4,
	D40_DREG_RCEG1,
	D40_DREG_RCEG2,
	D40_DREG_RCEG3,
	D40_DREG_RCEG4,
पूर्ण;

#घोषणा BACKUP_REGS_SZ_V4A ARRAY_SIZE(d40_backup_regs_v4a)

अटल u32 d40_backup_regs_v4b[] = अणु
	D40_DREG_CPSEG1,
	D40_DREG_CPSEG2,
	D40_DREG_CPSEG3,
	D40_DREG_CPSEG4,
	D40_DREG_CPSEG5,
	D40_DREG_CPCEG1,
	D40_DREG_CPCEG2,
	D40_DREG_CPCEG3,
	D40_DREG_CPCEG4,
	D40_DREG_CPCEG5,
	D40_DREG_CRSEG1,
	D40_DREG_CRSEG2,
	D40_DREG_CRSEG3,
	D40_DREG_CRSEG4,
	D40_DREG_CRSEG5,
	D40_DREG_CRCEG1,
	D40_DREG_CRCEG2,
	D40_DREG_CRCEG3,
	D40_DREG_CRCEG4,
	D40_DREG_CRCEG5,
पूर्ण;

#घोषणा BACKUP_REGS_SZ_V4B ARRAY_SIZE(d40_backup_regs_v4b)

अटल __maybe_unused u32 d40_backup_regs_chan[] = अणु
	D40_CHAN_REG_SSCFG,
	D40_CHAN_REG_SSELT,
	D40_CHAN_REG_SSPTR,
	D40_CHAN_REG_SSLNK,
	D40_CHAN_REG_SDCFG,
	D40_CHAN_REG_SDELT,
	D40_CHAN_REG_SDPTR,
	D40_CHAN_REG_SDLNK,
पूर्ण;

#घोषणा BACKUP_REGS_SZ_MAX ((BACKUP_REGS_SZ_V4A > BACKUP_REGS_SZ_V4B) ? \
			     BACKUP_REGS_SZ_V4A : BACKUP_REGS_SZ_V4B)

/**
 * काष्ठा d40_पूर्णांकerrupt_lookup - lookup table क्रम पूर्णांकerrupt handler
 *
 * @src: Interrupt mask रेजिस्टर.
 * @clr: Interrupt clear रेजिस्टर.
 * @is_error: true अगर this is an error पूर्णांकerrupt.
 * @offset: start delta in the lookup_log_chans in d40_base. If equals to
 * D40_PHY_CHAN, the lookup_phy_chans shall be used instead.
 */
काष्ठा d40_पूर्णांकerrupt_lookup अणु
	u32 src;
	u32 clr;
	bool is_error;
	पूर्णांक offset;
पूर्ण;


अटल काष्ठा d40_पूर्णांकerrupt_lookup il_v4a[] = अणु
	अणुD40_DREG_LCTIS0, D40_DREG_LCICR0, false,  0पूर्ण,
	अणुD40_DREG_LCTIS1, D40_DREG_LCICR1, false, 32पूर्ण,
	अणुD40_DREG_LCTIS2, D40_DREG_LCICR2, false, 64पूर्ण,
	अणुD40_DREG_LCTIS3, D40_DREG_LCICR3, false, 96पूर्ण,
	अणुD40_DREG_LCEIS0, D40_DREG_LCICR0, true,   0पूर्ण,
	अणुD40_DREG_LCEIS1, D40_DREG_LCICR1, true,  32पूर्ण,
	अणुD40_DREG_LCEIS2, D40_DREG_LCICR2, true,  64पूर्ण,
	अणुD40_DREG_LCEIS3, D40_DREG_LCICR3, true,  96पूर्ण,
	अणुD40_DREG_PCTIS,  D40_DREG_PCICR,  false, D40_PHY_CHANपूर्ण,
	अणुD40_DREG_PCEIS,  D40_DREG_PCICR,  true,  D40_PHY_CHANपूर्ण,
पूर्ण;

अटल काष्ठा d40_पूर्णांकerrupt_lookup il_v4b[] = अणु
	अणुD40_DREG_CLCTIS1, D40_DREG_CLCICR1, false,  0पूर्ण,
	अणुD40_DREG_CLCTIS2, D40_DREG_CLCICR2, false, 32पूर्ण,
	अणुD40_DREG_CLCTIS3, D40_DREG_CLCICR3, false, 64पूर्ण,
	अणुD40_DREG_CLCTIS4, D40_DREG_CLCICR4, false, 96पूर्ण,
	अणुD40_DREG_CLCTIS5, D40_DREG_CLCICR5, false, 128पूर्ण,
	अणुD40_DREG_CLCEIS1, D40_DREG_CLCICR1, true,   0पूर्ण,
	अणुD40_DREG_CLCEIS2, D40_DREG_CLCICR2, true,  32पूर्ण,
	अणुD40_DREG_CLCEIS3, D40_DREG_CLCICR3, true,  64पूर्ण,
	अणुD40_DREG_CLCEIS4, D40_DREG_CLCICR4, true,  96पूर्ण,
	अणुD40_DREG_CLCEIS5, D40_DREG_CLCICR5, true,  128पूर्ण,
	अणुD40_DREG_CPCTIS,  D40_DREG_CPCICR,  false, D40_PHY_CHANपूर्ण,
	अणुD40_DREG_CPCEIS,  D40_DREG_CPCICR,  true,  D40_PHY_CHANपूर्ण,
पूर्ण;

/**
 * काष्ठा d40_reg_val - simple lookup काष्ठा
 *
 * @reg: The रेजिस्टर.
 * @val: The value that beदीर्घs to the रेजिस्टर in reg.
 */
काष्ठा d40_reg_val अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक val;
पूर्ण;

अटल __initdata काष्ठा d40_reg_val dma_init_reg_v4a[] = अणु
	/* Clock every part of the DMA block from start */
	अणु .reg = D40_DREG_GCC,    .val = D40_DREG_GCC_ENABLE_ALLपूर्ण,

	/* Interrupts on all logical channels */
	अणु .reg = D40_DREG_LCMIS0, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCMIS1, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCMIS2, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCMIS3, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCICR0, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCICR1, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCICR2, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCICR3, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCTIS0, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCTIS1, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCTIS2, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_LCTIS3, .val = 0xFFFFFFFFपूर्ण
पूर्ण;
अटल __initdata काष्ठा d40_reg_val dma_init_reg_v4b[] = अणु
	/* Clock every part of the DMA block from start */
	अणु .reg = D40_DREG_GCC,    .val = D40_DREG_GCC_ENABLE_ALLपूर्ण,

	/* Interrupts on all logical channels */
	अणु .reg = D40_DREG_CLCMIS1, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCMIS2, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCMIS3, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCMIS4, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCMIS5, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCICR1, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCICR2, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCICR3, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCICR4, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCICR5, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCTIS1, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCTIS2, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCTIS3, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCTIS4, .val = 0xFFFFFFFFपूर्ण,
	अणु .reg = D40_DREG_CLCTIS5, .val = 0xFFFFFFFFपूर्ण
पूर्ण;

/**
 * काष्ठा d40_lli_pool - Structure क्रम keeping LLIs in memory
 *
 * @base: Poपूर्णांकer to memory area when the pre_alloc_lli's are not large
 * enough, IE bigger than the most common हाल, 1 dst and 1 src. शून्य अगर
 * pre_alloc_lli is used.
 * @dma_addr: DMA address, अगर mapped
 * @size: The size in bytes of the memory at base or the size of pre_alloc_lli.
 * @pre_alloc_lli: Pre allocated area क्रम the most common हाल of transfers,
 * one buffer to one buffer.
 */
काष्ठा d40_lli_pool अणु
	व्योम	*base;
	पूर्णांक	 size;
	dma_addr_t	dma_addr;
	/* Space क्रम dst and src, plus an extra क्रम padding */
	u8	 pre_alloc_lli[3 * माप(काष्ठा d40_phy_lli)];
पूर्ण;

/**
 * काष्ठा d40_desc - A descriptor is one DMA job.
 *
 * @lli_phy: LLI settings क्रम physical channel. Both src and dst=
 * poपूर्णांकs पूर्णांकo the lli_pool, to base अगर lli_len > 1 or to pre_alloc_lli अगर
 * lli_len equals one.
 * @lli_log: Same as above but क्रम logical channels.
 * @lli_pool: The pool with two entries pre-allocated.
 * @lli_len: Number of llis of current descriptor.
 * @lli_current: Number of transferred llis.
 * @lcla_alloc: Number of LCLA entries allocated.
 * @txd: DMA engine काष्ठा. Used क्रम among other things क्रम communication
 * during a transfer.
 * @node: List entry.
 * @is_in_client_list: true अगर the client owns this descriptor.
 * @cyclic: true अगर this is a cyclic job
 *
 * This descriptor is used क्रम both logical and physical transfers.
 */
काष्ठा d40_desc अणु
	/* LLI physical */
	काष्ठा d40_phy_lli_bidir	 lli_phy;
	/* LLI logical */
	काष्ठा d40_log_lli_bidir	 lli_log;

	काष्ठा d40_lli_pool		 lli_pool;
	पूर्णांक				 lli_len;
	पूर्णांक				 lli_current;
	पूर्णांक				 lcla_alloc;

	काष्ठा dma_async_tx_descriptor	 txd;
	काष्ठा list_head		 node;

	bool				 is_in_client_list;
	bool				 cyclic;
पूर्ण;

/**
 * काष्ठा d40_lcla_pool - LCLA pool settings and data.
 *
 * @base: The भव address of LCLA. 18 bit aligned.
 * @dma_addr: DMA address, अगर mapped
 * @base_unaligned: The orignal kदो_स्मृति poपूर्णांकer, अगर kदो_स्मृति is used.
 * This poपूर्णांकer is only there क्रम clean-up on error.
 * @pages: The number of pages needed क्रम all physical channels.
 * Only used later क्रम clean-up on error
 * @lock: Lock to protect the content in this काष्ठा.
 * @alloc_map: big map over which LCLA entry is own by which job.
 */
काष्ठा d40_lcla_pool अणु
	व्योम		*base;
	dma_addr_t	dma_addr;
	व्योम		*base_unaligned;
	पूर्णांक		 pages;
	spinlock_t	 lock;
	काष्ठा d40_desc	**alloc_map;
पूर्ण;

/**
 * काष्ठा d40_phy_res - काष्ठा क्रम handling eventlines mapped to physical
 * channels.
 *
 * @lock: A lock protection this entity.
 * @reserved: True अगर used by secure world or otherwise.
 * @num: The physical channel number of this entity.
 * @allocated_src: Bit mapped to show which src event line's are mapped to
 * this physical channel. Can also be मुक्त or physically allocated.
 * @allocated_dst: Same as क्रम src but is dst.
 * allocated_dst and allocated_src uses the D40_ALLOC* defines as well as
 * event line number.
 * @use_soft_lli: To mark अगर the linked lists of channel are managed by SW.
 */
काष्ठा d40_phy_res अणु
	spinlock_t lock;
	bool	   reserved;
	पूर्णांक	   num;
	u32	   allocated_src;
	u32	   allocated_dst;
	bool	   use_soft_lli;
पूर्ण;

काष्ठा d40_base;

/**
 * काष्ठा d40_chan - Struct that describes a channel.
 *
 * @lock: A spinlock to protect this काष्ठा.
 * @log_num: The logical number, अगर any of this channel.
 * @pending_tx: The number of pending transfers. Used between पूर्णांकerrupt handler
 * and tasklet.
 * @busy: Set to true when transfer is ongoing on this channel.
 * @phy_chan: Poपूर्णांकer to physical channel which this instance runs on. If this
 * poपूर्णांक is शून्य, then the channel is not allocated.
 * @chan: DMA engine handle.
 * @tasklet: Tasklet that माला_लो scheduled from पूर्णांकerrupt context to complete a
 * transfer and call client callback.
 * @client: Cliented owned descriptor list.
 * @pending_queue: Submitted jobs, to be issued by issue_pending()
 * @active: Active descriptor.
 * @करोne: Completed jobs
 * @queue: Queued jobs.
 * @prepare_queue: Prepared jobs.
 * @dma_cfg: The client configuration of this dma channel.
 * @slave_config: DMA slave configuration.
 * @configured: whether the dma_cfg configuration is valid
 * @base: Poपूर्णांकer to the device instance काष्ठा.
 * @src_def_cfg: Default cfg रेजिस्टर setting क्रम src.
 * @dst_def_cfg: Default cfg रेजिस्टर setting क्रम dst.
 * @log_def: Default logical channel settings.
 * @lcpa: Poपूर्णांकer to dst and src lcpa settings.
 * @runसमय_addr: runसमय configured address.
 * @runसमय_direction: runसमय configured direction.
 *
 * This काष्ठा can either "be" a logical or a physical channel.
 */
काष्ठा d40_chan अणु
	spinlock_t			 lock;
	पूर्णांक				 log_num;
	पूर्णांक				 pending_tx;
	bool				 busy;
	काष्ठा d40_phy_res		*phy_chan;
	काष्ठा dma_chan			 chan;
	काष्ठा tasklet_काष्ठा		 tasklet;
	काष्ठा list_head		 client;
	काष्ठा list_head		 pending_queue;
	काष्ठा list_head		 active;
	काष्ठा list_head		 करोne;
	काष्ठा list_head		 queue;
	काष्ठा list_head		 prepare_queue;
	काष्ठा stedma40_chan_cfg	 dma_cfg;
	काष्ठा dma_slave_config		 slave_config;
	bool				 configured;
	काष्ठा d40_base			*base;
	/* Default रेजिस्टर configurations */
	u32				 src_def_cfg;
	u32				 dst_def_cfg;
	काष्ठा d40_def_lcsp		 log_def;
	काष्ठा d40_log_lli_full		*lcpa;
	/* Runसमय reconfiguration */
	dma_addr_t			runसमय_addr;
	क्रमागत dma_transfer_direction	runसमय_direction;
पूर्ण;

/**
 * काष्ठा d40_gen_dmac - generic values to represent u8500/u8540 DMA
 * controller
 *
 * @backup: the poपूर्णांकer to the रेजिस्टरs address array क्रम backup
 * @backup_size: the size of the रेजिस्टरs address array क्रम backup
 * @realसमय_en: the realसमय enable रेजिस्टर
 * @realसमय_clear: the realसमय clear रेजिस्टर
 * @high_prio_en: the high priority enable रेजिस्टर
 * @high_prio_clear: the high priority clear रेजिस्टर
 * @पूर्णांकerrupt_en: the पूर्णांकerrupt enable रेजिस्टर
 * @पूर्णांकerrupt_clear: the पूर्णांकerrupt clear रेजिस्टर
 * @il: the poपूर्णांकer to काष्ठा d40_पूर्णांकerrupt_lookup
 * @il_size: the size of d40_पूर्णांकerrupt_lookup array
 * @init_reg: the poपूर्णांकer to the काष्ठा d40_reg_val
 * @init_reg_size: the size of d40_reg_val array
 */
काष्ठा d40_gen_dmac अणु
	u32				*backup;
	u32				 backup_size;
	u32				 realसमय_en;
	u32				 realसमय_clear;
	u32				 high_prio_en;
	u32				 high_prio_clear;
	u32				 पूर्णांकerrupt_en;
	u32				 पूर्णांकerrupt_clear;
	काष्ठा d40_पूर्णांकerrupt_lookup	*il;
	u32				 il_size;
	काष्ठा d40_reg_val		*init_reg;
	u32				 init_reg_size;
पूर्ण;

/**
 * काष्ठा d40_base - The big global काष्ठा, one क्रम each probe'd instance.
 *
 * @पूर्णांकerrupt_lock: Lock used to make sure one पूर्णांकerrupt is handle a समय.
 * @execmd_lock: Lock क्रम execute command usage since several channels share
 * the same physical रेजिस्टर.
 * @dev: The device काष्ठाure.
 * @virtbase: The भव base address of the DMA's रेजिस्टर.
 * @rev: silicon revision detected.
 * @clk: Poपूर्णांकer to the DMA घड़ी काष्ठाure.
 * @phy_start: Physical memory start of the DMA रेजिस्टरs.
 * @phy_size: Size of the DMA रेजिस्टर map.
 * @irq: The IRQ number.
 * @num_स_नकल_chans: The number of channels used क्रम स_नकल (mem-to-mem
 * transfers).
 * @num_phy_chans: The number of physical channels. Read from HW. This
 * is the number of available channels क्रम this driver, not counting "Secure
 * mode" allocated physical channels.
 * @num_log_chans: The number of logical channels. Calculated from
 * num_phy_chans.
 * @dma_both: dma_device channels that can करो both स_नकल and slave transfers.
 * @dma_slave: dma_device channels that can करो only करो slave transfers.
 * @dma_स_नकल: dma_device channels that can करो only करो स_नकल transfers.
 * @phy_chans: Room क्रम all possible physical channels in प्रणाली.
 * @log_chans: Room क्रम all possible logical channels in प्रणाली.
 * @lookup_log_chans: Used to map पूर्णांकerrupt number to logical channel. Poपूर्णांकs
 * to log_chans entries.
 * @lookup_phy_chans: Used to map पूर्णांकerrupt number to physical channel. Poपूर्णांकs
 * to phy_chans entries.
 * @plat_data: Poपूर्णांकer to provided platक्रमm_data which is the driver
 * configuration.
 * @lcpa_regulator: Poपूर्णांकer to hold the regulator क्रम the esram bank क्रम lcla.
 * @phy_res: Vector containing all physical channels.
 * @lcla_pool: lcla pool settings and data.
 * @lcpa_base: The भव mapped address of LCPA.
 * @phy_lcpa: The physical address of the LCPA.
 * @lcpa_size: The size of the LCPA area.
 * @desc_slab: cache क्रम descriptors.
 * @reg_val_backup: Here the values of some hardware रेजिस्टरs are stored
 * beक्रमe the DMA is घातered off. They are restored when the घातer is back on.
 * @reg_val_backup_v4: Backup of रेजिस्टरs that only निकासs on dma40 v3 and
 * later
 * @reg_val_backup_chan: Backup data क्रम standard channel parameter रेजिस्टरs.
 * @regs_पूर्णांकerrupt: Scratch space क्रम रेजिस्टरs during पूर्णांकerrupt.
 * @gcc_pwr_off_mask: Mask to मुख्यtain the channels that can be turned off.
 * @gen_dmac: the काष्ठा क्रम generic रेजिस्टरs values to represent u8500/8540
 * DMA controller
 */
काष्ठा d40_base अणु
	spinlock_t			 पूर्णांकerrupt_lock;
	spinlock_t			 execmd_lock;
	काष्ठा device			 *dev;
	व्योम __iomem			 *virtbase;
	u8				  rev:4;
	काष्ठा clk			 *clk;
	phys_addr_t			  phy_start;
	resource_माप_प्रकार			  phy_size;
	पूर्णांक				  irq;
	पूर्णांक				  num_स_नकल_chans;
	पूर्णांक				  num_phy_chans;
	पूर्णांक				  num_log_chans;
	काष्ठा dma_device		  dma_both;
	काष्ठा dma_device		  dma_slave;
	काष्ठा dma_device		  dma_स_नकल;
	काष्ठा d40_chan			 *phy_chans;
	काष्ठा d40_chan			 *log_chans;
	काष्ठा d40_chan			**lookup_log_chans;
	काष्ठा d40_chan			**lookup_phy_chans;
	काष्ठा stedma40_platक्रमm_data	 *plat_data;
	काष्ठा regulator		 *lcpa_regulator;
	/* Physical half channels */
	काष्ठा d40_phy_res		 *phy_res;
	काष्ठा d40_lcla_pool		  lcla_pool;
	व्योम				 *lcpa_base;
	dma_addr_t			  phy_lcpa;
	resource_माप_प्रकार			  lcpa_size;
	काष्ठा kmem_cache		 *desc_slab;
	u32				  reg_val_backup[BACKUP_REGS_SZ];
	u32				  reg_val_backup_v4[BACKUP_REGS_SZ_MAX];
	u32				 *reg_val_backup_chan;
	u32				 *regs_पूर्णांकerrupt;
	u16				  gcc_pwr_off_mask;
	काष्ठा d40_gen_dmac		  gen_dmac;
पूर्ण;

अटल काष्ठा device *chan2dev(काष्ठा d40_chan *d40c)
अणु
	वापस &d40c->chan.dev->device;
पूर्ण

अटल bool chan_is_physical(काष्ठा d40_chan *chan)
अणु
	वापस chan->log_num == D40_PHY_CHAN;
पूर्ण

अटल bool chan_is_logical(काष्ठा d40_chan *chan)
अणु
	वापस !chan_is_physical(chan);
पूर्ण

अटल व्योम __iomem *chan_base(काष्ठा d40_chan *chan)
अणु
	वापस chan->base->virtbase + D40_DREG_PCBASE +
	       chan->phy_chan->num * D40_DREG_PCDELTA;
पूर्ण

#घोषणा d40_err(dev, क्रमmat, arg...)		\
	dev_err(dev, "[%s] " क्रमmat, __func__, ## arg)

#घोषणा chan_err(d40c, क्रमmat, arg...)		\
	d40_err(chan2dev(d40c), क्रमmat, ## arg)

अटल पूर्णांक d40_set_runसमय_config_ग_लिखो(काष्ठा dma_chan *chan,
				  काष्ठा dma_slave_config *config,
				  क्रमागत dma_transfer_direction direction);

अटल पूर्णांक d40_pool_lli_alloc(काष्ठा d40_chan *d40c, काष्ठा d40_desc *d40d,
			      पूर्णांक lli_len)
अणु
	bool is_log = chan_is_logical(d40c);
	u32 align;
	व्योम *base;

	अगर (is_log)
		align = माप(काष्ठा d40_log_lli);
	अन्यथा
		align = माप(काष्ठा d40_phy_lli);

	अगर (lli_len == 1) अणु
		base = d40d->lli_pool.pre_alloc_lli;
		d40d->lli_pool.size = माप(d40d->lli_pool.pre_alloc_lli);
		d40d->lli_pool.base = शून्य;
	पूर्ण अन्यथा अणु
		d40d->lli_pool.size = lli_len * 2 * align;

		base = kदो_स्मृति(d40d->lli_pool.size + align, GFP_NOWAIT);
		d40d->lli_pool.base = base;

		अगर (d40d->lli_pool.base == शून्य)
			वापस -ENOMEM;
	पूर्ण

	अगर (is_log) अणु
		d40d->lli_log.src = PTR_ALIGN(base, align);
		d40d->lli_log.dst = d40d->lli_log.src + lli_len;

		d40d->lli_pool.dma_addr = 0;
	पूर्ण अन्यथा अणु
		d40d->lli_phy.src = PTR_ALIGN(base, align);
		d40d->lli_phy.dst = d40d->lli_phy.src + lli_len;

		d40d->lli_pool.dma_addr = dma_map_single(d40c->base->dev,
							 d40d->lli_phy.src,
							 d40d->lli_pool.size,
							 DMA_TO_DEVICE);

		अगर (dma_mapping_error(d40c->base->dev,
				      d40d->lli_pool.dma_addr)) अणु
			kमुक्त(d40d->lli_pool.base);
			d40d->lli_pool.base = शून्य;
			d40d->lli_pool.dma_addr = 0;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम d40_pool_lli_मुक्त(काष्ठा d40_chan *d40c, काष्ठा d40_desc *d40d)
अणु
	अगर (d40d->lli_pool.dma_addr)
		dma_unmap_single(d40c->base->dev, d40d->lli_pool.dma_addr,
				 d40d->lli_pool.size, DMA_TO_DEVICE);

	kमुक्त(d40d->lli_pool.base);
	d40d->lli_pool.base = शून्य;
	d40d->lli_pool.size = 0;
	d40d->lli_log.src = शून्य;
	d40d->lli_log.dst = शून्य;
	d40d->lli_phy.src = शून्य;
	d40d->lli_phy.dst = शून्य;
पूर्ण

अटल पूर्णांक d40_lcla_alloc_one(काष्ठा d40_chan *d40c,
			      काष्ठा d40_desc *d40d)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक ret = -EINVAL;

	spin_lock_irqsave(&d40c->base->lcla_pool.lock, flags);

	/*
	 * Allocate both src and dst at the same समय, thereक्रमe the half
	 * start on 1 since 0 can't be used since zero is used as end marker.
	 */
	क्रम (i = 1 ; i < D40_LCLA_LINK_PER_EVENT_GRP / 2; i++) अणु
		पूर्णांक idx = d40c->phy_chan->num * D40_LCLA_LINK_PER_EVENT_GRP + i;

		अगर (!d40c->base->lcla_pool.alloc_map[idx]) अणु
			d40c->base->lcla_pool.alloc_map[idx] = d40d;
			d40d->lcla_alloc++;
			ret = i;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&d40c->base->lcla_pool.lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक d40_lcla_मुक्त_all(काष्ठा d40_chan *d40c,
			     काष्ठा d40_desc *d40d)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक ret = -EINVAL;

	अगर (chan_is_physical(d40c))
		वापस 0;

	spin_lock_irqsave(&d40c->base->lcla_pool.lock, flags);

	क्रम (i = 1 ; i < D40_LCLA_LINK_PER_EVENT_GRP / 2; i++) अणु
		पूर्णांक idx = d40c->phy_chan->num * D40_LCLA_LINK_PER_EVENT_GRP + i;

		अगर (d40c->base->lcla_pool.alloc_map[idx] == d40d) अणु
			d40c->base->lcla_pool.alloc_map[idx] = शून्य;
			d40d->lcla_alloc--;
			अगर (d40d->lcla_alloc == 0) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&d40c->base->lcla_pool.lock, flags);

	वापस ret;

पूर्ण

अटल व्योम d40_desc_हटाओ(काष्ठा d40_desc *d40d)
अणु
	list_del(&d40d->node);
पूर्ण

अटल काष्ठा d40_desc *d40_desc_get(काष्ठा d40_chan *d40c)
अणु
	काष्ठा d40_desc *desc = शून्य;

	अगर (!list_empty(&d40c->client)) अणु
		काष्ठा d40_desc *d;
		काष्ठा d40_desc *_d;

		list_क्रम_each_entry_safe(d, _d, &d40c->client, node) अणु
			अगर (async_tx_test_ack(&d->txd)) अणु
				d40_desc_हटाओ(d);
				desc = d;
				स_रखो(desc, 0, माप(*desc));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!desc)
		desc = kmem_cache_zalloc(d40c->base->desc_slab, GFP_NOWAIT);

	अगर (desc)
		INIT_LIST_HEAD(&desc->node);

	वापस desc;
पूर्ण

अटल व्योम d40_desc_मुक्त(काष्ठा d40_chan *d40c, काष्ठा d40_desc *d40d)
अणु

	d40_pool_lli_मुक्त(d40c, d40d);
	d40_lcla_मुक्त_all(d40c, d40d);
	kmem_cache_मुक्त(d40c->base->desc_slab, d40d);
पूर्ण

अटल व्योम d40_desc_submit(काष्ठा d40_chan *d40c, काष्ठा d40_desc *desc)
अणु
	list_add_tail(&desc->node, &d40c->active);
पूर्ण

अटल व्योम d40_phy_lli_load(काष्ठा d40_chan *chan, काष्ठा d40_desc *desc)
अणु
	काष्ठा d40_phy_lli *lli_dst = desc->lli_phy.dst;
	काष्ठा d40_phy_lli *lli_src = desc->lli_phy.src;
	व्योम __iomem *base = chan_base(chan);

	ग_लिखोl(lli_src->reg_cfg, base + D40_CHAN_REG_SSCFG);
	ग_लिखोl(lli_src->reg_elt, base + D40_CHAN_REG_SSELT);
	ग_लिखोl(lli_src->reg_ptr, base + D40_CHAN_REG_SSPTR);
	ग_लिखोl(lli_src->reg_lnk, base + D40_CHAN_REG_SSLNK);

	ग_लिखोl(lli_dst->reg_cfg, base + D40_CHAN_REG_SDCFG);
	ग_लिखोl(lli_dst->reg_elt, base + D40_CHAN_REG_SDELT);
	ग_लिखोl(lli_dst->reg_ptr, base + D40_CHAN_REG_SDPTR);
	ग_लिखोl(lli_dst->reg_lnk, base + D40_CHAN_REG_SDLNK);
पूर्ण

अटल व्योम d40_desc_करोne(काष्ठा d40_chan *d40c, काष्ठा d40_desc *desc)
अणु
	list_add_tail(&desc->node, &d40c->करोne);
पूर्ण

अटल व्योम d40_log_lli_to_lcxa(काष्ठा d40_chan *chan, काष्ठा d40_desc *desc)
अणु
	काष्ठा d40_lcla_pool *pool = &chan->base->lcla_pool;
	काष्ठा d40_log_lli_bidir *lli = &desc->lli_log;
	पूर्णांक lli_current = desc->lli_current;
	पूर्णांक lli_len = desc->lli_len;
	bool cyclic = desc->cyclic;
	पूर्णांक curr_lcla = -EINVAL;
	पूर्णांक first_lcla = 0;
	bool use_esram_lcla = chan->base->plat_data->use_esram_lcla;
	bool linkback;

	/*
	 * We may have partially running cyclic transfers, in हाल we did't get
	 * enough LCLA entries.
	 */
	linkback = cyclic && lli_current == 0;

	/*
	 * For linkback, we need one LCLA even with only one link, because we
	 * can't link back to the one in LCPA space
	 */
	अगर (linkback || (lli_len - lli_current > 1)) अणु
		/*
		 * If the channel is expected to use only soft_lli करोn't
		 * allocate a lcla. This is to aव्योम a HW issue that exists
		 * in some controller during a peripheral to memory transfer
		 * that uses linked lists.
		 */
		अगर (!(chan->phy_chan->use_soft_lli &&
			chan->dma_cfg.dir == DMA_DEV_TO_MEM))
			curr_lcla = d40_lcla_alloc_one(chan, desc);

		first_lcla = curr_lcla;
	पूर्ण

	/*
	 * For linkback, we normally load the LCPA in the loop since we need to
	 * link it to the second LCLA and not the first.  However, अगर we
	 * couldn't even get a first LCLA, then we have to run in LCPA and
	 * reload manually.
	 */
	अगर (!linkback || curr_lcla == -EINVAL) अणु
		अचिन्हित पूर्णांक flags = 0;

		अगर (curr_lcla == -EINVAL)
			flags |= LLI_TERM_INT;

		d40_log_lli_lcpa_ग_लिखो(chan->lcpa,
				       &lli->dst[lli_current],
				       &lli->src[lli_current],
				       curr_lcla,
				       flags);
		lli_current++;
	पूर्ण

	अगर (curr_lcla < 0)
		जाओ set_current;

	क्रम (; lli_current < lli_len; lli_current++) अणु
		अचिन्हित पूर्णांक lcla_offset = chan->phy_chan->num * 1024 +
					   8 * curr_lcla * 2;
		काष्ठा d40_log_lli *lcla = pool->base + lcla_offset;
		अचिन्हित पूर्णांक flags = 0;
		पूर्णांक next_lcla;

		अगर (lli_current + 1 < lli_len)
			next_lcla = d40_lcla_alloc_one(chan, desc);
		अन्यथा
			next_lcla = linkback ? first_lcla : -EINVAL;

		अगर (cyclic || next_lcla == -EINVAL)
			flags |= LLI_TERM_INT;

		अगर (linkback && curr_lcla == first_lcla) अणु
			/* First link goes in both LCPA and LCLA */
			d40_log_lli_lcpa_ग_लिखो(chan->lcpa,
					       &lli->dst[lli_current],
					       &lli->src[lli_current],
					       next_lcla, flags);
		पूर्ण

		/*
		 * One unused LCLA in the cyclic हाल अगर the very first
		 * next_lcla fails...
		 */
		d40_log_lli_lcla_ग_लिखो(lcla,
				       &lli->dst[lli_current],
				       &lli->src[lli_current],
				       next_lcla, flags);

		/*
		 * Cache मुख्यtenance is not needed अगर lcla is
		 * mapped in esram
		 */
		अगर (!use_esram_lcla) अणु
			dma_sync_single_range_क्रम_device(chan->base->dev,
						pool->dma_addr, lcla_offset,
						2 * माप(काष्ठा d40_log_lli),
						DMA_TO_DEVICE);
		पूर्ण
		curr_lcla = next_lcla;

		अगर (curr_lcla == -EINVAL || curr_lcla == first_lcla) अणु
			lli_current++;
			अवरोध;
		पूर्ण
	पूर्ण
 set_current:
	desc->lli_current = lli_current;
पूर्ण

अटल व्योम d40_desc_load(काष्ठा d40_chan *d40c, काष्ठा d40_desc *d40d)
अणु
	अगर (chan_is_physical(d40c)) अणु
		d40_phy_lli_load(d40c, d40d);
		d40d->lli_current = d40d->lli_len;
	पूर्ण अन्यथा
		d40_log_lli_to_lcxa(d40c, d40d);
पूर्ण

अटल काष्ठा d40_desc *d40_first_active_get(काष्ठा d40_chan *d40c)
अणु
	वापस list_first_entry_or_null(&d40c->active, काष्ठा d40_desc, node);
पूर्ण

/* हटाओ desc from current queue and add it to the pending_queue */
अटल व्योम d40_desc_queue(काष्ठा d40_chan *d40c, काष्ठा d40_desc *desc)
अणु
	d40_desc_हटाओ(desc);
	desc->is_in_client_list = false;
	list_add_tail(&desc->node, &d40c->pending_queue);
पूर्ण

अटल काष्ठा d40_desc *d40_first_pending(काष्ठा d40_chan *d40c)
अणु
	वापस list_first_entry_or_null(&d40c->pending_queue, काष्ठा d40_desc,
					node);
पूर्ण

अटल काष्ठा d40_desc *d40_first_queued(काष्ठा d40_chan *d40c)
अणु
	वापस list_first_entry_or_null(&d40c->queue, काष्ठा d40_desc, node);
पूर्ण

अटल काष्ठा d40_desc *d40_first_करोne(काष्ठा d40_chan *d40c)
अणु
	वापस list_first_entry_or_null(&d40c->करोne, काष्ठा d40_desc, node);
पूर्ण

अटल पूर्णांक d40_psize_2_burst_size(bool is_log, पूर्णांक psize)
अणु
	अगर (is_log) अणु
		अगर (psize == STEDMA40_PSIZE_LOG_1)
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (psize == STEDMA40_PSIZE_PHY_1)
			वापस 1;
	पूर्ण

	वापस 2 << psize;
पूर्ण

/*
 * The dma only supports transmitting packages up to
 * STEDMA40_MAX_SEG_SIZE * data_width, where data_width is stored in Bytes.
 *
 * Calculate the total number of dma elements required to send the entire sg list.
 */
अटल पूर्णांक d40_size_2_dmalen(पूर्णांक size, u32 data_width1, u32 data_width2)
अणु
	पूर्णांक dmalen;
	u32 max_w = max(data_width1, data_width2);
	u32 min_w = min(data_width1, data_width2);
	u32 seg_max = ALIGN(STEDMA40_MAX_SEG_SIZE * min_w, max_w);

	अगर (seg_max > STEDMA40_MAX_SEG_SIZE)
		seg_max -= max_w;

	अगर (!IS_ALIGNED(size, max_w))
		वापस -EINVAL;

	अगर (size <= seg_max)
		dmalen = 1;
	अन्यथा अणु
		dmalen = size / seg_max;
		अगर (dmalen * seg_max < size)
			dmalen++;
	पूर्ण
	वापस dmalen;
पूर्ण

अटल पूर्णांक d40_sg_2_dmalen(काष्ठा scatterlist *sgl, पूर्णांक sg_len,
			   u32 data_width1, u32 data_width2)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;
	पूर्णांक len = 0;
	पूर्णांक ret;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		ret = d40_size_2_dmalen(sg_dma_len(sg),
					data_width1, data_width2);
		अगर (ret < 0)
			वापस ret;
		len += ret;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक __d40_execute_command_phy(काष्ठा d40_chan *d40c,
				     क्रमागत d40_command command)
अणु
	u32 status;
	पूर्णांक i;
	व्योम __iomem *active_reg;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	u32 wmask;

	अगर (command == D40_DMA_STOP) अणु
		ret = __d40_execute_command_phy(d40c, D40_DMA_SUSPEND_REQ);
		अगर (ret)
			वापस ret;
	पूर्ण

	spin_lock_irqsave(&d40c->base->execmd_lock, flags);

	अगर (d40c->phy_chan->num % 2 == 0)
		active_reg = d40c->base->virtbase + D40_DREG_ACTIVE;
	अन्यथा
		active_reg = d40c->base->virtbase + D40_DREG_ACTIVO;

	अगर (command == D40_DMA_SUSPEND_REQ) अणु
		status = (पढ़ोl(active_reg) &
			  D40_CHAN_POS_MASK(d40c->phy_chan->num)) >>
			D40_CHAN_POS(d40c->phy_chan->num);

		अगर (status == D40_DMA_SUSPENDED || status == D40_DMA_STOP)
			जाओ unlock;
	पूर्ण

	wmask = 0xffffffff & ~(D40_CHAN_POS_MASK(d40c->phy_chan->num));
	ग_लिखोl(wmask | (command << D40_CHAN_POS(d40c->phy_chan->num)),
	       active_reg);

	अगर (command == D40_DMA_SUSPEND_REQ) अणु

		क्रम (i = 0 ; i < D40_SUSPEND_MAX_IT; i++) अणु
			status = (पढ़ोl(active_reg) &
				  D40_CHAN_POS_MASK(d40c->phy_chan->num)) >>
				D40_CHAN_POS(d40c->phy_chan->num);

			cpu_relax();
			/*
			 * Reduce the number of bus accesses जबतक
			 * रुकोing क्रम the DMA to suspend.
			 */
			udelay(3);

			अगर (status == D40_DMA_STOP ||
			    status == D40_DMA_SUSPENDED)
				अवरोध;
		पूर्ण

		अगर (i == D40_SUSPEND_MAX_IT) अणु
			chan_err(d40c,
				"unable to suspend the chl %d (log: %d) status %x\n",
				d40c->phy_chan->num, d40c->log_num,
				status);
			dump_stack();
			ret = -EBUSY;
		पूर्ण

	पूर्ण
 unlock:
	spin_unlock_irqrestore(&d40c->base->execmd_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम d40_term_all(काष्ठा d40_chan *d40c)
अणु
	काष्ठा d40_desc *d40d;
	काष्ठा d40_desc *_d;

	/* Release completed descriptors */
	जबतक ((d40d = d40_first_करोne(d40c))) अणु
		d40_desc_हटाओ(d40d);
		d40_desc_मुक्त(d40c, d40d);
	पूर्ण

	/* Release active descriptors */
	जबतक ((d40d = d40_first_active_get(d40c))) अणु
		d40_desc_हटाओ(d40d);
		d40_desc_मुक्त(d40c, d40d);
	पूर्ण

	/* Release queued descriptors रुकोing क्रम transfer */
	जबतक ((d40d = d40_first_queued(d40c))) अणु
		d40_desc_हटाओ(d40d);
		d40_desc_मुक्त(d40c, d40d);
	पूर्ण

	/* Release pending descriptors */
	जबतक ((d40d = d40_first_pending(d40c))) अणु
		d40_desc_हटाओ(d40d);
		d40_desc_मुक्त(d40c, d40d);
	पूर्ण

	/* Release client owned descriptors */
	अगर (!list_empty(&d40c->client))
		list_क्रम_each_entry_safe(d40d, _d, &d40c->client, node) अणु
			d40_desc_हटाओ(d40d);
			d40_desc_मुक्त(d40c, d40d);
		पूर्ण

	/* Release descriptors in prepare queue */
	अगर (!list_empty(&d40c->prepare_queue))
		list_क्रम_each_entry_safe(d40d, _d,
					 &d40c->prepare_queue, node) अणु
			d40_desc_हटाओ(d40d);
			d40_desc_मुक्त(d40c, d40d);
		पूर्ण

	d40c->pending_tx = 0;
पूर्ण

अटल व्योम __d40_config_set_event(काष्ठा d40_chan *d40c,
				   क्रमागत d40_events event_type, u32 event,
				   पूर्णांक reg)
अणु
	व्योम __iomem *addr = chan_base(d40c) + reg;
	पूर्णांक tries;
	u32 status;

	चयन (event_type) अणु

	हाल D40_DEACTIVATE_EVENTLINE:

		ग_लिखोl((D40_DEACTIVATE_EVENTLINE << D40_EVENTLINE_POS(event))
		       | ~D40_EVENTLINE_MASK(event), addr);
		अवरोध;

	हाल D40_SUSPEND_REQ_EVENTLINE:
		status = (पढ़ोl(addr) & D40_EVENTLINE_MASK(event)) >>
			  D40_EVENTLINE_POS(event);

		अगर (status == D40_DEACTIVATE_EVENTLINE ||
		    status == D40_SUSPEND_REQ_EVENTLINE)
			अवरोध;

		ग_लिखोl((D40_SUSPEND_REQ_EVENTLINE << D40_EVENTLINE_POS(event))
		       | ~D40_EVENTLINE_MASK(event), addr);

		क्रम (tries = 0 ; tries < D40_SUSPEND_MAX_IT; tries++) अणु

			status = (पढ़ोl(addr) & D40_EVENTLINE_MASK(event)) >>
				  D40_EVENTLINE_POS(event);

			cpu_relax();
			/*
			 * Reduce the number of bus accesses जबतक
			 * रुकोing क्रम the DMA to suspend.
			 */
			udelay(3);

			अगर (status == D40_DEACTIVATE_EVENTLINE)
				अवरोध;
		पूर्ण

		अगर (tries == D40_SUSPEND_MAX_IT) अणु
			chan_err(d40c,
				"unable to stop the event_line chl %d (log: %d)"
				"status %x\n", d40c->phy_chan->num,
				 d40c->log_num, status);
		पूर्ण
		अवरोध;

	हाल D40_ACTIVATE_EVENTLINE:
	/*
	 * The hardware someबार करोesn't रेजिस्टर the enable when src and dst
	 * event lines are active on the same logical channel.  Retry to ensure
	 * it करोes.  Usually only one retry is sufficient.
	 */
		tries = 100;
		जबतक (--tries) अणु
			ग_लिखोl((D40_ACTIVATE_EVENTLINE <<
				D40_EVENTLINE_POS(event)) |
				~D40_EVENTLINE_MASK(event), addr);

			अगर (पढ़ोl(addr) & D40_EVENTLINE_MASK(event))
				अवरोध;
		पूर्ण

		अगर (tries != 99)
			dev_dbg(chan2dev(d40c),
				"[%s] workaround enable S%cLNK (%d tries)\n",
				__func__, reg == D40_CHAN_REG_SSLNK ? 'S' : 'D',
				100 - tries);

		WARN_ON(!tries);
		अवरोध;

	हाल D40_ROUND_EVENTLINE:
		BUG();
		अवरोध;

	पूर्ण
पूर्ण

अटल व्योम d40_config_set_event(काष्ठा d40_chan *d40c,
				 क्रमागत d40_events event_type)
अणु
	u32 event = D40_TYPE_TO_EVENT(d40c->dma_cfg.dev_type);

	/* Enable event line connected to device (or स_नकल) */
	अगर ((d40c->dma_cfg.dir == DMA_DEV_TO_MEM) ||
	    (d40c->dma_cfg.dir == DMA_DEV_TO_DEV))
		__d40_config_set_event(d40c, event_type, event,
				       D40_CHAN_REG_SSLNK);

	अगर (d40c->dma_cfg.dir !=  DMA_DEV_TO_MEM)
		__d40_config_set_event(d40c, event_type, event,
				       D40_CHAN_REG_SDLNK);
पूर्ण

अटल u32 d40_chan_has_events(काष्ठा d40_chan *d40c)
अणु
	व्योम __iomem *chanbase = chan_base(d40c);
	u32 val;

	val = पढ़ोl(chanbase + D40_CHAN_REG_SSLNK);
	val |= पढ़ोl(chanbase + D40_CHAN_REG_SDLNK);

	वापस val;
पूर्ण

अटल पूर्णांक
__d40_execute_command_log(काष्ठा d40_chan *d40c, क्रमागत d40_command command)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 active_status;
	व्योम __iomem *active_reg;

	अगर (d40c->phy_chan->num % 2 == 0)
		active_reg = d40c->base->virtbase + D40_DREG_ACTIVE;
	अन्यथा
		active_reg = d40c->base->virtbase + D40_DREG_ACTIVO;


	spin_lock_irqsave(&d40c->phy_chan->lock, flags);

	चयन (command) अणु
	हाल D40_DMA_STOP:
	हाल D40_DMA_SUSPEND_REQ:

		active_status = (पढ़ोl(active_reg) &
				 D40_CHAN_POS_MASK(d40c->phy_chan->num)) >>
				 D40_CHAN_POS(d40c->phy_chan->num);

		अगर (active_status == D40_DMA_RUN)
			d40_config_set_event(d40c, D40_SUSPEND_REQ_EVENTLINE);
		अन्यथा
			d40_config_set_event(d40c, D40_DEACTIVATE_EVENTLINE);

		अगर (!d40_chan_has_events(d40c) && (command == D40_DMA_STOP))
			ret = __d40_execute_command_phy(d40c, command);

		अवरोध;

	हाल D40_DMA_RUN:

		d40_config_set_event(d40c, D40_ACTIVATE_EVENTLINE);
		ret = __d40_execute_command_phy(d40c, command);
		अवरोध;

	हाल D40_DMA_SUSPENDED:
		BUG();
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&d40c->phy_chan->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक d40_channel_execute_command(काष्ठा d40_chan *d40c,
				       क्रमागत d40_command command)
अणु
	अगर (chan_is_logical(d40c))
		वापस __d40_execute_command_log(d40c, command);
	अन्यथा
		वापस __d40_execute_command_phy(d40c, command);
पूर्ण

अटल u32 d40_get_prmo(काष्ठा d40_chan *d40c)
अणु
	अटल स्थिर अचिन्हित पूर्णांक phy_map[] = अणु
		[STEDMA40_PCHAN_BASIC_MODE]
			= D40_DREG_PRMO_PCHAN_BASIC,
		[STEDMA40_PCHAN_MODULO_MODE]
			= D40_DREG_PRMO_PCHAN_MODULO,
		[STEDMA40_PCHAN_DOUBLE_DST_MODE]
			= D40_DREG_PRMO_PCHAN_DOUBLE_DST,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक log_map[] = अणु
		[STEDMA40_LCHAN_SRC_PHY_DST_LOG]
			= D40_DREG_PRMO_LCHAN_SRC_PHY_DST_LOG,
		[STEDMA40_LCHAN_SRC_LOG_DST_PHY]
			= D40_DREG_PRMO_LCHAN_SRC_LOG_DST_PHY,
		[STEDMA40_LCHAN_SRC_LOG_DST_LOG]
			= D40_DREG_PRMO_LCHAN_SRC_LOG_DST_LOG,
	पूर्ण;

	अगर (chan_is_physical(d40c))
		वापस phy_map[d40c->dma_cfg.mode_opt];
	अन्यथा
		वापस log_map[d40c->dma_cfg.mode_opt];
पूर्ण

अटल व्योम d40_config_ग_लिखो(काष्ठा d40_chan *d40c)
अणु
	u32 addr_base;
	u32 var;

	/* Odd addresses are even addresses + 4 */
	addr_base = (d40c->phy_chan->num % 2) * 4;
	/* Setup channel mode to logical or physical */
	var = ((u32)(chan_is_logical(d40c)) + 1) <<
		D40_CHAN_POS(d40c->phy_chan->num);
	ग_लिखोl(var, d40c->base->virtbase + D40_DREG_PRMSE + addr_base);

	/* Setup operational mode option रेजिस्टर */
	var = d40_get_prmo(d40c) << D40_CHAN_POS(d40c->phy_chan->num);

	ग_लिखोl(var, d40c->base->virtbase + D40_DREG_PRMOE + addr_base);

	अगर (chan_is_logical(d40c)) अणु
		पूर्णांक lidx = (d40c->phy_chan->num << D40_SREG_ELEM_LOG_LIDX_POS)
			   & D40_SREG_ELEM_LOG_LIDX_MASK;
		व्योम __iomem *chanbase = chan_base(d40c);

		/* Set शेष config क्रम CFG reg */
		ग_लिखोl(d40c->src_def_cfg, chanbase + D40_CHAN_REG_SSCFG);
		ग_लिखोl(d40c->dst_def_cfg, chanbase + D40_CHAN_REG_SDCFG);

		/* Set LIDX क्रम lcla */
		ग_लिखोl(lidx, chanbase + D40_CHAN_REG_SSELT);
		ग_लिखोl(lidx, chanbase + D40_CHAN_REG_SDELT);

		/* Clear LNK which will be used by d40_chan_has_events() */
		ग_लिखोl(0, chanbase + D40_CHAN_REG_SSLNK);
		ग_लिखोl(0, chanbase + D40_CHAN_REG_SDLNK);
	पूर्ण
पूर्ण

अटल u32 d40_residue(काष्ठा d40_chan *d40c)
अणु
	u32 num_elt;

	अगर (chan_is_logical(d40c))
		num_elt = (पढ़ोl(&d40c->lcpa->lcsp2) & D40_MEM_LCSP2_ECNT_MASK)
			>> D40_MEM_LCSP2_ECNT_POS;
	अन्यथा अणु
		u32 val = पढ़ोl(chan_base(d40c) + D40_CHAN_REG_SDELT);
		num_elt = (val & D40_SREG_ELEM_PHY_ECNT_MASK)
			  >> D40_SREG_ELEM_PHY_ECNT_POS;
	पूर्ण

	वापस num_elt * d40c->dma_cfg.dst_info.data_width;
पूर्ण

अटल bool d40_tx_is_linked(काष्ठा d40_chan *d40c)
अणु
	bool is_link;

	अगर (chan_is_logical(d40c))
		is_link = पढ़ोl(&d40c->lcpa->lcsp3) &  D40_MEM_LCSP3_DLOS_MASK;
	अन्यथा
		is_link = पढ़ोl(chan_base(d40c) + D40_CHAN_REG_SDLNK)
			  & D40_SREG_LNK_PHYS_LNK_MASK;

	वापस is_link;
पूर्ण

अटल पूर्णांक d40_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा d40_chan *d40c = container_of(chan, काष्ठा d40_chan, chan);
	पूर्णांक res = 0;
	अचिन्हित दीर्घ flags;

	अगर (d40c->phy_chan == शून्य) अणु
		chan_err(d40c, "Channel is not allocated!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!d40c->busy)
		वापस 0;

	spin_lock_irqsave(&d40c->lock, flags);
	pm_runसमय_get_sync(d40c->base->dev);

	res = d40_channel_execute_command(d40c, D40_DMA_SUSPEND_REQ);

	pm_runसमय_mark_last_busy(d40c->base->dev);
	pm_runसमय_put_स्वतःsuspend(d40c->base->dev);
	spin_unlock_irqrestore(&d40c->lock, flags);
	वापस res;
पूर्ण

अटल पूर्णांक d40_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा d40_chan *d40c = container_of(chan, काष्ठा d40_chan, chan);
	पूर्णांक res = 0;
	अचिन्हित दीर्घ flags;

	अगर (d40c->phy_chan == शून्य) अणु
		chan_err(d40c, "Channel is not allocated!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!d40c->busy)
		वापस 0;

	spin_lock_irqsave(&d40c->lock, flags);
	pm_runसमय_get_sync(d40c->base->dev);

	/* If bytes left to transfer or linked tx resume job */
	अगर (d40_residue(d40c) || d40_tx_is_linked(d40c))
		res = d40_channel_execute_command(d40c, D40_DMA_RUN);

	pm_runसमय_mark_last_busy(d40c->base->dev);
	pm_runसमय_put_स्वतःsuspend(d40c->base->dev);
	spin_unlock_irqrestore(&d40c->lock, flags);
	वापस res;
पूर्ण

अटल dma_cookie_t d40_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा d40_chan *d40c = container_of(tx->chan,
					     काष्ठा d40_chan,
					     chan);
	काष्ठा d40_desc *d40d = container_of(tx, काष्ठा d40_desc, txd);
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie;

	spin_lock_irqsave(&d40c->lock, flags);
	cookie = dma_cookie_assign(tx);
	d40_desc_queue(d40c, d40d);
	spin_unlock_irqrestore(&d40c->lock, flags);

	वापस cookie;
पूर्ण

अटल पूर्णांक d40_start(काष्ठा d40_chan *d40c)
अणु
	वापस d40_channel_execute_command(d40c, D40_DMA_RUN);
पूर्ण

अटल काष्ठा d40_desc *d40_queue_start(काष्ठा d40_chan *d40c)
अणु
	काष्ठा d40_desc *d40d;
	पूर्णांक err;

	/* Start queued jobs, अगर any */
	d40d = d40_first_queued(d40c);

	अगर (d40d != शून्य) अणु
		अगर (!d40c->busy) अणु
			d40c->busy = true;
			pm_runसमय_get_sync(d40c->base->dev);
		पूर्ण

		/* Remove from queue */
		d40_desc_हटाओ(d40d);

		/* Add to active queue */
		d40_desc_submit(d40c, d40d);

		/* Initiate DMA job */
		d40_desc_load(d40c, d40d);

		/* Start dma job */
		err = d40_start(d40c);

		अगर (err)
			वापस शून्य;
	पूर्ण

	वापस d40d;
पूर्ण

/* called from पूर्णांकerrupt context */
अटल व्योम dma_tc_handle(काष्ठा d40_chan *d40c)
अणु
	काष्ठा d40_desc *d40d;

	/* Get first active entry from list */
	d40d = d40_first_active_get(d40c);

	अगर (d40d == शून्य)
		वापस;

	अगर (d40d->cyclic) अणु
		/*
		 * If this was a paritially loaded list, we need to reloaded
		 * it, and only when the list is completed.  We need to check
		 * क्रम करोne because the पूर्णांकerrupt will hit क्रम every link, and
		 * not just the last one.
		 */
		अगर (d40d->lli_current < d40d->lli_len
		    && !d40_tx_is_linked(d40c)
		    && !d40_residue(d40c)) अणु
			d40_lcla_मुक्त_all(d40c, d40d);
			d40_desc_load(d40c, d40d);
			(व्योम) d40_start(d40c);

			अगर (d40d->lli_current == d40d->lli_len)
				d40d->lli_current = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		d40_lcla_मुक्त_all(d40c, d40d);

		अगर (d40d->lli_current < d40d->lli_len) अणु
			d40_desc_load(d40c, d40d);
			/* Start dma job */
			(व्योम) d40_start(d40c);
			वापस;
		पूर्ण

		अगर (d40_queue_start(d40c) == शून्य) अणु
			d40c->busy = false;

			pm_runसमय_mark_last_busy(d40c->base->dev);
			pm_runसमय_put_स्वतःsuspend(d40c->base->dev);
		पूर्ण

		d40_desc_हटाओ(d40d);
		d40_desc_करोne(d40c, d40d);
	पूर्ण

	d40c->pending_tx++;
	tasklet_schedule(&d40c->tasklet);

पूर्ण

अटल व्योम dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा d40_chan *d40c = from_tasklet(d40c, t, tasklet);
	काष्ठा d40_desc *d40d;
	अचिन्हित दीर्घ flags;
	bool callback_active;
	काष्ठा dmaengine_desc_callback cb;

	spin_lock_irqsave(&d40c->lock, flags);

	/* Get first entry from the करोne list */
	d40d = d40_first_करोne(d40c);
	अगर (d40d == शून्य) अणु
		/* Check अगर we have reached here क्रम cyclic job */
		d40d = d40_first_active_get(d40c);
		अगर (d40d == शून्य || !d40d->cyclic)
			जाओ check_pending_tx;
	पूर्ण

	अगर (!d40d->cyclic)
		dma_cookie_complete(&d40d->txd);

	/*
	 * If terminating a channel pending_tx is set to zero.
	 * This prevents any finished active jobs to वापस to the client.
	 */
	अगर (d40c->pending_tx == 0) अणु
		spin_unlock_irqrestore(&d40c->lock, flags);
		वापस;
	पूर्ण

	/* Callback to client */
	callback_active = !!(d40d->txd.flags & DMA_PREP_INTERRUPT);
	dmaengine_desc_get_callback(&d40d->txd, &cb);

	अगर (!d40d->cyclic) अणु
		अगर (async_tx_test_ack(&d40d->txd)) अणु
			d40_desc_हटाओ(d40d);
			d40_desc_मुक्त(d40c, d40d);
		पूर्ण अन्यथा अगर (!d40d->is_in_client_list) अणु
			d40_desc_हटाओ(d40d);
			d40_lcla_मुक्त_all(d40c, d40d);
			list_add_tail(&d40d->node, &d40c->client);
			d40d->is_in_client_list = true;
		पूर्ण
	पूर्ण

	d40c->pending_tx--;

	अगर (d40c->pending_tx)
		tasklet_schedule(&d40c->tasklet);

	spin_unlock_irqrestore(&d40c->lock, flags);

	अगर (callback_active)
		dmaengine_desc_callback_invoke(&cb, शून्य);

	वापस;
 check_pending_tx:
	/* Rescue manouver अगर receiving द्विगुन पूर्णांकerrupts */
	अगर (d40c->pending_tx > 0)
		d40c->pending_tx--;
	spin_unlock_irqrestore(&d40c->lock, flags);
पूर्ण

अटल irqवापस_t d40_handle_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक i;
	u32 idx;
	u32 row;
	दीर्घ chan = -1;
	काष्ठा d40_chan *d40c;
	काष्ठा d40_base *base = data;
	u32 *regs = base->regs_पूर्णांकerrupt;
	काष्ठा d40_पूर्णांकerrupt_lookup *il = base->gen_dmac.il;
	u32 il_size = base->gen_dmac.il_size;

	spin_lock(&base->पूर्णांकerrupt_lock);

	/* Read पूर्णांकerrupt status of both logical and physical channels */
	क्रम (i = 0; i < il_size; i++)
		regs[i] = पढ़ोl(base->virtbase + il[i].src);

	क्रम (;;) अणु

		chan = find_next_bit((अचिन्हित दीर्घ *)regs,
				     BITS_PER_LONG * il_size, chan + 1);

		/* No more set bits found? */
		अगर (chan == BITS_PER_LONG * il_size)
			अवरोध;

		row = chan / BITS_PER_LONG;
		idx = chan & (BITS_PER_LONG - 1);

		अगर (il[row].offset == D40_PHY_CHAN)
			d40c = base->lookup_phy_chans[idx];
		अन्यथा
			d40c = base->lookup_log_chans[il[row].offset + idx];

		अगर (!d40c) अणु
			/*
			 * No error because this can happen अगर something अन्यथा
			 * in the प्रणाली is using the channel.
			 */
			जारी;
		पूर्ण

		/* ACK पूर्णांकerrupt */
		ग_लिखोl(BIT(idx), base->virtbase + il[row].clr);

		spin_lock(&d40c->lock);

		अगर (!il[row].is_error)
			dma_tc_handle(d40c);
		अन्यथा
			d40_err(base->dev, "IRQ chan: %ld offset %d idx %d\n",
				chan, il[row].offset, idx);

		spin_unlock(&d40c->lock);
	पूर्ण

	spin_unlock(&base->पूर्णांकerrupt_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक d40_validate_conf(काष्ठा d40_chan *d40c,
			     काष्ठा stedma40_chan_cfg *conf)
अणु
	पूर्णांक res = 0;
	bool is_log = conf->mode == STEDMA40_MODE_LOGICAL;

	अगर (!conf->dir) अणु
		chan_err(d40c, "Invalid direction.\n");
		res = -EINVAL;
	पूर्ण

	अगर ((is_log && conf->dev_type > d40c->base->num_log_chans)  ||
	    (!is_log && conf->dev_type > d40c->base->num_phy_chans) ||
	    (conf->dev_type < 0)) अणु
		chan_err(d40c, "Invalid device type (%d)\n", conf->dev_type);
		res = -EINVAL;
	पूर्ण

	अगर (conf->dir == DMA_DEV_TO_DEV) अणु
		/*
		 * DMAC HW supports it. Will be added to this driver,
		 * in हाल any dma client requires it.
		 */
		chan_err(d40c, "periph to periph not supported\n");
		res = -EINVAL;
	पूर्ण

	अगर (d40_psize_2_burst_size(is_log, conf->src_info.psize) *
	    conf->src_info.data_width !=
	    d40_psize_2_burst_size(is_log, conf->dst_info.psize) *
	    conf->dst_info.data_width) अणु
		/*
		 * The DMAC hardware only supports
		 * src (burst x width) == dst (burst x width)
		 */

		chan_err(d40c, "src (burst x width) != dst (burst x width)\n");
		res = -EINVAL;
	पूर्ण

	वापस res;
पूर्ण

अटल bool d40_alloc_mask_set(काष्ठा d40_phy_res *phy,
			       bool is_src, पूर्णांक log_event_line, bool is_log,
			       bool *first_user)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&phy->lock, flags);

	*first_user = ((phy->allocated_src | phy->allocated_dst)
			== D40_ALLOC_FREE);

	अगर (!is_log) अणु
		/* Physical पूर्णांकerrupts are masked per physical full channel */
		अगर (phy->allocated_src == D40_ALLOC_FREE &&
		    phy->allocated_dst == D40_ALLOC_FREE) अणु
			phy->allocated_dst = D40_ALLOC_PHY;
			phy->allocated_src = D40_ALLOC_PHY;
			जाओ found_unlock;
		पूर्ण अन्यथा
			जाओ not_found_unlock;
	पूर्ण

	/* Logical channel */
	अगर (is_src) अणु
		अगर (phy->allocated_src == D40_ALLOC_PHY)
			जाओ not_found_unlock;

		अगर (phy->allocated_src == D40_ALLOC_FREE)
			phy->allocated_src = D40_ALLOC_LOG_FREE;

		अगर (!(phy->allocated_src & BIT(log_event_line))) अणु
			phy->allocated_src |= BIT(log_event_line);
			जाओ found_unlock;
		पूर्ण अन्यथा
			जाओ not_found_unlock;
	पूर्ण अन्यथा अणु
		अगर (phy->allocated_dst == D40_ALLOC_PHY)
			जाओ not_found_unlock;

		अगर (phy->allocated_dst == D40_ALLOC_FREE)
			phy->allocated_dst = D40_ALLOC_LOG_FREE;

		अगर (!(phy->allocated_dst & BIT(log_event_line))) अणु
			phy->allocated_dst |= BIT(log_event_line);
			जाओ found_unlock;
		पूर्ण
	पूर्ण
 not_found_unlock:
	spin_unlock_irqrestore(&phy->lock, flags);
	वापस false;
 found_unlock:
	spin_unlock_irqrestore(&phy->lock, flags);
	वापस true;
पूर्ण

अटल bool d40_alloc_mask_मुक्त(काष्ठा d40_phy_res *phy, bool is_src,
			       पूर्णांक log_event_line)
अणु
	अचिन्हित दीर्घ flags;
	bool is_मुक्त = false;

	spin_lock_irqsave(&phy->lock, flags);
	अगर (!log_event_line) अणु
		phy->allocated_dst = D40_ALLOC_FREE;
		phy->allocated_src = D40_ALLOC_FREE;
		is_मुक्त = true;
		जाओ unlock;
	पूर्ण

	/* Logical channel */
	अगर (is_src) अणु
		phy->allocated_src &= ~BIT(log_event_line);
		अगर (phy->allocated_src == D40_ALLOC_LOG_FREE)
			phy->allocated_src = D40_ALLOC_FREE;
	पूर्ण अन्यथा अणु
		phy->allocated_dst &= ~BIT(log_event_line);
		अगर (phy->allocated_dst == D40_ALLOC_LOG_FREE)
			phy->allocated_dst = D40_ALLOC_FREE;
	पूर्ण

	is_मुक्त = ((phy->allocated_src | phy->allocated_dst) ==
		   D40_ALLOC_FREE);
 unlock:
	spin_unlock_irqrestore(&phy->lock, flags);

	वापस is_मुक्त;
पूर्ण

अटल पूर्णांक d40_allocate_channel(काष्ठा d40_chan *d40c, bool *first_phy_user)
अणु
	पूर्णांक dev_type = d40c->dma_cfg.dev_type;
	पूर्णांक event_group;
	पूर्णांक event_line;
	काष्ठा d40_phy_res *phys;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक log_num;
	पूर्णांक num_phy_chans;
	bool is_src;
	bool is_log = d40c->dma_cfg.mode == STEDMA40_MODE_LOGICAL;

	phys = d40c->base->phy_res;
	num_phy_chans = d40c->base->num_phy_chans;

	अगर (d40c->dma_cfg.dir == DMA_DEV_TO_MEM) अणु
		log_num = 2 * dev_type;
		is_src = true;
	पूर्ण अन्यथा अगर (d40c->dma_cfg.dir == DMA_MEM_TO_DEV ||
		   d40c->dma_cfg.dir == DMA_MEM_TO_MEM) अणु
		/* dst event lines are used क्रम logical स_नकल */
		log_num = 2 * dev_type + 1;
		is_src = false;
	पूर्ण अन्यथा
		वापस -EINVAL;

	event_group = D40_TYPE_TO_GROUP(dev_type);
	event_line = D40_TYPE_TO_EVENT(dev_type);

	अगर (!is_log) अणु
		अगर (d40c->dma_cfg.dir == DMA_MEM_TO_MEM) अणु
			/* Find physical half channel */
			अगर (d40c->dma_cfg.use_fixed_channel) अणु
				i = d40c->dma_cfg.phy_channel;
				अगर (d40_alloc_mask_set(&phys[i], is_src,
						       0, is_log,
						       first_phy_user))
					जाओ found_phy;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < num_phy_chans; i++) अणु
					अगर (d40_alloc_mask_set(&phys[i], is_src,
						       0, is_log,
						       first_phy_user))
						जाओ found_phy;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			क्रम (j = 0; j < d40c->base->num_phy_chans; j += 8) अणु
				पूर्णांक phy_num = j  + event_group * 2;
				क्रम (i = phy_num; i < phy_num + 2; i++) अणु
					अगर (d40_alloc_mask_set(&phys[i],
							       is_src,
							       0,
							       is_log,
							       first_phy_user))
						जाओ found_phy;
				पूर्ण
			पूर्ण
		वापस -EINVAL;
found_phy:
		d40c->phy_chan = &phys[i];
		d40c->log_num = D40_PHY_CHAN;
		जाओ out;
	पूर्ण
	अगर (dev_type == -1)
		वापस -EINVAL;

	/* Find logical channel */
	क्रम (j = 0; j < d40c->base->num_phy_chans; j += 8) अणु
		पूर्णांक phy_num = j + event_group * 2;

		अगर (d40c->dma_cfg.use_fixed_channel) अणु
			i = d40c->dma_cfg.phy_channel;

			अगर ((i != phy_num) && (i != phy_num + 1)) अणु
				dev_err(chan2dev(d40c),
					"invalid fixed phy channel %d\n", i);
				वापस -EINVAL;
			पूर्ण

			अगर (d40_alloc_mask_set(&phys[i], is_src, event_line,
					       is_log, first_phy_user))
				जाओ found_log;

			dev_err(chan2dev(d40c),
				"could not allocate fixed phy channel %d\n", i);
			वापस -EINVAL;
		पूर्ण

		/*
		 * Spपढ़ो logical channels across all available physical rather
		 * than pack every logical channel at the first available phy
		 * channels.
		 */
		अगर (is_src) अणु
			क्रम (i = phy_num; i < phy_num + 2; i++) अणु
				अगर (d40_alloc_mask_set(&phys[i], is_src,
						       event_line, is_log,
						       first_phy_user))
					जाओ found_log;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = phy_num + 1; i >= phy_num; i--) अणु
				अगर (d40_alloc_mask_set(&phys[i], is_src,
						       event_line, is_log,
						       first_phy_user))
					जाओ found_log;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -EINVAL;

found_log:
	d40c->phy_chan = &phys[i];
	d40c->log_num = log_num;
out:

	अगर (is_log)
		d40c->base->lookup_log_chans[d40c->log_num] = d40c;
	अन्यथा
		d40c->base->lookup_phy_chans[d40c->phy_chan->num] = d40c;

	वापस 0;

पूर्ण

अटल पूर्णांक d40_config_स_नकल(काष्ठा d40_chan *d40c)
अणु
	dma_cap_mask_t cap = d40c->chan.device->cap_mask;

	अगर (dma_has_cap(DMA_MEMCPY, cap) && !dma_has_cap(DMA_SLAVE, cap)) अणु
		d40c->dma_cfg = dma40_स_नकल_conf_log;
		d40c->dma_cfg.dev_type = dma40_स_नकल_channels[d40c->chan.chan_id];

		d40_log_cfg(&d40c->dma_cfg,
			    &d40c->log_def.lcsp1, &d40c->log_def.lcsp3);

	पूर्ण अन्यथा अगर (dma_has_cap(DMA_MEMCPY, cap) &&
		   dma_has_cap(DMA_SLAVE, cap)) अणु
		d40c->dma_cfg = dma40_स_नकल_conf_phy;

		/* Generate पूर्णांकerrrupt at end of transfer or relink. */
		d40c->dst_def_cfg |= BIT(D40_SREG_CFG_TIM_POS);

		/* Generate पूर्णांकerrupt on error. */
		d40c->src_def_cfg |= BIT(D40_SREG_CFG_EIM_POS);
		d40c->dst_def_cfg |= BIT(D40_SREG_CFG_EIM_POS);

	पूर्ण अन्यथा अणु
		chan_err(d40c, "No memcpy\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक d40_मुक्त_dma(काष्ठा d40_chan *d40c)
अणु

	पूर्णांक res = 0;
	u32 event = D40_TYPE_TO_EVENT(d40c->dma_cfg.dev_type);
	काष्ठा d40_phy_res *phy = d40c->phy_chan;
	bool is_src;

	/* Terminate all queued and active transfers */
	d40_term_all(d40c);

	अगर (phy == शून्य) अणु
		chan_err(d40c, "phy == null\n");
		वापस -EINVAL;
	पूर्ण

	अगर (phy->allocated_src == D40_ALLOC_FREE &&
	    phy->allocated_dst == D40_ALLOC_FREE) अणु
		chan_err(d40c, "channel already free\n");
		वापस -EINVAL;
	पूर्ण

	अगर (d40c->dma_cfg.dir == DMA_MEM_TO_DEV ||
	    d40c->dma_cfg.dir == DMA_MEM_TO_MEM)
		is_src = false;
	अन्यथा अगर (d40c->dma_cfg.dir == DMA_DEV_TO_MEM)
		is_src = true;
	अन्यथा अणु
		chan_err(d40c, "Unknown direction\n");
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(d40c->base->dev);
	res = d40_channel_execute_command(d40c, D40_DMA_STOP);
	अगर (res) अणु
		chan_err(d40c, "stop failed\n");
		जाओ mark_last_busy;
	पूर्ण

	d40_alloc_mask_मुक्त(phy, is_src, chan_is_logical(d40c) ? event : 0);

	अगर (chan_is_logical(d40c))
		d40c->base->lookup_log_chans[d40c->log_num] = शून्य;
	अन्यथा
		d40c->base->lookup_phy_chans[phy->num] = शून्य;

	अगर (d40c->busy) अणु
		pm_runसमय_mark_last_busy(d40c->base->dev);
		pm_runसमय_put_स्वतःsuspend(d40c->base->dev);
	पूर्ण

	d40c->busy = false;
	d40c->phy_chan = शून्य;
	d40c->configured = false;
 mark_last_busy:
	pm_runसमय_mark_last_busy(d40c->base->dev);
	pm_runसमय_put_स्वतःsuspend(d40c->base->dev);
	वापस res;
पूर्ण

अटल bool d40_is_छोड़ोd(काष्ठा d40_chan *d40c)
अणु
	व्योम __iomem *chanbase = chan_base(d40c);
	bool is_छोड़ोd = false;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *active_reg;
	u32 status;
	u32 event = D40_TYPE_TO_EVENT(d40c->dma_cfg.dev_type);

	spin_lock_irqsave(&d40c->lock, flags);

	अगर (chan_is_physical(d40c)) अणु
		अगर (d40c->phy_chan->num % 2 == 0)
			active_reg = d40c->base->virtbase + D40_DREG_ACTIVE;
		अन्यथा
			active_reg = d40c->base->virtbase + D40_DREG_ACTIVO;

		status = (पढ़ोl(active_reg) &
			  D40_CHAN_POS_MASK(d40c->phy_chan->num)) >>
			D40_CHAN_POS(d40c->phy_chan->num);
		अगर (status == D40_DMA_SUSPENDED || status == D40_DMA_STOP)
			is_छोड़ोd = true;
		जाओ unlock;
	पूर्ण

	अगर (d40c->dma_cfg.dir == DMA_MEM_TO_DEV ||
	    d40c->dma_cfg.dir == DMA_MEM_TO_MEM) अणु
		status = पढ़ोl(chanbase + D40_CHAN_REG_SDLNK);
	पूर्ण अन्यथा अगर (d40c->dma_cfg.dir == DMA_DEV_TO_MEM) अणु
		status = पढ़ोl(chanbase + D40_CHAN_REG_SSLNK);
	पूर्ण अन्यथा अणु
		chan_err(d40c, "Unknown direction\n");
		जाओ unlock;
	पूर्ण

	status = (status & D40_EVENTLINE_MASK(event)) >>
		D40_EVENTLINE_POS(event);

	अगर (status != D40_DMA_RUN)
		is_छोड़ोd = true;
 unlock:
	spin_unlock_irqrestore(&d40c->lock, flags);
	वापस is_छोड़ोd;

पूर्ण

अटल u32 stedma40_residue(काष्ठा dma_chan *chan)
अणु
	काष्ठा d40_chan *d40c =
		container_of(chan, काष्ठा d40_chan, chan);
	u32 bytes_left;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d40c->lock, flags);
	bytes_left = d40_residue(d40c);
	spin_unlock_irqrestore(&d40c->lock, flags);

	वापस bytes_left;
पूर्ण

अटल पूर्णांक
d40_prep_sg_log(काष्ठा d40_chan *chan, काष्ठा d40_desc *desc,
		काष्ठा scatterlist *sg_src, काष्ठा scatterlist *sg_dst,
		अचिन्हित पूर्णांक sg_len, dma_addr_t src_dev_addr,
		dma_addr_t dst_dev_addr)
अणु
	काष्ठा stedma40_chan_cfg *cfg = &chan->dma_cfg;
	काष्ठा stedma40_half_channel_info *src_info = &cfg->src_info;
	काष्ठा stedma40_half_channel_info *dst_info = &cfg->dst_info;
	पूर्णांक ret;

	ret = d40_log_sg_to_lli(sg_src, sg_len,
				src_dev_addr,
				desc->lli_log.src,
				chan->log_def.lcsp1,
				src_info->data_width,
				dst_info->data_width);

	ret = d40_log_sg_to_lli(sg_dst, sg_len,
				dst_dev_addr,
				desc->lli_log.dst,
				chan->log_def.lcsp3,
				dst_info->data_width,
				src_info->data_width);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक
d40_prep_sg_phy(काष्ठा d40_chan *chan, काष्ठा d40_desc *desc,
		काष्ठा scatterlist *sg_src, काष्ठा scatterlist *sg_dst,
		अचिन्हित पूर्णांक sg_len, dma_addr_t src_dev_addr,
		dma_addr_t dst_dev_addr)
अणु
	काष्ठा stedma40_chan_cfg *cfg = &chan->dma_cfg;
	काष्ठा stedma40_half_channel_info *src_info = &cfg->src_info;
	काष्ठा stedma40_half_channel_info *dst_info = &cfg->dst_info;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	अगर (desc->cyclic)
		flags |= LLI_CYCLIC | LLI_TERM_INT;

	ret = d40_phy_sg_to_lli(sg_src, sg_len, src_dev_addr,
				desc->lli_phy.src,
				virt_to_phys(desc->lli_phy.src),
				chan->src_def_cfg,
				src_info, dst_info, flags);

	ret = d40_phy_sg_to_lli(sg_dst, sg_len, dst_dev_addr,
				desc->lli_phy.dst,
				virt_to_phys(desc->lli_phy.dst),
				chan->dst_def_cfg,
				dst_info, src_info, flags);

	dma_sync_single_क्रम_device(chan->base->dev, desc->lli_pool.dma_addr,
				   desc->lli_pool.size, DMA_TO_DEVICE);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल काष्ठा d40_desc *
d40_prep_desc(काष्ठा d40_chan *chan, काष्ठा scatterlist *sg,
	      अचिन्हित पूर्णांक sg_len, अचिन्हित दीर्घ dma_flags)
अणु
	काष्ठा stedma40_chan_cfg *cfg;
	काष्ठा d40_desc *desc;
	पूर्णांक ret;

	desc = d40_desc_get(chan);
	अगर (!desc)
		वापस शून्य;

	cfg = &chan->dma_cfg;
	desc->lli_len = d40_sg_2_dmalen(sg, sg_len, cfg->src_info.data_width,
					cfg->dst_info.data_width);
	अगर (desc->lli_len < 0) अणु
		chan_err(chan, "Unaligned size\n");
		जाओ मुक्त_desc;
	पूर्ण

	ret = d40_pool_lli_alloc(chan, desc, desc->lli_len);
	अगर (ret < 0) अणु
		chan_err(chan, "Could not allocate lli\n");
		जाओ मुक्त_desc;
	पूर्ण

	desc->lli_current = 0;
	desc->txd.flags = dma_flags;
	desc->txd.tx_submit = d40_tx_submit;

	dma_async_tx_descriptor_init(&desc->txd, &chan->chan);

	वापस desc;
 मुक्त_desc:
	d40_desc_मुक्त(chan, desc);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
d40_prep_sg(काष्ठा dma_chan *dchan, काष्ठा scatterlist *sg_src,
	    काष्ठा scatterlist *sg_dst, अचिन्हित पूर्णांक sg_len,
	    क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ dma_flags)
अणु
	काष्ठा d40_chan *chan = container_of(dchan, काष्ठा d40_chan, chan);
	dma_addr_t src_dev_addr;
	dma_addr_t dst_dev_addr;
	काष्ठा d40_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!chan->phy_chan) अणु
		chan_err(chan, "Cannot prepare unallocated channel\n");
		वापस शून्य;
	पूर्ण

	d40_set_runसमय_config_ग_लिखो(dchan, &chan->slave_config, direction);

	spin_lock_irqsave(&chan->lock, flags);

	desc = d40_prep_desc(chan, sg_src, sg_len, dma_flags);
	अगर (desc == शून्य)
		जाओ unlock;

	अगर (sg_next(&sg_src[sg_len - 1]) == sg_src)
		desc->cyclic = true;

	src_dev_addr = 0;
	dst_dev_addr = 0;
	अगर (direction == DMA_DEV_TO_MEM)
		src_dev_addr = chan->runसमय_addr;
	अन्यथा अगर (direction == DMA_MEM_TO_DEV)
		dst_dev_addr = chan->runसमय_addr;

	अगर (chan_is_logical(chan))
		ret = d40_prep_sg_log(chan, desc, sg_src, sg_dst,
				      sg_len, src_dev_addr, dst_dev_addr);
	अन्यथा
		ret = d40_prep_sg_phy(chan, desc, sg_src, sg_dst,
				      sg_len, src_dev_addr, dst_dev_addr);

	अगर (ret) अणु
		chan_err(chan, "Failed to prepare %s sg job: %d\n",
			 chan_is_logical(chan) ? "log" : "phy", ret);
		जाओ मुक्त_desc;
	पूर्ण

	/*
	 * add descriptor to the prepare queue in order to be able
	 * to मुक्त them later in terminate_all
	 */
	list_add_tail(&desc->node, &chan->prepare_queue);

	spin_unlock_irqrestore(&chan->lock, flags);

	वापस &desc->txd;
 मुक्त_desc:
	d40_desc_मुक्त(chan, desc);
 unlock:
	spin_unlock_irqrestore(&chan->lock, flags);
	वापस शून्य;
पूर्ण

bool stedma40_filter(काष्ठा dma_chan *chan, व्योम *data)
अणु
	काष्ठा stedma40_chan_cfg *info = data;
	काष्ठा d40_chan *d40c =
		container_of(chan, काष्ठा d40_chan, chan);
	पूर्णांक err;

	अगर (data) अणु
		err = d40_validate_conf(d40c, info);
		अगर (!err)
			d40c->dma_cfg = *info;
	पूर्ण अन्यथा
		err = d40_config_स_नकल(d40c);

	अगर (!err)
		d40c->configured = true;

	वापस err == 0;
पूर्ण
EXPORT_SYMBOL(stedma40_filter);

अटल व्योम __d40_set_prio_rt(काष्ठा d40_chan *d40c, पूर्णांक dev_type, bool src)
अणु
	bool realसमय = d40c->dma_cfg.realसमय;
	bool highprio = d40c->dma_cfg.high_priority;
	u32 rtreg;
	u32 event = D40_TYPE_TO_EVENT(dev_type);
	u32 group = D40_TYPE_TO_GROUP(dev_type);
	u32 bit = BIT(event);
	u32 prioreg;
	काष्ठा d40_gen_dmac *dmac = &d40c->base->gen_dmac;

	rtreg = realसमय ? dmac->realसमय_en : dmac->realसमय_clear;
	/*
	 * Due to a hardware bug, in some हालs a logical channel triggered by
	 * a high priority destination event line can generate extra packet
	 * transactions.
	 *
	 * The workaround is to not set the high priority level क्रम the
	 * destination event lines that trigger logical channels.
	 */
	अगर (!src && chan_is_logical(d40c))
		highprio = false;

	prioreg = highprio ? dmac->high_prio_en : dmac->high_prio_clear;

	/* Destination event lines are stored in the upper halfword */
	अगर (!src)
		bit <<= 16;

	ग_लिखोl(bit, d40c->base->virtbase + prioreg + group * 4);
	ग_लिखोl(bit, d40c->base->virtbase + rtreg + group * 4);
पूर्ण

अटल व्योम d40_set_prio_realसमय(काष्ठा d40_chan *d40c)
अणु
	अगर (d40c->base->rev < 3)
		वापस;

	अगर ((d40c->dma_cfg.dir ==  DMA_DEV_TO_MEM) ||
	    (d40c->dma_cfg.dir == DMA_DEV_TO_DEV))
		__d40_set_prio_rt(d40c, d40c->dma_cfg.dev_type, true);

	अगर ((d40c->dma_cfg.dir ==  DMA_MEM_TO_DEV) ||
	    (d40c->dma_cfg.dir == DMA_DEV_TO_DEV))
		__d40_set_prio_rt(d40c, d40c->dma_cfg.dev_type, false);
पूर्ण

#घोषणा D40_DT_FLAGS_MODE(flags)       ((flags >> 0) & 0x1)
#घोषणा D40_DT_FLAGS_सूची(flags)        ((flags >> 1) & 0x1)
#घोषणा D40_DT_FLAGS_BIG_ENDIAN(flags) ((flags >> 2) & 0x1)
#घोषणा D40_DT_FLAGS_FIXED_CHAN(flags) ((flags >> 3) & 0x1)
#घोषणा D40_DT_FLAGS_HIGH_PRIO(flags)  ((flags >> 4) & 0x1)

अटल काष्ठा dma_chan *d40_xlate(काष्ठा of_phandle_args *dma_spec,
				  काष्ठा of_dma *ofdma)
अणु
	काष्ठा stedma40_chan_cfg cfg;
	dma_cap_mask_t cap;
	u32 flags;

	स_रखो(&cfg, 0, माप(काष्ठा stedma40_chan_cfg));

	dma_cap_zero(cap);
	dma_cap_set(DMA_SLAVE, cap);

	cfg.dev_type = dma_spec->args[0];
	flags = dma_spec->args[2];

	चयन (D40_DT_FLAGS_MODE(flags)) अणु
	हाल 0: cfg.mode = STEDMA40_MODE_LOGICAL; अवरोध;
	हाल 1: cfg.mode = STEDMA40_MODE_PHYSICAL; अवरोध;
	पूर्ण

	चयन (D40_DT_FLAGS_सूची(flags)) अणु
	हाल 0:
		cfg.dir = DMA_MEM_TO_DEV;
		cfg.dst_info.big_endian = D40_DT_FLAGS_BIG_ENDIAN(flags);
		अवरोध;
	हाल 1:
		cfg.dir = DMA_DEV_TO_MEM;
		cfg.src_info.big_endian = D40_DT_FLAGS_BIG_ENDIAN(flags);
		अवरोध;
	पूर्ण

	अगर (D40_DT_FLAGS_FIXED_CHAN(flags)) अणु
		cfg.phy_channel = dma_spec->args[1];
		cfg.use_fixed_channel = true;
	पूर्ण

	अगर (D40_DT_FLAGS_HIGH_PRIO(flags))
		cfg.high_priority = true;

	वापस dma_request_channel(cap, stedma40_filter, &cfg);
पूर्ण

/* DMA ENGINE functions */
अटल पूर्णांक d40_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा d40_chan *d40c =
		container_of(chan, काष्ठा d40_chan, chan);
	bool is_मुक्त_phy;
	spin_lock_irqsave(&d40c->lock, flags);

	dma_cookie_init(chan);

	/* If no dma configuration is set use शेष configuration (स_नकल) */
	अगर (!d40c->configured) अणु
		err = d40_config_स_नकल(d40c);
		अगर (err) अणु
			chan_err(d40c, "Failed to configure memcpy channel\n");
			जाओ mark_last_busy;
		पूर्ण
	पूर्ण

	err = d40_allocate_channel(d40c, &is_मुक्त_phy);
	अगर (err) अणु
		chan_err(d40c, "Failed to allocate channel\n");
		d40c->configured = false;
		जाओ mark_last_busy;
	पूर्ण

	pm_runसमय_get_sync(d40c->base->dev);

	d40_set_prio_realसमय(d40c);

	अगर (chan_is_logical(d40c)) अणु
		अगर (d40c->dma_cfg.dir == DMA_DEV_TO_MEM)
			d40c->lcpa = d40c->base->lcpa_base +
				d40c->dma_cfg.dev_type * D40_LCPA_CHAN_SIZE;
		अन्यथा
			d40c->lcpa = d40c->base->lcpa_base +
				d40c->dma_cfg.dev_type *
				D40_LCPA_CHAN_SIZE + D40_LCPA_CHAN_DST_DELTA;

		/* Unmask the Global Interrupt Mask. */
		d40c->src_def_cfg |= BIT(D40_SREG_CFG_LOG_GIM_POS);
		d40c->dst_def_cfg |= BIT(D40_SREG_CFG_LOG_GIM_POS);
	पूर्ण

	dev_dbg(chan2dev(d40c), "allocated %s channel (phy %d%s)\n",
		 chan_is_logical(d40c) ? "logical" : "physical",
		 d40c->phy_chan->num,
		 d40c->dma_cfg.use_fixed_channel ? ", fixed" : "");


	/*
	 * Only ग_लिखो channel configuration to the DMA अगर the physical
	 * resource is मुक्त. In हाल of multiple logical channels
	 * on the same physical resource, only the first ग_लिखो is necessary.
	 */
	अगर (is_मुक्त_phy)
		d40_config_ग_लिखो(d40c);
 mark_last_busy:
	pm_runसमय_mark_last_busy(d40c->base->dev);
	pm_runसमय_put_स्वतःsuspend(d40c->base->dev);
	spin_unlock_irqrestore(&d40c->lock, flags);
	वापस err;
पूर्ण

अटल व्योम d40_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा d40_chan *d40c =
		container_of(chan, काष्ठा d40_chan, chan);
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	अगर (d40c->phy_chan == शून्य) अणु
		chan_err(d40c, "Cannot free unallocated channel\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&d40c->lock, flags);

	err = d40_मुक्त_dma(d40c);

	अगर (err)
		chan_err(d40c, "Failed to free channel\n");
	spin_unlock_irqrestore(&d40c->lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *d40_prep_स_नकल(काष्ठा dma_chan *chan,
						       dma_addr_t dst,
						       dma_addr_t src,
						       माप_प्रकार size,
						       अचिन्हित दीर्घ dma_flags)
अणु
	काष्ठा scatterlist dst_sg;
	काष्ठा scatterlist src_sg;

	sg_init_table(&dst_sg, 1);
	sg_init_table(&src_sg, 1);

	sg_dma_address(&dst_sg) = dst;
	sg_dma_address(&src_sg) = src;

	sg_dma_len(&dst_sg) = size;
	sg_dma_len(&src_sg) = size;

	वापस d40_prep_sg(chan, &src_sg, &dst_sg, 1,
			   DMA_MEM_TO_MEM, dma_flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
d40_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		  अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		  अचिन्हित दीर्घ dma_flags, व्योम *context)
अणु
	अगर (!is_slave_direction(direction))
		वापस शून्य;

	वापस d40_prep_sg(chan, sgl, sgl, sg_len, direction, dma_flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dma40_prep_dma_cyclic(काष्ठा dma_chan *chan, dma_addr_t dma_addr,
		     माप_प्रकार buf_len, माप_प्रकार period_len,
		     क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित पूर्णांक periods = buf_len / period_len;
	काष्ठा dma_async_tx_descriptor *txd;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	sg = kसुस्मृति(periods + 1, माप(काष्ठा scatterlist), GFP_NOWAIT);
	अगर (!sg)
		वापस शून्य;

	क्रम (i = 0; i < periods; i++) अणु
		sg_dma_address(&sg[i]) = dma_addr;
		sg_dma_len(&sg[i]) = period_len;
		dma_addr += period_len;
	पूर्ण

	sg_chain(sg, periods + 1, sg);

	txd = d40_prep_sg(chan, sg, sg, periods, direction,
			  DMA_PREP_INTERRUPT);

	kमुक्त(sg);

	वापस txd;
पूर्ण

अटल क्रमागत dma_status d40_tx_status(काष्ठा dma_chan *chan,
				     dma_cookie_t cookie,
				     काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा d40_chan *d40c = container_of(chan, काष्ठा d40_chan, chan);
	क्रमागत dma_status ret;

	अगर (d40c->phy_chan == शून्य) अणु
		chan_err(d40c, "Cannot read status of unallocated channel\n");
		वापस -EINVAL;
	पूर्ण

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret != DMA_COMPLETE && txstate)
		dma_set_residue(txstate, stedma40_residue(chan));

	अगर (d40_is_छोड़ोd(d40c))
		ret = DMA_PAUSED;

	वापस ret;
पूर्ण

अटल व्योम d40_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा d40_chan *d40c = container_of(chan, काष्ठा d40_chan, chan);
	अचिन्हित दीर्घ flags;

	अगर (d40c->phy_chan == शून्य) अणु
		chan_err(d40c, "Channel is not allocated!\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&d40c->lock, flags);

	list_splice_tail_init(&d40c->pending_queue, &d40c->queue);

	/* Busy means that queued jobs are alपढ़ोy being processed */
	अगर (!d40c->busy)
		(व्योम) d40_queue_start(d40c);

	spin_unlock_irqrestore(&d40c->lock, flags);
पूर्ण

अटल पूर्णांक d40_terminate_all(काष्ठा dma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा d40_chan *d40c = container_of(chan, काष्ठा d40_chan, chan);
	पूर्णांक ret;

	अगर (d40c->phy_chan == शून्य) अणु
		chan_err(d40c, "Channel is not allocated!\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&d40c->lock, flags);

	pm_runसमय_get_sync(d40c->base->dev);
	ret = d40_channel_execute_command(d40c, D40_DMA_STOP);
	अगर (ret)
		chan_err(d40c, "Failed to stop channel\n");

	d40_term_all(d40c);
	pm_runसमय_mark_last_busy(d40c->base->dev);
	pm_runसमय_put_स्वतःsuspend(d40c->base->dev);
	अगर (d40c->busy) अणु
		pm_runसमय_mark_last_busy(d40c->base->dev);
		pm_runसमय_put_स्वतःsuspend(d40c->base->dev);
	पूर्ण
	d40c->busy = false;

	spin_unlock_irqrestore(&d40c->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
dma40_config_to_halfchannel(काष्ठा d40_chan *d40c,
			    काष्ठा stedma40_half_channel_info *info,
			    u32 maxburst)
अणु
	पूर्णांक psize;

	अगर (chan_is_logical(d40c)) अणु
		अगर (maxburst >= 16)
			psize = STEDMA40_PSIZE_LOG_16;
		अन्यथा अगर (maxburst >= 8)
			psize = STEDMA40_PSIZE_LOG_8;
		अन्यथा अगर (maxburst >= 4)
			psize = STEDMA40_PSIZE_LOG_4;
		अन्यथा
			psize = STEDMA40_PSIZE_LOG_1;
	पूर्ण अन्यथा अणु
		अगर (maxburst >= 16)
			psize = STEDMA40_PSIZE_PHY_16;
		अन्यथा अगर (maxburst >= 8)
			psize = STEDMA40_PSIZE_PHY_8;
		अन्यथा अगर (maxburst >= 4)
			psize = STEDMA40_PSIZE_PHY_4;
		अन्यथा
			psize = STEDMA40_PSIZE_PHY_1;
	पूर्ण

	info->psize = psize;
	info->flow_ctrl = STEDMA40_NO_FLOW_CTRL;

	वापस 0;
पूर्ण

अटल पूर्णांक d40_set_runसमय_config(काष्ठा dma_chan *chan,
				  काष्ठा dma_slave_config *config)
अणु
	काष्ठा d40_chan *d40c = container_of(chan, काष्ठा d40_chan, chan);

	स_नकल(&d40c->slave_config, config, माप(*config));

	वापस 0;
पूर्ण

/* Runसमय reconfiguration extension */
अटल पूर्णांक d40_set_runसमय_config_ग_लिखो(काष्ठा dma_chan *chan,
				  काष्ठा dma_slave_config *config,
				  क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा d40_chan *d40c = container_of(chan, काष्ठा d40_chan, chan);
	काष्ठा stedma40_chan_cfg *cfg = &d40c->dma_cfg;
	क्रमागत dma_slave_buswidth src_addr_width, dst_addr_width;
	dma_addr_t config_addr;
	u32 src_maxburst, dst_maxburst;
	पूर्णांक ret;

	अगर (d40c->phy_chan == शून्य) अणु
		chan_err(d40c, "Channel is not allocated!\n");
		वापस -EINVAL;
	पूर्ण

	src_addr_width = config->src_addr_width;
	src_maxburst = config->src_maxburst;
	dst_addr_width = config->dst_addr_width;
	dst_maxburst = config->dst_maxburst;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		config_addr = config->src_addr;

		अगर (cfg->dir != DMA_DEV_TO_MEM)
			dev_dbg(d40c->base->dev,
				"channel was not configured for peripheral "
				"to memory transfer (%d) overriding\n",
				cfg->dir);
		cfg->dir = DMA_DEV_TO_MEM;

		/* Configure the memory side */
		अगर (dst_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			dst_addr_width = src_addr_width;
		अगर (dst_maxburst == 0)
			dst_maxburst = src_maxburst;

	पूर्ण अन्यथा अगर (direction == DMA_MEM_TO_DEV) अणु
		config_addr = config->dst_addr;

		अगर (cfg->dir != DMA_MEM_TO_DEV)
			dev_dbg(d40c->base->dev,
				"channel was not configured for memory "
				"to peripheral transfer (%d) overriding\n",
				cfg->dir);
		cfg->dir = DMA_MEM_TO_DEV;

		/* Configure the memory side */
		अगर (src_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			src_addr_width = dst_addr_width;
		अगर (src_maxburst == 0)
			src_maxburst = dst_maxburst;
	पूर्ण अन्यथा अणु
		dev_err(d40c->base->dev,
			"unrecognized channel direction %d\n",
			direction);
		वापस -EINVAL;
	पूर्ण

	अगर (config_addr <= 0) अणु
		dev_err(d40c->base->dev, "no address supplied\n");
		वापस -EINVAL;
	पूर्ण

	अगर (src_maxburst * src_addr_width != dst_maxburst * dst_addr_width) अणु
		dev_err(d40c->base->dev,
			"src/dst width/maxburst mismatch: %d*%d != %d*%d\n",
			src_maxburst,
			src_addr_width,
			dst_maxburst,
			dst_addr_width);
		वापस -EINVAL;
	पूर्ण

	अगर (src_maxburst > 16) अणु
		src_maxburst = 16;
		dst_maxburst = src_maxburst * src_addr_width / dst_addr_width;
	पूर्ण अन्यथा अगर (dst_maxburst > 16) अणु
		dst_maxburst = 16;
		src_maxburst = dst_maxburst * dst_addr_width / src_addr_width;
	पूर्ण

	/* Only valid widths are; 1, 2, 4 and 8. */
	अगर (src_addr_width <= DMA_SLAVE_BUSWIDTH_UNDEFINED ||
	    src_addr_width >  DMA_SLAVE_BUSWIDTH_8_BYTES   ||
	    dst_addr_width <= DMA_SLAVE_BUSWIDTH_UNDEFINED ||
	    dst_addr_width >  DMA_SLAVE_BUSWIDTH_8_BYTES   ||
	    !is_घातer_of_2(src_addr_width) ||
	    !is_घातer_of_2(dst_addr_width))
		वापस -EINVAL;

	cfg->src_info.data_width = src_addr_width;
	cfg->dst_info.data_width = dst_addr_width;

	ret = dma40_config_to_halfchannel(d40c, &cfg->src_info,
					  src_maxburst);
	अगर (ret)
		वापस ret;

	ret = dma40_config_to_halfchannel(d40c, &cfg->dst_info,
					  dst_maxburst);
	अगर (ret)
		वापस ret;

	/* Fill in रेजिस्टर values */
	अगर (chan_is_logical(d40c))
		d40_log_cfg(cfg, &d40c->log_def.lcsp1, &d40c->log_def.lcsp3);
	अन्यथा
		d40_phy_cfg(cfg, &d40c->src_def_cfg, &d40c->dst_def_cfg);

	/* These settings will take precedence later */
	d40c->runसमय_addr = config_addr;
	d40c->runसमय_direction = direction;
	dev_dbg(d40c->base->dev,
		"configured channel %s for %s, data width %d/%d, "
		"maxburst %d/%d elements, LE, no flow control\n",
		dma_chan_name(chan),
		(direction == DMA_DEV_TO_MEM) ? "RX" : "TX",
		src_addr_width, dst_addr_width,
		src_maxburst, dst_maxburst);

	वापस 0;
पूर्ण

/* Initialization functions */

अटल व्योम __init d40_chan_init(काष्ठा d40_base *base, काष्ठा dma_device *dma,
				 काष्ठा d40_chan *chans, पूर्णांक offset,
				 पूर्णांक num_chans)
अणु
	पूर्णांक i = 0;
	काष्ठा d40_chan *d40c;

	INIT_LIST_HEAD(&dma->channels);

	क्रम (i = offset; i < offset + num_chans; i++) अणु
		d40c = &chans[i];
		d40c->base = base;
		d40c->chan.device = dma;

		spin_lock_init(&d40c->lock);

		d40c->log_num = D40_PHY_CHAN;

		INIT_LIST_HEAD(&d40c->करोne);
		INIT_LIST_HEAD(&d40c->active);
		INIT_LIST_HEAD(&d40c->queue);
		INIT_LIST_HEAD(&d40c->pending_queue);
		INIT_LIST_HEAD(&d40c->client);
		INIT_LIST_HEAD(&d40c->prepare_queue);

		tasklet_setup(&d40c->tasklet, dma_tasklet);

		list_add_tail(&d40c->chan.device_node,
			      &dma->channels);
	पूर्ण
पूर्ण

अटल व्योम d40_ops_init(काष्ठा d40_base *base, काष्ठा dma_device *dev)
अणु
	अगर (dma_has_cap(DMA_SLAVE, dev->cap_mask)) अणु
		dev->device_prep_slave_sg = d40_prep_slave_sg;
		dev->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	पूर्ण

	अगर (dma_has_cap(DMA_MEMCPY, dev->cap_mask)) अणु
		dev->device_prep_dma_स_नकल = d40_prep_स_नकल;
		dev->directions = BIT(DMA_MEM_TO_MEM);
		/*
		 * This controller can only access address at even
		 * 32bit boundaries, i.e. 2^2
		 */
		dev->copy_align = DMAENGINE_ALIGN_4_BYTES;
	पूर्ण

	अगर (dma_has_cap(DMA_CYCLIC, dev->cap_mask))
		dev->device_prep_dma_cyclic = dma40_prep_dma_cyclic;

	dev->device_alloc_chan_resources = d40_alloc_chan_resources;
	dev->device_मुक्त_chan_resources = d40_मुक्त_chan_resources;
	dev->device_issue_pending = d40_issue_pending;
	dev->device_tx_status = d40_tx_status;
	dev->device_config = d40_set_runसमय_config;
	dev->device_छोड़ो = d40_छोड़ो;
	dev->device_resume = d40_resume;
	dev->device_terminate_all = d40_terminate_all;
	dev->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	dev->dev = base->dev;
पूर्ण

अटल पूर्णांक __init d40_dmaengine_init(काष्ठा d40_base *base,
				     पूर्णांक num_reserved_chans)
अणु
	पूर्णांक err ;

	d40_chan_init(base, &base->dma_slave, base->log_chans,
		      0, base->num_log_chans);

	dma_cap_zero(base->dma_slave.cap_mask);
	dma_cap_set(DMA_SLAVE, base->dma_slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, base->dma_slave.cap_mask);

	d40_ops_init(base, &base->dma_slave);

	err = dmaenginem_async_device_रेजिस्टर(&base->dma_slave);

	अगर (err) अणु
		d40_err(base->dev, "Failed to register slave channels\n");
		जाओ निकास;
	पूर्ण

	d40_chan_init(base, &base->dma_स_नकल, base->log_chans,
		      base->num_log_chans, base->num_स_नकल_chans);

	dma_cap_zero(base->dma_स_नकल.cap_mask);
	dma_cap_set(DMA_MEMCPY, base->dma_स_नकल.cap_mask);

	d40_ops_init(base, &base->dma_स_नकल);

	err = dmaenginem_async_device_रेजिस्टर(&base->dma_स_नकल);

	अगर (err) अणु
		d40_err(base->dev,
			"Failed to register memcpy only channels\n");
		जाओ निकास;
	पूर्ण

	d40_chan_init(base, &base->dma_both, base->phy_chans,
		      0, num_reserved_chans);

	dma_cap_zero(base->dma_both.cap_mask);
	dma_cap_set(DMA_SLAVE, base->dma_both.cap_mask);
	dma_cap_set(DMA_MEMCPY, base->dma_both.cap_mask);
	dma_cap_set(DMA_CYCLIC, base->dma_slave.cap_mask);

	d40_ops_init(base, &base->dma_both);
	err = dmaenginem_async_device_रेजिस्टर(&base->dma_both);

	अगर (err) अणु
		d40_err(base->dev,
			"Failed to register logical and physical capable channels\n");
		जाओ निकास;
	पूर्ण
	वापस 0;
 निकास:
	वापस err;
पूर्ण

/* Suspend resume functionality */
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dma40_suspend(काष्ठा device *dev)
अणु
	काष्ठा d40_base *base = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret)
		वापस ret;

	अगर (base->lcpa_regulator)
		ret = regulator_disable(base->lcpa_regulator);
	वापस ret;
पूर्ण

अटल पूर्णांक dma40_resume(काष्ठा device *dev)
अणु
	काष्ठा d40_base *base = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (base->lcpa_regulator) अणु
		ret = regulator_enable(base->lcpa_regulator);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल व्योम dma40_backup(व्योम __iomem *baseaddr, u32 *backup,
			 u32 *regaddr, पूर्णांक num, bool save)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		व्योम __iomem *addr = baseaddr + regaddr[i];

		अगर (save)
			backup[i] = पढ़ोl_relaxed(addr);
		अन्यथा
			ग_लिखोl_relaxed(backup[i], addr);
	पूर्ण
पूर्ण

अटल व्योम d40_save_restore_रेजिस्टरs(काष्ठा d40_base *base, bool save)
अणु
	पूर्णांक i;

	/* Save/Restore channel specअगरic रेजिस्टरs */
	क्रम (i = 0; i < base->num_phy_chans; i++) अणु
		व्योम __iomem *addr;
		पूर्णांक idx;

		अगर (base->phy_res[i].reserved)
			जारी;

		addr = base->virtbase + D40_DREG_PCBASE + i * D40_DREG_PCDELTA;
		idx = i * ARRAY_SIZE(d40_backup_regs_chan);

		dma40_backup(addr, &base->reg_val_backup_chan[idx],
			     d40_backup_regs_chan,
			     ARRAY_SIZE(d40_backup_regs_chan),
			     save);
	पूर्ण

	/* Save/Restore global रेजिस्टरs */
	dma40_backup(base->virtbase, base->reg_val_backup,
		     d40_backup_regs, ARRAY_SIZE(d40_backup_regs),
		     save);

	/* Save/Restore रेजिस्टरs only existing on dma40 v3 and later */
	अगर (base->gen_dmac.backup)
		dma40_backup(base->virtbase, base->reg_val_backup_v4,
			     base->gen_dmac.backup,
			base->gen_dmac.backup_size,
			save);
पूर्ण

अटल पूर्णांक dma40_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा d40_base *base = dev_get_drvdata(dev);

	d40_save_restore_रेजिस्टरs(base, true);

	/* Don't disable/enable घड़ीs क्रम v1 due to HW bugs */
	अगर (base->rev != 1)
		ग_लिखोl_relaxed(base->gcc_pwr_off_mask,
			       base->virtbase + D40_DREG_GCC);

	वापस 0;
पूर्ण

अटल पूर्णांक dma40_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा d40_base *base = dev_get_drvdata(dev);

	d40_save_restore_रेजिस्टरs(base, false);

	ग_लिखोl_relaxed(D40_DREG_GCC_ENABLE_ALL,
		       base->virtbase + D40_DREG_GCC);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops dma40_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(dma40_suspend, dma40_resume)
	SET_RUNTIME_PM_OPS(dma40_runसमय_suspend,
				dma40_runसमय_resume,
				शून्य)
पूर्ण;

/* Initialization functions. */

अटल पूर्णांक __init d40_phy_res_init(काष्ठा d40_base *base)
अणु
	पूर्णांक i;
	पूर्णांक num_phy_chans_avail = 0;
	u32 val[2];
	पूर्णांक odd_even_bit = -2;
	पूर्णांक gcc = D40_DREG_GCC_ENA;

	val[0] = पढ़ोl(base->virtbase + D40_DREG_PRSME);
	val[1] = पढ़ोl(base->virtbase + D40_DREG_PRSMO);

	क्रम (i = 0; i < base->num_phy_chans; i++) अणु
		base->phy_res[i].num = i;
		odd_even_bit += 2 * ((i % 2) == 0);
		अगर (((val[i % 2] >> odd_even_bit) & 3) == 1) अणु
			/* Mark security only channels as occupied */
			base->phy_res[i].allocated_src = D40_ALLOC_PHY;
			base->phy_res[i].allocated_dst = D40_ALLOC_PHY;
			base->phy_res[i].reserved = true;
			gcc |= D40_DREG_GCC_EVTGRP_ENA(D40_PHYS_TO_GROUP(i),
						       D40_DREG_GCC_SRC);
			gcc |= D40_DREG_GCC_EVTGRP_ENA(D40_PHYS_TO_GROUP(i),
						       D40_DREG_GCC_DST);


		पूर्ण अन्यथा अणु
			base->phy_res[i].allocated_src = D40_ALLOC_FREE;
			base->phy_res[i].allocated_dst = D40_ALLOC_FREE;
			base->phy_res[i].reserved = false;
			num_phy_chans_avail++;
		पूर्ण
		spin_lock_init(&base->phy_res[i].lock);
	पूर्ण

	/* Mark disabled channels as occupied */
	क्रम (i = 0; base->plat_data->disabled_channels[i] != -1; i++) अणु
		पूर्णांक chan = base->plat_data->disabled_channels[i];

		base->phy_res[chan].allocated_src = D40_ALLOC_PHY;
		base->phy_res[chan].allocated_dst = D40_ALLOC_PHY;
		base->phy_res[chan].reserved = true;
		gcc |= D40_DREG_GCC_EVTGRP_ENA(D40_PHYS_TO_GROUP(chan),
					       D40_DREG_GCC_SRC);
		gcc |= D40_DREG_GCC_EVTGRP_ENA(D40_PHYS_TO_GROUP(chan),
					       D40_DREG_GCC_DST);
		num_phy_chans_avail--;
	पूर्ण

	/* Mark soft_lli channels */
	क्रम (i = 0; i < base->plat_data->num_of_soft_lli_chans; i++) अणु
		पूर्णांक chan = base->plat_data->soft_lli_chans[i];

		base->phy_res[chan].use_soft_lli = true;
	पूर्ण

	dev_info(base->dev, "%d of %d physical DMA channels available\n",
		 num_phy_chans_avail, base->num_phy_chans);

	/* Verअगरy settings extended vs standard */
	val[0] = पढ़ोl(base->virtbase + D40_DREG_PRTYP);

	क्रम (i = 0; i < base->num_phy_chans; i++) अणु

		अगर (base->phy_res[i].allocated_src == D40_ALLOC_FREE &&
		    (val[0] & 0x3) != 1)
			dev_info(base->dev,
				 "[%s] INFO: channel %d is misconfigured (%d)\n",
				 __func__, i, val[0] & 0x3);

		val[0] = val[0] >> 2;
	पूर्ण

	/*
	 * To keep things simple, Enable all घड़ीs initially.
	 * The घड़ीs will get managed later post channel allocation.
	 * The घड़ीs क्रम the event lines on which reserved channels exists
	 * are not managed here.
	 */
	ग_लिखोl(D40_DREG_GCC_ENABLE_ALL, base->virtbase + D40_DREG_GCC);
	base->gcc_pwr_off_mask = gcc;

	वापस num_phy_chans_avail;
पूर्ण

अटल काष्ठा d40_base * __init d40_hw_detect_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stedma40_platक्रमm_data *plat_data = dev_get_platdata(&pdev->dev);
	काष्ठा clk *clk;
	व्योम __iomem *virtbase;
	काष्ठा resource *res;
	काष्ठा d40_base *base;
	पूर्णांक num_log_chans;
	पूर्णांक num_phy_chans;
	पूर्णांक num_स_नकल_chans;
	पूर्णांक clk_ret = -EINVAL;
	पूर्णांक i;
	u32 pid;
	u32 cid;
	u8 rev;

	clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		d40_err(&pdev->dev, "No matching clock found\n");
		जाओ check_prepare_enabled;
	पूर्ण

	clk_ret = clk_prepare_enable(clk);
	अगर (clk_ret) अणु
		d40_err(&pdev->dev, "Failed to prepare/enable clock\n");
		जाओ disable_unprepare;
	पूर्ण

	/* Get IO क्रम DMAC base address */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "base");
	अगर (!res)
		जाओ disable_unprepare;

	अगर (request_mem_region(res->start, resource_size(res),
			       D40_NAME " I/O base") == शून्य)
		जाओ release_region;

	virtbase = ioremap(res->start, resource_size(res));
	अगर (!virtbase)
		जाओ release_region;

	/* This is just a regular AMBA PrimeCell ID actually */
	क्रम (pid = 0, i = 0; i < 4; i++)
		pid |= (पढ़ोl(virtbase + resource_size(res) - 0x20 + 4 * i)
			& 255) << (i * 8);
	क्रम (cid = 0, i = 0; i < 4; i++)
		cid |= (पढ़ोl(virtbase + resource_size(res) - 0x10 + 4 * i)
			& 255) << (i * 8);

	अगर (cid != AMBA_CID) अणु
		d40_err(&pdev->dev, "Unknown hardware! No PrimeCell ID\n");
		जाओ unmap_io;
	पूर्ण
	अगर (AMBA_MANF_BITS(pid) != AMBA_VENDOR_ST) अणु
		d40_err(&pdev->dev, "Unknown designer! Got %x wanted %x\n",
			AMBA_MANF_BITS(pid),
			AMBA_VENDOR_ST);
		जाओ unmap_io;
	पूर्ण
	/*
	 * HW revision:
	 * DB8500ed has revision 0
	 * ? has revision 1
	 * DB8500v1 has revision 2
	 * DB8500v2 has revision 3
	 * AP9540v1 has revision 4
	 * DB8540v1 has revision 4
	 */
	rev = AMBA_REV_BITS(pid);
	अगर (rev < 2) अणु
		d40_err(&pdev->dev, "hardware revision: %d is not supported", rev);
		जाओ unmap_io;
	पूर्ण

	/* The number of physical channels on this HW */
	अगर (plat_data->num_of_phy_chans)
		num_phy_chans = plat_data->num_of_phy_chans;
	अन्यथा
		num_phy_chans = 4 * (पढ़ोl(virtbase + D40_DREG_ICFG) & 0x7) + 4;

	/* The number of channels used क्रम स_नकल */
	अगर (plat_data->num_of_स_नकल_chans)
		num_स_नकल_chans = plat_data->num_of_स_नकल_chans;
	अन्यथा
		num_स_नकल_chans = ARRAY_SIZE(dma40_स_नकल_channels);

	num_log_chans = num_phy_chans * D40_MAX_LOG_CHAN_PER_PHY;

	dev_info(&pdev->dev,
		 "hardware rev: %d @ %pa with %d physical and %d logical channels\n",
		 rev, &res->start, num_phy_chans, num_log_chans);

	base = kzalloc(ALIGN(माप(काष्ठा d40_base), 4) +
		       (num_phy_chans + num_log_chans + num_स_नकल_chans) *
		       माप(काष्ठा d40_chan), GFP_KERNEL);

	अगर (base == शून्य)
		जाओ unmap_io;

	base->rev = rev;
	base->clk = clk;
	base->num_स_नकल_chans = num_स_नकल_chans;
	base->num_phy_chans = num_phy_chans;
	base->num_log_chans = num_log_chans;
	base->phy_start = res->start;
	base->phy_size = resource_size(res);
	base->virtbase = virtbase;
	base->plat_data = plat_data;
	base->dev = &pdev->dev;
	base->phy_chans = ((व्योम *)base) + ALIGN(माप(काष्ठा d40_base), 4);
	base->log_chans = &base->phy_chans[num_phy_chans];

	अगर (base->plat_data->num_of_phy_chans == 14) अणु
		base->gen_dmac.backup = d40_backup_regs_v4b;
		base->gen_dmac.backup_size = BACKUP_REGS_SZ_V4B;
		base->gen_dmac.पूर्णांकerrupt_en = D40_DREG_CPCMIS;
		base->gen_dmac.पूर्णांकerrupt_clear = D40_DREG_CPCICR;
		base->gen_dmac.realसमय_en = D40_DREG_CRSEG1;
		base->gen_dmac.realसमय_clear = D40_DREG_CRCEG1;
		base->gen_dmac.high_prio_en = D40_DREG_CPSEG1;
		base->gen_dmac.high_prio_clear = D40_DREG_CPCEG1;
		base->gen_dmac.il = il_v4b;
		base->gen_dmac.il_size = ARRAY_SIZE(il_v4b);
		base->gen_dmac.init_reg = dma_init_reg_v4b;
		base->gen_dmac.init_reg_size = ARRAY_SIZE(dma_init_reg_v4b);
	पूर्ण अन्यथा अणु
		अगर (base->rev >= 3) अणु
			base->gen_dmac.backup = d40_backup_regs_v4a;
			base->gen_dmac.backup_size = BACKUP_REGS_SZ_V4A;
		पूर्ण
		base->gen_dmac.पूर्णांकerrupt_en = D40_DREG_PCMIS;
		base->gen_dmac.पूर्णांकerrupt_clear = D40_DREG_PCICR;
		base->gen_dmac.realसमय_en = D40_DREG_RSEG1;
		base->gen_dmac.realसमय_clear = D40_DREG_RCEG1;
		base->gen_dmac.high_prio_en = D40_DREG_PSEG1;
		base->gen_dmac.high_prio_clear = D40_DREG_PCEG1;
		base->gen_dmac.il = il_v4a;
		base->gen_dmac.il_size = ARRAY_SIZE(il_v4a);
		base->gen_dmac.init_reg = dma_init_reg_v4a;
		base->gen_dmac.init_reg_size = ARRAY_SIZE(dma_init_reg_v4a);
	पूर्ण

	base->phy_res = kसुस्मृति(num_phy_chans,
				माप(*base->phy_res),
				GFP_KERNEL);
	अगर (!base->phy_res)
		जाओ मुक्त_base;

	base->lookup_phy_chans = kसुस्मृति(num_phy_chans,
					 माप(*base->lookup_phy_chans),
					 GFP_KERNEL);
	अगर (!base->lookup_phy_chans)
		जाओ मुक्त_phy_res;

	base->lookup_log_chans = kसुस्मृति(num_log_chans,
					 माप(*base->lookup_log_chans),
					 GFP_KERNEL);
	अगर (!base->lookup_log_chans)
		जाओ मुक्त_phy_chans;

	base->reg_val_backup_chan = kदो_स्मृति_array(base->num_phy_chans,
						  माप(d40_backup_regs_chan),
						  GFP_KERNEL);
	अगर (!base->reg_val_backup_chan)
		जाओ मुक्त_log_chans;

	base->lcla_pool.alloc_map = kसुस्मृति(num_phy_chans
					    * D40_LCLA_LINK_PER_EVENT_GRP,
					    माप(*base->lcla_pool.alloc_map),
					    GFP_KERNEL);
	अगर (!base->lcla_pool.alloc_map)
		जाओ मुक्त_backup_chan;

	base->regs_पूर्णांकerrupt = kदो_स्मृति_array(base->gen_dmac.il_size,
					     माप(*base->regs_पूर्णांकerrupt),
					     GFP_KERNEL);
	अगर (!base->regs_पूर्णांकerrupt)
		जाओ मुक्त_map;

	base->desc_slab = kmem_cache_create(D40_NAME, माप(काष्ठा d40_desc),
					    0, SLAB_HWCACHE_ALIGN,
					    शून्य);
	अगर (base->desc_slab == शून्य)
		जाओ मुक्त_regs;


	वापस base;
 मुक्त_regs:
	kमुक्त(base->regs_पूर्णांकerrupt);
 मुक्त_map:
	kमुक्त(base->lcla_pool.alloc_map);
 मुक्त_backup_chan:
	kमुक्त(base->reg_val_backup_chan);
 मुक्त_log_chans:
	kमुक्त(base->lookup_log_chans);
 मुक्त_phy_chans:
	kमुक्त(base->lookup_phy_chans);
 मुक्त_phy_res:
	kमुक्त(base->phy_res);
 मुक्त_base:
	kमुक्त(base);
 unmap_io:
	iounmap(virtbase);
 release_region:
	release_mem_region(res->start, resource_size(res));
 check_prepare_enabled:
	अगर (!clk_ret)
 disable_unprepare:
		clk_disable_unprepare(clk);
	अगर (!IS_ERR(clk))
		clk_put(clk);
	वापस शून्य;
पूर्ण

अटल व्योम __init d40_hw_init(काष्ठा d40_base *base)
अणु

	पूर्णांक i;
	u32 prmseo[2] = अणु0, 0पूर्ण;
	u32 activeo[2] = अणु0xFFFFFFFF, 0xFFFFFFFFपूर्ण;
	u32 pcmis = 0;
	u32 pcicr = 0;
	काष्ठा d40_reg_val *dma_init_reg = base->gen_dmac.init_reg;
	u32 reg_size = base->gen_dmac.init_reg_size;

	क्रम (i = 0; i < reg_size; i++)
		ग_लिखोl(dma_init_reg[i].val,
		       base->virtbase + dma_init_reg[i].reg);

	/* Configure all our dma channels to शेष settings */
	क्रम (i = 0; i < base->num_phy_chans; i++) अणु

		activeo[i % 2] = activeo[i % 2] << 2;

		अगर (base->phy_res[base->num_phy_chans - i - 1].allocated_src
		    == D40_ALLOC_PHY) अणु
			activeo[i % 2] |= 3;
			जारी;
		पूर्ण

		/* Enable पूर्णांकerrupt # */
		pcmis = (pcmis << 1) | 1;

		/* Clear पूर्णांकerrupt # */
		pcicr = (pcicr << 1) | 1;

		/* Set channel to physical mode */
		prmseo[i % 2] = prmseo[i % 2] << 2;
		prmseo[i % 2] |= 1;

	पूर्ण

	ग_लिखोl(prmseo[1], base->virtbase + D40_DREG_PRMSE);
	ग_लिखोl(prmseo[0], base->virtbase + D40_DREG_PRMSO);
	ग_लिखोl(activeo[1], base->virtbase + D40_DREG_ACTIVE);
	ग_लिखोl(activeo[0], base->virtbase + D40_DREG_ACTIVO);

	/* Write which पूर्णांकerrupt to enable */
	ग_लिखोl(pcmis, base->virtbase + base->gen_dmac.पूर्णांकerrupt_en);

	/* Write which पूर्णांकerrupt to clear */
	ग_लिखोl(pcicr, base->virtbase + base->gen_dmac.पूर्णांकerrupt_clear);

	/* These are __initdata and cannot be accessed after init */
	base->gen_dmac.init_reg = शून्य;
	base->gen_dmac.init_reg_size = 0;
पूर्ण

अटल पूर्णांक __init d40_lcla_allocate(काष्ठा d40_base *base)
अणु
	काष्ठा d40_lcla_pool *pool = &base->lcla_pool;
	अचिन्हित दीर्घ *page_list;
	पूर्णांक i, j;
	पूर्णांक ret;

	/*
	 * This is somewhat ugly. We need 8192 bytes that are 18 bit aligned,
	 * To full fill this hardware requirement without wasting 256 kb
	 * we allocate pages until we get an aligned one.
	 */
	page_list = kदो_स्मृति_array(MAX_LCLA_ALLOC_ATTEMPTS,
				  माप(*page_list),
				  GFP_KERNEL);
	अगर (!page_list)
		वापस -ENOMEM;

	/* Calculating how many pages that are required */
	base->lcla_pool.pages = SZ_1K * base->num_phy_chans / PAGE_SIZE;

	क्रम (i = 0; i < MAX_LCLA_ALLOC_ATTEMPTS; i++) अणु
		page_list[i] = __get_मुक्त_pages(GFP_KERNEL,
						base->lcla_pool.pages);
		अगर (!page_list[i]) अणु

			d40_err(base->dev, "Failed to allocate %d pages.\n",
				base->lcla_pool.pages);
			ret = -ENOMEM;

			क्रम (j = 0; j < i; j++)
				मुक्त_pages(page_list[j], base->lcla_pool.pages);
			जाओ मुक्त_page_list;
		पूर्ण

		अगर ((virt_to_phys((व्योम *)page_list[i]) &
		     (LCLA_ALIGNMENT - 1)) == 0)
			अवरोध;
	पूर्ण

	क्रम (j = 0; j < i; j++)
		मुक्त_pages(page_list[j], base->lcla_pool.pages);

	अगर (i < MAX_LCLA_ALLOC_ATTEMPTS) अणु
		base->lcla_pool.base = (व्योम *)page_list[i];
	पूर्ण अन्यथा अणु
		/*
		 * After many attempts and no succees with finding the correct
		 * alignment, try with allocating a big buffer.
		 */
		dev_warn(base->dev,
			 "[%s] Failed to get %d pages @ 18 bit align.\n",
			 __func__, base->lcla_pool.pages);
		base->lcla_pool.base_unaligned = kदो_स्मृति(SZ_1K *
							 base->num_phy_chans +
							 LCLA_ALIGNMENT,
							 GFP_KERNEL);
		अगर (!base->lcla_pool.base_unaligned) अणु
			ret = -ENOMEM;
			जाओ मुक्त_page_list;
		पूर्ण

		base->lcla_pool.base = PTR_ALIGN(base->lcla_pool.base_unaligned,
						 LCLA_ALIGNMENT);
	पूर्ण

	pool->dma_addr = dma_map_single(base->dev, pool->base,
					SZ_1K * base->num_phy_chans,
					DMA_TO_DEVICE);
	अगर (dma_mapping_error(base->dev, pool->dma_addr)) अणु
		pool->dma_addr = 0;
		ret = -ENOMEM;
		जाओ मुक्त_page_list;
	पूर्ण

	ग_लिखोl(virt_to_phys(base->lcla_pool.base),
	       base->virtbase + D40_DREG_LCLA);
	ret = 0;
 मुक्त_page_list:
	kमुक्त(page_list);
	वापस ret;
पूर्ण

अटल पूर्णांक __init d40_of_probe(काष्ठा platक्रमm_device *pdev,
			       काष्ठा device_node *np)
अणु
	काष्ठा stedma40_platक्रमm_data *pdata;
	पूर्णांक num_phy = 0, num_स_नकल = 0, num_disabled = 0;
	स्थिर __be32 *list;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	/* If असलent this value will be obtained from h/w. */
	of_property_पढ़ो_u32(np, "dma-channels", &num_phy);
	अगर (num_phy > 0)
		pdata->num_of_phy_chans = num_phy;

	list = of_get_property(np, "memcpy-channels", &num_स_नकल);
	num_स_नकल /= माप(*list);

	अगर (num_स_नकल > D40_MEMCPY_MAX_CHANS || num_स_नकल <= 0) अणु
		d40_err(&pdev->dev,
			"Invalid number of memcpy channels specified (%d)\n",
			num_स_नकल);
		वापस -EINVAL;
	पूर्ण
	pdata->num_of_स_नकल_chans = num_स_नकल;

	of_property_पढ़ो_u32_array(np, "memcpy-channels",
				   dma40_स_नकल_channels,
				   num_स_नकल);

	list = of_get_property(np, "disabled-channels", &num_disabled);
	num_disabled /= माप(*list);

	अगर (num_disabled >= STEDMA40_MAX_PHYS || num_disabled < 0) अणु
		d40_err(&pdev->dev,
			"Invalid number of disabled channels specified (%d)\n",
			num_disabled);
		वापस -EINVAL;
	पूर्ण

	of_property_पढ़ो_u32_array(np, "disabled-channels",
				   pdata->disabled_channels,
				   num_disabled);
	pdata->disabled_channels[num_disabled] = -1;

	pdev->dev.platक्रमm_data = pdata;

	वापस 0;
पूर्ण

अटल पूर्णांक __init d40_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stedma40_platक्रमm_data *plat_data = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret = -ENOENT;
	काष्ठा d40_base *base;
	काष्ठा resource *res;
	पूर्णांक num_reserved_chans;
	u32 val;

	अगर (!plat_data) अणु
		अगर (np) अणु
			अगर (d40_of_probe(pdev, np)) अणु
				ret = -ENOMEM;
				जाओ report_failure;
			पूर्ण
		पूर्ण अन्यथा अणु
			d40_err(&pdev->dev, "No pdata or Device Tree provided\n");
			जाओ report_failure;
		पूर्ण
	पूर्ण

	base = d40_hw_detect_init(pdev);
	अगर (!base)
		जाओ report_failure;

	num_reserved_chans = d40_phy_res_init(base);

	platक्रमm_set_drvdata(pdev, base);

	spin_lock_init(&base->पूर्णांकerrupt_lock);
	spin_lock_init(&base->execmd_lock);

	/* Get IO क्रम logical channel parameter address */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "lcpa");
	अगर (!res) अणु
		ret = -ENOENT;
		d40_err(&pdev->dev, "No \"lcpa\" memory resource\n");
		जाओ destroy_cache;
	पूर्ण
	base->lcpa_size = resource_size(res);
	base->phy_lcpa = res->start;

	अगर (request_mem_region(res->start, resource_size(res),
			       D40_NAME " I/O lcpa") == शून्य) अणु
		ret = -EBUSY;
		d40_err(&pdev->dev, "Failed to request LCPA region %pR\n", res);
		जाओ destroy_cache;
	पूर्ण

	/* We make use of ESRAM memory क्रम this. */
	val = पढ़ोl(base->virtbase + D40_DREG_LCPA);
	अगर (res->start != val && val != 0) अणु
		dev_warn(&pdev->dev,
			 "[%s] Mismatch LCPA dma 0x%x, def %pa\n",
			 __func__, val, &res->start);
	पूर्ण अन्यथा
		ग_लिखोl(res->start, base->virtbase + D40_DREG_LCPA);

	base->lcpa_base = ioremap(res->start, resource_size(res));
	अगर (!base->lcpa_base) अणु
		ret = -ENOMEM;
		d40_err(&pdev->dev, "Failed to ioremap LCPA region\n");
		जाओ destroy_cache;
	पूर्ण
	/* If lcla has to be located in ESRAM we करोn't need to allocate */
	अगर (base->plat_data->use_esram_lcla) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
							"lcla_esram");
		अगर (!res) अणु
			ret = -ENOENT;
			d40_err(&pdev->dev,
				"No \"lcla_esram\" memory resource\n");
			जाओ destroy_cache;
		पूर्ण
		base->lcla_pool.base = ioremap(res->start,
						resource_size(res));
		अगर (!base->lcla_pool.base) अणु
			ret = -ENOMEM;
			d40_err(&pdev->dev, "Failed to ioremap LCLA region\n");
			जाओ destroy_cache;
		पूर्ण
		ग_लिखोl(res->start, base->virtbase + D40_DREG_LCLA);

	पूर्ण अन्यथा अणु
		ret = d40_lcla_allocate(base);
		अगर (ret) अणु
			d40_err(&pdev->dev, "Failed to allocate LCLA area\n");
			जाओ destroy_cache;
		पूर्ण
	पूर्ण

	spin_lock_init(&base->lcla_pool.lock);

	base->irq = platक्रमm_get_irq(pdev, 0);

	ret = request_irq(base->irq, d40_handle_पूर्णांकerrupt, 0, D40_NAME, base);
	अगर (ret) अणु
		d40_err(&pdev->dev, "No IRQ defined\n");
		जाओ destroy_cache;
	पूर्ण

	अगर (base->plat_data->use_esram_lcla) अणु

		base->lcpa_regulator = regulator_get(base->dev, "lcla_esram");
		अगर (IS_ERR(base->lcpa_regulator)) अणु
			d40_err(&pdev->dev, "Failed to get lcpa_regulator\n");
			ret = PTR_ERR(base->lcpa_regulator);
			base->lcpa_regulator = शून्य;
			जाओ destroy_cache;
		पूर्ण

		ret = regulator_enable(base->lcpa_regulator);
		अगर (ret) अणु
			d40_err(&pdev->dev,
				"Failed to enable lcpa_regulator\n");
			regulator_put(base->lcpa_regulator);
			base->lcpa_regulator = शून्य;
			जाओ destroy_cache;
		पूर्ण
	पूर्ण

	ग_लिखोl_relaxed(D40_DREG_GCC_ENABLE_ALL, base->virtbase + D40_DREG_GCC);

	pm_runसमय_irq_safe(base->dev);
	pm_runसमय_set_स्वतःsuspend_delay(base->dev, DMA40_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(base->dev);
	pm_runसमय_mark_last_busy(base->dev);
	pm_runसमय_set_active(base->dev);
	pm_runसमय_enable(base->dev);

	ret = d40_dmaengine_init(base, num_reserved_chans);
	अगर (ret)
		जाओ destroy_cache;

	ret = dma_set_max_seg_size(base->dev, STEDMA40_MAX_SEG_SIZE);
	अगर (ret) अणु
		d40_err(&pdev->dev, "Failed to set dma max seg size\n");
		जाओ destroy_cache;
	पूर्ण

	d40_hw_init(base);

	अगर (np) अणु
		ret = of_dma_controller_रेजिस्टर(np, d40_xlate, शून्य);
		अगर (ret)
			dev_err(&pdev->dev,
				"could not register of_dma_controller\n");
	पूर्ण

	dev_info(base->dev, "initialized\n");
	वापस 0;
 destroy_cache:
	kmem_cache_destroy(base->desc_slab);
	अगर (base->virtbase)
		iounmap(base->virtbase);

	अगर (base->lcla_pool.base && base->plat_data->use_esram_lcla) अणु
		iounmap(base->lcla_pool.base);
		base->lcla_pool.base = शून्य;
	पूर्ण

	अगर (base->lcla_pool.dma_addr)
		dma_unmap_single(base->dev, base->lcla_pool.dma_addr,
				 SZ_1K * base->num_phy_chans,
				 DMA_TO_DEVICE);

	अगर (!base->lcla_pool.base_unaligned && base->lcla_pool.base)
		मुक्त_pages((अचिन्हित दीर्घ)base->lcla_pool.base,
			   base->lcla_pool.pages);

	kमुक्त(base->lcla_pool.base_unaligned);

	अगर (base->lcpa_base)
		iounmap(base->lcpa_base);

	अगर (base->phy_lcpa)
		release_mem_region(base->phy_lcpa,
				   base->lcpa_size);
	अगर (base->phy_start)
		release_mem_region(base->phy_start,
				   base->phy_size);
	अगर (base->clk) अणु
		clk_disable_unprepare(base->clk);
		clk_put(base->clk);
	पूर्ण

	अगर (base->lcpa_regulator) अणु
		regulator_disable(base->lcpa_regulator);
		regulator_put(base->lcpa_regulator);
	पूर्ण

	kमुक्त(base->lcla_pool.alloc_map);
	kमुक्त(base->lookup_log_chans);
	kमुक्त(base->lookup_phy_chans);
	kमुक्त(base->phy_res);
	kमुक्त(base);
 report_failure:
	d40_err(&pdev->dev, "probe failed\n");
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id d40_match[] = अणु
        अणु .compatible = "stericsson,dma40", पूर्ण,
        अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver d40_driver = अणु
	.driver = अणु
		.name  = D40_NAME,
		.pm = &dma40_pm_ops,
		.of_match_table = d40_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init stedma40_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&d40_driver, d40_probe);
पूर्ण
subsys_initcall(stedma40_init);
