<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NITROX_CSR_H
#घोषणा __NITROX_CSR_H

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/types.h>

/* EMU clusters */
#घोषणा NR_CLUSTERS		4
/* Maximum cores per cluster,
 * varies based on partname
 */
#घोषणा AE_CORES_PER_CLUSTER	20
#घोषणा SE_CORES_PER_CLUSTER	16

#घोषणा AE_MAX_CORES	(AE_CORES_PER_CLUSTER * NR_CLUSTERS)
#घोषणा SE_MAX_CORES	(SE_CORES_PER_CLUSTER * NR_CLUSTERS)
#घोषणा ZIP_MAX_CORES	5

/* BIST रेजिस्टरs */
#घोषणा EMU_BIST_STATUSX(_i)	(0x1402700 + ((_i) * 0x40000))
#घोषणा UCD_BIST_STATUS		0x12C0070
#घोषणा NPS_CORE_BIST_REG	0x10000E8
#घोषणा NPS_CORE_NPC_BIST_REG	0x1000128
#घोषणा NPS_PKT_SLC_BIST_REG	0x1040088
#घोषणा NPS_PKT_IN_BIST_REG	0x1040100
#घोषणा POM_BIST_REG		0x11C0100
#घोषणा BMI_BIST_REG		0x1140080
#घोषणा EFL_CORE_BIST_REGX(_i)	(0x1240100 + ((_i) * 0x400))
#घोषणा EFL_TOP_BIST_STAT	0x1241090
#घोषणा BMO_BIST_REG		0x1180080
#घोषणा LBC_BIST_STATUS		0x1200020
#घोषणा PEM_BIST_STATUSX(_i)	(0x1080468 | ((_i) << 18))

/* EMU रेजिस्टरs */
#घोषणा EMU_SE_ENABLEX(_i)	(0x1400000 + ((_i) * 0x40000))
#घोषणा EMU_AE_ENABLEX(_i)	(0x1400008 + ((_i) * 0x40000))
#घोषणा EMU_WD_INT_ENA_W1SX(_i)	(0x1402318 + ((_i) * 0x40000))
#घोषणा EMU_GE_INT_ENA_W1SX(_i)	(0x1402518 + ((_i) * 0x40000))
#घोषणा EMU_FUSE_MAPX(_i)	(0x1402708 + ((_i) * 0x40000))

/* UCD रेजिस्टरs */
#घोषणा UCD_SE_EID_UCODE_BLOCK_NUMX(_i)	(0x12C0000 + ((_i) * 0x1000))
#घोषणा UCD_AE_EID_UCODE_BLOCK_NUMX(_i)	(0x12C0008 + ((_i) * 0x800))
#घोषणा UCD_UCODE_LOAD_BLOCK_NUM	0x12C0010
#घोषणा UCD_UCODE_LOAD_IDX_DATAX(_i)	(0x12C0018 + ((_i) * 0x20))
#घोषणा UCD_SE_CNTX(_i)			(0x12C0040 + ((_i) * 0x1000))
#घोषणा UCD_AE_CNTX(_i)			(0x12C0048 + ((_i) * 0x800))

/* AQM रेजिस्टरs */
#घोषणा AQM_CTL                         0x1300000
#घोषणा AQM_INT                         0x1300008
#घोषणा AQM_DBELL_OVF_LO                0x1300010
#घोषणा AQM_DBELL_OVF_HI                0x1300018
#घोषणा AQM_DBELL_OVF_LO_W1S            0x1300020
#घोषणा AQM_DBELL_OVF_LO_ENA_W1C        0x1300028
#घोषणा AQM_DBELL_OVF_LO_ENA_W1S        0x1300030
#घोषणा AQM_DBELL_OVF_HI_W1S            0x1300038
#घोषणा AQM_DBELL_OVF_HI_ENA_W1C        0x1300040
#घोषणा AQM_DBELL_OVF_HI_ENA_W1S        0x1300048
#घोषणा AQM_DMA_RD_ERR_LO               0x1300050
#घोषणा AQM_DMA_RD_ERR_HI               0x1300058
#घोषणा AQM_DMA_RD_ERR_LO_W1S           0x1300060
#घोषणा AQM_DMA_RD_ERR_LO_ENA_W1C       0x1300068
#घोषणा AQM_DMA_RD_ERR_LO_ENA_W1S       0x1300070
#घोषणा AQM_DMA_RD_ERR_HI_W1S           0x1300078
#घोषणा AQM_DMA_RD_ERR_HI_ENA_W1C       0x1300080
#घोषणा AQM_DMA_RD_ERR_HI_ENA_W1S       0x1300088
#घोषणा AQM_EXEC_NA_LO                  0x1300090
#घोषणा AQM_EXEC_NA_HI                  0x1300098
#घोषणा AQM_EXEC_NA_LO_W1S              0x13000A0
#घोषणा AQM_EXEC_NA_LO_ENA_W1C          0x13000A8
#घोषणा AQM_EXEC_NA_LO_ENA_W1S          0x13000B0
#घोषणा AQM_EXEC_NA_HI_W1S              0x13000B8
#घोषणा AQM_EXEC_NA_HI_ENA_W1C          0x13000C0
#घोषणा AQM_EXEC_NA_HI_ENA_W1S          0x13000C8
#घोषणा AQM_EXEC_ERR_LO                 0x13000D0
#घोषणा AQM_EXEC_ERR_HI                 0x13000D8
#घोषणा AQM_EXEC_ERR_LO_W1S             0x13000E0
#घोषणा AQM_EXEC_ERR_LO_ENA_W1C         0x13000E8
#घोषणा AQM_EXEC_ERR_LO_ENA_W1S         0x13000F0
#घोषणा AQM_EXEC_ERR_HI_W1S             0x13000F8
#घोषणा AQM_EXEC_ERR_HI_ENA_W1C         0x1300100
#घोषणा AQM_EXEC_ERR_HI_ENA_W1S         0x1300108
#घोषणा AQM_ECC_INT                     0x1300110
#घोषणा AQM_ECC_INT_W1S                 0x1300118
#घोषणा AQM_ECC_INT_ENA_W1C             0x1300120
#घोषणा AQM_ECC_INT_ENA_W1S             0x1300128
#घोषणा AQM_ECC_CTL                     0x1300130
#घोषणा AQM_BIST_STATUS                 0x1300138
#घोषणा AQM_CMD_INF_THRX(x)             (0x1300400 + ((x) * 0x8))
#घोषणा AQM_CMD_INFX(x)                 (0x1300800 + ((x) * 0x8))
#घोषणा AQM_GRP_EXECMSK_LOX(x)          (0x1300C00 + ((x) * 0x10))
#घोषणा AQM_GRP_EXECMSK_HIX(x)          (0x1300C08 + ((x) * 0x10))
#घोषणा AQM_ACTIVITY_STAT_LO            0x1300C80
#घोषणा AQM_ACTIVITY_STAT_HI            0x1300C88
#घोषणा AQM_Q_CMD_PROCX(x)              (0x1301000 + ((x) * 0x8))
#घोषणा AQM_PERF_CTL_LO                 0x1301400
#घोषणा AQM_PERF_CTL_HI                 0x1301408
#घोषणा AQM_PERF_CNT                    0x1301410

