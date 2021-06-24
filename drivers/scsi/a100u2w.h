<शैली गुरु>
/*
 * Initio A100 device driver क्रम Linux.
 *
 * Copyright (c) 1994-1998 Initio Corporation
 * All rights reserved.
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
 * Revision History:
 * 06/18/98 HL, Initial production Version 1.02
 * 12/19/98 bv, Use spinlocks क्रम 2.1.95 and up
 * 06/25/02 Doug Ledक्रमd <dledक्रमd@redhat.com>
 *	 - This and the i60uscsi.h file are almost identical,
 *	   merged them पूर्णांकo a single header used by both .c files.
 * 14/06/07 Alan Cox <alan@redhat.com>
 *	 - Gअक्रम cleanup and Linuxisation
 */

#घोषणा inia100_REVID "Initio INI-A100U2W SCSI device driver; Revision: 1.02d"

#अगर 1
#घोषणा ORC_MAXQUEUE		245
#घोषणा ORC_MAXTAGS		64
#अन्यथा
#घोषणा ORC_MAXQUEUE		25
#घोषणा ORC_MAXTAGS		8
#पूर्ण_अगर

#घोषणा TOTAL_SG_ENTRY		32
#घोषणा MAX_TARGETS		16
#घोषणा IMAX_CDB			15
#घोषणा SENSE_SIZE		14

/************************************************************************/
/*              Scatter-Gather Element Structure                        */
/************************************************************************/
काष्ठा orc_sgent अणु
	u32 base;		/* Data Poपूर्णांकer */
	u32 length;		/* Data Length */
पूर्ण;

/* SCSI related definition                                              */
#घोषणा DISC_NOT_ALLOW          0x80	/* Disconnect is not allowed    */
#घोषणा DISC_ALLOW              0xC0	/* Disconnect is allowed        */


#घोषणा ORC_OFFSET_SCB			16
#घोषणा ORC_MAX_SCBS		    250
#घोषणा MAX_CHANNELS       2
#घोषणा MAX_ESCB_ELE				64
#घोषणा TCF_DRV_255_63     0x0400

/********************************************************/
/*      Orchid Host Command Set                         */
/********************************************************/
#घोषणा ORC_CMD_NOP		0x00	/* Host command - NOP             */
#घोषणा ORC_CMD_VERSION		0x01	/* Host command - Get F/W version */
#घोषणा ORC_CMD_ECHO		0x02	/* Host command - ECHO            */
#घोषणा ORC_CMD_SET_NVM		0x03	/* Host command - Set NVRAM       */
#घोषणा ORC_CMD_GET_NVM		0x04	/* Host command - Get NVRAM       */
#घोषणा ORC_CMD_GET_BUS_STATUS	0x05	/* Host command - Get SCSI bus status */
#घोषणा ORC_CMD_ABORT_SCB	0x06	/* Host command - Abort SCB       */
#घोषणा ORC_CMD_ISSUE_SCB	0x07	/* Host command - Issue SCB       */

/********************************************************/
/*              Orchid Register Set                     */
/********************************************************/
#घोषणा ORC_GINTS	0xA0	/* Global Interrupt Status        */
#घोषणा QINT		0x04	/* Reply Queue Interrupt  */
#घोषणा ORC_GIMSK	0xA1	/* Global Interrupt MASK  */
#घोषणा MQINT		0x04	/* Mask Reply Queue Interrupt     */
#घोषणा	ORC_GCFG	0xA2	/* Global Configure               */
#घोषणा EEPRG		0x01	/* Enable EEPROM programming */
#घोषणा	ORC_GSTAT	0xA3	/* Global status          */
#घोषणा WIDEBUS		0x10	/* Wide SCSI Devices connected    */
#घोषणा ORC_HDATA	0xA4	/* Host Data                      */
#घोषणा ORC_HCTRL	0xA5	/* Host Control                   */
#घोषणा SCSIRST		0x80	/* SCSI bus reset         */
#घोषणा HDO			0x40	/* Host data out          */
#घोषणा HOSTSTOP		0x02	/* Host stop RISC engine  */
#घोषणा DEVRST		0x01	/* Device reset                   */
#घोषणा ORC_HSTUS	0xA6	/* Host Status                    */
#घोषणा HDI			0x02	/* Host data in                   */
#घोषणा RREADY		0x01	/* RISC engine is पढ़ोy to receive */
#घोषणा	ORC_NVRAM	0xA7	/* Nvram port address             */
#घोषणा SE2CS		0x008
#घोषणा SE2CLK		0x004
#घोषणा SE2DO		0x002
#घोषणा SE2DI		0x001
#घोषणा ORC_PQUEUE	0xA8	/* Posting queue FIFO             */
#घोषणा ORC_PQCNT	0xA9	/* Posting queue FIFO Cnt */
#घोषणा ORC_RQUEUE	0xAA	/* Reply queue FIFO               */
#घोषणा ORC_RQUEUECNT	0xAB	/* Reply queue FIFO Cnt           */
#घोषणा	ORC_FWBASEADR	0xAC	/* Firmware base address  */

