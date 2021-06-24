<शैली गुरु>
/*  linux/drivers/scsi/esas2r/atioctl.h
 *      ATTO IOCTL Handling
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  NO WARRANTY
 *  THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 *  CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 *  LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 *  MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 *  solely responsible क्रम determining the appropriateness of using and
 *  distributing the Program and assumes all risks associated with its
 *  exercise of rights under this Agreement, including but not limited to
 *  the risks and costs of program errors, damage to or loss of data,
 *  programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 *  DISCLAIMER OF LIABILITY
 *  NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 *  सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 *  HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश "atvda.h"

#अगर_अघोषित ATIOCTL_H
#घोषणा ATIOCTL_H

#घोषणा EXPRESS_IOCTL_SIGNATURE        "Express"
#घोषणा EXPRESS_IOCTL_SIGNATURE_SIZE   8

/* काष्ठाure definitions क्रम IOCTls */

काष्ठा __packed atto_express_ioctl_header अणु
	u8 signature[EXPRESS_IOCTL_SIGNATURE_SIZE];
	u8 वापस_code;

#घोषणा IOCTL_SUCCESS               0
#घोषणा IOCTL_ERR_INVCMD          101
#घोषणा IOCTL_INIT_FAILED         102
#घोषणा IOCTL_NOT_IMPLEMENTED     103
#घोषणा IOCTL_BAD_CHANNEL         104
#घोषणा IOCTL_TARGET_OVERRUN      105
#घोषणा IOCTL_TARGET_NOT_ENABLED  106
#घोषणा IOCTL_BAD_FLASH_IMGTYPE   107
#घोषणा IOCTL_OUT_OF_RESOURCES    108
#घोषणा IOCTL_GENERAL_ERROR       109
#घोषणा IOCTL_INVALID_PARAM       110

	u8 channel;
	u8 retries;
	u8 pad[5];
पूर्ण;

/*
 * NOTE - अगर channel == 0xFF, the request is
 * handled on the adapter it came in on.
 */
#घोषणा MAX_NODE_NAMES  256

काष्ठा __packed atto_firmware_rw_request अणु
	u8 function;
	#घोषणा FUNC_FW_DOWNLOAD        0x09
	#घोषणा FUNC_FW_UPLOAD          0x12

	u8 img_type;
	#घोषणा FW_IMG_FW               0x01
	#घोषणा FW_IMG_BIOS             0x02
	#घोषणा FW_IMG_NVR              0x03
	#घोषणा FW_IMG_RAW              0x04
	#घोषणा FW_IMG_FM_API           0x05
	#घोषणा FW_IMG_FS_API           0x06

	u8 pad[2];
	u32 img_offset;
	u32 img_size;
	u8 image[0x80000];
पूर्ण;

काष्ठा __packed atto_param_rw_request अणु
	u16 code;
	अक्षर data_buffer[512];
पूर्ण;

#घोषणा MAX_CHANNEL 256

काष्ठा __packed atto_channel_list अणु
	u32 num_channels;
	u8 channel[MAX_CHANNEL];
पूर्ण;

काष्ठा __packed atto_channel_info अणु
	u8 major_rev;
	u8 minor_rev;
	u8 IRQ;
	u8 revision_id;
	u8 pci_bus;
	u8 pci_dev_func;
	u8 core_rev;
	u8 host_no;
	u16 device_id;
	u16 venकरोr_id;
	u16 ven_dev_id;
	u8 pad[3];
	u32 hbaapi_rev;
पूर्ण;

/*
 * CSMI control codes
 * class independent
 */
#घोषणा CSMI_CC_GET_DRVR_INFO        1
#घोषणा CSMI_CC_GET_CNTLR_CFG        2
#घोषणा CSMI_CC_GET_CNTLR_STS        3
#घोषणा CSMI_CC_FW_DOWNLOAD          4

/* RAID class */
#घोषणा CSMI_CC_GET_RAID_INFO        10
#घोषणा CSMI_CC_GET_RAID_CFG         11

/* HBA class */
#घोषणा CSMI_CC_GET_PHY_INFO         20
#घोषणा CSMI_CC_SET_PHY_INFO         21
#घोषणा CSMI_CC_GET_LINK_ERRORS      22
#घोषणा CSMI_CC_SMP_PASSTHRU         23
#घोषणा CSMI_CC_SSP_PASSTHRU         24
#घोषणा CSMI_CC_STP_PASSTHRU         25
#घोषणा CSMI_CC_GET_SATA_SIG         26
#घोषणा CSMI_CC_GET_SCSI_ADDR        27
#घोषणा CSMI_CC_GET_DEV_ADDR         28
#घोषणा CSMI_CC_TASK_MGT             29
#घोषणा CSMI_CC_GET_CONN_INFO        30

/* PHY class */
#घोषणा CSMI_CC_PHY_CTRL             60

/*
 * CSMI status codes
 * class independent
 */
#घोषणा CSMI_STS_SUCCESS             0
#घोषणा CSMI_STS_FAILED              1
#घोषणा CSMI_STS_BAD_CTRL_CODE       2
#घोषणा CSMI_STS_INV_PARAM           3
#घोषणा CSMI_STS_WRITE_ATTEMPTED     4

/* RAID class */
#घोषणा CSMI_STS_INV_RAID_SET        1000

/* HBA class */
#घोषणा CSMI_STS_PHY_CHANGED         CSMI_STS_SUCCESS
#घोषणा CSMI_STS_PHY_UNCHANGEABLE    2000
#घोषणा CSMI_STS_INV_LINK_RATE       2001
#घोषणा CSMI_STS_INV_PHY             2002
#घोषणा CSMI_STS_INV_PHY_FOR_PORT    2003
#घोषणा CSMI_STS_PHY_UNSELECTABLE    2004
#घोषणा CSMI_STS_SELECT_PHY_OR_PORT  2005
#घोषणा CSMI_STS_INV_PORT            2006
#घोषणा CSMI_STS_PORT_UNSELECTABLE   2007
#घोषणा CSMI_STS_CONNECTION_FAILED   2008
#घोषणा CSMI_STS_NO_SATA_DEV         2009
#घोषणा CSMI_STS_NO_SATA_SIGNATURE   2010
#घोषणा CSMI_STS_SCSI_EMULATION      2011
#घोषणा CSMI_STS_NOT_AN_END_DEV      2012
#घोषणा CSMI_STS_NO_SCSI_ADDR        2013
#घोषणा CSMI_STS_NO_DEV_ADDR         2014

