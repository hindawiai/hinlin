<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Octeon HCD hardware रेजिस्टर definitions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Some parts of the code were originally released under BSD license:
 *
 * Copyright (c) 2003-2010 Cavium Networks (support@cavium.com). All rights
 * reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary क्रमm must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the करोcumentation and/or other materials provided
 *     with the distribution.
 *
 *   * Neither the name of Cavium Networks nor the names of
 *     its contributors may be used to enकरोrse or promote products
 *     derived from this software without specअगरic prior written
 *     permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its associated
 * regulations, and may be subject to export or import regulations in other
 * countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM NETWORKS MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION
 * OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 */

#अगर_अघोषित __OCTEON_HCD_H__
#घोषणा __OCTEON_HCD_H__

#समावेश <यंत्र/bitfield.h>

#घोषणा CVMX_USBCXBASE 0x00016F0010000000ull
#घोषणा CVMX_USBCXREG1(reg, bid) \
	(CVMX_ADD_IO_SEG(CVMX_USBCXBASE | reg) + \
	 ((bid) & 1) * 0x100000000000ull)
#घोषणा CVMX_USBCXREG2(reg, bid, off) \
	(CVMX_ADD_IO_SEG(CVMX_USBCXBASE | reg) + \
	 (((off) & 7) + ((bid) & 1) * 0x8000000000ull) * 32)

#घोषणा CVMX_USBCX_GAHBCFG(bid)		CVMX_USBCXREG1(0x008, bid)
#घोषणा CVMX_USBCX_GHWCFG3(bid)		CVMX_USBCXREG1(0x04c, bid)
#घोषणा CVMX_USBCX_GINTMSK(bid)		CVMX_USBCXREG1(0x018, bid)
#घोषणा CVMX_USBCX_GINTSTS(bid)		CVMX_USBCXREG1(0x014, bid)
#घोषणा CVMX_USBCX_GNPTXFSIZ(bid)	CVMX_USBCXREG1(0x028, bid)
#घोषणा CVMX_USBCX_GNPTXSTS(bid)	CVMX_USBCXREG1(0x02c, bid)
#घोषणा CVMX_USBCX_GOTGCTL(bid)		CVMX_USBCXREG1(0x000, bid)
#घोषणा CVMX_USBCX_GRSTCTL(bid)		CVMX_USBCXREG1(0x010, bid)
#घोषणा CVMX_USBCX_GRXFSIZ(bid)		CVMX_USBCXREG1(0x024, bid)
#घोषणा CVMX_USBCX_GRXSTSPH(bid)	CVMX_USBCXREG1(0x020, bid)
#घोषणा CVMX_USBCX_GUSBCFG(bid)		CVMX_USBCXREG1(0x00c, bid)
#घोषणा CVMX_USBCX_HAINT(bid)		CVMX_USBCXREG1(0x414, bid)
#घोषणा CVMX_USBCX_HAINTMSK(bid)	CVMX_USBCXREG1(0x418, bid)
#घोषणा CVMX_USBCX_HCCHARX(off, bid)	CVMX_USBCXREG2(0x500, bid, off)
#घोषणा CVMX_USBCX_HCFG(bid)		CVMX_USBCXREG1(0x400, bid)
#घोषणा CVMX_USBCX_HCINTMSKX(off, bid)	CVMX_USBCXREG2(0x50c, bid, off)
#घोषणा CVMX_USBCX_HCINTX(off, bid)	CVMX_USBCXREG2(0x508, bid, off)
#घोषणा CVMX_USBCX_HCSPLTX(off, bid)	CVMX_USBCXREG2(0x504, bid, off)
#घोषणा CVMX_USBCX_HCTSIZX(off, bid)	CVMX_USBCXREG2(0x510, bid, off)
#घोषणा CVMX_USBCX_HFIR(bid)		CVMX_USBCXREG1(0x404, bid)
#घोषणा CVMX_USBCX_HFNUM(bid)		CVMX_USBCXREG1(0x408, bid)
#घोषणा CVMX_USBCX_HPRT(bid)		CVMX_USBCXREG1(0x440, bid)
#घोषणा CVMX_USBCX_HPTXFSIZ(bid)	CVMX_USBCXREG1(0x100, bid)
#घोषणा CVMX_USBCX_HPTXSTS(bid)		CVMX_USBCXREG1(0x410, bid)

#घोषणा CVMX_USBNXBID1(bid) (((bid) & 1) * 0x10000000ull)
#घोषणा CVMX_USBNXBID2(bid) (((bid) & 1) * 0x100000000000ull)

#घोषणा CVMX_USBNXREG1(reg, bid) \
	(CVMX_ADD_IO_SEG(0x0001180068000000ull | reg) + CVMX_USBNXBID1(bid))
#घोषणा CVMX_USBNXREG2(reg, bid) \
	(CVMX_ADD_IO_SEG(0x00016F0000000000ull | reg) + CVMX_USBNXBID2(bid))

#घोषणा CVMX_USBNX_CLK_CTL(bid)		CVMX_USBNXREG1(0x10, bid)
#घोषणा CVMX_USBNX_DMA0_INB_CHN0(bid)	CVMX_USBNXREG2(0x818, bid)
#घोषणा CVMX_USBNX_DMA0_OUTB_CHN0(bid)	CVMX_USBNXREG2(0x858, bid)
#घोषणा CVMX_USBNX_USBP_CTL_STATUS(bid)	CVMX_USBNXREG1(0x18, bid)

/**
 * cvmx_usbc#_gahbcfg
 *
 * Core AHB Configuration Register (GAHBCFG)
 *
 * This रेजिस्टर can be used to configure the core after घातer-on or a change in
 * mode of operation. This रेजिस्टर मुख्यly contains AHB प्रणाली-related
 * configuration parameters. The AHB is the processor पूर्णांकerface to the O2P USB
 * core. In general, software need not know about this पूर्णांकerface except to
 * program the values as specअगरied.
 *
 * The application must program this रेजिस्टर as part of the O2P USB core
 * initialization. Do not change this रेजिस्टर after the initial programming.
 */
