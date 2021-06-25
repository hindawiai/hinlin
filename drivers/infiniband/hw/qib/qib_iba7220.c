<शैली गुरु>
/*
 * Copyright (c) 2011 - 2017 Intel Corporation.  All rights reserved.
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
 * QLogic_IB 7220 chip (except that specअगरic to the SerDes)
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <rdma/ib_verbs.h>

#समावेश "qib.h"
#समावेश "qib_7220.h"

अटल व्योम qib_setup_7220_setextled(काष्ठा qib_pportdata *, u32);
अटल व्योम qib_7220_handle_hwerrors(काष्ठा qib_devdata *, अक्षर *, माप_प्रकार);
अटल व्योम sendctrl_7220_mod(काष्ठा qib_pportdata *ppd, u32 op);
अटल u32 qib_7220_iblink_state(u64);
अटल u8 qib_7220_phys_portstate(u64);
अटल व्योम qib_sdma_update_7220_tail(काष्ठा qib_pportdata *, u16);
अटल व्योम qib_set_ib_7220_lstate(काष्ठा qib_pportdata *, u16, u16);

/*
 * This file contains almost all the chip-specअगरic रेजिस्टर inक्रमmation and
 * access functions क्रम the QLogic QLogic_IB 7220 PCI-Express chip, with the
 * exception of SerDes support, which in in qib_sd7220.c.
 */

/* Below uses machine-generated qib_chipnum_regs.h file */
#घोषणा KREG_IDX(regname) (QIB_7220_##regname##_OFFS / माप(u64))

/* Use defines to tie machine-generated names to lower-हाल names */
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
#घोषणा kr_hrtbt_guid KREG_IDX(HRTBT_GUID)
#घोषणा kr_hwdiagctrl KREG_IDX(HwDiagCtrl)
#घोषणा kr_hwerrclear KREG_IDX(HwErrClear)
#घोषणा kr_hwerrmask KREG_IDX(HwErrMask)
#घोषणा kr_hwerrstatus KREG_IDX(HwErrStatus)
#घोषणा kr_ibcctrl KREG_IDX(IBCCtrl)
#घोषणा kr_ibcddrctrl KREG_IDX(IBCDDRCtrl)
#घोषणा kr_ibcddrstatus KREG_IDX(IBCDDRStatus)
#घोषणा kr_ibcstatus KREG_IDX(IBCStatus)
#घोषणा kr_ibserdesctrl KREG_IDX(IBSerDesCtrl)
#घोषणा kr_पूर्णांकclear KREG_IDX(IntClear)
#घोषणा kr_पूर्णांकmask KREG_IDX(IntMask)
#घोषणा kr_पूर्णांकstatus KREG_IDX(IntStatus)
#घोषणा kr_ncmodectrl KREG_IDX(IBNCModeCtrl)
#घोषणा kr_palign KREG_IDX(PageAlign)
#घोषणा kr_partitionkey KREG_IDX(RcvPartitionKey)
#घोषणा kr_portcnt KREG_IDX(PortCnt)
#घोषणा kr_rcvbthqp KREG_IDX(RcvBTHQP)
#घोषणा kr_rcvctrl KREG_IDX(RcvCtrl)
#घोषणा kr_rcvegrbase KREG_IDX(RcvEgrBase)
#घोषणा kr_rcvegrcnt KREG_IDX(RcvEgrCnt)
#घोषणा kr_rcvhdrcnt KREG_IDX(RcvHdrCnt)
#घोषणा kr_rcvhdrentsize KREG_IDX(RcvHdrEntSize)
#घोषणा kr_rcvhdrsize KREG_IDX(RcvHdrSize)
#घोषणा kr_rcvpktledcnt KREG_IDX(RcvPktLEDCnt)
#घोषणा kr_rcvtidbase KREG_IDX(RcvTIDBase)
#घोषणा kr_rcvtidcnt KREG_IDX(RcvTIDCnt)
#घोषणा kr_revision KREG_IDX(Revision)
#घोषणा kr_scratch KREG_IDX(Scratch)
#घोषणा kr_sendbuffererror KREG_IDX(SendBufErr0)
#घोषणा kr_sendctrl KREG_IDX(SendCtrl)
#घोषणा kr_senddmabase KREG_IDX(SendDmaBase)
#घोषणा kr_senddmabufmask0 KREG_IDX(SendDmaBufMask0)
#घोषणा kr_senddmabufmask1 (KREG_IDX(SendDmaBufMask0) + 1)
#घोषणा kr_senddmabufmask2 (KREG_IDX(SendDmaBufMask0) + 2)
#घोषणा kr_senddmahead KREG_IDX(SendDmaHead)
#घोषणा kr_senddmaheadaddr KREG_IDX(SendDmaHeadAddr)
#घोषणा kr_senddmalengen KREG_IDX(SendDmaLenGen)
#घोषणा kr_senddmastatus KREG_IDX(SendDmaStatus)
#घोषणा kr_senddmatail KREG_IDX(SendDmaTail)
#घोषणा kr_sendpioavailaddr KREG_IDX(SendBufAvailAddr)
#घोषणा kr_sendpiobufbase KREG_IDX(SendBufBase)
#घोषणा kr_sendpiobufcnt KREG_IDX(SendBufCnt)
#घोषणा kr_sendpiosize KREG_IDX(SendBufSize)
#घोषणा kr_sendregbase KREG_IDX(SendRegBase)
#घोषणा kr_userregbase KREG_IDX(UserRegBase)
#घोषणा kr_xgxs_cfg KREG_IDX(XGXSCfg)

/* These must only be written via qib_ग_लिखो_kreg_ctxt() */
#घोषणा kr_rcvhdraddr KREG_IDX(RcvHdrAddr0)
#घोषणा kr_rcvhdrtailaddr KREG_IDX(RcvHdrTailAddr0)


#घोषणा CREG_IDX(regname) ((QIB_7220_##regname##_OFFS - \
			QIB_7220_LBIntCnt_OFFS) / माप(u64))

#घोषणा cr_badक्रमmat CREG_IDX(RxVersionErrCnt)
#घोषणा cr_erricrc CREG_IDX(RxICRCErrCnt)
#घोषणा cr_errlink CREG_IDX(RxLinkMalक्रमmCnt)
#घोषणा cr_errlpcrc CREG_IDX(RxLPCRCErrCnt)
#घोषणा cr_errpkey CREG_IDX(RxPKeyMismatchCnt)
#घोषणा cr_rcvflowctrl_err CREG_IDX(RxFlowCtrlViolCnt)
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
#घोषणा cr_vl15droppedpkt CREG_IDX(RxVL15DroppedPktCnt)
#घोषणा cr_rxotherlocalphyerr CREG_IDX(RxOtherLocalPhyErrCnt)
#घोषणा cr_excessbufferovfl CREG_IDX(ExcessBufferOvflCnt)
#घोषणा cr_locallinkपूर्णांकegrityerr CREG_IDX(LocalLinkIntegrityErrCnt)
#घोषणा cr_rxvlerr CREG_IDX(RxVlErrCnt)
#घोषणा cr_rxdlidfltr CREG_IDX(RxDlidFltrCnt)
#घोषणा cr_psstat CREG_IDX(PSStat)
#घोषणा cr_psstart CREG_IDX(PSStart)
#घोषणा cr_psपूर्णांकerval CREG_IDX(PSInterval)
#घोषणा cr_psrcvdatacount CREG_IDX(PSRcvDataCount)
#घोषणा cr_psrcvpktscount CREG_IDX(PSRcvPktsCount)
#घोषणा cr_psxmitdatacount CREG_IDX(PSXmitDataCount)
#घोषणा cr_psxmitpktscount CREG_IDX(PSXmitPktsCount)
#घोषणा cr_psxmitरुकोcount CREG_IDX(PSXmitWaitCount)
#घोषणा cr_txsdmadesc CREG_IDX(TxSDmaDescCnt)
#घोषणा cr_pcieretrydiag CREG_IDX(PcieRetryBufDiagQwordCnt)

#घोषणा SYM_RMASK(regname, fldname) ((u64)              \
	QIB_7220_##regname##_##fldname##_RMASK)
#घोषणा SYM_MASK(regname, fldname) ((u64)               \
	QIB_7220_##regname##_##fldname##_RMASK <<       \
	 QIB_7220_##regname##_##fldname##_LSB)
#घोषणा SYM_LSB(regname, fldname) (QIB_7220_##regname##_##fldname##_LSB)
#घोषणा SYM_FIELD(value, regname, fldname) ((u64) \
	(((value) >> SYM_LSB(regname, fldname)) & \
	 SYM_RMASK(regname, fldname)))
#घोषणा ERR_MASK(fldname) SYM_MASK(ErrMask, fldname##Mask)
#घोषणा HWE_MASK(fldname) SYM_MASK(HwErrMask, fldname##Mask)

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

#घोषणा BLOB_7220_IBCHG 0x81

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

अटल अंतरभूत व्योम ग_लिखो_7220_creg(स्थिर काष्ठा qib_devdata *dd,
				   u16 regno, u64 value)
अणु
	अगर (dd->cspec->cregbase && (dd->flags & QIB_PRESENT))
		ग_लिखोq(value, &dd->cspec->cregbase[regno]);
पूर्ण

अटल अंतरभूत u64 पढ़ो_7220_creg(स्थिर काष्ठा qib_devdata *dd, u16 regno)
अणु
	अगर (!dd->cspec->cregbase || !(dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोq(&dd->cspec->cregbase[regno]);
पूर्ण

अटल अंतरभूत u32 पढ़ो_7220_creg32(स्थिर काष्ठा qib_devdata *dd, u16 regno)
अणु
	अगर (!dd->cspec->cregbase || !(dd->flags & QIB_PRESENT))
		वापस 0;
	वापस पढ़ोl(&dd->cspec->cregbase[regno]);
पूर्ण

/* kr_revision bits */
#घोषणा QLOGIC_IB_R_EMULATORREV_MASK ((1ULL << 22) - 1)
#घोषणा QLOGIC_IB_R_EMULATORREV_SHIFT 40

/* kr_control bits */
#घोषणा QLOGIC_IB_C_RESET (1U << 7)

/* kr_पूर्णांकstatus, kr_पूर्णांकclear, kr_पूर्णांकmask bits */
#घोषणा QLOGIC_IB_I_RCVURG_MASK ((1ULL << 17) - 1)
#घोषणा QLOGIC_IB_I_RCVURG_SHIFT 32
#घोषणा QLOGIC_IB_I_RCVAVAIL_MASK ((1ULL << 17) - 1)
#घोषणा QLOGIC_IB_I_RCVAVAIL_SHIFT 0
#घोषणा QLOGIC_IB_I_SERDESTRIMDONE (1ULL << 27)

#घोषणा QLOGIC_IB_C_FREEZEMODE 0x00000002
#घोषणा QLOGIC_IB_C_LINKENABLE 0x00000004

#घोषणा QLOGIC_IB_I_SDMAINT             0x8000000000000000ULL
#घोषणा QLOGIC_IB_I_SDMADISABLED        0x4000000000000000ULL
#घोषणा QLOGIC_IB_I_ERROR               0x0000000080000000ULL
#घोषणा QLOGIC_IB_I_SPIOSENT            0x0000000040000000ULL
#घोषणा QLOGIC_IB_I_SPIOBUFAVAIL        0x0000000020000000ULL
#घोषणा QLOGIC_IB_I_GPIO                0x0000000010000000ULL

/* variables क्रम sanity checking पूर्णांकerrupt and errors */
#घोषणा QLOGIC_IB_I_BITSEXTANT \
		(QLOGIC_IB_I_SDMAINT | QLOGIC_IB_I_SDMADISABLED | \
		(QLOGIC_IB_I_RCVURG_MASK << QLOGIC_IB_I_RCVURG_SHIFT) | \
		(QLOGIC_IB_I_RCVAVAIL_MASK << \
		 QLOGIC_IB_I_RCVAVAIL_SHIFT) | \
		QLOGIC_IB_I_ERROR | QLOGIC_IB_I_SPIOSENT | \
		QLOGIC_IB_I_SPIOBUFAVAIL | QLOGIC_IB_I_GPIO | \
		QLOGIC_IB_I_SERDESTRIMDONE)

#घोषणा IB_HWE_BITSEXTANT \
	       (HWE_MASK(RXEMemParityErr) | \
		HWE_MASK(TXEMemParityErr) | \
		(QLOGIC_IB_HWE_PCIEMEMPARITYERR_MASK <<	 \
		 QLOGIC_IB_HWE_PCIEMEMPARITYERR_SHIFT) | \
		QLOGIC_IB_HWE_PCIE1PLLFAILED | \
		QLOGIC_IB_HWE_PCIE0PLLFAILED | \
		QLOGIC_IB_HWE_PCIEPOISONEDTLP | \
		QLOGIC_IB_HWE_PCIECPLTIMEOUT | \
		QLOGIC_IB_HWE_PCIEBUSPARITYXTLH | \
		QLOGIC_IB_HWE_PCIEBUSPARITYXADM | \
		QLOGIC_IB_HWE_PCIEBUSPARITYRADM | \
		HWE_MASK(PowerOnBISTFailed) |	  \
		QLOGIC_IB_HWE_COREPLL_FBSLIP | \
		QLOGIC_IB_HWE_COREPLL_RFSLIP | \
		QLOGIC_IB_HWE_SERDESPLLFAILED | \
		HWE_MASK(IBCBusToSPCParityErr) | \
		HWE_MASK(IBCBusFromSPCParityErr) | \
		QLOGIC_IB_HWE_PCIECPLDATAQUEUEERR | \
		QLOGIC_IB_HWE_PCIECPLHDRQUEUEERR | \
		QLOGIC_IB_HWE_SDMAMEMREADERR | \
		QLOGIC_IB_HWE_CLK_UC_PLLNOTLOCKED | \
		QLOGIC_IB_HWE_PCIESERDESQ0PCLKNOTDETECT | \
		QLOGIC_IB_HWE_PCIESERDESQ1PCLKNOTDETECT | \
		QLOGIC_IB_HWE_PCIESERDESQ2PCLKNOTDETECT | \
		QLOGIC_IB_HWE_PCIESERDESQ3PCLKNOTDETECT | \
		QLOGIC_IB_HWE_DDSRXEQMEMORYPARITYERR | \
		QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR | \
		QLOGIC_IB_HWE_PCIE_UC_OCT0MEMORYPARITYERR | \
		QLOGIC_IB_HWE_PCIE_UC_OCT1MEMORYPARITYERR)

#घोषणा IB_E_BITSEXTANT							\
	(ERR_MASK(RcvFormatErr) | ERR_MASK(RcvVCRCErr) |		\
	 ERR_MASK(RcvICRCErr) | ERR_MASK(RcvMinPktLenErr) |		\
	 ERR_MASK(RcvMaxPktLenErr) | ERR_MASK(RcvLongPktLenErr) |	\
	 ERR_MASK(RcvShortPktLenErr) | ERR_MASK(RcvUnexpectedCharErr) | \
	 ERR_MASK(RcvUnsupportedVLErr) | ERR_MASK(RcvEBPErr) |		\
	 ERR_MASK(RcvIBFlowErr) | ERR_MASK(RcvBadVersionErr) |		\
	 ERR_MASK(RcvEgrFullErr) | ERR_MASK(RcvHdrFullErr) |		\
	 ERR_MASK(RcvBadTidErr) | ERR_MASK(RcvHdrLenErr) |		\
	 ERR_MASK(RcvHdrErr) | ERR_MASK(RcvIBLostLinkErr) |		\
	 ERR_MASK(SendSpecialTriggerErr) |				\
	 ERR_MASK(SDmaDisabledErr) | ERR_MASK(SendMinPktLenErr) |	\
	 ERR_MASK(SendMaxPktLenErr) | ERR_MASK(SendUnderRunErr) |	\
	 ERR_MASK(SendPktLenErr) | ERR_MASK(SendDroppedSmpPktErr) |	\
	 ERR_MASK(SendDroppedDataPktErr) |				\
	 ERR_MASK(SendPioArmLaunchErr) |				\
	 ERR_MASK(SendUnexpectedPktNumErr) |				\
	 ERR_MASK(SendUnsupportedVLErr) | ERR_MASK(SendBufMisuseErr) |	\
	 ERR_MASK(SDmaGenMismatchErr) | ERR_MASK(SDmaOutOfBoundErr) |	\
	 ERR_MASK(SDmaTailOutOfBoundErr) | ERR_MASK(SDmaBaseErr) |	\
	 ERR_MASK(SDma1stDescErr) | ERR_MASK(SDmaRpyTagErr) |		\
	 ERR_MASK(SDmaDwEnErr) | ERR_MASK(SDmaMissingDwErr) |		\
	 ERR_MASK(SDmaUnexpDataErr) |					\
	 ERR_MASK(IBStatusChanged) | ERR_MASK(InvalidAddrErr) |		\
	 ERR_MASK(ResetNegated) | ERR_MASK(HardwareErr) |		\
	 ERR_MASK(SDmaDescAddrMisalignErr) |				\
	 ERR_MASK(InvalidEEPCmd))

/* kr_hwerrclear, kr_hwerrmask, kr_hwerrstatus, bits */
#घोषणा QLOGIC_IB_HWE_PCIEMEMPARITYERR_MASK  0x00000000000000ffULL
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
/* specअगरic to this chip */
#घोषणा QLOGIC_IB_HWE_PCIECPLDATAQUEUEERR         0x0000000000000040ULL
#घोषणा QLOGIC_IB_HWE_PCIECPLHDRQUEUEERR          0x0000000000000080ULL
#घोषणा QLOGIC_IB_HWE_SDMAMEMREADERR              0x0000000010000000ULL
#घोषणा QLOGIC_IB_HWE_CLK_UC_PLLNOTLOCKED          0x2000000000000000ULL
#घोषणा QLOGIC_IB_HWE_PCIESERDESQ0PCLKNOTDETECT   0x0100000000000000ULL
#घोषणा QLOGIC_IB_HWE_PCIESERDESQ1PCLKNOTDETECT   0x0200000000000000ULL
#घोषणा QLOGIC_IB_HWE_PCIESERDESQ2PCLKNOTDETECT   0x0400000000000000ULL
#घोषणा QLOGIC_IB_HWE_PCIESERDESQ3PCLKNOTDETECT   0x0800000000000000ULL
#घोषणा QLOGIC_IB_HWE_DDSRXEQMEMORYPARITYERR       0x0000008000000000ULL
#घोषणा QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR        0x0000004000000000ULL
#घोषणा QLOGIC_IB_HWE_PCIE_UC_OCT0MEMORYPARITYERR 0x0000001000000000ULL
#घोषणा QLOGIC_IB_HWE_PCIE_UC_OCT1MEMORYPARITYERR 0x0000002000000000ULL

#घोषणा IBA7220_IBCC_LINKCMD_SHIFT 19

/* kr_ibcddrctrl bits */
#घोषणा IBA7220_IBC_DLIDLMC_MASK        0xFFFFFFFFUL
#घोषणा IBA7220_IBC_DLIDLMC_SHIFT       32

#घोषणा IBA7220_IBC_HRTBT_MASK  (SYM_RMASK(IBCDDRCtrl, HRTBT_AUTO) | \
				 SYM_RMASK(IBCDDRCtrl, HRTBT_ENB))
#घोषणा IBA7220_IBC_HRTBT_SHIFT SYM_LSB(IBCDDRCtrl, HRTBT_ENB)

#घोषणा IBA7220_IBC_LANE_REV_SUPPORTED (1<<8)
#घोषणा IBA7220_IBC_LREV_MASK   1
#घोषणा IBA7220_IBC_LREV_SHIFT  8
#घोषणा IBA7220_IBC_RXPOL_MASK  1
#घोषणा IBA7220_IBC_RXPOL_SHIFT 7
#घोषणा IBA7220_IBC_WIDTH_SHIFT 5
#घोषणा IBA7220_IBC_WIDTH_MASK  0x3
#घोषणा IBA7220_IBC_WIDTH_1X_ONLY       (0 << IBA7220_IBC_WIDTH_SHIFT)
#घोषणा IBA7220_IBC_WIDTH_4X_ONLY       (1 << IBA7220_IBC_WIDTH_SHIFT)
#घोषणा IBA7220_IBC_WIDTH_AUTONEG       (2 << IBA7220_IBC_WIDTH_SHIFT)
#घोषणा IBA7220_IBC_SPEED_AUTONEG       (1 << 1)
#घोषणा IBA7220_IBC_SPEED_SDR           (1 << 2)
#घोषणा IBA7220_IBC_SPEED_DDR           (1 << 3)
#घोषणा IBA7220_IBC_SPEED_AUTONEG_MASK  (0x7 << 1)
#घोषणा IBA7220_IBC_IBTA_1_2_MASK       (1)

/* kr_ibcddrstatus */
/* link latency shअगरt is 0, करोn't bother defining */
#घोषणा IBA7220_DDRSTAT_LINKLAT_MASK    0x3ffffff

/* kr_extstatus bits */
#घोषणा QLOGIC_IB_EXTS_FREQSEL 0x2
#घोषणा QLOGIC_IB_EXTS_SERDESSEL 0x4
#घोषणा QLOGIC_IB_EXTS_MEMBIST_ENDTEST     0x0000000000004000
#घोषणा QLOGIC_IB_EXTS_MEMBIST_DISABLED    0x0000000000008000

/* kr_xgxsconfig bits */
#घोषणा QLOGIC_IB_XGXS_RESET          0x5ULL
#घोषणा QLOGIC_IB_XGXS_FC_SAFE        (1ULL << 63)

/* kr_rcvpktledcnt */
#घोषणा IBA7220_LEDBLINK_ON_SHIFT 32 /* 4ns period on after packet */
#घोषणा IBA7220_LEDBLINK_OFF_SHIFT 0 /* 4ns period off beक्रमe next on */

#घोषणा _QIB_GPIO_SDA_NUM 1
#घोषणा _QIB_GPIO_SCL_NUM 0
#घोषणा QIB_TWSI_EEPROM_DEV 0xA2 /* All Production 7220 cards. */
#घोषणा QIB_TWSI_TEMP_DEV 0x98

/* HW counter घड़ी is at 4nsec */
#घोषणा QIB_7220_PSXMITWAIT_CHECK_RATE 4000

#घोषणा IBA7220_R_INTRAVAIL_SHIFT 17
#घोषणा IBA7220_R_PKEY_DIS_SHIFT 34
#घोषणा IBA7220_R_TAILUPD_SHIFT 35
#घोषणा IBA7220_R_CTXTCFG_SHIFT 36

#घोषणा IBA7220_HDRHEAD_PKTINT_SHIFT 32 /* पूर्णांकerrupt cnt in upper 32 bits */

/*
 * the size bits give us 2^N, in KB units.  0 marks as invalid,
 * and 7 is reserved.  We currently use only 2KB and 4KB
 */
#घोषणा IBA7220_TID_SZ_SHIFT 37 /* shअगरt to 3bit size selector */
#घोषणा IBA7220_TID_SZ_2K (1UL << IBA7220_TID_SZ_SHIFT) /* 2KB */
#घोषणा IBA7220_TID_SZ_4K (2UL << IBA7220_TID_SZ_SHIFT) /* 4KB */
#घोषणा IBA7220_TID_PA_SHIFT 11U /* TID addr in chip stored w/o low bits */
#घोषणा PBC_7220_VL15_SEND (1ULL << 63) /* pbc; VL15, no credit check */
#घोषणा PBC_7220_VL15_SEND_CTRL (1ULL << 31) /* control version of same */

#घोषणा AUTONEG_TRIES 5 /* sequential retries to negotiate DDR */

/* packet rate matching delay multiplier */
अटल u8 rate_to_delay[2][2] = अणु
	/* 1x, 4x */
	अणु   8, 2 पूर्ण, /* SDR */
	अणु   4, 1 पूर्ण  /* DDR */
पूर्ण;

अटल u8 ib_rate_to_delay[IB_RATE_120_GBPS + 1] = अणु
	[IB_RATE_2_5_GBPS] = 8,
	[IB_RATE_5_GBPS] = 4,
	[IB_RATE_10_GBPS] = 2,
	[IB_RATE_20_GBPS] = 1
पूर्ण;

#घोषणा IBA7220_LINKSPEED_SHIFT SYM_LSB(IBCStatus, LinkSpeedActive)
#घोषणा IBA7220_LINKWIDTH_SHIFT SYM_LSB(IBCStatus, LinkWidthActive)

/* link training states, from IBC */
#घोषणा IB_7220_LT_STATE_DISABLED        0x00
#घोषणा IB_7220_LT_STATE_LINKUP          0x01
#घोषणा IB_7220_LT_STATE_POLLACTIVE      0x02
#घोषणा IB_7220_LT_STATE_POLLQUIET       0x03
#घोषणा IB_7220_LT_STATE_SLEEPDELAY      0x04
#घोषणा IB_7220_LT_STATE_SLEEPQUIET      0x05
#घोषणा IB_7220_LT_STATE_CFGDEBOUNCE     0x08
#घोषणा IB_7220_LT_STATE_CFGRCVFCFG      0x09
#घोषणा IB_7220_LT_STATE_CFGWAITRMT      0x0a
#घोषणा IB_7220_LT_STATE_CFGIDLE 0x0b
#घोषणा IB_7220_LT_STATE_RECOVERRETRAIN  0x0c
#घोषणा IB_7220_LT_STATE_RECOVERWAITRMT  0x0e
#घोषणा IB_7220_LT_STATE_RECOVERIDLE     0x0f

/* link state machine states from IBC */
#घोषणा IB_7220_L_STATE_DOWN             0x0
#घोषणा IB_7220_L_STATE_INIT             0x1
#घोषणा IB_7220_L_STATE_ARM              0x2
#घोषणा IB_7220_L_STATE_ACTIVE           0x3
#घोषणा IB_7220_L_STATE_ACT_DEFER        0x4

अटल स्थिर u8 qib_7220_physportstate[0x20] = अणु
	[IB_7220_LT_STATE_DISABLED] = IB_PHYSPORTSTATE_DISABLED,
	[IB_7220_LT_STATE_LINKUP] = IB_PHYSPORTSTATE_LINKUP,
	[IB_7220_LT_STATE_POLLACTIVE] = IB_PHYSPORTSTATE_POLL,
	[IB_7220_LT_STATE_POLLQUIET] = IB_PHYSPORTSTATE_POLL,
	[IB_7220_LT_STATE_SLEEPDELAY] = IB_PHYSPORTSTATE_SLEEP,
	[IB_7220_LT_STATE_SLEEPQUIET] = IB_PHYSPORTSTATE_SLEEP,
	[IB_7220_LT_STATE_CFGDEBOUNCE] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7220_LT_STATE_CFGRCVFCFG] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7220_LT_STATE_CFGWAITRMT] =
		IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7220_LT_STATE_CFGIDLE] = IB_PHYSPORTSTATE_CFG_TRAIN,
	[IB_7220_LT_STATE_RECOVERRETRAIN] =
		IB_PHYSPORTSTATE_LINK_ERR_RECOVER,
	[IB_7220_LT_STATE_RECOVERWAITRMT] =
		IB_PHYSPORTSTATE_LINK_ERR_RECOVER,
	[IB_7220_LT_STATE_RECOVERIDLE] =
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

