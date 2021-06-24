<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Renesas R-Car CAN FD device driver
 *
 * Copyright (C) 2015 Renesas Electronics Corp.
 */

/* The R-Car CAN FD controller can operate in either one of the below two modes
 *  - CAN FD only mode
 *  - Classical CAN (CAN 2.0) only mode
 *
 * This driver माला_दो the controller in CAN FD only mode by शेष. In this
 * mode, the controller acts as a CAN FD node that can also पूर्णांकeroperate with
 * CAN 2.0 nodes.
 *
 * To चयन the controller to Classical CAN (CAN 2.0) only mode, add
 * "renesas,no-can-fd" optional property to the device tree node. A h/w reset is
 * also required to चयन modes.
 *
 * Note: The h/w manual रेजिस्टर naming convention is clumsy and not acceptable
 * to use as it is in the driver. However, those names are added as comments
 * wherever it is modअगरied to a पढ़ोable name.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/can/led.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/iopoll.h>

#घोषणा RCANFD_DRV_NAME			"rcar_canfd"

/* Global रेजिस्टर bits */

/* RSCFDnCFDGRMCFG */
#घोषणा RCANFD_GRMCFG_RCMC		BIT(0)

/* RSCFDnCFDGCFG / RSCFDnGCFG */
#घोषणा RCANFD_GCFG_EEFE		BIT(6)
#घोषणा RCANFD_GCFG_CMPOC		BIT(5)	/* CAN FD only */
#घोषणा RCANFD_GCFG_DCS			BIT(4)
#घोषणा RCANFD_GCFG_DCE			BIT(1)
#घोषणा RCANFD_GCFG_TPRI		BIT(0)

/* RSCFDnCFDGCTR / RSCFDnGCTR */
#घोषणा RCANFD_GCTR_TSRST		BIT(16)
#घोषणा RCANFD_GCTR_CFMPOFIE		BIT(11)	/* CAN FD only */
#घोषणा RCANFD_GCTR_THLEIE		BIT(10)
#घोषणा RCANFD_GCTR_MEIE		BIT(9)
#घोषणा RCANFD_GCTR_DEIE		BIT(8)
#घोषणा RCANFD_GCTR_GSLPR		BIT(2)
#घोषणा RCANFD_GCTR_GMDC_MASK		(0x3)
#घोषणा RCANFD_GCTR_GMDC_GOPM		(0x0)
#घोषणा RCANFD_GCTR_GMDC_GRESET		(0x1)
#घोषणा RCANFD_GCTR_GMDC_GTEST		(0x2)

/* RSCFDnCFDGSTS / RSCFDnGSTS */
#घोषणा RCANFD_GSTS_GRAMINIT		BIT(3)
#घोषणा RCANFD_GSTS_GSLPSTS		BIT(2)
#घोषणा RCANFD_GSTS_GHLTSTS		BIT(1)
#घोषणा RCANFD_GSTS_GRSTSTS		BIT(0)
/* Non-operational status */
#घोषणा RCANFD_GSTS_GNOPM		(BIT(0) | BIT(1) | BIT(2) | BIT(3))

/* RSCFDnCFDGERFL / RSCFDnGERFL */
#घोषणा RCANFD_GERFL_EEF1		BIT(17)
#घोषणा RCANFD_GERFL_EEF0		BIT(16)
#घोषणा RCANFD_GERFL_CMPOF		BIT(3)	/* CAN FD only */
#घोषणा RCANFD_GERFL_THLES		BIT(2)
#घोषणा RCANFD_GERFL_MES		BIT(1)
#घोषणा RCANFD_GERFL_DEF		BIT(0)

#घोषणा RCANFD_GERFL_ERR(gpriv, x)	((x) & (RCANFD_GERFL_EEF1 |\
					RCANFD_GERFL_EEF0 | RCANFD_GERFL_MES |\
					(gpriv->fdmode ?\
					 RCANFD_GERFL_CMPOF : 0)))

/* AFL Rx rules रेजिस्टरs */

/* RSCFDnCFDGAFLCFG0 / RSCFDnGAFLCFG0 */
#घोषणा RCANFD_GAFLCFG_SETRNC(n, x)	(((x) & 0xff) << (24 - n * 8))
#घोषणा RCANFD_GAFLCFG_GETRNC(n, x)	(((x) >> (24 - n * 8)) & 0xff)

/* RSCFDnCFDGAFLECTR / RSCFDnGAFLECTR */
#घोषणा RCANFD_GAFLECTR_AFLDAE		BIT(8)
#घोषणा RCANFD_GAFLECTR_AFLPN(x)	((x) & 0x1f)

/* RSCFDnCFDGAFLIDj / RSCFDnGAFLIDj */
#घोषणा RCANFD_GAFLID_GAFLLB		BIT(29)

/* RSCFDnCFDGAFLP1_j / RSCFDnGAFLP1_j */
#घोषणा RCANFD_GAFLP1_GAFLFDP(x)	(1 << (x))

/* Channel रेजिस्टर bits */

/* RSCFDnCmCFG - Classical CAN only */
#घोषणा RCANFD_CFG_SJW(x)		(((x) & 0x3) << 24)
#घोषणा RCANFD_CFG_TSEG2(x)		(((x) & 0x7) << 20)
#घोषणा RCANFD_CFG_TSEG1(x)		(((x) & 0xf) << 16)
#घोषणा RCANFD_CFG_BRP(x)		(((x) & 0x3ff) << 0)

/* RSCFDnCFDCmNCFG - CAN FD only */
#घोषणा RCANFD_NCFG_NTSEG2(x)		(((x) & 0x1f) << 24)
#घोषणा RCANFD_NCFG_NTSEG1(x)		(((x) & 0x7f) << 16)
#घोषणा RCANFD_NCFG_NSJW(x)		(((x) & 0x1f) << 11)
#घोषणा RCANFD_NCFG_NBRP(x)		(((x) & 0x3ff) << 0)

/* RSCFDnCFDCmCTR / RSCFDnCmCTR */
#घोषणा RCANFD_CCTR_CTME		BIT(24)
#घोषणा RCANFD_CCTR_ERRD		BIT(23)
#घोषणा RCANFD_CCTR_BOM_MASK		(0x3 << 21)
#घोषणा RCANFD_CCTR_BOM_ISO		(0x0 << 21)
#घोषणा RCANFD_CCTR_BOM_BENTRY		(0x1 << 21)
#घोषणा RCANFD_CCTR_BOM_BEND		(0x2 << 21)
#घोषणा RCANFD_CCTR_TDCVFIE		BIT(19)
#घोषणा RCANFD_CCTR_SOCOIE		BIT(18)
#घोषणा RCANFD_CCTR_EOCOIE		BIT(17)
#घोषणा RCANFD_CCTR_TAIE		BIT(16)
#घोषणा RCANFD_CCTR_ALIE		BIT(15)
#घोषणा RCANFD_CCTR_BLIE		BIT(14)
#घोषणा RCANFD_CCTR_OLIE		BIT(13)
#घोषणा RCANFD_CCTR_BORIE		BIT(12)
#घोषणा RCANFD_CCTR_BOEIE		BIT(11)
#घोषणा RCANFD_CCTR_EPIE		BIT(10)
#घोषणा RCANFD_CCTR_EWIE		BIT(9)
#घोषणा RCANFD_CCTR_BEIE		BIT(8)
#घोषणा RCANFD_CCTR_CSLPR		BIT(2)
#घोषणा RCANFD_CCTR_CHMDC_MASK		(0x3)
#घोषणा RCANFD_CCTR_CHDMC_COPM		(0x0)
#घोषणा RCANFD_CCTR_CHDMC_CRESET	(0x1)
#घोषणा RCANFD_CCTR_CHDMC_CHLT		(0x2)

/* RSCFDnCFDCmSTS / RSCFDnCmSTS */
#घोषणा RCANFD_CSTS_COMSTS		BIT(7)
#घोषणा RCANFD_CSTS_RECSTS		BIT(6)
#घोषणा RCANFD_CSTS_TRMSTS		BIT(5)
#घोषणा RCANFD_CSTS_BOSTS		BIT(4)
#घोषणा RCANFD_CSTS_EPSTS		BIT(3)
#घोषणा RCANFD_CSTS_SLPSTS		BIT(2)
#घोषणा RCANFD_CSTS_HLTSTS		BIT(1)
#घोषणा RCANFD_CSTS_CRSTSTS		BIT(0)

#घोषणा RCANFD_CSTS_TECCNT(x)		(((x) >> 24) & 0xff)
#घोषणा RCANFD_CSTS_RECCNT(x)		(((x) >> 16) & 0xff)

/* RSCFDnCFDCmERFL / RSCFDnCmERFL */
#घोषणा RCANFD_CERFL_ADERR		BIT(14)
#घोषणा RCANFD_CERFL_B0ERR		BIT(13)
#घोषणा RCANFD_CERFL_B1ERR		BIT(12)
#घोषणा RCANFD_CERFL_CERR		BIT(11)
#घोषणा RCANFD_CERFL_AERR		BIT(10)
#घोषणा RCANFD_CERFL_FERR		BIT(9)
#घोषणा RCANFD_CERFL_SERR		BIT(8)
#घोषणा RCANFD_CERFL_ALF		BIT(7)
#घोषणा RCANFD_CERFL_BLF		BIT(6)
#घोषणा RCANFD_CERFL_OVLF		BIT(5)
#घोषणा RCANFD_CERFL_BORF		BIT(4)
#घोषणा RCANFD_CERFL_BOEF		BIT(3)
#घोषणा RCANFD_CERFL_EPF		BIT(2)
#घोषणा RCANFD_CERFL_EWF		BIT(1)
#घोषणा RCANFD_CERFL_BEF		BIT(0)

#घोषणा RCANFD_CERFL_ERR(x)		((x) & (0x7fff)) /* above bits 14:0 */

/* RSCFDnCFDCmDCFG */
#घोषणा RCANFD_DCFG_DSJW(x)		(((x) & 0x7) << 24)
#घोषणा RCANFD_DCFG_DTSEG2(x)		(((x) & 0x7) << 20)
#घोषणा RCANFD_DCFG_DTSEG1(x)		(((x) & 0xf) << 16)
#घोषणा RCANFD_DCFG_DBRP(x)		(((x) & 0xff) << 0)

/* RSCFDnCFDCmFDCFG */
#घोषणा RCANFD_FDCFG_TDCE		BIT(9)
#घोषणा RCANFD_FDCFG_TDCOC		BIT(8)
#घोषणा RCANFD_FDCFG_TDCO(x)		(((x) & 0x7f) >> 16)

