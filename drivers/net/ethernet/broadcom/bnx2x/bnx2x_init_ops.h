<शैली गुरु>
/* bnx2x_init_ops.h: Qlogic Everest network driver.
 *               Static functions needed during the initialization.
 *               This file is "included" in bnx2x_मुख्य.c.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Vladislav Zolotarov
 */

#अगर_अघोषित BNX2X_INIT_OPS_H
#घोषणा BNX2X_INIT_OPS_H


#अगर_अघोषित BP_ILT
#घोषणा BP_ILT(bp)	शून्य
#पूर्ण_अगर

#अगर_अघोषित BP_FUNC
#घोषणा BP_FUNC(bp)	0
#पूर्ण_अगर

#अगर_अघोषित BP_PORT
#घोषणा BP_PORT(bp)	0
#पूर्ण_अगर

#अगर_अघोषित BNX2X_ILT_FREE
#घोषणा BNX2X_ILT_FREE(x, y, sz)
#पूर्ण_अगर

#अगर_अघोषित BNX2X_ILT_ZALLOC
#घोषणा BNX2X_ILT_ZALLOC(x, y, sz)
#पूर्ण_अगर

#अगर_अघोषित ILOG2
#घोषणा ILOG2(x)	x
#पूर्ण_अगर

अटल पूर्णांक bnx2x_gunzip(काष्ठा bnx2x *bp, स्थिर u8 *zbuf, पूर्णांक len);
अटल व्योम bnx2x_reg_wr_ind(काष्ठा bnx2x *bp, u32 addr, u32 val);
अटल व्योम bnx2x_ग_लिखो_dmae_phys_len(काष्ठा bnx2x *bp,
				      dma_addr_t phys_addr, u32 addr,
				      u32 len);

अटल व्योम bnx2x_init_str_wr(काष्ठा bnx2x *bp, u32 addr,
			      स्थिर u32 *data, u32 len)
अणु
	u32 i;

	क्रम (i = 0; i < len; i++)
		REG_WR(bp, addr + i*4, data[i]);
पूर्ण

अटल व्योम bnx2x_init_ind_wr(काष्ठा bnx2x *bp, u32 addr,
			      स्थिर u32 *data, u32 len)
अणु
	u32 i;

	क्रम (i = 0; i < len; i++)
		bnx2x_reg_wr_ind(bp, addr + i*4, data[i]);
पूर्ण

अटल व्योम bnx2x_ग_लिखो_big_buf(काष्ठा bnx2x *bp, u32 addr, u32 len,
				u8 wb)
अणु
	अगर (bp->dmae_पढ़ोy)
		bnx2x_ग_लिखो_dmae_phys_len(bp, GUNZIP_PHYS(bp), addr, len);

	/* in E1 chips BIOS initiated ZLR may पूर्णांकerrupt widebus ग_लिखोs */
	अन्यथा अगर (wb && CHIP_IS_E1(bp))
		bnx2x_init_ind_wr(bp, addr, GUNZIP_BUF(bp), len);

	/* in later chips PXP root complex handles BIOS ZLR w/o पूर्णांकerrupting */
	अन्यथा
		bnx2x_init_str_wr(bp, addr, GUNZIP_BUF(bp), len);
पूर्ण

अटल व्योम bnx2x_init_fill(काष्ठा bnx2x *bp, u32 addr, पूर्णांक fill,
			    u32 len, u8 wb)
अणु
	u32 buf_len = (((len*4) > FW_BUF_SIZE) ? FW_BUF_SIZE : (len*4));
	u32 buf_len32 = buf_len/4;
	u32 i;

	स_रखो(GUNZIP_BUF(bp), (u8)fill, buf_len);

	क्रम (i = 0; i < len; i += buf_len32) अणु
		u32 cur_len = min(buf_len32, len - i);

		bnx2x_ग_लिखो_big_buf(bp, addr + i*4, cur_len, wb);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_ग_लिखो_big_buf_wb(काष्ठा bnx2x *bp, u32 addr, u32 len)
अणु
	अगर (bp->dmae_पढ़ोy)
		bnx2x_ग_लिखो_dmae_phys_len(bp, GUNZIP_PHYS(bp), addr, len);

	/* in E1 chips BIOS initiated ZLR may पूर्णांकerrupt widebus ग_लिखोs */
	अन्यथा अगर (CHIP_IS_E1(bp))
		bnx2x_init_ind_wr(bp, addr, GUNZIP_BUF(bp), len);

	/* in later chips PXP root complex handles BIOS ZLR w/o पूर्णांकerrupting */
	अन्यथा
		bnx2x_init_str_wr(bp, addr, GUNZIP_BUF(bp), len);
पूर्ण

अटल व्योम bnx2x_init_wr_64(काष्ठा bnx2x *bp, u32 addr,
			     स्थिर u32 *data, u32 len64)
अणु
	u32 buf_len32 = FW_BUF_SIZE/4;
	u32 len = len64*2;
	u64 data64 = 0;
	u32 i;

	/* 64 bit value is in a blob: first low DWORD, then high DWORD */
	data64 = HILO_U64((*(data + 1)), (*data));

	len64 = min((u32)(FW_BUF_SIZE/8), len64);
	क्रम (i = 0; i < len64; i++) अणु
		u64 *pdata = ((u64 *)(GUNZIP_BUF(bp))) + i;

		*pdata = data64;
	पूर्ण

	क्रम (i = 0; i < len; i += buf_len32) अणु
		u32 cur_len = min(buf_len32, len - i);

		bnx2x_ग_लिखो_big_buf_wb(bp, addr + i*4, cur_len);
	पूर्ण
पूर्ण

