<शैली गुरु>
/*
 * Core definitions and data काष्ठाures shareable across OS platक्रमms.
 *
 * Copyright (c) 1994-2001 Justin T. Gibbs.
 * Copyright (c) 2000-2001 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx.h#85 $
 *
 * $FreeBSD$
 */

#अगर_अघोषित _AIC7XXX_H_
#घोषणा _AIC7XXX_H_

/* Register Definitions */
#समावेश "aic7xxx_reg.h"

/************************* Forward Declarations *******************************/
काष्ठा ahc_platक्रमm_data;
काष्ठा scb_platक्रमm_data;
काष्ठा seeprom_descriptor;

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

#घोषणा SCSIID_TARGET(ahc, scsiid) \
	(((scsiid) & ((((ahc)->features & AHC_TWIN) != 0) ? TWIN_TID : TID)) \
	>> TID_SHIFT)
#घोषणा SCSIID_OUR_ID(scsiid) \
	((scsiid) & OID)
#घोषणा SCSIID_CHANNEL(ahc, scsiid) \
	((((ahc)->features & AHC_TWIN) != 0) \
        ? ((((scsiid) & TWIN_CHNLB) != 0) ? 'B' : 'A') \
       : 'A')
#घोषणा	SCB_IS_SCSIBUS_B(ahc, scb) \
	(SCSIID_CHANNEL(ahc, (scb)->hscb->scsiid) == 'B')
#घोषणा	SCB_GET_OUR_ID(scb) \
	SCSIID_OUR_ID((scb)->hscb->scsiid)
#घोषणा	SCB_GET_TARGET(ahc, scb) \
	SCSIID_TARGET((ahc), (scb)->hscb->scsiid)
#घोषणा	SCB_GET_CHANNEL(ahc, scb) \
	SCSIID_CHANNEL(ahc, (scb)->hscb->scsiid)
#घोषणा	SCB_GET_LUN(scb) \
	((scb)->hscb->lun & LID)
#घोषणा SCB_GET_TARGET_OFFSET(ahc, scb)	\
	(SCB_GET_TARGET(ahc, scb) + (SCB_IS_SCSIBUS_B(ahc, scb) ? 8 : 0))
#घोषणा SCB_GET_TARGET_MASK(ahc, scb) \
	(0x01 << (SCB_GET_TARGET_OFFSET(ahc, scb)))
#अगर_घोषित AHC_DEBUG
#घोषणा SCB_IS_SILENT(scb)					\
	((ahc_debug & AHC_SHOW_MASKED_ERRORS) == 0		\
      && (((scb)->flags & SCB_SILENT) != 0))
#अन्यथा
#घोषणा SCB_IS_SILENT(scb)					\
	(((scb)->flags & SCB_SILENT) != 0)
#पूर्ण_अगर
#घोषणा TCL_TARGET_OFFSET(tcl) \
	((((tcl) >> 4) & TID) >> 4)
#घोषणा TCL_LUN(tcl) \
	(tcl & (AHC_NUM_LUNS - 1))
#घोषणा BUILD_TCL(scsiid, lun) \
	((lun) | (((scsiid) & TID) << 4))

#अगर_अघोषित	AHC_TARGET_MODE
#अघोषित	AHC_TMODE_ENABLE
#घोषणा	AHC_TMODE_ENABLE 0
#पूर्ण_अगर

/**************************** Driver Constants ********************************/
/*
 * The maximum number of supported tarमाला_लो.
 */
#घोषणा AHC_NUM_TARGETS 16

/*
 * The maximum number of supported luns.
 * The identअगरy message only supports 64 luns in SPI3.
 * You can have 2^64 luns when inक्रमmation unit transfers are enabled,
 * but it is करोubtful this driver will ever support IUTs.
 */
#घोषणा AHC_NUM_LUNS 64

/*
 * The maximum transfer per S/G segment.
 */
#घोषणा AHC_MAXTRANSFER_SIZE	 0x00ffffff	/* limited by 24bit counter */

/*
 * The maximum amount of SCB storage in hardware on a controller.
 * This value represents an upper bound.  Controllers vary in the number
 * they actually support.
 */
#घोषणा AHC_SCB_MAX	255

/*
 * The maximum number of concurrent transactions supported per driver instance.
 * Sequencer Control Blocks (SCBs) store per-transaction inक्रमmation.  Although
 * the space क्रम SCBs on the host adapter varies by model, the driver will
 * page the SCBs between host and controller memory as needed.  We are limited
 * to 253 because:
 * 	1) The 8bit nature of the RISC engine holds us to an 8bit value.
 * 	2) We reserve one value, 255, to represent the invalid element.
 *	3) Our input queue scheme requires one SCB to always be reserved
 *	   in advance of queuing any SCBs.  This takes us करोwn to 254.
 *	4) To handle our output queue correctly on machines that only
 * 	   support 32bit stores, we must clear the array 4 bytes at a
 *	   समय.  To aव्योम colliding with a DMA ग_लिखो from the sequencer,
 *	   we must be sure that 4 slots are empty when we ग_लिखो to clear
 *	   the queue.  This reduces us to 253 SCBs: 1 that just completed
 *	   and the known three additional empty slots in the queue that
 *	   precede it.
 */
#घोषणा AHC_MAX_QUEUE	253

/*
 * The maximum amount of SCB storage we allocate in host memory.  This
 * number should reflect the 1 additional SCB we require to handle our
 * qinfअगरo mechanism.
 */
#घोषणा AHC_SCB_MAX_ALLOC (AHC_MAX_QUEUE+1)

/*
 * Ring Buffer of incoming target commands.
 * We allocate 256 to simplअगरy the logic in the sequencer
 * by using the natural wrap poपूर्णांक of an 8bit counter.
 */
#घोषणा AHC_TMODE_CMDS	256

/* Reset line निश्चितion समय in us */
#घोषणा AHC_BUSRESET_DELAY	25

/******************* Chip Characteristics/Operating Settings  *****************/
/*
 * Chip Type
 * The chip order is from least sophisticated to most sophisticated.
 */
प्रकार क्रमागत अणु
	AHC_NONE	= 0x0000,
	AHC_CHIPID_MASK	= 0x00FF,
	AHC_AIC7770	= 0x0001,
	AHC_AIC7850	= 0x0002,
	AHC_AIC7855	= 0x0003,
	AHC_AIC7859	= 0x0004,
	AHC_AIC7860	= 0x0005,
	AHC_AIC7870	= 0x0006,
	AHC_AIC7880	= 0x0007,
	AHC_AIC7895	= 0x0008,
	AHC_AIC7895C	= 0x0009,
	AHC_AIC7890	= 0x000a,
	AHC_AIC7896	= 0x000b,
	AHC_AIC7892	= 0x000c,
	AHC_AIC7899	= 0x000d,
	AHC_VL		= 0x0100,	/* Bus type VL */
	AHC_EISA	= 0x0200,	/* Bus type EISA */
	AHC_PCI		= 0x0400,	/* Bus type PCI */
	AHC_BUS_MASK	= 0x0F00
पूर्ण ahc_chip;

/*
 * Features available in each chip type.
 */
प्रकार क्रमागत अणु
	AHC_FENONE	= 0x00000,
	AHC_ULTRA	= 0x00001,	/* Supports 20MHz Transfers */
	AHC_ULTRA2	= 0x00002,	/* Supports 40MHz Transfers */
	AHC_WIDE  	= 0x00004,	/* Wide Channel */
	AHC_TWIN	= 0x00008,	/* Twin Channel */
	AHC_MORE_SRAM	= 0x00010,	/* 80 bytes instead of 64 */
	AHC_CMD_CHAN	= 0x00020,	/* Has a Command DMA Channel */
	AHC_QUEUE_REGS	= 0x00040,	/* Has Queue management रेजिस्टरs */
	AHC_SG_PRELOAD	= 0x00080,	/* Can perक्रमm स्वतः-SG preload */
	AHC_SPIOCAP	= 0x00100,	/* Has a Serial Port I/O Cap Register */
	AHC_MULTI_TID	= 0x00200,	/* Has biपंचांगask of TIDs क्रम select-in */
	AHC_HS_MAILBOX	= 0x00400,	/* Has HS_MAILBOX रेजिस्टर */
	AHC_DT		= 0x00800,	/* Double Transition transfers */
	AHC_NEW_TERMCTL	= 0x01000,	/* Newer termination scheme */
	AHC_MULTI_FUNC	= 0x02000,	/* Multi-Function Twin Channel Device */
	AHC_LARGE_SCBS	= 0x04000,	/* 64byte SCBs */
	AHC_AUTORATE	= 0x08000,	/* Automatic update of SCSIRATE/OFFSET*/
	AHC_AUTOPAUSE	= 0x10000,	/* Automatic छोड़ो on रेजिस्टर access */
	AHC_TARGETMODE	= 0x20000,	/* Has tested target mode support */
	AHC_MULTIROLE	= 0x40000,	/* Space क्रम two roles at a समय */
	AHC_REMOVABLE	= 0x80000,	/* Hot-Swap supported */
	AHC_HVD		= 0x100000,	/* HVD rather than SE */
	AHC_AIC7770_FE	= AHC_FENONE,
	/*
	 * The real 7850 करोes not support Ultra modes, but there are
	 * several cards that use the generic 7850 PCI ID even though
	 * they are using an Ultra capable chip (7859/7860).  We start
	 * out with the AHC_ULTRA feature set and then check the DEVSTATUS
	 * रेजिस्टर to determine अगर the capability is really present.
	 */
	AHC_AIC7850_FE	= AHC_SPIOCAP|AHC_AUTOPAUSE|AHC_TARGETMODE|AHC_ULTRA,
	AHC_AIC7860_FE	= AHC_AIC7850_FE,
	AHC_AIC7870_FE	= AHC_TARGETMODE|AHC_AUTOPAUSE,
	AHC_AIC7880_FE	= AHC_AIC7870_FE|AHC_ULTRA,
	/*
	 * Although we have space क्रम both the initiator and
	 * target roles on ULTRA2 chips, we currently disable
	 * the initiator role to allow multi-scsi-id target mode
	 * configurations.  We can only respond on the same SCSI
	 * ID as our initiator role अगर we allow initiator operation.
	 * At some poपूर्णांक, we should add a configuration knob to
	 * allow both roles to be loaded.
	 */
	AHC_AIC7890_FE	= AHC_MORE_SRAM|AHC_CMD_CHAN|AHC_ULTRA2
			  |AHC_QUEUE_REGS|AHC_SG_PRELOAD|AHC_MULTI_TID
			  |AHC_HS_MAILBOX|AHC_NEW_TERMCTL|AHC_LARGE_SCBS
			  |AHC_TARGETMODE,
	AHC_AIC7892_FE	= AHC_AIC7890_FE|AHC_DT|AHC_AUTORATE|AHC_AUTOPAUSE,
	AHC_AIC7895_FE	= AHC_AIC7880_FE|AHC_MORE_SRAM|AHC_AUTOPAUSE
			  |AHC_CMD_CHAN|AHC_MULTI_FUNC|AHC_LARGE_SCBS,
	AHC_AIC7895C_FE	= AHC_AIC7895_FE|AHC_MULTI_TID,
	AHC_AIC7896_FE	= AHC_AIC7890_FE|AHC_MULTI_FUNC,
	AHC_AIC7899_FE	= AHC_AIC7892_FE|AHC_MULTI_FUNC
पूर्ण ahc_feature;

/*
 * Bugs in the silicon that we work around in software.
 */
प्रकार क्रमागत अणु
	AHC_BUGNONE		= 0x00,
	/*
	 * On all chips prior to the U2 product line,
	 * the WIDEODD S/G segment feature करोes not
	 * work during scsi->HostBus transfers.
	 */
	AHC_TMODE_WIDEODD_BUG	= 0x01,
	/*
	 * On the aic7890/91 Rev 0 chips, the स्वतःflush
	 * feature करोes not work.  A manual flush of
	 * the DMA FIFO is required.
	 */
	AHC_AUTOFLUSH_BUG	= 0x02,
	/*
	 * On many chips, cacheline streaming करोes not work.
	 */
	AHC_CACHETHEN_BUG	= 0x04,
	/*
	 * On the aic7896/97 chips, cacheline
	 * streaming must be enabled.
	 */
	AHC_CACHETHEN_DIS_BUG	= 0x08,
	/*
	 * PCI 2.1 Retry failure on non-empty data fअगरo.
	 */
	AHC_PCI_2_1_RETRY_BUG	= 0x10,
	/*
	 * Controller करोes not handle cacheline residuals
	 * properly on S/G segments अगर PCI MWI inकाष्ठाions
	 * are allowed.
	 */
	AHC_PCI_MWI_BUG		= 0x20,
	/*
	 * An SCB upload using the SCB channel's
	 * स्वतः array entry copy feature may 
	 * corrupt data.  This appears to only
	 * occur on 66MHz प्रणालीs.
	 */
	AHC_SCBCHAN_UPLOAD_BUG	= 0x40
पूर्ण ahc_bug;

/*
 * Configuration specअगरic settings.
 * The driver determines these settings by probing the
 * chip/controller's configuration.
 */
