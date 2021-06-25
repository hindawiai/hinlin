<शैली गुरु>
/*
 * PMC-Sierra PM8001/8081/8088/8089 SAS/SATA based host adapters driver
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

#अगर_अघोषित _PM8001_SAS_H_
#घोषणा _PM8001_SAS_H_

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <scsi/libsas.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/sas_ata.h>
#समावेश <linux/atomic.h>
#समावेश "pm8001_defs.h"

#घोषणा DRV_NAME		"pm80xx"
#घोषणा DRV_VERSION		"0.1.40"
#घोषणा PM8001_FAIL_LOGGING	0x01 /* Error message logging */
#घोषणा PM8001_INIT_LOGGING	0x02 /* driver init logging */
#घोषणा PM8001_DISC_LOGGING	0x04 /* discovery layer logging */
#घोषणा PM8001_IO_LOGGING	0x08 /* I/O path logging */
#घोषणा PM8001_EH_LOGGING	0x10 /* libsas EH function logging*/
#घोषणा PM8001_IOCTL_LOGGING	0x20 /* IOCTL message logging */
#घोषणा PM8001_MSG_LOGGING	0x40 /* misc message logging */
#घोषणा PM8001_DEV_LOGGING	0x80 /* development message logging */
#घोषणा PM8001_DEVIO_LOGGING	0x100 /* development io message logging */
#घोषणा PM8001_IOERR_LOGGING	0x200 /* development io err message logging */

