<शैली गुरु>
/* SPDX-License-Identअगरier: MIT*/
/*
 * Copyright oडट 2003-2018 Intel Corporation
 */

#अगर_अघोषित _INTEL_GPU_COMMANDS_H_
#घोषणा _INTEL_GPU_COMMANDS_H_

#समावेश <linux/bitops.h>

/*
 * Target address alignments required क्रम GPU access e.g.
 * MI_STORE_DWORD_IMM.
 */
#घोषणा alignof_dword 4
#घोषणा alignof_qword 8

/*
 * Inकाष्ठाion field definitions used by the command parser
 */
#घोषणा INSTR_CLIENT_SHIFT      29
#घोषणा   INSTR_MI_CLIENT       0x0
#घोषणा   INSTR_BC_CLIENT       0x2
#घोषणा   INSTR_RC_CLIENT       0x3
#घोषणा INSTR_SUBCLIENT_SHIFT   27
#घोषणा INSTR_SUBCLIENT_MASK    0x18000000
#घोषणा   INSTR_MEDIA_SUBCLIENT 0x2
#घोषणा INSTR_26_TO_24_MASK	0x7000000
#घोषणा   INSTR_26_TO_24_SHIFT	24

/*
 * Memory पूर्णांकerface inकाष्ठाions used by the kernel
 */
#घोषणा MI_INSTR(opcode, flags) (((opcode) << 23) | (flags))
/* Many MI commands use bit 22 of the header dword क्रम GGTT vs PPGTT */
#घोषणा  MI_GLOBAL_GTT    (1<<22)

