<शैली गुरु>
/*
 * PMC-Sierra SPC 8001 SAS/SATA based host adapters driver
 *
 * Copyright (c) 2008-2009 USI Co., Ltd.
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
 */
#अगर_अघोषित _PMC8001_REG_H_
#घोषणा _PMC8001_REG_H_

#समावेश <linux/types.h>
#समावेश <scsi/libsas.h>


/* क्रम Request Opcode of IOMB */
#घोषणा OPC_INB_ECHO				1	/* 0x000 */
#घोषणा OPC_INB_PHYSTART			4	/* 0x004 */
#घोषणा OPC_INB_PHYSTOP				5	/* 0x005 */
#घोषणा OPC_INB_SSPINIIOSTART			6	/* 0x006 */
#घोषणा OPC_INB_SSPINITMSTART			7	/* 0x007 */
#घोषणा OPC_INB_SSPINIEXTIOSTART		8	/* 0x008 */
#घोषणा OPC_INB_DEV_HANDLE_ACCEPT		9	/* 0x009 */
#घोषणा OPC_INB_SSPTGTIOSTART			10	/* 0x00A */
#घोषणा OPC_INB_SSPTGTRSPSTART			11	/* 0x00B */
#घोषणा OPC_INB_SSPINIEDCIOSTART		12	/* 0x00C */
#घोषणा OPC_INB_SSPINIEXTEDCIOSTART		13	/* 0x00D */
#घोषणा OPC_INB_SSPTGTEDCIOSTART		14	/* 0x00E */
#घोषणा OPC_INB_SSP_ABORT			15	/* 0x00F */
#घोषणा OPC_INB_DEREG_DEV_HANDLE		16	/* 0x010 */
#घोषणा OPC_INB_GET_DEV_HANDLE			17	/* 0x011 */
#घोषणा OPC_INB_SMP_REQUEST			18	/* 0x012 */
/* SMP_RESPONSE is हटाओd */
#घोषणा OPC_INB_SMP_RESPONSE			19	/* 0x013 */
#घोषणा OPC_INB_SMP_ABORT			20	/* 0x014 */
#घोषणा OPC_INB_REG_DEV				22	/* 0x016 */
#घोषणा OPC_INB_SATA_HOST_OPSTART		23	/* 0x017 */
#घोषणा OPC_INB_SATA_ABORT			24	/* 0x018 */
#घोषणा OPC_INB_LOCAL_PHY_CONTROL		25	/* 0x019 */
#घोषणा OPC_INB_GET_DEV_INFO			26	/* 0x01A */
#घोषणा OPC_INB_FW_FLASH_UPDATE			32	/* 0x020 */
#घोषणा OPC_INB_GPIO				34	/* 0x022 */
#घोषणा OPC_INB_SAS_DIAG_MODE_START_END		35	/* 0x023 */
#घोषणा OPC_INB_SAS_DIAG_EXECUTE		36	/* 0x024 */
#घोषणा OPC_INB_SAS_HW_EVENT_ACK		37	/* 0x025 */
#घोषणा OPC_INB_GET_TIME_STAMP			38	/* 0x026 */
#घोषणा OPC_INB_PORT_CONTROL			39	/* 0x027 */
#घोषणा OPC_INB_GET_NVMD_DATA			40	/* 0x028 */
#घोषणा OPC_INB_SET_NVMD_DATA			41	/* 0x029 */
#घोषणा OPC_INB_SET_DEVICE_STATE		42	/* 0x02A */
#घोषणा OPC_INB_GET_DEVICE_STATE		43	/* 0x02B */
#घोषणा OPC_INB_SET_DEV_INFO			44	/* 0x02C */
#घोषणा OPC_INB_SAS_RE_INITIALIZE		45	/* 0x02D */

/* क्रम Response Opcode of IOMB */
#घोषणा OPC_OUB_ECHO				1	/* 0x001 */
#घोषणा OPC_OUB_HW_EVENT			4	/* 0x004 */
#घोषणा OPC_OUB_SSP_COMP			5	/* 0x005 */
#घोषणा OPC_OUB_SMP_COMP			6	/* 0x006 */
#घोषणा OPC_OUB_LOCAL_PHY_CNTRL			7	/* 0x007 */
#घोषणा OPC_OUB_DEV_REGIST			10	/* 0x00A */
#घोषणा OPC_OUB_DEREG_DEV			11	/* 0x00B */
#घोषणा OPC_OUB_GET_DEV_HANDLE			12	/* 0x00C */
#घोषणा OPC_OUB_SATA_COMP			13	/* 0x00D */
#घोषणा OPC_OUB_SATA_EVENT			14	/* 0x00E */
#घोषणा OPC_OUB_SSP_EVENT			15	/* 0x00F */
#घोषणा OPC_OUB_DEV_HANDLE_ARRIV		16	/* 0x010 */
/* SMP_RECEIVED Notअगरication is हटाओd */
#घोषणा OPC_OUB_SMP_RECV_EVENT			17	/* 0x011 */
#घोषणा OPC_OUB_SSP_RECV_EVENT			18	/* 0x012 */
#घोषणा OPC_OUB_DEV_INFO			19	/* 0x013 */
#घोषणा OPC_OUB_FW_FLASH_UPDATE			20	/* 0x014 */
#घोषणा OPC_OUB_GPIO_RESPONSE			22	/* 0x016 */
#घोषणा OPC_OUB_GPIO_EVENT			23	/* 0x017 */
#घोषणा OPC_OUB_GENERAL_EVENT			24	/* 0x018 */
#घोषणा OPC_OUB_SSP_ABORT_RSP			26	/* 0x01A */
#घोषणा OPC_OUB_SATA_ABORT_RSP			27	/* 0x01B */
#घोषणा OPC_OUB_SAS_DIAG_MODE_START_END		28	/* 0x01C */
#घोषणा OPC_OUB_SAS_DIAG_EXECUTE		29	/* 0x01D */
#घोषणा OPC_OUB_GET_TIME_STAMP			30	/* 0x01E */
#घोषणा OPC_OUB_SAS_HW_EVENT_ACK		31	/* 0x01F */
#घोषणा OPC_OUB_PORT_CONTROL			32	/* 0x020 */
#घोषणा OPC_OUB_SKIP_ENTRY			33	/* 0x021 */
#घोषणा OPC_OUB_SMP_ABORT_RSP			34	/* 0x022 */
#घोषणा OPC_OUB_GET_NVMD_DATA			35	/* 0x023 */
#घोषणा OPC_OUB_SET_NVMD_DATA			36	/* 0x024 */
#घोषणा OPC_OUB_DEVICE_HANDLE_REMOVAL		37	/* 0x025 */
#घोषणा OPC_OUB_SET_DEVICE_STATE		38	/* 0x026 */
#घोषणा OPC_OUB_GET_DEVICE_STATE		39	/* 0x027 */
#घोषणा OPC_OUB_SET_DEV_INFO			40	/* 0x028 */
#घोषणा OPC_OUB_SAS_RE_INITIALIZE		41	/* 0x029 */

