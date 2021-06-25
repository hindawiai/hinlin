<शैली गुरु>
/**************************************************************************
 * Initio 9100 device driver क्रम Linux.
 *
 * Copyright (c) 1994-1998 Initio Corporation
 * All rights reserved.
 *
 * Cleanups (c) Copyright 2007 Red Hat <alan@lxorguk.ukuu.org.uk>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, ग_लिखो to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 **************************************************************************/


#समावेश <linux/types.h>

#घोषणा TOTAL_SG_ENTRY		32
#घोषणा MAX_SUPPORTED_ADAPTERS  8
#घोषणा MAX_OFFSET		15
#घोषणा MAX_TARGETS		16

प्रकार काष्ठा अणु
	अचिन्हित लघु base;
	अचिन्हित लघु vec;
पूर्ण i91u_config;

/***************************************/
/*  Tulip Configuration Register Set */
/***************************************/
#घोषणा TUL_PVID        0x00	/* Venकरोr ID                    */
#घोषणा TUL_PDID        0x02	/* Device ID                    */
#घोषणा TUL_PCMD        0x04	/* Command                      */
#घोषणा TUL_PSTUS       0x06	/* Status                       */
#घोषणा TUL_PRID        0x08	/* Revision number              */
#घोषणा TUL_PPI         0x09	/* Programming पूर्णांकerface        */
#घोषणा TUL_PSC         0x0A	/* Sub Class                    */
#घोषणा TUL_PBC         0x0B	/* Base Class                   */
#घोषणा TUL_PCLS        0x0C	/* Cache line size              */
#घोषणा TUL_PLTR        0x0D	/* Latency समयr                */
#घोषणा TUL_PHDT        0x0E	/* Header type                  */
#घोषणा TUL_PBIST       0x0F	/* BIST                         */
#घोषणा TUL_PBAD        0x10	/* Base address                 */
#घोषणा TUL_PBAD1       0x14	/* Base address                 */
#घोषणा TUL_PBAD2       0x18	/* Base address                 */
#घोषणा TUL_PBAD3       0x1C	/* Base address                 */
#घोषणा TUL_PBAD4       0x20	/* Base address                 */
#घोषणा TUL_PBAD5       0x24	/* Base address                 */
#घोषणा TUL_PRSVD       0x28	/* Reserved                     */
#घोषणा TUL_PRSVD1      0x2C	/* Reserved                     */
#घोषणा TUL_PRAD        0x30	/* Expansion ROM base address   */
#घोषणा TUL_PRSVD2      0x34	/* Reserved                     */
#घोषणा TUL_PRSVD3      0x38	/* Reserved                     */
#घोषणा TUL_PINTL       0x3C	/* Interrupt line               */
#घोषणा TUL_PINTP       0x3D	/* Interrupt pin                */
#घोषणा TUL_PIGNT       0x3E	/* MIN_GNT                      */
#घोषणा TUL_PMGNT       0x3F	/* MAX_GNT                      */

/************************/
/*  Jयंत्रin Register Set */
/************************/
#घोषणा TUL_HACFG0      0x40	/* H/A Configuration Register 0         */
#घोषणा TUL_HACFG1      0x41	/* H/A Configuration Register 1         */
#घोषणा TUL_HACFG2      0x42	/* H/A Configuration Register 2         */

#घोषणा TUL_SDCFG0      0x44	/* SCSI Device Configuration 0          */
#घोषणा TUL_SDCFG1      0x45	/* SCSI Device Configuration 1          */
#घोषणा TUL_SDCFG2      0x46	/* SCSI Device Configuration 2          */
#घोषणा TUL_SDCFG3      0x47	/* SCSI Device Configuration 3          */

#घोषणा TUL_GINTS       0x50	/* Global Interrupt Status Register     */
#घोषणा TUL_GIMSK       0x52	/* Global Interrupt MASK Register       */
#घोषणा TUL_GCTRL       0x54	/* Global Control Register              */
#घोषणा TUL_GCTRL_EEPROM_BIT    0x04
#घोषणा TUL_GCTRL1      0x55	/* Global Control Register              */
#घोषणा TUL_DMACFG      0x5B	/* DMA configuration                    */
#घोषणा TUL_NVRAM       0x5D	/* Non-अस्थिर RAM port                */

