<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#अगर_अघोषित SYM_DEFS_H
#घोषणा SYM_DEFS_H

#घोषणा SYM_VERSION "2.2.3"
#घोषणा SYM_DRIVER_NAME	"sym-" SYM_VERSION

/*
 *	SYM53C8XX device features descriptor.
 */
काष्ठा sym_chip अणु
	u_लघु	device_id;
	u_लघु	revision_id;
	अक्षर	*name;
	u_अक्षर	burst_max;	/* log-base-2 of max burst */
	u_अक्षर	offset_max;
	u_अक्षर	nr_भागisor;
	u_अक्षर	lp_probe_bit;
	u_पूर्णांक	features;
#घोषणा FE_LED0		(1<<0)
#घोषणा FE_WIDE		(1<<1)    /* Wide data transfers */
#घोषणा FE_ULTRA	(1<<2)	  /* Ultra speed 20Mtrans/sec */
#घोषणा FE_ULTRA2	(1<<3)	  /* Ultra 2 - 40 Mtrans/sec */
#घोषणा FE_DBLR		(1<<4)	  /* Clock द्विगुनr present */
#घोषणा FE_QUAD		(1<<5)	  /* Clock quadrupler present */
#घोषणा FE_ERL		(1<<6)    /* Enable पढ़ो line */
#घोषणा FE_CLSE		(1<<7)    /* Cache line size enable */
#घोषणा FE_WRIE		(1<<8)    /* Write & Invalidate enable */
#घोषणा FE_ERMP		(1<<9)    /* Enable पढ़ो multiple */
#घोषणा FE_BOF		(1<<10)   /* Burst opcode fetch */
#घोषणा FE_DFS		(1<<11)   /* DMA fअगरo size */
#घोषणा FE_PFEN		(1<<12)   /* Prefetch enable */
#घोषणा FE_LDSTR	(1<<13)   /* Load/Store supported */
#घोषणा FE_RAM		(1<<14)   /* On chip RAM present */
#घोषणा FE_VARCLK	(1<<15)   /* Clock frequency may vary */
#घोषणा FE_RAM8K	(1<<16)   /* On chip RAM sized 8Kb */
#घोषणा FE_64BIT	(1<<17)   /* 64-bit PCI BUS पूर्णांकerface */
#घोषणा FE_IO256	(1<<18)   /* Requires full 256 bytes in PCI space */
#घोषणा FE_NOPM		(1<<19)   /* Scripts handles phase mismatch */
#घोषणा FE_LEDC		(1<<20)   /* Hardware control of LED */
#घोषणा FE_ULTRA3	(1<<21)	  /* Ultra 3 - 80 Mtrans/sec DT */
#घोषणा FE_66MHZ	(1<<22)	  /* 66MHz PCI support */
#घोषणा FE_CRC		(1<<23)	  /* CRC support */
#घोषणा FE_DIFF		(1<<24)	  /* SCSI HVD support */
#घोषणा FE_DFBC		(1<<25)	  /* Have DFBC रेजिस्टर */
#घोषणा FE_LCKFRQ	(1<<26)	  /* Have LCKFRQ */
#घोषणा FE_C10		(1<<27)	  /* Various C10 core (mis)features */
#घोषणा FE_U3EN		(1<<28)	  /* U3EN bit usable */
#घोषणा FE_DAC		(1<<29)	  /* Support PCI DAC (64 bit addressing) */
#घोषणा FE_ISTAT1 	(1<<30)   /* Have ISTAT1, MBOX0, MBOX1 रेजिस्टरs */

#घोषणा FE_CACHE_SET	(FE_ERL|FE_CLSE|FE_WRIE|FE_ERMP)
#घोषणा FE_CACHE0_SET	(FE_CACHE_SET & ~FE_ERL)
पूर्ण;

/*
 *	SYM53C8XX IO रेजिस्टर data काष्ठाure.
 */
काष्ठा sym_reg अणु
/*00*/  u8	nc_scntl0;	/* full arb., ena parity, par->ATN  */

/*01*/  u8	nc_scntl1;	/* no reset                         */
        #घोषणा   ISCON   0x10  /* connected to scsi		    */
        #घोषणा   CRST    0x08  /* क्रमce reset                      */
        #घोषणा   IARB    0x02  /* immediate arbitration            */

/*02*/  u8	nc_scntl2;	/* no disconnect expected           */
	#घोषणा   SDU     0x80  /* cmd: disconnect will उठाओ error */
	#घोषणा   CHM     0x40  /* sta: chained mode                */
	#घोषणा   WSS     0x08  /* sta: wide scsi send           [W]*/
	#घोषणा   WSR     0x01  /* sta: wide scsi received       [W]*/