/*********************************************************
   There are dअगरferent blobs क्रम each PRAM section.
   In addition, each blob ग_लिखो operation is भागided पूर्णांकo a few operations
   in order to decrease the amount of phys. contiguous buffer needed.
   Thus, when we select a blob the address may be with some offset
   from the beginning of PRAM section.
   The same holds क्रम the INT_TABLE sections.
**********************************************************/
#घोषणा IF_IS_INT_TABLE_ADDR(base, addr) \
			अगर (((base) <= (addr)) && ((base) + 0x400 >= (addr)))

#घोषणा IF_IS_PRAM_ADDR(base, addr) \
			अगर (((base) <= (addr)) && ((base) + 0x40000 >= (addr)))

अटल स्थिर u8 *bnx2x_sel_blob(काष्ठा bnx2x *bp, u32 addr,
				स्थिर u8 *data)
अणु
	IF_IS_INT_TABLE_ADDR(TSEM_REG_INT_TABLE, addr)
		data = INIT_TSEM_INT_TABLE_DATA(bp);
	अन्यथा
		IF_IS_INT_TABLE_ADDR(CSEM_REG_INT_TABLE, addr)
			data = INIT_CSEM_INT_TABLE_DATA(bp);
	अन्यथा
		IF_IS_INT_TABLE_ADDR(USEM_REG_INT_TABLE, addr)
			data = INIT_USEM_INT_TABLE_DATA(bp);
	अन्यथा
		IF_IS_INT_TABLE_ADDR(XSEM_REG_INT_TABLE, addr)
			data = INIT_XSEM_INT_TABLE_DATA(bp);
	अन्यथा
		IF_IS_PRAM_ADDR(TSEM_REG_PRAM, addr)
			data = INIT_TSEM_PRAM_DATA(bp);
	अन्यथा
		IF_IS_PRAM_ADDR(CSEM_REG_PRAM, addr)
			data = INIT_CSEM_PRAM_DATA(bp);
	अन्यथा
		IF_IS_PRAM_ADDR(USEM_REG_PRAM, addr)
			data = INIT_USEM_PRAM_DATA(bp);
	अन्यथा
		IF_IS_PRAM_ADDR(XSEM_REG_PRAM, addr)
			data = INIT_XSEM_PRAM_DATA(bp);

	वापस data;
पूर्ण

अटल व्योम bnx2x_init_wr_wb(काष्ठा bnx2x *bp, u32 addr,
			     स्थिर u32 *data, u32 len)
अणु
	अगर (bp->dmae_पढ़ोy)
		VIRT_WR_DMAE_LEN(bp, data, addr, len, 0);

	/* in E1 chips BIOS initiated ZLR may पूर्णांकerrupt widebus ग_लिखोs */
	अन्यथा अगर (CHIP_IS_E1(bp))
		bnx2x_init_ind_wr(bp, addr, data, len);

	/* in later chips PXP root complex handles BIOS ZLR w/o पूर्णांकerrupting */
	अन्यथा
		bnx2x_init_str_wr(bp, addr, data, len);
पूर्ण

अटल व्योम bnx2x_wr_64(काष्ठा bnx2x *bp, u32 reg, u32 val_lo,
			u32 val_hi)
अणु
	u32 wb_ग_लिखो[2];

	wb_ग_लिखो[0] = val_lo;
	wb_ग_लिखो[1] = val_hi;
	REG_WR_DMAE_LEN(bp, reg, wb_ग_लिखो, 2);
पूर्ण
अटल व्योम bnx2x_init_wr_zp(काष्ठा bnx2x *bp, u32 addr, u32 len,
			     u32 blob_off)
अणु
	स्थिर u8 *data = शून्य;
	पूर्णांक rc;
	u32 i;

	data = bnx2x_sel_blob(bp, addr, data) + blob_off*4;

	rc = bnx2x_gunzip(bp, data, len);
	अगर (rc)
		वापस;

	/* gunzip_outlen is in dwords */
	len = GUNZIP_OUTLEN(bp);
	क्रम (i = 0; i < len; i++)
		((u32 *)GUNZIP_BUF(bp))[i] = (__क्रमce u32)
				cpu_to_le32(((u32 *)GUNZIP_BUF(bp))[i]);

	bnx2x_ग_लिखो_big_buf_wb(bp, addr, len);
पूर्ण

अटल व्योम bnx2x_init_block(काष्ठा bnx2x *bp, u32 block, u32 stage)
अणु
	u16 op_start =
		INIT_OPS_OFFSETS(bp)[BLOCK_OPS_IDX(block, stage,
						     STAGE_START)];
	u16 op_end =
		INIT_OPS_OFFSETS(bp)[BLOCK_OPS_IDX(block, stage,
						     STAGE_END)];
	स्थिर जोड़ init_op *op;
	u32 op_idx, op_type, addr, len;
	स्थिर u32 *data, *data_base;

	/* If empty block */
	अगर (op_start == op_end)
		वापस;

	data_base = INIT_DATA(bp);

	क्रम (op_idx = op_start; op_idx < op_end; op_idx++) अणु

		op = (स्थिर जोड़ init_op *)&(INIT_OPS(bp)[op_idx]);
		/* Get generic data */
		op_type = op->raw.op;
		addr = op->raw.offset;
		/* Get data that's used क्रम OP_SW, OP_WB, OP_FW, OP_ZP and
		 * OP_WR64 (we assume that op_arr_ग_लिखो and op_ग_लिखो have the
		 * same काष्ठाure).
		 */
		len = op->arr_wr.data_len;
		data = data_base + op->arr_wr.data_off;

		चयन (op_type) अणु
		हाल OP_RD:
			REG_RD(bp, addr);
			अवरोध;
		हाल OP_WR:
			REG_WR(bp, addr, op->ग_लिखो.val);
			अवरोध;
		हाल OP_SW:
			bnx2x_init_str_wr(bp, addr, data, len);
			अवरोध;
		हाल OP_WB:
			bnx2x_init_wr_wb(bp, addr, data, len);
			अवरोध;
		हाल OP_ZR:
			bnx2x_init_fill(bp, addr, 0, op->zero.len, 0);
			अवरोध;
		हाल OP_WB_ZR:
			bnx2x_init_fill(bp, addr, 0, op->zero.len, 1);
			अवरोध;
		हाल OP_ZP:
			bnx2x_init_wr_zp(bp, addr, len,
					 op->arr_wr.data_off);
			अवरोध;
		हाल OP_WR_64:
			bnx2x_init_wr_64(bp, addr, data, len);
			अवरोध;
		हाल OP_IF_MODE_AND:
			/* अगर any of the flags करोesn't match, skip the
			 * conditional block.
			 */
			अगर ((INIT_MODE_FLAGS(bp) &
				op->अगर_mode.mode_bit_map) !=
				op->अगर_mode.mode_bit_map)
				op_idx += op->अगर_mode.cmd_offset;
			अवरोध;
		हाल OP_IF_MODE_OR:
			/* अगर all the flags करोn't match, skip the conditional
			 * block.
			 */
			अगर ((INIT_MODE_FLAGS(bp) &
				op->अगर_mode.mode_bit_map) == 0)
				op_idx += op->अगर_mode.cmd_offset;
			अवरोध;
		शेष:
			/* Should never get here! */

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण


/****************************************************************************
* PXP Arbiter
****************************************************************************/
/*
 * This code configures the PCI पढ़ो/ग_लिखो arbiter
 * which implements a weighted round robin
 * between the भव queues in the chip.
 *
 * The values were derived क्रम each PCI max payload and max request size.
 * since max payload and max request size are only known at run समय,
 * this is करोne as a separate init stage.
 */

#घोषणा NUM_WR_Q			13
#घोषणा NUM_RD_Q			29
#घोषणा MAX_RD_ORD			3
#घोषणा MAX_WR_ORD			2

/* configuration क्रम one arbiter queue */
काष्ठा arb_line अणु
	पूर्णांक l;
	पूर्णांक add;
	पूर्णांक ubound;
पूर्ण;

/* derived configuration क्रम each पढ़ो queue क्रम each max request size */
अटल स्थिर काष्ठा arb_line पढ़ो_arb_data[NUM_RD_Q][MAX_RD_ORD + 1] = अणु
/* 1 */	अणु अणु8, 64, 25पूर्ण, अणु16, 64, 25पूर्ण, अणु32, 64, 25पूर्ण, अणु64, 64, 41पूर्ण पूर्ण,
	अणु अणु4, 8,  4पूर्ण,  अणु4,  8,  4पूर्ण,  अणु4,  8,  4पूर्ण,  अणु4,  8,  4पूर्ण  पूर्ण,
	अणु अणु4, 3,  3पूर्ण,  अणु4,  3,  3पूर्ण,  अणु4,  3,  3पूर्ण,  अणु4,  3,  3पूर्ण  पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु16, 3,  11पूर्ण, अणु16, 3,  11पूर्ण पूर्ण,
	अणु अणु8, 64, 25पूर्ण, अणु16, 64, 25पूर्ण, अणु32, 64, 25पूर्ण, अणु64, 64, 41पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु64, 3,  41पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु64, 3,  41पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु64, 3,  41पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु64, 3,  41पूर्ण पूर्ण,
/* 10 */अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 64, 6पूर्ण,  अणु16, 64, 11पूर्ण, अणु32, 64, 21पूर्ण, अणु32, 64, 21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
/* 20 */अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 3,  6पूर्ण,  अणु16, 3,  11पूर्ण, अणु32, 3,  21पूर्ण, अणु32, 3,  21पूर्ण पूर्ण,
	अणु अणु8, 64, 25पूर्ण, अणु16, 64, 41पूर्ण, अणु32, 64, 81पूर्ण, अणु64, 64, 120पूर्ण पूर्ण
पूर्ण;

/* derived configuration क्रम each ग_लिखो queue क्रम each max request size */
अटल स्थिर काष्ठा arb_line ग_लिखो_arb_data[NUM_WR_Q][MAX_WR_ORD + 1] = अणु
/* 1 */	अणु अणु4, 6,  3पूर्ण,  अणु4,  6,  3पूर्ण,  अणु4,  6,  3पूर्ण पूर्ण,
	अणु अणु4, 2,  3पूर्ण,  अणु4,  2,  3पूर्ण,  अणु4,  2,  3पूर्ण पूर्ण,
	अणु अणु8, 2,  6पूर्ण,  अणु16, 2,  11पूर्ण, अणु16, 2,  11पूर्ण पूर्ण,
	अणु अणु8, 2,  6पूर्ण,  अणु16, 2,  11पूर्ण, अणु32, 2,  21पूर्ण पूर्ण,
	अणु अणु8, 2,  6पूर्ण,  अणु16, 2,  11पूर्ण, अणु32, 2,  21पूर्ण पूर्ण,
	अणु अणु8, 2,  6पूर्ण,  अणु16, 2,  11पूर्ण, अणु32, 2,  21पूर्ण पूर्ण,
	अणु अणु8, 64, 25पूर्ण, अणु16, 64, 25पूर्ण, अणु32, 64, 25पूर्ण पूर्ण,
	अणु अणु8, 2,  6पूर्ण,  अणु16, 2,  11पूर्ण, अणु16, 2,  11पूर्ण पूर्ण,
	अणु अणु8, 2,  6पूर्ण,  अणु16, 2,  11पूर्ण, अणु16, 2,  11पूर्ण पूर्ण,
