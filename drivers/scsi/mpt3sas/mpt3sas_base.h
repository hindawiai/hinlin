<शैली गुरु>
/*
 * This is the Fusion MPT base driver providing common API layer पूर्णांकerface
 * क्रम access to MPT (Message Passing Technology) firmware.
 *
 * This code is based on drivers/scsi/mpt3sas/mpt3sas_base.h
 * Copyright (C) 2012-2014  LSI Corporation
 * Copyright (C) 2013-2014 Avago Technologies
 *  (mailto: MPT-FusionLinux.pdl@avagotech.com)
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

 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#अगर_अघोषित MPT3SAS_BASE_H_INCLUDED
#घोषणा MPT3SAS_BASE_H_INCLUDED

#समावेश "mpi/mpi2_type.h"
#समावेश "mpi/mpi2.h"
#समावेश "mpi/mpi2_ioc.h"
#समावेश "mpi/mpi2_cnfg.h"
#समावेश "mpi/mpi2_init.h"
#समावेश "mpi/mpi2_raid.h"
#समावेश "mpi/mpi2_tool.h"
#समावेश "mpi/mpi2_sas.h"
#समावेश "mpi/mpi2_pci.h"
#समावेश "mpi/mpi2_image.h"

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/irq_poll.h>

#समावेश "mpt3sas_debug.h"
#समावेश "mpt3sas_trigger_diag.h"
#समावेश "mpt3sas_trigger_pages.h"

/* driver versioning info */
#घोषणा MPT3SAS_DRIVER_NAME		"mpt3sas"
#घोषणा MPT3SAS_AUTHOR "Avago Technologies <MPT-FusionLinux.pdl@avagotech.com>"
#घोषणा MPT3SAS_DESCRIPTION	"LSI MPT Fusion SAS 3.0 Device Driver"
#घोषणा MPT3SAS_DRIVER_VERSION		"37.101.00.00"
#घोषणा MPT3SAS_MAJOR_VERSION		37
#घोषणा MPT3SAS_MINOR_VERSION		101
#घोषणा MPT3SAS_BUILD_VERSION		0
#घोषणा MPT3SAS_RELEASE_VERSION	00

#घोषणा MPT2SAS_DRIVER_NAME		"mpt2sas"
#घोषणा MPT2SAS_DESCRIPTION	"LSI MPT Fusion SAS 2.0 Device Driver"
#घोषणा MPT2SAS_DRIVER_VERSION		"20.102.00.00"
#घोषणा MPT2SAS_MAJOR_VERSION		20
#घोषणा MPT2SAS_MINOR_VERSION		102
#घोषणा MPT2SAS_BUILD_VERSION		0
#घोषणा MPT2SAS_RELEASE_VERSION	00

/* CoreDump: Default समयout */
#घोषणा MPT3SAS_DEFAULT_COREDUMP_TIMEOUT_SECONDS	(15) /*15 seconds*/
#घोषणा MPT3SAS_COREDUMP_LOOP_DONE                     (0xFF)
#घोषणा MPT3SAS_TIMESYNC_TIMEOUT_SECONDS		(10) /* 10 seconds */
#घोषणा MPT3SAS_TIMESYNC_UPDATE_INTERVAL		(900) /* 15 minutes */
#घोषणा MPT3SAS_TIMESYNC_UNIT_MASK			(0x80) /* bit 7 */
#घोषणा MPT3SAS_TIMESYNC_MASK				(0x7F) /* 0 - 6 bits */
#घोषणा SECONDS_PER_MIN					(60)
#घोषणा SECONDS_PER_HOUR				(3600)
#घोषणा MPT3SAS_COREDUMP_LOOP_DONE			(0xFF)
#घोषणा MPI26_SET_IOC_PARAMETER_SYNC_TIMESTAMP		(0x81)

/*
 * Set MPT3SAS_SG_DEPTH value based on user input.
 */
#घोषणा MPT_MAX_PHYS_SEGMENTS	SG_CHUNK_SIZE
#घोषणा MPT_MIN_PHYS_SEGMENTS	16
#घोषणा MPT_KDUMP_MIN_PHYS_SEGMENTS	32

#घोषणा MCPU_MAX_CHAINS_PER_IO	3

#अगर_घोषित CONFIG_SCSI_MPT3SAS_MAX_SGE
#घोषणा MPT3SAS_SG_DEPTH		CONFIG_SCSI_MPT3SAS_MAX_SGE
#अन्यथा
#घोषणा MPT3SAS_SG_DEPTH		MPT_MAX_PHYS_SEGMENTS
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCSI_MPT2SAS_MAX_SGE
#घोषणा MPT2SAS_SG_DEPTH		CONFIG_SCSI_MPT2SAS_MAX_SGE
#अन्यथा
#घोषणा MPT2SAS_SG_DEPTH		MPT_MAX_PHYS_SEGMENTS
#पूर्ण_अगर

/*
 * Generic Defines
 */
#घोषणा MPT3SAS_SATA_QUEUE_DEPTH	32
#घोषणा MPT3SAS_SAS_QUEUE_DEPTH		254
#घोषणा MPT3SAS_RAID_QUEUE_DEPTH	128
#घोषणा MPT3SAS_KDUMP_SCSI_IO_DEPTH	200

#घोषणा MPT3SAS_RAID_MAX_SECTORS	8192
#घोषणा MPT3SAS_HOST_PAGE_SIZE_4K	12
#घोषणा MPT3SAS_NVME_QUEUE_DEPTH	128
#घोषणा MPT_NAME_LENGTH			32	/* generic length of strings */
#घोषणा MPT_STRING_LENGTH		64
#घोषणा MPI_FRAME_START_OFFSET		256
#घोषणा REPLY_FREE_POOL_SIZE		512 /*(32 maxcredix *4)*(4 बार)*/

#घोषणा MPT_MAX_CALLBACKS		32

#घोषणा INTERNAL_CMDS_COUNT		10	/* reserved cmds */
/* reserved क्रम issuing पूर्णांकernally framed scsi io cmds */
#घोषणा INTERNAL_SCSIIO_CMDS_COUNT	3

#घोषणा MPI3_HIM_MASK			0xFFFFFFFF /* mask every bit*/

#घोषणा MPT3SAS_INVALID_DEVICE_HANDLE	0xFFFF

#घोषणा MAX_CHAIN_ELEMT_SZ		16
#घोषणा DEFAULT_NUM_FWCHAIN_ELEMTS	8

#घोषणा IO_UNIT_CONTROL_SHUTDOWN_TIMEOUT 6
#घोषणा FW_IMG_HDR_READ_TIMEOUT	15

#घोषणा IOC_OPERATIONAL_WAIT_COUNT	10

/*
 * NVMe defines
 */
#घोषणा	NVME_PRP_SIZE			8	/* PRP size */
#घोषणा	NVME_ERROR_RESPONSE_SIZE	16	/* Max NVME Error Response */
#घोषणा NVME_TASK_ABORT_MIN_TIMEOUT	6
#घोषणा NVME_TASK_ABORT_MAX_TIMEOUT	60
#घोषणा NVME_TASK_MNGT_CUSTOM_MASK	(0x0010)
#घोषणा	NVME_PRP_PAGE_SIZE		4096	/* Page size */

काष्ठा mpt3sas_nvme_cmd अणु
	u8	rsvd[24];
	__le64	prp1;
	__le64	prp2;
पूर्ण;

/*
 * logging क्रमmat
 */