#घोषणा AQMQ_DRBLX(x)                   (0x20000 + ((x) * 0x40000))
#घोषणा AQMQ_QSZX(x)                    (0x20008 + ((x) * 0x40000))
#घोषणा AQMQ_BADRX(x)                   (0x20010 + ((x) * 0x40000))
#घोषणा AQMQ_NXT_CMDX(x)                (0x20018 + ((x) * 0x40000))
#घोषणा AQMQ_CMD_CNTX(x)                (0x20020 + ((x) * 0x40000))
#घोषणा AQMQ_CMP_THRX(x)                (0x20028 + ((x) * 0x40000))
#घोषणा AQMQ_CMP_CNTX(x)                (0x20030 + ((x) * 0x40000))
#घोषणा AQMQ_TIM_LDX(x)                 (0x20038 + ((x) * 0x40000))
#घोषणा AQMQ_TIMERX(x)                  (0x20040 + ((x) * 0x40000))
#घोषणा AQMQ_ENX(x)                     (0x20048 + ((x) * 0x40000))
#घोषणा AQMQ_ACTIVITY_STATX(x)          (0x20050 + ((x) * 0x40000))
#घोषणा AQM_VF_CMP_STATX(x)             (0x28000 + ((x) * 0x40000))

/* NPS core रेजिस्टरs */
#घोषणा NPS_CORE_GBL_VFCFG	0x1000000
#घोषणा NPS_CORE_CONTROL	0x1000008
#घोषणा NPS_CORE_INT_ACTIVE	0x1000080
#घोषणा NPS_CORE_INT		0x10000A0
#घोषणा NPS_CORE_INT_ENA_W1S	0x10000B8
#घोषणा NPS_STATS_PKT_DMA_RD_CNT	0x1000180
#घोषणा NPS_STATS_PKT_DMA_WR_CNT	0x1000190

/* NPS packet रेजिस्टरs */
#घोषणा NPS_PKT_INT			0x1040018
#घोषणा NPS_PKT_MBOX_INT_LO		0x1040020
#घोषणा NPS_PKT_MBOX_INT_LO_ENA_W1C	0x1040030
#घोषणा NPS_PKT_MBOX_INT_LO_ENA_W1S	0x1040038
#घोषणा NPS_PKT_MBOX_INT_HI		0x1040040
#घोषणा NPS_PKT_MBOX_INT_HI_ENA_W1C	0x1040050
#घोषणा NPS_PKT_MBOX_INT_HI_ENA_W1S	0x1040058
#घोषणा NPS_PKT_IN_RERR_HI		0x1040108
#घोषणा NPS_PKT_IN_RERR_HI_ENA_W1S	0x1040120
#घोषणा NPS_PKT_IN_RERR_LO		0x1040128
#घोषणा NPS_PKT_IN_RERR_LO_ENA_W1S	0x1040140
#घोषणा NPS_PKT_IN_ERR_TYPE		0x1040148
#घोषणा NPS_PKT_IN_ERR_TYPE_ENA_W1S	0x1040160
#घोषणा NPS_PKT_IN_INSTR_CTLX(_i)	(0x10060 + ((_i) * 0x40000))
#घोषणा NPS_PKT_IN_INSTR_BADDRX(_i)	(0x10068 + ((_i) * 0x40000))
#घोषणा NPS_PKT_IN_INSTR_RSIZEX(_i)	(0x10070 + ((_i) * 0x40000))
#घोषणा NPS_PKT_IN_DONE_CNTSX(_i)	(0x10080 + ((_i) * 0x40000))
#घोषणा NPS_PKT_IN_INSTR_BAOFF_DBELLX(_i)	(0x10078 + ((_i) * 0x40000))
#घोषणा NPS_PKT_IN_INT_LEVELSX(_i)		(0x10088 + ((_i) * 0x40000))

#घोषणा NPS_PKT_SLC_RERR_HI		0x1040208
#घोषणा NPS_PKT_SLC_RERR_HI_ENA_W1S	0x1040220
#घोषणा NPS_PKT_SLC_RERR_LO		0x1040228
#घोषणा NPS_PKT_SLC_RERR_LO_ENA_W1S	0x1040240
#घोषणा NPS_PKT_SLC_ERR_TYPE		0x1040248
#घोषणा NPS_PKT_SLC_ERR_TYPE_ENA_W1S	0x1040260
/* Mailbox PF->VF PF Accessible Data रेजिस्टरs */
#घोषणा NPS_PKT_MBOX_PF_VF_PFDATAX(_i)	(0x1040800 + ((_i) * 0x8))
#घोषणा NPS_PKT_MBOX_VF_PF_PFDATAX(_i)	(0x1040C00 + ((_i) * 0x8))

#घोषणा NPS_PKT_SLC_CTLX(_i)		(0x10000 + ((_i) * 0x40000))
#घोषणा NPS_PKT_SLC_CNTSX(_i)		(0x10008 + ((_i) * 0x40000))
#घोषणा NPS_PKT_SLC_INT_LEVELSX(_i)	(0x10010 + ((_i) * 0x40000))

/* POM रेजिस्टरs */
#घोषणा POM_INT_ENA_W1S		0x11C0018
#घोषणा POM_GRP_EXECMASKX(_i)	(0x11C1100 | ((_i) * 8))
#घोषणा POM_INT		0x11C0000
#घोषणा POM_PERF_CTL	0x11CC400

/* BMI रेजिस्टरs */
#घोषणा BMI_INT		0x1140000
#घोषणा BMI_CTL		0x1140020
#घोषणा BMI_INT_ENA_W1S	0x1140018
#घोषणा BMI_NPS_PKT_CNT	0x1140070

/* EFL रेजिस्टरs */
#घोषणा EFL_CORE_INT_ENA_W1SX(_i)		(0x1240018 + ((_i) * 0x400))
#घोषणा EFL_CORE_VF_ERR_INT0X(_i)		(0x1240050 + ((_i) * 0x400))
#घोषणा EFL_CORE_VF_ERR_INT0_ENA_W1SX(_i)	(0x1240068 + ((_i) * 0x400))
#घोषणा EFL_CORE_VF_ERR_INT1X(_i)		(0x1240070 + ((_i) * 0x400))
#घोषणा EFL_CORE_VF_ERR_INT1_ENA_W1SX(_i)	(0x1240088 + ((_i) * 0x400))
#घोषणा EFL_CORE_SE_ERR_INTX(_i)		(0x12400A0 + ((_i) * 0x400))
#घोषणा EFL_RNM_CTL_STATUS			0x1241800
#घोषणा EFL_CORE_INTX(_i)			(0x1240000 + ((_i) * 0x400))

/* BMO रेजिस्टरs */
#घोषणा BMO_CTL2		0x1180028
#घोषणा BMO_NPS_SLC_PKT_CNT	0x1180078

/* LBC रेजिस्टरs */
#घोषणा LBC_INT			0x1200000
#घोषणा LBC_INVAL_CTL		0x1201010
#घोषणा LBC_PLM_VF1_64_INT	0x1202008
#घोषणा LBC_INVAL_STATUS	0x1202010
#घोषणा LBC_INT_ENA_W1S		0x1203000
#घोषणा LBC_PLM_VF1_64_INT_ENA_W1S	0x1205008
#घोषणा LBC_PLM_VF65_128_INT		0x1206008
#घोषणा LBC_ELM_VF1_64_INT		0x1208000
#घोषणा LBC_PLM_VF65_128_INT_ENA_W1S	0x1209008
#घोषणा LBC_ELM_VF1_64_INT_ENA_W1S	0x120B000
#घोषणा LBC_ELM_VF65_128_INT		0x120C000
#घोषणा LBC_ELM_VF65_128_INT_ENA_W1S	0x120F000

