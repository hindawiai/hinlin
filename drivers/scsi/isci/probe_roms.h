<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#अगर_अघोषित _ISCI_PROBE_ROMS_H_
#घोषणा _ISCI_PROBE_ROMS_H_

#अगर_घोषित __KERNEL__
#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/efi.h>
#समावेश "isci.h"

#घोषणा SCIC_SDS_PARM_NO_SPEED   0

/* generation 1 (i.e. 1.5 Gb/s) */
#घोषणा SCIC_SDS_PARM_GEN1_SPEED 1

/* generation 2 (i.e. 3.0 Gb/s) */
#घोषणा SCIC_SDS_PARM_GEN2_SPEED 2

/* generation 3 (i.e. 6.0 Gb/s) */
#घोषणा SCIC_SDS_PARM_GEN3_SPEED 3
#घोषणा SCIC_SDS_PARM_MAX_SPEED SCIC_SDS_PARM_GEN3_SPEED

/* parameters that can be set by module parameters */
काष्ठा sci_user_parameters अणु
	काष्ठा sci_phy_user_params अणु
		/**
		 * This field specअगरies the NOTIFY (ENABLE SPIN UP) primitive
		 * insertion frequency क्रम this phy index.
		 */
		u32 notअगरy_enable_spin_up_insertion_frequency;

		/**
		 * This method specअगरies the number of transmitted DWORDs within which
		 * to transmit a single ALIGN primitive.  This value applies regardless
		 * of what type of device is attached or connection state.  A value of
		 * 0 indicates that no ALIGN primitives will be inserted.
		 */
		u16 align_insertion_frequency;

		/**
		 * This method specअगरies the number of transmitted DWORDs within which
		 * to transmit 2 ALIGN primitives.  This applies क्रम SAS connections
		 * only.  A minimum value of 3 is required क्रम this field.
		 */
		u16 in_connection_align_insertion_frequency;

		/**
		 * This field indicates the maximum speed generation to be utilized
		 * by phys in the supplied port.
		 * - A value of 1 indicates generation 1 (i.e. 1.5 Gb/s).
		 * - A value of 2 indicates generation 2 (i.e. 3.0 Gb/s).
		 * - A value of 3 indicates generation 3 (i.e. 6.0 Gb/s).
		 */
		u8 max_speed_generation;

	पूर्ण phys[SCI_MAX_PHYS];

	/**
	 * This field specअगरies the maximum number of direct attached devices
	 * that can have घातer supplied to them simultaneously.
	 */
	u8 max_concurr_spinup;

	/**
	 * This field specअगरies the number of seconds to allow a phy to consume
	 * घातer beक्रमe yielding to another phy.
	 *
	 */
	u8 phy_spin_up_delay_पूर्णांकerval;

	/**
	 * These समयr values specअगरies how दीर्घ a link will reमुख्य खोलो with no
	 * activity in increments of a microsecond, it can be in increments of
	 * 100 microseconds अगर the upper most bit is set.
	 *
	 */
	u16 stp_inactivity_समयout;
	u16 ssp_inactivity_समयout;

	/**
	 * These समयr values specअगरies how दीर्घ a link will reमुख्य खोलो in increments
	 * of 100 microseconds.
	 *
	 */
	u16 stp_max_occupancy_समयout;
	u16 ssp_max_occupancy_समयout;

	/**
	 * This समयr value specअगरies how दीर्घ a link will reमुख्य खोलो with no
	 * outbound traffic in increments of a microsecond.
	 *
	 */
	u8 no_outbound_task_समयout;

पूर्ण;

#घोषणा SCIC_SDS_PARM_PHY_MASK_MIN 0x0
#घोषणा SCIC_SDS_PARM_PHY_MASK_MAX 0xF
#घोषणा MAX_CONCURRENT_DEVICE_SPIN_UP_COUNT 4

काष्ठा sci_oem_params;
पूर्णांक sci_oem_parameters_validate(काष्ठा sci_oem_params *oem, u8 version);

