<शैली गुरु>
/* bnx2x_init.h: Qlogic Everest network driver.
 *               Structures and macroes needed during the initialization.
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
 * Written by: Eliezer Tamir
 * Modअगरied by: Vladislav Zolotarov
 */

#अगर_अघोषित BNX2X_INIT_H
#घोषणा BNX2X_INIT_H

/* Init operation types and काष्ठाures */
क्रमागत अणु
	OP_RD = 0x1,	/* पढ़ो a single रेजिस्टर */
	OP_WR,		/* ग_लिखो a single रेजिस्टर */
	OP_SW,		/* copy a string to the device */
	OP_ZR,		/* clear memory */
	OP_ZP,		/* unzip then copy with DMAE */
	OP_WR_64,	/* ग_लिखो 64 bit pattern */
	OP_WB,		/* copy a string using DMAE */
	OP_WB_ZR,	/* Clear a string using DMAE or indirect-wr */
	/* Skip the following ops अगर all of the init modes करोn't match */
	OP_IF_MODE_OR,
	/* Skip the following ops अगर any of the init modes करोn't match */
	OP_IF_MODE_AND,
	OP_MAX
पूर्ण;

क्रमागत अणु
	STAGE_START,
	STAGE_END,
पूर्ण;

/* Returns the index of start or end of a specअगरic block stage in ops array*/
#घोषणा BLOCK_OPS_IDX(block, stage, end) \
	(2*(((block)*NUM_OF_INIT_PHASES) + (stage)) + (end))


/* काष्ठाs क्रम the various opcodes */
काष्ठा raw_op अणु
	u32 op:8;
	u32 offset:24;
	u32 raw_data;
पूर्ण;

काष्ठा op_पढ़ो अणु
	u32 op:8;
	u32 offset:24;
	u32 val;
पूर्ण;

काष्ठा op_ग_लिखो अणु
	u32 op:8;
	u32 offset:24;
	u32 val;
पूर्ण;

काष्ठा op_arr_ग_लिखो अणु
	u32 op:8;
	u32 offset:24;
#अगर_घोषित __BIG_ENDIAN
	u16 data_len;
	u16 data_off;
#अन्यथा /* __LITTLE_ENDIAN */
	u16 data_off;
	u16 data_len;
#पूर्ण_अगर
पूर्ण;

काष्ठा op_zero अणु
	u32 op:8;
	u32 offset:24;
	u32 len;
पूर्ण;

काष्ठा op_अगर_mode अणु
	u32 op:8;
	u32 cmd_offset:24;
	u32 mode_bit_map;
पूर्ण;


जोड़ init_op अणु
	काष्ठा op_पढ़ो		पढ़ो;
	काष्ठा op_ग_लिखो		ग_लिखो;
	काष्ठा op_arr_ग_लिखो	arr_wr;
	काष्ठा op_zero		zero;
	काष्ठा raw_op		raw;
	काष्ठा op_अगर_mode	अगर_mode;
पूर्ण;


/* Init Phases */
क्रमागत अणु
	PHASE_COMMON,
	PHASE_PORT0,
	PHASE_PORT1,
	PHASE_PF0,
	PHASE_PF1,
	PHASE_PF2,
	PHASE_PF3,
	PHASE_PF4,
	PHASE_PF5,
	PHASE_PF6,
	PHASE_PF7,
	NUM_OF_INIT_PHASES
पूर्ण;

/* Init Modes */
क्रमागत अणु
	MODE_ASIC                      = 0x00000001,
	MODE_FPGA                      = 0x00000002,
	MODE_EMUL                      = 0x00000004,
	MODE_E2                        = 0x00000008,
	MODE_E3                        = 0x00000010,
	MODE_PORT2                     = 0x00000020,
	MODE_PORT4                     = 0x00000040,
	MODE_SF                        = 0x00000080,
	MODE_MF                        = 0x00000100,
	MODE_MF_SD                     = 0x00000200,
	MODE_MF_SI                     = 0x00000400,
	MODE_MF_AFEX                   = 0x00000800,
	MODE_E3_A0                     = 0x00001000,
	MODE_E3_B0                     = 0x00002000,
	MODE_COS3                      = 0x00004000,
	MODE_COS6                      = 0x00008000,
	MODE_LITTLE_ENDIAN             = 0x00010000,
	MODE_BIG_ENDIAN                = 0x00020000,
पूर्ण;

