<शैली गुरु>
/*
 * Copyright (c) 2013 - 2017 Intel Corporation. All rights reserved.
 * Copyright (c) 2006, 2007, 2008, 2009, 2010 QLogic Corporation.
 * All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
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
 * QLogic_IB 6120 PCIe chip.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "qib.h"
#समावेश "qib_6120_regs.h"

अटल व्योम qib_6120_setup_setextled(काष्ठा qib_pportdata *, u32);
अटल व्योम sendctrl_6120_mod(काष्ठा qib_pportdata *ppd, u32 op);
अटल u8 qib_6120_phys_portstate(u64);
अटल u32 qib_6120_iblink_state(u64);

/*
 * This file contains all the chip-specअगरic रेजिस्टर inक्रमmation and
 * access functions क्रम the Intel Intel_IB PCI-Express chip.
 *
 */

/* KREG_IDX uses machine-generated #घोषणाs */
#घोषणा KREG_IDX(regname) (QIB_6120_##regname##_OFFS / माप(u64))

/* Use defines to tie machine-generated names to lower-हाल names */
#घोषणा kr_extctrl KREG_IDX(EXTCtrl)
#घोषणा kr_extstatus KREG_IDX(EXTStatus)
#घोषणा kr_gpio_clear KREG_IDX(GPIOClear)
#घोषणा kr_gpio_mask KREG_IDX(GPIOMask)
#घोषणा kr_gpio_out KREG_IDX(GPIOOut)
#घोषणा kr_gpio_status KREG_IDX(GPIOStatus)
#घोषणा kr_rcvctrl KREG_IDX(RcvCtrl)
#घोषणा kr_sendctrl KREG_IDX(SendCtrl)
#घोषणा kr_partitionkey KREG_IDX(RcvPartitionKey)
#घोषणा kr_hwdiagctrl KREG_IDX(HwDiagCtrl)
#घोषणा kr_ibcstatus KREG_IDX(IBCStatus)
#घोषणा kr_ibcctrl KREG_IDX(IBCCtrl)
#घोषणा kr_sendbuffererror KREG_IDX(SendBufErr0)
#घोषणा kr_rcvbthqp KREG_IDX(RcvBTHQP)
#घोषणा kr_counterregbase KREG_IDX(CntrRegBase)
#घोषणा kr_palign KREG_IDX(PageAlign)
#घोषणा kr_rcvegrbase KREG_IDX(RcvEgrBase)
#घोषणा kr_rcvegrcnt KREG_IDX(RcvEgrCnt)
#घोषणा kr_rcvhdrcnt KREG_IDX(RcvHdrCnt)
#घोषणा kr_rcvhdrentsize KREG_IDX(RcvHdrEntSize)
#घोषणा kr_rcvhdrsize KREG_IDX(RcvHdrSize)
#घोषणा kr_rcvtidbase KREG_IDX(RcvTIDBase)
#घोषणा kr_rcvtidcnt KREG_IDX(RcvTIDCnt)
#घोषणा kr_scratch KREG_IDX(Scratch)
#घोषणा kr_sendctrl KREG_IDX(SendCtrl)
#घोषणा kr_sendpioavailaddr KREG_IDX(SendPIOAvailAddr)
#घोषणा kr_sendpiobufbase KREG_IDX(SendPIOBufBase)
#घोषणा kr_sendpiobufcnt KREG_IDX(SendPIOBufCnt)
#घोषणा kr_sendpiosize KREG_IDX(SendPIOSize)
#घोषणा kr_sendregbase KREG_IDX(SendRegBase)
#घोषणा kr_userregbase KREG_IDX(UserRegBase)
#घोषणा kr_control KREG_IDX(Control)
#घोषणा kr_पूर्णांकclear KREG_IDX(IntClear)
#घोषणा kr_पूर्णांकmask KREG_IDX(IntMask)
#घोषणा kr_पूर्णांकstatus KREG_IDX(IntStatus)
#घोषणा kr_errclear KREG_IDX(ErrClear)
#घोषणा kr_errmask KREG_IDX(ErrMask)
#घोषणा kr_errstatus KREG_IDX(ErrStatus)
#घोषणा kr_hwerrclear KREG_IDX(HwErrClear)
#घोषणा kr_hwerrmask KREG_IDX(HwErrMask)
#घोषणा kr_hwerrstatus KREG_IDX(HwErrStatus)
#घोषणा kr_revision KREG_IDX(Revision)
#घोषणा kr_portcnt KREG_IDX(PortCnt)
#घोषणा kr_serdes_cfg0 KREG_IDX(SerdesCfg0)
#घोषणा kr_serdes_cfg1 (kr_serdes_cfg0 + 1)
#घोषणा kr_serdes_stat KREG_IDX(SerdesStat)
#घोषणा kr_xgxs_cfg KREG_IDX(XGXSCfg)

/* These must only be written via qib_ग_लिखो_kreg_ctxt() */
#घोषणा kr_rcvhdraddr KREG_IDX(RcvHdrAddr0)
#घोषणा kr_rcvhdrtailaddr KREG_IDX(RcvHdrTailAddr0)

#घोषणा CREG_IDX(regname) ((QIB_6120_##regname##_OFFS - \
			QIB_6120_LBIntCnt_OFFS) / माप(u64))

#घोषणा cr_badक्रमmat CREG_IDX(RxBadFormatCnt)
#घोषणा cr_erricrc CREG_IDX(RxICRCErrCnt)
#घोषणा cr_errlink CREG_IDX(RxLinkProblemCnt)
#घोषणा cr_errlpcrc CREG_IDX(RxLPCRCErrCnt)
#घोषणा cr_errpkey CREG_IDX(RxPKeyMismatchCnt)
#घोषणा cr_rcvflowctrl_err CREG_IDX(RxFlowCtrlErrCnt)
#घोषणा cr_err_rlen CREG_IDX(RxLenErrCnt)
#घोषणा cr_errslen CREG_IDX(TxLenErrCnt)
#घोषणा cr_errtidfull CREG_IDX(RxTIDFullErrCnt)
#घोषणा cr_errtidvalid CREG_IDX(RxTIDValidErrCnt)
#घोषणा cr_errvcrc CREG_IDX(RxVCRCErrCnt)
#घोषणा cr_ibstatuschange CREG_IDX(IBStatusChangeCnt)
#घोषणा cr_lbपूर्णांक CREG_IDX(LBIntCnt)
#घोषणा cr_invalidrlen CREG_IDX(RxMaxMinLenErrCnt)
#घोषणा cr_invalidslen CREG_IDX(TxMaxMinLenErrCnt)
#घोषणा cr_lbflowstall CREG_IDX(LBFlowStallCnt)
#घोषणा cr_pktrcv CREG_IDX(RxDataPktCnt)
#घोषणा cr_pktrcvflowctrl CREG_IDX(RxFlowPktCnt)
#घोषणा cr_pktsend CREG_IDX(TxDataPktCnt)
#घोषणा cr_pktsendflow CREG_IDX(TxFlowPktCnt)
#घोषणा cr_portovfl CREG_IDX(RxP0HdrEgrOvflCnt)
#घोषणा cr_rcvebp CREG_IDX(RxEBPCnt)
#घोषणा cr_rcvovfl CREG_IDX(RxBufOvflCnt)
#घोषणा cr_senddropped CREG_IDX(TxDroppedPktCnt)
#घोषणा cr_sendstall CREG_IDX(TxFlowStallCnt)
#घोषणा cr_sendunderrun CREG_IDX(TxUnderrunCnt)
#घोषणा cr_wordrcv CREG_IDX(RxDwordCnt)
#घोषणा cr_wordsend CREG_IDX(TxDwordCnt)
#घोषणा cr_txunsupvl CREG_IDX(TxUnsupVLErrCnt)
#घोषणा cr_rxdroppkt CREG_IDX(RxDroppedPktCnt)
#घोषणा cr_iblinkerrrecov CREG_IDX(IBLinkErrRecoveryCnt)
#घोषणा cr_iblinkकरोwn CREG_IDX(IBLinkDownedCnt)
#घोषणा cr_ibsymbolerr CREG_IDX(IBSymbolErrCnt)

#घोषणा SYM_RMASK(regname, fldname) ((u64)              \
	QIB_6120_##regname##_##fldname##_RMASK)
#घोषणा SYM_MASK(regname, fldname) ((u64)               \
	QIB_6120_##regname##_##fldname##_RMASK <<       \
	 QIB_6120_##regname##_##fldname##_LSB)
#घोषणा SYM_LSB(regname, fldname) (QIB_6120_##regname##_##fldname##_LSB)

#घोषणा SYM_FIELD(value, regname, fldname) ((u64) \
	(((value) >> SYM_LSB(regname, fldname)) & \
	 SYM_RMASK(regname, fldname)))
#घोषणा ERR_MASK(fldname) SYM_MASK(ErrMask, fldname##Mask)
#घोषणा HWE_MASK(fldname) SYM_MASK(HwErrMask, fldname##Mask)

/* link training states, from IBC */
#घोषणा IB_6120_LT_STATE_DISABLED        0x00
#घोषणा IB_6120_LT_STATE_LINKUP          0x01
#घोषणा IB_6120_LT_STATE_POLLACTIVE      0x02
#घोषणा IB_6120_LT_STATE_POLLQUIET       0x03
#घोषणा IB_6120_LT_STATE_SLEEPDELAY      0x04
#घोषणा IB_6120_LT_STATE_SLEEPQUIET      0x05
#घोषणा IB_6120_LT_STATE_CFGDEBOUNCE     0x08
#घोषणा IB_6120_LT_STATE_CFGRCVFCFG      0x09
#घोषणा IB_6120_LT_STATE_CFGWAITRMT      0x0a
#घोषणा IB_6120_LT_STATE_CFGIDLE 0x0b
#घोषणा IB_6120_LT_STATE_RECOVERRETRAIN  0x0c
#घोषणा IB_6120_LT_STATE_RECOVERWAITRMT  0x0e
#घोषणा IB_6120_LT_STATE_RECOVERIDLE     0x0f

/* link state machine states from IBC */
#घोषणा IB_6120_L_STATE_DOWN             0x0
#घोषणा IB_6120_L_STATE_INIT             0x1
#घोषणा IB_6120_L_STATE_ARM              0x2
#घोषणा IB_6120_L_STATE_ACTIVE           0x3
#घोषणा IB_6120_L_STATE_ACT_DEFER        0x4

अटल स्थिर u8 qib_6120_physportstate[0x20] = अणु
	[IB_6120_LT_STATE_DISABLED] = IB_PHYSPORTSTATE_DISABLED,
	[IB_6120_LT_STATE_LINKUP] = IB_PHYSPORTSTATE_LINKUP,
	[IB_6120_LT_STATE_POLLACTIVE] = IB_PHYSPORTSTATE_POLL,
	[IB_6120_LT_STATE_POLLQUIET] = IB_PHYSPORTSTATE_POLL,
	[IB_6120_LT_STATE_SLEEPDELAY] = IB_PHYSPORTSTATE_SLEEP,
	[IB_6120_LT_STATE_SLEEPQUIET] = IB_PHYSPORTSTATE_SLEEP,
	[IB_6120_LT_STATE_CFGDEBOUNCE] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_6120_LT_STATE_CFGRCVFCFG] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_6120_LT_STATE_CFGWAITRMT] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_6120_LT_STATE_CFGIDLE] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_6120_LT_STATE_RECOVERRETRAIN] =
		IB_PHYSPORTSTATE_LINK_ERR_RECOVER,
	[IB_6120_LT_STATE_RECOVERWAITRMT] =
		IB_PHYSPORTSTATE_LINK_ERR_RECOVER,
	[IB_6120_LT_STATE_RECOVERIDLE] =
		IB_PHYSPORTSTATE_LINK_ERR_RECOVER,
	[0x10] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x11] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x12] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x13] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x14] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x15] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x16] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[0x17] = IB_PHYSPORTSTATE_CFG_TRAIN
पूर्ण;


काष्ठा qib_chip_specअगरic अणु
	u64 __iomem *cregbase;
	u64 *cntrs;
	u64 *portcntrs;
	व्योम *dummy_hdrq;   /* used after ctxt बंद */
	dma_addr_t dummy_hdrq_phys;
	spinlock_t kernel_tid_lock; /* no back to back kernel TID ग_लिखोs */
	spinlock_t user_tid_lock; /* no back to back user TID ग_लिखोs */
	spinlock_t rcvmod_lock; /* protect rcvctrl shaकरोw changes */
	spinlock_t gpio_lock; /* RMW of shaकरोws/regs क्रम ExtCtrl and GPIO */
	u64 hwerrmask;
	u64 errormask;
	u64 gpio_out; /* shaकरोw of kr_gpio_out, क्रम rmw ops */
	u64 gpio_mask; /* shaकरोw the gpio mask रेजिस्टर */
	u64 extctrl; /* shaकरोw the gpio output enable, etc... */
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
	u64 ibcctrl; /* shaकरोw क्रम kr_ibcctrl */
	u32 lastlinkrecov; /* link recovery issue */
	u32 cntrnamelen;
	u32 portcntrnamelen;
	u32 ncntrs;
	u32 nportcntrs;
	/* used with gpio पूर्णांकerrupts to implement IB counters */
	u32 rxfc_unsupvl_errs;
	u32 overrun_thresh_errs;
	/*
	 * these count only हालs where _successive_ LocalLinkIntegrity
	 * errors were seen in the receive headers of IB standard packets
	 */
	u32 lli_errs;
	u32 lli_counter;
	u64 lli_thresh;
	u64 sword; /* total dwords sent (sample result) */
	u64 rword; /* total dwords received (sample result) */
	u64 spkts; /* total packets sent (sample result) */
	u64 rpkts; /* total packets received (sample result) */
	u64 xmit_रुको; /* # of ticks no data sent (sample result) */
	काष्ठा समयr_list pma_समयr;
	काष्ठा qib_pportdata *ppd;
	अक्षर emsgbuf[128];
	अक्षर bitsmsgbuf[64];
	u8 pma_sample_status;
पूर्ण;

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
#घोषणा QLOGIC_IB_IBCC_LINKCMD_SHIFT 18

/*
 * We could have a single रेजिस्टर get/put routine, that takes a group type,
 * but this is somewhat clearer and cleaner.  It also gives us some error
 * checking.  64 bit रेजिस्टर पढ़ोs should always work, but are inefficient
 * on opteron (the northbridge always generates 2 separate HT 32 bit पढ़ोs),
 * so we use kreg32 wherever possible.  User रेजिस्टर and counter रेजिस्टर
 * पढ़ोs are always 32 bit पढ़ोs, so only one क्रमm of those routines.
 */

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

	अगर (dd->userbase)
		वापस पढ़ोl(regno + (u64 __iomem *)
			     ((अक्षर __iomem *)dd->userbase +
			      dd->ureg_align * ctxt));
	अन्यथा
		वापस पढ़ोl(regno + (u64 __iomem *)
			     (dd->uregbase +
			      (अक्षर __iomem *)dd->kregbase +
			      dd->ureg_align * ctxt));
पूर्ण

/**
 * qib_ग_लिखो_ureg - ग_लिखो 32-bit भवized per-context रेजिस्टर
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
				  स्थिर u16 regno)
अणु
	अगर (!dd->kregbase || !(dd->flags & QIB_PRESENT))
		वापस -1;
	वापस पढ़ोl((u32 __iomem *)&dd->kregbase[regno]);
पूर्ण

अटल अंतरभूत u64 qib_पढ़ो_kreg64(स्थिर काष्ठा qib_devdata *dd,
				  स्थिर u16 regno)
अणु
	अगर (!dd->kregbase || !(dd->flags & QIB_PRESENT))
		वापस -1;

	वापस पढ़ोq(&dd->kregbase[regno]);
पूर्ण

अटल अंतरभूत व्योम qib_ग_लिखो_kreg(स्थिर काष्ठा qib_devdata *dd,
				  स्थिर u16 regno, u64 value)
अणु
	अगर (dd->kregbase && (dd->flags & QIB_PRESENT))
		ग_लिखोq(value, &dd->kregbase[regno]);
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

अटल अंतरभूत व्योम ग_लिखो_6120_creg(स्थिर काष्ठा qib_devdata *dd,
				   u16 regno, u64 value)
अणु
	अगर (dd->cspec->cregbase && (dd->flags & QIB_PRESENT))
		ग_लिखोq(value, &dd->cspec->cregbase[regno]);
पूर्ण

अटल अंतरभूत u64 पढ़ो_6120_creg(स्थिर काष्ठा qib_devdata *dd, u16 regno)
अणु
	अगर (!dd->cspec->cregbase || !(dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोq(&dd->cspec->cregbase[regno]);
पूर्ण

अटल अंतरभूत u32 पढ़ो_6120_creg32(स्थिर काष्ठा qib_devdata *dd, u16 regno)
अणु
	अगर (!dd->cspec->cregbase || !(dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोl(&dd->cspec->cregbase[regno]);
पूर्ण

/* kr_control bits */
#घोषणा QLOGIC_IB_C_RESET 1U

/* kr_पूर्णांकstatus, kr_पूर्णांकclear, kr_पूर्णांकmask bits */
#घोषणा QLOGIC_IB_I_RCVURG_MASK ((1U << 5) - 1)
#घोषणा QLOGIC_IB_I_RCVURG_SHIFT 0
#घोषणा QLOGIC_IB_I_RCVAVAIL_MASK ((1U << 5) - 1)
#घोषणा QLOGIC_IB_I_RCVAVAIL_SHIFT 12

#घोषणा QLOGIC_IB_C_FREEZEMODE 0x00000002
#घोषणा QLOGIC_IB_C_LINKENABLE 0x00000004
#घोषणा QLOGIC_IB_I_ERROR               0x0000000080000000ULL
#घोषणा QLOGIC_IB_I_SPIOSENT            0x0000000040000000ULL
#घोषणा QLOGIC_IB_I_SPIOBUFAVAIL        0x0000000020000000ULL
#घोषणा QLOGIC_IB_I_GPIO                0x0000000010000000ULL
#घोषणा QLOGIC_IB_I_BITSEXTANT \
		((QLOGIC_IB_I_RCVURG_MASK << QLOGIC_IB_I_RCVURG_SHIFT) | \
		(QLOGIC_IB_I_RCVAVAIL_MASK << \
		 QLOGIC_IB_I_RCVAVAIL_SHIFT) | \
		QLOGIC_IB_I_ERROR | QLOGIC_IB_I_SPIOSENT | \
		QLOGIC_IB_I_SPIOBUFAVAIL | QLOGIC_IB_I_GPIO)

