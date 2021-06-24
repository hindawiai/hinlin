<शैली गुरु>
/*
   3w-sas.h -- LSI 3ware SAS/SATA-RAID Controller device driver क्रम Linux.

   Written By: Adam Radक्रमd <aradक्रमd@gmail.com>

   Copyright (C) 2009 LSI Corporation.

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

#अगर_अघोषित _3W_SAS_H
#घोषणा _3W_SAS_H

/* AEN severity table */
अटल अक्षर *twl_aen_severity_table[] =
अणु
	"None", "ERROR", "WARNING", "INFO", "DEBUG", शून्य
पूर्ण;

/* Liberator रेजिस्टर offsets */
#घोषणा TWL_STATUS			   0x0  /* Status */
#घोषणा TWL_HIBDB			   0x20 /* Inbound करोorbell */
#घोषणा TWL_HISTAT			   0x30 /* Host पूर्णांकerrupt status */
#घोषणा TWL_HIMASK			   0x34 /* Host पूर्णांकerrupt mask */
#घोषणा TWL_HOBDB			   0x9C /* Outbound करोorbell */
#घोषणा TWL_HOBDBC			   0xA0 /* Outbound करोorbell clear */
#घोषणा TWL_SCRPD3			   0xBC /* Scratchpad */
#घोषणा TWL_HIBQPL			   0xC0 /* Host inbound Q low */
#घोषणा TWL_HIBQPH			   0xC4 /* Host inbound Q high */
#घोषणा TWL_HOBQPL			   0xC8 /* Host outbound Q low */
#घोषणा TWL_HOBQPH			   0xCC /* Host outbound Q high */
#घोषणा TWL_HISTATUS_VALID_INTERRUPT	   0xC
#घोषणा TWL_HISTATUS_ATTENTION_INTERRUPT   0x4
#घोषणा TWL_HISTATUS_RESPONSE_INTERRUPT	   0x8
#घोषणा TWL_STATUS_OVERRUN_SUBMIT	   0x2000
#घोषणा TWL_ISSUE_SOFT_RESET		   0x100
#घोषणा TWL_CONTROLLER_READY		   0x2000
#घोषणा TWL_DOORBELL_CONTROLLER_ERROR	   0x200000
#घोषणा TWL_DOORBELL_ATTENTION_INTERRUPT   0x40000
#घोषणा TWL_PULL_MODE			   0x1

/* Command packet opcodes used by the driver */
#घोषणा TW_OP_INIT_CONNECTION 0x1
#घोषणा TW_OP_GET_PARAM	      0x12
#घोषणा TW_OP_SET_PARAM	      0x13
#घोषणा TW_OP_EXECUTE_SCSI    0x10

/* Asynchronous Event Notअगरication (AEN) codes used by the driver */
#घोषणा TW_AEN_QUEUE_EMPTY	 0x0000
#घोषणा TW_AEN_SOFT_RESET	 0x0001
#घोषणा TW_AEN_SYNC_TIME_WITH_HOST 0x031
#घोषणा TW_AEN_SEVERITY_ERROR	 0x1
#घोषणा TW_AEN_SEVERITY_DEBUG	 0x4
#घोषणा TW_AEN_NOT_RETRIEVED	 0x1

/* Command state defines */
#घोषणा TW_S_INITIAL   0x1  /* Initial state */
#घोषणा TW_S_STARTED   0x2  /* Id in use */
#घोषणा TW_S_POSTED    0x4  /* Posted to the controller */
#घोषणा TW_S_COMPLETED 0x8  /* Completed by isr */
#घोषणा TW_S_FINISHED  0x10 /* I/O completely करोne */

/* Compatibility defines */
#घोषणा TW_9750_ARCH_ID 10
#घोषणा TW_CURRENT_DRIVER_SRL 40
#घोषणा TW_CURRENT_DRIVER_BUILD 0
#घोषणा TW_CURRENT_DRIVER_BRANCH 0