/*03*/  u8	nc_scntl3;	/* cnf प्रणाली घड़ी dependent       */
	#घोषणा   EWS     0x08  /* cmd: enable wide scsi         [W]*/
	#घोषणा   ULTRA   0x80  /* cmd: ULTRA enable                */
				/* bits 0-2, 7 rsvd क्रम C1010       */

/*04*/  u8	nc_scid;	/* cnf host adapter scsi address    */
	#घोषणा   RRE     0x40  /* r/w:e enable response to resel.  */
	#घोषणा   SRE     0x20  /* r/w:e enable response to select  */

/*05*/  u8	nc_sxfer;	/* ### Sync speed and count         */
				/* bits 6-7 rsvd क्रम C1010          */

/*06*/  u8	nc_sdid;	/* ### Destination-ID               */

/*07*/  u8	nc_gpreg;	/* ??? IO-Pins                      */

/*08*/  u8	nc_sfbr;	/* ### First byte received          */

/*09*/  u8	nc_socl;
	#घोषणा   CREQ	  0x80	/* r/w: SCSI-REQ                    */
	#घोषणा   CACK	  0x40	/* r/w: SCSI-ACK                    */
	#घोषणा   CBSY	  0x20	/* r/w: SCSI-BSY                    */
	#घोषणा   CSEL	  0x10	/* r/w: SCSI-SEL                    */
	#घोषणा   CATN	  0x08	/* r/w: SCSI-ATN                    */
	#घोषणा   CMSG	  0x04	/* r/w: SCSI-MSG                    */
	#घोषणा   CC_D	  0x02	/* r/w: SCSI-C_D                    */
	#घोषणा   CI_O	  0x01	/* r/w: SCSI-I_O                    */

/*0a*/  u8	nc_ssid;

/*0b*/  u8	nc_sbcl;

/*0c*/  u8	nc_dstat;
        #घोषणा   DFE     0x80  /* sta: dma fअगरo empty              */
        #घोषणा   MDPE    0x40  /* पूर्णांक: master data parity error    */
        #घोषणा   BF      0x20  /* पूर्णांक: script: bus fault           */
        #घोषणा   ABRT    0x10  /* पूर्णांक: script: command पातed     */
        #घोषणा   SSI     0x08  /* पूर्णांक: script: single step         */
        #घोषणा   SIR     0x04  /* पूर्णांक: script: पूर्णांकerrupt inकाष्ठा. */
        #घोषणा   IID     0x01  /* पूर्णांक: script: illegal inकाष्ठा.   */

/*0d*/  u8	nc_sstat0;
        #घोषणा   ILF     0x80  /* sta: data in SIDL रेजिस्टर lsb   */
        #घोषणा   ORF     0x40  /* sta: data in SODR रेजिस्टर lsb   */
        #घोषणा   OLF     0x20  /* sta: data in SODL रेजिस्टर lsb   */
        #घोषणा   AIP     0x10  /* sta: arbitration in progress     */
        #घोषणा   LOA     0x08  /* sta: arbitration lost            */
        #घोषणा   WOA     0x04  /* sta: arbitration won             */
        #घोषणा   IRST    0x02  /* sta: scsi reset संकेत           */
        #घोषणा   SDP     0x01  /* sta: scsi parity संकेत          */

/*0e*/  u8	nc_sstat1;
	#घोषणा   FF3210  0xf0	/* sta: bytes in the scsi fअगरo      */

/*0f*/  u8	nc_sstat2;
        #घोषणा   ILF1    0x80  /* sta: data in SIDL रेजिस्टर msb[W]*/
        #घोषणा   ORF1    0x40  /* sta: data in SODR रेजिस्टर msb[W]*/
        #घोषणा   OLF1    0x20  /* sta: data in SODL रेजिस्टर msb[W]*/
        #घोषणा   DM      0x04  /* sta: DIFFSENS mismatch (895/6 only) */
        #घोषणा   LDSC    0x02  /* sta: disconnect & reconnect      */

/*10*/  u8	nc_dsa;		/* --> Base page                    */
/*11*/  u8	nc_dsa1;
/*12*/  u8	nc_dsa2;
/*13*/  u8	nc_dsa3;

/*14*/  u8	nc_istat;	/* --> Main Command and status      */
        #घोषणा   CABRT   0x80  /* cmd: पात current operation     */
        #घोषणा   SRST    0x40  /* mod: reset chip                  */
        #घोषणा   SIGP    0x20  /* r/w: message from host to script */
        #घोषणा   SEM     0x10  /* r/w: message between host + script  */
        #घोषणा   CON     0x08  /* sta: connected to scsi           */
        #घोषणा   INTF    0x04  /* sta: पूर्णांक on the fly (reset by wr)*/
        #घोषणा   SIP     0x02  /* sta: scsi-पूर्णांकerrupt              */
        #घोषणा   DIP     0x01  /* sta: host/script पूर्णांकerrupt       */