/* Init Blocks */
क्रमागत अणु
	BLOCK_ATC,
	BLOCK_BRB1,
	BLOCK_CCM,
	BLOCK_CDU,
	BLOCK_CFC,
	BLOCK_CSDM,
	BLOCK_CSEM,
	BLOCK_DBG,
	BLOCK_DMAE,
	BLOCK_DORQ,
	BLOCK_HC,
	BLOCK_IGU,
	BLOCK_MISC,
	BLOCK_NIG,
	BLOCK_PBF,
	BLOCK_PGLUE_B,
	BLOCK_PRS,
	BLOCK_PXP2,
	BLOCK_PXP,
	BLOCK_QM,
	BLOCK_SRC,
	BLOCK_TCM,
	BLOCK_TM,
	BLOCK_TSDM,
	BLOCK_TSEM,
	BLOCK_UCM,
	BLOCK_UPB,
	BLOCK_USDM,
	BLOCK_USEM,
	BLOCK_XCM,
	BLOCK_XPB,
	BLOCK_XSDM,
	BLOCK_XSEM,
	BLOCK_MISC_AEU,
	NUM_OF_INIT_BLOCKS
पूर्ण;

/* QM queue numbers */
#घोषणा BNX2X_ETH_Q		0
#घोषणा BNX2X_TOE_Q		3
#घोषणा BNX2X_TOE_ACK_Q		6
#घोषणा BNX2X_ISCSI_Q		9
#घोषणा BNX2X_ISCSI_ACK_Q	11
#घोषणा BNX2X_FCOE_Q		10

/* Vnics per mode */
#घोषणा BNX2X_PORT2_MODE_NUM_VNICS 4
#घोषणा BNX2X_PORT4_MODE_NUM_VNICS 2

/* COS offset क्रम port1 in E3 B0 4port mode */
#घोषणा BNX2X_E3B0_PORT1_COS_OFFSET 3

/* QM Register addresses */
#घोषणा BNX2X_Q_VOQ_REG_ADDR(pf_q_num)\
	(QM_REG_QVOQIDX_0 + 4 * (pf_q_num))
#घोषणा BNX2X_VOQ_Q_REG_ADDR(cos, pf_q_num)\
	(QM_REG_VOQQMASK_0_LSB + 4 * ((cos) * 2 + ((pf_q_num) >> 5)))
#घोषणा BNX2X_Q_CMDQ_REG_ADDR(pf_q_num)\
	(QM_REG_BYTECRDCMDQ_0 + 4 * ((pf_q_num) >> 4))

/* extracts the QM queue number क्रम the specअगरied port and vnic */
#घोषणा BNX2X_PF_Q_NUM(q_num, port, vnic)\
	((((port) << 1) | (vnic)) * 16 + (q_num))


/* Maps the specअगरied queue to the specअगरied COS */
अटल अंतरभूत व्योम bnx2x_map_q_cos(काष्ठा bnx2x *bp, u32 q_num, u32 new_cos)
अणु
	/* find current COS mapping */
	u32 curr_cos = REG_RD(bp, QM_REG_QVOQIDX_0 + q_num * 4);

	/* check अगर queue->COS mapping has changed */
	अगर (curr_cos != new_cos) अणु
		u32 num_vnics = BNX2X_PORT2_MODE_NUM_VNICS;
		u32 reg_addr, reg_bit_map, vnic;

		/* update parameters क्रम 4port mode */
		अगर (INIT_MODE_FLAGS(bp) & MODE_PORT4) अणु
			num_vnics = BNX2X_PORT4_MODE_NUM_VNICS;
			अगर (BP_PORT(bp)) अणु
				curr_cos += BNX2X_E3B0_PORT1_COS_OFFSET;
				new_cos += BNX2X_E3B0_PORT1_COS_OFFSET;
			पूर्ण
		पूर्ण

		/* change queue mapping क्रम each VNIC */
		क्रम (vnic = 0; vnic < num_vnics; vnic++) अणु
			u32 pf_q_num =
				BNX2X_PF_Q_NUM(q_num, BP_PORT(bp), vnic);
			u32 q_bit_map = 1 << (pf_q_num & 0x1f);

			/* overग_लिखो queue->VOQ mapping */
			REG_WR(bp, BNX2X_Q_VOQ_REG_ADDR(pf_q_num), new_cos);

			/* clear queue bit from current COS bit map */
			reg_addr = BNX2X_VOQ_Q_REG_ADDR(curr_cos, pf_q_num);
			reg_bit_map = REG_RD(bp, reg_addr);
			REG_WR(bp, reg_addr, reg_bit_map & (~q_bit_map));

			/* set queue bit in new COS bit map */
			reg_addr = BNX2X_VOQ_Q_REG_ADDR(new_cos, pf_q_num);
			reg_bit_map = REG_RD(bp, reg_addr);
			REG_WR(bp, reg_addr, reg_bit_map | q_bit_map);

			/* set/clear queue bit in command-queue bit map
			 * (E2/E3A0 only, valid COS values are 0/1)
			 */
			अगर (!(INIT_MODE_FLAGS(bp) & MODE_E3_B0)) अणु
				reg_addr = BNX2X_Q_CMDQ_REG_ADDR(pf_q_num);
				reg_bit_map = REG_RD(bp, reg_addr);
				q_bit_map = 1 << (2 * (pf_q_num & 0xf));
				reg_bit_map = new_cos ?
					      (reg_bit_map | q_bit_map) :
					      (reg_bit_map & (~q_bit_map));
				REG_WR(bp, reg_addr, reg_bit_map);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Configures the QM according to the specअगरied per-traffic-type COSes */
