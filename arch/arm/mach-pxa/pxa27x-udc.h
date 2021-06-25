<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARCH_PXA27X_UDC_H
#घोषणा _ASM_ARCH_PXA27X_UDC_H

#अगर_घोषित _ASM_ARCH_PXA25X_UDC_H
#त्रुटि You cannot include both PXA25x and PXA27x UDC support
#पूर्ण_अगर

#घोषणा UDCCR           __REG(0x40600000) /* UDC Control Register */
#घोषणा UDCCR_OEN	(1 << 31)	/* On-the-Go Enable */
#घोषणा UDCCR_AALTHNP	(1 << 30)	/* A-device Alternate Host Negotiation
					   Protocol Port Support */
#घोषणा UDCCR_AHNP	(1 << 29)	/* A-device Host Negotiation Protocol
					   Support */
#घोषणा UDCCR_BHNP	(1 << 28)	/* B-device Host Negotiation Protocol
					   Enable */
#घोषणा UDCCR_DWRE	(1 << 16)	/* Device Remote Wake-up Enable */
#घोषणा UDCCR_ACN	(0x03 << 11)	/* Active UDC configuration Number */
#घोषणा UDCCR_ACN_S	11
#घोषणा UDCCR_AIN	(0x07 << 8)	/* Active UDC पूर्णांकerface Number */
#घोषणा UDCCR_AIN_S	8
#घोषणा UDCCR_AAISN	(0x07 << 5)	/* Active UDC Alternate Interface
					   Setting Number */
#घोषणा UDCCR_AAISN_S	5
#घोषणा UDCCR_SMAC	(1 << 4)	/* Switch Endpoपूर्णांक Memory to Active
					   Configuration */
#घोषणा UDCCR_EMCE	(1 << 3)	/* Endpoपूर्णांक Memory Configuration
					   Error */
#घोषणा UDCCR_UDR	(1 << 2)	/* UDC Resume */
#घोषणा UDCCR_UDA	(1 << 1)	/* UDC Active */
#घोषणा UDCCR_UDE	(1 << 0)	/* UDC Enable */

#घोषणा UDCICR0         __REG(0x40600004) /* UDC Interrupt Control Register0 */
#घोषणा UDCICR1         __REG(0x40600008) /* UDC Interrupt Control Register1 */
#घोषणा UDCICR_FIFOERR	(1 << 1)	/* FIFO Error पूर्णांकerrupt क्रम EP */
#घोषणा UDCICR_PKTCOMPL (1 << 0)	/* Packet Complete पूर्णांकerrupt क्रम EP */

#घोषणा UDC_INT_FIFOERROR  (0x2)
#घोषणा UDC_INT_PACKETCMP  (0x1)

#घोषणा UDCICR_INT(n,पूर्णांकr) (((पूर्णांकr) & 0x03) << (((n) & 0x0F) * 2))
#घोषणा UDCICR1_IECC	(1 << 31)	/* IntEn - Configuration Change */
#घोषणा UDCICR1_IESOF	(1 << 30)	/* IntEn - Start of Frame */
#घोषणा UDCICR1_IERU	(1 << 29)	/* IntEn - Resume */
#घोषणा UDCICR1_IESU	(1 << 28)	/* IntEn - Suspend */
#घोषणा UDCICR1_IERS	(1 << 27)	/* IntEn - Reset */

#घोषणा UDCISR0         __REG(0x4060000C) /* UDC Interrupt Status Register 0 */
#घोषणा UDCISR1         __REG(0x40600010) /* UDC Interrupt Status Register 1 */
#घोषणा UDCISR_INT(n,पूर्णांकr) (((पूर्णांकr) & 0x03) << (((n) & 0x0F) * 2))
#घोषणा UDCISR1_IRCC	(1 << 31)	/* IntReq - Configuration Change */
#घोषणा UDCISR1_IRSOF	(1 << 30)	/* IntReq - Start of Frame */
#घोषणा UDCISR1_IRRU	(1 << 29)	/* IntReq - Resume */
#घोषणा UDCISR1_IRSU	(1 << 28)	/* IntReq - Suspend */
#घोषणा UDCISR1_IRRS	(1 << 27)	/* IntReq - Reset */

