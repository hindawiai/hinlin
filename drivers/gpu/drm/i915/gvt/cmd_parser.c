<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Ke Yu
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *
 * Contributors:
 *    Min He <min.he@पूर्णांकel.com>
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *    Yulei Zhang <yulei.zhang@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#समावेश <linux/slab.h>

#समावेश "i915_drv.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_lrc.h"
#समावेश "gt/intel_ring.h"
#समावेश "gt/intel_gt_requests.h"
#समावेश "gt/shmem_utils.h"
#समावेश "gvt.h"
#समावेश "i915_pvinfo.h"
#समावेश "trace.h"

#समावेश "gem/i915_gem_context.h"
#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_context.h"

#घोषणा INVALID_OP    (~0U)

#घोषणा OP_LEN_MI           9
#घोषणा OP_LEN_2D           10
#घोषणा OP_LEN_3D_MEDIA     16
#घोषणा OP_LEN_MFX_VC       16
#घोषणा OP_LEN_VEBOX	    16

#घोषणा CMD_TYPE(cmd)	(((cmd) >> 29) & 7)

काष्ठा sub_op_bits अणु
	पूर्णांक hi;
	पूर्णांक low;
पूर्ण;
काष्ठा decode_info अणु
	स्थिर अक्षर *name;
	पूर्णांक op_len;
	पूर्णांक nr_sub_op;
	स्थिर काष्ठा sub_op_bits *sub_op;
पूर्ण;

#घोषणा   MAX_CMD_BUDGET			0x7fffffff
#घोषणा   MI_WAIT_FOR_PLANE_C_FLIP_PENDING      (1<<15)
#घोषणा   MI_WAIT_FOR_PLANE_B_FLIP_PENDING      (1<<9)
#घोषणा   MI_WAIT_FOR_PLANE_A_FLIP_PENDING      (1<<1)

#घोषणा   MI_WAIT_FOR_SPRITE_C_FLIP_PENDING      (1<<20)
#घोषणा   MI_WAIT_FOR_SPRITE_B_FLIP_PENDING      (1<<10)
#घोषणा   MI_WAIT_FOR_SPRITE_A_FLIP_PENDING      (1<<2)

/* Render Command Map */

/* MI_* command Opcode (28:23) */
#घोषणा OP_MI_NOOP                          0x0
#घोषणा OP_MI_SET_PREDICATE                 0x1  /* HSW+ */
#घोषणा OP_MI_USER_INTERRUPT                0x2
#घोषणा OP_MI_WAIT_FOR_EVENT                0x3
#घोषणा OP_MI_FLUSH                         0x4
#घोषणा OP_MI_ARB_CHECK                     0x5
#घोषणा OP_MI_RS_CONTROL                    0x6  /* HSW+ */
#घोषणा OP_MI_REPORT_HEAD                   0x7
#घोषणा OP_MI_ARB_ON_OFF                    0x8
#घोषणा OP_MI_URB_ATOMIC_ALLOC              0x9  /* HSW+ */
#घोषणा OP_MI_BATCH_BUFFER_END              0xA
#घोषणा OP_MI_SUSPEND_FLUSH                 0xB
#घोषणा OP_MI_PREDICATE                     0xC  /* IVB+ */
#घोषणा OP_MI_TOPOLOGY_FILTER               0xD  /* IVB+ */
#घोषणा OP_MI_SET_APPID                     0xE  /* IVB+ */
#घोषणा OP_MI_RS_CONTEXT                    0xF  /* HSW+ */
#घोषणा OP_MI_LOAD_SCAN_LINES_INCL          0x12 /* HSW+ */
#घोषणा OP_MI_DISPLAY_FLIP                  0x14
#घोषणा OP_MI_SEMAPHORE_MBOX                0x16
#घोषणा OP_MI_SET_CONTEXT                   0x18
#घोषणा OP_MI_MATH                          0x1A
#घोषणा OP_MI_URB_CLEAR                     0x19
#घोषणा OP_MI_SEMAPHORE_SIGNAL		    0x1B  /* BDW+ */
#घोषणा OP_MI_SEMAPHORE_WAIT		    0x1C  /* BDW+ */

#घोषणा OP_MI_STORE_DATA_IMM                0x20
#घोषणा OP_MI_STORE_DATA_INDEX              0x21
#घोषणा OP_MI_LOAD_REGISTER_IMM             0x22
#घोषणा OP_MI_UPDATE_GTT                    0x23
#घोषणा OP_MI_STORE_REGISTER_MEM            0x24
#घोषणा OP_MI_FLUSH_DW                      0x26
#घोषणा OP_MI_CLFLUSH                       0x27
#घोषणा OP_MI_REPORT_PERF_COUNT             0x28
#घोषणा OP_MI_LOAD_REGISTER_MEM             0x29  /* HSW+ */
#घोषणा OP_MI_LOAD_REGISTER_REG             0x2A  /* HSW+ */
#घोषणा OP_MI_RS_STORE_DATA_IMM             0x2B  /* HSW+ */
#घोषणा OP_MI_LOAD_URB_MEM                  0x2C  /* HSW+ */
#घोषणा OP_MI_STORE_URM_MEM                 0x2D  /* HSW+ */
#घोषणा OP_MI_2E			    0x2E  /* BDW+ */
#घोषणा OP_MI_2F			    0x2F  /* BDW+ */
#घोषणा OP_MI_BATCH_BUFFER_START            0x31

/* Bit definition क्रम dword 0 */
#घोषणा _CMDBIT_BB_START_IN_PPGTT	(1UL << 8)

#घोषणा OP_MI_CONDITIONAL_BATCH_BUFFER_END  0x36

#घोषणा BATCH_BUFFER_ADDR_MASK ((1UL << 32) - (1U << 2))
#घोषणा BATCH_BUFFER_ADDR_HIGH_MASK ((1UL << 16) - (1U))
#घोषणा BATCH_BUFFER_ADR_SPACE_BIT(x)	(((x) >> 8) & 1U)
#घोषणा BATCH_BUFFER_2ND_LEVEL_BIT(x)   ((x) >> 22 & 1U)

/* 2D command: Opcode (28:22) */
#घोषणा OP_2D(x)    ((2<<7) | x)

#घोषणा OP_XY_SETUP_BLT                             OP_2D(0x1)
#घोषणा OP_XY_SETUP_CLIP_BLT                        OP_2D(0x3)
#घोषणा OP_XY_SETUP_MONO_PATTERN_SL_BLT             OP_2D(0x11)
#घोषणा OP_XY_PIXEL_BLT                             OP_2D(0x24)
#घोषणा OP_XY_SCANLINES_BLT                         OP_2D(0x25)
#घोषणा OP_XY_TEXT_BLT                              OP_2D(0x26)
#घोषणा OP_XY_TEXT_IMMEDIATE_BLT                    OP_2D(0x31)
#घोषणा OP_XY_COLOR_BLT                             OP_2D(0x50)
#घोषणा OP_XY_PAT_BLT                               OP_2D(0x51)
#घोषणा OP_XY_MONO_PAT_BLT                          OP_2D(0x52)
#घोषणा OP_XY_SRC_COPY_BLT                          OP_2D(0x53)
#घोषणा OP_XY_MONO_SRC_COPY_BLT                     OP_2D(0x54)
#घोषणा OP_XY_FULL_BLT                              OP_2D(0x55)
#घोषणा OP_XY_FULL_MONO_SRC_BLT                     OP_2D(0x56)
#घोषणा OP_XY_FULL_MONO_PATTERN_BLT                 OP_2D(0x57)
#घोषणा OP_XY_FULL_MONO_PATTERN_MONO_SRC_BLT        OP_2D(0x58)
#घोषणा OP_XY_MONO_PAT_FIXED_BLT                    OP_2D(0x59)
#घोषणा OP_XY_MONO_SRC_COPY_IMMEDIATE_BLT           OP_2D(0x71)
#घोषणा OP_XY_PAT_BLT_IMMEDIATE                     OP_2D(0x72)
#घोषणा OP_XY_SRC_COPY_CHROMA_BLT                   OP_2D(0x73)
#घोषणा OP_XY_FULL_IMMEDIATE_PATTERN_BLT            OP_2D(0x74)
#घोषणा OP_XY_FULL_MONO_SRC_IMMEDIATE_PATTERN_BLT   OP_2D(0x75)
#घोषणा OP_XY_PAT_CHROMA_BLT                        OP_2D(0x76)
#घोषणा OP_XY_PAT_CHROMA_BLT_IMMEDIATE              OP_2D(0x77)

/* 3D/Media Command: Pipeline Type(28:27) Opcode(26:24) Sub Opcode(23:16) */
#घोषणा OP_3D_MEDIA(sub_type, opcode, sub_opcode) \
	((3 << 13) | ((sub_type) << 11) | ((opcode) << 8) | (sub_opcode))

#घोषणा OP_STATE_PREFETCH                       OP_3D_MEDIA(0x0, 0x0, 0x03)

#घोषणा OP_STATE_BASE_ADDRESS                   OP_3D_MEDIA(0x0, 0x1, 0x01)
#घोषणा OP_STATE_SIP                            OP_3D_MEDIA(0x0, 0x1, 0x02)
#घोषणा OP_3D_MEDIA_0_1_4			OP_3D_MEDIA(0x0, 0x1, 0x04)
#घोषणा OP_SWTESS_BASE_ADDRESS			OP_3D_MEDIA(0x0, 0x1, 0x03)

#घोषणा OP_3DSTATE_VF_STATISTICS_GM45           OP_3D_MEDIA(0x1, 0x0, 0x0B)

#घोषणा OP_PIPELINE_SELECT                      OP_3D_MEDIA(0x1, 0x1, 0x04)

#घोषणा OP_MEDIA_VFE_STATE                      OP_3D_MEDIA(0x2, 0x0, 0x0)
#घोषणा OP_MEDIA_CURBE_LOAD                     OP_3D_MEDIA(0x2, 0x0, 0x1)
#घोषणा OP_MEDIA_INTERFACE_DESCRIPTOR_LOAD      OP_3D_MEDIA(0x2, 0x0, 0x2)
#घोषणा OP_MEDIA_GATEWAY_STATE                  OP_3D_MEDIA(0x2, 0x0, 0x3)
#घोषणा OP_MEDIA_STATE_FLUSH                    OP_3D_MEDIA(0x2, 0x0, 0x4)
#घोषणा OP_MEDIA_POOL_STATE                     OP_3D_MEDIA(0x2, 0x0, 0x5)

#घोषणा OP_MEDIA_OBJECT                         OP_3D_MEDIA(0x2, 0x1, 0x0)
#घोषणा OP_MEDIA_OBJECT_PRT                     OP_3D_MEDIA(0x2, 0x1, 0x2)
#घोषणा OP_MEDIA_OBJECT_WALKER                  OP_3D_MEDIA(0x2, 0x1, 0x3)
#घोषणा OP_GPGPU_WALKER                         OP_3D_MEDIA(0x2, 0x1, 0x5)

#घोषणा OP_3DSTATE_CLEAR_PARAMS                 OP_3D_MEDIA(0x3, 0x0, 0x04) /* IVB+ */
#घोषणा OP_3DSTATE_DEPTH_BUFFER                 OP_3D_MEDIA(0x3, 0x0, 0x05) /* IVB+ */
#घोषणा OP_3DSTATE_STENCIL_BUFFER               OP_3D_MEDIA(0x3, 0x0, 0x06) /* IVB+ */
#घोषणा OP_3DSTATE_HIER_DEPTH_BUFFER            OP_3D_MEDIA(0x3, 0x0, 0x07) /* IVB+ */
#घोषणा OP_3DSTATE_VERTEX_BUFFERS               OP_3D_MEDIA(0x3, 0x0, 0x08)
#घोषणा OP_3DSTATE_VERTEX_ELEMENTS              OP_3D_MEDIA(0x3, 0x0, 0x09)
#घोषणा OP_3DSTATE_INDEX_BUFFER                 OP_3D_MEDIA(0x3, 0x0, 0x0A)
#घोषणा OP_3DSTATE_VF_STATISTICS                OP_3D_MEDIA(0x3, 0x0, 0x0B)
#घोषणा OP_3DSTATE_VF                           OP_3D_MEDIA(0x3, 0x0, 0x0C)  /* HSW+ */
#घोषणा OP_3DSTATE_CC_STATE_POINTERS            OP_3D_MEDIA(0x3, 0x0, 0x0E)
#घोषणा OP_3DSTATE_SCISSOR_STATE_POINTERS       OP_3D_MEDIA(0x3, 0x0, 0x0F)
#घोषणा OP_3DSTATE_VS                           OP_3D_MEDIA(0x3, 0x0, 0x10)
#घोषणा OP_3DSTATE_GS                           OP_3D_MEDIA(0x3, 0x0, 0x11)
#घोषणा OP_3DSTATE_CLIP                         OP_3D_MEDIA(0x3, 0x0, 0x12)
#घोषणा OP_3DSTATE_SF                           OP_3D_MEDIA(0x3, 0x0, 0x13)
#घोषणा OP_3DSTATE_WM                           OP_3D_MEDIA(0x3, 0x0, 0x14)
#घोषणा OP_3DSTATE_CONSTANT_VS                  OP_3D_MEDIA(0x3, 0x0, 0x15)
#घोषणा OP_3DSTATE_CONSTANT_GS                  OP_3D_MEDIA(0x3, 0x0, 0x16)
#घोषणा OP_3DSTATE_CONSTANT_PS                  OP_3D_MEDIA(0x3, 0x0, 0x17)
#घोषणा OP_3DSTATE_SAMPLE_MASK                  OP_3D_MEDIA(0x3, 0x0, 0x18)
#घोषणा OP_3DSTATE_CONSTANT_HS                  OP_3D_MEDIA(0x3, 0x0, 0x19) /* IVB+ */
#घोषणा OP_3DSTATE_CONSTANT_DS                  OP_3D_MEDIA(0x3, 0x0, 0x1A) /* IVB+ */
#घोषणा OP_3DSTATE_HS                           OP_3D_MEDIA(0x3, 0x0, 0x1B) /* IVB+ */
#घोषणा OP_3DSTATE_TE                           OP_3D_MEDIA(0x3, 0x0, 0x1C) /* IVB+ */
#घोषणा OP_3DSTATE_DS                           OP_3D_MEDIA(0x3, 0x0, 0x1D) /* IVB+ */
#घोषणा OP_3DSTATE_STREAMOUT                    OP_3D_MEDIA(0x3, 0x0, 0x1E) /* IVB+ */
#घोषणा OP_3DSTATE_SBE                          OP_3D_MEDIA(0x3, 0x0, 0x1F) /* IVB+ */
#घोषणा OP_3DSTATE_PS                           OP_3D_MEDIA(0x3, 0x0, 0x20) /* IVB+ */
#घोषणा OP_3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP OP_3D_MEDIA(0x3, 0x0, 0x21) /* IVB+ */
#घोषणा OP_3DSTATE_VIEWPORT_STATE_POINTERS_CC   OP_3D_MEDIA(0x3, 0x0, 0x23) /* IVB+ */
#घोषणा OP_3DSTATE_BLEND_STATE_POINTERS         OP_3D_MEDIA(0x3, 0x0, 0x24) /* IVB+ */
#घोषणा OP_3DSTATE_DEPTH_STENCIL_STATE_POINTERS OP_3D_MEDIA(0x3, 0x0, 0x25) /* IVB+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_POINTERS_VS    OP_3D_MEDIA(0x3, 0x0, 0x26) /* IVB+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_POINTERS_HS    OP_3D_MEDIA(0x3, 0x0, 0x27) /* IVB+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_POINTERS_DS    OP_3D_MEDIA(0x3, 0x0, 0x28) /* IVB+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_POINTERS_GS    OP_3D_MEDIA(0x3, 0x0, 0x29) /* IVB+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_POINTERS_PS    OP_3D_MEDIA(0x3, 0x0, 0x2A) /* IVB+ */
#घोषणा OP_3DSTATE_SAMPLER_STATE_POINTERS_VS    OP_3D_MEDIA(0x3, 0x0, 0x2B) /* IVB+ */
#घोषणा OP_3DSTATE_SAMPLER_STATE_POINTERS_HS    OP_3D_MEDIA(0x3, 0x0, 0x2C) /* IVB+ */
#घोषणा OP_3DSTATE_SAMPLER_STATE_POINTERS_DS    OP_3D_MEDIA(0x3, 0x0, 0x2D) /* IVB+ */
#घोषणा OP_3DSTATE_SAMPLER_STATE_POINTERS_GS    OP_3D_MEDIA(0x3, 0x0, 0x2E) /* IVB+ */
#घोषणा OP_3DSTATE_SAMPLER_STATE_POINTERS_PS    OP_3D_MEDIA(0x3, 0x0, 0x2F) /* IVB+ */
#घोषणा OP_3DSTATE_URB_VS                       OP_3D_MEDIA(0x3, 0x0, 0x30) /* IVB+ */
#घोषणा OP_3DSTATE_URB_HS                       OP_3D_MEDIA(0x3, 0x0, 0x31) /* IVB+ */
#घोषणा OP_3DSTATE_URB_DS                       OP_3D_MEDIA(0x3, 0x0, 0x32) /* IVB+ */
#घोषणा OP_3DSTATE_URB_GS                       OP_3D_MEDIA(0x3, 0x0, 0x33) /* IVB+ */
#घोषणा OP_3DSTATE_GATHER_CONSTANT_VS           OP_3D_MEDIA(0x3, 0x0, 0x34) /* HSW+ */
#घोषणा OP_3DSTATE_GATHER_CONSTANT_GS           OP_3D_MEDIA(0x3, 0x0, 0x35) /* HSW+ */
#घोषणा OP_3DSTATE_GATHER_CONSTANT_HS           OP_3D_MEDIA(0x3, 0x0, 0x36) /* HSW+ */
#घोषणा OP_3DSTATE_GATHER_CONSTANT_DS           OP_3D_MEDIA(0x3, 0x0, 0x37) /* HSW+ */
#घोषणा OP_3DSTATE_GATHER_CONSTANT_PS           OP_3D_MEDIA(0x3, 0x0, 0x38) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_CONSTANTF_VS             OP_3D_MEDIA(0x3, 0x0, 0x39) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_CONSTANTF_PS             OP_3D_MEDIA(0x3, 0x0, 0x3A) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_CONSTANTI_VS             OP_3D_MEDIA(0x3, 0x0, 0x3B) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_CONSTANTI_PS             OP_3D_MEDIA(0x3, 0x0, 0x3C) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_CONSTANTB_VS             OP_3D_MEDIA(0x3, 0x0, 0x3D) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_CONSTANTB_PS             OP_3D_MEDIA(0x3, 0x0, 0x3E) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_LOCAL_VALID_VS           OP_3D_MEDIA(0x3, 0x0, 0x3F) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_LOCAL_VALID_PS           OP_3D_MEDIA(0x3, 0x0, 0x40) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_GENERATE_ACTIVE_VS       OP_3D_MEDIA(0x3, 0x0, 0x41) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_GENERATE_ACTIVE_PS       OP_3D_MEDIA(0x3, 0x0, 0x42) /* HSW+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_EDIT_VS        OP_3D_MEDIA(0x3, 0x0, 0x43) /* HSW+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_EDIT_GS        OP_3D_MEDIA(0x3, 0x0, 0x44) /* HSW+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_EDIT_HS        OP_3D_MEDIA(0x3, 0x0, 0x45) /* HSW+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_EDIT_DS        OP_3D_MEDIA(0x3, 0x0, 0x46) /* HSW+ */
#घोषणा OP_3DSTATE_BINDING_TABLE_EDIT_PS        OP_3D_MEDIA(0x3, 0x0, 0x47) /* HSW+ */