#घोषणा MI_NOOP			MI_INSTR(0, 0)
#घोषणा MI_USER_INTERRUPT	MI_INSTR(0x02, 0)
#घोषणा MI_WAIT_FOR_EVENT       MI_INSTR(0x03, 0)
#घोषणा   MI_WAIT_FOR_OVERLAY_FLIP	(1<<16)
#घोषणा   MI_WAIT_FOR_PLANE_B_FLIP      (1<<6)
#घोषणा   MI_WAIT_FOR_PLANE_A_FLIP      (1<<2)
#घोषणा   MI_WAIT_FOR_PLANE_A_SCANLINES (1<<1)
#घोषणा MI_FLUSH		MI_INSTR(0x04, 0)
#घोषणा   MI_READ_FLUSH		(1 << 0)
#घोषणा   MI_EXE_FLUSH		(1 << 1)
#घोषणा   MI_NO_WRITE_FLUSH	(1 << 2)
#घोषणा   MI_SCENE_COUNT	(1 << 3) /* just increment scene count */
#घोषणा   MI_END_SCENE		(1 << 4) /* flush binner and incr scene count */
#घोषणा   MI_INVALIDATE_ISP	(1 << 5) /* invalidate indirect state poपूर्णांकers */
#घोषणा MI_REPORT_HEAD		MI_INSTR(0x07, 0)
#घोषणा MI_ARB_ON_OFF		MI_INSTR(0x08, 0)
#घोषणा   MI_ARB_ENABLE			(1<<0)
#घोषणा   MI_ARB_DISABLE		(0<<0)
#घोषणा MI_BATCH_BUFFER_END	MI_INSTR(0x0a, 0)
#घोषणा MI_SUSPEND_FLUSH	MI_INSTR(0x0b, 0)
#घोषणा   MI_SUSPEND_FLUSH_EN	(1<<0)
#घोषणा MI_SET_APPID		MI_INSTR(0x0e, 0)
#घोषणा MI_OVERLAY_FLIP		MI_INSTR(0x11, 0)
#घोषणा   MI_OVERLAY_CONTINUE	(0x0<<21)
#घोषणा   MI_OVERLAY_ON		(0x1<<21)
#घोषणा   MI_OVERLAY_OFF	(0x2<<21)
#घोषणा MI_LOAD_SCAN_LINES_INCL MI_INSTR(0x12, 0)
#घोषणा MI_DISPLAY_FLIP		MI_INSTR(0x14, 2)
#घोषणा MI_DISPLAY_FLIP_I915	MI_INSTR(0x14, 1)
#घोषणा   MI_DISPLAY_FLIP_PLANE(n) ((n) << 20)
/* IVB has funny definitions क्रम which plane to flip. */
#घोषणा   MI_DISPLAY_FLIP_IVB_PLANE_A  (0 << 19)
#घोषणा   MI_DISPLAY_FLIP_IVB_PLANE_B  (1 << 19)
#घोषणा   MI_DISPLAY_FLIP_IVB_SPRITE_A (2 << 19)
#घोषणा   MI_DISPLAY_FLIP_IVB_SPRITE_B (3 << 19)
#घोषणा   MI_DISPLAY_FLIP_IVB_PLANE_C  (4 << 19)
#घोषणा   MI_DISPLAY_FLIP_IVB_SPRITE_C (5 << 19)
/* SKL ones */
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_1_A	(0 << 8)
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_1_B	(1 << 8)
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_1_C	(2 << 8)
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_2_A	(4 << 8)
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_2_B	(5 << 8)
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_2_C	(6 << 8)
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_3_A	(7 << 8)
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_3_B	(8 << 8)
#घोषणा   MI_DISPLAY_FLIP_SKL_PLANE_3_C	(9 << 8)
#घोषणा MI_SEMAPHORE_MBOX	MI_INSTR(0x16, 1) /* gen6, gen7 */
#घोषणा   MI_SEMAPHORE_GLOBAL_GTT    (1<<22)
#घोषणा   MI_SEMAPHORE_UPDATE	    (1<<21)
#घोषणा   MI_SEMAPHORE_COMPARE	    (1<<20)
#घोषणा   MI_SEMAPHORE_REGISTER	    (1<<18)
#घोषणा   MI_SEMAPHORE_SYNC_VR	    (0<<16) /* RCS  रुको क्रम VCS  (RVSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_VER	    (1<<16) /* RCS  रुको क्रम VECS (RVESYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_BR	    (2<<16) /* RCS  रुको क्रम BCS  (RBSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_BV	    (0<<16) /* VCS  रुको क्रम BCS  (VBSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_VEV	    (1<<16) /* VCS  रुको क्रम VECS (VVESYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_RV	    (2<<16) /* VCS  रुको क्रम RCS  (VRSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_RB	    (0<<16) /* BCS  रुको क्रम RCS  (BRSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_VEB	    (1<<16) /* BCS  रुको क्रम VECS (BVESYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_VB	    (2<<16) /* BCS  रुको क्रम VCS  (BVSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_BVE	    (0<<16) /* VECS रुको क्रम BCS  (VEBSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_VVE	    (1<<16) /* VECS रुको क्रम VCS  (VEVSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_RVE	    (2<<16) /* VECS रुको क्रम RCS  (VERSYNC) */
#घोषणा   MI_SEMAPHORE_SYNC_INVALID (3<<16)
#घोषणा   MI_SEMAPHORE_SYNC_MASK    (3<<16)
#घोषणा MI_SET_CONTEXT		MI_INSTR(0x18, 0)
#घोषणा   MI_MM_SPACE_GTT		(1<<8)
#घोषणा   MI_MM_SPACE_PHYSICAL		(0<<8)
#घोषणा   MI_SAVE_EXT_STATE_EN		(1<<3)
#घोषणा   MI_RESTORE_EXT_STATE_EN	(1<<2)
#घोषणा   MI_FORCE_RESTORE		(1<<1)
#घोषणा   MI_RESTORE_INHIBIT		(1<<0)
#घोषणा   HSW_MI_RS_SAVE_STATE_EN       (1<<3)
#घोषणा   HSW_MI_RS_RESTORE_STATE_EN    (1<<2)
#घोषणा MI_SEMAPHORE_SIGNAL	MI_INSTR(0x1b, 0) /* GEN8+ */
#घोषणा   MI_SEMAPHORE_TARGET(engine)	((engine)<<15)
#घोषणा MI_SEMAPHORE_WAIT	MI_INSTR(0x1c, 2) /* GEN8+ */
#घोषणा MI_SEMAPHORE_WAIT_TOKEN	MI_INSTR(0x1c, 3) /* GEN12+ */
#घोषणा   MI_SEMAPHORE_POLL		(1 << 15)
#घोषणा   MI_SEMAPHORE_SAD_GT_SDD	(0 << 12)
#घोषणा   MI_SEMAPHORE_SAD_GTE_SDD	(1 << 12)
#घोषणा   MI_SEMAPHORE_SAD_LT_SDD	(2 << 12)
#घोषणा   MI_SEMAPHORE_SAD_LTE_SDD	(3 << 12)
#घोषणा   MI_SEMAPHORE_SAD_EQ_SDD	(4 << 12)
#घोषणा   MI_SEMAPHORE_SAD_NEQ_SDD	(5 << 12)
#घोषणा   MI_SEMAPHORE_TOKEN_MASK	REG_GENMASK(9, 5)
#घोषणा   MI_SEMAPHORE_TOKEN_SHIFT	5
#घोषणा MI_STORE_DWORD_IMM	MI_INSTR(0x20, 1)
#घोषणा MI_STORE_DWORD_IMM_GEN4	MI_INSTR(0x20, 2)
#घोषणा   MI_MEM_VIRTUAL	(1 << 22) /* 945,g33,965 */
#घोषणा   MI_USE_GGTT		(1 << 22) /* g4x+ */
#घोषणा MI_STORE_DWORD_INDEX	MI_INSTR(0x21, 1)
/*
 * Official पूर्णांकel करोcs are somewhat sloppy concerning MI_LOAD_REGISTER_IMM:
 * - Always issue a MI_NOOP _beक्रमe_ the MI_LOAD_REGISTER_IMM - otherwise hw
 *   simply ignores the रेजिस्टर load under certain conditions.
 * - One can actually load arbitrary many arbitrary रेजिस्टरs: Simply issue x
 *   address/value pairs. Don't overdue it, though, x <= 2^4 must hold!
 */
