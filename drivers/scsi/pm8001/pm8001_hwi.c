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
 #समावेश <linux/slab.h>
 #समावेश "pm8001_sas.h"
 #समावेश "pm8001_hwi.h"
 #समावेश "pm8001_chips.h"
 #समावेश "pm8001_ctl.h"

/**
 * पढ़ो_मुख्य_config_table - पढ़ो the configure table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_मुख्य_config_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *address = pm8001_ha->मुख्य_cfg_tbl_addr;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.signature	=
				pm8001_mr32(address, 0x00);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.पूर्णांकerface_rev =
				pm8001_mr32(address, 0x04);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.firmware_rev	=
				pm8001_mr32(address, 0x08);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.max_out_io	=
				pm8001_mr32(address, 0x0C);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.max_sgl	=
				pm8001_mr32(address, 0x10);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.ctrl_cap_flag =
				pm8001_mr32(address, 0x14);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.gst_offset	=
				pm8001_mr32(address, 0x18);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.inbound_queue_offset =
		pm8001_mr32(address, MAIN_IBQ_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_queue_offset =
		pm8001_mr32(address, MAIN_OBQ_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.hda_mode_flag	=
		pm8001_mr32(address, MAIN_HDA_FLAGS_OFFSET);

	/* पढ़ो analog Setting offset from the configuration table */
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.anolog_setup_table_offset =
		pm8001_mr32(address, MAIN_ANALOG_SETUP_OFFSET);

	/* पढ़ो Error Dump Offset and Length */
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.fatal_err_dump_offset0 =
		pm8001_mr32(address, MAIN_FATAL_ERROR_RDUMP0_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.fatal_err_dump_length0 =
		pm8001_mr32(address, MAIN_FATAL_ERROR_RDUMP0_LENGTH);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.fatal_err_dump_offset1 =
		pm8001_mr32(address, MAIN_FATAL_ERROR_RDUMP1_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.fatal_err_dump_length1 =
		pm8001_mr32(address, MAIN_FATAL_ERROR_RDUMP1_LENGTH);
पूर्ण

/**
 * पढ़ो_general_status_table - पढ़ो the general status table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_general_status_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *address = pm8001_ha->general_stat_tbl_addr;
	pm8001_ha->gs_tbl.pm8001_tbl.gst_len_mpistate	=
				pm8001_mr32(address, 0x00);
	pm8001_ha->gs_tbl.pm8001_tbl.iq_मुक्तze_state0	=
				pm8001_mr32(address, 0x04);
	pm8001_ha->gs_tbl.pm8001_tbl.iq_मुक्तze_state1	=
				pm8001_mr32(address, 0x08);
	pm8001_ha->gs_tbl.pm8001_tbl.msgu_tcnt		=
				pm8001_mr32(address, 0x0C);
	pm8001_ha->gs_tbl.pm8001_tbl.iop_tcnt		=
				pm8001_mr32(address, 0x10);
	pm8001_ha->gs_tbl.pm8001_tbl.rsvd		=
				pm8001_mr32(address, 0x14);
	pm8001_ha->gs_tbl.pm8001_tbl.phy_state[0]	=
				pm8001_mr32(address, 0x18);
	pm8001_ha->gs_tbl.pm8001_tbl.phy_state[1]	=
				pm8001_mr32(address, 0x1C);
	pm8001_ha->gs_tbl.pm8001_tbl.phy_state[2]	=
				pm8001_mr32(address, 0x20);
	pm8001_ha->gs_tbl.pm8001_tbl.phy_state[3]	=
				pm8001_mr32(address, 0x24);
	pm8001_ha->gs_tbl.pm8001_tbl.phy_state[4]	=
				pm8001_mr32(address, 0x28);
	pm8001_ha->gs_tbl.pm8001_tbl.phy_state[5]	=
				pm8001_mr32(address, 0x2C);
	pm8001_ha->gs_tbl.pm8001_tbl.phy_state[6]	=
				pm8001_mr32(address, 0x30);
	pm8001_ha->gs_tbl.pm8001_tbl.phy_state[7]	=
				pm8001_mr32(address, 0x34);
	pm8001_ha->gs_tbl.pm8001_tbl.gpio_input_val	=
				pm8001_mr32(address, 0x38);
	pm8001_ha->gs_tbl.pm8001_tbl.rsvd1[0]		=
				pm8001_mr32(address, 0x3C);
	pm8001_ha->gs_tbl.pm8001_tbl.rsvd1[1]		=
				pm8001_mr32(address, 0x40);
	pm8001_ha->gs_tbl.pm8001_tbl.recover_err_info[0]	=
				pm8001_mr32(address, 0x44);
	pm8001_ha->gs_tbl.pm8001_tbl.recover_err_info[1]	=
				pm8001_mr32(address, 0x48);
	pm8001_ha->gs_tbl.pm8001_tbl.recover_err_info[2]	=
				pm8001_mr32(address, 0x4C);
	pm8001_ha->gs_tbl.pm8001_tbl.recover_err_info[3]	=
				pm8001_mr32(address, 0x50);
	pm8001_ha->gs_tbl.pm8001_tbl.recover_err_info[4]	=
				pm8001_mr32(address, 0x54);
	pm8001_ha->gs_tbl.pm8001_tbl.recover_err_info[5]	=
				pm8001_mr32(address, 0x58);
	pm8001_ha->gs_tbl.pm8001_tbl.recover_err_info[6]	=
				pm8001_mr32(address, 0x5C);
	pm8001_ha->gs_tbl.pm8001_tbl.recover_err_info[7]	=
				pm8001_mr32(address, 0x60);
पूर्ण

/**
 * पढ़ो_inbnd_queue_table - पढ़ो the inbound queue table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_inbnd_queue_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक i;
	व्योम __iomem *address = pm8001_ha->inbnd_q_tbl_addr;
	क्रम (i = 0; i < PM8001_MAX_INB_NUM; i++) अणु
		u32 offset = i * 0x20;
		pm8001_ha->inbnd_q_tbl[i].pi_pci_bar =
		      get_pci_bar_index(pm8001_mr32(address, (offset + 0x14)));
		pm8001_ha->inbnd_q_tbl[i].pi_offset =
			pm8001_mr32(address, (offset + 0x18));
	पूर्ण
पूर्ण

/**
 * पढ़ो_outbnd_queue_table - पढ़ो the outbound queue table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_outbnd_queue_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक i;
	व्योम __iomem *address = pm8001_ha->outbnd_q_tbl_addr;
	क्रम (i = 0; i < PM8001_MAX_OUTB_NUM; i++) अणु
		u32 offset = i * 0x24;
		pm8001_ha->outbnd_q_tbl[i].ci_pci_bar =
		      get_pci_bar_index(pm8001_mr32(address, (offset + 0x14)));
		pm8001_ha->outbnd_q_tbl[i].ci_offset =
			pm8001_mr32(address, (offset + 0x18));
	पूर्ण
पूर्ण

/**
 * init_शेष_table_values - init the शेष table.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम init_शेष_table_values(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक i;
	u32 offsetib, offsetob;
	व्योम __iomem *addressib = pm8001_ha->inbnd_q_tbl_addr;
	व्योम __iomem *addressob = pm8001_ha->outbnd_q_tbl_addr;
	u32 ib_offset = pm8001_ha->ib_offset;
	u32 ob_offset = pm8001_ha->ob_offset;
	u32 ci_offset = pm8001_ha->ci_offset;
	u32 pi_offset = pm8001_ha->pi_offset;

	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.inbound_q_nppd_hppd		= 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_hw_event_pid0_3	= 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_hw_event_pid4_7	= 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_ncq_event_pid0_3	= 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_ncq_event_pid4_7	= 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_tgt_ITNexus_event_pid0_3 =
									 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_tgt_ITNexus_event_pid4_7 =
									 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_tgt_ssp_event_pid0_3 = 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_tgt_ssp_event_pid4_7 = 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_tgt_smp_event_pid0_3 = 0;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_tgt_smp_event_pid4_7 = 0;

	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.upper_event_log_addr		=
		pm8001_ha->memoryMap.region[AAP1].phys_addr_hi;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.lower_event_log_addr		=
		pm8001_ha->memoryMap.region[AAP1].phys_addr_lo;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.event_log_size		=
		PM8001_EVENT_LOG_SIZE;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.event_log_option		= 0x01;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.upper_iop_event_log_addr	=
		pm8001_ha->memoryMap.region[IOP].phys_addr_hi;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.lower_iop_event_log_addr	=
		pm8001_ha->memoryMap.region[IOP].phys_addr_lo;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.iop_event_log_size		=
		PM8001_EVENT_LOG_SIZE;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.iop_event_log_option		= 0x01;
	pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.fatal_err_पूर्णांकerrupt		= 0x01;
	क्रम (i = 0; i < pm8001_ha->max_q_num; i++) अणु
		pm8001_ha->inbnd_q_tbl[i].element_pri_size_cnt	=
			PM8001_MPI_QUEUE | (pm8001_ha->iomb_size << 16) | (0x00<<30);
		pm8001_ha->inbnd_q_tbl[i].upper_base_addr	=
			pm8001_ha->memoryMap.region[ib_offset + i].phys_addr_hi;
		pm8001_ha->inbnd_q_tbl[i].lower_base_addr	=
		pm8001_ha->memoryMap.region[ib_offset + i].phys_addr_lo;
		pm8001_ha->inbnd_q_tbl[i].base_virt		=
		  (u8 *)pm8001_ha->memoryMap.region[ib_offset + i].virt_ptr;
		pm8001_ha->inbnd_q_tbl[i].total_length		=
			pm8001_ha->memoryMap.region[ib_offset + i].total_len;
		pm8001_ha->inbnd_q_tbl[i].ci_upper_base_addr	=
			pm8001_ha->memoryMap.region[ci_offset + i].phys_addr_hi;
		pm8001_ha->inbnd_q_tbl[i].ci_lower_base_addr	=
			pm8001_ha->memoryMap.region[ci_offset + i].phys_addr_lo;
		pm8001_ha->inbnd_q_tbl[i].ci_virt		=
			pm8001_ha->memoryMap.region[ci_offset + i].virt_ptr;
		pm8001_ग_लिखो_32(pm8001_ha->inbnd_q_tbl[i].ci_virt, 0, 0);
		offsetib = i * 0x20;
		pm8001_ha->inbnd_q_tbl[i].pi_pci_bar		=
			get_pci_bar_index(pm8001_mr32(addressib,
				(offsetib + 0x14)));
		pm8001_ha->inbnd_q_tbl[i].pi_offset		=
			pm8001_mr32(addressib, (offsetib + 0x18));
		pm8001_ha->inbnd_q_tbl[i].producer_idx		= 0;
		pm8001_ha->inbnd_q_tbl[i].consumer_index	= 0;
	पूर्ण
	क्रम (i = 0; i < pm8001_ha->max_q_num; i++) अणु
		pm8001_ha->outbnd_q_tbl[i].element_size_cnt	=
			PM8001_MPI_QUEUE | (pm8001_ha->iomb_size << 16) | (0x01<<30);
		pm8001_ha->outbnd_q_tbl[i].upper_base_addr	=
			pm8001_ha->memoryMap.region[ob_offset + i].phys_addr_hi;
		pm8001_ha->outbnd_q_tbl[i].lower_base_addr	=
			pm8001_ha->memoryMap.region[ob_offset + i].phys_addr_lo;
		pm8001_ha->outbnd_q_tbl[i].base_virt		=
		  (u8 *)pm8001_ha->memoryMap.region[ob_offset + i].virt_ptr;
		pm8001_ha->outbnd_q_tbl[i].total_length		=
			pm8001_ha->memoryMap.region[ob_offset + i].total_len;
		pm8001_ha->outbnd_q_tbl[i].pi_upper_base_addr	=
			pm8001_ha->memoryMap.region[pi_offset + i].phys_addr_hi;
		pm8001_ha->outbnd_q_tbl[i].pi_lower_base_addr	=
			pm8001_ha->memoryMap.region[pi_offset + i].phys_addr_lo;
		pm8001_ha->outbnd_q_tbl[i].पूर्णांकerrup_vec_cnt_delay	=
			0 | (10 << 16) | (i << 24);
		pm8001_ha->outbnd_q_tbl[i].pi_virt		=
			pm8001_ha->memoryMap.region[pi_offset + i].virt_ptr;
		pm8001_ग_लिखो_32(pm8001_ha->outbnd_q_tbl[i].pi_virt, 0, 0);
		offsetob = i * 0x24;
		pm8001_ha->outbnd_q_tbl[i].ci_pci_bar		=
			get_pci_bar_index(pm8001_mr32(addressob,
			offsetob + 0x14));
		pm8001_ha->outbnd_q_tbl[i].ci_offset		=
			pm8001_mr32(addressob, (offsetob + 0x18));
		pm8001_ha->outbnd_q_tbl[i].consumer_idx		= 0;
		pm8001_ha->outbnd_q_tbl[i].producer_index	= 0;
	पूर्ण
पूर्ण

/**
 * update_मुख्य_config_table - update the मुख्य शेष table to the HBA.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम update_मुख्य_config_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *address = pm8001_ha->मुख्य_cfg_tbl_addr;
	pm8001_mw32(address, 0x24,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.inbound_q_nppd_hppd);
	pm8001_mw32(address, 0x28,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_hw_event_pid0_3);
	pm8001_mw32(address, 0x2C,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_hw_event_pid4_7);
	pm8001_mw32(address, 0x30,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_ncq_event_pid0_3);
	pm8001_mw32(address, 0x34,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.outbound_ncq_event_pid4_7);
	pm8001_mw32(address, 0x38,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.
					outbound_tgt_ITNexus_event_pid0_3);
	pm8001_mw32(address, 0x3C,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.
					outbound_tgt_ITNexus_event_pid4_7);
	pm8001_mw32(address, 0x40,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.
					outbound_tgt_ssp_event_pid0_3);
	pm8001_mw32(address, 0x44,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.
					outbound_tgt_ssp_event_pid4_7);
	pm8001_mw32(address, 0x48,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.
					outbound_tgt_smp_event_pid0_3);
	pm8001_mw32(address, 0x4C,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.
					outbound_tgt_smp_event_pid4_7);
	pm8001_mw32(address, 0x50,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.upper_event_log_addr);
	pm8001_mw32(address, 0x54,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.lower_event_log_addr);
	pm8001_mw32(address, 0x58,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.event_log_size);
	pm8001_mw32(address, 0x5C,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.event_log_option);
	pm8001_mw32(address, 0x60,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.upper_iop_event_log_addr);
	pm8001_mw32(address, 0x64,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.lower_iop_event_log_addr);
	pm8001_mw32(address, 0x68,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.iop_event_log_size);
	pm8001_mw32(address, 0x6C,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.iop_event_log_option);
	pm8001_mw32(address, 0x70,
		pm8001_ha->मुख्य_cfg_tbl.pm8001_tbl.fatal_err_पूर्णांकerrupt);
पूर्ण

/**
 * update_inbnd_queue_table - update the inbound queue table to the HBA.
 * @pm8001_ha: our hba card inक्रमmation
 * @number: entry in the queue
 */
अटल व्योम update_inbnd_queue_table(काष्ठा pm8001_hba_info *pm8001_ha,
				     पूर्णांक number)
अणु
	व्योम __iomem *address = pm8001_ha->inbnd_q_tbl_addr;
	u16 offset = number * 0x20;
	pm8001_mw32(address, offset + 0x00,
		pm8001_ha->inbnd_q_tbl[number].element_pri_size_cnt);
	pm8001_mw32(address, offset + 0x04,
		pm8001_ha->inbnd_q_tbl[number].upper_base_addr);
	pm8001_mw32(address, offset + 0x08,
		pm8001_ha->inbnd_q_tbl[number].lower_base_addr);
	pm8001_mw32(address, offset + 0x0C,
		pm8001_ha->inbnd_q_tbl[number].ci_upper_base_addr);
	pm8001_mw32(address, offset + 0x10,
		pm8001_ha->inbnd_q_tbl[number].ci_lower_base_addr);
पूर्ण

/**
 * update_outbnd_queue_table - update the outbound queue table to the HBA.
 * @pm8001_ha: our hba card inक्रमmation
 * @number: entry in the queue
 */
अटल व्योम update_outbnd_queue_table(काष्ठा pm8001_hba_info *pm8001_ha,
				      पूर्णांक number)
अणु
	व्योम __iomem *address = pm8001_ha->outbnd_q_tbl_addr;
	u16 offset = number * 0x24;
	pm8001_mw32(address, offset + 0x00,
		pm8001_ha->outbnd_q_tbl[number].element_size_cnt);
	pm8001_mw32(address, offset + 0x04,
		pm8001_ha->outbnd_q_tbl[number].upper_base_addr);
	pm8001_mw32(address, offset + 0x08,
		pm8001_ha->outbnd_q_tbl[number].lower_base_addr);
	pm8001_mw32(address, offset + 0x0C,
		pm8001_ha->outbnd_q_tbl[number].pi_upper_base_addr);
	pm8001_mw32(address, offset + 0x10,
		pm8001_ha->outbnd_q_tbl[number].pi_lower_base_addr);
	pm8001_mw32(address, offset + 0x1C,
		pm8001_ha->outbnd_q_tbl[number].पूर्णांकerrup_vec_cnt_delay);
पूर्ण

/**
 * pm8001_bar4_shअगरt - function is called to shअगरt BAR base address
 * @pm8001_ha : our hba card infomation
 * @shअगरtValue : shअगरting value in memory bar.
 */
पूर्णांक pm8001_bar4_shअगरt(काष्ठा pm8001_hba_info *pm8001_ha, u32 shअगरtValue)
अणु
	u32 regVal;
	अचिन्हित दीर्घ start;

	/* program the inbound AXI translation Lower Address */
	pm8001_cw32(pm8001_ha, 1, SPC_IBW_AXI_TRANSLATION_LOW, shअगरtValue);

	/* confirm the setting is written */
	start = jअगरfies + HZ; /* 1 sec */
	करो अणु
		regVal = pm8001_cr32(pm8001_ha, 1, SPC_IBW_AXI_TRANSLATION_LOW);
	पूर्ण जबतक ((regVal != shअगरtValue) && समय_beक्रमe(jअगरfies, start));

	अगर (regVal != shअगरtValue) अणु
		pm8001_dbg(pm8001_ha, INIT,
			   "TIMEOUT:SPC_IBW_AXI_TRANSLATION_LOW = 0x%x\n",
			   regVal);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mpi_set_phys_g3_with_ssc
 * @pm8001_ha: our hba card inक्रमmation
 * @SSCbit: set SSCbit to 0 to disable all phys ssc; 1 to enable all phys ssc.
 */
अटल व्योम mpi_set_phys_g3_with_ssc(काष्ठा pm8001_hba_info *pm8001_ha,
				     u32 SSCbit)
अणु
	u32 offset, i;
	अचिन्हित दीर्घ flags;

#घोषणा SAS2_SETTINGS_LOCAL_PHY_0_3_SHIFT_ADDR 0x00030000
#घोषणा SAS2_SETTINGS_LOCAL_PHY_4_7_SHIFT_ADDR 0x00040000
#घोषणा SAS2_SETTINGS_LOCAL_PHY_0_3_OFFSET 0x1074
#घोषणा SAS2_SETTINGS_LOCAL_PHY_4_7_OFFSET 0x1074
#घोषणा PHY_G3_WITHOUT_SSC_BIT_SHIFT 12
#घोषणा PHY_G3_WITH_SSC_BIT_SHIFT 13
#घोषणा SNW3_PHY_CAPABILITIES_PARITY 31

   /*
    * Using shअगरted destination address 0x3_0000:0x1074 + 0x4000*N (N=0:3)
    * Using shअगरted destination address 0x4_0000:0x1074 + 0x4000*(N-4) (N=4:7)
    */
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha,
				SAS2_SETTINGS_LOCAL_PHY_0_3_SHIFT_ADDR)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		offset = SAS2_SETTINGS_LOCAL_PHY_0_3_OFFSET + 0x4000 * i;
		pm8001_cw32(pm8001_ha, 2, offset, 0x80001501);
	पूर्ण
	/* shअगरt membase 3 क्रम SAS2_SETTINGS_LOCAL_PHY 4 - 7 */
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha,
				SAS2_SETTINGS_LOCAL_PHY_4_7_SHIFT_ADDR)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		वापस;
	पूर्ण
	क्रम (i = 4; i < 8; i++) अणु
		offset = SAS2_SETTINGS_LOCAL_PHY_4_7_OFFSET + 0x4000 * (i-4);
		pm8001_cw32(pm8001_ha, 2, offset, 0x80001501);
	पूर्ण
	/*************************************************************
	Change the SSC upspपढ़ोing value to 0x0 so that upspपढ़ोing is disabled.
	Device MABC SMOD0 Controls
	Address: (via MEMBASE-III):
	Using shअगरted destination address 0x0_0000: with Offset 0xD8

	31:28 R/W Reserved Do not change
	27:24 R/W SAS_SMOD_SPRDUP 0000
	23:20 R/W SAS_SMOD_SPRDDN 0000
	19:0  R/W  Reserved Do not change
	Upon घातer-up this रेजिस्टर will पढ़ो as 0x8990c016,
	and I would like you to change the SAS_SMOD_SPRDUP bits to 0b0000
	so that the written value will be 0x8090c016.
	This will ensure only करोwn-spपढ़ोing SSC is enabled on the SPC.
	*************************************************************/
	pm8001_cr32(pm8001_ha, 2, 0xd8);
	pm8001_cw32(pm8001_ha, 2, 0xd8, 0x8000C016);

	/*set the shअगरted destination address to 0x0 to aव्योम error operation */
	pm8001_bar4_shअगरt(pm8001_ha, 0x0);
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	वापस;
पूर्ण

/**
 * mpi_set_खोलो_retry_पूर्णांकerval_reg
 * @pm8001_ha: our hba card inक्रमmation
 * @पूर्णांकerval: पूर्णांकerval समय क्रम each OPEN_REJECT (RETRY). The units are in 1us.
 */
अटल व्योम mpi_set_खोलो_retry_पूर्णांकerval_reg(काष्ठा pm8001_hba_info *pm8001_ha,
					    u32 पूर्णांकerval)
अणु
	u32 offset;
	u32 value;
	u32 i;
	अचिन्हित दीर्घ flags;