#घोषणा UDCFNR          __REG(0x40600014) /* UDC Frame Number Register */
#घोषणा UDCOTGICR	__REG(0x40600018) /* UDC On-The-Go पूर्णांकerrupt control */
#घोषणा UDCOTGICR_IESF	(1 << 24)	/* OTG SET_FEATURE command recvd */
#घोषणा UDCOTGICR_IEXR	(1 << 17)	/* Extra Transceiver Interrupt
					   Rising Edge Interrupt Enable */
#घोषणा UDCOTGICR_IEXF	(1 << 16)	/* Extra Transceiver Interrupt
					   Falling Edge Interrupt Enable */
#घोषणा UDCOTGICR_IEVV40R (1 << 9)	/* OTG Vbus Valid 4.0V Rising Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IEVV40F (1 << 8)	/* OTG Vbus Valid 4.0V Falling Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IEVV44R (1 << 7)	/* OTG Vbus Valid 4.4V Rising Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IEVV44F (1 << 6)	/* OTG Vbus Valid 4.4V Falling Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IESVR	(1 << 5)	/* OTG Session Valid Rising Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IESVF	(1 << 4)	/* OTG Session Valid Falling Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IESDR	(1 << 3)	/* OTG A-Device SRP Detect Rising
					   Edge Interrupt Enable */
#घोषणा UDCOTGICR_IESDF	(1 << 2)	/* OTG A-Device SRP Detect Falling
					   Edge Interrupt Enable */
#घोषणा UDCOTGICR_IEIDR	(1 << 1)	/* OTG ID Change Rising Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IEIDF	(1 << 0)	/* OTG ID Change Falling Edge
					   Interrupt Enable */

#घोषणा UP2OCR		  __REG(0x40600020)  /* USB Port 2 Output Control रेजिस्टर */
#घोषणा UP3OCR		  __REG(0x40600024)  /* USB Port 2 Output Control रेजिस्टर */

#घोषणा UP2OCR_CPVEN	(1 << 0)	/* Charge Pump Vbus Enable */
#घोषणा UP2OCR_CPVPE	(1 << 1)	/* Charge Pump Vbus Pulse Enable */
#घोषणा UP2OCR_DPPDE	(1 << 2)	/* Host Port 2 Transceiver D+ Pull Down Enable */
#घोषणा UP2OCR_DMPDE	(1 << 3)	/* Host Port 2 Transceiver D- Pull Down Enable */
#घोषणा UP2OCR_DPPUE	(1 << 4)	/* Host Port 2 Transceiver D+ Pull Up Enable */
#घोषणा UP2OCR_DMPUE	(1 << 5)	/* Host Port 2 Transceiver D- Pull Up Enable */
#घोषणा UP2OCR_DPPUBE	(1 << 6)	/* Host Port 2 Transceiver D+ Pull Up Bypass Enable */
#घोषणा UP2OCR_DMPUBE	(1 << 7)	/* Host Port 2 Transceiver D- Pull Up Bypass Enable */
#घोषणा UP2OCR_EXSP		(1 << 8)	/* External Transceiver Speed Control */
#घोषणा UP2OCR_EXSUS	(1 << 9)	/* External Transceiver Speed Enable */
#घोषणा UP2OCR_IDON		(1 << 10)	/* OTG ID Read Enable */
#घोषणा UP2OCR_HXS		(1 << 16)	/* Host Port 2 Transceiver Output Select */
#घोषणा UP2OCR_HXOE		(1 << 17)	/* Host Port 2 Transceiver Output Enable */
#घोषणा UP2OCR_SEOS(x)		((x & 7) << 24)	/* Single-Ended Output Select */

#घोषणा UDCCSN(x)	__REG2(0x40600100, (x) << 2)
#घोषणा UDCCSR0         __REG(0x40600100) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक 0 */
#घोषणा UDCCSR0_SA	(1 << 7)	/* Setup Active */
#घोषणा UDCCSR0_RNE	(1 << 6)	/* Receive FIFO Not Empty */
#घोषणा UDCCSR0_FST	(1 << 5)	/* Force Stall */
#घोषणा UDCCSR0_SST	(1 << 4)	/* Sent Stall */
#घोषणा UDCCSR0_DME	(1 << 3)	/* DMA Enable */
#घोषणा UDCCSR0_FTF	(1 << 2)	/* Flush Transmit FIFO */
#घोषणा UDCCSR0_IPR	(1 << 1)	/* IN Packet Ready */
#घोषणा UDCCSR0_OPC	(1 << 0)	/* OUT Packet Complete */