#घोषणा pm8001_info(HBA, fmt, ...)					\
	pr_info("%s:: %s  %d:" fmt,					\
		(HBA)->name, __func__, __LINE__, ##__VA_ARGS__)

#घोषणा pm8001_dbg(HBA, level, fmt, ...)				\
करो अणु									\
	अगर (unlikely((HBA)->logging_level & PM8001_##level##_LOGGING))	\
		pm8001_info(HBA, fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा PM8001_USE_TASKLET
#घोषणा PM8001_USE_MSIX
#घोषणा PM8001_READ_VPD


#घोषणा IS_SPCV_12G(dev)	((dev->device == 0X8074)		\
				|| (dev->device == 0X8076)		\
				|| (dev->device == 0X8077)		\
				|| (dev->device == 0X8070)		\
				|| (dev->device == 0X8072))

#घोषणा PM8001_NAME_LENGTH		32/* generic length of strings */
बाह्य काष्ठा list_head hba_list;
बाह्य स्थिर काष्ठा pm8001_dispatch pm8001_8001_dispatch;
बाह्य स्थिर काष्ठा pm8001_dispatch pm8001_80xx_dispatch;

काष्ठा pm8001_hba_info;
काष्ठा pm8001_ccb_info;
काष्ठा pm8001_device;
/* define task management IU */
काष्ठा pm8001_पंचांगf_task अणु
	u8	पंचांगf;
	u32	tag_of_task_to_be_managed;
पूर्ण;
काष्ठा pm8001_ioctl_payload अणु
	u32	signature;
	u16	major_function;
	u16	minor_function;
	u16	status;
	u16	offset;
	u16	id;
	u32	wr_length;
	u32	rd_length;
	u8	*func_specअगरic;
पूर्ण;

#घोषणा MPI_FATAL_ERROR_TABLE_OFFSET_MASK 0xFFFFFF
#घोषणा MPI_FATAL_ERROR_TABLE_SIZE(value) ((0xFF000000 & value) >> SHIFT24)
#घोषणा MPI_FATAL_EDUMP_TABLE_LO_OFFSET            0x00     /* HNFBUFL */
#घोषणा MPI_FATAL_EDUMP_TABLE_HI_OFFSET            0x04     /* HNFBUFH */
#घोषणा MPI_FATAL_EDUMP_TABLE_LENGTH               0x08     /* HNFBLEN */
#घोषणा MPI_FATAL_EDUMP_TABLE_HANDSHAKE            0x0C     /* FDDHSHK */
#घोषणा MPI_FATAL_EDUMP_TABLE_STATUS               0x10     /* FDDTSTAT */
#घोषणा MPI_FATAL_EDUMP_TABLE_ACCUM_LEN            0x14     /* ACCDDLEN */
#घोषणा MPI_FATAL_EDUMP_TABLE_TOTAL_LEN		   0x18	    /* TOTALLEN */
#घोषणा MPI_FATAL_EDUMP_TABLE_SIGNATURE		   0x1C     /* SIGNITURE */
#घोषणा MPI_FATAL_EDUMP_HANDSHAKE_RDY              0x1
#घोषणा MPI_FATAL_EDUMP_HANDSHAKE_BUSY             0x0
#घोषणा MPI_FATAL_EDUMP_TABLE_STAT_RSVD                 0x0
#घोषणा MPI_FATAL_EDUMP_TABLE_STAT_DMA_FAILED           0x1
#घोषणा MPI_FATAL_EDUMP_TABLE_STAT_NF_SUCCESS_MORE_DATA 0x2
#घोषणा MPI_FATAL_EDUMP_TABLE_STAT_NF_SUCCESS_DONE      0x3
#घोषणा TYPE_GSM_SPACE        1
#घोषणा TYPE_QUEUE            2
#घोषणा TYPE_FATAL            3
#घोषणा TYPE_NON_FATAL        4
#घोषणा TYPE_INBOUND          1
#घोषणा TYPE_OUTBOUND         2
काष्ठा क्रमensic_data अणु
	u32  data_type;
	जोड़ अणु
		काष्ठा अणु
			u32  direct_len;
			u32  direct_offset;
			व्योम  *direct_data;
		पूर्ण gsm_buf;
		काष्ठा अणु
			u16  queue_type;
			u16  queue_index;
			u32  direct_len;
			व्योम  *direct_data;
		पूर्ण queue_buf;
		काष्ठा अणु
			u32  direct_len;
			u32  direct_offset;
			u32  पढ़ो_len;
			व्योम  *direct_data;
		पूर्ण data_buf;
	पूर्ण;
पूर्ण;

/* bit31-26 - mask bar */
#घोषणा SCRATCH_PAD0_BAR_MASK                    0xFC000000
/* bit25-0  - offset mask */
#घोषणा SCRATCH_PAD0_OFFSET_MASK                 0x03FFFFFF
/* अगर AAP error state */
#घोषणा SCRATCH_PAD0_AAPERR_MASK                 0xFFFFFFFF
/* Inbound करोorbell bit7 */
#घोषणा SPCv_MSGU_CFG_TABLE_NONFATAL_DUMP	 0x80
/* Inbound करोorbell bit7 SPCV */
#घोषणा SPCV_MSGU_CFG_TABLE_TRANSFER_DEBUG_INFO  0x80
#घोषणा MAIN_MERRDCTO_MERRDCES		         0xA0/* DWORD 0x28) */

काष्ठा pm8001_dispatch अणु
	अक्षर *name;
	पूर्णांक (*chip_init)(काष्ठा pm8001_hba_info *pm8001_ha);
	पूर्णांक (*chip_soft_rst)(काष्ठा pm8001_hba_info *pm8001_ha);
	व्योम (*chip_rst)(काष्ठा pm8001_hba_info *pm8001_ha);
	पूर्णांक (*chip_ioremap)(काष्ठा pm8001_hba_info *pm8001_ha);
	व्योम (*chip_iounmap)(काष्ठा pm8001_hba_info *pm8001_ha);
	irqवापस_t (*isr)(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec);
	u32 (*is_our_पूर्णांकerrupt)(काष्ठा pm8001_hba_info *pm8001_ha);
	पूर्णांक (*isr_process_oq)(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec);
	व्योम (*पूर्णांकerrupt_enable)(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec);
	व्योम (*पूर्णांकerrupt_disable)(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec);
	व्योम (*make_prd)(काष्ठा scatterlist *scatter, पूर्णांक nr, व्योम *prd);
	पूर्णांक (*smp_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_ccb_info *ccb);
	पूर्णांक (*ssp_io_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_ccb_info *ccb);
	पूर्णांक (*sata_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_ccb_info *ccb);
	पूर्णांक (*phy_start_req)(काष्ठा pm8001_hba_info *pm8001_ha,	u8 phy_id);
	पूर्णांक (*phy_stop_req)(काष्ठा pm8001_hba_info *pm8001_ha, u8 phy_id);
	पूर्णांक (*reg_dev_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_device *pm8001_dev, u32 flag);
	पूर्णांक (*dereg_dev_req)(काष्ठा pm8001_hba_info *pm8001_ha, u32 device_id);
	पूर्णांक (*phy_ctl_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		u32 phy_id, u32 phy_op);
	पूर्णांक (*task_पात)(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_device *pm8001_dev, u8 flag, u32 task_tag,
		u32 cmd_tag);
	पूर्णांक (*ssp_पंचांग_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_ccb_info *ccb, काष्ठा pm8001_पंचांगf_task *पंचांगf);
	पूर्णांक (*get_nvmd_req)(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *payload);
	पूर्णांक (*set_nvmd_req)(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *payload);
	पूर्णांक (*fw_flash_update_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		व्योम *payload);
	पूर्णांक (*set_dev_state_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_device *pm8001_dev, u32 state);
	पूर्णांक (*sas_diag_start_end_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		u32 state);
	पूर्णांक (*sas_diag_execute_req)(काष्ठा pm8001_hba_info *pm8001_ha,
		u32 state);
	पूर्णांक (*sas_re_init_req)(काष्ठा pm8001_hba_info *pm8001_ha);
	पूर्णांक (*fatal_errors)(काष्ठा pm8001_hba_info *pm8001_ha);
पूर्ण;

काष्ठा pm8001_chip_info अणु
	u32     encrypt;
	u32	n_phy;
	स्थिर काष्ठा pm8001_dispatch	*dispatch;
पूर्ण;
#घोषणा PM8001_CHIP_DISP	(pm8001_ha->chip->dispatch)

काष्ठा pm8001_port अणु
	काष्ठा asd_sas_port	sas_port;
	u8			port_attached;
	u16			wide_port_phymap;
	u8			port_state;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा pm8001_phy अणु
	काष्ठा pm8001_hba_info	*pm8001_ha;
	काष्ठा pm8001_port	*port;
	काष्ठा asd_sas_phy	sas_phy;
	काष्ठा sas_identअगरy	identअगरy;
	काष्ठा scsi_device	*sdev;
	u64			dev_sas_addr;
	u32			phy_type;
	काष्ठा completion	*enable_completion;
	u32			frame_rcvd_size;
	u8			frame_rcvd[32];
	u8			phy_attached;
	u8			phy_state;
	क्रमागत sas_linkrate	minimum_linkrate;
	क्रमागत sas_linkrate	maximum_linkrate;
	काष्ठा completion	*reset_completion;
	bool			port_reset_status;
	bool			reset_success;
पूर्ण;

/* port reset status */
#घोषणा PORT_RESET_SUCCESS	0x00
#घोषणा PORT_RESET_TMO		0x01

काष्ठा pm8001_device अणु
	क्रमागत sas_device_type	dev_type;
	काष्ठा करोमुख्य_device	*sas_device;
	u32			attached_phy;
	u32			id;
	काष्ठा completion	*dcompletion;
	काष्ठा completion	*setds_completion;
	u32			device_id;
	atomic_t		running_req;
पूर्ण;

काष्ठा pm8001_prd_imt अणु
	__le32			len;
	__le32			e;
पूर्ण;

काष्ठा pm8001_prd अणु
	__le64			addr;		/* 64-bit buffer address */
	काष्ठा pm8001_prd_imt	im_len;		/* 64-bit length */
पूर्ण __attribute__ ((packed));
/*
 * CCB(Command Control Block)
 */
काष्ठा pm8001_ccb_info अणु
	काष्ठा sas_task		*task;
	u32			n_elem;
	u32			ccb_tag;
	dma_addr_t		ccb_dma_handle;
	काष्ठा pm8001_device	*device;
	काष्ठा pm8001_prd	*buf_prd;
	काष्ठा fw_control_ex	*fw_control_context;
	u8			खोलो_retry;
पूर्ण;

काष्ठा mpi_mem अणु
	व्योम			*virt_ptr;
	dma_addr_t		phys_addr;
	u32			phys_addr_hi;
	u32			phys_addr_lo;
	u32			total_len;
	u32			num_elements;
	u32			element_size;
	u32			alignment;
पूर्ण;

काष्ठा mpi_mem_req अणु
	/* The number of element in the  mpiMemory array */
	u32			count;
	/* The array of काष्ठाures that define memroy regions*/
	काष्ठा mpi_mem		region[USI_MAX_MEMCNT];
पूर्ण;

काष्ठा encrypt अणु
	u32	cipher_mode;
	u32	sec_mode;
	u32	status;
	u32	flag;
पूर्ण;

काष्ठा sas_phy_attribute_table अणु
	u32	phystart1_16[16];
	u32	outbound_hw_event_pid1_16[16];
पूर्ण;

जोड़ मुख्य_cfg_table अणु
	काष्ठा अणु
	u32			signature;
	u32			पूर्णांकerface_rev;
	u32			firmware_rev;
	u32			max_out_io;
	u32			max_sgl;
	u32			ctrl_cap_flag;
	u32			gst_offset;
	u32			inbound_queue_offset;
	u32			outbound_queue_offset;
	u32			inbound_q_nppd_hppd;
	u32			outbound_hw_event_pid0_3;
	u32			outbound_hw_event_pid4_7;
	u32			outbound_ncq_event_pid0_3;
	u32			outbound_ncq_event_pid4_7;
	u32			outbound_tgt_ITNexus_event_pid0_3;
	u32			outbound_tgt_ITNexus_event_pid4_7;
	u32			outbound_tgt_ssp_event_pid0_3;
	u32			outbound_tgt_ssp_event_pid4_7;
	u32			outbound_tgt_smp_event_pid0_3;
	u32			outbound_tgt_smp_event_pid4_7;
	u32			upper_event_log_addr;
	u32			lower_event_log_addr;
	u32			event_log_size;
	u32			event_log_option;
	u32			upper_iop_event_log_addr;
	u32			lower_iop_event_log_addr;
	u32			iop_event_log_size;
	u32			iop_event_log_option;
	u32			fatal_err_पूर्णांकerrupt;
	u32			fatal_err_dump_offset0;
	u32			fatal_err_dump_length0;
	u32			fatal_err_dump_offset1;
	u32			fatal_err_dump_length1;
	u32			hda_mode_flag;
	u32			anolog_setup_table_offset;
	u32			rsvd[4];
	पूर्ण pm8001_tbl;

	काष्ठा अणु
	u32			signature;
	u32			पूर्णांकerface_rev;
	u32			firmware_rev;
	u32			max_out_io;
	u32			max_sgl;
	u32			ctrl_cap_flag;
	u32			gst_offset;
	u32			inbound_queue_offset;
	u32			outbound_queue_offset;
	u32			inbound_q_nppd_hppd;
	u32			rsvd[8];
	u32			crc_core_dump;
	u32			rsvd1;
	u32			upper_event_log_addr;
	u32			lower_event_log_addr;
	u32			event_log_size;
	u32			event_log_severity;
	u32			upper_pcs_event_log_addr;
	u32			lower_pcs_event_log_addr;
	u32			pcs_event_log_size;
	u32			pcs_event_log_severity;
	u32			fatal_err_पूर्णांकerrupt;
	u32			fatal_err_dump_offset0;
	u32			fatal_err_dump_length0;
	u32			fatal_err_dump_offset1;
	u32			fatal_err_dump_length1;
	u32			gpio_led_mapping;
	u32			analog_setup_table_offset;
	u32			पूर्णांक_vec_table_offset;
	u32			phy_attr_table_offset;
	u32			port_recovery_समयr;
	u32			पूर्णांकerrupt_reनिश्चितion_delay;
	u32			fatal_n_non_fatal_dump;	        /* 0x28 */
	u32			ila_version;
	u32			inc_fw_version;
	पूर्ण pm80xx_tbl;
पूर्ण;

जोड़ general_status_table अणु
	काष्ठा अणु
	u32			gst_len_mpistate;
	u32			iq_मुक्तze_state0;
	u32			iq_मुक्तze_state1;
	u32			msgu_tcnt;
	u32			iop_tcnt;
	u32			rsvd;
	u32			phy_state[8];
	u32			gpio_input_val;
	u32			rsvd1[2];
	u32			recover_err_info[8];
	पूर्ण pm8001_tbl;
	काष्ठा अणु
	u32			gst_len_mpistate;
	u32			iq_मुक्तze_state0;
	u32			iq_मुक्तze_state1;
	u32			msgu_tcnt;
	u32			iop_tcnt;
	u32			rsvd[9];
	u32			gpio_input_val;
	u32			rsvd1[2];
	u32			recover_err_info[8];
	पूर्ण pm80xx_tbl;
पूर्ण;
काष्ठा inbound_queue_table अणु
	u32			element_pri_size_cnt;
	u32			upper_base_addr;
	u32			lower_base_addr;
	u32			ci_upper_base_addr;
	u32			ci_lower_base_addr;
	u32			pi_pci_bar;
	u32			pi_offset;
	u32			total_length;
	व्योम			*base_virt;
	व्योम			*ci_virt;
	u32			reserved;
	__le32			consumer_index;
	u32			producer_idx;
	spinlock_t		iq_lock;
पूर्ण;
काष्ठा outbound_queue_table अणु
	u32			element_size_cnt;
	u32			upper_base_addr;
	u32			lower_base_addr;
	व्योम			*base_virt;
	u32			pi_upper_base_addr;
	u32			pi_lower_base_addr;
	u32			ci_pci_bar;
	u32			ci_offset;
	u32			total_length;
	व्योम			*pi_virt;
	u32			पूर्णांकerrup_vec_cnt_delay;
	u32			dपूर्णांकerrup_to_pci_offset;
	__le32			producer_index;
	u32			consumer_idx;
	spinlock_t		oq_lock;
पूर्ण;
काष्ठा pm8001_hba_memspace अणु
	व्योम __iomem  		*memvirtaddr;
	u64			membase;
	u32			memsize;
पूर्ण;
काष्ठा isr_param अणु
	काष्ठा pm8001_hba_info *drv_inst;
	u32 irq_id;
पूर्ण;
काष्ठा pm8001_hba_info अणु
	अक्षर			name[PM8001_NAME_LENGTH];
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		flags;
	spinlock_t		lock;/* host-wide lock */
	spinlock_t		biपंचांगap_lock;
	काष्ठा pci_dev		*pdev;/* our device */
	काष्ठा device		*dev;
	काष्ठा pm8001_hba_memspace io_mem[6];
	काष्ठा mpi_mem_req	memoryMap;
	काष्ठा encrypt		encrypt_info; /* support encryption */
	काष्ठा क्रमensic_data	क्रमensic_info;
	u32			fatal_bar_loc;
	u32			क्रमensic_last_offset;
	u32			fatal_क्रमensic_shअगरt_offset;
	u32			क्रमensic_fatal_step;
	u32			क्रमensic_preserved_accumulated_transfer;
	u32			evtlog_ib_offset;
	u32			evtlog_ob_offset;
	व्योम __iomem	*msg_unit_tbl_addr;/*Message Unit Table Addr*/
	व्योम __iomem	*मुख्य_cfg_tbl_addr;/*Main Config Table Addr*/
	व्योम __iomem	*general_stat_tbl_addr;/*General Status Table Addr*/
	व्योम __iomem	*inbnd_q_tbl_addr;/*Inbound Queue Config Table Addr*/
	व्योम __iomem	*outbnd_q_tbl_addr;/*Outbound Queue Config Table Addr*/
	व्योम __iomem	*pspa_q_tbl_addr;
			/*MPI SAS PHY attributes Queue Config Table Addr*/
	व्योम __iomem	*ivt_tbl_addr; /*MPI IVT Table Addr */
	व्योम __iomem	*fatal_tbl_addr; /*MPI IVT Table Addr */
	जोड़ मुख्य_cfg_table	मुख्य_cfg_tbl;
	जोड़ general_status_table	gs_tbl;
	काष्ठा inbound_queue_table	inbnd_q_tbl[PM8001_MAX_INB_NUM];
	काष्ठा outbound_queue_table	outbnd_q_tbl[PM8001_MAX_OUTB_NUM];
	काष्ठा sas_phy_attribute_table	phy_attr_table;
					/* MPI SAS PHY attributes */
	u8			sas_addr[SAS_ADDR_SIZE];
	काष्ठा sas_ha_काष्ठा	*sas;/* SCSI/SAS glue */
	काष्ठा Scsi_Host	*shost;
	u32			chip_id;
	स्थिर काष्ठा pm8001_chip_info	*chip;
	काष्ठा completion	*nvmd_completion;
	पूर्णांक			tags_num;
	अचिन्हित दीर्घ		*tags;
	काष्ठा pm8001_phy	phy[PM8001_MAX_PHYS];
	काष्ठा pm8001_port	port[PM8001_MAX_PHYS];
	u32			id;
	u32			irq;
	u32			iomb_size; /* SPC and SPCV IOMB size */
	काष्ठा pm8001_device	*devices;
	काष्ठा pm8001_ccb_info	*ccb_info;
#अगर_घोषित PM8001_USE_MSIX
	पूर्णांक			number_of_पूर्णांकr;/*will be used in हटाओ()*/
	अक्षर			पूर्णांकr_drvname[PM8001_MAX_MSIX_VEC]
				[PM8001_NAME_LENGTH+1+3+1];
#पूर्ण_अगर
#अगर_घोषित PM8001_USE_TASKLET
	काष्ठा tasklet_काष्ठा	tasklet[PM8001_MAX_MSIX_VEC];
#पूर्ण_अगर
	u32			logging_level;
	u32			link_rate;
	u32			fw_status;
	u32			smp_exp_mode;
	bool			controller_fatal_error;
	स्थिर काष्ठा firmware 	*fw_image;
	काष्ठा isr_param irq_vector[PM8001_MAX_MSIX_VEC];
	u32			reset_in_progress;
	u32			non_fatal_count;
	u32			non_fatal_पढ़ो_length;
	u32 max_q_num;
	u32 ib_offset;
	u32 ob_offset;
	u32 ci_offset;
	u32 pi_offset;
	u32 max_memcnt;
पूर्ण;

काष्ठा pm8001_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा pm8001_hba_info *pm8001_ha;
	व्योम *data;
	पूर्णांक handler;
पूर्ण;

काष्ठा pm8001_fw_image_header अणु
	u8 vender_id[8];
	u8 product_id;
	u8 hardware_rev;
	u8 dest_partition;
	u8 reserved;
	u8 fw_rev[4];
	__be32  image_length;
	__be32 image_crc;
	__be32 startup_entry;
पूर्ण __attribute__((packed, aligned(4)));


/**
 * FW Flash Update status values
 */
#घोषणा FLASH_UPDATE_COMPLETE_PENDING_REBOOT	0x00
#घोषणा FLASH_UPDATE_IN_PROGRESS		0x01
#घोषणा FLASH_UPDATE_HDR_ERR			0x02
#घोषणा FLASH_UPDATE_OFFSET_ERR			0x03
#घोषणा FLASH_UPDATE_CRC_ERR			0x04
#घोषणा FLASH_UPDATE_LENGTH_ERR			0x05
#घोषणा FLASH_UPDATE_HW_ERR			0x06
#घोषणा FLASH_UPDATE_DNLD_NOT_SUPPORTED		0x10
#घोषणा FLASH_UPDATE_DISABLED			0x11

#घोषणा	NCQ_READ_LOG_FLAG			0x80000000
#घोषणा	NCQ_ABORT_ALL_FLAG			0x40000000
#घोषणा	NCQ_2ND_RLE_FLAG			0x20000000

/* Device states */
#घोषणा DS_OPERATIONAL				0x01
#घोषणा DS_PORT_IN_RESET			0x02
#घोषणा DS_IN_RECOVERY				0x03
#घोषणा DS_IN_ERROR				0x04
#घोषणा DS_NON_OPERATIONAL			0x07

/**
 * brief param काष्ठाure क्रम firmware flash update.
 */
काष्ठा fw_flash_updata_info अणु
	u32			cur_image_offset;
	u32			cur_image_len;
	u32			total_image_len;
	काष्ठा pm8001_prd	sgl;
पूर्ण;

काष्ठा fw_control_info अणु
	u32			retcode;/*ret code (status)*/
	u32			phase;/*ret code phase*/
	u32			phaseCmplt;/*percent complete क्रम the current
	update phase */
	u32			version;/*Hex encoded firmware version number*/
	u32			offset;/*Used क्रम करोwnloading firmware	*/
	u32			len; /*len of buffer*/
	u32			size;/* Used in OS VPD and Trace get size
	operations.*/
	u32			reserved;/* padding required क्रम 64 bit
	alignment */
	u8			buffer[1];/* Start of buffer */
पूर्ण;
काष्ठा fw_control_ex अणु
	काष्ठा fw_control_info *fw_control;
	व्योम			*buffer;/* keep buffer poपूर्णांकer to be
	मुक्तd when the response comes*/
	व्योम			*virtAddr;/* keep भव address of the data */
	व्योम			*usrAddr;/* keep भव address of the
	user data */
	dma_addr_t		phys_addr;
	u32			len; /* len of buffer  */
	व्योम			*payload; /* poपूर्णांकer to IOCTL Payload */
	u8			inProgress;/*अगर 1 - the IOCTL request is in
	progress */
	व्योम			*param1;
	व्योम			*param2;
	व्योम			*param3;
पूर्ण;

/* pm8001 workqueue */
बाह्य काष्ठा workqueue_काष्ठा *pm8001_wq;

/******************** function prototype *********************/
पूर्णांक pm8001_tag_alloc(काष्ठा pm8001_hba_info *pm8001_ha, u32 *tag_out);
व्योम pm8001_tag_init(काष्ठा pm8001_hba_info *pm8001_ha);
u32 pm8001_get_ncq_tag(काष्ठा sas_task *task, u32 *tag);
व्योम pm8001_ccb_task_मुक्त(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा sas_task *task, काष्ठा pm8001_ccb_info *ccb, u32 ccb_idx);
पूर्णांक pm8001_phy_control(काष्ठा asd_sas_phy *sas_phy, क्रमागत phy_func func,
	व्योम *funcdata);
व्योम pm8001_scan_start(काष्ठा Scsi_Host *shost);
पूर्णांक pm8001_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय);
पूर्णांक pm8001_queue_command(काष्ठा sas_task *task, gfp_t gfp_flags);
पूर्णांक pm8001_पात_task(काष्ठा sas_task *task);
पूर्णांक pm8001_पात_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun);
पूर्णांक pm8001_clear_aca(काष्ठा करोमुख्य_device *dev, u8 *lun);
पूर्णांक pm8001_clear_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun);
पूर्णांक pm8001_dev_found(काष्ठा करोमुख्य_device *dev);
व्योम pm8001_dev_gone(काष्ठा करोमुख्य_device *dev);
पूर्णांक pm8001_lu_reset(काष्ठा करोमुख्य_device *dev, u8 *lun);
पूर्णांक pm8001_I_T_nexus_reset(काष्ठा करोमुख्य_device *dev);
पूर्णांक pm8001_I_T_nexus_event_handler(काष्ठा करोमुख्य_device *dev);
पूर्णांक pm8001_query_task(काष्ठा sas_task *task);
व्योम pm8001_खोलो_reject_retry(
	काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा sas_task *task_to_बंद,
	काष्ठा pm8001_device *device_to_बंद);
