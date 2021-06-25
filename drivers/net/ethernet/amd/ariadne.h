<शैली गुरु>
/*
 *  Amiga Linux/m68k Ariadne Ethernet Driver
 *
 *  तऊ Copyright 1995 by Geert Uytterhoeven (geert@linux-m68k.org)
 *			Peter De Schrijver
 *		       (Peter.DeSchrijver@linux.cc.kuleuven.ac.be)
 *
 *  ----------------------------------------------------------------------------------
 *
 *  This program is based on
 *
 *	lance.c:	An AMD LANCE ethernet driver क्रम linux.
 *			Written 1993-94 by Donald Becker.
 *
 *	Am79C960:	PCnet(पंचांग)-ISA Single-Chip Ethernet Controller
 *			Advanced Micro Devices
 *			Publication #16907, Rev. B, Amendment/0, May 1994
 *
 *	MC68230:	Parallel Interface/Timer (PI/T)
 *			Motorola Semiconductors, December, 1983
 *
 *  ----------------------------------------------------------------------------------
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of the Linux
 *  distribution क्रम more details.
 *
 *  ----------------------------------------------------------------------------------
 *
 *  The Ariadne is a Zorro-II board made by Village Tronic. It contains:
 *
 *	- an Am79C960 PCnet-ISA Single-Chip Ethernet Controller with both
 *	  10BASE-2 (thin coax) and 10BASE-T (UTP) connectors
 *
 *	- an MC68230 Parallel Interface/Timer configured as 2 parallel ports
 */


    /*
     *	Am79C960 PCnet-ISA
     */

काष्ठा Am79C960 अणु
    अस्थिर u_लघु AddressPROM[8];
				/* IEEE Address PROM (Unused in the Ariadne) */
    अस्थिर u_लघु RDP;	/* Register Data Port */
    अस्थिर u_लघु RAP;	/* Register Address Port */
    अस्थिर u_लघु Reset;	/* Reset Chip on Read Access */
    अस्थिर u_लघु IDP;	/* ISACSR Data Port */
पूर्ण;


    /*
     *	Am79C960 Control and Status Registers
     *
     *	These values are alपढ़ोy swap()ed!!
     *
     *	Only रेजिस्टरs marked with a `-' are पूर्णांकended क्रम network software
     *	access
     */