#घोषणा OPEN_RETRY_INTERVAL_PHY_0_3_SHIFT_ADDR 0x00030000
#घोषणा OPEN_RETRY_INTERVAL_PHY_4_7_SHIFT_ADDR 0x00040000
#घोषणा OPEN_RETRY_INTERVAL_PHY_0_3_OFFSET 0x30B4
#घोषणा OPEN_RETRY_INTERVAL_PHY_4_7_OFFSET 0x30B4
#घोषणा OPEN_RETRY_INTERVAL_REG_MASK 0x0000FFFF

	value = पूर्णांकerval & OPEN_RETRY_INTERVAL_REG_MASK;
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	/* shअगरt bar and set the OPEN_REJECT(RETRY) पूर्णांकerval समय of PHY 0 -3.*/
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha,
			     OPEN_RETRY_INTERVAL_PHY_0_3_SHIFT_ADDR)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		वापस;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		offset = OPEN_RETRY_INTERVAL_PHY_0_3_OFFSET + 0x4000 * i;
		pm8001_cw32(pm8001_ha, 2, offset, value);
	पूर्ण

	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha,
			     OPEN_RETRY_INTERVAL_PHY_4_7_SHIFT_ADDR)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		वापस;
	पूर्ण
	क्रम (i = 4; i < 8; i++) अणु
		offset = OPEN_RETRY_INTERVAL_PHY_4_7_OFFSET + 0x4000 * (i-4);
		pm8001_cw32(pm8001_ha, 2, offset, value);
	पूर्ण
	/*set the shअगरted destination address to 0x0 to aव्योम error operation */
	pm8001_bar4_shअगरt(pm8001_ha, 0x0);
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	वापस;
पूर्ण

/**
 * mpi_init_check - check firmware initialization status.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल पूर्णांक mpi_init_check(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 max_रुको_count;
	u32 value;
	u32 gst_len_mpistate;
	/* Write bit0=1 to Inbound DoorBell Register to tell the SPC FW the
	table is updated */
	pm8001_cw32(pm8001_ha, 0, MSGU_IBDB_SET, SPC_MSGU_CFG_TABLE_UPDATE);
	/* रुको until Inbound DoorBell Clear Register toggled */
	max_रुको_count = 1 * 1000 * 1000;/* 1 sec */
	करो अणु
		udelay(1);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_IBDB_SET);
		value &= SPC_MSGU_CFG_TABLE_UPDATE;
	पूर्ण जबतक ((value != 0) && (--max_रुको_count));

	अगर (!max_रुको_count)
		वापस -1;
	/* check the MPI-State क्रम initialization */
	gst_len_mpistate =
		pm8001_mr32(pm8001_ha->general_stat_tbl_addr,
		GST_GSTLEN_MPIS_OFFSET);
	अगर (GST_MPI_STATE_INIT != (gst_len_mpistate & GST_MPI_STATE_MASK))
		वापस -1;
	/* check MPI Initialization error */
	gst_len_mpistate = gst_len_mpistate >> 16;
	अगर (0x0000 != gst_len_mpistate)
		वापस -1;
	वापस 0;
पूर्ण

/**
 * check_fw_पढ़ोy - The LLDD check अगर the FW is पढ़ोy, अगर not, वापस error.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल पूर्णांक check_fw_पढ़ोy(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 value, value1;
	u32 max_रुको_count;
	/* check error state */
	value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
	value1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2);
	/* check AAP error */
	अगर (SCRATCH_PAD1_ERR == (value & SCRATCH_PAD_STATE_MASK)) अणु
		/* error state */
		value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0);
		वापस -1;
	पूर्ण

	/* check IOP error */
	अगर (SCRATCH_PAD2_ERR == (value1 & SCRATCH_PAD_STATE_MASK)) अणु
		/* error state */
		value1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3);
		वापस -1;
	पूर्ण

	/* bit 4-31 of scratch pad1 should be zeros अगर it is not
	in error state*/
	अगर (value & SCRATCH_PAD1_STATE_MASK) अणु
		/* error हाल */
		pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0);
		वापस -1;
	पूर्ण

	/* bit 2, 4-31 of scratch pad2 should be zeros अगर it is not
	in error state */
	अगर (value1 & SCRATCH_PAD2_STATE_MASK) अणु
		/* error हाल */
		वापस -1;
	पूर्ण

	max_रुको_count = 1 * 1000 * 1000;/* 1 sec समयout */

	/* रुको until scratch pad 1 and 2 रेजिस्टरs in पढ़ोy state  */
	करो अणु
		udelay(1);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1)
			& SCRATCH_PAD1_RDY;
		value1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2)
			& SCRATCH_PAD2_RDY;
		अगर ((--max_रुको_count) == 0)
			वापस -1;
	पूर्ण जबतक ((value != SCRATCH_PAD1_RDY) || (value1 != SCRATCH_PAD2_RDY));
	वापस 0;
पूर्ण

अटल व्योम init_pci_device_addresses(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *base_addr;
	u32	value;
	u32	offset;
	u32	pcibar;
	u32	pcilogic;

	value = pm8001_cr32(pm8001_ha, 0, 0x44);
	offset = value & 0x03FFFFFF;
	pm8001_dbg(pm8001_ha, INIT, "Scratchpad 0 Offset: %x\n", offset);
	pcilogic = (value & 0xFC000000) >> 26;
	pcibar = get_pci_bar_index(pcilogic);
	pm8001_dbg(pm8001_ha, INIT, "Scratchpad 0 PCI BAR: %d\n", pcibar);
	pm8001_ha->मुख्य_cfg_tbl_addr = base_addr =
		pm8001_ha->io_mem[pcibar].memvirtaddr + offset;
	pm8001_ha->general_stat_tbl_addr =
		base_addr + pm8001_cr32(pm8001_ha, pcibar, offset + 0x18);
	pm8001_ha->inbnd_q_tbl_addr =
		base_addr + pm8001_cr32(pm8001_ha, pcibar, offset + 0x1C);
	pm8001_ha->outbnd_q_tbl_addr =
		base_addr + pm8001_cr32(pm8001_ha, pcibar, offset + 0x20);
पूर्ण

/**
 * pm8001_chip_init - the मुख्य init function that initialize whole PM8001 chip.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल पूर्णांक pm8001_chip_init(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 i = 0;
	u16 deviceid;
	pci_पढ़ो_config_word(pm8001_ha->pdev, PCI_DEVICE_ID, &deviceid);
	/* 8081 controllers need BAR shअगरt to access MPI space
	* as this is shared with BIOS data */
	अगर (deviceid == 0x8081 || deviceid == 0x0042) अणु
		अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, GSM_SM_BASE)) अणु
			pm8001_dbg(pm8001_ha, FAIL,
				   "Shift Bar4 to 0x%x failed\n",
				   GSM_SM_BASE);
			वापस -1;
		पूर्ण
	पूर्ण
	/* check the firmware status */
	अगर (-1 == check_fw_पढ़ोy(pm8001_ha)) अणु
		pm8001_dbg(pm8001_ha, FAIL, "Firmware is not ready!\n");
		वापस -EBUSY;
	पूर्ण

	/* Initialize pci space address eg: mpi offset */
	init_pci_device_addresses(pm8001_ha);
	init_शेष_table_values(pm8001_ha);
	पढ़ो_मुख्य_config_table(pm8001_ha);
	पढ़ो_general_status_table(pm8001_ha);
	पढ़ो_inbnd_queue_table(pm8001_ha);
	पढ़ो_outbnd_queue_table(pm8001_ha);
	/* update मुख्य config table ,inbound table and outbound table */
	update_मुख्य_config_table(pm8001_ha);
	क्रम (i = 0; i < pm8001_ha->max_q_num; i++)
		update_inbnd_queue_table(pm8001_ha, i);
	क्रम (i = 0; i < pm8001_ha->max_q_num; i++)
		update_outbnd_queue_table(pm8001_ha, i);
	/* 8081 controller करोnot require these operations */
	अगर (deviceid != 0x8081 && deviceid != 0x0042) अणु
		mpi_set_phys_g3_with_ssc(pm8001_ha, 0);
		/* 7->130ms, 34->500ms, 119->1.5s */
		mpi_set_खोलो_retry_पूर्णांकerval_reg(pm8001_ha, 119);
	पूर्ण
	/* notअगरy firmware update finished and check initialization status */
	अगर (0 == mpi_init_check(pm8001_ha)) अणु
		pm8001_dbg(pm8001_ha, INIT, "MPI initialize successful!\n");
	पूर्ण अन्यथा
		वापस -EBUSY;
	/*This रेजिस्टर is a 16-bit समयr with a resolution of 1us. This is the
	समयr used क्रम पूर्णांकerrupt delay/coalescing in the PCIe Application Layer.
	Zero is not a valid value. A value of 1 in the रेजिस्टर will cause the
	पूर्णांकerrupts to be normal. A value greater than 1 will cause coalescing
	delays.*/
	pm8001_cw32(pm8001_ha, 1, 0x0033c0, 0x1);
	pm8001_cw32(pm8001_ha, 1, 0x0033c4, 0x0);
	वापस 0;
पूर्ण

अटल पूर्णांक mpi_uninit_check(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 max_रुको_count;
	u32 value;
	u32 gst_len_mpistate;
	u16 deviceid;
	pci_पढ़ो_config_word(pm8001_ha->pdev, PCI_DEVICE_ID, &deviceid);
	अगर (deviceid == 0x8081 || deviceid == 0x0042) अणु
		अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, GSM_SM_BASE)) अणु
			pm8001_dbg(pm8001_ha, FAIL,
				   "Shift Bar4 to 0x%x failed\n",
				   GSM_SM_BASE);
			वापस -1;
		पूर्ण
	पूर्ण
	init_pci_device_addresses(pm8001_ha);
	/* Write bit1=1 to Inbound DoorBell Register to tell the SPC FW the
	table is stop */
	pm8001_cw32(pm8001_ha, 0, MSGU_IBDB_SET, SPC_MSGU_CFG_TABLE_RESET);

	/* रुको until Inbound DoorBell Clear Register toggled */
	max_रुको_count = 1 * 1000 * 1000;/* 1 sec */
	करो अणु
		udelay(1);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_IBDB_SET);
		value &= SPC_MSGU_CFG_TABLE_RESET;
	पूर्ण जबतक ((value != 0) && (--max_रुको_count));

	अगर (!max_रुको_count) अणु
		pm8001_dbg(pm8001_ha, FAIL, "TIMEOUT:IBDB value/=0x%x\n",
			   value);
		वापस -1;
	पूर्ण

	/* check the MPI-State क्रम termination in progress */
	/* रुको until Inbound DoorBell Clear Register toggled */
	max_रुको_count = 1 * 1000 * 1000;  /* 1 sec */
	करो अणु
		udelay(1);
		gst_len_mpistate =
			pm8001_mr32(pm8001_ha->general_stat_tbl_addr,
			GST_GSTLEN_MPIS_OFFSET);
		अगर (GST_MPI_STATE_UNINIT ==
			(gst_len_mpistate & GST_MPI_STATE_MASK))
			अवरोध;
	पूर्ण जबतक (--max_रुको_count);
	अगर (!max_रुको_count) अणु
		pm8001_dbg(pm8001_ha, FAIL, " TIME OUT MPI State = 0x%x\n",
			   gst_len_mpistate & GST_MPI_STATE_MASK);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * soft_reset_पढ़ोy_check - Function to check FW is पढ़ोy क्रम soft reset.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल u32 soft_reset_पढ़ोy_check(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 regVal, regVal1, regVal2;
	अगर (mpi_uninit_check(pm8001_ha) != 0) अणु
		pm8001_dbg(pm8001_ha, FAIL, "MPI state is not ready\n");
		वापस -1;
	पूर्ण
	/* पढ़ो the scratch pad 2 रेजिस्टर bit 2 */
	regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2)
		& SCRATCH_PAD2_FWRDY_RST;
	अगर (regVal == SCRATCH_PAD2_FWRDY_RST) अणु
		pm8001_dbg(pm8001_ha, INIT, "Firmware is ready for reset.\n");
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		/* Trigger NMI twice via RB6 */
		spin_lock_irqsave(&pm8001_ha->lock, flags);
		अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, RB6_ACCESS_REG)) अणु
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			pm8001_dbg(pm8001_ha, FAIL,
				   "Shift Bar4 to 0x%x failed\n",
				   RB6_ACCESS_REG);
			वापस -1;
		पूर्ण
		pm8001_cw32(pm8001_ha, 2, SPC_RB6_OFFSET,
			RB6_MAGIC_NUMBER_RST);
		pm8001_cw32(pm8001_ha, 2, SPC_RB6_OFFSET, RB6_MAGIC_NUMBER_RST);
		/* रुको क्रम 100 ms */
		mdelay(100);
		regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2) &
			SCRATCH_PAD2_FWRDY_RST;
		अगर (regVal != SCRATCH_PAD2_FWRDY_RST) अणु
			regVal1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
			regVal2 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2);
			pm8001_dbg(pm8001_ha, FAIL, "TIMEOUT:MSGU_SCRATCH_PAD1=0x%x, MSGU_SCRATCH_PAD2=0x%x\n",
				   regVal1, regVal2);
			pm8001_dbg(pm8001_ha, FAIL,
				   "SCRATCH_PAD0 value = 0x%x\n",
				   pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0));
			pm8001_dbg(pm8001_ha, FAIL,
				   "SCRATCH_PAD3 value = 0x%x\n",
				   pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3));
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			वापस -1;
		पूर्ण
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pm8001_chip_soft_rst - soft reset the PM8001 chip, so that the clear all
 * the FW रेजिस्टर status to the originated status.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल पूर्णांक
pm8001_chip_soft_rst(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32	regVal, toggleVal;
	u32	max_रुको_count;
	u32	regVal1, regVal2, regVal3;
	u32	signature = 0x252acbcd; /* क्रम host scratch pad0 */
	अचिन्हित दीर्घ flags;

	/* step1: Check FW is पढ़ोy क्रम soft reset */
	अगर (soft_reset_पढ़ोy_check(pm8001_ha) != 0) अणु
		pm8001_dbg(pm8001_ha, FAIL, "FW is not ready\n");
		वापस -1;
	पूर्ण

	/* step 2: clear NMI status रेजिस्टर on AAP1 and IOP, ग_लिखो the same
	value to clear */
	/* map 0x60000 to BAR4(0x20), BAR2(win) */
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, MBIC_AAP1_ADDR_BASE)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "Shift Bar4 to 0x%x failed\n",
			   MBIC_AAP1_ADDR_BASE);
		वापस -1;
	पूर्ण
	regVal = pm8001_cr32(pm8001_ha, 2, MBIC_NMI_ENABLE_VPE0_IOP);
	pm8001_dbg(pm8001_ha, INIT, "MBIC - NMI Enable VPE0 (IOP)= 0x%x\n",
		   regVal);
	pm8001_cw32(pm8001_ha, 2, MBIC_NMI_ENABLE_VPE0_IOP, 0x0);
	/* map 0x70000 to BAR4(0x20), BAR2(win) */
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, MBIC_IOP_ADDR_BASE)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "Shift Bar4 to 0x%x failed\n",
			   MBIC_IOP_ADDR_BASE);
		वापस -1;
	पूर्ण
	regVal = pm8001_cr32(pm8001_ha, 2, MBIC_NMI_ENABLE_VPE0_AAP1);
	pm8001_dbg(pm8001_ha, INIT, "MBIC - NMI Enable VPE0 (AAP1)= 0x%x\n",
		   regVal);
	pm8001_cw32(pm8001_ha, 2, MBIC_NMI_ENABLE_VPE0_AAP1, 0x0);

	regVal = pm8001_cr32(pm8001_ha, 1, PCIE_EVENT_INTERRUPT_ENABLE);
	pm8001_dbg(pm8001_ha, INIT, "PCIE -Event Interrupt Enable = 0x%x\n",
		   regVal);
	pm8001_cw32(pm8001_ha, 1, PCIE_EVENT_INTERRUPT_ENABLE, 0x0);

	regVal = pm8001_cr32(pm8001_ha, 1, PCIE_EVENT_INTERRUPT);
	pm8001_dbg(pm8001_ha, INIT, "PCIE - Event Interrupt  = 0x%x\n",
		   regVal);
	pm8001_cw32(pm8001_ha, 1, PCIE_EVENT_INTERRUPT, regVal);

	regVal = pm8001_cr32(pm8001_ha, 1, PCIE_ERROR_INTERRUPT_ENABLE);
	pm8001_dbg(pm8001_ha, INIT, "PCIE -Error Interrupt Enable = 0x%x\n",
		   regVal);
	pm8001_cw32(pm8001_ha, 1, PCIE_ERROR_INTERRUPT_ENABLE, 0x0);

	regVal = pm8001_cr32(pm8001_ha, 1, PCIE_ERROR_INTERRUPT);
	pm8001_dbg(pm8001_ha, INIT, "PCIE - Error Interrupt = 0x%x\n", regVal);
	pm8001_cw32(pm8001_ha, 1, PCIE_ERROR_INTERRUPT, regVal);

	/* पढ़ो the scratch pad 1 रेजिस्टर bit 2 */
	regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1)
		& SCRATCH_PAD1_RST;
	toggleVal = regVal ^ SCRATCH_PAD1_RST;

	/* set signature in host scratch pad0 रेजिस्टर to tell SPC that the
	host perक्रमms the soft reset */
	pm8001_cw32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_0, signature);

	/* पढ़ो required रेजिस्टरs क्रम confirmming */
	/* map 0x0700000 to BAR4(0x20), BAR2(win) */
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, GSM_ADDR_BASE)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "Shift Bar4 to 0x%x failed\n",
			   GSM_ADDR_BASE);
		वापस -1;
	पूर्ण
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x0(0x00007b88)-GSM Configuration and Reset = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET));

	/* step 3: host पढ़ो GSM Configuration and Reset रेजिस्टर */
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET);
	/* Put those bits to low */
	/* GSM XCBI offset = 0x70 0000
	0x00 Bit 13 COM_SLV_SW_RSTB 1
	0x00 Bit 12 QSSP_SW_RSTB 1
	0x00 Bit 11 RAAE_SW_RSTB 1
	0x00 Bit 9 RB_1_SW_RSTB 1
	0x00 Bit 8 SM_SW_RSTB 1
	*/
	regVal &= ~(0x00003b00);
	/* host ग_लिखो GSM Configuration and Reset रेजिस्टर */
	pm8001_cw32(pm8001_ha, 2, GSM_CONFIG_RESET, regVal);
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x0 (0x00007b88 ==> 0x00004088) - GSM Configuration and Reset is set to = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET));

	/* step 4: */
	/* disable GSM - Read Address Parity Check */
	regVal1 = pm8001_cr32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK);
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x700038 - Read Address Parity Check Enable = 0x%x\n",
		   regVal1);
	pm8001_cw32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK, 0x0);
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x700038 - Read Address Parity Check Enable is set to = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK));

	/* disable GSM - Write Address Parity Check */
	regVal2 = pm8001_cr32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK);
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x700040 - Write Address Parity Check Enable = 0x%x\n",
		   regVal2);
	pm8001_cw32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK, 0x0);
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x700040 - Write Address Parity Check Enable is set to = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK));

	/* disable GSM - Write Data Parity Check */
	regVal3 = pm8001_cr32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK);
	pm8001_dbg(pm8001_ha, INIT, "GSM 0x300048 - Write Data Parity Check Enable = 0x%x\n",
		   regVal3);
	pm8001_cw32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK, 0x0);
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x300048 - Write Data Parity Check Enable is set to = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK));

	/* step 5: delay 10 usec */
	udelay(10);
	/* step 5-b: set GPIO-0 output control to tristate anyway */
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, GPIO_ADDR_BASE)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		pm8001_dbg(pm8001_ha, INIT, "Shift Bar4 to 0x%x failed\n",
			   GPIO_ADDR_BASE);
		वापस -1;
	पूर्ण
	regVal = pm8001_cr32(pm8001_ha, 2, GPIO_GPIO_0_0UTPUT_CTL_OFFSET);
	pm8001_dbg(pm8001_ha, INIT, "GPIO Output Control Register: = 0x%x\n",
		   regVal);
	/* set GPIO-0 output control to tri-state */
	regVal &= 0xFFFFFFFC;
	pm8001_cw32(pm8001_ha, 2, GPIO_GPIO_0_0UTPUT_CTL_OFFSET, regVal);

	/* Step 6: Reset the IOP and AAP1 */
	/* map 0x00000 to BAR4(0x20), BAR2(win) */
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, SPC_TOP_LEVEL_ADDR_BASE)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "SPC Shift Bar4 to 0x%x failed\n",
			   SPC_TOP_LEVEL_ADDR_BASE);
		वापस -1;
	पूर्ण
	regVal = pm8001_cr32(pm8001_ha, 2, SPC_REG_RESET);
	pm8001_dbg(pm8001_ha, INIT, "Top Register before resetting IOP/AAP1:= 0x%x\n",
		   regVal);
	regVal &= ~(SPC_REG_RESET_PCS_IOP_SS | SPC_REG_RESET_PCS_AAP1_SS);
	pm8001_cw32(pm8001_ha, 2, SPC_REG_RESET, regVal);

	/* step 7: Reset the BDMA/OSSP */
	regVal = pm8001_cr32(pm8001_ha, 2, SPC_REG_RESET);
	pm8001_dbg(pm8001_ha, INIT, "Top Register before resetting BDMA/OSSP: = 0x%x\n",
		   regVal);
	regVal &= ~(SPC_REG_RESET_BDMA_CORE | SPC_REG_RESET_OSSP);
	pm8001_cw32(pm8001_ha, 2, SPC_REG_RESET, regVal);

	/* step 8: delay 10 usec */
	udelay(10);

	/* step 9: bring the BDMA and OSSP out of reset */
	regVal = pm8001_cr32(pm8001_ha, 2, SPC_REG_RESET);
	pm8001_dbg(pm8001_ha, INIT,
		   "Top Register before bringing up BDMA/OSSP:= 0x%x\n",
		   regVal);
	regVal |= (SPC_REG_RESET_BDMA_CORE | SPC_REG_RESET_OSSP);
	pm8001_cw32(pm8001_ha, 2, SPC_REG_RESET, regVal);

	/* step 10: delay 10 usec */
	udelay(10);

	/* step 11: पढ़ोs and sets the GSM Configuration and Reset Register */
	/* map 0x0700000 to BAR4(0x20), BAR2(win) */
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, GSM_ADDR_BASE)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "SPC Shift Bar4 to 0x%x failed\n",
			   GSM_ADDR_BASE);
		वापस -1;
	पूर्ण
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x0 (0x00007b88)-GSM Configuration and Reset = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET));
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET);
	/* Put those bits to high */
	/* GSM XCBI offset = 0x70 0000
	0x00 Bit 13 COM_SLV_SW_RSTB 1
	0x00 Bit 12 QSSP_SW_RSTB 1
	0x00 Bit 11 RAAE_SW_RSTB 1
	0x00 Bit 9   RB_1_SW_RSTB 1
	0x00 Bit 8   SM_SW_RSTB 1
	*/
	regVal |= (GSM_CONFIG_RESET_VALUE);
	pm8001_cw32(pm8001_ha, 2, GSM_CONFIG_RESET, regVal);
	pm8001_dbg(pm8001_ha, INIT, "GSM (0x00004088 ==> 0x00007b88) - GSM Configuration and Reset is set to = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET));

	/* step 12: Restore GSM - Read Address Parity Check */
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK);
	/* just क्रम debugging */
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x700038 - Read Address Parity Check Enable = 0x%x\n",
		   regVal);
	pm8001_cw32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK, regVal1);
	pm8001_dbg(pm8001_ha, INIT, "GSM 0x700038 - Read Address Parity Check Enable is set to = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK));
	/* Restore GSM - Write Address Parity Check */
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK);
	pm8001_cw32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK, regVal2);
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x700040 - Write Address Parity Check Enable is set to = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK));
	/* Restore GSM - Write Data Parity Check */
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK);
	pm8001_cw32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK, regVal3);
	pm8001_dbg(pm8001_ha, INIT,
		   "GSM 0x700048 - Write Data Parity Check Enable is set to = 0x%x\n",
		   pm8001_cr32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK));

	/* step 13: bring the IOP and AAP1 out of reset */
	/* map 0x00000 to BAR4(0x20), BAR2(win) */
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, SPC_TOP_LEVEL_ADDR_BASE)) अणु
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "Shift Bar4 to 0x%x failed\n",
			   SPC_TOP_LEVEL_ADDR_BASE);
		वापस -1;
	पूर्ण
	regVal = pm8001_cr32(pm8001_ha, 2, SPC_REG_RESET);
	regVal |= (SPC_REG_RESET_PCS_IOP_SS | SPC_REG_RESET_PCS_AAP1_SS);
	pm8001_cw32(pm8001_ha, 2, SPC_REG_RESET, regVal);

	/* step 14: delay 10 usec - Normal Mode */
	udelay(10);
	/* check Soft Reset Normal mode or Soft Reset HDA mode */
	अगर (signature == SPC_SOFT_RESET_SIGNATURE) अणु
		/* step 15 (Normal Mode): रुको until scratch pad1 रेजिस्टर
		bit 2 toggled */
		max_रुको_count = 2 * 1000 * 1000;/* 2 sec */
		करो अणु
			udelay(1);
			regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1) &
				SCRATCH_PAD1_RST;
		पूर्ण जबतक ((regVal != toggleVal) && (--max_रुको_count));

		अगर (!max_रुको_count) अणु
			regVal = pm8001_cr32(pm8001_ha, 0,
				MSGU_SCRATCH_PAD_1);
			pm8001_dbg(pm8001_ha, FAIL, "TIMEOUT : ToggleVal 0x%x,MSGU_SCRATCH_PAD1 = 0x%x\n",
				   toggleVal, regVal);
			pm8001_dbg(pm8001_ha, FAIL,
				   "SCRATCH_PAD0 value = 0x%x\n",
				   pm8001_cr32(pm8001_ha, 0,
					       MSGU_SCRATCH_PAD_0));
			pm8001_dbg(pm8001_ha, FAIL,
				   "SCRATCH_PAD2 value = 0x%x\n",
				   pm8001_cr32(pm8001_ha, 0,
					       MSGU_SCRATCH_PAD_2));
			pm8001_dbg(pm8001_ha, FAIL,
				   "SCRATCH_PAD3 value = 0x%x\n",
				   pm8001_cr32(pm8001_ha, 0,
					       MSGU_SCRATCH_PAD_3));
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			वापस -1;
		पूर्ण

		/* step 16 (Normal) - Clear ODMR and ODCR */
		pm8001_cw32(pm8001_ha, 0, MSGU_ODCR, ODCR_CLEAR_ALL);
		pm8001_cw32(pm8001_ha, 0, MSGU_ODMR, ODMR_CLEAR_ALL);

		/* step 17 (Normal Mode): रुको क्रम the FW and IOP to get
		पढ़ोy - 1 sec समयout */
		/* Wait क्रम the SPC Configuration Table to be पढ़ोy */
		अगर (check_fw_पढ़ोy(pm8001_ha) == -1) अणु
			regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
			/* वापस error अगर MPI Configuration Table not पढ़ोy */
			pm8001_dbg(pm8001_ha, INIT,
				   "FW not ready SCRATCH_PAD1 = 0x%x\n",
				   regVal);
			regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2);
			/* वापस error अगर MPI Configuration Table not पढ़ोy */
			pm8001_dbg(pm8001_ha, INIT,
				   "FW not ready SCRATCH_PAD2 = 0x%x\n",
				   regVal);
			pm8001_dbg(pm8001_ha, INIT,
				   "SCRATCH_PAD0 value = 0x%x\n",
				   pm8001_cr32(pm8001_ha, 0,
					       MSGU_SCRATCH_PAD_0));
			pm8001_dbg(pm8001_ha, INIT,
				   "SCRATCH_PAD3 value = 0x%x\n",
				   pm8001_cr32(pm8001_ha, 0,
					       MSGU_SCRATCH_PAD_3));
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			वापस -1;
		पूर्ण
	पूर्ण
	pm8001_bar4_shअगरt(pm8001_ha, 0);
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);

	pm8001_dbg(pm8001_ha, INIT, "SPC soft reset Complete\n");
	वापस 0;