#घोषणा ioc_err(ioc, fmt, ...)						\
	pr_err("%s: " fmt, (ioc)->name, ##__VA_ARGS__)
#घोषणा ioc_notice(ioc, fmt, ...)					\
	pr_notice("%s: " fmt, (ioc)->name, ##__VA_ARGS__)
#घोषणा ioc_warn(ioc, fmt, ...)						\
	pr_warn("%s: " fmt, (ioc)->name, ##__VA_ARGS__)
#घोषणा ioc_info(ioc, fmt, ...)						\
	pr_info("%s: " fmt, (ioc)->name, ##__VA_ARGS__)

/*
 *  WarpDrive Specअगरic Log codes
 */

#घोषणा MPT2_WARPDRIVE_LOGENTRY		(0x8002)
#घोषणा MPT2_WARPDRIVE_LC_SSDT			(0x41)
#घोषणा MPT2_WARPDRIVE_LC_SSDLW		(0x43)
#घोषणा MPT2_WARPDRIVE_LC_SSDLF		(0x44)
#घोषणा MPT2_WARPDRIVE_LC_BRMF			(0x4D)

/*
 * per target निजी data
 */
#घोषणा MPT_TARGET_FLAGS_RAID_COMPONENT	0x01
#घोषणा MPT_TARGET_FLAGS_VOLUME		0x02
#घोषणा MPT_TARGET_FLAGS_DELETED	0x04
#घोषणा MPT_TARGET_FASTPATH_IO		0x08
#घोषणा MPT_TARGET_FLAGS_PCIE_DEVICE	0x10

#घोषणा SAS2_PCI_DEVICE_B0_REVISION	(0x01)
#घोषणा SAS3_PCI_DEVICE_C0_REVISION	(0x02)

/* Atlas PCIe Switch Management Port */
#घोषणा MPI26_ATLAS_PCIe_SWITCH_DEVID	(0x00B2)

/*
 * Intel HBA bअक्रमing
 */
#घोषणा MPT2SAS_INTEL_RMS25JB080_BRANDING    \
	"Intel(R) Integrated RAID Module RMS25JB080"
#घोषणा MPT2SAS_INTEL_RMS25JB040_BRANDING    \
	"Intel(R) Integrated RAID Module RMS25JB040"
#घोषणा MPT2SAS_INTEL_RMS25KB080_BRANDING    \
	"Intel(R) Integrated RAID Module RMS25KB080"
#घोषणा MPT2SAS_INTEL_RMS25KB040_BRANDING    \
	"Intel(R) Integrated RAID Module RMS25KB040"
#घोषणा MPT2SAS_INTEL_RMS25LB040_BRANDING	\
	"Intel(R) Integrated RAID Module RMS25LB040"
#घोषणा MPT2SAS_INTEL_RMS25LB080_BRANDING	\
	"Intel(R) Integrated RAID Module RMS25LB080"
#घोषणा MPT2SAS_INTEL_RMS2LL080_BRANDING	\
	"Intel Integrated RAID Module RMS2LL080"
#घोषणा MPT2SAS_INTEL_RMS2LL040_BRANDING	\
	"Intel Integrated RAID Module RMS2LL040"
#घोषणा MPT2SAS_INTEL_RS25GB008_BRANDING       \
	"Intel(R) RAID Controller RS25GB008"
#घोषणा MPT2SAS_INTEL_SSD910_BRANDING          \
	"Intel(R) SSD 910 Series"

#घोषणा MPT3SAS_INTEL_RMS3JC080_BRANDING       \
	"Intel(R) Integrated RAID Module RMS3JC080"
#घोषणा MPT3SAS_INTEL_RS3GC008_BRANDING       \
	"Intel(R) RAID Controller RS3GC008"
#घोषणा MPT3SAS_INTEL_RS3FC044_BRANDING       \
	"Intel(R) RAID Controller RS3FC044"
#घोषणा MPT3SAS_INTEL_RS3UC080_BRANDING       \
	"Intel(R) RAID Controller RS3UC080"

/*
 * Intel HBA SSDIDs
 */
#घोषणा MPT2SAS_INTEL_RMS25JB080_SSDID		0x3516
#घोषणा MPT2SAS_INTEL_RMS25JB040_SSDID		0x3517
#घोषणा MPT2SAS_INTEL_RMS25KB080_SSDID		0x3518
#घोषणा MPT2SAS_INTEL_RMS25KB040_SSDID		0x3519
#घोषणा MPT2SAS_INTEL_RMS25LB040_SSDID		0x351A
#घोषणा MPT2SAS_INTEL_RMS25LB080_SSDID		0x351B
#घोषणा MPT2SAS_INTEL_RMS2LL080_SSDID		0x350E
#घोषणा MPT2SAS_INTEL_RMS2LL040_SSDID		0x350F
#घोषणा MPT2SAS_INTEL_RS25GB008_SSDID		0x3000
#घोषणा MPT2SAS_INTEL_SSD910_SSDID		0x3700

#घोषणा MPT3SAS_INTEL_RMS3JC080_SSDID		0x3521
#घोषणा MPT3SAS_INTEL_RS3GC008_SSDID		0x3522
#घोषणा MPT3SAS_INTEL_RS3FC044_SSDID		0x3523
#घोषणा MPT3SAS_INTEL_RS3UC080_SSDID		0x3524

/*
 * Dell HBA bअक्रमing
 */
#घोषणा MPT2SAS_DELL_BRANDING_SIZE                 32

#घोषणा MPT2SAS_DELL_6GBPS_SAS_HBA_BRANDING        "Dell 6Gbps SAS HBA"
#घोषणा MPT2SAS_DELL_PERC_H200_ADAPTER_BRANDING    "Dell PERC H200 Adapter"
#घोषणा MPT2SAS_DELL_PERC_H200_INTEGRATED_BRANDING "Dell PERC H200 Integrated"
#घोषणा MPT2SAS_DELL_PERC_H200_MODULAR_BRANDING    "Dell PERC H200 Modular"
#घोषणा MPT2SAS_DELL_PERC_H200_EMBEDDED_BRANDING   "Dell PERC H200 Embedded"
#घोषणा MPT2SAS_DELL_PERC_H200_BRANDING            "Dell PERC H200"
#घोषणा MPT2SAS_DELL_6GBPS_SAS_BRANDING            "Dell 6Gbps SAS"

#घोषणा MPT3SAS_DELL_12G_HBA_BRANDING       \
	"Dell 12Gbps HBA"

/*
 * Dell HBA SSDIDs
 */
#घोषणा MPT2SAS_DELL_6GBPS_SAS_HBA_SSDID	0x1F1C
#घोषणा MPT2SAS_DELL_PERC_H200_ADAPTER_SSDID	0x1F1D
#घोषणा MPT2SAS_DELL_PERC_H200_INTEGRATED_SSDID	0x1F1E
#घोषणा MPT2SAS_DELL_PERC_H200_MODULAR_SSDID	0x1F1F
#घोषणा MPT2SAS_DELL_PERC_H200_EMBEDDED_SSDID	0x1F20
#घोषणा MPT2SAS_DELL_PERC_H200_SSDID		0x1F21
#घोषणा MPT2SAS_DELL_6GBPS_SAS_SSDID		0x1F22

#घोषणा MPT3SAS_DELL_12G_HBA_SSDID		0x1F46

/*
 * Cisco HBA bअक्रमing
 */
#घोषणा MPT3SAS_CISCO_12G_8E_HBA_BRANDING		\
	"Cisco 9300-8E 12G SAS HBA"
#घोषणा MPT3SAS_CISCO_12G_8I_HBA_BRANDING		\
	"Cisco 9300-8i 12G SAS HBA"
#घोषणा MPT3SAS_CISCO_12G_AVILA_HBA_BRANDING	\
	"Cisco 12G Modular SAS Pass through Controller"
#घोषणा MPT3SAS_CISCO_12G_COLUSA_MEZZANINE_HBA_BRANDING		\
	"UCS C3X60 12G SAS Pass through Controller"
/*
 * Cisco HBA SSSDIDs
 */
#घोषणा MPT3SAS_CISCO_12G_8E_HBA_SSDID  0x14C
#घोषणा MPT3SAS_CISCO_12G_8I_HBA_SSDID  0x154
#घोषणा MPT3SAS_CISCO_12G_AVILA_HBA_SSDID  0x155
#घोषणा MPT3SAS_CISCO_12G_COLUSA_MEZZANINE_HBA_SSDID  0x156

/*
 * status bits क्रम ioc->diag_buffer_status
 */
#घोषणा MPT3_DIAG_BUFFER_IS_REGISTERED	(0x01)
#घोषणा MPT3_DIAG_BUFFER_IS_RELEASED	(0x02)
#घोषणा MPT3_DIAG_BUFFER_IS_DIAG_RESET	(0x04)
#घोषणा MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED (0x08)
#घोषणा MPT3_DIAG_BUFFER_IS_APP_OWNED (0x10)

/*
 * HP HBA bअक्रमing
 */
#घोषणा MPT2SAS_HP_3PAR_SSVID                0x1590

#घोषणा MPT2SAS_HP_2_4_INTERNAL_BRANDING	\
	"HP H220 Host Bus Adapter"
#घोषणा MPT2SAS_HP_2_4_EXTERNAL_BRANDING	\
	"HP H221 Host Bus Adapter"
#घोषणा MPT2SAS_HP_1_4_INTERNAL_1_4_EXTERNAL_BRANDING	\
	"HP H222 Host Bus Adapter"
#घोषणा MPT2SAS_HP_EMBEDDED_2_4_INTERNAL_BRANDING	\
	"HP H220i Host Bus Adapter"
#घोषणा MPT2SAS_HP_DAUGHTER_2_4_INTERNAL_BRANDING	\
	"HP H210i Host Bus Adapter"

/*
 * HO HBA SSDIDs
 */
#घोषणा MPT2SAS_HP_2_4_INTERNAL_SSDID			0x0041
#घोषणा MPT2SAS_HP_2_4_EXTERNAL_SSDID			0x0042
#घोषणा MPT2SAS_HP_1_4_INTERNAL_1_4_EXTERNAL_SSDID	0x0043
#घोषणा MPT2SAS_HP_EMBEDDED_2_4_INTERNAL_SSDID		0x0044
#घोषणा MPT2SAS_HP_DAUGHTER_2_4_INTERNAL_SSDID		0x0046

/*
 * Combined Reply Queue स्थिरants,
 * There are twelve Supplemental Reply Post Host Index Registers
 * and each रेजिस्टर is at offset 0x10 bytes from the previous one.
 */
#घोषणा MAX_COMBINED_MSIX_VECTORS(gen35) ((gen35 == 1) ? 16 : 8)
#घोषणा MPT3_SUP_REPLY_POST_HOST_INDEX_REG_COUNT_G3	12
#घोषणा MPT3_SUP_REPLY_POST_HOST_INDEX_REG_COUNT_G35	16
#घोषणा MPT3_SUP_REPLY_POST_HOST_INDEX_REG_OFFSET	(0x10)

/* OEM Identअगरiers */
#घोषणा MFG10_OEM_ID_INVALID                   (0x00000000)
#घोषणा MFG10_OEM_ID_DELL                      (0x00000001)
#घोषणा MFG10_OEM_ID_FSC                       (0x00000002)
#घोषणा MFG10_OEM_ID_SUN                       (0x00000003)
#घोषणा MFG10_OEM_ID_IBM                       (0x00000004)

/* GENERIC Flags 0*/
#घोषणा MFG10_GF0_OCE_DISABLED                 (0x00000001)
#घोषणा MFG10_GF0_R1E_DRIVE_COUNT              (0x00000002)
#घोषणा MFG10_GF0_R10_DISPLAY                  (0x00000004)
#घोषणा MFG10_GF0_SSD_DATA_SCRUB_DISABLE       (0x00000008)
#घोषणा MFG10_GF0_SINGLE_DRIVE_R0              (0x00000010)

#घोषणा VIRTUAL_IO_FAILED_RETRY			(0x32010081)

/* High IOPs definitions */
#घोषणा MPT3SAS_DEVICE_HIGH_IOPS_DEPTH		8
#घोषणा MPT3SAS_HIGH_IOPS_REPLY_QUEUES		8
#घोषणा MPT3SAS_HIGH_IOPS_BATCH_COUNT		16
#घोषणा MPT3SAS_GEN35_MAX_MSIX_QUEUES		128
#घोषणा RDPQ_MAX_INDEX_IN_ONE_CHUNK		16

/* OEM Specअगरic Flags will come from OEM specअगरic header files */
काष्ठा Mpi2ManufacturingPage10_t अणु
	MPI2_CONFIG_PAGE_HEADER	Header;		/* 00h */
	U8	OEMIdentअगरier;			/* 04h */
	U8	Reserved1;			/* 05h */
	U16	Reserved2;			/* 08h */
	U32	Reserved3;			/* 0Ch */
	U32	GenericFlags0;			/* 10h */
	U32	GenericFlags1;			/* 14h */
	U32	Reserved4;			/* 18h */
	U32	OEMSpecअगरicFlags0;		/* 1Ch */
	U32	OEMSpecअगरicFlags1;		/* 20h */
	U32	Reserved5[18];			/* 24h - 60h*/
पूर्ण;


/* Miscellaneous options */
काष्ठा Mpi2ManufacturingPage11_t अणु
	MPI2_CONFIG_PAGE_HEADER Header;		/* 00h */
	__le32	Reserved1;			/* 04h */
	u8	Reserved2;			/* 08h */
	u8	EEDPTagMode;			/* 09h */
	u8	Reserved3;			/* 0Ah */
	u8	Reserved4;			/* 0Bh */
	__le32	Reserved5[8];			/* 0Ch-2Ch */
	u16	AddlFlags2;			/* 2Ch */
	u8	AddlFlags3;			/* 2Eh */
	u8	Reserved6;			/* 2Fh */
	__le32	Reserved7[7];			/* 30h - 4Bh */
	u8	NVMeAbortTO;			/* 4Ch */
	u8	NumPerDevEvents;		/* 4Dh */
	u8	HostTraceBufferDecrementSizeKB;	/* 4Eh */
	u8	HostTraceBufferFlags;		/* 4Fh */
	u16	HostTraceBufferMaxSizeKB;	/* 50h */
	u16	HostTraceBufferMinSizeKB;	/* 52h */
	u8	CoreDumpTOSec;			/* 54h */
	u8	TimeSyncInterval;		/* 55h */
	u16	Reserved9;			/* 56h */
	__le32	Reserved10;			/* 58h */
पूर्ण;

/**
 * काष्ठा MPT3SAS_TARGET - starget निजी hostdata
 * @starget: starget object
 * @sas_address: target sas address
 * @raid_device: raid_device poपूर्णांकer to access volume data
 * @handle: device handle
 * @num_luns: number luns
 * @flags: MPT_TARGET_FLAGS_XXX flags
 * @deleted: target flaged क्रम deletion
 * @पंचांग_busy: target is busy with TM request.
 * @port: hba port entry containing target's port number info
 * @sas_dev: The sas_device associated with this target
 * @pcie_dev: The pcie device associated with this target
 */
काष्ठा MPT3SAS_TARGET अणु
	काष्ठा scsi_target *starget;
	u64	sas_address;
	काष्ठा _raid_device *raid_device;
	u16	handle;
	पूर्णांक	num_luns;
	u32	flags;
	u8	deleted;
	u8	पंचांग_busy;
	काष्ठा hba_port *port;
	काष्ठा _sas_device *sas_dev;
	काष्ठा _pcie_device *pcie_dev;
पूर्ण;


/*
 * per device निजी data
 */
#घोषणा MPT_DEVICE_FLAGS_INIT		0x01

#घोषणा MFG_PAGE10_HIDE_SSDS_MASK	(0x00000003)
#घोषणा MFG_PAGE10_HIDE_ALL_DISKS	(0x00)
#घोषणा MFG_PAGE10_EXPOSE_ALL_DISKS	(0x01)
#घोषणा MFG_PAGE10_HIDE_IF_VOL_PRESENT	(0x02)

/**
 * काष्ठा MPT3SAS_DEVICE - sdev निजी hostdata
 * @sas_target: starget निजी hostdata
 * @lun: lun number
 * @flags: MPT_DEVICE_XXX flags
 * @configured_lun: lun is configured
 * @block: device is in SDEV_BLOCK state
 * @tlr_snoop_check: flag used in determining whether to disable TLR
 * @eedp_enable: eedp support enable bit
 * @eedp_type: 0(type_1), 1(type_2), 2(type_3)
 * @eedp_block_length: block size
 * @ata_command_pending: SATL passthrough outstanding क्रम device
 */
काष्ठा MPT3SAS_DEVICE अणु
	काष्ठा MPT3SAS_TARGET *sas_target;
	अचिन्हित पूर्णांक	lun;
	u32	flags;
	u8	configured_lun;
	u8	block;
	u8	tlr_snoop_check;
	u8	ignore_delay_हटाओ;
	/* Iopriority Command Handling */
	u8	ncq_prio_enable;
	/*
	 * Bug workaround क्रम SATL handling: the mpt2/3sas firmware
	 * करोesn't वापस BUSY or TASK_SET_FULL क्रम subsequent
	 * commands जबतक a SATL pass through is in operation as the
	 * spec requires, it simply करोes nothing with them until the
	 * pass through completes, causing them possibly to समयout अगर
	 * the passthrough is a दीर्घ executing command (like क्रमmat or
	 * secure erase).  This variable allows us to करो the right
	 * thing जबतक a SATL command is pending.
	 */
	अचिन्हित दीर्घ ata_command_pending;

पूर्ण;

#घोषणा MPT3_CMD_NOT_USED	0x8000	/* मुक्त */
#घोषणा MPT3_CMD_COMPLETE	0x0001	/* completed */
#घोषणा MPT3_CMD_PENDING	0x0002	/* pending */
#घोषणा MPT3_CMD_REPLY_VALID	0x0004	/* reply is valid */
#घोषणा MPT3_CMD_RESET		0x0008	/* host reset dropped the command */

/**
 * काष्ठा _पूर्णांकernal_cmd - पूर्णांकernal commands काष्ठा
 * @mutex: mutex
 * @करोne: completion
 * @reply: reply message poपूर्णांकer
 * @sense: sense data
 * @status: MPT3_CMD_XXX status
 * @smid: प्रणाली message id
 */
काष्ठा _पूर्णांकernal_cmd अणु
	काष्ठा mutex mutex;
	काष्ठा completion करोne;
	व्योम	*reply;
	व्योम	*sense;
	u16	status;
	u16	smid;
पूर्ण;



/**
 * काष्ठा _sas_device - attached device inक्रमmation
 * @list: sas device list
 * @starget: starget object
 * @sas_address: device sas address
 * @device_name: retrieved from the SAS IDENTIFY frame.
 * @handle: device handle
 * @sas_address_parent: sas address of parent expander or sas host
 * @enclosure_handle: enclosure handle
 * @enclosure_logical_id: enclosure logical identअगरier
 * @volume_handle: volume handle (valid when hidden raid member)
 * @volume_wwid: volume unique identअगरier
 * @device_info: bitfield provides detailed info about the device
 * @id: target id
 * @channel: target channel
 * @slot: number number
 * @phy: phy identअगरier provided in sas device page 0
 * @responding: used in _scsih_sas_device_mark_responding
 * @fast_path: fast path feature enable bit
 * @pfa_led_on: flag क्रम PFA LED status
 * @pend_sas_rphy_add: flag to check अगर device is in sas_rphy_add()
 *	addition routine.
 * @chassis_slot: chassis slot
 * @is_chassis_slot_valid: chassis slot valid or not
 * @port: hba port entry containing device's port number info
 * @rphy: device's sas_rphy address used to identअगरy this device काष्ठाure in
 *	target_alloc callback function
 */
काष्ठा _sas_device अणु
	काष्ठा list_head list;
	काष्ठा scsi_target *starget;
	u64	sas_address;
	u64	device_name;
	u16	handle;
	u64	sas_address_parent;
	u16	enclosure_handle;
	u64	enclosure_logical_id;
	u16	volume_handle;
	u64	volume_wwid;
	u32	device_info;
	पूर्णांक	id;
	पूर्णांक	channel;
	u16	slot;
	u8	phy;
	u8	responding;
	u8	fast_path;
	u8	pfa_led_on;
	u8	pend_sas_rphy_add;
	u8	enclosure_level;
	u8	chassis_slot;
	u8	is_chassis_slot_valid;
	u8	connector_name[5];
	काष्ठा kref refcount;
	काष्ठा hba_port *port;
	काष्ठा sas_rphy *rphy;
पूर्ण;

अटल अंतरभूत व्योम sas_device_get(काष्ठा _sas_device *s)
अणु
	kref_get(&s->refcount);
पूर्ण

अटल अंतरभूत व्योम sas_device_मुक्त(काष्ठा kref *r)
अणु
	kमुक्त(container_of(r, काष्ठा _sas_device, refcount));
पूर्ण

अटल अंतरभूत व्योम sas_device_put(काष्ठा _sas_device *s)
अणु
	kref_put(&s->refcount, sas_device_मुक्त);
पूर्ण

/*
 * काष्ठा _pcie_device - attached PCIe device inक्रमmation
 * @list: pcie device list
 * @starget: starget object
 * @wwid: device WWID
 * @handle: device handle
 * @device_info: bitfield provides detailed info about the device
 * @id: target id
 * @channel: target channel
 * @slot: slot number
 * @port_num: port number
 * @responding: used in _scsih_pcie_device_mark_responding
 * @fast_path: fast path feature enable bit
 * @nvme_mdts: MaximumDataTransferSize from PCIe Device Page 2 क्रम
 *		NVMe device only
 * @enclosure_handle: enclosure handle
 * @enclosure_logical_id: enclosure logical identअगरier
 * @enclosure_level: The level of device's enclosure from the controller
 * @connector_name: ASCII value of the Connector's name
 * @serial_number: poपूर्णांकer of serial number string allocated runसमय
 * @access_status: Device's Access Status
 * @shutकरोwn_latency: NVMe device's RTD3 Entry Latency
 * @refcount: reference count क्रम deletion
 */
काष्ठा _pcie_device अणु
	काष्ठा list_head list;
	काष्ठा scsi_target *starget;
	u64	wwid;
	u16	handle;
	u32	device_info;
	पूर्णांक	id;
	पूर्णांक	channel;
	u16	slot;
	u8	port_num;
	u8	responding;
	u8	fast_path;
	u32	nvme_mdts;
	u16	enclosure_handle;
	u64	enclosure_logical_id;
	u8	enclosure_level;
	u8	connector_name[4];
	u8	*serial_number;
	u8	reset_समयout;
	u8	access_status;
	u16	shutकरोwn_latency;
	काष्ठा kref refcount;
पूर्ण;
/**
 * pcie_device_get - Increment the pcie device reference count
 *
 * @p: pcie_device object
 *
 * When ever this function called it will increment the
 * reference count of the pcie device क्रम which this function called.
 *
 */
अटल अंतरभूत व्योम pcie_device_get(काष्ठा _pcie_device *p)
अणु
	kref_get(&p->refcount);
पूर्ण

/**
 * pcie_device_मुक्त - Release the pcie device object
 * @r - kref object
 *
 * Free's the pcie device object. It will be called when reference count
 * reaches to zero.
 */
अटल अंतरभूत व्योम pcie_device_मुक्त(काष्ठा kref *r)
अणु
	kमुक्त(container_of(r, काष्ठा _pcie_device, refcount));
पूर्ण

/**
 * pcie_device_put - Decrement the pcie device reference count
 *
 * @p: pcie_device object
 *
 * When ever this function called it will decrement the
 * reference count of the pcie device क्रम which this function called.
 *
 * When refernce count reaches to Zero, this will call pcie_device_मुक्त to the
 * pcie_device object.
 */
अटल अंतरभूत व्योम pcie_device_put(काष्ठा _pcie_device *p)
अणु
	kref_put(&p->refcount, pcie_device_मुक्त);
पूर्ण
/**
 * काष्ठा _raid_device - raid volume link list
 * @list: sas device list
 * @starget: starget object
 * @sdev: scsi device काष्ठा (volumes are single lun)
 * @wwid: unique identअगरier क्रम the volume
 * @handle: device handle
 * @block_size: Block size of the volume
 * @id: target id
 * @channel: target channel
 * @volume_type: the raid level
 * @device_info: bitfield provides detailed info about the hidden components
 * @num_pds: number of hidden raid components
 * @responding: used in _scsih_raid_device_mark_responding
 * @percent_complete: resync percent complete
 * @direct_io_enabled: Whether direct io to PDs are allowed or not
 * @stripe_exponent: X where 2घातX is the stripe sz in blocks
 * @block_exponent: X where 2घातX is the block sz in bytes
 * @max_lba: Maximum number of LBA in the volume
 * @stripe_sz: Stripe Size of the volume
 * @device_info: Device info of the volume member disk
 * @pd_handle: Array of handles of the physical drives क्रम direct I/O in le16
 */
#घोषणा MPT_MAX_WARPDRIVE_PDS		8
काष्ठा _raid_device अणु
	काष्ठा list_head list;
	काष्ठा scsi_target *starget;
	काष्ठा scsi_device *sdev;
	u64	wwid;
	u16	handle;
	u16	block_sz;
	पूर्णांक	id;
	पूर्णांक	channel;
	u8	volume_type;
	u8	num_pds;
	u8	responding;
	u8	percent_complete;
	u8	direct_io_enabled;
	u8	stripe_exponent;
	u8	block_exponent;
	u64	max_lba;
	u32	stripe_sz;
	u32	device_info;
	u16	pd_handle[MPT_MAX_WARPDRIVE_PDS];
पूर्ण;

/**
 * काष्ठा _boot_device - boot device info
 *
 * @channel: sas, raid, or pcie channel
 * @device: holds poपूर्णांकer क्रम काष्ठा _sas_device, काष्ठा _raid_device or
 *     काष्ठा _pcie_device
 */
काष्ठा _boot_device अणु
	पूर्णांक channel;
	व्योम *device;
पूर्ण;

/**
 * काष्ठा _sas_port - wide/narrow sas port inक्रमmation
 * @port_list: list of ports beदीर्घing to expander
 * @num_phys: number of phys beदीर्घing to this port
 * @remote_identअगरy: attached device identअगरication
 * @rphy: sas transport rphy object
 * @port: sas transport wide/narrow port object
 * @hba_port: hba port entry containing port's port number info
 * @phy_list: _sas_phy list objects beदीर्घing to this port
 */
काष्ठा _sas_port अणु
	काष्ठा list_head port_list;
	u8	num_phys;
	काष्ठा sas_identअगरy remote_identअगरy;
	काष्ठा sas_rphy *rphy;
	काष्ठा sas_port *port;
	काष्ठा hba_port *hba_port;
	काष्ठा list_head phy_list;
पूर्ण;

/**
 * काष्ठा _sas_phy - phy inक्रमmation
 * @port_siblings: list of phys beदीर्घing to a port
 * @identअगरy: phy identअगरication
 * @remote_identअगरy: attached device identअगरication
 * @phy: sas transport phy object
 * @phy_id: unique phy id
 * @handle: device handle क्रम this phy
 * @attached_handle: device handle क्रम attached device
 * @phy_beदीर्घs_to_port: port has been created क्रम this phy
 * @port: hba port entry containing port number info
 */
काष्ठा _sas_phy अणु
	काष्ठा list_head port_siblings;
	काष्ठा sas_identअगरy identअगरy;
	काष्ठा sas_identअगरy remote_identअगरy;
	काष्ठा sas_phy *phy;
	u8	phy_id;
	u16	handle;
	u16	attached_handle;
	u8	phy_beदीर्घs_to_port;
	u8	hba_vphy;
	काष्ठा hba_port *port;
पूर्ण;

/**
 * काष्ठा _sas_node - sas_host/expander inक्रमmation
 * @list: list of expanders
 * @parent_dev: parent device class
 * @num_phys: number phys beदीर्घing to this sas_host/expander
 * @sas_address: sas address of this sas_host/expander
 * @handle: handle क्रम this sas_host/expander
 * @sas_address_parent: sas address of parent expander or sas host
 * @enclosure_handle: handle क्रम this a member of an enclosure
 * @device_info: bitwise defining capabilities of this sas_host/expander
 * @responding: used in _scsih_expander_device_mark_responding
 * @phy: a list of phys that make up this sas_host/expander
 * @sas_port_list: list of ports attached to this sas_host/expander
 * @port: hba port entry containing node's port number info
 * @rphy: sas_rphy object of this expander
 */
काष्ठा _sas_node अणु
	काष्ठा list_head list;
	काष्ठा device *parent_dev;
	u8	num_phys;
	u64	sas_address;
	u16	handle;
	u64	sas_address_parent;
	u16	enclosure_handle;
	u64	enclosure_logical_id;
	u8	responding;
	काष्ठा hba_port *port;
	काष्ठा	_sas_phy *phy;
	काष्ठा list_head sas_port_list;
	काष्ठा sas_rphy *rphy;
पूर्ण;

/**
 * काष्ठा _enclosure_node - enclosure inक्रमmation
 * @list: list of enclosures
 * @pg0: enclosure pg0;
 */
काष्ठा _enclosure_node अणु
	काष्ठा list_head list;
	Mpi2SasEnclosurePage0_t pg0;
पूर्ण;

/**
 * क्रमागत reset_type - reset state
 * @FORCE_BIG_HAMMER: issue diagnostic reset
 * @SOFT_RESET: issue message_unit_reset, अगर fails to to big hammer
 */
क्रमागत reset_type अणु
	FORCE_BIG_HAMMER,
	SOFT_RESET,
पूर्ण;

/**
 * काष्ठा pcie_sg_list - PCIe SGL buffer (contiguous per I/O)
 * @pcie_sgl: PCIe native SGL क्रम NVMe devices
 * @pcie_sgl_dma: physical address
 */
काष्ठा pcie_sg_list अणु
	व्योम            *pcie_sgl;
	dma_addr_t      pcie_sgl_dma;
पूर्ण;

/**
 * काष्ठा chain_tracker - firmware chain tracker
 * @chain_buffer: chain buffer
 * @chain_buffer_dma: physical address
 * @tracker_list: list of मुक्त request (ioc->मुक्त_chain_list)
 */
काष्ठा chain_tracker अणु
	व्योम *chain_buffer;
	dma_addr_t chain_buffer_dma;
पूर्ण;

काष्ठा chain_lookup अणु
	काष्ठा chain_tracker *chains_per_smid;
	atomic_t	chain_offset;
पूर्ण;

/**
 * काष्ठा scsiio_tracker - scsi mf request tracker
 * @smid: प्रणाली message id
 * @cb_idx: callback index
 * @direct_io: To indicate whether I/O is direct (WARPDRIVE)
 * @chain_list: list of associated firmware chain tracker
 * @msix_io: IO's msix
 */
काष्ठा scsiio_tracker अणु
	u16	smid;
	काष्ठा scsi_cmnd *scmd;
	u8	cb_idx;
	u8	direct_io;
	काष्ठा pcie_sg_list pcie_sg_list;
	काष्ठा list_head chain_list;
	u16     msix_io;
पूर्ण;

/**
 * काष्ठा request_tracker - firmware request tracker
 * @smid: प्रणाली message id
 * @cb_idx: callback index
 * @tracker_list: list of मुक्त request (ioc->मुक्त_list)
 */
काष्ठा request_tracker अणु
	u16	smid;
	u8	cb_idx;
	काष्ठा list_head tracker_list;
पूर्ण;

/**
 * काष्ठा _tr_list - target reset list
 * @handle: device handle
 * @state: state machine
 */
काष्ठा _tr_list अणु
	काष्ठा list_head list;
	u16	handle;
	u16	state;
पूर्ण;

/**
 * काष्ठा _sc_list - delayed SAS_IO_UNIT_CONTROL message list
 * @handle: device handle
 */
काष्ठा _sc_list अणु
	काष्ठा list_head list;
	u16     handle;
पूर्ण;

/**
 * काष्ठा _event_ack_list - delayed event acknowledgment list
 * @Event: Event ID
 * @EventContext: used to track the event uniquely
 */
काष्ठा _event_ack_list अणु
	काष्ठा list_head list;
	U16     Event;
	U32     EventContext;
पूर्ण;

/**
 * काष्ठा adapter_reply_queue - the reply queue काष्ठा
 * @ioc: per adapter object
 * @msix_index: msix index पूर्णांकo vector table
 * @vector: irq vector
 * @reply_post_host_index: head index in the pool where FW completes IO
 * @reply_post_मुक्त: reply post base virt address
 * @name: the name रेजिस्टरed to request_irq()
 * @busy: isr is actively processing replies on another cpu
 * @os_irq: irq number
 * @irqpoll: irq_poll object
 * @irq_poll_scheduled: Tells whether irq poll is scheduled or not
 * @list: this list
*/
काष्ठा adapter_reply_queue अणु
	काष्ठा MPT3SAS_ADAPTER	*ioc;
	u8			msix_index;
	u32			reply_post_host_index;
	Mpi2ReplyDescriptorsUnion_t *reply_post_मुक्त;
	अक्षर			name[MPT_NAME_LENGTH];
	atomic_t		busy;
	u32			os_irq;
	काष्ठा irq_poll         irqpoll;
	bool			irq_poll_scheduled;
	bool			irq_line_enable;
	काष्ठा list_head	list;
पूर्ण;

प्रकार व्योम (*MPT_ADD_SGE)(व्योम *paddr, u32 flags_length, dma_addr_t dma_addr);

/* SAS3.0 support */
प्रकार पूर्णांक (*MPT_BUILD_SG_SCMD)(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा scsi_cmnd *scmd, u16 smid, काष्ठा _pcie_device *pcie_device);
प्रकार व्योम (*MPT_BUILD_SG)(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम *psge,
		dma_addr_t data_out_dma, माप_प्रकार data_out_sz,
		dma_addr_t data_in_dma, माप_प्रकार data_in_sz);
प्रकार व्योम (*MPT_BUILD_ZERO_LEN_SGE)(काष्ठा MPT3SAS_ADAPTER *ioc,
		व्योम *paddr);

/* SAS3.5 support */
प्रकार व्योम (*NVME_BUILD_PRP)(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	Mpi26NVMeEncapsulatedRequest_t *nvme_encap_request,
	dma_addr_t data_out_dma, माप_प्रकार data_out_sz, dma_addr_t data_in_dma,
	माप_प्रकार data_in_sz);

/* To support atomic and non atomic descriptors*/
प्रकार व्योम (*PUT_SMID_IO_FP_HIP) (काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u16 funcdep);
प्रकार व्योम (*PUT_SMID_DEFAULT) (काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);
प्रकार u32 (*BASE_READ_REG) (स्थिर अस्थिर व्योम __iomem *addr);
/*
 * To get high iops reply queue's msix index when high iops mode is enabled
 * अन्यथा get the msix index of general reply queues.
 */
प्रकार u8 (*GET_MSIX_INDEX) (काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा scsi_cmnd *scmd);

/* IOC Facts and Port Facts converted from little endian to cpu */
जोड़ mpi3_version_जोड़ अणु
	MPI2_VERSION_STRUCT		Struct;
	u32				Word;
पूर्ण;

काष्ठा mpt3sas_facts अणु
	u16			MsgVersion;
	u16			HeaderVersion;
	u8			IOCNumber;
	u8			VP_ID;
	u8			VF_ID;
	u16			IOCExceptions;
	u16			IOCStatus;
	u32			IOCLogInfo;
	u8			MaxChainDepth;
	u8			WhoInit;
	u8			NumberOfPorts;
	u8			MaxMSIxVectors;
	u16			RequestCredit;
	u16			ProductID;
	u32			IOCCapabilities;
	जोड़ mpi3_version_जोड़	FWVersion;
	u16			IOCRequestFrameSize;
	u16			IOCMaxChainSegmentSize;
	u16			MaxInitiators;
	u16			MaxTarमाला_लो;
	u16			MaxSasExpanders;
	u16			MaxEnclosures;
	u16			ProtocolFlags;
	u16			HighPriorityCredit;
	u16			MaxReplyDescriptorPostQueueDepth;
	u8			ReplyFrameSize;
	u8			MaxVolumes;
	u16			MaxDevHandle;
	u16			MaxPersistentEntries;
	u16			MinDevHandle;
	u8			CurrentHostPageSize;
पूर्ण;

काष्ठा mpt3sas_port_facts अणु
	u8			PortNumber;
	u8			VP_ID;
	u8			VF_ID;
	u8			PortType;
	u16			MaxPostedCmdBuffers;
पूर्ण;

काष्ठा reply_post_काष्ठा अणु
	Mpi2ReplyDescriptorsUnion_t	*reply_post_मुक्त;
	dma_addr_t			reply_post_मुक्त_dma;
पूर्ण;

/**
 * काष्ठा भव_phy - vSES phy काष्ठाure
 * sas_address: SAS Address of vSES device
 * phy_mask: vSES device's phy number
 * flags: flags used to manage this काष्ठाure
 */
काष्ठा भव_phy अणु
	काष्ठा	list_head list;
	u64	sas_address;
	u32	phy_mask;
	u8	flags;
पूर्ण;

#घोषणा MPT_VPHY_FLAG_सूचीTY_PHY	0x01

/**
 * काष्ठा hba_port - Saves each HBA's Wide/Narrow port info
 * @sas_address: sas address of this wide/narrow port's attached device
 * @phy_mask: HBA PHY's beदीर्घing to this port
 * @port_id: port number
 * @flags: hba port flags
 * @vphys_mask : mask of vSES devices Phy number
 * @vphys_list : list containing vSES device काष्ठाures
 */
काष्ठा hba_port अणु
	काष्ठा list_head list;
	u64	sas_address;
	u32	phy_mask;
	u8      port_id;
	u8	flags;
	u32	vphys_mask;
	काष्ठा list_head vphys_list;
पूर्ण;

/* hba port flags */
#घोषणा HBA_PORT_FLAG_सूचीTY_PORT       0x01
#घोषणा HBA_PORT_FLAG_NEW_PORT         0x02

#घोषणा MULTIPATH_DISABLED_PORT_ID     0xFF

/**
 * काष्ठा htb_rel_query - diagnostic buffer release reason
 * @unique_id - unique id associated with this buffer.
 * @buffer_rel_condition - Release condition ioctl/sysfs/reset
 * @reserved
 * @trigger_type - Master/Event/scsi/MPI
 * @trigger_info_dwords - Data Correspondig to trigger type
 */
काष्ठा htb_rel_query अणु
	u16	buffer_rel_condition;
	u16	reserved;
	u32	trigger_type;
	u32	trigger_info_dwords[2];
पूर्ण;

/* Buffer_rel_condition bit fields */

/* Bit 0 - Diag Buffer not Released */
#घोषणा MPT3_DIAG_BUFFER_NOT_RELEASED	(0x00)
/* Bit 0 - Diag Buffer Released */
#घोषणा MPT3_DIAG_BUFFER_RELEASED	(0x01)

/*
 * Bit 1 - Diag Buffer Released by IOCTL,
 * This bit is valid only अगर Bit 0 is one
 */
#घोषणा MPT3_DIAG_BUFFER_REL_IOCTL	(0x02 | MPT3_DIAG_BUFFER_RELEASED)

/*
 * Bit 2 - Diag Buffer Released by Trigger,
 * This bit is valid only अगर Bit 0 is one
 */
#घोषणा MPT3_DIAG_BUFFER_REL_TRIGGER	(0x04 | MPT3_DIAG_BUFFER_RELEASED)

/*
 * Bit 3 - Diag Buffer Released by SysFs,
 * This bit is valid only अगर Bit 0 is one
 */
#घोषणा MPT3_DIAG_BUFFER_REL_SYSFS	(0x08 | MPT3_DIAG_BUFFER_RELEASED)

/* DIAG RESET Master trigger flags */
#घोषणा MPT_DIAG_RESET_ISSUED_BY_DRIVER 0x00000000
#घोषणा MPT_DIAG_RESET_ISSUED_BY_USER	0x00000001

प्रकार व्योम (*MPT3SAS_FLUSH_RUNNING_CMDS)(काष्ठा MPT3SAS_ADAPTER *ioc);
/**
 * काष्ठा MPT3SAS_ADAPTER - per adapter काष्ठा
 * @list: ioc_list
 * @shost: shost object
 * @id: unique adapter id
 * @cpu_count: number online cpus
 * @name: generic ioc string
 * @पंचांगp_string: पंचांगp string used क्रम logging
 * @pdev: pci pdev object
 * @pio_chip: physical io रेजिस्टर space
 * @chip: memory mapped रेजिस्टर space
 * @chip_phys: physical addrss prior to mapping
 * @logging_level: see mpt3sas_debug.h
 * @fwfault_debug: debuging FW समयouts
 * @ir_firmware: IR firmware present
 * @bars: biपंचांगask of BAR's that must be configured
 * @mask_पूर्णांकerrupts: ignore पूर्णांकerrupt
 * @pci_access_mutex: Mutex to synchronize ioctl, sysfs show path and
 *			pci resource handling
 * @fault_reset_work_q_name: fw fault work queue
 * @fault_reset_work_q: ""
 * @fault_reset_work: ""
 * @firmware_event_name: fw event work queue
 * @firmware_event_thपढ़ो: ""
 * @fw_event_lock:
 * @fw_event_list: list of fw events
 * @current_evet: current processing firmware event
 * @fw_event_cleanup: set to one जबतक cleaning up the fw events
 * @aen_event_पढ़ो_flag: event log was पढ़ो
 * @broadcast_aen_busy: broadcast aen रुकोing to be serviced
 * @shost_recovery: host reset in progress
 * @ioc_reset_in_progress_lock:
 * @ioc_link_reset_in_progress: phy/hard reset in progress
 * @ignore_loginfos: ignore loginfos during task management
 * @हटाओ_host: flag क्रम when driver unloads, to aव्योम sending dev resets
 * @pci_error_recovery: flag to prevent ioc access until slot reset completes
 * @रुको_क्रम_discovery_to_complete: flag set at driver load समय when
 *                                               रुकोing on reporting devices
 * @is_driver_loading: flag set at driver load समय
 * @port_enable_failed: flag set when port enable has failed
 * @start_scan: flag set from scan_start callback, cleared from _mpt3sas_fw_work
 * @start_scan_failed: means port enable failed, वापस's the ioc_status
 * @msix_enable: flag indicating msix is enabled
 * @msix_vector_count: number msix vectors
 * @cpu_msix_table: table क्रम mapping cpus to msix index
 * @cpu_msix_table_sz: table size
 * @total_io_cnt: Gives total IO count, used to load balance the पूर्णांकerrupts
 * @ioc_coredump_loop: will have non-zero value when FW is in CoreDump state
 * @बारtamp_update_count: Counter to fire समयSync command
 * समय_sync_पूर्णांकerval: Time sync पूर्णांकerval पढ़ो from man page 11
 * @high_iops_outstanding: used to load balance the पूर्णांकerrupts
 *				within high iops reply queues
 * @msix_load_balance: Enables load balancing of पूर्णांकerrupts across
 * the multiple MSIXs
 * @schedule_dead_ioc_flush_running_cmds: callback to flush pending commands
 * @thresh_hold: Max number of reply descriptors processed
 *				beक्रमe updating Host Index
 * @drv_support_biपंचांगap: driver's supported feature bit map
 * @use_32bit_dma: Flag to use 32 bit consistent dma mask
 * @scsi_io_cb_idx: shost generated commands
 * @पंचांग_cb_idx: task management commands
 * @scsih_cb_idx: scsih पूर्णांकernal commands
 * @transport_cb_idx: transport पूर्णांकernal commands
 * @ctl_cb_idx: clt पूर्णांकernal commands
 * @base_cb_idx: base पूर्णांकernal commands
 * @config_cb_idx: base पूर्णांकernal commands
 * @पंचांग_tr_cb_idx : device removal target reset handshake
 * @पंचांग_tr_volume_cb_idx : volume removal target reset
 * @base_cmds:
 * @transport_cmds:
 * @scsih_cmds:
 * @पंचांग_cmds:
 * @ctl_cmds:
 * @config_cmds:
 * @base_add_sg_single: handler क्रम either 32/64 bit sgl's
 * @event_type: bits indicating which events to log
 * @event_context: unique id क्रम each logged event
 * @event_log: event log poपूर्णांकer
 * @event_masks: events that are masked
 * @max_shutकरोwn_latency: समयout value क्रम NVMe shutकरोwn operation,
 *			which is equal that NVMe drive's RTD3 Entry Latency
 *			which has reported maximum RTD3 Entry Latency value
 *			among attached NVMe drives.
 * @facts: अटल facts data
 * @prev_fw_facts: previous fw facts data
 * @pfacts: अटल port facts data
 * @manu_pg0: अटल manufacturing page 0
 * @manu_pg10: अटल manufacturing page 10
 * @manu_pg11: अटल manufacturing page 11
 * @bios_pg2: अटल bios page 2
 * @bios_pg3: अटल bios page 3
 * @ioc_pg8: अटल ioc page 8
 * @iounit_pg0: अटल iounit page 0
 * @iounit_pg1: अटल iounit page 1
 * @iounit_pg8: अटल iounit page 8
 * @sas_hba: sas host object
 * @sas_expander_list: expander object list
 * @enclosure_list: enclosure object list
 * @sas_node_lock:
 * @sas_device_list: sas device object list
 * @sas_device_init_list: sas device object list (used only at init समय)
 * @sas_device_lock:
 * @pcie_device_list: pcie device object list
 * @pcie_device_init_list: pcie device object list (used only at init समय)
 * @pcie_device_lock:
 * @io_missing_delay: समय क्रम IO completed by fw when PDR enabled
 * @device_missing_delay: समय क्रम device missing by fw when PDR enabled
 * @sas_id : used क्रम setting volume target IDs
 * @pcie_target_id: used क्रम setting pcie target IDs
 * @blocking_handles: biपंचांगask used to identअगरy which devices need blocking
 * @pd_handles : biपंचांगask क्रम PD handles
 * @pd_handles_sz : size of pd_handle biपंचांगask
 * @config_page_sz: config page size
 * @config_page: reserve memory क्रम config page payload
 * @config_page_dma:
 * @hba_queue_depth: hba request queue depth
 * @sge_size: sg element size क्रम either 32/64 bit
 * @scsiio_depth: SCSI_IO queue depth
 * @request_sz: per request frame size
 * @request: pool of request frames
 * @request_dma:
 * @request_dma_sz:
 * @scsi_lookup: firmware request tracker list
 * @scsi_lookup_lock:
 * @मुक्त_list: मुक्त list of request
 * @pending_io_count:
 * @reset_wq:
 * @chain: pool of chains
 * @chain_dma:
 * @max_sges_in_मुख्य_message: number sg elements in मुख्य message
 * @max_sges_in_chain_message: number sg elements per chain
 * @chains_needed_per_io: max chains per io
 * @chain_depth: total chains allocated
 * @chain_segment_sz: gives the max number of
 *			SGEs accommodate on single chain buffer
 * @hi_priority_smid:
 * @hi_priority:
 * @hi_priority_dma:
 * @hi_priority_depth:
 * @hpr_lookup:
 * @hpr_मुक्त_list:
 * @पूर्णांकernal_smid:
 * @पूर्णांकernal:
 * @पूर्णांकernal_dma:
 * @पूर्णांकernal_depth:
 * @पूर्णांकernal_lookup:
 * @पूर्णांकernal_मुक्त_list:
 * @sense: pool of sense
 * @sense_dma:
 * @sense_dma_pool:
 * @reply_depth: hba reply queue depth:
 * @reply_sz: per reply frame size:
 * @reply: pool of replys:
 * @reply_dma:
 * @reply_dma_pool:
 * @reply_मुक्त_queue_depth: reply मुक्त depth
 * @reply_मुक्त: pool क्रम reply मुक्त queue (32 bit addr)
 * @reply_मुक्त_dma:
 * @reply_मुक्त_dma_pool:
 * @reply_मुक्त_host_index: tail index in pool to insert मुक्त replys
 * @reply_post_queue_depth: reply post queue depth
 * @reply_post_काष्ठा: काष्ठा क्रम reply_post_मुक्त physical & virt address
 * @rdpq_array_capable: FW supports multiple reply queue addresses in ioc_init
 * @rdpq_array_enable: rdpq_array support is enabled in the driver
 * @rdpq_array_enable_asचिन्हित: this ensures that rdpq_array_enable flag
 *				is asचिन्हित only ones
 * @reply_queue_count: number of reply queue's
 * @reply_queue_list: link list contaning the reply queue info
 * @msix96_vector: 96 MSI-X vector support
 * @replyPostRegisterIndex: index of next position in Reply Desc Post Queue
 * @delayed_tr_list: target reset link list
 * @delayed_tr_volume_list: volume target reset link list
 * @delayed_sc_list:
 * @delayed_event_ack_list:
 * @temp_sensors_count: flag to carry the number of temperature sensors
 * @pci_access_mutex: Mutex to synchronize ioctl,sysfs show path and
 *	pci resource handling. PCI resource मुक्तing will lead to मुक्त
 *	vital hardware/memory resource, which might be in use by cli/sysfs
 *	path functions resulting in Null poपूर्णांकer reference followed by kernel
 *	crash. To aव्योम the above race condition we use mutex syncrhonization
 *	which ensures the syncrhonization between cli/sysfs_show path.
 * @atomic_desc_capable: Atomic Request Descriptor support.
 * @GET_MSIX_INDEX: Get the msix index of high iops queues.
 * @multipath_on_hba: flag to determine multipath on hba is enabled or not
 * @port_table_list: list containing HBA's wide/narrow port's info
 */
काष्ठा MPT3SAS_ADAPTER अणु
	काष्ठा list_head list;
	काष्ठा Scsi_Host *shost;
	u8		id;
	पूर्णांक		cpu_count;
	अक्षर		name[MPT_NAME_LENGTH];
	अक्षर		driver_name[MPT_NAME_LENGTH - 8];
	अक्षर		पंचांगp_string[MPT_STRING_LENGTH];
	काष्ठा pci_dev	*pdev;
	Mpi2SystemInterfaceRegs_t __iomem *chip;
	phys_addr_t	chip_phys;
	पूर्णांक		logging_level;
	पूर्णांक		fwfault_debug;
	u8		ir_firmware;
	पूर्णांक		bars;
	u8		mask_पूर्णांकerrupts;

	/* fw fault handler */
	अक्षर		fault_reset_work_q_name[20];
	काष्ठा workqueue_काष्ठा *fault_reset_work_q;
	काष्ठा delayed_work fault_reset_work;

	/* fw event handler */
	अक्षर		firmware_event_name[20];
	काष्ठा workqueue_काष्ठा	*firmware_event_thपढ़ो;
	spinlock_t	fw_event_lock;
	काष्ठा list_head fw_event_list;
	काष्ठा fw_event_work	*current_event;
	u8		fw_events_cleanup;

	 /* misc flags */
	पूर्णांक		aen_event_पढ़ो_flag;
	u8		broadcast_aen_busy;
	u16		broadcast_aen_pending;
	u8		shost_recovery;
	u8		got_task_पात_from_ioctl;

	काष्ठा mutex	reset_in_progress_mutex;
	spinlock_t	ioc_reset_in_progress_lock;
	u8		ioc_link_reset_in_progress;

	u8		ignore_loginfos;
	u8		हटाओ_host;
	u8		pci_error_recovery;
	u8		रुको_क्रम_discovery_to_complete;
	u8		is_driver_loading;
	u8		port_enable_failed;
	u8		start_scan;
	u16		start_scan_failed;

	u8		msix_enable;
	u16		msix_vector_count;
	u8		*cpu_msix_table;
	u16		cpu_msix_table_sz;
	resource_माप_प्रकार __iomem **reply_post_host_index;
	u32		ioc_reset_count;
	MPT3SAS_FLUSH_RUNNING_CMDS schedule_dead_ioc_flush_running_cmds;
	u32             non_operational_loop;
	u8              ioc_coredump_loop;
	u32		बारtamp_update_count;
	u32		समय_sync_पूर्णांकerval;
	atomic64_t      total_io_cnt;
	atomic64_t	high_iops_outstanding;
	bool            msix_load_balance;
	u16		thresh_hold;
	u8		high_iops_queues;
	u32		drv_support_biपंचांगap;
	u32             dma_mask;
	bool		enable_sdev_max_qd;
	bool		use_32bit_dma;

	/* पूर्णांकernal commands, callback index */
	u8		scsi_io_cb_idx;
	u8		पंचांग_cb_idx;
	u8		transport_cb_idx;
	u8		scsih_cb_idx;
	u8		ctl_cb_idx;
	u8		base_cb_idx;
	u8		port_enable_cb_idx;
	u8		config_cb_idx;
	u8		पंचांग_tr_cb_idx;
	u8		पंचांग_tr_volume_cb_idx;
	u8		पंचांग_sas_control_cb_idx;
	काष्ठा _पूर्णांकernal_cmd base_cmds;
	काष्ठा _पूर्णांकernal_cmd port_enable_cmds;
	काष्ठा _पूर्णांकernal_cmd transport_cmds;
	काष्ठा _पूर्णांकernal_cmd scsih_cmds;
	काष्ठा _पूर्णांकernal_cmd पंचांग_cmds;
	काष्ठा _पूर्णांकernal_cmd ctl_cmds;
	काष्ठा _पूर्णांकernal_cmd config_cmds;

	MPT_ADD_SGE	base_add_sg_single;

	/* function ptr क्रम either IEEE or MPI sg elements */
	MPT_BUILD_SG_SCMD build_sg_scmd;
	MPT_BUILD_SG    build_sg;
	MPT_BUILD_ZERO_LEN_SGE build_zero_len_sge;
	u16             sge_size_ieee;
	u16		hba_mpi_version_beदीर्घed;

	/* function ptr क्रम MPI sg elements only */
	MPT_BUILD_SG    build_sg_mpi;
	MPT_BUILD_ZERO_LEN_SGE build_zero_len_sge_mpi;

	/* function ptr क्रम NVMe PRP elements only */
	NVME_BUILD_PRP  build_nvme_prp;

	/* event log */
	u32		event_type[MPI2_EVENT_NOTIFY_EVENTMASK_WORDS];
	u32		event_context;
	व्योम		*event_log;
	u32		event_masks[MPI2_EVENT_NOTIFY_EVENTMASK_WORDS];

	u8		पंचांग_custom_handling;
	u8		nvme_पात_समयout;
	u16		max_shutकरोwn_latency;

	/* अटल config pages */
	काष्ठा mpt3sas_facts facts;
	काष्ठा mpt3sas_facts prev_fw_facts;
	काष्ठा mpt3sas_port_facts *pfacts;
	Mpi2ManufacturingPage0_t manu_pg0;
	काष्ठा Mpi2ManufacturingPage10_t manu_pg10;
	काष्ठा Mpi2ManufacturingPage11_t manu_pg11;
	Mpi2BiosPage2_t	bios_pg2;
	Mpi2BiosPage3_t	bios_pg3;
	Mpi2IOCPage8_t ioc_pg8;
	Mpi2IOUnitPage0_t iounit_pg0;
	Mpi2IOUnitPage1_t iounit_pg1;
	Mpi2IOUnitPage8_t iounit_pg8;
	Mpi2IOCPage1_t	ioc_pg1_copy;

	काष्ठा _boot_device req_boot_device;
	काष्ठा _boot_device req_alt_boot_device;
	काष्ठा _boot_device current_boot_device;

	/* sas hba, expander, and device list */
	काष्ठा _sas_node sas_hba;
	काष्ठा list_head sas_expander_list;
	काष्ठा list_head enclosure_list;
	spinlock_t	sas_node_lock;
	काष्ठा list_head sas_device_list;
	काष्ठा list_head sas_device_init_list;
	spinlock_t	sas_device_lock;
	काष्ठा list_head pcie_device_list;
	काष्ठा list_head pcie_device_init_list;
	spinlock_t      pcie_device_lock;

	काष्ठा list_head raid_device_list;
	spinlock_t	raid_device_lock;
	u8		io_missing_delay;
	u16		device_missing_delay;
	पूर्णांक		sas_id;
	पूर्णांक		pcie_target_id;

	व्योम		*blocking_handles;
	व्योम		*pd_handles;
	u16		pd_handles_sz;

	व्योम		*pend_os_device_add;
	u16		pend_os_device_add_sz;

	/* config page */
	u16		config_page_sz;
	व्योम		*config_page;
	dma_addr_t	config_page_dma;
	व्योम		*config_vaddr;

	/* scsiio request */
	u16		hba_queue_depth;
	u16		sge_size;
	u16		scsiio_depth;
	u16		request_sz;
	u8		*request;
	dma_addr_t	request_dma;
	u32		request_dma_sz;
	काष्ठा pcie_sg_list *pcie_sg_lookup;
	spinlock_t	scsi_lookup_lock;
	पूर्णांक		pending_io_count;
	रुको_queue_head_t reset_wq;
	u16		*io_queue_num;

	/* PCIe SGL */
	काष्ठा dma_pool *pcie_sgl_dma_pool;
	/* Host Page Size */
	u32		page_size;

	/* chain */
	काष्ठा chain_lookup *chain_lookup;
	काष्ठा list_head मुक्त_chain_list;
	काष्ठा dma_pool *chain_dma_pool;
	uदीर्घ		chain_pages;
	u16		max_sges_in_मुख्य_message;
	u16		max_sges_in_chain_message;
	u16		chains_needed_per_io;
	u32		chain_depth;
	u16		chain_segment_sz;
	u16		chains_per_prp_buffer;

	/* hi-priority queue */
	u16		hi_priority_smid;
	u8		*hi_priority;
	dma_addr_t	hi_priority_dma;
	u16		hi_priority_depth;
	काष्ठा request_tracker *hpr_lookup;
	काष्ठा list_head hpr_मुक्त_list;

	/* पूर्णांकernal queue */
	u16		पूर्णांकernal_smid;
	u8		*पूर्णांकernal;
	dma_addr_t	पूर्णांकernal_dma;
	u16		पूर्णांकernal_depth;
	काष्ठा request_tracker *पूर्णांकernal_lookup;
	काष्ठा list_head पूर्णांकernal_मुक्त_list;

	/* sense */
	u8		*sense;
	dma_addr_t	sense_dma;
	काष्ठा dma_pool *sense_dma_pool;

	/* reply */
	u16		reply_sz;
	u8		*reply;
	dma_addr_t	reply_dma;
	u32		reply_dma_max_address;
	u32		reply_dma_min_address;
	काष्ठा dma_pool *reply_dma_pool;

	/* reply मुक्त queue */
	u16		reply_मुक्त_queue_depth;
	__le32		*reply_मुक्त;
	dma_addr_t	reply_मुक्त_dma;
	काष्ठा dma_pool *reply_मुक्त_dma_pool;
	u32		reply_मुक्त_host_index;

	/* reply post queue */
	u16		reply_post_queue_depth;
	काष्ठा reply_post_काष्ठा *reply_post;
	u8		rdpq_array_capable;
	u8		rdpq_array_enable;
	u8		rdpq_array_enable_asचिन्हित;
	काष्ठा dma_pool *reply_post_मुक्त_dma_pool;
	काष्ठा dma_pool *reply_post_मुक्त_array_dma_pool;
	Mpi2IOCInitRDPQArrayEntry *reply_post_मुक्त_array;
	dma_addr_t reply_post_मुक्त_array_dma;
	u8		reply_queue_count;
	काष्ठा list_head reply_queue_list;

	u8		combined_reply_queue;
	u8		combined_reply_index_count;
	u8		smp_affinity_enable;
	/* reply post रेजिस्टर index */
	resource_माप_प्रकार	**replyPostRegisterIndex;

	काष्ठा list_head delayed_tr_list;
	काष्ठा list_head delayed_tr_volume_list;
	काष्ठा list_head delayed_sc_list;
	काष्ठा list_head delayed_event_ack_list;
	u8		temp_sensors_count;
	काष्ठा mutex pci_access_mutex;

	/* diag buffer support */
	u8		*diag_buffer[MPI2_DIAG_BUF_TYPE_COUNT];
	u32		diag_buffer_sz[MPI2_DIAG_BUF_TYPE_COUNT];
	dma_addr_t	diag_buffer_dma[MPI2_DIAG_BUF_TYPE_COUNT];
	u8		diag_buffer_status[MPI2_DIAG_BUF_TYPE_COUNT];
	u32		unique_id[MPI2_DIAG_BUF_TYPE_COUNT];
	u32		product_specअगरic[MPI2_DIAG_BUF_TYPE_COUNT][23];
	u32		diagnostic_flags[MPI2_DIAG_BUF_TYPE_COUNT];
	u32		ring_buffer_offset;
	u32		ring_buffer_sz;
	काष्ठा htb_rel_query htb_rel;
	u8 reset_from_user;
	u8		is_warpdrive;
	u8		is_mcpu_endpoपूर्णांक;
	u8		hide_ir_msg;
	u8		mfg_pg10_hide_flag;
	u8		hide_drives;
	spinlock_t	diag_trigger_lock;
	u8		diag_trigger_active;
	u8		atomic_desc_capable;
	BASE_READ_REG	base_पढ़ोl;
	काष्ठा SL_WH_MASTER_TRIGGER_T diag_trigger_master;
	काष्ठा SL_WH_EVENT_TRIGGERS_T diag_trigger_event;
	काष्ठा SL_WH_SCSI_TRIGGERS_T diag_trigger_scsi;
	काष्ठा SL_WH_MPI_TRIGGERS_T diag_trigger_mpi;
	u8		supports_trigger_pages;
	व्योम		*device_हटाओ_in_progress;
	u16		device_हटाओ_in_progress_sz;
	u8		is_gen35_ioc;
	u8		is_aero_ioc;
	काष्ठा dentry	*debugfs_root;
	काष्ठा dentry	*ioc_dump;
	PUT_SMID_IO_FP_HIP put_smid_scsi_io;
	PUT_SMID_IO_FP_HIP put_smid_fast_path;
	PUT_SMID_IO_FP_HIP put_smid_hi_priority;
	PUT_SMID_DEFAULT put_smid_शेष;
	GET_MSIX_INDEX get_msix_index_क्रम_smlio;

	u8		multipath_on_hba;
	काष्ठा list_head port_table_list;
पूर्ण;

काष्ठा mpt3sas_debugfs_buffer अणु
	व्योम	*buf;
	u32	len;
पूर्ण;

#घोषणा MPT_DRV_SUPPORT_BITMAP_MEMMOVE 0x00000001
#घोषणा MPT_DRV_SUPPORT_BITMAP_ADDNLQUERY	0x00000002

प्रकार u8 (*MPT_CALLBACK)(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply);


/* base shared API */
बाह्य काष्ठा list_head mpt3sas_ioc_list;
बाह्य अक्षर    driver_name[MPT_NAME_LENGTH];
/* spinlock on list operations over IOCs
 * Case: when multiple warpdrive cards(IOCs) are in use
 * Each IOC will added to the ioc list काष्ठाure on initialization.
 * Watchकरोg thपढ़ोs run at regular पूर्णांकervals to check IOC क्रम any
 * fault conditions which will trigger the dead_ioc thपढ़ो to
 * deallocate pci resource, resulting deleting the IOC netry from list,
 * this deletion need to रक्षित by spinlock to enusre that
 * ioc removal is syncrhonized, अगर not synchronized it might lead to
 * list_del corruption as the ioc list is traversed in cli path.
 */
बाह्य spinlock_t gioc_lock;

व्योम mpt3sas_base_start_watchकरोg(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_base_stop_watchकरोg(काष्ठा MPT3SAS_ADAPTER *ioc);

पूर्णांक mpt3sas_base_attach(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_base_detach(काष्ठा MPT3SAS_ADAPTER *ioc);
पूर्णांक mpt3sas_base_map_resources(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_base_मुक्त_resources(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_मुक्त_enclosure_list(काष्ठा MPT3SAS_ADAPTER *ioc);
पूर्णांक mpt3sas_base_hard_reset_handler(काष्ठा MPT3SAS_ADAPTER *ioc,
	क्रमागत reset_type type);

व्योम *mpt3sas_base_get_msg_frame(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);
व्योम *mpt3sas_base_get_sense_buffer(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);
__le32 mpt3sas_base_get_sense_buffer_dma(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 smid);
व्योम *mpt3sas_base_get_pcie_sgl(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);
dma_addr_t mpt3sas_base_get_pcie_sgl_dma(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);
व्योम mpt3sas_base_sync_reply_irqs(काष्ठा MPT3SAS_ADAPTER *ioc, u8 poll);
व्योम mpt3sas_base_mask_पूर्णांकerrupts(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_base_unmask_पूर्णांकerrupts(काष्ठा MPT3SAS_ADAPTER *ioc);

व्योम mpt3sas_base_put_smid_fast_path(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u16 handle);
व्योम mpt3sas_base_put_smid_hi_priority(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u16 msix_task);
व्योम mpt3sas_base_put_smid_nvme_encap(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);
व्योम mpt3sas_base_put_smid_शेष(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);
/* hi-priority queue */
u16 mpt3sas_base_get_smid_hpr(काष्ठा MPT3SAS_ADAPTER *ioc, u8 cb_idx);
u16 mpt3sas_base_get_smid_scsiio(काष्ठा MPT3SAS_ADAPTER *ioc, u8 cb_idx,
		काष्ठा scsi_cmnd *scmd);
व्योम mpt3sas_base_clear_st(काष्ठा MPT3SAS_ADAPTER *ioc,
		काष्ठा scsiio_tracker *st);

u16 mpt3sas_base_get_smid(काष्ठा MPT3SAS_ADAPTER *ioc, u8 cb_idx);
व्योम mpt3sas_base_मुक्त_smid(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);
व्योम mpt3sas_base_initialize_callback_handler(व्योम);
u8 mpt3sas_base_रेजिस्टर_callback_handler(MPT_CALLBACK cb_func);
व्योम mpt3sas_base_release_callback_handler(u8 cb_idx);

u8 mpt3sas_base_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply);
u8 mpt3sas_port_enable_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u8 msix_index, u32 reply);
व्योम *mpt3sas_base_get_reply_virt_addr(काष्ठा MPT3SAS_ADAPTER *ioc,
	u32 phys_addr);

u32 mpt3sas_base_get_iocstate(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक cooked);

व्योम mpt3sas_base_fault_info(काष्ठा MPT3SAS_ADAPTER *ioc , u16 fault_code);
#घोषणा mpt3sas_prपूर्णांक_fault_code(ioc, fault_code) \
करो अणु pr_err("%s fault info from func: %s\n", ioc->name, __func__); \
	mpt3sas_base_fault_info(ioc, fault_code); पूर्ण जबतक (0)

व्योम mpt3sas_base_coredump_info(काष्ठा MPT3SAS_ADAPTER *ioc, u16 fault_code);
#घोषणा mpt3sas_prपूर्णांक_coredump_info(ioc, fault_code) \
करो अणु pr_err("%s fault info from func: %s\n", ioc->name, __func__); \
	mpt3sas_base_coredump_info(ioc, fault_code); पूर्ण जबतक (0)

पूर्णांक mpt3sas_base_रुको_क्रम_coredump_completion(काष्ठा MPT3SAS_ADAPTER *ioc,
		स्थिर अक्षर *caller);
पूर्णांक mpt3sas_base_sas_iounit_control(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2SasIoUnitControlReply_t *mpi_reply,
	Mpi2SasIoUnitControlRequest_t *mpi_request);
पूर्णांक mpt3sas_base_scsi_enclosure_processor(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2SepReply_t *mpi_reply, Mpi2SepRequest_t *mpi_request);

व्योम mpt3sas_base_validate_event_type(काष्ठा MPT3SAS_ADAPTER *ioc,
	u32 *event_type);

व्योम mpt3sas_halt_firmware(काष्ठा MPT3SAS_ADAPTER *ioc);

व्योम mpt3sas_base_update_missing_delay(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 device_missing_delay, u8 io_missing_delay);

पूर्णांक mpt3sas_port_enable(काष्ठा MPT3SAS_ADAPTER *ioc);

व्योम
mpt3sas_रुको_क्रम_commands_to_complete(काष्ठा MPT3SAS_ADAPTER *ioc);

u8 mpt3sas_base_check_cmd_समयout(काष्ठा MPT3SAS_ADAPTER *ioc,
	u8 status, व्योम *mpi_request, पूर्णांक sz);
#घोषणा mpt3sas_check_cmd_समयout(ioc, status, mpi_request, sz, issue_reset) \
करो अणु	ioc_err(ioc, "In func: %s\n", __func__); \
	issue_reset = mpt3sas_base_check_cmd_समयout(ioc, \
	status, mpi_request, sz); पूर्ण जबतक (0)

पूर्णांक mpt3sas_रुको_क्रम_ioc(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक रुको_count);

/* scsih shared API */
काष्ठा scsi_cmnd *mpt3sas_scsih_scsi_lookup_get(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 smid);
u8 mpt3sas_scsih_event_callback(काष्ठा MPT3SAS_ADAPTER *ioc, u8 msix_index,
	u32 reply);
व्योम mpt3sas_scsih_pre_reset_handler(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_scsih_clear_outstanding_scsi_पंचांग_commands(
	काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_scsih_reset_करोne_handler(काष्ठा MPT3SAS_ADAPTER *ioc);

पूर्णांक mpt3sas_scsih_issue_पंचांग(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	uपूर्णांक channel, uपूर्णांक id, u64 lun, u8 type, u16 smid_task,
	u16 msix_task, u8 समयout, u8 tr_method);
पूर्णांक mpt3sas_scsih_issue_locked_पंचांग(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	uपूर्णांक channel, uपूर्णांक id, u64 lun, u8 type, u16 smid_task,
	u16 msix_task, u8 समयout, u8 tr_method);

व्योम mpt3sas_scsih_set_पंचांग_flag(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle);
व्योम mpt3sas_scsih_clear_पंचांग_flag(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle);
व्योम mpt3sas_expander_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc, u64 sas_address,
	काष्ठा hba_port *port);
व्योम mpt3sas_device_हटाओ_by_sas_address(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, काष्ठा hba_port *port);
u8 mpt3sas_check_क्रम_pending_पूर्णांकernal_cmds(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 smid);
काष्ठा hba_port *
mpt3sas_get_port_by_id(काष्ठा MPT3SAS_ADAPTER *ioc, u8 port,
	u8 bypass_dirty_port_flag);

काष्ठा _sas_node *mpt3sas_scsih_expander_find_by_handle(
	काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle);
काष्ठा _sas_node *mpt3sas_scsih_expander_find_by_sas_address(
	काष्ठा MPT3SAS_ADAPTER *ioc, u64 sas_address,
	काष्ठा hba_port *port);
काष्ठा _sas_device *mpt3sas_get_sdev_by_addr(
	 काष्ठा MPT3SAS_ADAPTER *ioc, u64 sas_address,
	 काष्ठा hba_port *port);
काष्ठा _sas_device *__mpt3sas_get_sdev_by_addr(
	 काष्ठा MPT3SAS_ADAPTER *ioc, u64 sas_address,
	 काष्ठा hba_port *port);
काष्ठा _sas_device *mpt3sas_get_sdev_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 handle);
काष्ठा _pcie_device *mpt3sas_get_pdev_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 handle);

व्योम mpt3sas_port_enable_complete(काष्ठा MPT3SAS_ADAPTER *ioc);
काष्ठा _raid_device *
mpt3sas_raid_device_find_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle);
व्योम mpt3sas_scsih_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth);
काष्ठा _sas_device *
__mpt3sas_get_sdev_by_rphy(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा sas_rphy *rphy);
काष्ठा भव_phy *
mpt3sas_get_vphy_by_phy(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा hba_port *port, u32 phy);

/* config shared API */
u8 mpt3sas_config_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply);
पूर्णांक mpt3sas_config_get_number_hba_phys(काष्ठा MPT3SAS_ADAPTER *ioc,
	u8 *num_phys);
पूर्णांक mpt3sas_config_get_manufacturing_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2ManufacturingPage0_t *config_page);
पूर्णांक mpt3sas_config_get_manufacturing_pg7(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2ManufacturingPage7_t *config_page,
	u16 sz);
पूर्णांक mpt3sas_config_get_manufacturing_pg10(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply,
	काष्ठा Mpi2ManufacturingPage10_t *config_page);

पूर्णांक mpt3sas_config_get_manufacturing_pg11(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply,
	काष्ठा Mpi2ManufacturingPage11_t  *config_page);
पूर्णांक mpt3sas_config_set_manufacturing_pg11(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply,
	काष्ठा Mpi2ManufacturingPage11_t *config_page);

पूर्णांक mpt3sas_config_get_bios_pg2(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2BiosPage2_t *config_page);
पूर्णांक mpt3sas_config_get_bios_pg3(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2BiosPage3_t *config_page);
पूर्णांक mpt3sas_config_get_iounit_pg0(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2IOUnitPage0_t *config_page);
पूर्णांक mpt3sas_config_get_sas_device_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasDevicePage0_t *config_page,
	u32 क्रमm, u32 handle);
पूर्णांक mpt3sas_config_get_sas_device_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasDevicePage1_t *config_page,
	u32 क्रमm, u32 handle);