#घोषणा CSR0		0x0000	/* - PCnet-ISA Controller Status */
#घोषणा CSR1		0x0100	/* - IADR[15:0] */
#घोषणा CSR2		0x0200	/* - IADR[23:16] */
#घोषणा CSR3		0x0300	/* - Interrupt Masks and Deferral Control */
#घोषणा CSR4		0x0400	/* - Test and Features Control */
#घोषणा CSR6		0x0600	/*   RCV/XMT Descriptor Table Length */
#घोषणा CSR8		0x0800	/* - Logical Address Filter, LADRF[15:0] */
#घोषणा CSR9		0x0900	/* - Logical Address Filter, LADRF[31:16] */
#घोषणा CSR10		0x0a00	/* - Logical Address Filter, LADRF[47:32] */
#घोषणा CSR11		0x0b00	/* - Logical Address Filter, LADRF[63:48] */
#घोषणा CSR12		0x0c00	/* - Physical Address Register, PADR[15:0] */
#घोषणा CSR13		0x0d00	/* - Physical Address Register, PADR[31:16] */
#घोषणा CSR14		0x0e00	/* - Physical Address Register, PADR[47:32] */
#घोषणा CSR15		0x0f00	/* - Mode Register */
#घोषणा CSR16		0x1000	/*   Initialization Block Address Lower */
#घोषणा CSR17		0x1100	/*   Initialization Block Address Upper */
#घोषणा CSR18		0x1200	/*   Current Receive Buffer Address */
#घोषणा CSR19		0x1300	/*   Current Receive Buffer Address */
#घोषणा CSR20		0x1400	/*   Current Transmit Buffer Address */
#घोषणा CSR21		0x1500	/*   Current Transmit Buffer Address */
#घोषणा CSR22		0x1600	/*   Next Receive Buffer Address */
#घोषणा CSR23		0x1700	/*   Next Receive Buffer Address */
#घोषणा CSR24		0x1800	/* - Base Address of Receive Ring */
#घोषणा CSR25		0x1900	/* - Base Address of Receive Ring */
#घोषणा CSR26		0x1a00	/*   Next Receive Descriptor Address */
#घोषणा CSR27		0x1b00	/*   Next Receive Descriptor Address */
#घोषणा CSR28		0x1c00	/*   Current Receive Descriptor Address */
#घोषणा CSR29		0x1d00	/*   Current Receive Descriptor Address */
#घोषणा CSR30		0x1e00	/* - Base Address of Transmit Ring */
#घोषणा CSR31		0x1f00	/* - Base Address of transmit Ring */
#घोषणा CSR32		0x2000	/*   Next Transmit Descriptor Address */
#घोषणा CSR33		0x2100	/*   Next Transmit Descriptor Address */
#घोषणा CSR34		0x2200	/*   Current Transmit Descriptor Address */
#घोषणा CSR35		0x2300	/*   Current Transmit Descriptor Address */
#घोषणा CSR36		0x2400	/*   Next Next Receive Descriptor Address */
#घोषणा CSR37		0x2500	/*   Next Next Receive Descriptor Address */
#घोषणा CSR38		0x2600	/*   Next Next Transmit Descriptor Address */
#घोषणा CSR39		0x2700	/*   Next Next Transmit Descriptor Address */
#घोषणा CSR40		0x2800	/*   Current Receive Status and Byte Count */
#घोषणा CSR41		0x2900	/*   Current Receive Status and Byte Count */
#घोषणा CSR42		0x2a00	/*   Current Transmit Status and Byte Count */
#घोषणा CSR43		0x2b00	/*   Current Transmit Status and Byte Count */
#घोषणा CSR44		0x2c00	/*   Next Receive Status and Byte Count */
#घोषणा CSR45		0x2d00	/*   Next Receive Status and Byte Count */
#घोषणा CSR46		0x2e00	/*   Poll Time Counter */
#घोषणा CSR47		0x2f00	/*   Polling Interval */
#घोषणा CSR48		0x3000	/*   Temporary Storage */
#घोषणा CSR49		0x3100	/*   Temporary Storage */
#घोषणा CSR50		0x3200	/*   Temporary Storage */
#घोषणा CSR51		0x3300	/*   Temporary Storage */
#घोषणा CSR52		0x3400	/*   Temporary Storage */
#घोषणा CSR53		0x3500	/*   Temporary Storage */
#घोषणा CSR54		0x3600	/*   Temporary Storage */
#घोषणा CSR55		0x3700	/*   Temporary Storage */
#घोषणा CSR56		0x3800	/*   Temporary Storage */
#घोषणा CSR57		0x3900	/*   Temporary Storage */
#घोषणा CSR58		0x3a00	/*   Temporary Storage */
#घोषणा CSR59		0x3b00	/*   Temporary Storage */
#घोषणा CSR60		0x3c00	/*   Previous Transmit Descriptor Address */
#घोषणा CSR61		0x3d00	/*   Previous Transmit Descriptor Address */
#घोषणा CSR62		0x3e00	/*   Previous Transmit Status and Byte Count */
#घोषणा CSR63		0x3f00	/*   Previous Transmit Status and Byte Count */
#घोषणा CSR64		0x4000	/*   Next Transmit Buffer Address */
#घोषणा CSR65		0x4100	/*   Next Transmit Buffer Address */
#घोषणा CSR66		0x4200	/*   Next Transmit Status and Byte Count */
#घोषणा CSR67		0x4300	/*   Next Transmit Status and Byte Count */
#घोषणा CSR68		0x4400	/*   Transmit Status Temporary Storage */
#घोषणा CSR69		0x4500	/*   Transmit Status Temporary Storage */
#घोषणा CSR70		0x4600	/*   Temporary Storage */
#घोषणा CSR71		0x4700	/*   Temporary Storage */
#घोषणा CSR72		0x4800	/*   Receive Ring Counter */
#घोषणा CSR74		0x4a00	/*   Transmit Ring Counter */
#घोषणा CSR76		0x4c00	/* - Receive Ring Length */
#घोषणा CSR78		0x4e00	/* - Transmit Ring Length */
#घोषणा CSR80		0x5000	/* - Burst and FIFO Threshold Control */
#घोषणा CSR82		0x5200	/* - Bus Activity Timer */
#घोषणा CSR84		0x5400	/*   DMA Address */
#घोषणा CSR85		0x5500	/*   DMA Address */
#घोषणा CSR86		0x5600	/*   Buffer Byte Counter */
#घोषणा CSR88		0x5800	/* - Chip ID */
#घोषणा CSR89		0x5900	/* - Chip ID */
#घोषणा CSR92		0x5c00	/*   Ring Length Conversion */
#घोषणा CSR94		0x5e00	/*   Transmit Time Doमुख्य Reflectometry Count */
#घोषणा CSR96		0x6000	/*   Bus Interface Scratch Register 0 */
#घोषणा CSR97		0x6100	/*   Bus Interface Scratch Register 0 */
#घोषणा CSR98		0x6200	/*   Bus Interface Scratch Register 1 */
#घोषणा CSR99		0x6300	/*   Bus Interface Scratch Register 1 */
#घोषणा CSR104		0x6800	/*   SWAP */
#घोषणा CSR105		0x6900	/*   SWAP */
#घोषणा CSR108		0x6c00	/*   Buffer Management Scratch */
#घोषणा CSR109		0x6d00	/*   Buffer Management Scratch */
#घोषणा CSR112		0x7000	/* - Missed Frame Count */
#घोषणा CSR114		0x7200	/* - Receive Collision Count */
#घोषणा CSR124		0x7c00	/* - Buffer Management Unit Test */


    /*
     *	Am79C960 ISA Control and Status Registers
     *
     *	These values are alपढ़ोy swap()ed!!
     */

