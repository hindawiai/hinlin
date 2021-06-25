<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only OR Linux-OpenIB
/*
 * Mellanox BlueField Perक्रमmance Monitoring Counters driver
 *
 * This driver provides a sysfs पूर्णांकerface क्रम monitoring
 * perक्रमmance statistics in BlueField SoC.
 *
 * Copyright (c) 2020, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hwmon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <uapi/linux/psci.h>

#घोषणा MLXBF_PMC_WRITE_REG_32 0x82000009
#घोषणा MLXBF_PMC_READ_REG_32 0x8200000A
#घोषणा MLXBF_PMC_WRITE_REG_64 0x8200000B
#घोषणा MLXBF_PMC_READ_REG_64 0x8200000C
#घोषणा MLXBF_PMC_SIP_SVC_UID 0x8200ff01
#घोषणा MLXBF_PMC_SIP_SVC_VERSION 0x8200ff03
#घोषणा MLXBF_PMC_SVC_REQ_MAJOR 0
#घोषणा MLXBF_PMC_SVC_MIN_MINOR 3

#घोषणा MLXBF_PMC_SMCCC_ACCESS_VIOLATION -4

#घोषणा MLXBF_PMC_EVENT_SET_BF1 0
#घोषणा MLXBF_PMC_EVENT_SET_BF2 1
#घोषणा MLXBF_PMC_EVENT_INFO_LEN 100

#घोषणा MLXBF_PMC_MAX_BLOCKS 30
#घोषणा MLXBF_PMC_MAX_ATTRS 30
#घोषणा MLXBF_PMC_INFO_SZ 4
#घोषणा MLXBF_PMC_REG_SIZE 8
#घोषणा MLXBF_PMC_L3C_REG_SIZE 4

#घोषणा MLXBF_PMC_TYPE_COUNTER 1
#घोषणा MLXBF_PMC_TYPE_REGISTER 0

#घोषणा MLXBF_PMC_PERFCTL 0
#घोषणा MLXBF_PMC_PERFEVT 1
#घोषणा MLXBF_PMC_PERFACC0 4

#घोषणा MLXBF_PMC_PERFMON_CONFIG_WR_R_B BIT(0)
#घोषणा MLXBF_PMC_PERFMON_CONFIG_STROBE BIT(1)
#घोषणा MLXBF_PMC_PERFMON_CONFIG_ADDR GENMASK_ULL(4, 2)
#घोषणा MLXBF_PMC_PERFMON_CONFIG_WDATA GENMASK_ULL(60, 5)

#घोषणा MLXBF_PMC_PERFCTL_FM0 GENMASK_ULL(18, 16)
#घोषणा MLXBF_PMC_PERFCTL_MS0 GENMASK_ULL(21, 20)
#घोषणा MLXBF_PMC_PERFCTL_ACCM0 GENMASK_ULL(26, 24)
#घोषणा MLXBF_PMC_PERFCTL_AD0 BIT(27)
#घोषणा MLXBF_PMC_PERFCTL_ETRIG0 GENMASK_ULL(29, 28)
#घोषणा MLXBF_PMC_PERFCTL_EB0 BIT(30)
#घोषणा MLXBF_PMC_PERFCTL_EN0 BIT(31)

#घोषणा MLXBF_PMC_PERFEVT_EVTSEL GENMASK_ULL(31, 24)

#घोषणा MLXBF_PMC_L3C_PERF_CNT_CFG 0x0
#घोषणा MLXBF_PMC_L3C_PERF_CNT_SEL 0x10
#घोषणा MLXBF_PMC_L3C_PERF_CNT_SEL_1 0x14
#घोषणा MLXBF_PMC_L3C_PERF_CNT_LOW 0x40
#घोषणा MLXBF_PMC_L3C_PERF_CNT_HIGH 0x60

#घोषणा MLXBF_PMC_L3C_PERF_CNT_CFG_EN BIT(0)
#घोषणा MLXBF_PMC_L3C_PERF_CNT_CFG_RST BIT(1)
#घोषणा MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_0 GENMASK(5, 0)
#घोषणा MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_1 GENMASK(13, 8)
#घोषणा MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_2 GENMASK(21, 16)
#घोषणा MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_3 GENMASK(29, 24)

#घोषणा MLXBF_PMC_L3C_PERF_CNT_SEL_1_CNT_4 GENMASK(5, 0)

#घोषणा MLXBF_PMC_L3C_PERF_CNT_LOW_VAL GENMASK(31, 0)
#घोषणा MLXBF_PMC_L3C_PERF_CNT_HIGH_VAL GENMASK(24, 0)

/**
 * Structure to hold attribute and block info क्रम each sysfs entry
 * @dev_attr: Device attribute काष्ठा
 * @index: index to identअगरy counter number within a block
 * @nr: block number to which the sysfs beदीर्घs
 */
काष्ठा mlxbf_pmc_attribute अणु
	काष्ठा device_attribute dev_attr;
	पूर्णांक index;
	पूर्णांक nr;
पूर्ण;

/**
 * Structure to hold info क्रम each HW block
 *
 * @mmio_base: The VA at which the PMC block is mapped
 * @blk_size: Size of each mapped region
 * @counters: Number of counters in the block
 * @type: Type of counters in the block
 * @attr_counter: Attributes क्रम "counter" sysfs files
 * @attr_event: Attributes क्रम "event" sysfs files
 * @attr_event_list: Attributes क्रम "event_list" sysfs files
 * @attr_enable: Attributes क्रम "enable" sysfs files
 * @block_attr: All attributes needed क्रम the block
 * @blcok_attr_grp: Attribute group क्रम the block
 */
काष्ठा mlxbf_pmc_block_info अणु
	व्योम __iomem *mmio_base;
	माप_प्रकार blk_size;
	माप_प्रकार counters;
	पूर्णांक type;
	काष्ठा mlxbf_pmc_attribute *attr_counter;
	काष्ठा mlxbf_pmc_attribute *attr_event;
	काष्ठा mlxbf_pmc_attribute attr_event_list;
	काष्ठा mlxbf_pmc_attribute attr_enable;
	काष्ठा attribute *block_attr[MLXBF_PMC_MAX_ATTRS];
	काष्ठा attribute_group block_attr_grp;
पूर्ण;

/**
 * Structure to hold PMC context info
 *
 * @pdev: The kernel काष्ठाure representing the device
 * @total_blocks: Total number of blocks
 * @tile_count: Number of tiles in the प्रणाली
 * @hwmon_dev: Hwmon device क्रम bfperf
 * @block_name: Block name
 * @block:  Block info
 * @groups:  Attribute groups from each block
 * @sv_sreg_support: Whether SMCs are used to access perक्रमmance रेजिस्टरs
 * @sreg_tbl_perf: Secure रेजिस्टर access table number
 * @event_set: Event set to use
 */
काष्ठा mlxbf_pmc_context अणु
	काष्ठा platक्रमm_device *pdev;
	uपूर्णांक32_t total_blocks;
	uपूर्णांक32_t tile_count;
	काष्ठा device *hwmon_dev;
	स्थिर अक्षर *block_name[MLXBF_PMC_MAX_BLOCKS];
	काष्ठा mlxbf_pmc_block_info block[MLXBF_PMC_MAX_BLOCKS];
	स्थिर काष्ठा attribute_group *groups[MLXBF_PMC_MAX_BLOCKS];
	bool svc_sreg_support;
	uपूर्णांक32_t sreg_tbl_perf;
	अचिन्हित पूर्णांक event_set;
पूर्ण;

/**
 * Structure to hold supported events क्रम each block
 * @evt_num: Event number used to program counters
 * @evt_name: Name of the event
 */