#घोषणा OP_3DSTATE_VF_INSTANCING 		OP_3D_MEDIA(0x3, 0x0, 0x49) /* BDW+ */
#घोषणा OP_3DSTATE_VF_SGVS  			OP_3D_MEDIA(0x3, 0x0, 0x4A) /* BDW+ */
#घोषणा OP_3DSTATE_VF_TOPOLOGY   		OP_3D_MEDIA(0x3, 0x0, 0x4B) /* BDW+ */
#घोषणा OP_3DSTATE_WM_CHROMAKEY   		OP_3D_MEDIA(0x3, 0x0, 0x4C) /* BDW+ */
#घोषणा OP_3DSTATE_PS_BLEND   			OP_3D_MEDIA(0x3, 0x0, 0x4D) /* BDW+ */
#घोषणा OP_3DSTATE_WM_DEPTH_STENCIL   		OP_3D_MEDIA(0x3, 0x0, 0x4E) /* BDW+ */
#घोषणा OP_3DSTATE_PS_EXTRA   			OP_3D_MEDIA(0x3, 0x0, 0x4F) /* BDW+ */
#घोषणा OP_3DSTATE_RASTER   			OP_3D_MEDIA(0x3, 0x0, 0x50) /* BDW+ */
#घोषणा OP_3DSTATE_SBE_SWIZ   			OP_3D_MEDIA(0x3, 0x0, 0x51) /* BDW+ */
#घोषणा OP_3DSTATE_WM_HZ_OP   			OP_3D_MEDIA(0x3, 0x0, 0x52) /* BDW+ */
#घोषणा OP_3DSTATE_COMPONENT_PACKING		OP_3D_MEDIA(0x3, 0x0, 0x55) /* SKL+ */

#घोषणा OP_3DSTATE_DRAWING_RECTANGLE            OP_3D_MEDIA(0x3, 0x1, 0x00)
#घोषणा OP_3DSTATE_SAMPLER_PALETTE_LOAD0        OP_3D_MEDIA(0x3, 0x1, 0x02)
#घोषणा OP_3DSTATE_CHROMA_KEY                   OP_3D_MEDIA(0x3, 0x1, 0x04)
#घोषणा OP_SNB_3DSTATE_DEPTH_BUFFER             OP_3D_MEDIA(0x3, 0x1, 0x05)
#घोषणा OP_3DSTATE_POLY_STIPPLE_OFFSET          OP_3D_MEDIA(0x3, 0x1, 0x06)
#घोषणा OP_3DSTATE_POLY_STIPPLE_PATTERN         OP_3D_MEDIA(0x3, 0x1, 0x07)
#घोषणा OP_3DSTATE_LINE_STIPPLE                 OP_3D_MEDIA(0x3, 0x1, 0x08)
#घोषणा OP_3DSTATE_AA_LINE_PARAMS               OP_3D_MEDIA(0x3, 0x1, 0x0A)
#घोषणा OP_3DSTATE_GS_SVB_INDEX                 OP_3D_MEDIA(0x3, 0x1, 0x0B)
#घोषणा OP_3DSTATE_SAMPLER_PALETTE_LOAD1        OP_3D_MEDIA(0x3, 0x1, 0x0C)
#घोषणा OP_3DSTATE_MULTISAMPLE_BDW		OP_3D_MEDIA(0x3, 0x0, 0x0D)
#घोषणा OP_SNB_3DSTATE_STENCIL_BUFFER           OP_3D_MEDIA(0x3, 0x1, 0x0E)
#घोषणा OP_SNB_3DSTATE_HIER_DEPTH_BUFFER        OP_3D_MEDIA(0x3, 0x1, 0x0F)
#घोषणा OP_SNB_3DSTATE_CLEAR_PARAMS             OP_3D_MEDIA(0x3, 0x1, 0x10)
#घोषणा OP_3DSTATE_MONOFILTER_SIZE              OP_3D_MEDIA(0x3, 0x1, 0x11)
#घोषणा OP_3DSTATE_PUSH_CONSTANT_ALLOC_VS       OP_3D_MEDIA(0x3, 0x1, 0x12) /* IVB+ */
#घोषणा OP_3DSTATE_PUSH_CONSTANT_ALLOC_HS       OP_3D_MEDIA(0x3, 0x1, 0x13) /* IVB+ */
#घोषणा OP_3DSTATE_PUSH_CONSTANT_ALLOC_DS       OP_3D_MEDIA(0x3, 0x1, 0x14) /* IVB+ */
#घोषणा OP_3DSTATE_PUSH_CONSTANT_ALLOC_GS       OP_3D_MEDIA(0x3, 0x1, 0x15) /* IVB+ */
#घोषणा OP_3DSTATE_PUSH_CONSTANT_ALLOC_PS       OP_3D_MEDIA(0x3, 0x1, 0x16) /* IVB+ */
#घोषणा OP_3DSTATE_SO_DECL_LIST                 OP_3D_MEDIA(0x3, 0x1, 0x17)
#घोषणा OP_3DSTATE_SO_BUFFER                    OP_3D_MEDIA(0x3, 0x1, 0x18)
#घोषणा OP_3DSTATE_BINDING_TABLE_POOL_ALLOC     OP_3D_MEDIA(0x3, 0x1, 0x19) /* HSW+ */
#घोषणा OP_3DSTATE_GATHER_POOL_ALLOC            OP_3D_MEDIA(0x3, 0x1, 0x1A) /* HSW+ */
#घोषणा OP_3DSTATE_DX9_CONSTANT_BUFFER_POOL_ALLOC OP_3D_MEDIA(0x3, 0x1, 0x1B) /* HSW+ */
#घोषणा OP_3DSTATE_SAMPLE_PATTERN               OP_3D_MEDIA(0x3, 0x1, 0x1C)
#घोषणा OP_PIPE_CONTROL                         OP_3D_MEDIA(0x3, 0x2, 0x00)
#घोषणा OP_3DPRIMITIVE                          OP_3D_MEDIA(0x3, 0x3, 0x00)

/* VCCP Command Parser */

/*
 * Below MFX and VBE cmd definition is from vaapi पूर्णांकel driver project (BSD License)
 * git://anongit.मुक्तdesktop.org/vaapi/पूर्णांकel-driver
 * src/i965_defines.h
 *
 */

#घोषणा OP_MFX(pipeline, op, sub_opa, sub_opb)     \
	(3 << 13 | \
	 (pipeline) << 11 | \
	 (op) << 8 | \
	 (sub_opa) << 5 | \
	 (sub_opb))

#घोषणा OP_MFX_PIPE_MODE_SELECT                    OP_MFX(2, 0, 0, 0)  /* ALL */
#घोषणा OP_MFX_SURFACE_STATE                       OP_MFX(2, 0, 0, 1)  /* ALL */
#घोषणा OP_MFX_PIPE_BUF_ADDR_STATE                 OP_MFX(2, 0, 0, 2)  /* ALL */
#घोषणा OP_MFX_IND_OBJ_BASE_ADDR_STATE             OP_MFX(2, 0, 0, 3)  /* ALL */
#घोषणा OP_MFX_BSP_BUF_BASE_ADDR_STATE             OP_MFX(2, 0, 0, 4)  /* ALL */
#घोषणा OP_2_0_0_5                                 OP_MFX(2, 0, 0, 5)  /* ALL */
#घोषणा OP_MFX_STATE_POINTER                       OP_MFX(2, 0, 0, 6)  /* ALL */
#घोषणा OP_MFX_QM_STATE                            OP_MFX(2, 0, 0, 7)  /* IVB+ */
#घोषणा OP_MFX_FQM_STATE                           OP_MFX(2, 0, 0, 8)  /* IVB+ */
#घोषणा OP_MFX_PAK_INSERT_OBJECT                   OP_MFX(2, 0, 2, 8)  /* IVB+ */
#घोषणा OP_MFX_STITCH_OBJECT                       OP_MFX(2, 0, 2, 0xA)  /* IVB+ */

#घोषणा OP_MFD_IT_OBJECT                           OP_MFX(2, 0, 1, 9) /* ALL */

#घोषणा OP_MFX_WAIT                                OP_MFX(1, 0, 0, 0) /* IVB+ */
#घोषणा OP_MFX_AVC_IMG_STATE                       OP_MFX(2, 1, 0, 0) /* ALL */
#घोषणा OP_MFX_AVC_QM_STATE                        OP_MFX(2, 1, 0, 1) /* ALL */
#घोषणा OP_MFX_AVC_सूचीECTMODE_STATE                OP_MFX(2, 1, 0, 2) /* ALL */
#घोषणा OP_MFX_AVC_SLICE_STATE                     OP_MFX(2, 1, 0, 3) /* ALL */
#घोषणा OP_MFX_AVC_REF_IDX_STATE                   OP_MFX(2, 1, 0, 4) /* ALL */
#घोषणा OP_MFX_AVC_WEIGHTOFFSET_STATE              OP_MFX(2, 1, 0, 5) /* ALL */
#घोषणा OP_MFD_AVC_PICID_STATE                     OP_MFX(2, 1, 1, 5) /* HSW+ */
#घोषणा OP_MFD_AVC_DPB_STATE			   OP_MFX(2, 1, 1, 6) /* IVB+ */
#घोषणा OP_MFD_AVC_SLICEADDR                       OP_MFX(2, 1, 1, 7) /* IVB+ */
#घोषणा OP_MFD_AVC_BSD_OBJECT                      OP_MFX(2, 1, 1, 8) /* ALL */
#घोषणा OP_MFC_AVC_PAK_OBJECT                      OP_MFX(2, 1, 2, 9) /* ALL */

#घोषणा OP_MFX_VC1_PRED_PIPE_STATE                 OP_MFX(2, 2, 0, 1) /* ALL */
#घोषणा OP_MFX_VC1_सूचीECTMODE_STATE                OP_MFX(2, 2, 0, 2) /* ALL */
#घोषणा OP_MFD_VC1_SHORT_PIC_STATE                 OP_MFX(2, 2, 1, 0) /* IVB+ */
#घोषणा OP_MFD_VC1_LONG_PIC_STATE                  OP_MFX(2, 2, 1, 1) /* IVB+ */
#घोषणा OP_MFD_VC1_BSD_OBJECT                      OP_MFX(2, 2, 1, 8) /* ALL */

#घोषणा OP_MFX_MPEG2_PIC_STATE                     OP_MFX(2, 3, 0, 0) /* ALL */
#घोषणा OP_MFX_MPEG2_QM_STATE                      OP_MFX(2, 3, 0, 1) /* ALL */
#घोषणा OP_MFD_MPEG2_BSD_OBJECT                    OP_MFX(2, 3, 1, 8) /* ALL */
#घोषणा OP_MFC_MPEG2_SLICEGROUP_STATE              OP_MFX(2, 3, 2, 3) /* ALL */
#घोषणा OP_MFC_MPEG2_PAK_OBJECT                    OP_MFX(2, 3, 2, 9) /* ALL */

#घोषणा OP_MFX_2_6_0_0                             OP_MFX(2, 6, 0, 0) /* IVB+ */
#घोषणा OP_MFX_2_6_0_8                             OP_MFX(2, 6, 0, 8) /* IVB+ */
#घोषणा OP_MFX_2_6_0_9                             OP_MFX(2, 6, 0, 9) /* IVB+ */

#घोषणा OP_MFX_JPEG_PIC_STATE                      OP_MFX(2, 7, 0, 0)
#घोषणा OP_MFX_JPEG_HUFF_TABLE_STATE               OP_MFX(2, 7, 0, 2)
#घोषणा OP_MFD_JPEG_BSD_OBJECT                     OP_MFX(2, 7, 1, 8)

#घोषणा OP_VEB(pipeline, op, sub_opa, sub_opb) \
	(3 << 13 | \
	 (pipeline) << 11 | \
	 (op) << 8 | \
	 (sub_opa) << 5 | \
	 (sub_opb))

#घोषणा OP_VEB_SURFACE_STATE                       OP_VEB(2, 4, 0, 0)
#घोषणा OP_VEB_STATE                               OP_VEB(2, 4, 0, 2)
#घोषणा OP_VEB_DNDI_IECP_STATE                     OP_VEB(2, 4, 0, 3)

काष्ठा parser_exec_state;

प्रकार पूर्णांक (*parser_cmd_handler)(काष्ठा parser_exec_state *s);

#घोषणा GVT_CMD_HASH_BITS   7

/* which DWords need address fix */
#घोषणा ADDR_FIX_1(x1)			(1 << (x1))
#घोषणा ADDR_FIX_2(x1, x2)		(ADDR_FIX_1(x1) | ADDR_FIX_1(x2))
#घोषणा ADDR_FIX_3(x1, x2, x3)		(ADDR_FIX_1(x1) | ADDR_FIX_2(x2, x3))
#घोषणा ADDR_FIX_4(x1, x2, x3, x4)	(ADDR_FIX_1(x1) | ADDR_FIX_3(x2, x3, x4))
#घोषणा ADDR_FIX_5(x1, x2, x3, x4, x5)  (ADDR_FIX_1(x1) | ADDR_FIX_4(x2, x3, x4, x5))

#घोषणा DWORD_FIELD(dword, end, start) \
	FIELD_GET(GENMASK(end, start), cmd_val(s, dword))

#घोषणा OP_LENGTH_BIAS 2
#घोषणा CMD_LEN(value)  (value + OP_LENGTH_BIAS)

अटल पूर्णांक gvt_check_valid_cmd_length(पूर्णांक len, पूर्णांक valid_len)
अणु
	अगर (valid_len != len) अणु
		gvt_err("len is not valid:  len=%u  valid_len=%u\n",
			len, valid_len);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा cmd_info अणु
	स्थिर अक्षर *name;
	u32 opcode;

#घोषणा F_LEN_MASK	3U
#घोषणा F_LEN_CONST  1U
#घोषणा F_LEN_VAR    0U
/* value is स्थिर although LEN maybe variable */
#घोषणा F_LEN_VAR_FIXED    (1<<1)

/*
 * command has its own ip advance logic
 * e.g. MI_BATCH_START, MI_BATCH_END
 */
#घोषणा F_IP_ADVANCE_CUSTOM (1<<2)
	u32 flag;

#घोषणा R_RCS	BIT(RCS0)
#घोषणा R_VCS1  BIT(VCS0)
#घोषणा R_VCS2  BIT(VCS1)
#घोषणा R_VCS	(R_VCS1 | R_VCS2)
#घोषणा R_BCS	BIT(BCS0)
#घोषणा R_VECS	BIT(VECS0)
#घोषणा R_ALL (R_RCS | R_VCS | R_BCS | R_VECS)
	/* rings that support this cmd: BLT/RCS/VCS/VECS */
	u16 rings;

	/* devices that support this cmd: SNB/IVB/HSW/... */
	u16 devices;

	/* which DWords are address that need fix up.
	 * bit 0 means a 32-bit non address opeअक्रम in command
	 * bit 1 means address opeअक्रम, which could be 32-bit
	 * or 64-bit depending on dअगरferent architectures.(
	 * defined by "gmadr_bytes_in_cmd" in पूर्णांकel_gvt.
	 * No matter the address length, each address only takes
	 * one bit in the biपंचांगap.
	 */
	u16 addr_biपंचांगap;

	/* flag == F_LEN_CONST : command length
	 * flag == F_LEN_VAR : length bias bits
	 * Note: length is in DWord
	 */
	u32 len;

	parser_cmd_handler handler;

	/* valid length in DWord */
	u32 valid_len;
पूर्ण;

काष्ठा cmd_entry अणु
	काष्ठा hlist_node hlist;
	स्थिर काष्ठा cmd_info *info;
पूर्ण;

क्रमागत अणु
	RING_BUFFER_INSTRUCTION,
	BATCH_BUFFER_INSTRUCTION,
	BATCH_BUFFER_2ND_LEVEL,
	RING_BUFFER_CTX,
पूर्ण;

क्रमागत अणु
	GTT_BUFFER,
	PPGTT_BUFFER
पूर्ण;

काष्ठा parser_exec_state अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine;

	पूर्णांक buf_type;

	/* batch buffer address type */
	पूर्णांक buf_addr_type;

	/* graphics memory address of ring buffer start */
	अचिन्हित दीर्घ ring_start;
	अचिन्हित दीर्घ ring_size;
	अचिन्हित दीर्घ ring_head;
	अचिन्हित दीर्घ ring_tail;

	/* inकाष्ठाion graphics memory address */
	अचिन्हित दीर्घ ip_gma;

	/* mapped va of the instr_gma */
	व्योम *ip_va;
	व्योम *rb_va;

	व्योम *ret_bb_va;
	/* next inकाष्ठाion when वापस from  batch buffer to ring buffer */
	अचिन्हित दीर्घ ret_ip_gma_ring;

	/* next inकाष्ठाion when वापस from 2nd batch buffer to batch buffer */
	अचिन्हित दीर्घ ret_ip_gma_bb;

	/* batch buffer address type (GTT or PPGTT)
	 * used when ret from 2nd level batch buffer
	 */
	पूर्णांक saved_buf_addr_type;
	bool is_ctx_wa;
	bool is_init_ctx;

	स्थिर काष्ठा cmd_info *info;

	काष्ठा पूर्णांकel_vgpu_workload *workload;
पूर्ण;

#घोषणा gmadr_dw_number(s)	\
	(s->vgpu->gvt->device_info.gmadr_bytes_in_cmd >> 2)

अटल अचिन्हित दीर्घ bypass_scan_mask = 0;

/* ring ALL, type = 0 */
अटल स्थिर काष्ठा sub_op_bits sub_op_mi[] = अणु
	अणु31, 29पूर्ण,
	अणु28, 23पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा decode_info decode_info_mi = अणु
	"MI",
	OP_LEN_MI,
	ARRAY_SIZE(sub_op_mi),
	sub_op_mi,
पूर्ण;

/* ring RCS, command type 2 */
अटल स्थिर काष्ठा sub_op_bits sub_op_2d[] = अणु
	अणु31, 29पूर्ण,
	अणु28, 22पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा decode_info decode_info_2d = अणु
	"2D",
	OP_LEN_2D,
	ARRAY_SIZE(sub_op_2d),
	sub_op_2d,