/* kr_hwerrclear, kr_hwerrmask, kr_hwerrstatus, bits */
#घोषणा QLOGIC_IB_HWE_PCIEMEMPARITYERR_MASK  0x000000000000003fULL
#घोषणा QLOGIC_IB_HWE_PCIEMEMPARITYERR_SHIFT 0
#घोषणा QLOGIC_IB_HWE_PCIEPOISONEDTLP      0x0000000010000000ULL
#घोषणा QLOGIC_IB_HWE_PCIECPLTIMEOUT       0x0000000020000000ULL
#घोषणा QLOGIC_IB_HWE_PCIEBUSPARITYXTLH    0x0000000040000000ULL
#घोषणा QLOGIC_IB_HWE_PCIEBUSPARITYXADM    0x0000000080000000ULL
#घोषणा QLOGIC_IB_HWE_PCIEBUSPARITYRADM    0x0000000100000000ULL
#घोषणा QLOGIC_IB_HWE_COREPLL_FBSLIP       0x0080000000000000ULL
#घोषणा QLOGIC_IB_HWE_COREPLL_RFSLIP       0x0100000000000000ULL
#घोषणा QLOGIC_IB_HWE_PCIE1PLLFAILED       0x0400000000000000ULL
#घोषणा QLOGIC_IB_HWE_PCIE0PLLFAILED       0x0800000000000000ULL
#घोषणा QLOGIC_IB_HWE_SERDESPLLFAILED      0x1000000000000000ULL


/* kr_extstatus bits */
#घोषणा QLOGIC_IB_EXTS_FREQSEL 0x2
#घोषणा QLOGIC_IB_EXTS_SERDESSEL 0x4
#घोषणा QLOGIC_IB_EXTS_MEMBIST_ENDTEST     0x0000000000004000
#घोषणा QLOGIC_IB_EXTS_MEMBIST_FOUND       0x0000000000008000

/* kr_xgxsconfig bits */
#घोषणा QLOGIC_IB_XGXS_RESET          0x5ULL

#घोषणा _QIB_GPIO_SDA_NUM 1
#घोषणा _QIB_GPIO_SCL_NUM 0

/* Bits in GPIO क्रम the added IB link पूर्णांकerrupts */
#घोषणा GPIO_RXUVL_BIT 3
#घोषणा GPIO_OVRUN_BIT 4
#घोषणा GPIO_LLI_BIT 5
#घोषणा GPIO_ERRINTR_MASK 0x38


#घोषणा QLOGIC_IB_RT_बफ_मानE_MASK 0xe0000000ULL
#घोषणा QLOGIC_IB_RT_बफ_मानE_SHIFTVAL(tid) \
	((((tid) & QLOGIC_IB_RT_बफ_मानE_MASK) >> 29) + 11 - 1)
#घोषणा QLOGIC_IB_RT_बफ_मानE(tid) (1 << QLOGIC_IB_RT_बफ_मानE_SHIFTVAL(tid))
#घोषणा QLOGIC_IB_RT_IS_VALID(tid) \
	(((tid) & QLOGIC_IB_RT_बफ_मानE_MASK) && \
	 ((((tid) & QLOGIC_IB_RT_बफ_मानE_MASK) != QLOGIC_IB_RT_बफ_मानE_MASK)))
#घोषणा QLOGIC_IB_RT_ADDR_MASK 0x1FFFFFFFULL /* 29 bits valid */
#घोषणा QLOGIC_IB_RT_ADDR_SHIFT 10

#घोषणा QLOGIC_IB_R_INTRAVAIL_SHIFT 16
#घोषणा QLOGIC_IB_R_TAILUPD_SHIFT 31
#घोषणा IBA6120_R_PKEY_DIS_SHIFT 30

#घोषणा PBC_6120_VL15_SEND_CTRL (1ULL << 31) /* pbc; VL15; link_buf only */

#घोषणा IBCBUSFRSPCPARITYERR HWE_MASK(IBCBusFromSPCParityErr)
#घोषणा IBCBUSTOSPCPARITYERR HWE_MASK(IBCBusToSPCParityErr)

#घोषणा SYM_MASK_BIT(regname, fldname, bit) ((u64) \
	((1ULL << (SYM_LSB(regname, fldname) + (bit)))))

#घोषणा TXEMEMPARITYERR_PIOBUF \
	SYM_MASK_BIT(HwErrMask, TXEMemParityErrMask, 0)
#घोषणा TXEMEMPARITYERR_PIOPBC \
	SYM_MASK_BIT(HwErrMask, TXEMemParityErrMask, 1)
#घोषणा TXEMEMPARITYERR_PIOLAUNCHFIFO \
	SYM_MASK_BIT(HwErrMask, TXEMemParityErrMask, 2)

#घोषणा RXEMEMPARITYERR_RCVBUF \
	SYM_MASK_BIT(HwErrMask, RXEMemParityErrMask, 0)
#घोषणा RXEMEMPARITYERR_LOOKUPQ \
	SYM_MASK_BIT(HwErrMask, RXEMemParityErrMask, 1)
#घोषणा RXEMEMPARITYERR_EXPTID \
	SYM_MASK_BIT(HwErrMask, RXEMemParityErrMask, 2)
#घोषणा RXEMEMPARITYERR_EAGERTID \
	SYM_MASK_BIT(HwErrMask, RXEMemParityErrMask, 3)
#घोषणा RXEMEMPARITYERR_FLAGBUF \
	SYM_MASK_BIT(HwErrMask, RXEMemParityErrMask, 4)
#घोषणा RXEMEMPARITYERR_DATAINFO \
	SYM_MASK_BIT(HwErrMask, RXEMemParityErrMask, 5)
#घोषणा RXEMEMPARITYERR_HDRINFO \
	SYM_MASK_BIT(HwErrMask, RXEMemParityErrMask, 6)

/* 6120 specअगरic hardware errors... */
अटल स्थिर काष्ठा qib_hwerror_msgs qib_6120_hwerror_msgs[] = अणु
	/* generic hardware errors */
	QLOGIC_IB_HWE_MSG(IBCBUSFRSPCPARITYERR, "QIB2IB Parity"),
	QLOGIC_IB_HWE_MSG(IBCBUSTOSPCPARITYERR, "IB2QIB Parity"),

	QLOGIC_IB_HWE_MSG(TXEMEMPARITYERR_PIOBUF,
			  "TXE PIOBUF Memory Parity"),
	QLOGIC_IB_HWE_MSG(TXEMEMPARITYERR_PIOPBC,
			  "TXE PIOPBC Memory Parity"),
	QLOGIC_IB_HWE_MSG(TXEMEMPARITYERR_PIOLAUNCHFIFO,
			  "TXE PIOLAUNCHFIFO Memory Parity"),

	QLOGIC_IB_HWE_MSG(RXEMEMPARITYERR_RCVBUF,
			  "RXE RCVBUF Memory Parity"),
	QLOGIC_IB_HWE_MSG(RXEMEMPARITYERR_LOOKUPQ,
			  "RXE LOOKUPQ Memory Parity"),
	QLOGIC_IB_HWE_MSG(RXEMEMPARITYERR_EAGERTID,
			  "RXE EAGERTID Memory Parity"),
	QLOGIC_IB_HWE_MSG(RXEMEMPARITYERR_EXPTID,
			  "RXE EXPTID Memory Parity"),
	QLOGIC_IB_HWE_MSG(RXEMEMPARITYERR_FLAGBUF,
			  "RXE FLAGBUF Memory Parity"),
	QLOGIC_IB_HWE_MSG(RXEMEMPARITYERR_DATAINFO,
			  "RXE DATAINFO Memory Parity"),
	QLOGIC_IB_HWE_MSG(RXEMEMPARITYERR_HDRINFO,
			  "RXE HDRINFO Memory Parity"),

	/* chip-specअगरic hardware errors */
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIEPOISONEDTLP,
			  "PCIe Poisoned TLP"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIECPLTIMEOUT,
			  "PCIe completion timeout"),
	/*
	 * In practice, it's unlikely wthat we'll see PCIe PLL, or bus
	 * parity or memory parity error failures, because most likely we
	 * won't be able to talk to the core of the chip.  Nonetheless, we
	 * might see them, अगर they are in parts of the PCIe core that aren't
	 * essential.
	 */
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIE1PLLFAILED,
			  "PCIePLL1"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIE0PLLFAILED,
			  "PCIePLL0"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIEBUSPARITYXTLH,
			  "PCIe XTLH core parity"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIEBUSPARITYXADM,
			  "PCIe ADM TX core parity"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIEBUSPARITYRADM,
			  "PCIe ADM RX core parity"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_SERDESPLLFAILED,
			  "SerDes PLL"),
पूर्ण;

#घोषणा TXE_PIO_PARITY (TXEMEMPARITYERR_PIOBUF | TXEMEMPARITYERR_PIOPBC)
#घोषणा _QIB_PLL_FAIL (QLOGIC_IB_HWE_COREPLL_FBSLIP |   \
		QLOGIC_IB_HWE_COREPLL_RFSLIP)

	/* variables क्रम sanity checking पूर्णांकerrupt and errors */
#घोषणा IB_HWE_BITSEXTANT \
	(HWE_MASK(RXEMemParityErr) |					\
	 HWE_MASK(TXEMemParityErr) |					\
	 (QLOGIC_IB_HWE_PCIEMEMPARITYERR_MASK <<			\
	  QLOGIC_IB_HWE_PCIEMEMPARITYERR_SHIFT) |			\
	 QLOGIC_IB_HWE_PCIE1PLLFAILED |					\
	 QLOGIC_IB_HWE_PCIE0PLLFAILED |					\
	 QLOGIC_IB_HWE_PCIEPOISONEDTLP |				\
	 QLOGIC_IB_HWE_PCIECPLTIMEOUT |					\
	 QLOGIC_IB_HWE_PCIEBUSPARITYXTLH |				\
	 QLOGIC_IB_HWE_PCIEBUSPARITYXADM |				\
	 QLOGIC_IB_HWE_PCIEBUSPARITYRADM |				\
	 HWE_MASK(PowerOnBISTFailed) |					\
	 QLOGIC_IB_HWE_COREPLL_FBSLIP |					\
	 QLOGIC_IB_HWE_COREPLL_RFSLIP |					\
	 QLOGIC_IB_HWE_SERDESPLLFAILED |				\
	 HWE_MASK(IBCBusToSPCParityErr) |				\
	 HWE_MASK(IBCBusFromSPCParityErr))

#घोषणा IB_E_BITSEXTANT \
	(ERR_MASK(RcvFormatErr) | ERR_MASK(RcvVCRCErr) |		\
	 ERR_MASK(RcvICRCErr) | ERR_MASK(RcvMinPktLenErr) |		\
	 ERR_MASK(RcvMaxPktLenErr) | ERR_MASK(RcvLongPktLenErr) |	\
	 ERR_MASK(RcvShortPktLenErr) | ERR_MASK(RcvUnexpectedCharErr) | \
	 ERR_MASK(RcvUnsupportedVLErr) | ERR_MASK(RcvEBPErr) |		\
	 ERR_MASK(RcvIBFlowErr) | ERR_MASK(RcvBadVersionErr) |		\
	 ERR_MASK(RcvEgrFullErr) | ERR_MASK(RcvHdrFullErr) |		\
	 ERR_MASK(RcvBadTidErr) | ERR_MASK(RcvHdrLenErr) |		\
	 ERR_MASK(RcvHdrErr) | ERR_MASK(RcvIBLostLinkErr) |		\
	 ERR_MASK(SendMinPktLenErr) | ERR_MASK(SendMaxPktLenErr) |	\
	 ERR_MASK(SendUnderRunErr) | ERR_MASK(SendPktLenErr) |		\
	 ERR_MASK(SendDroppedSmpPktErr) |				\
	 ERR_MASK(SendDroppedDataPktErr) |				\
	 ERR_MASK(SendPioArmLaunchErr) |				\
	 ERR_MASK(SendUnexpectedPktNumErr) |				\
	 ERR_MASK(SendUnsupportedVLErr) | ERR_MASK(IBStatusChanged) |	\
	 ERR_MASK(InvalidAddrErr) | ERR_MASK(ResetNegated) |		\
	 ERR_MASK(HardwareErr))

#घोषणा QLOGIC_IB_E_PKTERRS ( \
		ERR_MASK(SendPktLenErr) |				\
		ERR_MASK(SendDroppedDataPktErr) |			\
		ERR_MASK(RcvVCRCErr) |					\
		ERR_MASK(RcvICRCErr) |					\
		ERR_MASK(RcvShortPktLenErr) |				\
		ERR_MASK(RcvEBPErr))

/* These are all rcv-related errors which we want to count क्रम stats */
#घोषणा E_SUM_PKTERRS						\
	(ERR_MASK(RcvHdrLenErr) | ERR_MASK(RcvBadTidErr) |		\
	 ERR_MASK(RcvBadVersionErr) | ERR_MASK(RcvHdrErr) |		\
	 ERR_MASK(RcvLongPktLenErr) | ERR_MASK(RcvShortPktLenErr) |	\
	 ERR_MASK(RcvMaxPktLenErr) | ERR_MASK(RcvMinPktLenErr) |	\
	 ERR_MASK(RcvFormatErr) | ERR_MASK(RcvUnsupportedVLErr) |	\
	 ERR_MASK(RcvUnexpectedCharErr) | ERR_MASK(RcvEBPErr))

/* These are all send-related errors which we want to count क्रम stats */
#घोषणा E_SUM_ERRS							\
	(ERR_MASK(SendPioArmLaunchErr) |				\
	 ERR_MASK(SendUnexpectedPktNumErr) |				\
	 ERR_MASK(SendDroppedDataPktErr) |				\
	 ERR_MASK(SendDroppedSmpPktErr) |				\
	 ERR_MASK(SendMaxPktLenErr) | ERR_MASK(SendUnsupportedVLErr) |	\
	 ERR_MASK(SendMinPktLenErr) | ERR_MASK(SendPktLenErr) |		\
	 ERR_MASK(InvalidAddrErr))

/*
 * this is similar to E_SUM_ERRS, but can't ignore armlaunch, don't ignore
 * errors not related to मुक्तze and cancelling buffers.  Can't ignore
 * armlaunch because could get more जबतक still cleaning up, and need
 * to cancel those as they happen.
 */
#घोषणा E_SPKT_ERRS_IGNORE \
	(ERR_MASK(SendDroppedDataPktErr) |				\
	 ERR_MASK(SendDroppedSmpPktErr) |				\
	 ERR_MASK(SendMaxPktLenErr) | ERR_MASK(SendMinPktLenErr) |	\
	 ERR_MASK(SendPktLenErr))

/*
 * these are errors that can occur when the link changes state जबतक
 * a packet is being sent or received.  This करोesn't cover things
 * like EBP or VCRC that can be the result of a sending having the
 * link change state, so we receive a "known bad" packet.
 */
#घोषणा E_SUM_LINK_PKTERRS		\
	(ERR_MASK(SendDroppedDataPktErr) |				\
	 ERR_MASK(SendDroppedSmpPktErr) |				\
	 ERR_MASK(SendMinPktLenErr) | ERR_MASK(SendPktLenErr) |		\
	 ERR_MASK(RcvShortPktLenErr) | ERR_MASK(RcvMinPktLenErr) |	\
	 ERR_MASK(RcvUnexpectedCharErr))

अटल व्योम qib_6120_put_tid_2(काष्ठा qib_devdata *, u64 __iomem *,
			       u32, अचिन्हित दीर्घ);

/*
 * On platक्रमms using this chip, and not having ordered WC stores, we
 * can get TXE parity errors due to speculative पढ़ोs to the PIO buffers,
 * and this, due to a chip issue can result in (many) false parity error
 * reports.  So it's a debug prपूर्णांक on those, and an info prपूर्णांक on प्रणालीs
 * where the speculative पढ़ोs करोn't occur.
 */
अटल व्योम qib_6120_txe_recover(काष्ठा qib_devdata *dd)
अणु
	अगर (!qib_unordered_wc())
		qib_devinfo(dd->pcidev,
			    "Recovering from TXE PIO parity error\n");
पूर्ण

/* enable/disable chip from delivering पूर्णांकerrupts */
अटल व्योम qib_6120_set_पूर्णांकr_state(काष्ठा qib_devdata *dd, u32 enable)
अणु
	अगर (enable) अणु
		अगर (dd->flags & QIB_BADINTR)
			वापस;
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकmask, ~0ULL);
		/* क्रमce re-पूर्णांकerrupt of any pending पूर्णांकerrupts. */
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, 0ULL);
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
 * even though the details are similar on most chips
 */
अटल व्योम qib_6120_clear_मुक्तze(काष्ठा qib_devdata *dd)
अणु
	/* disable error पूर्णांकerrupts, to aव्योम confusion */
	qib_ग_लिखो_kreg(dd, kr_errmask, 0ULL);

	/* also disable पूर्णांकerrupts; errormask is someबार overwritten */
	qib_6120_set_पूर्णांकr_state(dd, 0);

	qib_cancel_sends(dd->pport);

	/* clear the मुक्तze, and be sure chip saw it */
	qib_ग_लिखो_kreg(dd, kr_control, dd->control);
	qib_पढ़ो_kreg32(dd, kr_scratch);

	/* क्रमce in-memory update now we are out of मुक्तze */
	qib_क्रमce_pio_avail_update(dd);

	/*
	 * क्रमce new पूर्णांकerrupt अगर any hwerr, error or पूर्णांकerrupt bits are
	 * still set, and clear "safe" send packet errors related to मुक्तze
	 * and cancelling sends.  Re-enable error पूर्णांकerrupts beक्रमe possible
	 * क्रमce of re-पूर्णांकerrupt on pending पूर्णांकerrupts.
	 */
	qib_ग_लिखो_kreg(dd, kr_hwerrclear, 0ULL);
	qib_ग_लिखो_kreg(dd, kr_errclear, E_SPKT_ERRS_IGNORE);
	qib_ग_लिखो_kreg(dd, kr_errmask, dd->cspec->errormask);
	qib_6120_set_पूर्णांकr_state(dd, 1);
पूर्ण

/**
 * qib_handle_6120_hwerrors - display hardware errors.
 * @dd: the qlogic_ib device
 * @msg: the output buffer
 * @msgl: the size of the output buffer
 *
 * Use same msg buffer as regular errors to aव्योम excessive stack
 * use.  Most hardware errors are catastrophic, but क्रम right now,
 * we'll prपूर्णांक them and जारी.  Reuse the same message buffer as
 * handle_6120_errors() to aव्योम excessive stack usage.
 */
अटल व्योम qib_handle_6120_hwerrors(काष्ठा qib_devdata *dd, अक्षर *msg,
				     माप_प्रकार msgl)