/*15*/  u8	nc_istat1;	/* 896 only */
        #घोषणा   FLSH    0x04  /* sta: chip is flushing            */
        #घोषणा   SCRUN   0x02  /* sta: scripts are running         */
        #घोषणा   SIRQD   0x01  /* r/w: disable INT pin             */

/*16*/  u8	nc_mbox0;	/* 896 only */
/*17*/  u8	nc_mbox1;	/* 896 only */

/*18*/	u8	nc_ctest0;
/*19*/  u8	nc_ctest1;

/*1a*/  u8	nc_ctest2;
	#घोषणा   CSIGP   0x40
				/* bits 0-2,7 rsvd क्रम C1010        */

/*1b*/  u8	nc_ctest3;
	#घोषणा   FLF     0x08  /* cmd: flush dma fअगरo              */
	#घोषणा   CLF	  0x04	/* cmd: clear dma fअगरo		    */
	#घोषणा   FM      0x02  /* mod: fetch pin mode              */
	#घोषणा   WRIE    0x01  /* mod: ग_लिखो and invalidate enable */
				/* bits 4-7 rsvd क्रम C1010          */

/*1c*/  u32	nc_temp;	/* ### Temporary stack              */

/*20*/	u8	nc_dfअगरo;
/*21*/  u8	nc_ctest4;
	#घोषणा   BDIS    0x80  /* mod: burst disable               */
	#घोषणा   MPEE    0x08  /* mod: master parity error enable  */

/*22*/  u8	nc_ctest5;
	#घोषणा   DFS     0x20  /* mod: dma fअगरo size               */
				/* bits 0-1, 3-7 rsvd क्रम C1010     */

/*23*/  u8	nc_ctest6;

/*24*/  u32	nc_dbc;		/* ### Byte count and command       */
/*28*/  u32	nc_dnad;	/* ### Next command रेजिस्टर        */
/*2c*/  u32	nc_dsp;		/* --> Script Poपूर्णांकer               */
/*30*/  u32	nc_dsps;	/* --> Script poपूर्णांकer save/opcode#2 */

/*34*/  u8	nc_scratcha;	/* Temporary रेजिस्टर a            */
/*35*/  u8	nc_scratcha1;
/*36*/  u8	nc_scratcha2;
/*37*/  u8	nc_scratcha3;

/*38*/  u8	nc_dmode;
	#घोषणा   BL_2    0x80  /* mod: burst length shअगरt value +2 */
	#घोषणा   BL_1    0x40  /* mod: burst length shअगरt value +1 */
	#घोषणा   ERL     0x08  /* mod: enable पढ़ो line            */
	#घोषणा   ERMP    0x04  /* mod: enable पढ़ो multiple        */
	#घोषणा   BOF     0x02  /* mod: burst op code fetch         */

/*39*/  u8	nc_dien;
/*3a*/  u8	nc_sbr;

/*3b*/  u8	nc_dcntl;	/* --> Script execution control     */
	#घोषणा   CLSE    0x80  /* mod: cache line size enable      */
	#घोषणा   PFF     0x40  /* cmd: pre-fetch flush             */
	#घोषणा   PFEN    0x20  /* mod: pre-fetch enable            */
	#घोषणा   SSM     0x10  /* mod: single step mode            */
	#घोषणा   IRQM    0x08  /* mod: irq mode (1 = totem pole !) */
	#घोषणा   STD     0x04  /* cmd: start dma mode              */
	#घोषणा   IRQD    0x02  /* mod: irq disable                 */
 	#घोषणा	  NOCOM   0x01	/* cmd: protect sfbr जबतक reselect */
				/* bits 0-1 rsvd क्रम C1010          */

/*3c*/  u32	nc_adder;

/*40*/  u16	nc_sien;	/* -->: पूर्णांकerrupt enable            */
/*42*/  u16	nc_sist;	/* <--: पूर्णांकerrupt status            */
        #घोषणा   SBMC    0x1000/* sta: SCSI Bus Mode Change (895/6 only) */
        #घोषणा   STO     0x0400/* sta: समयout (select)            */
        #घोषणा   GEN     0x0200/* sta: समयout (general)           */
        #घोषणा   HTH     0x0100/* sta: समयout (handshake)         */
        #घोषणा   MA      0x80  /* sta: phase mismatch              */
        #घोषणा   CMP     0x40  /* sta: arbitration complete        */
        #घोषणा   SEL     0x20  /* sta: selected by another device  */
        #घोषणा   RSL     0x10  /* sta: reselected by another device*/
        #घोषणा   SGE     0x08  /* sta: gross error (over/underflow)*/
        #घोषणा   UDC     0x04  /* sta: unexpected disconnect       */
        #घोषणा   RST     0x02  /* sta: scsi bus reset detected     */
        #घोषणा   PAR     0x01  /* sta: scsi parity error           */

