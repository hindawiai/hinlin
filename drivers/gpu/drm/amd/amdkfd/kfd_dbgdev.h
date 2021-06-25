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

#अगर_अघोषित KFD_DBGDEV_H_
#घोषणा KFD_DBGDEV_H_

क्रमागत अणु
	SQ_CMD_VMID_OFFSET = 28,
	ADDRESS_WATCH_CNTL_OFFSET = 24
पूर्ण;

क्रमागत अणु
	PRIV_QUEUE_SYNC_TIME_MS = 200
पूर्ण;

/* CONTEXT reg space definition */
क्रमागत अणु
	CONTEXT_REG_BASE = 0xA000,
	CONTEXT_REG_END = 0xA400,
	CONTEXT_REG_SIZE = CONTEXT_REG_END - CONTEXT_REG_BASE
पूर्ण;

/* USER CONFIG reg space definition */
क्रमागत अणु
	USERCONFIG_REG_BASE = 0xC000,
	USERCONFIG_REG_END = 0x10000,
	USERCONFIG_REG_SIZE = USERCONFIG_REG_END - USERCONFIG_REG_BASE
पूर्ण;

/* CONFIG reg space definition */
क्रमागत अणु
	AMD_CONFIG_REG_BASE = 0x2000,	/* in dwords */
	AMD_CONFIG_REG_END = 0x2B00,
	AMD_CONFIG_REG_SIZE = AMD_CONFIG_REG_END - AMD_CONFIG_REG_BASE
पूर्ण;

/* SH reg space definition */
क्रमागत अणु
	SH_REG_BASE = 0x2C00,
	SH_REG_END = 0x3000,
	SH_REG_SIZE = SH_REG_END - SH_REG_BASE
पूर्ण;

/* SQ_CMD definitions */
#घोषणा SQ_CMD						0x8DEC

क्रमागत SQ_IND_CMD_CMD अणु
	SQ_IND_CMD_CMD_शून्य = 0x00000000,
	SQ_IND_CMD_CMD_HALT = 0x00000001,
	SQ_IND_CMD_CMD_RESUME = 0x00000002,
	SQ_IND_CMD_CMD_KILL = 0x00000003,
	SQ_IND_CMD_CMD_DEBUG = 0x00000004,
	SQ_IND_CMD_CMD_TRAP = 0x00000005,
पूर्ण;

क्रमागत SQ_IND_CMD_MODE अणु
	SQ_IND_CMD_MODE_SINGLE = 0x00000000,
	SQ_IND_CMD_MODE_BROADCAST = 0x00000001,
	SQ_IND_CMD_MODE_BROADCAST_QUEUE = 0x00000002,
	SQ_IND_CMD_MODE_BROADCAST_PIPE = 0x00000003,
	SQ_IND_CMD_MODE_BROADCAST_ME = 0x00000004,
पूर्ण;

जोड़ SQ_IND_INDEX_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t wave_id:4;
		uपूर्णांक32_t simd_id:2;
		uपूर्णांक32_t thपढ़ो_id:6;
		 uपूर्णांक32_t:1;
		uपूर्णांक32_t क्रमce_पढ़ो:1;
		uपूर्णांक32_t पढ़ो_समयout:1;
		uपूर्णांक32_t unindexed:1;
		uपूर्णांक32_t index:16;

	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

जोड़ SQ_IND_CMD_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t data:32;
	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

जोड़ SQ_CMD_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t cmd:3;
		 uपूर्णांक32_t:1;
		uपूर्णांक32_t mode:3;
		uपूर्णांक32_t check_vmid:1;
		uपूर्णांक32_t trap_id:3;
		 uपूर्णांक32_t:5;
		uपूर्णांक32_t wave_id:4;
		uपूर्णांक32_t simd_id:2;
		 uपूर्णांक32_t:2;
		uपूर्णांक32_t queue_id:3;
		 uपूर्णांक32_t:1;
		uपूर्णांक32_t vm_id:4;
	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

जोड़ SQ_IND_DATA_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t data:32;
	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

जोड़ GRBM_GFX_INDEX_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t instance_index:8;
		uपूर्णांक32_t sh_index:8;
		uपूर्णांक32_t se_index:8;
		 uपूर्णांक32_t:5;
		uपूर्णांक32_t sh_broadcast_ग_लिखोs:1;
		uपूर्णांक32_t instance_broadcast_ग_लिखोs:1;
		uपूर्णांक32_t se_broadcast_ग_लिखोs:1;
	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

जोड़ TCP_WATCH_ADDR_H_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t addr:16;
		 uपूर्णांक32_t:16;

	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

जोड़ TCP_WATCH_ADDR_L_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t:6;
		uपूर्णांक32_t addr:26;
	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

क्रमागत अणु
	QUEUESTATE__INVALID = 0, /* so by शेष we'll get invalid state */
	QUEUESTATE__ACTIVE_COMPLETION_PENDING,
	QUEUESTATE__ACTIVE
पूर्ण;

जोड़ ULARGE_INTEGER अणु
	काष्ठा अणु
		uपूर्णांक32_t low_part;
		uपूर्णांक32_t high_part;
	पूर्ण u;
	अचिन्हित दीर्घ दीर्घ quad_part;
पूर्ण;


#घोषणा KFD_CIK_VMID_START_OFFSET (8)
#घोषणा KFD_CIK_VMID_END_OFFSET (KFD_CIK_VMID_START_OFFSET + (8))


व्योम kfd_dbgdev_init(काष्ठा kfd_dbgdev *pdbgdev, काष्ठा kfd_dev *pdev,
			क्रमागत DBGDEV_TYPE type);

जोड़ TCP_WATCH_CNTL_BITS अणु
	काष्ठा अणु
		uपूर्णांक32_t mask:24;
		uपूर्णांक32_t vmid:4;
		uपूर्णांक32_t atc:1;
		uपूर्णांक32_t mode:2;
		uपूर्णांक32_t valid:1;
	पूर्ण bitfields, bits;
	uपूर्णांक32_t u32All;
	चिन्हित पूर्णांक i32All;
	भग्न f32All;
पूर्ण;

क्रमागत अणु
	ADDRESS_WATCH_REG_CNTL_ATC_BIT = 0x10000000UL,
	ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK = 0x00FFFFFF,
	ADDRESS_WATCH_REG_ADDLOW_MASK_EXTENSION = 0x03000000,
	/* extend the mask to 26 bits in order to match the low address field */
	ADDRESS_WATCH_REG_ADDLOW_SHIFT = 6,
	ADDRESS_WATCH_REG_ADDHIGH_MASK = 0xFFFF
पूर्ण;

क्रमागत अणु
	MAX_TRAPID = 8,		/* 3 bits in the bitfield. */
	MAX_WATCH_ADDRESSES = 4
पूर्ण;

क्रमागत अणु
	ADDRESS_WATCH_REG_ADDR_HI = 0,
	ADDRESS_WATCH_REG_ADDR_LO,
	ADDRESS_WATCH_REG_CNTL,
	ADDRESS_WATCH_REG_MAX
पूर्ण;

#पूर्ण_अगर	/* KFD_DBGDEV_H_ */