#घोषणा	ORC_EBIOSADR0 0xB0	/* External Bios address */
#घोषणा	ORC_EBIOSADR1 0xB1	/* External Bios address */
#घोषणा	ORC_EBIOSADR2 0xB2	/* External Bios address */
#घोषणा	ORC_EBIOSDATA 0xB3	/* External Bios address */

#घोषणा	ORC_SCBSIZE	0xB7	/* SCB size रेजिस्टर              */
#घोषणा	ORC_SCBBASE0	0xB8	/* SCB base address 0             */
#घोषणा	ORC_SCBBASE1	0xBC	/* SCB base address 1             */

#घोषणा	ORC_RISCCTL	0xE0	/* RISC Control                   */
#घोषणा PRGMRST		0x002
#घोषणा DOWNLOAD		0x001
#घोषणा	ORC_PRGMCTR0	0xE2	/* RISC program counter           */
#घोषणा	ORC_PRGMCTR1	0xE3	/* RISC program counter           */
#घोषणा	ORC_RISCRAM	0xEC	/* RISC RAM data port 4 bytes     */

काष्ठा orc_extended_scb अणु	/* Extended SCB                 */
	काष्ठा orc_sgent sglist[TOTAL_SG_ENTRY];	/*0 Start of SG list              */
	काष्ठा scsi_cmnd *srb;	/*50 SRB Poपूर्णांकer */
पूर्ण;

/***********************************************************************
		SCSI Control Block

		0x40 bytes दीर्घ, the last 8 are user bytes
************************************************************************/
काष्ठा orc_scb अणु	/* Scsi_Ctrl_Blk                */
	u8 opcode;	/*00 SCB command code&residual  */
	u8 flags;	/*01 SCB Flags                  */
	u8 target;	/*02 Target Id                  */
	u8 lun;		/*03 Lun                        */
	u32 reserved0;	/*04 Reserved क्रम ORCHID must 0 */
	u32 xferlen;	/*08 Data Transfer Length       */
	u32 reserved1;	/*0C Reserved क्रम ORCHID must 0 */
	u32 sg_len;		/*10 SG list # * 8              */
	u32 sg_addr;	/*14 SG List Buf physical Addr  */
	u32 sg_addrhigh;	/*18 SG Buffer high physical Addr */
	u8 hastat;	/*1C Host Status                */
	u8 tastat;	/*1D Target Status              */
	u8 status;	/*1E SCB status                 */
	u8 link;		/*1F Link poपूर्णांकer, शेष 0xFF */
	u8 sense_len;	/*20 Sense Allocation Length    */
	u8 cdb_len;	/*21 CDB Length                 */
	u8 ident;	/*22 Identअगरy                   */
	u8 tag_msg;	/*23 Tag Message                */
	u8 cdb[IMAX_CDB];	/*24 SCSI CDBs                  */
	u8 scbidx;	/*3C Index क्रम this ORCSCB      */
	u32 sense_addr;	/*34 Sense Buffer physical Addr */

	काष्ठा orc_extended_scb *escb; /*38 Extended SCB Poपूर्णांकer       */
        /* 64bit poपूर्णांकer or 32bit poपूर्णांकer + reserved ? */