/* CSMI class independent काष्ठाures */
काष्ठा atto_csmi_get_driver_info अणु
	अक्षर name[81];
	अक्षर description[81];
	u16 major_rev;
	u16 minor_rev;
	u16 build_rev;
	u16 release_rev;
	u16 csmi_major_rev;
	u16 csmi_minor_rev;
	#घोषणा CSMI_MAJOR_REV_0_81      0
	#घोषणा CSMI_MINOR_REV_0_81      81

	#घोषणा CSMI_MAJOR_REV           CSMI_MAJOR_REV_0_81
	#घोषणा CSMI_MINOR_REV           CSMI_MINOR_REV_0_81
पूर्ण;

काष्ठा atto_csmi_get_pci_bus_addr अणु
	u8 bus_num;
	u8 device_num;
	u8 function_num;
	u8 reserved;
पूर्ण;

काष्ठा atto_csmi_get_cntlr_cfg अणु
	u32 base_io_addr;

	काष्ठा अणु
		u32 base_memaddr_lo;
		u32 base_memaddr_hi;
	पूर्ण;

	u32 board_id;
	u16 slot_num;
	#घोषणा CSMI_SLOT_NUM_UNKNOWN    0xFFFF

	u8 cntlr_class;
	#घोषणा CSMI_CNTLR_CLASS_HBA     5

	u8 io_bus_type;
	#घोषणा CSMI_BUS_TYPE_PCI        3
	#घोषणा CSMI_BUS_TYPE_PCMCIA     4

	जोड़ अणु
		काष्ठा atto_csmi_get_pci_bus_addr pci_addr;
		u8 reserved[32];
	पूर्ण;

	अक्षर serial_num[81];
	u16 major_rev;
	u16 minor_rev;
	u16 build_rev;
	u16 release_rev;
	u16 bios_major_rev;
	u16 bios_minor_rev;
	u16 bios_build_rev;
	u16 bios_release_rev;
	u32 cntlr_flags;
	#घोषणा CSMI_CNTLRF_SAS_HBA      0x00000001
	#घोषणा CSMI_CNTLRF_SAS_RAID     0x00000002
	#घोषणा CSMI_CNTLRF_SATA_HBA     0x00000004
	#घोषणा CSMI_CNTLRF_SATA_RAID    0x00000008
	#घोषणा CSMI_CNTLRF_FWD_SUPPORT  0x00010000
	#घोषणा CSMI_CNTLRF_FWD_ONLINE   0x00020000
	#घोषणा CSMI_CNTLRF_FWD_SRESET   0x00040000
	#घोषणा CSMI_CNTLRF_FWD_HRESET   0x00080000
	#घोषणा CSMI_CNTLRF_FWD_RROM     0x00100000

	u16 rrom_major_rev;
	u16 rrom_minor_rev;
	u16 rrom_build_rev;
	u16 rrom_release_rev;
	u16 rrom_biosmajor_rev;
	u16 rrom_biosminor_rev;
	u16 rrom_biosbuild_rev;
	u16 rrom_biosrelease_rev;
	u8 reserved2[7];
पूर्ण;

काष्ठा atto_csmi_get_cntlr_sts अणु
	u32 status;
	#घोषणा CSMI_CNTLR_STS_GOOD          1
	#घोषणा CSMI_CNTLR_STS_FAILED        2
	#घोषणा CSMI_CNTLR_STS_OFFLINE       3
	#घोषणा CSMI_CNTLR_STS_POWEROFF      4

	u32 offline_reason;
	#घोषणा CSMI_OFFLINE_NO_REASON       0
	#घोषणा CSMI_OFFLINE_INITIALIZING    1
	#घोषणा CSMI_OFFLINE_BUS_DEGRADED    2
	#घोषणा CSMI_OFFLINE_BUS_FAILURE     3

	u8 reserved[28];
पूर्ण;

काष्ठा atto_csmi_fw_करोwnload अणु
	u32 buffer_len;
	u32 करोwnload_flags;
	#घोषणा CSMI_FWDF_VALIDATE       0x00000001
	#घोषणा CSMI_FWDF_SOFT_RESET     0x00000002
	#घोषणा CSMI_FWDF_HARD_RESET     0x00000004

	u8 reserved[32];
	u16 status;
	#घोषणा CSMI_FWD_STS_SUCCESS     0
	#घोषणा CSMI_FWD_STS_FAILED      1
	#घोषणा CSMI_FWD_STS_USING_RROM  2
	#घोषणा CSMI_FWD_STS_REJECT      3
	#घोषणा CSMI_FWD_STS_DOWNREV     4

	u16 severity;
	#घोषणा CSMI_FWD_SEV_INFO        0
	#घोषणा CSMI_FWD_SEV_WARNING     1
	#घोषणा CSMI_FWD_SEV_ERROR       2
	#घोषणा CSMI_FWD_SEV_FATAL       3

पूर्ण;

/* CSMI RAID class काष्ठाures */
काष्ठा atto_csmi_get_raid_info अणु
	u32 num_raid_sets;
	u32 max_drivesper_set;
	u8 reserved[92];
पूर्ण;

काष्ठा atto_csmi_raid_drives अणु
	अक्षर model[40];
	अक्षर firmware[8];
	अक्षर serial_num[40];
	u8 sas_addr[8];
	u8 lun[8];
	u8 drive_sts;
	#घोषणा CSMI_DRV_STS_OK          0
	#घोषणा CSMI_DRV_STS_REBUILDING  1
	#घोषणा CSMI_DRV_STS_FAILED      2
	#घोषणा CSMI_DRV_STS_DEGRADED    3

	u8 drive_usage;
	#घोषणा CSMI_DRV_USE_NOT_USED    0
	#घोषणा CSMI_DRV_USE_MEMBER      1
	#घोषणा CSMI_DRV_USE_SPARE       2

	u8 reserved[30]; /* spec says 22 */
पूर्ण;

काष्ठा atto_csmi_get_raid_cfg अणु
	u32 raid_set_index;
	u32 capacity;
	u32 stripe_size;
	u8 raid_type;
	u8 status;
	u8 inक्रमmation;
	u8 drive_cnt;
	u8 reserved[20];

	काष्ठा atto_csmi_raid_drives drives[1];
पूर्ण;