अटल अंतरभूत व्योम bnx2x_dcb_config_qm(काष्ठा bnx2x *bp, क्रमागत cos_mode mode,
				       काष्ठा priority_cos *traffic_cos)
अणु
	bnx2x_map_q_cos(bp, BNX2X_FCOE_Q,
			traffic_cos[LLFC_TRAFFIC_TYPE_FCOE].cos);
	bnx2x_map_q_cos(bp, BNX2X_ISCSI_Q,
			traffic_cos[LLFC_TRAFFIC_TYPE_ISCSI].cos);
	bnx2x_map_q_cos(bp, BNX2X_ISCSI_ACK_Q,
		traffic_cos[LLFC_TRAFFIC_TYPE_ISCSI].cos);
	अगर (mode != STATIC_COS) अणु
		/* required only in backward compatible COS mode */
		bnx2x_map_q_cos(bp, BNX2X_ETH_Q,
				traffic_cos[LLFC_TRAFFIC_TYPE_NW].cos);
		bnx2x_map_q_cos(bp, BNX2X_TOE_Q,
				traffic_cos[LLFC_TRAFFIC_TYPE_NW].cos);
		bnx2x_map_q_cos(bp, BNX2X_TOE_ACK_Q,
				traffic_cos[LLFC_TRAFFIC_TYPE_NW].cos);
	पूर्ण
पूर्ण


/* congestion management port init api description
 * the api works as follows:
 * the driver should pass the cmng_init_input काष्ठा, the port_init function
 * will prepare the required पूर्णांकernal ram काष्ठाure which will be passed back
 * to the driver (cmng_init) that will ग_लिखो it पूर्णांकo the पूर्णांकernal ram.
 *
 * IMPORTANT REMARKS:
 * 1. the cmng_init काष्ठा करोes not represent the contiguous पूर्णांकernal ram
 *    काष्ठाure. the driver should use the XSTORM_CMNG_PERPORT_VARS_OFFSET
 *    offset in order to ग_लिखो the port sub काष्ठा and the
 *    PFID_FROM_PORT_AND_VNIC offset क्रम writing the vnic sub काष्ठा (in other
 *    words - करोn't use स_नकल!).
 * 2. although the cmng_init काष्ठा is filled क्रम the maximal vnic number
 *    possible, the driver should only ग_लिखो the valid vnics पूर्णांकo the पूर्णांकernal
 *    ram according to the appropriate port mode.
 */

/* CMNG स्थिरants, as derived from प्रणाली spec calculations */

/* शेष MIN rate in हाल VNIC min rate is configured to zero- 100Mbps */
#घोषणा DEF_MIN_RATE 100

/* resolution of the rate shaping समयr - 400 usec */
#घोषणा RS_PERIODIC_TIMEOUT_USEC 400

/* number of bytes in single QM arbitration cycle -
 * coefficient क्रम calculating the fairness समयr
 */
#घोषणा QM_ARB_BYTES 160000

/* resolution of Min algorithm 1:100 */
#घोषणा MIN_RES 100

/* how many bytes above threshold क्रम
 * the minimal credit of Min algorithm
 */
#घोषणा MIN_ABOVE_THRESH 32768

/* Fairness algorithm पूर्णांकegration समय coefficient -
 * क्रम calculating the actual Tfair
 */
#घोषणा T_FAIR_COEF ((MIN_ABOVE_THRESH + QM_ARB_BYTES) * 8 * MIN_RES)

/* Memory of fairness algorithm - 2 cycles */
#घोषणा FAIR_MEM 2
#घोषणा SAFC_TIMEOUT_USEC 52

#घोषणा SDM_TICKS 4