/* RSCFDnCFDRFCCx */
#घोषणा RCANFD_RFCC_RFIM		BIT(12)
#घोषणा RCANFD_RFCC_RFDC(x)		(((x) & 0x7) << 8)
#घोषणा RCANFD_RFCC_RFPLS(x)		(((x) & 0x7) << 4)
#घोषणा RCANFD_RFCC_RFIE		BIT(1)
#घोषणा RCANFD_RFCC_RFE			BIT(0)

/* RSCFDnCFDRFSTSx */
#घोषणा RCANFD_RFSTS_RFIF		BIT(3)
#घोषणा RCANFD_RFSTS_RFMLT		BIT(2)
#घोषणा RCANFD_RFSTS_RFFLL		BIT(1)
#घोषणा RCANFD_RFSTS_RFEMP		BIT(0)

/* RSCFDnCFDRFIDx */
#घोषणा RCANFD_RFID_RFIDE		BIT(31)
#घोषणा RCANFD_RFID_RFRTR		BIT(30)

/* RSCFDnCFDRFPTRx */
#घोषणा RCANFD_RFPTR_RFDLC(x)		(((x) >> 28) & 0xf)
#घोषणा RCANFD_RFPTR_RFPTR(x)		(((x) >> 16) & 0xfff)
#घोषणा RCANFD_RFPTR_RFTS(x)		(((x) >> 0) & 0xffff)

/* RSCFDnCFDRFFDSTSx */
#घोषणा RCANFD_RFFDSTS_RFFDF		BIT(2)
#घोषणा RCANFD_RFFDSTS_RFBRS		BIT(1)
#घोषणा RCANFD_RFFDSTS_RFESI		BIT(0)

/* Common FIFO bits */

/* RSCFDnCFDCFCCk */
#घोषणा RCANFD_CFCC_CFTML(x)		(((x) & 0xf) << 20)
#घोषणा RCANFD_CFCC_CFM(x)		(((x) & 0x3) << 16)
#घोषणा RCANFD_CFCC_CFIM		BIT(12)
#घोषणा RCANFD_CFCC_CFDC(x)		(((x) & 0x7) << 8)
#घोषणा RCANFD_CFCC_CFPLS(x)		(((x) & 0x7) << 4)
#घोषणा RCANFD_CFCC_CFTXIE		BIT(2)
#घोषणा RCANFD_CFCC_CFE			BIT(0)

/* RSCFDnCFDCFSTSk */
#घोषणा RCANFD_CFSTS_CFMC(x)		(((x) >> 8) & 0xff)
#घोषणा RCANFD_CFSTS_CFTXIF		BIT(4)
#घोषणा RCANFD_CFSTS_CFMLT		BIT(2)
#घोषणा RCANFD_CFSTS_CFFLL		BIT(1)
#घोषणा RCANFD_CFSTS_CFEMP		BIT(0)

/* RSCFDnCFDCFIDk */
#घोषणा RCANFD_CFID_CFIDE		BIT(31)
#घोषणा RCANFD_CFID_CFRTR		BIT(30)
#घोषणा RCANFD_CFID_CFID_MASK(x)	((x) & 0x1fffffff)

/* RSCFDnCFDCFPTRk */
#घोषणा RCANFD_CFPTR_CFDLC(x)		(((x) & 0xf) << 28)
#घोषणा RCANFD_CFPTR_CFPTR(x)		(((x) & 0xfff) << 16)
#घोषणा RCANFD_CFPTR_CFTS(x)		(((x) & 0xff) << 0)

/* RSCFDnCFDCFFDCSTSk */
#घोषणा RCANFD_CFFDCSTS_CFFDF		BIT(2)
#घोषणा RCANFD_CFFDCSTS_CFBRS		BIT(1)
#घोषणा RCANFD_CFFDCSTS_CFESI		BIT(0)

/* This controller supports either Classical CAN only mode or CAN FD only mode.
 * These modes are supported in two separate set of रेजिस्टर maps & names.
 * However, some of the रेजिस्टर offsets are common क्रम both modes. Those
 * offsets are listed below as Common रेजिस्टरs.
 *
 * The CAN FD only mode specअगरic रेजिस्टरs & Classical CAN only mode specअगरic
 * रेजिस्टरs are listed separately. Their रेजिस्टर names starts with
 * RCANFD_F_xxx & RCANFD_C_xxx respectively.
 */

/* Common रेजिस्टरs */

/* RSCFDnCFDCmNCFG / RSCFDnCmCFG */
#घोषणा RCANFD_CCFG(m)			(0x0000 + (0x10 * (m)))
/* RSCFDnCFDCmCTR / RSCFDnCmCTR */
#घोषणा RCANFD_CCTR(m)			(0x0004 + (0x10 * (m)))
/* RSCFDnCFDCmSTS / RSCFDnCmSTS */
#घोषणा RCANFD_CSTS(m)			(0x0008 + (0x10 * (m)))
/* RSCFDnCFDCmERFL / RSCFDnCmERFL */
#घोषणा RCANFD_CERFL(m)			(0x000C + (0x10 * (m)))

/* RSCFDnCFDGCFG / RSCFDnGCFG */
#घोषणा RCANFD_GCFG			(0x0084)
/* RSCFDnCFDGCTR / RSCFDnGCTR */
#घोषणा RCANFD_GCTR			(0x0088)
/* RSCFDnCFDGCTS / RSCFDnGCTS */
#घोषणा RCANFD_GSTS			(0x008c)
/* RSCFDnCFDGERFL / RSCFDnGERFL */
#घोषणा RCANFD_GERFL			(0x0090)
/* RSCFDnCFDGTSC / RSCFDnGTSC */
#घोषणा RCANFD_GTSC			(0x0094)
/* RSCFDnCFDGAFLECTR / RSCFDnGAFLECTR */
#घोषणा RCANFD_GAFLECTR			(0x0098)
/* RSCFDnCFDGAFLCFG0 / RSCFDnGAFLCFG0 */
#घोषणा RCANFD_GAFLCFG0			(0x009c)
/* RSCFDnCFDGAFLCFG1 / RSCFDnGAFLCFG1 */
#घोषणा RCANFD_GAFLCFG1			(0x00a0)
/* RSCFDnCFDRMNB / RSCFDnRMNB */
#घोषणा RCANFD_RMNB			(0x00a4)
/* RSCFDnCFDRMND / RSCFDnRMND */
#घोषणा RCANFD_RMND(y)			(0x00a8 + (0x04 * (y)))

/* RSCFDnCFDRFCCx / RSCFDnRFCCx */
#घोषणा RCANFD_RFCC(x)			(0x00b8 + (0x04 * (x)))
/* RSCFDnCFDRFSTSx / RSCFDnRFSTSx */
#घोषणा RCANFD_RFSTS(x)			(0x00d8 + (0x04 * (x)))
/* RSCFDnCFDRFPCTRx / RSCFDnRFPCTRx */
#घोषणा RCANFD_RFPCTR(x)		(0x00f8 + (0x04 * (x)))

/* Common FIFO Control रेजिस्टरs */

/* RSCFDnCFDCFCCx / RSCFDnCFCCx */
#घोषणा RCANFD_CFCC(ch, idx)		(0x0118 + (0x0c * (ch)) + \
					 (0x04 * (idx)))
/* RSCFDnCFDCFSTSx / RSCFDnCFSTSx */
#घोषणा RCANFD_CFSTS(ch, idx)		(0x0178 + (0x0c * (ch)) + \
					 (0x04 * (idx)))
/* RSCFDnCFDCFPCTRx / RSCFDnCFPCTRx */
#घोषणा RCANFD_CFPCTR(ch, idx)		(0x01d8 + (0x0c * (ch)) + \
					 (0x04 * (idx)))

/* RSCFDnCFDFESTS / RSCFDnFESTS */
#घोषणा RCANFD_FESTS			(0x0238)
/* RSCFDnCFDFFSTS / RSCFDnFFSTS */
#घोषणा RCANFD_FFSTS			(0x023c)
/* RSCFDnCFDFMSTS / RSCFDnFMSTS */
#घोषणा RCANFD_FMSTS			(0x0240)
/* RSCFDnCFDRFISTS / RSCFDnRFISTS */
#घोषणा RCANFD_RFISTS			(0x0244)
/* RSCFDnCFDCFRISTS / RSCFDnCFRISTS */
#घोषणा RCANFD_CFRISTS			(0x0248)
/* RSCFDnCFDCFTISTS / RSCFDnCFTISTS */
#घोषणा RCANFD_CFTISTS			(0x024c)

/* RSCFDnCFDTMCp / RSCFDnTMCp */
#घोषणा RCANFD_TMC(p)			(0x0250 + (0x01 * (p)))
/* RSCFDnCFDTMSTSp / RSCFDnTMSTSp */
#घोषणा RCANFD_TMSTS(p)			(0x02d0 + (0x01 * (p)))

/* RSCFDnCFDTMTRSTSp / RSCFDnTMTRSTSp */
#घोषणा RCANFD_TMTRSTS(y)		(0x0350 + (0x04 * (y)))
/* RSCFDnCFDTMTARSTSp / RSCFDnTMTARSTSp */
#घोषणा RCANFD_TMTARSTS(y)		(0x0360 + (0x04 * (y)))
/* RSCFDnCFDTMTCSTSp / RSCFDnTMTCSTSp */
#घोषणा RCANFD_TMTCSTS(y)		(0x0370 + (0x04 * (y)))
/* RSCFDnCFDTMTASTSp / RSCFDnTMTASTSp */
#घोषणा RCANFD_TMTASTS(y)		(0x0380 + (0x04 * (y)))
/* RSCFDnCFDTMIECy / RSCFDnTMIECy */
#घोषणा RCANFD_TMIEC(y)			(0x0390 + (0x04 * (y)))

/* RSCFDnCFDTXQCCm / RSCFDnTXQCCm */
#घोषणा RCANFD_TXQCC(m)			(0x03a0 + (0x04 * (m)))
/* RSCFDnCFDTXQSTSm / RSCFDnTXQSTSm */
#घोषणा RCANFD_TXQSTS(m)		(0x03c0 + (0x04 * (m)))
/* RSCFDnCFDTXQPCTRm / RSCFDnTXQPCTRm */
#घोषणा RCANFD_TXQPCTR(m)		(0x03e0 + (0x04 * (m)))

/* RSCFDnCFDTHLCCm / RSCFDnTHLCCm */
#घोषणा RCANFD_THLCC(m)			(0x0400 + (0x04 * (m)))
/* RSCFDnCFDTHLSTSm / RSCFDnTHLSTSm */
#घोषणा RCANFD_THLSTS(m)		(0x0420 + (0x04 * (m)))
/* RSCFDnCFDTHLPCTRm / RSCFDnTHLPCTRm */
#घोषणा RCANFD_THLPCTR(m)		(0x0440 + (0x04 * (m)))