पूर्णांक mpt3sas_config_get_pcie_device_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26PCIeDevicePage0_t *config_page,
	u32 क्रमm, u32 handle);
पूर्णांक mpt3sas_config_get_pcie_device_pg2(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26PCIeDevicePage2_t *config_page,
	u32 क्रमm, u32 handle);
पूर्णांक mpt3sas_config_get_sas_iounit_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasIOUnitPage0_t *config_page,
	u16 sz);
पूर्णांक mpt3sas_config_get_iounit_pg1(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2IOUnitPage1_t *config_page);
पूर्णांक mpt3sas_config_get_iounit_pg3(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2IOUnitPage3_t *config_page, u16 sz);
पूर्णांक mpt3sas_config_set_iounit_pg1(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2IOUnitPage1_t *config_page);
पूर्णांक mpt3sas_config_get_iounit_pg8(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2IOUnitPage8_t *config_page);
पूर्णांक mpt3sas_config_get_sas_iounit_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasIOUnitPage1_t *config_page,
	u16 sz);
पूर्णांक mpt3sas_config_set_sas_iounit_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasIOUnitPage1_t *config_page,
	u16 sz);
पूर्णांक mpt3sas_config_get_ioc_pg1(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2IOCPage1_t *config_page);
पूर्णांक mpt3sas_config_set_ioc_pg1(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2IOCPage1_t *config_page);
पूर्णांक mpt3sas_config_get_ioc_pg8(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2IOCPage8_t *config_page);
पूर्णांक mpt3sas_config_get_expander_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2ExpanderPage0_t *config_page,
	u32 क्रमm, u32 handle);
