<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/crc8.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_init_ops.h"
#समावेश "qed_reg_addr.h"

#घोषणा CDU_VALIDATION_DEFAULT_CFG	61

अटल u16 con_region_offsets[3][NUM_OF_CONNECTION_TYPES_E4] = अणु
	अणु400, 336, 352, 368, 304, 384, 416, 352पूर्ण,	/* region 3 offsets */
	अणु528, 496, 416, 512, 448, 512, 544, 480पूर्ण,	/* region 4 offsets */
	अणु608, 544, 496, 576, 576, 592, 624, 560पूर्ण	/* region 5 offsets */
पूर्ण;

अटल u16 task_region_offsets[1][NUM_OF_CONNECTION_TYPES_E4] = अणु
	अणु240, 240, 112, 0, 0, 0, 0, 96पूर्ण	/* region 1 offsets */
पूर्ण;

/* General स्थिरants */
#घोषणा QM_PQ_MEM_4KB(pq_size)	(pq_size ? DIV_ROUND_UP((pq_size + 1) *	\
							QM_PQ_ELEMENT_SIZE, \
							0x1000) : 0)
#घोषणा QM_PQ_SIZE_256B(pq_size)	(pq_size ? DIV_ROUND_UP(pq_size, \
								0x100) - 1 : 0)
#घोषणा QM_INVALID_PQ_ID		0xffff

/* Max link speed (in Mbps) */
#घोषणा QM_MAX_LINK_SPEED               100000

/* Feature enable */
#घोषणा QM_BYPASS_EN	1
#घोषणा QM_BYTE_CRD_EN	1

/* Other PQ स्थिरants */
#घोषणा QM_OTHER_PQS_PER_PF	4

/* WFQ स्थिरants */

/* Upper bound in MB, 10 * burst size of 1ms in 50Gbps */
#घोषणा QM_WFQ_UPPER_BOUND	62500000

/* Bit  of VOQ in WFQ VP PQ map */
#घोषणा QM_WFQ_VP_PQ_VOQ_SHIFT	0

/* Bit  of PF in WFQ VP PQ map */
#घोषणा QM_WFQ_VP_PQ_PF_E4_SHIFT	5

/* 0x9000 = 4*9*1024 */
#घोषणा QM_WFQ_INC_VAL(weight)	((weight) * 0x9000)

/* Max WFQ increment value is 0.7 * upper bound */
#घोषणा QM_WFQ_MAX_INC_VAL	((QM_WFQ_UPPER_BOUND * 7) / 10)

/* RL स्थिरants */

/* Period in us */
#घोषणा QM_RL_PERIOD	5

/* Period in 25MHz cycles */
#घोषणा QM_RL_PERIOD_CLK_25M	(25 * QM_RL_PERIOD)

/* RL increment value - rate is specअगरied in mbps */
#घोषणा QM_RL_INC_VAL(rate) (अणु \
	typeof(rate) __rate = (rate); \
	max_t(u32, \
	      (u32)(((__rate ? __rate : 1000000) * QM_RL_PERIOD * 101) / \
		    (8 * 100)), \
	      1); पूर्ण)

/* PF RL Upper bound is set to 10 * burst size of 1ms in 50Gbps */
#घोषणा QM_PF_RL_UPPER_BOUND	62500000

/* Max PF RL increment value is 0.7 * upper bound */
#घोषणा QM_PF_RL_MAX_INC_VAL	((QM_PF_RL_UPPER_BOUND * 7) / 10)

/* Vport RL Upper bound, link speed is in Mpbs */
#घोषणा QM_VP_RL_UPPER_BOUND(speed)	((u32)max_t(u32, \
						    QM_RL_INC_VAL(speed), \
						    9700 + 1000))

/* Max Vport RL increment value is the Vport RL upper bound */
#घोषणा QM_VP_RL_MAX_INC_VAL(speed)	QM_VP_RL_UPPER_BOUND(speed)

/* Vport RL credit threshold in हाल of QM bypass */
#घोषणा QM_VP_RL_BYPASS_THRESH_SPEED	(QM_VP_RL_UPPER_BOUND(10000) - 1)

/* AFullOprtnstcCrdMask स्थिरants */
#घोषणा QM_OPPOR_LINE_VOQ_DEF	1
#घोषणा QM_OPPOR_FW_STOP_DEF	0
#घोषणा QM_OPPOR_PQ_EMPTY_DEF	1

/* Command Queue स्थिरants */

/* Pure LB CmdQ lines (+spare) */
#घोषणा PBF_CMDQ_PURE_LB_LINES	150

#घोषणा PBF_CMDQ_LINES_RT_OFFSET(ext_voq) \
	(PBF_REG_YCMD_QS_NUM_LINES_VOQ0_RT_OFFSET + \
	 (ext_voq) * (PBF_REG_YCMD_QS_NUM_LINES_VOQ1_RT_OFFSET - \
		PBF_REG_YCMD_QS_NUM_LINES_VOQ0_RT_OFFSET))

#घोषणा PBF_BTB_GUARANTEED_RT_OFFSET(ext_voq) \
	(PBF_REG_BTB_GUARANTEED_VOQ0_RT_OFFSET + \
	 (ext_voq) * (PBF_REG_BTB_GUARANTEED_VOQ1_RT_OFFSET - \
		PBF_REG_BTB_GUARANTEED_VOQ0_RT_OFFSET))

/* Returns the VOQ line credit क्रम the specअगरied number of PBF command lines.
 * PBF lines are specअगरied in 256b units.
 */
#घोषणा QM_VOQ_LINE_CRD(pbf_cmd_lines) \
	((((pbf_cmd_lines) - 4) * 2) | QM_LINE_CRD_REG_SIGN_BIT)

/* BTB: blocks स्थिरants (block size = 256B) */

/* 256B blocks in 9700B packet */
#घोषणा BTB_JUMBO_PKT_BLOCKS	38

/* Headroom per-port */
#घोषणा BTB_HEADROOM_BLOCKS	BTB_JUMBO_PKT_BLOCKS
#घोषणा BTB_PURE_LB_FACTOR	10

/* Factored (hence really 0.7) */
#घोषणा BTB_PURE_LB_RATIO	7

/* QM stop command स्थिरants */
#घोषणा QM_STOP_PQ_MASK_WIDTH		32
#घोषणा QM_STOP_CMD_ADDR		2
#घोषणा QM_STOP_CMD_STRUCT_SIZE		2
#घोषणा QM_STOP_CMD_PAUSE_MASK_OFFSET	0
#घोषणा QM_STOP_CMD_PAUSE_MASK_SHIFT	0
#घोषणा QM_STOP_CMD_PAUSE_MASK_MASK	-1
#घोषणा QM_STOP_CMD_GROUP_ID_OFFSET	1
#घोषणा QM_STOP_CMD_GROUP_ID_SHIFT	16
#घोषणा QM_STOP_CMD_GROUP_ID_MASK	15
#घोषणा QM_STOP_CMD_PQ_TYPE_OFFSET	1
#घोषणा QM_STOP_CMD_PQ_TYPE_SHIFT	24
#घोषणा QM_STOP_CMD_PQ_TYPE_MASK	1
#घोषणा QM_STOP_CMD_MAX_POLL_COUNT	100
#घोषणा QM_STOP_CMD_POLL_PERIOD_US	500