पूर्णांक qib_special_trigger;
module_param_named(special_trigger, qib_special_trigger, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(special_trigger, "Enable SpecialTrigger arm/launch");

#घोषणा IBCBUSFRSPCPARITYERR HWE_MASK(IBCBusFromSPCParityErr)
#घोषणा IBCBUSTOSPCPARITYERR HWE_MASK(IBCBusToSPCParityErr)

#घोषणा SYM_MASK_BIT(regname, fldname, bit) ((u64) \
	(1ULL << (SYM_LSB(regname, fldname) + (bit))))

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

/* 7220 specअगरic hardware errors... */
अटल स्थिर काष्ठा qib_hwerror_msgs qib_7220_hwerror_msgs[] = अणु
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
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIECPLDATAQUEUEERR,
			  "PCIe cpl header queue"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIECPLHDRQUEUEERR,
			  "PCIe cpl data queue"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_SDMAMEMREADERR,
			  "Send DMA memory read"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_CLK_UC_PLLNOTLOCKED,
			  "uC PLL clock not locked"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIESERDESQ0PCLKNOTDETECT,
			  "PCIe serdes Q0 no clock"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIESERDESQ1PCLKNOTDETECT,
			  "PCIe serdes Q1 no clock"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIESERDESQ2PCLKNOTDETECT,
			  "PCIe serdes Q2 no clock"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIESERDESQ3PCLKNOTDETECT,
			  "PCIe serdes Q3 no clock"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_DDSRXEQMEMORYPARITYERR,
			  "DDS RXEQ memory parity"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR,
			  "IB uC memory parity"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIE_UC_OCT0MEMORYPARITYERR,
			  "PCIe uC oct0 memory parity"),
	QLOGIC_IB_HWE_MSG(QLOGIC_IB_HWE_PCIE_UC_OCT1MEMORYPARITYERR,
			  "PCIe uC oct1 memory parity"),
पूर्ण;

#घोषणा RXE_PARITY (RXEMEMPARITYERR_EAGERTID|RXEMEMPARITYERR_EXPTID)

#घोषणा QLOGIC_IB_E_PKTERRS (\
		ERR_MASK(SendPktLenErr) |				\
		ERR_MASK(SendDroppedDataPktErr) |			\
		ERR_MASK(RcvVCRCErr) |					\
		ERR_MASK(RcvICRCErr) |					\
		ERR_MASK(RcvShortPktLenErr) |				\
		ERR_MASK(RcvEBPErr))

/* Convenience क्रम decoding Send DMA errors */
#घोषणा QLOGIC_IB_E_SDMAERRS ( \
		ERR_MASK(SDmaGenMismatchErr) |				\
		ERR_MASK(SDmaOutOfBoundErr) |				\
		ERR_MASK(SDmaTailOutOfBoundErr) | ERR_MASK(SDmaBaseErr) | \
		ERR_MASK(SDma1stDescErr) | ERR_MASK(SDmaRpyTagErr) |	\
		ERR_MASK(SDmaDwEnErr) | ERR_MASK(SDmaMissingDwErr) |	\
		ERR_MASK(SDmaUnexpDataErr) |				\
		ERR_MASK(SDmaDescAddrMisalignErr) |			\
		ERR_MASK(SDmaDisabledErr) |				\
		ERR_MASK(SendBufMisuseErr))

/* These are all rcv-related errors which we want to count क्रम stats */
#घोषणा E_SUM_PKTERRS \
	(ERR_MASK(RcvHdrLenErr) | ERR_MASK(RcvBadTidErr) |		\
	 ERR_MASK(RcvBadVersionErr) | ERR_MASK(RcvHdrErr) |		\
	 ERR_MASK(RcvLongPktLenErr) | ERR_MASK(RcvShortPktLenErr) |	\
	 ERR_MASK(RcvMaxPktLenErr) | ERR_MASK(RcvMinPktLenErr) |	\
	 ERR_MASK(RcvFormatErr) | ERR_MASK(RcvUnsupportedVLErr) |	\
	 ERR_MASK(RcvUnexpectedCharErr) | ERR_MASK(RcvEBPErr))

/* These are all send-related errors which we want to count क्रम stats */
#घोषणा E_SUM_ERRS \
	(ERR_MASK(SendPioArmLaunchErr) | ERR_MASK(SendUnexpectedPktNumErr) | \
	 ERR_MASK(SendDroppedDataPktErr) | ERR_MASK(SendDroppedSmpPktErr) | \
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
	(ERR_MASK(SendDroppedDataPktErr) | ERR_MASK(SendDroppedSmpPktErr) | \
	 ERR_MASK(SendMaxPktLenErr) | ERR_MASK(SendMinPktLenErr) |	\
	 ERR_MASK(SendPktLenErr))

/*
 * these are errors that can occur when the link changes state जबतक
 * a packet is being sent or received.  This करोesn't cover things
 * like EBP or VCRC that can be the result of a sending having the
 * link change state, so we receive a "known bad" packet.
 */
#घोषणा E_SUM_LINK_PKTERRS \
	(ERR_MASK(SendDroppedDataPktErr) | ERR_MASK(SendDroppedSmpPktErr) | \
	 ERR_MASK(SendMinPktLenErr) | ERR_MASK(SendPktLenErr) |		\
	 ERR_MASK(RcvShortPktLenErr) | ERR_MASK(RcvMinPktLenErr) |	\
	 ERR_MASK(RcvUnexpectedCharErr))

अटल व्योम स्वतःneg_7220_work(काष्ठा work_काष्ठा *);
अटल u32 __iomem *qib_7220_माला_लोendbuf(काष्ठा qib_pportdata *, u64, u32 *);

/*
 * Called when we might have an error that is specअगरic to a particular
 * PIO buffer, and may need to cancel that buffer, so it can be re-used.
 * because we करोn't need to क्रमce the update of pioavail.
 */
अटल व्योम qib_disarm_7220_senderrbufs(काष्ठा qib_pportdata *ppd)
अणु
	अचिन्हित दीर्घ sbuf[3];
	काष्ठा qib_devdata *dd = ppd->dd;

	/*
	 * It's possible that sendbuffererror could have bits set; might
	 * have alपढ़ोy करोne this as a result of hardware error handling.
	 */
	/* पढ़ो these beक्रमe writing errorclear */
	sbuf[0] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror);
	sbuf[1] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror + 1);
	sbuf[2] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror + 2);

	अगर (sbuf[0] || sbuf[1] || sbuf[2])
		qib_disarm_piobufs_set(dd, sbuf,
				       dd->piobcnt2k + dd->piobcnt4k);
पूर्ण

अटल व्योम qib_7220_txe_recover(काष्ठा qib_devdata *dd)
अणु
	qib_devinfo(dd->pcidev, "Recovering from TXE PIO parity error\n");
	qib_disarm_7220_senderrbufs(dd->pport);
पूर्ण

/*
 * This is called with पूर्णांकerrupts disabled and sdma_lock held.
 */
अटल व्योम qib_7220_sdma_sendctrl(काष्ठा qib_pportdata *ppd, अचिन्हित op)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 set_sendctrl = 0;
	u64 clr_sendctrl = 0;

	अगर (op & QIB_SDMA_SENDCTRL_OP_ENABLE)
		set_sendctrl |= SYM_MASK(SendCtrl, SDmaEnable);
	अन्यथा
		clr_sendctrl |= SYM_MASK(SendCtrl, SDmaEnable);

	अगर (op & QIB_SDMA_SENDCTRL_OP_INTENABLE)
		set_sendctrl |= SYM_MASK(SendCtrl, SDmaIntEnable);
	अन्यथा
		clr_sendctrl |= SYM_MASK(SendCtrl, SDmaIntEnable);

	अगर (op & QIB_SDMA_SENDCTRL_OP_HALT)
		set_sendctrl |= SYM_MASK(SendCtrl, SDmaHalt);
	अन्यथा
		clr_sendctrl |= SYM_MASK(SendCtrl, SDmaHalt);

	spin_lock(&dd->sendctrl_lock);

	dd->sendctrl |= set_sendctrl;
	dd->sendctrl &= ~clr_sendctrl;

	qib_ग_लिखो_kreg(dd, kr_sendctrl, dd->sendctrl);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);

	spin_unlock(&dd->sendctrl_lock);
पूर्ण

अटल व्योम qib_decode_7220_sdma_errs(काष्ठा qib_pportdata *ppd,
				      u64 err, अक्षर *buf, माप_प्रकार blen)
अणु
	अटल स्थिर काष्ठा अणु
		u64 err;
		स्थिर अक्षर *msg;
	पूर्ण errs[] = अणु
		अणु ERR_MASK(SDmaGenMismatchErr),
		  "SDmaGenMismatch" पूर्ण,
		अणु ERR_MASK(SDmaOutOfBoundErr),
		  "SDmaOutOfBound" पूर्ण,
		अणु ERR_MASK(SDmaTailOutOfBoundErr),
		  "SDmaTailOutOfBound" पूर्ण,
		अणु ERR_MASK(SDmaBaseErr),
		  "SDmaBase" पूर्ण,
		अणु ERR_MASK(SDma1stDescErr),
		  "SDma1stDesc" पूर्ण,
		अणु ERR_MASK(SDmaRpyTagErr),
		  "SDmaRpyTag" पूर्ण,
		अणु ERR_MASK(SDmaDwEnErr),
		  "SDmaDwEn" पूर्ण,
		अणु ERR_MASK(SDmaMissingDwErr),
		  "SDmaMissingDw" पूर्ण,
		अणु ERR_MASK(SDmaUnexpDataErr),
		  "SDmaUnexpData" पूर्ण,
		अणु ERR_MASK(SDmaDescAddrMisalignErr),
		  "SDmaDescAddrMisalign" पूर्ण,
		अणु ERR_MASK(SendBufMisuseErr),
		  "SendBufMisuse" पूर्ण,
		अणु ERR_MASK(SDmaDisabledErr),
		  "SDmaDisabled" पूर्ण,
	पूर्ण;
	पूर्णांक i;
	माप_प्रकार bidx = 0;

	क्रम (i = 0; i < ARRAY_SIZE(errs); i++) अणु
		अगर (err & errs[i].err)
			bidx += scnम_लिखो(buf + bidx, blen - bidx,
					 "%s ", errs[i].msg);
	पूर्ण
पूर्ण

/*
 * This is called as part of link करोwn clean up so disarm and flush
 * all send buffers so that SMP packets can be sent.
 */
अटल व्योम qib_7220_sdma_hw_clean_up(काष्ठा qib_pportdata *ppd)
अणु
	/* This will trigger the Abort पूर्णांकerrupt */
	sendctrl_7220_mod(ppd, QIB_SENDCTRL_DISARM_ALL | QIB_SENDCTRL_FLUSH |
			  QIB_SENDCTRL_AVAIL_BLIP);
	ppd->dd->upd_pio_shaकरोw  = 1; /* update our idea of what's busy */
पूर्ण

अटल व्योम qib_sdma_7220_setlengen(काष्ठा qib_pportdata *ppd)
अणु
	/*
	 * Set SendDmaLenGen and clear and set
	 * the MSB of the generation count to enable generation checking
	 * and load the पूर्णांकernal generation counter.
	 */
	qib_ग_लिखो_kreg(ppd->dd, kr_senddmalengen, ppd->sdma_descq_cnt);
	qib_ग_लिखो_kreg(ppd->dd, kr_senddmalengen,
		       ppd->sdma_descq_cnt |
		       (1ULL << QIB_7220_SendDmaLenGen_Generation_MSB));
पूर्ण

अटल व्योम qib_7220_sdma_hw_start_up(काष्ठा qib_pportdata *ppd)
अणु
	qib_sdma_7220_setlengen(ppd);
	qib_sdma_update_7220_tail(ppd, 0); /* Set SendDmaTail */
	ppd->sdma_head_dma[0] = 0;
पूर्ण

#घोषणा DISABLES_SDMA (							\
		ERR_MASK(SDmaDisabledErr) |				\
		ERR_MASK(SDmaBaseErr) |					\
		ERR_MASK(SDmaTailOutOfBoundErr) |			\
		ERR_MASK(SDmaOutOfBoundErr) |				\
		ERR_MASK(SDma1stDescErr) |				\
		ERR_MASK(SDmaRpyTagErr) |				\
		ERR_MASK(SDmaGenMismatchErr) |				\
		ERR_MASK(SDmaDescAddrMisalignErr) |			\
		ERR_MASK(SDmaMissingDwErr) |				\
		ERR_MASK(SDmaDwEnErr))

