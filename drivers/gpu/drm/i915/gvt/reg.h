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
 */

#अगर_अघोषित _GVT_REG_H
#घोषणा _GVT_REG_H

#घोषणा INTEL_GVT_PCI_CLASS_VGA_OTHER   0x80

#घोषणा INTEL_GVT_PCI_GMCH_CONTROL	0x50
#घोषणा   BDW_GMCH_GMS_SHIFT		8
#घोषणा   BDW_GMCH_GMS_MASK		0xff

#घोषणा INTEL_GVT_PCI_SWSCI		0xe8
#घोषणा   SWSCI_SCI_SELECT		(1 << 15)
#घोषणा   SWSCI_SCI_TRIGGER		1

#घोषणा INTEL_GVT_PCI_OPREGION		0xfc

#घोषणा INTEL_GVT_OPREGION_CLID		0x1AC
#घोषणा INTEL_GVT_OPREGION_SCIC		0x200
#घोषणा   OPREGION_SCIC_FUNC_MASK	0x1E
#घोषणा   OPREGION_SCIC_FUNC_SHIFT	1
#घोषणा   OPREGION_SCIC_SUBFUNC_MASK	0xFF00
#घोषणा   OPREGION_SCIC_SUBFUNC_SHIFT	8
#घोषणा   OPREGION_SCIC_EXIT_MASK	0xE0
#घोषणा INTEL_GVT_OPREGION_SCIC_F_GETBIOSDATA         4
#घोषणा INTEL_GVT_OPREGION_SCIC_F_GETBIOSCALLBACKS    6
#घोषणा INTEL_GVT_OPREGION_SCIC_SF_SUPPRTEDCALLS      0
#घोषणा INTEL_GVT_OPREGION_SCIC_SF_REQEUSTEDCALLBACKS 1
#घोषणा INTEL_GVT_OPREGION_PARM                   0x204

#घोषणा INTEL_GVT_OPREGION_PAGES	2
#घोषणा INTEL_GVT_OPREGION_SIZE		(INTEL_GVT_OPREGION_PAGES * PAGE_SIZE)
#घोषणा INTEL_GVT_OPREGION_VBT_OFFSET	0x400
#घोषणा INTEL_GVT_OPREGION_VBT_SIZE	\
		(INTEL_GVT_OPREGION_SIZE - INTEL_GVT_OPREGION_VBT_OFFSET)

#घोषणा VGT_SPRSTRIDE(pipe)	_PIPE(pipe, _SPRA_STRIDE, _PLANE_STRIDE_2_B)

#घोषणा _REG_701C0(pipe, plane) (0x701c0 + pipe * 0x1000 + (plane - 1) * 0x100)
#घोषणा _REG_701C4(pipe, plane) (0x701c4 + pipe * 0x1000 + (plane - 1) * 0x100)

#घोषणा SKL_FLIP_EVENT(pipe, plane) (PRIMARY_A_FLIP_DONE + (plane) * 3 + (pipe))

#घोषणा PLANE_CTL_ASYNC_FLIP		(1 << 9)
#घोषणा REG50080_FLIP_TYPE_MASK	0x3
#घोषणा REG50080_FLIP_TYPE_ASYNC	0x1

#घोषणा REG_50080(_pipe, _plane) (अणु \
	typeof(_pipe) (p) = (_pipe); \
	typeof(_plane) (q) = (_plane); \
	(((p) == PIPE_A) ? (((q) == PLANE_PRIMARY) ? (_MMIO(0x50080)) : \
		(_MMIO(0x50090))) : \
	(((p) == PIPE_B) ? (((q) == PLANE_PRIMARY) ? (_MMIO(0x50088)) : \
		(_MMIO(0x50098))) : \
	(((p) == PIPE_C) ? (((q) == PLANE_PRIMARY) ? (_MMIO(0x5008C)) : \
		(_MMIO(0x5009C))) : \
		(_MMIO(0x50080))))); पूर्ण)