/* QM command macros */
#घोषणा QM_CMD_STRUCT_SIZE(cmd)	cmd ## _STRUCT_SIZE
#घोषणा QM_CMD_SET_FIELD(var, cmd, field, value) \
	SET_FIELD(var[cmd ## _ ## field ## _OFFSET], \
		  cmd ## _ ## field, \
		  value)

#घोषणा QM_INIT_TX_PQ_MAP(p_hwfn, map, chip, pq_id, vp_pq_id, rl_valid,	      \
			  rl_id, ext_voq, wrr)				      \
	करो अणु								      \
		u32 __reg = 0;						      \
									      \
		BUILD_BUG_ON(माप((map).reg) != माप(__reg));	      \
									      \
		SET_FIELD(__reg, QM_RF_PQ_MAP_##chip##_PQ_VALID, 1);	      \
		SET_FIELD(__reg, QM_RF_PQ_MAP_##chip##_RL_VALID,	      \
			  !!(rl_valid));				      \
		SET_FIELD(__reg, QM_RF_PQ_MAP_##chip##_VP_PQ_ID, (vp_pq_id)); \
		SET_FIELD(__reg, QM_RF_PQ_MAP_##chip##_RL_ID, (rl_id));	      \
		SET_FIELD(__reg, QM_RF_PQ_MAP_##chip##_VOQ, (ext_voq));	      \
		SET_FIELD(__reg, QM_RF_PQ_MAP_##chip##_WRR_WEIGHT_GROUP,      \
			  (wrr));					      \
									      \
		STORE_RT_REG((p_hwfn), QM_REG_TXPQMAP_RT_OFFSET + (pq_id),    \
			     __reg);					      \
		(map).reg = cpu_to_le32(__reg);				      \
	पूर्ण जबतक (0)

#घोषणा WRITE_PQ_INFO_TO_RAM	1
#घोषणा PQ_INFO_ELEMENT(vp, pf, tc, port, rl_valid, rl) \
	(((vp) << 0) | ((pf) << 12) | ((tc) << 16) | ((port) << 20) | \
	((rl_valid ? 1 : 0) << 22) | (((rl) & 255) << 24) | \
	(((rl) >> 8) << 9))

#घोषणा PQ_INFO_RAM_GRC_ADDRESS(pq_id) \
	XSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM + \
	XSTORM_PQ_INFO_OFFSET(pq_id)

/******************** INTERNAL IMPLEMENTATION *********************/

/* Returns the बाह्यal VOQ number */
अटल u8 qed_get_ext_voq(काष्ठा qed_hwfn *p_hwfn,
			  u8 port_id, u8 tc, u8 max_phys_tcs_per_port)
अणु
	अगर (tc == PURE_LB_TC)
		वापस NUM_OF_PHYS_TCS * MAX_NUM_PORTS_BB + port_id;
	अन्यथा
		वापस port_id * max_phys_tcs_per_port + tc;
पूर्ण

/* Prepare PF RL enable/disable runसमय init values */
अटल व्योम qed_enable_pf_rl(काष्ठा qed_hwfn *p_hwfn, bool pf_rl_en)
अणु
	STORE_RT_REG(p_hwfn, QM_REG_RLPFENABLE_RT_OFFSET, pf_rl_en ? 1 : 0);
	अगर (pf_rl_en) अणु
		u8 num_ext_voqs = MAX_NUM_VOQS_E4;
		u64 voq_bit_mask = ((u64)1 << num_ext_voqs) - 1;

		/* Enable RLs क्रम all VOQs */
		STORE_RT_REG(p_hwfn,
			     QM_REG_RLPFVOQENABLE_RT_OFFSET,
			     (u32)voq_bit_mask);

		/* Write RL period */
		STORE_RT_REG(p_hwfn,
			     QM_REG_RLPFPERIOD_RT_OFFSET, QM_RL_PERIOD_CLK_25M);
		STORE_RT_REG(p_hwfn,
			     QM_REG_RLPFPERIODTIMER_RT_OFFSET,
			     QM_RL_PERIOD_CLK_25M);

		/* Set credit threshold क्रम QM bypass flow */
		अगर (QM_BYPASS_EN)
			STORE_RT_REG(p_hwfn,
				     QM_REG_AFULLQMBYPTHRPFRL_RT_OFFSET,
				     QM_PF_RL_UPPER_BOUND);
	पूर्ण
पूर्ण

/* Prepare PF WFQ enable/disable runसमय init values */
अटल व्योम qed_enable_pf_wfq(काष्ठा qed_hwfn *p_hwfn, bool pf_wfq_en)
अणु
	STORE_RT_REG(p_hwfn, QM_REG_WFQPFENABLE_RT_OFFSET, pf_wfq_en ? 1 : 0);

	/* Set credit threshold क्रम QM bypass flow */
	अगर (pf_wfq_en && QM_BYPASS_EN)
		STORE_RT_REG(p_hwfn,
			     QM_REG_AFULLQMBYPTHRPFWFQ_RT_OFFSET,
			     QM_WFQ_UPPER_BOUND);
पूर्ण

/* Prepare global RL enable/disable runसमय init values */
अटल व्योम qed_enable_global_rl(काष्ठा qed_hwfn *p_hwfn, bool global_rl_en)
अणु
	STORE_RT_REG(p_hwfn, QM_REG_RLGLBLENABLE_RT_OFFSET,
		     global_rl_en ? 1 : 0);
	अगर (global_rl_en) अणु
		/* Write RL period (use समयr 0 only) */
		STORE_RT_REG(p_hwfn,
			     QM_REG_RLGLBLPERIOD_0_RT_OFFSET,
			     QM_RL_PERIOD_CLK_25M);
		STORE_RT_REG(p_hwfn,
			     QM_REG_RLGLBLPERIODTIMER_0_RT_OFFSET,
			     QM_RL_PERIOD_CLK_25M);

		/* Set credit threshold क्रम QM bypass flow */
		अगर (QM_BYPASS_EN)
			STORE_RT_REG(p_hwfn,
				     QM_REG_AFULLQMBYPTHRGLBLRL_RT_OFFSET,
				     QM_VP_RL_BYPASS_THRESH_SPEED);
	पूर्ण
पूर्ण

/* Prepare VPORT WFQ enable/disable runसमय init values */
अटल व्योम qed_enable_vport_wfq(काष्ठा qed_hwfn *p_hwfn, bool vport_wfq_en)
अणु
	STORE_RT_REG(p_hwfn, QM_REG_WFQVPENABLE_RT_OFFSET,
		     vport_wfq_en ? 1 : 0);

	/* Set credit threshold क्रम QM bypass flow */
	अगर (vport_wfq_en && QM_BYPASS_EN)
		STORE_RT_REG(p_hwfn,
			     QM_REG_AFULLQMBYPTHRVPWFQ_RT_OFFSET,
			     QM_WFQ_UPPER_BOUND);
पूर्ण

/* Prepare runसमय init values to allocate PBF command queue lines क्रम
 * the specअगरied VOQ.
 */
अटल व्योम qed_cmdq_lines_voq_rt_init(काष्ठा qed_hwfn *p_hwfn,
				       u8 ext_voq, u16 cmdq_lines)
अणु
	u32 qm_line_crd = QM_VOQ_LINE_CRD(cmdq_lines);

	OVERWRITE_RT_REG(p_hwfn, PBF_CMDQ_LINES_RT_OFFSET(ext_voq),
			 (u32)cmdq_lines);
	STORE_RT_REG(p_hwfn, QM_REG_VOQCRDLINE_RT_OFFSET + ext_voq,
		     qm_line_crd);
	STORE_RT_REG(p_hwfn, QM_REG_VOQINITCRDLINE_RT_OFFSET + ext_voq,
		     qm_line_crd);
पूर्ण

/* Prepare runसमय init values to allocate PBF command queue lines. */
अटल व्योम qed_cmdq_lines_rt_init(
	काष्ठा qed_hwfn *p_hwfn,
	u8 max_ports_per_engine,
	u8 max_phys_tcs_per_port,
	काष्ठा init_qm_port_params port_params[MAX_NUM_PORTS])
अणु
	u8 tc, ext_voq, port_id, num_tcs_in_port;
	u8 num_ext_voqs = MAX_NUM_VOQS_E4;

	/* Clear PBF lines of all VOQs */
	क्रम (ext_voq = 0; ext_voq < num_ext_voqs; ext_voq++)
		STORE_RT_REG(p_hwfn, PBF_CMDQ_LINES_RT_OFFSET(ext_voq), 0);

	क्रम (port_id = 0; port_id < max_ports_per_engine; port_id++) अणु
		u16 phys_lines, phys_lines_per_tc;

		अगर (!port_params[port_id].active)
			जारी;

		/* Find number of command queue lines to भागide between the
		 * active physical TCs.
		 */
		phys_lines = port_params[port_id].num_pbf_cmd_lines;
		phys_lines -= PBF_CMDQ_PURE_LB_LINES;

		/* Find #पंक्तिs per active physical TC */
		num_tcs_in_port = 0;
		क्रम (tc = 0; tc < max_phys_tcs_per_port; tc++)
			अगर (((port_params[port_id].active_phys_tcs >>
			      tc) & 0x1) == 1)
				num_tcs_in_port++;
		phys_lines_per_tc = phys_lines / num_tcs_in_port;

		/* Init रेजिस्टरs per active TC */
		क्रम (tc = 0; tc < max_phys_tcs_per_port; tc++) अणु
			ext_voq = qed_get_ext_voq(p_hwfn,
						  port_id,
						  tc, max_phys_tcs_per_port);
			अगर (((port_params[port_id].active_phys_tcs >>
			      tc) & 0x1) == 1)
				qed_cmdq_lines_voq_rt_init(p_hwfn,
							   ext_voq,
							   phys_lines_per_tc);
		पूर्ण

		/* Init रेजिस्टरs क्रम pure LB TC */
		ext_voq = qed_get_ext_voq(p_hwfn,
					  port_id,
					  PURE_LB_TC, max_phys_tcs_per_port);
		qed_cmdq_lines_voq_rt_init(p_hwfn, ext_voq,
					   PBF_CMDQ_PURE_LB_LINES);
	पूर्ण
पूर्ण

/* Prepare runसमय init values to allocate guaranteed BTB blocks क्रम the
 * specअगरied port. The guaranteed BTB space is भागided between the TCs as
 * follows (shared space Is currently not used):
 * 1. Parameters:
 *    B - BTB blocks क्रम this port
 *    C - Number of physical TCs क्रम this port
 * 2. Calculation:
 *    a. 38 blocks (9700B jumbo frame) are allocated क्रम global per port
 *	 headroom.
 *    b. B = B - 38 (reमुख्यder after global headroom allocation).
 *    c. MAX(38,B/(C+0.7)) blocks are allocated क्रम the pure LB VOQ.
 *    d. B = B - MAX(38, B/(C+0.7)) (reमुख्यder after pure LB allocation).
 *    e. B/C blocks are allocated क्रम each physical TC.
 * Assumptions:
 * - MTU is up to 9700 bytes (38 blocks)
 * - All TCs are considered symmetrical (same rate and packet size)
 * - No optimization क्रम lossy TC (all are considered lossless). Shared space
 *   is not enabled and allocated क्रम each TC.
 */
अटल व्योम qed_btb_blocks_rt_init(
	काष्ठा qed_hwfn *p_hwfn,
	u8 max_ports_per_engine,
	u8 max_phys_tcs_per_port,
	काष्ठा init_qm_port_params port_params[MAX_NUM_PORTS])
अणु
	u32 usable_blocks, pure_lb_blocks, phys_blocks;
	u8 tc, ext_voq, port_id, num_tcs_in_port;

	क्रम (port_id = 0; port_id < max_ports_per_engine; port_id++) अणु
		अगर (!port_params[port_id].active)
			जारी;

		/* Subtract headroom blocks */
		usable_blocks = port_params[port_id].num_btb_blocks -
				BTB_HEADROOM_BLOCKS;

		/* Find blocks per physical TC. Use factor to aव्योम भग्नing
		 * arithmethic.
		 */
		num_tcs_in_port = 0;
		क्रम (tc = 0; tc < NUM_OF_PHYS_TCS; tc++)
			अगर (((port_params[port_id].active_phys_tcs >>
			      tc) & 0x1) == 1)
				num_tcs_in_port++;

		pure_lb_blocks = (usable_blocks * BTB_PURE_LB_FACTOR) /
				 (num_tcs_in_port * BTB_PURE_LB_FACTOR +
				  BTB_PURE_LB_RATIO);
		pure_lb_blocks = max_t(u32, BTB_JUMBO_PKT_BLOCKS,
				       pure_lb_blocks / BTB_PURE_LB_FACTOR);
		phys_blocks = (usable_blocks - pure_lb_blocks) /
			      num_tcs_in_port;

		/* Init physical TCs */
		क्रम (tc = 0; tc < NUM_OF_PHYS_TCS; tc++) अणु
			अगर (((port_params[port_id].active_phys_tcs >>
			      tc) & 0x1) == 1) अणु
				ext_voq =
					qed_get_ext_voq(p_hwfn,
							port_id,
							tc,
							max_phys_tcs_per_port);
				STORE_RT_REG(p_hwfn,
					     PBF_BTB_GUARANTEED_RT_OFFSET
					     (ext_voq), phys_blocks);
			पूर्ण
		पूर्ण

		/* Init pure LB TC */
		ext_voq = qed_get_ext_voq(p_hwfn,
					  port_id,
					  PURE_LB_TC, max_phys_tcs_per_port);
		STORE_RT_REG(p_hwfn, PBF_BTB_GUARANTEED_RT_OFFSET(ext_voq),
			     pure_lb_blocks);
	पूर्ण
पूर्ण

/* Prepare runसमय init values क्रम the specअगरied RL.
 * Set max link speed (100Gbps) per rate limiter.
 * Return -1 on error.
 */
अटल पूर्णांक qed_global_rl_rt_init(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 upper_bound = QM_VP_RL_UPPER_BOUND(QM_MAX_LINK_SPEED) |
			  (u32)QM_RL_CRD_REG_SIGN_BIT;
	u32 inc_val;
	u16 rl_id;

	/* Go over all global RLs */
	क्रम (rl_id = 0; rl_id < MAX_QM_GLOBAL_RLS; rl_id++) अणु
		inc_val = QM_RL_INC_VAL(QM_MAX_LINK_SPEED);

		STORE_RT_REG(p_hwfn,
			     QM_REG_RLGLBLCRD_RT_OFFSET + rl_id,
			     (u32)QM_RL_CRD_REG_SIGN_BIT);
		STORE_RT_REG(p_hwfn,
			     QM_REG_RLGLBLUPPERBOUND_RT_OFFSET + rl_id,
			     upper_bound);
		STORE_RT_REG(p_hwfn,
			     QM_REG_RLGLBLINCVAL_RT_OFFSET + rl_id, inc_val);
	पूर्ण

	वापस 0;
पूर्ण

/* Prepare Tx PQ mapping runसमय init values क्रम the specअगरied PF */
अटल व्योम qed_tx_pq_map_rt_init(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा qed_qm_pf_rt_init_params *p_params,
				  u32 base_mem_addr_4kb)
अणु
	u32 tx_pq_vf_mask[MAX_QM_TX_QUEUES / QM_PF_QUEUE_GROUP_SIZE] = अणु 0 पूर्ण;
	काष्ठा init_qm_vport_params *vport_params = p_params->vport_params;
	u32 num_tx_pq_vf_masks = MAX_QM_TX_QUEUES / QM_PF_QUEUE_GROUP_SIZE;
	u16 num_pqs, first_pq_group, last_pq_group, i, j, pq_id, pq_group;
	काष्ठा init_qm_pq_params *pq_params = p_params->pq_params;
	u32 pq_mem_4kb, vport_pq_mem_4kb, mem_addr_4kb;

	num_pqs = p_params->num_pf_pqs + p_params->num_vf_pqs;

	first_pq_group = p_params->start_pq / QM_PF_QUEUE_GROUP_SIZE;
	last_pq_group = (p_params->start_pq + num_pqs - 1) /
			QM_PF_QUEUE_GROUP_SIZE;

	pq_mem_4kb = QM_PQ_MEM_4KB(p_params->num_pf_cids);
	vport_pq_mem_4kb = QM_PQ_MEM_4KB(p_params->num_vf_cids);
	mem_addr_4kb = base_mem_addr_4kb;

	/* Set mapping from PQ group to PF */
	क्रम (pq_group = first_pq_group; pq_group <= last_pq_group; pq_group++)
		STORE_RT_REG(p_hwfn, QM_REG_PQTX2PF_0_RT_OFFSET + pq_group,
			     (u32)(p_params->pf_id));

	/* Set PQ sizes */
	STORE_RT_REG(p_hwfn, QM_REG_MAXPQSIZE_0_RT_OFFSET,
		     QM_PQ_SIZE_256B(p_params->num_pf_cids));
	STORE_RT_REG(p_hwfn, QM_REG_MAXPQSIZE_1_RT_OFFSET,
		     QM_PQ_SIZE_256B(p_params->num_vf_cids));

	/* Go over all Tx PQs */
	क्रम (i = 0, pq_id = p_params->start_pq; i < num_pqs; i++, pq_id++) अणु
		u16 *p_first_tx_pq_id, vport_id_in_pf;
		काष्ठा qm_rf_pq_map_e4 tx_pq_map;
		u8 tc_id = pq_params[i].tc_id;
		bool is_vf_pq;
		u8 ext_voq;

		ext_voq = qed_get_ext_voq(p_hwfn,
					  pq_params[i].port_id,
					  tc_id,
					  p_params->max_phys_tcs_per_port);
		is_vf_pq = (i >= p_params->num_pf_pqs);

		/* Update first Tx PQ of VPORT/TC */
		vport_id_in_pf = pq_params[i].vport_id - p_params->start_vport;
		p_first_tx_pq_id =
		    &vport_params[vport_id_in_pf].first_tx_pq_id[tc_id];
		अगर (*p_first_tx_pq_id == QM_INVALID_PQ_ID) अणु
			u32 map_val =
				(ext_voq << QM_WFQ_VP_PQ_VOQ_SHIFT) |
				(p_params->pf_id << QM_WFQ_VP_PQ_PF_E4_SHIFT);

			/* Create new VP PQ */
			*p_first_tx_pq_id = pq_id;

			/* Map VP PQ to VOQ and PF */
			STORE_RT_REG(p_hwfn,
				     QM_REG_WFQVPMAP_RT_OFFSET +
				     *p_first_tx_pq_id,
				     map_val);
		पूर्ण

		/* Prepare PQ map entry */
		QM_INIT_TX_PQ_MAP(p_hwfn,
				  tx_pq_map,
				  E4,
				  pq_id,
				  *p_first_tx_pq_id,
				  pq_params[i].rl_valid,
				  pq_params[i].rl_id,
				  ext_voq, pq_params[i].wrr_group);

		/* Set PQ base address */
		STORE_RT_REG(p_hwfn,
			     QM_REG_BASEADDRTXPQ_RT_OFFSET + pq_id,
			     mem_addr_4kb);

		/* Clear PQ poपूर्णांकer table entry (64 bit) */
		अगर (p_params->is_pf_loading)
			क्रम (j = 0; j < 2; j++)
				STORE_RT_REG(p_hwfn,
					     QM_REG_PTRTBLTX_RT_OFFSET +
					     (pq_id * 2) + j, 0);

		/* Write PQ info to RAM */
		अगर (WRITE_PQ_INFO_TO_RAM != 0) अणु
			u32 pq_info = 0;

			pq_info = PQ_INFO_ELEMENT(*p_first_tx_pq_id,
						  p_params->pf_id,
						  tc_id,
						  pq_params[i].port_id,
						  pq_params[i].rl_valid,
						  pq_params[i].rl_id);
			qed_wr(p_hwfn, p_ptt, PQ_INFO_RAM_GRC_ADDRESS(pq_id),
			       pq_info);
		पूर्ण

		/* If VF PQ, add indication to PQ VF mask */
		अगर (is_vf_pq) अणु
			tx_pq_vf_mask[pq_id /
				      QM_PF_QUEUE_GROUP_SIZE] |=
			    BIT((pq_id % QM_PF_QUEUE_GROUP_SIZE));
			mem_addr_4kb += vport_pq_mem_4kb;
		पूर्ण अन्यथा अणु
			mem_addr_4kb += pq_mem_4kb;
		पूर्ण
	पूर्ण

	/* Store Tx PQ VF mask to size select रेजिस्टर */
	क्रम (i = 0; i < num_tx_pq_vf_masks; i++)
		अगर (tx_pq_vf_mask[i])
			STORE_RT_REG(p_hwfn,
				     QM_REG_MAXPQSIZETXSEL_0_RT_OFFSET + i,
				     tx_pq_vf_mask[i]);
पूर्ण

/* Prepare Other PQ mapping runसमय init values क्रम the specअगरied PF */
अटल व्योम qed_other_pq_map_rt_init(काष्ठा qed_hwfn *p_hwfn,
				     u8 pf_id,
				     bool is_pf_loading,
				     u32 num_pf_cids,
				     u32 num_tids, u32 base_mem_addr_4kb)
अणु
	u32 pq_size, pq_mem_4kb, mem_addr_4kb;
	u16 i, j, pq_id, pq_group;

	/* A single other PQ group is used in each PF, where PQ group i is used
	 * in PF i.
	 */
	pq_group = pf_id;
	pq_size = num_pf_cids + num_tids;
	pq_mem_4kb = QM_PQ_MEM_4KB(pq_size);
	mem_addr_4kb = base_mem_addr_4kb;

	/* Map PQ group to PF */
	STORE_RT_REG(p_hwfn, QM_REG_PQOTHER2PF_0_RT_OFFSET + pq_group,
		     (u32)(pf_id));

	/* Set PQ sizes */
	STORE_RT_REG(p_hwfn, QM_REG_MAXPQSIZE_2_RT_OFFSET,
		     QM_PQ_SIZE_256B(pq_size));

	क्रम (i = 0, pq_id = pf_id * QM_PF_QUEUE_GROUP_SIZE;
	     i < QM_OTHER_PQS_PER_PF; i++, pq_id++) अणु
		/* Set PQ base address */
		STORE_RT_REG(p_hwfn,
			     QM_REG_BASEADDROTHERPQ_RT_OFFSET + pq_id,
			     mem_addr_4kb);

		/* Clear PQ poपूर्णांकer table entry */
		अगर (is_pf_loading)
			क्रम (j = 0; j < 2; j++)
				STORE_RT_REG(p_hwfn,
					     QM_REG_PTRTBLOTHER_RT_OFFSET +
					     (pq_id * 2) + j, 0);

		mem_addr_4kb += pq_mem_4kb;
	पूर्ण
पूर्ण

/* Prepare PF WFQ runसमय init values क्रम the specअगरied PF.
 * Return -1 on error.
 */
अटल पूर्णांक qed_pf_wfq_rt_init(काष्ठा qed_hwfn *p_hwfn,

			      काष्ठा qed_qm_pf_rt_init_params *p_params)
अणु
	u16 num_tx_pqs = p_params->num_pf_pqs + p_params->num_vf_pqs;
	काष्ठा init_qm_pq_params *pq_params = p_params->pq_params;
	u32 inc_val, crd_reg_offset;
	u8 ext_voq;
	u16 i;

	inc_val = QM_WFQ_INC_VAL(p_params->pf_wfq);
	अगर (!inc_val || inc_val > QM_WFQ_MAX_INC_VAL) अणु
		DP_NOTICE(p_hwfn, "Invalid PF WFQ weight configuration\n");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < num_tx_pqs; i++) अणु
		ext_voq = qed_get_ext_voq(p_hwfn,
					  pq_params[i].port_id,
					  pq_params[i].tc_id,
					  p_params->max_phys_tcs_per_port);
		crd_reg_offset =
			(p_params->pf_id < MAX_NUM_PFS_BB ?
			 QM_REG_WFQPFCRD_RT_OFFSET :
			 QM_REG_WFQPFCRD_MSB_RT_OFFSET) +
			ext_voq * MAX_NUM_PFS_BB +
			(p_params->pf_id % MAX_NUM_PFS_BB);
		OVERWRITE_RT_REG(p_hwfn,
				 crd_reg_offset, (u32)QM_WFQ_CRD_REG_SIGN_BIT);
	पूर्ण

	STORE_RT_REG(p_hwfn,
		     QM_REG_WFQPFUPPERBOUND_RT_OFFSET + p_params->pf_id,
		     QM_WFQ_UPPER_BOUND | (u32)QM_WFQ_CRD_REG_SIGN_BIT);
	STORE_RT_REG(p_hwfn, QM_REG_WFQPFWEIGHT_RT_OFFSET + p_params->pf_id,
		     inc_val);

	वापस 0;
पूर्ण

/* Prepare PF RL runसमय init values क्रम the specअगरied PF.
 * Return -1 on error.
 */
अटल पूर्णांक qed_pf_rl_rt_init(काष्ठा qed_hwfn *p_hwfn, u8 pf_id, u32 pf_rl)
अणु
	u32 inc_val = QM_RL_INC_VAL(pf_rl);

	अगर (inc_val > QM_PF_RL_MAX_INC_VAL) अणु
		DP_NOTICE(p_hwfn, "Invalid PF rate limit configuration\n");
		वापस -1;
	पूर्ण

	STORE_RT_REG(p_hwfn,
		     QM_REG_RLPFCRD_RT_OFFSET + pf_id,
		     (u32)QM_RL_CRD_REG_SIGN_BIT);
	STORE_RT_REG(p_hwfn,
		     QM_REG_RLPFUPPERBOUND_RT_OFFSET + pf_id,
		     QM_PF_RL_UPPER_BOUND | (u32)QM_RL_CRD_REG_SIGN_BIT);
	STORE_RT_REG(p_hwfn, QM_REG_RLPFINCVAL_RT_OFFSET + pf_id, inc_val);

	वापस 0;
पूर्ण

/* Prepare VPORT WFQ runसमय init values क्रम the specअगरied VPORTs.
 * Return -1 on error.
 */
अटल पूर्णांक qed_vp_wfq_rt_init(काष्ठा qed_hwfn *p_hwfn,
			      u16 num_vports,
			      काष्ठा init_qm_vport_params *vport_params)
अणु
	u16 vport_pq_id, i;
	u32 inc_val;
	u8 tc;

	/* Go over all PF VPORTs */
	क्रम (i = 0; i < num_vports; i++) अणु
		अगर (!vport_params[i].wfq)
			जारी;

		inc_val = QM_WFQ_INC_VAL(vport_params[i].wfq);
		अगर (inc_val > QM_WFQ_MAX_INC_VAL) अणु
			DP_NOTICE(p_hwfn,
				  "Invalid VPORT WFQ weight configuration\n");
			वापस -1;
		पूर्ण

		/* Each VPORT can have several VPORT PQ IDs क्रम various TCs */
		क्रम (tc = 0; tc < NUM_OF_TCS; tc++) अणु
			vport_pq_id = vport_params[i].first_tx_pq_id[tc];
			अगर (vport_pq_id != QM_INVALID_PQ_ID) अणु
				STORE_RT_REG(p_hwfn,
					     QM_REG_WFQVPCRD_RT_OFFSET +
					     vport_pq_id,
					     (u32)QM_WFQ_CRD_REG_SIGN_BIT);
				STORE_RT_REG(p_hwfn,
					     QM_REG_WFQVPWEIGHT_RT_OFFSET +
					     vport_pq_id, inc_val);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool qed_poll_on_qm_cmd_पढ़ोy(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt)
अणु
	u32 reg_val, i;

	क्रम (i = 0, reg_val = 0; i < QM_STOP_CMD_MAX_POLL_COUNT && !reg_val;
	     i++) अणु
		udelay(QM_STOP_CMD_POLL_PERIOD_US);
		reg_val = qed_rd(p_hwfn, p_ptt, QM_REG_SDMCMDREADY);
	पूर्ण

	/* Check अगर समयout जबतक रुकोing क्रम SDM command पढ़ोy */
	अगर (i == QM_STOP_CMD_MAX_POLL_COUNT) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "Timeout when waiting for QM SDM command ready signal\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool qed_send_qm_cmd(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt,
			    u32 cmd_addr, u32 cmd_data_lsb, u32 cmd_data_msb)
अणु
	अगर (!qed_poll_on_qm_cmd_पढ़ोy(p_hwfn, p_ptt))
		वापस false;

	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDADDR, cmd_addr);
	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDDATALSB, cmd_data_lsb);
	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDDATAMSB, cmd_data_msb);
	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDGO, 1);
	qed_wr(p_hwfn, p_ptt, QM_REG_SDMCMDGO, 0);

	वापस qed_poll_on_qm_cmd_पढ़ोy(p_hwfn, p_ptt);
