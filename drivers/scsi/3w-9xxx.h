<शैली गुरु>
/*
   3w-9xxx.h -- 3ware 9000 Storage Controller device driver क्रम Linux.

   Written By: Adam Radक्रमd <aradक्रमd@gmail.com>
   Modअगरications By: Tom Couch

   Copyright (C) 2004-2009 Applied Micro Circuits Corporation.
   Copyright (C) 2010 LSI Corporation.

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   NO WARRANTY
   THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
   LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
   solely responsible क्रम determining the appropriateness of using and
   distributing the Program and assumes all risks associated with its
   exercise of rights under this Agreement, including but not limited to
   the risks and costs of program errors, damage to or loss of data,
   programs or equipment, and unavailability or पूर्णांकerruption of operations.

   DISCLAIMER OF LIABILITY
   NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
   सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
   USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
   HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

   Bugs/Comments/Suggestions should be mailed to:
   aradक्रमd@gmail.com
*/

#अगर_अघोषित _3W_9XXX_H
#घोषणा _3W_9XXX_H

/* AEN string type */
प्रकार काष्ठा TAG_twa_message_type अणु
	अचिन्हित पूर्णांक   code;
	अक्षर*	       text;
पूर्ण twa_message_type;

/* AEN strings */
अटल twa_message_type twa_aen_table[] = अणु
	अणु0x0000, "AEN queue empty"पूर्ण,
	अणु0x0001, "Controller reset occurred"पूर्ण,
	अणु0x0002, "Degraded unit detected"पूर्ण,
	अणु0x0003, "Controller error occurred"पूर्ण,
	अणु0x0004, "Background rebuild failed"पूर्ण,
	अणु0x0005, "Background rebuild done"पूर्ण,
	अणु0x0006, "Incomplete unit detected"पूर्ण,
	अणु0x0007, "Background initialize done"पूर्ण,
	अणु0x0008, "Unclean shutdown detected"पूर्ण,
	अणु0x0009, "Drive timeout detected"पूर्ण,
	अणु0x000A, "Drive error detected"पूर्ण,
	अणु0x000B, "Rebuild started"पूर्ण,
	अणु0x000C, "Background initialize started"पूर्ण,
	अणु0x000D, "Entire logical unit was deleted"पूर्ण,
	अणु0x000E, "Background initialize failed"पूर्ण,
	अणु0x000F, "SMART attribute exceeded threshold"पूर्ण,
	अणु0x0010, "Power supply reported AC under range"पूर्ण,
	अणु0x0011, "Power supply reported DC out of range"पूर्ण,
	अणु0x0012, "Power supply reported a malfunction"पूर्ण,
	अणु0x0013, "Power supply predicted malfunction"पूर्ण,
	अणु0x0014, "Battery charge is below threshold"पूर्ण,
	अणु0x0015, "Fan speed is below threshold"पूर्ण,
	अणु0x0016, "Temperature sensor is above threshold"पूर्ण,
	अणु0x0017, "Power supply was removed"पूर्ण,
	अणु0x0018, "Power supply was inserted"पूर्ण,
	अणु0x0019, "Drive was removed from a bay"पूर्ण,
	अणु0x001A, "Drive was inserted into a bay"पूर्ण,
	अणु0x001B, "Drive bay cover door was opened"पूर्ण,
	अणु0x001C, "Drive bay cover door was closed"पूर्ण,
	अणु0x001D, "Product case was opened"पूर्ण,
	अणु0x0020, "Prepare for shutdown (power-off)"पूर्ण,
	अणु0x0021, "Downgrade UDMA mode to lower speed"पूर्ण,
	अणु0x0022, "Upgrade UDMA mode to higher speed"पूर्ण,
	अणु0x0023, "Sector repair completed"पूर्ण,
	अणु0x0024, "Sbuf memory test failed"पूर्ण,
	अणु0x0025, "Error flushing cached write data to array"पूर्ण,
	अणु0x0026, "Drive reported data ECC error"पूर्ण,
	अणु0x0027, "DCB has checksum error"पूर्ण,
	अणु0x0028, "DCB version is unsupported"पूर्ण,
	अणु0x0029, "Background verify started"पूर्ण,
	अणु0x002A, "Background verify failed"पूर्ण,
	अणु0x002B, "Background verify done"पूर्ण,
	अणु0x002C, "Bad sector overwritten during rebuild"पूर्ण,
	अणु0x002D, "Background rebuild error on source drive"पूर्ण,
	अणु0x002E, "Replace failed because replacement drive too small"पूर्ण,
	अणु0x002F, "Verify failed because array was never initialized"पूर्ण,
	अणु0x0030, "Unsupported ATA drive"पूर्ण,
	अणु0x0031, "Synchronize host/controller time"पूर्ण,
	अणु0x0032, "Spare capacity is inadequate for some units"पूर्ण,
	अणु0x0033, "Background migration started"पूर्ण,
	अणु0x0034, "Background migration failed"पूर्ण,
	अणु0x0035, "Background migration done"पूर्ण,
	अणु0x0036, "Verify detected and fixed data/parity mismatch"पूर्ण,
	अणु0x0037, "SO-DIMM incompatible"पूर्ण,
	अणु0x0038, "SO-DIMM not detected"पूर्ण,
	अणु0x0039, "Corrected Sbuf ECC error"पूर्ण,
	अणु0x003A, "Drive power on reset detected"पूर्ण,
	अणु0x003B, "Background rebuild paused"पूर्ण,
	अणु0x003C, "Background initialize paused"पूर्ण,
	अणु0x003D, "Background verify paused"पूर्ण,
	अणु0x003E, "Background migration paused"पूर्ण,
	अणु0x003F, "Corrupt flash file system detected"पूर्ण,
	अणु0x0040, "Flash file system repaired"पूर्ण,
	अणु0x0041, "Unit number assignments were lost"पूर्ण,
	अणु0x0042, "Error during read of primary DCB"पूर्ण,
	अणु0x0043, "Latent error found in backup DCB"पूर्ण,
	अणु0x00FC, "Recovered/finished array membership update"पूर्ण,
	अणु0x00FD, "Handler lockup"पूर्ण,
	अणु0x00FE, "Retrying PCI transfer"पूर्ण,
	अणु0x00FF, "AEN queue is full"पूर्ण,
	अणु0xFFFFFFFF, (अक्षर*) 0पूर्ण