#घोषणा MI_LOAD_REGISTER_IMM(x)	MI_INSTR(0x22, 2*(x)-1)
/* Gen11+. addr = base + (ctx_restore ? offset & GENMASK(12,2) : offset) */
#घोषणा   MI_LRI_LRM_CS_MMIO		REG_BIT(19)
#घोषणा   MI_LRI_FORCE_POSTED		(1<<12)
#घोषणा MI_LOAD_REGISTER_IMM_MAX_REGS (126)
#घोषणा MI_STORE_REGISTER_MEM        MI_INSTR(0x24, 1)
#घोषणा MI_STORE_REGISTER_MEM_GEN8   MI_INSTR(0x24, 2)
#घोषणा   MI_SRM_LRM_GLOBAL_GTT		(1<<22)
#घोषणा MI_FLUSH_DW		MI_INSTR(0x26, 1) /* क्रम GEN6 */
#घोषणा   MI_FLUSH_DW_STORE_INDEX	(1<<21)
#घोषणा   MI_INVALIDATE_TLB		(1<<18)
#घोषणा   MI_FLUSH_DW_OP_STOREDW	(1<<14)
#घोषणा   MI_FLUSH_DW_OP_MASK		(3<<14)
#घोषणा   MI_FLUSH_DW_NOTIFY		(1<<8)
#घोषणा   MI_INVALIDATE_BSD		(1<<7)
#घोषणा   MI_FLUSH_DW_USE_GTT		(1<<2)
#घोषणा   MI_FLUSH_DW_USE_PPGTT		(0<<2)
#घोषणा MI_LOAD_REGISTER_MEM	   MI_INSTR(0x29, 1)
#घोषणा MI_LOAD_REGISTER_MEM_GEN8  MI_INSTR(0x29, 2)
#घोषणा MI_LOAD_REGISTER_REG    MI_INSTR(0x2A, 1)
#घोषणा   MI_LRR_SOURCE_CS_MMIO		REG_BIT(18)
#घोषणा MI_BATCH_BUFFER		MI_INSTR(0x30, 1)
#घोषणा   MI_BATCH_NON_SECURE		(1)
/* क्रम snb/ivb/vlv this also means "batch in ppgtt" when ppgtt is enabled. */
#घोषणा   MI_BATCH_NON_SECURE_I965	(1<<8)
#घोषणा   MI_BATCH_PPGTT_HSW		(1<<8)
#घोषणा   MI_BATCH_NON_SECURE_HSW	(1<<13)
#घोषणा MI_BATCH_BUFFER_START	MI_INSTR(0x31, 0)
#घोषणा   MI_BATCH_GTT		    (2<<6) /* aliased with (1<<7) on gen4 */
#घोषणा MI_BATCH_BUFFER_START_GEN8	MI_INSTR(0x31, 1)
#घोषणा   MI_BATCH_RESOURCE_STREAMER REG_BIT(10)
#घोषणा   MI_BATCH_PREDICATE         REG_BIT(15) /* HSW+ on RCS only*/