पूर्ण

/******************** INTERFACE IMPLEMENTATION *********************/

u32 qed_qm_pf_mem_size(u32 num_pf_cids,
		       u32 num_vf_cids,
		       u32 num_tids, u16 num_pf_pqs, u16 num_vf_pqs)
अणु
	वापस QM_PQ_MEM_4KB(num_pf_cids) * num_pf_pqs +
	       QM_PQ_MEM_4KB(num_vf_cids) * num_vf_pqs +
	       QM_PQ_MEM_4KB(num_pf_cids + num_tids) * QM_OTHER_PQS_PER_PF;
पूर्ण

पूर्णांक qed_qm_common_rt_init(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_qm_common_rt_init_params *p_params)
अणु
	u32 mask = 0;

	/* Init AFullOprtnstcCrdMask */
	SET_FIELD(mask, QM_RF_OPPORTUNISTIC_MASK_LINEVOQ,
		  QM_OPPOR_LINE_VOQ_DEF);
	SET_FIELD(mask, QM_RF_OPPORTUNISTIC_MASK_BYTEVOQ, QM_BYTE_CRD_EN);
	SET_FIELD(mask, QM_RF_OPPORTUNISTIC_MASK_PFWFQ, p_params->pf_wfq_en);
	SET_FIELD(mask, QM_RF_OPPORTUNISTIC_MASK_VPWFQ, p_params->vport_wfq_en);
	SET_FIELD(mask, QM_RF_OPPORTUNISTIC_MASK_PFRL, p_params->pf_rl_en);
	SET_FIELD(mask, QM_RF_OPPORTUNISTIC_MASK_VPQCNRL,
		  p_params->global_rl_en);
	SET_FIELD(mask, QM_RF_OPPORTUNISTIC_MASK_FWPAUSE, QM_OPPOR_FW_STOP_DEF);
	SET_FIELD(mask,
		  QM_RF_OPPORTUNISTIC_MASK_QUEUEEMPTY, QM_OPPOR_PQ_EMPTY_DEF);
	STORE_RT_REG(p_hwfn, QM_REG_AFULLOPRTNSTCCRDMASK_RT_OFFSET, mask);

	/* Enable/disable PF RL */
	qed_enable_pf_rl(p_hwfn, p_params->pf_rl_en);

	/* Enable/disable PF WFQ */
	qed_enable_pf_wfq(p_hwfn, p_params->pf_wfq_en);

	/* Enable/disable global RL */
	qed_enable_global_rl(p_hwfn, p_params->global_rl_en);

	/* Enable/disable VPORT WFQ */
	qed_enable_vport_wfq(p_hwfn, p_params->vport_wfq_en);

	/* Init PBF CMDQ line credit */
	qed_cmdq_lines_rt_init(p_hwfn,
			       p_params->max_ports_per_engine,
			       p_params->max_phys_tcs_per_port,
			       p_params->port_params);

	/* Init BTB blocks in PBF */
	qed_btb_blocks_rt_init(p_hwfn,
			       p_params->max_ports_per_engine,
			       p_params->max_phys_tcs_per_port,
			       p_params->port_params);

	qed_global_rl_rt_init(p_hwfn);

	वापस 0;