अणु
	u64 hwerrs;
	u32 bits, ctrl;
	पूर्णांक isfatal = 0;
	अक्षर *bitsmsg;

	hwerrs = qib_पढ़ो_kreg64(dd, kr_hwerrstatus);
	अगर (!hwerrs)
		वापस;
	अगर (hwerrs == ~0ULL) अणु
		qib_dev_err(dd,
			"Read of hardware error status failed (all bits set); ignoring\n");
		वापस;
	पूर्ण
	qib_stats.sps_hwerrs++;

	/* Always clear the error status रेजिस्टर, except MEMBISTFAIL,
	 * regardless of whether we जारी or stop using the chip.
	 * We want that set so we know it failed, even across driver reload.
	 * We'll still ignore it in the hwerrmask.  We करो this partly क्रम
	 * diagnostics, but also क्रम support */
	qib_ग_लिखो_kreg(dd, kr_hwerrclear,
		       hwerrs & ~HWE_MASK(PowerOnBISTFailed));

	hwerrs &= dd->cspec->hwerrmask;

	/*
	 * Make sure we get this much out, unless told to be quiet,
	 * or it's occurred within the last 5 seconds.
	 */
	अगर (hwerrs & ~(TXE_PIO_PARITY | RXEMEMPARITYERR_EAGERTID))
		qib_devinfo(dd->pcidev,
			"Hardware error: hwerr=0x%llx (cleared)\n",
			(अचिन्हित दीर्घ दीर्घ) hwerrs);

	अगर (hwerrs & ~IB_HWE_BITSEXTANT)
		qib_dev_err(dd,
			"hwerror interrupt with unknown errors %llx set\n",
			(अचिन्हित दीर्घ दीर्घ)(hwerrs & ~IB_HWE_BITSEXTANT));

	ctrl = qib_पढ़ो_kreg32(dd, kr_control);
	अगर ((ctrl & QLOGIC_IB_C_FREEZEMODE) && !dd->diag_client) अणु
		/*
		 * Parity errors in send memory are recoverable,
		 * just cancel the send (अगर indicated in * sendbuffererror),
		 * count the occurrence, unमुक्तze (अगर no other handled
		 * hardware error bits are set), and जारी. They can
		 * occur अगर a processor speculative पढ़ो is करोne to the PIO
		 * buffer जबतक we are sending a packet, क्रम example.
		 */
		अगर (hwerrs & TXE_PIO_PARITY) अणु
			qib_6120_txe_recover(dd);
			hwerrs &= ~TXE_PIO_PARITY;
		पूर्ण

		अगर (!hwerrs) अणु
			अटल u32 मुक्तze_cnt;

			मुक्तze_cnt++;
			qib_6120_clear_मुक्तze(dd);
		पूर्ण अन्यथा
			isfatal = 1;
	पूर्ण

	*msg = '\0';

	अगर (hwerrs & HWE_MASK(PowerOnBISTFailed)) अणु
		isfatal = 1;
		strlcat(msg,
			"[Memory BIST test failed, InfiniPath hardware unusable]",
			msgl);
		/* ignore from now on, so disable until driver reloaded */
		dd->cspec->hwerrmask &= ~HWE_MASK(PowerOnBISTFailed);
		qib_ग_लिखो_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);
	पूर्ण

	qib_क्रमmat_hwerrors(hwerrs, qib_6120_hwerror_msgs,
			    ARRAY_SIZE(qib_6120_hwerror_msgs), msg, msgl);

	bitsmsg = dd->cspec->bitsmsgbuf;
	अगर (hwerrs & (QLOGIC_IB_HWE_PCIEMEMPARITYERR_MASK <<
		      QLOGIC_IB_HWE_PCIEMEMPARITYERR_SHIFT)) अणु
		bits = (u32) ((hwerrs >>
			       QLOGIC_IB_HWE_PCIEMEMPARITYERR_SHIFT) &
			      QLOGIC_IB_HWE_PCIEMEMPARITYERR_MASK);
		snम_लिखो(bitsmsg, माप(dd->cspec->bitsmsgbuf),
			 "[PCIe Mem Parity Errs %x] ", bits);
		strlcat(msg, bitsmsg, msgl);
	पूर्ण

	अगर (hwerrs & _QIB_PLL_FAIL) अणु
		isfatal = 1;
		snम_लिखो(bitsmsg, माप(dd->cspec->bitsmsgbuf),
			 "[PLL failed (%llx), InfiniPath hardware unusable]",
			 (अचिन्हित दीर्घ दीर्घ) hwerrs & _QIB_PLL_FAIL);
		strlcat(msg, bitsmsg, msgl);
		/* ignore from now on, so disable until driver reloaded */
		dd->cspec->hwerrmask &= ~(hwerrs & _QIB_PLL_FAIL);
		qib_ग_लिखो_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);
	पूर्ण

	अगर (hwerrs & QLOGIC_IB_HWE_SERDESPLLFAILED) अणु
		/*
		 * If it occurs, it is left masked since the बाह्यal
		 * पूर्णांकerface is unused
		 */
		dd->cspec->hwerrmask &= ~QLOGIC_IB_HWE_SERDESPLLFAILED;
		qib_ग_लिखो_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);
	पूर्ण

	अगर (hwerrs)
		/*
		 * अगर any set that we aren't ignoring; only
		 * make the complaपूर्णांक once, in हाल it's stuck
		 * or recurring, and we get here multiple
		 * बार.
		 */
		qib_dev_err(dd, "%s hardware error\n", msg);
	अन्यथा
		*msg = 0; /* recovered from all of them */

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
पूर्ण

/*
 * Decode the error status पूर्णांकo strings, deciding whether to always
 * prपूर्णांक * it or not depending on "normal packet errors" vs everything
 * अन्यथा.   Return 1 अगर "real" errors, otherwise 0 अगर only packet
 * errors, so caller can decide what to prपूर्णांक with the string.
 */
अटल पूर्णांक qib_decode_6120_err(काष्ठा qib_devdata *dd, अक्षर *buf, माप_प्रकार blen,
			       u64 err)
अणु
	पूर्णांक iserr = 1;

	*buf = '\0';
	अगर (err & QLOGIC_IB_E_PKTERRS) अणु
		अगर (!(err & ~QLOGIC_IB_E_PKTERRS))
			iserr = 0;
		अगर ((err & ERR_MASK(RcvICRCErr)) &&
		    !(err&(ERR_MASK(RcvVCRCErr)|ERR_MASK(RcvEBPErr))))
			strlcat(buf, "CRC ", blen);
		अगर (!iserr)
			जाओ करोne;
	पूर्ण
	अगर (err & ERR_MASK(RcvHdrLenErr))
		strlcat(buf, "rhdrlen ", blen);
	अगर (err & ERR_MASK(RcvBadTidErr))
		strlcat(buf, "rbadtid ", blen);
	अगर (err & ERR_MASK(RcvBadVersionErr))
		strlcat(buf, "rbadversion ", blen);
	अगर (err & ERR_MASK(RcvHdrErr))
		strlcat(buf, "rhdr ", blen);
	अगर (err & ERR_MASK(RcvLongPktLenErr))
		strlcat(buf, "rlongpktlen ", blen);
	अगर (err & ERR_MASK(RcvMaxPktLenErr))
		strlcat(buf, "rmaxpktlen ", blen);
	अगर (err & ERR_MASK(RcvMinPktLenErr))
		strlcat(buf, "rminpktlen ", blen);
	अगर (err & ERR_MASK(SendMinPktLenErr))
		strlcat(buf, "sminpktlen ", blen);
	अगर (err & ERR_MASK(RcvFormatErr))
		strlcat(buf, "rformaterr ", blen);
	अगर (err & ERR_MASK(RcvUnsupportedVLErr))
		strlcat(buf, "runsupvl ", blen);
	अगर (err & ERR_MASK(RcvUnexpectedCharErr))
		strlcat(buf, "runexpchar ", blen);
	अगर (err & ERR_MASK(RcvIBFlowErr))
		strlcat(buf, "ribflow ", blen);
	अगर (err & ERR_MASK(SendUnderRunErr))
		strlcat(buf, "sunderrun ", blen);
	अगर (err & ERR_MASK(SendPioArmLaunchErr))
		strlcat(buf, "spioarmlaunch ", blen);
	अगर (err & ERR_MASK(SendUnexpectedPktNumErr))
		strlcat(buf, "sunexperrpktnum ", blen);
	अगर (err & ERR_MASK(SendDroppedSmpPktErr))
		strlcat(buf, "sdroppedsmppkt ", blen);
	अगर (err & ERR_MASK(SendMaxPktLenErr))
		strlcat(buf, "smaxpktlen ", blen);
	अगर (err & ERR_MASK(SendUnsupportedVLErr))
		strlcat(buf, "sunsupVL ", blen);
	अगर (err & ERR_MASK(InvalidAddrErr))
		strlcat(buf, "invalidaddr ", blen);
	अगर (err & ERR_MASK(RcvEgrFullErr))
		strlcat(buf, "rcvegrfull ", blen);
	अगर (err & ERR_MASK(RcvHdrFullErr))
		strlcat(buf, "rcvhdrfull ", blen);
	अगर (err & ERR_MASK(IBStatusChanged))
		strlcat(buf, "ibcstatuschg ", blen);
	अगर (err & ERR_MASK(RcvIBLostLinkErr))
		strlcat(buf, "riblostlink ", blen);
	अगर (err & ERR_MASK(HardwareErr))
		strlcat(buf, "hardware ", blen);
	अगर (err & ERR_MASK(ResetNegated))
		strlcat(buf, "reset ", blen);
करोne:
	वापस iserr;
पूर्ण

/*
 * Called when we might have an error that is specअगरic to a particular
 * PIO buffer, and may need to cancel that buffer, so it can be re-used.
 */
अटल व्योम qib_disarm_6120_senderrbufs(काष्ठा qib_pportdata *ppd)
अणु
	अचिन्हित दीर्घ sbuf[2];
	काष्ठा qib_devdata *dd = ppd->dd;

	/*
	 * It's possible that sendbuffererror could have bits set; might
	 * have alपढ़ोy करोne this as a result of hardware error handling.
	 */
	sbuf[0] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror);
	sbuf[1] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror + 1);

	अगर (sbuf[0] || sbuf[1])
		qib_disarm_piobufs_set(dd, sbuf,
				       dd->piobcnt2k + dd->piobcnt4k);
पूर्ण

अटल पूर्णांक chk_6120_linkrecovery(काष्ठा qib_devdata *dd, u64 ibcs)
अणु
	पूर्णांक ret = 1;
	u32 ibstate = qib_6120_iblink_state(ibcs);
	u32 linkrecov = पढ़ो_6120_creg32(dd, cr_iblinkerrrecov);

	अगर (linkrecov != dd->cspec->lastlinkrecov) अणु
		/* and no more until active again */
		dd->cspec->lastlinkrecov = 0;
		qib_set_linkstate(dd->pport, QIB_IB_LINKDOWN);
		ret = 0;
	पूर्ण
	अगर (ibstate == IB_PORT_ACTIVE)
		dd->cspec->lastlinkrecov =
			पढ़ो_6120_creg32(dd, cr_iblinkerrrecov);
	वापस ret;
पूर्ण

अटल व्योम handle_6120_errors(काष्ठा qib_devdata *dd, u64 errs)
अणु
	अक्षर *msg;
	u64 ignore_this_समय = 0;
	u64 iserr = 0;
	काष्ठा qib_pportdata *ppd = dd->pport;
	u64 mask;

	/* करोn't report errors that are masked */
	errs &= dd->cspec->errormask;
	msg = dd->cspec->emsgbuf;

	/* करो these first, they are most important */
	अगर (errs & ERR_MASK(HardwareErr))
		qib_handle_6120_hwerrors(dd, msg, माप(dd->cspec->emsgbuf));

	अगर (errs & ~IB_E_BITSEXTANT)
		qib_dev_err(dd,
			"error interrupt with unknown errors %llx set\n",
			(अचिन्हित दीर्घ दीर्घ) (errs & ~IB_E_BITSEXTANT));

	अगर (errs & E_SUM_ERRS) अणु
		qib_disarm_6120_senderrbufs(ppd);
		अगर ((errs & E_SUM_LINK_PKTERRS) &&
		    !(ppd->lflags & QIBL_LINKACTIVE)) अणु
			/*
			 * This can happen when trying to bring the link
			 * up, but the IB link changes state at the "wrong"
			 * समय. The IB logic then complains that the packet
			 * isn't valid.  We don't want to confuse people, so
			 * we just करोn't prपूर्णांक them, except at debug
			 */
			ignore_this_समय = errs & E_SUM_LINK_PKTERRS;
		पूर्ण
	पूर्ण अन्यथा अगर ((errs & E_SUM_LINK_PKTERRS) &&
		   !(ppd->lflags & QIBL_LINKACTIVE)) अणु
		/*
		 * This can happen when SMA is trying to bring the link
		 * up, but the IB link changes state at the "wrong" समय.
		 * The IB logic then complains that the packet isn't
		 * valid.  We करोn't want to confuse people, so we just
		 * करोn't prपूर्णांक them, except at debug
		 */
		ignore_this_समय = errs & E_SUM_LINK_PKTERRS;
	पूर्ण

	qib_ग_लिखो_kreg(dd, kr_errclear, errs);

	errs &= ~ignore_this_समय;
	अगर (!errs)
		जाओ करोne;

	/*
	 * The ones we mask off are handled specially below
	 * or above.
	 */
	mask = ERR_MASK(IBStatusChanged) | ERR_MASK(RcvEgrFullErr) |
		ERR_MASK(RcvHdrFullErr) | ERR_MASK(HardwareErr);
	qib_decode_6120_err(dd, msg, माप(dd->cspec->emsgbuf), errs & ~mask);

	अगर (errs & E_SUM_PKTERRS)
		qib_stats.sps_rcverrs++;
	अगर (errs & E_SUM_ERRS)
		qib_stats.sps_txerrs++;

	iserr = errs & ~(E_SUM_PKTERRS | QLOGIC_IB_E_PKTERRS);

	अगर (errs & ERR_MASK(IBStatusChanged)) अणु
		u64 ibcs = qib_पढ़ो_kreg64(dd, kr_ibcstatus);
		u32 ibstate = qib_6120_iblink_state(ibcs);
		पूर्णांक handle = 1;

		अगर (ibstate != IB_PORT_INIT && dd->cspec->lastlinkrecov)
			handle = chk_6120_linkrecovery(dd, ibcs);
		/*
		 * Since going पूर्णांकo a recovery state causes the link state
		 * to go करोwn and since recovery is transitory, it is better
		 * अगर we "miss" ever seeing the link training state go पूर्णांकo
		 * recovery (i.e., ignore this transition क्रम link state
		 * special handling purposes) without updating lastibcstat.
		 */
		अगर (handle && qib_6120_phys_portstate(ibcs) ==
					    IB_PHYSPORTSTATE_LINK_ERR_RECOVER)
			handle = 0;
		अगर (handle)
			qib_handle_e_ibstatuschanged(ppd, ibcs);
	पूर्ण

	अगर (errs & ERR_MASK(ResetNegated)) अणु
		qib_dev_err(dd,
			"Got reset, requires re-init (unload and reload driver)\n");
		dd->flags &= ~QIB_INITTED;  /* needs re-init */
		/* mark as having had error */
		*dd->devstatusp |= QIB_STATUS_HWERROR;
		*dd->pport->statusp &= ~QIB_STATUS_IB_CONF;
	पूर्ण

	अगर (*msg && iserr)
		qib_dev_porterr(dd, ppd->port, "%s error\n", msg);

	अगर (ppd->state_wanted & ppd->lflags)
		wake_up_पूर्णांकerruptible(&ppd->state_रुको);

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

/**
 * qib_6120_init_hwerrors - enable hardware errors
 * @dd: the qlogic_ib device
 *
 * now that we have finished initializing everything that might reasonably
 * cause a hardware error, and cleared those errors bits as they occur,
 * we can enable hardware errors in the mask (potentially enabling
 * मुक्तze mode), and enable hardware errors as errors (aदीर्घ with
 * everything अन्यथा) in errormask
 */
अटल व्योम qib_6120_init_hwerrors(काष्ठा qib_devdata *dd)
अणु
	u64 val;
	u64 extsval;

	extsval = qib_पढ़ो_kreg64(dd, kr_extstatus);

	अगर (!(extsval & QLOGIC_IB_EXTS_MEMBIST_ENDTEST))
		qib_dev_err(dd, "MemBIST did not complete!\n");

	/* init so all hwerrors पूर्णांकerrupt, and enter मुक्तze, ajdust below */
	val = ~0ULL;
	अगर (dd->minrev < 2) अणु
		/*
		 * Aव्योम problem with पूर्णांकernal पूर्णांकerface bus parity
		 * checking. Fixed in Rev2.
		 */
		val &= ~QLOGIC_IB_HWE_PCIEBUSPARITYRADM;
	पूर्ण
	/* aव्योम some पूर्णांकel cpu's speculative पढ़ो मुक्तze mode issue */
	val &= ~TXEMEMPARITYERR_PIOBUF;

	dd->cspec->hwerrmask = val;

	qib_ग_लिखो_kreg(dd, kr_hwerrclear, ~HWE_MASK(PowerOnBISTFailed));
	qib_ग_लिखो_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);

	/* clear all */
	qib_ग_लिखो_kreg(dd, kr_errclear, ~0ULL);
	/* enable errors that are masked, at least this first समय. */
	qib_ग_लिखो_kreg(dd, kr_errmask, ~0ULL);
	dd->cspec->errormask = qib_पढ़ो_kreg64(dd, kr_errmask);
	/* clear any पूर्णांकerrupts up to this poपूर्णांक (पूर्णांकs still not enabled) */
	qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, ~0ULL);

	qib_ग_लिखो_kreg(dd, kr_rcvbthqp,
		       dd->qpn_mask << (QIB_6120_RcvBTHQP_BTHQP_Mask_LSB - 1) |
		       QIB_KD_QP);
पूर्ण

/*
 * Disable and enable the armlaunch error.  Used क्रम PIO bandwidth testing
 * on chips that are count-based, rather than trigger-based.  There is no
 * reference counting, but that's also fine, given the पूर्णांकended use.
 * Only chip-specअगरic because it's all रेजिस्टर accesses
 */
अटल व्योम qib_set_6120_armlaunch(काष्ठा qib_devdata *dd, u32 enable)
अणु
	अगर (enable) अणु
		qib_ग_लिखो_kreg(dd, kr_errclear,
			       ERR_MASK(SendPioArmLaunchErr));
		dd->cspec->errormask |= ERR_MASK(SendPioArmLaunchErr);
	पूर्ण अन्यथा
		dd->cspec->errormask &= ~ERR_MASK(SendPioArmLaunchErr);
	qib_ग_लिखो_kreg(dd, kr_errmask, dd->cspec->errormask);
पूर्ण

/*
 * Formerly took parameter <which> in pre-shअगरted,
 * pre-merged क्रमm with LinkCmd and LinkInitCmd
 * together, and assuming the zero was NOP.
 */
अटल व्योम qib_set_ib_6120_lstate(काष्ठा qib_pportdata *ppd, u16 linkcmd,
				   u16 linitcmd)
अणु
	u64 mod_wd;
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ flags;

	अगर (linitcmd == QLOGIC_IB_IBCC_LINKINITCMD_DISABLE) अणु
		/*
		 * If we are told to disable, note that so link-recovery
		 * code करोes not attempt to bring us back up.
		 */
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
	पूर्ण

	mod_wd = (linkcmd << QLOGIC_IB_IBCC_LINKCMD_SHIFT) |
		(linitcmd << QLOGIC_IB_IBCC_LINKINITCMD_SHIFT);

	qib_ग_लिखो_kreg(dd, kr_ibcctrl, dd->cspec->ibcctrl | mod_wd);
	/* ग_लिखो to chip to prevent back-to-back ग_लिखोs of control reg */
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);
पूर्ण