जोड़ cvmx_usbcx_gahbcfg अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_gahbcfg_s
	 * @ptxfemplvl: Periodic TxFIFO Empty Level (PTxFEmpLvl)
	 *	Software should set this bit to 0x1.
	 *	Indicates when the Periodic TxFIFO Empty Interrupt bit in the
	 *	Core Interrupt रेजिस्टर (GINTSTS.PTxFEmp) is triggered. This
	 *	bit is used only in Slave mode.
	 *	* 1'b0: GINTSTS.PTxFEmp पूर्णांकerrupt indicates that the Periodic
	 *	TxFIFO is half empty
	 *	* 1'b1: GINTSTS.PTxFEmp पूर्णांकerrupt indicates that the Periodic
	 *	TxFIFO is completely empty
	 * @nptxfemplvl: Non-Periodic TxFIFO Empty Level (NPTxFEmpLvl)
	 *	Software should set this bit to 0x1.
	 *	Indicates when the Non-Periodic TxFIFO Empty Interrupt bit in
	 *	the Core Interrupt रेजिस्टर (GINTSTS.NPTxFEmp) is triggered.
	 *	This bit is used only in Slave mode.
	 *	* 1'b0: GINTSTS.NPTxFEmp पूर्णांकerrupt indicates that the Non-
	 *	Periodic TxFIFO is half empty
	 *	* 1'b1: GINTSTS.NPTxFEmp पूर्णांकerrupt indicates that the Non-
	 *	Periodic TxFIFO is completely empty
	 * @dmaen: DMA Enable (DMAEn)
	 *	* 1'b0: Core operates in Slave mode
	 *	* 1'b1: Core operates in a DMA mode
	 * @hbstlen: Burst Length/Type (HBstLen)
	 *	This field has not effect and should be left as 0x0.
	 * @glblपूर्णांकrmsk: Global Interrupt Mask (GlblIntrMsk)
	 *	Software should set this field to 0x1.
	 *	The application uses this bit to mask or unmask the पूर्णांकerrupt
	 *	line निश्चितion to itself. Irrespective of this bit's setting,
	 *	the पूर्णांकerrupt status रेजिस्टरs are updated by the core.
	 *	* 1'b0: Mask the पूर्णांकerrupt निश्चितion to the application.
	 *	* 1'b1: Unmask the पूर्णांकerrupt निश्चितion to the application.
	 */
	काष्ठा cvmx_usbcx_gahbcfg_s अणु
		__BITFIELD_FIELD(u32 reserved_9_31	: 23,
		__BITFIELD_FIELD(u32 ptxfemplvl		: 1,
		__BITFIELD_FIELD(u32 nptxfemplvl	: 1,
		__BITFIELD_FIELD(u32 reserved_6_6	: 1,
		__BITFIELD_FIELD(u32 dmaen		: 1,
		__BITFIELD_FIELD(u32 hbstlen		: 4,
		__BITFIELD_FIELD(u32 glblपूर्णांकrmsk	: 1,
		;)))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_ghwcfg3
 *
 * User HW Config3 Register (GHWCFG3)
 *
 * This रेजिस्टर contains the configuration options of the O2P USB core.
 */
जोड़ cvmx_usbcx_ghwcfg3 अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_ghwcfg3_s
	 * @dfअगरodepth: DFIFO Depth (DfअगरoDepth)
	 *	This value is in terms of 32-bit words.
	 *	* Minimum value is 32
	 *	* Maximum value is 32768
	 * @ahbphysync: AHB and PHY Synchronous (AhbPhySync)
	 *	Indicates whether AHB and PHY घड़ीs are synchronous to
	 *	each other.
	 *	* 1'b0: No
	 *	* 1'b1: Yes
	 *	This bit is tied to 1.
	 * @rsttype: Reset Style क्रम Clocked always Blocks in RTL (RstType)
	 *	* 1'b0: Asynchronous reset is used in the core
	 *	* 1'b1: Synchronous reset is used in the core
	 * @optfeature: Optional Features Removed (OptFeature)
	 *	Indicates whether the User ID रेजिस्टर, GPIO पूर्णांकerface ports,
	 *	and SOF toggle and counter ports were हटाओd क्रम gate count
	 *	optimization.
	 * @venकरोr_control_पूर्णांकerface_support: Venकरोr Control Interface Support
	 *	* 1'b0: Venकरोr Control Interface is not available on the core.
	 *	* 1'b1: Venकरोr Control Interface is available.
	 * @i2c_selection: I2C Selection
	 *	* 1'b0: I2C Interface is not available on the core.
	 *	* 1'b1: I2C Interface is available on the core.
	 * @otgen: OTG Function Enabled (OtgEn)
	 *	The application uses this bit to indicate the O2P USB core's
	 *	OTG capabilities.
	 *	* 1'b0: Not OTG capable
	 *	* 1'b1: OTG Capable
	 * @pktsizewidth: Width of Packet Size Counters (PktSizeWidth)
	 *	* 3'b000: 4 bits
	 *	* 3'b001: 5 bits
	 *	* 3'b010: 6 bits
	 *	* 3'b011: 7 bits
	 *	* 3'b100: 8 bits
	 *	* 3'b101: 9 bits
	 *	* 3'b110: 10 bits
	 *	* Others: Reserved
	 * @xfersizewidth: Width of Transfer Size Counters (XferSizeWidth)
	 *	* 4'b0000: 11 bits
	 *	* 4'b0001: 12 bits
	 *	- ...
	 *	* 4'b1000: 19 bits
	 *	* Others: Reserved
	 */
	काष्ठा cvmx_usbcx_ghwcfg3_s अणु
		__BITFIELD_FIELD(u32 dfअगरodepth				: 16,
		__BITFIELD_FIELD(u32 reserved_13_15			: 3,
		__BITFIELD_FIELD(u32 ahbphysync				: 1,
		__BITFIELD_FIELD(u32 rsttype				: 1,
		__BITFIELD_FIELD(u32 optfeature				: 1,
		__BITFIELD_FIELD(u32 venकरोr_control_पूर्णांकerface_support	: 1,
		__BITFIELD_FIELD(u32 i2c_selection			: 1,
		__BITFIELD_FIELD(u32 otgen				: 1,
		__BITFIELD_FIELD(u32 pktsizewidth			: 3,
		__BITFIELD_FIELD(u32 xfersizewidth			: 4,
		;))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_gपूर्णांकmsk
 *
 * Core Interrupt Mask Register (GINTMSK)
 *
 * This रेजिस्टर works with the Core Interrupt रेजिस्टर to पूर्णांकerrupt the
 * application. When an पूर्णांकerrupt bit is masked, the पूर्णांकerrupt associated with
 * that bit will not be generated. However, the Core Interrupt (GINTSTS)
 * रेजिस्टर bit corresponding to that पूर्णांकerrupt will still be set.
 * Mask पूर्णांकerrupt: 1'b0, Unmask interrupt: 1'b1
 */
जोड़ cvmx_usbcx_gपूर्णांकmsk अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_gपूर्णांकmsk_s
	 * @wkupपूर्णांकmsk: Resume/Remote Wakeup Detected Interrupt Mask
	 *	(WkUpIntMsk)
	 * @sessreqपूर्णांकmsk: Session Request/New Session Detected Interrupt Mask
	 *	(SessReqIntMsk)
	 * @disconnपूर्णांकmsk: Disconnect Detected Interrupt Mask (DisconnIntMsk)
	 * @conidstschngmsk: Connector ID Status Change Mask (ConIDStsChngMsk)
	 * @ptxfempmsk: Periodic TxFIFO Empty Mask (PTxFEmpMsk)
	 * @hchपूर्णांकmsk: Host Channels Interrupt Mask (HChIntMsk)
	 * @prtपूर्णांकmsk: Host Port Interrupt Mask (PrtIntMsk)
	 * @fetsuspmsk: Data Fetch Suspended Mask (FetSuspMsk)
	 * @incomplpmsk: Incomplete Periodic Transfer Mask (incomplPMsk)
	 *	Incomplete Isochronous OUT Transfer Mask
	 *	(incompISOOUTMsk)
	 * @incompisoinmsk: Incomplete Isochronous IN Transfer Mask
	 *		    (incompISOINMsk)
	 * @oepपूर्णांकmsk: OUT Endpoपूर्णांकs Interrupt Mask (OEPIntMsk)
	 * @inepपूर्णांकmsk: IN Endpoपूर्णांकs Interrupt Mask (INEPIntMsk)
	 * @epmismsk: Endpoपूर्णांक Mismatch Interrupt Mask (EPMisMsk)
	 * @eopfmsk: End of Periodic Frame Interrupt Mask (EOPFMsk)
	 * @isooutdropmsk: Isochronous OUT Packet Dropped Interrupt Mask
	 *	(ISOOutDropMsk)
	 * @क्रमागतकरोnemsk: Enumeration Done Mask (EnumDoneMsk)
	 * @usbrsपंचांगsk: USB Reset Mask (USBRstMsk)
	 * @usbsuspmsk: USB Suspend Mask (USBSuspMsk)
	 * @erlysuspmsk: Early Suspend Mask (ErlySuspMsk)
	 * @i2cपूर्णांक: I2C Interrupt Mask (I2CINT)
	 * @ulpickपूर्णांकmsk: ULPI Carkit Interrupt Mask (ULPICKINTMsk)
	 *	I2C Carkit Interrupt Mask (I2CCKINTMsk)
	 * @goutnakeffmsk: Global OUT NAK Effective Mask (GOUTNakEffMsk)
	 * @ginnakeffmsk: Global Non-Periodic IN NAK Effective Mask
	 *		  (GINNakEffMsk)
	 * @nptxfempmsk: Non-Periodic TxFIFO Empty Mask (NPTxFEmpMsk)
	 * @rxflvlmsk: Receive FIFO Non-Empty Mask (RxFLvlMsk)
	 * @sofmsk: Start of (micro)Frame Mask (SofMsk)
	 * @otgपूर्णांकmsk: OTG Interrupt Mask (OTGIntMsk)
	 * @modemismsk: Mode Mismatch Interrupt Mask (ModeMisMsk)
	 */
	काष्ठा cvmx_usbcx_gपूर्णांकmsk_s अणु
		__BITFIELD_FIELD(u32 wkupपूर्णांकmsk		: 1,
		__BITFIELD_FIELD(u32 sessreqपूर्णांकmsk	: 1,
		__BITFIELD_FIELD(u32 disconnपूर्णांकmsk	: 1,
		__BITFIELD_FIELD(u32 conidstschngmsk	: 1,
		__BITFIELD_FIELD(u32 reserved_27_27	: 1,
		__BITFIELD_FIELD(u32 ptxfempmsk		: 1,
		__BITFIELD_FIELD(u32 hchपूर्णांकmsk		: 1,
		__BITFIELD_FIELD(u32 prtपूर्णांकmsk		: 1,
		__BITFIELD_FIELD(u32 reserved_23_23	: 1,
		__BITFIELD_FIELD(u32 fetsuspmsk		: 1,
		__BITFIELD_FIELD(u32 incomplpmsk	: 1,
		__BITFIELD_FIELD(u32 incompisoinmsk	: 1,
		__BITFIELD_FIELD(u32 oepपूर्णांकmsk		: 1,
		__BITFIELD_FIELD(u32 inepपूर्णांकmsk		: 1,
		__BITFIELD_FIELD(u32 epmismsk		: 1,
		__BITFIELD_FIELD(u32 reserved_16_16	: 1,
		__BITFIELD_FIELD(u32 eopfmsk		: 1,
		__BITFIELD_FIELD(u32 isooutdropmsk	: 1,
		__BITFIELD_FIELD(u32 क्रमागतकरोnemsk	: 1,
		__BITFIELD_FIELD(u32 usbrsपंचांगsk		: 1,
		__BITFIELD_FIELD(u32 usbsuspmsk		: 1,
		__BITFIELD_FIELD(u32 erlysuspmsk	: 1,
		__BITFIELD_FIELD(u32 i2cपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 ulpickपूर्णांकmsk	: 1,
		__BITFIELD_FIELD(u32 goutnakeffmsk	: 1,
		__BITFIELD_FIELD(u32 ginnakeffmsk	: 1,
		__BITFIELD_FIELD(u32 nptxfempmsk	: 1,
		__BITFIELD_FIELD(u32 rxflvlmsk		: 1,
		__BITFIELD_FIELD(u32 sofmsk		: 1,
		__BITFIELD_FIELD(u32 otgपूर्णांकmsk		: 1,
		__BITFIELD_FIELD(u32 modemismsk		: 1,
		__BITFIELD_FIELD(u32 reserved_0_0	: 1,
		;))))))))))))))))))))))))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_gपूर्णांकsts
 *
 * Core Interrupt Register (GINTSTS)
 *
 * This रेजिस्टर पूर्णांकerrupts the application क्रम प्रणाली-level events in the
 * current mode of operation (Device mode or Host mode). It is shown in
 * Interrupt. Some of the bits in this रेजिस्टर are valid only in Host mode,
 * जबतक others are valid in Device mode only. This रेजिस्टर also indicates the
 * current mode of operation. In order to clear the पूर्णांकerrupt status bits of
 * type R_SS_WC, the application must ग_लिखो 1'b1 पूर्णांकo the bit. The FIFO status
 * पूर्णांकerrupts are पढ़ो only; once software पढ़ोs from or ग_लिखोs to the FIFO
 * जबतक servicing these पूर्णांकerrupts, FIFO पूर्णांकerrupt conditions are cleared
 * स्वतःmatically.
 */
जोड़ cvmx_usbcx_gपूर्णांकsts अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_gपूर्णांकsts_s
	 * @wkupपूर्णांक: Resume/Remote Wakeup Detected Interrupt (WkUpInt)
	 *	In Device mode, this पूर्णांकerrupt is निश्चितed when a resume is
	 *	detected on the USB. In Host mode, this पूर्णांकerrupt is निश्चितed
	 *	when a remote wakeup is detected on the USB.
	 *	For more inक्रमmation on how to use this पूर्णांकerrupt, see "Partial
	 *	Power-Down and Clock Gating Programming Model" on
	 *	page 353.
	 * @sessreqपूर्णांक: Session Request/New Session Detected Interrupt
	 *		(SessReqInt)
	 *	In Host mode, this पूर्णांकerrupt is निश्चितed when a session request
	 *	is detected from the device. In Device mode, this पूर्णांकerrupt is
	 *	निश्चितed when the uपंचांगiotg_bvalid संकेत goes high.
	 *	For more inक्रमmation on how to use this पूर्णांकerrupt, see "Partial
	 *	Power-Down and Clock Gating Programming Model" on
	 *	page 353.
	 * @disconnपूर्णांक: Disconnect Detected Interrupt (DisconnInt)
	 *	Asserted when a device disconnect is detected.
	 * @conidstschng: Connector ID Status Change (ConIDStsChng)
	 *	The core sets this bit when there is a change in connector ID
	 *	status.
	 * @ptxfemp: Periodic TxFIFO Empty (PTxFEmp)
	 *	Asserted when the Periodic Transmit FIFO is either half or
	 *	completely empty and there is space क्रम at least one entry to be
	 *	written in the Periodic Request Queue. The half or completely
	 *	empty status is determined by the Periodic TxFIFO Empty Level
	 *	bit in the Core AHB Configuration रेजिस्टर
	 *	(GAHBCFG.PTxFEmpLvl).
	 * @hchपूर्णांक: Host Channels Interrupt (HChInt)
	 *	The core sets this bit to indicate that an पूर्णांकerrupt is pending
	 *	on one of the channels of the core (in Host mode). The
	 *	application must पढ़ो the Host All Channels Interrupt (HAINT)
	 *	रेजिस्टर to determine the exact number of the channel on which
	 *	the पूर्णांकerrupt occurred, and then पढ़ो the corresponding Host
	 *	Channel-n Interrupt (HCINTn) रेजिस्टर to determine the exact
	 *	cause of the पूर्णांकerrupt. The application must clear the
	 *	appropriate status bit in the HCINTn रेजिस्टर to clear this bit.
	 * @prtपूर्णांक: Host Port Interrupt (PrtInt)
	 *	The core sets this bit to indicate a change in port status of
	 *	one of the O2P USB core ports in Host mode. The application must
	 *	पढ़ो the Host Port Control and Status (HPRT) रेजिस्टर to
	 *	determine the exact event that caused this पूर्णांकerrupt. The
	 *	application must clear the appropriate status bit in the Host
	 *	Port Control and Status रेजिस्टर to clear this bit.
	 * @fetsusp: Data Fetch Suspended (FetSusp)
	 *	This पूर्णांकerrupt is valid only in DMA mode. This पूर्णांकerrupt
	 *	indicates that the core has stopped fetching data क्रम IN
	 *	endpoपूर्णांकs due to the unavailability of TxFIFO space or Request
	 *	Queue space. This पूर्णांकerrupt is used by the application क्रम an
	 *	endpoपूर्णांक mismatch algorithm.
	 * @incomplp: Incomplete Periodic Transfer (incomplP)
	 *	In Host mode, the core sets this पूर्णांकerrupt bit when there are
	 *	incomplete periodic transactions still pending which are
	 *	scheduled क्रम the current microframe.
	 *	Incomplete Isochronous OUT Transfer (incompISOOUT)
	 *	The Device mode, the core sets this पूर्णांकerrupt to indicate that
	 *	there is at least one isochronous OUT endpoपूर्णांक on which the
	 *	transfer is not completed in the current microframe. This
	 *	पूर्णांकerrupt is निश्चितed aदीर्घ with the End of Periodic Frame
	 *	Interrupt (EOPF) bit in this रेजिस्टर.
	 * @incompisoin: Incomplete Isochronous IN Transfer (incompISOIN)
	 *	The core sets this पूर्णांकerrupt to indicate that there is at least
	 *	one isochronous IN endpoपूर्णांक on which the transfer is not
	 *	completed in the current microframe. This पूर्णांकerrupt is निश्चितed
	 *	aदीर्घ with the End of Periodic Frame Interrupt (EOPF) bit in
	 *	this रेजिस्टर.
	 * @oepपूर्णांक: OUT Endpoपूर्णांकs Interrupt (OEPInt)
	 *	The core sets this bit to indicate that an पूर्णांकerrupt is pending
	 *	on one of the OUT endpoपूर्णांकs of the core (in Device mode). The
	 *	application must पढ़ो the Device All Endpoपूर्णांकs Interrupt
	 *	(DAINT) रेजिस्टर to determine the exact number of the OUT
	 *	endpoपूर्णांक on which the पूर्णांकerrupt occurred, and then पढ़ो the
	 *	corresponding Device OUT Endpoपूर्णांक-n Interrupt (DOEPINTn)
	 *	रेजिस्टर to determine the exact cause of the पूर्णांकerrupt. The
	 *	application must clear the appropriate status bit in the
	 *	corresponding DOEPINTn रेजिस्टर to clear this bit.
	 * @iepपूर्णांक: IN Endpoपूर्णांकs Interrupt (IEPInt)
	 *	The core sets this bit to indicate that an पूर्णांकerrupt is pending
	 *	on one of the IN endpoपूर्णांकs of the core (in Device mode). The
	 *	application must पढ़ो the Device All Endpoपूर्णांकs Interrupt
	 *	(DAINT) रेजिस्टर to determine the exact number of the IN
	 *	endpoपूर्णांक on which the पूर्णांकerrupt occurred, and then पढ़ो the
	 *	corresponding Device IN Endpoपूर्णांक-n Interrupt (DIEPINTn)
	 *	रेजिस्टर to determine the exact cause of the पूर्णांकerrupt. The
	 *	application must clear the appropriate status bit in the
	 *	corresponding DIEPINTn रेजिस्टर to clear this bit.
	 * @epmis: Endpoपूर्णांक Mismatch Interrupt (EPMis)
	 *	Indicates that an IN token has been received क्रम a non-periodic
	 *	endpoपूर्णांक, but the data क्रम another endpoपूर्णांक is present in the
	 *	top of the Non-Periodic Transmit FIFO and the IN endpoपूर्णांक
	 *	mismatch count programmed by the application has expired.
	 * @eopf: End of Periodic Frame Interrupt (EOPF)
	 *	Indicates that the period specअगरied in the Periodic Frame
	 *	Interval field of the Device Configuration रेजिस्टर
	 *	(DCFG.PerFrInt) has been reached in the current microframe.
	 * @isooutdrop: Isochronous OUT Packet Dropped Interrupt (ISOOutDrop)
	 *	The core sets this bit when it fails to ग_लिखो an isochronous OUT
	 *	packet पूर्णांकo the RxFIFO because the RxFIFO करोesn't have
	 *	enough space to accommodate a maximum packet size packet
	 *	क्रम the isochronous OUT endpoपूर्णांक.
	 * @क्रमागतकरोne: Enumeration Done (EnumDone)
	 *	The core sets this bit to indicate that speed क्रमागतeration is
	 *	complete. The application must पढ़ो the Device Status (DSTS)
	 *	रेजिस्टर to obtain the क्रमागतerated speed.
	 * @usbrst: USB Reset (USBRst)
	 *	The core sets this bit to indicate that a reset is detected on
	 *	the USB.
	 * @usbsusp: USB Suspend (USBSusp)
	 *	The core sets this bit to indicate that a suspend was detected
	 *	on the USB. The core enters the Suspended state when there
	 *	is no activity on the phy_line_state_i संकेत क्रम an extended
	 *	period of समय.
	 * @erlysusp: Early Suspend (ErlySusp)
	 *	The core sets this bit to indicate that an Idle state has been
	 *	detected on the USB क्रम 3 ms.
	 * @i2cपूर्णांक: I2C Interrupt (I2CINT)
	 *	This bit is always 0x0.
	 * @ulpickपूर्णांक: ULPI Carkit Interrupt (ULPICKINT)
	 *	This bit is always 0x0.
	 * @goutnakeff: Global OUT NAK Effective (GOUTNakEff)
	 *	Indicates that the Set Global OUT NAK bit in the Device Control
	 *	रेजिस्टर (DCTL.SGOUTNak), set by the application, has taken
	 *	effect in the core. This bit can be cleared by writing the Clear
	 *	Global OUT NAK bit in the Device Control रेजिस्टर
	 *	(DCTL.CGOUTNak).
	 * @ginnakeff: Global IN Non-Periodic NAK Effective (GINNakEff)
	 *	Indicates that the Set Global Non-Periodic IN NAK bit in the
	 *	Device Control रेजिस्टर (DCTL.SGNPInNak), set by the
	 *	application, has taken effect in the core. That is, the core has
	 *	sampled the Global IN NAK bit set by the application. This bit
	 *	can be cleared by clearing the Clear Global Non-Periodic IN
	 *	NAK bit in the Device Control रेजिस्टर (DCTL.CGNPInNak).
	 *	This पूर्णांकerrupt करोes not necessarily mean that a NAK handshake
	 *	is sent out on the USB. The STALL bit takes precedence over
	 *	the NAK bit.
	 * @nptxfemp: Non-Periodic TxFIFO Empty (NPTxFEmp)
	 *	This पूर्णांकerrupt is निश्चितed when the Non-Periodic TxFIFO is
	 *	either half or completely empty, and there is space क्रम at least
	 *	one entry to be written to the Non-Periodic Transmit Request
	 *	Queue. The half or completely empty status is determined by
	 *	the Non-Periodic TxFIFO Empty Level bit in the Core AHB
	 *	Configuration रेजिस्टर (GAHBCFG.NPTxFEmpLvl).
	 * @rxflvl: RxFIFO Non-Empty (RxFLvl)
	 *	Indicates that there is at least one packet pending to be पढ़ो
	 *	from the RxFIFO.
	 * @sof: Start of (micro)Frame (Sof)
	 *	In Host mode, the core sets this bit to indicate that an SOF
	 *	(FS), micro-SOF (HS), or Keep-Alive (LS) is transmitted on the
	 *	USB. The application must ग_लिखो a 1 to this bit to clear the
	 *	पूर्णांकerrupt.
	 *	In Device mode, in the core sets this bit to indicate that an
	 *	SOF token has been received on the USB. The application can पढ़ो
	 *	the Device Status रेजिस्टर to get the current (micro)frame
	 *	number. This पूर्णांकerrupt is seen only when the core is operating
	 *	at either HS or FS.
	 * @otgपूर्णांक: OTG Interrupt (OTGInt)
	 *	The core sets this bit to indicate an OTG protocol event. The
	 *	application must पढ़ो the OTG Interrupt Status (GOTGINT)
	 *	रेजिस्टर to determine the exact event that caused this
	 *	पूर्णांकerrupt. The application must clear the appropriate status bit
	 *	in the GOTGINT रेजिस्टर to clear this bit.
	 * @modemis: Mode Mismatch Interrupt (ModeMis)
	 *	The core sets this bit when the application is trying to access:
	 *	* A Host mode रेजिस्टर, when the core is operating in Device
	 *	mode
	 *	* A Device mode रेजिस्टर, when the core is operating in Host
	 *	mode
	 *	The रेजिस्टर access is completed on the AHB with an OKAY
	 *	response, but is ignored by the core पूर्णांकernally and करोesn't
	 *	affect the operation of the core.
	 * @curmod: Current Mode of Operation (CurMod)
	 *	Indicates the current mode of operation.
	 *	* 1'b0: Device mode
	 *	* 1'b1: Host mode
	 */
	काष्ठा cvmx_usbcx_gपूर्णांकsts_s अणु
		__BITFIELD_FIELD(u32 wkupपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 sessreqपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 disconnपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 conidstschng	: 1,
		__BITFIELD_FIELD(u32 reserved_27_27	: 1,
		__BITFIELD_FIELD(u32 ptxfemp		: 1,
		__BITFIELD_FIELD(u32 hchपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 prtपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 reserved_23_23	: 1,
		__BITFIELD_FIELD(u32 fetsusp		: 1,
		__BITFIELD_FIELD(u32 incomplp		: 1,
		__BITFIELD_FIELD(u32 incompisoin	: 1,
		__BITFIELD_FIELD(u32 oepपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 iepपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 epmis		: 1,
		__BITFIELD_FIELD(u32 reserved_16_16	: 1,
		__BITFIELD_FIELD(u32 eopf		: 1,
		__BITFIELD_FIELD(u32 isooutdrop		: 1,
		__BITFIELD_FIELD(u32 क्रमागतकरोne		: 1,
		__BITFIELD_FIELD(u32 usbrst		: 1,
		__BITFIELD_FIELD(u32 usbsusp		: 1,
		__BITFIELD_FIELD(u32 erlysusp		: 1,
		__BITFIELD_FIELD(u32 i2cपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 ulpickपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 goutnakeff		: 1,
		__BITFIELD_FIELD(u32 ginnakeff		: 1,
		__BITFIELD_FIELD(u32 nptxfemp		: 1,
		__BITFIELD_FIELD(u32 rxflvl		: 1,
		__BITFIELD_FIELD(u32 sof		: 1,
		__BITFIELD_FIELD(u32 otgपूर्णांक		: 1,
		__BITFIELD_FIELD(u32 modemis		: 1,
		__BITFIELD_FIELD(u32 curmod		: 1,
		;))))))))))))))))))))))))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_gnptxfsiz
 *
 * Non-Periodic Transmit FIFO Size Register (GNPTXFSIZ)
 *
 * The application can program the RAM size and the memory start address क्रम the
 * Non-Periodic TxFIFO.
 */
जोड़ cvmx_usbcx_gnptxfsiz अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_gnptxfsiz_s
	 * @nptxfdep: Non-Periodic TxFIFO Depth (NPTxFDep)
	 *	This value is in terms of 32-bit words.
	 *	Minimum value is 16
	 *	Maximum value is 32768
	 * @nptxfstaddr: Non-Periodic Transmit RAM Start Address (NPTxFStAddr)
	 *	This field contains the memory start address क्रम Non-Periodic
	 *	Transmit FIFO RAM.
	 */
	काष्ठा cvmx_usbcx_gnptxfsiz_s अणु
		__BITFIELD_FIELD(u32 nptxfdep		: 16,
		__BITFIELD_FIELD(u32 nptxfstaddr	: 16,
		;))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_gnptxsts
 *
 * Non-Periodic Transmit FIFO/Queue Status Register (GNPTXSTS)
 *
 * This पढ़ो-only रेजिस्टर contains the मुक्त space inक्रमmation क्रम the
 * Non-Periodic TxFIFO and the Non-Periodic Transmit Request Queue.
 */
जोड़ cvmx_usbcx_gnptxsts अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_gnptxsts_s
	 * @nptxqtop: Top of the Non-Periodic Transmit Request Queue (NPTxQTop)
	 *	Entry in the Non-Periodic Tx Request Queue that is currently
	 *	being processed by the MAC.
	 *	* Bits [30:27]: Channel/endpoपूर्णांक number
	 *	* Bits [26:25]:
	 *	- 2'b00: IN/OUT token
	 *	- 2'b01: Zero-length transmit packet (device IN/host OUT)
	 *	- 2'b10: PING/CSPLIT token
	 *	- 2'b11: Channel halt command
	 *	* Bit [24]: Terminate (last entry क्रम selected channel/endpoपूर्णांक)
	 * @nptxqspcavail: Non-Periodic Transmit Request Queue Space Available
	 *	(NPTxQSpcAvail)
	 *	Indicates the amount of मुक्त space available in the Non-
	 *	Periodic Transmit Request Queue. This queue holds both IN
	 *	and OUT requests in Host mode. Device mode has only IN
	 *	requests.
	 *	* 8'h0: Non-Periodic Transmit Request Queue is full
	 *	* 8'h1: 1 location available
	 *	* 8'h2: 2 locations available
	 *	* n: n locations available (0..8)
	 *	* Others: Reserved
	 * @nptxfspcavail: Non-Periodic TxFIFO Space Avail (NPTxFSpcAvail)
	 *	Indicates the amount of मुक्त space available in the Non-
	 *	Periodic TxFIFO.
	 *	Values are in terms of 32-bit words.
	 *	* 16'h0: Non-Periodic TxFIFO is full
	 *	* 16'h1: 1 word available
	 *	* 16'h2: 2 words available
	 *	* 16'hn: n words available (where 0..32768)
	 *	* 16'h8000: 32768 words available
	 *	* Others: Reserved
	 */
	काष्ठा cvmx_usbcx_gnptxsts_s अणु
		__BITFIELD_FIELD(u32 reserved_31_31	: 1,
		__BITFIELD_FIELD(u32 nptxqtop		: 7,
		__BITFIELD_FIELD(u32 nptxqspcavail	: 8,
		__BITFIELD_FIELD(u32 nptxfspcavail	: 16,
		;))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_grstctl
 *
 * Core Reset Register (GRSTCTL)
 *
 * The application uses this रेजिस्टर to reset various hardware features inside
 * the core.
 */
जोड़ cvmx_usbcx_grstctl अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_grstctl_s
	 * @ahbidle: AHB Master Idle (AHBIdle)
	 *	Indicates that the AHB Master State Machine is in the IDLE
	 *	condition.
	 * @dmareq: DMA Request Signal (DMAReq)
	 *	Indicates that the DMA request is in progress. Used क्रम debug.
	 * @txfnum: TxFIFO Number (TxFNum)
	 *	This is the FIFO number that must be flushed using the TxFIFO
	 *	Flush bit. This field must not be changed until the core clears
	 *	the TxFIFO Flush bit.
	 *	* 5'h0: Non-Periodic TxFIFO flush
	 *	* 5'h1: Periodic TxFIFO 1 flush in Device mode or Periodic
	 *	TxFIFO flush in Host mode
	 *	* 5'h2: Periodic TxFIFO 2 flush in Device mode
	 *	- ...
	 *	* 5'hF: Periodic TxFIFO 15 flush in Device mode
	 *	* 5'h10: Flush all the Periodic and Non-Periodic TxFIFOs in the
	 *	core
	 * @txfflsh: TxFIFO Flush (TxFFlsh)
	 *	This bit selectively flushes a single or all transmit FIFOs, but
	 *	cannot करो so अगर the core is in the midst of a transaction.
	 *	The application must only ग_लिखो this bit after checking that the
	 *	core is neither writing to the TxFIFO nor पढ़ोing from the
	 *	TxFIFO.
	 *	The application must रुको until the core clears this bit beक्रमe
	 *	perक्रमming any operations. This bit takes 8 घड़ीs (of phy_clk
	 *	or hclk, whichever is slower) to clear.
	 * @rxfflsh: RxFIFO Flush (RxFFlsh)
	 *	The application can flush the entire RxFIFO using this bit, but
	 *	must first ensure that the core is not in the middle of a
	 *	transaction.
	 *	The application must only ग_लिखो to this bit after checking that
	 *	the core is neither पढ़ोing from the RxFIFO nor writing to the
	 *	RxFIFO.
	 *	The application must रुको until the bit is cleared beक्रमe
	 *	perक्रमming any other operations. This bit will take 8 घड़ीs
	 *	(slowest of PHY or AHB घड़ी) to clear.
	 * @पूर्णांकknqflsh: IN Token Sequence Learning Queue Flush (INTknQFlsh)
	 *	The application ग_लिखोs this bit to flush the IN Token Sequence
	 *	Learning Queue.
	 * @frmcntrrst: Host Frame Counter Reset (FrmCntrRst)
	 *	The application ग_लिखोs this bit to reset the (micro)frame number
	 *	counter inside the core. When the (micro)frame counter is reset,
	 *	the subsequent SOF sent out by the core will have a
	 *	(micro)frame number of 0.
	 * @hsftrst: HClk Soft Reset (HSftRst)
	 *	The application uses this bit to flush the control logic in the
	 *	AHB Clock करोमुख्य. Only AHB Clock Doमुख्य pipelines are reset.
	 *	* FIFOs are not flushed with this bit.
	 *	* All state machines in the AHB घड़ी करोमुख्य are reset to the
	 *	Idle state after terminating the transactions on the AHB,
	 *	following the protocol.
	 *	* CSR control bits used by the AHB घड़ी करोमुख्य state
	 *	machines are cleared.
	 *	* To clear this पूर्णांकerrupt, status mask bits that control the
	 *	पूर्णांकerrupt status and are generated by the AHB घड़ी करोमुख्य
	 *	state machine are cleared.
	 *	* Because पूर्णांकerrupt status bits are not cleared, the application
	 *	can get the status of any core events that occurred after it set
	 *	this bit.
	 *	This is a self-clearing bit that the core clears after all
	 *	necessary logic is reset in the core. This may take several
	 *	घड़ीs, depending on the core's current state.
	 * @csftrst: Core Soft Reset (CSftRst)
	 *	Resets the hclk and phy_घड़ी करोमुख्यs as follows:
	 *	* Clears the पूर्णांकerrupts and all the CSR रेजिस्टरs except the
	 *	following रेजिस्टर bits:
	 *	- PCGCCTL.RstPdwnModule
	 *	- PCGCCTL.GateHclk
	 *	- PCGCCTL.PwrClmp
	 *	- PCGCCTL.StopPPhyLPwrClkSelclk
	 *	- GUSBCFG.PhyLPwrClkSel
	 *	- GUSBCFG.DDRSel
	 *	- GUSBCFG.PHYSel
	 *	- GUSBCFG.FSIntf
	 *	- GUSBCFG.ULPI_UTMI_Sel
	 *	- GUSBCFG.PHYIf
	 *	- HCFG.FSLSPclkSel
	 *	- DCFG.DevSpd
	 *	* All module state machines (except the AHB Slave Unit) are
	 *	reset to the IDLE state, and all the transmit FIFOs and the
	 *	receive FIFO are flushed.
	 *	* Any transactions on the AHB Master are terminated as soon
	 *	as possible, after gracefully completing the last data phase of
	 *	an AHB transfer. Any transactions on the USB are terminated
	 *	immediately.
	 *	The application can ग_लिखो to this bit any समय it wants to reset
	 *	the core. This is a self-clearing bit and the core clears this
	 *	bit after all the necessary logic is reset in the core, which
	 *	may take several घड़ीs, depending on the current state of the
	 *	core. Once this bit is cleared software should रुको at least 3
	 *	PHY घड़ीs beक्रमe करोing any access to the PHY करोमुख्य
	 *	(synchronization delay). Software should also should check that
	 *	bit 31 of this रेजिस्टर is 1 (AHB Master is IDLE) beक्रमe
	 *	starting any operation.
	 *	Typically software reset is used during software development
	 *	and also when you dynamically change the PHY selection bits
	 *	in the USB configuration रेजिस्टरs listed above. When you
	 *	change the PHY, the corresponding घड़ी क्रम the PHY is
	 *	selected and used in the PHY करोमुख्य. Once a new घड़ी is
	 *	selected, the PHY करोमुख्य has to be reset क्रम proper operation.
	 */
	काष्ठा cvmx_usbcx_grstctl_s अणु
		__BITFIELD_FIELD(u32 ahbidle		: 1,
		__BITFIELD_FIELD(u32 dmareq		: 1,
		__BITFIELD_FIELD(u32 reserved_11_29	: 19,
		__BITFIELD_FIELD(u32 txfnum		: 5,
		__BITFIELD_FIELD(u32 txfflsh		: 1,
		__BITFIELD_FIELD(u32 rxfflsh		: 1,
		__BITFIELD_FIELD(u32 पूर्णांकknqflsh		: 1,
		__BITFIELD_FIELD(u32 frmcntrrst		: 1,
		__BITFIELD_FIELD(u32 hsftrst		: 1,
		__BITFIELD_FIELD(u32 csftrst		: 1,
		;))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_grxfsiz
 *
 * Receive FIFO Size Register (GRXFSIZ)
 *
 * The application can program the RAM size that must be allocated to the
 * RxFIFO.
 */
जोड़ cvmx_usbcx_grxfsiz अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_grxfsiz_s
	 * @rxfdep: RxFIFO Depth (RxFDep)
	 *	This value is in terms of 32-bit words.
	 *	* Minimum value is 16
	 *	* Maximum value is 32768
	 */
	काष्ठा cvmx_usbcx_grxfsiz_s अणु
		__BITFIELD_FIELD(u32 reserved_16_31	: 16,
		__BITFIELD_FIELD(u32 rxfdep		: 16,
		;))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_grxstsph
 *
 * Receive Status Read and Pop Register, Host Mode (GRXSTSPH)
 *
 * A पढ़ो to the Receive Status Read and Pop रेजिस्टर वापसs and additionally
 * pops the top data entry out of the RxFIFO.
 * This Description is only valid when the core is in Host Mode. For Device Mode
 * use USBC_GRXSTSPD instead.
 * NOTE: GRXSTSPH and GRXSTSPD are physically the same रेजिस्टर and share the
 *	 same offset in the O2P USB core. The offset dअगरference shown in this
 *	 करोcument is क्रम software clarity and is actually ignored by the
 *       hardware.
 */
जोड़ cvmx_usbcx_grxstsph अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_grxstsph_s
	 * @pktsts: Packet Status (PktSts)
	 *	Indicates the status of the received packet
	 *	* 4'b0010: IN data packet received
	 *	* 4'b0011: IN transfer completed (triggers an पूर्णांकerrupt)
	 *	* 4'b0101: Data toggle error (triggers an पूर्णांकerrupt)
	 *	* 4'b0111: Channel halted (triggers an पूर्णांकerrupt)
	 *	* Others: Reserved
	 * @dpid: Data PID (DPID)
	 *	* 2'b00: DATA0
	 *	* 2'b10: DATA1
	 *	* 2'b01: DATA2
	 *	* 2'b11: MDATA
	 * @bcnt: Byte Count (BCnt)
	 *	Indicates the byte count of the received IN data packet
	 * @chnum: Channel Number (ChNum)
	 *	Indicates the channel number to which the current received
	 *	packet beदीर्घs.
	 */
	काष्ठा cvmx_usbcx_grxstsph_s अणु
		__BITFIELD_FIELD(u32 reserved_21_31	: 11,
		__BITFIELD_FIELD(u32 pktsts		: 4,
		__BITFIELD_FIELD(u32 dpid		: 2,
		__BITFIELD_FIELD(u32 bcnt		: 11,
		__BITFIELD_FIELD(u32 chnum		: 4,
		;)))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_gusbcfg
 *
 * Core USB Configuration Register (GUSBCFG)
 *
 * This रेजिस्टर can be used to configure the core after घातer-on or a changing
 * to Host mode or Device mode. It contains USB and USB-PHY related
 * configuration parameters. The application must program this रेजिस्टर beक्रमe
 * starting any transactions on either the AHB or the USB. Do not make changes
 * to this रेजिस्टर after the initial programming.
 */
जोड़ cvmx_usbcx_gusbcfg अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_gusbcfg_s
	 * @otgi2csel: UTMIFS or I2C Interface Select (OtgI2CSel)
	 *	This bit is always 0x0.
	 * @phylpwrclksel: PHY Low-Power Clock Select (PhyLPwrClkSel)
	 *	Software should set this bit to 0x0.
	 *	Selects either 480-MHz or 48-MHz (low-घातer) PHY mode. In
	 *	FS and LS modes, the PHY can usually operate on a 48-MHz
	 *	घड़ी to save घातer.
	 *	* 1'b0: 480-MHz Internal PLL घड़ी
	 *	* 1'b1: 48-MHz External Clock
	 *	In 480 MHz mode, the UTMI पूर्णांकerface operates at either 60 or
	 *	30-MHz, depending upon whether 8- or 16-bit data width is
	 *	selected. In 48-MHz mode, the UTMI पूर्णांकerface operates at 48
	 *	MHz in FS mode and at either 48 or 6 MHz in LS mode
	 *	(depending on the PHY venकरोr).
	 *	This bit drives the uपंचांगi_fsls_low_घातer core output संकेत, and
	 *	is valid only क्रम UTMI+ PHYs.
	 * @usbtrdtim: USB Turnaround Time (USBTrdTim)
	 *	Sets the turnaround समय in PHY घड़ीs.
	 *	Specअगरies the response समय क्रम a MAC request to the Packet
	 *	FIFO Controller (PFC) to fetch data from the DFIFO (SPRAM).
	 *	This must be programmed to 0x5.
	 * @hnpcap: HNP-Capable (HNPCap)
	 *	This bit is always 0x0.
	 * @srpcap: SRP-Capable (SRPCap)
	 *	This bit is always 0x0.
	 * @ddrsel: ULPI DDR Select (DDRSel)
	 *	Software should set this bit to 0x0.
	 * @physel: USB 2.0 High-Speed PHY or USB 1.1 Full-Speed Serial
	 *	Software should set this bit to 0x0.
	 * @fsपूर्णांकf: Full-Speed Serial Interface Select (FSIntf)
	 *	Software should set this bit to 0x0.
	 * @ulpi_uपंचांगi_sel: ULPI or UTMI+ Select (ULPI_UTMI_Sel)
	 *	This bit is always 0x0.
	 * @phyअगर: PHY Interface (PHYIf)
	 *	This bit is always 0x1.
	 * @toutcal: HS/FS Timeout Calibration (TOutCal)
	 *	The number of PHY घड़ीs that the application programs in this
	 *	field is added to the high-speed/full-speed पूर्णांकerpacket समयout
	 *	duration in the core to account क्रम any additional delays
	 *	पूर्णांकroduced by the PHY. This may be required, since the delay
	 *	पूर्णांकroduced by the PHY in generating the linestate condition may
	 *	vary from one PHY to another.
	 *	The USB standard समयout value क्रम high-speed operation is
	 *	736 to 816 (inclusive) bit बार. The USB standard समयout
	 *	value क्रम full-speed operation is 16 to 18 (inclusive) bit
	 *	बार. The application must program this field based on the
	 *	speed of क्रमागतeration. The number of bit बार added per PHY
	 *	घड़ी are:
	 *	High-speed operation:
	 *	* One 30-MHz PHY घड़ी = 16 bit बार
	 *	* One 60-MHz PHY घड़ी = 8 bit बार
	 *	Full-speed operation:
	 *	* One 30-MHz PHY घड़ी = 0.4 bit बार
	 *	* One 60-MHz PHY घड़ी = 0.2 bit बार
	 *	* One 48-MHz PHY घड़ी = 0.25 bit बार
	 */
	काष्ठा cvmx_usbcx_gusbcfg_s अणु
		__BITFIELD_FIELD(u32 reserved_17_31	: 15,
		__BITFIELD_FIELD(u32 otgi2csel		: 1,
		__BITFIELD_FIELD(u32 phylpwrclksel	: 1,
		__BITFIELD_FIELD(u32 reserved_14_14	: 1,
		__BITFIELD_FIELD(u32 usbtrdtim		: 4,
		__BITFIELD_FIELD(u32 hnpcap		: 1,
		__BITFIELD_FIELD(u32 srpcap		: 1,
		__BITFIELD_FIELD(u32 ddrsel		: 1,
		__BITFIELD_FIELD(u32 physel		: 1,
		__BITFIELD_FIELD(u32 fsपूर्णांकf		: 1,
		__BITFIELD_FIELD(u32 ulpi_uपंचांगi_sel	: 1,
		__BITFIELD_FIELD(u32 phyअगर		: 1,
		__BITFIELD_FIELD(u32 toutcal		: 3,
		;)))))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_haपूर्णांक
 *
 * Host All Channels Interrupt Register (HAINT)
 *
 * When a signअगरicant event occurs on a channel, the Host All Channels Interrupt
 * रेजिस्टर पूर्णांकerrupts the application using the Host Channels Interrupt bit of
 * the Core Interrupt रेजिस्टर (GINTSTS.HChInt). This is shown in Interrupt.
 * There is one पूर्णांकerrupt bit per channel, up to a maximum of 16 bits. Bits in
 * this रेजिस्टर are set and cleared when the application sets and clears bits
 * in the corresponding Host Channel-n Interrupt रेजिस्टर.
 */
जोड़ cvmx_usbcx_haपूर्णांक अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_haपूर्णांक_s
	 * @haपूर्णांक: Channel Interrupts (HAINT)
	 *	One bit per channel: Bit 0 क्रम Channel 0, bit 15 क्रम Channel 15
	 */
	काष्ठा cvmx_usbcx_haपूर्णांक_s अणु
		__BITFIELD_FIELD(u32 reserved_16_31	: 16,
		__BITFIELD_FIELD(u32 haपूर्णांक		: 16,
		;))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_haपूर्णांकmsk
 *
 * Host All Channels Interrupt Mask Register (HAINTMSK)
 *
 * The Host All Channel Interrupt Mask रेजिस्टर works with the Host All Channel
 * Interrupt रेजिस्टर to पूर्णांकerrupt the application when an event occurs on a
 * channel. There is one पूर्णांकerrupt mask bit per channel, up to a maximum of 16
 * bits.
 * Mask पूर्णांकerrupt: 1'b0 Unmask interrupt: 1'b1
 */
जोड़ cvmx_usbcx_haपूर्णांकmsk अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_haपूर्णांकmsk_s
	 * @haपूर्णांकmsk: Channel Interrupt Mask (HAINTMsk)
	 *	One bit per channel: Bit 0 क्रम channel 0, bit 15 क्रम channel 15
	 */
	काष्ठा cvmx_usbcx_haपूर्णांकmsk_s अणु
		__BITFIELD_FIELD(u32 reserved_16_31	: 16,
		__BITFIELD_FIELD(u32 haपूर्णांकmsk		: 16,
		;))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hcअक्षर#
 *
 * Host Channel-n Characteristics Register (HCCHAR)
 *
 */
जोड़ cvmx_usbcx_hcअक्षरx अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hcअक्षरx_s
	 * @chena: Channel Enable (ChEna)
	 *	This field is set by the application and cleared by the OTG
	 *	host.
	 *	* 1'b0: Channel disabled
	 *	* 1'b1: Channel enabled
	 * @chdis: Channel Disable (ChDis)
	 *	The application sets this bit to stop transmitting/receiving
	 *	data on a channel, even beक्रमe the transfer क्रम that channel is
	 *	complete. The application must रुको क्रम the Channel Disabled
	 *	पूर्णांकerrupt beक्रमe treating the channel as disabled.
	 * @oddfrm: Odd Frame (OddFrm)
	 *	This field is set (reset) by the application to indicate that
	 *	the OTG host must perक्रमm a transfer in an odd (micro)frame.
	 *	This field is applicable क्रम only periodic (isochronous and
	 *	पूर्णांकerrupt) transactions.
	 *	* 1'b0: Even (micro)frame
	 *	* 1'b1: Odd (micro)frame
	 * @devaddr: Device Address (DevAddr)
	 *	This field selects the specअगरic device serving as the data
	 *	source or sink.
	 * @ec: Multi Count (MC) / Error Count (EC)
	 *	When the Split Enable bit of the Host Channel-n Split Control
	 *	रेजिस्टर (HCSPLTn.SpltEna) is reset (1'b0), this field indicates
	 *	to the host the number of transactions that should be executed
	 *	per microframe क्रम this endpoपूर्णांक.
	 *	* 2'b00: Reserved. This field yields undefined results.
	 *	* 2'b01: 1 transaction
	 *	* 2'b10: 2 transactions to be issued क्रम this endpoपूर्णांक per
	 *	microframe
	 *	* 2'b11: 3 transactions to be issued क्रम this endpoपूर्णांक per
	 *	microframe
	 *	When HCSPLTn.SpltEna is set (1'b1), this field indicates the
	 *	number of immediate retries to be perक्रमmed क्रम a periodic split
	 *	transactions on transaction errors. This field must be set to at
	 *	least 2'b01.
	 * @eptype: Endpoपूर्णांक Type (EPType)
	 *	Indicates the transfer type selected.
	 *	* 2'b00: Control
	 *	* 2'b01: Isochronous
	 *	* 2'b10: Bulk
	 *	* 2'b11: Interrupt
	 * @lspddev: Low-Speed Device (LSpdDev)
	 *	This field is set by the application to indicate that this
	 *	channel is communicating to a low-speed device.
	 * @epdir: Endpoपूर्णांक Direction (EPDir)
	 *	Indicates whether the transaction is IN or OUT.
	 *	* 1'b0: OUT
	 *	* 1'b1: IN
	 * @epnum: Endpoपूर्णांक Number (EPNum)
	 *	Indicates the endpoपूर्णांक number on the device serving as the
	 *	data source or sink.
	 * @mps: Maximum Packet Size (MPS)
	 *	Indicates the maximum packet size of the associated endpoपूर्णांक.
	 */
	काष्ठा cvmx_usbcx_hcअक्षरx_s अणु
		__BITFIELD_FIELD(u32 chena		: 1,
		__BITFIELD_FIELD(u32 chdis		: 1,
		__BITFIELD_FIELD(u32 oddfrm		: 1,
		__BITFIELD_FIELD(u32 devaddr		: 7,
		__BITFIELD_FIELD(u32 ec			: 2,
		__BITFIELD_FIELD(u32 eptype		: 2,
		__BITFIELD_FIELD(u32 lspddev		: 1,
		__BITFIELD_FIELD(u32 reserved_16_16	: 1,
		__BITFIELD_FIELD(u32 epdir		: 1,
		__BITFIELD_FIELD(u32 epnum		: 4,
		__BITFIELD_FIELD(u32 mps		: 11,
		;)))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hcfg
 *
 * Host Configuration Register (HCFG)
 *
 * This रेजिस्टर configures the core after घातer-on. Do not make changes to this
 * रेजिस्टर after initializing the host.
 */
जोड़ cvmx_usbcx_hcfg अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hcfg_s
	 * @fslssupp: FS- and LS-Only Support (FSLSSupp)
	 *	The application uses this bit to control the core's क्रमागतeration
	 *	speed. Using this bit, the application can make the core
	 *	क्रमागतerate as a FS host, even अगर the connected device supports
	 *	HS traffic. Do not make changes to this field after initial
	 *	programming.
	 *	* 1'b0: HS/FS/LS, based on the maximum speed supported by
	 *	the connected device
	 *	* 1'b1: FS/LS-only, even अगर the connected device can support HS
	 * @fslspclksel: FS/LS PHY Clock Select (FSLSPclkSel)
	 *	When the core is in FS Host mode
	 *	* 2'b00: PHY घड़ी is running at 30/60 MHz
	 *	* 2'b01: PHY घड़ी is running at 48 MHz
	 *	* Others: Reserved
	 *	When the core is in LS Host mode
	 *	* 2'b00: PHY घड़ी is running at 30/60 MHz. When the
	 *	UTMI+/ULPI PHY Low Power mode is not selected, use
	 *	30/60 MHz.
	 *	* 2'b01: PHY घड़ी is running at 48 MHz. When the UTMI+
	 *	PHY Low Power mode is selected, use 48MHz अगर the PHY
	 *	supplies a 48 MHz घड़ी during LS mode.
	 *	* 2'b10: PHY घड़ी is running at 6 MHz. In USB 1.1 FS mode,
	 *	use 6 MHz when the UTMI+ PHY Low Power mode is
	 *	selected and the PHY supplies a 6 MHz घड़ी during LS
	 *	mode. If you select a 6 MHz घड़ी during LS mode, you must
	 *	करो a soft reset.
	 *	* 2'b11: Reserved
	 */
	काष्ठा cvmx_usbcx_hcfg_s अणु
		__BITFIELD_FIELD(u32 reserved_3_31	: 29,
		__BITFIELD_FIELD(u32 fslssupp		: 1,
		__BITFIELD_FIELD(u32 fslspclksel	: 2,
		;)))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hcपूर्णांक#
 *
 * Host Channel-n Interrupt Register (HCINT)
 *
 * This रेजिस्टर indicates the status of a channel with respect to USB- and
 * AHB-related events. The application must पढ़ो this रेजिस्टर when the Host
 * Channels Interrupt bit of the Core Interrupt रेजिस्टर (GINTSTS.HChInt) is
 * set. Beक्रमe the application can पढ़ो this रेजिस्टर, it must first पढ़ो
 * the Host All Channels Interrupt (HAINT) रेजिस्टर to get the exact channel
 * number क्रम the Host Channel-n Interrupt रेजिस्टर. The application must clear
 * the appropriate bit in this रेजिस्टर to clear the corresponding bits in the
 * HAINT and GINTSTS रेजिस्टरs.
 */
जोड़ cvmx_usbcx_hcपूर्णांकx अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hcपूर्णांकx_s
	 * @datatglerr: Data Toggle Error (DataTglErr)
	 * @frmovrun: Frame Overrun (FrmOvrun)
	 * @bblerr: Babble Error (BblErr)
	 * @xacterr: Transaction Error (XactErr)
	 * @nyet: NYET Response Received Interrupt (NYET)
	 * @ack: ACK Response Received Interrupt (ACK)
	 * @nak: NAK Response Received Interrupt (NAK)
	 * @stall: STALL Response Received Interrupt (STALL)
	 * @ahberr: This bit is always 0x0.
	 * @chhltd: Channel Halted (ChHltd)
	 *	Indicates the transfer completed abnormally either because of
	 *	any USB transaction error or in response to disable request by
	 *	the application.
	 * @xfercompl: Transfer Completed (XferCompl)
	 *	Transfer completed normally without any errors.
	 */
	काष्ठा cvmx_usbcx_hcपूर्णांकx_s अणु
		__BITFIELD_FIELD(u32 reserved_11_31	: 21,
		__BITFIELD_FIELD(u32 datatglerr		: 1,
		__BITFIELD_FIELD(u32 frmovrun		: 1,
		__BITFIELD_FIELD(u32 bblerr		: 1,
		__BITFIELD_FIELD(u32 xacterr		: 1,
		__BITFIELD_FIELD(u32 nyet		: 1,
		__BITFIELD_FIELD(u32 ack		: 1,
		__BITFIELD_FIELD(u32 nak		: 1,
		__BITFIELD_FIELD(u32 stall		: 1,
		__BITFIELD_FIELD(u32 ahberr		: 1,
		__BITFIELD_FIELD(u32 chhltd		: 1,
		__BITFIELD_FIELD(u32 xfercompl		: 1,
		;))))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hcपूर्णांकmsk#
 *
 * Host Channel-n Interrupt Mask Register (HCINTMSKn)
 *
 * This रेजिस्टर reflects the mask क्रम each channel status described in the
 * previous section.
 * Mask पूर्णांकerrupt: 1'b0 Unmask interrupt: 1'b1
 */
जोड़ cvmx_usbcx_hcपूर्णांकmskx अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hcपूर्णांकmskx_s
	 * @datatglerrmsk: Data Toggle Error Mask (DataTglErrMsk)
	 * @frmovrunmsk: Frame Overrun Mask (FrmOvrunMsk)
	 * @bblerrmsk: Babble Error Mask (BblErrMsk)
	 * @xacterrmsk: Transaction Error Mask (XactErrMsk)
	 * @nyeपंचांगsk: NYET Response Received Interrupt Mask (NyetMsk)
	 * @ackmsk: ACK Response Received Interrupt Mask (AckMsk)
	 * @nakmsk: NAK Response Received Interrupt Mask (NakMsk)
	 * @stallmsk: STALL Response Received Interrupt Mask (StallMsk)
	 * @ahberrmsk: AHB Error Mask (AHBErrMsk)
	 * @chhltdmsk: Channel Halted Mask (ChHltdMsk)
	 * @xfercomplmsk: Transfer Completed Mask (XferComplMsk)
	 */
	काष्ठा cvmx_usbcx_hcपूर्णांकmskx_s अणु
		__BITFIELD_FIELD(u32 reserved_11_31		: 21,
		__BITFIELD_FIELD(u32 datatglerrmsk		: 1,
		__BITFIELD_FIELD(u32 frmovrunmsk		: 1,
		__BITFIELD_FIELD(u32 bblerrmsk			: 1,
		__BITFIELD_FIELD(u32 xacterrmsk			: 1,
		__BITFIELD_FIELD(u32 nyeपंचांगsk			: 1,
		__BITFIELD_FIELD(u32 ackmsk			: 1,
		__BITFIELD_FIELD(u32 nakmsk			: 1,
		__BITFIELD_FIELD(u32 stallmsk			: 1,
		__BITFIELD_FIELD(u32 ahberrmsk			: 1,
		__BITFIELD_FIELD(u32 chhltdmsk			: 1,
		__BITFIELD_FIELD(u32 xfercomplmsk		: 1,
		;))))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hcsplt#
 *
 * Host Channel-n Split Control Register (HCSPLT)
 *
 */
जोड़ cvmx_usbcx_hcspltx अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hcspltx_s
	 * @spltena: Split Enable (SpltEna)
	 *	The application sets this field to indicate that this channel is
	 *	enabled to perक्रमm split transactions.
	 * @compsplt: Do Complete Split (CompSplt)
	 *	The application sets this field to request the OTG host to
	 *	perक्रमm a complete split transaction.
	 * @xactpos: Transaction Position (XactPos)
	 *	This field is used to determine whether to send all, first,
	 *	middle, or last payloads with each OUT transaction.
	 *	* 2'b11: All. This is the entire data payload is of this
	 *	transaction (which is less than or equal to 188 bytes).
	 *	* 2'b10: Begin. This is the first data payload of this
	 *	transaction (which is larger than 188 bytes).
	 *	* 2'b00: Mid. This is the middle payload of this transaction
	 *	(which is larger than 188 bytes).
	 *	* 2'b01: End. This is the last payload of this transaction
	 *	(which is larger than 188 bytes).
	 * @hubaddr: Hub Address (HubAddr)
	 *	This field holds the device address of the transaction
	 *	translator's hub.
	 * @prtaddr: Port Address (PrtAddr)
	 *	This field is the port number of the recipient transaction
	 *	translator.
	 */
	काष्ठा cvmx_usbcx_hcspltx_s अणु
		__BITFIELD_FIELD(u32 spltena			: 1,
		__BITFIELD_FIELD(u32 reserved_17_30		: 14,
		__BITFIELD_FIELD(u32 compsplt			: 1,
		__BITFIELD_FIELD(u32 xactpos			: 2,
		__BITFIELD_FIELD(u32 hubaddr			: 7,
		__BITFIELD_FIELD(u32 prtaddr			: 7,
		;))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hctsiz#
 *
 * Host Channel-n Transfer Size Register (HCTSIZ)
 *
 */
जोड़ cvmx_usbcx_hctsizx अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hctsizx_s
	 * @करोpng: Do Ping (DoPng)
	 *	Setting this field to 1 directs the host to करो PING protocol.
	 * @pid: PID (Pid)
	 *	The application programs this field with the type of PID to use
	 *	क्रम the initial transaction. The host will मुख्यtain this field
	 *	क्रम the rest of the transfer.
	 *	* 2'b00: DATA0
	 *	* 2'b01: DATA2
	 *	* 2'b10: DATA1
	 *	* 2'b11: MDATA (non-control)/SETUP (control)
	 * @pktcnt: Packet Count (PktCnt)
	 *	This field is programmed by the application with the expected
	 *	number of packets to be transmitted (OUT) or received (IN).
	 *	The host decrements this count on every successful
	 *	transmission or reception of an OUT/IN packet. Once this count
	 *	reaches zero, the application is पूर्णांकerrupted to indicate normal
	 *	completion.
	 * @xfersize: Transfer Size (XferSize)
	 *	For an OUT, this field is the number of data bytes the host will
	 *	send during the transfer.
	 *	For an IN, this field is the buffer size that the application
	 *	has reserved क्रम the transfer. The application is expected to
	 *	program this field as an पूर्णांकeger multiple of the maximum packet
	 *	size क्रम IN transactions (periodic and non-periodic).
	 */
	काष्ठा cvmx_usbcx_hctsizx_s अणु
		__BITFIELD_FIELD(u32 करोpng		: 1,
		__BITFIELD_FIELD(u32 pid		: 2,
		__BITFIELD_FIELD(u32 pktcnt		: 10,
		__BITFIELD_FIELD(u32 xfersize		: 19,
		;))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hfir
 *
 * Host Frame Interval Register (HFIR)
 *
 * This रेजिस्टर stores the frame पूर्णांकerval inक्रमmation क्रम the current speed to
 * which the O2P USB core has क्रमागतerated.
 */
जोड़ cvmx_usbcx_hfir अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hfir_s
	 * @frपूर्णांक: Frame Interval (FrInt)
	 *	The value that the application programs to this field specअगरies
	 *	the पूर्णांकerval between two consecutive SOFs (FS) or micro-
	 *	SOFs (HS) or Keep-Alive tokens (HS). This field contains the
	 *	number of PHY घड़ीs that स्थिरitute the required frame
	 *	पूर्णांकerval. The शेष value set in this field क्रम a FS operation
	 *	when the PHY घड़ी frequency is 60 MHz. The application can
	 *	ग_लिखो a value to this रेजिस्टर only after the Port Enable bit of
	 *	the Host Port Control and Status रेजिस्टर (HPRT.PrtEnaPort)
	 *	has been set. If no value is programmed, the core calculates
	 *	the value based on the PHY घड़ी specअगरied in the FS/LS PHY
	 *	Clock Select field of the Host Configuration रेजिस्टर
	 *	(HCFG.FSLSPclkSel). Do not change the value of this field
	 *	after the initial configuration.
	 *	* 125 us (PHY घड़ी frequency क्रम HS)
	 *	* 1 ms (PHY घड़ी frequency क्रम FS/LS)
	 */
	काष्ठा cvmx_usbcx_hfir_s अणु
		__BITFIELD_FIELD(u32 reserved_16_31		: 16,
		__BITFIELD_FIELD(u32 frपूर्णांक			: 16,
		;))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hfnum
 *
 * Host Frame Number/Frame Time Reमुख्यing Register (HFNUM)
 *
 * This रेजिस्टर indicates the current frame number.
 * It also indicates the समय reमुख्यing (in terms of the number of PHY घड़ीs)
 * in the current (micro)frame.
 */
जोड़ cvmx_usbcx_hfnum अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hfnum_s
	 * @frrem: Frame Time Reमुख्यing (FrRem)
	 *	Indicates the amount of समय reमुख्यing in the current
	 *	microframe (HS) or frame (FS/LS), in terms of PHY घड़ीs.
	 *	This field decrements on each PHY घड़ी. When it reaches
	 *	zero, this field is reloaded with the value in the Frame
	 *	Interval रेजिस्टर and a new SOF is transmitted on the USB.
	 * @frnum: Frame Number (FrNum)
	 *	This field increments when a new SOF is transmitted on the
	 *	USB, and is reset to 0 when it reaches 16'h3FFF.
	 */
	काष्ठा cvmx_usbcx_hfnum_s अणु
		__BITFIELD_FIELD(u32 frrem		: 16,
		__BITFIELD_FIELD(u32 frnum		: 16,
		;))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hprt
 *
 * Host Port Control and Status Register (HPRT)
 *
 * This रेजिस्टर is available in both Host and Device modes.
 * Currently, the OTG Host supports only one port.
 * A single रेजिस्टर holds USB port-related inक्रमmation such as USB reset,
 * enable, suspend, resume, connect status, and test mode क्रम each port. The
 * R_SS_WC bits in this रेजिस्टर can trigger an पूर्णांकerrupt to the application
 * through the Host Port Interrupt bit of the Core Interrupt रेजिस्टर
 * (GINTSTS.PrtInt). On a Port Interrupt, the application must पढ़ो this
 * रेजिस्टर and clear the bit that caused the पूर्णांकerrupt. For the R_SS_WC bits,
 * the application must ग_लिखो a 1 to the bit to clear the पूर्णांकerrupt.
 */
जोड़ cvmx_usbcx_hprt अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hprt_s
	 * @prtspd: Port Speed (PrtSpd)
	 *	Indicates the speed of the device attached to this port.
	 *	* 2'b00: High speed
	 *	* 2'b01: Full speed
	 *	* 2'b10: Low speed
	 *	* 2'b11: Reserved
	 * @prttstctl: Port Test Control (PrtTstCtl)
	 *	The application ग_लिखोs a nonzero value to this field to put
	 *	the port पूर्णांकo a Test mode, and the corresponding pattern is
	 *	संकेतed on the port.
	 *	* 4'b0000: Test mode disabled
	 *	* 4'b0001: Test_J mode
	 *	* 4'b0010: Test_K mode
	 *	* 4'b0011: Test_SE0_NAK mode
	 *	* 4'b0100: Test_Packet mode
	 *	* 4'b0101: Test_Force_Enable
	 *	* Others: Reserved
	 *	PrtSpd must be zero (i.e. the पूर्णांकerface must be in high-speed
	 *	mode) to use the PrtTstCtl test modes.
	 * @prtpwr: Port Power (PrtPwr)
	 *	The application uses this field to control घातer to this port,
	 *	and the core clears this bit on an overcurrent condition.
	 *	* 1'b0: Power off
	 *	* 1'b1: Power on
	 * @prtlnsts: Port Line Status (PrtLnSts)
	 *	Indicates the current logic level USB data lines
	 *	* Bit [10]: Logic level of D-
	 *	* Bit [11]: Logic level of D+
	 * @prtrst: Port Reset (PrtRst)
	 *	When the application sets this bit, a reset sequence is
	 *	started on this port. The application must समय the reset
	 *	period and clear this bit after the reset sequence is
	 *	complete.
	 *	* 1'b0: Port not in reset
	 *	* 1'b1: Port in reset
	 *	The application must leave this bit set क्रम at least a
	 *	minimum duration mentioned below to start a reset on the
	 *	port. The application can leave it set क्रम another 10 ms in
	 *	addition to the required minimum duration, beक्रमe clearing
	 *	the bit, even though there is no maximum limit set by the
	 *	USB standard.
	 *	* High speed: 50 ms
	 *	* Full speed/Low speed: 10 ms
	 * @prtsusp: Port Suspend (PrtSusp)
	 *	The application sets this bit to put this port in Suspend
	 *	mode. The core only stops sending SOFs when this is set.
	 *	To stop the PHY घड़ी, the application must set the Port
	 *	Clock Stop bit, which will निश्चित the suspend input pin of
	 *	the PHY.
	 *	The पढ़ो value of this bit reflects the current suspend
	 *	status of the port. This bit is cleared by the core after a
	 *	remote wakeup संकेत is detected or the application sets
	 *	the Port Reset bit or Port Resume bit in this रेजिस्टर or the
	 *	Resume/Remote Wakeup Detected Interrupt bit or
	 *	Disconnect Detected Interrupt bit in the Core Interrupt
	 *	रेजिस्टर (GINTSTS.WkUpInt or GINTSTS.DisconnInt,
	 *	respectively).
	 *	* 1'b0: Port not in Suspend mode
	 *	* 1'b1: Port in Suspend mode
	 * @prtres: Port Resume (PrtRes)
	 *	The application sets this bit to drive resume संकेतing on
	 *	the port. The core जारीs to drive the resume संकेत
	 *	until the application clears this bit.
	 *	If the core detects a USB remote wakeup sequence, as
	 *	indicated by the Port Resume/Remote Wakeup Detected
	 *	Interrupt bit of the Core Interrupt रेजिस्टर
	 *	(GINTSTS.WkUpInt), the core starts driving resume
	 *	संकेतing without application पूर्णांकervention and clears this bit
	 *	when it detects a disconnect condition. The पढ़ो value of
	 *	this bit indicates whether the core is currently driving
	 *	resume संकेतing.
	 *	* 1'b0: No resume driven
	 *	* 1'b1: Resume driven
	 * @prtovrcurrchng: Port Overcurrent Change (PrtOvrCurrChng)
	 *	The core sets this bit when the status of the Port
	 *	Overcurrent Active bit (bit 4) in this रेजिस्टर changes.
	 * @prtovrcurract: Port Overcurrent Active (PrtOvrCurrAct)
	 *	Indicates the overcurrent condition of the port.
	 *	* 1'b0: No overcurrent condition
	 *	* 1'b1: Overcurrent condition
	 * @prtenchng: Port Enable/Disable Change (PrtEnChng)
	 *	The core sets this bit when the status of the Port Enable bit
	 *	[2] of this रेजिस्टर changes.
	 * @prtena: Port Enable (PrtEna)
	 *	A port is enabled only by the core after a reset sequence,
	 *	and is disabled by an overcurrent condition, a disconnect
	 *	condition, or by the application clearing this bit. The
	 *	application cannot set this bit by a रेजिस्टर ग_लिखो. It can only
	 *	clear it to disable the port. This bit करोes not trigger any
	 *	पूर्णांकerrupt to the application.
	 *	* 1'b0: Port disabled
	 *	* 1'b1: Port enabled
	 * @prtconndet: Port Connect Detected (PrtConnDet)
	 *	The core sets this bit when a device connection is detected
	 *	to trigger an पूर्णांकerrupt to the application using the Host Port
	 *	Interrupt bit of the Core Interrupt रेजिस्टर (GINTSTS.PrtInt).
	 *	The application must ग_लिखो a 1 to this bit to clear the
	 *	पूर्णांकerrupt.
	 * @prtconnsts: Port Connect Status (PrtConnSts)
	 *	* 0: No device is attached to the port.
	 *	* 1: A device is attached to the port.
	 */
	काष्ठा cvmx_usbcx_hprt_s अणु
		__BITFIELD_FIELD(u32 reserved_19_31	: 13,
		__BITFIELD_FIELD(u32 prtspd		: 2,
		__BITFIELD_FIELD(u32 prttstctl		: 4,
		__BITFIELD_FIELD(u32 prtpwr		: 1,
		__BITFIELD_FIELD(u32 prtlnsts		: 2,
		__BITFIELD_FIELD(u32 reserved_9_9	: 1,
		__BITFIELD_FIELD(u32 prtrst		: 1,
		__BITFIELD_FIELD(u32 prtsusp		: 1,
		__BITFIELD_FIELD(u32 prtres		: 1,
		__BITFIELD_FIELD(u32 prtovrcurrchng	: 1,
		__BITFIELD_FIELD(u32 prtovrcurract	: 1,
		__BITFIELD_FIELD(u32 prtenchng		: 1,
		__BITFIELD_FIELD(u32 prtena		: 1,
		__BITFIELD_FIELD(u32 prtconndet		: 1,
		__BITFIELD_FIELD(u32 prtconnsts		: 1,
		;)))))))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hptxfsiz
 *
 * Host Periodic Transmit FIFO Size Register (HPTXFSIZ)
 *
 * This रेजिस्टर holds the size and the memory start address of the Periodic
 * TxFIFO, as shown in Figures 310 and 311.
 */
जोड़ cvmx_usbcx_hptxfsiz अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hptxfsiz_s
	 * @ptxfsize: Host Periodic TxFIFO Depth (PTxFSize)
	 *	This value is in terms of 32-bit words.
	 *	* Minimum value is 16
	 *	* Maximum value is 32768
	 * @ptxfstaddr: Host Periodic TxFIFO Start Address (PTxFStAddr)
	 */
	काष्ठा cvmx_usbcx_hptxfsiz_s अणु
		__BITFIELD_FIELD(u32 ptxfsize	: 16,
		__BITFIELD_FIELD(u32 ptxfstaddr	: 16,
		;))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbc#_hptxsts
 *
 * Host Periodic Transmit FIFO/Queue Status Register (HPTXSTS)
 *
 * This पढ़ो-only रेजिस्टर contains the मुक्त space inक्रमmation क्रम the Periodic
 * TxFIFO and the Periodic Transmit Request Queue
 */
जोड़ cvmx_usbcx_hptxsts अणु
	u32 u32;
	/**
	 * काष्ठा cvmx_usbcx_hptxsts_s
	 * @ptxqtop: Top of the Periodic Transmit Request Queue (PTxQTop)
	 *	This indicates the entry in the Periodic Tx Request Queue that
	 *	is currently being processes by the MAC.
	 *	This रेजिस्टर is used क्रम debugging.
	 *	* Bit [31]: Odd/Even (micro)frame
	 *	- 1'b0: send in even (micro)frame
	 *	- 1'b1: send in odd (micro)frame
	 *	* Bits [30:27]: Channel/endpoपूर्णांक number
	 *	* Bits [26:25]: Type
	 *	- 2'b00: IN/OUT
	 *	- 2'b01: Zero-length packet
	 *	- 2'b10: CSPLIT
	 *	- 2'b11: Disable channel command
	 *	* Bit [24]: Terminate (last entry क्रम the selected
	 *	channel/endpoपूर्णांक)
	 * @ptxqspcavail: Periodic Transmit Request Queue Space Available
	 *	(PTxQSpcAvail)
	 *	Indicates the number of मुक्त locations available to be written
	 *	in the Periodic Transmit Request Queue. This queue holds both
	 *	IN and OUT requests.
	 *	* 8'h0: Periodic Transmit Request Queue is full
	 *	* 8'h1: 1 location available
	 *	* 8'h2: 2 locations available
	 *	* n: n locations available (0..8)
	 *	* Others: Reserved
	 * @ptxfspcavail: Periodic Transmit Data FIFO Space Available
	 *		  (PTxFSpcAvail)
	 *	Indicates the number of मुक्त locations available to be written
	 *	to in the Periodic TxFIFO.
	 *	Values are in terms of 32-bit words
	 *	* 16'h0: Periodic TxFIFO is full
	 *	* 16'h1: 1 word available
	 *	* 16'h2: 2 words available
	 *	* 16'hn: n words available (where 0..32768)
	 *	* 16'h8000: 32768 words available
	 *	* Others: Reserved
	 */
	काष्ठा cvmx_usbcx_hptxsts_s अणु
		__BITFIELD_FIELD(u32 ptxqtop		: 8,
		__BITFIELD_FIELD(u32 ptxqspcavail	: 8,
		__BITFIELD_FIELD(u32 ptxfspcavail	: 16,
		;)))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbn#_clk_ctl
 *
 * USBN_CLK_CTL = USBN's Clock Control
 *
 * This रेजिस्टर is used to control the frequency of the hclk and the
 * hreset and phy_rst संकेतs.
 */
जोड़ cvmx_usbnx_clk_ctl अणु
	u64 u64;
	/**
	 * काष्ठा cvmx_usbnx_clk_ctl_s
	 * @भागide2: The 'hclk' used by the USB subप्रणाली is derived
	 *	from the eclk.
	 *	Also see the field DIVIDE. DIVIDE2<1> must currently
	 *	be zero because it is not implemented, so the maximum
	 *	ratio of eclk/hclk is currently 16.
	 *	The actual भागide number क्रम hclk is:
	 *	(DIVIDE2 + 1) * (DIVIDE + 1)
	 * @hclk_rst: When this field is '0' the HCLK-DIVIDER used to
	 *	generate the hclk in the USB Subप्रणाली is held
	 *	in reset. This bit must be set to '0' beक्रमe
	 *	changing the value os DIVIDE in this रेजिस्टर.
	 *	The reset to the HCLK_DIVIDERis also निश्चितed
	 *	when core reset is निश्चितed.
	 * @p_x_on: Force USB-PHY on during suspend.
	 *	'1' USB-PHY XO block is घातered-करोwn during
	 *	suspend.
	 *	'0' USB-PHY XO block is घातered-up during
	 *	suspend.
	 *	The value of this field must be set जबतक POR is
	 *	active.
	 * @p_rtype: PHY reference घड़ी type
	 *	On CN50XX/CN52XX/CN56XX the values are:
	 *		'0' The USB-PHY uses a 12MHz crystal as a घड़ी source
	 *		    at the USB_XO and USB_XI pins.
	 *		'1' Reserved.
	 *		'2' The USB_PHY uses 12/24/48MHz 2.5V board घड़ी at the
	 *		    USB_XO pin. USB_XI should be tied to ground in this
	 *		    हाल.
	 *		'3' Reserved.
	 *	On CN3xxx bits 14 and 15 are p_xenbn and p_rclk and values are:
	 *		'0' Reserved.
	 *		'1' Reserved.
	 *		'2' The PHY PLL uses the XO block output as a reference.
	 *		    The XO block uses an बाह्यal घड़ी supplied on the
	 *		    XO pin. USB_XI should be tied to ground क्रम this
	 *		    usage.
	 *		'3' The XO block uses the घड़ी from a crystal.
	 * @p_com_on: '0' Force USB-PHY XO Bias, Bandgap and PLL to
	 *	reमुख्य घातered in Suspend Mode.
	 *	'1' The USB-PHY XO Bias, Bandgap and PLL are
	 *	घातered करोwn in suspend mode.
	 *	The value of this field must be set जबतक POR is
	 *	active.
	 * @p_c_sel: Phy घड़ी speed select.
	 *	Selects the reference घड़ी / crystal frequency.
	 *	'11': Reserved
	 *	'10': 48 MHz (reserved when a crystal is used)
	 *	'01': 24 MHz (reserved when a crystal is used)
	 *	'00': 12 MHz
	 *	The value of this field must be set जबतक POR is
	 *	active.
	 *	NOTE: अगर a crystal is used as a reference घड़ी,
	 *	this field must be set to 12 MHz.
	 * @cभाग_byp: Used to enable the bypass input to the USB_CLK_DIV.
	 * @sd_mode: Scaleकरोwn mode क्रम the USBC. Control timing events
	 *	in the USBC, क्रम normal operation this must be '0'.
	 * @s_bist: Starts bist on the hclk memories, during the '0'
	 *	to '1' transition.
	 * @por: Power On Reset क्रम the PHY.
	 *	Resets all the PHYS रेजिस्टरs and state machines.
	 * @enable: When '1' allows the generation of the hclk. When
	 *	'0' the hclk will not be generated. SEE DIVIDE
	 *	field of this रेजिस्टर.
	 * @prst: When this field is '0' the reset associated with
	 *	the phy_clk functionality in the USB Subप्रणाली is
	 *	help in reset. This bit should not be set to '1'
	 *	until the समय it takes 6 घड़ीs (hclk or phy_clk,
	 *	whichever is slower) has passed. Under normal
	 *	operation once this bit is set to '1' it should not
	 *	be set to '0'.
	 * @hrst: When this field is '0' the reset associated with
	 *	the hclk functioanlity in the USB Subप्रणाली is
	 *	held in reset.This bit should not be set to '1'
	 *	until 12ms after phy_clk is stable. Under normal
	 *	operation, once this bit is set to '1' it should
	 *	not be set to '0'.
	 * @भागide: The frequency of 'hclk' used by the USB subप्रणाली
	 *	is the eclk frequency भागided by the value of
	 *	(DIVIDE2 + 1) * (DIVIDE + 1), also see the field
	 *	DIVIDE2 of this रेजिस्टर.
	 *	The hclk frequency should be less than 125Mhz.
	 *	After writing a value to this field the SW should
	 *	पढ़ो the field क्रम the value written.
	 *	The ENABLE field of this रेजिस्टर should not be set
	 *	until AFTER this field is set and then पढ़ो.
	 */
	काष्ठा cvmx_usbnx_clk_ctl_s अणु
		__BITFIELD_FIELD(u64 reserved_20_63	: 44,
		__BITFIELD_FIELD(u64 भागide2		: 2,
		__BITFIELD_FIELD(u64 hclk_rst		: 1,
		__BITFIELD_FIELD(u64 p_x_on		: 1,
		__BITFIELD_FIELD(u64 p_rtype		: 2,
		__BITFIELD_FIELD(u64 p_com_on		: 1,
		__BITFIELD_FIELD(u64 p_c_sel		: 2,
		__BITFIELD_FIELD(u64 cभाग_byp		: 1,
		__BITFIELD_FIELD(u64 sd_mode		: 2,
		__BITFIELD_FIELD(u64 s_bist		: 1,
		__BITFIELD_FIELD(u64 por		: 1,
		__BITFIELD_FIELD(u64 enable		: 1,
		__BITFIELD_FIELD(u64 prst		: 1,
		__BITFIELD_FIELD(u64 hrst		: 1,
		__BITFIELD_FIELD(u64 भागide		: 3,
		;)))))))))))))))
	पूर्ण s;
पूर्ण;

/**
 * cvmx_usbn#_usbp_ctl_status
 *
 * USBN_USBP_CTL_STATUS = USBP Control And Status Register
 *
 * Contains general control and status inक्रमmation क्रम the USBN block.
 */
जोड़ cvmx_usbnx_usbp_ctl_status अणु
	u64 u64;
	/**
	 * काष्ठा cvmx_usbnx_usbp_ctl_status_s
	 * @txrisetune: HS Transmitter Rise/Fall Time Adjusपंचांगent
	 * @txvreftune: HS DC Voltage Level Adjusपंचांगent
	 * @txfslstune: FS/LS Source Impedance Adjusपंचांगent
	 * @txhsxvtune: Transmitter High-Speed Crossover Adjusपंचांगent
	 * @sqrxtune: Squelch Threshold Adjusपंचांगent
	 * @compdistune: Disconnect Threshold Adjusपंचांगent
	 * @otgtune: VBUS Valid Threshold Adjusपंचांगent
	 * @otgdisable: OTG Block Disable
	 * @portreset: Per_Port Reset
	 * @drvvbus: Drive VBUS
	 * @lsbist: Low-Speed BIST Enable.
	 * @fsbist: Full-Speed BIST Enable.
	 * @hsbist: High-Speed BIST Enable.
	 * @bist_करोne: PHY Bist Done.
	 *	Asserted at the end of the PHY BIST sequence.
	 * @bist_err: PHY Bist Error.
	 *	Indicates an पूर्णांकernal error was detected during
	 *	the BIST sequence.
	 * @tdata_out: PHY Test Data Out.
	 *	Presents either पूर्णांकernally generated संकेतs or
	 *	test रेजिस्टर contents, based upon the value of
	 *	test_data_out_sel.
	 * @siddq: Drives the USBP (USB-PHY) SIDDQ input.
	 *	Normally should be set to zero.
	 *	When customers have no पूर्णांकent to use USB PHY
	 *	पूर्णांकerface, they should:
	 *	- still provide 3.3V to USB_VDD33, and
	 *	- tie USB_REXT to 3.3V supply, and
	 *	- set USBN*_USBP_CTL_STATUS[SIDDQ]=1
	 * @txpreemphasistune: HS Transmitter Pre-Emphasis Enable
	 * @dma_bmode: When set to 1 the L2C DMA address will be updated
	 *	with byte-counts between packets. When set to 0
	 *	the L2C DMA address is incremented to the next
	 *	4-byte aligned address after adding byte-count.
	 * @usbc_end: Bigendian input to the USB Core. This should be
	 *	set to '0' क्रम operation.
	 * @usbp_bist: PHY, This is cleared '0' to run BIST on the USBP.
	 * @tclk: PHY Test Clock, used to load TDATA_IN to the USBP.
	 * @dp_pulld: PHY DP_PULLDOWN input to the USB-PHY.
	 *	This संकेत enables the pull-करोwn resistance on
	 *	the D+ line. '1' pull करोwn-resistance is connected
	 *	to D+/ '0' pull करोwn resistance is not connected
	 *	to D+. When an A/B device is acting as a host
	 *	(करोwnstream-facing port), dp_pullकरोwn and
	 *	dm_pullकरोwn are enabled. This must not toggle
	 *	during normal operation.
	 * @dm_pulld: PHY DM_PULLDOWN input to the USB-PHY.
	 *	This संकेत enables the pull-करोwn resistance on
	 *	the D- line. '1' pull करोwn-resistance is connected
	 *	to D-. '0' pull करोwn resistance is not connected
	 *	to D-. When an A/B device is acting as a host
	 *	(करोwnstream-facing port), dp_pullकरोwn and
	 *	dm_pullकरोwn are enabled. This must not toggle
	 *	during normal operation.
	 * @hst_mode: When '0' the USB is acting as HOST, when '1'
	 *	USB is acting as device. This field needs to be
	 *	set जबतक the USB is in reset.
	 * @tuning: Transmitter Tuning क्रम High-Speed Operation.
	 *	Tunes the current supply and rise/fall output
	 *	बार क्रम high-speed operation.
	 *	[20:19] == 11: Current supply increased
	 *	approximately 9%
	 *	[20:19] == 10: Current supply increased
	 *	approximately 4.5%
	 *	[20:19] == 01: Design शेष.
	 *	[20:19] == 00: Current supply decreased
	 *	approximately 4.5%
	 *	[22:21] == 11: Rise and fall बार are increased.
	 *	[22:21] == 10: Design शेष.
	 *	[22:21] == 01: Rise and fall बार are decreased.
	 *	[22:21] == 00: Rise and fall बार are decreased
	 *	further as compared to the 01 setting.
	 * @tx_bs_enh: Transmit Bit Stuffing on [15:8].
	 *	Enables or disables bit stuffing on data[15:8]
	 *	when bit-stuffing is enabled.
	 * @tx_bs_en: Transmit Bit Stuffing on [7:0].
	 *	Enables or disables bit stuffing on data[7:0]
	 *	when bit-stuffing is enabled.
	 * @loop_enb: PHY Loopback Test Enable.
	 *	'1': During data transmission the receive is
	 *	enabled.
	 *	'0': During data transmission the receive is
	 *	disabled.
	 *	Must be '0' क्रम normal operation.
	 * @vtest_enb: Analog Test Pin Enable.
	 *	'1' The PHY's analog_test pin is enabled क्रम the
	 *	input and output of applicable analog test संकेतs.
	 *	'0' THe analog_test pin is disabled.
	 * @bist_enb: Built-In Self Test Enable.
	 *	Used to activate BIST in the PHY.
	 * @tdata_sel: Test Data Out Select.
	 *	'1' test_data_out[3:0] (PHY) रेजिस्टर contents
	 *	are output. '0' पूर्णांकernally generated संकेतs are
	 *	output.
	 * @taddr_in: Mode Address क्रम Test Interface.
	 *	Specअगरies the रेजिस्टर address क्रम writing to or
	 *	पढ़ोing from the PHY test पूर्णांकerface रेजिस्टर.
	 * @tdata_in: Internal Testing Register Input Data and Select
	 *	This is a test bus. Data is present on [3:0],
	 *	and its corresponding select (enable) is present
	 *	on bits [7:4].
	 * @ate_reset: Reset input from स्वतःmatic test equipment.
	 *	This is a test संकेत. When the USB Core is
	 *	घातered up (not in Susned Mode), an स्वतःmatic
	 *	tester can use this to disable phy_घड़ी and
	 *	मुक्त_clk, then re-enable them with an aligned
	 *	phase.
	 *	'1': The phy_clk and मुक्त_clk outमाला_दो are
	 *	disabled. "0": The phy_घड़ी and मुक्त_clk outमाला_दो
	 *	are available within a specअगरic period after the
	 *	de-निश्चितion.
	 */
	काष्ठा cvmx_usbnx_usbp_ctl_status_s अणु
		__BITFIELD_FIELD(u64 txrisetune		: 1,
		__BITFIELD_FIELD(u64 txvreftune		: 4,
		__BITFIELD_FIELD(u64 txfslstune		: 4,
		__BITFIELD_FIELD(u64 txhsxvtune		: 2,
		__BITFIELD_FIELD(u64 sqrxtune		: 3,
		__BITFIELD_FIELD(u64 compdistune	: 3,
		__BITFIELD_FIELD(u64 otgtune		: 3,
		__BITFIELD_FIELD(u64 otgdisable		: 1,
		__BITFIELD_FIELD(u64 portreset		: 1,
		__BITFIELD_FIELD(u64 drvvbus		: 1,
		__BITFIELD_FIELD(u64 lsbist		: 1,
		__BITFIELD_FIELD(u64 fsbist		: 1,
		__BITFIELD_FIELD(u64 hsbist		: 1,
		__BITFIELD_FIELD(u64 bist_करोne		: 1,
		__BITFIELD_FIELD(u64 bist_err		: 1,
		__BITFIELD_FIELD(u64 tdata_out		: 4,
		__BITFIELD_FIELD(u64 siddq		: 1,
		__BITFIELD_FIELD(u64 txpreemphasistune	: 1,
		__BITFIELD_FIELD(u64 dma_bmode		: 1,
		__BITFIELD_FIELD(u64 usbc_end		: 1,
		__BITFIELD_FIELD(u64 usbp_bist		: 1,
		__BITFIELD_FIELD(u64 tclk		: 1,
		__BITFIELD_FIELD(u64 dp_pulld		: 1,
		__BITFIELD_FIELD(u64 dm_pulld		: 1,
		__BITFIELD_FIELD(u64 hst_mode		: 1,
		__BITFIELD_FIELD(u64 tuning		: 4,
		__BITFIELD_FIELD(u64 tx_bs_enh		: 1,
		__BITFIELD_FIELD(u64 tx_bs_en		: 1,
		__BITFIELD_FIELD(u64 loop_enb		: 1,
		__BITFIELD_FIELD(u64 vtest_enb		: 1,
		__BITFIELD_FIELD(u64 bist_enb		: 1,
		__BITFIELD_FIELD(u64 tdata_sel		: 1,
		__BITFIELD_FIELD(u64 taddr_in		: 4,
		__BITFIELD_FIELD(u64 tdata_in		: 8,
		__BITFIELD_FIELD(u64 ate_reset		: 1,
		;)))))))))))))))))))))))))))))))))))
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर /* __OCTEON_HCD_H__ */
