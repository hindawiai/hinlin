<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * hal.c - DIM2 HAL implementation
 * (MediaLB, Device Interface Macro IP, OS62420)
 *
 * Copyright (C) 2015-2016, Microchip Technology Germany II GmbH & Co. KG
 */

/* Author: Andrey Shvetsov <andrey.shvetsov@k2l.de> */

#समावेश "hal.h"
#समावेश "errors.h"
#समावेश "reg.h"
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>

/*
 * Size factor क्रम isochronous DBR buffer.
 * Minimal value is 3.
 */
#घोषणा ISOC_DBR_FACTOR 3u

/*
 * Number of 32-bit units क्रम DBR map.
 *
 * 1: block size is 512, max allocation is 16K
 * 2: block size is 256, max allocation is 8K
 * 4: block size is 128, max allocation is 4K
 * 8: block size is 64, max allocation is 2K
 *
 * Min allocated space is block size.
 * Max possible allocated space is 32 blocks.
 */
#घोषणा DBR_MAP_SIZE 2

/* -------------------------------------------------------------------------- */
/* not configurable area */

#घोषणा CDT 0x00
#घोषणा ADT 0x40
#घोषणा MLB_CAT 0x80
#घोषणा AHB_CAT 0x88

#घोषणा DBR_SIZE  (16 * 1024) /* specअगरied by IP */
#घोषणा DBR_BLOCK_SIZE  (DBR_SIZE / 32 / DBR_MAP_SIZE)

#घोषणा ROUND_UP_TO(x, d)  (DIV_ROUND_UP(x, (d)) * (d))

/* -------------------------------------------------------------------------- */
/* generic helper functions and macros */

अटल अंतरभूत u32 bit_mask(u8 position)
अणु
	वापस (u32)1 << position;
पूर्ण

अटल अंतरभूत bool dim_on_error(u8 error_id, स्थिर अक्षर *error_message)
अणु
	dimcb_on_error(error_id, error_message);
	वापस false;
पूर्ण

/* -------------------------------------------------------------------------- */
/* types and local variables */

काष्ठा async_tx_dbr अणु
	u8 ch_addr;
	u16 rpc;
	u16 wpc;
	u16 rest_size;
	u16 sz_queue[CDT0_RPC_MASK + 1];
पूर्ण;

काष्ठा lld_global_vars_t अणु
	bool dim_is_initialized;
	bool mcm_is_initialized;
	काष्ठा dim2_regs __iomem *dim2; /* DIM2 core base address */
	काष्ठा async_tx_dbr atx_dbr;
	u32 fcnt;
	u32 dbr_map[DBR_MAP_SIZE];
पूर्ण;

अटल काष्ठा lld_global_vars_t g = अणु false पूर्ण;

/* -------------------------------------------------------------------------- */