काष्ठा isci_orom;
काष्ठा isci_orom *isci_request_oprom(काष्ठा pci_dev *pdev);
काष्ठा isci_orom *isci_request_firmware(काष्ठा pci_dev *pdev, स्थिर काष्ठा firmware *fw);
काष्ठा isci_orom *isci_get_efi_var(काष्ठा pci_dev *pdev);

काष्ठा isci_oem_hdr अणु
	u8 sig[4];
	u8 rev_major;
	u8 rev_minor;
	u16 len;
	u8 checksum;
	u8 reserved1;
	u16 reserved2;
पूर्ण __attribute__ ((packed));

#अन्यथा
#घोषणा SCI_MAX_PORTS 4
#घोषणा SCI_MAX_PHYS 4
#घोषणा SCI_MAX_CONTROLLERS 2
#पूर्ण_अगर

#घोषणा ISCI_FW_NAME		"isci/isci_firmware.bin"

#घोषणा ROMSIGNATURE		0xaa55

#घोषणा ISCI_OEM_SIG		"$OEM"
#घोषणा ISCI_OEM_SIG_SIZE	4
#घोषणा ISCI_ROM_SIG		"ISCUOEMB"
#घोषणा ISCI_ROM_SIG_SIZE	8

#घोषणा ISCI_EFI_VENDOR_GUID	\
	EFI_GUID(0x193dfefa, 0xa445, 0x4302, 0x99, 0xd8, 0xef, 0x3a, 0xad, \
			0x1a, 0x04, 0xc6)
#घोषणा ISCI_EFI_VAR_NAME	"RstScuO"

#घोषणा ISCI_ROM_VER_1_0	0x10
#घोषणा ISCI_ROM_VER_1_1	0x11
#घोषणा ISCI_ROM_VER_1_3	0x13
#घोषणा ISCI_ROM_VER_LATEST	ISCI_ROM_VER_1_3

/* Allowed PORT configuration modes APC Automatic PORT configuration mode is
 * defined by the OEM configuration parameters providing no PHY_MASK parameters
 * क्रम any PORT. i.e. There are no phys asचिन्हित to any of the ports at start.
 * MPC Manual PORT configuration mode is defined by the OEM configuration
 * parameters providing a PHY_MASK value क्रम any PORT.  It is assumed that any
 * PORT with no PHY_MASK is an invalid port and not all PHYs must be asचिन्हित.
 * A PORT_PHY mask that assigns just a single PHY to a port and no other PHYs
 * being asचिन्हित is sufficient to declare manual PORT configuration.
 */
क्रमागत sci_port_configuration_mode अणु
	SCIC_PORT_MANUAL_CONFIGURATION_MODE = 0,
	SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE = 1
पूर्ण;

काष्ठा sci_bios_oem_param_block_hdr अणु
	uपूर्णांक8_t signature[ISCI_ROM_SIG_SIZE];
	uपूर्णांक16_t total_block_length;
	uपूर्णांक8_t hdr_length;
	uपूर्णांक8_t version;
	uपूर्णांक8_t preboot_source;
	uपूर्णांक8_t num_elements;
	uपूर्णांक16_t element_length;
	uपूर्णांक8_t reserved[8];
पूर्ण __attribute__ ((packed));

