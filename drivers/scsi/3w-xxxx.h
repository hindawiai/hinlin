<शैली गुरु>
/*
   3w-xxxx.h -- 3ware Storage Controller device driver क्रम Linux.

   Written By: Adam Radक्रमd <aradक्रमd@gmail.com>
   Modअगरications By: Joel Jacobson <linux@3ware.com>
                     Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
                     Brad Stअक्रम <linux@3ware.com>

   Copyright (C) 1999-2010 3ware Inc.

   Kernel compatibility By:	Andre Hedrick <andre@suse.com>
   Non-Copyright (C) 2000	Andre Hedrick <andre@suse.com>

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

   For more inक्रमmation, जाओ:
   http://www.lsi.com
*/

#अगर_अघोषित _3W_XXXX_H
#घोषणा _3W_XXXX_H

#समावेश <linux/types.h>

/* AEN strings */
अटल अक्षर *tw_aen_string[] = अणु
	[0x000] = "INFO: AEN queue empty",
	[0x001] = "INFO: Soft reset occurred",
	[0x002] = "ERROR: Unit degraded: Unit #",
	[0x003] = "ERROR: Controller error",
	[0x004] = "ERROR: Rebuild failed: Unit #",
	[0x005] = "INFO: Rebuild complete: Unit #",
	[0x006] = "ERROR: Incomplete unit detected: Unit #",
	[0x007] = "INFO: Initialization complete: Unit #",
	[0x008] = "WARNING: Unclean shutdown detected: Unit #",
	[0x009] = "WARNING: ATA port timeout: Port #",
	[0x00A] = "ERROR: Drive error: Port #",
	[0x00B] = "INFO: Rebuild started: Unit #",
	[0x00C] = "INFO: Initialization started: Unit #",
	[0x00D] = "ERROR: Logical unit deleted: Unit #",
	[0x00F] = "WARNING: SMART threshold exceeded: Port #",
	[0x021] = "WARNING: ATA UDMA downgrade: Port #",
	[0x022] = "WARNING: ATA UDMA upgrade: Port #",
	[0x023] = "WARNING: Sector repair occurred: Port #",
	[0x024] = "ERROR: SBUF integrity check failure",
	[0x025] = "ERROR: Lost cached write: Port #",
	[0x026] = "ERROR: Drive ECC error detected: Port #",
	[0x027] = "ERROR: DCB checksum error: Port #",
	[0x028] = "ERROR: DCB unsupported version: Port #",
	[0x029] = "INFO: Verify started: Unit #",
	[0x02A] = "ERROR: Verify failed: Port #",
	[0x02B] = "INFO: Verify complete: Unit #",
	[0x02C] = "WARNING: Overwrote bad sector during rebuild: Port #",
	[0x02D] = "ERROR: Encountered bad sector during rebuild: Port #",
	[0x02E] = "ERROR: Replacement drive is too small: Port #",
	[0x02F] = "WARNING: Verify error: Unit not previously initialized: Unit #",
	[0x030] = "ERROR: Drive not supported: Port #"
पूर्ण;