प्रकार क्रमागत अणु
	AHC_FNONE	      = 0x000,
	AHC_PRIMARY_CHANNEL   = 0x003,  /*
					 * The channel that should
					 * be probed first.
					 */
	AHC_USEDEFAULTS	      = 0x004,  /*
					 * For cards without an seeprom
					 * or a BIOS to initialize the chip's
					 * SRAM, we use the शेष target
					 * settings.
					 */
	AHC_SEQUENCER_DEBUG   = 0x008,
	AHC_SHARED_SRAM	      = 0x010,
	AHC_LARGE_SEEPROM     = 0x020,  /* Uses C56_66 not C46 */
	AHC_RESET_BUS_A	      = 0x040,
	AHC_RESET_BUS_B	      = 0x080,
	AHC_EXTENDED_TRANS_A  = 0x100,
	AHC_EXTENDED_TRANS_B  = 0x200,
	AHC_TERM_ENB_A	      = 0x400,
	AHC_TERM_ENB_B	      = 0x800,
	AHC_INITIATORROLE     = 0x1000,  /*
					  * Allow initiator operations on
					  * this controller.
					  */
	AHC_TARGETROLE	      = 0x2000,  /*
					  * Allow target operations on this
					  * controller.
					  */
	AHC_NEWEEPROM_FMT     = 0x4000,
	AHC_TQINFIFO_BLOCKED  = 0x10000,  /* Blocked रुकोing क्रम ATIOs */
	AHC_INT50_SPEEDFLEX   = 0x20000,  /*
					   * Internal 50pin connector
					   * sits behind an aic3860
					   */
	AHC_SCB_BTT	      = 0x40000,  /*
					   * The busy tarमाला_लो table is
					   * stored in SCB space rather
					   * than SRAM.
					   */
	AHC_BIOS_ENABLED      = 0x80000,
	AHC_ALL_INTERRUPTS    = 0x100000,
	AHC_PAGESCBS	      = 0x400000,  /* Enable SCB paging */
	AHC_EDGE_INTERRUPT    = 0x800000,  /* Device uses edge triggered पूर्णांकs */
	AHC_39BIT_ADDRESSING  = 0x1000000, /* Use 39 bit addressing scheme. */
	AHC_LSCBS_ENABLED     = 0x2000000, /* 64Byte SCBs enabled */
	AHC_SCB_CONFIG_USED   = 0x4000000, /* No SEEPROM but SCB2 had info. */
	AHC_NO_BIOS_INIT      = 0x8000000, /* No BIOS left over settings. */
	AHC_DISABLE_PCI_PERR  = 0x10000000,
	AHC_HAS_TERM_LOGIC    = 0x20000000
पूर्ण ahc_flag;

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
 * complete abnormally (non-zero status byte).
 */
काष्ठा status_pkt अणु
	uपूर्णांक32_t residual_datacnt;	/* Residual in the current S/G seg */
	uपूर्णांक32_t residual_sg_ptr;	/* The next S/G क्रम this transfer */
	uपूर्णांक8_t	 scsi_status;		/* Standard SCSI status byte */
पूर्ण;

/*
 * Target mode version of the shared data SCB segment.
 */
काष्ठा target_data अणु
	uपूर्णांक32_t residual_datacnt;	/* Residual in the current S/G seg */
	uपूर्णांक32_t residual_sg_ptr;	/* The next S/G क्रम this transfer */
	uपूर्णांक8_t  scsi_status;		/* SCSI status to give to initiator */
	uपूर्णांक8_t  target_phases;		/* Biपंचांगap of phases to execute */
	uपूर्णांक8_t  data_phase;		/* Data-In or Data-Out */
	uपूर्णांक8_t  initiator_tag;		/* Initiator's transaction tag */
पूर्ण;

काष्ठा hardware_scb अणु
/*0*/	जोड़ अणु
		/*
		 * If the cdb is 12 bytes or less, we embed it directly
		 * in the SCB.  For दीर्घer cdbs, we embed the address
		 * of the cdb payload as seen by the chip and a DMA
		 * is used to pull it in.
		 */
		uपूर्णांक8_t	 cdb[12];
		uपूर्णांक32_t cdb_ptr;
		काष्ठा	 status_pkt status;
		काष्ठा	 target_data tdata;
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
 * sequencer determines that there is a residual in the tranfer, it
 * will set the SG_RESID_VALID flag in sgptr and dma the scb back पूर्णांकo
 * host memory.  To sumarize:
 *
 * Sequencer:
 *	o A residual has occurred अगर SG_FULL_RESID is set in sgptr,
 *	  or residual_sgptr करोes not have SG_LIST_शून्य set.
 *
 *	o We are transferring the last segment अगर residual_datacnt has
 *	  the SG_LAST_SEG flag set.
 *
 * Host:
 *	o A residual has occurred अगर a completed scb has the
 *	  SG_RESID_VALID flag set.
 *
 *	o residual_sgptr and sgptr refer to the "next" sg entry
 *	  and so may poपूर्णांक beyond the last valid sg entry क्रम the
 *	  transfer.
 */ 
/*12*/	uपूर्णांक32_t dataptr;
/*16*/	uपूर्णांक32_t datacnt;		/*
					 * Byte 3 (numbered from 0) of
					 * the datacnt is really the
					 * 4th byte in that data address.
					 */
/*20*/	uपूर्णांक32_t sgptr;
#घोषणा SG_PTR_MASK	0xFFFFFFF8
/*24*/	uपूर्णांक8_t  control;	/* See SCB_CONTROL in aic7xxx.reg क्रम details */
/*25*/	uपूर्णांक8_t  scsiid;	/* what to load in the SCSIID रेजिस्टर */
/*26*/	uपूर्णांक8_t  lun;
/*27*/	uपूर्णांक8_t  tag;			/*
					 * Index पूर्णांकo our kernel SCB array.
					 * Also used as the tag क्रम tagged I/O
					 */
/*28*/	uपूर्णांक8_t  cdb_len;
/*29*/	uपूर्णांक8_t  scsirate;		/* Value क्रम SCSIRATE रेजिस्टर */
/*30*/	uपूर्णांक8_t  scsioffset;		/* Value क्रम SCSIOFFSET रेजिस्टर */
/*31*/	uपूर्णांक8_t  next;			/*
					 * Used क्रम thपढ़ोing SCBs in the
					 * "Waiting for Selection" and
					 * "Disconnected SCB" lists करोwn
					 * in the sequencer.
					 */
/*32*/	uपूर्णांक8_t  cdb32[32];		/*
					 * CDB storage क्रम cdbs of size
					 * 13->32.  We store them here
					 * because hardware scbs are
					 * allocated from DMA safe
					 * memory so we are guaranteed
					 * the controller can access
					 * this data.
					 */
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
काष्ठा ahc_dma_seg अणु
	uपूर्णांक32_t	addr;
	uपूर्णांक32_t	len;
