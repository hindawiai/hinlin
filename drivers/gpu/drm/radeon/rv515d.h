<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */
#अगर_अघोषित __RV515D_H__
#घोषणा __RV515D_H__

/*
 * RV515 रेजिस्टरs
 */
#घोषणा PCIE_INDEX			0x0030
#घोषणा PCIE_DATA			0x0034
#घोषणा	MC_IND_INDEX			0x0070
#घोषणा		MC_IND_WR_EN				(1 << 24)
#घोषणा	MC_IND_DATA			0x0074
#घोषणा	RBBM_SOFT_RESET			0x00F0
#घोषणा	CONFIG_MEMSIZE			0x00F8
#घोषणा HDP_FB_LOCATION			0x0134
#घोषणा	CP_CSQ_CNTL			0x0740
#घोषणा	CP_CSQ_MODE			0x0744
#घोषणा	CP_CSQ_ADDR			0x07F0
#घोषणा	CP_CSQ_DATA			0x07F4
#घोषणा	CP_CSQ_STAT			0x07F8
#घोषणा	CP_CSQ2_STAT			0x07FC
#घोषणा	RBBM_STATUS			0x0E40
#घोषणा	DST_PIPE_CONFIG			0x170C
#घोषणा	WAIT_UNTIL			0x1720
#घोषणा		WAIT_2D_IDLE				(1 << 14)
#घोषणा		WAIT_3D_IDLE				(1 << 15)
#घोषणा		WAIT_2D_IDLECLEAN			(1 << 16)
#घोषणा		WAIT_3D_IDLECLEAN			(1 << 17)
#घोषणा	ISYNC_CNTL			0x1724
#घोषणा		ISYNC_ANY2D_IDLE3D			(1 << 0)
#घोषणा		ISYNC_ANY3D_IDLE2D			(1 << 1)
#घोषणा		ISYNC_TRIG2D_IDLE3D			(1 << 2)
#घोषणा		ISYNC_TRIG3D_IDLE2D			(1 << 3)
#घोषणा		ISYNC_WAIT_IDLEGUI			(1 << 4)
#घोषणा		ISYNC_CPSCRATCH_IDLEGUI			(1 << 5)
#घोषणा	VAP_INDEX_OFFSET		0x208C
#घोषणा	VAP_PVS_STATE_FLUSH_REG		0x2284
#घोषणा	GB_ENABLE			0x4008
#घोषणा	GB_MSPOS0			0x4010
#घोषणा		MS_X0_SHIFT				0
#घोषणा		MS_Y0_SHIFT				4
#घोषणा		MS_X1_SHIFT				8
#घोषणा		MS_Y1_SHIFT				12
#घोषणा		MS_X2_SHIFT				16
#घोषणा		MS_Y2_SHIFT				20
#घोषणा		MSBD0_Y_SHIFT				24
#घोषणा		MSBD0_X_SHIFT				28
#घोषणा	GB_MSPOS1			0x4014
#घोषणा		MS_X3_SHIFT				0
#घोषणा		MS_Y3_SHIFT				4
#घोषणा		MS_X4_SHIFT				8
#घोषणा		MS_Y4_SHIFT				12
#घोषणा		MS_X5_SHIFT				16
#घोषणा		MS_Y5_SHIFT				20
#घोषणा		MSBD1_SHIFT				24
#घोषणा GB_TILE_CONFIG			0x4018
#घोषणा		ENABLE_TILING				(1 << 0)
#घोषणा		PIPE_COUNT_MASK				0x0000000E
#घोषणा		PIPE_COUNT_SHIFT			1
#घोषणा		TILE_SIZE_8				(0 << 4)
#घोषणा		TILE_SIZE_16				(1 << 4)
#घोषणा		TILE_SIZE_32				(2 << 4)
#घोषणा		SUBPIXEL_1_12				(0 << 16)
#घोषणा		SUBPIXEL_1_16				(1 << 16)
#घोषणा	GB_SELECT			0x401C
#घोषणा	GB_AA_CONFIG			0x4020
#घोषणा	GB_PIPE_SELECT			0x402C
#घोषणा	GA_ENHANCE			0x4274
#घोषणा		GA_DEADLOCK_CNTL			(1 << 0)
#घोषणा		GA_FASTSYNC_CNTL			(1 << 1)
#घोषणा	GA_POLY_MODE			0x4288
#घोषणा		FRONT_PTYPE_POINT			(0 << 4)
#घोषणा		FRONT_PTYPE_LINE			(1 << 4)
#घोषणा		FRONT_PTYPE_TRIANGE			(2 << 4)
#घोषणा		BACK_PTYPE_POINT			(0 << 7)
#घोषणा		BACK_PTYPE_LINE				(1 << 7)
#घोषणा		BACK_PTYPE_TRIANGE			(2 << 7)
#घोषणा	GA_ROUND_MODE			0x428C
#घोषणा		GEOMETRY_ROUND_TRUNC			(0 << 0)
#घोषणा		GEOMETRY_ROUND_NEAREST			(1 << 0)
#घोषणा		COLOR_ROUND_TRUNC			(0 << 2)
#घोषणा		COLOR_ROUND_NEAREST			(1 << 2)
#घोषणा	SU_REG_DEST			0x42C8
#घोषणा	RB3D_DSTCACHE_CTLSTAT		0x4E4C
#घोषणा		RB3D_DC_FLUSH				(2 << 0)
#घोषणा		RB3D_DC_FREE				(2 << 2)
#घोषणा		RB3D_DC_FINISH				(1 << 4)
#घोषणा ZB_ZCACHE_CTLSTAT		0x4F18
#घोषणा		ZC_FLUSH				(1 << 0)
#घोषणा		ZC_FREE					(1 << 1)
#घोषणा DC_LB_MEMORY_SPLIT		0x6520
#घोषणा		DC_LB_MEMORY_SPLIT_MASK			0x00000003
#घोषणा		DC_LB_MEMORY_SPLIT_SHIFT		0
#घोषणा		DC_LB_MEMORY_SPLIT_D1HALF_D2HALF	0
#घोषणा		DC_LB_MEMORY_SPLIT_D1_3Q_D2_1Q		1
#घोषणा		DC_LB_MEMORY_SPLIT_D1_ONLY		2
#घोषणा		DC_LB_MEMORY_SPLIT_D1_1Q_D2_3Q		3
#घोषणा		DC_LB_MEMORY_SPLIT_SHIFT_MODE		(1 << 2)
#घोषणा		DC_LB_DISP1_END_ADR_SHIFT		4
#घोषणा		DC_LB_DISP1_END_ADR_MASK		0x00007FF0
#घोषणा D1MODE_PRIORITY_A_CNT		0x6548
#घोषणा		MODE_PRIORITY_MARK_MASK			0x00007FFF
#घोषणा		MODE_PRIORITY_OFF			(1 << 16)
#घोषणा		MODE_PRIORITY_ALWAYS_ON			(1 << 20)
#घोषणा		MODE_PRIORITY_FORCE_MASK		(1 << 24)
#घोषणा D1MODE_PRIORITY_B_CNT		0x654C
#घोषणा LB_MAX_REQ_OUTSTANDING		0x6D58
#घोषणा		LB_D1_MAX_REQ_OUTSTANDING_MASK		0x0000000F
#घोषणा		LB_D1_MAX_REQ_OUTSTANDING_SHIFT		0
#घोषणा		LB_D2_MAX_REQ_OUTSTANDING_MASK		0x000F0000
#घोषणा		LB_D2_MAX_REQ_OUTSTANDING_SHIFT		16
#घोषणा D2MODE_PRIORITY_A_CNT		0x6D48
#घोषणा D2MODE_PRIORITY_B_CNT		0x6D4C