/*
   Sense key lookup table
   Format: ESDC/flags,SenseKey,AdditionalSenseCode,AdditionalSenseCodeQualअगरier
*/
अटल अचिन्हित अक्षर tw_sense_table[][4] =
अणु
  /* Codes क्रम newer firmware */
	// ATA Error                    SCSI Error
	अणु0x01, 0x03, 0x13, 0x00पूर्ण, // Address mark not found       Address mark not found क्रम data field
	अणु0x04, 0x0b, 0x00, 0x00पूर्ण, // Aborted command              Aborted command
	अणु0x10, 0x0b, 0x14, 0x00पूर्ण, // ID not found                 Recorded entity not found
	अणु0x40, 0x03, 0x11, 0x00पूर्ण, // Uncorrectable ECC error      Unrecovered पढ़ो error
	अणु0x61, 0x04, 0x00, 0x00पूर्ण, // Device fault                 Hardware error
	अणु0x84, 0x0b, 0x47, 0x00पूर्ण, // Data CRC error               SCSI parity error
	अणु0xd0, 0x0b, 0x00, 0x00पूर्ण, // Device busy                  Aborted command
	अणु0xd1, 0x0b, 0x00, 0x00पूर्ण, // Device busy                  Aborted command
	अणु0x37, 0x02, 0x04, 0x00पूर्ण, // Unit offline                 Not पढ़ोy
	अणु0x09, 0x02, 0x04, 0x00पूर्ण, // Unrecovered disk error       Not पढ़ोy

	/* Codes क्रम older firmware */
	// 3ware Error                  SCSI Error
	अणु0x51, 0x0b, 0x00, 0x00पूर्ण  // Unspecअगरied                  Aborted command
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
#घोषणा TW_CONTROL_CLEAR_SBUF_WRITE_ERROR      0x00000008

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
#घोषणा TW_STATUS_ALL_INTERRUPTS	       0x000F0000
#घोषणा TW_STATUS_CLEARABLE_BITS	       0x00D00000
#घोषणा TW_STATUS_EXPECTED_BITS		       0x00002000
#घोषणा TW_STATUS_UNEXPECTED_BITS	       0x00F00008
#घोषणा TW_STATUS_SBUF_WRITE_ERROR	       0x00000008
#घोषणा TW_STATUS_VALID_INTERRUPT	       0x00DF0008

/* RESPONSE QUEUE BIT DEFINITIONS */
#घोषणा TW_RESPONSE_ID_MASK		       0x00000FF0

/* PCI related defines */
#घोषणा TW_IO_ADDRESS_RANGE		       0x10
#घोषणा TW_DEVICE_NAME			       "3ware Storage Controller"
#घोषणा TW_VENDOR_ID (0x13C1)	/* 3ware */
#घोषणा TW_DEVICE_ID (0x1000)	/* Storage Controller */
#घोषणा TW_DEVICE_ID2 (0x1001)  /* 7000 series controller */
#घोषणा TW_NUMDEVICES 2
#घोषणा TW_PCI_CLEAR_PARITY_ERRORS 0xc100
#घोषणा TW_PCI_CLEAR_PCI_ABORT     0x2000

/* Command packet opcodes */
#घोषणा TW_OP_NOP	      0x0
#घोषणा TW_OP_INIT_CONNECTION 0x1
#घोषणा TW_OP_READ	      0x2
#घोषणा TW_OP_WRITE	      0x3
#घोषणा TW_OP_VERIFY	      0x4
#घोषणा TW_OP_GET_PARAM	      0x12
#घोषणा TW_OP_SET_PARAM	      0x13
#घोषणा TW_OP_SECTOR_INFO     0x1a
#घोषणा TW_OP_AEN_LISTEN      0x1c
#घोषणा TW_OP_FLUSH_CACHE     0x0e
#घोषणा TW_CMD_PACKET	      0x1d
#घोषणा TW_CMD_PACKET_WITH_DATA 0x1f

/* Asynchronous Event Notअगरication (AEN) Codes */
#घोषणा TW_AEN_QUEUE_EMPTY       0x0000
#घोषणा TW_AEN_SOFT_RESET	 0x0001
#घोषणा TW_AEN_DEGRADED_MIRROR   0x0002
#घोषणा TW_AEN_CONTROLLER_ERROR  0x0003
#घोषणा TW_AEN_REBUILD_FAIL      0x0004
#घोषणा TW_AEN_REBUILD_DONE      0x0005
#घोषणा TW_AEN_QUEUE_FULL	 0x00ff
#घोषणा TW_AEN_TABLE_UNDEFINED   0x15
#घोषणा TW_AEN_APORT_TIMEOUT     0x0009
#घोषणा TW_AEN_DRIVE_ERROR       0x000A
#घोषणा TW_AEN_SMART_FAIL	 0x000F
#घोषणा TW_AEN_SBUF_FAIL	 0x0024

