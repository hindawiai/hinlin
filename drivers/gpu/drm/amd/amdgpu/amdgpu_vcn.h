<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित __AMDGPU_VCN_H__
#घोषणा __AMDGPU_VCN_H__

#घोषणा AMDGPU_VCN_STACK_SIZE		(128*1024)
#घोषणा AMDGPU_VCN_CONTEXT_SIZE 	(512*1024)

#घोषणा AMDGPU_VCN_FIRMWARE_OFFSET	256
#घोषणा AMDGPU_VCN_MAX_ENC_RINGS	3

#घोषणा AMDGPU_MAX_VCN_INSTANCES	2
#घोषणा AMDGPU_MAX_VCN_ENC_RINGS  AMDGPU_VCN_MAX_ENC_RINGS * AMDGPU_MAX_VCN_INSTANCES

#घोषणा AMDGPU_VCN_HARVEST_VCN0 (1 << 0)
#घोषणा AMDGPU_VCN_HARVEST_VCN1 (1 << 1)

#घोषणा VCN_DEC_KMD_CMD 		0x80000000
#घोषणा VCN_DEC_CMD_FENCE		0x00000000
#घोषणा VCN_DEC_CMD_TRAP		0x00000001
#घोषणा VCN_DEC_CMD_WRITE_REG		0x00000004
#घोषणा VCN_DEC_CMD_REG_READ_COND_WAIT	0x00000006
#घोषणा VCN_DEC_CMD_PACKET_START	0x0000000a
#घोषणा VCN_DEC_CMD_PACKET_END		0x0000000b

#घोषणा VCN_DEC_SW_CMD_NO_OP		0x00000000
#घोषणा VCN_DEC_SW_CMD_END		0x00000001
#घोषणा VCN_DEC_SW_CMD_IB		0x00000002
#घोषणा VCN_DEC_SW_CMD_FENCE		0x00000003
#घोषणा VCN_DEC_SW_CMD_TRAP		0x00000004
#घोषणा VCN_DEC_SW_CMD_IB_AUTO		0x00000005
#घोषणा VCN_DEC_SW_CMD_SEMAPHORE	0x00000006
#घोषणा VCN_DEC_SW_CMD_PREEMPT_FENCE	0x00000009
#घोषणा VCN_DEC_SW_CMD_REG_WRITE	0x0000000b
#घोषणा VCN_DEC_SW_CMD_REG_WAIT		0x0000000c

#घोषणा VCN_ENC_CMD_NO_OP		0x00000000
#घोषणा VCN_ENC_CMD_END 		0x00000001
#घोषणा VCN_ENC_CMD_IB			0x00000002
#घोषणा VCN_ENC_CMD_FENCE		0x00000003
#घोषणा VCN_ENC_CMD_TRAP		0x00000004
#घोषणा VCN_ENC_CMD_REG_WRITE		0x0000000b
#घोषणा VCN_ENC_CMD_REG_WAIT		0x0000000c

#घोषणा VCN_VID_SOC_ADDRESS_2_0 	0x1fa00
#घोषणा VCN1_VID_SOC_ADDRESS_3_0 	0x48200
#घोषणा VCN_AON_SOC_ADDRESS_2_0 	0x1f800
#घोषणा VCN1_AON_SOC_ADDRESS_3_0 	0x48000
#घोषणा VCN_VID_IP_ADDRESS_2_0		0x0
#घोषणा VCN_AON_IP_ADDRESS_2_0		0x30000

#घोषणा mmUVD_RBC_XX_IB_REG_CHECK 					0x026b
#घोषणा mmUVD_RBC_XX_IB_REG_CHECK_BASE_IDX 				1
#घोषणा mmUVD_REG_XX_MASK 						0x026c
#घोषणा mmUVD_REG_XX_MASK_BASE_IDX 					1

/* 1 second समयout */
#घोषणा VCN_IDLE_TIMEOUT	msecs_to_jअगरfies(1000)