पूर्ण

अटल व्योम pm8001_hw_chip_rst(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 i;
	u32 regVal;
	pm8001_dbg(pm8001_ha, INIT, "chip reset start\n");

	/* करो SPC chip reset. */
	regVal = pm8001_cr32(pm8001_ha, 1, SPC_REG_RESET);
	regVal &= ~(SPC_REG_RESET_DEVICE);
	pm8001_cw32(pm8001_ha, 1, SPC_REG_RESET, regVal);

	/* delay 10 usec */
	udelay(10);

	/* bring chip reset out of reset */
	regVal = pm8001_cr32(pm8001_ha, 1, SPC_REG_RESET);
	regVal |= SPC_REG_RESET_DEVICE;
	pm8001_cw32(pm8001_ha, 1, SPC_REG_RESET, regVal);

	/* delay 10 usec */
	udelay(10);

	/* रुको क्रम 20 msec until the firmware माला_लो reloaded */
	i = 20;
	करो अणु
		mdelay(1);
	पूर्ण जबतक ((--i) != 0);

	pm8001_dbg(pm8001_ha, INIT, "chip reset finished\n");
पूर्ण

/**
 * pm8001_chip_iounmap - which maped when initialized.
 * @pm8001_ha: our hba card inक्रमmation
 */
व्योम pm8001_chip_iounmap(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	s8 bar, logical = 0;
	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
		/*
		** logical BARs क्रम SPC:
		** bar 0 and 1 - logical BAR0
		** bar 2 and 3 - logical BAR1
		** bar4 - logical BAR2
		** bar5 - logical BAR3
		** Skip the appropriate assignments:
		*/
		अगर ((bar == 1) || (bar == 3))
			जारी;
		अगर (pm8001_ha->io_mem[logical].memvirtaddr) अणु
			iounmap(pm8001_ha->io_mem[logical].memvirtaddr);
			logical++;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_अघोषित PM8001_USE_MSIX
/**
 * pm8001_chip_पूर्णांकx_पूर्णांकerrupt_enable - enable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम
pm8001_chip_पूर्णांकx_पूर्णांकerrupt_enable(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	pm8001_cw32(pm8001_ha, 0, MSGU_ODMR, ODMR_CLEAR_ALL);
	pm8001_cw32(pm8001_ha, 0, MSGU_ODCR, ODCR_CLEAR_ALL);
पूर्ण

 /**
  * pm8001_chip_पूर्णांकx_पूर्णांकerrupt_disable- disable PM8001 chip पूर्णांकerrupt
  * @pm8001_ha: our hba card inक्रमmation
  */
अटल व्योम
pm8001_chip_पूर्णांकx_पूर्णांकerrupt_disable(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	pm8001_cw32(pm8001_ha, 0, MSGU_ODMR, ODMR_MASK_ALL);
पूर्ण

#अन्यथा

/**
 * pm8001_chip_msix_पूर्णांकerrupt_enable - enable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 * @पूर्णांक_vec_idx: पूर्णांकerrupt number to enable
 */
अटल व्योम
pm8001_chip_msix_पूर्णांकerrupt_enable(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 पूर्णांक_vec_idx)
अणु
	u32 msi_index;
	u32 value;
	msi_index = पूर्णांक_vec_idx * MSIX_TABLE_ELEMENT_SIZE;
	msi_index += MSIX_TABLE_BASE;
	pm8001_cw32(pm8001_ha, 0, msi_index, MSIX_INTERRUPT_ENABLE);
	value = (1 << पूर्णांक_vec_idx);
	pm8001_cw32(pm8001_ha, 0,  MSGU_ODCR, value);

पूर्ण

/**
 * pm8001_chip_msix_पूर्णांकerrupt_disable - disable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 * @पूर्णांक_vec_idx: पूर्णांकerrupt number to disable
 */
अटल व्योम
pm8001_chip_msix_पूर्णांकerrupt_disable(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 पूर्णांक_vec_idx)
अणु
	u32 msi_index;
	msi_index = पूर्णांक_vec_idx * MSIX_TABLE_ELEMENT_SIZE;
	msi_index += MSIX_TABLE_BASE;
	pm8001_cw32(pm8001_ha, 0,  msi_index, MSIX_INTERRUPT_DISABLE);
पूर्ण
#पूर्ण_अगर

/**
 * pm8001_chip_पूर्णांकerrupt_enable - enable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 * @vec: unused
 */
अटल व्योम
pm8001_chip_पूर्णांकerrupt_enable(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec)
अणु
#अगर_घोषित PM8001_USE_MSIX
	pm8001_chip_msix_पूर्णांकerrupt_enable(pm8001_ha, 0);
#अन्यथा
	pm8001_chip_पूर्णांकx_पूर्णांकerrupt_enable(pm8001_ha);
#पूर्ण_अगर
पूर्ण

/**
 * pm8001_chip_पूर्णांकerrupt_disable - disable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 * @vec: unused
 */
अटल व्योम
pm8001_chip_पूर्णांकerrupt_disable(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec)
अणु
#अगर_घोषित PM8001_USE_MSIX
	pm8001_chip_msix_पूर्णांकerrupt_disable(pm8001_ha, 0);
#अन्यथा
	pm8001_chip_पूर्णांकx_पूर्णांकerrupt_disable(pm8001_ha);
#पूर्ण_अगर
पूर्ण

/**
 * pm8001_mpi_msg_मुक्त_get - get the मुक्त message buffer क्रम transfer
 * inbound queue.
 * @circularQ: the inbound queue  we want to transfer to HBA.
 * @messageSize: the message size of this transfer, normally it is 64 bytes
 * @messagePtr: the poपूर्णांकer to message.
 */
पूर्णांक pm8001_mpi_msg_मुक्त_get(काष्ठा inbound_queue_table *circularQ,
			    u16 messageSize, व्योम **messagePtr)
अणु
	u32 offset, consumer_index;
	काष्ठा mpi_msg_hdr *msgHeader;
	u8 bcCount = 1; /* only support single buffer */

	/* Checks is the requested message size can be allocated in this queue*/
	अगर (messageSize > IOMB_SIZE_SPCV) अणु
		*messagePtr = शून्य;
		वापस -1;
	पूर्ण

	/* Stores the new consumer index */
	consumer_index = pm8001_पढ़ो_32(circularQ->ci_virt);
	circularQ->consumer_index = cpu_to_le32(consumer_index);
	अगर (((circularQ->producer_idx + bcCount) % PM8001_MPI_QUEUE) ==
		le32_to_cpu(circularQ->consumer_index)) अणु
		*messagePtr = शून्य;
		वापस -1;
	पूर्ण
	/* get memory IOMB buffer address */
	offset = circularQ->producer_idx * messageSize;
	/* increment to next bcCount element */
	circularQ->producer_idx = (circularQ->producer_idx + bcCount)
				% PM8001_MPI_QUEUE;
	/* Adds that distance to the base of the region भव address plus
	the message header size*/
	msgHeader = (काष्ठा mpi_msg_hdr *)(circularQ->base_virt	+ offset);
	*messagePtr = ((व्योम *)msgHeader) + माप(काष्ठा mpi_msg_hdr);
	वापस 0;
पूर्ण

/**
 * pm8001_mpi_build_cmd- build the message queue क्रम transfer, update the PI to
 * FW to tell the fw to get this message from IOMB.
 * @pm8001_ha: our hba card inक्रमmation
 * @circularQ: the inbound queue we want to transfer to HBA.
 * @opCode: the operation code represents commands which LLDD and fw recognized.
 * @payload: the command payload of each operation command.
 * @nb: size in bytes of the command payload
 * @responseQueue: queue to पूर्णांकerrupt on w/ command response (अगर any)
 */
पूर्णांक pm8001_mpi_build_cmd(काष्ठा pm8001_hba_info *pm8001_ha,
			 काष्ठा inbound_queue_table *circularQ,
			 u32 opCode, व्योम *payload, माप_प्रकार nb,
			 u32 responseQueue)
अणु
	u32 Header = 0, hpriority = 0, bc = 1, category = 0x02;
	व्योम *pMessage;
	अचिन्हित दीर्घ flags;
	पूर्णांक q_index = circularQ - pm8001_ha->inbnd_q_tbl;
	पूर्णांक rv = -1;

	WARN_ON(q_index >= PM8001_MAX_INB_NUM);
	spin_lock_irqsave(&circularQ->iq_lock, flags);
	rv = pm8001_mpi_msg_मुक्त_get(circularQ, pm8001_ha->iomb_size,
			&pMessage);
	अगर (rv < 0) अणु
		pm8001_dbg(pm8001_ha, IO, "No free mpi buffer\n");
		rv = -ENOMEM;
		जाओ करोne;
	पूर्ण

	अगर (nb > (pm8001_ha->iomb_size - माप(काष्ठा mpi_msg_hdr)))
		nb = pm8001_ha->iomb_size - माप(काष्ठा mpi_msg_hdr);
	स_नकल(pMessage, payload, nb);
	अगर (nb + माप(काष्ठा mpi_msg_hdr) < pm8001_ha->iomb_size)
		स_रखो(pMessage + nb, 0, pm8001_ha->iomb_size -
				(nb + माप(काष्ठा mpi_msg_hdr)));

	/*Build the header*/
	Header = ((1 << 31) | (hpriority << 30) | ((bc & 0x1f) << 24)
		| ((responseQueue & 0x3F) << 16)
		| ((category & 0xF) << 12) | (opCode & 0xFFF));

	pm8001_ग_लिखो_32((pMessage - 4), 0, cpu_to_le32(Header));
	/*Update the PI to the firmware*/
	pm8001_cw32(pm8001_ha, circularQ->pi_pci_bar,
		circularQ->pi_offset, circularQ->producer_idx);
	pm8001_dbg(pm8001_ha, DEVIO,
		   "INB Q %x OPCODE:%x , UPDATED PI=%d CI=%d\n",
		   responseQueue, opCode, circularQ->producer_idx,
		   circularQ->consumer_index);
करोne:
	spin_unlock_irqrestore(&circularQ->iq_lock, flags);
	वापस rv;
पूर्ण

u32 pm8001_mpi_msg_मुक्त_set(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *pMsg,
			    काष्ठा outbound_queue_table *circularQ, u8 bc)
अणु
	u32 producer_index;
	काष्ठा mpi_msg_hdr *msgHeader;
	काष्ठा mpi_msg_hdr *pOutBoundMsgHeader;

	msgHeader = (काष्ठा mpi_msg_hdr *)(pMsg - माप(काष्ठा mpi_msg_hdr));
	pOutBoundMsgHeader = (काष्ठा mpi_msg_hdr *)(circularQ->base_virt +
				circularQ->consumer_idx * pm8001_ha->iomb_size);
	अगर (pOutBoundMsgHeader != msgHeader) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			   "consumer_idx = %d msgHeader = %p\n",
			   circularQ->consumer_idx, msgHeader);

		/* Update the producer index from SPC */
		producer_index = pm8001_पढ़ो_32(circularQ->pi_virt);
		circularQ->producer_index = cpu_to_le32(producer_index);
		pm8001_dbg(pm8001_ha, FAIL,
			   "consumer_idx = %d producer_index = %dmsgHeader = %p\n",
			   circularQ->consumer_idx,
			   circularQ->producer_index, msgHeader);
		वापस 0;
	पूर्ण
	/* मुक्त the circular queue buffer elements associated with the message*/
	circularQ->consumer_idx = (circularQ->consumer_idx + bc)
				% PM8001_MPI_QUEUE;
	/* update the CI of outbound queue */
	pm8001_cw32(pm8001_ha, circularQ->ci_pci_bar, circularQ->ci_offset,
		circularQ->consumer_idx);
	/* Update the producer index from SPC*/
	producer_index = pm8001_पढ़ो_32(circularQ->pi_virt);
	circularQ->producer_index = cpu_to_le32(producer_index);
	pm8001_dbg(pm8001_ha, IO, " CI=%d PI=%d\n",
		   circularQ->consumer_idx, circularQ->producer_index);
	वापस 0;
पूर्ण

/**
 * pm8001_mpi_msg_consume- get the MPI message from outbound queue
 * message table.
 * @pm8001_ha: our hba card inक्रमmation
 * @circularQ: the outbound queue  table.
 * @messagePtr1: the message contents of this outbound message.
 * @pBC: the message size.
 */
u32 pm8001_mpi_msg_consume(काष्ठा pm8001_hba_info *pm8001_ha,
			   काष्ठा outbound_queue_table *circularQ,
			   व्योम **messagePtr1, u8 *pBC)
अणु
	काष्ठा mpi_msg_hdr	*msgHeader;
	__le32	msgHeader_पंचांगp;
	u32 header_पंचांगp;
	करो अणु
		/* If there are not-yet-delivered messages ... */
		अगर (le32_to_cpu(circularQ->producer_index)
			!= circularQ->consumer_idx) अणु
			/*Get the poपूर्णांकer to the circular queue buffer element*/
			msgHeader = (काष्ठा mpi_msg_hdr *)
				(circularQ->base_virt +
				circularQ->consumer_idx * pm8001_ha->iomb_size);
			/* पढ़ो header */
			header_पंचांगp = pm8001_पढ़ो_32(msgHeader);
			msgHeader_पंचांगp = cpu_to_le32(header_पंचांगp);
			pm8001_dbg(pm8001_ha, DEVIO,
				   "outbound opcode msgheader:%x ci=%d pi=%d\n",
				   msgHeader_पंचांगp, circularQ->consumer_idx,
				   circularQ->producer_index);
			अगर (0 != (le32_to_cpu(msgHeader_पंचांगp) & 0x80000000)) अणु
				अगर (OPC_OUB_SKIP_ENTRY !=
					(le32_to_cpu(msgHeader_पंचांगp) & 0xfff)) अणु
					*messagePtr1 =
						((u8 *)msgHeader) +
						माप(काष्ठा mpi_msg_hdr);
					*pBC = (u8)((le32_to_cpu(msgHeader_पंचांगp)
						>> 24) & 0x1f);
					pm8001_dbg(pm8001_ha, IO,
						   ": CI=%d PI=%d msgHeader=%x\n",
						   circularQ->consumer_idx,
						   circularQ->producer_index,
						   msgHeader_पंचांगp);
					वापस MPI_IO_STATUS_SUCCESS;
				पूर्ण अन्यथा अणु
					circularQ->consumer_idx =
						(circularQ->consumer_idx +
						((le32_to_cpu(msgHeader_पंचांगp)
						 >> 24) & 0x1f))
							% PM8001_MPI_QUEUE;
					msgHeader_पंचांगp = 0;
					pm8001_ग_लिखो_32(msgHeader, 0, 0);
					/* update the CI of outbound queue */
					pm8001_cw32(pm8001_ha,
						circularQ->ci_pci_bar,
						circularQ->ci_offset,
						circularQ->consumer_idx);
				पूर्ण
			पूर्ण अन्यथा अणु
				circularQ->consumer_idx =
					(circularQ->consumer_idx +
					((le32_to_cpu(msgHeader_पंचांगp) >> 24) &
					0x1f)) % PM8001_MPI_QUEUE;
				msgHeader_पंचांगp = 0;
				pm8001_ग_लिखो_32(msgHeader, 0, 0);
				/* update the CI of outbound queue */
				pm8001_cw32(pm8001_ha, circularQ->ci_pci_bar,
					circularQ->ci_offset,
					circularQ->consumer_idx);
				वापस MPI_IO_STATUS_FAIL;
			पूर्ण
		पूर्ण अन्यथा अणु
			u32 producer_index;
			व्योम *pi_virt = circularQ->pi_virt;
			/* spurious पूर्णांकerrupt during setup अगर
			 * kexec-ing and driver करोing a करोorbell access
			 * with the pre-kexec oq पूर्णांकerrupt setup
			 */
			अगर (!pi_virt)
				अवरोध;
			/* Update the producer index from SPC */
			producer_index = pm8001_पढ़ो_32(pi_virt);
			circularQ->producer_index = cpu_to_le32(producer_index);
		पूर्ण
	पूर्ण जबतक (le32_to_cpu(circularQ->producer_index) !=
		circularQ->consumer_idx);
	/* जबतक we करोn't have any more not-yet-delivered message */
	/* report empty */
	वापस MPI_IO_STATUS_BUSY;
पूर्ण

व्योम pm8001_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pm8001_work *pw = container_of(work, काष्ठा pm8001_work, work);
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा करोमुख्य_device *dev;

	/*
	 * So far, all users of this stash an associated काष्ठाure here.
	 * If we get here, and this poपूर्णांकer is null, then the action
	 * was cancelled. This nullअगरication happens when the device
	 * goes away.
	 */
	अगर (pw->handler != IO_FATAL_ERROR) अणु
		pm8001_dev = pw->data; /* Most stash device काष्ठाure */
		अगर ((pm8001_dev == शून्य)
		 || ((pw->handler != IO_XFER_ERROR_BREAK)
			 && (pm8001_dev->dev_type == SAS_PHY_UNUSED))) अणु
			kमुक्त(pw);
			वापस;
		पूर्ण
	पूर्ण

	चयन (pw->handler) अणु
	हाल IO_XFER_ERROR_BREAK:
	अणु	/* This one stashes the sas_task instead */
		काष्ठा sas_task *t = (काष्ठा sas_task *)pm8001_dev;
		u32 tag;
		काष्ठा pm8001_ccb_info *ccb;
		काष्ठा pm8001_hba_info *pm8001_ha = pw->pm8001_ha;
		अचिन्हित दीर्घ flags, flags1;
		काष्ठा task_status_काष्ठा *ts;
		पूर्णांक i;

		अगर (pm8001_query_task(t) == TMF_RESP_FUNC_SUCC)
			अवरोध; /* Task still on lu */
		spin_lock_irqsave(&pm8001_ha->lock, flags);

		spin_lock_irqsave(&t->task_state_lock, flags1);
		अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_DONE))) अणु
			spin_unlock_irqrestore(&t->task_state_lock, flags1);
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			अवरोध; /* Task got completed by another */
		पूर्ण
		spin_unlock_irqrestore(&t->task_state_lock, flags1);

		/* Search क्रम a possible ccb that matches the task */
		क्रम (i = 0; ccb = शून्य, i < PM8001_MAX_CCB; i++) अणु
			ccb = &pm8001_ha->ccb_info[i];
			tag = ccb->ccb_tag;
			अगर ((tag != 0xFFFFFFFF) && (ccb->task == t))
				अवरोध;
		पूर्ण
		अगर (!ccb) अणु
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			अवरोध; /* Task got मुक्तd by another */
		पूर्ण
		ts = &t->task_status;
		ts->resp = SAS_TASK_COMPLETE;
		/* Force the midlayer to retry */
		ts->stat = SAS_QUEUE_FULL;
		pm8001_dev = ccb->device;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		spin_lock_irqsave(&t->task_state_lock, flags1);
		t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
		t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
		t->task_state_flags |= SAS_TASK_STATE_DONE;
		अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
			spin_unlock_irqrestore(&t->task_state_lock, flags1);
			pm8001_dbg(pm8001_ha, FAIL, "task 0x%p done with event 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
				   t, pw->handler, ts->resp, ts->stat);
			pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&t->task_state_lock, flags1);
			pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
			mb();/* in order to क्रमce CPU ordering */
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			t->task_करोne(t);
		पूर्ण
	पूर्ण	अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
	अणु	/* This one stashes the sas_task instead */
		काष्ठा sas_task *t = (काष्ठा sas_task *)pm8001_dev;
		u32 tag;
		काष्ठा pm8001_ccb_info *ccb;
		काष्ठा pm8001_hba_info *pm8001_ha = pw->pm8001_ha;
		अचिन्हित दीर्घ flags, flags1;
		पूर्णांक i, ret = 0;

		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");

		ret = pm8001_query_task(t);

		अगर (ret == TMF_RESP_FUNC_SUCC)
			pm8001_dbg(pm8001_ha, IO, "...Task on lu\n");
		अन्यथा अगर (ret == TMF_RESP_FUNC_COMPLETE)
			pm8001_dbg(pm8001_ha, IO, "...Task NOT on lu\n");
		अन्यथा
			pm8001_dbg(pm8001_ha, DEVIO, "...query task failed!!!\n");

		spin_lock_irqsave(&pm8001_ha->lock, flags);

		spin_lock_irqsave(&t->task_state_lock, flags1);

		अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_DONE))) अणु
			spin_unlock_irqrestore(&t->task_state_lock, flags1);
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			अगर (ret == TMF_RESP_FUNC_SUCC) /* task on lu */
				(व्योम)pm8001_पात_task(t);
			अवरोध; /* Task got completed by another */
		पूर्ण

		spin_unlock_irqrestore(&t->task_state_lock, flags1);

		/* Search क्रम a possible ccb that matches the task */
		क्रम (i = 0; ccb = शून्य, i < PM8001_MAX_CCB; i++) अणु
			ccb = &pm8001_ha->ccb_info[i];
			tag = ccb->ccb_tag;
			अगर ((tag != 0xFFFFFFFF) && (ccb->task == t))
				अवरोध;
		पूर्ण
		अगर (!ccb) अणु
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			अगर (ret == TMF_RESP_FUNC_SUCC) /* task on lu */
				(व्योम)pm8001_पात_task(t);
			अवरोध; /* Task got मुक्तd by another */
		पूर्ण

		pm8001_dev = ccb->device;
		dev = pm8001_dev->sas_device;

		चयन (ret) अणु
		हाल TMF_RESP_FUNC_SUCC: /* task on lu */
			ccb->खोलो_retry = 1; /* Snub completion */
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			ret = pm8001_पात_task(t);
			ccb->खोलो_retry = 0;
			चयन (ret) अणु
			हाल TMF_RESP_FUNC_SUCC:
			हाल TMF_RESP_FUNC_COMPLETE:
				अवरोध;
			शेष: /* device misbehavior */
				ret = TMF_RESP_FUNC_FAILED;
				pm8001_dbg(pm8001_ha, IO, "...Reset phy\n");
				pm8001_I_T_nexus_reset(dev);
				अवरोध;
			पूर्ण
			अवरोध;

		हाल TMF_RESP_FUNC_COMPLETE: /* task not on lu */
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			/* Do we need to पात the task locally? */
			अवरोध;

		शेष: /* device misbehavior */
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			ret = TMF_RESP_FUNC_FAILED;
			pm8001_dbg(pm8001_ha, IO, "...Reset phy\n");
			pm8001_I_T_nexus_reset(dev);
		पूर्ण

		अगर (ret == TMF_RESP_FUNC_FAILED)
			t = शून्य;
		pm8001_खोलो_reject_retry(pm8001_ha, t, pm8001_dev);
		pm8001_dbg(pm8001_ha, IO, "...Complete\n");
	पूर्ण	अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
		dev = pm8001_dev->sas_device;
		pm8001_I_T_nexus_event_handler(dev);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY:
		dev = pm8001_dev->sas_device;
		pm8001_I_T_nexus_reset(dev);
		अवरोध;
	हाल IO_DS_IN_ERROR:
		dev = pm8001_dev->sas_device;
		pm8001_I_T_nexus_reset(dev);
		अवरोध;
	हाल IO_DS_NON_OPERATIONAL:
		dev = pm8001_dev->sas_device;
		pm8001_I_T_nexus_reset(dev);
		अवरोध;
	हाल IO_FATAL_ERROR:
	अणु
		काष्ठा pm8001_hba_info *pm8001_ha = pw->pm8001_ha;
		काष्ठा pm8001_ccb_info *ccb;
		काष्ठा task_status_काष्ठा *ts;
		काष्ठा sas_task *task;
		पूर्णांक i;
		u32 tag, device_id;

		क्रम (i = 0; ccb = शून्य, i < PM8001_MAX_CCB; i++) अणु
			ccb = &pm8001_ha->ccb_info[i];
			task = ccb->task;
			ts = &task->task_status;
			tag = ccb->ccb_tag;
			/* check अगर tag is शून्य */
			अगर (!tag) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					"tag Null\n");
				जारी;
			पूर्ण
			अगर (task != शून्य) अणु
				dev = task->dev;
				अगर (!dev) अणु
					pm8001_dbg(pm8001_ha, FAIL,
						"dev is NULL\n");
					जारी;
				पूर्ण
				/*complete sas task and update to top layer */
				pm8001_ccb_task_मुक्त(pm8001_ha, task, ccb, tag);
				ts->resp = SAS_TASK_COMPLETE;
				task->task_करोne(task);
			पूर्ण अन्यथा अगर (tag != 0xFFFFFFFF) अणु
				/* complete the पूर्णांकernal commands/non-sas task */
				pm8001_dev = ccb->device;
				अगर (pm8001_dev->dcompletion) अणु
					complete(pm8001_dev->dcompletion);
					pm8001_dev->dcompletion = शून्य;
				पूर्ण
				complete(pm8001_ha->nvmd_completion);
				pm8001_tag_मुक्त(pm8001_ha, tag);
			पूर्ण
		पूर्ण
		/* Deरेजिस्टर all the device ids  */
		क्रम (i = 0; i < PM8001_MAX_DEVICES; i++) अणु
			pm8001_dev = &pm8001_ha->devices[i];
			device_id = pm8001_dev->device_id;
			अगर (device_id) अणु
				PM8001_CHIP_DISP->dereg_dev_req(pm8001_ha, device_id);
				pm8001_मुक्त_dev(pm8001_dev);
			पूर्ण
		पूर्ण
	पूर्ण	अवरोध;
	पूर्ण
	kमुक्त(pw);
