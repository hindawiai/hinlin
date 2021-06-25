<शैली गुरु>
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 *         Andy Gross <andy.gross@ti.com>
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

#अगर_अघोषित OMAP_DMM_PRIV_H
#घोषणा OMAP_DMM_PRIV_H

#घोषणा DMM_REVISION          0x000
#घोषणा DMM_HWINFO            0x004
#घोषणा DMM_LISA_HWINFO       0x008
#घोषणा DMM_DMM_SYSCONFIG     0x010
#घोषणा DMM_LISA_LOCK         0x01C
#घोषणा DMM_LISA_MAP__0       0x040
#घोषणा DMM_LISA_MAP__1       0x044
#घोषणा DMM_TILER_HWINFO      0x208
#घोषणा DMM_TILER_OR__0       0x220
#घोषणा DMM_TILER_OR__1       0x224
#घोषणा DMM_PAT_HWINFO        0x408
#घोषणा DMM_PAT_GEOMETRY      0x40C
#घोषणा DMM_PAT_CONFIG        0x410
#घोषणा DMM_PAT_VIEW__0       0x420
#घोषणा DMM_PAT_VIEW__1       0x424
#घोषणा DMM_PAT_VIEW_MAP__0   0x440
#घोषणा DMM_PAT_VIEW_MAP_BASE 0x460
#घोषणा DMM_PAT_IRQ_EOI       0x478
#घोषणा DMM_PAT_IRQSTATUS_RAW 0x480
#घोषणा DMM_PAT_IRQSTATUS     0x490
#घोषणा DMM_PAT_IRQENABLE_SET 0x4A0
#घोषणा DMM_PAT_IRQENABLE_CLR 0x4B0
#घोषणा DMM_PAT_STATUS__0     0x4C0
#घोषणा DMM_PAT_STATUS__1     0x4C4
#घोषणा DMM_PAT_STATUS__2     0x4C8
#घोषणा DMM_PAT_STATUS__3     0x4CC
#घोषणा DMM_PAT_DESCR__0      0x500
#घोषणा DMM_PAT_DESCR__1      0x510
#घोषणा DMM_PAT_DESCR__2      0x520
#घोषणा DMM_PAT_DESCR__3      0x530
#घोषणा DMM_PEG_HWINFO        0x608
#घोषणा DMM_PEG_PRIO          0x620
#घोषणा DMM_PEG_PRIO_PAT      0x640

#घोषणा DMM_IRQSTAT_DST			(1<<0)
#घोषणा DMM_IRQSTAT_LST			(1<<1)
#घोषणा DMM_IRQSTAT_ERR_INV_DSC		(1<<2)
#घोषणा DMM_IRQSTAT_ERR_INV_DATA	(1<<3)
#घोषणा DMM_IRQSTAT_ERR_UPD_AREA	(1<<4)
#घोषणा DMM_IRQSTAT_ERR_UPD_CTRL	(1<<5)
#घोषणा DMM_IRQSTAT_ERR_UPD_DATA	(1<<6)
#घोषणा DMM_IRQSTAT_ERR_LUT_MISS	(1<<7)

#घोषणा DMM_IRQSTAT_ERR_MASK	(DMM_IRQSTAT_ERR_INV_DSC | \
				DMM_IRQSTAT_ERR_INV_DATA | \
				DMM_IRQSTAT_ERR_UPD_AREA | \
				DMM_IRQSTAT_ERR_UPD_CTRL | \
				DMM_IRQSTAT_ERR_UPD_DATA | \
				DMM_IRQSTAT_ERR_LUT_MISS)

#घोषणा DMM_PATSTATUS_READY		(1<<0)
#घोषणा DMM_PATSTATUS_VALID		(1<<1)
#घोषणा DMM_PATSTATUS_RUN		(1<<2)
#घोषणा DMM_PATSTATUS_DONE		(1<<3)
#घोषणा DMM_PATSTATUS_LINKED		(1<<4)
#घोषणा DMM_PATSTATUS_BYPASSED		(1<<7)
#घोषणा DMM_PATSTATUS_ERR_INV_DESCR	(1<<10)
#घोषणा DMM_PATSTATUS_ERR_INV_DATA	(1<<11)
#घोषणा DMM_PATSTATUS_ERR_UPD_AREA	(1<<12)
#घोषणा DMM_PATSTATUS_ERR_UPD_CTRL	(1<<13)
#घोषणा DMM_PATSTATUS_ERR_UPD_DATA	(1<<14)
#घोषणा DMM_PATSTATUS_ERR_ACCESS	(1<<15)