/* 10 */अणु अणु8, 9,  6पूर्ण,  अणु16, 9,  11पूर्ण, अणु32, 9,  21पूर्ण पूर्ण,
	अणु अणु8, 47, 19पूर्ण, अणु16, 47, 19पूर्ण, अणु32, 47, 21पूर्ण पूर्ण,
	अणु अणु8, 9,  6पूर्ण,  अणु16, 9,  11पूर्ण, अणु16, 9,  11पूर्ण पूर्ण,
	अणु अणु8, 64, 25पूर्ण, अणु16, 64, 41पूर्ण, अणु32, 64, 81पूर्ण पूर्ण
पूर्ण;

/* रेजिस्टर addresses क्रम पढ़ो queues */
अटल स्थिर काष्ठा arb_line पढ़ो_arb_addr[NUM_RD_Q-1] = अणु
/* 1 */	अणुPXP2_REG_RQ_BW_RD_L0, PXP2_REG_RQ_BW_RD_ADD0,
		PXP2_REG_RQ_BW_RD_UBOUND0पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L1, PXP2_REG_PSWRQ_BW_ADD1,
		PXP2_REG_PSWRQ_BW_UB1पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L2, PXP2_REG_PSWRQ_BW_ADD2,
		PXP2_REG_PSWRQ_BW_UB2पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L3, PXP2_REG_PSWRQ_BW_ADD3,
		PXP2_REG_PSWRQ_BW_UB3पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L4, PXP2_REG_RQ_BW_RD_ADD4,
		PXP2_REG_RQ_BW_RD_UBOUND4पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L5, PXP2_REG_RQ_BW_RD_ADD5,
		PXP2_REG_RQ_BW_RD_UBOUND5पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L6, PXP2_REG_PSWRQ_BW_ADD6,
		PXP2_REG_PSWRQ_BW_UB6पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L7, PXP2_REG_PSWRQ_BW_ADD7,
		PXP2_REG_PSWRQ_BW_UB7पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L8, PXP2_REG_PSWRQ_BW_ADD8,
		PXP2_REG_PSWRQ_BW_UB8पूर्ण,
/* 10 */अणुPXP2_REG_PSWRQ_BW_L9, PXP2_REG_PSWRQ_BW_ADD9,
		PXP2_REG_PSWRQ_BW_UB9पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L10, PXP2_REG_PSWRQ_BW_ADD10,
		PXP2_REG_PSWRQ_BW_UB10पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L11, PXP2_REG_PSWRQ_BW_ADD11,
		PXP2_REG_PSWRQ_BW_UB11पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L12, PXP2_REG_RQ_BW_RD_ADD12,
		PXP2_REG_RQ_BW_RD_UBOUND12पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L13, PXP2_REG_RQ_BW_RD_ADD13,
		PXP2_REG_RQ_BW_RD_UBOUND13पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L14, PXP2_REG_RQ_BW_RD_ADD14,
		PXP2_REG_RQ_BW_RD_UBOUND14पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L15, PXP2_REG_RQ_BW_RD_ADD15,
		PXP2_REG_RQ_BW_RD_UBOUND15पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L16, PXP2_REG_RQ_BW_RD_ADD16,
		PXP2_REG_RQ_BW_RD_UBOUND16पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L17, PXP2_REG_RQ_BW_RD_ADD17,
		PXP2_REG_RQ_BW_RD_UBOUND17पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L18, PXP2_REG_RQ_BW_RD_ADD18,
		PXP2_REG_RQ_BW_RD_UBOUND18पूर्ण,
/* 20 */अणुPXP2_REG_RQ_BW_RD_L19, PXP2_REG_RQ_BW_RD_ADD19,
		PXP2_REG_RQ_BW_RD_UBOUND19पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L20, PXP2_REG_RQ_BW_RD_ADD20,
		PXP2_REG_RQ_BW_RD_UBOUND20पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L22, PXP2_REG_RQ_BW_RD_ADD22,
		PXP2_REG_RQ_BW_RD_UBOUND22पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L23, PXP2_REG_RQ_BW_RD_ADD23,
		PXP2_REG_RQ_BW_RD_UBOUND23पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L24, PXP2_REG_RQ_BW_RD_ADD24,
		PXP2_REG_RQ_BW_RD_UBOUND24पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L25, PXP2_REG_RQ_BW_RD_ADD25,
		PXP2_REG_RQ_BW_RD_UBOUND25पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L26, PXP2_REG_RQ_BW_RD_ADD26,
		PXP2_REG_RQ_BW_RD_UBOUND26पूर्ण,
	अणुPXP2_REG_RQ_BW_RD_L27, PXP2_REG_RQ_BW_RD_ADD27,
		PXP2_REG_RQ_BW_RD_UBOUND27पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L28, PXP2_REG_PSWRQ_BW_ADD28,
		PXP2_REG_PSWRQ_BW_UB28पूर्ण
पूर्ण;

/* रेजिस्टर addresses क्रम ग_लिखो queues */
अटल स्थिर काष्ठा arb_line ग_लिखो_arb_addr[NUM_WR_Q-1] = अणु
/* 1 */	अणुPXP2_REG_PSWRQ_BW_L1, PXP2_REG_PSWRQ_BW_ADD1,
		PXP2_REG_PSWRQ_BW_UB1पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L2, PXP2_REG_PSWRQ_BW_ADD2,
		PXP2_REG_PSWRQ_BW_UB2पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L3, PXP2_REG_PSWRQ_BW_ADD3,
		PXP2_REG_PSWRQ_BW_UB3पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L6, PXP2_REG_PSWRQ_BW_ADD6,
		PXP2_REG_PSWRQ_BW_UB6पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L7, PXP2_REG_PSWRQ_BW_ADD7,
		PXP2_REG_PSWRQ_BW_UB7पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L8, PXP2_REG_PSWRQ_BW_ADD8,
		PXP2_REG_PSWRQ_BW_UB8पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L9, PXP2_REG_PSWRQ_BW_ADD9,
		PXP2_REG_PSWRQ_BW_UB9पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L10, PXP2_REG_PSWRQ_BW_ADD10,
		PXP2_REG_PSWRQ_BW_UB10पूर्ण,
	अणुPXP2_REG_PSWRQ_BW_L11, PXP2_REG_PSWRQ_BW_ADD11,
		PXP2_REG_PSWRQ_BW_UB11पूर्ण,