/*
 * 3D inकाष्ठाions used by the kernel
 */
#घोषणा GFX_INSTR(opcode, flags) ((0x3 << 29) | ((opcode) << 24) | (flags))

#घोषणा GEN9_MEDIA_POOL_STATE     ((0x3 << 29) | (0x2 << 27) | (0x5 << 16) | 4)
#घोषणा   GEN9_MEDIA_POOL_ENABLE  (1 << 31)
#घोषणा GFX_OP_RASTER_RULES    ((0x3<<29)|(0x7<<24))
#घोषणा GFX_OP_SCISSOR         ((0x3<<29)|(0x1c<<24)|(0x10<<19))
#घोषणा   SC_UPDATE_SCISSOR       (0x1<<1)
#घोषणा   SC_ENABLE_MASK          (0x1<<0)
#घोषणा   SC_ENABLE               (0x1<<0)
#घोषणा GFX_OP_LOAD_INसूचीECT   ((0x3<<29)|(0x1d<<24)|(0x7<<16))
#घोषणा GFX_OP_SCISSOR_INFO    ((0x3<<29)|(0x1d<<24)|(0x81<<16)|(0x1))
#घोषणा   SCI_YMIN_MASK      (0xffff<<16)
#घोषणा   SCI_XMIN_MASK      (0xffff<<0)
#घोषणा   SCI_YMAX_MASK      (0xffff<<16)
#घोषणा   SCI_XMAX_MASK      (0xffff<<0)
#घोषणा GFX_OP_SCISSOR_ENABLE	 ((0x3<<29)|(0x1c<<24)|(0x10<<19))
#घोषणा GFX_OP_SCISSOR_RECT	 ((0x3<<29)|(0x1d<<24)|(0x81<<16)|1)
#घोषणा GFX_OP_COLOR_FACTOR      ((0x3<<29)|(0x1d<<24)|(0x1<<16)|0x0)
#घोषणा GFX_OP_STIPPLE           ((0x3<<29)|(0x1d<<24)|(0x83<<16))
#घोषणा GFX_OP_MAP_INFO          ((0x3<<29)|(0x1d<<24)|0x4)
#घोषणा GFX_OP_DESTBUFFER_VARS   ((0x3<<29)|(0x1d<<24)|(0x85<<16)|0x0)
#घोषणा GFX_OP_DESTBUFFER_INFO	 ((0x3<<29)|(0x1d<<24)|(0x8e<<16)|1)
#घोषणा GFX_OP_DRAWRECT_INFO     ((0x3<<29)|(0x1d<<24)|(0x80<<16)|(0x3))
#घोषणा GFX_OP_DRAWRECT_INFO_I965  ((0x7900<<16)|0x2)

