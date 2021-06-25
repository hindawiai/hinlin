<शैली गुरु>
/*
 * Core definitions and data काष्ठाures shareable across OS platक्रमms.
 *
 * Copyright (c) 1994-2002 Justin T. Gibbs.
 * Copyright (c) 2000-2002 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic79xx.h#109 $
 *
 * $FreeBSD$
 */

#अगर_अघोषित _AIC79XX_H_
#घोषणा _AIC79XX_H_

/* Register Definitions */
#समावेश "aic79xx_reg.h"

/************************* Forward Declarations *******************************/
काष्ठा ahd_platक्रमm_data;
काष्ठा scb_platक्रमm_data;

/****************************** Useful Macros *********************************/
#अगर_अघोषित TRUE
#घोषणा TRUE 1
#पूर्ण_अगर
#अगर_अघोषित FALSE
#घोषणा FALSE 0
#पूर्ण_अगर

#घोषणा ALL_CHANNELS '\0'
#घोषणा ALL_TARGETS_MASK 0xFFFF
#घोषणा INITIATOR_WILDCARD	(~0)
#घोषणा	SCB_LIST_शून्य		0xFF00
#घोषणा	SCB_LIST_शून्य_LE	(ahd_htole16(SCB_LIST_शून्य))
#घोषणा QOUTFIFO_ENTRY_VALID 0x80
#घोषणा SCBID_IS_शून्य(scbid) (((scbid) & 0xFF00 ) == SCB_LIST_शून्य)

#घोषणा SCSIID_TARGET(ahd, scsiid)	\
	(((scsiid) & TID) >> TID_SHIFT)
#घोषणा SCSIID_OUR_ID(scsiid)		\
	((scsiid) & OID)
#घोषणा SCSIID_CHANNEL(ahd, scsiid) ('A')
#घोषणा	SCB_IS_SCSIBUS_B(ahd, scb) (0)
#घोषणा	SCB_GET_OUR_ID(scb) \
	SCSIID_OUR_ID((scb)->hscb->scsiid)
#घोषणा	SCB_GET_TARGET(ahd, scb) \
	SCSIID_TARGET((ahd), (scb)->hscb->scsiid)
#घोषणा	SCB_GET_CHANNEL(ahd, scb) \
	SCSIID_CHANNEL(ahd, (scb)->hscb->scsiid)
#घोषणा	SCB_GET_LUN(scb) \
	((scb)->hscb->lun)
#घोषणा SCB_GET_TARGET_OFFSET(ahd, scb)	\
	SCB_GET_TARGET(ahd, scb)
#घोषणा SCB_GET_TARGET_MASK(ahd, scb) \
	(0x01 << (SCB_GET_TARGET_OFFSET(ahd, scb)))
#अगर_घोषित AHD_DEBUG
#घोषणा SCB_IS_SILENT(scb)					\
	((ahd_debug & AHD_SHOW_MASKED_ERRORS) == 0		\
      && (((scb)->flags & SCB_SILENT) != 0))
#अन्यथा
#घोषणा SCB_IS_SILENT(scb)					\
	(((scb)->flags & SCB_SILENT) != 0)
#पूर्ण_अगर
/*
 * TCLs have the following क्रमmat: TTTTLLLLLLLL
 */
#घोषणा TCL_TARGET_OFFSET(tcl) \
	((((tcl) >> 4) & TID) >> 4)
#घोषणा TCL_LUN(tcl) \
	(tcl & (AHD_NUM_LUNS - 1))
#घोषणा BUILD_TCL(scsiid, lun) \
	((lun) | (((scsiid) & TID) << 4))
#घोषणा BUILD_TCL_RAW(target, channel, lun) \
	((lun) | ((target) << 8))

#घोषणा SCB_GET_TAG(scb) \
	ahd_le16toh(scb->hscb->tag)

#अगर_अघोषित	AHD_TARGET_MODE
#अघोषित	AHD_TMODE_ENABLE
#घोषणा	AHD_TMODE_ENABLE 0
#पूर्ण_अगर

#घोषणा AHD_BUILD_COL_IDX(target, lun)				\
	((((u8)lun) << 4) | target)

#घोषणा AHD_GET_SCB_COL_IDX(ahd, scb)				\
	((SCB_GET_LUN(scb) << 4) | SCB_GET_TARGET(ahd, scb))

#घोषणा AHD_SET_SCB_COL_IDX(scb, col_idx)				\
करो अणु									\
	(scb)->hscb->scsiid = ((col_idx) << TID_SHIFT) & TID;		\
	(scb)->hscb->lun = ((col_idx) >> 4) & (AHD_NUM_LUNS_NONPKT-1);	\
पूर्ण जबतक (0)

#घोषणा AHD_COPY_SCB_COL_IDX(dst, src)				\
करो अणु								\
	dst->hscb->scsiid = src->hscb->scsiid;			\
	dst->hscb->lun = src->hscb->lun;			\
पूर्ण जबतक (0)

#घोषणा	AHD_NEVER_COL_IDX 0xFFFF

/**************************** Driver Constants ********************************/
/*
 * The maximum number of supported tarमाला_लो.
 */
#घोषणा AHD_NUM_TARGETS 16

/*
 * The maximum number of supported luns.
 * The identअगरy message only supports 64 luns in non-packetized transfers.
 * You can have 2^64 luns when inक्रमmation unit transfers are enabled,
 * but until we see a need to support that many, we support 256.
 */
#घोषणा AHD_NUM_LUNS_NONPKT 64
#घोषणा AHD_NUM_LUNS 256

/*
 * The maximum transfer per S/G segment.
 */
#घोषणा AHD_MAXTRANSFER_SIZE	 0x00ffffff	/* limited by 24bit counter */

/*
 * The maximum amount of SCB storage in hardware on a controller.
 * This value represents an upper bound.  Due to software design,
 * we may not be able to use this number.
 */
#घोषणा AHD_SCB_MAX	512

/*
 * The maximum number of concurrent transactions supported per driver instance.
 * Sequencer Control Blocks (SCBs) store per-transaction inक्रमmation.
 */
#घोषणा AHD_MAX_QUEUE	AHD_SCB_MAX

/*
 * Define the size of our QIN and QOUT FIFOs.  They must be a घातer of 2
 * in size and accommodate as many transactions as can be queued concurrently.
 */
#घोषणा	AHD_QIN_SIZE	AHD_MAX_QUEUE
#घोषणा	AHD_QOUT_SIZE	AHD_MAX_QUEUE

#घोषणा AHD_QIN_WRAP(x) ((x) & (AHD_QIN_SIZE-1))
/*
 * The maximum amount of SCB storage we allocate in host memory.
 */
#घोषणा AHD_SCB_MAX_ALLOC AHD_MAX_QUEUE

/*
 * Ring Buffer of incoming target commands.
 * We allocate 256 to simplअगरy the logic in the sequencer
 * by using the natural wrap poपूर्णांक of an 8bit counter.
 */
#घोषणा AHD_TMODE_CMDS	256

/* Reset line निश्चितion समय in us */
#घोषणा AHD_BUSRESET_DELAY	25

/******************* Chip Characteristics/Operating Settings  *****************/
/*
 * Chip Type
 * The chip order is from least sophisticated to most sophisticated.
 */
प्रकार क्रमागत अणु
	AHD_NONE	= 0x0000,
	AHD_CHIPID_MASK	= 0x00FF,
	AHD_AIC7901	= 0x0001,
	AHD_AIC7902	= 0x0002,
	AHD_AIC7901A	= 0x0003,
	AHD_PCI		= 0x0100,	/* Bus type PCI */
	AHD_PCIX	= 0x0200,	/* Bus type PCIX */
	AHD_BUS_MASK	= 0x0F00
पूर्ण ahd_chip;

/*
 * Features available in each chip type.
 */
प्रकार क्रमागत अणु
	AHD_FENONE		= 0x00000,
	AHD_WIDE		= 0x00001,/* Wide Channel */
	AHD_AIC79XXB_SLOWCRC    = 0x00002,/* SLOWCRC bit should be set */
	AHD_MULTI_FUNC		= 0x00100,/* Multi-Function/Channel Device */
	AHD_TARGETMODE		= 0x01000,/* Has tested target mode support */
	AHD_MULTIROLE		= 0x02000,/* Space क्रम two roles at a समय */
	AHD_RTI			= 0x04000,/* Retained Training Support */
	AHD_NEW_IOCELL_OPTS	= 0x08000,/* More Signal knobs in the IOCELL */
	AHD_NEW_DFCNTRL_OPTS	= 0x10000,/* SCSIENWRDIS bit */
	AHD_FAST_CDB_DELIVERY	= 0x20000,/* CDB acks released to Output Sync */
	AHD_REMOVABLE		= 0x00000,/* Hot-Swap supported - None so far*/
	AHD_AIC7901_FE		= AHD_FENONE,
	AHD_AIC7901A_FE		= AHD_FENONE,
	AHD_AIC7902_FE		= AHD_MULTI_FUNC