/* 10 */अणुPXP2_REG_PSWRQ_BW_L28, PXP2_REG_PSWRQ_BW_ADD28,
		PXP2_REG_PSWRQ_BW_UB28पूर्ण,
	अणुPXP2_REG_RQ_BW_WR_L29, PXP2_REG_RQ_BW_WR_ADD29,
		PXP2_REG_RQ_BW_WR_UBOUND29पूर्ण,
	अणुPXP2_REG_RQ_BW_WR_L30, PXP2_REG_RQ_BW_WR_ADD30,
		PXP2_REG_RQ_BW_WR_UBOUND30पूर्ण
पूर्ण;

अटल व्योम bnx2x_init_pxp_arb(काष्ठा bnx2x *bp, पूर्णांक r_order,
			       पूर्णांक w_order)
अणु
	u32 val, i;

	अगर (r_order > MAX_RD_ORD) अणु
		DP(NETIF_MSG_HW, "read order of %d  order adjusted to %d\n",
		   r_order, MAX_RD_ORD);
		r_order = MAX_RD_ORD;
	पूर्ण
	अगर (w_order > MAX_WR_ORD) अणु
		DP(NETIF_MSG_HW, "write order of %d  order adjusted to %d\n",
		   w_order, MAX_WR_ORD);
		w_order = MAX_WR_ORD;
	पूर्ण
	अगर (CHIP_REV_IS_FPGA(bp)) अणु
		DP(NETIF_MSG_HW, "write order adjusted to 1 for FPGA\n");
		w_order = 0;
	पूर्ण
	DP(NETIF_MSG_HW, "read order %d  write order %d\n", r_order, w_order);

	क्रम (i = 0; i < NUM_RD_Q-1; i++) अणु
		REG_WR(bp, पढ़ो_arb_addr[i].l, पढ़ो_arb_data[i][r_order].l);
		REG_WR(bp, पढ़ो_arb_addr[i].add,
		       पढ़ो_arb_data[i][r_order].add);
		REG_WR(bp, पढ़ो_arb_addr[i].ubound,
		       पढ़ो_arb_data[i][r_order].ubound);
	पूर्ण

	क्रम (i = 0; i < NUM_WR_Q-1; i++) अणु
		अगर ((ग_लिखो_arb_addr[i].l == PXP2_REG_RQ_BW_WR_L29) ||
		    (ग_लिखो_arb_addr[i].l == PXP2_REG_RQ_BW_WR_L30)) अणु

			REG_WR(bp, ग_लिखो_arb_addr[i].l,
			       ग_लिखो_arb_data[i][w_order].l);

			REG_WR(bp, ग_लिखो_arb_addr[i].add,
			       ग_लिखो_arb_data[i][w_order].add);

			REG_WR(bp, ग_लिखो_arb_addr[i].ubound,
			       ग_लिखो_arb_data[i][w_order].ubound);
		पूर्ण अन्यथा अणु

			val = REG_RD(bp, ग_लिखो_arb_addr[i].l);
			REG_WR(bp, ग_लिखो_arb_addr[i].l,
			       val | (ग_लिखो_arb_data[i][w_order].l << 10));

			val = REG_RD(bp, ग_लिखो_arb_addr[i].add);
			REG_WR(bp, ग_लिखो_arb_addr[i].add,
			       val | (ग_लिखो_arb_data[i][w_order].add << 10));

			val = REG_RD(bp, ग_लिखो_arb_addr[i].ubound);
			REG_WR(bp, ग_लिखो_arb_addr[i].ubound,
			       val | (ग_लिखो_arb_data[i][w_order].ubound << 7));
		पूर्ण
	पूर्ण

	val =  ग_लिखो_arb_data[NUM_WR_Q-1][w_order].add;
	val += ग_लिखो_arb_data[NUM_WR_Q-1][w_order].ubound << 10;
	val += ग_लिखो_arb_data[NUM_WR_Q-1][w_order].l << 17;
	REG_WR(bp, PXP2_REG_PSWRQ_BW_RD, val);

	val =  पढ़ो_arb_data[NUM_RD_Q-1][r_order].add;
	val += पढ़ो_arb_data[NUM_RD_Q-1][r_order].ubound << 10;
	val += पढ़ो_arb_data[NUM_RD_Q-1][r_order].l << 17;
	REG_WR(bp, PXP2_REG_PSWRQ_BW_WR, val);

	REG_WR(bp, PXP2_REG_RQ_WR_MBS0, w_order);
	REG_WR(bp, PXP2_REG_RQ_WR_MBS1, w_order);
	REG_WR(bp, PXP2_REG_RQ_RD_MBS0, r_order);
	REG_WR(bp, PXP2_REG_RQ_RD_MBS1, r_order);

	अगर ((CHIP_IS_E1(bp) || CHIP_IS_E1H(bp)) && (r_order == MAX_RD_ORD))
		REG_WR(bp, PXP2_REG_RQ_PDR_LIMIT, 0xe00);

	अगर (CHIP_IS_E3(bp))
		REG_WR(bp, PXP2_REG_WR_USDMDP_TH, (0x4 << w_order));
	अन्यथा अगर (CHIP_IS_E2(bp))
		REG_WR(bp, PXP2_REG_WR_USDMDP_TH, (0x8 << w_order));
	अन्यथा
		REG_WR(bp, PXP2_REG_WR_USDMDP_TH, (0x18 << w_order));

	अगर (!CHIP_IS_E1(bp)) अणु
		/*    MPS      w_order     optimal TH      presently TH
		 *    128         0             0               2
		 *    256         1             1               3
		 *    >=512       2             2               3
		 */
		/* DMAE is special */
		अगर (!CHIP_IS_E1H(bp)) अणु
			/* E2 can use optimal TH */
			val = w_order;
			REG_WR(bp, PXP2_REG_WR_DMAE_MPS, val);
		पूर्ण अन्यथा अणु
			val = ((w_order == 0) ? 2 : 3);
			REG_WR(bp, PXP2_REG_WR_DMAE_MPS, 2);
		पूर्ण

		REG_WR(bp, PXP2_REG_WR_HC_MPS, val);
		REG_WR(bp, PXP2_REG_WR_USDM_MPS, val);
		REG_WR(bp, PXP2_REG_WR_CSDM_MPS, val);
		REG_WR(bp, PXP2_REG_WR_TSDM_MPS, val);
		REG_WR(bp, PXP2_REG_WR_XSDM_MPS, val);
		REG_WR(bp, PXP2_REG_WR_QM_MPS, val);
		REG_WR(bp, PXP2_REG_WR_TM_MPS, val);
		REG_WR(bp, PXP2_REG_WR_SRC_MPS, val);
		REG_WR(bp, PXP2_REG_WR_DBG_MPS, val);
		REG_WR(bp, PXP2_REG_WR_CDU_MPS, val);
	पूर्ण

	/* Validate number of tags suppoted by device */