पूर्ण

पूर्णांक qed_qm_pf_rt_init(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      काष्ठा qed_qm_pf_rt_init_params *p_params)
अणु
	काष्ठा init_qm_vport_params *vport_params = p_params->vport_params;
	u32 other_mem_size_4kb = QM_PQ_MEM_4KB(p_params->num_pf_cids +
					       p_params->num_tids) *
				 QM_OTHER_PQS_PER_PF;
	u16 i;
	u8 tc;


	/* Clear first Tx PQ ID array क्रम each VPORT */
	क्रम (i = 0; i < p_params->num_vports; i++)
		क्रम (tc = 0; tc < NUM_OF_TCS; tc++)
			vport_params[i].first_tx_pq_id[tc] = QM_INVALID_PQ_ID;

	/* Map Other PQs (अगर any) */
	qed_other_pq_map_rt_init(p_hwfn,
				 p_params->pf_id,
				 p_params->is_pf_loading, p_params->num_pf_cids,
				 p_params->num_tids, 0);

	/* Map Tx PQs */
	qed_tx_pq_map_rt_init(p_hwfn, p_ptt, p_params, other_mem_size_4kb);

	/* Init PF WFQ */
	अगर (p_params->pf_wfq)
		अगर (qed_pf_wfq_rt_init(p_hwfn, p_params))
			वापस -1;

	/* Init PF RL */
	अगर (qed_pf_rl_rt_init(p_hwfn, p_params->pf_id, p_params->pf_rl))
		वापस -1;

	/* Init VPORT WFQ */
	अगर (qed_vp_wfq_rt_init(p_hwfn, p_params->num_vports, vport_params))
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक qed_init_pf_wfq(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt, u8 pf_id, u16 pf_wfq)
अणु
	u32 inc_val = QM_WFQ_INC_VAL(pf_wfq);

	अगर (!inc_val || inc_val > QM_WFQ_MAX_INC_VAL) अणु
		DP_NOTICE(p_hwfn, "Invalid PF WFQ weight configuration\n");
		वापस -1;
	पूर्ण

	qed_wr(p_hwfn, p_ptt, QM_REG_WFQPFWEIGHT + pf_id * 4, inc_val);

	वापस 0;