/* ix[MC] रेजिस्टरs */
#घोषणा MC_FB_LOCATION			0x01
#घोषणा		MC_FB_START_MASK			0x0000FFFF
#घोषणा		MC_FB_START_SHIFT			0
#घोषणा		MC_FB_TOP_MASK				0xFFFF0000
#घोषणा		MC_FB_TOP_SHIFT				16
#घोषणा MC_AGP_LOCATION			0x02
#घोषणा		MC_AGP_START_MASK			0x0000FFFF
#घोषणा		MC_AGP_START_SHIFT			0
#घोषणा		MC_AGP_TOP_MASK				0xFFFF0000
#घोषणा		MC_AGP_TOP_SHIFT			16
#घोषणा MC_AGP_BASE			0x03
#घोषणा MC_AGP_BASE_2			0x04
#घोषणा	MC_CNTL				0x5
#घोषणा		MEM_NUM_CHANNELS_MASK			0x00000003
#घोषणा	MC_STATUS			0x08
#घोषणा		MC_STATUS_IDLE				(1 << 4)
#घोषणा	MC_MISC_LAT_TIMER		0x09
#घोषणा		MC_CPR_INIT_LAT_MASK			0x0000000F
#घोषणा		MC_VF_INIT_LAT_MASK			0x000000F0
#घोषणा		MC_DISP0R_INIT_LAT_MASK			0x00000F00
#घोषणा		MC_DISP0R_INIT_LAT_SHIFT		8
#घोषणा		MC_DISP1R_INIT_LAT_MASK			0x0000F000
#घोषणा		MC_DISP1R_INIT_LAT_SHIFT		12
#घोषणा		MC_FIXED_INIT_LAT_MASK			0x000F0000
#घोषणा		MC_E2R_INIT_LAT_MASK			0x00F00000
#घोषणा		SAME_PAGE_PRIO_MASK			0x0F000000
#घोषणा		MC_GLOBW_INIT_LAT_MASK			0xF0000000


/*
 * PM4 packet
 */
#घोषणा CP_PACKET0			0x00000000
#घोषणा		PACKET0_BASE_INDEX_SHIFT	0
#घोषणा		PACKET0_BASE_INDEX_MASK		(0x1ffff << 0)
#घोषणा		PACKET0_COUNT_SHIFT		16
#घोषणा		PACKET0_COUNT_MASK		(0x3fff << 16)
#घोषणा CP_PACKET1			0x40000000
#घोषणा CP_PACKET2			0x80000000
#घोषणा		PACKET2_PAD_SHIFT		0
#घोषणा		PACKET2_PAD_MASK		(0x3fffffff << 0)
#घोषणा CP_PACKET3			0xC0000000
#घोषणा		PACKET3_IT_OPCODE_SHIFT		8
#घोषणा		PACKET3_IT_OPCODE_MASK		(0xff << 8)
#घोषणा		PACKET3_COUNT_SHIFT		16
#घोषणा		PACKET3_COUNT_MASK		(0x3fff << 16)
/* PACKET3 op code */
#घोषणा		PACKET3_NOP			0x10
#घोषणा		PACKET3_3D_DRAW_VBUF		0x28
#घोषणा		PACKET3_3D_DRAW_IMMD		0x29
#घोषणा		PACKET3_3D_DRAW_INDX		0x2A
#घोषणा		PACKET3_3D_LOAD_VBPNTR		0x2F
#घोषणा		PACKET3_INDX_BUFFER		0x33
#घोषणा		PACKET3_3D_DRAW_VBUF_2		0x34
#घोषणा		PACKET3_3D_DRAW_IMMD_2		0x35
#घोषणा		PACKET3_3D_DRAW_INDX_2		0x36
#घोषणा		PACKET3_BITBLT_MULTI		0x9B

#घोषणा PACKET0(reg, n)	(CP_PACKET0 |					\
			 REG_SET(PACKET0_BASE_INDEX, (reg) >> 2) |	\
			 REG_SET(PACKET0_COUNT, (n)))
#घोषणा PACKET2(v)	(CP_PACKET2 | REG_SET(PACKET2_PAD, (v)))
#घोषणा PACKET3(op, n)	(CP_PACKET3 |					\
			 REG_SET(PACKET3_IT_OPCODE, (op)) |		\
			 REG_SET(PACKET3_COUNT, (n)))