अटल व्योम sdma_7220_errors(काष्ठा qib_pportdata *ppd, u64 errs)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qib_devdata *dd = ppd->dd;
	अक्षर *msg;

	errs &= QLOGIC_IB_E_SDMAERRS;

	msg = dd->cspec->sdmamsgbuf;
	qib_decode_7220_sdma_errs(ppd, errs, msg,
		माप(dd->cspec->sdmamsgbuf));
	spin_lock_irqsave(&ppd->sdma_lock, flags);

	अगर (errs & ERR_MASK(SendBufMisuseErr)) अणु
		अचिन्हित दीर्घ sbuf[3];

		sbuf[0] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror);
		sbuf[1] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror + 1);
		sbuf[2] = qib_पढ़ो_kreg64(dd, kr_sendbuffererror + 2);

		qib_dev_err(ppd->dd,
			    "IB%u:%u SendBufMisuse: %04lx %016lx %016lx\n",
			    ppd->dd->unit, ppd->port, sbuf[2], sbuf[1],
			    sbuf[0]);
	पूर्ण

	अगर (errs & ERR_MASK(SDmaUnexpDataErr))
		qib_dev_err(dd, "IB%u:%u SDmaUnexpData\n", ppd->dd->unit,
			    ppd->port);

	चयन (ppd->sdma_state.current_state) अणु
	हाल qib_sdma_state_s00_hw_करोwn:
		/* not expecting any पूर्णांकerrupts */
		अवरोध;

	हाल qib_sdma_state_s10_hw_start_up_रुको:
		/* handled in पूर्णांकr path */
		अवरोध;

	हाल qib_sdma_state_s20_idle:
		/* not expecting any पूर्णांकerrupts */
		अवरोध;

	हाल qib_sdma_state_s30_sw_clean_up_रुको:
		/* not expecting any पूर्णांकerrupts */
		अवरोध;

	हाल qib_sdma_state_s40_hw_clean_up_रुको:
		अगर (errs & ERR_MASK(SDmaDisabledErr))
			__qib_sdma_process_event(ppd,
				qib_sdma_event_e50_hw_cleaned);
		अवरोध;

	हाल qib_sdma_state_s50_hw_halt_रुको:
		/* handled in पूर्णांकr path */
		अवरोध;

	हाल qib_sdma_state_s99_running:
		अगर (errs & DISABLES_SDMA)
			__qib_sdma_process_event(ppd,
				qib_sdma_event_e7220_err_halted);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
पूर्ण

/*
 * Decode the error status पूर्णांकo strings, deciding whether to always
 * prपूर्णांक * it or not depending on "normal packet errors" vs everything
 * अन्यथा.   Return 1 अगर "real" errors, otherwise 0 अगर only packet
 * errors, so caller can decide what to prपूर्णांक with the string.
 */
अटल पूर्णांक qib_decode_7220_err(काष्ठा qib_devdata *dd, अक्षर *buf, माप_प्रकार blen,
			       u64 err)
अणु
	पूर्णांक iserr = 1;

	*buf = '\0';
	अगर (err & QLOGIC_IB_E_PKTERRS) अणु
		अगर (!(err & ~QLOGIC_IB_E_PKTERRS))
			iserr = 0;
		अगर ((err & ERR_MASK(RcvICRCErr)) &&
		    !(err & (ERR_MASK(RcvVCRCErr) | ERR_MASK(RcvEBPErr))))
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
	अगर (err & ERR_MASK(SendSpecialTriggerErr))
		strlcat(buf, "sendspecialtrigger ", blen);
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
	अगर (err & QLOGIC_IB_E_SDMAERRS)
		qib_decode_7220_sdma_errs(dd->pport, err, buf, blen);
	अगर (err & ERR_MASK(InvalidEEPCmd))
		strlcat(buf, "invalideepromcmd ", blen);
करोne:
	वापस iserr;
पूर्ण

अटल व्योम reenable_7220_chase(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_chippport_specअगरic *cpspec = from_समयr(cpspec, t,
							 chase_समयr);
	काष्ठा qib_pportdata *ppd = &cpspec->pportdata;

	ppd->cpspec->chase_समयr.expires = 0;
	qib_set_ib_7220_lstate(ppd, QLOGIC_IB_IBCC_LINKCMD_DOWN,
		QLOGIC_IB_IBCC_LINKINITCMD_POLL);
पूर्ण

अटल व्योम handle_7220_chase(काष्ठा qib_pportdata *ppd, u64 ibcst)
अणु
	u8 ibclt;
	अचिन्हित दीर्घ tnow;

	ibclt = (u8)SYM_FIELD(ibcst, IBCStatus, LinkTrainingState);

	/*
	 * Detect and handle the state chase issue, where we can
	 * get stuck अगर we are unlucky on timing on both sides of
	 * the link.   If we are, we disable, set a समयr, and
	 * then re-enable.
	 */
	चयन (ibclt) अणु
	हाल IB_7220_LT_STATE_CFGRCVFCFG:
	हाल IB_7220_LT_STATE_CFGWAITRMT:
	हाल IB_7220_LT_STATE_TXREVLANES:
	हाल IB_7220_LT_STATE_CFGENH:
		tnow = jअगरfies;
		अगर (ppd->cpspec->chase_end &&
		    समय_after(tnow, ppd->cpspec->chase_end)) अणु
			ppd->cpspec->chase_end = 0;
			qib_set_ib_7220_lstate(ppd,
				QLOGIC_IB_IBCC_LINKCMD_DOWN,
				QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);
			ppd->cpspec->chase_समयr.expires = jअगरfies +
				QIB_CHASE_DIS_TIME;
			add_समयr(&ppd->cpspec->chase_समयr);
		पूर्ण अन्यथा अगर (!ppd->cpspec->chase_end)
			ppd->cpspec->chase_end = tnow + QIB_CHASE_TIME;
		अवरोध;

	शेष:
		ppd->cpspec->chase_end = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_7220_errors(काष्ठा qib_devdata *dd, u64 errs)
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
		qib_7220_handle_hwerrors(dd, msg, माप(dd->cspec->emsgbuf));

	अगर (errs & QLOGIC_IB_E_SDMAERRS)
		sdma_7220_errors(ppd, errs);

	अगर (errs & ~IB_E_BITSEXTANT)
		qib_dev_err(dd,
			"error interrupt with unknown errors %llx set\n",
			(अचिन्हित दीर्घ दीर्घ) (errs & ~IB_E_BITSEXTANT));

	अगर (errs & E_SUM_ERRS) अणु
		qib_disarm_7220_senderrbufs(ppd);
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
	 * or above.  Also mask SDMADISABLED by शेष as it
	 * is too chatty.
	 */
	mask = ERR_MASK(IBStatusChanged) |
		ERR_MASK(RcvEgrFullErr) | ERR_MASK(RcvHdrFullErr) |
		ERR_MASK(HardwareErr) | ERR_MASK(SDmaDisabledErr);

	qib_decode_7220_err(dd, msg, माप(dd->cspec->emsgbuf), errs & ~mask);

	अगर (errs & E_SUM_PKTERRS)
		qib_stats.sps_rcverrs++;
	अगर (errs & E_SUM_ERRS)
		qib_stats.sps_txerrs++;
	iserr = errs & ~(E_SUM_PKTERRS | QLOGIC_IB_E_PKTERRS |
			 ERR_MASK(SDmaDisabledErr));

	अगर (errs & ERR_MASK(IBStatusChanged)) अणु
		u64 ibcs;

		ibcs = qib_पढ़ो_kreg64(dd, kr_ibcstatus);
		अगर (!(ppd->lflags & QIBL_IB_AUTONEG_INPROG))
			handle_7220_chase(ppd, ibcs);

		/* Update our picture of width and speed from chip */
		ppd->link_width_active =
			((ibcs >> IBA7220_LINKWIDTH_SHIFT) & 1) ?
			    IB_WIDTH_4X : IB_WIDTH_1X;
		ppd->link_speed_active =
			((ibcs >> IBA7220_LINKSPEED_SHIFT) & 1) ?
			    QIB_IB_DDR : QIB_IB_SDR;

		/*
		 * Since going पूर्णांकo a recovery state causes the link state
		 * to go करोwn and since recovery is transitory, it is better
		 * अगर we "miss" ever seeing the link training state go पूर्णांकo
		 * recovery (i.e., ignore this transition क्रम link state
		 * special handling purposes) without updating lastibcstat.
		 */
		अगर (qib_7220_phys_portstate(ibcs) !=
					    IB_PHYSPORTSTATE_LINK_ERR_RECOVER)
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

/* enable/disable chip from delivering पूर्णांकerrupts */
अटल व्योम qib_7220_set_पूर्णांकr_state(काष्ठा qib_devdata *dd, u32 enable)
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
 * even though the details are similar on most chips.
 */
अटल व्योम qib_7220_clear_मुक्तze(काष्ठा qib_devdata *dd)
अणु
	/* disable error पूर्णांकerrupts, to aव्योम confusion */
	qib_ग_लिखो_kreg(dd, kr_errmask, 0ULL);

	/* also disable पूर्णांकerrupts; errormask is someबार overwritten */
	qib_7220_set_पूर्णांकr_state(dd, 0);

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
	qib_7220_set_पूर्णांकr_state(dd, 1);
पूर्ण

/**
 * qib_7220_handle_hwerrors - display hardware errors.
 * @dd: the qlogic_ib device
 * @msg: the output buffer
 * @msgl: the size of the output buffer
 *
 * Use same msg buffer as regular errors to aव्योम excessive stack
 * use.  Most hardware errors are catastrophic, but क्रम right now,
 * we'll prपूर्णांक them and जारी.  We reuse the same message buffer as
 * handle_7220_errors() to aव्योम excessive stack usage.
 */
अटल व्योम qib_7220_handle_hwerrors(काष्ठा qib_devdata *dd, अक्षर *msg,
				     माप_प्रकार msgl)
अणु
	u64 hwerrs;
	u32 bits, ctrl;
	पूर्णांक isfatal = 0;
	अक्षर *bitsmsg;

	hwerrs = qib_पढ़ो_kreg64(dd, kr_hwerrstatus);
	अगर (!hwerrs)
		जाओ bail;
	अगर (hwerrs == ~0ULL) अणु
		qib_dev_err(dd,
			"Read of hardware error status failed (all bits set); ignoring\n");
		जाओ bail;
	पूर्ण
	qib_stats.sps_hwerrs++;

	/*
	 * Always clear the error status रेजिस्टर, except MEMBISTFAIL,
	 * regardless of whether we जारी or stop using the chip.
	 * We want that set so we know it failed, even across driver reload.
	 * We'll still ignore it in the hwerrmask.  We करो this partly क्रम
	 * diagnostics, but also क्रम support.
	 */
	qib_ग_लिखो_kreg(dd, kr_hwerrclear,
		       hwerrs & ~HWE_MASK(PowerOnBISTFailed));

	hwerrs &= dd->cspec->hwerrmask;

	अगर (hwerrs & ~(TXEMEMPARITYERR_PIOBUF | TXEMEMPARITYERR_PIOPBC |
		       RXE_PARITY))
		qib_devinfo(dd->pcidev,
			"Hardware error: hwerr=0x%llx (cleared)\n",
			(अचिन्हित दीर्घ दीर्घ) hwerrs);

	अगर (hwerrs & ~IB_HWE_BITSEXTANT)
		qib_dev_err(dd,
			"hwerror interrupt with unknown errors %llx set\n",
			(अचिन्हित दीर्घ दीर्घ) (hwerrs & ~IB_HWE_BITSEXTANT));

	अगर (hwerrs & QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR)
		qib_sd7220_clr_ibpar(dd);

	ctrl = qib_पढ़ो_kreg32(dd, kr_control);
	अगर ((ctrl & QLOGIC_IB_C_FREEZEMODE) && !dd->diag_client) अणु
		/*
		 * Parity errors in send memory are recoverable by h/w
		 * just करो housekeeping, निकास मुक्तze mode and जारी.
		 */
		अगर (hwerrs & (TXEMEMPARITYERR_PIOBUF |
			      TXEMEMPARITYERR_PIOPBC)) अणु
			qib_7220_txe_recover(dd);
			hwerrs &= ~(TXEMEMPARITYERR_PIOBUF |
				    TXEMEMPARITYERR_PIOPBC);
		पूर्ण
		अगर (hwerrs)
			isfatal = 1;
		अन्यथा
			qib_7220_clear_मुक्तze(dd);
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

	qib_क्रमmat_hwerrors(hwerrs, qib_7220_hwerror_msgs,
			    ARRAY_SIZE(qib_7220_hwerror_msgs), msg, msgl);

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

#घोषणा _QIB_PLL_FAIL (QLOGIC_IB_HWE_COREPLL_FBSLIP |   \
			 QLOGIC_IB_HWE_COREPLL_RFSLIP)

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
		 * If it occurs, it is left masked since the eternal
		 * पूर्णांकerface is unused.
		 */
		dd->cspec->hwerrmask &= ~QLOGIC_IB_HWE_SERDESPLLFAILED;
		qib_ग_लिखो_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);
	पूर्ण

	qib_dev_err(dd, "%s hardware error\n", msg);

	अगर (isfatal && !dd->diag_client) अणु
		qib_dev_err(dd,
			"Fatal Hardware Error, no longer usable, SN %.16s\n",
			dd->serial);
		/*
		 * For /sys status file and user programs to prपूर्णांक; अगर no
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
 * qib_7220_init_hwerrors - enable hardware errors
 * @dd: the qlogic_ib device
 *
 * now that we have finished initializing everything that might reasonably
 * cause a hardware error, and cleared those errors bits as they occur,
 * we can enable hardware errors in the mask (potentially enabling
 * मुक्तze mode), and enable hardware errors as errors (aदीर्घ with
 * everything अन्यथा) in errormask
 */
अटल व्योम qib_7220_init_hwerrors(काष्ठा qib_devdata *dd)
अणु
	u64 val;
	u64 extsval;

	extsval = qib_पढ़ो_kreg64(dd, kr_extstatus);

	अगर (!(extsval & (QLOGIC_IB_EXTS_MEMBIST_ENDTEST |
			 QLOGIC_IB_EXTS_MEMBIST_DISABLED)))
		qib_dev_err(dd, "MemBIST did not complete!\n");
	अगर (extsval & QLOGIC_IB_EXTS_MEMBIST_DISABLED)
		qib_devinfo(dd->pcidev, "MemBIST is disabled.\n");

	val = ~0ULL;    /* शेष to all hwerrors become पूर्णांकerrupts, */

	val &= ~QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR;
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
पूर्ण

/*
 * Disable and enable the armlaunch error.  Used क्रम PIO bandwidth testing
 * on chips that are count-based, rather than trigger-based.  There is no
 * reference counting, but that's also fine, given the पूर्णांकended use.
 * Only chip-specअगरic because it's all रेजिस्टर accesses
 */
अटल व्योम qib_set_7220_armlaunch(काष्ठा qib_devdata *dd, u32 enable)
अणु
	अगर (enable) अणु
		qib_ग_लिखो_kreg(dd, kr_errclear, ERR_MASK(SendPioArmLaunchErr));
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
अटल व्योम qib_set_ib_7220_lstate(काष्ठा qib_pportdata *ppd, u16 linkcmd,
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

	mod_wd = (linkcmd << IBA7220_IBCC_LINKCMD_SHIFT) |
		(linitcmd << QLOGIC_IB_IBCC_LINKINITCMD_SHIFT);

	qib_ग_लिखो_kreg(dd, kr_ibcctrl, ppd->cpspec->ibcctrl | mod_wd);
	/* ग_लिखो to chip to prevent back-to-back ग_लिखोs of ibc reg */
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);
पूर्ण

/*
 * All detailed पूर्णांकeraction with the SerDes has been moved to qib_sd7220.c
 *
 * The portion of IBA7220-specअगरic bringup_serdes() that actually deals with
 * रेजिस्टरs and memory within the SerDes itself is qib_sd7220_init().
 */

/**
 * qib_7220_bringup_serdes - bring up the serdes
 * @ppd: physical port on the qlogic_ib device
 */
अटल पूर्णांक qib_7220_bringup_serdes(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 val, prev_val, guid, ibc;
	पूर्णांक ret = 0;

	/* Put IBC in reset, sends disabled */
	dd->control &= ~QLOGIC_IB_C_LINKENABLE;
	qib_ग_लिखो_kreg(dd, kr_control, 0ULL);

	अगर (qib_compat_ddr_negotiate) अणु
		ppd->cpspec->ibdeltainprog = 1;
		ppd->cpspec->ibsymsnap = पढ़ो_7220_creg32(dd, cr_ibsymbolerr);
		ppd->cpspec->iblnkerrsnap =
			पढ़ो_7220_creg32(dd, cr_iblinkerrrecov);
	पूर्ण

	/* flowcontrolwatermark is in units of KBytes */
	ibc = 0x5ULL << SYM_LSB(IBCCtrl, FlowCtrlWaterMark);
	/*
	 * How often flowctrl sent.  More or less in usecs; balance against
	 * watermark value, so that in theory senders always get a flow
	 * control update in समय to not let the IB link go idle.
	 */
	ibc |= 0x3ULL << SYM_LSB(IBCCtrl, FlowCtrlPeriod);
	/* max error tolerance */
	ibc |= 0xfULL << SYM_LSB(IBCCtrl, PhyerrThreshold);
	/* use "real" buffer space क्रम */
	ibc |= 4ULL << SYM_LSB(IBCCtrl, CreditScale);
	/* IB credit flow control. */
	ibc |= 0xfULL << SYM_LSB(IBCCtrl, OverrunThreshold);
	/*
	 * set initial max size pkt IBC will send, including ICRC; it's the
	 * PIO buffer size in dwords, less 1; also see qib_set_mtu()
	 */
	ibc |= ((u64)(ppd->ibmaxlen >> 2) + 1) << SYM_LSB(IBCCtrl, MaxPktLen);
	ppd->cpspec->ibcctrl = ibc; /* without linkcmd or linkinitcmd! */

	/* initially come up रुकोing क्रम TS1, without sending anything. */
	val = ppd->cpspec->ibcctrl | (QLOGIC_IB_IBCC_LINKINITCMD_DISABLE <<
		QLOGIC_IB_IBCC_LINKINITCMD_SHIFT);
	qib_ग_लिखो_kreg(dd, kr_ibcctrl, val);

	अगर (!ppd->cpspec->ibcddrctrl) अणु
		/* not on re-init after reset */
		ppd->cpspec->ibcddrctrl = qib_पढ़ो_kreg64(dd, kr_ibcddrctrl);

		अगर (ppd->link_speed_enabled == (QIB_IB_SDR | QIB_IB_DDR))
			ppd->cpspec->ibcddrctrl |=
				IBA7220_IBC_SPEED_AUTONEG_MASK |
				IBA7220_IBC_IBTA_1_2_MASK;
		अन्यथा
			ppd->cpspec->ibcddrctrl |=
				ppd->link_speed_enabled == QIB_IB_DDR ?
				IBA7220_IBC_SPEED_DDR : IBA7220_IBC_SPEED_SDR;
		अगर ((ppd->link_width_enabled & (IB_WIDTH_1X | IB_WIDTH_4X)) ==
		    (IB_WIDTH_1X | IB_WIDTH_4X))
			ppd->cpspec->ibcddrctrl |= IBA7220_IBC_WIDTH_AUTONEG;
		अन्यथा
			ppd->cpspec->ibcddrctrl |=
				ppd->link_width_enabled == IB_WIDTH_4X ?
				IBA7220_IBC_WIDTH_4X_ONLY :
				IBA7220_IBC_WIDTH_1X_ONLY;

		/* always enable these on driver reload, not sticky */
		ppd->cpspec->ibcddrctrl |=
			IBA7220_IBC_RXPOL_MASK << IBA7220_IBC_RXPOL_SHIFT;
		ppd->cpspec->ibcddrctrl |=
			IBA7220_IBC_HRTBT_MASK << IBA7220_IBC_HRTBT_SHIFT;

		/* enable स्वतःmatic lane reversal detection क्रम receive */
		ppd->cpspec->ibcddrctrl |= IBA7220_IBC_LANE_REV_SUPPORTED;
	पूर्ण अन्यथा
		/* ग_लिखो to chip to prevent back-to-back ग_लिखोs of ibc reg */
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);

	qib_ग_लिखो_kreg(dd, kr_ibcddrctrl, ppd->cpspec->ibcddrctrl);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);

	qib_ग_लिखो_kreg(dd, kr_ncmodectrl, 0Ull);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);

	ret = qib_sd7220_init(dd);

	val = qib_पढ़ो_kreg64(dd, kr_xgxs_cfg);
	prev_val = val;
	val |= QLOGIC_IB_XGXS_FC_SAFE;
	अगर (val != prev_val) अणु
		qib_ग_लिखो_kreg(dd, kr_xgxs_cfg, val);
		qib_पढ़ो_kreg32(dd, kr_scratch);
	पूर्ण
	अगर (val & QLOGIC_IB_XGXS_RESET)
		val &= ~QLOGIC_IB_XGXS_RESET;
	अगर (val != prev_val)
		qib_ग_लिखो_kreg(dd, kr_xgxs_cfg, val);

	/* first समय through, set port guid */
	अगर (!ppd->guid)
		ppd->guid = dd->base_guid;
	guid = be64_to_cpu(ppd->guid);

	qib_ग_लिखो_kreg(dd, kr_hrtbt_guid, guid);
	अगर (!ret) अणु
		dd->control |= QLOGIC_IB_C_LINKENABLE;
		qib_ग_लिखो_kreg(dd, kr_control, dd->control);
	पूर्ण अन्यथा
		/* ग_लिखो to chip to prevent back-to-back ग_लिखोs of ibc reg */
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
	वापस ret;