अटल अंतरभूत व्योम bnx2x_init_max(स्थिर काष्ठा cmng_init_input *input_data,
				  u32 r_param, काष्ठा cmng_init *ram_data)
अणु
	u32 vnic;
	काष्ठा cmng_vnic *vdata = &ram_data->vnic;
	काष्ठा cmng_काष्ठा_per_port *pdata = &ram_data->port;
	/* rate shaping per-port variables
	 * 100 micro seconds in SDM ticks = 25
	 * since each tick is 4 microSeconds
	 */

	pdata->rs_vars.rs_periodic_समयout =
	RS_PERIODIC_TIMEOUT_USEC / SDM_TICKS;

	/* this is the threshold below which no समयr arming will occur.
	 * 1.25 coefficient is क्रम the threshold to be a little bigger
	 * then the real समय to compensate क्रम समयr in-accuracy
	 */
	pdata->rs_vars.rs_threshold =
	(5 * RS_PERIODIC_TIMEOUT_USEC * r_param)/4;

	/* rate shaping per-vnic variables */
	क्रम (vnic = 0; vnic < BNX2X_PORT2_MODE_NUM_VNICS; vnic++) अणु
		/* global vnic counter */
		vdata->vnic_max_rate[vnic].vn_counter.rate =
		input_data->vnic_max_rate[vnic];
		/* maximal Mbps क्रम this vnic
		 * the quota in each समयr period - number of bytes
		 * transmitted in this period
		 */
		vdata->vnic_max_rate[vnic].vn_counter.quota =
			RS_PERIODIC_TIMEOUT_USEC *
			(u32)vdata->vnic_max_rate[vnic].vn_counter.rate / 8;
	पूर्ण

पूर्ण

अटल अंतरभूत व्योम bnx2x_init_min(स्थिर काष्ठा cmng_init_input *input_data,
				  u32 r_param, काष्ठा cmng_init *ram_data)
अणु
	u32 vnic, fair_periodic_समयout_usec, vnicWeightSum, tFair;
	काष्ठा cmng_vnic *vdata = &ram_data->vnic;
	काष्ठा cmng_काष्ठा_per_port *pdata = &ram_data->port;

	/* this is the resolution of the fairness समयr */
	fair_periodic_समयout_usec = QM_ARB_BYTES / r_param;

	/* fairness per-port variables
	 * क्रम 10G it is 1000usec. क्रम 1G it is 10000usec.
	 */
	tFair = T_FAIR_COEF / input_data->port_rate;

	/* this is the threshold below which we won't arm the समयr anymore */
	pdata->fair_vars.fair_threshold = QM_ARB_BYTES;

	/* we multiply by 1e3/8 to get bytes/msec. We करोn't want the credits
	 * to pass a credit of the T_FAIR*FAIR_MEM (algorithm resolution)
	 */
	pdata->fair_vars.upper_bound = r_param * tFair * FAIR_MEM;

	/* since each tick is 4 microSeconds */
	pdata->fair_vars.fairness_समयout =
				fair_periodic_समयout_usec / SDM_TICKS;

	/* calculate sum of weights */
	vnicWeightSum = 0;

	क्रम (vnic = 0; vnic < BNX2X_PORT2_MODE_NUM_VNICS; vnic++)
		vnicWeightSum += input_data->vnic_min_rate[vnic];

	/* global vnic counter */
	अगर (vnicWeightSum > 0) अणु
		/* fairness per-vnic variables */
		क्रम (vnic = 0; vnic < BNX2X_PORT2_MODE_NUM_VNICS; vnic++) अणु
			/* this is the credit क्रम each period of the fairness
			 * algorithm - number of bytes in T_FAIR (this vnic
			 * share of the port rate)
			 */
			vdata->vnic_min_rate[vnic].vn_credit_delta =
				(u32)input_data->vnic_min_rate[vnic] * 100 *
				(T_FAIR_COEF / (8 * 100 * vnicWeightSum));
			अगर (vdata->vnic_min_rate[vnic].vn_credit_delta <
			    pdata->fair_vars.fair_threshold +
			    MIN_ABOVE_THRESH) अणु
				vdata->vnic_min_rate[vnic].vn_credit_delta =
					pdata->fair_vars.fair_threshold +
					MIN_ABOVE_THRESH;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bnx2x_init_fw_wrr(स्थिर काष्ठा cmng_init_input *input_data,
				     u32 r_param, काष्ठा cmng_init *ram_data)