#अगर_अघोषित CONFIG_64BIT
	u8 reserved2[4];	/*3E Reserved क्रम Driver use    */
#पूर्ण_अगर
पूर्ण;

/* Opcodes of ORCSCB_Opcode */
#घोषणा ORC_EXECSCSI	0x00	/* SCSI initiator command with residual */
#घोषणा ORC_BUSDEVRST	0x01	/* SCSI Bus Device Reset  */

/* Status of ORCSCB_Status */
#घोषणा ORCSCB_COMPLETE	0x00	/* SCB request completed  */
#घोषणा ORCSCB_POST	0x01	/* SCB is posted by the HOST      */

/* Bit Definition क्रम ORCSCB_Flags */
#घोषणा SCF_DISINT	0x01	/* Disable HOST पूर्णांकerrupt */
#घोषणा SCF_सूची		0x18	/* Direction bits         */
#घोषणा SCF_NO_DCHK	0x00	/* Direction determined by SCSI   */
#घोषणा SCF_DIN		0x08	/* From Target to Initiator       */
#घोषणा SCF_DOUT	0x10	/* From Initiator to Target       */
#घोषणा SCF_NO_XF	0x18	/* No data transfer               */
#घोषणा SCF_POLL   0x40

/* Error Codes क्रम ORCSCB_HaStat */
#घोषणा HOST_SEL_TOUT	0x11
#घोषणा HOST_DO_DU	0x12
#घोषणा HOST_BUS_FREE	0x13
#घोषणा HOST_BAD_PHAS	0x14
#घोषणा HOST_INV_CMD	0x16
#घोषणा HOST_SCSI_RST	0x1B
#घोषणा HOST_DEV_RST	0x1C


/* Error Codes क्रम ORCSCB_TaStat */
#घोषणा TARGET_CHK_COND	0x02
#घोषणा TARGET_BUSY	0x08
#घोषणा TARGET_TAG_FULL	0x28


/***********************************************************************
		Target Device Control Structure
**********************************************************************/

काष्ठा orc_target अणु
	u8 TCS_DrvDASD;	/* 6 */
	u8 TCS_DrvSCSI;	/* 7 */
	u8 TCS_DrvHead;	/* 8 */
	u16 TCS_DrvFlags;	/* 4 */
	u8 TCS_DrvSector;	/* 7 */
पूर्ण;

/* Bit Definition क्रम TCF_DrvFlags */
#घोषणा	TCS_DF_NODASD_SUPT	0x20	/* Suppress OS/2 DASD Mgr support */
#घोषणा	TCS_DF_NOSCSI_SUPT	0x40	/* Suppress OS/2 SCSI Mgr support */


/***********************************************************************
              Host Adapter Control Structure
************************************************************************/
काष्ठा orc_host अणु
	अचिन्हित दीर्घ base;	/* Base address */
	u8 index;		/* Index (Channel)*/
	u8 scsi_id;		/* H/A SCSI ID */
	u8 BIOScfg;		/*BIOS configuration */
	u8 flags;
	u8 max_tarमाला_लो;		/* SCSI0MAXTags */
	काष्ठा orc_scb *scb_virt;	/* Virtual Poपूर्णांकer to SCB array */
	dma_addr_t scb_phys;	/* Scb Physical address */
	काष्ठा orc_extended_scb *escb_virt; /* Virtual poपूर्णांकer to ESCB Scatter list */
	dma_addr_t escb_phys;	/* scatter list Physical address */
	u8 target_flag[16];	/* target configuration, TCF_EN_TAG */
	u8 max_tags[16];	/* ORC_MAX_SCBS */
	u32 allocation_map[MAX_CHANNELS][8];	/* Max STB is 256, So 256/32 */
	spinlock_t allocation_lock;
	काष्ठा pci_dev *pdev;
पूर्ण;

/* Bit Definition क्रम HCS_Flags */

#घोषणा HCF_SCSI_RESET	0x01	/* SCSI BUS RESET         */
#घोषणा HCF_PARITY    	0x02	/* parity card                    */
#घोषणा HCF_LVDS     	0x10	/* parity card                    */