#घोषणा	AHC_DMA_LAST_SEG	0x80000000
#घोषणा	AHC_SG_HIGH_ADDR_MASK	0x7F000000
#घोषणा	AHC_SG_LEN_MASK		0x00FFFFFF
पूर्ण;

काष्ठा sg_map_node अणु
	bus_dmamap_t		 sg_dmamap;
	dma_addr_t		 sg_physaddr;
	काष्ठा ahc_dma_seg*	 sg_vaddr;
	SLIST_ENTRY(sg_map_node) links;
पूर्ण;

/*
 * The current state of this SCB.
 */
प्रकार क्रमागत अणु
	SCB_FREE		= 0x0000,
	SCB_OTHERTCL_TIMEOUT	= 0x0002,/*
					  * Another device was active
					  * during the first समयout क्रम
					  * this SCB so we gave ourselves
					  * an additional समयout period
					  * in हाल it was hogging the
					  * bus.
				          */
	SCB_DEVICE_RESET	= 0x0004,
	SCB_SENSE		= 0x0008,
	SCB_CDB32_PTR		= 0x0010,
	SCB_RECOVERY_SCB	= 0x0020,
	SCB_AUTO_NEGOTIATE	= 0x0040,/* Negotiate to achieve goal. */
	SCB_NEGOTIATE		= 0x0080,/* Negotiation क्रमced क्रम command. */
	SCB_ABORT		= 0x0100,
	SCB_UNTAGGEDQ		= 0x0200,
	SCB_ACTIVE		= 0x0400,
	SCB_TARGET_IMMEDIATE	= 0x0800,
	SCB_TRANSMISSION_ERROR	= 0x1000,/*
					  * We detected a parity or CRC
					  * error that has effected the
					  * payload of the command.  This
					  * flag is checked when normal
					  * status is वापसed to catch
					  * the हाल of a target not
					  * responding to our attempt
					  * to report the error.
					  */
	SCB_TARGET_SCB		= 0x2000,
	SCB_SILENT		= 0x4000 /*
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
		TAILQ_ENTRY(scb)  tqe;
	पूर्ण links;
	LIST_ENTRY(scb)		  pending_links;
	ahc_io_ctx_t		  io_ctx;
	काष्ठा ahc_softc	 *ahc_softc;
	scb_flag		  flags;
	काष्ठा scb_platक्रमm_data *platक्रमm_data;
	काष्ठा sg_map_node	 *sg_map;
	काष्ठा ahc_dma_seg 	 *sg_list;
	dma_addr_t		  sg_list_phys;
	u_पूर्णांक			  sg_count;/* How full ahc_dma_seg is */
पूर्ण;

काष्ठा scb_data अणु
	SLIST_HEAD(, scb) मुक्त_scbs;	/*
					 * Pool of SCBs पढ़ोy to be asचिन्हित
					 * commands to execute.
					 */
	काष्ठा	scb *scbindex[256];	/*
					 * Mapping from tag to SCB.
					 * As tag identअगरiers are an
					 * 8bit value, we provide space
					 * क्रम all possible tag values.
					 * Any lookups to entries at or
					 * above AHC_SCB_MAX_ALLOC will
					 * always fail.
					 */
	काष्ठा	hardware_scb	*hscbs;	/* Array of hardware SCBs */
	काष्ठा	scb *scbarray;		/* Array of kernel SCBs */
	काष्ठा	scsi_sense_data *sense; /* Per SCB sense data */

	/*
	 * "Bus" addresses of our data काष्ठाures.
	 */
	bus_dma_tag_t	 hscb_dmat;	/* dmat क्रम our hardware SCB array */
	bus_dmamap_t	 hscb_dmamap;
	dma_addr_t	 hscb_busaddr;
	bus_dma_tag_t	 sense_dmat;
	bus_dmamap_t	 sense_dmamap;
	dma_addr_t	 sense_busaddr;
	bus_dma_tag_t	 sg_dmat;	/* dmat क्रम our sg segments */
	SLIST_HEAD(, sg_map_node) sg_maps;
	uपूर्णांक8_t	numscbs;
	uपूर्णांक8_t	maxhscbs;		/* Number of SCBs on the card */
	uपूर्णांक8_t	init_level;		/*
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
#घोषणा AHC_TMODE_EVENT_BUFFER_SIZE 8
काष्ठा ahc_पंचांगode_event अणु
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
#अगर_घोषित AHC_TARGET_MODE 
काष्ठा ahc_पंचांगode_lstate अणु
	काष्ठा cam_path *path;
	काष्ठा ccb_hdr_slist accept_tios;
	काष्ठा ccb_hdr_slist immed_notअगरies;
	काष्ठा ahc_पंचांगode_event event_buffer[AHC_TMODE_EVENT_BUFFER_SIZE];
	uपूर्णांक8_t event_r_idx;
	uपूर्णांक8_t event_w_idx;
पूर्ण;
#अन्यथा
काष्ठा ahc_पंचांगode_lstate;
#पूर्ण_अगर

/******************** Transfer Negotiation Dataकाष्ठाures *********************/
#घोषणा AHC_TRANS_CUR		0x01	/* Modअगरy current neogtiation status */
#घोषणा AHC_TRANS_ACTIVE	0x03	/* Assume this target is on the bus */
#घोषणा AHC_TRANS_GOAL		0x04	/* Modअगरy negotiation goal */
#घोषणा AHC_TRANS_USER		0x08	/* Modअगरy user negotiation settings */

#घोषणा AHC_WIDTH_UNKNOWN	0xFF
#घोषणा AHC_PERIOD_UNKNOWN	0xFF
#घोषणा AHC_OFFSET_UNKNOWN	0xFF
#घोषणा AHC_PPR_OPTS_UNKNOWN	0xFF

/*
 * Transfer Negotiation Inक्रमmation.
 */
काष्ठा ahc_transinfo अणु
	uपूर्णांक8_t protocol_version;	/* SCSI Revision level */
	uपूर्णांक8_t transport_version;	/* SPI Revision level */
	uपूर्णांक8_t width;			/* Bus width */
	uपूर्णांक8_t period;			/* Sync rate factor */
	uपूर्णांक8_t offset;			/* Sync offset */
	uपूर्णांक8_t ppr_options;		/* Parallel Protocol Request options */
पूर्ण;

/*
 * Per-initiator current, goal and user transfer negotiation inक्रमmation. */
काष्ठा ahc_initiator_tinfo अणु
	uपूर्णांक8_t scsirate;		/* Computed value क्रम SCSIRATE reg */
	काष्ठा ahc_transinfo curr;
	काष्ठा ahc_transinfo goal;
	काष्ठा ahc_transinfo user;