पूर्णांक pm8001_mem_alloc(काष्ठा pci_dev *pdev, व्योम **virt_addr,
	dma_addr_t *pphys_addr, u32 *pphys_addr_hi, u32 *pphys_addr_lo,
	u32 mem_size, u32 align);

व्योम pm8001_chip_iounmap(काष्ठा pm8001_hba_info *pm8001_ha);
पूर्णांक pm8001_mpi_build_cmd(काष्ठा pm8001_hba_info *pm8001_ha,
			काष्ठा inbound_queue_table *circularQ,
			u32 opCode, व्योम *payload, माप_प्रकार nb,
			u32 responseQueue);
पूर्णांक pm8001_mpi_msg_मुक्त_get(काष्ठा inbound_queue_table *circularQ,
				u16 messageSize, व्योम **messagePtr);
u32 pm8001_mpi_msg_मुक्त_set(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *pMsg,
			काष्ठा outbound_queue_table *circularQ, u8 bc);
u32 pm8001_mpi_msg_consume(काष्ठा pm8001_hba_info *pm8001_ha,
			काष्ठा outbound_queue_table *circularQ,
			व्योम **messagePtr1, u8 *pBC);
पूर्णांक pm8001_chip_set_dev_state_req(काष्ठा pm8001_hba_info *pm8001_ha,
			काष्ठा pm8001_device *pm8001_dev, u32 state);
