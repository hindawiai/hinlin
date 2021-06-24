<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */


#अगर_अघोषित _DCE_DMCU_H_
#घोषणा _DCE_DMCU_H_

#समावेश "dmcu.h"

#घोषणा DMCU_COMMON_REG_LIST_DCE_BASE() \
	SR(DMCU_CTRL), \
	SR(DMCU_STATUS), \
	SR(DMCU_RAM_ACCESS_CTRL), \
	SR(DMCU_IRAM_WR_CTRL), \
	SR(DMCU_IRAM_WR_DATA), \
	SR(MASTER_COMM_DATA_REG1), \
	SR(MASTER_COMM_DATA_REG2), \
	SR(MASTER_COMM_DATA_REG3), \
	SR(MASTER_COMM_CMD_REG), \
	SR(MASTER_COMM_CNTL_REG), \
	SR(SLAVE_COMM_DATA_REG1), \
	SR(SLAVE_COMM_DATA_REG2), \
	SR(SLAVE_COMM_DATA_REG3), \
	SR(SLAVE_COMM_CMD_REG), \
	SR(DMCU_IRAM_RD_CTRL), \
	SR(DMCU_IRAM_RD_DATA), \
	SR(DMCU_INTERRUPT_TO_UC_EN_MASK), \
	SR(SMU_INTERRUPT_CONTROL), \
	SR(DC_DMCU_SCRATCH)

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा DMCU_DCE60_REG_LIST() \
	SR(DMCU_CTRL), \
	SR(DMCU_STATUS), \
	SR(DMCU_RAM_ACCESS_CTRL), \
	SR(DMCU_IRAM_WR_CTRL), \
	SR(DMCU_IRAM_WR_DATA), \
	SR(MASTER_COMM_DATA_REG1), \
	SR(MASTER_COMM_DATA_REG2), \
	SR(MASTER_COMM_DATA_REG3), \
	SR(MASTER_COMM_CMD_REG), \
	SR(MASTER_COMM_CNTL_REG), \
	SR(DMCU_IRAM_RD_CTRL), \
	SR(DMCU_IRAM_RD_DATA), \
	SR(DMCU_INTERRUPT_TO_UC_EN_MASK), \
	SR(DC_DMCU_SCRATCH)
#पूर्ण_अगर

#घोषणा DMCU_DCE80_REG_LIST() \
	SR(DMCU_CTRL), \
	SR(DMCU_STATUS), \
	SR(DMCU_RAM_ACCESS_CTRL), \
	SR(DMCU_IRAM_WR_CTRL), \
	SR(DMCU_IRAM_WR_DATA), \
	SR(MASTER_COMM_DATA_REG1), \
	SR(MASTER_COMM_DATA_REG2), \
	SR(MASTER_COMM_DATA_REG3), \
	SR(MASTER_COMM_CMD_REG), \
	SR(MASTER_COMM_CNTL_REG), \
	SR(DMCU_IRAM_RD_CTRL), \
	SR(DMCU_IRAM_RD_DATA), \
	SR(DMCU_INTERRUPT_TO_UC_EN_MASK), \
	SR(SMU_INTERRUPT_CONTROL), \
	SR(DC_DMCU_SCRATCH)

#घोषणा DMCU_DCE110_COMMON_REG_LIST() \
	DMCU_COMMON_REG_LIST_DCE_BASE(), \
	SR(DCI_MEM_PWR_STATUS)

#घोषणा DMCU_DCN10_REG_LIST()\
	DMCU_COMMON_REG_LIST_DCE_BASE(), \
	SR(DMU_MEM_PWR_CNTL)

#घोषणा DMCU_DCN20_REG_LIST()\
	DMCU_DCN10_REG_LIST(), \
	SR(DMCUB_SCRATCH15)