पूर्ण;

/* ring RCS, command type 3 */
अटल स्थिर काष्ठा sub_op_bits sub_op_3d_media[] = अणु
	अणु31, 29पूर्ण,
	अणु28, 27पूर्ण,
	अणु26, 24पूर्ण,
	अणु23, 16पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा decode_info decode_info_3d_media = अणु
	"3D_Media",
	OP_LEN_3D_MEDIA,
	ARRAY_SIZE(sub_op_3d_media),
	sub_op_3d_media,
पूर्ण;

/* ring VCS, command type 3 */
अटल स्थिर काष्ठा sub_op_bits sub_op_mfx_vc[] = अणु
	अणु31, 29पूर्ण,
	अणु28, 27पूर्ण,
	अणु26, 24पूर्ण,
	अणु23, 21पूर्ण,
	अणु20, 16पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा decode_info decode_info_mfx_vc = अणु
	"MFX_VC",
	OP_LEN_MFX_VC,
	ARRAY_SIZE(sub_op_mfx_vc),
	sub_op_mfx_vc,
पूर्ण;

/* ring VECS, command type 3 */
अटल स्थिर काष्ठा sub_op_bits sub_op_vebox[] = अणु
	अणु31, 29पूर्ण,
	अणु28, 27पूर्ण,
	अणु26, 24पूर्ण,
	अणु23, 21पूर्ण,
	अणु20, 16पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा decode_info decode_info_vebox = अणु
	"VEBOX",
	OP_LEN_VEBOX,
	ARRAY_SIZE(sub_op_vebox),
	sub_op_vebox,
पूर्ण;

अटल स्थिर काष्ठा decode_info *ring_decode_info[I915_NUM_ENGINES][8] = अणु
	[RCS0] = अणु
		&decode_info_mi,
		शून्य,
		शून्य,
		&decode_info_3d_media,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
	पूर्ण,

	[VCS0] = अणु
		&decode_info_mi,
		शून्य,
		शून्य,
		&decode_info_mfx_vc,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
	पूर्ण,

	[BCS0] = अणु
		&decode_info_mi,
		शून्य,
		&decode_info_2d,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
	पूर्ण,

	[VECS0] = अणु
		&decode_info_mi,
		शून्य,
		शून्य,
		&decode_info_vebox,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
	पूर्ण,

	[VCS1] = अणु
		&decode_info_mi,
		शून्य,
		शून्य,
		&decode_info_mfx_vc,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
	पूर्ण,
पूर्ण;