पूर्ण

/**
 * qib_7220_quiet_serdes - set serdes to txidle
 * @ppd: physical port of the qlogic_ib device
 * Called when driver is being unloaded
 */
अटल व्योम qib_7220_quiet_serdes(काष्ठा qib_pportdata *ppd)
अणु
	u64 val;
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ flags;

	/* disable IBC */
	dd->control &= ~QLOGIC_IB_C_LINKENABLE;
	qib_ग_लिखो_kreg(dd, kr_control,
		       dd->control | QLOGIC_IB_C_FREEZEMODE);

	ppd->cpspec->chase_end = 0;
	अगर (ppd->cpspec->chase_समयr.function) /* अगर initted */
		del_समयr_sync(&ppd->cpspec->chase_समयr);

	अगर (ppd->cpspec->ibsymdelta || ppd->cpspec->iblnkerrdelta ||
	    ppd->cpspec->ibdeltainprog) अणु
		u64 diagc;

		/* enable counter ग_लिखोs */
		diagc = qib_पढ़ो_kreg64(dd, kr_hwdiagctrl);
		qib_ग_लिखो_kreg(dd, kr_hwdiagctrl,
			       diagc | SYM_MASK(HwDiagCtrl, CounterWrEnable));

		अगर (ppd->cpspec->ibsymdelta || ppd->cpspec->ibdeltainprog) अणु
			val = पढ़ो_7220_creg32(dd, cr_ibsymbolerr);
			अगर (ppd->cpspec->ibdeltainprog)
				val -= val - ppd->cpspec->ibsymsnap;
			val -= ppd->cpspec->ibsymdelta;
			ग_लिखो_7220_creg(dd, cr_ibsymbolerr, val);
		पूर्ण
		अगर (ppd->cpspec->iblnkerrdelta || ppd->cpspec->ibdeltainprog) अणु
			val = पढ़ो_7220_creg32(dd, cr_iblinkerrrecov);
			अगर (ppd->cpspec->ibdeltainprog)
				val -= val - ppd->cpspec->iblnkerrsnap;
			val -= ppd->cpspec->iblnkerrdelta;
			ग_लिखो_7220_creg(dd, cr_iblinkerrrecov, val);
		पूर्ण

		/* and disable counter ग_लिखोs */
		qib_ग_लिखो_kreg(dd, kr_hwdiagctrl, diagc);
	पूर्ण
	qib_set_ib_7220_lstate(ppd, 0, QLOGIC_IB_IBCC_LINKINITCMD_DISABLE);

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags &= ~QIBL_IB_AUTONEG_INPROG;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	wake_up(&ppd->cpspec->स्वतःneg_रुको);
	cancel_delayed_work_sync(&ppd->cpspec->स्वतःneg_work);

	shutकरोwn_7220_relock_poll(ppd->dd);
	val = qib_पढ़ो_kreg64(ppd->dd, kr_xgxs_cfg);
	val |= QLOGIC_IB_XGXS_RESET;
	qib_ग_लिखो_kreg(ppd->dd, kr_xgxs_cfg, val);
पूर्ण

/**
 * qib_setup_7220_setextled - set the state of the two बाह्यal LEDs
 * @ppd: the qlogic_ib device
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
 *
 */
अटल व्योम qib_setup_7220_setextled(काष्ठा qib_pportdata *ppd, u32 on)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 extctl, ledblink = 0, val, lst, ltst;
	अचिन्हित दीर्घ flags;

	/*
	 * The diags use the LED to indicate diag info, so we leave
	 * the बाह्यal LED alone when the diags are running.
	 */
	अगर (dd->diag_client)
		वापस;

	अगर (ppd->led_override) अणु
		ltst = (ppd->led_override & QIB_LED_PHYS) ?
			IB_PHYSPORTSTATE_LINKUP : IB_PHYSPORTSTATE_DISABLED,
		lst = (ppd->led_override & QIB_LED_LOG) ?
			IB_PORT_ACTIVE : IB_PORT_DOWN;
	पूर्ण अन्यथा अगर (on) अणु
		val = qib_पढ़ो_kreg64(dd, kr_ibcstatus);
		ltst = qib_7220_phys_portstate(val);
		lst = qib_7220_iblink_state(val);
	पूर्ण अन्यथा अणु
		ltst = 0;
		lst = 0;
	पूर्ण

	spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
	extctl = dd->cspec->extctrl & ~(SYM_MASK(EXTCtrl, LEDPriPortGreenOn) |
				 SYM_MASK(EXTCtrl, LEDPriPortYellowOn));
	अगर (ltst == IB_PHYSPORTSTATE_LINKUP) अणु
		extctl |= SYM_MASK(EXTCtrl, LEDPriPortGreenOn);
		/*
		 * counts are in chip घड़ी (4ns) periods.
		 * This is 1/16 sec (66.6ms) on,
		 * 3/16 sec (187.5 ms) off, with packets rcvd
		 */
		ledblink = ((66600 * 1000UL / 4) << IBA7220_LEDBLINK_ON_SHIFT)
			| ((187500 * 1000UL / 4) << IBA7220_LEDBLINK_OFF_SHIFT);
	पूर्ण
	अगर (lst == IB_PORT_ACTIVE)
		extctl |= SYM_MASK(EXTCtrl, LEDPriPortYellowOn);
	dd->cspec->extctrl = extctl;
	qib_ग_लिखो_kreg(dd, kr_extctrl, extctl);
	spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);

	अगर (ledblink) /* blink the LED on packet receive */
		qib_ग_लिखो_kreg(dd, kr_rcvpktledcnt, ledblink);
पूर्ण

/*
 * qib_setup_7220_cleanup - clean up any per-chip chip-specअगरic stuff
 * @dd: the qlogic_ib device
 *
 * This is called during driver unload.
 *
 */
अटल व्योम qib_setup_7220_cleanup(काष्ठा qib_devdata *dd)
अणु
	qib_मुक्त_irq(dd);
	kमुक्त(dd->cspec->cntrs);
	kमुक्त(dd->cspec->portcntrs);
पूर्ण

/*
 * This is only called क्रम SDmaInt.
 * SDmaDisabled is handled on the error path.
 */
अटल व्योम sdma_7220_पूर्णांकr(काष्ठा qib_pportdata *ppd, u64 istat)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	चयन (ppd->sdma_state.current_state) अणु
	हाल qib_sdma_state_s00_hw_करोwn:
		अवरोध;

	हाल qib_sdma_state_s10_hw_start_up_रुको:
		__qib_sdma_process_event(ppd, qib_sdma_event_e20_hw_started);
		अवरोध;

	हाल qib_sdma_state_s20_idle:
		अवरोध;

	हाल qib_sdma_state_s30_sw_clean_up_रुको:
		अवरोध;

	हाल qib_sdma_state_s40_hw_clean_up_रुको:
		अवरोध;

	हाल qib_sdma_state_s50_hw_halt_रुको:
		__qib_sdma_process_event(ppd, qib_sdma_event_e60_hw_halted);
		अवरोध;

	हाल qib_sdma_state_s99_running:
		/* too chatty to prपूर्णांक here */
		__qib_sdma_पूर्णांकr(ppd);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
पूर्ण

अटल व्योम qib_wantpiobuf_7220_पूर्णांकr(काष्ठा qib_devdata *dd, u32 needपूर्णांक)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);
	अगर (needपूर्णांक) अणु
		अगर (!(dd->sendctrl & SYM_MASK(SendCtrl, SendBufAvailUpd)))
			जाओ करोne;
		/*
		 * blip the availupd off, next ग_लिखो will be on, so
		 * we ensure an avail update, regardless of threshold or
		 * buffers becoming मुक्त, whenever we want an पूर्णांकerrupt
		 */
		qib_ग_लिखो_kreg(dd, kr_sendctrl, dd->sendctrl &
			~SYM_MASK(SendCtrl, SendBufAvailUpd));
		qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
		dd->sendctrl |= SYM_MASK(SendCtrl, SendIntBufAvail);
	पूर्ण अन्यथा
		dd->sendctrl &= ~SYM_MASK(SendCtrl, SendIntBufAvail);
	qib_ग_लिखो_kreg(dd, kr_sendctrl, dd->sendctrl);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0ULL);
करोne:
	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
पूर्ण

/*
 * Handle errors and unusual events first, separate function
 * to improve cache hits क्रम fast path पूर्णांकerrupt handling.
 */
अटल noअंतरभूत व्योम unlikely_7220_पूर्णांकr(काष्ठा qib_devdata *dd, u64 istat)
अणु
	अगर (unlikely(istat & ~QLOGIC_IB_I_BITSEXTANT))
		qib_dev_err(dd,
			    "interrupt with unknown interrupts %Lx set\n",
			    istat & ~QLOGIC_IB_I_BITSEXTANT);

	अगर (istat & QLOGIC_IB_I_GPIO) अणु
		u32 gpiostatus;

		/*
		 * Boards क्रम this chip currently करोn't use GPIO पूर्णांकerrupts,
		 * so clear by writing GPIOstatus to GPIOclear, and complain
		 * to alert developer. To aव्योम endless repeats, clear
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

		अगर (gpiostatus) अणु
			स्थिर u32 mask = qib_पढ़ो_kreg32(dd, kr_gpio_mask);
			u32 gpio_irq = mask & gpiostatus;

			/*
			 * A bit set in status and (chip) Mask रेजिस्टर
			 * would cause an पूर्णांकerrupt. Since we are not
			 * expecting any, report it. Also check that the
			 * chip reflects our shaकरोw, report issues,
			 * and refresh from the shaकरोw.
			 */
			/*
			 * Clear any troublemakers, and update chip
			 * from shaकरोw
			 */
			dd->cspec->gpio_mask &= ~gpio_irq;
			qib_ग_लिखो_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
		पूर्ण
	पूर्ण

	अगर (istat & QLOGIC_IB_I_ERROR) अणु
		u64 estat;

		qib_stats.sps_errपूर्णांकs++;
		estat = qib_पढ़ो_kreg64(dd, kr_errstatus);
		अगर (!estat)
			qib_devinfo(dd->pcidev,
				"error interrupt (%Lx), but no error bits set!\n",
				istat);
		अन्यथा
			handle_7220_errors(dd, estat);
	पूर्ण
पूर्ण

अटल irqवापस_t qib_7220पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qib_devdata *dd = data;
	irqवापस_t ret;
	u64 istat;
	u64 ctxtrbits;
	u64 rmask;
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

	istat = qib_पढ़ो_kreg64(dd, kr_पूर्णांकstatus);

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
		unlikely_7220_पूर्णांकr(dd, istat);

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
		rmask = (1ULL << QLOGIC_IB_I_RCVAVAIL_SHIFT) |
			(1ULL << QLOGIC_IB_I_RCVURG_SHIFT);
		क्रम (i = 0; i < dd->first_user_ctxt; i++) अणु
			अगर (ctxtrbits & rmask) अणु
				ctxtrbits &= ~rmask;
				qib_kreceive(dd->rcd[i], शून्य, शून्य);
			पूर्ण
			rmask <<= 1;
		पूर्ण
		अगर (ctxtrbits) अणु
			ctxtrbits =
				(ctxtrbits >> QLOGIC_IB_I_RCVAVAIL_SHIFT) |
				(ctxtrbits >> QLOGIC_IB_I_RCVURG_SHIFT);
			qib_handle_urcv(dd, ctxtrbits);
		पूर्ण
	पूर्ण

	/* only call क्रम SDmaInt */
	अगर (istat & QLOGIC_IB_I_SDMAINT)
		sdma_7220_पूर्णांकr(dd->pport, istat);

	अगर ((istat & QLOGIC_IB_I_SPIOBUFAVAIL) && (dd->flags & QIB_INITTED))
		qib_ib_piobufavail(dd);

	ret = IRQ_HANDLED;
bail:
	वापस ret;
पूर्ण

/*
 * Set up our chip-specअगरic पूर्णांकerrupt handler.
 * The पूर्णांकerrupt type has alपढ़ोy been setup, so
 * we just need to करो the registration and error checking.
 * If we are using MSI पूर्णांकerrupts, we may fall back to
 * INTx later, अगर the पूर्णांकerrupt handler करोesn't get called
 * within 1/2 second (see verअगरy_पूर्णांकerrupt()).
 */