/* CSMI HBA class काष्ठाures */
काष्ठा atto_csmi_phy_entity अणु
	u8 ident_frame[0x1C];
	u8 port_id;
	u8 neg_link_rate;
	u8 min_link_rate;
	u8 max_link_rate;
	u8 phy_change_cnt;
	u8 स्वतः_discover;
	#घोषणा CSMI_DISC_NOT_SUPPORTED  0x00
	#घोषणा CSMI_DISC_NOT_STARTED    0x01
	#घोषणा CSMI_DISC_IN_PROGRESS    0x02
	#घोषणा CSMI_DISC_COMPLETE       0x03
	#घोषणा CSMI_DISC_ERROR          0x04

	u8 reserved[2];
	u8 attach_ident_frame[0x1C];
पूर्ण;

काष्ठा atto_csmi_get_phy_info अणु
	u8 number_of_phys;
	u8 reserved[3];
	काष्ठा atto_csmi_phy_entity
		phy[32];
पूर्ण;

काष्ठा atto_csmi_set_phy_info अणु
	u8 phy_id;
	u8 neg_link_rate;
	#घोषणा CSMI_NEG_RATE_NEGOTIATE  0x00
	#घोषणा CSMI_NEG_RATE_PHY_DIS    0x01

	u8 prog_minlink_rate;
	u8 prog_maxlink_rate;
	u8 संकेत_class;
	#घोषणा CSMI_SIG_CLASS_UNKNOWN   0x00
	#घोषणा CSMI_SIG_CLASS_सूचीECT    0x01
	#घोषणा CSMI_SIG_CLASS_SERVER    0x02
	#घोषणा CSMI_SIG_CLASS_ENCLOSURE 0x03

	u8 reserved[3];
पूर्ण;

काष्ठा atto_csmi_get_link_errors अणु
	u8 phy_id;
	u8 reset_cnts;
	#घोषणा CSMI_RESET_CNTS_NO       0x00
	#घोषणा CSMI_RESET_CNTS_YES      0x01

	u8 reserved[2];
	u32 inv_dw_cnt;
	u32 disp_err_cnt;
	u32 loss_ofdw_sync_cnt;
	u32 phy_reseterr_cnt;

	/*
	 * The following field has been added by ATTO क्रम ease of
	 * implementation of additional statistics.  Drivers must validate
	 * the length of the IOCTL payload prior to filling them in so CSMI
	 * complaपूर्णांक applications function correctly.
	 */

	u32 crc_err_cnt;
पूर्ण;

काष्ठा atto_csmi_smp_passthru अणु
	u8 phy_id;
	u8 port_id;
	u8 conn_rate;
	u8 reserved;
	u8 dest_sas_addr[8];
	u32 req_len;
	u8 smp_req[1020];
	u8 conn_sts;
	u8 reserved2[3];
	u32 rsp_len;
	u8 smp_rsp[1020];
पूर्ण;

काष्ठा atto_csmi_ssp_passthru_sts अणु
	u8 conn_sts;
	u8 reserved[3];
	u8 data_present;
	u8 status;
	u16 rsp_length;
	u8 rsp[256];
	u32 data_bytes;
पूर्ण;

काष्ठा atto_csmi_ssp_passthru अणु
	u8 phy_id;
	u8 port_id;
	u8 conn_rate;
	u8 reserved;
	u8 dest_sas_addr[8];
	u8 lun[8];
	u8 cdb_len;
	u8 add_cdb_len;
	u8 reserved2[2];
	u8 cdb[16];
	u32 flags;
	#घोषणा CSMI_SSPF_DD_READ        0x00000001
	#घोषणा CSMI_SSPF_DD_WRITE       0x00000002
	#घोषणा CSMI_SSPF_DD_UNSPECIFIED 0x00000004
	#घोषणा CSMI_SSPF_TA_SIMPLE      0x00000000
	#घोषणा CSMI_SSPF_TA_HEAD_OF_Q   0x00000010
	#घोषणा CSMI_SSPF_TA_ORDERED     0x00000020
	#घोषणा CSMI_SSPF_TA_ACA         0x00000040

	u8 add_cdb[24];
	u32 data_len;

	काष्ठा atto_csmi_ssp_passthru_sts sts;
पूर्ण;

काष्ठा atto_csmi_stp_passthru_sts अणु
	u8 conn_sts;
	u8 reserved[3];
	u8 sts_fis[20];
	u32 scr[16];
	u32 data_bytes;
पूर्ण;

काष्ठा atto_csmi_stp_passthru अणु
	u8 phy_id;
	u8 port_id;
	u8 conn_rate;
	u8 reserved;
	u8 dest_sas_addr[8];
	u8 reserved2[4];
	u8 command_fis[20];
	u32 flags;
	#घोषणा CSMI_STPF_DD_READ        0x00000001
	#घोषणा CSMI_STPF_DD_WRITE       0x00000002
	#घोषणा CSMI_STPF_DD_UNSPECIFIED 0x00000004
	#घोषणा CSMI_STPF_PIO            0x00000010
	#घोषणा CSMI_STPF_DMA            0x00000020
	#घोषणा CSMI_STPF_PACKET         0x00000040
	#घोषणा CSMI_STPF_DMA_QUEUED     0x00000080
	#घोषणा CSMI_STPF_EXECUTE_DIAG   0x00000100
	#घोषणा CSMI_STPF_RESET_DEVICE   0x00000200

	u32 data_len;

	काष्ठा atto_csmi_stp_passthru_sts sts;
पूर्ण;

काष्ठा atto_csmi_get_sata_sig अणु
	u8 phy_id;
	u8 reserved[3];
	u8 reg_dth_fis[20];
पूर्ण;

काष्ठा atto_csmi_get_scsi_addr अणु
	u8 sas_addr[8];
	u8 sas_lun[8];
	u8 host_index;
	u8 path_id;
	u8 target_id;
	u8 lun;
पूर्ण;

काष्ठा atto_csmi_get_dev_addr अणु
	u8 host_index;
	u8 path_id;
	u8 target_id;
	u8 lun;
	u8 sas_addr[8];
	u8 sas_lun[8];
पूर्ण;

काष्ठा atto_csmi_task_mgmt अणु
	u8 host_index;
	u8 path_id;
	u8 target_id;
	u8 lun;
	u32 flags;
	#घोषणा CSMI_TMF_TASK_IU         0x00000001
	#घोषणा CSMI_TMF_HARD_RST        0x00000002
	#घोषणा CSMI_TMF_SUPPRESS_RSLT   0x00000004

	u32 queue_tag;
	u32 reserved;
	u8 task_mgt_func;
	u8 reserved2[7];
	u32 inक्रमmation;
	#घोषणा CSMI_TM_INFO_TEST        1
	#घोषणा CSMI_TM_INFO_EXCEEDED    2
	#घोषणा CSMI_TM_INFO_DEMAND      3
	#घोषणा CSMI_TM_INFO_TRIGGER     4

	काष्ठा atto_csmi_ssp_passthru_sts sts;