/* Registers */
#घोषणा R_0000F0_RBBM_SOFT_RESET                     0x0000F0
#घोषणा   S_0000F0_SOFT_RESET_CP(x)                    (((x) & 0x1) << 0)
#घोषणा   G_0000F0_SOFT_RESET_CP(x)                    (((x) >> 0) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_CP                       0xFFFFFFFE
#घोषणा   S_0000F0_SOFT_RESET_HI(x)                    (((x) & 0x1) << 1)
#घोषणा   G_0000F0_SOFT_RESET_HI(x)                    (((x) >> 1) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_HI                       0xFFFFFFFD
#घोषणा   S_0000F0_SOFT_RESET_VAP(x)                   (((x) & 0x1) << 2)
#घोषणा   G_0000F0_SOFT_RESET_VAP(x)                   (((x) >> 2) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_VAP                      0xFFFFFFFB
#घोषणा   S_0000F0_SOFT_RESET_RE(x)                    (((x) & 0x1) << 3)
#घोषणा   G_0000F0_SOFT_RESET_RE(x)                    (((x) >> 3) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_RE                       0xFFFFFFF7
#घोषणा   S_0000F0_SOFT_RESET_PP(x)                    (((x) & 0x1) << 4)
#घोषणा   G_0000F0_SOFT_RESET_PP(x)                    (((x) >> 4) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_PP                       0xFFFFFFEF
#घोषणा   S_0000F0_SOFT_RESET_E2(x)                    (((x) & 0x1) << 5)
#घोषणा   G_0000F0_SOFT_RESET_E2(x)                    (((x) >> 5) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_E2                       0xFFFFFFDF
#घोषणा   S_0000F0_SOFT_RESET_RB(x)                    (((x) & 0x1) << 6)
#घोषणा   G_0000F0_SOFT_RESET_RB(x)                    (((x) >> 6) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_RB                       0xFFFFFFBF
#घोषणा   S_0000F0_SOFT_RESET_HDP(x)                   (((x) & 0x1) << 7)
#घोषणा   G_0000F0_SOFT_RESET_HDP(x)                   (((x) >> 7) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_HDP                      0xFFFFFF7F
#घोषणा   S_0000F0_SOFT_RESET_MC(x)                    (((x) & 0x1) << 8)
#घोषणा   G_0000F0_SOFT_RESET_MC(x)                    (((x) >> 8) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_MC                       0xFFFFFEFF
#घोषणा   S_0000F0_SOFT_RESET_AIC(x)                   (((x) & 0x1) << 9)
#घोषणा   G_0000F0_SOFT_RESET_AIC(x)                   (((x) >> 9) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_AIC                      0xFFFFFDFF
#घोषणा   S_0000F0_SOFT_RESET_VIP(x)                   (((x) & 0x1) << 10)
#घोषणा   G_0000F0_SOFT_RESET_VIP(x)                   (((x) >> 10) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_VIP                      0xFFFFFBFF
#घोषणा   S_0000F0_SOFT_RESET_DISP(x)                  (((x) & 0x1) << 11)
#घोषणा   G_0000F0_SOFT_RESET_DISP(x)                  (((x) >> 11) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_DISP                     0xFFFFF7FF
#घोषणा   S_0000F0_SOFT_RESET_CG(x)                    (((x) & 0x1) << 12)
#घोषणा   G_0000F0_SOFT_RESET_CG(x)                    (((x) >> 12) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_CG                       0xFFFFEFFF
#घोषणा   S_0000F0_SOFT_RESET_GA(x)                    (((x) & 0x1) << 13)
#घोषणा   G_0000F0_SOFT_RESET_GA(x)                    (((x) >> 13) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_GA                       0xFFFFDFFF
#घोषणा   S_0000F0_SOFT_RESET_IDCT(x)                  (((x) & 0x1) << 14)
#घोषणा   G_0000F0_SOFT_RESET_IDCT(x)                  (((x) >> 14) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_IDCT                     0xFFFFBFFF
#घोषणा R_0000F8_CONFIG_MEMSIZE                      0x0000F8
#घोषणा   S_0000F8_CONFIG_MEMSIZE(x)                   (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_0000F8_CONFIG_MEMSIZE(x)                   (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_0000F8_CONFIG_MEMSIZE                      0x00000000
#घोषणा R_000134_HDP_FB_LOCATION                     0x000134
#घोषणा   S_000134_HDP_FB_START(x)                     (((x) & 0xFFFF) << 0)
#घोषणा   G_000134_HDP_FB_START(x)                     (((x) >> 0) & 0xFFFF)
#घोषणा   C_000134_HDP_FB_START                        0xFFFF0000
#घोषणा R_000300_VGA_RENDER_CONTROL                  0x000300
#घोषणा   S_000300_VGA_BLINK_RATE(x)                   (((x) & 0x1F) << 0)
#घोषणा   G_000300_VGA_BLINK_RATE(x)                   (((x) >> 0) & 0x1F)
#घोषणा   C_000300_VGA_BLINK_RATE                      0xFFFFFFE0
#घोषणा   S_000300_VGA_BLINK_MODE(x)                   (((x) & 0x3) << 5)
#घोषणा   G_000300_VGA_BLINK_MODE(x)                   (((x) >> 5) & 0x3)
#घोषणा   C_000300_VGA_BLINK_MODE                      0xFFFFFF9F
#घोषणा   S_000300_VGA_CURSOR_BLINK_INVERT(x)          (((x) & 0x1) << 7)
#घोषणा   G_000300_VGA_CURSOR_BLINK_INVERT(x)          (((x) >> 7) & 0x1)
#घोषणा   C_000300_VGA_CURSOR_BLINK_INVERT             0xFFFFFF7F
#घोषणा   S_000300_VGA_EXTD_ADDR_COUNT_ENABLE(x)       (((x) & 0x1) << 8)
#घोषणा   G_000300_VGA_EXTD_ADDR_COUNT_ENABLE(x)       (((x) >> 8) & 0x1)
#घोषणा   C_000300_VGA_EXTD_ADDR_COUNT_ENABLE          0xFFFFFEFF
#घोषणा   S_000300_VGA_VSTATUS_CNTL(x)                 (((x) & 0x3) << 16)
#घोषणा   G_000300_VGA_VSTATUS_CNTL(x)                 (((x) >> 16) & 0x3)
#घोषणा   C_000300_VGA_VSTATUS_CNTL                    0xFFFCFFFF
#घोषणा   S_000300_VGA_LOCK_8DOT(x)                    (((x) & 0x1) << 24)
#घोषणा   G_000300_VGA_LOCK_8DOT(x)                    (((x) >> 24) & 0x1)
#घोषणा   C_000300_VGA_LOCK_8DOT                       0xFEFFFFFF
#घोषणा   S_000300_VGAREG_LINECMP_COMPATIBILITY_SEL(x) (((x) & 0x1) << 25)
#घोषणा   G_000300_VGAREG_LINECMP_COMPATIBILITY_SEL(x) (((x) >> 25) & 0x1)
#घोषणा   C_000300_VGAREG_LINECMP_COMPATIBILITY_SEL    0xFDFFFFFF
#घोषणा R_000310_VGA_MEMORY_BASE_ADDRESS             0x000310
#घोषणा   S_000310_VGA_MEMORY_BASE_ADDRESS(x)          (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_000310_VGA_MEMORY_BASE_ADDRESS(x)          (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_000310_VGA_MEMORY_BASE_ADDRESS             0x00000000
#घोषणा R_000328_VGA_HDP_CONTROL                     0x000328
#घोषणा   S_000328_VGA_MEM_PAGE_SELECT_EN(x)           (((x) & 0x1) << 0)
#घोषणा   G_000328_VGA_MEM_PAGE_SELECT_EN(x)           (((x) >> 0) & 0x1)
#घोषणा   C_000328_VGA_MEM_PAGE_SELECT_EN              0xFFFFFFFE
#घोषणा   S_000328_VGA_RBBM_LOCK_DISABLE(x)            (((x) & 0x1) << 8)
#घोषणा   G_000328_VGA_RBBM_LOCK_DISABLE(x)            (((x) >> 8) & 0x1)
#घोषणा   C_000328_VGA_RBBM_LOCK_DISABLE               0xFFFFFEFF
#घोषणा   S_000328_VGA_SOFT_RESET(x)                   (((x) & 0x1) << 16)
#घोषणा   G_000328_VGA_SOFT_RESET(x)                   (((x) >> 16) & 0x1)
#घोषणा   C_000328_VGA_SOFT_RESET                      0xFFFEFFFF
#घोषणा   S_000328_VGA_TEST_RESET_CONTROL(x)           (((x) & 0x1) << 24)
#घोषणा   G_000328_VGA_TEST_RESET_CONTROL(x)           (((x) >> 24) & 0x1)
#घोषणा   C_000328_VGA_TEST_RESET_CONTROL              0xFEFFFFFF
#घोषणा R_000330_D1VGA_CONTROL                       0x000330
#घोषणा   S_000330_D1VGA_MODE_ENABLE(x)                (((x) & 0x1) << 0)
#घोषणा   G_000330_D1VGA_MODE_ENABLE(x)                (((x) >> 0) & 0x1)
#घोषणा   C_000330_D1VGA_MODE_ENABLE                   0xFFFFFFFE
#घोषणा   S_000330_D1VGA_TIMING_SELECT(x)              (((x) & 0x1) << 8)
#घोषणा   G_000330_D1VGA_TIMING_SELECT(x)              (((x) >> 8) & 0x1)
#घोषणा   C_000330_D1VGA_TIMING_SELECT                 0xFFFFFEFF
#घोषणा   S_000330_D1VGA_SYNC_POLARITY_SELECT(x)       (((x) & 0x1) << 9)
#घोषणा   G_000330_D1VGA_SYNC_POLARITY_SELECT(x)       (((x) >> 9) & 0x1)
#घोषणा   C_000330_D1VGA_SYNC_POLARITY_SELECT          0xFFFFFDFF
#घोषणा   S_000330_D1VGA_OVERSCAN_TIMING_SELECT(x)     (((x) & 0x1) << 10)
#घोषणा   G_000330_D1VGA_OVERSCAN_TIMING_SELECT(x)     (((x) >> 10) & 0x1)
#घोषणा   C_000330_D1VGA_OVERSCAN_TIMING_SELECT        0xFFFFFBFF
#घोषणा   S_000330_D1VGA_OVERSCAN_COLOR_EN(x)          (((x) & 0x1) << 16)
#घोषणा   G_000330_D1VGA_OVERSCAN_COLOR_EN(x)          (((x) >> 16) & 0x1)
#घोषणा   C_000330_D1VGA_OVERSCAN_COLOR_EN             0xFFFEFFFF
#घोषणा   S_000330_D1VGA_ROTATE(x)                     (((x) & 0x3) << 24)
#घोषणा   G_000330_D1VGA_ROTATE(x)                     (((x) >> 24) & 0x3)
#घोषणा   C_000330_D1VGA_ROTATE                        0xFCFFFFFF
#घोषणा R_000338_D2VGA_CONTROL                       0x000338
#घोषणा   S_000338_D2VGA_MODE_ENABLE(x)                (((x) & 0x1) << 0)
#घोषणा   G_000338_D2VGA_MODE_ENABLE(x)                (((x) >> 0) & 0x1)
#घोषणा   C_000338_D2VGA_MODE_ENABLE                   0xFFFFFFFE
#घोषणा   S_000338_D2VGA_TIMING_SELECT(x)              (((x) & 0x1) << 8)
#घोषणा   G_000338_D2VGA_TIMING_SELECT(x)              (((x) >> 8) & 0x1)
#घोषणा   C_000338_D2VGA_TIMING_SELECT                 0xFFFFFEFF
#घोषणा   S_000338_D2VGA_SYNC_POLARITY_SELECT(x)       (((x) & 0x1) << 9)
#घोषणा   G_000338_D2VGA_SYNC_POLARITY_SELECT(x)       (((x) >> 9) & 0x1)
#घोषणा   C_000338_D2VGA_SYNC_POLARITY_SELECT          0xFFFFFDFF
#घोषणा   S_000338_D2VGA_OVERSCAN_TIMING_SELECT(x)     (((x) & 0x1) << 10)
#घोषणा   G_000338_D2VGA_OVERSCAN_TIMING_SELECT(x)     (((x) >> 10) & 0x1)
#घोषणा   C_000338_D2VGA_OVERSCAN_TIMING_SELECT        0xFFFFFBFF
#घोषणा   S_000338_D2VGA_OVERSCAN_COLOR_EN(x)          (((x) & 0x1) << 16)
#घोषणा   G_000338_D2VGA_OVERSCAN_COLOR_EN(x)          (((x) >> 16) & 0x1)
#घोषणा   C_000338_D2VGA_OVERSCAN_COLOR_EN             0xFFFEFFFF
#घोषणा   S_000338_D2VGA_ROTATE(x)                     (((x) & 0x3) << 24)
#घोषणा   G_000338_D2VGA_ROTATE(x)                     (((x) >> 24) & 0x3)
#घोषणा   C_000338_D2VGA_ROTATE                        0xFCFFFFFF
#घोषणा R_0007C0_CP_STAT                             0x0007C0
#घोषणा   S_0007C0_MRU_BUSY(x)                         (((x) & 0x1) << 0)
#घोषणा   G_0007C0_MRU_BUSY(x)                         (((x) >> 0) & 0x1)
#घोषणा   C_0007C0_MRU_BUSY                            0xFFFFFFFE
#घोषणा   S_0007C0_MWU_BUSY(x)                         (((x) & 0x1) << 1)
#घोषणा   G_0007C0_MWU_BUSY(x)                         (((x) >> 1) & 0x1)
#घोषणा   C_0007C0_MWU_BUSY                            0xFFFFFFFD
#घोषणा   S_0007C0_RSIU_BUSY(x)                        (((x) & 0x1) << 2)
#घोषणा   G_0007C0_RSIU_BUSY(x)                        (((x) >> 2) & 0x1)
#घोषणा   C_0007C0_RSIU_BUSY                           0xFFFFFFFB
#घोषणा   S_0007C0_RCIU_BUSY(x)                        (((x) & 0x1) << 3)
#घोषणा   G_0007C0_RCIU_BUSY(x)                        (((x) >> 3) & 0x1)
#घोषणा   C_0007C0_RCIU_BUSY                           0xFFFFFFF7
#घोषणा   S_0007C0_CSF_PRIMARY_BUSY(x)                 (((x) & 0x1) << 9)
#घोषणा   G_0007C0_CSF_PRIMARY_BUSY(x)                 (((x) >> 9) & 0x1)
#घोषणा   C_0007C0_CSF_PRIMARY_BUSY                    0xFFFFFDFF
#घोषणा   S_0007C0_CSF_INसूचीECT_BUSY(x)                (((x) & 0x1) << 10)
#घोषणा   G_0007C0_CSF_INसूचीECT_BUSY(x)                (((x) >> 10) & 0x1)
#घोषणा   C_0007C0_CSF_INसूचीECT_BUSY                   0xFFFFFBFF
#घोषणा   S_0007C0_CSQ_PRIMARY_BUSY(x)                 (((x) & 0x1) << 11)
#घोषणा   G_0007C0_CSQ_PRIMARY_BUSY(x)                 (((x) >> 11) & 0x1)
#घोषणा   C_0007C0_CSQ_PRIMARY_BUSY                    0xFFFFF7FF
#घोषणा   S_0007C0_CSQ_INसूचीECT_BUSY(x)                (((x) & 0x1) << 12)
#घोषणा   G_0007C0_CSQ_INसूचीECT_BUSY(x)                (((x) >> 12) & 0x1)
#घोषणा   C_0007C0_CSQ_INसूचीECT_BUSY                   0xFFFFEFFF
#घोषणा   S_0007C0_CSI_BUSY(x)                         (((x) & 0x1) << 13)
#घोषणा   G_0007C0_CSI_BUSY(x)                         (((x) >> 13) & 0x1)
#घोषणा   C_0007C0_CSI_BUSY                            0xFFFFDFFF
#घोषणा   S_0007C0_CSF_INसूचीECT2_BUSY(x)               (((x) & 0x1) << 14)
#घोषणा   G_0007C0_CSF_INसूचीECT2_BUSY(x)               (((x) >> 14) & 0x1)
#घोषणा   C_0007C0_CSF_INसूचीECT2_BUSY                  0xFFFFBFFF
#घोषणा   S_0007C0_CSQ_INसूचीECT2_BUSY(x)               (((x) & 0x1) << 15)
#घोषणा   G_0007C0_CSQ_INसूचीECT2_BUSY(x)               (((x) >> 15) & 0x1)
#घोषणा   C_0007C0_CSQ_INसूचीECT2_BUSY                  0xFFFF7FFF
#घोषणा   S_0007C0_GUIDMA_BUSY(x)                      (((x) & 0x1) << 28)
#घोषणा   G_0007C0_GUIDMA_BUSY(x)                      (((x) >> 28) & 0x1)
#घोषणा   C_0007C0_GUIDMA_BUSY                         0xEFFFFFFF
#घोषणा   S_0007C0_VIDDMA_BUSY(x)                      (((x) & 0x1) << 29)
#घोषणा   G_0007C0_VIDDMA_BUSY(x)                      (((x) >> 29) & 0x1)
#घोषणा   C_0007C0_VIDDMA_BUSY                         0xDFFFFFFF
#घोषणा   S_0007C0_CMDSTRM_BUSY(x)                     (((x) & 0x1) << 30)
#घोषणा   G_0007C0_CMDSTRM_BUSY(x)                     (((x) >> 30) & 0x1)
#घोषणा   C_0007C0_CMDSTRM_BUSY                        0xBFFFFFFF
#घोषणा   S_0007C0_CP_BUSY(x)                          (((x) & 0x1) << 31)
#घोषणा   G_0007C0_CP_BUSY(x)                          (((x) >> 31) & 0x1)
#घोषणा   C_0007C0_CP_BUSY                             0x7FFFFFFF
#घोषणा R_000E40_RBBM_STATUS                         0x000E40
#घोषणा   S_000E40_CMDFIFO_AVAIL(x)                    (((x) & 0x7F) << 0)
#घोषणा   G_000E40_CMDFIFO_AVAIL(x)                    (((x) >> 0) & 0x7F)
#घोषणा   C_000E40_CMDFIFO_AVAIL                       0xFFFFFF80
#घोषणा   S_000E40_HIRQ_ON_RBB(x)                      (((x) & 0x1) << 8)
#घोषणा   G_000E40_HIRQ_ON_RBB(x)                      (((x) >> 8) & 0x1)
#घोषणा   C_000E40_HIRQ_ON_RBB                         0xFFFFFEFF
#घोषणा   S_000E40_CPRQ_ON_RBB(x)                      (((x) & 0x1) << 9)
#घोषणा   G_000E40_CPRQ_ON_RBB(x)                      (((x) >> 9) & 0x1)
#घोषणा   C_000E40_CPRQ_ON_RBB                         0xFFFFFDFF
#घोषणा   S_000E40_CFRQ_ON_RBB(x)                      (((x) & 0x1) << 10)
#घोषणा   G_000E40_CFRQ_ON_RBB(x)                      (((x) >> 10) & 0x1)
#घोषणा   C_000E40_CFRQ_ON_RBB                         0xFFFFFBFF
#घोषणा   S_000E40_HIRQ_IN_RTBUF(x)                    (((x) & 0x1) << 11)
#घोषणा   G_000E40_HIRQ_IN_RTBUF(x)                    (((x) >> 11) & 0x1)
#घोषणा   C_000E40_HIRQ_IN_RTBUF                       0xFFFFF7FF
#घोषणा   S_000E40_CPRQ_IN_RTBUF(x)                    (((x) & 0x1) << 12)
#घोषणा   G_000E40_CPRQ_IN_RTBUF(x)                    (((x) >> 12) & 0x1)
#घोषणा   C_000E40_CPRQ_IN_RTBUF                       0xFFFFEFFF
#घोषणा   S_000E40_CFRQ_IN_RTBUF(x)                    (((x) & 0x1) << 13)
#घोषणा   G_000E40_CFRQ_IN_RTBUF(x)                    (((x) >> 13) & 0x1)
#घोषणा   C_000E40_CFRQ_IN_RTBUF                       0xFFFFDFFF
#घोषणा   S_000E40_CF_PIPE_BUSY(x)                     (((x) & 0x1) << 14)
#घोषणा   G_000E40_CF_PIPE_BUSY(x)                     (((x) >> 14) & 0x1)
#घोषणा   C_000E40_CF_PIPE_BUSY                        0xFFFFBFFF
#घोषणा   S_000E40_ENG_EV_BUSY(x)                      (((x) & 0x1) << 15)
#घोषणा   G_000E40_ENG_EV_BUSY(x)                      (((x) >> 15) & 0x1)
#घोषणा   C_000E40_ENG_EV_BUSY                         0xFFFF7FFF
#घोषणा   S_000E40_CP_CMDSTRM_BUSY(x)                  (((x) & 0x1) << 16)
#घोषणा   G_000E40_CP_CMDSTRM_BUSY(x)                  (((x) >> 16) & 0x1)
#घोषणा   C_000E40_CP_CMDSTRM_BUSY                     0xFFFEFFFF
#घोषणा   S_000E40_E2_BUSY(x)                          (((x) & 0x1) << 17)
#घोषणा   G_000E40_E2_BUSY(x)                          (((x) >> 17) & 0x1)
#घोषणा   C_000E40_E2_BUSY                             0xFFFDFFFF
#घोषणा   S_000E40_RB2D_BUSY(x)                        (((x) & 0x1) << 18)
#घोषणा   G_000E40_RB2D_BUSY(x)                        (((x) >> 18) & 0x1)
#घोषणा   C_000E40_RB2D_BUSY                           0xFFFBFFFF
#घोषणा   S_000E40_RB3D_BUSY(x)                        (((x) & 0x1) << 19)
#घोषणा   G_000E40_RB3D_BUSY(x)                        (((x) >> 19) & 0x1)
#घोषणा   C_000E40_RB3D_BUSY                           0xFFF7FFFF
#घोषणा   S_000E40_VAP_BUSY(x)                         (((x) & 0x1) << 20)
#घोषणा   G_000E40_VAP_BUSY(x)                         (((x) >> 20) & 0x1)
#घोषणा   C_000E40_VAP_BUSY                            0xFFEFFFFF
#घोषणा   S_000E40_RE_BUSY(x)                          (((x) & 0x1) << 21)
#घोषणा   G_000E40_RE_BUSY(x)                          (((x) >> 21) & 0x1)
#घोषणा   C_000E40_RE_BUSY                             0xFFDFFFFF
#घोषणा   S_000E40_TAM_BUSY(x)                         (((x) & 0x1) << 22)
#घोषणा   G_000E40_TAM_BUSY(x)                         (((x) >> 22) & 0x1)
#घोषणा   C_000E40_TAM_BUSY                            0xFFBFFFFF
#घोषणा   S_000E40_TDM_BUSY(x)                         (((x) & 0x1) << 23)
#घोषणा   G_000E40_TDM_BUSY(x)                         (((x) >> 23) & 0x1)
#घोषणा   C_000E40_TDM_BUSY                            0xFF7FFFFF
#घोषणा   S_000E40_PB_BUSY(x)                          (((x) & 0x1) << 24)
#घोषणा   G_000E40_PB_BUSY(x)                          (((x) >> 24) & 0x1)
#घोषणा   C_000E40_PB_BUSY                             0xFEFFFFFF
#घोषणा   S_000E40_TIM_BUSY(x)                         (((x) & 0x1) << 25)
#घोषणा   G_000E40_TIM_BUSY(x)                         (((x) >> 25) & 0x1)
#घोषणा   C_000E40_TIM_BUSY                            0xFDFFFFFF
#घोषणा   S_000E40_GA_BUSY(x)                          (((x) & 0x1) << 26)
#घोषणा   G_000E40_GA_BUSY(x)                          (((x) >> 26) & 0x1)
#घोषणा   C_000E40_GA_BUSY                             0xFBFFFFFF
#घोषणा   S_000E40_CBA2D_BUSY(x)                       (((x) & 0x1) << 27)
#घोषणा   G_000E40_CBA2D_BUSY(x)                       (((x) >> 27) & 0x1)
#घोषणा   C_000E40_CBA2D_BUSY                          0xF7FFFFFF
#घोषणा   S_000E40_RBBM_HIBUSY(x)                      (((x) & 0x1) << 28)
#घोषणा   G_000E40_RBBM_HIBUSY(x)                      (((x) >> 28) & 0x1)
#घोषणा   C_000E40_RBBM_HIBUSY                         0xEFFFFFFF
#घोषणा   S_000E40_SKID_CFBUSY(x)                      (((x) & 0x1) << 29)
#घोषणा   G_000E40_SKID_CFBUSY(x)                      (((x) >> 29) & 0x1)
#घोषणा   C_000E40_SKID_CFBUSY                         0xDFFFFFFF
#घोषणा   S_000E40_VAP_VF_BUSY(x)                      (((x) & 0x1) << 30)
#घोषणा   G_000E40_VAP_VF_BUSY(x)                      (((x) >> 30) & 0x1)
#घोषणा   C_000E40_VAP_VF_BUSY                         0xBFFFFFFF
#घोषणा   S_000E40_GUI_ACTIVE(x)                       (((x) & 0x1) << 31)
#घोषणा   G_000E40_GUI_ACTIVE(x)                       (((x) >> 31) & 0x1)
#घोषणा   C_000E40_GUI_ACTIVE                          0x7FFFFFFF
#घोषणा R_006080_D1CRTC_CONTROL                      0x006080
#घोषणा   S_006080_D1CRTC_MASTER_EN(x)                 (((x) & 0x1) << 0)
#घोषणा   G_006080_D1CRTC_MASTER_EN(x)                 (((x) >> 0) & 0x1)
#घोषणा   C_006080_D1CRTC_MASTER_EN                    0xFFFFFFFE
#घोषणा   S_006080_D1CRTC_SYNC_RESET_SEL(x)            (((x) & 0x1) << 4)
#घोषणा   G_006080_D1CRTC_SYNC_RESET_SEL(x)            (((x) >> 4) & 0x1)
#घोषणा   C_006080_D1CRTC_SYNC_RESET_SEL               0xFFFFFFEF
#घोषणा   S_006080_D1CRTC_DISABLE_POINT_CNTL(x)        (((x) & 0x3) << 8)
#घोषणा   G_006080_D1CRTC_DISABLE_POINT_CNTL(x)        (((x) >> 8) & 0x3)
#घोषणा   C_006080_D1CRTC_DISABLE_POINT_CNTL           0xFFFFFCFF
#घोषणा   S_006080_D1CRTC_CURRENT_MASTER_EN_STATE(x)   (((x) & 0x1) << 16)
#घोषणा   G_006080_D1CRTC_CURRENT_MASTER_EN_STATE(x)   (((x) >> 16) & 0x1)
#घोषणा   C_006080_D1CRTC_CURRENT_MASTER_EN_STATE      0xFFFEFFFF
#घोषणा   S_006080_D1CRTC_DISP_READ_REQUEST_DISABLE(x) (((x) & 0x1) << 24)
#घोषणा   G_006080_D1CRTC_DISP_READ_REQUEST_DISABLE(x) (((x) >> 24) & 0x1)
#घोषणा   C_006080_D1CRTC_DISP_READ_REQUEST_DISABLE    0xFEFFFFFF
#घोषणा R_0060E8_D1CRTC_UPDATE_LOCK                  0x0060E8
#घोषणा   S_0060E8_D1CRTC_UPDATE_LOCK(x)               (((x) & 0x1) << 0)
#घोषणा   G_0060E8_D1CRTC_UPDATE_LOCK(x)               (((x) >> 0) & 0x1)
#घोषणा   C_0060E8_D1CRTC_UPDATE_LOCK                  0xFFFFFFFE
#घोषणा R_006110_D1GRPH_PRIMARY_SURFACE_ADDRESS      0x006110
#घोषणा   S_006110_D1GRPH_PRIMARY_SURFACE_ADDRESS(x)   (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_006110_D1GRPH_PRIMARY_SURFACE_ADDRESS(x)   (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_006110_D1GRPH_PRIMARY_SURFACE_ADDRESS      0x00000000
#घोषणा R_006118_D1GRPH_SECONDARY_SURFACE_ADDRESS    0x006118
#घोषणा   S_006118_D1GRPH_SECONDARY_SURFACE_ADDRESS(x) (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_006118_D1GRPH_SECONDARY_SURFACE_ADDRESS(x) (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_006118_D1GRPH_SECONDARY_SURFACE_ADDRESS    0x00000000
#घोषणा R_006880_D2CRTC_CONTROL                      0x006880
#घोषणा   S_006880_D2CRTC_MASTER_EN(x)                 (((x) & 0x1) << 0)
#घोषणा   G_006880_D2CRTC_MASTER_EN(x)                 (((x) >> 0) & 0x1)
#घोषणा   C_006880_D2CRTC_MASTER_EN                    0xFFFFFFFE
#घोषणा   S_006880_D2CRTC_SYNC_RESET_SEL(x)            (((x) & 0x1) << 4)
#घोषणा   G_006880_D2CRTC_SYNC_RESET_SEL(x)            (((x) >> 4) & 0x1)
#घोषणा   C_006880_D2CRTC_SYNC_RESET_SEL               0xFFFFFFEF
#घोषणा   S_006880_D2CRTC_DISABLE_POINT_CNTL(x)        (((x) & 0x3) << 8)
#घोषणा   G_006880_D2CRTC_DISABLE_POINT_CNTL(x)        (((x) >> 8) & 0x3)
#घोषणा   C_006880_D2CRTC_DISABLE_POINT_CNTL           0xFFFFFCFF
#घोषणा   S_006880_D2CRTC_CURRENT_MASTER_EN_STATE(x)   (((x) & 0x1) << 16)
#घोषणा   G_006880_D2CRTC_CURRENT_MASTER_EN_STATE(x)   (((x) >> 16) & 0x1)
#घोषणा   C_006880_D2CRTC_CURRENT_MASTER_EN_STATE      0xFFFEFFFF
#घोषणा   S_006880_D2CRTC_DISP_READ_REQUEST_DISABLE(x) (((x) & 0x1) << 24)
#घोषणा   G_006880_D2CRTC_DISP_READ_REQUEST_DISABLE(x) (((x) >> 24) & 0x1)
#घोषणा   C_006880_D2CRTC_DISP_READ_REQUEST_DISABLE    0xFEFFFFFF
#घोषणा R_0068E8_D2CRTC_UPDATE_LOCK                  0x0068E8
#घोषणा   S_0068E8_D2CRTC_UPDATE_LOCK(x)               (((x) & 0x1) << 0)
#घोषणा   G_0068E8_D2CRTC_UPDATE_LOCK(x)               (((x) >> 0) & 0x1)
#घोषणा   C_0068E8_D2CRTC_UPDATE_LOCK                  0xFFFFFFFE
#घोषणा R_006910_D2GRPH_PRIMARY_SURFACE_ADDRESS      0x006910
#घोषणा   S_006910_D2GRPH_PRIMARY_SURFACE_ADDRESS(x)   (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_006910_D2GRPH_PRIMARY_SURFACE_ADDRESS(x)   (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_006910_D2GRPH_PRIMARY_SURFACE_ADDRESS      0x00000000
#घोषणा R_006918_D2GRPH_SECONDARY_SURFACE_ADDRESS    0x006918
#घोषणा   S_006918_D2GRPH_SECONDARY_SURFACE_ADDRESS(x) (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_006918_D2GRPH_SECONDARY_SURFACE_ADDRESS(x) (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_006918_D2GRPH_SECONDARY_SURFACE_ADDRESS    0x00000000