#घोषणा PCIE_REG_PCIER_TL_HDR_FC_ST		0x2980
	val = REG_RD(bp, PCIE_REG_PCIER_TL_HDR_FC_ST);
	val &= 0xFF;
	अगर (val <= 0x20)
		REG_WR(bp, PXP2_REG_PGL_TAGS_LIMIT, 0x20);
पूर्ण

/****************************************************************************
* ILT management
****************************************************************************/
/*
 * This codes hides the low level HW पूर्णांकeraction क्रम ILT management and
 * configuration. The API consists of a shaकरोw ILT table which is set by the
 * driver and a set of routines to use it to configure the HW.
 *
 */

/* ILT HW init operations */

/* ILT memory management operations */
#घोषणा ILT_MEMOP_ALLOC		0
#घोषणा ILT_MEMOP_FREE		1

/* the phys address is shअगरted right 12 bits and has an added
 * 1=valid bit added to the 53rd bit
 * then since this is a wide रेजिस्टर(TM)
 * we split it पूर्णांकo two 32 bit ग_लिखोs
 */
#घोषणा ILT_ADDR1(x)		((u32)(((u64)x >> 12) & 0xFFFFFFFF))
#घोषणा ILT_ADDR2(x)		((u32)((1 << 20) | ((u64)x >> 44)))
#घोषणा ILT_RANGE(f, l)		(((l) << 10) | f)

अटल पूर्णांक bnx2x_ilt_line_mem_op(काष्ठा bnx2x *bp,
				 काष्ठा ilt_line *line, u32 size, u8 memop)
अणु
	अगर (memop == ILT_MEMOP_FREE) अणु
		BNX2X_ILT_FREE(line->page, line->page_mapping, line->size);
		वापस 0;
	पूर्ण
	BNX2X_ILT_ZALLOC(line->page, &line->page_mapping, size);
	अगर (!line->page)
		वापस -1;
	line->size = size;
	वापस 0;
पूर्ण


अटल पूर्णांक bnx2x_ilt_client_mem_op(काष्ठा bnx2x *bp, पूर्णांक cli_num,
				   u8 memop)
अणु
	पूर्णांक i, rc;
	काष्ठा bnx2x_ilt *ilt = BP_ILT(bp);
	काष्ठा ilt_client_info *ilt_cli = &ilt->clients[cli_num];

	अगर (!ilt || !ilt->lines)
		वापस -1;

	अगर (ilt_cli->flags & (ILT_CLIENT_SKIP_INIT | ILT_CLIENT_SKIP_MEM))
		वापस 0;

	क्रम (rc = 0, i = ilt_cli->start; i <= ilt_cli->end && !rc; i++) अणु
		rc = bnx2x_ilt_line_mem_op(bp, &ilt->lines[i],
					   ilt_cli->page_size, memop);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_ilt_mem_op_cnic(काष्ठा bnx2x *bp, u8 memop)
अणु
	पूर्णांक rc = 0;

	अगर (CONFIGURE_NIC_MODE(bp))
		rc = bnx2x_ilt_client_mem_op(bp, ILT_CLIENT_SRC, memop);
	अगर (!rc)
		rc = bnx2x_ilt_client_mem_op(bp, ILT_CLIENT_TM, memop);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_ilt_mem_op(काष्ठा bnx2x *bp, u8 memop)
अणु
	पूर्णांक rc = bnx2x_ilt_client_mem_op(bp, ILT_CLIENT_CDU, memop);
	अगर (!rc)
		rc = bnx2x_ilt_client_mem_op(bp, ILT_CLIENT_QM, memop);
	अगर (!rc && CNIC_SUPPORT(bp) && !CONFIGURE_NIC_MODE(bp))
		rc = bnx2x_ilt_client_mem_op(bp, ILT_CLIENT_SRC, memop);

	वापस rc;
पूर्ण