#घोषणा RST_BOOT	0x10C1600
#घोषणा FUS_DAT1	0x10C1408

/* PEM रेजिस्टरs */
#घोषणा PEM0_INT 0x1080428

/**
 * काष्ठा ucd_core_eid_ucode_block_num - Core Eid to Ucode Blk Mapping Registers
 * @ucode_len: Ucode length identअगरier 32KB or 64KB
 * @ucode_blk: Ucode Block Number
 */
जोड़ ucd_core_eid_ucode_block_num अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_4_63 : 60;
		u64 ucode_len : 1;
		u64 ucode_blk : 3;
#अन्यथा
		u64 ucode_blk : 3;
		u64 ucode_len : 1;
		u64 raz_4_63 : 60;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा aqm_grp_execmsk_lo - Available AE engines क्रम the group
 * @exec_0_to_39: AE engines 0 to 39 status
 */
जोड़ aqm_grp_execmsk_lo अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_40_63 : 24;
		u64 exec_0_to_39 : 40;
#अन्यथा
		u64 exec_0_to_39 : 40;
		u64 raz_40_63 : 24;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा aqm_grp_execmsk_hi - Available AE engines क्रम the group
 * @exec_40_to_79: AE engines 40 to 79 status
 */
जोड़ aqm_grp_execmsk_hi अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_40_63 : 24;
		u64 exec_40_to_79 : 40;
#अन्यथा
		u64 exec_40_to_79 : 40;
		u64 raz_40_63 : 24;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा aqmq_drbl - AQM Queue Doorbell Counter Registers
 * @dbell_count: Doorbell Counter
 */
जोड़ aqmq_drbl अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_32_63 : 32;
		u64 dbell_count : 32;
#अन्यथा
		u64 dbell_count : 32;
		u64 raz_32_63 : 32;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा aqmq_qsz - AQM Queue Host Queue Size Registers
 * @host_queue_size: Size, in numbers of 'aqmq_command_s' command
 * of the Host Ring.
 */
जोड़ aqmq_qsz अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_32_63 : 32;
		u64 host_queue_size : 32;
#अन्यथा
		u64 host_queue_size : 32;
		u64 raz_32_63 : 32;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा aqmq_cmp_thr - AQM Queue Commands Completed Threshold Registers
 * @commands_completed_threshold: Count of 'aqmq_command_s' commands executed
 * by AE engines क्रम which completion पूर्णांकerrupt is निश्चितed.
 */
जोड़ aqmq_cmp_thr अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_32_63 : 32;
		u64 commands_completed_threshold : 32;
#अन्यथा
		u64 commands_completed_threshold : 32;
		u64 raz_32_63 : 32;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा aqmq_cmp_cnt - AQM Queue Commands Completed Count Registers
 * @resend: Bit to request completion पूर्णांकerrupt Resend.
 * @completion_status: Command completion status of the ring.
 * @commands_completed_count: Count of 'aqmq_command_s' commands executed by
 * AE engines.
 */
जोड़ aqmq_cmp_cnt अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_34_63 : 30;
		u64 resend : 1;
		u64 completion_status : 1;
		u64 commands_completed_count : 32;
#अन्यथा
		u64 commands_completed_count : 32;
		u64 completion_status : 1;
		u64 resend : 1;
		u64 raz_34_63 : 30;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा aqmq_en - AQM Queue Enable Registers
 * @queue_status: 1 = AQMQ is enabled, 0 = AQMQ is disabled
 */
जोड़ aqmq_en अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_1_63 : 63;
		u64 queue_enable : 1;
#अन्यथा
		u64 queue_enable : 1;
		u64 raz_1_63 : 63;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा aqmq_activity_stat - AQM Queue Activity Status Registers
 * @queue_active: 1 = AQMQ is active, 0 = AQMQ is quiescent
 */
जोड़ aqmq_activity_stat अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_1_63 : 63;
		u64 queue_active : 1;
#अन्यथा
		u64 queue_active : 1;
		u64 raz_1_63 : 63;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा emu_fuse_map - EMU Fuse Map Registers
 * @ae_fuse: Fuse settings क्रम AE 19..0
 * @se_fuse: Fuse settings क्रम SE 15..0
 *
 * A set bit indicates the unit is fuse disabled.
 */
जोड़ emu_fuse_map अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 valid : 1;
		u64 raz_52_62 : 11;
		u64 ae_fuse : 20;
		u64 raz_16_31 : 16;
		u64 se_fuse : 16;
#अन्यथा
		u64 se_fuse : 16;
		u64 raz_16_31 : 16;
		u64 ae_fuse : 20;
		u64 raz_52_62 : 11;
		u64 valid : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा emu_se_enable - Symmetric Engine Enable Registers
 * @enable: Inभागidual enables क्रम each of the clusters
 *   16 symmetric engines.
 */
जोड़ emu_se_enable अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz	: 48;
		u64 enable : 16;
#अन्यथा
		u64 enable : 16;
		u64 raz	: 48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा emu_ae_enable - EMU Asymmetric engines.
 * @enable: Inभागidual enables क्रम each of the cluster's
 *   20 Asymmetric Engines.
 */
जोड़ emu_ae_enable अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz	: 44;
		u64 enable : 20;
#अन्यथा
		u64 enable : 20;
		u64 raz	: 44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा emu_wd_पूर्णांक_ena_w1s - EMU Interrupt Enable Registers
 * @ae_wd: Reads or sets enable क्रम EMU(0..3)_WD_INT[AE_WD]
 * @se_wd: Reads or sets enable क्रम EMU(0..3)_WD_INT[SE_WD]
 */
जोड़ emu_wd_पूर्णांक_ena_w1s अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz2 : 12;
		u64 ae_wd : 20;
		u64 raz1 : 16;
		u64 se_wd : 16;
#अन्यथा
		u64 se_wd : 16;
		u64 raz1 : 16;
		u64 ae_wd : 20;
		u64 raz2 : 12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा emu_ge_पूर्णांक_ena_w1s - EMU Interrupt Enable set रेजिस्टरs
 * @ae_ge: Reads or sets enable क्रम EMU(0..3)_GE_INT[AE_GE]
 * @se_ge: Reads or sets enable क्रम EMU(0..3)_GE_INT[SE_GE]
 */
जोड़ emu_ge_पूर्णांक_ena_w1s अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_52_63 : 12;
		u64 ae_ge : 20;
		u64 raz_16_31: 16;
		u64 se_ge : 16;
#अन्यथा
		u64 se_ge : 16;
		u64 raz_16_31: 16;
		u64 ae_ge : 20;
		u64 raz_52_63 : 12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_slc_ctl - Solicited Packet Out Control Registers
 * @rh: Indicates whether to हटाओ or include the response header
 *   1 = Include, 0 = Remove
 * @z: If set, 8 trailing 0x00 bytes will be added to the end of the
 *   outgoing packet.
 * @enb: Enable क्रम this port.
 */
जोड़ nps_pkt_slc_ctl अणु
	u64 value;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 raz : 61;
		u64 rh : 1;
		u64 z : 1;
		u64 enb : 1;