/*44*/  u8	nc_slpar;
/*45*/  u8	nc_swide;
/*46*/  u8	nc_macntl;
/*47*/  u8	nc_gpcntl;
/*48*/  u8	nc_sसमय0;	/* cmd: समयout क्रम select&handshake*/
/*49*/  u8	nc_sसमय1;	/* cmd: समयout user defined        */
/*4a*/  u16	nc_respid;	/* sta: Reselect-IDs                */

/*4c*/  u8	nc_stest0;

/*4d*/  u8	nc_stest1;
	#घोषणा   SCLK    0x80	/* Use the PCI घड़ी as SCSI घड़ी	*/
	#घोषणा   DBLEN   0x08	/* घड़ी द्विगुनr running		*/
	#घोषणा   DBLSEL  0x04	/* घड़ी द्विगुनr selected		*/
  

/*4e*/  u8	nc_stest2;
	#घोषणा   ROF     0x40	/* reset scsi offset (after gross error!) */
	#घोषणा   EXT     0x02  /* extended filtering                     */

/*4f*/  u8	nc_stest3;
	#घोषणा   TE     0x80	/* c: tolerAnt enable */
	#घोषणा   HSC    0x20	/* c: Halt SCSI Clock */
	#घोषणा   CSF    0x02	/* c: clear scsi fअगरo */

/*50*/  u16	nc_sidl;	/* Lowlevel: latched from scsi data */
/*52*/  u8	nc_stest4;
	#घोषणा   SMODE  0xc0	/* SCSI bus mode      (895/6 only) */
	#घोषणा    SMODE_HVD 0x40	/* High Voltage Dअगरferential       */
	#घोषणा    SMODE_SE  0x80	/* Single Ended                    */
	#घोषणा    SMODE_LVD 0xc0	/* Low Voltage Dअगरferential        */
	#घोषणा   LCKFRQ 0x20	/* Frequency Lock (895/6 only)     */
				/* bits 0-5 rsvd क्रम C1010         */

/*53*/  u8	nc_53_;
/*54*/  u16	nc_sodl;	/* Lowlevel: data out to scsi data  */
/*56*/	u8	nc_ccntl0;	/* Chip Control 0 (896)             */
	#घोषणा   ENPMJ  0x80	/* Enable Phase Mismatch Jump       */
	#घोषणा   PMJCTL 0x40	/* Phase Mismatch Jump Control      */
	#घोषणा   ENNDJ  0x20	/* Enable Non Data PM Jump          */
	#घोषणा   DISFC  0x10	/* Disable Auto FIFO Clear          */
	#घोषणा   DILS   0x02	/* Disable Internal Load/Store      */
	#घोषणा   DPR    0x01	/* Disable Pipe Req                 */

/*57*/	u8	nc_ccntl1;	/* Chip Control 1 (896)             */
	#घोषणा   ZMOD   0x80	/* High Impedance Mode              */
	#घोषणा   DDAC   0x08	/* Disable Dual Address Cycle       */
	#घोषणा   XTIMOD 0x04	/* 64-bit Table Ind. Indexing Mode  */
	#घोषणा   EXTIBMV 0x02	/* Enable 64-bit Table Ind. BMOV    */
	#घोषणा   EXDBMV 0x01	/* Enable 64-bit Direct BMOV        */

/*58*/  u16	nc_sbdl;	/* Lowlevel: data from scsi data    */
/*5a*/  u16	nc_5a_;

/*5c*/  u8	nc_scr0;	/* Working रेजिस्टर B               */
/*5d*/  u8	nc_scr1;
/*5e*/  u8	nc_scr2;
/*5f*/  u8	nc_scr3;

/*60*/  u8	nc_scrx[64];	/* Working रेजिस्टर C-R             */
/*a0*/	u32	nc_mmrs;	/* Memory Move Read Selector        */
/*a4*/	u32	nc_mmws;	/* Memory Move Write Selector       */
/*a8*/	u32	nc_sfs;		/* Script Fetch Selector            */
/*ac*/	u32	nc_drs;		/* DSA Relative Selector            */
/*b0*/	u32	nc_sbms;	/* Static Block Move Selector       */
/*b4*/	u32	nc_dbms;	/* Dynamic Block Move Selector      */
/*b8*/	u32	nc_dnad64;	/* DMA Next Address 64              */
/*bc*/	u16	nc_scntl4;	/* C1010 only                       */
	#घोषणा   U3EN    0x80	/* Enable Ultra 3                   */
	#घोषणा   AIPCKEN 0x40  /* AIP checking enable              */
				/* Also enable AIP generation on C10-33*/
	#घोषणा   XCLKH_DT 0x08 /* Extra घड़ी of data hold on DT edge */
	#घोषणा   XCLKH_ST 0x04 /* Extra घड़ी of data hold on ST edge */
	#घोषणा   XCLKS_DT 0x02 /* Extra घड़ी of data set  on DT edge */
	#घोषणा   XCLKS_ST 0x01 /* Extra घड़ी of data set  on ST edge */