#घोषणा TUL_SCnt0       0x80	/* 00 R/W Transfer Counter Low          */
#घोषणा TUL_SCnt1       0x81	/* 01 R/W Transfer Counter Mid          */
#घोषणा TUL_SCnt2       0x82	/* 02 R/W Transfer Count High           */
#घोषणा TUL_SFअगरoCnt    0x83	/* 03 R   FIFO counter                  */
#घोषणा TUL_SIntEnable  0x84	/* 03 W   Interrupt enble               */
#घोषणा TUL_SInt        0x84	/* 04 R   Interrupt Register            */
#घोषणा TUL_SCtrl0      0x85	/* 05 W   Control 0                     */
#घोषणा TUL_SStatus0    0x85	/* 05 R   Status 0                      */
#घोषणा TUL_SCtrl1      0x86	/* 06 W   Control 1                     */
#घोषणा TUL_SStatus1    0x86	/* 06 R   Status 1                      */
#घोषणा TUL_SConfig     0x87	/* 07 W   Configuration                 */
#घोषणा TUL_SStatus2    0x87	/* 07 R   Status 2                      */
#घोषणा TUL_SPeriod     0x88	/* 08 W   Sync. Transfer Period & Offset */
#घोषणा TUL_SOffset     0x88	/* 08 R   Offset                        */
#घोषणा TUL_SScsiId     0x89	/* 09 W   SCSI ID                       */
#घोषणा TUL_SBusId      0x89	/* 09 R   SCSI BUS ID                   */
#घोषणा TUL_STimeOut    0x8A	/* 0A W   Sel/Resel Time Out Register   */
#घोषणा TUL_SIdent      0x8A	/* 0A R   Identअगरy Message Register     */
#घोषणा TUL_SAvail      0x8A	/* 0A R   Available Counter Register   */
#घोषणा TUL_SData       0x8B	/* 0B R/W SCSI data in/out              */
#घोषणा TUL_SFअगरo       0x8C	/* 0C R/W FIFO                          */
#घोषणा TUL_SSignal     0x90	/* 10 R/W SCSI संकेत in/out            */
#घोषणा TUL_SCmd        0x91	/* 11 R/W Command                       */
#घोषणा TUL_STest0      0x92	/* 12 R/W Test0                         */
#घोषणा TUL_STest1      0x93	/* 13 R/W Test1                         */
#घोषणा TUL_SCFG1	0x94	/* 14 R/W Configuration                 */

#घोषणा TUL_XAddH       0xC0	/*DMA Transfer Physical Address         */
#घोषणा TUL_XAddW       0xC8	/*DMA Current Transfer Physical Address */
#घोषणा TUL_XCntH       0xD0	/*DMA Transfer Counter                  */
#घोषणा TUL_XCntW       0xD4	/*DMA Current Transfer Counter          */
#घोषणा TUL_XCmd        0xD8	/*DMA Command Register                  */
#घोषणा TUL_Int         0xDC	/*Interrupt Register                    */
#घोषणा TUL_XStatus     0xDD	/*DMA status Register                   */
#घोषणा TUL_Mask        0xE0	/*Interrupt Mask Register               */
#घोषणा TUL_XCtrl       0xE4	/*DMA Control Register                  */
#घोषणा TUL_XCtrl1      0xE5	/*DMA Control Register 1                */
#घोषणा TUL_XFअगरo       0xE8	/*DMA FIFO                              */

#घोषणा TUL_WCtrl       0xF7	/*Bus master रुको state control         */
#घोषणा TUL_DCtrl       0xFB	/*DMA delay control                     */

/*----------------------------------------------------------------------*/
/*   bit definition क्रम Command रेजिस्टर of Configuration Space Header  */
/*----------------------------------------------------------------------*/
#घोषणा BUSMS           0x04	/* BUS MASTER Enable                    */
#घोषणा IOSPA           0x01	/* IO Space Enable                      */

/*----------------------------------------------------------------------*/
/* Command Codes of Tulip SCSI Command रेजिस्टर                         */
/*----------------------------------------------------------------------*/
#घोषणा TSC_EN_RESEL    0x80	/* Enable Reselection                   */
#घोषणा TSC_CMD_COMP    0x84	/* Command Complete Sequence            */
#घोषणा TSC_SEL         0x01	/* Select Without ATN Sequence          */
#घोषणा TSC_SEL_ATN     0x11	/* Select With ATN Sequence             */
#घोषणा TSC_SEL_ATN_DMA 0x51	/* Select With ATN Sequence with DMA    */
#घोषणा TSC_SEL_ATN3    0x31	/* Select With ATN3 Sequence            */
#घोषणा TSC_SEL_ATNSTOP 0x12	/* Select With ATN and Stop Sequence    */
#घोषणा TSC_SELATNSTOP  0x1E	/* Select With ATN and Stop Sequence    */