/* Misc defines */
#घोषणा TW_ALIGNMENT_6000		      64 /* 64 bytes */
#घोषणा TW_ALIGNMENT_7000		      4  /* 4 bytes */
#घोषणा TW_MAX_UNITS			      16
#घोषणा TW_COMMAND_ALIGNMENT_MASK	      0x1ff
#घोषणा TW_INIT_MESSAGE_CREDITS		      0x100
#घोषणा TW_INIT_COMMAND_PACKET_SIZE	      0x3
#घोषणा TW_POLL_MAX_RETRIES		      20000
#घोषणा TW_MAX_SGL_LENGTH		      62
#घोषणा TW_ATA_PASS_SGL_MAX		      60
#घोषणा TW_Q_LENGTH			      256
#घोषणा TW_Q_START			      0
#घोषणा TW_MAX_SLOT			      32
#घोषणा TW_MAX_PCI_BUSES		      255
#घोषणा TW_MAX_RESET_TRIES		      3
#घोषणा TW_UNIT_INFORMATION_TABLE_BASE	      0x300
#घोषणा TW_MAX_CMDS_PER_LUN		      254 /* 254 क्रम io, 1 क्रम
                                                     chrdev ioctl, one क्रम
                                                     पूर्णांकernal aen post */
#घोषणा TW_BLOCK_SIZE			      0x200 /* 512-byte blocks */
#घोषणा TW_IOCTL			      0x80
#घोषणा TW_UNIT_ONLINE			      1
#घोषणा TW_IN_INTR			      1
#घोषणा TW_IN_RESET			      2
#घोषणा TW_IN_CHRDEV_IOCTL		      3
#घोषणा TW_MAX_SECTORS			      256
#घोषणा TW_MAX_IOCTL_SECTORS		      512
#घोषणा TW_AEN_WAIT_TIME		      1000
#घोषणा TW_IOCTL_WAIT_TIME		      (1 * HZ) /* 1 second */
#घोषणा TW_ISR_DONT_COMPLETE		      2
#घोषणा TW_ISR_DONT_RESULT		      3
#घोषणा TW_IOCTL_TIMEOUT		      25 /* 25 seconds */
#घोषणा TW_IOCTL_CHRDEV_TIMEOUT		      60 /* 60 seconds */
#घोषणा TW_IOCTL_CHRDEV_FREE		      -1
#घोषणा TW_MAX_CDB_LEN			      16

/* Biपंचांगask macros to eliminate bitfields */

/* opcode: 5, sgloffset: 3 */
#घोषणा TW_OPSGL_IN(x,y) ((x << 5) | (y & 0x1f))
#घोषणा TW_SGL_OUT(x) ((x >> 5) & 0x7)

/* reserved_1: 4, response_id: 8, reserved_2: 20 */
#घोषणा TW_RESID_OUT(x) ((x >> 4) & 0xff)

/* unit: 4, host_id: 4 */
#घोषणा TW_UNITHOST_IN(x,y) ((x << 4) | ( y & 0xf))
#घोषणा TW_UNIT_OUT(x) (x & 0xf)