#अन्यथा
		u64 enb : 1;
		u64 z : 1;
		u64 rh : 1;
		u64 raz : 61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_slc_cnts - Solicited Packet Out Count Registers
 * @slc_पूर्णांक: Returns a 1 when:
 *   NPS_PKT_SLC(i)_CNTS[CNT] > NPS_PKT_SLC(i)_INT_LEVELS[CNT], or
 *   NPS_PKT_SLC(i)_CNTS[TIMER] > NPS_PKT_SLC(i)_INT_LEVELS[TIMET].
 *   To clear the bit, the CNTS रेजिस्टर must be written to clear.
 * @in_पूर्णांक: Returns a 1 when:
 *   NPS_PKT_IN(i)_DONE_CNTS[CNT] > NPS_PKT_IN(i)_INT_LEVELS[CNT].
 *   To clear the bit, the DONE_CNTS रेजिस्टर must be written to clear.
 * @mbox_पूर्णांक: Returns a 1 when:
 *   NPS_PKT_MBOX_PF_VF(i)_INT[INTR] is set. To clear the bit,
 *   ग_लिखो NPS_PKT_MBOX_PF_VF(i)_INT[INTR] with 1.
 * @समयr: Timer, incremented every 2048 coprocessor घड़ी cycles
 *   when [CNT] is not zero. The hardware clears both [TIMER] and
 *   [INT] when [CNT] goes to 0.
 * @cnt: Packet counter. Hardware adds to [CNT] as it sends packets out.
 *   On a ग_लिखो to this CSR, hardware subtracts the amount written to the
 *   [CNT] field from [CNT].
 */
जोड़ nps_pkt_slc_cnts अणु
	u64 value;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 slc_पूर्णांक : 1;
		u64 uns_पूर्णांक : 1;
		u64 in_पूर्णांक : 1;
		u64 mbox_पूर्णांक : 1;
		u64 resend : 1;
		u64 raz : 5;
		u64 समयr : 22;
		u64 cnt : 32;
#अन्यथा
		u64 cnt	: 32;
		u64 समयr : 22;
		u64 raz	: 5;
		u64 resend : 1;
		u64 mbox_पूर्णांक : 1;
		u64 in_पूर्णांक : 1;
		u64 uns_पूर्णांक : 1;
		u64 slc_पूर्णांक : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_slc_पूर्णांक_levels - Solicited Packet Out Interrupt Levels
 *   Registers.
 * @bmode: Determines whether NPS_PKT_SLC_CNTS[CNT] is a byte or
 *   packet counter.
 * @समयt: Output port counter समय पूर्णांकerrupt threshold.
 * @cnt: Output port counter पूर्णांकerrupt threshold.
 */
जोड़ nps_pkt_slc_पूर्णांक_levels अणु
	u64 value;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 bmode : 1;
		u64 raz	: 9;
		u64 समयt : 22;
		u64 cnt	: 32;
#अन्यथा
		u64 cnt : 32;
		u64 समयt : 22;
		u64 raz : 9;
		u64 bmode : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_inst - NPS Packet Interrupt Register
 * @in_err: Set when any NPS_PKT_IN_RERR_HI/LO bit and
 *    corresponding NPS_PKT_IN_RERR_*_ENA_* bit are bot set.
 * @uns_err: Set when any NSP_PKT_UNS_RERR_HI/LO bit and
 *    corresponding NPS_PKT_UNS_RERR_*_ENA_* bit are both set.
 * @slc_er: Set when any NSP_PKT_SLC_RERR_HI/LO bit and
 *    corresponding NPS_PKT_SLC_RERR_*_ENA_* bit are both set.
 */
जोड़ nps_pkt_पूर्णांक अणु
	u64 value;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 raz	: 54;
		u64 uns_wto : 1;
		u64 in_err : 1;
		u64 uns_err : 1;
		u64 slc_err : 1;
		u64 in_dbe : 1;
		u64 in_sbe : 1;
		u64 uns_dbe : 1;
		u64 uns_sbe : 1;
		u64 slc_dbe : 1;
		u64 slc_sbe : 1;
#अन्यथा
		u64 slc_sbe : 1;
		u64 slc_dbe : 1;
		u64 uns_sbe : 1;
		u64 uns_dbe : 1;
		u64 in_sbe : 1;
		u64 in_dbe : 1;
		u64 slc_err : 1;
		u64 uns_err : 1;
		u64 in_err : 1;
		u64 uns_wto : 1;
		u64 raz	: 54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_in_करोne_cnts - Input inकाष्ठाion ring counts रेजिस्टरs
 * @slc_cnt: Returns a 1 when:
 *    NPS_PKT_SLC(i)_CNTS[CNT] > NPS_PKT_SLC(i)_INT_LEVELS[CNT], or
 *    NPS_PKT_SLC(i)_CNTS[TIMER] > NPS_PKT_SCL(i)_INT_LEVELS[TIMET]
 *    To clear the bit, the CNTS रेजिस्टर must be
 *    written to clear the underlying condition
 * @uns_पूर्णांक: Return a 1 when:
 *    NPS_PKT_UNS(i)_CNTS[CNT] > NPS_PKT_UNS(i)_INT_LEVELS[CNT], or
 *    NPS_PKT_UNS(i)_CNTS[TIMER] > NPS_PKT_UNS(i)_INT_LEVELS[TIMET]
 *    To clear the bit, the CNTS रेजिस्टर must be
 *    written to clear the underlying condition
 * @in_पूर्णांक: Returns a 1 when:
 *    NPS_PKT_IN(i)_DONE_CNTS[CNT] > NPS_PKT_IN(i)_INT_LEVELS[CNT]
 *    To clear the bit, the DONE_CNTS रेजिस्टर
 *    must be written to clear the underlying condition
 * @mbox_पूर्णांक: Returns a 1 when:
 *    NPS_PKT_MBOX_PF_VF(i)_INT[INTR] is set.
 *    To clear the bit, ग_लिखो NPS_PKT_MBOX_PF_VF(i)_INT[INTR]
 *    with 1.
 * @resend: A ग_लिखो of 1 will resend an MSI-X पूर्णांकerrupt message अगर any
 *    of the following conditions are true क्रम this ring "i".
 *    NPS_PKT_SLC(i)_CNTS[CNT] > NPS_PKT_SLC(i)_INT_LEVELS[CNT]
 *    NPS_PKT_SLC(i)_CNTS[TIMER] > NPS_PKT_SLC(i)_INT_LEVELS[TIMET]
 *    NPS_PKT_UNS(i)_CNTS[CNT] > NPS_PKT_UNS(i)_INT_LEVELS[CNT]
 *    NPS_PKT_UNS(i)_CNTS[TIMER] > NPS_PKT_UNS(i)_INT_LEVELS[TIMET]
 *    NPS_PKT_IN(i)_DONE_CNTS[CNT] > NPS_PKT_IN(i)_INT_LEVELS[CNT]
 *    NPS_PKT_MBOX_PF_VF(i)_INT[INTR] is set
 * @cnt: Packet counter. Hardware adds to [CNT] as it पढ़ोs
 *    packets. On a ग_लिखो to this CSR, hardware substracts the
 *    amount written to the [CNT] field from [CNT], which will
 *    clear PKT_IN(i)_INT_STATUS[INTR] अगर [CNT] becomes <=
 *    NPS_PKT_IN(i)_INT_LEVELS[CNT]. This रेजिस्टर should be
 *    cleared beक्रमe enabling a ring by पढ़ोing the current
 *    value and writing it back.
 */
