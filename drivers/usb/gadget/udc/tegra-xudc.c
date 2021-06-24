<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * NVIDIA Tegra XUSB device mode controller
 *
 * Copyright (c) 2013-2019, NVIDIA CORPORATION.  All rights reserved.
 * Copyright (c) 2015, Google Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/tegra/xusb.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/workqueue.h>

/* XUSB_DEV रेजिस्टरs */
#घोषणा SPARAM 0x000
#घोषणा  SPARAM_ERSTMAX_MASK GENMASK(20, 16)
#घोषणा  SPARAM_ERSTMAX(x) (((x) << 16) & SPARAM_ERSTMAX_MASK)
#घोषणा DB 0x004
#घोषणा  DB_TARGET_MASK GENMASK(15, 8)
#घोषणा  DB_TARGET(x) (((x) << 8) & DB_TARGET_MASK)
#घोषणा  DB_STREAMID_MASK GENMASK(31, 16)
#घोषणा  DB_STREAMID(x) (((x) << 16) & DB_STREAMID_MASK)
#घोषणा ERSTSZ 0x008
#घोषणा  ERSTSZ_ERSTXSZ_SHIFT(x) ((x) * 16)
#घोषणा  ERSTSZ_ERSTXSZ_MASK GENMASK(15, 0)
#घोषणा ERSTXBALO(x) (0x010 + 8 * (x))
#घोषणा ERSTXBAHI(x) (0x014 + 8 * (x))
#घोषणा ERDPLO 0x020
#घोषणा  ERDPLO_EHB BIT(3)
#घोषणा ERDPHI 0x024
#घोषणा EREPLO 0x028
#घोषणा  EREPLO_ECS BIT(0)
#घोषणा  EREPLO_SEGI BIT(1)
#घोषणा EREPHI 0x02c
#घोषणा CTRL 0x030
#घोषणा  CTRL_RUN BIT(0)
#घोषणा  CTRL_LSE BIT(1)
#घोषणा  CTRL_IE BIT(4)
#घोषणा  CTRL_SMI_EVT BIT(5)
#घोषणा  CTRL_SMI_DSE BIT(6)
#घोषणा  CTRL_EWE BIT(7)
#घोषणा  CTRL_DEVADDR_MASK GENMASK(30, 24)
#घोषणा  CTRL_DEVADDR(x) (((x) << 24) & CTRL_DEVADDR_MASK)
#घोषणा  CTRL_ENABLE BIT(31)
#घोषणा ST 0x034
#घोषणा  ST_RC BIT(0)
#घोषणा  ST_IP BIT(4)
#घोषणा RT_IMOD	0x038
#घोषणा  RT_IMOD_IMODI_MASK GENMASK(15, 0)
#घोषणा  RT_IMOD_IMODI(x) ((x) & RT_IMOD_IMODI_MASK)
#घोषणा  RT_IMOD_IMODC_MASK GENMASK(31, 16)
#घोषणा  RT_IMOD_IMODC(x) (((x) << 16) & RT_IMOD_IMODC_MASK)
#घोषणा PORTSC 0x03c
#घोषणा  PORTSC_CCS BIT(0)
#घोषणा  PORTSC_PED BIT(1)
#घोषणा  PORTSC_PR BIT(4)
#घोषणा  PORTSC_PLS_SHIFT 5
#घोषणा  PORTSC_PLS_MASK GENMASK(8, 5)
#घोषणा  PORTSC_PLS_U0 0x0
#घोषणा  PORTSC_PLS_U2 0x2
#घोषणा  PORTSC_PLS_U3 0x3
#घोषणा  PORTSC_PLS_DISABLED 0x4
#घोषणा  PORTSC_PLS_RXDETECT 0x5
#घोषणा  PORTSC_PLS_INACTIVE 0x6
#घोषणा  PORTSC_PLS_RESUME 0xf
#घोषणा  PORTSC_PLS(x) (((x) << PORTSC_PLS_SHIFT) & PORTSC_PLS_MASK)
#घोषणा  PORTSC_PS_SHIFT 10
#घोषणा  PORTSC_PS_MASK GENMASK(13, 10)
#घोषणा  PORTSC_PS_UNDEFINED 0x0
#घोषणा  PORTSC_PS_FS 0x1
#घोषणा  PORTSC_PS_LS 0x2
#घोषणा  PORTSC_PS_HS 0x3
#घोषणा  PORTSC_PS_SS 0x4
#घोषणा  PORTSC_LWS BIT(16)
#घोषणा  PORTSC_CSC BIT(17)
#घोषणा  PORTSC_WRC BIT(19)
#घोषणा  PORTSC_PRC BIT(21)
#घोषणा  PORTSC_PLC BIT(22)
#घोषणा  PORTSC_CEC BIT(23)
#घोषणा  PORTSC_WPR BIT(30)
#घोषणा  PORTSC_CHANGE_MASK (PORTSC_CSC | PORTSC_WRC | PORTSC_PRC | \
			     PORTSC_PLC | PORTSC_CEC)
#घोषणा ECPLO 0x040
#घोषणा ECPHI 0x044
#घोषणा MFINDEX 0x048
#घोषणा  MFINDEX_FRAME_SHIFT 3
#घोषणा  MFINDEX_FRAME_MASK GENMASK(13, 3)
#घोषणा PORTPM 0x04c
#घोषणा  PORTPM_L1S_MASK GENMASK(1, 0)
#घोषणा  PORTPM_L1S_DROP 0x0
#घोषणा  PORTPM_L1S_ACCEPT 0x1
#घोषणा  PORTPM_L1S_NYET 0x2
#घोषणा  PORTPM_L1S_STALL 0x3
#घोषणा  PORTPM_L1S(x) ((x) & PORTPM_L1S_MASK)
#घोषणा  PORTPM_RWE BIT(3)
#घोषणा  PORTPM_U2TIMEOUT_MASK GENMASK(15, 8)
#घोषणा  PORTPM_U1TIMEOUT_MASK GENMASK(23, 16)
#घोषणा  PORTPM_FLA BIT(24)
#घोषणा  PORTPM_VBA BIT(25)
#घोषणा  PORTPM_WOC BIT(26)
#घोषणा  PORTPM_WOD BIT(27)
#घोषणा  PORTPM_U1E BIT(28)
#घोषणा  PORTPM_U2E BIT(29)
#घोषणा  PORTPM_FRWE BIT(30)
#घोषणा  PORTPM_PNG_CYA BIT(31)
#घोषणा EP_HALT 0x050
#घोषणा EP_PAUSE 0x054
#घोषणा EP_RELOAD 0x058
#घोषणा EP_STCHG 0x05c
#घोषणा DEVNOTIF_LO 0x064
#घोषणा  DEVNOTIF_LO_TRIG BIT(0)
#घोषणा  DEVNOTIF_LO_TYPE_MASK GENMASK(7, 4)
#घोषणा  DEVNOTIF_LO_TYPE(x) (((x) << 4)  & DEVNOTIF_LO_TYPE_MASK)
#घोषणा  DEVNOTIF_LO_TYPE_FUNCTION_WAKE 0x1
#घोषणा DEVNOTIF_HI 0x068
#घोषणा PORTHALT 0x06c
#घोषणा  PORTHALT_HALT_LTSSM BIT(0)
#घोषणा  PORTHALT_HALT_REJECT BIT(1)
#घोषणा  PORTHALT_STCHG_REQ BIT(20)
#घोषणा  PORTHALT_STCHG_INTR_EN BIT(24)
#घोषणा PORT_TM	0x070
#घोषणा EP_THREAD_ACTIVE 0x074
#घोषणा EP_STOPPED 0x078
#घोषणा HSFSPI_COUNT0 0x100
#घोषणा HSFSPI_COUNT13 0x134
#घोषणा  HSFSPI_COUNT13_U2_RESUME_K_DURATION_MASK GENMASK(29, 0)
#घोषणा  HSFSPI_COUNT13_U2_RESUME_K_DURATION(x) ((x) & \
				HSFSPI_COUNT13_U2_RESUME_K_DURATION_MASK)
#घोषणा BLCG 0x840
#घोषणा SSPX_CORE_CNT0 0x610
#घोषणा  SSPX_CORE_CNT0_PING_TBURST_MASK GENMASK(7, 0)
#घोषणा  SSPX_CORE_CNT0_PING_TBURST(x) ((x) & SSPX_CORE_CNT0_PING_TBURST_MASK)
#घोषणा SSPX_CORE_CNT30 0x688
#घोषणा  SSPX_CORE_CNT30_LMPITP_TIMER_MASK GENMASK(19, 0)
#घोषणा  SSPX_CORE_CNT30_LMPITP_TIMER(x) ((x) & \
					SSPX_CORE_CNT30_LMPITP_TIMER_MASK)
#घोषणा SSPX_CORE_CNT32 0x690
#घोषणा  SSPX_CORE_CNT32_POLL_TBURST_MAX_MASK GENMASK(7, 0)
#घोषणा  SSPX_CORE_CNT32_POLL_TBURST_MAX(x) ((x) & \
					SSPX_CORE_CNT32_POLL_TBURST_MAX_MASK)
#घोषणा SSPX_CORE_CNT56 0x6fc
#घोषणा  SSPX_CORE_CNT56_SCD_BIT0_TRPT_MAX_MASK GENMASK(19, 0)
#घोषणा  SSPX_CORE_CNT56_SCD_BIT0_TRPT_MAX(x) ((x) & \
				SSPX_CORE_CNT56_SCD_BIT0_TRPT_MAX_MASK)
#घोषणा SSPX_CORE_CNT57 0x700
#घोषणा  SSPX_CORE_CNT57_SCD_BIT1_TRPT_MAX_MASK GENMASK(19, 0)
#घोषणा  SSPX_CORE_CNT57_SCD_BIT1_TRPT_MAX(x) ((x) & \
				SSPX_CORE_CNT57_SCD_BIT1_TRPT_MAX_MASK)
#घोषणा SSPX_CORE_CNT65 0x720
#घोषणा  SSPX_CORE_CNT65_TX_SCD_END_TRPT_MID_MASK GENMASK(19, 0)
#घोषणा  SSPX_CORE_CNT65_TX_SCD_END_TRPT_MID(x) ((x) & \
				SSPX_CORE_CNT65_TX_SCD_END_TRPT_MID_MASK)
#घोषणा SSPX_CORE_CNT66 0x724
#घोषणा  SSPX_CORE_CNT66_TX_SCD_BIT0_TRPT_MID_MASK GENMASK(19, 0)
#घोषणा  SSPX_CORE_CNT66_TX_SCD_BIT0_TRPT_MID(x) ((x) & \
				SSPX_CORE_CNT66_TX_SCD_BIT0_TRPT_MID_MASK)
#घोषणा SSPX_CORE_CNT67 0x728
#घोषणा  SSPX_CORE_CNT67_TX_SCD_BIT1_TRPT_MID_MASK GENMASK(19, 0)
#घोषणा  SSPX_CORE_CNT67_TX_SCD_BIT1_TRPT_MID(x) ((x) & \
				SSPX_CORE_CNT67_TX_SCD_BIT1_TRPT_MID_MASK)
#घोषणा SSPX_CORE_CNT72 0x73c
#घोषणा  SSPX_CORE_CNT72_SCD_LFPS_TIMEOUT_MASK GENMASK(19, 0)
#घोषणा  SSPX_CORE_CNT72_SCD_LFPS_TIMEOUT(x) ((x) & \
				SSPX_CORE_CNT72_SCD_LFPS_TIMEOUT_MASK)
#घोषणा SSPX_CORE_PADCTL4 0x750
#घोषणा  SSPX_CORE_PADCTL4_RXDAT_VLD_TIMEOUT_U3_MASK GENMASK(19, 0)
#घोषणा  SSPX_CORE_PADCTL4_RXDAT_VLD_TIMEOUT_U3(x) ((x) & \
				SSPX_CORE_PADCTL4_RXDAT_VLD_TIMEOUT_U3_MASK)
#घोषणा  BLCG_DFPCI BIT(0)
#घोषणा  BLCG_UFPCI BIT(1)
#घोषणा  BLCG_FE BIT(2)
#घोषणा  BLCG_COREPLL_PWRDN BIT(8)
#घोषणा  BLCG_IOPLL_0_PWRDN BIT(9)
#घोषणा  BLCG_IOPLL_1_PWRDN BIT(10)
#घोषणा  BLCG_IOPLL_2_PWRDN BIT(11)
#घोषणा  BLCG_ALL 0x1ff
#घोषणा CFG_DEV_SSPI_XFER 0x858
#घोषणा  CFG_DEV_SSPI_XFER_ACKTIMEOUT_MASK GENMASK(31, 0)
#घोषणा  CFG_DEV_SSPI_XFER_ACKTIMEOUT(x) ((x) & \
					CFG_DEV_SSPI_XFER_ACKTIMEOUT_MASK)
#घोषणा CFG_DEV_FE 0x85c
#घोषणा  CFG_DEV_FE_PORTREGSEL_MASK GENMASK(1, 0)
#घोषणा  CFG_DEV_FE_PORTREGSEL_SS_PI 1
#घोषणा  CFG_DEV_FE_PORTREGSEL_HSFS_PI 2
#घोषणा  CFG_DEV_FE_PORTREGSEL(x) ((x) & CFG_DEV_FE_PORTREGSEL_MASK)
#घोषणा  CFG_DEV_FE_INFINITE_SS_RETRY BIT(29)

/* FPCI रेजिस्टरs */
#घोषणा XUSB_DEV_CFG_1 0x004
#घोषणा  XUSB_DEV_CFG_1_IO_SPACE_EN BIT(0)
#घोषणा  XUSB_DEV_CFG_1_MEMORY_SPACE_EN BIT(1)
#घोषणा  XUSB_DEV_CFG_1_BUS_MASTER_EN BIT(2)
#घोषणा XUSB_DEV_CFG_4 0x010
#घोषणा  XUSB_DEV_CFG_4_BASE_ADDR_MASK GENMASK(31, 15)
#घोषणा XUSB_DEV_CFG_5 0x014

/* IPFS रेजिस्टरs */
#घोषणा XUSB_DEV_CONFIGURATION_0 0x180
#घोषणा  XUSB_DEV_CONFIGURATION_0_EN_FPCI BIT(0)
#घोषणा XUSB_DEV_INTR_MASK_0 0x188
#घोषणा  XUSB_DEV_INTR_MASK_0_IP_INT_MASK BIT(16)

काष्ठा tegra_xudc_ep_context अणु
	__le32 info0;
	__le32 info1;
	__le32 deq_lo;
	__le32 deq_hi;
	__le32 tx_info;
	__le32 rsvd[11];
पूर्ण;

#घोषणा EP_STATE_DISABLED 0
#घोषणा EP_STATE_RUNNING 1
#घोषणा EP_STATE_HALTED 2
#घोषणा EP_STATE_STOPPED 3
#घोषणा EP_STATE_ERROR 4

#घोषणा EP_TYPE_INVALID 0
#घोषणा EP_TYPE_ISOCH_OUT 1
#घोषणा EP_TYPE_BULK_OUT 2
#घोषणा EP_TYPE_INTERRUPT_OUT 3
#घोषणा EP_TYPE_CONTROL 4
#घोषणा EP_TYPE_ISCOH_IN 5
#घोषणा EP_TYPE_BULK_IN 6
#घोषणा EP_TYPE_INTERRUPT_IN 7

#घोषणा BUILD_EP_CONTEXT_RW(name, member, shअगरt, mask)			\
अटल अंतरभूत u32 ep_ctx_पढ़ो_##name(काष्ठा tegra_xudc_ep_context *ctx)	\
अणु									\
	वापस (le32_to_cpu(ctx->member) >> (shअगरt)) & (mask);		\
पूर्ण									\
अटल अंतरभूत व्योम							\
ep_ctx_ग_लिखो_##name(काष्ठा tegra_xudc_ep_context *ctx, u32 val)		\
अणु									\
	u32 पंचांगp;							\
									\
	पंचांगp = le32_to_cpu(ctx->member) & ~((mask) << (shअगरt));		\
	पंचांगp |= (val & (mask)) << (shअगरt);				\
	ctx->member = cpu_to_le32(पंचांगp);					\
पूर्ण

BUILD_EP_CONTEXT_RW(state, info0, 0, 0x7)
BUILD_EP_CONTEXT_RW(mult, info0, 8, 0x3)
BUILD_EP_CONTEXT_RW(max_pstreams, info0, 10, 0x1f)
BUILD_EP_CONTEXT_RW(lsa, info0, 15, 0x1)
BUILD_EP_CONTEXT_RW(पूर्णांकerval, info0, 16, 0xff)
BUILD_EP_CONTEXT_RW(cerr, info1, 1, 0x3)
BUILD_EP_CONTEXT_RW(type, info1, 3, 0x7)
BUILD_EP_CONTEXT_RW(hid, info1, 7, 0x1)
BUILD_EP_CONTEXT_RW(max_burst_size, info1, 8, 0xff)
BUILD_EP_CONTEXT_RW(max_packet_size, info1, 16, 0xffff)
BUILD_EP_CONTEXT_RW(dcs, deq_lo, 0, 0x1)
BUILD_EP_CONTEXT_RW(deq_lo, deq_lo, 4, 0xfffffff)
BUILD_EP_CONTEXT_RW(deq_hi, deq_hi, 0, 0xffffffff)
BUILD_EP_CONTEXT_RW(avg_trb_len, tx_info, 0, 0xffff)
BUILD_EP_CONTEXT_RW(max_esit_payload, tx_info, 16, 0xffff)
BUILD_EP_CONTEXT_RW(edtla, rsvd[0], 0, 0xffffff)
BUILD_EP_CONTEXT_RW(seq_num, rsvd[0], 24, 0xff)
BUILD_EP_CONTEXT_RW(partial_td, rsvd[0], 25, 0x1)
BUILD_EP_CONTEXT_RW(cerrcnt, rsvd[1], 18, 0x3)
BUILD_EP_CONTEXT_RW(data_offset, rsvd[2], 0, 0x1ffff)
BUILD_EP_CONTEXT_RW(numtrbs, rsvd[2], 22, 0x1f)
BUILD_EP_CONTEXT_RW(devaddr, rsvd[6], 0, 0x7f)

अटल अंतरभूत u64 ep_ctx_पढ़ो_deq_ptr(काष्ठा tegra_xudc_ep_context *ctx)
अणु
	वापस ((u64)ep_ctx_पढ़ो_deq_hi(ctx) << 32) |
		(ep_ctx_पढ़ो_deq_lo(ctx) << 4);
पूर्ण

अटल अंतरभूत व्योम
ep_ctx_ग_लिखो_deq_ptr(काष्ठा tegra_xudc_ep_context *ctx, u64 addr)
अणु
	ep_ctx_ग_लिखो_deq_lo(ctx, lower_32_bits(addr) >> 4);
	ep_ctx_ग_लिखो_deq_hi(ctx, upper_32_bits(addr));
पूर्ण

काष्ठा tegra_xudc_trb अणु
	__le32 data_lo;
	__le32 data_hi;
	__le32 status;
	__le32 control;
पूर्ण;

#घोषणा TRB_TYPE_RSVD 0
#घोषणा TRB_TYPE_NORMAL 1
#घोषणा TRB_TYPE_SETUP_STAGE 2
#घोषणा TRB_TYPE_DATA_STAGE 3
#घोषणा TRB_TYPE_STATUS_STAGE 4
#घोषणा TRB_TYPE_ISOCH 5
#घोषणा TRB_TYPE_LINK 6
#घोषणा TRB_TYPE_TRANSFER_EVENT 32
#घोषणा TRB_TYPE_PORT_STATUS_CHANGE_EVENT 34
#घोषणा TRB_TYPE_STREAM 48
#घोषणा TRB_TYPE_SETUP_PACKET_EVENT 63