पूर्ण

पूर्णांक pm8001_handle_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *data,
			       पूर्णांक handler)
अणु
	काष्ठा pm8001_work *pw;
	पूर्णांक ret = 0;

	pw = kदो_स्मृति(माप(काष्ठा pm8001_work), GFP_ATOMIC);
	अगर (pw) अणु
		pw->pm8001_ha = pm8001_ha;
		pw->data = data;
		pw->handler = handler;
		INIT_WORK(&pw->work, pm8001_work_fn);
		queue_work(pm8001_wq, &pw->work);
	पूर्ण अन्यथा
		ret = -ENOMEM;

	वापस ret;
पूर्ण

अटल व्योम pm8001_send_पात_all(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_device *pm8001_ha_dev)
अणु
	पूर्णांक res;
	u32 ccb_tag;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा sas_task *task = शून्य;
	काष्ठा task_पात_req task_पात;
	काष्ठा inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SATA_ABORT;
	पूर्णांक ret;

	अगर (!pm8001_ha_dev) अणु
		pm8001_dbg(pm8001_ha, FAIL, "dev is null\n");
		वापस;
	पूर्ण

	task = sas_alloc_slow_task(GFP_ATOMIC);

	अगर (!task) अणु
		pm8001_dbg(pm8001_ha, FAIL, "cannot allocate task\n");
		वापस;
	पूर्ण

	task->task_करोne = pm8001_task_करोne;

	res = pm8001_tag_alloc(pm8001_ha, &ccb_tag);
	अगर (res)
		वापस;

	ccb = &pm8001_ha->ccb_info[ccb_tag];
	ccb->device = pm8001_ha_dev;
	ccb->ccb_tag = ccb_tag;
	ccb->task = task;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	स_रखो(&task_पात, 0, माप(task_पात));
	task_पात.पात_all = cpu_to_le32(1);
	task_पात.device_id = cpu_to_le32(pm8001_ha_dev->device_id);
	task_पात.tag = cpu_to_le32(ccb_tag);

	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &task_पात,
			माप(task_पात), 0);
	अगर (ret)
		pm8001_tag_मुक्त(pm8001_ha, ccb_tag);

पूर्ण

अटल व्योम pm8001_send_पढ़ो_log(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_device *pm8001_ha_dev)
अणु
	काष्ठा sata_start_req sata_cmd;
	पूर्णांक res;
	u32 ccb_tag;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा sas_task *task = शून्य;
	काष्ठा host_to_dev_fis fis;
	काष्ठा करोमुख्य_device *dev;
	काष्ठा inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SATA_HOST_OPSTART;

	task = sas_alloc_slow_task(GFP_ATOMIC);

	अगर (!task) अणु
		pm8001_dbg(pm8001_ha, FAIL, "cannot allocate task !!!\n");
		वापस;
	पूर्ण
	task->task_करोne = pm8001_task_करोne;

	res = pm8001_tag_alloc(pm8001_ha, &ccb_tag);
	अगर (res) अणु
		sas_मुक्त_task(task);
		pm8001_dbg(pm8001_ha, FAIL, "cannot allocate tag !!!\n");
		वापस;
	पूर्ण

	/* allocate करोमुख्य device by ourselves as libsas
	 * is not going to provide any
	*/
	dev = kzalloc(माप(काष्ठा करोमुख्य_device), GFP_ATOMIC);
	अगर (!dev) अणु
		sas_मुक्त_task(task);
		pm8001_tag_मुक्त(pm8001_ha, ccb_tag);
		pm8001_dbg(pm8001_ha, FAIL,
			   "Domain device cannot be allocated\n");
		वापस;
	पूर्ण
	task->dev = dev;
	task->dev->lldd_dev = pm8001_ha_dev;

	ccb = &pm8001_ha->ccb_info[ccb_tag];
	ccb->device = pm8001_ha_dev;
	ccb->ccb_tag = ccb_tag;
	ccb->task = task;
	pm8001_ha_dev->id |= NCQ_READ_LOG_FLAG;
	pm8001_ha_dev->id |= NCQ_2ND_RLE_FLAG;

	स_रखो(&sata_cmd, 0, माप(sata_cmd));
	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	/* स्थिरruct पढ़ो log FIS */
	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));
	fis.fis_type = 0x27;
	fis.flags = 0x80;
	fis.command = ATA_CMD_READ_LOG_EXT;
	fis.lbal = 0x10;
	fis.sector_count = 0x1;

	sata_cmd.tag = cpu_to_le32(ccb_tag);
	sata_cmd.device_id = cpu_to_le32(pm8001_ha_dev->device_id);
	sata_cmd.ncqtag_atap_dir_m |= ((0x1 << 7) | (0x5 << 9));
	स_नकल(&sata_cmd.sata_fis, &fis, माप(काष्ठा host_to_dev_fis));

	res = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &sata_cmd,
			माप(sata_cmd), 0);
	अगर (res) अणु
		sas_मुक्त_task(task);
		pm8001_tag_मुक्त(pm8001_ha, ccb_tag);
		kमुक्त(dev);
	पूर्ण
पूर्ण

/**
 * mpi_ssp_completion- process the event that FW response to the SSP request.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: the message contents of this outbound message.
 *
 * When FW has completed a ssp request क्रम example a IO request, after it has
 * filled the SG data with the data, it will trigger this event represent
 * that he has finished the job,please check the coresponding buffer.
 * So we will tell the caller who maybe रुकोing the result to tell upper layer
 * that the task has been finished.
 */