#घोषणा UDCCSRA         __REG(0x40600104) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक A */
#घोषणा UDCCSRB         __REG(0x40600108) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक B */
#घोषणा UDCCSRC         __REG(0x4060010C) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक C */
#घोषणा UDCCSRD         __REG(0x40600110) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक D */
#घोषणा UDCCSRE         __REG(0x40600114) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक E */
#घोषणा UDCCSRF         __REG(0x40600118) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक F */
#घोषणा UDCCSRG         __REG(0x4060011C) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक G */
#घोषणा UDCCSRH         __REG(0x40600120) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक H */
#घोषणा UDCCSRI         __REG(0x40600124) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक I */
#घोषणा UDCCSRJ         __REG(0x40600128) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक J */
#घोषणा UDCCSRK         __REG(0x4060012C) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक K */
#घोषणा UDCCSRL         __REG(0x40600130) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक L */
#घोषणा UDCCSRM         __REG(0x40600134) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक M */
#घोषणा UDCCSRN         __REG(0x40600138) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक N */
#घोषणा UDCCSRP         __REG(0x4060013C) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक P */
#घोषणा UDCCSRQ         __REG(0x40600140) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक Q */
#घोषणा UDCCSRR         __REG(0x40600144) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक R */
#घोषणा UDCCSRS         __REG(0x40600148) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक S */
#घोषणा UDCCSRT         __REG(0x4060014C) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक T */
#घोषणा UDCCSRU         __REG(0x40600150) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक U */
#घोषणा UDCCSRV         __REG(0x40600154) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक V */
#घोषणा UDCCSRW         __REG(0x40600158) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक W */
#घोषणा UDCCSRX         __REG(0x4060015C) /* UDC Control/Status रेजिस्टर - Endpoपूर्णांक X */

#घोषणा UDCCSR_DPE	(1 << 9)	/* Data Packet Error */
#घोषणा UDCCSR_FEF	(1 << 8)	/* Flush Endpoपूर्णांक FIFO */
#घोषणा UDCCSR_SP	(1 << 7)	/* Short Packet Control/Status */
#घोषणा UDCCSR_BNE	(1 << 6)	/* Buffer Not Empty (IN endpoपूर्णांकs) */
#घोषणा UDCCSR_BNF	(1 << 6)	/* Buffer Not Full (OUT endpoपूर्णांकs) */
#घोषणा UDCCSR_FST	(1 << 5)	/* Force STALL */
#घोषणा UDCCSR_SST	(1 << 4)	/* Sent STALL */
#घोषणा UDCCSR_DME	(1 << 3)	/* DMA Enable */
#घोषणा UDCCSR_TRN	(1 << 2)	/* Tx/Rx NAK */
#घोषणा UDCCSR_PC	(1 << 1)	/* Packet Complete */
#घोषणा UDCCSR_FS	(1 << 0)	/* FIFO needs service */