/* Bit Definition क्रम TargetFlag */

#घोषणा TCF_EN_255	    0x08
#घोषणा TCF_EN_TAG	    0x10
#घोषणा TCF_BUSY	      0x20
#घोषणा TCF_DISCONNECT	0x40
#घोषणा TCF_SPIN_UP	  0x80

/* Bit Definition क्रम HCS_AFlags */
#घोषणा	HCS_AF_IGNORE		0x01	/* Adapter ignore         */
#घोषणा	HCS_AF_DISABLE_RESET	0x10	/* Adapter disable reset  */
#घोषणा	HCS_AF_DISABLE_ADPT	0x80	/* Adapter disable                */

काष्ठा orc_nvram अणु
/*----------header ---------------*/
        u8 SubVenकरोrID0;     /* 00 - Sub Venकरोr ID           */
        u8 SubVenकरोrID1;     /* 00 - Sub Venकरोr ID           */
        u8 SubSysID0;        /* 02 - Sub System ID           */
        u8 SubSysID1;        /* 02 - Sub System ID           */
        u8 SubClass;         /* 04 - Sub Class               */
        u8 VenकरोrID0;        /* 05 - Venकरोr ID               */
        u8 VenकरोrID1;        /* 05 - Venकरोr ID               */
        u8 DeviceID0;        /* 07 - Device ID               */
        u8 DeviceID1;        /* 07 - Device ID               */
        u8 Reserved0[2];     /* 09 - Reserved                */
        u8 revision;         /* 0B - revision of data काष्ठाure */
        /* ----Host Adapter Structure ---- */
        u8 NumOfCh;          /* 0C - Number of SCSI channel  */
        u8 BIOSConfig1;      /* 0D - BIOS configuration 1    */
        u8 BIOSConfig2;      /* 0E - BIOS boot channel&target ID */
        u8 BIOSConfig3;      /* 0F - BIOS configuration 3    */
        /* ----SCSI channel Structure ---- */
        /* from "CTRL-I SCSI Host Adapter SetUp menu "  */
        u8 scsi_id;          /* 10 - Channel 0 SCSI ID       */
        u8 SCSI0Config;      /* 11 - Channel 0 SCSI configuration */
        u8 SCSI0MaxTags;     /* 12 - Channel 0 Maximum tags  */
        u8 SCSI0ResetTime;   /* 13 - Channel 0 Reset recovering समय */
        u8 Reservedक्रमChannel0[2];   /* 14 - Reserved                */

        /* ----SCSI target Structure ----  */
        /* from "CTRL-I SCSI device SetUp menu "                        */
        u8 Target00Config;   /* 16 - Channel 0 Target 0 config */
        u8 Target01Config;   /* 17 - Channel 0 Target 1 config */
        u8 Target02Config;   /* 18 - Channel 0 Target 2 config */
        u8 Target03Config;   /* 19 - Channel 0 Target 3 config */
        u8 Target04Config;   /* 1A - Channel 0 Target 4 config */
        u8 Target05Config;   /* 1B - Channel 0 Target 5 config */
        u8 Target06Config;   /* 1C - Channel 0 Target 6 config */
        u8 Target07Config;   /* 1D - Channel 0 Target 7 config */
        u8 Target08Config;   /* 1E - Channel 0 Target 8 config */
        u8 Target09Config;   /* 1F - Channel 0 Target 9 config */
        u8 Target0AConfig;   /* 20 - Channel 0 Target A config */
        u8 Target0BConfig;   /* 21 - Channel 0 Target B config */
        u8 Target0CConfig;   /* 22 - Channel 0 Target C config */
        u8 Target0DConfig;   /* 23 - Channel 0 Target D config */
        u8 Target0EConfig;   /* 24 - Channel 0 Target E config */
        u8 Target0FConfig;   /* 25 - Channel 0 Target F config */

        u8 SCSI1Id;          /* 26 - Channel 1 SCSI ID       */
        u8 SCSI1Config;      /* 27 - Channel 1 SCSI configuration */
        u8 SCSI1MaxTags;     /* 28 - Channel 1 Maximum tags  */
        u8 SCSI1ResetTime;   /* 29 - Channel 1 Reset recovering समय */
        u8 Reservedक्रमChannel1[2];   /* 2A - Reserved                */

        /* ----SCSI target Structure ----  */
        /* from "CTRL-I SCSI device SetUp menu "                                          */
        u8 Target10Config;   /* 2C - Channel 1 Target 0 config */
        u8 Target11Config;   /* 2D - Channel 1 Target 1 config */
        u8 Target12Config;   /* 2E - Channel 1 Target 2 config */
        u8 Target13Config;   /* 2F - Channel 1 Target 3 config */
        u8 Target14Config;   /* 30 - Channel 1 Target 4 config */
        u8 Target15Config;   /* 31 - Channel 1 Target 5 config */
        u8 Target16Config;   /* 32 - Channel 1 Target 6 config */
        u8 Target17Config;   /* 33 - Channel 1 Target 7 config */
        u8 Target18Config;   /* 34 - Channel 1 Target 8 config */
        u8 Target19Config;   /* 35 - Channel 1 Target 9 config */
        u8 Target1AConfig;   /* 36 - Channel 1 Target A config */
        u8 Target1BConfig;   /* 37 - Channel 1 Target B config */
        u8 Target1CConfig;   /* 38 - Channel 1 Target C config */
        u8 Target1DConfig;   /* 39 - Channel 1 Target D config */
        u8 Target1EConfig;   /* 3A - Channel 1 Target E config */
        u8 Target1FConfig;   /* 3B - Channel 1 Target F config */
        u8 reserved[3];      /* 3C - Reserved                */
        /* ---------- CheckSum ----------       */
        u8 CheckSum;         /* 3F - Checksum of NVRam       */