अटल व्योम qib_setup_7220_पूर्णांकerrupt(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret;

	ret = pci_request_irq(dd->pcidev, 0, qib_7220पूर्णांकr, शून्य, dd,
			      QIB_DRV_NAME);
	अगर (ret)
		qib_dev_err(dd, "Couldn't setup %s interrupt (irq=%d): %d\n",
			    dd->pcidev->msi_enabled ?  "MSI" : "INTx",
			    pci_irq_vector(dd->pcidev, 0), ret);
पूर्ण

/**
 * qib_7220_boardname - fill in the board name
 * @dd: the qlogic_ib device
 *
 * info is based on the board revision रेजिस्टर
 */
अटल व्योम qib_7220_boardname(काष्ठा qib_devdata *dd)
अणु
	u32 boardid;

	boardid = SYM_FIELD(dd->revision, Revision,
			    BoardID);

	चयन (boardid) अणु
	हाल 1:
		dd->boardname = "InfiniPath_QLE7240";
		अवरोध;
	हाल 2:
		dd->boardname = "InfiniPath_QLE7280";
		अवरोध;
	शेष:
		qib_dev_err(dd, "Unknown 7220 board with ID %u\n", boardid);
		dd->boardname = "Unknown_InfiniPath_7220";
		अवरोध;
	पूर्ण

	अगर (dd->majrev != 5 || !dd->minrev || dd->minrev > 2)
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
 * from पूर्णांकerrupt context.
 */
अटल पूर्णांक qib_setup_7220_reset(काष्ठा qib_devdata *dd)
अणु
	u64 val;
	पूर्णांक i;
	पूर्णांक ret;
	u16 cmdval;
	u8 पूर्णांक_line, clinesz;
	अचिन्हित दीर्घ flags;

	qib_pcie_अ_लोmd(dd, &cmdval, &पूर्णांक_line, &clinesz);

	/* Use dev_err so it shows up in logs, etc. */
	qib_dev_err(dd, "Resetting InfiniPath unit %u\n", dd->unit);

	/* no पूर्णांकerrupts till re-initted */
	qib_7220_set_पूर्णांकr_state(dd, 0);

	dd->pport->cpspec->ibdeltainprog = 0;
	dd->pport->cpspec->ibsymdelta = 0;
	dd->pport->cpspec->iblnkerrdelta = 0;

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
	mb(); /* prevent compiler reordering around actual reset */

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

		/* hold IBC in reset, no sends, etc till later */
		qib_ग_लिखो_kreg(dd, kr_control, 0ULL);

		/* clear the reset error, init error/hwerror mask */
		qib_7220_init_hwerrors(dd);

		/* करो setup similar to speed or link-width changes */
		अगर (dd->pport->cpspec->ibcddrctrl & IBA7220_IBC_IBTA_1_2_MASK)
			dd->cspec->presets_needed = 1;
		spin_lock_irqsave(&dd->pport->lflags_lock, flags);
		dd->pport->lflags |= QIBL_IB_FORCE_NOTIFY;
		dd->pport->lflags &= ~QIBL_IB_AUTONEG_FAILED;
		spin_unlock_irqrestore(&dd->pport->lflags_lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * qib_7220_put_tid - ग_लिखो a TID to the chip
 * @dd: the qlogic_ib device
 * @tidptr: poपूर्णांकer to the expected TID (in chip) to update
 * @type: 0 क्रम eager, 1 क्रम expected
 * @pa: physical address of in memory buffer; tidinvalid अगर मुक्तing
 */
अटल व्योम qib_7220_put_tid(काष्ठा qib_devdata *dd, u64 __iomem *tidptr,
			     u32 type, अचिन्हित दीर्घ pa)
अणु
	अगर (pa != dd->tidinvalid) अणु
		u64 chippa = pa >> IBA7220_TID_PA_SHIFT;

		/* paranoia checks */
		अगर (pa != (chippa << IBA7220_TID_PA_SHIFT)) अणु
			qib_dev_err(dd, "Physaddr %lx not 2KB aligned!\n",
				    pa);
			वापस;
		पूर्ण
		अगर (chippa >= (1UL << IBA7220_TID_SZ_SHIFT)) अणु
			qib_dev_err(dd,
				"Physical page address 0x%lx larger than supported\n",
				pa);
			वापस;
		पूर्ण

		अगर (type == RCVHQ_RCV_TYPE_EAGER)
			chippa |= dd->tidढाँचा;
		अन्यथा /* क्रम now, always full 4KB page */
			chippa |= IBA7220_TID_SZ_4K;
		pa = chippa;
	पूर्ण
	ग_लिखोq(pa, tidptr);
पूर्ण

/**
 * qib_7220_clear_tids - clear all TID entries क्रम a ctxt, expected and eager
 * @dd: the qlogic_ib device
 * @rcd: the ctxt
 *
 * clear all TID entries क्रम a ctxt, expected and eager.
 * Used from qib_बंद().  On this chip, TIDs are only 32 bits,
 * not 64, but they are still on 64 bit boundaries, so tidbase
 * is declared as u64 * क्रम the poपूर्णांकer math, even though we ग_लिखो 32 bits
 */
अटल व्योम qib_7220_clear_tids(काष्ठा qib_devdata *dd,
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
		qib_7220_put_tid(dd, &tidbase[i], RCVHQ_RCV_TYPE_EXPECTED,
				 tidinv);

	tidbase = (u64 __iomem *)
		((अक्षर __iomem *)(dd->kregbase) +
		 dd->rcvegrbase +
		 rcd->rcvegr_tid_base * माप(*tidbase));

	क्रम (i = 0; i < rcd->rcvegrcnt; i++)
		qib_7220_put_tid(dd, &tidbase[i], RCVHQ_RCV_TYPE_EAGER,
				 tidinv);
पूर्ण

/**
 * qib_7220_tidढाँचा - setup स्थिरants क्रम TID updates
 * @dd: the qlogic_ib device
 *
 * We setup stuff that we use a lot, to aव्योम calculating each समय
 */
अटल व्योम qib_7220_tidढाँचा(काष्ठा qib_devdata *dd)
अणु
	अगर (dd->rcvegrbufsize == 2048)
		dd->tidढाँचा = IBA7220_TID_SZ_2K;
	अन्यथा अगर (dd->rcvegrbufsize == 4096)
		dd->tidढाँचा = IBA7220_TID_SZ_4K;
	dd->tidinvalid = 0;
पूर्ण

/**
 * qib_7220_get_base_info - set chip-specअगरic flags क्रम user code
 * @rcd: the qlogic_ib ctxt
 * @kinfo: qib_base_info poपूर्णांकer
 *
 * We set the PCIE flag because the lower bandwidth on PCIe vs
 * HyperTransport can affect some user packet algorithims.
 */
अटल पूर्णांक qib_7220_get_base_info(काष्ठा qib_ctxtdata *rcd,
				  काष्ठा qib_base_info *kinfo)
अणु
	kinfo->spi_runसमय_flags |= QIB_RUNTIME_PCIE |
		QIB_RUNTIME_NODMA_RTAIL | QIB_RUNTIME_SDMA;

	अगर (rcd->dd->flags & QIB_USE_SPCL_TRIG)
		kinfo->spi_runसमय_flags |= QIB_RUNTIME_SPECIAL_TRIGGER;

	वापस 0;
पूर्ण

अटल काष्ठा qib_message_header *
qib_7220_get_msgheader(काष्ठा qib_devdata *dd, __le32 *rhf_addr)
अणु
	u32 offset = qib_hdrget_offset(rhf_addr);

	वापस (काष्ठा qib_message_header *)
		(rhf_addr - dd->rhf_offset + offset);
पूर्ण

अटल व्योम qib_7220_config_ctxts(काष्ठा qib_devdata *dd)
अणु
	अचिन्हित दीर्घ flags;
	u32 nchipctxts;

	nchipctxts = qib_पढ़ो_kreg32(dd, kr_portcnt);
	dd->cspec->numctxts = nchipctxts;
	अगर (qib_n_krcv_queues > 1) अणु
		dd->qpn_mask = 0x3e;
		dd->first_user_ctxt = qib_n_krcv_queues * dd->num_pports;
		अगर (dd->first_user_ctxt > nchipctxts)
			dd->first_user_ctxt = nchipctxts;
	पूर्ण अन्यथा
		dd->first_user_ctxt = dd->num_pports;
	dd->n_krcv_queues = dd->first_user_ctxt;

	अगर (!qib_cfgctxts) अणु
		पूर्णांक nctxts = dd->first_user_ctxt + num_online_cpus();

		अगर (nctxts <= 5)
			dd->ctxtcnt = 5;
		अन्यथा अगर (nctxts <= 9)
			dd->ctxtcnt = 9;
		अन्यथा अगर (nctxts <= nchipctxts)
			dd->ctxtcnt = nchipctxts;
	पूर्ण अन्यथा अगर (qib_cfgctxts <= nchipctxts)
		dd->ctxtcnt = qib_cfgctxts;
	अगर (!dd->ctxtcnt) /* none of the above, set to max */
		dd->ctxtcnt = nchipctxts;

	/*
	 * Chip can be configured क्रम 5, 9, or 17 ctxts, and choice
	 * affects number of eager TIDs per ctxt (1K, 2K, 4K).
	 * Lock to be paranoid about later motion, etc.
	 */
	spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);
	अगर (dd->ctxtcnt > 9)
		dd->rcvctrl |= 2ULL << IBA7220_R_CTXTCFG_SHIFT;
	अन्यथा अगर (dd->ctxtcnt > 5)
		dd->rcvctrl |= 1ULL << IBA7220_R_CTXTCFG_SHIFT;
	/* अन्यथा configure क्रम शेष 5 receive ctxts */
	अगर (dd->qpn_mask)
		dd->rcvctrl |= 1ULL << QIB_7220_RcvCtrl_RcvQPMapEnable_LSB;
	qib_ग_लिखो_kreg(dd, kr_rcvctrl, dd->rcvctrl);
	spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);

	/* kr_rcvegrcnt changes based on the number of contexts enabled */
	dd->cspec->rcvegrcnt = qib_पढ़ो_kreg32(dd, kr_rcvegrcnt);
	dd->rcvhdrcnt = max(dd->cspec->rcvegrcnt, IBA7220_KRCVEGRCNT);
पूर्ण

अटल पूर्णांक qib_7220_get_ib_cfg(काष्ठा qib_pportdata *ppd, पूर्णांक which)
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
		lsb = IBA7220_IBC_RXPOL_SHIFT;
		maskr = IBA7220_IBC_RXPOL_MASK;
		अवरोध;

	हाल QIB_IB_CFG_LREV_ENB: /* Get Auto-Lane-reversal enable */
		lsb = IBA7220_IBC_LREV_SHIFT;
		maskr = IBA7220_IBC_LREV_MASK;
		अवरोध;

	हाल QIB_IB_CFG_LINKLATENCY:
		ret = qib_पढ़ो_kreg64(ppd->dd, kr_ibcddrstatus)
			& IBA7220_DDRSTAT_LINKLAT_MASK;
		जाओ करोne;

	हाल QIB_IB_CFG_OP_VLS:
		ret = ppd->vls_operational;
		जाओ करोne;

	हाल QIB_IB_CFG_VL_HIGH_CAP:
		ret = 0;
		जाओ करोne;

	हाल QIB_IB_CFG_VL_LOW_CAP:
		ret = 0;
		जाओ करोne;

	हाल QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		ret = SYM_FIELD(ppd->cpspec->ibcctrl, IBCCtrl,
				OverrunThreshold);
		जाओ करोne;

	हाल QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		ret = SYM_FIELD(ppd->cpspec->ibcctrl, IBCCtrl,
				PhyerrThreshold);
		जाओ करोne;

	हाल QIB_IB_CFG_LINKDEFAULT: /* IB link शेष (sleep/poll) */
		/* will only take effect when the link state changes */
		ret = (ppd->cpspec->ibcctrl &
		       SYM_MASK(IBCCtrl, LinkDownDefaultState)) ?
			IB_LINKINITCMD_SLEEP : IB_LINKINITCMD_POLL;
		जाओ करोne;

	हाल QIB_IB_CFG_HRTBT: /* Get Heartbeat off/enable/स्वतः */
		lsb = IBA7220_IBC_HRTBT_SHIFT;
		maskr = IBA7220_IBC_HRTBT_MASK;
		अवरोध;

	हाल QIB_IB_CFG_PMA_TICKS:
		/*
		 * 0x00 = 10x link transfer rate or 4 nsec. क्रम 2.5Gbs
		 * Since the घड़ी is always 250MHz, the value is 1 or 0.
		 */
		ret = (ppd->link_speed_active == QIB_IB_DDR);
		जाओ करोne;

	शेष:
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	ret = (पूर्णांक)((ppd->cpspec->ibcddrctrl >> lsb) & maskr);
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_7220_set_ib_cfg(काष्ठा qib_pportdata *ppd, पूर्णांक which, u32 val)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 maskr; /* right-justअगरied mask */
	पूर्णांक lsb, ret = 0, setक्रमce = 0;
	u16 lcmd, licmd;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp = 0;

	चयन (which) अणु
	हाल QIB_IB_CFG_LIDLMC:
		/*
		 * Set LID and LMC. Combined to aव्योम possible hazard
		 * caller माला_दो LMC in 16MSbits, DLID in 16LSbits of val
		 */
		lsb = IBA7220_IBC_DLIDLMC_SHIFT;
		maskr = IBA7220_IBC_DLIDLMC_MASK;
		अवरोध;

	हाल QIB_IB_CFG_LWID_ENB: /* set allowed Link-width */
		/*
		 * As with speed, only ग_लिखो the actual रेजिस्टर अगर
		 * the link is currently करोwn, otherwise takes effect
		 * on next link change.
		 */
		ppd->link_width_enabled = val;
		अगर (!(ppd->lflags & QIBL_LINKDOWN))
			जाओ bail;
		/*
		 * We set the QIBL_IB_FORCE_NOTIFY bit so upकरोwn
		 * will get called because we want update
		 * link_width_active, and the change may not take
		 * effect क्रम some समय (अगर we are in POLL), so this
		 * flag will क्रमce the upकरोwn routine to be called
		 * on the next ibstatuschange करोwn पूर्णांकerrupt, even
		 * अगर it's not an करोwn->up transition.
		 */
		val--; /* convert from IB to chip */
		maskr = IBA7220_IBC_WIDTH_MASK;
		lsb = IBA7220_IBC_WIDTH_SHIFT;
		setक्रमce = 1;
		अवरोध;

	हाल QIB_IB_CFG_SPD_ENB: /* set allowed Link speeds */
		/*
		 * If we turn off IB1.2, need to preset SerDes शेषs,
		 * but not right now. Set a flag क्रम the next समय
		 * we command the link करोwn.  As with width, only ग_लिखो the
		 * actual रेजिस्टर अगर the link is currently करोwn, otherwise
		 * takes effect on next link change.  Since setting is being
		 * explicitly requested (via MAD or sysfs), clear स्वतःneg
		 * failure status अगर speed स्वतःneg is enabled.
		 */
		ppd->link_speed_enabled = val;
		अगर ((ppd->cpspec->ibcddrctrl & IBA7220_IBC_IBTA_1_2_MASK) &&
		    !(val & (val - 1)))
			dd->cspec->presets_needed = 1;
		अगर (!(ppd->lflags & QIBL_LINKDOWN))
			जाओ bail;
		/*
		 * We set the QIBL_IB_FORCE_NOTIFY bit so upकरोwn
		 * will get called because we want update
		 * link_speed_active, and the change may not take
		 * effect क्रम some समय (अगर we are in POLL), so this
		 * flag will क्रमce the upकरोwn routine to be called
		 * on the next ibstatuschange करोwn पूर्णांकerrupt, even
		 * अगर it's not an करोwn->up transition.
		 */
		अगर (val == (QIB_IB_SDR | QIB_IB_DDR)) अणु
			val = IBA7220_IBC_SPEED_AUTONEG_MASK |
				IBA7220_IBC_IBTA_1_2_MASK;
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			ppd->lflags &= ~QIBL_IB_AUTONEG_FAILED;
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		पूर्ण अन्यथा
			val = val == QIB_IB_DDR ?
				IBA7220_IBC_SPEED_DDR : IBA7220_IBC_SPEED_SDR;
		maskr = IBA7220_IBC_SPEED_AUTONEG_MASK |
			IBA7220_IBC_IBTA_1_2_MASK;
		/* IBTA 1.2 mode + speed bits are contiguous */
		lsb = SYM_LSB(IBCDDRCtrl, IB_ENHANCED_MODE);
		setक्रमce = 1;
		अवरोध;

	हाल QIB_IB_CFG_RXPOL_ENB: /* set Auto-RX-polarity enable */
		lsb = IBA7220_IBC_RXPOL_SHIFT;
		maskr = IBA7220_IBC_RXPOL_MASK;
		अवरोध;

	हाल QIB_IB_CFG_LREV_ENB: /* set Auto-Lane-reversal enable */
		lsb = IBA7220_IBC_LREV_SHIFT;
		maskr = IBA7220_IBC_LREV_MASK;
		अवरोध;

	हाल QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		maskr = SYM_FIELD(ppd->cpspec->ibcctrl, IBCCtrl,
				  OverrunThreshold);
		अगर (maskr != val) अणु
			ppd->cpspec->ibcctrl &=
				~SYM_MASK(IBCCtrl, OverrunThreshold);
			ppd->cpspec->ibcctrl |= (u64) val <<
				SYM_LSB(IBCCtrl, OverrunThreshold);
			qib_ग_लिखो_kreg(dd, kr_ibcctrl, ppd->cpspec->ibcctrl);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		पूर्ण
		जाओ bail;

	हाल QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		maskr = SYM_FIELD(ppd->cpspec->ibcctrl, IBCCtrl,
				  PhyerrThreshold);
		अगर (maskr != val) अणु
			ppd->cpspec->ibcctrl &=
				~SYM_MASK(IBCCtrl, PhyerrThreshold);
			ppd->cpspec->ibcctrl |= (u64) val <<
				SYM_LSB(IBCCtrl, PhyerrThreshold);
			qib_ग_लिखो_kreg(dd, kr_ibcctrl, ppd->cpspec->ibcctrl);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		पूर्ण
		जाओ bail;

	हाल QIB_IB_CFG_PKEYS: /* update pkeys */
		maskr = (u64) ppd->pkeys[0] | ((u64) ppd->pkeys[1] << 16) |
			((u64) ppd->pkeys[2] << 32) |
			((u64) ppd->pkeys[3] << 48);
		qib_ग_लिखो_kreg(dd, kr_partitionkey, maskr);
		जाओ bail;

	हाल QIB_IB_CFG_LINKDEFAULT: /* IB link शेष (sleep/poll) */
		/* will only take effect when the link state changes */
		अगर (val == IB_LINKINITCMD_POLL)
			ppd->cpspec->ibcctrl &=
				~SYM_MASK(IBCCtrl, LinkDownDefaultState);
		अन्यथा /* SLEEP */
			ppd->cpspec->ibcctrl |=
				SYM_MASK(IBCCtrl, LinkDownDefaultState);
		qib_ग_लिखो_kreg(dd, kr_ibcctrl, ppd->cpspec->ibcctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
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
		ppd->cpspec->ibcctrl &= ~SYM_MASK(IBCCtrl, MaxPktLen);
		ppd->cpspec->ibcctrl |= (u64)val << SYM_LSB(IBCCtrl, MaxPktLen);
		qib_ग_लिखो_kreg(dd, kr_ibcctrl, ppd->cpspec->ibcctrl);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		जाओ bail;

	हाल QIB_IB_CFG_LSTATE: /* set the IB link state */
		चयन (val & 0xffff0000) अणु
		हाल IB_LINKCMD_DOWN:
			lcmd = QLOGIC_IB_IBCC_LINKCMD_DOWN;
			अगर (!ppd->cpspec->ibdeltainprog &&
			    qib_compat_ddr_negotiate) अणु
				ppd->cpspec->ibdeltainprog = 1;
				ppd->cpspec->ibsymsnap =
					पढ़ो_7220_creg32(dd, cr_ibsymbolerr);
				ppd->cpspec->iblnkerrsnap =
					पढ़ो_7220_creg32(dd, cr_iblinkerrrecov);
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
		qib_set_ib_7220_lstate(ppd, lcmd, licmd);

		maskr = IBA7220_IBC_WIDTH_MASK;
		lsb = IBA7220_IBC_WIDTH_SHIFT;
		पंचांगp = (ppd->cpspec->ibcddrctrl >> lsb) & maskr;
		/* If the width active on the chip करोes not match the
		 * width in the shaकरोw रेजिस्टर, ग_लिखो the new active
		 * width to the chip.
		 * We करोn't have to worry about speed as the speed is taken
		 * care of by set_7220_ibspeed_fast called by ib_upकरोwn.
		 */
		अगर (ppd->link_width_enabled-1 != पंचांगp) अणु
			ppd->cpspec->ibcddrctrl &= ~(maskr << lsb);
			ppd->cpspec->ibcddrctrl |=
				(((u64)(ppd->link_width_enabled-1) & maskr) <<
				 lsb);
			qib_ग_लिखो_kreg(dd, kr_ibcddrctrl,
				       ppd->cpspec->ibcddrctrl);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0);
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			ppd->lflags |= QIBL_IB_FORCE_NOTIFY;
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		पूर्ण
		जाओ bail;

	हाल QIB_IB_CFG_HRTBT: /* set Heartbeat off/enable/स्वतः */
		अगर (val > IBA7220_IBC_HRTBT_MASK) अणु
			ret = -EINVAL;
			जाओ bail;
		पूर्ण
		lsb = IBA7220_IBC_HRTBT_SHIFT;
		maskr = IBA7220_IBC_HRTBT_MASK;
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	ppd->cpspec->ibcddrctrl &= ~(maskr << lsb);
	ppd->cpspec->ibcddrctrl |= (((u64) val & maskr) << lsb);
	qib_ग_लिखो_kreg(dd, kr_ibcddrctrl, ppd->cpspec->ibcddrctrl);
	qib_ग_लिखो_kreg(dd, kr_scratch, 0);
	अगर (setक्रमce) अणु
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags |= QIBL_IB_FORCE_NOTIFY;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	पूर्ण
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_7220_set_loopback(काष्ठा qib_pportdata *ppd, स्थिर अक्षर *what)
अणु
	पूर्णांक ret = 0;
	u64 val, ddr;

	अगर (!म_भेदन(what, "ibc", 3)) अणु
		ppd->cpspec->ibcctrl |= SYM_MASK(IBCCtrl, Loopback);
		val = 0; /* disable heart beat, so link will come up */
		qib_devinfo(ppd->dd->pcidev, "Enabling IB%u:%u IBC loopback\n",
			 ppd->dd->unit, ppd->port);
	पूर्ण अन्यथा अगर (!म_भेदन(what, "off", 3)) अणु
		ppd->cpspec->ibcctrl &= ~SYM_MASK(IBCCtrl, Loopback);
		/* enable heart beat again */
		val = IBA7220_IBC_HRTBT_MASK << IBA7220_IBC_HRTBT_SHIFT;
		qib_devinfo(ppd->dd->pcidev,
			"Disabling IB%u:%u IBC loopback (normal)\n",
			ppd->dd->unit, ppd->port);
	पूर्ण अन्यथा
		ret = -EINVAL;
	अगर (!ret) अणु
		qib_ग_लिखो_kreg(ppd->dd, kr_ibcctrl, ppd->cpspec->ibcctrl);
		ddr = ppd->cpspec->ibcddrctrl & ~(IBA7220_IBC_HRTBT_MASK
					     << IBA7220_IBC_HRTBT_SHIFT);
		ppd->cpspec->ibcddrctrl = ddr | val;
		qib_ग_लिखो_kreg(ppd->dd, kr_ibcddrctrl,
			       ppd->cpspec->ibcddrctrl);
		qib_ग_लिखो_kreg(ppd->dd, kr_scratch, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम qib_update_7220_usrhead(काष्ठा qib_ctxtdata *rcd, u64 hd,
				    u32 updegr, u32 egrhd, u32 npkts)
अणु
	अगर (updegr)
		qib_ग_लिखो_ureg(rcd->dd, ur_rcvegrindexhead, egrhd, rcd->ctxt);
	qib_ग_लिखो_ureg(rcd->dd, ur_rcvhdrhead, hd, rcd->ctxt);
पूर्ण

अटल u32 qib_7220_hdrqempty(काष्ठा qib_ctxtdata *rcd)
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
 * Modअगरy the RCVCTRL रेजिस्टर in chip-specअगरic way. This
 * is a function because bit positions and (future) रेजिस्टर
 * location is chip-specअगरc, but the needed operations are
 * generic. <op> is a bit-mask because we often want to
 * करो multiple modअगरications.
 */
अटल व्योम rcvctrl_7220_mod(काष्ठा qib_pportdata *ppd, अचिन्हित पूर्णांक op,
			     पूर्णांक ctxt)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 mask, val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);
	अगर (op & QIB_RCVCTRL_TAILUPD_ENB)
		dd->rcvctrl |= (1ULL << IBA7220_R_TAILUPD_SHIFT);
	अगर (op & QIB_RCVCTRL_TAILUPD_DIS)
		dd->rcvctrl &= ~(1ULL << IBA7220_R_TAILUPD_SHIFT);
	अगर (op & QIB_RCVCTRL_PKEY_ENB)
		dd->rcvctrl &= ~(1ULL << IBA7220_R_PKEY_DIS_SHIFT);
	अगर (op & QIB_RCVCTRL_PKEY_DIS)
		dd->rcvctrl |= (1ULL << IBA7220_R_PKEY_DIS_SHIFT);
	अगर (ctxt < 0)
		mask = (1ULL << dd->ctxtcnt) - 1;
	अन्यथा
		mask = (1ULL << ctxt);
	अगर (op & QIB_RCVCTRL_CTXT_ENB) अणु
		/* always करोne क्रम specअगरic ctxt */
		dd->rcvctrl |= (mask << SYM_LSB(RcvCtrl, PortEnable));
		अगर (!(dd->flags & QIB_NODMA_RTAIL))
			dd->rcvctrl |= 1ULL << IBA7220_R_TAILUPD_SHIFT;
		/* Write these रेजिस्टरs beक्रमe the context is enabled. */
		qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdrtailaddr, ctxt,
			dd->rcd[ctxt]->rcvhdrqtailaddr_phys);
		qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdraddr, ctxt,
			dd->rcd[ctxt]->rcvhdrq_phys);
		dd->rcd[ctxt]->seq_cnt = 1;
	पूर्ण
	अगर (op & QIB_RCVCTRL_CTXT_DIS)
		dd->rcvctrl &= ~(mask << SYM_LSB(RcvCtrl, PortEnable));
	अगर (op & QIB_RCVCTRL_INTRAVAIL_ENB)
		dd->rcvctrl |= (mask << IBA7220_R_INTRAVAIL_SHIFT);
	अगर (op & QIB_RCVCTRL_INTRAVAIL_DIS)
		dd->rcvctrl &= ~(mask << IBA7220_R_INTRAVAIL_SHIFT);
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
		अगर (ctxt >= 0) अणु
			qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdrtailaddr, ctxt, 0);
			qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdraddr, ctxt, 0);
		पूर्ण अन्यथा अणु
			अचिन्हित i;

			क्रम (i = 0; i < dd->cfgctxts; i++) अणु
				qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdrtailaddr,
						    i, 0);
				qib_ग_लिखो_kreg_ctxt(dd, kr_rcvhdraddr, i, 0);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);
