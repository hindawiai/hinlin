<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित CIK_REGS_H
#घोषणा CIK_REGS_H

/* अगर PTR32, these are the bases क्रम scratch and lds */
#घोषणा	PRIVATE_BASE(x)					((x) << 0) /* scratch */
#घोषणा	SHARED_BASE(x)					((x) << 16) /* LDS */
#घोषणा	PTR32						(1 << 0)
#घोषणा	ALIGNMENT_MODE(x)				((x) << 2)
#घोषणा	SH_MEM_ALIGNMENT_MODE_UNALIGNED			3
#घोषणा	DEFAULT_MTYPE(x)				((x) << 4)
#घोषणा	APE1_MTYPE(x)					((x) << 7)

/* valid क्रम both DEFAULT_MTYPE and APE1_MTYPE */
#घोषणा	MTYPE_CACHED_NV					0
#घोषणा	MTYPE_CACHED					1
#घोषणा	MTYPE_NONCACHED					3

#घोषणा	DEFAULT_CP_HQD_PERSISTENT_STATE			(0x33U << 8)
#घोषणा	PRELOAD_REQ					(1 << 0)

#घोषणा	MQD_CONTROL_PRIV_STATE_EN			(1U << 8)

#घोषणा	DEFAULT_MIN_IB_AVAIL_SIZE			(3U << 20)

#घोषणा	IB_ATC_EN					(1U << 23)

#घोषणा	QUANTUM_EN					1U
#घोषणा	QUANTUM_SCALE_1MS				(1U << 4)
#घोषणा	QUANTUM_DURATION(x)				((x) << 8)

#घोषणा	RPTR_BLOCK_SIZE(x)				((x) << 8)
#घोषणा	MIN_AVAIL_SIZE(x)				((x) << 20)
#घोषणा	DEFAULT_RPTR_BLOCK_SIZE				RPTR_BLOCK_SIZE(5)
#घोषणा	DEFAULT_MIN_AVAIL_SIZE				MIN_AVAIL_SIZE(3)

#घोषणा	PQ_ATC_EN					(1 << 23)
#घोषणा	NO_UPDATE_RPTR					(1 << 27)

#घोषणा	DOORBELL_OFFSET(x)				((x) << 2)
#घोषणा	DOORBELL_EN					(1 << 30)

#घोषणा	PRIV_STATE					(1 << 30)
#घोषणा	KMD_QUEUE					(1 << 31)

#घोषणा	AQL_ENABLE					1

#घोषणा GRBM_GFX_INDEX					0x30800

#पूर्ण_अगर