अटल व्योम
mpi_ssp_completion(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	काष्ठा pm8001_ccb_info *ccb;
	अचिन्हित दीर्घ flags;
	u32 status;
	u32 param;
	u32 tag;
	काष्ठा ssp_completion_resp *psspPayload;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा ssp_response_iu *iu;
	काष्ठा pm8001_device *pm8001_dev;
	psspPayload = (काष्ठा ssp_completion_resp *)(piomb + 4);
	status = le32_to_cpu(psspPayload->status);
	tag = le32_to_cpu(psspPayload->tag);
	ccb = &pm8001_ha->ccb_info[tag];
	अगर ((status == IO_ABORTED) && ccb->खोलो_retry) अणु
		/* Being completed by another */
		ccb->खोलो_retry = 0;
		वापस;
	पूर्ण
	pm8001_dev = ccb->device;
	param = le32_to_cpu(psspPayload->param);

	t = ccb->task;

	अगर (status && status != IO_UNDERFLOW)
		pm8001_dbg(pm8001_ha, FAIL, "sas IO status 0x%x\n", status);
	अगर (unlikely(!t || !t->lldd_task || !t->dev))
		वापस;
	ts = &t->task_status;
	/* Prपूर्णांक sas address of IO failed device */
	अगर ((status != IO_SUCCESS) && (status != IO_OVERFLOW) &&
		(status != IO_UNDERFLOW))
		pm8001_dbg(pm8001_ha, FAIL, "SAS Address of IO Failure Drive:%016llx\n",
			   SAS_ADDR(t->dev->sas_addr));

	अगर (status)
		pm8001_dbg(pm8001_ha, IOERR,
			   "status:0x%x, tag:0x%x, task:0x%p\n",
			   status, tag, t);

	चयन (status) अणु
	हाल IO_SUCCESS:
		pm8001_dbg(pm8001_ha, IO, "IO_SUCCESS,param = %d\n",
			   param);
		अगर (param == 0) अणु
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAM_STAT_GOOD;
		पूर्ण अन्यथा अणु
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_PROTO_RESPONSE;
			ts->residual = param;
			iu = &psspPayload->ssp_resp_iu;
			sas_ssp_task_response(pm8001_ha->dev, t, iu);
		पूर्ण
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_ABORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_ABORTED IOMB Tag\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अवरोध;
	हाल IO_UNDERFLOW:
		/* SSP Completion with error */
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW,param = %d\n",
			   param);
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		ts->residual = param;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_NO_DEVICE:
		pm8001_dbg(pm8001_ha, IO, "IO_NO_DEVICE\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PHY_DOWN;
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		/* Force the midlayer to retry */
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अगर (!t->uldd_task)
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अवरोध;
	हाल IO_XFER_ERROR_NAK_RECEIVED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_NAK_RECEIVED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_XFER_ERROR_ACK_NAK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_ACK_NAK_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अवरोध;
	हाल IO_XFER_ERROR_DMA:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_DMA\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_XFER_ERROR_OFFSET_MISMATCH:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_OFFSET_MISMATCH\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अवरोध;
	हाल IO_PORT_IN_RESET:
		pm8001_dbg(pm8001_ha, IO, "IO_PORT_IN_RESET\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अवरोध;
	हाल IO_DS_NON_OPERATIONAL:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_NON_OPERATIONAL\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (!t->uldd_task)
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_DS_NON_OPERATIONAL);
		अवरोध;
	हाल IO_DS_IN_RECOVERY:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_IN_RECOVERY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अवरोध;
	हाल IO_TM_TAG_NOT_FOUND:
		pm8001_dbg(pm8001_ha, IO, "IO_TM_TAG_NOT_FOUND\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अवरोध;
	हाल IO_SSP_EXT_IU_ZERO_LEN_ERROR:
		pm8001_dbg(pm8001_ha, IO, "IO_SSP_EXT_IU_ZERO_LEN_ERROR\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown status 0x%x\n", status);
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अवरोध;
	पूर्ण
	pm8001_dbg(pm8001_ha, IO, "scsi_status = %x\n",
		   psspPayload->ssp_resp_iu.status);
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "task 0x%p done with io_status 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, status, ts->resp, ts->stat);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
		mb();/* in order to क्रमce CPU ordering */
		t->task_करोne(t);
	पूर्ण
पूर्ण

/*See the comments क्रम mpi_ssp_completion */
अटल व्योम mpi_ssp_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	अचिन्हित दीर्घ flags;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा ssp_event_resp *psspPayload =
		(काष्ठा ssp_event_resp *)(piomb + 4);
	u32 event = le32_to_cpu(psspPayload->event);
	u32 tag = le32_to_cpu(psspPayload->tag);
	u32 port_id = le32_to_cpu(psspPayload->port_id);
	u32 dev_id = le32_to_cpu(psspPayload->device_id);

	ccb = &pm8001_ha->ccb_info[tag];
	t = ccb->task;
	pm8001_dev = ccb->device;
	अगर (event)
		pm8001_dbg(pm8001_ha, FAIL, "sas IO status 0x%x\n", event);
	अगर (unlikely(!t || !t->lldd_task || !t->dev))
		वापस;
	ts = &t->task_status;
	pm8001_dbg(pm8001_ha, DEVIO, "port_id = %x,device_id = %x\n",
		   port_id, dev_id);
	चयन (event) अणु
	हाल IO_OVERFLOW:
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		pm8001_handle_event(pm8001_ha, t, IO_XFER_ERROR_BREAK);
		वापस;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अगर (!t->uldd_task)
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अवरोध;
	हाल IO_XFER_ERROR_NAK_RECEIVED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_NAK_RECEIVED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_XFER_ERROR_ACK_NAK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_ACK_NAK_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		pm8001_handle_event(pm8001_ha, t, IO_XFER_OPEN_RETRY_TIMEOUT);
		वापस;
	हाल IO_XFER_ERROR_UNEXPECTED_PHASE:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_UNEXPECTED_PHASE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_RDY_OVERRUN:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_XFER_RDY_OVERRUN\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_CMD_ISSUE_ACK_NAK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_CMD_ISSUE_ACK_NAK_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_OFFSET_MISMATCH:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_OFFSET_MISMATCH\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_ZERO_DATA_LEN:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_XFER_ZERO_DATA_LEN\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_CMD_FRAME_ISSUED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_CMD_FRAME_ISSUED\n");
		वापस;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown status 0x%x\n", event);
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "task 0x%p done with event 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, event, ts->resp, ts->stat);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
		mb();/* in order to क्रमce CPU ordering */
		t->task_करोne(t);
	पूर्ण
पूर्ण

/*See the comments क्रम mpi_ssp_completion */
अटल व्योम
mpi_sata_completion(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	काष्ठा pm8001_ccb_info *ccb;
	u32 param;
	u32 status;
	u32 tag;
	पूर्णांक i, j;
	u8 sata_addr_low[4];
	u32 temp_sata_addr_low;
	u8 sata_addr_hi[4];
	u32 temp_sata_addr_hi;
	काष्ठा sata_completion_resp *psataPayload;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा ata_task_resp *resp ;
	u32 *sata_resp;
	काष्ठा pm8001_device *pm8001_dev;
	अचिन्हित दीर्घ flags;

	psataPayload = (काष्ठा sata_completion_resp *)(piomb + 4);
	status = le32_to_cpu(psataPayload->status);
	tag = le32_to_cpu(psataPayload->tag);

	अगर (!tag) अणु
		pm8001_dbg(pm8001_ha, FAIL, "tag null\n");
		वापस;
	पूर्ण
	ccb = &pm8001_ha->ccb_info[tag];
	param = le32_to_cpu(psataPayload->param);
	अगर (ccb) अणु
		t = ccb->task;
		pm8001_dev = ccb->device;
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, FAIL, "ccb null\n");
		वापस;
	पूर्ण

	अगर (t) अणु
		अगर (t->dev && (t->dev->lldd_dev))
			pm8001_dev = t->dev->lldd_dev;
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, FAIL, "task null\n");
		वापस;
	पूर्ण

	अगर ((pm8001_dev && !(pm8001_dev->id & NCQ_READ_LOG_FLAG))
		&& unlikely(!t || !t->lldd_task || !t->dev)) अणु
		pm8001_dbg(pm8001_ha, FAIL, "task or dev null\n");
		वापस;
	पूर्ण

	ts = &t->task_status;
	अगर (!ts) अणु
		pm8001_dbg(pm8001_ha, FAIL, "ts null\n");
		वापस;
	पूर्ण

	अगर (status)
		pm8001_dbg(pm8001_ha, IOERR,
			   "status:0x%x, tag:0x%x, task::0x%p\n",
			   status, tag, t);

	/* Prपूर्णांक sas address of IO failed device */
	अगर ((status != IO_SUCCESS) && (status != IO_OVERFLOW) &&
		(status != IO_UNDERFLOW)) अणु
		अगर (!((t->dev->parent) &&
			(dev_is_expander(t->dev->parent->dev_type)))) अणु
			क्रम (i = 0, j = 4; j <= 7 && i <= 3; i++, j++)
				sata_addr_low[i] = pm8001_ha->sas_addr[j];
			क्रम (i = 0, j = 0; j <= 3 && i <= 3; i++, j++)
				sata_addr_hi[i] = pm8001_ha->sas_addr[j];
			स_नकल(&temp_sata_addr_low, sata_addr_low,
				माप(sata_addr_low));
			स_नकल(&temp_sata_addr_hi, sata_addr_hi,
				माप(sata_addr_hi));
			temp_sata_addr_hi = (((temp_sata_addr_hi >> 24) & 0xff)
						|((temp_sata_addr_hi << 8) &
						0xff0000) |
						((temp_sata_addr_hi >> 8)
						& 0xff00) |
						((temp_sata_addr_hi << 24) &
						0xff000000));
			temp_sata_addr_low = ((((temp_sata_addr_low >> 24)
						& 0xff) |
						((temp_sata_addr_low << 8)
						& 0xff0000) |
						((temp_sata_addr_low >> 8)
						& 0xff00) |
						((temp_sata_addr_low << 24)
						& 0xff000000)) +
						pm8001_dev->attached_phy +
						0x10);
			pm8001_dbg(pm8001_ha, FAIL,
				   "SAS Address of IO Failure Drive:%08x%08x\n",
				   temp_sata_addr_hi,
				   temp_sata_addr_low);
		पूर्ण अन्यथा अणु
			pm8001_dbg(pm8001_ha, FAIL,
				   "SAS Address of IO Failure Drive:%016llx\n",
				   SAS_ADDR(t->dev->sas_addr));
		पूर्ण
	पूर्ण
	चयन (status) अणु
	हाल IO_SUCCESS:
		pm8001_dbg(pm8001_ha, IO, "IO_SUCCESS\n");
		अगर (param == 0) अणु
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAM_STAT_GOOD;
			/* check अगर response is क्रम SEND READ LOG */
			अगर (pm8001_dev &&
				(pm8001_dev->id & NCQ_READ_LOG_FLAG)) अणु
				/* set new bit क्रम पात_all */
				pm8001_dev->id |= NCQ_ABORT_ALL_FLAG;
				/* clear bit क्रम पढ़ो log */
				pm8001_dev->id = pm8001_dev->id & 0x7FFFFFFF;
				pm8001_send_पात_all(pm8001_ha, pm8001_dev);
				/* Free the tag */
				pm8001_tag_मुक्त(pm8001_ha, tag);
				sas_मुक्त_task(t);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 len;
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_PROTO_RESPONSE;
			ts->residual = param;
			pm8001_dbg(pm8001_ha, IO,
				   "SAS_PROTO_RESPONSE len = %d\n",
				   param);
			sata_resp = &psataPayload->sata_resp[0];
			resp = (काष्ठा ata_task_resp *)ts->buf;
			अगर (t->ata_task.dma_xfer == 0 &&
			    t->data_dir == DMA_FROM_DEVICE) अणु
				len = माप(काष्ठा pio_setup_fis);
				pm8001_dbg(pm8001_ha, IO,
					   "PIO read len = %d\n", len);
			पूर्ण अन्यथा अगर (t->ata_task.use_ncq) अणु
				len = माप(काष्ठा set_dev_bits_fis);
				pm8001_dbg(pm8001_ha, IO, "FPDMA len = %d\n",
					   len);
			पूर्ण अन्यथा अणु
				len = माप(काष्ठा dev_to_host_fis);
				pm8001_dbg(pm8001_ha, IO, "other len = %d\n",
					   len);
			पूर्ण
			अगर (SAS_STATUS_BUF_SIZE >= माप(*resp)) अणु
				resp->frame_len = len;
				स_नकल(&resp->ending_fis[0], sata_resp, len);
				ts->buf_valid_size = माप(*resp);
			पूर्ण अन्यथा
				pm8001_dbg(pm8001_ha, IO,
					   "response too large\n");
		पूर्ण
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_ABORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_ABORTED IOMB Tag\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
		/* following हालs are to करो हालs */
	हाल IO_UNDERFLOW:
		/* SATA Completion with error */
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW param = %d\n", param);
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		ts->residual =  param;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_NO_DEVICE:
		pm8001_dbg(pm8001_ha, IO, "IO_NO_DEVICE\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PHY_DOWN;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_INTERRUPTED;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_CONT0;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_NAK_RECEIVED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_NAK_RECEIVED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_ACK_NAK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_ACK_NAK_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_DMA:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_DMA\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_SATA_LINK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_SATA_LINK_TIMEOUT\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_REJECTED_NCQ_MODE:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_REJECTED_NCQ_MODE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_PORT_IN_RESET:
		pm8001_dbg(pm8001_ha, IO, "IO_PORT_IN_RESET\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_DS_NON_OPERATIONAL:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_NON_OPERATIONAL\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha, pm8001_dev,
				    IO_DS_NON_OPERATIONAL);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_DS_IN_RECOVERY:
		pm8001_dbg(pm8001_ha, IO, "  IO_DS_IN_RECOVERY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_DS_IN_ERROR:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_IN_ERROR\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha, pm8001_dev,
				    IO_DS_IN_ERROR);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown status 0x%x\n", status);
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL,
			   "task 0x%p done with io_status 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, status, ts->resp, ts->stat);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
	पूर्ण
पूर्ण

/*See the comments क्रम mpi_ssp_completion */
अटल व्योम mpi_sata_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा sata_event_resp *psataPayload =
		(काष्ठा sata_event_resp *)(piomb + 4);
	u32 event = le32_to_cpu(psataPayload->event);
	u32 tag = le32_to_cpu(psataPayload->tag);
	u32 port_id = le32_to_cpu(psataPayload->port_id);
	u32 dev_id = le32_to_cpu(psataPayload->device_id);
	अचिन्हित दीर्घ flags;

	ccb = &pm8001_ha->ccb_info[tag];

	अगर (ccb) अणु
		t = ccb->task;
		pm8001_dev = ccb->device;
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, FAIL, "No CCB !!!. returning\n");
	पूर्ण
	अगर (event)
		pm8001_dbg(pm8001_ha, FAIL, "SATA EVENT 0x%x\n", event);

	/* Check अगर this is NCQ error */
	अगर (event == IO_XFER_ERROR_ABORTED_NCQ_MODE) अणु
		/* find device using device id */
		pm8001_dev = pm8001_find_dev(pm8001_ha, dev_id);
		/* send पढ़ो log extension */
		अगर (pm8001_dev)
			pm8001_send_पढ़ो_log(pm8001_ha, pm8001_dev);
		वापस;
	पूर्ण

	ccb = &pm8001_ha->ccb_info[tag];
	t = ccb->task;
	pm8001_dev = ccb->device;
	अगर (event)
		pm8001_dbg(pm8001_ha, FAIL, "sata IO status 0x%x\n", event);
	अगर (unlikely(!t || !t->lldd_task || !t->dev))
		वापस;
	ts = &t->task_status;
	pm8001_dbg(pm8001_ha, DEVIO,
		   "port_id:0x%x, device_id:0x%x, tag:0x%x, event:0x%x\n",
		   port_id, dev_id, tag, event);
	चयन (event) अणु
	हाल IO_OVERFLOW:
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_INTERRUPTED;
		अवरोध;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_CONT0;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अवरोध;
	हाल IO_XFER_ERROR_NAK_RECEIVED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_NAK_RECEIVED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अवरोध;
	हाल IO_XFER_ERROR_PEER_ABORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PEER_ABORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अवरोध;
	हाल IO_XFER_ERROR_REJECTED_NCQ_MODE:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_REJECTED_NCQ_MODE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_UNEXPECTED_PHASE:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_UNEXPECTED_PHASE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_RDY_OVERRUN:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_XFER_RDY_OVERRUN\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_OFFSET_MISMATCH:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_OFFSET_MISMATCH\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_ZERO_DATA_LEN:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_XFER_ZERO_DATA_LEN\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_CMD_FRAME_ISSUED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_CMD_FRAME_ISSUED\n");
		अवरोध;
	हाल IO_XFER_PIO_SETUP_ERROR:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_PIO_SETUP_ERROR\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown status 0x%x\n", event);
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL,
			   "task 0x%p done with io_status 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, event, ts->resp, ts->stat);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
	पूर्ण
पूर्ण

/*See the comments क्रम mpi_ssp_completion */
अटल व्योम
mpi_smp_completion(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	काष्ठा pm8001_ccb_info *ccb;
	अचिन्हित दीर्घ flags;
	u32 status;
	u32 tag;
	काष्ठा smp_completion_resp *psmpPayload;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा pm8001_device *pm8001_dev;

	psmpPayload = (काष्ठा smp_completion_resp *)(piomb + 4);
	status = le32_to_cpu(psmpPayload->status);
	tag = le32_to_cpu(psmpPayload->tag);

	ccb = &pm8001_ha->ccb_info[tag];
	t = ccb->task;
	ts = &t->task_status;
	pm8001_dev = ccb->device;
	अगर (status) अणु
		pm8001_dbg(pm8001_ha, FAIL, "smp IO status 0x%x\n", status);
		pm8001_dbg(pm8001_ha, IOERR,
			   "status:0x%x, tag:0x%x, task:0x%p\n",
			   status, tag, t);
	पूर्ण
	अगर (unlikely(!t || !t->lldd_task || !t->dev))
		वापस;

	चयन (status) अणु
	हाल IO_SUCCESS:
		pm8001_dbg(pm8001_ha, IO, "IO_SUCCESS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_GOOD;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_ABORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_ABORTED IOMB\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OVERFLOW:
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_NO_DEVICE:
		pm8001_dbg(pm8001_ha, IO, "IO_NO_DEVICE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_PHY_DOWN;
		अवरोध;
	हाल IO_ERROR_HW_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_ERROR_HW_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		अवरोध;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_CONT0;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अवरोध;
	हाल IO_XFER_ERROR_RX_FRAME:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_RX_FRAME\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_ERROR_INTERNAL_SMP_RESOURCE:
		pm8001_dbg(pm8001_ha, IO, "IO_ERROR_INTERNAL_SMP_RESOURCE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_QUEUE_FULL;
		अवरोध;
	हाल IO_PORT_IN_RESET:
		pm8001_dbg(pm8001_ha, IO, "IO_PORT_IN_RESET\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_DS_NON_OPERATIONAL:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_NON_OPERATIONAL\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अवरोध;
	हाल IO_DS_IN_RECOVERY:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_IN_RECOVERY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown status 0x%x\n", status);
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL, "task 0x%p done with io_status 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, status, ts->resp, ts->stat);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
		mb();/* in order to क्रमce CPU ordering */
		t->task_करोne(t);
	पूर्ण
पूर्ण

व्योम pm8001_mpi_set_dev_state_resp(काष्ठा pm8001_hba_info *pm8001_ha,
		व्योम *piomb)
अणु
	काष्ठा set_dev_state_resp *pPayload =
		(काष्ठा set_dev_state_resp *)(piomb + 4);
	u32 tag = le32_to_cpu(pPayload->tag);
	काष्ठा pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[tag];
	काष्ठा pm8001_device *pm8001_dev = ccb->device;
	u32 status = le32_to_cpu(pPayload->status);
	u32 device_id = le32_to_cpu(pPayload->device_id);
	u8 pds = le32_to_cpu(pPayload->pds_nds) & PDS_BITS;
	u8 nds = le32_to_cpu(pPayload->pds_nds) & NDS_BITS;
	pm8001_dbg(pm8001_ha, MSG, "Set device id = 0x%x state from 0x%x to 0x%x status = 0x%x!\n",
		   device_id, pds, nds, status);
	complete(pm8001_dev->setds_completion);
	ccb->task = शून्य;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_tag_मुक्त(pm8001_ha, tag);
पूर्ण

व्योम pm8001_mpi_set_nvmd_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा get_nvm_data_resp *pPayload =
		(काष्ठा get_nvm_data_resp *)(piomb + 4);
	u32 tag = le32_to_cpu(pPayload->tag);
	काष्ठा pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[tag];
	u32 dlen_status = le32_to_cpu(pPayload->dlen_status);
	complete(pm8001_ha->nvmd_completion);
	pm8001_dbg(pm8001_ha, MSG, "Set nvm data complete!\n");
	अगर ((dlen_status & NVMD_STAT) != 0) अणु
		pm8001_dbg(pm8001_ha, FAIL, "Set nvm data error %x\n",
				dlen_status);
	पूर्ण
	ccb->task = शून्य;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_tag_मुक्त(pm8001_ha, tag);
पूर्ण

व्योम
pm8001_mpi_get_nvmd_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा fw_control_ex    *fw_control_context;
	काष्ठा get_nvm_data_resp *pPayload =
		(काष्ठा get_nvm_data_resp *)(piomb + 4);
	u32 tag = le32_to_cpu(pPayload->tag);
	काष्ठा pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[tag];
	u32 dlen_status = le32_to_cpu(pPayload->dlen_status);
	u32 ir_tds_bn_dps_das_nvm =
		le32_to_cpu(pPayload->ir_tda_bn_dps_das_nvm);
	व्योम *virt_addr = pm8001_ha->memoryMap.region[NVMD].virt_ptr;
	fw_control_context = ccb->fw_control_context;

	pm8001_dbg(pm8001_ha, MSG, "Get nvm data complete!\n");
	अगर ((dlen_status & NVMD_STAT) != 0) अणु
		pm8001_dbg(pm8001_ha, FAIL, "Get nvm data error %x\n",
				dlen_status);
		complete(pm8001_ha->nvmd_completion);
		/* We should मुक्त tag during failure also, the tag is not being
		 * मुक्तd by requesting path anywhere.
		 */
		ccb->task = शून्य;
		ccb->ccb_tag = 0xFFFFFFFF;
		pm8001_tag_मुक्त(pm8001_ha, tag);
		वापस;
	पूर्ण
	अगर (ir_tds_bn_dps_das_nvm & IPMode) अणु
		/* indirect mode - IR bit set */
		pm8001_dbg(pm8001_ha, MSG, "Get NVMD success, IR=1\n");
		अगर ((ir_tds_bn_dps_das_nvm & NVMD_TYPE) == TWI_DEVICE) अणु
			अगर (ir_tds_bn_dps_das_nvm == 0x80a80200) अणु
				स_नकल(pm8001_ha->sas_addr,
				      ((u8 *)virt_addr + 4),
				       SAS_ADDR_SIZE);
				pm8001_dbg(pm8001_ha, MSG, "Get SAS address from VPD successfully!\n");
			पूर्ण
		पूर्ण अन्यथा अगर (((ir_tds_bn_dps_das_nvm & NVMD_TYPE) == C_SEEPROM)
			|| ((ir_tds_bn_dps_das_nvm & NVMD_TYPE) == VPD_FLASH) ||
			((ir_tds_bn_dps_das_nvm & NVMD_TYPE) == EXPAN_ROM)) अणु
				;
		पूर्ण अन्यथा अगर (((ir_tds_bn_dps_das_nvm & NVMD_TYPE) == AAP1_RDUMP)
			|| ((ir_tds_bn_dps_das_nvm & NVMD_TYPE) == IOP_RDUMP)) अणु
			;
		पूर्ण अन्यथा अणु
			/* Should not be happened*/
			pm8001_dbg(pm8001_ha, MSG,
				   "(IR=1)Wrong Device type 0x%x\n",
				   ir_tds_bn_dps_das_nvm);
		पूर्ण
	पूर्ण अन्यथा /* direct mode */अणु
		pm8001_dbg(pm8001_ha, MSG,
			   "Get NVMD success, IR=0, dataLen=%d\n",
			   (dlen_status & NVMD_LEN) >> 24);
	पूर्ण
	/* Though fw_control_context is मुक्तd below, usrAddr still needs
	 * to be updated as this holds the response to the request function
	 */
	स_नकल(fw_control_context->usrAddr,
		pm8001_ha->memoryMap.region[NVMD].virt_ptr,
		fw_control_context->len);
	kमुक्त(ccb->fw_control_context);
	/* To aव्योम race condition, complete should be
	 * called after the message is copied to
	 * fw_control_context->usrAddr
	 */
	complete(pm8001_ha->nvmd_completion);
	pm8001_dbg(pm8001_ha, MSG, "Set nvm data complete!\n");
	ccb->task = शून्य;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_tag_मुक्त(pm8001_ha, tag);
पूर्ण

पूर्णांक pm8001_mpi_local_phy_ctl(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	u32 tag;
	काष्ठा local_phy_ctl_resp *pPayload =
		(काष्ठा local_phy_ctl_resp *)(piomb + 4);
	u32 status = le32_to_cpu(pPayload->status);
	u32 phy_id = le32_to_cpu(pPayload->phyop_phyid) & ID_BITS;
	u32 phy_op = le32_to_cpu(pPayload->phyop_phyid) & OP_BITS;
	tag = le32_to_cpu(pPayload->tag);
	अगर (status != 0) अणु
		pm8001_dbg(pm8001_ha, MSG,
			   "%x phy execute %x phy op failed!\n",
			   phy_id, phy_op);
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, MSG,
			   "%x phy execute %x phy op success!\n",
			   phy_id, phy_op);
		pm8001_ha->phy[phy_id].reset_success = true;
	पूर्ण
	अगर (pm8001_ha->phy[phy_id].enable_completion) अणु
		complete(pm8001_ha->phy[phy_id].enable_completion);
		pm8001_ha->phy[phy_id].enable_completion = शून्य;
	पूर्ण
	pm8001_tag_मुक्त(pm8001_ha, tag);
	वापस 0;
पूर्ण

/**
 * pm8001_bytes_dmaed - one of the पूर्णांकerface function communication with libsas
 * @pm8001_ha: our hba card inक्रमmation
 * @i: which phy that received the event.
 *
 * when HBA driver received the identअगरy करोne event or initiate FIS received
 * event(क्रम SATA), it will invoke this function to notअगरy the sas layer that
 * the sas toplogy has क्रमmed, please discover the the whole sas करोमुख्य,
 * जबतक receive a broadcast(change) primitive just tell the sas
 * layer to discover the changed करोमुख्य rather than the whole करोमुख्य.
 */
व्योम pm8001_bytes_dmaed(काष्ठा pm8001_hba_info *pm8001_ha, पूर्णांक i)
अणु
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[i];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	अगर (!phy->phy_attached)
		वापस;

	अगर (sas_phy->phy) अणु
		काष्ठा sas_phy *sphy = sas_phy->phy;
		sphy->negotiated_linkrate = sas_phy->linkrate;
		sphy->minimum_linkrate = phy->minimum_linkrate;
		sphy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
		sphy->maximum_linkrate = phy->maximum_linkrate;
		sphy->maximum_linkrate_hw = phy->maximum_linkrate;
	पूर्ण

	अगर (phy->phy_type & PORT_TYPE_SAS) अणु
		काष्ठा sas_identअगरy_frame *id;
		id = (काष्ठा sas_identअगरy_frame *)phy->frame_rcvd;
		id->dev_type = phy->identअगरy.device_type;
		id->initiator_bits = SAS_PROTOCOL_ALL;
		id->target_bits = phy->identअगरy.target_port_protocols;
	पूर्ण अन्यथा अगर (phy->phy_type & PORT_TYPE_SATA) अणु
		/*Nothing*/
	पूर्ण
	pm8001_dbg(pm8001_ha, MSG, "phy %d byte dmaded.\n", i);

	sas_phy->frame_rcvd_size = phy->frame_rcvd_size;
	sas_notअगरy_port_event(sas_phy, PORTE_BYTES_DMAED, GFP_ATOMIC);
पूर्ण

/* Get the link rate speed  */
व्योम pm8001_get_lrate_mode(काष्ठा pm8001_phy *phy, u8 link_rate)
अणु
	काष्ठा sas_phy *sas_phy = phy->sas_phy.phy;

	चयन (link_rate) अणु
	हाल PHY_SPEED_120:
		phy->sas_phy.linkrate = SAS_LINK_RATE_12_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_12_0_GBPS;
		अवरोध;
	हाल PHY_SPEED_60:
		phy->sas_phy.linkrate = SAS_LINK_RATE_6_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_6_0_GBPS;
		अवरोध;
	हाल PHY_SPEED_30:
		phy->sas_phy.linkrate = SAS_LINK_RATE_3_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_3_0_GBPS;
		अवरोध;
	हाल PHY_SPEED_15:
		phy->sas_phy.linkrate = SAS_LINK_RATE_1_5_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_1_5_GBPS;
		अवरोध;
	पूर्ण
	sas_phy->negotiated_linkrate = phy->sas_phy.linkrate;
	sas_phy->maximum_linkrate_hw = SAS_LINK_RATE_6_0_GBPS;
	sas_phy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
	sas_phy->maximum_linkrate = SAS_LINK_RATE_6_0_GBPS;
	sas_phy->minimum_linkrate = SAS_LINK_RATE_1_5_GBPS;
पूर्ण

/**
 * pm8001_get_attached_sas_addr - extract/generate attached SAS address
 * @phy: poपूर्णांकer to asd_phy
 * @sas_addr: poपूर्णांकer to buffer where the SAS address is to be written
 *
 * This function extracts the SAS address from an IDENTIFY frame
 * received.  If OOB is SATA, then a SAS address is generated from the
 * HA tables.
 *
 * LOCKING: the frame_rcvd_lock needs to be held since this parses the frame
 * buffer.
 */
व्योम pm8001_get_attached_sas_addr(काष्ठा pm8001_phy *phy,
	u8 *sas_addr)
अणु
	अगर (phy->sas_phy.frame_rcvd[0] == 0x34
		&& phy->sas_phy.oob_mode == SATA_OOB_MODE) अणु
		काष्ठा pm8001_hba_info *pm8001_ha = phy->sas_phy.ha->lldd_ha;
		/* FIS device-to-host */
		u64 addr = be64_to_cpu(*(__be64 *)pm8001_ha->sas_addr);
		addr += phy->sas_phy.id;
		*(__be64 *)sas_addr = cpu_to_be64(addr);
	पूर्ण अन्यथा अणु
		काष्ठा sas_identअगरy_frame *idframe =
			(व्योम *) phy->sas_phy.frame_rcvd;
		स_नकल(sas_addr, idframe->sas_addr, SAS_ADDR_SIZE);
	पूर्ण
पूर्ण

/**
 * pm8001_hw_event_ack_req- For PM8001,some events need to acknowage to FW.
 * @pm8001_ha: our hba card inक्रमmation
 * @Qnum: the outbound queue message number.
 * @SEA: source of event to ack
 * @port_id: port id.
 * @phyId: phy id.
 * @param0: parameter 0.
 * @param1: parameter 1.
 */
अटल व्योम pm8001_hw_event_ack_req(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 Qnum, u32 SEA, u32 port_id, u32 phyId, u32 param0, u32 param1)
अणु
	काष्ठा hw_event_ack_req	 payload;
	u32 opc = OPC_INB_SAS_HW_EVENT_ACK;

	काष्ठा inbound_queue_table *circularQ;

	स_रखो((u8 *)&payload, 0, माप(payload));
	circularQ = &pm8001_ha->inbnd_q_tbl[Qnum];
	payload.tag = cpu_to_le32(1);
	payload.sea_phyid_portid = cpu_to_le32(((SEA & 0xFFFF) << 8) |
		((phyId & 0x0F) << 4) | (port_id & 0x0F));
	payload.param0 = cpu_to_le32(param0);
	payload.param1 = cpu_to_le32(param1);
	pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
पूर्ण

अटल पूर्णांक pm8001_chip_phy_ctl_req(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 phyId, u32 phy_op);

/**
 * hw_event_sas_phy_up -FW tells me a SAS phy up event.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल व्योम
hw_event_sas_phy_up(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा hw_event_resp *pPayload =
		(काष्ठा hw_event_resp *)(piomb + 4);
	u32 lr_evt_status_phyid_portid =
		le32_to_cpu(pPayload->lr_evt_status_phyid_portid);
	u8 link_rate =
		(u8)((lr_evt_status_phyid_portid & 0xF0000000) >> 28);
	u8 port_id = (u8)(lr_evt_status_phyid_portid & 0x0000000F);
	u8 phy_id =
		(u8)((lr_evt_status_phyid_portid & 0x000000F0) >> 4);
	u32 npip_portstate = le32_to_cpu(pPayload->npip_portstate);
	u8 portstate = (u8)(npip_portstate & 0x0000000F);
	काष्ठा pm8001_port *port = &pm8001_ha->port[port_id];
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	अचिन्हित दीर्घ flags;
	u8 deviceType = pPayload->sas_identअगरy.dev_type;
	port->port_state =  portstate;
	phy->phy_state = PHY_STATE_LINK_UP_SPC;
	pm8001_dbg(pm8001_ha, MSG,
		   "HW_EVENT_SAS_PHY_UP port id = %d, phy id = %d\n",
		   port_id, phy_id);

	चयन (deviceType) अणु
	हाल SAS_PHY_UNUSED:
		pm8001_dbg(pm8001_ha, MSG, "device type no device.\n");
		अवरोध;
	हाल SAS_END_DEVICE:
		pm8001_dbg(pm8001_ha, MSG, "end device.\n");
		pm8001_chip_phy_ctl_req(pm8001_ha, phy_id,
			PHY_NOTIFY_ENABLE_SPINUP);
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		अवरोध;
	हाल SAS_EDGE_EXPANDER_DEVICE:
		pm8001_dbg(pm8001_ha, MSG, "expander device.\n");
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		अवरोध;
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		pm8001_dbg(pm8001_ha, MSG, "fanout expander device.\n");
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "unknown device type(%x)\n",
			   deviceType);
		अवरोध;
	पूर्ण
	phy->phy_type |= PORT_TYPE_SAS;
	phy->identअगरy.device_type = deviceType;
	phy->phy_attached = 1;
	अगर (phy->identअगरy.device_type == SAS_END_DEVICE)
		phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SSP;
	अन्यथा अगर (phy->identअगरy.device_type != SAS_PHY_UNUSED)
		phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SMP;
	phy->sas_phy.oob_mode = SAS_OOB_MODE;
	sas_notअगरy_phy_event(&phy->sas_phy, PHYE_OOB_DONE, GFP_ATOMIC);
	spin_lock_irqsave(&phy->sas_phy.frame_rcvd_lock, flags);
	स_नकल(phy->frame_rcvd, &pPayload->sas_identअगरy,
		माप(काष्ठा sas_identअगरy_frame)-4);
	phy->frame_rcvd_size = माप(काष्ठा sas_identअगरy_frame) - 4;
	pm8001_get_attached_sas_addr(phy, phy->sas_phy.attached_sas_addr);
	spin_unlock_irqrestore(&phy->sas_phy.frame_rcvd_lock, flags);
	अगर (pm8001_ha->flags == PM8001F_RUN_TIME)
		mdelay(200);/*delay a moment to रुको disk to spinup*/
	pm8001_bytes_dmaed(pm8001_ha, phy_id);
पूर्ण

/**
 * hw_event_sata_phy_up -FW tells me a SATA phy up event.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल व्योम
hw_event_sata_phy_up(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा hw_event_resp *pPayload =
		(काष्ठा hw_event_resp *)(piomb + 4);
	u32 lr_evt_status_phyid_portid =
		le32_to_cpu(pPayload->lr_evt_status_phyid_portid);
	u8 link_rate =
		(u8)((lr_evt_status_phyid_portid & 0xF0000000) >> 28);
	u8 port_id = (u8)(lr_evt_status_phyid_portid & 0x0000000F);
	u8 phy_id =
		(u8)((lr_evt_status_phyid_portid & 0x000000F0) >> 4);
	u32 npip_portstate = le32_to_cpu(pPayload->npip_portstate);
	u8 portstate = (u8)(npip_portstate & 0x0000000F);
	काष्ठा pm8001_port *port = &pm8001_ha->port[port_id];
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	अचिन्हित दीर्घ flags;
	pm8001_dbg(pm8001_ha, DEVIO, "HW_EVENT_SATA_PHY_UP port id = %d, phy id = %d\n",
		   port_id, phy_id);
	port->port_state =  portstate;
	phy->phy_state = PHY_STATE_LINK_UP_SPC;
	port->port_attached = 1;
	pm8001_get_lrate_mode(phy, link_rate);
	phy->phy_type |= PORT_TYPE_SATA;
	phy->phy_attached = 1;
	phy->sas_phy.oob_mode = SATA_OOB_MODE;
	sas_notअगरy_phy_event(&phy->sas_phy, PHYE_OOB_DONE, GFP_ATOMIC);
	spin_lock_irqsave(&phy->sas_phy.frame_rcvd_lock, flags);
	स_नकल(phy->frame_rcvd, ((u8 *)&pPayload->sata_fis - 4),
		माप(काष्ठा dev_to_host_fis));
	phy->frame_rcvd_size = माप(काष्ठा dev_to_host_fis);
	phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SATA;
	phy->identअगरy.device_type = SAS_SATA_DEV;
	pm8001_get_attached_sas_addr(phy, phy->sas_phy.attached_sas_addr);
	spin_unlock_irqrestore(&phy->sas_phy.frame_rcvd_lock, flags);
	pm8001_bytes_dmaed(pm8001_ha, phy_id);
पूर्ण

/**
 * hw_event_phy_करोwn -we should notअगरy the libsas the phy is करोwn.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल व्योम
hw_event_phy_करोwn(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा hw_event_resp *pPayload =
		(काष्ठा hw_event_resp *)(piomb + 4);
	u32 lr_evt_status_phyid_portid =
		le32_to_cpu(pPayload->lr_evt_status_phyid_portid);
	u8 port_id = (u8)(lr_evt_status_phyid_portid & 0x0000000F);
	u8 phy_id =
		(u8)((lr_evt_status_phyid_portid & 0x000000F0) >> 4);
	u32 npip_portstate = le32_to_cpu(pPayload->npip_portstate);
	u8 portstate = (u8)(npip_portstate & 0x0000000F);
	काष्ठा pm8001_port *port = &pm8001_ha->port[port_id];
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	port->port_state =  portstate;
	phy->phy_type = 0;
	phy->identअगरy.device_type = 0;
	phy->phy_attached = 0;
	स_रखो(&phy->dev_sas_addr, 0, SAS_ADDR_SIZE);
	चयन (portstate) अणु
	हाल PORT_VALID:
		अवरोध;
	हाल PORT_INVALID:
		pm8001_dbg(pm8001_ha, MSG, " PortInvalid portID %d\n",
			   port_id);
		pm8001_dbg(pm8001_ha, MSG,
			   " Last phy Down and port invalid\n");
		port->port_attached = 0;
		pm8001_hw_event_ack_req(pm8001_ha, 0, HW_EVENT_PHY_DOWN,
			port_id, phy_id, 0, 0);
		अवरोध;
	हाल PORT_IN_RESET:
		pm8001_dbg(pm8001_ha, MSG, " Port In Reset portID %d\n",
			   port_id);
		अवरोध;
	हाल PORT_NOT_ESTABLISHED:
		pm8001_dbg(pm8001_ha, MSG,
			   " phy Down and PORT_NOT_ESTABLISHED\n");
		port->port_attached = 0;
		अवरोध;
	हाल PORT_LOSTCOMM:
		pm8001_dbg(pm8001_ha, MSG, " phy Down and PORT_LOSTCOMM\n");
		pm8001_dbg(pm8001_ha, MSG,
			   " Last phy Down and port invalid\n");
		port->port_attached = 0;
		pm8001_hw_event_ack_req(pm8001_ha, 0, HW_EVENT_PHY_DOWN,
			port_id, phy_id, 0, 0);
		अवरोध;
	शेष:
		port->port_attached = 0;
		pm8001_dbg(pm8001_ha, DEVIO, " phy Down and(default) = %x\n",
			   portstate);
		अवरोध;

	पूर्ण
पूर्ण

/**
 * pm8001_mpi_reg_resp -process रेजिस्टर device ID response.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 *
 * when sas layer find a device it will notअगरy LLDD, then the driver रेजिस्टर
 * the करोमुख्य device to FW, this event is the वापस device ID which the FW
 * has asचिन्हित, from now,पूर्णांकer-communication with FW is no दीर्घer using the
 * SAS address, use device ID which FW asचिन्हित.
 */
पूर्णांक pm8001_mpi_reg_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	u32 status;
	u32 device_id;
	u32 htag;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा dev_reg_resp *रेजिस्टरRespPayload =
		(काष्ठा dev_reg_resp *)(piomb + 4);

	htag = le32_to_cpu(रेजिस्टरRespPayload->tag);
	ccb = &pm8001_ha->ccb_info[htag];
	pm8001_dev = ccb->device;
	status = le32_to_cpu(रेजिस्टरRespPayload->status);
	device_id = le32_to_cpu(रेजिस्टरRespPayload->device_id);
	pm8001_dbg(pm8001_ha, MSG, " register device is status = %d\n",
		   status);
	चयन (status) अणु
	हाल DEVREG_SUCCESS:
		pm8001_dbg(pm8001_ha, MSG, "DEVREG_SUCCESS\n");
		pm8001_dev->device_id = device_id;
		अवरोध;
	हाल DEVREG_FAILURE_OUT_OF_RESOURCE:
		pm8001_dbg(pm8001_ha, MSG, "DEVREG_FAILURE_OUT_OF_RESOURCE\n");
		अवरोध;
	हाल DEVREG_FAILURE_DEVICE_ALREADY_REGISTERED:
		pm8001_dbg(pm8001_ha, MSG,
			   "DEVREG_FAILURE_DEVICE_ALREADY_REGISTERED\n");
		अवरोध;
	हाल DEVREG_FAILURE_INVALID_PHY_ID:
		pm8001_dbg(pm8001_ha, MSG, "DEVREG_FAILURE_INVALID_PHY_ID\n");
		अवरोध;
	हाल DEVREG_FAILURE_PHY_ID_ALREADY_REGISTERED:
		pm8001_dbg(pm8001_ha, MSG,
			   "DEVREG_FAILURE_PHY_ID_ALREADY_REGISTERED\n");
		अवरोध;
	हाल DEVREG_FAILURE_PORT_ID_OUT_OF_RANGE:
		pm8001_dbg(pm8001_ha, MSG,
			   "DEVREG_FAILURE_PORT_ID_OUT_OF_RANGE\n");
		अवरोध;
	हाल DEVREG_FAILURE_PORT_NOT_VALID_STATE:
		pm8001_dbg(pm8001_ha, MSG,
			   "DEVREG_FAILURE_PORT_NOT_VALID_STATE\n");
		अवरोध;
	हाल DEVREG_FAILURE_DEVICE_TYPE_NOT_VALID:
		pm8001_dbg(pm8001_ha, MSG,
			   "DEVREG_FAILURE_DEVICE_TYPE_NOT_VALID\n");
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, MSG,
			   "DEVREG_FAILURE_DEVICE_TYPE_NOT_SUPPORTED\n");
		अवरोध;
	पूर्ण
	complete(pm8001_dev->dcompletion);
	ccb->task = शून्य;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_tag_मुक्त(pm8001_ha, htag);
	वापस 0;
पूर्ण

पूर्णांक pm8001_mpi_dereg_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	u32 status;
	u32 device_id;
	काष्ठा dev_reg_resp *रेजिस्टरRespPayload =
		(काष्ठा dev_reg_resp *)(piomb + 4);

	status = le32_to_cpu(रेजिस्टरRespPayload->status);
	device_id = le32_to_cpu(रेजिस्टरRespPayload->device_id);
	अगर (status != 0)
		pm8001_dbg(pm8001_ha, MSG,
			   " deregister device failed ,status = %x, device_id = %x\n",
			   status, device_id);
	वापस 0;
पूर्ण

/**
 * pm8001_mpi_fw_flash_update_resp - Response from FW क्रम flash update command.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
पूर्णांक pm8001_mpi_fw_flash_update_resp(काष्ठा pm8001_hba_info *pm8001_ha,
		व्योम *piomb)
अणु
	u32 status;
	काष्ठा fw_flash_Update_resp *ppayload =
		(काष्ठा fw_flash_Update_resp *)(piomb + 4);
	u32 tag = le32_to_cpu(ppayload->tag);
	काष्ठा pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[tag];
	status = le32_to_cpu(ppayload->status);
	चयन (status) अणु
	हाल FLASH_UPDATE_COMPLETE_PENDING_REBOOT:
		pm8001_dbg(pm8001_ha, MSG,
			   ": FLASH_UPDATE_COMPLETE_PENDING_REBOOT\n");
		अवरोध;
	हाल FLASH_UPDATE_IN_PROGRESS:
		pm8001_dbg(pm8001_ha, MSG, ": FLASH_UPDATE_IN_PROGRESS\n");
		अवरोध;
	हाल FLASH_UPDATE_HDR_ERR:
		pm8001_dbg(pm8001_ha, MSG, ": FLASH_UPDATE_HDR_ERR\n");
		अवरोध;
	हाल FLASH_UPDATE_OFFSET_ERR:
		pm8001_dbg(pm8001_ha, MSG, ": FLASH_UPDATE_OFFSET_ERR\n");
		अवरोध;
	हाल FLASH_UPDATE_CRC_ERR:
		pm8001_dbg(pm8001_ha, MSG, ": FLASH_UPDATE_CRC_ERR\n");
		अवरोध;
	हाल FLASH_UPDATE_LENGTH_ERR:
		pm8001_dbg(pm8001_ha, MSG, ": FLASH_UPDATE_LENGTH_ERR\n");
		अवरोध;
	हाल FLASH_UPDATE_HW_ERR:
		pm8001_dbg(pm8001_ha, MSG, ": FLASH_UPDATE_HW_ERR\n");
		अवरोध;
	हाल FLASH_UPDATE_DNLD_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, MSG,
			   ": FLASH_UPDATE_DNLD_NOT_SUPPORTED\n");
		अवरोध;
	हाल FLASH_UPDATE_DISABLED:
		pm8001_dbg(pm8001_ha, MSG, ": FLASH_UPDATE_DISABLED\n");
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "No matched status = %d\n",
			   status);
		अवरोध;
	पूर्ण
	kमुक्त(ccb->fw_control_context);
	ccb->task = शून्य;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_tag_मुक्त(pm8001_ha, tag);
	complete(pm8001_ha->nvmd_completion);
	वापस 0;
पूर्ण

पूर्णांक pm8001_mpi_general_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	u32 status;
	पूर्णांक i;
	काष्ठा general_event_resp *pPayload =
		(काष्ठा general_event_resp *)(piomb + 4);
	status = le32_to_cpu(pPayload->status);
	pm8001_dbg(pm8001_ha, MSG, " status = 0x%x\n", status);
	क्रम (i = 0; i < GENERAL_EVENT_PAYLOAD; i++)
		pm8001_dbg(pm8001_ha, MSG, "inb_IOMB_payload[0x%x] 0x%x,\n",
			   i,
			   pPayload->inb_IOMB_payload[i]);
	वापस 0;
पूर्ण

पूर्णांक pm8001_mpi_task_पात_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	काष्ठा pm8001_ccb_info *ccb;
	अचिन्हित दीर्घ flags;
	u32 status ;
	u32 tag, scp;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा pm8001_device *pm8001_dev;

	काष्ठा task_पात_resp *pPayload =
		(काष्ठा task_पात_resp *)(piomb + 4);

	status = le32_to_cpu(pPayload->status);
	tag = le32_to_cpu(pPayload->tag);
	अगर (!tag) अणु
		pm8001_dbg(pm8001_ha, FAIL, " TAG NULL. RETURNING !!!\n");
		वापस -1;
	पूर्ण

	scp = le32_to_cpu(pPayload->scp);
	ccb = &pm8001_ha->ccb_info[tag];
	t = ccb->task;
	pm8001_dev = ccb->device; /* retrieve device */

	अगर (!t)	अणु
		pm8001_dbg(pm8001_ha, FAIL, " TASK NULL. RETURNING !!!\n");
		वापस -1;
	पूर्ण
	ts = &t->task_status;
	अगर (status != 0)
		pm8001_dbg(pm8001_ha, FAIL, "task abort failed status 0x%x ,tag = 0x%x, scp= 0x%x\n",
			   status, tag, scp);
	चयन (status) अणु
	हाल IO_SUCCESS:
		pm8001_dbg(pm8001_ha, EH, "IO_SUCCESS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_GOOD;
		अवरोध;
	हाल IO_NOT_VALID:
		pm8001_dbg(pm8001_ha, EH, "IO_NOT_VALID\n");
		ts->resp = TMF_RESP_FUNC_FAILED;
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	spin_unlock_irqrestore(&t->task_state_lock, flags);
	pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	mb();

	अगर (pm8001_dev->id & NCQ_ABORT_ALL_FLAG) अणु
		pm8001_tag_मुक्त(pm8001_ha, tag);
		sas_मुक्त_task(t);
		/* clear the flag */
		pm8001_dev->id &= 0xBFFFFFFF;
	पूर्ण अन्यथा
		t->task_करोne(t);

	वापस 0;
पूर्ण

/**
 * mpi_hw_event -The hw event has come.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_hw_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hw_event_resp *pPayload =
		(काष्ठा hw_event_resp *)(piomb + 4);
	u32 lr_evt_status_phyid_portid =
		le32_to_cpu(pPayload->lr_evt_status_phyid_portid);
	u8 port_id = (u8)(lr_evt_status_phyid_portid & 0x0000000F);
	u8 phy_id =
		(u8)((lr_evt_status_phyid_portid & 0x000000F0) >> 4);
	u16 eventType =
		(u16)((lr_evt_status_phyid_portid & 0x00FFFF00) >> 8);
	u8 status =
		(u8)((lr_evt_status_phyid_portid & 0x0F000000) >> 24);
	काष्ठा sas_ha_काष्ठा *sas_ha = pm8001_ha->sas;
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	काष्ठा asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	pm8001_dbg(pm8001_ha, DEVIO,
		   "SPC HW event for portid:%d, phyid:%d, event:%x, status:%x\n",
		   port_id, phy_id, eventType, status);
	चयन (eventType) अणु
	हाल HW_EVENT_PHY_START_STATUS:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PHY_START_STATUS status = %x\n",
			   status);
		अगर (status == 0)
			phy->phy_state = 1;

		अगर (pm8001_ha->flags == PM8001F_RUN_TIME &&
				phy->enable_completion != शून्य) अणु
			complete(phy->enable_completion);
			phy->enable_completion = शून्य;
		पूर्ण
		अवरोध;
	हाल HW_EVENT_SAS_PHY_UP:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PHY_START_STATUS\n");
		hw_event_sas_phy_up(pm8001_ha, piomb);
		अवरोध;
	हाल HW_EVENT_SATA_PHY_UP:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_SATA_PHY_UP\n");
		hw_event_sata_phy_up(pm8001_ha, piomb);
		अवरोध;
	हाल HW_EVENT_PHY_STOP_STATUS:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PHY_STOP_STATUS status = %x\n",
			   status);
		अगर (status == 0)
			phy->phy_state = 0;
		अवरोध;
	हाल HW_EVENT_SATA_SPINUP_HOLD:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_SATA_SPINUP_HOLD\n");
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_SPINUP_HOLD,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_PHY_DOWN:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PHY_DOWN\n");
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_LOSS_OF_SIGNAL,
			GFP_ATOMIC);
		phy->phy_attached = 0;
		phy->phy_state = 0;
		hw_event_phy_करोwn(pm8001_ha, piomb);
		अवरोध;
	हाल HW_EVENT_PORT_INVALID:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PORT_INVALID\n");
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	/* the broadcast change primitive received, tell the LIBSAS this event
	to revalidate the sas करोमुख्य*/
	हाल HW_EVENT_BROADCAST_CHANGE:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_BROADCAST_CHANGE\n");
		pm8001_hw_event_ack_req(pm8001_ha, 0, HW_EVENT_BROADCAST_CHANGE,
			port_id, phy_id, 1, 0);
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_CHANGE;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_PHY_ERROR:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PHY_ERROR\n");
		sas_phy_disconnected(&phy->sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_OOB_ERROR, GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_BROADCAST_EXP:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_BROADCAST_EXP\n");
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_EXP;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_INVALID_DWORD:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_INVALID_DWORD\n");
		pm8001_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_INVALID_DWORD, port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_DISPARITY_ERROR:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_DISPARITY_ERROR\n");
		pm8001_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_DISPARITY_ERROR,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_CODE_VIOLATION:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_CODE_VIOLATION\n");
		pm8001_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_CODE_VIOLATION,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH\n");
		pm8001_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_MALFUNCTION:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_MALFUNCTION\n");
		अवरोध;
	हाल HW_EVENT_BROADCAST_SES:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_BROADCAST_SES\n");
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_SES;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_INBOUND_CRC_ERROR:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_INBOUND_CRC_ERROR\n");
		pm8001_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_INBOUND_CRC_ERROR,
			port_id, phy_id, 0, 0);
		अवरोध;
	हाल HW_EVENT_HARD_RESET_RECEIVED:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_HARD_RESET_RECEIVED\n");
		sas_notअगरy_port_event(sas_phy, PORTE_HARD_RESET, GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_ID_FRAME_TIMEOUT:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_ID_FRAME_TIMEOUT\n");
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_PHY_RESET_FAILED:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_PHY_RESET_FAILED\n");
		pm8001_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_PHY_RESET_FAILED,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_PORT_RESET_TIMER_TMO:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PORT_RESET_TIMER_TMO\n");
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_PORT_RECOVERY_TIMER_TMO:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_PORT_RECOVERY_TIMER_TMO\n");
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_PORT_RECOVER:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PORT_RECOVER\n");
		अवरोध;
	हाल HW_EVENT_PORT_RESET_COMPLETE:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PORT_RESET_COMPLETE\n");
		अवरोध;
	हाल EVENT_BROADCAST_ASYNCH_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "EVENT_BROADCAST_ASYNCH_EVENT\n");
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown event type = %x\n",
			   eventType);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * process_one_iomb - process one outbound Queue memory block
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल व्योम process_one_iomb(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	__le32 pHeader = *(__le32 *)piomb;
	u8 opc = (u8)((le32_to_cpu(pHeader)) & 0xFFF);

	pm8001_dbg(pm8001_ha, MSG, "process_one_iomb:\n");

	चयन (opc) अणु
	हाल OPC_OUB_ECHO:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_ECHO\n");
		अवरोध;
	हाल OPC_OUB_HW_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_HW_EVENT\n");
		mpi_hw_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SSP_COMP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SSP_COMP\n");
		mpi_ssp_completion(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SMP_COMP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SMP_COMP\n");
		mpi_smp_completion(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_LOCAL_PHY_CNTRL:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_LOCAL_PHY_CNTRL\n");
		pm8001_mpi_local_phy_ctl(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEV_REGIST:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_DEV_REGIST\n");
		pm8001_mpi_reg_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEREG_DEV:
		pm8001_dbg(pm8001_ha, MSG, "unregister the device\n");
		pm8001_mpi_dereg_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GET_DEV_HANDLE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GET_DEV_HANDLE\n");
		अवरोध;
	हाल OPC_OUB_SATA_COMP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SATA_COMP\n");
		mpi_sata_completion(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SATA_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SATA_EVENT\n");
		mpi_sata_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SSP_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SSP_EVENT\n");
		mpi_ssp_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEV_HANDLE_ARRIV:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_DEV_HANDLE_ARRIV\n");
		/*This is क्रम target*/
		अवरोध;
	हाल OPC_OUB_SSP_RECV_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SSP_RECV_EVENT\n");
		/*This is क्रम target*/
		अवरोध;
	हाल OPC_OUB_DEV_INFO:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_DEV_INFO\n");
		अवरोध;
	हाल OPC_OUB_FW_FLASH_UPDATE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_FW_FLASH_UPDATE\n");
		pm8001_mpi_fw_flash_update_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GPIO_RESPONSE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GPIO_RESPONSE\n");
		अवरोध;
	हाल OPC_OUB_GPIO_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GPIO_EVENT\n");
		अवरोध;
	हाल OPC_OUB_GENERAL_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GENERAL_EVENT\n");
		pm8001_mpi_general_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SSP_ABORT_RSP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SSP_ABORT_RSP\n");
		pm8001_mpi_task_पात_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SATA_ABORT_RSP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SATA_ABORT_RSP\n");
		pm8001_mpi_task_पात_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SAS_DIAG_MODE_START_END:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_SAS_DIAG_MODE_START_END\n");
		अवरोध;
	हाल OPC_OUB_SAS_DIAG_EXECUTE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SAS_DIAG_EXECUTE\n");
		अवरोध;
	हाल OPC_OUB_GET_TIME_STAMP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GET_TIME_STAMP\n");
		अवरोध;
	हाल OPC_OUB_SAS_HW_EVENT_ACK:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SAS_HW_EVENT_ACK\n");
		अवरोध;
	हाल OPC_OUB_PORT_CONTROL:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_PORT_CONTROL\n");
		अवरोध;
	हाल OPC_OUB_SMP_ABORT_RSP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SMP_ABORT_RSP\n");
		pm8001_mpi_task_पात_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GET_NVMD_DATA:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GET_NVMD_DATA\n");
		pm8001_mpi_get_nvmd_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SET_NVMD_DATA:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SET_NVMD_DATA\n");
		pm8001_mpi_set_nvmd_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEVICE_HANDLE_REMOVAL:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_DEVICE_HANDLE_REMOVAL\n");
		अवरोध;
	हाल OPC_OUB_SET_DEVICE_STATE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SET_DEVICE_STATE\n");
		pm8001_mpi_set_dev_state_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GET_DEVICE_STATE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GET_DEVICE_STATE\n");
		अवरोध;
	हाल OPC_OUB_SET_DEV_INFO:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SET_DEV_INFO\n");
		अवरोध;
	हाल OPC_OUB_SAS_RE_INITIALIZE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SAS_RE_INITIALIZE\n");
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO,
			   "Unknown outbound Queue IOMB OPC = %x\n",
			   opc);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक process_oq(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec)
अणु
	काष्ठा outbound_queue_table *circularQ;
	व्योम *pMsg1 = शून्य;
	u8 bc;
	u32 ret = MPI_IO_STATUS_FAIL;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pm8001_ha->lock, flags);
	circularQ = &pm8001_ha->outbnd_q_tbl[vec];
	करो अणु
		ret = pm8001_mpi_msg_consume(pm8001_ha, circularQ, &pMsg1, &bc);
		अगर (MPI_IO_STATUS_SUCCESS == ret) अणु
			/* process the outbound message */
			process_one_iomb(pm8001_ha, (व्योम *)(pMsg1 - 4));
			/* मुक्त the message from the outbound circular buffer */
			pm8001_mpi_msg_मुक्त_set(pm8001_ha, pMsg1,
							circularQ, bc);
		पूर्ण
		अगर (MPI_IO_STATUS_BUSY == ret) अणु
			/* Update the producer index from SPC */
			circularQ->producer_index =
				cpu_to_le32(pm8001_पढ़ो_32(circularQ->pi_virt));
			अगर (le32_to_cpu(circularQ->producer_index) ==
				circularQ->consumer_idx)
				/* OQ is empty */
				अवरोध;
		पूर्ण
	पूर्ण जबतक (1);
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	वापस ret;
पूर्ण

/* DMA_... to our direction translation. */
अटल स्थिर u8 data_dir_flags[] = अणु
	[DMA_BIसूचीECTIONAL]	= DATA_सूची_BYRECIPIENT,	/* UNSPECIFIED */
	[DMA_TO_DEVICE]		= DATA_सूची_OUT,		/* OUTBOUND */
	[DMA_FROM_DEVICE]	= DATA_सूची_IN,		/* INBOUND */
	[DMA_NONE]		= DATA_सूची_NONE,	/* NO TRANSFER */
पूर्ण;
व्योम
pm8001_chip_make_sg(काष्ठा scatterlist *scatter, पूर्णांक nr, व्योम *prd)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;
	काष्ठा pm8001_prd *buf_prd = prd;

	क्रम_each_sg(scatter, sg, nr, i) अणु
		buf_prd->addr = cpu_to_le64(sg_dma_address(sg));
		buf_prd->im_len.len = cpu_to_le32(sg_dma_len(sg));
		buf_prd->im_len.e = 0;
		buf_prd++;
	पूर्ण
पूर्ण

अटल व्योम build_smp_cmd(u32 deviceID, __le32 hTag, काष्ठा smp_req *psmp_cmd)
अणु
	psmp_cmd->tag = hTag;
	psmp_cmd->device_id = cpu_to_le32(deviceID);
	psmp_cmd->len_ip_ir = cpu_to_le32(1|(1 << 1));
पूर्ण

/**
 * pm8001_chip_smp_req - send a SMP task to FW
 * @pm8001_ha: our hba card inक्रमmation.
 * @ccb: the ccb inक्रमmation this request used.
 */
अटल पूर्णांक pm8001_chip_smp_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	पूर्णांक elem, rc;
	काष्ठा sas_task *task = ccb->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;
	काष्ठा scatterlist *sg_req, *sg_resp;
	u32 req_len, resp_len;
	काष्ठा smp_req smp_cmd;
	u32 opc;
	काष्ठा inbound_queue_table *circularQ;

	स_रखो(&smp_cmd, 0, माप(smp_cmd));
	/*
	 * DMA-map SMP request, response buffers
	 */
	sg_req = &task->smp_task.smp_req;
	elem = dma_map_sg(pm8001_ha->dev, sg_req, 1, DMA_TO_DEVICE);
	अगर (!elem)
		वापस -ENOMEM;
	req_len = sg_dma_len(sg_req);

	sg_resp = &task->smp_task.smp_resp;
	elem = dma_map_sg(pm8001_ha->dev, sg_resp, 1, DMA_FROM_DEVICE);
	अगर (!elem) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण
	resp_len = sg_dma_len(sg_resp);
	/* must be in dwords */
	अगर ((req_len & 0x3) || (resp_len & 0x3)) अणु
		rc = -EINVAL;
		जाओ err_out_2;
	पूर्ण

	opc = OPC_INB_SMP_REQUEST;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	smp_cmd.tag = cpu_to_le32(ccb->ccb_tag);
	smp_cmd.दीर्घ_smp_req.दीर्घ_req_addr =
		cpu_to_le64((u64)sg_dma_address(&task->smp_task.smp_req));
	smp_cmd.दीर्घ_smp_req.दीर्घ_req_size =
		cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_req)-4);
	smp_cmd.दीर्घ_smp_req.दीर्घ_resp_addr =
		cpu_to_le64((u64)sg_dma_address(&task->smp_task.smp_resp));
	smp_cmd.दीर्घ_smp_req.दीर्घ_resp_size =
		cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_resp)-4);
	build_smp_cmd(pm8001_dev->device_id, smp_cmd.tag, &smp_cmd);
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc,
			&smp_cmd, माप(smp_cmd), 0);
	अगर (rc)
		जाओ err_out_2;

	वापस 0;

err_out_2:
	dma_unmap_sg(pm8001_ha->dev, &ccb->task->smp_task.smp_resp, 1,
			DMA_FROM_DEVICE);
err_out:
	dma_unmap_sg(pm8001_ha->dev, &ccb->task->smp_task.smp_req, 1,
			DMA_TO_DEVICE);
	वापस rc;
पूर्ण

/**
 * pm8001_chip_ssp_io_req - send a SSP task to FW
 * @pm8001_ha: our hba card inक्रमmation.
 * @ccb: the ccb inक्रमmation this request used.
 */
अटल पूर्णांक pm8001_chip_ssp_io_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	काष्ठा sas_task *task = ccb->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;
	काष्ठा ssp_ini_io_start_req ssp_cmd;
	u32 tag = ccb->ccb_tag;
	पूर्णांक ret;
	u64 phys_addr;
	काष्ठा inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SSPINIIOSTART;
	स_रखो(&ssp_cmd, 0, माप(ssp_cmd));
	स_नकल(ssp_cmd.ssp_iu.lun, task->ssp_task.LUN, 8);
	ssp_cmd.dir_m_tlr =
		cpu_to_le32(data_dir_flags[task->data_dir] << 8 | 0x0);/*0 क्रम
	SAS 1.1 compatible TLR*/
	ssp_cmd.data_len = cpu_to_le32(task->total_xfer_len);
	ssp_cmd.device_id = cpu_to_le32(pm8001_dev->device_id);
	ssp_cmd.tag = cpu_to_le32(tag);
	अगर (task->ssp_task.enable_first_burst)
		ssp_cmd.ssp_iu.efb_prio_attr |= 0x80;
	ssp_cmd.ssp_iu.efb_prio_attr |= (task->ssp_task.task_prio << 3);
	ssp_cmd.ssp_iu.efb_prio_attr |= (task->ssp_task.task_attr & 7);
	स_नकल(ssp_cmd.ssp_iu.cdb, task->ssp_task.cmd->cmnd,
	       task->ssp_task.cmd->cmd_len);
	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	/* fill in PRD (scatter/gather) table, अगर any */
	अगर (task->num_scatter > 1) अणु
		pm8001_chip_make_sg(task->scatter, ccb->n_elem, ccb->buf_prd);
		phys_addr = ccb->ccb_dma_handle;
		ssp_cmd.addr_low = cpu_to_le32(lower_32_bits(phys_addr));
		ssp_cmd.addr_high = cpu_to_le32(upper_32_bits(phys_addr));
		ssp_cmd.esgl = cpu_to_le32(1<<31);
	पूर्ण अन्यथा अगर (task->num_scatter == 1) अणु
		u64 dma_addr = sg_dma_address(task->scatter);
		ssp_cmd.addr_low = cpu_to_le32(lower_32_bits(dma_addr));
		ssp_cmd.addr_high = cpu_to_le32(upper_32_bits(dma_addr));
		ssp_cmd.len = cpu_to_le32(task->total_xfer_len);
		ssp_cmd.esgl = 0;
	पूर्ण अन्यथा अगर (task->num_scatter == 0) अणु
		ssp_cmd.addr_low = 0;
		ssp_cmd.addr_high = 0;
		ssp_cmd.len = cpu_to_le32(task->total_xfer_len);
		ssp_cmd.esgl = 0;
	पूर्ण
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &ssp_cmd,
			माप(ssp_cmd), 0);
	वापस ret;
पूर्ण

अटल पूर्णांक pm8001_chip_sata_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	काष्ठा sas_task *task = ccb->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा pm8001_device *pm8001_ha_dev = dev->lldd_dev;
	u32 tag = ccb->ccb_tag;
	पूर्णांक ret;
	काष्ठा sata_start_req sata_cmd;
	u32 hdr_tag, ncg_tag = 0;
	u64 phys_addr;
	u32 ATAP = 0x0;
	u32 dir;
	काष्ठा inbound_queue_table *circularQ;
	अचिन्हित दीर्घ flags;
	u32  opc = OPC_INB_SATA_HOST_OPSTART;
	स_रखो(&sata_cmd, 0, माप(sata_cmd));
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	अगर (task->data_dir == DMA_NONE) अणु
		ATAP = 0x04;  /* no data*/
		pm8001_dbg(pm8001_ha, IO, "no data\n");
	पूर्ण अन्यथा अगर (likely(!task->ata_task.device_control_reg_update)) अणु
		अगर (task->ata_task.dma_xfer) अणु
			ATAP = 0x06; /* DMA */
			pm8001_dbg(pm8001_ha, IO, "DMA\n");
		पूर्ण अन्यथा अणु
			ATAP = 0x05; /* PIO*/
			pm8001_dbg(pm8001_ha, IO, "PIO\n");
		पूर्ण
		अगर (task->ata_task.use_ncq &&
			dev->sata_dev.class != ATA_DEV_ATAPI) अणु
			ATAP = 0x07; /* FPDMA */
			pm8001_dbg(pm8001_ha, IO, "FPDMA\n");
		पूर्ण
	पूर्ण
	अगर (task->ata_task.use_ncq && pm8001_get_ncq_tag(task, &hdr_tag)) अणु
		task->ata_task.fis.sector_count |= (u8) (hdr_tag << 3);
		ncg_tag = hdr_tag;
	पूर्ण
	dir = data_dir_flags[task->data_dir] << 8;
	sata_cmd.tag = cpu_to_le32(tag);
	sata_cmd.device_id = cpu_to_le32(pm8001_ha_dev->device_id);
	sata_cmd.data_len = cpu_to_le32(task->total_xfer_len);
	sata_cmd.ncqtag_atap_dir_m =
		cpu_to_le32(((ncg_tag & 0xff)<<16)|((ATAP & 0x3f) << 10) | dir);
	sata_cmd.sata_fis = task->ata_task.fis;
	अगर (likely(!task->ata_task.device_control_reg_update))
		sata_cmd.sata_fis.flags |= 0x80;/* C=1: update ATA cmd reg */
	sata_cmd.sata_fis.flags &= 0xF0;/* PM_PORT field shall be 0 */
	/* fill in PRD (scatter/gather) table, अगर any */
	अगर (task->num_scatter > 1) अणु
		pm8001_chip_make_sg(task->scatter, ccb->n_elem, ccb->buf_prd);
		phys_addr = ccb->ccb_dma_handle;
		sata_cmd.addr_low = lower_32_bits(phys_addr);
		sata_cmd.addr_high = upper_32_bits(phys_addr);
		sata_cmd.esgl = cpu_to_le32(1 << 31);
	पूर्ण अन्यथा अगर (task->num_scatter == 1) अणु
		u64 dma_addr = sg_dma_address(task->scatter);
		sata_cmd.addr_low = lower_32_bits(dma_addr);
		sata_cmd.addr_high = upper_32_bits(dma_addr);
		sata_cmd.len = cpu_to_le32(task->total_xfer_len);
		sata_cmd.esgl = 0;
	पूर्ण अन्यथा अगर (task->num_scatter == 0) अणु
		sata_cmd.addr_low = 0;
		sata_cmd.addr_high = 0;
		sata_cmd.len = cpu_to_le32(task->total_xfer_len);
		sata_cmd.esgl = 0;
	पूर्ण

	/* Check क्रम पढ़ो log क्रम failed drive and वापस */
	अगर (sata_cmd.sata_fis.command == 0x2f) अणु
		अगर (((pm8001_ha_dev->id & NCQ_READ_LOG_FLAG) ||
			(pm8001_ha_dev->id & NCQ_ABORT_ALL_FLAG) ||
			(pm8001_ha_dev->id & NCQ_2ND_RLE_FLAG))) अणु
			काष्ठा task_status_काष्ठा *ts;

			pm8001_ha_dev->id &= 0xDFFFFFFF;
			ts = &task->task_status;

			spin_lock_irqsave(&task->task_state_lock, flags);
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAM_STAT_GOOD;
			task->task_state_flags &= ~SAS_TASK_STATE_PENDING;
			task->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
			task->task_state_flags |= SAS_TASK_STATE_DONE;
			अगर (unlikely((task->task_state_flags &
					SAS_TASK_STATE_ABORTED))) अणु
				spin_unlock_irqrestore(&task->task_state_lock,
							flags);
				pm8001_dbg(pm8001_ha, FAIL,
					   "task 0x%p resp 0x%x  stat 0x%x but aborted by upper layer\n",
					   task, ts->resp,
					   ts->stat);
				pm8001_ccb_task_मुक्त(pm8001_ha, task, ccb, tag);
			पूर्ण अन्यथा अणु
				spin_unlock_irqrestore(&task->task_state_lock,
							flags);
				pm8001_ccb_task_मुक्त_करोne(pm8001_ha, task,
								ccb, tag);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &sata_cmd,
			माप(sata_cmd), 0);
	वापस ret;
पूर्ण

/**
 * pm8001_chip_phy_start_req - start phy via PHY_START COMMAND
 * @pm8001_ha: our hba card inक्रमmation.
 * @phy_id: the phy id which we wanted to start up.
 */
अटल पूर्णांक
pm8001_chip_phy_start_req(काष्ठा pm8001_hba_info *pm8001_ha, u8 phy_id)
अणु
	काष्ठा phy_start_req payload;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक ret;
	u32 tag = 0x01;
	u32 opcode = OPC_INB_PHYSTART;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	स_रखो(&payload, 0, माप(payload));
	payload.tag = cpu_to_le32(tag);
	/*
	 ** [0:7]   PHY Identअगरier
	 ** [8:11]  link rate 1.5G, 3G, 6G
	 ** [12:13] link mode 01b SAS mode; 10b SATA mode; 11b both
	 ** [14]    0b disable spin up hold; 1b enable spin up hold
	 */
	payload.ase_sh_lm_slr_phyid = cpu_to_le32(SPINHOLD_DISABLE |
		LINKMODE_AUTO |	LINKRATE_15 |
		LINKRATE_30 | LINKRATE_60 | phy_id);
	payload.sas_identअगरy.dev_type = SAS_END_DEVICE;
	payload.sas_identअगरy.initiator_bits = SAS_PROTOCOL_ALL;
	स_नकल(payload.sas_identअगरy.sas_addr,
		pm8001_ha->sas_addr, SAS_ADDR_SIZE);
	payload.sas_identअगरy.phy_id = phy_id;
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opcode, &payload,
			माप(payload), 0);
	वापस ret;