पूर्ण;

काष्ठा atto_csmi_get_conn_info अणु
	u32 pinout;
	#घोषणा CSMI_CON_UNKNOWN         0x00000001
	#घोषणा CSMI_CON_SFF_8482        0x00000002
	#घोषणा CSMI_CON_SFF_8470_LANE_1 0x00000100
	#घोषणा CSMI_CON_SFF_8470_LANE_2 0x00000200
	#घोषणा CSMI_CON_SFF_8470_LANE_3 0x00000400
	#घोषणा CSMI_CON_SFF_8470_LANE_4 0x00000800
	#घोषणा CSMI_CON_SFF_8484_LANE_1 0x00010000
	#घोषणा CSMI_CON_SFF_8484_LANE_2 0x00020000
	#घोषणा CSMI_CON_SFF_8484_LANE_3 0x00040000
	#घोषणा CSMI_CON_SFF_8484_LANE_4 0x00080000

	u8 connector[16];
	u8 location;
	#घोषणा CSMI_CON_INTERNAL        0x02
	#घोषणा CSMI_CON_EXTERNAL        0x04
	#घोषणा CSMI_CON_SWITCHABLE      0x08
	#घोषणा CSMI_CON_AUTO            0x10

	u8 reserved[15];
पूर्ण;

/* CSMI PHY class काष्ठाures */
काष्ठा atto_csmi_अक्षरacter अणु
	u8 type_flags;
	#घोषणा CSMI_CTF_POS_DISP        0x01
	#घोषणा CSMI_CTF_NEG_DISP        0x02
	#घोषणा CSMI_CTF_CTRL_CHAR       0x04

	u8 value;
पूर्ण;

काष्ठा atto_csmi_pc_ctrl अणु
	u8 type;
	#घोषणा CSMI_PC_TYPE_UNDEFINED   0x00
	#घोषणा CSMI_PC_TYPE_SATA        0x01
	#घोषणा CSMI_PC_TYPE_SAS         0x02
	u8 rate;
	u8 reserved[6];
	u32 venकरोr_unique[8];
	u32 tx_flags;
	#घोषणा CSMI_PC_TXF_PREEMP_DIS   0x00000001

	चिन्हित अक्षर tx_amplitude;
	चिन्हित अक्षर tx_preemphasis;
	चिन्हित अक्षर tx_slew_rate;
	चिन्हित अक्षर tx_reserved[13];
	u8 tx_venकरोr_unique[64];
	u32 rx_flags;
	#घोषणा CSMI_PC_RXF_EQ_DIS       0x00000001

	चिन्हित अक्षर rx_threshold;
	चिन्हित अक्षर rx_equalization_gain;
	चिन्हित अक्षर rx_reserved[14];
	u8 rx_venकरोr_unique[64];
	u32 pattern_flags;
	#घोषणा CSMI_PC_PATF_FIXED       0x00000001
	#घोषणा CSMI_PC_PATF_DIS_SCR     0x00000002
	#घोषणा CSMI_PC_PATF_DIS_ALIGN   0x00000004
	#घोषणा CSMI_PC_PATF_DIS_SSC     0x00000008

	u8 fixed_pattern;
	#घोषणा CSMI_PC_FP_CJPAT         0x00000001
	#घोषणा CSMI_PC_FP_ALIGN         0x00000002

	u8 user_pattern_len;
	u8 pattern_reserved[6];

	काष्ठा atto_csmi_अक्षरacter user_pattern_buffer[16];
पूर्ण;

काष्ठा atto_csmi_phy_ctrl अणु
	u32 function;
	#घोषणा CSMI_PC_FUNC_GET_SETUP   0x00000100

	u8 phy_id;
	u16 len_of_cntl;
	u8 num_of_cntls;
	u8 reserved[4];
	u32 link_flags;
	#घोषणा CSMI_PHY_ACTIVATE_CTRL   0x00000001
	#घोषणा CSMI_PHY_UPD_SPINUP_RATE 0x00000002
	#घोषणा CSMI_PHY_AUTO_COMWAKE    0x00000004

	u8 spinup_rate;
	u8 link_reserved[7];
	u32 venकरोr_unique[8];

	काष्ठा atto_csmi_pc_ctrl control[1];
पूर्ण;

जोड़ atto_ioctl_csmi अणु
	काष्ठा atto_csmi_get_driver_info drvr_info;
	काष्ठा atto_csmi_get_cntlr_cfg cntlr_cfg;
	काष्ठा atto_csmi_get_cntlr_sts cntlr_sts;
	काष्ठा atto_csmi_fw_करोwnload fw_dwnld;
	काष्ठा atto_csmi_get_raid_info raid_info;
	काष्ठा atto_csmi_get_raid_cfg raid_cfg;
	काष्ठा atto_csmi_get_phy_info get_phy_info;
	काष्ठा atto_csmi_set_phy_info set_phy_info;
	काष्ठा atto_csmi_get_link_errors link_errs;
	काष्ठा atto_csmi_smp_passthru smp_pass_thru;
	काष्ठा atto_csmi_ssp_passthru ssp_pass_thru;
	काष्ठा atto_csmi_stp_passthru stp_pass_thru;
	काष्ठा atto_csmi_task_mgmt tsk_mgt;
	काष्ठा atto_csmi_get_sata_sig sata_sig;
	काष्ठा atto_csmi_get_scsi_addr scsi_addr;
	काष्ठा atto_csmi_get_dev_addr dev_addr;
	काष्ठा atto_csmi_get_conn_info conn_info[32];
	काष्ठा atto_csmi_phy_ctrl phy_ctrl;
पूर्ण;

काष्ठा atto_csmi अणु
	u32 control_code;
	u32 status;
	जोड़ atto_ioctl_csmi data;
पूर्ण;

काष्ठा atto_module_info अणु
	व्योम *adapter;
	व्योम *pci_dev;
	व्योम *scsi_host;
	अचिन्हित लघु host_no;
	जोड़ अणु
		काष्ठा अणु
			u64 node_name;
			u64 port_name;
		पूर्ण;
		u64 sas_addr;
	पूर्ण;
पूर्ण;

#घोषणा ATTO_FUNC_GET_ADAP_INFO      0x00
#घोषणा ATTO_VER_GET_ADAP_INFO0      0
#घोषणा ATTO_VER_GET_ADAP_INFO       ATTO_VER_GET_ADAP_INFO0

