<शैली गुरु>
/*
 * Copyright (c) 2012 - 2017 Intel Corporation.  All rights reserved.
 * Copyright (c) 2008 - 2012 QLogic Corporation. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * This file contains all of the code that is specअगरic to the
 * InfiniPath 7322 chip
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_smi.h>
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
#समावेश <linux/dca.h>
#पूर्ण_अगर

#समावेश "qib.h"
#समावेश "qib_7322_regs.h"
#समावेश "qib_qsfp.h"

#समावेश "qib_mad.h"
#समावेश "qib_verbs.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) QIB_DRV_NAME " " fmt

अटल व्योम qib_setup_7322_setextled(काष्ठा qib_pportdata *, u32);
अटल व्योम qib_7322_handle_hwerrors(काष्ठा qib_devdata *, अक्षर *, माप_प्रकार);
अटल व्योम sendctrl_7322_mod(काष्ठा qib_pportdata *ppd, u32 op);
अटल irqवापस_t qib_7322पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t qib_7322bufavail(पूर्णांक irq, व्योम *data);
अटल irqवापस_t sdma_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t sdma_idle_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t sdma_progress_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t sdma_cleanup_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल व्योम qib_7322_txchk_change(काष्ठा qib_devdata *, u32, u32, u32,
				  काष्ठा qib_ctxtdata *rcd);
अटल u8 qib_7322_phys_portstate(u64);
अटल u32 qib_7322_iblink_state(u64);
अटल व्योम qib_set_ib_7322_lstate(काष्ठा qib_pportdata *ppd, u16 linkcmd,
				   u16 linitcmd);
अटल व्योम क्रमce_h1(काष्ठा qib_pportdata *);
अटल व्योम adj_tx_serdes(काष्ठा qib_pportdata *);
अटल u32 qib_7322_setpbc_control(काष्ठा qib_pportdata *, u32, u8, u8);
अटल व्योम qib_7322_mini_pcs_reset(काष्ठा qib_pportdata *);

अटल u32 ahb_mod(काष्ठा qib_devdata *, पूर्णांक, पूर्णांक, पूर्णांक, u32, u32);
अटल व्योम ibsd_wr_allchans(काष्ठा qib_pportdata *, पूर्णांक, अचिन्हित, अचिन्हित);
अटल व्योम serdes_7322_los_enable(काष्ठा qib_pportdata *, पूर्णांक);
अटल पूर्णांक serdes_7322_init_old(काष्ठा qib_pportdata *);
अटल पूर्णांक serdes_7322_init_new(काष्ठा qib_pportdata *);
अटल व्योम dump_sdma_7322_state(काष्ठा qib_pportdata *);

#घोषणा BMASK(msb, lsb) (((1 << ((msb) + 1 - (lsb))) - 1) << (lsb))

/* LE2 serdes values क्रम dअगरferent हालs */
#घोषणा LE2_DEFAULT 5
#घोषणा LE2_5m 4
#घोषणा LE2_QME 0

/* Below is special-purpose, so only really works क्रम the IB SerDes blocks. */
#घोषणा IBSD(hw_pidx) (hw_pidx + 2)

/* these are variables क्रम करोcumentation and experimentation purposes */
अटल स्थिर अचिन्हित rcv_पूर्णांक_समयout = 375;
अटल स्थिर अचिन्हित rcv_पूर्णांक_count = 16;
अटल स्थिर अचिन्हित sdma_idle_cnt = 64;

/* Time to stop altering Rx Equalization parameters, after link up. */
#घोषणा RXEQ_DISABLE_MSECS 2500

/*
 * Number of VLs we are configured to use (to allow क्रम more
 * credits per vl, etc.)
 */
uलघु qib_num_cfg_vls = 2;
module_param_named(num_vls, qib_num_cfg_vls, uलघु, S_IRUGO);
MODULE_PARM_DESC(num_vls, "Set number of Virtual Lanes to use (1-8)");

अटल uलघु qib_chase = 1;
module_param_named(chase, qib_chase, uलघु, S_IRUGO);
MODULE_PARM_DESC(chase, "Enable state chase handling");

अटल uलघु qib_दीर्घ_atten = 10; /* 10 dB ~= 5m length */
module_param_named(दीर्घ_attenuation, qib_दीर्घ_atten, uलघु, S_IRUGO);
MODULE_PARM_DESC(दीर्घ_attenuation,
		 "attenuation cutoff (dB) for long copper cable setup");

अटल uलघु qib_singleport;
module_param_named(singleport, qib_singleport, uलघु, S_IRUGO);
MODULE_PARM_DESC(singleport, "Use only IB port 1; more per-port buffer space");

अटल uलघु qib_krcvq01_no_msi;
module_param_named(krcvq01_no_msi, qib_krcvq01_no_msi, uलघु, S_IRUGO);
MODULE_PARM_DESC(krcvq01_no_msi, "No MSI for kctx < 2");

/*
 * Receive header queue sizes
 */
अटल अचिन्हित qib_rcvhdrcnt;
module_param_named(rcvhdrcnt, qib_rcvhdrcnt, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rcvhdrcnt, "receive header count");

अटल अचिन्हित qib_rcvhdrsize;
module_param_named(rcvhdrsize, qib_rcvhdrsize, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rcvhdrsize, "receive header size in 32-bit words");

अटल अचिन्हित qib_rcvhdrentsize;
module_param_named(rcvhdrentsize, qib_rcvhdrentsize, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rcvhdrentsize, "receive header entry size in 32-bit words");

#घोषणा MAX_ATTEN_LEN 64 /* plenty क्रम any real प्रणाली */
/* क्रम पढ़ो back, शेष index is ~5m copper cable */
अटल अक्षर txselect_list[MAX_ATTEN_LEN] = "10";
अटल काष्ठा kparam_string kp_txselect = अणु
	.string = txselect_list,
	.maxlen = MAX_ATTEN_LEN
पूर्ण;
अटल पूर्णांक  setup_txselect(स्थिर अक्षर *, स्थिर काष्ठा kernel_param *);
module_param_call(txselect, setup_txselect, param_get_string,
		  &kp_txselect, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(txselect,
		 "Tx serdes indices (for no QSFP or invalid QSFP data)");

#घोषणा BOARD_QME7342 5
#घोषणा BOARD_QMH7342 6
#घोषणा BOARD_QMH7360 9
#घोषणा IS_QMH(dd) (SYM_FIELD((dd)->revision, Revision, BoardID) == \
		    BOARD_QMH7342)
#घोषणा IS_QME(dd) (SYM_FIELD((dd)->revision, Revision, BoardID) == \
		    BOARD_QME7342)

#घोषणा KREG_IDX(regname)     (QIB_7322_##regname##_OFFS / माप(u64))

#घोषणा KREG_IBPORT_IDX(regname) ((QIB_7322_##regname##_0_OFFS / माप(u64)))

#घोषणा MASK_ACROSS(lsb, msb) \
	(((1ULL << ((msb) + 1 - (lsb))) - 1) << (lsb))

#घोषणा SYM_RMASK(regname, fldname) ((u64)              \
	QIB_7322_##regname##_##fldname##_RMASK)

#घोषणा SYM_MASK(regname, fldname) ((u64)               \
	QIB_7322_##regname##_##fldname##_RMASK <<       \
	 QIB_7322_##regname##_##fldname##_LSB)

#घोषणा SYM_FIELD(value, regname, fldname) ((u64)	\
	(((value) >> SYM_LSB(regname, fldname)) &	\
	 SYM_RMASK(regname, fldname)))

/* useful क्रम things like LaFअगरoEmpty_0...7, TxCreditOK_0...7, etc. */
#घोषणा SYM_FIELD_ACROSS(value, regname, fldname, nbits) \
	(((value) >> SYM_LSB(regname, fldname)) & MASK_ACROSS(0, nbits))

#घोषणा HWE_MASK(fldname) SYM_MASK(HwErrMask, fldname##Mask)
#घोषणा ERR_MASK(fldname) SYM_MASK(ErrMask, fldname##Mask)
#घोषणा ERR_MASK_N(fldname) SYM_MASK(ErrMask_0, fldname##Mask)
#घोषणा INT_MASK(fldname) SYM_MASK(IntMask, fldname##IntMask)
#घोषणा INT_MASK_P(fldname, port) SYM_MASK(IntMask, fldname##IntMask##_##port)
/* Below because most, but not all, fields of IntMask have that full suffix */
#घोषणा INT_MASK_PM(fldname, port) SYM_MASK(IntMask, fldname##Mask##_##port)


#घोषणा SYM_LSB(regname, fldname) (QIB_7322_##regname##_##fldname##_LSB)

/*
 * the size bits give us 2^N, in KB units.  0 marks as invalid,
 * and 7 is reserved.  We currently use only 2KB and 4KB
 */
#घोषणा IBA7322_TID_SZ_SHIFT QIB_7322_RcvTIDArray0_RT_BufSize_LSB
#घोषणा IBA7322_TID_SZ_2K (1UL<<IBA7322_TID_SZ_SHIFT) /* 2KB */
#घोषणा IBA7322_TID_SZ_4K (2UL<<IBA7322_TID_SZ_SHIFT) /* 4KB */
#घोषणा IBA7322_TID_PA_SHIFT 11U /* TID addr in chip stored w/o low bits */

#घोषणा SendIBSLIDAssignMask \
	QIB_7322_SendIBSLIDAssign_0_SendIBSLIDAssign_15_0_RMASK
#घोषणा SendIBSLMCMask \
	QIB_7322_SendIBSLIDMask_0_SendIBSLIDMask_15_0_RMASK

#घोषणा ExtLED_IB1_YEL SYM_MASK(EXTCtrl, LEDPort0YellowOn)
#घोषणा ExtLED_IB1_GRN SYM_MASK(EXTCtrl, LEDPort0GreenOn)
#घोषणा ExtLED_IB2_YEL SYM_MASK(EXTCtrl, LEDPort1YellowOn)
#घोषणा ExtLED_IB2_GRN SYM_MASK(EXTCtrl, LEDPort1GreenOn)
#घोषणा ExtLED_IB1_MASK (ExtLED_IB1_YEL | ExtLED_IB1_GRN)
#घोषणा ExtLED_IB2_MASK (ExtLED_IB2_YEL | ExtLED_IB2_GRN)

#घोषणा _QIB_GPIO_SDA_NUM 1
#घोषणा _QIB_GPIO_SCL_NUM 0
#घोषणा QIB_EEPROM_WEN_NUM 14
#घोषणा QIB_TWSI_EEPROM_DEV 0xA2 /* All Production 7322 cards. */

/* HW counter घड़ी is at 4nsec */
#घोषणा QIB_7322_PSXMITWAIT_CHECK_RATE 4000

/* full speed IB port 1 only */
#घोषणा PORT_SPD_CAP (QIB_IB_SDR | QIB_IB_DDR | QIB_IB_QDR)
#घोषणा PORT_SPD_CAP_SHIFT 3

/* full speed featuremask, both ports */
#घोषणा DUAL_PORT_CAP (PORT_SPD_CAP | (PORT_SPD_CAP << PORT_SPD_CAP_SHIFT))

/*
 * This file contains almost all the chip-specअगरic रेजिस्टर inक्रमmation and
 * access functions क्रम the FAKED QLogic InfiniPath 7322 PCI-Express chip.
 */

/* Use defines to tie machine-generated names to lower-हाल names */
#घोषणा kr_contextcnt KREG_IDX(ContextCnt)
#घोषणा kr_control KREG_IDX(Control)
#घोषणा kr_counterregbase KREG_IDX(CntrRegBase)
#घोषणा kr_errclear KREG_IDX(ErrClear)
#घोषणा kr_errmask KREG_IDX(ErrMask)
#घोषणा kr_errstatus KREG_IDX(ErrStatus)
#घोषणा kr_extctrl KREG_IDX(EXTCtrl)
#घोषणा kr_extstatus KREG_IDX(EXTStatus)
#घोषणा kr_gpio_clear KREG_IDX(GPIOClear)
#घोषणा kr_gpio_mask KREG_IDX(GPIOMask)
#घोषणा kr_gpio_out KREG_IDX(GPIOOut)
#घोषणा kr_gpio_status KREG_IDX(GPIOStatus)
#घोषणा kr_hwdiagctrl KREG_IDX(HwDiagCtrl)
#घोषणा kr_debugportval KREG_IDX(DebugPortValueReg)
#घोषणा kr_fmask KREG_IDX(feature_mask)
#घोषणा kr_act_fmask KREG_IDX(active_feature_mask)
#घोषणा kr_hwerrclear KREG_IDX(HwErrClear)
#घोषणा kr_hwerrmask KREG_IDX(HwErrMask)
#घोषणा kr_hwerrstatus KREG_IDX(HwErrStatus)
#घोषणा kr_पूर्णांकclear KREG_IDX(IntClear)
#घोषणा kr_पूर्णांकmask KREG_IDX(IntMask)
#घोषणा kr_पूर्णांकredirect KREG_IDX(IntRedirect0)
#घोषणा kr_पूर्णांकstatus KREG_IDX(IntStatus)
#घोषणा kr_pagealign KREG_IDX(PageAlign)
#घोषणा kr_rcvavailसमयout KREG_IDX(RcvAvailTimeOut0)
#घोषणा kr_rcvctrl KREG_IDX(RcvCtrl) /* Common, but chip also has per-port */
#घोषणा kr_rcvegrbase KREG_IDX(RcvEgrBase)
#घोषणा kr_rcvegrcnt KREG_IDX(RcvEgrCnt)
#घोषणा kr_rcvhdrcnt KREG_IDX(RcvHdrCnt)
#घोषणा kr_rcvhdrentsize KREG_IDX(RcvHdrEntSize)
#घोषणा kr_rcvhdrsize KREG_IDX(RcvHdrSize)
#घोषणा kr_rcvtidbase KREG_IDX(RcvTIDBase)
#घोषणा kr_rcvtidcnt KREG_IDX(RcvTIDCnt)
#घोषणा kr_revision KREG_IDX(Revision)
#घोषणा kr_scratch KREG_IDX(Scratch)
#घोषणा kr_sendbuffererror KREG_IDX(SendBufErr0) /* and base क्रम 1 and 2 */
#घोषणा kr_sendcheckmask KREG_IDX(SendCheckMask0) /* and 1, 2 */
#घोषणा kr_sendctrl KREG_IDX(SendCtrl)
#घोषणा kr_sendgrhcheckmask KREG_IDX(SendGRHCheckMask0) /* and 1, 2 */
#घोषणा kr_sendibpkपंचांगask KREG_IDX(SendIBPacketMask0) /* and 1, 2 */
#घोषणा kr_sendpioavailaddr KREG_IDX(SendBufAvailAddr)
#घोषणा kr_sendpiobufbase KREG_IDX(SendBufBase)
#घोषणा kr_sendpiobufcnt KREG_IDX(SendBufCnt)
#घोषणा kr_sendpiosize KREG_IDX(SendBufSize)
#घोषणा kr_sendregbase KREG_IDX(SendRegBase)
#घोषणा kr_sendbufavail0 KREG_IDX(SendBufAvail0)
#घोषणा kr_userregbase KREG_IDX(UserRegBase)
#घोषणा kr_पूर्णांकgranted KREG_IDX(Int_Granted)
#घोषणा kr_vecclr_wo_पूर्णांक KREG_IDX(vec_clr_without_पूर्णांक)
#घोषणा kr_पूर्णांकblocked KREG_IDX(IntBlocked)
#घोषणा kr_r_access KREG_IDX(SPC_JTAG_ACCESS_REG)

/*
 * per-port kernel रेजिस्टरs.  Access only with qib_पढ़ो_kreg_port()
 * or qib_ग_लिखो_kreg_port()
 */
#घोषणा krp_errclear KREG_IBPORT_IDX(ErrClear)
#घोषणा krp_errmask KREG_IBPORT_IDX(ErrMask)
#घोषणा krp_errstatus KREG_IBPORT_IDX(ErrStatus)
#घोषणा krp_highprio_0 KREG_IBPORT_IDX(HighPriority0)
#घोषणा krp_highprio_limit KREG_IBPORT_IDX(HighPriorityLimit)
#घोषणा krp_hrtbt_guid KREG_IBPORT_IDX(HRTBT_GUID)
#घोषणा krp_ib_pcsconfig KREG_IBPORT_IDX(IBPCSConfig)
#घोषणा krp_ibcctrl_a KREG_IBPORT_IDX(IBCCtrlA)
#घोषणा krp_ibcctrl_b KREG_IBPORT_IDX(IBCCtrlB)
#घोषणा krp_ibcctrl_c KREG_IBPORT_IDX(IBCCtrlC)
#घोषणा krp_ibcstatus_a KREG_IBPORT_IDX(IBCStatusA)
#घोषणा krp_ibcstatus_b KREG_IBPORT_IDX(IBCStatusB)
#घोषणा krp_txestatus KREG_IBPORT_IDX(TXEStatus)
#घोषणा krp_lowprio_0 KREG_IBPORT_IDX(LowPriority0)
#घोषणा krp_ncmodectrl KREG_IBPORT_IDX(IBNCModeCtrl)
#घोषणा krp_partitionkey KREG_IBPORT_IDX(RcvPartitionKey)
#घोषणा krp_psपूर्णांकerval KREG_IBPORT_IDX(PSInterval)
#घोषणा krp_psstart KREG_IBPORT_IDX(PSStart)
#घोषणा krp_psstat KREG_IBPORT_IDX(PSStat)
#घोषणा krp_rcvbthqp KREG_IBPORT_IDX(RcvBTHQP)
#घोषणा krp_rcvctrl KREG_IBPORT_IDX(RcvCtrl)
#घोषणा krp_rcvpktledcnt KREG_IBPORT_IDX(RcvPktLEDCnt)
#घोषणा krp_rcvqpmaptable KREG_IBPORT_IDX(RcvQPMapTableA)
#घोषणा krp_rxcreditvl0 KREG_IBPORT_IDX(RxCreditVL0)
#घोषणा krp_rxcreditvl15 (KREG_IBPORT_IDX(RxCreditVL0)+15)
#घोषणा krp_sendcheckcontrol KREG_IBPORT_IDX(SendCheckControl)
#घोषणा krp_sendctrl KREG_IBPORT_IDX(SendCtrl)
#घोषणा krp_senddmabase KREG_IBPORT_IDX(SendDmaBase)
#घोषणा krp_senddmabufmask0 KREG_IBPORT_IDX(SendDmaBufMask0)
#घोषणा krp_senddmabufmask1 (KREG_IBPORT_IDX(SendDmaBufMask0) + 1)
#घोषणा krp_senddmabufmask2 (KREG_IBPORT_IDX(SendDmaBufMask0) + 2)
#घोषणा krp_senddmabuf_use0 KREG_IBPORT_IDX(SendDmaBufUsed0)
#घोषणा krp_senddmabuf_use1 (KREG_IBPORT_IDX(SendDmaBufUsed0) + 1)
#घोषणा krp_senddmabuf_use2 (KREG_IBPORT_IDX(SendDmaBufUsed0) + 2)
#घोषणा krp_senddmadesccnt KREG_IBPORT_IDX(SendDmaDescCnt)
#घोषणा krp_senddmahead KREG_IBPORT_IDX(SendDmaHead)
#घोषणा krp_senddmaheadaddr KREG_IBPORT_IDX(SendDmaHeadAddr)
#घोषणा krp_senddmaidlecnt KREG_IBPORT_IDX(SendDmaIdleCnt)
#घोषणा krp_senddmalengen KREG_IBPORT_IDX(SendDmaLenGen)
#घोषणा krp_senddmaprioritythld KREG_IBPORT_IDX(SendDmaPriorityThld)
#घोषणा krp_senddmareloadcnt KREG_IBPORT_IDX(SendDmaReloadCnt)
#घोषणा krp_senddmastatus KREG_IBPORT_IDX(SendDmaStatus)
#घोषणा krp_senddmatail KREG_IBPORT_IDX(SendDmaTail)
#घोषणा krp_sendhdrsymptom KREG_IBPORT_IDX(SendHdrErrSymptom)
#घोषणा krp_sendslid KREG_IBPORT_IDX(SendIBSLIDAssign)
#घोषणा krp_sendslidmask KREG_IBPORT_IDX(SendIBSLIDMask)
#घोषणा krp_ibsdtestअगरtx KREG_IBPORT_IDX(IB_SDTEST_IF_TX)
#घोषणा krp_adapt_dis_समयr KREG_IBPORT_IDX(ADAPT_DISABLE_TIMER_THRESHOLD)
#घोषणा krp_tx_deemph_override KREG_IBPORT_IDX(IBSD_TX_DEEMPHASIS_OVERRIDE)
#घोषणा krp_serdesctrl KREG_IBPORT_IDX(IBSerdesCtrl)

/*
 * Per-context kernel रेजिस्टरs.  Access only with qib_पढ़ो_kreg_ctxt()
 * or qib_ग_लिखो_kreg_ctxt()
 */
#घोषणा krc_rcvhdraddr KREG_IDX(RcvHdrAddr0)
#घोषणा krc_rcvhdrtailaddr KREG_IDX(RcvHdrTailAddr0)

/*
 * TID Flow table, per context.  Reduces
 * number of hdrq updates to one per flow (or on errors).
 * context 0 and 1 share same memory, but have distinct
 * addresses.  Since क्रम now, we never use expected sends
 * on kernel contexts, we करोn't worry about that (we initialize
 * those entries क्रम ctxt 0/1 on driver load twice, क्रम example).
 */
#घोषणा NUM_TIDFLOWS_CTXT 0x20 /* 0x20 per context; have to hardcode */
#घोषणा ur_rcvflowtable (KREG_IDX(RcvTIDFlowTable0) - KREG_IDX(RcvHdrTail0))

/* these are the error bits in the tid flows, and are W1C */
#घोषणा TIDFLOW_ERRBITS  ( \
	(SYM_MASK(RcvTIDFlowTable0, GenMismatch) << \
	SYM_LSB(RcvTIDFlowTable0, GenMismatch)) | \
	(SYM_MASK(RcvTIDFlowTable0, SeqMismatch) << \
	SYM_LSB(RcvTIDFlowTable0, SeqMismatch)))

/* Most (not all) Counters are per-IBport.
 * Requires LBIntCnt is at offset 0 in the group
 */
#घोषणा CREG_IDX(regname) \
((QIB_7322_##regname##_0_OFFS - QIB_7322_LBIntCnt_OFFS) / माप(u64))

#घोषणा crp_badक्रमmat CREG_IDX(RxVersionErrCnt)
#घोषणा crp_err_rlen CREG_IDX(RxLenErrCnt)
#घोषणा crp_erricrc CREG_IDX(RxICRCErrCnt)
#घोषणा crp_errlink CREG_IDX(RxLinkMalक्रमmCnt)
#घोषणा crp_errlpcrc CREG_IDX(RxLPCRCErrCnt)
#घोषणा crp_errpkey CREG_IDX(RxPKeyMismatchCnt)
#घोषणा crp_errvcrc CREG_IDX(RxVCRCErrCnt)
#घोषणा crp_excessbufferovfl CREG_IDX(ExcessBufferOvflCnt)
#घोषणा crp_iblinkकरोwn CREG_IDX(IBLinkDownedCnt)
#घोषणा crp_iblinkerrrecov CREG_IDX(IBLinkErrRecoveryCnt)
#घोषणा crp_ibstatuschange CREG_IDX(IBStatusChangeCnt)
#घोषणा crp_ibsymbolerr CREG_IDX(IBSymbolErrCnt)
#घोषणा crp_invalidrlen CREG_IDX(RxMaxMinLenErrCnt)
#घोषणा crp_locallinkपूर्णांकegrityerr CREG_IDX(LocalLinkIntegrityErrCnt)
#घोषणा crp_pktrcv CREG_IDX(RxDataPktCnt)
#घोषणा crp_pktrcvflowctrl CREG_IDX(RxFlowPktCnt)
#घोषणा crp_pktsend CREG_IDX(TxDataPktCnt)
#घोषणा crp_pktsendflow CREG_IDX(TxFlowPktCnt)
#घोषणा crp_psrcvdatacount CREG_IDX(PSRcvDataCount)
#घोषणा crp_psrcvpktscount CREG_IDX(PSRcvPktsCount)
#घोषणा crp_psxmitdatacount CREG_IDX(PSXmitDataCount)
#घोषणा crp_psxmitpktscount CREG_IDX(PSXmitPktsCount)
#घोषणा crp_psxmitरुकोcount CREG_IDX(PSXmitWaitCount)
#घोषणा crp_rcvebp CREG_IDX(RxEBPCnt)
#घोषणा crp_rcvflowctrlviol CREG_IDX(RxFlowCtrlViolCnt)
#घोषणा crp_rcvovfl CREG_IDX(RxBufOvflCnt)
#घोषणा crp_rxdlidfltr CREG_IDX(RxDlidFltrCnt)
#घोषणा crp_rxdroppkt CREG_IDX(RxDroppedPktCnt)
#घोषणा crp_rxotherlocalphyerr CREG_IDX(RxOtherLocalPhyErrCnt)
#घोषणा crp_rxqpinvalidctxt CREG_IDX(RxQPInvalidContextCnt)
#घोषणा crp_rxvlerr CREG_IDX(RxVlErrCnt)
#घोषणा crp_sendstall CREG_IDX(TxFlowStallCnt)
#घोषणा crp_txdroppedpkt CREG_IDX(TxDroppedPktCnt)
#घोषणा crp_txhdrerr CREG_IDX(TxHeadersErrCnt)
#घोषणा crp_txlenerr CREG_IDX(TxLenErrCnt)
#घोषणा crp_txminmaxlenerr CREG_IDX(TxMaxMinLenErrCnt)
#घोषणा crp_txsdmadesc CREG_IDX(TxSDmaDescCnt)
#घोषणा crp_txunderrun CREG_IDX(TxUnderrunCnt)
#घोषणा crp_txunsupvl CREG_IDX(TxUnsupVLErrCnt)
#घोषणा crp_vl15droppedpkt CREG_IDX(RxVL15DroppedPktCnt)
#घोषणा crp_wordrcv CREG_IDX(RxDwordCnt)
#घोषणा crp_wordsend CREG_IDX(TxDwordCnt)
#घोषणा crp_tx_creditstalls CREG_IDX(TxCreditUpToDateTimeOut)

/* these are the (few) counters that are not port-specअगरic */
#घोषणा CREG_DEVIDX(regname) ((QIB_7322_##regname##_OFFS - \
			QIB_7322_LBIntCnt_OFFS) / माप(u64))
#घोषणा cr_base_egrovfl CREG_DEVIDX(RxP0HdrEgrOvflCnt)
#घोषणा cr_lbपूर्णांक CREG_DEVIDX(LBIntCnt)
#घोषणा cr_lbstall CREG_DEVIDX(LBFlowStallCnt)
#घोषणा cr_pcieretrydiag CREG_DEVIDX(PcieRetryBufDiagQwordCnt)
#घोषणा cr_rxtidflowdrop CREG_DEVIDX(RxTidFlowDropCnt)
#घोषणा cr_tidfull CREG_DEVIDX(RxTIDFullErrCnt)
#घोषणा cr_tidinvalid CREG_DEVIDX(RxTIDValidErrCnt)

/* no chip रेजिस्टर क्रम # of IB ports supported, so define */
#घोषणा NUM_IB_PORTS 2

/* 1 VL15 buffer per hardware IB port, no रेजिस्टर क्रम this, so define */
#घोषणा NUM_VL15_BUFS NUM_IB_PORTS

/*
 * context 0 and 1 are special, and there is no chip रेजिस्टर that
 * defines this value, so we have to define it here.
 * These are all allocated to either 0 or 1 क्रम single port
 * hardware configuration, otherwise each माला_लो half
 */
#घोषणा KCTXT0_EGRCNT 2048

/* values क्रम vl and port fields in PBC, 7322-specअगरic */
#घोषणा PBC_PORT_SEL_LSB 26
#घोषणा PBC_PORT_SEL_RMASK 1
#घोषणा PBC_VL_NUM_LSB 27
#घोषणा PBC_VL_NUM_RMASK 7
#घोषणा PBC_7322_VL15_SEND (1ULL << 63) /* pbc; VL15, no credit check */
#घोषणा PBC_7322_VL15_SEND_CTRL (1ULL << 31) /* control version of same */

अटल u8 ib_rate_to_delay[IB_RATE_120_GBPS + 1] = अणु
	[IB_RATE_2_5_GBPS] = 16,
	[IB_RATE_5_GBPS] = 8,
	[IB_RATE_10_GBPS] = 4,
	[IB_RATE_20_GBPS] = 2,
	[IB_RATE_30_GBPS] = 2,
	[IB_RATE_40_GBPS] = 1
पूर्ण;

अटल स्थिर अक्षर * स्थिर qib_sdma_state_names[] = अणु
	[qib_sdma_state_s00_hw_करोwn]          = "s00_HwDown",
	[qib_sdma_state_s10_hw_start_up_रुको] = "s10_HwStartUpWait",
	[qib_sdma_state_s20_idle]             = "s20_Idle",
	[qib_sdma_state_s30_sw_clean_up_रुको] = "s30_SwCleanUpWait",
	[qib_sdma_state_s40_hw_clean_up_रुको] = "s40_HwCleanUpWait",
	[qib_sdma_state_s50_hw_halt_रुको]     = "s50_HwHaltWait",
	[qib_sdma_state_s99_running]          = "s99_Running",
पूर्ण;

#घोषणा IBA7322_LINKSPEED_SHIFT SYM_LSB(IBCStatusA_0, LinkSpeedActive)
#घोषणा IBA7322_LINKWIDTH_SHIFT SYM_LSB(IBCStatusA_0, LinkWidthActive)

/* link training states, from IBC */
#घोषणा IB_7322_LT_STATE_DISABLED        0x00
#घोषणा IB_7322_LT_STATE_LINKUP          0x01
#घोषणा IB_7322_LT_STATE_POLLACTIVE      0x02
#घोषणा IB_7322_LT_STATE_POLLQUIET       0x03
#घोषणा IB_7322_LT_STATE_SLEEPDELAY      0x04
#घोषणा IB_7322_LT_STATE_SLEEPQUIET      0x05
#घोषणा IB_7322_LT_STATE_CFGDEBOUNCE     0x08
#घोषणा IB_7322_LT_STATE_CFGRCVFCFG      0x09
#घोषणा IB_7322_LT_STATE_CFGWAITRMT      0x0a
#घोषणा IB_7322_LT_STATE_CFGIDLE         0x0b
#घोषणा IB_7322_LT_STATE_RECOVERRETRAIN  0x0c
#घोषणा IB_7322_LT_STATE_TXREVLANES      0x0d
#घोषणा IB_7322_LT_STATE_RECOVERWAITRMT  0x0e
#घोषणा IB_7322_LT_STATE_RECOVERIDLE     0x0f
#घोषणा IB_7322_LT_STATE_CFGENH          0x10
#घोषणा IB_7322_LT_STATE_CFGTEST         0x11
#घोषणा IB_7322_LT_STATE_CFGWAITRMTTEST  0x12
#घोषणा IB_7322_LT_STATE_CFGWAITENH      0x13

/* link state machine states from IBC */
#घोषणा IB_7322_L_STATE_DOWN             0x0
#घोषणा IB_7322_L_STATE_INIT             0x1
#घोषणा IB_7322_L_STATE_ARM              0x2
#घोषणा IB_7322_L_STATE_ACTIVE           0x3
#घोषणा IB_7322_L_STATE_ACT_DEFER        0x4

अटल स्थिर u8 qib_7322_physportstate[0x20] = अणु
	[IB_7322_LT_STATE_DISABLED] = IB_PHYSPORTSTATE_DISABLED,
	[IB_7322_LT_STATE_LINKUP] = IB_PHYSPORTSTATE_LINKUP,
	[IB_7322_LT_STATE_POLLACTIVE] = IB_PHYSPORTSTATE_POLL,
	[IB_7322_LT_STATE_POLLQUIET] = IB_PHYSPORTSTATE_POLL,
	[IB_7322_LT_STATE_SLEEPDELAY] = IB_PHYSPORTSTATE_SLEEP,
	[IB_7322_LT_STATE_SLEEPQUIET] = IB_PHYSPORTSTATE_SLEEP,
	[IB_7322_LT_STATE_CFGDEBOUNCE] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7322_LT_STATE_CFGRCVFCFG] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7322_LT_STATE_CFGWAITRMT] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7322_LT_STATE_CFGIDLE] = IB_PHYSPORTSTATE_CFG_IDLE,
	[IB_7322_LT_STATE_RECOVERRETRAIN] =
		IB_PHYSPORTSTATE_LINK_ERR_RECOVER,
	[IB_7322_LT_STATE_RECOVERWAITRMT] =
		IB_PHYSPORTSTATE_LINK_ERR_RECOVER,
	[IB_7322_LT_STATE_RECOVERIDLE] =
		IB_PHYSPORTSTATE_LINK_ERR_RECOVER,
	[IB_7322_LT_STATE_CFGENH] = IB_PHYSPORTSTATE_CFG_ENH,
	[IB_7322_LT_STATE_CFGTEST] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7322_LT_STATE_CFGWAITRMTTEST] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7322_LT_STATE_CFGWAITENH] =
		IB_PHYSPORTSTATE_CFG_WAIT_ENH,
	[0x14] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x15] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x16] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x17] = IB_PHYSPORTSTATE_CFG_TRAIN
पूर्ण;

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
काष्ठा qib_irq_notअगरy अणु
	पूर्णांक rcv;
	व्योम *arg;
	काष्ठा irq_affinity_notअगरy notअगरy;
पूर्ण;
#पूर्ण_अगर

काष्ठा qib_chip_specअगरic अणु
	u64 __iomem *cregbase;
	u64 *cntrs;
	spinlock_t rcvmod_lock; /* protect rcvctrl shaकरोw changes */
	spinlock_t gpio_lock; /* RMW of shaकरोws/regs क्रम ExtCtrl and GPIO */
	u64 मुख्य_पूर्णांक_mask;      /* clear bits which have dedicated handlers */
	u64 पूर्णांक_enable_mask;  /* क्रम per port पूर्णांकerrupts in single port mode */
	u64 errormask;
	u64 hwerrmask;
	u64 gpio_out; /* shaकरोw of kr_gpio_out, क्रम rmw ops */
	u64 gpio_mask; /* shaकरोw the gpio mask रेजिस्टर */
	u64 extctrl; /* shaकरोw the gpio output enable, etc... */
	u32 ncntrs;
	u32 nportcntrs;
	u32 cntrnamelen;
	u32 portcntrnamelen;
	u32 numctxts;
	u32 rcvegrcnt;
	u32 updthresh; /* current AvailUpdThld */
	u32 updthresh_dflt; /* शेष AvailUpdThld */
	u32 r1;
	u32 num_msix_entries;
	u32 sdmabufcnt;
	u32 lastbuf_क्रम_pio;
	u32 stay_in_मुक्तze;
	u32 recovery_ports_initted;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	u32 dca_ctrl;
	पूर्णांक rhdr_cpu[18];
	पूर्णांक sdma_cpu[2];
	u64 dca_rcvhdr_ctrl[5]; /* B, C, D, E, F */
#पूर्ण_अगर
	काष्ठा qib_msix_entry *msix_entries;
	अचिन्हित दीर्घ *sendchkenable;
	अचिन्हित दीर्घ *sendgrhchk;
	अचिन्हित दीर्घ *sendibchk;
	u32 rcvavail_समयout[18];
	अक्षर emsgbuf[128]; /* क्रम device error पूर्णांकerrupt msg buffer */
पूर्ण;

/* Table of entries in "human readable" क्रमm Tx Emphasis. */
काष्ठा txdds_ent अणु
	u8 amp;
	u8 pre;
	u8 मुख्य;
	u8 post;
पूर्ण;

काष्ठा venकरोr_txdds_ent अणु
	u8 oui[QSFP_VOUI_LEN];
	u8 *partnum;
	काष्ठा txdds_ent sdr;
	काष्ठा txdds_ent ddr;
	काष्ठा txdds_ent qdr;
पूर्ण;

अटल व्योम ग_लिखो_tx_serdes_param(काष्ठा qib_pportdata *, काष्ठा txdds_ent *);

#घोषणा TXDDS_TABLE_SZ 16 /* number of entries per speed in onchip table */
#घोषणा TXDDS_EXTRA_SZ 18 /* number of extra tx settings entries */
#घोषणा TXDDS_MFG_SZ 2    /* number of mfg tx settings entries */
#घोषणा SERDES_CHANS 4 /* yes, it's obvious, but one less magic number */

#घोषणा H1_FORCE_VAL 8
#घोषणा H1_FORCE_QME 1 /*  may be overridden via setup_txselect() */
#घोषणा H1_FORCE_QMH 7 /*  may be overridden via setup_txselect() */

/* The अटल and dynamic रेजिस्टरs are paired, and the pairs indexed by spd */
#घोषणा krp_अटल_adapt_dis(spd) (KREG_IBPORT_IDX(ADAPT_DISABLE_STATIC_SDR) \
	+ ((spd) * 2))

#घोषणा QDR_DFE_DISABLE_DELAY 4000 /* msec after LINKUP */
#घोषणा QDR_STATIC_ADAPT_DOWN 0xf0f0f0f0ULL /* link करोwn, H1-H4 QDR adapts */
#घोषणा QDR_STATIC_ADAPT_DOWN_R1 0ULL /* r1 link करोwn, H1-H4 QDR adapts */
#घोषणा QDR_STATIC_ADAPT_INIT 0xffffffffffULL /* up, disable H0,H1-8, LE */
#घोषणा QDR_STATIC_ADAPT_INIT_R1 0xf0ffffffffULL /* r1 up, disable H0,H1-8 */

काष्ठा qib_chippport_specअगरic अणु
	u64 __iomem *kpregbase;
	u64 __iomem *cpregbase;
	u64 *portcntrs;
	काष्ठा qib_pportdata *ppd;
	रुको_queue_head_t स्वतःneg_रुको;
	काष्ठा delayed_work स्वतःneg_work;
	काष्ठा delayed_work ipg_work;
	काष्ठा समयr_list chase_समयr;
	/*
	 * these 5 fields are used to establish deltas क्रम IB symbol
	 * errors and linkrecovery errors.  They can be reported on
	 * some chips during link negotiation prior to INIT, and with
	 * DDR when faking DDR negotiations with non-IBTA चयनes.
	 * The chip counters are adjusted at driver unload अगर there is
	 * a non-zero delta.
	 */
	u64 ibdeltainprog;
	u64 ibsymdelta;
	u64 ibsymsnap;
	u64 iblnkerrdelta;
	u64 iblnkerrsnap;
	u64 iblnkकरोwnsnap;
	u64 iblnkकरोwndelta;
	u64 ibmalfdelta;
	u64 ibmalfsnap;
	u64 ibcctrl_a; /* krp_ibcctrl_a shaकरोw */
	u64 ibcctrl_b; /* krp_ibcctrl_b shaकरोw */
	अचिन्हित दीर्घ qdr_dfe_समय;
	अचिन्हित दीर्घ chase_end;
	u32 स्वतःneg_tries;
	u32 recovery_init;
	u32 qdr_dfe_on;
	u32 qdr_reक्रमce;
	/*
	 * Per-bay per-channel rcv QMH H1 values and Tx values क्रम QDR.
	 * entry zero is unused, to simplअगरy indexing
	 */
	u8 h1_val;
	u8 no_eep;  /* txselect table index to use अगर no qsfp info */
	u8 ipg_tries;
	u8 ibmalfusesnap;
	काष्ठा qib_qsfp_data qsfp_data;
	अक्षर epmsgbuf[192]; /* क्रम port error पूर्णांकerrupt msg buffer */
	अक्षर sdmamsgbuf[192]; /* क्रम per-port sdma error messages */
पूर्ण;

अटल काष्ठा अणु
	स्थिर अक्षर *name;
	irq_handler_t handler;
	पूर्णांक lsb;
	पूर्णांक port; /* 0 अगर not port-specअगरic, अन्यथा port # */
	पूर्णांक dca;
पूर्ण irq_table[] = अणु
	अणु "", qib_7322पूर्णांकr, -1, 0, 0 पूर्ण,
	अणु " (buf avail)", qib_7322bufavail,
		SYM_LSB(IntStatus, SendBufAvail), 0, 0पूर्ण,
	अणु " (sdma 0)", sdma_पूर्णांकr,
		SYM_LSB(IntStatus, SDmaInt_0), 1, 1 पूर्ण,
	अणु " (sdma 1)", sdma_पूर्णांकr,
		SYM_LSB(IntStatus, SDmaInt_1), 2, 1 पूर्ण,
	अणु " (sdmaI 0)", sdma_idle_पूर्णांकr,
		SYM_LSB(IntStatus, SDmaIdleInt_0), 1, 1पूर्ण,
	अणु " (sdmaI 1)", sdma_idle_पूर्णांकr,
		SYM_LSB(IntStatus, SDmaIdleInt_1), 2, 1पूर्ण,
	अणु " (sdmaP 0)", sdma_progress_पूर्णांकr,
		SYM_LSB(IntStatus, SDmaProgressInt_0), 1, 1 पूर्ण,
	अणु " (sdmaP 1)", sdma_progress_पूर्णांकr,
		SYM_LSB(IntStatus, SDmaProgressInt_1), 2, 1 पूर्ण,
	अणु " (sdmaC 0)", sdma_cleanup_पूर्णांकr,
		SYM_LSB(IntStatus, SDmaCleanupDone_0), 1, 0 पूर्ण,
	अणु " (sdmaC 1)", sdma_cleanup_पूर्णांकr,
		SYM_LSB(IntStatus, SDmaCleanupDone_1), 2 , 0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA

अटल स्थिर काष्ठा dca_reg_map अणु
	पूर्णांक     shaकरोw_inx;
	पूर्णांक     lsb;
	u64     mask;
	u16     regno;
पूर्ण dca_rcvhdr_reg_map[] = अणु
	अणु 0, SYM_LSB(DCACtrlB, RcvHdrq0DCAOPH),
	   ~SYM_MASK(DCACtrlB, RcvHdrq0DCAOPH) , KREG_IDX(DCACtrlB) पूर्ण,
	अणु 0, SYM_LSB(DCACtrlB, RcvHdrq1DCAOPH),
	   ~SYM_MASK(DCACtrlB, RcvHdrq1DCAOPH) , KREG_IDX(DCACtrlB) पूर्ण,
	अणु 0, SYM_LSB(DCACtrlB, RcvHdrq2DCAOPH),
	   ~SYM_MASK(DCACtrlB, RcvHdrq2DCAOPH) , KREG_IDX(DCACtrlB) पूर्ण,
	अणु 0, SYM_LSB(DCACtrlB, RcvHdrq3DCAOPH),
	   ~SYM_MASK(DCACtrlB, RcvHdrq3DCAOPH) , KREG_IDX(DCACtrlB) पूर्ण,
	अणु 1, SYM_LSB(DCACtrlC, RcvHdrq4DCAOPH),
	   ~SYM_MASK(DCACtrlC, RcvHdrq4DCAOPH) , KREG_IDX(DCACtrlC) पूर्ण,
	अणु 1, SYM_LSB(DCACtrlC, RcvHdrq5DCAOPH),
	   ~SYM_MASK(DCACtrlC, RcvHdrq5DCAOPH) , KREG_IDX(DCACtrlC) पूर्ण,
	अणु 1, SYM_LSB(DCACtrlC, RcvHdrq6DCAOPH),
	   ~SYM_MASK(DCACtrlC, RcvHdrq6DCAOPH) , KREG_IDX(DCACtrlC) पूर्ण,
	अणु 1, SYM_LSB(DCACtrlC, RcvHdrq7DCAOPH),
	   ~SYM_MASK(DCACtrlC, RcvHdrq7DCAOPH) , KREG_IDX(DCACtrlC) पूर्ण,
	अणु 2, SYM_LSB(DCACtrlD, RcvHdrq8DCAOPH),
	   ~SYM_MASK(DCACtrlD, RcvHdrq8DCAOPH) , KREG_IDX(DCACtrlD) पूर्ण,
	अणु 2, SYM_LSB(DCACtrlD, RcvHdrq9DCAOPH),
	   ~SYM_MASK(DCACtrlD, RcvHdrq9DCAOPH) , KREG_IDX(DCACtrlD) पूर्ण,
	अणु 2, SYM_LSB(DCACtrlD, RcvHdrq10DCAOPH),
	   ~SYM_MASK(DCACtrlD, RcvHdrq10DCAOPH) , KREG_IDX(DCACtrlD) पूर्ण,
	अणु 2, SYM_LSB(DCACtrlD, RcvHdrq11DCAOPH),
	   ~SYM_MASK(DCACtrlD, RcvHdrq11DCAOPH) , KREG_IDX(DCACtrlD) पूर्ण,
	अणु 3, SYM_LSB(DCACtrlE, RcvHdrq12DCAOPH),
	   ~SYM_MASK(DCACtrlE, RcvHdrq12DCAOPH) , KREG_IDX(DCACtrlE) पूर्ण,
	अणु 3, SYM_LSB(DCACtrlE, RcvHdrq13DCAOPH),
	   ~SYM_MASK(DCACtrlE, RcvHdrq13DCAOPH) , KREG_IDX(DCACtrlE) पूर्ण,
	अणु 3, SYM_LSB(DCACtrlE, RcvHdrq14DCAOPH),
	   ~SYM_MASK(DCACtrlE, RcvHdrq14DCAOPH) , KREG_IDX(DCACtrlE) पूर्ण,
	अणु 3, SYM_LSB(DCACtrlE, RcvHdrq15DCAOPH),
	   ~SYM_MASK(DCACtrlE, RcvHdrq15DCAOPH) , KREG_IDX(DCACtrlE) पूर्ण,
	अणु 4, SYM_LSB(DCACtrlF, RcvHdrq16DCAOPH),
	   ~SYM_MASK(DCACtrlF, RcvHdrq16DCAOPH) , KREG_IDX(DCACtrlF) पूर्ण,
	अणु 4, SYM_LSB(DCACtrlF, RcvHdrq17DCAOPH),
	   ~SYM_MASK(DCACtrlF, RcvHdrq17DCAOPH) , KREG_IDX(DCACtrlF) पूर्ण,
पूर्ण;
#पूर्ण_अगर

/* ibcctrl bits */
#घोषणा QLOGIC_IB_IBCC_LINKINITCMD_DISABLE 1
/* cycle through TS1/TS2 till OK */
#घोषणा QLOGIC_IB_IBCC_LINKINITCMD_POLL 2
/* रुको क्रम TS1, then go on */
#घोषणा QLOGIC_IB_IBCC_LINKINITCMD_SLEEP 3
#घोषणा QLOGIC_IB_IBCC_LINKINITCMD_SHIFT 16

#घोषणा QLOGIC_IB_IBCC_LINKCMD_DOWN 1           /* move to 0x11 */
#घोषणा QLOGIC_IB_IBCC_LINKCMD_ARMED 2          /* move to 0x21 */
#घोषणा QLOGIC_IB_IBCC_LINKCMD_ACTIVE 3 /* move to 0x31 */

#घोषणा BLOB_7322_IBCHG 0x101

अटल अंतरभूत व्योम qib_ग_लिखो_kreg(स्थिर काष्ठा qib_devdata *dd,
				  स्थिर u32 regno, u64 value);
अटल अंतरभूत u32 qib_पढ़ो_kreg32(स्थिर काष्ठा qib_devdata *, स्थिर u32);
अटल व्योम ग_लिखो_7322_initregs(काष्ठा qib_devdata *);
अटल व्योम ग_लिखो_7322_init_portregs(काष्ठा qib_pportdata *);
अटल व्योम setup_7322_link_recovery(काष्ठा qib_pportdata *, u32);
अटल व्योम check_7322_rxe_status(काष्ठा qib_pportdata *);
अटल u32 __iomem *qib_7322_माला_लोendbuf(काष्ठा qib_pportdata *, u64, u32 *);
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
अटल व्योम qib_setup_dca(काष्ठा qib_devdata *dd);
अटल व्योम setup_dca_notअगरier(काष्ठा qib_devdata *dd, पूर्णांक msixnum);
अटल व्योम reset_dca_notअगरier(काष्ठा qib_devdata *dd, पूर्णांक msixnum);
#पूर्ण_अगर

/**
 * qib_पढ़ो_ureg32 - पढ़ो 32-bit भवized per-context रेजिस्टर
 * @dd: device
 * @regno: रेजिस्टर number
 * @ctxt: context number
 *
 * Return the contents of a रेजिस्टर that is भवized to be per context.
 * Returns -1 on errors (not distinguishable from valid contents at
 * runसमय; we may add a separate error variable at some poपूर्णांक).
 */
अटल अंतरभूत u32 qib_पढ़ो_ureg32(स्थिर काष्ठा qib_devdata *dd,
				  क्रमागत qib_ureg regno, पूर्णांक ctxt)
अणु
	अगर (!dd->kregbase || !(dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोl(regno + (u64 __iomem *)(
		(dd->ureg_align * ctxt) + (dd->userbase ?
		 (अक्षर __iomem *)dd->userbase :
		 (अक्षर __iomem *)dd->kregbase + dd->uregbase)));
पूर्ण

/**
 * qib_ग_लिखो_ureg - ग_लिखो भवized per-context रेजिस्टर
 * @dd: device
 * @regno: रेजिस्टर number
 * @value: value
 * @ctxt: context
 *
 * Write the contents of a रेजिस्टर that is भवized to be per context.
 */
अटल अंतरभूत व्योम qib_ग_लिखो_ureg(स्थिर काष्ठा qib_devdata *dd,
				  क्रमागत qib_ureg regno, u64 value, पूर्णांक ctxt)
अणु
	u64 __iomem *ubase;

	अगर (dd->userbase)
		ubase = (u64 __iomem *)
			((अक्षर __iomem *) dd->userbase +
			 dd->ureg_align * ctxt);
	अन्यथा
		ubase = (u64 __iomem *)
			(dd->uregbase +
			 (अक्षर __iomem *) dd->kregbase +
			 dd->ureg_align * ctxt);

	अगर (dd->kregbase && (dd->flags & QIB_PRESENT))
		ग_लिखोq(value, &ubase[regno]);
पूर्ण

अटल अंतरभूत u32 qib_पढ़ो_kreg32(स्थिर काष्ठा qib_devdata *dd,
				  स्थिर u32 regno)
अणु
	अगर (!dd->kregbase || !(dd->flags & QIB_PRESENT))
		वापस -1;
	वापस पढ़ोl((u32 __iomem *) &dd->kregbase[regno]);
पूर्ण

अटल अंतरभूत u64 qib_पढ़ो_kreg64(स्थिर काष्ठा qib_devdata *dd,
				  स्थिर u32 regno)
अणु
	अगर (!dd->kregbase || !(dd->flags & QIB_PRESENT))
		वापस -1;
	वापस पढ़ोq(&dd->kregbase[regno]);
पूर्ण

अटल अंतरभूत व्योम qib_ग_लिखो_kreg(स्थिर काष्ठा qib_devdata *dd,
				  स्थिर u32 regno, u64 value)
अणु
	अगर (dd->kregbase && (dd->flags & QIB_PRESENT))
		ग_लिखोq(value, &dd->kregbase[regno]);
पूर्ण

/*
 * not many sanity checks क्रम the port-specअगरic kernel रेजिस्टर routines,
 * since they are only used when it's known to be safe.
*/
अटल अंतरभूत u64 qib_पढ़ो_kreg_port(स्थिर काष्ठा qib_pportdata *ppd,
				     स्थिर u16 regno)
अणु
	अगर (!ppd->cpspec->kpregbase || !(ppd->dd->flags & QIB_PRESENT))
		वापस 0ULL;
	वापस पढ़ोq(&ppd->cpspec->kpregbase[regno]);
पूर्ण

अटल अंतरभूत व्योम qib_ग_लिखो_kreg_port(स्थिर काष्ठा qib_pportdata *ppd,
				       स्थिर u16 regno, u64 value)
अणु
	अगर (ppd->cpspec && ppd->dd && ppd->cpspec->kpregbase &&
	    (ppd->dd->flags & QIB_PRESENT))
		ग_लिखोq(value, &ppd->cpspec->kpregbase[regno]);
पूर्ण

/**
 * qib_ग_लिखो_kreg_ctxt - ग_लिखो a device's per-ctxt 64-bit kernel रेजिस्टर
 * @dd: the qlogic_ib device
 * @regno: the रेजिस्टर number to ग_लिखो
 * @ctxt: the context containing the रेजिस्टर
 * @value: the value to ग_लिखो
 */
अटल अंतरभूत व्योम qib_ग_लिखो_kreg_ctxt(स्थिर काष्ठा qib_devdata *dd,
				       स्थिर u16 regno, अचिन्हित ctxt,
				       u64 value)
अणु
	qib_ग_लिखो_kreg(dd, regno + ctxt, value);
पूर्ण

अटल अंतरभूत u64 पढ़ो_7322_creg(स्थिर काष्ठा qib_devdata *dd, u16 regno)
अणु
	अगर (!dd->cspec->cregbase || !(dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोq(&dd->cspec->cregbase[regno]);


पूर्ण

अटल अंतरभूत u32 पढ़ो_7322_creg32(स्थिर काष्ठा qib_devdata *dd, u16 regno)
अणु
	अगर (!dd->cspec->cregbase || !(dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोl(&dd->cspec->cregbase[regno]);


पूर्ण

अटल अंतरभूत व्योम ग_लिखो_7322_creg_port(स्थिर काष्ठा qib_pportdata *ppd,
					u16 regno, u64 value)
अणु
	अगर (ppd->cpspec && ppd->cpspec->cpregbase &&
	    (ppd->dd->flags & QIB_PRESENT))
		ग_लिखोq(value, &ppd->cpspec->cpregbase[regno]);
पूर्ण

अटल अंतरभूत u64 पढ़ो_7322_creg_port(स्थिर काष्ठा qib_pportdata *ppd,
				      u16 regno)
अणु
	अगर (!ppd->cpspec || !ppd->cpspec->cpregbase ||
	    !(ppd->dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोq(&ppd->cpspec->cpregbase[regno]);
पूर्ण

अटल अंतरभूत u32 पढ़ो_7322_creg32_port(स्थिर काष्ठा qib_pportdata *ppd,
					u16 regno)
अणु
	अगर (!ppd->cpspec || !ppd->cpspec->cpregbase ||
	    !(ppd->dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोl(&ppd->cpspec->cpregbase[regno]);
पूर्ण

/* bits in Control रेजिस्टर */
#घोषणा QLOGIC_IB_C_RESET SYM_MASK(Control, SyncReset)
#घोषणा QLOGIC_IB_C_SDMAFETCHPRIOEN SYM_MASK(Control, SDmaDescFetchPriorityEn)

/* bits in general पूर्णांकerrupt regs */
#घोषणा QIB_I_RCVURG_LSB SYM_LSB(IntMask, RcvUrg0IntMask)
#घोषणा QIB_I_RCVURG_RMASK MASK_ACROSS(0, 17)
#घोषणा QIB_I_RCVURG_MASK (QIB_I_RCVURG_RMASK << QIB_I_RCVURG_LSB)
#घोषणा QIB_I_RCVAVAIL_LSB SYM_LSB(IntMask, RcvAvail0IntMask)
#घोषणा QIB_I_RCVAVAIL_RMASK MASK_ACROSS(0, 17)
#घोषणा QIB_I_RCVAVAIL_MASK (QIB_I_RCVAVAIL_RMASK << QIB_I_RCVAVAIL_LSB)
#घोषणा QIB_I_C_ERROR INT_MASK(Err)

#घोषणा QIB_I_SPIOSENT (INT_MASK_P(SendDone, 0) | INT_MASK_P(SendDone, 1))
#घोषणा QIB_I_SPIOBUFAVAIL INT_MASK(SendBufAvail)
#घोषणा QIB_I_GPIO INT_MASK(AssertGPIO)
#घोषणा QIB_I_P_SDMAINT(pidx) \
	(INT_MASK_P(SDma, pidx) | INT_MASK_P(SDmaIdle, pidx) | \
	 INT_MASK_P(SDmaProgress, pidx) | \
	 INT_MASK_PM(SDmaCleanupDone, pidx))

/* Interrupt bits that are "per port" */
#घोषणा QIB_I_P_BITSEXTANT(pidx) \
	(INT_MASK_P(Err, pidx) | INT_MASK_P(SendDone, pidx) | \
	INT_MASK_P(SDma, pidx) | INT_MASK_P(SDmaIdle, pidx) | \
	INT_MASK_P(SDmaProgress, pidx) | \
	INT_MASK_PM(SDmaCleanupDone, pidx))

/* Interrupt bits that are common to a device */
/* currently unused: QIB_I_SPIOSENT */
#घोषणा QIB_I_C_BITSEXTANT \
	(QIB_I_RCVURG_MASK | QIB_I_RCVAVAIL_MASK | \
	QIB_I_SPIOSENT | \
	QIB_I_C_ERROR | QIB_I_SPIOBUFAVAIL | QIB_I_GPIO)

#घोषणा QIB_I_BITSEXTANT (QIB_I_C_BITSEXTANT | \
	QIB_I_P_BITSEXTANT(0) | QIB_I_P_BITSEXTANT(1))

/*
 * Error bits that are "per port".
 */
#घोषणा QIB_E_P_IBSTATUSCHANGED ERR_MASK_N(IBStatusChanged)
#घोषणा QIB_E_P_SHDR ERR_MASK_N(SHeadersErr)
#घोषणा QIB_E_P_VL15_BUF_MISUSE ERR_MASK_N(VL15BufMisuseErr)
#घोषणा QIB_E_P_SND_BUF_MISUSE ERR_MASK_N(SendBufMisuseErr)
#घोषणा QIB_E_P_SUNSUPVL ERR_MASK_N(SendUnsupportedVLErr)
#घोषणा QIB_E_P_SUNEXP_PKTNUM ERR_MASK_N(SendUnexpectedPktNumErr)
#घोषणा QIB_E_P_SDROP_DATA ERR_MASK_N(SendDroppedDataPktErr)
#घोषणा QIB_E_P_SDROP_SMP ERR_MASK_N(SendDroppedSmpPktErr)
#घोषणा QIB_E_P_SPKTLEN ERR_MASK_N(SendPktLenErr)
#घोषणा QIB_E_P_SUNDERRUN ERR_MASK_N(SendUnderRunErr)
#घोषणा QIB_E_P_SMAXPKTLEN ERR_MASK_N(SendMaxPktLenErr)
#घोषणा QIB_E_P_SMINPKTLEN ERR_MASK_N(SendMinPktLenErr)
#घोषणा QIB_E_P_RIBLOSTLINK ERR_MASK_N(RcvIBLostLinkErr)
#घोषणा QIB_E_P_RHDR ERR_MASK_N(RcvHdrErr)
#घोषणा QIB_E_P_RHDRLEN ERR_MASK_N(RcvHdrLenErr)
#घोषणा QIB_E_P_RBADTID ERR_MASK_N(RcvBadTidErr)
#घोषणा QIB_E_P_RBADVERSION ERR_MASK_N(RcvBadVersionErr)
#घोषणा QIB_E_P_RIBFLOW ERR_MASK_N(RcvIBFlowErr)
#घोषणा QIB_E_P_REBP ERR_MASK_N(RcvEBPErr)
#घोषणा QIB_E_P_RUNSUPVL ERR_MASK_N(RcvUnsupportedVLErr)
#घोषणा QIB_E_P_RUNEXPCHAR ERR_MASK_N(RcvUnexpectedCharErr)
#घोषणा QIB_E_P_RSHORTPKTLEN ERR_MASK_N(RcvShortPktLenErr)
#घोषणा QIB_E_P_RLONGPKTLEN ERR_MASK_N(RcvLongPktLenErr)
#घोषणा QIB_E_P_RMAXPKTLEN ERR_MASK_N(RcvMaxPktLenErr)
#घोषणा QIB_E_P_RMINPKTLEN ERR_MASK_N(RcvMinPktLenErr)
#घोषणा QIB_E_P_RICRC ERR_MASK_N(RcvICRCErr)
#घोषणा QIB_E_P_RVCRC ERR_MASK_N(RcvVCRCErr)
#घोषणा QIB_E_P_RFORMATERR ERR_MASK_N(RcvFormatErr)

#घोषणा QIB_E_P_SDMA1STDESC ERR_MASK_N(SDma1stDescErr)
#घोषणा QIB_E_P_SDMABASE ERR_MASK_N(SDmaBaseErr)
#घोषणा QIB_E_P_SDMADESCADDRMISALIGN ERR_MASK_N(SDmaDescAddrMisalignErr)
#घोषणा QIB_E_P_SDMADWEN ERR_MASK_N(SDmaDwEnErr)
#घोषणा QIB_E_P_SDMAGENMISMATCH ERR_MASK_N(SDmaGenMismatchErr)
#घोषणा QIB_E_P_SDMAHALT ERR_MASK_N(SDmaHaltErr)
#घोषणा QIB_E_P_SDMAMISSINGDW ERR_MASK_N(SDmaMissingDwErr)
#घोषणा QIB_E_P_SDMAOUTOFBOUND ERR_MASK_N(SDmaOutOfBoundErr)
#घोषणा QIB_E_P_SDMARPYTAG ERR_MASK_N(SDmaRpyTagErr)
#घोषणा QIB_E_P_SDMATAILOUTOFBOUND ERR_MASK_N(SDmaTailOutOfBoundErr)
#घोषणा QIB_E_P_SDMAUNEXPDATA ERR_MASK_N(SDmaUnexpDataErr)

/* Error bits that are common to a device */
#घोषणा QIB_E_RESET ERR_MASK(ResetNegated)
#घोषणा QIB_E_HARDWARE ERR_MASK(HardwareErr)
#घोषणा QIB_E_INVALIDADDR ERR_MASK(InvalidAddrErr)


/*
 * Per chip (rather than per-port) errors.  Most either करो
 * nothing but trigger a prपूर्णांक (because they self-recover, or
 * always occur in tandem with other errors that handle the
 * issue), or because they indicate errors with no recovery,
 * but we want to know that they happened.
 */
#घोषणा QIB_E_SBUF_VL15_MISUSE ERR_MASK(SBufVL15MisUseErr)
#घोषणा QIB_E_BADEEP ERR_MASK(InvalidEEPCmd)
#घोषणा QIB_E_VLMISMATCH ERR_MASK(SendVLMismatchErr)
#घोषणा QIB_E_ARMLAUNCH ERR_MASK(SendArmLaunchErr)
#घोषणा QIB_E_SPCLTRIG ERR_MASK(SendSpecialTriggerErr)
#घोषणा QIB_E_RRCVHDRFULL ERR_MASK(RcvHdrFullErr)
#घोषणा QIB_E_RRCVEGRFULL ERR_MASK(RcvEgrFullErr)
#घोषणा QIB_E_RCVCTXTSHARE ERR_MASK(RcvContextShareErr)

/* SDMA chip errors (not per port)
 * QIB_E_SDMA_BUF_DUP needs no special handling, because we will also get
 * the SDMAHALT error immediately, so we just prपूर्णांक the dup error via the
 * E_AUTO mechanism.  This is true of most of the per-port fatal errors
 * as well, but since this is port-independent, by definition, it's
 * handled a bit dअगरferently.  SDMA_VL15 and SDMA_WRONG_PORT are per
 * packet send errors, and so are handled in the same manner as other
 * per-packet errors.
 */
#घोषणा QIB_E_SDMA_VL15 ERR_MASK(SDmaVL15Err)
#घोषणा QIB_E_SDMA_WRONG_PORT ERR_MASK(SDmaWrongPortErr)
#घोषणा QIB_E_SDMA_BUF_DUP ERR_MASK(SDmaBufMaskDuplicateErr)

/*
 * Below functionally equivalent to legacy QLOGIC_IB_E_PKTERRS
 * it is used to prपूर्णांक "common" packet errors.
 */
#घोषणा QIB_E_P_PKTERRS (QIB_E_P_SPKTLEN |\
	QIB_E_P_SDROP_DATA | QIB_E_P_RVCRC |\
	QIB_E_P_RICRC | QIB_E_P_RSHORTPKTLEN |\
	QIB_E_P_VL15_BUF_MISUSE | QIB_E_P_SHDR | \
	QIB_E_P_REBP)

/* Error Bits that Packet-related (Receive, per-port) */
#घोषणा QIB_E_P_RPKTERRS (\
	QIB_E_P_RHDRLEN | QIB_E_P_RBADTID | \
	QIB_E_P_RBADVERSION | QIB_E_P_RHDR | \
	QIB_E_P_RLONGPKTLEN | QIB_E_P_RSHORTPKTLEN |\
	QIB_E_P_RMAXPKTLEN | QIB_E_P_RMINPKTLEN | \
	QIB_E_P_RFORMATERR | QIB_E_P_RUNSUPVL | \
	QIB_E_P_RUNEXPCHAR | QIB_E_P_RIBFLOW | QIB_E_P_REBP)

/*
 * Error bits that are Send-related (per port)
 * (ARMLAUNCH excluded from E_SPKTERRS because it माला_लो special handling).
 * All of these potentially need to have a buffer disarmed
 */
#घोषणा QIB_E_P_SPKTERRS (\
	QIB_E_P_SUNEXP_PKTNUM |\
	QIB_E_P_SDROP_DATA | QIB_E_P_SDROP_SMP |\
	QIB_E_P_SMAXPKTLEN |\
	QIB_E_P_VL15_BUF_MISUSE | QIB_E_P_SHDR | \
	QIB_E_P_SMINPKTLEN | QIB_E_P_SPKTLEN | \
	QIB_E_P_SND_BUF_MISUSE | QIB_E_P_SUNSUPVL)

#घोषणा QIB_E_SPKTERRS ( \
		QIB_E_SBUF_VL15_MISUSE | QIB_E_VLMISMATCH | \
		ERR_MASK_N(SendUnsupportedVLErr) |			\
		QIB_E_SPCLTRIG | QIB_E_SDMA_VL15 | QIB_E_SDMA_WRONG_PORT)

#घोषणा QIB_E_P_SDMAERRS ( \
	QIB_E_P_SDMAHALT | \
	QIB_E_P_SDMADESCADDRMISALIGN | \
	QIB_E_P_SDMAUNEXPDATA | \
	QIB_E_P_SDMAMISSINGDW | \
	QIB_E_P_SDMADWEN | \
	QIB_E_P_SDMARPYTAG | \
	QIB_E_P_SDMA1STDESC | \
	QIB_E_P_SDMABASE | \
	QIB_E_P_SDMATAILOUTOFBOUND | \
	QIB_E_P_SDMAOUTOFBOUND | \
	QIB_E_P_SDMAGENMISMATCH)

/*
 * This sets some bits more than once, but makes it more obvious which
 * bits are not handled under other categories, and the repeat definition
 * is not a problem.
 */
#घोषणा QIB_E_P_BITSEXTANT ( \
	QIB_E_P_SPKTERRS | QIB_E_P_PKTERRS | QIB_E_P_RPKTERRS | \
	QIB_E_P_RIBLOSTLINK | QIB_E_P_IBSTATUSCHANGED | \
	QIB_E_P_SND_BUF_MISUSE | QIB_E_P_SUNDERRUN | \
	QIB_E_P_SHDR | QIB_E_P_VL15_BUF_MISUSE | QIB_E_P_SDMAERRS \
	)

/*
 * These are errors that can occur when the link
 * changes state जबतक a packet is being sent or received.  This करोesn't
 * cover things like EBP or VCRC that can be the result of a sending
 * having the link change state, so we receive a "known bad" packet.
 * All of these are "per port", so नामd:
 */
#घोषणा QIB_E_P_LINK_PKTERRS (\
	QIB_E_P_SDROP_DATA | QIB_E_P_SDROP_SMP |\
	QIB_E_P_SMINPKTLEN | QIB_E_P_SPKTLEN |\
	QIB_E_P_RSHORTPKTLEN | QIB_E_P_RMINPKTLEN |\
	QIB_E_P_RUNEXPCHAR)

/*
 * This sets some bits more than once, but makes it more obvious which
 * bits are not handled under other categories (such as QIB_E_SPKTERRS),
 * and the repeat definition is not a problem.
 */
#घोषणा QIB_E_C_BITSEXTANT (\
	QIB_E_HARDWARE | QIB_E_INVALIDADDR | QIB_E_BADEEP |\
	QIB_E_ARMLAUNCH | QIB_E_VLMISMATCH | QIB_E_RRCVHDRFULL |\
	QIB_E_RRCVEGRFULL | QIB_E_RESET | QIB_E_SBUF_VL15_MISUSE)

/* Likewise Neuter E_SPKT_ERRS_IGNORE */
#घोषणा E_SPKT_ERRS_IGNORE 0

#घोषणा QIB_EXTS_MEMBIST_DISABLED \
	SYM_MASK(EXTStatus, MemBISTDisabled)
#घोषणा QIB_EXTS_MEMBIST_ENDTEST \
	SYM_MASK(EXTStatus, MemBISTEndTest)

#घोषणा QIB_E_SPIOARMLAUNCH \
	ERR_MASK(SendArmLaunchErr)

#घोषणा IBA7322_IBCC_LINKINITCMD_MASK SYM_RMASK(IBCCtrlA_0, LinkInitCmd)
#घोषणा IBA7322_IBCC_LINKCMD_SHIFT SYM_LSB(IBCCtrlA_0, LinkCmd)

/*
 * IBTA_1_2 is set when multiple speeds are enabled (normal),
 * and also अगर क्रमced QDR (only QDR enabled).  It's enabled क्रम the
 * क्रमced QDR हाल so that scrambling will be enabled by the TS3
 * exchange, when supported by both sides of the link.
 */
#घोषणा IBA7322_IBC_IBTA_1_2_MASK SYM_MASK(IBCCtrlB_0, IB_ENHANCED_MODE)
#घोषणा IBA7322_IBC_MAX_SPEED_MASK SYM_MASK(IBCCtrlB_0, SD_SPEED)
#घोषणा IBA7322_IBC_SPEED_QDR SYM_MASK(IBCCtrlB_0, SD_SPEED_QDR)
#घोषणा IBA7322_IBC_SPEED_DDR SYM_MASK(IBCCtrlB_0, SD_SPEED_DDR)
#घोषणा IBA7322_IBC_SPEED_SDR SYM_MASK(IBCCtrlB_0, SD_SPEED_SDR)
#घोषणा IBA7322_IBC_SPEED_MASK (SYM_MASK(IBCCtrlB_0, SD_SPEED_SDR) | \
	SYM_MASK(IBCCtrlB_0, SD_SPEED_DDR) | SYM_MASK(IBCCtrlB_0, SD_SPEED_QDR))
#घोषणा IBA7322_IBC_SPEED_LSB SYM_LSB(IBCCtrlB_0, SD_SPEED_SDR)

#घोषणा IBA7322_LEDBLINK_OFF_SHIFT SYM_LSB(RcvPktLEDCnt_0, OFFperiod)
#घोषणा IBA7322_LEDBLINK_ON_SHIFT SYM_LSB(RcvPktLEDCnt_0, ONperiod)

#घोषणा IBA7322_IBC_WIDTH_AUTONEG SYM_MASK(IBCCtrlB_0, IB_NUM_CHANNELS)
#घोषणा IBA7322_IBC_WIDTH_4X_ONLY (1<<SYM_LSB(IBCCtrlB_0, IB_NUM_CHANNELS))
#घोषणा IBA7322_IBC_WIDTH_1X_ONLY (0<<SYM_LSB(IBCCtrlB_0, IB_NUM_CHANNELS))

#घोषणा IBA7322_IBC_RXPOL_MASK SYM_MASK(IBCCtrlB_0, IB_POLARITY_REV_SUPP)
#घोषणा IBA7322_IBC_RXPOL_LSB SYM_LSB(IBCCtrlB_0, IB_POLARITY_REV_SUPP)
#घोषणा IBA7322_IBC_HRTBT_MASK (SYM_MASK(IBCCtrlB_0, HRTBT_AUTO) | \
	SYM_MASK(IBCCtrlB_0, HRTBT_ENB))
#घोषणा IBA7322_IBC_HRTBT_RMASK (IBA7322_IBC_HRTBT_MASK >> \
	SYM_LSB(IBCCtrlB_0, HRTBT_ENB))
#घोषणा IBA7322_IBC_HRTBT_LSB SYM_LSB(IBCCtrlB_0, HRTBT_ENB)

#घोषणा IBA7322_REसूचीECT_VEC_PER_REG 12

#घोषणा IBA7322_SENDCHK_PKEY SYM_MASK(SendCheckControl_0, PKey_En)
#घोषणा IBA7322_SENDCHK_BTHQP SYM_MASK(SendCheckControl_0, BTHQP_En)
#घोषणा IBA7322_SENDCHK_SLID SYM_MASK(SendCheckControl_0, SLID_En)
#घोषणा IBA7322_SENDCHK_RAW_IPV6 SYM_MASK(SendCheckControl_0, RawIPV6_En)
#घोषणा IBA7322_SENDCHK_MINSZ SYM_MASK(SendCheckControl_0, PacketTooSmall_En)

#घोषणा AUTONEG_TRIES 3 /* sequential retries to negotiate DDR */

#घोषणा HWE_AUTO(fldname) अणु .mask = SYM_MASK(HwErrMask, fldname##Mask), \
	.msg = #fldname , .sz = माप(#fldname) पूर्ण
#घोषणा HWE_AUTO_P(fldname, port) अणु .mask = SYM_MASK(HwErrMask, \
	fldname##Mask##_##port), .msg = #fldname , .sz = माप(#fldname) पूर्ण
अटल स्थिर काष्ठा qib_hwerror_msgs qib_7322_hwerror_msgs[] = अणु
	HWE_AUTO_P(IBSerdesPClkNotDetect, 1),
	HWE_AUTO_P(IBSerdesPClkNotDetect, 0),
	HWE_AUTO(PCIESerdesPClkNotDetect),
	HWE_AUTO(PowerOnBISTFailed),
	HWE_AUTO(TempsenseTholdReached),
	HWE_AUTO(MemoryErr),
	HWE_AUTO(PCIeBusParityErr),
	HWE_AUTO(PcieCplTimeout),
	HWE_AUTO(PciePoisonedTLP),
	HWE_AUTO_P(SDmaMemReadErr, 1),
	HWE_AUTO_P(SDmaMemReadErr, 0),
	HWE_AUTO_P(IBCBusFromSPCParityErr, 1),
	HWE_AUTO_P(IBCBusToSPCParityErr, 1),
	HWE_AUTO_P(IBCBusFromSPCParityErr, 0),
	HWE_AUTO(statusValidNoEop),
	HWE_AUTO(LATriggered),
	अणु .mask = 0, .sz = 0 पूर्ण
पूर्ण;

#घोषणा E_AUTO(fldname) अणु .mask = SYM_MASK(ErrMask, fldname##Mask), \
	.msg = #fldname, .sz = माप(#fldname) पूर्ण
#घोषणा E_P_AUTO(fldname) अणु .mask = SYM_MASK(ErrMask_0, fldname##Mask), \
	.msg = #fldname, .sz = माप(#fldname) पूर्ण
अटल स्थिर काष्ठा qib_hwerror_msgs qib_7322error_msgs[] = अणु
	E_AUTO(RcvEgrFullErr),
	E_AUTO(RcvHdrFullErr),
	E_AUTO(ResetNegated),
	E_AUTO(HardwareErr),
	E_AUTO(InvalidAddrErr),
	E_AUTO(SDmaVL15Err),
	E_AUTO(SBufVL15MisUseErr),
	E_AUTO(InvalidEEPCmd),
	E_AUTO(RcvContextShareErr),
	E_AUTO(SendVLMismatchErr),
	E_AUTO(SendArmLaunchErr),
	E_AUTO(SendSpecialTriggerErr),
	E_AUTO(SDmaWrongPortErr),
	E_AUTO(SDmaBufMaskDuplicateErr),
	अणु .mask = 0, .sz = 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा  qib_hwerror_msgs qib_7322p_error_msgs[] = अणु
	E_P_AUTO(IBStatusChanged),
	E_P_AUTO(SHeadersErr),
	E_P_AUTO(VL15BufMisuseErr),
	/*
	 * SDmaHaltErr is not really an error, make it clearer;
	 */
	अणु.mask = SYM_MASK(ErrMask_0, SDmaHaltErrMask), .msg = "SDmaHalted",
		.sz = 11पूर्ण,
	E_P_AUTO(SDmaDescAddrMisalignErr),
	E_P_AUTO(SDmaUnexpDataErr),
	E_P_AUTO(SDmaMissingDwErr),
	E_P_AUTO(SDmaDwEnErr),
	E_P_AUTO(SDmaRpyTagErr),
	E_P_AUTO(SDma1stDescErr),
	E_P_AUTO(SDmaBaseErr),
	E_P_AUTO(SDmaTailOutOfBoundErr),
	E_P_AUTO(SDmaOutOfBoundErr),
	E_P_AUTO(SDmaGenMismatchErr),
	E_P_AUTO(SendBufMisuseErr),
	E_P_AUTO(SendUnsupportedVLErr),
	E_P_AUTO(SendUnexpectedPktNumErr),
	E_P_AUTO(SendDroppedDataPktErr),
	E_P_AUTO(SendDroppedSmpPktErr),
	E_P_AUTO(SendPktLenErr),
	E_P_AUTO(SendUnderRunErr),
	E_P_AUTO(SendMaxPktLenErr),
	E_P_AUTO(SendMinPktLenErr),
	E_P_AUTO(RcvIBLostLinkErr),
	E_P_AUTO(RcvHdrErr),
	E_P_AUTO(RcvHdrLenErr),
	E_P_AUTO(RcvBadTidErr),
	E_P_AUTO(RcvBadVersionErr),
	E_P_AUTO(RcvIBFlowErr),
	E_P_AUTO(RcvEBPErr),
	E_P_AUTO(RcvUnsupportedVLErr),
	E_P_AUTO(RcvUnexpectedCharErr),
	E_P_AUTO(RcvShortPktLenErr),
	E_P_AUTO(RcvLongPktLenErr),
	E_P_AUTO(RcvMaxPktLenErr),
	E_P_AUTO(RcvMinPktLenErr),
	E_P_AUTO(RcvICRCErr),
	E_P_AUTO(RcvVCRCErr),
	E_P_AUTO(RcvFormatErr),
	अणु .mask = 0, .sz = 0 पूर्ण
पूर्ण;

/*
 * Below generates "auto-message" क्रम पूर्णांकerrupts not specअगरic to any port or
 * context
 */
#घोषणा INTR_AUTO(fldname) अणु .mask = SYM_MASK(IntMask, fldname##Mask), \
	.msg = #fldname, .sz = माप(#fldname) पूर्ण
/* Below generates "auto-message" क्रम पूर्णांकerrupts specअगरic to a port */
#घोषणा INTR_AUTO_P(fldname) अणु .mask = MASK_ACROSS(\
	SYM_LSB(IntMask, fldname##Mask##_0), \
	SYM_LSB(IntMask, fldname##Mask##_1)), \
	.msg = #fldname "_P", .sz = माप(#fldname "_P") पूर्ण
/* For some reason, the SerDesTrimDone bits are reversed */
#घोषणा INTR_AUTO_PI(fldname) अणु .mask = MASK_ACROSS(\
	SYM_LSB(IntMask, fldname##Mask##_1), \
	SYM_LSB(IntMask, fldname##Mask##_0)), \
	.msg = #fldname "_P", .sz = माप(#fldname "_P") पूर्ण
/*
 * Below generates "auto-message" क्रम पूर्णांकerrupts specअगरic to a context,
 * with ctxt-number appended
 */
#घोषणा INTR_AUTO_C(fldname) अणु .mask = MASK_ACROSS(\
	SYM_LSB(IntMask, fldname##0IntMask), \
	SYM_LSB(IntMask, fldname##17IntMask)), \
	.msg = #fldname "_C", .sz = माप(#fldname "_C") पूर्ण

#घोषणा TXSYMPTOM_AUTO_P(fldname) \
	अणु .mask = SYM_MASK(SendHdrErrSymptom_0, fldname), \
	.msg = #fldname, .sz = माप(#fldname) पूर्ण
अटल स्थिर काष्ठा  qib_hwerror_msgs hdrchk_msgs[] = अणु
	TXSYMPTOM_AUTO_P(NonKeyPacket),
	TXSYMPTOM_AUTO_P(GRHFail),
	TXSYMPTOM_AUTO_P(PkeyFail),
	TXSYMPTOM_AUTO_P(QPFail),
	TXSYMPTOM_AUTO_P(SLIDFail),
	TXSYMPTOM_AUTO_P(RawIPV6),
	TXSYMPTOM_AUTO_P(PacketTooSmall),
	अणु .mask = 0, .sz = 0 पूर्ण
पूर्ण;

#घोषणा IBA7322_HDRHEAD_PKTINT_SHIFT 32 /* पूर्णांकerrupt cnt in upper 32 bits */

/*
 * Called when we might have an error that is specअगरic to a particular
 * PIO buffer, and may need to cancel that buffer, so it can be re-used,
 * because we करोn't need to क्रमce the update of pioavail
 */
अटल व्योम qib_disarm_7322_senderrbufs(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u32 i;
	पूर्णांक any;
	u32 piobcnt = dd->piobcnt2k + dd->piobcnt4k + NUM_VL15_BUFS;
	u32 regcnt = (piobcnt + BITS_PER_LONG - 1) / BITS_PER_LONG;
	अचिन्हित दीर्घ sbuf[4];

	/*
	 * It's possible that sendbuffererror could have bits set; might
	 * have alपढ़ोy करोne this as a result of hardware error handling.
	 */
	any = 0;
	क्रम (i = 0; i < regcnt; ++i) अणु
		sbuf[i] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror + i);
		अगर (sbuf[i]) अणु
			any = 1;
			qib_ग_लिखो_kreg(dd, kr_sendbuffererror + i, sbuf[i]);
		पूर्ण
	पूर्ण

	अगर (any)
		qib_disarm_piobufs_set(dd, sbuf, piobcnt);
पूर्ण

/* No txe_recover yet, अगर ever */

/* No decode__errors yet */
अटल व्योम err_decode(अक्षर *msg, माप_प्रकार len, u64 errs,
		       स्थिर काष्ठा qib_hwerror_msgs *msp)
अणु
	u64 these, lmask;
	पूर्णांक took, multi, n = 0;

	जबतक (errs && msp && msp->mask) अणु
		multi = (msp->mask & (msp->mask - 1));
		जबतक (errs & msp->mask) अणु
			these = (errs & msp->mask);
			lmask = (these & (these - 1)) ^ these;
			अगर (len) अणु
				अगर (n++) अणु
					/* separate the strings */
					*msg++ = ',';
					len--;
				पूर्ण
				/* msp->sz counts the nul */
				took = min_t(माप_प्रकार, msp->sz - (माप_प्रकार)1, len);
				स_नकल(msg,  msp->msg, took);
				len -= took;
				msg += took;
				अगर (len)
					*msg = '\0';
			पूर्ण
			errs &= ~lmask;
			अगर (len && multi) अणु
				/* More than one bit this mask */
				पूर्णांक idx = -1;

				जबतक (lmask & msp->mask) अणु
					++idx;
					lmask >>= 1;
				पूर्ण
				took = scnम_लिखो(msg, len, "_%d", idx);
				len -= took;
				msg += took;
			पूर्ण
		पूर्ण
		++msp;
	पूर्ण
	/* If some bits are left, show in hex. */
	अगर (len && errs)
		snम_लिखो(msg, len, "%sMORE:%llX", n ? "," : "",
			(अचिन्हित दीर्घ दीर्घ) errs);
पूर्ण

/* only called अगर r1 set */
अटल व्योम flush_fअगरo(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u32 __iomem *piobuf;
	u32 bufn;
	u32 *hdr;
	u64 pbc;
	स्थिर अचिन्हित hdrwords = 7;
	अटल काष्ठा ib_header ibhdr = अणु
		.lrh[0] = cpu_to_be16(0xF000 | QIB_LRH_BTH),
		.lrh[1] = IB_LID_PERMISSIVE,
		.lrh[2] = cpu_to_be16(hdrwords + SIZE_OF_CRC),
		.lrh[3] = IB_LID_PERMISSIVE,
		.u.oth.bth[0] = cpu_to_be32(
			(IB_OPCODE_UD_SEND_ONLY << 24) | QIB_DEFAULT_P_KEY),
		.u.oth.bth[1] = cpu_to_be32(0),
		.u.oth.bth[2] = cpu_to_be32(0),
		.u.oth.u.ud.deth[0] = cpu_to_be32(0),
		.u.oth.u.ud.deth[1] = cpu_to_be32(0),
	पूर्ण;

	/*
	 * Send a dummy VL15 packet to flush the launch FIFO.
	 * This will not actually be sent since the TxeBypassIbc bit is set.
	 */
	pbc = PBC_7322_VL15_SEND |
		(((u64)ppd->hw_pidx) << (PBC_PORT_SEL_LSB + 32)) |
		(hdrwords + SIZE_OF_CRC);
	piobuf = qib_7322_माला_लोendbuf(ppd, pbc, &bufn);
	अगर (!piobuf)
		वापस;
	ग_लिखोq(pbc, piobuf);
	hdr = (u32 *) &ibhdr;
	अगर (dd->flags & QIB_PIO_FLUSH_WC) अणु
		qib_flush_wc();
		qib_pio_copy(piobuf + 2, hdr, hdrwords - 1);
		qib_flush_wc();
		__raw_ग_लिखोl(hdr[hdrwords - 1], piobuf + hdrwords + 1);
		qib_flush_wc();
	पूर्ण अन्यथा
		qib_pio_copy(piobuf + 2, hdr, hdrwords);
	qib_sendbuf_करोne(dd, bufn);
पूर्ण

/*
 * This is called with पूर्णांकerrupts disabled and sdma_lock held.
 */
अटल व्योम qib_7322_sdma_sendctrl(काष्ठा qib_pportdata *ppd, अचिन्हित op)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 set_sendctrl = 0;
	u64 clr_sendctrl = 0;

	अगर (op & QIB_SDMA_SENDCTRL_OP_ENABLE)
		set_sendctrl |= SYM_MASK(SendCtrl_0, SDmaEnable);
	अन्यथा
		clr_sendctrl |= SYM_MASK(SendCtrl_0, SDmaEnable);

	अगर (op & QIB_SDMA_SENDCTRL_OP_INTENABLE)
		set_sendctrl |= SYM_MASK(SendCtrl_0, SDmaIntEnable);
	अन्यथा
		clr_sendctrl |= SYM_MASK(SendCtrl_0, SDmaIntEnable);

	अगर (op & QIB_SDMA_SENDCTRL_OP_HALT)
		set_sendctrl |= SYM_MASK(SendCtrl_0, SDmaHalt);
	अन्यथा
		clr_sendctrl |= SYM_MASK(SendCtrl_0, SDmaHalt);

	अगर (op & QIB_SDMA_SENDCTRL_OP_DRAIN)
		set_sendctrl |= SYM_MASK(SendCtrl_0, TxeBypassIbc) |
				SYM_MASK(SendCtrl_0, TxeAbortIbc) |
				SYM_MASK(SendCtrl_0, TxeDrainRmFअगरo);
	अन्यथा
		clr_sendctrl |= SYM_MASK(SendCtrl_0, TxeBypassIbc) |
				SYM_MASK(SendCtrl_0, TxeAbortIbc) |
				SYM_MASK(SendCtrl_0, TxeDrainRmFअगरo);

	spin_lock(&dd->sendctrl_lock);

	/* If we are draining everything, block sends first */
	अगर (op & QIB_SDMA_SENDCTRL_OP_DRAIN) अणु
		ppd->p_sendctrl &= ~SYM_MASK(SendCtrl_0, SendEnable);
		qib_ग_लिखो_kreg_port(ppd, krp_sendctrl, ppd->p_sendctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
	पूर्ण

	ppd->p_sendctrl |= set_sendctrl;
	ppd->p_sendctrl &= ~clr_sendctrl;

	अगर (op & QIB_SDMA_SENDCTRL_OP_CLEANUP)
		qib_ग_लिखो_kreg_port(ppd, krp_sendctrl,
				    ppd->p_sendctrl |
				    SYM_MASK(SendCtrl_0, SDmaCleanup));
	अन्यथा
		qib_ग_लिखो_kreg_port(ppd, krp_sendctrl, ppd->p_sendctrl);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);

	अगर (op & QIB_SDMA_SENDCTRL_OP_DRAIN) अणु
		ppd->p_sendctrl |= SYM_MASK(SendCtrl_0, SendEnable);
		qib_ग_लिखो_kreg_port(ppd, krp_sendctrl, ppd->p_sendctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
	पूर्ण

	spin_unlock(&dd->sendctrl_lock);

	अगर ((op & QIB_SDMA_SENDCTRL_OP_DRAIN) && ppd->dd->cspec->r1)
		flush_fअगरo(ppd);
पूर्ण

अटल व्योम qib_7322_sdma_hw_clean_up(काष्ठा qib_pportdata *ppd)
अणु
	__qib_sdma_process_event(ppd, qib_sdma_event_e50_hw_cleaned);
पूर्ण

अटल व्योम qib_sdma_7322_setlengen(काष्ठा qib_pportdata *ppd)
अणु
	/*
	 * Set SendDmaLenGen and clear and set
	 * the MSB of the generation count to enable generation checking
	 * and load the पूर्णांकernal generation counter.
	 */
	qib_ग_लिखो_kreg_port(ppd, krp_senddmalengen, ppd->sdma_descq_cnt);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmalengen,
			    ppd->sdma_descq_cnt |
			    (1ULL << QIB_7322_SendDmaLenGen_0_Generation_MSB));
पूर्ण

/*
 * Must be called with sdma_lock held, or beक्रमe init finished.
 */
अटल व्योम qib_sdma_update_7322_tail(काष्ठा qib_pportdata *ppd, u16 tail)
अणु
	/* Commit ग_लिखोs to memory and advance the tail on the chip */
	wmb();
	ppd->sdma_descq_tail = tail;
	qib_ग_लिखो_kreg_port(ppd, krp_senddmatail, tail);
पूर्ण

/*
 * This is called with पूर्णांकerrupts disabled and sdma_lock held.
 */
अटल व्योम qib_7322_sdma_hw_start_up(काष्ठा qib_pportdata *ppd)
अणु
	/*
	 * Drain all FIFOs.
	 * The hardware करोesn't require this but we करो it so that verbs
	 * and user applications करोn't रुको क्रम link active to send stale
	 * data.
	 */
	sendctrl_7322_mod(ppd, QIB_SENDCTRL_FLUSH);

	qib_sdma_7322_setlengen(ppd);
	qib_sdma_update_7322_tail(ppd, 0); /* Set SendDmaTail */
	ppd->sdma_head_dma[0] = 0;
	qib_7322_sdma_sendctrl(ppd,
		ppd->sdma_state.current_op | QIB_SDMA_SENDCTRL_OP_CLEANUP);
पूर्ण

#घोषणा DISABLES_SDMA ( \
	QIB_E_P_SDMAHALT | \
	QIB_E_P_SDMADESCADDRMISALIGN | \
	QIB_E_P_SDMAMISSINGDW | \
	QIB_E_P_SDMADWEN | \
	QIB_E_P_SDMARPYTAG | \
	QIB_E_P_SDMA1STDESC | \
	QIB_E_P_SDMABASE | \
	QIB_E_P_SDMATAILOUTOFBOUND | \
	QIB_E_P_SDMAOUTOFBOUND | \
	QIB_E_P_SDMAGENMISMATCH)

अटल व्योम sdma_7322_p_errors(काष्ठा qib_pportdata *ppd, u64 errs)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qib_devdata *dd = ppd->dd;

	errs &= QIB_E_P_SDMAERRS;
	err_decode(ppd->cpspec->sdmamsgbuf, माप(ppd->cpspec->sdmamsgbuf),
		   errs, qib_7322p_error_msgs);

	अगर (errs & QIB_E_P_SDMAUNEXPDATA)
		qib_dev_err(dd, "IB%u:%u SDmaUnexpData\n", dd->unit,
			    ppd->port);

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	अगर (errs != QIB_E_P_SDMAHALT) अणु
		/* SDMA errors have QIB_E_P_SDMAHALT and another bit set */
		qib_dev_porterr(dd, ppd->port,
			"SDMA %s 0x%016llx %s\n",
			qib_sdma_state_names[ppd->sdma_state.current_state],
			errs, ppd->cpspec->sdmamsgbuf);
		dump_sdma_7322_state(ppd);
	पूर्ण

	चयन (ppd->sdma_state.current_state) अणु
	हाल qib_sdma_state_s00_hw_करोwn:
		अवरोध;

	हाल qib_sdma_state_s10_hw_start_up_रुको:
		अगर (errs & QIB_E_P_SDMAHALT)
			__qib_sdma_process_event(ppd,
				qib_sdma_event_e20_hw_started);
		अवरोध;

	हाल qib_sdma_state_s20_idle:
		अवरोध;

	हाल qib_sdma_state_s30_sw_clean_up_रुको:
		अवरोध;

	हाल qib_sdma_state_s40_hw_clean_up_रुको:
		अगर (errs & QIB_E_P_SDMAHALT)
			__qib_sdma_process_event(ppd,
				qib_sdma_event_e50_hw_cleaned);
		अवरोध;

	हाल qib_sdma_state_s50_hw_halt_रुको:
		अगर (errs & QIB_E_P_SDMAHALT)
			__qib_sdma_process_event(ppd,
				qib_sdma_event_e60_hw_halted);
		अवरोध;

	हाल qib_sdma_state_s99_running:
		__qib_sdma_process_event(ppd, qib_sdma_event_e7322_err_halted);
		__qib_sdma_process_event(ppd, qib_sdma_event_e60_hw_halted);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
पूर्ण

/*
 * handle per-device errors (not per-port errors)
 */
अटल noअंतरभूत व्योम handle_7322_errors(काष्ठा qib_devdata *dd)
अणु
	अक्षर *msg;
	u64 iserr = 0;
	u64 errs;
	u64 mask;

	qib_stats.sps_errपूर्णांकs++;
	errs = qib_पढ़ो_kreg64(dd, kr_errstatus);
	अगर (!errs) अणु
		qib_devinfo(dd->pcidev,
			"device error interrupt, but no error bits set!\n");
		जाओ करोne;
	पूर्ण

	/* करोn't report errors that are masked */
	errs &= dd->cspec->errormask;
	msg = dd->cspec->emsgbuf;

	/* करो these first, they are most important */
	अगर (errs & QIB_E_HARDWARE) अणु
		*msg = '\0';
		qib_7322_handle_hwerrors(dd, msg, माप(dd->cspec->emsgbuf));
	पूर्ण

	अगर (errs & QIB_E_SPKTERRS) अणु
		qib_disarm_7322_senderrbufs(dd->pport);
		qib_stats.sps_txerrs++;
	पूर्ण अन्यथा अगर (errs & QIB_E_INVALIDADDR)
		qib_stats.sps_txerrs++;
	अन्यथा अगर (errs & QIB_E_ARMLAUNCH) अणु
		qib_stats.sps_txerrs++;
		qib_disarm_7322_senderrbufs(dd->pport);
	पूर्ण
	qib_ग_लिखो_kreg(dd, kr_errclear, errs);

	/*
	 * The ones we mask off are handled specially below
	 * or above.  Also mask SDMADISABLED by शेष as it
	 * is too chatty.
	 */
	mask = QIB_E_HARDWARE;
	*msg = '\0';

	err_decode(msg, माप(dd->cspec->emsgbuf), errs & ~mask,
		   qib_7322error_msgs);

	/*
	 * Getting reset is a tragedy क्रम all ports. Mark the device
	 * _and_ the ports as "offline" in way meaningful to each.
	 */
	अगर (errs & QIB_E_RESET) अणु
		पूर्णांक pidx;

		qib_dev_err(dd,
			"Got reset, requires re-init (unload and reload driver)\n");
		dd->flags &= ~QIB_INITTED;  /* needs re-init */
		/* mark as having had error */
		*dd->devstatusp |= QIB_STATUS_HWERROR;
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx)
			अगर (dd->pport[pidx].link_speed_supported)
				*dd->pport[pidx].statusp &= ~QIB_STATUS_IB_CONF;
	पूर्ण

	अगर (*msg && iserr)
		qib_dev_err(dd, "%s error\n", msg);

	/*
	 * If there were hdrq or egrfull errors, wake up any processes
	 * रुकोing in poll.  We used to try to check which contexts had
	 * the overflow, but given the cost of that and the chip पढ़ोs
	 * to support it, it's better to just wake everybody up अगर we
	 * get an overflow; रुकोers can poll again अगर it's not them.
	 */
	अगर (errs & (ERR_MASK(RcvEgrFullErr) | ERR_MASK(RcvHdrFullErr))) अणु
		qib_handle_urcv(dd, ~0U);
		अगर (errs & ERR_MASK(RcvEgrFullErr))
			qib_stats.sps_buffull++;
		अन्यथा
			qib_stats.sps_hdrfull++;
	पूर्ण

करोne:
	वापस;
पूर्ण

अटल व्योम qib_error_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा qib_devdata *dd = from_tasklet(dd, t, error_tasklet);

	handle_7322_errors(dd);
	qib_ग_लिखो_kreg(dd, kr_errmask, dd->cspec->errormask);
पूर्ण

अटल व्योम reenable_chase(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_chippport_specअगरic *cp = from_समयr(cp, t, chase_समयr);
	काष्ठा qib_pportdata *ppd = cp->ppd;

	ppd->cpspec->chase_समयr.expires = 0;
	qib_set_ib_7322_lstate(ppd, QLOGIC_IB_IBCC_LINKCMD_DOWN,
		QLOGIC_IB_IBCC_LINKINITCMD_POLL);
पूर्ण

अटल व्योम disable_chase(काष्ठा qib_pportdata *ppd, अचिन्हित दीर्घ tnow,
		u8 ibclt)
अणु
	ppd->cpspec->chase_end = 0;

	अगर (!qib_chase)
		वापस;

	qib_set_ib_7322_lstate(ppd, QLOGIC_IB_IBCC_LINKCMD_DOWN,
		QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);
	ppd->cpspec->chase_समयr.expires = jअगरfies + QIB_CHASE_DIS_TIME;
	add_समयr(&ppd->cpspec->chase_समयr);
पूर्ण

अटल व्योम handle_serdes_issues(काष्ठा qib_pportdata *ppd, u64 ibcst)
अणु
	u8 ibclt;
	अचिन्हित दीर्घ tnow;

	ibclt = (u8)SYM_FIELD(ibcst, IBCStatusA_0, LinkTrainingState);

	/*
	 * Detect and handle the state chase issue, where we can
	 * get stuck अगर we are unlucky on timing on both sides of
	 * the link.   If we are, we disable, set a समयr, and
	 * then re-enable.
	 */
	चयन (ibclt) अणु
	हाल IB_7322_LT_STATE_CFGRCVFCFG:
	हाल IB_7322_LT_STATE_CFGWAITRMT:
	हाल IB_7322_LT_STATE_TXREVLANES:
	हाल IB_7322_LT_STATE_CFGENH:
		tnow = jअगरfies;
		अगर (ppd->cpspec->chase_end &&
		     समय_after(tnow, ppd->cpspec->chase_end))
			disable_chase(ppd, tnow, ibclt);
		अन्यथा अगर (!ppd->cpspec->chase_end)
			ppd->cpspec->chase_end = tnow + QIB_CHASE_TIME;
		अवरोध;
	शेष:
		ppd->cpspec->chase_end = 0;
		अवरोध;
	पूर्ण

	अगर (((ibclt >= IB_7322_LT_STATE_CFGTEST &&
	      ibclt <= IB_7322_LT_STATE_CFGWAITENH) ||
	     ibclt == IB_7322_LT_STATE_LINKUP) &&
	    (ibcst & SYM_MASK(IBCStatusA_0, LinkSpeedQDR))) अणु
		क्रमce_h1(ppd);
		ppd->cpspec->qdr_reक्रमce = 1;
		अगर (!ppd->dd->cspec->r1)
			serdes_7322_los_enable(ppd, 0);
	पूर्ण अन्यथा अगर (ppd->cpspec->qdr_reक्रमce &&
		(ibcst & SYM_MASK(IBCStatusA_0, LinkSpeedQDR)) &&
		 (ibclt == IB_7322_LT_STATE_CFGENH ||
		ibclt == IB_7322_LT_STATE_CFGIDLE ||
		ibclt == IB_7322_LT_STATE_LINKUP))
		क्रमce_h1(ppd);

	अगर ((IS_QMH(ppd->dd) || IS_QME(ppd->dd)) &&
	    ppd->link_speed_enabled == QIB_IB_QDR &&
	    (ibclt == IB_7322_LT_STATE_CFGTEST ||
	     ibclt == IB_7322_LT_STATE_CFGENH ||
	     (ibclt >= IB_7322_LT_STATE_POLLACTIVE &&
	      ibclt <= IB_7322_LT_STATE_SLEEPQUIET)))
		adj_tx_serdes(ppd);

	अगर (ibclt != IB_7322_LT_STATE_LINKUP) अणु
		u8 ltstate = qib_7322_phys_portstate(ibcst);
		u8 pibclt = (u8)SYM_FIELD(ppd->lastibcstat, IBCStatusA_0,
					  LinkTrainingState);
		अगर (!ppd->dd->cspec->r1 &&
		    pibclt == IB_7322_LT_STATE_LINKUP &&
		    ltstate != IB_PHYSPORTSTATE_LINK_ERR_RECOVER &&
		    ltstate != IB_PHYSPORTSTATE_RECOVERY_RETRAIN &&
		    ltstate != IB_PHYSPORTSTATE_RECOVERY_WAITRMT &&
		    ltstate != IB_PHYSPORTSTATE_RECOVERY_IDLE)
			/* If the link went करोwn (but no पूर्णांकo recovery,
			 * turn LOS back on */
			serdes_7322_los_enable(ppd, 1);
		अगर (!ppd->cpspec->qdr_dfe_on &&
		    ibclt <= IB_7322_LT_STATE_SLEEPQUIET) अणु
			ppd->cpspec->qdr_dfe_on = 1;
			ppd->cpspec->qdr_dfe_समय = 0;
			/* On link करोwn, reenable QDR adaptation */
			qib_ग_लिखो_kreg_port(ppd, krp_अटल_adapt_dis(2),
					    ppd->dd->cspec->r1 ?
					    QDR_STATIC_ADAPT_DOWN_R1 :
					    QDR_STATIC_ADAPT_DOWN);
			pr_info(
				"IB%u:%u re-enabled QDR adaptation ibclt %x\n",
				ppd->dd->unit, ppd->port, ibclt);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qib_7322_set_ib_cfg(काष्ठा qib_pportdata *, पूर्णांक, u32);

/*
 * This is per-pport error handling.
 * will likely get it's own MSIx पूर्णांकerrupt (one क्रम each port,
 * although just a single handler).
 */
अटल noअंतरभूत व्योम handle_7322_p_errors(काष्ठा qib_pportdata *ppd)
अणु
	अक्षर *msg;
	u64 ignore_this_समय = 0, iserr = 0, errs, fmask;
	काष्ठा qib_devdata *dd = ppd->dd;

	/* करो this as soon as possible */
	fmask = qib_पढ़ो_kreg64(dd, kr_act_fmask);
	अगर (!fmask)
		check_7322_rxe_status(ppd);

	errs = qib_पढ़ो_kreg_port(ppd, krp_errstatus);
	अगर (!errs)
		qib_devinfo(dd->pcidev,
			 "Port%d error interrupt, but no error bits set!\n",
			 ppd->port);
	अगर (!fmask)
		errs &= ~QIB_E_P_IBSTATUSCHANGED;
	अगर (!errs)
		जाओ करोne;

	msg = ppd->cpspec->epmsgbuf;
	*msg = '\0';

	अगर (errs & ~QIB_E_P_BITSEXTANT) अणु
		err_decode(msg, माप(ppd->cpspec->epmsgbuf),
			   errs & ~QIB_E_P_BITSEXTANT, qib_7322p_error_msgs);
		अगर (!*msg)
			snम_लिखो(msg, माप(ppd->cpspec->epmsgbuf),
				 "no others");
		qib_dev_porterr(dd, ppd->port,
			"error interrupt with unknown errors 0x%016Lx set (and %s)\n",
			(errs & ~QIB_E_P_BITSEXTANT), msg);
		*msg = '\0';
	पूर्ण

	अगर (errs & QIB_E_P_SHDR) अणु
		u64 symptom;

		/* determine cause, then ग_लिखो to clear */
		symptom = qib_पढ़ो_kreg_port(ppd, krp_sendhdrsymptom);
		qib_ग_लिखो_kreg_port(ppd, krp_sendhdrsymptom, 0);
		err_decode(msg, माप(ppd->cpspec->epmsgbuf), symptom,
			   hdrchk_msgs);
		*msg = '\0';
		/* senderrbuf cleared in SPKTERRS below */
	पूर्ण

	अगर (errs & QIB_E_P_SPKTERRS) अणु
		अगर ((errs & QIB_E_P_LINK_PKTERRS) &&
		    !(ppd->lflags & QIBL_LINKACTIVE)) अणु
			/*
			 * This can happen when trying to bring the link
			 * up, but the IB link changes state at the "wrong"
			 * समय. The IB logic then complains that the packet
			 * isn't valid.  We don't want to confuse people, so
			 * we just करोn't prपूर्णांक them, except at debug
			 */
			err_decode(msg, माप(ppd->cpspec->epmsgbuf),
				   (errs & QIB_E_P_LINK_PKTERRS),
				   qib_7322p_error_msgs);
			*msg = '\0';
			ignore_this_समय = errs & QIB_E_P_LINK_PKTERRS;
		पूर्ण
		qib_disarm_7322_senderrbufs(ppd);
	पूर्ण अन्यथा अगर ((errs & QIB_E_P_LINK_PKTERRS) &&
		   !(ppd->lflags & QIBL_LINKACTIVE)) अणु
		/*
		 * This can happen when SMA is trying to bring the link
		 * up, but the IB link changes state at the "wrong" समय.
		 * The IB logic then complains that the packet isn't
		 * valid.  We करोn't want to confuse people, so we just
		 * करोn't prपूर्णांक them, except at debug
		 */
		err_decode(msg, माप(ppd->cpspec->epmsgbuf), errs,
			   qib_7322p_error_msgs);
		ignore_this_समय = errs & QIB_E_P_LINK_PKTERRS;
		*msg = '\0';
	पूर्ण

	qib_ग_लिखो_kreg_port(ppd, krp_errclear, errs);

	errs &= ~ignore_this_समय;
	अगर (!errs)
		जाओ करोne;

	अगर (errs & QIB_E_P_RPKTERRS)
		qib_stats.sps_rcverrs++;
	अगर (errs & QIB_E_P_SPKTERRS)
		qib_stats.sps_txerrs++;

	iserr = errs & ~(QIB_E_P_RPKTERRS | QIB_E_P_PKTERRS);

	अगर (errs & QIB_E_P_SDMAERRS)
		sdma_7322_p_errors(ppd, errs);

	अगर (errs & QIB_E_P_IBSTATUSCHANGED) अणु
		u64 ibcs;
		u8 ltstate;

		ibcs = qib_पढ़ो_kreg_port(ppd, krp_ibcstatus_a);
		ltstate = qib_7322_phys_portstate(ibcs);

		अगर (!(ppd->lflags & QIBL_IB_AUTONEG_INPROG))
			handle_serdes_issues(ppd, ibcs);
		अगर (!(ppd->cpspec->ibcctrl_a &
		      SYM_MASK(IBCCtrlA_0, IBStatIntReductionEn))) अणु
			/*
			 * We got our पूर्णांकerrupt, so init code should be
			 * happy and not try alternatives. Now squelch
			 * other "chatter" from link-negotiation (pre Init)
			 */
			ppd->cpspec->ibcctrl_a |=
				SYM_MASK(IBCCtrlA_0, IBStatIntReductionEn);
			qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a,
					    ppd->cpspec->ibcctrl_a);
		पूर्ण

		/* Update our picture of width and speed from chip */
		ppd->link_width_active =
			(ibcs & SYM_MASK(IBCStatusA_0, LinkWidthActive)) ?
			    IB_WIDTH_4X : IB_WIDTH_1X;
		ppd->link_speed_active = (ibcs & SYM_MASK(IBCStatusA_0,
			LinkSpeedQDR)) ? QIB_IB_QDR : (ibcs &
			  SYM_MASK(IBCStatusA_0, LinkSpeedActive)) ?
				   QIB_IB_DDR : QIB_IB_SDR;

		अगर ((ppd->lflags & QIBL_IB_LINK_DISABLED) && ltstate !=
		    IB_PHYSPORTSTATE_DISABLED)
			qib_set_ib_7322_lstate(ppd, 0,
			       QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);
		अन्यथा
			/*
			 * Since going पूर्णांकo a recovery state causes the link
			 * state to go करोwn and since recovery is transitory,
			 * it is better अगर we "miss" ever seeing the link
			 * training state go पूर्णांकo recovery (i.e., ignore this
			 * transition क्रम link state special handling purposes)
			 * without updating lastibcstat.
			 */
			अगर (ltstate != IB_PHYSPORTSTATE_LINK_ERR_RECOVER &&
			    ltstate != IB_PHYSPORTSTATE_RECOVERY_RETRAIN &&
			    ltstate != IB_PHYSPORTSTATE_RECOVERY_WAITRMT &&
			    ltstate != IB_PHYSPORTSTATE_RECOVERY_IDLE)
				qib_handle_e_ibstatuschanged(ppd, ibcs);
	पूर्ण
	अगर (*msg && iserr)
		qib_dev_porterr(dd, ppd->port, "%s error\n", msg);

	अगर (ppd->state_wanted & ppd->lflags)
		wake_up_पूर्णांकerruptible(&ppd->state_रुको);
करोne:
	वापस;
पूर्ण

/* enable/disable chip from delivering पूर्णांकerrupts */
अटल व्योम qib_7322_set_पूर्णांकr_state(काष्ठा qib_devdata *dd, u32 enable)
अणु
	अगर (enable) अणु
		अगर (dd->flags & QIB_BADINTR)
			वापस;
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकmask, dd->cspec->पूर्णांक_enable_mask);
		/* cause any pending enabled पूर्णांकerrupts to be re-delivered */
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, 0ULL);
		अगर (dd->cspec->num_msix_entries) अणु
			/* and same क्रम MSIx */
			u64 val = qib_पढ़ो_kreg64(dd, kr_पूर्णांकgranted);

			अगर (val)
				qib_ग_लिखो_kreg(dd, kr_पूर्णांकgranted, val);
		पूर्ण
	पूर्ण अन्यथा
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकmask, 0ULL);
पूर्ण

/*
 * Try to cleanup as much as possible क्रम anything that might have gone
 * wrong जबतक in मुक्तze mode, such as pio buffers being written by user
 * processes (causing armlaunch), send errors due to going पूर्णांकo मुक्तze mode,
 * etc., and try to aव्योम causing extra पूर्णांकerrupts जबतक करोing so.
 * Forcibly update the in-memory pioavail रेजिस्टर copies after cleanup
 * because the chip won't करो it जबतक in मुक्तze mode (the रेजिस्टर values
 * themselves are kept correct).
 * Make sure that we करोn't lose any important पूर्णांकerrupts by using the chip
 * feature that says that writing 0 to a bit in *clear that is set in
 * *status will cause an पूर्णांकerrupt to be generated again (अगर allowed by
 * the *mask value).
 * This is in chip-specअगरic code because of all of the रेजिस्टर accesses,
 * even though the details are similar on most chips.
 */
अटल व्योम qib_7322_clear_मुक्तze(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक pidx;

	/* disable error पूर्णांकerrupts, to aव्योम confusion */
	qib_ग_लिखो_kreg(dd, kr_errmask, 0ULL);

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx)
		अगर (dd->pport[pidx].link_speed_supported)
			qib_ग_लिखो_kreg_port(dd->pport + pidx, krp_errmask,
					    0ULL);

	/* also disable पूर्णांकerrupts; errormask is someबार overwritten */
	qib_7322_set_पूर्णांकr_state(dd, 0);

	/* clear the मुक्तze, and be sure chip saw it */
	qib_ग_लिखो_kreg(dd, kr_control, dd->control);
	qib_पढ़ो_kreg32(dd, kr_scratch);

	/*
	 * Force new पूर्णांकerrupt अगर any hwerr, error or पूर्णांकerrupt bits are
	 * still set, and clear "safe" send packet errors related to मुक्तze
	 * and cancelling sends.  Re-enable error पूर्णांकerrupts beक्रमe possible
	 * क्रमce of re-पूर्णांकerrupt on pending पूर्णांकerrupts.
	 */
	qib_ग_लिखो_kreg(dd, kr_hwerrclear, 0ULL);
	qib_ग_लिखो_kreg(dd, kr_errclear, E_SPKT_ERRS_IGNORE);
	qib_ग_लिखो_kreg(dd, kr_errmask, dd->cspec->errormask);
	/* We need to purge per-port errs and reset mask, too */
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		अगर (!dd->pport[pidx].link_speed_supported)
			जारी;
		qib_ग_लिखो_kreg_port(dd->pport + pidx, krp_errclear, ~0Ull);
		qib_ग_लिखो_kreg_port(dd->pport + pidx, krp_errmask, ~0Ull);
	पूर्ण
	qib_7322_set_पूर्णांकr_state(dd, 1);
पूर्ण

/* no error handling to speak of */
/**
 * qib_7322_handle_hwerrors - display hardware errors.
 * @dd: the qlogic_ib device
 * @msg: the output buffer
 * @msgl: the size of the output buffer
 *
 * Use same msg buffer as regular errors to aव्योम excessive stack
 * use.  Most hardware errors are catastrophic, but क्रम right now,
 * we'll prपूर्णांक them and जारी.  We reuse the same message buffer as
 * qib_handle_errors() to aव्योम excessive stack usage.
 */
अटल व्योम qib_7322_handle_hwerrors(काष्ठा qib_devdata *dd, अक्षर *msg,
				     माप_प्रकार msgl)
अणु
	u64 hwerrs;
	u32 ctrl;
	पूर्णांक isfatal = 0;

	hwerrs = qib_पढ़ो_kreg64(dd, kr_hwerrstatus);
	अगर (!hwerrs)
		जाओ bail;
	अगर (hwerrs == ~0ULL) अणु
		qib_dev_err(dd,
			"Read of hardware error status failed (all bits set); ignoring\n");
		जाओ bail;
	पूर्ण
	qib_stats.sps_hwerrs++;

	/* Always clear the error status रेजिस्टर, except BIST fail */
	qib_ग_लिखो_kreg(dd, kr_hwerrclear, hwerrs &
		       ~HWE_MASK(PowerOnBISTFailed));

	hwerrs &= dd->cspec->hwerrmask;

	/* no EEPROM logging, yet */

	अगर (hwerrs)
		qib_devinfo(dd->pcidev,
			"Hardware error: hwerr=0x%llx (cleared)\n",
			(अचिन्हित दीर्घ दीर्घ) hwerrs);

	ctrl = qib_पढ़ो_kreg32(dd, kr_control);
	अगर ((ctrl & SYM_MASK(Control, FreezeMode)) && !dd->diag_client) अणु
		/*
		 * No recovery yet...
		 */
		अगर ((hwerrs & ~HWE_MASK(LATriggered)) ||
		    dd->cspec->stay_in_मुक्तze) अणु
			/*
			 * If any set that we aren't ignoring only make the
			 * complaपूर्णांक once, in हाल it's stuck or recurring,
			 * and we get here multiple बार
			 * Force link करोwn, so चयन knows, and
			 * LEDs are turned off.
			 */
			अगर (dd->flags & QIB_INITTED)
				isfatal = 1;
		पूर्ण अन्यथा
			qib_7322_clear_मुक्तze(dd);
	पूर्ण

	अगर (hwerrs & HWE_MASK(PowerOnBISTFailed)) अणु
		isfatal = 1;
		strlcpy(msg,
			"[Memory BIST test failed, InfiniPath hardware unusable]",
			msgl);
		/* ignore from now on, so disable until driver reloaded */
		dd->cspec->hwerrmask &= ~HWE_MASK(PowerOnBISTFailed);
		qib_ग_लिखो_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);
	पूर्ण

	err_decode(msg, msgl, hwerrs, qib_7322_hwerror_msgs);

	/* Ignore esoteric PLL failures et al. */

	qib_dev_err(dd, "%s hardware error\n", msg);

	अगर (hwerrs &
		   (SYM_MASK(HwErrMask, SDmaMemReadErrMask_0) |
		    SYM_MASK(HwErrMask, SDmaMemReadErrMask_1))) अणु
		पूर्णांक pidx = 0;
		पूर्णांक err;
		अचिन्हित दीर्घ flags;
		काष्ठा qib_pportdata *ppd = dd->pport;

		क्रम (; pidx < dd->num_pports; ++pidx, ppd++) अणु
			err = 0;
			अगर (pidx == 0 && (hwerrs &
				SYM_MASK(HwErrMask, SDmaMemReadErrMask_0)))
				err++;
			अगर (pidx == 1 && (hwerrs &
				SYM_MASK(HwErrMask, SDmaMemReadErrMask_1)))
				err++;
			अगर (err) अणु
				spin_lock_irqsave(&ppd->sdma_lock, flags);
				dump_sdma_7322_state(ppd);
				spin_unlock_irqrestore(&ppd->sdma_lock, flags);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (isfatal && !dd->diag_client) अणु
		qib_dev_err(dd,
			"Fatal Hardware Error, no longer usable, SN %.16s\n",
			dd->serial);
		/*
		 * क्रम /sys status file and user programs to prपूर्णांक; अगर no
		 * trailing brace is copied, we'll know it was truncated.
		 */
		अगर (dd->मुक्तzemsg)
			snम_लिखो(dd->मुक्तzemsg, dd->मुक्तzelen,
				 "{%s}", msg);
		qib_disable_after_error(dd);
	पूर्ण
bail:;
पूर्ण

/**
 * qib_7322_init_hwerrors - enable hardware errors
 * @dd: the qlogic_ib device
 *
 * now that we have finished initializing everything that might reasonably
 * cause a hardware error, and cleared those errors bits as they occur,
 * we can enable hardware errors in the mask (potentially enabling
 * मुक्तze mode), and enable hardware errors as errors (aदीर्घ with
 * everything अन्यथा) in errormask
 */
अटल व्योम qib_7322_init_hwerrors(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक pidx;
	u64 extsval;

	extsval = qib_पढ़ो_kreg64(dd, kr_extstatus);
	अगर (!(extsval & (QIB_EXTS_MEMBIST_DISABLED |
			 QIB_EXTS_MEMBIST_ENDTEST)))
		qib_dev_err(dd, "MemBIST did not complete!\n");

	/* never clear BIST failure, so reported on each driver load */
	qib_ग_लिखो_kreg(dd, kr_hwerrclear, ~HWE_MASK(PowerOnBISTFailed));
	qib_ग_लिखो_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);

	/* clear all */
	qib_ग_लिखो_kreg(dd, kr_errclear, ~0ULL);
	/* enable errors that are masked, at least this first समय. */
	qib_ग_लिखो_kreg(dd, kr_errmask, ~0ULL);
	dd->cspec->errormask = qib_पढ़ो_kreg64(dd, kr_errmask);
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx)
		अगर (dd->pport[pidx].link_speed_supported)
			qib_ग_लिखो_kreg_port(dd->pport + pidx, krp_errmask,
					    ~0ULL);
पूर्ण

/*
 * Disable and enable the armlaunch error.  Used क्रम PIO bandwidth testing
 * on chips that are count-based, rather than trigger-based.  There is no
 * reference counting, but that's also fine, given the पूर्णांकended use.
 * Only chip-specअगरic because it's all रेजिस्टर accesses
 */
अटल व्योम qib_set_7322_armlaunch(काष्ठा qib_devdata *dd, u32 enable)
अणु
	अगर (enable) अणु
		qib_ग_लिखो_kreg(dd, kr_errclear, QIB_E_SPIOARMLAUNCH);
		dd->cspec->errormask |= QIB_E_SPIOARMLAUNCH;
	पूर्ण अन्यथा
		dd->cspec->errormask &= ~QIB_E_SPIOARMLAUNCH;
	qib_ग_लिखो_kreg(dd, kr_errmask, dd->cspec->errormask);
पूर्ण

/*
 * Formerly took parameter <which> in pre-shअगरted,
 * pre-merged क्रमm with LinkCmd and LinkInitCmd
 * together, and assuming the zero was NOP.
 */
अटल व्योम qib_set_ib_7322_lstate(काष्ठा qib_pportdata *ppd, u16 linkcmd,
				   u16 linitcmd)
अणु
	u64 mod_wd;
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ flags;

	अगर (linitcmd == QLOGIC_IB_IBCC_LINKINITCMD_DISABLE) अणु
		/*
		 * If we are told to disable, note that so link-recovery
		 * code करोes not attempt to bring us back up.
		 * Also reset everything that we can, so we start
		 * completely clean when re-enabled (beक्रमe we
		 * actually issue the disable to the IBC)
		 */
		qib_7322_mini_pcs_reset(ppd);
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags |= QIBL_IB_LINK_DISABLED;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	पूर्ण अन्यथा अगर (linitcmd || linkcmd == QLOGIC_IB_IBCC_LINKCMD_DOWN) अणु
		/*
		 * Any other linkinitcmd will lead to LINKDOWN and then
		 * to INIT (अगर all is well), so clear flag to let
		 * link-recovery code attempt to bring us back up.
		 */
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags &= ~QIBL_IB_LINK_DISABLED;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		/*
		 * Clear status change पूर्णांकerrupt reduction so the
		 * new state is seen.
		 */
		ppd->cpspec->ibcctrl_a &=
			~SYM_MASK(IBCCtrlA_0, IBStatIntReductionEn);
	पूर्ण

	mod_wd = (linkcmd << IBA7322_IBCC_LINKCMD_SHIFT) |
		(linitcmd << QLOGIC_IB_IBCC_LINKINITCMD_SHIFT);

	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a, ppd->cpspec->ibcctrl_a |
			    mod_wd);
	/* ग_लिखो to chip to prevent back-to-back ग_लिखोs of ibc reg */
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);

पूर्ण

/*
 * The total RCV buffer memory is 64KB, used क्रम both ports, and is
 * in units of 64 bytes (same as IB flow control credit unit).
 * The consumedVL unit in the same रेजिस्टरs are in 32 byte units!
 * So, a VL15 packet needs 4.50 IB credits, and 9 rx buffer chunks,
 * and we can thereक्रमe allocate just 9 IB credits क्रम 2 VL15 packets
 * in krp_rxcreditvl15, rather than 10.
 */
#घोषणा RCV_BUF_UNITSZ 64
#घोषणा NUM_RCV_BUF_UNITS(dd) ((64 * 1024) / (RCV_BUF_UNITSZ * dd->num_pports))

अटल व्योम set_vls(काष्ठा qib_pportdata *ppd)
अणु
	पूर्णांक i, numvls, totcred, cred_vl, vl0extra;
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 val;

	numvls = qib_num_vls(ppd->vls_operational);

	/*
	 * Set up per-VL credits. Below is kluge based on these assumptions:
	 * 1) port is disabled at the समय early_init is called.
	 * 2) give VL15 17 credits, क्रम two max-plausible packets.
	 * 3) Give VL0-N the rest, with any rounding excess used क्रम VL0
	 */
	/* 2 VL15 packets @ 288 bytes each (including IB headers) */
	totcred = NUM_RCV_BUF_UNITS(dd);
	cred_vl = (2 * 288 + RCV_BUF_UNITSZ - 1) / RCV_BUF_UNITSZ;
	totcred -= cred_vl;
	qib_ग_लिखो_kreg_port(ppd, krp_rxcreditvl15, (u64) cred_vl);
	cred_vl = totcred / numvls;
	vl0extra = totcred - cred_vl * numvls;
	qib_ग_लिखो_kreg_port(ppd, krp_rxcreditvl0, cred_vl + vl0extra);
	क्रम (i = 1; i < numvls; i++)
		qib_ग_लिखो_kreg_port(ppd, krp_rxcreditvl0 + i, cred_vl);
	क्रम (; i < 8; i++) /* no buffer space क्रम other VLs */
		qib_ग_लिखो_kreg_port(ppd, krp_rxcreditvl0 + i, 0);

	/* Notअगरy IBC that credits need to be recalculated */
	val = qib_पढ़ो_kreg_port(ppd, krp_ibsdtestअगरtx);
	val |= SYM_MASK(IB_SDTEST_IF_TX_0, CREDIT_CHANGE);
	qib_ग_लिखो_kreg_port(ppd, krp_ibsdtestअगरtx, val);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
	val &= ~SYM_MASK(IB_SDTEST_IF_TX_0, CREDIT_CHANGE);
	qib_ग_लिखो_kreg_port(ppd, krp_ibsdtestअगरtx, val);

	क्रम (i = 0; i < numvls; i++)
		val = qib_पढ़ो_kreg_port(ppd, krp_rxcreditvl0 + i);
	val = qib_पढ़ो_kreg_port(ppd, krp_rxcreditvl15);

	/* Change the number of operational VLs */
	ppd->cpspec->ibcctrl_a = (ppd->cpspec->ibcctrl_a &
				~SYM_MASK(IBCCtrlA_0, NumVLane)) |
		((u64)(numvls - 1) << SYM_LSB(IBCCtrlA_0, NumVLane));
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a, ppd->cpspec->ibcctrl_a);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
पूर्ण

/*
 * The code that deals with actual SerDes is in serdes_7322_init().
 * Compared to the code क्रम iba7220, it is minimal.
 */
अटल पूर्णांक serdes_7322_init(काष्ठा qib_pportdata *ppd);

/**
 * qib_7322_bringup_serdes - bring up the serdes
 * @ppd: physical port on the qlogic_ib device
 */
अटल पूर्णांक qib_7322_bringup_serdes(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 val, guid, ibc;
	अचिन्हित दीर्घ flags;

	/*
	 * SerDes model not in Pd, but still need to
	 * set up much of IBCCtrl and IBCDDRCtrl; move अन्यथाwhere
	 * eventually.
	 */
	/* Put IBC in reset, sends disabled (should be in reset alपढ़ोy) */
	ppd->cpspec->ibcctrl_a &= ~SYM_MASK(IBCCtrlA_0, IBLinkEn);
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a, ppd->cpspec->ibcctrl_a);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);

	/* ensure previous Tx parameters are not still क्रमced */
	qib_ग_लिखो_kreg_port(ppd, krp_tx_deemph_override,
		SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		reset_tx_deemphasis_override));

	अगर (qib_compat_ddr_negotiate) अणु
		ppd->cpspec->ibdeltainprog = 1;
		ppd->cpspec->ibsymsnap = पढ़ो_7322_creg32_port(ppd,
						crp_ibsymbolerr);
		ppd->cpspec->iblnkerrsnap = पढ़ो_7322_creg32_port(ppd,
						crp_iblinkerrrecov);
	पूर्ण

	/* flowcontrolwatermark is in units of KBytes */
	ibc = 0x5ULL << SYM_LSB(IBCCtrlA_0, FlowCtrlWaterMark);
	/*
	 * Flow control is sent this often, even अगर no changes in
	 * buffer space occur.  Units are 128ns क्रम this chip.
	 * Set to 3usec.
	 */
	ibc |= 24ULL << SYM_LSB(IBCCtrlA_0, FlowCtrlPeriod);
	/* max error tolerance */
	ibc |= 0xfULL << SYM_LSB(IBCCtrlA_0, PhyerrThreshold);
	/* IB credit flow control. */
	ibc |= 0xfULL << SYM_LSB(IBCCtrlA_0, OverrunThreshold);
	/*
	 * set initial max size pkt IBC will send, including ICRC; it's the
	 * PIO buffer size in dwords, less 1; also see qib_set_mtu()
	 */
	ibc |= ((u64)(ppd->ibmaxlen >> 2) + 1) <<
		SYM_LSB(IBCCtrlA_0, MaxPktLen);
	ppd->cpspec->ibcctrl_a = ibc; /* without linkcmd or linkinitcmd! */

	/*
	 * Reset the PCS पूर्णांकerface to the serdes (and also ibc, which is still
	 * in reset from above).  Writes new value of ibcctrl_a as last step.
	 */
	qib_7322_mini_pcs_reset(ppd);

	अगर (!ppd->cpspec->ibcctrl_b) अणु
		अचिन्हित lse = ppd->link_speed_enabled;

		/*
		 * Not on re-init after reset, establish shaकरोw
		 * and क्रमce initial config.
		 */
		ppd->cpspec->ibcctrl_b = qib_पढ़ो_kreg_port(ppd,
							     krp_ibcctrl_b);
		ppd->cpspec->ibcctrl_b &= ~(IBA7322_IBC_SPEED_QDR |
				IBA7322_IBC_SPEED_DDR |
				IBA7322_IBC_SPEED_SDR |
				IBA7322_IBC_WIDTH_AUTONEG |
				SYM_MASK(IBCCtrlB_0, IB_LANE_REV_SUPPORTED));
		अगर (lse & (lse - 1)) /* Muliple speeds enabled */
			ppd->cpspec->ibcctrl_b |=
				(lse << IBA7322_IBC_SPEED_LSB) |
				IBA7322_IBC_IBTA_1_2_MASK |
				IBA7322_IBC_MAX_SPEED_MASK;
		अन्यथा
			ppd->cpspec->ibcctrl_b |= (lse == QIB_IB_QDR) ?
				IBA7322_IBC_SPEED_QDR |
				 IBA7322_IBC_IBTA_1_2_MASK :
				(lse == QIB_IB_DDR) ?
					IBA7322_IBC_SPEED_DDR :
					IBA7322_IBC_SPEED_SDR;
		अगर ((ppd->link_width_enabled & (IB_WIDTH_1X | IB_WIDTH_4X)) ==
		    (IB_WIDTH_1X | IB_WIDTH_4X))
			ppd->cpspec->ibcctrl_b |= IBA7322_IBC_WIDTH_AUTONEG;
		अन्यथा
			ppd->cpspec->ibcctrl_b |=
				ppd->link_width_enabled == IB_WIDTH_4X ?
				IBA7322_IBC_WIDTH_4X_ONLY :
				IBA7322_IBC_WIDTH_1X_ONLY;

		/* always enable these on driver reload, not sticky */
		ppd->cpspec->ibcctrl_b |= (IBA7322_IBC_RXPOL_MASK |
			IBA7322_IBC_HRTBT_MASK);
	पूर्ण
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_b, ppd->cpspec->ibcctrl_b);

	/* setup so we have more समय at CFGTEST to change H1 */
	val = qib_पढ़ो_kreg_port(ppd, krp_ibcctrl_c);
	val &= ~SYM_MASK(IBCCtrlC_0, IB_FRONT_PORCH);
	val |= 0xfULL << SYM_LSB(IBCCtrlC_0, IB_FRONT_PORCH);
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_c, val);

	serdes_7322_init(ppd);

	guid = be64_to_cpu(ppd->guid);
	अगर (!guid) अणु
		अगर (dd->base_guid)
			guid = be64_to_cpu(dd->base_guid) + ppd->port - 1;
		ppd->guid = cpu_to_be64(guid);
	पूर्ण

	qib_ग_लिखो_kreg_port(ppd, krp_hrtbt_guid, guid);
	/* ग_लिखो to chip to prevent back-to-back ग_लिखोs of ibc reg */
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);

	/* Enable port */
	ppd->cpspec->ibcctrl_a |= SYM_MASK(IBCCtrlA_0, IBLinkEn);
	set_vls(ppd);

	/* initially come up DISABLED, without sending anything. */
	val = ppd->cpspec->ibcctrl_a | (QLOGIC_IB_IBCC_LINKINITCMD_DISABLE <<
					QLOGIC_IB_IBCC_LINKINITCMD_SHIFT);
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a, val);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
	/* clear the linkinit cmds */
	ppd->cpspec->ibcctrl_a = val & ~SYM_MASK(IBCCtrlA_0, LinkInitCmd);

	/* be paranoid against later code motion, etc. */
	spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);
	ppd->p_rcvctrl |= SYM_MASK(RcvCtrl_0, RcvIBPortEnable);
	qib_ग_लिखो_kreg_port(ppd, krp_rcvctrl, ppd->p_rcvctrl);
	spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);

	/* Also enable IBSTATUSCHG पूर्णांकerrupt.  */
	val = qib_पढ़ो_kreg_port(ppd, krp_errmask);
	qib_ग_लिखो_kreg_port(ppd, krp_errmask,
		val | ERR_MASK_N(IBStatusChanged));

	/* Always zero until we start messing with SerDes क्रम real */
	वापस 0;
पूर्ण

/**
 * qib_7322_mini_quiet_serdes - set serdes to txidle
 * @ppd: the qlogic_ib device
 * Called when driver is being unloaded
 */
अटल व्योम qib_7322_mini_quiet_serdes(काष्ठा qib_pportdata *ppd)
अणु
	u64 val;
	अचिन्हित दीर्घ flags;

	qib_set_ib_7322_lstate(ppd, 0, QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags &= ~QIBL_IB_AUTONEG_INPROG;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	wake_up(&ppd->cpspec->स्वतःneg_रुको);
	cancel_delayed_work_sync(&ppd->cpspec->स्वतःneg_work);
	अगर (ppd->dd->cspec->r1)
		cancel_delayed_work_sync(&ppd->cpspec->ipg_work);

	ppd->cpspec->chase_end = 0;
	अगर (ppd->cpspec->chase_समयr.function) /* अगर initted */
		del_समयr_sync(&ppd->cpspec->chase_समयr);

	/*
	 * Despite the name, actually disables IBC as well. Do it when
	 * we are as sure as possible that no more packets can be
	 * received, following the करोwn and the PCS reset.
	 * The actual disabling happens in qib_7322_mini_pci_reset(),
	 * aदीर्घ with the PCS being reset.
	 */
	ppd->cpspec->ibcctrl_a &= ~SYM_MASK(IBCCtrlA_0, IBLinkEn);
	qib_7322_mini_pcs_reset(ppd);

	/*
	 * Update the adjusted counters so the adjusपंचांगent persists
	 * across driver reload.
	 */
	अगर (ppd->cpspec->ibsymdelta || ppd->cpspec->iblnkerrdelta ||
	    ppd->cpspec->ibdeltainprog || ppd->cpspec->iblnkकरोwndelta) अणु
		काष्ठा qib_devdata *dd = ppd->dd;
		u64 diagc;

		/* enable counter ग_लिखोs */
		diagc = qib_पढ़ो_kreg64(dd, kr_hwdiagctrl);
		qib_ग_लिखो_kreg(dd, kr_hwdiagctrl,
			       diagc | SYM_MASK(HwDiagCtrl, CounterWrEnable));

		अगर (ppd->cpspec->ibsymdelta || ppd->cpspec->ibdeltainprog) अणु
			val = पढ़ो_7322_creg32_port(ppd, crp_ibsymbolerr);
			अगर (ppd->cpspec->ibdeltainprog)
				val -= val - ppd->cpspec->ibsymsnap;
			val -= ppd->cpspec->ibsymdelta;
			ग_लिखो_7322_creg_port(ppd, crp_ibsymbolerr, val);
		पूर्ण
		अगर (ppd->cpspec->iblnkerrdelta || ppd->cpspec->ibdeltainprog) अणु
			val = पढ़ो_7322_creg32_port(ppd, crp_iblinkerrrecov);
			अगर (ppd->cpspec->ibdeltainprog)
				val -= val - ppd->cpspec->iblnkerrsnap;
			val -= ppd->cpspec->iblnkerrdelta;
			ग_लिखो_7322_creg_port(ppd, crp_iblinkerrrecov, val);
		पूर्ण
		अगर (ppd->cpspec->iblnkकरोwndelta) अणु
			val = पढ़ो_7322_creg32_port(ppd, crp_iblinkकरोwn);
			val += ppd->cpspec->iblnkकरोwndelta;
			ग_लिखो_7322_creg_port(ppd, crp_iblinkकरोwn, val);
		पूर्ण
		/*
		 * No need to save ibmalfdelta since IB perfcounters
		 * are cleared on driver reload.
		 */

		/* and disable counter ग_लिखोs */
		qib_ग_लिखो_kreg(dd, kr_hwdiagctrl, diagc);
	पूर्ण
पूर्ण

/**
 * qib_setup_7322_setextled - set the state of the two बाह्यal LEDs
 * @ppd: physical port on the qlogic_ib device
 * @on: whether the link is up or not
 *
 * The exact combo of LEDs अगर on is true is determined by looking
 * at the ibcstatus.
 *
 * These LEDs indicate the physical and logical state of IB link.
 * For this chip (at least with recommended board pinouts), LED1
 * is Yellow (logical state) and LED2 is Green (physical state),
 *
 * Note:  We try to match the Mellanox HCA LED behavior as best
 * we can.  Green indicates physical link state is OK (something is
 * plugged in, and we can train).
 * Amber indicates the link is logically up (ACTIVE).
 * Mellanox further blinks the amber LED to indicate data packet
 * activity, but we have no hardware support क्रम that, so it would
 * require waking up every 10-20 msecs and checking the counters
 * on the chip, and then turning the LED off अगर appropriate.  That's
 * visible overhead, so not something we will करो.
 */
अटल व्योम qib_setup_7322_setextled(काष्ठा qib_pportdata *ppd, u32 on)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 extctl, ledblink = 0, val;
	अचिन्हित दीर्घ flags;
	पूर्णांक yel, grn;

	/*
	 * The diags use the LED to indicate diag info, so we leave
	 * the बाह्यal LED alone when the diags are running.
	 */
	अगर (dd->diag_client)
		वापस;

	/* Allow override of LED display क्रम, e.g. Locating प्रणाली in rack */
	अगर (ppd->led_override) अणु
		grn = (ppd->led_override & QIB_LED_PHYS);
		yel = (ppd->led_override & QIB_LED_LOG);
	पूर्ण अन्यथा अगर (on) अणु
		val = qib_पढ़ो_kreg_port(ppd, krp_ibcstatus_a);
		grn = qib_7322_phys_portstate(val) ==
			IB_PHYSPORTSTATE_LINKUP;
		yel = qib_7322_iblink_state(val) == IB_PORT_ACTIVE;
	पूर्ण अन्यथा अणु
		grn = 0;
		yel = 0;
	पूर्ण

	spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
	extctl = dd->cspec->extctrl & (ppd->port == 1 ?
		~ExtLED_IB1_MASK : ~ExtLED_IB2_MASK);
	अगर (grn) अणु
		extctl |= ppd->port == 1 ? ExtLED_IB1_GRN : ExtLED_IB2_GRN;
		/*
		 * Counts are in chip घड़ी (4ns) periods.
		 * This is 1/16 sec (66.6ms) on,
		 * 3/16 sec (187.5 ms) off, with packets rcvd.
		 */
		ledblink = ((66600 * 1000UL / 4) << IBA7322_LEDBLINK_ON_SHIFT) |
			((187500 * 1000UL / 4) << IBA7322_LEDBLINK_OFF_SHIFT);
	पूर्ण
	अगर (yel)
		extctl |= ppd->port == 1 ? ExtLED_IB1_YEL : ExtLED_IB2_YEL;
	dd->cspec->extctrl = extctl;
	qib_ग_लिखो_kreg(dd, kr_extctrl, dd->cspec->extctrl);
	spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);

	अगर (ledblink) /* blink the LED on packet receive */
		qib_ग_लिखो_kreg_port(ppd, krp_rcvpktledcnt, ledblink);
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA

अटल पूर्णांक qib_7322_notअगरy_dca(काष्ठा qib_devdata *dd, अचिन्हित दीर्घ event)
अणु
	चयन (event) अणु
	हाल DCA_PROVIDER_ADD:
		अगर (dd->flags & QIB_DCA_ENABLED)
			अवरोध;
		अगर (!dca_add_requester(&dd->pcidev->dev)) अणु
			qib_devinfo(dd->pcidev, "DCA enabled\n");
			dd->flags |= QIB_DCA_ENABLED;
			qib_setup_dca(dd);
		पूर्ण
		अवरोध;
	हाल DCA_PROVIDER_REMOVE:
		अगर (dd->flags & QIB_DCA_ENABLED) अणु
			dca_हटाओ_requester(&dd->pcidev->dev);
			dd->flags &= ~QIB_DCA_ENABLED;
			dd->cspec->dca_ctrl = 0;
			qib_ग_लिखो_kreg(dd, KREG_IDX(DCACtrlA),
				dd->cspec->dca_ctrl);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qib_update_rhdrq_dca(काष्ठा qib_ctxtdata *rcd, पूर्णांक cpu)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	काष्ठा qib_chip_specअगरic *cspec = dd->cspec;

	अगर (!(dd->flags & QIB_DCA_ENABLED))
		वापस;
	अगर (cspec->rhdr_cpu[rcd->ctxt] != cpu) अणु
		स्थिर काष्ठा dca_reg_map *rmp;

		cspec->rhdr_cpu[rcd->ctxt] = cpu;
		rmp = &dca_rcvhdr_reg_map[rcd->ctxt];
		cspec->dca_rcvhdr_ctrl[rmp->shaकरोw_inx] &= rmp->mask;
		cspec->dca_rcvhdr_ctrl[rmp->shaकरोw_inx] |=
			(u64) dca3_get_tag(&dd->pcidev->dev, cpu) << rmp->lsb;
		qib_devinfo(dd->pcidev,
			"Ctxt %d cpu %d dca %llx\n", rcd->ctxt, cpu,
			(दीर्घ दीर्घ) cspec->dca_rcvhdr_ctrl[rmp->shaकरोw_inx]);
		qib_ग_लिखो_kreg(dd, rmp->regno,
			       cspec->dca_rcvhdr_ctrl[rmp->shaकरोw_inx]);
		cspec->dca_ctrl |= SYM_MASK(DCACtrlA, RcvHdrqDCAEnable);
		qib_ग_लिखो_kreg(dd, KREG_IDX(DCACtrlA), cspec->dca_ctrl);
	पूर्ण
पूर्ण

अटल व्योम qib_update_sdma_dca(काष्ठा qib_pportdata *ppd, पूर्णांक cpu)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	काष्ठा qib_chip_specअगरic *cspec = dd->cspec;
	अचिन्हित pidx = ppd->port - 1;

	अगर (!(dd->flags & QIB_DCA_ENABLED))
		वापस;
	अगर (cspec->sdma_cpu[pidx] != cpu) अणु
		cspec->sdma_cpu[pidx] = cpu;
		cspec->dca_rcvhdr_ctrl[4] &= ~(ppd->hw_pidx ?
			SYM_MASK(DCACtrlF, SendDma1DCAOPH) :
			SYM_MASK(DCACtrlF, SendDma0DCAOPH));
		cspec->dca_rcvhdr_ctrl[4] |=
			(u64) dca3_get_tag(&dd->pcidev->dev, cpu) <<
				(ppd->hw_pidx ?
					SYM_LSB(DCACtrlF, SendDma1DCAOPH) :
					SYM_LSB(DCACtrlF, SendDma0DCAOPH));
		qib_devinfo(dd->pcidev,
			"sdma %d cpu %d dca %llx\n", ppd->hw_pidx, cpu,
			(दीर्घ दीर्घ) cspec->dca_rcvhdr_ctrl[4]);
		qib_ग_लिखो_kreg(dd, KREG_IDX(DCACtrlF),
			       cspec->dca_rcvhdr_ctrl[4]);
		cspec->dca_ctrl |= ppd->hw_pidx ?
			SYM_MASK(DCACtrlA, SendDMAHead1DCAEnable) :
			SYM_MASK(DCACtrlA, SendDMAHead0DCAEnable);
		qib_ग_लिखो_kreg(dd, KREG_IDX(DCACtrlA), cspec->dca_ctrl);
	पूर्ण
पूर्ण

अटल व्योम qib_setup_dca(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_chip_specअगरic *cspec = dd->cspec;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cspec->rhdr_cpu); i++)
		cspec->rhdr_cpu[i] = -1;
	क्रम (i = 0; i < ARRAY_SIZE(cspec->sdma_cpu); i++)
		cspec->sdma_cpu[i] = -1;
	cspec->dca_rcvhdr_ctrl[0] =
		(1ULL << SYM_LSB(DCACtrlB, RcvHdrq0DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlB, RcvHdrq1DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlB, RcvHdrq2DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlB, RcvHdrq3DCAXfrCnt));
	cspec->dca_rcvhdr_ctrl[1] =
		(1ULL << SYM_LSB(DCACtrlC, RcvHdrq4DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlC, RcvHdrq5DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlC, RcvHdrq6DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlC, RcvHdrq7DCAXfrCnt));
	cspec->dca_rcvhdr_ctrl[2] =
		(1ULL << SYM_LSB(DCACtrlD, RcvHdrq8DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlD, RcvHdrq9DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlD, RcvHdrq10DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlD, RcvHdrq11DCAXfrCnt));
	cspec->dca_rcvhdr_ctrl[3] =
		(1ULL << SYM_LSB(DCACtrlE, RcvHdrq12DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlE, RcvHdrq13DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlE, RcvHdrq14DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlE, RcvHdrq15DCAXfrCnt));
	cspec->dca_rcvhdr_ctrl[4] =
		(1ULL << SYM_LSB(DCACtrlF, RcvHdrq16DCAXfrCnt)) |
		(1ULL << SYM_LSB(DCACtrlF, RcvHdrq17DCAXfrCnt));
	क्रम (i = 0; i < ARRAY_SIZE(cspec->sdma_cpu); i++)
		qib_ग_लिखो_kreg(dd, KREG_IDX(DCACtrlB) + i,
			       cspec->dca_rcvhdr_ctrl[i]);
	क्रम (i = 0; i < cspec->num_msix_entries; i++)
		setup_dca_notअगरier(dd, i);
पूर्ण

अटल व्योम qib_irq_notअगरier_notअगरy(काष्ठा irq_affinity_notअगरy *notअगरy,
			     स्थिर cpumask_t *mask)
अणु
	काष्ठा qib_irq_notअगरy *n =
		container_of(notअगरy, काष्ठा qib_irq_notअगरy, notअगरy);
	पूर्णांक cpu = cpumask_first(mask);

	अगर (n->rcv) अणु
		काष्ठा qib_ctxtdata *rcd = (काष्ठा qib_ctxtdata *)n->arg;

		qib_update_rhdrq_dca(rcd, cpu);
	पूर्ण अन्यथा अणु
		काष्ठा qib_pportdata *ppd = (काष्ठा qib_pportdata *)n->arg;

		qib_update_sdma_dca(ppd, cpu);
	पूर्ण
पूर्ण

अटल व्योम qib_irq_notअगरier_release(काष्ठा kref *ref)
अणु
	काष्ठा qib_irq_notअगरy *n =
		container_of(ref, काष्ठा qib_irq_notअगरy, notअगरy.kref);
	काष्ठा qib_devdata *dd;

	अगर (n->rcv) अणु
		काष्ठा qib_ctxtdata *rcd = (काष्ठा qib_ctxtdata *)n->arg;

		dd = rcd->dd;
	पूर्ण अन्यथा अणु
		काष्ठा qib_pportdata *ppd = (काष्ठा qib_pportdata *)n->arg;

		dd = ppd->dd;
	पूर्ण
	qib_devinfo(dd->pcidev,
		"release on HCA notify 0x%p n 0x%p\n", ref, n);
	kमुक्त(n);
पूर्ण
#पूर्ण_अगर

अटल व्योम qib_7322_मुक्त_irq(काष्ठा qib_devdata *dd)
अणु
	u64 पूर्णांकgranted;
	पूर्णांक i;

	dd->cspec->मुख्य_पूर्णांक_mask = ~0ULL;

	क्रम (i = 0; i < dd->cspec->num_msix_entries; i++) अणु
		/* only मुक्त IRQs that were allocated */
		अगर (dd->cspec->msix_entries[i].arg) अणु
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
			reset_dca_notअगरier(dd, i);
#पूर्ण_अगर
			irq_set_affinity_hपूर्णांक(pci_irq_vector(dd->pcidev, i),
					      शून्य);
			मुक्त_cpumask_var(dd->cspec->msix_entries[i].mask);
			pci_मुक्त_irq(dd->pcidev, i,
				     dd->cspec->msix_entries[i].arg);
		पूर्ण
	पूर्ण

	/* If num_msix_entries was 0, disable the INTx IRQ */
	अगर (!dd->cspec->num_msix_entries)
		pci_मुक्त_irq(dd->pcidev, 0, dd);
	अन्यथा
		dd->cspec->num_msix_entries = 0;

	pci_मुक्त_irq_vectors(dd->pcidev);

	/* make sure no MSIx पूर्णांकerrupts are left pending */
	पूर्णांकgranted = qib_पढ़ो_kreg64(dd, kr_पूर्णांकgranted);
	अगर (पूर्णांकgranted)
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकgranted, पूर्णांकgranted);
पूर्ण

अटल व्योम qib_setup_7322_cleanup(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	अगर (dd->flags & QIB_DCA_ENABLED) अणु
		dca_हटाओ_requester(&dd->pcidev->dev);
		dd->flags &= ~QIB_DCA_ENABLED;
		dd->cspec->dca_ctrl = 0;
		qib_ग_लिखो_kreg(dd, KREG_IDX(DCACtrlA), dd->cspec->dca_ctrl);
	पूर्ण
#पूर्ण_अगर

	qib_7322_मुक्त_irq(dd);
	kमुक्त(dd->cspec->cntrs);
	kमुक्त(dd->cspec->sendchkenable);
	kमुक्त(dd->cspec->sendgrhchk);
	kमुक्त(dd->cspec->sendibchk);
	kमुक्त(dd->cspec->msix_entries);
	क्रम (i = 0; i < dd->num_pports; i++) अणु
		अचिन्हित दीर्घ flags;
		u32 mask = QSFP_GPIO_MOD_PRS_N |
			(QSFP_GPIO_MOD_PRS_N << QSFP_GPIO_PORT2_SHIFT);

		kमुक्त(dd->pport[i].cpspec->portcntrs);
		अगर (dd->flags & QIB_HAS_QSFP) अणु
			spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
			dd->cspec->gpio_mask &= ~mask;
			qib_ग_लिखो_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
			spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

/* handle SDMA पूर्णांकerrupts */
अटल व्योम sdma_7322_पूर्णांकr(काष्ठा qib_devdata *dd, u64 istat)
अणु
	काष्ठा qib_pportdata *ppd0 = &dd->pport[0];
	काष्ठा qib_pportdata *ppd1 = &dd->pport[1];
	u64 पूर्णांकr0 = istat & (INT_MASK_P(SDma, 0) |
		INT_MASK_P(SDmaIdle, 0) | INT_MASK_P(SDmaProgress, 0));
	u64 पूर्णांकr1 = istat & (INT_MASK_P(SDma, 1) |
		INT_MASK_P(SDmaIdle, 1) | INT_MASK_P(SDmaProgress, 1));

	अगर (पूर्णांकr0)
		qib_sdma_पूर्णांकr(ppd0);
	अगर (पूर्णांकr1)
		qib_sdma_पूर्णांकr(ppd1);

	अगर (istat & INT_MASK_PM(SDmaCleanupDone, 0))
		qib_sdma_process_event(ppd0, qib_sdma_event_e20_hw_started);
	अगर (istat & INT_MASK_PM(SDmaCleanupDone, 1))
		qib_sdma_process_event(ppd1, qib_sdma_event_e20_hw_started);
पूर्ण

/*
 * Set or clear the Send buffer available पूर्णांकerrupt enable bit.
 */
अटल व्योम qib_wantpiobuf_7322_पूर्णांकr(काष्ठा qib_devdata *dd, u32 needपूर्णांक)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);
	अगर (needपूर्णांक)
		dd->sendctrl |= SYM_MASK(SendCtrl, SendIntBufAvail);
	अन्यथा
		dd->sendctrl &= ~SYM_MASK(SendCtrl, SendIntBufAvail);
	qib_ग_लिखो_kreg(dd, kr_sendctrl, dd->sendctrl);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
पूर्ण

/*
 * Somehow got an पूर्णांकerrupt with reserved bits set in पूर्णांकerrupt status.
 * Prपूर्णांक a message so we know it happened, then clear them.
 * keep मुख्यline पूर्णांकerrupt handler cache-मित्रly
 */
अटल noअंतरभूत व्योम unknown_7322_ibits(काष्ठा qib_devdata *dd, u64 istat)
अणु
	u64 समाप्तs;
	अक्षर msg[128];

	समाप्तs = istat & ~QIB_I_BITSEXTANT;
	qib_dev_err(dd,
		"Clearing reserved interrupt(s) 0x%016llx: %s\n",
		(अचिन्हित दीर्घ दीर्घ) समाप्तs, msg);
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकmask, (dd->cspec->पूर्णांक_enable_mask & ~समाप्तs));
पूर्ण

/* keep मुख्यline पूर्णांकerrupt handler cache-मित्रly */
अटल noअंतरभूत व्योम unknown_7322_gpio_पूर्णांकr(काष्ठा qib_devdata *dd)
अणु
	u32 gpiostatus;
	पूर्णांक handled = 0;
	पूर्णांक pidx;

	/*
	 * Boards क्रम this chip currently करोn't use GPIO पूर्णांकerrupts,
	 * so clear by writing GPIOstatus to GPIOclear, and complain
	 * to developer.  To aव्योम endless repeats, clear
	 * the bits in the mask, since there is some kind of
	 * programming error or chip problem.
	 */
	gpiostatus = qib_पढ़ो_kreg32(dd, kr_gpio_status);
	/*
	 * In theory, writing GPIOstatus to GPIOclear could
	 * have a bad side-effect on some diagnostic that wanted
	 * to poll क्रम a status-change, but the various shaकरोws
	 * make that problematic at best. Diags will just suppress
	 * all GPIO पूर्णांकerrupts during such tests.
	 */
	qib_ग_लिखो_kreg(dd, kr_gpio_clear, gpiostatus);
	/*
	 * Check क्रम QSFP MOD_PRS changes
	 * only works क्रम single port अगर IB1 != pidx1
	 */
	क्रम (pidx = 0; pidx < dd->num_pports && (dd->flags & QIB_HAS_QSFP);
	     ++pidx) अणु
		काष्ठा qib_pportdata *ppd;
		काष्ठा qib_qsfp_data *qd;
		u32 mask;

		अगर (!dd->pport[pidx].link_speed_supported)
			जारी;
		mask = QSFP_GPIO_MOD_PRS_N;
		ppd = dd->pport + pidx;
		mask <<= (QSFP_GPIO_PORT2_SHIFT * ppd->hw_pidx);
		अगर (gpiostatus & dd->cspec->gpio_mask & mask) अणु
			u64 pins;

			qd = &ppd->cpspec->qsfp_data;
			gpiostatus &= ~mask;
			pins = qib_पढ़ो_kreg64(dd, kr_extstatus);
			pins >>= SYM_LSB(EXTStatus, GPIOIn);
			अगर (!(pins & mask)) अणु
				++handled;
				qd->t_insert = jअगरfies;
				queue_work(ib_wq, &qd->work);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (gpiostatus && !handled) अणु
		स्थिर u32 mask = qib_पढ़ो_kreg32(dd, kr_gpio_mask);
		u32 gpio_irq = mask & gpiostatus;

		/*
		 * Clear any troublemakers, and update chip from shaकरोw
		 */
		dd->cspec->gpio_mask &= ~gpio_irq;
		qib_ग_लिखो_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
	पूर्ण
पूर्ण

/*
 * Handle errors and unusual events first, separate function
 * to improve cache hits क्रम fast path पूर्णांकerrupt handling.
 */
अटल noअंतरभूत व्योम unlikely_7322_पूर्णांकr(काष्ठा qib_devdata *dd, u64 istat)
अणु
	अगर (istat & ~QIB_I_BITSEXTANT)
		unknown_7322_ibits(dd, istat);
	अगर (istat & QIB_I_GPIO)
		unknown_7322_gpio_पूर्णांकr(dd);
	अगर (istat & QIB_I_C_ERROR) अणु
		qib_ग_लिखो_kreg(dd, kr_errmask, 0ULL);
		tasklet_schedule(&dd->error_tasklet);
	पूर्ण
	अगर (istat & INT_MASK_P(Err, 0) && dd->rcd[0])
		handle_7322_p_errors(dd->rcd[0]->ppd);
	अगर (istat & INT_MASK_P(Err, 1) && dd->rcd[1])
		handle_7322_p_errors(dd->rcd[1]->ppd);
पूर्ण

/*
 * Dynamically adjust the rcv पूर्णांक समयout क्रम a context based on incoming
 * packet rate.
 */
अटल व्योम adjust_rcv_समयout(काष्ठा qib_ctxtdata *rcd, पूर्णांक npkts)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	u32 समयout = dd->cspec->rcvavail_समयout[rcd->ctxt];

	/*
	 * Dynamically adjust idle समयout on chip
	 * based on number of packets processed.
	 */
	अगर (npkts < rcv_पूर्णांक_count && समयout > 2)
		समयout >>= 1;
	अन्यथा अगर (npkts >= rcv_पूर्णांक_count && समयout < rcv_पूर्णांक_समयout)
		समयout = min(समयout << 1, rcv_पूर्णांक_समयout);
	अन्यथा
		वापस;

	dd->cspec->rcvavail_समयout[rcd->ctxt] = समयout;
	qib_ग_लिखो_kreg(dd, kr_rcvavailसमयout + rcd->ctxt, समयout);
पूर्ण

/*
 * This is the मुख्य पूर्णांकerrupt handler.
 * It will normally only be used क्रम low frequency पूर्णांकerrupts but may
 * have to handle all पूर्णांकerrupts अगर INTx is enabled or fewer than normal
 * MSIx पूर्णांकerrupts were allocated.
 * This routine should ignore the पूर्णांकerrupt bits क्रम any of the
 * dedicated MSIx handlers.
 */
अटल irqवापस_t qib_7322पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_devdata *dd = data;
	irqवापस_t ret;
	u64 istat;
	u64 ctxtrbits;
	u64 rmask;
	अचिन्हित i;
	u32 npkts;

	अगर ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT) अणु
		/*
		 * This वापस value is not great, but we करो not want the
		 * पूर्णांकerrupt core code to हटाओ our पूर्णांकerrupt handler
		 * because we करोn't appear to be handling an पूर्णांकerrupt
		 * during a chip reset.
		 */
		ret = IRQ_HANDLED;
		जाओ bail;
	पूर्ण

	istat = qib_पढ़ो_kreg64(dd, kr_पूर्णांकstatus);

	अगर (unlikely(istat == ~0ULL)) अणु
		qib_bad_पूर्णांकrstatus(dd);
		qib_dev_err(dd, "Interrupt status all f's, skipping\n");
		/* करोn't know अगर it was our पूर्णांकerrupt or not */
		ret = IRQ_NONE;
		जाओ bail;
	पूर्ण

	istat &= dd->cspec->मुख्य_पूर्णांक_mask;
	अगर (unlikely(!istat)) अणु
		/* alपढ़ोy handled, or shared and not us */
		ret = IRQ_NONE;
		जाओ bail;
	पूर्ण

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* handle "errors" of various kinds first, device ahead of port */
	अगर (unlikely(istat & (~QIB_I_BITSEXTANT | QIB_I_GPIO |
			      QIB_I_C_ERROR | INT_MASK_P(Err, 0) |
			      INT_MASK_P(Err, 1))))
		unlikely_7322_पूर्णांकr(dd, istat);

	/*
	 * Clear the पूर्णांकerrupt bits we found set, relatively early, so we
	 * "know" know the chip will have seen this by the समय we process
	 * the queue, and will re-पूर्णांकerrupt अगर necessary.  The processor
	 * itself won't take the पूर्णांकerrupt again until we वापस.
	 */
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, istat);

	/*
	 * Handle kernel receive queues beक्रमe checking क्रम pio buffers
	 * available since receives can overflow; piobuf रुकोers can afक्रमd
	 * a few extra cycles, since they were रुकोing anyway.
	 */
	ctxtrbits = istat & (QIB_I_RCVAVAIL_MASK | QIB_I_RCVURG_MASK);
	अगर (ctxtrbits) अणु
		rmask = (1ULL << QIB_I_RCVAVAIL_LSB) |
			(1ULL << QIB_I_RCVURG_LSB);
		क्रम (i = 0; i < dd->first_user_ctxt; i++) अणु
			अगर (ctxtrbits & rmask) अणु
				ctxtrbits &= ~rmask;
				अगर (dd->rcd[i])
					qib_kreceive(dd->rcd[i], शून्य, &npkts);
			पूर्ण
			rmask <<= 1;
		पूर्ण
		अगर (ctxtrbits) अणु
			ctxtrbits = (ctxtrbits >> QIB_I_RCVAVAIL_LSB) |
				(ctxtrbits >> QIB_I_RCVURG_LSB);
			qib_handle_urcv(dd, ctxtrbits);
		पूर्ण
	पूर्ण

	अगर (istat & (QIB_I_P_SDMAINT(0) | QIB_I_P_SDMAINT(1)))
		sdma_7322_पूर्णांकr(dd, istat);

	अगर ((istat & QIB_I_SPIOBUFAVAIL) && (dd->flags & QIB_INITTED))
		qib_ib_piobufavail(dd);

	ret = IRQ_HANDLED;
bail:
	वापस ret;
पूर्ण

/*
 * Dedicated receive packet available पूर्णांकerrupt handler.
 */
अटल irqवापस_t qib_7322pपूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_ctxtdata *rcd = data;
	काष्ठा qib_devdata *dd = rcd->dd;
	u32 npkts;

	अगर ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT)
		/*
		 * This वापस value is not great, but we करो not want the
		 * पूर्णांकerrupt core code to हटाओ our पूर्णांकerrupt handler
		 * because we करोn't appear to be handling an पूर्णांकerrupt
		 * during a chip reset.
		 */
		वापस IRQ_HANDLED;

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* Clear the पूर्णांकerrupt bit we expect to be set. */
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, ((1ULL << QIB_I_RCVAVAIL_LSB) |
		       (1ULL << QIB_I_RCVURG_LSB)) << rcd->ctxt);

	qib_kreceive(rcd, शून्य, &npkts);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Dedicated Send buffer available पूर्णांकerrupt handler.
 */
अटल irqवापस_t qib_7322bufavail(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_devdata *dd = data;

	अगर ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT)
		/*
		 * This वापस value is not great, but we करो not want the
		 * पूर्णांकerrupt core code to हटाओ our पूर्णांकerrupt handler
		 * because we करोn't appear to be handling an पूर्णांकerrupt
		 * during a chip reset.
		 */
		वापस IRQ_HANDLED;

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* Clear the पूर्णांकerrupt bit we expect to be set. */
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, QIB_I_SPIOBUFAVAIL);

	/* qib_ib_piobufavail() will clear the want PIO पूर्णांकerrupt अगर needed */
	अगर (dd->flags & QIB_INITTED)
		qib_ib_piobufavail(dd);
	अन्यथा
		qib_wantpiobuf_7322_पूर्णांकr(dd, 0);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Dedicated Send DMA पूर्णांकerrupt handler.
 */
अटल irqवापस_t sdma_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_pportdata *ppd = data;
	काष्ठा qib_devdata *dd = ppd->dd;

	अगर ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT)
		/*
		 * This वापस value is not great, but we करो not want the
		 * पूर्णांकerrupt core code to हटाओ our पूर्णांकerrupt handler
		 * because we करोn't appear to be handling an पूर्णांकerrupt
		 * during a chip reset.
		 */
		वापस IRQ_HANDLED;

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* Clear the पूर्णांकerrupt bit we expect to be set. */
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, ppd->hw_pidx ?
		       INT_MASK_P(SDma, 1) : INT_MASK_P(SDma, 0));
	qib_sdma_पूर्णांकr(ppd);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Dedicated Send DMA idle पूर्णांकerrupt handler.
 */
अटल irqवापस_t sdma_idle_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_pportdata *ppd = data;
	काष्ठा qib_devdata *dd = ppd->dd;

	अगर ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT)
		/*
		 * This वापस value is not great, but we करो not want the
		 * पूर्णांकerrupt core code to हटाओ our पूर्णांकerrupt handler
		 * because we करोn't appear to be handling an पूर्णांकerrupt
		 * during a chip reset.
		 */
		वापस IRQ_HANDLED;

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* Clear the पूर्णांकerrupt bit we expect to be set. */
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, ppd->hw_pidx ?
		       INT_MASK_P(SDmaIdle, 1) : INT_MASK_P(SDmaIdle, 0));
	qib_sdma_पूर्णांकr(ppd);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Dedicated Send DMA progress पूर्णांकerrupt handler.
 */
अटल irqवापस_t sdma_progress_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_pportdata *ppd = data;
	काष्ठा qib_devdata *dd = ppd->dd;

	अगर ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT)
		/*
		 * This वापस value is not great, but we करो not want the
		 * पूर्णांकerrupt core code to हटाओ our पूर्णांकerrupt handler
		 * because we करोn't appear to be handling an पूर्णांकerrupt
		 * during a chip reset.
		 */
		वापस IRQ_HANDLED;

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* Clear the पूर्णांकerrupt bit we expect to be set. */
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, ppd->hw_pidx ?
		       INT_MASK_P(SDmaProgress, 1) :
		       INT_MASK_P(SDmaProgress, 0));
	qib_sdma_पूर्णांकr(ppd);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Dedicated Send DMA cleanup पूर्णांकerrupt handler.
 */
अटल irqवापस_t sdma_cleanup_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_pportdata *ppd = data;
	काष्ठा qib_devdata *dd = ppd->dd;

	अगर ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT)
		/*
		 * This वापस value is not great, but we करो not want the
		 * पूर्णांकerrupt core code to हटाओ our पूर्णांकerrupt handler
		 * because we करोn't appear to be handling an पूर्णांकerrupt
		 * during a chip reset.
		 */
		वापस IRQ_HANDLED;

	this_cpu_inc(*dd->पूर्णांक_counter);

	/* Clear the पूर्णांकerrupt bit we expect to be set. */
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, ppd->hw_pidx ?
		       INT_MASK_PM(SDmaCleanupDone, 1) :
		       INT_MASK_PM(SDmaCleanupDone, 0));
	qib_sdma_process_event(ppd, qib_sdma_event_e20_hw_started);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA

अटल व्योम reset_dca_notअगरier(काष्ठा qib_devdata *dd, पूर्णांक msixnum)
अणु
	अगर (!dd->cspec->msix_entries[msixnum].dca)
		वापस;

	qib_devinfo(dd->pcidev, "Disabling notifier on HCA %d irq %d\n",
		    dd->unit, pci_irq_vector(dd->pcidev, msixnum));
	irq_set_affinity_notअगरier(pci_irq_vector(dd->pcidev, msixnum), शून्य);
	dd->cspec->msix_entries[msixnum].notअगरier = शून्य;
पूर्ण

अटल व्योम setup_dca_notअगरier(काष्ठा qib_devdata *dd, पूर्णांक msixnum)
अणु
	काष्ठा qib_msix_entry *m = &dd->cspec->msix_entries[msixnum];
	काष्ठा qib_irq_notअगरy *n;

	अगर (!m->dca)
		वापस;
	n = kzalloc(माप(*n), GFP_KERNEL);
	अगर (n) अणु
		पूर्णांक ret;

		m->notअगरier = n;
		n->notअगरy.irq = pci_irq_vector(dd->pcidev, msixnum);
		n->notअगरy.notअगरy = qib_irq_notअगरier_notअगरy;
		n->notअगरy.release = qib_irq_notअगरier_release;
		n->arg = m->arg;
		n->rcv = m->rcv;
		qib_devinfo(dd->pcidev,
			"set notifier irq %d rcv %d notify %p\n",
			n->notअगरy.irq, n->rcv, &n->notअगरy);
		ret = irq_set_affinity_notअगरier(
				n->notअगरy.irq,
				&n->notअगरy);
		अगर (ret) अणु
			m->notअगरier = शून्य;
			kमुक्त(n);
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर

/*
 * Set up our chip-specअगरic पूर्णांकerrupt handler.
 * The पूर्णांकerrupt type has alपढ़ोy been setup, so
 * we just need to करो the registration and error checking.
 * If we are using MSIx पूर्णांकerrupts, we may fall back to
 * INTx later, अगर the पूर्णांकerrupt handler करोesn't get called
 * within 1/2 second (see verअगरy_पूर्णांकerrupt()).
 */
अटल व्योम qib_setup_7322_पूर्णांकerrupt(काष्ठा qib_devdata *dd, पूर्णांक clearpend)
अणु
	पूर्णांक ret, i, msixnum;
	u64 redirect[6];
	u64 mask;
	स्थिर काष्ठा cpumask *local_mask;
	पूर्णांक firstcpu, secondcpu = 0, currrcvcpu = 0;

	अगर (!dd->num_pports)
		वापस;

	अगर (clearpend) अणु
		/*
		 * अगर not चयनing पूर्णांकerrupt types, be sure पूर्णांकerrupts are
		 * disabled, and then clear anything pending at this poपूर्णांक,
		 * because we are starting clean.
		 */
		qib_7322_set_पूर्णांकr_state(dd, 0);

		/* clear the reset error, init error/hwerror mask */
		qib_7322_init_hwerrors(dd);

		/* clear any पूर्णांकerrupt bits that might be set */
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, ~0ULL);

		/* make sure no pending MSIx पूर्णांकr, and clear diag reg */
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकgranted, ~0ULL);
		qib_ग_लिखो_kreg(dd, kr_vecclr_wo_पूर्णांक, ~0ULL);
	पूर्ण

	अगर (!dd->cspec->num_msix_entries) अणु
		/* Try to get INTx पूर्णांकerrupt */
try_पूर्णांकx:
		ret = pci_request_irq(dd->pcidev, 0, qib_7322पूर्णांकr, शून्य, dd,
				      QIB_DRV_NAME);
		अगर (ret) अणु
			qib_dev_err(
				dd,
				"Couldn't setup INTx interrupt (irq=%d): %d\n",
				pci_irq_vector(dd->pcidev, 0), ret);
			वापस;
		पूर्ण
		dd->cspec->मुख्य_पूर्णांक_mask = ~0ULL;
		वापस;
	पूर्ण

	/* Try to get MSIx पूर्णांकerrupts */
	स_रखो(redirect, 0, माप(redirect));
	mask = ~0ULL;
	msixnum = 0;
	local_mask = cpumask_of_pcibus(dd->pcidev->bus);
	firstcpu = cpumask_first(local_mask);
	अगर (firstcpu >= nr_cpu_ids ||
			cpumask_weight(local_mask) == num_online_cpus()) अणु
		local_mask = topology_core_cpumask(0);
		firstcpu = cpumask_first(local_mask);
	पूर्ण
	अगर (firstcpu < nr_cpu_ids) अणु
		secondcpu = cpumask_next(firstcpu, local_mask);
		अगर (secondcpu >= nr_cpu_ids)
			secondcpu = firstcpu;
		currrcvcpu = secondcpu;
	पूर्ण
	क्रम (i = 0; msixnum < dd->cspec->num_msix_entries; i++) अणु
		irq_handler_t handler;
		व्योम *arg;
		पूर्णांक lsb, reg, sh;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
		पूर्णांक dca = 0;
#पूर्ण_अगर
		अगर (i < ARRAY_SIZE(irq_table)) अणु
			अगर (irq_table[i].port) अणु
				/* skip अगर क्रम a non-configured port */
				अगर (irq_table[i].port > dd->num_pports)
					जारी;
				arg = dd->pport + irq_table[i].port - 1;
			पूर्ण अन्यथा
				arg = dd;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
			dca = irq_table[i].dca;
#पूर्ण_अगर
			lsb = irq_table[i].lsb;
			handler = irq_table[i].handler;
			ret = pci_request_irq(dd->pcidev, msixnum, handler,
					      शून्य, arg, QIB_DRV_NAME "%d%s",
					      dd->unit,
					      irq_table[i].name);
		पूर्ण अन्यथा अणु
			अचिन्हित ctxt;

			ctxt = i - ARRAY_SIZE(irq_table);
			/* per krcvq context receive पूर्णांकerrupt */
			arg = dd->rcd[ctxt];
			अगर (!arg)
				जारी;
			अगर (qib_krcvq01_no_msi && ctxt < 2)
				जारी;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
			dca = 1;
#पूर्ण_अगर
			lsb = QIB_I_RCVAVAIL_LSB + ctxt;
			handler = qib_7322pपूर्णांकr;
			ret = pci_request_irq(dd->pcidev, msixnum, handler,
					      शून्य, arg,
					      QIB_DRV_NAME "%d (kctx)",
					      dd->unit);
		पूर्ण

		अगर (ret) अणु
			/*
			 * Shouldn't happen since the enable said we could
			 * have as many as we are trying to setup here.
			 */
			qib_dev_err(dd,
				    "Couldn't setup MSIx interrupt (vec=%d, irq=%d): %d\n",
				    msixnum,
				    pci_irq_vector(dd->pcidev, msixnum),
				    ret);
			qib_7322_मुक्त_irq(dd);
			pci_alloc_irq_vectors(dd->pcidev, 1, 1,
					      PCI_IRQ_LEGACY);
			जाओ try_पूर्णांकx;
		पूर्ण
		dd->cspec->msix_entries[msixnum].arg = arg;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
		dd->cspec->msix_entries[msixnum].dca = dca;
		dd->cspec->msix_entries[msixnum].rcv =
			handler == qib_7322pपूर्णांकr;
#पूर्ण_अगर
		अगर (lsb >= 0) अणु
			reg = lsb / IBA7322_REसूचीECT_VEC_PER_REG;
			sh = (lsb % IBA7322_REसूचीECT_VEC_PER_REG) *
				SYM_LSB(IntRedirect0, vec1);
			mask &= ~(1ULL << lsb);
			redirect[reg] |= ((u64) msixnum) << sh;
		पूर्ण
		qib_पढ़ो_kreg64(dd, 2 * msixnum + 1 +
				(QIB_7322_MsixTable_OFFS / माप(u64)));
		अगर (firstcpu < nr_cpu_ids &&
			zalloc_cpumask_var(
				&dd->cspec->msix_entries[msixnum].mask,
				GFP_KERNEL)) अणु
			अगर (handler == qib_7322pपूर्णांकr) अणु
				cpumask_set_cpu(currrcvcpu,
					dd->cspec->msix_entries[msixnum].mask);
				currrcvcpu = cpumask_next(currrcvcpu,
					local_mask);
				अगर (currrcvcpu >= nr_cpu_ids)
					currrcvcpu = secondcpu;
			पूर्ण अन्यथा अणु
				cpumask_set_cpu(firstcpu,
					dd->cspec->msix_entries[msixnum].mask);
			पूर्ण
			irq_set_affinity_hपूर्णांक(
				pci_irq_vector(dd->pcidev, msixnum),
				dd->cspec->msix_entries[msixnum].mask);
		पूर्ण
		msixnum++;
	पूर्ण
	/* Initialize the vector mapping */
	क्रम (i = 0; i < ARRAY_SIZE(redirect); i++)
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकredirect + i, redirect[i]);
	dd->cspec->मुख्य_पूर्णांक_mask = mask;
	tasklet_setup(&dd->error_tasklet, qib_error_tasklet);
पूर्ण

/**
 * qib_7322_boardname - fill in the board name and note features
 * @dd: the qlogic_ib device
 *
 * info will be based on the board revision रेजिस्टर
 */
अटल अचिन्हित qib_7322_boardname(काष्ठा qib_devdata *dd)
अणु
	/* Will need क्रमागतeration of board-types here */
	u32 boardid;
	अचिन्हित पूर्णांक features = DUAL_PORT_CAP;

	boardid = SYM_FIELD(dd->revision, Revision, BoardID);

	चयन (boardid) अणु
	हाल 0:
		dd->boardname = "InfiniPath_QLE7342_Emulation";
		अवरोध;
	हाल 1:
		dd->boardname = "InfiniPath_QLE7340";
		dd->flags |= QIB_HAS_QSFP;
		features = PORT_SPD_CAP;
		अवरोध;
	हाल 2:
		dd->boardname = "InfiniPath_QLE7342";
		dd->flags |= QIB_HAS_QSFP;
		अवरोध;
	हाल 3:
		dd->boardname = "InfiniPath_QMI7342";
		अवरोध;
	हाल 4:
		dd->boardname = "InfiniPath_Unsupported7342";
		qib_dev_err(dd, "Unsupported version of QMH7342\n");
		features = 0;
		अवरोध;
	हाल BOARD_QMH7342:
		dd->boardname = "InfiniPath_QMH7342";
		features = 0x24;
		अवरोध;
	हाल BOARD_QME7342:
		dd->boardname = "InfiniPath_QME7342";
		अवरोध;
	हाल 8:
		dd->boardname = "InfiniPath_QME7362";
		dd->flags |= QIB_HAS_QSFP;
		अवरोध;
	हाल BOARD_QMH7360:
		dd->boardname = "Intel IB QDR 1P FLR-QSFP Adptr";
		dd->flags |= QIB_HAS_QSFP;
		अवरोध;
	हाल 15:
		dd->boardname = "InfiniPath_QLE7342_TEST";
		dd->flags |= QIB_HAS_QSFP;
		अवरोध;
	शेष:
		dd->boardname = "InfiniPath_QLE73xy_UNKNOWN";
		qib_dev_err(dd, "Unknown 7322 board type %u\n", boardid);
		अवरोध;
	पूर्ण
	dd->board_atten = 1; /* index पूर्णांकo txdds_Xdr */

	snम_लिखो(dd->boardversion, माप(dd->boardversion),
		 "ChipABI %u.%u, %s, InfiniPath%u %u.%u, SW Compat %u\n",
		 QIB_CHIP_VERS_MAJ, QIB_CHIP_VERS_MIN, dd->boardname,
		 (अचिन्हित पूर्णांक)SYM_FIELD(dd->revision, Revision_R, Arch),
		 dd->majrev, dd->minrev,
		 (अचिन्हित पूर्णांक)SYM_FIELD(dd->revision, Revision_R, SW));

	अगर (qib_singleport && (features >> PORT_SPD_CAP_SHIFT) & PORT_SPD_CAP) अणु
		qib_devinfo(dd->pcidev,
			    "IB%u: Forced to single port mode by module parameter\n",
			    dd->unit);
		features &= PORT_SPD_CAP;
	पूर्ण

	वापस features;
पूर्ण

/*
 * This routine sleeps, so it can only be called from user context, not
 * from पूर्णांकerrupt context.
 */
अटल पूर्णांक qib_करो_7322_reset(काष्ठा qib_devdata *dd)
अणु
	u64 val;
	u64 *msix_vecsave = शून्य;
	पूर्णांक i, msix_entries, ret = 1;
	u16 cmdval;
	u8 पूर्णांक_line, clinesz;
	अचिन्हित दीर्घ flags;

	/* Use dev_err so it shows up in logs, etc. */
	qib_dev_err(dd, "Resetting InfiniPath unit %u\n", dd->unit);

	qib_pcie_अ_लोmd(dd, &cmdval, &पूर्णांक_line, &clinesz);

	msix_entries = dd->cspec->num_msix_entries;

	/* no पूर्णांकerrupts till re-initted */
	qib_7322_set_पूर्णांकr_state(dd, 0);

	qib_7322_मुक्त_irq(dd);

	अगर (msix_entries) अणु
		/* can be up to 512 bytes, too big क्रम stack */
		msix_vecsave = kदो_स्मृति_array(2 * dd->cspec->num_msix_entries,
					     माप(u64),
					     GFP_KERNEL);
	पूर्ण

	/*
	 * Core PCI (as of 2.6.18) करोesn't save or reग_लिखो the full vector
	 * info that is set up by the BIOS, so we have to save and restore
	 * it ourselves.   There is some risk something could change it,
	 * after we save it, but since we have disabled the MSIx, it
	 * shouldn't be touched...
	 */
	क्रम (i = 0; i < msix_entries; i++) अणु
		u64 vecaddr, vecdata;

		vecaddr = qib_पढ़ो_kreg64(dd, 2 * i +
				  (QIB_7322_MsixTable_OFFS / माप(u64)));
		vecdata = qib_पढ़ो_kreg64(dd, 1 + 2 * i +
				  (QIB_7322_MsixTable_OFFS / माप(u64)));
		अगर (msix_vecsave) अणु
			msix_vecsave[2 * i] = vecaddr;
			/* save it without the masked bit set */
			msix_vecsave[1 + 2 * i] = vecdata & ~0x100000000ULL;
		पूर्ण
	पूर्ण

	dd->pport->cpspec->ibdeltainprog = 0;
	dd->pport->cpspec->ibsymdelta = 0;
	dd->pport->cpspec->iblnkerrdelta = 0;
	dd->pport->cpspec->ibmalfdelta = 0;
	/* so we check पूर्णांकerrupts work again */
	dd->z_पूर्णांक_counter = qib_पूर्णांक_counter(dd);

	/*
	 * Keep chip from being accessed until we are पढ़ोy.  Use
	 * ग_लिखोq() directly, to allow the ग_लिखो even though QIB_PRESENT
	 * isn't set.
	 */
	dd->flags &= ~(QIB_INITTED | QIB_PRESENT | QIB_BADINTR);
	dd->flags |= QIB_DOING_RESET;
	val = dd->control | QLOGIC_IB_C_RESET;
	ग_लिखोq(val, &dd->kregbase[kr_control]);

	क्रम (i = 1; i <= 5; i++) अणु
		/*
		 * Allow MBIST, etc. to complete; दीर्घer on each retry.
		 * We someबार get machine checks from bus समयout अगर no
		 * response, so क्रम now, make it *really* दीर्घ.
		 */
		msleep(1000 + (1 + i) * 3000);

		qib_pcie_reenable(dd, cmdval, पूर्णांक_line, clinesz);

		/*
		 * Use पढ़ोq directly, so we करोn't need to mark it as PRESENT
		 * until we get a successful indication that all is well.
		 */
		val = पढ़ोq(&dd->kregbase[kr_revision]);
		अगर (val == dd->revision)
			अवरोध;
		अगर (i == 5) अणु
			qib_dev_err(dd,
				"Failed to initialize after reset, unusable\n");
			ret = 0;
			जाओ  bail;
		पूर्ण
	पूर्ण

	dd->flags |= QIB_PRESENT; /* it's back */

	अगर (msix_entries) अणु
		/* restore the MSIx vector address and data अगर saved above */
		क्रम (i = 0; i < msix_entries; i++) अणु
			अगर (!msix_vecsave || !msix_vecsave[2 * i])
				जारी;
			qib_ग_लिखो_kreg(dd, 2 * i +
				(QIB_7322_MsixTable_OFFS / माप(u64)),
				msix_vecsave[2 * i]);
			qib_ग_लिखो_kreg(dd, 1 + 2 * i +
				(QIB_7322_MsixTable_OFFS / माप(u64)),
				msix_vecsave[1 + 2 * i]);
		पूर्ण
	पूर्ण

	/* initialize the reमुख्यing रेजिस्टरs.  */
	क्रम (i = 0; i < dd->num_pports; ++i)
		ग_लिखो_7322_init_portregs(&dd->pport[i]);
	ग_लिखो_7322_initregs(dd);

	अगर (qib_pcie_params(dd, dd->lbus_width, &msix_entries))
		qib_dev_err(dd,
			"Reset failed to setup PCIe or interrupts; continuing anyway\n");

	dd->cspec->num_msix_entries = msix_entries;
	qib_setup_7322_पूर्णांकerrupt(dd, 1);

	क्रम (i = 0; i < dd->num_pports; ++i) अणु
		काष्ठा qib_pportdata *ppd = &dd->pport[i];

		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags |= QIBL_IB_FORCE_NOTIFY;
		ppd->lflags &= ~QIBL_IB_AUTONEG_FAILED;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	पूर्ण

bail:
	dd->flags &= ~QIB_DOING_RESET; /* OK or not, no दीर्घer resetting */
	kमुक्त(msix_vecsave);
	वापस ret;
पूर्ण

/**
 * qib_7322_put_tid - ग_लिखो a TID to the chip
 * @dd: the qlogic_ib device
 * @tidptr: poपूर्णांकer to the expected TID (in chip) to update
 * @type: 0 क्रम eager, 1 क्रम expected
 * @pa: physical address of in memory buffer; tidinvalid अगर मुक्तing
 */
अटल व्योम qib_7322_put_tid(काष्ठा qib_devdata *dd, u64 __iomem *tidptr,
			     u32 type, अचिन्हित दीर्घ pa)
अणु
	अगर (!(dd->flags & QIB_PRESENT))
		वापस;
	अगर (pa != dd->tidinvalid) अणु
		u64 chippa = pa >> IBA7322_TID_PA_SHIFT;

		/* paranoia checks */
		अगर (pa != (chippa << IBA7322_TID_PA_SHIFT)) अणु
			qib_dev_err(dd, "Physaddr %lx not 2KB aligned!\n",
				    pa);
			वापस;
		पूर्ण
		अगर (chippa >= (1UL << IBA7322_TID_SZ_SHIFT)) अणु
			qib_dev_err(dd,
				"Physical page address 0x%lx larger than supported\n",
				pa);
			वापस;
		पूर्ण

		अगर (type == RCVHQ_RCV_TYPE_EAGER)
			chippa |= dd->tidढाँचा;
		अन्यथा /* क्रम now, always full 4KB page */
			chippa |= IBA7322_TID_SZ_4K;
		pa = chippa;
	पूर्ण
	ग_लिखोq(pa, tidptr);
पूर्ण

/**
 * qib_7322_clear_tids - clear all TID entries क्रम a ctxt, expected and eager
 * @dd: the qlogic_ib device
 * @rcd: the ctxt
 *
 * clear all TID entries क्रम a ctxt, expected and eager.
 * Used from qib_बंद().
 */
अटल व्योम qib_7322_clear_tids(काष्ठा qib_devdata *dd,
				काष्ठा qib_ctxtdata *rcd)
अणु
	u64 __iomem *tidbase;
	अचिन्हित दीर्घ tidinv;
	u32 ctxt;
	पूर्णांक i;

	अगर (!dd->kregbase || !rcd)
		वापस;

	ctxt = rcd->ctxt;

	tidinv = dd->tidinvalid;
	tidbase = (u64 __iomem *)
		((अक्षर __iomem *) dd->kregbase +
		 dd->rcvtidbase +
		 ctxt * dd->rcvtidcnt * माप(*tidbase));

	क्रम (i = 0; i < dd->rcvtidcnt; i++)
		qib_7322_put_tid(dd, &tidbase[i], RCVHQ_RCV_TYPE_EXPECTED,
				 tidinv);

	tidbase = (u64 __iomem *)
		((अक्षर __iomem *) dd->kregbase +
		 dd->rcvegrbase +
		 rcd->rcvegr_tid_base * माप(*tidbase));

	क्रम (i = 0; i < rcd->rcvegrcnt; i++)
		qib_7322_put_tid(dd, &tidbase[i], RCVHQ_RCV_TYPE_EAGER,
				 tidinv);
पूर्ण

/**
 * qib_7322_tidढाँचा - setup स्थिरants क्रम TID updates
 * @dd: the qlogic_ib device
 *
 * We setup stuff that we use a lot, to aव्योम calculating each समय
 */
अटल व्योम qib_7322_tidढाँचा(काष्ठा qib_devdata *dd)
अणु
	/*
	 * For now, we always allocate 4KB buffers (at init) so we can
	 * receive max size packets.  We may want a module parameter to
	 * specअगरy 2KB or 4KB and/or make it per port instead of per device
	 * क्रम those who want to reduce memory footprपूर्णांक.  Note that the
	 * rcvhdrentsize size must be large enough to hold the largest
	 * IB header (currently 96 bytes) that we expect to handle (plus of
	 * course the 2 dwords of RHF).
	 */
	अगर (dd->rcvegrbufsize == 2048)
		dd->tidढाँचा = IBA7322_TID_SZ_2K;
	अन्यथा अगर (dd->rcvegrbufsize == 4096)
		dd->tidढाँचा = IBA7322_TID_SZ_4K;
	dd->tidinvalid = 0;
पूर्ण

/**
 * qib_7322_get_base_info - set chip-specअगरic flags क्रम user code
 * @rcd: the qlogic_ib ctxt
 * @kinfo: qib_base_info poपूर्णांकer
 *
 * We set the PCIE flag because the lower bandwidth on PCIe vs
 * HyperTransport can affect some user packet algorithims.
 */

अटल पूर्णांक qib_7322_get_base_info(काष्ठा qib_ctxtdata *rcd,
				  काष्ठा qib_base_info *kinfo)
अणु
	kinfo->spi_runसमय_flags |= QIB_RUNTIME_CTXT_MSB_IN_QP |
		QIB_RUNTIME_PCIE | QIB_RUNTIME_NODMA_RTAIL |
		QIB_RUNTIME_HDRSUPP | QIB_RUNTIME_SDMA;
	अगर (rcd->dd->cspec->r1)
		kinfo->spi_runसमय_flags |= QIB_RUNTIME_RCHK;
	अगर (rcd->dd->flags & QIB_USE_SPCL_TRIG)
		kinfo->spi_runसमय_flags |= QIB_RUNTIME_SPECIAL_TRIGGER;

	वापस 0;
पूर्ण

अटल काष्ठा qib_message_header *
qib_7322_get_msgheader(काष्ठा qib_devdata *dd, __le32 *rhf_addr)
अणु
	u32 offset = qib_hdrget_offset(rhf_addr);

	वापस (काष्ठा qib_message_header *)
		(rhf_addr - dd->rhf_offset + offset);
पूर्ण

/*
 * Configure number of contexts.
 */
अटल व्योम qib_7322_config_ctxts(काष्ठा qib_devdata *dd)
अणु
	अचिन्हित दीर्घ flags;
	u32 nchipctxts;

	nchipctxts = qib_पढ़ो_kreg32(dd, kr_contextcnt);
	dd->cspec->numctxts = nchipctxts;
	अगर (qib_n_krcv_queues > 1 && dd->num_pports) अणु
		dd->first_user_ctxt = NUM_IB_PORTS +
			(qib_n_krcv_queues - 1) * dd->num_pports;
		अगर (dd->first_user_ctxt > nchipctxts)
			dd->first_user_ctxt = nchipctxts;
		dd->n_krcv_queues = dd->first_user_ctxt / dd->num_pports;
	पूर्ण अन्यथा अणु
		dd->first_user_ctxt = NUM_IB_PORTS;
		dd->n_krcv_queues = 1;
	पूर्ण

	अगर (!qib_cfgctxts) अणु
		पूर्णांक nctxts = dd->first_user_ctxt + num_online_cpus();

		अगर (nctxts <= 6)
			dd->ctxtcnt = 6;
		अन्यथा अगर (nctxts <= 10)
			dd->ctxtcnt = 10;
		अन्यथा अगर (nctxts <= nchipctxts)
			dd->ctxtcnt = nchipctxts;
	पूर्ण अन्यथा अगर (qib_cfgctxts < dd->num_pports)
		dd->ctxtcnt = dd->num_pports;
	अन्यथा अगर (qib_cfgctxts <= nchipctxts)
		dd->ctxtcnt = qib_cfgctxts;
	अगर (!dd->ctxtcnt) /* none of the above, set to max */
		dd->ctxtcnt = nchipctxts;

	/*
	 * Chip can be configured क्रम 6, 10, or 18 ctxts, and choice
	 * affects number of eager TIDs per ctxt (1K, 2K, 4K).
	 * Lock to be paranoid about later motion, etc.
	 */
	spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);
	अगर (dd->ctxtcnt > 10)
		dd->rcvctrl |= 2ULL << SYM_LSB(RcvCtrl, ContextCfg);
	अन्यथा अगर (dd->ctxtcnt > 6)
		dd->rcvctrl |= 1ULL << SYM_LSB(RcvCtrl, ContextCfg);
	/* अन्यथा configure क्रम शेष 6 receive ctxts */

	/* The XRC opcode is 5. */
	dd->rcvctrl |= 5ULL << SYM_LSB(RcvCtrl, XrcTypeCode);

	/*
	 * RcvCtrl *must* be written here so that the
	 * chip understands how to change rcvegrcnt below.
	 */
	qib_ग_लिखो_kreg(dd, kr_rcvctrl, dd->rcvctrl);
	spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);

	/* kr_rcvegrcnt changes based on the number of contexts enabled */
	dd->cspec->rcvegrcnt = qib_पढ़ो_kreg32(dd, kr_rcvegrcnt);
	अगर (qib_rcvhdrcnt)
		dd->rcvhdrcnt = max(dd->cspec->rcvegrcnt, qib_rcvhdrcnt);
	अन्यथा
		dd->rcvhdrcnt = 2 * max(dd->cspec->rcvegrcnt,
				    dd->num_pports > 1 ? 1024U : 2048U);
पूर्ण

अटल पूर्णांक qib_7322_get_ib_cfg(काष्ठा qib_pportdata *ppd, पूर्णांक which)
अणु

	पूर्णांक lsb, ret = 0;
	u64 maskr; /* right-justअगरied mask */

	चयन (which) अणु

	हाल QIB_IB_CFG_LWID_ENB: /* Get allowed Link-width */
		ret = ppd->link_width_enabled;
		जाओ करोne;

	हाल QIB_IB_CFG_LWID: /* Get currently active Link-width */
		ret = ppd->link_width_active;
		जाओ करोne;

	हाल QIB_IB_CFG_SPD_ENB: /* Get allowed Link speeds */
		ret = ppd->link_speed_enabled;
		जाओ करोne;

	हाल QIB_IB_CFG_SPD: /* Get current Link spd */
		ret = ppd->link_speed_active;
		जाओ करोne;

	हाल QIB_IB_CFG_RXPOL_ENB: /* Get Auto-RX-polarity enable */
		lsb = SYM_LSB(IBCCtrlB_0, IB_POLARITY_REV_SUPP);
		maskr = SYM_RMASK(IBCCtrlB_0, IB_POLARITY_REV_SUPP);
		अवरोध;

	हाल QIB_IB_CFG_LREV_ENB: /* Get Auto-Lane-reversal enable */
		lsb = SYM_LSB(IBCCtrlB_0, IB_LANE_REV_SUPPORTED);
		maskr = SYM_RMASK(IBCCtrlB_0, IB_LANE_REV_SUPPORTED);
		अवरोध;

	हाल QIB_IB_CFG_LINKLATENCY:
		ret = qib_पढ़ो_kreg_port(ppd, krp_ibcstatus_b) &
			SYM_MASK(IBCStatusB_0, LinkRoundTripLatency);
		जाओ करोne;

	हाल QIB_IB_CFG_OP_VLS:
		ret = ppd->vls_operational;
		जाओ करोne;

	हाल QIB_IB_CFG_VL_HIGH_CAP:
		ret = 16;
		जाओ करोne;

	हाल QIB_IB_CFG_VL_LOW_CAP:
		ret = 16;
		जाओ करोne;

	हाल QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		ret = SYM_FIELD(ppd->cpspec->ibcctrl_a, IBCCtrlA_0,
				OverrunThreshold);
		जाओ करोne;

	हाल QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		ret = SYM_FIELD(ppd->cpspec->ibcctrl_a, IBCCtrlA_0,
				PhyerrThreshold);
		जाओ करोne;

	हाल QIB_IB_CFG_LINKDEFAULT: /* IB link शेष (sleep/poll) */
		/* will only take effect when the link state changes */
		ret = (ppd->cpspec->ibcctrl_a &
		       SYM_MASK(IBCCtrlA_0, LinkDownDefaultState)) ?
			IB_LINKINITCMD_SLEEP : IB_LINKINITCMD_POLL;
		जाओ करोne;

	हाल QIB_IB_CFG_HRTBT: /* Get Heartbeat off/enable/स्वतः */
		lsb = IBA7322_IBC_HRTBT_LSB;
		maskr = IBA7322_IBC_HRTBT_RMASK; /* OR of AUTO and ENB */
		अवरोध;

	हाल QIB_IB_CFG_PMA_TICKS:
		/*
		 * 0x00 = 10x link transfer rate or 4 nsec. क्रम 2.5Gbs
		 * Since the घड़ी is always 250MHz, the value is 3, 1 or 0.
		 */
		अगर (ppd->link_speed_active == QIB_IB_QDR)
			ret = 3;
		अन्यथा अगर (ppd->link_speed_active == QIB_IB_DDR)
			ret = 1;
		अन्यथा
			ret = 0;
		जाओ करोne;

	शेष:
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	ret = (पूर्णांक)((ppd->cpspec->ibcctrl_b >> lsb) & maskr);
करोne:
	वापस ret;
पूर्ण

/*
 * Below again cribbed liberally from older version. Do not lean
 * heavily on it.
 */
#घोषणा IBA7322_IBC_DLIDLMC_SHIFT QIB_7322_IBCCtrlB_0_IB_DLID_LSB
#घोषणा IBA7322_IBC_DLIDLMC_MASK (QIB_7322_IBCCtrlB_0_IB_DLID_RMASK \
	| (QIB_7322_IBCCtrlB_0_IB_DLID_MASK_RMASK << 16))

अटल पूर्णांक qib_7322_set_ib_cfg(काष्ठा qib_pportdata *ppd, पूर्णांक which, u32 val)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 maskr; /* right-justअगरied mask */
	पूर्णांक lsb, ret = 0;
	u16 lcmd, licmd;
	अचिन्हित दीर्घ flags;

	चयन (which) अणु
	हाल QIB_IB_CFG_LIDLMC:
		/*
		 * Set LID and LMC. Combined to aव्योम possible hazard
		 * caller माला_दो LMC in 16MSbits, DLID in 16LSbits of val
		 */
		lsb = IBA7322_IBC_DLIDLMC_SHIFT;
		maskr = IBA7322_IBC_DLIDLMC_MASK;
		/*
		 * For header-checking, the SLID in the packet will
		 * be masked with SendIBSLMCMask, and compared
		 * with SendIBSLIDAssignMask. Make sure we करो not
		 * set any bits not covered by the mask, or we get
		 * false-positives.
		 */
		qib_ग_लिखो_kreg_port(ppd, krp_sendslid,
				    val & (val >> 16) & SendIBSLIDAssignMask);
		qib_ग_लिखो_kreg_port(ppd, krp_sendslidmask,
				    (val >> 16) & SendIBSLMCMask);
		अवरोध;

	हाल QIB_IB_CFG_LWID_ENB: /* set allowed Link-width */
		ppd->link_width_enabled = val;
		/* convert IB value to chip रेजिस्टर value */
		अगर (val == IB_WIDTH_1X)
			val = 0;
		अन्यथा अगर (val == IB_WIDTH_4X)
			val = 1;
		अन्यथा
			val = 3;
		maskr = SYM_RMASK(IBCCtrlB_0, IB_NUM_CHANNELS);
		lsb = SYM_LSB(IBCCtrlB_0, IB_NUM_CHANNELS);
		अवरोध;

	हाल QIB_IB_CFG_SPD_ENB: /* set allowed Link speeds */
		/*
		 * As with width, only ग_लिखो the actual रेजिस्टर अगर the
		 * link is currently करोwn, otherwise takes effect on next
		 * link change.  Since setting is being explicitly requested
		 * (via MAD or sysfs), clear स्वतःneg failure status अगर speed
		 * स्वतःneg is enabled.
		 */
		ppd->link_speed_enabled = val;
		val <<= IBA7322_IBC_SPEED_LSB;
		maskr = IBA7322_IBC_SPEED_MASK | IBA7322_IBC_IBTA_1_2_MASK |
			IBA7322_IBC_MAX_SPEED_MASK;
		अगर (val & (val - 1)) अणु
			/* Muliple speeds enabled */
			val |= IBA7322_IBC_IBTA_1_2_MASK |
				IBA7322_IBC_MAX_SPEED_MASK;
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			ppd->lflags &= ~QIBL_IB_AUTONEG_FAILED;
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		पूर्ण अन्यथा अगर (val & IBA7322_IBC_SPEED_QDR)
			val |= IBA7322_IBC_IBTA_1_2_MASK;
		/* IBTA 1.2 mode + min/max + speed bits are contiguous */
		lsb = SYM_LSB(IBCCtrlB_0, IB_ENHANCED_MODE);
		अवरोध;

	हाल QIB_IB_CFG_RXPOL_ENB: /* set Auto-RX-polarity enable */
		lsb = SYM_LSB(IBCCtrlB_0, IB_POLARITY_REV_SUPP);
		maskr = SYM_RMASK(IBCCtrlB_0, IB_POLARITY_REV_SUPP);
		अवरोध;

	हाल QIB_IB_CFG_LREV_ENB: /* set Auto-Lane-reversal enable */
		lsb = SYM_LSB(IBCCtrlB_0, IB_LANE_REV_SUPPORTED);
		maskr = SYM_RMASK(IBCCtrlB_0, IB_LANE_REV_SUPPORTED);
		अवरोध;

	हाल QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		maskr = SYM_FIELD(ppd->cpspec->ibcctrl_a, IBCCtrlA_0,
				  OverrunThreshold);
		अगर (maskr != val) अणु
			ppd->cpspec->ibcctrl_a &=
				~SYM_MASK(IBCCtrlA_0, OverrunThreshold);
			ppd->cpspec->ibcctrl_a |= (u64) val <<
				SYM_LSB(IBCCtrlA_0, OverrunThreshold);
			qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a,
					    ppd->cpspec->ibcctrl_a);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
		पूर्ण
		जाओ bail;

	हाल QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		maskr = SYM_FIELD(ppd->cpspec->ibcctrl_a, IBCCtrlA_0,
				  PhyerrThreshold);
		अगर (maskr != val) अणु
			ppd->cpspec->ibcctrl_a &=
				~SYM_MASK(IBCCtrlA_0, PhyerrThreshold);
			ppd->cpspec->ibcctrl_a |= (u64) val <<
				SYM_LSB(IBCCtrlA_0, PhyerrThreshold);
			qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a,
					    ppd->cpspec->ibcctrl_a);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
		पूर्ण
		जाओ bail;

	हाल QIB_IB_CFG_PKEYS: /* update pkeys */
		maskr = (u64) ppd->pkeys[0] | ((u64) ppd->pkeys[1] << 16) |
			((u64) ppd->pkeys[2] << 32) |
			((u64) ppd->pkeys[3] << 48);
		qib_ग_लिखो_kreg_port(ppd, krp_partitionkey, maskr);
		जाओ bail;

	हाल QIB_IB_CFG_LINKDEFAULT: /* IB link शेष (sleep/poll) */
		/* will only take effect when the link state changes */
		अगर (val == IB_LINKINITCMD_POLL)
			ppd->cpspec->ibcctrl_a &=
				~SYM_MASK(IBCCtrlA_0, LinkDownDefaultState);
		अन्यथा /* SLEEP */
			ppd->cpspec->ibcctrl_a |=
				SYM_MASK(IBCCtrlA_0, LinkDownDefaultState);
		qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a, ppd->cpspec->ibcctrl_a);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
		जाओ bail;

	हाल QIB_IB_CFG_MTU: /* update the MTU in IBC */
		/*
		 * Update our housekeeping variables, and set IBC max
		 * size, same as init code; max IBC is max we allow in
		 * buffer, less the qword pbc, plus 1 क्रम ICRC, in dwords
		 * Set even अगर it's unchanged, prपूर्णांक debug message only
		 * on changes.
		 */
		val = (ppd->ibmaxlen >> 2) + 1;
		ppd->cpspec->ibcctrl_a &= ~SYM_MASK(IBCCtrlA_0, MaxPktLen);
		ppd->cpspec->ibcctrl_a |= (u64)val <<
			SYM_LSB(IBCCtrlA_0, MaxPktLen);
		qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a,
				    ppd->cpspec->ibcctrl_a);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
		जाओ bail;

	हाल QIB_IB_CFG_LSTATE: /* set the IB link state */
		चयन (val & 0xffff0000) अणु
		हाल IB_LINKCMD_DOWN:
			lcmd = QLOGIC_IB_IBCC_LINKCMD_DOWN;
			ppd->cpspec->ibmalfusesnap = 1;
			ppd->cpspec->ibmalfsnap = पढ़ो_7322_creg32_port(ppd,
				crp_errlink);
			अगर (!ppd->cpspec->ibdeltainprog &&
			    qib_compat_ddr_negotiate) अणु
				ppd->cpspec->ibdeltainprog = 1;
				ppd->cpspec->ibsymsnap =
					पढ़ो_7322_creg32_port(ppd,
							      crp_ibsymbolerr);
				ppd->cpspec->iblnkerrsnap =
					पढ़ो_7322_creg32_port(ppd,
						      crp_iblinkerrrecov);
			पूर्ण
			अवरोध;

		हाल IB_LINKCMD_ARMED:
			lcmd = QLOGIC_IB_IBCC_LINKCMD_ARMED;
			अगर (ppd->cpspec->ibmalfusesnap) अणु
				ppd->cpspec->ibmalfusesnap = 0;
				ppd->cpspec->ibmalfdelta +=
					पढ़ो_7322_creg32_port(ppd,
							      crp_errlink) -
					ppd->cpspec->ibmalfsnap;
			पूर्ण
			अवरोध;

		हाल IB_LINKCMD_ACTIVE:
			lcmd = QLOGIC_IB_IBCC_LINKCMD_ACTIVE;
			अवरोध;

		शेष:
			ret = -EINVAL;
			qib_dev_err(dd, "bad linkcmd req 0x%x\n", val >> 16);
			जाओ bail;
		पूर्ण
		चयन (val & 0xffff) अणु
		हाल IB_LINKINITCMD_NOP:
			licmd = 0;
			अवरोध;

		हाल IB_LINKINITCMD_POLL:
			licmd = QLOGIC_IB_IBCC_LINKINITCMD_POLL;
			अवरोध;

		हाल IB_LINKINITCMD_SLEEP:
			licmd = QLOGIC_IB_IBCC_LINKINITCMD_SLEEP;
			अवरोध;

		हाल IB_LINKINITCMD_DISABLE:
			licmd = QLOGIC_IB_IBCC_LINKINITCMD_DISABLE;
			ppd->cpspec->chase_end = 0;
			/*
			 * stop state chase counter and समयr, अगर running.
			 * रुको क्रमpending समयr, but करोn't clear .data (ppd)!
			 */
			अगर (ppd->cpspec->chase_समयr.expires) अणु
				del_समयr_sync(&ppd->cpspec->chase_समयr);
				ppd->cpspec->chase_समयr.expires = 0;
			पूर्ण
			अवरोध;

		शेष:
			ret = -EINVAL;
			qib_dev_err(dd, "bad linkinitcmd req 0x%x\n",
				    val & 0xffff);
			जाओ bail;
		पूर्ण
		qib_set_ib_7322_lstate(ppd, lcmd, licmd);
		जाओ bail;

	हाल QIB_IB_CFG_OP_VLS:
		अगर (ppd->vls_operational != val) अणु
			ppd->vls_operational = val;
			set_vls(ppd);
		पूर्ण
		जाओ bail;

	हाल QIB_IB_CFG_VL_HIGH_LIMIT:
		qib_ग_लिखो_kreg_port(ppd, krp_highprio_limit, val);
		जाओ bail;

	हाल QIB_IB_CFG_HRTBT: /* set Heartbeat off/enable/स्वतः */
		अगर (val > 3) अणु
			ret = -EINVAL;
			जाओ bail;
		पूर्ण
		lsb = IBA7322_IBC_HRTBT_LSB;
		maskr = IBA7322_IBC_HRTBT_RMASK; /* OR of AUTO and ENB */
		अवरोध;

	हाल QIB_IB_CFG_PORT:
		/* val is the port number of the चयन we are connected to. */
		अगर (ppd->dd->cspec->r1) अणु
			cancel_delayed_work(&ppd->cpspec->ipg_work);
			ppd->cpspec->ipg_tries = 0;
		पूर्ण
		जाओ bail;

	शेष:
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	ppd->cpspec->ibcctrl_b &= ~(maskr << lsb);
	ppd->cpspec->ibcctrl_b |= (((u64) val & maskr) << lsb);
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_b, ppd->cpspec->ibcctrl_b);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_7322_set_loopback(काष्ठा qib_pportdata *ppd, स्थिर अक्षर *what)
अणु
	पूर्णांक ret = 0;
	u64 val, ctrlb;

	/* only IBC loopback, may add serdes and xgxs loopbacks later */
	अगर (!म_भेदन(what, "ibc", 3)) अणु
		ppd->cpspec->ibcctrl_a |= SYM_MASK(IBCCtrlA_0,
						       Loopback);
		val = 0; /* disable heart beat, so link will come up */
		qib_devinfo(ppd->dd->pcidev, "Enabling IB%u:%u IBC loopback\n",
			 ppd->dd->unit, ppd->port);
	पूर्ण अन्यथा अगर (!म_भेदन(what, "off", 3)) अणु
		ppd->cpspec->ibcctrl_a &= ~SYM_MASK(IBCCtrlA_0,
							Loopback);
		/* enable heart beat again */
		val = IBA7322_IBC_HRTBT_RMASK << IBA7322_IBC_HRTBT_LSB;
		qib_devinfo(ppd->dd->pcidev,
			"Disabling IB%u:%u IBC loopback (normal)\n",
			ppd->dd->unit, ppd->port);
	पूर्ण अन्यथा
		ret = -EINVAL;
	अगर (!ret) अणु
		qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a,
				    ppd->cpspec->ibcctrl_a);
		ctrlb = ppd->cpspec->ibcctrl_b & ~(IBA7322_IBC_HRTBT_MASK
					     << IBA7322_IBC_HRTBT_LSB);
		ppd->cpspec->ibcctrl_b = ctrlb | val;
		qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_b,
				    ppd->cpspec->ibcctrl_b);
		qib_ग_लिखो_kreg(ppd->dd, kr_scratch, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम get_vl_weights(काष्ठा qib_pportdata *ppd, अचिन्हित regno,
			   काष्ठा ib_vl_weight_elem *vl)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < 16; i++, regno++, vl++) अणु
		u32 val = qib_पढ़ो_kreg_port(ppd, regno);

		vl->vl = (val >> SYM_LSB(LowPriority0_0, VirtualLane)) &
			SYM_RMASK(LowPriority0_0, VirtualLane);
		vl->weight = (val >> SYM_LSB(LowPriority0_0, Weight)) &
			SYM_RMASK(LowPriority0_0, Weight);
	पूर्ण
पूर्ण

अटल व्योम set_vl_weights(काष्ठा qib_pportdata *ppd, अचिन्हित regno,
			   काष्ठा ib_vl_weight_elem *vl)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < 16; i++, regno++, vl++) अणु
		u64 val;

		val = ((vl->vl & SYM_RMASK(LowPriority0_0, VirtualLane)) <<
			SYM_LSB(LowPriority0_0, VirtualLane)) |
		      ((vl->weight & SYM_RMASK(LowPriority0_0, Weight)) <<
			SYM_LSB(LowPriority0_0, Weight));
		qib_ग_लिखो_kreg_port(ppd, regno, val);
	पूर्ण
	अगर (!(ppd->p_sendctrl & SYM_MASK(SendCtrl_0, IBVLArbiterEn))) अणु
		काष्ठा qib_devdata *dd = ppd->dd;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dd->sendctrl_lock, flags);
		ppd->p_sendctrl |= SYM_MASK(SendCtrl_0, IBVLArbiterEn);
		qib_ग_लिखो_kreg_port(ppd, krp_sendctrl, ppd->p_sendctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक qib_7322_get_ib_table(काष्ठा qib_pportdata *ppd, पूर्णांक which, व्योम *t)
अणु
	चयन (which) अणु
	हाल QIB_IB_TBL_VL_HIGH_ARB:
		get_vl_weights(ppd, krp_highprio_0, t);
		अवरोध;

	हाल QIB_IB_TBL_VL_LOW_ARB:
		get_vl_weights(ppd, krp_lowprio_0, t);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qib_7322_set_ib_table(काष्ठा qib_pportdata *ppd, पूर्णांक which, व्योम *t)
अणु
	चयन (which) अणु
	हाल QIB_IB_TBL_VL_HIGH_ARB:
		set_vl_weights(ppd, krp_highprio_0, t);
		अवरोध;

	हाल QIB_IB_TBL_VL_LOW_ARB:
		set_vl_weights(ppd, krp_lowprio_0, t);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qib_update_7322_usrhead(काष्ठा qib_ctxtdata *rcd, u64 hd,
				    u32 updegr, u32 egrhd, u32 npkts)
अणु
	/*
	 * Need to ग_लिखो समयout रेजिस्टर beक्रमe updating rcvhdrhead to ensure
	 * that the समयr is enabled on reception of a packet.
	 */
	अगर (hd >> IBA7322_HDRHEAD_PKTINT_SHIFT)
		adjust_rcv_समयout(rcd, npkts);
	अगर (updegr)
		qib_ग_लिखो_ureg(rcd->dd, ur_rcvegrindexhead, egrhd, rcd->ctxt);
	qib_ग_लिखो_ureg(rcd->dd, ur_rcvhdrhead, hd, rcd->ctxt);
	qib_ग_लिखो_ureg(rcd->dd, ur_rcvhdrhead, hd, rcd->ctxt);
पूर्ण

अटल u32 qib_7322_hdrqempty(काष्ठा qib_ctxtdata *rcd)
अणु
	u32 head, tail;

	head = qib_पढ़ो_ureg32(rcd->dd, ur_rcvhdrhead, rcd->ctxt);
	अगर (rcd->rcvhdrtail_kvaddr)
		tail = qib_get_rcvhdrtail(rcd);
	अन्यथा
		tail = qib_पढ़ो_ureg32(rcd->dd, ur_rcvhdrtail, rcd->ctxt);
	वापस head == tail;
पूर्ण

#घोषणा RCVCTRL_COMMON_MODS (QIB_RCVCTRL_CTXT_ENB | \
	QIB_RCVCTRL_CTXT_DIS | \
	QIB_RCVCTRL_TIDFLOW_ENB | \
	QIB_RCVCTRL_TIDFLOW_DIS | \
	QIB_RCVCTRL_TAILUPD_ENB | \
	QIB_RCVCTRL_TAILUPD_DIS | \
	QIB_RCVCTRL_INTRAVAIL_ENB | \
	QIB_RCVCTRL_INTRAVAIL_DIS | \
	QIB_RCVCTRL_BP_ENB | \
	QIB_RCVCTRL_BP_DIS)

#घोषणा RCVCTRL_PORT_MODS (QIB_RCVCTRL_CTXT_ENB | \
	QIB_RCVCTRL_CTXT_DIS | \
	QIB_RCVCTRL_PKEY_DIS | \
	QIB_RCVCTRL_PKEY_ENB)

/*
 * Modअगरy the RCVCTRL रेजिस्टर in chip-specअगरic way. This
 * is a function because bit positions and (future) रेजिस्टर
 * location is chip-specअगरc, but the needed operations are
 * generic. <op> is a bit-mask because we often want to
 * करो multiple modअगरications.
 */
अटल व्योम rcvctrl_7322_mod(काष्ठा qib_pportdata *ppd, अचिन्हित पूर्णांक op,
			     पूर्णांक ctxt)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	काष्ठा qib_ctxtdata *rcd;
	u64 mask, val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);

	अगर (op & QIB_RCVCTRL_TIDFLOW_ENB)
		dd->rcvctrl |= SYM_MASK(RcvCtrl, TidFlowEnable);
	अगर (op & QIB_RCVCTRL_TIDFLOW_DIS)
		dd->rcvctrl &= ~SYM_MASK(RcvCtrl, TidFlowEnable);
	अगर (op & QIB_RCVCTRL_TAILUPD_ENB)
		dd->rcvctrl |= SYM_MASK(RcvCtrl, TailUpd);
	अगर (op & QIB_RCVCTRL_TAILUPD_DIS)
		dd->rcvctrl &= ~SYM_MASK(RcvCtrl, TailUpd);
	अगर (op & QIB_RCVCTRL_PKEY_ENB)
		ppd->p_rcvctrl &= ~SYM_MASK(RcvCtrl_0, RcvPartitionKeyDisable);
	अगर (op & QIB_RCVCTRL_PKEY_DIS)
		ppd->p_rcvctrl |= SYM_MASK(RcvCtrl_0, RcvPartitionKeyDisable);
	अगर (ctxt < 0) अणु
		mask = (1ULL << dd->ctxtcnt) - 1;
		rcd = शून्य;
	पूर्ण अन्यथा अणु
		mask = (1ULL << ctxt);
		rcd = dd->rcd[ctxt];
	पूर्ण
	अगर ((op & QIB_RCVCTRL_CTXT_ENB) && rcd) अणु
		ppd->p_rcvctrl |=
			(mask << SYM_LSB(RcvCtrl_0, ContextEnableKernel));
		अगर (!(dd->flags & QIB_NODMA_RTAIL)) अणु
			op |= QIB_RCVCTRL_TAILUPD_ENB; /* need reg ग_लिखो */
			dd->rcvctrl |= SYM_MASK(RcvCtrl, TailUpd);
		पूर्ण
		/* Write these रेजिस्टरs beक्रमe the context is enabled. */
		qib_ग_लिखो_kreg_ctxt(dd, krc_rcvhdrtailaddr, ctxt,
				    rcd->rcvhdrqtailaddr_phys);
		qib_ग_लिखो_kreg_ctxt(dd, krc_rcvhdraddr, ctxt,
				    rcd->rcvhdrq_phys);
		rcd->seq_cnt = 1;
	पूर्ण
	अगर (op & QIB_RCVCTRL_CTXT_DIS)
		ppd->p_rcvctrl &=
			~(mask << SYM_LSB(RcvCtrl_0, ContextEnableKernel));
	अगर (op & QIB_RCVCTRL_BP_ENB)
		dd->rcvctrl |= mask << SYM_LSB(RcvCtrl, करोntDropRHQFull);
	अगर (op & QIB_RCVCTRL_BP_DIS)
		dd->rcvctrl &= ~(mask << SYM_LSB(RcvCtrl, करोntDropRHQFull));
	अगर (op & QIB_RCVCTRL_INTRAVAIL_ENB)
		dd->rcvctrl |= (mask << SYM_LSB(RcvCtrl, IntrAvail));
	अगर (op & QIB_RCVCTRL_INTRAVAIL_DIS)
		dd->rcvctrl &= ~(mask << SYM_LSB(RcvCtrl, IntrAvail));
	/*
	 * Decide which रेजिस्टरs to ग_लिखो depending on the ops enabled.
	 * Special हाल is "flush" (no bits set at all)
	 * which needs to ग_लिखो both.
	 */
	अगर (op == 0 || (op & RCVCTRL_COMMON_MODS))
		qib_ग_लिखो_kreg(dd, kr_rcvctrl, dd->rcvctrl);
	अगर (op == 0 || (op & RCVCTRL_PORT_MODS))
		qib_ग_लिखो_kreg_port(ppd, krp_rcvctrl, ppd->p_rcvctrl);
	अगर ((op & QIB_RCVCTRL_CTXT_ENB) && dd->rcd[ctxt]) अणु
		/*
		 * Init the context रेजिस्टरs also; अगर we were
		 * disabled, tail and head should both be zero
		 * alपढ़ोy from the enable, but since we करोn't
		 * know, we have to करो it explicitly.
		 */
		val = qib_पढ़ो_ureg32(dd, ur_rcvegrindextail, ctxt);
		qib_ग_लिखो_ureg(dd, ur_rcvegrindexhead, val, ctxt);

		/* be sure enabling ग_लिखो seen; hd/tl should be 0 */
		(व्योम) qib_पढ़ो_kreg32(dd, kr_scratch);
		val = qib_पढ़ो_ureg32(dd, ur_rcvhdrtail, ctxt);
		dd->rcd[ctxt]->head = val;
		/* If kctxt, पूर्णांकerrupt on next receive. */
		अगर (ctxt < dd->first_user_ctxt)
			val |= dd->rhdrhead_पूर्णांकr_off;
		qib_ग_लिखो_ureg(dd, ur_rcvhdrhead, val, ctxt);
	पूर्ण अन्यथा अगर ((op & QIB_RCVCTRL_INTRAVAIL_ENB) &&
		dd->rcd[ctxt] && dd->rhdrhead_पूर्णांकr_off) अणु
		/* arm rcv पूर्णांकerrupt */
		val = dd->rcd[ctxt]->head | dd->rhdrhead_पूर्णांकr_off;
		qib_ग_लिखो_ureg(dd, ur_rcvhdrhead, val, ctxt);
	पूर्ण
	अगर (op & QIB_RCVCTRL_CTXT_DIS) अणु
		अचिन्हित f;

		/* Now that the context is disabled, clear these रेजिस्टरs. */
		अगर (ctxt >= 0) अणु
			qib_ग_लिखो_kreg_ctxt(dd, krc_rcvhdrtailaddr, ctxt, 0);
			qib_ग_लिखो_kreg_ctxt(dd, krc_rcvhdraddr, ctxt, 0);
			क्रम (f = 0; f < NUM_TIDFLOWS_CTXT; f++)
				qib_ग_लिखो_ureg(dd, ur_rcvflowtable + f,
					       TIDFLOW_ERRBITS, ctxt);
		पूर्ण अन्यथा अणु
			अचिन्हित i;

			क्रम (i = 0; i < dd->cfgctxts; i++) अणु
				qib_ग_लिखो_kreg_ctxt(dd, krc_rcvhdrtailaddr,
						    i, 0);
				qib_ग_लिखो_kreg_ctxt(dd, krc_rcvhdraddr, i, 0);
				क्रम (f = 0; f < NUM_TIDFLOWS_CTXT; f++)
					qib_ग_लिखो_ureg(dd, ur_rcvflowtable + f,
						       TIDFLOW_ERRBITS, i);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);
पूर्ण

/*
 * Modअगरy the SENDCTRL रेजिस्टर in chip-specअगरic way. This
 * is a function where there are multiple such रेजिस्टरs with
 * slightly dअगरferent layouts.
 * The chip करोesn't allow back-to-back sendctrl ग_लिखोs, so ग_लिखो
 * the scratch रेजिस्टर after writing sendctrl.
 *
 * Which रेजिस्टर is written depends on the operation.
 * Most operate on the common रेजिस्टर, जबतक
 * SEND_ENB and SEND_DIS operate on the per-port ones.
 * SEND_ENB is included in common because it can change SPCL_TRIG
 */
#घोषणा SENDCTRL_COMMON_MODS (\
	QIB_SENDCTRL_CLEAR | \
	QIB_SENDCTRL_AVAIL_DIS | \
	QIB_SENDCTRL_AVAIL_ENB | \
	QIB_SENDCTRL_AVAIL_BLIP | \
	QIB_SENDCTRL_DISARM | \
	QIB_SENDCTRL_DISARM_ALL | \
	QIB_SENDCTRL_SEND_ENB)

#घोषणा SENDCTRL_PORT_MODS (\
	QIB_SENDCTRL_CLEAR | \
	QIB_SENDCTRL_SEND_ENB | \
	QIB_SENDCTRL_SEND_DIS | \
	QIB_SENDCTRL_FLUSH)

अटल व्योम sendctrl_7322_mod(काष्ठा qib_pportdata *ppd, u32 op)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 पंचांगp_dd_sendctrl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);

	/* First the dd ones that are "sticky", saved in shaकरोw */
	अगर (op & QIB_SENDCTRL_CLEAR)
		dd->sendctrl = 0;
	अगर (op & QIB_SENDCTRL_AVAIL_DIS)
		dd->sendctrl &= ~SYM_MASK(SendCtrl, SendBufAvailUpd);
	अन्यथा अगर (op & QIB_SENDCTRL_AVAIL_ENB) अणु
		dd->sendctrl |= SYM_MASK(SendCtrl, SendBufAvailUpd);
		अगर (dd->flags & QIB_USE_SPCL_TRIG)
			dd->sendctrl |= SYM_MASK(SendCtrl, SpecialTriggerEn);
	पूर्ण

	/* Then the ppd ones that are "sticky", saved in shaकरोw */
	अगर (op & QIB_SENDCTRL_SEND_DIS)
		ppd->p_sendctrl &= ~SYM_MASK(SendCtrl_0, SendEnable);
	अन्यथा अगर (op & QIB_SENDCTRL_SEND_ENB)
		ppd->p_sendctrl |= SYM_MASK(SendCtrl_0, SendEnable);

	अगर (op & QIB_SENDCTRL_DISARM_ALL) अणु
		u32 i, last;

		पंचांगp_dd_sendctrl = dd->sendctrl;
		last = dd->piobcnt2k + dd->piobcnt4k + NUM_VL15_BUFS;
		/*
		 * Disarm any buffers that are not yet launched,
		 * disabling updates until करोne.
		 */
		पंचांगp_dd_sendctrl &= ~SYM_MASK(SendCtrl, SendBufAvailUpd);
		क्रम (i = 0; i < last; i++) अणु
			qib_ग_लिखो_kreg(dd, kr_sendctrl,
				       पंचांगp_dd_sendctrl |
				       SYM_MASK(SendCtrl, Disarm) | i);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		पूर्ण
	पूर्ण

	अगर (op & QIB_SENDCTRL_FLUSH) अणु
		u64 पंचांगp_ppd_sendctrl = ppd->p_sendctrl;

		/*
		 * Now drain all the fअगरos.  The Abort bit should never be
		 * needed, so क्रम now, at least, we करोn't use it.
		 */
		पंचांगp_ppd_sendctrl |=
			SYM_MASK(SendCtrl_0, TxeDrainRmFअगरo) |
			SYM_MASK(SendCtrl_0, TxeDrainLaFअगरo) |
			SYM_MASK(SendCtrl_0, TxeBypassIbc);
		qib_ग_लिखो_kreg_port(ppd, krp_sendctrl, पंचांगp_ppd_sendctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
	पूर्ण

	पंचांगp_dd_sendctrl = dd->sendctrl;

	अगर (op & QIB_SENDCTRL_DISARM)
		पंचांगp_dd_sendctrl |= SYM_MASK(SendCtrl, Disarm) |
			((op & QIB_7322_SendCtrl_DisarmSendBuf_RMASK) <<
			 SYM_LSB(SendCtrl, DisarmSendBuf));
	अगर ((op & QIB_SENDCTRL_AVAIL_BLIP) &&
	    (dd->sendctrl & SYM_MASK(SendCtrl, SendBufAvailUpd)))
		पंचांगp_dd_sendctrl &= ~SYM_MASK(SendCtrl, SendBufAvailUpd);

	अगर (op == 0 || (op & SENDCTRL_COMMON_MODS)) अणु
		qib_ग_लिखो_kreg(dd, kr_sendctrl, पंचांगp_dd_sendctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
	पूर्ण

	अगर (op == 0 || (op & SENDCTRL_PORT_MODS)) अणु
		qib_ग_लिखो_kreg_port(ppd, krp_sendctrl, ppd->p_sendctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
	पूर्ण

	अगर (op & QIB_SENDCTRL_AVAIL_BLIP) अणु
		qib_ग_लिखो_kreg(dd, kr_sendctrl, dd->sendctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
	पूर्ण

	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);

	अगर (op & QIB_SENDCTRL_FLUSH) अणु
		u32 v;
		/*
		 * ensure ग_लिखोs have hit chip, then करो a few
		 * more पढ़ोs, to allow DMA of pioavail रेजिस्टरs
		 * to occur, so in-memory copy is in sync with
		 * the chip.  Not always safe to sleep.
		 */
		v = qib_पढ़ो_kreg32(dd, kr_scratch);
		qib_ग_लिखो_kreg(dd, kr_scratch, v);
		v = qib_पढ़ो_kreg32(dd, kr_scratch);
		qib_ग_लिखो_kreg(dd, kr_scratch, v);
		qib_पढ़ो_kreg32(dd, kr_scratch);
	पूर्ण
पूर्ण

#घोषणा _PORT_VIRT_FLAG 0x8000U /* "virtual", need adjusपंचांगents */
#घोषणा _PORT_64BIT_FLAG 0x10000U /* not "virtual", but 64bit */
#घोषणा _PORT_CNTR_IDXMASK 0x7fffU /* mask off flags above */

/**
 * qib_portcntr_7322 - पढ़ो a per-port chip counter
 * @ppd: the qlogic_ib pport
 * @reg: the counter to पढ़ो (not a chip offset)
 */
अटल u64 qib_portcntr_7322(काष्ठा qib_pportdata *ppd, u32 reg)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 ret = 0ULL;
	u16 creg;
	/* 0xffff क्रम unimplemented or synthesized counters */
	अटल स्थिर u32 xlator[] = अणु
		[QIBPORTCNTR_PKTSEND] = crp_pktsend | _PORT_64BIT_FLAG,
		[QIBPORTCNTR_WORDSEND] = crp_wordsend | _PORT_64BIT_FLAG,
		[QIBPORTCNTR_PSXMITDATA] = crp_psxmitdatacount,
		[QIBPORTCNTR_PSXMITPKTS] = crp_psxmitpktscount,
		[QIBPORTCNTR_PSXMITWAIT] = crp_psxmitरुकोcount,
		[QIBPORTCNTR_SENDSTALL] = crp_sendstall,
		[QIBPORTCNTR_PKTRCV] = crp_pktrcv | _PORT_64BIT_FLAG,
		[QIBPORTCNTR_PSRCVDATA] = crp_psrcvdatacount,
		[QIBPORTCNTR_PSRCVPKTS] = crp_psrcvpktscount,
		[QIBPORTCNTR_RCVEBP] = crp_rcvebp,
		[QIBPORTCNTR_RCVOVFL] = crp_rcvovfl,
		[QIBPORTCNTR_WORDRCV] = crp_wordrcv | _PORT_64BIT_FLAG,
		[QIBPORTCNTR_RXDROPPKT] = 0xffff, /* not needed  क्रम 7322 */
		[QIBPORTCNTR_RXLOCALPHYERR] = crp_rxotherlocalphyerr,
		[QIBPORTCNTR_RXVLERR] = crp_rxvlerr,
		[QIBPORTCNTR_ERRICRC] = crp_erricrc,
		[QIBPORTCNTR_ERRVCRC] = crp_errvcrc,
		[QIBPORTCNTR_ERRLPCRC] = crp_errlpcrc,
		[QIBPORTCNTR_BADFORMAT] = crp_badक्रमmat,
		[QIBPORTCNTR_ERR_RLEN] = crp_err_rlen,
		[QIBPORTCNTR_IBSYMBOLERR] = crp_ibsymbolerr,
		[QIBPORTCNTR_INVALIDRLEN] = crp_invalidrlen,
		[QIBPORTCNTR_UNSUPVL] = crp_txunsupvl,
		[QIBPORTCNTR_EXCESSBUFOVFL] = crp_excessbufferovfl,
		[QIBPORTCNTR_ERRLINK] = crp_errlink,
		[QIBPORTCNTR_IBLINKDOWN] = crp_iblinkकरोwn,
		[QIBPORTCNTR_IBLINKERRRECOV] = crp_iblinkerrrecov,
		[QIBPORTCNTR_LLI] = crp_locallinkपूर्णांकegrityerr,
		[QIBPORTCNTR_VL15PKTDROP] = crp_vl15droppedpkt,
		[QIBPORTCNTR_ERRPKEY] = crp_errpkey,
		/*
		 * the next 3 aren't really counters, but were implemented
		 * as counters in older chips, so still get accessed as
		 * though they were counters from this code.
		 */
		[QIBPORTCNTR_PSINTERVAL] = krp_psपूर्णांकerval,
		[QIBPORTCNTR_PSSTART] = krp_psstart,
		[QIBPORTCNTR_PSSTAT] = krp_psstat,
		/* pseuकरो-counter, summed क्रम all ports */
		[QIBPORTCNTR_KHDROVFL] = 0xffff,
	पूर्ण;

	अगर (reg >= ARRAY_SIZE(xlator)) अणु
		qib_devinfo(ppd->dd->pcidev,
			 "Unimplemented portcounter %u\n", reg);
		जाओ करोne;
	पूर्ण
	creg = xlator[reg] & _PORT_CNTR_IDXMASK;

	/* handle non-counters and special हालs first */
	अगर (reg == QIBPORTCNTR_KHDROVFL) अणु
		पूर्णांक i;

		/* sum over all kernel contexts (skip अगर mini_init) */
		क्रम (i = 0; dd->rcd && i < dd->first_user_ctxt; i++) अणु
			काष्ठा qib_ctxtdata *rcd = dd->rcd[i];

			अगर (!rcd || rcd->ppd != ppd)
				जारी;
			ret += पढ़ो_7322_creg32(dd, cr_base_egrovfl + i);
		पूर्ण
		जाओ करोne;
	पूर्ण अन्यथा अगर (reg == QIBPORTCNTR_RXDROPPKT) अणु
		/*
		 * Used as part of the synthesis of port_rcv_errors
		 * in the verbs code क्रम IBTA counters.  Not needed क्रम 7322,
		 * because all the errors are alपढ़ोy counted by other cntrs.
		 */
		जाओ करोne;
	पूर्ण अन्यथा अगर (reg == QIBPORTCNTR_PSINTERVAL ||
		   reg == QIBPORTCNTR_PSSTART || reg == QIBPORTCNTR_PSSTAT) अणु
		/* were counters in older chips, now per-port kernel regs */
		ret = qib_पढ़ो_kreg_port(ppd, creg);
		जाओ करोne;
	पूर्ण

	/*
	 * Only fast increment counters are 64 bits; use 32 bit पढ़ोs to
	 * aव्योम two independent पढ़ोs when on Opteron.
	 */
	अगर (xlator[reg] & _PORT_64BIT_FLAG)
		ret = पढ़ो_7322_creg_port(ppd, creg);
	अन्यथा
		ret = पढ़ो_7322_creg32_port(ppd, creg);
	अगर (creg == crp_ibsymbolerr) अणु
		अगर (ppd->cpspec->ibdeltainprog)
			ret -= ret - ppd->cpspec->ibsymsnap;
		ret -= ppd->cpspec->ibsymdelta;
	पूर्ण अन्यथा अगर (creg == crp_iblinkerrrecov) अणु
		अगर (ppd->cpspec->ibdeltainprog)
			ret -= ret - ppd->cpspec->iblnkerrsnap;
		ret -= ppd->cpspec->iblnkerrdelta;
	पूर्ण अन्यथा अगर (creg == crp_errlink)
		ret -= ppd->cpspec->ibmalfdelta;
	अन्यथा अगर (creg == crp_iblinkकरोwn)
		ret += ppd->cpspec->iblnkकरोwndelta;
करोne:
	वापस ret;
पूर्ण

/*
 * Device counter names (not port-specअगरic), one line per stat,
 * single string.  Used by utilities like ipathstats to prपूर्णांक the stats
 * in a way which works क्रम dअगरferent versions of drivers, without changing
 * the utility.  Names need to be 12 अक्षरs or less (w/o newline), क्रम proper
 * display by utility.
 * Non-error counters are first.
 * Start of "error" conters is indicated by a leading "E " on the first
 * "error" counter, and करोesn't count in label length.
 * The EgrOvfl list needs to be last so we truncate them at the configured
 * context count क्रम the device.
 * cntr7322indices contains the corresponding रेजिस्टर indices.
 */
अटल स्थिर अक्षर cntr7322names[] =
	"Interrupts\n"
	"HostBusStall\n"
	"E RxTIDFull\n"
	"RxTIDInvalid\n"
	"RxTIDFloDrop\n" /* 7322 only */
	"Ctxt0EgrOvfl\n"
	"Ctxt1EgrOvfl\n"
	"Ctxt2EgrOvfl\n"
	"Ctxt3EgrOvfl\n"
	"Ctxt4EgrOvfl\n"
	"Ctxt5EgrOvfl\n"
	"Ctxt6EgrOvfl\n"
	"Ctxt7EgrOvfl\n"
	"Ctxt8EgrOvfl\n"
	"Ctxt9EgrOvfl\n"
	"Ctx10EgrOvfl\n"
	"Ctx11EgrOvfl\n"
	"Ctx12EgrOvfl\n"
	"Ctx13EgrOvfl\n"
	"Ctx14EgrOvfl\n"
	"Ctx15EgrOvfl\n"
	"Ctx16EgrOvfl\n"
	"Ctx17EgrOvfl\n"
	;

अटल स्थिर u32 cntr7322indices[] = अणु
	cr_lbपूर्णांक | _PORT_64BIT_FLAG,
	cr_lbstall | _PORT_64BIT_FLAG,
	cr_tidfull,
	cr_tidinvalid,
	cr_rxtidflowdrop,
	cr_base_egrovfl + 0,
	cr_base_egrovfl + 1,
	cr_base_egrovfl + 2,
	cr_base_egrovfl + 3,
	cr_base_egrovfl + 4,
	cr_base_egrovfl + 5,
	cr_base_egrovfl + 6,
	cr_base_egrovfl + 7,
	cr_base_egrovfl + 8,
	cr_base_egrovfl + 9,
	cr_base_egrovfl + 10,
	cr_base_egrovfl + 11,
	cr_base_egrovfl + 12,
	cr_base_egrovfl + 13,
	cr_base_egrovfl + 14,
	cr_base_egrovfl + 15,
	cr_base_egrovfl + 16,
	cr_base_egrovfl + 17,
पूर्ण;

/*
 * same as cntr7322names and cntr7322indices, but क्रम port-specअगरic counters.
 * portcntr7322indices is somewhat complicated by some रेजिस्टरs needing
 * adjusपंचांगents of various kinds, and those are ORed with _PORT_VIRT_FLAG
 */
अटल स्थिर अक्षर portcntr7322names[] =
	"TxPkt\n"
	"TxFlowPkt\n"
	"TxWords\n"
	"RxPkt\n"
	"RxFlowPkt\n"
	"RxWords\n"
	"TxFlowStall\n"
	"TxDmaDesc\n"  /* 7220 and 7322-only */
	"E RxDlidFltr\n"  /* 7220 and 7322-only */
	"IBStatusChng\n"
	"IBLinkDown\n"
	"IBLnkRecov\n"
	"IBRxLinkErr\n"
	"IBSymbolErr\n"
	"RxLLIErr\n"
	"RxBadFormat\n"
	"RxBadLen\n"
	"RxBufOvrfl\n"
	"RxEBP\n"
	"RxFlowCtlErr\n"
	"RxICRCerr\n"
	"RxLPCRCerr\n"
	"RxVCRCerr\n"
	"RxInvalLen\n"
	"RxInvalPKey\n"
	"RxPktDropped\n"
	"TxBadLength\n"
	"TxDropped\n"
	"TxInvalLen\n"
	"TxUnderrun\n"
	"TxUnsupVL\n"
	"RxLclPhyErr\n" /* 7220 and 7322-only from here करोwn */
	"RxVL15Drop\n"
	"RxVlErr\n"
	"XcessBufOvfl\n"
	"RxQPBadCtxt\n" /* 7322-only from here करोwn */
	"TXBadHeader\n"
	;

अटल स्थिर u32 portcntr7322indices[] = अणु
	QIBPORTCNTR_PKTSEND | _PORT_VIRT_FLAG,
	crp_pktsendflow,
	QIBPORTCNTR_WORDSEND | _PORT_VIRT_FLAG,
	QIBPORTCNTR_PKTRCV | _PORT_VIRT_FLAG,
	crp_pktrcvflowctrl,
	QIBPORTCNTR_WORDRCV | _PORT_VIRT_FLAG,
	QIBPORTCNTR_SENDSTALL | _PORT_VIRT_FLAG,
	crp_txsdmadesc | _PORT_64BIT_FLAG,
	crp_rxdlidfltr,
	crp_ibstatuschange,
	QIBPORTCNTR_IBLINKDOWN | _PORT_VIRT_FLAG,
	QIBPORTCNTR_IBLINKERRRECOV | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERRLINK | _PORT_VIRT_FLAG,
	QIBPORTCNTR_IBSYMBOLERR | _PORT_VIRT_FLAG,
	QIBPORTCNTR_LLI | _PORT_VIRT_FLAG,
	QIBPORTCNTR_BADFORMAT | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERR_RLEN | _PORT_VIRT_FLAG,
	QIBPORTCNTR_RCVOVFL | _PORT_VIRT_FLAG,
	QIBPORTCNTR_RCVEBP | _PORT_VIRT_FLAG,
	crp_rcvflowctrlviol,
	QIBPORTCNTR_ERRICRC | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERRLPCRC | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERRVCRC | _PORT_VIRT_FLAG,
	QIBPORTCNTR_INVALIDRLEN | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERRPKEY | _PORT_VIRT_FLAG,
	QIBPORTCNTR_RXDROPPKT | _PORT_VIRT_FLAG,
	crp_txminmaxlenerr,
	crp_txdroppedpkt,
	crp_txlenerr,
	crp_txunderrun,
	crp_txunsupvl,
	QIBPORTCNTR_RXLOCALPHYERR | _PORT_VIRT_FLAG,
	QIBPORTCNTR_VL15PKTDROP | _PORT_VIRT_FLAG,
	QIBPORTCNTR_RXVLERR | _PORT_VIRT_FLAG,
	QIBPORTCNTR_EXCESSBUFOVFL | _PORT_VIRT_FLAG,
	crp_rxqpinvalidctxt,
	crp_txhdrerr,
पूर्ण;

/* करो all the setup to make the counter पढ़ोs efficient later */
अटल व्योम init_7322_cntrnames(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक i, j = 0;
	अक्षर *s;

	क्रम (i = 0, s = (अक्षर *)cntr7322names; s && j <= dd->cfgctxts;
	     i++) अणु
		/* we always have at least one counter beक्रमe the egrovfl */
		अगर (!j && !म_भेदन("Ctxt0EgrOvfl", s + 1, 12))
			j = 1;
		s = म_अक्षर(s + 1, '\n');
		अगर (s && j)
			j++;
	पूर्ण
	dd->cspec->ncntrs = i;
	अगर (!s)
		/* full list; size is without terminating null */
		dd->cspec->cntrnamelen = माप(cntr7322names) - 1;
	अन्यथा
		dd->cspec->cntrnamelen = 1 + s - cntr7322names;
	dd->cspec->cntrs = kदो_स्मृति_array(dd->cspec->ncntrs, माप(u64),
					 GFP_KERNEL);

	क्रम (i = 0, s = (अक्षर *)portcntr7322names; s; i++)
		s = म_अक्षर(s + 1, '\n');
	dd->cspec->nportcntrs = i - 1;
	dd->cspec->portcntrnamelen = माप(portcntr7322names) - 1;
	क्रम (i = 0; i < dd->num_pports; ++i) अणु
		dd->pport[i].cpspec->portcntrs =
			kदो_स्मृति_array(dd->cspec->nportcntrs, माप(u64),
				      GFP_KERNEL);
	पूर्ण
पूर्ण

अटल u32 qib_पढ़ो_7322cntrs(काष्ठा qib_devdata *dd, loff_t pos, अक्षर **namep,
			      u64 **cntrp)
अणु
	u32 ret;

	अगर (namep) अणु
		ret = dd->cspec->cntrnamelen;
		अगर (pos >= ret)
			ret = 0; /* final पढ़ो after getting everything */
		अन्यथा
			*namep = (अक्षर *) cntr7322names;
	पूर्ण अन्यथा अणु
		u64 *cntr = dd->cspec->cntrs;
		पूर्णांक i;

		ret = dd->cspec->ncntrs * माप(u64);
		अगर (!cntr || pos >= ret) अणु
			/* everything पढ़ो, or couldn't get memory */
			ret = 0;
			जाओ करोne;
		पूर्ण
		*cntrp = cntr;
		क्रम (i = 0; i < dd->cspec->ncntrs; i++)
			अगर (cntr7322indices[i] & _PORT_64BIT_FLAG)
				*cntr++ = पढ़ो_7322_creg(dd,
							 cntr7322indices[i] &
							 _PORT_CNTR_IDXMASK);
			अन्यथा
				*cntr++ = पढ़ो_7322_creg32(dd,
							   cntr7322indices[i]);
	पूर्ण
करोne:
	वापस ret;
पूर्ण

अटल u32 qib_पढ़ो_7322portcntrs(काष्ठा qib_devdata *dd, loff_t pos, u32 port,
				  अक्षर **namep, u64 **cntrp)
अणु
	u32 ret;

	अगर (namep) अणु
		ret = dd->cspec->portcntrnamelen;
		अगर (pos >= ret)
			ret = 0; /* final पढ़ो after getting everything */
		अन्यथा
			*namep = (अक्षर *)portcntr7322names;
	पूर्ण अन्यथा अणु
		काष्ठा qib_pportdata *ppd = &dd->pport[port];
		u64 *cntr = ppd->cpspec->portcntrs;
		पूर्णांक i;

		ret = dd->cspec->nportcntrs * माप(u64);
		अगर (!cntr || pos >= ret) अणु
			/* everything पढ़ो, or couldn't get memory */
			ret = 0;
			जाओ करोne;
		पूर्ण
		*cntrp = cntr;
		क्रम (i = 0; i < dd->cspec->nportcntrs; i++) अणु
			अगर (portcntr7322indices[i] & _PORT_VIRT_FLAG)
				*cntr++ = qib_portcntr_7322(ppd,
					portcntr7322indices[i] &
					_PORT_CNTR_IDXMASK);
			अन्यथा अगर (portcntr7322indices[i] & _PORT_64BIT_FLAG)
				*cntr++ = पढ़ो_7322_creg_port(ppd,
					   portcntr7322indices[i] &
					    _PORT_CNTR_IDXMASK);
			अन्यथा
				*cntr++ = पढ़ो_7322_creg32_port(ppd,
					   portcntr7322indices[i]);
		पूर्ण
	पूर्ण
करोne:
	वापस ret;
पूर्ण

/**
 * qib_get_7322_faststats - get word counters from chip beक्रमe they overflow
 * @t: contains a poपूर्णांकer to the qlogic_ib device qib_devdata
 *
 * VESTIGIAL IBA7322 has no "small fast counters", so the only
 * real purpose of this function is to मुख्यtain the notion of
 * "active time", which in turn is only logged पूर्णांकo the eeprom,
 * which we करोn;t have, yet, क्रम 7322-based boards.
 *
 * called from add_समयr
 */
अटल व्योम qib_get_7322_faststats(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_devdata *dd = from_समयr(dd, t, stats_समयr);
	काष्ठा qib_pportdata *ppd;
	अचिन्हित दीर्घ flags;
	u64 traffic_wds;
	पूर्णांक pidx;

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;

		/*
		 * If port isn't enabled or not operational ports, or
		 * diags is running (can cause memory diags to fail)
		 * skip this port this समय.
		 */
		अगर (!ppd->link_speed_supported || !(dd->flags & QIB_INITTED)
		    || dd->diag_client)
			जारी;

		/*
		 * Maपूर्णांकain an activity समयr, based on traffic
		 * exceeding a threshold, so we need to check the word-counts
		 * even अगर they are 64-bit.
		 */
		traffic_wds = qib_portcntr_7322(ppd, QIBPORTCNTR_WORDRCV) +
			qib_portcntr_7322(ppd, QIBPORTCNTR_WORDSEND);
		spin_lock_irqsave(&ppd->dd->eep_st_lock, flags);
		traffic_wds -= ppd->dd->traffic_wds;
		ppd->dd->traffic_wds += traffic_wds;
		spin_unlock_irqrestore(&ppd->dd->eep_st_lock, flags);
		अगर (ppd->cpspec->qdr_dfe_on && (ppd->link_speed_active &
						QIB_IB_QDR) &&
		    (ppd->lflags & (QIBL_LINKINIT | QIBL_LINKARMED |
				    QIBL_LINKACTIVE)) &&
		    ppd->cpspec->qdr_dfe_समय &&
		    समय_is_beक्रमe_jअगरfies(ppd->cpspec->qdr_dfe_समय)) अणु
			ppd->cpspec->qdr_dfe_on = 0;

			qib_ग_लिखो_kreg_port(ppd, krp_अटल_adapt_dis(2),
					    ppd->dd->cspec->r1 ?
					    QDR_STATIC_ADAPT_INIT_R1 :
					    QDR_STATIC_ADAPT_INIT);
			क्रमce_h1(ppd);
		पूर्ण
	पूर्ण
	mod_समयr(&dd->stats_समयr, jअगरfies + HZ * ACTIVITY_TIMER);
पूर्ण

/*
 * If we were using MSIx, try to fallback to INTx.
 */
अटल पूर्णांक qib_7322_पूर्णांकr_fallback(काष्ठा qib_devdata *dd)
अणु
	अगर (!dd->cspec->num_msix_entries)
		वापस 0; /* alपढ़ोy using INTx */

	qib_devinfo(dd->pcidev,
		"MSIx interrupt not detected, trying INTx interrupts\n");
	qib_7322_मुक्त_irq(dd);
	अगर (pci_alloc_irq_vectors(dd->pcidev, 1, 1, PCI_IRQ_LEGACY) < 0)
		qib_dev_err(dd, "Failed to enable INTx\n");
	qib_setup_7322_पूर्णांकerrupt(dd, 0);
	वापस 1;
पूर्ण

/*
 * Reset the XGXS (between serdes and IBC).  Slightly less पूर्णांकrusive
 * than resetting the IBC or बाह्यal link state, and useful in some
 * हालs to cause some retraining.  To करो this right, we reset IBC
 * as well, then वापस to previous state (which may be still in reset)
 * NOTE: some callers of this "know" this ग_लिखोs the current value
 * of cpspec->ibcctrl_a as part of it's operation, so अगर that changes,
 * check all callers.
 */
अटल व्योम qib_7322_mini_pcs_reset(काष्ठा qib_pportdata *ppd)
अणु
	u64 val;
	काष्ठा qib_devdata *dd = ppd->dd;
	स्थिर u64 reset_bits = SYM_MASK(IBPCSConfig_0, xcv_rreset) |
		SYM_MASK(IBPCSConfig_0, xcv_treset) |
		SYM_MASK(IBPCSConfig_0, tx_rx_reset);

	val = qib_पढ़ो_kreg_port(ppd, krp_ib_pcsconfig);
	qib_ग_लिखो_kreg(dd, kr_hwerrmask,
		       dd->cspec->hwerrmask & ~HWE_MASK(statusValidNoEop));
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a,
			    ppd->cpspec->ibcctrl_a &
			    ~SYM_MASK(IBCCtrlA_0, IBLinkEn));

	qib_ग_लिखो_kreg_port(ppd, krp_ib_pcsconfig, val | reset_bits);
	qib_पढ़ो_kreg32(dd, kr_scratch);
	qib_ग_लिखो_kreg_port(ppd, krp_ib_pcsconfig, val & ~reset_bits);
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a, ppd->cpspec->ibcctrl_a);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
	qib_ग_लिखो_kreg(dd, kr_hwerrclear,
		       SYM_MASK(HwErrClear, statusValidNoEopClear));
	qib_ग_लिखो_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);
पूर्ण

/*
 * This code क्रम non-IBTA-compliant IB speed negotiation is only known to
 * work क्रम the SDR to DDR transition, and only between an HCA and a चयन
 * with recent firmware.  It is based on observed heuristics, rather than
 * actual knowledge of the non-compliant speed negotiation.
 * It has a number of hard-coded fields, since the hope is to reग_लिखो this
 * when a spec is available on how the negoation is पूर्णांकended to work.
 */
अटल व्योम स्वतःneg_7322_sendpkt(काष्ठा qib_pportdata *ppd, u32 *hdr,
				 u32 dcnt, u32 *data)
अणु
	पूर्णांक i;
	u64 pbc;
	u32 __iomem *piobuf;
	u32 pnum, control, len;
	काष्ठा qib_devdata *dd = ppd->dd;

	i = 0;
	len = 7 + dcnt + 1; /* 7 dword header, dword data, icrc */
	control = qib_7322_setpbc_control(ppd, len, 0, 15);
	pbc = ((u64) control << 32) | len;
	जबतक (!(piobuf = qib_7322_माला_लोendbuf(ppd, pbc, &pnum))) अणु
		अगर (i++ > 15)
			वापस;
		udelay(2);
	पूर्ण
	/* disable header check on this packet, since it can't be valid */
	dd->f_txchk_change(dd, pnum, 1, TXCHK_CHG_TYPE_DIS1, शून्य);
	ग_लिखोq(pbc, piobuf);
	qib_flush_wc();
	qib_pio_copy(piobuf + 2, hdr, 7);
	qib_pio_copy(piobuf + 9, data, dcnt);
	अगर (dd->flags & QIB_USE_SPCL_TRIG) अणु
		u32 spcl_off = (pnum >= dd->piobcnt2k) ? 2047 : 1023;

		qib_flush_wc();
		__raw_ग_लिखोl(0xaebecede, piobuf + spcl_off);
	पूर्ण
	qib_flush_wc();
	qib_sendbuf_करोne(dd, pnum);
	/* and re-enable hdr check */
	dd->f_txchk_change(dd, pnum, 1, TXCHK_CHG_TYPE_ENAB1, शून्य);
पूर्ण

/*
 * _start packet माला_लो sent twice at start, _करोne माला_लो sent twice at end
 */
अटल व्योम qib_स्वतःneg_7322_send(काष्ठा qib_pportdata *ppd, पूर्णांक which)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	अटल u32 swapped;
	u32 dw, i, hcnt, dcnt, *data;
	अटल u32 hdr[7] = अणु 0xf002ffff, 0x48ffff, 0x6400abba पूर्ण;
	अटल u32 madpayload_start[0x40] = अणु
		0x1810103, 0x1, 0x0, 0x0, 0x2c90000, 0x2c9, 0x0, 0x0,
		0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		0x1, 0x1388, 0x15e, 0x1, /* rest 0's */
		पूर्ण;
	अटल u32 madpayload_करोne[0x40] = अणु
		0x1810103, 0x1, 0x0, 0x0, 0x2c90000, 0x2c9, 0x0, 0x0,
		0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		0x40000001, 0x1388, 0x15e, /* rest 0's */
		पूर्ण;

	dcnt = ARRAY_SIZE(madpayload_start);
	hcnt = ARRAY_SIZE(hdr);
	अगर (!swapped) अणु
		/* क्रम मुख्यtainability, करो it at runसमय */
		क्रम (i = 0; i < hcnt; i++) अणु
			dw = (__क्रमce u32) cpu_to_be32(hdr[i]);
			hdr[i] = dw;
		पूर्ण
		क्रम (i = 0; i < dcnt; i++) अणु
			dw = (__क्रमce u32) cpu_to_be32(madpayload_start[i]);
			madpayload_start[i] = dw;
			dw = (__क्रमce u32) cpu_to_be32(madpayload_करोne[i]);
			madpayload_करोne[i] = dw;
		पूर्ण
		swapped = 1;
	पूर्ण

	data = which ? madpayload_करोne : madpayload_start;

	स्वतःneg_7322_sendpkt(ppd, hdr, dcnt, data);
	qib_पढ़ो_kreg64(dd, kr_scratch);
	udelay(2);
	स्वतःneg_7322_sendpkt(ppd, hdr, dcnt, data);
	qib_पढ़ो_kreg64(dd, kr_scratch);
	udelay(2);
पूर्ण

/*
 * Do the असलolute minimum to cause an IB speed change, and make it
 * पढ़ोy, but करोn't actually trigger the change.   The caller will
 * करो that when पढ़ोy (अगर link is in Polling training state, it will
 * happen immediately, otherwise when link next goes करोwn)
 *
 * This routine should only be used as part of the DDR स्वतःnegotation
 * code क्रम devices that are not compliant with IB 1.2 (or code that
 * fixes things up क्रम same).
 *
 * When link has gone करोwn, and स्वतःneg enabled, or स्वतःneg has
 * failed and we give up until next समय we set both speeds, and
 * then we want IBTA enabled as well as "use max enabled speed.
 */
अटल व्योम set_7322_ibspeed_fast(काष्ठा qib_pportdata *ppd, u32 speed)
अणु
	u64 newctrlb;

	newctrlb = ppd->cpspec->ibcctrl_b & ~(IBA7322_IBC_SPEED_MASK |
				    IBA7322_IBC_IBTA_1_2_MASK |
				    IBA7322_IBC_MAX_SPEED_MASK);

	अगर (speed & (speed - 1)) /* multiple speeds */
		newctrlb |= (speed << IBA7322_IBC_SPEED_LSB) |
				    IBA7322_IBC_IBTA_1_2_MASK |
				    IBA7322_IBC_MAX_SPEED_MASK;
	अन्यथा
		newctrlb |= speed == QIB_IB_QDR ?
			IBA7322_IBC_SPEED_QDR | IBA7322_IBC_IBTA_1_2_MASK :
			((speed == QIB_IB_DDR ?
			  IBA7322_IBC_SPEED_DDR : IBA7322_IBC_SPEED_SDR));

	अगर (newctrlb == ppd->cpspec->ibcctrl_b)
		वापस;

	ppd->cpspec->ibcctrl_b = newctrlb;
	qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_b, ppd->cpspec->ibcctrl_b);
	qib_ग_लिखो_kreg(ppd->dd, kr_scratch, 0);
पूर्ण

/*
 * This routine is only used when we are not talking to another
 * IB 1.2-compliant device that we think can करो DDR.
 * (This includes all existing चयन chips as of Oct 2007.)
 * 1.2-compliant devices go directly to DDR prior to reaching INIT
 */
अटल व्योम try_7322_स्वतःneg(काष्ठा qib_pportdata *ppd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags |= QIBL_IB_AUTONEG_INPROG;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	qib_स्वतःneg_7322_send(ppd, 0);
	set_7322_ibspeed_fast(ppd, QIB_IB_DDR);
	qib_7322_mini_pcs_reset(ppd);
	/* 2 msec is minimum length of a poll cycle */
	queue_delayed_work(ib_wq, &ppd->cpspec->स्वतःneg_work,
			   msecs_to_jअगरfies(2));
पूर्ण

/*
 * Handle the empirically determined mechanism क्रम स्वतः-negotiation
 * of DDR speed with चयनes.
 */
अटल व्योम स्वतःneg_7322_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qib_pportdata *ppd;
	u32 i;
	अचिन्हित दीर्घ flags;

	ppd = container_of(work, काष्ठा qib_chippport_specअगरic,
			    स्वतःneg_work.work)->ppd;

	/*
	 * Busy रुको क्रम this first part, it should be at most a
	 * few hundred usec, since we scheduled ourselves क्रम 2msec.
	 */
	क्रम (i = 0; i < 25; i++) अणु
		अगर (SYM_FIELD(ppd->lastibcstat, IBCStatusA_0, LinkState)
		     == IB_7322_LT_STATE_POLLQUIET) अणु
			qib_set_linkstate(ppd, QIB_IB_LINKDOWN_DISABLE);
			अवरोध;
		पूर्ण
		udelay(100);
	पूर्ण

	अगर (!(ppd->lflags & QIBL_IB_AUTONEG_INPROG))
		जाओ करोne; /* we got there early or told to stop */

	/* we expect this to समयout */
	अगर (रुको_event_समयout(ppd->cpspec->स्वतःneg_रुको,
			       !(ppd->lflags & QIBL_IB_AUTONEG_INPROG),
			       msecs_to_jअगरfies(90)))
		जाओ करोne;
	qib_7322_mini_pcs_reset(ppd);

	/* we expect this to समयout */
	अगर (रुको_event_समयout(ppd->cpspec->स्वतःneg_रुको,
			       !(ppd->lflags & QIBL_IB_AUTONEG_INPROG),
			       msecs_to_jअगरfies(1700)))
		जाओ करोne;
	qib_7322_mini_pcs_reset(ppd);

	set_7322_ibspeed_fast(ppd, QIB_IB_SDR);

	/*
	 * Wait up to 250 msec क्रम link to train and get to INIT at DDR;
	 * this should terminate early.
	 */
	रुको_event_समयout(ppd->cpspec->स्वतःneg_रुको,
		!(ppd->lflags & QIBL_IB_AUTONEG_INPROG),
		msecs_to_jअगरfies(250));
करोne:
	अगर (ppd->lflags & QIBL_IB_AUTONEG_INPROG) अणु
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags &= ~QIBL_IB_AUTONEG_INPROG;
		अगर (ppd->cpspec->स्वतःneg_tries == AUTONEG_TRIES) अणु
			ppd->lflags |= QIBL_IB_AUTONEG_FAILED;
			ppd->cpspec->स्वतःneg_tries = 0;
		पूर्ण
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		set_7322_ibspeed_fast(ppd, ppd->link_speed_enabled);
	पूर्ण
पूर्ण

/*
 * This routine is used to request IPG set in the QLogic चयन.
 * Only called अगर r1.
 */
अटल व्योम try_7322_ipg(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_ibport *ibp = &ppd->ibport_data;
	काष्ठा ib_mad_send_buf *send_buf;
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_smp *smp;
	अचिन्हित delay;
	पूर्णांक ret;

	agent = ibp->rvp.send_agent;
	अगर (!agent)
		जाओ retry;

	send_buf = ib_create_send_mad(agent, 0, 0, 0, IB_MGMT_MAD_HDR,
				      IB_MGMT_MAD_DATA, GFP_ATOMIC,
				      IB_MGMT_BASE_VERSION);
	अगर (IS_ERR(send_buf))
		जाओ retry;

	अगर (!ibp->smi_ah) अणु
		काष्ठा ib_ah *ah;

		ah = qib_create_qp0_ah(ibp, be16_to_cpu(IB_LID_PERMISSIVE));
		अगर (IS_ERR(ah))
			ret = PTR_ERR(ah);
		अन्यथा अणु
			send_buf->ah = ah;
			ibp->smi_ah = ibah_to_rvtah(ah);
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		send_buf->ah = &ibp->smi_ah->ibah;
		ret = 0;
	पूर्ण

	smp = send_buf->mad;
	smp->base_version = IB_MGMT_BASE_VERSION;
	smp->mgmt_class = IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE;
	smp->class_version = 1;
	smp->method = IB_MGMT_METHOD_SEND;
	smp->hop_cnt = 1;
	smp->attr_id = QIB_VENDOR_IPG;
	smp->attr_mod = 0;

	अगर (!ret)
		ret = ib_post_send_mad(send_buf, शून्य);
	अगर (ret)
		ib_मुक्त_send_mad(send_buf);
retry:
	delay = 2 << ppd->cpspec->ipg_tries;
	queue_delayed_work(ib_wq, &ppd->cpspec->ipg_work,
			   msecs_to_jअगरfies(delay));
पूर्ण

/*
 * Timeout handler क्रम setting IPG.
 * Only called अगर r1.
 */
अटल व्योम ipg_7322_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qib_pportdata *ppd;

	ppd = container_of(work, काष्ठा qib_chippport_specअगरic,
			   ipg_work.work)->ppd;
	अगर ((ppd->lflags & (QIBL_LINKINIT | QIBL_LINKARMED | QIBL_LINKACTIVE))
	    && ++ppd->cpspec->ipg_tries <= 10)
		try_7322_ipg(ppd);
पूर्ण

अटल u32 qib_7322_iblink_state(u64 ibcs)
अणु
	u32 state = (u32)SYM_FIELD(ibcs, IBCStatusA_0, LinkState);

	चयन (state) अणु
	हाल IB_7322_L_STATE_INIT:
		state = IB_PORT_INIT;
		अवरोध;
	हाल IB_7322_L_STATE_ARM:
		state = IB_PORT_ARMED;
		अवरोध;
	हाल IB_7322_L_STATE_ACTIVE:
	हाल IB_7322_L_STATE_ACT_DEFER:
		state = IB_PORT_ACTIVE;
		अवरोध;
	शेष:
		fallthrough;
	हाल IB_7322_L_STATE_DOWN:
		state = IB_PORT_DOWN;
		अवरोध;
	पूर्ण
	वापस state;
पूर्ण

/* वापसs the IBTA port state, rather than the IBC link training state */
अटल u8 qib_7322_phys_portstate(u64 ibcs)
अणु
	u8 state = (u8)SYM_FIELD(ibcs, IBCStatusA_0, LinkTrainingState);
	वापस qib_7322_physportstate[state];
पूर्ण

अटल पूर्णांक qib_7322_ib_upकरोwn(काष्ठा qib_pportdata *ppd, पूर्णांक ibup, u64 ibcs)
अणु
	पूर्णांक ret = 0, symadj = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक mult;

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags &= ~QIBL_IB_FORCE_NOTIFY;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);

	/* Update our picture of width and speed from chip */
	अगर (ibcs & SYM_MASK(IBCStatusA_0, LinkSpeedQDR)) अणु
		ppd->link_speed_active = QIB_IB_QDR;
		mult = 4;
	पूर्ण अन्यथा अगर (ibcs & SYM_MASK(IBCStatusA_0, LinkSpeedActive)) अणु
		ppd->link_speed_active = QIB_IB_DDR;
		mult = 2;
	पूर्ण अन्यथा अणु
		ppd->link_speed_active = QIB_IB_SDR;
		mult = 1;
	पूर्ण
	अगर (ibcs & SYM_MASK(IBCStatusA_0, LinkWidthActive)) अणु
		ppd->link_width_active = IB_WIDTH_4X;
		mult *= 4;
	पूर्ण अन्यथा
		ppd->link_width_active = IB_WIDTH_1X;
	ppd->delay_mult = ib_rate_to_delay[mult_to_ib_rate(mult)];

	अगर (!ibup) अणु
		u64 clr;

		/* Link went करोwn. */
		/* करो IPG MAD again after linkकरोwn, even अगर last समय failed */
		ppd->cpspec->ipg_tries = 0;
		clr = qib_पढ़ो_kreg_port(ppd, krp_ibcstatus_b) &
			(SYM_MASK(IBCStatusB_0, heartbeat_समयd_out) |
			 SYM_MASK(IBCStatusB_0, heartbeat_crosstalk));
		अगर (clr)
			qib_ग_लिखो_kreg_port(ppd, krp_ibcstatus_b, clr);
		अगर (!(ppd->lflags & (QIBL_IB_AUTONEG_FAILED |
				     QIBL_IB_AUTONEG_INPROG)))
			set_7322_ibspeed_fast(ppd, ppd->link_speed_enabled);
		अगर (!(ppd->lflags & QIBL_IB_AUTONEG_INPROG)) अणु
			काष्ठा qib_qsfp_data *qd =
				&ppd->cpspec->qsfp_data;
			/* unlock the Tx settings, speed may change */
			qib_ग_लिखो_kreg_port(ppd, krp_tx_deemph_override,
				SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				reset_tx_deemphasis_override));
			qib_cancel_sends(ppd);
			/* on link करोwn, ensure sane pcs state */
			qib_7322_mini_pcs_reset(ppd);
			/* schedule the qsfp refresh which should turn the link
			   off */
			अगर (ppd->dd->flags & QIB_HAS_QSFP) अणु
				qd->t_insert = jअगरfies;
				queue_work(ib_wq, &qd->work);
			पूर्ण
			spin_lock_irqsave(&ppd->sdma_lock, flags);
			अगर (__qib_sdma_running(ppd))
				__qib_sdma_process_event(ppd,
					qib_sdma_event_e70_go_idle);
			spin_unlock_irqrestore(&ppd->sdma_lock, flags);
		पूर्ण
		clr = पढ़ो_7322_creg32_port(ppd, crp_iblinkकरोwn);
		अगर (clr == ppd->cpspec->iblnkकरोwnsnap)
			ppd->cpspec->iblnkकरोwndelta++;
	पूर्ण अन्यथा अणु
		अगर (qib_compat_ddr_negotiate &&
		    !(ppd->lflags & (QIBL_IB_AUTONEG_FAILED |
				     QIBL_IB_AUTONEG_INPROG)) &&
		    ppd->link_speed_active == QIB_IB_SDR &&
		    (ppd->link_speed_enabled & QIB_IB_DDR)
		    && ppd->cpspec->स्वतःneg_tries < AUTONEG_TRIES) अणु
			/* we are SDR, and स्वतः-negotiation enabled */
			++ppd->cpspec->स्वतःneg_tries;
			अगर (!ppd->cpspec->ibdeltainprog) अणु
				ppd->cpspec->ibdeltainprog = 1;
				ppd->cpspec->ibsymdelta +=
					पढ़ो_7322_creg32_port(ppd,
						crp_ibsymbolerr) -
						ppd->cpspec->ibsymsnap;
				ppd->cpspec->iblnkerrdelta +=
					पढ़ो_7322_creg32_port(ppd,
						crp_iblinkerrrecov) -
						ppd->cpspec->iblnkerrsnap;
			पूर्ण
			try_7322_स्वतःneg(ppd);
			ret = 1; /* no other IB status change processing */
		पूर्ण अन्यथा अगर ((ppd->lflags & QIBL_IB_AUTONEG_INPROG) &&
			   ppd->link_speed_active == QIB_IB_SDR) अणु
			qib_स्वतःneg_7322_send(ppd, 1);
			set_7322_ibspeed_fast(ppd, QIB_IB_DDR);
			qib_7322_mini_pcs_reset(ppd);
			udelay(2);
			ret = 1; /* no other IB status change processing */
		पूर्ण अन्यथा अगर ((ppd->lflags & QIBL_IB_AUTONEG_INPROG) &&
			   (ppd->link_speed_active & QIB_IB_DDR)) अणु
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			ppd->lflags &= ~(QIBL_IB_AUTONEG_INPROG |
					 QIBL_IB_AUTONEG_FAILED);
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
			ppd->cpspec->स्वतःneg_tries = 0;
			/* re-enable SDR, क्रम next link करोwn */
			set_7322_ibspeed_fast(ppd, ppd->link_speed_enabled);
			wake_up(&ppd->cpspec->स्वतःneg_रुको);
			symadj = 1;
		पूर्ण अन्यथा अगर (ppd->lflags & QIBL_IB_AUTONEG_FAILED) अणु
			/*
			 * Clear स्वतःneg failure flag, and करो setup
			 * so we'll try next समय link goes करोwn and
			 * back to INIT (possibly connected to a
			 * dअगरferent device).
			 */
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			ppd->lflags &= ~QIBL_IB_AUTONEG_FAILED;
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
			ppd->cpspec->ibcctrl_b |= IBA7322_IBC_IBTA_1_2_MASK;
			symadj = 1;
		पूर्ण
		अगर (!(ppd->lflags & QIBL_IB_AUTONEG_INPROG)) अणु
			symadj = 1;
			अगर (ppd->dd->cspec->r1 && ppd->cpspec->ipg_tries <= 10)
				try_7322_ipg(ppd);
			अगर (!ppd->cpspec->recovery_init)
				setup_7322_link_recovery(ppd, 0);
			ppd->cpspec->qdr_dfe_समय = jअगरfies +
				msecs_to_jअगरfies(QDR_DFE_DISABLE_DELAY);
		पूर्ण
		ppd->cpspec->ibmalfusesnap = 0;
		ppd->cpspec->ibmalfsnap = पढ़ो_7322_creg32_port(ppd,
			crp_errlink);
	पूर्ण
	अगर (symadj) अणु
		ppd->cpspec->iblnkकरोwnsnap =
			पढ़ो_7322_creg32_port(ppd, crp_iblinkकरोwn);
		अगर (ppd->cpspec->ibdeltainprog) अणु
			ppd->cpspec->ibdeltainprog = 0;
			ppd->cpspec->ibsymdelta += पढ़ो_7322_creg32_port(ppd,
				crp_ibsymbolerr) - ppd->cpspec->ibsymsnap;
			ppd->cpspec->iblnkerrdelta += पढ़ो_7322_creg32_port(ppd,
				crp_iblinkerrrecov) - ppd->cpspec->iblnkerrsnap;
		पूर्ण
	पूर्ण अन्यथा अगर (!ibup && qib_compat_ddr_negotiate &&
		   !ppd->cpspec->ibdeltainprog &&
			!(ppd->lflags & QIBL_IB_AUTONEG_INPROG)) अणु
		ppd->cpspec->ibdeltainprog = 1;
		ppd->cpspec->ibsymsnap = पढ़ो_7322_creg32_port(ppd,
			crp_ibsymbolerr);
		ppd->cpspec->iblnkerrsnap = पढ़ो_7322_creg32_port(ppd,
			crp_iblinkerrrecov);
	पूर्ण

	अगर (!ret)
		qib_setup_7322_setextled(ppd, ibup);
	वापस ret;
पूर्ण

/*
 * Does पढ़ो/modअगरy/ग_लिखो to appropriate रेजिस्टरs to
 * set output and direction bits selected by mask.
 * these are in their canonical postions (e.g. lsb of
 * dir will end up in D48 of extctrl on existing chips).
 * वापसs contents of GP Inमाला_दो.
 */
अटल पूर्णांक gpio_7322_mod(काष्ठा qib_devdata *dd, u32 out, u32 dir, u32 mask)
अणु
	u64 पढ़ो_val, new_out;
	अचिन्हित दीर्घ flags;

	अगर (mask) अणु
		/* some bits being written, lock access to GPIO */
		dir &= mask;
		out &= mask;
		spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
		dd->cspec->extctrl &= ~((u64)mask << SYM_LSB(EXTCtrl, GPIOOe));
		dd->cspec->extctrl |= ((u64) dir << SYM_LSB(EXTCtrl, GPIOOe));
		new_out = (dd->cspec->gpio_out & ~mask) | out;

		qib_ग_लिखो_kreg(dd, kr_extctrl, dd->cspec->extctrl);
		qib_ग_लिखो_kreg(dd, kr_gpio_out, new_out);
		dd->cspec->gpio_out = new_out;
		spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
	पूर्ण
	/*
	 * It is unlikely that a पढ़ो at this समय would get valid
	 * data on a pin whose direction line was set in the same
	 * call to this function. We include the पढ़ो here because
	 * that allows us to potentially combine a change on one pin with
	 * a पढ़ो on another, and because the old code did something like
	 * this.
	 */
	पढ़ो_val = qib_पढ़ो_kreg64(dd, kr_extstatus);
	वापस SYM_FIELD(पढ़ो_val, EXTStatus, GPIOIn);
पूर्ण

/* Enable ग_लिखोs to config EEPROM, अगर possible. Returns previous state */
अटल पूर्णांक qib_7322_eeprom_wen(काष्ठा qib_devdata *dd, पूर्णांक wen)
अणु
	पूर्णांक prev_wen;
	u32 mask;

	mask = 1 << QIB_EEPROM_WEN_NUM;
	prev_wen = ~gpio_7322_mod(dd, 0, 0, 0) >> QIB_EEPROM_WEN_NUM;
	gpio_7322_mod(dd, wen ? 0 : mask, mask, mask);

	वापस prev_wen & 1;
पूर्ण

/*
 * Read fundamental info we need to use the chip.  These are
 * the रेजिस्टरs that describe chip capabilities, and are
 * saved in shaकरोw रेजिस्टरs.
 */
अटल व्योम get_7322_chip_params(काष्ठा qib_devdata *dd)
अणु
	u64 val;
	u32 piobufs;
	पूर्णांक mtu;

	dd->palign = qib_पढ़ो_kreg32(dd, kr_pagealign);

	dd->uregbase = qib_पढ़ो_kreg32(dd, kr_userregbase);

	dd->rcvtidcnt = qib_पढ़ो_kreg32(dd, kr_rcvtidcnt);
	dd->rcvtidbase = qib_पढ़ो_kreg32(dd, kr_rcvtidbase);
	dd->rcvegrbase = qib_पढ़ो_kreg32(dd, kr_rcvegrbase);
	dd->piobufbase = qib_पढ़ो_kreg64(dd, kr_sendpiobufbase);
	dd->pio2k_bufbase = dd->piobufbase & 0xffffffff;

	val = qib_पढ़ो_kreg64(dd, kr_sendpiobufcnt);
	dd->piobcnt2k = val & ~0U;
	dd->piobcnt4k = val >> 32;
	val = qib_पढ़ो_kreg64(dd, kr_sendpiosize);
	dd->piosize2k = val & ~0U;
	dd->piosize4k = val >> 32;

	mtu = ib_mtu_क्रमागत_to_पूर्णांक(qib_ibmtu);
	अगर (mtu == -1)
		mtu = QIB_DEFAULT_MTU;
	dd->pport[0].ibmtu = (u32)mtu;
	dd->pport[1].ibmtu = (u32)mtu;

	/* these may be adjusted in init_chip_wc_pat() */
	dd->pio2kbase = (u32 __iomem *)
		((अक्षर __iomem *) dd->kregbase + dd->pio2k_bufbase);
	dd->pio4kbase = (u32 __iomem *)
		((अक्षर __iomem *) dd->kregbase +
		 (dd->piobufbase >> 32));
	/*
	 * 4K buffers take 2 pages; we use roundup just to be
	 * paranoid; we calculate it once here, rather than on
	 * ever buf allocate
	 */
	dd->align4k = ALIGN(dd->piosize4k, dd->palign);

	piobufs = dd->piobcnt4k + dd->piobcnt2k + NUM_VL15_BUFS;

	dd->pioavregs = ALIGN(piobufs, माप(u64) * BITS_PER_BYTE / 2) /
		(माप(u64) * BITS_PER_BYTE / 2);
पूर्ण

/*
 * The chip base addresses in cspec and cpspec have to be set
 * after possible init_chip_wc_pat(), rather than in
 * get_7322_chip_params(), so split out as separate function
 */
अटल व्योम qib_7322_set_baseaddrs(काष्ठा qib_devdata *dd)
अणु
	u32 cregbase;

	cregbase = qib_पढ़ो_kreg32(dd, kr_counterregbase);

	dd->cspec->cregbase = (u64 __iomem *)(cregbase +
		(अक्षर __iomem *)dd->kregbase);

	dd->egrtidbase = (u64 __iomem *)
		((अक्षर __iomem *) dd->kregbase + dd->rcvegrbase);

	/* port रेजिस्टरs are defined as relative to base of chip */
	dd->pport[0].cpspec->kpregbase =
		(u64 __iomem *)((अक्षर __iomem *)dd->kregbase);
	dd->pport[1].cpspec->kpregbase =
		(u64 __iomem *)(dd->palign +
		(अक्षर __iomem *)dd->kregbase);
	dd->pport[0].cpspec->cpregbase =
		(u64 __iomem *)(qib_पढ़ो_kreg_port(&dd->pport[0],
		kr_counterregbase) + (अक्षर __iomem *)dd->kregbase);
	dd->pport[1].cpspec->cpregbase =
		(u64 __iomem *)(qib_पढ़ो_kreg_port(&dd->pport[1],
		kr_counterregbase) + (अक्षर __iomem *)dd->kregbase);
पूर्ण

/*
 * This is a fairly special-purpose observer, so we only support
 * the port-specअगरic parts of SendCtrl
 */

#घोषणा SENDCTRL_SHADOWED (SYM_MASK(SendCtrl_0, SendEnable) |		\
			   SYM_MASK(SendCtrl_0, SDmaEnable) |		\
			   SYM_MASK(SendCtrl_0, SDmaIntEnable) |	\
			   SYM_MASK(SendCtrl_0, SDmaSingleDescriptor) | \
			   SYM_MASK(SendCtrl_0, SDmaHalt) |		\
			   SYM_MASK(SendCtrl_0, IBVLArbiterEn) |	\
			   SYM_MASK(SendCtrl_0, ForceCreditUpToDate))

अटल पूर्णांक sendctrl_hook(काष्ठा qib_devdata *dd,
			 स्थिर काष्ठा diag_observer *op, u32 offs,
			 u64 *data, u64 mask, पूर्णांक only_32)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित idx;
	अचिन्हित pidx;
	काष्ठा qib_pportdata *ppd = शून्य;
	u64 local_data, all_bits;

	/*
	 * The fixed correspondence between Physical ports and pports is
	 * severed. We need to hunt क्रम the ppd that corresponds
	 * to the offset we got. And we have to करो that without admitting
	 * we know the stride, apparently.
	 */
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		u64 __iomem *psptr;
		u32 psoffs;

		ppd = dd->pport + pidx;
		अगर (!ppd->cpspec->kpregbase)
			जारी;

		psptr = ppd->cpspec->kpregbase + krp_sendctrl;
		psoffs = (u32) (psptr - dd->kregbase) * माप(*psptr);
		अगर (psoffs == offs)
			अवरोध;
	पूर्ण

	/* If pport is not being managed by driver, just aव्योम shaकरोws. */
	अगर (pidx >= dd->num_pports)
		ppd = शून्य;

	/* In any हाल, "idx" is flat index in kreg space */
	idx = offs / माप(u64);

	all_bits = ~0ULL;
	अगर (only_32)
		all_bits >>= 32;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);
	अगर (!ppd || (mask & all_bits) != all_bits) अणु
		/*
		 * At least some mask bits are zero, so we need
		 * to पढ़ो. The judgement call is whether from
		 * reg or shaकरोw. First-cut: पढ़ो reg, and complain
		 * अगर any bits which should be shaकरोwed are dअगरferent
		 * from their shaकरोwed value.
		 */
		अगर (only_32)
			local_data = (u64)qib_पढ़ो_kreg32(dd, idx);
		अन्यथा
			local_data = qib_पढ़ो_kreg64(dd, idx);
		*data = (local_data & ~mask) | (*data & mask);
	पूर्ण
	अगर (mask) अणु
		/*
		 * At least some mask bits are one, so we need
		 * to ग_लिखो, but only shaकरोw some bits.
		 */
		u64 sval, tval; /* Shaकरोwed, transient */

		/*
		 * New shaकरोw val is bits we करोn't want to touch,
		 * ORed with bits we करो, that are पूर्णांकended क्रम shaकरोw.
		 */
		अगर (ppd) अणु
			sval = ppd->p_sendctrl & ~mask;
			sval |= *data & SENDCTRL_SHADOWED & mask;
			ppd->p_sendctrl = sval;
		पूर्ण अन्यथा
			sval = *data & SENDCTRL_SHADOWED & mask;
		tval = sval | (*data & ~SENDCTRL_SHADOWED & mask);
		qib_ग_लिखो_kreg(dd, idx, tval);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0Ull);
	पूर्ण
	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
	वापस only_32 ? 4 : 8;
पूर्ण

अटल स्थिर काष्ठा diag_observer sendctrl_0_observer = अणु
	sendctrl_hook, KREG_IDX(SendCtrl_0) * माप(u64),
	KREG_IDX(SendCtrl_0) * माप(u64)
पूर्ण;

अटल स्थिर काष्ठा diag_observer sendctrl_1_observer = अणु
	sendctrl_hook, KREG_IDX(SendCtrl_1) * माप(u64),
	KREG_IDX(SendCtrl_1) * माप(u64)
पूर्ण;

अटल uलघु sdma_fetch_prio = 8;
module_param_named(sdma_fetch_prio, sdma_fetch_prio, uलघु, S_IRUGO);
MODULE_PARM_DESC(sdma_fetch_prio, "SDMA descriptor fetch priority");

/* Besides logging QSFP events, we set appropriate TxDDS values */
अटल व्योम init_txdds_table(काष्ठा qib_pportdata *ppd, पूर्णांक override);

अटल व्योम qsfp_7322_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qib_qsfp_data *qd;
	काष्ठा qib_pportdata *ppd;
	अचिन्हित दीर्घ pwrup;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 le2;

	qd = container_of(work, काष्ठा qib_qsfp_data, work);
	ppd = qd->ppd;
	pwrup = qd->t_insert +
		msecs_to_jअगरfies(QSFP_PWR_LAG_MSEC - QSFP_MODPRS_LAG_MSEC);

	/* Delay क्रम 20 msecs to allow ModPrs resistor to setup */
	mdelay(QSFP_MODPRS_LAG_MSEC);

	अगर (!qib_qsfp_mod_present(ppd)) अणु
		ppd->cpspec->qsfp_data.modpresent = 0;
		/* Set the physical link to disabled */
		qib_set_ib_7322_lstate(ppd, 0,
				       QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags &= ~QIBL_LINKV;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	पूर्ण अन्यथा अणु
		/*
		 * Some QSFP's not only करो not respond until the full घातer-up
		 * समय, but may behave badly अगर we try. So hold off responding
		 * to insertion.
		 */
		जबतक (1) अणु
			अगर (समय_is_beक्रमe_jअगरfies(pwrup))
				अवरोध;
			msleep(20);
		पूर्ण

		ret = qib_refresh_qsfp_cache(ppd, &qd->cache);

		/*
		 * Need to change LE2 back to शेषs अगर we couldn't
		 * पढ़ो the cable type (to handle cable swaps), so करो this
		 * even on failure to पढ़ो cable inक्रमmation.  We करोn't
		 * get here क्रम QME, so IS_QME check not needed here.
		 */
		अगर (!ret && !ppd->dd->cspec->r1) अणु
			अगर (QSFP_IS_ACTIVE_FAR(qd->cache.tech))
				le2 = LE2_QME;
			अन्यथा अगर (qd->cache.atten[1] >= qib_दीर्घ_atten &&
				 QSFP_IS_CU(qd->cache.tech))
				le2 = LE2_5m;
			अन्यथा
				le2 = LE2_DEFAULT;
		पूर्ण अन्यथा
			le2 = LE2_DEFAULT;
		ibsd_wr_allchans(ppd, 13, (le2 << 7), BMASK(9, 7));
		/*
		 * We always change parameteters, since we can choose
		 * values क्रम cables without eeproms, and the cable may have
		 * changed from a cable with full or partial eeprom content
		 * to one with partial or no content.
		 */
		init_txdds_table(ppd, 0);
		/* The physical link is being re-enabled only when the
		 * previous state was DISABLED and the VALID bit is not
		 * set. This should only happen when  the cable has been
		 * physically pulled. */
		अगर (!ppd->cpspec->qsfp_data.modpresent &&
		    (ppd->lflags & (QIBL_LINKV | QIBL_IB_LINK_DISABLED))) अणु
			ppd->cpspec->qsfp_data.modpresent = 1;
			qib_set_ib_7322_lstate(ppd, 0,
				QLOGIC_IB_IBCC_LINKINITCMD_SLEEP);
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			ppd->lflags |= QIBL_LINKV;
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * There is little we can करो but complain to the user अगर QSFP
 * initialization fails.
 */
अटल व्योम qib_init_7322_qsfp(काष्ठा qib_pportdata *ppd)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qib_qsfp_data *qd = &ppd->cpspec->qsfp_data;
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 mod_prs_bit = QSFP_GPIO_MOD_PRS_N;

	mod_prs_bit <<= (QSFP_GPIO_PORT2_SHIFT * ppd->hw_pidx);
	qd->ppd = ppd;
	qib_qsfp_init(qd, qsfp_7322_event);
	spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
	dd->cspec->extctrl |= (mod_prs_bit << SYM_LSB(EXTCtrl, GPIOInvert));
	dd->cspec->gpio_mask |= mod_prs_bit;
	qib_ग_लिखो_kreg(dd, kr_extctrl, dd->cspec->extctrl);
	qib_ग_लिखो_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
	spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
पूर्ण

/*
 * called at device initialization समय, and also अगर the txselect
 * module parameter is changed.  This is used क्रम cables that करोn't
 * have valid QSFP EEPROMs (not present, or attenuation is zero).
 * We initialize to the शेष, then अगर there is a specअगरic
 * unit,port match, we use that (and set it immediately, क्रम the
 * current speed, अगर the link is at INIT or better).
 * String क्रमmat is "default# unit#,port#=# ... u,p=#", separators must
 * be a SPACE अक्षरacter.  A newline terminates.  The u,p=# tuples may
 * optionally have "u,p=#,#", where the final # is the H1 value
 * The last specअगरic match is used (actually, all are used, but last
 * one is the one that winds up set); अगर none at all, fall back on शेष.
 */
अटल व्योम set_no_qsfp_atten(काष्ठा qib_devdata *dd, पूर्णांक change)
अणु
	अक्षर *nxt, *str;
	u32 pidx, unit, port, deflt, h1;
	अचिन्हित दीर्घ val;
	पूर्णांक any = 0, seth1;
	पूर्णांक txdds_size;

	str = txselect_list;

	/* शेष number is validated in setup_txselect() */
	deflt = simple_म_से_अदीर्घ(str, &nxt, 0);
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx)
		dd->pport[pidx].cpspec->no_eep = deflt;

	txdds_size = TXDDS_TABLE_SZ + TXDDS_EXTRA_SZ;
	अगर (IS_QME(dd) || IS_QMH(dd))
		txdds_size += TXDDS_MFG_SZ;

	जबतक (*nxt && nxt[1]) अणु
		str = ++nxt;
		unit = simple_म_से_अदीर्घ(str, &nxt, 0);
		अगर (nxt == str || !*nxt || *nxt != ',') अणु
			जबतक (*nxt && *nxt++ != ' ') /* skip to next, अगर any */
				;
			जारी;
		पूर्ण
		str = ++nxt;
		port = simple_म_से_अदीर्घ(str, &nxt, 0);
		अगर (nxt == str || *nxt != '=') अणु
			जबतक (*nxt && *nxt++ != ' ') /* skip to next, अगर any */
				;
			जारी;
		पूर्ण
		str = ++nxt;
		val = simple_म_से_अदीर्घ(str, &nxt, 0);
		अगर (nxt == str) अणु
			जबतक (*nxt && *nxt++ != ' ') /* skip to next, अगर any */
				;
			जारी;
		पूर्ण
		अगर (val >= txdds_size)
			जारी;
		seth1 = 0;
		h1 = 0; /* gcc thinks it might be used uninitted */
		अगर (*nxt == ',' && nxt[1]) अणु
			str = ++nxt;
			h1 = (u32)simple_म_से_अदीर्घ(str, &nxt, 0);
			अगर (nxt == str)
				जबतक (*nxt && *nxt++ != ' ') /* skip */
					;
			अन्यथा
				seth1 = 1;
		पूर्ण
		क्रम (pidx = 0; dd->unit == unit && pidx < dd->num_pports;
		     ++pidx) अणु
			काष्ठा qib_pportdata *ppd = &dd->pport[pidx];

			अगर (ppd->port != port || !ppd->link_speed_supported)
				जारी;
			ppd->cpspec->no_eep = val;
			अगर (seth1)
				ppd->cpspec->h1_val = h1;
			/* now change the IBC and serdes, overriding generic */
			init_txdds_table(ppd, 1);
			/* Re-enable the physical state machine on mezz boards
			 * now that the correct settings have been set.
			 * QSFP boards are handles by the QSFP event handler */
			अगर (IS_QMH(dd) || IS_QME(dd))
				qib_set_ib_7322_lstate(ppd, 0,
					    QLOGIC_IB_IBCC_LINKINITCMD_SLEEP);
			any++;
		पूर्ण
		अगर (*nxt == '\n')
			अवरोध; /* करोne */
	पूर्ण
	अगर (change && !any) अणु
		/* no specअगरic setting, use the शेष.
		 * Change the IBC and serdes, but since it's
		 * general, करोn't override specअगरic settings.
		 */
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx)
			अगर (dd->pport[pidx].link_speed_supported)
				init_txdds_table(&dd->pport[pidx], 0);
	पूर्ण
पूर्ण

/* handle the txselect parameter changing */
अटल पूर्णांक setup_txselect(स्थिर अक्षर *str, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा qib_devdata *dd;
	अचिन्हित दीर्घ index, val;
	अक्षर *n;

	अगर (म_माप(str) >= ARRAY_SIZE(txselect_list)) अणु
		pr_info("txselect_values string too long\n");
		वापस -ENOSPC;
	पूर्ण
	val = simple_म_से_अदीर्घ(str, &n, 0);
	अगर (n == str || val >= (TXDDS_TABLE_SZ + TXDDS_EXTRA_SZ +
				TXDDS_MFG_SZ)) अणु
		pr_info("txselect_values must start with a number < %d\n",
			TXDDS_TABLE_SZ + TXDDS_EXTRA_SZ + TXDDS_MFG_SZ);
		वापस -EINVAL;
	पूर्ण
	म_नकलन(txselect_list, str, ARRAY_SIZE(txselect_list) - 1);

	xa_क्रम_each(&qib_dev_table, index, dd)
		अगर (dd->deviceid == PCI_DEVICE_ID_QLOGIC_IB_7322)
			set_no_qsfp_atten(dd, 1);
	वापस 0;
पूर्ण

/*
 * Write the final few रेजिस्टरs that depend on some of the
 * init setup.  Done late in init, just beक्रमe bringing up
 * the serdes.
 */
अटल पूर्णांक qib_late_7322_initreg(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret = 0, n;
	u64 val;

	qib_ग_लिखो_kreg(dd, kr_rcvhdrentsize, dd->rcvhdrentsize);
	qib_ग_लिखो_kreg(dd, kr_rcvhdrsize, dd->rcvhdrsize);
	qib_ग_लिखो_kreg(dd, kr_rcvhdrcnt, dd->rcvhdrcnt);
	qib_ग_लिखो_kreg(dd, kr_sendpioavailaddr, dd->pioavailregs_phys);
	val = qib_पढ़ो_kreg64(dd, kr_sendpioavailaddr);
	अगर (val != dd->pioavailregs_phys) अणु
		qib_dev_err(dd,
			"Catastrophic software error, SendPIOAvailAddr written as %lx, read back as %llx\n",
			(अचिन्हित दीर्घ) dd->pioavailregs_phys,
			(अचिन्हित दीर्घ दीर्घ) val);
		ret = -EINVAL;
	पूर्ण

	n = dd->piobcnt2k + dd->piobcnt4k + NUM_VL15_BUFS;
	qib_7322_txchk_change(dd, 0, n, TXCHK_CHG_TYPE_KERN, शून्य);
	/* driver sends get pkey, lid, etc. checking also, to catch bugs */
	qib_7322_txchk_change(dd, 0, n, TXCHK_CHG_TYPE_ENAB1, शून्य);

	qib_रेजिस्टर_observer(dd, &sendctrl_0_observer);
	qib_रेजिस्टर_observer(dd, &sendctrl_1_observer);

	dd->control &= ~QLOGIC_IB_C_SDMAFETCHPRIOEN;
	qib_ग_लिखो_kreg(dd, kr_control, dd->control);
	/*
	 * Set SendDmaFetchPriority and init Tx params, including
	 * QSFP handler on boards that have QSFP.
	 * First set our शेष attenuation entry क्रम cables that
	 * करोn't have valid attenuation.
	 */
	set_no_qsfp_atten(dd, 0);
	क्रम (n = 0; n < dd->num_pports; ++n) अणु
		काष्ठा qib_pportdata *ppd = dd->pport + n;

		qib_ग_लिखो_kreg_port(ppd, krp_senddmaprioritythld,
				    sdma_fetch_prio & 0xf);
		/* Initialize qsfp अगर present on board. */
		अगर (dd->flags & QIB_HAS_QSFP)
			qib_init_7322_qsfp(ppd);
	पूर्ण
	dd->control |= QLOGIC_IB_C_SDMAFETCHPRIOEN;
	qib_ग_लिखो_kreg(dd, kr_control, dd->control);

	वापस ret;
पूर्ण

/* per IB port errors.  */
#घोषणा SENDCTRL_PIBP (MASK_ACROSS(0, 1) | MASK_ACROSS(3, 3) | \
	MASK_ACROSS(8, 15))
#घोषणा RCVCTRL_PIBP (MASK_ACROSS(0, 17) | MASK_ACROSS(39, 41))
#घोषणा ERRS_PIBP (MASK_ACROSS(57, 58) | MASK_ACROSS(54, 54) | \
	MASK_ACROSS(36, 49) | MASK_ACROSS(29, 34) | MASK_ACROSS(14, 17) | \
	MASK_ACROSS(0, 11))

/*
 * Write the initialization per-port रेजिस्टरs that need to be करोne at
 * driver load and after reset completes (i.e., that aren't करोne as part
 * of other init procedures called from qib_init.c).
 * Some of these should be redundant on reset, but play safe.
 */
अटल व्योम ग_लिखो_7322_init_portregs(काष्ठा qib_pportdata *ppd)
अणु
	u64 val;
	पूर्णांक i;

	अगर (!ppd->link_speed_supported) अणु
		/* no buffer credits क्रम this port */
		क्रम (i = 1; i < 8; i++)
			qib_ग_लिखो_kreg_port(ppd, krp_rxcreditvl0 + i, 0);
		qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_b, 0);
		qib_ग_लिखो_kreg(ppd->dd, kr_scratch, 0);
		वापस;
	पूर्ण

	/*
	 * Set the number of supported भव lanes in IBC,
	 * क्रम flow control packet handling on unsupported VLs
	 */
	val = qib_पढ़ो_kreg_port(ppd, krp_ibsdtestअगरtx);
	val &= ~SYM_MASK(IB_SDTEST_IF_TX_0, VL_CAP);
	val |= (u64)(ppd->vls_supported - 1) <<
		SYM_LSB(IB_SDTEST_IF_TX_0, VL_CAP);
	qib_ग_लिखो_kreg_port(ppd, krp_ibsdtestअगरtx, val);

	qib_ग_लिखो_kreg_port(ppd, krp_rcvbthqp, QIB_KD_QP);

	/* enable tx header checking */
	qib_ग_लिखो_kreg_port(ppd, krp_sendcheckcontrol, IBA7322_SENDCHK_PKEY |
			    IBA7322_SENDCHK_BTHQP | IBA7322_SENDCHK_SLID |
			    IBA7322_SENDCHK_RAW_IPV6 | IBA7322_SENDCHK_MINSZ);

	qib_ग_लिखो_kreg_port(ppd, krp_ncmodectrl,
		SYM_MASK(IBNCModeCtrl_0, ScrambleCapLocal));

	/*
	 * Unconditionally clear the bufmask bits.  If SDMA is
	 * enabled, we'll set them appropriately later.
	 */
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabufmask0, 0);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabufmask1, 0);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabufmask2, 0);
	अगर (ppd->dd->cspec->r1)
		ppd->p_sendctrl |= SYM_MASK(SendCtrl_0, ForceCreditUpToDate);
पूर्ण

/*
 * Write the initialization per-device रेजिस्टरs that need to be करोne at
 * driver load and after reset completes (i.e., that aren't करोne as part
 * of other init procedures called from qib_init.c).  Also ग_लिखो per-port
 * रेजिस्टरs that are affected by overall device config, such as QP mapping
 * Some of these should be redundant on reset, but play safe.
 */
अटल व्योम ग_लिखो_7322_initregs(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_pportdata *ppd;
	पूर्णांक i, pidx;
	u64 val;

	/* Set Multicast QPs received by port 2 to map to context one. */
	qib_ग_लिखो_kreg(dd, KREG_IDX(RcvQPMulticastContext_1), 1);

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		अचिन्हित n, regno;
		अचिन्हित दीर्घ flags;

		अगर (dd->n_krcv_queues < 2 ||
			!dd->pport[pidx].link_speed_supported)
			जारी;

		ppd = &dd->pport[pidx];

		/* be paranoid against later code motion, etc. */
		spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);
		ppd->p_rcvctrl |= SYM_MASK(RcvCtrl_0, RcvQPMapEnable);
		spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);

		/* Initialize QP to context mapping */
		regno = krp_rcvqpmaptable;
		val = 0;
		अगर (dd->num_pports > 1)
			n = dd->first_user_ctxt / dd->num_pports;
		अन्यथा
			n = dd->first_user_ctxt - 1;
		क्रम (i = 0; i < 32; ) अणु
			अचिन्हित ctxt;

			अगर (dd->num_pports > 1)
				ctxt = (i % n) * dd->num_pports + pidx;
			अन्यथा अगर (i % n)
				ctxt = (i % n) + 1;
			अन्यथा
				ctxt = ppd->hw_pidx;
			val |= ctxt << (5 * (i % 6));
			i++;
			अगर (i % 6 == 0) अणु
				qib_ग_लिखो_kreg_port(ppd, regno, val);
				val = 0;
				regno++;
			पूर्ण
		पूर्ण
		qib_ग_लिखो_kreg_port(ppd, regno, val);
	पूर्ण

	/*
	 * Setup up पूर्णांकerrupt mitigation क्रम kernel contexts, but
	 * not user contexts (user contexts use पूर्णांकerrupts when
	 * stalled रुकोing क्रम any packet, so want those पूर्णांकerrupts
	 * right away).
	 */
	क्रम (i = 0; i < dd->first_user_ctxt; i++) अणु
		dd->cspec->rcvavail_समयout[i] = rcv_पूर्णांक_समयout;
		qib_ग_लिखो_kreg(dd, kr_rcvavailसमयout + i, rcv_पूर्णांक_समयout);
	पूर्ण

	/*
	 * Initialize  as (disabled) rcvflow tables.  Application code
	 * will setup each flow as it uses the flow.
	 * Doesn't clear any of the error bits that might be set.
	 */
	val = TIDFLOW_ERRBITS; /* these are W1C */
	क्रम (i = 0; i < dd->cfgctxts; i++) अणु
		पूर्णांक flow;

		क्रम (flow = 0; flow < NUM_TIDFLOWS_CTXT; flow++)
			qib_ग_लिखो_ureg(dd, ur_rcvflowtable+flow, val, i);
	पूर्ण

	/*
	 * dual cards init to dual port recovery, single port cards to
	 * the one port.  Dual port cards may later adjust to 1 port,
	 * and then back to dual port अगर both ports are connected
	 * */
	अगर (dd->num_pports)
		setup_7322_link_recovery(dd->pport, dd->num_pports > 1);
पूर्ण

अटल पूर्णांक qib_init_7322_variables(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_pportdata *ppd;
	अचिन्हित features, pidx, sbufcnt;
	पूर्णांक ret, mtu;
	u32 sbufs, updthresh;
	resource_माप_प्रकार vl15off;

	/* pport काष्ठाs are contiguous, allocated after devdata */
	ppd = (काष्ठा qib_pportdata *)(dd + 1);
	dd->pport = ppd;
	ppd[0].dd = dd;
	ppd[1].dd = dd;

	dd->cspec = (काष्ठा qib_chip_specअगरic *)(ppd + 2);

	ppd[0].cpspec = (काष्ठा qib_chippport_specअगरic *)(dd->cspec + 1);
	ppd[1].cpspec = &ppd[0].cpspec[1];
	ppd[0].cpspec->ppd = &ppd[0]; /* क्रम स्वतःneg_7322_work() */
	ppd[1].cpspec->ppd = &ppd[1]; /* क्रम स्वतःneg_7322_work() */

	spin_lock_init(&dd->cspec->rcvmod_lock);
	spin_lock_init(&dd->cspec->gpio_lock);

	/* we haven't yet set QIB_PRESENT, so use पढ़ो directly */
	dd->revision = पढ़ोq(&dd->kregbase[kr_revision]);

	अगर ((dd->revision & 0xffffffffU) == 0xffffffffU) अणु
		qib_dev_err(dd,
			"Revision register read failure, giving up initialization\n");
		ret = -ENODEV;
		जाओ bail;
	पूर्ण
	dd->flags |= QIB_PRESENT;  /* now रेजिस्टर routines work */

	dd->majrev = (u8) SYM_FIELD(dd->revision, Revision_R, ChipRevMajor);
	dd->minrev = (u8) SYM_FIELD(dd->revision, Revision_R, ChipRevMinor);
	dd->cspec->r1 = dd->minrev == 1;

	get_7322_chip_params(dd);
	features = qib_7322_boardname(dd);

	/* now that piobcnt2k and 4k set, we can allocate these */
	sbufcnt = dd->piobcnt2k + dd->piobcnt4k +
		NUM_VL15_BUFS + BITS_PER_LONG - 1;
	sbufcnt /= BITS_PER_LONG;
	dd->cspec->sendchkenable =
		kदो_स्मृति_array(sbufcnt, माप(*dd->cspec->sendchkenable),
			      GFP_KERNEL);
	dd->cspec->sendgrhchk =
		kदो_स्मृति_array(sbufcnt, माप(*dd->cspec->sendgrhchk),
			      GFP_KERNEL);
	dd->cspec->sendibchk =
		kदो_स्मृति_array(sbufcnt, माप(*dd->cspec->sendibchk),
			      GFP_KERNEL);
	अगर (!dd->cspec->sendchkenable || !dd->cspec->sendgrhchk ||
		!dd->cspec->sendibchk) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	ppd = dd->pport;

	/*
	 * GPIO bits क्रम TWSI data and घड़ी,
	 * used क्रम serial EEPROM.
	 */
	dd->gpio_sda_num = _QIB_GPIO_SDA_NUM;
	dd->gpio_scl_num = _QIB_GPIO_SCL_NUM;
	dd->twsi_eeprom_dev = QIB_TWSI_EEPROM_DEV;

	dd->flags |= QIB_HAS_INTX | QIB_HAS_LINK_LATENCY |
		QIB_NODMA_RTAIL | QIB_HAS_VLSUPP | QIB_HAS_HDRSUPP |
		QIB_HAS_THRESH_UPDATE |
		(sdma_idle_cnt ? QIB_HAS_SDMA_TIMEOUT : 0);
	dd->flags |= qib_special_trigger ?
		QIB_USE_SPCL_TRIG : QIB_HAS_SEND_DMA;

	/*
	 * Setup initial values.  These may change when PAT is enabled, but
	 * we need these to करो initial chip रेजिस्टर accesses.
	 */
	qib_7322_set_baseaddrs(dd);

	mtu = ib_mtu_क्रमागत_to_पूर्णांक(qib_ibmtu);
	अगर (mtu == -1)
		mtu = QIB_DEFAULT_MTU;

	dd->cspec->पूर्णांक_enable_mask = QIB_I_BITSEXTANT;
	/* all hwerrors become पूर्णांकerrupts, unless special purposed */
	dd->cspec->hwerrmask = ~0ULL;
	/*  link_recovery setup causes these errors, so ignore them,
	 *  other than clearing them when they occur */
	dd->cspec->hwerrmask &=
		~(SYM_MASK(HwErrMask, IBSerdesPClkNotDetectMask_0) |
		  SYM_MASK(HwErrMask, IBSerdesPClkNotDetectMask_1) |
		  HWE_MASK(LATriggered));

	क्रम (pidx = 0; pidx < NUM_IB_PORTS; ++pidx) अणु
		काष्ठा qib_chippport_specअगरic *cp = ppd->cpspec;

		ppd->link_speed_supported = features & PORT_SPD_CAP;
		features >>=  PORT_SPD_CAP_SHIFT;
		अगर (!ppd->link_speed_supported) अणु
			/* single port mode (7340, or configured) */
			dd->skip_kctxt_mask |= 1 << pidx;
			अगर (pidx == 0) अणु
				/* Make sure port is disabled. */
				qib_ग_लिखो_kreg_port(ppd, krp_rcvctrl, 0);
				qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a, 0);
				ppd[0] = ppd[1];
				dd->cspec->hwerrmask &= ~(SYM_MASK(HwErrMask,
						  IBSerdesPClkNotDetectMask_0)
						  | SYM_MASK(HwErrMask,
						  SDmaMemReadErrMask_0));
				dd->cspec->पूर्णांक_enable_mask &= ~(
				     SYM_MASK(IntMask, SDmaCleanupDoneMask_0) |
				     SYM_MASK(IntMask, SDmaIdleIntMask_0) |
				     SYM_MASK(IntMask, SDmaProgressIntMask_0) |
				     SYM_MASK(IntMask, SDmaIntMask_0) |
				     SYM_MASK(IntMask, ErrIntMask_0) |
				     SYM_MASK(IntMask, SendDoneIntMask_0));
			पूर्ण अन्यथा अणु
				/* Make sure port is disabled. */
				qib_ग_लिखो_kreg_port(ppd, krp_rcvctrl, 0);
				qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a, 0);
				dd->cspec->hwerrmask &= ~(SYM_MASK(HwErrMask,
						  IBSerdesPClkNotDetectMask_1)
						  | SYM_MASK(HwErrMask,
						  SDmaMemReadErrMask_1));
				dd->cspec->पूर्णांक_enable_mask &= ~(
				     SYM_MASK(IntMask, SDmaCleanupDoneMask_1) |
				     SYM_MASK(IntMask, SDmaIdleIntMask_1) |
				     SYM_MASK(IntMask, SDmaProgressIntMask_1) |
				     SYM_MASK(IntMask, SDmaIntMask_1) |
				     SYM_MASK(IntMask, ErrIntMask_1) |
				     SYM_MASK(IntMask, SendDoneIntMask_1));
			पूर्ण
			जारी;
		पूर्ण

		dd->num_pports++;
		ret = qib_init_pportdata(ppd, dd, pidx, dd->num_pports);
		अगर (ret) अणु
			dd->num_pports--;
			जाओ bail;
		पूर्ण

		ppd->link_width_supported = IB_WIDTH_1X | IB_WIDTH_4X;
		ppd->link_width_enabled = IB_WIDTH_4X;
		ppd->link_speed_enabled = ppd->link_speed_supported;
		/*
		 * Set the initial values to reasonable शेष, will be set
		 * क्रम real when link is up.
		 */
		ppd->link_width_active = IB_WIDTH_4X;
		ppd->link_speed_active = QIB_IB_SDR;
		ppd->delay_mult = ib_rate_to_delay[IB_RATE_10_GBPS];
		चयन (qib_num_cfg_vls) अणु
		हाल 1:
			ppd->vls_supported = IB_VL_VL0;
			अवरोध;
		हाल 2:
			ppd->vls_supported = IB_VL_VL0_1;
			अवरोध;
		शेष:
			qib_devinfo(dd->pcidev,
				    "Invalid num_vls %u, using 4 VLs\n",
				    qib_num_cfg_vls);
			qib_num_cfg_vls = 4;
			fallthrough;
		हाल 4:
			ppd->vls_supported = IB_VL_VL0_3;
			अवरोध;
		हाल 8:
			अगर (mtu <= 2048)
				ppd->vls_supported = IB_VL_VL0_7;
			अन्यथा अणु
				qib_devinfo(dd->pcidev,
					    "Invalid num_vls %u for MTU %d , using 4 VLs\n",
					    qib_num_cfg_vls, mtu);
				ppd->vls_supported = IB_VL_VL0_3;
				qib_num_cfg_vls = 4;
			पूर्ण
			अवरोध;
		पूर्ण
		ppd->vls_operational = ppd->vls_supported;

		init_रुकोqueue_head(&cp->स्वतःneg_रुको);
		INIT_DELAYED_WORK(&cp->स्वतःneg_work,
				  स्वतःneg_7322_work);
		अगर (ppd->dd->cspec->r1)
			INIT_DELAYED_WORK(&cp->ipg_work, ipg_7322_work);

		/*
		 * For Mez and similar cards, no qsfp info, so करो
		 * the "cable info" setup here.  Can be overridden
		 * in adapter-specअगरic routines.
		 */
		अगर (!(dd->flags & QIB_HAS_QSFP)) अणु
			अगर (!IS_QMH(dd) && !IS_QME(dd))
				qib_devinfo(dd->pcidev,
					"IB%u:%u: Unknown mezzanine card type\n",
					dd->unit, ppd->port);
			cp->h1_val = IS_QMH(dd) ? H1_FORCE_QMH : H1_FORCE_QME;
			/*
			 * Choose center value as शेष tx serdes setting
			 * until changed through module parameter.
			 */
			ppd->cpspec->no_eep = IS_QMH(dd) ?
				TXDDS_TABLE_SZ + 2 : TXDDS_TABLE_SZ + 4;
		पूर्ण अन्यथा
			cp->h1_val = H1_FORCE_VAL;

		/* Aव्योम ग_लिखोs to chip क्रम mini_init */
		अगर (!qib_mini_init)
			ग_लिखो_7322_init_portregs(ppd);

		समयr_setup(&cp->chase_समयr, reenable_chase, 0);

		ppd++;
	पूर्ण

	dd->rcvhdrentsize = qib_rcvhdrentsize ?
		qib_rcvhdrentsize : QIB_RCVHDR_ENTSIZE;
	dd->rcvhdrsize = qib_rcvhdrsize ?
		qib_rcvhdrsize : QIB_DFLT_RCVHDRSIZE;
	dd->rhf_offset = dd->rcvhdrentsize - माप(u64) / माप(u32);

	/* we always allocate at least 2048 bytes क्रम eager buffers */
	dd->rcvegrbufsize = max(mtu, 2048);
	dd->rcvegrbufsize_shअगरt = ilog2(dd->rcvegrbufsize);

	qib_7322_tidढाँचा(dd);

	/*
	 * We can request a receive पूर्णांकerrupt क्रम 1 or
	 * more packets from current offset.
	 */
	dd->rhdrhead_पूर्णांकr_off =
		(u64) rcv_पूर्णांक_count << IBA7322_HDRHEAD_PKTINT_SHIFT;

	/* setup the stats समयr; the add_समयr is करोne at end of init */
	समयr_setup(&dd->stats_समयr, qib_get_7322_faststats, 0);

	dd->ureg_align = 0x10000;  /* 64KB alignment */

	dd->piosize2kmax_dwords = dd->piosize2k >> 2;

	qib_7322_config_ctxts(dd);
	qib_set_ctxtcnt(dd);

	/*
	 * We करो not set WC on the VL15 buffers to aव्योम
	 * a rare problem with unaligned ग_लिखोs from
	 * पूर्णांकerrupt-flushed store buffers, so we need
	 * to map those separately here.  We can't solve
	 * this क्रम the rarely used mtrr हाल.
	 */
	ret = init_chip_wc_pat(dd, 0);
	अगर (ret)
		जाओ bail;

	/* vl15 buffers start just after the 4k buffers */
	vl15off = dd->physaddr + (dd->piobufbase >> 32) +
		  dd->piobcnt4k * dd->align4k;
	dd->piovl15base	= ioremap(vl15off,
					  NUM_VL15_BUFS * dd->align4k);
	अगर (!dd->piovl15base) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	qib_7322_set_baseaddrs(dd); /* set chip access poपूर्णांकers now */

	ret = 0;
	अगर (qib_mini_init)
		जाओ bail;
	अगर (!dd->num_pports) अणु
		qib_dev_err(dd, "No ports enabled, giving up initialization\n");
		जाओ bail; /* no error, so can still figure out why err */
	पूर्ण

	ग_लिखो_7322_initregs(dd);
	ret = qib_create_ctxts(dd);
	init_7322_cntrnames(dd);

	updthresh = 8U; /* update threshold */

	/* use all of 4KB buffers क्रम the kernel SDMA, zero अगर !SDMA.
	 * reserve the update threshold amount क्रम other kernel use, such
	 * as sending SMI, MAD, and ACKs, or 3, whichever is greater,
	 * unless we aren't enabling SDMA, in which हाल we want to use
	 * all the 4k bufs क्रम the kernel.
	 * अगर this was less than the update threshold, we could रुको
	 * a दीर्घ समय क्रम an update.  Coded this way because we
	 * someबार change the update threshold क्रम various reasons,
	 * and we want this to reमुख्य robust.
	 */
	अगर (dd->flags & QIB_HAS_SEND_DMA) अणु
		dd->cspec->sdmabufcnt = dd->piobcnt4k;
		sbufs = updthresh > 3 ? updthresh : 3;
	पूर्ण अन्यथा अणु
		dd->cspec->sdmabufcnt = 0;
		sbufs = dd->piobcnt4k;
	पूर्ण
	dd->cspec->lastbuf_क्रम_pio = dd->piobcnt2k + dd->piobcnt4k -
		dd->cspec->sdmabufcnt;
	dd->lastctxt_piobuf = dd->cspec->lastbuf_क्रम_pio - sbufs;
	dd->cspec->lastbuf_क्रम_pio--; /* range is <= , not < */
	dd->last_pio = dd->cspec->lastbuf_क्रम_pio;
	dd->pbufsctxt = (dd->cfgctxts > dd->first_user_ctxt) ?
		dd->lastctxt_piobuf / (dd->cfgctxts - dd->first_user_ctxt) : 0;

	/*
	 * If we have 16 user contexts, we will have 7 sbufs
	 * per context, so reduce the update threshold to match.  We
	 * want to update beक्रमe we actually run out, at low pbufs/ctxt
	 * so give ourselves some margin.
	 */
	अगर (dd->pbufsctxt >= 2 && dd->pbufsctxt - 2 < updthresh)
		updthresh = dd->pbufsctxt - 2;
	dd->cspec->updthresh_dflt = updthresh;
	dd->cspec->updthresh = updthresh;

	/* beक्रमe full enable, no पूर्णांकerrupts, no locking needed */
	dd->sendctrl |= ((updthresh & SYM_RMASK(SendCtrl, AvailUpdThld))
			     << SYM_LSB(SendCtrl, AvailUpdThld)) |
			SYM_MASK(SendCtrl, SendBufAvailPad64Byte);

	dd->psxmitरुको_supported = 1;
	dd->psxmitरुको_check_rate = QIB_7322_PSXMITWAIT_CHECK_RATE;
bail:
	अगर (!dd->ctxtcnt)
		dd->ctxtcnt = 1; /* क्रम other initialization code */

	वापस ret;
पूर्ण

अटल u32 __iomem *qib_7322_माला_लोendbuf(काष्ठा qib_pportdata *ppd, u64 pbc,
					u32 *pbufnum)
अणु
	u32 first, last, plen = pbc & QIB_PBC_LENGTH_MASK;
	काष्ठा qib_devdata *dd = ppd->dd;

	/* last is same क्रम 2k and 4k, because we use 4k अगर all 2k busy */
	अगर (pbc & PBC_7322_VL15_SEND) अणु
		first = dd->piobcnt2k + dd->piobcnt4k + ppd->hw_pidx;
		last = first;
	पूर्ण अन्यथा अणु
		अगर ((plen + 1) > dd->piosize2kmax_dwords)
			first = dd->piobcnt2k;
		अन्यथा
			first = 0;
		last = dd->cspec->lastbuf_क्रम_pio;
	पूर्ण
	वापस qib_माला_लोendbuf_range(dd, pbufnum, first, last);
पूर्ण

अटल व्योम qib_set_cntr_7322_sample(काष्ठा qib_pportdata *ppd, u32 पूर्णांकv,
				     u32 start)
अणु
	qib_ग_लिखो_kreg_port(ppd, krp_psपूर्णांकerval, पूर्णांकv);
	qib_ग_लिखो_kreg_port(ppd, krp_psstart, start);
पूर्ण

/*
 * Must be called with sdma_lock held, or beक्रमe init finished.
 */
अटल व्योम qib_sdma_set_7322_desc_cnt(काष्ठा qib_pportdata *ppd, अचिन्हित cnt)
अणु
	qib_ग_लिखो_kreg_port(ppd, krp_senddmadesccnt, cnt);
पूर्ण

/*
 * sdma_lock should be acquired beक्रमe calling this routine
 */
अटल व्योम dump_sdma_7322_state(काष्ठा qib_pportdata *ppd)
अणु
	u64 reg, reg1, reg2;

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmastatus);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmastatus: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_sendctrl);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA sendctrl: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmabase);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmabase: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmabufmask0);
	reg1 = qib_पढ़ो_kreg_port(ppd, krp_senddmabufmask1);
	reg2 = qib_पढ़ो_kreg_port(ppd, krp_senddmabufmask2);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmabufmask 0:%llx  1:%llx  2:%llx\n",
		 reg, reg1, reg2);

	/* get bufuse bits, clear them, and prपूर्णांक them again अगर non-zero */
	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmabuf_use0);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabuf_use0, reg);
	reg1 = qib_पढ़ो_kreg_port(ppd, krp_senddmabuf_use1);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabuf_use0, reg1);
	reg2 = qib_पढ़ो_kreg_port(ppd, krp_senddmabuf_use2);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabuf_use0, reg2);
	/* 0 and 1 should always be zero, so prपूर्णांक as लघु क्रमm */
	qib_dev_porterr(ppd->dd, ppd->port,
		 "SDMA current senddmabuf_use 0:%llx  1:%llx  2:%llx\n",
		 reg, reg1, reg2);
	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmabuf_use0);
	reg1 = qib_पढ़ो_kreg_port(ppd, krp_senddmabuf_use1);
	reg2 = qib_पढ़ो_kreg_port(ppd, krp_senddmabuf_use2);
	/* 0 and 1 should always be zero, so prपूर्णांक as लघु क्रमm */
	qib_dev_porterr(ppd->dd, ppd->port,
		 "SDMA cleared senddmabuf_use 0:%llx  1:%llx  2:%llx\n",
		 reg, reg1, reg2);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmatail);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmatail: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmahead);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmahead: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmaheadaddr);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmaheadaddr: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmalengen);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmalengen: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmadesccnt);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmadesccnt: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmaidlecnt);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmaidlecnt: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmaprioritythld);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmapriorityhld: 0x%016llx\n", reg);

	reg = qib_पढ़ो_kreg_port(ppd, krp_senddmareloadcnt);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA senddmareloadcnt: 0x%016llx\n", reg);

	dump_sdma_state(ppd);
पूर्ण

अटल काष्ठा sdma_set_state_action sdma_7322_action_table[] = अणु
	[qib_sdma_state_s00_hw_करोwn] = अणु
		.go_s99_running_tofalse = 1,
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 0,
		.op_drain = 0,
	पूर्ण,
	[qib_sdma_state_s10_hw_start_up_रुको] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
		.op_drain = 0,
	पूर्ण,
	[qib_sdma_state_s20_idle] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
		.op_drain = 0,
	पूर्ण,
	[qib_sdma_state_s30_sw_clean_up_रुको] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
		.op_drain = 0,
	पूर्ण,
	[qib_sdma_state_s40_hw_clean_up_रुको] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
		.op_drain = 0,
	पूर्ण,
	[qib_sdma_state_s50_hw_halt_रुको] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
		.op_drain = 1,
	पूर्ण,
	[qib_sdma_state_s99_running] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 0,
		.op_drain = 0,
		.go_s99_running_totrue = 1,
	पूर्ण,
पूर्ण;

अटल व्योम qib_7322_sdma_init_early(काष्ठा qib_pportdata *ppd)
अणु
	ppd->sdma_state.set_state_action = sdma_7322_action_table;
पूर्ण

अटल पूर्णांक init_sdma_7322_regs(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित lastbuf, erstbuf;
	u64 senddmabufmask[3] = अणु 0 पूर्ण;
	पूर्णांक n;

	qib_ग_लिखो_kreg_port(ppd, krp_senddmabase, ppd->sdma_descq_phys);
	qib_sdma_7322_setlengen(ppd);
	qib_sdma_update_7322_tail(ppd, 0); /* Set SendDmaTail */
	qib_ग_लिखो_kreg_port(ppd, krp_senddmareloadcnt, sdma_idle_cnt);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmadesccnt, 0);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmaheadaddr, ppd->sdma_head_phys);

	अगर (dd->num_pports)
		n = dd->cspec->sdmabufcnt / dd->num_pports; /* no reमुख्यder */
	अन्यथा
		n = dd->cspec->sdmabufcnt; /* failsafe क्रम init */
	erstbuf = (dd->piobcnt2k + dd->piobcnt4k) -
		((dd->num_pports == 1 || ppd->port == 2) ? n :
		dd->cspec->sdmabufcnt);
	lastbuf = erstbuf + n;

	ppd->sdma_state.first_sendbuf = erstbuf;
	ppd->sdma_state.last_sendbuf = lastbuf;
	क्रम (; erstbuf < lastbuf; ++erstbuf) अणु
		अचिन्हित word = erstbuf / BITS_PER_LONG;
		अचिन्हित bit = erstbuf & (BITS_PER_LONG - 1);

		senddmabufmask[word] |= 1ULL << bit;
	पूर्ण
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabufmask0, senddmabufmask[0]);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabufmask1, senddmabufmask[1]);
	qib_ग_लिखो_kreg_port(ppd, krp_senddmabufmask2, senddmabufmask[2]);
	वापस 0;
पूर्ण

/* sdma_lock must be held */
अटल u16 qib_sdma_7322_gethead(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक sane;
	पूर्णांक use_dmahead;
	u16 swhead;
	u16 swtail;
	u16 cnt;
	u16 hwhead;

	use_dmahead = __qib_sdma_running(ppd) &&
		(dd->flags & QIB_HAS_SDMA_TIMEOUT);
retry:
	hwhead = use_dmahead ?
		(u16) le64_to_cpu(*ppd->sdma_head_dma) :
		(u16) qib_पढ़ो_kreg_port(ppd, krp_senddmahead);

	swhead = ppd->sdma_descq_head;
	swtail = ppd->sdma_descq_tail;
	cnt = ppd->sdma_descq_cnt;

	अगर (swhead < swtail)
		/* not wrapped */
		sane = (hwhead >= swhead) & (hwhead <= swtail);
	अन्यथा अगर (swhead > swtail)
		/* wrapped around */
		sane = ((hwhead >= swhead) && (hwhead < cnt)) ||
			(hwhead <= swtail);
	अन्यथा
		/* empty */
		sane = (hwhead == swhead);

	अगर (unlikely(!sane)) अणु
		अगर (use_dmahead) अणु
			/* try one more समय, directly from the रेजिस्टर */
			use_dmahead = 0;
			जाओ retry;
		पूर्ण
		/* proceed as अगर no progress */
		hwhead = swhead;
	पूर्ण

	वापस hwhead;
पूर्ण

अटल पूर्णांक qib_sdma_7322_busy(काष्ठा qib_pportdata *ppd)
अणु
	u64 hwstatus = qib_पढ़ो_kreg_port(ppd, krp_senddmastatus);

	वापस (hwstatus & SYM_MASK(SendDmaStatus_0, ScoreBoardDrainInProg)) ||
	       (hwstatus & SYM_MASK(SendDmaStatus_0, HaltInProg)) ||
	       !(hwstatus & SYM_MASK(SendDmaStatus_0, InternalSDmaHalt)) ||
	       !(hwstatus & SYM_MASK(SendDmaStatus_0, ScbEmpty));
पूर्ण

/*
 * Compute the amount of delay beक्रमe sending the next packet अगर the
 * port's send rate dअगरfers from the अटल rate set क्रम the QP.
 * The delay affects the next packet and the amount of the delay is
 * based on the length of the this packet.
 */
अटल u32 qib_7322_setpbc_control(काष्ठा qib_pportdata *ppd, u32 plen,
				   u8 srate, u8 vl)
अणु
	u8 snd_mult = ppd->delay_mult;
	u8 rcv_mult = ib_rate_to_delay[srate];
	u32 ret;

	ret = rcv_mult > snd_mult ? ((plen + 1) >> 1) * snd_mult : 0;

	/* Indicate VL15, अन्यथा set the VL in the control word */
	अगर (vl == 15)
		ret |= PBC_7322_VL15_SEND_CTRL;
	अन्यथा
		ret |= vl << PBC_VL_NUM_LSB;
	ret |= ((u32)(ppd->hw_pidx)) << PBC_PORT_SEL_LSB;

	वापस ret;
पूर्ण

/*
 * Enable the per-port VL15 send buffers क्रम use.
 * They follow the rest of the buffers, without a config parameter.
 * This was in initregs, but that is करोne beक्रमe the shaकरोw
 * is set up, and this has to be करोne after the shaकरोw is
 * set up.
 */
अटल व्योम qib_7322_initvl15_bufs(काष्ठा qib_devdata *dd)
अणु
	अचिन्हित vl15bufs;

	vl15bufs = dd->piobcnt2k + dd->piobcnt4k;
	qib_chg_pioavailkernel(dd, vl15bufs, NUM_VL15_BUFS,
			       TXCHK_CHG_TYPE_KERN, शून्य);
पूर्ण

अटल व्योम qib_7322_init_ctxt(काष्ठा qib_ctxtdata *rcd)
अणु
	अगर (rcd->ctxt < NUM_IB_PORTS) अणु
		अगर (rcd->dd->num_pports > 1) अणु
			rcd->rcvegrcnt = KCTXT0_EGRCNT / 2;
			rcd->rcvegr_tid_base = rcd->ctxt ? rcd->rcvegrcnt : 0;
		पूर्ण अन्यथा अणु
			rcd->rcvegrcnt = KCTXT0_EGRCNT;
			rcd->rcvegr_tid_base = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		rcd->rcvegrcnt = rcd->dd->cspec->rcvegrcnt;
		rcd->rcvegr_tid_base = KCTXT0_EGRCNT +
			(rcd->ctxt - NUM_IB_PORTS) * rcd->rcvegrcnt;
	पूर्ण
पूर्ण

#घोषणा QTXSLEEPS 5000
अटल व्योम qib_7322_txchk_change(काष्ठा qib_devdata *dd, u32 start,
				  u32 len, u32 which, काष्ठा qib_ctxtdata *rcd)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक last = start + len - 1;
	स्थिर पूर्णांक lastr = last / BITS_PER_LONG;
	u32 sleeps = 0;
	पूर्णांक रुको = rcd != शून्य;
	अचिन्हित दीर्घ flags;

	जबतक (रुको) अणु
		अचिन्हित दीर्घ shaकरोw = 0;
		पूर्णांक cstart, previ = -1;

		/*
		 * when flipping from kernel to user, we can't change
		 * the checking type अगर the buffer is allocated to the
		 * driver.   It's OK the other direction, because it's
		 * from बंद, and we have just disarm'ed all the
		 * buffers.  All the kernel to kernel changes are also
		 * OK.
		 */
		क्रम (cstart = start; cstart <= last; cstart++) अणु
			i = ((2 * cstart) + QLOGIC_IB_SENDPIOAVAIL_BUSY_SHIFT)
				/ BITS_PER_LONG;
			अगर (i != previ) अणु
				shaकरोw = (अचिन्हित दीर्घ)
					le64_to_cpu(dd->pioavailregs_dma[i]);
				previ = i;
			पूर्ण
			अगर (test_bit(((2 * cstart) +
				      QLOGIC_IB_SENDPIOAVAIL_BUSY_SHIFT)
				     % BITS_PER_LONG, &shaकरोw))
				अवरोध;
		पूर्ण

		अगर (cstart > last)
			अवरोध;

		अगर (sleeps == QTXSLEEPS)
			अवरोध;
		/* make sure we see an updated copy next समय around */
		sendctrl_7322_mod(dd->pport, QIB_SENDCTRL_AVAIL_BLIP);
		sleeps++;
		msleep(20);
	पूर्ण

	चयन (which) अणु
	हाल TXCHK_CHG_TYPE_DIS1:
		/*
		 * disable checking on a range; used by diags; just
		 * one buffer, but still written generically
		 */
		क्रम (i = start; i <= last; i++)
			clear_bit(i, dd->cspec->sendchkenable);
		अवरोध;

	हाल TXCHK_CHG_TYPE_ENAB1:
		/*
		 * (re)enable checking on a range; used by diags; just
		 * one buffer, but still written generically; पढ़ो
		 * scratch to be sure buffer actually triggered, not
		 * just flushed from processor.
		 */
		qib_पढ़ो_kreg32(dd, kr_scratch);
		क्रम (i = start; i <= last; i++)
			set_bit(i, dd->cspec->sendchkenable);
		अवरोध;

	हाल TXCHK_CHG_TYPE_KERN:
		/* usable by kernel */
		क्रम (i = start; i <= last; i++) अणु
			set_bit(i, dd->cspec->sendibchk);
			clear_bit(i, dd->cspec->sendgrhchk);
		पूर्ण
		spin_lock_irqsave(&dd->uctxt_lock, flags);
		/* see अगर we need to उठाओ avail update threshold */
		क्रम (i = dd->first_user_ctxt;
		     dd->cspec->updthresh != dd->cspec->updthresh_dflt
		     && i < dd->cfgctxts; i++)
			अगर (dd->rcd[i] && dd->rcd[i]->subctxt_cnt &&
			   ((dd->rcd[i]->piocnt / dd->rcd[i]->subctxt_cnt) - 1)
			   < dd->cspec->updthresh_dflt)
				अवरोध;
		spin_unlock_irqrestore(&dd->uctxt_lock, flags);
		अगर (i == dd->cfgctxts) अणु
			spin_lock_irqsave(&dd->sendctrl_lock, flags);
			dd->cspec->updthresh = dd->cspec->updthresh_dflt;
			dd->sendctrl &= ~SYM_MASK(SendCtrl, AvailUpdThld);
			dd->sendctrl |= (dd->cspec->updthresh &
					 SYM_RMASK(SendCtrl, AvailUpdThld)) <<
					   SYM_LSB(SendCtrl, AvailUpdThld);
			spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
			sendctrl_7322_mod(dd->pport, QIB_SENDCTRL_AVAIL_BLIP);
		पूर्ण
		अवरोध;

	हाल TXCHK_CHG_TYPE_USER:
		/* क्रम user process */
		क्रम (i = start; i <= last; i++) अणु
			clear_bit(i, dd->cspec->sendibchk);
			set_bit(i, dd->cspec->sendgrhchk);
		पूर्ण
		spin_lock_irqsave(&dd->sendctrl_lock, flags);
		अगर (rcd && rcd->subctxt_cnt && ((rcd->piocnt
			/ rcd->subctxt_cnt) - 1) < dd->cspec->updthresh) अणु
			dd->cspec->updthresh = (rcd->piocnt /
						rcd->subctxt_cnt) - 1;
			dd->sendctrl &= ~SYM_MASK(SendCtrl, AvailUpdThld);
			dd->sendctrl |= (dd->cspec->updthresh &
					SYM_RMASK(SendCtrl, AvailUpdThld))
					<< SYM_LSB(SendCtrl, AvailUpdThld);
			spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
			sendctrl_7322_mod(dd->pport, QIB_SENDCTRL_AVAIL_BLIP);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = start / BITS_PER_LONG; which >= 2 && i <= lastr; ++i)
		qib_ग_लिखो_kreg(dd, kr_sendcheckmask + i,
			       dd->cspec->sendchkenable[i]);

	क्रम (i = start / BITS_PER_LONG; which < 2 && i <= lastr; ++i) अणु
		qib_ग_लिखो_kreg(dd, kr_sendgrhcheckmask + i,
			       dd->cspec->sendgrhchk[i]);
		qib_ग_लिखो_kreg(dd, kr_sendibpkपंचांगask + i,
			       dd->cspec->sendibchk[i]);
	पूर्ण

	/*
	 * Be sure whatever we did was seen by the chip and acted upon,
	 * beक्रमe we वापस.  Mostly important क्रम which >= 2.
	 */
	qib_पढ़ो_kreg32(dd, kr_scratch);
पूर्ण


/* useful क्रम trigger analyzers, etc. */
अटल व्योम ग_लिखोscratch(काष्ठा qib_devdata *dd, u32 val)
अणु
	qib_ग_लिखो_kreg(dd, kr_scratch, val);
पूर्ण

/* Dummy क्रम now, use chip regs soon */
अटल पूर्णांक qib_7322_tempsense_rd(काष्ठा qib_devdata *dd, पूर्णांक regnum)
अणु
	वापस -ENXIO;
पूर्ण

/**
 * qib_init_iba7322_funcs - set up the chip-specअगरic function poपूर्णांकers
 * @pdev: the pci_dev क्रम qlogic_ib device
 * @ent: pci_device_id काष्ठा क्रम this dev
 *
 * Also allocates, inits, and वापसs the devdata काष्ठा क्रम this
 * device instance
 *
 * This is global, and is called directly at init to set up the
 * chip-specअगरic function poपूर्णांकers क्रम later use.
 */
काष्ठा qib_devdata *qib_init_iba7322_funcs(काष्ठा pci_dev *pdev,
					   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा qib_devdata *dd;
	पूर्णांक ret, i;
	u32 tअसलize, actual_cnt = 0;

	dd = qib_alloc_devdata(pdev,
		NUM_IB_PORTS * माप(काष्ठा qib_pportdata) +
		माप(काष्ठा qib_chip_specअगरic) +
		NUM_IB_PORTS * माप(काष्ठा qib_chippport_specअगरic));
	अगर (IS_ERR(dd))
		जाओ bail;

	dd->f_bringup_serdes    = qib_7322_bringup_serdes;
	dd->f_cleanup           = qib_setup_7322_cleanup;
	dd->f_clear_tids        = qib_7322_clear_tids;
	dd->f_मुक्त_irq          = qib_7322_मुक्त_irq;
	dd->f_get_base_info     = qib_7322_get_base_info;
	dd->f_get_msgheader     = qib_7322_get_msgheader;
	dd->f_माला_लोendbuf        = qib_7322_माला_लोendbuf;
	dd->f_gpio_mod          = gpio_7322_mod;
	dd->f_eeprom_wen        = qib_7322_eeprom_wen;
	dd->f_hdrqempty         = qib_7322_hdrqempty;
	dd->f_ib_upकरोwn         = qib_7322_ib_upकरोwn;
	dd->f_init_ctxt         = qib_7322_init_ctxt;
	dd->f_initvl15_bufs     = qib_7322_initvl15_bufs;
	dd->f_पूर्णांकr_fallback     = qib_7322_पूर्णांकr_fallback;
	dd->f_late_initreg      = qib_late_7322_initreg;
	dd->f_setpbc_control    = qib_7322_setpbc_control;
	dd->f_portcntr          = qib_portcntr_7322;
	dd->f_put_tid           = qib_7322_put_tid;
	dd->f_quiet_serdes      = qib_7322_mini_quiet_serdes;
	dd->f_rcvctrl           = rcvctrl_7322_mod;
	dd->f_पढ़ो_cntrs        = qib_पढ़ो_7322cntrs;
	dd->f_पढ़ो_portcntrs    = qib_पढ़ो_7322portcntrs;
	dd->f_reset             = qib_करो_7322_reset;
	dd->f_init_sdma_regs    = init_sdma_7322_regs;
	dd->f_sdma_busy         = qib_sdma_7322_busy;
	dd->f_sdma_gethead      = qib_sdma_7322_gethead;
	dd->f_sdma_sendctrl     = qib_7322_sdma_sendctrl;
	dd->f_sdma_set_desc_cnt = qib_sdma_set_7322_desc_cnt;
	dd->f_sdma_update_tail  = qib_sdma_update_7322_tail;
	dd->f_sendctrl          = sendctrl_7322_mod;
	dd->f_set_armlaunch     = qib_set_7322_armlaunch;
	dd->f_set_cntr_sample   = qib_set_cntr_7322_sample;
	dd->f_iblink_state      = qib_7322_iblink_state;
	dd->f_ibphys_portstate  = qib_7322_phys_portstate;
	dd->f_get_ib_cfg        = qib_7322_get_ib_cfg;
	dd->f_set_ib_cfg        = qib_7322_set_ib_cfg;
	dd->f_set_ib_loopback   = qib_7322_set_loopback;
	dd->f_get_ib_table      = qib_7322_get_ib_table;
	dd->f_set_ib_table      = qib_7322_set_ib_table;
	dd->f_set_पूर्णांकr_state    = qib_7322_set_पूर्णांकr_state;
	dd->f_setextled         = qib_setup_7322_setextled;
	dd->f_txchk_change      = qib_7322_txchk_change;
	dd->f_update_usrhead    = qib_update_7322_usrhead;
	dd->f_wantpiobuf_पूर्णांकr   = qib_wantpiobuf_7322_पूर्णांकr;
	dd->f_xgxs_reset        = qib_7322_mini_pcs_reset;
	dd->f_sdma_hw_clean_up  = qib_7322_sdma_hw_clean_up;
	dd->f_sdma_hw_start_up  = qib_7322_sdma_hw_start_up;
	dd->f_sdma_init_early   = qib_7322_sdma_init_early;
	dd->f_ग_लिखोscratch      = ग_लिखोscratch;
	dd->f_tempsense_rd	= qib_7322_tempsense_rd;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	dd->f_notअगरy_dca	= qib_7322_notअगरy_dca;
#पूर्ण_अगर
	/*
	 * Do reमुख्यing PCIe setup and save PCIe values in dd.
	 * Any error prपूर्णांकing is alपढ़ोy करोne by the init code.
	 * On वापस, we have the chip mapped, but chip रेजिस्टरs
	 * are not set up until start of qib_init_7322_variables.
	 */
	ret = qib_pcie_ddinit(dd, pdev, ent);
	अगर (ret < 0)
		जाओ bail_मुक्त;

	/* initialize chip-specअगरic variables */
	ret = qib_init_7322_variables(dd);
	अगर (ret)
		जाओ bail_cleanup;

	अगर (qib_mini_init || !dd->num_pports)
		जाओ bail;

	/*
	 * Determine number of vectors we want; depends on port count
	 * and number of configured kernel receive queues actually used.
	 * Should also depend on whether sdma is enabled or not, but
	 * that's such a rare testing case it's not worth worrying about.
	 */
	tअसलize = dd->first_user_ctxt + ARRAY_SIZE(irq_table);
	क्रम (i = 0; i < tअसलize; i++)
		अगर ((i < ARRAY_SIZE(irq_table) &&
		     irq_table[i].port <= dd->num_pports) ||
		    (i >= ARRAY_SIZE(irq_table) &&
		     dd->rcd[i - ARRAY_SIZE(irq_table)]))
			actual_cnt++;
	/* reduce by ctxt's < 2 */
	अगर (qib_krcvq01_no_msi)
		actual_cnt -= dd->num_pports;

	tअसलize = actual_cnt;
	dd->cspec->msix_entries = kसुस्मृति(tअसलize,
					  माप(काष्ठा qib_msix_entry),
					  GFP_KERNEL);
	अगर (!dd->cspec->msix_entries)
		tअसलize = 0;

	अगर (qib_pcie_params(dd, 8, &tअसलize))
		qib_dev_err(dd,
			"Failed to setup PCIe or interrupts; continuing anyway\n");
	/* may be less than we wanted, अगर not enough available */
	dd->cspec->num_msix_entries = tअसलize;

	/* setup पूर्णांकerrupt handler */
	qib_setup_7322_पूर्णांकerrupt(dd, 1);

	/* clear diagctrl रेजिस्टर, in हाल diags were running and crashed */
	qib_ग_लिखो_kreg(dd, kr_hwdiagctrl, 0);
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	अगर (!dca_add_requester(&pdev->dev)) अणु
		qib_devinfo(dd->pcidev, "DCA enabled\n");
		dd->flags |= QIB_DCA_ENABLED;
		qib_setup_dca(dd);
	पूर्ण
#पूर्ण_अगर
	जाओ bail;

bail_cleanup:
	qib_pcie_ddcleanup(dd);
bail_मुक्त:
	qib_मुक्त_devdata(dd);
	dd = ERR_PTR(ret);
bail:
	वापस dd;
पूर्ण

/*
 * Set the table entry at the specअगरied index from the table specअगरed.
 * There are 3 * TXDDS_TABLE_SZ entries in all per port, with the first
 * TXDDS_TABLE_SZ क्रम SDR, the next क्रम DDR, and the last क्रम QDR.
 * 'idx' below addresses the correct entry, जबतक its 4 LSBs select the
 * corresponding entry (one of TXDDS_TABLE_SZ) from the selected table.
 */
#घोषणा DDS_ENT_AMP_LSB 14
#घोषणा DDS_ENT_MAIN_LSB 9
#घोषणा DDS_ENT_POST_LSB 5
#घोषणा DDS_ENT_PRE_XTRA_LSB 3
#घोषणा DDS_ENT_PRE_LSB 0

/*
 * Set one entry in the TxDDS table क्रम spec'd port
 * ridx picks one of the entries, जबतक tp poपूर्णांकs
 * to the appropriate table entry.
 */
अटल व्योम set_txdds(काष्ठा qib_pportdata *ppd, पूर्णांक ridx,
		      स्थिर काष्ठा txdds_ent *tp)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u32 pack_ent;
	पूर्णांक regidx;

	/* Get correct offset in chip-space, and in source table */
	regidx = KREG_IBPORT_IDX(IBSD_DDS_MAP_TABLE) + ridx;
	/*
	 * We करो not use qib_ग_लिखो_kreg_port() because it was पूर्णांकended
	 * only क्रम रेजिस्टरs in the lower "port specific" pages.
	 * So करो index calculation  by hand.
	 */
	अगर (ppd->hw_pidx)
		regidx += (dd->palign / माप(u64));

	pack_ent = tp->amp << DDS_ENT_AMP_LSB;
	pack_ent |= tp->मुख्य << DDS_ENT_MAIN_LSB;
	pack_ent |= tp->pre << DDS_ENT_PRE_LSB;
	pack_ent |= tp->post << DDS_ENT_POST_LSB;
	qib_ग_लिखो_kreg(dd, regidx, pack_ent);
	/* Prevent back-to-back ग_लिखोs by hitting scratch */
	qib_ग_लिखो_kreg(ppd->dd, kr_scratch, 0);
पूर्ण

अटल स्थिर काष्ठा venकरोr_txdds_ent venकरोr_txdds[] = अणु
	अणु /* Amphenol 1m 30awg NoEq */
		अणु 0x41, 0x50, 0x48 पूर्ण, "584470002       ",
		अणु 10,  0,  0,  5 पूर्ण, अणु 10,  0,  0,  9 पूर्ण, अणु  7,  1,  0, 13 पूर्ण,
	पूर्ण,
	अणु /* Amphenol 3m 28awg NoEq */
		अणु 0x41, 0x50, 0x48 पूर्ण, "584470004       ",
		अणु  0,  0,  0,  8 पूर्ण, अणु  0,  0,  0, 11 पूर्ण, अणु  0,  1,  7, 15 पूर्ण,
	पूर्ण,
	अणु /* Finisar 3m OM2 Optical */
		अणु 0x00, 0x90, 0x65 पूर्ण, "FCBG410QB1C03-QL",
		अणु  0,  0,  0,  3 पूर्ण, अणु  0,  0,  0,  4 पूर्ण, अणु  0,  0,  0, 13 पूर्ण,
	पूर्ण,
	अणु /* Finisar 30m OM2 Optical */
		अणु 0x00, 0x90, 0x65 पूर्ण, "FCBG410QB1C30-QL",
		अणु  0,  0,  0,  1 पूर्ण, अणु  0,  0,  0,  5 पूर्ण, अणु  0,  0,  0, 11 पूर्ण,
	पूर्ण,
	अणु /* Finisar Default OM2 Optical */
		अणु 0x00, 0x90, 0x65 पूर्ण, शून्य,
		अणु  0,  0,  0,  2 पूर्ण, अणु  0,  0,  0,  5 पूर्ण, अणु  0,  0,  0, 12 पूर्ण,
	पूर्ण,
	अणु /* Gore 1m 30awg NoEq */
		अणु 0x00, 0x21, 0x77 पूर्ण, "QSN3300-1       ",
		अणु  0,  0,  0,  6 पूर्ण, अणु  0,  0,  0,  9 पूर्ण, अणु  0,  1,  0, 15 पूर्ण,
	पूर्ण,
	अणु /* Gore 2m 30awg NoEq */
		अणु 0x00, 0x21, 0x77 पूर्ण, "QSN3300-2       ",
		अणु  0,  0,  0,  8 पूर्ण, अणु  0,  0,  0, 10 पूर्ण, अणु  0,  1,  7, 15 पूर्ण,
	पूर्ण,
	अणु /* Gore 1m 28awg NoEq */
		अणु 0x00, 0x21, 0x77 पूर्ण, "QSN3800-1       ",
		अणु  0,  0,  0,  6 पूर्ण, अणु  0,  0,  0,  8 पूर्ण, अणु  0,  1,  0, 15 पूर्ण,
	पूर्ण,
	अणु /* Gore 3m 28awg NoEq */
		अणु 0x00, 0x21, 0x77 पूर्ण, "QSN3800-3       ",
		अणु  0,  0,  0,  9 पूर्ण, अणु  0,  0,  0, 13 पूर्ण, अणु  0,  1,  7, 15 पूर्ण,
	पूर्ण,
	अणु /* Gore 5m 24awg Eq */
		अणु 0x00, 0x21, 0x77 पूर्ण, "QSN7000-5       ",
		अणु  0,  0,  0,  7 पूर्ण, अणु  0,  0,  0,  9 पूर्ण, अणु  0,  1,  3, 15 पूर्ण,
	पूर्ण,
	अणु /* Gore 7m 24awg Eq */
		अणु 0x00, 0x21, 0x77 पूर्ण, "QSN7000-7       ",
		अणु  0,  0,  0,  9 पूर्ण, अणु  0,  0,  0, 11 पूर्ण, अणु  0,  2,  6, 15 पूर्ण,
	पूर्ण,
	अणु /* Gore 5m 26awg Eq */
		अणु 0x00, 0x21, 0x77 पूर्ण, "QSN7600-5       ",
		अणु  0,  0,  0,  8 पूर्ण, अणु  0,  0,  0, 11 पूर्ण, अणु  0,  1,  9, 13 पूर्ण,
	पूर्ण,
	अणु /* Gore 7m 26awg Eq */
		अणु 0x00, 0x21, 0x77 पूर्ण, "QSN7600-7       ",
		अणु  0,  0,  0,  8 पूर्ण, अणु  0,  0,  0, 11 पूर्ण, अणु  10,  1,  8, 15 पूर्ण,
	पूर्ण,
	अणु /* Intersil 12m 24awg Active */
		अणु 0x00, 0x30, 0xB4 पूर्ण, "QLX4000CQSFP1224",
		अणु  0,  0,  0,  2 पूर्ण, अणु  0,  0,  0,  5 पूर्ण, अणु  0,  3,  0,  9 पूर्ण,
	पूर्ण,
	अणु /* Intersil 10m 28awg Active */
		अणु 0x00, 0x30, 0xB4 पूर्ण, "QLX4000CQSFP1028",
		अणु  0,  0,  0,  6 पूर्ण, अणु  0,  0,  0,  4 पूर्ण, अणु  0,  2,  0,  2 पूर्ण,
	पूर्ण,
	अणु /* Intersil 7m 30awg Active */
		अणु 0x00, 0x30, 0xB4 पूर्ण, "QLX4000CQSFP0730",
		अणु  0,  0,  0,  6 पूर्ण, अणु  0,  0,  0,  4 पूर्ण, अणु  0,  1,  0,  3 पूर्ण,
	पूर्ण,
	अणु /* Intersil 5m 32awg Active */
		अणु 0x00, 0x30, 0xB4 पूर्ण, "QLX4000CQSFP0532",
		अणु  0,  0,  0,  6 पूर्ण, अणु  0,  0,  0,  6 पूर्ण, अणु  0,  2,  0,  8 पूर्ण,
	पूर्ण,
	अणु /* Intersil Default Active */
		अणु 0x00, 0x30, 0xB4 पूर्ण, शून्य,
		अणु  0,  0,  0,  6 पूर्ण, अणु  0,  0,  0,  5 पूर्ण, अणु  0,  2,  0,  5 पूर्ण,
	पूर्ण,
	अणु /* Luxtera 20m Active Optical */
		अणु 0x00, 0x25, 0x63 पूर्ण, शून्य,
		अणु  0,  0,  0,  5 पूर्ण, अणु  0,  0,  0,  8 पूर्ण, अणु  0,  2,  0,  12 पूर्ण,
	पूर्ण,
	अणु /* Molex 1M Cu loopback */
		अणु 0x00, 0x09, 0x3A पूर्ण, "74763-0025      ",
		अणु  2,  2,  6, 15 पूर्ण, अणु  2,  2,  6, 15 पूर्ण, अणु  2,  2,  6, 15 पूर्ण,
	पूर्ण,
	अणु /* Molex 2m 28awg NoEq */
		अणु 0x00, 0x09, 0x3A पूर्ण, "74757-2201      ",
		अणु  0,  0,  0,  6 पूर्ण, अणु  0,  0,  0,  9 पूर्ण, अणु  0,  1,  1, 15 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा txdds_ent txdds_sdr[TXDDS_TABLE_SZ] = अणु
	/* amp, pre, मुख्य, post */
	अणु  2, 2, 15,  6 पूर्ण,	/* Loopback */
	अणु  0, 0,  0,  1 पूर्ण,	/*  2 dB */
	अणु  0, 0,  0,  2 पूर्ण,	/*  3 dB */
	अणु  0, 0,  0,  3 पूर्ण,	/*  4 dB */
	अणु  0, 0,  0,  4 पूर्ण,	/*  5 dB */
	अणु  0, 0,  0,  5 पूर्ण,	/*  6 dB */
	अणु  0, 0,  0,  6 पूर्ण,	/*  7 dB */
	अणु  0, 0,  0,  7 पूर्ण,	/*  8 dB */
	अणु  0, 0,  0,  8 पूर्ण,	/*  9 dB */
	अणु  0, 0,  0,  9 पूर्ण,	/* 10 dB */
	अणु  0, 0,  0, 10 पूर्ण,	/* 11 dB */
	अणु  0, 0,  0, 11 पूर्ण,	/* 12 dB */
	अणु  0, 0,  0, 12 पूर्ण,	/* 13 dB */
	अणु  0, 0,  0, 13 पूर्ण,	/* 14 dB */
	अणु  0, 0,  0, 14 पूर्ण,	/* 15 dB */
	अणु  0, 0,  0, 15 पूर्ण,	/* 16 dB */
पूर्ण;

अटल स्थिर काष्ठा txdds_ent txdds_ddr[TXDDS_TABLE_SZ] = अणु
	/* amp, pre, मुख्य, post */
	अणु  2, 2, 15,  6 पूर्ण,	/* Loopback */
	अणु  0, 0,  0,  8 पूर्ण,	/*  2 dB */
	अणु  0, 0,  0,  8 पूर्ण,	/*  3 dB */
	अणु  0, 0,  0,  9 पूर्ण,	/*  4 dB */
	अणु  0, 0,  0,  9 पूर्ण,	/*  5 dB */
	अणु  0, 0,  0, 10 पूर्ण,	/*  6 dB */
	अणु  0, 0,  0, 10 पूर्ण,	/*  7 dB */
	अणु  0, 0,  0, 11 पूर्ण,	/*  8 dB */
	अणु  0, 0,  0, 11 पूर्ण,	/*  9 dB */
	अणु  0, 0,  0, 12 पूर्ण,	/* 10 dB */
	अणु  0, 0,  0, 12 पूर्ण,	/* 11 dB */
	अणु  0, 0,  0, 13 पूर्ण,	/* 12 dB */
	अणु  0, 0,  0, 13 पूर्ण,	/* 13 dB */
	अणु  0, 0,  0, 14 पूर्ण,	/* 14 dB */
	अणु  0, 0,  0, 14 पूर्ण,	/* 15 dB */
	अणु  0, 0,  0, 15 पूर्ण,	/* 16 dB */
पूर्ण;

अटल स्थिर काष्ठा txdds_ent txdds_qdr[TXDDS_TABLE_SZ] = अणु
	/* amp, pre, मुख्य, post */
	अणु  2, 2, 15,  6 पूर्ण,	/* Loopback */
	अणु  0, 1,  0,  7 पूर्ण,	/*  2 dB (also QMH7342) */
	अणु  0, 1,  0,  9 पूर्ण,	/*  3 dB (also QMH7342) */
	अणु  0, 1,  0, 11 पूर्ण,	/*  4 dB */
	अणु  0, 1,  0, 13 पूर्ण,	/*  5 dB */
	अणु  0, 1,  0, 15 पूर्ण,	/*  6 dB */
	अणु  0, 1,  3, 15 पूर्ण,	/*  7 dB */
	अणु  0, 1,  7, 15 पूर्ण,	/*  8 dB */
	अणु  0, 1,  7, 15 पूर्ण,	/*  9 dB */
	अणु  0, 1,  8, 15 पूर्ण,	/* 10 dB */
	अणु  0, 1,  9, 15 पूर्ण,	/* 11 dB */
	अणु  0, 1, 10, 15 पूर्ण,	/* 12 dB */
	अणु  0, 2,  6, 15 पूर्ण,	/* 13 dB */
	अणु  0, 2,  7, 15 पूर्ण,	/* 14 dB */
	अणु  0, 2,  8, 15 पूर्ण,	/* 15 dB */
	अणु  0, 2,  9, 15 पूर्ण,	/* 16 dB */
पूर्ण;

/*
 * extra entries क्रम use with txselect, क्रम indices >= TXDDS_TABLE_SZ.
 * These are mostly used क्रम mez cards going through connectors
 * and backplane traces, but can be used to add other "unusual"
 * table values as well.
 */
अटल स्थिर काष्ठा txdds_ent txdds_extra_sdr[TXDDS_EXTRA_SZ] = अणु
	/* amp, pre, मुख्य, post */
	अणु  0, 0, 0,  1 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  1 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  2 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  2 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  3 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  4 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 1, 4, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 3, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0, 12 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0, 11 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0,  9 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0, 14 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 2, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0, 11 पूर्ण,       /* QME7342 backplane settings 1.1 */
	अणु  0, 1, 0,  7 पूर्ण,       /* QME7342 backplane settings 1.1 */
	अणु  0, 1, 0,  9 पूर्ण,       /* QME7342 backplane settings 1.1 */
	अणु  0, 1, 0,  6 पूर्ण,       /* QME7342 backplane settings 1.1 */
	अणु  0, 1, 0,  8 पूर्ण,       /* QME7342 backplane settings 1.1 */
पूर्ण;

अटल स्थिर काष्ठा txdds_ent txdds_extra_ddr[TXDDS_EXTRA_SZ] = अणु
	/* amp, pre, मुख्य, post */
	अणु  0, 0, 0,  7 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  7 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  8 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  8 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0,  9 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 0, 0, 10 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 1, 4, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 3, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0, 12 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0, 11 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0,  9 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0, 14 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 2, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1, 0, 11 पूर्ण,       /* QME7342 backplane settings 1.1 */
	अणु  0, 1, 0,  7 पूर्ण,       /* QME7342 backplane settings 1.1 */
	अणु  0, 1, 0,  9 पूर्ण,       /* QME7342 backplane settings 1.1 */
	अणु  0, 1, 0,  6 पूर्ण,       /* QME7342 backplane settings 1.1 */
	अणु  0, 1, 0,  8 पूर्ण,       /* QME7342 backplane settings 1.1 */
पूर्ण;

अटल स्थिर काष्ठा txdds_ent txdds_extra_qdr[TXDDS_EXTRA_SZ] = अणु
	/* amp, pre, मुख्य, post */
	अणु  0, 1,  0,  4 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 1,  0,  5 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 1,  0,  6 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 1,  0,  8 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 1,  0, 10 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 1,  0, 12 पूर्ण,	/* QMH7342 backplane settings */
	अणु  0, 1,  4, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1,  3, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1,  0, 12 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1,  0, 11 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1,  0,  9 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1,  0, 14 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1,  2, 15 पूर्ण,	/* QME7342 backplane settings 1.0 */
	अणु  0, 1,  0, 11 पूर्ण,      /* QME7342 backplane settings 1.1 */
	अणु  0, 1,  0,  7 पूर्ण,      /* QME7342 backplane settings 1.1 */
	अणु  0, 1,  0,  9 पूर्ण,      /* QME7342 backplane settings 1.1 */
	अणु  0, 1,  0,  6 पूर्ण,      /* QME7342 backplane settings 1.1 */
	अणु  0, 1,  0,  8 पूर्ण,      /* QME7342 backplane settings 1.1 */
पूर्ण;

अटल स्थिर काष्ठा txdds_ent txdds_extra_mfg[TXDDS_MFG_SZ] = अणु
	/* amp, pre, मुख्य, post */
	अणु 0, 0, 0, 0 पूर्ण,         /* QME7342 mfg settings */
	अणु 0, 0, 0, 6 पूर्ण,         /* QME7342 P2 mfg settings */
पूर्ण;

अटल स्थिर काष्ठा txdds_ent *get_atten_table(स्थिर काष्ठा txdds_ent *txdds,
					       अचिन्हित atten)
अणु
	/*
	 * The attenuation table starts at 2dB क्रम entry 1,
	 * with entry 0 being the loopback entry.
	 */
	अगर (atten <= 2)
		atten = 1;
	अन्यथा अगर (atten > TXDDS_TABLE_SZ)
		atten = TXDDS_TABLE_SZ - 1;
	अन्यथा
		atten--;
	वापस txdds + atten;
पूर्ण

/*
 * अगर override is set, the module parameter txselect has a value
 * क्रम this specअगरic port, so use it, rather than our normal mechanism.
 */
अटल व्योम find_best_ent(काष्ठा qib_pportdata *ppd,
			  स्थिर काष्ठा txdds_ent **sdr_dds,
			  स्थिर काष्ठा txdds_ent **ddr_dds,
			  स्थिर काष्ठा txdds_ent **qdr_dds, पूर्णांक override)
अणु
	काष्ठा qib_qsfp_cache *qd = &ppd->cpspec->qsfp_data.cache;
	पूर्णांक idx;

	/* Search table of known cables */
	क्रम (idx = 0; !override && idx < ARRAY_SIZE(venकरोr_txdds); ++idx) अणु
		स्थिर काष्ठा venकरोr_txdds_ent *v = venकरोr_txdds + idx;

		अगर (!स_भेद(v->oui, qd->oui, QSFP_VOUI_LEN) &&
		    (!v->partnum ||
		     !स_भेद(v->partnum, qd->partnum, QSFP_PN_LEN))) अणु
			*sdr_dds = &v->sdr;
			*ddr_dds = &v->ddr;
			*qdr_dds = &v->qdr;
			वापस;
		पूर्ण
	पूर्ण

	/* Active cables करोn't have attenuation so we only set SERDES
	 * settings to account क्रम the attenuation of the board traces. */
	अगर (!override && QSFP_IS_ACTIVE(qd->tech)) अणु
		*sdr_dds = txdds_sdr + ppd->dd->board_atten;
		*ddr_dds = txdds_ddr + ppd->dd->board_atten;
		*qdr_dds = txdds_qdr + ppd->dd->board_atten;
		वापस;
	पूर्ण

	अगर (!override && QSFP_HAS_ATTEN(qd->tech) && (qd->atten[0] ||
						      qd->atten[1])) अणु
		*sdr_dds = get_atten_table(txdds_sdr, qd->atten[0]);
		*ddr_dds = get_atten_table(txdds_ddr, qd->atten[0]);
		*qdr_dds = get_atten_table(txdds_qdr, qd->atten[1]);
		वापस;
	पूर्ण अन्यथा अगर (ppd->cpspec->no_eep < TXDDS_TABLE_SZ) अणु
		/*
		 * If we have no (or incomplete) data from the cable
		 * EEPROM, or no QSFP, or override is set, use the
		 * module parameter value to index पूर्णांकo the attentuation
		 * table.
		 */
		idx = ppd->cpspec->no_eep;
		*sdr_dds = &txdds_sdr[idx];
		*ddr_dds = &txdds_ddr[idx];
		*qdr_dds = &txdds_qdr[idx];
	पूर्ण अन्यथा अगर (ppd->cpspec->no_eep < (TXDDS_TABLE_SZ + TXDDS_EXTRA_SZ)) अणु
		/* similar to above, but index पूर्णांकo the "extra" table. */
		idx = ppd->cpspec->no_eep - TXDDS_TABLE_SZ;
		*sdr_dds = &txdds_extra_sdr[idx];
		*ddr_dds = &txdds_extra_ddr[idx];
		*qdr_dds = &txdds_extra_qdr[idx];
	पूर्ण अन्यथा अगर ((IS_QME(ppd->dd) || IS_QMH(ppd->dd)) &&
		   ppd->cpspec->no_eep < (TXDDS_TABLE_SZ + TXDDS_EXTRA_SZ +
					  TXDDS_MFG_SZ)) अणु
		idx = ppd->cpspec->no_eep - (TXDDS_TABLE_SZ + TXDDS_EXTRA_SZ);
		pr_info("IB%u:%u use idx %u into txdds_mfg\n",
			ppd->dd->unit, ppd->port, idx);
		*sdr_dds = &txdds_extra_mfg[idx];
		*ddr_dds = &txdds_extra_mfg[idx];
		*qdr_dds = &txdds_extra_mfg[idx];
	पूर्ण अन्यथा अणु
		/* this shouldn't happen, it's range checked */
		*sdr_dds = txdds_sdr + qib_दीर्घ_atten;
		*ddr_dds = txdds_ddr + qib_दीर्घ_atten;
		*qdr_dds = txdds_qdr + qib_दीर्घ_atten;
	पूर्ण
पूर्ण

अटल व्योम init_txdds_table(काष्ठा qib_pportdata *ppd, पूर्णांक override)
अणु
	स्थिर काष्ठा txdds_ent *sdr_dds, *ddr_dds, *qdr_dds;
	काष्ठा txdds_ent *dds;
	पूर्णांक idx;
	पूर्णांक single_ent = 0;

	find_best_ent(ppd, &sdr_dds, &ddr_dds, &qdr_dds, override);

	/* क्रम mez cards or override, use the selected value क्रम all entries */
	अगर (!(ppd->dd->flags & QIB_HAS_QSFP) || override)
		single_ent = 1;

	/* Fill in the first entry with the best entry found. */
	set_txdds(ppd, 0, sdr_dds);
	set_txdds(ppd, TXDDS_TABLE_SZ, ddr_dds);
	set_txdds(ppd, 2 * TXDDS_TABLE_SZ, qdr_dds);
	अगर (ppd->lflags & (QIBL_LINKINIT | QIBL_LINKARMED |
		QIBL_LINKACTIVE)) अणु
		dds = (काष्ठा txdds_ent *)(ppd->link_speed_active ==
					   QIB_IB_QDR ?  qdr_dds :
					   (ppd->link_speed_active ==
					    QIB_IB_DDR ? ddr_dds : sdr_dds));
		ग_लिखो_tx_serdes_param(ppd, dds);
	पूर्ण

	/* Fill in the reमुख्यing entries with the शेष table values. */
	क्रम (idx = 1; idx < ARRAY_SIZE(txdds_sdr); ++idx) अणु
		set_txdds(ppd, idx, single_ent ? sdr_dds : txdds_sdr + idx);
		set_txdds(ppd, idx + TXDDS_TABLE_SZ,
			  single_ent ? ddr_dds : txdds_ddr + idx);
		set_txdds(ppd, idx + 2 * TXDDS_TABLE_SZ,
			  single_ent ? qdr_dds : txdds_qdr + idx);
	पूर्ण
पूर्ण

#घोषणा KR_AHB_ACC KREG_IDX(ahb_access_ctrl)
#घोषणा KR_AHB_TRANS KREG_IDX(ahb_transaction_reg)
#घोषणा AHB_TRANS_RDY SYM_MASK(ahb_transaction_reg, ahb_rdy)
#घोषणा AHB_ADDR_LSB SYM_LSB(ahb_transaction_reg, ahb_address)
#घोषणा AHB_DATA_LSB SYM_LSB(ahb_transaction_reg, ahb_data)
#घोषणा AHB_WR SYM_MASK(ahb_transaction_reg, ग_लिखो_not_पढ़ो)
#घोषणा AHB_TRANS_TRIES 10

/*
 * The chan argument is 0=chan0, 1=chan1, 2=pll, 3=chan2, 4=chan4,
 * 5=subप्रणाली which is why most calls have "chan + chan >> 1"
 * क्रम the channel argument.
 */
अटल u32 ahb_mod(काष्ठा qib_devdata *dd, पूर्णांक quad, पूर्णांक chan, पूर्णांक addr,
		    u32 data, u32 mask)
अणु
	u32 rd_data, wr_data, sz_mask;
	u64 trans, acc, prev_acc;
	u32 ret = 0xBAD0BAD;
	पूर्णांक tries;

	prev_acc = qib_पढ़ो_kreg64(dd, KR_AHB_ACC);
	/* From this poपूर्णांक on, make sure we वापस access */
	acc = (quad << 1) | 1;
	qib_ग_लिखो_kreg(dd, KR_AHB_ACC, acc);

	क्रम (tries = 1; tries < AHB_TRANS_TRIES; ++tries) अणु
		trans = qib_पढ़ो_kreg64(dd, KR_AHB_TRANS);
		अगर (trans & AHB_TRANS_RDY)
			अवरोध;
	पूर्ण
	अगर (tries >= AHB_TRANS_TRIES) अणु
		qib_dev_err(dd, "No ahb_rdy in %d tries\n", AHB_TRANS_TRIES);
		जाओ bail;
	पूर्ण

	/* If mask is not all 1s, we need to पढ़ो, but dअगरferent SerDes
	 * entities have dअगरferent sizes
	 */
	sz_mask = (1UL << ((quad == 1) ? 32 : 16)) - 1;
	wr_data = data & mask & sz_mask;
	अगर ((~mask & sz_mask) != 0) अणु
		trans = ((chan << 6) | addr) << (AHB_ADDR_LSB + 1);
		qib_ग_लिखो_kreg(dd, KR_AHB_TRANS, trans);

		क्रम (tries = 1; tries < AHB_TRANS_TRIES; ++tries) अणु
			trans = qib_पढ़ो_kreg64(dd, KR_AHB_TRANS);
			अगर (trans & AHB_TRANS_RDY)
				अवरोध;
		पूर्ण
		अगर (tries >= AHB_TRANS_TRIES) अणु
			qib_dev_err(dd, "No Rd ahb_rdy in %d tries\n",
				    AHB_TRANS_TRIES);
			जाओ bail;
		पूर्ण
		/* Re-पढ़ो in हाल host split पढ़ोs and पढ़ो data first */
		trans = qib_पढ़ो_kreg64(dd, KR_AHB_TRANS);
		rd_data = (uपूर्णांक32_t)(trans >> AHB_DATA_LSB);
		wr_data |= (rd_data & ~mask & sz_mask);
	पूर्ण

	/* If mask is not zero, we need to ग_लिखो. */
	अगर (mask & sz_mask) अणु
		trans = ((chan << 6) | addr) << (AHB_ADDR_LSB + 1);
		trans |= ((uपूर्णांक64_t)wr_data << AHB_DATA_LSB);
		trans |= AHB_WR;
		qib_ग_लिखो_kreg(dd, KR_AHB_TRANS, trans);

		क्रम (tries = 1; tries < AHB_TRANS_TRIES; ++tries) अणु
			trans = qib_पढ़ो_kreg64(dd, KR_AHB_TRANS);
			अगर (trans & AHB_TRANS_RDY)
				अवरोध;
		पूर्ण
		अगर (tries >= AHB_TRANS_TRIES) अणु
			qib_dev_err(dd, "No Wr ahb_rdy in %d tries\n",
				    AHB_TRANS_TRIES);
			जाओ bail;
		पूर्ण
	पूर्ण
	ret = wr_data;
bail:
	qib_ग_लिखो_kreg(dd, KR_AHB_ACC, prev_acc);
	वापस ret;
पूर्ण

अटल व्योम ibsd_wr_allchans(काष्ठा qib_pportdata *ppd, पूर्णांक addr, अचिन्हित data,
			     अचिन्हित mask)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक chan;

	क्रम (chan = 0; chan < SERDES_CHANS; ++chan) अणु
		ahb_mod(dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)), addr,
			data, mask);
		ahb_mod(dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)), addr,
			0, 0);
	पूर्ण
पूर्ण

अटल व्योम serdes_7322_los_enable(काष्ठा qib_pportdata *ppd, पूर्णांक enable)
अणु
	u64 data = qib_पढ़ो_kreg_port(ppd, krp_serdesctrl);
	u8 state = SYM_FIELD(data, IBSerdesCtrl_0, RXLOSEN);

	अगर (enable && !state) अणु
		pr_info("IB%u:%u Turning LOS on\n",
			ppd->dd->unit, ppd->port);
		data |= SYM_MASK(IBSerdesCtrl_0, RXLOSEN);
	पूर्ण अन्यथा अगर (!enable && state) अणु
		pr_info("IB%u:%u Turning LOS off\n",
			ppd->dd->unit, ppd->port);
		data &= ~SYM_MASK(IBSerdesCtrl_0, RXLOSEN);
	पूर्ण
	qib_ग_लिखो_kreg_port(ppd, krp_serdesctrl, data);
पूर्ण

अटल पूर्णांक serdes_7322_init(काष्ठा qib_pportdata *ppd)
अणु
	पूर्णांक ret = 0;

	अगर (ppd->dd->cspec->r1)
		ret = serdes_7322_init_old(ppd);
	अन्यथा
		ret = serdes_7322_init_new(ppd);
	वापस ret;
पूर्ण

अटल पूर्णांक serdes_7322_init_old(काष्ठा qib_pportdata *ppd)
अणु
	u32 le_val;

	/*
	 * Initialize the Tx DDS tables.  Also करोne every QSFP event,
	 * क्रम adapters with QSFP
	 */
	init_txdds_table(ppd, 0);

	/* ensure no tx overrides from earlier driver loads */
	qib_ग_लिखो_kreg_port(ppd, krp_tx_deemph_override,
		SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		reset_tx_deemphasis_override));

	/* Patch some SerDes शेषs to "Better for IB" */
	/* Timing Loop Bandwidth: cdr_timing[11:9] = 0 */
	ibsd_wr_allchans(ppd, 2, 0, BMASK(11, 9));

	/* Termination: rxtermctrl_r2d addr 11 bits [12:11] = 1 */
	ibsd_wr_allchans(ppd, 11, (1 << 11), BMASK(12, 11));
	/* Enable LE2: rxle2en_r2a addr 13 bit [6] = 1 */
	ibsd_wr_allchans(ppd, 13, (1 << 6), (1 << 6));

	/* May be overridden in qsfp_7322_event */
	le_val = IS_QME(ppd->dd) ? LE2_QME : LE2_DEFAULT;
	ibsd_wr_allchans(ppd, 13, (le_val << 7), BMASK(9, 7));

	/* enable LE1 adaptation क्रम all but QME, which is disabled */
	le_val = IS_QME(ppd->dd) ? 0 : 1;
	ibsd_wr_allchans(ppd, 13, (le_val << 5), (1 << 5));

	/* Clear cmode-override, may be set from older driver */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 0 << 14, 1 << 14);

	/* Timing Recovery: rxtapsel addr 5 bits [9:8] = 0 */
	ibsd_wr_allchans(ppd, 5, (0 << 8), BMASK(9, 8));

	/* setup LoS params; these are subप्रणाली, so chan == 5 */
	/* LoS filter threshold_count on, ch 0-3, set to 8 */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 5, 8 << 11, BMASK(14, 11));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 7, 8 << 4, BMASK(7, 4));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 8, 8 << 11, BMASK(14, 11));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 8 << 4, BMASK(7, 4));

	/* LoS filter threshold_count off, ch 0-3, set to 4 */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 6, 4 << 0, BMASK(3, 0));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 7, 4 << 8, BMASK(11, 8));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 9, 4 << 0, BMASK(3, 0));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 4 << 8, BMASK(11, 8));

	/* LoS filter select enabled */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 9, 1 << 15, 1 << 15);

	/* LoS target data:  SDR=4, DDR=2, QDR=1 */
	ibsd_wr_allchans(ppd, 14, (1 << 3), BMASK(5, 3)); /* QDR */
	ibsd_wr_allchans(ppd, 20, (2 << 10), BMASK(12, 10)); /* DDR */
	ibsd_wr_allchans(ppd, 20, (4 << 13), BMASK(15, 13)); /* SDR */

	serdes_7322_los_enable(ppd, 1);

	/* rxbistena; set 0 to aव्योम effects of it चयन later */
	ibsd_wr_allchans(ppd, 9, 0 << 15, 1 << 15);

	/* Configure 4 DFE taps, and only they adapt */
	ibsd_wr_allchans(ppd, 16, 0 << 0, BMASK(1, 0));

	/* gain hi stop 32 (22) (6:1) lo stop 7 (10:7) target 22 (13) (15:11) */
	le_val = (ppd->dd->cspec->r1 || IS_QME(ppd->dd)) ? 0xb6c0 : 0x6bac;
	ibsd_wr_allchans(ppd, 21, le_val, 0xfffe);

	/*
	 * Set receive adaptation mode.  SDR and DDR adaptation are
	 * always on, and QDR is initially enabled; later disabled.
	 */
	qib_ग_लिखो_kreg_port(ppd, krp_अटल_adapt_dis(0), 0ULL);
	qib_ग_लिखो_kreg_port(ppd, krp_अटल_adapt_dis(1), 0ULL);
	qib_ग_लिखो_kreg_port(ppd, krp_अटल_adapt_dis(2),
			    ppd->dd->cspec->r1 ?
			    QDR_STATIC_ADAPT_DOWN_R1 : QDR_STATIC_ADAPT_DOWN);
	ppd->cpspec->qdr_dfe_on = 1;

	/* FLoop LOS gate: PPM filter  enabled */
	ibsd_wr_allchans(ppd, 38, 0 << 10, 1 << 10);

	/* rx offset center enabled */
	ibsd_wr_allchans(ppd, 12, 1 << 4, 1 << 4);

	अगर (!ppd->dd->cspec->r1) अणु
		ibsd_wr_allchans(ppd, 12, 1 << 12, 1 << 12);
		ibsd_wr_allchans(ppd, 12, 2 << 8, 0x0f << 8);
	पूर्ण

	/* Set the frequency loop bandwidth to 15 */
	ibsd_wr_allchans(ppd, 2, 15 << 5, BMASK(8, 5));

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_7322_init_new(काष्ठा qib_pportdata *ppd)
अणु
	अचिन्हित दीर्घ tend;
	u32 le_val, rxcalकरोne;
	पूर्णांक chan, chan_करोne = (1 << SERDES_CHANS) - 1;

	/* Clear cmode-override, may be set from older driver */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 0 << 14, 1 << 14);

	/* ensure no tx overrides from earlier driver loads */
	qib_ग_लिखो_kreg_port(ppd, krp_tx_deemph_override,
		SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		reset_tx_deemphasis_override));

	/* START OF LSI SUGGESTED SERDES BRINGUP */
	/* Reset - Calibration Setup */
	/*       Stop DFE adaptaion */
	ibsd_wr_allchans(ppd, 1, 0, BMASK(9, 1));
	/*       Disable LE1 */
	ibsd_wr_allchans(ppd, 13, 0, BMASK(5, 5));
	/*       Disable स्वतःadapt क्रम LE1 */
	ibsd_wr_allchans(ppd, 1, 0, BMASK(15, 15));
	/*       Disable LE2 */
	ibsd_wr_allchans(ppd, 13, 0, BMASK(6, 6));
	/*       Disable VGA */
	ibsd_wr_allchans(ppd, 5, 0, BMASK(0, 0));
	/*       Disable AFE Offset Cancel */
	ibsd_wr_allchans(ppd, 12, 0, BMASK(12, 12));
	/*       Disable Timing Loop */
	ibsd_wr_allchans(ppd, 2, 0, BMASK(3, 3));
	/*       Disable Frequency Loop */
	ibsd_wr_allchans(ppd, 2, 0, BMASK(4, 4));
	/*       Disable Baseline Wander Correction */
	ibsd_wr_allchans(ppd, 13, 0, BMASK(13, 13));
	/*       Disable RX Calibration */
	ibsd_wr_allchans(ppd, 4, 0, BMASK(10, 10));
	/*       Disable RX Offset Calibration */
	ibsd_wr_allchans(ppd, 12, 0, BMASK(4, 4));
	/*       Select BB CDR */
	ibsd_wr_allchans(ppd, 2, (1 << 15), BMASK(15, 15));
	/*       CDR Step Size */
	ibsd_wr_allchans(ppd, 5, 0, BMASK(9, 8));
	/*       Enable phase Calibration */
	ibsd_wr_allchans(ppd, 12, (1 << 5), BMASK(5, 5));
	/*       DFE Bandwidth [2:14-12] */
	ibsd_wr_allchans(ppd, 2, (4 << 12), BMASK(14, 12));
	/*       DFE Config (4 taps only) */
	ibsd_wr_allchans(ppd, 16, 0, BMASK(1, 0));
	/*       Gain Loop Bandwidth */
	अगर (!ppd->dd->cspec->r1) अणु
		ibsd_wr_allchans(ppd, 12, 1 << 12, BMASK(12, 12));
		ibsd_wr_allchans(ppd, 12, 2 << 8, BMASK(11, 8));
	पूर्ण अन्यथा अणु
		ibsd_wr_allchans(ppd, 19, (3 << 11), BMASK(13, 11));
	पूर्ण
	/*       Baseline Wander Correction Gain [13:4-0] (leave as शेष) */
	/*       Baseline Wander Correction Gain [3:7-5] (leave as शेष) */
	/*       Data Rate Select [5:7-6] (leave as शेष) */
	/*       RX Parallel Word Width [3:10-8] (leave as शेष) */

	/* RX REST */
	/*       Single- or Multi-channel reset */
	/*       RX Analog reset */
	/*       RX Digital reset */
	ibsd_wr_allchans(ppd, 0, 0, BMASK(15, 13));
	msleep(20);
	/*       RX Analog reset */
	ibsd_wr_allchans(ppd, 0, (1 << 14), BMASK(14, 14));
	msleep(20);
	/*       RX Digital reset */
	ibsd_wr_allchans(ppd, 0, (1 << 13), BMASK(13, 13));
	msleep(20);

	/* setup LoS params; these are subप्रणाली, so chan == 5 */
	/* LoS filter threshold_count on, ch 0-3, set to 8 */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 5, 8 << 11, BMASK(14, 11));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 7, 8 << 4, BMASK(7, 4));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 8, 8 << 11, BMASK(14, 11));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 8 << 4, BMASK(7, 4));

	/* LoS filter threshold_count off, ch 0-3, set to 4 */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 6, 4 << 0, BMASK(3, 0));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 7, 4 << 8, BMASK(11, 8));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 9, 4 << 0, BMASK(3, 0));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 4 << 8, BMASK(11, 8));

	/* LoS filter select enabled */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 9, 1 << 15, 1 << 15);

	/* LoS target data:  SDR=4, DDR=2, QDR=1 */
	ibsd_wr_allchans(ppd, 14, (1 << 3), BMASK(5, 3)); /* QDR */
	ibsd_wr_allchans(ppd, 20, (2 << 10), BMASK(12, 10)); /* DDR */
	ibsd_wr_allchans(ppd, 20, (4 << 13), BMASK(15, 13)); /* SDR */

	/* Turn on LOS on initial SERDES init */
	serdes_7322_los_enable(ppd, 1);
	/* FLoop LOS gate: PPM filter  enabled */
	ibsd_wr_allchans(ppd, 38, 0 << 10, 1 << 10);

	/* RX LATCH CALIBRATION */
	/*       Enable Eyefinder Phase Calibration latch */
	ibsd_wr_allchans(ppd, 15, 1, BMASK(0, 0));
	/*       Enable RX Offset Calibration latch */
	ibsd_wr_allchans(ppd, 12, (1 << 4), BMASK(4, 4));
	msleep(20);
	/*       Start Calibration */
	ibsd_wr_allchans(ppd, 4, (1 << 10), BMASK(10, 10));
	tend = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (chan_करोne && !समय_is_beक्रमe_jअगरfies(tend)) अणु
		msleep(20);
		क्रम (chan = 0; chan < SERDES_CHANS; ++chan) अणु
			rxcalकरोne = ahb_mod(ppd->dd, IBSD(ppd->hw_pidx),
					    (chan + (chan >> 1)),
					    25, 0, 0);
			अगर ((~rxcalकरोne & (u32)BMASK(9, 9)) == 0 &&
			    (~chan_करोne & (1 << chan)) == 0)
				chan_करोne &= ~(1 << chan);
		पूर्ण
	पूर्ण
	अगर (chan_करोne) अणु
		pr_info("Serdes %d calibration not done after .5 sec: 0x%x\n",
			 IBSD(ppd->hw_pidx), chan_करोne);
	पूर्ण अन्यथा अणु
		क्रम (chan = 0; chan < SERDES_CHANS; ++chan) अणु
			rxcalकरोne = ahb_mod(ppd->dd, IBSD(ppd->hw_pidx),
					    (chan + (chan >> 1)),
					    25, 0, 0);
			अगर ((~rxcalकरोne & (u32)BMASK(10, 10)) == 0)
				pr_info("Serdes %d chan %d calibration failed\n",
					IBSD(ppd->hw_pidx), chan);
		पूर्ण
	पूर्ण

	/*       Turn off Calibration */
	ibsd_wr_allchans(ppd, 4, 0, BMASK(10, 10));
	msleep(20);

	/* BRING RX UP */
	/*       Set LE2 value (May be overridden in qsfp_7322_event) */
	le_val = IS_QME(ppd->dd) ? LE2_QME : LE2_DEFAULT;
	ibsd_wr_allchans(ppd, 13, (le_val << 7), BMASK(9, 7));
	/*       Set LE2 Loop bandwidth */
	ibsd_wr_allchans(ppd, 3, (7 << 5), BMASK(7, 5));
	/*       Enable LE2 */
	ibsd_wr_allchans(ppd, 13, (1 << 6), BMASK(6, 6));
	msleep(20);
	/*       Enable H0 only */
	ibsd_wr_allchans(ppd, 1, 1, BMASK(9, 1));
	/* gain hi stop 32 (22) (6:1) lo stop 7 (10:7) target 22 (13) (15:11) */
	le_val = (ppd->dd->cspec->r1 || IS_QME(ppd->dd)) ? 0xb6c0 : 0x6bac;
	ibsd_wr_allchans(ppd, 21, le_val, 0xfffe);
	/*       Enable VGA */
	ibsd_wr_allchans(ppd, 5, 0, BMASK(0, 0));
	msleep(20);
	/*       Set Frequency Loop Bandwidth */
	ibsd_wr_allchans(ppd, 2, (15 << 5), BMASK(8, 5));
	/*       Enable Frequency Loop */
	ibsd_wr_allchans(ppd, 2, (1 << 4), BMASK(4, 4));
	/*       Set Timing Loop Bandwidth */
	ibsd_wr_allchans(ppd, 2, 0, BMASK(11, 9));
	/*       Enable Timing Loop */
	ibsd_wr_allchans(ppd, 2, (1 << 3), BMASK(3, 3));
	msleep(50);
	/*       Enable DFE
	 *       Set receive adaptation mode.  SDR and DDR adaptation are
	 *       always on, and QDR is initially enabled; later disabled.
	 */
	qib_ग_लिखो_kreg_port(ppd, krp_अटल_adapt_dis(0), 0ULL);
	qib_ग_लिखो_kreg_port(ppd, krp_अटल_adapt_dis(1), 0ULL);
	qib_ग_लिखो_kreg_port(ppd, krp_अटल_adapt_dis(2),
			    ppd->dd->cspec->r1 ?
			    QDR_STATIC_ADAPT_DOWN_R1 : QDR_STATIC_ADAPT_DOWN);
	ppd->cpspec->qdr_dfe_on = 1;
	/*       Disable LE1  */
	ibsd_wr_allchans(ppd, 13, (0 << 5), (1 << 5));
	/*       Disable स्वतः adapt क्रम LE1 */
	ibsd_wr_allchans(ppd, 1, (0 << 15), BMASK(15, 15));
	msleep(20);
	/*       Enable AFE Offset Cancel */
	ibsd_wr_allchans(ppd, 12, (1 << 12), BMASK(12, 12));
	/*       Enable Baseline Wander Correction */
	ibsd_wr_allchans(ppd, 12, (1 << 13), BMASK(13, 13));
	/* Termination: rxtermctrl_r2d addr 11 bits [12:11] = 1 */
	ibsd_wr_allchans(ppd, 11, (1 << 11), BMASK(12, 11));
	/* VGA output common mode */
	ibsd_wr_allchans(ppd, 12, (3 << 2), BMASK(3, 2));

	/*
	 * Initialize the Tx DDS tables.  Also करोne every QSFP event,
	 * क्रम adapters with QSFP
	 */
	init_txdds_table(ppd, 0);

	वापस 0;
पूर्ण

/* start adjust QMH serdes parameters */

अटल व्योम set_man_code(काष्ठा qib_pportdata *ppd, पूर्णांक chan, पूर्णांक code)
अणु
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
		9, code << 9, 0x3f << 9);
पूर्ण

अटल व्योम set_man_mode_h1(काष्ठा qib_pportdata *ppd, पूर्णांक chan,
	पूर्णांक enable, u32 tapenable)
अणु
	अगर (enable)
		ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
			1, 3 << 10, 0x1f << 10);
	अन्यथा
		ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
			1, 0, 0x1f << 10);
पूर्ण

/* Set घड़ी to 1, 0, 1, 0 */
अटल व्योम घड़ी_man(काष्ठा qib_pportdata *ppd, पूर्णांक chan)
अणु
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
		4, 0x4000, 0x4000);
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
		4, 0, 0x4000);
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
		4, 0x4000, 0x4000);
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
		4, 0, 0x4000);
पूर्ण

/*
 * ग_लिखो the current Tx serdes pre,post,मुख्य,amp settings पूर्णांकo the serdes.
 * The caller must pass the settings appropriate क्रम the current speed,
 * or not care अगर they are correct क्रम the current speed.
 */
अटल व्योम ग_लिखो_tx_serdes_param(काष्ठा qib_pportdata *ppd,
				  काष्ठा txdds_ent *txdds)
अणु
	u64 deemph;

	deemph = qib_पढ़ो_kreg_port(ppd, krp_tx_deemph_override);
	/* field names क्रम amp, मुख्य, post, pre, respectively */
	deemph &= ~(SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0, txampcntl_d2a) |
		    SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0, txc0_ena) |
		    SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0, txcp1_ena) |
		    SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0, txcn1_ena));

	deemph |= SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
			   tx_override_deemphasis_select);
	deemph |= (txdds->amp & SYM_RMASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		    txampcntl_d2a)) << SYM_LSB(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				       txampcntl_d2a);
	deemph |= (txdds->मुख्य & SYM_RMASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		     txc0_ena)) << SYM_LSB(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				   txc0_ena);
	deemph |= (txdds->post & SYM_RMASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		     txcp1_ena)) << SYM_LSB(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				    txcp1_ena);
	deemph |= (txdds->pre & SYM_RMASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		     txcn1_ena)) << SYM_LSB(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
				    txcn1_ena);
	qib_ग_लिखो_kreg_port(ppd, krp_tx_deemph_override, deemph);
पूर्ण

/*
 * Set the parameters क्रम mez cards on link bounce, so they are
 * always exactly what was requested.  Similar logic to init_txdds
 * but करोes just the serdes.
 */
अटल व्योम adj_tx_serdes(काष्ठा qib_pportdata *ppd)
अणु
	स्थिर काष्ठा txdds_ent *sdr_dds, *ddr_dds, *qdr_dds;
	काष्ठा txdds_ent *dds;

	find_best_ent(ppd, &sdr_dds, &ddr_dds, &qdr_dds, 1);
	dds = (काष्ठा txdds_ent *)(ppd->link_speed_active == QIB_IB_QDR ?
		qdr_dds : (ppd->link_speed_active == QIB_IB_DDR ?
				ddr_dds : sdr_dds));
	ग_लिखो_tx_serdes_param(ppd, dds);
पूर्ण

/* set QDR क्रमced value क्रम H1, अगर needed */
अटल व्योम क्रमce_h1(काष्ठा qib_pportdata *ppd)
अणु
	पूर्णांक chan;

	ppd->cpspec->qdr_reक्रमce = 0;
	अगर (!ppd->dd->cspec->r1)
		वापस;

	क्रम (chan = 0; chan < SERDES_CHANS; chan++) अणु
		set_man_mode_h1(ppd, chan, 1, 0);
		set_man_code(ppd, chan, ppd->cpspec->h1_val);
		घड़ी_man(ppd, chan);
		set_man_mode_h1(ppd, chan, 0, 0);
	पूर्ण
पूर्ण

#घोषणा SJA_EN SYM_MASK(SPC_JTAG_ACCESS_REG, SPC_JTAG_ACCESS_EN)
#घोषणा BISTEN_LSB SYM_LSB(SPC_JTAG_ACCESS_REG, bist_en)

#घोषणा R_OPCODE_LSB 3
#घोषणा R_OP_NOP 0
#घोषणा R_OP_SHIFT 2
#घोषणा R_OP_UPDATE 3
#घोषणा R_TDI_LSB 2
#घोषणा R_TDO_LSB 1
#घोषणा R_RDY 1

अटल पूर्णांक qib_r_grab(काष्ठा qib_devdata *dd)
अणु
	u64 val = SJA_EN;

	qib_ग_लिखो_kreg(dd, kr_r_access, val);
	qib_पढ़ो_kreg32(dd, kr_scratch);
	वापस 0;
पूर्ण

/* qib_r_रुको_क्रम_rdy() not only रुकोs क्रम the पढ़ोy bit, it
 * वापसs the current state of R_TDO
 */
अटल पूर्णांक qib_r_रुको_क्रम_rdy(काष्ठा qib_devdata *dd)
अणु
	u64 val;
	पूर्णांक समयout;

	क्रम (समयout = 0; समयout < 100 ; ++समयout) अणु
		val = qib_पढ़ो_kreg32(dd, kr_r_access);
		अगर (val & R_RDY)
			वापस (val >> R_TDO_LSB) & 1;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक qib_r_shअगरt(काष्ठा qib_devdata *dd, पूर्णांक bisten,
		       पूर्णांक len, u8 *inp, u8 *outp)
अणु
	u64 valbase, val;
	पूर्णांक ret, pos;

	valbase = SJA_EN | (bisten << BISTEN_LSB) |
		(R_OP_SHIFT << R_OPCODE_LSB);
	ret = qib_r_रुको_क्रम_rdy(dd);
	अगर (ret < 0)
		जाओ bail;
	क्रम (pos = 0; pos < len; ++pos) अणु
		val = valbase;
		अगर (outp) अणु
			outp[pos >> 3] &= ~(1 << (pos & 7));
			outp[pos >> 3] |= (ret << (pos & 7));
		पूर्ण
		अगर (inp) अणु
			पूर्णांक tdi = inp[pos >> 3] >> (pos & 7);

			val |= ((tdi & 1) << R_TDI_LSB);
		पूर्ण
		qib_ग_लिखो_kreg(dd, kr_r_access, val);
		qib_पढ़ो_kreg32(dd, kr_scratch);
		ret = qib_r_रुको_क्रम_rdy(dd);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	/* Restore to NOP between operations. */
	val =  SJA_EN | (bisten << BISTEN_LSB);
	qib_ग_लिखो_kreg(dd, kr_r_access, val);
	qib_पढ़ो_kreg32(dd, kr_scratch);
	ret = qib_r_रुको_क्रम_rdy(dd);

	अगर (ret >= 0)
		ret = pos;
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_r_update(काष्ठा qib_devdata *dd, पूर्णांक bisten)
अणु
	u64 val;
	पूर्णांक ret;

	val = SJA_EN | (bisten << BISTEN_LSB) | (R_OP_UPDATE << R_OPCODE_LSB);
	ret = qib_r_रुको_क्रम_rdy(dd);
	अगर (ret >= 0) अणु
		qib_ग_लिखो_kreg(dd, kr_r_access, val);
		qib_पढ़ो_kreg32(dd, kr_scratch);
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा BISTEN_PORT_SEL 15
#घोषणा LEN_PORT_SEL 625
#घोषणा BISTEN_AT 17
#घोषणा LEN_AT 156
#घोषणा BISTEN_ETM 16
#घोषणा LEN_ETM 632

#घोषणा BIT2BYTE(x) (((x) +  BITS_PER_BYTE - 1) / BITS_PER_BYTE)

/* these are common क्रम all IB port use हालs. */
अटल u8 reset_at[BIT2BYTE(LEN_AT)] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
पूर्ण;
अटल u8 reset_ateपंचांग[BIT2BYTE(LEN_ETM)] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0xe3, 0x81, 0x73, 0x3c, 0x70, 0x8e,
	0x07, 0xce, 0xf1, 0xc0, 0x39, 0x1e, 0x38, 0xc7, 0x03, 0xe7,
	0x78, 0xe0, 0x1c, 0x0f, 0x9c, 0x7f, 0x80, 0x73, 0x0f, 0x70,
	0xde, 0x01, 0xce, 0x39, 0xc0, 0xf9, 0x06, 0x38, 0xd7, 0x00,
	0xe7, 0x19, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
पूर्ण;
अटल u8 at[BIT2BYTE(LEN_AT)] = अणु
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
पूर्ण;

/* used क्रम IB1 or IB2, only one in use */
अटल u8 ateपंचांग_1port[BIT2BYTE(LEN_ETM)] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0xf2, 0x80, 0x83, 0x1e, 0x38, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x50, 0xf4, 0x41, 0x00, 0x18, 0x78, 0xc8, 0x03,
	0x07, 0x7b, 0xa0, 0x3e, 0x00, 0x02, 0x00, 0x00, 0x18, 0x00,
	0x18, 0x00, 0x00, 0x00, 0x00, 0x4b, 0x00, 0x00, 0x00,
पूर्ण;

/* used when both IB1 and IB2 are in use */
अटल u8 ateपंचांग_2port[BIT2BYTE(LEN_ETM)] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xf8, 0x80, 0x83, 0x1e, 0x38, 0xe0, 0x03, 0x05,
	0x7b, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0xa2, 0x0f, 0x50, 0xf4, 0x41, 0x00, 0x18, 0x78, 0xd1, 0x07,
	0x02, 0x7c, 0x80, 0x3e, 0x00, 0x02, 0x00, 0x00, 0x3e, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
पूर्ण;

/* used when only IB1 is in use */
अटल u8 portsel_port1[BIT2BYTE(LEN_PORT_SEL)] = अणु
	0x32, 0x65, 0xa4, 0x7b, 0x10, 0x98, 0xdc, 0xfe, 0x13, 0x13,
	0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x73, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
	0x13, 0x78, 0x78, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x74, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x9f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
पूर्ण;

/* used when only IB2 is in use */
अटल u8 portsel_port2[BIT2BYTE(LEN_PORT_SEL)] = अणु
	0x32, 0x65, 0xa4, 0x7b, 0x10, 0x98, 0xdc, 0xfe, 0x39, 0x39,
	0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x73, 0x32, 0x32, 0x32,
	0x32, 0x32, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39,
	0x39, 0x78, 0x78, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39,
	0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x74, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a,
	0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a,
	0x3a, 0x3a, 0x9f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
पूर्ण;

/* used when both IB1 and IB2 are in use */
अटल u8 portsel_2port[BIT2BYTE(LEN_PORT_SEL)] = अणु
	0x32, 0xba, 0x54, 0x76, 0x10, 0x98, 0xdc, 0xfe, 0x13, 0x13,
	0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x73, 0x0c, 0x0c, 0x0c,
	0x0c, 0x0c, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
	0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x74, 0x32,
	0x32, 0x32, 0x32, 0x32, 0x14, 0x14, 0x14, 0x14, 0x14, 0x3a,
	0x3a, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x9f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
पूर्ण;

/*
 * Do setup to properly handle IB link recovery; अगर port is zero, we
 * are initializing to cover both ports; otherwise we are initializing
 * to cover a single port card, or the port has reached INIT and we may
 * need to चयन coverage types.
 */
अटल व्योम setup_7322_link_recovery(काष्ठा qib_pportdata *ppd, u32 both)
अणु
	u8 *portsel, *eपंचांग;
	काष्ठा qib_devdata *dd = ppd->dd;

	अगर (!ppd->dd->cspec->r1)
		वापस;
	अगर (!both) अणु
		dd->cspec->recovery_ports_initted++;
		ppd->cpspec->recovery_init = 1;
	पूर्ण
	अगर (!both && dd->cspec->recovery_ports_initted == 1) अणु
		portsel = ppd->port == 1 ? portsel_port1 : portsel_port2;
		eपंचांग = ateपंचांग_1port;
	पूर्ण अन्यथा अणु
		portsel = portsel_2port;
		eपंचांग = ateपंचांग_2port;
	पूर्ण

	अगर (qib_r_grab(dd) < 0 ||
		qib_r_shअगरt(dd, BISTEN_ETM, LEN_ETM, reset_ateपंचांग, शून्य) < 0 ||
		qib_r_update(dd, BISTEN_ETM) < 0 ||
		qib_r_shअगरt(dd, BISTEN_AT, LEN_AT, reset_at, शून्य) < 0 ||
		qib_r_update(dd, BISTEN_AT) < 0 ||
		qib_r_shअगरt(dd, BISTEN_PORT_SEL, LEN_PORT_SEL,
			    portsel, शून्य) < 0 ||
		qib_r_update(dd, BISTEN_PORT_SEL) < 0 ||
		qib_r_shअगरt(dd, BISTEN_AT, LEN_AT, at, शून्य) < 0 ||
		qib_r_update(dd, BISTEN_AT) < 0 ||
		qib_r_shअगरt(dd, BISTEN_ETM, LEN_ETM, eपंचांग, शून्य) < 0 ||
		qib_r_update(dd, BISTEN_ETM) < 0)
		qib_dev_err(dd, "Failed IB link recovery setup\n");
पूर्ण

अटल व्योम check_7322_rxe_status(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 fmask;

	अगर (dd->cspec->recovery_ports_initted != 1)
		वापस; /* rest करोesn't apply to dualport */
	qib_ग_लिखो_kreg(dd, kr_control, dd->control |
		       SYM_MASK(Control, FreezeMode));
	(व्योम)qib_पढ़ो_kreg64(dd, kr_scratch);
	udelay(3); /* ibcreset निश्चितed 400ns, be sure that's over */
	fmask = qib_पढ़ो_kreg64(dd, kr_act_fmask);
	अगर (!fmask) अणु
		/*
		 * require a घातercycle beक्रमe we'll work again, and make
		 * sure we get no more पूर्णांकerrupts, and करोn't turn off
		 * मुक्तze.
		 */
		ppd->dd->cspec->stay_in_मुक्तze = 1;
		qib_7322_set_पूर्णांकr_state(ppd->dd, 0);
		qib_ग_लिखो_kreg(dd, kr_fmask, 0ULL);
		qib_dev_err(dd, "HCA unusable until powercycled\n");
		वापस; /* eventually reset */
	पूर्ण

	qib_ग_लिखो_kreg(ppd->dd, kr_hwerrclear,
	    SYM_MASK(HwErrClear, IBSerdesPClkNotDetectClear_1));

	/* करोn't करो the full clear_मुक्तze(), not needed क्रम this */
	qib_ग_लिखो_kreg(dd, kr_control, dd->control);
	qib_पढ़ो_kreg32(dd, kr_scratch);
	/* take IBC out of reset */
	अगर (ppd->link_speed_supported) अणु
		ppd->cpspec->ibcctrl_a &=
			~SYM_MASK(IBCCtrlA_0, IBStatIntReductionEn);
		qib_ग_लिखो_kreg_port(ppd, krp_ibcctrl_a,
				    ppd->cpspec->ibcctrl_a);
		qib_पढ़ो_kreg32(dd, kr_scratch);
		अगर (ppd->lflags & QIBL_IB_LINK_DISABLED)
			qib_set_ib_7322_lstate(ppd, 0,
				QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);
	पूर्ण
पूर्ण