/* क्रम phy start*/
#घोषणा SPINHOLD_DISABLE		(0x00 << 14)
#घोषणा SPINHOLD_ENABLE			(0x01 << 14)
#घोषणा LINKMODE_SAS			(0x01 << 12)
#घोषणा LINKMODE_DSATA			(0x02 << 12)
#घोषणा LINKMODE_AUTO			(0x03 << 12)
#घोषणा LINKRATE_15			(0x01 << 8)
#घोषणा LINKRATE_30			(0x02 << 8)
#घोषणा LINKRATE_60			(0x04 << 8)

/* क्रम new SPC controllers MEMBASE III is shared between BIOS and DATA */
#घोषणा GSM_SM_BASE			0x4F0000
काष्ठा mpi_msg_hdrअणु
	__le32	header;	/* Bits [11:0]  - Message operation code */
	/* Bits [15:12] - Message Category */
	/* Bits [21:16] - Outboundqueue ID क्रम the
	operation completion message */
	/* Bits [23:22] - Reserved */
	/* Bits [28:24] - Buffer Count, indicates how
	many buffer are allocated क्रम the massage */
	/* Bits [30:29] - Reserved */
	/* Bits [31] - Message Valid bit */
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of PHY Start Command
 * use to describe enable the phy (64 bytes)
 */
काष्ठा phy_start_req अणु
	__le32	tag;
	__le32	ase_sh_lm_slr_phyid;
	काष्ठा sas_identअगरy_frame sas_identअगरy;
	u32	reserved[5];
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of PHY Start Command
 * use to disable the phy (64 bytes)
 */
काष्ठा phy_stop_req अणु
	__le32	tag;
	__le32	phy_id;
	u32	reserved[13];
पूर्ण __attribute__((packed, aligned(4)));


/* set device bits fis - device to host */
काष्ठा  set_dev_bits_fis अणु
	u8	fis_type;	/* 0xA1*/
	u8	n_i_pmport;
	/* b7 : n Bit. Notअगरication bit. If set device needs attention. */
	/* b6 : i Bit. Interrupt Bit */
	/* b5-b4: reserved2 */
	/* b3-b0: PM Port */
	u8 	status;
	u8	error;
	u32	_r_a;
पूर्ण __attribute__ ((packed));
/* PIO setup FIS - device to host */
काष्ठा  pio_setup_fis अणु
	u8	fis_type;	/* 0x5f */
	u8	i_d_pmPort;
	/* b7 : reserved */
	/* b6 : i bit. Interrupt bit */
	/* b5 : d bit. data transfer direction. set to 1 क्रम device to host
	xfer */
	/* b4 : reserved */
	/* b3-b0: PM Port */
	u8	status;
	u8	error;
	u8	lbal;
	u8	lbam;
	u8	lbah;
	u8	device;
	u8	lbal_exp;
	u8	lbam_exp;
	u8	lbah_exp;
	u8	_r_a;
	u8	sector_count;
	u8	sector_count_exp;
	u8	_r_b;
	u8	e_status;
	u8	_r_c[2];
	u8	transfer_count;
पूर्ण __attribute__ ((packed));

/*
 * brief the data काष्ठाure of SATA Completion Response
 * use to describe the sata task response (64 bytes)
 */
काष्ठा sata_completion_resp अणु
	__le32	tag;
	__le32	status;
	__le32	param;
	u32	sata_resp[12];
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of SAS HW Event Notअगरication
 * use to alert the host about the hardware event(64 bytes)
 */
काष्ठा hw_event_resp अणु
	__le32	lr_evt_status_phyid_portid;
	__le32	evt_param;
	__le32	npip_portstate;
	काष्ठा sas_identअगरy_frame	sas_identअगरy;
	काष्ठा dev_to_host_fis	sata_fis;
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of  REGISTER DEVICE Command
 * use to describe MPI REGISTER DEVICE Command (64 bytes)
 */

काष्ठा reg_dev_req अणु
	__le32	tag;
	__le32	phyid_portid;
	__le32	dtype_dlr_retry;
	__le32	firstburstsize_ITNexusसमयout;
	u8	sas_addr[SAS_ADDR_SIZE];
	__le32	upper_device_id;
	u32	reserved[8];
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of  DEREGISTER DEVICE Command
 * use to request spc to हटाओ all पूर्णांकernal resources associated
 * with the device id (64 bytes)
 */

काष्ठा dereg_dev_req अणु
	__le32	tag;
	__le32	device_id;
	u32	reserved[13];
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of DEVICE_REGISTRATION Response
 * use to notअगरy the completion of the device registration  (64 bytes)
 */

काष्ठा dev_reg_resp अणु
	__le32	tag;
	__le32	status;
	__le32	device_id;
	u32	reserved[12];
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of Local PHY Control Command
 * use to issue PHY CONTROL to local phy (64 bytes)
 */
काष्ठा local_phy_ctl_req अणु
	__le32	tag;
	__le32	phyop_phyid;
	u32	reserved1[13];
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of Local Phy Control Response
 * use to describe MPI Local Phy Control Response (64 bytes)
 */