काष्ठा __packed atto_hba_get_adapter_info अणु

	काष्ठा अणु
		u16 venकरोr_id;
		u16 device_id;
		u16 ss_venकरोr_id;
		u16 ss_device_id;
		u8 class_code[3];
		u8 rev_id;
		u8 bus_num;
		u8 dev_num;
		u8 func_num;
		u8 link_width_max;
		u8 link_width_curr;
	    #घोषणा ATTO_GAI_PCILW_UNKNOWN   0x00

		u8 link_speed_max;
		u8 link_speed_curr;
	    #घोषणा ATTO_GAI_PCILS_UNKNOWN   0x00
	    #घोषणा ATTO_GAI_PCILS_GEN1      0x01
	    #घोषणा ATTO_GAI_PCILS_GEN2      0x02
	    #घोषणा ATTO_GAI_PCILS_GEN3      0x03

		u8 पूर्णांकerrupt_mode;
	    #घोषणा ATTO_GAI_PCIIM_UNKNOWN   0x00
	    #घोषणा ATTO_GAI_PCIIM_LEGACY    0x01
	    #घोषणा ATTO_GAI_PCIIM_MSI       0x02
	    #घोषणा ATTO_GAI_PCIIM_MSIX      0x03

		u8 msi_vector_cnt;
		u8 reserved[19];
	पूर्ण pci;

	u8 adap_type;
	#घोषणा ATTO_GAI_AT_EPCIU320     0x00
	#घोषणा ATTO_GAI_AT_ESASRAID     0x01
	#घोषणा ATTO_GAI_AT_ESASRAID2    0x02
	#घोषणा ATTO_GAI_AT_ESASHBA      0x03
	#घोषणा ATTO_GAI_AT_ESASHBA2     0x04
	#घोषणा ATTO_GAI_AT_CELERITY     0x05
	#घोषणा ATTO_GAI_AT_CELERITY8    0x06
	#घोषणा ATTO_GAI_AT_FASTFRAME    0x07
	#घोषणा ATTO_GAI_AT_ESASHBA3     0x08
	#घोषणा ATTO_GAI_AT_CELERITY16   0x09
	#घोषणा ATTO_GAI_AT_TLSASHBA     0x0A
	#घोषणा ATTO_GAI_AT_ESASHBA4     0x0B

	u8 adap_flags;
	#घोषणा ATTO_GAI_AF_DEGRADED     0x01
	#घोषणा ATTO_GAI_AF_SPT_SUPP     0x02
	#घोषणा ATTO_GAI_AF_DEVADDR_SUPP 0x04
	#घोषणा ATTO_GAI_AF_PHYCTRL_SUPP 0x08
	#घोषणा ATTO_GAI_AF_TEST_SUPP    0x10
	#घोषणा ATTO_GAI_AF_DIAG_SUPP    0x20
	#घोषणा ATTO_GAI_AF_VIRT_SES     0x40
	#घोषणा ATTO_GAI_AF_CONN_CTRL    0x80

	u8 num_ports;
	u8 num_phys;
	u8 drvr_rev_major;
	u8 drvr_rev_minor;
	u8 drvr_revsub_minor;
	u8 drvr_rev_build;
	अक्षर drvr_rev_ascii[16];
	अक्षर drvr_name[32];
	अक्षर firmware_rev[16];
	अक्षर flash_rev[16];
	अक्षर model_name_लघु[16];
	अक्षर model_name[32];
	u32 num_tarमाला_लो;
	u32 num_targsper_bus;
	u32 num_lunsper_targ;
	u8 num_busses;
	u8 num_connectors;
	u8 adap_flags2;
	#घोषणा ATTO_GAI_AF2_FCOE_SUPP       0x01
	#घोषणा ATTO_GAI_AF2_NIC_SUPP        0x02
	#घोषणा ATTO_GAI_AF2_LOCATE_SUPP     0x04
	#घोषणा ATTO_GAI_AF2_ADAP_CTRL_SUPP  0x08
	#घोषणा ATTO_GAI_AF2_DEV_INFO_SUPP   0x10
	#घोषणा ATTO_GAI_AF2_NPIV_SUPP       0x20
	#घोषणा ATTO_GAI_AF2_MP_SUPP         0x40

	u8 num_temp_sensors;
	u32 num_tarमाला_लो_backend;
	u32 tunnel_flags;
	#घोषणा ATTO_GAI_TF_MEM_RW           0x00000001
	#घोषणा ATTO_GAI_TF_TRACE            0x00000002
	#घोषणा ATTO_GAI_TF_SCSI_PASS_THRU   0x00000004
	#घोषणा ATTO_GAI_TF_GET_DEV_ADDR     0x00000008
	#घोषणा ATTO_GAI_TF_PHY_CTRL         0x00000010
	#घोषणा ATTO_GAI_TF_CONN_CTRL        0x00000020
	#घोषणा ATTO_GAI_TF_GET_DEV_INFO     0x00000040

	u8 reserved3[0x138];
पूर्ण;

#घोषणा ATTO_FUNC_GET_ADAP_ADDR      0x01
#घोषणा ATTO_VER_GET_ADAP_ADDR0      0
#घोषणा ATTO_VER_GET_ADAP_ADDR       ATTO_VER_GET_ADAP_ADDR0

काष्ठा __packed atto_hba_get_adapter_address अणु

	u8 addr_type;
	#घोषणा ATTO_GAA_AT_PORT         0x00
	#घोषणा ATTO_GAA_AT_NODE         0x01
	#घोषणा ATTO_GAA_AT_CURR_MAC     0x02
	#घोषणा ATTO_GAA_AT_PERM_MAC     0x03
	#घोषणा ATTO_GAA_AT_VNIC         0x04

	u8 port_id;
	u16 addr_len;
	u8 address[256];
पूर्ण;

#घोषणा ATTO_FUNC_MEM_RW             0x02
#घोषणा ATTO_VER_MEM_RW0             0
#घोषणा ATTO_VER_MEM_RW              ATTO_VER_MEM_RW0

काष्ठा __packed atto_hba_memory_पढ़ो_ग_लिखो अणु
	u8 mem_func;
	u8 mem_type;
	जोड़ अणु
		u8 pci_index;
		u8 i2c_dev;
	पूर्ण;
	u8 i2c_status;
	u32 length;
	u64 address;
	u8 reserved[48];

पूर्ण;

#घोषणा ATTO_FUNC_TRACE              0x03
#घोषणा ATTO_VER_TRACE0              0
#घोषणा ATTO_VER_TRACE1              1
#घोषणा ATTO_VER_TRACE               ATTO_VER_TRACE1