पूर्ण ahd_feature;

/*
 * Bugs in the silicon that we work around in software.
 */
प्रकार क्रमागत अणु
	AHD_BUGNONE		= 0x0000,
	/*
	 * Rev A hardware fails to update LAST/CURR/NEXTSCB
	 * correctly in certain packetized selection हालs.
	 */
	AHD_SENT_SCB_UPDATE_BUG	= 0x0001,
	/* The wrong SCB is accessed to check the पात pending bit. */
	AHD_ABORT_LQI_BUG	= 0x0002,
	/* Packetized bitbucket crosses packet boundaries. */
	AHD_PKT_BITBUCKET_BUG	= 0x0004,
	/* The selection समयr runs twice as दीर्घ as its setting. */
	AHD_LONG_SETIMO_BUG	= 0x0008,
	/* The Non-LQ CRC error status is delayed until phase change. */
	AHD_NLQICRC_DELAYED_BUG	= 0x0010,
	/* The chip must be reset क्रम all outgoing bus resets.  */
	AHD_SCSIRST_BUG		= 0x0020,
	/* Some PCIX fields must be saved and restored across chip reset. */
	AHD_PCIX_CHIPRST_BUG	= 0x0040,
	/* MMAPIO is not functional in PCI-X mode.  */
	AHD_PCIX_MMAPIO_BUG	= 0x0080,
	/* Reads to SCBRAM fail to reset the discard समयr. */
	AHD_PCIX_SCBRAM_RD_BUG  = 0x0100,
	/* Bug workarounds that can be disabled on non-PCIX busses. */
	AHD_PCIX_BUG_MASK	= AHD_PCIX_CHIPRST_BUG
				| AHD_PCIX_MMAPIO_BUG
				| AHD_PCIX_SCBRAM_RD_BUG,
	/*
	 * LQOSTOP0 status set even क्रम क्रमced selections with ATN
	 * to perक्रमm non-packetized message delivery.
	 */
	AHD_LQO_ATNO_BUG	= 0x0200,
	/* FIFO स्वतः-flush करोes not always trigger.  */
	AHD_AUTOFLUSH_BUG	= 0x0400,
	/* The CLRLQO रेजिस्टरs are not self-clearing. */
	AHD_CLRLQO_AUTOCLR_BUG	= 0x0800,
	/* The PACKETIZED status bit refers to the previous connection. */
	AHD_PKTIZED_STATUS_BUG  = 0x1000,
	/* "Short Luns" are not placed पूर्णांकo outgoing LQ packets correctly. */
	AHD_PKT_LUN_BUG		= 0x2000,
	/*
	 * Only the FIFO allocated to the non-packetized connection may
	 * be in use during a non-packetzied connection.
	 */
	AHD_NONPACKFIFO_BUG	= 0x4000,
	/*
	 * Writing to a DFF SCBPTR रेजिस्टर may fail अगर concurent with
	 * a hardware ग_लिखो to the other DFF SCBPTR रेजिस्टर.  This is
	 * not currently a concern in our sequencer since all chips with
	 * this bug have the AHD_NONPACKFIFO_BUG and all ग_लिखोs of concern
	 * occur in non-packetized connections.
	 */
	AHD_MDFF_WSCBPTR_BUG	= 0x8000,
	/* SGHADDR updates are slow. */
	AHD_REG_SLOW_SETTLE_BUG	= 0x10000,
	/*
	 * Changing the MODE_PTR coincident with an पूर्णांकerrupt that
	 * चयनes to a dअगरferent mode will cause the पूर्णांकerrupt to
	 * be in the mode written outside of पूर्णांकerrupt context.
	 */
	AHD_SET_MODE_BUG	= 0x20000,
	/* Non-packetized busमुक्त revision करोes not work. */
	AHD_BUSFREEREV_BUG	= 0x40000,
	/*
	 * Paced transfers are indicated with a non-standard PPR
	 * option bit in the neg table, 160MHz is indicated by
	 * sync factor 0x7, and the offset अगर off by a factor of 2.
	 */
	AHD_PACED_NEGTABLE_BUG	= 0x80000,
	/* LQOOVERRUN false positives. */
	AHD_LQOOVERRUN_BUG	= 0x100000,
	/*
	 * Controller ग_लिखो to INTSTAT will lose to a host
	 * ग_लिखो to CLRINT.
	 */
	AHD_INTCOLLISION_BUG	= 0x200000,
	/*
	 * The GEM318 violates the SCSI spec by not रुकोing
	 * the mandated bus settle delay between phase changes
	 * in some situations.  Some aic79xx chip revs. are more
	 * strict in this regard and will treat REQ निश्चितions
	 * that fall within the bus settle delay winकरोw as
	 * glitches.  This flag tells the firmware to tolerate
	 * early REQ निश्चितions.
	 */
	AHD_EARLY_REQ_BUG	= 0x400000,
	/*
	 * The LED करोes not stay on दीर्घ enough in packetized modes.
	 */
	AHD_FAINT_LED_BUG	= 0x800000
पूर्ण ahd_bug;

/*
 * Configuration specअगरic settings.
 * The driver determines these settings by probing the
 * chip/controller's configuration.
 */
प्रकार क्रमागत अणु
	AHD_FNONE	      = 0x00000,
	AHD_BOOT_CHANNEL      = 0x00001,/* We were set as the boot channel. */
	AHD_USEDEFAULTS	      = 0x00004,/*
					 * For cards without an seeprom
					 * or a BIOS to initialize the chip's
					 * SRAM, we use the शेष target
					 * settings.
					 */
	AHD_SEQUENCER_DEBUG   = 0x00008,
	AHD_RESET_BUS_A	      = 0x00010,
	AHD_EXTENDED_TRANS_A  = 0x00020,
	AHD_TERM_ENB_A	      = 0x00040,
	AHD_SPCHK_ENB_A	      = 0x00080,
	AHD_STPWLEVEL_A	      = 0x00100,
	AHD_INITIATORROLE     = 0x00200,/*
					 * Allow initiator operations on
					 * this controller.
					 */
	AHD_TARGETROLE	      = 0x00400,/*
					 * Allow target operations on this
					 * controller.
					 */
	AHD_RESOURCE_SHORTAGE = 0x00800,
	AHD_TQINFIFO_BLOCKED  = 0x01000,/* Blocked रुकोing क्रम ATIOs */
	AHD_INT50_SPEEDFLEX   = 0x02000,/*
					 * Internal 50pin connector
					 * sits behind an aic3860
					 */
	AHD_BIOS_ENABLED      = 0x04000,
	AHD_ALL_INTERRUPTS    = 0x08000,
	AHD_39BIT_ADDRESSING  = 0x10000,/* Use 39 bit addressing scheme. */
	AHD_64BIT_ADDRESSING  = 0x20000,/* Use 64 bit addressing scheme. */
	AHD_CURRENT_SENSING   = 0x40000,
	AHD_SCB_CONFIG_USED   = 0x80000,/* No SEEPROM but SCB had info. */
	AHD_HP_BOARD	      = 0x100000,
	AHD_BUS_RESET_ACTIVE  = 0x200000,
	AHD_UPDATE_PEND_CMDS  = 0x400000,
	AHD_RUNNING_QOUTFIFO  = 0x800000,
	AHD_HAD_FIRST_SEL     = 0x1000000
पूर्ण ahd_flag;

/************************* Hardware  SCB Definition ***************************/

/*
 * The driver keeps up to MAX_SCB scb काष्ठाures per card in memory.  The SCB
 * consists of a "hardware SCB" mirroring the fields available on the card
 * and additional inक्रमmation the kernel stores क्रम each transaction.
 *
 * To minimize space utilization, a portion of the hardware scb stores
 * dअगरferent data during dअगरferent portions of a SCSI transaction.
 * As initialized by the host driver क्रम the initiator role, this area
 * contains the SCSI cdb (or a poपूर्णांकer to the  cdb) to be executed.  After
 * the cdb has been presented to the target, this area serves to store
 * residual transfer inक्रमmation and the SCSI status byte.
 * For the target role, the contents of this area करो not change, but
 * still serve a dअगरferent purpose than क्रम the initiator role.  See
 * काष्ठा target_data क्रम details.
 */

/*
 * Status inक्रमmation embedded in the shared poriton of
 * an SCB after passing the cdb to the target.  The kernel
 * driver will only पढ़ो this data क्रम transactions that
 * complete abnormally.
 */
काष्ठा initiator_status अणु
	uपूर्णांक32_t residual_datacnt;	/* Residual in the current S/G seg */
	uपूर्णांक32_t residual_sgptr;	/* The next S/G क्रम this transfer */
	uपूर्णांक8_t	 scsi_status;		/* Standard SCSI status byte */