काष्ठा mlxbf_pmc_events अणु
	पूर्णांक evt_num;
	अक्षर *evt_name;
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_pcie_events[] = अणु
	अणु 0x0, "IN_P_PKT_CNT" पूर्ण,
	अणु 0x10, "IN_NP_PKT_CNT" पूर्ण,
	अणु 0x18, "IN_C_PKT_CNT" पूर्ण,
	अणु 0x20, "OUT_P_PKT_CNT" पूर्ण,
	अणु 0x28, "OUT_NP_PKT_CNT" पूर्ण,
	अणु 0x30, "OUT_C_PKT_CNT" पूर्ण,
	अणु 0x38, "IN_P_BYTE_CNT" पूर्ण,
	अणु 0x40, "IN_NP_BYTE_CNT" पूर्ण,
	अणु 0x48, "IN_C_BYTE_CNT" पूर्ण,
	अणु 0x50, "OUT_P_BYTE_CNT" पूर्ण,
	अणु 0x58, "OUT_NP_BYTE_CNT" पूर्ण,
	अणु 0x60, "OUT_C_BYTE_CNT" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_smgen_events[] = अणु
	अणु 0x0, "AW_REQ" पूर्ण,
	अणु 0x1, "AW_BEATS" पूर्ण,
	अणु 0x2, "AW_TRANS" पूर्ण,
	अणु 0x3, "AW_RESP" पूर्ण,
	अणु 0x4, "AW_STL" पूर्ण,
	अणु 0x5, "AW_LAT" पूर्ण,
	अणु 0x6, "AW_REQ_TBU" पूर्ण,
	अणु 0x8, "AR_REQ" पूर्ण,
	अणु 0x9, "AR_BEATS" पूर्ण,
	अणु 0xa, "AR_TRANS" पूर्ण,
	अणु 0xb, "AR_STL" पूर्ण,
	अणु 0xc, "AR_LAT" पूर्ण,
	अणु 0xd, "AR_REQ_TBU" पूर्ण,
	अणु 0xe, "TBU_MISS" पूर्ण,
	अणु 0xf, "TX_DAT_AF" पूर्ण,
	अणु 0x10, "RX_DAT_AF" पूर्ण,
	अणु 0x11, "RETRYQ_CRED" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_trio_events_1[] = अणु
	अणु 0xa0, "TPIO_DATA_BEAT" पूर्ण,
	अणु 0xa1, "TDMA_DATA_BEAT" पूर्ण,
	अणु 0xa2, "MAP_DATA_BEAT" पूर्ण,
	अणु 0xa3, "TXMSG_DATA_BEAT" पूर्ण,
	अणु 0xa4, "TPIO_DATA_PACKET" पूर्ण,
	अणु 0xa5, "TDMA_DATA_PACKET" पूर्ण,
	अणु 0xa6, "MAP_DATA_PACKET" पूर्ण,
	अणु 0xa7, "TXMSG_DATA_PACKET" पूर्ण,
	अणु 0xa8, "TDMA_RT_AF" पूर्ण,
	अणु 0xa9, "TDMA_PBUF_MAC_AF" पूर्ण,
	अणु 0xaa, "TRIO_MAP_WRQ_BUF_EMPTY" पूर्ण,
	अणु 0xab, "TRIO_MAP_CPL_BUF_EMPTY" पूर्ण,
	अणु 0xac, "TRIO_MAP_RDQ0_BUF_EMPTY" पूर्ण,
	अणु 0xad, "TRIO_MAP_RDQ1_BUF_EMPTY" पूर्ण,
	अणु 0xae, "TRIO_MAP_RDQ2_BUF_EMPTY" पूर्ण,
	अणु 0xaf, "TRIO_MAP_RDQ3_BUF_EMPTY" पूर्ण,
	अणु 0xb0, "TRIO_MAP_RDQ4_BUF_EMPTY" पूर्ण,
	अणु 0xb1, "TRIO_MAP_RDQ5_BUF_EMPTY" पूर्ण,
	अणु 0xb2, "TRIO_MAP_RDQ6_BUF_EMPTY" पूर्ण,
	अणु 0xb3, "TRIO_MAP_RDQ7_BUF_EMPTY" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_trio_events_2[] = अणु
	अणु 0xa0, "TPIO_DATA_BEAT" पूर्ण,
	अणु 0xa1, "TDMA_DATA_BEAT" पूर्ण,
	अणु 0xa2, "MAP_DATA_BEAT" पूर्ण,
	अणु 0xa3, "TXMSG_DATA_BEAT" पूर्ण,
	अणु 0xa4, "TPIO_DATA_PACKET" पूर्ण,
	अणु 0xa5, "TDMA_DATA_PACKET" पूर्ण,
	अणु 0xa6, "MAP_DATA_PACKET" पूर्ण,
	अणु 0xa7, "TXMSG_DATA_PACKET" पूर्ण,
	अणु 0xa8, "TDMA_RT_AF" पूर्ण,
	अणु 0xa9, "TDMA_PBUF_MAC_AF" पूर्ण,
	अणु 0xaa, "TRIO_MAP_WRQ_BUF_EMPTY" पूर्ण,
	अणु 0xab, "TRIO_MAP_CPL_BUF_EMPTY" पूर्ण,
	अणु 0xac, "TRIO_MAP_RDQ0_BUF_EMPTY" पूर्ण,
	अणु 0xad, "TRIO_MAP_RDQ1_BUF_EMPTY" पूर्ण,
	अणु 0xae, "TRIO_MAP_RDQ2_BUF_EMPTY" पूर्ण,
	अणु 0xaf, "TRIO_MAP_RDQ3_BUF_EMPTY" पूर्ण,
	अणु 0xb0, "TRIO_MAP_RDQ4_BUF_EMPTY" पूर्ण,
	अणु 0xb1, "TRIO_MAP_RDQ5_BUF_EMPTY" पूर्ण,
	अणु 0xb2, "TRIO_MAP_RDQ6_BUF_EMPTY" पूर्ण,
	अणु 0xb3, "TRIO_MAP_RDQ7_BUF_EMPTY" पूर्ण,
	अणु 0xb4, "TRIO_RING_TX_FLIT_CH0" पूर्ण,
	अणु 0xb5, "TRIO_RING_TX_FLIT_CH1" पूर्ण,
	अणु 0xb6, "TRIO_RING_TX_FLIT_CH2" पूर्ण,
	अणु 0xb7, "TRIO_RING_TX_FLIT_CH3" पूर्ण,
	अणु 0xb8, "TRIO_RING_TX_FLIT_CH4" पूर्ण,
	अणु 0xb9, "TRIO_RING_RX_FLIT_CH0" पूर्ण,
	अणु 0xba, "TRIO_RING_RX_FLIT_CH1" पूर्ण,
	अणु 0xbb, "TRIO_RING_RX_FLIT_CH2" पूर्ण,
	अणु 0xbc, "TRIO_RING_RX_FLIT_CH3" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_ecc_events[] = अणु
	अणु 0x100, "ECC_SINGLE_ERROR_CNT" पूर्ण,
	अणु 0x104, "ECC_DOUBLE_ERROR_CNT" पूर्ण,
	अणु 0x114, "SERR_INJ" पूर्ण,
	अणु 0x118, "DERR_INJ" पूर्ण,
	अणु 0x124, "ECC_SINGLE_ERROR_0" पूर्ण,
	अणु 0x164, "ECC_DOUBLE_ERROR_0" पूर्ण,
	अणु 0x340, "DRAM_ECC_COUNT" पूर्ण,
	अणु 0x344, "DRAM_ECC_INJECT" पूर्ण,
	अणु 0x348, "DRAM_ECC_ERROR" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_mss_events[] = अणु
	अणु 0xc0, "RXREQ_MSS" पूर्ण,
	अणु 0xc1, "RXDAT_MSS" पूर्ण,
	अणु 0xc2, "TXRSP_MSS" पूर्ण,
	अणु 0xc3, "TXDAT_MSS" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_hnf_events[] = अणु
	अणु 0x45, "HNF_REQUESTS" पूर्ण,
	अणु 0x46, "HNF_REJECTS" पूर्ण,
	अणु 0x47, "ALL_BUSY" पूर्ण,
	अणु 0x48, "MAF_BUSY" पूर्ण,
	अणु 0x49, "MAF_REQUESTS" पूर्ण,
	अणु 0x4a, "RNF_REQUESTS" पूर्ण,
	अणु 0x4b, "REQUEST_TYPE" पूर्ण,
	अणु 0x4c, "MEMORY_READS" पूर्ण,
	अणु 0x4d, "MEMORY_WRITES" पूर्ण,
	अणु 0x4e, "VICTIM_WRITE" पूर्ण,
	अणु 0x4f, "POC_FULL" पूर्ण,
	अणु 0x50, "POC_FAIL" पूर्ण,
	अणु 0x51, "POC_SUCCESS" पूर्ण,
	अणु 0x52, "POC_WRITES" पूर्ण,
	अणु 0x53, "POC_READS" पूर्ण,
	अणु 0x54, "FORWARD" पूर्ण,
	अणु 0x55, "RXREQ_HNF" पूर्ण,
	अणु 0x56, "RXRSP_HNF" पूर्ण,
	अणु 0x57, "RXDAT_HNF" पूर्ण,
	अणु 0x58, "TXREQ_HNF" पूर्ण,
	अणु 0x59, "TXRSP_HNF" पूर्ण,
	अणु 0x5a, "TXDAT_HNF" पूर्ण,
	अणु 0x5b, "TXSNP_HNF" पूर्ण,
	अणु 0x5c, "INDEX_MATCH" पूर्ण,
	अणु 0x5d, "A72_ACCESS" पूर्ण,
	अणु 0x5e, "IO_ACCESS" पूर्ण,
	अणु 0x5f, "TSO_WRITE" पूर्ण,
	अणु 0x60, "TSO_CONFLICT" पूर्ण,
	अणु 0x61, "DIR_HIT" पूर्ण,
	अणु 0x62, "HNF_ACCEPTS" पूर्ण,
	अणु 0x63, "REQ_BUF_EMPTY" पूर्ण,
	अणु 0x64, "REQ_BUF_IDLE_MAF" पूर्ण,
	अणु 0x65, "TSO_NOARB" पूर्ण,
	अणु 0x66, "TSO_NOARB_CYCLES" पूर्ण,
	अणु 0x67, "MSS_NO_CREDIT" पूर्ण,
	अणु 0x68, "TXDAT_NO_LCRD" पूर्ण,
	अणु 0x69, "TXSNP_NO_LCRD" पूर्ण,
	अणु 0x6a, "TXRSP_NO_LCRD" पूर्ण,
	अणु 0x6b, "TXREQ_NO_LCRD" पूर्ण,
	अणु 0x6c, "TSO_CL_MATCH" पूर्ण,
	अणु 0x6d, "MEMORY_READS_BYPASS" पूर्ण,
	अणु 0x6e, "TSO_NOARB_TIMEOUT" पूर्ण,
	अणु 0x6f, "ALLOCATE" पूर्ण,
	अणु 0x70, "VICTIM" पूर्ण,
	अणु 0x71, "A72_WRITE" पूर्ण,
	अणु 0x72, "A72_READ" पूर्ण,
	अणु 0x73, "IO_WRITE" पूर्ण,
	अणु 0x74, "IO_READ" पूर्ण,
	अणु 0x75, "TSO_REJECT" पूर्ण,
	अणु 0x80, "TXREQ_RN" पूर्ण,
	अणु 0x81, "TXRSP_RN" पूर्ण,
	अणु 0x82, "TXDAT_RN" पूर्ण,
	अणु 0x83, "RXSNP_RN" पूर्ण,
	अणु 0x84, "RXRSP_RN" पूर्ण,
	अणु 0x85, "RXDAT_RN" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_hnfnet_events[] = अणु
	अणु 0x12, "CDN_REQ" पूर्ण,
	अणु 0x13, "DDN_REQ" पूर्ण,
	अणु 0x14, "NDN_REQ" पूर्ण,
	अणु 0x15, "CDN_DIAG_N_OUT_OF_CRED" पूर्ण,
	अणु 0x16, "CDN_DIAG_S_OUT_OF_CRED" पूर्ण,
	अणु 0x17, "CDN_DIAG_E_OUT_OF_CRED" पूर्ण,
	अणु 0x18, "CDN_DIAG_W_OUT_OF_CRED" पूर्ण,
	अणु 0x19, "CDN_DIAG_C_OUT_OF_CRED" पूर्ण,
	अणु 0x1a, "CDN_DIAG_N_EGRESS" पूर्ण,
	अणु 0x1b, "CDN_DIAG_S_EGRESS" पूर्ण,
	अणु 0x1c, "CDN_DIAG_E_EGRESS" पूर्ण,
	अणु 0x1d, "CDN_DIAG_W_EGRESS" पूर्ण,
	अणु 0x1e, "CDN_DIAG_C_EGRESS" पूर्ण,
	अणु 0x1f, "CDN_DIAG_N_INGRESS" पूर्ण,
	अणु 0x20, "CDN_DIAG_S_INGRESS" पूर्ण,
	अणु 0x21, "CDN_DIAG_E_INGRESS" पूर्ण,
	अणु 0x22, "CDN_DIAG_W_INGRESS" पूर्ण,
	अणु 0x23, "CDN_DIAG_C_INGRESS" पूर्ण,
	अणु 0x24, "CDN_DIAG_CORE_SENT" पूर्ण,
	अणु 0x25, "DDN_DIAG_N_OUT_OF_CRED" पूर्ण,
	अणु 0x26, "DDN_DIAG_S_OUT_OF_CRED" पूर्ण,
	अणु 0x27, "DDN_DIAG_E_OUT_OF_CRED" पूर्ण,
	अणु 0x28, "DDN_DIAG_W_OUT_OF_CRED" पूर्ण,
	अणु 0x29, "DDN_DIAG_C_OUT_OF_CRED" पूर्ण,
	अणु 0x2a, "DDN_DIAG_N_EGRESS" पूर्ण,
	अणु 0x2b, "DDN_DIAG_S_EGRESS" पूर्ण,
	अणु 0x2c, "DDN_DIAG_E_EGRESS" पूर्ण,
	अणु 0x2d, "DDN_DIAG_W_EGRESS" पूर्ण,
	अणु 0x2e, "DDN_DIAG_C_EGRESS" पूर्ण,
	अणु 0x2f, "DDN_DIAG_N_INGRESS" पूर्ण,
	अणु 0x30, "DDN_DIAG_S_INGRESS" पूर्ण,
	अणु 0x31, "DDN_DIAG_E_INGRESS" पूर्ण,
	अणु 0x32, "DDN_DIAG_W_INGRESS" पूर्ण,
	अणु 0x33, "DDN_DIAG_C_INGRESS" पूर्ण,
	अणु 0x34, "DDN_DIAG_CORE_SENT" पूर्ण,
	अणु 0x35, "NDN_DIAG_S_OUT_OF_CRED" पूर्ण,
	अणु 0x36, "NDN_DIAG_S_OUT_OF_CRED" पूर्ण,
	अणु 0x37, "NDN_DIAG_E_OUT_OF_CRED" पूर्ण,
	अणु 0x38, "NDN_DIAG_W_OUT_OF_CRED" पूर्ण,
	अणु 0x39, "NDN_DIAG_C_OUT_OF_CRED" पूर्ण,
	अणु 0x3a, "NDN_DIAG_N_EGRESS" पूर्ण,
	अणु 0x3b, "NDN_DIAG_S_EGRESS" पूर्ण,
	अणु 0x3c, "NDN_DIAG_E_EGRESS" पूर्ण,
	अणु 0x3d, "NDN_DIAG_W_EGRESS" पूर्ण,
	अणु 0x3e, "NDN_DIAG_C_EGRESS" पूर्ण,
	अणु 0x3f, "NDN_DIAG_N_INGRESS" पूर्ण,
	अणु 0x40, "NDN_DIAG_S_INGRESS" पूर्ण,
	अणु 0x41, "NDN_DIAG_E_INGRESS" पूर्ण,
	अणु 0x42, "NDN_DIAG_W_INGRESS" पूर्ण,
	अणु 0x43, "NDN_DIAG_C_INGRESS" पूर्ण,
	अणु 0x44, "NDN_DIAG_CORE_SENT" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxbf_pmc_events mlxbf_pmc_l3c_events[] = अणु
	अणु 0x00, "DISABLE" पूर्ण,
	अणु 0x01, "CYCLES" पूर्ण,
	अणु 0x02, "TOTAL_RD_REQ_IN" पूर्ण,
	अणु 0x03, "TOTAL_WR_REQ_IN" पूर्ण,
	अणु 0x04, "TOTAL_WR_DBID_ACK" पूर्ण,
	अणु 0x05, "TOTAL_WR_DATA_IN" पूर्ण,
	अणु 0x06, "TOTAL_WR_COMP" पूर्ण,
	अणु 0x07, "TOTAL_RD_DATA_OUT" पूर्ण,
	अणु 0x08, "TOTAL_CDN_REQ_IN_BANK0" पूर्ण,
	अणु 0x09, "TOTAL_CDN_REQ_IN_BANK1" पूर्ण,
	अणु 0x0a, "TOTAL_DDN_REQ_IN_BANK0" पूर्ण,
	अणु 0x0b, "TOTAL_DDN_REQ_IN_BANK1" पूर्ण,
	अणु 0x0c, "TOTAL_EMEM_RD_RES_IN_BANK0" पूर्ण,
	अणु 0x0d, "TOTAL_EMEM_RD_RES_IN_BANK1" पूर्ण,
	अणु 0x0e, "TOTAL_CACHE_RD_RES_IN_BANK0" पूर्ण,
	अणु 0x0f, "TOTAL_CACHE_RD_RES_IN_BANK1" पूर्ण,
	अणु 0x10, "TOTAL_EMEM_RD_REQ_BANK0" पूर्ण,
	अणु 0x11, "TOTAL_EMEM_RD_REQ_BANK1" पूर्ण,
	अणु 0x12, "TOTAL_EMEM_WR_REQ_BANK0" पूर्ण,
	अणु 0x13, "TOTAL_EMEM_WR_REQ_BANK1" पूर्ण,
	अणु 0x14, "TOTAL_RD_REQ_OUT" पूर्ण,
	अणु 0x15, "TOTAL_WR_REQ_OUT" पूर्ण,
	अणु 0x16, "TOTAL_RD_RES_IN" पूर्ण,
	अणु 0x17, "HITS_BANK0" पूर्ण,
	अणु 0x18, "HITS_BANK1" पूर्ण,
	अणु 0x19, "MISSES_BANK0" पूर्ण,
	अणु 0x1a, "MISSES_BANK1" पूर्ण,
	अणु 0x1b, "ALLOCATIONS_BANK0" पूर्ण,
	अणु 0x1c, "ALLOCATIONS_BANK1" पूर्ण,
	अणु 0x1d, "EVICTIONS_BANK0" पूर्ण,
	अणु 0x1e, "EVICTIONS_BANK1" पूर्ण,
	अणु 0x1f, "DBID_REJECT" पूर्ण,
	अणु 0x20, "WRDB_REJECT_BANK0" पूर्ण,
	अणु 0x21, "WRDB_REJECT_BANK1" पूर्ण,
	अणु 0x22, "CMDQ_REJECT_BANK0" पूर्ण,
	अणु 0x23, "CMDQ_REJECT_BANK1" पूर्ण,
	अणु 0x24, "COB_REJECT_BANK0" पूर्ण,
	अणु 0x25, "COB_REJECT_BANK1" पूर्ण,
	अणु 0x26, "TRB_REJECT_BANK0" पूर्ण,
	अणु 0x27, "TRB_REJECT_BANK1" पूर्ण,
	अणु 0x28, "TAG_REJECT_BANK0" पूर्ण,
	अणु 0x29, "TAG_REJECT_BANK1" पूर्ण,
	अणु 0x2a, "ANY_REJECT_BANK0" पूर्ण,
	अणु 0x2b, "ANY_REJECT_BANK1" पूर्ण,