/*be*/	u8	nc_aipcntl0;	/* AIP Control 0 C1010 only         */
/*bf*/	u8	nc_aipcntl1;	/* AIP Control 1 C1010 only         */
	#घोषणा DISAIP  0x08	/* Disable AIP generation C10-66 only  */
/*c0*/	u32	nc_pmjad1;	/* Phase Mismatch Jump Address 1    */
/*c4*/	u32	nc_pmjad2;	/* Phase Mismatch Jump Address 2    */
/*c8*/	u8	nc_rbc;		/* Reमुख्यing Byte Count             */
/*c9*/	u8	nc_rbc1;
/*ca*/	u8	nc_rbc2;
/*cb*/	u8	nc_rbc3;

/*cc*/	u8	nc_ua;		/* Updated Address                  */
/*cd*/	u8	nc_ua1;
/*ce*/	u8	nc_ua2;
/*cf*/	u8	nc_ua3;
/*d0*/	u32	nc_esa;		/* Entry Storage Address            */
/*d4*/	u8	nc_ia;		/* Inकाष्ठाion Address              */
/*d5*/	u8	nc_ia1;
/*d6*/	u8	nc_ia2;
/*d7*/	u8	nc_ia3;
/*d8*/	u32	nc_sbc;		/* SCSI Byte Count (3 bytes only)   */
/*dc*/	u32	nc_csbc;	/* Cumulative SCSI Byte Count       */
                                /* Following क्रम C1010 only         */
/*e0*/	u16    nc_crcpad;	/* CRC Value                        */
/*e2*/	u8     nc_crccntl0;	/* CRC control रेजिस्टर             */
	#घोषणा   SNDCRC  0x10	/* Send CRC Request                 */
/*e3*/	u8     nc_crccntl1;	/* CRC control रेजिस्टर             */
/*e4*/	u32    nc_crcdata;	/* CRC data रेजिस्टर                */
/*e8*/	u32    nc_e8_;
/*ec*/	u32    nc_ec_;
/*f0*/	u16    nc_dfbc;		/* DMA FIFO byte count              */ 
पूर्ण;

/*-----------------------------------------------------------
 *
 *	Utility macros क्रम the script.
 *
 *-----------------------------------------------------------
 */

#घोषणा REGJ(p,r) (दुरत्व(काष्ठा sym_reg, p ## r))
#घोषणा REG(r) REGJ (nc_, r)

/*-----------------------------------------------------------
 *
 *	SCSI phases
 *
 *-----------------------------------------------------------
 */

#घोषणा	SCR_DATA_OUT	0x00000000
#घोषणा	SCR_DATA_IN	0x01000000
#घोषणा	SCR_COMMAND	0x02000000
#घोषणा	SCR_STATUS	0x03000000
#घोषणा	SCR_DT_DATA_OUT	0x04000000
#घोषणा	SCR_DT_DATA_IN	0x05000000
#घोषणा SCR_MSG_OUT	0x06000000
#घोषणा SCR_MSG_IN      0x07000000
/* DT phases are illegal क्रम non Ultra3 mode */
#घोषणा SCR_ILG_OUT	0x04000000
#घोषणा SCR_ILG_IN	0x05000000

/*-----------------------------------------------------------
 *
 *	Data transfer via SCSI.
 *
 *-----------------------------------------------------------
 *
 *	MOVE_ABS (LEN)
 *	<<start address>>
 *
 *	MOVE_IND (LEN)
 *	<<dnad_offset>>
 *
 *	MOVE_TBL
 *	<<dnad_offset>>
 *
 *-----------------------------------------------------------
 */

#घोषणा OPC_MOVE          0x08000000

#घोषणा SCR_MOVE_ABS(l) ((0x00000000 | OPC_MOVE) | (l))
/* #घोषणा SCR_MOVE_IND(l) ((0x20000000 | OPC_MOVE) | (l)) */
#घोषणा SCR_MOVE_TBL     (0x10000000 | OPC_MOVE)

#घोषणा SCR_CHMOV_ABS(l) ((0x00000000) | (l))
/* #घोषणा SCR_CHMOV_IND(l) ((0x20000000) | (l)) */
#घोषणा SCR_CHMOV_TBL     (0x10000000)

#अगर_घोषित SYM_CONF_TARGET_ROLE_SUPPORT
/* We steal the `indirect addressing' flag क्रम target mode MOVE in scripts */

#घोषणा OPC_TCHMOVE        0x08000000

#घोषणा SCR_TCHMOVE_ABS(l) ((0x20000000 | OPC_TCHMOVE) | (l))
#घोषणा SCR_TCHMOVE_TBL     (0x30000000 | OPC_TCHMOVE)