#घोषणा UDCBCN(x)	__REG2(0x40600200, (x)<<2)
#घोषणा UDCBCR0         __REG(0x40600200) /* Byte Count Register - EP0 */
#घोषणा UDCBCRA         __REG(0x40600204) /* Byte Count Register - EPA */
#घोषणा UDCBCRB         __REG(0x40600208) /* Byte Count Register - EPB */
#घोषणा UDCBCRC         __REG(0x4060020C) /* Byte Count Register - EPC */
#घोषणा UDCBCRD         __REG(0x40600210) /* Byte Count Register - EPD */
#घोषणा UDCBCRE         __REG(0x40600214) /* Byte Count Register - EPE */
#घोषणा UDCBCRF         __REG(0x40600218) /* Byte Count Register - EPF */
#घोषणा UDCBCRG         __REG(0x4060021C) /* Byte Count Register - EPG */
#घोषणा UDCBCRH         __REG(0x40600220) /* Byte Count Register - EPH */
#घोषणा UDCBCRI         __REG(0x40600224) /* Byte Count Register - EPI */
#घोषणा UDCBCRJ         __REG(0x40600228) /* Byte Count Register - EPJ */
#घोषणा UDCBCRK         __REG(0x4060022C) /* Byte Count Register - EPK */
#घोषणा UDCBCRL         __REG(0x40600230) /* Byte Count Register - EPL */
#घोषणा UDCBCRM         __REG(0x40600234) /* Byte Count Register - EPM */
#घोषणा UDCBCRN         __REG(0x40600238) /* Byte Count Register - EPN */
#घोषणा UDCBCRP         __REG(0x4060023C) /* Byte Count Register - EPP */
#घोषणा UDCBCRQ         __REG(0x40600240) /* Byte Count Register - EPQ */
#घोषणा UDCBCRR         __REG(0x40600244) /* Byte Count Register - EPR */
#घोषणा UDCBCRS         __REG(0x40600248) /* Byte Count Register - EPS */
#घोषणा UDCBCRT         __REG(0x4060024C) /* Byte Count Register - EPT */
#घोषणा UDCBCRU         __REG(0x40600250) /* Byte Count Register - EPU */
#घोषणा UDCBCRV         __REG(0x40600254) /* Byte Count Register - EPV */
#घोषणा UDCBCRW         __REG(0x40600258) /* Byte Count Register - EPW */
#घोषणा UDCBCRX         __REG(0x4060025C) /* Byte Count Register - EPX */

#घोषणा UDCDN(x)	__REG2(0x40600300, (x)<<2)
#घोषणा PHYS_UDCDN(x)	(0x40600300 + ((x)<<2))
#घोषणा PUDCDN(x)	(अस्थिर u32 *)(io_p2v(PHYS_UDCDN((x))))
#घोषणा UDCDR0          __REG(0x40600300) /* Data Register - EP0 */
#घोषणा UDCDRA          __REG(0x40600304) /* Data Register - EPA */
#घोषणा UDCDRB          __REG(0x40600308) /* Data Register - EPB */
#घोषणा UDCDRC          __REG(0x4060030C) /* Data Register - EPC */
#घोषणा UDCDRD          __REG(0x40600310) /* Data Register - EPD */
#घोषणा UDCDRE          __REG(0x40600314) /* Data Register - EPE */
#घोषणा UDCDRF          __REG(0x40600318) /* Data Register - EPF */
#घोषणा UDCDRG          __REG(0x4060031C) /* Data Register - EPG */
#घोषणा UDCDRH          __REG(0x40600320) /* Data Register - EPH */
#घोषणा UDCDRI          __REG(0x40600324) /* Data Register - EPI */
#घोषणा UDCDRJ          __REG(0x40600328) /* Data Register - EPJ */
#घोषणा UDCDRK          __REG(0x4060032C) /* Data Register - EPK */
#घोषणा UDCDRL          __REG(0x40600330) /* Data Register - EPL */
#घोषणा UDCDRM          __REG(0x40600334) /* Data Register - EPM */
#घोषणा UDCDRN          __REG(0x40600338) /* Data Register - EPN */
#घोषणा UDCDRP          __REG(0x4060033C) /* Data Register - EPP */
#घोषणा UDCDRQ          __REG(0x40600340) /* Data Register - EPQ */
#घोषणा UDCDRR          __REG(0x40600344) /* Data Register - EPR */
#घोषणा UDCDRS          __REG(0x40600348) /* Data Register - EPS */
#घोषणा UDCDRT          __REG(0x4060034C) /* Data Register - EPT */
#घोषणा UDCDRU          __REG(0x40600350) /* Data Register - EPU */
#घोषणा UDCDRV          __REG(0x40600354) /* Data Register - EPV */
#घोषणा UDCDRW          __REG(0x40600358) /* Data Register - EPW */
#घोषणा UDCDRX          __REG(0x4060035C) /* Data Register - EPX */