#घोषणा COLOR_BLT_CMD			(2 << 29 | 0x40 << 22 | (5 - 2))
#घोषणा XY_COLOR_BLT_CMD		(2 << 29 | 0x50 << 22)
#घोषणा SRC_COPY_BLT_CMD		(2 << 29 | 0x43 << 22)
#घोषणा GEN9_XY_FAST_COPY_BLT_CMD	(2 << 29 | 0x42 << 22)
#घोषणा XY_SRC_COPY_BLT_CMD		(2 << 29 | 0x53 << 22)
#घोषणा XY_MONO_SRC_COPY_IMM_BLT	(2 << 29 | 0x71 << 22 | 5)
#घोषणा   BLT_WRITE_A			(2<<20)
#घोषणा   BLT_WRITE_RGB			(1<<20)
#घोषणा   BLT_WRITE_RGBA		(BLT_WRITE_RGB | BLT_WRITE_A)
#घोषणा   BLT_DEPTH_8			(0<<24)
#घोषणा   BLT_DEPTH_16_565		(1<<24)
#घोषणा   BLT_DEPTH_16_1555		(2<<24)
#घोषणा   BLT_DEPTH_32			(3<<24)
#घोषणा   BLT_ROP_SRC_COPY		(0xcc<<16)
#घोषणा   BLT_ROP_COLOR_COPY		(0xf0<<16)
#घोषणा XY_SRC_COPY_BLT_SRC_TILED	(1<<15) /* 965+ only */
#घोषणा XY_SRC_COPY_BLT_DST_TILED	(1<<11) /* 965+ only */
#घोषणा CMD_OP_DISPLAYBUFFER_INFO ((0x0<<29)|(0x14<<23)|2)
#घोषणा   ASYNC_FLIP                (1<<22)
#घोषणा   DISPLAY_PLANE_A           (0<<20)
#घोषणा   DISPLAY_PLANE_B           (1<<20)
#घोषणा GFX_OP_PIPE_CONTROL(len)	((0x3<<29)|(0x3<<27)|(0x2<<24)|((len)-2))
#घोषणा   PIPE_CONTROL_COMMAND_CACHE_INVALIDATE		(1<<29) /* gen11+ */
#घोषणा   PIPE_CONTROL_TILE_CACHE_FLUSH			(1<<28) /* gen11+ */
#घोषणा   PIPE_CONTROL_FLUSH_L3				(1<<27)
#घोषणा   PIPE_CONTROL_GLOBAL_GTT_IVB			(1<<24) /* gen7+ */
#घोषणा   PIPE_CONTROL_MMIO_WRITE			(1<<23)
#घोषणा   PIPE_CONTROL_STORE_DATA_INDEX			(1<<21)
#घोषणा   PIPE_CONTROL_CS_STALL				(1<<20)
#घोषणा   PIPE_CONTROL_TLB_INVALIDATE			(1<<18)
#घोषणा   PIPE_CONTROL_MEDIA_STATE_CLEAR		(1<<16)
#घोषणा   PIPE_CONTROL_WRITE_TIMESTAMP			(3<<14)
#घोषणा   PIPE_CONTROL_QW_WRITE				(1<<14)
#घोषणा   PIPE_CONTROL_POST_SYNC_OP_MASK                (3<<14)
#घोषणा   PIPE_CONTROL_DEPTH_STALL			(1<<13)
#घोषणा   PIPE_CONTROL_WRITE_FLUSH			(1<<12)
#घोषणा   PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH	(1<<12) /* gen6+ */
#घोषणा   PIPE_CONTROL_INSTRUCTION_CACHE_INVALIDATE	(1<<11) /* MBZ on ILK */
#घोषणा   PIPE_CONTROL_TEXTURE_CACHE_INVALIDATE		(1<<10) /* GM45+ only */
#घोषणा   PIPE_CONTROL_INसूचीECT_STATE_DISABLE		(1<<9)
#घोषणा   PIPE_CONTROL0_HDC_PIPELINE_FLUSH		REG_BIT(9)  /* gen12 */
#घोषणा   PIPE_CONTROL_NOTIFY				(1<<8)
#घोषणा   PIPE_CONTROL_FLUSH_ENABLE			(1<<7) /* gen7+ */
#घोषणा   PIPE_CONTROL_DC_FLUSH_ENABLE			(1<<5)
#घोषणा   PIPE_CONTROL_VF_CACHE_INVALIDATE		(1<<4)
#घोषणा   PIPE_CONTROL_CONST_CACHE_INVALIDATE		(1<<3)
#घोषणा   PIPE_CONTROL_STATE_CACHE_INVALIDATE		(1<<2)
#घोषणा   PIPE_CONTROL_STALL_AT_SCOREBOARD		(1<<1)
#घोषणा   PIPE_CONTROL_DEPTH_CACHE_FLUSH		(1<<0)
#घोषणा   PIPE_CONTROL_GLOBAL_GTT (1<<2) /* in addr dword */