#घोषणा SCR_TMOV_ABS(l)    ((0x20000000) | (l))
#घोषणा SCR_TMOV_TBL        (0x30000000)
#पूर्ण_अगर

काष्ठा sym_tblmove अणु
        u32  size;
        u32  addr;
पूर्ण;

/*-----------------------------------------------------------
 *
 *	Selection
 *
 *-----------------------------------------------------------
 *
 *	SEL_ABS | SCR_ID (0..15)    [ | REL_JMP]
 *	<<alternate_address>>
 *
 *	SEL_TBL | << dnad_offset>>  [ | REL_JMP]
 *	<<alternate_address>>
 *
 *-----------------------------------------------------------
 */

#घोषणा	SCR_SEL_ABS	0x40000000
#घोषणा	SCR_SEL_ABS_ATN	0x41000000
#घोषणा	SCR_SEL_TBL	0x42000000
#घोषणा	SCR_SEL_TBL_ATN	0x43000000

#अगर_घोषित SYM_CONF_TARGET_ROLE_SUPPORT
#घोषणा	SCR_RESEL_ABS     0x40000000
#घोषणा	SCR_RESEL_ABS_ATN 0x41000000
#घोषणा	SCR_RESEL_TBL     0x42000000
#घोषणा	SCR_RESEL_TBL_ATN 0x43000000
#पूर्ण_अगर

काष्ठा sym_tblsel अणु
        u_अक्षर  sel_scntl4;	/* C1010 only */
        u_अक्षर  sel_sxfer;
        u_अक्षर  sel_id;
        u_अक्षर  sel_scntl3;
पूर्ण;

#घोषणा SCR_JMP_REL     0x04000000
#घोषणा SCR_ID(id)	(((u32)(id)) << 16)

/*-----------------------------------------------------------
 *
 *	Waiting क्रम Disconnect or Reselect
 *
 *-----------------------------------------------------------
 *
 *	WAIT_DISC
 *	dummy: <<alternate_address>>
 *
 *	WAIT_RESEL
 *	<<alternate_address>>
 *
 *-----------------------------------------------------------
 */

#घोषणा	SCR_WAIT_DISC	0x48000000
#घोषणा SCR_WAIT_RESEL  0x50000000

#अगर_घोषित SYM_CONF_TARGET_ROLE_SUPPORT
#घोषणा	SCR_DISCONNECT	0x48000000
#पूर्ण_अगर

/*-----------------------------------------------------------
 *
 *	Bit Set / Reset
 *
 *-----------------------------------------------------------
 *
 *	SET (flags अणु|.. पूर्ण)
 *
 *	CLR (flags अणु|.. पूर्ण)
 *
 *-----------------------------------------------------------
 */

#घोषणा SCR_SET(f)     (0x58000000 | (f))
#घोषणा SCR_CLR(f)     (0x60000000 | (f))

#घोषणा	SCR_CARRY	0x00000400
#घोषणा	SCR_TRG		0x00000200
#घोषणा	SCR_ACK		0x00000040
#घोषणा	SCR_ATN		0x00000008


/*-----------------------------------------------------------
 *
 *	Memory to memory move
 *
 *-----------------------------------------------------------
 *
 *	COPY (bytecount)
 *	<< source_address >>
 *	<< destination_address >>
 *
 *	SCR_COPY   sets the NO FLUSH option by शेष.
 *	SCR_COPY_F करोes not set this option.
 *
 *	For chips which करो not support this option,
 *	sym_fw_bind_script() will हटाओ this bit.
 *
 *-----------------------------------------------------------
 */

#घोषणा SCR_NO_FLUSH 0x01000000

#घोषणा SCR_COPY(n) (0xc0000000 | SCR_NO_FLUSH | (n))
#घोषणा SCR_COPY_F(n) (0xc0000000 | (n))

/*-----------------------------------------------------------
 *
 *	Register move and binary operations
 *
 *-----------------------------------------------------------
 *
 *	SFBR_REG (reg, op, data)        reg  = SFBR op data
 *	<< 0 >>
 *
 *	REG_SFBR (reg, op, data)        SFBR = reg op data
 *	<< 0 >>
 *
 *	REG_REG  (reg, op, data)        reg  = reg op data
 *	<< 0 >>
 *
 *-----------------------------------------------------------
 *
 *	On 825A, 875, 895 and 896 chips the content 
 *	of SFBR रेजिस्टर can be used as data (SCR_SFBR_DATA).
 *	The 896 has additionnal IO रेजिस्टरs starting at 
 *	offset 0x80. Bit 7 of रेजिस्टर offset is stored in 
 *	bit 7 of the SCRIPTS inकाष्ठाion first DWORD.
 *
 *-----------------------------------------------------------
 */

#घोषणा SCR_REG_OFS(ofs) ((((ofs) & 0x7f) << 16ul) + ((ofs) & 0x80)) 

