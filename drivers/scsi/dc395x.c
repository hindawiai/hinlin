<शैली गुरु>
/*
 * dc395x.c
 *
 * Device Driver क्रम Tekram DC395(U/UW/F), DC315(U)
 * PCI SCSI Bus Master Host Adapter
 * (SCSI chip set used Tekram ASIC TRM-S1040)
 *
 * Authors:
 *  C.L. Huang <ching@tekram.com.tw>
 *  Erich Chen <erich@tekram.com.tw>
 *  (C) Copyright 1995-1999 Tekram Technology Co., Ltd.
 *
 *  Kurt Garloff <garloff@suse.de>
 *  (C) 1999-2000 Kurt Garloff
 *
 *  Oliver Neukum <oliver@neukum.name>
 *  Ali Akcaagac <aliakc@web.de>
 *  Jamie Lenehan <lenehan@twibble.org>
 *  (C) 2003
 *
 * License: GNU GPL
 *
 *************************************************************************
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/delay.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "dc395x.h"

#घोषणा DC395X_NAME	"dc395x"
#घोषणा DC395X_BANNER	"Tekram DC395(U/UW/F), DC315(U) - ASIC TRM-S1040"
#घोषणा DC395X_VERSION	"v2.05, 2004/03/08"

/*---------------------------------------------------------------------------
                                  Features
 ---------------------------------------------------------------------------*/
/*
 * Set to disable parts of the driver
 */
/*#घोषणा DC395x_NO_DISCONNECT*/
/*#घोषणा DC395x_NO_TAGQ*/
/*#घोषणा DC395x_NO_SYNC*/
/*#घोषणा DC395x_NO_WIDE*/

/*---------------------------------------------------------------------------
                                  Debugging
 ---------------------------------------------------------------------------*/
/*
 * Types of debugging that can be enabled and disabled
 */
#घोषणा DBG_KG		0x0001
#घोषणा DBG_0		0x0002
#घोषणा DBG_1		0x0004
#घोषणा DBG_SG		0x0020
#घोषणा DBG_FIFO	0x0040
#घोषणा DBG_PIO		0x0080


/*
 * Set set of things to output debugging क्रम.
 * Undefine to हटाओ all debugging
 */
/*#घोषणा DEBUG_MASK (DBG_0|DBG_1|DBG_SG|DBG_FIFO|DBG_PIO)*/
/*#घोषणा  DEBUG_MASK	DBG_0*/


/*
 * Output a kernel mesage at the specअगरied level and append the
 * driver name and a ": " to the start of the message
 */
#घोषणा dprपूर्णांकkl(level, क्रमmat, arg...)  \
    prपूर्णांकk(level DC395X_NAME ": " क्रमmat , ## arg)


#अगर_घोषित DEBUG_MASK
/*
 * prपूर्णांक a debug message - this is क्रमmated with KERN_DEBUG, then the
 * driver name followed by a ": " and then the message is output. 
 * This also checks that the specअगरied debug level is enabled beक्रमe
 * outputing the message
 */
#घोषणा dprपूर्णांकkdbg(type, क्रमmat, arg...) \
	करो अणु \
		अगर ((type) & (DEBUG_MASK)) \
			dprपूर्णांकkl(KERN_DEBUG , क्रमmat , ## arg); \
	पूर्ण जबतक (0)

/*
 * Check अगर the specअगरied type of debugging is enabled
 */
#घोषणा debug_enabled(type)	((DEBUG_MASK) & (type))

#अन्यथा
/*
 * No debugging. Do nothing
 */
#घोषणा dprपूर्णांकkdbg(type, क्रमmat, arg...) \
	करो अणुपूर्ण जबतक (0)
#घोषणा debug_enabled(type)	(0)

#पूर्ण_अगर


#अगर_अघोषित PCI_VENDOR_ID_TEKRAM
#घोषणा PCI_VENDOR_ID_TEKRAM                    0x1DE1	/* Venकरोr ID    */
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_TEKRAM_TRMS1040
#घोषणा PCI_DEVICE_ID_TEKRAM_TRMS1040           0x0391	/* Device ID    */
#पूर्ण_अगर


#घोषणा DC395x_LOCK_IO(dev,flags)		spin_lock_irqsave(((काष्ठा Scsi_Host *)dev)->host_lock, flags)
#घोषणा DC395x_UNLOCK_IO(dev,flags)		spin_unlock_irqrestore(((काष्ठा Scsi_Host *)dev)->host_lock, flags)

#घोषणा DC395x_पढ़ो8(acb,address)		(u8)(inb(acb->io_port_base + (address)))
#घोषणा DC395x_पढ़ो16(acb,address)		(u16)(inw(acb->io_port_base + (address)))
#घोषणा DC395x_पढ़ो32(acb,address)		(u32)(inl(acb->io_port_base + (address)))
#घोषणा DC395x_ग_लिखो8(acb,address,value)	outb((value), acb->io_port_base + (address))
#घोषणा DC395x_ग_लिखो16(acb,address,value)	outw((value), acb->io_port_base + (address))
#घोषणा DC395x_ग_लिखो32(acb,address,value)	outl((value), acb->io_port_base + (address))

/* cmd->result */
#घोषणा RES_TARGET		0x000000FF	/* Target State */
#घोषणा RES_TARGET_LNX  STATUS_MASK	/* Only official ... */
#घोषणा RES_ENDMSG		0x0000FF00	/* End Message */
#घोषणा RES_DID			0x00FF0000	/* DID_ codes */
#घोषणा RES_DRV			0xFF000000	/* DRIVER_ codes */

#घोषणा MK_RES(drv,did,msg,tgt) ((पूर्णांक)(drv)<<24 | (पूर्णांक)(did)<<16 | (पूर्णांक)(msg)<<8 | (पूर्णांक)(tgt))
#घोषणा MK_RES_LNX(drv,did,msg,tgt) ((पूर्णांक)(drv)<<24 | (पूर्णांक)(did)<<16 | (पूर्णांक)(msg)<<8 | (पूर्णांक)(tgt)<<1)

#घोषणा SET_RES_TARGET(who,tgt) अणु who &= ~RES_TARGET; who |= (पूर्णांक)(tgt); पूर्ण
#घोषणा SET_RES_TARGET_LNX(who,tgt) अणु who &= ~RES_TARGET_LNX; who |= (पूर्णांक)(tgt) << 1; पूर्ण
#घोषणा SET_RES_MSG(who,msg) अणु who &= ~RES_ENDMSG; who |= (पूर्णांक)(msg) << 8; पूर्ण
#घोषणा SET_RES_DID(who,did) अणु who &= ~RES_DID; who |= (पूर्णांक)(did) << 16; पूर्ण
#घोषणा SET_RES_DRV(who,drv) अणु who &= ~RES_DRV; who |= (पूर्णांक)(drv) << 24; पूर्ण

#घोषणा TAG_NONE 255

/*
 * srb->segement_x is the hw sg list. It is always allocated as a
 * DC395x_MAX_SG_LISTENTRY entries in a linear block which करोes not
 * cross a page boundy.
 */
#घोषणा SEGMENTX_LEN	(माप(काष्ठा SGentry)*DC395x_MAX_SG_LISTENTRY)


काष्ठा SGentry अणु
	u32 address;		/* bus! address */
	u32 length;
पूर्ण;

/* The SEEPROM काष्ठाure क्रम TRM_S1040 */
काष्ठा NVRamTarget अणु
	u8 cfg0;		/* Target configuration byte 0  */
	u8 period;		/* Target period                */
	u8 cfg2;		/* Target configuration byte 2  */
	u8 cfg3;		/* Target configuration byte 3  */
पूर्ण;

काष्ठा NvRamType अणु
	u8 sub_venकरोr_id[2];	/* 0,1  Sub Venकरोr ID   */
	u8 sub_sys_id[2];	/* 2,3  Sub System ID   */
	u8 sub_class;		/* 4    Sub Class       */
	u8 venकरोr_id[2];	/* 5,6  Venकरोr ID       */
	u8 device_id[2];	/* 7,8  Device ID       */
	u8 reserved;		/* 9    Reserved        */
	काष्ठा NVRamTarget target[DC395x_MAX_SCSI_ID];
						/** 10,11,12,13
						 ** 14,15,16,17
						 ** ....
						 ** ....
						 ** 70,71,72,73
						 */
	u8 scsi_id;		/* 74 Host Adapter SCSI ID      */
	u8 channel_cfg;		/* 75 Channel configuration     */
	u8 delay_समय;		/* 76 Power on delay समय       */
	u8 max_tag;		/* 77 Maximum tags              */
	u8 reserved0;		/* 78  */
	u8 boot_target;		/* 79  */
	u8 boot_lun;		/* 80  */
	u8 reserved1;		/* 81  */
	u16 reserved2[22];	/* 82,..125 */
	u16 cksum;		/* 126,127 */
पूर्ण;

काष्ठा ScsiReqBlk अणु
	काष्ठा list_head list;		/* next/prev ptrs क्रम srb lists */
	काष्ठा DeviceCtlBlk *dcb;
	काष्ठा scsi_cmnd *cmd;

	काष्ठा SGentry *segment_x;	/* Linear array of hw sg entries (up to 64 entries) */
	dma_addr_t sg_bus_addr;	        /* Bus address of sg list (ie, of segment_x) */

	u8 sg_count;			/* No of HW sg entries क्रम this request */
	u8 sg_index;			/* Index of HW sg entry क्रम this request */
	माप_प्रकार total_xfer_length;	/* Total number of bytes reमुख्यing to be transferred */
	माप_प्रकार request_length;		/* Total number of bytes in this request */
	/*
	 * The sense buffer handling function, request_sense, uses
	 * the first hw sg entry (segment_x[0]) and the transfer
	 * length (total_xfer_length). While करोing this it stores the
	 * original values पूर्णांकo the last sg hw list
	 * (srb->segment_x[DC395x_MAX_SG_LISTENTRY - 1] and the
	 * total_xfer_length in xferred. These values are restored in
	 * pci_unmap_srb_sense. This is the only place xferred is used.
	 */
	माप_प्रकार xferred;		        /* Saved copy of total_xfer_length */

	u16 state;

	u8 msgin_buf[6];
	u8 msgout_buf[6];

	u8 adapter_status;
	u8 target_status;
	u8 msg_count;
	u8 end_message;

	u8 tag_number;
	u8 status;
	u8 retry_count;
	u8 flag;

	u8 scsi_phase;
पूर्ण;

काष्ठा DeviceCtlBlk अणु
	काष्ठा list_head list;		/* next/prev ptrs क्रम the dcb list */
	काष्ठा AdapterCtlBlk *acb;
	काष्ठा list_head srb_going_list;	/* head of going srb list */
	काष्ठा list_head srb_रुकोing_list;	/* head of रुकोing srb list */

	काष्ठा ScsiReqBlk *active_srb;
	u32 tag_mask;

	u16 max_command;

	u8 target_id;		/* SCSI Target ID  (SCSI Only) */
	u8 target_lun;		/* SCSI Log.  Unit (SCSI Only) */
	u8 identअगरy_msg;
	u8 dev_mode;

	u8 inquiry7;		/* To store Inquiry flags */
	u8 sync_mode;		/* 0:async mode */
	u8 min_nego_period;	/* क्रम nego. */
	u8 sync_period;		/* क्रम reg.  */

	u8 sync_offset;		/* क्रम reg. and nego.(low nibble) */
	u8 flag;
	u8 dev_type;
	u8 init_tcq_flag;
पूर्ण;

काष्ठा AdapterCtlBlk अणु
	काष्ठा Scsi_Host *scsi_host;

	अचिन्हित दीर्घ io_port_base;
	अचिन्हित दीर्घ io_port_len;

	काष्ठा list_head dcb_list;		/* head of going dcb list */
	काष्ठा DeviceCtlBlk *dcb_run_robin;
	काष्ठा DeviceCtlBlk *active_dcb;

	काष्ठा list_head srb_मुक्त_list;		/* head of मुक्त srb list */
	काष्ठा ScsiReqBlk *पंचांगp_srb;
	काष्ठा समयr_list रुकोing_समयr;
	काष्ठा समयr_list selto_समयr;

	अचिन्हित दीर्घ last_reset;

	u16 srb_count;

	u8 sel_समयout;

	अचिन्हित पूर्णांक irq_level;
	u8 tag_max_num;
	u8 acb_flag;
	u8 gmode2;

	u8 config;
	u8 lun_chk;
	u8 scan_devices;
	u8 hostid_bit;

	u8 dcb_map[DC395x_MAX_SCSI_ID];
	काष्ठा DeviceCtlBlk *children[DC395x_MAX_SCSI_ID][32];

	काष्ठा pci_dev *dev;

	u8 msg_len;

	काष्ठा ScsiReqBlk srb_array[DC395x_MAX_SRB_CNT];
	काष्ठा ScsiReqBlk srb;

	काष्ठा NvRamType eeprom;	/* eeprom settings क्रम this adapter */
पूर्ण;


/*---------------------------------------------------------------------------
                            Forward declarations
 ---------------------------------------------------------------------------*/
अटल व्योम data_out_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम data_in_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम command_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम status_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम msgout_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम msgin_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम data_out_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम data_in_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम command_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम status_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम msgout_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम msgin_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम nop0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status);
अटल व्योम nop1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb, 
		u16 *pscsi_status);
अटल व्योम set_basic_config(काष्ठा AdapterCtlBlk *acb);
अटल व्योम cleanup_after_transfer(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb);
अटल व्योम reset_scsi_bus(काष्ठा AdapterCtlBlk *acb);
अटल व्योम data_io_transfer(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb, u16 io_dir);
अटल व्योम disconnect(काष्ठा AdapterCtlBlk *acb);
अटल व्योम reselect(काष्ठा AdapterCtlBlk *acb);
अटल u8 start_scsi(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb);
अटल अंतरभूत व्योम enable_msgout_पात(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb);
अटल व्योम build_srb(काष्ठा scsi_cmnd *cmd, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb);
अटल व्योम करोing_srb_करोne(काष्ठा AdapterCtlBlk *acb, u8 did_code,
		काष्ठा scsi_cmnd *cmd, u8 क्रमce);
अटल व्योम scsi_reset_detect(काष्ठा AdapterCtlBlk *acb);
अटल व्योम pci_unmap_srb(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb);
अटल व्योम pci_unmap_srb_sense(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb);
अटल व्योम srb_करोne(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb);
अटल व्योम request_sense(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb);
अटल व्योम set_xfer_rate(काष्ठा AdapterCtlBlk *acb,
		काष्ठा DeviceCtlBlk *dcb);
अटल व्योम रुकोing_समयout(काष्ठा समयr_list *t);


/*---------------------------------------------------------------------------
                                 Static Data
 ---------------------------------------------------------------------------*/
अटल u16 current_sync_offset = 0;

अटल व्योम *dc395x_scsi_phase0[] = अणु
	data_out_phase0,/* phase:0 */
	data_in_phase0,	/* phase:1 */
	command_phase0,	/* phase:2 */
	status_phase0,	/* phase:3 */
	nop0,		/* phase:4 PH_BUS_FREE .. initial phase */
	nop0,		/* phase:5 PH_BUS_FREE .. initial phase */
	msgout_phase0,	/* phase:6 */
	msgin_phase0,	/* phase:7 */
पूर्ण;

अटल व्योम *dc395x_scsi_phase1[] = अणु
	data_out_phase1,/* phase:0 */
	data_in_phase1,	/* phase:1 */
	command_phase1,	/* phase:2 */
	status_phase1,	/* phase:3 */
	nop1,		/* phase:4 PH_BUS_FREE .. initial phase */
	nop1,		/* phase:5 PH_BUS_FREE .. initial phase */
	msgout_phase1,	/* phase:6 */
	msgin_phase1,	/* phase:7 */
पूर्ण;

/*
 *Fast20:	000	 50ns, 20.0 MHz
 *		001	 75ns, 13.3 MHz
 *		010	100ns, 10.0 MHz
 *		011	125ns,  8.0 MHz
 *		100	150ns,  6.6 MHz
 *		101	175ns,  5.7 MHz
 *		110	200ns,  5.0 MHz
 *		111	250ns,  4.0 MHz
 *
 *Fast40(LVDS):	000	 25ns, 40.0 MHz
 *		001	 50ns, 20.0 MHz
 *		010	 75ns, 13.3 MHz
 *		011	100ns, 10.0 MHz
 *		100	125ns,  8.0 MHz
 *		101	150ns,  6.6 MHz
 *		110	175ns,  5.7 MHz
 *		111	200ns,  5.0 MHz
 */
/*अटल u8	घड़ी_period[] = अणु12,19,25,31,37,44,50,62पूर्ण;*/

/* real period:48ns,76ns,100ns,124ns,148ns,176ns,200ns,248ns */
अटल u8 घड़ी_period[] = अणु 12, 18, 25, 31, 37, 43, 50, 62 पूर्ण;
अटल u16 घड़ी_speed[] = अणु 200, 133, 100, 80, 67, 58, 50, 40 पूर्ण;


/*---------------------------------------------------------------------------
                                Configuration
  ---------------------------------------------------------------------------*/
/*
 * Module/boot parameters currently effect *all* instances of the
 * card in the प्रणाली.
 */

/*
 * Command line parameters are stored in a काष्ठाure below.
 * These are the index's पूर्णांकo the काष्ठाure क्रम the various
 * command line options.
 */
#घोषणा CFG_ADAPTER_ID		0
#घोषणा CFG_MAX_SPEED		1
#घोषणा CFG_DEV_MODE		2
#घोषणा CFG_ADAPTER_MODE	3
#घोषणा CFG_TAGS		4
#घोषणा CFG_RESET_DELAY		5

#घोषणा CFG_NUM			6	/* number of configuration items */


/*
 * Value used to indicate that a command line override
 * hasn't been used to modअगरy the value.
 */
#घोषणा CFG_PARAM_UNSET -1


/*
 * Hold command line parameters.
 */
काष्ठा ParameterData अणु
	पूर्णांक value;		/* value of this setting */
	पूर्णांक min;		/* minimum value */
	पूर्णांक max;		/* maximum value */
	पूर्णांक def;		/* शेष value */
	पूर्णांक safe;		/* safe value */
पूर्ण;
अटल काष्ठा ParameterData cfg_data[] = अणु
	अणु /* adapter id */
		CFG_PARAM_UNSET,
		0,
		15,
		7,
		7
	पूर्ण,
	अणु /* max speed */
		CFG_PARAM_UNSET,
		  0,
		  7,
		  1,	/* 13.3Mhz */
		  4,	/*  6.7Hmz */
	पूर्ण,
	अणु /* dev mode */
		CFG_PARAM_UNSET,
		0,
		0x3f,
		NTC_DO_PARITY_CHK | NTC_DO_DISCONNECT | NTC_DO_SYNC_NEGO |
			NTC_DO_WIDE_NEGO | NTC_DO_TAG_QUEUEING |
			NTC_DO_SEND_START,
		NTC_DO_PARITY_CHK | NTC_DO_SEND_START
	पूर्ण,
	अणु /* adapter mode */
		CFG_PARAM_UNSET,
		0,
		0x2f,
		NAC_SCANLUN |
		NAC_GT2DRIVES | NAC_GREATER_1G | NAC_POWERON_SCSI_RESET
			/*| NAC_ACTIVE_NEG*/,
		NAC_GT2DRIVES | NAC_GREATER_1G | NAC_POWERON_SCSI_RESET | 0x08
	पूर्ण,
	अणु /* tags */
		CFG_PARAM_UNSET,
		0,
		5,
		3,	/* 16 tags (??) */
		2,
	पूर्ण,
	अणु /* reset delay */
		CFG_PARAM_UNSET,
		0,
		180,
		1,	/* 1 second */
		10,	/* 10 seconds */
	पूर्ण
पूर्ण;


/*
 * Safe settings. If set to zero the BIOS/शेष values with
 * command line overrides will be used. If set to 1 then safe and
 * slow settings will be used.
 */
अटल bool use_safe_settings = 0;
module_param_named(safe, use_safe_settings, bool, 0);
MODULE_PARM_DESC(safe, "Use safe and slow settings only. Default: false");


module_param_named(adapter_id, cfg_data[CFG_ADAPTER_ID].value, पूर्णांक, 0);
MODULE_PARM_DESC(adapter_id, "Adapter SCSI ID. Default 7 (0-15)");

module_param_named(max_speed, cfg_data[CFG_MAX_SPEED].value, पूर्णांक, 0);
MODULE_PARM_DESC(max_speed, "Maximum bus speed. Default 1 (0-7) Speeds: 0=20, 1=13.3, 2=10, 3=8, 4=6.7, 5=5.8, 6=5, 7=4 Mhz");

module_param_named(dev_mode, cfg_data[CFG_DEV_MODE].value, पूर्णांक, 0);
MODULE_PARM_DESC(dev_mode, "Device mode.");

module_param_named(adapter_mode, cfg_data[CFG_ADAPTER_MODE].value, पूर्णांक, 0);
MODULE_PARM_DESC(adapter_mode, "Adapter mode.");

module_param_named(tags, cfg_data[CFG_TAGS].value, पूर्णांक, 0);
MODULE_PARM_DESC(tags, "Number of tags (1<<x). Default 3 (0-5)");

module_param_named(reset_delay, cfg_data[CFG_RESET_DELAY].value, पूर्णांक, 0);
MODULE_PARM_DESC(reset_delay, "Reset delay in seconds. Default 1 (0-180)");


/**
 * set_safe_settings - अगर the use_safe_settings option is set then
 * set all values to the safe and slow values.
 **/
अटल व्योम set_safe_settings(व्योम)
अणु
	अगर (use_safe_settings)
	अणु
		पूर्णांक i;

		dprपूर्णांकkl(KERN_INFO, "Using safe settings.\n");
		क्रम (i = 0; i < CFG_NUM; i++)
		अणु
			cfg_data[i].value = cfg_data[i].safe;
		पूर्ण
	पूर्ण
पूर्ण


/**
 * fix_settings - reset any boot parameters which are out of range
 * back to the शेष values.
 **/
अटल व्योम fix_settings(व्योम)
अणु
	पूर्णांक i;

	dprपूर्णांकkdbg(DBG_1,
		"setup: AdapterId=%08x MaxSpeed=%08x DevMode=%08x "
		"AdapterMode=%08x Tags=%08x ResetDelay=%08x\n",
		cfg_data[CFG_ADAPTER_ID].value,
		cfg_data[CFG_MAX_SPEED].value,
		cfg_data[CFG_DEV_MODE].value,
		cfg_data[CFG_ADAPTER_MODE].value,
		cfg_data[CFG_TAGS].value,
		cfg_data[CFG_RESET_DELAY].value);
	क्रम (i = 0; i < CFG_NUM; i++)
	अणु
		अगर (cfg_data[i].value < cfg_data[i].min
		    || cfg_data[i].value > cfg_data[i].max)
			cfg_data[i].value = cfg_data[i].def;
	पूर्ण
पूर्ण



/*
 * Mapping from the eeprom delay index value (index पूर्णांकo this array)
 * to the number of actual seconds that the delay should be क्रम.
 */
अटल अक्षर eeprom_index_to_delay_map[] =
	अणु 1, 3, 5, 10, 16, 30, 60, 120 पूर्ण;


/**
 * eeprom_index_to_delay - Take the eeprom delay setting and convert it
 * पूर्णांकo a number of seconds.
 *
 * @eeprom: The eeprom काष्ठाure in which we find the delay index to map.
 **/
अटल व्योम eeprom_index_to_delay(काष्ठा NvRamType *eeprom)
अणु
	eeprom->delay_समय = eeprom_index_to_delay_map[eeprom->delay_समय];
पूर्ण


/**
 * delay_to_eeprom_index - Take a delay in seconds and वापस the
 * बंदst eeprom index which will delay क्रम at least that amount of
 * seconds.
 *
 * @delay: The delay, in seconds, to find the eeprom index क्रम.
 **/
अटल पूर्णांक delay_to_eeprom_index(पूर्णांक delay)
अणु
	u8 idx = 0;
	जबतक (idx < 7 && eeprom_index_to_delay_map[idx] < delay)
		idx++;
	वापस idx;
पूर्ण