पूर्ण;

/*
 * Per enabled target ID state.
 * Poपूर्णांकers to lun target state as well as sync/wide negotiation inक्रमmation
 * क्रम each initiator<->target mapping.  For the initiator role we pretend
 * that we are the target and the tarमाला_लो are the initiators since the
 * negotiation is the same regardless of role.
 */
काष्ठा ahc_पंचांगode_tstate अणु
	काष्ठा ahc_पंचांगode_lstate*	enabled_luns[AHC_NUM_LUNS];
	काष्ठा ahc_initiator_tinfo	transinfo[AHC_NUM_TARGETS];

	/*
	 * Per initiator state biपंचांगasks.
	 */
	uपूर्णांक16_t	 स्वतः_negotiate;/* Auto Negotiation Required */
	uपूर्णांक16_t	 ultraenb;	/* Using ultra sync rate  */
	uपूर्णांक16_t	 discenable;	/* Disconnection allowed  */
	uपूर्णांक16_t	 tagenable;	/* Tagged Queuing allowed */
पूर्ण;

/*
 * Data काष्ठाure क्रम our table of allowed synchronous transfer rates.
 */
काष्ठा ahc_syncrate अणु
	u_पूर्णांक sxfr_u2;	/* Value of the SXFR parameter क्रम Ultra2+ Chips */
	u_पूर्णांक sxfr;	/* Value of the SXFR parameter क्रम <= Ultra Chips */
#घोषणा		ULTRA_SXFR 0x100	/* Rate Requires Ultra Mode set */
#घोषणा		ST_SXFR	   0x010	/* Rate Single Transition Only */
#घोषणा		DT_SXFR	   0x040	/* Rate Double Transition Only */
	uपूर्णांक8_t period; /* Period to send to SCSI target */
	स्थिर अक्षर *rate;
पूर्ण;

/* Safe and valid period क्रम async negotiations. */
#घोषणा	AHC_ASYNC_XFER_PERIOD 0x45
#घोषणा	AHC_ULTRA2_XFER_PERIOD 0x0a

/*
 * Indexes पूर्णांकo our table of syncronous transfer rates.
 */
#घोषणा AHC_SYNCRATE_DT		0
#घोषणा AHC_SYNCRATE_ULTRA2	1
#घोषणा AHC_SYNCRATE_ULTRA	3
#घोषणा AHC_SYNCRATE_FAST	6
#घोषणा AHC_SYNCRATE_MAX	AHC_SYNCRATE_DT
#घोषणा	AHC_SYNCRATE_MIN	13

/***************************** Lookup Tables **********************************/
/*
 * Phase -> name and message out response
 * to parity errors in each phase table. 
 */
काष्ठा ahc_phase_table_entry अणु
        uपूर्णांक8_t phase;
        uपूर्णांक8_t mesg_out; /* Message response to parity errors */
	अक्षर *phasemsg;
पूर्ण;

/************************** Serial EEPROM Format ******************************/

काष्ठा seeprom_config अणु
/*
 * Per SCSI ID Configuration Flags
 */
	uपूर्णांक16_t device_flags[16];	/* words 0-15 */
#घोषणा		CFXFER		0x0007	/* synchronous transfer rate */
#घोषणा		CFSYNCH		0x0008	/* enable synchronous transfer */
#घोषणा		CFDISC		0x0010	/* enable disconnection */
#घोषणा		CFWIDEB		0x0020	/* wide bus device */
#घोषणा		CFSYNCHISULTRA	0x0040	/* CFSYNCH is an ultra offset (2940AU)*/
#घोषणा		CFSYNCSINGLE	0x0080	/* Single-Transition संकेतling */
#घोषणा		CFSTART		0x0100	/* send start unit SCSI command */
#घोषणा		CFINCBIOS	0x0200	/* include in BIOS scan */
#घोषणा		CFRNFOUND	0x0400	/* report even अगर not found */
#घोषणा		CFMULTILUNDEV	0x0800	/* Probe multiple luns in BIOS scan */
#घोषणा		CFWBCACHEENB	0x4000	/* Enable W-Behind Cache on disks */
#घोषणा		CFWBCACHENOP	0xc000	/* Don't touch W-Behind Cache */

/*
 * BIOS Control Bits
 */
	uपूर्णांक16_t bios_control;		/* word 16 */
#घोषणा		CFSUPREM	0x0001	/* support all हटाओable drives */
#घोषणा		CFSUPREMB	0x0002	/* support हटाओable boot drives */
#घोषणा		CFBIOSEN	0x0004	/* BIOS enabled */
#घोषणा		CFBIOS_BUSSCAN	0x0008	/* Have the BIOS Scan the Bus */
#घोषणा		CFSM2DRV	0x0010	/* support more than two drives */
#घोषणा		CFSTPWLEVEL	0x0010	/* Termination level control */
#घोषणा		CF284XEXTEND	0x0020	/* extended translation (284x cards) */	
#घोषणा		CFCTRL_A	0x0020	/* BIOS displays Ctrl-A message */	
#घोषणा		CFTERM_MENU	0x0040	/* BIOS displays termination menu */	
#घोषणा		CFEXTEND	0x0080	/* extended translation enabled */
#घोषणा		CFSCAMEN	0x0100	/* SCAM enable */
#घोषणा		CFMSG_LEVEL	0x0600	/* BIOS Message Level */
#घोषणा			CFMSG_VERBOSE	0x0000
#घोषणा			CFMSG_SILENT	0x0200
#घोषणा			CFMSG_DIAG	0x0400
#घोषणा		CFBOOTCD	0x0800  /* Support Bootable CD-ROM */
/*		UNUSED		0xff00	*/

/*
 * Host Adapter Control Bits
 */
	uपूर्णांक16_t adapter_control;	/* word 17 */	
#घोषणा		CFAUTOTERM	0x0001	/* Perक्रमm Auto termination */
#घोषणा		CFULTRAEN	0x0002	/* Ultra SCSI speed enable */
#घोषणा		CF284XSELTO     0x0003	/* Selection समयout (284x cards) */
#घोषणा		CF284XFIFO      0x000C	/* FIFO Threshold (284x cards) */
#घोषणा		CFSTERM		0x0004	/* SCSI low byte termination */
#घोषणा		CFWSTERM	0x0008	/* SCSI high byte termination */
#घोषणा		CFSPARITY	0x0010	/* SCSI parity */
#घोषणा		CF284XSTERM     0x0020	/* SCSI low byte term (284x cards) */	
#घोषणा		CFMULTILUN	0x0020
#घोषणा		CFRESETB	0x0040	/* reset SCSI bus at boot */
#घोषणा		CFCLUSTERENB	0x0080	/* Cluster Enable */
#घोषणा		CFBOOTCHAN	0x0300	/* probe this channel first */
#घोषणा		CFBOOTCHANSHIFT 8
#घोषणा		CFSEAUTOTERM	0x0400	/* Ultra2 Perक्रमm secondary Auto Term*/
#घोषणा		CFSELOWTERM	0x0800	/* Ultra2 secondary low term */
#घोषणा		CFSEHIGHTERM	0x1000	/* Ultra2 secondary high term */
#घोषणा		CFENABLEDV	0x4000	/* Perक्रमm Doमुख्य Validation*/