पूर्णांक pm8001_chip_fw_flash_update_req(काष्ठा pm8001_hba_info *pm8001_ha,
					व्योम *payload);
पूर्णांक pm8001_chip_fw_flash_update_build(काष्ठा pm8001_hba_info *pm8001_ha,
					व्योम *fw_flash_updata_info, u32 tag);
पूर्णांक pm8001_chip_set_nvmd_req(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *payload);
पूर्णांक pm8001_chip_get_nvmd_req(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *payload);
पूर्णांक pm8001_chip_ssp_पंचांग_req(काष्ठा pm8001_hba_info *pm8001_ha,
				काष्ठा pm8001_ccb_info *ccb,
				काष्ठा pm8001_पंचांगf_task *पंचांगf);
पूर्णांक pm8001_chip_पात_task(काष्ठा pm8001_hba_info *pm8001_ha,
				काष्ठा pm8001_device *pm8001_dev,
				u8 flag, u32 task_tag, u32 cmd_tag);
पूर्णांक pm8001_chip_dereg_dev_req(काष्ठा pm8001_hba_info *pm8001_ha, u32 device_id);
व्योम pm8001_chip_make_sg(काष्ठा scatterlist *scatter, पूर्णांक nr, व्योम *prd);
व्योम pm8001_work_fn(काष्ठा work_काष्ठा *work);
पूर्णांक pm8001_handle_event(काष्ठा pm8001_hba_info *pm8001_ha,
					व्योम *data, पूर्णांक handler);