/* RSCFDnCFDGTINTSTS0 / RSCFDnGTINTSTS0 */
#घोषणा RCANFD_GTINTSTS0		(0x0460)
/* RSCFDnCFDGTINTSTS1 / RSCFDnGTINTSTS1 */
#घोषणा RCANFD_GTINTSTS1		(0x0464)
/* RSCFDnCFDGTSTCFG / RSCFDnGTSTCFG */
#घोषणा RCANFD_GTSTCFG			(0x0468)
/* RSCFDnCFDGTSTCTR / RSCFDnGTSTCTR */
#घोषणा RCANFD_GTSTCTR			(0x046c)
/* RSCFDnCFDGLOCKK / RSCFDnGLOCKK */
#घोषणा RCANFD_GLOCKK			(0x047c)
/* RSCFDnCFDGRMCFG */
#घोषणा RCANFD_GRMCFG			(0x04fc)

/* RSCFDnCFDGAFLIDj / RSCFDnGAFLIDj */
#घोषणा RCANFD_GAFLID(offset, j)	((offset) + (0x10 * (j)))
/* RSCFDnCFDGAFLMj / RSCFDnGAFLMj */
#घोषणा RCANFD_GAFLM(offset, j)		((offset) + 0x04 + (0x10 * (j)))
/* RSCFDnCFDGAFLP0j / RSCFDnGAFLP0j */
#घोषणा RCANFD_GAFLP0(offset, j)	((offset) + 0x08 + (0x10 * (j)))
/* RSCFDnCFDGAFLP1j / RSCFDnGAFLP1j */
#घोषणा RCANFD_GAFLP1(offset, j)	((offset) + 0x0c + (0x10 * (j)))

/* Classical CAN only mode रेजिस्टर map */

/* RSCFDnGAFLXXXj offset */
#घोषणा RCANFD_C_GAFL_OFFSET		(0x0500)

/* RSCFDnRMXXXq -> RCANFD_C_RMXXX(q) */
#घोषणा RCANFD_C_RMID(q)		(0x0600 + (0x10 * (q)))
#घोषणा RCANFD_C_RMPTR(q)		(0x0604 + (0x10 * (q)))
#घोषणा RCANFD_C_RMDF0(q)		(0x0608 + (0x10 * (q)))
#घोषणा RCANFD_C_RMDF1(q)		(0x060c + (0x10 * (q)))

/* RSCFDnRFXXx -> RCANFD_C_RFXX(x) */
#घोषणा RCANFD_C_RFOFFSET		(0x0e00)
#घोषणा RCANFD_C_RFID(x)		(RCANFD_C_RFOFFSET + (0x10 * (x)))
#घोषणा RCANFD_C_RFPTR(x)		(RCANFD_C_RFOFFSET + 0x04 + \
					 (0x10 * (x)))
#घोषणा RCANFD_C_RFDF(x, df)		(RCANFD_C_RFOFFSET + 0x08 + \
					 (0x10 * (x)) + (0x04 * (df)))

/* RSCFDnCFXXk -> RCANFD_C_CFXX(ch, k) */
#घोषणा RCANFD_C_CFOFFSET		(0x0e80)
#घोषणा RCANFD_C_CFID(ch, idx)		(RCANFD_C_CFOFFSET + (0x30 * (ch)) + \
					 (0x10 * (idx)))
#घोषणा RCANFD_C_CFPTR(ch, idx)		(RCANFD_C_CFOFFSET + 0x04 + \
					 (0x30 * (ch)) + (0x10 * (idx)))
#घोषणा RCANFD_C_CFDF(ch, idx, df)	(RCANFD_C_CFOFFSET + 0x08 + \
					 (0x30 * (ch)) + (0x10 * (idx)) + \
					 (0x04 * (df)))

/* RSCFDnTMXXp -> RCANFD_C_TMXX(p) */
#घोषणा RCANFD_C_TMID(p)		(0x1000 + (0x10 * (p)))
#घोषणा RCANFD_C_TMPTR(p)		(0x1004 + (0x10 * (p)))
#घोषणा RCANFD_C_TMDF0(p)		(0x1008 + (0x10 * (p)))
#घोषणा RCANFD_C_TMDF1(p)		(0x100c + (0x10 * (p)))

/* RSCFDnTHLACCm */
#घोषणा RCANFD_C_THLACC(m)		(0x1800 + (0x04 * (m)))
/* RSCFDnRPGACCr */
#घोषणा RCANFD_C_RPGACC(r)		(0x1900 + (0x04 * (r)))

/* CAN FD mode specअगरic रेजिस्टर map */

/* RSCFDnCFDCmXXX -> RCANFD_F_XXX(m) */
#घोषणा RCANFD_F_DCFG(m)		(0x0500 + (0x20 * (m)))
#घोषणा RCANFD_F_CFDCFG(m)		(0x0504 + (0x20 * (m)))
#घोषणा RCANFD_F_CFDCTR(m)		(0x0508 + (0x20 * (m)))
#घोषणा RCANFD_F_CFDSTS(m)		(0x050c + (0x20 * (m)))
#घोषणा RCANFD_F_CFDCRC(m)		(0x0510 + (0x20 * (m)))

/* RSCFDnCFDGAFLXXXj offset */
#घोषणा RCANFD_F_GAFL_OFFSET		(0x1000)

/* RSCFDnCFDRMXXXq -> RCANFD_F_RMXXX(q) */
#घोषणा RCANFD_F_RMID(q)		(0x2000 + (0x20 * (q)))
#घोषणा RCANFD_F_RMPTR(q)		(0x2004 + (0x20 * (q)))
#घोषणा RCANFD_F_RMFDSTS(q)		(0x2008 + (0x20 * (q)))
#घोषणा RCANFD_F_RMDF(q, b)		(0x200c + (0x04 * (b)) + (0x20 * (q)))

/* RSCFDnCFDRFXXx -> RCANFD_F_RFXX(x) */
#घोषणा RCANFD_F_RFOFFSET		(0x3000)
#घोषणा RCANFD_F_RFID(x)		(RCANFD_F_RFOFFSET + (0x80 * (x)))
#घोषणा RCANFD_F_RFPTR(x)		(RCANFD_F_RFOFFSET + 0x04 + \
					 (0x80 * (x)))
#घोषणा RCANFD_F_RFFDSTS(x)		(RCANFD_F_RFOFFSET + 0x08 + \
					 (0x80 * (x)))
#घोषणा RCANFD_F_RFDF(x, df)		(RCANFD_F_RFOFFSET + 0x0c + \
					 (0x80 * (x)) + (0x04 * (df)))

/* RSCFDnCFDCFXXk -> RCANFD_F_CFXX(ch, k) */
#घोषणा RCANFD_F_CFOFFSET		(0x3400)
#घोषणा RCANFD_F_CFID(ch, idx)		(RCANFD_F_CFOFFSET + (0x180 * (ch)) + \
					 (0x80 * (idx)))
#घोषणा RCANFD_F_CFPTR(ch, idx)		(RCANFD_F_CFOFFSET + 0x04 + \
					 (0x180 * (ch)) + (0x80 * (idx)))
#घोषणा RCANFD_F_CFFDCSTS(ch, idx)	(RCANFD_F_CFOFFSET + 0x08 + \
					 (0x180 * (ch)) + (0x80 * (idx)))
#घोषणा RCANFD_F_CFDF(ch, idx, df)	(RCANFD_F_CFOFFSET + 0x0c + \
					 (0x180 * (ch)) + (0x80 * (idx)) + \
					 (0x04 * (df)))

/* RSCFDnCFDTMXXp -> RCANFD_F_TMXX(p) */
#घोषणा RCANFD_F_TMID(p)		(0x4000 + (0x20 * (p)))
#घोषणा RCANFD_F_TMPTR(p)		(0x4004 + (0x20 * (p)))
#घोषणा RCANFD_F_TMFDCTR(p)		(0x4008 + (0x20 * (p)))
#घोषणा RCANFD_F_TMDF(p, b)		(0x400c + (0x20 * (p)) + (0x04 * (b)))

/* RSCFDnCFDTHLACCm */
#घोषणा RCANFD_F_THLACC(m)		(0x6000 + (0x04 * (m)))
/* RSCFDnCFDRPGACCr */
#घोषणा RCANFD_F_RPGACC(r)		(0x6400 + (0x04 * (r)))

/* Constants */
#घोषणा RCANFD_FIFO_DEPTH		8	/* Tx FIFO depth */
#घोषणा RCANFD_NAPI_WEIGHT		8	/* Rx poll quota */

#घोषणा RCANFD_NUM_CHANNELS		2	/* Two channels max */
#घोषणा RCANFD_CHANNELS_MASK		BIT((RCANFD_NUM_CHANNELS) - 1)

#घोषणा RCANFD_GAFL_PAGENUM(entry)	((entry) / 16)
#घोषणा RCANFD_CHANNEL_NUMRULES		1	/* only one rule per channel */

/* Rx FIFO is a global resource of the controller. There are 8 such FIFOs
 * available. Each channel माला_लो a dedicated Rx FIFO (i.e.) the channel
 * number is added to RFFIFO index.
 */
#घोषणा RCANFD_RFFIFO_IDX		0

/* Tx/Rx or Common FIFO is a per channel resource. Each channel has 3 Common
 * FIFOs dedicated to them. Use the first (index 0) FIFO out of the 3 क्रम Tx.
 */
#घोषणा RCANFD_CFFIFO_IDX		0

/* fCAN घड़ी select रेजिस्टर settings */
क्रमागत rcar_canfd_fcanclk अणु
	RCANFD_CANFDCLK = 0,		/* CANFD घड़ी */
	RCANFD_EXTCLK,			/* Externally input घड़ी */
पूर्ण;

काष्ठा rcar_canfd_global;

/* Channel priv data */
काष्ठा rcar_canfd_channel अणु
	काष्ठा can_priv can;			/* Must be the first member */
	काष्ठा net_device *ndev;
	काष्ठा rcar_canfd_global *gpriv;	/* Controller reference */
	व्योम __iomem *base;			/* Register base address */
	काष्ठा napi_काष्ठा napi;
	u8  tx_len[RCANFD_FIFO_DEPTH];		/* For net stats */
	u32 tx_head;				/* Incremented on xmit */
	u32 tx_tail;				/* Incremented on xmit करोne */
	u32 channel;				/* Channel number */
	spinlock_t tx_lock;			/* To protect tx path */
पूर्ण;