#घोषणा TRB_CMPL_CODE_INVALID 0
#घोषणा TRB_CMPL_CODE_SUCCESS 1
#घोषणा TRB_CMPL_CODE_DATA_BUFFER_ERR 2
#घोषणा TRB_CMPL_CODE_BABBLE_DETECTED_ERR 3
#घोषणा TRB_CMPL_CODE_USB_TRANS_ERR 4
#घोषणा TRB_CMPL_CODE_TRB_ERR 5
#घोषणा TRB_CMPL_CODE_STALL 6
#घोषणा TRB_CMPL_CODE_INVALID_STREAM_TYPE_ERR 10
#घोषणा TRB_CMPL_CODE_SHORT_PACKET 13
#घोषणा TRB_CMPL_CODE_RING_UNDERRUN 14
#घोषणा TRB_CMPL_CODE_RING_OVERRUN 15
#घोषणा TRB_CMPL_CODE_EVENT_RING_FULL_ERR 21
#घोषणा TRB_CMPL_CODE_STOPPED 26
#घोषणा TRB_CMPL_CODE_ISOCH_BUFFER_OVERRUN 31
#घोषणा TRB_CMPL_CODE_STREAM_NUMP_ERROR 219
#घोषणा TRB_CMPL_CODE_PRIME_PIPE_RECEIVED 220
#घोषणा TRB_CMPL_CODE_HOST_REJECTED 221
#घोषणा TRB_CMPL_CODE_CTRL_सूची_ERR 222
#घोषणा TRB_CMPL_CODE_CTRL_SEQNUM_ERR 223

#घोषणा BUILD_TRB_RW(name, member, shअगरt, mask)				\
अटल अंतरभूत u32 trb_पढ़ो_##name(काष्ठा tegra_xudc_trb *trb)		\
अणु									\
	वापस (le32_to_cpu(trb->member) >> (shअगरt)) & (mask);		\
पूर्ण									\
अटल अंतरभूत व्योम							\
trb_ग_लिखो_##name(काष्ठा tegra_xudc_trb *trb, u32 val)			\
अणु									\
	u32 पंचांगp;							\
									\
	पंचांगp = le32_to_cpu(trb->member) & ~((mask) << (shअगरt));		\
	पंचांगp |= (val & (mask)) << (shअगरt);				\
	trb->member = cpu_to_le32(पंचांगp);					\
पूर्ण

BUILD_TRB_RW(data_lo, data_lo, 0, 0xffffffff)
BUILD_TRB_RW(data_hi, data_hi, 0, 0xffffffff)
BUILD_TRB_RW(seq_num, status, 0, 0xffff)
BUILD_TRB_RW(transfer_len, status, 0, 0xffffff)
BUILD_TRB_RW(td_size, status, 17, 0x1f)
BUILD_TRB_RW(cmpl_code, status, 24, 0xff)
BUILD_TRB_RW(cycle, control, 0, 0x1)
BUILD_TRB_RW(toggle_cycle, control, 1, 0x1)
BUILD_TRB_RW(isp, control, 2, 0x1)
BUILD_TRB_RW(chain, control, 4, 0x1)
BUILD_TRB_RW(ioc, control, 5, 0x1)
BUILD_TRB_RW(type, control, 10, 0x3f)
BUILD_TRB_RW(stream_id, control, 16, 0xffff)
BUILD_TRB_RW(endpoपूर्णांक_id, control, 16, 0x1f)
BUILD_TRB_RW(tlbpc, control, 16, 0xf)
BUILD_TRB_RW(data_stage_dir, control, 16, 0x1)
BUILD_TRB_RW(frame_id, control, 20, 0x7ff)
BUILD_TRB_RW(sia, control, 31, 0x1)

अटल अंतरभूत u64 trb_पढ़ो_data_ptr(काष्ठा tegra_xudc_trb *trb)
अणु
	वापस ((u64)trb_पढ़ो_data_hi(trb) << 32) |
		trb_पढ़ो_data_lo(trb);
पूर्ण

अटल अंतरभूत व्योम trb_ग_लिखो_data_ptr(काष्ठा tegra_xudc_trb *trb, u64 addr)
अणु
	trb_ग_लिखो_data_lo(trb, lower_32_bits(addr));
	trb_ग_लिखो_data_hi(trb, upper_32_bits(addr));
पूर्ण

काष्ठा tegra_xudc_request अणु
	काष्ठा usb_request usb_req;

	माप_प्रकार buf_queued;
	अचिन्हित पूर्णांक trbs_queued;
	अचिन्हित पूर्णांक trbs_needed;
	bool need_zlp;

	काष्ठा tegra_xudc_trb *first_trb;
	काष्ठा tegra_xudc_trb *last_trb;

	काष्ठा list_head list;
पूर्ण;

काष्ठा tegra_xudc_ep अणु
	काष्ठा tegra_xudc *xudc;
	काष्ठा usb_ep usb_ep;
	अचिन्हित पूर्णांक index;
	अक्षर name[8];

	काष्ठा tegra_xudc_ep_context *context;

#घोषणा XUDC_TRANSFER_RING_SIZE 64
	काष्ठा tegra_xudc_trb *transfer_ring;
	dma_addr_t transfer_ring_phys;

	अचिन्हित पूर्णांक enq_ptr;
	अचिन्हित पूर्णांक deq_ptr;
	bool pcs;
	bool ring_full;
	bool stream_rejected;

	काष्ठा list_head queue;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	स्थिर काष्ठा usb_ss_ep_comp_descriptor *comp_desc;
पूर्ण;

काष्ठा tegra_xudc_sel_timing अणु
	__u8 u1sel;
	__u8 u1pel;
	__le16 u2sel;
	__le16 u2pel;
पूर्ण;

क्रमागत tegra_xudc_setup_state अणु
	WAIT_FOR_SETUP,
	DATA_STAGE_XFER,
	DATA_STAGE_RECV,
	STATUS_STAGE_XFER,
	STATUS_STAGE_RECV,
पूर्ण;

काष्ठा tegra_xudc_setup_packet अणु
	काष्ठा usb_ctrlrequest ctrl_req;
	अचिन्हित पूर्णांक seq_num;
पूर्ण;

काष्ठा tegra_xudc_save_regs अणु
	u32 ctrl;
	u32 portpm;
पूर्ण;

काष्ठा tegra_xudc अणु
	काष्ठा device *dev;
	स्थिर काष्ठा tegra_xudc_soc *soc;
	काष्ठा tegra_xusb_padctl *padctl;

	spinlock_t lock;

	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *driver;

#घोषणा XUDC_NR_EVENT_RINGS 2
#घोषणा XUDC_EVENT_RING_SIZE 4096
	काष्ठा tegra_xudc_trb *event_ring[XUDC_NR_EVENT_RINGS];
	dma_addr_t event_ring_phys[XUDC_NR_EVENT_RINGS];
	अचिन्हित पूर्णांक event_ring_index;
	अचिन्हित पूर्णांक event_ring_deq_ptr;
	bool ccs;

#घोषणा XUDC_NR_EPS 32
	काष्ठा tegra_xudc_ep ep[XUDC_NR_EPS];
	काष्ठा tegra_xudc_ep_context *ep_context;
	dma_addr_t ep_context_phys;

	काष्ठा device *genpd_dev_device;
	काष्ठा device *genpd_dev_ss;
	काष्ठा device_link *genpd_dl_device;
	काष्ठा device_link *genpd_dl_ss;

	काष्ठा dma_pool *transfer_ring_pool;

	bool queued_setup_packet;
	काष्ठा tegra_xudc_setup_packet setup_packet;
	क्रमागत tegra_xudc_setup_state setup_state;
	u16 setup_seq_num;

	u16 dev_addr;
	u16 isoch_delay;
	काष्ठा tegra_xudc_sel_timing sel_timing;
	u8 test_mode_pattern;
	u16 status_buf;
	काष्ठा tegra_xudc_request *ep0_req;

	bool pullup;

	अचिन्हित पूर्णांक nr_enabled_eps;
	अचिन्हित पूर्णांक nr_isoch_eps;

	अचिन्हित पूर्णांक device_state;
	अचिन्हित पूर्णांक resume_state;

	पूर्णांक irq;

	व्योम __iomem *base;
	resource_माप_प्रकार phys_base;
	व्योम __iomem *ipfs;
	व्योम __iomem *fpci;

	काष्ठा regulator_bulk_data *supplies;

	काष्ठा clk_bulk_data *clks;

	bool device_mode;
	काष्ठा work_काष्ठा usb_role_sw_work;

	काष्ठा phy **usb3_phy;
	काष्ठा phy *curr_usb3_phy;
	काष्ठा phy **uपंचांगi_phy;
	काष्ठा phy *curr_uपंचांगi_phy;

	काष्ठा tegra_xudc_save_regs saved_regs;
	bool suspended;
	bool घातergated;

	काष्ठा usb_phy **usbphy;
	काष्ठा usb_phy *curr_usbphy;
	काष्ठा notअगरier_block vbus_nb;

	काष्ठा completion disconnect_complete;

	bool selfघातered;

#घोषणा TOGGLE_VBUS_WAIT_MS 100
	काष्ठा delayed_work plc_reset_work;
	bool रुको_csc;

	काष्ठा delayed_work port_reset_war_work;
	bool रुको_क्रम_sec_prc;
पूर्ण;

#घोषणा XUDC_TRB_MAX_BUFFER_SIZE 65536
#घोषणा XUDC_MAX_ISOCH_EPS 4
#घोषणा XUDC_INTERRUPT_MODERATION_US 0

अटल काष्ठा usb_endpoपूर्णांक_descriptor tegra_xudc_ep0_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress = 0,
	.bmAttributes = USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize = cpu_to_le16(64),
पूर्ण;

काष्ठा tegra_xudc_soc अणु
	स्थिर अक्षर * स्थिर *supply_names;
	अचिन्हित पूर्णांक num_supplies;
	स्थिर अक्षर * स्थिर *घड़ी_names;
	अचिन्हित पूर्णांक num_clks;
	अचिन्हित पूर्णांक num_phys;
	bool u1_enable;
	bool u2_enable;
	bool lpm_enable;
	bool invalid_seq_num;
	bool pls_quirk;
	bool port_reset_quirk;
	bool port_speed_quirk;
	bool has_ipfs;
पूर्ण;

अटल अंतरभूत u32 fpci_पढ़ोl(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(xudc->fpci + offset);
पूर्ण

अटल अंतरभूत व्योम fpci_ग_लिखोl(काष्ठा tegra_xudc *xudc, u32 val,
			       अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(val, xudc->fpci + offset);
पूर्ण

अटल अंतरभूत u32 ipfs_पढ़ोl(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(xudc->ipfs + offset);
पूर्ण

अटल अंतरभूत व्योम ipfs_ग_लिखोl(काष्ठा tegra_xudc *xudc, u32 val,
			       अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(val, xudc->ipfs + offset);
पूर्ण

अटल अंतरभूत u32 xudc_पढ़ोl(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(xudc->base + offset);
पूर्ण

अटल अंतरभूत व्योम xudc_ग_लिखोl(काष्ठा tegra_xudc *xudc, u32 val,
			       अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(val, xudc->base + offset);
पूर्ण

अटल अंतरभूत पूर्णांक xudc_पढ़ोl_poll(काष्ठा tegra_xudc *xudc,
				  अचिन्हित पूर्णांक offset, u32 mask, u32 val)
अणु
	u32 regval;

	वापस पढ़ोl_poll_समयout_atomic(xudc->base + offset, regval,
					 (regval & mask) == val, 1, 100);
पूर्ण

अटल अंतरभूत काष्ठा tegra_xudc *to_xudc(काष्ठा usb_gadget *gadget)
अणु
	वापस container_of(gadget, काष्ठा tegra_xudc, gadget);
पूर्ण

अटल अंतरभूत काष्ठा tegra_xudc_ep *to_xudc_ep(काष्ठा usb_ep *ep)
अणु
	वापस container_of(ep, काष्ठा tegra_xudc_ep, usb_ep);
पूर्ण

अटल अंतरभूत काष्ठा tegra_xudc_request *to_xudc_req(काष्ठा usb_request *req)
अणु
	वापस container_of(req, काष्ठा tegra_xudc_request, usb_req);
पूर्ण

अटल अंतरभूत व्योम dump_trb(काष्ठा tegra_xudc *xudc, स्थिर अक्षर *type,
			    काष्ठा tegra_xudc_trb *trb)
अणु
	dev_dbg(xudc->dev,
		"%s: %p, lo = %#x, hi = %#x, status = %#x, control = %#x\n",
		type, trb, trb->data_lo, trb->data_hi, trb->status,
		trb->control);
पूर्ण

अटल व्योम tegra_xudc_limit_port_speed(काष्ठा tegra_xudc *xudc)
अणु
	u32 val;

	/* limit port speed to gen 1 */
	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT56);
	val &= ~(SSPX_CORE_CNT56_SCD_BIT0_TRPT_MAX_MASK);
	val |= SSPX_CORE_CNT56_SCD_BIT0_TRPT_MAX(0x260);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT56);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT57);
	val &= ~(SSPX_CORE_CNT57_SCD_BIT1_TRPT_MAX_MASK);
	val |= SSPX_CORE_CNT57_SCD_BIT1_TRPT_MAX(0x6D6);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT57);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT65);
	val &= ~(SSPX_CORE_CNT65_TX_SCD_END_TRPT_MID_MASK);
	val |= SSPX_CORE_CNT65_TX_SCD_END_TRPT_MID(0x4B0);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT66);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT66);
	val &= ~(SSPX_CORE_CNT66_TX_SCD_BIT0_TRPT_MID_MASK);
	val |= SSPX_CORE_CNT66_TX_SCD_BIT0_TRPT_MID(0x4B0);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT66);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT67);
	val &= ~(SSPX_CORE_CNT67_TX_SCD_BIT1_TRPT_MID_MASK);
	val |= SSPX_CORE_CNT67_TX_SCD_BIT1_TRPT_MID(0x4B0);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT67);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT72);
	val &= ~(SSPX_CORE_CNT72_SCD_LFPS_TIMEOUT_MASK);
	val |= SSPX_CORE_CNT72_SCD_LFPS_TIMEOUT(0x10);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT72);
पूर्ण

अटल व्योम tegra_xudc_restore_port_speed(काष्ठा tegra_xudc *xudc)
अणु
	u32 val;

	/* restore port speed to gen2 */
	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT56);
	val &= ~(SSPX_CORE_CNT56_SCD_BIT0_TRPT_MAX_MASK);
	val |= SSPX_CORE_CNT56_SCD_BIT0_TRPT_MAX(0x438);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT56);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT57);
	val &= ~(SSPX_CORE_CNT57_SCD_BIT1_TRPT_MAX_MASK);
	val |= SSPX_CORE_CNT57_SCD_BIT1_TRPT_MAX(0x528);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT57);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT65);
	val &= ~(SSPX_CORE_CNT65_TX_SCD_END_TRPT_MID_MASK);
	val |= SSPX_CORE_CNT65_TX_SCD_END_TRPT_MID(0xE10);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT66);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT66);
	val &= ~(SSPX_CORE_CNT66_TX_SCD_BIT0_TRPT_MID_MASK);
	val |= SSPX_CORE_CNT66_TX_SCD_BIT0_TRPT_MID(0x348);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT66);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT67);
	val &= ~(SSPX_CORE_CNT67_TX_SCD_BIT1_TRPT_MID_MASK);
	val |= SSPX_CORE_CNT67_TX_SCD_BIT1_TRPT_MID(0x5a0);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT67);

	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT72);
	val &= ~(SSPX_CORE_CNT72_SCD_LFPS_TIMEOUT_MASK);
	val |= SSPX_CORE_CNT72_SCD_LFPS_TIMEOUT(0x1c21);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT72);
पूर्ण

अटल व्योम tegra_xudc_device_mode_on(काष्ठा tegra_xudc *xudc)
अणु
	पूर्णांक err;

	pm_runसमय_get_sync(xudc->dev);

	err = phy_घातer_on(xudc->curr_uपंचांगi_phy);
	अगर (err < 0)
		dev_err(xudc->dev, "UTMI power on failed: %d\n", err);

	err = phy_घातer_on(xudc->curr_usb3_phy);
	अगर (err < 0)
		dev_err(xudc->dev, "USB3 PHY power on failed: %d\n", err);

	dev_dbg(xudc->dev, "device mode on\n");

	phy_set_mode_ext(xudc->curr_uपंचांगi_phy, PHY_MODE_USB_OTG,
			 USB_ROLE_DEVICE);
पूर्ण

अटल व्योम tegra_xudc_device_mode_off(काष्ठा tegra_xudc *xudc)
अणु
	bool connected = false;
	u32 pls, val;
	पूर्णांक err;

	dev_dbg(xudc->dev, "device mode off\n");

	connected = !!(xudc_पढ़ोl(xudc, PORTSC) & PORTSC_CCS);

	reinit_completion(&xudc->disconnect_complete);

	अगर (xudc->soc->port_speed_quirk)
		tegra_xudc_restore_port_speed(xudc);

	phy_set_mode_ext(xudc->curr_uपंचांगi_phy, PHY_MODE_USB_OTG, USB_ROLE_NONE);

	pls = (xudc_पढ़ोl(xudc, PORTSC) & PORTSC_PLS_MASK) >>
		PORTSC_PLS_SHIFT;

	/* Direct link to U0 अगर disconnected in RESUME or U2. */
	अगर (xudc->soc->pls_quirk && xudc->gadget.speed == USB_SPEED_SUPER &&
	    (pls == PORTSC_PLS_RESUME || pls == PORTSC_PLS_U2)) अणु
		val = xudc_पढ़ोl(xudc, PORTPM);
		val |= PORTPM_FRWE;
		xudc_ग_लिखोl(xudc, val, PORTPM);

		val = xudc_पढ़ोl(xudc, PORTSC);
		val &= ~(PORTSC_CHANGE_MASK | PORTSC_PLS_MASK);
		val |= PORTSC_LWS | PORTSC_PLS(PORTSC_PLS_U0);
		xudc_ग_लिखोl(xudc, val, PORTSC);
	पूर्ण

	/* Wait क्रम disconnect event. */
	अगर (connected)
		रुको_क्रम_completion(&xudc->disconnect_complete);

	/* Make sure पूर्णांकerrupt handler has completed beक्रमe घातergating. */
	synchronize_irq(xudc->irq);

	err = phy_घातer_off(xudc->curr_uपंचांगi_phy);
	अगर (err < 0)
		dev_err(xudc->dev, "UTMI PHY power off failed: %d\n", err);

	err = phy_घातer_off(xudc->curr_usb3_phy);
	अगर (err < 0)
		dev_err(xudc->dev, "USB3 PHY power off failed: %d\n", err);

	pm_runसमय_put(xudc->dev);
पूर्ण

अटल व्योम tegra_xudc_usb_role_sw_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tegra_xudc *xudc = container_of(work, काष्ठा tegra_xudc,
					       usb_role_sw_work);

	अगर (xudc->device_mode)
		tegra_xudc_device_mode_on(xudc);
	अन्यथा
		tegra_xudc_device_mode_off(xudc);
पूर्ण

अटल पूर्णांक tegra_xudc_get_phy_index(काष्ठा tegra_xudc *xudc,
					      काष्ठा usb_phy *usbphy)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < xudc->soc->num_phys; i++) अणु
		अगर (xudc->usbphy[i] && usbphy == xudc->usbphy[i])
			वापस i;
	पूर्ण

	dev_info(xudc->dev, "phy index could not be found for shared USB PHY");
	वापस -1;
पूर्ण