/**
 * qib_6120_bringup_serdes - bring up the serdes
 * @ppd: the qlogic_ib device
 */
अटल पूर्णांक qib_6120_bringup_serdes(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 val, config1, prev_val, hwstat, ibc;

	/* Put IBC in reset, sends disabled */
	dd->control &= ~QLOGIC_IB_C_LINKENABLE;
	qib_ग_लिखो_kreg(dd, kr_control, 0ULL);

	dd->cspec->ibdeltainprog = 1;
	dd->cspec->ibsymsnap = पढ़ो_6120_creg32(dd, cr_ibsymbolerr);
	dd->cspec->iblnkerrsnap = पढ़ो_6120_creg32(dd, cr_iblinkerrrecov);

	/* flowcontrolwatermark is in units of KBytes */
	ibc = 0x5ULL << SYM_LSB(IBCCtrl, FlowCtrlWaterMark);
	/*
	 * How often flowctrl sent.  More or less in usecs; balance against
	 * watermark value, so that in theory senders always get a flow
	 * control update in समय to not let the IB link go idle.
	 */
	ibc |= 0x3ULL << SYM_LSB(IBCCtrl, FlowCtrlPeriod);
	/* max error tolerance */
	dd->cspec->lli_thresh = 0xf;
	ibc |= (u64) dd->cspec->lli_thresh << SYM_LSB(IBCCtrl, PhyerrThreshold);
	/* use "real" buffer space क्रम */
	ibc |= 4ULL << SYM_LSB(IBCCtrl, CreditScale);
	/* IB credit flow control. */
	ibc |= 0xfULL << SYM_LSB(IBCCtrl, OverrunThreshold);
	/*
	 * set initial max size pkt IBC will send, including ICRC; it's the
	 * PIO buffer size in dwords, less 1; also see qib_set_mtu()
	 */
	ibc |= ((u64)(ppd->ibmaxlen >> 2) + 1) << SYM_LSB(IBCCtrl, MaxPktLen);
	dd->cspec->ibcctrl = ibc; /* without linkcmd or linkinitcmd! */

	/* initially come up रुकोing क्रम TS1, without sending anything. */
	val = dd->cspec->ibcctrl | (QLOGIC_IB_IBCC_LINKINITCMD_DISABLE <<
		QLOGIC_IB_IBCC_LINKINITCMD_SHIFT);
	qib_ग_लिखो_kreg(dd, kr_ibcctrl, val);

	val = qib_पढ़ो_kreg64(dd, kr_serdes_cfg0);
	config1 = qib_पढ़ो_kreg64(dd, kr_serdes_cfg1);

	/*
	 * Force reset on, also set rxdetect enable.  Must करो beक्रमe पढ़ोing
	 * serdesstatus at least क्रम simulation, or some of the bits in
	 * serdes status will come back as undefined and cause simulation
	 * failures
	 */
	val |= SYM_MASK(SerdesCfg0, ResetPLL) |
		SYM_MASK(SerdesCfg0, RxDetEnX) |
		(SYM_MASK(SerdesCfg0, L1PwrDnA) |
		 SYM_MASK(SerdesCfg0, L1PwrDnB) |
		 SYM_MASK(SerdesCfg0, L1PwrDnC) |
		 SYM_MASK(SerdesCfg0, L1PwrDnD));
	qib_ग_लिखो_kreg(dd, kr_serdes_cfg0, val);
	/* be sure chip saw it */
	qib_पढ़ो_kreg64(dd, kr_scratch);
	udelay(5);              /* need pll reset set at least क्रम a bit */
	/*
	 * after PLL is reset, set the per-lane Resets and TxIdle and
	 * clear the PLL reset and rxdetect (to get falling edge).
	 * Leave L1PWR bits set (permanently)
	 */
	val &= ~(SYM_MASK(SerdesCfg0, RxDetEnX) |
		 SYM_MASK(SerdesCfg0, ResetPLL) |
		 (SYM_MASK(SerdesCfg0, L1PwrDnA) |
		  SYM_MASK(SerdesCfg0, L1PwrDnB) |
		  SYM_MASK(SerdesCfg0, L1PwrDnC) |
		  SYM_MASK(SerdesCfg0, L1PwrDnD)));
	val |= (SYM_MASK(SerdesCfg0, ResetA) |
		SYM_MASK(SerdesCfg0, ResetB) |
		SYM_MASK(SerdesCfg0, ResetC) |
		SYM_MASK(SerdesCfg0, ResetD)) |
		SYM_MASK(SerdesCfg0, TxIdeEnX);
	qib_ग_लिखो_kreg(dd, kr_serdes_cfg0, val);
	/* be sure chip saw it */
	(व्योम) qib_पढ़ो_kreg64(dd, kr_scratch);
	/* need PLL reset clear क्रम at least 11 usec beक्रमe lane
	 * resets cleared; give it a few more to be sure */
	udelay(15);
	val &= ~((SYM_MASK(SerdesCfg0, ResetA) |
		  SYM_MASK(SerdesCfg0, ResetB) |
		  SYM_MASK(SerdesCfg0, ResetC) |
		  SYM_MASK(SerdesCfg0, ResetD)) |
		 SYM_MASK(SerdesCfg0, TxIdeEnX));

	qib_ग_लिखो_kreg(dd, kr_serdes_cfg0, val);
	/* be sure chip saw it */
	(व्योम) qib_पढ़ो_kreg64(dd, kr_scratch);

	val = qib_पढ़ो_kreg64(dd, kr_xgxs_cfg);
	prev_val = val;
	अगर (val & QLOGIC_IB_XGXS_RESET)
		val &= ~QLOGIC_IB_XGXS_RESET;
	अगर (SYM_FIELD(val, XGXSCfg, polarity_inv) != ppd->rx_pol_inv) अणु
		/* need to compensate क्रम Tx inversion in partner */
		val &= ~SYM_MASK(XGXSCfg, polarity_inv);
		val |= (u64)ppd->rx_pol_inv << SYM_LSB(XGXSCfg, polarity_inv);
	पूर्ण
	अगर (val != prev_val)
		qib_ग_लिखो_kreg(dd, kr_xgxs_cfg, val);

	val = qib_पढ़ो_kreg64(dd, kr_serdes_cfg0);

	/* clear current and de-emphasis bits */
	config1 &= ~0x0ffffffff00ULL;
	/* set current to 20ma */
	config1 |= 0x00000000000ULL;
	/* set de-emphasis to -5.68dB */
	config1 |= 0x0cccc000000ULL;
	qib_ग_लिखो_kreg(dd, kr_serdes_cfg1, config1);

	/* base and port guid same क्रम single port */
	ppd->guid = dd->base_guid;

	/*
	 * the process of setting and un-resetting the serdes normally
	 * causes a serdes PLL error, so check क्रम that and clear it
	 * here.  Also clearr hwerr bit in errstatus, but not others.
	 */
	hwstat = qib_पढ़ो_kreg64(dd, kr_hwerrstatus);
	अगर (hwstat) अणु
		/* should just have PLL, clear all set, in an हाल */
		qib_ग_लिखो_kreg(dd, kr_hwerrclear, hwstat);
		qib_ग_लिखो_kreg(dd, kr_errclear, ERR_MASK(HardwareErr));
	पूर्ण

	dd->control |= QLOGIC_IB_C_LINKENABLE;
	dd->control &= ~QLOGIC_IB_C_FREEZEMODE;
	qib_ग_लिखो_kreg(dd, kr_control, dd->control);

	वापस 0;
पूर्ण

/**
 * qib_6120_quiet_serdes - set serdes to txidle
 * @ppd: physical port of the qlogic_ib device
 * Called when driver is being unloaded
 */
अटल व्योम qib_6120_quiet_serdes(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 val;

	qib_set_ib_6120_lstate(ppd, 0, QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);

	/* disable IBC */
	dd->control &= ~QLOGIC_IB_C_LINKENABLE;
	qib_ग_लिखो_kreg(dd, kr_control,
		       dd->control | QLOGIC_IB_C_FREEZEMODE);

	अगर (dd->cspec->ibsymdelta || dd->cspec->iblnkerrdelta ||
	    dd->cspec->ibdeltainprog) अणु
		u64 diagc;

		/* enable counter ग_लिखोs */
		diagc = qib_पढ़ो_kreg64(dd, kr_hwdiagctrl);
		qib_ग_लिखो_kreg(dd, kr_hwdiagctrl,
			       diagc | SYM_MASK(HwDiagCtrl, CounterWrEnable));

		अगर (dd->cspec->ibsymdelta || dd->cspec->ibdeltainprog) अणु
			val = पढ़ो_6120_creg32(dd, cr_ibsymbolerr);
			अगर (dd->cspec->ibdeltainprog)
				val -= val - dd->cspec->ibsymsnap;
			val -= dd->cspec->ibsymdelta;
			ग_लिखो_6120_creg(dd, cr_ibsymbolerr, val);
		पूर्ण
		अगर (dd->cspec->iblnkerrdelta || dd->cspec->ibdeltainprog) अणु
			val = पढ़ो_6120_creg32(dd, cr_iblinkerrrecov);
			अगर (dd->cspec->ibdeltainprog)
				val -= val - dd->cspec->iblnkerrsnap;
			val -= dd->cspec->iblnkerrdelta;
			ग_लिखो_6120_creg(dd, cr_iblinkerrrecov, val);
		पूर्ण

		/* and disable counter ग_लिखोs */
		qib_ग_लिखो_kreg(dd, kr_hwdiagctrl, diagc);
	पूर्ण

	val = qib_पढ़ो_kreg64(dd, kr_serdes_cfg0);
	val |= SYM_MASK(SerdesCfg0, TxIdeEnX);
	qib_ग_लिखो_kreg(dd, kr_serdes_cfg0, val);
पूर्ण

/**
 * qib_6120_setup_setextled - set the state of the two बाह्यal LEDs
 * @ppd: the qlogic_ib device
 * @on: whether the link is up or not
 *
 * The exact combo of LEDs अगर on is true is determined by looking
 * at the ibcstatus.
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
 *
 */
अटल व्योम qib_6120_setup_setextled(काष्ठा qib_pportdata *ppd, u32 on)
अणु
	u64 extctl, val, lst, ltst;
	अचिन्हित दीर्घ flags;
	काष्ठा qib_devdata *dd = ppd->dd;

	/*
	 * The diags use the LED to indicate diag info, so we leave
	 * the बाह्यal LED alone when the diags are running.
	 */
	अगर (dd->diag_client)
		वापस;

	/* Allow override of LED display क्रम, e.g. Locating प्रणाली in rack */
	अगर (ppd->led_override) अणु
		ltst = (ppd->led_override & QIB_LED_PHYS) ?
			IB_PHYSPORTSTATE_LINKUP : IB_PHYSPORTSTATE_DISABLED,
		lst = (ppd->led_override & QIB_LED_LOG) ?
			IB_PORT_ACTIVE : IB_PORT_DOWN;
	पूर्ण अन्यथा अगर (on) अणु
		val = qib_पढ़ो_kreg64(dd, kr_ibcstatus);
		ltst = qib_6120_phys_portstate(val);
		lst = qib_6120_iblink_state(val);
	पूर्ण अन्यथा अणु
		ltst = 0;
		lst = 0;
	पूर्ण

	spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
	extctl = dd->cspec->extctrl & ~(SYM_MASK(EXTCtrl, LEDPriPortGreenOn) |
				 SYM_MASK(EXTCtrl, LEDPriPortYellowOn));

	अगर (ltst == IB_PHYSPORTSTATE_LINKUP)
		extctl |= SYM_MASK(EXTCtrl, LEDPriPortYellowOn);
	अगर (lst == IB_PORT_ACTIVE)
		extctl |= SYM_MASK(EXTCtrl, LEDPriPortGreenOn);
	dd->cspec->extctrl = extctl;
	qib_ग_लिखो_kreg(dd, kr_extctrl, extctl);
	spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
पूर्ण

/**
 * qib_6120_setup_cleanup - clean up any per-chip chip-specअगरic stuff
 * @dd: the qlogic_ib device
 *
 * This is called during driver unload.
*/
अटल व्योम qib_6120_setup_cleanup(काष्ठा qib_devdata *dd)
अणु
	qib_मुक्त_irq(dd);
	kमुक्त(dd->cspec->cntrs);
	kमुक्त(dd->cspec->portcntrs);
	अगर (dd->cspec->dummy_hdrq) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev,
				  ALIGN(dd->rcvhdrcnt *
					dd->rcvhdrentsize *
					माप(u32), PAGE_SIZE),
				  dd->cspec->dummy_hdrq,
				  dd->cspec->dummy_hdrq_phys);
		dd->cspec->dummy_hdrq = शून्य;
	पूर्ण
पूर्ण

अटल व्योम qib_wantpiobuf_6120_पूर्णांकr(काष्ठा qib_devdata *dd, u32 needपूर्णांक)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);
	अगर (needपूर्णांक)
		dd->sendctrl |= SYM_MASK(SendCtrl, PIOIntBufAvail);
	अन्यथा
		dd->sendctrl &= ~SYM_MASK(SendCtrl, PIOIntBufAvail);
	qib_ग_लिखो_kreg(dd, kr_sendctrl, dd->sendctrl);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
पूर्ण

/*
 * handle errors and unusual events first, separate function
 * to improve cache hits क्रम fast path पूर्णांकerrupt handling
 */
अटल noअंतरभूत व्योम unlikely_6120_पूर्णांकr(काष्ठा qib_devdata *dd, u64 istat)
अणु
	अगर (unlikely(istat & ~QLOGIC_IB_I_BITSEXTANT))
		qib_dev_err(dd, "interrupt with unknown interrupts %Lx set\n",
			    istat & ~QLOGIC_IB_I_BITSEXTANT);

	अगर (istat & QLOGIC_IB_I_ERROR) अणु
		u64 estat = 0;

		qib_stats.sps_errपूर्णांकs++;
		estat = qib_पढ़ो_kreg64(dd, kr_errstatus);
		अगर (!estat)
			qib_devinfo(dd->pcidev,
				"error interrupt (%Lx), but no error bits set!\n",
				istat);
		handle_6120_errors(dd, estat);
	पूर्ण

	अगर (istat & QLOGIC_IB_I_GPIO) अणु
		u32 gpiostatus;
		u32 to_clear = 0;

		/*
		 * GPIO_3..5 on IBA6120 Rev2 chips indicate
		 * errors that we need to count.
		 */
		gpiostatus = qib_पढ़ो_kreg32(dd, kr_gpio_status);
		/* First the error-counter हाल. */
		अगर (gpiostatus & GPIO_ERRINTR_MASK) अणु
			/* want to clear the bits we see निश्चितed. */
			to_clear |= (gpiostatus & GPIO_ERRINTR_MASK);

			/*
			 * Count appropriately, clear bits out of our copy,
			 * as they have been "handled".
			 */
			अगर (gpiostatus & (1 << GPIO_RXUVL_BIT))
				dd->cspec->rxfc_unsupvl_errs++;
			अगर (gpiostatus & (1 << GPIO_OVRUN_BIT))
				dd->cspec->overrun_thresh_errs++;
			अगर (gpiostatus & (1 << GPIO_LLI_BIT))
				dd->cspec->lli_errs++;
			gpiostatus &= ~GPIO_ERRINTR_MASK;
		पूर्ण
		अगर (gpiostatus) अणु
			/*
			 * Some unexpected bits reमुख्य. If they could have
			 * caused the पूर्णांकerrupt, complain and clear.
			 * To aव्योम repetition of this condition, also clear
			 * the mask. It is almost certainly due to error.
			 */
			स्थिर u32 mask = qib_पढ़ो_kreg32(dd, kr_gpio_mask);

			/*
			 * Also check that the chip reflects our shaकरोw,
			 * and report issues, If they caused the पूर्णांकerrupt.
			 * we will suppress by refreshing from the shaकरोw.
			 */
			अगर (mask & gpiostatus) अणु
				to_clear |= (gpiostatus & mask);
				dd->cspec->gpio_mask &= ~(gpiostatus & mask);
				qib_ग_लिखो_kreg(dd, kr_gpio_mask,
					       dd->cspec->gpio_mask);
			पूर्ण
		पूर्ण
		अगर (to_clear)
			qib_ग_लिखो_kreg(dd, kr_gpio_clear, (u64) to_clear);
	पूर्ण
पूर्ण

अटल irqवापस_t qib_6120पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_devdata *dd = data;
	irqवापस_t ret;
	u32 istat, ctxtrbits, rmask, crcs = 0;
	अचिन्हित i;

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

	istat = qib_पढ़ो_kreg32(dd, kr_पूर्णांकstatus);

	अगर (unlikely(!istat)) अणु
		ret = IRQ_NONE; /* not our पूर्णांकerrupt, or alपढ़ोy handled */
		जाओ bail;
	पूर्ण
	अगर (unlikely(istat == -1)) अणु
		qib_bad_पूर्णांकrstatus(dd);
		/* करोn't know अगर it was our पूर्णांकerrupt or not */
		ret = IRQ_NONE;
		जाओ bail;
	पूर्ण

	this_cpu_inc(*dd->पूर्णांक_counter);

	अगर (unlikely(istat & (~QLOGIC_IB_I_BITSEXTANT |
			      QLOGIC_IB_I_GPIO | QLOGIC_IB_I_ERROR)))
		unlikely_6120_पूर्णांकr(dd, istat);

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
	ctxtrbits = istat &
		((QLOGIC_IB_I_RCVAVAIL_MASK << QLOGIC_IB_I_RCVAVAIL_SHIFT) |
		 (QLOGIC_IB_I_RCVURG_MASK << QLOGIC_IB_I_RCVURG_SHIFT));
	अगर (ctxtrbits) अणु
		rmask = (1U << QLOGIC_IB_I_RCVAVAIL_SHIFT) |
			(1U << QLOGIC_IB_I_RCVURG_SHIFT);
		क्रम (i = 0; i < dd->first_user_ctxt; i++) अणु
			अगर (ctxtrbits & rmask) अणु
				ctxtrbits &= ~rmask;
				crcs += qib_kreceive(dd->rcd[i],
						     &dd->cspec->lli_counter,
						     शून्य);
			पूर्ण
			rmask <<= 1;
		पूर्ण
		अगर (crcs) अणु
			u32 cntr = dd->cspec->lli_counter;

			cntr += crcs;
			अगर (cntr) अणु
				अगर (cntr > dd->cspec->lli_thresh) अणु
					dd->cspec->lli_counter = 0;
					dd->cspec->lli_errs++;
				पूर्ण अन्यथा
					dd->cspec->lli_counter += cntr;
			पूर्ण
		पूर्ण


		अगर (ctxtrbits) अणु
			ctxtrbits =
				(ctxtrbits >> QLOGIC_IB_I_RCVAVAIL_SHIFT) |
				(ctxtrbits >> QLOGIC_IB_I_RCVURG_SHIFT);
			qib_handle_urcv(dd, ctxtrbits);
		पूर्ण
	पूर्ण

	अगर ((istat & QLOGIC_IB_I_SPIOBUFAVAIL) && (dd->flags & QIB_INITTED))
		qib_ib_piobufavail(dd);

	ret = IRQ_HANDLED;