काष्ठा local_phy_ctl_resp अणु
	__le32	tag;
	__le32	phyop_phyid;
	__le32	status;
	u32	reserved[12];
पूर्ण __attribute__((packed, aligned(4)));


#घोषणा OP_BITS 0x0000FF00
#घोषणा ID_BITS 0x000000FF

/*
 * brief the data काष्ठाure of PORT Control Command
 * use to control port properties (64 bytes)
 */

काष्ठा port_ctl_req अणु
	__le32	tag;
	__le32	portop_portid;
	__le32	param0;
	__le32	param1;
	u32	reserved1[11];
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of HW Event Ack Command
 * use to acknowledge receive HW event (64 bytes)
 */

काष्ठा hw_event_ack_req अणु
	__le32	tag;
	__le32	sea_phyid_portid;
	__le32	param0;
	__le32	param1;
	u32	reserved1[11];
पूर्ण __attribute__((packed, aligned(4)));


/*
 * brief the data काष्ठाure of SSP Completion Response
 * use to indicate a SSP Completion  (n bytes)
 */
काष्ठा ssp_completion_resp अणु
	__le32	tag;
	__le32	status;
	__le32	param;
	__le32	ssptag_rescv_rescpad;
	काष्ठा ssp_response_iu  ssp_resp_iu;
	__le32	residual_count;
पूर्ण __attribute__((packed, aligned(4)));


#घोषणा SSP_RESCV_BIT	0x00010000

/*
 * brief the data काष्ठाure of SATA EVNET esponse
 * use to indicate a SATA Completion  (64 bytes)
 */

काष्ठा sata_event_resp अणु
	__le32	tag;
	__le32	event;
	__le32	port_id;
	__le32	device_id;
	u32	reserved[11];
पूर्ण __attribute__((packed, aligned(4)));

/*
 * brief the data काष्ठाure of SSP EVNET esponse
 * use to indicate a SSP Completion  (64 bytes)
 */

काष्ठा ssp_event_resp अणु
	__le32	tag;
	__le32	event;
	__le32	port_id;
	__le32	device_id;
	u32	reserved[11];
पूर्ण __attribute__((packed, aligned(4)));

/**
 * brief the data काष्ठाure of General Event Notअगरication Response
 * use to describe MPI General Event Notअगरication Response (64 bytes)
 */
काष्ठा general_event_resp अणु
	__le32	status;
	__le32	inb_IOMB_payload[14];
पूर्ण __attribute__((packed, aligned(4)));


#घोषणा GENERAL_EVENT_PAYLOAD	14
#घोषणा OPCODE_BITS	0x00000fff

/*
 * brief the data काष्ठाure of SMP Request Command
 * use to describe MPI SMP REQUEST Command (64 bytes)
 */
काष्ठा smp_req अणु
	__le32	tag;
	__le32	device_id;
	__le32	len_ip_ir;
	/* Bits [0]  - Indirect response */
	/* Bits [1] - Indirect Payload */
	/* Bits [15:2] - Reserved */
	/* Bits [23:16] - direct payload Len */
	/* Bits [31:24] - Reserved */
	u8	smp_req16[16];
	जोड़ अणु
		u8	smp_req[32];
		काष्ठा अणु
			__le64 दीर्घ_req_addr;/* sg dma address, LE */
			__le32 दीर्घ_req_size;/* LE */
			u32	_r_a;
			__le64 दीर्घ_resp_addr;/* sg dma address, LE */
			__le32 दीर्घ_resp_size;/* LE */
			u32	_r_b;
			पूर्ण दीर्घ_smp_req;/* sequencer extension */
	पूर्ण;
पूर्ण __attribute__((packed, aligned(4)));
/*
 * brief the data काष्ठाure of SMP Completion Response
 * use to describe MPI SMP Completion Response (64 bytes)
 */
काष्ठा smp_completion_resp अणु
	__le32	tag;
	__le32	status;
	__le32	param;
	__le32	_r_a[12];
पूर्ण __attribute__((packed, aligned(4)));

/*
 *brief the data काष्ठाure of SSP SMP SATA Abort Command
 * use to describe MPI SSP SMP & SATA Abort Command (64 bytes)
 */
काष्ठा task_पात_req अणु
	__le32	tag;
	__le32	device_id;
	__le32	tag_to_पात;
	__le32	पात_all;
	u32	reserved[11];
पूर्ण __attribute__((packed, aligned(4)));

/* These flags used क्रम SSP SMP & SATA Abort */
#घोषणा ABORT_MASK		0x3
#घोषणा ABORT_SINGLE		0x0
#घोषणा ABORT_ALL		0x1

/**
 * brief the data काष्ठाure of SSP SATA SMP Abort Response
 * use to describe SSP SMP & SATA Abort Response ( 64 bytes)
 */
काष्ठा task_पात_resp अणु
	__le32	tag;
	__le32	status;
	__le32	scp;
	u32	reserved[12];
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of SAS Diagnostic Start/End Command
 * use to describe MPI SAS Diagnostic Start/End Command (64 bytes)
 */
काष्ठा sas_diag_start_end_req अणु
	__le32	tag;
	__le32	operation_phyid;
	u32	reserved[13];
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of SAS Diagnostic Execute Command
 * use to describe MPI SAS Diagnostic Execute Command (64 bytes)
 */
काष्ठा sas_diag_execute_reqअणु
	__le32	tag;
	__le32	cmdtype_cmddesc_phyid;
	__le32	pat1_pat2;
	__le32	threshold;
	__le32	codepat_errmsk;
	__le32	pmon;
	__le32	pERF1CTL;
	u32	reserved[8];
पूर्ण __attribute__((packed, aligned(4)));


#घोषणा SAS_DIAG_PARAM_BYTES 24

/*
 * brief the data काष्ठाure of Set Device State Command
 * use to describe MPI Set Device State Command (64 bytes)
 */
काष्ठा set_dev_state_req अणु
	__le32	tag;
	__le32	device_id;
	__le32	nds;
	u32	reserved[12];
पूर्ण __attribute__((packed, aligned(4)));

/*
 * brief the data काष्ठाure of sas_re_initialization
 */