पूर्ण;

/* AEN severity table */
अटल अक्षर *twa_aen_severity_table[] =
अणु
	"None", "ERROR", "WARNING", "INFO", "DEBUG", (अक्षर*) 0
पूर्ण;

/* Error strings */
अटल twa_message_type twa_error_table[] = अणु
	अणु0x0100, "SGL entry contains zero data"पूर्ण,
	अणु0x0101, "Invalid command opcode"पूर्ण,
	अणु0x0102, "SGL entry has unaligned address"पूर्ण,
	अणु0x0103, "SGL size does not match command"पूर्ण,
	अणु0x0104, "SGL entry has illegal length"पूर्ण,
	अणु0x0105, "Command packet is not aligned"पूर्ण,
	अणु0x0106, "Invalid request ID"पूर्ण,
	अणु0x0107, "Duplicate request ID"पूर्ण,
	अणु0x0108, "ID not locked"पूर्ण,
	अणु0x0109, "LBA out of range"पूर्ण,
	अणु0x010A, "Logical unit not supported"पूर्ण,
	अणु0x010B, "Parameter table does not exist"पूर्ण,
	अणु0x010C, "Parameter index does not exist"पूर्ण,
	अणु0x010D, "Invalid field in CDB"पूर्ण,
	अणु0x010E, "Specified port has invalid drive"पूर्ण,
	अणु0x010F, "Parameter item size mismatch"पूर्ण,
	अणु0x0110, "Failed memory allocation"पूर्ण,
	अणु0x0111, "Memory request too large"पूर्ण,
	अणु0x0112, "Out of memory segments"पूर्ण,
	अणु0x0113, "Invalid address to deallocate"पूर्ण,
	अणु0x0114, "Out of memory"पूर्ण,
	अणु0x0115, "Out of heap"पूर्ण,
	अणु0x0120, "Double degrade"पूर्ण,
	अणु0x0121, "Drive not degraded"पूर्ण,
	अणु0x0122, "Reconstruct error"पूर्ण,
	अणु0x0123, "Replace not accepted"पूर्ण,
	अणु0x0124, "Replace drive capacity too small"पूर्ण,
	अणु0x0125, "Sector count not allowed"पूर्ण,
	अणु0x0126, "No spares left"पूर्ण,
	अणु0x0127, "Reconstruct error"पूर्ण,
	अणु0x0128, "Unit is offline"पूर्ण,
	अणु0x0129, "Cannot update status to DCB"पूर्ण,
	अणु0x0130, "Invalid stripe handle"पूर्ण,
	अणु0x0131, "Handle that was not locked"पूर्ण,
	अणु0x0132, "Handle that was not empty"पूर्ण,
	अणु0x0133, "Handle has different owner"पूर्ण,
	अणु0x0140, "IPR has parent"पूर्ण,
	अणु0x0150, "Illegal Pbuf address alignment"पूर्ण,
	अणु0x0151, "Illegal Pbuf transfer length"पूर्ण,
	अणु0x0152, "Illegal Sbuf address alignment"पूर्ण,
	अणु0x0153, "Illegal Sbuf transfer length"पूर्ण,
	अणु0x0160, "Command packet too large"पूर्ण,
	अणु0x0161, "SGL exceeds maximum length"पूर्ण,
	अणु0x0162, "SGL has too many entries"पूर्ण,
	अणु0x0170, "Insufficient resources for rebuilder"पूर्ण,
	अणु0x0171, "Verify error (data != parity)"पूर्ण,
	अणु0x0180, "Requested segment not in directory of this DCB"पूर्ण,
	अणु0x0181, "DCB segment has unsupported version"पूर्ण,
	अणु0x0182, "DCB segment has checksum error"पूर्ण,
	अणु0x0183, "DCB support (settings) segment invalid"पूर्ण,
	अणु0x0184, "DCB UDB (unit descriptor block) segment invalid"पूर्ण,
	अणु0x0185, "DCB GUID (globally unique identifier) segment invalid"पूर्ण,
	अणु0x01A0, "Could not clear Sbuf"पूर्ण,
	अणु0x01C0, "Flash identify failed"पूर्ण,
	अणु0x01C1, "Flash out of bounds"पूर्ण,
	अणु0x01C2, "Flash verify error"पूर्ण,
	अणु0x01C3, "Flash file object not found"पूर्ण,
	अणु0x01C4, "Flash file already present"पूर्ण,
	अणु0x01C5, "Flash file system full"पूर्ण,
	अणु0x01C6, "Flash file not present"पूर्ण,
	अणु0x01C7, "Flash file size error"पूर्ण,
	अणु0x01C8, "Bad flash file checksum"पूर्ण,
	अणु0x01CA, "Corrupt flash file system detected"पूर्ण,
	अणु0x01D0, "Invalid field in parameter list"पूर्ण,
	अणु0x01D1, "Parameter list length error"पूर्ण,
	अणु0x01D2, "Parameter item is not changeable"पूर्ण,
	अणु0x01D3, "Parameter item is not saveable"पूर्ण,
	अणु0x0200, "UDMA CRC error"पूर्ण,
	अणु0x0201, "Internal CRC error"पूर्ण,
	अणु0x0202, "Data ECC error"पूर्ण,
	अणु0x0203, "ADP level 1 error"पूर्ण,
	अणु0x0204, "Port timeout"पूर्ण,
	अणु0x0205, "Drive power on reset"पूर्ण,
	अणु0x0206, "ADP level 2 error"पूर्ण,
	अणु0x0207, "Soft reset failed"पूर्ण,
	अणु0x0208, "Drive not ready"पूर्ण,
	अणु0x0209, "Unclassified port error"पूर्ण,
	अणु0x020A, "Drive aborted command"पूर्ण,
	अणु0x0210, "Internal CRC error"पूर्ण,
	अणु0x0211, "PCI abort error"पूर्ण,
	अणु0x0212, "PCI parity error"पूर्ण,
	अणु0x0213, "Port handler error"पूर्ण,
	अणु0x0214, "Token interrupt count error"पूर्ण,
	अणु0x0215, "Timeout waiting for PCI transfer"पूर्ण,
	अणु0x0216, "Corrected buffer ECC"पूर्ण,
	अणु0x0217, "Uncorrected buffer ECC"पूर्ण,
	अणु0x0230, "Unsupported command during flash recovery"पूर्ण,
	अणु0x0231, "Next image buffer expected"पूर्ण,
	अणु0x0232, "Binary image architecture incompatible"पूर्ण,
	अणु0x0233, "Binary image has no signature"पूर्ण,
	अणु0x0234, "Binary image has bad checksum"पूर्ण,
	अणु0x0235, "Image downloaded overflowed buffer"पूर्ण,
	अणु0x0240, "I2C device not found"पूर्ण,
	अणु0x0241, "I2C transaction aborted"पूर्ण,
	अणु0x0242, "SO-DIMM parameter(s) incompatible using defaults"पूर्ण,
	अणु0x0243, "SO-DIMM unsupported"पूर्ण,
	अणु0x0248, "SPI transfer status error"पूर्ण,
	अणु0x0249, "SPI transfer timeout error"पूर्ण,
	अणु0x0250, "Invalid unit descriptor size in CreateUnit"पूर्ण,
	अणु0x0251, "Unit descriptor size exceeds data buffer in CreateUnit"पूर्ण,
	अणु0x0252, "Invalid value in CreateUnit descriptor"पूर्ण,
	अणु0x0253, "Inadequate disk space to support descriptor in CreateUnit"पूर्ण,
	अणु0x0254, "Unable to create data channel for this unit descriptor"पूर्ण,
	अणु0x0255, "CreateUnit descriptor specifies a drive already in use"पूर्ण,
	अणु0x0256, "Unable to write configuration to all disks during CreateUnit"पूर्ण,
	अणु0x0257, "CreateUnit does not support this descriptor version"पूर्ण,
	अणु0x0258, "Invalid subunit for RAID 0 or 5 in CreateUnit"पूर्ण,
	अणु0x0259, "Too many descriptors in CreateUnit"पूर्ण,
	अणु0x025A, "Invalid configuration specified in CreateUnit descriptor"पूर्ण,
	अणु0x025B, "Invalid LBA offset specified in CreateUnit descriptor"पूर्ण,
	अणु0x025C, "Invalid stripelet size specified in CreateUnit descriptor"पूर्ण,
	अणु0x0260, "SMART attribute exceeded threshold"पूर्ण,
	अणु0xFFFFFFFF, (अक्षर*) 0पूर्ण