#घोषणा RREG32_SOC15_DPG_MODE_1_0(ip, inst_idx, reg, mask, sram_sel) 			\
	(अणु	WREG32_SOC15(ip, inst_idx, mmUVD_DPG_LMA_MASK, mask); 			\
		WREG32_SOC15(ip, inst_idx, mmUVD_DPG_LMA_CTL, 				\
			UVD_DPG_LMA_CTL__MASK_EN_MASK | 				\
			((adev->reg_offset[ip##_HWIP][inst_idx][reg##_BASE_IDX] + reg) 	\
			<< UVD_DPG_LMA_CTL__READ_WRITE_ADDR__SHIFT) | 			\
			(sram_sel << UVD_DPG_LMA_CTL__SRAM_SEL__SHIFT)); 		\
		RREG32_SOC15(ip, inst_idx, mmUVD_DPG_LMA_DATA); 			\
	पूर्ण)

#घोषणा WREG32_SOC15_DPG_MODE_1_0(ip, inst_idx, reg, value, mask, sram_sel) 		\
	करो अणु 										\
		WREG32_SOC15(ip, inst_idx, mmUVD_DPG_LMA_DATA, value); 			\
		WREG32_SOC15(ip, inst_idx, mmUVD_DPG_LMA_MASK, mask); 			\
		WREG32_SOC15(ip, inst_idx, mmUVD_DPG_LMA_CTL, 				\
			UVD_DPG_LMA_CTL__READ_WRITE_MASK | 				\
			((adev->reg_offset[ip##_HWIP][inst_idx][reg##_BASE_IDX] + reg) 	\
			<< UVD_DPG_LMA_CTL__READ_WRITE_ADDR__SHIFT) | 			\
			(sram_sel << UVD_DPG_LMA_CTL__SRAM_SEL__SHIFT)); 		\
	पूर्ण जबतक (0)

#घोषणा SOC15_DPG_MODE_OFFSET(ip, inst_idx, reg) 						\
	(अणु											\
		uपूर्णांक32_t पूर्णांकernal_reg_offset, addr;						\
		bool video_range, video1_range, aon_range, aon1_range;				\
												\
		addr = (adev->reg_offset[ip##_HWIP][inst_idx][reg##_BASE_IDX] + reg);		\
		addr <<= 2; 									\
		video_range = ((((0xFFFFF & addr) >= (VCN_VID_SOC_ADDRESS_2_0)) && 		\
				((0xFFFFF & addr) < ((VCN_VID_SOC_ADDRESS_2_0 + 0x2600)))));	\
		video1_range = ((((0xFFFFF & addr) >= (VCN1_VID_SOC_ADDRESS_3_0)) && 		\
				((0xFFFFF & addr) < ((VCN1_VID_SOC_ADDRESS_3_0 + 0x2600)))));	\
		aon_range   = ((((0xFFFFF & addr) >= (VCN_AON_SOC_ADDRESS_2_0)) && 		\
				((0xFFFFF & addr) < ((VCN_AON_SOC_ADDRESS_2_0 + 0x600)))));	\
		aon1_range   = ((((0xFFFFF & addr) >= (VCN1_AON_SOC_ADDRESS_3_0)) && 		\
				((0xFFFFF & addr) < ((VCN1_AON_SOC_ADDRESS_3_0 + 0x600)))));	\
		अगर (video_range) 								\
			पूर्णांकernal_reg_offset = ((0xFFFFF & addr) - (VCN_VID_SOC_ADDRESS_2_0) + 	\
				(VCN_VID_IP_ADDRESS_2_0));					\
		अन्यथा अगर (aon_range)								\
			पूर्णांकernal_reg_offset = ((0xFFFFF & addr) - (VCN_AON_SOC_ADDRESS_2_0) + 	\
				(VCN_AON_IP_ADDRESS_2_0));					\
		अन्यथा अगर (video1_range) 								\
			पूर्णांकernal_reg_offset = ((0xFFFFF & addr) - (VCN1_VID_SOC_ADDRESS_3_0) + 	\
				(VCN_VID_IP_ADDRESS_2_0));					\
		अन्यथा अगर (aon1_range)								\
			पूर्णांकernal_reg_offset = ((0xFFFFF & addr) - (VCN1_AON_SOC_ADDRESS_3_0) + 	\
				(VCN_AON_IP_ADDRESS_2_0));					\
		अन्यथा										\
			पूर्णांकernal_reg_offset = (0xFFFFF & addr);					\
												\
		पूर्णांकernal_reg_offset >>= 2;							\
	पूर्ण)

#घोषणा RREG32_SOC15_DPG_MODE(inst_idx, offset, mask_en) 					\
	(अणु											\
		WREG32_SOC15(VCN, inst_idx, mmUVD_DPG_LMA_CTL, 					\
			(0x0 << UVD_DPG_LMA_CTL__READ_WRITE__SHIFT |				\
			mask_en << UVD_DPG_LMA_CTL__MASK_EN__SHIFT |				\
			offset << UVD_DPG_LMA_CTL__READ_WRITE_ADDR__SHIFT));			\
		RREG32_SOC15(VCN, inst_idx, mmUVD_DPG_LMA_DATA);				\
	पूर्ण)

#घोषणा WREG32_SOC15_DPG_MODE(inst_idx, offset, value, mask_en, indirect)			\
	करो अणु											\
		अगर (!indirect) अणु								\
			WREG32_SOC15(VCN, inst_idx, mmUVD_DPG_LMA_DATA, value);			\
			WREG32_SOC15(VCN, inst_idx, mmUVD_DPG_LMA_CTL, 				\
				(0x1 << UVD_DPG_LMA_CTL__READ_WRITE__SHIFT |			\
				 mask_en << UVD_DPG_LMA_CTL__MASK_EN__SHIFT |			\
				 offset << UVD_DPG_LMA_CTL__READ_WRITE_ADDR__SHIFT));		\
		पूर्ण अन्यथा अणु									\
			*adev->vcn.inst[inst_idx].dpg_sram_curr_addr++ = offset;		\
			*adev->vcn.inst[inst_idx].dpg_sram_curr_addr++ = value;			\
		पूर्ण										\
	पूर्ण जबतक (0)

#घोषणा AMDGPU_VCN_FW_SHARED_FLAG_0_RB	(1 << 6)
#घोषणा AMDGPU_VCN_MULTI_QUEUE_FLAG	(1 << 8)
#घोषणा AMDGPU_VCN_SW_RING_FLAG		(1 << 9)

#घोषणा AMDGPU_VCN_IB_FLAG_DECODE_BUFFER	0x00000001
#घोषणा AMDGPU_VCN_CMD_FLAG_MSG_BUFFER		0x00000001

क्रमागत fw_queue_mode अणु
	FW_QUEUE_RING_RESET = 1,
	FW_QUEUE_DPG_HOLD_OFF = 2,
पूर्ण;

क्रमागत engine_status_स्थिरants अणु
	UVD_PGFSM_STATUS__UVDM_UVDU_PWR_ON = 0x2AAAA0,
	UVD_PGFSM_STATUS__UVDM_UVDU_PWR_ON_2_0 = 0xAAAA0,
	UVD_PGFSM_STATUS__UVDM_UVDU_UVDLM_PWR_ON_3_0 = 0x2A2A8AA0,
	UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON = 0x00000002,
	UVD_STATUS__UVD_BUSY = 0x00000004,
	GB_ADDR_CONFIG_DEFAULT = 0x26010011,
	UVD_STATUS__IDLE = 0x2,
	UVD_STATUS__BUSY = 0x5,
	UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF = 0x1,
	UVD_STATUS__RBC_BUSY = 0x1,
	UVD_PGFSM_STATUS_UVDJ_PWR_ON = 0,
पूर्ण;

क्रमागत पूर्णांकernal_dpg_state अणु
	VCN_DPG_STATE__UNPAUSE = 0,
	VCN_DPG_STATE__PAUSE,
पूर्ण;

काष्ठा dpg_छोड़ो_state अणु
	क्रमागत पूर्णांकernal_dpg_state fw_based;
	क्रमागत पूर्णांकernal_dpg_state jpeg;
पूर्ण;

काष्ठा amdgpu_vcn_regअणु
	अचिन्हित	data0;
	अचिन्हित	data1;
	अचिन्हित	cmd;
	अचिन्हित	nop;
	अचिन्हित	context_id;
	अचिन्हित	ib_vmid;
	अचिन्हित	ib_bar_low;
	अचिन्हित	ib_bar_high;
	अचिन्हित	ib_size;
	अचिन्हित	gp_scratch8;
	अचिन्हित	scratch9;
पूर्ण;

काष्ठा amdgpu_vcn_inst अणु
	काष्ठा amdgpu_bo	*vcpu_bo;
	व्योम			*cpu_addr;
	uपूर्णांक64_t		gpu_addr;
	व्योम			*saved_bo;
	काष्ठा amdgpu_ring	ring_dec;
	काष्ठा amdgpu_ring	ring_enc[AMDGPU_VCN_MAX_ENC_RINGS];
	atomic_t		sched_score;
	काष्ठा amdgpu_irq_src	irq;
	काष्ठा amdgpu_vcn_reg	बाह्यal;
	काष्ठा amdgpu_bo	*dpg_sram_bo;
	काष्ठा dpg_छोड़ो_state	छोड़ो_state;
	व्योम			*dpg_sram_cpu_addr;
	uपूर्णांक64_t		dpg_sram_gpu_addr;
	uपूर्णांक32_t		*dpg_sram_curr_addr;
	atomic_t		dpg_enc_submission_cnt;
	व्योम			*fw_shared_cpu_addr;
	uपूर्णांक64_t		fw_shared_gpu_addr;
पूर्ण;

काष्ठा amdgpu_vcn अणु
	अचिन्हित		fw_version;
	काष्ठा delayed_work	idle_work;
	स्थिर काष्ठा firmware	*fw;	/* VCN firmware */
	अचिन्हित		num_enc_rings;
	क्रमागत amd_घातergating_state cur_state;
	bool			indirect_sram;

	uपूर्णांक8_t	num_vcn_inst;
	काष्ठा amdgpu_vcn_inst	 inst[AMDGPU_MAX_VCN_INSTANCES];
	काष्ठा amdgpu_vcn_reg	 पूर्णांकernal;
	काष्ठा mutex		 vcn_pg_lock;
	काष्ठा mutex		vcn1_jpeg1_workaround;
	atomic_t		 total_submission_cnt;

	अचिन्हित	harvest_config;
	पूर्णांक (*छोड़ो_dpg_mode)(काष्ठा amdgpu_device *adev,
		पूर्णांक inst_idx, काष्ठा dpg_छोड़ो_state *new_state);
पूर्ण;

काष्ठा amdgpu_fw_shared_rb_ptrs_काष्ठा अणु
	/* to WA DPG R/W ptr issues.*/
	uपूर्णांक32_t  rptr;
	uपूर्णांक32_t  wptr;
पूर्ण;

काष्ठा amdgpu_fw_shared_multi_queue अणु
	uपूर्णांक8_t decode_queue_mode;
	uपूर्णांक8_t encode_generalpurpose_queue_mode;
	uपूर्णांक8_t encode_lowlatency_queue_mode;
	uपूर्णांक8_t encode_realसमय_queue_mode;
	uपूर्णांक8_t padding[4];
पूर्ण;

काष्ठा amdgpu_fw_shared_sw_ring अणु
	uपूर्णांक8_t is_enabled;
	uपूर्णांक8_t padding[3];
पूर्ण;

काष्ठा amdgpu_fw_shared अणु
	uपूर्णांक32_t present_flag_0;
	uपूर्णांक8_t pad[44];
	काष्ठा amdgpu_fw_shared_rb_ptrs_काष्ठा rb;
	uपूर्णांक8_t pad1[1];
	काष्ठा amdgpu_fw_shared_multi_queue multi_queue;
	काष्ठा amdgpu_fw_shared_sw_ring sw_ring;
पूर्ण;

काष्ठा amdgpu_vcn_decode_buffer अणु
	uपूर्णांक32_t valid_buf_flag;
	uपूर्णांक32_t msg_buffer_address_hi;
	uपूर्णांक32_t msg_buffer_address_lo;
	uपूर्णांक32_t pad[30];
पूर्ण;

पूर्णांक amdgpu_vcn_sw_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_vcn_sw_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_vcn_suspend(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_vcn_resume(काष्ठा amdgpu_device *adev);
व्योम amdgpu_vcn_ring_begin_use(काष्ठा amdgpu_ring *ring);
व्योम amdgpu_vcn_ring_end_use(काष्ठा amdgpu_ring *ring);

पूर्णांक amdgpu_vcn_dec_ring_test_ring(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_vcn_dec_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout);
पूर्णांक amdgpu_vcn_dec_sw_ring_test_ring(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_vcn_dec_sw_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout);

पूर्णांक amdgpu_vcn_enc_ring_test_ring(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_vcn_enc_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout);

#पूर्ण_अगर