#घोषणा TSC_SEL_ATN_सूचीECT_IN   0x95	/* Select With ATN Sequence     */
#घोषणा TSC_SEL_ATN_सूचीECT_OUT  0x15	/* Select With ATN Sequence     */
#घोषणा TSC_SEL_ATN3_सूचीECT_IN  0xB5	/* Select With ATN3 Sequence    */
#घोषणा TSC_SEL_ATN3_सूचीECT_OUT 0x35	/* Select With ATN3 Sequence    */
#घोषणा TSC_XF_DMA_OUT_सूचीECT   0x06	/* DMA Xfer Inक्रमmation out      */
#घोषणा TSC_XF_DMA_IN_सूचीECT    0x86	/* DMA Xfer Inक्रमmation in       */

#घोषणा TSC_XF_DMA_OUT  0x43	/* DMA Xfer Inक्रमmation out              */
#घोषणा TSC_XF_DMA_IN   0xC3	/* DMA Xfer Inक्रमmation in               */
#घोषणा TSC_XF_FIFO_OUT 0x03	/* FIFO Xfer Inक्रमmation out             */
#घोषणा TSC_XF_FIFO_IN  0x83	/* FIFO Xfer Inक्रमmation in              */

#घोषणा TSC_MSG_ACCEPT  0x0F	/* Message Accept                       */

/*----------------------------------------------------------------------*/
/* bit definition क्रम Tulip SCSI Control 0 Register                     */
/*----------------------------------------------------------------------*/
#घोषणा TSC_RST_SEQ     0x20	/* Reset sequence counter               */
#घोषणा TSC_FLUSH_FIFO  0x10	/* Flush FIFO                           */
#घोषणा TSC_ABT_CMD     0x04	/* Abort command (sequence)             */
#घोषणा TSC_RST_CHIP    0x02	/* Reset SCSI Chip                      */
#घोषणा TSC_RST_BUS     0x01	/* Reset SCSI Bus                       */

/*----------------------------------------------------------------------*/
/* bit definition क्रम Tulip SCSI Control 1 Register                     */
/*----------------------------------------------------------------------*/
#घोषणा TSC_EN_SCAM     0x80	/* Enable SCAM                          */
#घोषणा TSC_TIMER       0x40	/* Select समयout unit                  */
#घोषणा TSC_EN_SCSI2    0x20	/* SCSI-2 mode                          */
#घोषणा TSC_PWDN        0x10	/* Power करोwn mode                      */
#घोषणा TSC_WIDE_CPU    0x08	/* Wide CPU                             */
#घोषणा TSC_HW_RESELECT 0x04	/* Enable HW reselect                   */
#घोषणा TSC_EN_BUS_OUT  0x02	/* Enable SCSI data bus out latch       */
#घोषणा TSC_EN_BUS_IN   0x01	/* Enable SCSI data bus in latch        */

/*----------------------------------------------------------------------*/
/* bit definition क्रम Tulip SCSI Configuration Register                 */
/*----------------------------------------------------------------------*/
#घोषणा TSC_EN_LATCH    0x80	/* Enable phase latch                   */
#घोषणा TSC_INITIATOR   0x40	/* Initiator mode                       */
#घोषणा TSC_EN_SCSI_PAR 0x20	/* Enable SCSI parity                   */
#घोषणा TSC_DMA_8BIT    0x10	/* Alternate dma 8-bits mode            */
#घोषणा TSC_DMA_16BIT   0x08	/* Alternate dma 16-bits mode           */
#घोषणा TSC_EN_WDACK    0x04	/* Enable DACK जबतक wide SCSI xfer     */
#घोषणा TSC_ALT_PERIOD  0x02	/* Alternate sync period mode           */
#घोषणा TSC_DIS_SCSIRST 0x01	/* Disable SCSI bus reset us            */

#घोषणा TSC_INITDEFAULT (TSC_INITIATOR | TSC_EN_LATCH | TSC_ALT_PERIOD | TSC_DIS_SCSIRST)

#घोषणा TSC_WIDE_SCSI   0x80	/* Enable Wide SCSI                     */

/*----------------------------------------------------------------------*/
/* bit definition क्रम Tulip SCSI संकेत Register                        */
/*----------------------------------------------------------------------*/
#घोषणा TSC_RST_ACK     0x00	/* Release ACK संकेत                   */
#घोषणा TSC_RST_ATN     0x00	/* Release ATN संकेत                   */
#घोषणा TSC_RST_BSY     0x00	/* Release BSY संकेत                   */