पूर्ण;

/* Control रेजिस्टर bit definitions */
#घोषणा TW_CONTROL_CLEAR_HOST_INTERRUPT	       0x00080000
#घोषणा TW_CONTROL_CLEAR_ATTENTION_INTERRUPT   0x00040000
#घोषणा TW_CONTROL_MASK_COMMAND_INTERRUPT      0x00020000
#घोषणा TW_CONTROL_MASK_RESPONSE_INTERRUPT     0x00010000
#घोषणा TW_CONTROL_UNMASK_COMMAND_INTERRUPT    0x00008000
#घोषणा TW_CONTROL_UNMASK_RESPONSE_INTERRUPT   0x00004000
#घोषणा TW_CONTROL_CLEAR_ERROR_STATUS	       0x00000200
#घोषणा TW_CONTROL_ISSUE_SOFT_RESET	       0x00000100
#घोषणा TW_CONTROL_ENABLE_INTERRUPTS	       0x00000080
#घोषणा TW_CONTROL_DISABLE_INTERRUPTS	       0x00000040
#घोषणा TW_CONTROL_ISSUE_HOST_INTERRUPT	       0x00000020
#घोषणा TW_CONTROL_CLEAR_PARITY_ERROR	       0x00800000
#घोषणा TW_CONTROL_CLEAR_QUEUE_ERROR	       0x00400000
#घोषणा TW_CONTROL_CLEAR_PCI_ABORT	       0x00100000