/* Global priv data */
काष्ठा rcar_canfd_global अणु
	काष्ठा rcar_canfd_channel *ch[RCANFD_NUM_CHANNELS];
	व्योम __iomem *base;		/* Register base address */
	काष्ठा platक्रमm_device *pdev;	/* Respective platक्रमm device */
	काष्ठा clk *clkp;		/* Peripheral घड़ी */
	काष्ठा clk *can_clk;		/* fCAN घड़ी */
	क्रमागत rcar_canfd_fcanclk fcan;	/* CANFD or Ext घड़ी */
	अचिन्हित दीर्घ channels_mask;	/* Enabled channels mask */
	bool fdmode;			/* CAN FD or Classical CAN only mode */
पूर्ण;

/* CAN FD mode nominal rate स्थिरants */
अटल स्थिर काष्ठा can_bittiming_स्थिर rcar_canfd_nom_bittiming_स्थिर = अणु
	.name = RCANFD_DRV_NAME,
	.tseg1_min = 2,
	.tseg1_max = 128,
	.tseg2_min = 2,
	.tseg2_max = 32,
	.sjw_max = 32,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

/* CAN FD mode data rate स्थिरants */
अटल स्थिर काष्ठा can_bittiming_स्थिर rcar_canfd_data_bittiming_स्थिर = अणु
	.name = RCANFD_DRV_NAME,
	.tseg1_min = 2,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 8,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

/* Classical CAN mode bitrate स्थिरants */
अटल स्थिर काष्ठा can_bittiming_स्थिर rcar_canfd_bittiming_स्थिर = अणु
	.name = RCANFD_DRV_NAME,
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

/* Helper functions */
अटल अंतरभूत व्योम rcar_canfd_update(u32 mask, u32 val, u32 __iomem *reg)
अणु
	u32 data = पढ़ोl(reg);

	data &= ~mask;
	data |= (val & mask);
	ग_लिखोl(data, reg);
पूर्ण

अटल अंतरभूत u32 rcar_canfd_पढ़ो(व्योम __iomem *base, u32 offset)
अणु
	वापस पढ़ोl(base + (offset));
पूर्ण

अटल अंतरभूत व्योम rcar_canfd_ग_लिखो(व्योम __iomem *base, u32 offset, u32 val)
अणु
	ग_लिखोl(val, base + (offset));
पूर्ण

अटल व्योम rcar_canfd_set_bit(व्योम __iomem *base, u32 reg, u32 val)
अणु
	rcar_canfd_update(val, val, base + (reg));
पूर्ण

अटल व्योम rcar_canfd_clear_bit(व्योम __iomem *base, u32 reg, u32 val)
अणु
	rcar_canfd_update(val, 0, base + (reg));
पूर्ण

अटल व्योम rcar_canfd_update_bit(व्योम __iomem *base, u32 reg,
				  u32 mask, u32 val)
अणु
	rcar_canfd_update(mask, val, base + (reg));
पूर्ण

अटल व्योम rcar_canfd_get_data(काष्ठा rcar_canfd_channel *priv,
				काष्ठा canfd_frame *cf, u32 off)
अणु
	u32 i, lwords;

	lwords = DIV_ROUND_UP(cf->len, माप(u32));
	क्रम (i = 0; i < lwords; i++)
		*((u32 *)cf->data + i) =
			rcar_canfd_पढ़ो(priv->base, off + (i * माप(u32)));
पूर्ण

अटल व्योम rcar_canfd_put_data(काष्ठा rcar_canfd_channel *priv,
				काष्ठा canfd_frame *cf, u32 off)
अणु
	u32 i, lwords;

	lwords = DIV_ROUND_UP(cf->len, माप(u32));
	क्रम (i = 0; i < lwords; i++)
		rcar_canfd_ग_लिखो(priv->base, off + (i * माप(u32)),
				 *((u32 *)cf->data + i));
पूर्ण

अटल व्योम rcar_canfd_tx_failure_cleanup(काष्ठा net_device *ndev)
अणु
	u32 i;

	क्रम (i = 0; i < RCANFD_FIFO_DEPTH; i++)
		can_मुक्त_echo_skb(ndev, i, शून्य);
पूर्ण

अटल पूर्णांक rcar_canfd_reset_controller(काष्ठा rcar_canfd_global *gpriv)
अणु
	u32 sts, ch;
	पूर्णांक err;

	/* Check RAMINIT flag as CAN RAM initialization takes place
	 * after the MCU reset
	 */
	err = पढ़ोl_poll_समयout((gpriv->base + RCANFD_GSTS), sts,
				 !(sts & RCANFD_GSTS_GRAMINIT), 2, 500000);
	अगर (err) अणु
		dev_dbg(&gpriv->pdev->dev, "global raminit failed\n");
		वापस err;
	पूर्ण

	/* Transition to Global Reset mode */
	rcar_canfd_clear_bit(gpriv->base, RCANFD_GCTR, RCANFD_GCTR_GSLPR);
	rcar_canfd_update_bit(gpriv->base, RCANFD_GCTR,
			      RCANFD_GCTR_GMDC_MASK, RCANFD_GCTR_GMDC_GRESET);

	/* Ensure Global reset mode */
	err = पढ़ोl_poll_समयout((gpriv->base + RCANFD_GSTS), sts,
				 (sts & RCANFD_GSTS_GRSTSTS), 2, 500000);
	अगर (err) अणु
		dev_dbg(&gpriv->pdev->dev, "global reset failed\n");
		वापस err;
	पूर्ण

	/* Reset Global error flags */
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_GERFL, 0x0);

	/* Set the controller पूर्णांकo appropriate mode */
	अगर (gpriv->fdmode)
		rcar_canfd_set_bit(gpriv->base, RCANFD_GRMCFG,
				   RCANFD_GRMCFG_RCMC);
	अन्यथा
		rcar_canfd_clear_bit(gpriv->base, RCANFD_GRMCFG,
				     RCANFD_GRMCFG_RCMC);

	/* Transition all Channels to reset mode */
	क्रम_each_set_bit(ch, &gpriv->channels_mask, RCANFD_NUM_CHANNELS) अणु
		rcar_canfd_clear_bit(gpriv->base,
				     RCANFD_CCTR(ch), RCANFD_CCTR_CSLPR);

		rcar_canfd_update_bit(gpriv->base, RCANFD_CCTR(ch),
				      RCANFD_CCTR_CHMDC_MASK,
				      RCANFD_CCTR_CHDMC_CRESET);

		/* Ensure Channel reset mode */
		err = पढ़ोl_poll_समयout((gpriv->base + RCANFD_CSTS(ch)), sts,
					 (sts & RCANFD_CSTS_CRSTSTS),
					 2, 500000);
		अगर (err) अणु
			dev_dbg(&gpriv->pdev->dev,
				"channel %u reset failed\n", ch);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम rcar_canfd_configure_controller(काष्ठा rcar_canfd_global *gpriv)
अणु
	u32 cfg, ch;

	/* Global configuration settings */

	/* ECC Error flag Enable */
	cfg = RCANFD_GCFG_EEFE;

	अगर (gpriv->fdmode)
		/* Truncate payload to configured message size RFPLS */
		cfg |= RCANFD_GCFG_CMPOC;

	/* Set External Clock अगर selected */
	अगर (gpriv->fcan != RCANFD_CANFDCLK)
		cfg |= RCANFD_GCFG_DCS;

	rcar_canfd_set_bit(gpriv->base, RCANFD_GCFG, cfg);

	/* Channel configuration settings */
	क्रम_each_set_bit(ch, &gpriv->channels_mask, RCANFD_NUM_CHANNELS) अणु
		rcar_canfd_set_bit(gpriv->base, RCANFD_CCTR(ch),
				   RCANFD_CCTR_ERRD);
		rcar_canfd_update_bit(gpriv->base, RCANFD_CCTR(ch),
				      RCANFD_CCTR_BOM_MASK,
				      RCANFD_CCTR_BOM_BENTRY);
	पूर्ण
पूर्ण

अटल व्योम rcar_canfd_configure_afl_rules(काष्ठा rcar_canfd_global *gpriv,
					   u32 ch)
अणु
	u32 cfg;
	पूर्णांक offset, start, page, num_rules = RCANFD_CHANNEL_NUMRULES;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	अगर (ch == 0) अणु
		start = 0; /* Channel 0 always starts from 0th rule */
	पूर्ण अन्यथा अणु
		/* Get number of Channel 0 rules and adjust */
		cfg = rcar_canfd_पढ़ो(gpriv->base, RCANFD_GAFLCFG0);
		start = RCANFD_GAFLCFG_GETRNC(0, cfg);
	पूर्ण

	/* Enable ग_लिखो access to entry */
	page = RCANFD_GAFL_PAGENUM(start);
	rcar_canfd_set_bit(gpriv->base, RCANFD_GAFLECTR,
			   (RCANFD_GAFLECTR_AFLPN(page) |
			    RCANFD_GAFLECTR_AFLDAE));

	/* Write number of rules क्रम channel */
	rcar_canfd_set_bit(gpriv->base, RCANFD_GAFLCFG0,
			   RCANFD_GAFLCFG_SETRNC(ch, num_rules));
	अगर (gpriv->fdmode)
		offset = RCANFD_F_GAFL_OFFSET;
	अन्यथा
		offset = RCANFD_C_GAFL_OFFSET;

	/* Accept all IDs */
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_GAFLID(offset, start), 0);
	/* IDE or RTR is not considered क्रम matching */
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_GAFLM(offset, start), 0);
	/* Any data length accepted */
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_GAFLP0(offset, start), 0);
	/* Place the msg in corresponding Rx FIFO entry */
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_GAFLP1(offset, start),
			 RCANFD_GAFLP1_GAFLFDP(ridx));

	/* Disable ग_लिखो access to page */
	rcar_canfd_clear_bit(gpriv->base,
			     RCANFD_GAFLECTR, RCANFD_GAFLECTR_AFLDAE);
पूर्ण

अटल व्योम rcar_canfd_configure_rx(काष्ठा rcar_canfd_global *gpriv, u32 ch)
अणु
	/* Rx FIFO is used क्रम reception */
	u32 cfg;
	u16 rfdc, rfpls;

	/* Select Rx FIFO based on channel */
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	rfdc = 2;		/* b010 - 8 messages Rx FIFO depth */
	अगर (gpriv->fdmode)
		rfpls = 7;	/* b111 - Max 64 bytes payload */
	अन्यथा
		rfpls = 0;	/* b000 - Max 8 bytes payload */

	cfg = (RCANFD_RFCC_RFIM | RCANFD_RFCC_RFDC(rfdc) |
		RCANFD_RFCC_RFPLS(rfpls) | RCANFD_RFCC_RFIE);
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_RFCC(ridx), cfg);
पूर्ण