अटल पूर्णांक tegra_xudc_vbus_notअगरy(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा tegra_xudc *xudc = container_of(nb, काष्ठा tegra_xudc,
					       vbus_nb);
	काष्ठा usb_phy *usbphy = (काष्ठा usb_phy *)data;
	पूर्णांक phy_index;

	dev_dbg(xudc->dev, "%s(): event is %d\n", __func__, usbphy->last_event);

	अगर ((xudc->device_mode && usbphy->last_event == USB_EVENT_VBUS) ||
	    (!xudc->device_mode && usbphy->last_event != USB_EVENT_VBUS)) अणु
		dev_dbg(xudc->dev, "Same role(%d) received. Ignore",
			xudc->device_mode);
		वापस NOTIFY_OK;
	पूर्ण

	xudc->device_mode = (usbphy->last_event == USB_EVENT_VBUS) ? true :
								     false;

	phy_index = tegra_xudc_get_phy_index(xudc, usbphy);
	dev_dbg(xudc->dev, "%s(): current phy index is %d\n", __func__,
		phy_index);

	अगर (!xudc->suspended && phy_index != -1) अणु
		xudc->curr_uपंचांगi_phy = xudc->uपंचांगi_phy[phy_index];
		xudc->curr_usb3_phy = xudc->usb3_phy[phy_index];
		xudc->curr_usbphy = usbphy;
		schedule_work(&xudc->usb_role_sw_work);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम tegra_xudc_plc_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा tegra_xudc *xudc = container_of(dwork, काष्ठा tegra_xudc,
					       plc_reset_work);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&xudc->lock, flags);

	अगर (xudc->रुको_csc) अणु
		u32 pls = (xudc_पढ़ोl(xudc, PORTSC) & PORTSC_PLS_MASK) >>
			PORTSC_PLS_SHIFT;

		अगर (pls == PORTSC_PLS_INACTIVE) अणु
			dev_info(xudc->dev, "PLS = Inactive. Toggle VBUS\n");
			phy_set_mode_ext(xudc->curr_uपंचांगi_phy, PHY_MODE_USB_OTG,
					 USB_ROLE_NONE);
			phy_set_mode_ext(xudc->curr_uपंचांगi_phy, PHY_MODE_USB_OTG,
					 USB_ROLE_DEVICE);

			xudc->रुको_csc = false;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&xudc->lock, flags);
पूर्ण

अटल व्योम tegra_xudc_port_reset_war_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा tegra_xudc *xudc =
		container_of(dwork, काष्ठा tegra_xudc, port_reset_war_work);
	अचिन्हित दीर्घ flags;
	u32 pls;
	पूर्णांक ret;

	spin_lock_irqsave(&xudc->lock, flags);

	अगर (xudc->device_mode && xudc->रुको_क्रम_sec_prc) अणु
		pls = (xudc_पढ़ोl(xudc, PORTSC) & PORTSC_PLS_MASK) >>
			PORTSC_PLS_SHIFT;
		dev_dbg(xudc->dev, "pls = %x\n", pls);

		अगर (pls == PORTSC_PLS_DISABLED) अणु
			dev_dbg(xudc->dev, "toggle vbus\n");
			/* PRC करोesn't complete in 100ms, toggle the vbus */
			ret = tegra_phy_xusb_uपंचांगi_port_reset(
				xudc->curr_uपंचांगi_phy);
			अगर (ret == 1)
				xudc->रुको_क्रम_sec_prc = 0;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&xudc->lock, flags);
पूर्ण

अटल dma_addr_t trb_virt_to_phys(काष्ठा tegra_xudc_ep *ep,
				   काष्ठा tegra_xudc_trb *trb)
अणु
	अचिन्हित पूर्णांक index;

	index = trb - ep->transfer_ring;

	अगर (WARN_ON(index >= XUDC_TRANSFER_RING_SIZE))
		वापस 0;

	वापस (ep->transfer_ring_phys + index * माप(*trb));
पूर्ण

अटल काष्ठा tegra_xudc_trb *trb_phys_to_virt(काष्ठा tegra_xudc_ep *ep,
					       dma_addr_t addr)
अणु
	काष्ठा tegra_xudc_trb *trb;
	अचिन्हित पूर्णांक index;

	index = (addr - ep->transfer_ring_phys) / माप(*trb);

	अगर (WARN_ON(index >= XUDC_TRANSFER_RING_SIZE))
		वापस शून्य;

	trb = &ep->transfer_ring[index];

	वापस trb;
पूर्ण

अटल व्योम ep_reload(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक ep)
अणु
	xudc_ग_लिखोl(xudc, BIT(ep), EP_RELOAD);
	xudc_पढ़ोl_poll(xudc, EP_RELOAD, BIT(ep), 0);
पूर्ण

अटल व्योम ep_छोड़ो(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक ep)
अणु
	u32 val;

	val = xudc_पढ़ोl(xudc, EP_PAUSE);
	अगर (val & BIT(ep))
		वापस;
	val |= BIT(ep);

	xudc_ग_लिखोl(xudc, val, EP_PAUSE);

	xudc_पढ़ोl_poll(xudc, EP_STCHG, BIT(ep), BIT(ep));

	xudc_ग_लिखोl(xudc, BIT(ep), EP_STCHG);
पूर्ण

अटल व्योम ep_unछोड़ो(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक ep)
अणु
	u32 val;

	val = xudc_पढ़ोl(xudc, EP_PAUSE);
	अगर (!(val & BIT(ep)))
		वापस;
	val &= ~BIT(ep);

	xudc_ग_लिखोl(xudc, val, EP_PAUSE);

	xudc_पढ़ोl_poll(xudc, EP_STCHG, BIT(ep), BIT(ep));

	xudc_ग_लिखोl(xudc, BIT(ep), EP_STCHG);
पूर्ण

अटल व्योम ep_unछोड़ो_all(काष्ठा tegra_xudc *xudc)
अणु
	u32 val;

	val = xudc_पढ़ोl(xudc, EP_PAUSE);

	xudc_ग_लिखोl(xudc, 0, EP_PAUSE);

	xudc_पढ़ोl_poll(xudc, EP_STCHG, val, val);

	xudc_ग_लिखोl(xudc, val, EP_STCHG);
पूर्ण

अटल व्योम ep_halt(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक ep)
अणु
	u32 val;

	val = xudc_पढ़ोl(xudc, EP_HALT);
	अगर (val & BIT(ep))
		वापस;
	val |= BIT(ep);
	xudc_ग_लिखोl(xudc, val, EP_HALT);

	xudc_पढ़ोl_poll(xudc, EP_STCHG, BIT(ep), BIT(ep));

	xudc_ग_लिखोl(xudc, BIT(ep), EP_STCHG);
पूर्ण

अटल व्योम ep_unhalt(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक ep)
अणु
	u32 val;

	val = xudc_पढ़ोl(xudc, EP_HALT);
	अगर (!(val & BIT(ep)))
		वापस;
	val &= ~BIT(ep);
	xudc_ग_लिखोl(xudc, val, EP_HALT);

	xudc_पढ़ोl_poll(xudc, EP_STCHG, BIT(ep), BIT(ep));

	xudc_ग_लिखोl(xudc, BIT(ep), EP_STCHG);
पूर्ण

अटल व्योम ep_unhalt_all(काष्ठा tegra_xudc *xudc)
अणु
	u32 val;

	val = xudc_पढ़ोl(xudc, EP_HALT);
	अगर (!val)
		वापस;
	xudc_ग_लिखोl(xudc, 0, EP_HALT);

	xudc_पढ़ोl_poll(xudc, EP_STCHG, val, val);

	xudc_ग_लिखोl(xudc, val, EP_STCHG);
पूर्ण

अटल व्योम ep_रुको_क्रम_stopped(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक ep)
अणु
	xudc_पढ़ोl_poll(xudc, EP_STOPPED, BIT(ep), BIT(ep));
	xudc_ग_लिखोl(xudc, BIT(ep), EP_STOPPED);
पूर्ण

अटल व्योम ep_रुको_क्रम_inactive(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक ep)
अणु
	xudc_पढ़ोl_poll(xudc, EP_THREAD_ACTIVE, BIT(ep), 0);
पूर्ण

अटल व्योम tegra_xudc_req_करोne(काष्ठा tegra_xudc_ep *ep,
				काष्ठा tegra_xudc_request *req, पूर्णांक status)
अणु
	काष्ठा tegra_xudc *xudc = ep->xudc;

	dev_dbg(xudc->dev, "completing request %p on EP %u with status %d\n",
		 req, ep->index, status);

	अगर (likely(req->usb_req.status == -EINPROGRESS))
		req->usb_req.status = status;

	list_del_init(&req->list);

	अगर (usb_endpoपूर्णांक_xfer_control(ep->desc)) अणु
		usb_gadget_unmap_request(&xudc->gadget, &req->usb_req,
					 (xudc->setup_state ==
					  DATA_STAGE_XFER));
	पूर्ण अन्यथा अणु
		usb_gadget_unmap_request(&xudc->gadget, &req->usb_req,
					 usb_endpoपूर्णांक_dir_in(ep->desc));
	पूर्ण

	spin_unlock(&xudc->lock);
	usb_gadget_giveback_request(&ep->usb_ep, &req->usb_req);
	spin_lock(&xudc->lock);
पूर्ण

अटल व्योम tegra_xudc_ep_nuke(काष्ठा tegra_xudc_ep *ep, पूर्णांक status)
अणु
	काष्ठा tegra_xudc_request *req;

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_first_entry(&ep->queue, काष्ठा tegra_xudc_request,
				       list);
		tegra_xudc_req_करोne(ep, req, status);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ep_available_trbs(काष्ठा tegra_xudc_ep *ep)
अणु
	अगर (ep->ring_full)
		वापस 0;

	अगर (ep->deq_ptr > ep->enq_ptr)
		वापस ep->deq_ptr - ep->enq_ptr - 1;

	वापस XUDC_TRANSFER_RING_SIZE - (ep->enq_ptr - ep->deq_ptr) - 2;
पूर्ण

अटल व्योम tegra_xudc_queue_one_trb(काष्ठा tegra_xudc_ep *ep,
				     काष्ठा tegra_xudc_request *req,
				     काष्ठा tegra_xudc_trb *trb,
				     bool ioc)
अणु
	काष्ठा tegra_xudc *xudc = ep->xudc;
	dma_addr_t buf_addr;
	माप_प्रकार len;

	len = min_t(माप_प्रकार, XUDC_TRB_MAX_BUFFER_SIZE, req->usb_req.length -
		    req->buf_queued);
	अगर (len > 0)
		buf_addr = req->usb_req.dma + req->buf_queued;
	अन्यथा
		buf_addr = 0;

	trb_ग_लिखो_data_ptr(trb, buf_addr);

	trb_ग_लिखो_transfer_len(trb, len);
	trb_ग_लिखो_td_size(trb, req->trbs_needed - req->trbs_queued - 1);

	अगर (req->trbs_queued == req->trbs_needed - 1 ||
		(req->need_zlp && req->trbs_queued == req->trbs_needed - 2))
		trb_ग_लिखो_chain(trb, 0);
	अन्यथा
		trb_ग_लिखो_chain(trb, 1);

	trb_ग_लिखो_ioc(trb, ioc);

	अगर (usb_endpoपूर्णांक_dir_out(ep->desc) ||
	    (usb_endpoपूर्णांक_xfer_control(ep->desc) &&
	     (xudc->setup_state == DATA_STAGE_RECV)))
		trb_ग_लिखो_isp(trb, 1);
	अन्यथा
		trb_ग_लिखो_isp(trb, 0);

	अगर (usb_endpoपूर्णांक_xfer_control(ep->desc)) अणु
		अगर (xudc->setup_state == DATA_STAGE_XFER ||
		    xudc->setup_state == DATA_STAGE_RECV)
			trb_ग_लिखो_type(trb, TRB_TYPE_DATA_STAGE);
		अन्यथा
			trb_ग_लिखो_type(trb, TRB_TYPE_STATUS_STAGE);

		अगर (xudc->setup_state == DATA_STAGE_XFER ||
		    xudc->setup_state == STATUS_STAGE_XFER)
			trb_ग_लिखो_data_stage_dir(trb, 1);
		अन्यथा
			trb_ग_लिखो_data_stage_dir(trb, 0);
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_isoc(ep->desc)) अणु
		trb_ग_लिखो_type(trb, TRB_TYPE_ISOCH);
		trb_ग_लिखो_sia(trb, 1);
		trb_ग_लिखो_frame_id(trb, 0);
		trb_ग_लिखो_tlbpc(trb, 0);
	पूर्ण अन्यथा अगर (usb_ss_max_streams(ep->comp_desc)) अणु
		trb_ग_लिखो_type(trb, TRB_TYPE_STREAM);
		trb_ग_लिखो_stream_id(trb, req->usb_req.stream_id);
	पूर्ण अन्यथा अणु
		trb_ग_लिखो_type(trb, TRB_TYPE_NORMAL);
		trb_ग_लिखो_stream_id(trb, 0);
	पूर्ण

	trb_ग_लिखो_cycle(trb, ep->pcs);

	req->trbs_queued++;
	req->buf_queued += len;

	dump_trb(xudc, "TRANSFER", trb);
पूर्ण

अटल अचिन्हित पूर्णांक tegra_xudc_queue_trbs(काष्ठा tegra_xudc_ep *ep,
					  काष्ठा tegra_xudc_request *req)
अणु
	अचिन्हित पूर्णांक i, count, available;
	bool रुको_td = false;

	available = ep_available_trbs(ep);
	count = req->trbs_needed - req->trbs_queued;
	अगर (available < count) अणु
		count = available;
		ep->ring_full = true;
	पूर्ण

	/*
	 * To generate zero-length packet on USB bus, SW needs schedule a
	 * standalone zero-length TD. According to HW's behavior, SW needs
	 * to schedule TDs in dअगरferent ways क्रम dअगरferent endpoपूर्णांक types.
	 *
	 * For control endpoपूर्णांक:
	 * - Data stage TD (IOC = 1, CH = 0)
	 * - Ring करोorbell and रुको transfer event
	 * - Data stage TD क्रम ZLP (IOC = 1, CH = 0)
	 * - Ring करोorbell
	 *
	 * For bulk and पूर्णांकerrupt endpoपूर्णांकs:
	 * - Normal transfer TD (IOC = 0, CH = 0)
	 * - Normal transfer TD क्रम ZLP (IOC = 1, CH = 0)
	 * - Ring करोorbell
	 */

	अगर (req->need_zlp && usb_endpoपूर्णांक_xfer_control(ep->desc) && count > 1)
		रुको_td = true;

	अगर (!req->first_trb)
		req->first_trb = &ep->transfer_ring[ep->enq_ptr];

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा tegra_xudc_trb *trb = &ep->transfer_ring[ep->enq_ptr];
		bool ioc = false;

		अगर ((i == count - 1) || (रुको_td && i == count - 2))
			ioc = true;

		tegra_xudc_queue_one_trb(ep, req, trb, ioc);
		req->last_trb = trb;

		ep->enq_ptr++;
		अगर (ep->enq_ptr == XUDC_TRANSFER_RING_SIZE - 1) अणु
			trb = &ep->transfer_ring[ep->enq_ptr];
			trb_ग_लिखो_cycle(trb, ep->pcs);
			ep->pcs = !ep->pcs;
			ep->enq_ptr = 0;
		पूर्ण

		अगर (ioc)
			अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम tegra_xudc_ep_ring_करोorbell(काष्ठा tegra_xudc_ep *ep)
अणु
	काष्ठा tegra_xudc *xudc = ep->xudc;
	u32 val;

	अगर (list_empty(&ep->queue))
		वापस;

	val = DB_TARGET(ep->index);
	अगर (usb_endpoपूर्णांक_xfer_control(ep->desc)) अणु
		val |= DB_STREAMID(xudc->setup_seq_num);
	पूर्ण अन्यथा अगर (usb_ss_max_streams(ep->comp_desc) > 0) अणु
		काष्ठा tegra_xudc_request *req;

		/* Don't ring करोorbell अगर the stream has been rejected. */
		अगर (ep->stream_rejected)
			वापस;

		req = list_first_entry(&ep->queue, काष्ठा tegra_xudc_request,
				       list);
		val |= DB_STREAMID(req->usb_req.stream_id);
	पूर्ण

	dev_dbg(xudc->dev, "ring doorbell: %#x\n", val);
	xudc_ग_लिखोl(xudc, val, DB);
पूर्ण

अटल व्योम tegra_xudc_ep_kick_queue(काष्ठा tegra_xudc_ep *ep)
अणु
	काष्ठा tegra_xudc_request *req;
	bool trbs_queued = false;

	list_क्रम_each_entry(req, &ep->queue, list) अणु
		अगर (ep->ring_full)
			अवरोध;

		अगर (tegra_xudc_queue_trbs(ep, req) > 0)
			trbs_queued = true;
	पूर्ण

	अगर (trbs_queued)
		tegra_xudc_ep_ring_करोorbell(ep);
पूर्ण

अटल पूर्णांक
__tegra_xudc_ep_queue(काष्ठा tegra_xudc_ep *ep, काष्ठा tegra_xudc_request *req)
अणु
	काष्ठा tegra_xudc *xudc = ep->xudc;
	पूर्णांक err;

	अगर (usb_endpoपूर्णांक_xfer_control(ep->desc) && !list_empty(&ep->queue)) अणु
		dev_err(xudc->dev, "control EP has pending transfers\n");
		वापस -EINVAL;
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_control(ep->desc)) अणु
		err = usb_gadget_map_request(&xudc->gadget, &req->usb_req,
					     (xudc->setup_state ==
					      DATA_STAGE_XFER));
	पूर्ण अन्यथा अणु
		err = usb_gadget_map_request(&xudc->gadget, &req->usb_req,
					     usb_endpoपूर्णांक_dir_in(ep->desc));
	पूर्ण

	अगर (err < 0) अणु
		dev_err(xudc->dev, "failed to map request: %d\n", err);
		वापस err;
	पूर्ण

	req->first_trb = शून्य;
	req->last_trb = शून्य;
	req->buf_queued = 0;
	req->trbs_queued = 0;
	req->need_zlp = false;
	req->trbs_needed = DIV_ROUND_UP(req->usb_req.length,
					XUDC_TRB_MAX_BUFFER_SIZE);
	अगर (req->usb_req.length == 0)
		req->trbs_needed++;

	अगर (!usb_endpoपूर्णांक_xfer_isoc(ep->desc) &&
	    req->usb_req.zero && req->usb_req.length &&
	    ((req->usb_req.length % ep->usb_ep.maxpacket) == 0)) अणु
		req->trbs_needed++;
		req->need_zlp = true;
	पूर्ण

	req->usb_req.status = -EINPROGRESS;
	req->usb_req.actual = 0;

	list_add_tail(&req->list, &ep->queue);

	tegra_xudc_ep_kick_queue(ep);

	वापस 0;
पूर्ण

अटल पूर्णांक
tegra_xudc_ep_queue(काष्ठा usb_ep *usb_ep, काष्ठा usb_request *usb_req,
		    gfp_t gfp)
अणु
	काष्ठा tegra_xudc_request *req;
	काष्ठा tegra_xudc_ep *ep;
	काष्ठा tegra_xudc *xudc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!usb_ep || !usb_req)
		वापस -EINVAL;

	ep = to_xudc_ep(usb_ep);
	req = to_xudc_req(usb_req);
	xudc = ep->xudc;

	spin_lock_irqsave(&xudc->lock, flags);
	अगर (xudc->घातergated || !ep->desc) अणु
		ret = -ESHUTDOWN;
		जाओ unlock;
	पूर्ण

	ret = __tegra_xudc_ep_queue(ep, req);