काष्ठा sas_re_initialization_req अणु

	__le32	tag;
	__le32	SSAHOLT;/* bit29-set max port;
			** bit28-set खोलो reject cmd retries.
			** bit27-set खोलो reject data retries.
			** bit26-set खोलो reject option, remap:1 or not:0.
			** bit25-set sata head of line समय out.
			*/
	__le32 reserved_maxPorts;
	__le32 खोलो_reject_cmdretries_data_retries;/* cmd retries: 31-bit16;
						    * data retries: bit15-bit0.
						    */
	__le32	sata_hol_पंचांगo;
	u32	reserved1[10];
पूर्ण __attribute__((packed, aligned(4)));

/*
 * brief the data काष्ठाure of SATA Start Command
 * use to describe MPI SATA IO Start Command (64 bytes)
 */

काष्ठा sata_start_req अणु
	__le32	tag;
	__le32	device_id;
	__le32	data_len;
	__le32	ncqtag_atap_dir_m;
	काष्ठा host_to_dev_fis	sata_fis;
	u32	reserved1;
	u32	reserved2;
	u32	addr_low;
	u32	addr_high;
	__le32	len;
	__le32	esgl;
पूर्ण __attribute__((packed, aligned(4)));

/**
 * brief the data काष्ठाure of SSP INI TM Start Command
 * use to describe MPI SSP INI TM Start Command (64 bytes)
 */
काष्ठा ssp_ini_पंचांग_start_req अणु
	__le32	tag;
	__le32	device_id;
	__le32	relate_tag;
	__le32	पंचांगf;
	u8	lun[8];
	__le32	ds_ads_m;
	u32	reserved[8];
पूर्ण __attribute__((packed, aligned(4)));


काष्ठा ssp_info_unit अणु
	u8	lun[8];/* SCSI Logical Unit Number */
	u8	reserved1;/* reserved */
	u8	efb_prio_attr;
	/* B7   : enabledFirstBurst */
	/* B6-3 : taskPriority */
	/* B2-0 : taskAttribute */
	u8	reserved2;	/* reserved */
	u8	additional_cdb_len;
	/* B7-2 : additional_cdb_len */
	/* B1-0 : reserved */
	u8	cdb[16];/* The SCSI CDB up to 16 bytes length */
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of SSP INI IO Start Command
 * use to describe MPI SSP INI IO Start Command (64 bytes)
 */
काष्ठा ssp_ini_io_start_req अणु
	__le32	tag;
	__le32	device_id;
	__le32	data_len;
	__le32	dir_m_tlr;
	काष्ठा ssp_info_unit	ssp_iu;
	__le32	addr_low;
	__le32	addr_high;
	__le32	len;
	__le32	esgl;
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of Firmware करोwnload
 * use to describe MPI FW DOWNLOAD Command (64 bytes)
 */
काष्ठा fw_flash_Update_req अणु
	__le32	tag;
	__le32	cur_image_offset;
	__le32	cur_image_len;
	__le32	total_image_len;
	u32	reserved0[7];
	__le32	sgl_addr_lo;
	__le32	sgl_addr_hi;
	__le32	len;
	__le32	ext_reserved;
पूर्ण __attribute__((packed, aligned(4)));


#घोषणा FWFLASH_IOMB_RESERVED_LEN 0x07
/**
 * brief the data काष्ठाure of FW_FLASH_UPDATE Response
 * use to describe MPI FW_FLASH_UPDATE Response (64 bytes)
 *
 */
काष्ठा fw_flash_Update_resp अणु
	__le32	tag;
	__le32	status;
	u32	reserved[13];
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of Get NVM Data Command
 * use to get data from NVM in HBA(64 bytes)
 */
काष्ठा get_nvm_data_req अणु
	__le32	tag;
	__le32	len_ir_vpdd;
	__le32	vpd_offset;
	u32	reserved[8];
	__le32	resp_addr_lo;
	__le32	resp_addr_hi;
	__le32	resp_len;
	u32	reserved1;
पूर्ण __attribute__((packed, aligned(4)));


काष्ठा set_nvm_data_req अणु
	__le32	tag;
	__le32	len_ir_vpdd;
	__le32	vpd_offset;
	__le32	reserved[8];
	__le32	resp_addr_lo;
	__le32	resp_addr_hi;
	__le32	resp_len;
	u32	reserved1;
पूर्ण __attribute__((packed, aligned(4)));


#घोषणा TWI_DEVICE	0x0
#घोषणा C_SEEPROM	0x1
#घोषणा VPD_FLASH	0x4
#घोषणा AAP1_RDUMP	0x5
#घोषणा IOP_RDUMP	0x6
#घोषणा EXPAN_ROM	0x7

#घोषणा IPMode		0x80000000
#घोषणा NVMD_TYPE	0x0000000F
#घोषणा NVMD_STAT	0x0000FFFF
#घोषणा NVMD_LEN	0xFF000000
/**
 * brief the data काष्ठाure of Get NVMD Data Response
 * use to describe MPI Get NVMD Data Response (64 bytes)
 */
काष्ठा get_nvm_data_resp अणु
	__le32		tag;
	__le32		ir_tda_bn_dps_das_nvm;
	__le32		dlen_status;
	__le32		nvm_data[12];
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of SAS Diagnostic Start/End Response
 * use to describe MPI SAS Diagnostic Start/End Response (64 bytes)
 *
 */
काष्ठा sas_diag_start_end_resp अणु
	__le32		tag;
	__le32		status;
	u32		reserved[13];
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of SAS Diagnostic Execute Response
 * use to describe MPI SAS Diagnostic Execute Response (64 bytes)
 *
 */
काष्ठा sas_diag_execute_resp अणु
	__le32		tag;
	__le32		cmdtype_cmddesc_phyid;
	__le32		Status;
	__le32		ReportData;
	u32		reserved[11];
पूर्ण __attribute__((packed, aligned(4)));


/**
 * brief the data काष्ठाure of Set Device State Response
 * use to describe MPI Set Device State Response (64 bytes)
 *
 */
काष्ठा set_dev_state_resp अणु
	__le32		tag;
	__le32		status;
	__le32		device_id;
	__le32		pds_nds;
	u32		reserved[11];