अणु
	u32 vnic, cos;
	u32 cosWeightSum = 0;
	काष्ठा cmng_vnic *vdata = &ram_data->vnic;
	काष्ठा cmng_काष्ठा_per_port *pdata = &ram_data->port;

	क्रम (cos = 0; cos < MAX_COS_NUMBER; cos++)
		cosWeightSum += input_data->cos_min_rate[cos];

	अगर (cosWeightSum > 0) अणु

		क्रम (vnic = 0; vnic < BNX2X_PORT2_MODE_NUM_VNICS; vnic++) अणु
			/* Since cos and vnic shouldn't work together the rate
			 * to भागide between the coses is the port rate.
			 */
			u32 *ccd = vdata->vnic_min_rate[vnic].cos_credit_delta;
			क्रम (cos = 0; cos < MAX_COS_NUMBER; cos++) अणु
				/* this is the credit क्रम each period of
				 * the fairness algorithm - number of bytes
				 * in T_FAIR (this cos share of the vnic rate)
				 */
				ccd[cos] =
				    (u32)input_data->cos_min_rate[cos] * 100 *
				    (T_FAIR_COEF / (8 * 100 * cosWeightSum));
				अगर (ccd[cos] < pdata->fair_vars.fair_threshold
						+ MIN_ABOVE_THRESH) अणु
					ccd[cos] =
					    pdata->fair_vars.fair_threshold +
					    MIN_ABOVE_THRESH;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bnx2x_init_safc(स्थिर काष्ठा cmng_init_input *input_data,
				   काष्ठा cmng_init *ram_data)
अणु
	/* in microSeconds */
	ram_data->port.safc_vars.safc_समयout_usec = SAFC_TIMEOUT_USEC;
पूर्ण

/* Congestion management port init */
अटल अंतरभूत व्योम bnx2x_init_cmng(स्थिर काष्ठा cmng_init_input *input_data,
				   काष्ठा cmng_init *ram_data)
अणु
	u32 r_param;
	स_रखो(ram_data, 0, माप(काष्ठा cmng_init));

	ram_data->port.flags = input_data->flags;

	/* number of bytes transmitted in a rate of 10Gbps
	 * in one usec = 1.25KB.
	 */
	r_param = BITS_TO_BYTES(input_data->port_rate);
	bnx2x_init_max(input_data, r_param, ram_data);
	bnx2x_init_min(input_data, r_param, ram_data);
	bnx2x_init_fw_wrr(input_data, r_param, ram_data);
	bnx2x_init_safc(input_data, ram_data);
पूर्ण



/* Returns the index of start or end of a specअगरic block stage in ops array */
#घोषणा BLOCK_OPS_IDX(block, stage, end) \
			(2*(((block)*NUM_OF_INIT_PHASES) + (stage)) + (end))


#घोषणा INITOP_SET		0	/* set the HW directly */
#घोषणा INITOP_CLEAR		1	/* clear the HW directly */
#घोषणा INITOP_INIT		2	/* set the init-value array */

/****************************************************************************
* ILT management
****************************************************************************/
काष्ठा ilt_line अणु
	dma_addr_t page_mapping;
	व्योम *page;
	u32 size;
पूर्ण;

काष्ठा ilt_client_info अणु
	u32 page_size;
	u16 start;
	u16 end;
	u16 client_num;
	u16 flags;
#घोषणा ILT_CLIENT_SKIP_INIT	0x1
#घोषणा ILT_CLIENT_SKIP_MEM	0x2
पूर्ण;

काष्ठा bnx2x_ilt अणु
	u32 start_line;
	काष्ठा ilt_line		*lines;
	काष्ठा ilt_client_info	clients[4];
#घोषणा ILT_CLIENT_CDU	0
#घोषणा ILT_CLIENT_QM	1
#घोषणा ILT_CLIENT_SRC	2
#घोषणा ILT_CLIENT_TM	3
पूर्ण;

/****************************************************************************
* SRC configuration
****************************************************************************/
काष्ठा src_ent अणु
	u8 opaque[56];
	u64 next;
पूर्ण;

/****************************************************************************
* Parity configuration
****************************************************************************/
#घोषणा BLOCK_PRTY_INFO(block, en_mask, m1, m1h, m2, m3) \
अणु \
	block##_REG_##block##_PRTY_MASK, \
	block##_REG_##block##_PRTY_STS_CLR, \
	en_mask, अणुm1, m1h, m2, m3पूर्ण, #block \
पूर्ण

#घोषणा BLOCK_PRTY_INFO_0(block, en_mask, m1, m1h, m2, m3) \
अणु \
	block##_REG_##block##_PRTY_MASK_0, \
	block##_REG_##block##_PRTY_STS_CLR_0, \
	en_mask, अणुm1, m1h, m2, m3पूर्ण, #block"_0" \