पूर्ण;

काष्ठा target_status अणु
	uपूर्णांक32_t residual_datacnt;	/* Residual in the current S/G seg */
	uपूर्णांक32_t residual_sgptr;	/* The next S/G क्रम this transfer */
	uपूर्णांक8_t  scsi_status;		/* SCSI status to give to initiator */
	uपूर्णांक8_t  target_phases;		/* Biपंचांगap of phases to execute */
	uपूर्णांक8_t  data_phase;		/* Data-In or Data-Out */
	uपूर्णांक8_t  initiator_tag;		/* Initiator's transaction tag */
पूर्ण;

/*
 * Initiator mode SCB shared data area.
 * If the embedded CDB is 12 bytes or less, we embed
 * the sense buffer address in the SCB.  This allows
 * us to retrieve sense inक्रमmation without पूर्णांकerrupting
 * the host in packetized mode.
 */
प्रकार uपूर्णांक32_t sense_addr_t;
#घोषणा MAX_CDB_LEN 16
#घोषणा MAX_CDB_LEN_WITH_SENSE_ADDR (MAX_CDB_LEN - माप(sense_addr_t))
जोड़ initiator_data अणु
	काष्ठा अणु
		uपूर्णांक64_t cdbptr;
		uपूर्णांक8_t  cdblen;
	पूर्ण cdb_from_host;
	uपूर्णांक8_t	 cdb[MAX_CDB_LEN];
	काष्ठा अणु
		uपूर्णांक8_t	 cdb[MAX_CDB_LEN_WITH_SENSE_ADDR];
		sense_addr_t sense_addr;
	पूर्ण cdb_plus_saddr;
पूर्ण;

/*
 * Target mode version of the shared data SCB segment.
 */
काष्ठा target_data अणु
	uपूर्णांक32_t spare[2];
	uपूर्णांक8_t  scsi_status;		/* SCSI status to give to initiator */
	uपूर्णांक8_t  target_phases;		/* Biपंचांगap of phases to execute */
	uपूर्णांक8_t  data_phase;		/* Data-In or Data-Out */
	uपूर्णांक8_t  initiator_tag;		/* Initiator's transaction tag */
पूर्ण;

काष्ठा hardware_scb अणु
/*0*/	जोड़ अणु
		जोड़	initiator_data idata;
		काष्ठा	target_data tdata;
		काष्ठा	initiator_status istatus;
		काष्ठा	target_status tstatus;
	पूर्ण shared_data;
/*
 * A word about residuals.
 * The scb is presented to the sequencer with the dataptr and datacnt
 * fields initialized to the contents of the first S/G element to
 * transfer.  The sgptr field is initialized to the bus address क्रम
 * the S/G element that follows the first in the in core S/G array
 * or'ed with the SG_FULL_RESID flag.  Sgptr may poपूर्णांक to an invalid
 * S/G entry क्रम this transfer (single S/G element transfer with the
 * first elements address and length preloaded in the dataptr/datacnt
 * fields).  If no transfer is to occur, sgptr is set to SG_LIST_शून्य.
 * The SG_FULL_RESID flag ensures that the residual will be correctly
 * noted even अगर no data transfers occur.  Once the data phase is entered,
 * the residual sgptr and datacnt are loaded from the sgptr and the
 * datacnt fields.  After each S/G element's dataptr and length are
 * loaded पूर्णांकo the hardware, the residual sgptr is advanced.  After
 * each S/G element is expired, its datacnt field is checked to see
 * अगर the LAST_SEG flag is set.  If so, SG_LIST_शून्य is set in the
 * residual sg ptr and the transfer is considered complete.  If the
 * sequencer determines that there is a residual in the tranfer, or
 * there is non-zero status, it will set the SG_STATUS_VALID flag in
 * sgptr and dma the scb back पूर्णांकo host memory.  To sumarize:
 *
 * Sequencer:
 *	o A residual has occurred अगर SG_FULL_RESID is set in sgptr,
 *	  or residual_sgptr करोes not have SG_LIST_शून्य set.
 *
 *	o We are transferring the last segment अगर residual_datacnt has
 *	  the SG_LAST_SEG flag set.
 *
 * Host:
 *	o A residual can only have occurred अगर a completed scb has the
 *	  SG_STATUS_VALID flag set.  Inspection of the SCSI status field,
 *	  the residual_datacnt, and the residual_sgptr field will tell
 *	  क्रम sure.
 *
 *	o residual_sgptr and sgptr refer to the "next" sg entry
 *	  and so may poपूर्णांक beyond the last valid sg entry क्रम the
 *	  transfer.
 */ 
#घोषणा SG_PTR_MASK	0xFFFFFFF8
/*16*/	uपूर्णांक16_t tag;		/* Reused by Sequencer. */
/*18*/	uपूर्णांक8_t  control;	/* See SCB_CONTROL in aic79xx.reg क्रम details */
/*19*/	uपूर्णांक8_t	 scsiid;	/*
				 * Selection out Id
				 * Our Id (bits 0-3) Their ID (bits 4-7)
				 */
/*20*/	uपूर्णांक8_t  lun;
/*21*/	uपूर्णांक8_t  task_attribute;
/*22*/	uपूर्णांक8_t  cdb_len;
/*23*/	uपूर्णांक8_t  task_management;
/*24*/	uपूर्णांक64_t dataptr;
/*32*/	uपूर्णांक32_t datacnt;	/* Byte 3 is spare. */
/*36*/	uपूर्णांक32_t sgptr;
/*40*/	uपूर्णांक32_t hscb_busaddr;
/*44*/	uपूर्णांक32_t next_hscb_busaddr;
/********** Long lun field only करोwnloaded क्रम full 8 byte lun support ********/
/*48*/  uपूर्णांक8_t	 pkt_दीर्घ_lun[8];
/******* Fields below are not Downloaded (Sequencer may use क्रम scratch) ******/
/*56*/  uपूर्णांक8_t	 spare[8];
पूर्ण;

/************************ Kernel SCB Definitions ******************************/
/*
 * Some fields of the SCB are OS dependent.  Here we collect the
 * definitions क्रम elements that all OS platक्रमms need to include
 * in there SCB definition.
 */

/*
 * Definition of a scatter/gather element as transferred to the controller.
 * The aic7xxx chips only support a 24bit length.  We use the top byte of
 * the length to store additional address bits and a flag to indicate
 * that a given segment terminates the transfer.  This gives us an
 * addressable range of 512GB on machines with 64bit PCI or with chips
 * that can support dual address cycles on 32bit PCI busses.
 */
काष्ठा ahd_dma_seg अणु
	uपूर्णांक32_t	addr;
	uपूर्णांक32_t	len;
#घोषणा	AHD_DMA_LAST_SEG	0x80000000
#घोषणा	AHD_SG_HIGH_ADDR_MASK	0x7F000000
#घोषणा	AHD_SG_LEN_MASK		0x00FFFFFF
पूर्ण;

काष्ठा ahd_dma64_seg अणु
	uपूर्णांक64_t	addr;
	uपूर्णांक32_t	len;
	uपूर्णांक32_t	pad;
पूर्ण;

काष्ठा map_node अणु
	bus_dmamap_t		 dmamap;
	dma_addr_t		 physaddr;
	uपूर्णांक8_t			*vaddr;
	SLIST_ENTRY(map_node)	 links;
पूर्ण;

/*
 * The current state of this SCB.
 */
प्रकार क्रमागत अणु
	SCB_FLAG_NONE		= 0x00000,
	SCB_TRANSMISSION_ERROR	= 0x00001,/*
					   * We detected a parity or CRC
					   * error that has effected the
					   * payload of the command.  This
					   * flag is checked when normal
					   * status is वापसed to catch
					   * the हाल of a target not
					   * responding to our attempt
					   * to report the error.
					   */
	SCB_OTHERTCL_TIMEOUT	= 0x00002,/*
					   * Another device was active
					   * during the first समयout क्रम
					   * this SCB so we gave ourselves
					   * an additional समयout period
					   * in हाल it was hogging the
					   * bus.
				           */
	SCB_DEVICE_RESET	= 0x00004,
	SCB_SENSE		= 0x00008,
	SCB_CDB32_PTR		= 0x00010,
	SCB_RECOVERY_SCB	= 0x00020,
	SCB_AUTO_NEGOTIATE	= 0x00040,/* Negotiate to achieve goal. */
	SCB_NEGOTIATE		= 0x00080,/* Negotiation क्रमced क्रम command. */
	SCB_ABORT		= 0x00100,
	SCB_ACTIVE		= 0x00200,
	SCB_TARGET_IMMEDIATE	= 0x00400,
	SCB_PACKETIZED		= 0x00800,
	SCB_EXPECT_PPR_BUSFREE	= 0x01000,
	SCB_PKT_SENSE		= 0x02000,
	SCB_EXTERNAL_RESET	= 0x04000,/* Device was reset बाह्यally */
	SCB_ON_COL_LIST		= 0x08000,
	SCB_SILENT		= 0x10000 /*
					   * Be quiet about transmission type
					   * errors.  They are expected and we
					   * करोn't want to upset the user.  This
					   * flag is typically used during DV.
					   */