पूर्ण

पूर्णांक qed_init_pf_rl(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt, u8 pf_id, u32 pf_rl)
अणु
	u32 inc_val = QM_RL_INC_VAL(pf_rl);

	अगर (inc_val > QM_PF_RL_MAX_INC_VAL) अणु
		DP_NOTICE(p_hwfn, "Invalid PF rate limit configuration\n");
		वापस -1;
	पूर्ण

	qed_wr(p_hwfn,
	       p_ptt, QM_REG_RLPFCRD + pf_id * 4, (u32)QM_RL_CRD_REG_SIGN_BIT);
	qed_wr(p_hwfn, p_ptt, QM_REG_RLPFINCVAL + pf_id * 4, inc_val);

	वापस 0;
पूर्ण

पूर्णांक qed_init_vport_wfq(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       u16 first_tx_pq_id[NUM_OF_TCS], u16 wfq)
अणु
	u16 vport_pq_id;
	u32 inc_val;
	u8 tc;

	inc_val = QM_WFQ_INC_VAL(wfq);
	अगर (!inc_val || inc_val > QM_WFQ_MAX_INC_VAL) अणु
		DP_NOTICE(p_hwfn, "Invalid VPORT WFQ configuration.\n");
		वापस -1;
	पूर्ण

	/* A VPORT can have several VPORT PQ IDs क्रम various TCs */
	क्रम (tc = 0; tc < NUM_OF_TCS; tc++) अणु
		vport_pq_id = first_tx_pq_id[tc];
		अगर (vport_pq_id != QM_INVALID_PQ_ID)
			qed_wr(p_hwfn,
			       p_ptt,
			       QM_REG_WFQVPWEIGHT + vport_pq_id * 4, inc_val);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_init_global_rl(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt, u16 rl_id, u32 rate_limit)
अणु
	u32 inc_val;

	inc_val = QM_RL_INC_VAL(rate_limit);
	अगर (inc_val > QM_VP_RL_MAX_INC_VAL(rate_limit)) अणु
		DP_NOTICE(p_hwfn, "Invalid rate limit configuration.\n");
		वापस -1;
	पूर्ण

	qed_wr(p_hwfn, p_ptt,
	       QM_REG_RLGLBLCRD + rl_id * 4, (u32)QM_RL_CRD_REG_SIGN_BIT);
	qed_wr(p_hwfn, p_ptt, QM_REG_RLGLBLINCVAL + rl_id * 4, inc_val);

	वापस 0;
पूर्ण

bool qed_send_qm_stop_cmd(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt,
			  bool is_release_cmd,
			  bool is_tx_pq, u16 start_pq, u16 num_pqs)
अणु
	u32 cmd_arr[QM_CMD_STRUCT_SIZE(QM_STOP_CMD)] = अणु 0 पूर्ण;
	u32 pq_mask = 0, last_pq, pq_id;

	last_pq = start_pq + num_pqs - 1;

	/* Set command's PQ type */
	QM_CMD_SET_FIELD(cmd_arr, QM_STOP_CMD, PQ_TYPE, is_tx_pq ? 0 : 1);

	/* Go over requested PQs */
	क्रम (pq_id = start_pq; pq_id <= last_pq; pq_id++) अणु
		/* Set PQ bit in mask (stop command only) */
		अगर (!is_release_cmd)
			pq_mask |= BIT((pq_id % QM_STOP_PQ_MASK_WIDTH));

		/* If last PQ or end of PQ mask, ग_लिखो command */
		अगर ((pq_id == last_pq) ||
		    (pq_id % QM_STOP_PQ_MASK_WIDTH ==
		     (QM_STOP_PQ_MASK_WIDTH - 1))) अणु
			QM_CMD_SET_FIELD(cmd_arr,
					 QM_STOP_CMD, PAUSE_MASK, pq_mask);
			QM_CMD_SET_FIELD(cmd_arr,
					 QM_STOP_CMD,
					 GROUP_ID,
					 pq_id / QM_STOP_PQ_MASK_WIDTH);
			अगर (!qed_send_qm_cmd(p_hwfn, p_ptt, QM_STOP_CMD_ADDR,
					     cmd_arr[0], cmd_arr[1]))
				वापस false;
			pq_mask = 0;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

#घोषणा SET_TUNNEL_TYPE_ENABLE_BIT(var, offset, enable) \
	करो अणु \
		typeof(var) *__p_var = &(var); \
		typeof(offset) __offset = offset; \
		*__p_var = (*__p_var & ~BIT(__offset)) | \
			   ((enable) ? BIT(__offset) : 0); \
	पूर्ण जबतक (0)

#घोषणा PRS_ETH_TUNN_OUTPUT_FORMAT     0xF4DAB910
#घोषणा PRS_ETH_OUTPUT_FORMAT          0xFFFF4910

#घोषणा ARR_REG_WR(dev, ptt, addr, arr,	arr_size) \
	करो अणु \
		u32 i; \
		\
		क्रम (i = 0; i < (arr_size); i++) \
			qed_wr(dev, ptt, \
			       ((addr) + (4 * i)), \
			       ((u32 *)&(arr))[i]); \
	पूर्ण जबतक (0)

/**
 * qed_dmae_to_grc() - Internal function क्रम writing from host to
 * wide-bus रेजिस्टरs (split रेजिस्टरs are not supported yet).
 *
 * @p_hwfn: HW device data.
 * @p_ptt: PTT winकरोw used क्रम writing the रेजिस्टरs.
 * @p_data: Poपूर्णांकer to source data.
 * @addr: Destination रेजिस्टर address.
 * @len_in_dwords: Data length in dwords (u32).
 *
 * Return: Length of the written data in dwords (u32) or -1 on invalid
 *         input.
 */
अटल पूर्णांक qed_dmae_to_grc(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			   __le32 *p_data, u32 addr, u32 len_in_dwords)
अणु
	काष्ठा qed_dmae_params params = अणुपूर्ण;
	u32 *data_cpu;
	पूर्णांक rc;

	अगर (!p_data)
		वापस -1;

	/* Set DMAE params */
	SET_FIELD(params.flags, QED_DMAE_PARAMS_COMPLETION_DST, 1);

	/* Execute DMAE command */
	rc = qed_dmae_host2grc(p_hwfn, p_ptt,
			       (u64)(uपूर्णांकptr_t)(p_data),
			       addr, len_in_dwords, &params);

	/* If not पढ़ो using DMAE, पढ़ो using GRC */
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_DEBUG,
			   "Failed writing to chip using DMAE, using GRC instead\n");

		/* Swap to CPU byteorder and ग_लिखो to रेजिस्टरs using GRC */
		data_cpu = (__क्रमce u32 *)p_data;
		le32_to_cpu_array(data_cpu, len_in_dwords);

		ARR_REG_WR(p_hwfn, p_ptt, addr, data_cpu, len_in_dwords);
		cpu_to_le32_array(data_cpu, len_in_dwords);
	पूर्ण

	वापस len_in_dwords;