पूर्ण __attribute__((packed, aligned(4)));


#घोषणा NDS_BITS 0x0F
#घोषणा PDS_BITS 0xF0

/*
 * HW Events type
 */

#घोषणा HW_EVENT_RESET_START			0x01
#घोषणा HW_EVENT_CHIP_RESET_COMPLETE		0x02
#घोषणा HW_EVENT_PHY_STOP_STATUS		0x03
#घोषणा HW_EVENT_SAS_PHY_UP			0x04
#घोषणा HW_EVENT_SATA_PHY_UP			0x05
#घोषणा HW_EVENT_SATA_SPINUP_HOLD		0x06
#घोषणा HW_EVENT_PHY_DOWN			0x07
#घोषणा HW_EVENT_PORT_INVALID			0x08
#घोषणा HW_EVENT_BROADCAST_CHANGE		0x09
#घोषणा HW_EVENT_PHY_ERROR			0x0A
#घोषणा HW_EVENT_BROADCAST_SES			0x0B
#घोषणा HW_EVENT_INBOUND_CRC_ERROR		0x0C
#घोषणा HW_EVENT_HARD_RESET_RECEIVED		0x0D
#घोषणा HW_EVENT_MALFUNCTION			0x0E
#घोषणा HW_EVENT_ID_FRAME_TIMEOUT		0x0F
#घोषणा HW_EVENT_BROADCAST_EXP			0x10
#घोषणा HW_EVENT_PHY_START_STATUS		0x11
#घोषणा HW_EVENT_LINK_ERR_INVALID_DWORD		0x12
#घोषणा HW_EVENT_LINK_ERR_DISPARITY_ERROR	0x13
#घोषणा HW_EVENT_LINK_ERR_CODE_VIOLATION	0x14
#घोषणा HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH	0x15
#घोषणा HW_EVENT_LINK_ERR_PHY_RESET_FAILED	0x16
#घोषणा HW_EVENT_PORT_RECOVERY_TIMER_TMO	0x17
#घोषणा HW_EVENT_PORT_RECOVER			0x18
#घोषणा HW_EVENT_PORT_RESET_TIMER_TMO		0x19
#घोषणा HW_EVENT_PORT_RESET_COMPLETE		0x20
#घोषणा EVENT_BROADCAST_ASYNCH_EVENT		0x21

/* port state */
#घोषणा PORT_NOT_ESTABLISHED			0x00
#घोषणा PORT_VALID				0x01
#घोषणा PORT_LOSTCOMM				0x02
#घोषणा PORT_IN_RESET				0x04
#घोषणा PORT_INVALID				0x08

/*
 * SSP/SMP/SATA IO Completion Status values
 */

#घोषणा IO_SUCCESS				0x00
#घोषणा IO_ABORTED				0x01
#घोषणा IO_OVERFLOW				0x02
#घोषणा IO_UNDERFLOW				0x03
#घोषणा IO_FAILED				0x04
#घोषणा IO_ABORT_RESET				0x05
#घोषणा IO_NOT_VALID				0x06
#घोषणा IO_NO_DEVICE				0x07
#घोषणा IO_ILLEGAL_PARAMETER			0x08
#घोषणा IO_LINK_FAILURE				0x09
#घोषणा IO_PROG_ERROR				0x0A
#घोषणा IO_EDC_IN_ERROR				0x0B
#घोषणा IO_EDC_OUT_ERROR			0x0C
#घोषणा IO_ERROR_HW_TIMEOUT			0x0D
#घोषणा IO_XFER_ERROR_BREAK			0x0E
#घोषणा IO_XFER_ERROR_PHY_NOT_READY		0x0F
#घोषणा IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED	0x10
#घोषणा IO_OPEN_CNX_ERROR_ZONE_VIOLATION		0x11
#घोषणा IO_OPEN_CNX_ERROR_BREAK				0x12
#घोषणा IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS			0x13
#घोषणा IO_OPEN_CNX_ERROR_BAD_DESTINATION		0x14
#घोषणा IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED	0x15
#घोषणा IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY		0x16
#घोषणा IO_OPEN_CNX_ERROR_WRONG_DESTINATION		0x17
#घोषणा IO_OPEN_CNX_ERROR_UNKNOWN_ERROR			0x18
#घोषणा IO_XFER_ERROR_NAK_RECEIVED			0x19
#घोषणा IO_XFER_ERROR_ACK_NAK_TIMEOUT			0x1A
#घोषणा IO_XFER_ERROR_PEER_ABORTED			0x1B
#घोषणा IO_XFER_ERROR_RX_FRAME				0x1C
#घोषणा IO_XFER_ERROR_DMA				0x1D
#घोषणा IO_XFER_ERROR_CREDIT_TIMEOUT			0x1E
#घोषणा IO_XFER_ERROR_SATA_LINK_TIMEOUT			0x1F
#घोषणा IO_XFER_ERROR_SATA				0x20
#घोषणा IO_XFER_ERROR_ABORTED_DUE_TO_SRST		0x22
#घोषणा IO_XFER_ERROR_REJECTED_NCQ_MODE			0x21
#घोषणा IO_XFER_ERROR_ABORTED_NCQ_MODE			0x23
#घोषणा IO_XFER_OPEN_RETRY_TIMEOUT			0x24
#घोषणा IO_XFER_SMP_RESP_CONNECTION_ERROR		0x25
#घोषणा IO_XFER_ERROR_UNEXPECTED_PHASE			0x26
#घोषणा IO_XFER_ERROR_XFER_RDY_OVERRUN			0x27
#घोषणा IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED		0x28

#घोषणा IO_XFER_ERROR_CMD_ISSUE_ACK_NAK_TIMEOUT		0x30
#घोषणा IO_XFER_ERROR_CMD_ISSUE_BREAK_BEFORE_ACK_NAK	0x31
#घोषणा IO_XFER_ERROR_CMD_ISSUE_PHY_DOWN_BEFORE_ACK_NAK	0x32