/**
 * eeprom_override - Override the eeprom settings, in the provided
 * eeprom काष्ठाure, with values that have been set on the command
 * line.
 *
 * @eeprom: The eeprom data to override with command line options.
 **/
अटल व्योम eeprom_override(काष्ठा NvRamType *eeprom)
अणु
	u8 id;

	/* Adapter Settings */
	अगर (cfg_data[CFG_ADAPTER_ID].value != CFG_PARAM_UNSET)
		eeprom->scsi_id = (u8)cfg_data[CFG_ADAPTER_ID].value;

	अगर (cfg_data[CFG_ADAPTER_MODE].value != CFG_PARAM_UNSET)
		eeprom->channel_cfg = (u8)cfg_data[CFG_ADAPTER_MODE].value;

	अगर (cfg_data[CFG_RESET_DELAY].value != CFG_PARAM_UNSET)
		eeprom->delay_समय = delay_to_eeprom_index(
					cfg_data[CFG_RESET_DELAY].value);

	अगर (cfg_data[CFG_TAGS].value != CFG_PARAM_UNSET)
		eeprom->max_tag = (u8)cfg_data[CFG_TAGS].value;

	/* Device Settings */
	क्रम (id = 0; id < DC395x_MAX_SCSI_ID; id++) अणु
		अगर (cfg_data[CFG_DEV_MODE].value != CFG_PARAM_UNSET)
			eeprom->target[id].cfg0 =
				(u8)cfg_data[CFG_DEV_MODE].value;

		अगर (cfg_data[CFG_MAX_SPEED].value != CFG_PARAM_UNSET)
			eeprom->target[id].period =
				(u8)cfg_data[CFG_MAX_SPEED].value;

	पूर्ण
पूर्ण


/*---------------------------------------------------------------------------
 ---------------------------------------------------------------------------*/

अटल अचिन्हित पूर्णांक list_size(काष्ठा list_head *head)
अणु
	अचिन्हित पूर्णांक count = 0;
	काष्ठा list_head *pos;
	list_क्रम_each(pos, head)
		count++;
	वापस count;
पूर्ण


अटल काष्ठा DeviceCtlBlk *dcb_get_next(काष्ठा list_head *head,
		काष्ठा DeviceCtlBlk *pos)
अणु
	पूर्णांक use_next = 0;
	काष्ठा DeviceCtlBlk* next = शून्य;
	काष्ठा DeviceCtlBlk* i;

	अगर (list_empty(head))
		वापस शून्य;

	/* find supplied dcb and then select the next one */
	list_क्रम_each_entry(i, head, list)
		अगर (use_next) अणु
			next = i;
			अवरोध;
		पूर्ण अन्यथा अगर (i == pos) अणु
			use_next = 1;
		पूर्ण
	/* अगर no next one take the head one (ie, wraparound) */
	अगर (!next)
        	list_क्रम_each_entry(i, head, list) अणु
        		next = i;
        		अवरोध;
        	पूर्ण

	वापस next;
पूर्ण


अटल व्योम मुक्त_tag(काष्ठा DeviceCtlBlk *dcb, काष्ठा ScsiReqBlk *srb)
अणु
	अगर (srb->tag_number < 255) अणु
		dcb->tag_mask &= ~(1 << srb->tag_number);	/* मुक्त tag mask */
		srb->tag_number = 255;
	पूर्ण
पूर्ण


/* Find cmd in SRB list */
अटल अंतरभूत काष्ठा ScsiReqBlk *find_cmd(काष्ठा scsi_cmnd *cmd,
		काष्ठा list_head *head)
अणु
	काष्ठा ScsiReqBlk *i;
	list_क्रम_each_entry(i, head, list)
		अगर (i->cmd == cmd)
			वापस i;
	वापस शून्य;
पूर्ण

/* Sets the समयr to wake us up */
अटल व्योम रुकोing_set_समयr(काष्ठा AdapterCtlBlk *acb, अचिन्हित दीर्घ to)
अणु
	अगर (समयr_pending(&acb->रुकोing_समयr))
		वापस;
	अगर (समय_beक्रमe(jअगरfies + to, acb->last_reset - HZ / 2))
		acb->रुकोing_समयr.expires =
		    acb->last_reset - HZ / 2 + 1;
	अन्यथा
		acb->रुकोing_समयr.expires = jअगरfies + to + 1;
	add_समयr(&acb->रुकोing_समयr);
पूर्ण


/* Send the next command from the रुकोing list to the bus */
अटल व्योम रुकोing_process_next(काष्ठा AdapterCtlBlk *acb)
अणु
	काष्ठा DeviceCtlBlk *start = शून्य;
	काष्ठा DeviceCtlBlk *pos;
	काष्ठा DeviceCtlBlk *dcb;
	काष्ठा ScsiReqBlk *srb;
	काष्ठा list_head *dcb_list_head = &acb->dcb_list;

	अगर (acb->active_dcb
	    || (acb->acb_flag & (RESET_DETECT + RESET_DONE + RESET_DEV)))
		वापस;

	अगर (समयr_pending(&acb->रुकोing_समयr))
		del_समयr(&acb->रुकोing_समयr);

	अगर (list_empty(dcb_list_head))
		वापस;

	/*
	 * Find the starting dcb. Need to find it again in the list
	 * since the list may have changed since we set the ptr to it
	 */
	list_क्रम_each_entry(dcb, dcb_list_head, list)
		अगर (dcb == acb->dcb_run_robin) अणु
			start = dcb;
			अवरोध;
		पूर्ण
	अगर (!start) अणु
		/* This can happen! */
		start = list_entry(dcb_list_head->next, typeof(*start), list);
		acb->dcb_run_robin = start;
	पूर्ण


	/*
	 * Loop over the dcb, but we start somewhere (potentially) in
	 * the middle of the loop so we need to manully करो this.
	 */
	pos = start;
	करो अणु
		काष्ठा list_head *रुकोing_list_head = &pos->srb_रुकोing_list;

		/* Make sure, the next another device माला_लो scheduled ... */
		acb->dcb_run_robin = dcb_get_next(dcb_list_head,
						  acb->dcb_run_robin);

		अगर (list_empty(रुकोing_list_head) ||
		    pos->max_command <= list_size(&pos->srb_going_list)) अणु
			/* move to next dcb */
			pos = dcb_get_next(dcb_list_head, pos);
		पूर्ण अन्यथा अणु
			srb = list_entry(रुकोing_list_head->next,
					 काष्ठा ScsiReqBlk, list);

			/* Try to send to the bus */
			अगर (!start_scsi(acb, pos, srb))
				list_move(&srb->list, &pos->srb_going_list);
			अन्यथा
				रुकोing_set_समयr(acb, HZ/50);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (pos != start);
पूर्ण


/* Wake up रुकोing queue */
अटल व्योम रुकोing_समयout(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा AdapterCtlBlk *acb = from_समयr(acb, t, रुकोing_समयr);
	dprपूर्णांकkdbg(DBG_1,
		"waiting_timeout: Queue woken up by timer. acb=%p\n", acb);
	DC395x_LOCK_IO(acb->scsi_host, flags);
	रुकोing_process_next(acb);
	DC395x_UNLOCK_IO(acb->scsi_host, flags);
पूर्ण


/* Get the DCB क्रम a given ID/LUN combination */
अटल काष्ठा DeviceCtlBlk *find_dcb(काष्ठा AdapterCtlBlk *acb, u8 id, u8 lun)
अणु
	वापस acb->children[id][lun];
पूर्ण


/* Send SCSI Request Block (srb) to adapter (acb) */
अटल व्योम send_srb(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb)
अणु
	काष्ठा DeviceCtlBlk *dcb = srb->dcb;

	अगर (dcb->max_command <= list_size(&dcb->srb_going_list) ||
	    acb->active_dcb ||
	    (acb->acb_flag & (RESET_DETECT + RESET_DONE + RESET_DEV))) अणु
		list_add_tail(&srb->list, &dcb->srb_रुकोing_list);
		रुकोing_process_next(acb);
		वापस;
	पूर्ण

	अगर (!start_scsi(acb, dcb, srb)) अणु
		list_add_tail(&srb->list, &dcb->srb_going_list);
	पूर्ण अन्यथा अणु
		list_add(&srb->list, &dcb->srb_रुकोing_list);
		रुकोing_set_समयr(acb, HZ / 50);
	पूर्ण
पूर्ण

/* Prepare SRB क्रम being sent to Device DCB w/ command *cmd */
अटल व्योम build_srb(काष्ठा scsi_cmnd *cmd, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb)
अणु
	पूर्णांक nseg;
	क्रमागत dma_data_direction dir = cmd->sc_data_direction;
	dprपूर्णांकkdbg(DBG_0, "build_srb: (0x%p) <%02i-%i>\n",
		cmd, dcb->target_id, dcb->target_lun);

	srb->dcb = dcb;
	srb->cmd = cmd;
	srb->sg_count = 0;
	srb->total_xfer_length = 0;
	srb->sg_bus_addr = 0;
	srb->sg_index = 0;
	srb->adapter_status = 0;
	srb->target_status = 0;
	srb->msg_count = 0;
	srb->status = 0;
	srb->flag = 0;
	srb->state = 0;
	srb->retry_count = 0;
	srb->tag_number = TAG_NONE;
	srb->scsi_phase = PH_BUS_FREE;	/* initial phase */
	srb->end_message = 0;

	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);

	अगर (dir == DMA_NONE || !nseg) अणु
		dprपूर्णांकkdbg(DBG_0,
			"build_srb: [0] len=%d buf=%p use_sg=%d !MAP=%08x\n",
			   cmd->bufflen, scsi_sglist(cmd), scsi_sg_count(cmd),
			   srb->segment_x[0].address);
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		u32 reqlen = scsi_bufflen(cmd);
		काष्ठा scatterlist *sg;
		काष्ठा SGentry *sgp = srb->segment_x;

		srb->sg_count = nseg;

		dprपूर्णांकkdbg(DBG_0,
			   "build_srb: [n] len=%d buf=%p use_sg=%d segs=%d\n",
			   reqlen, scsi_sglist(cmd), scsi_sg_count(cmd),
			   srb->sg_count);

		scsi_क्रम_each_sg(cmd, sg, srb->sg_count, i) अणु
			u32 busaddr = (u32)sg_dma_address(sg);
			u32 seglen = (u32)sg->length;
			sgp[i].address = busaddr;
			sgp[i].length = seglen;
			srb->total_xfer_length += seglen;
		पूर्ण
		sgp += srb->sg_count - 1;

		/*
		 * adjust last page अगर too big as it is allocated
		 * on even page boundaries
		 */
		अगर (srb->total_xfer_length > reqlen) अणु
			sgp->length -= (srb->total_xfer_length - reqlen);
			srb->total_xfer_length = reqlen;
		पूर्ण

		/* Fixup क्रम WIDE padding - make sure length is even */
		अगर (dcb->sync_period & WIDE_SYNC &&
		    srb->total_xfer_length % 2) अणु
			srb->total_xfer_length++;
			sgp->length++;
		पूर्ण

		srb->sg_bus_addr = dma_map_single(&dcb->acb->dev->dev,
				srb->segment_x, SEGMENTX_LEN, DMA_TO_DEVICE);

		dprपूर्णांकkdbg(DBG_SG, "build_srb: [n] map sg %p->%08x(%05x)\n",
			srb->segment_x, srb->sg_bus_addr, SEGMENTX_LEN);
	पूर्ण

	srb->request_length = srb->total_xfer_length;
पूर्ण


/**
 * dc395x_queue_command_lck - queue scsi command passed from the mid
 * layer, invoke 'done' on completion
 *
 * @cmd: poपूर्णांकer to scsi command object
 * @करोne: function poपूर्णांकer to be invoked on completion
 *
 * Returns 1 अगर the adapter (host) is busy, अन्यथा वापसs 0. One
 * reason क्रम an adapter to be busy is that the number
 * of outstanding queued commands is alपढ़ोy equal to
 * काष्ठा Scsi_Host::can_queue .
 *
 * Required: अगर काष्ठा Scsi_Host::can_queue is ever non-zero
 *           then this function is required.
 *
 * Locks: काष्ठा Scsi_Host::host_lock held on entry (with "irqsave")
 *        and is expected to be held on वापस.
 *
 **/
अटल पूर्णांक dc395x_queue_command_lck(काष्ठा scsi_cmnd *cmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा DeviceCtlBlk *dcb;
	काष्ठा ScsiReqBlk *srb;
	काष्ठा AdapterCtlBlk *acb =
	    (काष्ठा AdapterCtlBlk *)cmd->device->host->hostdata;
	dprपूर्णांकkdbg(DBG_0, "queue_command: (0x%p) <%02i-%i> cmnd=0x%02x\n",
		cmd, cmd->device->id, (u8)cmd->device->lun, cmd->cmnd[0]);

	/* Assume BAD_TARGET; will be cleared later */
	cmd->result = DID_BAD_TARGET << 16;

	/* ignore invalid tarमाला_लो */
	अगर (cmd->device->id >= acb->scsi_host->max_id ||
	    cmd->device->lun >= acb->scsi_host->max_lun ||
	    cmd->device->lun >31) अणु
		जाओ complete;
	पूर्ण

	/* करोes the specअगरied lun on the specअगरied device exist */
	अगर (!(acb->dcb_map[cmd->device->id] & (1 << cmd->device->lun))) अणु
		dprपूर्णांकkl(KERN_INFO, "queue_command: Ignore target <%02i-%i>\n",
			cmd->device->id, (u8)cmd->device->lun);
		जाओ complete;
	पूर्ण

	/* करो we have a DCB क्रम the device */
	dcb = find_dcb(acb, cmd->device->id, cmd->device->lun);
	अगर (!dcb) अणु
		/* should never happen */
		dprपूर्णांकkl(KERN_ERR, "queue_command: No such device <%02i-%i>",
			cmd->device->id, (u8)cmd->device->lun);
		जाओ complete;
	पूर्ण

	/* set callback and clear result in the command */
	cmd->scsi_करोne = करोne;
	cmd->result = 0;

	srb = list_first_entry_or_null(&acb->srb_मुक्त_list,
			काष्ठा ScsiReqBlk, list);
	अगर (!srb) अणु
		/*
		 * Return 1 since we are unable to queue this command at this
		 * poपूर्णांक in समय.
		 */
		dprपूर्णांकkdbg(DBG_0, "queue_command: No free srb's\n");
		वापस 1;
	पूर्ण
	list_del(&srb->list);

	build_srb(cmd, dcb, srb);

	अगर (!list_empty(&dcb->srb_रुकोing_list)) अणु
		/* append to रुकोing queue */
		list_add_tail(&srb->list, &dcb->srb_रुकोing_list);
		रुकोing_process_next(acb);
	पूर्ण अन्यथा अणु
		/* process immediately */
		send_srb(acb, srb);
	पूर्ण
	dprपूर्णांकkdbg(DBG_1, "queue_command: (0x%p) done\n", cmd);
	वापस 0;

complete:
	/*
	 * Complete the command immediatey, and then वापस 0 to
	 * indicate that we have handled the command. This is usually
	 * करोne when the commad is क्रम things like non existent
	 * devices.
	 */
	करोne(cmd);
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(dc395x_queue_command)

अटल व्योम dump_रेजिस्टर_info(काष्ठा AdapterCtlBlk *acb,
		काष्ठा DeviceCtlBlk *dcb, काष्ठा ScsiReqBlk *srb)
अणु
	u16 pstat;
	काष्ठा pci_dev *dev = acb->dev;
	pci_पढ़ो_config_word(dev, PCI_STATUS, &pstat);
	अगर (!dcb)
		dcb = acb->active_dcb;
	अगर (!srb && dcb)
		srb = dcb->active_srb;
	अगर (srb) अणु
		अगर (!srb->cmd)
			dprपूर्णांकkl(KERN_INFO, "dump: srb=%p cmd=%p OOOPS!\n",
				srb, srb->cmd);
		अन्यथा
			dprपूर्णांकkl(KERN_INFO, "dump: srb=%p cmd=%p "
				 "cmnd=0x%02x <%02i-%i>\n",
				srb, srb->cmd,
				srb->cmd->cmnd[0], srb->cmd->device->id,
				(u8)srb->cmd->device->lun);
		prपूर्णांकk("  sglist=%p cnt=%i idx=%i len=%zu\n",
		       srb->segment_x, srb->sg_count, srb->sg_index,
		       srb->total_xfer_length);
		prपूर्णांकk("  state=0x%04x status=0x%02x phase=0x%02x (%sconn.)\n",
		       srb->state, srb->status, srb->scsi_phase,
		       (acb->active_dcb) ? "" : "not");
	पूर्ण
	dprपूर्णांकkl(KERN_INFO, "dump: SCSI{status=0x%04x fifocnt=0x%02x "
		"signals=0x%02x irqstat=0x%02x sync=0x%02x target=0x%02x "
		"rselid=0x%02x ctr=0x%08x irqen=0x%02x config=0x%04x "
		"config2=0x%02x cmd=0x%02x selto=0x%02x}\n",
		DC395x_पढ़ो16(acb, TRM_S1040_SCSI_STATUS),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_SIGNAL),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_INTSTATUS),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_SYNC),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_TARGETID),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_IDMSG),
		DC395x_पढ़ो32(acb, TRM_S1040_SCSI_COUNTER),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_INTEN),
		DC395x_पढ़ो16(acb, TRM_S1040_SCSI_CONFIG0),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_CONFIG2),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_COMMAND),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_TIMEOUT));
	dprपूर्णांकkl(KERN_INFO, "dump: DMA{cmd=0x%04x fifocnt=0x%02x fstat=0x%02x "
		"irqstat=0x%02x irqen=0x%02x cfg=0x%04x tctr=0x%08x "
		"ctctr=0x%08x addr=0x%08x:0x%08x}\n",
		DC395x_पढ़ो16(acb, TRM_S1040_DMA_COMMAND),
		DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOCNT),
		DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOSTAT),
		DC395x_पढ़ो8(acb, TRM_S1040_DMA_STATUS),
		DC395x_पढ़ो8(acb, TRM_S1040_DMA_INTEN),
		DC395x_पढ़ो16(acb, TRM_S1040_DMA_CONFIG),
		DC395x_पढ़ो32(acb, TRM_S1040_DMA_XCNT),
		DC395x_पढ़ो32(acb, TRM_S1040_DMA_CXCNT),
		DC395x_पढ़ो32(acb, TRM_S1040_DMA_XHIGHADDR),
		DC395x_पढ़ो32(acb, TRM_S1040_DMA_XLOWADDR));
	dprपूर्णांकkl(KERN_INFO, "dump: gen{gctrl=0x%02x gstat=0x%02x gtmr=0x%02x} "
		"pci{status=0x%04x}\n",
		DC395x_पढ़ो8(acb, TRM_S1040_GEN_CONTROL),
		DC395x_पढ़ो8(acb, TRM_S1040_GEN_STATUS),
		DC395x_पढ़ो8(acb, TRM_S1040_GEN_TIMER),
		pstat);
पूर्ण


अटल अंतरभूत व्योम clear_fअगरo(काष्ठा AdapterCtlBlk *acb, अक्षर *txt)
अणु
#अगर debug_enabled(DBG_FIFO)
	u8 lines = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_SIGNAL);
	u8 fअगरocnt = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT);
	अगर (!(fअगरocnt & 0x40))
		dprपूर्णांकkdbg(DBG_FIFO,
			"clear_fifo: (%i bytes) on phase %02x in %s\n",
			fअगरocnt & 0x3f, lines, txt);
#पूर्ण_अगर
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_CLRFIFO);
पूर्ण


अटल व्योम reset_dev_param(काष्ठा AdapterCtlBlk *acb)
अणु
	काष्ठा DeviceCtlBlk *dcb;
	काष्ठा NvRamType *eeprom = &acb->eeprom;
	dprपूर्णांकkdbg(DBG_0, "reset_dev_param: acb=%p\n", acb);

	list_क्रम_each_entry(dcb, &acb->dcb_list, list) अणु
		u8 period_index;

		dcb->sync_mode &= ~(SYNC_NEGO_DONE + WIDE_NEGO_DONE);
		dcb->sync_period = 0;
		dcb->sync_offset = 0;

		dcb->dev_mode = eeprom->target[dcb->target_id].cfg0;
		period_index = eeprom->target[dcb->target_id].period & 0x07;
		dcb->min_nego_period = घड़ी_period[period_index];
		अगर (!(dcb->dev_mode & NTC_DO_WIDE_NEGO)
		    || !(acb->config & HCC_WIDE_CARD))
			dcb->sync_mode &= ~WIDE_NEGO_ENABLE;
	पूर्ण
पूर्ण


/*
 * perक्रमm a hard reset on the SCSI bus
 * @cmd - some command क्रम this host (क्रम fetching hooks)
 * Returns: SUCCESS (0x2002) on success, अन्यथा FAILED (0x2003).
 */
अटल पूर्णांक __dc395x_eh_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा AdapterCtlBlk *acb =
		(काष्ठा AdapterCtlBlk *)cmd->device->host->hostdata;
	dprपूर्णांकkl(KERN_INFO,
		"eh_bus_reset: (0%p) target=<%02i-%i> cmd=%p\n",
		cmd, cmd->device->id, (u8)cmd->device->lun, cmd);

	अगर (समयr_pending(&acb->रुकोing_समयr))
		del_समयr(&acb->रुकोing_समयr);

	/*
	 * disable पूर्णांकerrupt    
	 */
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_INTEN, 0x00);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_INTEN, 0x00);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONTROL, DO_RSTMODULE);
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, DMARESETMODULE);

	reset_scsi_bus(acb);
	udelay(500);

	/* We may be in serious trouble. Wait some seconds */
	acb->last_reset =
	    jअगरfies + 3 * HZ / 2 +
	    HZ * acb->eeprom.delay_समय;

	/*
	 * re-enable पूर्णांकerrupt      
	 */
	/* Clear SCSI FIFO          */
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, CLRXFIFO);
	clear_fअगरo(acb, "eh_bus_reset");
	/* Delete pending IRQ */
	DC395x_पढ़ो8(acb, TRM_S1040_SCSI_INTSTATUS);
	set_basic_config(acb);

	reset_dev_param(acb);
	करोing_srb_करोne(acb, DID_RESET, cmd, 0);
	acb->active_dcb = शून्य;
	acb->acb_flag = 0;	/* RESET_DETECT, RESET_DONE ,RESET_DEV */
	रुकोing_process_next(acb);

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक dc395x_eh_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक rc;

	spin_lock_irq(cmd->device->host->host_lock);
	rc = __dc395x_eh_bus_reset(cmd);
	spin_unlock_irq(cmd->device->host->host_lock);

	वापस rc;
पूर्ण

/*
 * पात an errant SCSI command
 * @cmd - command to be पातed
 * Returns: SUCCESS (0x2002) on success, अन्यथा FAILED (0x2003).
 */
अटल पूर्णांक dc395x_eh_पात(काष्ठा scsi_cmnd *cmd)
अणु
	/*
	 * Look पूर्णांकo our command queues: If it has not been sent alपढ़ोy,
	 * we हटाओ it and वापस success. Otherwise fail.
	 */
	काष्ठा AdapterCtlBlk *acb =
	    (काष्ठा AdapterCtlBlk *)cmd->device->host->hostdata;
	काष्ठा DeviceCtlBlk *dcb;
	काष्ठा ScsiReqBlk *srb;
	dprपूर्णांकkl(KERN_INFO, "eh_abort: (0x%p) target=<%02i-%i> cmd=%p\n",
		cmd, cmd->device->id, (u8)cmd->device->lun, cmd);

	dcb = find_dcb(acb, cmd->device->id, cmd->device->lun);
	अगर (!dcb) अणु
		dprपूर्णांकkl(KERN_DEBUG, "eh_abort: No such device\n");
		वापस FAILED;
	पूर्ण

	srb = find_cmd(cmd, &dcb->srb_रुकोing_list);
	अगर (srb) अणु
		list_del(&srb->list);
		pci_unmap_srb_sense(acb, srb);
		pci_unmap_srb(acb, srb);
		मुक्त_tag(dcb, srb);
		list_add_tail(&srb->list, &acb->srb_मुक्त_list);
		dprपूर्णांकkl(KERN_DEBUG, "eh_abort: Command was waiting\n");
		cmd->result = DID_ABORT << 16;
		वापस SUCCESS;
	पूर्ण
	srb = find_cmd(cmd, &dcb->srb_going_list);
	अगर (srb) अणु
		dprपूर्णांकkl(KERN_DEBUG, "eh_abort: Command in progress\n");
		/* XXX: Should पात the command here */
	पूर्ण अन्यथा अणु
		dprपूर्णांकkl(KERN_DEBUG, "eh_abort: Command not found\n");
	पूर्ण
	वापस FAILED;