अटल व्योम rcar_canfd_configure_tx(काष्ठा rcar_canfd_global *gpriv, u32 ch)
अणु
	/* Tx/Rx(Common) FIFO configured in Tx mode is
	 * used क्रम transmission
	 *
	 * Each channel has 3 Common FIFO dedicated to them.
	 * Use the 1st (index 0) out of 3
	 */
	u32 cfg;
	u16 cfपंचांगl, cfm, cfdc, cfpls;

	cfपंचांगl = 0;		/* 0th buffer */
	cfm = 1;		/* b01 - Transmit mode */
	cfdc = 2;		/* b010 - 8 messages Tx FIFO depth */
	अगर (gpriv->fdmode)
		cfpls = 7;	/* b111 - Max 64 bytes payload */
	अन्यथा
		cfpls = 0;	/* b000 - Max 8 bytes payload */

	cfg = (RCANFD_CFCC_CFTML(cfपंचांगl) | RCANFD_CFCC_CFM(cfm) |
		RCANFD_CFCC_CFIM | RCANFD_CFCC_CFDC(cfdc) |
		RCANFD_CFCC_CFPLS(cfpls) | RCANFD_CFCC_CFTXIE);
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_CFCC(ch, RCANFD_CFFIFO_IDX), cfg);

	अगर (gpriv->fdmode)
		/* Clear FD mode specअगरic control/status रेजिस्टर */
		rcar_canfd_ग_लिखो(gpriv->base,
				 RCANFD_F_CFFDCSTS(ch, RCANFD_CFFIFO_IDX), 0);
पूर्ण

अटल व्योम rcar_canfd_enable_global_पूर्णांकerrupts(काष्ठा rcar_canfd_global *gpriv)
अणु
	u32 ctr;

	/* Clear any stray error पूर्णांकerrupt flags */
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_GERFL, 0);

	/* Global पूर्णांकerrupts setup */
	ctr = RCANFD_GCTR_MEIE;
	अगर (gpriv->fdmode)
		ctr |= RCANFD_GCTR_CFMPOFIE;

	rcar_canfd_set_bit(gpriv->base, RCANFD_GCTR, ctr);
पूर्ण

अटल व्योम rcar_canfd_disable_global_पूर्णांकerrupts(काष्ठा rcar_canfd_global
						 *gpriv)
अणु
	/* Disable all पूर्णांकerrupts */
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_GCTR, 0);

	/* Clear any stray error पूर्णांकerrupt flags */
	rcar_canfd_ग_लिखो(gpriv->base, RCANFD_GERFL, 0);
पूर्ण

अटल व्योम rcar_canfd_enable_channel_पूर्णांकerrupts(काष्ठा rcar_canfd_channel
						 *priv)
अणु
	u32 ctr, ch = priv->channel;

	/* Clear any stray error flags */
	rcar_canfd_ग_लिखो(priv->base, RCANFD_CERFL(ch), 0);

	/* Channel पूर्णांकerrupts setup */
	ctr = (RCANFD_CCTR_TAIE |
	       RCANFD_CCTR_ALIE | RCANFD_CCTR_BLIE |
	       RCANFD_CCTR_OLIE | RCANFD_CCTR_BORIE |
	       RCANFD_CCTR_BOEIE | RCANFD_CCTR_EPIE |
	       RCANFD_CCTR_EWIE | RCANFD_CCTR_BEIE);
	rcar_canfd_set_bit(priv->base, RCANFD_CCTR(ch), ctr);
पूर्ण

अटल व्योम rcar_canfd_disable_channel_पूर्णांकerrupts(काष्ठा rcar_canfd_channel
						  *priv)
अणु
	u32 ctr, ch = priv->channel;

	ctr = (RCANFD_CCTR_TAIE |
	       RCANFD_CCTR_ALIE | RCANFD_CCTR_BLIE |
	       RCANFD_CCTR_OLIE | RCANFD_CCTR_BORIE |
	       RCANFD_CCTR_BOEIE | RCANFD_CCTR_EPIE |
	       RCANFD_CCTR_EWIE | RCANFD_CCTR_BEIE);
	rcar_canfd_clear_bit(priv->base, RCANFD_CCTR(ch), ctr);

	/* Clear any stray error flags */
	rcar_canfd_ग_लिखो(priv->base, RCANFD_CERFL(ch), 0);
पूर्ण

अटल व्योम rcar_canfd_global_error(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	काष्ठा rcar_canfd_global *gpriv = priv->gpriv;
	काष्ठा net_device_stats *stats = &ndev->stats;
	u32 ch = priv->channel;
	u32 gerfl, sts;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	gerfl = rcar_canfd_पढ़ो(priv->base, RCANFD_GERFL);
	अगर ((gerfl & RCANFD_GERFL_EEF0) && (ch == 0)) अणु
		netdev_dbg(ndev, "Ch0: ECC Error flag\n");
		stats->tx_dropped++;
	पूर्ण
	अगर ((gerfl & RCANFD_GERFL_EEF1) && (ch == 1)) अणु
		netdev_dbg(ndev, "Ch1: ECC Error flag\n");
		stats->tx_dropped++;
	पूर्ण
	अगर (gerfl & RCANFD_GERFL_MES) अणु
		sts = rcar_canfd_पढ़ो(priv->base,
				      RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX));
		अगर (sts & RCANFD_CFSTS_CFMLT) अणु
			netdev_dbg(ndev, "Tx Message Lost flag\n");
			stats->tx_dropped++;
			rcar_canfd_ग_लिखो(priv->base,
					 RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX),
					 sts & ~RCANFD_CFSTS_CFMLT);
		पूर्ण

		sts = rcar_canfd_पढ़ो(priv->base, RCANFD_RFSTS(ridx));
		अगर (sts & RCANFD_RFSTS_RFMLT) अणु
			netdev_dbg(ndev, "Rx Message Lost flag\n");
			stats->rx_dropped++;
			rcar_canfd_ग_लिखो(priv->base, RCANFD_RFSTS(ridx),
					 sts & ~RCANFD_RFSTS_RFMLT);
		पूर्ण
	पूर्ण
	अगर (gpriv->fdmode && gerfl & RCANFD_GERFL_CMPOF) अणु
		/* Message Lost flag will be set क्रम respective channel
		 * when this condition happens with counters and flags
		 * alपढ़ोy updated.
		 */
		netdev_dbg(ndev, "global payload overflow interrupt\n");
	पूर्ण

	/* Clear all global error पूर्णांकerrupts. Only affected channels bits
	 * get cleared
	 */
	rcar_canfd_ग_लिखो(priv->base, RCANFD_GERFL, 0);
पूर्ण

अटल व्योम rcar_canfd_error(काष्ठा net_device *ndev, u32 cerfl,
			     u16 txerr, u16 rxerr)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 ch = priv->channel;

	netdev_dbg(ndev, "ch erfl %x txerr %u rxerr %u\n", cerfl, txerr, rxerr);

	/* Propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(ndev, &cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	/* Channel error पूर्णांकerrupts */
	अगर (cerfl & RCANFD_CERFL_BEF) अणु
		netdev_dbg(ndev, "Bus error\n");
		cf->can_id |= CAN_ERR_BUSERROR | CAN_ERR_PROT;
		cf->data[2] = CAN_ERR_PROT_UNSPEC;
		priv->can.can_stats.bus_error++;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_ADERR) अणु
		netdev_dbg(ndev, "ACK Delimiter Error\n");
		stats->tx_errors++;
		cf->data[3] |= CAN_ERR_PROT_LOC_ACK_DEL;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_B0ERR) अणु
		netdev_dbg(ndev, "Bit Error (dominant)\n");
		stats->tx_errors++;
		cf->data[2] |= CAN_ERR_PROT_BIT0;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_B1ERR) अणु
		netdev_dbg(ndev, "Bit Error (recessive)\n");
		stats->tx_errors++;
		cf->data[2] |= CAN_ERR_PROT_BIT1;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_CERR) अणु
		netdev_dbg(ndev, "CRC Error\n");
		stats->rx_errors++;
		cf->data[3] |= CAN_ERR_PROT_LOC_CRC_SEQ;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_AERR) अणु
		netdev_dbg(ndev, "ACK Error\n");
		stats->tx_errors++;
		cf->can_id |= CAN_ERR_ACK;
		cf->data[3] |= CAN_ERR_PROT_LOC_ACK;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_FERR) अणु
		netdev_dbg(ndev, "Form Error\n");
		stats->rx_errors++;
		cf->data[2] |= CAN_ERR_PROT_FORM;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_SERR) अणु
		netdev_dbg(ndev, "Stuff Error\n");
		stats->rx_errors++;
		cf->data[2] |= CAN_ERR_PROT_STUFF;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_ALF) अणु
		netdev_dbg(ndev, "Arbitration lost Error\n");
		priv->can.can_stats.arbitration_lost++;
		cf->can_id |= CAN_ERR_LOSTARB;
		cf->data[0] |= CAN_ERR_LOSTARB_UNSPEC;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_BLF) अणु
		netdev_dbg(ndev, "Bus Lock Error\n");
		stats->rx_errors++;
		cf->can_id |= CAN_ERR_BUSERROR;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_EWF) अणु
		netdev_dbg(ndev, "Error warning interrupt\n");
		priv->can.state = CAN_STATE_ERROR_WARNING;
		priv->can.can_stats.error_warning++;
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = txerr > rxerr ? CAN_ERR_CRTL_TX_WARNING :
			CAN_ERR_CRTL_RX_WARNING;
		cf->data[6] = txerr;
		cf->data[7] = rxerr;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_EPF) अणु
		netdev_dbg(ndev, "Error passive interrupt\n");
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		priv->can.can_stats.error_passive++;
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = txerr > rxerr ? CAN_ERR_CRTL_TX_PASSIVE :
			CAN_ERR_CRTL_RX_PASSIVE;
		cf->data[6] = txerr;
		cf->data[7] = rxerr;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_BOEF) अणु
		netdev_dbg(ndev, "Bus-off entry interrupt\n");
		rcar_canfd_tx_failure_cleanup(ndev);
		priv->can.state = CAN_STATE_BUS_OFF;
		priv->can.can_stats.bus_off++;
		can_bus_off(ndev);
		cf->can_id |= CAN_ERR_BUSOFF;
	पूर्ण
	अगर (cerfl & RCANFD_CERFL_OVLF) अणु
		netdev_dbg(ndev,
			   "Overload Frame Transmission error interrupt\n");
		stats->tx_errors++;
		cf->can_id |= CAN_ERR_PROT;
		cf->data[2] |= CAN_ERR_PROT_OVERLOAD;
	पूर्ण

	/* Clear channel error पूर्णांकerrupts that are handled */
	rcar_canfd_ग_लिखो(priv->base, RCANFD_CERFL(ch),
			 RCANFD_CERFL_ERR(~cerfl));
	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