पूर्ण

व्योम qed_set_vxlan_dest_port(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt, u16 dest_port)
अणु
	/* Update PRS रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, PRS_REG_VXLAN_PORT, dest_port);

	/* Update NIG रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, NIG_REG_VXLAN_CTRL, dest_port);

	/* Update PBF रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, PBF_REG_VXLAN_PORT, dest_port);
पूर्ण

व्योम qed_set_vxlan_enable(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, bool vxlan_enable)
अणु
	u32 reg_val;
	u8 shअगरt;

	/* Update PRS रेजिस्टर */
	reg_val = qed_rd(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN);
	shअगरt = PRS_REG_ENCAPSULATION_TYPE_EN_VXLAN_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shअगरt, vxlan_enable);
	qed_wr(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN, reg_val);
	अगर (reg_val) अणु
		reg_val =
		    qed_rd(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2);

		/* Update output  only अगर tunnel blocks not included. */
		अगर (reg_val == (u32)PRS_ETH_OUTPUT_FORMAT)
			qed_wr(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2,
			       (u32)PRS_ETH_TUNN_OUTPUT_FORMAT);
	पूर्ण

	/* Update NIG रेजिस्टर */
	reg_val = qed_rd(p_hwfn, p_ptt, NIG_REG_ENC_TYPE_ENABLE);
	shअगरt = NIG_REG_ENC_TYPE_ENABLE_VXLAN_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shअगरt, vxlan_enable);
	qed_wr(p_hwfn, p_ptt, NIG_REG_ENC_TYPE_ENABLE, reg_val);

	/* Update DORQ रेजिस्टर */
	qed_wr(p_hwfn,
	       p_ptt, DORQ_REG_L2_EDPM_TUNNEL_VXLAN_EN, vxlan_enable ? 1 : 0);
पूर्ण

व्योम qed_set_gre_enable(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt,
			bool eth_gre_enable, bool ip_gre_enable)
अणु
	u32 reg_val;
	u8 shअगरt;

	/* Update PRS रेजिस्टर */
	reg_val = qed_rd(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN);
	shअगरt = PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GRE_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shअगरt, eth_gre_enable);
	shअगरt = PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GRE_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shअगरt, ip_gre_enable);
	qed_wr(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN, reg_val);
	अगर (reg_val) अणु
		reg_val =
		    qed_rd(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2);

		/* Update output  only अगर tunnel blocks not included. */
		अगर (reg_val == (u32)PRS_ETH_OUTPUT_FORMAT)
			qed_wr(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2,
			       (u32)PRS_ETH_TUNN_OUTPUT_FORMAT);
	पूर्ण

	/* Update NIG रेजिस्टर */
	reg_val = qed_rd(p_hwfn, p_ptt, NIG_REG_ENC_TYPE_ENABLE);
	shअगरt = NIG_REG_ENC_TYPE_ENABLE_ETH_OVER_GRE_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shअगरt, eth_gre_enable);
	shअगरt = NIG_REG_ENC_TYPE_ENABLE_IP_OVER_GRE_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shअगरt, ip_gre_enable);
	qed_wr(p_hwfn, p_ptt, NIG_REG_ENC_TYPE_ENABLE, reg_val);

	/* Update DORQ रेजिस्टरs */
	qed_wr(p_hwfn,
	       p_ptt,
	       DORQ_REG_L2_EDPM_TUNNEL_GRE_ETH_EN, eth_gre_enable ? 1 : 0);
	qed_wr(p_hwfn,
	       p_ptt, DORQ_REG_L2_EDPM_TUNNEL_GRE_IP_EN, ip_gre_enable ? 1 : 0);
पूर्ण

व्योम qed_set_geneve_dest_port(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt, u16 dest_port)
अणु
	/* Update PRS रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, PRS_REG_NGE_PORT, dest_port);

	/* Update NIG रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, NIG_REG_NGE_PORT, dest_port);

	/* Update PBF रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, PBF_REG_NGE_PORT, dest_port);
पूर्ण

व्योम qed_set_geneve_enable(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt,
			   bool eth_geneve_enable, bool ip_geneve_enable)
अणु
	u32 reg_val;
	u8 shअगरt;

	/* Update PRS रेजिस्टर */
	reg_val = qed_rd(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN);
	shअगरt = PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GENEVE_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shअगरt, eth_geneve_enable);
	shअगरt = PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GENEVE_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shअगरt, ip_geneve_enable);
	qed_wr(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN, reg_val);
	अगर (reg_val) अणु
		reg_val =
		    qed_rd(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2);

		/* Update output  only अगर tunnel blocks not included. */
		अगर (reg_val == (u32)PRS_ETH_OUTPUT_FORMAT)
			qed_wr(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2,
			       (u32)PRS_ETH_TUNN_OUTPUT_FORMAT);
	पूर्ण

	/* Update NIG रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, NIG_REG_NGE_ETH_ENABLE,
	       eth_geneve_enable ? 1 : 0);
	qed_wr(p_hwfn, p_ptt, NIG_REG_NGE_IP_ENABLE, ip_geneve_enable ? 1 : 0);

	/* EDPM with geneve tunnel not supported in BB */
	अगर (QED_IS_BB_B0(p_hwfn->cdev))
		वापस;

	/* Update DORQ रेजिस्टरs */
	qed_wr(p_hwfn,
	       p_ptt,
	       DORQ_REG_L2_EDPM_TUNNEL_NGE_ETH_EN_K2_E5,
	       eth_geneve_enable ? 1 : 0);
	qed_wr(p_hwfn,
	       p_ptt,
	       DORQ_REG_L2_EDPM_TUNNEL_NGE_IP_EN_K2_E5,
	       ip_geneve_enable ? 1 : 0);
पूर्ण

#घोषणा PRS_ETH_VXLAN_NO_L2_ENABLE_OFFSET      3
#घोषणा PRS_ETH_VXLAN_NO_L2_OUTPUT_FORMAT   -925189872

व्योम qed_set_vxlan_no_l2_enable(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt, bool enable)
अणु
	u32 reg_val, cfg_mask;

	/* पढ़ो PRS config रेजिस्टर */
	reg_val = qed_rd(p_hwfn, p_ptt, PRS_REG_MSG_INFO);

	/* set VXLAN_NO_L2_ENABLE mask */
	cfg_mask = BIT(PRS_ETH_VXLAN_NO_L2_ENABLE_OFFSET);

	अगर (enable) अणु
		/* set VXLAN_NO_L2_ENABLE flag */
		reg_val |= cfg_mask;

		/* update PRS FIC  रेजिस्टर */
		qed_wr(p_hwfn,
		       p_ptt,
		       PRS_REG_OUTPUT_FORMAT_4_0_BB_K2,
		       (u32)PRS_ETH_VXLAN_NO_L2_OUTPUT_FORMAT);
	पूर्ण अन्यथा अणु
		/* clear VXLAN_NO_L2_ENABLE flag */
		reg_val &= ~cfg_mask;
	पूर्ण

	/* ग_लिखो PRS config रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, PRS_REG_MSG_INFO, reg_val);
पूर्ण

#घोषणा T_ETH_PACKET_ACTION_GFT_EVENTID  23
#घोषणा PARSER_ETH_CONN_GFT_ACTION_CM_HDR  272
#घोषणा T_ETH_PACKET_MATCH_RFS_EVENTID 25
#घोषणा PARSER_ETH_CONN_CM_HDR 0
#घोषणा CAM_LINE_SIZE माप(u32)
#घोषणा RAM_LINE_SIZE माप(u64)
#घोषणा REG_SIZE माप(u32)

व्योम qed_gft_disable(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt, u16 pf_id)
अणु
	काष्ठा regpair ram_line = अणु पूर्ण;

	/* Disable gft search क्रम PF */
	qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_GFT, 0);

	/* Clean ram & cam क्रम next gft session */

	/* Zero camline */
	qed_wr(p_hwfn, p_ptt, PRS_REG_GFT_CAM + CAM_LINE_SIZE * pf_id, 0);

	/* Zero ramline */
	qed_dmae_to_grc(p_hwfn, p_ptt, &ram_line.lo,
			PRS_REG_GFT_PROखाता_MASK_RAM + RAM_LINE_SIZE * pf_id,
			माप(ram_line) / REG_SIZE);
पूर्ण

व्योम qed_gft_config(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    u16 pf_id,
		    bool tcp,
		    bool udp,
		    bool ipv4, bool ipv6, क्रमागत gft_profile_type profile_type)