पूर्ण


/* SDTR */
अटल व्योम build_sdtr(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb)
अणु
	u8 *ptr = srb->msgout_buf + srb->msg_count;
	अगर (srb->msg_count > 1) अणु
		dprपूर्णांकkl(KERN_INFO,
			"build_sdtr: msgout_buf BUSY (%i: %02x %02x)\n",
			srb->msg_count, srb->msgout_buf[0],
			srb->msgout_buf[1]);
		वापस;
	पूर्ण
	अगर (!(dcb->dev_mode & NTC_DO_SYNC_NEGO)) अणु
		dcb->sync_offset = 0;
		dcb->min_nego_period = 200 >> 2;
	पूर्ण अन्यथा अगर (dcb->sync_offset == 0)
		dcb->sync_offset = SYNC_NEGO_OFFSET;

	srb->msg_count += spi_populate_sync_msg(ptr, dcb->min_nego_period,
						dcb->sync_offset);
	srb->state |= SRB_DO_SYNC_NEGO;
पूर्ण


/* WDTR */
अटल व्योम build_wdtr(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb)
अणु
	u8 wide = ((dcb->dev_mode & NTC_DO_WIDE_NEGO) &
		   (acb->config & HCC_WIDE_CARD)) ? 1 : 0;
	u8 *ptr = srb->msgout_buf + srb->msg_count;
	अगर (srb->msg_count > 1) अणु
		dprपूर्णांकkl(KERN_INFO,
			"build_wdtr: msgout_buf BUSY (%i: %02x %02x)\n",
			srb->msg_count, srb->msgout_buf[0],
			srb->msgout_buf[1]);
		वापस;
	पूर्ण
	srb->msg_count += spi_populate_width_msg(ptr, wide);
	srb->state |= SRB_DO_WIDE_NEGO;
पूर्ण


#अगर 0
/* Timer to work around chip flaw: When selecting and the bus is 
 * busy, we someबार miss a Selection समयout IRQ */
व्योम selection_समयout_missed(अचिन्हित दीर्घ ptr);
/* Sets the समयr to wake us up */
अटल व्योम selto_समयr(काष्ठा AdapterCtlBlk *acb)
अणु
	अगर (समयr_pending(&acb->selto_समयr))
		वापस;
	acb->selto_समयr.function = selection_समयout_missed;
	acb->selto_समयr.data = (अचिन्हित दीर्घ) acb;
	अगर (समय_beक्रमe
	    (jअगरfies + HZ, acb->last_reset + HZ / 2))
		acb->selto_समयr.expires =
		    acb->last_reset + HZ / 2 + 1;
	अन्यथा
		acb->selto_समयr.expires = jअगरfies + HZ + 1;
	add_समयr(&acb->selto_समयr);
पूर्ण


व्योम selection_समयout_missed(अचिन्हित दीर्घ ptr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा AdapterCtlBlk *acb = (काष्ठा AdapterCtlBlk *)ptr;
	काष्ठा ScsiReqBlk *srb;
	dprपूर्णांकkl(KERN_DEBUG, "Chip forgot to produce SelTO IRQ!\n");
	अगर (!acb->active_dcb || !acb->active_dcb->active_srb) अणु
		dprपूर्णांकkl(KERN_DEBUG, "... but no cmd pending? Oops!\n");
		वापस;
	पूर्ण
	DC395x_LOCK_IO(acb->scsi_host, flags);
	srb = acb->active_dcb->active_srb;
	disconnect(acb);
	DC395x_UNLOCK_IO(acb->scsi_host, flags);
पूर्ण
#पूर्ण_अगर


अटल u8 start_scsi(काष्ठा AdapterCtlBlk* acb, काष्ठा DeviceCtlBlk* dcb,
		काष्ठा ScsiReqBlk* srb)
अणु
	u16 __maybe_unused s_stat2, वापस_code;
	u8 s_stat, scsicommand, i, identअगरy_message;
	u8 *ptr;
	dprपूर्णांकkdbg(DBG_0, "start_scsi: (0x%p) <%02i-%i> srb=%p\n",
		dcb->target_id, dcb->target_lun, srb);

	srb->tag_number = TAG_NONE;	/* acb->tag_max_num: had error पढ़ो in eeprom */

	s_stat = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_SIGNAL);
	s_stat2 = 0;
	s_stat2 = DC395x_पढ़ो16(acb, TRM_S1040_SCSI_STATUS);
#अगर 1
	अगर (s_stat & 0x20 /* s_stat2 & 0x02000 */ ) अणु
		dprपूर्णांकkdbg(DBG_KG, "start_scsi: (0x%p) BUSY %02x %04x\n",
			s_stat, s_stat2);
		/*
		 * Try anyway?
		 *
		 * We could, BUT: Someबार the TRM_S1040 misses to produce a Selection
		 * Timeout, a Disconnect or a Reselection IRQ, so we would be screwed!
		 * (This is likely to be a bug in the hardware. Obviously, most people
		 *  only have one initiator per SCSI bus.)
		 * Instead let this fail and have the समयr make sure the command is 
		 * tried again after a लघु समय
		 */
		/*selto_समयr (acb); */
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	अगर (acb->active_dcb) अणु
		dprपूर्णांकkl(KERN_DEBUG, "start_scsi: (0x%p) Attempt to start a"
			"command while another command (0x%p) is active.",
			srb->cmd,
			acb->active_dcb->active_srb ?
			    acb->active_dcb->active_srb->cmd : 0);
		वापस 1;
	पूर्ण
	अगर (DC395x_पढ़ो16(acb, TRM_S1040_SCSI_STATUS) & SCSIINTERRUPT) अणु
		dprपूर्णांकkdbg(DBG_KG, "start_scsi: (0x%p) Failed (busy)\n", srb->cmd);
		वापस 1;
	पूर्ण
	/* Allow starting of SCSI commands half a second beक्रमe we allow the mid-level
	 * to queue them again after a reset */
	अगर (समय_beक्रमe(jअगरfies, acb->last_reset - HZ / 2)) अणु
		dprपूर्णांकkdbg(DBG_KG, "start_scsi: Refuse cmds (reset wait)\n");
		वापस 1;
	पूर्ण

	/* Flush FIFO */
	clear_fअगरo(acb, "start_scsi");
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_HOSTID, acb->scsi_host->this_id);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_TARGETID, dcb->target_id);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_SYNC, dcb->sync_period);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_OFFSET, dcb->sync_offset);
	srb->scsi_phase = PH_BUS_FREE;	/* initial phase */

	identअगरy_message = dcb->identअगरy_msg;
	/*DC395x_TRM_ग_लिखो8(TRM_S1040_SCSI_IDMSG, identअगरy_message); */
	/* Don't allow disconnection क्रम AUTO_REQSENSE: Cont.All.Cond.! */
	अगर (srb->flag & AUTO_REQSENSE)
		identअगरy_message &= 0xBF;

	अगर (((srb->cmd->cmnd[0] == INQUIRY)
	     || (srb->cmd->cmnd[0] == REQUEST_SENSE)
	     || (srb->flag & AUTO_REQSENSE))
	    && (((dcb->sync_mode & WIDE_NEGO_ENABLE)
		 && !(dcb->sync_mode & WIDE_NEGO_DONE))
		|| ((dcb->sync_mode & SYNC_NEGO_ENABLE)
		    && !(dcb->sync_mode & SYNC_NEGO_DONE)))
	    && (dcb->target_lun == 0)) अणु
		srb->msgout_buf[0] = identअगरy_message;
		srb->msg_count = 1;
		scsicommand = SCMD_SEL_ATNSTOP;
		srb->state = SRB_MSGOUT;
#अगर_अघोषित SYNC_FIRST
		अगर (dcb->sync_mode & WIDE_NEGO_ENABLE
		    && dcb->inquiry7 & SCSI_INQ_WBUS16) अणु
			build_wdtr(acb, dcb, srb);
			जाओ no_cmd;
		पूर्ण
#पूर्ण_अगर
		अगर (dcb->sync_mode & SYNC_NEGO_ENABLE
		    && dcb->inquiry7 & SCSI_INQ_SYNC) अणु
			build_sdtr(acb, dcb, srb);
			जाओ no_cmd;
		पूर्ण
		अगर (dcb->sync_mode & WIDE_NEGO_ENABLE
		    && dcb->inquiry7 & SCSI_INQ_WBUS16) अणु
			build_wdtr(acb, dcb, srb);
			जाओ no_cmd;
		पूर्ण
		srb->msg_count = 0;
	पूर्ण
	/* Send identअगरy message */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, identअगरy_message);

	scsicommand = SCMD_SEL_ATN;
	srb->state = SRB_START_;
#अगर_अघोषित DC395x_NO_TAGQ
	अगर ((dcb->sync_mode & EN_TAG_QUEUEING)
	    && (identअगरy_message & 0xC0)) अणु
		/* Send Tag message */
		u32 tag_mask = 1;
		u8 tag_number = 0;
		जबतक (tag_mask & dcb->tag_mask
		       && tag_number < dcb->max_command) अणु
			tag_mask = tag_mask << 1;
			tag_number++;
		पूर्ण
		अगर (tag_number >= dcb->max_command) अणु
			dprपूर्णांकkl(KERN_WARNING, "start_scsi: (0x%p) "
				"Out of tags target=<%02i-%i>)\n",
				srb->cmd, srb->cmd->device->id,
				(u8)srb->cmd->device->lun);
			srb->state = SRB_READY;
			DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL,
				       DO_HWRESELECT);
			वापस 1;
		पूर्ण
		/* Send Tag id */
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, SIMPLE_QUEUE_TAG);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, tag_number);
		dcb->tag_mask |= tag_mask;
		srb->tag_number = tag_number;
		scsicommand = SCMD_SEL_ATN3;
		srb->state = SRB_START_;
	पूर्ण
#पूर्ण_अगर
/*polling:*/
	/* Send CDB ..command block ......... */
	dprपूर्णांकkdbg(DBG_KG, "start_scsi: (0x%p) <%02i-%i> cmnd=0x%02x tag=%i\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun,
		srb->cmd->cmnd[0], srb->tag_number);
	अगर (srb->flag & AUTO_REQSENSE) अणु
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, REQUEST_SENSE);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, (dcb->target_lun << 5));
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 0);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 0);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, SCSI_SENSE_BUFFERSIZE);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 0);
	पूर्ण अन्यथा अणु
		ptr = (u8 *)srb->cmd->cmnd;
		क्रम (i = 0; i < srb->cmd->cmd_len; i++)
			DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, *ptr++);
	पूर्ण
      no_cmd:
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL,
		       DO_HWRESELECT | DO_DATALATCH);
	अगर (DC395x_पढ़ो16(acb, TRM_S1040_SCSI_STATUS) & SCSIINTERRUPT) अणु
		/* 
		 * If start_scsi वापस 1:
		 * we caught an पूर्णांकerrupt (must be reset or reselection ... )
		 * : Let's process it first!
		 */
		dprपूर्णांकkdbg(DBG_0, "start_scsi: (0x%p) <%02i-%i> Failed - busy\n",
			srb->cmd, dcb->target_id, dcb->target_lun);
		srb->state = SRB_READY;
		मुक्त_tag(dcb, srb);
		srb->msg_count = 0;
		वापस_code = 1;
		/* This IRQ should NOT get lost, as we did not acknowledge it */
	पूर्ण अन्यथा अणु
		/* 
		 * If start_scsi वापसs 0:
		 * we know that the SCSI processor is मुक्त
		 */
		srb->scsi_phase = PH_BUS_FREE;	/* initial phase */
		dcb->active_srb = srb;
		acb->active_dcb = dcb;
		वापस_code = 0;
		/* it's important क्रम atn stop */
		DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL,
			       DO_DATALATCH | DO_HWRESELECT);
		/* SCSI command */
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, scsicommand);
	पूर्ण
	वापस वापस_code;
पूर्ण


#घोषणा DC395x_ENABLE_MSGOUT \
 DC395x_ग_लिखो16 (acb, TRM_S1040_SCSI_CONTROL, DO_SETATN); \
 srb->state |= SRB_MSGOUT


/* पात command */
अटल अंतरभूत व्योम enable_msgout_पात(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb)
अणु
	srb->msgout_buf[0] = ABORT;
	srb->msg_count = 1;
	DC395x_ENABLE_MSGOUT;
	srb->state &= ~SRB_MSGIN;
	srb->state |= SRB_MSGOUT;
पूर्ण


/**
 * dc395x_handle_पूर्णांकerrupt - Handle an पूर्णांकerrupt that has been confirmed to
 *                           have been triggered क्रम this card.
 *
 * @acb:	 a poपूर्णांकer to the adpter control block
 * @scsi_status: the status वापस when we checked the card
 **/
अटल व्योम dc395x_handle_पूर्णांकerrupt(काष्ठा AdapterCtlBlk *acb,
		u16 scsi_status)
अणु
	काष्ठा DeviceCtlBlk *dcb;
	काष्ठा ScsiReqBlk *srb;
	u16 phase;
	u8 scsi_पूर्णांकstatus;
	अचिन्हित दीर्घ flags;
	व्योम (*dc395x_statev)(काष्ठा AdapterCtlBlk *, काष्ठा ScsiReqBlk *, 
			      u16 *);

	DC395x_LOCK_IO(acb->scsi_host, flags);

	/* This acknowledges the IRQ */
	scsi_पूर्णांकstatus = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_INTSTATUS);
	अगर ((scsi_status & 0x2007) == 0x2002)
		dprपूर्णांकkl(KERN_DEBUG,
			"COP after COP completed? %04x\n", scsi_status);
	अगर (debug_enabled(DBG_KG)) अणु
		अगर (scsi_पूर्णांकstatus & INT_SELTIMEOUT)
			dprपूर्णांकkdbg(DBG_KG, "handle_interrupt: Selection timeout\n");
	पूर्ण
	/*dprपूर्णांकkl(KERN_DEBUG, "handle_interrupt: intstatus = 0x%02x ", scsi_पूर्णांकstatus); */

	अगर (समयr_pending(&acb->selto_समयr))
		del_समयr(&acb->selto_समयr);

	अगर (scsi_पूर्णांकstatus & (INT_SELTIMEOUT | INT_DISCONNECT)) अणु
		disconnect(acb);	/* bus मुक्त पूर्णांकerrupt  */
		जाओ out_unlock;
	पूर्ण
	अगर (scsi_पूर्णांकstatus & INT_RESELECTED) अणु
		reselect(acb);
		जाओ out_unlock;
	पूर्ण
	अगर (scsi_पूर्णांकstatus & INT_SELECT) अणु
		dprपूर्णांकkl(KERN_INFO, "Host does not support target mode!\n");
		जाओ out_unlock;
	पूर्ण
	अगर (scsi_पूर्णांकstatus & INT_SCSIRESET) अणु
		scsi_reset_detect(acb);
		जाओ out_unlock;
	पूर्ण
	अगर (scsi_पूर्णांकstatus & (INT_BUSSERVICE | INT_CMDDONE)) अणु
		dcb = acb->active_dcb;
		अगर (!dcb) अणु
			dprपूर्णांकkl(KERN_DEBUG,
				"Oops: BusService (%04x %02x) w/o ActiveDCB!\n",
				scsi_status, scsi_पूर्णांकstatus);
			जाओ out_unlock;
		पूर्ण
		srb = dcb->active_srb;
		अगर (dcb->flag & ABORT_DEV_) अणु
			dprपूर्णांकkdbg(DBG_0, "MsgOut Abort Device.....\n");
			enable_msgout_पात(acb, srb);
		पूर्ण

		/* software sequential machine */
		phase = (u16)srb->scsi_phase;

		/* 
		 * 62037 or 62137
		 * call  dc395x_scsi_phase0[]... "phase entry"
		 * handle every phase beक्रमe start transfer
		 */
		/* data_out_phase0,	phase:0 */
		/* data_in_phase0,	phase:1 */
		/* command_phase0,	phase:2 */
		/* status_phase0,	phase:3 */
		/* nop0,		phase:4 PH_BUS_FREE .. initial phase */
		/* nop0,		phase:5 PH_BUS_FREE .. initial phase */
		/* msgout_phase0,	phase:6 */
		/* msgin_phase0,	phase:7 */
		dc395x_statev = dc395x_scsi_phase0[phase];
		dc395x_statev(acb, srb, &scsi_status);

		/* 
		 * अगर there were any exception occurred scsi_status
		 * will be modअगरy to bus मुक्त phase new scsi_status
		 * transfer out from ... previous dc395x_statev
		 */
		srb->scsi_phase = scsi_status & PHASEMASK;
		phase = (u16)scsi_status & PHASEMASK;

		/* 
		 * call  dc395x_scsi_phase1[]... "phase entry" handle
		 * every phase to करो transfer
		 */
		/* data_out_phase1,	phase:0 */
		/* data_in_phase1,	phase:1 */
		/* command_phase1,	phase:2 */
		/* status_phase1,	phase:3 */
		/* nop1,		phase:4 PH_BUS_FREE .. initial phase */
		/* nop1,		phase:5 PH_BUS_FREE .. initial phase */
		/* msgout_phase1,	phase:6 */
		/* msgin_phase1,	phase:7 */
		dc395x_statev = dc395x_scsi_phase1[phase];
		dc395x_statev(acb, srb, &scsi_status);
	पूर्ण
      out_unlock:
	DC395x_UNLOCK_IO(acb->scsi_host, flags);
पूर्ण


अटल irqवापस_t dc395x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा AdapterCtlBlk *acb = dev_id;
	u16 scsi_status;
	u8 dma_status;
	irqवापस_t handled = IRQ_NONE;

	/*
	 * Check क्रम pending पूर्णांकerrupt
	 */
	scsi_status = DC395x_पढ़ो16(acb, TRM_S1040_SCSI_STATUS);
	dma_status = DC395x_पढ़ो8(acb, TRM_S1040_DMA_STATUS);
	अगर (scsi_status & SCSIINTERRUPT) अणु
		/* पूर्णांकerrupt pending - let's process it! */
		dc395x_handle_पूर्णांकerrupt(acb, scsi_status);
		handled = IRQ_HANDLED;
	पूर्ण
	अन्यथा अगर (dma_status & 0x20) अणु
		/* Error from the DMA engine */
		dprपूर्णांकkl(KERN_INFO, "Interrupt from DMA engine: 0x%02x!\n", dma_status);
#अगर 0
		dprपूर्णांकkl(KERN_INFO, "This means DMA error! Try to handle ...\n");
		अगर (acb->active_dcb) अणु
			acb->active_dcb-> flag |= ABORT_DEV_;
			अगर (acb->active_dcb->active_srb)
				enable_msgout_पात(acb, acb->active_dcb->active_srb);
		पूर्ण
		DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, ABORTXFER | CLRXFIFO);
#अन्यथा
		dprपूर्णांकkl(KERN_INFO, "Ignoring DMA error (probably a bad thing) ...\n");
		acb = शून्य;
#पूर्ण_अगर
		handled = IRQ_HANDLED;
	पूर्ण

	वापस handled;
पूर्ण


अटल व्योम msgout_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	dprपूर्णांकkdbg(DBG_0, "msgout_phase0: (0x%p)\n", srb->cmd);
	अगर (srb->state & (SRB_UNEXPECT_RESEL + SRB_ABORT_SENT))
		*pscsi_status = PH_BUS_FREE;	/*.. initial phase */

	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
	srb->state &= ~SRB_MSGOUT;
पूर्ण


अटल व्योम msgout_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	u16 i;
	u8 *ptr;
	dprपूर्णांकkdbg(DBG_0, "msgout_phase1: (0x%p)\n", srb->cmd);

	clear_fअगरo(acb, "msgout_phase1");
	अगर (!(srb->state & SRB_MSGOUT)) अणु
		srb->state |= SRB_MSGOUT;
		dprपूर्णांकkl(KERN_DEBUG,
			"msgout_phase1: (0x%p) Phase unexpected\n",
			srb->cmd);	/* So what ? */
	पूर्ण
	अगर (!srb->msg_count) अणु
		dprपूर्णांकkdbg(DBG_0, "msgout_phase1: (0x%p) NOP msg\n",
			srb->cmd);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, NOP);
		DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);
		/* it's important क्रम atn stop */
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_OUT);
		वापस;
	पूर्ण
	ptr = (u8 *)srb->msgout_buf;
	क्रम (i = 0; i < srb->msg_count; i++)
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, *ptr++);
	srb->msg_count = 0;
	अगर (srb->msgout_buf[0] == ABORT_TASK_SET)
		srb->state = SRB_ABORT_SENT;

	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_OUT);
पूर्ण


अटल व्योम command_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	dprपूर्णांकkdbg(DBG_0, "command_phase0: (0x%p)\n", srb->cmd);
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);
पूर्ण


अटल व्योम command_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	काष्ठा DeviceCtlBlk *dcb;
	u8 *ptr;
	u16 i;
	dprपूर्णांकkdbg(DBG_0, "command_phase1: (0x%p)\n", srb->cmd);

	clear_fअगरo(acb, "command_phase1");
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_CLRATN);
	अगर (!(srb->flag & AUTO_REQSENSE)) अणु
		ptr = (u8 *)srb->cmd->cmnd;
		क्रम (i = 0; i < srb->cmd->cmd_len; i++) अणु
			DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, *ptr);
			ptr++;
		पूर्ण
	पूर्ण अन्यथा अणु
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, REQUEST_SENSE);
		dcb = acb->active_dcb;
		/* target id */
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, (dcb->target_lun << 5));
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 0);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 0);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, SCSI_SENSE_BUFFERSIZE);
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 0);
	पूर्ण
	srb->state |= SRB_COMMAND;
	/* it's important क्रम atn stop */
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);
	/* SCSI command */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_OUT);
पूर्ण


/*
 * Verअगरy that the reमुख्यing space in the hw sg lists is the same as
 * the count of reमुख्यing bytes in srb->total_xfer_length
 */
अटल व्योम sg_verअगरy_length(काष्ठा ScsiReqBlk *srb)
अणु
	अगर (debug_enabled(DBG_SG)) अणु
		अचिन्हित len = 0;
		अचिन्हित idx = srb->sg_index;
		काष्ठा SGentry *psge = srb->segment_x + idx;
		क्रम (; idx < srb->sg_count; psge++, idx++)
			len += psge->length;
		अगर (len != srb->total_xfer_length)
			dprपूर्णांकkdbg(DBG_SG,
			       "Inconsistent SRB S/G lengths (Tot=%i, Count=%i) !!\n",
			       srb->total_xfer_length, len);
	पूर्ण			       
पूर्ण


/*
 * Compute the next Scatter Gather list index and adjust its length
 * and address अगर necessary
 */
अटल व्योम sg_update_list(काष्ठा ScsiReqBlk *srb, u32 left)
अणु
	u8 idx;
	u32 xferred = srb->total_xfer_length - left; /* bytes transferred */
	काष्ठा SGentry *psge = srb->segment_x + srb->sg_index;

	dprपूर्णांकkdbg(DBG_0,
		"sg_update_list: Transferred %i of %i bytes, %i remain\n",
		xferred, srb->total_xfer_length, left);
	अगर (xferred == 0) अणु
		/* nothing to update since we did not transfer any data */
		वापस;
	पूर्ण

	sg_verअगरy_length(srb);
	srb->total_xfer_length = left;	/* update reमुख्यing count */
	क्रम (idx = srb->sg_index; idx < srb->sg_count; idx++) अणु
		अगर (xferred >= psge->length) अणु
			/* Complete SG entries करोne */
			xferred -= psge->length;
		पूर्ण अन्यथा अणु
			/* Partial SG entry करोne */
			dma_sync_single_क्रम_cpu(&srb->dcb->acb->dev->dev,
					srb->sg_bus_addr, SEGMENTX_LEN,
					DMA_TO_DEVICE);
			psge->length -= xferred;
			psge->address += xferred;
			srb->sg_index = idx;
			dma_sync_single_क्रम_device(&srb->dcb->acb->dev->dev,
					srb->sg_bus_addr, SEGMENTX_LEN,
					DMA_TO_DEVICE);
			अवरोध;
		पूर्ण
		psge++;
	पूर्ण
	sg_verअगरy_length(srb);