#घोषणा SCR_SFBR_REG(reg,op,data) \
        (0x68000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&0xff)<<8ul))

#घोषणा SCR_REG_SFBR(reg,op,data) \
        (0x70000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&0xff)<<8ul))

#घोषणा SCR_REG_REG(reg,op,data) \
        (0x78000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&0xff)<<8ul))


#घोषणा      SCR_LOAD   0x00000000
#घोषणा      SCR_SHL    0x01000000
#घोषणा      SCR_OR     0x02000000
#घोषणा      SCR_XOR    0x03000000
#घोषणा      SCR_AND    0x04000000
#घोषणा      SCR_SHR    0x05000000
#घोषणा      SCR_ADD    0x06000000
#घोषणा      SCR_ADDC   0x07000000

#घोषणा      SCR_SFBR_DATA   (0x00800000>>8ul)	/* Use SFBR as data */

/*-----------------------------------------------------------
 *
 *	FROM_REG (reg)		  SFBR = reg
 *	<< 0 >>
 *
 *	TO_REG	 (reg)		  reg  = SFBR
 *	<< 0 >>
 *
 *	LOAD_REG (reg, data)	  reg  = <data>
 *	<< 0 >>
 *
 *	LOAD_SFBR(data) 	  SFBR = <data>
 *	<< 0 >>
 *
 *-----------------------------------------------------------
 */

#घोषणा	SCR_FROM_REG(reg) \
	SCR_REG_SFBR(reg,SCR_OR,0)

#घोषणा	SCR_TO_REG(reg) \
	SCR_SFBR_REG(reg,SCR_OR,0)

#घोषणा	SCR_LOAD_REG(reg,data) \
	SCR_REG_REG(reg,SCR_LOAD,data)

#घोषणा SCR_LOAD_SFBR(data) \
        (SCR_REG_SFBR (gpreg, SCR_LOAD, data))

/*-----------------------------------------------------------
 *
 *	LOAD  from memory   to रेजिस्टर.
 *	STORE from रेजिस्टर to memory.
 *
 *	Only supported by 810A, 860, 825A, 875, 895 and 896.
 *
 *-----------------------------------------------------------
 *
 *	LOAD_ABS (LEN)
 *	<<start address>>
 *
 *	LOAD_REL (LEN)        (DSA relative)
 *	<<dsa_offset>>
 *
 *-----------------------------------------------------------
 */

#घोषणा SCR_REG_OFS2(ofs) (((ofs) & 0xff) << 16ul)
#घोषणा SCR_NO_FLUSH2	0x02000000
#घोषणा SCR_DSA_REL2	0x10000000

#घोषणा SCR_LOAD_R(reg, how, n) \
        (0xe1000000 | how | (SCR_REG_OFS2(REG(reg))) | (n))

#घोषणा SCR_STORE_R(reg, how, n) \
        (0xe0000000 | how | (SCR_REG_OFS2(REG(reg))) | (n))

#घोषणा SCR_LOAD_ABS(reg, n)	SCR_LOAD_R(reg, SCR_NO_FLUSH2, n)
#घोषणा SCR_LOAD_REL(reg, n)	SCR_LOAD_R(reg, SCR_NO_FLUSH2|SCR_DSA_REL2, n)
#घोषणा SCR_LOAD_ABS_F(reg, n)	SCR_LOAD_R(reg, 0, n)
#घोषणा SCR_LOAD_REL_F(reg, n)	SCR_LOAD_R(reg, SCR_DSA_REL2, n)

#घोषणा SCR_STORE_ABS(reg, n)	SCR_STORE_R(reg, SCR_NO_FLUSH2, n)
#घोषणा SCR_STORE_REL(reg, n)	SCR_STORE_R(reg, SCR_NO_FLUSH2|SCR_DSA_REL2,n)
#घोषणा SCR_STORE_ABS_F(reg, n)	SCR_STORE_R(reg, 0, n)
#घोषणा SCR_STORE_REL_F(reg, n)	SCR_STORE_R(reg, SCR_DSA_REL2, n)


/*-----------------------------------------------------------
 *
 *	Waiting क्रम Disconnect or Reselect
 *
 *-----------------------------------------------------------
 *
 *	JUMP            [ | IFTRUE/IFFALSE ( ... ) ]
 *	<<address>>
 *
 *	JUMPR           [ | IFTRUE/IFFALSE ( ... ) ]
 *	<<distance>>
 *
 *	CALL            [ | IFTRUE/IFFALSE ( ... ) ]
 *	<<address>>
 *
 *	CALLR           [ | IFTRUE/IFFALSE ( ... ) ]
 *	<<distance>>
 *
 *	RETURN          [ | IFTRUE/IFFALSE ( ... ) ]
 *	<<dummy>>
 *
 *	INT             [ | IFTRUE/IFFALSE ( ... ) ]
 *	<<ident>>
 *
 *	INT_FLY         [ | IFTRUE/IFFALSE ( ... ) ]
 *	<<ident>>
 *
 *	Conditions:
 *	     WHEN (phase)
 *	     IF   (phase)
 *	     CARRYSET
 *	     DATA (data, mask)
 *
 *-----------------------------------------------------------
 */