पूर्ण;

अटल काष्ठा mlxbf_pmc_context *pmc;

/* UUID used to probe ATF service. */
अटल स्थिर अक्षर *mlxbf_pmc_svc_uuid_str = "89c036b4-e7d7-11e6-8797-001aca00bfc4";

/* Calls an SMC to access a perक्रमmance रेजिस्टर */
अटल पूर्णांक mlxbf_pmc_secure_पढ़ो(व्योम __iomem *addr, uपूर्णांक32_t command,
				 uपूर्णांक64_t *result)
अणु
	काष्ठा arm_smccc_res res;
	पूर्णांक status, err = 0;

	arm_smccc_smc(command, pmc->sreg_tbl_perf, (uपूर्णांकptr_t)addr, 0, 0, 0, 0,
		      0, &res);

	status = res.a0;

	चयन (status) अणु
	हाल PSCI_RET_NOT_SUPPORTED:
		err = -EINVAL;
		अवरोध;
	हाल MLXBF_PMC_SMCCC_ACCESS_VIOLATION:
		err = -EACCES;
		अवरोध;
	शेष:
		*result = res.a1;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Read from a perक्रमmance counter */
अटल पूर्णांक mlxbf_pmc_पढ़ो(व्योम __iomem *addr, uपूर्णांक32_t command,
			  uपूर्णांक64_t *result)