पूर्ण


/*
 * We have transferred a single byte (PIO mode?) and need to update
 * the count of bytes reमुख्यing (total_xfer_length) and update the sg
 * entry to either poपूर्णांक to next byte in the current sg entry, or of
 * alपढ़ोy at the end to poपूर्णांक to the start of the next sg entry
 */
अटल व्योम sg_subtract_one(काष्ठा ScsiReqBlk *srb)
अणु
	sg_update_list(srb, srb->total_xfer_length - 1);
पूर्ण


/* 
 * cleanup_after_transfer
 * 
 * Makes sure, DMA and SCSI engine are empty, after the transfer has finished
 * KG: Currently called from  StatusPhase1 ()
 * Should probably also be called from other places
 * Best might be to call it in DataXXPhase0, अगर new phase will dअगरfer 
 */
अटल व्योम cleanup_after_transfer(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb)
अणु
	/*DC395x_ग_लिखो8 (TRM_S1040_DMA_STATUS, FORCEDMACOMP); */
	अगर (DC395x_पढ़ो16(acb, TRM_S1040_DMA_COMMAND) & 0x0001) अणु	/* पढ़ो */
		अगर (!(DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT) & 0x40))
			clear_fअगरo(acb, "cleanup/in");
		अगर (!(DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOSTAT) & 0x80))
			DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, CLRXFIFO);
	पूर्ण अन्यथा अणु		/* ग_लिखो */
		अगर (!(DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOSTAT) & 0x80))
			DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, CLRXFIFO);
		अगर (!(DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT) & 0x40))
			clear_fअगरo(acb, "cleanup/out");
	पूर्ण
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);
पूर्ण


/*
 * Those no of bytes will be transferred w/ PIO through the SCSI FIFO
 * Seems to be needed क्रम unknown reasons; could be a hardware bug :-(
 */
#घोषणा DC395x_LASTPIO 4


अटल व्योम data_out_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	काष्ठा DeviceCtlBlk *dcb = srb->dcb;
	u16 scsi_status = *pscsi_status;
	u32 d_left_counter = 0;
	dprपूर्णांकkdbg(DBG_0, "data_out_phase0: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun);

	/*
	 * KG: We need to drain the buffers beक्रमe we draw any conclusions!
	 * This means telling the DMA to push the rest पूर्णांकo SCSI, telling
	 * SCSI to push the rest to the bus.
	 * However, the device might have been the one to stop us (phase
	 * change), and the data in transit just needs to be accounted so
	 * it can be retransmitted.)
	 */
	/* 
	 * KG: Stop DMA engine pushing more data पूर्णांकo the SCSI FIFO
	 * If we need more data, the DMA SG list will be freshly set up, anyway
	 */
	dprपूर्णांकkdbg(DBG_PIO, "data_out_phase0: "
		"DMA{fifocnt=0x%02x fifostat=0x%02x} "
		"SCSI{fifocnt=0x%02x cnt=0x%06x status=0x%04x} total=0x%06x\n",
		DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOCNT),
		DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOSTAT),
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT),
		DC395x_पढ़ो32(acb, TRM_S1040_SCSI_COUNTER), scsi_status,
		srb->total_xfer_length);
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, STOPDMAXFER | CLRXFIFO);

	अगर (!(srb->state & SRB_XFERPAD)) अणु
		अगर (scsi_status & PARITYERROR)
			srb->status |= PARITY_ERROR;

		/*
		 * KG: Right, we can't just rely on the SCSI_COUNTER, because this
		 * is the no of bytes it got from the DMA engine not the no it 
		 * transferred successfully to the device. (And the dअगरference could
		 * be as much as the FIFO size, I guess ...)
		 */
		अगर (!(scsi_status & SCSIXFERDONE)) अणु
			/*
			 * when data transfer from DMA FIFO to SCSI FIFO
			 * अगर there was some data left in SCSI FIFO
			 */
			d_left_counter =
			    (u32)(DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT) &
				  0x1F);
			अगर (dcb->sync_period & WIDE_SYNC)
				d_left_counter <<= 1;

			dprपूर्णांकkdbg(DBG_KG, "data_out_phase0: FIFO contains %i %s\n"
				"SCSI{fifocnt=0x%02x cnt=0x%08x} "
				"DMA{fifocnt=0x%04x cnt=0x%02x ctr=0x%08x}\n",
				DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT),
				(dcb->sync_period & WIDE_SYNC) ? "words" : "bytes",
				DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT),
				DC395x_पढ़ो32(acb, TRM_S1040_SCSI_COUNTER),
				DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOCNT),
				DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOSTAT),
				DC395x_पढ़ो32(acb, TRM_S1040_DMA_CXCNT));
		पूर्ण
		/*
		 * calculate all the residue data that not yet tranfered
		 * SCSI transfer counter + left in SCSI FIFO data
		 *
		 * .....TRM_S1040_SCSI_COUNTER (24bits)
		 * The counter always decrement by one क्रम every SCSI byte transfer.
		 * .....TRM_S1040_SCSI_FIFOCNT ( 5bits)
		 * The counter is SCSI FIFO offset counter (in units of bytes or! words)
		 */
		अगर (srb->total_xfer_length > DC395x_LASTPIO)
			d_left_counter +=
			    DC395x_पढ़ो32(acb, TRM_S1040_SCSI_COUNTER);

		/* Is this a good idea? */
		/*clear_fअगरo(acb, "DOP1"); */
		/* KG: What is this supposed to be useful क्रम? WIDE padding stuff? */
		अगर (d_left_counter == 1 && dcb->sync_period & WIDE_SYNC
		    && scsi_bufflen(srb->cmd) % 2) अणु
			d_left_counter = 0;
			dprपूर्णांकkl(KERN_INFO,
				"data_out_phase0: Discard 1 byte (0x%02x)\n",
				scsi_status);
		पूर्ण
		/*
		 * KG: Oops again. Same thinko as above: The SCSI might have been
		 * faster than the DMA engine, so that it ran out of data.
		 * In that हाल, we have to करो just nothing! 
		 * But: Why the पूर्णांकerrupt: No phase change. No XFERCNT_2_ZERO. Or?
		 */
		/*
		 * KG: This is nonsense: We have been WRITING data to the bus
		 * If the SCSI engine has no bytes left, how should the DMA engine?
		 */
		अगर (d_left_counter == 0) अणु
			srb->total_xfer_length = 0;
		पूर्ण अन्यथा अणु
			/*
			 * अगर transfer not yet complete
			 * there were some data residue in SCSI FIFO or
			 * SCSI transfer counter not empty
			 */
			दीर्घ oldxferred =
			    srb->total_xfer_length - d_left_counter;
			स्थिर पूर्णांक dअगरf =
			    (dcb->sync_period & WIDE_SYNC) ? 2 : 1;
			sg_update_list(srb, d_left_counter);
			/* KG: Most ugly hack! Apparently, this works around a chip bug */
			अगर ((srb->segment_x[srb->sg_index].length ==
			     dअगरf && scsi_sg_count(srb->cmd))
			    || ((oldxferred & ~PAGE_MASK) ==
				(PAGE_SIZE - dअगरf))
			    ) अणु
				dprपूर्णांकkl(KERN_INFO, "data_out_phase0: "
					"Work around chip bug (%i)?\n", dअगरf);
				d_left_counter =
				    srb->total_xfer_length - dअगरf;
				sg_update_list(srb, d_left_counter);
				/*srb->total_xfer_length -= dअगरf; */
				/*srb->virt_addr += dअगरf; */
				/*अगर (srb->cmd->use_sg) */
				/*      srb->sg_index++; */
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((*pscsi_status & PHASEMASK) != PH_DATA_OUT) अणु
		cleanup_after_transfer(acb, srb);
	पूर्ण
पूर्ण


अटल व्योम data_out_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	dprपूर्णांकkdbg(DBG_0, "data_out_phase1: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun);
	clear_fअगरo(acb, "data_out_phase1");
	/* करो prepare beक्रमe transfer when data out phase */
	data_io_transfer(acb, srb, XFERDATAOUT);
पूर्ण

अटल व्योम data_in_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	u16 scsi_status = *pscsi_status;

	dprपूर्णांकkdbg(DBG_0, "data_in_phase0: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun);

	/*
	 * KG: DataIn is much more tricky than DataOut. When the device is finished
	 * and चयनes to another phase, the SCSI engine should be finished too.
	 * But: There might still be bytes left in its FIFO to be fetched by the DMA
	 * engine and transferred to memory.
	 * We should रुको क्रम the FIFOs to be emptied by that (is there any way to 
	 * enक्रमce this?) and then stop the DMA engine, because it might think, that
	 * there are more bytes to follow. Yes, the device might disconnect prior to
	 * having all bytes transferred! 
	 * Also we should make sure that all data from the DMA engine buffer's really
	 * made its way to the प्रणाली memory! Some करोcumentation on this would not
	 * seem to be a bad idea, actually.
	 */
	अगर (!(srb->state & SRB_XFERPAD)) अणु
		u32 d_left_counter;
		अचिन्हित पूर्णांक sc, fc;

		अगर (scsi_status & PARITYERROR) अणु
			dprपूर्णांकkl(KERN_INFO, "data_in_phase0: (0x%p) "
				"Parity Error\n", srb->cmd);
			srb->status |= PARITY_ERROR;
		पूर्ण
		/*
		 * KG: We should रुको क्रम the DMA FIFO to be empty ...
		 * but: it would be better to रुको first क्रम the SCSI FIFO and then the
		 * the DMA FIFO to become empty? How करो we know, that the device not alपढ़ोy
		 * sent data to the FIFO in a MsgIn phase, eg.?
		 */
		अगर (!(DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOSTAT) & 0x80)) अणु
#अगर 0
			पूर्णांक ctr = 6000000;
			dprपूर्णांकkl(KERN_DEBUG,
				"DIP0: Wait for DMA FIFO to flush ...\n");
			/*DC395x_ग_लिखो8  (TRM_S1040_DMA_CONTROL, STOPDMAXFER); */
			/*DC395x_ग_लिखो32 (TRM_S1040_SCSI_COUNTER, 7); */
			/*DC395x_ग_लिखो8  (TRM_S1040_SCSI_COMMAND, SCMD_DMA_IN); */
			जबतक (!
			       (DC395x_पढ़ो16(acb, TRM_S1040_DMA_FIFOSTAT) &
				0x80) && --ctr);
			अगर (ctr < 6000000 - 1)
				dprपूर्णांकkl(KERN_DEBUG
				       "DIP0: Had to wait for DMA ...\n");
			अगर (!ctr)
				dprपूर्णांकkl(KERN_ERR,
				       "Deadlock in DIP0 waiting for DMA FIFO empty!!\n");
			/*DC395x_ग_लिखो32 (TRM_S1040_SCSI_COUNTER, 0); */
#पूर्ण_अगर
			dprपूर्णांकkdbg(DBG_KG, "data_in_phase0: "
				"DMA{fifocnt=0x%02x fifostat=0x%02x}\n",
				DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOCNT),
				DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOSTAT));
		पूर्ण
		/* Now: Check reमुख्यig data: The SCSI counters should tell us ... */
		sc = DC395x_पढ़ो32(acb, TRM_S1040_SCSI_COUNTER);
		fc = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT);
		d_left_counter = sc + ((fc & 0x1f)
		       << ((srb->dcb->sync_period & WIDE_SYNC) ? 1 :
			   0));
		dprपूर्णांकkdbg(DBG_KG, "data_in_phase0: "
			"SCSI{fifocnt=0x%02x%s ctr=0x%08x} "
			"DMA{fifocnt=0x%02x fifostat=0x%02x ctr=0x%08x} "
			"Remain{totxfer=%i scsi_fifo+ctr=%i}\n",
			fc,
			(srb->dcb->sync_period & WIDE_SYNC) ? "words" : "bytes",
			sc,
			fc,
			DC395x_पढ़ो8(acb, TRM_S1040_DMA_FIFOSTAT),
			DC395x_पढ़ो32(acb, TRM_S1040_DMA_CXCNT),
			srb->total_xfer_length, d_left_counter);
#अगर DC395x_LASTPIO
		/* KG: Less than or equal to 4 bytes can not be transferred via DMA, it seems. */
		अगर (d_left_counter
		    && srb->total_xfer_length <= DC395x_LASTPIO) अणु
			माप_प्रकार left_io = srb->total_xfer_length;

			/*u32 addr = (srb->segment_x[srb->sg_index].address); */
			/*sg_update_list (srb, d_left_counter); */
			dprपूर्णांकkdbg(DBG_PIO, "data_in_phase0: PIO (%i %s) "
				   "for remaining %i bytes:",
				fc & 0x1f,
				(srb->dcb->sync_period & WIDE_SYNC) ?
				    "words" : "bytes",
				srb->total_xfer_length);
			अगर (srb->dcb->sync_period & WIDE_SYNC)
				DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONFIG2,
					      CFG2_WIDEFIFO);
			जबतक (left_io) अणु
				अचिन्हित अक्षर *virt, *base = शून्य;
				अचिन्हित दीर्घ flags = 0;
				माप_प्रकार len = left_io;
				माप_प्रकार offset = srb->request_length - left_io;

				local_irq_save(flags);
				/* Assumption: it's inside one page as it's at most 4 bytes and
				   I just assume it's on a 4-byte boundary */
				base = scsi_kmap_atomic_sg(scsi_sglist(srb->cmd),
							   srb->sg_count, &offset, &len);
				virt = base + offset;

				left_io -= len;

				जबतक (len) अणु
					u8 byte;
					byte = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFO);
					*virt++ = byte;

					अगर (debug_enabled(DBG_PIO))
						prपूर्णांकk(" %02x", byte);

					d_left_counter--;
					sg_subtract_one(srb);

					len--;

					fc = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT);

					अगर (fc == 0x40) अणु
						left_io = 0;
						अवरोध;
					पूर्ण
				पूर्ण

				WARN_ON((fc != 0x40) == !d_left_counter);

				अगर (fc == 0x40 && (srb->dcb->sync_period & WIDE_SYNC)) अणु
					/* Read the last byte ... */
					अगर (srb->total_xfer_length > 0) अणु
						u8 byte = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFO);

						*virt++ = byte;
						srb->total_xfer_length--;
						अगर (debug_enabled(DBG_PIO))
							prपूर्णांकk(" %02x", byte);
					पूर्ण

					DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONFIG2, 0);
				पूर्ण

				scsi_kunmap_atomic_sg(base);
				local_irq_restore(flags);
			पूर्ण
			/*prपूर्णांकk(" %08x", *(u32*)(bus_to_virt (addr))); */
			/*srb->total_xfer_length = 0; */
			अगर (debug_enabled(DBG_PIO))
				prपूर्णांकk("\n");
		पूर्ण
#पूर्ण_अगर				/* DC395x_LASTPIO */

#अगर 0
		/*
		 * KG: This was in DATAOUT. Does it also beदीर्घ here?
		 * Nobody seems to know what counter and fअगरo_cnt count exactly ...
		 */
		अगर (!(scsi_status & SCSIXFERDONE)) अणु
			/*
			 * when data transfer from DMA FIFO to SCSI FIFO
			 * अगर there was some data left in SCSI FIFO
			 */
			d_left_counter =
			    (u32)(DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFOCNT) &
				  0x1F);
			अगर (srb->dcb->sync_period & WIDE_SYNC)
				d_left_counter <<= 1;
			/*
			 * अगर WIDE scsi SCSI FIFOCNT unit is word !!!
			 * so need to *= 2
			 * KG: Seems to be correct ...
			 */
		पूर्ण
#पूर्ण_अगर
		/* KG: This should not be needed any more! */
		अगर (d_left_counter == 0
		    || (scsi_status & SCSIXFERCNT_2_ZERO)) अणु
#अगर 0
			पूर्णांक ctr = 6000000;
			u8 TempDMAstatus;
			करो अणु
				TempDMAstatus =
				    DC395x_पढ़ो8(acb, TRM_S1040_DMA_STATUS);
			पूर्ण जबतक (!(TempDMAstatus & DMAXFERCOMP) && --ctr);
			अगर (!ctr)
				dprपूर्णांकkl(KERN_ERR,
				       "Deadlock in DataInPhase0 waiting for DMA!!\n");
			srb->total_xfer_length = 0;
#पूर्ण_अगर
			srb->total_xfer_length = d_left_counter;
		पूर्ण अन्यथा अणु	/* phase changed */
			/*
			 * parsing the हाल:
			 * when a transfer not yet complete 
			 * but be disconnected by target
			 * अगर transfer not yet complete
			 * there were some data residue in SCSI FIFO or
			 * SCSI transfer counter not empty
			 */
			sg_update_list(srb, d_left_counter);
		पूर्ण
	पूर्ण
	/* KG: The target may decide to disconnect: Empty FIFO beक्रमe! */
	अगर ((*pscsi_status & PHASEMASK) != PH_DATA_IN) अणु
		cleanup_after_transfer(acb, srb);
	पूर्ण
पूर्ण


अटल व्योम data_in_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	dprपूर्णांकkdbg(DBG_0, "data_in_phase1: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun);
	data_io_transfer(acb, srb, XFERDATAIN);
पूर्ण


अटल व्योम data_io_transfer(काष्ठा AdapterCtlBlk *acb, 
		काष्ठा ScsiReqBlk *srb, u16 io_dir)
अणु
	काष्ठा DeviceCtlBlk *dcb = srb->dcb;
	u8 bval;
	dprपूर्णांकkdbg(DBG_0,
		"data_io_transfer: (0x%p) <%02i-%i> %c len=%i, sg=(%i/%i)\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun,
		((io_dir & DMACMD_सूची) ? 'r' : 'w'),
		srb->total_xfer_length, srb->sg_index, srb->sg_count);
	अगर (srb == acb->पंचांगp_srb)
		dprपूर्णांकkl(KERN_ERR, "data_io_transfer: Using tmp_srb!\n");
	अगर (srb->sg_index >= srb->sg_count) अणु
		/* can't happen? out of bounds error */
		वापस;
	पूर्ण

	अगर (srb->total_xfer_length > DC395x_LASTPIO) अणु
		u8 dma_status = DC395x_पढ़ो8(acb, TRM_S1040_DMA_STATUS);
		/*
		 * KG: What should we करो: Use SCSI Cmd 0x90/0x92?
		 * Maybe, even ABORTXFER would be appropriate
		 */
		अगर (dma_status & XFERPENDING) अणु
			dprपूर्णांकkl(KERN_DEBUG, "data_io_transfer: Xfer pending! "
				"Expect trouble!\n");
			dump_रेजिस्टर_info(acb, dcb, srb);
			DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, CLRXFIFO);
		पूर्ण
		/* clear_fअगरo(acb, "IO"); */
		/* 
		 * load what physical address of Scatter/Gather list table
		 * want to be transfer
		 */
		srb->state |= SRB_DATA_XFER;
		DC395x_ग_लिखो32(acb, TRM_S1040_DMA_XHIGHADDR, 0);
		अगर (scsi_sg_count(srb->cmd)) अणु	/* with S/G */
			io_dir |= DMACMD_SG;
			DC395x_ग_लिखो32(acb, TRM_S1040_DMA_XLOWADDR,
				       srb->sg_bus_addr +
				       माप(काष्ठा SGentry) *
				       srb->sg_index);
			/* load how many bytes in the sg list table */
			DC395x_ग_लिखो32(acb, TRM_S1040_DMA_XCNT,
				       ((u32)(srb->sg_count -
					      srb->sg_index) << 3));
		पूर्ण अन्यथा अणु	/* without S/G */
			io_dir &= ~DMACMD_SG;
			DC395x_ग_लिखो32(acb, TRM_S1040_DMA_XLOWADDR,
				       srb->segment_x[0].address);
			DC395x_ग_लिखो32(acb, TRM_S1040_DMA_XCNT,
				       srb->segment_x[0].length);
		पूर्ण
		/* load total transfer length (24bits) max value 16Mbyte */
		DC395x_ग_लिखो32(acb, TRM_S1040_SCSI_COUNTER,
			       srb->total_xfer_length);
		DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
		अगर (io_dir & DMACMD_सूची) अणु	/* पढ़ो */
			DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND,
				      SCMD_DMA_IN);
			DC395x_ग_लिखो16(acb, TRM_S1040_DMA_COMMAND, io_dir);
		पूर्ण अन्यथा अणु
			DC395x_ग_लिखो16(acb, TRM_S1040_DMA_COMMAND, io_dir);
			DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND,
				      SCMD_DMA_OUT);
		पूर्ण

	पूर्ण
#अगर DC395x_LASTPIO
	अन्यथा अगर (srb->total_xfer_length > 0) अणु	/* The last four bytes: Do PIO */
		/* 
		 * load what physical address of Scatter/Gather list table
		 * want to be transfer
		 */
		srb->state |= SRB_DATA_XFER;
		/* load total transfer length (24bits) max value 16Mbyte */
		DC395x_ग_लिखो32(acb, TRM_S1040_SCSI_COUNTER,
			       srb->total_xfer_length);
		DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
		अगर (io_dir & DMACMD_सूची) अणु	/* पढ़ो */
			DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND,
				      SCMD_FIFO_IN);
		पूर्ण अन्यथा अणु	/* ग_लिखो */
			पूर्णांक ln = srb->total_xfer_length;
			माप_प्रकार left_io = srb->total_xfer_length;

			अगर (srb->dcb->sync_period & WIDE_SYNC)
				DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONFIG2,
				     CFG2_WIDEFIFO);

			जबतक (left_io) अणु
				अचिन्हित अक्षर *virt, *base = शून्य;
				अचिन्हित दीर्घ flags = 0;
				माप_प्रकार len = left_io;
				माप_प्रकार offset = srb->request_length - left_io;

				local_irq_save(flags);
				/* Again, max 4 bytes */
				base = scsi_kmap_atomic_sg(scsi_sglist(srb->cmd),
							   srb->sg_count, &offset, &len);
				virt = base + offset;

				left_io -= len;

				जबतक (len--) अणु
					अगर (debug_enabled(DBG_PIO))
						prपूर्णांकk(" %02x", *virt);

					DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, *virt++);

					sg_subtract_one(srb);
				पूर्ण

				scsi_kunmap_atomic_sg(base);
				local_irq_restore(flags);
			पूर्ण
			अगर (srb->dcb->sync_period & WIDE_SYNC) अणु
				अगर (ln % 2) अणु
					DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 0);
					अगर (debug_enabled(DBG_PIO))
						prपूर्णांकk(" |00");
				पूर्ण
				DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONFIG2, 0);
			पूर्ण
			/*DC395x_ग_लिखो32(acb, TRM_S1040_SCSI_COUNTER, ln); */
			अगर (debug_enabled(DBG_PIO))
				prपूर्णांकk("\n");
			DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND,
					  SCMD_FIFO_OUT);
		पूर्ण
	पूर्ण
#पूर्ण_अगर				/* DC395x_LASTPIO */
	अन्यथा अणु		/* xfer pad */
		अगर (srb->sg_count) अणु
			srb->adapter_status = H_OVER_UNDER_RUN;
			srb->status |= OVER_RUN;
		पूर्ण
		/*
		 * KG: despite the fact that we are using 16 bits I/O ops
		 * the SCSI FIFO is only 8 bits according to the करोcs
		 * (we can set bit 1 in 0x8f to serialize FIFO access ...)
		 */
		अगर (dcb->sync_period & WIDE_SYNC) अणु
			DC395x_ग_लिखो32(acb, TRM_S1040_SCSI_COUNTER, 2);
			DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONFIG2,
				      CFG2_WIDEFIFO);
			अगर (io_dir & DMACMD_सूची) अणु
				DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFO);
				DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFO);
			पूर्ण अन्यथा अणु
				/* Danger, Robinson: If you find KGs
				 * scattered over the wide disk, the driver
				 * or chip is to blame :-( */
				DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 'K');
				DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 'G');
			पूर्ण
			DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONFIG2, 0);
		पूर्ण अन्यथा अणु
			DC395x_ग_लिखो32(acb, TRM_S1040_SCSI_COUNTER, 1);
			/* Danger, Robinson: If you find a collection of Ks on your disk
			 * something broke :-( */
			अगर (io_dir & DMACMD_सूची)
				DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFO);
			अन्यथा
				DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_FIFO, 'K');
		पूर्ण
		srb->state |= SRB_XFERPAD;
		DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
		/* SCSI command */
		bval = (io_dir & DMACMD_सूची) ? SCMD_FIFO_IN : SCMD_FIFO_OUT;
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, bval);
	पूर्ण