पूर्णांक mpt3sas_config_get_expander_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2ExpanderPage1_t *config_page,
	u32 phy_number, u16 handle);
पूर्णांक mpt3sas_config_get_enclosure_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2SasEnclosurePage0_t *config_page,
	u32 क्रमm, u32 handle);
पूर्णांक mpt3sas_config_get_phy_pg0(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2SasPhyPage0_t *config_page, u32 phy_number);
पूर्णांक mpt3sas_config_get_phy_pg1(काष्ठा MPT3SAS_ADAPTER *ioc, Mpi2ConfigReply_t
	*mpi_reply, Mpi2SasPhyPage1_t *config_page, u32 phy_number);
पूर्णांक mpt3sas_config_get_raid_volume_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2RaidVolPage1_t *config_page, u32 क्रमm,
	u32 handle);
पूर्णांक mpt3sas_config_get_number_pds(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	u8 *num_pds);
पूर्णांक mpt3sas_config_get_raid_volume_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2RaidVolPage0_t *config_page, u32 क्रमm,
	u32 handle, u16 sz);
पूर्णांक mpt3sas_config_get_phys_disk_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi2RaidPhysDiskPage0_t *config_page,
	u32 क्रमm, u32 क्रमm_specअगरic);
पूर्णांक mpt3sas_config_get_volume_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 pd_handle,
	u16 *volume_handle);