पूर्ण scb_flag;

काष्ठा scb अणु
	काष्ठा	hardware_scb	 *hscb;
	जोड़ अणु
		SLIST_ENTRY(scb)  sle;
		LIST_ENTRY(scb)	  le;
		TAILQ_ENTRY(scb)  tqe;
	पूर्ण links;
	जोड़ अणु
		SLIST_ENTRY(scb)  sle;
		LIST_ENTRY(scb)	  le;
		TAILQ_ENTRY(scb)  tqe;
	पूर्ण links2;
#घोषणा pending_links links2.le
#घोषणा collision_links links2.le
	काष्ठा scb		 *col_scb;
	ahd_io_ctx_t		  io_ctx;
	काष्ठा ahd_softc	 *ahd_softc;
	scb_flag		  flags;
	काष्ठा scb_platक्रमm_data *platक्रमm_data;
	काष्ठा map_node		 *hscb_map;
	काष्ठा map_node		 *sg_map;
	काष्ठा map_node		 *sense_map;
	व्योम			 *sg_list;
	uपूर्णांक8_t			 *sense_data;
	dma_addr_t		  sg_list_busaddr;
	dma_addr_t		  sense_busaddr;
	u_पूर्णांक			  sg_count;/* How full ahd_dma_seg is */
#घोषणा	AHD_MAX_LQ_CRC_ERRORS 5
	u_पूर्णांक			  crc_retry_count;
पूर्ण;

TAILQ_HEAD(scb_tailq, scb);
BSD_LIST_HEAD(scb_list, scb);

काष्ठा scb_data अणु
	/*
	 * TAILQ of lists of मुक्त SCBs grouped by device
	 * collision करोमुख्यs.
	 */
	काष्ठा scb_tailq मुक्त_scbs;

	/*
	 * Per-device lists of SCBs whose tag ID would collide
	 * with an alपढ़ोy active tag on the device.
	 */
	काष्ठा scb_list मुक्त_scb_lists[AHD_NUM_TARGETS * AHD_NUM_LUNS_NONPKT];

	/*
	 * SCBs that will not collide with any active device.
	 */
	काष्ठा scb_list any_dev_मुक्त_scb_list;

	/*
	 * Mapping from tag to SCB.
	 */
	काष्ठा	scb *scbindex[AHD_SCB_MAX];

	/*
	 * "Bus" addresses of our data काष्ठाures.
	 */
	bus_dma_tag_t	 hscb_dmat;	/* dmat क्रम our hardware SCB array */
	bus_dma_tag_t	 sg_dmat;	/* dmat क्रम our sg segments */
	bus_dma_tag_t	 sense_dmat;	/* dmat क्रम our sense buffers */
	SLIST_HEAD(, map_node) hscb_maps;
	SLIST_HEAD(, map_node) sg_maps;
	SLIST_HEAD(, map_node) sense_maps;
	पूर्णांक		 scbs_left;	/* unallocated scbs in head map_node */
	पूर्णांक		 sgs_left;	/* unallocated sgs in head map_node */
	पूर्णांक		 sense_left;	/* unallocated sense in head map_node */
	uपूर्णांक16_t	 numscbs;
	uपूर्णांक16_t	 maxhscbs;	/* Number of SCBs on the card */
	uपूर्णांक8_t		 init_level;	/*
					 * How far we've initialized
					 * this काष्ठाure.
					 */
पूर्ण;

/************************ Target Mode Definitions *****************************/

/*
 * Connection descriptor क्रम select-in requests in target mode.
 */
काष्ठा target_cmd अणु
	uपूर्णांक8_t scsiid;		/* Our ID and the initiator's ID */
	uपूर्णांक8_t identअगरy;	/* Identअगरy message */
	uपूर्णांक8_t bytes[22];	/*
				 * Bytes contains any additional message
				 * bytes terminated by 0xFF.  The reमुख्यder
				 * is the cdb to execute.
				 */
	uपूर्णांक8_t cmd_valid;	/*
				 * When a command is complete, the firmware
				 * will set cmd_valid to all bits set.
				 * After the host has seen the command,
				 * the bits are cleared.  This allows us
				 * to just peek at host memory to determine
				 * अगर more work is complete. cmd_valid is on
				 * an 8 byte boundary to simplअगरy setting
				 * it on aic7880 hardware which only has
				 * limited direct access to the DMA FIFO.
				 */
	uपूर्णांक8_t pad[7];
पूर्ण;

/*
 * Number of events we can buffer up अगर we run out
 * of immediate notअगरy ccbs.
 */
#घोषणा AHD_TMODE_EVENT_BUFFER_SIZE 8
काष्ठा ahd_पंचांगode_event अणु
	uपूर्णांक8_t initiator_id;
	uपूर्णांक8_t event_type;	/* MSG type or EVENT_TYPE_BUS_RESET */
#घोषणा	EVENT_TYPE_BUS_RESET 0xFF
	uपूर्णांक8_t event_arg;
पूर्ण;

/*
 * Per enabled lun target mode state.
 * As this state is directly influenced by the host OS'es target mode
 * environment, we let the OS module define it.  Forward declare the
 * काष्ठाure here so we can store arrays of them, etc. in OS neutral
 * data काष्ठाures.
 */
#अगर_घोषित AHD_TARGET_MODE
काष्ठा ahd_पंचांगode_lstate अणु
	काष्ठा cam_path *path;
	काष्ठा ccb_hdr_slist accept_tios;
	काष्ठा ccb_hdr_slist immed_notअगरies;
	काष्ठा ahd_पंचांगode_event event_buffer[AHD_TMODE_EVENT_BUFFER_SIZE];
	uपूर्णांक8_t event_r_idx;
	uपूर्णांक8_t event_w_idx;
पूर्ण;
#अन्यथा
काष्ठा ahd_पंचांगode_lstate;
#पूर्ण_अगर

/******************** Transfer Negotiation Dataकाष्ठाures *********************/
#घोषणा AHD_TRANS_CUR		0x01	/* Modअगरy current neogtiation status */
#घोषणा AHD_TRANS_ACTIVE	0x03	/* Assume this target is on the bus */
#घोषणा AHD_TRANS_GOAL		0x04	/* Modअगरy negotiation goal */
#घोषणा AHD_TRANS_USER		0x08	/* Modअगरy user negotiation settings */
#घोषणा AHD_PERIOD_10MHz	0x19

#घोषणा AHD_WIDTH_UNKNOWN	0xFF
#घोषणा AHD_PERIOD_UNKNOWN	0xFF
#घोषणा AHD_OFFSET_UNKNOWN	0xFF
#घोषणा AHD_PPR_OPTS_UNKNOWN	0xFF

/*
 * Transfer Negotiation Inक्रमmation.
 */
काष्ठा ahd_transinfo अणु
	uपूर्णांक8_t protocol_version;	/* SCSI Revision level */
	uपूर्णांक8_t transport_version;	/* SPI Revision level */
	uपूर्णांक8_t width;			/* Bus width */
	uपूर्णांक8_t period;			/* Sync rate factor */
	uपूर्णांक8_t offset;			/* Sync offset */
	uपूर्णांक8_t ppr_options;		/* Parallel Protocol Request options */
पूर्ण;

/*
 * Per-initiator current, goal and user transfer negotiation inक्रमmation. */
काष्ठा ahd_initiator_tinfo अणु
	काष्ठा ahd_transinfo curr;
	काष्ठा ahd_transinfo goal;
	काष्ठा ahd_transinfo user;
पूर्ण;

/*
 * Per enabled target ID state.
 * Poपूर्णांकers to lun target state as well as sync/wide negotiation inक्रमmation
 * क्रम each initiator<->target mapping.  For the initiator role we pretend
 * that we are the target and the tarमाला_लो are the initiators since the
 * negotiation is the same regardless of role.
 */
काष्ठा ahd_पंचांगode_tstate अणु
	काष्ठा ahd_पंचांगode_lstate*	enabled_luns[AHD_NUM_LUNS];
	काष्ठा ahd_initiator_tinfo	transinfo[AHD_NUM_TARGETS];

	/*
	 * Per initiator state biपंचांगasks.
	 */
	uपूर्णांक16_t	 स्वतः_negotiate;/* Auto Negotiation Required */
	uपूर्णांक16_t	 discenable;	/* Disconnection allowed  */
	uपूर्णांक16_t	 tagenable;	/* Tagged Queuing allowed */
पूर्ण;