जोड़ nps_pkt_in_करोne_cnts अणु
	u64 value;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 slc_पूर्णांक : 1;
		u64 uns_पूर्णांक : 1;
		u64 in_पूर्णांक : 1;
		u64 mbox_पूर्णांक : 1;
		u64 resend : 1;
		u64 raz : 27;
		u64 cnt	: 32;
#अन्यथा
		u64 cnt	: 32;
		u64 raz	: 27;
		u64 resend : 1;
		u64 mbox_पूर्णांक : 1;
		u64 in_पूर्णांक : 1;
		u64 uns_पूर्णांक : 1;
		u64 slc_पूर्णांक : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_in_instr_ctl - Input Inकाष्ठाion Ring Control Registers.
 * @is64b: If 1, the ring uses 64-byte inकाष्ठाions. If 0, the
 *   ring uses 32-byte inकाष्ठाions.
 * @enb: Enable क्रम the input ring.
 */
जोड़ nps_pkt_in_instr_ctl अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz	: 62;
		u64 is64b : 1;
		u64 enb	: 1;
#अन्यथा
		u64 enb	: 1;
		u64 is64b : 1;
		u64 raz : 62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_in_instr_rsize - Input inकाष्ठाion ring size रेजिस्टरs
 * @rsize: Ring size (number of inकाष्ठाions)
 */
जोड़ nps_pkt_in_instr_rsize अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz	: 32;
		u64 rsize : 32;
#अन्यथा
		u64 rsize : 32;
		u64 raz	: 32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_in_instr_baoff_dbell - Input inकाष्ठाion ring
 *   base address offset and करोorbell रेजिस्टरs
 * @aoff: Address offset. The offset from the NPS_PKT_IN_INSTR_BADDR
 *   where the next poपूर्णांकer is पढ़ो.
 * @dbell: Poपूर्णांकer list करोorbell count. Write operations to this field
 *   increments the present value here. Read operations वापस the
 *   present value.
 */
जोड़ nps_pkt_in_instr_baoff_dbell अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 aoff : 32;
		u64 dbell : 32;
#अन्यथा
		u64 dbell : 32;
		u64 aoff : 32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_core_पूर्णांक_ena_w1s - NPS core पूर्णांकerrupt enable set रेजिस्टर
 * @host_nps_wr_err: Reads or sets enable क्रम
 *   NPS_CORE_INT[HOST_NPS_WR_ERR].
 * @npco_dma_malक्रमm: Reads or sets enable क्रम
 *   NPS_CORE_INT[NPCO_DMA_MALFORM].
 * @exec_wr_समयout: Reads or sets enable क्रम
 *   NPS_CORE_INT[EXEC_WR_TIMEOUT].
 * @host_wr_समयout: Reads or sets enable क्रम
 *   NPS_CORE_INT[HOST_WR_TIMEOUT].
 * @host_wr_err: Reads or sets enable क्रम
 *   NPS_CORE_INT[HOST_WR_ERR]
 */
जोड़ nps_core_पूर्णांक_ena_w1s अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz4 : 55;
		u64 host_nps_wr_err : 1;
		u64 npco_dma_malक्रमm : 1;
		u64 exec_wr_समयout : 1;
		u64 host_wr_समयout : 1;
		u64 host_wr_err : 1;
		u64 raz3 : 1;
		u64 raz2 : 1;
		u64 raz1 : 1;
		u64 raz0 : 1;
#अन्यथा
		u64 raz0 : 1;
		u64 raz1 : 1;
		u64 raz2 : 1;
		u64 raz3 : 1;
		u64 host_wr_err	: 1;
		u64 host_wr_समयout : 1;
		u64 exec_wr_समयout : 1;
		u64 npco_dma_malक्रमm : 1;
		u64 host_nps_wr_err : 1;
		u64 raz4 : 55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_core_gbl_vfcfg - Global VF Configuration Register.
 * @ilk_disable: When set, this bit indicates that the ILK पूर्णांकerface has
 *    been disabled.
 * @obaf: BMO allocation control
 *    0 = allocate per queue
 *    1 = allocate per VF
 * @ibaf: BMI allocation control
 *    0 = allocate per queue
 *    1 = allocate per VF
 * @zaf: ZIP allocation control
 *    0 = allocate per queue
 *    1 = allocate per VF
 * @aeaf: AE allocation control
 *    0 = allocate per queue
 *    1 = allocate per VF
 * @seaf: SE allocation control
 *    0 = allocation per queue
 *    1 = allocate per VF
 * @cfg: VF/PF mode.
 */
जोड़ nps_core_gbl_vfcfg अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64  raz :55;
		u64  ilk_disable :1;
		u64  obaf :1;
		u64  ibaf :1;
		u64  zaf :1;
		u64  aeaf :1;
		u64  seaf :1;
		u64  cfg :3;