अणु
	अगर (pmc->svc_sreg_support)
		वापस mlxbf_pmc_secure_पढ़ो(addr, command, result);

	अगर (command == MLXBF_PMC_READ_REG_32)
		*result = पढ़ोl(addr);
	अन्यथा
		*result = पढ़ोq(addr);

	वापस 0;
पूर्ण

/* Convenience function क्रम 32-bit पढ़ोs */
अटल पूर्णांक mlxbf_pmc_पढ़ोl(व्योम __iomem *addr, uपूर्णांक32_t *result)
अणु
	uपूर्णांक64_t पढ़ो_out;
	पूर्णांक status;

	status = mlxbf_pmc_पढ़ो(addr, MLXBF_PMC_READ_REG_32, &पढ़ो_out);
	अगर (status)
		वापस status;
	*result = (uपूर्णांक32_t)पढ़ो_out;

	वापस 0;
पूर्ण

/* Calls an SMC to access a perक्रमmance रेजिस्टर */
अटल पूर्णांक mlxbf_pmc_secure_ग_लिखो(व्योम __iomem *addr, uपूर्णांक32_t command,
				  uपूर्णांक64_t value)
अणु
	काष्ठा arm_smccc_res res;
	पूर्णांक status, err = 0;

	arm_smccc_smc(command, pmc->sreg_tbl_perf, value, (uपूर्णांकptr_t)addr, 0, 0,
		      0, 0, &res);

	status = res.a0;

	चयन (status) अणु
	हाल PSCI_RET_NOT_SUPPORTED:
		err = -EINVAL;
		अवरोध;
	हाल MLXBF_PMC_SMCCC_ACCESS_VIOLATION:
		err = -EACCES;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Write to a perक्रमmance counter */
अटल पूर्णांक mlxbf_pmc_ग_लिखो(व्योम __iomem *addr, पूर्णांक command, uपूर्णांक64_t value)
अणु
	अगर (pmc->svc_sreg_support)
		वापस mlxbf_pmc_secure_ग_लिखो(addr, command, value);

	अगर (command == MLXBF_PMC_WRITE_REG_32)
		ग_लिखोl(value, addr);
	अन्यथा
		ग_लिखोq(value, addr);

	वापस 0;
पूर्ण

/* Check अगर the रेजिस्टर offset is within the mapped region क्रम the block */
अटल bool mlxbf_pmc_valid_range(पूर्णांक blk_num, uपूर्णांक32_t offset)
अणु
	अगर ((offset >= 0) && !(offset % MLXBF_PMC_REG_SIZE) &&
	    (offset + MLXBF_PMC_REG_SIZE <= pmc->block[blk_num].blk_size))
		वापस true; /* inside the mapped PMC space */

	वापस false;
पूर्ण

/* Get the event list corresponding to a certain block */
अटल स्थिर काष्ठा mlxbf_pmc_events *mlxbf_pmc_event_list(स्थिर अक्षर *blk,
							   पूर्णांक *size)
अणु
	स्थिर काष्ठा mlxbf_pmc_events *events;

	अगर (म_माला(blk, "tilenet")) अणु
		events = mlxbf_pmc_hnfnet_events;
		*size = ARRAY_SIZE(mlxbf_pmc_hnfnet_events);
	पूर्ण अन्यथा अगर (म_माला(blk, "tile")) अणु
		events = mlxbf_pmc_hnf_events;
		*size = ARRAY_SIZE(mlxbf_pmc_hnf_events);
	पूर्ण अन्यथा अगर (म_माला(blk, "triogen")) अणु
		events = mlxbf_pmc_smgen_events;
		*size = ARRAY_SIZE(mlxbf_pmc_smgen_events);
	पूर्ण अन्यथा अगर (म_माला(blk, "trio")) अणु
		चयन (pmc->event_set) अणु
		हाल MLXBF_PMC_EVENT_SET_BF1:
			events = mlxbf_pmc_trio_events_1;
			*size = ARRAY_SIZE(mlxbf_pmc_trio_events_1);
			अवरोध;
		हाल MLXBF_PMC_EVENT_SET_BF2:
			events = mlxbf_pmc_trio_events_2;
			*size = ARRAY_SIZE(mlxbf_pmc_trio_events_2);
			अवरोध;
		शेष:
			events = शून्य;
			*size = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (म_माला(blk, "mss")) अणु
		events = mlxbf_pmc_mss_events;
		*size = ARRAY_SIZE(mlxbf_pmc_mss_events);
	पूर्ण अन्यथा अगर (म_माला(blk, "ecc")) अणु
		events = mlxbf_pmc_ecc_events;
		*size = ARRAY_SIZE(mlxbf_pmc_ecc_events);
	पूर्ण अन्यथा अगर (म_माला(blk, "pcie")) अणु
		events = mlxbf_pmc_pcie_events;
		*size = ARRAY_SIZE(mlxbf_pmc_pcie_events);
	पूर्ण अन्यथा अगर (म_माला(blk, "l3cache")) अणु
		events = mlxbf_pmc_l3c_events;
		*size = ARRAY_SIZE(mlxbf_pmc_l3c_events);
	पूर्ण अन्यथा अगर (म_माला(blk, "gic")) अणु
		events = mlxbf_pmc_smgen_events;
		*size = ARRAY_SIZE(mlxbf_pmc_smgen_events);
	पूर्ण अन्यथा अगर (म_माला(blk, "smmu")) अणु
		events = mlxbf_pmc_smgen_events;
		*size = ARRAY_SIZE(mlxbf_pmc_smgen_events);
	पूर्ण अन्यथा अणु
		events = शून्य;
		*size = 0;
	पूर्ण

	वापस events;