#घोषणा UDCCN(x)       __REG2(0x40600400, (x)<<2)
#घोषणा UDCCRA          __REG(0x40600404) /* Configuration रेजिस्टर EPA */
#घोषणा UDCCRB          __REG(0x40600408) /* Configuration रेजिस्टर EPB */
#घोषणा UDCCRC          __REG(0x4060040C) /* Configuration रेजिस्टर EPC */
#घोषणा UDCCRD          __REG(0x40600410) /* Configuration रेजिस्टर EPD */
#घोषणा UDCCRE          __REG(0x40600414) /* Configuration रेजिस्टर EPE */
#घोषणा UDCCRF          __REG(0x40600418) /* Configuration रेजिस्टर EPF */
#घोषणा UDCCRG          __REG(0x4060041C) /* Configuration रेजिस्टर EPG */
#घोषणा UDCCRH          __REG(0x40600420) /* Configuration रेजिस्टर EPH */
#घोषणा UDCCRI          __REG(0x40600424) /* Configuration रेजिस्टर EPI */
#घोषणा UDCCRJ          __REG(0x40600428) /* Configuration रेजिस्टर EPJ */
#घोषणा UDCCRK          __REG(0x4060042C) /* Configuration रेजिस्टर EPK */
#घोषणा UDCCRL          __REG(0x40600430) /* Configuration रेजिस्टर EPL */
#घोषणा UDCCRM          __REG(0x40600434) /* Configuration रेजिस्टर EPM */
#घोषणा UDCCRN          __REG(0x40600438) /* Configuration रेजिस्टर EPN */
#घोषणा UDCCRP          __REG(0x4060043C) /* Configuration रेजिस्टर EPP */
#घोषणा UDCCRQ          __REG(0x40600440) /* Configuration रेजिस्टर EPQ */
#घोषणा UDCCRR          __REG(0x40600444) /* Configuration रेजिस्टर EPR */
#घोषणा UDCCRS          __REG(0x40600448) /* Configuration रेजिस्टर EPS */
#घोषणा UDCCRT          __REG(0x4060044C) /* Configuration रेजिस्टर EPT */
#घोषणा UDCCRU          __REG(0x40600450) /* Configuration रेजिस्टर EPU */
#घोषणा UDCCRV          __REG(0x40600454) /* Configuration रेजिस्टर EPV */
#घोषणा UDCCRW          __REG(0x40600458) /* Configuration रेजिस्टर EPW */
#घोषणा UDCCRX          __REG(0x4060045C) /* Configuration रेजिस्टर EPX */

#घोषणा UDCCONR_CN	(0x03 << 25)	/* Configuration Number */
#घोषणा UDCCONR_CN_S	(25)
#घोषणा UDCCONR_IN	(0x07 << 22)	/* Interface Number */
#घोषणा UDCCONR_IN_S	(22)
#घोषणा UDCCONR_AISN	(0x07 << 19)	/* Alternate Interface Number */
#घोषणा UDCCONR_AISN_S	(19)
#घोषणा UDCCONR_EN	(0x0f << 15)	/* Endpoपूर्णांक Number */
#घोषणा UDCCONR_EN_S	(15)
#घोषणा UDCCONR_ET	(0x03 << 13)	/* Endpoपूर्णांक Type: */
#घोषणा UDCCONR_ET_S	(13)
#घोषणा UDCCONR_ET_INT	(0x03 << 13)	/*   Interrupt */
#घोषणा UDCCONR_ET_BULK	(0x02 << 13)	/*   Bulk */
#घोषणा UDCCONR_ET_ISO	(0x01 << 13)	/*   Isochronous */
#घोषणा UDCCONR_ET_NU	(0x00 << 13)	/*   Not used */
#घोषणा UDCCONR_ED	(1 << 12)	/* Endpoपूर्णांक Direction */
#घोषणा UDCCONR_MPS	(0x3ff << 2)	/* Maximum Packet Size */
#घोषणा UDCCONR_MPS_S	(2)
#घोषणा UDCCONR_DE	(1 << 1)	/* Double Buffering Enable */
#घोषणा UDCCONR_EE	(1 << 0)	/* Endpoपूर्णांक Enable */


#घोषणा UDC_INT_FIFOERROR  (0x2)
#घोषणा UDC_INT_PACKETCMP  (0x1)

#घोषणा UDC_FNR_MASK     (0x7ff)

#घोषणा UDCCSR_WR_MASK   (UDCCSR_DME|UDCCSR_FST)
#घोषणा UDC_BCR_MASK    (0x3ff)

#पूर्ण_अगर