#घोषणा TSC_SET_ACK     0x40	/* ACK संकेत                           */
#घोषणा TSC_SET_ATN     0x08	/* ATN संकेत                           */

#घोषणा TSC_REQI        0x80	/* REQ संकेत                           */
#घोषणा TSC_ACKI        0x40	/* ACK संकेत                           */
#घोषणा TSC_BSYI        0x20	/* BSY संकेत                           */
#घोषणा TSC_SELI        0x10	/* SEL संकेत                           */
#घोषणा TSC_ATNI        0x08	/* ATN संकेत                           */
#घोषणा TSC_MSGI        0x04	/* MSG संकेत                           */
#घोषणा TSC_CDI         0x02	/* C/D संकेत                           */
#घोषणा TSC_IOI         0x01	/* I/O संकेत                           */


/*----------------------------------------------------------------------*/
/* bit definition क्रम Tulip SCSI Status 0 Register                      */
/*----------------------------------------------------------------------*/
#घोषणा TSS_INT_PENDING 0x80	/* Interrupt pending            */
#घोषणा TSS_SEQ_ACTIVE  0x40	/* Sequencer active             */
#घोषणा TSS_XFER_CNT    0x20	/* Transfer counter zero        */
#घोषणा TSS_FIFO_EMPTY  0x10	/* FIFO empty                   */
#घोषणा TSS_PAR_ERROR   0x08	/* SCSI parity error            */
#घोषणा TSS_PH_MASK     0x07	/* SCSI phase mask              */

/*----------------------------------------------------------------------*/
/* bit definition क्रम Tulip SCSI Status 1 Register                      */
/*----------------------------------------------------------------------*/
#घोषणा TSS_STATUS_RCV  0x08	/* Status received              */
#घोषणा TSS_MSG_SEND    0x40	/* Message sent                 */
#घोषणा TSS_CMD_PH_CMP  0x20	/* command phase करोne              */
#घोषणा TSS_DATA_PH_CMP 0x10	/* Data phase करोne              */
#घोषणा TSS_STATUS_SEND 0x08	/* Status sent                  */
#घोषणा TSS_XFER_CMP    0x04	/* Transfer completed           */
#घोषणा TSS_SEL_CMP     0x02	/* Selection completed          */
#घोषणा TSS_ARB_CMP     0x01	/* Arbitration completed        */

/*----------------------------------------------------------------------*/
/* bit definition क्रम Tulip SCSI Status 2 Register                      */
/*----------------------------------------------------------------------*/
#घोषणा TSS_CMD_ABTED   0x80	/* Command पातed              */
#घोषणा TSS_OFFSET_0    0x40	/* Offset counter zero          */
#घोषणा TSS_FIFO_FULL   0x20	/* FIFO full                    */
#घोषणा TSS_TIMEOUT_0   0x10	/* Timeout counter zero         */
#घोषणा TSS_BUSY_RLS    0x08	/* Busy release                 */
#घोषणा TSS_PH_MISMATCH 0x04	/* Phase mismatch               */
#घोषणा TSS_SCSI_BUS_EN 0x02	/* SCSI data bus enable         */
#घोषणा TSS_SCSIRST     0x01	/* SCSI bus reset in progress   */

/*----------------------------------------------------------------------*/
/* bit definition क्रम Tulip SCSI Interrupt Register                     */
/*----------------------------------------------------------------------*/
#घोषणा TSS_RESEL_INT   0x80	/* Reselected पूर्णांकerrupt         */
#घोषणा TSS_SEL_TIMEOUT 0x40	/* Selected/reselected समयout  */
#घोषणा TSS_BUS_SERV    0x20
#घोषणा TSS_SCSIRST_INT 0x10	/* SCSI bus reset detected      */
#घोषणा TSS_DISC_INT    0x08	/* Disconnected पूर्णांकerrupt       */
#घोषणा TSS_SEL_INT     0x04	/* Select पूर्णांकerrupt             */
#घोषणा TSS_SCAM_SEL    0x02	/* SCAM selected                */
#घोषणा TSS_FUNC_COMP   0x01

/*----------------------------------------------------------------------*/
/* SCSI Phase Codes.                                                    */
/*----------------------------------------------------------------------*/
#घोषणा DATA_OUT        0
#घोषणा DATA_IN         1	/* 4                            */
#घोषणा CMD_OUT         2
#घोषणा STATUS_IN       3	/* 6                            */
#घोषणा MSG_OUT         6	/* 3                            */
#घोषणा MSG_IN          7