अणु
	काष्ठा regpair ram_line;
	u32 search_non_ip_as_gft;
	u32 reg_val, cam_line;
	u32 lo = 0, hi = 0;

	अगर (!ipv6 && !ipv4)
		DP_NOTICE(p_hwfn,
			  "gft_config: must accept at least on of - ipv4 or ipv6'\n");
	अगर (!tcp && !udp)
		DP_NOTICE(p_hwfn,
			  "gft_config: must accept at least on of - udp or tcp\n");
	अगर (profile_type >= MAX_GFT_PROखाता_TYPE)
		DP_NOTICE(p_hwfn, "gft_config: unsupported gft_profile_type\n");

	/* Set RFS event ID to be awakened i Tstorm By Prs */
	reg_val = T_ETH_PACKET_MATCH_RFS_EVENTID <<
		  PRS_REG_CM_HDR_GFT_EVENT_ID_SHIFT;
	reg_val |= PARSER_ETH_CONN_CM_HDR << PRS_REG_CM_HDR_GFT_CM_HDR_SHIFT;
	qed_wr(p_hwfn, p_ptt, PRS_REG_CM_HDR_GFT, reg_val);

	/* Do not load context only cid in PRS on match. */
	qed_wr(p_hwfn, p_ptt, PRS_REG_LOAD_L2_FILTER, 0);

	/* Do not use tenant ID exist bit क्रम gft search */
	qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_TEन_अंकT_ID, 0);

	/* Set Cam */
	cam_line = 0;
	SET_FIELD(cam_line, GFT_CAM_LINE_MAPPED_VALID, 1);

	/* Filters are per PF!! */
	SET_FIELD(cam_line,
		  GFT_CAM_LINE_MAPPED_PF_ID_MASK,
		  GFT_CAM_LINE_MAPPED_PF_ID_MASK_MASK);
	SET_FIELD(cam_line, GFT_CAM_LINE_MAPPED_PF_ID, pf_id);

	अगर (!(tcp && udp)) अणु
		SET_FIELD(cam_line,
			  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK,
			  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK_MASK);
		अगर (tcp)
			SET_FIELD(cam_line,
				  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE,
				  GFT_PROखाता_TCP_PROTOCOL);
		अन्यथा
			SET_FIELD(cam_line,
				  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE,
				  GFT_PROखाता_UDP_PROTOCOL);
	पूर्ण

	अगर (!(ipv4 && ipv6)) अणु
		SET_FIELD(cam_line, GFT_CAM_LINE_MAPPED_IP_VERSION_MASK, 1);
		अगर (ipv4)
			SET_FIELD(cam_line,
				  GFT_CAM_LINE_MAPPED_IP_VERSION,
				  GFT_PROखाता_IPV4);
		अन्यथा
			SET_FIELD(cam_line,
				  GFT_CAM_LINE_MAPPED_IP_VERSION,
				  GFT_PROखाता_IPV6);
	पूर्ण

	/* Write अक्षरacteristics to cam */
	qed_wr(p_hwfn, p_ptt, PRS_REG_GFT_CAM + CAM_LINE_SIZE * pf_id,
	       cam_line);
	cam_line =
	    qed_rd(p_hwfn, p_ptt, PRS_REG_GFT_CAM + CAM_LINE_SIZE * pf_id);

	/* Write line to RAM - compare to filter 4 tuple */

	/* Search no IP as GFT */
	search_non_ip_as_gft = 0;

	/* Tunnel type */
	SET_FIELD(lo, GFT_RAM_LINE_TUNNEL_DST_PORT, 1);
	SET_FIELD(lo, GFT_RAM_LINE_TUNNEL_OVER_IP_PROTOCOL, 1);

	अगर (profile_type == GFT_PROखाता_TYPE_4_TUPLE) अणु
		SET_FIELD(hi, GFT_RAM_LINE_DST_IP, 1);
		SET_FIELD(hi, GFT_RAM_LINE_SRC_IP, 1);
		SET_FIELD(hi, GFT_RAM_LINE_OVER_IP_PROTOCOL, 1);
		SET_FIELD(lo, GFT_RAM_LINE_ETHERTYPE, 1);
		SET_FIELD(lo, GFT_RAM_LINE_SRC_PORT, 1);
		SET_FIELD(lo, GFT_RAM_LINE_DST_PORT, 1);
	पूर्ण अन्यथा अगर (profile_type == GFT_PROखाता_TYPE_L4_DST_PORT) अणु
		SET_FIELD(hi, GFT_RAM_LINE_OVER_IP_PROTOCOL, 1);
		SET_FIELD(lo, GFT_RAM_LINE_ETHERTYPE, 1);
		SET_FIELD(lo, GFT_RAM_LINE_DST_PORT, 1);
	पूर्ण अन्यथा अगर (profile_type == GFT_PROखाता_TYPE_IP_DST_ADDR) अणु
		SET_FIELD(hi, GFT_RAM_LINE_DST_IP, 1);
		SET_FIELD(lo, GFT_RAM_LINE_ETHERTYPE, 1);
	पूर्ण अन्यथा अगर (profile_type == GFT_PROखाता_TYPE_IP_SRC_ADDR) अणु
		SET_FIELD(hi, GFT_RAM_LINE_SRC_IP, 1);
		SET_FIELD(lo, GFT_RAM_LINE_ETHERTYPE, 1);
	पूर्ण अन्यथा अगर (profile_type == GFT_PROखाता_TYPE_TUNNEL_TYPE) अणु
		SET_FIELD(lo, GFT_RAM_LINE_TUNNEL_ETHERTYPE, 1);

		/* Allow tunneled traffic without inner IP */
		search_non_ip_as_gft = 1;
	पूर्ण

	ram_line.lo = cpu_to_le32(lo);
	ram_line.hi = cpu_to_le32(hi);

	qed_wr(p_hwfn,
	       p_ptt, PRS_REG_SEARCH_NON_IP_AS_GFT, search_non_ip_as_gft);
	qed_dmae_to_grc(p_hwfn, p_ptt, &ram_line.lo,
			PRS_REG_GFT_PROखाता_MASK_RAM + RAM_LINE_SIZE * pf_id,
			माप(ram_line) / REG_SIZE);

	/* Set शेष profile so that no filter match will happen */
	ram_line.lo = cpu_to_le32(0xffffffff);
	ram_line.hi = cpu_to_le32(0x3ff);
	qed_dmae_to_grc(p_hwfn, p_ptt, &ram_line.lo,
			PRS_REG_GFT_PROखाता_MASK_RAM + RAM_LINE_SIZE *
			PRS_GFT_CAM_LINES_NO_MATCH,
			माप(ram_line) / REG_SIZE);

	/* Enable gft search */
	qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_GFT, 1);
पूर्ण

DECLARE_CRC8_TABLE(cdu_crc8_table);

/* Calculate and वापस CDU validation byte per connection type/region/cid */
अटल u8 qed_calc_cdu_validation_byte(u8 conn_type, u8 region, u32 cid)
अणु
	स्थिर u8 validation_cfg = CDU_VALIDATION_DEFAULT_CFG;
	u8 crc, validation_byte = 0;
	अटल u8 crc8_table_valid; /* स्वतःmatically initialized to 0 */
	u32 validation_string = 0;
	__be32 data_to_crc;

	अगर (!crc8_table_valid) अणु
		crc8_populate_msb(cdu_crc8_table, 0x07);
		crc8_table_valid = 1;
	पूर्ण

	/* The CRC is calculated on the String-to-compress:
	 * [31:8]  = अणुCID[31:20],CID[11:0]पूर्ण
	 * [7:4]   = Region
	 * [3:0]   = Type
	 */
	अगर ((validation_cfg >> CDU_CONTEXT_VALIDATION_CFG_USE_CID) & 1)
		validation_string |= (cid & 0xFFF00000) | ((cid & 0xFFF) << 8);

	अगर ((validation_cfg >> CDU_CONTEXT_VALIDATION_CFG_USE_REGION) & 1)
		validation_string |= ((region & 0xF) << 4);

	अगर ((validation_cfg >> CDU_CONTEXT_VALIDATION_CFG_USE_TYPE) & 1)
		validation_string |= (conn_type & 0xF);

	/* Convert to big-endian and calculate CRC8 */
	data_to_crc = cpu_to_be32(validation_string);
	crc = crc8(cdu_crc8_table, (u8 *)&data_to_crc, माप(data_to_crc),
		   CRC8_INIT_VALUE);

	/* The validation byte [7:0] is composed:
	 * क्रम type A validation
	 * [7]          = active configuration bit
	 * [6:0]        = crc[6:0]
	 *
	 * क्रम type B validation
	 * [7]          = active configuration bit
	 * [6:3]        = connection_type[3:0]
	 * [2:0]        = crc[2:0]
	 */
	validation_byte |=
	    ((validation_cfg >>
	      CDU_CONTEXT_VALIDATION_CFG_USE_ACTIVE) & 1) << 7;

	अगर ((validation_cfg >>
	     CDU_CONTEXT_VALIDATION_CFG_VALIDATION_TYPE_SHIFT) & 1)
		validation_byte |= ((conn_type & 0xF) << 3) | (crc & 0x7);
	अन्यथा
		validation_byte |= crc & 0x7F;

	वापस validation_byte;
पूर्ण

/* Calcualte and set validation bytes क्रम session context */
व्योम qed_calc_session_ctx_validation(व्योम *p_ctx_mem,
				     u16 ctx_size, u8 ctx_type, u32 cid)
अणु
	u8 *x_val_ptr, *t_val_ptr, *u_val_ptr, *p_ctx;

	p_ctx = (u8 * स्थिर)p_ctx_mem;
	x_val_ptr = &p_ctx[con_region_offsets[0][ctx_type]];
	t_val_ptr = &p_ctx[con_region_offsets[1][ctx_type]];
	u_val_ptr = &p_ctx[con_region_offsets[2][ctx_type]];

	स_रखो(p_ctx, 0, ctx_size);

	*x_val_ptr = qed_calc_cdu_validation_byte(ctx_type, 3, cid);
	*t_val_ptr = qed_calc_cdu_validation_byte(ctx_type, 4, cid);
	*u_val_ptr = qed_calc_cdu_validation_byte(ctx_type, 5, cid);
पूर्ण

/* Calcualte and set validation bytes क्रम task context */
व्योम qed_calc_task_ctx_validation(व्योम *p_ctx_mem,
				  u16 ctx_size, u8 ctx_type, u32 tid)
अणु
	u8 *p_ctx, *region1_val_ptr;

	p_ctx = (u8 * स्थिर)p_ctx_mem;
	region1_val_ptr = &p_ctx[task_region_offsets[0][ctx_type]];

	स_रखो(p_ctx, 0, ctx_size);

	*region1_val_ptr = qed_calc_cdu_validation_byte(ctx_type, 1, tid);
पूर्ण