पूर्ण

/*
 * Modअगरy the SENDCTRL रेजिस्टर in chip-specअगरic way. This
 * is a function there may be multiple such रेजिस्टरs with
 * slightly dअगरferent layouts. To start, we assume the
 * "canonical" रेजिस्टर layout of the first chips.
 * Chip requires no back-back sendctrl ग_लिखोs, so ग_लिखो
 * scratch रेजिस्टर after writing sendctrl
 */
अटल व्योम sendctrl_7220_mod(काष्ठा qib_pportdata *ppd, u32 op)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u64 पंचांगp_dd_sendctrl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);

	/* First the ones that are "sticky", saved in shaकरोw */
	अगर (op & QIB_SENDCTRL_CLEAR)
		dd->sendctrl = 0;
	अगर (op & QIB_SENDCTRL_SEND_DIS)
		dd->sendctrl &= ~SYM_MASK(SendCtrl, SPioEnable);
	अन्यथा अगर (op & QIB_SENDCTRL_SEND_ENB) अणु
		dd->sendctrl |= SYM_MASK(SendCtrl, SPioEnable);
		अगर (dd->flags & QIB_USE_SPCL_TRIG)
			dd->sendctrl |= SYM_MASK(SendCtrl,
						 SSpecialTriggerEn);
	पूर्ण
	अगर (op & QIB_SENDCTRL_AVAIL_DIS)
		dd->sendctrl &= ~SYM_MASK(SendCtrl, SendBufAvailUpd);
	अन्यथा अगर (op & QIB_SENDCTRL_AVAIL_ENB)
		dd->sendctrl |= SYM_MASK(SendCtrl, SendBufAvailUpd);

	अगर (op & QIB_SENDCTRL_DISARM_ALL) अणु
		u32 i, last;

		पंचांगp_dd_sendctrl = dd->sendctrl;
		/*
		 * disarm any that are not yet launched, disabling sends
		 * and updates until करोne.
		 */
		last = dd->piobcnt2k + dd->piobcnt4k;
		पंचांगp_dd_sendctrl &=
			~(SYM_MASK(SendCtrl, SPioEnable) |
			  SYM_MASK(SendCtrl, SendBufAvailUpd));
		क्रम (i = 0; i < last; i++) अणु
			qib_ग_लिखो_kreg(dd, kr_sendctrl,
				       पंचांगp_dd_sendctrl |
				       SYM_MASK(SendCtrl, Disarm) | i);
			qib_ग_लिखो_kreg(dd, kr_scratch, 0);
		पूर्ण
	पूर्ण

	पंचांगp_dd_sendctrl = dd->sendctrl;

	अगर (op & QIB_SENDCTRL_FLUSH)
		पंचांगp_dd_sendctrl |= SYM_MASK(SendCtrl, Abort);
	अगर (op & QIB_SENDCTRL_DISARM)
		पंचांगp_dd_sendctrl |= SYM_MASK(SendCtrl, Disarm) |
			((op & QIB_7220_SendCtrl_DisarmPIOBuf_RMASK) <<
			 SYM_LSB(SendCtrl, DisarmPIOBuf));
	अगर ((op & QIB_SENDCTRL_AVAIL_BLIP) &&
	    (dd->sendctrl & SYM_MASK(SendCtrl, SendBufAvailUpd)))
		पंचांगp_dd_sendctrl &= ~SYM_MASK(SendCtrl, SendBufAvailUpd);

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
 * qib_portcntr_7220 - पढ़ो a per-port counter
 * @ppd: the qlogic_ib device
 * @reg: the counter to snapshot
 */
अटल u64 qib_portcntr_7220(काष्ठा qib_pportdata *ppd, u32 reg)
अणु
	u64 ret = 0ULL;
	काष्ठा qib_devdata *dd = ppd->dd;
	u16 creg;
	/* 0xffff क्रम unimplemented or synthesized counters */
	अटल स्थिर u16 xlator[] = अणु
		[QIBPORTCNTR_PKTSEND] = cr_pktsend,
		[QIBPORTCNTR_WORDSEND] = cr_wordsend,
		[QIBPORTCNTR_PSXMITDATA] = cr_psxmitdatacount,
		[QIBPORTCNTR_PSXMITPKTS] = cr_psxmitpktscount,
		[QIBPORTCNTR_PSXMITWAIT] = cr_psxmitरुकोcount,
		[QIBPORTCNTR_SENDSTALL] = cr_sendstall,
		[QIBPORTCNTR_PKTRCV] = cr_pktrcv,
		[QIBPORTCNTR_PSRCVDATA] = cr_psrcvdatacount,
		[QIBPORTCNTR_PSRCVPKTS] = cr_psrcvpktscount,
		[QIBPORTCNTR_RCVEBP] = cr_rcvebp,
		[QIBPORTCNTR_RCVOVFL] = cr_rcvovfl,
		[QIBPORTCNTR_WORDRCV] = cr_wordrcv,
		[QIBPORTCNTR_RXDROPPKT] = cr_rxdroppkt,
		[QIBPORTCNTR_RXLOCALPHYERR] = cr_rxotherlocalphyerr,
		[QIBPORTCNTR_RXVLERR] = cr_rxvlerr,
		[QIBPORTCNTR_ERRICRC] = cr_erricrc,
		[QIBPORTCNTR_ERRVCRC] = cr_errvcrc,
		[QIBPORTCNTR_ERRLPCRC] = cr_errlpcrc,
		[QIBPORTCNTR_BADFORMAT] = cr_badक्रमmat,
		[QIBPORTCNTR_ERR_RLEN] = cr_err_rlen,
		[QIBPORTCNTR_IBSYMBOLERR] = cr_ibsymbolerr,
		[QIBPORTCNTR_INVALIDRLEN] = cr_invalidrlen,
		[QIBPORTCNTR_UNSUPVL] = cr_txunsupvl,
		[QIBPORTCNTR_EXCESSBUFOVFL] = cr_excessbufferovfl,
		[QIBPORTCNTR_ERRLINK] = cr_errlink,
		[QIBPORTCNTR_IBLINKDOWN] = cr_iblinkकरोwn,
		[QIBPORTCNTR_IBLINKERRRECOV] = cr_iblinkerrrecov,
		[QIBPORTCNTR_LLI] = cr_locallinkपूर्णांकegrityerr,
		[QIBPORTCNTR_PSINTERVAL] = cr_psपूर्णांकerval,
		[QIBPORTCNTR_PSSTART] = cr_psstart,
		[QIBPORTCNTR_PSSTAT] = cr_psstat,
		[QIBPORTCNTR_VL15PKTDROP] = cr_vl15droppedpkt,
		[QIBPORTCNTR_ERRPKEY] = cr_errpkey,
		[QIBPORTCNTR_KHDROVFL] = 0xffff,
	पूर्ण;

	अगर (reg >= ARRAY_SIZE(xlator)) अणु
		qib_devinfo(ppd->dd->pcidev,
			 "Unimplemented portcounter %u\n", reg);
		जाओ करोne;
	पूर्ण
	creg = xlator[reg];

	अगर (reg == QIBPORTCNTR_KHDROVFL) अणु
		पूर्णांक i;

		/* sum over all kernel contexts */
		क्रम (i = 0; i < dd->first_user_ctxt; i++)
			ret += पढ़ो_7220_creg32(dd, cr_portovfl + i);
	पूर्ण
	अगर (creg == 0xffff)
		जाओ करोne;

	/*
	 * only fast incrementing counters are 64bit; use 32 bit पढ़ोs to
	 * aव्योम two independent पढ़ोs when on opteron
	 */
	अगर ((creg == cr_wordsend || creg == cr_wordrcv ||
	     creg == cr_pktsend || creg == cr_pktrcv))
		ret = पढ़ो_7220_creg(dd, creg);
	अन्यथा
		ret = पढ़ो_7220_creg32(dd, creg);
	अगर (creg == cr_ibsymbolerr) अणु
		अगर (dd->pport->cpspec->ibdeltainprog)
			ret -= ret - ppd->cpspec->ibsymsnap;
		ret -= dd->pport->cpspec->ibsymdelta;
	पूर्ण अन्यथा अगर (creg == cr_iblinkerrrecov) अणु
		अगर (dd->pport->cpspec->ibdeltainprog)
			ret -= ret - ppd->cpspec->iblnkerrsnap;
		ret -= dd->pport->cpspec->iblnkerrdelta;
	पूर्ण
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
 * cntr7220indices contains the corresponding रेजिस्टर indices.
 */
अटल स्थिर अक्षर cntr7220names[] =
	"Interrupts\n"
	"HostBusStall\n"
	"E RxTIDFull\n"
	"RxTIDInvalid\n"
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
	"Ctx16EgrOvfl\n";

अटल स्थिर माप_प्रकार cntr7220indices[] = अणु
	cr_lbपूर्णांक,
	cr_lbflowstall,
	cr_errtidfull,
	cr_errtidvalid,
	cr_portovfl + 0,
	cr_portovfl + 1,
	cr_portovfl + 2,
	cr_portovfl + 3,
	cr_portovfl + 4,
	cr_portovfl + 5,
	cr_portovfl + 6,
	cr_portovfl + 7,
	cr_portovfl + 8,
	cr_portovfl + 9,
	cr_portovfl + 10,
	cr_portovfl + 11,
	cr_portovfl + 12,
	cr_portovfl + 13,
	cr_portovfl + 14,
	cr_portovfl + 15,
	cr_portovfl + 16,
पूर्ण;

/*
 * same as cntr7220names and cntr7220indices, but क्रम port-specअगरic counters.
 * portcntr7220indices is somewhat complicated by some रेजिस्टरs needing
 * adjusपंचांगents of various kinds, and those are ORed with _PORT_VIRT_FLAG
 */
अटल स्थिर अक्षर portcntr7220names[] =
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
	"RxLclPhyErr\n" /* 7220 and 7322-only */
	"RxVL15Drop\n" /* 7220 and 7322-only */
	"RxVlErr\n" /* 7220 and 7322-only */
	"XcessBufOvfl\n" /* 7220 and 7322-only */
	;

#घोषणा _PORT_VIRT_FLAG 0x8000 /* "virtual", need adjusपंचांगents */
अटल स्थिर माप_प्रकार portcntr7220indices[] = अणु
	QIBPORTCNTR_PKTSEND | _PORT_VIRT_FLAG,
	cr_pktsendflow,
	QIBPORTCNTR_WORDSEND | _PORT_VIRT_FLAG,
	QIBPORTCNTR_PKTRCV | _PORT_VIRT_FLAG,
	cr_pktrcvflowctrl,
	QIBPORTCNTR_WORDRCV | _PORT_VIRT_FLAG,
	QIBPORTCNTR_SENDSTALL | _PORT_VIRT_FLAG,
	cr_txsdmadesc,
	cr_rxdlidfltr,
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
	QIBPORTCNTR_RXLOCALPHYERR | _PORT_VIRT_FLAG,
	QIBPORTCNTR_VL15PKTDROP | _PORT_VIRT_FLAG,
	QIBPORTCNTR_RXVLERR | _PORT_VIRT_FLAG,
	QIBPORTCNTR_EXCESSBUFOVFL | _PORT_VIRT_FLAG,
पूर्ण;