#घोषणा MI_MATH(x)			MI_INSTR(0x1a, (x) - 1)
#घोषणा MI_MATH_INSTR(opcode, op1, op2) ((opcode) << 20 | (op1) << 10 | (op2))
/* Opcodes क्रम MI_MATH_INSTR */
#घोषणा   MI_MATH_NOOP			MI_MATH_INSTR(0x000, 0x0, 0x0)
#घोषणा   MI_MATH_LOAD(op1, op2)	MI_MATH_INSTR(0x080, op1, op2)
#घोषणा   MI_MATH_LOADINV(op1, op2)	MI_MATH_INSTR(0x480, op1, op2)
#घोषणा   MI_MATH_LOAD0(op1)		MI_MATH_INSTR(0x081, op1)
#घोषणा   MI_MATH_LOAD1(op1)		MI_MATH_INSTR(0x481, op1)
#घोषणा   MI_MATH_ADD			MI_MATH_INSTR(0x100, 0x0, 0x0)
#घोषणा   MI_MATH_SUB			MI_MATH_INSTR(0x101, 0x0, 0x0)
#घोषणा   MI_MATH_AND			MI_MATH_INSTR(0x102, 0x0, 0x0)
#घोषणा   MI_MATH_OR			MI_MATH_INSTR(0x103, 0x0, 0x0)
#घोषणा   MI_MATH_XOR			MI_MATH_INSTR(0x104, 0x0, 0x0)
#घोषणा   MI_MATH_STORE(op1, op2)	MI_MATH_INSTR(0x180, op1, op2)
#घोषणा   MI_MATH_STOREINV(op1, op2)	MI_MATH_INSTR(0x580, op1, op2)
/* Registers used as opeअक्रमs in MI_MATH_INSTR */
#घोषणा   MI_MATH_REG(x)		(x)
#घोषणा   MI_MATH_REG_SRCA		0x20
#घोषणा   MI_MATH_REG_SRCB		0x21
#घोषणा   MI_MATH_REG_ACCU		0x31
#घोषणा   MI_MATH_REG_ZF		0x32
#घोषणा   MI_MATH_REG_CF		0x33

/*
 * Commands used only by the command parser
 */
#घोषणा MI_SET_PREDICATE        MI_INSTR(0x01, 0)
#घोषणा MI_ARB_CHECK            MI_INSTR(0x05, 0)
#घोषणा MI_RS_CONTROL           MI_INSTR(0x06, 0)
#घोषणा MI_URB_ATOMIC_ALLOC     MI_INSTR(0x09, 0)
#घोषणा MI_PREDICATE            MI_INSTR(0x0C, 0)
#घोषणा MI_RS_CONTEXT           MI_INSTR(0x0F, 0)
#घोषणा MI_TOPOLOGY_FILTER      MI_INSTR(0x0D, 0)
#घोषणा MI_LOAD_SCAN_LINES_EXCL MI_INSTR(0x13, 0)
#घोषणा MI_URB_CLEAR            MI_INSTR(0x19, 0)
#घोषणा MI_UPDATE_GTT           MI_INSTR(0x23, 0)
#घोषणा MI_CLFLUSH              MI_INSTR(0x27, 0)
#घोषणा MI_REPORT_PERF_COUNT    MI_INSTR(0x28, 0)
#घोषणा   MI_REPORT_PERF_COUNT_GGTT (1<<0)
#घोषणा MI_RS_STORE_DATA_IMM    MI_INSTR(0x2B, 0)
#घोषणा MI_LOAD_URB_MEM         MI_INSTR(0x2C, 0)
#घोषणा MI_STORE_URB_MEM        MI_INSTR(0x2D, 0)
#घोषणा MI_CONDITIONAL_BATCH_BUFFER_END MI_INSTR(0x36, 0)