/* Status रेजिस्टर bit definitions */
#घोषणा TW_STATUS_MAJOR_VERSION_MASK	       0xF0000000
#घोषणा TW_STATUS_MINOR_VERSION_MASK	       0x0F000000
#घोषणा TW_STATUS_PCI_PARITY_ERROR	       0x00800000
#घोषणा TW_STATUS_QUEUE_ERROR		       0x00400000
#घोषणा TW_STATUS_MICROCONTROLLER_ERROR	       0x00200000
#घोषणा TW_STATUS_PCI_ABORT		       0x00100000
#घोषणा TW_STATUS_HOST_INTERRUPT	       0x00080000
#घोषणा TW_STATUS_ATTENTION_INTERRUPT	       0x00040000
#घोषणा TW_STATUS_COMMAND_INTERRUPT	       0x00020000
#घोषणा TW_STATUS_RESPONSE_INTERRUPT	       0x00010000
#घोषणा TW_STATUS_COMMAND_QUEUE_FULL	       0x00008000
#घोषणा TW_STATUS_RESPONSE_QUEUE_EMPTY	       0x00004000
#घोषणा TW_STATUS_MICROCONTROLLER_READY	       0x00002000
#घोषणा TW_STATUS_COMMAND_QUEUE_EMPTY	       0x00001000
#घोषणा TW_STATUS_EXPECTED_BITS		       0x00002000
#घोषणा TW_STATUS_UNEXPECTED_BITS	       0x00F00000
#घोषणा TW_STATUS_VALID_INTERRUPT	       0x00DF0000

/* PCI related defines */
#घोषणा TW_PCI_CLEAR_PARITY_ERRORS 0xc100
#घोषणा TW_PCI_CLEAR_PCI_ABORT     0x2000

/* Command packet opcodes used by the driver */
#घोषणा TW_OP_INIT_CONNECTION	0x1
#घोषणा TW_OP_GET_PARAM		0x12
#घोषणा TW_OP_SET_PARAM		0x13
#घोषणा TW_OP_EXECUTE_SCSI	0x10
#घोषणा TW_OP_DOWNLOAD_FIRMWARE 0x16
#घोषणा TW_OP_RESET		0x1C

/* Asynchronous Event Notअगरication (AEN) codes used by the driver */
#घोषणा TW_AEN_QUEUE_EMPTY	0x0000
#घोषणा TW_AEN_SOFT_RESET	0x0001
#घोषणा TW_AEN_SYNC_TIME_WITH_HOST 0x031
#घोषणा TW_AEN_SEVERITY_ERROR	0x1
#घोषणा TW_AEN_SEVERITY_DEBUG    0x4
#घोषणा TW_AEN_NOT_RETRIEVED 0x1
#घोषणा TW_AEN_RETRIEVED 0x2

/* Command state defines */
#घोषणा TW_S_INITIAL   0x1  /* Initial state */
#घोषणा TW_S_STARTED   0x2  /* Id in use */
#घोषणा TW_S_POSTED    0x4  /* Posted to the controller */
#घोषणा TW_S_PENDING   0x8  /* Waiting to be posted in isr */
#घोषणा TW_S_COMPLETED 0x10 /* Completed by isr */
#घोषणा TW_S_FINISHED  0x20 /* I/O completely करोne */

/* Compatibility defines */
#घोषणा TW_9000_ARCH_ID 0x5
#घोषणा TW_CURRENT_DRIVER_SRL 35
#घोषणा TW_CURRENT_DRIVER_BUILD 0
#घोषणा TW_CURRENT_DRIVER_BRANCH 0