पूर्ण


अटल व्योम status_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	dprपूर्णांकkdbg(DBG_0, "status_phase0: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun);
	srb->target_status = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFO);
	srb->end_message = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFO);	/* get message */
	srb->state = SRB_COMPLETED;
	*pscsi_status = PH_BUS_FREE;	/*.. initial phase */
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, SCMD_MSGACCEPT);
पूर्ण


अटल व्योम status_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	dprपूर्णांकkdbg(DBG_0, "status_phase1: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun);
	srb->state = SRB_STATUS;
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, SCMD_COMP);
पूर्ण


/* Check अगर the message is complete */
अटल अंतरभूत u8 msgin_completed(u8 * msgbuf, u32 len)
अणु
	अगर (*msgbuf == EXTENDED_MESSAGE) अणु
		अगर (len < 2)
			वापस 0;
		अगर (len < msgbuf[1] + 2)
			वापस 0;
	पूर्ण अन्यथा अगर (*msgbuf >= 0x20 && *msgbuf <= 0x2f)	/* two byte messages */
		अगर (len < 2)
			वापस 0;
	वापस 1;
पूर्ण

/* reject_msg */
अटल अंतरभूत व्योम msgin_reject(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb)
अणु
	srb->msgout_buf[0] = MESSAGE_REJECT;
	srb->msg_count = 1;
	DC395x_ENABLE_MSGOUT;
	srb->state &= ~SRB_MSGIN;
	srb->state |= SRB_MSGOUT;
	dprपूर्णांकkl(KERN_INFO, "msgin_reject: 0x%02x <%02i-%i>\n",
		srb->msgin_buf[0],
		srb->dcb->target_id, srb->dcb->target_lun);
पूर्ण


अटल काष्ठा ScsiReqBlk *msgin_qtag(काष्ठा AdapterCtlBlk *acb,
		काष्ठा DeviceCtlBlk *dcb, u8 tag)
अणु
	काष्ठा ScsiReqBlk *srb = शून्य;
	काष्ठा ScsiReqBlk *i;
	dprपूर्णांकkdbg(DBG_0, "msgin_qtag: (0x%p) tag=%i srb=%p\n",
		   srb->cmd, tag, srb);

	अगर (!(dcb->tag_mask & (1 << tag)))
		dprपूर्णांकkl(KERN_DEBUG,
			"msgin_qtag: tag_mask=0x%08x does not reserve tag %i!\n",
			dcb->tag_mask, tag);

	अगर (list_empty(&dcb->srb_going_list))
		जाओ mingx0;
	list_क्रम_each_entry(i, &dcb->srb_going_list, list) अणु
		अगर (i->tag_number == tag) अणु
			srb = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!srb)
		जाओ mingx0;

	dprपूर्णांकkdbg(DBG_0, "msgin_qtag: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->dcb->target_id, srb->dcb->target_lun);
	अगर (dcb->flag & ABORT_DEV_) अणु
		/*srb->state = SRB_ABORT_SENT; */
		enable_msgout_पात(acb, srb);
	पूर्ण

	अगर (!(srb->state & SRB_DISCONNECT))
		जाओ mingx0;

	स_नकल(srb->msgin_buf, dcb->active_srb->msgin_buf, acb->msg_len);
	srb->state |= dcb->active_srb->state;
	srb->state |= SRB_DATA_XFER;
	dcb->active_srb = srb;
	/* How can we make the DORS happy? */
	वापस srb;

      mingx0:
	srb = acb->पंचांगp_srb;
	srb->state = SRB_UNEXPECT_RESEL;
	dcb->active_srb = srb;
	srb->msgout_buf[0] = ABORT_TASK;
	srb->msg_count = 1;
	DC395x_ENABLE_MSGOUT;
	dprपूर्णांकkl(KERN_DEBUG, "msgin_qtag: Unknown tag %i - abort\n", tag);
	वापस srb;
पूर्ण


अटल अंतरभूत व्योम reprogram_regs(काष्ठा AdapterCtlBlk *acb,
		काष्ठा DeviceCtlBlk *dcb)
अणु
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_TARGETID, dcb->target_id);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_SYNC, dcb->sync_period);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_OFFSET, dcb->sync_offset);
	set_xfer_rate(acb, dcb);
पूर्ण


/* set async transfer mode */
अटल व्योम msgin_set_async(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb)
अणु
	काष्ठा DeviceCtlBlk *dcb = srb->dcb;
	dprपूर्णांकkl(KERN_DEBUG, "msgin_set_async: No sync transfers <%02i-%i>\n",
		dcb->target_id, dcb->target_lun);

	dcb->sync_mode &= ~(SYNC_NEGO_ENABLE);
	dcb->sync_mode |= SYNC_NEGO_DONE;
	/*dcb->sync_period &= 0; */
	dcb->sync_offset = 0;
	dcb->min_nego_period = 200 >> 2;	/* 200ns <=> 5 MHz */
	srb->state &= ~SRB_DO_SYNC_NEGO;
	reprogram_regs(acb, dcb);
	अगर ((dcb->sync_mode & WIDE_NEGO_ENABLE)
	    && !(dcb->sync_mode & WIDE_NEGO_DONE)) अणु
		build_wdtr(acb, dcb, srb);
		DC395x_ENABLE_MSGOUT;
		dprपूर्णांकkdbg(DBG_0, "msgin_set_async(rej): Try WDTR anyway\n");
	पूर्ण
पूर्ण


/* set sync transfer mode */
अटल व्योम msgin_set_sync(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb)
अणु
	काष्ठा DeviceCtlBlk *dcb = srb->dcb;
	u8 bval;
	पूर्णांक fact;
	dprपूर्णांकkdbg(DBG_1, "msgin_set_sync: <%02i> Sync: %ins "
		"(%02i.%01i MHz) Offset %i\n",
		dcb->target_id, srb->msgin_buf[3] << 2,
		(250 / srb->msgin_buf[3]),
		((250 % srb->msgin_buf[3]) * 10) / srb->msgin_buf[3],
		srb->msgin_buf[4]);

	अगर (srb->msgin_buf[4] > 15)
		srb->msgin_buf[4] = 15;
	अगर (!(dcb->dev_mode & NTC_DO_SYNC_NEGO))
		dcb->sync_offset = 0;
	अन्यथा अगर (dcb->sync_offset == 0)
		dcb->sync_offset = srb->msgin_buf[4];
	अगर (srb->msgin_buf[4] > dcb->sync_offset)
		srb->msgin_buf[4] = dcb->sync_offset;
	अन्यथा
		dcb->sync_offset = srb->msgin_buf[4];
	bval = 0;
	जबतक (bval < 7 && (srb->msgin_buf[3] > घड़ी_period[bval]
			    || dcb->min_nego_period >
			    घड़ी_period[bval]))
		bval++;
	अगर (srb->msgin_buf[3] < घड़ी_period[bval])
		dprपूर्णांकkl(KERN_INFO,
			"msgin_set_sync: Increase sync nego period to %ins\n",
			घड़ी_period[bval] << 2);
	srb->msgin_buf[3] = घड़ी_period[bval];
	dcb->sync_period &= 0xf0;
	dcb->sync_period |= ALT_SYNC | bval;
	dcb->min_nego_period = srb->msgin_buf[3];

	अगर (dcb->sync_period & WIDE_SYNC)
		fact = 500;
	अन्यथा
		fact = 250;

	dprपूर्णांकkl(KERN_INFO,
		"Target %02i: %s Sync: %ins Offset %i (%02i.%01i MB/s)\n",
		dcb->target_id, (fact == 500) ? "Wide16" : "",
		dcb->min_nego_period << 2, dcb->sync_offset,
		(fact / dcb->min_nego_period),
		((fact % dcb->min_nego_period) * 10 +
		dcb->min_nego_period / 2) / dcb->min_nego_period);

	अगर (!(srb->state & SRB_DO_SYNC_NEGO)) अणु
		/* Reply with corrected SDTR Message */
		dprपूर्णांकkl(KERN_DEBUG, "msgin_set_sync: answer w/%ins %i\n",
			srb->msgin_buf[3] << 2, srb->msgin_buf[4]);

		स_नकल(srb->msgout_buf, srb->msgin_buf, 5);
		srb->msg_count = 5;
		DC395x_ENABLE_MSGOUT;
		dcb->sync_mode |= SYNC_NEGO_DONE;
	पूर्ण अन्यथा अणु
		अगर ((dcb->sync_mode & WIDE_NEGO_ENABLE)
		    && !(dcb->sync_mode & WIDE_NEGO_DONE)) अणु
			build_wdtr(acb, dcb, srb);
			DC395x_ENABLE_MSGOUT;
			dprपूर्णांकkdbg(DBG_0, "msgin_set_sync: Also try WDTR\n");
		पूर्ण
	पूर्ण
	srb->state &= ~SRB_DO_SYNC_NEGO;
	dcb->sync_mode |= SYNC_NEGO_DONE | SYNC_NEGO_ENABLE;

	reprogram_regs(acb, dcb);
पूर्ण


अटल अंतरभूत व्योम msgin_set_nowide(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb)
अणु
	काष्ठा DeviceCtlBlk *dcb = srb->dcb;
	dprपूर्णांकkdbg(DBG_1, "msgin_set_nowide: <%02i>\n", dcb->target_id);

	dcb->sync_period &= ~WIDE_SYNC;
	dcb->sync_mode &= ~(WIDE_NEGO_ENABLE);
	dcb->sync_mode |= WIDE_NEGO_DONE;
	srb->state &= ~SRB_DO_WIDE_NEGO;
	reprogram_regs(acb, dcb);
	अगर ((dcb->sync_mode & SYNC_NEGO_ENABLE)
	    && !(dcb->sync_mode & SYNC_NEGO_DONE)) अणु
		build_sdtr(acb, dcb, srb);
		DC395x_ENABLE_MSGOUT;
		dprपूर्णांकkdbg(DBG_0, "msgin_set_nowide: Rejected. Try SDTR anyway\n");
	पूर्ण
पूर्ण

अटल व्योम msgin_set_wide(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb)
अणु
	काष्ठा DeviceCtlBlk *dcb = srb->dcb;
	u8 wide = (dcb->dev_mode & NTC_DO_WIDE_NEGO
		   && acb->config & HCC_WIDE_CARD) ? 1 : 0;
	dprपूर्णांकkdbg(DBG_1, "msgin_set_wide: <%02i>\n", dcb->target_id);

	अगर (srb->msgin_buf[3] > wide)
		srb->msgin_buf[3] = wide;
	/* Completed */
	अगर (!(srb->state & SRB_DO_WIDE_NEGO)) अणु
		dprपूर्णांकkl(KERN_DEBUG,
			"msgin_set_wide: Wide nego initiated <%02i>\n",
			dcb->target_id);
		स_नकल(srb->msgout_buf, srb->msgin_buf, 4);
		srb->msg_count = 4;
		srb->state |= SRB_DO_WIDE_NEGO;
		DC395x_ENABLE_MSGOUT;
	पूर्ण

	dcb->sync_mode |= (WIDE_NEGO_ENABLE | WIDE_NEGO_DONE);
	अगर (srb->msgin_buf[3] > 0)
		dcb->sync_period |= WIDE_SYNC;
	अन्यथा
		dcb->sync_period &= ~WIDE_SYNC;
	srb->state &= ~SRB_DO_WIDE_NEGO;
	/*dcb->sync_mode &= ~(WIDE_NEGO_ENABLE+WIDE_NEGO_DONE); */
	dprपूर्णांकkdbg(DBG_1,
		"msgin_set_wide: Wide (%i bit) negotiated <%02i>\n",
		(8 << srb->msgin_buf[3]), dcb->target_id);
	reprogram_regs(acb, dcb);
	अगर ((dcb->sync_mode & SYNC_NEGO_ENABLE)
	    && !(dcb->sync_mode & SYNC_NEGO_DONE)) अणु
		build_sdtr(acb, dcb, srb);
		DC395x_ENABLE_MSGOUT;
		dprपूर्णांकkdbg(DBG_0, "msgin_set_wide: Also try SDTR.\n");
	पूर्ण
पूर्ण


/*
 * extended message codes:
 *
 *	code	description
 *
 *	02h	Reserved
 *	00h	MODIFY DATA  POINTER
 *	01h	SYNCHRONOUS DATA TRANSFER REQUEST
 *	03h	WIDE DATA TRANSFER REQUEST
 *   04h - 7Fh	Reserved
 *   80h - FFh	Venकरोr specअगरic
 */
अटल व्योम msgin_phase0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	काष्ठा DeviceCtlBlk *dcb = acb->active_dcb;
	dprपूर्णांकkdbg(DBG_0, "msgin_phase0: (0x%p)\n", srb->cmd);

	srb->msgin_buf[acb->msg_len++] = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_FIFO);
	अगर (msgin_completed(srb->msgin_buf, acb->msg_len)) अणु
		/* Now eval the msg */
		चयन (srb->msgin_buf[0]) अणु
		हाल DISCONNECT:
			srb->state = SRB_DISCONNECT;
			अवरोध;

		हाल SIMPLE_QUEUE_TAG:
		हाल HEAD_OF_QUEUE_TAG:
		हाल ORDERED_QUEUE_TAG:
			srb =
			    msgin_qtag(acb, dcb,
					      srb->msgin_buf[1]);
			अवरोध;

		हाल MESSAGE_REJECT:
			DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL,
				       DO_CLRATN | DO_DATALATCH);
			/* A sync nego message was rejected ! */
			अगर (srb->state & SRB_DO_SYNC_NEGO) अणु
				msgin_set_async(acb, srb);
				अवरोध;
			पूर्ण
			/* A wide nego message was rejected ! */
			अगर (srb->state & SRB_DO_WIDE_NEGO) अणु
				msgin_set_nowide(acb, srb);
				अवरोध;
			पूर्ण
			enable_msgout_पात(acb, srb);
			/*srb->state |= SRB_ABORT_SENT */
			अवरोध;

		हाल EXTENDED_MESSAGE:
			/* SDTR */
			अगर (srb->msgin_buf[1] == 3
			    && srb->msgin_buf[2] == EXTENDED_SDTR) अणु
				msgin_set_sync(acb, srb);
				अवरोध;
			पूर्ण
			/* WDTR */
			अगर (srb->msgin_buf[1] == 2
			    && srb->msgin_buf[2] == EXTENDED_WDTR
			    && srb->msgin_buf[3] <= 2) अणु /* sanity check ... */
				msgin_set_wide(acb, srb);
				अवरोध;
			पूर्ण
			msgin_reject(acb, srb);
			अवरोध;

		हाल IGNORE_WIDE_RESIDUE:
			/* Discard  wide residual */
			dprपूर्णांकkdbg(DBG_0, "msgin_phase0: Ignore Wide Residual!\n");
			अवरोध;

		हाल COMMAND_COMPLETE:
			/* nothing has to be करोne */
			अवरोध;

		हाल SAVE_POINTERS:
			/*
			 * SAVE POINTER may be ignored as we have the काष्ठा
			 * ScsiReqBlk* associated with the scsi command.
			 */
			dprपूर्णांकkdbg(DBG_0, "msgin_phase0: (0x%p) "
				"SAVE POINTER rem=%i Ignore\n",
				srb->cmd, srb->total_xfer_length);
			अवरोध;

		हाल RESTORE_POINTERS:
			dprपूर्णांकkdbg(DBG_0, "msgin_phase0: RESTORE POINTER. Ignore\n");
			अवरोध;

		हाल ABORT:
			dprपूर्णांकkdbg(DBG_0, "msgin_phase0: (0x%p) "
				"<%02i-%i> ABORT msg\n",
				srb->cmd, dcb->target_id,
				dcb->target_lun);
			dcb->flag |= ABORT_DEV_;
			enable_msgout_पात(acb, srb);
			अवरोध;

		शेष:
			/* reject unknown messages */
			अगर (srb->msgin_buf[0] & IDENTIFY_BASE) अणु
				dprपूर्णांकkdbg(DBG_0, "msgin_phase0: Identify msg\n");
				srb->msg_count = 1;
				srb->msgout_buf[0] = dcb->identअगरy_msg;
				DC395x_ENABLE_MSGOUT;
				srb->state |= SRB_MSGOUT;
				/*अवरोध; */
			पूर्ण
			msgin_reject(acb, srb);
		पूर्ण

		/* Clear counter and MsgIn state */
		srb->state &= ~SRB_MSGIN;
		acb->msg_len = 0;
	पूर्ण
	*pscsi_status = PH_BUS_FREE;
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important ... you know! */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, SCMD_MSGACCEPT);
पूर्ण


अटल व्योम msgin_phase1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
	dprपूर्णांकkdbg(DBG_0, "msgin_phase1: (0x%p)\n", srb->cmd);
	clear_fअगरo(acb, "msgin_phase1");
	DC395x_ग_लिखो32(acb, TRM_S1040_SCSI_COUNTER, 1);
	अगर (!(srb->state & SRB_MSGIN)) अणु
		srb->state &= ~SRB_DISCONNECT;
		srb->state |= SRB_MSGIN;
	पूर्ण
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
	/* SCSI command */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_IN);
पूर्ण


अटल व्योम nop0(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
पूर्ण


अटल व्योम nop1(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb,
		u16 *pscsi_status)
अणु
पूर्ण


अटल व्योम set_xfer_rate(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb)
अणु
	काष्ठा DeviceCtlBlk *i;

	/* set all lun device's  period, offset */
	अगर (dcb->identअगरy_msg & 0x07)
		वापस;

	अगर (acb->scan_devices) अणु
		current_sync_offset = dcb->sync_offset;
		वापस;
	पूर्ण

	list_क्रम_each_entry(i, &acb->dcb_list, list)
		अगर (i->target_id == dcb->target_id) अणु
			i->sync_period = dcb->sync_period;
			i->sync_offset = dcb->sync_offset;
			i->sync_mode = dcb->sync_mode;
			i->min_nego_period = dcb->min_nego_period;
		पूर्ण
पूर्ण


अटल व्योम disconnect(काष्ठा AdapterCtlBlk *acb)
अणु
	काष्ठा DeviceCtlBlk *dcb = acb->active_dcb;
	काष्ठा ScsiReqBlk *srb;

	अगर (!dcb) अणु
		dprपूर्णांकkl(KERN_ERR, "disconnect: No such device\n");
		udelay(500);
		/* Suspend queue क्रम a जबतक */
		acb->last_reset =
		    jअगरfies + HZ / 2 +
		    HZ * acb->eeprom.delay_समय;
		clear_fअगरo(acb, "disconnectEx");
		DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT);
		वापस;
	पूर्ण
	srb = dcb->active_srb;
	acb->active_dcb = शून्य;
	dprपूर्णांकkdbg(DBG_0, "disconnect: (0x%p)\n", srb->cmd);

	srb->scsi_phase = PH_BUS_FREE;	/* initial phase */
	clear_fअगरo(acb, "disconnect");
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT);
	अगर (srb->state & SRB_UNEXPECT_RESEL) अणु
		dprपूर्णांकkl(KERN_ERR,
			"disconnect: Unexpected reselection <%02i-%i>\n",
			dcb->target_id, dcb->target_lun);
		srb->state = 0;
		रुकोing_process_next(acb);
	पूर्ण अन्यथा अगर (srb->state & SRB_ABORT_SENT) अणु
		dcb->flag &= ~ABORT_DEV_;
		acb->last_reset = jअगरfies + HZ / 2 + 1;
		dprपूर्णांकkl(KERN_ERR, "disconnect: SRB_ABORT_SENT\n");
		करोing_srb_करोne(acb, DID_ABORT, srb->cmd, 1);
		रुकोing_process_next(acb);
	पूर्ण अन्यथा अणु
		अगर ((srb->state & (SRB_START_ + SRB_MSGOUT))
		    || !(srb->
			 state & (SRB_DISCONNECT | SRB_COMPLETED))) अणु
			/*
			 * Selection समय out 
			 * SRB_START_ || SRB_MSGOUT || (!SRB_DISCONNECT && !SRB_COMPLETED)
			 */
			/* Unexp. Disc / Sel Timeout */
			अगर (srb->state != SRB_START_
			    && srb->state != SRB_MSGOUT) अणु
				srb->state = SRB_READY;
				dprपूर्णांकkl(KERN_DEBUG,
					"disconnect: (0x%p) Unexpected\n",
					srb->cmd);
				srb->target_status = SCSI_STAT_SEL_TIMEOUT;
				जाओ disc1;
			पूर्ण अन्यथा अणु
				/* Normal selection समयout */
				dprपूर्णांकkdbg(DBG_KG, "disconnect: (0x%p) "
					"<%02i-%i> SelTO\n", srb->cmd,
					dcb->target_id, dcb->target_lun);
				अगर (srb->retry_count++ > DC395x_MAX_RETRIES
				    || acb->scan_devices) अणु
					srb->target_status =
					    SCSI_STAT_SEL_TIMEOUT;
					जाओ disc1;
				पूर्ण
				मुक्त_tag(dcb, srb);
				list_move(&srb->list, &dcb->srb_रुकोing_list);
				dprपूर्णांकkdbg(DBG_KG,
					"disconnect: (0x%p) Retry\n",
					srb->cmd);
				रुकोing_set_समयr(acb, HZ / 20);
			पूर्ण
		पूर्ण अन्यथा अगर (srb->state & SRB_DISCONNECT) अणु
			u8 bval = DC395x_पढ़ो8(acb, TRM_S1040_SCSI_SIGNAL);
			/*
			 * SRB_DISCONNECT (This is what we expect!)
			 */
			अगर (bval & 0x40) अणु
				dprपूर्णांकkdbg(DBG_0, "disconnect: SCSI bus stat "
					" 0x%02x: ACK set! Other controllers?\n",
					bval);
				/* It could come from another initiator, thereक्रमe करोn't करो much ! */
			पूर्ण अन्यथा
				रुकोing_process_next(acb);
		पूर्ण अन्यथा अगर (srb->state & SRB_COMPLETED) अणु
		      disc1:
			/*
			 ** SRB_COMPLETED
			 */
			मुक्त_tag(dcb, srb);
			dcb->active_srb = शून्य;
			srb->state = SRB_FREE;
			srb_करोne(acb, dcb, srb);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम reselect(काष्ठा AdapterCtlBlk *acb)