अटल व्योम bnx2x_ilt_line_wr(काष्ठा bnx2x *bp, पूर्णांक असल_idx,
			      dma_addr_t page_mapping)
अणु
	u32 reg;

	अगर (CHIP_IS_E1(bp))
		reg = PXP2_REG_RQ_ONCHIP_AT + असल_idx*8;
	अन्यथा
		reg = PXP2_REG_RQ_ONCHIP_AT_B0 + असल_idx*8;

	bnx2x_wr_64(bp, reg, ILT_ADDR1(page_mapping), ILT_ADDR2(page_mapping));
पूर्ण

अटल व्योम bnx2x_ilt_line_init_op(काष्ठा bnx2x *bp,
				   काष्ठा bnx2x_ilt *ilt, पूर्णांक idx, u8 initop)
अणु
	dma_addr_t	null_mapping;
	पूर्णांक असल_idx = ilt->start_line + idx;


	चयन (initop) अणु
	हाल INITOP_INIT:
		/* set in the init-value array */
	हाल INITOP_SET:
		bnx2x_ilt_line_wr(bp, असल_idx, ilt->lines[idx].page_mapping);
		अवरोध;
	हाल INITOP_CLEAR:
		null_mapping = 0;
		bnx2x_ilt_line_wr(bp, असल_idx, null_mapping);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_ilt_boundry_init_op(काष्ठा bnx2x *bp,
				      काष्ठा ilt_client_info *ilt_cli,
				      u32 ilt_start, u8 initop)
अणु
	u32 start_reg = 0;
	u32 end_reg = 0;

	/* The boundary is either SET or INIT,
	   CLEAR => SET and क्रम now SET ~~ INIT */

	/* find the appropriate regs */
	अगर (CHIP_IS_E1(bp)) अणु
		चयन (ilt_cli->client_num) अणु
		हाल ILT_CLIENT_CDU:
			start_reg = PXP2_REG_PSWRQ_CDU0_L2P;
			अवरोध;
		हाल ILT_CLIENT_QM:
			start_reg = PXP2_REG_PSWRQ_QM0_L2P;
			अवरोध;
		हाल ILT_CLIENT_SRC:
			start_reg = PXP2_REG_PSWRQ_SRC0_L2P;
			अवरोध;
		हाल ILT_CLIENT_TM:
			start_reg = PXP2_REG_PSWRQ_TM0_L2P;
			अवरोध;
		पूर्ण
		REG_WR(bp, start_reg + BP_FUNC(bp)*4,
		       ILT_RANGE((ilt_start + ilt_cli->start),
				 (ilt_start + ilt_cli->end)));
	पूर्ण अन्यथा अणु
		चयन (ilt_cli->client_num) अणु
		हाल ILT_CLIENT_CDU:
			start_reg = PXP2_REG_RQ_CDU_FIRST_ILT;
			end_reg = PXP2_REG_RQ_CDU_LAST_ILT;
			अवरोध;
		हाल ILT_CLIENT_QM:
			start_reg = PXP2_REG_RQ_QM_FIRST_ILT;
			end_reg = PXP2_REG_RQ_QM_LAST_ILT;
			अवरोध;
		हाल ILT_CLIENT_SRC:
			start_reg = PXP2_REG_RQ_SRC_FIRST_ILT;
			end_reg = PXP2_REG_RQ_SRC_LAST_ILT;
			अवरोध;
		हाल ILT_CLIENT_TM:
			start_reg = PXP2_REG_RQ_TM_FIRST_ILT;
			end_reg = PXP2_REG_RQ_TM_LAST_ILT;
			अवरोध;
		पूर्ण
		REG_WR(bp, start_reg, (ilt_start + ilt_cli->start));
		REG_WR(bp, end_reg, (ilt_start + ilt_cli->end));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_ilt_client_init_op_ilt(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_ilt *ilt,
					 काष्ठा ilt_client_info *ilt_cli,
					 u8 initop)
अणु
	पूर्णांक i;

	अगर (ilt_cli->flags & ILT_CLIENT_SKIP_INIT)
		वापस;

	क्रम (i = ilt_cli->start; i <= ilt_cli->end; i++)
		bnx2x_ilt_line_init_op(bp, ilt, i, initop);

	/* init/clear the ILT boundries */
	bnx2x_ilt_boundry_init_op(bp, ilt_cli, ilt->start_line, initop);
पूर्ण

अटल व्योम bnx2x_ilt_client_init_op(काष्ठा bnx2x *bp,
				     काष्ठा ilt_client_info *ilt_cli, u8 initop)
अणु
	काष्ठा bnx2x_ilt *ilt = BP_ILT(bp);

	bnx2x_ilt_client_init_op_ilt(bp, ilt, ilt_cli, initop);
पूर्ण

अटल व्योम bnx2x_ilt_client_id_init_op(काष्ठा bnx2x *bp,
					पूर्णांक cli_num, u8 initop)
अणु
	काष्ठा bnx2x_ilt *ilt = BP_ILT(bp);
	काष्ठा ilt_client_info *ilt_cli = &ilt->clients[cli_num];

	bnx2x_ilt_client_init_op(bp, ilt_cli, initop);
पूर्ण

अटल व्योम bnx2x_ilt_init_op_cnic(काष्ठा bnx2x *bp, u8 initop)
अणु
	अगर (CONFIGURE_NIC_MODE(bp))
		bnx2x_ilt_client_id_init_op(bp, ILT_CLIENT_SRC, initop);
	bnx2x_ilt_client_id_init_op(bp, ILT_CLIENT_TM, initop);
पूर्ण