व्योम pm8001_mpi_set_dev_state_resp(काष्ठा pm8001_hba_info *pm8001_ha,
							व्योम *piomb);
व्योम pm8001_mpi_set_nvmd_resp(काष्ठा pm8001_hba_info *pm8001_ha,
							व्योम *piomb);
व्योम pm8001_mpi_get_nvmd_resp(काष्ठा pm8001_hba_info *pm8001_ha,
							व्योम *piomb);
पूर्णांक pm8001_mpi_local_phy_ctl(काष्ठा pm8001_hba_info *pm8001_ha,
							व्योम *piomb);
व्योम pm8001_get_lrate_mode(काष्ठा pm8001_phy *phy, u8 link_rate);
व्योम pm8001_get_attached_sas_addr(काष्ठा pm8001_phy *phy, u8 *sas_addr);
व्योम pm8001_bytes_dmaed(काष्ठा pm8001_hba_info *pm8001_ha, पूर्णांक i);
पूर्णांक pm8001_mpi_reg_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb);
पूर्णांक pm8001_mpi_dereg_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb);
पूर्णांक pm8001_mpi_fw_flash_update_resp(काष्ठा pm8001_hba_info *pm8001_ha,
							व्योम *piomb);
पूर्णांक pm8001_mpi_general_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb);
पूर्णांक pm8001_mpi_task_पात_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb);
काष्ठा sas_task *pm8001_alloc_task(व्योम);
व्योम pm8001_task_करोne(काष्ठा sas_task *task);
व्योम pm8001_मुक्त_task(काष्ठा sas_task *task);
व्योम pm8001_tag_मुक्त(काष्ठा pm8001_hba_info *pm8001_ha, u32 tag);
काष्ठा pm8001_device *pm8001_find_dev(काष्ठा pm8001_hba_info *pm8001_ha,
					u32 device_id);