पूर्ण;

/* Bios Configuration क्रम nvram->BIOSConfig1                            */
#घोषणा NBC_BIOSENABLE  0x01    /* BIOS enable                    */
#घोषणा NBC_CDROM       0x02    /* Support bootable CDROM */
#घोषणा NBC_REMOVABLE   0x04    /* Support removable drive        */

/* Bios Configuration क्रम nvram->BIOSConfig2                            */
#घोषणा NBB_TARGET_MASK 0x0F    /* Boot SCSI target ID number     */
#घोषणा NBB_CHANL_MASK  0xF0    /* Boot SCSI channel number       */

/* Bit definition क्रम nvram->SCSIConfig                                 */
#घोषणा NCC_BUSRESET    0x01    /* Reset SCSI bus at घातer up     */
#घोषणा NCC_PARITYCHK   0x02    /* SCSI parity enable             */
#घोषणा NCC_LVDS        0x10    /* Enable LVDS                    */
#घोषणा NCC_ACTTERM1    0x20    /* Enable active terminator 1     */
#घोषणा NCC_ACTTERM2    0x40    /* Enable active terminator 2     */
#घोषणा NCC_AUTOTERM    0x80    /* Enable स्वतः termination        */

/* Bit definition क्रम nvram->TargetxConfig                              */
#घोषणा NTC_PERIOD      0x07    /* Maximum Sync. Speed            */
#घोषणा NTC_1GIGA       0x08    /* 255 head / 63 sectors (64/32) */
#घोषणा NTC_NO_SYNC     0x10    /* NO SYNC. NEGO          */
#घोषणा NTC_NO_WIDESYNC 0x20    /* NO WIDE SYNC. NEGO             */
#घोषणा NTC_DISC_ENABLE 0x40    /* Enable SCSI disconnect */
#घोषणा NTC_SPINUP      0x80    /* Start disk drive               */

/* Default NVRam values                                                 */
#घोषणा NBC_DEFAULT     (NBC_ENABLE)
#घोषणा NCC_DEFAULT     (NCC_BUSRESET | NCC_AUTOTERM | NCC_PARITYCHK)
#घोषणा NCC_MAX_TAGS    0x20    /* Maximum tags per target        */
#घोषणा NCC_RESET_TIME  0x0A    /* SCSI RESET recovering समय     */
#घोषणा NTC_DEFAULT     (NTC_1GIGA | NTC_NO_WIDESYNC | NTC_DISC_ENABLE)