पूर्ण

/* Get the event number given the name */
अटल पूर्णांक mlxbf_pmc_get_event_num(स्थिर अक्षर *blk, स्थिर अक्षर *evt)
अणु
	स्थिर काष्ठा mlxbf_pmc_events *events;
	पूर्णांक i, size;

	events = mlxbf_pmc_event_list(blk, &size);
	अगर (!events)
		वापस -EINVAL;

	क्रम (i = 0; i < size; ++i) अणु
		अगर (!म_भेद(evt, events[i].evt_name))
			वापस events[i].evt_num;
	पूर्ण

	वापस -ENODEV;
पूर्ण

/* Get the event number given the name */
अटल अक्षर *mlxbf_pmc_get_event_name(स्थिर अक्षर *blk, पूर्णांक evt)
अणु
	स्थिर काष्ठा mlxbf_pmc_events *events;
	पूर्णांक i, size;

	events = mlxbf_pmc_event_list(blk, &size);
	अगर (!events)
		वापस शून्य;

	क्रम (i = 0; i < size; ++i) अणु
		अगर (evt == events[i].evt_num)
			वापस events[i].evt_name;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Method to enable/disable/reset l3cache counters */
अटल पूर्णांक mlxbf_pmc_config_l3_counters(पूर्णांक blk_num, bool enable, bool reset)
अणु
	uपूर्णांक32_t perfcnt_cfg = 0;

	अगर (enable)
		perfcnt_cfg |= MLXBF_PMC_L3C_PERF_CNT_CFG_EN;
	अगर (reset)
		perfcnt_cfg |= MLXBF_PMC_L3C_PERF_CNT_CFG_RST;

	वापस mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base +
				       MLXBF_PMC_L3C_PERF_CNT_CFG,
			       MLXBF_PMC_WRITE_REG_32, perfcnt_cfg);
पूर्ण

/* Method to handle l3cache counter programming */
अटल पूर्णांक mlxbf_pmc_program_l3_counter(पूर्णांक blk_num, uपूर्णांक32_t cnt_num,
					uपूर्णांक32_t evt)
अणु
	uपूर्णांक32_t perfcnt_sel_1 = 0;
	uपूर्णांक32_t perfcnt_sel = 0;
	uपूर्णांक32_t *wordaddr;
	व्योम __iomem *pmcaddr;
	पूर्णांक ret;

	/* Disable all counters beक्रमe programming them */
	अगर (mlxbf_pmc_config_l3_counters(blk_num, false, false))
		वापस -EINVAL;

	/* Select appropriate रेजिस्टर inक्रमmation */
	चयन (cnt_num) अणु
	हाल 0 ... 3:
		pmcaddr = pmc->block[blk_num].mmio_base +
			  MLXBF_PMC_L3C_PERF_CNT_SEL;
		wordaddr = &perfcnt_sel;
		अवरोध;
	हाल 4:
		pmcaddr = pmc->block[blk_num].mmio_base +
			  MLXBF_PMC_L3C_PERF_CNT_SEL_1;
		wordaddr = &perfcnt_sel_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = mlxbf_pmc_पढ़ोl(pmcaddr, wordaddr);
	अगर (ret)
		वापस ret;

	चयन (cnt_num) अणु
	हाल 0:
		perfcnt_sel &= ~MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_0;
		perfcnt_sel |= FIELD_PREP(MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_0,
					  evt);
		अवरोध;
	हाल 1:
		perfcnt_sel &= ~MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_1;
		perfcnt_sel |= FIELD_PREP(MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_1,
					  evt);
		अवरोध;
	हाल 2:
		perfcnt_sel &= ~MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_2;
		perfcnt_sel |= FIELD_PREP(MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_2,
					  evt);
		अवरोध;
	हाल 3:
		perfcnt_sel &= ~MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_3;
		perfcnt_sel |= FIELD_PREP(MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_3,
					  evt);
		अवरोध;
	हाल 4:
		perfcnt_sel_1 &= ~MLXBF_PMC_L3C_PERF_CNT_SEL_1_CNT_4;
		perfcnt_sel_1 |= FIELD_PREP(MLXBF_PMC_L3C_PERF_CNT_SEL_1_CNT_4,
					    evt);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mlxbf_pmc_ग_लिखो(pmcaddr, MLXBF_PMC_WRITE_REG_32, *wordaddr);
पूर्ण

/* Method to program a counter to monitor an event */
अटल पूर्णांक mlxbf_pmc_program_counter(पूर्णांक blk_num, uपूर्णांक32_t cnt_num,
				     uपूर्णांक32_t evt, bool is_l3)
अणु
	uपूर्णांक64_t perfctl, perfevt, perfmon_cfg;

	अगर (cnt_num >= pmc->block[blk_num].counters)
		वापस -ENODEV;

	अगर (is_l3)
		वापस mlxbf_pmc_program_l3_counter(blk_num, cnt_num, evt);

	/* Configure the counter */
	perfctl = FIELD_PREP(MLXBF_PMC_PERFCTL_EN0, 1);
	perfctl |= FIELD_PREP(MLXBF_PMC_PERFCTL_EB0, 0);
	perfctl |= FIELD_PREP(MLXBF_PMC_PERFCTL_ETRIG0, 1);
	perfctl |= FIELD_PREP(MLXBF_PMC_PERFCTL_AD0, 0);
	perfctl |= FIELD_PREP(MLXBF_PMC_PERFCTL_ACCM0, 0);
	perfctl |= FIELD_PREP(MLXBF_PMC_PERFCTL_MS0, 0);
	perfctl |= FIELD_PREP(MLXBF_PMC_PERFCTL_FM0, 0);

	perfmon_cfg = FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_WDATA, perfctl);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_ADDR,
				  MLXBF_PMC_PERFCTL);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_STROBE, 1);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_WR_R_B, 1);

	अगर (mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base +
				    cnt_num * MLXBF_PMC_REG_SIZE,
			    MLXBF_PMC_WRITE_REG_64, perfmon_cfg))
		वापस -EFAULT;

	/* Select the event */
	perfevt = FIELD_PREP(MLXBF_PMC_PERFEVT_EVTSEL, evt);

	perfmon_cfg = FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_WDATA, perfevt);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_ADDR,
				  MLXBF_PMC_PERFEVT);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_STROBE, 1);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_WR_R_B, 1);

	अगर (mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base +
				    cnt_num * MLXBF_PMC_REG_SIZE,
			    MLXBF_PMC_WRITE_REG_64, perfmon_cfg))
		वापस -EFAULT;

	/* Clear the accumulator */
	perfmon_cfg = FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_ADDR,
				 MLXBF_PMC_PERFACC0);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_STROBE, 1);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_WR_R_B, 1);

	अगर (mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base +
				    cnt_num * MLXBF_PMC_REG_SIZE,
			    MLXBF_PMC_WRITE_REG_64, perfmon_cfg))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* Method to handle l3 counter पढ़ोs */
अटल पूर्णांक mlxbf_pmc_पढ़ो_l3_counter(पूर्णांक blk_num, uपूर्णांक32_t cnt_num,
				     uपूर्णांक64_t *result)
अणु
	uपूर्णांक32_t perfcnt_low = 0, perfcnt_high = 0;
	uपूर्णांक64_t value;
	पूर्णांक status = 0;

	status = mlxbf_pmc_पढ़ोl(pmc->block[blk_num].mmio_base +
					 MLXBF_PMC_L3C_PERF_CNT_LOW +
					 cnt_num * MLXBF_PMC_L3C_REG_SIZE,
				 &perfcnt_low);

	अगर (status)
		वापस status;

	status = mlxbf_pmc_पढ़ोl(pmc->block[blk_num].mmio_base +
					 MLXBF_PMC_L3C_PERF_CNT_HIGH +
					 cnt_num * MLXBF_PMC_L3C_REG_SIZE,
				 &perfcnt_high);

	अगर (status)
		वापस status;

	value = perfcnt_high;
	value = value << 32;
	value |= perfcnt_low;
	*result = value;

	वापस 0;
पूर्ण

/* Method to पढ़ो the counter value */
अटल पूर्णांक mlxbf_pmc_पढ़ो_counter(पूर्णांक blk_num, uपूर्णांक32_t cnt_num, bool is_l3,
				  uपूर्णांक64_t *result)