#घोषणा STATE_BASE_ADDRESS \
	((0x3 << 29) | (0x0 << 27) | (0x1 << 24) | (0x1 << 16))
#घोषणा BASE_ADDRESS_MODIFY		REG_BIT(0)
#घोषणा PIPELINE_SELECT \
	((0x3 << 29) | (0x1 << 27) | (0x1 << 24) | (0x4 << 16))
#घोषणा PIPELINE_SELECT_MEDIA	       REG_BIT(0)
#घोषणा GFX_OP_3DSTATE_VF_STATISTICS \
	((0x3 << 29) | (0x1 << 27) | (0x0 << 24) | (0xB << 16))
#घोषणा MEDIA_VFE_STATE \
	((0x3 << 29) | (0x2 << 27) | (0x0 << 24) | (0x0 << 16))
#घोषणा  MEDIA_VFE_STATE_MMIO_ACCESS_MASK (0x18)
#घोषणा MEDIA_INTERFACE_DESCRIPTOR_LOAD \
	((0x3 << 29) | (0x2 << 27) | (0x0 << 24) | (0x2 << 16))
#घोषणा MEDIA_OBJECT \
	((0x3 << 29) | (0x2 << 27) | (0x1 << 24) | (0x0 << 16))
#घोषणा GPGPU_OBJECT                   ((0x3<<29)|(0x2<<27)|(0x1<<24)|(0x4<<16))
#घोषणा GPGPU_WALKER                   ((0x3<<29)|(0x2<<27)|(0x1<<24)|(0x5<<16))
#घोषणा GFX_OP_3DSTATE_DX9_CONSTANTF_VS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x39<<16))
#घोषणा GFX_OP_3DSTATE_DX9_CONSTANTF_PS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x3A<<16))
#घोषणा GFX_OP_3DSTATE_SO_DECL_LIST \
	((0x3<<29)|(0x3<<27)|(0x1<<24)|(0x17<<16))

#घोषणा GFX_OP_3DSTATE_BINDING_TABLE_EDIT_VS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x43<<16))
#घोषणा GFX_OP_3DSTATE_BINDING_TABLE_EDIT_GS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x44<<16))
#घोषणा GFX_OP_3DSTATE_BINDING_TABLE_EDIT_HS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x45<<16))
#घोषणा GFX_OP_3DSTATE_BINDING_TABLE_EDIT_DS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x46<<16))
#घोषणा GFX_OP_3DSTATE_BINDING_TABLE_EDIT_PS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x47<<16))

#घोषणा MFX_WAIT  ((0x3<<29)|(0x1<<27)|(0x0<<16))

#घोषणा COLOR_BLT     ((0x2<<29)|(0x40<<22))
#घोषणा SRC_COPY_BLT  ((0x2<<29)|(0x43<<22))

/*
 * Used to convert any address to canonical क्रमm.
 * Starting from gen8, some commands (e.g. STATE_BASE_ADDRESS,
 * MI_LOAD_REGISTER_MEM and others, see Broadwell PRM Vol2a) require the
 * addresses to be in a canonical क्रमm:
 * "GraphicsAddress[63:48] are ignored by the HW and assumed to be in correct
 * canonical क्रमm [63:48] == [47]."
 */
#घोषणा GEN8_HIGH_ADDRESS_BIT 47
अटल अंतरभूत u64 gen8_canonical_addr(u64 address)
अणु
	वापस sign_extend64(address, GEN8_HIGH_ADDRESS_BIT);
पूर्ण

अटल अंतरभूत u64 gen8_noncanonical_addr(u64 address)
अणु
	वापस address & GENMASK_ULL(GEN8_HIGH_ADDRESS_BIT, 0);
पूर्ण

अटल अंतरभूत u32 *__gen6_emit_bb_start(u32 *cs, u32 addr, अचिन्हित पूर्णांक flags)
अणु
	*cs++ = MI_BATCH_BUFFER_START | flags;
	*cs++ = addr;

	वापस cs;
पूर्ण

#पूर्ण_अगर /* _INTEL_GPU_COMMANDS_H_ */