#घोषणा DMCU_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा DMCU_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(mask_sh) \
	DMCU_SF(DMCU_CTRL, \
			DMCU_ENABLE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_STOP_MODE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_RESET, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_HOST_ACCESS_EN, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_WR_ADDR_AUTO_INC, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_RD_ADDR_AUTO_INC, mask_sh), \
	DMCU_SF(MASTER_COMM_CMD_REG, \
			MASTER_COMM_CMD_REG_BYTE0, mask_sh), \
	DMCU_SF(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, mask_sh), \
	DMCU_SF(SLAVE_COMM_CNTL_REG, SLAVE_COMM_INTERRUPT, mask_sh), \
	DMCU_SF(DMCU_INTERRUPT_TO_UC_EN_MASK, \
			STATIC_SCREEN1_INT_TO_UC_EN, mask_sh), \
	DMCU_SF(DMCU_INTERRUPT_TO_UC_EN_MASK, \
			STATIC_SCREEN2_INT_TO_UC_EN, mask_sh), \
	DMCU_SF(DMCU_INTERRUPT_TO_UC_EN_MASK, \
			STATIC_SCREEN3_INT_TO_UC_EN, mask_sh), \
	DMCU_SF(DMCU_INTERRUPT_TO_UC_EN_MASK, \
			STATIC_SCREEN4_INT_TO_UC_EN, mask_sh), \
	DMCU_SF(SMU_INTERRUPT_CONTROL, DC_SMU_INT_ENABLE, mask_sh)

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा DMCU_MASK_SH_LIST_DCE60(mask_sh) \
	DMCU_SF(DMCU_CTRL, \
			DMCU_ENABLE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_STOP_MODE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_RESET, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_HOST_ACCESS_EN, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_WR_ADDR_AUTO_INC, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_RD_ADDR_AUTO_INC, mask_sh), \
	DMCU_SF(MASTER_COMM_CMD_REG, \
			MASTER_COMM_CMD_REG_BYTE0, mask_sh), \
	DMCU_SF(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, mask_sh)
#पूर्ण_अगर

#घोषणा DMCU_MASK_SH_LIST_DCE80(mask_sh) \
	DMCU_SF(DMCU_CTRL, \
			DMCU_ENABLE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_STOP_MODE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_RESET, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_HOST_ACCESS_EN, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_WR_ADDR_AUTO_INC, mask_sh), \
	DMCU_SF(DMCU_RAM_ACCESS_CTRL, \
			IRAM_RD_ADDR_AUTO_INC, mask_sh), \
	DMCU_SF(MASTER_COMM_CMD_REG, \
			MASTER_COMM_CMD_REG_BYTE0, mask_sh), \
	DMCU_SF(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, mask_sh), \
	DMCU_SF(SMU_INTERRUPT_CONTROL, DC_SMU_INT_ENABLE, mask_sh)

#घोषणा DMCU_MASK_SH_LIST_DCE110(mask_sh) \
	DMCU_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(mask_sh), \
	DMCU_SF(DCI_MEM_PWR_STATUS, \
		DMCU_IRAM_MEM_PWR_STATE, mask_sh)

#घोषणा DMCU_MASK_SH_LIST_DCN10(mask_sh) \
	DMCU_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(mask_sh), \
	DMCU_SF(DMU_MEM_PWR_CNTL, \
			DMCU_IRAM_MEM_PWR_STATE, mask_sh)

#घोषणा DMCU_REG_FIELD_LIST(type) \
	type DMCU_IRAM_MEM_PWR_STATE; \
	type IRAM_HOST_ACCESS_EN; \
	type IRAM_WR_ADDR_AUTO_INC; \
	type IRAM_RD_ADDR_AUTO_INC; \
	type DMCU_ENABLE; \
	type UC_IN_STOP_MODE; \
	type UC_IN_RESET; \
	type MASTER_COMM_CMD_REG_BYTE0; \
	type MASTER_COMM_INTERRUPT; \
	type SLAVE_COMM_INTERRUPT; \
	type DPHY_RX_FAST_TRAINING_CAPABLE; \
	type DPHY_LOAD_BS_COUNT; \
	type STATIC_SCREEN1_INT_TO_UC_EN; \
	type STATIC_SCREEN2_INT_TO_UC_EN; \
	type STATIC_SCREEN3_INT_TO_UC_EN; \
	type STATIC_SCREEN4_INT_TO_UC_EN; \
	type DP_SEC_GSP0_LINE_NUM; \
	type DP_SEC_GSP0_PRIORITY; \
	type DC_SMU_INT_ENABLE

काष्ठा dce_dmcu_shअगरt अणु
	DMCU_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dce_dmcu_mask अणु
	DMCU_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dce_dmcu_रेजिस्टरs अणु
	uपूर्णांक32_t DMCU_CTRL;
	uपूर्णांक32_t DMCU_STATUS;
	uपूर्णांक32_t DMCU_RAM_ACCESS_CTRL;
	uपूर्णांक32_t DCI_MEM_PWR_STATUS;
	uपूर्णांक32_t DMU_MEM_PWR_CNTL;
	uपूर्णांक32_t DMCU_IRAM_WR_CTRL;
	uपूर्णांक32_t DMCU_IRAM_WR_DATA;

	uपूर्णांक32_t MASTER_COMM_DATA_REG1;
	uपूर्णांक32_t MASTER_COMM_DATA_REG2;
	uपूर्णांक32_t MASTER_COMM_DATA_REG3;
	uपूर्णांक32_t MASTER_COMM_CMD_REG;
	uपूर्णांक32_t MASTER_COMM_CNTL_REG;
	uपूर्णांक32_t SLAVE_COMM_DATA_REG1;
	uपूर्णांक32_t SLAVE_COMM_DATA_REG2;
	uपूर्णांक32_t SLAVE_COMM_DATA_REG3;
	uपूर्णांक32_t SLAVE_COMM_CMD_REG;
	uपूर्णांक32_t SLAVE_COMM_CNTL_REG;
	uपूर्णांक32_t DMCU_IRAM_RD_CTRL;
	uपूर्णांक32_t DMCU_IRAM_RD_DATA;
	uपूर्णांक32_t DMCU_INTERRUPT_TO_UC_EN_MASK;
	uपूर्णांक32_t SMU_INTERRUPT_CONTROL;
	uपूर्णांक32_t DC_DMCU_SCRATCH;
	uपूर्णांक32_t DMCUB_SCRATCH15;