पूर्णांक mpt3sas_config_get_volume_wwid(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 volume_handle, u64 *wwid);
पूर्णांक
mpt3sas_config_get_driver_trigger_pg0(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage0_t *config_page);
पूर्णांक
mpt3sas_config_get_driver_trigger_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage1_t *config_page);
पूर्णांक
mpt3sas_config_get_driver_trigger_pg2(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage2_t *config_page);
पूर्णांक
mpt3sas_config_get_driver_trigger_pg3(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage3_t *config_page);
पूर्णांक
mpt3sas_config_get_driver_trigger_pg4(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26DriverTriggerPage4_t *config_page);
पूर्णांक
mpt3sas_config_update_driver_trigger_pg1(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_MASTER_TRIGGER_T *master_tg, bool set);
पूर्णांक
mpt3sas_config_update_driver_trigger_pg2(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_EVENT_TRIGGERS_T *event_tg, bool set);
पूर्णांक
mpt3sas_config_update_driver_trigger_pg3(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_SCSI_TRIGGERS_T *scsi_tg, bool set);
पूर्णांक
mpt3sas_config_update_driver_trigger_pg4(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_MPI_TRIGGERS_T *mpi_tg, bool set);

/* ctl shared API */
बाह्य काष्ठा device_attribute *mpt3sas_host_attrs[];
बाह्य काष्ठा device_attribute *mpt3sas_dev_attrs[];
व्योम mpt3sas_ctl_init(uलघु hbas_to_क्रमागतerate);
व्योम mpt3sas_ctl_निकास(uलघु hbas_to_क्रमागतerate);
u8 mpt3sas_ctl_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply);
व्योम mpt3sas_ctl_pre_reset_handler(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_ctl_clear_outstanding_ioctls(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_ctl_reset_करोne_handler(काष्ठा MPT3SAS_ADAPTER *ioc);
u8 mpt3sas_ctl_event_callback(काष्ठा MPT3SAS_ADAPTER *ioc,
	u8 msix_index, u32 reply);
व्योम mpt3sas_ctl_add_to_event_log(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventNotअगरicationReply_t *mpi_reply);

व्योम mpt3sas_enable_diag_buffer(काष्ठा MPT3SAS_ADAPTER *ioc,
	u8 bits_to_रेजिस्टर);
पूर्णांक mpt3sas_send_diag_release(काष्ठा MPT3SAS_ADAPTER *ioc, u8 buffer_type,
	u8 *issue_reset);

/* transport shared API */
बाह्य काष्ठा scsi_transport_ढाँचा *mpt3sas_transport_ढाँचा;
u8 mpt3sas_transport_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply);
काष्ठा _sas_port *mpt3sas_transport_port_add(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 handle, u64 sas_address, काष्ठा hba_port *port);
व्योम mpt3sas_transport_port_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc, u64 sas_address,
	u64 sas_address_parent, काष्ठा hba_port *port);