अटल अंतरभूत u32 get_opcode(u32 cmd, स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर काष्ठा decode_info *d_info;

	d_info = ring_decode_info[engine->id][CMD_TYPE(cmd)];
	अगर (d_info == शून्य)
		वापस INVALID_OP;

	वापस cmd >> (32 - d_info->op_len);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cmd_info *
find_cmd_entry(काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक opcode,
	       स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा cmd_entry *e;

	hash_क्रम_each_possible(gvt->cmd_table, e, hlist, opcode) अणु
		अगर (opcode == e->info->opcode &&
		    e->info->rings & engine->mask)
			वापस e->info;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cmd_info *
get_cmd_info(काष्ठा पूर्णांकel_gvt *gvt, u32 cmd,
	     स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	u32 opcode;

	opcode = get_opcode(cmd, engine);
	अगर (opcode == INVALID_OP)
		वापस शून्य;

	वापस find_cmd_entry(gvt, opcode, engine);
पूर्ण

अटल अंतरभूत u32 sub_op_val(u32 cmd, u32 hi, u32 low)
अणु
	वापस (cmd >> low) & ((1U << (hi - low + 1)) - 1);
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_opcode(u32 cmd, स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर काष्ठा decode_info *d_info;
	पूर्णांक i;

	d_info = ring_decode_info[engine->id][CMD_TYPE(cmd)];
	अगर (d_info == शून्य)
		वापस;

	gvt_dbg_cmd("opcode=0x%x %s sub_ops:",
			cmd >> (32 - d_info->op_len), d_info->name);

	क्रम (i = 0; i < d_info->nr_sub_op; i++)
		pr_err("0x%x ", sub_op_val(cmd, d_info->sub_op[i].hi,
					d_info->sub_op[i].low));

	pr_err("\n");
पूर्ण

अटल अंतरभूत u32 *cmd_ptr(काष्ठा parser_exec_state *s, पूर्णांक index)
अणु
	वापस s->ip_va + (index << 2);
पूर्ण

अटल अंतरभूत u32 cmd_val(काष्ठा parser_exec_state *s, पूर्णांक index)
अणु
	वापस *cmd_ptr(s, index);
पूर्ण

अटल अंतरभूत bool is_init_ctx(काष्ठा parser_exec_state *s)
अणु
	वापस (s->buf_type == RING_BUFFER_CTX && s->is_init_ctx);
पूर्ण

अटल व्योम parser_exec_state_dump(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक cnt = 0;
	पूर्णांक i;

	gvt_dbg_cmd("  vgpu%d RING%s: ring_start(%08lx) ring_end(%08lx)"
		    " ring_head(%08lx) ring_tail(%08lx)\n",
		    s->vgpu->id, s->engine->name,
		    s->ring_start, s->ring_start + s->ring_size,
		    s->ring_head, s->ring_tail);

	gvt_dbg_cmd("  %s %s ip_gma(%08lx) ",
			s->buf_type == RING_BUFFER_INSTRUCTION ?
			"RING_BUFFER" : ((s->buf_type == RING_BUFFER_CTX) ?
				"CTX_BUFFER" : "BATCH_BUFFER"),
			s->buf_addr_type == GTT_BUFFER ?
			"GTT" : "PPGTT", s->ip_gma);

	अगर (s->ip_va == शून्य) अणु
		gvt_dbg_cmd(" ip_va(NULL)");
		वापस;
	पूर्ण

	gvt_dbg_cmd("  ip_va=%p: %08x %08x %08x %08x\n",
			s->ip_va, cmd_val(s, 0), cmd_val(s, 1),
			cmd_val(s, 2), cmd_val(s, 3));

	prपूर्णांक_opcode(cmd_val(s, 0), s->engine);

	s->ip_va = (u32 *)((((u64)s->ip_va) >> 12) << 12);

	जबतक (cnt < 1024) अणु
		gvt_dbg_cmd("ip_va=%p: ", s->ip_va);
		क्रम (i = 0; i < 8; i++)
			gvt_dbg_cmd("%08x ", cmd_val(s, i));
		gvt_dbg_cmd("\n");

		s->ip_va += 8 * माप(u32);
		cnt += 8;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_ip_va(काष्ठा parser_exec_state *s)
अणु
	अचिन्हित दीर्घ len = 0;

	अगर (WARN_ON(s->ring_head == s->ring_tail))
		वापस;

	अगर (s->buf_type == RING_BUFFER_INSTRUCTION ||
			s->buf_type == RING_BUFFER_CTX) अणु
		अचिन्हित दीर्घ ring_top = s->ring_start + s->ring_size;

		अगर (s->ring_head > s->ring_tail) अणु
			अगर (s->ip_gma >= s->ring_head && s->ip_gma < ring_top)
				len = (s->ip_gma - s->ring_head);
			अन्यथा अगर (s->ip_gma >= s->ring_start &&
					s->ip_gma <= s->ring_tail)
				len = (ring_top - s->ring_head) +
					(s->ip_gma - s->ring_start);
		पूर्ण अन्यथा
			len = (s->ip_gma - s->ring_head);

		s->ip_va = s->rb_va + len;
	पूर्ण अन्यथा अणु/* shaकरोw batch buffer */
		s->ip_va = s->ret_bb_va;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ip_gma_set(काष्ठा parser_exec_state *s,
		अचिन्हित दीर्घ ip_gma)
अणु
	WARN_ON(!IS_ALIGNED(ip_gma, 4));

	s->ip_gma = ip_gma;
	update_ip_va(s);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ip_gma_advance(काष्ठा parser_exec_state *s,
		अचिन्हित पूर्णांक dw_len)
अणु
	s->ip_gma += (dw_len << 2);

	अगर (s->buf_type == RING_BUFFER_INSTRUCTION) अणु
		अगर (s->ip_gma >= s->ring_start + s->ring_size)
			s->ip_gma -= s->ring_size;
		update_ip_va(s);
	पूर्ण अन्यथा अणु
		s->ip_va += (dw_len << 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_cmd_length(स्थिर काष्ठा cmd_info *info, u32 cmd)
अणु
	अगर ((info->flag & F_LEN_MASK) == F_LEN_CONST)
		वापस info->len;
	अन्यथा
		वापस (cmd & ((1U << info->len) - 1)) + 2;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cmd_length(काष्ठा parser_exec_state *s)
अणु
	वापस get_cmd_length(s->info, cmd_val(s, 0));
पूर्ण

/* करो not हटाओ this, some platक्रमm may need clflush here */
#घोषणा patch_value(s, addr, val) करो अणु \
	*addr = val; \
पूर्ण जबतक (0)

अटल अंतरभूत bool is_mocs_mmio(अचिन्हित पूर्णांक offset)
अणु
	वापस ((offset >= 0xc800) && (offset <= 0xcff8)) ||
		((offset >= 0xb020) && (offset <= 0xb0a0));
पूर्ण

अटल पूर्णांक is_cmd_update_pdps(अचिन्हित पूर्णांक offset,
			      काष्ठा parser_exec_state *s)
अणु
	u32 base = s->workload->engine->mmio_base;
	वापस i915_mmio_reg_equal(_MMIO(offset), GEN8_RING_PDP_UDW(base, 0));
पूर्ण

अटल पूर्णांक cmd_pdp_mmio_update_handler(काष्ठा parser_exec_state *s,
				       अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक index)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	काष्ठा पूर्णांकel_vgpu_mm *shaकरोw_mm = s->workload->shaकरोw_mm;
	काष्ठा पूर्णांकel_vgpu_mm *mm;
	u64 pdps[GEN8_3LVL_PDPES];

	अगर (shaकरोw_mm->ppgtt_mm.root_entry_type ==
	    GTT_TYPE_PPGTT_ROOT_L4_ENTRY) अणु
		pdps[0] = (u64)cmd_val(s, 2) << 32;
		pdps[0] |= cmd_val(s, 4);

		mm = पूर्णांकel_vgpu_find_ppgtt_mm(vgpu, pdps);
		अगर (!mm) अणु
			gvt_vgpu_err("failed to get the 4-level shadow vm\n");
			वापस -EINVAL;
		पूर्ण
		पूर्णांकel_vgpu_mm_get(mm);
		list_add_tail(&mm->ppgtt_mm.link,
			      &s->workload->lri_shaकरोw_mm);
		*cmd_ptr(s, 2) = upper_32_bits(mm->ppgtt_mm.shaकरोw_pdps[0]);
		*cmd_ptr(s, 4) = lower_32_bits(mm->ppgtt_mm.shaकरोw_pdps[0]);
	पूर्ण अन्यथा अणु
		/* Currently all guests use PML4 table and now can't
		 * have a guest with 3-level table but uses LRI क्रम
		 * PPGTT update. So this is simply un-testable. */
		GEM_BUG_ON(1);
		gvt_vgpu_err("invalid shared shadow vm type\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cmd_reg_handler(काष्ठा parser_exec_state *s,
	अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक index, अक्षर *cmd)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	u32 ctx_sr_ctl;
	u32 *vreg, vreg_old;

	अगर (offset + 4 > gvt->device_info.mmio_size) अणु
		gvt_vgpu_err("%s access to (%x) outside of MMIO range\n",
				cmd, offset);
		वापस -EFAULT;
	पूर्ण

	अगर (is_init_ctx(s)) अणु
		काष्ठा पूर्णांकel_gvt_mmio_info *mmio_info;

		पूर्णांकel_gvt_mmio_set_cmd_accessible(gvt, offset);
		mmio_info = पूर्णांकel_gvt_find_mmio_info(gvt, offset);
		अगर (mmio_info && mmio_info->ग_लिखो)
			पूर्णांकel_gvt_mmio_set_cmd_ग_लिखो_patch(gvt, offset);
		वापस 0;
	पूर्ण

	अगर (!पूर्णांकel_gvt_mmio_is_cmd_accessible(gvt, offset)) अणु
		gvt_vgpu_err("%s access to non-render register (%x)\n",
				cmd, offset);
		वापस -EBADRQC;
	पूर्ण

	अगर (!म_भेदन(cmd, "srm", 3) ||
			!म_भेदन(cmd, "lrm", 3)) अणु
		अगर (offset == i915_mmio_reg_offset(GEN8_L3SQCREG4) ||
		    offset == 0x21f0 ||
		    (IS_BROADWELL(gvt->gt->i915) &&
		     offset == i915_mmio_reg_offset(INSTPM)))
			वापस 0;
		अन्यथा अणु
			gvt_vgpu_err("%s access to register (%x)\n",
					cmd, offset);
			वापस -EPERM;
		पूर्ण
	पूर्ण

	अगर (!म_भेदन(cmd, "lrr-src", 7) ||
			!म_भेदन(cmd, "lrr-dst", 7)) अणु
		अगर (IS_BROADWELL(gvt->gt->i915) && offset == 0x215c)
			वापस 0;
		अन्यथा अणु
			gvt_vgpu_err("not allowed cmd %s reg (%x)\n", cmd, offset);
			वापस -EPERM;
		पूर्ण
	पूर्ण

	अगर (!म_भेदन(cmd, "pipe_ctrl", 9)) अणु
		/* TODO: add LRI POST logic here */
		वापस 0;
	पूर्ण

	अगर (म_भेदन(cmd, "lri", 3))
		वापस -EPERM;

	/* below are all lri handlers */
	vreg = &vgpu_vreg(s->vgpu, offset);

	अगर (is_cmd_update_pdps(offset, s) &&
	    cmd_pdp_mmio_update_handler(s, offset, index))
		वापस -EINVAL;

	अगर (offset == i915_mmio_reg_offset(DERRMR) ||
		offset == i915_mmio_reg_offset(FORCEWAKE_MT)) अणु
		/* Writing to HW VGT_PVINFO_PAGE offset will be discarded */
		patch_value(s, cmd_ptr(s, index), VGT_PVINFO_PAGE);
	पूर्ण

	अगर (is_mocs_mmio(offset))
		*vreg = cmd_val(s, index + 1);

	vreg_old = *vreg;

	अगर (पूर्णांकel_gvt_mmio_is_cmd_ग_लिखो_patch(gvt, offset)) अणु
		u32 cmdval_new, cmdval;
		काष्ठा पूर्णांकel_gvt_mmio_info *mmio_info;

		cmdval = cmd_val(s, index + 1);

		mmio_info = पूर्णांकel_gvt_find_mmio_info(gvt, offset);
		अगर (!mmio_info) अणु
			cmdval_new = cmdval;
		पूर्ण अन्यथा अणु
			u64 ro_mask = mmio_info->ro_mask;
			पूर्णांक ret;

			अगर (likely(!ro_mask))
				ret = mmio_info->ग_लिखो(s->vgpu, offset,
						&cmdval, 4);
			अन्यथा अणु
				gvt_vgpu_err("try to write RO reg %x\n",
						offset);
				ret = -EBADRQC;
			पूर्ण
			अगर (ret)
				वापस ret;
			cmdval_new = *vreg;
		पूर्ण
		अगर (cmdval_new != cmdval)
			patch_value(s, cmd_ptr(s, index+1), cmdval_new);
	पूर्ण

	/* only patch cmd. restore vreg value अगर changed in mmio ग_लिखो handler*/
	*vreg = vreg_old;

	/* TODO
	 * In order to let workload with inhibit context to generate
	 * correct image data पूर्णांकo memory, vregs values will be loaded to
	 * hw via LRIs in the workload with inhibit context. But as
	 * indirect context is loaded prior to LRIs in workload, we करोn't
	 * want reg values specअगरied in indirect context overwritten by
	 * LRIs in workloads. So, when scanning an indirect context, we
	 * update reg values in it पूर्णांकo vregs, so LRIs in workload with
	 * inhibit context will restore with correct values
	 */
	अगर (IS_GEN(s->engine->i915, 9) &&
	    पूर्णांकel_gvt_mmio_is_sr_in_ctx(gvt, offset) &&
	    !म_भेदन(cmd, "lri", 3)) अणु
		पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(s->vgpu,
			s->workload->ring_context_gpa + 12, &ctx_sr_ctl, 4);
		/* check inhibit context */
		अगर (ctx_sr_ctl & 1) अणु
			u32 data = cmd_val(s, index + 1);

			अगर (पूर्णांकel_gvt_mmio_has_mode_mask(s->vgpu->gvt, offset))
				पूर्णांकel_vgpu_mask_mmio_ग_लिखो(vgpu,
							offset, &data, 4);
			अन्यथा
				vgpu_vreg(vgpu, offset) = data;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा cmd_reg(s, i) \
	(cmd_val(s, i) & GENMASK(22, 2))

#घोषणा cmd_reg_inhibit(s, i) \
	(cmd_val(s, i) & GENMASK(22, 18))

#घोषणा cmd_gma(s, i) \
	(cmd_val(s, i) & GENMASK(31, 2))

#घोषणा cmd_gma_hi(s, i) \
	(cmd_val(s, i) & GENMASK(15, 0))

अटल पूर्णांक cmd_handler_lri(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक i, ret = 0;
	पूर्णांक cmd_len = cmd_length(s);

	क्रम (i = 1; i < cmd_len; i += 2) अणु
		अगर (IS_BROADWELL(s->engine->i915) && s->engine->id != RCS0) अणु
			अगर (s->engine->id == BCS0 &&
			    cmd_reg(s, i) == i915_mmio_reg_offset(DERRMR))
				ret |= 0;
			अन्यथा
				ret |= cmd_reg_inhibit(s, i) ? -EBADRQC : 0;
		पूर्ण
		अगर (ret)
			अवरोध;
		ret |= cmd_reg_handler(s, cmd_reg(s, i), i, "lri");
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cmd_handler_lrr(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक i, ret = 0;
	पूर्णांक cmd_len = cmd_length(s);

	क्रम (i = 1; i < cmd_len; i += 2) अणु
		अगर (IS_BROADWELL(s->engine->i915))
			ret |= ((cmd_reg_inhibit(s, i) ||
				 (cmd_reg_inhibit(s, i + 1)))) ?
				-EBADRQC : 0;
		अगर (ret)
			अवरोध;
		ret |= cmd_reg_handler(s, cmd_reg(s, i), i, "lrr-src");
		अगर (ret)
			अवरोध;
		ret |= cmd_reg_handler(s, cmd_reg(s, i + 1), i, "lrr-dst");
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक cmd_address_audit(काष्ठा parser_exec_state *s,
		अचिन्हित दीर्घ guest_gma, पूर्णांक op_size, bool index_mode);

अटल पूर्णांक cmd_handler_lrm(काष्ठा parser_exec_state *s)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = s->vgpu->gvt;
	पूर्णांक gmadr_bytes = gvt->device_info.gmadr_bytes_in_cmd;
	अचिन्हित दीर्घ gma;
	पूर्णांक i, ret = 0;
	पूर्णांक cmd_len = cmd_length(s);

	क्रम (i = 1; i < cmd_len;) अणु
		अगर (IS_BROADWELL(s->engine->i915))
			ret |= (cmd_reg_inhibit(s, i)) ? -EBADRQC : 0;
		अगर (ret)
			अवरोध;
		ret |= cmd_reg_handler(s, cmd_reg(s, i), i, "lrm");
		अगर (ret)
			अवरोध;
		अगर (cmd_val(s, 0) & (1 << 22)) अणु
			gma = cmd_gma(s, i + 1);
			अगर (gmadr_bytes == 8)
				gma |= (cmd_gma_hi(s, i + 2)) << 32;
			ret |= cmd_address_audit(s, gma, माप(u32), false);
			अगर (ret)
				अवरोध;
		पूर्ण
		i += gmadr_dw_number(s) + 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cmd_handler_srm(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक gmadr_bytes = s->vgpu->gvt->device_info.gmadr_bytes_in_cmd;
	अचिन्हित दीर्घ gma;
	पूर्णांक i, ret = 0;
	पूर्णांक cmd_len = cmd_length(s);

	क्रम (i = 1; i < cmd_len;) अणु
		ret |= cmd_reg_handler(s, cmd_reg(s, i), i, "srm");
		अगर (ret)
			अवरोध;
		अगर (cmd_val(s, 0) & (1 << 22)) अणु
			gma = cmd_gma(s, i + 1);
			अगर (gmadr_bytes == 8)
				gma |= (cmd_gma_hi(s, i + 2)) << 32;
			ret |= cmd_address_audit(s, gma, माप(u32), false);
			अगर (ret)
				अवरोध;
		पूर्ण
		i += gmadr_dw_number(s) + 1;
	पूर्ण
	वापस ret;
पूर्ण

काष्ठा cmd_पूर्णांकerrupt_event अणु
	पूर्णांक pipe_control_notअगरy;
	पूर्णांक mi_flush_dw;
	पूर्णांक mi_user_पूर्णांकerrupt;
पूर्ण;

अटल काष्ठा cmd_पूर्णांकerrupt_event cmd_पूर्णांकerrupt_events[] = अणु
	[RCS0] = अणु
		.pipe_control_notअगरy = RCS_PIPE_CONTROL,
		.mi_flush_dw = INTEL_GVT_EVENT_RESERVED,
		.mi_user_पूर्णांकerrupt = RCS_MI_USER_INTERRUPT,
	पूर्ण,
	[BCS0] = अणु
		.pipe_control_notअगरy = INTEL_GVT_EVENT_RESERVED,
		.mi_flush_dw = BCS_MI_FLUSH_DW,
		.mi_user_पूर्णांकerrupt = BCS_MI_USER_INTERRUPT,
	पूर्ण,
	[VCS0] = अणु
		.pipe_control_notअगरy = INTEL_GVT_EVENT_RESERVED,
		.mi_flush_dw = VCS_MI_FLUSH_DW,
		.mi_user_पूर्णांकerrupt = VCS_MI_USER_INTERRUPT,
	पूर्ण,
	[VCS1] = अणु
		.pipe_control_notअगरy = INTEL_GVT_EVENT_RESERVED,
		.mi_flush_dw = VCS2_MI_FLUSH_DW,
		.mi_user_पूर्णांकerrupt = VCS2_MI_USER_INTERRUPT,
	पूर्ण,
	[VECS0] = अणु
		.pipe_control_notअगरy = INTEL_GVT_EVENT_RESERVED,
		.mi_flush_dw = VECS_MI_FLUSH_DW,
		.mi_user_पूर्णांकerrupt = VECS_MI_USER_INTERRUPT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cmd_handler_pipe_control(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक gmadr_bytes = s->vgpu->gvt->device_info.gmadr_bytes_in_cmd;
	अचिन्हित दीर्घ gma;
	bool index_mode = false;
	अचिन्हित पूर्णांक post_sync;
	पूर्णांक ret = 0;
	u32 hws_pga, val;

	post_sync = (cmd_val(s, 1) & PIPE_CONTROL_POST_SYNC_OP_MASK) >> 14;

	/* LRI post sync */
	अगर (cmd_val(s, 1) & PIPE_CONTROL_MMIO_WRITE)
		ret = cmd_reg_handler(s, cmd_reg(s, 2), 1, "pipe_ctrl");
	/* post sync */
	अन्यथा अगर (post_sync) अणु
		अगर (post_sync == 2)
			ret = cmd_reg_handler(s, 0x2350, 1, "pipe_ctrl");
		अन्यथा अगर (post_sync == 3)
			ret = cmd_reg_handler(s, 0x2358, 1, "pipe_ctrl");
		अन्यथा अगर (post_sync == 1) अणु
			/* check ggtt*/
			अगर ((cmd_val(s, 1) & PIPE_CONTROL_GLOBAL_GTT_IVB)) अणु
				gma = cmd_val(s, 2) & GENMASK(31, 3);
				अगर (gmadr_bytes == 8)
					gma |= (cmd_gma_hi(s, 3)) << 32;
				/* Store Data Index */
				अगर (cmd_val(s, 1) & (1 << 21))
					index_mode = true;
				ret |= cmd_address_audit(s, gma, माप(u64),
						index_mode);
				अगर (ret)
					वापस ret;
				अगर (index_mode) अणु
					hws_pga = s->vgpu->hws_pga[s->engine->id];
					gma = hws_pga + gma;
					patch_value(s, cmd_ptr(s, 2), gma);
					val = cmd_val(s, 1) & (~(1 << 21));
					patch_value(s, cmd_ptr(s, 1), val);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;

	अगर (cmd_val(s, 1) & PIPE_CONTROL_NOTIFY)
		set_bit(cmd_पूर्णांकerrupt_events[s->engine->id].pipe_control_notअगरy,
			s->workload->pending_events);
	वापस 0;
पूर्ण

अटल पूर्णांक cmd_handler_mi_user_पूर्णांकerrupt(काष्ठा parser_exec_state *s)
अणु
	set_bit(cmd_पूर्णांकerrupt_events[s->engine->id].mi_user_पूर्णांकerrupt,
		s->workload->pending_events);
	patch_value(s, cmd_ptr(s, 0), MI_NOOP);
	वापस 0;
पूर्ण

अटल पूर्णांक cmd_advance_शेष(काष्ठा parser_exec_state *s)
अणु
	वापस ip_gma_advance(s, cmd_length(s));
पूर्ण

अटल पूर्णांक cmd_handler_mi_batch_buffer_end(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक ret;

	अगर (s->buf_type == BATCH_BUFFER_2ND_LEVEL) अणु
		s->buf_type = BATCH_BUFFER_INSTRUCTION;
		ret = ip_gma_set(s, s->ret_ip_gma_bb);
		s->buf_addr_type = s->saved_buf_addr_type;
	पूर्ण अन्यथा अगर (s->buf_type == RING_BUFFER_CTX) अणु
		ret = ip_gma_set(s, s->ring_tail);
	पूर्ण अन्यथा अणु
		s->buf_type = RING_BUFFER_INSTRUCTION;
		s->buf_addr_type = GTT_BUFFER;
		अगर (s->ret_ip_gma_ring >= s->ring_start + s->ring_size)
			s->ret_ip_gma_ring -= s->ring_size;
		ret = ip_gma_set(s, s->ret_ip_gma_ring);
	पूर्ण
	वापस ret;
पूर्ण

काष्ठा mi_display_flip_command_info अणु
	पूर्णांक pipe;
	पूर्णांक plane;
	पूर्णांक event;
	i915_reg_t stride_reg;
	i915_reg_t ctrl_reg;
	i915_reg_t surf_reg;
	u64 stride_val;
	u64 tile_val;
	u64 surf_val;
	bool async_flip;
पूर्ण;

काष्ठा plane_code_mapping अणु
	पूर्णांक pipe;
	पूर्णांक plane;
	पूर्णांक event;
पूर्ण;

अटल पूर्णांक gen8_decode_mi_display_flip(काष्ठा parser_exec_state *s,
		काष्ठा mi_display_flip_command_info *info)
अणु
	काष्ठा drm_i915_निजी *dev_priv = s->engine->i915;
	काष्ठा plane_code_mapping gen8_plane_code[] = अणु
		[0] = अणुPIPE_A, PLANE_A, PRIMARY_A_FLIP_DONEपूर्ण,
		[1] = अणुPIPE_B, PLANE_A, PRIMARY_B_FLIP_DONEपूर्ण,
		[2] = अणुPIPE_A, PLANE_B, SPRITE_A_FLIP_DONEपूर्ण,
		[3] = अणुPIPE_B, PLANE_B, SPRITE_B_FLIP_DONEपूर्ण,
		[4] = अणुPIPE_C, PLANE_A, PRIMARY_C_FLIP_DONEपूर्ण,
		[5] = अणुPIPE_C, PLANE_B, SPRITE_C_FLIP_DONEपूर्ण,
	पूर्ण;
	u32 dword0, dword1, dword2;
	u32 v;

	dword0 = cmd_val(s, 0);
	dword1 = cmd_val(s, 1);
	dword2 = cmd_val(s, 2);

	v = (dword0 & GENMASK(21, 19)) >> 19;
	अगर (drm_WARN_ON(&dev_priv->drm, v >= ARRAY_SIZE(gen8_plane_code)))
		वापस -EBADRQC;

	info->pipe = gen8_plane_code[v].pipe;
	info->plane = gen8_plane_code[v].plane;
	info->event = gen8_plane_code[v].event;
	info->stride_val = (dword1 & GENMASK(15, 6)) >> 6;
	info->tile_val = (dword1 & 0x1);
	info->surf_val = (dword2 & GENMASK(31, 12)) >> 12;
	info->async_flip = ((dword2 & GENMASK(1, 0)) == 0x1);

	अगर (info->plane == PLANE_A) अणु
		info->ctrl_reg = DSPCNTR(info->pipe);
		info->stride_reg = DSPSTRIDE(info->pipe);
		info->surf_reg = DSPSURF(info->pipe);
	पूर्ण अन्यथा अगर (info->plane == PLANE_B) अणु
		info->ctrl_reg = SPRCTL(info->pipe);
		info->stride_reg = SPRSTRIDE(info->pipe);
		info->surf_reg = SPRSURF(info->pipe);
	पूर्ण अन्यथा अणु
		drm_WARN_ON(&dev_priv->drm, 1);
		वापस -EBADRQC;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक skl_decode_mi_display_flip(काष्ठा parser_exec_state *s,
		काष्ठा mi_display_flip_command_info *info)
अणु
	काष्ठा drm_i915_निजी *dev_priv = s->engine->i915;
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	u32 dword0 = cmd_val(s, 0);
	u32 dword1 = cmd_val(s, 1);
	u32 dword2 = cmd_val(s, 2);
	u32 plane = (dword0 & GENMASK(12, 8)) >> 8;

	info->plane = PRIMARY_PLANE;

	चयन (plane) अणु
	हाल MI_DISPLAY_FLIP_SKL_PLANE_1_A:
		info->pipe = PIPE_A;
		info->event = PRIMARY_A_FLIP_DONE;
		अवरोध;
	हाल MI_DISPLAY_FLIP_SKL_PLANE_1_B:
		info->pipe = PIPE_B;
		info->event = PRIMARY_B_FLIP_DONE;
		अवरोध;
	हाल MI_DISPLAY_FLIP_SKL_PLANE_1_C:
		info->pipe = PIPE_C;
		info->event = PRIMARY_C_FLIP_DONE;
		अवरोध;

	हाल MI_DISPLAY_FLIP_SKL_PLANE_2_A:
		info->pipe = PIPE_A;
		info->event = SPRITE_A_FLIP_DONE;
		info->plane = SPRITE_PLANE;
		अवरोध;
	हाल MI_DISPLAY_FLIP_SKL_PLANE_2_B:
		info->pipe = PIPE_B;
		info->event = SPRITE_B_FLIP_DONE;
		info->plane = SPRITE_PLANE;
		अवरोध;
	हाल MI_DISPLAY_FLIP_SKL_PLANE_2_C:
		info->pipe = PIPE_C;
		info->event = SPRITE_C_FLIP_DONE;
		info->plane = SPRITE_PLANE;
		अवरोध;

	शेष:
		gvt_vgpu_err("unknown plane code %d\n", plane);
		वापस -EBADRQC;
	पूर्ण

	info->stride_val = (dword1 & GENMASK(15, 6)) >> 6;
	info->tile_val = (dword1 & GENMASK(2, 0));
	info->surf_val = (dword2 & GENMASK(31, 12)) >> 12;
	info->async_flip = ((dword2 & GENMASK(1, 0)) == 0x1);

	info->ctrl_reg = DSPCNTR(info->pipe);
	info->stride_reg = DSPSTRIDE(info->pipe);
	info->surf_reg = DSPSURF(info->pipe);

	वापस 0;
पूर्ण

अटल पूर्णांक gen8_check_mi_display_flip(काष्ठा parser_exec_state *s,
		काष्ठा mi_display_flip_command_info *info)
अणु
	u32 stride, tile;

	अगर (!info->async_flip)
		वापस 0;

	अगर (INTEL_GEN(s->engine->i915) >= 9) अणु
		stride = vgpu_vreg_t(s->vgpu, info->stride_reg) & GENMASK(9, 0);
		tile = (vgpu_vreg_t(s->vgpu, info->ctrl_reg) &
				GENMASK(12, 10)) >> 10;
	पूर्ण अन्यथा अणु
		stride = (vgpu_vreg_t(s->vgpu, info->stride_reg) &
				GENMASK(15, 6)) >> 6;
		tile = (vgpu_vreg_t(s->vgpu, info->ctrl_reg) & (1 << 10)) >> 10;
	पूर्ण

	अगर (stride != info->stride_val)
		gvt_dbg_cmd("cannot change stride during async flip\n");

	अगर (tile != info->tile_val)
		gvt_dbg_cmd("cannot change tile during async flip\n");

	वापस 0;
पूर्ण

अटल पूर्णांक gen8_update_plane_mmio_from_mi_display_flip(
		काष्ठा parser_exec_state *s,
		काष्ठा mi_display_flip_command_info *info)
अणु
	काष्ठा drm_i915_निजी *dev_priv = s->engine->i915;
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;

	set_mask_bits(&vgpu_vreg_t(vgpu, info->surf_reg), GENMASK(31, 12),
		      info->surf_val << 12);
	अगर (INTEL_GEN(dev_priv) >= 9) अणु
		set_mask_bits(&vgpu_vreg_t(vgpu, info->stride_reg), GENMASK(9, 0),
			      info->stride_val);
		set_mask_bits(&vgpu_vreg_t(vgpu, info->ctrl_reg), GENMASK(12, 10),
			      info->tile_val << 10);
	पूर्ण अन्यथा अणु
		set_mask_bits(&vgpu_vreg_t(vgpu, info->stride_reg), GENMASK(15, 6),
			      info->stride_val << 6);
		set_mask_bits(&vgpu_vreg_t(vgpu, info->ctrl_reg), GENMASK(10, 10),
			      info->tile_val << 10);
	पूर्ण

	अगर (info->plane == PLANE_PRIMARY)
		vgpu_vreg_t(vgpu, PIPE_FLIPCOUNT_G4X(info->pipe))++;

	अगर (info->async_flip)
		पूर्णांकel_vgpu_trigger_भव_event(vgpu, info->event);
	अन्यथा
		set_bit(info->event, vgpu->irq.flip_करोne_event[info->pipe]);

	वापस 0;
पूर्ण

अटल पूर्णांक decode_mi_display_flip(काष्ठा parser_exec_state *s,
		काष्ठा mi_display_flip_command_info *info)
अणु
	अगर (IS_BROADWELL(s->engine->i915))
		वापस gen8_decode_mi_display_flip(s, info);
	अगर (INTEL_GEN(s->engine->i915) >= 9)
		वापस skl_decode_mi_display_flip(s, info);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक check_mi_display_flip(काष्ठा parser_exec_state *s,
		काष्ठा mi_display_flip_command_info *info)
अणु
	वापस gen8_check_mi_display_flip(s, info);
पूर्ण

अटल पूर्णांक update_plane_mmio_from_mi_display_flip(
		काष्ठा parser_exec_state *s,
		काष्ठा mi_display_flip_command_info *info)
अणु
	वापस gen8_update_plane_mmio_from_mi_display_flip(s, info);
पूर्ण

अटल पूर्णांक cmd_handler_mi_display_flip(काष्ठा parser_exec_state *s)
अणु
	काष्ठा mi_display_flip_command_info info;
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक len = cmd_length(s);
	u32 valid_len = CMD_LEN(1);

	/* Flip Type == Stereo 3D Flip */
	अगर (DWORD_FIELD(2, 1, 0) == 2)
		valid_len++;
	ret = gvt_check_valid_cmd_length(cmd_length(s),
			valid_len);
	अगर (ret)
		वापस ret;

	ret = decode_mi_display_flip(s, &info);
	अगर (ret) अणु
		gvt_vgpu_err("fail to decode MI display flip command\n");
		वापस ret;
	पूर्ण

	ret = check_mi_display_flip(s, &info);
	अगर (ret) अणु
		gvt_vgpu_err("invalid MI display flip command\n");
		वापस ret;
	पूर्ण

	ret = update_plane_mmio_from_mi_display_flip(s, &info);
	अगर (ret) अणु
		gvt_vgpu_err("fail to update plane mmio\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < len; i++)
		patch_value(s, cmd_ptr(s, i), MI_NOOP);
	वापस 0;
पूर्ण

अटल bool is_रुको_क्रम_flip_pending(u32 cmd)
अणु
	वापस cmd & (MI_WAIT_FOR_PLANE_A_FLIP_PENDING |
			MI_WAIT_FOR_PLANE_B_FLIP_PENDING |
			MI_WAIT_FOR_PLANE_C_FLIP_PENDING |
			MI_WAIT_FOR_SPRITE_A_FLIP_PENDING |
			MI_WAIT_FOR_SPRITE_B_FLIP_PENDING |
			MI_WAIT_FOR_SPRITE_C_FLIP_PENDING);
पूर्ण

अटल पूर्णांक cmd_handler_mi_रुको_क्रम_event(काष्ठा parser_exec_state *s)
अणु
	u32 cmd = cmd_val(s, 0);

	अगर (!is_रुको_क्रम_flip_pending(cmd))
		वापस 0;

	patch_value(s, cmd_ptr(s, 0), MI_NOOP);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ get_gma_bb_from_cmd(काष्ठा parser_exec_state *s, पूर्णांक index)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ gma_high, gma_low;
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	पूर्णांक gmadr_bytes = vgpu->gvt->device_info.gmadr_bytes_in_cmd;

	अगर (WARN_ON(gmadr_bytes != 4 && gmadr_bytes != 8)) अणु
		gvt_vgpu_err("invalid gma bytes %d\n", gmadr_bytes);
		वापस INTEL_GVT_INVALID_ADDR;
	पूर्ण

	gma_low = cmd_val(s, index) & BATCH_BUFFER_ADDR_MASK;
	अगर (gmadr_bytes == 4) अणु
		addr = gma_low;
	पूर्ण अन्यथा अणु
		gma_high = cmd_val(s, index + 1) & BATCH_BUFFER_ADDR_HIGH_MASK;
		addr = (((अचिन्हित दीर्घ)gma_high) << 32) | gma_low;
	पूर्ण
	वापस addr;
पूर्ण

अटल अंतरभूत पूर्णांक cmd_address_audit(काष्ठा parser_exec_state *s,
		अचिन्हित दीर्घ guest_gma, पूर्णांक op_size, bool index_mode)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	u32 max_surface_size = vgpu->gvt->device_info.max_surface_size;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (op_size > max_surface_size) अणु
		gvt_vgpu_err("command address audit fail name %s\n",
			s->info->name);
		वापस -EFAULT;
	पूर्ण

	अगर (index_mode)	अणु
		अगर (guest_gma >= I915_GTT_PAGE_SIZE) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अगर (!पूर्णांकel_gvt_ggtt_validate_range(vgpu, guest_gma, op_size)) अणु
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	gvt_vgpu_err("cmd_parser: Malicious %s detected, addr=0x%lx, len=%d!\n",
			s->info->name, guest_gma, op_size);

	pr_err("cmd dump: ");
	क्रम (i = 0; i < cmd_length(s); i++) अणु
		अगर (!(i % 4))
			pr_err("\n%08x ", cmd_val(s, i));
		अन्यथा
			pr_err("%08x ", cmd_val(s, i));
	पूर्ण
	pr_err("\nvgpu%d: aperture 0x%llx - 0x%llx, hidden 0x%llx - 0x%llx\n",
			vgpu->id,
			vgpu_aperture_gmadr_base(vgpu),
			vgpu_aperture_gmadr_end(vgpu),
			vgpu_hidden_gmadr_base(vgpu),
			vgpu_hidden_gmadr_end(vgpu));
	वापस ret;
पूर्ण

अटल पूर्णांक cmd_handler_mi_store_data_imm(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक gmadr_bytes = s->vgpu->gvt->device_info.gmadr_bytes_in_cmd;
	पूर्णांक op_size = (cmd_length(s) - 3) * माप(u32);
	पूर्णांक core_id = (cmd_val(s, 2) & (1 << 0)) ? 1 : 0;
	अचिन्हित दीर्घ gma, gma_low, gma_high;
	u32 valid_len = CMD_LEN(2);
	पूर्णांक ret = 0;

	/* check ppggt */
	अगर (!(cmd_val(s, 0) & (1 << 22)))
		वापस 0;

	/* check अगर QWORD */
	अगर (DWORD_FIELD(0, 21, 21))
		valid_len++;
	ret = gvt_check_valid_cmd_length(cmd_length(s),
			valid_len);
	अगर (ret)
		वापस ret;

	gma = cmd_val(s, 2) & GENMASK(31, 2);

	अगर (gmadr_bytes == 8) अणु
		gma_low = cmd_val(s, 1) & GENMASK(31, 2);
		gma_high = cmd_val(s, 2) & GENMASK(15, 0);
		gma = (gma_high << 32) | gma_low;
		core_id = (cmd_val(s, 1) & (1 << 0)) ? 1 : 0;
	पूर्ण
	ret = cmd_address_audit(s, gma + op_size * core_id, op_size, false);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक unexpected_cmd(काष्ठा parser_exec_state *s)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;

	gvt_vgpu_err("Unexpected %s in command buffer!\n", s->info->name);

	वापस -EBADRQC;
पूर्ण

अटल पूर्णांक cmd_handler_mi_semaphore_रुको(काष्ठा parser_exec_state *s)
अणु
	वापस unexpected_cmd(s);
पूर्ण

अटल पूर्णांक cmd_handler_mi_report_perf_count(काष्ठा parser_exec_state *s)
अणु
	वापस unexpected_cmd(s);
पूर्ण

अटल पूर्णांक cmd_handler_mi_op_2e(काष्ठा parser_exec_state *s)
अणु
	वापस unexpected_cmd(s);
पूर्ण

अटल पूर्णांक cmd_handler_mi_op_2f(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक gmadr_bytes = s->vgpu->gvt->device_info.gmadr_bytes_in_cmd;
	पूर्णांक op_size = (1 << ((cmd_val(s, 0) & GENMASK(20, 19)) >> 19)) *
			माप(u32);
	अचिन्हित दीर्घ gma, gma_high;
	u32 valid_len = CMD_LEN(1);
	पूर्णांक ret = 0;

	अगर (!(cmd_val(s, 0) & (1 << 22)))
		वापस ret;

	/* check अंतरभूत data */
	अगर (cmd_val(s, 0) & BIT(18))
		valid_len = CMD_LEN(9);
	ret = gvt_check_valid_cmd_length(cmd_length(s),
			valid_len);
	अगर (ret)
		वापस ret;

	gma = cmd_val(s, 1) & GENMASK(31, 2);
	अगर (gmadr_bytes == 8) अणु
		gma_high = cmd_val(s, 2) & GENMASK(15, 0);
		gma = (gma_high << 32) | gma;
	पूर्ण
	ret = cmd_address_audit(s, gma, op_size, false);
	वापस ret;
पूर्ण

अटल पूर्णांक cmd_handler_mi_store_data_index(काष्ठा parser_exec_state *s)
अणु
	वापस unexpected_cmd(s);
पूर्ण

अटल पूर्णांक cmd_handler_mi_clflush(काष्ठा parser_exec_state *s)
अणु
	वापस unexpected_cmd(s);
पूर्ण

अटल पूर्णांक cmd_handler_mi_conditional_batch_buffer_end(
		काष्ठा parser_exec_state *s)
अणु
	वापस unexpected_cmd(s);
पूर्ण

अटल पूर्णांक cmd_handler_mi_update_gtt(काष्ठा parser_exec_state *s)
अणु
	वापस unexpected_cmd(s);
पूर्ण

अटल पूर्णांक cmd_handler_mi_flush_dw(काष्ठा parser_exec_state *s)
अणु
	पूर्णांक gmadr_bytes = s->vgpu->gvt->device_info.gmadr_bytes_in_cmd;
	अचिन्हित दीर्घ gma;
	bool index_mode = false;
	पूर्णांक ret = 0;
	u32 hws_pga, val;
	u32 valid_len = CMD_LEN(2);

	ret = gvt_check_valid_cmd_length(cmd_length(s),
			valid_len);
	अगर (ret) अणु
		/* Check again क्रम Qword */
		ret = gvt_check_valid_cmd_length(cmd_length(s),
			++valid_len);
		वापस ret;
	पूर्ण

	/* Check post-sync and ppgtt bit */
	अगर (((cmd_val(s, 0) >> 14) & 0x3) && (cmd_val(s, 1) & (1 << 2))) अणु
		gma = cmd_val(s, 1) & GENMASK(31, 3);
		अगर (gmadr_bytes == 8)
			gma |= (cmd_val(s, 2) & GENMASK(15, 0)) << 32;
		/* Store Data Index */
		अगर (cmd_val(s, 0) & (1 << 21))
			index_mode = true;
		ret = cmd_address_audit(s, gma, माप(u64), index_mode);
		अगर (ret)
			वापस ret;
		अगर (index_mode) अणु
			hws_pga = s->vgpu->hws_pga[s->engine->id];
			gma = hws_pga + gma;
			patch_value(s, cmd_ptr(s, 1), gma);
			val = cmd_val(s, 0) & (~(1 << 21));
			patch_value(s, cmd_ptr(s, 0), val);
		पूर्ण
	पूर्ण
	/* Check notअगरy bit */
	अगर ((cmd_val(s, 0) & (1 << 8)))
		set_bit(cmd_पूर्णांकerrupt_events[s->engine->id].mi_flush_dw,
			s->workload->pending_events);
	वापस ret;
पूर्ण

अटल व्योम addr_type_update_snb(काष्ठा parser_exec_state *s)
अणु
	अगर ((s->buf_type == RING_BUFFER_INSTRUCTION) &&
			(BATCH_BUFFER_ADR_SPACE_BIT(cmd_val(s, 0)) == 1)) अणु
		s->buf_addr_type = PPGTT_BUFFER;
	पूर्ण
पूर्ण


अटल पूर्णांक copy_gma_to_hva(काष्ठा पूर्णांकel_vgpu *vgpu, काष्ठा पूर्णांकel_vgpu_mm *mm,
		अचिन्हित दीर्घ gma, अचिन्हित दीर्घ end_gma, व्योम *va)
अणु
	अचिन्हित दीर्घ copy_len, offset;
	अचिन्हित दीर्घ len = 0;
	अचिन्हित दीर्घ gpa;

	जबतक (gma != end_gma) अणु
		gpa = पूर्णांकel_vgpu_gma_to_gpa(mm, gma);
		अगर (gpa == INTEL_GVT_INVALID_ADDR) अणु
			gvt_vgpu_err("invalid gma address: %lx\n", gma);
			वापस -EFAULT;
		पूर्ण

		offset = gma & (I915_GTT_PAGE_SIZE - 1);

		copy_len = (end_gma - gma) >= (I915_GTT_PAGE_SIZE - offset) ?
			I915_GTT_PAGE_SIZE - offset : end_gma - gma;

		पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, gpa, va + len, copy_len);

		len += copy_len;
		gma += copy_len;
	पूर्ण
	वापस len;
पूर्ण


/*
 * Check whether a batch buffer needs to be scanned. Currently
 * the only criteria is based on privilege.
 */
अटल पूर्णांक batch_buffer_needs_scan(काष्ठा parser_exec_state *s)
अणु
	/* Decide privilege based on address space */
	अगर (cmd_val(s, 0) & BIT(8) &&
	    !(s->vgpu->scan_nonprivbb & s->engine->mask))
		वापस 0;

	वापस 1;
पूर्ण

अटल स्थिर अक्षर *repr_addr_type(अचिन्हित पूर्णांक type)
अणु
	वापस type == PPGTT_BUFFER ? "ppgtt" : "ggtt";
पूर्ण

अटल पूर्णांक find_bb_size(काष्ठा parser_exec_state *s,
			अचिन्हित दीर्घ *bb_size,
			अचिन्हित दीर्घ *bb_end_cmd_offset)
अणु
	अचिन्हित दीर्घ gma = 0;
	स्थिर काष्ठा cmd_info *info;
	u32 cmd_len = 0;
	bool bb_end = false;
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	u32 cmd;
	काष्ठा पूर्णांकel_vgpu_mm *mm = (s->buf_addr_type == GTT_BUFFER) ?
		s->vgpu->gtt.ggtt_mm : s->workload->shaकरोw_mm;

	*bb_size = 0;
	*bb_end_cmd_offset = 0;

	/* get the start gm address of the batch buffer */
	gma = get_gma_bb_from_cmd(s, 1);
	अगर (gma == INTEL_GVT_INVALID_ADDR)
		वापस -EFAULT;

	cmd = cmd_val(s, 0);
	info = get_cmd_info(s->vgpu->gvt, cmd, s->engine);
	अगर (info == शून्य) अणु
		gvt_vgpu_err("unknown cmd 0x%x, opcode=0x%x, addr_type=%s, ring %s, workload=%p\n",
			     cmd, get_opcode(cmd, s->engine),
			     repr_addr_type(s->buf_addr_type),
			     s->engine->name, s->workload);
		वापस -EBADRQC;
	पूर्ण
	करो अणु
		अगर (copy_gma_to_hva(s->vgpu, mm,
				    gma, gma + 4, &cmd) < 0)
			वापस -EFAULT;
		info = get_cmd_info(s->vgpu->gvt, cmd, s->engine);
		अगर (info == शून्य) अणु
			gvt_vgpu_err("unknown cmd 0x%x, opcode=0x%x, addr_type=%s, ring %s, workload=%p\n",
				     cmd, get_opcode(cmd, s->engine),
				     repr_addr_type(s->buf_addr_type),
				     s->engine->name, s->workload);
			वापस -EBADRQC;
		पूर्ण

		अगर (info->opcode == OP_MI_BATCH_BUFFER_END) अणु
			bb_end = true;
		पूर्ण अन्यथा अगर (info->opcode == OP_MI_BATCH_BUFFER_START) अणु
			अगर (BATCH_BUFFER_2ND_LEVEL_BIT(cmd) == 0)
				/* chained batch buffer */
				bb_end = true;
		पूर्ण

		अगर (bb_end)
			*bb_end_cmd_offset = *bb_size;

		cmd_len = get_cmd_length(info, cmd) << 2;
		*bb_size += cmd_len;
		gma += cmd_len;
	पूर्ण जबतक (!bb_end);

	वापस 0;
पूर्ण

अटल पूर्णांक audit_bb_end(काष्ठा parser_exec_state *s, व्योम *va)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	u32 cmd = *(u32 *)va;
	स्थिर काष्ठा cmd_info *info;

	info = get_cmd_info(s->vgpu->gvt, cmd, s->engine);
	अगर (info == शून्य) अणु
		gvt_vgpu_err("unknown cmd 0x%x, opcode=0x%x, addr_type=%s, ring %s, workload=%p\n",
			     cmd, get_opcode(cmd, s->engine),
			     repr_addr_type(s->buf_addr_type),
			     s->engine->name, s->workload);
		वापस -EBADRQC;
	पूर्ण

	अगर ((info->opcode == OP_MI_BATCH_BUFFER_END) ||
	    ((info->opcode == OP_MI_BATCH_BUFFER_START) &&
	     (BATCH_BUFFER_2ND_LEVEL_BIT(cmd) == 0)))
		वापस 0;

	वापस -EBADRQC;
पूर्ण

अटल पूर्णांक perक्रमm_bb_shaकरोw(काष्ठा parser_exec_state *s)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	काष्ठा पूर्णांकel_vgpu_shaकरोw_bb *bb;
	अचिन्हित दीर्घ gma = 0;
	अचिन्हित दीर्घ bb_size;
	अचिन्हित दीर्घ bb_end_cmd_offset;
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_vgpu_mm *mm = (s->buf_addr_type == GTT_BUFFER) ?
		s->vgpu->gtt.ggtt_mm : s->workload->shaकरोw_mm;
	अचिन्हित दीर्घ start_offset = 0;

	/* get the start gm address of the batch buffer */
	gma = get_gma_bb_from_cmd(s, 1);
	अगर (gma == INTEL_GVT_INVALID_ADDR)
		वापस -EFAULT;

	ret = find_bb_size(s, &bb_size, &bb_end_cmd_offset);
	अगर (ret)
		वापस ret;

	bb = kzalloc(माप(*bb), GFP_KERNEL);
	अगर (!bb)
		वापस -ENOMEM;

	bb->ppgtt = (s->buf_addr_type == GTT_BUFFER) ? false : true;

	/* the start_offset stores the batch buffer's start gma's
	 * offset relative to page boundary. so क्रम non-privileged batch
	 * buffer, the shaकरोwed gem object holds exactly the same page
	 * layout as original gem object. This is क्रम the convience of
	 * replacing the whole non-privilged batch buffer page to this
	 * shaकरोwed one in PPGTT at the same gma address. (this replacing
	 * action is not implemented yet now, but may be necessary in
	 * future).
	 * क्रम prileged batch buffer, we just change start gma address to
	 * that of shaकरोwed page.
	 */
	अगर (bb->ppgtt)
		start_offset = gma & ~I915_GTT_PAGE_MASK;

	bb->obj = i915_gem_object_create_shmem(s->engine->i915,
					       round_up(bb_size + start_offset,
							PAGE_SIZE));
	अगर (IS_ERR(bb->obj)) अणु
		ret = PTR_ERR(bb->obj);
		जाओ err_मुक्त_bb;
	पूर्ण

	bb->va = i915_gem_object_pin_map(bb->obj, I915_MAP_WB);
	अगर (IS_ERR(bb->va)) अणु
		ret = PTR_ERR(bb->va);
		जाओ err_मुक्त_obj;
	पूर्ण

	ret = copy_gma_to_hva(s->vgpu, mm,
			      gma, gma + bb_size,
			      bb->va + start_offset);
	अगर (ret < 0) अणु
		gvt_vgpu_err("fail to copy guest ring buffer\n");
		ret = -EFAULT;
		जाओ err_unmap;
	पूर्ण

	ret = audit_bb_end(s, bb->va + start_offset + bb_end_cmd_offset);
	अगर (ret)
		जाओ err_unmap;

	i915_gem_object_unlock(bb->obj);
	INIT_LIST_HEAD(&bb->list);
	list_add(&bb->list, &s->workload->shaकरोw_bb);

	bb->bb_start_cmd_va = s->ip_va;

	अगर ((s->buf_type == BATCH_BUFFER_INSTRUCTION) && (!s->is_ctx_wa))
		bb->bb_offset = s->ip_va - s->rb_va;
	अन्यथा
		bb->bb_offset = 0;

	/*
	 * ip_va saves the भव address of the shaकरोw batch buffer, जबतक
	 * ip_gma saves the graphics address of the original batch buffer.
	 * As the shaकरोw batch buffer is just a copy from the originial one,
	 * it should be right to use shaकरोw batch buffer'va and original batch
	 * buffer's gma in pair. After all, we don't want to pin the shaकरोw
	 * buffer here (too early).
	 */
	s->ip_va = bb->va + start_offset;
	s->ip_gma = gma;
	वापस 0;
err_unmap:
	i915_gem_object_unpin_map(bb->obj);
err_मुक्त_obj:
	i915_gem_object_put(bb->obj);
err_मुक्त_bb:
	kमुक्त(bb);
	वापस ret;
पूर्ण

अटल पूर्णांक cmd_handler_mi_batch_buffer_start(काष्ठा parser_exec_state *s)
अणु
	bool second_level;
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;

	अगर (s->buf_type == BATCH_BUFFER_2ND_LEVEL) अणु
		gvt_vgpu_err("Found MI_BATCH_BUFFER_START in 2nd level BB\n");
		वापस -EFAULT;
	पूर्ण

	second_level = BATCH_BUFFER_2ND_LEVEL_BIT(cmd_val(s, 0)) == 1;
	अगर (second_level && (s->buf_type != BATCH_BUFFER_INSTRUCTION)) अणु
		gvt_vgpu_err("Jumping to 2nd level BB from RB is not allowed\n");
		वापस -EFAULT;
	पूर्ण

	s->saved_buf_addr_type = s->buf_addr_type;
	addr_type_update_snb(s);
	अगर (s->buf_type == RING_BUFFER_INSTRUCTION) अणु
		s->ret_ip_gma_ring = s->ip_gma + cmd_length(s) * माप(u32);
		s->buf_type = BATCH_BUFFER_INSTRUCTION;
	पूर्ण अन्यथा अगर (second_level) अणु
		s->buf_type = BATCH_BUFFER_2ND_LEVEL;
		s->ret_ip_gma_bb = s->ip_gma + cmd_length(s) * माप(u32);
		s->ret_bb_va = s->ip_va + cmd_length(s) * माप(u32);
	पूर्ण

	अगर (batch_buffer_needs_scan(s)) अणु
		ret = perक्रमm_bb_shaकरोw(s);
		अगर (ret < 0)
			gvt_vgpu_err("invalid shadow batch buffer\n");
	पूर्ण अन्यथा अणु
		/* emulate a batch buffer end to करो वापस right */
		ret = cmd_handler_mi_batch_buffer_end(s);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mi_noop_index;

अटल स्थिर काष्ठा cmd_info cmd_info[] = अणु
	अणु"MI_NOOP", OP_MI_NOOP, F_LEN_CONST, R_ALL, D_ALL, 0, 1, शून्यपूर्ण,

	अणु"MI_SET_PREDICATE", OP_MI_SET_PREDICATE, F_LEN_CONST, R_ALL, D_ALL,
		0, 1, शून्यपूर्ण,

	अणु"MI_USER_INTERRUPT", OP_MI_USER_INTERRUPT, F_LEN_CONST, R_ALL, D_ALL,
		0, 1, cmd_handler_mi_user_पूर्णांकerruptपूर्ण,

	अणु"MI_WAIT_FOR_EVENT", OP_MI_WAIT_FOR_EVENT, F_LEN_CONST, R_RCS | R_BCS,
		D_ALL, 0, 1, cmd_handler_mi_रुको_क्रम_eventपूर्ण,

	अणु"MI_FLUSH", OP_MI_FLUSH, F_LEN_CONST, R_ALL, D_ALL, 0, 1, शून्यपूर्ण,

	अणु"MI_ARB_CHECK", OP_MI_ARB_CHECK, F_LEN_CONST, R_ALL, D_ALL, 0, 1,
		शून्यपूर्ण,

	अणु"MI_RS_CONTROL", OP_MI_RS_CONTROL, F_LEN_CONST, R_RCS, D_ALL, 0, 1,
		शून्यपूर्ण,

	अणु"MI_REPORT_HEAD", OP_MI_REPORT_HEAD, F_LEN_CONST, R_ALL, D_ALL, 0, 1,
		शून्यपूर्ण,

	अणु"MI_ARB_ON_OFF", OP_MI_ARB_ON_OFF, F_LEN_CONST, R_ALL, D_ALL, 0, 1,
		शून्यपूर्ण,

	अणु"MI_URB_ATOMIC_ALLOC", OP_MI_URB_ATOMIC_ALLOC, F_LEN_CONST, R_RCS,
		D_ALL, 0, 1, शून्यपूर्ण,

	अणु"MI_BATCH_BUFFER_END", OP_MI_BATCH_BUFFER_END,
		F_IP_ADVANCE_CUSTOM | F_LEN_CONST, R_ALL, D_ALL, 0, 1,
		cmd_handler_mi_batch_buffer_endपूर्ण,

	अणु"MI_SUSPEND_FLUSH", OP_MI_SUSPEND_FLUSH, F_LEN_CONST, R_ALL, D_ALL,
		0, 1, शून्यपूर्ण,

	अणु"MI_PREDICATE", OP_MI_PREDICATE, F_LEN_CONST, R_RCS, D_ALL, 0, 1,
		शून्यपूर्ण,

	अणु"MI_TOPOLOGY_FILTER", OP_MI_TOPOLOGY_FILTER, F_LEN_CONST, R_ALL,
		D_ALL, 0, 1, शून्यपूर्ण,

	अणु"MI_SET_APPID", OP_MI_SET_APPID, F_LEN_CONST, R_ALL, D_ALL, 0, 1,
		शून्यपूर्ण,

	अणु"MI_RS_CONTEXT", OP_MI_RS_CONTEXT, F_LEN_CONST, R_RCS, D_ALL, 0, 1,
		शून्यपूर्ण,

	अणु"MI_DISPLAY_FLIP", OP_MI_DISPLAY_FLIP, F_LEN_VAR,
		R_RCS | R_BCS, D_ALL, 0, 8, cmd_handler_mi_display_flipपूर्ण,

	अणु"MI_SEMAPHORE_MBOX", OP_MI_SEMAPHORE_MBOX, F_LEN_VAR | F_LEN_VAR_FIXED,
		R_ALL, D_ALL, 0, 8, शून्य, CMD_LEN(1)पूर्ण,

	अणु"MI_MATH", OP_MI_MATH, F_LEN_VAR, R_ALL, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"MI_URB_CLEAR", OP_MI_URB_CLEAR, F_LEN_VAR | F_LEN_VAR_FIXED, R_RCS,
		D_ALL, 0, 8, शून्य, CMD_LEN(0)पूर्ण,

	अणु"MI_SEMAPHORE_SIGNAL", OP_MI_SEMAPHORE_SIGNAL,
		F_LEN_VAR | F_LEN_VAR_FIXED, R_ALL, D_BDW_PLUS, 0, 8,
		शून्य, CMD_LEN(0)पूर्ण,

	अणु"MI_SEMAPHORE_WAIT", OP_MI_SEMAPHORE_WAIT,
		F_LEN_VAR | F_LEN_VAR_FIXED, R_ALL, D_BDW_PLUS, ADDR_FIX_1(2),
		8, cmd_handler_mi_semaphore_रुको, CMD_LEN(2)पूर्ण,

	अणु"MI_STORE_DATA_IMM", OP_MI_STORE_DATA_IMM, F_LEN_VAR, R_ALL, D_BDW_PLUS,
		ADDR_FIX_1(1), 10, cmd_handler_mi_store_data_immपूर्ण,

	अणु"MI_STORE_DATA_INDEX", OP_MI_STORE_DATA_INDEX, F_LEN_VAR, R_ALL, D_ALL,
		0, 8, cmd_handler_mi_store_data_indexपूर्ण,

	अणु"MI_LOAD_REGISTER_IMM", OP_MI_LOAD_REGISTER_IMM, F_LEN_VAR, R_ALL,
		D_ALL, 0, 8, cmd_handler_lriपूर्ण,

	अणु"MI_UPDATE_GTT", OP_MI_UPDATE_GTT, F_LEN_VAR, R_ALL, D_BDW_PLUS, 0, 10,
		cmd_handler_mi_update_gttपूर्ण,

	अणु"MI_STORE_REGISTER_MEM", OP_MI_STORE_REGISTER_MEM,
		F_LEN_VAR | F_LEN_VAR_FIXED, R_ALL, D_ALL, ADDR_FIX_1(2), 8,
		cmd_handler_srm, CMD_LEN(2)पूर्ण,

	अणु"MI_FLUSH_DW", OP_MI_FLUSH_DW, F_LEN_VAR, R_ALL, D_ALL, 0, 6,
		cmd_handler_mi_flush_dwपूर्ण,

	अणु"MI_CLFLUSH", OP_MI_CLFLUSH, F_LEN_VAR, R_ALL, D_ALL, ADDR_FIX_1(1),
		10, cmd_handler_mi_clflushपूर्ण,

	अणु"MI_REPORT_PERF_COUNT", OP_MI_REPORT_PERF_COUNT,
		F_LEN_VAR | F_LEN_VAR_FIXED, R_ALL, D_ALL, ADDR_FIX_1(1), 6,
		cmd_handler_mi_report_perf_count, CMD_LEN(2)पूर्ण,

	अणु"MI_LOAD_REGISTER_MEM", OP_MI_LOAD_REGISTER_MEM,
		F_LEN_VAR | F_LEN_VAR_FIXED, R_ALL, D_ALL, ADDR_FIX_1(2), 8,
		cmd_handler_lrm, CMD_LEN(2)पूर्ण,

	अणु"MI_LOAD_REGISTER_REG", OP_MI_LOAD_REGISTER_REG,
		F_LEN_VAR | F_LEN_VAR_FIXED, R_ALL, D_ALL, 0, 8,
		cmd_handler_lrr, CMD_LEN(1)पूर्ण,

	अणु"MI_RS_STORE_DATA_IMM", OP_MI_RS_STORE_DATA_IMM,
		F_LEN_VAR | F_LEN_VAR_FIXED, R_RCS, D_ALL, 0,
		8, शून्य, CMD_LEN(2)पूर्ण,

	अणु"MI_LOAD_URB_MEM", OP_MI_LOAD_URB_MEM, F_LEN_VAR | F_LEN_VAR_FIXED,
		R_RCS, D_ALL, ADDR_FIX_1(2), 8, शून्य, CMD_LEN(2)पूर्ण,

	अणु"MI_STORE_URM_MEM", OP_MI_STORE_URM_MEM, F_LEN_VAR, R_RCS, D_ALL,
		ADDR_FIX_1(2), 8, शून्यपूर्ण,

	अणु"MI_OP_2E", OP_MI_2E, F_LEN_VAR | F_LEN_VAR_FIXED, R_ALL, D_BDW_PLUS,
		ADDR_FIX_2(1, 2), 8, cmd_handler_mi_op_2e, CMD_LEN(3)पूर्ण,

	अणु"MI_OP_2F", OP_MI_2F, F_LEN_VAR, R_ALL, D_BDW_PLUS, ADDR_FIX_1(1),
		8, cmd_handler_mi_op_2fपूर्ण,

	अणु"MI_BATCH_BUFFER_START", OP_MI_BATCH_BUFFER_START,
		F_IP_ADVANCE_CUSTOM, R_ALL, D_ALL, 0, 8,
		cmd_handler_mi_batch_buffer_startपूर्ण,

	अणु"MI_CONDITIONAL_BATCH_BUFFER_END", OP_MI_CONDITIONAL_BATCH_BUFFER_END,
		F_LEN_VAR | F_LEN_VAR_FIXED, R_ALL, D_ALL, ADDR_FIX_1(2), 8,
		cmd_handler_mi_conditional_batch_buffer_end, CMD_LEN(2)पूर्ण,

	अणु"MI_LOAD_SCAN_LINES_INCL", OP_MI_LOAD_SCAN_LINES_INCL, F_LEN_CONST,
		R_RCS | R_BCS, D_ALL, 0, 2, शून्यपूर्ण,

	अणु"XY_SETUP_BLT", OP_XY_SETUP_BLT, F_LEN_VAR, R_BCS, D_ALL,
		ADDR_FIX_2(4, 7), 8, शून्यपूर्ण,

	अणु"XY_SETUP_CLIP_BLT", OP_XY_SETUP_CLIP_BLT, F_LEN_VAR, R_BCS, D_ALL,
		0, 8, शून्यपूर्ण,

	अणु"XY_SETUP_MONO_PATTERN_SL_BLT", OP_XY_SETUP_MONO_PATTERN_SL_BLT,
		F_LEN_VAR, R_BCS, D_ALL, ADDR_FIX_1(4), 8, शून्यपूर्ण,

	अणु"XY_PIXEL_BLT", OP_XY_PIXEL_BLT, F_LEN_VAR, R_BCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"XY_SCANLINES_BLT", OP_XY_SCANLINES_BLT, F_LEN_VAR, R_BCS, D_ALL,
		0, 8, शून्यपूर्ण,

	अणु"XY_TEXT_BLT", OP_XY_TEXT_BLT, F_LEN_VAR, R_BCS, D_ALL,
		ADDR_FIX_1(3), 8, शून्यपूर्ण,

	अणु"XY_TEXT_IMMEDIATE_BLT", OP_XY_TEXT_IMMEDIATE_BLT, F_LEN_VAR, R_BCS,
		D_ALL, 0, 8, शून्यपूर्ण,

	अणु"XY_COLOR_BLT", OP_XY_COLOR_BLT, F_LEN_VAR, R_BCS, D_ALL,
		ADDR_FIX_1(4), 8, शून्यपूर्ण,

	अणु"XY_PAT_BLT", OP_XY_PAT_BLT, F_LEN_VAR, R_BCS, D_ALL,
		ADDR_FIX_2(4, 5), 8, शून्यपूर्ण,

	अणु"XY_MONO_PAT_BLT", OP_XY_MONO_PAT_BLT, F_LEN_VAR, R_BCS, D_ALL,
		ADDR_FIX_1(4), 8, शून्यपूर्ण,

	अणु"XY_SRC_COPY_BLT", OP_XY_SRC_COPY_BLT, F_LEN_VAR, R_BCS, D_ALL,
		ADDR_FIX_2(4, 7), 8, शून्यपूर्ण,

	अणु"XY_MONO_SRC_COPY_BLT", OP_XY_MONO_SRC_COPY_BLT, F_LEN_VAR, R_BCS,
		D_ALL, ADDR_FIX_2(4, 5), 8, शून्यपूर्ण,

	अणु"XY_FULL_BLT", OP_XY_FULL_BLT, F_LEN_VAR, R_BCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"XY_FULL_MONO_SRC_BLT", OP_XY_FULL_MONO_SRC_BLT, F_LEN_VAR, R_BCS,
		D_ALL, ADDR_FIX_3(4, 5, 8), 8, शून्यपूर्ण,

	अणु"XY_FULL_MONO_PATTERN_BLT", OP_XY_FULL_MONO_PATTERN_BLT, F_LEN_VAR,
		R_BCS, D_ALL, ADDR_FIX_2(4, 7), 8, शून्यपूर्ण,

	अणु"XY_FULL_MONO_PATTERN_MONO_SRC_BLT",
		OP_XY_FULL_MONO_PATTERN_MONO_SRC_BLT,
		F_LEN_VAR, R_BCS, D_ALL, ADDR_FIX_2(4, 5), 8, शून्यपूर्ण,

	अणु"XY_MONO_PAT_FIXED_BLT", OP_XY_MONO_PAT_FIXED_BLT, F_LEN_VAR, R_BCS,
		D_ALL, ADDR_FIX_1(4), 8, शून्यपूर्ण,

	अणु"XY_MONO_SRC_COPY_IMMEDIATE_BLT", OP_XY_MONO_SRC_COPY_IMMEDIATE_BLT,
		F_LEN_VAR, R_BCS, D_ALL, ADDR_FIX_1(4), 8, शून्यपूर्ण,

	अणु"XY_PAT_BLT_IMMEDIATE", OP_XY_PAT_BLT_IMMEDIATE, F_LEN_VAR, R_BCS,
		D_ALL, ADDR_FIX_1(4), 8, शून्यपूर्ण,

	अणु"XY_SRC_COPY_CHROMA_BLT", OP_XY_SRC_COPY_CHROMA_BLT, F_LEN_VAR, R_BCS,
		D_ALL, ADDR_FIX_2(4, 7), 8, शून्यपूर्ण,

	अणु"XY_FULL_IMMEDIATE_PATTERN_BLT", OP_XY_FULL_IMMEDIATE_PATTERN_BLT,
		F_LEN_VAR, R_BCS, D_ALL, ADDR_FIX_2(4, 7), 8, शून्यपूर्ण,

	अणु"XY_FULL_MONO_SRC_IMMEDIATE_PATTERN_BLT",
		OP_XY_FULL_MONO_SRC_IMMEDIATE_PATTERN_BLT,
		F_LEN_VAR, R_BCS, D_ALL, ADDR_FIX_2(4, 5), 8, शून्यपूर्ण,

	अणु"XY_PAT_CHROMA_BLT", OP_XY_PAT_CHROMA_BLT, F_LEN_VAR, R_BCS, D_ALL,
		ADDR_FIX_2(4, 5), 8, शून्यपूर्ण,

	अणु"XY_PAT_CHROMA_BLT_IMMEDIATE", OP_XY_PAT_CHROMA_BLT_IMMEDIATE,
		F_LEN_VAR, R_BCS, D_ALL, ADDR_FIX_1(4), 8, शून्यपूर्ण,

	अणु"3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP",
		OP_3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_VIEWPORT_STATE_POINTERS_CC",
		OP_3DSTATE_VIEWPORT_STATE_POINTERS_CC,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_BLEND_STATE_POINTERS",
		OP_3DSTATE_BLEND_STATE_POINTERS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DEPTH_STENCIL_STATE_POINTERS",
		OP_3DSTATE_DEPTH_STENCIL_STATE_POINTERS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_POINTERS_VS",
		OP_3DSTATE_BINDING_TABLE_POINTERS_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_POINTERS_HS",
		OP_3DSTATE_BINDING_TABLE_POINTERS_HS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_POINTERS_DS",
		OP_3DSTATE_BINDING_TABLE_POINTERS_DS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_POINTERS_GS",
		OP_3DSTATE_BINDING_TABLE_POINTERS_GS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_POINTERS_PS",
		OP_3DSTATE_BINDING_TABLE_POINTERS_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLER_STATE_POINTERS_VS",
		OP_3DSTATE_SAMPLER_STATE_POINTERS_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLER_STATE_POINTERS_HS",
		OP_3DSTATE_SAMPLER_STATE_POINTERS_HS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLER_STATE_POINTERS_DS",
		OP_3DSTATE_SAMPLER_STATE_POINTERS_DS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLER_STATE_POINTERS_GS",
		OP_3DSTATE_SAMPLER_STATE_POINTERS_GS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLER_STATE_POINTERS_PS",
		OP_3DSTATE_SAMPLER_STATE_POINTERS_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_URB_VS", OP_3DSTATE_URB_VS, F_LEN_VAR, R_RCS, D_ALL,
		0, 8, शून्यपूर्ण,

	अणु"3DSTATE_URB_HS", OP_3DSTATE_URB_HS, F_LEN_VAR, R_RCS, D_ALL,
		0, 8, शून्यपूर्ण,

	अणु"3DSTATE_URB_DS", OP_3DSTATE_URB_DS, F_LEN_VAR, R_RCS, D_ALL,
		0, 8, शून्यपूर्ण,

	अणु"3DSTATE_URB_GS", OP_3DSTATE_URB_GS, F_LEN_VAR, R_RCS, D_ALL,
		0, 8, शून्यपूर्ण,

	अणु"3DSTATE_GATHER_CONSTANT_VS", OP_3DSTATE_GATHER_CONSTANT_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_GATHER_CONSTANT_GS", OP_3DSTATE_GATHER_CONSTANT_GS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_GATHER_CONSTANT_HS", OP_3DSTATE_GATHER_CONSTANT_HS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_GATHER_CONSTANT_DS", OP_3DSTATE_GATHER_CONSTANT_DS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_GATHER_CONSTANT_PS", OP_3DSTATE_GATHER_CONSTANT_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_CONSTANTF_VS", OP_3DSTATE_DX9_CONSTANTF_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 11, शून्यपूर्ण,

	अणु"3DSTATE_DX9_CONSTANTF_PS", OP_3DSTATE_DX9_CONSTANTF_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 11, शून्यपूर्ण,

	अणु"3DSTATE_DX9_CONSTANTI_VS", OP_3DSTATE_DX9_CONSTANTI_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_CONSTANTI_PS", OP_3DSTATE_DX9_CONSTANTI_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_CONSTANTB_VS", OP_3DSTATE_DX9_CONSTANTB_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_CONSTANTB_PS", OP_3DSTATE_DX9_CONSTANTB_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_LOCAL_VALID_VS", OP_3DSTATE_DX9_LOCAL_VALID_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_LOCAL_VALID_PS", OP_3DSTATE_DX9_LOCAL_VALID_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_GENERATE_ACTIVE_VS", OP_3DSTATE_DX9_GENERATE_ACTIVE_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_GENERATE_ACTIVE_PS", OP_3DSTATE_DX9_GENERATE_ACTIVE_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_EDIT_VS", OP_3DSTATE_BINDING_TABLE_EDIT_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 9, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_EDIT_GS", OP_3DSTATE_BINDING_TABLE_EDIT_GS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 9, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_EDIT_HS", OP_3DSTATE_BINDING_TABLE_EDIT_HS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 9, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_EDIT_DS", OP_3DSTATE_BINDING_TABLE_EDIT_DS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 9, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_EDIT_PS", OP_3DSTATE_BINDING_TABLE_EDIT_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 9, शून्यपूर्ण,

	अणु"3DSTATE_VF_INSTANCING", OP_3DSTATE_VF_INSTANCING, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_VF_SGVS", OP_3DSTATE_VF_SGVS, F_LEN_VAR, R_RCS, D_BDW_PLUS, 0, 8,
		शून्यपूर्ण,

	अणु"3DSTATE_VF_TOPOLOGY", OP_3DSTATE_VF_TOPOLOGY, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_WM_CHROMAKEY", OP_3DSTATE_WM_CHROMAKEY, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_PS_BLEND", OP_3DSTATE_PS_BLEND, F_LEN_VAR, R_RCS, D_BDW_PLUS, 0,
		8, शून्यपूर्ण,

	अणु"3DSTATE_WM_DEPTH_STENCIL", OP_3DSTATE_WM_DEPTH_STENCIL, F_LEN_VAR,
		R_RCS, D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_PS_EXTRA", OP_3DSTATE_PS_EXTRA, F_LEN_VAR, R_RCS, D_BDW_PLUS, 0,
		8, शून्यपूर्ण,

	अणु"3DSTATE_RASTER", OP_3DSTATE_RASTER, F_LEN_VAR, R_RCS, D_BDW_PLUS, 0, 8,
		शून्यपूर्ण,

	अणु"3DSTATE_SBE_SWIZ", OP_3DSTATE_SBE_SWIZ, F_LEN_VAR, R_RCS, D_BDW_PLUS, 0, 8,
		शून्यपूर्ण,

	अणु"3DSTATE_WM_HZ_OP", OP_3DSTATE_WM_HZ_OP, F_LEN_VAR, R_RCS, D_BDW_PLUS, 0, 8,
		शून्यपूर्ण,

	अणु"3DSTATE_VERTEX_BUFFERS", OP_3DSTATE_VERTEX_BUFFERS, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_VERTEX_ELEMENTS", OP_3DSTATE_VERTEX_ELEMENTS, F_LEN_VAR,
		R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_INDEX_BUFFER", OP_3DSTATE_INDEX_BUFFER, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, ADDR_FIX_1(2), 8, शून्यपूर्ण,

	अणु"3DSTATE_VF_STATISTICS", OP_3DSTATE_VF_STATISTICS, F_LEN_CONST,
		R_RCS, D_ALL, 0, 1, शून्यपूर्ण,

	अणु"3DSTATE_VF", OP_3DSTATE_VF, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_CC_STATE_POINTERS", OP_3DSTATE_CC_STATE_POINTERS, F_LEN_VAR,
		R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SCISSOR_STATE_POINTERS", OP_3DSTATE_SCISSOR_STATE_POINTERS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_GS", OP_3DSTATE_GS, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_CLIP", OP_3DSTATE_CLIP, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_WM", OP_3DSTATE_WM, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_CONSTANT_GS", OP_3DSTATE_CONSTANT_GS, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_CONSTANT_PS", OP_3DSTATE_CONSTANT_PS, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLE_MASK", OP_3DSTATE_SAMPLE_MASK, F_LEN_VAR, R_RCS,
		D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_CONSTANT_HS", OP_3DSTATE_CONSTANT_HS, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_CONSTANT_DS", OP_3DSTATE_CONSTANT_DS, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_HS", OP_3DSTATE_HS, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_TE", OP_3DSTATE_TE, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DS", OP_3DSTATE_DS, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_STREAMOUT", OP_3DSTATE_STREAMOUT, F_LEN_VAR, R_RCS,
		D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SBE", OP_3DSTATE_SBE, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_PS", OP_3DSTATE_PS, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DRAWING_RECTANGLE", OP_3DSTATE_DRAWING_RECTANGLE, F_LEN_VAR,
		R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLER_PALETTE_LOAD0", OP_3DSTATE_SAMPLER_PALETTE_LOAD0,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_CHROMA_KEY", OP_3DSTATE_CHROMA_KEY, F_LEN_VAR, R_RCS, D_ALL,
		0, 8, शून्यपूर्ण,

	अणु"3DSTATE_DEPTH_BUFFER", OP_3DSTATE_DEPTH_BUFFER, F_LEN_VAR, R_RCS,
		D_ALL, ADDR_FIX_1(2), 8, शून्यपूर्ण,

	अणु"3DSTATE_POLY_STIPPLE_OFFSET", OP_3DSTATE_POLY_STIPPLE_OFFSET,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_POLY_STIPPLE_PATTERN", OP_3DSTATE_POLY_STIPPLE_PATTERN,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_LINE_STIPPLE", OP_3DSTATE_LINE_STIPPLE, F_LEN_VAR, R_RCS,
		D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_AA_LINE_PARAMS", OP_3DSTATE_AA_LINE_PARAMS, F_LEN_VAR, R_RCS,
		D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_GS_SVB_INDEX", OP_3DSTATE_GS_SVB_INDEX, F_LEN_VAR, R_RCS,
		D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLER_PALETTE_LOAD1", OP_3DSTATE_SAMPLER_PALETTE_LOAD1,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_MULTISAMPLE", OP_3DSTATE_MULTISAMPLE_BDW, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_STENCIL_BUFFER", OP_3DSTATE_STENCIL_BUFFER, F_LEN_VAR, R_RCS,
		D_ALL, ADDR_FIX_1(2), 8, शून्यपूर्ण,

	अणु"3DSTATE_HIER_DEPTH_BUFFER", OP_3DSTATE_HIER_DEPTH_BUFFER, F_LEN_VAR,
		R_RCS, D_ALL, ADDR_FIX_1(2), 8, शून्यपूर्ण,

	अणु"3DSTATE_CLEAR_PARAMS", OP_3DSTATE_CLEAR_PARAMS, F_LEN_VAR,
		R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_PUSH_CONSTANT_ALLOC_VS", OP_3DSTATE_PUSH_CONSTANT_ALLOC_VS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_PUSH_CONSTANT_ALLOC_HS", OP_3DSTATE_PUSH_CONSTANT_ALLOC_HS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_PUSH_CONSTANT_ALLOC_DS", OP_3DSTATE_PUSH_CONSTANT_ALLOC_DS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_PUSH_CONSTANT_ALLOC_GS", OP_3DSTATE_PUSH_CONSTANT_ALLOC_GS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_PUSH_CONSTANT_ALLOC_PS", OP_3DSTATE_PUSH_CONSTANT_ALLOC_PS,
		F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_MONOFILTER_SIZE", OP_3DSTATE_MONOFILTER_SIZE, F_LEN_VAR,
		R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SO_DECL_LIST", OP_3DSTATE_SO_DECL_LIST, F_LEN_VAR, R_RCS,
		D_ALL, 0, 9, शून्यपूर्ण,

	अणु"3DSTATE_SO_BUFFER", OP_3DSTATE_SO_BUFFER, F_LEN_VAR, R_RCS, D_BDW_PLUS,
		ADDR_FIX_2(2, 4), 8, शून्यपूर्ण,

	अणु"3DSTATE_BINDING_TABLE_POOL_ALLOC",
		OP_3DSTATE_BINDING_TABLE_POOL_ALLOC,
		F_LEN_VAR, R_RCS, D_BDW_PLUS, ADDR_FIX_1(1), 8, शून्यपूर्ण,

	अणु"3DSTATE_GATHER_POOL_ALLOC", OP_3DSTATE_GATHER_POOL_ALLOC,
		F_LEN_VAR, R_RCS, D_BDW_PLUS, ADDR_FIX_1(1), 8, शून्यपूर्ण,

	अणु"3DSTATE_DX9_CONSTANT_BUFFER_POOL_ALLOC",
		OP_3DSTATE_DX9_CONSTANT_BUFFER_POOL_ALLOC,
		F_LEN_VAR, R_RCS, D_BDW_PLUS, ADDR_FIX_1(1), 8, शून्यपूर्ण,

	अणु"3DSTATE_SAMPLE_PATTERN", OP_3DSTATE_SAMPLE_PATTERN, F_LEN_VAR, R_RCS,
		D_BDW_PLUS, 0, 8, शून्यपूर्ण,

	अणु"PIPE_CONTROL", OP_PIPE_CONTROL, F_LEN_VAR, R_RCS, D_ALL,
		ADDR_FIX_1(2), 8, cmd_handler_pipe_controlपूर्ण,

	अणु"3DPRIMITIVE", OP_3DPRIMITIVE, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"PIPELINE_SELECT", OP_PIPELINE_SELECT, F_LEN_CONST, R_RCS, D_ALL, 0,
		1, शून्यपूर्ण,

	अणु"STATE_PREFETCH", OP_STATE_PREFETCH, F_LEN_VAR, R_RCS, D_ALL,
		ADDR_FIX_1(1), 8, शून्यपूर्ण,

	अणु"STATE_SIP", OP_STATE_SIP, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"STATE_BASE_ADDRESS", OP_STATE_BASE_ADDRESS, F_LEN_VAR, R_RCS, D_BDW_PLUS,
		ADDR_FIX_5(1, 3, 4, 5, 6), 8, शून्यपूर्ण,

	अणु"OP_3D_MEDIA_0_1_4", OP_3D_MEDIA_0_1_4, F_LEN_VAR, R_RCS, D_ALL,
		ADDR_FIX_1(1), 8, शून्यपूर्ण,

	अणु"OP_SWTESS_BASE_ADDRESS", OP_SWTESS_BASE_ADDRESS,
		F_LEN_VAR, R_RCS, D_ALL, ADDR_FIX_2(1, 2), 3, शून्यपूर्ण,

	अणु"3DSTATE_VS", OP_3DSTATE_VS, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_SF", OP_3DSTATE_SF, F_LEN_VAR, R_RCS, D_ALL, 0, 8, शून्यपूर्ण,

	अणु"3DSTATE_CONSTANT_VS", OP_3DSTATE_CONSTANT_VS, F_LEN_VAR, R_RCS, D_BDW_PLUS,
		0, 8, शून्यपूर्ण,

	अणु"3DSTATE_COMPONENT_PACKING", OP_3DSTATE_COMPONENT_PACKING, F_LEN_VAR, R_RCS,
		D_SKL_PLUS, 0, 8, शून्यपूर्ण,

	अणु"MEDIA_INTERFACE_DESCRIPTOR_LOAD", OP_MEDIA_INTERFACE_DESCRIPTOR_LOAD,
		F_LEN_VAR, R_RCS, D_ALL, 0, 16, शून्यपूर्ण,

	अणु"MEDIA_GATEWAY_STATE", OP_MEDIA_GATEWAY_STATE, F_LEN_VAR, R_RCS, D_ALL,
		0, 16, शून्यपूर्ण,

	अणु"MEDIA_STATE_FLUSH", OP_MEDIA_STATE_FLUSH, F_LEN_VAR, R_RCS, D_ALL,
		0, 16, शून्यपूर्ण,

	अणु"MEDIA_POOL_STATE", OP_MEDIA_POOL_STATE, F_LEN_VAR, R_RCS, D_ALL,
		0, 16, शून्यपूर्ण,

	अणु"MEDIA_OBJECT", OP_MEDIA_OBJECT, F_LEN_VAR, R_RCS, D_ALL, 0, 16, शून्यपूर्ण,

	अणु"MEDIA_CURBE_LOAD", OP_MEDIA_CURBE_LOAD, F_LEN_VAR, R_RCS, D_ALL,
		0, 16, शून्यपूर्ण,

	अणु"MEDIA_OBJECT_PRT", OP_MEDIA_OBJECT_PRT, F_LEN_VAR, R_RCS, D_ALL,
		0, 16, शून्यपूर्ण,

	अणु"MEDIA_OBJECT_WALKER", OP_MEDIA_OBJECT_WALKER, F_LEN_VAR, R_RCS, D_ALL,
		0, 16, शून्यपूर्ण,

	अणु"GPGPU_WALKER", OP_GPGPU_WALKER, F_LEN_VAR, R_RCS, D_ALL,
		0, 8, शून्यपूर्ण,

	अणु"MEDIA_VFE_STATE", OP_MEDIA_VFE_STATE, F_LEN_VAR, R_RCS, D_ALL, 0, 16,
		शून्यपूर्ण,

	अणु"3DSTATE_VF_STATISTICS_GM45", OP_3DSTATE_VF_STATISTICS_GM45,
		F_LEN_CONST, R_ALL, D_ALL, 0, 1, शून्यपूर्ण,

	अणु"MFX_PIPE_MODE_SELECT", OP_MFX_PIPE_MODE_SELECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_SURFACE_STATE", OP_MFX_SURFACE_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_PIPE_BUF_ADDR_STATE", OP_MFX_PIPE_BUF_ADDR_STATE, F_LEN_VAR,
		R_VCS, D_BDW_PLUS, 0, 12, शून्यपूर्ण,

	अणु"MFX_IND_OBJ_BASE_ADDR_STATE", OP_MFX_IND_OBJ_BASE_ADDR_STATE,
		F_LEN_VAR, R_VCS, D_BDW_PLUS, 0, 12, शून्यपूर्ण,

	अणु"MFX_BSP_BUF_BASE_ADDR_STATE", OP_MFX_BSP_BUF_BASE_ADDR_STATE,
		F_LEN_VAR, R_VCS, D_BDW_PLUS, ADDR_FIX_3(1, 3, 5), 12, शून्यपूर्ण,

	अणु"OP_2_0_0_5", OP_2_0_0_5, F_LEN_VAR, R_VCS, D_BDW_PLUS, 0, 12, शून्यपूर्ण,

	अणु"MFX_STATE_POINTER", OP_MFX_STATE_POINTER, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_QM_STATE", OP_MFX_QM_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_FQM_STATE", OP_MFX_FQM_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_PAK_INSERT_OBJECT", OP_MFX_PAK_INSERT_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_STITCH_OBJECT", OP_MFX_STITCH_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_IT_OBJECT", OP_MFD_IT_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_WAIT", OP_MFX_WAIT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 6, शून्यपूर्ण,

	अणु"MFX_AVC_IMG_STATE", OP_MFX_AVC_IMG_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_AVC_QM_STATE", OP_MFX_AVC_QM_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_AVC_DIRECTMODE_STATE", OP_MFX_AVC_सूचीECTMODE_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_AVC_SLICE_STATE", OP_MFX_AVC_SLICE_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_AVC_REF_IDX_STATE", OP_MFX_AVC_REF_IDX_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_AVC_WEIGHTOFFSET_STATE", OP_MFX_AVC_WEIGHTOFFSET_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_AVC_PICID_STATE", OP_MFD_AVC_PICID_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,
	अणु"MFD_AVC_DPB_STATE", OP_MFD_AVC_DPB_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_AVC_BSD_OBJECT", OP_MFD_AVC_BSD_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_AVC_SLICEADDR", OP_MFD_AVC_SLICEADDR, F_LEN_VAR,
		R_VCS, D_ALL, ADDR_FIX_1(2), 12, शून्यपूर्ण,

	अणु"MFC_AVC_PAK_OBJECT", OP_MFC_AVC_PAK_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_VC1_PRED_PIPE_STATE", OP_MFX_VC1_PRED_PIPE_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_VC1_DIRECTMODE_STATE", OP_MFX_VC1_सूचीECTMODE_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_VC1_SHORT_PIC_STATE", OP_MFD_VC1_SHORT_PIC_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_VC1_LONG_PIC_STATE", OP_MFD_VC1_LONG_PIC_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_VC1_BSD_OBJECT", OP_MFD_VC1_BSD_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFC_MPEG2_SLICEGROUP_STATE", OP_MFC_MPEG2_SLICEGROUP_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFC_MPEG2_PAK_OBJECT", OP_MFC_MPEG2_PAK_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_MPEG2_PIC_STATE", OP_MFX_MPEG2_PIC_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_MPEG2_QM_STATE", OP_MFX_MPEG2_QM_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_MPEG2_BSD_OBJECT", OP_MFD_MPEG2_BSD_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_2_6_0_0", OP_MFX_2_6_0_0, F_LEN_VAR, R_VCS, D_ALL,
		0, 16, शून्यपूर्ण,

	अणु"MFX_2_6_0_9", OP_MFX_2_6_0_9, F_LEN_VAR, R_VCS, D_ALL, 0, 16, शून्यपूर्ण,

	अणु"MFX_2_6_0_8", OP_MFX_2_6_0_8, F_LEN_VAR, R_VCS, D_ALL, 0, 16, शून्यपूर्ण,

	अणु"MFX_JPEG_PIC_STATE", OP_MFX_JPEG_PIC_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFX_JPEG_HUFF_TABLE_STATE", OP_MFX_JPEG_HUFF_TABLE_STATE, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"MFD_JPEG_BSD_OBJECT", OP_MFD_JPEG_BSD_OBJECT, F_LEN_VAR,
		R_VCS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"VEBOX_STATE", OP_VEB_STATE, F_LEN_VAR, R_VECS, D_ALL, 0, 12, शून्यपूर्ण,

	अणु"VEBOX_SURFACE_STATE", OP_VEB_SURFACE_STATE, F_LEN_VAR, R_VECS, D_ALL,
		0, 12, शून्यपूर्ण,

	अणु"VEB_DI_IECP", OP_VEB_DNDI_IECP_STATE, F_LEN_VAR, R_VECS, D_BDW_PLUS,
		0, 12, शून्यपूर्ण,
पूर्ण;

अटल व्योम add_cmd_entry(काष्ठा पूर्णांकel_gvt *gvt, काष्ठा cmd_entry *e)
अणु
	hash_add(gvt->cmd_table, &e->hlist, e->info->opcode);
पूर्ण

/* call the cmd handler, and advance ip */
अटल पूर्णांक cmd_parser_exec(काष्ठा parser_exec_state *s)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;
	स्थिर काष्ठा cmd_info *info;
	u32 cmd;
	पूर्णांक ret = 0;

	cmd = cmd_val(s, 0);

	/* fastpath क्रम MI_NOOP */
	अगर (cmd == MI_NOOP)
		info = &cmd_info[mi_noop_index];
	अन्यथा
		info = get_cmd_info(s->vgpu->gvt, cmd, s->engine);

	अगर (info == शून्य) अणु
		gvt_vgpu_err("unknown cmd 0x%x, opcode=0x%x, addr_type=%s, ring %s, workload=%p\n",
			     cmd, get_opcode(cmd, s->engine),
			     repr_addr_type(s->buf_addr_type),
			     s->engine->name, s->workload);
		वापस -EBADRQC;
	पूर्ण

	s->info = info;

	trace_gvt_command(vgpu->id, s->engine->id, s->ip_gma, s->ip_va,
			  cmd_length(s), s->buf_type, s->buf_addr_type,
			  s->workload, info->name);

	अगर ((info->flag & F_LEN_MASK) == F_LEN_VAR_FIXED) अणु
		ret = gvt_check_valid_cmd_length(cmd_length(s),
						 info->valid_len);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (info->handler) अणु
		ret = info->handler(s);
		अगर (ret < 0) अणु
			gvt_vgpu_err("%s handler error\n", info->name);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!(info->flag & F_IP_ADVANCE_CUSTOM)) अणु
		ret = cmd_advance_शेष(s);
		अगर (ret) अणु
			gvt_vgpu_err("%s IP advance error\n", info->name);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool gma_out_of_range(अचिन्हित दीर्घ gma,
		अचिन्हित दीर्घ gma_head, अचिन्हित पूर्णांक gma_tail)
अणु
	अगर (gma_tail >= gma_head)
		वापस (gma < gma_head) || (gma > gma_tail);
	अन्यथा
		वापस (gma > gma_tail) && (gma < gma_head);
पूर्ण

/* Keep the consistent वापस type, e.g EBADRQC क्रम unknown
 * cmd, EFAULT क्रम invalid address, EPERM क्रम nonpriv. later
 * works as the input of VM healthy status.
 */
अटल पूर्णांक command_scan(काष्ठा parser_exec_state *s,
		अचिन्हित दीर्घ rb_head, अचिन्हित दीर्घ rb_tail,
		अचिन्हित दीर्घ rb_start, अचिन्हित दीर्घ rb_len)
अणु

	अचिन्हित दीर्घ gma_head, gma_tail, gma_bottom;
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_vgpu *vgpu = s->vgpu;

	gma_head = rb_start + rb_head;
	gma_tail = rb_start + rb_tail;
	gma_bottom = rb_start +  rb_len;

	जबतक (s->ip_gma != gma_tail) अणु
		अगर (s->buf_type == RING_BUFFER_INSTRUCTION ||
				s->buf_type == RING_BUFFER_CTX) अणु
			अगर (!(s->ip_gma >= rb_start) ||
				!(s->ip_gma < gma_bottom)) अणु
				gvt_vgpu_err("ip_gma %lx out of ring scope."
					"(base:0x%lx, bottom: 0x%lx)\n",
					s->ip_gma, rb_start,
					gma_bottom);
				parser_exec_state_dump(s);
				वापस -EFAULT;
			पूर्ण
			अगर (gma_out_of_range(s->ip_gma, gma_head, gma_tail)) अणु
				gvt_vgpu_err("ip_gma %lx out of range."
					"base 0x%lx head 0x%lx tail 0x%lx\n",
					s->ip_gma, rb_start,
					rb_head, rb_tail);
				parser_exec_state_dump(s);
				अवरोध;
			पूर्ण
		पूर्ण
		ret = cmd_parser_exec(s);
		अगर (ret) अणु
			gvt_vgpu_err("cmd parser error\n");
			parser_exec_state_dump(s);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक scan_workload(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	अचिन्हित दीर्घ gma_head, gma_tail, gma_bottom;
	काष्ठा parser_exec_state s;
	पूर्णांक ret = 0;

	/* ring base is page aligned */
	अगर (WARN_ON(!IS_ALIGNED(workload->rb_start, I915_GTT_PAGE_SIZE)))
		वापस -EINVAL;

	gma_head = workload->rb_start + workload->rb_head;
	gma_tail = workload->rb_start + workload->rb_tail;
	gma_bottom = workload->rb_start +  _RING_CTL_BUF_SIZE(workload->rb_ctl);

	s.buf_type = RING_BUFFER_INSTRUCTION;
	s.buf_addr_type = GTT_BUFFER;
	s.vgpu = workload->vgpu;
	s.engine = workload->engine;
	s.ring_start = workload->rb_start;
	s.ring_size = _RING_CTL_BUF_SIZE(workload->rb_ctl);
	s.ring_head = gma_head;
	s.ring_tail = gma_tail;
	s.rb_va = workload->shaकरोw_ring_buffer_va;
	s.workload = workload;
	s.is_ctx_wa = false;

	अगर (bypass_scan_mask & workload->engine->mask || gma_head == gma_tail)
		वापस 0;

	ret = ip_gma_set(&s, gma_head);
	अगर (ret)
		जाओ out;

	ret = command_scan(&s, workload->rb_head, workload->rb_tail,
		workload->rb_start, _RING_CTL_BUF_SIZE(workload->rb_ctl));

out:
	वापस ret;
पूर्ण

अटल पूर्णांक scan_wa_ctx(काष्ठा पूर्णांकel_shaकरोw_wa_ctx *wa_ctx)
अणु

	अचिन्हित दीर्घ gma_head, gma_tail, gma_bottom, ring_size, ring_tail;
	काष्ठा parser_exec_state s;
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_vgpu_workload *workload = container_of(wa_ctx,
				काष्ठा पूर्णांकel_vgpu_workload,
				wa_ctx);

	/* ring base is page aligned */
	अगर (WARN_ON(!IS_ALIGNED(wa_ctx->indirect_ctx.guest_gma,
					I915_GTT_PAGE_SIZE)))
		वापस -EINVAL;

	ring_tail = wa_ctx->indirect_ctx.size + 3 * माप(u32);
	ring_size = round_up(wa_ctx->indirect_ctx.size + CACHELINE_BYTES,
			PAGE_SIZE);
	gma_head = wa_ctx->indirect_ctx.guest_gma;
	gma_tail = wa_ctx->indirect_ctx.guest_gma + ring_tail;
	gma_bottom = wa_ctx->indirect_ctx.guest_gma + ring_size;

	s.buf_type = RING_BUFFER_INSTRUCTION;
	s.buf_addr_type = GTT_BUFFER;
	s.vgpu = workload->vgpu;
	s.engine = workload->engine;
	s.ring_start = wa_ctx->indirect_ctx.guest_gma;
	s.ring_size = ring_size;
	s.ring_head = gma_head;
	s.ring_tail = gma_tail;
	s.rb_va = wa_ctx->indirect_ctx.shaकरोw_va;
	s.workload = workload;
	s.is_ctx_wa = true;

	ret = ip_gma_set(&s, gma_head);
	अगर (ret)
		जाओ out;

	ret = command_scan(&s, 0, ring_tail,
		wa_ctx->indirect_ctx.guest_gma, ring_size);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक shaकरोw_workload_ring_buffer(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	अचिन्हित दीर्घ gma_head, gma_tail, gma_top, guest_rb_size;
	व्योम *shaकरोw_ring_buffer_va;
	पूर्णांक ret;

	guest_rb_size = _RING_CTL_BUF_SIZE(workload->rb_ctl);

	/* calculate workload ring buffer size */
	workload->rb_len = (workload->rb_tail + guest_rb_size -
			workload->rb_head) % guest_rb_size;

	gma_head = workload->rb_start + workload->rb_head;
	gma_tail = workload->rb_start + workload->rb_tail;
	gma_top = workload->rb_start + guest_rb_size;

	अगर (workload->rb_len > s->ring_scan_buffer_size[workload->engine->id]) अणु
		व्योम *p;

		/* पुनः_स्मृति the new ring buffer अगर needed */
		p = kपुनः_स्मृति(s->ring_scan_buffer[workload->engine->id],
			     workload->rb_len, GFP_KERNEL);
		अगर (!p) अणु
			gvt_vgpu_err("fail to re-alloc ring scan buffer\n");
			वापस -ENOMEM;
		पूर्ण
		s->ring_scan_buffer[workload->engine->id] = p;
		s->ring_scan_buffer_size[workload->engine->id] = workload->rb_len;
	पूर्ण

	shaकरोw_ring_buffer_va = s->ring_scan_buffer[workload->engine->id];

	/* get shaकरोw ring buffer va */
	workload->shaकरोw_ring_buffer_va = shaकरोw_ring_buffer_va;

	/* head > tail --> copy head <-> top */
	अगर (gma_head > gma_tail) अणु
		ret = copy_gma_to_hva(vgpu, vgpu->gtt.ggtt_mm,
				      gma_head, gma_top, shaकरोw_ring_buffer_va);
		अगर (ret < 0) अणु
			gvt_vgpu_err("fail to copy guest ring buffer\n");
			वापस ret;
		पूर्ण
		shaकरोw_ring_buffer_va += ret;
		gma_head = workload->rb_start;
	पूर्ण

	/* copy head or start <-> tail */
	ret = copy_gma_to_hva(vgpu, vgpu->gtt.ggtt_mm, gma_head, gma_tail,
				shaकरोw_ring_buffer_va);
	अगर (ret < 0) अणु
		gvt_vgpu_err("fail to copy guest ring buffer\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_gvt_scan_and_shaकरोw_ringbuffer(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	पूर्णांक ret;
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;

	ret = shaकरोw_workload_ring_buffer(workload);
	अगर (ret) अणु
		gvt_vgpu_err("fail to shadow workload ring_buffer\n");
		वापस ret;
	पूर्ण

	ret = scan_workload(workload);
	अगर (ret) अणु
		gvt_vgpu_err("scan workload error\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक shaकरोw_indirect_ctx(काष्ठा पूर्णांकel_shaकरोw_wa_ctx *wa_ctx)
अणु
	पूर्णांक ctx_size = wa_ctx->indirect_ctx.size;
	अचिन्हित दीर्घ guest_gma = wa_ctx->indirect_ctx.guest_gma;
	काष्ठा पूर्णांकel_vgpu_workload *workload = container_of(wa_ctx,
					काष्ठा पूर्णांकel_vgpu_workload,
					wa_ctx);
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक ret = 0;
	व्योम *map;

	obj = i915_gem_object_create_shmem(workload->engine->i915,
					   roundup(ctx_size + CACHELINE_BYTES,
						   PAGE_SIZE));
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	/* get the va of the shaकरोw batch buffer */
	map = i915_gem_object_pin_map(obj, I915_MAP_WB);
	अगर (IS_ERR(map)) अणु
		gvt_vgpu_err("failed to vmap shadow indirect ctx\n");
		ret = PTR_ERR(map);
		जाओ put_obj;
	पूर्ण

	i915_gem_object_lock(obj, शून्य);
	ret = i915_gem_object_set_to_cpu_करोमुख्य(obj, false);
	i915_gem_object_unlock(obj);
	अगर (ret) अणु
		gvt_vgpu_err("failed to set shadow indirect ctx to CPU\n");
		जाओ unmap_src;
	पूर्ण

	ret = copy_gma_to_hva(workload->vgpu,
				workload->vgpu->gtt.ggtt_mm,
				guest_gma, guest_gma + ctx_size,
				map);
	अगर (ret < 0) अणु
		gvt_vgpu_err("fail to copy guest indirect ctx\n");
		जाओ unmap_src;
	पूर्ण

	wa_ctx->indirect_ctx.obj = obj;
	wa_ctx->indirect_ctx.shaकरोw_va = map;
	वापस 0;

unmap_src:
	i915_gem_object_unpin_map(obj);
put_obj:
	i915_gem_object_put(obj);
	वापस ret;
पूर्ण

अटल पूर्णांक combine_wa_ctx(काष्ठा पूर्णांकel_shaकरोw_wa_ctx *wa_ctx)
अणु
	u32 per_ctx_start[CACHELINE_DWORDS] = अणु0पूर्ण;
	अचिन्हित अक्षर *bb_start_sva;

	अगर (!wa_ctx->per_ctx.valid)
		वापस 0;

	per_ctx_start[0] = 0x18800001;
	per_ctx_start[1] = wa_ctx->per_ctx.guest_gma;

	bb_start_sva = (अचिन्हित अक्षर *)wa_ctx->indirect_ctx.shaकरोw_va +
				wa_ctx->indirect_ctx.size;

	स_नकल(bb_start_sva, per_ctx_start, CACHELINE_BYTES);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_gvt_scan_and_shaकरोw_wa_ctx(काष्ठा पूर्णांकel_shaकरोw_wa_ctx *wa_ctx)
अणु
	पूर्णांक ret;
	काष्ठा पूर्णांकel_vgpu_workload *workload = container_of(wa_ctx,
					काष्ठा पूर्णांकel_vgpu_workload,
					wa_ctx);
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;

	अगर (wa_ctx->indirect_ctx.size == 0)
		वापस 0;

	ret = shaकरोw_indirect_ctx(wa_ctx);
	अगर (ret) अणु
		gvt_vgpu_err("fail to shadow indirect ctx\n");
		वापस ret;
	पूर्ण

	combine_wa_ctx(wa_ctx);

	ret = scan_wa_ctx(wa_ctx);
	अगर (ret) अणु
		gvt_vgpu_err("scan wa ctx error\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* generate dummy contexts by sending empty requests to HW, and let
 * the HW to fill Engine Contexts. This dummy contexts are used क्रम
 * initialization purpose (update reg whitelist), so referred to as
 * init context here
 */
व्योम पूर्णांकel_gvt_update_reg_whitelist(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	स्थिर अचिन्हित दीर्घ start = LRC_STATE_PN * PAGE_SIZE;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	अगर (gvt->is_reg_whitelist_updated)
		वापस;

	/* scan init ctx to update cmd accessible list */
	क्रम_each_engine(engine, gvt->gt, id) अणु
		काष्ठा parser_exec_state s;
		व्योम *vaddr;
		पूर्णांक ret;

		अगर (!engine->शेष_state)
			जारी;

		vaddr = shmem_pin_map(engine->शेष_state);
		अगर (IS_ERR(vaddr)) अणु
			gvt_err("failed to map %s->default state, err:%zd\n",
				engine->name, PTR_ERR(vaddr));
			वापस;
		पूर्ण

		s.buf_type = RING_BUFFER_CTX;
		s.buf_addr_type = GTT_BUFFER;
		s.vgpu = vgpu;
		s.engine = engine;
		s.ring_start = 0;
		s.ring_size = engine->context_size - start;
		s.ring_head = 0;
		s.ring_tail = s.ring_size;
		s.rb_va = vaddr + start;
		s.workload = शून्य;
		s.is_ctx_wa = false;
		s.is_init_ctx = true;

		/* skipping the first RING_CTX_SIZE(0x50) dwords */
		ret = ip_gma_set(&s, RING_CTX_SIZE);
		अगर (ret == 0) अणु
			ret = command_scan(&s, 0, s.ring_size, 0, s.ring_size);
			अगर (ret)
				gvt_err("Scan init ctx error\n");
		पूर्ण

		shmem_unpin_map(engine->शेष_state, vaddr);
		अगर (ret)
			वापस;
	पूर्ण

	gvt->is_reg_whitelist_updated = true;
पूर्ण

पूर्णांक पूर्णांकel_gvt_scan_engine_context(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	अचिन्हित दीर्घ gma_head, gma_tail, gma_start, ctx_size;
	काष्ठा parser_exec_state s;
	पूर्णांक ring_id = workload->engine->id;
	काष्ठा पूर्णांकel_context *ce = vgpu->submission.shaकरोw[ring_id];
	पूर्णांक ret;

	GEM_BUG_ON(atomic_पढ़ो(&ce->pin_count) < 0);

	ctx_size = workload->engine->context_size - PAGE_SIZE;

	/* Only ring contxt is loaded to HW क्रम inhibit context, no need to
	 * scan engine context
	 */
	अगर (is_inhibit_context(ce))
		वापस 0;

	gma_start = i915_ggtt_offset(ce->state) + LRC_STATE_PN*PAGE_SIZE;
	gma_head = 0;
	gma_tail = ctx_size;

	s.buf_type = RING_BUFFER_CTX;
	s.buf_addr_type = GTT_BUFFER;
	s.vgpu = workload->vgpu;
	s.engine = workload->engine;
	s.ring_start = gma_start;
	s.ring_size = ctx_size;
	s.ring_head = gma_start + gma_head;
	s.ring_tail = gma_start + gma_tail;
	s.rb_va = ce->lrc_reg_state;
	s.workload = workload;
	s.is_ctx_wa = false;
	s.is_init_ctx = false;

	/* करोn't scan the first RING_CTX_SIZE(0x50) dwords, as it's ring
	 * context
	 */
	ret = ip_gma_set(&s, gma_start + gma_head + RING_CTX_SIZE);
	अगर (ret)
		जाओ out;

	ret = command_scan(&s, gma_head, gma_tail,
		gma_start, ctx_size);
out:
	अगर (ret)
		gvt_vgpu_err("scan shadow ctx error\n");

	वापस ret;
पूर्ण

अटल पूर्णांक init_cmd_table(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	अचिन्हित पूर्णांक gen_type = पूर्णांकel_gvt_get_device_type(gvt);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cmd_info); i++) अणु
		काष्ठा cmd_entry *e;

		अगर (!(cmd_info[i].devices & gen_type))
			जारी;

		e = kzalloc(माप(*e), GFP_KERNEL);
		अगर (!e)
			वापस -ENOMEM;

		e->info = &cmd_info[i];
		अगर (cmd_info[i].opcode == OP_MI_NOOP)
			mi_noop_index = i;

		INIT_HLIST_NODE(&e->hlist);
		add_cmd_entry(gvt, e);
		gvt_dbg_cmd("add %-30s op %04x flag %x devs %02x rings %02x\n",
			    e->info->name, e->info->opcode, e->info->flag,
			    e->info->devices, e->info->rings);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clean_cmd_table(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा hlist_node *पंचांगp;
	काष्ठा cmd_entry *e;
	पूर्णांक i;

	hash_क्रम_each_safe(gvt->cmd_table, i, पंचांगp, e, hlist)
		kमुक्त(e);

	hash_init(gvt->cmd_table);
पूर्ण

व्योम पूर्णांकel_gvt_clean_cmd_parser(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	clean_cmd_table(gvt);
पूर्ण

पूर्णांक पूर्णांकel_gvt_init_cmd_parser(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	पूर्णांक ret;

	ret = init_cmd_table(gvt);
	अगर (ret) अणु
		पूर्णांकel_gvt_clean_cmd_parser(gvt);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