/*
 * Poपूर्णांकs of पूर्णांकerest aदीर्घ the negotiated transfer scale.
 */
#घोषणा AHD_SYNCRATE_160	0x8
#घोषणा AHD_SYNCRATE_PACED	0x8
#घोषणा AHD_SYNCRATE_DT		0x9
#घोषणा AHD_SYNCRATE_ULTRA2	0xa
#घोषणा AHD_SYNCRATE_ULTRA	0xc
#घोषणा AHD_SYNCRATE_FAST	0x19
#घोषणा AHD_SYNCRATE_MIN_DT	AHD_SYNCRATE_FAST
#घोषणा AHD_SYNCRATE_SYNC	0x32
#घोषणा AHD_SYNCRATE_MIN	0x60
#घोषणा	AHD_SYNCRATE_ASYNC	0xFF
#घोषणा AHD_SYNCRATE_MAX	AHD_SYNCRATE_160

/* Safe and valid period क्रम async negotiations. */
#घोषणा	AHD_ASYNC_XFER_PERIOD	0x44

/*
 * In RevA, the synctable uses a 120MHz rate क्रम the period
 * factor 8 and 160MHz क्रम the period factor 7.  The 120MHz
 * rate never made it पूर्णांकo the official SCSI spec, so we must
 * compensate when setting the negotiation table क्रम Rev A
 * parts.
 */
#घोषणा AHD_SYNCRATE_REVA_120	0x8
#घोषणा AHD_SYNCRATE_REVA_160	0x7

/***************************** Lookup Tables **********************************/
/*
 * Phase -> name and message out response
 * to parity errors in each phase table.
 */
काष्ठा ahd_phase_table_entry अणु
	uपूर्णांक8_t phase;
	uपूर्णांक8_t mesg_out; /* Message response to parity errors */
	स्थिर अक्षर *phasemsg;
पूर्ण;

/************************** Serial EEPROM Format ******************************/

काष्ठा seeprom_config अणु
/*
 * Per SCSI ID Configuration Flags
 */
	uपूर्णांक16_t device_flags[16];	/* words 0-15 */
#घोषणा		CFXFER		0x003F	/* synchronous transfer rate */
#घोषणा			CFXFER_ASYNC	0x3F
#घोषणा		CFQAS		0x0040	/* Negotiate QAS */
#घोषणा		CFPACKETIZED	0x0080	/* Negotiate Packetized Transfers */
#घोषणा		CFSTART		0x0100	/* send start unit SCSI command */
#घोषणा		CFINCBIOS	0x0200	/* include in BIOS scan */
#घोषणा		CFDISC		0x0400	/* enable disconnection */
#घोषणा		CFMULTILUNDEV	0x0800	/* Probe multiple luns in BIOS scan */
#घोषणा		CFWIDEB		0x1000	/* wide bus device */
#घोषणा		CFHOSTMANAGED	0x8000	/* Managed by a RAID controller */

/*
 * BIOS Control Bits
 */
	uपूर्णांक16_t bios_control;		/* word 16 */
#घोषणा		CFSUPREM	0x0001	/* support all हटाओable drives */
#घोषणा		CFSUPREMB	0x0002	/* support हटाओable boot drives */
#घोषणा		CFBIOSSTATE	0x000C	/* BIOS Action State */
#घोषणा		    CFBS_DISABLED	0x00
#घोषणा		    CFBS_ENABLED	0x04
#घोषणा		    CFBS_DISABLED_SCAN	0x08
#घोषणा		CFENABLEDV	0x0010	/* Perक्रमm Doमुख्य Validation */
#घोषणा		CFCTRL_A	0x0020	/* BIOS displays Ctrl-A message */
#घोषणा		CFSPARITY	0x0040	/* SCSI parity */
#घोषणा		CFEXTEND	0x0080	/* extended translation enabled */
#घोषणा		CFBOOTCD	0x0100  /* Support Bootable CD-ROM */
#घोषणा		CFMSG_LEVEL	0x0600	/* BIOS Message Level */
#घोषणा			CFMSG_VERBOSE	0x0000
#घोषणा			CFMSG_SILENT	0x0200
#घोषणा			CFMSG_DIAG	0x0400
#घोषणा		CFRESETB	0x0800	/* reset SCSI bus at boot */
/*		UNUSED		0xf000	*/

/*
 * Host Adapter Control Bits
 */
	uपूर्णांक16_t adapter_control;	/* word 17 */
#घोषणा		CFAUTOTERM	0x0001	/* Perक्रमm Auto termination */
#घोषणा		CFSTERM		0x0002	/* SCSI low byte termination */
#घोषणा		CFWSTERM	0x0004	/* SCSI high byte termination */
#घोषणा		CFSEAUTOTERM	0x0008	/* Ultra2 Perक्रमm secondary Auto Term*/
#घोषणा		CFSELOWTERM	0x0010	/* Ultra2 secondary low term */
#घोषणा		CFSEHIGHTERM	0x0020	/* Ultra2 secondary high term */
#घोषणा		CFSTPWLEVEL	0x0040	/* Termination level control */
#घोषणा		CFBIOSAUTOTERM	0x0080	/* Perक्रमm Auto termination */
#घोषणा		CFTERM_MENU	0x0100	/* BIOS displays termination menu */
#घोषणा		CFCLUSTERENB	0x8000	/* Cluster Enable */

/*
 * Bus Release Time, Host Adapter ID
 */
	uपूर्णांक16_t brसमय_id;		/* word 18 */
#घोषणा		CFSCSIID	0x000f	/* host adapter SCSI ID */
/*		UNUSED		0x00f0	*/
#घोषणा		CFBRTIME	0xff00	/* bus release समय/PCI Latency Time */

/*
 * Maximum tarमाला_लो
 */
	uपूर्णांक16_t max_tarमाला_लो;		/* word 19 */
#घोषणा		CFMAXTARG	0x00ff	/* maximum tarमाला_लो */
#घोषणा		CFBOOTLUN	0x0f00	/* Lun to boot from */
#घोषणा		CFBOOTID	0xf000	/* Target to boot from */
	uपूर्णांक16_t res_1[10];		/* words 20-29 */
	uपूर्णांक16_t signature;		/* BIOS Signature */
#घोषणा		CFSIGNATURE	0x400
	uपूर्णांक16_t checksum;		/* word 31 */
पूर्ण;

/*
 * Vital Product Data used during POST and by the BIOS.
 */
काष्ठा vpd_config अणु
	uपूर्णांक8_t  bios_flags;
#घोषणा		VPDMASTERBIOS	0x0001
#घोषणा		VPDBOOTHOST	0x0002
	uपूर्णांक8_t  reserved_1[21];
	uपूर्णांक8_t  resource_type;
	uपूर्णांक8_t  resource_len[2];
	uपूर्णांक8_t  resource_data[8];
	uपूर्णांक8_t  vpd_tag;
	uपूर्णांक16_t vpd_len;
	uपूर्णांक8_t  vpd_keyword[2];
	uपूर्णांक8_t  length;
	uपूर्णांक8_t  revision;
	uपूर्णांक8_t  device_flags;
	uपूर्णांक8_t  termination_menus[2];
	uपूर्णांक8_t  fअगरo_threshold;
	uपूर्णांक8_t  end_tag;
	uपूर्णांक8_t  vpd_checksum;
	uपूर्णांक16_t शेष_target_flags;
	uपूर्णांक16_t शेष_bios_flags;
	uपूर्णांक16_t शेष_ctrl_flags;
	uपूर्णांक8_t  शेष_irq;
	uपूर्णांक8_t  pci_latसमय;
	uपूर्णांक8_t  max_target;
	uपूर्णांक8_t  boot_lun;
	uपूर्णांक16_t signature;
	uपूर्णांक8_t  reserved_2;
	uपूर्णांक8_t  checksum;
	uपूर्णांक8_t	 reserved_3[4];
पूर्ण;