अटल व्योम rcar_canfd_tx_करोne(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	u32 sts;
	अचिन्हित दीर्घ flags;
	u32 ch = priv->channel;

	करो अणु
		u8 unsent, sent;

		sent = priv->tx_tail % RCANFD_FIFO_DEPTH;
		stats->tx_packets++;
		stats->tx_bytes += priv->tx_len[sent];
		priv->tx_len[sent] = 0;
		can_get_echo_skb(ndev, sent, शून्य);

		spin_lock_irqsave(&priv->tx_lock, flags);
		priv->tx_tail++;
		sts = rcar_canfd_पढ़ो(priv->base,
				      RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX));
		unsent = RCANFD_CFSTS_CFMC(sts);

		/* Wake producer only when there is room */
		अगर (unsent != RCANFD_FIFO_DEPTH)
			netअगर_wake_queue(ndev);

		अगर (priv->tx_head - priv->tx_tail <= unsent) अणु
			spin_unlock_irqrestore(&priv->tx_lock, flags);
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&priv->tx_lock, flags);

	पूर्ण जबतक (1);

	/* Clear पूर्णांकerrupt */
	rcar_canfd_ग_लिखो(priv->base, RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX),
			 sts & ~RCANFD_CFSTS_CFTXIF);
	can_led_event(ndev, CAN_LED_EVENT_TX);
पूर्ण

अटल irqवापस_t rcar_canfd_global_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rcar_canfd_global *gpriv = dev_id;
	काष्ठा net_device *ndev;
	काष्ठा rcar_canfd_channel *priv;
	u32 sts, gerfl;
	u32 ch, ridx;

	/* Global error पूर्णांकerrupts still indicate a condition specअगरic
	 * to a channel. RxFIFO पूर्णांकerrupt is a global पूर्णांकerrupt.
	 */
	क्रम_each_set_bit(ch, &gpriv->channels_mask, RCANFD_NUM_CHANNELS) अणु
		priv = gpriv->ch[ch];
		ndev = priv->ndev;
		ridx = ch + RCANFD_RFFIFO_IDX;

		/* Global error पूर्णांकerrupts */
		gerfl = rcar_canfd_पढ़ो(priv->base, RCANFD_GERFL);
		अगर (unlikely(RCANFD_GERFL_ERR(gpriv, gerfl)))
			rcar_canfd_global_error(ndev);

		/* Handle Rx पूर्णांकerrupts */
		sts = rcar_canfd_पढ़ो(priv->base, RCANFD_RFSTS(ridx));
		अगर (likely(sts & RCANFD_RFSTS_RFIF)) अणु
			अगर (napi_schedule_prep(&priv->napi)) अणु
				/* Disable Rx FIFO पूर्णांकerrupts */
				rcar_canfd_clear_bit(priv->base,
						     RCANFD_RFCC(ridx),
						     RCANFD_RFCC_RFIE);
				__napi_schedule(&priv->napi);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rcar_canfd_state_change(काष्ठा net_device *ndev,
				    u16 txerr, u16 rxerr)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	क्रमागत can_state rx_state, tx_state, state = priv->can.state;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	/* Handle transition from error to normal states */
	अगर (txerr < 96 && rxerr < 96)
		state = CAN_STATE_ERROR_ACTIVE;
	अन्यथा अगर (txerr < 128 && rxerr < 128)
		state = CAN_STATE_ERROR_WARNING;

	अगर (state != priv->can.state) अणु
		netdev_dbg(ndev, "state: new %d, old %d: txerr %u, rxerr %u\n",
			   state, priv->can.state, txerr, rxerr);
		skb = alloc_can_err_skb(ndev, &cf);
		अगर (!skb) अणु
			stats->rx_dropped++;
			वापस;
		पूर्ण
		tx_state = txerr >= rxerr ? state : 0;
		rx_state = txerr <= rxerr ? state : 0;

		can_change_state(ndev, cf, tx_state, rx_state);
		stats->rx_packets++;
		stats->rx_bytes += cf->len;
		netअगर_rx(skb);
	पूर्ण
पूर्ण