#घोषणा R_000001_MC_FB_LOCATION                      0x000001
#घोषणा   S_000001_MC_FB_START(x)                      (((x) & 0xFFFF) << 0)
#घोषणा   G_000001_MC_FB_START(x)                      (((x) >> 0) & 0xFFFF)
#घोषणा   C_000001_MC_FB_START                         0xFFFF0000
#घोषणा   S_000001_MC_FB_TOP(x)                        (((x) & 0xFFFF) << 16)
#घोषणा   G_000001_MC_FB_TOP(x)                        (((x) >> 16) & 0xFFFF)
#घोषणा   C_000001_MC_FB_TOP                           0x0000FFFF
#घोषणा R_000002_MC_AGP_LOCATION                     0x000002
#घोषणा   S_000002_MC_AGP_START(x)                     (((x) & 0xFFFF) << 0)
#घोषणा   G_000002_MC_AGP_START(x)                     (((x) >> 0) & 0xFFFF)
#घोषणा   C_000002_MC_AGP_START                        0xFFFF0000
#घोषणा   S_000002_MC_AGP_TOP(x)                       (((x) & 0xFFFF) << 16)
#घोषणा   G_000002_MC_AGP_TOP(x)                       (((x) >> 16) & 0xFFFF)
#घोषणा   C_000002_MC_AGP_TOP                          0x0000FFFF
#घोषणा R_000003_MC_AGP_BASE                         0x000003
#घोषणा   S_000003_AGP_BASE_ADDR(x)                    (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_000003_AGP_BASE_ADDR(x)                    (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_000003_AGP_BASE_ADDR                       0x00000000
#घोषणा R_000004_MC_AGP_BASE_2                       0x000004
#घोषणा   S_000004_AGP_BASE_ADDR_2(x)                  (((x) & 0xF) << 0)
#घोषणा   G_000004_AGP_BASE_ADDR_2(x)                  (((x) >> 0) & 0xF)
#घोषणा   C_000004_AGP_BASE_ADDR_2                     0xFFFFFFF0