काष्ठा __packed atto_hba_trace अणु
	u8 trace_func;
	#घोषणा ATTO_TRC_TF_GET_INFO     0x00
	#घोषणा ATTO_TRC_TF_ENABLE       0x01
	#घोषणा ATTO_TRC_TF_DISABLE      0x02
	#घोषणा ATTO_TRC_TF_SET_MASK     0x03
	#घोषणा ATTO_TRC_TF_UPLOAD       0x04
	#घोषणा ATTO_TRC_TF_RESET        0x05

	u8 trace_type;
	#घोषणा ATTO_TRC_TT_DRIVER       0x00
	#घोषणा ATTO_TRC_TT_FWCOREDUMP   0x01

	u8 reserved[2];
	u32 current_offset;
	u32 total_length;
	u32 trace_mask;
	u8 reserved2[48];
पूर्ण;

#घोषणा ATTO_FUNC_SCSI_PASS_THRU     0x04
#घोषणा ATTO_VER_SCSI_PASS_THRU0     0
#घोषणा ATTO_VER_SCSI_PASS_THRU      ATTO_VER_SCSI_PASS_THRU0

काष्ठा __packed atto_hba_scsi_pass_thru अणु
	u8 cdb[32];
	u8 cdb_length;
	u8 req_status;
	#घोषणा ATTO_SPT_RS_SUCCESS      0x00
	#घोषणा ATTO_SPT_RS_FAILED       0x01
	#घोषणा ATTO_SPT_RS_OVERRUN      0x02
	#घोषणा ATTO_SPT_RS_UNDERRUN     0x03
	#घोषणा ATTO_SPT_RS_NO_DEVICE    0x04
	#घोषणा ATTO_SPT_RS_NO_LUN       0x05
	#घोषणा ATTO_SPT_RS_TIMEOUT      0x06
	#घोषणा ATTO_SPT_RS_BUS_RESET    0x07
	#घोषणा ATTO_SPT_RS_ABORTED      0x08
	#घोषणा ATTO_SPT_RS_BUSY         0x09
	#घोषणा ATTO_SPT_RS_DEGRADED     0x0A

	u8 scsi_status;
	u8 sense_length;
	u32 flags;
	#घोषणा ATTO_SPTF_DATA_IN    0x00000001
	#घोषणा ATTO_SPTF_DATA_OUT   0x00000002
	#घोषणा ATTO_SPTF_SIMPLE_Q   0x00000004
	#घोषणा ATTO_SPTF_HEAD_OF_Q  0x00000008
	#घोषणा ATTO_SPTF_ORDERED_Q  0x00000010

	u32 समयout;
	u32 target_id;
	u8 lun[8];
	u32 residual_length;
	u8 sense_data[0xFC];
	u8 reserved[0x28];
पूर्ण;

#घोषणा ATTO_FUNC_GET_DEV_ADDR       0x05
#घोषणा ATTO_VER_GET_DEV_ADDR0       0
#घोषणा ATTO_VER_GET_DEV_ADDR        ATTO_VER_GET_DEV_ADDR0

काष्ठा __packed atto_hba_get_device_address अणु
	u8 addr_type;
	#घोषणा ATTO_GDA_AT_PORT         0x00
	#घोषणा ATTO_GDA_AT_NODE         0x01
	#घोषणा ATTO_GDA_AT_MAC          0x02
	#घोषणा ATTO_GDA_AT_PORTID       0x03
	#घोषणा ATTO_GDA_AT_UNIQUE       0x04

	u8 reserved;
	u16 addr_len;
	u32 target_id;
	u8 address[256];
पूर्ण;

/* The following functions are supported by firmware but करो not have any
 * associated driver काष्ठाures
 */
#घोषणा ATTO_FUNC_PHY_CTRL           0x06
#घोषणा ATTO_FUNC_CONN_CTRL          0x0C
#घोषणा ATTO_FUNC_ADAP_CTRL          0x0E
#घोषणा ATTO_VER_ADAP_CTRL0          0
#घोषणा ATTO_VER_ADAP_CTRL           ATTO_VER_ADAP_CTRL0

काष्ठा __packed atto_hba_adap_ctrl अणु
	u8 adap_func;
	#घोषणा ATTO_AC_AF_HARD_RST      0x00
	#घोषणा ATTO_AC_AF_GET_STATE     0x01
	#घोषणा ATTO_AC_AF_GET_TEMP      0x02

	u8 adap_state;
	#घोषणा ATTO_AC_AS_UNKNOWN       0x00
	#घोषणा ATTO_AC_AS_OK            0x01
	#घोषणा ATTO_AC_AS_RST_SCHED     0x02
	#घोषणा ATTO_AC_AS_RST_IN_PROG   0x03
	#घोषणा ATTO_AC_AS_RST_DISC      0x04
	#घोषणा ATTO_AC_AS_DEGRADED      0x05
	#घोषणा ATTO_AC_AS_DISABLED      0x06
	#घोषणा ATTO_AC_AS_TEMP          0x07

	u8 reserved[2];

	जोड़ अणु
		काष्ठा अणु
			u8 temp_sensor;
			u8 temp_state;

	#घोषणा ATTO_AC_TS_UNSUPP        0x00
	#घोषणा ATTO_AC_TS_UNKNOWN       0x01
	#घोषणा ATTO_AC_TS_INIT_FAILED   0x02
	#घोषणा ATTO_AC_TS_NORMAL        0x03
	#घोषणा ATTO_AC_TS_OUT_OF_RANGE  0x04
	#घोषणा ATTO_AC_TS_FAULT         0x05

			चिन्हित लघु temp_value;
			चिन्हित लघु temp_lower_lim;
			चिन्हित लघु temp_upper_lim;
			अक्षर temp_desc[32];
			u8 reserved2[20];
		पूर्ण;
	पूर्ण;
पूर्ण;

#घोषणा ATTO_FUNC_GET_DEV_INFO       0x0F
#घोषणा ATTO_VER_GET_DEV_INFO0       0
#घोषणा ATTO_VER_GET_DEV_INFO        ATTO_VER_GET_DEV_INFO0