#घोषणा IO_XFER_ERROR_OFFSET_MISMATCH			0x34
#घोषणा IO_XFER_ERROR_XFER_ZERO_DATA_LEN		0x35
#घोषणा IO_XFER_CMD_FRAME_ISSUED			0x36
#घोषणा IO_ERROR_INTERNAL_SMP_RESOURCE			0x37
#घोषणा IO_PORT_IN_RESET				0x38
#घोषणा IO_DS_NON_OPERATIONAL				0x39
#घोषणा IO_DS_IN_RECOVERY				0x3A
#घोषणा IO_TM_TAG_NOT_FOUND				0x3B
#घोषणा IO_XFER_PIO_SETUP_ERROR				0x3C
#घोषणा IO_SSP_EXT_IU_ZERO_LEN_ERROR			0x3D
#घोषणा IO_DS_IN_ERROR					0x3E
#घोषणा IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY		0x3F
#घोषणा IO_ABORT_IN_PROGRESS				0x40
#घोषणा IO_ABORT_DELAYED				0x41
#घोषणा IO_INVALID_LENGTH				0x42
#घोषणा IO_FATAL_ERROR					0x51

/* WARNING: This error code must always be the last number.
 * If you add error code, modअगरy this code also
 * It is used as an index
 */
#घोषणा IO_ERROR_UNKNOWN_GENERIC			0x43

/* MSGU CONFIGURATION  TABLE*/

#घोषणा SPC_MSGU_CFG_TABLE_UPDATE		0x01/* Inbound करोorbell bit0 */
#घोषणा SPC_MSGU_CFG_TABLE_RESET		0x02/* Inbound करोorbell bit1 */
#घोषणा SPC_MSGU_CFG_TABLE_FREEZE		0x04/* Inbound करोorbell bit2 */
#घोषणा SPC_MSGU_CFG_TABLE_UNFREEZE		0x08/* Inbound करोorbell bit4 */
#घोषणा MSGU_IBDB_SET				0x04
#घोषणा MSGU_HOST_INT_STATUS			0x08
#घोषणा MSGU_HOST_INT_MASK			0x0C
#घोषणा MSGU_IOPIB_INT_STATUS			0x18
#घोषणा MSGU_IOPIB_INT_MASK			0x1C
#घोषणा MSGU_IBDB_CLEAR				0x20/* RevB - Host not use */
#घोषणा MSGU_MSGU_CONTROL			0x24
#घोषणा MSGU_ODR				0x3C/* RevB */
#घोषणा MSGU_ODCR				0x40/* RevB */
#घोषणा MSGU_SCRATCH_PAD_0			0x44
#घोषणा MSGU_SCRATCH_PAD_1			0x48
#घोषणा MSGU_SCRATCH_PAD_2			0x4C
#घोषणा MSGU_SCRATCH_PAD_3			0x50
#घोषणा MSGU_HOST_SCRATCH_PAD_0			0x54
#घोषणा MSGU_HOST_SCRATCH_PAD_1			0x58
#घोषणा MSGU_HOST_SCRATCH_PAD_2			0x5C
#घोषणा MSGU_HOST_SCRATCH_PAD_3			0x60
#घोषणा MSGU_HOST_SCRATCH_PAD_4			0x64
#घोषणा MSGU_HOST_SCRATCH_PAD_5			0x68
#घोषणा MSGU_HOST_SCRATCH_PAD_6			0x6C
#घोषणा MSGU_HOST_SCRATCH_PAD_7			0x70
#घोषणा MSGU_ODMR				0x74/* RevB */

/* bit definition क्रम ODMR रेजिस्टर */
#घोषणा ODMR_MASK_ALL				0xFFFFFFFF/* mask all
					पूर्णांकerrupt vector */
#घोषणा ODMR_CLEAR_ALL				0/* clear all
					पूर्णांकerrupt vector */
/* bit definition क्रम ODCR रेजिस्टर */
#घोषणा ODCR_CLEAR_ALL		0xFFFFFFFF   /* mask all
					पूर्णांकerrupt vector*/
/* MSIX Interupts */
#घोषणा MSIX_TABLE_OFFSET		0x2000
#घोषणा MSIX_TABLE_ELEMENT_SIZE		0x10
#घोषणा MSIX_INTERRUPT_CONTROL_OFFSET	0xC
#घोषणा MSIX_TABLE_BASE	  (MSIX_TABLE_OFFSET + MSIX_INTERRUPT_CONTROL_OFFSET)
#घोषणा MSIX_INTERRUPT_DISABLE		0x1
#घोषणा MSIX_INTERRUPT_ENABLE		0x0


/* state definition क्रम Scratch Pad1 रेजिस्टर */
#घोषणा SCRATCH_PAD1_POR		0x00  /* घातer on reset state */
#घोषणा SCRATCH_PAD1_SFR		0x01  /* soft reset state */
#घोषणा SCRATCH_PAD1_ERR		0x02  /* error state */
#घोषणा SCRATCH_PAD1_RDY		0x03  /* पढ़ोy state */
#घोषणा SCRATCH_PAD1_RST		0x04  /* soft reset toggle flag */
#घोषणा SCRATCH_PAD1_AAP1RDY_RST	0x08  /* AAP1 पढ़ोy क्रम soft reset */
#घोषणा SCRATCH_PAD1_STATE_MASK		0xFFFFFFF0   /* ScratchPad1
 Mask, bit1-0 State, bit2 Soft Reset, bit3 FW RDY क्रम Soft Reset */
#घोषणा SCRATCH_PAD1_RESERVED		0x000003F8   /* Scratch Pad1
 Reserved bit 3 to 9 */

 /* state definition क्रम Scratch Pad2 रेजिस्टर */
#घोषणा SCRATCH_PAD2_POR		0x00  /* घातer on state */
#घोषणा SCRATCH_PAD2_SFR		0x01  /* soft reset state */
#घोषणा SCRATCH_PAD2_ERR		0x02  /* error state */
#घोषणा SCRATCH_PAD2_RDY		0x03  /* पढ़ोy state */
#घोषणा SCRATCH_PAD2_FWRDY_RST		0x04  /* FW पढ़ोy क्रम soft reset flag*/
#घोषणा SCRATCH_PAD2_IOPRDY_RST		0x08  /* IOP पढ़ोy क्रम soft reset */
#घोषणा SCRATCH_PAD2_STATE_MASK		0xFFFFFFF4 /* ScratchPad 2
 Mask, bit1-0 State */