अटल व्योम bnx2x_ilt_init_op(काष्ठा bnx2x *bp, u8 initop)
अणु
	bnx2x_ilt_client_id_init_op(bp, ILT_CLIENT_CDU, initop);
	bnx2x_ilt_client_id_init_op(bp, ILT_CLIENT_QM, initop);
	अगर (CNIC_SUPPORT(bp) && !CONFIGURE_NIC_MODE(bp))
		bnx2x_ilt_client_id_init_op(bp, ILT_CLIENT_SRC, initop);
पूर्ण

अटल व्योम bnx2x_ilt_init_client_psz(काष्ठा bnx2x *bp, पूर्णांक cli_num,
				      u32 psz_reg, u8 initop)
अणु
	काष्ठा bnx2x_ilt *ilt = BP_ILT(bp);
	काष्ठा ilt_client_info *ilt_cli = &ilt->clients[cli_num];

	अगर (ilt_cli->flags & ILT_CLIENT_SKIP_INIT)
		वापस;

	चयन (initop) अणु
	हाल INITOP_INIT:
		/* set in the init-value array */
	हाल INITOP_SET:
		REG_WR(bp, psz_reg, ILOG2(ilt_cli->page_size >> 12));
		अवरोध;
	हाल INITOP_CLEAR:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * called during init common stage, ilt clients should be initialized
 * prioir to calling this function
 */
अटल व्योम bnx2x_ilt_init_page_size(काष्ठा bnx2x *bp, u8 initop)
अणु
	bnx2x_ilt_init_client_psz(bp, ILT_CLIENT_CDU,
				  PXP2_REG_RQ_CDU_P_SIZE, initop);
	bnx2x_ilt_init_client_psz(bp, ILT_CLIENT_QM,
				  PXP2_REG_RQ_QM_P_SIZE, initop);
	bnx2x_ilt_init_client_psz(bp, ILT_CLIENT_SRC,
				  PXP2_REG_RQ_SRC_P_SIZE, initop);
	bnx2x_ilt_init_client_psz(bp, ILT_CLIENT_TM,
				  PXP2_REG_RQ_TM_P_SIZE, initop);
पूर्ण

/****************************************************************************
* QM initializations
****************************************************************************/
#घोषणा QM_QUEUES_PER_FUNC	16 /* E1 has 32, but only 16 are used */
#घोषणा QM_INIT_MIN_CID_COUNT	31
#घोषणा QM_INIT(cid_cnt)	(cid_cnt > QM_INIT_MIN_CID_COUNT)

/* called during init port stage */
अटल व्योम bnx2x_qm_init_cid_count(काष्ठा bnx2x *bp, पूर्णांक qm_cid_count,
				    u8 initop)
अणु
	पूर्णांक port = BP_PORT(bp);

	अगर (QM_INIT(qm_cid_count)) अणु
		चयन (initop) अणु
		हाल INITOP_INIT:
			/* set in the init-value array */
		हाल INITOP_SET:
			REG_WR(bp, QM_REG_CONNNUM_0 + port*4,
			       qm_cid_count/16 - 1);
			अवरोध;
		हाल INITOP_CLEAR:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnx2x_qm_set_ptr_table(काष्ठा bnx2x *bp, पूर्णांक qm_cid_count,
				   u32 base_reg, u32 reg)
अणु
	पूर्णांक i;
	u32 wb_data[2] = अणु0, 0पूर्ण;
	क्रम (i = 0; i < 4 * QM_QUEUES_PER_FUNC; i++) अणु
		REG_WR(bp, base_reg + i*4,
		       qm_cid_count * 4 * (i % QM_QUEUES_PER_FUNC));
		bnx2x_init_wr_wb(bp, reg + i*8,	 wb_data, 2);
	पूर्ण
पूर्ण

/* called during init common stage */
अटल व्योम bnx2x_qm_init_ptr_table(काष्ठा bnx2x *bp, पूर्णांक qm_cid_count,
				    u8 initop)
अणु
	अगर (!QM_INIT(qm_cid_count))
		वापस;

	चयन (initop) अणु
	हाल INITOP_INIT:
		/* set in the init-value array */
	हाल INITOP_SET:
		bnx2x_qm_set_ptr_table(bp, qm_cid_count,
				       QM_REG_BASEADDR, QM_REG_PTRTBL);
		अगर (CHIP_IS_E1H(bp))
			bnx2x_qm_set_ptr_table(bp, qm_cid_count,
					       QM_REG_BASEADDR_EXT_A,
					       QM_REG_PTRTBL_EXT_A);
		अवरोध;
	हाल INITOP_CLEAR:
		अवरोध;
	पूर्ण
पूर्ण

/****************************************************************************
* SRC initializations
****************************************************************************/
/* called during init func stage */
अटल व्योम bnx2x_src_init_t2(काष्ठा bnx2x *bp, काष्ठा src_ent *t2,
			      dma_addr_t t2_mapping, पूर्णांक src_cid_count)
अणु
	पूर्णांक i;
	पूर्णांक port = BP_PORT(bp);

	/* Initialize T2 */
	क्रम (i = 0; i < src_cid_count-1; i++)
		t2[i].next = (u64)(t2_mapping +
			     (i+1)*माप(काष्ठा src_ent));

	/* tell the searcher where the T2 table is */
	REG_WR(bp, SRC_REG_COUNTFREE0 + port*4, src_cid_count);

	bnx2x_wr_64(bp, SRC_REG_FIRSTFREE0 + port*16,
		    U64_LO(t2_mapping), U64_HI(t2_mapping));

	bnx2x_wr_64(bp, SRC_REG_LASTFREE0 + port*16,
		    U64_LO((u64)t2_mapping +
			   (src_cid_count-1) * माप(काष्ठा src_ent)),
		    U64_HI((u64)t2_mapping +
			   (src_cid_count-1) * माप(काष्ठा src_ent)));
पूर्ण
#पूर्ण_अगर /* BNX2X_INIT_OPS_H */