/*
 * Bus Release Time, Host Adapter ID
 */
	uपूर्णांक16_t brसमय_id;		/* word 18 */
#घोषणा		CFSCSIID	0x000f	/* host adapter SCSI ID */
/*		UNUSED		0x00f0	*/
#घोषणा		CFBRTIME	0xff00	/* bus release समय */

/*
 * Maximum tarमाला_लो
 */
	uपूर्णांक16_t max_tarमाला_लो;		/* word 19 */	
#घोषणा		CFMAXTARG	0x00ff	/* maximum tarमाला_लो */
#घोषणा		CFBOOTLUN	0x0f00	/* Lun to boot from */
#घोषणा		CFBOOTID	0xf000	/* Target to boot from */
	uपूर्णांक16_t res_1[10];		/* words 20-29 */
	uपूर्णांक16_t signature;		/* Signature == 0x250 */
#घोषणा		CFSIGNATURE	0x250
#घोषणा		CFSIGNATURE2	0x300
	uपूर्णांक16_t checksum;		/* word 31 */
पूर्ण;

/****************************  Message Buffer *********************************/
प्रकार क्रमागत अणु
	MSG_TYPE_NONE			= 0x00,
	MSG_TYPE_INITIATOR_MSGOUT	= 0x01,
	MSG_TYPE_INITIATOR_MSGIN	= 0x02,
	MSG_TYPE_TARGET_MSGOUT		= 0x03,
	MSG_TYPE_TARGET_MSGIN		= 0x04
पूर्ण ahc_msg_type;

प्रकार क्रमागत अणु
	MSGLOOP_IN_PROG,
	MSGLOOP_MSGCOMPLETE,
	MSGLOOP_TERMINATED
पूर्ण msg_loop_stat;

/*********************** Software Configuration Structure *********************/
TAILQ_HEAD(scb_tailq, scb);

काष्ठा ahc_aic7770_softc अणु
	/*
	 * Saved रेजिस्टर state used क्रम chip_init().
	 */
	uपूर्णांक8_t busspd;
	uपूर्णांक8_t busसमय;
पूर्ण;

काष्ठा ahc_pci_softc अणु
	/*
	 * Saved रेजिस्टर state used क्रम chip_init().
	 */
	uपूर्णांक32_t  devconfig;
	uपूर्णांक16_t  targcrccnt;
	uपूर्णांक8_t   command;
	uपूर्णांक8_t   csize_latसमय;
	uपूर्णांक8_t   optionmode;
	uपूर्णांक8_t   crccontrol1;
	uपूर्णांक8_t   dscommand0;
	uपूर्णांक8_t   dspcistatus;
	uपूर्णांक8_t   scbbaddr;
	uपूर्णांक8_t   dff_thrsh;
पूर्ण;

जोड़ ahc_bus_softc अणु
	काष्ठा ahc_aic7770_softc aic7770_softc;
	काष्ठा ahc_pci_softc pci_softc;
पूर्ण;

प्रकार व्योम (*ahc_bus_पूर्णांकr_t)(काष्ठा ahc_softc *);
प्रकार पूर्णांक (*ahc_bus_chip_init_t)(काष्ठा ahc_softc *);
प्रकार व्योम ahc_callback_t (व्योम *);

काष्ठा ahc_softc अणु
	bus_space_tag_t           tag;
	bus_space_handle_t        bsh;
	काष्ठा scb_data		 *scb_data;

	काष्ठा scb		 *next_queued_scb;

	/*
	 * SCBs that have been sent to the controller
	 */
	BSD_LIST_HEAD(, scb)	  pending_scbs;

	/*
	 * Counting lock क्रम deferring the release of additional
	 * untagged transactions from the untagged_queues.  When
	 * the lock is decremented to 0, all queues in the
	 * untagged_queues array are run.
	 */
	u_पूर्णांक			  untagged_queue_lock;

	/*
	 * Per-target queue of untagged-transactions.  The
	 * transaction at the head of the queue is the
	 * currently pending untagged transaction क्रम the
	 * target.  The driver only allows a single untagged
	 * transaction per target.
	 */
	काष्ठा scb_tailq	  untagged_queues[AHC_NUM_TARGETS];

	/*
	 * Bus attachment specअगरic data.
	 */
	जोड़ ahc_bus_softc	  bus_softc;

	/*
	 * Platक्रमm specअगरic data.
	 */
	काष्ठा ahc_platक्रमm_data *platक्रमm_data;

	/*
	 * Platक्रमm specअगरic device inक्रमmation.
	 */
	ahc_dev_softc_t		  dev_softc;
	काष्ठा device		  *dev;

	/*
	 * Bus specअगरic device inक्रमmation.
	 */
	ahc_bus_पूर्णांकr_t		  bus_पूर्णांकr;

	/*
	 * Bus specअगरic initialization required
	 * after a chip reset.
	 */
	ahc_bus_chip_init_t	  bus_chip_init;

	/*
	 * Target mode related state kept on a per enabled lun basis.
	 * Tarमाला_लो that are not enabled will have null entries.
	 * As an initiator, we keep one target entry क्रम our initiator
	 * ID to store our sync/wide transfer settings.
	 */
	काष्ठा ahc_पंचांगode_tstate  *enabled_tarमाला_लो[AHC_NUM_TARGETS];

	/*
	 * The black hole device responsible क्रम handling requests क्रम
	 * disabled luns on enabled tarमाला_लो.
	 */
	काष्ठा ahc_पंचांगode_lstate  *black_hole;

	/*
	 * Device instance currently on the bus aरुकोing a जारी TIO
	 * क्रम a command that was not given the disconnect priveledge.
	 */
	काष्ठा ahc_पंचांगode_lstate  *pending_device;

	/*
	 * Card अक्षरacteristics
	 */
	ahc_chip		  chip;
	ahc_feature		  features;
	ahc_bug			  bugs;
	ahc_flag		  flags;
	काष्ठा seeprom_config	 *seep_config;

	/* Values to store in the SEQCTL रेजिस्टर क्रम छोड़ो and unछोड़ो */
	uपूर्णांक8_t			  unछोड़ो;
	uपूर्णांक8_t			  छोड़ो;

	/* Command Queues */
	uपूर्णांक8_t			  qoutfअगरonext;
	uपूर्णांक8_t			  qinfअगरonext;
	uपूर्णांक8_t			 *qoutfअगरo;
	uपूर्णांक8_t			 *qinfअगरo;

	/* Critical Section Data */
	काष्ठा cs		 *critical_sections;
	u_पूर्णांक			  num_critical_sections;

	/* Channel Names ('A', 'B', etc.) */
	अक्षर			  channel;
	अक्षर			  channel_b;

	/* Initiator Bus ID */
	uपूर्णांक8_t			  our_id;
	uपूर्णांक8_t			  our_id_b;

	/*
	 * PCI error detection.
	 */
	पूर्णांक			  unsolicited_पूर्णांकs;

	/*
	 * Target incoming command FIFO.
	 */
	काष्ठा target_cmd	 *tarअ_लोmds;
	uपूर्णांक8_t			  tqinfअगरonext;

	/*
	 * Cached copy of the sequencer control रेजिस्टर.
	 */
	uपूर्णांक8_t			  seqctl;

	/*
	 * Incoming and outgoing message handling.
	 */
	uपूर्णांक8_t			  send_msg_लिखो_त्रुटि;
	ahc_msg_type		  msg_type;
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
	bus_dmamap_t		  shared_data_dmamap;
	dma_addr_t		  shared_data_busaddr;

	/*
	 * Bus address of the one byte buffer used to
	 * work-around a DMA bug क्रम chips <= aic7880
	 * in target mode.
	 */
	dma_addr_t		  dma_bug_buf;

	/* Number of enabled target mode device on this card */
	u_पूर्णांक			  enabled_luns;

	/* Initialization level of this data काष्ठाure */
	u_पूर्णांक			  init_level;

	/* PCI cacheline size. */
	u_पूर्णांक			  pci_cachesize;

	/*
	 * Count of parity errors we have seen as a target.
	 * We स्वतः-disable parity error checking after seeing
	 * AHC_PCI_TARGET_PERR_THRESH number of errors.
	 */
	u_पूर्णांक			  pci_target_perr_count;