#घोषणा REG_50080_TO_PIPE(_reg) (अणु \
	typeof(_reg) (reg) = (_reg); \
	(((reg) == 0x50080 || (reg) == 0x50090) ? (PIPE_A) : \
	(((reg) == 0x50088 || (reg) == 0x50098) ? (PIPE_B) : \
	(((reg) == 0x5008C || (reg) == 0x5009C) ? (PIPE_C) : \
	(INVALID_PIPE)))); पूर्ण)

#घोषणा REG_50080_TO_PLANE(_reg) (अणु \
	typeof(_reg) (reg) = (_reg); \
	(((reg) == 0x50080 || (reg) == 0x50088 || (reg) == 0x5008C) ? \
		(PLANE_PRIMARY) : \
	(((reg) == 0x50090 || (reg) == 0x50098 || (reg) == 0x5009C) ? \
		(PLANE_SPRITE0) : (I915_MAX_PLANES))); पूर्ण)

#घोषणा GFX_MODE_BIT_SET_IN_MASK(val, bit) \
		((((bit) & 0xffff0000) == 0) && !!((val) & (((bit) << 16))))

#घोषणा IS_MASKED_BITS_ENABLED(_val, _b) \
		(((_val) & _MASKED_BIT_ENABLE(_b)) == _MASKED_BIT_ENABLE(_b))
#घोषणा IS_MASKED_BITS_DISABLED(_val, _b) \
		((_val) & _MASKED_BIT_DISABLE(_b))

#घोषणा FORCEWAKE_RENDER_GEN9_REG 0xa278
#घोषणा FORCEWAKE_ACK_RENDER_GEN9_REG 0x0D84
#घोषणा FORCEWAKE_GT_GEN9_REG 0xa188
#घोषणा FORCEWAKE_ACK_GT_GEN9_REG 0x130044
#घोषणा FORCEWAKE_MEDIA_GEN9_REG 0xa270
#घोषणा FORCEWAKE_ACK_MEDIA_GEN9_REG 0x0D88
#घोषणा FORCEWAKE_ACK_HSW_REG 0x130044

#घोषणा RB_HEAD_WRAP_CNT_MAX	((1 << 11) - 1)
#घोषणा RB_HEAD_WRAP_CNT_OFF	21
#घोषणा RB_HEAD_OFF_MASK	((1U << 21) - (1U << 2))
#घोषणा RB_TAIL_OFF_MASK	((1U << 21) - (1U << 3))
#घोषणा RB_TAIL_SIZE_MASK	((1U << 21) - (1U << 12))
#घोषणा _RING_CTL_BUF_SIZE(ctl) (((ctl) & RB_TAIL_SIZE_MASK) + \
		I915_GTT_PAGE_SIZE)

#घोषणा PCH_GPIO_BASE	_MMIO(0xc5010)

#घोषणा PCH_GMBUS0	_MMIO(0xc5100)
#घोषणा PCH_GMBUS1	_MMIO(0xc5104)
#घोषणा PCH_GMBUS2	_MMIO(0xc5108)
#घोषणा PCH_GMBUS3	_MMIO(0xc510c)
#घोषणा PCH_GMBUS4	_MMIO(0xc5110)
#घोषणा PCH_GMBUS5	_MMIO(0xc5120)

#घोषणा TRVATTL3PTRDW(i)	_MMIO(0x4de0 + (i) * 4)
#घोषणा TRशून्यDETCT		_MMIO(0x4de8)
#घोषणा TRINVTILEDETCT		_MMIO(0x4dec)
#घोषणा TRVADR			_MMIO(0x4df0)
#घोषणा TRTTE			_MMIO(0x4df4)
#घोषणा RING_EXCC(base)		_MMIO((base) + 0x28)
#घोषणा RING_GFX_MODE(base)	_MMIO((base) + 0x29c)
#घोषणा VF_GUARDBAND		_MMIO(0x83a4)


#घोषणा BCS_TILE_REGISTER_VAL_OFFSET (0x43*4)
#पूर्ण_अगर