bail:
	वापस ret;
पूर्ण

/*
 * Set up our chip-specअगरic पूर्णांकerrupt handler
 * The पूर्णांकerrupt type has alपढ़ोy been setup, so
 * we just need to करो the registration and error checking.
 */
अटल व्योम qib_setup_6120_पूर्णांकerrupt(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret;

	/*
	 * If the chip supports added error indication via GPIO pins,
	 * enable पूर्णांकerrupts on those bits so the पूर्णांकerrupt routine
	 * can count the events. Also set flag so पूर्णांकerrupt routine
	 * can know they are expected.
	 */
	अगर (SYM_FIELD(dd->revision, Revision_R,
		      ChipRevMinor) > 1) अणु
		/* Rev2+ reports extra errors via पूर्णांकernal GPIO pins */
		dd->cspec->gpio_mask |= GPIO_ERRINTR_MASK;
		qib_ग_लिखो_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
	पूर्ण

	ret = pci_request_irq(dd->pcidev, 0, qib_6120पूर्णांकr, शून्य, dd,
			      QIB_DRV_NAME);
	अगर (ret)
		qib_dev_err(dd,
			    "Couldn't setup interrupt (irq=%d): %d\n",
			    pci_irq_vector(dd->pcidev, 0), ret);
पूर्ण

/**
 * pe_boardname - fill in the board name
 * @dd: the qlogic_ib device
 *
 * info is based on the board revision रेजिस्टर
 */
अटल व्योम pe_boardname(काष्ठा qib_devdata *dd)
अणु
	u32 boardid;

	boardid = SYM_FIELD(dd->revision, Revision,
			    BoardID);

	चयन (boardid) अणु
	हाल 2:
		dd->boardname = "InfiniPath_QLE7140";
		अवरोध;
	शेष:
		qib_dev_err(dd, "Unknown 6120 board with ID %u\n", boardid);
		dd->boardname = "Unknown_InfiniPath_6120";
		अवरोध;
	पूर्ण

	अगर (dd->majrev != 4 || !dd->minrev || dd->minrev > 2)
		qib_dev_err(dd,
			    "Unsupported InfiniPath hardware revision %u.%u!\n",
			    dd->majrev, dd->minrev);

	snम_लिखो(dd->boardversion, माप(dd->boardversion),
		 "ChipABI %u.%u, %s, InfiniPath%u %u.%u, SW Compat %u\n",
		 QIB_CHIP_VERS_MAJ, QIB_CHIP_VERS_MIN, dd->boardname,
		 (अचिन्हित पूर्णांक)SYM_FIELD(dd->revision, Revision_R, Arch),
		 dd->majrev, dd->minrev,
		 (अचिन्हित पूर्णांक)SYM_FIELD(dd->revision, Revision_R, SW));
पूर्ण

/*
 * This routine sleeps, so it can only be called from user context, not
 * from पूर्णांकerrupt context.  If we need पूर्णांकerrupt context, we can split
 * it पूर्णांकo two routines.
 */
अटल पूर्णांक qib_6120_setup_reset(काष्ठा qib_devdata *dd)
अणु
	u64 val;
	पूर्णांक i;
	पूर्णांक ret;
	u16 cmdval;
	u8 पूर्णांक_line, clinesz;

	qib_pcie_अ_लोmd(dd, &cmdval, &पूर्णांक_line, &clinesz);

	/* Use ERROR so it shows up in logs, etc. */
	qib_dev_err(dd, "Resetting InfiniPath unit %u\n", dd->unit);

	/* no पूर्णांकerrupts till re-initted */
	qib_6120_set_पूर्णांकr_state(dd, 0);

	dd->cspec->ibdeltainprog = 0;
	dd->cspec->ibsymdelta = 0;
	dd->cspec->iblnkerrdelta = 0;

	/*
	 * Keep chip from being accessed until we are पढ़ोy.  Use
	 * ग_लिखोq() directly, to allow the ग_लिखो even though QIB_PRESENT
	 * isn't set.
	 */
	dd->flags &= ~(QIB_INITTED | QIB_PRESENT);
	/* so we check पूर्णांकerrupts work again */
	dd->z_पूर्णांक_counter = qib_पूर्णांक_counter(dd);
	val = dd->control | QLOGIC_IB_C_RESET;
	ग_लिखोq(val, &dd->kregbase[kr_control]);
	mb(); /* prevent compiler re-ordering around actual reset */

	क्रम (i = 1; i <= 5; i++) अणु
		/*
		 * Allow MBIST, etc. to complete; दीर्घer on each retry.
		 * We someबार get machine checks from bus समयout अगर no
		 * response, so क्रम now, make it *really* दीर्घ.
		 */
		msleep(1000 + (1 + i) * 2000);

		qib_pcie_reenable(dd, cmdval, पूर्णांक_line, clinesz);

		/*
		 * Use पढ़ोq directly, so we करोn't need to mark it as PRESENT
		 * until we get a successful indication that all is well.
		 */
		val = पढ़ोq(&dd->kregbase[kr_revision]);
		अगर (val == dd->revision) अणु
			dd->flags |= QIB_PRESENT; /* it's back */
			ret = qib_reinit_पूर्णांकr(dd);
			जाओ bail;
		पूर्ण
	पूर्ण
	ret = 0; /* failed */

bail:
	अगर (ret) अणु
		अगर (qib_pcie_params(dd, dd->lbus_width, शून्य))
			qib_dev_err(dd,
				"Reset failed to setup PCIe or interrupts; continuing anyway\n");
		/* clear the reset error, init error/hwerror mask */
		qib_6120_init_hwerrors(dd);
		/* क्रम Rev2 error पूर्णांकerrupts; nop क्रम rev 1 */
		qib_ग_लिखो_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
		/* clear the reset error, init error/hwerror mask */
		qib_6120_init_hwerrors(dd);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * qib_6120_put_tid - ग_लिखो a TID in chip
 * @dd: the qlogic_ib device
 * @tidptr: poपूर्णांकer to the expected TID (in chip) to update
 * @type: RCVHQ_RCV_TYPE_EAGER (1) क्रम eager, RCVHQ_RCV_TYPE_EXPECTED (0)
 * क्रम expected
 * @pa: physical address of in memory buffer; tidinvalid अगर मुक्तing
 *
 * This exists as a separate routine to allow क्रम special locking etc.
 * It's used क्रम both the full cleanup on निकास, as well as the normal
 * setup and tearकरोwn.
 */
अटल व्योम qib_6120_put_tid(काष्ठा qib_devdata *dd, u64 __iomem *tidptr,
			     u32 type, अचिन्हित दीर्घ pa)
अणु
	u32 __iomem *tidp32 = (u32 __iomem *)tidptr;
	अचिन्हित दीर्घ flags;
	पूर्णांक tidx;
	spinlock_t *tidlockp; /* select appropriate spinlock */

	अगर (!dd->kregbase)
		वापस;

	अगर (pa != dd->tidinvalid) अणु
		अगर (pa & ((1U << 11) - 1)) अणु
			qib_dev_err(dd, "Physaddr %lx not 2KB aligned!\n",
				    pa);
			वापस;
		पूर्ण
		pa >>= 11;
		अगर (pa & ~QLOGIC_IB_RT_ADDR_MASK) अणु
			qib_dev_err(dd,
				"Physical page address 0x%lx larger than supported\n",
				pa);
			वापस;
		पूर्ण

		अगर (type == RCVHQ_RCV_TYPE_EAGER)
			pa |= dd->tidढाँचा;
		अन्यथा /* क्रम now, always full 4KB page */
			pa |= 2 << 29;
	पूर्ण

	/*
	 * Aव्योम chip issue by writing the scratch रेजिस्टर
	 * beक्रमe and after the TID, and with an io ग_लिखो barrier.
	 * We use a spinlock around the ग_लिखोs, so they can't पूर्णांकermix
	 * with other TID (eager or expected) ग_लिखोs (the chip problem
	 * is triggered by back to back TID ग_लिखोs). Unक्रमtunately, this
	 * call can be करोne from पूर्णांकerrupt level क्रम the ctxt 0 eager TIDs,
	 * so we have to use irqsave locks.
	 */
	/*
	 * Assumes tidptr always > egrtidbase
	 * अगर type == RCVHQ_RCV_TYPE_EAGER.
	 */
	tidx = tidptr - dd->egrtidbase;

	tidlockp = (type == RCVHQ_RCV_TYPE_EAGER && tidx < dd->rcvhdrcnt)
		? &dd->cspec->kernel_tid_lock : &dd->cspec->user_tid_lock;
	spin_lock_irqsave(tidlockp, flags);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0xfeeddeaf);
	ग_लिखोl(pa, tidp32);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0xdeadbeef);
	spin_unlock_irqrestore(tidlockp, flags);
पूर्ण

/**
 * qib_6120_put_tid_2 - ग_लिखो a TID in chip, Revision 2 or higher
 * @dd: the qlogic_ib device
 * @tidptr: poपूर्णांकer to the expected TID (in chip) to update
 * @type: RCVHQ_RCV_TYPE_EAGER (1) क्रम eager, RCVHQ_RCV_TYPE_EXPECTED (0)
 * क्रम expected
 * @pa: physical address of in memory buffer; tidinvalid अगर मुक्तing
 *
 * This exists as a separate routine to allow क्रम selection of the
 * appropriate "flavor". The अटल calls in cleanup just use the
 * revision-agnostic क्रमm, as they are not perक्रमmance critical.
 */
अटल व्योम qib_6120_put_tid_2(काष्ठा qib_devdata *dd, u64 __iomem *tidptr,
			       u32 type, अचिन्हित दीर्घ pa)
अणु
	u32 __iomem *tidp32 = (u32 __iomem *)tidptr;

	अगर (!dd->kregbase)
		वापस;

	अगर (pa != dd->tidinvalid) अणु
		अगर (pa & ((1U << 11) - 1)) अणु
			qib_dev_err(dd, "Physaddr %lx not 2KB aligned!\n",
				    pa);
			वापस;
		पूर्ण
		pa >>= 11;
		अगर (pa & ~QLOGIC_IB_RT_ADDR_MASK) अणु
			qib_dev_err(dd,
				"Physical page address 0x%lx larger than supported\n",
				pa);
			वापस;
		पूर्ण

		अगर (type == RCVHQ_RCV_TYPE_EAGER)
			pa |= dd->tidढाँचा;
		अन्यथा /* क्रम now, always full 4KB page */
			pa |= 2 << 29;
	पूर्ण
	ग_लिखोl(pa, tidp32);
पूर्ण


/**
 * qib_6120_clear_tids - clear all TID entries क्रम a context, expected and eager
 * @dd: the qlogic_ib device
 * @rcd: the context
 *
 * clear all TID entries क्रम a context, expected and eager.
 * Used from qib_बंद().  On this chip, TIDs are only 32 bits,
 * not 64, but they are still on 64 bit boundaries, so tidbase
 * is declared as u64 * क्रम the poपूर्णांकer math, even though we ग_लिखो 32 bits
 */
अटल व्योम qib_6120_clear_tids(काष्ठा qib_devdata *dd,
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
		((अक्षर __iomem *)(dd->kregbase) +
		 dd->rcvtidbase +
		 ctxt * dd->rcvtidcnt * माप(*tidbase));

	क्रम (i = 0; i < dd->rcvtidcnt; i++)
		/* use func poपूर्णांकer because could be one of two funcs */
		dd->f_put_tid(dd, &tidbase[i], RCVHQ_RCV_TYPE_EXPECTED,
				  tidinv);

	tidbase = (u64 __iomem *)
		((अक्षर __iomem *)(dd->kregbase) +
		 dd->rcvegrbase +
		 rcd->rcvegr_tid_base * माप(*tidbase));

	क्रम (i = 0; i < rcd->rcvegrcnt; i++)
		/* use func poपूर्णांकer because could be one of two funcs */
		dd->f_put_tid(dd, &tidbase[i], RCVHQ_RCV_TYPE_EAGER,
				  tidinv);
पूर्ण

/**
 * qib_6120_tidढाँचा - setup स्थिरants क्रम TID updates
 * @dd: the qlogic_ib device
 *
 * We setup stuff that we use a lot, to aव्योम calculating each समय
 */
अटल व्योम qib_6120_tidढाँचा(काष्ठा qib_devdata *dd)
अणु
	u32 egrsize = dd->rcvegrbufsize;

	/*
	 * For now, we always allocate 4KB buffers (at init) so we can
	 * receive max size packets.  We may want a module parameter to
	 * specअगरy 2KB or 4KB and/or make be per ctxt instead of per device
	 * क्रम those who want to reduce memory footprपूर्णांक.  Note that the
	 * rcvhdrentsize size must be large enough to hold the largest
	 * IB header (currently 96 bytes) that we expect to handle (plus of
	 * course the 2 dwords of RHF).
	 */
	अगर (egrsize == 2048)
		dd->tidढाँचा = 1U << 29;
	अन्यथा अगर (egrsize == 4096)
		dd->tidढाँचा = 2U << 29;
	dd->tidinvalid = 0;
पूर्ण

पूर्णांक __attribute__((weak)) qib_unordered_wc(व्योम)
अणु
	वापस 0;
पूर्ण

/**
 * qib_6120_get_base_info - set chip-specअगरic flags क्रम user code
 * @rcd: the qlogic_ib ctxt
 * @kinfo: qib_base_info poपूर्णांकer
 *
 * We set the PCIE flag because the lower bandwidth on PCIe vs
 * HyperTransport can affect some user packet algorithms.
 */
अटल पूर्णांक qib_6120_get_base_info(काष्ठा qib_ctxtdata *rcd,
				  काष्ठा qib_base_info *kinfo)
अणु
	अगर (qib_unordered_wc())
		kinfo->spi_runसमय_flags |= QIB_RUNTIME_FORCE_WC_ORDER;

	kinfo->spi_runसमय_flags |= QIB_RUNTIME_PCIE |
		QIB_RUNTIME_FORCE_PIOAVAIL | QIB_RUNTIME_PIO_REGSWAPPED;
	वापस 0;
पूर्ण


अटल काष्ठा qib_message_header *
qib_6120_get_msgheader(काष्ठा qib_devdata *dd, __le32 *rhf_addr)
अणु
	वापस (काष्ठा qib_message_header *)
		&rhf_addr[माप(u64) / माप(u32)];
पूर्ण

अटल व्योम qib_6120_config_ctxts(काष्ठा qib_devdata *dd)
अणु
	dd->ctxtcnt = qib_पढ़ो_kreg32(dd, kr_portcnt);
	अगर (qib_n_krcv_queues > 1) अणु
		dd->first_user_ctxt = qib_n_krcv_queues * dd->num_pports;
		अगर (dd->first_user_ctxt > dd->ctxtcnt)
			dd->first_user_ctxt = dd->ctxtcnt;
		dd->qpn_mask = dd->first_user_ctxt <= 2 ? 2 : 6;
	पूर्ण अन्यथा
		dd->first_user_ctxt = dd->num_pports;
	dd->n_krcv_queues = dd->first_user_ctxt;
पूर्ण

अटल व्योम qib_update_6120_usrhead(काष्ठा qib_ctxtdata *rcd, u64 hd,
				    u32 updegr, u32 egrhd, u32 npkts)
अणु
	अगर (updegr)
		qib_ग_लिखो_ureg(rcd->dd, ur_rcvegrindexhead, egrhd, rcd->ctxt);
	qib_ग_लिखो_ureg(rcd->dd, ur_rcvhdrhead, hd, rcd->ctxt);
पूर्ण

अटल u32 qib_6120_hdrqempty(काष्ठा qib_ctxtdata *rcd)
अणु
	u32 head, tail;

	head = qib_पढ़ो_ureg32(rcd->dd, ur_rcvhdrhead, rcd->ctxt);
	अगर (rcd->rcvhdrtail_kvaddr)
		tail = qib_get_rcvhdrtail(rcd);
	अन्यथा
		tail = qib_पढ़ो_ureg32(rcd->dd, ur_rcvhdrtail, rcd->ctxt);
	वापस head == tail;
पूर्ण

/*
 * Used when we बंद any ctxt, क्रम DMA alपढ़ोy in flight
 * at बंद.  Can't be करोne until we know hdrq size, so not
 * early in chip init.
 */
अटल व्योम alloc_dummy_hdrq(काष्ठा qib_devdata *dd)
अणु
	dd->cspec->dummy_hdrq = dma_alloc_coherent(&dd->pcidev->dev,
					dd->rcd[0]->rcvhdrq_size,
					&dd->cspec->dummy_hdrq_phys,
					GFP_ATOMIC | __GFP_COMP);
	अगर (!dd->cspec->dummy_hdrq) अणु
		qib_devinfo(dd->pcidev, "Couldn't allocate dummy hdrq\n");
		/* fallback to just 0'ing */
		dd->cspec->dummy_hdrq_phys = 0UL;
	पूर्ण
पूर्ण

/*
 * Modअगरy the RCVCTRL रेजिस्टर in chip-specअगरic way. This
 * is a function because bit positions and (future) रेजिस्टर
 * location is chip-specअगरic, but the needed operations are
 * generic. <op> is a bit-mask because we often want to
 * करो multiple modअगरications.
 */
अटल व्योम rcvctrl_6120_mod(काष्ठा qib_pportdata *ppd, अचिन्हित पूर्णांक op,
			     पूर्णांक ctxt)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 mask, val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);

	अगर (op & QIB_RCVCTRL_TAILUPD_ENB)
		dd->rcvctrl |= (1ULL << QLOGIC_IB_R_TAILUPD_SHIFT);
	अगर (op & QIB_RCVCTRL_TAILUPD_DIS)
		dd->rcvctrl &= ~(1ULL << QLOGIC_IB_R_TAILUPD_SHIFT);
	अगर (op & QIB_RCVCTRL_PKEY_ENB)
		dd->rcvctrl &= ~(1ULL << IBA6120_R_PKEY_DIS_SHIFT);
	अगर (op & QIB_RCVCTRL_PKEY_DIS)
		dd->rcvctrl |= (1ULL << IBA6120_R_PKEY_DIS_SHIFT);
	अगर (ctxt < 0)
		mask = (1ULL << dd->ctxtcnt) - 1;
	अन्यथा
		mask = (1ULL << ctxt);
	अगर (op & QIB_RCVCTRL_CTXT_ENB) अणु
		/* always करोne क्रम specअगरic ctxt */
		dd->rcvctrl |= (mask << SYM_LSB(RcvCtrl, PortEnable));
		अगर (!(dd->flags & QIB_NODMA_RTAIL))
			dd->rcvctrl |= 1ULL << QLOGIC_IB_R_TAILUPD_SHIFT;
		/* Write these रेजिस्टरs beक्रमe the context is enabled. */
		qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdrtailaddr, ctxt,
			dd->rcd[ctxt]->rcvhdrqtailaddr_phys);
		qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdraddr, ctxt,
			dd->rcd[ctxt]->rcvhdrq_phys);

		अगर (ctxt == 0 && !dd->cspec->dummy_hdrq)
			alloc_dummy_hdrq(dd);
	पूर्ण
	अगर (op & QIB_RCVCTRL_CTXT_DIS)
		dd->rcvctrl &= ~(mask << SYM_LSB(RcvCtrl, PortEnable));
	अगर (op & QIB_RCVCTRL_INTRAVAIL_ENB)
		dd->rcvctrl |= (mask << QLOGIC_IB_R_INTRAVAIL_SHIFT);
	अगर (op & QIB_RCVCTRL_INTRAVAIL_DIS)
		dd->rcvctrl &= ~(mask << QLOGIC_IB_R_INTRAVAIL_SHIFT);
	qib_ग_लिखो_kreg(dd, kr_rcvctrl, dd->rcvctrl);
	अगर ((op & QIB_RCVCTRL_INTRAVAIL_ENB) && dd->rhdrhead_पूर्णांकr_off) अणु
		/* arm rcv पूर्णांकerrupt */
		val = qib_पढ़ो_ureg32(dd, ur_rcvhdrhead, ctxt) |
			dd->rhdrhead_पूर्णांकr_off;
		qib_ग_लिखो_ureg(dd, ur_rcvhdrhead, val, ctxt);
	पूर्ण
	अगर (op & QIB_RCVCTRL_CTXT_ENB) अणु
		/*
		 * Init the context रेजिस्टरs also; अगर we were
		 * disabled, tail and head should both be zero
		 * alपढ़ोy from the enable, but since we करोn't
		 * know, we have to करो it explicitly.
		 */
		val = qib_पढ़ो_ureg32(dd, ur_rcvegrindextail, ctxt);
		qib_ग_लिखो_ureg(dd, ur_rcvegrindexhead, val, ctxt);

		val = qib_पढ़ो_ureg32(dd, ur_rcvhdrtail, ctxt);
		dd->rcd[ctxt]->head = val;
		/* If kctxt, पूर्णांकerrupt on next receive. */
		अगर (ctxt < dd->first_user_ctxt)
			val |= dd->rhdrhead_पूर्णांकr_off;
		qib_ग_लिखो_ureg(dd, ur_rcvhdrhead, val, ctxt);
	पूर्ण
	अगर (op & QIB_RCVCTRL_CTXT_DIS) अणु
		/*
		 * Be paranoid, and never ग_लिखो 0's to these, just use an
		 * unused page.  Of course,
		 * rcvhdraddr poपूर्णांकs to a large chunk of memory, so this
		 * could still trash things, but at least it won't trash
		 * page 0, and by disabling the ctxt, it should stop "soon",
		 * even अगर a packet or two is in alपढ़ोy in flight after we
		 * disabled the ctxt.  Only 6120 has this issue.
		 */
		अगर (ctxt >= 0) अणु
			qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdrtailaddr, ctxt,
					    dd->cspec->dummy_hdrq_phys);
			qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdraddr, ctxt,
					    dd->cspec->dummy_hdrq_phys);
		पूर्ण अन्यथा अणु
			अचिन्हित i;

			क्रम (i = 0; i < dd->cfgctxts; i++) अणु
				qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdrtailaddr,
					    i, dd->cspec->dummy_hdrq_phys);
				qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdraddr,
					    i, dd->cspec->dummy_hdrq_phys);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);