अणु
	uपूर्णांक32_t perfcfg_offset, perfval_offset;
	uपूर्णांक64_t perfmon_cfg;
	पूर्णांक status;

	अगर (cnt_num >= pmc->block[blk_num].counters)
		वापस -EINVAL;

	अगर (is_l3)
		वापस mlxbf_pmc_पढ़ो_l3_counter(blk_num, cnt_num, result);

	perfcfg_offset = cnt_num * MLXBF_PMC_REG_SIZE;
	perfval_offset = perfcfg_offset +
			 pmc->block[blk_num].counters * MLXBF_PMC_REG_SIZE;

	/* Set counter in "read" mode */
	perfmon_cfg = FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_ADDR,
				 MLXBF_PMC_PERFACC0);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_STROBE, 1);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_WR_R_B, 0);

	status = mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base + perfcfg_offset,
				 MLXBF_PMC_WRITE_REG_64, perfmon_cfg);

	अगर (status)
		वापस status;

	/* Get the counter value */
	वापस mlxbf_pmc_पढ़ो(pmc->block[blk_num].mmio_base + perfval_offset,
			      MLXBF_PMC_READ_REG_64, result);
पूर्ण

/* Method to पढ़ो L3 block event */
अटल पूर्णांक mlxbf_pmc_पढ़ो_l3_event(पूर्णांक blk_num, uपूर्णांक32_t cnt_num,
				   uपूर्णांक64_t *result)
अणु
	uपूर्णांक32_t perfcnt_sel = 0, perfcnt_sel_1 = 0;
	uपूर्णांक32_t *wordaddr;
	व्योम __iomem *pmcaddr;
	uपूर्णांक64_t evt;

	/* Select appropriate रेजिस्टर inक्रमmation */
	चयन (cnt_num) अणु
	हाल 0 ... 3:
		pmcaddr = pmc->block[blk_num].mmio_base +
			  MLXBF_PMC_L3C_PERF_CNT_SEL;
		wordaddr = &perfcnt_sel;
		अवरोध;
	हाल 4:
		pmcaddr = pmc->block[blk_num].mmio_base +
			  MLXBF_PMC_L3C_PERF_CNT_SEL_1;
		wordaddr = &perfcnt_sel_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (mlxbf_pmc_पढ़ोl(pmcaddr, wordaddr))
		वापस -EINVAL;

	/* Read from appropriate रेजिस्टर field क्रम the counter */
	चयन (cnt_num) अणु
	हाल 0:
		evt = FIELD_GET(MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_0, perfcnt_sel);
		अवरोध;
	हाल 1:
		evt = FIELD_GET(MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_1, perfcnt_sel);
		अवरोध;
	हाल 2:
		evt = FIELD_GET(MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_2, perfcnt_sel);
		अवरोध;
	हाल 3:
		evt = FIELD_GET(MLXBF_PMC_L3C_PERF_CNT_SEL_CNT_3, perfcnt_sel);
		अवरोध;
	हाल 4:
		evt = FIELD_GET(MLXBF_PMC_L3C_PERF_CNT_SEL_1_CNT_4,
				perfcnt_sel_1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	*result = evt;

	वापस 0;
पूर्ण

/* Method to find the event currently being monitored by a counter */
अटल पूर्णांक mlxbf_pmc_पढ़ो_event(पूर्णांक blk_num, uपूर्णांक32_t cnt_num, bool is_l3,
				uपूर्णांक64_t *result)
अणु
	uपूर्णांक32_t perfcfg_offset, perfval_offset;
	uपूर्णांक64_t perfmon_cfg, perfevt, perfctl;

	अगर (cnt_num >= pmc->block[blk_num].counters)
		वापस -EINVAL;

	अगर (is_l3)
		वापस mlxbf_pmc_पढ़ो_l3_event(blk_num, cnt_num, result);

	perfcfg_offset = cnt_num * MLXBF_PMC_REG_SIZE;
	perfval_offset = perfcfg_offset +
			 pmc->block[blk_num].counters * MLXBF_PMC_REG_SIZE;

	/* Set counter in "read" mode */
	perfmon_cfg = FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_ADDR,
				 MLXBF_PMC_PERFCTL);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_STROBE, 1);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_WR_R_B, 0);

	अगर (mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base + perfcfg_offset,
			    MLXBF_PMC_WRITE_REG_64, perfmon_cfg))
		वापस -EFAULT;

	/* Check अगर the counter is enabled */

	अगर (mlxbf_pmc_पढ़ो(pmc->block[blk_num].mmio_base + perfval_offset,
			   MLXBF_PMC_READ_REG_64, &perfctl))
		वापस -EFAULT;

	अगर (!FIELD_GET(MLXBF_PMC_PERFCTL_EN0, perfctl))
		वापस -EINVAL;

	/* Set counter in "read" mode */
	perfmon_cfg = FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_ADDR,
				 MLXBF_PMC_PERFEVT);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_STROBE, 1);
	perfmon_cfg |= FIELD_PREP(MLXBF_PMC_PERFMON_CONFIG_WR_R_B, 0);

	अगर (mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base + perfcfg_offset,
			    MLXBF_PMC_WRITE_REG_64, perfmon_cfg))
		वापस -EFAULT;

	/* Get the event number */
	अगर (mlxbf_pmc_पढ़ो(pmc->block[blk_num].mmio_base + perfval_offset,
			   MLXBF_PMC_READ_REG_64, &perfevt))
		वापस -EFAULT;

	*result = FIELD_GET(MLXBF_PMC_PERFEVT_EVTSEL, perfevt);

	वापस 0;
पूर्ण

/* Method to पढ़ो a रेजिस्टर */
अटल पूर्णांक mlxbf_pmc_पढ़ो_reg(पूर्णांक blk_num, uपूर्णांक32_t offset, uपूर्णांक64_t *result)
अणु
	uपूर्णांक32_t ecc_out;

	अगर (म_माला(pmc->block_name[blk_num], "ecc")) अणु
		अगर (mlxbf_pmc_पढ़ोl(pmc->block[blk_num].mmio_base + offset,
				    &ecc_out))
			वापस -EFAULT;

		*result = ecc_out;
		वापस 0;
	पूर्ण

	अगर (mlxbf_pmc_valid_range(blk_num, offset))
		वापस mlxbf_pmc_पढ़ो(pmc->block[blk_num].mmio_base + offset,
				      MLXBF_PMC_READ_REG_64, result);

	वापस -EINVAL;
पूर्ण

/* Method to ग_लिखो to a रेजिस्टर */
अटल पूर्णांक mlxbf_pmc_ग_लिखो_reg(पूर्णांक blk_num, uपूर्णांक32_t offset, uपूर्णांक64_t data)
अणु
	अगर (म_माला(pmc->block_name[blk_num], "ecc")) अणु
		वापस mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base + offset,
				       MLXBF_PMC_WRITE_REG_32, data);
	पूर्ण

	अगर (mlxbf_pmc_valid_range(blk_num, offset))
		वापस mlxbf_pmc_ग_लिखो(pmc->block[blk_num].mmio_base + offset,
				       MLXBF_PMC_WRITE_REG_64, data);

	वापस -EINVAL;
पूर्ण

/* Show function क्रम "counter" sysfs files */
अटल sमाप_प्रकार mlxbf_pmc_counter_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlxbf_pmc_attribute *attr_counter = container_of(
		attr, काष्ठा mlxbf_pmc_attribute, dev_attr);
	पूर्णांक blk_num, cnt_num, offset;
	bool is_l3 = false;
	uपूर्णांक64_t value;

	blk_num = attr_counter->nr;
	cnt_num = attr_counter->index;

	अगर (म_माला(pmc->block_name[blk_num], "l3cache"))
		is_l3 = true;

	अगर (pmc->block[blk_num].type == MLXBF_PMC_TYPE_COUNTER) अणु
		अगर (mlxbf_pmc_पढ़ो_counter(blk_num, cnt_num, is_l3, &value))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (pmc->block[blk_num].type == MLXBF_PMC_TYPE_REGISTER) अणु
		offset = mlxbf_pmc_get_event_num(pmc->block_name[blk_num],
						 attr->attr.name);
		अगर (offset < 0)
			वापस -EINVAL;
		अगर (mlxbf_pmc_पढ़ो_reg(blk_num, offset, &value))
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "0x%llx\n", value);
पूर्ण