अणु
	काष्ठा DeviceCtlBlk *dcb = acb->active_dcb;
	काष्ठा ScsiReqBlk *srb = शून्य;
	u16 rsel_tar_lun_id;
	u8 id, lun;
	dprपूर्णांकkdbg(DBG_0, "reselect: acb=%p\n", acb);

	clear_fअगरo(acb, "reselect");
	/*DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT | DO_DATALATCH); */
	/* Read Reselected Target ID and LUN */
	rsel_tar_lun_id = DC395x_पढ़ो16(acb, TRM_S1040_SCSI_TARGETID);
	अगर (dcb) अणु		/* Arbitration lost but Reselection win */
		srb = dcb->active_srb;
		अगर (!srb) अणु
			dprपूर्णांकkl(KERN_DEBUG, "reselect: Arb lost Resel won, "
				"but active_srb == NULL\n");
			DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
			वापस;
		पूर्ण
		/* Why the अगर ? */
		अगर (!acb->scan_devices) अणु
			dprपूर्णांकkdbg(DBG_KG, "reselect: (0x%p) <%02i-%i> "
				"Arb lost but Resel win rsel=%i stat=0x%04x\n",
				srb->cmd, dcb->target_id,
				dcb->target_lun, rsel_tar_lun_id,
				DC395x_पढ़ो16(acb, TRM_S1040_SCSI_STATUS));
			/*srb->state |= SRB_DISCONNECT; */

			srb->state = SRB_READY;
			मुक्त_tag(dcb, srb);
			list_move(&srb->list, &dcb->srb_रुकोing_list);
			रुकोing_set_समयr(acb, HZ / 20);

			/* वापस; */
		पूर्ण
	पूर्ण
	/* Read Reselected Target Id and LUN */
	अगर (!(rsel_tar_lun_id & (IDENTIFY_BASE << 8)))
		dprपूर्णांकkl(KERN_DEBUG, "reselect: Expects identify msg. "
			"Got %i!\n", rsel_tar_lun_id);
	id = rsel_tar_lun_id & 0xff;
	lun = (rsel_tar_lun_id >> 8) & 7;
	dcb = find_dcb(acb, id, lun);
	अगर (!dcb) अणु
		dprपूर्णांकkl(KERN_ERR, "reselect: From non existent device "
			"<%02i-%i>\n", id, lun);
		DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important क्रम atn stop */
		वापस;
	पूर्ण
	acb->active_dcb = dcb;

	अगर (!(dcb->dev_mode & NTC_DO_DISCONNECT))
		dprपूर्णांकkl(KERN_DEBUG, "reselect: in spite of forbidden "
			"disconnection? <%02i-%i>\n",
			dcb->target_id, dcb->target_lun);

	अगर (dcb->sync_mode & EN_TAG_QUEUEING) अणु
		srb = acb->पंचांगp_srb;
		dcb->active_srb = srb;
	पूर्ण अन्यथा अणु
		/* There can be only one! */
		srb = dcb->active_srb;
		अगर (!srb || !(srb->state & SRB_DISCONNECT)) अणु
			/*
			 * पात command
			 */
			dprपूर्णांकkl(KERN_DEBUG,
				"reselect: w/o disconnected cmds <%02i-%i>\n",
				dcb->target_id, dcb->target_lun);
			srb = acb->पंचांगp_srb;
			srb->state = SRB_UNEXPECT_RESEL;
			dcb->active_srb = srb;
			enable_msgout_पात(acb, srb);
		पूर्ण अन्यथा अणु
			अगर (dcb->flag & ABORT_DEV_) अणु
				/*srb->state = SRB_ABORT_SENT; */
				enable_msgout_पात(acb, srb);
			पूर्ण अन्यथा
				srb->state = SRB_DATA_XFER;

		पूर्ण
	पूर्ण
	srb->scsi_phase = PH_BUS_FREE;	/* initial phase */

	/* Program HA ID, target ID, period and offset */
	dprपूर्णांकkdbg(DBG_0, "reselect: select <%i>\n", dcb->target_id);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_HOSTID, acb->scsi_host->this_id);	/* host   ID */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_TARGETID, dcb->target_id);		/* target ID */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_OFFSET, dcb->sync_offset);		/* offset    */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_SYNC, dcb->sync_period);		/* sync period, wide */
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);		/* it's important क्रम atn stop */
	/* SCSI command */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_COMMAND, SCMD_MSGACCEPT);
पूर्ण


अटल अंतरभूत u8 tagq_blacklist(अक्षर *name)
अणु
#अगर_अघोषित DC395x_NO_TAGQ
#अगर 0
	u8 i;
	क्रम (i = 0; i < BADDEVCNT; i++)
		अगर (स_भेद(name, DC395x_baddevname1[i], 28) == 0)
			वापस 1;
#पूर्ण_अगर
	वापस 0;
#अन्यथा
	वापस 1;
#पूर्ण_अगर
पूर्ण


अटल व्योम disc_tagq_set(काष्ठा DeviceCtlBlk *dcb, काष्ठा ScsiInqData *ptr)
अणु
	/* Check क्रम SCSI क्रमmat (ANSI and Response data क्रमmat) */
	अगर ((ptr->Vers & 0x07) >= 2 || (ptr->RDF & 0x0F) == 2) अणु
		अगर ((ptr->Flags & SCSI_INQ_CMDQUEUE)
		    && (dcb->dev_mode & NTC_DO_TAG_QUEUEING) &&
		    /*(dcb->dev_mode & NTC_DO_DISCONNECT) */
		    /* ((dcb->dev_type == TYPE_DISK) 
		       || (dcb->dev_type == TYPE_MOD)) && */
		    !tagq_blacklist(((अक्षर *)ptr) + 8)) अणु
			अगर (dcb->max_command == 1)
				dcb->max_command =
				    dcb->acb->tag_max_num;
			dcb->sync_mode |= EN_TAG_QUEUEING;
			/*dcb->tag_mask = 0; */
		पूर्ण अन्यथा
			dcb->max_command = 1;
	पूर्ण
पूर्ण


अटल व्योम add_dev(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiInqData *ptr)
अणु
	u8 bval1 = ptr->DevType & SCSI_DEVTYPE;
	dcb->dev_type = bval1;
	/* अगर (bval1 == TYPE_DISK || bval1 == TYPE_MOD) */
	disc_tagq_set(dcb, ptr);
पूर्ण


/* unmap mapped pci regions from SRB */
अटल व्योम pci_unmap_srb(काष्ठा AdapterCtlBlk *acb, काष्ठा ScsiReqBlk *srb)
अणु
	काष्ठा scsi_cmnd *cmd = srb->cmd;
	क्रमागत dma_data_direction dir = cmd->sc_data_direction;

	अगर (scsi_sg_count(cmd) && dir != DMA_NONE) अणु
		/* unmap DC395x SG list */
		dprपूर्णांकkdbg(DBG_SG, "pci_unmap_srb: list=%08x(%05x)\n",
			srb->sg_bus_addr, SEGMENTX_LEN);
		dma_unmap_single(&acb->dev->dev, srb->sg_bus_addr, SEGMENTX_LEN,
				DMA_TO_DEVICE);
		dprपूर्णांकkdbg(DBG_SG, "pci_unmap_srb: segs=%i buffer=%p\n",
			   scsi_sg_count(cmd), scsi_bufflen(cmd));
		/* unmap the sg segments */
		scsi_dma_unmap(cmd);
	पूर्ण
पूर्ण


/* unmap mapped pci sense buffer from SRB */
अटल व्योम pci_unmap_srb_sense(काष्ठा AdapterCtlBlk *acb,
		काष्ठा ScsiReqBlk *srb)
अणु
	अगर (!(srb->flag & AUTO_REQSENSE))
		वापस;
	/* Unmap sense buffer */
	dprपूर्णांकkdbg(DBG_SG, "pci_unmap_srb_sense: buffer=%08x\n",
	       srb->segment_x[0].address);
	dma_unmap_single(&acb->dev->dev, srb->segment_x[0].address,
			 srb->segment_x[0].length, DMA_FROM_DEVICE);
	/* Restore SG stuff */
	srb->total_xfer_length = srb->xferred;
	srb->segment_x[0].address =
	    srb->segment_x[DC395x_MAX_SG_LISTENTRY - 1].address;
	srb->segment_x[0].length =
	    srb->segment_x[DC395x_MAX_SG_LISTENTRY - 1].length;
पूर्ण


/*
 * Complete execution of a SCSI command
 * Signal completion to the generic SCSI driver  
 */
अटल व्योम srb_करोne(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb)
अणु
	u8 tempcnt, status;
	काष्ठा scsi_cmnd *cmd = srb->cmd;
	क्रमागत dma_data_direction dir = cmd->sc_data_direction;
	पूर्णांक ckc_only = 1;

	dprपूर्णांकkdbg(DBG_1, "srb_done: (0x%p) <%02i-%i>\n", srb->cmd,
		srb->cmd->device->id, (u8)srb->cmd->device->lun);
	dprपूर्णांकkdbg(DBG_SG, "srb_done: srb=%p sg=%i(%i/%i) buf=%p\n",
		   srb, scsi_sg_count(cmd), srb->sg_index, srb->sg_count,
		   scsi_sgtalbe(cmd));
	status = srb->target_status;
	अगर (srb->flag & AUTO_REQSENSE) अणु
		dprपूर्णांकkdbg(DBG_0, "srb_done: AUTO_REQSENSE1\n");
		pci_unmap_srb_sense(acb, srb);
		/*
		 ** target status..........................
		 */
		srb->flag &= ~AUTO_REQSENSE;
		srb->adapter_status = 0;
		srb->target_status = CHECK_CONDITION << 1;
		अगर (debug_enabled(DBG_1)) अणु
			चयन (cmd->sense_buffer[2] & 0x0f) अणु
			हाल NOT_READY:
				dprपूर्णांकkl(KERN_DEBUG,
				     "ReqSense: NOT_READY cmnd=0x%02x <%02i-%i> stat=%i scan=%i ",
				     cmd->cmnd[0], dcb->target_id,
				     dcb->target_lun, status, acb->scan_devices);
				अवरोध;
			हाल UNIT_ATTENTION:
				dprपूर्णांकkl(KERN_DEBUG,
				     "ReqSense: UNIT_ATTENTION cmnd=0x%02x <%02i-%i> stat=%i scan=%i ",
				     cmd->cmnd[0], dcb->target_id,
				     dcb->target_lun, status, acb->scan_devices);
				अवरोध;
			हाल ILLEGAL_REQUEST:
				dprपूर्णांकkl(KERN_DEBUG,
				     "ReqSense: ILLEGAL_REQUEST cmnd=0x%02x <%02i-%i> stat=%i scan=%i ",
				     cmd->cmnd[0], dcb->target_id,
				     dcb->target_lun, status, acb->scan_devices);
				अवरोध;
			हाल MEDIUM_ERROR:
				dprपूर्णांकkl(KERN_DEBUG,
				     "ReqSense: MEDIUM_ERROR cmnd=0x%02x <%02i-%i> stat=%i scan=%i ",
				     cmd->cmnd[0], dcb->target_id,
				     dcb->target_lun, status, acb->scan_devices);
				अवरोध;
			हाल HARDWARE_ERROR:
				dprपूर्णांकkl(KERN_DEBUG,
				     "ReqSense: HARDWARE_ERROR cmnd=0x%02x <%02i-%i> stat=%i scan=%i ",
				     cmd->cmnd[0], dcb->target_id,
				     dcb->target_lun, status, acb->scan_devices);
				अवरोध;
			पूर्ण
			अगर (cmd->sense_buffer[7] >= 6)
				prपूर्णांकk("sense=0x%02x ASC=0x%02x ASCQ=0x%02x "
					"(0x%08x 0x%08x)\n",
					cmd->sense_buffer[2], cmd->sense_buffer[12],
					cmd->sense_buffer[13],
					*((अचिन्हित पूर्णांक *)(cmd->sense_buffer + 3)),
					*((अचिन्हित पूर्णांक *)(cmd->sense_buffer + 8)));
			अन्यथा
				prपूर्णांकk("sense=0x%02x No ASC/ASCQ (0x%08x)\n",
					cmd->sense_buffer[2],
					*((अचिन्हित पूर्णांक *)(cmd->sense_buffer + 3)));
		पूर्ण

		अगर (status == (CHECK_CONDITION << 1)) अणु
			cmd->result = DID_BAD_TARGET << 16;
			जाओ ckc_e;
		पूर्ण
		dprपूर्णांकkdbg(DBG_0, "srb_done: AUTO_REQSENSE2\n");

		अगर (srb->total_xfer_length
		    && srb->total_xfer_length >= cmd->underflow)
			cmd->result =
			    MK_RES_LNX(DRIVER_SENSE, DID_OK,
				       srb->end_message, CHECK_CONDITION);
		/*SET_RES_DID(cmd->result,DID_OK) */
		अन्यथा
			cmd->result =
			    MK_RES_LNX(DRIVER_SENSE, DID_OK,
				       srb->end_message, CHECK_CONDITION);

		जाओ ckc_e;
	पूर्ण

/*************************************************************/
	अगर (status) अणु
		/*
		 * target status..........................
		 */
		अगर (status >> 1 == CHECK_CONDITION) अणु
			request_sense(acb, dcb, srb);
			वापस;
		पूर्ण अन्यथा अगर (status >> 1 == QUEUE_FULL) अणु
			tempcnt = (u8)list_size(&dcb->srb_going_list);
			dprपूर्णांकkl(KERN_INFO, "QUEUE_FULL for dev <%02i-%i> with %i cmnds\n",
			     dcb->target_id, dcb->target_lun, tempcnt);
			अगर (tempcnt > 1)
				tempcnt--;
			dcb->max_command = tempcnt;
			मुक्त_tag(dcb, srb);
			list_move(&srb->list, &dcb->srb_रुकोing_list);
			रुकोing_set_समयr(acb, HZ / 20);
			srb->adapter_status = 0;
			srb->target_status = 0;
			वापस;
		पूर्ण अन्यथा अगर (status == SCSI_STAT_SEL_TIMEOUT) अणु
			srb->adapter_status = H_SEL_TIMEOUT;
			srb->target_status = 0;
			cmd->result = DID_NO_CONNECT << 16;
		पूर्ण अन्यथा अणु
			srb->adapter_status = 0;
			SET_RES_DID(cmd->result, DID_ERROR);
			SET_RES_MSG(cmd->result, srb->end_message);
			SET_RES_TARGET(cmd->result, status);

		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 ** process initiator status..........................
		 */
		status = srb->adapter_status;
		अगर (status & H_OVER_UNDER_RUN) अणु
			srb->target_status = 0;
			SET_RES_DID(cmd->result, DID_OK);
			SET_RES_MSG(cmd->result, srb->end_message);
		पूर्ण अन्यथा अगर (srb->status & PARITY_ERROR) अणु
			SET_RES_DID(cmd->result, DID_PARITY);
			SET_RES_MSG(cmd->result, srb->end_message);
		पूर्ण अन्यथा अणु	/* No error */

			srb->adapter_status = 0;
			srb->target_status = 0;
			SET_RES_DID(cmd->result, DID_OK);
		पूर्ण
	पूर्ण

	ckc_only = 0;
/* Check Error Conditions */
      ckc_e:

	pci_unmap_srb(acb, srb);

	अगर (cmd->cmnd[0] == INQUIRY) अणु
		अचिन्हित अक्षर *base = शून्य;
		काष्ठा ScsiInqData *ptr;
		अचिन्हित दीर्घ flags = 0;
		काष्ठा scatterlist* sg = scsi_sglist(cmd);
		माप_प्रकार offset = 0, len = माप(काष्ठा ScsiInqData);

		local_irq_save(flags);
		base = scsi_kmap_atomic_sg(sg, scsi_sg_count(cmd), &offset, &len);
		ptr = (काष्ठा ScsiInqData *)(base + offset);

		अगर (!ckc_only && (cmd->result & RES_DID) == 0
		    && cmd->cmnd[2] == 0 && scsi_bufflen(cmd) >= 8
		    && dir != DMA_NONE && ptr && (ptr->Vers & 0x07) >= 2)
			dcb->inquiry7 = ptr->Flags;

	/*अगर( srb->cmd->cmnd[0] == INQUIRY && */
	/*  (host_byte(cmd->result) == DID_OK || status_byte(cmd->result) & CHECK_CONDITION) ) */
		अगर ((cmd->result == (DID_OK << 16) ||
		     status_byte(cmd->result) == CHECK_CONDITION)) अणु
			अगर (!dcb->init_tcq_flag) अणु
				add_dev(acb, dcb, ptr);
				dcb->init_tcq_flag = 1;
			पूर्ण
		पूर्ण

		scsi_kunmap_atomic_sg(base);
		local_irq_restore(flags);
	पूर्ण

	/* Here is the info क्रम Doug Gilbert's sg3 ... */
	scsi_set_resid(cmd, srb->total_xfer_length);
	/* This may be पूर्णांकerpreted by sb. or not ... */
	cmd->SCp.this_residual = srb->total_xfer_length;
	cmd->SCp.buffers_residual = 0;
	अगर (debug_enabled(DBG_KG)) अणु
		अगर (srb->total_xfer_length)
			dprपूर्णांकkdbg(DBG_KG, "srb_done: (0x%p) <%02i-%i> "
				"cmnd=0x%02x Missed %i bytes\n",
				cmd, cmd->device->id, (u8)cmd->device->lun,
				cmd->cmnd[0], srb->total_xfer_length);
	पूर्ण

	अगर (srb != acb->पंचांगp_srb) अणु
		/* Add to मुक्त list */
		dprपूर्णांकkdbg(DBG_0, "srb_done: (0x%p) done result=0x%08x\n",
			cmd, cmd->result);
		list_move_tail(&srb->list, &acb->srb_मुक्त_list);
	पूर्ण अन्यथा अणु
		dprपूर्णांकkl(KERN_ERR, "srb_done: ERROR! Completed cmd with tmp_srb\n");
	पूर्ण

	cmd->scsi_करोne(cmd);
	रुकोing_process_next(acb);
पूर्ण


/* पात all cmds in our queues */
अटल व्योम करोing_srb_करोne(काष्ठा AdapterCtlBlk *acb, u8 did_flag,
		काष्ठा scsi_cmnd *cmd, u8 क्रमce)
अणु
	काष्ठा DeviceCtlBlk *dcb;
	dprपूर्णांकkl(KERN_INFO, "doing_srb_done: pids ");

	list_क्रम_each_entry(dcb, &acb->dcb_list, list) अणु
		काष्ठा ScsiReqBlk *srb;
		काष्ठा ScsiReqBlk *पंचांगp;
		काष्ठा scsi_cmnd *p;

		list_क्रम_each_entry_safe(srb, पंचांगp, &dcb->srb_going_list, list) अणु
			पूर्णांक result;

			p = srb->cmd;
			result = MK_RES(0, did_flag, 0, 0);
			prपूर्णांकk("G:%p(%02i-%i) ", p,
			       p->device->id, (u8)p->device->lun);
			list_del(&srb->list);
			मुक्त_tag(dcb, srb);
			list_add_tail(&srb->list, &acb->srb_मुक्त_list);
			p->result = result;
			pci_unmap_srb_sense(acb, srb);
			pci_unmap_srb(acb, srb);
			अगर (क्रमce) अणु
				/* For new EH, we normally करोn't need to give commands back,
				 * as they all complete or all समय out */
				p->scsi_करोne(p);
			पूर्ण
		पूर्ण
		अगर (!list_empty(&dcb->srb_going_list))
			dprपूर्णांकkl(KERN_DEBUG, 
			       "How could the ML send cmnds to the Going queue? <%02i-%i>\n",
			       dcb->target_id, dcb->target_lun);
		अगर (dcb->tag_mask)
			dprपूर्णांकkl(KERN_DEBUG,
			       "tag_mask for <%02i-%i> should be empty, is %08x!\n",
			       dcb->target_id, dcb->target_lun,
			       dcb->tag_mask);

		/* Waiting queue */
		list_क्रम_each_entry_safe(srb, पंचांगp, &dcb->srb_रुकोing_list, list) अणु
			पूर्णांक result;
			p = srb->cmd;

			result = MK_RES(0, did_flag, 0, 0);
			prपूर्णांकk("W:%p<%02i-%i>", p, p->device->id,
			       (u8)p->device->lun);
			list_move_tail(&srb->list, &acb->srb_मुक्त_list);
			p->result = result;
			pci_unmap_srb_sense(acb, srb);
			pci_unmap_srb(acb, srb);
			अगर (क्रमce) अणु
				/* For new EH, we normally करोn't need to give commands back,
				 * as they all complete or all समय out */
				cmd->scsi_करोne(cmd);
			पूर्ण
		पूर्ण
		अगर (!list_empty(&dcb->srb_रुकोing_list))
			dprपूर्णांकkl(KERN_DEBUG, "ML queued %i cmnds again to <%02i-%i>\n",
			     list_size(&dcb->srb_रुकोing_list), dcb->target_id,
			     dcb->target_lun);
		dcb->flag &= ~ABORT_DEV_;
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण


अटल व्योम reset_scsi_bus(काष्ठा AdapterCtlBlk *acb)
अणु
	dprपूर्णांकkdbg(DBG_0, "reset_scsi_bus: acb=%p\n", acb);
	acb->acb_flag |= RESET_DEV;	/* RESET_DETECT, RESET_DONE, RESET_DEV */
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_RSTSCSI);

	जबतक (!(DC395x_पढ़ो8(acb, TRM_S1040_SCSI_INTSTATUS) & INT_SCSIRESET))
		/* nothing */;
पूर्ण


अटल व्योम set_basic_config(काष्ठा AdapterCtlBlk *acb)
अणु
	u8 bval;
	u16 wval;
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_TIMEOUT, acb->sel_समयout);
	अगर (acb->config & HCC_PARITY)
		bval = PHASELATCH | INITIATOR | BLOCKRST | PARITYCHECK;
	अन्यथा
		bval = PHASELATCH | INITIATOR | BLOCKRST;

	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONFIG0, bval);

	/* program configuration 1: Act_Neg (+ Act_Neg_Enh? + Fast_Filter? + DataDis?) */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONFIG1, 0x03);	/* was 0x13: शेष */
	/* program Host ID                  */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_HOSTID, acb->scsi_host->this_id);
	/* set ansynchronous transfer       */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_OFFSET, 0x00);
	/* Turn LED control off */
	wval = DC395x_पढ़ो16(acb, TRM_S1040_GEN_CONTROL) & 0x7F;
	DC395x_ग_लिखो16(acb, TRM_S1040_GEN_CONTROL, wval);
	/* DMA config          */
	wval = DC395x_पढ़ो16(acb, TRM_S1040_DMA_CONFIG) & ~DMA_FIFO_CTRL;
	wval |=
	    DMA_FIFO_HALF_HALF | DMA_ENHANCE /*| DMA_MEM_MULTI_READ */ ;
	DC395x_ग_लिखो16(acb, TRM_S1040_DMA_CONFIG, wval);
	/* Clear pending पूर्णांकerrupt status */
	DC395x_पढ़ो8(acb, TRM_S1040_SCSI_INTSTATUS);
	/* Enable SCSI पूर्णांकerrupt    */
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_INTEN, 0x7F);
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_INTEN, EN_SCSIINTR | EN_DMAXFERERROR
		      /*| EN_DMAXFERABORT | EN_DMAXFERCOMP | EN_FORCEDMACOMP */
		      );
पूर्ण


अटल व्योम scsi_reset_detect(काष्ठा AdapterCtlBlk *acb)
अणु
	dprपूर्णांकkl(KERN_INFO, "scsi_reset_detect: acb=%p\n", acb);
	/* delay half a second */
	अगर (समयr_pending(&acb->रुकोing_समयr))
		del_समयr(&acb->रुकोing_समयr);

	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONTROL, DO_RSTMODULE);
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, DMARESETMODULE);
	/*DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL,STOPDMAXFER); */
	udelay(500);
	/* Maybe we locked up the bus? Then lets रुको even दीर्घer ... */
	acb->last_reset =
	    jअगरfies + 5 * HZ / 2 +
	    HZ * acb->eeprom.delay_समय;

	clear_fअगरo(acb, "scsi_reset_detect");
	set_basic_config(acb);
	/*1.25 */
	/*DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT); */

	अगर (acb->acb_flag & RESET_DEV) अणु	/* RESET_DETECT, RESET_DONE, RESET_DEV */
		acb->acb_flag |= RESET_DONE;
	पूर्ण अन्यथा अणु
		acb->acb_flag |= RESET_DETECT;
		reset_dev_param(acb);
		करोing_srb_करोne(acb, DID_RESET, शून्य, 1);
		/*DC395x_RecoverSRB( acb ); */
		acb->active_dcb = शून्य;
		acb->acb_flag = 0;
		रुकोing_process_next(acb);
	पूर्ण
पूर्ण


अटल व्योम request_sense(काष्ठा AdapterCtlBlk *acb, काष्ठा DeviceCtlBlk *dcb,
		काष्ठा ScsiReqBlk *srb)