पूर्ण

#घोषणा BLOCK_PRTY_INFO_1(block, en_mask, m1, m1h, m2, m3) \
अणु \
	block##_REG_##block##_PRTY_MASK_1, \
	block##_REG_##block##_PRTY_STS_CLR_1, \
	en_mask, अणुm1, m1h, m2, m3पूर्ण, #block"_1" \
पूर्ण

अटल स्थिर काष्ठा अणु
	u32 mask_addr;
	u32 sts_clr_addr;
	u32 en_mask;		/* Mask to enable parity attentions */
	काष्ठा अणु
		u32 e1;		/* 57710 */
		u32 e1h;	/* 57711 */
		u32 e2;		/* 57712 */
		u32 e3;		/* 578xx */
	पूर्ण reg_mask;		/* Register mask (all valid bits) */
	अक्षर name[8];		/* Block's दीर्घest name is 7 अक्षरacters दीर्घ
				 * (name + suffix)
				 */
पूर्ण bnx2x_blocks_parity_data[] = अणु
	/* bit 19 masked */
	/* REG_WR(bp, PXP_REG_PXP_PRTY_MASK, 0x80000); */
	/* bit 5,18,20-31 */
	/* REG_WR(bp, PXP2_REG_PXP2_PRTY_MASK_0, 0xfff40020); */
	/* bit 5 */
	/* REG_WR(bp, PXP2_REG_PXP2_PRTY_MASK_1, 0x20);	*/
	/* REG_WR(bp, HC_REG_HC_PRTY_MASK, 0x0); */
	/* REG_WR(bp, MISC_REG_MISC_PRTY_MASK, 0x0); */

	/* Block IGU, MISC, PXP and PXP2 parity errors as दीर्घ as we करोn't
	 * want to handle "system kill" flow at the moment.
	 */
	BLOCK_PRTY_INFO(PXP, 0x7ffffff, 0x3ffffff, 0x3ffffff, 0x7ffffff,
			0x7ffffff),
	BLOCK_PRTY_INFO_0(PXP2,	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BLOCK_PRTY_INFO_1(PXP2,	0x1ffffff, 0x7f, 0x7f, 0x7ff, 0x1ffffff),
	BLOCK_PRTY_INFO(HC, 0x7, 0x7, 0x7, 0, 0),
	BLOCK_PRTY_INFO(NIG, 0xffffffff, 0x3fffffff, 0xffffffff, 0, 0),
	BLOCK_PRTY_INFO_0(NIG,	0xffffffff, 0, 0, 0xffffffff, 0xffffffff),
	BLOCK_PRTY_INFO_1(NIG,	0xffff, 0, 0, 0xff, 0xffff),
	BLOCK_PRTY_INFO(IGU, 0x7ff, 0, 0, 0x7ff, 0x7ff),
	BLOCK_PRTY_INFO(MISC, 0x1, 0x1, 0x1, 0x1, 0x1),
	BLOCK_PRTY_INFO(QM, 0, 0x1ff, 0xfff, 0xfff, 0xfff),
	BLOCK_PRTY_INFO(ATC, 0x1f, 0, 0, 0x1f, 0x1f),
	BLOCK_PRTY_INFO(PGLUE_B, 0x3, 0, 0, 0x3, 0x3),
	BLOCK_PRTY_INFO(DORQ, 0, 0x3, 0x3, 0x3, 0x3),
	अणुGRCBASE_UPB + PB_REG_PB_PRTY_MASK,
		GRCBASE_UPB + PB_REG_PB_PRTY_STS_CLR, 0xf,
		अणु0xf, 0xf, 0xf, 0xfपूर्ण, "UPB"पूर्ण,
	अणुGRCBASE_XPB + PB_REG_PB_PRTY_MASK,
		GRCBASE_XPB + PB_REG_PB_PRTY_STS_CLR, 0,
		अणु0xf, 0xf, 0xf, 0xfपूर्ण, "XPB"पूर्ण,
	BLOCK_PRTY_INFO(SRC, 0x4, 0x7, 0x7, 0x7, 0x7),
	BLOCK_PRTY_INFO(CDU, 0, 0x1f, 0x1f, 0x1f, 0x1f),
	BLOCK_PRTY_INFO(CFC, 0, 0xf, 0xf, 0xf, 0x3f),
	BLOCK_PRTY_INFO(DBG, 0, 0x1, 0x1, 0x1, 0x1),
	BLOCK_PRTY_INFO(DMAE, 0, 0xf, 0xf, 0xf, 0xf),
	BLOCK_PRTY_INFO(BRB1, 0, 0xf, 0xf, 0xf, 0xf),
	BLOCK_PRTY_INFO(PRS, (1<<6), 0xff, 0xff, 0xff, 0xff),
	BLOCK_PRTY_INFO(PBF, 0, 0, 0x3ffff, 0xfffff, 0xfffffff),
	BLOCK_PRTY_INFO(TM, 0, 0, 0x7f, 0x7f, 0x7f),
	BLOCK_PRTY_INFO(TSDM, 0x18, 0x7ff, 0x7ff, 0x7ff, 0x7ff),
	BLOCK_PRTY_INFO(CSDM, 0x8, 0x7ff, 0x7ff, 0x7ff, 0x7ff),
	BLOCK_PRTY_INFO(USDM, 0x38, 0x7ff, 0x7ff, 0x7ff, 0x7ff),
	BLOCK_PRTY_INFO(XSDM, 0x8, 0x7ff, 0x7ff, 0x7ff, 0x7ff),
	BLOCK_PRTY_INFO(TCM, 0, 0, 0x7ffffff, 0x7ffffff, 0x7ffffff),
	BLOCK_PRTY_INFO(CCM, 0, 0, 0x7ffffff, 0x7ffffff, 0x7ffffff),
	BLOCK_PRTY_INFO(UCM, 0, 0, 0x7ffffff, 0x7ffffff, 0x7ffffff),
	BLOCK_PRTY_INFO(XCM, 0, 0, 0x3fffffff, 0x3fffffff, 0x3fffffff),
	BLOCK_PRTY_INFO_0(TSEM, 0, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BLOCK_PRTY_INFO_1(TSEM, 0, 0x3, 0x1f, 0x3f, 0x3f),
	BLOCK_PRTY_INFO_0(USEM, 0, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BLOCK_PRTY_INFO_1(USEM, 0, 0x3, 0x1f, 0x1f, 0x1f),
	BLOCK_PRTY_INFO_0(CSEM, 0, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BLOCK_PRTY_INFO_1(CSEM, 0, 0x3, 0x1f, 0x1f, 0x1f),
	BLOCK_PRTY_INFO_0(XSEM, 0, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BLOCK_PRTY_INFO_1(XSEM, 0, 0x3, 0x1f, 0x3f, 0x3f),
पूर्ण;


/* [28] MCP Latched rom_parity
 * [29] MCP Latched ump_rx_parity
 * [30] MCP Latched ump_tx_parity
 * [31] MCP Latched scpad_parity
 */
#घोषणा MISC_AEU_ENABLE_MCP_PRTY_SUB_BITS	\
	(AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY | \
	 AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY | \
	 AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY)

#घोषणा MISC_AEU_ENABLE_MCP_PRTY_BITS	\
	(MISC_AEU_ENABLE_MCP_PRTY_SUB_BITS | \
	 AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY)

/* Below रेजिस्टरs control the MCP parity attention output. When
 * MISC_AEU_ENABLE_MCP_PRTY_BITS are set - attentions are
 * enabled, when cleared - disabled.
 */
अटल स्थिर काष्ठा अणु
	u32 addr;
	u32 bits;
पूर्ण mcp_attn_ctl_regs[] = अणु
	अणु MISC_REG_AEU_ENABLE4_FUNC_0_OUT_0,
		MISC_AEU_ENABLE_MCP_PRTY_BITS पूर्ण,
	अणु MISC_REG_AEU_ENABLE4_NIG_0,
		MISC_AEU_ENABLE_MCP_PRTY_SUB_BITS पूर्ण,
	अणु MISC_REG_AEU_ENABLE4_PXP_0,
		MISC_AEU_ENABLE_MCP_PRTY_SUB_BITS पूर्ण,
	अणु MISC_REG_AEU_ENABLE4_FUNC_1_OUT_0,
		MISC_AEU_ENABLE_MCP_PRTY_BITS पूर्ण,
	अणु MISC_REG_AEU_ENABLE4_NIG_1,
		MISC_AEU_ENABLE_MCP_PRTY_SUB_BITS पूर्ण,
	अणु MISC_REG_AEU_ENABLE4_PXP_1,
		MISC_AEU_ENABLE_MCP_PRTY_SUB_BITS पूर्ण
पूर्ण;

अटल अंतरभूत व्योम bnx2x_set_mcp_parity(काष्ठा bnx2x *bp, u8 enable)
अणु
	पूर्णांक i;
	u32 reg_val;

	क्रम (i = 0; i < ARRAY_SIZE(mcp_attn_ctl_regs); i++) अणु
		reg_val = REG_RD(bp, mcp_attn_ctl_regs[i].addr);

		अगर (enable)
			reg_val |= mcp_attn_ctl_regs[i].bits;
		अन्यथा
			reg_val &= ~mcp_attn_ctl_regs[i].bits;

		REG_WR(bp, mcp_attn_ctl_regs[i].addr, reg_val);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 bnx2x_parity_reg_mask(काष्ठा bnx2x *bp, पूर्णांक idx)
अणु
	अगर (CHIP_IS_E1(bp))
		वापस bnx2x_blocks_parity_data[idx].reg_mask.e1;
	अन्यथा अगर (CHIP_IS_E1H(bp))
		वापस bnx2x_blocks_parity_data[idx].reg_mask.e1h;
	अन्यथा अगर (CHIP_IS_E2(bp))
		वापस bnx2x_blocks_parity_data[idx].reg_mask.e2;
	अन्यथा /* CHIP_IS_E3 */
		वापस bnx2x_blocks_parity_data[idx].reg_mask.e3;
पूर्ण

अटल अंतरभूत व्योम bnx2x_disable_blocks_parity(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bnx2x_blocks_parity_data); i++) अणु
		u32 dis_mask = bnx2x_parity_reg_mask(bp, i);

		अगर (dis_mask) अणु
			REG_WR(bp, bnx2x_blocks_parity_data[i].mask_addr,
			       dis_mask);
			DP(NETIF_MSG_HW, "Setting parity mask "
						 "for %s to\t\t0x%x\n",
				    bnx2x_blocks_parity_data[i].name, dis_mask);
		पूर्ण
	पूर्ण

	/* Disable MCP parity attentions */
	bnx2x_set_mcp_parity(bp, false);
पूर्ण

/* Clear the parity error status रेजिस्टरs. */
अटल अंतरभूत व्योम bnx2x_clear_blocks_parity(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	u32 reg_val, mcp_aeu_bits =
		AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY |
		AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY |
		AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY |
		AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY;

	/* Clear SEM_FAST parities */
	REG_WR(bp, XSEM_REG_FAST_MEMORY + SEM_FAST_REG_PARITY_RST, 0x1);
	REG_WR(bp, TSEM_REG_FAST_MEMORY + SEM_FAST_REG_PARITY_RST, 0x1);
	REG_WR(bp, USEM_REG_FAST_MEMORY + SEM_FAST_REG_PARITY_RST, 0x1);
	REG_WR(bp, CSEM_REG_FAST_MEMORY + SEM_FAST_REG_PARITY_RST, 0x1);

	क्रम (i = 0; i < ARRAY_SIZE(bnx2x_blocks_parity_data); i++) अणु
		u32 reg_mask = bnx2x_parity_reg_mask(bp, i);

		अगर (reg_mask) अणु
			reg_val = REG_RD(bp, bnx2x_blocks_parity_data[i].
					 sts_clr_addr);
			अगर (reg_val & reg_mask)
				DP(NETIF_MSG_HW,
					    "Parity errors in %s: 0x%x\n",
					    bnx2x_blocks_parity_data[i].name,
					    reg_val & reg_mask);
		पूर्ण
	पूर्ण

	/* Check अगर there were parity attentions in MCP */
	reg_val = REG_RD(bp, MISC_REG_AEU_AFTER_INVERT_4_MCP);
	अगर (reg_val & mcp_aeu_bits)
		DP(NETIF_MSG_HW, "Parity error in MCP: 0x%x\n",
		   reg_val & mcp_aeu_bits);

	/* Clear parity attentions in MCP:
	 * [7]  clears Latched rom_parity
	 * [8]  clears Latched ump_rx_parity
	 * [9]  clears Latched ump_tx_parity
	 * [10] clears Latched scpad_parity (both ports)
	 */
	REG_WR(bp, MISC_REG_AEU_CLR_LATCH_SIGNAL, 0x780);
पूर्ण

अटल अंतरभूत व्योम bnx2x_enable_blocks_parity(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bnx2x_blocks_parity_data); i++) अणु
		u32 reg_mask = bnx2x_parity_reg_mask(bp, i);

		अगर (reg_mask)
			REG_WR(bp, bnx2x_blocks_parity_data[i].mask_addr,
				bnx2x_blocks_parity_data[i].en_mask & reg_mask);
	पूर्ण

	/* Enable MCP parity attentions */
	bnx2x_set_mcp_parity(bp, true);
पूर्ण


#पूर्ण_अगर /* BNX2X_INIT_H */