/* Store function क्रम "counter" sysfs files */
अटल sमाप_प्रकार mlxbf_pmc_counter_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mlxbf_pmc_attribute *attr_counter = container_of(
		attr, काष्ठा mlxbf_pmc_attribute, dev_attr);
	पूर्णांक blk_num, cnt_num, offset, err, data;
	bool is_l3 = false;
	uपूर्णांक64_t evt_num;

	blk_num = attr_counter->nr;
	cnt_num = attr_counter->index;

	err = kstrtoपूर्णांक(buf, 0, &data);
	अगर (err < 0)
		वापस err;

	/* Allow non-zero ग_लिखोs only to the ecc regs */
	अगर (!(म_माला(pmc->block_name[blk_num], "ecc")) && data)
		वापस -EINVAL;

	/* Do not allow ग_लिखोs to the L3C regs */
	अगर (म_माला(pmc->block_name[blk_num], "l3cache"))
		वापस -EINVAL;

	अगर (pmc->block[blk_num].type == MLXBF_PMC_TYPE_COUNTER) अणु
		err = mlxbf_pmc_पढ़ो_event(blk_num, cnt_num, is_l3, &evt_num);
		अगर (err)
			वापस err;
		err = mlxbf_pmc_program_counter(blk_num, cnt_num, evt_num,
						is_l3);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (pmc->block[blk_num].type == MLXBF_PMC_TYPE_REGISTER) अणु
		offset = mlxbf_pmc_get_event_num(pmc->block_name[blk_num],
						 attr->attr.name);
		अगर (offset < 0)
			वापस -EINVAL;
		err = mlxbf_pmc_ग_लिखो_reg(blk_num, offset, data);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

/* Show function क्रम "event" sysfs files */
अटल sमाप_प्रकार mlxbf_pmc_event_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlxbf_pmc_attribute *attr_event = container_of(
		attr, काष्ठा mlxbf_pmc_attribute, dev_attr);
	पूर्णांक blk_num, cnt_num, err;
	bool is_l3 = false;
	uपूर्णांक64_t evt_num;
	अक्षर *evt_name;

	blk_num = attr_event->nr;
	cnt_num = attr_event->index;

	अगर (म_माला(pmc->block_name[blk_num], "l3cache"))
		is_l3 = true;

	err = mlxbf_pmc_पढ़ो_event(blk_num, cnt_num, is_l3, &evt_num);
	अगर (err)
		वापस प्र_लिखो(buf, "No event being monitored\n");

	evt_name = mlxbf_pmc_get_event_name(pmc->block_name[blk_num], evt_num);
	अगर (!evt_name)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "0x%llx: %s\n", evt_num, evt_name);
पूर्ण

/* Store function क्रम "event" sysfs files */
अटल sमाप_प्रकार mlxbf_pmc_event_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mlxbf_pmc_attribute *attr_event = container_of(
		attr, काष्ठा mlxbf_pmc_attribute, dev_attr);
	पूर्णांक blk_num, cnt_num, evt_num, err;
	bool is_l3 = false;

	blk_num = attr_event->nr;
	cnt_num = attr_event->index;

	अगर (है_अक्षर(buf[0])) अणु
		evt_num = mlxbf_pmc_get_event_num(pmc->block_name[blk_num],
						  buf);
		अगर (evt_num < 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		err = kstrtoपूर्णांक(buf, 0, &evt_num);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (म_माला(pmc->block_name[blk_num], "l3cache"))
		is_l3 = true;

	err = mlxbf_pmc_program_counter(blk_num, cnt_num, evt_num, is_l3);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

/* Show function क्रम "event_list" sysfs files */
अटल sमाप_प्रकार mlxbf_pmc_event_list_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा mlxbf_pmc_attribute *attr_event_list = container_of(
		attr, काष्ठा mlxbf_pmc_attribute, dev_attr);
	पूर्णांक blk_num, i, size, len = 0, ret = 0;
	स्थिर काष्ठा mlxbf_pmc_events *events;
	अक्षर e_info[MLXBF_PMC_EVENT_INFO_LEN];

	blk_num = attr_event_list->nr;

	events = mlxbf_pmc_event_list(pmc->block_name[blk_num], &size);
	अगर (!events)
		वापस -EINVAL;

	क्रम (i = 0, buf[0] = '\0'; i < size; ++i) अणु
		len += प्र_लिखो(e_info, "0x%x: %s\n", events[i].evt_num,
			       events[i].evt_name);
		अगर (len > PAGE_SIZE)
			अवरोध;
		म_जोड़ो(buf, e_info);
		ret = len;
	पूर्ण

	वापस ret;
पूर्ण

/* Show function क्रम "enable" sysfs files - only क्रम l3cache */
अटल sमाप_प्रकार mlxbf_pmc_enable_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlxbf_pmc_attribute *attr_enable = container_of(
		attr, काष्ठा mlxbf_pmc_attribute, dev_attr);
	uपूर्णांक32_t perfcnt_cfg;
	पूर्णांक blk_num, value;

	blk_num = attr_enable->nr;

	अगर (mlxbf_pmc_पढ़ोl(pmc->block[blk_num].mmio_base +
				    MLXBF_PMC_L3C_PERF_CNT_CFG,
			    &perfcnt_cfg))
		वापस -EINVAL;

	value = FIELD_GET(MLXBF_PMC_L3C_PERF_CNT_CFG_EN, perfcnt_cfg);

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

/* Store function क्रम "enable" sysfs files - only क्रम l3cache */
अटल sमाप_प्रकार mlxbf_pmc_enable_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mlxbf_pmc_attribute *attr_enable = container_of(
		attr, काष्ठा mlxbf_pmc_attribute, dev_attr);
	पूर्णांक err, en, blk_num;

	blk_num = attr_enable->nr;

	err = kstrtoपूर्णांक(buf, 0, &en);
	अगर (err < 0)
		वापस err;

	अगर (!en) अणु
		err = mlxbf_pmc_config_l3_counters(blk_num, false, false);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (en == 1) अणु
		err = mlxbf_pmc_config_l3_counters(blk_num, false, true);
		अगर (err)
			वापस err;
		err = mlxbf_pmc_config_l3_counters(blk_num, true, false);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

/* Populate attributes क्रम blocks with counters to monitor perक्रमmance */
अटल पूर्णांक mlxbf_pmc_init_perftype_counter(काष्ठा device *dev, पूर्णांक blk_num)
अणु
	काष्ठा mlxbf_pmc_attribute *attr;
	पूर्णांक i = 0, j = 0;

	/* "event_list" sysfs to list events supported by the block */
	attr = &pmc->block[blk_num].attr_event_list;
	attr->dev_attr.attr.mode = 0444;
	attr->dev_attr.show = mlxbf_pmc_event_list_show;
	attr->nr = blk_num;
	attr->dev_attr.attr.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "event_list");
	pmc->block[blk_num].block_attr[i] = &attr->dev_attr.attr;
	attr = शून्य;

	/* "enable" sysfs to start/stop the counters. Only in L3C blocks */
	अगर (म_माला(pmc->block_name[blk_num], "l3cache")) अणु
		attr = &pmc->block[blk_num].attr_enable;
		attr->dev_attr.attr.mode = 0644;
		attr->dev_attr.show = mlxbf_pmc_enable_show;
		attr->dev_attr.store = mlxbf_pmc_enable_store;
		attr->nr = blk_num;
		attr->dev_attr.attr.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "enable");
		pmc->block[blk_num].block_attr[++i] = &attr->dev_attr.attr;
		attr = शून्य;
	पूर्ण

	pmc->block[blk_num].attr_counter = devm_kसुस्मृति(
		dev, pmc->block[blk_num].counters,
		माप(काष्ठा mlxbf_pmc_attribute), GFP_KERNEL);
	अगर (!pmc->block[blk_num].attr_counter)
		वापस -ENOMEM;

	pmc->block[blk_num].attr_event = devm_kसुस्मृति(
		dev, pmc->block[blk_num].counters,
		माप(काष्ठा mlxbf_pmc_attribute), GFP_KERNEL);
	अगर (!pmc->block[blk_num].attr_event)
		वापस -ENOMEM;

	/* "eventX" and "counterX" sysfs to program and पढ़ो counter values */
	क्रम (j = 0; j < pmc->block[blk_num].counters; ++j) अणु
		attr = &pmc->block[blk_num].attr_counter[j];
		attr->dev_attr.attr.mode = 0644;
		attr->dev_attr.show = mlxbf_pmc_counter_show;
		attr->dev_attr.store = mlxbf_pmc_counter_store;
		attr->index = j;
		attr->nr = blk_num;
		attr->dev_attr.attr.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "counter%d", j);
		pmc->block[blk_num].block_attr[++i] = &attr->dev_attr.attr;
		attr = शून्य;

		attr = &pmc->block[blk_num].attr_event[j];
		attr->dev_attr.attr.mode = 0644;
		attr->dev_attr.show = mlxbf_pmc_event_show;
		attr->dev_attr.store = mlxbf_pmc_event_store;
		attr->index = j;
		attr->nr = blk_num;
		attr->dev_attr.attr.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "event%d", j);
		pmc->block[blk_num].block_attr[++i] = &attr->dev_attr.attr;
		attr = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/* Populate attributes क्रम blocks with रेजिस्टरs to monitor perक्रमmance */