/*----------------------------------------------------------------------*/
/* Command Codes of Tulip xfer Command रेजिस्टर                         */
/*----------------------------------------------------------------------*/
#घोषणा TAX_X_FORC      0x02
#घोषणा TAX_X_ABT       0x04
#घोषणा TAX_X_CLR_FIFO  0x08

#घोषणा TAX_X_IN        0x21
#घोषणा TAX_X_OUT       0x01
#घोषणा TAX_SG_IN       0xA1
#घोषणा TAX_SG_OUT      0x81

/*----------------------------------------------------------------------*/
/* Tulip Interrupt Register                                             */
/*----------------------------------------------------------------------*/
#घोषणा XCMP            0x01
#घोषणा FCMP            0x02
#घोषणा XABT            0x04
#घोषणा XERR            0x08
#घोषणा SCMP            0x10
#घोषणा IPEND           0x80

/*----------------------------------------------------------------------*/
/* Tulip DMA Status Register                                            */
/*----------------------------------------------------------------------*/
#घोषणा XPEND           0x01	/* Transfer pending             */
#घोषणा FEMPTY          0x02	/* FIFO empty                   */



/*----------------------------------------------------------------------*/
/* bit definition क्रम TUL_GCTRL                                         */
/*----------------------------------------------------------------------*/
#घोषणा EXTSG           0x80
#घोषणा EXTAD           0x60
#घोषणा SEG4K           0x08
#घोषणा EEPRG           0x04
#घोषणा MRMUL           0x02

/*----------------------------------------------------------------------*/
/* bit definition क्रम TUL_NVRAM                                         */
/*----------------------------------------------------------------------*/
#घोषणा SE2CS           0x08
#घोषणा SE2CLK          0x04
#घोषणा SE2DO           0x02
#घोषणा SE2DI           0x01


/************************************************************************/
/*              Scatter-Gather Element Structure                        */
/************************************************************************/
काष्ठा sg_entry अणु
	u32 data;		/* Data Poपूर्णांकer */
	u32 len;		/* Data Length */
पूर्ण;

/***********************************************************************
		SCSI Control Block
************************************************************************/
काष्ठा scsi_ctrl_blk अणु
	काष्ठा scsi_ctrl_blk *next;
	u8 status;	/*4 */
	u8 next_state;	/*5 */
	u8 mode;		/*6 */
	u8 msgin;	/*7 SCB_Res0 */
	u16 sgidx;	/*8 */
	u16 sgmax;	/*A */
#अगर_घोषित ALPHA
	u32 reserved[2];	/*C */
#अन्यथा
	u32 reserved[3];	/*C */
#पूर्ण_अगर

	u32 xferlen;	/*18 Current xfer len           */
	u32 totxlen;	/*1C Total xfer len             */
	u32 paddr;		/*20 SCB phy. Addr. */

	u8 opcode;	/*24 SCB command code */
	u8 flags;	/*25 SCB Flags */
	u8 target;	/*26 Target Id */
	u8 lun;		/*27 Lun */
	u32 bufptr;		/*28 Data Buffer Poपूर्णांकer */
	u32 buflen;		/*2C Data Allocation Length */
	u8 sglen;	/*30 SG list # */
	u8 senselen;	/*31 Sense Allocation Length */
	u8 hastat;	/*32 */
	u8 tastat;	/*33 */
	u8 cdblen;	/*34 CDB Length */
	u8 ident;	/*35 Identअगरy */
	u8 tagmsg;	/*36 Tag Message */
	u8 tagid;	/*37 Queue Tag */
	u8 cdb[12];	/*38 */
	u32 sgpaddr;	/*44 SG List/Sense Buf phy. Addr. */
	u32 senseptr;	/*48 Sense data poपूर्णांकer */
	व्योम (*post) (u8 *, u8 *);	/*4C POST routine */
	काष्ठा scsi_cmnd *srb;	/*50 SRB Poपूर्णांकer */
	काष्ठा sg_entry sglist[TOTAL_SG_ENTRY];	/*54 Start of SG list */
पूर्ण;

/* Bit Definition क्रम status */
#घोषणा SCB_RENT        0x01
#घोषणा SCB_PEND        0x02
#घोषणा SCB_CONTIG      0x04	/* Contingent Allegiance */
#घोषणा SCB_SELECT      0x08
#घोषणा SCB_BUSY        0x10
#घोषणा SCB_DONE        0x20