#घोषणा ISACSR0		0x0000	/* Master Mode Read Active */
#घोषणा ISACSR1		0x0100	/* Master Mode Write Active */
#घोषणा ISACSR2		0x0200	/* Miscellaneous Configuration */
#घोषणा ISACSR4		0x0400	/* LED0 Status (Link Integrity) */
#घोषणा ISACSR5		0x0500	/* LED1 Status */
#घोषणा ISACSR6		0x0600	/* LED2 Status */
#घोषणा ISACSR7		0x0700	/* LED3 Status */


    /*
     *	Bit definitions क्रम CSR0 (PCnet-ISA Controller Status)
     *
     *	These values are alपढ़ोy swap()ed!!
     */

#घोषणा ERR		0x0080	/* Error */
#घोषणा BABL		0x0040	/* Babble: Transmitted too many bits */
#घोषणा CERR		0x0020	/* No Heartbeat (10BASE-T) */
#घोषणा MISS		0x0010	/* Missed Frame */
#घोषणा MERR		0x0008	/* Memory Error */
#घोषणा RINT		0x0004	/* Receive Interrupt */
#घोषणा TINT		0x0002	/* Transmit Interrupt */
#घोषणा IDON		0x0001	/* Initialization Done */
#घोषणा INTR		0x8000	/* Interrupt Flag */
#घोषणा INEA		0x4000	/* Interrupt Enable */
#घोषणा RXON		0x2000	/* Receive On */
#घोषणा TXON		0x1000	/* Transmit On */
#घोषणा TDMD		0x0800	/* Transmit Demand */
#घोषणा STOP		0x0400	/* Stop */
#घोषणा STRT		0x0200	/* Start */
#घोषणा INIT		0x0100	/* Initialize */


    /*
     *	Bit definitions क्रम CSR3 (Interrupt Masks and Deferral Control)
     *
     *	These values are alपढ़ोy swap()ed!!
     */

#घोषणा BABLM		0x0040	/* Babble Mask */
#घोषणा MISSM		0x0010	/* Missed Frame Mask */
#घोषणा MERRM		0x0008	/* Memory Error Mask */
#घोषणा RINTM		0x0004	/* Receive Interrupt Mask */
#घोषणा TINTM		0x0002	/* Transmit Interrupt Mask */
#घोषणा IDONM		0x0001	/* Initialization Done Mask */
#घोषणा DXMT2PD		0x1000	/* Disable Transmit Two Part Deferral */
#घोषणा EMBA		0x0800	/* Enable Modअगरied Back-off Algorithm */


    /*
     *	Bit definitions क्रम CSR4 (Test and Features Control)
     *
     *	These values are alपढ़ोy swap()ed!!
     */