अटल पूर्णांक dbr_get_mask_size(u16 size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		अगर (size <= (DBR_BLOCK_SIZE << i))
			वापस 1 << i;
	वापस 0;
पूर्ण

/**
 * Allocates DBR memory.
 * @param size Allocating memory size.
 * @वापस Offset in DBR memory by success or DBR_SIZE अगर out of memory.
 */
अटल पूर्णांक alloc_dbr(u16 size)
अणु
	पूर्णांक mask_size;
	पूर्णांक i, block_idx = 0;

	अगर (size <= 0)
		वापस DBR_SIZE; /* out of memory */

	mask_size = dbr_get_mask_size(size);
	अगर (mask_size == 0)
		वापस DBR_SIZE; /* out of memory */

	क्रम (i = 0; i < DBR_MAP_SIZE; i++) अणु
		u32 स्थिर blocks = DIV_ROUND_UP(size, DBR_BLOCK_SIZE);
		u32 mask = ~((~(u32)0) << blocks);

		करो अणु
			अगर ((g.dbr_map[i] & mask) == 0) अणु
				g.dbr_map[i] |= mask;
				वापस block_idx * DBR_BLOCK_SIZE;
			पूर्ण
			block_idx += mask_size;
			/* करो shअगरt left with 2 steps in हाल mask_size == 32 */
			mask <<= mask_size - 1;
		पूर्ण जबतक ((mask <<= 1) != 0);
	पूर्ण

	वापस DBR_SIZE; /* out of memory */
पूर्ण

अटल व्योम मुक्त_dbr(पूर्णांक offs, पूर्णांक size)
अणु
	पूर्णांक block_idx = offs / DBR_BLOCK_SIZE;
	u32 स्थिर blocks = DIV_ROUND_UP(size, DBR_BLOCK_SIZE);
	u32 mask = ~((~(u32)0) << blocks);

	mask <<= block_idx % 32;
	g.dbr_map[block_idx / 32] &= ~mask;
पूर्ण

/* -------------------------------------------------------------------------- */

अटल व्योम dim2_transfer_madr(u32 val)
अणु
	ग_लिखोl(val, &g.dim2->MADR);

	/* रुको क्रम transfer completion */
	जबतक ((पढ़ोl(&g.dim2->MCTL) & 1) != 1)
		जारी;

	ग_लिखोl(0, &g.dim2->MCTL);   /* clear transfer complete */
पूर्ण

अटल व्योम dim2_clear_dbr(u16 addr, u16 size)
अणु
	क्रमागत अणु MADR_TB_BIT = 30, MADR_WNR_BIT = 31 पूर्ण;

	u16 स्थिर end_addr = addr + size;
	u32 स्थिर cmd = bit_mask(MADR_WNR_BIT) | bit_mask(MADR_TB_BIT);

	ग_लिखोl(0, &g.dim2->MCTL);   /* clear transfer complete */
	ग_लिखोl(0, &g.dim2->MDAT0);

	क्रम (; addr < end_addr; addr++)
		dim2_transfer_madr(cmd | addr);
पूर्ण

अटल u32 dim2_पढ़ो_ctr(u32 ctr_addr, u16 mdat_idx)
अणु
	dim2_transfer_madr(ctr_addr);

	वापस पढ़ोl((&g.dim2->MDAT0) + mdat_idx);
पूर्ण

अटल व्योम dim2_ग_लिखो_ctr_mask(u32 ctr_addr, स्थिर u32 *mask, स्थिर u32 *value)
अणु
	क्रमागत अणु MADR_WNR_BIT = 31 पूर्ण;

	ग_लिखोl(0, &g.dim2->MCTL);   /* clear transfer complete */

	अगर (mask[0] != 0)
		ग_लिखोl(value[0], &g.dim2->MDAT0);
	अगर (mask[1] != 0)
		ग_लिखोl(value[1], &g.dim2->MDAT1);
	अगर (mask[2] != 0)
		ग_लिखोl(value[2], &g.dim2->MDAT2);
	अगर (mask[3] != 0)
		ग_लिखोl(value[3], &g.dim2->MDAT3);

	ग_लिखोl(mask[0], &g.dim2->MDWE0);
	ग_लिखोl(mask[1], &g.dim2->MDWE1);
	ग_लिखोl(mask[2], &g.dim2->MDWE2);
	ग_लिखोl(mask[3], &g.dim2->MDWE3);

	dim2_transfer_madr(bit_mask(MADR_WNR_BIT) | ctr_addr);
पूर्ण

अटल अंतरभूत व्योम dim2_ग_लिखो_ctr(u32 ctr_addr, स्थिर u32 *value)
अणु
	u32 स्थिर mask[4] = अणु 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण;

	dim2_ग_लिखो_ctr_mask(ctr_addr, mask, value);
पूर्ण

अटल अंतरभूत व्योम dim2_clear_ctr(u32 ctr_addr)
अणु
	u32 स्थिर value[4] = अणु 0, 0, 0, 0 पूर्ण;

	dim2_ग_लिखो_ctr(ctr_addr, value);
पूर्ण

अटल व्योम dim2_configure_cat(u8 cat_base, u8 ch_addr, u8 ch_type,
			       bool पढ़ो_not_ग_लिखो)
अणु
	bool isoc_fce = ch_type == CAT_CT_VAL_ISOC;
	bool sync_mfe = ch_type == CAT_CT_VAL_SYNC;
	u16 स्थिर cat =
		(पढ़ो_not_ग_लिखो << CAT_RNW_BIT) |
		(ch_type << CAT_CT_SHIFT) |
		(ch_addr << CAT_CL_SHIFT) |
		(isoc_fce << CAT_FCE_BIT) |
		(sync_mfe << CAT_MFE_BIT) |
		(false << CAT_MT_BIT) |
		(true << CAT_CE_BIT);
	u8 स्थिर ctr_addr = cat_base + ch_addr / 8;
	u8 स्थिर idx = (ch_addr % 8) / 2;
	u8 स्थिर shअगरt = (ch_addr % 2) * 16;
	u32 mask[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 value[4] = अणु 0, 0, 0, 0 पूर्ण;

	mask[idx] = (u32)0xFFFF << shअगरt;
	value[idx] = cat << shअगरt;
	dim2_ग_लिखो_ctr_mask(ctr_addr, mask, value);
पूर्ण

अटल व्योम dim2_clear_cat(u8 cat_base, u8 ch_addr)
अणु
	u8 स्थिर ctr_addr = cat_base + ch_addr / 8;
	u8 स्थिर idx = (ch_addr % 8) / 2;
	u8 स्थिर shअगरt = (ch_addr % 2) * 16;
	u32 mask[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 value[4] = अणु 0, 0, 0, 0 पूर्ण;

	mask[idx] = (u32)0xFFFF << shअगरt;
	dim2_ग_लिखो_ctr_mask(ctr_addr, mask, value);
पूर्ण

अटल व्योम dim2_configure_cdt(u8 ch_addr, u16 dbr_address, u16 hw_buffer_size,
			       u16 packet_length)
अणु
	u32 cdt[4] = अणु 0, 0, 0, 0 पूर्ण;

	अगर (packet_length)
		cdt[1] = ((packet_length - 1) << CDT1_BS_ISOC_SHIFT);

	cdt[3] =
		((hw_buffer_size - 1) << CDT3_BD_SHIFT) |
		(dbr_address << CDT3_BA_SHIFT);
	dim2_ग_लिखो_ctr(CDT + ch_addr, cdt);
पूर्ण

अटल u16 dim2_rpc(u8 ch_addr)
अणु
	u32 cdt0 = dim2_पढ़ो_ctr(CDT + ch_addr, 0);

	वापस (cdt0 >> CDT0_RPC_SHIFT) & CDT0_RPC_MASK;
पूर्ण

अटल व्योम dim2_clear_cdt(u8 ch_addr)
अणु
	u32 cdt[4] = अणु 0, 0, 0, 0 पूर्ण;

	dim2_ग_लिखो_ctr(CDT + ch_addr, cdt);
पूर्ण

अटल व्योम dim2_configure_adt(u8 ch_addr)
अणु
	u32 adt[4] = अणु 0, 0, 0, 0 पूर्ण;

	adt[0] =
		(true << ADT0_CE_BIT) |
		(true << ADT0_LE_BIT) |
		(0 << ADT0_PG_BIT);

	dim2_ग_लिखो_ctr(ADT + ch_addr, adt);
पूर्ण

अटल व्योम dim2_clear_adt(u8 ch_addr)
अणु
	u32 adt[4] = अणु 0, 0, 0, 0 पूर्ण;

	dim2_ग_लिखो_ctr(ADT + ch_addr, adt);
पूर्ण

अटल व्योम dim2_start_ctrl_async(u8 ch_addr, u8 idx, u32 buf_addr,
				  u16 buffer_size)
अणु
	u8 स्थिर shअगरt = idx * 16;

	u32 mask[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 adt[4] = अणु 0, 0, 0, 0 पूर्ण;

	mask[1] =
		bit_mask(ADT1_PS_BIT + shअगरt) |
		bit_mask(ADT1_RDY_BIT + shअगरt) |
		(ADT1_CTRL_ASYNC_BD_MASK << (ADT1_BD_SHIFT + shअगरt));
	adt[1] =
		(true << (ADT1_PS_BIT + shअगरt)) |
		(true << (ADT1_RDY_BIT + shअगरt)) |
		((buffer_size - 1) << (ADT1_BD_SHIFT + shअगरt));

	mask[idx + 2] = 0xFFFFFFFF;
	adt[idx + 2] = buf_addr;

	dim2_ग_लिखो_ctr_mask(ADT + ch_addr, mask, adt);
पूर्ण

अटल व्योम dim2_start_isoc_sync(u8 ch_addr, u8 idx, u32 buf_addr,
				 u16 buffer_size)
अणु
	u8 स्थिर shअगरt = idx * 16;

	u32 mask[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 adt[4] = अणु 0, 0, 0, 0 पूर्ण;

	mask[1] =
		bit_mask(ADT1_RDY_BIT + shअगरt) |
		(ADT1_ISOC_SYNC_BD_MASK << (ADT1_BD_SHIFT + shअगरt));
	adt[1] =
		(true << (ADT1_RDY_BIT + shअगरt)) |
		((buffer_size - 1) << (ADT1_BD_SHIFT + shअगरt));

	mask[idx + 2] = 0xFFFFFFFF;
	adt[idx + 2] = buf_addr;

	dim2_ग_लिखो_ctr_mask(ADT + ch_addr, mask, adt);
पूर्ण

अटल व्योम dim2_clear_ctram(व्योम)
अणु
	u32 ctr_addr;

	क्रम (ctr_addr = 0; ctr_addr < 0x90; ctr_addr++)
		dim2_clear_ctr(ctr_addr);
पूर्ण

अटल व्योम dim2_configure_channel(
	u8 ch_addr, u8 type, u8 is_tx, u16 dbr_address, u16 hw_buffer_size,
	u16 packet_length)
अणु
	dim2_configure_cdt(ch_addr, dbr_address, hw_buffer_size, packet_length);
	dim2_configure_cat(MLB_CAT, ch_addr, type, is_tx ? 1 : 0);

	dim2_configure_adt(ch_addr);
	dim2_configure_cat(AHB_CAT, ch_addr, type, is_tx ? 0 : 1);

	/* unmask पूर्णांकerrupt क्रम used channel, enable mlb_sys_पूर्णांक[0] पूर्णांकerrupt */
	ग_लिखोl(पढ़ोl(&g.dim2->ACMR0) | bit_mask(ch_addr), &g.dim2->ACMR0);
पूर्ण

अटल व्योम dim2_clear_channel(u8 ch_addr)
अणु
	/* mask पूर्णांकerrupt क्रम used channel, disable mlb_sys_पूर्णांक[0] पूर्णांकerrupt */
	ग_लिखोl(पढ़ोl(&g.dim2->ACMR0) & ~bit_mask(ch_addr), &g.dim2->ACMR0);

	dim2_clear_cat(AHB_CAT, ch_addr);
	dim2_clear_adt(ch_addr);

	dim2_clear_cat(MLB_CAT, ch_addr);
	dim2_clear_cdt(ch_addr);

	/* clear channel status bit */
	ग_लिखोl(bit_mask(ch_addr), &g.dim2->ACSR0);
पूर्ण

/* -------------------------------------------------------------------------- */
/* trace async tx dbr fill state */

अटल अंतरभूत u16 norm_pc(u16 pc)
अणु
	वापस pc & CDT0_RPC_MASK;
पूर्ण

अटल व्योम dbrcnt_init(u8 ch_addr, u16 dbr_size)
अणु
	g.atx_dbr.rest_size = dbr_size;
	g.atx_dbr.rpc = dim2_rpc(ch_addr);
	g.atx_dbr.wpc = g.atx_dbr.rpc;
पूर्ण

अटल व्योम dbrcnt_enq(पूर्णांक buf_sz)
अणु
	g.atx_dbr.rest_size -= buf_sz;
	g.atx_dbr.sz_queue[norm_pc(g.atx_dbr.wpc)] = buf_sz;
	g.atx_dbr.wpc++;
पूर्ण

u16 dim_dbr_space(काष्ठा dim_channel *ch)
अणु
	u16 cur_rpc;
	काष्ठा async_tx_dbr *dbr = &g.atx_dbr;

	अगर (ch->addr != dbr->ch_addr)
		वापस 0xFFFF;

	cur_rpc = dim2_rpc(ch->addr);

	जबतक (norm_pc(dbr->rpc) != cur_rpc) अणु
		dbr->rest_size += dbr->sz_queue[norm_pc(dbr->rpc)];
		dbr->rpc++;
	पूर्ण

	अगर ((u16)(dbr->wpc - dbr->rpc) >= CDT0_RPC_MASK)
		वापस 0;

	वापस dbr->rest_size;
पूर्ण

/* -------------------------------------------------------------------------- */
/* channel state helpers */

अटल व्योम state_init(काष्ठा पूर्णांक_ch_state *state)
अणु
	state->request_counter = 0;
	state->service_counter = 0;

	state->idx1 = 0;
	state->idx2 = 0;
	state->level = 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* macro helper functions */

अटल अंतरभूत bool check_channel_address(u32 ch_address)
अणु
	वापस ch_address > 0 && (ch_address % 2) == 0 &&
	       (ch_address / 2) <= (u32)CAT_CL_MASK;
पूर्ण

अटल अंतरभूत bool check_packet_length(u32 packet_length)
अणु
	u16 स्थिर max_size = ((u16)CDT3_BD_ISOC_MASK + 1u) / ISOC_DBR_FACTOR;

	अगर (packet_length <= 0)
		वापस false; /* too small */

	अगर (packet_length > max_size)
		वापस false; /* too big */

	अगर (packet_length - 1u > (u32)CDT1_BS_ISOC_MASK)
		वापस false; /* too big */

	वापस true;
पूर्ण

अटल अंतरभूत bool check_bytes_per_frame(u32 bytes_per_frame)
अणु
	u16 स्थिर bd_factor = g.fcnt + 2;
	u16 स्थिर max_size = ((u16)CDT3_BD_MASK + 1u) >> bd_factor;

	अगर (bytes_per_frame <= 0)
		वापस false; /* too small */

	अगर (bytes_per_frame > max_size)
		वापस false; /* too big */

	वापस true;
पूर्ण

u16 dim_norm_ctrl_async_buffer_size(u16 buf_size)
अणु
	u16 स्थिर max_size = (u16)ADT1_CTRL_ASYNC_BD_MASK + 1u;

	अगर (buf_size > max_size)
		वापस max_size;

	वापस buf_size;
पूर्ण

अटल अंतरभूत u16 norm_isoc_buffer_size(u16 buf_size, u16 packet_length)
अणु
	u16 n;
	u16 स्थिर max_size = (u16)ADT1_ISOC_SYNC_BD_MASK + 1u;

	अगर (buf_size > max_size)
		buf_size = max_size;

	n = buf_size / packet_length;

	अगर (n < 2u)
		वापस 0; /* too small buffer क्रम given packet_length */

	वापस packet_length * n;
पूर्ण

अटल अंतरभूत u16 norm_sync_buffer_size(u16 buf_size, u16 bytes_per_frame)
अणु
	u16 n;
	u16 स्थिर max_size = (u16)ADT1_ISOC_SYNC_BD_MASK + 1u;
	u32 स्थिर unit = bytes_per_frame << g.fcnt;

	अगर (buf_size > max_size)
		buf_size = max_size;

	n = buf_size / unit;

	अगर (n < 1u)
		वापस 0; /* too small buffer क्रम given bytes_per_frame */

	वापस unit * n;
पूर्ण

अटल व्योम dim2_cleanup(व्योम)
अणु
	/* disable MediaLB */
	ग_लिखोl(false << MLBC0_MLBEN_BIT, &g.dim2->MLBC0);

	dim2_clear_ctram();

	/* disable mlb_पूर्णांक पूर्णांकerrupt */
	ग_लिखोl(0, &g.dim2->MIEN);

	/* clear status क्रम all dma channels */
	ग_लिखोl(0xFFFFFFFF, &g.dim2->ACSR0);
	ग_लिखोl(0xFFFFFFFF, &g.dim2->ACSR1);

	/* mask पूर्णांकerrupts क्रम all channels */
	ग_लिखोl(0, &g.dim2->ACMR0);
	ग_लिखोl(0, &g.dim2->ACMR1);
पूर्ण

अटल व्योम dim2_initialize(bool enable_6pin, u8 mlb_घड़ी)
अणु
	dim2_cleanup();

	/* configure and enable MediaLB */
	ग_लिखोl(enable_6pin << MLBC0_MLBPEN_BIT |
	       mlb_घड़ी << MLBC0_MLBCLK_SHIFT |
	       g.fcnt << MLBC0_FCNT_SHIFT |
	       true << MLBC0_MLBEN_BIT,
	       &g.dim2->MLBC0);

	/* activate all HBI channels */
	ग_लिखोl(0xFFFFFFFF, &g.dim2->HCMR0);
	ग_लिखोl(0xFFFFFFFF, &g.dim2->HCMR1);

	/* enable HBI */
	ग_लिखोl(bit_mask(HCTL_EN_BIT), &g.dim2->HCTL);

	/* configure DMA */
	ग_लिखोl(ACTL_DMA_MODE_VAL_DMA_MODE_1 << ACTL_DMA_MODE_BIT |
	       true << ACTL_SCE_BIT, &g.dim2->ACTL);
पूर्ण

अटल bool dim2_is_mlb_locked(व्योम)
अणु
	u32 स्थिर mask0 = bit_mask(MLBC0_MLBLK_BIT);
	u32 स्थिर mask1 = bit_mask(MLBC1_CLKMERR_BIT) |
			  bit_mask(MLBC1_LOCKERR_BIT);
	u32 स्थिर c1 = पढ़ोl(&g.dim2->MLBC1);
	u32 स्थिर nda_mask = (u32)MLBC1_NDA_MASK << MLBC1_NDA_SHIFT;

	ग_लिखोl(c1 & nda_mask, &g.dim2->MLBC1);
	वापस (पढ़ोl(&g.dim2->MLBC1) & mask1) == 0 &&
	       (पढ़ोl(&g.dim2->MLBC0) & mask0) != 0;
पूर्ण

/* -------------------------------------------------------------------------- */
/* channel help routines */

अटल अंतरभूत bool service_channel(u8 ch_addr, u8 idx)
अणु
	u8 स्थिर shअगरt = idx * 16;
	u32 स्थिर adt1 = dim2_पढ़ो_ctr(ADT + ch_addr, 1);
	u32 mask[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 adt_w[4] = अणु 0, 0, 0, 0 पूर्ण;

	अगर (((adt1 >> (ADT1_DNE_BIT + shअगरt)) & 1) == 0)
		वापस false;

	mask[1] =
		bit_mask(ADT1_DNE_BIT + shअगरt) |
		bit_mask(ADT1_ERR_BIT + shअगरt) |
		bit_mask(ADT1_RDY_BIT + shअगरt);
	dim2_ग_लिखो_ctr_mask(ADT + ch_addr, mask, adt_w);

	/* clear channel status bit */
	ग_लिखोl(bit_mask(ch_addr), &g.dim2->ACSR0);

	वापस true;
पूर्ण

/* -------------------------------------------------------------------------- */
/* channel init routines */

अटल व्योम isoc_init(काष्ठा dim_channel *ch, u8 ch_addr, u16 packet_length)
अणु
	state_init(&ch->state);

	ch->addr = ch_addr;

	ch->packet_length = packet_length;
	ch->bytes_per_frame = 0;
	ch->करोne_sw_buffers_number = 0;
पूर्ण

अटल व्योम sync_init(काष्ठा dim_channel *ch, u8 ch_addr, u16 bytes_per_frame)
अणु
	state_init(&ch->state);

	ch->addr = ch_addr;

	ch->packet_length = 0;
	ch->bytes_per_frame = bytes_per_frame;
	ch->करोne_sw_buffers_number = 0;
पूर्ण

अटल व्योम channel_init(काष्ठा dim_channel *ch, u8 ch_addr)
अणु
	state_init(&ch->state);

	ch->addr = ch_addr;

	ch->packet_length = 0;
	ch->bytes_per_frame = 0;
	ch->करोne_sw_buffers_number = 0;
पूर्ण

/* वापसs true अगर channel पूर्णांकerrupt state is cleared */
अटल bool channel_service_पूर्णांकerrupt(काष्ठा dim_channel *ch)
अणु
	काष्ठा पूर्णांक_ch_state *स्थिर state = &ch->state;

	अगर (!service_channel(ch->addr, state->idx2))
		वापस false;

	state->idx2 ^= 1;
	state->request_counter++;
	वापस true;
पूर्ण

अटल bool channel_start(काष्ठा dim_channel *ch, u32 buf_addr, u16 buf_size)
अणु
	काष्ठा पूर्णांक_ch_state *स्थिर state = &ch->state;

	अगर (buf_size <= 0)
		वापस dim_on_error(DIM_ERR_BAD_BUFFER_SIZE, "Bad buffer size");

	अगर (ch->packet_length == 0 && ch->bytes_per_frame == 0 &&
	    buf_size != dim_norm_ctrl_async_buffer_size(buf_size))
		वापस dim_on_error(DIM_ERR_BAD_BUFFER_SIZE,
				    "Bad control/async buffer size");

	अगर (ch->packet_length &&
	    buf_size != norm_isoc_buffer_size(buf_size, ch->packet_length))
		वापस dim_on_error(DIM_ERR_BAD_BUFFER_SIZE,
				    "Bad isochronous buffer size");

	अगर (ch->bytes_per_frame &&
	    buf_size != norm_sync_buffer_size(buf_size, ch->bytes_per_frame))
		वापस dim_on_error(DIM_ERR_BAD_BUFFER_SIZE,
				    "Bad synchronous buffer size");

	अगर (state->level >= 2u)
		वापस dim_on_error(DIM_ERR_OVERFLOW, "Channel overflow");

	++state->level;

	अगर (ch->addr == g.atx_dbr.ch_addr)
		dbrcnt_enq(buf_size);

	अगर (ch->packet_length || ch->bytes_per_frame)
		dim2_start_isoc_sync(ch->addr, state->idx1, buf_addr, buf_size);
	अन्यथा
		dim2_start_ctrl_async(ch->addr, state->idx1, buf_addr,
				      buf_size);
	state->idx1 ^= 1;

	वापस true;
पूर्ण

अटल u8 channel_service(काष्ठा dim_channel *ch)
अणु
	काष्ठा पूर्णांक_ch_state *स्थिर state = &ch->state;

	अगर (state->service_counter != state->request_counter) अणु
		state->service_counter++;
		अगर (state->level == 0)
			वापस DIM_ERR_UNDERFLOW;

		--state->level;
		ch->करोne_sw_buffers_number++;
	पूर्ण

	वापस DIM_NO_ERROR;
पूर्ण

अटल bool channel_detach_buffers(काष्ठा dim_channel *ch, u16 buffers_number)
अणु
	अगर (buffers_number > ch->करोne_sw_buffers_number)
		वापस dim_on_error(DIM_ERR_UNDERFLOW, "Channel underflow");

	ch->करोne_sw_buffers_number -= buffers_number;
	वापस true;
पूर्ण

/* -------------------------------------------------------------------------- */
/* API */

u8 dim_startup(काष्ठा dim2_regs __iomem *dim_base_address, u32 mlb_घड़ी,
	       u32 fcnt)
अणु
	g.dim_is_initialized = false;

	अगर (!dim_base_address)
		वापस DIM_INIT_ERR_DIM_ADDR;

	/* MediaLB घड़ी: 0 - 256 fs, 1 - 512 fs, 2 - 1024 fs, 3 - 2048 fs */
	/* MediaLB घड़ी: 4 - 3072 fs, 5 - 4096 fs, 6 - 6144 fs, 7 - 8192 fs */
	अगर (mlb_घड़ी >= 8)
		वापस DIM_INIT_ERR_MLB_CLOCK;

	अगर (fcnt > MLBC0_FCNT_MAX_VAL)
		वापस DIM_INIT_ERR_MLB_CLOCK;

	g.dim2 = dim_base_address;
	g.fcnt = fcnt;
	g.dbr_map[0] = 0;
	g.dbr_map[1] = 0;

	dim2_initialize(mlb_घड़ी >= 3, mlb_घड़ी);

	g.dim_is_initialized = true;

	वापस DIM_NO_ERROR;
पूर्ण

व्योम dim_shutकरोwn(व्योम)
अणु
	g.dim_is_initialized = false;
	dim2_cleanup();
पूर्ण

bool dim_get_lock_state(व्योम)
अणु
	वापस dim2_is_mlb_locked();
पूर्ण

अटल u8 init_ctrl_async(काष्ठा dim_channel *ch, u8 type, u8 is_tx,
			  u16 ch_address, u16 hw_buffer_size)
अणु
	अगर (!g.dim_is_initialized || !ch)
		वापस DIM_ERR_DRIVER_NOT_INITIALIZED;

	अगर (!check_channel_address(ch_address))
		वापस DIM_INIT_ERR_CHANNEL_ADDRESS;

	अगर (!ch->dbr_size)
		ch->dbr_size = ROUND_UP_TO(hw_buffer_size, DBR_BLOCK_SIZE);
	ch->dbr_addr = alloc_dbr(ch->dbr_size);
	अगर (ch->dbr_addr >= DBR_SIZE)
		वापस DIM_INIT_ERR_OUT_OF_MEMORY;

	channel_init(ch, ch_address / 2);

	dim2_configure_channel(ch->addr, type, is_tx,
			       ch->dbr_addr, ch->dbr_size, 0);

	वापस DIM_NO_ERROR;
पूर्ण

व्योम dim_service_mlb_पूर्णांक_irq(व्योम)
अणु
	ग_लिखोl(0, &g.dim2->MS0);
	ग_लिखोl(0, &g.dim2->MS1);
पूर्ण

/**
 * Retrieves maximal possible correct buffer size क्रम isochronous data type
 * conक्रमm to given packet length and not bigger than given buffer size.
 *
 * Returns non-zero correct buffer size or zero by error.
 */
u16 dim_norm_isoc_buffer_size(u16 buf_size, u16 packet_length)
अणु
	अगर (!check_packet_length(packet_length))
		वापस 0;

	वापस norm_isoc_buffer_size(buf_size, packet_length);
पूर्ण

/**
 * Retrieves maximal possible correct buffer size क्रम synchronous data type
 * conक्रमm to given bytes per frame and not bigger than given buffer size.
 *
 * Returns non-zero correct buffer size or zero by error.
 */
u16 dim_norm_sync_buffer_size(u16 buf_size, u16 bytes_per_frame)
अणु
	अगर (!check_bytes_per_frame(bytes_per_frame))
		वापस 0;

	वापस norm_sync_buffer_size(buf_size, bytes_per_frame);
पूर्ण

u8 dim_init_control(काष्ठा dim_channel *ch, u8 is_tx, u16 ch_address,
		    u16 max_buffer_size)
अणु
	वापस init_ctrl_async(ch, CAT_CT_VAL_CONTROL, is_tx, ch_address,
			       max_buffer_size);
पूर्ण

u8 dim_init_async(काष्ठा dim_channel *ch, u8 is_tx, u16 ch_address,
		  u16 max_buffer_size)
अणु
	u8 ret = init_ctrl_async(ch, CAT_CT_VAL_ASYNC, is_tx, ch_address,
				 max_buffer_size);

	अगर (is_tx && !g.atx_dbr.ch_addr) अणु
		g.atx_dbr.ch_addr = ch->addr;
		dbrcnt_init(ch->addr, ch->dbr_size);
		ग_लिखोl(bit_mask(20), &g.dim2->MIEN);
	पूर्ण

	वापस ret;
पूर्ण

u8 dim_init_isoc(काष्ठा dim_channel *ch, u8 is_tx, u16 ch_address,
		 u16 packet_length)
अणु
	अगर (!g.dim_is_initialized || !ch)
		वापस DIM_ERR_DRIVER_NOT_INITIALIZED;

	अगर (!check_channel_address(ch_address))
		वापस DIM_INIT_ERR_CHANNEL_ADDRESS;

	अगर (!check_packet_length(packet_length))
		वापस DIM_ERR_BAD_CONFIG;

	अगर (!ch->dbr_size)
		ch->dbr_size = packet_length * ISOC_DBR_FACTOR;
	ch->dbr_addr = alloc_dbr(ch->dbr_size);
	अगर (ch->dbr_addr >= DBR_SIZE)
		वापस DIM_INIT_ERR_OUT_OF_MEMORY;

	isoc_init(ch, ch_address / 2, packet_length);

	dim2_configure_channel(ch->addr, CAT_CT_VAL_ISOC, is_tx, ch->dbr_addr,
			       ch->dbr_size, packet_length);

	वापस DIM_NO_ERROR;
पूर्ण

u8 dim_init_sync(काष्ठा dim_channel *ch, u8 is_tx, u16 ch_address,
		 u16 bytes_per_frame)
अणु
	u16 bd_factor = g.fcnt + 2;

	अगर (!g.dim_is_initialized || !ch)
		वापस DIM_ERR_DRIVER_NOT_INITIALIZED;

	अगर (!check_channel_address(ch_address))
		वापस DIM_INIT_ERR_CHANNEL_ADDRESS;

	अगर (!check_bytes_per_frame(bytes_per_frame))
		वापस DIM_ERR_BAD_CONFIG;

	अगर (!ch->dbr_size)
		ch->dbr_size = bytes_per_frame << bd_factor;
	ch->dbr_addr = alloc_dbr(ch->dbr_size);
	अगर (ch->dbr_addr >= DBR_SIZE)
		वापस DIM_INIT_ERR_OUT_OF_MEMORY;

	sync_init(ch, ch_address / 2, bytes_per_frame);

	dim2_clear_dbr(ch->dbr_addr, ch->dbr_size);
	dim2_configure_channel(ch->addr, CAT_CT_VAL_SYNC, is_tx,
			       ch->dbr_addr, ch->dbr_size, 0);

	वापस DIM_NO_ERROR;
पूर्ण

u8 dim_destroy_channel(काष्ठा dim_channel *ch)
अणु
	अगर (!g.dim_is_initialized || !ch)
		वापस DIM_ERR_DRIVER_NOT_INITIALIZED;

	अगर (ch->addr == g.atx_dbr.ch_addr) अणु
		ग_लिखोl(0, &g.dim2->MIEN);
		g.atx_dbr.ch_addr = 0;
	पूर्ण

	dim2_clear_channel(ch->addr);
	अगर (ch->dbr_addr < DBR_SIZE)
		मुक्त_dbr(ch->dbr_addr, ch->dbr_size);
	ch->dbr_addr = DBR_SIZE;

	वापस DIM_NO_ERROR;
पूर्ण

व्योम dim_service_ahb_पूर्णांक_irq(काष्ठा dim_channel *स्थिर *channels)
अणु
	bool state_changed;

	अगर (!g.dim_is_initialized) अणु
		dim_on_error(DIM_ERR_DRIVER_NOT_INITIALIZED,
			     "DIM is not initialized");
		वापस;
	पूर्ण

	अगर (!channels) अणु
		dim_on_error(DIM_ERR_DRIVER_NOT_INITIALIZED, "Bad channels");
		वापस;
	पूर्ण

	/*
	 * Use जबतक-loop and a flag to make sure the age is changed back at
	 * least once, otherwise the पूर्णांकerrupt may never come अगर CPU generates
	 * पूर्णांकerrupt on changing age.
	 * This cycle runs not more than number of channels, because
	 * channel_service_पूर्णांकerrupt() routine करोesn't start the channel again.
	 */
	करो अणु
		काष्ठा dim_channel *स्थिर *ch = channels;

		state_changed = false;

		जबतक (*ch) अणु
			state_changed |= channel_service_पूर्णांकerrupt(*ch);
			++ch;
		पूर्ण
	पूर्ण जबतक (state_changed);
पूर्ण

u8 dim_service_channel(काष्ठा dim_channel *ch)
अणु
	अगर (!g.dim_is_initialized || !ch)
		वापस DIM_ERR_DRIVER_NOT_INITIALIZED;

	वापस channel_service(ch);
पूर्ण

काष्ठा dim_ch_state_t *dim_get_channel_state(काष्ठा dim_channel *ch,
					     काष्ठा dim_ch_state_t *state_ptr)
अणु
	अगर (!ch || !state_ptr)
		वापस शून्य;

	state_ptr->पढ़ोy = ch->state.level < 2;
	state_ptr->करोne_buffers = ch->करोne_sw_buffers_number;

	वापस state_ptr;
पूर्ण

bool dim_enqueue_buffer(काष्ठा dim_channel *ch, u32 buffer_addr,
			u16 buffer_size)
अणु
	अगर (!ch)
		वापस dim_on_error(DIM_ERR_DRIVER_NOT_INITIALIZED,
				    "Bad channel");

	वापस channel_start(ch, buffer_addr, buffer_size);
पूर्ण

bool dim_detach_buffers(काष्ठा dim_channel *ch, u16 buffers_number)
अणु
	अगर (!ch)
		वापस dim_on_error(DIM_ERR_DRIVER_NOT_INITIALIZED,
				    "Bad channel");

	वापस channel_detach_buffers(ch, buffers_number);
पूर्ण