/* करो all the setup to make the counter पढ़ोs efficient later */
अटल व्योम init_7220_cntrnames(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक i, j = 0;
	अक्षर *s;

	क्रम (i = 0, s = (अक्षर *)cntr7220names; s && j <= dd->cfgctxts;
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
		dd->cspec->cntrnamelen = माप(cntr7220names) - 1;
	अन्यथा
		dd->cspec->cntrnamelen = 1 + s - cntr7220names;
	dd->cspec->cntrs = kदो_स्मृति_array(dd->cspec->ncntrs, माप(u64),
					 GFP_KERNEL);

	क्रम (i = 0, s = (अक्षर *)portcntr7220names; s; i++)
		s = म_अक्षर(s + 1, '\n');
	dd->cspec->nportcntrs = i - 1;
	dd->cspec->portcntrnamelen = माप(portcntr7220names) - 1;
	dd->cspec->portcntrs = kदो_स्मृति_array(dd->cspec->nportcntrs,
					     माप(u64),
					     GFP_KERNEL);
पूर्ण

अटल u32 qib_पढ़ो_7220cntrs(काष्ठा qib_devdata *dd, loff_t pos, अक्षर **namep,
			      u64 **cntrp)
अणु
	u32 ret;

	अगर (!dd->cspec->cntrs) अणु
		ret = 0;
		जाओ करोne;
	पूर्ण

	अगर (namep) अणु
		*namep = (अक्षर *)cntr7220names;
		ret = dd->cspec->cntrnamelen;
		अगर (pos >= ret)
			ret = 0; /* final पढ़ो after getting everything */
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
			*cntr++ = पढ़ो_7220_creg32(dd, cntr7220indices[i]);
	पूर्ण
करोne:
	वापस ret;
पूर्ण

अटल u32 qib_पढ़ो_7220portcntrs(काष्ठा qib_devdata *dd, loff_t pos, u32 port,
				  अक्षर **namep, u64 **cntrp)
अणु
	u32 ret;

	अगर (!dd->cspec->portcntrs) अणु
		ret = 0;
		जाओ करोne;
	पूर्ण
	अगर (namep) अणु
		*namep = (अक्षर *)portcntr7220names;
		ret = dd->cspec->portcntrnamelen;
		अगर (pos >= ret)
			ret = 0; /* final पढ़ो after getting everything */
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
			अगर (portcntr7220indices[i] & _PORT_VIRT_FLAG)
				*cntr++ = qib_portcntr_7220(ppd,
					portcntr7220indices[i] &
					~_PORT_VIRT_FLAG);
			अन्यथा
				*cntr++ = पढ़ो_7220_creg32(dd,
					   portcntr7220indices[i]);
		पूर्ण
	पूर्ण
करोne:
	वापस ret;
पूर्ण

/**
 * qib_get_7220_faststats - get word counters from chip beक्रमe they overflow
 * @t: contains a poपूर्णांकer to the qlogic_ib device qib_devdata
 *
 * This needs more work; in particular, decision on whether we really
 * need traffic_wds करोne the way it is
 * called from add_समयr
 */
अटल व्योम qib_get_7220_faststats(काष्ठा समयr_list *t)
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
	traffic_wds = qib_portcntr_7220(ppd, cr_wordsend) +
		qib_portcntr_7220(ppd, cr_wordrcv);
	spin_lock_irqsave(&dd->eep_st_lock, flags);
	traffic_wds -= dd->traffic_wds;
	dd->traffic_wds += traffic_wds;
	spin_unlock_irqrestore(&dd->eep_st_lock, flags);
करोne:
	mod_समयr(&dd->stats_समयr, jअगरfies + HZ * ACTIVITY_TIMER);
पूर्ण

/*
 * If we are using MSI, try to fallback to INTx.
 */
अटल पूर्णांक qib_7220_पूर्णांकr_fallback(काष्ठा qib_devdata *dd)
अणु
	अगर (!dd->msi_lo)
		वापस 0;

	qib_devinfo(dd->pcidev,
		    "MSI interrupt not detected, trying INTx interrupts\n");

	qib_मुक्त_irq(dd);
	dd->msi_lo = 0;
	अगर (pci_alloc_irq_vectors(dd->pcidev, 1, 1, PCI_IRQ_LEGACY) < 0)
		qib_dev_err(dd, "Failed to enable INTx\n");
	qib_setup_7220_पूर्णांकerrupt(dd);
	वापस 1;
पूर्ण

/*
 * Reset the XGXS (between serdes and IBC).  Slightly less पूर्णांकrusive
 * than resetting the IBC or बाह्यal link state, and useful in some
 * हालs to cause some retraining.  To करो this right, we reset IBC
 * as well.
 */
अटल व्योम qib_7220_xgxs_reset(काष्ठा qib_pportdata *ppd)
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
अटल u32 __iomem *get_7220_link_buf(काष्ठा qib_pportdata *ppd, u32 *bnum)
अणु
	u32 __iomem *buf;
	u32 lbuf = ppd->dd->cspec->lastbuf_क्रम_pio;
	पूर्णांक करो_cleanup;
	अचिन्हित दीर्घ flags;

	/*
	 * always blip to get avail list updated, since it's almost
	 * always needed, and is fairly cheap.
	 */
	sendctrl_7220_mod(ppd->dd->pport, QIB_SENDCTRL_AVAIL_BLIP);
	qib_पढ़ो_kreg64(ppd->dd, kr_scratch); /* extra chip flush */
	buf = qib_माला_लोendbuf_range(ppd->dd, bnum, lbuf, lbuf);
	अगर (buf)
		जाओ करोne;

	spin_lock_irqsave(&ppd->sdma_lock, flags);
	अगर (ppd->sdma_state.current_state == qib_sdma_state_s20_idle &&
	    ppd->sdma_state.current_state != qib_sdma_state_s00_hw_करोwn) अणु
		__qib_sdma_process_event(ppd, qib_sdma_event_e00_go_hw_करोwn);
		करो_cleanup = 0;
	पूर्ण अन्यथा अणु
		करो_cleanup = 1;
		qib_7220_sdma_hw_clean_up(ppd);
	पूर्ण
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);

	अगर (करो_cleanup) अणु
		qib_पढ़ो_kreg64(ppd->dd, kr_scratch); /* extra chip flush */
		buf = qib_माला_लोendbuf_range(ppd->dd, bnum, lbuf, lbuf);
	पूर्ण
करोne:
	वापस buf;
पूर्ण

/*
 * This code क्रम non-IBTA-compliant IB speed negotiation is only known to
 * work क्रम the SDR to DDR transition, and only between an HCA and a चयन
 * with recent firmware.  It is based on observed heuristics, rather than
 * actual knowledge of the non-compliant speed negotiation.
 * It has a number of hard-coded fields, since the hope is to reग_लिखो this
 * when a spec is available on how the negoation is पूर्णांकended to work.
 */
अटल व्योम स्वतःneg_7220_sendpkt(काष्ठा qib_pportdata *ppd, u32 *hdr,
				 u32 dcnt, u32 *data)
अणु
	पूर्णांक i;
	u64 pbc;
	u32 __iomem *piobuf;
	u32 pnum;
	काष्ठा qib_devdata *dd = ppd->dd;

	i = 0;
	pbc = 7 + dcnt + 1; /* 7 dword header, dword data, icrc */
	pbc |= PBC_7220_VL15_SEND;
	जबतक (!(piobuf = get_7220_link_buf(ppd, &pnum))) अणु
		अगर (i++ > 5)
			वापस;
		udelay(2);
	पूर्ण
	sendctrl_7220_mod(dd->pport, QIB_SENDCTRL_DISARM_BUF(pnum));
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
पूर्ण

/*
 * _start packet माला_लो sent twice at start, _करोne माला_लो sent twice at end
 */
अटल व्योम स्वतःneg_7220_send(काष्ठा qib_pportdata *ppd, पूर्णांक which)
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

	स्वतःneg_7220_sendpkt(ppd, hdr, dcnt, data);
	qib_पढ़ो_kreg64(dd, kr_scratch);
	udelay(2);
	स्वतःneg_7220_sendpkt(ppd, hdr, dcnt, data);
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
अटल व्योम set_7220_ibspeed_fast(काष्ठा qib_pportdata *ppd, u32 speed)
अणु
	ppd->cpspec->ibcddrctrl &= ~(IBA7220_IBC_SPEED_AUTONEG_MASK |
		IBA7220_IBC_IBTA_1_2_MASK);

	अगर (speed == (QIB_IB_SDR | QIB_IB_DDR))
		ppd->cpspec->ibcddrctrl |= IBA7220_IBC_SPEED_AUTONEG_MASK |
			IBA7220_IBC_IBTA_1_2_MASK;
	अन्यथा
		ppd->cpspec->ibcddrctrl |= speed == QIB_IB_DDR ?
			IBA7220_IBC_SPEED_DDR : IBA7220_IBC_SPEED_SDR;

	qib_ग_लिखो_kreg(ppd->dd, kr_ibcddrctrl, ppd->cpspec->ibcddrctrl);
	qib_ग_लिखो_kreg(ppd->dd, kr_scratch, 0);
पूर्ण

/*
 * This routine is only used when we are not talking to another
 * IB 1.2-compliant device that we think can करो DDR.
 * (This includes all existing चयन chips as of Oct 2007.)
 * 1.2-compliant devices go directly to DDR prior to reaching INIT
 */
अटल व्योम try_7220_स्वतःneg(काष्ठा qib_pportdata *ppd)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Required क्रम older non-IB1.2 DDR चयनes.  Newer
	 * non-IB-compliant चयनes करोn't need it, but so far,
	 * aren't bothered by it either.  "Magic constant"
	 */
	qib_ग_लिखो_kreg(ppd->dd, kr_ncmodectrl, 0x3b9dc07);

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags |= QIBL_IB_AUTONEG_INPROG;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	स्वतःneg_7220_send(ppd, 0);
	set_7220_ibspeed_fast(ppd, QIB_IB_DDR);

	toggle_7220_rclkrls(ppd->dd);
	/* 2 msec is minimum length of a poll cycle */
	queue_delayed_work(ib_wq, &ppd->cpspec->स्वतःneg_work,
			   msecs_to_jअगरfies(2));
पूर्ण

/*
 * Handle the empirically determined mechanism क्रम स्वतः-negotiation
 * of DDR speed with चयनes.
 */
अटल व्योम स्वतःneg_7220_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qib_pportdata *ppd;
	काष्ठा qib_devdata *dd;
	u32 i;
	अचिन्हित दीर्घ flags;

	ppd = &container_of(work, काष्ठा qib_chippport_specअगरic,
			    स्वतःneg_work.work)->pportdata;
	dd = ppd->dd;

	/*
	 * Busy रुको क्रम this first part, it should be at most a
	 * few hundred usec, since we scheduled ourselves क्रम 2msec.
	 */
	क्रम (i = 0; i < 25; i++) अणु
		अगर (SYM_FIELD(ppd->lastibcstat, IBCStatus, LinkTrainingState)
		     == IB_7220_LT_STATE_POLLQUIET) अणु
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

	toggle_7220_rclkrls(dd);

	/* we expect this to समयout */
	अगर (रुको_event_समयout(ppd->cpspec->स्वतःneg_रुको,
			       !(ppd->lflags & QIBL_IB_AUTONEG_INPROG),
			       msecs_to_jअगरfies(1700)))
		जाओ करोne;

	set_7220_ibspeed_fast(ppd, QIB_IB_SDR);
	toggle_7220_rclkrls(dd);

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
		अगर (dd->cspec->स्वतःneg_tries == AUTONEG_TRIES) अणु
			ppd->lflags |= QIBL_IB_AUTONEG_FAILED;
			dd->cspec->स्वतःneg_tries = 0;
		पूर्ण
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		set_7220_ibspeed_fast(ppd, ppd->link_speed_enabled);
	पूर्ण
पूर्ण

अटल u32 qib_7220_iblink_state(u64 ibcs)
अणु
	u32 state = (u32)SYM_FIELD(ibcs, IBCStatus, LinkState);

	चयन (state) अणु
	हाल IB_7220_L_STATE_INIT:
		state = IB_PORT_INIT;
		अवरोध;
	हाल IB_7220_L_STATE_ARM:
		state = IB_PORT_ARMED;
		अवरोध;
	हाल IB_7220_L_STATE_ACTIVE:
	हाल IB_7220_L_STATE_ACT_DEFER:
		state = IB_PORT_ACTIVE;
		अवरोध;
	शेष:
		fallthrough;
	हाल IB_7220_L_STATE_DOWN:
		state = IB_PORT_DOWN;
		अवरोध;
	पूर्ण
	वापस state;
पूर्ण

/* वापसs the IBTA port state, rather than the IBC link training state */
अटल u8 qib_7220_phys_portstate(u64 ibcs)
अणु
	u8 state = (u8)SYM_FIELD(ibcs, IBCStatus, LinkTrainingState);
	वापस qib_7220_physportstate[state];
पूर्ण

अटल पूर्णांक qib_7220_ib_upकरोwn(काष्ठा qib_pportdata *ppd, पूर्णांक ibup, u64 ibcs)
अणु
	पूर्णांक ret = 0, symadj = 0;
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags &= ~QIBL_IB_FORCE_NOTIFY;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);

	अगर (!ibup) अणु
		/*
		 * When the link goes करोwn we करोn't want AEQ running, so it
		 * won't पूर्णांकerfere with IBC training, etc., and we need
		 * to go back to the अटल SerDes preset values.
		 */
		अगर (!(ppd->lflags & (QIBL_IB_AUTONEG_FAILED |
				     QIBL_IB_AUTONEG_INPROG)))
			set_7220_ibspeed_fast(ppd, ppd->link_speed_enabled);
		अगर (!(ppd->lflags & QIBL_IB_AUTONEG_INPROG)) अणु
			qib_sd7220_presets(dd);
			qib_cancel_sends(ppd); /* initial disarm, etc. */
			spin_lock_irqsave(&ppd->sdma_lock, flags);
			अगर (__qib_sdma_running(ppd))
				__qib_sdma_process_event(ppd,
					qib_sdma_event_e70_go_idle);
			spin_unlock_irqrestore(&ppd->sdma_lock, flags);
		पूर्ण
		/* this might better in qib_sd7220_presets() */
		set_7220_relock_poll(dd, ibup);
	पूर्ण अन्यथा अणु
		अगर (qib_compat_ddr_negotiate &&
		    !(ppd->lflags & (QIBL_IB_AUTONEG_FAILED |
				     QIBL_IB_AUTONEG_INPROG)) &&
		    ppd->link_speed_active == QIB_IB_SDR &&
		    (ppd->link_speed_enabled & (QIB_IB_DDR | QIB_IB_SDR)) ==
		    (QIB_IB_DDR | QIB_IB_SDR) &&
		    dd->cspec->स्वतःneg_tries < AUTONEG_TRIES) अणु
			/* we are SDR, and DDR स्वतः-negotiation enabled */
			++dd->cspec->स्वतःneg_tries;
			अगर (!ppd->cpspec->ibdeltainprog) अणु
				ppd->cpspec->ibdeltainprog = 1;
				ppd->cpspec->ibsymsnap = पढ़ो_7220_creg32(dd,
					cr_ibsymbolerr);
				ppd->cpspec->iblnkerrsnap = पढ़ो_7220_creg32(dd,
					cr_iblinkerrrecov);
			पूर्ण
			try_7220_स्वतःneg(ppd);
			ret = 1; /* no other IB status change processing */
		पूर्ण अन्यथा अगर ((ppd->lflags & QIBL_IB_AUTONEG_INPROG) &&
			   ppd->link_speed_active == QIB_IB_SDR) अणु
			स्वतःneg_7220_send(ppd, 1);
			set_7220_ibspeed_fast(ppd, QIB_IB_DDR);
			udelay(2);
			toggle_7220_rclkrls(dd);
			ret = 1; /* no other IB status change processing */
		पूर्ण अन्यथा अणु
			अगर ((ppd->lflags & QIBL_IB_AUTONEG_INPROG) &&
			    (ppd->link_speed_active & QIB_IB_DDR)) अणु
				spin_lock_irqsave(&ppd->lflags_lock, flags);
				ppd->lflags &= ~(QIBL_IB_AUTONEG_INPROG |
						 QIBL_IB_AUTONEG_FAILED);
				spin_unlock_irqrestore(&ppd->lflags_lock,
						       flags);
				dd->cspec->स्वतःneg_tries = 0;
				/* re-enable SDR, क्रम next link करोwn */
				set_7220_ibspeed_fast(ppd,
						      ppd->link_speed_enabled);
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
				spin_unlock_irqrestore(&ppd->lflags_lock,
						       flags);
				ppd->cpspec->ibcddrctrl |=
					IBA7220_IBC_IBTA_1_2_MASK;
				qib_ग_लिखो_kreg(dd, kr_ncmodectrl, 0);
				symadj = 1;
			पूर्ण
		पूर्ण

		अगर (!(ppd->lflags & QIBL_IB_AUTONEG_INPROG))
			symadj = 1;

		अगर (!ret) अणु
			ppd->delay_mult = rate_to_delay
			    [(ibcs >> IBA7220_LINKSPEED_SHIFT) & 1]
			    [(ibcs >> IBA7220_LINKWIDTH_SHIFT) & 1];

			set_7220_relock_poll(dd, ibup);
			spin_lock_irqsave(&ppd->sdma_lock, flags);
			/*
			 * Unlike 7322, the 7220 needs this, due to lack of
			 * पूर्णांकerrupt in some हालs when we have sdma active
			 * when the link goes करोwn.
			 */
			अगर (ppd->sdma_state.current_state !=
			    qib_sdma_state_s20_idle)
				__qib_sdma_process_event(ppd,
					qib_sdma_event_e00_go_hw_करोwn);
			spin_unlock_irqrestore(&ppd->sdma_lock, flags);
		पूर्ण
	पूर्ण

	अगर (symadj) अणु
		अगर (ppd->cpspec->ibdeltainprog) अणु
			ppd->cpspec->ibdeltainprog = 0;
			ppd->cpspec->ibsymdelta += पढ़ो_7220_creg32(ppd->dd,
				cr_ibsymbolerr) - ppd->cpspec->ibsymsnap;
			ppd->cpspec->iblnkerrdelta += पढ़ो_7220_creg32(ppd->dd,
				cr_iblinkerrrecov) - ppd->cpspec->iblnkerrsnap;
		पूर्ण
	पूर्ण अन्यथा अगर (!ibup && qib_compat_ddr_negotiate &&
		   !ppd->cpspec->ibdeltainprog &&
			!(ppd->lflags & QIBL_IB_AUTONEG_INPROG)) अणु
		ppd->cpspec->ibdeltainprog = 1;
		ppd->cpspec->ibsymsnap = पढ़ो_7220_creg32(ppd->dd,
							  cr_ibsymbolerr);
		ppd->cpspec->iblnkerrsnap = पढ़ो_7220_creg32(ppd->dd,
						     cr_iblinkerrrecov);
	पूर्ण

	अगर (!ret)
		qib_setup_7220_setextled(ppd, ibup);
	वापस ret;
पूर्ण

/*
 * Does पढ़ो/modअगरy/ग_लिखो to appropriate रेजिस्टरs to
 * set output and direction bits selected by mask.
 * these are in their canonical postions (e.g. lsb of
 * dir will end up in D48 of extctrl on existing chips).
 * वापसs contents of GP Inमाला_दो.
 */
अटल पूर्णांक gpio_7220_mod(काष्ठा qib_devdata *dd, u32 out, u32 dir, u32 mask)
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
अटल व्योम get_7220_chip_params(काष्ठा qib_devdata *dd)
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
	/* these may be adjusted in init_chip_wc_pat() */
	dd->pio2kbase = (u32 __iomem *)
		((अक्षर __iomem *) dd->kregbase + dd->pio2k_bufbase);
	अगर (dd->piobcnt4k) अणु
		dd->pio4kbase = (u32 __iomem *)
			((अक्षर __iomem *) dd->kregbase +
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
 * qib_get_7220_chip_params(), so split out as separate function
 */
अटल व्योम set_7220_baseaddrs(काष्ठा qib_devdata *dd)
अणु
	u32 cregbase;
	/* init after possible re-map in init_chip_wc_pat() */
	cregbase = qib_पढ़ो_kreg32(dd, kr_counterregbase);
	dd->cspec->cregbase = (u64 __iomem *)
		((अक्षर __iomem *) dd->kregbase + cregbase);

	dd->egrtidbase = (u64 __iomem *)
		((अक्षर __iomem *) dd->kregbase + dd->rcvegrbase);
पूर्ण


#घोषणा SENDCTRL_SHADOWED (SYM_MASK(SendCtrl, SendIntBufAvail) |	\
			   SYM_MASK(SendCtrl, SPioEnable) |		\
			   SYM_MASK(SendCtrl, SSpecialTriggerEn) |	\
			   SYM_MASK(SendCtrl, SendBufAvailUpd) |	\
			   SYM_MASK(SendCtrl, AvailUpdThld) |		\
			   SYM_MASK(SendCtrl, SDmaEnable) |		\
			   SYM_MASK(SendCtrl, SDmaIntEnable) |		\
			   SYM_MASK(SendCtrl, SDmaHalt) |		\
			   SYM_MASK(SendCtrl, SDmaSingleDescriptor))

अटल पूर्णांक sendctrl_hook(काष्ठा qib_devdata *dd,
			 स्थिर काष्ठा diag_observer *op,
			 u32 offs, u64 *data, u64 mask, पूर्णांक only_32)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित idx = offs / माप(u64);
	u64 local_data, all_bits;

	अगर (idx != kr_sendctrl) अणु
		qib_dev_err(dd, "SendCtrl Hook called with offs %X, %s-bit\n",
			    offs, only_32 ? "32" : "64");
		वापस 0;
	पूर्ण

	all_bits = ~0ULL;
	अगर (only_32)
		all_bits >>= 32;
	spin_lock_irqsave(&dd->sendctrl_lock, flags);
	अगर ((mask & all_bits) != all_bits) अणु
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
		qib_dev_err(dd, "Sendctrl -> %X, Shad -> %X\n",
			    (u32)local_data, (u32)dd->sendctrl);
		अगर ((local_data & SENDCTRL_SHADOWED) !=
		    (dd->sendctrl & SENDCTRL_SHADOWED))
			qib_dev_err(dd, "Sendctrl read: %X shadow is %X\n",
				(u32)local_data, (u32) dd->sendctrl);
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
		sval = (dd->sendctrl & ~mask);
		sval |= *data & SENDCTRL_SHADOWED & mask;
		dd->sendctrl = sval;
		tval = sval | (*data & ~SENDCTRL_SHADOWED & mask);
		qib_dev_err(dd, "Sendctrl <- %X, Shad <- %X\n",
			    (u32)tval, (u32)sval);
		qib_ग_लिखो_kreg(dd, kr_sendctrl, tval);
		qib_ग_लिखो_kreg(dd, kr_scratch, 0Ull);
	पूर्ण
	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);

	वापस only_32 ? 4 : 8;
पूर्ण

अटल स्थिर काष्ठा diag_observer sendctrl_observer = अणु
	sendctrl_hook, kr_sendctrl * माप(u64),
	kr_sendctrl * माप(u64)
पूर्ण;

/*
 * ग_लिखो the final few रेजिस्टरs that depend on some of the
 * init setup.  Done late in init, just beक्रमe bringing up
 * the serdes.
 */
अटल पूर्णांक qib_late_7220_initreg(काष्ठा qib_devdata *dd)
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
	qib_रेजिस्टर_observer(dd, &sendctrl_observer);
	वापस ret;
पूर्ण