#घोषणा ENTST		0x0080	/* Enable Test Mode */
#घोषणा DMAPLUS		0x0040	/* Disable Burst Transaction Counter */
#घोषणा TIMER		0x0020	/* Timer Enable Register */
#घोषणा DPOLL		0x0010	/* Disable Transmit Polling */
#घोषणा APAD_XMT	0x0008	/* Auto Pad Transmit */
#घोषणा ASTRP_RCV	0x0004	/* Auto Pad Stripping */
#घोषणा MFCO		0x0002	/* Missed Frame Counter Overflow Interrupt */
#घोषणा MFCOM		0x0001	/* Missed Frame Counter Overflow Mask */
#घोषणा RCVCCO		0x2000	/* Receive Collision Counter Overflow Interrupt */
#घोषणा RCVCCOM		0x1000	/* Receive Collision Counter Overflow Mask */
#घोषणा TXSTRT		0x0800	/* Transmit Start Status */
#घोषणा TXSTRTM		0x0400	/* Transmit Start Mask */
#घोषणा JAB		0x0200	/* Jabber Error */
#घोषणा JABM		0x0100	/* Jabber Error Mask */


    /*
     *	Bit definitions क्रम CSR15 (Mode Register)
     *
     *	These values are alपढ़ोy swap()ed!!
     */

#घोषणा PROM		0x0080	/* Promiscuous Mode */
#घोषणा DRCVBC		0x0040	/* Disable Receive Broadcast */
#घोषणा DRCVPA		0x0020	/* Disable Receive Physical Address */
#घोषणा DLNKTST		0x0010	/* Disable Link Status */
#घोषणा DAPC		0x0008	/* Disable Automatic Polarity Correction */
#घोषणा MENDECL		0x0004	/* MENDEC Loopback Mode */
#घोषणा LRTTSEL		0x0002	/* Low Receive Threshold/Transmit Mode Select */
#घोषणा PORTSEL1	0x0001	/* Port Select Bits */
#घोषणा PORTSEL2	0x8000	/* Port Select Bits */
#घोषणा INTL		0x4000	/* Internal Loopback */
#घोषणा DRTY		0x2000	/* Disable Retry */
#घोषणा FCOLL		0x1000	/* Force Collision */
#घोषणा DXMTFCS		0x0800	/* Disable Transmit CRC */
#घोषणा LOOP		0x0400	/* Loopback Enable */
#घोषणा DTX		0x0200	/* Disable Transmitter */
#घोषणा DRX		0x0100	/* Disable Receiver */


    /*
     *	Bit definitions क्रम ISACSR2 (Miscellaneous Configuration)
     *
     *	These values are alपढ़ोy swap()ed!!
     */

#घोषणा ASEL		0x0200	/* Media Interface Port Auto Select */


    /*
     *	Bit definitions क्रम ISACSR5-7 (LED1-3 Status)
     *
     *	These values are alपढ़ोy swap()ed!!
     */

#घोषणा LEDOUT		0x0080	/* Current LED Status */
#घोषणा PSE		0x8000	/* Pulse Stretcher Enable */
#घोषणा XMTE		0x1000	/* Enable Transmit Status Signal */
#घोषणा RVPOLE		0x0800	/* Enable Receive Polarity Signal */
#घोषणा RCVE		0x0400	/* Enable Receive Status Signal */
#घोषणा JABE		0x0200	/* Enable Jabber Signal */
#घोषणा COLE		0x0100	/* Enable Collision Signal */


    /*
     *	Receive Descriptor Ring Entry
     */

काष्ठा RDRE अणु
    अस्थिर u_लघु RMD0;	/* LADR[15:0] */
    अस्थिर u_लघु RMD1;	/* HADR[23:16] | Receive Flags */
    अस्थिर u_लघु RMD2;	/* Buffer Byte Count (two's complement) */
    अस्थिर u_लघु RMD3;	/* Message Byte Count */
पूर्ण;


    /*
     *	Transmit Descriptor Ring Entry
     */

काष्ठा TDRE अणु
    अस्थिर u_लघु TMD0;	/* LADR[15:0] */
    अस्थिर u_लघु TMD1;	/* HADR[23:16] | Transmit Flags */
    अस्थिर u_लघु TMD2;	/* Buffer Byte Count (two's complement) */
    अस्थिर u_लघु TMD3;	/* Error Flags */
पूर्ण;


    /*
     *	Receive Flags
     */

#घोषणा RF_OWN		0x0080	/* PCnet-ISA controller owns the descriptor */
#घोषणा RF_ERR		0x0040	/* Error */
#घोषणा RF_FRAM		0x0020	/* Framing Error */
#घोषणा RF_OFLO		0x0010	/* Overflow Error */
#घोषणा RF_CRC		0x0008	/* CRC Error */
#घोषणा RF_BUFF		0x0004	/* Buffer Error */
#घोषणा RF_STP		0x0002	/* Start of Packet */
#घोषणा RF_ENP		0x0001	/* End of Packet */


    /*
     *	Transmit Flags
     */