पूर्ण;

काष्ठा dce_dmcu अणु
	काष्ठा dmcu base;
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs;
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt;
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask;
पूर्ण;

/*******************************************************************
 *   MASTER_COMM_DATA_REG1   Bit position    Data
 *                           7:0	            hyst_frames[7:0]
 *                           14:8	        hyst_lines[6:0]
 *                           15	            RFB_UPDATE_AUTO_EN
 *                           18:16	        phy_num[2:0]
 *                           21:19	        dcp_sel[2:0]
 *                           22	            phy_type
 *                           23	            frame_cap_ind
 *                           26:24	        aux_chan[2:0]
 *                           30:27	        aux_repeat[3:0]
 *                           31:31	        reserved[31:31]
 ******************************************************************/
जोड़ dce_dmcu_psr_config_data_reg1 अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक समयhyst_frames:8;                  /*[7:0]*/
		अचिन्हित पूर्णांक hyst_lines:7;                       /*[14:8]*/
		अचिन्हित पूर्णांक rfb_update_स्वतः_en:1;               /*[15:15]*/
		अचिन्हित पूर्णांक dp_port_num:3;                      /*[18:16]*/
		अचिन्हित पूर्णांक dcp_sel:3;                          /*[21:19]*/
		अचिन्हित पूर्णांक phy_type:1;                         /*[22:22]*/
		अचिन्हित पूर्णांक frame_cap_ind:1;                    /*[23:23]*/
		अचिन्हित पूर्णांक aux_chan:3;                         /*[26:24]*/
		अचिन्हित पूर्णांक aux_repeat:4;                       /*[30:27]*/
		अचिन्हित पूर्णांक allow_smu_optimizations:1;         /*[31:31]*/
	पूर्ण bits;
	अचिन्हित पूर्णांक u32All;
पूर्ण;

/*******************************************************************
 *   MASTER_COMM_DATA_REG2
 *******************************************************************/
जोड़ dce_dmcu_psr_config_data_reg2 अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक dig_fe:3;                  /*[2:0]*/
		अचिन्हित पूर्णांक dig_be:3;                  /*[5:3]*/
		अचिन्हित पूर्णांक skip_रुको_क्रम_pll_lock:1;  /*[6:6]*/
		अचिन्हित पूर्णांक reserved:9;                /*[15:7]*/
		अचिन्हित पूर्णांक frame_delay:8;             /*[23:16]*/
		अचिन्हित पूर्णांक smu_phy_id:4;              /*[27:24]*/
		अचिन्हित पूर्णांक num_of_controllers:4;      /*[31:28]*/
	पूर्ण bits;
	अचिन्हित पूर्णांक u32All;
पूर्ण;

/*******************************************************************
 *   MASTER_COMM_DATA_REG3
 *******************************************************************/
जोड़ dce_dmcu_psr_config_data_reg3 अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक psr_level:16;      /*[15:0]*/
		अचिन्हित पूर्णांक link_rate:4;       /*[19:16]*/
		अचिन्हित पूर्णांक reserved:12;        /*[31:20]*/
	पूर्ण bits;
	अचिन्हित पूर्णांक u32All;
पूर्ण;

जोड़ dce_dmcu_psr_config_data_रुको_loop_reg1 अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक रुको_loop:16; /* [15:0] */
		अचिन्हित पूर्णांक reserved:16; /* [31:16] */
	पूर्ण bits;
	अचिन्हित पूर्णांक u32;
पूर्ण;

काष्ठा dmcu *dce_dmcu_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask);

काष्ठा dmcu *dcn10_dmcu_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask);

काष्ठा dmcu *dcn20_dmcu_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask);

काष्ठा dmcu *dcn21_dmcu_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask);

व्योम dce_dmcu_destroy(काष्ठा dmcu **dmcu);

#पूर्ण_अगर /* _DCE_ABM_H_ */