पूर्ण

/**
 * pm8001_chip_phy_stop_req - start phy via PHY_STOP COMMAND
 * @pm8001_ha: our hba card inक्रमmation.
 * @phy_id: the phy id which we wanted to start up.
 */
अटल पूर्णांक pm8001_chip_phy_stop_req(काष्ठा pm8001_hba_info *pm8001_ha,
				    u8 phy_id)
अणु
	काष्ठा phy_stop_req payload;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक ret;
	u32 tag = 0x01;
	u32 opcode = OPC_INB_PHYSTOP;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	स_रखो(&payload, 0, माप(payload));
	payload.tag = cpu_to_le32(tag);
	payload.phy_id = cpu_to_le32(phy_id);
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opcode, &payload,
			माप(payload), 0);
	वापस ret;
पूर्ण

/*
 * see comments on pm8001_mpi_reg_resp.
 */
अटल पूर्णांक pm8001_chip_reg_dev_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_device *pm8001_dev, u32 flag)
अणु
	काष्ठा reg_dev_req payload;
	u32	opc;
	u32 stp_sspsmp_sata = 0x4;
	काष्ठा inbound_queue_table *circularQ;
	u32 linkrate, phy_id;
	पूर्णांक rc, tag = 0xdeadbeef;
	काष्ठा pm8001_ccb_info *ccb;
	u8 retryFlag = 0x1;
	u16 firstBurstSize = 0;
	u16 ITNT = 2000;
	काष्ठा करोमुख्य_device *dev = pm8001_dev->sas_device;
	काष्ठा करोमुख्य_device *parent_dev = dev->parent;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	स_रखो(&payload, 0, माप(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		वापस rc;
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->device = pm8001_dev;
	ccb->ccb_tag = tag;
	payload.tag = cpu_to_le32(tag);
	अगर (flag == 1)
		stp_sspsmp_sata = 0x02; /*direct attached sata */
	अन्यथा अणु
		अगर (pm8001_dev->dev_type == SAS_SATA_DEV)
			stp_sspsmp_sata = 0x00; /* stp*/
		अन्यथा अगर (pm8001_dev->dev_type == SAS_END_DEVICE ||
			pm8001_dev->dev_type == SAS_EDGE_EXPANDER_DEVICE ||
			pm8001_dev->dev_type == SAS_FANOUT_EXPANDER_DEVICE)
			stp_sspsmp_sata = 0x01; /*ssp or smp*/
	पूर्ण
	अगर (parent_dev && dev_is_expander(parent_dev->dev_type))
		phy_id = parent_dev->ex_dev.ex_phy->phy_id;
	अन्यथा
		phy_id = pm8001_dev->attached_phy;
	opc = OPC_INB_REG_DEV;
	linkrate = (pm8001_dev->sas_device->linkrate < dev->port->linkrate) ?
			pm8001_dev->sas_device->linkrate : dev->port->linkrate;
	payload.phyid_portid =
		cpu_to_le32(((pm8001_dev->sas_device->port->id) & 0x0F) |
		((phy_id & 0x0F) << 4));
	payload.dtype_dlr_retry = cpu_to_le32((retryFlag & 0x01) |
		((linkrate & 0x0F) * 0x1000000) |
		((stp_sspsmp_sata & 0x03) * 0x10000000));
	payload.firstburstsize_ITNexusसमयout =
		cpu_to_le32(ITNT | (firstBurstSize * 0x10000));
	स_नकल(payload.sas_addr, pm8001_dev->sas_device->sas_addr,
		SAS_ADDR_SIZE);
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	वापस rc;
पूर्ण

/*
 * see comments on pm8001_mpi_reg_resp.
 */
पूर्णांक pm8001_chip_dereg_dev_req(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 device_id)
अणु
	काष्ठा dereg_dev_req payload;
	u32 opc = OPC_INB_DEREG_DEV_HANDLE;
	पूर्णांक ret;
	काष्ठा inbound_queue_table *circularQ;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	स_रखो(&payload, 0, माप(payload));
	payload.tag = cpu_to_le32(1);
	payload.device_id = cpu_to_le32(device_id);
	pm8001_dbg(pm8001_ha, MSG, "unregister device device_id = %d\n",
		   device_id);
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	वापस ret;
पूर्ण

/**
 * pm8001_chip_phy_ctl_req - support the local phy operation
 * @pm8001_ha: our hba card inक्रमmation.
 * @phyId: the phy id which we wanted to operate
 * @phy_op: the phy operation to request
 */
अटल पूर्णांक pm8001_chip_phy_ctl_req(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 phyId, u32 phy_op)
अणु
	काष्ठा local_phy_ctl_req payload;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक ret;
	u32 opc = OPC_INB_LOCAL_PHY_CONTROL;
	स_रखो(&payload, 0, माप(payload));
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(1);
	payload.phyop_phyid =
		cpu_to_le32(((phy_op & 0xff) << 8) | (phyId & 0x0F));
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	वापस ret;
पूर्ण

अटल u32 pm8001_chip_is_our_पूर्णांकerrupt(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
#अगर_घोषित PM8001_USE_MSIX
	वापस 1;
#अन्यथा
	u32 value;

	value = pm8001_cr32(pm8001_ha, 0, MSGU_ODR);
	अगर (value)
		वापस 1;
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * pm8001_chip_isr - PM8001 isr handler.
 * @pm8001_ha: our hba card inक्रमmation.
 * @vec: IRQ number
 */
अटल irqवापस_t
pm8001_chip_isr(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec)
अणु
	pm8001_chip_पूर्णांकerrupt_disable(pm8001_ha, vec);
	pm8001_dbg(pm8001_ha, DEVIO,
		   "irq vec %d, ODMR:0x%x\n",
		   vec, pm8001_cr32(pm8001_ha, 0, 0x30));
	process_oq(pm8001_ha, vec);
	pm8001_chip_पूर्णांकerrupt_enable(pm8001_ha, vec);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक send_task_पात(काष्ठा pm8001_hba_info *pm8001_ha, u32 opc,
	u32 dev_id, u8 flag, u32 task_tag, u32 cmd_tag)
अणु
	काष्ठा task_पात_req task_पात;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक ret;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	स_रखो(&task_पात, 0, माप(task_पात));
	अगर (ABORT_SINGLE == (flag & ABORT_MASK)) अणु
		task_पात.पात_all = 0;
		task_पात.device_id = cpu_to_le32(dev_id);
		task_पात.tag_to_पात = cpu_to_le32(task_tag);
		task_पात.tag = cpu_to_le32(cmd_tag);
	पूर्ण अन्यथा अगर (ABORT_ALL == (flag & ABORT_MASK)) अणु
		task_पात.पात_all = cpu_to_le32(1);
		task_पात.device_id = cpu_to_le32(dev_id);
		task_पात.tag = cpu_to_le32(cmd_tag);
	पूर्ण
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &task_पात,
			माप(task_पात), 0);
	वापस ret;
पूर्ण

/*
 * pm8001_chip_पात_task - SAS पात task when error or exception happened.
 */
पूर्णांक pm8001_chip_पात_task(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_device *pm8001_dev, u8 flag, u32 task_tag, u32 cmd_tag)
अणु
	u32 opc, device_id;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	pm8001_dbg(pm8001_ha, EH, "cmd_tag = %x, abort task tag = 0x%x\n",
		   cmd_tag, task_tag);
	अगर (pm8001_dev->dev_type == SAS_END_DEVICE)
		opc = OPC_INB_SSP_ABORT;
	अन्यथा अगर (pm8001_dev->dev_type == SAS_SATA_DEV)
		opc = OPC_INB_SATA_ABORT;
	अन्यथा
		opc = OPC_INB_SMP_ABORT;/* SMP */
	device_id = pm8001_dev->device_id;
	rc = send_task_पात(pm8001_ha, opc, device_id, flag,
		task_tag, cmd_tag);
	अगर (rc != TMF_RESP_FUNC_COMPLETE)
		pm8001_dbg(pm8001_ha, EH, "rc= %d\n", rc);
	वापस rc;
पूर्ण

/**
 * pm8001_chip_ssp_पंचांग_req - built the task management command.
 * @pm8001_ha: our hba card inक्रमmation.
 * @ccb: the ccb inक्रमmation.
 * @पंचांगf: task management function.
 */
पूर्णांक pm8001_chip_ssp_पंचांग_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb, काष्ठा pm8001_पंचांगf_task *पंचांगf)
अणु
	काष्ठा sas_task *task = ccb->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;
	u32 opc = OPC_INB_SSPINITMSTART;
	काष्ठा inbound_queue_table *circularQ;
	काष्ठा ssp_ini_पंचांग_start_req sspTMCmd;
	पूर्णांक ret;

	स_रखो(&sspTMCmd, 0, माप(sspTMCmd));
	sspTMCmd.device_id = cpu_to_le32(pm8001_dev->device_id);
	sspTMCmd.relate_tag = cpu_to_le32(पंचांगf->tag_of_task_to_be_managed);
	sspTMCmd.पंचांगf = cpu_to_le32(पंचांगf->पंचांगf);
	स_नकल(sspTMCmd.lun, task->ssp_task.LUN, 8);
	sspTMCmd.tag = cpu_to_le32(ccb->ccb_tag);
	अगर (pm8001_ha->chip_id != chip_8001)
		sspTMCmd.ds_ads_m = 0x08;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &sspTMCmd,
			माप(sspTMCmd), 0);
	वापस ret;