/****************************** Flexport Logic ********************************/
#घोषणा FLXADDR_TERMCTL			0x0
#घोषणा		FLX_TERMCTL_ENSECHIGH	0x8
#घोषणा		FLX_TERMCTL_ENSECLOW	0x4
#घोषणा		FLX_TERMCTL_ENPRIHIGH	0x2
#घोषणा		FLX_TERMCTL_ENPRILOW	0x1
#घोषणा FLXADDR_ROMSTAT_CURSENSECTL	0x1
#घोषणा		FLX_ROMSTAT_SEECFG	0xF0
#घोषणा		FLX_ROMSTAT_EECFG	0x0F
#घोषणा		FLX_ROMSTAT_SEE_93C66	0x00
#घोषणा		FLX_ROMSTAT_SEE_NONE	0xF0
#घोषणा		FLX_ROMSTAT_EE_512x8	0x0
#घोषणा		FLX_ROMSTAT_EE_1MBx8	0x1
#घोषणा		FLX_ROMSTAT_EE_2MBx8	0x2
#घोषणा		FLX_ROMSTAT_EE_4MBx8	0x3
#घोषणा		FLX_ROMSTAT_EE_16MBx8	0x4
#घोषणा			CURSENSE_ENB	0x1
#घोषणा	FLXADDR_FLEXSTAT		0x2
#घोषणा		FLX_FSTAT_BUSY		0x1
#घोषणा FLXADDR_CURRENT_STAT		0x4
#घोषणा		FLX_CSTAT_SEC_HIGH	0xC0
#घोषणा		FLX_CSTAT_SEC_LOW	0x30
#घोषणा		FLX_CSTAT_PRI_HIGH	0x0C
#घोषणा		FLX_CSTAT_PRI_LOW	0x03
#घोषणा		FLX_CSTAT_MASK		0x03
#घोषणा		FLX_CSTAT_SHIFT		2
#घोषणा		FLX_CSTAT_OKAY		0x0
#घोषणा		FLX_CSTAT_OVER		0x1
#घोषणा		FLX_CSTAT_UNDER		0x2
#घोषणा		FLX_CSTAT_INVALID	0x3

पूर्णांक		ahd_पढ़ो_seeprom(काष्ठा ahd_softc *ahd, uपूर्णांक16_t *buf,
				 u_पूर्णांक start_addr, u_पूर्णांक count, पूर्णांक bstream);

पूर्णांक		ahd_ग_लिखो_seeprom(काष्ठा ahd_softc *ahd, uपूर्णांक16_t *buf,
				  u_पूर्णांक start_addr, u_पूर्णांक count);
पूर्णांक		ahd_verअगरy_cksum(काष्ठा seeprom_config *sc);
पूर्णांक		ahd_acquire_seeprom(काष्ठा ahd_softc *ahd);
व्योम		ahd_release_seeprom(काष्ठा ahd_softc *ahd);

/****************************  Message Buffer *********************************/
प्रकार क्रमागत अणु
	MSG_FLAG_NONE			= 0x00,
	MSG_FLAG_EXPECT_PPR_BUSFREE	= 0x01,
	MSG_FLAG_IU_REQ_CHANGED		= 0x02,
	MSG_FLAG_EXPECT_IDE_BUSFREE	= 0x04,
	MSG_FLAG_EXPECT_QASREJ_BUSFREE	= 0x08,
	MSG_FLAG_PACKETIZED		= 0x10
पूर्ण ahd_msg_flags;

प्रकार क्रमागत अणु
	MSG_TYPE_NONE			= 0x00,
	MSG_TYPE_INITIATOR_MSGOUT	= 0x01,
	MSG_TYPE_INITIATOR_MSGIN	= 0x02,
	MSG_TYPE_TARGET_MSGOUT		= 0x03,
	MSG_TYPE_TARGET_MSGIN		= 0x04
पूर्ण ahd_msg_type;

प्रकार क्रमागत अणु
	MSGLOOP_IN_PROG,
	MSGLOOP_MSGCOMPLETE,
	MSGLOOP_TERMINATED
पूर्ण msg_loop_stat;

/*********************** Software Configuration Structure *********************/
काष्ठा ahd_suspend_channel_state अणु
	uपूर्णांक8_t	scsiseq;
	uपूर्णांक8_t	sxfrctl0;
	uपूर्णांक8_t	sxfrctl1;
	uपूर्णांक8_t	simode0;
	uपूर्णांक8_t	simode1;
	uपूर्णांक8_t	selसमयr;
	uपूर्णांक8_t	seqctl;
पूर्ण;

काष्ठा ahd_suspend_pci_state अणु
	uपूर्णांक32_t  devconfig;
	uपूर्णांक8_t   command;
	uपूर्णांक8_t   csize_latसमय;
पूर्ण;

काष्ठा ahd_suspend_state अणु
	काष्ठा	ahd_suspend_channel_state channel[2];
	काष्ठा  ahd_suspend_pci_state pci_state;
	uपूर्णांक8_t	optionmode;
	uपूर्णांक8_t	dscommand0;
	uपूर्णांक8_t	dspcistatus;
	/* hsmailbox */
	uपूर्णांक8_t	crccontrol1;
	uपूर्णांक8_t	scbbaddr;
	/* Host and sequencer SCB counts */
	uपूर्णांक8_t	dff_thrsh;
	uपूर्णांक8_t	*scratch_ram;
	uपूर्णांक8_t	*btt;
पूर्ण;

प्रकार व्योम (*ahd_bus_पूर्णांकr_t)(काष्ठा ahd_softc *);

प्रकार क्रमागत अणु
	AHD_MODE_DFF0,
	AHD_MODE_DFF1,
	AHD_MODE_CCHAN,
	AHD_MODE_SCSI,
	AHD_MODE_CFG,
	AHD_MODE_UNKNOWN
पूर्ण ahd_mode;

#घोषणा AHD_MK_MSK(x) (0x01 << (x))
#घोषणा AHD_MODE_DFF0_MSK	AHD_MK_MSK(AHD_MODE_DFF0)
#घोषणा AHD_MODE_DFF1_MSK	AHD_MK_MSK(AHD_MODE_DFF1)
#घोषणा AHD_MODE_CCHAN_MSK	AHD_MK_MSK(AHD_MODE_CCHAN)
#घोषणा AHD_MODE_SCSI_MSK	AHD_MK_MSK(AHD_MODE_SCSI)
#घोषणा AHD_MODE_CFG_MSK	AHD_MK_MSK(AHD_MODE_CFG)
#घोषणा AHD_MODE_UNKNOWN_MSK	AHD_MK_MSK(AHD_MODE_UNKNOWN)
#घोषणा AHD_MODE_ANY_MSK (~0)

प्रकार uपूर्णांक8_t ahd_mode_state;

काष्ठा ahd_completion
अणु
	uपूर्णांक16_t	tag;
	uपूर्णांक8_t		sg_status;
	uपूर्णांक8_t		valid_tag;
पूर्ण;

काष्ठा ahd_softc अणु
	bus_space_tag_t		  tags[2];
	bus_space_handle_t	  bshs[2];
	काष्ठा scb_data		  scb_data;

	काष्ठा hardware_scb	 *next_queued_hscb;
	काष्ठा map_node		 *next_queued_hscb_map;

	/*
	 * SCBs that have been sent to the controller
	 */
	BSD_LIST_HEAD(, scb)	  pending_scbs;

	/*
	 * Current रेजिस्टर winकरोw mode inक्रमmation.
	 */
	ahd_mode		  dst_mode;
	ahd_mode		  src_mode;

	/*
	 * Saved रेजिस्टर winकरोw mode inक्रमmation
	 * used क्रम restore on next unछोड़ो.
	 */
	ahd_mode		  saved_dst_mode;
	ahd_mode		  saved_src_mode;

	/*
	 * Platक्रमm specअगरic data.
	 */
	काष्ठा ahd_platक्रमm_data *platक्रमm_data;

	/*
	 * Platक्रमm specअगरic device inक्रमmation.
	 */
	ahd_dev_softc_t		  dev_softc;

	/*
	 * Bus specअगरic device inक्रमmation.
	 */
	ahd_bus_पूर्णांकr_t		  bus_पूर्णांकr;

	/*
	 * Target mode related state kept on a per enabled lun basis.
	 * Tarमाला_लो that are not enabled will have null entries.
	 * As an initiator, we keep one target entry क्रम our initiator
	 * ID to store our sync/wide transfer settings.
	 */
	काष्ठा ahd_पंचांगode_tstate  *enabled_tarमाला_लो[AHD_NUM_TARGETS];

	/*
	 * The black hole device responsible क्रम handling requests क्रम
	 * disabled luns on enabled tarमाला_लो.
	 */
	काष्ठा ahd_पंचांगode_lstate  *black_hole;

	/*
	 * Device instance currently on the bus aरुकोing a जारी TIO
	 * क्रम a command that was not given the disconnect priveledge.
	 */
	काष्ठा ahd_पंचांगode_lstate  *pending_device;

	/*
	 * Timer handles क्रम समयr driven callbacks.
	 */
	काष्ठा समयr_list	stat_समयr;

	/*
	 * Statistics.
	 */
#घोषणा	AHD_STAT_UPDATE_US	250000 /* 250ms */
#घोषणा	AHD_STAT_BUCKETS	4
	u_पूर्णांक			  cmdcmplt_bucket;
	uपूर्णांक32_t		  cmdcmplt_counts[AHD_STAT_BUCKETS];
	uपूर्णांक32_t		  cmdcmplt_total;

	/*
	 * Card अक्षरacteristics
	 */
	ahd_chip		  chip;
	ahd_feature		  features;
	ahd_bug			  bugs;
	ahd_flag		  flags;
	काष्ठा seeprom_config	 *seep_config;

	/* Command Queues */
	काष्ठा ahd_completion	  *qoutfअगरo;
	uपूर्णांक16_t		  qoutfअगरonext;
	uपूर्णांक16_t		  qoutfअगरonext_valid_tag;
	uपूर्णांक16_t		  qinfअगरonext;
	uपूर्णांक16_t		  qinfअगरo[AHD_SCB_MAX];

	/*
	 * Our qमुक्तze count.  The sequencer compares
	 * this value with its own counter to determine
	 * whether to allow selections to occur.
	 */
	uपूर्णांक16_t		  qमुक्तze_cnt;

	/* Values to store in the SEQCTL रेजिस्टर क्रम छोड़ो and unछोड़ो */
	uपूर्णांक8_t			  unछोड़ो;
	uपूर्णांक8_t			  छोड़ो;

	/* Critical Section Data */
	काष्ठा cs		 *critical_sections;
	u_पूर्णांक			  num_critical_sections;

	/* Buffer क्रम handling packetized bitbucket. */
	uपूर्णांक8_t			 *overrun_buf;

	/* Links क्रम chaining softcs */
	TAILQ_ENTRY(ahd_softc)	  links;

	/* Channel Names ('A', 'B', etc.) */
	अक्षर			  channel;

	/* Initiator Bus ID */
	uपूर्णांक8_t			  our_id;

	/*
	 * Target incoming command FIFO.
	 */
	काष्ठा target_cmd	 *tarअ_लोmds;
	uपूर्णांक8_t			  tqinfअगरonext;

	/*
	 * Cached version of the hs_mailbox so we can aव्योम
	 * pausing the sequencer during mailbox updates.
	 */
	uपूर्णांक8_t			  hs_mailbox;

	/*
	 * Incoming and outgoing message handling.
	 */
	uपूर्णांक8_t			  send_msg_लिखो_त्रुटि;
	ahd_msg_flags		  msg_flags;
	ahd_msg_type		  msg_type;
	uपूर्णांक8_t			  msgout_buf[12];/* Message we are sending */
	uपूर्णांक8_t			  msgin_buf[12];/* Message we are receiving */
	u_पूर्णांक			  msgout_len;	/* Length of message to send */
	u_पूर्णांक			  msgout_index;	/* Current index in msgout */
	u_पूर्णांक			  msgin_index;	/* Current index in msgin */

	/*
	 * Mapping inक्रमmation क्रम data काष्ठाures shared
	 * between the sequencer and kernel.
	 */
	bus_dma_tag_t		  parent_dmat;
	bus_dma_tag_t		  shared_data_dmat;
	काष्ठा map_node		  shared_data_map;

	/* Inक्रमmation saved through suspend/resume cycles */
	काष्ठा ahd_suspend_state  suspend_state;

	/* Number of enabled target mode device on this card */
	u_पूर्णांक			  enabled_luns;

	/* Initialization level of this data काष्ठाure */
	u_पूर्णांक			  init_level;

	/* PCI cacheline size. */
	u_पूर्णांक			  pci_cachesize;

	/* IO Cell Parameters */
	uपूर्णांक8_t			  iocell_opts[AHD_NUM_PER_DEV_ANNEXCOLS];

	u_पूर्णांक			  stack_size;
	uपूर्णांक16_t		 *saved_stack;

	/* Per-Unit descriptive inक्रमmation */
	स्थिर अक्षर		 *description;
	स्थिर अक्षर		 *bus_description;
	अक्षर			 *name;
	पूर्णांक			  unit;

	/* Selection Timer settings */
	पूर्णांक			  selसमय;

	/*
	 * Interrupt coalescing settings.
	 */
#घोषणा	AHD_INT_COALESCING_TIMER_DEFAULT		250 /*us*/
#घोषणा	AHD_INT_COALESCING_MAXCMDS_DEFAULT		10
#घोषणा	AHD_INT_COALESCING_MAXCMDS_MAX			127
#घोषणा	AHD_INT_COALESCING_MINCMDS_DEFAULT		5
#घोषणा	AHD_INT_COALESCING_MINCMDS_MAX			127
#घोषणा	AHD_INT_COALESCING_THRESHOLD_DEFAULT		2000
#घोषणा	AHD_INT_COALESCING_STOP_THRESHOLD_DEFAULT	1000
	u_पूर्णांक			  पूर्णांक_coalescing_समयr;
	u_पूर्णांक			  पूर्णांक_coalescing_maxcmds;
	u_पूर्णांक			  पूर्णांक_coalescing_mincmds;
	u_पूर्णांक			  पूर्णांक_coalescing_threshold;
	u_पूर्णांक			  पूर्णांक_coalescing_stop_threshold;

	uपूर्णांक16_t		  user_discenable;/* Disconnection allowed  */
	uपूर्णांक16_t		  user_tagenable;/* Tagged Queuing allowed */
पूर्ण;

/*************************** IO Cell Configuration ****************************/
#घोषणा	AHD_PRECOMP_SLEW_INDEX						\
    (AHD_ANNEXCOL_PRECOMP_SLEW - AHD_ANNEXCOL_PER_DEV0)

#घोषणा	AHD_AMPLITUDE_INDEX						\
    (AHD_ANNEXCOL_AMPLITUDE - AHD_ANNEXCOL_PER_DEV0)

#घोषणा AHD_SET_SLEWRATE(ahd, new_slew)					\
करो अणु									\
    (ahd)->iocell_opts[AHD_PRECOMP_SLEW_INDEX] &= ~AHD_SLEWRATE_MASK;	\
    (ahd)->iocell_opts[AHD_PRECOMP_SLEW_INDEX] |=			\
	(((new_slew) << AHD_SLEWRATE_SHIFT) & AHD_SLEWRATE_MASK);	\
पूर्ण जबतक (0)

#घोषणा AHD_SET_PRECOMP(ahd, new_pcomp)					\
करो अणु									\
    (ahd)->iocell_opts[AHD_PRECOMP_SLEW_INDEX] &= ~AHD_PRECOMP_MASK;	\
    (ahd)->iocell_opts[AHD_PRECOMP_SLEW_INDEX] |=			\
	(((new_pcomp) << AHD_PRECOMP_SHIFT) & AHD_PRECOMP_MASK);	\
पूर्ण जबतक (0)

#घोषणा AHD_SET_AMPLITUDE(ahd, new_amp)					\
करो अणु									\
    (ahd)->iocell_opts[AHD_AMPLITUDE_INDEX] &= ~AHD_AMPLITUDE_MASK;	\
    (ahd)->iocell_opts[AHD_AMPLITUDE_INDEX] |=				\
	(((new_amp) << AHD_AMPLITUDE_SHIFT) & AHD_AMPLITUDE_MASK);	\
पूर्ण जबतक (0)

/************************ Active Device Inक्रमmation ***************************/
प्रकार क्रमागत अणु
	ROLE_UNKNOWN,
	ROLE_INITIATOR,
	ROLE_TARGET
पूर्ण role_t;

काष्ठा ahd_devinfo अणु
	पूर्णांक	 our_scsiid;
	पूर्णांक	 target_offset;
	uपूर्णांक16_t target_mask;
	u_पूर्णांक	 target;
	u_पूर्णांक	 lun;
	अक्षर	 channel;
	role_t	 role;		/*
				 * Only guaranteed to be correct अगर not
				 * in the busमुक्त state.
				 */
पूर्ण;

/****************************** PCI Structures ********************************/
#घोषणा AHD_PCI_IOADDR0	PCIR_BAR(0)	/* I/O BAR*/
#घोषणा AHD_PCI_MEMADDR	PCIR_BAR(1)	/* Memory BAR */
#घोषणा AHD_PCI_IOADDR1	PCIR_BAR(3)	/* Second I/O BAR */

प्रकार पूर्णांक (ahd_device_setup_t)(काष्ठा ahd_softc *);

काष्ठा ahd_pci_identity अणु
	uपूर्णांक64_t		 full_id;
	uपूर्णांक64_t		 id_mask;
	स्थिर अक्षर		*name;
	ahd_device_setup_t	*setup;
पूर्ण;

/***************************** VL/EISA Declarations ***************************/
काष्ठा aic7770_identity अणु
	uपूर्णांक32_t		 full_id;
	uपूर्णांक32_t		 id_mask;
	स्थिर अक्षर		*name;
	ahd_device_setup_t	*setup;
पूर्ण;
बाह्य काष्ठा aic7770_identity aic7770_ident_table [];
बाह्य स्थिर पूर्णांक ahd_num_aic7770_devs;

#घोषणा AHD_EISA_SLOT_OFFSET	0xc00
#घोषणा AHD_EISA_IOSIZE		0x100

/*************************** Function Declarations ****************************/
/******************************************************************************/