अटल पूर्णांक qib_init_7220_variables(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_chippport_specअगरic *cpspec;
	काष्ठा qib_pportdata *ppd;
	पूर्णांक ret = 0;
	u32 sbufs, updthresh;

	cpspec = (काष्ठा qib_chippport_specअगरic *)(dd + 1);
	ppd = &cpspec->pportdata;
	dd->pport = ppd;
	dd->num_pports = 1;

	dd->cspec = (काष्ठा qib_chip_specअगरic *)(cpspec + dd->num_pports);
	dd->cspec->dd = dd;
	ppd->cpspec = cpspec;

	spin_lock_init(&dd->cspec->sdepb_lock);
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

	get_7220_chip_params(dd);
	qib_7220_boardname(dd);

	/*
	 * GPIO bits क्रम TWSI data and घड़ी,
	 * used क्रम serial EEPROM.
	 */
	dd->gpio_sda_num = _QIB_GPIO_SDA_NUM;
	dd->gpio_scl_num = _QIB_GPIO_SCL_NUM;
	dd->twsi_eeprom_dev = QIB_TWSI_EEPROM_DEV;

	dd->flags |= QIB_HAS_INTX | QIB_HAS_LINK_LATENCY |
		QIB_NODMA_RTAIL | QIB_HAS_THRESH_UPDATE;
	dd->flags |= qib_special_trigger ?
		QIB_USE_SPCL_TRIG : QIB_HAS_SEND_DMA;

	init_रुकोqueue_head(&cpspec->स्वतःneg_रुको);
	INIT_DELAYED_WORK(&cpspec->स्वतःneg_work, स्वतःneg_7220_work);

	ret = qib_init_pportdata(ppd, dd, 0, 1);
	अगर (ret)
		जाओ bail;
	ppd->link_width_supported = IB_WIDTH_1X | IB_WIDTH_4X;
	ppd->link_speed_supported = QIB_IB_SDR | QIB_IB_DDR;

	ppd->link_width_enabled = ppd->link_width_supported;
	ppd->link_speed_enabled = ppd->link_speed_supported;
	/*
	 * Set the initial values to reasonable शेष, will be set
	 * क्रम real when link is up.
	 */
	ppd->link_width_active = IB_WIDTH_4X;
	ppd->link_speed_active = QIB_IB_SDR;
	ppd->delay_mult = rate_to_delay[0][1];
	ppd->vls_supported = IB_VL_VL0;
	ppd->vls_operational = ppd->vls_supported;

	अगर (!qib_mini_init)
		qib_ग_लिखो_kreg(dd, kr_rcvbthqp, QIB_KD_QP);

	समयr_setup(&ppd->cpspec->chase_समयr, reenable_7220_chase, 0);

	qib_num_cfg_vls = 1; /* अगर any 7220's, only one VL */

	dd->rcvhdrentsize = QIB_RCVHDR_ENTSIZE;
	dd->rcvhdrsize = QIB_DFLT_RCVHDRSIZE;
	dd->rhf_offset =
		dd->rcvhdrentsize - माप(u64) / माप(u32);

	/* we always allocate at least 2048 bytes क्रम eager buffers */
	ret = ib_mtu_क्रमागत_to_पूर्णांक(qib_ibmtu);
	dd->rcvegrbufsize = ret != -1 ? max(ret, 2048) : QIB_DEFAULT_MTU;
	dd->rcvegrbufsize_shअगरt = ilog2(dd->rcvegrbufsize);

	qib_7220_tidढाँचा(dd);

	/*
	 * We can request a receive पूर्णांकerrupt क्रम 1 or
	 * more packets from current offset.  For now, we set this
	 * up क्रम a single packet.
	 */
	dd->rhdrhead_पूर्णांकr_off = 1ULL << 32;

	/* setup the stats समयr; the add_समयr is करोne at end of init */
	समयr_setup(&dd->stats_समयr, qib_get_7220_faststats, 0);
	dd->stats_समयr.expires = jअगरfies + ACTIVITY_TIMER * HZ;

	/*
	 * Control[4] has been added to change the arbitration within
	 * the SDMA engine between favoring data fetches over descriptor
	 * fetches.  qib_sdma_fetch_arb==0 gives data fetches priority.
	 */
	अगर (qib_sdma_fetch_arb)
		dd->control |= 1 << 4;

	dd->ureg_align = 0x10000;  /* 64KB alignment */

	dd->piosize2kmax_dwords = (dd->piosize2k >> 2)-1;
	qib_7220_config_ctxts(dd);
	qib_set_ctxtcnt(dd);  /* needed क्रम PAT setup */

	ret = init_chip_wc_pat(dd, 0);
	अगर (ret)
		जाओ bail;
	set_7220_baseaddrs(dd); /* set chip access poपूर्णांकers now */

	ret = 0;
	अगर (qib_mini_init)
		जाओ bail;

	ret = qib_create_ctxts(dd);
	init_7220_cntrnames(dd);

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
	updthresh = 8U; /* update threshold */
	अगर (dd->flags & QIB_HAS_SEND_DMA) अणु
		dd->cspec->sdmabufcnt =  dd->piobcnt4k;
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
	dd->pbufsctxt = dd->lastctxt_piobuf /
		(dd->cfgctxts - dd->first_user_ctxt);

	/*
	 * अगर we are at 16 user contexts, we will have one 7 sbufs
	 * per context, so drop the update threshold to match.  We
	 * want to update beक्रमe we actually run out, at low pbufs/ctxt
	 * so give ourselves some margin
	 */
	अगर ((dd->pbufsctxt - 2) < updthresh)
		updthresh = dd->pbufsctxt - 2;

	dd->cspec->updthresh_dflt = updthresh;
	dd->cspec->updthresh = updthresh;

	/* beक्रमe full enable, no पूर्णांकerrupts, no locking needed */
	dd->sendctrl |= (updthresh & SYM_RMASK(SendCtrl, AvailUpdThld))
			     << SYM_LSB(SendCtrl, AvailUpdThld);

	dd->psxmitरुको_supported = 1;
	dd->psxmitरुको_check_rate = QIB_7220_PSXMITWAIT_CHECK_RATE;
bail:
	वापस ret;
पूर्ण

अटल u32 __iomem *qib_7220_माला_लोendbuf(काष्ठा qib_pportdata *ppd, u64 pbc,
					u32 *pbufnum)
अणु
	u32 first, last, plen = pbc & QIB_PBC_LENGTH_MASK;
	काष्ठा qib_devdata *dd = ppd->dd;
	u32 __iomem *buf;

	अगर (((pbc >> 32) & PBC_7220_VL15_SEND_CTRL) &&
		!(ppd->lflags & (QIBL_IB_AUTONEG_INPROG | QIBL_LINKACTIVE)))
		buf = get_7220_link_buf(ppd, pbufnum);
	अन्यथा अणु
		अगर ((plen + 1) > dd->piosize2kmax_dwords)
			first = dd->piobcnt2k;
		अन्यथा
			first = 0;
		/* try 4k अगर all 2k busy, so same last क्रम both sizes */
		last = dd->cspec->lastbuf_क्रम_pio;
		buf = qib_माला_लोendbuf_range(dd, pbufnum, first, last);
	पूर्ण
	वापस buf;
पूर्ण

/* these 2 "counters" are really control रेजिस्टरs, and are always RW */
अटल व्योम qib_set_cntr_7220_sample(काष्ठा qib_pportdata *ppd, u32 पूर्णांकv,
				     u32 start)
अणु
	ग_लिखो_7220_creg(ppd->dd, cr_psपूर्णांकerval, पूर्णांकv);
	ग_लिखो_7220_creg(ppd->dd, cr_psstart, start);
पूर्ण

/*
 * NOTE: no real attempt is made to generalize the SDMA stuff.
 * At some poपूर्णांक "soon" we will have a new more generalized
 * set of sdma पूर्णांकerface, and then we'll clean this up.
 */

/* Must be called with sdma_lock held, or beक्रमe init finished */
अटल व्योम qib_sdma_update_7220_tail(काष्ठा qib_pportdata *ppd, u16 tail)
अणु
	/* Commit ग_लिखोs to memory and advance the tail on the chip */
	wmb();
	ppd->sdma_descq_tail = tail;
	qib_ग_लिखो_kreg(ppd->dd, kr_senddmatail, tail);
पूर्ण

अटल व्योम qib_sdma_set_7220_desc_cnt(काष्ठा qib_pportdata *ppd, अचिन्हित cnt)
अणु
पूर्ण

अटल काष्ठा sdma_set_state_action sdma_7220_action_table[] = अणु
	[qib_sdma_state_s00_hw_करोwn] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 0,
		.op_halt = 0,
		.go_s99_running_tofalse = 1,
	पूर्ण,
	[qib_sdma_state_s10_hw_start_up_रुको] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
	पूर्ण,
	[qib_sdma_state_s20_idle] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
	पूर्ण,
	[qib_sdma_state_s30_sw_clean_up_रुको] = अणु
		.op_enable = 0,
		.op_पूर्णांकenable = 1,
		.op_halt = 0,
	पूर्ण,
	[qib_sdma_state_s40_hw_clean_up_रुको] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
	पूर्ण,
	[qib_sdma_state_s50_hw_halt_रुको] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 1,
	पूर्ण,
	[qib_sdma_state_s99_running] = अणु
		.op_enable = 1,
		.op_पूर्णांकenable = 1,
		.op_halt = 0,
		.go_s99_running_totrue = 1,
	पूर्ण,
पूर्ण;

अटल व्योम qib_7220_sdma_init_early(काष्ठा qib_pportdata *ppd)
अणु
	ppd->sdma_state.set_state_action = sdma_7220_action_table;
पूर्ण

अटल पूर्णांक init_sdma_7220_regs(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित i, n;
	u64 senddmabufmask[3] = अणु 0 पूर्ण;

	/* Set SendDmaBase */
	qib_ग_लिखो_kreg(dd, kr_senddmabase, ppd->sdma_descq_phys);
	qib_sdma_7220_setlengen(ppd);
	qib_sdma_update_7220_tail(ppd, 0); /* Set SendDmaTail */
	/* Set SendDmaHeadAddr */
	qib_ग_लिखो_kreg(dd, kr_senddmaheadaddr, ppd->sdma_head_phys);

	/*
	 * Reserve all the क्रमmer "kernel" piobufs, using high number range
	 * so we get as many 4K buffers as possible
	 */
	n = dd->piobcnt2k + dd->piobcnt4k;
	i = n - dd->cspec->sdmabufcnt;

	क्रम (; i < n; ++i) अणु
		अचिन्हित word = i / 64;
		अचिन्हित bit = i & 63;

		senddmabufmask[word] |= 1ULL << bit;
	पूर्ण
	qib_ग_लिखो_kreg(dd, kr_senddmabufmask0, senddmabufmask[0]);
	qib_ग_लिखो_kreg(dd, kr_senddmabufmask1, senddmabufmask[1]);
	qib_ग_लिखो_kreg(dd, kr_senddmabufmask2, senddmabufmask[2]);

	ppd->sdma_state.first_sendbuf = i;
	ppd->sdma_state.last_sendbuf = n;

	वापस 0;
पूर्ण

/* sdma_lock must be held */
अटल u16 qib_sdma_7220_gethead(काष्ठा qib_pportdata *ppd)
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
		(u16)le64_to_cpu(*ppd->sdma_head_dma) :
		(u16)qib_पढ़ो_kreg32(dd, kr_senddmahead);

	swhead = ppd->sdma_descq_head;
	swtail = ppd->sdma_descq_tail;
	cnt = ppd->sdma_descq_cnt;

	अगर (swhead < swtail) अणु
		/* not wrapped */
		sane = (hwhead >= swhead) & (hwhead <= swtail);
	पूर्ण अन्यथा अगर (swhead > swtail) अणु
		/* wrapped around */
		sane = ((hwhead >= swhead) && (hwhead < cnt)) ||
			(hwhead <= swtail);
	पूर्ण अन्यथा अणु
		/* empty */
		sane = (hwhead == swhead);
	पूर्ण

	अगर (unlikely(!sane)) अणु
		अगर (use_dmahead) अणु
			/* try one more समय, directly from the रेजिस्टर */
			use_dmahead = 0;
			जाओ retry;
		पूर्ण
		/* assume no progress */
		hwhead = swhead;
	पूर्ण

	वापस hwhead;
पूर्ण

अटल पूर्णांक qib_sdma_7220_busy(काष्ठा qib_pportdata *ppd)
अणु
	u64 hwstatus = qib_पढ़ो_kreg64(ppd->dd, kr_senddmastatus);

	वापस (hwstatus & SYM_MASK(SendDmaStatus, ScoreBoardDrainInProg)) ||
	       (hwstatus & SYM_MASK(SendDmaStatus, AbortInProg)) ||
	       (hwstatus & SYM_MASK(SendDmaStatus, InternalSDmaEnable)) ||
	       !(hwstatus & SYM_MASK(SendDmaStatus, ScbEmpty));
पूर्ण

/*
 * Compute the amount of delay beक्रमe sending the next packet अगर the
 * port's send rate dअगरfers from the अटल rate set क्रम the QP.
 * Since the delay affects this packet but the amount of the delay is
 * based on the length of the previous packet, use the last delay computed
 * and save the delay count क्रम this packet to be used next समय
 * we get here.
 */
अटल u32 qib_7220_setpbc_control(काष्ठा qib_pportdata *ppd, u32 plen,
				   u8 srate, u8 vl)
अणु
	u8 snd_mult = ppd->delay_mult;
	u8 rcv_mult = ib_rate_to_delay[srate];
	u32 ret = ppd->cpspec->last_delay_mult;

	ppd->cpspec->last_delay_mult = (rcv_mult > snd_mult) ?
		(plen * (rcv_mult - snd_mult) + 1) >> 1 : 0;

	/* Indicate VL15, अगर necessary */
	अगर (vl == 15)
		ret |= PBC_7220_VL15_SEND_CTRL;
	वापस ret;
पूर्ण

अटल व्योम qib_7220_initvl15_bufs(काष्ठा qib_devdata *dd)
अणु
पूर्ण

अटल व्योम qib_7220_init_ctxt(काष्ठा qib_ctxtdata *rcd)
अणु
	अगर (!rcd->ctxt) अणु
		rcd->rcvegrcnt = IBA7220_KRCVEGRCNT;
		rcd->rcvegr_tid_base = 0;
	पूर्ण अन्यथा अणु
		rcd->rcvegrcnt = rcd->dd->cspec->rcvegrcnt;
		rcd->rcvegr_tid_base = IBA7220_KRCVEGRCNT +
			(rcd->ctxt - 1) * rcd->rcvegrcnt;
	पूर्ण
पूर्ण

अटल व्योम qib_7220_txchk_change(काष्ठा qib_devdata *dd, u32 start,
				  u32 len, u32 which, काष्ठा qib_ctxtdata *rcd)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	चयन (which) अणु
	हाल TXCHK_CHG_TYPE_KERN:
		/* see अगर we need to उठाओ avail update threshold */
		spin_lock_irqsave(&dd->uctxt_lock, flags);
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
			sendctrl_7220_mod(dd->pport, QIB_SENDCTRL_AVAIL_BLIP);
		पूर्ण
		अवरोध;
	हाल TXCHK_CHG_TYPE_USER:
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
			sendctrl_7220_mod(dd->pport, QIB_SENDCTRL_AVAIL_BLIP);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखोscratch(काष्ठा qib_devdata *dd, u32 val)
अणु
	qib_ग_लिखो_kreg(dd, kr_scratch, val);
पूर्ण

#घोषणा VALID_TS_RD_REG_MASK 0xBF
/**
 * qib_7220_tempsense_rd - पढ़ो रेजिस्टर of temp sensor via TWSI
 * @dd: the qlogic_ib device
 * @regnum: रेजिस्टर to पढ़ो from
 *
 * वापसs reg contents (0..255) or < 0 क्रम error
 */
अटल पूर्णांक qib_7220_tempsense_rd(काष्ठा qib_devdata *dd, पूर्णांक regnum)
अणु
	पूर्णांक ret;
	u8 rdata;

	अगर (regnum > 7) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	/* वापस a bogus value क्रम (the one) रेजिस्टर we करो not have */
	अगर (!((1 << regnum) & VALID_TS_RD_REG_MASK)) अणु
		ret = 0;
		जाओ bail;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&dd->eep_lock);
	अगर (ret)
		जाओ bail;

	ret = qib_twsi_blk_rd(dd, QIB_TWSI_TEMP_DEV, regnum, &rdata, 1);
	अगर (!ret)
		ret = rdata;

	mutex_unlock(&dd->eep_lock);

	/*
	 * There are three possibilities here:
	 * ret is actual value (0..255)
	 * ret is -ENXIO or -EINVAL from twsi code or this file
	 * ret is -EINTR from mutex_lock_पूर्णांकerruptible.
	 */
bail:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
अटल पूर्णांक qib_7220_notअगरy_dca(काष्ठा qib_devdata *dd, अचिन्हित दीर्घ event)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Dummy function, as 7220 boards never disable EEPROM Write */
अटल पूर्णांक qib_7220_eeprom_wen(काष्ठा qib_devdata *dd, पूर्णांक wen)
अणु
	वापस 1;
पूर्ण

/**
 * qib_init_iba7220_funcs - set up the chip-specअगरic function poपूर्णांकers
 * @pdev: the pci_dev क्रम qlogic_ib device
 * @ent: pci_device_id काष्ठा क्रम this dev
 *
 * This is global, and is called directly at init to set up the
 * chip-specअगरic function poपूर्णांकers क्रम later use.
 */
काष्ठा qib_devdata *qib_init_iba7220_funcs(काष्ठा pci_dev *pdev,
					   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा qib_devdata *dd;
	पूर्णांक ret;
	u32 boardid, minwidth;

	dd = qib_alloc_devdata(pdev, माप(काष्ठा qib_chip_specअगरic) +
		माप(काष्ठा qib_chippport_specअगरic));
	अगर (IS_ERR(dd))
		जाओ bail;

	dd->f_bringup_serdes    = qib_7220_bringup_serdes;
	dd->f_cleanup           = qib_setup_7220_cleanup;
	dd->f_clear_tids        = qib_7220_clear_tids;
	dd->f_मुक्त_irq          = qib_मुक्त_irq;
	dd->f_get_base_info     = qib_7220_get_base_info;
	dd->f_get_msgheader     = qib_7220_get_msgheader;
	dd->f_माला_लोendbuf        = qib_7220_माला_लोendbuf;
	dd->f_gpio_mod          = gpio_7220_mod;
	dd->f_eeprom_wen        = qib_7220_eeprom_wen;
	dd->f_hdrqempty         = qib_7220_hdrqempty;
	dd->f_ib_upकरोwn         = qib_7220_ib_upकरोwn;
	dd->f_init_ctxt         = qib_7220_init_ctxt;
	dd->f_initvl15_bufs     = qib_7220_initvl15_bufs;
	dd->f_पूर्णांकr_fallback     = qib_7220_पूर्णांकr_fallback;
	dd->f_late_initreg      = qib_late_7220_initreg;
	dd->f_setpbc_control    = qib_7220_setpbc_control;
	dd->f_portcntr          = qib_portcntr_7220;
	dd->f_put_tid           = qib_7220_put_tid;
	dd->f_quiet_serdes      = qib_7220_quiet_serdes;
	dd->f_rcvctrl           = rcvctrl_7220_mod;
	dd->f_पढ़ो_cntrs        = qib_पढ़ो_7220cntrs;
	dd->f_पढ़ो_portcntrs    = qib_पढ़ो_7220portcntrs;
	dd->f_reset             = qib_setup_7220_reset;
	dd->f_init_sdma_regs    = init_sdma_7220_regs;
	dd->f_sdma_busy         = qib_sdma_7220_busy;
	dd->f_sdma_gethead      = qib_sdma_7220_gethead;
	dd->f_sdma_sendctrl     = qib_7220_sdma_sendctrl;
	dd->f_sdma_set_desc_cnt = qib_sdma_set_7220_desc_cnt;
	dd->f_sdma_update_tail  = qib_sdma_update_7220_tail;
	dd->f_sdma_hw_clean_up  = qib_7220_sdma_hw_clean_up;
	dd->f_sdma_hw_start_up  = qib_7220_sdma_hw_start_up;
	dd->f_sdma_init_early   = qib_7220_sdma_init_early;
	dd->f_sendctrl          = sendctrl_7220_mod;
	dd->f_set_armlaunch     = qib_set_7220_armlaunch;
	dd->f_set_cntr_sample   = qib_set_cntr_7220_sample;
	dd->f_iblink_state      = qib_7220_iblink_state;
	dd->f_ibphys_portstate  = qib_7220_phys_portstate;
	dd->f_get_ib_cfg        = qib_7220_get_ib_cfg;
	dd->f_set_ib_cfg        = qib_7220_set_ib_cfg;
	dd->f_set_ib_loopback   = qib_7220_set_loopback;
	dd->f_set_पूर्णांकr_state    = qib_7220_set_पूर्णांकr_state;
	dd->f_setextled         = qib_setup_7220_setextled;
	dd->f_txchk_change      = qib_7220_txchk_change;
	dd->f_update_usrhead    = qib_update_7220_usrhead;
	dd->f_wantpiobuf_पूर्णांकr   = qib_wantpiobuf_7220_पूर्णांकr;
	dd->f_xgxs_reset        = qib_7220_xgxs_reset;
	dd->f_ग_लिखोscratch      = ग_लिखोscratch;
	dd->f_tempsense_rd	= qib_7220_tempsense_rd;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	dd->f_notअगरy_dca = qib_7220_notअगरy_dca;
#पूर्ण_अगर
	/*
	 * Do reमुख्यing pcie setup and save pcie values in dd.
	 * Any error prपूर्णांकing is alपढ़ोy करोne by the init code.
	 * On वापस, we have the chip mapped, but chip रेजिस्टरs
	 * are not set up until start of qib_init_7220_variables.
	 */
	ret = qib_pcie_ddinit(dd, pdev, ent);
	अगर (ret < 0)
		जाओ bail_मुक्त;

	/* initialize chip-specअगरic variables */
	ret = qib_init_7220_variables(dd);
	अगर (ret)
		जाओ bail_cleanup;

	अगर (qib_mini_init)
		जाओ bail;

	boardid = SYM_FIELD(dd->revision, Revision,
			    BoardID);
	चयन (boardid) अणु
	हाल 0:
	हाल 2:
	हाल 10:
	हाल 12:
		minwidth = 16; /* x16 capable boards */
		अवरोध;
	शेष:
		minwidth = 8; /* x8 capable boards */
		अवरोध;
	पूर्ण
	अगर (qib_pcie_params(dd, minwidth, शून्य))
		qib_dev_err(dd,
			"Failed to setup PCIe or interrupts; continuing anyway\n");

	अगर (qib_पढ़ो_kreg64(dd, kr_hwerrstatus) &
	    QLOGIC_IB_HWE_SERDESPLLFAILED)
		qib_ग_लिखो_kreg(dd, kr_hwerrclear,
			       QLOGIC_IB_HWE_SERDESPLLFAILED);

	/* setup पूर्णांकerrupt handler (पूर्णांकerrupt type handled above) */
	qib_setup_7220_पूर्णांकerrupt(dd);
	qib_7220_init_hwerrors(dd);

	/* clear diagctrl रेजिस्टर, in हाल diags were running and crashed */
	qib_ग_लिखो_kreg(dd, kr_hwdiagctrl, 0);

	जाओ bail;

bail_cleanup:
	qib_pcie_ddcleanup(dd);
bail_मुक्त:
	qib_मुक्त_devdata(dd);
	dd = ERR_PTR(ret);
bail:
	वापस dd;
पूर्ण