/* Misc defines */
#घोषणा TW_SECTOR_SIZE			      512
#घोषणा TW_MAX_UNITS			      32
#घोषणा TW_INIT_MESSAGE_CREDITS		      0x100
#घोषणा TW_INIT_COMMAND_PACKET_SIZE	      0x3
#घोषणा TW_INIT_COMMAND_PACKET_SIZE_EXTENDED  0x6
#घोषणा TW_EXTENDED_INIT_CONNECT	      0x2
#घोषणा TW_BASE_FW_SRL			      24
#घोषणा TW_BASE_FW_BRANCH		      0
#घोषणा TW_BASE_FW_BUILD		      1
#घोषणा TW_Q_LENGTH			      256
#घोषणा TW_Q_START			      0
#घोषणा TW_MAX_SLOT			      32
#घोषणा TW_MAX_RESET_TRIES		      2
#घोषणा TW_MAX_CMDS_PER_LUN		      254
#घोषणा TW_MAX_AEN_DRAIN		      255
#घोषणा TW_IN_RESET			      2
#घोषणा TW_USING_MSI			      3
#घोषणा TW_IN_ATTENTION_LOOP		      4
#घोषणा TW_MAX_SECTORS			      256
#घोषणा TW_MAX_CDB_LEN			      16
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
#घोषणा TW_PARAM_MODEL			      8
#घोषणा TW_PARAM_MODEL_LENGTH		      16
#घोषणा TW_PARAM_PHY_SUMMARY_TABLE	      1
#घोषणा TW_PARAM_PHYCOUNT		      2
#घोषणा TW_PARAM_PHYCOUNT_LENGTH	      1
#घोषणा TW_IOCTL_FIRMWARE_PASS_THROUGH	      0x108  // Used by smarपंचांगontools
#घोषणा TW_ALLOCATION_LENGTH		      128
#घोषणा TW_SENSE_DATA_LENGTH		      18
#घोषणा TW_ERROR_LOGICAL_UNIT_NOT_SUPPORTED   0x10a
#घोषणा TW_ERROR_INVALID_FIELD_IN_CDB	      0x10d
#घोषणा TW_ERROR_UNIT_OFFLINE		      0x128
#घोषणा TW_MESSAGE_SOURCE_CONTROLLER_ERROR    3
#घोषणा TW_MESSAGE_SOURCE_CONTROLLER_EVENT    4
#घोषणा TW_DRIVER			      6
#अगर_अघोषित PCI_DEVICE_ID_3WARE_9750
#घोषणा PCI_DEVICE_ID_3WARE_9750 0x1010
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

/* not_mfa: 1, reserved: 7, status: 8, request_id: 16 */
#घोषणा TW_RESID_OUT(x) ((x >> 16) & 0xffff)
#घोषणा TW_NOTMFA_OUT(x) (x & 0x1)

/* request_id: 12, lun: 4 */
#घोषणा TW_REQ_LUN_IN(lun, request_id)			\
	(((lun << 12) & 0xf000) | (request_id & 0xfff))
#घोषणा TW_LUN_OUT(lun) ((lun >> 12) & 0xf)

/* Register access macros */
#घोषणा TWL_STATUS_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_STATUS)
#घोषणा TWL_HOBQPL_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HOBQPL)
#घोषणा TWL_HOBQPH_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HOBQPH)
#घोषणा TWL_HOBDB_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HOBDB)
#घोषणा TWL_HOBDBC_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HOBDBC)
#घोषणा TWL_HIMASK_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HIMASK)
#घोषणा TWL_HISTAT_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HISTAT)
#घोषणा TWL_HIBQPH_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HIBQPH)
#घोषणा TWL_HIBQPL_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HIBQPL)
#घोषणा TWL_HIBDB_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_HIBDB)
#घोषणा TWL_SCRPD3_REG_ADDR(x)					\
	((अचिन्हित अक्षर __iomem *)x->base_addr + TWL_SCRPD3)
#घोषणा TWL_MASK_INTERRUPTS(x)					\
	(ग_लिखोl(~0, TWL_HIMASK_REG_ADDR(tw_dev)))
#घोषणा TWL_UNMASK_INTERRUPTS(x)				\
	(ग_लिखोl(~TWL_HISTATUS_VALID_INTERRUPT, TWL_HIMASK_REG_ADDR(tw_dev)))
#घोषणा TWL_CLEAR_DB_INTERRUPT(x)				\
	(ग_लिखोl(~0, TWL_HOBDBC_REG_ADDR(tw_dev)))
#घोषणा TWL_SOFT_RESET(x)					\
	(ग_लिखोl(TWL_ISSUE_SOFT_RESET, TWL_HIBDB_REG_ADDR(tw_dev)))