पूर्णांक mpt3sas_transport_add_host_phy(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा _sas_phy
	*mpt3sas_phy, Mpi2SasPhyPage0_t phy_pg0, काष्ठा device *parent_dev);
पूर्णांक mpt3sas_transport_add_expander_phy(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_phy *mpt3sas_phy, Mpi2ExpanderPage1_t expander_pg1,
	काष्ठा device *parent_dev);
व्योम mpt3sas_transport_update_links(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, u16 handle, u8 phy_number, u8 link_rate,
	काष्ठा hba_port *port);
बाह्य काष्ठा sas_function_ढाँचा mpt3sas_transport_functions;
बाह्य काष्ठा scsi_transport_ढाँचा *mpt3sas_transport_ढाँचा;
व्योम
mpt3sas_transport_del_phy_from_an_existing_port(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_node, काष्ठा _sas_phy *mpt3sas_phy);
व्योम
mpt3sas_transport_add_phy_to_an_existing_port(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_node, काष्ठा _sas_phy *mpt3sas_phy,
	u64 sas_address, काष्ठा hba_port *port);
/* trigger data बाह्यs */
व्योम mpt3sas_send_trigger_data_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T *event_data);
व्योम mpt3sas_process_trigger_data(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T *event_data);
व्योम mpt3sas_trigger_master(काष्ठा MPT3SAS_ADAPTER *ioc,
	u32 trigger_biपंचांगask);