/* Memset session context to 0 जबतक preserving validation bytes */
व्योम qed_स_रखो_session_ctx(व्योम *p_ctx_mem, u32 ctx_size, u8 ctx_type)
अणु
	u8 *x_val_ptr, *t_val_ptr, *u_val_ptr, *p_ctx;
	u8 x_val, t_val, u_val;

	p_ctx = (u8 * स्थिर)p_ctx_mem;
	x_val_ptr = &p_ctx[con_region_offsets[0][ctx_type]];
	t_val_ptr = &p_ctx[con_region_offsets[1][ctx_type]];
	u_val_ptr = &p_ctx[con_region_offsets[2][ctx_type]];

	x_val = *x_val_ptr;
	t_val = *t_val_ptr;
	u_val = *u_val_ptr;

	स_रखो(p_ctx, 0, ctx_size);

	*x_val_ptr = x_val;
	*t_val_ptr = t_val;
	*u_val_ptr = u_val;
पूर्ण

/* Memset task context to 0 जबतक preserving validation bytes */
व्योम qed_स_रखो_task_ctx(व्योम *p_ctx_mem, u32 ctx_size, u8 ctx_type)
अणु
	u8 *p_ctx, *region1_val_ptr;
	u8 region1_val;

	p_ctx = (u8 * स्थिर)p_ctx_mem;
	region1_val_ptr = &p_ctx[task_region_offsets[0][ctx_type]];

	region1_val = *region1_val_ptr;

	स_रखो(p_ctx, 0, ctx_size);

	*region1_val_ptr = region1_val;
पूर्ण

/* Enable and configure context validation */
व्योम qed_enable_context_validation(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt)
अणु
	u32 ctx_validation;

	/* Enable validation क्रम connection region 3: CCFC_CTX_VALID0[31:24] */
	ctx_validation = CDU_VALIDATION_DEFAULT_CFG << 24;
	qed_wr(p_hwfn, p_ptt, CDU_REG_CCFC_CTX_VALID0, ctx_validation);

	/* Enable validation क्रम connection region 5: CCFC_CTX_VALID1[15:8] */
	ctx_validation = CDU_VALIDATION_DEFAULT_CFG << 8;
	qed_wr(p_hwfn, p_ptt, CDU_REG_CCFC_CTX_VALID1, ctx_validation);

	/* Enable validation क्रम connection region 1: TCFC_CTX_VALID0[15:8] */
	ctx_validation = CDU_VALIDATION_DEFAULT_CFG << 8;
	qed_wr(p_hwfn, p_ptt, CDU_REG_TCFC_CTX_VALID0, ctx_validation);
पूर्ण

अटल u32 qed_get_rdma_निश्चित_ram_addr(काष्ठा qed_hwfn *p_hwfn, u8 storm_id)
अणु
	चयन (storm_id) अणु
	हाल 0:
		वापस TSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    TSTORM_RDMA_ASSERT_LEVEL_OFFSET(p_hwfn->rel_pf_id);
	हाल 1:
		वापस MSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    MSTORM_RDMA_ASSERT_LEVEL_OFFSET(p_hwfn->rel_pf_id);
	हाल 2:
		वापस USEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    USTORM_RDMA_ASSERT_LEVEL_OFFSET(p_hwfn->rel_pf_id);
	हाल 3:
		वापस XSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    XSTORM_RDMA_ASSERT_LEVEL_OFFSET(p_hwfn->rel_pf_id);
	हाल 4:
		वापस YSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    YSTORM_RDMA_ASSERT_LEVEL_OFFSET(p_hwfn->rel_pf_id);
	हाल 5:
		वापस PSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    PSTORM_RDMA_ASSERT_LEVEL_OFFSET(p_hwfn->rel_pf_id);

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

व्योम qed_set_rdma_error_level(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      u8 निश्चित_level[NUM_STORMS])
अणु
	u8 storm_id;

	क्रम (storm_id = 0; storm_id < NUM_STORMS; storm_id++) अणु
		u32 ram_addr = qed_get_rdma_निश्चित_ram_addr(p_hwfn, storm_id);

		qed_wr(p_hwfn, p_ptt, ram_addr, निश्चित_level[storm_id]);
	पूर्ण
पूर्ण

#घोषणा PHYS_ADDR_DWORDS        DIV_ROUND_UP(माप(dma_addr_t), 4)
#घोषणा OVERLAY_HDR_SIZE_DWORDS (माप(काष्ठा fw_overlay_buf_hdr) / 4)

अटल u32 qed_get_overlay_addr_ram_addr(काष्ठा qed_hwfn *p_hwfn, u8 storm_id)
अणु
	चयन (storm_id) अणु
	हाल 0:
		वापस TSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    TSTORM_OVERLAY_BUF_ADDR_OFFSET;
	हाल 1:
		वापस MSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    MSTORM_OVERLAY_BUF_ADDR_OFFSET;
	हाल 2:
		वापस USEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    USTORM_OVERLAY_BUF_ADDR_OFFSET;
	हाल 3:
		वापस XSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    XSTORM_OVERLAY_BUF_ADDR_OFFSET;
	हाल 4:
		वापस YSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    YSTORM_OVERLAY_BUF_ADDR_OFFSET;
	हाल 5:
		वापस PSEM_REG_FAST_MEMORY + SEM_FAST_REG_INT_RAM +
		    PSTORM_OVERLAY_BUF_ADDR_OFFSET;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

काष्ठा phys_mem_desc *qed_fw_overlay_mem_alloc(काष्ठा qed_hwfn *p_hwfn,
					       स्थिर u32 * स्थिर
					       fw_overlay_in_buf,
					       u32 buf_size_in_bytes)
अणु
	u32 buf_size = buf_size_in_bytes / माप(u32), buf_offset = 0;
	काष्ठा phys_mem_desc *allocated_mem;

	अगर (!buf_size)
		वापस शून्य;

	allocated_mem = kसुस्मृति(NUM_STORMS, माप(काष्ठा phys_mem_desc),
				GFP_KERNEL);
	अगर (!allocated_mem)
		वापस शून्य;

	स_रखो(allocated_mem, 0, NUM_STORMS * माप(काष्ठा phys_mem_desc));

	/* For each Storm, set physical address in RAM */
	जबतक (buf_offset < buf_size) अणु
		काष्ठा phys_mem_desc *storm_mem_desc;
		काष्ठा fw_overlay_buf_hdr *hdr;
		u32 storm_buf_size;
		u8 storm_id;

		hdr =
		    (काष्ठा fw_overlay_buf_hdr *)&fw_overlay_in_buf[buf_offset];
		storm_buf_size = GET_FIELD(hdr->data,
					   FW_OVERLAY_BUF_HDR_BUF_SIZE);
		storm_id = GET_FIELD(hdr->data, FW_OVERLAY_BUF_HDR_STORM_ID);
		storm_mem_desc = allocated_mem + storm_id;
		storm_mem_desc->size = storm_buf_size * माप(u32);

		/* Allocate physical memory क्रम Storm's overlays buffer */
		storm_mem_desc->virt_addr =
		    dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				       storm_mem_desc->size,
				       &storm_mem_desc->phys_addr, GFP_KERNEL);
		अगर (!storm_mem_desc->virt_addr)
			अवरोध;

		/* Skip overlays buffer header */
		buf_offset += OVERLAY_HDR_SIZE_DWORDS;

		/* Copy Storm's overlays buffer to allocated memory */
		स_नकल(storm_mem_desc->virt_addr,
		       &fw_overlay_in_buf[buf_offset], storm_mem_desc->size);

		/* Advance to next Storm */
		buf_offset += storm_buf_size;
	पूर्ण

	/* If memory allocation has failed, मुक्त all allocated memory */
	अगर (buf_offset < buf_size) अणु
		qed_fw_overlay_mem_मुक्त(p_hwfn, allocated_mem);
		वापस शून्य;
	पूर्ण

	वापस allocated_mem;
पूर्ण

व्योम qed_fw_overlay_init_ram(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt,
			     काष्ठा phys_mem_desc *fw_overlay_mem)
अणु
	u8 storm_id;

	क्रम (storm_id = 0; storm_id < NUM_STORMS; storm_id++) अणु
		काष्ठा phys_mem_desc *storm_mem_desc =
		    (काष्ठा phys_mem_desc *)fw_overlay_mem + storm_id;
		u32 ram_addr, i;

		/* Skip Storms with no FW overlays */
		अगर (!storm_mem_desc->virt_addr)
			जारी;

		/* Calculate overlay RAM GRC address of current PF */
		ram_addr = qed_get_overlay_addr_ram_addr(p_hwfn, storm_id) +
			   माप(dma_addr_t) * p_hwfn->rel_pf_id;

		/* Write Storm's overlay physical address to RAM */
		क्रम (i = 0; i < PHYS_ADDR_DWORDS; i++, ram_addr += माप(u32))
			qed_wr(p_hwfn, p_ptt, ram_addr,
			       ((u32 *)&storm_mem_desc->phys_addr)[i]);
	पूर्ण
पूर्ण

व्योम qed_fw_overlay_mem_मुक्त(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा phys_mem_desc *fw_overlay_mem)
अणु
	u8 storm_id;

	अगर (!fw_overlay_mem)
		वापस;

	क्रम (storm_id = 0; storm_id < NUM_STORMS; storm_id++) अणु
		काष्ठा phys_mem_desc *storm_mem_desc =
		    (काष्ठा phys_mem_desc *)fw_overlay_mem + storm_id;

		/* Free Storm's physical memory */
		अगर (storm_mem_desc->virt_addr)
			dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
					  storm_mem_desc->size,
					  storm_mem_desc->virt_addr,
					  storm_mem_desc->phys_addr);
	पूर्ण

	/* Free allocated भव memory */
	kमुक्त(fw_overlay_mem);
पूर्ण