#घोषणा SCRATCH_PAD2_RESERVED		0x000003FC   /* Scratch Pad1
 Reserved bit 2 to 9 */

#घोषणा SCRATCH_PAD_ERROR_MASK		0xFFFFFC00   /* Error mask bits */
#घोषणा SCRATCH_PAD_STATE_MASK		0x00000003   /* State Mask bits */

/* मुख्य configuration offset - byte offset */
#घोषणा MAIN_SIGNATURE_OFFSET		0x00/* DWORD 0x00 */
#घोषणा MAIN_INTERFACE_REVISION		0x04/* DWORD 0x01 */
#घोषणा MAIN_FW_REVISION		0x08/* DWORD 0x02 */
#घोषणा MAIN_MAX_OUTSTANDING_IO_OFFSET	0x0C/* DWORD 0x03 */
#घोषणा MAIN_MAX_SGL_OFFSET		0x10/* DWORD 0x04 */
#घोषणा MAIN_CNTRL_CAP_OFFSET		0x14/* DWORD 0x05 */
#घोषणा MAIN_GST_OFFSET			0x18/* DWORD 0x06 */
#घोषणा MAIN_IBQ_OFFSET			0x1C/* DWORD 0x07 */
#घोषणा MAIN_OBQ_OFFSET			0x20/* DWORD 0x08 */
#घोषणा MAIN_IQNPPD_HPPD_OFFSET		0x24/* DWORD 0x09 */
#घोषणा MAIN_OB_HW_EVENT_PID03_OFFSET	0x28/* DWORD 0x0A */
#घोषणा MAIN_OB_HW_EVENT_PID47_OFFSET	0x2C/* DWORD 0x0B */
#घोषणा MAIN_OB_NCQ_EVENT_PID03_OFFSET	0x30/* DWORD 0x0C */
#घोषणा MAIN_OB_NCQ_EVENT_PID47_OFFSET	0x34/* DWORD 0x0D */
#घोषणा MAIN_TITNX_EVENT_PID03_OFFSET	0x38/* DWORD 0x0E */
#घोषणा MAIN_TITNX_EVENT_PID47_OFFSET	0x3C/* DWORD 0x0F */
#घोषणा MAIN_OB_SSP_EVENT_PID03_OFFSET	0x40/* DWORD 0x10 */
#घोषणा MAIN_OB_SSP_EVENT_PID47_OFFSET	0x44/* DWORD 0x11 */
#घोषणा MAIN_OB_SMP_EVENT_PID03_OFFSET	0x48/* DWORD 0x12 */
#घोषणा MAIN_OB_SMP_EVENT_PID47_OFFSET	0x4C/* DWORD 0x13 */
#घोषणा MAIN_EVENT_LOG_ADDR_HI		0x50/* DWORD 0x14 */
#घोषणा MAIN_EVENT_LOG_ADDR_LO		0x54/* DWORD 0x15 */
#घोषणा MAIN_EVENT_LOG_BUFF_SIZE	0x58/* DWORD 0x16 */
#घोषणा MAIN_EVENT_LOG_OPTION		0x5C/* DWORD 0x17 */
#घोषणा MAIN_IOP_EVENT_LOG_ADDR_HI	0x60/* DWORD 0x18 */
#घोषणा MAIN_IOP_EVENT_LOG_ADDR_LO	0x64/* DWORD 0x19 */
#घोषणा MAIN_IOP_EVENT_LOG_BUFF_SIZE	0x68/* DWORD 0x1A */
#घोषणा MAIN_IOP_EVENT_LOG_OPTION	0x6C/* DWORD 0x1B */
#घोषणा MAIN_FATAL_ERROR_INTERRUPT	0x70/* DWORD 0x1C */
#घोषणा MAIN_FATAL_ERROR_RDUMP0_OFFSET	0x74/* DWORD 0x1D */
#घोषणा MAIN_FATAL_ERROR_RDUMP0_LENGTH	0x78/* DWORD 0x1E */
#घोषणा MAIN_FATAL_ERROR_RDUMP1_OFFSET	0x7C/* DWORD 0x1F */
#घोषणा MAIN_FATAL_ERROR_RDUMP1_LENGTH	0x80/* DWORD 0x20 */
#घोषणा MAIN_HDA_FLAGS_OFFSET		0x84/* DWORD 0x21 */
#घोषणा MAIN_ANALOG_SETUP_OFFSET	0x88/* DWORD 0x22 */

/* Gereral Status Table offset - byte offset */
#घोषणा GST_GSTLEN_MPIS_OFFSET		0x00
#घोषणा GST_IQ_FREEZE_STATE0_OFFSET	0x04
#घोषणा GST_IQ_FREEZE_STATE1_OFFSET	0x08
#घोषणा GST_MSGUTCNT_OFFSET		0x0C
#घोषणा GST_IOPTCNT_OFFSET		0x10
#घोषणा GST_PHYSTATE_OFFSET		0x18
#घोषणा GST_PHYSTATE0_OFFSET		0x18
#घोषणा GST_PHYSTATE1_OFFSET		0x1C
#घोषणा GST_PHYSTATE2_OFFSET		0x20
#घोषणा GST_PHYSTATE3_OFFSET		0x24
#घोषणा GST_PHYSTATE4_OFFSET		0x28
#घोषणा GST_PHYSTATE5_OFFSET		0x2C
#घोषणा GST_PHYSTATE6_OFFSET		0x30
#घोषणा GST_PHYSTATE7_OFFSET		0x34
#घोषणा GST_RERRINFO_OFFSET		0x44

/* General Status Table - MPI state */
#घोषणा GST_MPI_STATE_UNINIT		0x00
#घोषणा GST_MPI_STATE_INIT		0x01
#घोषणा GST_MPI_STATE_TERMINATION	0x02
#घोषणा GST_MPI_STATE_ERROR		0x03
#घोषणा GST_MPI_STATE_MASK		0x07