काष्ठा __packed atto_hba_sas_device_info अणु

    #घोषणा ATTO_SDI_MAX_PHYS_WIDE_PORT  16

	u8 phy_id[ATTO_SDI_MAX_PHYS_WIDE_PORT]; /* IDs of parent exp/adapt */
	#घोषणा ATTO_SDI_PHY_ID_INV      ATTO_SAS_PHY_ID_INV
	u32 exp_target_id;
	u32 sas_port_mask;
	u8 sas_level;
	#घोषणा ATTO_SDI_SAS_LVL_INV     0xFF

	u8 slot_num;
	#घोषणा ATTO_SDI_SLOT_NUM_INV    ATTO_SLOT_NUM_INV

	u8 dev_type;
	#घोषणा ATTO_SDI_DT_END_DEVICE   0
	#घोषणा ATTO_SDI_DT_EXPANDER     1
	#घोषणा ATTO_SDI_DT_PORT_MULT    2

	u8 ini_flags;
	u8 tgt_flags;
	u8 link_rate; /* SMP_RATE_XXX */
	u8 loc_flags;
	#घोषणा ATTO_SDI_LF_सूचीECT       0x01
	#घोषणा ATTO_SDI_LF_EXPANDER     0x02
	#घोषणा ATTO_SDI_LF_PORT_MULT    0x04
	u8 pm_port;
	u8 reserved[0x60];
पूर्ण;

जोड़ atto_hba_device_info अणु
	काष्ठा atto_hba_sas_device_info sas_dev_info;
पूर्ण;

काष्ठा __packed atto_hba_get_device_info अणु
	u32 target_id;
	u8 info_type;
	#घोषणा ATTO_GDI_IT_UNKNOWN      0x00
	#घोषणा ATTO_GDI_IT_SAS          0x01
	#घोषणा ATTO_GDI_IT_FC           0x02
	#घोषणा ATTO_GDI_IT_FCOE         0x03

	u8 reserved[11];
	जोड़ atto_hba_device_info dev_info;
पूर्ण;

काष्ठा atto_ioctl अणु
	u8 version;
	u8 function; /* ATTO_FUNC_XXX */
	u8 status;
#घोषणा ATTO_STS_SUCCESS         0x00
#घोषणा ATTO_STS_FAILED          0x01
#घोषणा ATTO_STS_INV_VERSION     0x02
#घोषणा ATTO_STS_OUT_OF_RSRC     0x03
#घोषणा ATTO_STS_INV_FUNC        0x04
#घोषणा ATTO_STS_UNSUPPORTED     0x05
#घोषणा ATTO_STS_INV_ADAPTER     0x06
#घोषणा ATTO_STS_INV_DRVR_VER    0x07
#घोषणा ATTO_STS_INV_PARAM       0x08
#घोषणा ATTO_STS_TIMEOUT         0x09
#घोषणा ATTO_STS_NOT_APPL        0x0A
#घोषणा ATTO_STS_DEGRADED        0x0B

	u8 flags;
	#घोषणा HBAF_TUNNEL      0x01

	u32 data_length;
	u8 reserved2[56];

	जोड़ अणु
		u8 byte[1];
		काष्ठा atto_hba_get_adapter_info get_adap_info;
		काष्ठा atto_hba_get_adapter_address get_adap_addr;
		काष्ठा atto_hba_scsi_pass_thru scsi_pass_thru;
		काष्ठा atto_hba_get_device_address get_dev_addr;
		काष्ठा atto_hba_adap_ctrl adap_ctrl;
		काष्ठा atto_hba_get_device_info get_dev_info;
		काष्ठा atto_hba_trace trace;
	पूर्ण data;

पूर्ण;

काष्ठा __packed atto_ioctl_vda_scsi_cmd अणु

    #घोषणा ATTO_VDA_SCSI_VER0   0
    #घोषणा ATTO_VDA_SCSI_VER    ATTO_VDA_SCSI_VER0

	u8 cdb[16];
	u32 flags;
	u32 data_length;
	u32 residual_length;
	u16 target_id;
	u8 sense_len;
	u8 scsi_stat;
	u8 reserved[8];
	u8 sense_data[80];
पूर्ण;

काष्ठा __packed atto_ioctl_vda_flash_cmd अणु

    #घोषणा ATTO_VDA_FLASH_VER0  0
    #घोषणा ATTO_VDA_FLASH_VER   ATTO_VDA_FLASH_VER0

	u32 flash_addr;
	u32 data_length;
	u8 sub_func;
	u8 reserved[15];

	जोड़ अणु
		काष्ठा अणु
			u32 flash_size;
			u32 page_size;
			u8 prod_info[32];
		पूर्ण info;

		काष्ठा अणु
			अक्षर file_name[16]; /* 8.3 fname, शून्य term, wc=* */
			u32 file_size;
		पूर्ण file;
	पूर्ण data;

पूर्ण;

काष्ठा __packed atto_ioctl_vda_diag_cmd अणु

    #घोषणा ATTO_VDA_DIAG_VER0   0
    #घोषणा ATTO_VDA_DIAG_VER    ATTO_VDA_DIAG_VER0

	u64 local_addr;
	u32 data_length;
	u8 sub_func;
	u8 flags;
	u8 reserved[3];
पूर्ण;

काष्ठा __packed atto_ioctl_vda_cli_cmd अणु

    #घोषणा ATTO_VDA_CLI_VER0    0
    #घोषणा ATTO_VDA_CLI_VER     ATTO_VDA_CLI_VER0

	u32 cmd_rsp_len;
पूर्ण;

काष्ठा __packed atto_ioctl_vda_smp_cmd अणु

    #घोषणा ATTO_VDA_SMP_VER0    0
    #घोषणा ATTO_VDA_SMP_VER     ATTO_VDA_SMP_VER0

	u64 dest;
	u32 cmd_rsp_len;
पूर्ण;

काष्ठा __packed atto_ioctl_vda_cfg_cmd अणु

    #घोषणा ATTO_VDA_CFG_VER0    0
    #घोषणा ATTO_VDA_CFG_VER     ATTO_VDA_CFG_VER0

	u32 data_length;
	u8 cfg_func;
	u8 reserved[11];

	जोड़ अणु
		u8 bytes[112];
		काष्ठा atto_vda_cfg_init init;
	पूर्ण data;

पूर्ण;

काष्ठा __packed atto_ioctl_vda_mgt_cmd अणु

    #घोषणा ATTO_VDA_MGT_VER0    0
    #घोषणा ATTO_VDA_MGT_VER     ATTO_VDA_MGT_VER0

	u8 mgt_func;
	u8 scan_generation;
	u16 dev_index;
	u32 data_length;
	u8 reserved[8];
	जोड़ अणु
		u8 bytes[112];
		काष्ठा atto_vda_devinfo dev_info;
		काष्ठा atto_vda_grp_info grp_info;
		काष्ठा atto_vdapart_info part_info;
		काष्ठा atto_vda_dh_info dh_info;
		काष्ठा atto_vda_metrics_info metrics_info;
		काष्ठा atto_vda_schedule_info sched_info;
		काष्ठा atto_vda_n_vcache_info nvcache_info;
		काष्ठा atto_vda_buzzer_info buzzer_info;
		काष्ठा atto_vda_adapter_info adapter_info;
		काष्ठा atto_vda_temp_info temp_info;
		काष्ठा atto_vda_fan_info fan_info;
	पूर्ण data;