पूर्ण

/*
 * Modअगरy the SENDCTRL रेजिस्टर in chip-specअगरic way. This
 * is a function there may be multiple such रेजिस्टरs with
 * slightly dअगरferent layouts. Only operations actually used
 * are implemented yet.
 * Chip requires no back-back sendctrl ग_लिखोs, so ग_लिखो
 * scratch रेजिस्टर after writing sendctrl
 */
अटल व्योम sendctrl_6120_mod(काष्ठा qib_pportdata *ppd, u32 op)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 पंचांगp_dd_sendctrl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);

	/* First the ones that are "sticky", saved in shaकरोw */
	अगर (op & QIB_SENDCTRL_CLEAR)
		dd->sendctrl = 0;
	अगर (op & QIB_SENDCTRL_SEND_DIS)
		dd->sendctrl &= ~SYM_MASK(SendCtrl, PIOEnable);
	अन्यथा अगर (op & QIB_SENDCTRL_SEND_ENB)
		dd->sendctrl |= SYM_MASK(SendCtrl, PIOEnable);
	अगर (op & QIB_SENDCTRL_AVAIL_DIS)
		dd->sendctrl &= ~SYM_MASK(SendCtrl, PIOBufAvailUpd);
	अन्यथा अगर (op & QIB_SENDCTRL_AVAIL_ENB)
		dd->sendctrl |= SYM_MASK(SendCtrl, PIOBufAvailUpd);

	अगर (op & QIB_SENDCTRL_DISARM_ALL) अणु
		u32 i, last;

		पंचांगp_dd_sendctrl = dd->sendctrl;
		/*
		 * disarm any that are not yet launched, disabling sends
		 * and updates until करोne.
		 */
		last = dd->piobcnt2k + dd->piobcnt4k;
		पंचांगp_dd_sendctrl &=
			~(SYM_MASK(SendCtrl, PIOEnable) |
			  SYM_MASK(SendCtrl, PIOBufAvailUpd));
		क्रम (i = 0; i < last; i++) अणु
			qib_ग_लिखो_kreg(dd, kr_sendctrl, पंचांगp_dd_sendctrl |
				       SYM_MASK(SendCtrl, Disarm) | i);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		पूर्ण
	पूर्ण

	पंचांगp_dd_sendctrl = dd->sendctrl;

	अगर (op & QIB_SENDCTRL_FLUSH)
		पंचांगp_dd_sendctrl |= SYM_MASK(SendCtrl, Abort);
	अगर (op & QIB_SENDCTRL_DISARM)
		पंचांगp_dd_sendctrl |= SYM_MASK(SendCtrl, Disarm) |
			((op & QIB_6120_SendCtrl_DisarmPIOBuf_RMASK) <<
			 SYM_LSB(SendCtrl, DisarmPIOBuf));
	अगर (op & QIB_SENDCTRL_AVAIL_BLIP)
		पंचांगp_dd_sendctrl &= ~SYM_MASK(SendCtrl, PIOBufAvailUpd);

	qib_ग_लिखो_kreg(dd, kr_sendctrl, पंचांगp_dd_sendctrl);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);

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

/**
 * qib_portcntr_6120 - पढ़ो a per-port counter
 * @ppd: the qlogic_ib device
 * @reg: the counter to snapshot
 */
अटल u64 qib_portcntr_6120(काष्ठा qib_pportdata *ppd, u32 reg)
अणु
	u64 ret = 0ULL;
	काष्ठा qib_devdata *dd = ppd->dd;
	u16 creg;
	/* 0xffff क्रम unimplemented or synthesized counters */
	अटल स्थिर u16 xlator[] = अणु
		[QIBPORTCNTR_PKTSEND] = cr_pktsend,
		[QIBPORTCNTR_WORDSEND] = cr_wordsend,
		[QIBPORTCNTR_PSXMITDATA] = 0xffff,
		[QIBPORTCNTR_PSXMITPKTS] = 0xffff,
		[QIBPORTCNTR_PSXMITWAIT] = 0xffff,
		[QIBPORTCNTR_SENDSTALL] = cr_sendstall,
		[QIBPORTCNTR_PKTRCV] = cr_pktrcv,
		[QIBPORTCNTR_PSRCVDATA] = 0xffff,
		[QIBPORTCNTR_PSRCVPKTS] = 0xffff,
		[QIBPORTCNTR_RCVEBP] = cr_rcvebp,
		[QIBPORTCNTR_RCVOVFL] = cr_rcvovfl,
		[QIBPORTCNTR_WORDRCV] = cr_wordrcv,
		[QIBPORTCNTR_RXDROPPKT] = cr_rxdroppkt,
		[QIBPORTCNTR_RXLOCALPHYERR] = 0xffff,
		[QIBPORTCNTR_RXVLERR] = 0xffff,
		[QIBPORTCNTR_ERRICRC] = cr_erricrc,
		[QIBPORTCNTR_ERRVCRC] = cr_errvcrc,
		[QIBPORTCNTR_ERRLPCRC] = cr_errlpcrc,
		[QIBPORTCNTR_BADFORMAT] = cr_badक्रमmat,
		[QIBPORTCNTR_ERR_RLEN] = cr_err_rlen,
		[QIBPORTCNTR_IBSYMBOLERR] = cr_ibsymbolerr,
		[QIBPORTCNTR_INVALIDRLEN] = cr_invalidrlen,
		[QIBPORTCNTR_UNSUPVL] = cr_txunsupvl,
		[QIBPORTCNTR_EXCESSBUFOVFL] = 0xffff,
		[QIBPORTCNTR_ERRLINK] = cr_errlink,
		[QIBPORTCNTR_IBLINKDOWN] = cr_iblinkकरोwn,
		[QIBPORTCNTR_IBLINKERRRECOV] = cr_iblinkerrrecov,
		[QIBPORTCNTR_LLI] = 0xffff,
		[QIBPORTCNTR_PSINTERVAL] = 0xffff,
		[QIBPORTCNTR_PSSTART] = 0xffff,
		[QIBPORTCNTR_PSSTAT] = 0xffff,
		[QIBPORTCNTR_VL15PKTDROP] = 0xffff,
		[QIBPORTCNTR_ERRPKEY] = cr_errpkey,
		[QIBPORTCNTR_KHDROVFL] = 0xffff,
	पूर्ण;

	अगर (reg >= ARRAY_SIZE(xlator)) अणु
		qib_devinfo(ppd->dd->pcidev,
			 "Unimplemented portcounter %u\n", reg);
		जाओ करोne;
	पूर्ण
	creg = xlator[reg];

	/* handle counters requests not implemented as chip counters */
	अगर (reg == QIBPORTCNTR_LLI)
		ret = dd->cspec->lli_errs;
	अन्यथा अगर (reg == QIBPORTCNTR_EXCESSBUFOVFL)
		ret = dd->cspec->overrun_thresh_errs;
	अन्यथा अगर (reg == QIBPORTCNTR_KHDROVFL) अणु
		पूर्णांक i;

		/* sum over all kernel contexts */
		क्रम (i = 0; i < dd->first_user_ctxt; i++)
			ret += पढ़ो_6120_creg32(dd, cr_portovfl + i);
	पूर्ण अन्यथा अगर (reg == QIBPORTCNTR_PSSTAT)
		ret = dd->cspec->pma_sample_status;
	अगर (creg == 0xffff)
		जाओ करोne;

	/*
	 * only fast incrementing counters are 64bit; use 32 bit पढ़ोs to
	 * aव्योम two independent पढ़ोs when on opteron
	 */
	अगर (creg == cr_wordsend || creg == cr_wordrcv ||
	    creg == cr_pktsend || creg == cr_pktrcv)
		ret = पढ़ो_6120_creg(dd, creg);
	अन्यथा
		ret = पढ़ो_6120_creg32(dd, creg);
	अगर (creg == cr_ibsymbolerr) अणु
		अगर (dd->cspec->ibdeltainprog)
			ret -= ret - dd->cspec->ibsymsnap;
		ret -= dd->cspec->ibsymdelta;
	पूर्ण अन्यथा अगर (creg == cr_iblinkerrrecov) अणु
		अगर (dd->cspec->ibdeltainprog)
			ret -= ret - dd->cspec->iblnkerrsnap;
		ret -= dd->cspec->iblnkerrdelta;
	पूर्ण
	अगर (reg == QIBPORTCNTR_RXDROPPKT) /* add special हालd count */
		ret += dd->cspec->rxfc_unsupvl_errs;

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
 * cntr6120indices contains the corresponding रेजिस्टर indices.
 */
अटल स्थिर अक्षर cntr6120names[] =
	"Interrupts\n"
	"HostBusStall\n"
	"E RxTIDFull\n"
	"RxTIDInvalid\n"
	"Ctxt0EgrOvfl\n"
	"Ctxt1EgrOvfl\n"
	"Ctxt2EgrOvfl\n"
	"Ctxt3EgrOvfl\n"
	"Ctxt4EgrOvfl\n";

अटल स्थिर माप_प्रकार cntr6120indices[] = अणु
	cr_lbपूर्णांक,
	cr_lbflowstall,
	cr_errtidfull,
	cr_errtidvalid,
	cr_portovfl + 0,
	cr_portovfl + 1,
	cr_portovfl + 2,
	cr_portovfl + 3,
	cr_portovfl + 4,
पूर्ण;

/*
 * same as cntr6120names and cntr6120indices, but क्रम port-specअगरic counters.
 * portcntr6120indices is somewhat complicated by some रेजिस्टरs needing
 * adjusपंचांगents of various kinds, and those are ORed with _PORT_VIRT_FLAG
 */
अटल स्थिर अक्षर portcntr6120names[] =
	"TxPkt\n"
	"TxFlowPkt\n"
	"TxWords\n"
	"RxPkt\n"
	"RxFlowPkt\n"
	"RxWords\n"
	"TxFlowStall\n"
	"E IBStatusChng\n"
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
	;

#घोषणा _PORT_VIRT_FLAG 0x8000 /* "virtual", need adjusपंचांगents */
अटल स्थिर माप_प्रकार portcntr6120indices[] = अणु
	QIBPORTCNTR_PKTSEND | _PORT_VIRT_FLAG,
	cr_pktsendflow,
	QIBPORTCNTR_WORDSEND | _PORT_VIRT_FLAG,
	QIBPORTCNTR_PKTRCV | _PORT_VIRT_FLAG,
	cr_pktrcvflowctrl,
	QIBPORTCNTR_WORDRCV | _PORT_VIRT_FLAG,
	QIBPORTCNTR_SENDSTALL | _PORT_VIRT_FLAG,
	cr_ibstatuschange,
	QIBPORTCNTR_IBLINKDOWN | _PORT_VIRT_FLAG,
	QIBPORTCNTR_IBLINKERRRECOV | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERRLINK | _PORT_VIRT_FLAG,
	QIBPORTCNTR_IBSYMBOLERR | _PORT_VIRT_FLAG,
	QIBPORTCNTR_LLI | _PORT_VIRT_FLAG,
	QIBPORTCNTR_BADFORMAT | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERR_RLEN | _PORT_VIRT_FLAG,
	QIBPORTCNTR_RCVOVFL | _PORT_VIRT_FLAG,
	QIBPORTCNTR_RCVEBP | _PORT_VIRT_FLAG,
	cr_rcvflowctrl_err,
	QIBPORTCNTR_ERRICRC | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERRLPCRC | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERRVCRC | _PORT_VIRT_FLAG,
	QIBPORTCNTR_INVALIDRLEN | _PORT_VIRT_FLAG,
	QIBPORTCNTR_ERRPKEY | _PORT_VIRT_FLAG,
	QIBPORTCNTR_RXDROPPKT | _PORT_VIRT_FLAG,
	cr_invalidslen,
	cr_senddropped,
	cr_errslen,
	cr_sendunderrun,
	cr_txunsupvl,
पूर्ण;