पूर्ण

पूर्णांक pm8001_chip_get_nvmd_req(काष्ठा pm8001_hba_info *pm8001_ha,
	व्योम *payload)
अणु
	u32 opc = OPC_INB_GET_NVMD_DATA;
	u32 nvmd_type;
	पूर्णांक rc;
	u32 tag;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा inbound_queue_table *circularQ;
	काष्ठा get_nvm_data_req nvmd_req;
	काष्ठा fw_control_ex *fw_control_context;
	काष्ठा pm8001_ioctl_payload *ioctl_payload = payload;

	nvmd_type = ioctl_payload->minor_function;
	fw_control_context = kzalloc(माप(काष्ठा fw_control_ex), GFP_KERNEL);
	अगर (!fw_control_context)
		वापस -ENOMEM;
	fw_control_context->usrAddr = (u8 *)ioctl_payload->func_specअगरic;
	fw_control_context->len = ioctl_payload->rd_length;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	स_रखो(&nvmd_req, 0, माप(nvmd_req));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc) अणु
		kमुक्त(fw_control_context);
		वापस rc;
	पूर्ण
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->ccb_tag = tag;
	ccb->fw_control_context = fw_control_context;
	nvmd_req.tag = cpu_to_le32(tag);

	चयन (nvmd_type) अणु
	हाल TWI_DEVICE: अणु
		u32 twi_addr, twi_page_size;
		twi_addr = 0xa8;
		twi_page_size = 2;

		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | twi_addr << 16 |
			twi_page_size << 8 | TWI_DEVICE);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->rd_length);
		nvmd_req.resp_addr_hi =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	पूर्ण
	हाल C_SEEPROM: अणु
		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | C_SEEPROM);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->rd_length);
		nvmd_req.resp_addr_hi =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	पूर्ण
	हाल VPD_FLASH: अणु
		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | VPD_FLASH);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->rd_length);
		nvmd_req.resp_addr_hi =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	पूर्ण
	हाल EXPAN_ROM: अणु
		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | EXPAN_ROM);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->rd_length);
		nvmd_req.resp_addr_hi =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	पूर्ण
	हाल IOP_RDUMP: अणु
		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | IOP_RDUMP);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->rd_length);
		nvmd_req.vpd_offset = cpu_to_le32(ioctl_payload->offset);
		nvmd_req.resp_addr_hi =
		cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &nvmd_req,
			माप(nvmd_req), 0);
	अगर (rc) अणु
		kमुक्त(fw_control_context);
		pm8001_tag_मुक्त(pm8001_ha, tag);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक pm8001_chip_set_nvmd_req(काष्ठा pm8001_hba_info *pm8001_ha,
	व्योम *payload)