#घोषणा TF_OWN		0x0080	/* PCnet-ISA controller owns the descriptor */
#घोषणा TF_ERR		0x0040	/* Error */
#घोषणा TF_ADD_FCS	0x0020	/* Controls FCS Generation */
#घोषणा TF_MORE		0x0010	/* More than one retry needed */
#घोषणा TF_ONE		0x0008	/* One retry needed */
#घोषणा TF_DEF		0x0004	/* Deferred */
#घोषणा TF_STP		0x0002	/* Start of Packet */
#घोषणा TF_ENP		0x0001	/* End of Packet */


    /*
     *	Error Flags
     */

#घोषणा EF_BUFF		0x0080	/* Buffer Error */
#घोषणा EF_UFLO		0x0040	/* Underflow Error */
#घोषणा EF_LCOL		0x0010	/* Late Collision */
#घोषणा EF_LCAR		0x0008	/* Loss of Carrier */
#घोषणा EF_RTRY		0x0004	/* Retry Error */
#घोषणा EF_TDR		0xff03	/* Time Doमुख्य Reflectometry */



    /*
     *	MC68230 Parallel Interface/Timer
     */

काष्ठा MC68230 अणु
    अस्थिर u_अक्षर PGCR;	/* Port General Control Register */
    u_अक्षर Pad1[1];
    अस्थिर u_अक्षर PSRR;	/* Port Service Request Register */
    u_अक्षर Pad2[1];
    अस्थिर u_अक्षर PADDR;	/* Port A Data Direction Register */
    u_अक्षर Pad3[1];
    अस्थिर u_अक्षर PBDDR;	/* Port B Data Direction Register */
    u_अक्षर Pad4[1];
    अस्थिर u_अक्षर PCDDR;	/* Port C Data Direction Register */
    u_अक्षर Pad5[1];
    अस्थिर u_अक्षर PIVR;	/* Port Interrupt Vector Register */
    u_अक्षर Pad6[1];
    अस्थिर u_अक्षर PACR;	/* Port A Control Register */
    u_अक्षर Pad7[1];
    अस्थिर u_अक्षर PBCR;	/* Port B Control Register */
    u_अक्षर Pad8[1];
    अस्थिर u_अक्षर PADR;	/* Port A Data Register */
    u_अक्षर Pad9[1];
    अस्थिर u_अक्षर PBDR;	/* Port B Data Register */
    u_अक्षर Pad10[1];
    अस्थिर u_अक्षर PAAR;	/* Port A Alternate Register */
    u_अक्षर Pad11[1];
    अस्थिर u_अक्षर PBAR;	/* Port B Alternate Register */
    u_अक्षर Pad12[1];
    अस्थिर u_अक्षर PCDR;	/* Port C Data Register */
    u_अक्षर Pad13[1];
    अस्थिर u_अक्षर PSR;	/* Port Status Register */
    u_अक्षर Pad14[5];
    अस्थिर u_अक्षर TCR;	/* Timer Control Register */
    u_अक्षर Pad15[1];
    अस्थिर u_अक्षर TIVR;	/* Timer Interrupt Vector Register */
    u_अक्षर Pad16[3];
    अस्थिर u_अक्षर CPRH;	/* Counter Preload Register (High) */
    u_अक्षर Pad17[1];
    अस्थिर u_अक्षर CPRM;	/* Counter Preload Register (Mid) */
    u_अक्षर Pad18[1];
    अस्थिर u_अक्षर CPRL;	/* Counter Preload Register (Low) */
    u_अक्षर Pad19[3];
    अस्थिर u_अक्षर CNTRH;	/* Count Register (High) */
    u_अक्षर Pad20[1];
    अस्थिर u_अक्षर CNTRM;	/* Count Register (Mid) */
    u_अक्षर Pad21[1];
    अस्थिर u_अक्षर CNTRL;	/* Count Register (Low) */
    u_अक्षर Pad22[1];
    अस्थिर u_अक्षर TSR;	/* Timer Status Register */
    u_अक्षर Pad23[11];
पूर्ण;


    /*
     *	Ariadne Expansion Board Structure
     */

#घोषणा ARIADNE_LANCE		0x360

#घोषणा ARIADNE_PIT		0x1000

#घोषणा ARIADNE_BOOTPROM	0x4000	/* I guess it's here :-) */
#घोषणा ARIADNE_BOOTPROM_SIZE	0x4000

#घोषणा ARIADNE_RAM		0x8000	/* Always access WORDs!! */
#घोषणा ARIADNE_RAM_SIZE	0x8000