#घोषणा MBIC_NMI_ENABLE_VPE0_IOP	0x000418
#घोषणा MBIC_NMI_ENABLE_VPE0_AAP1	0x000418
/* PCIE रेजिस्टरs - BAR2(0x18), BAR1(win) 0x010000 */
#घोषणा PCIE_EVENT_INTERRUPT_ENABLE	0x003040
#घोषणा PCIE_EVENT_INTERRUPT		0x003044
#घोषणा PCIE_ERROR_INTERRUPT_ENABLE	0x003048
#घोषणा PCIE_ERROR_INTERRUPT		0x00304C
/* signature definition क्रम host scratch pad0 रेजिस्टर */
#घोषणा SPC_SOFT_RESET_SIGNATURE	0x252acbcd
/* Signature क्रम Soft Reset */

/* SPC Reset रेजिस्टर - BAR4(0x20), BAR2(win) (need dynamic mapping) */
#घोषणा SPC_REG_RESET			0x000000/* reset रेजिस्टर */

/* bit dअगरination क्रम SPC_RESET रेजिस्टर */
#घोषणा   SPC_REG_RESET_OSSP		0x00000001
#घोषणा   SPC_REG_RESET_RAAE		0x00000002
#घोषणा   SPC_REG_RESET_PCS_SPBC	0x00000004
#घोषणा   SPC_REG_RESET_PCS_IOP_SS	0x00000008
#घोषणा   SPC_REG_RESET_PCS_AAP1_SS	0x00000010
#घोषणा   SPC_REG_RESET_PCS_AAP2_SS	0x00000020
#घोषणा   SPC_REG_RESET_PCS_LM		0x00000040
#घोषणा   SPC_REG_RESET_PCS		0x00000080
#घोषणा   SPC_REG_RESET_GSM		0x00000100
#घोषणा   SPC_REG_RESET_DDR2		0x00010000
#घोषणा   SPC_REG_RESET_BDMA_CORE	0x00020000
#घोषणा   SPC_REG_RESET_BDMA_SXCBI	0x00040000
#घोषणा   SPC_REG_RESET_PCIE_AL_SXCBI	0x00080000
#घोषणा   SPC_REG_RESET_PCIE_PWR	0x00100000
#घोषणा   SPC_REG_RESET_PCIE_SFT	0x00200000
#घोषणा   SPC_REG_RESET_PCS_SXCBI	0x00400000
#घोषणा   SPC_REG_RESET_LMS_SXCBI	0x00800000
#घोषणा   SPC_REG_RESET_PMIC_SXCBI	0x01000000
#घोषणा   SPC_REG_RESET_PMIC_CORE	0x02000000
#घोषणा   SPC_REG_RESET_PCIE_PC_SXCBI	0x04000000
#घोषणा   SPC_REG_RESET_DEVICE		0x80000000

/* रेजिस्टरs क्रम BAR Shअगरting - BAR2(0x18), BAR1(win) */
#घोषणा SPC_IBW_AXI_TRANSLATION_LOW	0x003258

#घोषणा MBIC_AAP1_ADDR_BASE		0x060000
#घोषणा MBIC_IOP_ADDR_BASE		0x070000
#घोषणा GSM_ADDR_BASE			0x0700000
/* Dynamic map through Bar4 - 0x00700000 */
#घोषणा GSM_CONFIG_RESET		0x00000000
#घोषणा RAM_ECC_DB_ERR			0x00000018
#घोषणा GSM_READ_ADDR_PARITY_INDIC	0x00000058
#घोषणा GSM_WRITE_ADDR_PARITY_INDIC	0x00000060
#घोषणा GSM_WRITE_DATA_PARITY_INDIC	0x00000068
#घोषणा GSM_READ_ADDR_PARITY_CHECK	0x00000038
#घोषणा GSM_WRITE_ADDR_PARITY_CHECK	0x00000040
#घोषणा GSM_WRITE_DATA_PARITY_CHECK	0x00000048

#घोषणा RB6_ACCESS_REG			0x6A0000
#घोषणा HDAC_EXEC_CMD			0x0002
#घोषणा HDA_C_PA			0xcb
#घोषणा HDA_SEQ_ID_BITS			0x00ff0000
#घोषणा HDA_GSM_OFFSET_BITS		0x00FFFFFF
#घोषणा MBIC_AAP1_ADDR_BASE		0x060000
#घोषणा MBIC_IOP_ADDR_BASE		0x070000
#घोषणा GSM_ADDR_BASE			0x0700000
#घोषणा SPC_TOP_LEVEL_ADDR_BASE		0x000000
#घोषणा GSM_CONFIG_RESET_VALUE          0x00003b00
#घोषणा GPIO_ADDR_BASE                  0x00090000
#घोषणा GPIO_GPIO_0_0UTPUT_CTL_OFFSET   0x0000010c

/* RB6 offset */
#घोषणा SPC_RB6_OFFSET			0x80C0
/* Magic number of  soft reset क्रम RB6 */
#घोषणा RB6_MAGIC_NUMBER_RST		0x1234

/* Device Register status */
#घोषणा DEVREG_SUCCESS					0x00
#घोषणा DEVREG_FAILURE_OUT_OF_RESOURCE			0x01
#घोषणा DEVREG_FAILURE_DEVICE_ALREADY_REGISTERED	0x02
#घोषणा DEVREG_FAILURE_INVALID_PHY_ID			0x03
#घोषणा DEVREG_FAILURE_PHY_ID_ALREADY_REGISTERED	0x04
#घोषणा DEVREG_FAILURE_PORT_ID_OUT_OF_RANGE		0x05
#घोषणा DEVREG_FAILURE_PORT_NOT_VALID_STATE		0x06
#घोषणा DEVREG_FAILURE_DEVICE_TYPE_NOT_VALID		0x07

#घोषणा GSM_BASE					0x4F0000
#घोषणा SHIFT_REG_64K_MASK				0xffff0000
#घोषणा SHIFT_REG_BIT_SHIFT				8
#पूर्ण_अगर