अटल irqवापस_t rcar_canfd_channel_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rcar_canfd_global *gpriv = dev_id;
	काष्ठा net_device *ndev;
	काष्ठा rcar_canfd_channel *priv;
	u32 sts, ch, cerfl;
	u16 txerr, rxerr;

	/* Common FIFO is a per channel resource */
	क्रम_each_set_bit(ch, &gpriv->channels_mask, RCANFD_NUM_CHANNELS) अणु
		priv = gpriv->ch[ch];
		ndev = priv->ndev;

		/* Channel error पूर्णांकerrupts */
		cerfl = rcar_canfd_पढ़ो(priv->base, RCANFD_CERFL(ch));
		sts = rcar_canfd_पढ़ो(priv->base, RCANFD_CSTS(ch));
		txerr = RCANFD_CSTS_TECCNT(sts);
		rxerr = RCANFD_CSTS_RECCNT(sts);
		अगर (unlikely(RCANFD_CERFL_ERR(cerfl)))
			rcar_canfd_error(ndev, cerfl, txerr, rxerr);

		/* Handle state change to lower states */
		अगर (unlikely((priv->can.state != CAN_STATE_ERROR_ACTIVE) &&
			     (priv->can.state != CAN_STATE_BUS_OFF)))
			rcar_canfd_state_change(ndev, txerr, rxerr);

		/* Handle Tx पूर्णांकerrupts */
		sts = rcar_canfd_पढ़ो(priv->base,
				      RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX));
		अगर (likely(sts & RCANFD_CFSTS_CFTXIF))
			rcar_canfd_tx_करोne(ndev);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rcar_canfd_set_bittiming(काष्ठा net_device *dev)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(dev);
	स्थिर काष्ठा can_bittiming *bt = &priv->can.bittiming;
	स्थिर काष्ठा can_bittiming *dbt = &priv->can.data_bittiming;
	u16 brp, sjw, tseg1, tseg2;
	u32 cfg;
	u32 ch = priv->channel;

	/* Nominal bit timing settings */
	brp = bt->brp - 1;
	sjw = bt->sjw - 1;
	tseg1 = bt->prop_seg + bt->phase_seg1 - 1;
	tseg2 = bt->phase_seg2 - 1;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		/* CAN FD only mode */
		cfg = (RCANFD_NCFG_NTSEG1(tseg1) | RCANFD_NCFG_NBRP(brp) |
		       RCANFD_NCFG_NSJW(sjw) | RCANFD_NCFG_NTSEG2(tseg2));

		rcar_canfd_ग_लिखो(priv->base, RCANFD_CCFG(ch), cfg);
		netdev_dbg(priv->ndev, "nrate: brp %u, sjw %u, tseg1 %u, tseg2 %u\n",
			   brp, sjw, tseg1, tseg2);

		/* Data bit timing settings */
		brp = dbt->brp - 1;
		sjw = dbt->sjw - 1;
		tseg1 = dbt->prop_seg + dbt->phase_seg1 - 1;
		tseg2 = dbt->phase_seg2 - 1;

		cfg = (RCANFD_DCFG_DTSEG1(tseg1) | RCANFD_DCFG_DBRP(brp) |
		       RCANFD_DCFG_DSJW(sjw) | RCANFD_DCFG_DTSEG2(tseg2));

		rcar_canfd_ग_लिखो(priv->base, RCANFD_F_DCFG(ch), cfg);
		netdev_dbg(priv->ndev, "drate: brp %u, sjw %u, tseg1 %u, tseg2 %u\n",
			   brp, sjw, tseg1, tseg2);
	पूर्ण अन्यथा अणु
		/* Classical CAN only mode */
		cfg = (RCANFD_CFG_TSEG1(tseg1) | RCANFD_CFG_BRP(brp) |
			RCANFD_CFG_SJW(sjw) | RCANFD_CFG_TSEG2(tseg2));

		rcar_canfd_ग_लिखो(priv->base, RCANFD_CCFG(ch), cfg);
		netdev_dbg(priv->ndev,
			   "rate: brp %u, sjw %u, tseg1 %u, tseg2 %u\n",
			   brp, sjw, tseg1, tseg2);
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_canfd_start(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	पूर्णांक err = -EOPNOTSUPP;
	u32 sts, ch = priv->channel;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	rcar_canfd_set_bittiming(ndev);

	rcar_canfd_enable_channel_पूर्णांकerrupts(priv);

	/* Set channel to Operational mode */
	rcar_canfd_update_bit(priv->base, RCANFD_CCTR(ch),
			      RCANFD_CCTR_CHMDC_MASK, RCANFD_CCTR_CHDMC_COPM);

	/* Verअगरy channel mode change */
	err = पढ़ोl_poll_समयout((priv->base + RCANFD_CSTS(ch)), sts,
				 (sts & RCANFD_CSTS_COMSTS), 2, 500000);
	अगर (err) अणु
		netdev_err(ndev, "channel %u communication state failed\n", ch);
		जाओ fail_mode_change;
	पूर्ण

	/* Enable Common & Rx FIFO */
	rcar_canfd_set_bit(priv->base, RCANFD_CFCC(ch, RCANFD_CFFIFO_IDX),
			   RCANFD_CFCC_CFE);
	rcar_canfd_set_bit(priv->base, RCANFD_RFCC(ridx), RCANFD_RFCC_RFE);

	priv->can.state = CAN_STATE_ERROR_ACTIVE;
	वापस 0;

fail_mode_change:
	rcar_canfd_disable_channel_पूर्णांकerrupts(priv);
	वापस err;
पूर्ण

अटल पूर्णांक rcar_canfd_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	काष्ठा rcar_canfd_global *gpriv = priv->gpriv;
	पूर्णांक err;

	/* Peripheral घड़ी is alपढ़ोy enabled in probe */
	err = clk_prepare_enable(gpriv->can_clk);
	अगर (err) अणु
		netdev_err(ndev, "failed to enable CAN clock, error %d\n", err);
		जाओ out_घड़ी;
	पूर्ण

	err = खोलो_candev(ndev);
	अगर (err) अणु
		netdev_err(ndev, "open_candev() failed, error %d\n", err);
		जाओ out_can_घड़ी;
	पूर्ण

	napi_enable(&priv->napi);
	err = rcar_canfd_start(ndev);
	अगर (err)
		जाओ out_बंद;
	netअगर_start_queue(ndev);
	can_led_event(ndev, CAN_LED_EVENT_OPEN);
	वापस 0;
out_बंद:
	napi_disable(&priv->napi);
	बंद_candev(ndev);
out_can_घड़ी:
	clk_disable_unprepare(gpriv->can_clk);
out_घड़ी:
	वापस err;
पूर्ण

अटल व्योम rcar_canfd_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	पूर्णांक err;
	u32 sts, ch = priv->channel;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	/* Transition to channel reset mode  */
	rcar_canfd_update_bit(priv->base, RCANFD_CCTR(ch),
			      RCANFD_CCTR_CHMDC_MASK, RCANFD_CCTR_CHDMC_CRESET);

	/* Check Channel reset mode */
	err = पढ़ोl_poll_समयout((priv->base + RCANFD_CSTS(ch)), sts,
				 (sts & RCANFD_CSTS_CRSTSTS), 2, 500000);
	अगर (err)
		netdev_err(ndev, "channel %u reset failed\n", ch);

	rcar_canfd_disable_channel_पूर्णांकerrupts(priv);

	/* Disable Common & Rx FIFO */
	rcar_canfd_clear_bit(priv->base, RCANFD_CFCC(ch, RCANFD_CFFIFO_IDX),
			     RCANFD_CFCC_CFE);
	rcar_canfd_clear_bit(priv->base, RCANFD_RFCC(ridx), RCANFD_RFCC_RFE);

	/* Set the state as STOPPED */
	priv->can.state = CAN_STATE_STOPPED;
पूर्ण

अटल पूर्णांक rcar_canfd_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	काष्ठा rcar_canfd_global *gpriv = priv->gpriv;

	netअगर_stop_queue(ndev);
	rcar_canfd_stop(ndev);
	napi_disable(&priv->napi);
	clk_disable_unprepare(gpriv->can_clk);
	बंद_candev(ndev);
	can_led_event(ndev, CAN_LED_EVENT_STOP);
	वापस 0;
पूर्ण

अटल netdev_tx_t rcar_canfd_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(ndev);
	काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)skb->data;
	u32 sts = 0, id, dlc;
	अचिन्हित दीर्घ flags;
	u32 ch = priv->channel;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		id = cf->can_id & CAN_EFF_MASK;
		id |= RCANFD_CFID_CFIDE;
	पूर्ण अन्यथा अणु
		id = cf->can_id & CAN_SFF_MASK;
	पूर्ण

	अगर (cf->can_id & CAN_RTR_FLAG)
		id |= RCANFD_CFID_CFRTR;

	dlc = RCANFD_CFPTR_CFDLC(can_fd_len2dlc(cf->len));

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		rcar_canfd_ग_लिखो(priv->base,
				 RCANFD_F_CFID(ch, RCANFD_CFFIFO_IDX), id);
		rcar_canfd_ग_लिखो(priv->base,
				 RCANFD_F_CFPTR(ch, RCANFD_CFFIFO_IDX), dlc);

		अगर (can_is_canfd_skb(skb)) अणु
			/* CAN FD frame क्रमmat */
			sts |= RCANFD_CFFDCSTS_CFFDF;
			अगर (cf->flags & CANFD_BRS)
				sts |= RCANFD_CFFDCSTS_CFBRS;

			अगर (priv->can.state == CAN_STATE_ERROR_PASSIVE)
				sts |= RCANFD_CFFDCSTS_CFESI;
		पूर्ण

		rcar_canfd_ग_लिखो(priv->base,
				 RCANFD_F_CFFDCSTS(ch, RCANFD_CFFIFO_IDX), sts);

		rcar_canfd_put_data(priv, cf,
				    RCANFD_F_CFDF(ch, RCANFD_CFFIFO_IDX, 0));
	पूर्ण अन्यथा अणु
		rcar_canfd_ग_लिखो(priv->base,
				 RCANFD_C_CFID(ch, RCANFD_CFFIFO_IDX), id);
		rcar_canfd_ग_लिखो(priv->base,
				 RCANFD_C_CFPTR(ch, RCANFD_CFFIFO_IDX), dlc);
		rcar_canfd_put_data(priv, cf,
				    RCANFD_C_CFDF(ch, RCANFD_CFFIFO_IDX, 0));
	पूर्ण

	priv->tx_len[priv->tx_head % RCANFD_FIFO_DEPTH] = cf->len;
	can_put_echo_skb(skb, ndev, priv->tx_head % RCANFD_FIFO_DEPTH, 0);

	spin_lock_irqsave(&priv->tx_lock, flags);
	priv->tx_head++;

	/* Stop the queue अगर we've filled all FIFO entries */
	अगर (priv->tx_head - priv->tx_tail >= RCANFD_FIFO_DEPTH)
		netअगर_stop_queue(ndev);

	/* Start Tx: Write 0xff to CFPC to increment the CPU-side
	 * poपूर्णांकer क्रम the Common FIFO
	 */
	rcar_canfd_ग_लिखो(priv->base,
			 RCANFD_CFPCTR(ch, RCANFD_CFFIFO_IDX), 0xff);

	spin_unlock_irqrestore(&priv->tx_lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम rcar_canfd_rx_pkt(काष्ठा rcar_canfd_channel *priv)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	काष्ठा canfd_frame *cf;
	काष्ठा sk_buff *skb;
	u32 sts = 0, id, dlc;
	u32 ch = priv->channel;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		id = rcar_canfd_पढ़ो(priv->base, RCANFD_F_RFID(ridx));
		dlc = rcar_canfd_पढ़ो(priv->base, RCANFD_F_RFPTR(ridx));

		sts = rcar_canfd_पढ़ो(priv->base, RCANFD_F_RFFDSTS(ridx));
		अगर (sts & RCANFD_RFFDSTS_RFFDF)
			skb = alloc_canfd_skb(priv->ndev, &cf);
		अन्यथा
			skb = alloc_can_skb(priv->ndev,
					    (काष्ठा can_frame **)&cf);
	पूर्ण अन्यथा अणु
		id = rcar_canfd_पढ़ो(priv->base, RCANFD_C_RFID(ridx));
		dlc = rcar_canfd_पढ़ो(priv->base, RCANFD_C_RFPTR(ridx));
		skb = alloc_can_skb(priv->ndev, (काष्ठा can_frame **)&cf);
	पूर्ण

	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	अगर (id & RCANFD_RFID_RFIDE)
		cf->can_id = (id & CAN_EFF_MASK) | CAN_EFF_FLAG;
	अन्यथा
		cf->can_id = id & CAN_SFF_MASK;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		अगर (sts & RCANFD_RFFDSTS_RFFDF)
			cf->len = can_fd_dlc2len(RCANFD_RFPTR_RFDLC(dlc));
		अन्यथा
			cf->len = can_cc_dlc2len(RCANFD_RFPTR_RFDLC(dlc));

		अगर (sts & RCANFD_RFFDSTS_RFESI) अणु
			cf->flags |= CANFD_ESI;
			netdev_dbg(priv->ndev, "ESI Error\n");
		पूर्ण

		अगर (!(sts & RCANFD_RFFDSTS_RFFDF) && (id & RCANFD_RFID_RFRTR)) अणु
			cf->can_id |= CAN_RTR_FLAG;
		पूर्ण अन्यथा अणु
			अगर (sts & RCANFD_RFFDSTS_RFBRS)
				cf->flags |= CANFD_BRS;

			rcar_canfd_get_data(priv, cf, RCANFD_F_RFDF(ridx, 0));
		पूर्ण
	पूर्ण अन्यथा अणु
		cf->len = can_cc_dlc2len(RCANFD_RFPTR_RFDLC(dlc));
		अगर (id & RCANFD_RFID_RFRTR)
			cf->can_id |= CAN_RTR_FLAG;
		अन्यथा
			rcar_canfd_get_data(priv, cf, RCANFD_C_RFDF(ridx, 0));
	पूर्ण

	/* Write 0xff to RFPC to increment the CPU-side
	 * poपूर्णांकer of the Rx FIFO
	 */
	rcar_canfd_ग_लिखो(priv->base, RCANFD_RFPCTR(ridx), 0xff);

	can_led_event(priv->ndev, CAN_LED_EVENT_RX);

	stats->rx_bytes += cf->len;
	stats->rx_packets++;
	netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक rcar_canfd_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा rcar_canfd_channel *priv =
		container_of(napi, काष्ठा rcar_canfd_channel, napi);
	पूर्णांक num_pkts;
	u32 sts;
	u32 ch = priv->channel;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	क्रम (num_pkts = 0; num_pkts < quota; num_pkts++) अणु
		sts = rcar_canfd_पढ़ो(priv->base, RCANFD_RFSTS(ridx));
		/* Check FIFO empty condition */
		अगर (sts & RCANFD_RFSTS_RFEMP)
			अवरोध;

		rcar_canfd_rx_pkt(priv);

		/* Clear पूर्णांकerrupt bit */
		अगर (sts & RCANFD_RFSTS_RFIF)
			rcar_canfd_ग_लिखो(priv->base, RCANFD_RFSTS(ridx),
					 sts & ~RCANFD_RFSTS_RFIF);
	पूर्ण

	/* All packets processed */
	अगर (num_pkts < quota) अणु
		अगर (napi_complete_करोne(napi, num_pkts)) अणु
			/* Enable Rx FIFO पूर्णांकerrupts */
			rcar_canfd_set_bit(priv->base, RCANFD_RFCC(ridx),
					   RCANFD_RFCC_RFIE);
		पूर्ण
	पूर्ण
	वापस num_pkts;
पूर्ण

अटल पूर्णांक rcar_canfd_करो_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	पूर्णांक err;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		err = rcar_canfd_start(ndev);
		अगर (err)
			वापस err;
		netअगर_wake_queue(ndev);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_canfd_get_berr_counter(स्थिर काष्ठा net_device *dev,
				       काष्ठा can_berr_counter *bec)
अणु
	काष्ठा rcar_canfd_channel *priv = netdev_priv(dev);
	u32 val, ch = priv->channel;

	/* Peripheral घड़ी is alपढ़ोy enabled in probe */
	val = rcar_canfd_पढ़ो(priv->base, RCANFD_CSTS(ch));
	bec->txerr = RCANFD_CSTS_TECCNT(val);
	bec->rxerr = RCANFD_CSTS_RECCNT(val);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops rcar_canfd_netdev_ops = अणु
	.nकरो_खोलो = rcar_canfd_खोलो,
	.nकरो_stop = rcar_canfd_बंद,
	.nकरो_start_xmit = rcar_canfd_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल पूर्णांक rcar_canfd_channel_probe(काष्ठा rcar_canfd_global *gpriv, u32 ch,
				    u32 fcan_freq)
अणु
	काष्ठा platक्रमm_device *pdev = gpriv->pdev;
	काष्ठा rcar_canfd_channel *priv;
	काष्ठा net_device *ndev;
	पूर्णांक err = -ENODEV;

	ndev = alloc_candev(माप(*priv), RCANFD_FIFO_DEPTH);
	अगर (!ndev) अणु
		dev_err(&pdev->dev, "alloc_candev() failed\n");
		err = -ENOMEM;
		जाओ fail;
	पूर्ण
	priv = netdev_priv(ndev);

	ndev->netdev_ops = &rcar_canfd_netdev_ops;
	ndev->flags |= IFF_ECHO;
	priv->ndev = ndev;
	priv->base = gpriv->base;
	priv->channel = ch;
	priv->can.घड़ी.freq = fcan_freq;
	dev_info(&pdev->dev, "can_clk rate is %u\n", priv->can.घड़ी.freq);

	अगर (gpriv->fdmode) अणु
		priv->can.bittiming_स्थिर = &rcar_canfd_nom_bittiming_स्थिर;
		priv->can.data_bittiming_स्थिर =
			&rcar_canfd_data_bittiming_स्थिर;

		/* Controller starts in CAN FD only mode */
		can_set_अटल_ctrlmode(ndev, CAN_CTRLMODE_FD);
		priv->can.ctrlmode_supported = CAN_CTRLMODE_BERR_REPORTING;
	पूर्ण अन्यथा अणु
		/* Controller starts in Classical CAN only mode */
		priv->can.bittiming_स्थिर = &rcar_canfd_bittiming_स्थिर;
		priv->can.ctrlmode_supported = CAN_CTRLMODE_BERR_REPORTING;
	पूर्ण

	priv->can.करो_set_mode = rcar_canfd_करो_set_mode;
	priv->can.करो_get_berr_counter = rcar_canfd_get_berr_counter;
	priv->gpriv = gpriv;
	SET_NETDEV_DEV(ndev, &pdev->dev);

	netअगर_napi_add(ndev, &priv->napi, rcar_canfd_rx_poll,
		       RCANFD_NAPI_WEIGHT);
	err = रेजिस्टर_candev(ndev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"register_candev() failed, error %d\n", err);
		जाओ fail_candev;
	पूर्ण
	spin_lock_init(&priv->tx_lock);
	devm_can_led_init(ndev);
	gpriv->ch[priv->channel] = priv;
	dev_info(&pdev->dev, "device registered (channel %u)\n", priv->channel);
	वापस 0;

fail_candev:
	netअगर_napi_del(&priv->napi);
	मुक्त_candev(ndev);
fail:
	वापस err;
पूर्ण

अटल व्योम rcar_canfd_channel_हटाओ(काष्ठा rcar_canfd_global *gpriv, u32 ch)
अणु
	काष्ठा rcar_canfd_channel *priv = gpriv->ch[ch];

	अगर (priv) अणु
		unरेजिस्टर_candev(priv->ndev);
		netअगर_napi_del(&priv->napi);
		मुक्त_candev(priv->ndev);
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_canfd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *addr;
	u32 sts, ch, fcan_freq;
	काष्ठा rcar_canfd_global *gpriv;
	काष्ठा device_node *of_child;
	अचिन्हित दीर्घ channels_mask = 0;
	पूर्णांक err, ch_irq, g_irq;
	bool fdmode = true;			/* CAN FD only mode - शेष */

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "renesas,no-can-fd"))
		fdmode = false;			/* Classical CAN only mode */

	of_child = of_get_child_by_name(pdev->dev.of_node, "channel0");
	अगर (of_child && of_device_is_available(of_child))
		channels_mask |= BIT(0);	/* Channel 0 */

	of_child = of_get_child_by_name(pdev->dev.of_node, "channel1");
	अगर (of_child && of_device_is_available(of_child))
		channels_mask |= BIT(1);	/* Channel 1 */

	ch_irq = platक्रमm_get_irq(pdev, 0);
	अगर (ch_irq < 0) अणु
		err = ch_irq;
		जाओ fail_dev;
	पूर्ण

	g_irq = platक्रमm_get_irq(pdev, 1);
	अगर (g_irq < 0) अणु
		err = g_irq;
		जाओ fail_dev;
	पूर्ण

	/* Global controller context */
	gpriv = devm_kzalloc(&pdev->dev, माप(*gpriv), GFP_KERNEL);
	अगर (!gpriv) अणु
		err = -ENOMEM;
		जाओ fail_dev;
	पूर्ण
	gpriv->pdev = pdev;
	gpriv->channels_mask = channels_mask;
	gpriv->fdmode = fdmode;

	/* Peripheral घड़ी */
	gpriv->clkp = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(gpriv->clkp)) अणु
		err = PTR_ERR(gpriv->clkp);
		dev_err(&pdev->dev, "cannot get peripheral clock, error %d\n",
			err);
		जाओ fail_dev;
	पूर्ण

	/* fCAN घड़ी: Pick External घड़ी. If not available fallback to
	 * CANFD घड़ी
	 */
	gpriv->can_clk = devm_clk_get(&pdev->dev, "can_clk");
	अगर (IS_ERR(gpriv->can_clk) || (clk_get_rate(gpriv->can_clk) == 0)) अणु
		gpriv->can_clk = devm_clk_get(&pdev->dev, "canfd");
		अगर (IS_ERR(gpriv->can_clk)) अणु
			err = PTR_ERR(gpriv->can_clk);
			dev_err(&pdev->dev,
				"cannot get canfd clock, error %d\n", err);
			जाओ fail_dev;
		पूर्ण
		gpriv->fcan = RCANFD_CANFDCLK;

	पूर्ण अन्यथा अणु
		gpriv->fcan = RCANFD_EXTCLK;
	पूर्ण
	fcan_freq = clk_get_rate(gpriv->can_clk);

	अगर (gpriv->fcan == RCANFD_CANFDCLK)
		/* CANFD घड़ी is further भागided by (1/2) within the IP */
		fcan_freq /= 2;

	addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(addr)) अणु
		err = PTR_ERR(addr);
		जाओ fail_dev;
	पूर्ण
	gpriv->base = addr;

	/* Request IRQ that's common क्रम both channels */
	err = devm_request_irq(&pdev->dev, ch_irq,
			       rcar_canfd_channel_पूर्णांकerrupt, 0,
			       "canfd.chn", gpriv);
	अगर (err) अणु
		dev_err(&pdev->dev, "devm_request_irq(%d) failed, error %d\n",
			ch_irq, err);
		जाओ fail_dev;
	पूर्ण
	err = devm_request_irq(&pdev->dev, g_irq,
			       rcar_canfd_global_पूर्णांकerrupt, 0,
			       "canfd.gbl", gpriv);
	अगर (err) अणु
		dev_err(&pdev->dev, "devm_request_irq(%d) failed, error %d\n",
			g_irq, err);
		जाओ fail_dev;
	पूर्ण

	/* Enable peripheral घड़ी क्रम रेजिस्टर access */
	err = clk_prepare_enable(gpriv->clkp);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"failed to enable peripheral clock, error %d\n", err);
		जाओ fail_dev;
	पूर्ण

	err = rcar_canfd_reset_controller(gpriv);
	अगर (err) अणु
		dev_err(&pdev->dev, "reset controller failed\n");
		जाओ fail_clk;
	पूर्ण

	/* Controller in Global reset & Channel reset mode */
	rcar_canfd_configure_controller(gpriv);

	/* Configure per channel attributes */
	क्रम_each_set_bit(ch, &gpriv->channels_mask, RCANFD_NUM_CHANNELS) अणु
		/* Configure Channel's Rx fअगरo */
		rcar_canfd_configure_rx(gpriv, ch);

		/* Configure Channel's Tx (Common) fअगरo */
		rcar_canfd_configure_tx(gpriv, ch);

		/* Configure receive rules */
		rcar_canfd_configure_afl_rules(gpriv, ch);
	पूर्ण

	/* Configure common पूर्णांकerrupts */
	rcar_canfd_enable_global_पूर्णांकerrupts(gpriv);

	/* Start Global operation mode */
	rcar_canfd_update_bit(gpriv->base, RCANFD_GCTR, RCANFD_GCTR_GMDC_MASK,
			      RCANFD_GCTR_GMDC_GOPM);

	/* Verअगरy mode change */
	err = पढ़ोl_poll_समयout((gpriv->base + RCANFD_GSTS), sts,
				 !(sts & RCANFD_GSTS_GNOPM), 2, 500000);
	अगर (err) अणु
		dev_err(&pdev->dev, "global operational mode failed\n");
		जाओ fail_mode;
	पूर्ण

	क्रम_each_set_bit(ch, &gpriv->channels_mask, RCANFD_NUM_CHANNELS) अणु
		err = rcar_canfd_channel_probe(gpriv, ch, fcan_freq);
		अगर (err)
			जाओ fail_channel;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gpriv);
	dev_info(&pdev->dev, "global operational state (clk %d, fdmode %d)\n",
		 gpriv->fcan, gpriv->fdmode);
	वापस 0;