#घोषणा R_00000F_CP_DYN_CNTL                         0x00000F
#घोषणा   S_00000F_CP_FORCEON(x)                       (((x) & 0x1) << 0)
#घोषणा   G_00000F_CP_FORCEON(x)                       (((x) >> 0) & 0x1)
#घोषणा   C_00000F_CP_FORCEON                          0xFFFFFFFE
#घोषणा   S_00000F_CP_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 1)
#घोषणा   G_00000F_CP_MAX_DYN_STOP_LAT(x)              (((x) >> 1) & 0x1)
#घोषणा   C_00000F_CP_MAX_DYN_STOP_LAT                 0xFFFFFFFD
#घोषणा   S_00000F_CP_CLOCK_STATUS(x)                  (((x) & 0x1) << 2)
#घोषणा   G_00000F_CP_CLOCK_STATUS(x)                  (((x) >> 2) & 0x1)
#घोषणा   C_00000F_CP_CLOCK_STATUS                     0xFFFFFFFB
#घोषणा   S_00000F_CP_PROG_SHUTOFF(x)                  (((x) & 0x1) << 3)
#घोषणा   G_00000F_CP_PROG_SHUTOFF(x)                  (((x) >> 3) & 0x1)
#घोषणा   C_00000F_CP_PROG_SHUTOFF                     0xFFFFFFF7
#घोषणा   S_00000F_CP_PROG_DELAY_VALUE(x)              (((x) & 0xFF) << 4)
#घोषणा   G_00000F_CP_PROG_DELAY_VALUE(x)              (((x) >> 4) & 0xFF)
#घोषणा   C_00000F_CP_PROG_DELAY_VALUE                 0xFFFFF00F
#घोषणा   S_00000F_CP_LOWER_POWER_IDLE(x)              (((x) & 0xFF) << 12)
#घोषणा   G_00000F_CP_LOWER_POWER_IDLE(x)              (((x) >> 12) & 0xFF)
#घोषणा   C_00000F_CP_LOWER_POWER_IDLE                 0xFFF00FFF
#घोषणा   S_00000F_CP_LOWER_POWER_IGNORE(x)            (((x) & 0x1) << 20)
#घोषणा   G_00000F_CP_LOWER_POWER_IGNORE(x)            (((x) >> 20) & 0x1)
#घोषणा   C_00000F_CP_LOWER_POWER_IGNORE               0xFFEFFFFF
#घोषणा   S_00000F_CP_NORMAL_POWER_IGNORE(x)           (((x) & 0x1) << 21)
#घोषणा   G_00000F_CP_NORMAL_POWER_IGNORE(x)           (((x) >> 21) & 0x1)
#घोषणा   C_00000F_CP_NORMAL_POWER_IGNORE              0xFFDFFFFF
#घोषणा   S_00000F_SPARE(x)                            (((x) & 0x3) << 22)
#घोषणा   G_00000F_SPARE(x)                            (((x) >> 22) & 0x3)
#घोषणा   C_00000F_SPARE                               0xFF3FFFFF
#घोषणा   S_00000F_CP_NORMAL_POWER_BUSY(x)             (((x) & 0xFF) << 24)
#घोषणा   G_00000F_CP_NORMAL_POWER_BUSY(x)             (((x) >> 24) & 0xFF)
#घोषणा   C_00000F_CP_NORMAL_POWER_BUSY                0x00FFFFFF
#घोषणा R_000011_E2_DYN_CNTL                         0x000011
#घोषणा   S_000011_E2_FORCEON(x)                       (((x) & 0x1) << 0)
#घोषणा   G_000011_E2_FORCEON(x)                       (((x) >> 0) & 0x1)
#घोषणा   C_000011_E2_FORCEON                          0xFFFFFFFE
#घोषणा   S_000011_E2_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 1)
#घोषणा   G_000011_E2_MAX_DYN_STOP_LAT(x)              (((x) >> 1) & 0x1)
#घोषणा   C_000011_E2_MAX_DYN_STOP_LAT                 0xFFFFFFFD
#घोषणा   S_000011_E2_CLOCK_STATUS(x)                  (((x) & 0x1) << 2)
#घोषणा   G_000011_E2_CLOCK_STATUS(x)                  (((x) >> 2) & 0x1)
#घोषणा   C_000011_E2_CLOCK_STATUS                     0xFFFFFFFB
#घोषणा   S_000011_E2_PROG_SHUTOFF(x)                  (((x) & 0x1) << 3)
#घोषणा   G_000011_E2_PROG_SHUTOFF(x)                  (((x) >> 3) & 0x1)
#घोषणा   C_000011_E2_PROG_SHUTOFF                     0xFFFFFFF7
#घोषणा   S_000011_E2_PROG_DELAY_VALUE(x)              (((x) & 0xFF) << 4)
#घोषणा   G_000011_E2_PROG_DELAY_VALUE(x)              (((x) >> 4) & 0xFF)
#घोषणा   C_000011_E2_PROG_DELAY_VALUE                 0xFFFFF00F
#घोषणा   S_000011_E2_LOWER_POWER_IDLE(x)              (((x) & 0xFF) << 12)
#घोषणा   G_000011_E2_LOWER_POWER_IDLE(x)              (((x) >> 12) & 0xFF)
#घोषणा   C_000011_E2_LOWER_POWER_IDLE                 0xFFF00FFF
#घोषणा   S_000011_E2_LOWER_POWER_IGNORE(x)            (((x) & 0x1) << 20)
#घोषणा   G_000011_E2_LOWER_POWER_IGNORE(x)            (((x) >> 20) & 0x1)
#घोषणा   C_000011_E2_LOWER_POWER_IGNORE               0xFFEFFFFF
#घोषणा   S_000011_E2_NORMAL_POWER_IGNORE(x)           (((x) & 0x1) << 21)
#घोषणा   G_000011_E2_NORMAL_POWER_IGNORE(x)           (((x) >> 21) & 0x1)
#घोषणा   C_000011_E2_NORMAL_POWER_IGNORE              0xFFDFFFFF
#घोषणा   S_000011_SPARE(x)                            (((x) & 0x3) << 22)
#घोषणा   G_000011_SPARE(x)                            (((x) >> 22) & 0x3)
#घोषणा   C_000011_SPARE                               0xFF3FFFFF
#घोषणा   S_000011_E2_NORMAL_POWER_BUSY(x)             (((x) & 0xFF) << 24)
#घोषणा   G_000011_E2_NORMAL_POWER_BUSY(x)             (((x) >> 24) & 0xFF)
#घोषणा   C_000011_E2_NORMAL_POWER_BUSY                0x00FFFFFF
#घोषणा R_000013_IDCT_DYN_CNTL                       0x000013
#घोषणा   S_000013_IDCT_FORCEON(x)                     (((x) & 0x1) << 0)
#घोषणा   G_000013_IDCT_FORCEON(x)                     (((x) >> 0) & 0x1)
#घोषणा   C_000013_IDCT_FORCEON                        0xFFFFFFFE
#घोषणा   S_000013_IDCT_MAX_DYN_STOP_LAT(x)            (((x) & 0x1) << 1)
#घोषणा   G_000013_IDCT_MAX_DYN_STOP_LAT(x)            (((x) >> 1) & 0x1)
#घोषणा   C_000013_IDCT_MAX_DYN_STOP_LAT               0xFFFFFFFD
#घोषणा   S_000013_IDCT_CLOCK_STATUS(x)                (((x) & 0x1) << 2)
#घोषणा   G_000013_IDCT_CLOCK_STATUS(x)                (((x) >> 2) & 0x1)
#घोषणा   C_000013_IDCT_CLOCK_STATUS                   0xFFFFFFFB
#घोषणा   S_000013_IDCT_PROG_SHUTOFF(x)                (((x) & 0x1) << 3)
#घोषणा   G_000013_IDCT_PROG_SHUTOFF(x)                (((x) >> 3) & 0x1)
#घोषणा   C_000013_IDCT_PROG_SHUTOFF                   0xFFFFFFF7
#घोषणा   S_000013_IDCT_PROG_DELAY_VALUE(x)            (((x) & 0xFF) << 4)
#घोषणा   G_000013_IDCT_PROG_DELAY_VALUE(x)            (((x) >> 4) & 0xFF)
#घोषणा   C_000013_IDCT_PROG_DELAY_VALUE               0xFFFFF00F
#घोषणा   S_000013_IDCT_LOWER_POWER_IDLE(x)            (((x) & 0xFF) << 12)
#घोषणा   G_000013_IDCT_LOWER_POWER_IDLE(x)            (((x) >> 12) & 0xFF)
#घोषणा   C_000013_IDCT_LOWER_POWER_IDLE               0xFFF00FFF
#घोषणा   S_000013_IDCT_LOWER_POWER_IGNORE(x)          (((x) & 0x1) << 20)
#घोषणा   G_000013_IDCT_LOWER_POWER_IGNORE(x)          (((x) >> 20) & 0x1)
#घोषणा   C_000013_IDCT_LOWER_POWER_IGNORE             0xFFEFFFFF
#घोषणा   S_000013_IDCT_NORMAL_POWER_IGNORE(x)         (((x) & 0x1) << 21)
#घोषणा   G_000013_IDCT_NORMAL_POWER_IGNORE(x)         (((x) >> 21) & 0x1)
#घोषणा   C_000013_IDCT_NORMAL_POWER_IGNORE            0xFFDFFFFF
#घोषणा   S_000013_SPARE(x)                            (((x) & 0x3) << 22)
#घोषणा   G_000013_SPARE(x)                            (((x) >> 22) & 0x3)
#घोषणा   C_000013_SPARE                               0xFF3FFFFF
#घोषणा   S_000013_IDCT_NORMAL_POWER_BUSY(x)           (((x) & 0xFF) << 24)
#घोषणा   G_000013_IDCT_NORMAL_POWER_BUSY(x)           (((x) >> 24) & 0xFF)
#घोषणा   C_000013_IDCT_NORMAL_POWER_BUSY              0x00FFFFFF

#पूर्ण_अगर