/* Macros */
#घोषणा TW_PRINTK(h,a,b,c) अणु \
अगर (h) \
prपूर्णांकk(KERN_WARNING "3w-sas: scsi%d: ERROR: (0x%02X:0x%04X): %s.\n",h->host_no,a,b,c); \
अन्यथा \
prपूर्णांकk(KERN_WARNING "3w-sas: ERROR: (0x%02X:0x%04X): %s.\n",a,b,c); \
पूर्ण
#घोषणा TW_MAX_LUNS 16
#घोषणा TW_COMMAND_SIZE (माप(dma_addr_t) > 4 ? 6 : 4)
#घोषणा TW_LIBERATOR_MAX_SGL_LENGTH (माप(dma_addr_t) > 4 ? 46 : 92)
#घोषणा TW_LIBERATOR_MAX_SGL_LENGTH_OLD (माप(dma_addr_t) > 4 ? 47 : 94)
#घोषणा TW_PADDING_LENGTH_LIBERATOR 136
#घोषणा TW_PADDING_LENGTH_LIBERATOR_OLD 132
#घोषणा TW_CPU_TO_SGL(x) (माप(dma_addr_t) > 4 ? cpu_to_le64(x) : cpu_to_le32(x))

#आशय pack(1)

/* SGL entry */
प्रकार काष्ठा TAG_TW_SG_Entry_ISO अणु
	dma_addr_t address;
	dma_addr_t length;
पूर्ण TW_SG_Entry_ISO;

/* Old Command Packet with ISO SGL */
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
			TW_SG_Entry_ISO sgl[TW_LIBERATOR_MAX_SGL_LENGTH_OLD];
			अचिन्हित अक्षर padding[TW_PADDING_LENGTH_LIBERATOR_OLD];
		पूर्ण io;
		काष्ठा अणु
			TW_SG_Entry_ISO sgl[TW_LIBERATOR_MAX_SGL_LENGTH_OLD];
			u32 padding;
			अचिन्हित अक्षर padding2[TW_PADDING_LENGTH_LIBERATOR_OLD];
		पूर्ण param;
	पूर्ण byte8_offset;
पूर्ण TW_Command;

/* New Command Packet with ISO SGL */
प्रकार काष्ठा TAG_TW_Command_Apache अणु
	अचिन्हित अक्षर opcode__reserved;
	अचिन्हित अक्षर unit;
	अचिन्हित लघु request_id__lunl;
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर sgl_offset;
	अचिन्हित लघु sgl_entries__lunh;
	अचिन्हित अक्षर cdb[16];
	TW_SG_Entry_ISO sg_list[TW_LIBERATOR_MAX_SGL_LENGTH];
	अचिन्हित अक्षर padding[TW_PADDING_LENGTH_LIBERATOR];
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
		अचिन्हित लघु request_id;
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

/* GetParam descriptor */
प्रकार काष्ठा अणु
	अचिन्हित लघु	table_id;
	अचिन्हित लघु	parameter_id;
	अचिन्हित लघु	parameter_size_bytes;
	अचिन्हित लघु  actual_parameter_size_bytes;
	अचिन्हित अक्षर	data[1];
पूर्ण TW_Param_Apache;

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
	व्योम			__iomem *base_addr;
	अचिन्हित दीर्घ		*generic_buffer_virt[TW_Q_LENGTH];
	dma_addr_t		generic_buffer_phys[TW_Q_LENGTH];
	TW_Command_Full		*command_packet_virt[TW_Q_LENGTH];
	dma_addr_t		command_packet_phys[TW_Q_LENGTH];
	TW_Command_Apache_Header *sense_buffer_virt[TW_Q_LENGTH];
	dma_addr_t		sense_buffer_phys[TW_Q_LENGTH];
	काष्ठा pci_dev		*tw_pci_dev;
	काष्ठा scsi_cmnd	*srb[TW_Q_LENGTH];
	अचिन्हित अक्षर		मुक्त_queue[TW_Q_LENGTH];
	अचिन्हित अक्षर		मुक्त_head;
	अचिन्हित अक्षर		मुक्त_tail;
	पूर्णांक			state[TW_Q_LENGTH];
	अचिन्हित पूर्णांक		posted_request_count;
	अचिन्हित पूर्णांक		max_posted_request_count;
	अचिन्हित पूर्णांक		max_sgl_entries;
	अचिन्हित पूर्णांक		sgl_entries;
	अचिन्हित पूर्णांक		num_resets;
	अचिन्हित पूर्णांक		sector_count;
	अचिन्हित पूर्णांक		max_sector_count;
	अचिन्हित पूर्णांक		aen_count;
	काष्ठा Scsi_Host	*host;
	दीर्घ			flags;
	TW_Event		*event_queue[TW_Q_LENGTH];
	अचिन्हित अक्षर		error_index;
	अचिन्हित पूर्णांक		error_sequence_id;
	पूर्णांक			chrdev_request_id;
	रुको_queue_head_t	ioctl_wqueue;
	काष्ठा mutex		ioctl_lock;
	TW_Compatibility_Info	tw_compat_info;
	अक्षर			online;
पूर्ण TW_Device_Extension;

#पूर्ण_अगर /* _3W_SAS_H */