पूर्ण;

काष्ठा __packed atto_ioctl_vda_gsv_cmd अणु

    #घोषणा ATTO_VDA_GSV_VER0    0
    #घोषणा ATTO_VDA_GSV_VER     ATTO_VDA_GSV_VER0

	u8 rsp_len;
	u8 reserved[7];
	u8 version_info[1];
	#घोषणा ATTO_VDA_VER_UNSUPPORTED 0xFF

पूर्ण;

काष्ठा __packed atto_ioctl_vda अणु
	u8 version;
	u8 function;    /* VDA_FUNC_XXXX */
	u8 status;      /* ATTO_STS_XXX */
	u8 vda_status;  /* RS_XXX (अगर status == ATTO_STS_SUCCESS) */
	u32 data_length;
	u8 reserved[8];

	जोड़ अणु
		काष्ठा atto_ioctl_vda_scsi_cmd scsi;
		काष्ठा atto_ioctl_vda_flash_cmd flash;
		काष्ठा atto_ioctl_vda_diag_cmd diag;
		काष्ठा atto_ioctl_vda_cli_cmd cli;
		काष्ठा atto_ioctl_vda_smp_cmd smp;
		काष्ठा atto_ioctl_vda_cfg_cmd cfg;
		काष्ठा atto_ioctl_vda_mgt_cmd mgt;
		काष्ठा atto_ioctl_vda_gsv_cmd gsv;
		u8 cmd_info[256];
	पूर्ण cmd;

	जोड़ अणु
		u8 data[1];
		काष्ठा atto_vda_devinfo2 dev_info2;
	पूर्ण data;

पूर्ण;

काष्ठा __packed atto_ioctl_smp अणु
	u8 version;
	#घोषणा ATTO_SMP_VERSION0        0
	#घोषणा ATTO_SMP_VERSION1        1
	#घोषणा ATTO_SMP_VERSION2        2
	#घोषणा ATTO_SMP_VERSION         ATTO_SMP_VERSION2

	u8 function;
#घोषणा ATTO_SMP_FUNC_DISC_SMP           0x00
#घोषणा ATTO_SMP_FUNC_DISC_TARG          0x01
#घोषणा ATTO_SMP_FUNC_SEND_CMD           0x02
#घोषणा ATTO_SMP_FUNC_DISC_TARG_सूचीECT   0x03
#घोषणा ATTO_SMP_FUNC_SEND_CMD_सूचीECT    0x04
#घोषणा ATTO_SMP_FUNC_DISC_SMP_सूचीECT    0x05

	u8 status;      /* ATTO_STS_XXX */
	u8 smp_status;  /* अगर status == ATTO_STS_SUCCESS */
	#घोषणा ATTO_SMP_STS_SUCCESS     0x00
	#घोषणा ATTO_SMP_STS_FAILURE     0x01
	#घोषणा ATTO_SMP_STS_RESCAN      0x02
	#घोषणा ATTO_SMP_STS_NOT_FOUND   0x03

	u16 target_id;
	u8 phy_id;
	u8 dev_index;
	u64 smp_sas_addr;
	u64 targ_sas_addr;
	u32 req_length;
	u32 rsp_length;
	u8 flags;
	#घोषणा ATTO_SMPF_ROOT_EXP       0x01 /* expander direct attached */

	u8 reserved[31];

	जोड़ अणु
		u8 byte[1];
		u32 dword[1];
	पूर्ण data;

पूर्ण;

काष्ठा __packed atto_express_ioctl अणु
	काष्ठा atto_express_ioctl_header header;

	जोड़ अणु
		काष्ठा atto_firmware_rw_request fwrw;
		काष्ठा atto_param_rw_request prw;
		काष्ठा atto_channel_list chanlist;
		काष्ठा atto_channel_info chaninfo;
		काष्ठा atto_ioctl ioctl_hba;
		काष्ठा atto_module_info modinfo;
		काष्ठा atto_ioctl_vda ioctl_vda;
		काष्ठा atto_ioctl_smp ioctl_smp;
		काष्ठा atto_csmi csmi;

	पूर्ण data;
पूर्ण;

/* The काष्ठा associated with the code is listed after the definition */
#घोषणा EXPRESS_IOCTL_MIN             0x4500
#घोषणा EXPRESS_IOCTL_RW_FIRMWARE     0x4500            /* FIRMWARERW    */
#घोषणा EXPRESS_IOCTL_READ_PARAMS     0x4501            /* PARAMRW       */
#घोषणा EXPRESS_IOCTL_WRITE_PARAMS    0x4502            /* PARAMRW       */
#घोषणा EXPRESS_IOCTL_FC_API          0x4503            /* पूर्णांकernal      */
#घोषणा EXPRESS_IOCTL_GET_CHANNELS    0x4504            /* CHANNELLIST   */
#घोषणा EXPRESS_IOCTL_CHAN_INFO       0x4505            /* CHANNELINFO   */
#घोषणा EXPRESS_IOCTL_DEFAULT_PARAMS  0x4506            /* PARAMRW       */
#घोषणा EXPRESS_ADDR_MEMORY           0x4507            /* MEMADDR       */
#घोषणा EXPRESS_RW_MEMORY             0x4508            /* MEMRW         */
#घोषणा EXPRESS_TSDK_DUMP             0x4509            /* TSDKDUMP      */
#घोषणा EXPRESS_IOCTL_SMP             0x450A            /* IOCTL_SMP     */
#घोषणा EXPRESS_CSMI                  0x450B            /* CSMI          */
#घोषणा EXPRESS_IOCTL_HBA             0x450C            /* IOCTL_HBA     */
#घोषणा EXPRESS_IOCTL_VDA             0x450D            /* IOCTL_VDA     */
#घोषणा EXPRESS_IOCTL_GET_ID          0x450E            /* GET_ID        */
#घोषणा EXPRESS_IOCTL_GET_MOD_INFO    0x450F            /* MODULE_INFO   */
#घोषणा EXPRESS_IOCTL_MAX             0x450F

#पूर्ण_अगर