/* करो all the setup to make the counter पढ़ोs efficient later */
अटल व्योम init_6120_cntrnames(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक i, j = 0;
	अक्षर *s;

	क्रम (i = 0, s = (अक्षर *)cntr6120names; s && j <= dd->cfgctxts;
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
		dd->cspec->cntrnamelen = माप(cntr6120names) - 1;
	अन्यथा
		dd->cspec->cntrnamelen = 1 + s - cntr6120names;
	dd->cspec->cntrs = kदो_स्मृति_array(dd->cspec->ncntrs, माप(u64),
					 GFP_KERNEL);

	क्रम (i = 0, s = (अक्षर *)portcntr6120names; s; i++)
		s = म_अक्षर(s + 1, '\n');
	dd->cspec->nportcntrs = i - 1;
	dd->cspec->portcntrnamelen = माप(portcntr6120names) - 1;
	dd->cspec->portcntrs = kदो_स्मृति_array(dd->cspec->nportcntrs,
					     माप(u64),
					     GFP_KERNEL);
पूर्ण

अटल u32 qib_पढ़ो_6120cntrs(काष्ठा qib_devdata *dd, loff_t pos, अक्षर **namep,
			      u64 **cntrp)
अणु
	u32 ret;

	अगर (namep) अणु
		ret = dd->cspec->cntrnamelen;
		अगर (pos >= ret)
			ret = 0; /* final पढ़ो after getting everything */
		अन्यथा
			*namep = (अक्षर *)cntr6120names;
	पूर्ण अन्यथा अणु
		u64 *cntr = dd->cspec->cntrs;
		पूर्णांक i;

		ret = dd->cspec->ncntrs * माप(u64);
		अगर (!cntr || pos >= ret) अणु
			/* everything पढ़ो, or couldn't get memory */
			ret = 0;
			जाओ करोne;
		पूर्ण
		अगर (pos >= ret) अणु
			ret = 0; /* final पढ़ो after getting everything */
			जाओ करोne;
		पूर्ण
		*cntrp = cntr;
		क्रम (i = 0; i < dd->cspec->ncntrs; i++)
			*cntr++ = पढ़ो_6120_creg32(dd, cntr6120indices[i]);
	पूर्ण
करोne:
	वापस ret;
पूर्ण

अटल u32 qib_पढ़ो_6120portcntrs(काष्ठा qib_devdata *dd, loff_t pos, u32 port,
				  अक्षर **namep, u64 **cntrp)
अणु
	u32 ret;

	अगर (namep) अणु
		ret = dd->cspec->portcntrnamelen;
		अगर (pos >= ret)
			ret = 0; /* final पढ़ो after getting everything */
		अन्यथा
			*namep = (अक्षर *)portcntr6120names;
	पूर्ण अन्यथा अणु
		u64 *cntr = dd->cspec->portcntrs;
		काष्ठा qib_pportdata *ppd = &dd->pport[port];
		पूर्णांक i;

		ret = dd->cspec->nportcntrs * माप(u64);
		अगर (!cntr || pos >= ret) अणु
			/* everything पढ़ो, or couldn't get memory */
			ret = 0;
			जाओ करोne;
		पूर्ण
		*cntrp = cntr;
		क्रम (i = 0; i < dd->cspec->nportcntrs; i++) अणु
			अगर (portcntr6120indices[i] & _PORT_VIRT_FLAG)
				*cntr++ = qib_portcntr_6120(ppd,
					portcntr6120indices[i] &
					~_PORT_VIRT_FLAG);
			अन्यथा
				*cntr++ = पढ़ो_6120_creg32(dd,
					   portcntr6120indices[i]);
		पूर्ण
	पूर्ण
करोne:
	वापस ret;
पूर्ण

अटल व्योम qib_chk_6120_errormask(काष्ठा qib_devdata *dd)
अणु
	अटल u32 fixed;
	u32 ctrl;
	अचिन्हित दीर्घ errormask;
	अचिन्हित दीर्घ hwerrs;

	अगर (!dd->cspec->errormask || !(dd->flags & QIB_INITTED))
		वापस;

	errormask = qib_पढ़ो_kreg64(dd, kr_errmask);

	अगर (errormask == dd->cspec->errormask)
		वापस;
	fixed++;

	hwerrs = qib_पढ़ो_kreg64(dd, kr_hwerrstatus);
	ctrl = qib_पढ़ो_kreg32(dd, kr_control);

	qib_ग_लिखो_kreg(dd, kr_errmask,
		dd->cspec->errormask);

	अगर ((hwerrs & dd->cspec->hwerrmask) ||
	    (ctrl & QLOGIC_IB_C_FREEZEMODE)) अणु
		qib_ग_लिखो_kreg(dd, kr_hwerrclear, 0ULL);
		qib_ग_लिखो_kreg(dd, kr_errclear, 0ULL);
		/* क्रमce re-पूर्णांकerrupt of pending events, just in हाल */
		qib_ग_लिखो_kreg(dd, kr_पूर्णांकclear, 0ULL);
		qib_devinfo(dd->pcidev,
			 "errormask fixed(%u) %lx->%lx, ctrl %x hwerr %lx\n",
			 fixed, errormask, (अचिन्हित दीर्घ)dd->cspec->errormask,
			 ctrl, hwerrs);
	पूर्ण
पूर्ण

/**
 * qib_get_6120_faststats - get word counters from chip beक्रमe they overflow
 * @t: contains a poपूर्णांकer to the qlogic_ib device qib_devdata
 *
 * This needs more work; in particular, decision on whether we really
 * need traffic_wds करोne the way it is
 * called from add_समयr
 */
अटल व्योम qib_get_6120_faststats(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_devdata *dd = from_समयr(dd, t, stats_समयr);
	काष्ठा qib_pportdata *ppd = dd->pport;
	अचिन्हित दीर्घ flags;
	u64 traffic_wds;

	/*
	 * करोn't access the chip जबतक running diags, or memory diags can
	 * fail
	 */
	अगर (!(dd->flags & QIB_INITTED) || dd->diag_client)
		/* but re-arm the समयr, क्रम diags हाल; won't hurt other */
		जाओ करोne;

	/*
	 * We now try to मुख्यtain an activity समयr, based on traffic
	 * exceeding a threshold, so we need to check the word-counts
	 * even अगर they are 64-bit.
	 */
	traffic_wds = qib_portcntr_6120(ppd, cr_wordsend) +
		qib_portcntr_6120(ppd, cr_wordrcv);
	spin_lock_irqsave(&dd->eep_st_lock, flags);
	traffic_wds -= dd->traffic_wds;
	dd->traffic_wds += traffic_wds;
	spin_unlock_irqrestore(&dd->eep_st_lock, flags);

	qib_chk_6120_errormask(dd);
करोne:
	mod_समयr(&dd->stats_समयr, jअगरfies + HZ * ACTIVITY_TIMER);
पूर्ण

/* no पूर्णांकerrupt fallback क्रम these chips */
अटल पूर्णांक qib_6120_noपूर्णांकr_fallback(काष्ठा qib_devdata *dd)
अणु
	वापस 0;
पूर्ण

/*
 * reset the XGXS (between serdes and IBC).  Slightly less पूर्णांकrusive
 * than resetting the IBC or बाह्यal link state, and useful in some
 * हालs to cause some retraining.  To करो this right, we reset IBC
 * as well.
 */
अटल व्योम qib_6120_xgxs_reset(काष्ठा qib_pportdata *ppd)
अणु
	u64 val, prev_val;
	काष्ठा qib_devdata *dd = ppd->dd;

	prev_val = qib_पढ़ो_kreg64(dd, kr_xgxs_cfg);
	val = prev_val | QLOGIC_IB_XGXS_RESET;
	prev_val &= ~QLOGIC_IB_XGXS_RESET; /* be sure */
	qib_ग_लिखो_kreg(dd, kr_control,
		       dd->control & ~QLOGIC_IB_C_LINKENABLE);
	qib_ग_लिखो_kreg(dd, kr_xgxs_cfg, val);
	qib_पढ़ो_kreg32(dd, kr_scratch);
	qib_ग_लिखो_kreg(dd, kr_xgxs_cfg, prev_val);
	qib_ग_लिखो_kreg(dd, kr_control, dd->control);
पूर्ण

अटल पूर्णांक qib_6120_get_ib_cfg(काष्ठा qib_pportdata *ppd, पूर्णांक which)
अणु
	पूर्णांक ret;

	चयन (which) अणु
	हाल QIB_IB_CFG_LWID:
		ret = ppd->link_width_active;
		अवरोध;

	हाल QIB_IB_CFG_SPD:
		ret = ppd->link_speed_active;
		अवरोध;

	हाल QIB_IB_CFG_LWID_ENB:
		ret = ppd->link_width_enabled;
		अवरोध;

	हाल QIB_IB_CFG_SPD_ENB:
		ret = ppd->link_speed_enabled;
		अवरोध;

	हाल QIB_IB_CFG_OP_VLS:
		ret = ppd->vls_operational;
		अवरोध;

	हाल QIB_IB_CFG_VL_HIGH_CAP:
		ret = 0;
		अवरोध;

	हाल QIB_IB_CFG_VL_LOW_CAP:
		ret = 0;
		अवरोध;

	हाल QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		ret = SYM_FIELD(ppd->dd->cspec->ibcctrl, IBCCtrl,
				OverrunThreshold);
		अवरोध;

	हाल QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		ret = SYM_FIELD(ppd->dd->cspec->ibcctrl, IBCCtrl,
				PhyerrThreshold);
		अवरोध;

	हाल QIB_IB_CFG_LINKDEFAULT: /* IB link शेष (sleep/poll) */
		/* will only take effect when the link state changes */
		ret = (ppd->dd->cspec->ibcctrl &
		       SYM_MASK(IBCCtrl, LinkDownDefaultState)) ?
			IB_LINKINITCMD_SLEEP : IB_LINKINITCMD_POLL;
		अवरोध;

	हाल QIB_IB_CFG_HRTBT: /* Get Heartbeat off/enable/स्वतः */
		ret = 0; /* no heartbeat on this chip */
		अवरोध;

	हाल QIB_IB_CFG_PMA_TICKS:
		ret = 250; /* 1 usec. */
		अवरोध;

	शेष:
		ret =  -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * We assume range checking is alपढ़ोy करोne, अगर needed.
 */
अटल पूर्णांक qib_6120_set_ib_cfg(काष्ठा qib_pportdata *ppd, पूर्णांक which, u32 val)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक ret = 0;
	u64 val64;
	u16 lcmd, licmd;

	चयन (which) अणु
	हाल QIB_IB_CFG_LWID_ENB:
		ppd->link_width_enabled = val;
		अवरोध;

	हाल QIB_IB_CFG_SPD_ENB:
		ppd->link_speed_enabled = val;
		अवरोध;

	हाल QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		val64 = SYM_FIELD(dd->cspec->ibcctrl, IBCCtrl,
				  OverrunThreshold);
		अगर (val64 != val) अणु
			dd->cspec->ibcctrl &=
				~SYM_MASK(IBCCtrl, OverrunThreshold);
			dd->cspec->ibcctrl |= (u64) val <<
				SYM_LSB(IBCCtrl, OverrunThreshold);
			qib_ग_लिखो_kreg(dd, kr_ibcctrl, dd->cspec->ibcctrl);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		पूर्ण
		अवरोध;

	हाल QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		val64 = SYM_FIELD(dd->cspec->ibcctrl, IBCCtrl,
				  PhyerrThreshold);
		अगर (val64 != val) अणु
			dd->cspec->ibcctrl &=
				~SYM_MASK(IBCCtrl, PhyerrThreshold);
			dd->cspec->ibcctrl |= (u64) val <<
				SYM_LSB(IBCCtrl, PhyerrThreshold);
			qib_ग_लिखो_kreg(dd, kr_ibcctrl, dd->cspec->ibcctrl);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		पूर्ण
		अवरोध;

	हाल QIB_IB_CFG_PKEYS: /* update pkeys */
		val64 = (u64) ppd->pkeys[0] | ((u64) ppd->pkeys[1] << 16) |
			((u64) ppd->pkeys[2] << 32) |
			((u64) ppd->pkeys[3] << 48);
		qib_ग_लिखो_kreg(dd, kr_partitionkey, val64);
		अवरोध;

	हाल QIB_IB_CFG_LINKDEFAULT: /* IB link शेष (sleep/poll) */
		/* will only take effect when the link state changes */
		अगर (val == IB_LINKINITCMD_POLL)
			dd->cspec->ibcctrl &=
				~SYM_MASK(IBCCtrl, LinkDownDefaultState);
		अन्यथा /* SLEEP */
			dd->cspec->ibcctrl |=
				SYM_MASK(IBCCtrl, LinkDownDefaultState);
		qib_ग_लिखो_kreg(dd, kr_ibcctrl, dd->cspec->ibcctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		अवरोध;

	हाल QIB_IB_CFG_MTU: /* update the MTU in IBC */
		/*
		 * Update our housekeeping variables, and set IBC max
		 * size, same as init code; max IBC is max we allow in
		 * buffer, less the qword pbc, plus 1 क्रम ICRC, in dwords
		 * Set even अगर it's unchanged, prपूर्णांक debug message only
		 * on changes.
		 */
		val = (ppd->ibmaxlen >> 2) + 1;
		dd->cspec->ibcctrl &= ~SYM_MASK(IBCCtrl, MaxPktLen);
		dd->cspec->ibcctrl |= (u64)val <<
			SYM_LSB(IBCCtrl, MaxPktLen);
		qib_ग_लिखो_kreg(dd, kr_ibcctrl, dd->cspec->ibcctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		अवरोध;

	हाल QIB_IB_CFG_LSTATE: /* set the IB link state */
		चयन (val & 0xffff0000) अणु
		हाल IB_LINKCMD_DOWN:
			lcmd = QLOGIC_IB_IBCC_LINKCMD_DOWN;
			अगर (!dd->cspec->ibdeltainprog) अणु
				dd->cspec->ibdeltainprog = 1;
				dd->cspec->ibsymsnap =
					पढ़ो_6120_creg32(dd, cr_ibsymbolerr);
				dd->cspec->iblnkerrsnap =
					पढ़ो_6120_creg32(dd, cr_iblinkerrrecov);
			पूर्ण
			अवरोध;

		हाल IB_LINKCMD_ARMED:
			lcmd = QLOGIC_IB_IBCC_LINKCMD_ARMED;
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
			अवरोध;

		शेष:
			ret = -EINVAL;
			qib_dev_err(dd, "bad linkinitcmd req 0x%x\n",
				    val & 0xffff);
			जाओ bail;
		पूर्ण
		qib_set_ib_6120_lstate(ppd, lcmd, licmd);
		जाओ bail;

	हाल QIB_IB_CFG_HRTBT:
		ret = -EINVAL;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_6120_set_loopback(काष्ठा qib_pportdata *ppd, स्थिर अक्षर *what)
अणु
	पूर्णांक ret = 0;

	अगर (!म_भेदन(what, "ibc", 3)) अणु
		ppd->dd->cspec->ibcctrl |= SYM_MASK(IBCCtrl, Loopback);
		qib_devinfo(ppd->dd->pcidev, "Enabling IB%u:%u IBC loopback\n",
			 ppd->dd->unit, ppd->port);
	पूर्ण अन्यथा अगर (!म_भेदन(what, "off", 3)) अणु
		ppd->dd->cspec->ibcctrl &= ~SYM_MASK(IBCCtrl, Loopback);
		qib_devinfo(ppd->dd->pcidev,
			"Disabling IB%u:%u IBC loopback (normal)\n",
			ppd->dd->unit, ppd->port);
	पूर्ण अन्यथा
		ret = -EINVAL;
	अगर (!ret) अणु
		qib_ग_लिखो_kreg(ppd->dd, kr_ibcctrl, ppd->dd->cspec->ibcctrl);
		qib_ग_लिखो_kreg(ppd->dd, kr_scratch, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम pma_6120_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_chip_specअगरic *cs = from_समयr(cs, t, pma_समयr);
	काष्ठा qib_pportdata *ppd = cs->ppd;
	काष्ठा qib_ibport *ibp = &ppd->ibport_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ibp->rvp.lock, flags);
	अगर (cs->pma_sample_status == IB_PMA_SAMPLE_STATUS_STARTED) अणु
		cs->pma_sample_status = IB_PMA_SAMPLE_STATUS_RUNNING;
		qib_snapshot_counters(ppd, &cs->sword, &cs->rword,
				      &cs->spkts, &cs->rpkts, &cs->xmit_रुको);
		mod_समयr(&cs->pma_समयr,
		      jअगरfies + usecs_to_jअगरfies(ibp->rvp.pma_sample_पूर्णांकerval));
	पूर्ण अन्यथा अगर (cs->pma_sample_status == IB_PMA_SAMPLE_STATUS_RUNNING) अणु
		u64 ta, tb, tc, td, te;

		cs->pma_sample_status = IB_PMA_SAMPLE_STATUS_DONE;
		qib_snapshot_counters(ppd, &ta, &tb, &tc, &td, &te);

		cs->sword = ta - cs->sword;
		cs->rword = tb - cs->rword;
		cs->spkts = tc - cs->spkts;
		cs->rpkts = td - cs->rpkts;
		cs->xmit_रुको = te - cs->xmit_रुको;
	पूर्ण
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);
पूर्ण

/*
 * Note that the caller has the ibp->rvp.lock held.
 */
अटल व्योम qib_set_cntr_6120_sample(काष्ठा qib_pportdata *ppd, u32 पूर्णांकv,
				     u32 start)
अणु
	काष्ठा qib_chip_specअगरic *cs = ppd->dd->cspec;

	अगर (start && पूर्णांकv) अणु
		cs->pma_sample_status = IB_PMA_SAMPLE_STATUS_STARTED;
		mod_समयr(&cs->pma_समयr, jअगरfies + usecs_to_jअगरfies(start));
	पूर्ण अन्यथा अगर (पूर्णांकv) अणु
		cs->pma_sample_status = IB_PMA_SAMPLE_STATUS_RUNNING;
		qib_snapshot_counters(ppd, &cs->sword, &cs->rword,
				      &cs->spkts, &cs->rpkts, &cs->xmit_रुको);
		mod_समयr(&cs->pma_समयr, jअगरfies + usecs_to_jअगरfies(पूर्णांकv));
	पूर्ण अन्यथा अणु
		cs->pma_sample_status = IB_PMA_SAMPLE_STATUS_DONE;
		cs->sword = 0;
		cs->rword = 0;
		cs->spkts = 0;
		cs->rpkts = 0;
		cs->xmit_रुको = 0;
	पूर्ण
पूर्ण

अटल u32 qib_6120_iblink_state(u64 ibcs)
अणु
	u32 state = (u32)SYM_FIELD(ibcs, IBCStatus, LinkState);

	चयन (state) अणु
	हाल IB_6120_L_STATE_INIT:
		state = IB_PORT_INIT;
		अवरोध;
	हाल IB_6120_L_STATE_ARM:
		state = IB_PORT_ARMED;
		अवरोध;
	हाल IB_6120_L_STATE_ACTIVE:
	हाल IB_6120_L_STATE_ACT_DEFER:
		state = IB_PORT_ACTIVE;
		अवरोध;
	शेष:
		fallthrough;
	हाल IB_6120_L_STATE_DOWN:
		state = IB_PORT_DOWN;
		अवरोध;
	पूर्ण
	वापस state;
पूर्ण

/* वापसs the IBTA port state, rather than the IBC link training state */
अटल u8 qib_6120_phys_portstate(u64 ibcs)
अणु
	u8 state = (u8)SYM_FIELD(ibcs, IBCStatus, LinkTrainingState);
	वापस qib_6120_physportstate[state];
पूर्ण

अटल पूर्णांक qib_6120_ib_upकरोwn(काष्ठा qib_pportdata *ppd, पूर्णांक ibup, u64 ibcs)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags &= ~QIBL_IB_FORCE_NOTIFY;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);

	अगर (ibup) अणु
		अगर (ppd->dd->cspec->ibdeltainprog) अणु
			ppd->dd->cspec->ibdeltainprog = 0;
			ppd->dd->cspec->ibsymdelta +=
				पढ़ो_6120_creg32(ppd->dd, cr_ibsymbolerr) -
					ppd->dd->cspec->ibsymsnap;
			ppd->dd->cspec->iblnkerrdelta +=
				पढ़ो_6120_creg32(ppd->dd, cr_iblinkerrrecov) -
					ppd->dd->cspec->iblnkerrsnap;
		पूर्ण
		qib_hol_init(ppd);
	पूर्ण अन्यथा अणु
		ppd->dd->cspec->lli_counter = 0;
		अगर (!ppd->dd->cspec->ibdeltainprog) अणु
			ppd->dd->cspec->ibdeltainprog = 1;
			ppd->dd->cspec->ibsymsnap =
				पढ़ो_6120_creg32(ppd->dd, cr_ibsymbolerr);
			ppd->dd->cspec->iblnkerrsnap =
				पढ़ो_6120_creg32(ppd->dd, cr_iblinkerrrecov);
		पूर्ण
		qib_hol_करोwn(ppd);
	पूर्ण

	qib_6120_setup_setextled(ppd, ibup);

	वापस 0;
पूर्ण

/* Does पढ़ो/modअगरy/ग_लिखो to appropriate रेजिस्टरs to
 * set output and direction bits selected by mask.
 * these are in their canonical postions (e.g. lsb of
 * dir will end up in D48 of extctrl on existing chips).
 * वापसs contents of GP Inमाला_दो.
 */
अटल पूर्णांक gpio_6120_mod(काष्ठा qib_devdata *dd, u32 out, u32 dir, u32 mask)
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

/*
 * Read fundamental info we need to use the chip.  These are
 * the रेजिस्टरs that describe chip capabilities, and are
 * saved in shaकरोw रेजिस्टरs.
 */
अटल व्योम get_6120_chip_params(काष्ठा qib_devdata *dd)
अणु
	u64 val;
	u32 piobufs;
	पूर्णांक mtu;

	dd->uregbase = qib_पढ़ो_kreg32(dd, kr_userregbase);

	dd->rcvtidcnt = qib_पढ़ो_kreg32(dd, kr_rcvtidcnt);
	dd->rcvtidbase = qib_पढ़ो_kreg32(dd, kr_rcvtidbase);
	dd->rcvegrbase = qib_पढ़ो_kreg32(dd, kr_rcvegrbase);
	dd->palign = qib_पढ़ो_kreg32(dd, kr_palign);
	dd->piobufbase = qib_पढ़ो_kreg64(dd, kr_sendpiobufbase);
	dd->pio2k_bufbase = dd->piobufbase & 0xffffffff;

	dd->rcvhdrcnt = qib_पढ़ो_kreg32(dd, kr_rcvegrcnt);

	val = qib_पढ़ो_kreg64(dd, kr_sendpiosize);
	dd->piosize2k = val & ~0U;
	dd->piosize4k = val >> 32;

	mtu = ib_mtu_क्रमागत_to_पूर्णांक(qib_ibmtu);
	अगर (mtu == -1)
		mtu = QIB_DEFAULT_MTU;
	dd->pport->ibmtu = (u32)mtu;

	val = qib_पढ़ो_kreg64(dd, kr_sendpiobufcnt);
	dd->piobcnt2k = val & ~0U;
	dd->piobcnt4k = val >> 32;
	dd->last_pio = dd->piobcnt4k + dd->piobcnt2k - 1;
	/* these may be adjusted in init_chip_wc_pat() */
	dd->pio2kbase = (u32 __iomem *)
		(((अक्षर __iomem *)dd->kregbase) + dd->pio2k_bufbase);
	अगर (dd->piobcnt4k) अणु
		dd->pio4kbase = (u32 __iomem *)
			(((अक्षर __iomem *) dd->kregbase) +
			 (dd->piobufbase >> 32));
		/*
		 * 4K buffers take 2 pages; we use roundup just to be
		 * paranoid; we calculate it once here, rather than on
		 * ever buf allocate
		 */
		dd->align4k = ALIGN(dd->piosize4k, dd->palign);
	पूर्ण

	piobufs = dd->piobcnt4k + dd->piobcnt2k;

	dd->pioavregs = ALIGN(piobufs, माप(u64) * BITS_PER_BYTE / 2) /
		(माप(u64) * BITS_PER_BYTE / 2);
पूर्ण

/*
 * The chip base addresses in cspec and cpspec have to be set
 * after possible init_chip_wc_pat(), rather than in
 * get_6120_chip_params(), so split out as separate function
 */
अटल व्योम set_6120_baseaddrs(काष्ठा qib_devdata *dd)
अणु
	u32 cregbase;

	cregbase = qib_पढ़ो_kreg32(dd, kr_counterregbase);
	dd->cspec->cregbase = (u64 __iomem *)
		((अक्षर __iomem *) dd->kregbase + cregbase);

	dd->egrtidbase = (u64 __iomem *)
		((अक्षर __iomem *) dd->kregbase + dd->rcvegrbase);
पूर्ण

/*
 * Write the final few रेजिस्टरs that depend on some of the
 * init setup.  Done late in init, just beक्रमe bringing up
 * the serdes.
 */
अटल पूर्णांक qib_late_6120_initreg(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret = 0;
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
	वापस ret;
पूर्ण

अटल पूर्णांक init_6120_variables(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret = 0;
	काष्ठा qib_pportdata *ppd;
	u32 sbufs;

	ppd = (काष्ठा qib_pportdata *)(dd + 1);
	dd->pport = ppd;
	dd->num_pports = 1;

	dd->cspec = (काष्ठा qib_chip_specअगरic *)(ppd + dd->num_pports);
	dd->cspec->ppd = ppd;
	ppd->cpspec = शून्य; /* not used in this chip */

	spin_lock_init(&dd->cspec->kernel_tid_lock);
	spin_lock_init(&dd->cspec->user_tid_lock);
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

	dd->majrev = (u8) SYM_FIELD(dd->revision, Revision_R,
				    ChipRevMajor);
	dd->minrev = (u8) SYM_FIELD(dd->revision, Revision_R,
				    ChipRevMinor);

	get_6120_chip_params(dd);
	pe_boardname(dd); /* fill in boardname */

	/*
	 * GPIO bits क्रम TWSI data and घड़ी,
	 * used क्रम serial EEPROM.
	 */
	dd->gpio_sda_num = _QIB_GPIO_SDA_NUM;
	dd->gpio_scl_num = _QIB_GPIO_SCL_NUM;
	dd->twsi_eeprom_dev = QIB_TWSI_NO_DEV;

	अगर (qib_unordered_wc())
		dd->flags |= QIB_PIO_FLUSH_WC;

	ret = qib_init_pportdata(ppd, dd, 0, 1);
	अगर (ret)
		जाओ bail;
	ppd->link_width_supported = IB_WIDTH_1X | IB_WIDTH_4X;
	ppd->link_speed_supported = QIB_IB_SDR;
	ppd->link_width_enabled = IB_WIDTH_4X;
	ppd->link_speed_enabled = ppd->link_speed_supported;
	/* these can't change क्रम this chip, so set once */
	ppd->link_width_active = ppd->link_width_enabled;
	ppd->link_speed_active = ppd->link_speed_enabled;
	ppd->vls_supported = IB_VL_VL0;
	ppd->vls_operational = ppd->vls_supported;

	dd->rcvhdrentsize = QIB_RCVHDR_ENTSIZE;
	dd->rcvhdrsize = QIB_DFLT_RCVHDRSIZE;
	dd->rhf_offset = 0;

	/* we always allocate at least 2048 bytes क्रम eager buffers */
	ret = ib_mtu_क्रमागत_to_पूर्णांक(qib_ibmtu);
	dd->rcvegrbufsize = ret != -1 ? max(ret, 2048) : QIB_DEFAULT_MTU;
	dd->rcvegrbufsize_shअगरt = ilog2(dd->rcvegrbufsize);

	qib_6120_tidढाँचा(dd);

	/*
	 * We can request a receive पूर्णांकerrupt क्रम 1 or
	 * more packets from current offset.  For now, we set this
	 * up क्रम a single packet.
	 */
	dd->rhdrhead_पूर्णांकr_off = 1ULL << 32;

	/* setup the stats समयr; the add_समयr is करोne at end of init */
	समयr_setup(&dd->stats_समयr, qib_get_6120_faststats, 0);
	समयr_setup(&dd->cspec->pma_समयr, pma_6120_समयr, 0);

	dd->ureg_align = qib_पढ़ो_kreg32(dd, kr_palign);

	dd->piosize2kmax_dwords = dd->piosize2k >> 2;
	qib_6120_config_ctxts(dd);
	qib_set_ctxtcnt(dd);

	ret = init_chip_wc_pat(dd, 0);
	अगर (ret)
		जाओ bail;
	set_6120_baseaddrs(dd); /* set chip access poपूर्णांकers now */

	ret = 0;
	अगर (qib_mini_init)
		जाओ bail;

	qib_num_cfg_vls = 1; /* अगर any 6120's, only one VL */

	ret = qib_create_ctxts(dd);
	init_6120_cntrnames(dd);

	/* use all of 4KB buffers क्रम the kernel, otherwise 16 */
	sbufs = dd->piobcnt4k ?  dd->piobcnt4k : 16;

	dd->lastctxt_piobuf = dd->piobcnt2k + dd->piobcnt4k - sbufs;
	dd->pbufsctxt = dd->lastctxt_piobuf /
		(dd->cfgctxts - dd->first_user_ctxt);

	अगर (ret)
		जाओ bail;
bail:
	वापस ret;
पूर्ण

/*
 * For this chip, we want to use the same buffer every समय
 * when we are trying to bring the link up (they are always VL15
 * packets).  At that link state the packet should always go out immediately
 * (or at least be discarded at the tx पूर्णांकerface अगर the link is करोwn).
 * If it करोesn't, and the buffer isn't available, that means some other
 * sender has gotten ahead of us, and is preventing our packet from going
 * out.  In that हाल, we flush all packets, and try again.  If that still
 * fails, we fail the request, and hope things work the next समय around.
 *
 * We करोn't need very complicated heuristics on whether the packet had
 * समय to go out or not, since even at SDR 1X, it goes out in very लघु
 * समय periods, covered by the chip पढ़ोs करोne here and as part of the
 * flush.
 */
अटल u32 __iomem *get_6120_link_buf(काष्ठा qib_pportdata *ppd, u32 *bnum)
अणु
	u32 __iomem *buf;
	u32 lbuf = ppd->dd->piobcnt2k + ppd->dd->piobcnt4k - 1;

	/*
	 * always blip to get avail list updated, since it's almost
	 * always needed, and is fairly cheap.
	 */
	sendctrl_6120_mod(ppd->dd->pport, QIB_SENDCTRL_AVAIL_BLIP);
	qib_पढ़ो_kreg64(ppd->dd, kr_scratch); /* extra chip flush */
	buf = qib_माला_लोendbuf_range(ppd->dd, bnum, lbuf, lbuf);
	अगर (buf)
		जाओ करोne;

	sendctrl_6120_mod(ppd, QIB_SENDCTRL_DISARM_ALL | QIB_SENDCTRL_FLUSH |
			  QIB_SENDCTRL_AVAIL_BLIP);
	ppd->dd->upd_pio_shaकरोw  = 1; /* update our idea of what's busy */
	qib_पढ़ो_kreg64(ppd->dd, kr_scratch); /* extra chip flush */
	buf = qib_माला_लोendbuf_range(ppd->dd, bnum, lbuf, lbuf);
करोne:
	वापस buf;
पूर्ण

अटल u32 __iomem *qib_6120_माला_लोendbuf(काष्ठा qib_pportdata *ppd, u64 pbc,
					u32 *pbufnum)
अणु
	u32 first, last, plen = pbc & QIB_PBC_LENGTH_MASK;
	काष्ठा qib_devdata *dd = ppd->dd;
	u32 __iomem *buf;

	अगर (((pbc >> 32) & PBC_6120_VL15_SEND_CTRL) &&
		!(ppd->lflags & (QIBL_IB_AUTONEG_INPROG | QIBL_LINKACTIVE)))
		buf = get_6120_link_buf(ppd, pbufnum);
	अन्यथा अणु

		अगर ((plen + 1) > dd->piosize2kmax_dwords)
			first = dd->piobcnt2k;
		अन्यथा
			first = 0;
		/* try 4k अगर all 2k busy, so same last क्रम both sizes */
		last = dd->piobcnt2k + dd->piobcnt4k - 1;
		buf = qib_माला_लोendbuf_range(dd, pbufnum, first, last);
	पूर्ण
	वापस buf;
पूर्ण

अटल पूर्णांक init_sdma_6120_regs(काष्ठा qib_pportdata *ppd)
अणु
	वापस -ENODEV;
पूर्ण

अटल u16 qib_sdma_6120_gethead(काष्ठा qib_pportdata *ppd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक qib_sdma_6120_busy(काष्ठा qib_pportdata *ppd)
अणु
	वापस 0;
पूर्ण

अटल व्योम qib_sdma_update_6120_tail(काष्ठा qib_pportdata *ppd, u16 tail)
अणु
पूर्ण

अटल व्योम qib_6120_sdma_sendctrl(काष्ठा qib_pportdata *ppd, अचिन्हित op)
अणु
पूर्ण

अटल व्योम qib_sdma_set_6120_desc_cnt(काष्ठा qib_pportdata *ppd, अचिन्हित cnt)
अणु
पूर्ण

/*
 * the pbc करोesn't need a VL15 indicator, but we need it क्रम link_buf.
 * The chip ignores the bit अगर set.
 */
अटल u32 qib_6120_setpbc_control(काष्ठा qib_pportdata *ppd, u32 plen,
				   u8 srate, u8 vl)
अणु
	वापस vl == 15 ? PBC_6120_VL15_SEND_CTRL : 0;
पूर्ण

अटल व्योम qib_6120_initvl15_bufs(काष्ठा qib_devdata *dd)
अणु
पूर्ण

अटल व्योम qib_6120_init_ctxt(काष्ठा qib_ctxtdata *rcd)
अणु
	rcd->rcvegrcnt = rcd->dd->rcvhdrcnt;
	rcd->rcvegr_tid_base = rcd->ctxt * rcd->rcvegrcnt;
पूर्ण

अटल व्योम qib_6120_txchk_change(काष्ठा qib_devdata *dd, u32 start,
	u32 len, u32 avail, काष्ठा qib_ctxtdata *rcd)
अणु
पूर्ण

अटल व्योम ग_लिखोscratch(काष्ठा qib_devdata *dd, u32 val)
अणु
	(व्योम) qib_ग_लिखो_kreg(dd, kr_scratch, val);
पूर्ण

अटल पूर्णांक qib_6120_tempsense_rd(काष्ठा qib_devdata *dd, पूर्णांक regnum)
अणु
	वापस -ENXIO;
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
अटल पूर्णांक qib_6120_notअगरy_dca(काष्ठा qib_devdata *dd, अचिन्हित दीर्घ event)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Dummy function, as 6120 boards never disable EEPROM Write */
अटल पूर्णांक qib_6120_eeprom_wen(काष्ठा qib_devdata *dd, पूर्णांक wen)
अणु
	वापस 1;
पूर्ण

/**
 * qib_init_iba6120_funcs - set up the chip-specअगरic function poपूर्णांकers
 * @pdev: pci_dev of the qlogic_ib device
 * @ent: pci_device_id matching this chip
 *
 * This is global, and is called directly at init to set up the
 * chip-specअगरic function poपूर्णांकers क्रम later use.
 *
 * It also allocates/partially-inits the qib_devdata काष्ठा क्रम
 * this device.
 */
काष्ठा qib_devdata *qib_init_iba6120_funcs(काष्ठा pci_dev *pdev,
					   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा qib_devdata *dd;
	पूर्णांक ret;

	dd = qib_alloc_devdata(pdev, माप(काष्ठा qib_pportdata) +
			       माप(काष्ठा qib_chip_specअगरic));
	अगर (IS_ERR(dd))
		जाओ bail;

	dd->f_bringup_serdes    = qib_6120_bringup_serdes;
	dd->f_cleanup           = qib_6120_setup_cleanup;
	dd->f_clear_tids        = qib_6120_clear_tids;
	dd->f_मुक्त_irq          = qib_मुक्त_irq;
	dd->f_get_base_info     = qib_6120_get_base_info;
	dd->f_get_msgheader     = qib_6120_get_msgheader;
	dd->f_माला_लोendbuf        = qib_6120_माला_लोendbuf;
	dd->f_gpio_mod          = gpio_6120_mod;
	dd->f_eeprom_wen	= qib_6120_eeprom_wen;
	dd->f_hdrqempty         = qib_6120_hdrqempty;
	dd->f_ib_upकरोwn         = qib_6120_ib_upकरोwn;
	dd->f_init_ctxt         = qib_6120_init_ctxt;
	dd->f_initvl15_bufs     = qib_6120_initvl15_bufs;
	dd->f_पूर्णांकr_fallback     = qib_6120_noपूर्णांकr_fallback;
	dd->f_late_initreg      = qib_late_6120_initreg;
	dd->f_setpbc_control    = qib_6120_setpbc_control;
	dd->f_portcntr          = qib_portcntr_6120;
	dd->f_put_tid           = (dd->minrev >= 2) ?
				      qib_6120_put_tid_2 :
				      qib_6120_put_tid;
	dd->f_quiet_serdes      = qib_6120_quiet_serdes;
	dd->f_rcvctrl           = rcvctrl_6120_mod;
	dd->f_पढ़ो_cntrs        = qib_पढ़ो_6120cntrs;
	dd->f_पढ़ो_portcntrs    = qib_पढ़ो_6120portcntrs;
	dd->f_reset             = qib_6120_setup_reset;
	dd->f_init_sdma_regs    = init_sdma_6120_regs;
	dd->f_sdma_busy         = qib_sdma_6120_busy;
	dd->f_sdma_gethead      = qib_sdma_6120_gethead;
	dd->f_sdma_sendctrl     = qib_6120_sdma_sendctrl;
	dd->f_sdma_set_desc_cnt = qib_sdma_set_6120_desc_cnt;
	dd->f_sdma_update_tail  = qib_sdma_update_6120_tail;
	dd->f_sendctrl          = sendctrl_6120_mod;
	dd->f_set_armlaunch     = qib_set_6120_armlaunch;
	dd->f_set_cntr_sample   = qib_set_cntr_6120_sample;
	dd->f_iblink_state      = qib_6120_iblink_state;
	dd->f_ibphys_portstate  = qib_6120_phys_portstate;
	dd->f_get_ib_cfg        = qib_6120_get_ib_cfg;
	dd->f_set_ib_cfg        = qib_6120_set_ib_cfg;
	dd->f_set_ib_loopback   = qib_6120_set_loopback;
	dd->f_set_पूर्णांकr_state    = qib_6120_set_पूर्णांकr_state;
	dd->f_setextled         = qib_6120_setup_setextled;
	dd->f_txchk_change      = qib_6120_txchk_change;
	dd->f_update_usrhead    = qib_update_6120_usrhead;
	dd->f_wantpiobuf_पूर्णांकr   = qib_wantpiobuf_6120_पूर्णांकr;
	dd->f_xgxs_reset        = qib_6120_xgxs_reset;
	dd->f_ग_लिखोscratch      = ग_लिखोscratch;
	dd->f_tempsense_rd	= qib_6120_tempsense_rd;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	dd->f_notअगरy_dca = qib_6120_notअगरy_dca;
#पूर्ण_अगर
	/*
	 * Do reमुख्यing pcie setup and save pcie values in dd.
	 * Any error prपूर्णांकing is alपढ़ोy करोne by the init code.
	 * On वापस, we have the chip mapped and accessible,
	 * but chip रेजिस्टरs are not set up until start of
	 * init_6120_variables.
	 */
	ret = qib_pcie_ddinit(dd, pdev, ent);
	अगर (ret < 0)
		जाओ bail_मुक्त;

	/* initialize chip-specअगरic variables */
	ret = init_6120_variables(dd);
	अगर (ret)
		जाओ bail_cleanup;

	अगर (qib_mini_init)
		जाओ bail;

	अगर (qib_pcie_params(dd, 8, शून्य))
		qib_dev_err(dd,
			"Failed to setup PCIe or interrupts; continuing anyway\n");
	/* clear diagctrl रेजिस्टर, in हाल diags were running and crashed */
	qib_ग_लिखो_kreg(dd, kr_hwdiagctrl, 0);

	अगर (qib_पढ़ो_kreg64(dd, kr_hwerrstatus) &
	    QLOGIC_IB_HWE_SERDESPLLFAILED)
		qib_ग_लिखो_kreg(dd, kr_hwerrclear,
			       QLOGIC_IB_HWE_SERDESPLLFAILED);

	/* setup पूर्णांकerrupt handler (पूर्णांकerrupt type handled above) */
	qib_setup_6120_पूर्णांकerrupt(dd);
	/* Note that qpn_mask is set by qib_6120_config_ctxts() first */
	qib_6120_init_hwerrors(dd);

	जाओ bail;

bail_cleanup:
	qib_pcie_ddcleanup(dd);
bail_मुक्त:
	qib_मुक्त_devdata(dd);
	dd = ERR_PTR(ret);
bail:
	वापस dd;
पूर्ण