पूर्णांक pm80xx_set_thermal_config(काष्ठा pm8001_hba_info *pm8001_ha);

पूर्णांक pm8001_bar4_shअगरt(काष्ठा pm8001_hba_info *pm8001_ha, u32 shअगरtValue);
व्योम pm8001_set_phy_profile(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 length, u8 *buf);
व्योम pm8001_set_phy_profile_single(काष्ठा pm8001_hba_info *pm8001_ha,
		u32 phy, u32 length, u32 *buf);
पूर्णांक pm80xx_bar4_shअगरt(काष्ठा pm8001_hba_info *pm8001_ha, u32 shअगरtValue);
sमाप_प्रकार pm80xx_get_fatal_dump(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf);
sमाप_प्रकार pm80xx_get_non_fatal_dump(काष्ठा device *cdev,
		काष्ठा device_attribute *attr, अक्षर *buf);
sमाप_प्रकार pm8001_get_gsm_dump(काष्ठा device *cdev, u32, अक्षर *buf);
पूर्णांक pm80xx_fatal_errors(काष्ठा pm8001_hba_info *pm8001_ha);
व्योम pm8001_मुक्त_dev(काष्ठा pm8001_device *pm8001_dev);
/* ctl shared API */
बाह्य काष्ठा device_attribute *pm8001_host_attrs[];

अटल अंतरभूत व्योम
pm8001_ccb_task_मुक्त_करोne(काष्ठा pm8001_hba_info *pm8001_ha,
			काष्ठा sas_task *task, काष्ठा pm8001_ccb_info *ccb,
			u32 ccb_idx)
अणु
	pm8001_ccb_task_मुक्त(pm8001_ha, task, ccb, ccb_idx);
	smp_mb(); /*in order to क्रमce CPU ordering*/
	spin_unlock(&pm8001_ha->lock);
	task->task_करोne(task);
	spin_lock(&pm8001_ha->lock);
पूर्ण

#पूर्ण_अगर