fail_channel:
	क्रम_each_set_bit(ch, &gpriv->channels_mask, RCANFD_NUM_CHANNELS)
		rcar_canfd_channel_हटाओ(gpriv, ch);
fail_mode:
	rcar_canfd_disable_global_पूर्णांकerrupts(gpriv);
fail_clk:
	clk_disable_unprepare(gpriv->clkp);
fail_dev:
	वापस err;
पूर्ण

अटल पूर्णांक rcar_canfd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_canfd_global *gpriv = platक्रमm_get_drvdata(pdev);
	u32 ch;

	rcar_canfd_reset_controller(gpriv);
	rcar_canfd_disable_global_पूर्णांकerrupts(gpriv);

	क्रम_each_set_bit(ch, &gpriv->channels_mask, RCANFD_NUM_CHANNELS) अणु
		rcar_canfd_disable_channel_पूर्णांकerrupts(gpriv->ch[ch]);
		rcar_canfd_channel_हटाओ(gpriv, ch);
	पूर्ण

	/* Enter global sleep mode */
	rcar_canfd_set_bit(gpriv->base, RCANFD_GCTR, RCANFD_GCTR_GSLPR);
	clk_disable_unprepare(gpriv->clkp);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rcar_canfd_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rcar_canfd_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rcar_canfd_pm_ops, rcar_canfd_suspend,
			 rcar_canfd_resume);

अटल स्थिर काष्ठा of_device_id rcar_canfd_of_table[] = अणु
	अणु .compatible = "renesas,rcar-gen3-canfd" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rcar_canfd_of_table);

अटल काष्ठा platक्रमm_driver rcar_canfd_driver = अणु
	.driver = अणु
		.name = RCANFD_DRV_NAME,
		.of_match_table = of_match_ptr(rcar_canfd_of_table),
		.pm = &rcar_canfd_pm_ops,
	पूर्ण,
	.probe = rcar_canfd_probe,
	.हटाओ = rcar_canfd_हटाओ,
पूर्ण;

module_platक्रमm_driver(rcar_canfd_driver);

MODULE_AUTHOR("Ramesh Shanmugasundaram <ramesh.shanmugasundaram@bp.renesas.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CAN FD driver for Renesas R-Car SoC");
MODULE_ALIAS("platform:" RCANFD_DRV_NAME);