अणु
	काष्ठा scsi_cmnd *cmd = srb->cmd;
	dprपूर्णांकkdbg(DBG_1, "request_sense: (0x%p) <%02i-%i>\n",
		cmd, cmd->device->id, (u8)cmd->device->lun);

	srb->flag |= AUTO_REQSENSE;
	srb->adapter_status = 0;
	srb->target_status = 0;

	/* KG: Can this prevent crap sense data ? */
	स_रखो(cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);

	/* Save some data */
	srb->segment_x[DC395x_MAX_SG_LISTENTRY - 1].address =
	    srb->segment_x[0].address;
	srb->segment_x[DC395x_MAX_SG_LISTENTRY - 1].length =
	    srb->segment_x[0].length;
	srb->xferred = srb->total_xfer_length;
	/* srb->segment_x : a one entry of S/G list table */
	srb->total_xfer_length = SCSI_SENSE_BUFFERSIZE;
	srb->segment_x[0].length = SCSI_SENSE_BUFFERSIZE;
	/* Map sense buffer */
	srb->segment_x[0].address = dma_map_single(&acb->dev->dev,
			cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE,
			DMA_FROM_DEVICE);
	dprपूर्णांकkdbg(DBG_SG, "request_sense: map buffer %p->%08x(%05x)\n",
	       cmd->sense_buffer, srb->segment_x[0].address,
	       SCSI_SENSE_BUFFERSIZE);
	srb->sg_count = 1;
	srb->sg_index = 0;

	अगर (start_scsi(acb, dcb, srb)) अणु	/* Should only happen, अगर sb. अन्यथा grअसल the bus */
		dprपूर्णांकkl(KERN_DEBUG,
			"request_sense: (0x%p) failed <%02i-%i>\n",
			srb->cmd, dcb->target_id, dcb->target_lun);
		list_move(&srb->list, &dcb->srb_रुकोing_list);
		रुकोing_set_समयr(acb, HZ / 100);
	पूर्ण
पूर्ण


/**
 * device_alloc - Allocate a new device instance. This create the
 * devices instance and sets up all the data items. The adapter
 * instance is required to obtain confiuration inक्रमmation क्रम this
 * device. This करोes *not* add this device to the adapters device
 * list.
 *
 * @acb: The adapter to obtain configuration inक्रमmation from.
 * @target: The target क्रम the new device.
 * @lun: The lun क्रम the new device.
 *
 * Return the new device अगर successful or शून्य on failure.
 **/
अटल काष्ठा DeviceCtlBlk *device_alloc(काष्ठा AdapterCtlBlk *acb,
		u8 target, u8 lun)
अणु
	काष्ठा NvRamType *eeprom = &acb->eeprom;
	u8 period_index = eeprom->target[target].period & 0x07;
	काष्ठा DeviceCtlBlk *dcb;

	dcb = kदो_स्मृति(माप(काष्ठा DeviceCtlBlk), GFP_ATOMIC);
	dprपूर्णांकkdbg(DBG_0, "device_alloc: <%02i-%i>\n", target, lun);
	अगर (!dcb)
		वापस शून्य;
	dcb->acb = शून्य;
	INIT_LIST_HEAD(&dcb->srb_going_list);
	INIT_LIST_HEAD(&dcb->srb_रुकोing_list);
	dcb->active_srb = शून्य;
	dcb->tag_mask = 0;
	dcb->max_command = 1;
	dcb->target_id = target;
	dcb->target_lun = lun;
	dcb->dev_mode = eeprom->target[target].cfg0;
#अगर_अघोषित DC395x_NO_DISCONNECT
	dcb->identअगरy_msg =
	    IDENTIFY(dcb->dev_mode & NTC_DO_DISCONNECT, lun);
#अन्यथा
	dcb->identअगरy_msg = IDENTIFY(0, lun);
#पूर्ण_अगर
	dcb->inquiry7 = 0;
	dcb->sync_mode = 0;
	dcb->min_nego_period = घड़ी_period[period_index];
	dcb->sync_period = 0;
	dcb->sync_offset = 0;
	dcb->flag = 0;

#अगर_अघोषित DC395x_NO_WIDE
	अगर ((dcb->dev_mode & NTC_DO_WIDE_NEGO)
	    && (acb->config & HCC_WIDE_CARD))
		dcb->sync_mode |= WIDE_NEGO_ENABLE;
#पूर्ण_अगर
#अगर_अघोषित DC395x_NO_SYNC
	अगर (dcb->dev_mode & NTC_DO_SYNC_NEGO)
		अगर (!(lun) || current_sync_offset)
			dcb->sync_mode |= SYNC_NEGO_ENABLE;
#पूर्ण_अगर
	अगर (dcb->target_lun != 0) अणु
		/* Copy settings */
		काष्ठा DeviceCtlBlk *p;
		list_क्रम_each_entry(p, &acb->dcb_list, list)
			अगर (p->target_id == dcb->target_id)
				अवरोध;
		dprपूर्णांकkdbg(DBG_1, 
		       "device_alloc: <%02i-%i> copy from <%02i-%i>\n",
		       dcb->target_id, dcb->target_lun,
		       p->target_id, p->target_lun);
		dcb->sync_mode = p->sync_mode;
		dcb->sync_period = p->sync_period;
		dcb->min_nego_period = p->min_nego_period;
		dcb->sync_offset = p->sync_offset;
		dcb->inquiry7 = p->inquiry7;
	पूर्ण
	वापस dcb;
पूर्ण


/**
 * adapter_add_device - Adds the device instance to the adaptor instance.
 *
 * @acb: The adapter device to be updated
 * @dcb: A newly created and initialised device instance to add.
 **/
अटल व्योम adapter_add_device(काष्ठा AdapterCtlBlk *acb,
		काष्ठा DeviceCtlBlk *dcb)
अणु
	/* backpoपूर्णांकer to adapter */
	dcb->acb = acb;
	
	/* set run_robin to this device अगर it is currently empty */
	अगर (list_empty(&acb->dcb_list))
		acb->dcb_run_robin = dcb;

	/* add device to list */
	list_add_tail(&dcb->list, &acb->dcb_list);

	/* update device maps */
	acb->dcb_map[dcb->target_id] |= (1 << dcb->target_lun);
	acb->children[dcb->target_id][dcb->target_lun] = dcb;
पूर्ण


/**
 * adapter_हटाओ_device - Removes the device instance from the adaptor
 * instance. The device instance is not check in any way or मुक्तd by this. 
 * The caller is expected to take care of that. This will simply हटाओ the
 * device from the adapters data strcutures.
 *
 * @acb: The adapter device to be updated
 * @dcb: A device that has previously been added to the adapter.
 **/
अटल व्योम adapter_हटाओ_device(काष्ठा AdapterCtlBlk *acb,
		काष्ठा DeviceCtlBlk *dcb)
अणु
	काष्ठा DeviceCtlBlk *i;
	काष्ठा DeviceCtlBlk *पंचांगp;
	dprपूर्णांकkdbg(DBG_0, "adapter_remove_device: <%02i-%i>\n",
		dcb->target_id, dcb->target_lun);

	/* fix up any poपूर्णांकers to this device that we have in the adapter */
	अगर (acb->active_dcb == dcb)
		acb->active_dcb = शून्य;
	अगर (acb->dcb_run_robin == dcb)
		acb->dcb_run_robin = dcb_get_next(&acb->dcb_list, dcb);

	/* unlink from list */
	list_क्रम_each_entry_safe(i, पंचांगp, &acb->dcb_list, list)
		अगर (dcb == i) अणु
			list_del(&i->list);
			अवरोध;
		पूर्ण

	/* clear map and children */	
	acb->dcb_map[dcb->target_id] &= ~(1 << dcb->target_lun);
	acb->children[dcb->target_id][dcb->target_lun] = शून्य;
	dcb->acb = शून्य;
पूर्ण


/**
 * adapter_हटाओ_and_मुक्त_device - Removes a single device from the adapter
 * and then मुक्तs the device inक्रमmation.
 *
 * @acb: The adapter device to be updated
 * @dcb: A device that has previously been added to the adapter.
 */
अटल व्योम adapter_हटाओ_and_मुक्त_device(काष्ठा AdapterCtlBlk *acb,
		काष्ठा DeviceCtlBlk *dcb)
अणु
	अगर (list_size(&dcb->srb_going_list) > 1) अणु
		dprपूर्णांकkdbg(DBG_1, "adapter_remove_and_free_device: <%02i-%i> "
		           "Won't remove because of %i active requests.\n",
			   dcb->target_id, dcb->target_lun,
			   list_size(&dcb->srb_going_list));
		वापस;
	पूर्ण
	adapter_हटाओ_device(acb, dcb);
	kमुक्त(dcb);
पूर्ण


/**
 * adapter_हटाओ_and_मुक्त_all_devices - Removes and मुक्तs all of the
 * devices associated with the specअगरied adapter.
 *
 * @acb: The adapter from which all devices should be हटाओd.
 **/
अटल व्योम adapter_हटाओ_and_मुक्त_all_devices(काष्ठा AdapterCtlBlk* acb)
अणु
	काष्ठा DeviceCtlBlk *dcb;
	काष्ठा DeviceCtlBlk *पंचांगp;
	dprपूर्णांकkdbg(DBG_1, "adapter_remove_and_free_all_devices: num=%i\n",
		   list_size(&acb->dcb_list));

	list_क्रम_each_entry_safe(dcb, पंचांगp, &acb->dcb_list, list)
		adapter_हटाओ_and_मुक्त_device(acb, dcb);
पूर्ण


/**
 * dc395x_slave_alloc - Called by the scsi mid layer to tell us about a new
 * scsi device that we need to deal with. We allocate a new device and then
 * insert that device पूर्णांकo the adapters device list.
 *
 * @scsi_device: The new scsi device that we need to handle.
 **/
अटल पूर्णांक dc395x_slave_alloc(काष्ठा scsi_device *scsi_device)
अणु
	काष्ठा AdapterCtlBlk *acb = (काष्ठा AdapterCtlBlk *)scsi_device->host->hostdata;
	काष्ठा DeviceCtlBlk *dcb;

	dcb = device_alloc(acb, scsi_device->id, scsi_device->lun);
	अगर (!dcb)
		वापस -ENOMEM;
	adapter_add_device(acb, dcb);

	वापस 0;
पूर्ण


/**
 * dc395x_slave_destroy - Called by the scsi mid layer to tell us about a
 * device that is going away.
 *
 * @scsi_device: The new scsi device that we need to handle.
 **/
अटल व्योम dc395x_slave_destroy(काष्ठा scsi_device *scsi_device)
अणु
	काष्ठा AdapterCtlBlk *acb = (काष्ठा AdapterCtlBlk *)scsi_device->host->hostdata;
	काष्ठा DeviceCtlBlk *dcb = find_dcb(acb, scsi_device->id, scsi_device->lun);
	अगर (dcb)
		adapter_हटाओ_and_मुक्त_device(acb, dcb);
पूर्ण




/**
 * trms1040_रुको_30us: रुको क्रम 30 us
 *
 * Waits क्रम 30us (using the chip by the looks of it..)
 *
 * @io_port: base I/O address
 **/
अटल व्योम trms1040_रुको_30us(अचिन्हित दीर्घ io_port)
अणु
	/* ScsiPortStallExecution(30); रुको 30 us */
	outb(5, io_port + TRM_S1040_GEN_TIMER);
	जबतक (!(inb(io_port + TRM_S1040_GEN_STATUS) & GTIMEOUT))
		/* nothing */ ;
पूर्ण


/**
 * trms1040_ग_लिखो_cmd - ग_लिखो the secअगरied command and address to
 * chip
 *
 * @io_port:	base I/O address
 * @cmd:	SB + op code (command) to send
 * @addr:	address to send
 **/
अटल व्योम trms1040_ग_लिखो_cmd(अचिन्हित दीर्घ io_port, u8 cmd, u8 addr)
अणु
	पूर्णांक i;
	u8 send_data;

	/* program SB + OP code */
	क्रम (i = 0; i < 3; i++, cmd <<= 1) अणु
		send_data = NVR_SELECT;
		अगर (cmd & 0x04)	/* Start from bit 2 */
			send_data |= NVR_BITOUT;

		outb(send_data, io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);
		outb((send_data | NVR_CLOCK),
		     io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);
	पूर्ण

	/* send address */
	क्रम (i = 0; i < 7; i++, addr <<= 1) अणु
		send_data = NVR_SELECT;
		अगर (addr & 0x40)	/* Start from bit 6 */
			send_data |= NVR_BITOUT;

		outb(send_data, io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);
		outb((send_data | NVR_CLOCK),
		     io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);
	पूर्ण
	outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_रुको_30us(io_port);
पूर्ण


/**
 * trms1040_set_data - store a single byte in the eeprom
 *
 * Called from ग_लिखो all to ग_लिखो a single byte पूर्णांकo the SSEEPROM
 * Which is करोne one bit at a समय.
 *
 * @io_port:	base I/O address
 * @addr:	offset पूर्णांकo EEPROM
 * @byte:	bytes to ग_लिखो
 **/
अटल व्योम trms1040_set_data(अचिन्हित दीर्घ io_port, u8 addr, u8 byte)
अणु
	पूर्णांक i;
	u8 send_data;

	/* Send ग_लिखो command & address */
	trms1040_ग_लिखो_cmd(io_port, 0x05, addr);

	/* Write data */
	क्रम (i = 0; i < 8; i++, byte <<= 1) अणु
		send_data = NVR_SELECT;
		अगर (byte & 0x80)	/* Start from bit 7 */
			send_data |= NVR_BITOUT;

		outb(send_data, io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);
		outb((send_data | NVR_CLOCK), io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);
	पूर्ण
	outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_रुको_30us(io_port);

	/* Disable chip select */
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_रुको_30us(io_port);

	outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_रुको_30us(io_port);

	/* Wait क्रम ग_लिखो पढ़ोy */
	जबतक (1) अणु
		outb((NVR_SELECT | NVR_CLOCK), io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);

		outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);

		अगर (inb(io_port + TRM_S1040_GEN_NVRAM) & NVR_BITIN)
			अवरोध;
	पूर्ण

	/*  Disable chip select */
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
पूर्ण


/**
 * trms1040_ग_लिखो_all - ग_लिखो 128 bytes to the eeprom
 *
 * Write the supplied 128 bytes to the chips SEEPROM
 *
 * @eeprom:	the data to ग_लिखो
 * @io_port:	the base io port
 **/
अटल व्योम trms1040_ग_लिखो_all(काष्ठा NvRamType *eeprom, अचिन्हित दीर्घ io_port)
अणु
	u8 *b_eeprom = (u8 *)eeprom;
	u8 addr;

	/* Enable SEEPROM */
	outb((inb(io_port + TRM_S1040_GEN_CONTROL) | EN_EEPROM),
	     io_port + TRM_S1040_GEN_CONTROL);

	/* ग_लिखो enable */
	trms1040_ग_लिखो_cmd(io_port, 0x04, 0xFF);
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_रुको_30us(io_port);

	/* ग_लिखो */
	क्रम (addr = 0; addr < 128; addr++, b_eeprom++)
		trms1040_set_data(io_port, addr, *b_eeprom);

	/* ग_लिखो disable */
	trms1040_ग_लिखो_cmd(io_port, 0x04, 0x00);
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_रुको_30us(io_port);

	/* Disable SEEPROM */
	outb((inb(io_port + TRM_S1040_GEN_CONTROL) & ~EN_EEPROM),
	     io_port + TRM_S1040_GEN_CONTROL);
पूर्ण


/**
 * trms1040_get_data - get a single byte from the eeprom
 *
 * Called from पढ़ो all to पढ़ो a single byte पूर्णांकo the SSEEPROM
 * Which is करोne one bit at a समय.
 *
 * @io_port:	base I/O address
 * @addr:	offset पूर्णांकo SEEPROM
 *
 * Returns the byte पढ़ो.
 **/
अटल u8 trms1040_get_data(अचिन्हित दीर्घ io_port, u8 addr)
अणु
	पूर्णांक i;
	u8 पढ़ो_byte;
	u8 result = 0;

	/* Send पढ़ो command & address */
	trms1040_ग_लिखो_cmd(io_port, 0x06, addr);

	/* पढ़ो data */
	क्रम (i = 0; i < 8; i++) अणु
		outb((NVR_SELECT | NVR_CLOCK), io_port + TRM_S1040_GEN_NVRAM);
		trms1040_रुको_30us(io_port);
		outb(NVR_SELECT, io_port + TRM_S1040_GEN_NVRAM);

		/* Get data bit जबतक falling edge */
		पढ़ो_byte = inb(io_port + TRM_S1040_GEN_NVRAM);
		result <<= 1;
		अगर (पढ़ो_byte & NVR_BITIN)
			result |= 1;

		trms1040_रुको_30us(io_port);
	पूर्ण

	/* Disable chip select */
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
	वापस result;
पूर्ण


/**
 * trms1040_पढ़ो_all - पढ़ो all bytes from the eeprom
 *
 * Read the 128 bytes from the SEEPROM.
 *
 * @eeprom:	where to store the data
 * @io_port:	the base io port
 **/
अटल व्योम trms1040_पढ़ो_all(काष्ठा NvRamType *eeprom, अचिन्हित दीर्घ io_port)
अणु
	u8 *b_eeprom = (u8 *)eeprom;
	u8 addr;

	/* Enable SEEPROM */
	outb((inb(io_port + TRM_S1040_GEN_CONTROL) | EN_EEPROM),
	     io_port + TRM_S1040_GEN_CONTROL);

	/* पढ़ो details */
	क्रम (addr = 0; addr < 128; addr++, b_eeprom++)
		*b_eeprom = trms1040_get_data(io_port, addr);

	/* Disable SEEPROM */
	outb((inb(io_port + TRM_S1040_GEN_CONTROL) & ~EN_EEPROM),
	     io_port + TRM_S1040_GEN_CONTROL);
पूर्ण



/**
 * check_eeprom - get and check contents of the eeprom
 *
 * Read seeprom 128 bytes पूर्णांकo the memory provider in eeprom.
 * Checks the checksum and अगर it's not correct it uses a set of शेष
 * values.
 *
 * @eeprom:	caller allocated strcuture to पढ़ो the eeprom data पूर्णांकo
 * @io_port:	io port to पढ़ो from
 **/
अटल व्योम check_eeprom(काष्ठा NvRamType *eeprom, अचिन्हित दीर्घ io_port)
अणु
	u16 *w_eeprom = (u16 *)eeprom;
	u16 w_addr;
	u16 cksum;
	u32 d_addr;
	u32 *d_eeprom;

	trms1040_पढ़ो_all(eeprom, io_port);	/* पढ़ो eeprom */

	cksum = 0;
	क्रम (w_addr = 0, w_eeprom = (u16 *)eeprom; w_addr < 64;
	     w_addr++, w_eeprom++)
		cksum += *w_eeprom;
	अगर (cksum != 0x1234) अणु
		/*
		 * Checksum is wrong.
		 * Load a set of शेषs पूर्णांकo the eeprom buffer
		 */
		dprपूर्णांकkl(KERN_WARNING,
			"EEProm checksum error: using default values and options.\n");
		eeprom->sub_venकरोr_id[0] = (u8)PCI_VENDOR_ID_TEKRAM;
		eeprom->sub_venकरोr_id[1] = (u8)(PCI_VENDOR_ID_TEKRAM >> 8);
		eeprom->sub_sys_id[0] = (u8)PCI_DEVICE_ID_TEKRAM_TRMS1040;
		eeprom->sub_sys_id[1] =
		    (u8)(PCI_DEVICE_ID_TEKRAM_TRMS1040 >> 8);
		eeprom->sub_class = 0x00;
		eeprom->venकरोr_id[0] = (u8)PCI_VENDOR_ID_TEKRAM;
		eeprom->venकरोr_id[1] = (u8)(PCI_VENDOR_ID_TEKRAM >> 8);
		eeprom->device_id[0] = (u8)PCI_DEVICE_ID_TEKRAM_TRMS1040;
		eeprom->device_id[1] =
		    (u8)(PCI_DEVICE_ID_TEKRAM_TRMS1040 >> 8);
		eeprom->reserved = 0x00;

		क्रम (d_addr = 0, d_eeprom = (u32 *)eeprom->target;
		     d_addr < 16; d_addr++, d_eeprom++)
			*d_eeprom = 0x00000077;	/* cfg3,cfg2,period,cfg0 */

		*d_eeprom++ = 0x04000F07;	/* max_tag,delay_समय,channel_cfg,scsi_id */
		*d_eeprom++ = 0x00000015;	/* reserved1,boot_lun,boot_target,reserved0 */
		क्रम (d_addr = 0; d_addr < 12; d_addr++, d_eeprom++)
			*d_eeprom = 0x00;

		/* Now load शेषs (maybe set by boot/module params) */
		set_safe_settings();
		fix_settings();
		eeprom_override(eeprom);

		eeprom->cksum = 0x00;
		क्रम (w_addr = 0, cksum = 0, w_eeprom = (u16 *)eeprom;
		     w_addr < 63; w_addr++, w_eeprom++)
			cksum += *w_eeprom;

		*w_eeprom = 0x1234 - cksum;
		trms1040_ग_लिखो_all(eeprom, io_port);
		eeprom->delay_समय = cfg_data[CFG_RESET_DELAY].value;
	पूर्ण अन्यथा अणु
		set_safe_settings();
		eeprom_index_to_delay(eeprom);
		eeprom_override(eeprom);
	पूर्ण
पूर्ण


/**
 * prपूर्णांक_eeprom_settings - output the eeprom settings
 * to the kernel log so people can see what they were.
 *
 * @eeprom: The eeprom data strucutre to show details क्रम.
 **/
अटल व्योम prपूर्णांक_eeprom_settings(काष्ठा NvRamType *eeprom)
अणु
	dprपूर्णांकkl(KERN_INFO, "Used settings: AdapterID=%02i, Speed=%i(%02i.%01iMHz), dev_mode=0x%02x\n",
		eeprom->scsi_id,
		eeprom->target[0].period,
		घड़ी_speed[eeprom->target[0].period] / 10,
		घड़ी_speed[eeprom->target[0].period] % 10,
		eeprom->target[0].cfg0);
	dprपूर्णांकkl(KERN_INFO, "               AdaptMode=0x%02x, Tags=%i(%02i), DelayReset=%is\n",
		eeprom->channel_cfg, eeprom->max_tag,
		1 << eeprom->max_tag, eeprom->delay_समय);
पूर्ण


/* Free SG tables */
अटल व्योम adapter_sg_tables_मुक्त(काष्ठा AdapterCtlBlk *acb)
अणु
	पूर्णांक i;
	स्थिर अचिन्हित srbs_per_page = PAGE_SIZE/SEGMENTX_LEN;

	क्रम (i = 0; i < DC395x_MAX_SRB_CNT; i += srbs_per_page)
		kमुक्त(acb->srb_array[i].segment_x);
पूर्ण


/*
 * Allocate SG tables; as we have to pci_map them, an SG list (काष्ठा SGentry*)
 * should never cross a page boundary */
अटल पूर्णांक adapter_sg_tables_alloc(काष्ठा AdapterCtlBlk *acb)
अणु
	स्थिर अचिन्हित mem_needed = (DC395x_MAX_SRB_CNT+1)
	                            *SEGMENTX_LEN;
	पूर्णांक pages = (mem_needed+(PAGE_SIZE-1))/PAGE_SIZE;
	स्थिर अचिन्हित srbs_per_page = PAGE_SIZE/SEGMENTX_LEN;
	पूर्णांक srb_idx = 0;
	अचिन्हित i = 0;
	काष्ठा SGentry *ptr;

	क्रम (i = 0; i < DC395x_MAX_SRB_CNT; i++)
		acb->srb_array[i].segment_x = शून्य;

	dprपूर्णांकkdbg(DBG_1, "Allocate %i pages for SG tables\n", pages);
	जबतक (pages--) अणु
		ptr = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
		अगर (!ptr) अणु
			adapter_sg_tables_मुक्त(acb);
			वापस 1;
		पूर्ण
		dprपूर्णांकkdbg(DBG_1, "Allocate %li bytes at %p for SG segments %i\n",
			PAGE_SIZE, ptr, srb_idx);
		i = 0;
		जबतक (i < srbs_per_page && srb_idx < DC395x_MAX_SRB_CNT)
			acb->srb_array[srb_idx++].segment_x =
			    ptr + (i++ * DC395x_MAX_SG_LISTENTRY);
	पूर्ण
	अगर (i < srbs_per_page)
		acb->srb.segment_x =
		    ptr + (i * DC395x_MAX_SG_LISTENTRY);
	अन्यथा
		dprपूर्णांकkl(KERN_DEBUG, "No space for tmsrb SG table reserved?!\n");
	वापस 0;
पूर्ण