unlock:
	spin_unlock_irqrestore(&xudc->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम squeeze_transfer_ring(काष्ठा tegra_xudc_ep *ep,
				  काष्ठा tegra_xudc_request *req)
अणु
	काष्ठा tegra_xudc_trb *trb = req->first_trb;
	bool pcs_enq = trb_पढ़ो_cycle(trb);
	bool pcs;

	/*
	 * Clear out all the TRBs part of or after the cancelled request,
	 * and must correct trb cycle bit to the last un-enqueued state.
	 */
	जबतक (trb != &ep->transfer_ring[ep->enq_ptr]) अणु
		pcs = trb_पढ़ो_cycle(trb);
		स_रखो(trb, 0, माप(*trb));
		trb_ग_लिखो_cycle(trb, !pcs);
		trb++;

		अगर (trb_पढ़ो_type(trb) == TRB_TYPE_LINK)
			trb = ep->transfer_ring;
	पूर्ण

	/* Requests will be re-queued at the start of the cancelled request. */
	ep->enq_ptr = req->first_trb - ep->transfer_ring;
	/*
	 * Retrieve the correct cycle bit state from the first trb of
	 * the cancelled request.
	 */
	ep->pcs = pcs_enq;
	ep->ring_full = false;
	list_क्रम_each_entry_जारी(req, &ep->queue, list) अणु
		req->usb_req.status = -EINPROGRESS;
		req->usb_req.actual = 0;

		req->first_trb = शून्य;
		req->last_trb = शून्य;
		req->buf_queued = 0;
		req->trbs_queued = 0;
	पूर्ण
पूर्ण

/*
 * Determine अगर the given TRB is in the range [first trb, last trb] क्रम the
 * given request.
 */
अटल bool trb_in_request(काष्ठा tegra_xudc_ep *ep,
			   काष्ठा tegra_xudc_request *req,
			   काष्ठा tegra_xudc_trb *trb)
अणु
	dev_dbg(ep->xudc->dev, "%s: request %p -> %p; trb %p\n", __func__,
		req->first_trb, req->last_trb, trb);

	अगर (trb >= req->first_trb && (trb <= req->last_trb ||
				      req->last_trb < req->first_trb))
		वापस true;

	अगर (trb < req->first_trb && trb <= req->last_trb &&
	    req->last_trb < req->first_trb)
		वापस true;

	वापस false;
पूर्ण

/*
 * Determine अगर the given TRB is in the range [EP enqueue poपूर्णांकer, first TRB)
 * क्रम the given endpoपूर्णांक and request.
 */
अटल bool trb_beक्रमe_request(काष्ठा tegra_xudc_ep *ep,
			       काष्ठा tegra_xudc_request *req,
			       काष्ठा tegra_xudc_trb *trb)
अणु
	काष्ठा tegra_xudc_trb *enq_trb = &ep->transfer_ring[ep->enq_ptr];

	dev_dbg(ep->xudc->dev, "%s: request %p -> %p; enq ptr: %p; trb %p\n",
		__func__, req->first_trb, req->last_trb, enq_trb, trb);

	अगर (trb < req->first_trb && (enq_trb <= trb ||
				     req->first_trb < enq_trb))
		वापस true;

	अगर (trb > req->first_trb && req->first_trb < enq_trb && enq_trb <= trb)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक
__tegra_xudc_ep_dequeue(काष्ठा tegra_xudc_ep *ep,
			काष्ठा tegra_xudc_request *req)
अणु
	काष्ठा tegra_xudc *xudc = ep->xudc;
	काष्ठा tegra_xudc_request *r;
	काष्ठा tegra_xudc_trb *deq_trb;
	bool busy, kick_queue = false;
	पूर्णांक ret = 0;

	/* Make sure the request is actually queued to this endpoपूर्णांक. */
	list_क्रम_each_entry(r, &ep->queue, list) अणु
		अगर (r == req)
			अवरोध;
	पूर्ण

	अगर (r != req)
		वापस -EINVAL;

	/* Request hasn't been queued in the transfer ring yet. */
	अगर (!req->trbs_queued) अणु
		tegra_xudc_req_करोne(ep, req, -ECONNRESET);
		वापस 0;
	पूर्ण

	/* Halt DMA क्रम this endpiont. */
	अगर (ep_ctx_पढ़ो_state(ep->context) == EP_STATE_RUNNING) अणु
		ep_छोड़ो(xudc, ep->index);
		ep_रुको_क्रम_inactive(xudc, ep->index);
	पूर्ण

	deq_trb = trb_phys_to_virt(ep, ep_ctx_पढ़ो_deq_ptr(ep->context));
	/* Is the hardware processing the TRB at the dequeue poपूर्णांकer? */
	busy = (trb_पढ़ो_cycle(deq_trb) == ep_ctx_पढ़ो_dcs(ep->context));

	अगर (trb_in_request(ep, req, deq_trb) && busy) अणु
		/*
		 * Request has been partially completed or it hasn't
		 * started processing yet.
		 */
		dma_addr_t deq_ptr;

		squeeze_transfer_ring(ep, req);

		req->usb_req.actual = ep_ctx_पढ़ो_edtla(ep->context);
		tegra_xudc_req_करोne(ep, req, -ECONNRESET);
		kick_queue = true;

		/* EDTLA is > 0: request has been partially completed */
		अगर (req->usb_req.actual > 0) अणु
			/*
			 * Abort the pending transfer and update the dequeue
			 * poपूर्णांकer
			 */
			ep_ctx_ग_लिखो_edtla(ep->context, 0);
			ep_ctx_ग_लिखो_partial_td(ep->context, 0);
			ep_ctx_ग_लिखो_data_offset(ep->context, 0);

			deq_ptr = trb_virt_to_phys(ep,
					&ep->transfer_ring[ep->enq_ptr]);

			अगर (dma_mapping_error(xudc->dev, deq_ptr)) अणु
				ret = -EINVAL;
			पूर्ण अन्यथा अणु
				ep_ctx_ग_लिखो_deq_ptr(ep->context, deq_ptr);
				ep_ctx_ग_लिखो_dcs(ep->context, ep->pcs);
				ep_reload(xudc, ep->index);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (trb_beक्रमe_request(ep, req, deq_trb) && busy) अणु
		/* Request hasn't started processing yet. */
		squeeze_transfer_ring(ep, req);

		tegra_xudc_req_करोne(ep, req, -ECONNRESET);
		kick_queue = true;
	पूर्ण अन्यथा अणु
		/*
		 * Request has completed, but we haven't processed the
		 * completion event yet.
		 */
		tegra_xudc_req_करोne(ep, req, -ECONNRESET);
		ret = -EINVAL;
	पूर्ण

	/* Resume the endpoपूर्णांक. */
	ep_unछोड़ो(xudc, ep->index);

	अगर (kick_queue)
		tegra_xudc_ep_kick_queue(ep);

	वापस ret;
पूर्ण

अटल पूर्णांक
tegra_xudc_ep_dequeue(काष्ठा usb_ep *usb_ep, काष्ठा usb_request *usb_req)
अणु
	काष्ठा tegra_xudc_request *req;
	काष्ठा tegra_xudc_ep *ep;
	काष्ठा tegra_xudc *xudc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!usb_ep || !usb_req)
		वापस -EINVAL;

	ep = to_xudc_ep(usb_ep);
	req = to_xudc_req(usb_req);
	xudc = ep->xudc;

	spin_lock_irqsave(&xudc->lock, flags);

	अगर (xudc->घातergated || !ep->desc) अणु
		ret = -ESHUTDOWN;
		जाओ unlock;
	पूर्ण

	ret = __tegra_xudc_ep_dequeue(ep, req);