#घोषणा SCR_NO_OP       0x80000000
#घोषणा SCR_JUMP        0x80080000
#घोषणा SCR_JUMP64      0x80480000
#घोषणा SCR_JUMPR       0x80880000
#घोषणा SCR_CALL        0x88080000
#घोषणा SCR_CALLR       0x88880000
#घोषणा SCR_RETURN      0x90080000
#घोषणा SCR_INT         0x98080000
#घोषणा SCR_INT_FLY     0x98180000

#घोषणा IFFALSE(arg)   (0x00080000 | (arg))
#घोषणा IFTRUE(arg)    (0x00000000 | (arg))

#घोषणा WHEN(phase)    (0x00030000 | (phase))
#घोषणा IF(phase)      (0x00020000 | (phase))

#घोषणा DATA(D)        (0x00040000 | ((D) & 0xff))
#घोषणा MASK(D,M)      (0x00040000 | (((M ^ 0xff) & 0xff) << 8ul)|((D) & 0xff))

#घोषणा CARRYSET       (0x00200000)

/*-----------------------------------------------------------
 *
 *	SCSI  स्थिरants.
 *
 *-----------------------------------------------------------
 */

/*
 *	Messages
 */

#घोषणा	M_COMPLETE	COMMAND_COMPLETE
#घोषणा	M_EXTENDED	EXTENDED_MESSAGE
#घोषणा	M_SAVE_DP	SAVE_POINTERS
#घोषणा	M_RESTORE_DP	RESTORE_POINTERS
#घोषणा	M_DISCONNECT	DISCONNECT
#घोषणा	M_ID_ERROR	INITIATOR_ERROR
#घोषणा	M_ABORT		ABORT_TASK_SET
#घोषणा	M_REJECT	MESSAGE_REJECT
#घोषणा	M_NOOP		NOP
#घोषणा	M_PARITY	MSG_PARITY_ERROR
#घोषणा	M_LCOMPLETE	LINKED_CMD_COMPLETE
#घोषणा	M_FCOMPLETE	LINKED_FLG_CMD_COMPLETE
#घोषणा	M_RESET		TARGET_RESET
#घोषणा	M_ABORT_TAG	ABORT_TASK
#घोषणा	M_CLEAR_QUEUE	CLEAR_TASK_SET
#घोषणा	M_INIT_REC	INITIATE_RECOVERY
#घोषणा	M_REL_REC	RELEASE_RECOVERY
#घोषणा	M_TERMINATE	(0x11)
#घोषणा	M_SIMPLE_TAG	SIMPLE_QUEUE_TAG
#घोषणा	M_HEAD_TAG	HEAD_OF_QUEUE_TAG
#घोषणा	M_ORDERED_TAG	ORDERED_QUEUE_TAG
#घोषणा	M_IGN_RESIDUE	IGNORE_WIDE_RESIDUE

#घोषणा	M_X_MODIFY_DP	EXTENDED_MODIFY_DATA_POINTER
#घोषणा	M_X_SYNC_REQ	EXTENDED_SDTR
#घोषणा	M_X_WIDE_REQ	EXTENDED_WDTR
#घोषणा	M_X_PPR_REQ	EXTENDED_PPR

/*
 *	PPR protocol options
 */
#घोषणा	PPR_OPT_IU	(0x01)
#घोषणा	PPR_OPT_DT	(0x02)
#घोषणा	PPR_OPT_QAS	(0x04)
#घोषणा PPR_OPT_MASK	(0x07)

/*
 *	Status
 */

#घोषणा	S_GOOD		SAM_STAT_GOOD
#घोषणा	S_CHECK_COND	SAM_STAT_CHECK_CONDITION
#घोषणा	S_COND_MET	SAM_STAT_CONDITION_MET
#घोषणा	S_BUSY		SAM_STAT_BUSY
#घोषणा	S_INT		SAM_STAT_INTERMEDIATE
#घोषणा	S_INT_COND_MET	SAM_STAT_INTERMEDIATE_CONDITION_MET
#घोषणा	S_CONFLICT	SAM_STAT_RESERVATION_CONFLICT
#घोषणा	S_TERMINATED	SAM_STAT_COMMAND_TERMINATED
#घोषणा	S_QUEUE_FULL	SAM_STAT_TASK_SET_FULL
#घोषणा	S_ILLEGAL	(0xff)

#पूर्ण_अगर /* defined SYM_DEFS_H */