/* note: करोn't treat DMM_PATSTATUS_ERR_ACCESS as an error */
#घोषणा DMM_PATSTATUS_ERR	(DMM_PATSTATUS_ERR_INV_DESCR | \
				DMM_PATSTATUS_ERR_INV_DATA | \
				DMM_PATSTATUS_ERR_UPD_AREA | \
				DMM_PATSTATUS_ERR_UPD_CTRL | \
				DMM_PATSTATUS_ERR_UPD_DATA)



क्रमागत अणु
	PAT_STATUS,
	PAT_DESCR
पूर्ण;

काष्ठा pat_ctrl अणु
	u32 start:4;
	u32 dir:4;
	u32 lut_id:8;
	u32 sync:12;
	u32 ini:4;
पूर्ण;

काष्ठा pat अणु
	u32 next_pa;
	काष्ठा pat_area area;
	काष्ठा pat_ctrl ctrl;
	u32 data_pa;
पूर्ण;

#घोषणा DMM_FIXED_RETRY_COUNT 1000

/* create refill buffer big enough to refill all slots, plus 3 descriptors..
 * 3 descriptors is probably the worst-हाल क्रम # of 2d-slices in a 1d area,
 * but I guess you करोn't hit that worst हाल at the same समय as full area
 * refill
 */
#घोषणा DESCR_SIZE 128
#घोषणा REFILL_BUFFER_SIZE ((4 * 128 * 256) + (3 * DESCR_SIZE))

/* For OMAP5, a fixed offset is added to all Y coordinates क्रम 1D buffers.
 * This is used in programming to address the upper portion of the LUT
*/
#घोषणा OMAP5_LUT_OFFSET       128

काष्ठा dmm;

काष्ठा dmm_txn अणु
	व्योम *engine_handle;
	काष्ठा tcm *tcm;

	u8 *current_va;
	dma_addr_t current_pa;

	काष्ठा pat *last_pat;
पूर्ण;

काष्ठा refill_engine अणु
	पूर्णांक id;
	काष्ठा dmm *dmm;
	काष्ठा tcm *tcm;

	u8 *refill_va;
	dma_addr_t refill_pa;

	/* only one trans per engine क्रम now */
	काष्ठा dmm_txn txn;

	bool async;

	काष्ठा completion compl;

	काष्ठा list_head idle_node;
पूर्ण;

काष्ठा dmm_platक्रमm_data अणु
	u32 cpu_cache_flags;
पूर्ण;

काष्ठा dmm अणु
	काष्ठा device *dev;
	dma_addr_t phys_base;
	व्योम __iomem *base;
	पूर्णांक irq;

	काष्ठा page *dummy_page;
	dma_addr_t dummy_pa;

	व्योम *refill_va;
	dma_addr_t refill_pa;

	/* refill engines */
	रुको_queue_head_t engine_queue;
	काष्ठा list_head idle_head;
	काष्ठा refill_engine *engines;
	पूर्णांक num_engines;
	atomic_t engine_counter;

	/* container inक्रमmation */
	पूर्णांक container_width;
	पूर्णांक container_height;
	पूर्णांक lut_width;
	पूर्णांक lut_height;
	पूर्णांक num_lut;

	/* array of LUT - TCM containers */
	काष्ठा tcm **tcm;

	/* allocation list and lock */
	काष्ठा list_head alloc_head;

	स्थिर काष्ठा dmm_platक्रमm_data *plat_data;

	bool dmm_workaround;
	spinlock_t wa_lock;
	u32 *wa_dma_data;
	dma_addr_t wa_dma_handle;
	काष्ठा dma_chan *wa_dma_chan;
पूर्ण;

#पूर्ण_अगर