unlock:
	spin_unlock_irqrestore(&xudc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक __tegra_xudc_ep_set_halt(काष्ठा tegra_xudc_ep *ep, bool halt)
अणु
	काष्ठा tegra_xudc *xudc = ep->xudc;

	अगर (!ep->desc)
		वापस -EINVAL;

	अगर (usb_endpoपूर्णांक_xfer_isoc(ep->desc)) अणु
		dev_err(xudc->dev, "can't halt isochronous EP\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!!(xudc_पढ़ोl(xudc, EP_HALT) & BIT(ep->index)) == halt) अणु
		dev_dbg(xudc->dev, "EP %u already %s\n", ep->index,
			halt ? "halted" : "not halted");
		वापस 0;
	पूर्ण

	अगर (halt) अणु
		ep_halt(xudc, ep->index);
	पूर्ण अन्यथा अणु
		ep_ctx_ग_लिखो_state(ep->context, EP_STATE_DISABLED);

		ep_reload(xudc, ep->index);

		ep_ctx_ग_लिखो_state(ep->context, EP_STATE_RUNNING);
		ep_ctx_ग_लिखो_seq_num(ep->context, 0);

		ep_reload(xudc, ep->index);
		ep_unछोड़ो(xudc, ep->index);
		ep_unhalt(xudc, ep->index);

		tegra_xudc_ep_ring_करोorbell(ep);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xudc_ep_set_halt(काष्ठा usb_ep *usb_ep, पूर्णांक value)
अणु
	काष्ठा tegra_xudc_ep *ep;
	काष्ठा tegra_xudc *xudc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!usb_ep)
		वापस -EINVAL;

	ep = to_xudc_ep(usb_ep);
	xudc = ep->xudc;

	spin_lock_irqsave(&xudc->lock, flags);
	अगर (xudc->घातergated) अणु
		ret = -ESHUTDOWN;
		जाओ unlock;
	पूर्ण

	अगर (value && usb_endpoपूर्णांक_dir_in(ep->desc) &&
	    !list_empty(&ep->queue)) अणु
		dev_err(xudc->dev, "can't halt EP with requests pending\n");
		ret = -EAGAIN;
		जाओ unlock;
	पूर्ण

	ret = __tegra_xudc_ep_set_halt(ep, value);
unlock:
	spin_unlock_irqrestore(&xudc->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम tegra_xudc_ep_context_setup(काष्ठा tegra_xudc_ep *ep)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc = ep->desc;
	स्थिर काष्ठा usb_ss_ep_comp_descriptor *comp_desc = ep->comp_desc;
	काष्ठा tegra_xudc *xudc = ep->xudc;
	u16 maxpacket, maxburst = 0, esit = 0;
	u32 val;

	maxpacket = usb_endpoपूर्णांक_maxp(desc) & 0x7ff;
	अगर (xudc->gadget.speed == USB_SPEED_SUPER) अणु
		अगर (!usb_endpoपूर्णांक_xfer_control(desc))
			maxburst = comp_desc->bMaxBurst;

		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(desc) || usb_endpoपूर्णांक_xfer_isoc(desc))
			esit = le16_to_cpu(comp_desc->wBytesPerInterval);
	पूर्ण अन्यथा अगर ((xudc->gadget.speed < USB_SPEED_SUPER) &&
		   (usb_endpoपूर्णांक_xfer_पूर्णांक(desc) ||
		    usb_endpoपूर्णांक_xfer_isoc(desc))) अणु
		अगर (xudc->gadget.speed == USB_SPEED_HIGH) अणु
			maxburst = (usb_endpoपूर्णांक_maxp(desc) >> 11) & 0x3;
			अगर (maxburst == 0x3) अणु
				dev_warn(xudc->dev,
					 "invalid endpoint maxburst\n");
				maxburst = 0x2;
			पूर्ण
		पूर्ण
		esit = maxpacket * (maxburst + 1);
	पूर्ण

	स_रखो(ep->context, 0, माप(*ep->context));

	ep_ctx_ग_लिखो_state(ep->context, EP_STATE_RUNNING);
	ep_ctx_ग_लिखो_पूर्णांकerval(ep->context, desc->bInterval);
	अगर (xudc->gadget.speed == USB_SPEED_SUPER) अणु
		अगर (usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
			ep_ctx_ग_लिखो_mult(ep->context,
					  comp_desc->bmAttributes & 0x3);
		पूर्ण

		अगर (usb_endpoपूर्णांक_xfer_bulk(desc)) अणु
			ep_ctx_ग_लिखो_max_pstreams(ep->context,
						  comp_desc->bmAttributes &
						  0x1f);
			ep_ctx_ग_लिखो_lsa(ep->context, 1);
		पूर्ण
	पूर्ण

	अगर (!usb_endpoपूर्णांक_xfer_control(desc) && usb_endpoपूर्णांक_dir_out(desc))
		val = usb_endpoपूर्णांक_type(desc);
	अन्यथा
		val = usb_endpoपूर्णांक_type(desc) + EP_TYPE_CONTROL;

	ep_ctx_ग_लिखो_type(ep->context, val);
	ep_ctx_ग_लिखो_cerr(ep->context, 0x3);
	ep_ctx_ग_लिखो_max_packet_size(ep->context, maxpacket);
	ep_ctx_ग_लिखो_max_burst_size(ep->context, maxburst);

	ep_ctx_ग_लिखो_deq_ptr(ep->context, ep->transfer_ring_phys);
	ep_ctx_ग_लिखो_dcs(ep->context, ep->pcs);

	/* Select a reasonable average TRB length based on endpoपूर्णांक type. */
	चयन (usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		val = 8;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		val = 1024;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_ISOC:
	शेष:
		val = 3072;
		अवरोध;
	पूर्ण

	ep_ctx_ग_लिखो_avg_trb_len(ep->context, val);
	ep_ctx_ग_लिखो_max_esit_payload(ep->context, esit);

	ep_ctx_ग_लिखो_cerrcnt(ep->context, 0x3);
पूर्ण

अटल व्योम setup_link_trb(काष्ठा tegra_xudc_ep *ep,
			   काष्ठा tegra_xudc_trb *trb)
अणु
	trb_ग_लिखो_data_ptr(trb, ep->transfer_ring_phys);
	trb_ग_लिखो_type(trb, TRB_TYPE_LINK);
	trb_ग_लिखो_toggle_cycle(trb, 1);
पूर्ण

अटल पूर्णांक __tegra_xudc_ep_disable(काष्ठा tegra_xudc_ep *ep)
अणु
	काष्ठा tegra_xudc *xudc = ep->xudc;

	अगर (ep_ctx_पढ़ो_state(ep->context) == EP_STATE_DISABLED) अणु
		dev_err(xudc->dev, "endpoint %u already disabled\n",
			ep->index);
		वापस -EINVAL;
	पूर्ण

	ep_ctx_ग_लिखो_state(ep->context, EP_STATE_DISABLED);

	ep_reload(xudc, ep->index);

	tegra_xudc_ep_nuke(ep, -ESHUTDOWN);

	xudc->nr_enabled_eps--;
	अगर (usb_endpoपूर्णांक_xfer_isoc(ep->desc))
		xudc->nr_isoch_eps--;

	ep->desc = शून्य;
	ep->comp_desc = शून्य;

	स_रखो(ep->context, 0, माप(*ep->context));

	ep_unछोड़ो(xudc, ep->index);
	ep_unhalt(xudc, ep->index);
	अगर (xudc_पढ़ोl(xudc, EP_STOPPED) & BIT(ep->index))
		xudc_ग_लिखोl(xudc, BIT(ep->index), EP_STOPPED);

	/*
	 * If this is the last endpoपूर्णांक disabled in a de-configure request,
	 * चयन back to address state.
	 */
	अगर ((xudc->device_state == USB_STATE_CONFIGURED) &&
	    (xudc->nr_enabled_eps == 1)) अणु
		u32 val;

		xudc->device_state = USB_STATE_ADDRESS;
		usb_gadget_set_state(&xudc->gadget, xudc->device_state);

		val = xudc_पढ़ोl(xudc, CTRL);
		val &= ~CTRL_RUN;
		xudc_ग_लिखोl(xudc, val, CTRL);
	पूर्ण

	dev_info(xudc->dev, "ep %u disabled\n", ep->index);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xudc_ep_disable(काष्ठा usb_ep *usb_ep)
अणु
	काष्ठा tegra_xudc_ep *ep;
	काष्ठा tegra_xudc *xudc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!usb_ep)
		वापस -EINVAL;

	ep = to_xudc_ep(usb_ep);
	xudc = ep->xudc;

	spin_lock_irqsave(&xudc->lock, flags);
	अगर (xudc->घातergated) अणु
		ret = -ESHUTDOWN;
		जाओ unlock;
	पूर्ण

	ret = __tegra_xudc_ep_disable(ep);
unlock:
	spin_unlock_irqrestore(&xudc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक __tegra_xudc_ep_enable(काष्ठा tegra_xudc_ep *ep,
				  स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा tegra_xudc *xudc = ep->xudc;
	अचिन्हित पूर्णांक i;
	u32 val;

	अगर (xudc->gadget.speed == USB_SPEED_SUPER &&
		!usb_endpoपूर्णांक_xfer_control(desc) && !ep->usb_ep.comp_desc)
		वापस -EINVAL;

	/* Disable the EP अगर it is not disabled */
	अगर (ep_ctx_पढ़ो_state(ep->context) != EP_STATE_DISABLED)
		__tegra_xudc_ep_disable(ep);

	ep->desc = desc;
	ep->comp_desc = ep->usb_ep.comp_desc;

	अगर (usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
		अगर (xudc->nr_isoch_eps > XUDC_MAX_ISOCH_EPS) अणु
			dev_err(xudc->dev, "too many isochronous endpoints\n");
			वापस -EBUSY;
		पूर्ण
		xudc->nr_isoch_eps++;
	पूर्ण

	स_रखो(ep->transfer_ring, 0, XUDC_TRANSFER_RING_SIZE *
	       माप(*ep->transfer_ring));
	setup_link_trb(ep, &ep->transfer_ring[XUDC_TRANSFER_RING_SIZE - 1]);

	ep->enq_ptr = 0;
	ep->deq_ptr = 0;
	ep->pcs = true;
	ep->ring_full = false;
	xudc->nr_enabled_eps++;

	tegra_xudc_ep_context_setup(ep);

	/*
	 * No need to reload and un-halt EP0.  This will be करोne स्वतःmatically
	 * once a valid SETUP packet is received.
	 */
	अगर (usb_endpoपूर्णांक_xfer_control(desc))
		जाओ out;

	/*
	 * Transition to configured state once the first non-control
	 * endpoपूर्णांक is enabled.
	 */
	अगर (xudc->device_state == USB_STATE_ADDRESS) अणु
		val = xudc_पढ़ोl(xudc, CTRL);
		val |= CTRL_RUN;
		xudc_ग_लिखोl(xudc, val, CTRL);

		xudc->device_state = USB_STATE_CONFIGURED;
		usb_gadget_set_state(&xudc->gadget, xudc->device_state);
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
		/*
		 * Pause all bulk endpoपूर्णांकs when enabling an isoch endpoपूर्णांक
		 * to ensure the isoch endpoपूर्णांक is allocated enough bandwidth.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(xudc->ep); i++) अणु
			अगर (xudc->ep[i].desc &&
			    usb_endpoपूर्णांक_xfer_bulk(xudc->ep[i].desc))
				ep_छोड़ो(xudc, i);
		पूर्ण
	पूर्ण

	ep_reload(xudc, ep->index);
	ep_unछोड़ो(xudc, ep->index);
	ep_unhalt(xudc, ep->index);

	अगर (usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(xudc->ep); i++) अणु
			अगर (xudc->ep[i].desc &&
			    usb_endpoपूर्णांक_xfer_bulk(xudc->ep[i].desc))
				ep_unछोड़ो(xudc, i);
		पूर्ण
	पूर्ण

out:
	dev_info(xudc->dev, "EP %u (type: %s, dir: %s) enabled\n", ep->index,
		 usb_ep_type_string(usb_endpoपूर्णांक_type(ep->desc)),
		 usb_endpoपूर्णांक_dir_in(ep->desc) ? "in" : "out");

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xudc_ep_enable(काष्ठा usb_ep *usb_ep,
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा tegra_xudc_ep *ep;
	काष्ठा tegra_xudc *xudc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर  (!usb_ep || !desc || (desc->bDescriptorType != USB_DT_ENDPOINT))
		वापस -EINVAL;

	ep = to_xudc_ep(usb_ep);
	xudc = ep->xudc;

	spin_lock_irqsave(&xudc->lock, flags);
	अगर (xudc->घातergated) अणु
		ret = -ESHUTDOWN;
		जाओ unlock;
	पूर्ण

	ret = __tegra_xudc_ep_enable(ep, desc);
unlock:
	spin_unlock_irqrestore(&xudc->lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा usb_request *
tegra_xudc_ep_alloc_request(काष्ठा usb_ep *usb_ep, gfp_t gfp)
अणु
	काष्ठा tegra_xudc_request *req;

	req = kzalloc(माप(*req), gfp);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->list);

	वापस &req->usb_req;
पूर्ण

अटल व्योम tegra_xudc_ep_मुक्त_request(काष्ठा usb_ep *usb_ep,
				       काष्ठा usb_request *usb_req)
अणु
	काष्ठा tegra_xudc_request *req = to_xudc_req(usb_req);

	kमुक्त(req);
पूर्ण

अटल काष्ठा usb_ep_ops tegra_xudc_ep_ops = अणु
	.enable = tegra_xudc_ep_enable,
	.disable = tegra_xudc_ep_disable,
	.alloc_request = tegra_xudc_ep_alloc_request,
	.मुक्त_request = tegra_xudc_ep_मुक्त_request,
	.queue = tegra_xudc_ep_queue,
	.dequeue = tegra_xudc_ep_dequeue,
	.set_halt = tegra_xudc_ep_set_halt,
पूर्ण;

अटल पूर्णांक tegra_xudc_ep0_enable(काष्ठा usb_ep *usb_ep,
				 स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक tegra_xudc_ep0_disable(काष्ठा usb_ep *usb_ep)
अणु
	वापस -EBUSY;
पूर्ण

अटल काष्ठा usb_ep_ops tegra_xudc_ep0_ops = अणु
	.enable = tegra_xudc_ep0_enable,
	.disable = tegra_xudc_ep0_disable,
	.alloc_request = tegra_xudc_ep_alloc_request,
	.मुक्त_request = tegra_xudc_ep_मुक्त_request,
	.queue = tegra_xudc_ep_queue,
	.dequeue = tegra_xudc_ep_dequeue,
	.set_halt = tegra_xudc_ep_set_halt,
पूर्ण;

अटल पूर्णांक tegra_xudc_gadget_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा tegra_xudc *xudc = to_xudc(gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&xudc->lock, flags);
	अगर (xudc->घातergated) अणु
		ret = -ESHUTDOWN;
		जाओ unlock;
	पूर्ण

	ret = (xudc_पढ़ोl(xudc, MFINDEX) & MFINDEX_FRAME_MASK) >>
		MFINDEX_FRAME_SHIFT;
unlock:
	spin_unlock_irqrestore(&xudc->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम tegra_xudc_resume_device_state(काष्ठा tegra_xudc *xudc)
अणु
	अचिन्हित पूर्णांक i;
	u32 val;

	ep_unछोड़ो_all(xudc);

	/* Direct link to U0. */
	val = xudc_पढ़ोl(xudc, PORTSC);
	अगर (((val & PORTSC_PLS_MASK) >> PORTSC_PLS_SHIFT) != PORTSC_PLS_U0) अणु
		val &= ~(PORTSC_CHANGE_MASK | PORTSC_PLS_MASK);
		val |= PORTSC_LWS | PORTSC_PLS(PORTSC_PLS_U0);
		xudc_ग_लिखोl(xudc, val, PORTSC);
	पूर्ण

	अगर (xudc->device_state == USB_STATE_SUSPENDED) अणु
		xudc->device_state = xudc->resume_state;
		usb_gadget_set_state(&xudc->gadget, xudc->device_state);
		xudc->resume_state = 0;
	पूर्ण

	/*
	 * Doorbells may be dropped अगर they are sent too soon (< ~200ns)
	 * after unpausing the endpoपूर्णांक.  Wait क्रम 500ns just to be safe.
	 */
	ndelay(500);
	क्रम (i = 0; i < ARRAY_SIZE(xudc->ep); i++)
		tegra_xudc_ep_ring_करोorbell(&xudc->ep[i]);
पूर्ण

अटल पूर्णांक tegra_xudc_gadget_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा tegra_xudc *xudc = to_xudc(gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 val;

	spin_lock_irqsave(&xudc->lock, flags);

	अगर (xudc->घातergated) अणु
		ret = -ESHUTDOWN;
		जाओ unlock;
	पूर्ण
	val = xudc_पढ़ोl(xudc, PORTPM);
	dev_dbg(xudc->dev, "%s: PORTPM=%#x, speed=%x\n", __func__,
			val, gadget->speed);

	अगर (((xudc->gadget.speed <= USB_SPEED_HIGH) &&
	     (val & PORTPM_RWE)) ||
	    ((xudc->gadget.speed == USB_SPEED_SUPER) &&
	     (val & PORTPM_FRWE))) अणु
		tegra_xudc_resume_device_state(xudc);

		/* Send Device Notअगरication packet. */
		अगर (xudc->gadget.speed == USB_SPEED_SUPER) अणु
			val = DEVNOTIF_LO_TYPE(DEVNOTIF_LO_TYPE_FUNCTION_WAKE)
					     | DEVNOTIF_LO_TRIG;
			xudc_ग_लिखोl(xudc, 0, DEVNOTIF_HI);
			xudc_ग_लिखोl(xudc, val, DEVNOTIF_LO);
		पूर्ण
	पूर्ण

unlock:
	dev_dbg(xudc->dev, "%s: ret value is %d", __func__, ret);
	spin_unlock_irqrestore(&xudc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_xudc_gadget_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा tegra_xudc *xudc = to_xudc(gadget);
	अचिन्हित दीर्घ flags;
	u32 val;

	pm_runसमय_get_sync(xudc->dev);

	spin_lock_irqsave(&xudc->lock, flags);

	अगर (is_on != xudc->pullup) अणु
		val = xudc_पढ़ोl(xudc, CTRL);
		अगर (is_on)
			val |= CTRL_ENABLE;
		अन्यथा
			val &= ~CTRL_ENABLE;
		xudc_ग_लिखोl(xudc, val, CTRL);
	पूर्ण

	xudc->pullup = is_on;
	dev_dbg(xudc->dev, "%s: pullup:%d", __func__, is_on);

	spin_unlock_irqrestore(&xudc->lock, flags);

	pm_runसमय_put(xudc->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xudc_gadget_start(काष्ठा usb_gadget *gadget,
				   काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा tegra_xudc *xudc = to_xudc(gadget);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	अगर (!driver)
		वापस -EINVAL;

	pm_runसमय_get_sync(xudc->dev);

	spin_lock_irqsave(&xudc->lock, flags);

	अगर (xudc->driver) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	xudc->setup_state = WAIT_FOR_SETUP;
	xudc->device_state = USB_STATE_DEFAULT;
	usb_gadget_set_state(&xudc->gadget, xudc->device_state);

	ret = __tegra_xudc_ep_enable(&xudc->ep[0], &tegra_xudc_ep0_desc);
	अगर (ret < 0)
		जाओ unlock;

	val = xudc_पढ़ोl(xudc, CTRL);
	val |= CTRL_IE | CTRL_LSE;
	xudc_ग_लिखोl(xudc, val, CTRL);

	val = xudc_पढ़ोl(xudc, PORTHALT);
	val |= PORTHALT_STCHG_INTR_EN;
	xudc_ग_लिखोl(xudc, val, PORTHALT);

	अगर (xudc->pullup) अणु
		val = xudc_पढ़ोl(xudc, CTRL);
		val |= CTRL_ENABLE;
		xudc_ग_लिखोl(xudc, val, CTRL);
	पूर्ण

	क्रम (i = 0; i < xudc->soc->num_phys; i++)
		अगर (xudc->usbphy[i])
			otg_set_peripheral(xudc->usbphy[i]->otg, gadget);

	xudc->driver = driver;
unlock:
	dev_dbg(xudc->dev, "%s: ret value is %d", __func__, ret);
	spin_unlock_irqrestore(&xudc->lock, flags);

	pm_runसमय_put(xudc->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_xudc_gadget_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा tegra_xudc *xudc = to_xudc(gadget);
	अचिन्हित दीर्घ flags;
	u32 val;
	अचिन्हित पूर्णांक i;

	pm_runसमय_get_sync(xudc->dev);

	spin_lock_irqsave(&xudc->lock, flags);

	क्रम (i = 0; i < xudc->soc->num_phys; i++)
		अगर (xudc->usbphy[i])
			otg_set_peripheral(xudc->usbphy[i]->otg, शून्य);

	val = xudc_पढ़ोl(xudc, CTRL);
	val &= ~(CTRL_IE | CTRL_ENABLE);
	xudc_ग_लिखोl(xudc, val, CTRL);

	__tegra_xudc_ep_disable(&xudc->ep[0]);

	xudc->driver = शून्य;
	dev_dbg(xudc->dev, "Gadget stopped");

	spin_unlock_irqrestore(&xudc->lock, flags);

	pm_runसमय_put(xudc->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xudc_gadget_vbus_draw(काष्ठा usb_gadget *gadget,
						अचिन्हित पूर्णांक m_a)
अणु
	पूर्णांक ret = 0;
	काष्ठा tegra_xudc *xudc = to_xudc(gadget);

	dev_dbg(xudc->dev, "%s: %u mA\n", __func__, m_a);

	अगर (xudc->curr_usbphy->chg_type == SDP_TYPE)
		ret = usb_phy_set_घातer(xudc->curr_usbphy, m_a);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_xudc_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा tegra_xudc *xudc = to_xudc(gadget);

	dev_dbg(xudc->dev, "%s: %d\n", __func__, is_on);
	xudc->selfघातered = !!is_on;

	वापस 0;
पूर्ण

अटल काष्ठा usb_gadget_ops tegra_xudc_gadget_ops = अणु
	.get_frame = tegra_xudc_gadget_get_frame,
	.wakeup = tegra_xudc_gadget_wakeup,
	.pullup = tegra_xudc_gadget_pullup,
	.udc_start = tegra_xudc_gadget_start,
	.udc_stop = tegra_xudc_gadget_stop,
	.vbus_draw = tegra_xudc_gadget_vbus_draw,
	.set_selfघातered = tegra_xudc_set_selfघातered,
पूर्ण;

अटल व्योम no_op_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
पूर्ण

अटल पूर्णांक
tegra_xudc_ep0_queue_status(काष्ठा tegra_xudc *xudc,
		व्योम (*cmpl)(काष्ठा usb_ep *, काष्ठा usb_request *))
अणु
	xudc->ep0_req->usb_req.buf = शून्य;
	xudc->ep0_req->usb_req.dma = 0;
	xudc->ep0_req->usb_req.length = 0;
	xudc->ep0_req->usb_req.complete = cmpl;
	xudc->ep0_req->usb_req.context = xudc;

	वापस __tegra_xudc_ep_queue(&xudc->ep[0], xudc->ep0_req);
पूर्ण

अटल पूर्णांक
tegra_xudc_ep0_queue_data(काष्ठा tegra_xudc *xudc, व्योम *buf, माप_प्रकार len,
		व्योम (*cmpl)(काष्ठा usb_ep *, काष्ठा usb_request *))
अणु
	xudc->ep0_req->usb_req.buf = buf;
	xudc->ep0_req->usb_req.length = len;
	xudc->ep0_req->usb_req.complete = cmpl;
	xudc->ep0_req->usb_req.context = xudc;

	वापस __tegra_xudc_ep_queue(&xudc->ep[0], xudc->ep0_req);
पूर्ण

अटल व्योम tegra_xudc_ep0_req_करोne(काष्ठा tegra_xudc *xudc)
अणु
	चयन (xudc->setup_state) अणु
	हाल DATA_STAGE_XFER:
		xudc->setup_state = STATUS_STAGE_RECV;
		tegra_xudc_ep0_queue_status(xudc, no_op_complete);
		अवरोध;
	हाल DATA_STAGE_RECV:
		xudc->setup_state = STATUS_STAGE_XFER;
		tegra_xudc_ep0_queue_status(xudc, no_op_complete);
		अवरोध;
	शेष:
		xudc->setup_state = WAIT_FOR_SETUP;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xudc_ep0_delegate_req(काष्ठा tegra_xudc *xudc,
				       काष्ठा usb_ctrlrequest *ctrl)
अणु
	पूर्णांक ret;

	spin_unlock(&xudc->lock);
	ret = xudc->driver->setup(&xudc->gadget, ctrl);
	spin_lock(&xudc->lock);

	वापस ret;
पूर्ण

अटल व्योम set_feature_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा tegra_xudc *xudc = req->context;

	अगर (xudc->test_mode_pattern) अणु
		xudc_ग_लिखोl(xudc, xudc->test_mode_pattern, PORT_TM);
		xudc->test_mode_pattern = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xudc_ep0_set_feature(काष्ठा tegra_xudc *xudc,
				      काष्ठा usb_ctrlrequest *ctrl)
अणु
	bool set = (ctrl->bRequest == USB_REQ_SET_FEATURE);
	u32 feature = le16_to_cpu(ctrl->wValue);
	u32 index = le16_to_cpu(ctrl->wIndex);
	u32 val, ep;
	पूर्णांक ret;

	अगर (le16_to_cpu(ctrl->wLength) != 0)
		वापस -EINVAL;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		चयन (feature) अणु
		हाल USB_DEVICE_REMOTE_WAKEUP:
			अगर ((xudc->gadget.speed == USB_SPEED_SUPER) ||
			    (xudc->device_state == USB_STATE_DEFAULT))
				वापस -EINVAL;

			val = xudc_पढ़ोl(xudc, PORTPM);
			अगर (set)
				val |= PORTPM_RWE;
			अन्यथा
				val &= ~PORTPM_RWE;

			xudc_ग_लिखोl(xudc, val, PORTPM);
			अवरोध;
		हाल USB_DEVICE_U1_ENABLE:
		हाल USB_DEVICE_U2_ENABLE:
			अगर ((xudc->device_state != USB_STATE_CONFIGURED) ||
			    (xudc->gadget.speed != USB_SPEED_SUPER))
				वापस -EINVAL;

			val = xudc_पढ़ोl(xudc, PORTPM);
			अगर ((feature == USB_DEVICE_U1_ENABLE) &&
			     xudc->soc->u1_enable) अणु
				अगर (set)
					val |= PORTPM_U1E;
				अन्यथा
					val &= ~PORTPM_U1E;
			पूर्ण

			अगर ((feature == USB_DEVICE_U2_ENABLE) &&
			     xudc->soc->u2_enable) अणु
				अगर (set)
					val |= PORTPM_U2E;
				अन्यथा
					val &= ~PORTPM_U2E;
			पूर्ण

			xudc_ग_लिखोl(xudc, val, PORTPM);
			अवरोध;
		हाल USB_DEVICE_TEST_MODE:
			अगर (xudc->gadget.speed != USB_SPEED_HIGH)
				वापस -EINVAL;

			अगर (!set)
				वापस -EINVAL;

			xudc->test_mode_pattern = index >> 8;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	हाल USB_RECIP_INTERFACE:
		अगर (xudc->device_state != USB_STATE_CONFIGURED)
			वापस -EINVAL;

		चयन (feature) अणु
		हाल USB_INTRF_FUNC_SUSPEND:
			अगर (set) अणु
				val = xudc_पढ़ोl(xudc, PORTPM);

				अगर (index & USB_INTRF_FUNC_SUSPEND_RW)
					val |= PORTPM_FRWE;
				अन्यथा
					val &= ~PORTPM_FRWE;

				xudc_ग_लिखोl(xudc, val, PORTPM);
			पूर्ण

			वापस tegra_xudc_ep0_delegate_req(xudc, ctrl);
		शेष:
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		ep = (index & USB_ENDPOINT_NUMBER_MASK) * 2 +
			((index & USB_सूची_IN) ? 1 : 0);

		अगर ((xudc->device_state == USB_STATE_DEFAULT) ||
		    ((xudc->device_state == USB_STATE_ADDRESS) &&
		     (index != 0)))
			वापस -EINVAL;

		ret = __tegra_xudc_ep_set_halt(&xudc->ep[ep], set);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस tegra_xudc_ep0_queue_status(xudc, set_feature_complete);
पूर्ण

अटल पूर्णांक tegra_xudc_ep0_get_status(काष्ठा tegra_xudc *xudc,
				     काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा tegra_xudc_ep_context *ep_ctx;
	u32 val, ep, index = le16_to_cpu(ctrl->wIndex);
	u16 status = 0;

	अगर (!(ctrl->bRequestType & USB_सूची_IN))
		वापस -EINVAL;

	अगर ((le16_to_cpu(ctrl->wValue) != 0) ||
	    (le16_to_cpu(ctrl->wLength) != 2))
		वापस -EINVAL;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		val = xudc_पढ़ोl(xudc, PORTPM);

		अगर (xudc->selfघातered)
			status |= BIT(USB_DEVICE_SELF_POWERED);

		अगर ((xudc->gadget.speed < USB_SPEED_SUPER) &&
		    (val & PORTPM_RWE))
			status |= BIT(USB_DEVICE_REMOTE_WAKEUP);

		अगर (xudc->gadget.speed == USB_SPEED_SUPER) अणु
			अगर (val & PORTPM_U1E)
				status |= BIT(USB_DEV_STAT_U1_ENABLED);
			अगर (val & PORTPM_U2E)
				status |= BIT(USB_DEV_STAT_U2_ENABLED);
		पूर्ण
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		अगर (xudc->gadget.speed == USB_SPEED_SUPER) अणु
			status |= USB_INTRF_STAT_FUNC_RW_CAP;
			val = xudc_पढ़ोl(xudc, PORTPM);
			अगर (val & PORTPM_FRWE)
				status |= USB_INTRF_STAT_FUNC_RW;
		पूर्ण
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		ep = (index & USB_ENDPOINT_NUMBER_MASK) * 2 +
			((index & USB_सूची_IN) ? 1 : 0);
		ep_ctx = &xudc->ep_context[ep];

		अगर ((xudc->device_state != USB_STATE_CONFIGURED) &&
		    ((xudc->device_state != USB_STATE_ADDRESS) || (ep != 0)))
			वापस -EINVAL;

		अगर (ep_ctx_पढ़ो_state(ep_ctx) == EP_STATE_DISABLED)
			वापस -EINVAL;

		अगर (xudc_पढ़ोl(xudc, EP_HALT) & BIT(ep))
			status |= BIT(USB_ENDPOINT_HALT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	xudc->status_buf = cpu_to_le16(status);
	वापस tegra_xudc_ep0_queue_data(xudc, &xudc->status_buf,
					 माप(xudc->status_buf),
					 no_op_complete);
पूर्ण

अटल व्योम set_sel_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	/* Nothing to करो with SEL values */
पूर्ण

अटल पूर्णांक tegra_xudc_ep0_set_sel(काष्ठा tegra_xudc *xudc,
				  काष्ठा usb_ctrlrequest *ctrl)
अणु
	अगर (ctrl->bRequestType != (USB_सूची_OUT | USB_RECIP_DEVICE |
				     USB_TYPE_STANDARD))
		वापस -EINVAL;

	अगर (xudc->device_state == USB_STATE_DEFAULT)
		वापस -EINVAL;

	अगर ((le16_to_cpu(ctrl->wIndex) != 0) ||
	    (le16_to_cpu(ctrl->wValue) != 0) ||
	    (le16_to_cpu(ctrl->wLength) != 6))
		वापस -EINVAL;

	वापस tegra_xudc_ep0_queue_data(xudc, &xudc->sel_timing,
					 माप(xudc->sel_timing),
					 set_sel_complete);
पूर्ण

अटल व्योम set_isoch_delay_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	/* Nothing to करो with isoch delay */
पूर्ण

अटल पूर्णांक tegra_xudc_ep0_set_isoch_delay(काष्ठा tegra_xudc *xudc,
					  काष्ठा usb_ctrlrequest *ctrl)
अणु
	u32 delay = le16_to_cpu(ctrl->wValue);

	अगर (ctrl->bRequestType != (USB_सूची_OUT | USB_RECIP_DEVICE |
				   USB_TYPE_STANDARD))
		वापस -EINVAL;

	अगर ((delay > 65535) || (le16_to_cpu(ctrl->wIndex) != 0) ||
	    (le16_to_cpu(ctrl->wLength) != 0))
		वापस -EINVAL;

	xudc->isoch_delay = delay;

	वापस tegra_xudc_ep0_queue_status(xudc, set_isoch_delay_complete);
पूर्ण

अटल व्योम set_address_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा tegra_xudc *xudc = req->context;

	अगर ((xudc->device_state == USB_STATE_DEFAULT) &&
	    (xudc->dev_addr != 0)) अणु
		xudc->device_state = USB_STATE_ADDRESS;
		usb_gadget_set_state(&xudc->gadget, xudc->device_state);
	पूर्ण अन्यथा अगर ((xudc->device_state == USB_STATE_ADDRESS) &&
		   (xudc->dev_addr == 0)) अणु
		xudc->device_state = USB_STATE_DEFAULT;
		usb_gadget_set_state(&xudc->gadget, xudc->device_state);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xudc_ep0_set_address(काष्ठा tegra_xudc *xudc,
				      काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा tegra_xudc_ep *ep0 = &xudc->ep[0];
	u32 val, addr = le16_to_cpu(ctrl->wValue);

	अगर (ctrl->bRequestType != (USB_सूची_OUT | USB_RECIP_DEVICE |
				     USB_TYPE_STANDARD))
		वापस -EINVAL;

	अगर ((addr > 127) || (le16_to_cpu(ctrl->wIndex) != 0) ||
	    (le16_to_cpu(ctrl->wLength) != 0))
		वापस -EINVAL;

	अगर (xudc->device_state == USB_STATE_CONFIGURED)
		वापस -EINVAL;

	dev_dbg(xudc->dev, "set address: %u\n", addr);

	xudc->dev_addr = addr;
	val = xudc_पढ़ोl(xudc, CTRL);
	val &= ~(CTRL_DEVADDR_MASK);
	val |= CTRL_DEVADDR(addr);
	xudc_ग_लिखोl(xudc, val, CTRL);

	ep_ctx_ग_लिखो_devaddr(ep0->context, addr);

	वापस tegra_xudc_ep0_queue_status(xudc, set_address_complete);
पूर्ण

अटल पूर्णांक tegra_xudc_ep0_standard_req(काष्ठा tegra_xudc *xudc,
				      काष्ठा usb_ctrlrequest *ctrl)
अणु
	पूर्णांक ret;

	चयन (ctrl->bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		dev_dbg(xudc->dev, "USB_REQ_GET_STATUS\n");
		ret = tegra_xudc_ep0_get_status(xudc, ctrl);
		अवरोध;
	हाल USB_REQ_SET_ADDRESS:
		dev_dbg(xudc->dev, "USB_REQ_SET_ADDRESS\n");
		ret = tegra_xudc_ep0_set_address(xudc, ctrl);
		अवरोध;
	हाल USB_REQ_SET_SEL:
		dev_dbg(xudc->dev, "USB_REQ_SET_SEL\n");
		ret = tegra_xudc_ep0_set_sel(xudc, ctrl);
		अवरोध;
	हाल USB_REQ_SET_ISOCH_DELAY:
		dev_dbg(xudc->dev, "USB_REQ_SET_ISOCH_DELAY\n");
		ret = tegra_xudc_ep0_set_isoch_delay(xudc, ctrl);
		अवरोध;
	हाल USB_REQ_CLEAR_FEATURE:
	हाल USB_REQ_SET_FEATURE:
		dev_dbg(xudc->dev, "USB_REQ_CLEAR/SET_FEATURE\n");
		ret = tegra_xudc_ep0_set_feature(xudc, ctrl);
		अवरोध;
	हाल USB_REQ_SET_CONFIGURATION:
		dev_dbg(xudc->dev, "USB_REQ_SET_CONFIGURATION\n");
		/*
		 * In theory we need to clear RUN bit beक्रमe status stage of
		 * deconfig request sent, but this seems to be causing problems.
		 * Clear RUN once all endpoपूर्णांकs are disabled instead.
		 */
		fallthrough;
	शेष:
		ret = tegra_xudc_ep0_delegate_req(xudc, ctrl);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम tegra_xudc_handle_ep0_setup_packet(काष्ठा tegra_xudc *xudc,
					       काष्ठा usb_ctrlrequest *ctrl,
					       u16 seq_num)
अणु
	पूर्णांक ret;

	xudc->setup_seq_num = seq_num;

	/* Ensure EP0 is unhalted. */
	ep_unhalt(xudc, 0);

	/*
	 * On Tegra210, setup packets with sequence numbers 0xfffe or 0xffff
	 * are invalid.  Halt EP0 until we get a valid packet.
	 */
	अगर (xudc->soc->invalid_seq_num &&
	    (seq_num == 0xfffe || seq_num == 0xffff)) अणु
		dev_warn(xudc->dev, "invalid sequence number detected\n");
		ep_halt(xudc, 0);
		वापस;
	पूर्ण

	अगर (ctrl->wLength)
		xudc->setup_state = (ctrl->bRequestType & USB_सूची_IN) ?
			DATA_STAGE_XFER :  DATA_STAGE_RECV;
	अन्यथा
		xudc->setup_state = STATUS_STAGE_XFER;

	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		ret = tegra_xudc_ep0_standard_req(xudc, ctrl);
	अन्यथा
		ret = tegra_xudc_ep0_delegate_req(xudc, ctrl);

	अगर (ret < 0) अणु
		dev_warn(xudc->dev, "setup request failed: %d\n", ret);
		xudc->setup_state = WAIT_FOR_SETUP;
		ep_halt(xudc, 0);
	पूर्ण
पूर्ण

अटल व्योम tegra_xudc_handle_ep0_event(काष्ठा tegra_xudc *xudc,
					काष्ठा tegra_xudc_trb *event)
अणु
	काष्ठा usb_ctrlrequest *ctrl = (काष्ठा usb_ctrlrequest *)event;
	u16 seq_num = trb_पढ़ो_seq_num(event);

	अगर (xudc->setup_state != WAIT_FOR_SETUP) अणु
		/*
		 * The controller is in the process of handling another
		 * setup request.  Queue subsequent requests and handle
		 * the last one once the controller reports a sequence
		 * number error.
		 */
		स_नकल(&xudc->setup_packet.ctrl_req, ctrl, माप(*ctrl));
		xudc->setup_packet.seq_num = seq_num;
		xudc->queued_setup_packet = true;
	पूर्ण अन्यथा अणु
		tegra_xudc_handle_ep0_setup_packet(xudc, ctrl, seq_num);
	पूर्ण
पूर्ण

अटल काष्ठा tegra_xudc_request *
trb_to_request(काष्ठा tegra_xudc_ep *ep, काष्ठा tegra_xudc_trb *trb)
अणु
	काष्ठा tegra_xudc_request *req;

	list_क्रम_each_entry(req, &ep->queue, list) अणु
		अगर (!req->trbs_queued)
			अवरोध;

		अगर (trb_in_request(ep, req, trb))
			वापस req;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम tegra_xudc_handle_transfer_completion(काष्ठा tegra_xudc *xudc,
						  काष्ठा tegra_xudc_ep *ep,
						  काष्ठा tegra_xudc_trb *event)
अणु
	काष्ठा tegra_xudc_request *req;
	काष्ठा tegra_xudc_trb *trb;
	bool लघु_packet;

	लघु_packet = (trb_पढ़ो_cmpl_code(event) ==
			TRB_CMPL_CODE_SHORT_PACKET);

	trb = trb_phys_to_virt(ep, trb_पढ़ो_data_ptr(event));
	req = trb_to_request(ep, trb);

	/*
	 * TDs are complete on लघु packet or when the completed TRB is the
	 * last TRB in the TD (the CHAIN bit is unset).
	 */
	अगर (req && (लघु_packet || (!trb_पढ़ो_chain(trb) &&
		(req->trbs_needed == req->trbs_queued)))) अणु
		काष्ठा tegra_xudc_trb *last = req->last_trb;
		अचिन्हित पूर्णांक residual;

		residual = trb_पढ़ो_transfer_len(event);
		req->usb_req.actual = req->usb_req.length - residual;

		dev_dbg(xudc->dev, "bytes transferred %u / %u\n",
			req->usb_req.actual, req->usb_req.length);

		tegra_xudc_req_करोne(ep, req, 0);

		अगर (ep->desc && usb_endpoपूर्णांक_xfer_control(ep->desc))
			tegra_xudc_ep0_req_करोne(xudc);

		/*
		 * Advance the dequeue poपूर्णांकer past the end of the current TD
		 * on लघु packet completion.
		 */
		अगर (लघु_packet) अणु
			ep->deq_ptr = (last - ep->transfer_ring) + 1;
			अगर (ep->deq_ptr == XUDC_TRANSFER_RING_SIZE - 1)
				ep->deq_ptr = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!req) अणु
		dev_warn(xudc->dev, "transfer event on dequeued request\n");
	पूर्ण

	अगर (ep->desc)
		tegra_xudc_ep_kick_queue(ep);
पूर्ण

अटल व्योम tegra_xudc_handle_transfer_event(काष्ठा tegra_xudc *xudc,
					     काष्ठा tegra_xudc_trb *event)
अणु
	अचिन्हित पूर्णांक ep_index = trb_पढ़ो_endpoपूर्णांक_id(event);
	काष्ठा tegra_xudc_ep *ep = &xudc->ep[ep_index];
	काष्ठा tegra_xudc_trb *trb;
	u16 comp_code;

	अगर (ep_ctx_पढ़ो_state(ep->context) == EP_STATE_DISABLED) अणु
		dev_warn(xudc->dev, "transfer event on disabled EP %u\n",
			 ep_index);
		वापस;
	पूर्ण

	/* Update transfer ring dequeue poपूर्णांकer. */
	trb = trb_phys_to_virt(ep, trb_पढ़ो_data_ptr(event));
	comp_code = trb_पढ़ो_cmpl_code(event);
	अगर (comp_code != TRB_CMPL_CODE_BABBLE_DETECTED_ERR) अणु
		ep->deq_ptr = (trb - ep->transfer_ring) + 1;

		अगर (ep->deq_ptr == XUDC_TRANSFER_RING_SIZE - 1)
			ep->deq_ptr = 0;
		ep->ring_full = false;
	पूर्ण

	चयन (comp_code) अणु
	हाल TRB_CMPL_CODE_SUCCESS:
	हाल TRB_CMPL_CODE_SHORT_PACKET:
		tegra_xudc_handle_transfer_completion(xudc, ep, event);
		अवरोध;
	हाल TRB_CMPL_CODE_HOST_REJECTED:
		dev_info(xudc->dev, "stream rejected on EP %u\n", ep_index);

		ep->stream_rejected = true;
		अवरोध;
	हाल TRB_CMPL_CODE_PRIME_PIPE_RECEIVED:
		dev_info(xudc->dev, "prime pipe received on EP %u\n", ep_index);

		अगर (ep->stream_rejected) अणु
			ep->stream_rejected = false;
			/*
			 * An EP is stopped when a stream is rejected.  Wait
			 * क्रम the EP to report that it is stopped and then
			 * un-stop it.
			 */
			ep_रुको_क्रम_stopped(xudc, ep_index);
		पूर्ण
		tegra_xudc_ep_ring_करोorbell(ep);
		अवरोध;
	हाल TRB_CMPL_CODE_BABBLE_DETECTED_ERR:
		/*
		 * Wait क्रम the EP to be stopped so the controller stops
		 * processing करोorbells.
		 */
		ep_रुको_क्रम_stopped(xudc, ep_index);
		ep->enq_ptr = ep->deq_ptr;
		tegra_xudc_ep_nuke(ep, -EIO);
		fallthrough;
	हाल TRB_CMPL_CODE_STREAM_NUMP_ERROR:
	हाल TRB_CMPL_CODE_CTRL_सूची_ERR:
	हाल TRB_CMPL_CODE_INVALID_STREAM_TYPE_ERR:
	हाल TRB_CMPL_CODE_RING_UNDERRUN:
	हाल TRB_CMPL_CODE_RING_OVERRUN:
	हाल TRB_CMPL_CODE_ISOCH_BUFFER_OVERRUN:
	हाल TRB_CMPL_CODE_USB_TRANS_ERR:
	हाल TRB_CMPL_CODE_TRB_ERR:
		dev_err(xudc->dev, "completion error %#x on EP %u\n",
			comp_code, ep_index);

		ep_halt(xudc, ep_index);
		अवरोध;
	हाल TRB_CMPL_CODE_CTRL_SEQNUM_ERR:
		dev_info(xudc->dev, "sequence number error\n");

		/*
		 * Kill any queued control request and skip to the last
		 * setup packet we received.
		 */
		tegra_xudc_ep_nuke(ep, -EINVAL);
		xudc->setup_state = WAIT_FOR_SETUP;
		अगर (!xudc->queued_setup_packet)
			अवरोध;

		tegra_xudc_handle_ep0_setup_packet(xudc,
						   &xudc->setup_packet.ctrl_req,
						   xudc->setup_packet.seq_num);
		xudc->queued_setup_packet = false;
		अवरोध;
	हाल TRB_CMPL_CODE_STOPPED:
		dev_dbg(xudc->dev, "stop completion code on EP %u\n",
			ep_index);

		/* Disconnected. */
		tegra_xudc_ep_nuke(ep, -ECONNREFUSED);
		अवरोध;
	शेष:
		dev_dbg(xudc->dev, "completion event %#x on EP %u\n",
			comp_code, ep_index);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tegra_xudc_reset(काष्ठा tegra_xudc *xudc)
अणु
	काष्ठा tegra_xudc_ep *ep0 = &xudc->ep[0];
	dma_addr_t deq_ptr;
	अचिन्हित पूर्णांक i;

	xudc->setup_state = WAIT_FOR_SETUP;
	xudc->device_state = USB_STATE_DEFAULT;
	usb_gadget_set_state(&xudc->gadget, xudc->device_state);

	ep_unछोड़ो_all(xudc);

	क्रम (i = 0; i < ARRAY_SIZE(xudc->ep); i++)
		tegra_xudc_ep_nuke(&xudc->ep[i], -ESHUTDOWN);

	/*
	 * Reset sequence number and dequeue poपूर्णांकer to flush the transfer
	 * ring.
	 */
	ep0->deq_ptr = ep0->enq_ptr;
	ep0->ring_full = false;

	xudc->setup_seq_num = 0;
	xudc->queued_setup_packet = false;

	ep_ctx_ग_लिखो_seq_num(ep0->context, xudc->setup_seq_num);

	deq_ptr = trb_virt_to_phys(ep0, &ep0->transfer_ring[ep0->deq_ptr]);

	अगर (!dma_mapping_error(xudc->dev, deq_ptr)) अणु
		ep_ctx_ग_लिखो_deq_ptr(ep0->context, deq_ptr);
		ep_ctx_ग_लिखो_dcs(ep0->context, ep0->pcs);
	पूर्ण

	ep_unhalt_all(xudc);
	ep_reload(xudc, 0);
	ep_unछोड़ो(xudc, 0);
पूर्ण

अटल व्योम tegra_xudc_port_connect(काष्ठा tegra_xudc *xudc)
अणु
	काष्ठा tegra_xudc_ep *ep0 = &xudc->ep[0];
	u16 maxpacket;
	u32 val;

	val = (xudc_पढ़ोl(xudc, PORTSC) & PORTSC_PS_MASK) >> PORTSC_PS_SHIFT;
	चयन (val) अणु
	हाल PORTSC_PS_LS:
		xudc->gadget.speed = USB_SPEED_LOW;
		अवरोध;
	हाल PORTSC_PS_FS:
		xudc->gadget.speed = USB_SPEED_FULL;
		अवरोध;
	हाल PORTSC_PS_HS:
		xudc->gadget.speed = USB_SPEED_HIGH;
		अवरोध;
	हाल PORTSC_PS_SS:
		xudc->gadget.speed = USB_SPEED_SUPER;
		अवरोध;
	शेष:
		xudc->gadget.speed = USB_SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	xudc->device_state = USB_STATE_DEFAULT;
	usb_gadget_set_state(&xudc->gadget, xudc->device_state);

	xudc->setup_state = WAIT_FOR_SETUP;

	अगर (xudc->gadget.speed == USB_SPEED_SUPER)
		maxpacket = 512;
	अन्यथा
		maxpacket = 64;

	ep_ctx_ग_लिखो_max_packet_size(ep0->context, maxpacket);
	tegra_xudc_ep0_desc.wMaxPacketSize = cpu_to_le16(maxpacket);
	usb_ep_set_maxpacket_limit(&ep0->usb_ep, maxpacket);

	अगर (!xudc->soc->u1_enable) अणु
		val = xudc_पढ़ोl(xudc, PORTPM);
		val &= ~(PORTPM_U1TIMEOUT_MASK);
		xudc_ग_लिखोl(xudc, val, PORTPM);
	पूर्ण

	अगर (!xudc->soc->u2_enable) अणु
		val = xudc_पढ़ोl(xudc, PORTPM);
		val &= ~(PORTPM_U2TIMEOUT_MASK);
		xudc_ग_लिखोl(xudc, val, PORTPM);
	पूर्ण

	अगर (xudc->gadget.speed <= USB_SPEED_HIGH) अणु
		val = xudc_पढ़ोl(xudc, PORTPM);
		val &= ~(PORTPM_L1S_MASK);
		अगर (xudc->soc->lpm_enable)
			val |= PORTPM_L1S(PORTPM_L1S_ACCEPT);
		अन्यथा
			val |= PORTPM_L1S(PORTPM_L1S_NYET);
		xudc_ग_लिखोl(xudc, val, PORTPM);
	पूर्ण

	val = xudc_पढ़ोl(xudc, ST);
	अगर (val & ST_RC)
		xudc_ग_लिखोl(xudc, ST_RC, ST);
पूर्ण

अटल व्योम tegra_xudc_port_disconnect(काष्ठा tegra_xudc *xudc)
अणु
	tegra_xudc_reset(xudc);

	अगर (xudc->driver && xudc->driver->disconnect) अणु
		spin_unlock(&xudc->lock);
		xudc->driver->disconnect(&xudc->gadget);
		spin_lock(&xudc->lock);
	पूर्ण

	xudc->device_state = USB_STATE_NOTATTACHED;
	usb_gadget_set_state(&xudc->gadget, xudc->device_state);

	complete(&xudc->disconnect_complete);
पूर्ण

अटल व्योम tegra_xudc_port_reset(काष्ठा tegra_xudc *xudc)
अणु
	tegra_xudc_reset(xudc);

	अगर (xudc->driver) अणु
		spin_unlock(&xudc->lock);
		usb_gadget_udc_reset(&xudc->gadget, xudc->driver);
		spin_lock(&xudc->lock);
	पूर्ण

	tegra_xudc_port_connect(xudc);
पूर्ण

अटल व्योम tegra_xudc_port_suspend(काष्ठा tegra_xudc *xudc)
अणु
	dev_dbg(xudc->dev, "port suspend\n");

	xudc->resume_state = xudc->device_state;
	xudc->device_state = USB_STATE_SUSPENDED;
	usb_gadget_set_state(&xudc->gadget, xudc->device_state);

	अगर (xudc->driver->suspend) अणु
		spin_unlock(&xudc->lock);
		xudc->driver->suspend(&xudc->gadget);
		spin_lock(&xudc->lock);
	पूर्ण
पूर्ण

अटल व्योम tegra_xudc_port_resume(काष्ठा tegra_xudc *xudc)
अणु
	dev_dbg(xudc->dev, "port resume\n");

	tegra_xudc_resume_device_state(xudc);

	अगर (xudc->driver->resume) अणु
		spin_unlock(&xudc->lock);
		xudc->driver->resume(&xudc->gadget);
		spin_lock(&xudc->lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम clear_port_change(काष्ठा tegra_xudc *xudc, u32 flag)
अणु
	u32 val;

	val = xudc_पढ़ोl(xudc, PORTSC);
	val &= ~PORTSC_CHANGE_MASK;
	val |= flag;
	xudc_ग_लिखोl(xudc, val, PORTSC);
पूर्ण

अटल व्योम __tegra_xudc_handle_port_status(काष्ठा tegra_xudc *xudc)
अणु
	u32 portsc, porthalt;

	porthalt = xudc_पढ़ोl(xudc, PORTHALT);
	अगर ((porthalt & PORTHALT_STCHG_REQ) &&
	    (porthalt & PORTHALT_HALT_LTSSM)) अणु
		dev_dbg(xudc->dev, "STCHG_REQ, PORTHALT = %#x\n", porthalt);
		porthalt &= ~PORTHALT_HALT_LTSSM;
		xudc_ग_लिखोl(xudc, porthalt, PORTHALT);
	पूर्ण

	portsc = xudc_पढ़ोl(xudc, PORTSC);
	अगर ((portsc & PORTSC_PRC) && (portsc & PORTSC_PR)) अणु
		dev_dbg(xudc->dev, "PRC, PR, PORTSC = %#x\n", portsc);
		clear_port_change(xudc, PORTSC_PRC | PORTSC_PED);
#घोषणा TOGGLE_VBUS_WAIT_MS 100
		अगर (xudc->soc->port_reset_quirk) अणु
			schedule_delayed_work(&xudc->port_reset_war_work,
				msecs_to_jअगरfies(TOGGLE_VBUS_WAIT_MS));
			xudc->रुको_क्रम_sec_prc = 1;
		पूर्ण
	पूर्ण

	अगर ((portsc & PORTSC_PRC) && !(portsc & PORTSC_PR)) अणु
		dev_dbg(xudc->dev, "PRC, Not PR, PORTSC = %#x\n", portsc);
		clear_port_change(xudc, PORTSC_PRC | PORTSC_PED);
		tegra_xudc_port_reset(xudc);
		cancel_delayed_work(&xudc->port_reset_war_work);
		xudc->रुको_क्रम_sec_prc = 0;
	पूर्ण

	portsc = xudc_पढ़ोl(xudc, PORTSC);
	अगर (portsc & PORTSC_WRC) अणु
		dev_dbg(xudc->dev, "WRC, PORTSC = %#x\n", portsc);
		clear_port_change(xudc, PORTSC_WRC | PORTSC_PED);
		अगर (!(xudc_पढ़ोl(xudc, PORTSC) & PORTSC_WPR))
			tegra_xudc_port_reset(xudc);
	पूर्ण

	portsc = xudc_पढ़ोl(xudc, PORTSC);
	अगर (portsc & PORTSC_CSC) अणु
		dev_dbg(xudc->dev, "CSC, PORTSC = %#x\n", portsc);
		clear_port_change(xudc, PORTSC_CSC);

		अगर (portsc & PORTSC_CCS)
			tegra_xudc_port_connect(xudc);
		अन्यथा
			tegra_xudc_port_disconnect(xudc);

		अगर (xudc->रुको_csc) अणु
			cancel_delayed_work(&xudc->plc_reset_work);
			xudc->रुको_csc = false;
		पूर्ण
	पूर्ण

	portsc = xudc_पढ़ोl(xudc, PORTSC);
	अगर (portsc & PORTSC_PLC) अणु
		u32 pls = (portsc & PORTSC_PLS_MASK) >> PORTSC_PLS_SHIFT;

		dev_dbg(xudc->dev, "PLC, PORTSC = %#x\n", portsc);
		clear_port_change(xudc, PORTSC_PLC);
		चयन (pls) अणु
		हाल PORTSC_PLS_U3:
			tegra_xudc_port_suspend(xudc);
			अवरोध;
		हाल PORTSC_PLS_U0:
			अगर (xudc->gadget.speed < USB_SPEED_SUPER)
				tegra_xudc_port_resume(xudc);
			अवरोध;
		हाल PORTSC_PLS_RESUME:
			अगर (xudc->gadget.speed == USB_SPEED_SUPER)
				tegra_xudc_port_resume(xudc);
			अवरोध;
		हाल PORTSC_PLS_INACTIVE:
			schedule_delayed_work(&xudc->plc_reset_work,
					msecs_to_jअगरfies(TOGGLE_VBUS_WAIT_MS));
			xudc->रुको_csc = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (portsc & PORTSC_CEC) अणु
		dev_warn(xudc->dev, "CEC, PORTSC = %#x\n", portsc);
		clear_port_change(xudc, PORTSC_CEC);
	पूर्ण

	dev_dbg(xudc->dev, "PORTSC = %#x\n", xudc_पढ़ोl(xudc, PORTSC));
पूर्ण

अटल व्योम tegra_xudc_handle_port_status(काष्ठा tegra_xudc *xudc)
अणु
	जबतक ((xudc_पढ़ोl(xudc, PORTSC) & PORTSC_CHANGE_MASK) ||
	       (xudc_पढ़ोl(xudc, PORTHALT) & PORTHALT_STCHG_REQ))
		__tegra_xudc_handle_port_status(xudc);
पूर्ण

अटल व्योम tegra_xudc_handle_event(काष्ठा tegra_xudc *xudc,
				    काष्ठा tegra_xudc_trb *event)
अणु
	u32 type = trb_पढ़ो_type(event);

	dump_trb(xudc, "EVENT", event);

	चयन (type) अणु
	हाल TRB_TYPE_PORT_STATUS_CHANGE_EVENT:
		tegra_xudc_handle_port_status(xudc);
		अवरोध;
	हाल TRB_TYPE_TRANSFER_EVENT:
		tegra_xudc_handle_transfer_event(xudc, event);
		अवरोध;
	हाल TRB_TYPE_SETUP_PACKET_EVENT:
		tegra_xudc_handle_ep0_event(xudc, event);
		अवरोध;
	शेष:
		dev_info(xudc->dev, "Unrecognized TRB type = %#x\n", type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tegra_xudc_process_event_ring(काष्ठा tegra_xudc *xudc)
अणु
	काष्ठा tegra_xudc_trb *event;
	dma_addr_t erdp;

	जबतक (true) अणु
		event = xudc->event_ring[xudc->event_ring_index] +
			xudc->event_ring_deq_ptr;

		अगर (trb_पढ़ो_cycle(event) != xudc->ccs)
			अवरोध;

		tegra_xudc_handle_event(xudc, event);

		xudc->event_ring_deq_ptr++;
		अगर (xudc->event_ring_deq_ptr == XUDC_EVENT_RING_SIZE) अणु
			xudc->event_ring_deq_ptr = 0;
			xudc->event_ring_index++;
		पूर्ण

		अगर (xudc->event_ring_index == XUDC_NR_EVENT_RINGS) अणु
			xudc->event_ring_index = 0;
			xudc->ccs = !xudc->ccs;
		पूर्ण
	पूर्ण

	erdp = xudc->event_ring_phys[xudc->event_ring_index] +
		xudc->event_ring_deq_ptr * माप(*event);

	xudc_ग_लिखोl(xudc, upper_32_bits(erdp), ERDPHI);
	xudc_ग_लिखोl(xudc, lower_32_bits(erdp) | ERDPLO_EHB, ERDPLO);
पूर्ण

अटल irqवापस_t tegra_xudc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_xudc *xudc = data;
	अचिन्हित दीर्घ flags;
	u32 val;

	val = xudc_पढ़ोl(xudc, ST);
	अगर (!(val & ST_IP))
		वापस IRQ_NONE;
	xudc_ग_लिखोl(xudc, ST_IP, ST);

	spin_lock_irqsave(&xudc->lock, flags);
	tegra_xudc_process_event_ring(xudc);
	spin_unlock_irqrestore(&xudc->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tegra_xudc_alloc_ep(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xudc_ep *ep = &xudc->ep[index];

	ep->xudc = xudc;
	ep->index = index;
	ep->context = &xudc->ep_context[index];
	INIT_LIST_HEAD(&ep->queue);

	/*
	 * EP1 would be the input endpoपूर्णांक corresponding to EP0, but since
	 * EP0 is bi-directional, EP1 is unused.
	 */
	अगर (index == 1)
		वापस 0;

	ep->transfer_ring = dma_pool_alloc(xudc->transfer_ring_pool,
					   GFP_KERNEL,
					   &ep->transfer_ring_phys);
	अगर (!ep->transfer_ring)
		वापस -ENOMEM;

	अगर (index) अणु
		snम_लिखो(ep->name, माप(ep->name), "ep%u%s", index / 2,
			 (index % 2 == 0) ? "out" : "in");
		ep->usb_ep.name = ep->name;
		usb_ep_set_maxpacket_limit(&ep->usb_ep, 1024);
		ep->usb_ep.max_streams = 16;
		ep->usb_ep.ops = &tegra_xudc_ep_ops;
		ep->usb_ep.caps.type_bulk = true;
		ep->usb_ep.caps.type_पूर्णांक = true;
		अगर (index & 1)
			ep->usb_ep.caps.dir_in = true;
		अन्यथा
			ep->usb_ep.caps.dir_out = true;
		list_add_tail(&ep->usb_ep.ep_list, &xudc->gadget.ep_list);
	पूर्ण अन्यथा अणु
		strscpy(ep->name, "ep0", 3);
		ep->usb_ep.name = ep->name;
		usb_ep_set_maxpacket_limit(&ep->usb_ep, 512);
		ep->usb_ep.ops = &tegra_xudc_ep0_ops;
		ep->usb_ep.caps.type_control = true;
		ep->usb_ep.caps.dir_in = true;
		ep->usb_ep.caps.dir_out = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_xudc_मुक्त_ep(काष्ठा tegra_xudc *xudc, अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xudc_ep *ep = &xudc->ep[index];

	/*
	 * EP1 would be the input endpoपूर्णांक corresponding to EP0, but since
	 * EP0 is bi-directional, EP1 is unused.
	 */
	अगर (index == 1)
		वापस;

	dma_pool_मुक्त(xudc->transfer_ring_pool, ep->transfer_ring,
		      ep->transfer_ring_phys);
पूर्ण

अटल पूर्णांक tegra_xudc_alloc_eps(काष्ठा tegra_xudc *xudc)
अणु
	काष्ठा usb_request *req;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	xudc->ep_context =
		dma_alloc_coherent(xudc->dev, XUDC_NR_EPS *
				    माप(*xudc->ep_context),
				    &xudc->ep_context_phys, GFP_KERNEL);
	अगर (!xudc->ep_context)
		वापस -ENOMEM;

	xudc->transfer_ring_pool =
		dmam_pool_create(dev_name(xudc->dev), xudc->dev,
				 XUDC_TRANSFER_RING_SIZE *
				 माप(काष्ठा tegra_xudc_trb),
				 माप(काष्ठा tegra_xudc_trb), 0);
	अगर (!xudc->transfer_ring_pool) अणु
		err = -ENOMEM;
		जाओ मुक्त_ep_context;
	पूर्ण

	INIT_LIST_HEAD(&xudc->gadget.ep_list);
	क्रम (i = 0; i < ARRAY_SIZE(xudc->ep); i++) अणु
		err = tegra_xudc_alloc_ep(xudc, i);
		अगर (err < 0)
			जाओ मुक्त_eps;
	पूर्ण

	req = tegra_xudc_ep_alloc_request(&xudc->ep[0].usb_ep, GFP_KERNEL);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ मुक्त_eps;
	पूर्ण
	xudc->ep0_req = to_xudc_req(req);

	वापस 0;

मुक्त_eps:
	क्रम (; i > 0; i--)
		tegra_xudc_मुक्त_ep(xudc, i - 1);
मुक्त_ep_context:
	dma_मुक्त_coherent(xudc->dev, XUDC_NR_EPS * माप(*xudc->ep_context),
			  xudc->ep_context, xudc->ep_context_phys);
	वापस err;
पूर्ण

अटल व्योम tegra_xudc_init_eps(काष्ठा tegra_xudc *xudc)
अणु
	xudc_ग_लिखोl(xudc, lower_32_bits(xudc->ep_context_phys), ECPLO);
	xudc_ग_लिखोl(xudc, upper_32_bits(xudc->ep_context_phys), ECPHI);
पूर्ण

अटल व्योम tegra_xudc_मुक्त_eps(काष्ठा tegra_xudc *xudc)
अणु
	अचिन्हित पूर्णांक i;

	tegra_xudc_ep_मुक्त_request(&xudc->ep[0].usb_ep,
				   &xudc->ep0_req->usb_req);

	क्रम (i = 0; i < ARRAY_SIZE(xudc->ep); i++)
		tegra_xudc_मुक्त_ep(xudc, i);

	dma_मुक्त_coherent(xudc->dev, XUDC_NR_EPS * माप(*xudc->ep_context),
			  xudc->ep_context, xudc->ep_context_phys);
पूर्ण

अटल पूर्णांक tegra_xudc_alloc_event_ring(काष्ठा tegra_xudc *xudc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xudc->event_ring); i++) अणु
		xudc->event_ring[i] =
			dma_alloc_coherent(xudc->dev, XUDC_EVENT_RING_SIZE *
					   माप(*xudc->event_ring[i]),
					   &xudc->event_ring_phys[i],
					   GFP_KERNEL);
		अगर (!xudc->event_ring[i])
			जाओ मुक्त_dma;
	पूर्ण

	वापस 0;

मुक्त_dma:
	क्रम (; i > 0; i--) अणु
		dma_मुक्त_coherent(xudc->dev, XUDC_EVENT_RING_SIZE *
				  माप(*xudc->event_ring[i - 1]),
				  xudc->event_ring[i - 1],
				  xudc->event_ring_phys[i - 1]);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम tegra_xudc_init_event_ring(काष्ठा tegra_xudc *xudc)
अणु
	अचिन्हित पूर्णांक i;
	u32 val;

	val = xudc_पढ़ोl(xudc, SPARAM);
	val &= ~(SPARAM_ERSTMAX_MASK);
	val |= SPARAM_ERSTMAX(XUDC_NR_EVENT_RINGS);
	xudc_ग_लिखोl(xudc, val, SPARAM);

	क्रम (i = 0; i < ARRAY_SIZE(xudc->event_ring); i++) अणु
		स_रखो(xudc->event_ring[i], 0, XUDC_EVENT_RING_SIZE *
		       माप(*xudc->event_ring[i]));

		val = xudc_पढ़ोl(xudc, ERSTSZ);
		val &= ~(ERSTSZ_ERSTXSZ_MASK << ERSTSZ_ERSTXSZ_SHIFT(i));
		val |= XUDC_EVENT_RING_SIZE << ERSTSZ_ERSTXSZ_SHIFT(i);
		xudc_ग_लिखोl(xudc, val, ERSTSZ);

		xudc_ग_लिखोl(xudc, lower_32_bits(xudc->event_ring_phys[i]),
			    ERSTXBALO(i));
		xudc_ग_लिखोl(xudc, upper_32_bits(xudc->event_ring_phys[i]),
			    ERSTXBAHI(i));
	पूर्ण

	val = lower_32_bits(xudc->event_ring_phys[0]);
	xudc_ग_लिखोl(xudc, val, ERDPLO);
	val |= EREPLO_ECS;
	xudc_ग_लिखोl(xudc, val, EREPLO);

	val = upper_32_bits(xudc->event_ring_phys[0]);
	xudc_ग_लिखोl(xudc, val, ERDPHI);
	xudc_ग_लिखोl(xudc, val, EREPHI);

	xudc->ccs = true;
	xudc->event_ring_index = 0;
	xudc->event_ring_deq_ptr = 0;
पूर्ण

अटल व्योम tegra_xudc_मुक्त_event_ring(काष्ठा tegra_xudc *xudc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xudc->event_ring); i++) अणु
		dma_मुक्त_coherent(xudc->dev, XUDC_EVENT_RING_SIZE *
				  माप(*xudc->event_ring[i]),
				  xudc->event_ring[i],
				  xudc->event_ring_phys[i]);
	पूर्ण
पूर्ण

अटल व्योम tegra_xudc_fpci_ipfs_init(काष्ठा tegra_xudc *xudc)
अणु
	u32 val;

	अगर (xudc->soc->has_ipfs) अणु
		val = ipfs_पढ़ोl(xudc, XUSB_DEV_CONFIGURATION_0);
		val |= XUSB_DEV_CONFIGURATION_0_EN_FPCI;
		ipfs_ग_लिखोl(xudc, val, XUSB_DEV_CONFIGURATION_0);
		usleep_range(10, 15);
	पूर्ण

	/* Enable bus master */
	val = XUSB_DEV_CFG_1_IO_SPACE_EN | XUSB_DEV_CFG_1_MEMORY_SPACE_EN |
		XUSB_DEV_CFG_1_BUS_MASTER_EN;
	fpci_ग_लिखोl(xudc, val, XUSB_DEV_CFG_1);

	/* Program BAR0 space */
	val = fpci_पढ़ोl(xudc, XUSB_DEV_CFG_4);
	val &= ~(XUSB_DEV_CFG_4_BASE_ADDR_MASK);
	val |= xudc->phys_base & (XUSB_DEV_CFG_4_BASE_ADDR_MASK);

	fpci_ग_लिखोl(xudc, val, XUSB_DEV_CFG_4);
	fpci_ग_लिखोl(xudc, upper_32_bits(xudc->phys_base), XUSB_DEV_CFG_5);

	usleep_range(100, 200);

	अगर (xudc->soc->has_ipfs) अणु
		/* Enable पूर्णांकerrupt निश्चितion */
		val = ipfs_पढ़ोl(xudc, XUSB_DEV_INTR_MASK_0);
		val |= XUSB_DEV_INTR_MASK_0_IP_INT_MASK;
		ipfs_ग_लिखोl(xudc, val, XUSB_DEV_INTR_MASK_0);
	पूर्ण
पूर्ण

अटल व्योम tegra_xudc_device_params_init(काष्ठा tegra_xudc *xudc)
अणु
	u32 val, imod;

	अगर (xudc->soc->has_ipfs) अणु
		val = xudc_पढ़ोl(xudc, BLCG);
		val |= BLCG_ALL;
		val &= ~(BLCG_DFPCI | BLCG_UFPCI | BLCG_FE |
				BLCG_COREPLL_PWRDN);
		val |= BLCG_IOPLL_0_PWRDN;
		val |= BLCG_IOPLL_1_PWRDN;
		val |= BLCG_IOPLL_2_PWRDN;

		xudc_ग_लिखोl(xudc, val, BLCG);
	पूर्ण

	अगर (xudc->soc->port_speed_quirk)
		tegra_xudc_limit_port_speed(xudc);

	/* Set a reasonable U3 निकास समयr value. */
	val = xudc_पढ़ोl(xudc, SSPX_CORE_PADCTL4);
	val &= ~(SSPX_CORE_PADCTL4_RXDAT_VLD_TIMEOUT_U3_MASK);
	val |= SSPX_CORE_PADCTL4_RXDAT_VLD_TIMEOUT_U3(0x5dc0);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_PADCTL4);

	/* Default ping LFPS tBurst is too large. */
	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT0);
	val &= ~(SSPX_CORE_CNT0_PING_TBURST_MASK);
	val |= SSPX_CORE_CNT0_PING_TBURST(0xa);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT0);

	/* Default tPortConfiguration समयout is too small. */
	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT30);
	val &= ~(SSPX_CORE_CNT30_LMPITP_TIMER_MASK);
	val |= SSPX_CORE_CNT30_LMPITP_TIMER(0x978);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT30);

	अगर (xudc->soc->lpm_enable) अणु
		/* Set L1 resume duration to 95 us. */
		val = xudc_पढ़ोl(xudc, HSFSPI_COUNT13);
		val &= ~(HSFSPI_COUNT13_U2_RESUME_K_DURATION_MASK);
		val |= HSFSPI_COUNT13_U2_RESUME_K_DURATION(0x2c88);
		xudc_ग_लिखोl(xudc, val, HSFSPI_COUNT13);
	पूर्ण

	/*
	 * Compliacne suite appears to be violating polling LFPS tBurst max
	 * of 1.4us.  Send 1.45us instead.
	 */
	val = xudc_पढ़ोl(xudc, SSPX_CORE_CNT32);
	val &= ~(SSPX_CORE_CNT32_POLL_TBURST_MAX_MASK);
	val |= SSPX_CORE_CNT32_POLL_TBURST_MAX(0xb0);
	xudc_ग_लिखोl(xudc, val, SSPX_CORE_CNT32);

	/* Direct HS/FS port instance to RxDetect. */
	val = xudc_पढ़ोl(xudc, CFG_DEV_FE);
	val &= ~(CFG_DEV_FE_PORTREGSEL_MASK);
	val |= CFG_DEV_FE_PORTREGSEL(CFG_DEV_FE_PORTREGSEL_HSFS_PI);
	xudc_ग_लिखोl(xudc, val, CFG_DEV_FE);

	val = xudc_पढ़ोl(xudc, PORTSC);
	val &= ~(PORTSC_CHANGE_MASK | PORTSC_PLS_MASK);
	val |= PORTSC_LWS | PORTSC_PLS(PORTSC_PLS_RXDETECT);
	xudc_ग_लिखोl(xudc, val, PORTSC);

	/* Direct SS port instance to RxDetect. */
	val = xudc_पढ़ोl(xudc, CFG_DEV_FE);
	val &= ~(CFG_DEV_FE_PORTREGSEL_MASK);
	val |= CFG_DEV_FE_PORTREGSEL_SS_PI & CFG_DEV_FE_PORTREGSEL_MASK;
	xudc_ग_लिखोl(xudc, val, CFG_DEV_FE);

	val = xudc_पढ़ोl(xudc, PORTSC);
	val &= ~(PORTSC_CHANGE_MASK | PORTSC_PLS_MASK);
	val |= PORTSC_LWS | PORTSC_PLS(PORTSC_PLS_RXDETECT);
	xudc_ग_लिखोl(xudc, val, PORTSC);

	/* Restore port instance. */
	val = xudc_पढ़ोl(xudc, CFG_DEV_FE);
	val &= ~(CFG_DEV_FE_PORTREGSEL_MASK);
	xudc_ग_लिखोl(xudc, val, CFG_DEV_FE);

	/*
	 * Enable INFINITE_SS_RETRY to prevent device from entering
	 * Disabled.Error when attached to buggy SuperSpeed hubs.
	 */
	val = xudc_पढ़ोl(xudc, CFG_DEV_FE);
	val |= CFG_DEV_FE_INFINITE_SS_RETRY;
	xudc_ग_लिखोl(xudc, val, CFG_DEV_FE);

	/* Set पूर्णांकerrupt moderation. */
	imod = XUDC_INTERRUPT_MODERATION_US * 4;
	val = xudc_पढ़ोl(xudc, RT_IMOD);
	val &= ~((RT_IMOD_IMODI_MASK) | (RT_IMOD_IMODC_MASK));
	val |= (RT_IMOD_IMODI(imod) | RT_IMOD_IMODC(imod));
	xudc_ग_लिखोl(xudc, val, RT_IMOD);

	/* increase SSPI transaction समयout from 32us to 512us */
	val = xudc_पढ़ोl(xudc, CFG_DEV_SSPI_XFER);
	val &= ~(CFG_DEV_SSPI_XFER_ACKTIMEOUT_MASK);
	val |= CFG_DEV_SSPI_XFER_ACKTIMEOUT(0xf000);
	xudc_ग_लिखोl(xudc, val, CFG_DEV_SSPI_XFER);
पूर्ण

अटल पूर्णांक tegra_xudc_phy_get(काष्ठा tegra_xudc *xudc)
अणु
	पूर्णांक err = 0, usb3;
	अचिन्हित पूर्णांक i;

	xudc->uपंचांगi_phy = devm_kसुस्मृति(xudc->dev, xudc->soc->num_phys,
					   माप(*xudc->uपंचांगi_phy), GFP_KERNEL);
	अगर (!xudc->uपंचांगi_phy)
		वापस -ENOMEM;

	xudc->usb3_phy = devm_kसुस्मृति(xudc->dev, xudc->soc->num_phys,
					   माप(*xudc->usb3_phy), GFP_KERNEL);
	अगर (!xudc->usb3_phy)
		वापस -ENOMEM;

	xudc->usbphy = devm_kसुस्मृति(xudc->dev, xudc->soc->num_phys,
					   माप(*xudc->usbphy), GFP_KERNEL);
	अगर (!xudc->usbphy)
		वापस -ENOMEM;

	xudc->vbus_nb.notअगरier_call = tegra_xudc_vbus_notअगरy;

	क्रम (i = 0; i < xudc->soc->num_phys; i++) अणु
		अक्षर phy_name[] = "usb.-.";

		/* Get USB2 phy */
		snम_लिखो(phy_name, माप(phy_name), "usb2-%d", i);
		xudc->uपंचांगi_phy[i] = devm_phy_optional_get(xudc->dev, phy_name);
		अगर (IS_ERR(xudc->uपंचांगi_phy[i])) अणु
			err = PTR_ERR(xudc->uपंचांगi_phy[i]);
			अगर (err != -EPROBE_DEFER)
				dev_err(xudc->dev, "failed to get usb2-%d PHY: %d\n",
					i, err);

			जाओ clean_up;
		पूर्ण अन्यथा अगर (xudc->uपंचांगi_phy[i]) अणु
			/* Get usb-phy, अगर uपंचांगi phy is available */
			xudc->usbphy[i] = devm_usb_get_phy_by_node(xudc->dev,
						xudc->uपंचांगi_phy[i]->dev.of_node,
						&xudc->vbus_nb);
			अगर (IS_ERR(xudc->usbphy[i])) अणु
				err = PTR_ERR(xudc->usbphy[i]);
				dev_err(xudc->dev, "failed to get usbphy-%d: %d\n",
					i, err);
				जाओ clean_up;
			पूर्ण
		पूर्ण अन्यथा अगर (!xudc->uपंचांगi_phy[i]) अणु
			/* अगर uपंचांगi phy is not available, ignore USB3 phy get */
			जारी;
		पूर्ण

		/* Get USB3 phy */
		usb3 = tegra_xusb_padctl_get_usb3_companion(xudc->padctl, i);
		अगर (usb3 < 0)
			जारी;

		snम_लिखो(phy_name, माप(phy_name), "usb3-%d", usb3);
		xudc->usb3_phy[i] = devm_phy_optional_get(xudc->dev, phy_name);
		अगर (IS_ERR(xudc->usb3_phy[i])) अणु
			err = PTR_ERR(xudc->usb3_phy[i]);
			अगर (err != -EPROBE_DEFER)
				dev_err(xudc->dev, "failed to get usb3-%d PHY: %d\n",
					usb3, err);

			जाओ clean_up;
		पूर्ण अन्यथा अगर (xudc->usb3_phy[i])
			dev_dbg(xudc->dev, "usb3-%d PHY registered", usb3);
	पूर्ण

	वापस err;

clean_up:
	क्रम (i = 0; i < xudc->soc->num_phys; i++) अणु
		xudc->usb3_phy[i] = शून्य;
		xudc->uपंचांगi_phy[i] = शून्य;
		xudc->usbphy[i] = शून्य;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम tegra_xudc_phy_निकास(काष्ठा tegra_xudc *xudc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < xudc->soc->num_phys; i++) अणु
		phy_निकास(xudc->usb3_phy[i]);
		phy_निकास(xudc->uपंचांगi_phy[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xudc_phy_init(काष्ठा tegra_xudc *xudc)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < xudc->soc->num_phys; i++) अणु
		err = phy_init(xudc->uपंचांगi_phy[i]);
		अगर (err < 0) अणु
			dev_err(xudc->dev, "UTMI PHY #%u initialization failed: %d\n", i, err);
			जाओ निकास_phy;
		पूर्ण

		err = phy_init(xudc->usb3_phy[i]);
		अगर (err < 0) अणु
			dev_err(xudc->dev, "USB3 PHY #%u initialization failed: %d\n", i, err);
			जाओ निकास_phy;
		पूर्ण
	पूर्ण
	वापस 0;

निकास_phy:
	tegra_xudc_phy_निकास(xudc);
	वापस err;
पूर्ण

अटल स्थिर अक्षर * स्थिर tegra210_xudc_supply_names[] = अणु
	"hvdd-usb",
	"avddio-usb",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_xudc_घड़ी_names[] = अणु
	"dev",
	"ss",
	"ss_src",
	"hs_src",
	"fs_src",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra186_xudc_घड़ी_names[] = अणु
	"dev",
	"ss",
	"ss_src",
	"fs_src",
पूर्ण;

अटल काष्ठा tegra_xudc_soc tegra210_xudc_soc_data = अणु
	.supply_names = tegra210_xudc_supply_names,
	.num_supplies = ARRAY_SIZE(tegra210_xudc_supply_names),
	.घड़ी_names = tegra210_xudc_घड़ी_names,
	.num_clks = ARRAY_SIZE(tegra210_xudc_घड़ी_names),
	.num_phys = 4,
	.u1_enable = false,
	.u2_enable = true,
	.lpm_enable = false,
	.invalid_seq_num = true,
	.pls_quirk = true,
	.port_reset_quirk = true,
	.port_speed_quirk = false,
	.has_ipfs = true,
पूर्ण;

अटल काष्ठा tegra_xudc_soc tegra186_xudc_soc_data = अणु
	.घड़ी_names = tegra186_xudc_घड़ी_names,
	.num_clks = ARRAY_SIZE(tegra186_xudc_घड़ी_names),
	.num_phys = 4,
	.u1_enable = true,
	.u2_enable = true,
	.lpm_enable = false,
	.invalid_seq_num = false,
	.pls_quirk = false,
	.port_reset_quirk = false,
	.port_speed_quirk = false,
	.has_ipfs = false,
पूर्ण;

अटल काष्ठा tegra_xudc_soc tegra194_xudc_soc_data = अणु
	.घड़ी_names = tegra186_xudc_घड़ी_names,
	.num_clks = ARRAY_SIZE(tegra186_xudc_घड़ी_names),
	.num_phys = 4,
	.u1_enable = true,
	.u2_enable = true,
	.lpm_enable = true,
	.invalid_seq_num = false,
	.pls_quirk = false,
	.port_reset_quirk = false,
	.port_speed_quirk = true,
	.has_ipfs = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_xudc_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra210-xudc",
		.data = &tegra210_xudc_soc_data
	पूर्ण,
	अणु
		.compatible = "nvidia,tegra186-xudc",
		.data = &tegra186_xudc_soc_data
	पूर्ण,
	अणु
		.compatible = "nvidia,tegra194-xudc",
		.data = &tegra194_xudc_soc_data
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_xudc_of_match);

अटल व्योम tegra_xudc_घातerकरोमुख्य_हटाओ(काष्ठा tegra_xudc *xudc)
अणु
	अगर (xudc->genpd_dl_ss)
		device_link_del(xudc->genpd_dl_ss);
	अगर (xudc->genpd_dl_device)
		device_link_del(xudc->genpd_dl_device);
	अगर (xudc->genpd_dev_ss)
		dev_pm_करोमुख्य_detach(xudc->genpd_dev_ss, true);
	अगर (xudc->genpd_dev_device)
		dev_pm_करोमुख्य_detach(xudc->genpd_dev_device, true);
पूर्ण

अटल पूर्णांक tegra_xudc_घातerकरोमुख्य_init(काष्ठा tegra_xudc *xudc)
अणु
	काष्ठा device *dev = xudc->dev;
	पूर्णांक err;

	xudc->genpd_dev_device = dev_pm_करोमुख्य_attach_by_name(dev, "dev");
	अगर (IS_ERR(xudc->genpd_dev_device)) अणु
		err = PTR_ERR(xudc->genpd_dev_device);
		dev_err(dev, "failed to get device power domain: %d\n", err);
		वापस err;
	पूर्ण

	xudc->genpd_dev_ss = dev_pm_करोमुख्य_attach_by_name(dev, "ss");
	अगर (IS_ERR(xudc->genpd_dev_ss)) अणु
		err = PTR_ERR(xudc->genpd_dev_ss);
		dev_err(dev, "failed to get SuperSpeed power domain: %d\n", err);
		वापस err;
	पूर्ण

	xudc->genpd_dl_device = device_link_add(dev, xudc->genpd_dev_device,
						DL_FLAG_PM_RUNTIME |
						DL_FLAG_STATELESS);
	अगर (!xudc->genpd_dl_device) अणु
		dev_err(dev, "failed to add USB device link\n");
		वापस -ENODEV;
	पूर्ण

	xudc->genpd_dl_ss = device_link_add(dev, xudc->genpd_dev_ss,
					    DL_FLAG_PM_RUNTIME |
					    DL_FLAG_STATELESS);
	अगर (!xudc->genpd_dl_ss) अणु
		dev_err(dev, "failed to add SuperSpeed device link\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xudc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_xudc *xudc;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	xudc = devm_kzalloc(&pdev->dev, माप(*xudc), GFP_KERNEL);
	अगर (!xudc)
		वापस -ENOMEM;

	xudc->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, xudc);

	xudc->soc = of_device_get_match_data(&pdev->dev);
	अगर (!xudc->soc)
		वापस -ENODEV;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "base");
	xudc->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(xudc->base))
		वापस PTR_ERR(xudc->base);
	xudc->phys_base = res->start;

	xudc->fpci = devm_platक्रमm_ioremap_resource_byname(pdev, "fpci");
	अगर (IS_ERR(xudc->fpci))
		वापस PTR_ERR(xudc->fpci);

	अगर (xudc->soc->has_ipfs) अणु
		xudc->ipfs = devm_platक्रमm_ioremap_resource_byname(pdev, "ipfs");
		अगर (IS_ERR(xudc->ipfs))
			वापस PTR_ERR(xudc->ipfs);
	पूर्ण

	xudc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (xudc->irq < 0)
		वापस xudc->irq;

	err = devm_request_irq(&pdev->dev, xudc->irq, tegra_xudc_irq, 0,
			       dev_name(&pdev->dev), xudc);
	अगर (err < 0) अणु
		dev_err(xudc->dev, "failed to claim IRQ#%u: %d\n", xudc->irq,
			err);
		वापस err;
	पूर्ण

	xudc->clks = devm_kसुस्मृति(&pdev->dev, xudc->soc->num_clks, माप(*xudc->clks),
				  GFP_KERNEL);
	अगर (!xudc->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < xudc->soc->num_clks; i++)
		xudc->clks[i].id = xudc->soc->घड़ी_names[i];

	err = devm_clk_bulk_get(&pdev->dev, xudc->soc->num_clks, xudc->clks);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(xudc->dev, "failed to request clocks: %d\n", err);

		वापस err;
	पूर्ण

	xudc->supplies = devm_kसुस्मृति(&pdev->dev, xudc->soc->num_supplies,
				      माप(*xudc->supplies), GFP_KERNEL);
	अगर (!xudc->supplies)
		वापस -ENOMEM;

	क्रम (i = 0; i < xudc->soc->num_supplies; i++)
		xudc->supplies[i].supply = xudc->soc->supply_names[i];

	err = devm_regulator_bulk_get(&pdev->dev, xudc->soc->num_supplies,
				      xudc->supplies);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(xudc->dev, "failed to request regulators: %d\n", err);

		वापस err;
	पूर्ण

	xudc->padctl = tegra_xusb_padctl_get(&pdev->dev);
	अगर (IS_ERR(xudc->padctl))
		वापस PTR_ERR(xudc->padctl);

	err = regulator_bulk_enable(xudc->soc->num_supplies, xudc->supplies);
	अगर (err) अणु
		dev_err(xudc->dev, "failed to enable regulators: %d\n", err);
		जाओ put_padctl;
	पूर्ण

	err = tegra_xudc_phy_get(xudc);
	अगर (err)
		जाओ disable_regulator;

	err = tegra_xudc_घातerकरोमुख्य_init(xudc);
	अगर (err)
		जाओ put_घातerकरोमुख्यs;

	err = tegra_xudc_phy_init(xudc);
	अगर (err)
		जाओ put_घातerकरोमुख्यs;

	err = tegra_xudc_alloc_event_ring(xudc);
	अगर (err)
		जाओ disable_phy;

	err = tegra_xudc_alloc_eps(xudc);
	अगर (err)
		जाओ मुक्त_event_ring;

	spin_lock_init(&xudc->lock);

	init_completion(&xudc->disconnect_complete);

	INIT_WORK(&xudc->usb_role_sw_work, tegra_xudc_usb_role_sw_work);

	INIT_DELAYED_WORK(&xudc->plc_reset_work, tegra_xudc_plc_reset_work);

	INIT_DELAYED_WORK(&xudc->port_reset_war_work,
				tegra_xudc_port_reset_war_work);

	pm_runसमय_enable(&pdev->dev);

	xudc->gadget.ops = &tegra_xudc_gadget_ops;
	xudc->gadget.ep0 = &xudc->ep[0].usb_ep;
	xudc->gadget.name = "tegra-xudc";
	xudc->gadget.max_speed = USB_SPEED_SUPER;

	err = usb_add_gadget_udc(&pdev->dev, &xudc->gadget);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to add USB gadget: %d\n", err);
		जाओ मुक्त_eps;
	पूर्ण

	वापस 0;

मुक्त_eps:
	tegra_xudc_मुक्त_eps(xudc);
मुक्त_event_ring:
	tegra_xudc_मुक्त_event_ring(xudc);
disable_phy:
	tegra_xudc_phy_निकास(xudc);
put_घातerकरोमुख्यs:
	tegra_xudc_घातerकरोमुख्य_हटाओ(xudc);
disable_regulator:
	regulator_bulk_disable(xudc->soc->num_supplies, xudc->supplies);
put_padctl:
	tegra_xusb_padctl_put(xudc->padctl);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_xudc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_xudc *xudc = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक i;

	pm_runसमय_get_sync(xudc->dev);

	cancel_delayed_work_sync(&xudc->plc_reset_work);
	cancel_work_sync(&xudc->usb_role_sw_work);

	usb_del_gadget_udc(&xudc->gadget);

	tegra_xudc_मुक्त_eps(xudc);
	tegra_xudc_मुक्त_event_ring(xudc);

	tegra_xudc_घातerकरोमुख्य_हटाओ(xudc);

	regulator_bulk_disable(xudc->soc->num_supplies, xudc->supplies);

	क्रम (i = 0; i < xudc->soc->num_phys; i++) अणु
		phy_घातer_off(xudc->uपंचांगi_phy[i]);
		phy_घातer_off(xudc->usb3_phy[i]);
	पूर्ण

	tegra_xudc_phy_निकास(xudc);

	pm_runसमय_disable(xudc->dev);
	pm_runसमय_put(xudc->dev);

	tegra_xusb_padctl_put(xudc->padctl);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_xudc_घातergate(काष्ठा tegra_xudc *xudc)
अणु
	अचिन्हित दीर्घ flags;

	dev_dbg(xudc->dev, "entering ELPG\n");

	spin_lock_irqsave(&xudc->lock, flags);

	xudc->घातergated = true;
	xudc->saved_regs.ctrl = xudc_पढ़ोl(xudc, CTRL);
	xudc->saved_regs.portpm = xudc_पढ़ोl(xudc, PORTPM);
	xudc_ग_लिखोl(xudc, 0, CTRL);

	spin_unlock_irqrestore(&xudc->lock, flags);

	clk_bulk_disable_unprepare(xudc->soc->num_clks, xudc->clks);

	regulator_bulk_disable(xudc->soc->num_supplies, xudc->supplies);

	dev_dbg(xudc->dev, "entering ELPG done\n");
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_xudc_unघातergate(काष्ठा tegra_xudc *xudc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	dev_dbg(xudc->dev, "exiting ELPG\n");

	err = regulator_bulk_enable(xudc->soc->num_supplies,
			xudc->supplies);
	अगर (err < 0)
		वापस err;

	err = clk_bulk_prepare_enable(xudc->soc->num_clks, xudc->clks);
	अगर (err < 0)
		वापस err;

	tegra_xudc_fpci_ipfs_init(xudc);

	tegra_xudc_device_params_init(xudc);

	tegra_xudc_init_event_ring(xudc);

	tegra_xudc_init_eps(xudc);

	xudc_ग_लिखोl(xudc, xudc->saved_regs.portpm, PORTPM);
	xudc_ग_लिखोl(xudc, xudc->saved_regs.ctrl, CTRL);

	spin_lock_irqsave(&xudc->lock, flags);
	xudc->घातergated = false;
	spin_unlock_irqrestore(&xudc->lock, flags);

	dev_dbg(xudc->dev, "exiting ELPG done\n");
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_xudc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_xudc *xudc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&xudc->lock, flags);
	xudc->suspended = true;
	spin_unlock_irqrestore(&xudc->lock, flags);

	flush_work(&xudc->usb_role_sw_work);

	अगर (!pm_runसमय_status_suspended(dev)) अणु
		/* Forcibly disconnect beक्रमe घातergating. */
		tegra_xudc_device_mode_off(xudc);
		tegra_xudc_घातergate(xudc);
	पूर्ण

	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_xudc_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_xudc *xudc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	err = tegra_xudc_unघातergate(xudc);
	अगर (err < 0)
		वापस err;

	spin_lock_irqsave(&xudc->lock, flags);
	xudc->suspended = false;
	spin_unlock_irqrestore(&xudc->lock, flags);

	schedule_work(&xudc->usb_role_sw_work);

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_xudc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_xudc *xudc = dev_get_drvdata(dev);

	वापस tegra_xudc_घातergate(xudc);
पूर्ण

अटल पूर्णांक __maybe_unused tegra_xudc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_xudc *xudc = dev_get_drvdata(dev);

	वापस tegra_xudc_unघातergate(xudc);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_xudc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tegra_xudc_suspend, tegra_xudc_resume)
	SET_RUNTIME_PM_OPS(tegra_xudc_runसमय_suspend,
			   tegra_xudc_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_xudc_driver = अणु
	.probe = tegra_xudc_probe,
	.हटाओ = tegra_xudc_हटाओ,
	.driver = अणु
		.name = "tegra-xudc",
		.pm = &tegra_xudc_pm_ops,
		.of_match_table = tegra_xudc_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_xudc_driver);

MODULE_DESCRIPTION("NVIDIA Tegra XUSB Device Controller");
MODULE_AUTHOR("Andrew Bresticker <abrestic@chromium.org>");
MODULE_AUTHOR("Hui Fu <hfu@nvidia.com>");
MODULE_AUTHOR("Nagarjuna Kristam <nkristam@nvidia.com>");
MODULE_LICENSE("GPL v2");