अटल पूर्णांक mlxbf_pmc_init_perftype_reg(काष्ठा device *dev, पूर्णांक blk_num)
अणु
	काष्ठा mlxbf_pmc_attribute *attr;
	स्थिर काष्ठा mlxbf_pmc_events *events;
	पूर्णांक i = 0, j = 0;

	events = mlxbf_pmc_event_list(pmc->block_name[blk_num], &j);
	अगर (!events)
		वापस -EINVAL;

	pmc->block[blk_num].attr_event = devm_kसुस्मृति(
		dev, j, माप(काष्ठा mlxbf_pmc_attribute), GFP_KERNEL);
	अगर (!pmc->block[blk_num].attr_event)
		वापस -ENOMEM;

	जबतक (j > 0) अणु
		--j;
		attr = &pmc->block[blk_num].attr_event[j];
		attr->dev_attr.attr.mode = 0644;
		attr->dev_attr.show = mlxbf_pmc_counter_show;
		attr->dev_attr.store = mlxbf_pmc_counter_store;
		attr->nr = blk_num;
		attr->dev_attr.attr.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  events[j].evt_name);
		pmc->block[blk_num].block_attr[i] = &attr->dev_attr.attr;
		attr = शून्य;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

/* Helper to create the bfperf sysfs sub-directories and files */
अटल पूर्णांक mlxbf_pmc_create_groups(काष्ठा device *dev, पूर्णांक blk_num)
अणु
	पूर्णांक err;

	/* Populate attributes based on counter type */
	अगर (pmc->block[blk_num].type == MLXBF_PMC_TYPE_COUNTER)
		err = mlxbf_pmc_init_perftype_counter(dev, blk_num);
	अन्यथा अगर (pmc->block[blk_num].type == MLXBF_PMC_TYPE_REGISTER)
		err = mlxbf_pmc_init_perftype_reg(dev, blk_num);
	अन्यथा
		err = -EINVAL;

	अगर (err)
		वापस err;

	/* Add a new attribute_group क्रम the block */
	pmc->block[blk_num].block_attr_grp.attrs = pmc->block[blk_num].block_attr;
	pmc->block[blk_num].block_attr_grp.name = devm_kaप्र_लिखो(
		dev, GFP_KERNEL, pmc->block_name[blk_num]);
	pmc->groups[blk_num] = &pmc->block[blk_num].block_attr_grp;

	वापस 0;
पूर्ण

अटल bool mlxbf_pmc_guid_match(स्थिर guid_t *guid,
				 स्थिर काष्ठा arm_smccc_res *res)
अणु
	guid_t id = GUID_INIT(res->a0, res->a1, res->a1 >> 16, res->a2,
			      res->a2 >> 8, res->a2 >> 16, res->a2 >> 24,
			      res->a3, res->a3 >> 8, res->a3 >> 16,
			      res->a3 >> 24);

	वापस guid_equal(guid, &id);
पूर्ण

/* Helper to map the Perक्रमmance Counters from the varios blocks */
अटल पूर्णांक mlxbf_pmc_map_counters(काष्ठा device *dev)
अणु
	uपूर्णांक64_t info[MLXBF_PMC_INFO_SZ];
	पूर्णांक i, tile_num, ret;

	क्रम (i = 0; i < pmc->total_blocks; ++i) अणु
		अगर (म_माला(pmc->block_name[i], "tile")) अणु
			ret = माला_पूछो(pmc->block_name[i], "tile%d", &tile_num);
			अगर (ret < 0)
				वापस ret;

			अगर (tile_num >= pmc->tile_count)
				जारी;
		पूर्ण
		ret = device_property_पढ़ो_u64_array(dev, pmc->block_name[i],
						     info, MLXBF_PMC_INFO_SZ);
		अगर (ret)
			वापस ret;

		/*
		 * Do not remap अगर the proper SMC calls are supported,
		 * since the SMC calls expect physical addresses.
		 */
		अगर (pmc->svc_sreg_support)
			pmc->block[i].mmio_base = (व्योम __iomem *)info[0];
		अन्यथा
			pmc->block[i].mmio_base =
				devm_ioremap(dev, info[0], info[1]);

		pmc->block[i].blk_size = info[1];
		pmc->block[i].counters = info[2];
		pmc->block[i].type = info[3];

		अगर (IS_ERR(pmc->block[i].mmio_base))
			वापस PTR_ERR(pmc->block[i].mmio_base);

		ret = mlxbf_pmc_create_groups(dev, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_pmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_device *acpi_dev = ACPI_COMPANION(&pdev->dev);
	स्थिर अक्षर *hid = acpi_device_hid(acpi_dev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा arm_smccc_res res;
	guid_t guid;
	पूर्णांक ret;

	/* Ensure we have the UUID we expect क्रम this service. */
	arm_smccc_smc(MLXBF_PMC_SIP_SVC_UID, 0, 0, 0, 0, 0, 0, 0, &res);
	guid_parse(mlxbf_pmc_svc_uuid_str, &guid);
	अगर (!mlxbf_pmc_guid_match(&guid, &res))
		वापस -ENODEV;

	pmc = devm_kzalloc(dev, माप(काष्ठा mlxbf_pmc_context), GFP_KERNEL);
	अगर (!pmc)
		वापस -ENOMEM;

	/*
	 * ACPI indicates whether we use SMCs to access रेजिस्टरs or not.
	 * If sreg_tbl_perf is not present, just assume we're not using SMCs.
	 */
	ret = device_property_पढ़ो_u32(dev, "sec_reg_block",
				       &pmc->sreg_tbl_perf);
	अगर (ret) अणु
		pmc->svc_sreg_support = false;
	पूर्ण अन्यथा अणु
		/*
		 * Check service version to see अगर we actually करो support the
		 * needed SMCs. If we have the calls we need, mark support क्रम
		 * them in the pmc काष्ठा.
		 */
		arm_smccc_smc(MLXBF_PMC_SIP_SVC_VERSION, 0, 0, 0, 0, 0, 0, 0,
			      &res);
		अगर (res.a0 == MLXBF_PMC_SVC_REQ_MAJOR &&
		    res.a1 >= MLXBF_PMC_SVC_MIN_MINOR)
			pmc->svc_sreg_support = true;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (!म_भेद(hid, "MLNXBFD0"))
		pmc->event_set = MLXBF_PMC_EVENT_SET_BF1;
	अन्यथा अगर (!म_भेद(hid, "MLNXBFD1"))
		pmc->event_set = MLXBF_PMC_EVENT_SET_BF2;
	अन्यथा
		वापस -ENODEV;

	ret = device_property_पढ़ो_u32(dev, "block_num", &pmc->total_blocks);
	अगर (ret)
		वापस ret;

	ret = device_property_पढ़ो_string_array(dev, "block_name",
						pmc->block_name,
						pmc->total_blocks);
	अगर (ret != pmc->total_blocks)
		वापस -EFAULT;

	ret = device_property_पढ़ो_u32(dev, "tile_num", &pmc->tile_count);
	अगर (ret)
		वापस ret;

	pmc->pdev = pdev;

	ret = mlxbf_pmc_map_counters(dev);
	अगर (ret)
		वापस ret;

	pmc->hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(
		dev, "bfperf", pmc, pmc->groups);
	platक्रमm_set_drvdata(pdev, pmc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id mlxbf_pmc_acpi_ids[] = अणु अणु "MLNXBFD0", 0 पूर्ण,
							    अणु "MLNXBFD1", 0 पूर्ण,
							    अणुपूर्ण, पूर्ण;

MODULE_DEVICE_TABLE(acpi, mlxbf_pmc_acpi_ids);
अटल काष्ठा platक्रमm_driver pmc_driver = अणु
	.driver = अणु .name = "mlxbf-pmc",
		    .acpi_match_table = ACPI_PTR(mlxbf_pmc_acpi_ids), पूर्ण,
	.probe = mlxbf_pmc_probe,
पूर्ण;

module_platक्रमm_driver(pmc_driver);

MODULE_AUTHOR("Shravan Kumar Ramani <sramani@mellanox.com>");
MODULE_DESCRIPTION("Mellanox PMC driver");
MODULE_LICENSE("Dual BSD/GPL");