#घोषणा		AHC_PCI_TARGET_PERR_THRESH	10

	/* Maximum number of sequencer inकाष्ठाions supported. */
	u_पूर्णांक			  inकाष्ठाion_ram_size;

	/* Per-Unit descriptive inक्रमmation */
	स्थिर अक्षर		 *description;
	अक्षर			 *name;
	पूर्णांक			  unit;

	/* Selection Timer settings */
	पूर्णांक			  selसमय;
	पूर्णांक			  selसमय_b;

	uपूर्णांक16_t	 	  user_discenable;/* Disconnection allowed  */
	uपूर्णांक16_t		  user_tagenable;/* Tagged Queuing allowed */
पूर्ण;

/************************ Active Device Inक्रमmation ***************************/
प्रकार क्रमागत अणु
	ROLE_UNKNOWN,
	ROLE_INITIATOR,
	ROLE_TARGET
पूर्ण role_t;

काष्ठा ahc_devinfo अणु
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
प्रकार पूर्णांक (ahc_device_setup_t)(काष्ठा ahc_softc *);

काष्ठा ahc_pci_identity अणु
	uपूर्णांक64_t		 full_id;
	uपूर्णांक64_t		 id_mask;
	स्थिर अक्षर		*name;
	ahc_device_setup_t	*setup;
पूर्ण;

/***************************** VL/EISA Declarations ***************************/
काष्ठा aic7770_identity अणु
	uपूर्णांक32_t		 full_id;
	uपूर्णांक32_t		 id_mask;
	स्थिर अक्षर		*name;
	ahc_device_setup_t	*setup;
पूर्ण;
बाह्य काष्ठा aic7770_identity aic7770_ident_table[];
बाह्य स्थिर पूर्णांक ahc_num_aic7770_devs;

#घोषणा AHC_EISA_SLOT_OFFSET	0xc00
#घोषणा AHC_EISA_IOSIZE		0x100

/*************************** Function Declarations ****************************/
/******************************************************************************/

/***************************** PCI Front End *********************************/
स्थिर काष्ठा ahc_pci_identity	*ahc_find_pci_device(ahc_dev_softc_t);
पूर्णांक			 ahc_pci_config(काष्ठा ahc_softc *,
					स्थिर काष्ठा ahc_pci_identity *);
पूर्णांक			 ahc_pci_test_रेजिस्टर_access(काष्ठा ahc_softc *);
व्योम __maybe_unused	 ahc_pci_resume(काष्ठा ahc_softc *ahc);

/*************************** EISA/VL Front End ********************************/
काष्ठा aic7770_identity *aic7770_find_device(uपूर्णांक32_t);
पूर्णांक			 aic7770_config(काष्ठा ahc_softc *ahc,
					काष्ठा aic7770_identity *,
					u_पूर्णांक port);

/************************** SCB and SCB queue management **********************/
पूर्णांक		ahc_probe_scbs(काष्ठा ahc_softc *);
व्योम		ahc_qinfअगरo_requeue_tail(काष्ठा ahc_softc *ahc,
					 काष्ठा scb *scb);
पूर्णांक		ahc_match_scb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb,
			      पूर्णांक target, अक्षर channel, पूर्णांक lun,
			      u_पूर्णांक tag, role_t role);

/****************************** Initialization ********************************/
काष्ठा ahc_softc	*ahc_alloc(व्योम *platक्रमm_arg, अक्षर *name);
पूर्णांक			 ahc_softc_init(काष्ठा ahc_softc *);
व्योम			 ahc_controller_info(काष्ठा ahc_softc *ahc, अक्षर *buf);
पूर्णांक			 ahc_chip_init(काष्ठा ahc_softc *ahc);
पूर्णांक			 ahc_init(काष्ठा ahc_softc *ahc);
व्योम			 ahc_पूर्णांकr_enable(काष्ठा ahc_softc *ahc, पूर्णांक enable);
व्योम			 ahc_छोड़ो_and_flushwork(काष्ठा ahc_softc *ahc);
पूर्णांक __maybe_unused	 ahc_suspend(काष्ठा ahc_softc *ahc);
पूर्णांक __maybe_unused	 ahc_resume(काष्ठा ahc_softc *ahc);
व्योम			 ahc_set_unit(काष्ठा ahc_softc *, पूर्णांक);
व्योम			 ahc_set_name(काष्ठा ahc_softc *, अक्षर *);
व्योम			 ahc_मुक्त(काष्ठा ahc_softc *ahc);
पूर्णांक			 ahc_reset(काष्ठा ahc_softc *ahc, पूर्णांक reinit);