/* Misc defines */
#घोषणा TW_9550SX_DRAIN_COMPLETED	      0xFFFF
#घोषणा TW_SECTOR_SIZE			      512
#घोषणा TW_ALIGNMENT_9000		      4  /* 4 bytes */
#घोषणा TW_ALIGNMENT_9000_SGL		      0x3
#घोषणा TW_MAX_UNITS			      16
#घोषणा TW_MAX_UNITS_9650SE		      32
#घोषणा TW_INIT_MESSAGE_CREDITS		      0x100
#घोषणा TW_INIT_COMMAND_PACKET_SIZE	      0x3
#घोषणा TW_INIT_COMMAND_PACKET_SIZE_EXTENDED  0x6
#घोषणा TW_EXTENDED_INIT_CONNECT	      0x2
#घोषणा TW_BUNDLED_FW_SAFE_TO_FLASH	      0x4
#घोषणा TW_CTLR_FW_RECOMMENDS_FLASH	      0x8
#घोषणा TW_CTLR_FW_COMPATIBLE		      0x2
#घोषणा TW_BASE_FW_SRL			      24
#घोषणा TW_BASE_FW_BRANCH		      0
#घोषणा TW_BASE_FW_BUILD		      1
#घोषणा TW_FW_SRL_LUNS_SUPPORTED	      28
#घोषणा TW_Q_LENGTH			      256
#घोषणा TW_Q_START			      0
#घोषणा TW_MAX_SLOT			      32
#घोषणा TW_MAX_RESET_TRIES		      2
#घोषणा TW_MAX_CMDS_PER_LUN		      254
#घोषणा TW_MAX_RESPONSE_DRAIN		      256
#घोषणा TW_MAX_AEN_DRAIN		      255
#घोषणा TW_IN_RESET			      2
#घोषणा TW_USING_MSI			      3
#घोषणा TW_IN_ATTENTION_LOOP		      4
#घोषणा TW_MAX_SECTORS			      256
#घोषणा TW_AEN_WAIT_TIME		      1000
#घोषणा TW_IOCTL_WAIT_TIME		      (1 * HZ) /* 1 second */
#घोषणा TW_MAX_CDB_LEN			      16
#घोषणा TW_ISR_DONT_COMPLETE		      2
#घोषणा TW_ISR_DONT_RESULT		      3
#घोषणा TW_IOCTL_CHRDEV_TIMEOUT		      60 /* 60 seconds */
#घोषणा TW_IOCTL_CHRDEV_FREE		      -1
#घोषणा TW_COMMAND_OFFSET		      128 /* 128 bytes */
#घोषणा TW_VERSION_TABLE		      0x0402
#घोषणा TW_TIMEKEEP_TABLE		      0x040A
#घोषणा TW_INFORMATION_TABLE		      0x0403
#घोषणा TW_PARAM_FWVER			      3
#घोषणा TW_PARAM_FWVER_LENGTH		      16
#घोषणा TW_PARAM_BIOSVER		      4
#घोषणा TW_PARAM_BIOSVER_LENGTH		      16
#घोषणा TW_PARAM_PORTCOUNT		      3
#घोषणा TW_PARAM_PORTCOUNT_LENGTH	      1
#घोषणा TW_MIN_SGL_LENGTH		      0x200 /* 512 bytes */
#घोषणा TW_MAX_SENSE_LENGTH		      256
#घोषणा TW_EVENT_SOURCE_AEN		      0x1000
#घोषणा TW_EVENT_SOURCE_COMMAND		      0x1001
#घोषणा TW_EVENT_SOURCE_PCHIP		      0x1002
#घोषणा TW_EVENT_SOURCE_DRIVER		      0x1003
#घोषणा TW_IOCTL_GET_COMPATIBILITY_INFO	      0x101
#घोषणा TW_IOCTL_GET_LAST_EVENT		      0x102
#घोषणा TW_IOCTL_GET_FIRST_EVENT	      0x103
#घोषणा TW_IOCTL_GET_NEXT_EVENT		      0x104
#घोषणा TW_IOCTL_GET_PREVIOUS_EVENT	      0x105
#घोषणा TW_IOCTL_GET_LOCK		      0x106
#घोषणा TW_IOCTL_RELEASE_LOCK		      0x107
#घोषणा TW_IOCTL_FIRMWARE_PASS_THROUGH	      0x108
#घोषणा TW_IOCTL_ERROR_STATUS_NOT_LOCKED      0x1001 // Not locked
#घोषणा TW_IOCTL_ERROR_STATUS_LOCKED	      0x1002 // Alपढ़ोy locked
#घोषणा TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS  0x1003 // No more events
#घोषणा TW_IOCTL_ERROR_STATUS_AEN_CLOBBER     0x1004 // AEN clobber occurred
#घोषणा TW_IOCTL_ERROR_OS_EFAULT	      -EFAULT // Bad address
#घोषणा TW_IOCTL_ERROR_OS_EINTR		      -EINTR  // Interrupted प्रणाली call
#घोषणा TW_IOCTL_ERROR_OS_EINVAL	      -EINVAL // Invalid argument
#घोषणा TW_IOCTL_ERROR_OS_ENOMEM	      -ENOMEM // Out of memory
#घोषणा TW_IOCTL_ERROR_OS_ERESTARTSYS	      -ERESTARTSYS // Restart प्रणाली call
#घोषणा TW_IOCTL_ERROR_OS_EIO		      -EIO // I/O error
#घोषणा TW_IOCTL_ERROR_OS_ENOTTY	      -ENOTTY // Not a typeग_लिखोr
#घोषणा TW_IOCTL_ERROR_OS_ENODEV	      -ENODEV // No such device
#घोषणा TW_ALLOCATION_LENGTH		      128
#घोषणा TW_SENSE_DATA_LENGTH		      18
#घोषणा TW_STATUS_CHECK_CONDITION	      2
#घोषणा TW_ERROR_LOGICAL_UNIT_NOT_SUPPORTED   0x10a
#घोषणा TW_ERROR_UNIT_OFFLINE		      0x128
#घोषणा TW_MESSAGE_SOURCE_CONTROLLER_ERROR    3
#घोषणा TW_MESSAGE_SOURCE_CONTROLLER_EVENT    4
#घोषणा TW_MESSAGE_SOURCE_LINUX_DRIVER	      6
#घोषणा TW_DRIVER TW_MESSAGE_SOURCE_LINUX_DRIVER
#घोषणा TW_MESSAGE_SOURCE_LINUX_OS	      9
#घोषणा TW_OS TW_MESSAGE_SOURCE_LINUX_OS
#अगर_अघोषित PCI_DEVICE_ID_3WARE_9000
#घोषणा PCI_DEVICE_ID_3WARE_9000 0x1002
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_3WARE_9550SX
#घोषणा PCI_DEVICE_ID_3WARE_9550SX 0x1003
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_3WARE_9650SE
#घोषणा PCI_DEVICE_ID_3WARE_9650SE 0x1004
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_3WARE_9690SA
#घोषणा PCI_DEVICE_ID_3WARE_9690SA 0x1005
#पूर्ण_अगर