/* Opcodes क्रम opcode */
#घोषणा ExecSCSI        0x1
#घोषणा BusDevRst       0x2
#घोषणा AbortCmd        0x3


/* Bit Definition क्रम mode */
#घोषणा SCM_RSENS       0x01	/* request sense mode */


/* Bit Definition क्रम flags */
#घोषणा SCF_DONE        0x01
#घोषणा SCF_POST        0x02
#घोषणा SCF_SENSE       0x04
#घोषणा SCF_सूची         0x18
#घोषणा SCF_NO_DCHK     0x00
#घोषणा SCF_DIN         0x08
#घोषणा SCF_DOUT        0x10
#घोषणा SCF_NO_XF       0x18
#घोषणा SCF_WR_VF       0x20	/* Write verअगरy turn on         */
#घोषणा SCF_POLL        0x40
#घोषणा SCF_SG          0x80

/* Error Codes क्रम SCB_HaStat */
#घोषणा HOST_SEL_TOUT   0x11
#घोषणा HOST_DO_DU      0x12
#घोषणा HOST_BUS_FREE   0x13
#घोषणा HOST_BAD_PHAS   0x14
#घोषणा HOST_INV_CMD    0x16
#घोषणा HOST_ABORTED    0x1A	/* 07/21/98 */
#घोषणा HOST_SCSI_RST   0x1B
#घोषणा HOST_DEV_RST    0x1C

/* Error Codes क्रम SCB_TaStat */
#घोषणा TARGET_CHKCOND  0x02
#घोषणा TARGET_BUSY     0x08
#घोषणा INI_QUEUE_FULL	0x28

/***********************************************************************
		Target Device Control Structure
**********************************************************************/

काष्ठा target_control अणु
	u16 flags;
	u8 js_period;
	u8 sconfig0;
	u16 drv_flags;
	u8 heads;
	u8 sectors;
पूर्ण;

/***********************************************************************
		Target Device Control Structure
**********************************************************************/

/* Bit Definition क्रम TCF_Flags */
#घोषणा TCF_SCSI_RATE           0x0007
#घोषणा TCF_EN_DISC             0x0008
#घोषणा TCF_NO_SYNC_NEGO        0x0010
#घोषणा TCF_NO_WDTR             0x0020
#घोषणा TCF_EN_255              0x0040
#घोषणा TCF_EN_START            0x0080
#घोषणा TCF_WDTR_DONE           0x0100
#घोषणा TCF_SYNC_DONE           0x0200
#घोषणा TCF_BUSY                0x0400


/* Bit Definition क्रम TCF_DrvFlags */
#घोषणा TCF_DRV_BUSY            0x01	/* Indicate target busy(driver) */
#घोषणा TCF_DRV_EN_TAG          0x0800
#घोषणा TCF_DRV_255_63          0x0400

/***********************************************************************
	      Host Adapter Control Structure
************************************************************************/
काष्ठा initio_host अणु
	u16 addr;		/* 00 */
	u16 bios_addr;		/* 02 */
	u8 irq;			/* 04 */
	u8 scsi_id;		/* 05 */
	u8 max_tar;		/* 06 */
	u8 num_scbs;		/* 07 */

	u8 flags;		/* 08 */
	u8 index;		/* 09 */
	u8 ha_id;		/* 0A */
	u8 config;		/* 0B */
	u16 idmask;		/* 0C */
	u8 semaph;		/* 0E */
	u8 phase;		/* 0F */
	u8 jsstatus0;		/* 10 */
	u8 jsपूर्णांक;		/* 11 */
	u8 jsstatus1;		/* 12 */
	u8 sconf1;		/* 13 */

	u8 msg[8];		/* 14 */
	काष्ठा scsi_ctrl_blk *next_avail;	/* 1C */
	काष्ठा scsi_ctrl_blk *scb;		/* 20 */
	काष्ठा scsi_ctrl_blk *scb_end;		/* 24 */ /*UNUSED*/
	काष्ठा scsi_ctrl_blk *next_pending;	/* 28 */
	काष्ठा scsi_ctrl_blk *next_contig;	/* 2C */ /*UNUSED*/
	काष्ठा scsi_ctrl_blk *active;		/* 30 */
	काष्ठा target_control *active_tc;	/* 34 */

	काष्ठा scsi_ctrl_blk *first_avail;	/* 38 */
	काष्ठा scsi_ctrl_blk *last_avail;	/* 3C */
	काष्ठा scsi_ctrl_blk *first_pending;	/* 40 */
	काष्ठा scsi_ctrl_blk *last_pending;	/* 44 */
	काष्ठा scsi_ctrl_blk *first_busy;	/* 48 */
	काष्ठा scsi_ctrl_blk *last_busy;	/* 4C */
	काष्ठा scsi_ctrl_blk *first_करोne;	/* 50 */
	काष्ठा scsi_ctrl_blk *last_करोne;	/* 54 */
	u8 max_tags[16];	/* 58 */
	u8 act_tags[16];	/* 68 */
	काष्ठा target_control tarमाला_लो[MAX_TARGETS];	/* 78 */
	spinlock_t avail_lock;
	spinlock_t semaph_lock;
	काष्ठा pci_dev *pci_dev;