/* Macros */
#घोषणा TW_CONTROL_REG_ADDR(x) (x->base_addr)
#घोषणा TW_STATUS_REG_ADDR(x) (x->base_addr + 0x4)
#घोषणा TW_COMMAND_QUEUE_REG_ADDR(x) (x->base_addr + 0x8)
#घोषणा TW_RESPONSE_QUEUE_REG_ADDR(x) (x->base_addr + 0xC)
#घोषणा TW_CLEAR_ALL_INTERRUPTS(x)					\
	(outl(TW_STATUS_VALID_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_CLEAR_ATTENTION_INTERRUPT(x)					\
	(outl(TW_CONTROL_CLEAR_ATTENTION_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_CLEAR_HOST_INTERRUPT(x)					\
	(outl(TW_CONTROL_CLEAR_HOST_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_DISABLE_INTERRUPTS(x)					\
	(outl(TW_CONTROL_DISABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_ENABLE_AND_CLEAR_INTERRUPTS(x)				\
	(outl(TW_CONTROL_CLEAR_ATTENTION_INTERRUPT |			\
	      TW_CONTROL_UNMASK_RESPONSE_INTERRUPT |			\
	      TW_CONTROL_ENABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_MASK_COMMAND_INTERRUPT(x)					\
	(outl(TW_CONTROL_MASK_COMMAND_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_UNMASK_COMMAND_INTERRUPT(x)					\
	(outl(TW_CONTROL_UNMASK_COMMAND_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_SOFT_RESET(x) (outl(TW_CONTROL_ISSUE_SOFT_RESET |		\
			       TW_CONTROL_CLEAR_HOST_INTERRUPT |	\
			       TW_CONTROL_CLEAR_ATTENTION_INTERRUPT |	\
			       TW_CONTROL_MASK_COMMAND_INTERRUPT |	\
			       TW_CONTROL_MASK_RESPONSE_INTERRUPT |	\
			       TW_CONTROL_CLEAR_ERROR_STATUS |		\
			       TW_CONTROL_DISABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
#घोषणा TW_STATUS_ERRORS(x)				\
	(((x & TW_STATUS_PCI_ABORT) ||			\
	  (x & TW_STATUS_PCI_PARITY_ERROR) ||		\
	  (x & TW_STATUS_QUEUE_ERROR) ||		\
	  (x & TW_STATUS_MICROCONTROLLER_ERROR)) &&	\
	 (x & TW_STATUS_MICROCONTROLLER_READY))

#अगर_घोषित TW_DEBUG
#घोषणा dprपूर्णांकk(msg...) prपूर्णांकk(msg)
#अन्यथा
#घोषणा dprपूर्णांकk(msg...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#आशय pack(1)

/* Scatter Gather List Entry */
प्रकार काष्ठा TAG_TW_SG_Entry अणु
	u32 address;
	u32 length;
पूर्ण TW_SG_Entry;

प्रकार अचिन्हित अक्षर TW_Sector[512];

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
		अचिन्हित लघु message_credits;
	पूर्ण byte6;
	जोड़ अणु
		काष्ठा अणु
			u32 lba;
			TW_SG_Entry sgl[TW_MAX_SGL_LENGTH];
			u32 padding;	/* pad to 512 bytes */
		पूर्ण io;
		काष्ठा अणु
			TW_SG_Entry sgl[TW_MAX_SGL_LENGTH];
			u32 padding[2];
		पूर्ण param;
		काष्ठा अणु
			u32 response_queue_poपूर्णांकer;
			u32 padding[125];
		पूर्ण init_connection;
		काष्ठा अणु
			अक्षर version[504];
		पूर्ण ioctl_miniport_version;
	पूर्ण byte8;
पूर्ण TW_Command;

#आशय pack()

प्रकार काष्ठा TAG_TW_Ioctl अणु
	अचिन्हित अक्षर opcode;
	अचिन्हित लघु table_id;
	अचिन्हित अक्षर parameter_id;
	अचिन्हित अक्षर parameter_size_bytes;
	अचिन्हित अक्षर unit_index;
	अचिन्हित अक्षर data[1];
पूर्ण TW_Ioctl;

#आशय pack(1)

/* Structure क्रम new अक्षरdev ioctls */
प्रकार काष्ठा TAG_TW_New_Ioctl अणु
	अचिन्हित पूर्णांक data_buffer_length;
	अचिन्हित अक्षर padding [508];
	TW_Command firmware_command;
	अक्षर data_buffer[1];
पूर्ण TW_New_Ioctl;

/* GetParam descriptor */
प्रकार काष्ठा अणु
	अचिन्हित लघु	table_id;
	अचिन्हित अक्षर	parameter_id;
	अचिन्हित अक्षर	parameter_size_bytes;
	अचिन्हित अक्षर	data[1];
पूर्ण TW_Param, *PTW_Param;

/* Response queue */
प्रकार जोड़ TAG_TW_Response_Queue अणु
	u32 response_id;
	u32 value;
पूर्ण TW_Response_Queue;

प्रकार पूर्णांक TW_Cmd_State;

#घोषणा TW_S_INITIAL   0x1  /* Initial state */
#घोषणा TW_S_STARTED   0x2  /* Id in use */
#घोषणा TW_S_POSTED    0x4  /* Posted to the controller */
#घोषणा TW_S_PENDING   0x8  /* Waiting to be posted in isr */
#घोषणा TW_S_COMPLETED 0x10 /* Completed by isr */
#घोषणा TW_S_FINISHED  0x20 /* I/O completely करोne */
#घोषणा TW_START_MASK (TW_S_STARTED | TW_S_POSTED | TW_S_PENDING | TW_S_COMPLETED)

/* Command header क्रम ATA pass-thru */
प्रकार काष्ठा TAG_TW_Passthru
अणु
	अचिन्हित अक्षर opcode__sgloffset;
	अचिन्हित अक्षर size;
	अचिन्हित अक्षर request_id;
	अचिन्हित अक्षर aport__hostid;
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर flags;
	अचिन्हित लघु param;
	अचिन्हित लघु features;
	अचिन्हित लघु sector_count;
	अचिन्हित लघु sector_num;
	अचिन्हित लघु cylinder_lo;
	अचिन्हित लघु cylinder_hi;
	अचिन्हित अक्षर drive_head;
	अचिन्हित अक्षर command;
	TW_SG_Entry sg_list[TW_ATA_PASS_SGL_MAX];
	अचिन्हित अक्षर padding[12];
पूर्ण TW_Passthru;

#आशय pack()

प्रकार काष्ठा TAG_TW_Device_Extension अणु
	u32			base_addr;
	अचिन्हित दीर्घ		*alignment_भव_address[TW_Q_LENGTH];
	अचिन्हित दीर्घ		alignment_physical_address[TW_Q_LENGTH];
	पूर्णांक			is_unit_present[TW_MAX_UNITS];
	अचिन्हित दीर्घ		*command_packet_भव_address[TW_Q_LENGTH];
	अचिन्हित दीर्घ		command_packet_physical_address[TW_Q_LENGTH];
	काष्ठा pci_dev		*tw_pci_dev;
	काष्ठा scsi_cmnd	*srb[TW_Q_LENGTH];
	अचिन्हित अक्षर		मुक्त_queue[TW_Q_LENGTH];
	अचिन्हित अक्षर		मुक्त_head;
	अचिन्हित अक्षर		मुक्त_tail;
	अचिन्हित अक्षर		pending_queue[TW_Q_LENGTH];
	अचिन्हित अक्षर		pending_head;
	अचिन्हित अक्षर		pending_tail;
	TW_Cmd_State		state[TW_Q_LENGTH];
	u32			posted_request_count;
	u32			max_posted_request_count;
	u32			request_count_marked_pending;
	u32			pending_request_count;
	u32			max_pending_request_count;
	u32			max_sgl_entries;
	u32			sgl_entries;
	u32			num_resets;
	u32			sector_count;
	u32			max_sector_count;
	u32			aen_count;
	काष्ठा Scsi_Host	*host;
	काष्ठा mutex		ioctl_lock;
	अचिन्हित लघु		aen_queue[TW_Q_LENGTH];
	अचिन्हित अक्षर		aen_head;
	अचिन्हित अक्षर		aen_tail;
	अस्थिर दीर्घ		flags; /* दीर्घ req'd क्रम set_bit --RR */
	पूर्णांक			reset_prपूर्णांक;
	अस्थिर पूर्णांक		chrdev_request_id;
	रुको_queue_head_t	ioctl_wqueue;
पूर्ण TW_Device_Extension;

#पूर्ण_अगर /* _3W_XXXX_H */
