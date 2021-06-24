<शैली गुरु>
/*  linux/drivers/scsi/esas2r/atvda.h
 *       ATTO VDA पूर्णांकerface definitions
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


#अगर_अघोषित ATVDA_H
#घोषणा ATVDA_H

काष्ठा __packed atto_dev_addr अणु
	u64 dev_port;
	u64 hba_port;
	u8 lun;
	u8 flags;
	   #घोषणा VDA_DEVADDRF_SATA   0x01
	   #घोषणा VDA_DEVADDRF_SSD    0x02
	u8 link_speed; /* VDALINKSPEED_xxx */
	u8 pad[1];
पूर्ण;

/* dev_addr2 was added क्रम 64-bit alignment */

काष्ठा __packed atto_dev_addr2 अणु
	u64 dev_port;
	u64 hba_port;
	u8 lun;
	u8 flags;
	u8 link_speed;
	u8 pad[5];
पूर्ण;

काष्ठा __packed atto_vda_sge अणु
	u32 length;
	u64 address;
पूर्ण;


/* VDA request function codes */

#घोषणा VDA_FUNC_SCSI     0x00
#घोषणा VDA_FUNC_FLASH    0x01
#घोषणा VDA_FUNC_DIAG     0x02
#घोषणा VDA_FUNC_AE       0x03
#घोषणा VDA_FUNC_CLI      0x04
#घोषणा VDA_FUNC_IOCTL    0x05
#घोषणा VDA_FUNC_CFG      0x06
#घोषणा VDA_FUNC_MGT      0x07
#घोषणा VDA_FUNC_GSV      0x08


/* VDA request status values.  क्रम host driver considerations, values क्रम
 * SCSI requests start at zero.  other requests may use these values as well. */

#घोषणा RS_SUCCESS          0x00        /*! successful completion            */
#घोषणा RS_INV_FUNC         0x01        /*! invalid command function         */
#घोषणा RS_BUSY             0x02        /*! insufficient resources           */
#घोषणा RS_SEL              0x03        /*! no target at target_id           */
#घोषणा RS_NO_LUN           0x04        /*! invalid LUN                      */
#घोषणा RS_TIMEOUT          0x05        /*! request समयout                  */
#घोषणा RS_OVERRUN          0x06        /*! data overrun                     */
#घोषणा RS_UNDERRUN         0x07        /*! data underrun                    */
#घोषणा RS_SCSI_ERROR       0x08        /*! SCSI error occurred              */
#घोषणा RS_ABORTED          0x0A        /*! command पातed                  */
#घोषणा RS_RESID_MISM       0x0B        /*! residual length incorrect        */
#घोषणा RS_TM_FAILED        0x0C        /*! task management failed           */
#घोषणा RS_RESET            0x0D        /*! पातed due to bus reset         */
#घोषणा RS_ERR_DMA_SG       0x0E        /*! error पढ़ोing SG list            */
#घोषणा RS_ERR_DMA_DATA     0x0F        /*! error transferring data          */
#घोषणा RS_UNSUPPORTED      0x10        /*! unsupported request              */
#घोषणा RS_SEL2             0x70        /*! पूर्णांकernal generated RS_SEL        */
#घोषणा RS_VDA_BASE         0x80        /*! base of VDA-specअगरic errors      */
#घोषणा RS_MGT_BASE         0x80        /*! base of VDA management errors    */
#घोषणा RS_SCAN_FAIL        (RS_MGT_BASE + 0x00)
#घोषणा RS_DEV_INVALID      (RS_MGT_BASE + 0x01)
#घोषणा RS_DEV_ASSIGNED     (RS_MGT_BASE + 0x02)
#घोषणा RS_DEV_REMOVE       (RS_MGT_BASE + 0x03)
#घोषणा RS_DEV_LOST         (RS_MGT_BASE + 0x04)
#घोषणा RS_SCAN_GEN         (RS_MGT_BASE + 0x05)
#घोषणा RS_GRP_INVALID      (RS_MGT_BASE + 0x08)
#घोषणा RS_GRP_EXISTS       (RS_MGT_BASE + 0x09)
#घोषणा RS_GRP_LIMIT        (RS_MGT_BASE + 0x0A)
#घोषणा RS_GRP_INTLV        (RS_MGT_BASE + 0x0B)
#घोषणा RS_GRP_SPAN         (RS_MGT_BASE + 0x0C)
#घोषणा RS_GRP_TYPE         (RS_MGT_BASE + 0x0D)
#घोषणा RS_GRP_MEMBERS      (RS_MGT_BASE + 0x0E)
#घोषणा RS_GRP_COMMIT       (RS_MGT_BASE + 0x0F)
#घोषणा RS_GRP_REBUILD      (RS_MGT_BASE + 0x10)
#घोषणा RS_GRP_REBUILD_TYPE (RS_MGT_BASE + 0x11)
#घोषणा RS_GRP_BLOCK_SIZE   (RS_MGT_BASE + 0x12)
#घोषणा RS_CFG_SAVE         (RS_MGT_BASE + 0x14)
#घोषणा RS_PART_LAST        (RS_MGT_BASE + 0x18)
#घोषणा RS_ELEM_INVALID     (RS_MGT_BASE + 0x19)
#घोषणा RS_PART_MAPPED      (RS_MGT_BASE + 0x1A)
#घोषणा RS_PART_TARGET      (RS_MGT_BASE + 0x1B)
#घोषणा RS_PART_LUN         (RS_MGT_BASE + 0x1C)
#घोषणा RS_PART_DUP         (RS_MGT_BASE + 0x1D)
#घोषणा RS_PART_NOMAP       (RS_MGT_BASE + 0x1E)
#घोषणा RS_PART_MAX         (RS_MGT_BASE + 0x1F)
#घोषणा RS_PART_CAP         (RS_MGT_BASE + 0x20)
#घोषणा RS_PART_STATE       (RS_MGT_BASE + 0x21)
#घोषणा RS_TEST_IN_PROG     (RS_MGT_BASE + 0x22)
#घोषणा RS_METRICS_ERROR    (RS_MGT_BASE + 0x23)
#घोषणा RS_HS_ERROR         (RS_MGT_BASE + 0x24)
#घोषणा RS_NO_METRICS_TEST  (RS_MGT_BASE + 0x25)
#घोषणा RS_BAD_PARAM        (RS_MGT_BASE + 0x26)
#घोषणा RS_GRP_MEMBER_SIZE  (RS_MGT_BASE + 0x27)
#घोषणा RS_FLS_BASE         0xB0        /*! base of VDA errors               */
#घोषणा RS_FLS_ERR_AREA     (RS_FLS_BASE + 0x00)
#घोषणा RS_FLS_ERR_BUSY     (RS_FLS_BASE + 0x01)
#घोषणा RS_FLS_ERR_RANGE    (RS_FLS_BASE + 0x02)
#घोषणा RS_FLS_ERR_BEGIN    (RS_FLS_BASE + 0x03)
#घोषणा RS_FLS_ERR_CHECK    (RS_FLS_BASE + 0x04)
#घोषणा RS_FLS_ERR_FAIL     (RS_FLS_BASE + 0x05)
#घोषणा RS_FLS_ERR_RSRC     (RS_FLS_BASE + 0x06)
#घोषणा RS_FLS_ERR_NOखाता   (RS_FLS_BASE + 0x07)
#घोषणा RS_FLS_ERR_FSIZE    (RS_FLS_BASE + 0x08)
#घोषणा RS_CFG_BASE         0xC0        /*! base of VDA configuration errors */
#घोषणा RS_CFG_ERR_BUSY     (RS_CFG_BASE + 0)
#घोषणा RS_CFG_ERR_SGE      (RS_CFG_BASE + 1)
#घोषणा RS_CFG_ERR_DATE     (RS_CFG_BASE + 2)
#घोषणा RS_CFG_ERR_TIME     (RS_CFG_BASE + 3)
#घोषणा RS_DEGRADED         0xFB        /*! degraded mode                    */
#घोषणा RS_CLI_INTERNAL     0xFC        /*! VDA CLI पूर्णांकernal error           */
#घोषणा RS_VDA_INTERNAL     0xFD        /*! catch-all                        */
#घोषणा RS_PENDING          0xFE        /*! pending, not started             */
#घोषणा RS_STARTED          0xFF        /*! started                          */


/* flash request subfunctions.  these are used in both the IOCTL and the
 * driver-firmware पूर्णांकerface (VDA_FUNC_FLASH). */

#घोषणा VDA_FLASH_BEGINW  0x00
#घोषणा VDA_FLASH_READ    0x01
#घोषणा VDA_FLASH_WRITE   0x02
#घोषणा VDA_FLASH_COMMIT  0x03
#घोषणा VDA_FLASH_CANCEL  0x04
#घोषणा VDA_FLASH_INFO    0x05
#घोषणा VDA_FLASH_FREAD   0x06
#घोषणा VDA_FLASH_FWRITE  0x07
#घोषणा VDA_FLASH_FINFO   0x08


/* IOCTL request subfunctions.  these identअगरy the payload type क्रम
 * VDA_FUNC_IOCTL.
 */

#घोषणा VDA_IOCTL_HBA     0x00
#घोषणा VDA_IOCTL_CSMI    0x01
#घोषणा VDA_IOCTL_SMP     0x02

काष्ठा __packed atto_vda_devinfo अणु
	काष्ठा atto_dev_addr dev_addr;
	u8 venकरोr_id[8];
	u8 product_id[16];
	u8 revision[4];
	u64 capacity;
	u32 block_size;
	u8 dev_type;

	जोड़ अणु
		u8 dev_status;
	    #घोषणा VDADEVSTAT_INVALID   0x00
	    #घोषणा VDADEVSTAT_CORRUPT   VDADEVSTAT_INVALID
	    #घोषणा VDADEVSTAT_ASSIGNED  0x01
	    #घोषणा VDADEVSTAT_SPARE     0x02
	    #घोषणा VDADEVSTAT_UNAVAIL   0x03
	    #घोषणा VDADEVSTAT_PT_MAINT  0x04
	    #घोषणा VDADEVSTAT_LCLSPARE  0x05
	    #घोषणा VDADEVSTAT_UNUSEABLE 0x06
	    #घोषणा VDADEVSTAT_AVAIL     0xFF

		u8 op_ctrl;
	    #घोषणा VDA_DEV_OP_CTRL_START   0x01
	    #घोषणा VDA_DEV_OP_CTRL_HALT    0x02
	    #घोषणा VDA_DEV_OP_CTRL_RESUME  0x03
	    #घोषणा VDA_DEV_OP_CTRL_CANCEL  0x04
	पूर्ण;

	u8 member_state;
	#घोषणा VDAMBRSTATE_ONLINE   0x00
	#घोषणा VDAMBRSTATE_DEGRADED 0x01
	#घोषणा VDAMBRSTATE_UNAVAIL  0x02
	#घोषणा VDAMBRSTATE_FAULTED  0x03
	#घोषणा VDAMBRSTATE_MISREAD  0x04
	#घोषणा VDAMBRSTATE_INCOMPAT 0x05

	u8 operation;
	#घोषणा VDAOP_NONE           0x00
	#घोषणा VDAOP_REBUILD        0x01
	#घोषणा VDAOP_ERASE          0x02
	#घोषणा VDAOP_PATTERN        0x03
	#घोषणा VDAOP_CONVERSION     0x04
	#घोषणा VDAOP_FULL_INIT      0x05
	#घोषणा VDAOP_QUICK_INIT     0x06
	#घोषणा VDAOP_SECT_SCAN      0x07
	#घोषणा VDAOP_SECT_SCAN_PARITY      0x08
	#घोषणा VDAOP_SECT_SCAN_PARITY_FIX  0x09
	#घोषणा VDAOP_RECOV_REBUILD  0x0A

	u8 op_status;
	#घोषणा VDAOPSTAT_OK         0x00
	#घोषणा VDAOPSTAT_FAULTED    0x01
	#घोषणा VDAOPSTAT_HALTED     0x02
	#घोषणा VDAOPSTAT_INT        0x03

	u8 progress; /* 0 - 100% */
	u16 ses_dev_index;
	#घोषणा VDASESDI_INVALID     0xFFFF

	u8 serial_no[32];

	जोड़ अणु
		u16 target_id;
	#घोषणा VDATGTID_INVALID     0xFFFF

		u16 features_mask;
	पूर्ण;

	u16 lun;
	u16 features;
	#घोषणा VDADEVFEAT_ENC_SERV  0x0001
	#घोषणा VDADEVFEAT_IDENT     0x0002
	#घोषणा VDADEVFEAT_DH_SUPP   0x0004
	#घोषणा VDADEVFEAT_PHYS_ID   0x0008

	u8 ses_element_id;
	u8 link_speed;
	#घोषणा VDALINKSPEED_UNKNOWN 0x00
	#घोषणा VDALINKSPEED_1GB     0x01
	#घोषणा VDALINKSPEED_1_5GB   0x02
	#घोषणा VDALINKSPEED_2GB     0x03
	#घोषणा VDALINKSPEED_3GB     0x04
	#घोषणा VDALINKSPEED_4GB     0x05
	#घोषणा VDALINKSPEED_6GB     0x06
	#घोषणा VDALINKSPEED_8GB     0x07

	u16 phys_target_id;
	u8 reserved[2];
पूर्ण;


/*! काष्ठा atto_vda_devinfo2 is a replacement क्रम atto_vda_devinfo.  it
 * extends beyond the 0x70 bytes allowed in atto_vda_mgmt_req; thereक्रमe,
 * the entire काष्ठाure is DMaed between the firmware and host buffer and
 * the data will always be in little endian क्रमmat.
 */

काष्ठा __packed atto_vda_devinfo2 अणु
	काष्ठा atto_dev_addr dev_addr;
	u8 venकरोr_id[8];
	u8 product_id[16];
	u8 revision[4];
	u64 capacity;
	u32 block_size;
	u8 dev_type;
	u8 dev_status;
	u8 member_state;
	u8 operation;
	u8 op_status;
	u8 progress;
	u16 ses_dev_index;
	u8 serial_no[32];
	जोड़ अणु
		u16 target_id;
		u16 features_mask;
	पूर्ण;

	u16 lun;
	u16 features;
	u8 ses_element_id;
	u8 link_speed;
	u16 phys_target_id;
	u8 reserved[2];

/* This is where fields specअगरic to काष्ठा atto_vda_devinfo2 begin.  Note
 * that the काष्ठाure version started at one so applications that जोड़ize this
 * काष्ठाure with atto_vda_dev_info can dअगरferentiate them अगर desired.
 */

	u8 version;
	#घोषणा VDADEVINFO_VERSION0         0x00
	#घोषणा VDADEVINFO_VERSION1         0x01
	#घोषणा VDADEVINFO_VERSION2         0x02
	#घोषणा VDADEVINFO_VERSION3         0x03
	#घोषणा VDADEVINFO_VERSION          VDADEVINFO_VERSION3

	u8 reserved2[3];

	/* sector scanning fields */

	u32 ss_curr_errors;
	u64 ss_curr_scanned;
	u32 ss_curr_recvrd;
	u32 ss_scan_length;
	u32 ss_total_errors;
	u32 ss_total_recvrd;
	u32 ss_num_scans;

	/* grp_name was added in version 2 of this काष्ठाure. */

	अक्षर grp_name[15];
	u8 reserved3[4];

	/* dev_addr_list was added in version 3 of this काष्ठाure. */

	u8 num_dev_addr;
	काष्ठा atto_dev_addr2 dev_addr_list[8];
पूर्ण;


काष्ठा __packed atto_vda_grp_info अणु
	u8 grp_index;
	#घोषणा VDA_MAX_RAID_GROUPS         32

	अक्षर grp_name[15];
	u64 capacity;
	u32 block_size;
	u32 पूर्णांकerleave;
	u8 type;
	#घोषणा VDA_GRP_TYPE_RAID0          0
	#घोषणा VDA_GRP_TYPE_RAID1          1
	#घोषणा VDA_GRP_TYPE_RAID4          4
	#घोषणा VDA_GRP_TYPE_RAID5          5
	#घोषणा VDA_GRP_TYPE_RAID6          6
	#घोषणा VDA_GRP_TYPE_RAID10         10
	#घोषणा VDA_GRP_TYPE_RAID40         40
	#घोषणा VDA_GRP_TYPE_RAID50         50
	#घोषणा VDA_GRP_TYPE_RAID60         60
	#घोषणा VDA_GRP_TYPE_DVRAID_HS      252
	#घोषणा VDA_GRP_TYPE_DVRAID_NOHS    253
	#घोषणा VDA_GRP_TYPE_JBOD           254
	#घोषणा VDA_GRP_TYPE_SPARE          255

	जोड़ अणु
		u8 status;
	    #घोषणा VDA_GRP_STAT_INVALID  0x00
	    #घोषणा VDA_GRP_STAT_NEW      0x01
	    #घोषणा VDA_GRP_STAT_WAITING  0x02
	    #घोषणा VDA_GRP_STAT_ONLINE   0x03
	    #घोषणा VDA_GRP_STAT_DEGRADED 0x04
	    #घोषणा VDA_GRP_STAT_OFFLINE  0x05
	    #घोषणा VDA_GRP_STAT_DELETED  0x06
	    #घोषणा VDA_GRP_STAT_RECOV_BASIC    0x07
	    #घोषणा VDA_GRP_STAT_RECOV_EXTREME  0x08

		u8 op_ctrl;
	    #घोषणा VDA_GRP_OP_CTRL_START   0x01
	    #घोषणा VDA_GRP_OP_CTRL_HALT    0x02
	    #घोषणा VDA_GRP_OP_CTRL_RESUME  0x03
	    #घोषणा VDA_GRP_OP_CTRL_CANCEL  0x04
	पूर्ण;

	u8 rebuild_state;
	#घोषणा VDA_RBLD_NONE      0x00
	#घोषणा VDA_RBLD_REBUILD   0x01
	#घोषणा VDA_RBLD_ERASE     0x02
	#घोषणा VDA_RBLD_PATTERN   0x03
	#घोषणा VDA_RBLD_CONV      0x04
	#घोषणा VDA_RBLD_FULL_INIT 0x05
	#घोषणा VDA_RBLD_QUICK_INIT 0x06
	#घोषणा VDA_RBLD_SECT_SCAN 0x07
	#घोषणा VDA_RBLD_SECT_SCAN_PARITY     0x08
	#घोषणा VDA_RBLD_SECT_SCAN_PARITY_FIX 0x09
	#घोषणा VDA_RBLD_RECOV_REBUILD 0x0A
	#घोषणा VDA_RBLD_RECOV_BASIC   0x0B
	#घोषणा VDA_RBLD_RECOV_EXTREME 0x0C

	u8 span_depth;
	u8 progress;
	u8 mirror_width;
	u8 stripe_width;
	u8 member_cnt;

	जोड़ अणु
		u16 members[32];
	#घोषणा VDA_MEMBER_MISSING  0xFFFF
	#घोषणा VDA_MEMBER_NEW      0xFFFE
		u16 features_mask;
	पूर्ण;

	u16 features;
	#घोषणा VDA_GRP_FEAT_HOTSWAP    0x0001
	#घोषणा VDA_GRP_FEAT_SPDRD_MASK 0x0006
	#घोषणा VDA_GRP_FEAT_SPDRD_DIS  0x0000
	#घोषणा VDA_GRP_FEAT_SPDRD_ENB  0x0002
	#घोषणा VDA_GRP_FEAT_SPDRD_AUTO 0x0004
	#घोषणा VDA_GRP_FEAT_IDENT      0x0008
	#घोषणा VDA_GRP_FEAT_RBLDPRI_MASK 0x0030
	#घोषणा VDA_GRP_FEAT_RBLDPRI_LOW  0x0010
	#घोषणा VDA_GRP_FEAT_RBLDPRI_SAME 0x0020
	#घोषणा VDA_GRP_FEAT_RBLDPRI_HIGH 0x0030
	#घोषणा VDA_GRP_FEAT_WRITE_CACHE  0x0040
	#घोषणा VDA_GRP_FEAT_RBLD_RESUME  0x0080
	#घोषणा VDA_GRP_FEAT_SECT_RESUME  0x0100
	#घोषणा VDA_GRP_FEAT_INIT_RESUME  0x0200
	#घोषणा VDA_GRP_FEAT_SSD          0x0400
	#घोषणा VDA_GRP_FEAT_BOOT_DEV     0x0800

	/*
	 * क्रम backward compatibility, a prefetch value of zero means the
	 * setting is ignored/unsupported.  thereक्रमe, the firmware supported
	 * 0-6 values are incremented to 1-7.
	 */

	u8 prefetch;
	u8 op_status;
	#घोषणा VDAGRPOPSTAT_MASK       0x0F
	#घोषणा VDAGRPOPSTAT_INVALID    0x00
	#घोषणा VDAGRPOPSTAT_OK         0x01
	#घोषणा VDAGRPOPSTAT_FAULTED    0x02
	#घोषणा VDAGRPOPSTAT_HALTED     0x03
	#घोषणा VDAGRPOPSTAT_INT        0x04
	#घोषणा VDAGRPOPPROC_MASK       0xF0
	#घोषणा VDAGRPOPPROC_STARTABLE  0x10
	#घोषणा VDAGRPOPPROC_CANCELABLE 0x20
	#घोषणा VDAGRPOPPROC_RESUMABLE  0x40
	#घोषणा VDAGRPOPPROC_HALTABLE   0x80
	u8 over_provision;
	u8 reserved[3];

पूर्ण;


काष्ठा __packed atto_vdapart_info अणु
	u8 part_no;
	#घोषणा VDA_MAX_PARTITIONS   128

	अक्षर grp_name[15];
	u64 part_size;
	u64 start_lba;
	u32 block_size;
	u16 target_id;
	u8 LUN;
	अक्षर serial_no[41];
	u8 features;
	#घोषणा VDAPI_FEAT_WRITE_CACHE   0x01

	u8 reserved[7];
पूर्ण;


काष्ठा __packed atto_vda_dh_info अणु
	u8 req_type;
	#घोषणा VDADH_RQTYPE_CACHE      0x01
	#घोषणा VDADH_RQTYPE_FETCH      0x02
	#घोषणा VDADH_RQTYPE_SET_STAT   0x03
	#घोषणा VDADH_RQTYPE_GET_STAT   0x04

	u8 req_qual;
	#घोषणा VDADH_RQQUAL_SMART      0x01
	#घोषणा VDADH_RQQUAL_MEDDEF     0x02
	#घोषणा VDADH_RQQUAL_INFOEXC    0x04

	u8 num_smart_attribs;
	u8 status;
	#घोषणा VDADH_STAT_DISABLE      0x00
	#घोषणा VDADH_STAT_ENABLE       0x01

	u32 med_defect_cnt;
	u32 info_exc_cnt;
	u8 smart_status;
	#घोषणा VDADH_SMARTSTAT_OK      0x00
	#घोषणा VDADH_SMARTSTAT_ERR     0x01

	u8 reserved[35];
	काष्ठा atto_vda_sge sge[1];
पूर्ण;


काष्ठा __packed atto_vda_dh_smart अणु
	u8 attrib_id;
	u8 current_val;
	u8 worst;
	u8 threshold;
	u8 raw_data[6];
	u8 raw_attrib_status;
	#घोषणा VDADHSM_RAWSTAT_PREFAIL_WARRANTY        0x01
	#घोषणा VDADHSM_RAWSTAT_ONLINE_COLLECTION       0x02
	#घोषणा VDADHSM_RAWSTAT_PERFORMANCE_ATTR        0x04
	#घोषणा VDADHSM_RAWSTAT_ERROR_RATE_ATTR         0x08
	#घोषणा VDADHSM_RAWSTAT_EVENT_COUNT_ATTR        0x10
	#घोषणा VDADHSM_RAWSTAT_SELF_PRESERVING_ATTR    0x20

	u8 calc_attrib_status;
	#घोषणा VDADHSM_CALCSTAT_UNKNOWN                0x00
	#घोषणा VDADHSM_CALCSTAT_GOOD                   0x01
	#घोषणा VDADHSM_CALCSTAT_PREFAIL                0x02
	#घोषणा VDADHSM_CALCSTAT_OLDAGE                 0x03

	u8 reserved[4];
पूर्ण;


काष्ठा __packed atto_vda_metrics_info अणु
	u8 data_version;
	#घोषणा VDAMET_VERSION0         0x00
	#घोषणा VDAMET_VERSION          VDAMET_VERSION0

	u8 metrics_action;
	#घोषणा VDAMET_METACT_NONE      0x00
	#घोषणा VDAMET_METACT_START     0x01
	#घोषणा VDAMET_METACT_STOP      0x02
	#घोषणा VDAMET_METACT_RETRIEVE  0x03
	#घोषणा VDAMET_METACT_CLEAR     0x04

	u8 test_action;
	#घोषणा VDAMET_TSTACT_NONE              0x00
	#घोषणा VDAMET_TSTACT_STRT_INIT         0x01
	#घोषणा VDAMET_TSTACT_STRT_READ         0x02
	#घोषणा VDAMET_TSTACT_STRT_VERIFY       0x03
	#घोषणा VDAMET_TSTACT_STRT_INIT_VERIFY  0x04
	#घोषणा VDAMET_TSTACT_STOP              0x05

	u8 num_dev_indexes;
	#घोषणा VDAMET_ALL_DEVICES      0xFF

	u16 dev_indexes[32];
	u8 reserved[12];
	काष्ठा atto_vda_sge sge[1];
पूर्ण;


काष्ठा __packed atto_vda_metrics_data अणु
	u16 dev_index;
	u16 length;
	#घोषणा VDAMD_LEN_LAST          0x8000
	#घोषणा VDAMD_LEN_MASK          0x0FFF

	u32 flags;
	#घोषणा VDAMDF_RUN          0x00000007
	#घोषणा VDAMDF_RUN_READ     0x00000001
	#घोषणा VDAMDF_RUN_WRITE    0x00000002
	#घोषणा VDAMDF_RUN_ALL      0x00000004
	#घोषणा VDAMDF_READ         0x00000010
	#घोषणा VDAMDF_WRITE        0x00000020
	#घोषणा VDAMDF_ALL          0x00000040
	#घोषणा VDAMDF_DRIVETEST    0x40000000
	#घोषणा VDAMDF_NEW          0x80000000

	u64 total_पढ़ो_data;
	u64 total_ग_लिखो_data;
	u64 total_पढ़ो_io;
	u64 total_ग_लिखो_io;
	u64 पढ़ो_start_समय;
	u64 पढ़ो_stop_समय;
	u64 ग_लिखो_start_समय;
	u64 ग_लिखो_stop_समय;
	u64 पढ़ो_maxio_समय;
	u64 wpvdadmetricsdatarite_maxio_समय;
	u64 पढ़ो_totalio_समय;
	u64 ग_लिखो_totalio_समय;
	u64 पढ़ो_total_errs;
	u64 ग_लिखो_total_errs;
	u64 पढ़ो_recvrd_errs;
	u64 ग_लिखो_recvrd_errs;
	u64 miscompares;
पूर्ण;


काष्ठा __packed atto_vda_schedule_info अणु
	u8 schedule_type;
	#घोषणा VDASI_SCHTYPE_ONETIME   0x01
	#घोषणा VDASI_SCHTYPE_DAILY     0x02
	#घोषणा VDASI_SCHTYPE_WEEKLY    0x03

	u8 operation;
	#घोषणा VDASI_OP_NONE           0x00
	#घोषणा VDASI_OP_CREATE         0x01
	#घोषणा VDASI_OP_CANCEL         0x02

	u8 hour;
	u8 minute;
	u8 day;
	#घोषणा VDASI_DAY_NONE          0x00

	u8 progress;
	#घोषणा VDASI_PROG_NONE         0xFF

	u8 event_type;
	#घोषणा VDASI_EVTTYPE_SECT_SCAN             0x01
	#घोषणा VDASI_EVTTYPE_SECT_SCAN_PARITY      0x02
	#घोषणा VDASI_EVTTYPE_SECT_SCAN_PARITY_FIX  0x03

	u8 recurrences;
	#घोषणा VDASI_RECUR_FOREVER     0x00

	u32 id;
	#घोषणा VDASI_ID_NONE           0x00

	अक्षर grp_name[15];
	u8 reserved[85];
पूर्ण;


काष्ठा __packed atto_vda_n_vcache_info अणु
	u8 super_cap_status;
	#घोषणा VDANVCI_SUPERCAP_NOT_PRESENT       0x00
	#घोषणा VDANVCI_SUPERCAP_FULLY_CHARGED     0x01
	#घोषणा VDANVCI_SUPERCAP_NOT_CHARGED       0x02

	u8 nvcache_module_status;
	#घोषणा VDANVCI_NVCACHEMODULE_NOT_PRESENT  0x00
	#घोषणा VDANVCI_NVCACHEMODULE_PRESENT      0x01

	u8 protection_mode;
	#घोषणा VDANVCI_PROTMODE_HI_PROTECT        0x00
	#घोषणा VDANVCI_PROTMODE_HI_PERFORM        0x01

	u8 reserved[109];
पूर्ण;


काष्ठा __packed atto_vda_buzzer_info अणु
	u8 status;
	#घोषणा VDABUZZI_BUZZER_OFF           0x00
	#घोषणा VDABUZZI_BUZZER_ON            0x01
	#घोषणा VDABUZZI_BUZZER_LAST          0x02

	u8 reserved[3];
	u32 duration;
	#घोषणा VDABUZZI_DURATION_INDEFINITE  0xffffffff

	u8 reserved2[104];
पूर्ण;


काष्ठा  __packed atto_vda_adapter_info अणु
	u8 version;
	#घोषणा VDAADAPINFO_VERSION0         0x00
	#घोषणा VDAADAPINFO_VERSION          VDAADAPINFO_VERSION0

	u8 reserved;
	चिन्हित लघु utc_offset;
	u32 utc_समय;
	u32 features;
	#घोषणा VDA_ADAP_FEAT_IDENT     0x0001
	#घोषणा VDA_ADAP_FEAT_BUZZ_ERR  0x0002
	#घोषणा VDA_ADAP_FEAT_UTC_TIME  0x0004

	u32 valid_features;
	अक्षर active_config[33];
	u8 temp_count;
	u8 fan_count;
	u8 reserved3[61];
पूर्ण;


काष्ठा __packed atto_vda_temp_info अणु
	u8 temp_index;
	u8 max_op_temp;
	u8 min_op_temp;
	u8 op_temp_warn;
	u8 temperature;
	u8 type;
	#घोषणा VDA_TEMP_TYPE_CPU  1

	u8 reserved[106];
पूर्ण;


काष्ठा __packed atto_vda_fan_info अणु
	u8 fan_index;
	u8 status;
	#घोषणा VDA_FAN_STAT_UNKNOWN 0
	#घोषणा VDA_FAN_STAT_NORMAL  1
	#घोषणा VDA_FAN_STAT_FAIL    2

	u16 crit_pvdafaninfothreshold;
	u16 warn_threshold;
	u16 speed;
	u8 reserved[104];
पूर्ण;


/* VDA management commands */

#घोषणा VDAMGT_DEV_SCAN         0x00
#घोषणा VDAMGT_DEV_INFO         0x01
#घोषणा VDAMGT_DEV_CLEAN        0x02
#घोषणा VDAMGT_DEV_IDENTIFY     0x03
#घोषणा VDAMGT_DEV_IDENTSTOP    0x04
#घोषणा VDAMGT_DEV_PT_INFO      0x05
#घोषणा VDAMGT_DEV_FEATURES     0x06
#घोषणा VDAMGT_DEV_PT_FEATURES  0x07
#घोषणा VDAMGT_DEV_HEALTH_REQ   0x08
#घोषणा VDAMGT_DEV_METRICS      0x09
#घोषणा VDAMGT_DEV_INFO2        0x0A
#घोषणा VDAMGT_DEV_OPERATION    0x0B
#घोषणा VDAMGT_DEV_INFO2_BYADDR 0x0C
#घोषणा VDAMGT_GRP_INFO         0x10
#घोषणा VDAMGT_GRP_CREATE       0x11
#घोषणा VDAMGT_GRP_DELETE       0x12
#घोषणा VDAMGT_ADD_STORAGE      0x13
#घोषणा VDAMGT_MEMBER_ADD       0x14
#घोषणा VDAMGT_GRP_COMMIT       0x15
#घोषणा VDAMGT_GRP_REBUILD      0x16
#घोषणा VDAMGT_GRP_COMMIT_INIT  0x17
#घोषणा VDAMGT_QUICK_RAID       0x18
#घोषणा VDAMGT_GRP_FEATURES     0x19
#घोषणा VDAMGT_GRP_COMMIT_INIT_AUTOMAP  0x1A
#घोषणा VDAMGT_QUICK_RAID_INIT_AUTOMAP  0x1B
#घोषणा VDAMGT_GRP_OPERATION    0x1C
#घोषणा VDAMGT_CFG_SAVE         0x20
#घोषणा VDAMGT_LAST_ERROR       0x21
#घोषणा VDAMGT_ADAP_INFO        0x22
#घोषणा VDAMGT_ADAP_FEATURES    0x23
#घोषणा VDAMGT_TEMP_INFO        0x24
#घोषणा VDAMGT_FAN_INFO         0x25
#घोषणा VDAMGT_PART_INFO        0x30
#घोषणा VDAMGT_PART_MAP         0x31
#घोषणा VDAMGT_PART_UNMAP       0x32
#घोषणा VDAMGT_PART_AUTOMAP     0x33
#घोषणा VDAMGT_PART_SPLIT       0x34
#घोषणा VDAMGT_PART_MERGE       0x35
#घोषणा VDAMGT_SPARE_LIST       0x40
#घोषणा VDAMGT_SPARE_ADD        0x41
#घोषणा VDAMGT_SPARE_REMOVE     0x42
#घोषणा VDAMGT_LOCAL_SPARE_ADD  0x43
#घोषणा VDAMGT_SCHEDULE_EVENT   0x50
#घोषणा VDAMGT_SCHEDULE_INFO    0x51
#घोषणा VDAMGT_NVCACHE_INFO     0x60
#घोषणा VDAMGT_NVCACHE_SET      0x61
#घोषणा VDAMGT_BUZZER_INFO      0x70
#घोषणा VDAMGT_BUZZER_SET       0x71


काष्ठा __packed atto_vda_ae_hdr अणु
	u8 bylength;
	u8 byflags;
	#घोषणा VDAAE_HDRF_EVENT_ACK    0x01

	u8 byversion;
	#घोषणा VDAAE_HDR_VER_0         0

	u8 bytype;
	#घोषणा VDAAE_HDR_TYPE_RAID     1
	#घोषणा VDAAE_HDR_TYPE_LU       2
	#घोषणा VDAAE_HDR_TYPE_DISK     3
	#घोषणा VDAAE_HDR_TYPE_RESET    4
	#घोषणा VDAAE_HDR_TYPE_LOG_INFO 5
	#घोषणा VDAAE_HDR_TYPE_LOG_WARN 6
	#घोषणा VDAAE_HDR_TYPE_LOG_CRIT 7
	#घोषणा VDAAE_HDR_TYPE_LOG_FAIL 8
	#घोषणा VDAAE_HDR_TYPE_NVC      9
	#घोषणा VDAAE_HDR_TYPE_TLG_INFO 10
	#घोषणा VDAAE_HDR_TYPE_TLG_WARN 11
	#घोषणा VDAAE_HDR_TYPE_TLG_CRIT 12
	#घोषणा VDAAE_HDR_TYPE_PWRMGT   13
	#घोषणा VDAAE_HDR_TYPE_MUTE     14
	#घोषणा VDAAE_HDR_TYPE_DEV      15
पूर्ण;


काष्ठा  __packed atto_vda_ae_raid अणु
	काष्ठा atto_vda_ae_hdr hdr;
	u32 dwflags;
	#घोषणा VDAAE_GROUP_STATE   0x00000001
	#घोषणा VDAAE_RBLD_STATE    0x00000002
	#घोषणा VDAAE_RBLD_PROG     0x00000004
	#घोषणा VDAAE_MEMBER_CHG    0x00000008
	#घोषणा VDAAE_PART_CHG      0x00000010
	#घोषणा VDAAE_MEM_STATE_CHG 0x00000020

	u8 bygroup_state;
	#घोषणा VDAAE_RAID_INVALID  0
	#घोषणा VDAAE_RAID_NEW      1
	#घोषणा VDAAE_RAID_WAITING  2
	#घोषणा VDAAE_RAID_ONLINE   3
	#घोषणा VDAAE_RAID_DEGRADED 4
	#घोषणा VDAAE_RAID_OFFLINE  5
	#घोषणा VDAAE_RAID_DELETED  6
	#घोषणा VDAAE_RAID_BASIC    7
	#घोषणा VDAAE_RAID_EXTREME  8
	#घोषणा VDAAE_RAID_UNKNOWN  9

	u8 byrebuild_state;
	#घोषणा VDAAE_RBLD_NONE       0
	#घोषणा VDAAE_RBLD_REBUILD    1
	#घोषणा VDAAE_RBLD_ERASE      2
	#घोषणा VDAAE_RBLD_PATTERN    3
	#घोषणा VDAAE_RBLD_CONV       4
	#घोषणा VDAAE_RBLD_FULL_INIT  5
	#घोषणा VDAAE_RBLD_QUICK_INIT 6
	#घोषणा VDAAE_RBLD_SECT_SCAN  7
	#घोषणा VDAAE_RBLD_SECT_SCAN_PARITY     8
	#घोषणा VDAAE_RBLD_SECT_SCAN_PARITY_FIX 9
	#घोषणा VDAAE_RBLD_RECOV_REBUILD 10
	#घोषणा VDAAE_RBLD_UNKNOWN    11

	u8 byrebuild_progress;
	u8 op_status;
	#घोषणा VDAAE_GRPOPSTAT_MASK       0x0F
	#घोषणा VDAAE_GRPOPSTAT_INVALID    0x00
	#घोषणा VDAAE_GRPOPSTAT_OK         0x01
	#घोषणा VDAAE_GRPOPSTAT_FAULTED    0x02
	#घोषणा VDAAE_GRPOPSTAT_HALTED     0x03
	#घोषणा VDAAE_GRPOPSTAT_INT        0x04
	#घोषणा VDAAE_GRPOPPROC_MASK       0xF0
	#घोषणा VDAAE_GRPOPPROC_STARTABLE  0x10
	#घोषणा VDAAE_GRPOPPROC_CANCELABLE 0x20
	#घोषणा VDAAE_GRPOPPROC_RESUMABLE  0x40
	#घोषणा VDAAE_GRPOPPROC_HALTABLE   0x80
	अक्षर acname[15];
	u8 byreserved;
	u8 byreserved2[0x80 - 0x1C];
पूर्ण;


काष्ठा __packed atto_vda_ae_lu_tgt_lun अणु
	u16 wtarget_id;
	u8 bylun;
	u8 byreserved;
पूर्ण;


काष्ठा __packed atto_vda_ae_lu_tgt_lun_raid अणु
	u16 wtarget_id;
	u8 bylun;
	u8 byreserved;
	u32 dwपूर्णांकerleave;
	u32 dwblock_size;
पूर्ण;


काष्ठा __packed atto_vda_ae_lu अणु
	काष्ठा atto_vda_ae_hdr hdr;
	u32 dwevent;
	#घोषणा VDAAE_LU_DISC        0x00000001
	#घोषणा VDAAE_LU_LOST        0x00000002
	#घोषणा VDAAE_LU_STATE       0x00000004
	#घोषणा VDAAE_LU_PASSTHROUGH 0x10000000
	#घोषणा VDAAE_LU_PHYS_ID     0x20000000

	u8 bystate;
	#घोषणा VDAAE_LU_UNDEFINED        0
	#घोषणा VDAAE_LU_NOT_PRESENT      1
	#घोषणा VDAAE_LU_OFFLINE          2
	#घोषणा VDAAE_LU_ONLINE           3
	#घोषणा VDAAE_LU_DEGRADED         4
	#घोषणा VDAAE_LU_FACTORY_DISABLED 5
	#घोषणा VDAAE_LU_DELETED          6
	#घोषणा VDAAE_LU_BUSSCAN          7
	#घोषणा VDAAE_LU_UNKNOWN          8

	u8 byreserved;
	u16 wphys_target_id;

	जोड़ अणु
		काष्ठा atto_vda_ae_lu_tgt_lun tgtlun;
		काष्ठा atto_vda_ae_lu_tgt_lun_raid tgtlun_raid;
	पूर्ण id;
पूर्ण;


काष्ठा __packed atto_vda_ae_disk अणु
	काष्ठा atto_vda_ae_hdr hdr;
पूर्ण;


#घोषणा VDAAE_LOG_STRSZ 64

काष्ठा __packed atto_vda_ae_log अणु
	काष्ठा atto_vda_ae_hdr hdr;
	अक्षर aclog_ascii[VDAAE_LOG_STRSZ];
पूर्ण;


#घोषणा VDAAE_TLG_STRSZ 56

काष्ठा __packed atto_vda_ae_बारtamp_log अणु
	काष्ठा atto_vda_ae_hdr hdr;
	u32 dwबारtamp;
	अक्षर aclog_ascii[VDAAE_TLG_STRSZ];
पूर्ण;


काष्ठा __packed atto_vda_ae_nvc अणु
	काष्ठा atto_vda_ae_hdr hdr;
पूर्ण;


काष्ठा __packed atto_vda_ae_dev अणु
	काष्ठा atto_vda_ae_hdr hdr;
	काष्ठा atto_dev_addr devaddr;
पूर्ण;


जोड़ atto_vda_ae अणु
	काष्ठा atto_vda_ae_hdr hdr;
	काष्ठा atto_vda_ae_disk disk;
	काष्ठा atto_vda_ae_lu lu;
	काष्ठा atto_vda_ae_raid raid;
	काष्ठा atto_vda_ae_log log;
	काष्ठा atto_vda_ae_बारtamp_log tslog;
	काष्ठा atto_vda_ae_nvc nvcache;
	काष्ठा atto_vda_ae_dev dev;
पूर्ण;


काष्ठा __packed atto_vda_date_and_समय अणु
	u8 flags;
	#घोषणा VDA_DT_DAY_MASK   0x07
	#घोषणा VDA_DT_DAY_NONE   0x00
	#घोषणा VDA_DT_DAY_SUN    0x01
	#घोषणा VDA_DT_DAY_MON    0x02
	#घोषणा VDA_DT_DAY_TUE    0x03
	#घोषणा VDA_DT_DAY_WED    0x04
	#घोषणा VDA_DT_DAY_THU    0x05
	#घोषणा VDA_DT_DAY_FRI    0x06
	#घोषणा VDA_DT_DAY_SAT    0x07
	#घोषणा VDA_DT_PM         0x40
	#घोषणा VDA_DT_MILITARY   0x80

	u8 seconds;
	u8 minutes;
	u8 hours;
	u8 day;
	u8 month;
	u16 year;
पूर्ण;

#घोषणा SGE_LEN_LIMIT   0x003FFFFF      /*! mask of segment length            */
#घोषणा SGE_LEN_MAX     0x003FF000      /*! maximum segment length            */
#घोषणा SGE_LAST        0x01000000      /*! last entry                        */
#घोषणा SGE_ADDR_64     0x04000000      /*! 64-bit addressing flag            */
#घोषणा SGE_CHAIN       0x80000000      /*! chain descriptor flag             */
#घोषणा SGE_CHAIN_LEN   0x0000FFFF      /*! mask of length in chain entries   */
#घोषणा SGE_CHAIN_SZ    0x00FF0000      /*! mask of size of chained buffer    */


काष्ठा __packed atto_vda_cfg_init अणु
	काष्ठा atto_vda_date_and_समय date_समय;
	u32 sgl_page_size;
	u32 vda_version;
	u32 fw_version;
	u32 fw_build;
	u32 fw_release;
	u32 epoch_समय;
	u32 ioctl_tunnel;
	#घोषणा VDA_ITF_MEM_RW           0x00000001
	#घोषणा VDA_ITF_TRACE            0x00000002
	#घोषणा VDA_ITF_SCSI_PASS_THRU   0x00000004
	#घोषणा VDA_ITF_GET_DEV_ADDR     0x00000008
	#घोषणा VDA_ITF_PHY_CTRL         0x00000010
	#घोषणा VDA_ITF_CONN_CTRL        0x00000020
	#घोषणा VDA_ITF_GET_DEV_INFO     0x00000040

	u32 num_tarमाला_लो_backend;
	u8 reserved[0x48];
पूर्ण;


/* configuration commands */

#घोषणा VDA_CFG_INIT          0x00
#घोषणा VDA_CFG_GET_INIT      0x01
#घोषणा VDA_CFG_GET_INIT2     0x02


/*! physical region descriptor (PRD) aka scatter/gather entry */

काष्ठा __packed atto_physical_region_description अणु
	u64 address;
	u32 ctl_len;
	#घोषणा PRD_LEN_LIMIT       0x003FFFFF
	#घोषणा PRD_LEN_MAX         0x003FF000
	#घोषणा PRD_NXT_PRD_CNT     0x0000007F
	#घोषणा PRD_CHAIN           0x01000000
	#घोषणा PRD_DATA            0x00000000
	#घोषणा PRD_INT_SEL         0xF0000000
	  #घोषणा PRD_INT_SEL_F0    0x00000000
	  #घोषणा PRD_INT_SEL_F1    0x40000000
	  #घोषणा PRD_INT_SEL_F2    0x80000000
	  #घोषणा PRD_INT_SEL_F3    0xc0000000
	  #घोषणा PRD_INT_SEL_SRAM  0x10000000
	  #घोषणा PRD_INT_SEL_PBSR  0x20000000

पूर्ण;

/* Request types. NOTE that ALL requests have the same layout क्रम the first
 * few bytes.
 */
काष्ठा __packed atto_vda_req_header अणु
	u32 length;
	u8 function;
	u8 variable1;
	u8 chain_offset;
	u8 sg_list_offset;
	u32 handle;
पूर्ण;


#घोषणा FCP_CDB_SIZE    16

काष्ठा __packed atto_vda_scsi_req अणु
	u32 length;
	u8 function;  /* VDA_FUNC_SCSI */
	u8 sense_len;
	u8 chain_offset;
	u8 sg_list_offset;
	u32 handle;
	u32 flags;
     #घोषणा FCP_CMND_LUN_MASK    0x000000FF
     #घोषणा FCP_CMND_TA_MASK     0x00000700
      #घोषणा FCP_CMND_TA_SIMPL_Q 0x00000000
      #घोषणा FCP_CMND_TA_HEAD_Q  0x00000100
      #घोषणा FCP_CMND_TA_ORDRD_Q 0x00000200
      #घोषणा FCP_CMND_TA_ACA     0x00000400
     #घोषणा FCP_CMND_PRI_MASK    0x00007800
     #घोषणा FCP_CMND_TM_MASK     0x00FF0000
      #घोषणा FCP_CMND_ATS        0x00020000
      #घोषणा FCP_CMND_CTS        0x00040000
      #घोषणा FCP_CMND_LRS        0x00100000
      #घोषणा FCP_CMND_TRS        0x00200000
      #घोषणा FCP_CMND_CLA        0x00400000
      #घोषणा FCP_CMND_TRM        0x00800000
     #घोषणा FCP_CMND_DATA_सूची    0x03000000
      #घोषणा FCP_CMND_WRD        0x01000000
      #घोषणा FCP_CMND_RDD        0x02000000

	u8 cdb[FCP_CDB_SIZE];
	जोड़ अणु
		काष्ठा __packed अणु
			u64 ppsense_buf;
			u16 target_id;
			u8 iblk_cnt_prd;
			u8 reserved;
		पूर्ण;

		काष्ठा atto_physical_region_description sense_buff_prd;
	पूर्ण;

	जोड़ अणु
		काष्ठा atto_vda_sge sge[1];

		u32 पात_handle;
		u32 dwords[245];
		काष्ठा atto_physical_region_description prd[1];
	पूर्ण u;
पूर्ण;


काष्ठा __packed atto_vda_flash_req अणु
	u32 length;
	u8 function; /* VDA_FUNC_FLASH */
	u8 sub_func;
	u8 chain_offset;
	u8 sg_list_offset;
	u32 handle;
	u32 flash_addr;
	u8 checksum;
	u8 rsvd[3];

	जोड़ अणु
		काष्ठा अणु
			अक्षर file_name[16]; /* 8.3 fname, शून्य term, wc=* */
			काष्ठा atto_vda_sge sge[1];
		पूर्ण file;

		काष्ठा atto_vda_sge sge[1];
		काष्ठा atto_physical_region_description prde[2];
	पूर्ण data;
पूर्ण;


काष्ठा __packed atto_vda_diag_req अणु
	u32 length;
	u8 function; /* VDA_FUNC_DIAG */
	u8 sub_func;
	#घोषणा VDA_DIAG_STATUS   0x00
	#घोषणा VDA_DIAG_RESET    0x01
	#घोषणा VDA_DIAG_PAUSE    0x02
	#घोषणा VDA_DIAG_RESUME   0x03
	#घोषणा VDA_DIAG_READ     0x04
	#घोषणा VDA_DIAG_WRITE    0x05

	u8 chain_offset;
	u8 sg_list_offset;
	u32 handle;
	u32 rsvd;
	u64 local_addr;
	काष्ठा atto_vda_sge sge[1];
पूर्ण;


काष्ठा __packed atto_vda_ae_req अणु
	u32 length;
	u8 function; /* VDA_FUNC_AE */
	u8 reserved1;
	u8 chain_offset;
	u8 sg_list_offset;
	u32 handle;

	जोड़ अणु
		काष्ठा atto_vda_sge sge[1];
		काष्ठा atto_physical_region_description prde[1];
	पूर्ण;
पूर्ण;


काष्ठा __packed atto_vda_cli_req अणु
	u32 length;
	u8 function; /* VDA_FUNC_CLI */
	u8 reserved1;
	u8 chain_offset;
	u8 sg_list_offset;
	u32 handle;
	u32 cmd_rsp_len;
	काष्ठा atto_vda_sge sge[1];
पूर्ण;


काष्ठा __packed atto_vda_ioctl_req अणु
	u32 length;
	u8 function; /* VDA_FUNC_IOCTL */
	u8 sub_func;
	u8 chain_offset;
	u8 sg_list_offset;
	u32 handle;

	जोड़ अणु
		काष्ठा atto_vda_sge reserved_sge;
		काष्ठा atto_physical_region_description reserved_prde;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			u32 ctrl_code;
			u16 target_id;
			u8 lun;
			u8 reserved;
		पूर्ण csmi;
	पूर्ण;

	जोड़ अणु
		काष्ठा atto_vda_sge sge[1];
		काष्ठा atto_physical_region_description prde[1];
	पूर्ण;
पूर्ण;


काष्ठा __packed atto_vda_cfg_req अणु
	u32 length;
	u8 function; /* VDA_FUNC_CFG */
	u8 sub_func;
	u8 rsvd1;
	u8 sg_list_offset;
	u32 handle;

	जोड़ अणु
		u8 bytes[116];
		काष्ठा atto_vda_cfg_init init;
		काष्ठा atto_vda_sge sge;
		काष्ठा atto_physical_region_description prde;
	पूर्ण data;
पूर्ण;


काष्ठा __packed atto_vda_mgmt_req अणु
	u32 length;
	u8 function; /* VDA_FUNC_MGT */
	u8 mgt_func;
	u8 chain_offset;
	u8 sg_list_offset;
	u32 handle;
	u8 scan_generation;
	u8 payld_sglst_offset;
	u16 dev_index;
	u32 payld_length;
	u32 pad;
	जोड़ अणु
		काष्ठा atto_vda_sge sge[2];
		काष्ठा atto_physical_region_description prde[2];
	पूर्ण;
	काष्ठा atto_vda_sge payld_sge[1];
पूर्ण;


जोड़ atto_vda_req अणु
	काष्ठा atto_vda_scsi_req scsi;
	काष्ठा atto_vda_flash_req flash;
	काष्ठा atto_vda_diag_req diag;
	काष्ठा atto_vda_ae_req ae;
	काष्ठा atto_vda_cli_req cli;
	काष्ठा atto_vda_ioctl_req ioctl;
	काष्ठा atto_vda_cfg_req cfg;
	काष्ठा atto_vda_mgmt_req mgt;
	u8 bytes[1024];
पूर्ण;

/* Outbound response काष्ठाures */

काष्ठा __packed atto_vda_scsi_rsp अणु
	u8 scsi_stat;
	u8 sense_len;
	u8 rsvd[2];
	u32 residual_length;
पूर्ण;

काष्ठा __packed atto_vda_flash_rsp अणु
	u32 file_size;
पूर्ण;

काष्ठा __packed atto_vda_ae_rsp अणु
	u32 length;
पूर्ण;

काष्ठा __packed atto_vda_cli_rsp अणु
	u32 cmd_rsp_len;
पूर्ण;

काष्ठा __packed atto_vda_ioctl_rsp अणु
	जोड़ अणु
		काष्ठा अणु
			u32 csmi_status;
			u16 target_id;
			u8 lun;
			u8 reserved;
		पूर्ण csmi;
	पूर्ण;
पूर्ण;

काष्ठा __packed atto_vda_cfg_rsp अणु
	u16 vda_version;
	u16 fw_release;
	u32 fw_build;
पूर्ण;

काष्ठा __packed atto_vda_mgmt_rsp अणु
	u32 length;
	u16 dev_index;
	u8 scan_generation;
पूर्ण;

जोड़ atto_vda_func_rsp अणु
	काष्ठा atto_vda_scsi_rsp scsi_rsp;
	काष्ठा atto_vda_flash_rsp flash_rsp;
	काष्ठा atto_vda_ae_rsp ae_rsp;
	काष्ठा atto_vda_cli_rsp cli_rsp;
	काष्ठा atto_vda_ioctl_rsp ioctl_rsp;
	काष्ठा atto_vda_cfg_rsp cfg_rsp;
	काष्ठा atto_vda_mgmt_rsp mgt_rsp;
	u32 dwords[2];
पूर्ण;

काष्ठा __packed atto_vda_ob_rsp अणु
	u32 handle;
	u8 req_stat;
	u8 rsvd[3];

	जोड़ atto_vda_func_rsp
		func_rsp;
पूर्ण;

काष्ठा __packed atto_vda_ae_data अणु
	u8 event_data[256];
पूर्ण;

काष्ठा __packed atto_vda_mgmt_data अणु
	जोड़ अणु
		u8 bytes[112];
		काष्ठा atto_vda_devinfo dev_info;
		काष्ठा atto_vda_grp_info grp_info;
		काष्ठा atto_vdapart_info part_info;
		काष्ठा atto_vda_dh_info dev_health_info;
		काष्ठा atto_vda_metrics_info metrics_info;
		काष्ठा atto_vda_schedule_info sched_info;
		काष्ठा atto_vda_n_vcache_info nvcache_info;
		काष्ठा atto_vda_buzzer_info buzzer_info;
	पूर्ण data;
पूर्ण;

जोड़ atto_vda_rsp_data अणु
	काष्ठा atto_vda_ae_data ae_data;
	काष्ठा atto_vda_mgmt_data mgt_data;
	u8 sense_data[252];
	#घोषणा SENSE_DATA_SZ   252;
	u8 bytes[256];
पूर्ण;

#पूर्ण_अगर