व्योम mpt3sas_trigger_event(काष्ठा MPT3SAS_ADAPTER *ioc, u16 event,
	u16 log_entry_qualअगरier);
व्योम mpt3sas_trigger_scsi(काष्ठा MPT3SAS_ADAPTER *ioc, u8 sense_key,
	u8 asc, u8 ascq);
व्योम mpt3sas_trigger_mpi(काष्ठा MPT3SAS_ADAPTER *ioc, u16 ioc_status,
	u32 loginfo);

/* warpdrive APIs */
u8 mpt3sas_get_num_volumes(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_init_warpdrive_properties(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _raid_device *raid_device);
व्योम
mpt3sas_setup_direct_io(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा scsi_cmnd *scmd,
	काष्ठा _raid_device *raid_device, Mpi25SCSIIORequest_t *mpi_request);

/* NCQ Prio Handling Check */
bool scsih_ncq_prio_supp(काष्ठा scsi_device *sdev);

व्योम mpt3sas_setup_debugfs(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_destroy_debugfs(काष्ठा MPT3SAS_ADAPTER *ioc);
व्योम mpt3sas_init_debugfs(व्योम);
व्योम mpt3sas_निकास_debugfs(व्योम);

/**
 * _scsih_is_pcie_scsi_device - determines अगर device is an pcie scsi device
 * @device_info: bitfield providing inक्रमmation about the device.
 * Context: none
 *
 * Returns 1 अगर scsi device.
 */
अटल अंतरभूत पूर्णांक
mpt3sas_scsih_is_pcie_scsi_device(u32 device_info)
अणु
	अगर ((device_info &
	    MPI26_PCIE_DEVINFO_MASK_DEVICE_TYPE) == MPI26_PCIE_DEVINFO_SCSI)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण
#पूर्ण_अगर /* MPT3SAS_BASE_H_INCLUDED */