अणु
	u32 opc = OPC_INB_SET_NVMD_DATA;
	u32 nvmd_type;
	पूर्णांक rc;
	u32 tag;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा inbound_queue_table *circularQ;
	काष्ठा set_nvm_data_req nvmd_req;
	काष्ठा fw_control_ex *fw_control_context;
	काष्ठा pm8001_ioctl_payload *ioctl_payload = payload;

	nvmd_type = ioctl_payload->minor_function;
	fw_control_context = kzalloc(माप(काष्ठा fw_control_ex), GFP_KERNEL);
	अगर (!fw_control_context)
		वापस -ENOMEM;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	स_नकल(pm8001_ha->memoryMap.region[NVMD].virt_ptr,
		&ioctl_payload->func_specअगरic,
		ioctl_payload->wr_length);
	स_रखो(&nvmd_req, 0, माप(nvmd_req));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc) अणु
		kमुक्त(fw_control_context);
		वापस -EBUSY;
	पूर्ण
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->fw_control_context = fw_control_context;
	ccb->ccb_tag = tag;
	nvmd_req.tag = cpu_to_le32(tag);
	चयन (nvmd_type) अणु
	हाल TWI_DEVICE: अणु
		u32 twi_addr, twi_page_size;
		twi_addr = 0xa8;
		twi_page_size = 2;
		nvmd_req.reserved[0] = cpu_to_le32(0xFEDCBA98);
		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | twi_addr << 16 |
			twi_page_size << 8 | TWI_DEVICE);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->wr_length);
		nvmd_req.resp_addr_hi =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	पूर्ण
	हाल C_SEEPROM:
		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | C_SEEPROM);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->wr_length);
		nvmd_req.reserved[0] = cpu_to_le32(0xFEDCBA98);
		nvmd_req.resp_addr_hi =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	हाल VPD_FLASH:
		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | VPD_FLASH);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->wr_length);
		nvmd_req.reserved[0] = cpu_to_le32(0xFEDCBA98);
		nvmd_req.resp_addr_hi =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	हाल EXPAN_ROM:
		nvmd_req.len_ir_vpdd = cpu_to_le32(IPMode | EXPAN_ROM);
		nvmd_req.resp_len = cpu_to_le32(ioctl_payload->wr_length);
		nvmd_req.reserved[0] = cpu_to_le32(0xFEDCBA98);
		nvmd_req.resp_addr_hi =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_hi);
		nvmd_req.resp_addr_lo =
		    cpu_to_le32(pm8001_ha->memoryMap.region[NVMD].phys_addr_lo);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &nvmd_req,
			माप(nvmd_req), 0);
	अगर (rc) अणु
		kमुक्त(fw_control_context);
		pm8001_tag_मुक्त(pm8001_ha, tag);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * pm8001_chip_fw_flash_update_build - support the firmware update operation
 * @pm8001_ha: our hba card inक्रमmation.
 * @fw_flash_updata_info: firmware flash update param
 * @tag: Tag to apply to the payload
 */
पूर्णांक
pm8001_chip_fw_flash_update_build(काष्ठा pm8001_hba_info *pm8001_ha,
	व्योम *fw_flash_updata_info, u32 tag)
अणु
	काष्ठा fw_flash_Update_req payload;
	काष्ठा fw_flash_updata_info *info;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक ret;
	u32 opc = OPC_INB_FW_FLASH_UPDATE;

	स_रखो(&payload, 0, माप(काष्ठा fw_flash_Update_req));
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	info = fw_flash_updata_info;
	payload.tag = cpu_to_le32(tag);
	payload.cur_image_len = cpu_to_le32(info->cur_image_len);
	payload.cur_image_offset = cpu_to_le32(info->cur_image_offset);
	payload.total_image_len = cpu_to_le32(info->total_image_len);
	payload.len = info->sgl.im_len.len ;
	payload.sgl_addr_lo =
		cpu_to_le32(lower_32_bits(le64_to_cpu(info->sgl.addr)));
	payload.sgl_addr_hi =
		cpu_to_le32(upper_32_bits(le64_to_cpu(info->sgl.addr)));
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	वापस ret;
पूर्ण

पूर्णांक
pm8001_chip_fw_flash_update_req(काष्ठा pm8001_hba_info *pm8001_ha,
	व्योम *payload)
अणु
	काष्ठा fw_flash_updata_info flash_update_info;
	काष्ठा fw_control_info *fw_control;
	काष्ठा fw_control_ex *fw_control_context;
	पूर्णांक rc;
	u32 tag;
	काष्ठा pm8001_ccb_info *ccb;
	व्योम *buffer = pm8001_ha->memoryMap.region[FW_FLASH].virt_ptr;
	dma_addr_t phys_addr = pm8001_ha->memoryMap.region[FW_FLASH].phys_addr;
	काष्ठा pm8001_ioctl_payload *ioctl_payload = payload;

	fw_control_context = kzalloc(माप(काष्ठा fw_control_ex), GFP_KERNEL);
	अगर (!fw_control_context)
		वापस -ENOMEM;
	fw_control = (काष्ठा fw_control_info *)&ioctl_payload->func_specअगरic;
	pm8001_dbg(pm8001_ha, DEVIO,
		   "dma fw_control context input length :%x\n",
		   fw_control->len);
	स_नकल(buffer, fw_control->buffer, fw_control->len);
	flash_update_info.sgl.addr = cpu_to_le64(phys_addr);
	flash_update_info.sgl.im_len.len = cpu_to_le32(fw_control->len);
	flash_update_info.sgl.im_len.e = 0;
	flash_update_info.cur_image_offset = fw_control->offset;
	flash_update_info.cur_image_len = fw_control->len;
	flash_update_info.total_image_len = fw_control->size;
	fw_control_context->fw_control = fw_control;
	fw_control_context->virtAddr = buffer;
	fw_control_context->phys_addr = phys_addr;
	fw_control_context->len = fw_control->len;
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc) अणु
		kमुक्त(fw_control_context);
		वापस -EBUSY;
	पूर्ण
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->fw_control_context = fw_control_context;
	ccb->ccb_tag = tag;
	rc = pm8001_chip_fw_flash_update_build(pm8001_ha, &flash_update_info,
		tag);
	वापस rc;
पूर्ण

sमाप_प्रकार
pm8001_get_gsm_dump(काष्ठा device *cdev, u32 length, अक्षर *buf)
अणु
	u32 value, rem, offset = 0, bar = 0;
	u32 index, work_offset, dw_length;
	u32 shअगरt_value, gsm_base, gsm_dump_offset;
	अक्षर *direct_data;
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	direct_data = buf;
	gsm_dump_offset = pm8001_ha->fatal_क्रमensic_shअगरt_offset;

	/* check max is 1 Mbytes */
	अगर ((length > 0x100000) || (gsm_dump_offset & 3) ||
		((gsm_dump_offset + length) > 0x1000000))
			वापस -EINVAL;

	अगर (pm8001_ha->chip_id == chip_8001)
		bar = 2;
	अन्यथा
		bar = 1;

	work_offset = gsm_dump_offset & 0xFFFF0000;
	offset = gsm_dump_offset & 0x0000FFFF;
	gsm_dump_offset = work_offset;
	/* adjust length to dword boundary */
	rem = length & 3;
	dw_length = length >> 2;

	क्रम (index = 0; index < dw_length; index++) अणु
		अगर ((work_offset + offset) & 0xFFFF0000) अणु
			अगर (pm8001_ha->chip_id == chip_8001)
				shअगरt_value = ((gsm_dump_offset + offset) &
						SHIFT_REG_64K_MASK);
			अन्यथा
				shअगरt_value = (((gsm_dump_offset + offset) &
						SHIFT_REG_64K_MASK) >>
						SHIFT_REG_BIT_SHIFT);

			अगर (pm8001_ha->chip_id == chip_8001) अणु
				gsm_base = GSM_BASE;
				अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha,
						(gsm_base + shअगरt_value)))
					वापस -EIO;
			पूर्ण अन्यथा अणु
				gsm_base = 0;
				अगर (-1 == pm80xx_bar4_shअगरt(pm8001_ha,
						(gsm_base + shअगरt_value)))
					वापस -EIO;
			पूर्ण
			gsm_dump_offset = (gsm_dump_offset + offset) &
						0xFFFF0000;
			work_offset = 0;
			offset = offset & 0x0000FFFF;
		पूर्ण
		value = pm8001_cr32(pm8001_ha, bar, (work_offset + offset) &
						0x0000FFFF);
		direct_data += प्र_लिखो(direct_data, "%08x ", value);
		offset += 4;
	पूर्ण
	अगर (rem != 0) अणु
		value = pm8001_cr32(pm8001_ha, bar, (work_offset + offset) &
						0x0000FFFF);
		/* xfr क्रम non_dw */
		direct_data += प्र_लिखो(direct_data, "%08x ", value);
	पूर्ण
	/* Shअगरt back to BAR4 original address */
	अगर (-1 == pm8001_bar4_shअगरt(pm8001_ha, 0))
			वापस -EIO;
	pm8001_ha->fatal_क्रमensic_shअगरt_offset += 1024;

	अगर (pm8001_ha->fatal_क्रमensic_shअगरt_offset >= 0x100000)
		pm8001_ha->fatal_क्रमensic_shअगरt_offset = 0;
	वापस direct_data - buf;
पूर्ण

पूर्णांक
pm8001_chip_set_dev_state_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_device *pm8001_dev, u32 state)
अणु
	काष्ठा set_dev_state_req payload;
	काष्ठा inbound_queue_table *circularQ;
	काष्ठा pm8001_ccb_info *ccb;
	पूर्णांक rc;
	u32 tag;
	u32 opc = OPC_INB_SET_DEVICE_STATE;
	स_रखो(&payload, 0, माप(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		वापस -1;
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->ccb_tag = tag;
	ccb->device = pm8001_dev;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	payload.device_id = cpu_to_le32(pm8001_dev->device_id);
	payload.nds = cpu_to_le32(state);
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	वापस rc;

पूर्ण

अटल पूर्णांक
pm8001_chip_sas_re_initialization(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा sas_re_initialization_req payload;
	काष्ठा inbound_queue_table *circularQ;
	काष्ठा pm8001_ccb_info *ccb;
	पूर्णांक rc;
	u32 tag;
	u32 opc = OPC_INB_SAS_RE_INITIALIZE;
	स_रखो(&payload, 0, माप(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		वापस -ENOMEM;
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->ccb_tag = tag;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	payload.SSAHOLT = cpu_to_le32(0xd << 25);
	payload.sata_hol_पंचांगo = cpu_to_le32(80);
	payload.खोलो_reject_cmdretries_data_retries = cpu_to_le32(0xff00ff);
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	अगर (rc)
		pm8001_tag_मुक्त(pm8001_ha, tag);
	वापस rc;

पूर्ण

स्थिर काष्ठा pm8001_dispatch pm8001_8001_dispatch = अणु
	.name			= "pmc8001",
	.chip_init		= pm8001_chip_init,
	.chip_soft_rst		= pm8001_chip_soft_rst,
	.chip_rst		= pm8001_hw_chip_rst,
	.chip_iounmap		= pm8001_chip_iounmap,
	.isr			= pm8001_chip_isr,
	.is_our_पूर्णांकerrupt	= pm8001_chip_is_our_पूर्णांकerrupt,
	.isr_process_oq		= process_oq,
	.पूर्णांकerrupt_enable 	= pm8001_chip_पूर्णांकerrupt_enable,
	.पूर्णांकerrupt_disable	= pm8001_chip_पूर्णांकerrupt_disable,
	.make_prd		= pm8001_chip_make_sg,
	.smp_req		= pm8001_chip_smp_req,
	.ssp_io_req		= pm8001_chip_ssp_io_req,
	.sata_req		= pm8001_chip_sata_req,
	.phy_start_req		= pm8001_chip_phy_start_req,
	.phy_stop_req		= pm8001_chip_phy_stop_req,
	.reg_dev_req		= pm8001_chip_reg_dev_req,
	.dereg_dev_req		= pm8001_chip_dereg_dev_req,
	.phy_ctl_req		= pm8001_chip_phy_ctl_req,
	.task_पात		= pm8001_chip_पात_task,
	.ssp_पंचांग_req		= pm8001_chip_ssp_पंचांग_req,
	.get_nvmd_req		= pm8001_chip_get_nvmd_req,
	.set_nvmd_req		= pm8001_chip_set_nvmd_req,
	.fw_flash_update_req	= pm8001_chip_fw_flash_update_req,
	.set_dev_state_req	= pm8001_chip_set_dev_state_req,
	.sas_re_init_req	= pm8001_chip_sas_re_initialization,
	.fatal_errors		= pm80xx_fatal_errors,
पूर्ण;