#अन्यथा
		u64  cfg :3;
		u64  seaf :1;
		u64  aeaf :1;
		u64  zaf :1;
		u64  ibaf :1;
		u64  obaf :1;
		u64  ilk_disable :1;
		u64  raz :55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_core_पूर्णांक_active - NPS Core Interrupt Active Register
 * @resend: Resend MSI-X पूर्णांकerrupt अगर needs to handle पूर्णांकerrupts
 *    Sofware can set this bit and then निकास the ISR.
 * @ocla: Set when any OCLA(0)_INT and corresponding OCLA(0_INT_ENA_W1C
 *    bit are set
 * @mbox: Set when any NPS_PKT_MBOX_INT_LO/HI and corresponding
 *    NPS_PKT_MBOX_INT_LO_ENA_W1C/HI_ENA_W1C bits are set
 * @emu: bit i is set in [EMU] when any EMU(i)_INT bit is set
 * @bmo: Set when any BMO_INT bit is set
 * @bmi: Set when any BMI_INT bit is set or when any non-RO
 *    BMI_INT and corresponding BMI_INT_ENA_W1C bits are both set
 * @aqm: Set when any AQM_INT bit is set
 * @zqm: Set when any ZQM_INT bit is set
 * @efl: Set when any EFL_INT RO bit is set or when any non-RO EFL_INT
 *    and corresponding EFL_INT_ENA_W1C bits are both set
 * @ilk: Set when any ILK_INT bit is set
 * @lbc: Set when any LBC_INT RO bit is set or when any non-RO LBC_INT
 *    and corresponding LBC_INT_ENA_W1C bits are bot set
 * @pem: Set when any PEM(0)_INT RO bit is set or when any non-RO
 *    PEM(0)_INT and corresponding PEM(0)_INT_ENA_W1C bit are both set
 * @ucd: Set when any UCD_INT bit is set
 * @zctl: Set when any ZIP_INT RO bit is set or when any non-RO ZIP_INT
 *    and corresponding ZIP_INT_ENA_W1C bits are both set
 * @lbm: Set when any LBM_INT bit is set
 * @nps_pkt: Set when any NPS_PKT_INT bit is set
 * @nps_core: Set when any NPS_CORE_INT RO bit is set or when non-RO
 *    NPS_CORE_INT and corresponding NSP_CORE_INT_ENA_W1C bits are both set
 */
जोड़ nps_core_पूर्णांक_active अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 resend : 1;
		u64 raz	: 43;
		u64 ocla : 1;
		u64 mbox : 1;
		u64 emu	: 4;
		u64 bmo	: 1;
		u64 bmi	: 1;
		u64 aqm	: 1;
		u64 zqm	: 1;
		u64 efl	: 1;
		u64 ilk	: 1;
		u64 lbc	: 1;
		u64 pem	: 1;
		u64 pom	: 1;
		u64 ucd	: 1;
		u64 zctl : 1;
		u64 lbm	: 1;
		u64 nps_pkt : 1;
		u64 nps_core : 1;
#अन्यथा
		u64 nps_core : 1;
		u64 nps_pkt : 1;
		u64 lbm	: 1;
		u64 zctl: 1;
		u64 ucd	: 1;
		u64 pom	: 1;
		u64 pem	: 1;
		u64 lbc	: 1;
		u64 ilk	: 1;
		u64 efl	: 1;
		u64 zqm	: 1;
		u64 aqm	: 1;
		u64 bmi	: 1;
		u64 bmo	: 1;
		u64 emu	: 4;
		u64 mbox : 1;
		u64 ocla : 1;
		u64 raz	: 43;
		u64 resend : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा efl_core_पूर्णांक - EFL Interrupt Registers
 * @epci_decode_err: EPCI decoded a transacation that was unknown
 *    This error should only occurred when there is a micrcode/SE error
 *    and should be considered fatal
 * @ae_err: An AE uncorrectable error occurred.
 *    See EFL_CORE(0..3)_AE_ERR_INT
 * @se_err: An SE uncorrectable error occurred.
 *    See EFL_CORE(0..3)_SE_ERR_INT
 * @dbe: Double-bit error occurred in EFL
 * @sbe: Single-bit error occurred in EFL
 * @d_left: Asserted when new POM-Header-BMI-data is
 *    being sent to an Exec, and that Exec has Not पढ़ो all BMI
 *    data associated with the previous POM header
 * @len_ovr: Asserted when an Exec-Read is issued that is more than
 *    14 greater in length that the BMI data left to be पढ़ो
 */
जोड़ efl_core_पूर्णांक अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz	: 57;
		u64 epci_decode_err : 1;
		u64 ae_err : 1;
		u64 se_err : 1;
		u64 dbe	: 1;
		u64 sbe	: 1;
		u64 d_left : 1;
		u64 len_ovr : 1;
#अन्यथा
		u64 len_ovr : 1;
		u64 d_left : 1;
		u64 sbe	: 1;
		u64 dbe	: 1;
		u64 se_err : 1;
		u64 ae_err : 1;
		u64 epci_decode_err  : 1;
		u64 raz	: 57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा efl_core_पूर्णांक_ena_w1s - EFL core पूर्णांकerrupt enable set रेजिस्टर
 * @epci_decode_err: Reads or sets enable क्रम
 *   EFL_CORE(0..3)_INT[EPCI_DECODE_ERR].
 * @d_left: Reads or sets enable क्रम
 *   EFL_CORE(0..3)_INT[D_LEFT].
 * @len_ovr: Reads or sets enable क्रम
 *   EFL_CORE(0..3)_INT[LEN_OVR].
 */
जोड़ efl_core_पूर्णांक_ena_w1s अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_7_63 : 57;
		u64 epci_decode_err : 1;
		u64 raz_2_5 : 4;
		u64 d_left : 1;
		u64 len_ovr : 1;
#अन्यथा
		u64 len_ovr : 1;
		u64 d_left : 1;
		u64 raz_2_5 : 4;
		u64 epci_decode_err : 1;
		u64 raz_7_63 : 57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा efl_rnm_ctl_status - RNM Control and Status Register
 * @ent_sel: Select input to RNM FIFO
 * @exp_ent: Exported entropy enable क्रम अक्रमom number generator
 * @rng_rst: Reset to RNG. Setting this bit to 1 cancels the generation
 *    of the current अक्रमom number.
 * @rnm_rst: Reset the RNM. Setting this bit to 1 clears all sorted numbers
 *    in the अक्रमom number memory.
 * @rng_en: Enabled the output of the RNG.
 * @ent_en: Entropy enable क्रम अक्रमom number generator.
 */
जोड़ efl_rnm_ctl_status अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_9_63 : 55;
		u64 ent_sel : 4;
		u64 exp_ent : 1;
		u64 rng_rst : 1;
		u64 rnm_rst : 1;
		u64 rng_en : 1;
		u64 ent_en : 1;
#अन्यथा
		u64 ent_en : 1;
		u64 rng_en : 1;
		u64 rnm_rst : 1;
		u64 rng_rst : 1;
		u64 exp_ent : 1;
		u64 ent_sel : 4;
		u64 raz_9_63 : 55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा bmi_ctl - BMI control रेजिस्टर
 * @ilk_hdrq_thrsh: Maximum number of header queue locations
 *   that ILK packets may consume. When the threshold is
 *   exceeded ILK_XOFF is sent to the BMI_X2P_ARB.
 * @nps_hdrq_thrsh: Maximum number of header queue locations
 *   that NPS packets may consume. When the threshold is
 *   exceeded NPS_XOFF is sent to the BMI_X2P_ARB.
 * @totl_hdrq_thrsh: Maximum number of header queue locations
 *   that the sum of ILK and NPS packets may consume.
 * @ilk_मुक्त_thrsh: Maximum number of buffers that ILK packet
 *   flows may consume beक्रमe ILK_XOFF is sent to the BMI_X2P_ARB.
 * @nps_मुक्त_thrsh: Maximum number of buffers that NPS packet
 *   flows may consume beक्रमe NPS XOFF is sent to the BMI_X2p_ARB.
 * @totl_मुक्त_thrsh: Maximum number of buffers that bot ILK and NPS
 *   packet flows may consume beक्रमe both NPS_XOFF and ILK_XOFF
 *   are निश्चितed to the BMI_X2P_ARB.
 * @max_pkt_len: Maximum packet length, पूर्णांकegral number of 256B
 *   buffers.
 */
जोड़ bmi_ctl अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_56_63 : 8;
		u64 ilk_hdrq_thrsh : 8;
		u64 nps_hdrq_thrsh : 8;
		u64 totl_hdrq_thrsh : 8;
		u64 ilk_मुक्त_thrsh : 8;
		u64 nps_मुक्त_thrsh : 8;
		u64 totl_मुक्त_thrsh : 8;
		u64 max_pkt_len : 8;
#अन्यथा
		u64 max_pkt_len : 8;
		u64 totl_मुक्त_thrsh : 8;
		u64 nps_मुक्त_thrsh : 8;
		u64 ilk_मुक्त_thrsh : 8;
		u64 totl_hdrq_thrsh : 8;
		u64 nps_hdrq_thrsh : 8;
		u64 ilk_hdrq_thrsh : 8;
		u64 raz_56_63 : 8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा bmi_पूर्णांक_ena_w1s - BMI पूर्णांकerrupt enable set रेजिस्टर
 * @ilk_req_oflw: Reads or sets enable क्रम
 *   BMI_INT[ILK_REQ_OFLW].
 * @nps_req_oflw: Reads or sets enable क्रम
 *   BMI_INT[NPS_REQ_OFLW].
 * @fpf_undrrn: Reads or sets enable क्रम
 *   BMI_INT[FPF_UNDRRN].
 * @eop_err_ilk: Reads or sets enable क्रम
 *   BMI_INT[EOP_ERR_ILK].
 * @eop_err_nps: Reads or sets enable क्रम
 *   BMI_INT[EOP_ERR_NPS].
 * @sop_err_ilk: Reads or sets enable क्रम
 *   BMI_INT[SOP_ERR_ILK].
 * @sop_err_nps: Reads or sets enable क्रम
 *   BMI_INT[SOP_ERR_NPS].
 * @pkt_rcv_err_ilk: Reads or sets enable क्रम
 *   BMI_INT[PKT_RCV_ERR_ILK].
 * @pkt_rcv_err_nps: Reads or sets enable क्रम
 *   BMI_INT[PKT_RCV_ERR_NPS].
 * @max_len_err_ilk: Reads or sets enable क्रम
 *   BMI_INT[MAX_LEN_ERR_ILK].
 * @max_len_err_nps: Reads or sets enable क्रम
 *   BMI_INT[MAX_LEN_ERR_NPS].
 */
जोड़ bmi_पूर्णांक_ena_w1s अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_13_63	: 51;
		u64 ilk_req_oflw : 1;
		u64 nps_req_oflw : 1;
		u64 raz_10 : 1;
		u64 raz_9 : 1;
		u64 fpf_undrrn	: 1;
		u64 eop_err_ilk	: 1;
		u64 eop_err_nps	: 1;
		u64 sop_err_ilk	: 1;
		u64 sop_err_nps	: 1;
		u64 pkt_rcv_err_ilk : 1;
		u64 pkt_rcv_err_nps : 1;
		u64 max_len_err_ilk : 1;
		u64 max_len_err_nps : 1;
#अन्यथा
		u64 max_len_err_nps : 1;
		u64 max_len_err_ilk : 1;
		u64 pkt_rcv_err_nps : 1;
		u64 pkt_rcv_err_ilk : 1;
		u64 sop_err_nps	: 1;
		u64 sop_err_ilk	: 1;
		u64 eop_err_nps	: 1;
		u64 eop_err_ilk	: 1;
		u64 fpf_undrrn	: 1;
		u64 raz_9 : 1;
		u64 raz_10 : 1;
		u64 nps_req_oflw : 1;
		u64 ilk_req_oflw : 1;
		u64 raz_13_63 : 51;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा bmo_ctl2 - BMO Control2 Register
 * @arb_sel: Determines P2X Arbitration
 * @ilk_buf_thrsh: Maximum number of buffers that the
 *    ILK packet flows may consume beक्रमe ILK XOFF is
 *    निश्चितed to the POM.
 * @nps_slc_buf_thrsh: Maximum number of buffers that the
 *    NPS_SLC packet flow may consume beक्रमe NPS_SLC XOFF is
 *    निश्चितed to the POM.
 * @nps_uns_buf_thrsh: Maximum number of buffers that the
 *    NPS_UNS packet flow may consume beक्रमe NPS_UNS XOFF is
 *    निश्चितed to the POM.
 * @totl_buf_thrsh: Maximum number of buffers that ILK, NPS_UNS and
 *    NPS_SLC packet flows may consume beक्रमe NPS_UNS XOFF, NSP_SLC and
 *    ILK_XOFF are all निश्चितed POM.
 */
जोड़ bmo_ctl2 अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 arb_sel : 1;
		u64 raz_32_62 : 31;
		u64 ilk_buf_thrsh : 8;
		u64 nps_slc_buf_thrsh : 8;
		u64 nps_uns_buf_thrsh : 8;
		u64 totl_buf_thrsh : 8;
#अन्यथा
		u64 totl_buf_thrsh : 8;
		u64 nps_uns_buf_thrsh : 8;
		u64 nps_slc_buf_thrsh : 8;
		u64 ilk_buf_thrsh : 8;
		u64 raz_32_62 : 31;
		u64 arb_sel : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा pom_पूर्णांक_ena_w1s - POM पूर्णांकerrupt enable set रेजिस्टर
 * @illegal_पूर्णांकf: Reads or sets enable क्रम POM_INT[ILLEGAL_INTF].
 * @illegal_dport: Reads or sets enable क्रम POM_INT[ILLEGAL_DPORT].
 */
जोड़ pom_पूर्णांक_ena_w1s अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz2 : 60;
		u64 illegal_पूर्णांकf : 1;
		u64 illegal_dport : 1;
		u64 raz1 : 1;
		u64 raz0 : 1;
#अन्यथा
		u64 raz0 : 1;
		u64 raz1 : 1;
		u64 illegal_dport : 1;
		u64 illegal_पूर्णांकf : 1;
		u64 raz2 : 60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा lbc_inval_ctl - LBC invalidation control रेजिस्टर
 * @रुको_समयr: Wait समयr क्रम रुको state. [WAIT_TIMER] must
 *   always be written with its reset value.
 * @cam_inval_start: Software should ग_लिखो [CAM_INVAL_START]=1
 *   to initiate an LBC cache invalidation. After this, software
 *   should पढ़ो LBC_INVAL_STATUS until LBC_INVAL_STATUS[DONE] is set.
 *   LBC hardware clears [CAVM_INVAL_START] beक्रमe software can
 *   observed LBC_INVAL_STATUS[DONE] to be set
 */
जोड़ lbc_inval_ctl अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz2 : 48;
		u64 रुको_समयr : 8;
		u64 raz1 : 6;
		u64 cam_inval_start : 1;
		u64 raz0 : 1;
#अन्यथा
		u64 raz0 : 1;
		u64 cam_inval_start : 1;
		u64 raz1 : 6;
		u64 रुको_समयr : 8;
		u64 raz2 : 48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा lbc_पूर्णांक_ena_w1s - LBC पूर्णांकerrupt enable set रेजिस्टर
 * @cam_hard_err: Reads or sets enable क्रम LBC_INT[CAM_HARD_ERR].
 * @cam_inval_पात: Reads or sets enable क्रम LBC_INT[CAM_INVAL_ABORT].
 * @over_fetch_err: Reads or sets enable क्रम LBC_INT[OVER_FETCH_ERR].
 * @cache_line_to_err: Reads or sets enable क्रम
 *   LBC_INT[CACHE_LINE_TO_ERR].
 * @cam_soft_err: Reads or sets enable क्रम
 *   LBC_INT[CAM_SOFT_ERR].
 * @dma_rd_err: Reads or sets enable क्रम
 *   LBC_INT[DMA_RD_ERR].
 */
जोड़ lbc_पूर्णांक_ena_w1s अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_10_63 : 54;
		u64 cam_hard_err : 1;
		u64 cam_inval_पात : 1;
		u64 over_fetch_err : 1;
		u64 cache_line_to_err : 1;
		u64 raz_2_5 : 4;
		u64 cam_soft_err : 1;
		u64 dma_rd_err : 1;
#अन्यथा
		u64 dma_rd_err : 1;
		u64 cam_soft_err : 1;
		u64 raz_2_5 : 4;
		u64 cache_line_to_err : 1;
		u64 over_fetch_err : 1;
		u64 cam_inval_पात : 1;
		u64 cam_hard_err : 1;
		u64 raz_10_63 : 54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा lbc_पूर्णांक - LBC पूर्णांकerrupt summary रेजिस्टर
 * @cam_hard_err: indicates a fatal hardware error.
 *   It requires प्रणाली reset.
 *   When [CAM_HARD_ERR] is set, LBC stops logging any new inक्रमmation in
 *   LBC_POM_MISS_INFO_LOG,
 *   LBC_POM_MISS_ADDR_LOG,
 *   LBC_EFL_MISS_INFO_LOG, and
 *   LBC_EFL_MISS_ADDR_LOG.
 *   Software should sample them.
 * @cam_inval_पात: indicates a fatal hardware error.
 *   System reset is required.
 * @over_fetch_err: indicates a fatal hardware error
 *   System reset is required
 * @cache_line_to_err: is a debug feature.
 *   This समयout पूर्णांकerrupt bit tells the software that
 *   a cacheline in LBC has non-zero usage and the context
 *   has not been used क्रम greater than the
 *   LBC_TO_CNT[TO_CNT] समय पूर्णांकerval.
 * @sbe: Memory SBE error. This is recoverable via ECC.
 *   See LBC_ECC_INT क्रम more details.
 * @dbe: Memory DBE error. This is a fatal and requires a
 *   प्रणाली reset.
 * @pref_dat_len_mismatch_err: Summary bit क्रम context length
 *   mismatch errors.
 * @rd_dat_len_mismatch_err: Summary bit क्रम SE पढ़ो data length
 *   greater than data prefect length errors.
 * @cam_soft_err: is recoverable. Software must complete a
 *   LBC_INVAL_CTL[CAM_INVAL_START] invalidation sequence and
 *   then clear [CAM_SOFT_ERR].
 * @dma_rd_err: A context prefect पढ़ो of host memory वापसed with
 *   a पढ़ो error.
 */
जोड़ lbc_पूर्णांक अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_10_63 : 54;
		u64 cam_hard_err : 1;
		u64 cam_inval_पात : 1;
		u64 over_fetch_err : 1;
		u64 cache_line_to_err : 1;
		u64 sbe : 1;
		u64 dbe	: 1;
		u64 pref_dat_len_mismatch_err : 1;
		u64 rd_dat_len_mismatch_err : 1;
		u64 cam_soft_err : 1;
		u64 dma_rd_err : 1;
#अन्यथा
		u64 dma_rd_err : 1;
		u64 cam_soft_err : 1;
		u64 rd_dat_len_mismatch_err : 1;
		u64 pref_dat_len_mismatch_err : 1;
		u64 dbe	: 1;
		u64 sbe	: 1;
		u64 cache_line_to_err : 1;
		u64 over_fetch_err : 1;
		u64 cam_inval_पात : 1;
		u64 cam_hard_err : 1;
		u64 raz_10_63 : 54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा lbc_inval_status: LBC Invalidation status रेजिस्टर
 * @cam_clean_entry_complete_cnt: The number of entries that are
 *   cleaned up successfully.
 * @cam_clean_entry_cnt: The number of entries that have the CAM
 *   inval command issued.
 * @cam_inval_state: cam invalidation FSM state
 * @cam_inval_पात: cam invalidation पात
 * @cam_rst_rdy: lbc_cam reset पढ़ोy
 * @करोne: LBC clears [DONE] when
 *   LBC_INVAL_CTL[CAM_INVAL_START] is written with a one,
 *   and sets [DONE] when it completes the invalidation
 *   sequence.
 */
जोड़ lbc_inval_status अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz3 : 23;
		u64 cam_clean_entry_complete_cnt : 9;
		u64 raz2 : 7;
		u64 cam_clean_entry_cnt : 9;
		u64 raz1 : 5;
		u64 cam_inval_state : 3;
		u64 raz0 : 5;
		u64 cam_inval_पात : 1;
		u64 cam_rst_rdy	: 1;
		u64 करोne : 1;
#अन्यथा
		u64 करोne : 1;
		u64 cam_rst_rdy : 1;
		u64 cam_inval_पात : 1;
		u64 raz0 : 5;
		u64 cam_inval_state : 3;
		u64 raz1 : 5;
		u64 cam_clean_entry_cnt : 9;
		u64 raz2 : 7;
		u64 cam_clean_entry_complete_cnt : 9;
		u64 raz3 : 23;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा rst_boot: RST Boot Register
 * @jtcsrdis: when set, पूर्णांकernal CSR access via JTAG TAP controller
 *   is disabled
 * @jt_tst_mode: JTAG test mode
 * @io_supply: I/O घातer supply setting based on IO_VDD_SELECT pin:
 *    0x1 = 1.8V
 *    0x2 = 2.5V
 *    0x4 = 3.3V
 *    All other values are reserved
 * @pnr_mul: घड़ी multiplier
 * @lboot: last boot cause mask, resets only with PLL_DC_OK
 * @rboot: determines whether core 0 reमुख्यs in reset after
 *    chip cold or warm or soft reset
 * @rboot_pin: पढ़ो only access to REMOTE_BOOT pin
 */
जोड़ rst_boot अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_63 : 1;
		u64 jtcsrdis : 1;
		u64 raz_59_61 : 3;
		u64 jt_tst_mode : 1;
		u64 raz_40_57 : 18;
		u64 io_supply : 3;
		u64 raz_30_36 : 7;
		u64 pnr_mul : 6;
		u64 raz_12_23 : 12;
		u64 lboot : 10;
		u64 rboot : 1;
		u64 rboot_pin : 1;
#अन्यथा
		u64 rboot_pin : 1;
		u64 rboot : 1;
		u64 lboot : 10;
		u64 raz_12_23 : 12;
		u64 pnr_mul : 6;
		u64 raz_30_36 : 7;
		u64 io_supply : 3;
		u64 raz_40_57 : 18;
		u64 jt_tst_mode : 1;
		u64 raz_59_61 : 3;
		u64 jtcsrdis : 1;
		u64 raz_63 : 1;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा fus_dat1: Fuse Data 1 Register
 * @pll_mul: मुख्य घड़ी PLL multiplier hardware limit
 * @pll_half_dis: मुख्य घड़ी PLL control
 * @efus_lck: efuse lockकरोwn
 * @zip_info: ZIP inक्रमmation
 * @bar2_sz_conf: when zero, BAR2 size conक्रमms to
 *    PCIe specअगरication
 * @efus_ign: efuse ignore
 * @nozip: ZIP disable
 * @pll_alt_matrix: select alternate PLL matrix
 * @pll_bwadj_denom: select CLKF denominator क्रम
 *    BWADJ value
 * @chip_id: chip ID
 */
जोड़ fus_dat1 अणु
	u64 value;
	काष्ठा अणु
#अगर (defined(__BIG_ENDIAN_BITFIELD))
		u64 raz_57_63 : 7;
		u64 pll_mul : 3;
		u64 pll_half_dis : 1;
		u64 raz_43_52 : 10;
		u64 efus_lck : 3;
		u64 raz_26_39 : 14;
		u64 zip_info : 5;
		u64 bar2_sz_conf : 1;
		u64 efus_ign : 1;
		u64 nozip : 1;
		u64 raz_11_17 : 7;
		u64 pll_alt_matrix : 1;
		u64 pll_bwadj_denom : 2;
		u64 chip_id : 8;
#अन्यथा
		u64 chip_id : 8;
		u64 pll_bwadj_denom : 2;
		u64 pll_alt_matrix : 1;
		u64 raz_11_17 : 7;
		u64 nozip : 1;
		u64 efus_ign : 1;
		u64 bar2_sz_conf : 1;
		u64 zip_info : 5;
		u64 raz_26_39 : 14;
		u64 efus_lck : 3;
		u64 raz_43_52 : 10;
		u64 pll_half_dis : 1;
		u64 pll_mul : 3;
		u64 raz_57_63 : 7;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* __NITROX_CSR_H */