/* Biपंचांगask macros to eliminate bitfields */

/* opcode: 5, reserved: 3 */
#घोषणा TW_OPRES_IN(x,y) ((x << 5) | (y & 0x1f))
#घोषणा TW_OP_OUT(x) (x & 0x1f)

/* opcode: 5, sgloffset: 3 */
#घोषणा TW_OPSGL_IN(x,y) ((x << 5) | (y & 0x1f))
#घोषणा TW_SGL_OUT(x) ((x >> 5) & 0x7)

/* severity: 3, reserved: 5 */
#घोषणा TW_SEV_OUT(x) (x & 0x7)

/* reserved_1: 4, response_id: 8, reserved_2: 20 */
#घोषणा TW_RESID_OUT(x) ((x >> 4) & 0xff)

/* request_id: 12, lun: 4 */
#घोषणा TW_REQ_LUN_IN(lun, request_id)			\
	(((lun << 12) & 0xf000) | (request_id & 0xfff))
#घोषणा TW_LUN_OUT(lun) ((lun >> 12) & 0xf)

/* Macros */
#घोषणा TW_CONTROL_REG_ADDR(x) (x->base_addr)
#घोषणा TW_STATUS_REG_ADDR(x) ((अचिन्हित अक्षर __iomem *)x->base_addr + 0x4)
#घोषणा TW_COMMAND_QUEUE_REG_ADDR(x) \
	(माप(dma_addr_t) > 4 ? ((अचिन्हित अक्षर __iomem *)x->base_addr + 0x20) : ((अचिन्हित अक्षर __iomem *)x->base_addr + 0x8))
#घोषणा TW_COMMAND_QUEUE_REG_ADDR_LARGE(x) \
	((अचिन्हित अक्षर __iomem *)x->base_addr + 0x20)
#घोषणा TW_RESPONSE_QUEUE_REG_ADDR(x) \
	((अचिन्हित अक्षर __iomem *)x->base_addr + 0xC)
#घोषणा TW_RESPONSE_QUEUE_REG_ADDR_LARGE(x) \
	((अचिन्हित अक्षर __iomem *)x->base_addr + 0x30)