पूर्ण;

/* Bit Definition क्रम HCB_Config */
#घोषणा HCC_SCSI_RESET          0x01
#घोषणा HCC_EN_PAR              0x02
#घोषणा HCC_ACT_TERM1           0x04
#घोषणा HCC_ACT_TERM2           0x08
#घोषणा HCC_AUTO_TERM           0x10
#घोषणा HCC_EN_PWR              0x80

/* Bit Definition क्रम HCB_Flags */
#घोषणा HCF_EXPECT_DISC         0x01
#घोषणा HCF_EXPECT_SELECT       0x02
#घोषणा HCF_EXPECT_RESET        0x10
#घोषणा HCF_EXPECT_DONE_DISC    0x20

/******************************************************************
	Serial EEProm
*******************************************************************/

प्रकार काष्ठा _NVRAM_SCSI अणु	/* SCSI channel configuration   */
	u8 NVM_ChSCSIID;	/* 0Ch -> Channel SCSI ID       */
	u8 NVM_ChConfig1;	/* 0Dh -> Channel config 1      */
	u8 NVM_ChConfig2;	/* 0Eh -> Channel config 2      */
	u8 NVM_NumOfTarg;	/* 0Fh -> Number of SCSI target */
	/* SCSI target configuration    */
	u8 NVM_Targ0Config;	/* 10h -> Target 0 configuration */
	u8 NVM_Targ1Config;	/* 11h -> Target 1 configuration */
	u8 NVM_Targ2Config;	/* 12h -> Target 2 configuration */
	u8 NVM_Targ3Config;	/* 13h -> Target 3 configuration */
	u8 NVM_Targ4Config;	/* 14h -> Target 4 configuration */
	u8 NVM_Targ5Config;	/* 15h -> Target 5 configuration */
	u8 NVM_Targ6Config;	/* 16h -> Target 6 configuration */
	u8 NVM_Targ7Config;	/* 17h -> Target 7 configuration */
	u8 NVM_Targ8Config;	/* 18h -> Target 8 configuration */
	u8 NVM_Targ9Config;	/* 19h -> Target 9 configuration */
	u8 NVM_TargAConfig;	/* 1Ah -> Target A configuration */
	u8 NVM_TargBConfig;	/* 1Bh -> Target B configuration */
	u8 NVM_TargCConfig;	/* 1Ch -> Target C configuration */
	u8 NVM_TargDConfig;	/* 1Dh -> Target D configuration */
	u8 NVM_TargEConfig;	/* 1Eh -> Target E configuration */
	u8 NVM_TargFConfig;	/* 1Fh -> Target F configuration */
पूर्ण NVRAM_SCSI;

प्रकार काष्ठा _NVRAM अणु
/*----------header ---------------*/
	u16 NVM_Signature;	/* 0,1: Signature */
	u8 NVM_Size;		/* 2:   Size of data काष्ठाure */
	u8 NVM_Revision;	/* 3:   Revision of data काष्ठाure */
	/* ----Host Adapter Structure ---- */
	u8 NVM_ModelByte0;	/* 4:   Model number (byte 0) */
	u8 NVM_ModelByte1;	/* 5:   Model number (byte 1) */
	u8 NVM_ModelInfo;	/* 6:   Model inक्रमmation         */
	u8 NVM_NumOfCh;	/* 7:   Number of SCSI channel */
	u8 NVM_BIOSConfig1;	/* 8:   BIOS configuration 1  */
	u8 NVM_BIOSConfig2;	/* 9:   BIOS configuration 2  */
	u8 NVM_HAConfig1;	/* A:   Hoat adapter configuration 1 */
	u8 NVM_HAConfig2;	/* B:   Hoat adapter configuration 2 */
	NVRAM_SCSI NVM_SCSIInfo[2];
	u8 NVM_reserved[10];
	/* ---------- CheckSum ----------       */
	u16 NVM_CheckSum;	/* 0x3E, 0x3F: Checksum of NVRam        */