काष्ठा sci_oem_params अणु
	काष्ठा अणु
		uपूर्णांक8_t mode_type;
		uपूर्णांक8_t max_concurr_spin_up;
		/*
		 * This bitfield indicates the OEM's desired शेष Tx
		 * Spपढ़ो Spectrum Clocking (SSC) settings क्रम SATA and SAS.
		 * NOTE: Default SSC Modulation Frequency is 31.5KHz.
		 */
		जोड़ अणु
			काष्ठा अणु
			/*
			 * NOTE: Max spपढ़ो क्रम SATA is +0 / -5000 PPM.
			 * Down-spपढ़ोing SSC (only method allowed क्रम SATA):
			 *  SATA SSC Tx Disabled                    = 0x0
			 *  SATA SSC Tx at +0 / -1419 PPM Spपढ़ो    = 0x2
			 *  SATA SSC Tx at +0 / -2129 PPM Spपढ़ो    = 0x3
			 *  SATA SSC Tx at +0 / -4257 PPM Spपढ़ो    = 0x6
			 *  SATA SSC Tx at +0 / -4967 PPM Spपढ़ो    = 0x7
			 */
				uपूर्णांक8_t ssc_sata_tx_spपढ़ो_level:4;
			/*
			 * SAS SSC Tx Disabled                     = 0x0
			 *
			 * NOTE: Max spपढ़ो क्रम SAS करोwn-spपढ़ोing +0 /
			 *	 -2300 PPM
			 * Down-spपढ़ोing SSC:
			 *  SAS SSC Tx at +0 / -1419 PPM Spपढ़ो     = 0x2
			 *  SAS SSC Tx at +0 / -2129 PPM Spपढ़ो     = 0x3
			 *
			 * NOTE: Max spपढ़ो क्रम SAS center-spपढ़ोing +2300 /
			 *	 -2300 PPM
			 * Center-spपढ़ोing SSC:
			 *  SAS SSC Tx at +1064 / -1064 PPM Spपढ़ो  = 0x3
			 *  SAS SSC Tx at +2129 / -2129 PPM Spपढ़ो  = 0x6
			 */
				uपूर्णांक8_t ssc_sas_tx_spपढ़ो_level:3;
			/*
			 * NOTE: Refer to the SSC section of the SAS 2.x
			 * Specअगरication क्रम proper setting of this field.
			 * For standard SAS Initiator SAS PHY operation it
			 * should be 0 क्रम Down-spपढ़ोing.
			 * SAS SSC Tx spपढ़ो type:
			 *  Down-spपढ़ोing SSC      = 0
			 *  Center-spपढ़ोing SSC    = 1
			 */
				uपूर्णांक8_t ssc_sas_tx_type:1;
			पूर्ण;
			uपूर्णांक8_t करो_enable_ssc;
		पूर्ण;
		/*
		 * This field indicates length of the SAS/SATA cable between
		 * host and device.
		 * This field is used make relationship between analog
		 * parameters of the phy in the silicon and length of the cable.
		 * Supported cable attenuation levels:
		 * "short"- up to 3m, "medium"-3m to 6m, and "long"- more than
		 * 6m.
		 *
		 * This is bit mask field:
		 *
		 * BIT:      (MSB) 7     6     5     4
		 * ASSIGNMENT:   <phy3><phy2><phy1><phy0>  - Medium cable
		 *                                           length assignment
		 * BIT:            3     2     1     0  (LSB)
		 * ASSIGNMENT:   <phy3><phy2><phy1><phy0>  - Long cable length
		 *                                           assignment
		 *
		 * BITS 7-4 are set when the cable length is asचिन्हित to medium
		 * BITS 3-0 are set when the cable length is asचिन्हित to दीर्घ
		 *
		 * The BIT positions are clear when the cable length is
		 * asचिन्हित to लघु.
		 *
		 * Setting the bits क्रम both दीर्घ and medium cable length is
		 * undefined.
		 *
		 * A value of 0x84 would assign
		 *    phy3 - medium
		 *    phy2 - दीर्घ
		 *    phy1 - लघु
		 *    phy0 - लघु
		 */
		uपूर्णांक8_t cable_selection_mask;
	पूर्ण controller;

	काष्ठा अणु
		uपूर्णांक8_t phy_mask;
	पूर्ण ports[SCI_MAX_PORTS];

	काष्ठा sci_phy_oem_params अणु
		काष्ठा अणु
			uपूर्णांक32_t high;
			uपूर्णांक32_t low;
		पूर्ण sas_address;

		uपूर्णांक32_t afe_tx_amp_control0;
		uपूर्णांक32_t afe_tx_amp_control1;
		uपूर्णांक32_t afe_tx_amp_control2;
		uपूर्णांक32_t afe_tx_amp_control3;
	पूर्ण phys[SCI_MAX_PHYS];
पूर्ण __attribute__ ((packed));

काष्ठा isci_orom अणु
	काष्ठा sci_bios_oem_param_block_hdr hdr;
	काष्ठा sci_oem_params ctrl[SCI_MAX_CONTROLLERS];
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर
