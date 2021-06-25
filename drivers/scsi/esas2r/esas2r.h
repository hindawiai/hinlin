<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r.h
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * NO WARRANTY
 * THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 * solely responsible क्रम determining the appropriateness of using and
 * distributing the Program and assumes all risks associated with its
 * exercise of rights under this Agreement, including but not limited to
 * the risks and costs of program errors, damage to or loss of data,
 * programs or equipment, and unavailability or पूर्णांकerruption of operations.
 *
 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "esas2r_log.h"
#समावेश "atioctl.h"
#समावेश "atvda.h"

#अगर_अघोषित ESAS2R_H
#घोषणा ESAS2R_H

/* Global Variables */
बाह्य काष्ठा esas2r_adapter *esas2r_adapters[];
बाह्य u8 *esas2r_buffered_ioctl;
बाह्य dma_addr_t esas2r_buffered_ioctl_addr;
बाह्य u32 esas2r_buffered_ioctl_size;
बाह्य काष्ठा pci_dev *esas2r_buffered_ioctl_pcid;
#घोषणा SGL_PG_SZ_MIN   64
#घोषणा SGL_PG_SZ_MAX   1024
बाह्य पूर्णांक sgl_page_size;
#घोषणा NUM_SGL_MIN     8
#घोषणा NUM_SGL_MAX     2048
बाह्य पूर्णांक num_sg_lists;
#घोषणा NUM_REQ_MIN     4
#घोषणा NUM_REQ_MAX     256
बाह्य पूर्णांक num_requests;
#घोषणा NUM_AE_MIN      2
#घोषणा NUM_AE_MAX      8
बाह्य पूर्णांक num_ae_requests;
बाह्य पूर्णांक cmd_per_lun;
बाह्य पूर्णांक can_queue;
बाह्य पूर्णांक esas2r_max_sectors;
बाह्य पूर्णांक sg_tablesize;
बाह्य पूर्णांक पूर्णांकerrupt_mode;
बाह्य पूर्णांक num_io_requests;

/* Macro defपूर्णांकions */
#घोषणा ESAS2R_MAX_ID        255
#घोषणा MAX_ADAPTERS         32
#घोषणा ESAS2R_DRVR_NAME     "esas2r"
#घोषणा ESAS2R_LONGNAME      "ATTO ExpressSAS 6GB RAID Adapter"
#घोषणा ESAS2R_MAX_DEVICES     32
#घोषणा ATTONODE_NAME         "ATTONode"
#घोषणा ESAS2R_MAJOR_REV       1
#घोषणा ESAS2R_MINOR_REV       00
#घोषणा ESAS2R_VERSION_STR     DEFINED_NUM_TO_STR(ESAS2R_MAJOR_REV) "." \
	DEFINED_NUM_TO_STR(ESAS2R_MINOR_REV)
#घोषणा ESAS2R_COPYRIGHT_YEARS "2001-2013"
#घोषणा ESAS2R_DEFAULT_SGL_PAGE_SIZE 384
#घोषणा ESAS2R_DEFAULT_CMD_PER_LUN   64
#घोषणा ESAS2R_DEFAULT_NUM_SG_LISTS 1024
#घोषणा DEFINED_NUM_TO_STR(num) NUM_TO_STR(num)
#घोषणा NUM_TO_STR(num) #num

#घोषणा ESAS2R_SGL_ALIGN    16
#घोषणा ESAS2R_LIST_ALIGN   16
#घोषणा ESAS2R_LIST_EXTRA   ESAS2R_NUM_EXTRA
#घोषणा ESAS2R_DATA_BUF_LEN         256
#घोषणा ESAS2R_DEFAULT_TMO          5000
#घोषणा ESAS2R_DISC_BUF_LEN         512
#घोषणा ESAS2R_FWCOREDUMP_SZ        0x80000
#घोषणा ESAS2R_NUM_PHYS             8
#घोषणा ESAS2R_TARG_ID_INV          0xFFFF
#घोषणा ESAS2R_INT_STS_MASK         MU_INTSTAT_MASK
#घोषणा ESAS2R_INT_ENB_MASK         MU_INTSTAT_MASK
#घोषणा ESAS2R_INT_DIS_MASK         0
#घोषणा ESAS2R_MAX_TARGETS          256
#घोषणा ESAS2R_KOBJ_NAME_LEN        20

/* u16 (WORD) component macros */
#घोषणा LOBYTE(w) ((u8)(u16)(w))
#घोषणा HIBYTE(w) ((u8)(((u16)(w)) >> 8))
#घोषणा MAKEWORD(lo, hi) ((u16)((u8)(lo) | ((u16)(u8)(hi) << 8)))

/* u32 (DWORD) component macros */
#घोषणा LOWORD(d) ((u16)(u32)(d))
#घोषणा HIWORD(d) ((u16)(((u32)(d)) >> 16))
#घोषणा MAKEDWORD(lo, hi) ((u32)((u16)(lo) | ((u32)(u16)(hi) << 16)))

/* macro to get the lowest nonzero bit of a value */
#घोषणा LOBIT(x) ((x) & (0 - (x)))

/* These functions are provided to access the chip's control रेजिस्टरs.
 * The रेजिस्टर is specअगरied by its byte offset from the रेजिस्टर base
 * क्रम the adapter.
 */
#घोषणा esas2r_पढ़ो_रेजिस्टर_dword(a, reg)                             \
	पढ़ोl((व्योम __iomem *)a->regs + (reg) + MW_REG_OFFSET_HWREG)

#घोषणा esas2r_ग_लिखो_रेजिस्टर_dword(a, reg, data)                      \
	ग_लिखोl(data, (व्योम __iomem *)(a->regs + (reg) + MW_REG_OFFSET_HWREG))

#घोषणा esas2r_flush_रेजिस्टर_dword(a, r) esas2r_पढ़ो_रेजिस्टर_dword(a, r)

/* This function is provided to access the chip's data winकरोw.   The
 * रेजिस्टर is specअगरied by its byte offset from the winकरोw base
 * क्रम the adapter.
 */
#घोषणा esas2r_पढ़ो_data_byte(a, reg)                                  \
	पढ़ोb((व्योम __iomem *)a->data_winकरोw + (reg))

/* ATTO venकरोr and device Ids */
#घोषणा ATTO_VENDOR_ID          0x117C
#घोषणा ATTO_DID_INTEL_IOP348   0x002C
#घोषणा ATTO_DID_MV_88RC9580    0x0049
#घोषणा ATTO_DID_MV_88RC9580TS  0x0066
#घोषणा ATTO_DID_MV_88RC9580TSE 0x0067
#घोषणा ATTO_DID_MV_88RC9580TL  0x0068

/* ATTO subप्रणाली device Ids */
#घोषणा ATTO_SSDID_TBT      0x4000
#घोषणा ATTO_TSSC_3808      0x4066
#घोषणा ATTO_TSSC_3808E     0x4067
#घोषणा ATTO_TLSH_1068      0x4068
#घोषणा ATTO_ESAS_R680      0x0049
#घोषणा ATTO_ESAS_R608      0x004A
#घोषणा ATTO_ESAS_R60F      0x004B
#घोषणा ATTO_ESAS_R6F0      0x004C
#घोषणा ATTO_ESAS_R644      0x004D
#घोषणा ATTO_ESAS_R648      0x004E

/*
 * flash definitions & काष्ठाures
 * define the code types
 */
#घोषणा FBT_CPYR        0xAA00
#घोषणा FBT_SETUP       0xAA02
#घोषणा FBT_FLASH_VER   0xAA04

/* offsets to various locations in flash */
#घोषणा FLS_OFFSET_BOOT (u32)(0x00700000)
#घोषणा FLS_OFFSET_NVR  (u32)(0x007C0000)
#घोषणा FLS_OFFSET_CPYR FLS_OFFSET_NVR
#घोषणा FLS_LENGTH_BOOT (FLS_OFFSET_CPYR - FLS_OFFSET_BOOT)
#घोषणा FLS_BLOCK_SIZE  (u32)(0x00020000)
#घोषणा FI_NVR_2KB  0x0800
#घोषणा FI_NVR_8KB  0x2000
#घोषणा FM_BUF_SZ   0x800

/*
 * marvell frey (88R9580) रेजिस्टर definitions
 * chip revision identअगरiers
 */
#घोषणा MVR_FREY_B2     0xB2

/*
 * memory winकरोw definitions.  winकरोw 0 is the data winकरोw with definitions
 * of MW_DATA_XXX.  winकरोw 1 is the रेजिस्टर winकरोw with definitions of
 * MW_REG_XXX.
 */
#घोषणा MW_REG_WINDOW_SIZE      (u32)(0x00040000)
#घोषणा MW_REG_OFFSET_HWREG     (u32)(0x00000000)
#घोषणा MW_REG_OFFSET_PCI       (u32)(0x00008000)
#घोषणा MW_REG_PCI_HWREG_DELTA  (MW_REG_OFFSET_PCI - MW_REG_OFFSET_HWREG)
#घोषणा MW_DATA_WINDOW_SIZE     (u32)(0x00020000)
#घोषणा MW_DATA_ADDR_SER_FLASH  (u32)(0xEC000000)
#घोषणा MW_DATA_ADDR_SRAM       (u32)(0xF4000000)
#घोषणा MW_DATA_ADDR_PAR_FLASH  (u32)(0xFC000000)

/*
 * the following रेजिस्टरs are क्रम the communication
 * list पूर्णांकerface (AKA message unit (MU))
 */
#घोषणा MU_IN_LIST_ADDR_LO      (u32)(0x00004000)
#घोषणा MU_IN_LIST_ADDR_HI      (u32)(0x00004004)

#घोषणा MU_IN_LIST_WRITE        (u32)(0x00004018)
    #घोषणा MU_ILW_TOGGLE       (u32)(0x00004000)

#घोषणा MU_IN_LIST_READ         (u32)(0x0000401C)
    #घोषणा MU_ILR_TOGGLE       (u32)(0x00004000)
    #घोषणा MU_ILIC_LIST        (u32)(0x0000000F)
    #घोषणा MU_ILIC_LIST_F0     (u32)(0x00000000)
    #घोषणा MU_ILIC_DEST        (u32)(0x00000F00)
    #घोषणा MU_ILIC_DEST_DDR    (u32)(0x00000200)
#घोषणा MU_IN_LIST_IFC_CONFIG   (u32)(0x00004028)

#घोषणा MU_IN_LIST_CONFIG       (u32)(0x0000402C)
    #घोषणा MU_ILC_ENABLE       (u32)(0x00000001)
    #घोषणा MU_ILC_ENTRY_MASK   (u32)(0x000000F0)
    #घोषणा MU_ILC_ENTRY_4_DW   (u32)(0x00000020)
    #घोषणा MU_ILC_DYNAMIC_SRC  (u32)(0x00008000)
    #घोषणा MU_ILC_NUMBER_MASK  (u32)(0x7FFF0000)
    #घोषणा MU_ILC_NUMBER_SHIFT            16

#घोषणा MU_OUT_LIST_ADDR_LO     (u32)(0x00004050)
#घोषणा MU_OUT_LIST_ADDR_HI     (u32)(0x00004054)

#घोषणा MU_OUT_LIST_COPY_PTR_LO (u32)(0x00004058)
#घोषणा MU_OUT_LIST_COPY_PTR_HI (u32)(0x0000405C)

#घोषणा MU_OUT_LIST_WRITE       (u32)(0x00004068)
    #घोषणा MU_OLW_TOGGLE       (u32)(0x00004000)

#घोषणा MU_OUT_LIST_COPY        (u32)(0x0000406C)
    #घोषणा MU_OLC_TOGGLE       (u32)(0x00004000)
    #घोषणा MU_OLC_WRT_PTR      (u32)(0x00003FFF)

#घोषणा MU_OUT_LIST_IFC_CONFIG  (u32)(0x00004078)
    #घोषणा MU_OLIC_LIST        (u32)(0x0000000F)
    #घोषणा MU_OLIC_LIST_F0     (u32)(0x00000000)
    #घोषणा MU_OLIC_SOURCE      (u32)(0x00000F00)
    #घोषणा MU_OLIC_SOURCE_DDR  (u32)(0x00000200)

#घोषणा MU_OUT_LIST_CONFIG      (u32)(0x0000407C)
    #घोषणा MU_OLC_ENABLE       (u32)(0x00000001)
    #घोषणा MU_OLC_ENTRY_MASK   (u32)(0x000000F0)
    #घोषणा MU_OLC_ENTRY_4_DW   (u32)(0x00000020)
    #घोषणा MU_OLC_NUMBER_MASK  (u32)(0x7FFF0000)
    #घोषणा MU_OLC_NUMBER_SHIFT            16

#घोषणा MU_OUT_LIST_INT_STAT    (u32)(0x00004088)
    #घोषणा MU_OLIS_INT         (u32)(0x00000001)

#घोषणा MU_OUT_LIST_INT_MASK    (u32)(0x0000408C)
    #घोषणा MU_OLIS_MASK        (u32)(0x00000001)

/*
 * the maximum size of the communication lists is two greater than the
 * maximum amount of VDA requests.  the extra are to prevent queue overflow.
 */
#घोषणा ESAS2R_MAX_NUM_REQS         256
#घोषणा ESAS2R_NUM_EXTRA            2
#घोषणा ESAS2R_MAX_COMM_LIST_SIZE   (ESAS2R_MAX_NUM_REQS + ESAS2R_NUM_EXTRA)

/*
 * the following रेजिस्टरs are क्रम the CPU पूर्णांकerface
 */
#घोषणा MU_CTL_STATUS_IN        (u32)(0x00010108)
    #घोषणा MU_CTL_IN_FULL_RST  (u32)(0x00000020)
#घोषणा MU_CTL_STATUS_IN_B2     (u32)(0x00010130)
    #घोषणा MU_CTL_IN_FULL_RST2 (u32)(0x80000000)
#घोषणा MU_DOORBELL_IN          (u32)(0x00010460)
    #घोषणा DRBL_RESET_BUS      (u32)(0x00000002)
    #घोषणा DRBL_PAUSE_AE       (u32)(0x00000004)
    #घोषणा DRBL_RESUME_AE      (u32)(0x00000008)
    #घोषणा DRBL_MSG_IFC_DOWN   (u32)(0x00000010)
    #घोषणा DRBL_FLASH_REQ      (u32)(0x00000020)
    #घोषणा DRBL_FLASH_DONE     (u32)(0x00000040)
    #घोषणा DRBL_FORCE_INT      (u32)(0x00000080)
    #घोषणा DRBL_MSG_IFC_INIT   (u32)(0x00000100)
    #घोषणा DRBL_POWER_DOWN     (u32)(0x00000200)
    #घोषणा DRBL_DRV_VER_1      (u32)(0x00010000)
    #घोषणा DRBL_DRV_VER        DRBL_DRV_VER_1
#घोषणा MU_DOORBELL_IN_ENB      (u32)(0x00010464)
#घोषणा MU_DOORBELL_OUT         (u32)(0x00010480)
 #घोषणा DRBL_PANIC_REASON_MASK (u32)(0x00F00000)
    #घोषणा DRBL_UNUSED_HANDLER (u32)(0x00100000)
    #घोषणा DRBL_UNDEF_INSTR    (u32)(0x00200000)
    #घोषणा DRBL_PREFETCH_ABORT (u32)(0x00300000)
    #घोषणा DRBL_DATA_ABORT     (u32)(0x00400000)
    #घोषणा DRBL_JUMP_TO_ZERO   (u32)(0x00500000)
  #घोषणा DRBL_FW_RESET         (u32)(0x00080000)
  #घोषणा DRBL_FW_VER_MSK       (u32)(0x00070000)
  #घोषणा DRBL_FW_VER_0         (u32)(0x00000000)
  #घोषणा DRBL_FW_VER_1         (u32)(0x00010000)
  #घोषणा DRBL_FW_VER           DRBL_FW_VER_1
#घोषणा MU_DOORBELL_OUT_ENB     (u32)(0x00010484)
    #घोषणा DRBL_ENB_MASK       (u32)(0x00F803FF)
#घोषणा MU_INT_STATUS_OUT       (u32)(0x00010200)
    #घोषणा MU_INTSTAT_POST_OUT (u32)(0x00000010)
    #घोषणा MU_INTSTAT_DRBL_IN  (u32)(0x00000100)
    #घोषणा MU_INTSTAT_DRBL     (u32)(0x00001000)
    #घोषणा MU_INTSTAT_MASK     (u32)(0x00001010)
#घोषणा MU_INT_MASK_OUT         (u32)(0x0001020C)

/* PCI express रेजिस्टरs accessed via winकरोw 1 */
#घोषणा MVR_PCI_WIN1_REMAP      (u32)(0x00008438)
    #घोषणा MVRPW1R_ENABLE      (u32)(0x00000001)


/* काष्ठाures */

/* inbound list dynamic source entry */
काष्ठा esas2r_inbound_list_source_entry अणु
	u64 address;
	u32 length;
	#घोषणा HWILSE_INTERFACE_F0  0x00000000
	u32 reserved;
पूर्ण;

/* PCI data काष्ठाure in expansion ROM images */
काष्ठा __packed esas2r_boot_header अणु
	अक्षर signature[4];
	u16 venकरोr_id;
	u16 device_id;
	u16 VPD;
	u16 काष्ठा_length;
	u8 काष्ठा_revision;
	u8 class_code[3];
	u16 image_length;
	u16 code_revision;
	u8 code_type;
	#घोषणा CODE_TYPE_PC    0
	#घोषणा CODE_TYPE_OPEN  1
	#घोषणा CODE_TYPE_EFI   3
	u8 indicator;
	#घोषणा INDICATOR_LAST  0x80
	u8 reserved[2];
पूर्ण;

काष्ठा __packed esas2r_boot_image अणु
	u16 signature;
	u8 reserved[22];
	u16 header_offset;
	u16 pnp_offset;
पूर्ण;

काष्ठा __packed esas2r_pc_image अणु
	u16 signature;
	u8 length;
	u8 entry_poपूर्णांक[3];
	u8 checksum;
	u16 image_end;
	u16 min_size;
	u8 rom_flags;
	u8 reserved[12];
	u16 header_offset;
	u16 pnp_offset;
	काष्ठा esas2r_boot_header boot_image;
पूर्ण;

काष्ठा __packed esas2r_efi_image अणु
	u16 signature;
	u16 length;
	u32 efi_signature;
	#घोषणा EFI_ROM_SIG     0x00000EF1
	u16 image_type;
	#घोषणा EFI_IMAGE_APP   10
	#घोषणा EFI_IMAGE_BSD   11
	#घोषणा EFI_IMAGE_RTD   12
	u16 machine_type;
	#घोषणा EFI_MACHINE_IA32 0x014c
	#घोषणा EFI_MACHINE_IA64 0x0200
	#घोषणा EFI_MACHINE_X64  0x8664
	#घोषणा EFI_MACHINE_EBC  0x0EBC
	u16 compression;
	#घोषणा EFI_UNCOMPRESSED 0x0000
	#घोषणा EFI_COMPRESSED   0x0001
	u8 reserved[8];
	u16 efi_offset;
	u16 header_offset;
	u16 reserved2;
	काष्ठा esas2r_boot_header boot_image;
पूर्ण;

काष्ठा esas2r_adapter;
काष्ठा esas2r_sg_context;
काष्ठा esas2r_request;

प्रकार व्योम (*RQCALLBK)     (काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_request *rq);
प्रकार bool (*RQBUILDSGL)   (काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_sg_context *sgc);

काष्ठा esas2r_component_header अणु
	u8 img_type;
	#घोषणा CH_IT_FW    0x00
	#घोषणा CH_IT_NVR   0x01
	#घोषणा CH_IT_BIOS  0x02
	#घोषणा CH_IT_MAC   0x03
	#घोषणा CH_IT_CFG   0x04
	#घोषणा CH_IT_EFI   0x05
	u8 status;
	#घोषणा CH_STAT_PENDING 0xff
	#घोषणा CH_STAT_FAILED  0x00
	#घोषणा CH_STAT_SUCCESS 0x01
	#घोषणा CH_STAT_RETRY   0x02
	#घोषणा CH_STAT_INVALID 0x03
	u8 pad[2];
	u32 version;
	u32 length;
	u32 image_offset;
पूर्ण;

#घोषणा FI_REL_VER_SZ   16

काष्ठा esas2r_flash_img_v0 अणु
	u8 fi_version;
	#घोषणा FI_VERSION_0    00
	u8 status;
	u8 adap_typ;
	u8 action;
	u32 length;
	u16 checksum;
	u16 driver_error;
	u16 flags;
	u16 num_comps;
	#घोषणा FI_NUM_COMPS_V0 5
	u8 rel_version[FI_REL_VER_SZ];
	काष्ठा esas2r_component_header cmp_hdr[FI_NUM_COMPS_V0];
	u8 scratch_buf[FM_BUF_SZ];
पूर्ण;

काष्ठा esas2r_flash_img अणु
	u8 fi_version;
	#घोषणा FI_VERSION_1    01
	u8 status;
	#घोषणा FI_STAT_SUCCESS  0x00
	#घोषणा FI_STAT_FAILED   0x01
	#घोषणा FI_STAT_REBOOT   0x02
	#घोषणा FI_STAT_ADAPTYP  0x03
	#घोषणा FI_STAT_INVALID  0x04
	#घोषणा FI_STAT_CHKSUM   0x05
	#घोषणा FI_STAT_LENGTH   0x06
	#घोषणा FI_STAT_UNKNOWN  0x07
	#घोषणा FI_STAT_IMG_VER  0x08
	#घोषणा FI_STAT_BUSY     0x09
	#घोषणा FI_STAT_DUAL     0x0A
	#घोषणा FI_STAT_MISSING  0x0B
	#घोषणा FI_STAT_UNSUPP   0x0C
	#घोषणा FI_STAT_ERASE    0x0D
	#घोषणा FI_STAT_FLASH    0x0E
	#घोषणा FI_STAT_DEGRADED 0x0F
	u8 adap_typ;
	#घोषणा FI_AT_UNKNWN    0xFF
	#घोषणा FI_AT_SUN_LAKE  0x0B
	#घोषणा FI_AT_MV_9580   0x0F
	u8 action;
	#घोषणा FI_ACT_DOWN     0x00
	#घोषणा FI_ACT_UP       0x01
	#घोषणा FI_ACT_UPSZ     0x02
	#घोषणा FI_ACT_MAX      0x02
	#घोषणा FI_ACT_DOWN1    0x80
	u32 length;
	u16 checksum;
	u16 driver_error;
	u16 flags;
	#घोषणा FI_FLG_NVR_DEF  0x0001
	u16 num_comps;
	#घोषणा FI_NUM_COMPS_V1 6
	u8 rel_version[FI_REL_VER_SZ];
	काष्ठा esas2r_component_header cmp_hdr[FI_NUM_COMPS_V1];
	u8 scratch_buf[FM_BUF_SZ];
पूर्ण;

/* definitions क्रम flash script (FS) commands */
काष्ठा esas2r_ioctlfs_command अणु
	u8 command;
	#घोषणा ESAS2R_FS_CMD_ERASE    0
	#घोषणा ESAS2R_FS_CMD_READ     1
	#घोषणा ESAS2R_FS_CMD_BEGINW   2
	#घोषणा ESAS2R_FS_CMD_WRITE    3
	#घोषणा ESAS2R_FS_CMD_COMMIT   4
	#घोषणा ESAS2R_FS_CMD_CANCEL   5
	u8 checksum;
	u8 reserved[2];
	u32 flash_addr;
	u32 length;
	u32 image_offset;
पूर्ण;

काष्ठा esas2r_ioctl_fs अणु
	u8 version;
	#घोषणा ESAS2R_FS_VER      0
	u8 status;
	u8 driver_error;
	u8 adap_type;
	#घोषणा ESAS2R_FS_AT_ESASRAID2     3
	#घोषणा ESAS2R_FS_AT_TSSASRAID2    4
	#घोषणा ESAS2R_FS_AT_TSSASRAID2E   5
	#घोषणा ESAS2R_FS_AT_TLSASHBA      6
	u8 driver_ver;
	u8 reserved[11];
	काष्ठा esas2r_ioctlfs_command command;
	u8 data[1];
पूर्ण;

काष्ठा esas2r_sas_nvram अणु
	u8 signature[4];
	u8 version;
	#घोषणा SASNVR_VERSION_0    0x00
	#घोषणा SASNVR_VERSION      SASNVR_VERSION_0
	u8 checksum;
	#घोषणा SASNVR_CKSUM_SEED   0x5A
	u8 max_lun_क्रम_target;
	u8 pci_latency;
	#घोषणा SASNVR_PCILAT_DIS   0x00
	#घोषणा SASNVR_PCILAT_MIN   0x10
	#घोषणा SASNVR_PCILAT_MAX   0xF8
	u8 options1;
	#घोषणा SASNVR1_BOOT_DRVR   0x01
	#घोषणा SASNVR1_BOOT_SCAN   0x02
	#घोषणा SASNVR1_DIS_PCI_MWI 0x04
	#घोषणा SASNVR1_FORCE_ORD_Q 0x08
	#घोषणा SASNVR1_CACHELINE_0 0x10
	#घोषणा SASNVR1_DIS_DEVSORT 0x20
	#घोषणा SASNVR1_PWR_MGT_EN  0x40
	#घोषणा SASNVR1_WIDEPORT    0x80
	u8 options2;
	#घोषणा SASNVR2_SINGLE_BUS  0x01
	#घोषणा SASNVR2_SLOT_BIND   0x02
	#घोषणा SASNVR2_EXP_PROG    0x04
	#घोषणा SASNVR2_CMDTHR_LUN  0x08
	#घोषणा SASNVR2_HEARTBEAT   0x10
	#घोषणा SASNVR2_INT_CONNECT 0x20
	#घोषणा SASNVR2_SW_MUX_CTRL 0x40
	#घोषणा SASNVR2_DISABLE_NCQ 0x80
	u8 पूर्णांक_coalescing;
	#घोषणा SASNVR_COAL_DIS     0x00
	#घोषणा SASNVR_COAL_LOW     0x01
	#घोषणा SASNVR_COAL_MED     0x02
	#घोषणा SASNVR_COAL_HI      0x03
	u8 cmd_throttle;
	#घोषणा SASNVR_CMDTHR_NONE  0x00
	u8 dev_रुको_समय;
	u8 dev_रुको_count;
	u8 spin_up_delay;
	#घोषणा SASNVR_SPINUP_MAX   0x14
	u8 ssp_align_rate;
	u8 sas_addr[8];
	u8 phy_speed[16];
	#घोषणा SASNVR_SPEED_AUTO   0x00
	#घोषणा SASNVR_SPEED_1_5GB  0x01
	#घोषणा SASNVR_SPEED_3GB    0x02
	#घोषणा SASNVR_SPEED_6GB    0x03
	#घोषणा SASNVR_SPEED_12GB   0x04
	u8 phy_mux[16];
	#घोषणा SASNVR_MUX_DISABLED 0x00
	#घोषणा SASNVR_MUX_1_5GB    0x01
	#घोषणा SASNVR_MUX_3GB      0x02
	#घोषणा SASNVR_MUX_6GB      0x03
	u8 phy_flags[16];
	#घोषणा SASNVR_PHF_DISABLED 0x01
	#घोषणा SASNVR_PHF_RD_ONLY  0x02
	u8 sort_type;
	#घोषणा SASNVR_SORT_SAS_ADDR    0x00
	#घोषणा SASNVR_SORT_H308_CONN   0x01
	#घोषणा SASNVR_SORT_PHY_ID      0x02
	#घोषणा SASNVR_SORT_SLOT_ID     0x03
	u8 dpm_reqcmd_lmt;
	u8 dpm_stndby_समय;
	u8 dpm_active_समय;
	u8 phy_target_id[16];
	#घोषणा SASNVR_PTI_DISABLED     0xFF
	u8 virt_ses_mode;
	#घोषणा SASNVR_VSMH_DISABLED    0x00
	u8 पढ़ो_ग_लिखो_mode;
	#घोषणा SASNVR_RWM_DEFAULT      0x00
	u8 link_करोwn_to;
	u8 reserved[0xA1];
पूर्ण;

प्रकार u32 (*PGETPHYSADDR) (काष्ठा esas2r_sg_context *sgc, u64 *addr);

काष्ठा esas2r_sg_context अणु
	काष्ठा esas2r_adapter *adapter;
	काष्ठा esas2r_request *first_req;
	u32 length;
	u8 *cur_offset;
	PGETPHYSADDR get_phys_addr;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा atto_vda_sge *curr;
			काष्ठा atto_vda_sge *last;
			काष्ठा atto_vda_sge *limit;
			काष्ठा atto_vda_sge *chain;
		पूर्ण a64;
		काष्ठा अणु
			काष्ठा atto_physical_region_description *curr;
			काष्ठा atto_physical_region_description *chain;
			u32 sgl_max_cnt;
			u32 sge_cnt;
		पूर्ण prd;
	पूर्ण sge;
	काष्ठा scatterlist *cur_sgel;
	u8 *exp_offset;
	पूर्णांक num_sgel;
	पूर्णांक sgel_count;
पूर्ण;

काष्ठा esas2r_target अणु
	u8 flags;
	#घोषणा TF_PASS_THRU    0x01
	#घोषणा TF_USED         0x02
	u8 new_target_state;
	u8 target_state;
	u8 buffered_target_state;
#घोषणा TS_NOT_PRESENT      0x00
#घोषणा TS_PRESENT          0x05
#घोषणा TS_LUN_CHANGE       0x06
#घोषणा TS_INVALID          0xFF
	u32 block_size;
	u32 पूर्णांकer_block;
	u32 पूर्णांकer_byte;
	u16 virt_targ_id;
	u16 phys_targ_id;
	u8 identअगरier_len;
	u64 sas_addr;
	u8 identअगरier[60];
	काष्ठा atto_vda_ae_lu lu_event;
पूर्ण;

काष्ठा esas2r_request अणु
	काष्ठा list_head comp_list;
	काष्ठा list_head req_list;
	जोड़ atto_vda_req *vrq;
	काष्ठा esas2r_mem_desc *vrq_md;
	जोड़ अणु
		व्योम *data_buf;
		जोड़ atto_vda_rsp_data *vda_rsp_data;
	पूर्ण;
	u8 *sense_buf;
	काष्ठा list_head sg_table_head;
	काष्ठा esas2r_mem_desc *sg_table;
	u32 समयout;
	#घोषणा RQ_TIMEOUT_S1     0xFFFFFFFF
	#घोषणा RQ_TIMEOUT_S2     0xFFFFFFFE
	#घोषणा RQ_MAX_TIMEOUT    0xFFFFFFFD
	u16 target_id;
	u8 req_type;
	#घोषणा RT_INI_REQ          0x01
	#घोषणा RT_DISC_REQ         0x02
	u8 sense_len;
	जोड़ atto_vda_func_rsp func_rsp;
	RQCALLBK comp_cb;
	RQCALLBK पूर्णांकerrupt_cb;
	व्योम *पूर्णांकerrupt_cx;
	u8 flags;
	#घोषणा RF_1ST_IBLK_BASE    0x04
	#घोषणा RF_FAILURE_OK       0x08
	u8 req_stat;
	u16 vda_req_sz;
	#घोषणा RQ_SIZE_DEFAULT   0
	u64 lba;
	RQCALLBK aux_req_cb;
	व्योम *aux_req_cx;
	u32 blk_len;
	u32 max_blk_len;
	जोड़ अणु
		काष्ठा scsi_cmnd *cmd;
		u8 *task_management_status_ptr;
	पूर्ण;
पूर्ण;

काष्ठा esas2r_flash_context अणु
	काष्ठा esas2r_flash_img *fi;
	RQCALLBK पूर्णांकerrupt_cb;
	u8 *sgc_offset;
	u8 *scratch;
	u32 fi_hdr_len;
	u8 task;
	#घोषणा     FMTSK_ERASE_BOOT    0
	#घोषणा     FMTSK_WRTBIOS       1
	#घोषणा     FMTSK_READBIOS      2
	#घोषणा     FMTSK_WRTMAC        3
	#घोषणा     FMTSK_READMAC       4
	#घोषणा     FMTSK_WRTEFI        5
	#घोषणा     FMTSK_READEFI       6
	#घोषणा     FMTSK_WRTCFG        7
	#घोषणा     FMTSK_READCFG       8
	u8 func;
	u16 num_comps;
	u32 cmp_len;
	u32 flsh_addr;
	u32 curr_len;
	u8 comp_typ;
	काष्ठा esas2r_sg_context sgc;
पूर्ण;

काष्ठा esas2r_disc_context अणु
	u8 disc_evt;
	#घोषणा DCDE_DEV_CHANGE     0x01
	#घोषणा DCDE_DEV_SCAN       0x02
	u8 state;
	#घोषणा DCS_DEV_RMV         0x00
	#घोषणा DCS_DEV_ADD         0x01
	#घोषणा DCS_BLOCK_DEV_SCAN  0x02
	#घोषणा DCS_RAID_GRP_INFO   0x03
	#घोषणा DCS_PART_INFO       0x04
	#घोषणा DCS_PT_DEV_INFO     0x05
	#घोषणा DCS_PT_DEV_ADDR     0x06
	#घोषणा DCS_DISC_DONE       0xFF
	u16 flags;
	#घोषणा DCF_DEV_CHANGE      0x0001
	#घोषणा DCF_DEV_SCAN        0x0002
	#घोषणा DCF_POLLED          0x8000
	u32 पूर्णांकerleave;
	u32 block_size;
	u16 dev_ix;
	u8 part_num;
	u8 raid_grp_ix;
	अक्षर raid_grp_name[16];
	काष्ठा esas2r_target *curr_targ;
	u16 curr_virt_id;
	u16 curr_phys_id;
	u8 scan_gen;
	u8 dev_addr_type;
	u64 sas_addr;
पूर्ण;

काष्ठा esas2r_mem_desc अणु
	काष्ठा list_head next_desc;
	व्योम *virt_addr;
	u64 phys_addr;
	व्योम *pad;
	व्योम *esas2r_data;
	u32 esas2r_param;
	u32 size;
पूर्ण;

क्रमागत fw_event_type अणु
	fw_event_null,
	fw_event_lun_change,
	fw_event_present,
	fw_event_not_present,
	fw_event_vda_ae
पूर्ण;

काष्ठा esas2r_vda_ae अणु
	u32 signature;
#घोषणा ESAS2R_VDA_EVENT_SIG  0x4154544F
	u8 bus_number;
	u8 devfn;
	u8 pad[2];
	जोड़ atto_vda_ae vda_ae;
पूर्ण;

काष्ठा esas2r_fw_event_work अणु
	काष्ठा list_head list;
	काष्ठा delayed_work work;
	काष्ठा esas2r_adapter *a;
	क्रमागत fw_event_type type;
	u8 data[माप(काष्ठा esas2r_vda_ae)];
पूर्ण;

क्रमागत state अणु
	FW_INVALID_ST,
	FW_STATUS_ST,
	FW_COMMAND_ST
पूर्ण;

काष्ठा esas2r_firmware अणु
	क्रमागत state state;
	काष्ठा esas2r_flash_img header;
	u8 *data;
	u64 phys;
	पूर्णांक orig_len;
	व्योम *header_buff;
	u64 header_buff_phys;
पूर्ण;

काष्ठा esas2r_adapter अणु
	काष्ठा esas2r_target targetdb[ESAS2R_MAX_TARGETS];
	काष्ठा esas2r_target *targetdb_end;
	अचिन्हित अक्षर *regs;
	अचिन्हित अक्षर *data_winकरोw;
	दीर्घ flags;
	#घोषणा AF_PORT_CHANGE      0
	#घोषणा AF_CHPRST_NEEDED    1
	#घोषणा AF_CHPRST_PENDING   2
	#घोषणा AF_CHPRST_DETECTED  3
	#घोषणा AF_BUSRST_NEEDED    4
	#घोषणा AF_BUSRST_PENDING   5
	#घोषणा AF_BUSRST_DETECTED  6
	#घोषणा AF_DISABLED         7
	#घोषणा AF_FLASH_LOCK       8
	#घोषणा AF_OS_RESET         9
	#घोषणा AF_FLASHING         10
	#घोषणा AF_POWER_MGT        11
	#घोषणा AF_NVR_VALID        12
	#घोषणा AF_DEGRADED_MODE    13
	#घोषणा AF_DISC_PENDING     14
	#घोषणा AF_TASKLET_SCHEDULED    15
	#घोषणा AF_HEARTBEAT        16
	#घोषणा AF_HEARTBEAT_ENB    17
	#घोषणा AF_NOT_PRESENT      18
	#घोषणा AF_CHPRST_STARTED   19
	#घोषणा AF_FIRST_INIT       20
	#घोषणा AF_POWER_DOWN       21
	#घोषणा AF_DISC_IN_PROG     22
	#घोषणा AF_COMM_LIST_TOGGLE 23
	#घोषणा AF_LEGACY_SGE_MODE  24
	#घोषणा AF_DISC_POLLED      25
	दीर्घ flags2;
	#घोषणा AF2_SERIAL_FLASH    0
	#घोषणा AF2_DEV_SCAN        1
	#घोषणा AF2_DEV_CNT_OK      2
	#घोषणा AF2_COREDUMP_AVAIL  3
	#घोषणा AF2_COREDUMP_SAVED  4
	#घोषणा AF2_VDA_POWER_DOWN  5
	#घोषणा AF2_THUNDERLINK     6
	#घोषणा AF2_THUNDERBOLT     7
	#घोषणा AF2_INIT_DONE       8
	#घोषणा AF2_INT_PENDING     9
	#घोषणा AF2_TIMER_TICK      10
	#घोषणा AF2_IRQ_CLAIMED     11
	#घोषणा AF2_MSI_ENABLED     12
	atomic_t disable_cnt;
	atomic_t dis_पूर्णांकs_cnt;
	u32 पूर्णांक_stat;
	u32 पूर्णांक_mask;
	u32 अस्थिर *outbound_copy;
	काष्ठा list_head avail_request;
	spinlock_t request_lock;
	spinlock_t sg_list_lock;
	spinlock_t queue_lock;
	spinlock_t mem_lock;
	काष्ठा list_head मुक्त_sg_list_head;
	काष्ठा esas2r_mem_desc *sg_list_mds;
	काष्ठा list_head active_list;
	काष्ठा list_head defer_list;
	काष्ठा esas2r_request **req_table;
	जोड़ अणु
		u16 prev_dev_cnt;
		u32 heartbeat_समय;
	#घोषणा ESAS2R_HEARTBEAT_TIME       (3000)
	पूर्ण;
	u32 chip_upसमय;
	#घोषणा ESAS2R_CHP_UPTIME_MAX       (60000)
	#घोषणा ESAS2R_CHP_UPTIME_CNT       (20000)
	u64 uncached_phys;
	u8 *uncached;
	काष्ठा esas2r_sas_nvram *nvram;
	काष्ठा esas2r_request general_req;
	u8 init_msg;
	#घोषणा ESAS2R_INIT_MSG_START       1
	#घोषणा ESAS2R_INIT_MSG_INIT        2
	#घोषणा ESAS2R_INIT_MSG_GET_INIT    3
	#घोषणा ESAS2R_INIT_MSG_REINIT      4
	u16 cmd_ref_no;
	u32 fw_version;
	u32 fw_build;
	u32 chip_init_समय;
	#घोषणा ESAS2R_CHPRST_TIME         (180000)
	#घोषणा ESAS2R_CHPRST_WAIT_TIME    (2000)
	u32 last_tick_समय;
	u32 winकरोw_base;
	RQBUILDSGL build_sgl;
	काष्ठा esas2r_request *first_ae_req;
	u32 list_size;
	u32 last_ग_लिखो;
	u32 last_पढ़ो;
	u16 max_vdareq_size;
	u16 disc_रुको_cnt;
	काष्ठा esas2r_mem_desc inbound_list_md;
	काष्ठा esas2r_mem_desc outbound_list_md;
	काष्ठा esas2r_disc_context disc_ctx;
	u8 *disc_buffer;
	u32 disc_start_समय;
	u32 disc_रुको_समय;
	u32 flash_ver;
	अक्षर flash_rev[16];
	अक्षर fw_rev[16];
	अक्षर image_type[16];
	काष्ठा esas2r_flash_context flash_context;
	u32 num_tarमाला_लो_backend;
	u32 ioctl_tunnel;
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा pci_dev *pcid;
	काष्ठा Scsi_Host *host;
	अचिन्हित पूर्णांक index;
	अक्षर name[32];
	काष्ठा समयr_list समयr;
	काष्ठा esas2r_firmware firmware;
	रुको_queue_head_t nvram_रुकोer;
	पूर्णांक nvram_command_करोne;
	रुको_queue_head_t fm_api_रुकोer;
	पूर्णांक fm_api_command_करोne;
	रुको_queue_head_t vda_रुकोer;
	पूर्णांक vda_command_करोne;
	u8 *vda_buffer;
	u64 ppvda_buffer;
#घोषणा VDA_BUFFER_HEADER_SZ (दुरत्व(काष्ठा atto_ioctl_vda, data))
#घोषणा VDA_MAX_BUFFER_SIZE  (0x40000 + VDA_BUFFER_HEADER_SZ)
	रुको_queue_head_t fs_api_रुकोer;
	पूर्णांक fs_api_command_करोne;
	u64 ppfs_api_buffer;
	u8 *fs_api_buffer;
	u32 fs_api_buffer_size;
	रुको_queue_head_t buffered_ioctl_रुकोer;
	पूर्णांक buffered_ioctl_करोne;
	पूर्णांक uncached_size;
	काष्ठा workqueue_काष्ठा *fw_event_q;
	काष्ठा list_head fw_event_list;
	spinlock_t fw_event_lock;
	u8 fw_events_off;                       /* अगर '1', then ignore events */
	अक्षर fw_event_q_name[ESAS2R_KOBJ_NAME_LEN];
	/*
	 * पूर्णांकr_mode stores the पूर्णांकerrupt mode currently being used by this
	 * adapter. it is based on the पूर्णांकerrupt_mode module parameter, but
	 * can be changed based on the ability (or not) to utilize the
	 * mode requested by the parameter.
	 */
	पूर्णांक पूर्णांकr_mode;
#घोषणा INTR_MODE_LEGACY 0
#घोषणा INTR_MODE_MSI    1
#घोषणा INTR_MODE_MSIX   2
	काष्ठा esas2r_sg_context fm_api_sgc;
	u8 *save_offset;
	काष्ठा list_head vrq_mds_head;
	काष्ठा esas2r_mem_desc *vrq_mds;
	पूर्णांक num_vrqs;
	काष्ठा mutex fm_api_mutex;
	काष्ठा mutex fs_api_mutex;
	काष्ठा semaphore nvram_semaphore;
	काष्ठा atto_ioctl *local_atto_ioctl;
	u8 fw_coredump_buff[ESAS2R_FWCOREDUMP_SZ];
	अचिन्हित पूर्णांक sysfs_fw_created:1;
	अचिन्हित पूर्णांक sysfs_fs_created:1;
	अचिन्हित पूर्णांक sysfs_vda_created:1;
	अचिन्हित पूर्णांक sysfs_hw_created:1;
	अचिन्हित पूर्णांक sysfs_live_nvram_created:1;
	अचिन्हित पूर्णांक sysfs_शेष_nvram_created:1;
पूर्ण;

/*
 * Function Declarations
 * SCSI functions
 */
स्थिर अक्षर *esas2r_info(काष्ठा Scsi_Host *);
पूर्णांक esas2r_ग_लिखो_params(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq,
			काष्ठा esas2r_sas_nvram *data);
पूर्णांक esas2r_ioctl_handler(व्योम *hostdata, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
पूर्णांक esas2r_ioctl(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
u8 handle_hba_ioctl(काष्ठा esas2r_adapter *a,
		    काष्ठा atto_ioctl *ioctl_hba);
पूर्णांक esas2r_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmd);
पूर्णांक esas2r_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *sh);
दीर्घ esas2r_proc_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/* SCSI error handler (eh) functions */
पूर्णांक esas2r_eh_पात(काष्ठा scsi_cmnd *cmd);
पूर्णांक esas2r_device_reset(काष्ठा scsi_cmnd *cmd);
पूर्णांक esas2r_host_reset(काष्ठा scsi_cmnd *cmd);
पूर्णांक esas2r_bus_reset(काष्ठा scsi_cmnd *cmd);
पूर्णांक esas2r_target_reset(काष्ठा scsi_cmnd *cmd);

/* Internal functions */
पूर्णांक esas2r_init_adapter(काष्ठा Scsi_Host *host, काष्ठा pci_dev *pcid,
			पूर्णांक index);
पूर्णांक esas2r_पढ़ो_fw(काष्ठा esas2r_adapter *a, अक्षर *buf, दीर्घ off, पूर्णांक count);
पूर्णांक esas2r_ग_लिखो_fw(काष्ठा esas2r_adapter *a, स्थिर अक्षर *buf, दीर्घ off,
		    पूर्णांक count);
पूर्णांक esas2r_पढ़ो_vda(काष्ठा esas2r_adapter *a, अक्षर *buf, दीर्घ off, पूर्णांक count);
पूर्णांक esas2r_ग_लिखो_vda(काष्ठा esas2r_adapter *a, स्थिर अक्षर *buf, दीर्घ off,
		     पूर्णांक count);
पूर्णांक esas2r_पढ़ो_fs(काष्ठा esas2r_adapter *a, अक्षर *buf, दीर्घ off, पूर्णांक count);
पूर्णांक esas2r_ग_लिखो_fs(काष्ठा esas2r_adapter *a, स्थिर अक्षर *buf, दीर्घ off,
		    पूर्णांक count);
व्योम esas2r_adapter_tasklet(अचिन्हित दीर्घ context);
irqवापस_t esas2r_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t esas2r_msi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
व्योम esas2r_kickoff_समयr(काष्ठा esas2r_adapter *a);

बाह्य स्थिर काष्ठा dev_pm_ops esas2r_pm_ops;

व्योम esas2r_fw_event_off(काष्ठा esas2r_adapter *a);
व्योम esas2r_fw_event_on(काष्ठा esas2r_adapter *a);
bool esas2r_nvram_ग_लिखो(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq,
			काष्ठा esas2r_sas_nvram *nvram);
व्योम esas2r_nvram_get_शेषs(काष्ठा esas2r_adapter *a,
			       काष्ठा esas2r_sas_nvram *nvram);
व्योम esas2r_complete_request_cb(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq);
व्योम esas2r_reset_detected(काष्ठा esas2r_adapter *a);
व्योम esas2r_target_state_changed(काष्ठा esas2r_adapter *ha, u16 targ_id,
				 u8 state);
पूर्णांक esas2r_req_status_to_error(u8 req_stat);
व्योम esas2r_समाप्त_adapter(पूर्णांक i);
व्योम esas2r_मुक्त_request(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq);
काष्ठा esas2r_request *esas2r_alloc_request(काष्ठा esas2r_adapter *a);
u32 esas2r_get_uncached_size(काष्ठा esas2r_adapter *a);
bool esas2r_init_adapter_काष्ठा(काष्ठा esas2r_adapter *a,
				व्योम **uncached_area);
bool esas2r_check_adapter(काष्ठा esas2r_adapter *a);
bool esas2r_init_adapter_hw(काष्ठा esas2r_adapter *a, bool init_poll);
व्योम esas2r_start_request(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq);
bool esas2r_send_task_mgmt(काष्ठा esas2r_adapter *a,
			   काष्ठा esas2r_request *rqaux, u8 task_mgt_func);
व्योम esas2r_करो_tasklet_tasks(काष्ठा esas2r_adapter *a);
व्योम esas2r_adapter_पूर्णांकerrupt(काष्ठा esas2r_adapter *a);
व्योम esas2r_करो_deferred_processes(काष्ठा esas2r_adapter *a);
व्योम esas2r_reset_bus(काष्ठा esas2r_adapter *a);
व्योम esas2r_reset_adapter(काष्ठा esas2r_adapter *a);
व्योम esas2r_समयr_tick(काष्ठा esas2r_adapter *a);
स्थिर अक्षर *esas2r_get_model_name(काष्ठा esas2r_adapter *a);
स्थिर अक्षर *esas2r_get_model_name_लघु(काष्ठा esas2r_adapter *a);
u32 esas2r_stall_execution(काष्ठा esas2r_adapter *a, u32 start_समय,
			   u32 *delay);
व्योम esas2r_build_flash_req(काष्ठा esas2r_adapter *a,
			    काष्ठा esas2r_request *rq,
			    u8 sub_func,
			    u8 cksum,
			    u32 addr,
			    u32 length);
व्योम esas2r_build_mgt_req(काष्ठा esas2r_adapter *a,
			  काष्ठा esas2r_request *rq,
			  u8 sub_func,
			  u8 scan_gen,
			  u16 dev_index,
			  u32 length,
			  व्योम *data);
व्योम esas2r_build_ae_req(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq);
व्योम esas2r_build_cli_req(काष्ठा esas2r_adapter *a,
			  काष्ठा esas2r_request *rq,
			  u32 length,
			  u32 cmd_rsp_len);
व्योम esas2r_build_ioctl_req(काष्ठा esas2r_adapter *a,
			    काष्ठा esas2r_request *rq,
			    u32 length,
			    u8 sub_func);
व्योम esas2r_build_cfg_req(काष्ठा esas2r_adapter *a,
			  काष्ठा esas2r_request *rq,
			  u8 sub_func,
			  u32 length,
			  व्योम *data);
व्योम esas2r_घातer_करोwn(काष्ठा esas2r_adapter *a);
bool esas2r_घातer_up(काष्ठा esas2r_adapter *a, bool init_poll);
व्योम esas2r_रुको_request(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq);
u32 esas2r_map_data_winकरोw(काष्ठा esas2r_adapter *a, u32 addr_lo);
bool esas2r_process_fs_ioctl(काष्ठा esas2r_adapter *a,
			     काष्ठा esas2r_ioctl_fs *fs,
			     काष्ठा esas2r_request *rq,
			     काष्ठा esas2r_sg_context *sgc);
bool esas2r_पढ़ो_flash_block(काष्ठा esas2r_adapter *a, व्योम *to, u32 from,
			     u32 size);
bool esas2r_पढ़ो_mem_block(काष्ठा esas2r_adapter *a, व्योम *to, u32 from,
			   u32 size);
bool esas2r_fm_api(काष्ठा esas2r_adapter *a, काष्ठा esas2r_flash_img *fi,
		   काष्ठा esas2r_request *rq, काष्ठा esas2r_sg_context *sgc);
व्योम esas2r_क्रमce_पूर्णांकerrupt(काष्ठा esas2r_adapter *a);
व्योम esas2r_local_start_request(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq);
व्योम esas2r_process_adapter_reset(काष्ठा esas2r_adapter *a);
व्योम esas2r_complete_request(काष्ठा esas2r_adapter *a,
			     काष्ठा esas2r_request *rq);
व्योम esas2r_dummy_complete(काष्ठा esas2r_adapter *a,
			   काष्ठा esas2r_request *rq);
व्योम esas2r_ae_complete(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq);
व्योम esas2r_start_vda_request(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_request *rq);
bool esas2r_पढ़ो_flash_rev(काष्ठा esas2r_adapter *a);
bool esas2r_पढ़ो_image_type(काष्ठा esas2r_adapter *a);
bool esas2r_nvram_पढ़ो_direct(काष्ठा esas2r_adapter *a);
bool esas2r_nvram_validate(काष्ठा esas2r_adapter *a);
व्योम esas2r_nvram_set_शेषs(काष्ठा esas2r_adapter *a);
bool esas2r_prपूर्णांक_flash_rev(काष्ठा esas2r_adapter *a);
व्योम esas2r_send_reset_ae(काष्ठा esas2r_adapter *a, bool pwr_mgt);
bool esas2r_init_msgs(काष्ठा esas2r_adapter *a);
bool esas2r_is_adapter_present(काष्ठा esas2r_adapter *a);
व्योम esas2r_nuxi_mgt_data(u8 function, व्योम *data);
व्योम esas2r_nuxi_cfg_data(u8 function, व्योम *data);
व्योम esas2r_nuxi_ae_data(जोड़ atto_vda_ae *ae);
व्योम esas2r_reset_chip(काष्ठा esas2r_adapter *a);
व्योम esas2r_log_request_failure(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq);
व्योम esas2r_polled_पूर्णांकerrupt(काष्ठा esas2r_adapter *a);
bool esas2r_ioreq_पातed(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq,
			  u8 status);
bool esas2r_build_sg_list_sge(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_sg_context *sgc);
bool esas2r_build_sg_list_prd(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_sg_context *sgc);
व्योम esas2r_targ_db_initialize(काष्ठा esas2r_adapter *a);
व्योम esas2r_targ_db_हटाओ_all(काष्ठा esas2r_adapter *a, bool notअगरy);
व्योम esas2r_targ_db_report_changes(काष्ठा esas2r_adapter *a);
काष्ठा esas2r_target *esas2r_targ_db_add_raid(काष्ठा esas2r_adapter *a,
					      काष्ठा esas2r_disc_context *dc);
काष्ठा esas2r_target *esas2r_targ_db_add_pthru(काष्ठा esas2r_adapter *a,
					       काष्ठा esas2r_disc_context *dc,
					       u8 *ident,
					       u8 ident_len);
व्योम esas2r_targ_db_हटाओ(काष्ठा esas2r_adapter *a, काष्ठा esas2r_target *t);
काष्ठा esas2r_target *esas2r_targ_db_find_by_sas_addr(काष्ठा esas2r_adapter *a,
						      u64 *sas_addr);
काष्ठा esas2r_target *esas2r_targ_db_find_by_ident(काष्ठा esas2r_adapter *a,
						   व्योम *identअगरier,
						   u8 ident_len);
u16 esas2r_targ_db_find_next_present(काष्ठा esas2r_adapter *a, u16 target_id);
काष्ठा esas2r_target *esas2r_targ_db_find_by_virt_id(काष्ठा esas2r_adapter *a,
						     u16 virt_id);
u16 esas2r_targ_db_get_tgt_cnt(काष्ठा esas2r_adapter *a);
व्योम esas2r_disc_initialize(काष्ठा esas2r_adapter *a);
व्योम esas2r_disc_start_रुकोing(काष्ठा esas2r_adapter *a);
व्योम esas2r_disc_check_क्रम_work(काष्ठा esas2r_adapter *a);
व्योम esas2r_disc_check_complete(काष्ठा esas2r_adapter *a);
व्योम esas2r_disc_queue_event(काष्ठा esas2r_adapter *a, u8 disc_evt);
bool esas2r_disc_start_port(काष्ठा esas2r_adapter *a);
व्योम esas2r_disc_local_start_request(काष्ठा esas2r_adapter *a,
				     काष्ठा esas2r_request *rq);
bool esas2r_set_degraded_mode(काष्ठा esas2r_adapter *a, अक्षर *error_str);
bool esas2r_process_vda_ioctl(काष्ठा esas2r_adapter *a,
			      काष्ठा atto_ioctl_vda *vi,
			      काष्ठा esas2r_request *rq,
			      काष्ठा esas2r_sg_context *sgc);
व्योम esas2r_queue_fw_event(काष्ठा esas2r_adapter *a,
			   क्रमागत fw_event_type type,
			   व्योम *data,
			   पूर्णांक data_sz);

/* Inline functions */

/* Allocate a chip scatter/gather list entry */
अटल अंतरभूत काष्ठा esas2r_mem_desc *esas2r_alloc_sgl(काष्ठा esas2r_adapter *a)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *sgl;
	काष्ठा esas2r_mem_desc *result = शून्य;

	spin_lock_irqsave(&a->sg_list_lock, flags);
	अगर (likely(!list_empty(&a->मुक्त_sg_list_head))) अणु
		sgl = a->मुक्त_sg_list_head.next;
		result = list_entry(sgl, काष्ठा esas2r_mem_desc, next_desc);
		list_del_init(sgl);
	पूर्ण
	spin_unlock_irqrestore(&a->sg_list_lock, flags);

	वापस result;
पूर्ण

/* Initialize a scatter/gather context */
अटल अंतरभूत व्योम esas2r_sgc_init(काष्ठा esas2r_sg_context *sgc,
				   काष्ठा esas2r_adapter *a,
				   काष्ठा esas2r_request *rq,
				   काष्ठा atto_vda_sge *first)
अणु
	sgc->adapter = a;
	sgc->first_req = rq;

	/*
	 * set the limit poपूर्णांकer such that an SGE poपूर्णांकer above this value
	 * would be the first one to overflow the SGL.
	 */
	sgc->sge.a64.limit = (काष्ठा atto_vda_sge *)((u8 *)rq->vrq
						     + (माप(जोड़
							       atto_vda_req) /
							8)
						     - माप(काष्ठा
							      atto_vda_sge));
	अगर (first) अणु
		sgc->sge.a64.last =
			sgc->sge.a64.curr = first;
		rq->vrq->scsi.sg_list_offset = (u8)
					       ((u8 *)first -
						(u8 *)rq->vrq);
	पूर्ण अन्यथा अणु
		sgc->sge.a64.last =
			sgc->sge.a64.curr = &rq->vrq->scsi.u.sge[0];
		rq->vrq->scsi.sg_list_offset =
			(u8)दुरत्व(काष्ठा atto_vda_scsi_req, u.sge);
	पूर्ण
	sgc->sge.a64.chain = शून्य;
पूर्ण

अटल अंतरभूत व्योम esas2r_rq_init_request(काष्ठा esas2r_request *rq,
					  काष्ठा esas2r_adapter *a)
अणु
	जोड़ atto_vda_req *vrq = rq->vrq;

	INIT_LIST_HEAD(&rq->sg_table_head);
	rq->data_buf = (व्योम *)(vrq + 1);
	rq->पूर्णांकerrupt_cb = शून्य;
	rq->comp_cb = esas2r_complete_request_cb;
	rq->flags = 0;
	rq->समयout = 0;
	rq->req_stat = RS_PENDING;
	rq->req_type = RT_INI_REQ;

	/* clear the outbound response */
	rq->func_rsp.dwords[0] = 0;
	rq->func_rsp.dwords[1] = 0;

	/*
	 * clear the size of the VDA request.  esas2r_build_sg_list() will
	 * only allow the size of the request to grow.  there are some
	 * management requests that go through there twice and the second
	 * समय through sets a smaller request size.  अगर this is not modअगरied
	 * at all we'll set it to the size of the entire VDA request.
	 */
	rq->vda_req_sz = RQ_SIZE_DEFAULT;

	/* req_table entry should be शून्य at this poपूर्णांक - अगर not, halt */

	अगर (a->req_table[LOWORD(vrq->scsi.handle)]) अणु
		esas2r_bugon();
	पूर्ण

	/* fill in the table क्रम this handle so we can get back to the
	 * request.
	 */
	a->req_table[LOWORD(vrq->scsi.handle)] = rq;

	/*
	 * add a reference number to the handle to make it unique (until it
	 * wraps of course) जबतक preserving the least signअगरicant word
	 */
	vrq->scsi.handle = (a->cmd_ref_no++ << 16) | (u16)vrq->scsi.handle;

	/*
	 * the following क्रमmats a SCSI request.  the caller can override as
	 * necessary.  clear_vda_request can be called to clear the VDA
	 * request क्रम another type of request.
	 */
	vrq->scsi.function = VDA_FUNC_SCSI;
	vrq->scsi.sense_len = SENSE_DATA_SZ;

	/* clear out sg_list_offset and chain_offset */
	vrq->scsi.sg_list_offset = 0;
	vrq->scsi.chain_offset = 0;
	vrq->scsi.flags = 0;
	vrq->scsi.reserved = 0;

	/* set the sense buffer to be the data payload buffer */
	vrq->scsi.ppsense_buf
		= cpu_to_le64(rq->vrq_md->phys_addr +
			      माप(जोड़ atto_vda_req));
पूर्ण

अटल अंतरभूत व्योम esas2r_rq_मुक्त_sg_lists(काष्ठा esas2r_request *rq,
					   काष्ठा esas2r_adapter *a)
अणु
	अचिन्हित दीर्घ flags;

	अगर (list_empty(&rq->sg_table_head))
		वापस;

	spin_lock_irqsave(&a->sg_list_lock, flags);
	list_splice_tail_init(&rq->sg_table_head, &a->मुक्त_sg_list_head);
	spin_unlock_irqrestore(&a->sg_list_lock, flags);
पूर्ण

अटल अंतरभूत व्योम esas2r_rq_destroy_request(काष्ठा esas2r_request *rq,
					     काष्ठा esas2r_adapter *a)

अणु
	esas2r_rq_मुक्त_sg_lists(rq, a);
	a->req_table[LOWORD(rq->vrq->scsi.handle)] = शून्य;
	rq->data_buf = शून्य;
पूर्ण

अटल अंतरभूत bool esas2r_is_tasklet_pending(काष्ठा esas2r_adapter *a)
अणु

	वापस test_bit(AF_BUSRST_NEEDED, &a->flags) ||
	       test_bit(AF_BUSRST_DETECTED, &a->flags) ||
	       test_bit(AF_CHPRST_NEEDED, &a->flags) ||
	       test_bit(AF_CHPRST_DETECTED, &a->flags) ||
	       test_bit(AF_PORT_CHANGE, &a->flags);

पूर्ण

/*
 * Build the scatter/gather list क्रम an I/O request according to the
 * specअगरications placed in the esas2r_sg_context.  The caller must initialize
 * काष्ठा esas2r_sg_context prior to the initial call by calling
 * esas2r_sgc_init()
 */
अटल अंतरभूत bool esas2r_build_sg_list(काष्ठा esas2r_adapter *a,
					काष्ठा esas2r_request *rq,
					काष्ठा esas2r_sg_context *sgc)
अणु
	अगर (unlikely(le32_to_cpu(rq->vrq->scsi.length) == 0))
		वापस true;

	वापस (*a->build_sgl)(a, sgc);
पूर्ण

अटल अंतरभूत व्योम esas2r_disable_chip_पूर्णांकerrupts(काष्ठा esas2r_adapter *a)
अणु
	अगर (atomic_inc_वापस(&a->dis_पूर्णांकs_cnt) == 1)
		esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_INT_MASK_OUT,
					    ESAS2R_INT_DIS_MASK);
पूर्ण

अटल अंतरभूत व्योम esas2r_enable_chip_पूर्णांकerrupts(काष्ठा esas2r_adapter *a)
अणु
	अगर (atomic_dec_वापस(&a->dis_पूर्णांकs_cnt) == 0)
		esas2r_ग_लिखो_रेजिस्टर_dword(a, MU_INT_MASK_OUT,
					    ESAS2R_INT_ENB_MASK);
पूर्ण

/* Schedule a TASKLET to perक्रमm non-पूर्णांकerrupt tasks that may require delays
 * or दीर्घ completion बार.
 */
अटल अंतरभूत व्योम esas2r_schedule_tasklet(काष्ठा esas2r_adapter *a)
अणु
	/* make sure we करोn't schedule twice */
	अगर (!test_and_set_bit(AF_TASKLET_SCHEDULED, &a->flags))
		tasklet_hi_schedule(&a->tasklet);
पूर्ण

अटल अंतरभूत व्योम esas2r_enable_heartbeat(काष्ठा esas2r_adapter *a)
अणु
	अगर (!test_bit(AF_DEGRADED_MODE, &a->flags) &&
	    !test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    (a->nvram->options2 & SASNVR2_HEARTBEAT))
		set_bit(AF_HEARTBEAT_ENB, &a->flags);
	अन्यथा
		clear_bit(AF_HEARTBEAT_ENB, &a->flags);
पूर्ण

अटल अंतरभूत व्योम esas2r_disable_heartbeat(काष्ठा esas2r_adapter *a)
अणु
	clear_bit(AF_HEARTBEAT_ENB, &a->flags);
	clear_bit(AF_HEARTBEAT, &a->flags);
पूर्ण

/* Set the initial state क्रम resetting the adapter on the next pass through
 * esas2r_करो_deferred.
 */
अटल अंतरभूत व्योम esas2r_local_reset_adapter(काष्ठा esas2r_adapter *a)
अणु
	esas2r_disable_heartbeat(a);

	set_bit(AF_CHPRST_NEEDED, &a->flags);
	set_bit(AF_CHPRST_PENDING, &a->flags);
	set_bit(AF_DISC_PENDING, &a->flags);
पूर्ण

/* See अगर an पूर्णांकerrupt is pending on the adapter. */
अटल अंतरभूत bool esas2r_adapter_पूर्णांकerrupt_pending(काष्ठा esas2r_adapter *a)
अणु
	u32 पूर्णांकstat;

	अगर (a->पूर्णांक_mask == 0)
		वापस false;

	पूर्णांकstat = esas2r_पढ़ो_रेजिस्टर_dword(a, MU_INT_STATUS_OUT);

	अगर ((पूर्णांकstat & a->पूर्णांक_mask) == 0)
		वापस false;

	esas2r_disable_chip_पूर्णांकerrupts(a);

	a->पूर्णांक_stat = पूर्णांकstat;
	a->पूर्णांक_mask = 0;

	वापस true;
पूर्ण

अटल अंतरभूत u16 esas2r_targ_get_id(काष्ठा esas2r_target *t,
				     काष्ठा esas2r_adapter *a)
अणु
	वापस (u16)(uपूर्णांकptr_t)(t - a->targetdb);
पूर्ण

/*  Build and start an asynchronous event request */
अटल अंतरभूत व्योम esas2r_start_ae_request(काष्ठा esas2r_adapter *a,
					   काष्ठा esas2r_request *rq)
अणु
	अचिन्हित दीर्घ flags;

	esas2r_build_ae_req(a, rq);

	spin_lock_irqsave(&a->queue_lock, flags);
	esas2r_start_vda_request(a, rq);
	spin_unlock_irqrestore(&a->queue_lock, flags);
पूर्ण

अटल अंतरभूत व्योम esas2r_comp_list_drain(काष्ठा esas2r_adapter *a,
					  काष्ठा list_head *comp_list)
अणु
	काष्ठा esas2r_request *rq;
	काष्ठा list_head *element, *next;

	list_क्रम_each_safe(element, next, comp_list) अणु
		rq = list_entry(element, काष्ठा esas2r_request, comp_list);
		list_del_init(element);
		esas2r_complete_request(a, rq);
	पूर्ण
पूर्ण

/* sysfs handlers */
बाह्य काष्ठा bin_attribute bin_attr_fw;
बाह्य काष्ठा bin_attribute bin_attr_fs;
बाह्य काष्ठा bin_attribute bin_attr_vda;
बाह्य काष्ठा bin_attribute bin_attr_hw;
बाह्य काष्ठा bin_attribute bin_attr_live_nvram;
बाह्य काष्ठा bin_attribute bin_attr_शेष_nvram;

#पूर्ण_अगर /* ESAS2R_H */