/**
 * adapter_prपूर्णांक_config - prपूर्णांक adapter connection and termination
 * config
 *
 * The io port in the adapter needs to have been set beक्रमe calling
 * this function.
 *
 * @acb: The adapter to prपूर्णांक the inक्रमmation क्रम.
 **/
अटल व्योम adapter_prपूर्णांक_config(काष्ठा AdapterCtlBlk *acb)
अणु
	u8 bval;

	bval = DC395x_पढ़ो8(acb, TRM_S1040_GEN_STATUS);
	dprपूर्णांकkl(KERN_INFO, "%sConnectors: ",
		((bval & WIDESCSI) ? "(Wide) " : ""));
	अगर (!(bval & CON5068))
		prपूर्णांकk("ext%s ", !(bval & EXT68HIGH) ? "68" : "50");
	अगर (!(bval & CON68))
		prपूर्णांकk("int68%s ", !(bval & INT68HIGH) ? "" : "(50)");
	अगर (!(bval & CON50))
		prपूर्णांकk("int50 ");
	अगर ((bval & (CON5068 | CON50 | CON68)) ==
	    0 /*(CON5068 | CON50 | CON68) */ )
		prपूर्णांकk(" Oops! (All 3?) ");
	bval = DC395x_पढ़ो8(acb, TRM_S1040_GEN_CONTROL);
	prपूर्णांकk(" Termination: ");
	अगर (bval & DIS_TERM)
		prपूर्णांकk("Disabled\n");
	अन्यथा अणु
		अगर (bval & AUTOTERM)
			prपूर्णांकk("Auto ");
		अगर (bval & LOW8TERM)
			prपूर्णांकk("Low ");
		अगर (bval & UP8TERM)
			prपूर्णांकk("High ");
		prपूर्णांकk("\n");
	पूर्ण
पूर्ण


/**
 * adapter_init_params - Initialize the various parameters in the
 * adapter काष्ठाure. Note that the poपूर्णांकer to the scsi_host is set
 * early (when this instance is created) and the io_port and irq
 * values are set later after they have been reserved. This just माला_लो
 * everything set to a good starting position.
 *
 * The eeprom काष्ठाure in the adapter needs to have been set beक्रमe
 * calling this function.
 *
 * @acb: The adapter to initialize.
 **/
अटल व्योम adapter_init_params(काष्ठा AdapterCtlBlk *acb)
अणु
	काष्ठा NvRamType *eeprom = &acb->eeprom;
	पूर्णांक i;

	/* NOTE: acb->scsi_host is set at scsi_host/acb creation समय */
	/* NOTE: acb->io_port_base is set at port registration समय */
	/* NOTE: acb->io_port_len is set at port registration समय */

	INIT_LIST_HEAD(&acb->dcb_list);
	acb->dcb_run_robin = शून्य;
	acb->active_dcb = शून्य;

	INIT_LIST_HEAD(&acb->srb_मुक्त_list);
	/*  temp SRB क्रम Q tag used or पात command used  */
	acb->पंचांगp_srb = &acb->srb;
	समयr_setup(&acb->रुकोing_समयr, रुकोing_समयout, 0);
	समयr_setup(&acb->selto_समयr, शून्य, 0);

	acb->srb_count = DC395x_MAX_SRB_CNT;

	acb->sel_समयout = DC395x_SEL_TIMEOUT;	/* समयout=250ms */
	/* NOTE: acb->irq_level is set at IRQ registration समय */

	acb->tag_max_num = 1 << eeprom->max_tag;
	अगर (acb->tag_max_num > 30)
		acb->tag_max_num = 30;

	acb->acb_flag = 0;	/* RESET_DETECT, RESET_DONE, RESET_DEV */
	acb->gmode2 = eeprom->channel_cfg;
	acb->config = 0;	/* NOTE: actually set in adapter_init_chip */

	अगर (eeprom->channel_cfg & NAC_SCANLUN)
		acb->lun_chk = 1;
	acb->scan_devices = 1;

	acb->scsi_host->this_id = eeprom->scsi_id;
	acb->hostid_bit = (1 << acb->scsi_host->this_id);

	क्रम (i = 0; i < DC395x_MAX_SCSI_ID; i++)
		acb->dcb_map[i] = 0;

	acb->msg_len = 0;
	
	/* link अटल array of srbs पूर्णांकo the srb मुक्त list */
	क्रम (i = 0; i < acb->srb_count - 1; i++)
		list_add_tail(&acb->srb_array[i].list, &acb->srb_मुक्त_list);
पूर्ण


/**
 * adapter_init_scsi_host - Initialize the scsi host instance based on
 * values that we have alपढ़ोy stored in the adapter instance. There's
 * some mention that a lot of these are deprecated, so we won't use
 * them (we'll use the ones in the adapter instance) but we'll fill
 * them in in हाल something अन्यथा needs them.
 *
 * The eeprom काष्ठाure, irq and io ports in the adapter need to have
 * been set beक्रमe calling this function.
 *
 * @host: The scsi host instance to fill in the values क्रम.
 **/
अटल व्योम adapter_init_scsi_host(काष्ठा Scsi_Host *host)
अणु
        काष्ठा AdapterCtlBlk *acb = (काष्ठा AdapterCtlBlk *)host->hostdata;
	काष्ठा NvRamType *eeprom = &acb->eeprom;
        
	host->max_cmd_len = 24;
	host->can_queue = DC395x_MAX_CMD_QUEUE;
	host->cmd_per_lun = DC395x_MAX_CMD_PER_LUN;
	host->this_id = (पूर्णांक)eeprom->scsi_id;
	host->io_port = acb->io_port_base;
	host->n_io_port = acb->io_port_len;
	host->dma_channel = -1;
	host->unique_id = acb->io_port_base;
	host->irq = acb->irq_level;
	acb->last_reset = jअगरfies;

	host->max_id = 16;
	अगर (host->max_id - 1 == eeprom->scsi_id)
		host->max_id--;

	अगर (eeprom->channel_cfg & NAC_SCANLUN)
		host->max_lun = 8;
	अन्यथा
		host->max_lun = 1;
पूर्ण


/**
 * adapter_init_chip - Get the chip पूर्णांकo a know state and figure out
 * some of the settings that apply to this adapter.
 *
 * The io port in the adapter needs to have been set beक्रमe calling
 * this function. The config will be configured correctly on वापस.
 *
 * @acb: The adapter which we are to init.
 **/
अटल व्योम adapter_init_chip(काष्ठा AdapterCtlBlk *acb)
अणु
        काष्ठा NvRamType *eeprom = &acb->eeprom;
        
        /* Mask all the पूर्णांकerrupt */
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_INTEN, 0x00);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_INTEN, 0x00);

	/* Reset SCSI module */
	DC395x_ग_लिखो16(acb, TRM_S1040_SCSI_CONTROL, DO_RSTMODULE);

	/* Reset PCI/DMA module */
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_CONTROL, DMARESETMODULE);
	udelay(20);

	/* program configuration 0 */
	acb->config = HCC_AUTOTERM | HCC_PARITY;
	अगर (DC395x_पढ़ो8(acb, TRM_S1040_GEN_STATUS) & WIDESCSI)
		acb->config |= HCC_WIDE_CARD;

	अगर (eeprom->channel_cfg & NAC_POWERON_SCSI_RESET)
		acb->config |= HCC_SCSI_RESET;

	अगर (acb->config & HCC_SCSI_RESET) अणु
		dprपूर्णांकkl(KERN_INFO, "Performing initial SCSI bus reset\n");
		DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_CONTROL, DO_RSTSCSI);

		/*जबतक (!( DC395x_पढ़ो8(acb, TRM_S1040_SCSI_INTSTATUS) & INT_SCSIRESET )); */
		/*spin_unlock_irq (&io_request_lock); */
		udelay(500);

		acb->last_reset =
		    jअगरfies + HZ / 2 +
		    HZ * acb->eeprom.delay_समय;

		/*spin_lock_irq (&io_request_lock); */
	पूर्ण
पूर्ण


/**
 * adapter_init - Grab the resource क्रम the card, setup the adapter
 * inक्रमmation, set the card पूर्णांकo a known state, create the various
 * tables etc etc. This basically माला_लो all adapter inक्रमmation all up
 * to date, initialised and माला_लो the chip in sync with it.
 *
 * @acb:	The adapter which we are to init.
 * @io_port:	The base I/O port
 * @io_port_len: The I/O port size
 * @irq:	IRQ
 *
 * Returns 0 अगर the initialization succeeds, any other value on
 * failure.
 **/
अटल पूर्णांक adapter_init(काष्ठा AdapterCtlBlk *acb, अचिन्हित दीर्घ io_port,
			u32 io_port_len, अचिन्हित पूर्णांक irq)
अणु
	अगर (!request_region(io_port, io_port_len, DC395X_NAME)) अणु
		dprपूर्णांकkl(KERN_ERR, "Failed to reserve IO region 0x%lx\n", io_port);
		जाओ failed;
	पूर्ण
	/* store port base to indicate we have रेजिस्टरed it */
	acb->io_port_base = io_port;
	acb->io_port_len = io_port_len;
	
	अगर (request_irq(irq, dc395x_पूर्णांकerrupt, IRQF_SHARED, DC395X_NAME, acb)) अणु
	    	/* release the region we just claimed */
		dprपूर्णांकkl(KERN_INFO, "Failed to register IRQ\n");
		जाओ failed;
	पूर्ण
	/* store irq to indicate we have रेजिस्टरed it */
	acb->irq_level = irq;

	/* get eeprom configuration inक्रमmation and command line settings etc */
	check_eeprom(&acb->eeprom, io_port);
 	prपूर्णांक_eeprom_settings(&acb->eeprom);

	/* setup adapter control block */	
	adapter_init_params(acb);
	
	/* display card connectors/termination settings */
 	adapter_prपूर्णांक_config(acb);

	अगर (adapter_sg_tables_alloc(acb)) अणु
		dprपूर्णांकkl(KERN_DEBUG, "Memory allocation for SG tables failed\n");
		जाओ failed;
	पूर्ण
	adapter_init_scsi_host(acb->scsi_host);
	adapter_init_chip(acb);
	set_basic_config(acb);

	dprपूर्णांकkdbg(DBG_0,
		"adapter_init: acb=%p, pdcb_map=%p psrb_array=%p "
		"size{acb=0x%04x dcb=0x%04x srb=0x%04x}\n",
		acb, acb->dcb_map, acb->srb_array, माप(काष्ठा AdapterCtlBlk),
		माप(काष्ठा DeviceCtlBlk), माप(काष्ठा ScsiReqBlk));
	वापस 0;

failed:
	अगर (acb->irq_level)
		मुक्त_irq(acb->irq_level, acb);
	अगर (acb->io_port_base)
		release_region(acb->io_port_base, acb->io_port_len);
	adapter_sg_tables_मुक्त(acb);

	वापस 1;
पूर्ण


/**
 * adapter_uninit_chip - cleanly shut करोwn the scsi controller chip,
 * stopping all operations and disabling पूर्णांकerrupt generation on the
 * card.
 *
 * @acb: The adapter which we are to shutकरोwn.
 **/
अटल व्योम adapter_uninit_chip(काष्ठा AdapterCtlBlk *acb)
अणु
	/* disable पूर्णांकerrupts */
	DC395x_ग_लिखो8(acb, TRM_S1040_DMA_INTEN, 0);
	DC395x_ग_लिखो8(acb, TRM_S1040_SCSI_INTEN, 0);

	/* reset the scsi bus */
	अगर (acb->config & HCC_SCSI_RESET)
		reset_scsi_bus(acb);

	/* clear any pending पूर्णांकerrupt state */
	DC395x_पढ़ो8(acb, TRM_S1040_SCSI_INTSTATUS);
पूर्ण



/**
 * adapter_uninit - Shut करोwn the chip and release any resources that
 * we had allocated. Once this वापसs the adapter should not be used
 * anymore.
 *
 * @acb: The adapter which we are to un-initialize.
 **/
अटल व्योम adapter_uninit(काष्ठा AdapterCtlBlk *acb)
अणु
	अचिन्हित दीर्घ flags;
	DC395x_LOCK_IO(acb->scsi_host, flags);

	/* हटाओ समयrs */
	अगर (समयr_pending(&acb->रुकोing_समयr))
		del_समयr(&acb->रुकोing_समयr);
	अगर (समयr_pending(&acb->selto_समयr))
		del_समयr(&acb->selto_समयr);

	adapter_uninit_chip(acb);
	adapter_हटाओ_and_मुक्त_all_devices(acb);
	DC395x_UNLOCK_IO(acb->scsi_host, flags);

	अगर (acb->irq_level)
		मुक्त_irq(acb->irq_level, acb);
	अगर (acb->io_port_base)
		release_region(acb->io_port_base, acb->io_port_len);

	adapter_sg_tables_मुक्त(acb);
पूर्ण


#अघोषित YESNO
#घोषणा YESNO(YN) \
 अगर (YN) seq_म_लिखो(m, " Yes ");\
 अन्यथा seq_म_लिखो(m, " No  ")

अटल पूर्णांक dc395x_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	काष्ठा AdapterCtlBlk *acb = (काष्ठा AdapterCtlBlk *)host->hostdata;
	पूर्णांक spd, spd1;
	काष्ठा DeviceCtlBlk *dcb;
	अचिन्हित दीर्घ flags;
	पूर्णांक dev;

	seq_माला_दो(m, DC395X_BANNER " PCI SCSI Host Adapter\n"
		" Driver Version " DC395X_VERSION "\n");

	DC395x_LOCK_IO(acb->scsi_host, flags);

	seq_म_लिखो(m, "SCSI Host Nr %i, ", host->host_no);
	seq_म_लिखो(m, "DC395U/UW/F DC315/U %s\n",
		(acb->config & HCC_WIDE_CARD) ? "Wide" : "");
	seq_म_लिखो(m, "io_port_base 0x%04lx, ", acb->io_port_base);
	seq_म_लिखो(m, "irq_level 0x%04x, ", acb->irq_level);
	seq_म_लिखो(m, " SelTimeout %ims\n", (1638 * acb->sel_समयout) / 1000);

	seq_म_लिखो(m, "MaxID %i, MaxLUN %llu, ", host->max_id, host->max_lun);
	seq_म_लिखो(m, "AdapterID %i\n", host->this_id);

	seq_म_लिखो(m, "tag_max_num %i", acb->tag_max_num);
	/*seq_म_लिखो(m, ", DMA_Status %i\n", DC395x_पढ़ो8(acb, TRM_S1040_DMA_STATUS)); */
	seq_म_लिखो(m, ", FilterCfg 0x%02x",
		DC395x_पढ़ो8(acb, TRM_S1040_SCSI_CONFIG1));
	seq_म_लिखो(m, ", DelayReset %is\n", acb->eeprom.delay_समय);
	/*seq_म_लिखो(m, "\n"); */

	seq_म_लिखो(m, "Nr of DCBs: %i\n", list_size(&acb->dcb_list));
	seq_म_लिखो(m, "Map of attached LUNs: %8ph\n", &acb->dcb_map[0]);
	seq_म_लिखो(m, "                      %8ph\n", &acb->dcb_map[8]);

	seq_माला_दो(m,
		 "Un ID LUN Prty Sync Wide DsCn SndS TagQ nego_period SyncFreq SyncOffs MaxCmd\n");

	dev = 0;
	list_क्रम_each_entry(dcb, &acb->dcb_list, list) अणु
		पूर्णांक nego_period;
		seq_म_लिखो(m, "%02i %02i  %02i ", dev, dcb->target_id,
			dcb->target_lun);
		YESNO(dcb->dev_mode & NTC_DO_PARITY_CHK);
		YESNO(dcb->sync_offset);
		YESNO(dcb->sync_period & WIDE_SYNC);
		YESNO(dcb->dev_mode & NTC_DO_DISCONNECT);
		YESNO(dcb->dev_mode & NTC_DO_SEND_START);
		YESNO(dcb->sync_mode & EN_TAG_QUEUEING);
		nego_period = घड़ी_period[dcb->sync_period & 0x07] << 2;
		अगर (dcb->sync_offset)
			seq_म_लिखो(m, "  %03i ns ", nego_period);
		अन्यथा
			seq_म_लिखो(m, " (%03i ns)", (dcb->min_nego_period << 2));

		अगर (dcb->sync_offset & 0x0f) अणु
			spd = 1000 / (nego_period);
			spd1 = 1000 % (nego_period);
			spd1 = (spd1 * 10 + nego_period / 2) / (nego_period);
			seq_म_लिखो(m, "   %2i.%1i M     %02i ", spd, spd1,
				(dcb->sync_offset & 0x0f));
		पूर्ण अन्यथा
			seq_माला_दो(m, "                 ");

		/* Add more info ... */
		seq_म_लिखो(m, "     %02i\n", dcb->max_command);
		dev++;
	पूर्ण

	अगर (समयr_pending(&acb->रुकोing_समयr))
		seq_माला_दो(m, "Waiting queue timer running\n");
	अन्यथा
		seq_अ_दो(m, '\n');

	list_क्रम_each_entry(dcb, &acb->dcb_list, list) अणु
		काष्ठा ScsiReqBlk *srb;
		अगर (!list_empty(&dcb->srb_रुकोing_list))
			seq_म_लिखो(m, "DCB (%02i-%i): Waiting: %i:",
				dcb->target_id, dcb->target_lun,
				list_size(&dcb->srb_रुकोing_list));
                list_क्रम_each_entry(srb, &dcb->srb_रुकोing_list, list)
			seq_म_लिखो(m, " %p", srb->cmd);
		अगर (!list_empty(&dcb->srb_going_list))
			seq_म_लिखो(m, "\nDCB (%02i-%i): Going  : %i:",
				dcb->target_id, dcb->target_lun,
				list_size(&dcb->srb_going_list));
		list_क्रम_each_entry(srb, &dcb->srb_going_list, list)
			seq_म_लिखो(m, " %p", srb->cmd);
		अगर (!list_empty(&dcb->srb_रुकोing_list) || !list_empty(&dcb->srb_going_list))
			seq_अ_दो(m, '\n');
	पूर्ण

	अगर (debug_enabled(DBG_1)) अणु
		seq_म_लिखो(m, "DCB list for ACB %p:\n", acb);
		list_क्रम_each_entry(dcb, &acb->dcb_list, list) अणु
			seq_म_लिखो(m, "%p -> ", dcb);
		पूर्ण
		seq_माला_दो(m, "END\n");
	पूर्ण

	DC395x_UNLOCK_IO(acb->scsi_host, flags);
	वापस 0;
पूर्ण


अटल काष्ठा scsi_host_ढाँचा dc395x_driver_ढाँचा = अणु
	.module                 = THIS_MODULE,
	.proc_name              = DC395X_NAME,
	.show_info              = dc395x_show_info,
	.name                   = DC395X_BANNER " " DC395X_VERSION,
	.queuecommand           = dc395x_queue_command,
	.slave_alloc            = dc395x_slave_alloc,
	.slave_destroy          = dc395x_slave_destroy,
	.can_queue              = DC395x_MAX_CAN_QUEUE,
	.this_id                = 7,
	.sg_tablesize           = DC395x_MAX_SG_TABLESIZE,
	.cmd_per_lun            = DC395x_MAX_CMD_PER_LUN,
	.eh_पात_handler       = dc395x_eh_पात,
	.eh_bus_reset_handler   = dc395x_eh_bus_reset,
	.dma_boundary		= PAGE_SIZE - 1,
पूर्ण;


/**
 * banner_display - Display banner on first instance of driver
 * initialized.
 **/
अटल व्योम banner_display(व्योम)
अणु
	अटल पूर्णांक banner_करोne = 0;
	अगर (!banner_करोne)
	अणु
		dprपूर्णांकkl(KERN_INFO, "%s %s\n", DC395X_BANNER, DC395X_VERSION);
		banner_करोne = 1;
	पूर्ण
पूर्ण


/**
 * dc395x_init_one - Initialise a single instance of the adapter.
 *
 * The PCI layer will call this once क्रम each instance of the adapter
 * that it finds in the प्रणाली. The pci_dev strcuture indicates which
 * instance we are being called from.
 * 
 * @dev: The PCI device to initialize.
 * @id: Looks like a poपूर्णांकer to the entry in our pci device table
 * that was actually matched by the PCI subप्रणाली.
 *
 * Returns 0 on success, or an error code (-ve) on failure.
 **/
अटल पूर्णांक dc395x_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *scsi_host = शून्य;
	काष्ठा AdapterCtlBlk *acb = शून्य;
	अचिन्हित दीर्घ io_port_base;
	अचिन्हित पूर्णांक io_port_len;
	अचिन्हित पूर्णांक irq;
	
	dprपूर्णांकkdbg(DBG_0, "Init one instance (%s)\n", pci_name(dev));
	banner_display();

	अगर (pci_enable_device(dev))
	अणु
		dprपूर्णांकkl(KERN_INFO, "PCI Enable device failed.\n");
		वापस -ENODEV;
	पूर्ण
	io_port_base = pci_resource_start(dev, 0) & PCI_BASE_ADDRESS_IO_MASK;
	io_port_len = pci_resource_len(dev, 0);
	irq = dev->irq;
	dprपूर्णांकkdbg(DBG_0, "IO_PORT=0x%04lx, IRQ=0x%x\n", io_port_base, dev->irq);

	/* allocate scsi host inक्रमmation (includes out adapter) */
	scsi_host = scsi_host_alloc(&dc395x_driver_ढाँचा,
				    माप(काष्ठा AdapterCtlBlk));
	अगर (!scsi_host) अणु
		dprपूर्णांकkl(KERN_INFO, "scsi_host_alloc failed\n");
		जाओ fail;
	पूर्ण
 	acb = (काष्ठा AdapterCtlBlk*)scsi_host->hostdata;
 	acb->scsi_host = scsi_host;
 	acb->dev = dev;

	/* initialise the adapter and everything we need */
 	अगर (adapter_init(acb, io_port_base, io_port_len, irq)) अणु
		dprपूर्णांकkl(KERN_INFO, "adapter init failed\n");
		जाओ fail;
	पूर्ण

	pci_set_master(dev);

	/* get the scsi mid level to scan क्रम new devices on the bus */
	अगर (scsi_add_host(scsi_host, &dev->dev)) अणु
		dprपूर्णांकkl(KERN_ERR, "scsi_add_host failed\n");
		जाओ fail;
	पूर्ण
	pci_set_drvdata(dev, scsi_host);
	scsi_scan_host(scsi_host);
        	
	वापस 0;

fail:
	अगर (acb != शून्य)
		adapter_uninit(acb);
	अगर (scsi_host != शून्य)
		scsi_host_put(scsi_host);
	pci_disable_device(dev);
	वापस -ENODEV;
पूर्ण


/**
 * dc395x_हटाओ_one - Called to हटाओ a single instance of the
 * adapter.
 *
 * @dev: The PCI device to initialize.
 **/
अटल व्योम dc395x_हटाओ_one(काष्ठा pci_dev *dev)
अणु
	काष्ठा Scsi_Host *scsi_host = pci_get_drvdata(dev);
	काष्ठा AdapterCtlBlk *acb = (काष्ठा AdapterCtlBlk *)(scsi_host->hostdata);

	dprपूर्णांकkdbg(DBG_0, "dc395x_remove_one: acb=%p\n", acb);

	scsi_हटाओ_host(scsi_host);
	adapter_uninit(acb);
	pci_disable_device(dev);
	scsi_host_put(scsi_host);
पूर्ण


अटल काष्ठा pci_device_id dc395x_pci_table[] = अणु
	अणु
		.venकरोr		= PCI_VENDOR_ID_TEKRAM,
		.device		= PCI_DEVICE_ID_TEKRAM_TRMS1040,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	 पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, dc395x_pci_table);


अटल काष्ठा pci_driver dc395x_driver = अणु
	.name           = DC395X_NAME,
	.id_table       = dc395x_pci_table,
	.probe          = dc395x_init_one,
	.हटाओ         = dc395x_हटाओ_one,
पूर्ण;
module_pci_driver(dc395x_driver);

MODULE_AUTHOR("C.L. Huang / Erich Chen / Kurt Garloff");
MODULE_DESCRIPTION("SCSI host adapter driver for Tekram TRM-S1040 based adapters: Tekram DC395 and DC315 series");
MODULE_LICENSE("GPL");