पूर्ण NVRAM, *PNVRAM;

/* Bios Configuration क्रम nvram->BIOSConfig1                            */
#घोषणा NBC1_ENABLE             0x01	/* BIOS enable                  */
#घोषणा NBC1_8DRIVE             0x02	/* Support more than 2 drives   */
#घोषणा NBC1_REMOVABLE          0x04	/* Support removable drive      */
#घोषणा NBC1_INT19              0x08	/* Intercept पूर्णांक 19h            */
#घोषणा NBC1_BIOSSCAN           0x10	/* Dynamic BIOS scan            */
#घोषणा NBC1_LUNSUPPORT         0x40	/* Support LUN                  */

/* HA Configuration Byte 1                                              */
#घोषणा NHC1_BOOTIDMASK 0x0F	/* Boot ID number               */
#घोषणा NHC1_LUNMASK    0x70	/* Boot LUN number              */
#घोषणा NHC1_CHANMASK   0x80	/* Boot Channel number          */

/* Bit definition क्रम nvram->SCSIconfig1                                */
#घोषणा NCC1_BUSRESET           0x01	/* Reset SCSI bus at घातer up   */
#घोषणा NCC1_PARITYCHK          0x02	/* SCSI parity enable           */
#घोषणा NCC1_ACTTERM1           0x04	/* Enable active terminator 1   */
#घोषणा NCC1_ACTTERM2           0x08	/* Enable active terminator 2   */
#घोषणा NCC1_AUTOTERM           0x10	/* Enable स्वतः terminator       */
#घोषणा NCC1_PWRMGR             0x80	/* Enable घातer management      */

/* Bit definition क्रम SCSI Target configuration byte                    */
#घोषणा NTC_DISCONNECT          0x08	/* Enable SCSI disconnect       */
#घोषणा NTC_SYNC                0x10	/* SYNC_NEGO                    */
#घोषणा NTC_NO_WDTR             0x20	/* SYNC_NEGO                    */
#घोषणा NTC_1GIGA               0x40	/* 255 head / 63 sectors (64/32) */
#घोषणा NTC_SPINUP              0x80	/* Start disk drive             */

/*      Default NVRam values                                            */
#घोषणा INI_SIGNATURE           0xC925
#घोषणा NBC1_DEFAULT            (NBC1_ENABLE)
#घोषणा NCC1_DEFAULT            (NCC1_BUSRESET | NCC1_AUTOTERM | NCC1_PARITYCHK)
#घोषणा NTC_DEFAULT             (NTC_NO_WDTR | NTC_1GIGA | NTC_DISCONNECT)

/* SCSI related definition                                              */
#घोषणा DISC_NOT_ALLOW          0x80	/* Disconnect is not allowed    */
#घोषणा DISC_ALLOW              0xC0	/* Disconnect is allowed        */
#घोषणा SCSICMD_RequestSense    0x03

#घोषणा SCSI_ABORT_SNOOZE 0
#घोषणा SCSI_ABORT_SUCCESS 1
#घोषणा SCSI_ABORT_PENDING 2
#घोषणा SCSI_ABORT_BUSY 3
#घोषणा SCSI_ABORT_NOT_RUNNING 4
#घोषणा SCSI_ABORT_ERROR 5

#घोषणा SCSI_RESET_SNOOZE 0
#घोषणा SCSI_RESET_PUNT 1
#घोषणा SCSI_RESET_SUCCESS 2
#घोषणा SCSI_RESET_PENDING 3
#घोषणा SCSI_RESET_WAKEUP 4
#घोषणा SCSI_RESET_NOT_RUNNING 5
#घोषणा SCSI_RESET_ERROR 6

#घोषणा SCSI_RESET_SYNCHRONOUS		0x01
#घोषणा SCSI_RESET_ASYNCHRONOUS		0x02
#घोषणा SCSI_RESET_SUGGEST_BUS_RESET	0x04
#घोषणा SCSI_RESET_SUGGEST_HOST_RESET	0x08

#घोषणा SCSI_RESET_BUS_RESET 0x100
#घोषणा SCSI_RESET_HOST_RESET 0x200
#घोषणा SCSI_RESET_ACTION   0xff