/***************************** PCI Front End *********************************/
स्थिर काष्ठा	ahd_pci_identity *ahd_find_pci_device(ahd_dev_softc_t);
पूर्णांक			  ahd_pci_config(काष्ठा ahd_softc *,
					 स्थिर काष्ठा ahd_pci_identity *);
पूर्णांक	ahd_pci_test_रेजिस्टर_access(काष्ठा ahd_softc *);
व्योम __maybe_unused	ahd_pci_suspend(काष्ठा ahd_softc *);
व्योम __maybe_unused	ahd_pci_resume(काष्ठा ahd_softc *);

/************************** SCB and SCB queue management **********************/
व्योम		ahd_qinfअगरo_requeue_tail(काष्ठा ahd_softc *ahd,
					 काष्ठा scb *scb);

/****************************** Initialization ********************************/
काष्ठा ahd_softc	*ahd_alloc(व्योम *platक्रमm_arg, अक्षर *name);
पूर्णांक			 ahd_softc_init(काष्ठा ahd_softc *);
व्योम			 ahd_controller_info(काष्ठा ahd_softc *ahd, अक्षर *buf);
पूर्णांक			 ahd_init(काष्ठा ahd_softc *ahd);
पूर्णांक __maybe_unused	 ahd_suspend(काष्ठा ahd_softc *ahd);
व्योम __maybe_unused	 ahd_resume(काष्ठा ahd_softc *ahd);
पूर्णांक			 ahd_शेष_config(काष्ठा ahd_softc *ahd);
पूर्णांक			 ahd_parse_vpddata(काष्ठा ahd_softc *ahd,
					   काष्ठा vpd_config *vpd);
पूर्णांक			 ahd_parse_cfgdata(काष्ठा ahd_softc *ahd,
					   काष्ठा seeprom_config *sc);
व्योम			 ahd_पूर्णांकr_enable(काष्ठा ahd_softc *ahd, पूर्णांक enable);
व्योम			 ahd_छोड़ो_and_flushwork(काष्ठा ahd_softc *ahd);
व्योम			 ahd_set_unit(काष्ठा ahd_softc *, पूर्णांक);
व्योम			 ahd_set_name(काष्ठा ahd_softc *, अक्षर *);
काष्ठा scb		*ahd_get_scb(काष्ठा ahd_softc *ahd, u_पूर्णांक col_idx);
व्योम			 ahd_मुक्त_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb);
व्योम			 ahd_मुक्त(काष्ठा ahd_softc *ahd);
पूर्णांक			 ahd_reset(काष्ठा ahd_softc *ahd, पूर्णांक reinit);
पूर्णांक			 ahd_ग_लिखो_flexport(काष्ठा ahd_softc *ahd,
					    u_पूर्णांक addr, u_पूर्णांक value);
पूर्णांक			 ahd_पढ़ो_flexport(काष्ठा ahd_softc *ahd, u_पूर्णांक addr,
					   uपूर्णांक8_t *value);

/***************************** Error Recovery *********************************/
प्रकार क्रमागत अणु
	SEARCH_COMPLETE,
	SEARCH_COUNT,
	SEARCH_REMOVE,
	SEARCH_PRINT
पूर्ण ahd_search_action;
पूर्णांक			ahd_search_qinfअगरo(काष्ठा ahd_softc *ahd, पूर्णांक target,
					   अक्षर channel, पूर्णांक lun, u_पूर्णांक tag,
					   role_t role, uपूर्णांक32_t status,
					   ahd_search_action action);
पूर्णांक			ahd_search_disc_list(काष्ठा ahd_softc *ahd, पूर्णांक target,
					     अक्षर channel, पूर्णांक lun, u_पूर्णांक tag,
					     पूर्णांक stop_on_first, पूर्णांक हटाओ,
					     पूर्णांक save_state);
पूर्णांक			ahd_reset_channel(काष्ठा ahd_softc *ahd, अक्षर channel,
					  पूर्णांक initiate_reset);
/*************************** Utility Functions ********************************/
व्योम			ahd_compile_devinfo(काष्ठा ahd_devinfo *devinfo,
					    u_पूर्णांक our_id, u_पूर्णांक target,
					    u_पूर्णांक lun, अक्षर channel,
					    role_t role);
/************************** Transfer Negotiation ******************************/
व्योम			ahd_find_syncrate(काष्ठा ahd_softc *ahd, u_पूर्णांक *period,
					  u_पूर्णांक *ppr_options, u_पूर्णांक maxsync);
/*
 * Negotiation types.  These are used to qualअगरy अगर we should renegotiate
 * even अगर our goal and current transport parameters are identical.
 */
प्रकार क्रमागत अणु
	AHD_NEG_TO_GOAL,	/* Renegotiate only अगर goal and curr dअगरfer. */
	AHD_NEG_IF_NON_ASYNC,	/* Renegotiate so दीर्घ as goal is non-async. */
	AHD_NEG_ALWAYS		/* Renegotiat even अगर goal is async. */
पूर्ण ahd_neg_type;
पूर्णांक			ahd_update_neg_request(काष्ठा ahd_softc*,
					       काष्ठा ahd_devinfo*,
					       काष्ठा ahd_पंचांगode_tstate*,
					       काष्ठा ahd_initiator_tinfo*,
					       ahd_neg_type);
व्योम			ahd_set_width(काष्ठा ahd_softc *ahd,
				      काष्ठा ahd_devinfo *devinfo,
				      u_पूर्णांक width, u_पूर्णांक type, पूर्णांक छोड़ोd);
व्योम			ahd_set_syncrate(काष्ठा ahd_softc *ahd,
					 काष्ठा ahd_devinfo *devinfo,
					 u_पूर्णांक period, u_पूर्णांक offset,
					 u_पूर्णांक ppr_options,
					 u_पूर्णांक type, पूर्णांक छोड़ोd);
प्रकार क्रमागत अणु
	AHD_QUEUE_NONE,
	AHD_QUEUE_BASIC,
	AHD_QUEUE_TAGGED
पूर्ण ahd_queue_alg;

/**************************** Target Mode *************************************/
#अगर_घोषित AHD_TARGET_MODE
व्योम		ahd_send_lstate_events(काष्ठा ahd_softc *,
				       काष्ठा ahd_पंचांगode_lstate *);
व्योम		ahd_handle_en_lun(काष्ठा ahd_softc *ahd,
				  काष्ठा cam_sim *sim, जोड़ ccb *ccb);
cam_status	ahd_find_पंचांगode_devs(काष्ठा ahd_softc *ahd,
				    काष्ठा cam_sim *sim, जोड़ ccb *ccb,
				    काष्ठा ahd_पंचांगode_tstate **tstate,
				    काष्ठा ahd_पंचांगode_lstate **lstate,
				    पूर्णांक notfound_failure);
#अगर_अघोषित AHD_TMODE_ENABLE
#घोषणा AHD_TMODE_ENABLE 0
#पूर्ण_अगर
#पूर्ण_अगर
/******************************* Debug ***************************************/
#अगर_घोषित AHD_DEBUG
बाह्य uपूर्णांक32_t ahd_debug;
#घोषणा AHD_SHOW_MISC		0x00001
#घोषणा AHD_SHOW_SENSE		0x00002
#घोषणा AHD_SHOW_RECOVERY	0x00004
#घोषणा AHD_DUMP_SEEPROM	0x00008
#घोषणा AHD_SHOW_TERMCTL	0x00010
#घोषणा AHD_SHOW_MEMORY		0x00020
#घोषणा AHD_SHOW_MESSAGES	0x00040
#घोषणा AHD_SHOW_MODEPTR	0x00080
#घोषणा AHD_SHOW_SELTO		0x00100
#घोषणा AHD_SHOW_FIFOS		0x00200
#घोषणा AHD_SHOW_QFULL		0x00400
#घोषणा	AHD_SHOW_DV		0x00800
#घोषणा AHD_SHOW_MASKED_ERRORS	0x01000
#घोषणा AHD_SHOW_QUEUE		0x02000
#घोषणा AHD_SHOW_TQIN		0x04000
#घोषणा AHD_SHOW_SG		0x08000
#घोषणा AHD_SHOW_INT_COALESCING	0x10000
#घोषणा AHD_DEBUG_SEQUENCER	0x20000
#पूर्ण_अगर
व्योम			ahd_prपूर्णांक_devinfo(काष्ठा ahd_softc *ahd,
					  काष्ठा ahd_devinfo *devinfo);
व्योम			ahd_dump_card_state(काष्ठा ahd_softc *ahd);
पूर्णांक			ahd_prपूर्णांक_रेजिस्टर(स्थिर ahd_reg_parse_entry_t *table,
					   u_पूर्णांक num_entries,
					   स्थिर अक्षर *name,
					   u_पूर्णांक address,
					   u_पूर्णांक value,
					   u_पूर्णांक *cur_column,
					   u_पूर्णांक wrap_poपूर्णांक);
#पूर्ण_अगर /* _AIC79XX_H_ */