/***************************** Error Recovery *********************************/
प्रकार क्रमागत अणु
	SEARCH_COMPLETE,
	SEARCH_COUNT,
	SEARCH_REMOVE
पूर्ण ahc_search_action;
पूर्णांक			ahc_search_qinfअगरo(काष्ठा ahc_softc *ahc, पूर्णांक target,
					   अक्षर channel, पूर्णांक lun, u_पूर्णांक tag,
					   role_t role, uपूर्णांक32_t status,
					   ahc_search_action action);
पूर्णांक			ahc_search_untagged_queues(काष्ठा ahc_softc *ahc,
						   ahc_io_ctx_t ctx,
						   पूर्णांक target, अक्षर channel,
						   पूर्णांक lun, uपूर्णांक32_t status,
						   ahc_search_action action);
पूर्णांक			ahc_search_disc_list(काष्ठा ahc_softc *ahc, पूर्णांक target,
					     अक्षर channel, पूर्णांक lun, u_पूर्णांक tag,
					     पूर्णांक stop_on_first, पूर्णांक हटाओ,
					     पूर्णांक save_state);
पूर्णांक			ahc_reset_channel(काष्ठा ahc_softc *ahc, अक्षर channel,
					  पूर्णांक initiate_reset);

/*************************** Utility Functions ********************************/
व्योम			ahc_compile_devinfo(काष्ठा ahc_devinfo *devinfo,
					    u_पूर्णांक our_id, u_पूर्णांक target,
					    u_पूर्णांक lun, अक्षर channel,
					    role_t role);
/************************** Transfer Negotiation ******************************/
स्थिर काष्ठा ahc_syncrate*	ahc_find_syncrate(काष्ठा ahc_softc *ahc, u_पूर्णांक *period,
					  u_पूर्णांक *ppr_options, u_पूर्णांक maxsync);
u_पूर्णांक			ahc_find_period(काष्ठा ahc_softc *ahc,
					u_पूर्णांक scsirate, u_पूर्णांक maxsync);
/*
 * Negotiation types.  These are used to qualअगरy अगर we should renegotiate
 * even अगर our goal and current transport parameters are identical.
 */
प्रकार क्रमागत अणु
	AHC_NEG_TO_GOAL,	/* Renegotiate only अगर goal and curr dअगरfer. */
	AHC_NEG_IF_NON_ASYNC,	/* Renegotiate so दीर्घ as goal is non-async. */
	AHC_NEG_ALWAYS		/* Renegotiat even अगर goal is async. */
पूर्ण ahc_neg_type;
पूर्णांक			ahc_update_neg_request(काष्ठा ahc_softc*,
					       काष्ठा ahc_devinfo*,
					       काष्ठा ahc_पंचांगode_tstate*,
					       काष्ठा ahc_initiator_tinfo*,
					       ahc_neg_type);
व्योम			ahc_set_width(काष्ठा ahc_softc *ahc,
				      काष्ठा ahc_devinfo *devinfo,
				      u_पूर्णांक width, u_पूर्णांक type, पूर्णांक छोड़ोd);
व्योम			ahc_set_syncrate(काष्ठा ahc_softc *ahc,
					 काष्ठा ahc_devinfo *devinfo,
					 स्थिर काष्ठा ahc_syncrate *syncrate,
					 u_पूर्णांक period, u_पूर्णांक offset,
					 u_पूर्णांक ppr_options,
					 u_पूर्णांक type, पूर्णांक छोड़ोd);
प्रकार क्रमागत अणु
	AHC_QUEUE_NONE,
	AHC_QUEUE_BASIC,
	AHC_QUEUE_TAGGED
पूर्ण ahc_queue_alg;

/**************************** Target Mode *************************************/
#अगर_घोषित AHC_TARGET_MODE
व्योम		ahc_send_lstate_events(काष्ठा ahc_softc *,
				       काष्ठा ahc_पंचांगode_lstate *);
व्योम		ahc_handle_en_lun(काष्ठा ahc_softc *ahc,
				  काष्ठा cam_sim *sim, जोड़ ccb *ccb);
cam_status	ahc_find_पंचांगode_devs(काष्ठा ahc_softc *ahc,
				    काष्ठा cam_sim *sim, जोड़ ccb *ccb,
				    काष्ठा ahc_पंचांगode_tstate **tstate,
				    काष्ठा ahc_पंचांगode_lstate **lstate,
				    पूर्णांक notfound_failure);
#अगर_अघोषित AHC_TMODE_ENABLE
#घोषणा AHC_TMODE_ENABLE 0
#पूर्ण_अगर
#पूर्ण_अगर
/******************************* Debug ***************************************/
#अगर_घोषित AHC_DEBUG
बाह्य uपूर्णांक32_t ahc_debug;
#घोषणा	AHC_SHOW_MISC		0x0001
#घोषणा	AHC_SHOW_SENSE		0x0002
#घोषणा AHC_DUMP_SEEPROM	0x0004
#घोषणा AHC_SHOW_TERMCTL	0x0008
#घोषणा AHC_SHOW_MEMORY		0x0010
#घोषणा AHC_SHOW_MESSAGES	0x0020
#घोषणा	AHC_SHOW_DV		0x0040
#घोषणा AHC_SHOW_SELTO		0x0080
#घोषणा AHC_SHOW_QFULL		0x0200
#घोषणा AHC_SHOW_QUEUE		0x0400
#घोषणा AHC_SHOW_TQIN		0x0800
#घोषणा AHC_SHOW_MASKED_ERRORS	0x1000
#घोषणा AHC_DEBUG_SEQUENCER	0x2000
#पूर्ण_अगर
व्योम			ahc_prपूर्णांक_devinfo(काष्ठा ahc_softc *ahc,
					  काष्ठा ahc_devinfo *dev);
व्योम			ahc_dump_card_state(काष्ठा ahc_softc *ahc);
पूर्णांक			ahc_prपूर्णांक_रेजिस्टर(स्थिर ahc_reg_parse_entry_t *table,
					   u_पूर्णांक num_entries,
					   स्थिर अक्षर *name,
					   u_पूर्णांक address,
					   u_पूर्णांक value,
					   u_पूर्णांक *cur_column,
					   u_पूर्णांक wrap_poपूर्णांक);
/******************************* SEEPROM *************************************/
पूर्णांक		ahc_acquire_seeprom(काष्ठा ahc_softc *ahc,
				    काष्ठा seeprom_descriptor *sd);
व्योम		ahc_release_seeprom(काष्ठा seeprom_descriptor *sd);
#पूर्ण_अगर /* _AIC7XXX_H_ */