#घोषणा TW_CLEAR_ALL_INTERRUPTS(x) \
	(ग_लिखोl(TW_STATUS_VALID_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_CLEAR_ATTENTION_INTERRUPT(x) \
	(ग_लिखोl(TW_CONTROL_CLEAR_ATTENTION_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_CLEAR_HOST_INTERRUPT(x) \
	(ग_लिखोl(TW_CONTROL_CLEAR_HOST_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_DISABLE_INTERRUPTS(x) \
	(ग_लिखोl(TW_CONTROL_DISABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_ENABLE_AND_CLEAR_INTERRUPTS(x)				\
	(ग_लिखोl(TW_CONTROL_CLEAR_ATTENTION_INTERRUPT |			\
		TW_CONTROL_UNMASK_RESPONSE_INTERRUPT |			\
		TW_CONTROL_ENABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_MASK_COMMAND_INTERRUPT(x)					\
	(ग_लिखोl(TW_CONTROL_MASK_COMMAND_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_UNMASK_COMMAND_INTERRUPT(x)					\
	(ग_लिखोl(TW_CONTROL_UNMASK_COMMAND_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_SOFT_RESET(x) (ग_लिखोl(TW_CONTROL_ISSUE_SOFT_RESET |	\
			TW_CONTROL_CLEAR_HOST_INTERRUPT | \
			TW_CONTROL_CLEAR_ATTENTION_INTERRUPT | \
			TW_CONTROL_MASK_COMMAND_INTERRUPT | \
			TW_CONTROL_MASK_RESPONSE_INTERRUPT | \
			TW_CONTROL_CLEAR_ERROR_STATUS | \
			TW_CONTROL_DISABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_PRINTK(h,a,b,c) अणु \
अगर (h) \
prपूर्णांकk(KERN_WARNING "3w-9xxx: scsi%d: ERROR: (0x%02X:0x%04X): %s.\n",h->host_no,a,b,c); \
अन्यथा \
prपूर्णांकk(KERN_WARNING "3w-9xxx: ERROR: (0x%02X:0x%04X): %s.\n",a,b,c); \
पूर्ण
#घोषणा TW_MAX_LUNS(srl) (srl < TW_FW_SRL_LUNS_SUPPORTED ? 1 : 16)
#घोषणा TW_COMMAND_SIZE (माप(dma_addr_t) > 4 ? 5 : 4)
#घोषणा TW_APACHE_MAX_SGL_LENGTH (माप(dma_addr_t) > 4 ? 72 : 109)
#घोषणा TW_ESCALADE_MAX_SGL_LENGTH (माप(dma_addr_t) > 4 ? 41 : 62)
#घोषणा TW_PADDING_LENGTH (माप(dma_addr_t) > 4 ? 8 : 0)
#घोषणा TW_CPU_TO_SGL(x) (माप(dma_addr_t) > 4 ? cpu_to_le64(x) : cpu_to_le32(x))

#आशय pack(1)

/* Scatter Gather List Entry */
प्रकार काष्ठा TAG_TW_SG_Entry अणु
	dma_addr_t address;
	u32 length;
पूर्ण TW_SG_Entry;

/* Command Packet */
प्रकार काष्ठा TW_Command अणु
	अचिन्हित अक्षर opcode__sgloffset;
	अचिन्हित अक्षर size;
	अचिन्हित अक्षर request_id;
	अचिन्हित अक्षर unit__hostid;
	/* Second DWORD */
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर flags;
	जोड़ अणु
		अचिन्हित लघु block_count;
		अचिन्हित लघु parameter_count;
	पूर्ण byte6_offset;
	जोड़ अणु
		काष्ठा अणु
			u32 lba;
			TW_SG_Entry sgl[TW_ESCALADE_MAX_SGL_LENGTH];
			dma_addr_t padding;
		पूर्ण io;
		काष्ठा अणु
			TW_SG_Entry sgl[TW_ESCALADE_MAX_SGL_LENGTH];
			u32 padding;
			dma_addr_t padding2;
		पूर्ण param;
	पूर्ण byte8_offset;
पूर्ण TW_Command;

/* Command Packet क्रम 9000+ controllers */
प्रकार काष्ठा TAG_TW_Command_Apache अणु
	अचिन्हित अक्षर opcode__reserved;
	अचिन्हित अक्षर unit;
	अचिन्हित लघु request_id__lunl;
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर sgl_offset;
	अचिन्हित लघु sgl_entries__lunh;
	अचिन्हित अक्षर cdb[16];
	TW_SG_Entry sg_list[TW_APACHE_MAX_SGL_LENGTH];
	अचिन्हित अक्षर padding[TW_PADDING_LENGTH];
पूर्ण TW_Command_Apache;

/* New command packet header */
प्रकार काष्ठा TAG_TW_Command_Apache_Header अणु
	अचिन्हित अक्षर sense_data[TW_SENSE_DATA_LENGTH];
	काष्ठा अणु
		अक्षर reserved[4];
		अचिन्हित लघु error;
		अचिन्हित अक्षर padding;
		अचिन्हित अक्षर severity__reserved;
	पूर्ण status_block;
	अचिन्हित अक्षर err_specअगरic_desc[98];
	काष्ठा अणु
		अचिन्हित अक्षर size_header;
		अचिन्हित लघु reserved;
		अचिन्हित अक्षर size_sense;
	पूर्ण header_desc;
पूर्ण TW_Command_Apache_Header;

/* This काष्ठा is a जोड़ of the 2 command packets */
प्रकार काष्ठा TAG_TW_Command_Full अणु
	TW_Command_Apache_Header header;
	जोड़ अणु
		TW_Command oldcommand;
		TW_Command_Apache newcommand;
	पूर्ण command;
पूर्ण TW_Command_Full;

/* Initconnection काष्ठाure */
प्रकार काष्ठा TAG_TW_Initconnect अणु
	अचिन्हित अक्षर opcode__reserved;
	अचिन्हित अक्षर size;
	अचिन्हित अक्षर request_id;
	अचिन्हित अक्षर res2;
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर flags;
	अचिन्हित लघु message_credits;
	u32 features;
	अचिन्हित लघु fw_srl;
	अचिन्हित लघु fw_arch_id;
	अचिन्हित लघु fw_branch;
	अचिन्हित लघु fw_build;
	u32 result;
पूर्ण TW_Initconnect;

/* Event info काष्ठाure */
प्रकार काष्ठा TAG_TW_Event
अणु
	अचिन्हित पूर्णांक sequence_id;
	अचिन्हित पूर्णांक समय_stamp_sec;
	अचिन्हित लघु aen_code;
	अचिन्हित अक्षर severity;
	अचिन्हित अक्षर retrieved;
	अचिन्हित अक्षर repeat_count;
	अचिन्हित अक्षर parameter_len;
	अचिन्हित अक्षर parameter_data[98];
पूर्ण TW_Event;

प्रकार काष्ठा TAG_TW_Ioctl_Driver_Command अणु
	अचिन्हित पूर्णांक control_code;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक unique_id;
	अचिन्हित पूर्णांक sequence_id;
	अचिन्हित पूर्णांक os_specअगरic;
	अचिन्हित पूर्णांक buffer_length;
पूर्ण TW_Ioctl_Driver_Command;

प्रकार काष्ठा TAG_TW_Ioctl_Apache अणु
	TW_Ioctl_Driver_Command driver_command;
	अक्षर padding[488];
	TW_Command_Full firmware_command;
	अक्षर data_buffer[1];
पूर्ण TW_Ioctl_Buf_Apache;

/* Lock काष्ठाure क्रम ioctl get/release lock */
प्रकार काष्ठा TAG_TW_Lock अणु
	अचिन्हित दीर्घ समयout_msec;
	अचिन्हित दीर्घ समय_reमुख्यing_msec;
	अचिन्हित दीर्घ क्रमce_flag;
पूर्ण TW_Lock;

/* GetParam descriptor */
प्रकार काष्ठा अणु
	अचिन्हित लघु	table_id;
	अचिन्हित लघु	parameter_id;
	अचिन्हित लघु	parameter_size_bytes;
	अचिन्हित लघु  actual_parameter_size_bytes;
	अचिन्हित अक्षर	data[1];
पूर्ण TW_Param_Apache, *PTW_Param_Apache;

/* Response queue */
प्रकार जोड़ TAG_TW_Response_Queue अणु
	u32 response_id;
	u32 value;
पूर्ण TW_Response_Queue;

/* Compatibility inक्रमmation काष्ठाure */
प्रकार काष्ठा TAG_TW_Compatibility_Info
अणु
	अक्षर driver_version[32];
	अचिन्हित लघु working_srl;
	अचिन्हित लघु working_branch;
	अचिन्हित लघु working_build;
	अचिन्हित लघु driver_srl_high;
	अचिन्हित लघु driver_branch_high;
	अचिन्हित लघु driver_build_high;
	अचिन्हित लघु driver_srl_low;
	अचिन्हित लघु driver_branch_low;
	अचिन्हित लघु driver_build_low;
	अचिन्हित लघु fw_on_ctlr_srl;
	अचिन्हित लघु fw_on_ctlr_branch;
	अचिन्हित लघु fw_on_ctlr_build;
पूर्ण TW_Compatibility_Info;

#आशय pack()

प्रकार काष्ठा TAG_TW_Device_Extension अणु
	u32			__iomem *base_addr;
	अचिन्हित दीर्घ		*generic_buffer_virt[TW_Q_LENGTH];
	dma_addr_t		generic_buffer_phys[TW_Q_LENGTH];
	TW_Command_Full		*command_packet_virt[TW_Q_LENGTH];
	dma_addr_t		command_packet_phys[TW_Q_LENGTH];
	काष्ठा pci_dev		*tw_pci_dev;
	काष्ठा scsi_cmnd	*srb[TW_Q_LENGTH];
	अचिन्हित अक्षर		मुक्त_queue[TW_Q_LENGTH];
	अचिन्हित अक्षर		मुक्त_head;
	अचिन्हित अक्षर		मुक्त_tail;
	अचिन्हित अक्षर		pending_queue[TW_Q_LENGTH];
	अचिन्हित अक्षर		pending_head;
	अचिन्हित अक्षर		pending_tail;
	पूर्णांक			state[TW_Q_LENGTH];
	अचिन्हित पूर्णांक		posted_request_count;
	अचिन्हित पूर्णांक		max_posted_request_count;
	अचिन्हित पूर्णांक		pending_request_count;
	अचिन्हित पूर्णांक		max_pending_request_count;
	अचिन्हित पूर्णांक		max_sgl_entries;
	अचिन्हित पूर्णांक		sgl_entries;
	अचिन्हित पूर्णांक		num_resets;
	अचिन्हित पूर्णांक		sector_count;
	अचिन्हित पूर्णांक		max_sector_count;
	अचिन्हित पूर्णांक		aen_count;
	काष्ठा Scsi_Host	*host;
	दीर्घ			flags;
	पूर्णांक			reset_prपूर्णांक;
	TW_Event		*event_queue[TW_Q_LENGTH];
	अचिन्हित अक्षर		error_index;
	अचिन्हित अक्षर		event_queue_wrapped;
	अचिन्हित पूर्णांक		error_sequence_id;
	पूर्णांक			ioctl_sem_lock;
	kसमय_प्रकार			ioctl_समय;
	पूर्णांक			chrdev_request_id;
	रुको_queue_head_t	ioctl_wqueue;
	काष्ठा mutex		ioctl_lock;
	अक्षर			aen_clobber;
	TW_Compatibility_Info	tw_compat_info;
पूर्ण TW_Device_Extension;

#पूर्ण_अगर /* _3W_9XXX_H */

