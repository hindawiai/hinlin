<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptbase.h
 *      High perक्रमmance SCSI + LAN / Fibre Channel device drivers.
 *      For use with PCI chip/adapter(s):
 *          LSIFC9xx/LSI409xx Fibre Channel
 *      running LSI Fusion MPT (Message Passing Technology) firmware.
 *
 *  Copyright (c) 1999-2008 LSI Corporation
 *  (mailto:DL-MPTFusionLinux@lsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
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
*/

#अगर_अघोषित MPTBASE_H_INCLUDED
#घोषणा MPTBASE_H_INCLUDED
/*अणु-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>

#समावेश "lsi/mpi_type.h"
#समावेश "lsi/mpi.h"		/* Fusion MPI(nterface) basic defs */
#समावेश "lsi/mpi_ioc.h"	/* Fusion MPT IOC(ontroller) defs */
#समावेश "lsi/mpi_cnfg.h"	/* IOC configuration support */
#समावेश "lsi/mpi_init.h"	/* SCSI Host (initiator) protocol support */
#समावेश "lsi/mpi_lan.h"	/* LAN over FC protocol support */
#समावेश "lsi/mpi_raid.h"	/* Integrated Mirroring support */

#समावेश "lsi/mpi_fc.h"		/* Fibre Channel (lowlevel) support */
#समावेश "lsi/mpi_targ.h"	/* SCSI/FCP Target protcol support */
#समावेश "lsi/mpi_tool.h"	/* Tools support */
#समावेश "lsi/mpi_sas.h"	/* SAS support */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#अगर_अघोषित MODULEAUTHOR
#घोषणा MODULEAUTHOR	"LSI Corporation"
#पूर्ण_अगर

#अगर_अघोषित COPYRIGHT
#घोषणा COPYRIGHT	"Copyright (c) 1999-2008 " MODULEAUTHOR
#पूर्ण_अगर

#घोषणा MPT_LINUX_VERSION_COMMON	"3.04.20"
#घोषणा MPT_LINUX_PACKAGE_NAME		"@(#)mptlinux-3.04.20"
#घोषणा WHAT_MAGIC_STRING		"@" "(" "#" ")"

#घोषणा show_mpपंचांगod_ver(s,ver)  \
	prपूर्णांकk(KERN_INFO "%s %s\n", s, ver);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Fusion MPT(linux) driver configurable stuff...
 */
#घोषणा MPT_MAX_ADAPTERS		18
#घोषणा MPT_MAX_PROTOCOL_DRIVERS	16
#घोषणा MPT_MAX_CALLBACKNAME_LEN	49
#घोषणा MPT_MAX_BUS			1	/* Do not change */
#घोषणा MPT_MAX_FC_DEVICES		255
#घोषणा MPT_MAX_SCSI_DEVICES		16
#घोषणा MPT_LAST_LUN			255
#घोषणा MPT_SENSE_BUFFER_ALLOC		64
	/* allow क्रम 256 max sense alloc, but only 255 max request */
#अगर MPT_SENSE_BUFFER_ALLOC >= 256
#	undef MPT_SENSE_BUFFER_ALLOC
#	define MPT_SENSE_BUFFER_ALLOC	256
#	define MPT_SENSE_BUFFER_SIZE	255
#अन्यथा
#	define MPT_SENSE_BUFFER_SIZE	MPT_SENSE_BUFFER_ALLOC
#पूर्ण_अगर

#घोषणा MPT_NAME_LENGTH			32
#घोषणा MPT_KOBJ_NAME_LEN		20

#घोषणा MPT_PROCFS_MPTBASEसूची		"mpt"
						/* chg it to "driver/fusion" ? */
#घोषणा MPT_PROCFS_SUMMARY_ALL_NODE		MPT_PROCFS_MPTBASEसूची "/summary"
#घोषणा MPT_PROCFS_SUMMARY_ALL_PATHNAME		"/proc/" MPT_PROCFS_SUMMARY_ALL_NODE
#घोषणा MPT_FW_REV_MAGIC_ID_STRING		"FwRev="

#घोषणा  MPT_MAX_REQ_DEPTH		1023
#घोषणा  MPT_DEFAULT_REQ_DEPTH		256
#घोषणा  MPT_MIN_REQ_DEPTH		128

#घोषणा  MPT_MAX_REPLY_DEPTH		MPT_MAX_REQ_DEPTH
#घोषणा  MPT_DEFAULT_REPLY_DEPTH	128
#घोषणा  MPT_MIN_REPLY_DEPTH		8
#घोषणा  MPT_MAX_REPLIES_PER_ISR	32

#घोषणा  MPT_MAX_FRAME_SIZE		128
#घोषणा  MPT_DEFAULT_FRAME_SIZE		128

#घोषणा  MPT_REPLY_FRAME_SIZE		0x50  /* Must be a multiple of 8 */

#घोषणा  MPT_SG_REQ_128_SCALE		1
#घोषणा  MPT_SG_REQ_96_SCALE		2
#घोषणा  MPT_SG_REQ_64_SCALE		4

#घोषणा	 CAN_SLEEP			1
#घोषणा  NO_SLEEP			0

#घोषणा MPT_COALESCING_TIMEOUT		0x10


/*
 * SCSI transfer rate defines.
 */
#घोषणा MPT_ULTRA320			0x08
#घोषणा MPT_ULTRA160			0x09
#घोषणा MPT_ULTRA2			0x0A
#घोषणा MPT_ULTRA			0x0C
#घोषणा MPT_FAST			0x19
#घोषणा MPT_SCSI			0x32
#घोषणा MPT_ASYNC			0xFF

#घोषणा MPT_NARROW			0
#घोषणा MPT_WIDE			1

#घोषणा C0_1030				0x08
#घोषणा XL_929				0x01


/*
 *	Try to keep these at 2^N-1
 */
#घोषणा MPT_FC_CAN_QUEUE	1024
#घोषणा MPT_SCSI_CAN_QUEUE	127
#घोषणा MPT_SAS_CAN_QUEUE	127

/*
 * Set the MAX_SGE value based on user input.
 */
#अगर_घोषित CONFIG_FUSION_MAX_SGE
#अगर CONFIG_FUSION_MAX_SGE  < 16
#घोषणा MPT_SCSI_SG_DEPTH	16
#या_अगर CONFIG_FUSION_MAX_SGE  > 128
#घोषणा MPT_SCSI_SG_DEPTH	128
#अन्यथा
#घोषणा MPT_SCSI_SG_DEPTH	CONFIG_FUSION_MAX_SGE
#पूर्ण_अगर
#अन्यथा
#घोषणा MPT_SCSI_SG_DEPTH	40
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUSION_MAX_FC_SGE
#अगर CONFIG_FUSION_MAX_FC_SGE  < 16
#घोषणा MPT_SCSI_FC_SG_DEPTH	16
#या_अगर CONFIG_FUSION_MAX_FC_SGE  > 256
#घोषणा MPT_SCSI_FC_SG_DEPTH	256
#अन्यथा
#घोषणा MPT_SCSI_FC_SG_DEPTH	CONFIG_FUSION_MAX_FC_SGE
#पूर्ण_अगर
#अन्यथा
#घोषणा MPT_SCSI_FC_SG_DEPTH	40
#पूर्ण_अगर

/* debug prपूर्णांक string length used क्रम events and iocstatus */
# define EVENT_DESCR_STR_SZ             100

#घोषणा MPT_POLLING_INTERVAL		1000	/* in milliseconds */

#अगर_घोषित __KERNEL__	/* अणु */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश <linux/proc_fs.h>

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * Attempt semi-consistent error & warning msgs across
 * MPT drivers.  NOTE: Users of these macro defs must
 * themselves define their own MYNAM.
 */
#घोषणा MYIOC_s_FMT			MYNAM ": %s: "
#घोषणा MYIOC_s_DEBUG_FMT		KERN_DEBUG MYNAM ": %s: "
#घोषणा MYIOC_s_INFO_FMT		KERN_INFO MYNAM ": %s: "
#घोषणा MYIOC_s_NOTE_FMT		KERN_NOTICE MYNAM ": %s: "
#घोषणा MYIOC_s_WARN_FMT		KERN_WARNING MYNAM ": %s: WARNING - "
#घोषणा MYIOC_s_ERR_FMT			KERN_ERR MYNAM ": %s: ERROR - "

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  ATTO UL4D associated काष्ठाures and defines
 */
#घोषणा ATTOFLAG_DISC     0x0001
#घोषणा ATTOFLAG_TAGGED   0x0002
#घोषणा ATTOFLAG_WIDE_ENB 0x0008
#घोषणा ATTOFLAG_ID_ENB   0x0010
#घोषणा ATTOFLAG_LUN_ENB  0x0060

प्रकार काष्ठा _ATTO_DEVICE_INFO
अणु
	u8	Offset;					/* 00h */
	u8	Period;					/* 01h */
	u16	ATTOFlags;				/* 02h */
पूर्ण ATTO_DEVICE_INFO, MPI_POINTER PTR_ATTO_DEVICE_INFO,
  ATTODeviceInfo_t, MPI_POINTER pATTODeviceInfo_t;

प्रकार काष्ठा _ATTO_CONFIG_PAGE_SCSI_PORT_2
अणु
	CONFIG_PAGE_HEADER	Header;			/* 00h */
	u16			PortFlags;		/* 04h */
	u16			Unused1;		/* 06h */
	u32			Unused2;		/* 08h */
	ATTO_DEVICE_INFO	DeviceSettings[16];	/* 0Ch */
पूर्ण fATTO_CONFIG_PAGE_SCSI_PORT_2, MPI_POINTER PTR_ATTO_CONFIG_PAGE_SCSI_PORT_2,
  ATTO_SCSIPortPage2_t, MPI_POINTER pATTO_SCSIPortPage2_t;


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  MPT protocol driver defs...
 */
प्रकार क्रमागत अणु
	MPTBASE_DRIVER,		/* MPT base class */
	MPTCTL_DRIVER,		/* MPT ioctl class */
	MPTSPI_DRIVER,		/* MPT SPI host class */
	MPTFC_DRIVER,		/* MPT FC host class */
	MPTSAS_DRIVER,		/* MPT SAS host class */
	MPTLAN_DRIVER,		/* MPT LAN class */
	MPTSTM_DRIVER,		/* MPT SCSI target mode class */
	MPTUNKNOWN_DRIVER
पूर्ण MPT_DRIVER_CLASS;

काष्ठा mpt_pci_driverअणु
	पूर्णांक  (*probe) (काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id);
	व्योम (*हटाओ) (काष्ठा pci_dev *dev);
पूर्ण;

/*
 *  MPT adapter / port / bus / device info काष्ठाures...
 */

प्रकार जोड़ _MPT_FRAME_TRACKER अणु
	काष्ठा अणु
		काष्ठा list_head	list;
		u32			 arg1;
		u32			 pad;
		व्योम			*argp1;
	पूर्ण linkage;
	/*
	 * NOTE: When request frames are मुक्त, on the linkage काष्ठाure
	 * contents are valid.  All other values are invalid.
	 * In particular, करो NOT reply on offset [2]
	 * (in words) being the * message context.
	 * The message context must be reset (computed via base address
	 * + an offset) prior to issuing any command.
	 *
	 * NOTE2: On non-32-bit प्रणालीs, where poपूर्णांकers are LARGE,
	 * using the linkage poपूर्णांकers destroys our sacred MsgContext
	 * field contents.  But we करोn't care anymore because these
	 * are now reset in mpt_put_msg_frame() just prior to sending
	 * a request off to the IOC.
	 */
	काष्ठा अणु
		u32 __hdr[2];
		/*
		 * The following _MUST_ match the location of the
		 * MsgContext field in the MPT message headers.
		 */
		जोड़ अणु
			u32		 MsgContext;
			काष्ठा अणु
				u16	 req_idx;	/* Request index */
				u8	 cb_idx;	/* callback function index */
				u8	 rsvd;
			पूर्ण fld;
		पूर्ण msgctxu;
	पूर्ण hwhdr;
	/*
	 * Remark: 32 bit identअगरier:
	 *  31-24: reserved
	 *  23-16: call back index
	 *  15-0 : request index
	 */
पूर्ण MPT_FRAME_TRACKER;

/*
 *  We might want to view/access a frame as:
 *    1) generic request header
 *    2) SCSIIORequest
 *    3) SCSIIOReply
 *    4) MPIDefaultReply
 *    5) frame tracker
 */
प्रकार काष्ठा _MPT_FRAME_HDR अणु
	जोड़ अणु
		MPIHeader_t		hdr;
		SCSIIORequest_t		scsireq;
		SCSIIOReply_t		sreply;
		ConfigReply_t		configreply;
		MPIDefaultReply_t	reply;
		MPT_FRAME_TRACKER	frame;
	पूर्ण u;
पूर्ण MPT_FRAME_HDR;

#घोषणा MPT_REQ_MSGFLAGS_DROPME		0x80

प्रकार काष्ठा _MPT_SGL_HDR अणु
	SGESimple32_t	 sge[1];
पूर्ण MPT_SGL_HDR;

प्रकार काष्ठा _MPT_SGL64_HDR अणु
	SGESimple64_t	 sge[1];
पूर्ण MPT_SGL64_HDR;

/*
 *  System पूर्णांकerface रेजिस्टर set
 */

प्रकार काष्ठा _SYSIF_REGS
अणु
	u32	Doorbell;	/* 00     System<->IOC Doorbell reg  */
	u32	WriteSequence;	/* 04     Write Sequence रेजिस्टर    */
	u32	Diagnostic;	/* 08     Diagnostic रेजिस्टर        */
	u32	TestBase;	/* 0C     Test Base Address          */
	u32	DiagRwData;	/* 10     Read Write Data (fw करोwnload)   */
	u32	DiagRwAddress;	/* 14     Read Write Address (fw करोwnload)*/
	u32	Reserved1[6];	/* 18-2F  reserved क्रम future use    */
	u32	IntStatus;	/* 30     Interrupt Status           */
	u32	IntMask;	/* 34     Interrupt Mask             */
	u32	Reserved2[2];	/* 38-3F  reserved क्रम future use    */
	u32	RequestFअगरo;	/* 40     Request Post/Free FIFO     */
	u32	ReplyFअगरo;	/* 44     Reply   Post/Free FIFO     */
	u32	RequestHiPriFअगरo; /* 48   Hi Priority Request FIFO   */
	u32	Reserved3;	/* 4C-4F  reserved क्रम future use    */
	u32	HostIndex;	/* 50     Host Index रेजिस्टर        */
	u32	Reserved4[15];	/* 54-8F                             */
	u32	Fubar;		/* 90     For Fubar usage            */
	u32	Reserved5[1050];/* 94-10F8                           */
	u32	Reset_1078;	/* 10FC   Reset 1078                 */
पूर्ण SYSIF_REGS;

/*
 * NOTE: Use MPI_अणुDOORBELL,WRITESEQ,DIAGपूर्ण_xxx defs in lsi/mpi.h
 * in conjunction with SYSIF_REGS accesses!
 */


/*
 *	Dynamic Multi-Pathing specअगरic stuff...
 */

/* VirtTarget negoFlags field */
#घोषणा MPT_TARGET_NO_NEGO_WIDE		0x01
#घोषणा MPT_TARGET_NO_NEGO_SYNC		0x02
#घोषणा MPT_TARGET_NO_NEGO_QAS		0x04
#घोषणा MPT_TAPE_NEGO_IDP     		0x08

/*
 *	VirtDevice - FC LUN device or SCSI target device
 */
प्रकार काष्ठा _VirtTarget अणु
	काष्ठा scsi_target	*starget;
	u8			 tflags;
	u8			 ioc_id;
	u8			 id;
	u8			 channel;
	u8			 minSyncFactor;	/* 0xFF is async */
	u8			 maxOffset;	/* 0 अगर async */
	u8			 maxWidth;	/* 0 अगर narrow, 1 अगर wide */
	u8			 negoFlags;	/* bit field, see above */
	u8			 raidVolume;	/* set, अगर RAID Volume */
	u8			 type;		/* byte 0 of Inquiry data */
	u8			 deleted;	/* target in process of being हटाओd */
	u8			 inDMD;		/* currently in the device
						   removal delay समयr */
	u32			 num_luns;
पूर्ण VirtTarget;

प्रकार काष्ठा _VirtDevice अणु
	VirtTarget		*vtarget;
	u8			 configured_lun;
	u64			 lun;
पूर्ण VirtDevice;

/*
 *  Fibre Channel (SCSI) target device and associated defines...
 */
#घोषणा MPT_TARGET_DEFAULT_DV_STATUS	0x00
#घोषणा MPT_TARGET_FLAGS_VALID_NEGO	0x01
#घोषणा MPT_TARGET_FLAGS_VALID_INQUIRY	0x02
#घोषणा MPT_TARGET_FLAGS_Q_YES		0x08
#घोषणा MPT_TARGET_FLAGS_VALID_56	0x10
#घोषणा MPT_TARGET_FLAGS_SAF_TE_ISSUED	0x20
#घोषणा MPT_TARGET_FLAGS_RAID_COMPONENT	0x40
#घोषणा MPT_TARGET_FLAGS_LED_ON		0x80

/*
 *	IOCTL काष्ठाure and associated defines
 */

#घोषणा MPTCTL_RESET_OK			0x01	/* Issue Bus Reset */

#घोषणा MPT_MGMT_STATUS_RF_VALID	0x01	/* The Reply Frame is VALID */
#घोषणा MPT_MGMT_STATUS_COMMAND_GOOD	0x02	/* Command Status GOOD */
#घोषणा MPT_MGMT_STATUS_PENDING		0x04	/* command is pending */
#घोषणा MPT_MGMT_STATUS_DID_IOCRESET	0x08	/* IOC Reset occurred
						   on the current*/
#घोषणा MPT_MGMT_STATUS_SENSE_VALID	0x10	/* valid sense info */
#घोषणा MPT_MGMT_STATUS_TIMER_ACTIVE	0x20	/* obsolete */
#घोषणा MPT_MGMT_STATUS_FREE_MF		0x40	/* मुक्त the mf from
						   complete routine */

#घोषणा INITIALIZE_MGMT_STATUS(status) \
	status = MPT_MGMT_STATUS_PENDING;
#घोषणा CLEAR_MGMT_STATUS(status) \
	status = 0;
#घोषणा CLEAR_MGMT_PENDING_STATUS(status) \
	status &= ~MPT_MGMT_STATUS_PENDING;
#घोषणा SET_MGMT_MSG_CONTEXT(msg_context, value) \
	msg_context = value;

प्रकार काष्ठा _MPT_MGMT अणु
	काष्ठा mutex		 mutex;
	काष्ठा completion	 करोne;
	u8			 reply[MPT_DEFAULT_FRAME_SIZE]; /* reply frame data */
	u8			 sense[MPT_SENSE_BUFFER_ALLOC];
	u8			 status;	/* current command status */
	पूर्णांक			 completion_code;
	u32			 msg_context;
पूर्ण MPT_MGMT;

/*
 *  Event Structure and define
 */
#घोषणा MPTCTL_EVENT_LOG_SIZE		(0x000000032)
प्रकार काष्ठा _mpt_ioctl_events अणु
	u32	event;		/* Specअगरied by define above */
	u32	eventContext;	/* Index or counter */
	u32	data[2];	/* First 8 bytes of Event Data */
पूर्ण MPT_IOCTL_EVENTS;

/*
 * CONFIGPARM status  defines
 */
#घोषणा MPT_CONFIG_GOOD		MPI_IOCSTATUS_SUCCESS
#घोषणा MPT_CONFIG_ERROR	0x002F

/*
 *	Subकाष्ठाure to store SCSI specअगरic configuration page data
 */
						/* dvStatus defines: */
#घोषणा MPT_SCSICFG_USE_NVRAM		0x01	/* WriteSDP1 using NVRAM */
#घोषणा MPT_SCSICFG_ALL_IDS		0x02	/* WriteSDP1 to all IDS */
/* #घोषणा MPT_SCSICFG_BLK_NEGO		0x10	   WriteSDP1 with WDTR and SDTR disabled */

प्रकार	काष्ठा _SpiCfgData अणु
	u32		 PortFlags;
	पूर्णांक		*nvram;			/* table of device NVRAM values */
	IOCPage4_t	*pIocPg4;		/* SEP devices addressing */
	dma_addr_t	 IocPg4_dma;		/* Phys Addr of IOCPage4 data */
	पूर्णांक		 IocPg4Sz;		/* IOCPage4 size */
	u8		 minSyncFactor;		/* 0xFF अगर async */
	u8		 maxSyncOffset;		/* 0 अगर async */
	u8		 maxBusWidth;		/* 0 अगर narrow, 1 अगर wide */
	u8		 busType;		/* SE, LVD, HD */
	u8		 sdp1version;		/* SDP1 version */
	u8		 sdp1length;		/* SDP1 length  */
	u8		 sdp0version;		/* SDP0 version */
	u8		 sdp0length;		/* SDP0 length  */
	u8		 dvScheduled;		/* 1 अगर scheduled */
	u8		 noQas;			/* Disable QAS क्रम this adapter */
	u8		 Saf_Te;		/* 1 to क्रमce all Processors as
						 * SAF-TE अगर Inquiry data length
						 * is too लघु to check क्रम SAF-TE
						 */
	u8		 bus_reset;		/* 1 to allow bus reset */
	u8		 rsvd[1];
पूर्णSpiCfgData;

प्रकार	काष्ठा _SasCfgData अणु
	u8		 ptClear;		/* 1 to स्वतःmatically clear the
						 * persistent table.
						 * 0 to disable
						 * स्वतःmatic clearing.
						 */
पूर्णSasCfgData;

/*
 * Inactive volume link list of raid component data
 * @inactive_list
 */
काष्ठा inactive_raid_component_info अणु
	काष्ठा 	 list_head list;
	u8		 volumeID;		/* volume target id */
	u8		 volumeBus;		/* volume channel */
	IOC_3_PHYS_DISK	 d;			/* phys disk info */
पूर्ण;

प्रकार	काष्ठा _RaidCfgData अणु
	IOCPage2_t	*pIocPg2;		/* table of Raid Volumes */
	IOCPage3_t	*pIocPg3;		/* table of physical disks */
	काष्ठा mutex	inactive_list_mutex;
	काष्ठा list_head	inactive_list; /* link list क्रम physical
						disk that beदीर्घ in
						inactive volumes */
पूर्णRaidCfgData;

प्रकार काष्ठा _FcCfgData अणु
	/* will ultimately hold fc_port_page0 also */
	काष्ठा अणु
		FCPortPage1_t	*data;
		dma_addr_t	 dma;
		पूर्णांक		 pg_sz;
	पूर्ण			 fc_port_page1[2];
पूर्ण FcCfgData;

#घोषणा MPT_RPORT_INFO_FLAGS_REGISTERED	0x01	/* rport रेजिस्टरed */
#घोषणा MPT_RPORT_INFO_FLAGS_MISSING	0x02	/* missing from DevPage0 scan */

/*
 * data allocated क्रम each fc rport device
 */
काष्ठा mptfc_rport_info
अणु
	काष्ठा list_head list;
	काष्ठा fc_rport *rport;
	काष्ठा scsi_target *starget;
	FCDevicePage0_t pg0;
	u8		flags;
पूर्ण;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

/*
 * MPT_SCSI_HOST defines - Used by the IOCTL and the SCSI drivers
 * Private to the driver.
 */

#घोषणा MPT_HOST_BUS_UNKNOWN		(0xFF)
#घोषणा MPT_HOST_TOO_MANY_TM		(0x05)
#घोषणा MPT_HOST_NVRAM_INVALID		(0xFFFFFFFF)
#घोषणा MPT_HOST_NO_CHAIN		(0xFFFFFFFF)
#घोषणा MPT_NVRAM_MASK_TIMEOUT		(0x000000FF)
#घोषणा MPT_NVRAM_SYNC_MASK		(0x0000FF00)
#घोषणा MPT_NVRAM_SYNC_SHIFT		(8)
#घोषणा MPT_NVRAM_DISCONNECT_ENABLE	(0x00010000)
#घोषणा MPT_NVRAM_ID_SCAN_ENABLE	(0x00020000)
#घोषणा MPT_NVRAM_LUN_SCAN_ENABLE	(0x00040000)
#घोषणा MPT_NVRAM_TAG_QUEUE_ENABLE	(0x00080000)
#घोषणा MPT_NVRAM_WIDE_DISABLE		(0x00100000)
#घोषणा MPT_NVRAM_BOOT_CHOICE		(0x00200000)

प्रकार क्रमागत अणु
	FC,
	SPI,
	SAS
पूर्ण BUS_TYPE;

प्रकार काष्ठा _MPT_SCSI_HOST अणु
	काष्ठा _MPT_ADAPTER		 *ioc;
	uलघु			  sel_समयout[MPT_MAX_FC_DEVICES];
	अक्षर			  *info_kbuf;
	दीर्घ			  last_queue_full;
	u16			  spi_pending;
	काष्ठा list_head	  target_reset_list;
पूर्ण MPT_SCSI_HOST;

प्रकार व्योम (*MPT_ADD_SGE)(व्योम *pAddr, u32 flagslength, dma_addr_t dma_addr);
प्रकार व्योम (*MPT_ADD_CHAIN)(व्योम *pAddr, u8 next, u16 length,
		dma_addr_t dma_addr);
प्रकार व्योम (*MPT_SCHEDULE_TARGET_RESET)(व्योम *ioc);
प्रकार व्योम (*MPT_FLUSH_RUNNING_CMDS)(MPT_SCSI_HOST *hd);

/*
 *  Adapter Structure - pci_dev specअगरic. Maximum: MPT_MAX_ADAPTERS
 */
प्रकार काष्ठा _MPT_ADAPTER
अणु
	पूर्णांक			 id;		/* Unique adapter id N अणु0,1,2,...पूर्ण */
	पूर्णांक			 pci_irq;	/* This irq           */
	अक्षर			 name[MPT_NAME_LENGTH];	/* "iocN"             */
	स्थिर अक्षर		 *prod_name;	/* "LSIFC9x9"         */
#अगर_घोषित CONFIG_FUSION_LOGGING
	/* used in mpt_display_event_info */
	अक्षर			 evStr[EVENT_DESCR_STR_SZ];
#पूर्ण_अगर
	अक्षर			 board_name[16];
	अक्षर			 board_assembly[16];
	अक्षर			 board_tracer[16];
	u16			 nvdata_version_persistent;
	u16			 nvdata_version_शेष;
	पूर्णांक			 debug_level;
	u8			 io_missing_delay;
	u16			 device_missing_delay;
	SYSIF_REGS __iomem	*chip;		/* == c8817000 (mmap) */
	SYSIF_REGS __iomem	*pio_chip;	/* Programmed IO (करोwnloadboot) */
	u8			 bus_type;
	u32			 mem_phys;	/* == f4020000 (mmap) */
	u32			 pio_mem_phys;	/* Programmed IO (करोwnloadboot) */
	पूर्णांक			 mem_size;	/* mmap memory size */
	पूर्णांक			 number_of_buses;
	पूर्णांक			 devices_per_bus;
	पूर्णांक			 alloc_total;
	u32			 last_state;
	पूर्णांक			 active;
	u8			*alloc;		/* frames alloc ptr */
	dma_addr_t		 alloc_dma;
	u32			 alloc_sz;
	MPT_FRAME_HDR		*reply_frames;	/* Reply msg frames - rounded up! */
	u32			 reply_frames_low_dma;
	पूर्णांक			 reply_depth;	/* Num Allocated reply frames */
	पूर्णांक			 reply_sz;	/* Reply frame size */
	पूर्णांक			 num_chain;	/* Number of chain buffers */
	MPT_ADD_SGE              add_sge;       /* Poपूर्णांकer to add_sge
						   function */
	MPT_ADD_CHAIN		 add_chain;	/* Poपूर्णांकer to add_chain
						   function */
		/* Pool of buffers क्रम chaining. ReqToChain
		 * and ChainToChain track index of chain buffers.
		 * ChainBuffer (DMA) virt/phys addresses.
		 * FreeChainQ (lock) locking mechanisms.
		 */
	पूर्णांक			*ReqToChain;
	पूर्णांक			*RequestNB;
	पूर्णांक			*ChainToChain;
	u8			*ChainBuffer;
	dma_addr_t		 ChainBufferDMA;
	काष्ठा list_head	 FreeChainQ;
	spinlock_t		 FreeChainQlock;
		/* We (host driver) get to manage our own RequestQueue! */
	dma_addr_t		 req_frames_dma;
	MPT_FRAME_HDR		*req_frames;	/* Request msg frames - rounded up! */
	u32			 req_frames_low_dma;
	पूर्णांक			 req_depth;	/* Number of request frames */
	पूर्णांक			 req_sz;	/* Request frame size (bytes) */
	spinlock_t		 FreeQlock;
	काष्ठा list_head	 FreeQ;
		/* Pool of SCSI sense buffers क्रम commands coming from
		 * the SCSI mid-layer.  We have one 256 byte sense buffer
		 * क्रम each REQ entry.
		 */
	u8			*sense_buf_pool;
	dma_addr_t		 sense_buf_pool_dma;
	u32			 sense_buf_low_dma;
	u8			*HostPageBuffer; /* SAS - host page buffer support */
	u32			HostPageBuffer_sz;
	dma_addr_t		HostPageBuffer_dma;
	काष्ठा pci_dev		*pcidev;	/* काष्ठा pci_dev poपूर्णांकer */
	पूर्णांक			bars;		/* biपंचांगask of BAR's that must be configured */
	पूर्णांक			msi_enable;
	u8			__iomem *memmap;	/* mmap address */
	काष्ठा Scsi_Host	*sh;		/* Scsi Host poपूर्णांकer */
	SpiCfgData		spi_data;	/* Scsi config. data */
	RaidCfgData		raid_data;	/* Raid config. data */
	SasCfgData		sas_data;	/* Sas config. data */
	FcCfgData		fc_data;	/* Fc config. data */
	काष्ठा proc_dir_entry	*ioc_dentry;
	काष्ठा _MPT_ADAPTER	*alt_ioc;	/* ptr to 929 bound adapter port */
	u32			 biosVersion;	/* BIOS version from IO Unit Page 2 */
	पूर्णांक			 eventTypes;	/* Event logging parameters */
	पूर्णांक			 eventContext;	/* Next event context */
	पूर्णांक			 eventLogSize;	/* Max number of cached events */
	काष्ठा _mpt_ioctl_events *events;	/* poपूर्णांकer to event log */
	u8			*cached_fw;	/* Poपूर्णांकer to FW */
	dma_addr_t	 	cached_fw_dma;
	पूर्णांक			 hs_reply_idx;
#अगर_अघोषित MFCNT
	u32			 pad0;
#अन्यथा
	u32			 mfcnt;
#पूर्ण_अगर
	u32			 NB_क्रम_64_byte_frame;
	u32			 hs_req[MPT_MAX_FRAME_SIZE/माप(u32)];
	u16			 hs_reply[MPT_MAX_FRAME_SIZE/माप(u16)];
	IOCFactsReply_t		 facts;
	PortFactsReply_t	 pfacts[2];
	FCPortPage0_t		 fc_port_page0[2];
	LANPage0_t		 lan_cnfg_page0;
	LANPage1_t		 lan_cnfg_page1;

	u8			 ir_firmware; /* =1 अगर IR firmware detected */
	/*
	 * Description: errata_flag_1064
	 * If a PCIX पढ़ो occurs within 1 or 2 cycles after the chip receives
	 * a split completion क्रम a पढ़ो data, an पूर्णांकernal address poपूर्णांकer incorrectly
	 * increments by 32 bytes
	 */
	पूर्णांक			 errata_flag_1064;
	पूर्णांक			 aen_event_पढ़ो_flag; /* flag to indicate event log was पढ़ो*/
	u8			 FirstWhoInit;
	u8			 upload_fw;	/* If set, करो a fw upload */
	u8			 NBShअगरtFactor;  /* NB Shअगरt Factor based on Block Size (Facts)  */
	u8			 pad1[4];
	u8			 DoneCtx;
	u8			 TaskCtx;
	u8			 InternalCtx;
	काष्ठा list_head	 list;
	काष्ठा net_device	*netdev;
	काष्ठा list_head	 sas_topology;
	काष्ठा mutex		 sas_topology_mutex;

	काष्ठा workqueue_काष्ठा	*fw_event_q;
	काष्ठा list_head	 fw_event_list;
	spinlock_t		 fw_event_lock;
	u8			 fw_events_off; /* अगर '1', then ignore events */
	अक्षर 			 fw_event_q_name[MPT_KOBJ_NAME_LEN];

	काष्ठा mutex		 sas_discovery_mutex;
	u8			 sas_discovery_runसमय;
	u8			 sas_discovery_ignore_events;

	/* port_info object क्रम the host */
	काष्ठा mptsas_portinfo	*hba_port_info;
	u64			 hba_port_sas_addr;
	u16			 hba_port_num_phy;
	काष्ठा list_head	 sas_device_info_list;
	काष्ठा mutex		 sas_device_info_mutex;
	u8			 old_sas_discovery_protocal;
	u8			 sas_discovery_quiesce_io;
	पूर्णांक			 sas_index; /* index refrencing */
	MPT_MGMT		 sas_mgmt;
	MPT_MGMT		 mptbase_cmds; /* क्रम sending config pages */
	MPT_MGMT		 पूर्णांकernal_cmds;
	MPT_MGMT		 taskmgmt_cmds;
	MPT_MGMT		 ioctl_cmds;
	spinlock_t		 taskmgmt_lock; /* diagnostic reset lock */
	पूर्णांक			 taskmgmt_in_progress;
	u8			 taskmgmt_quiesce_io;
	u8			 ioc_reset_in_progress;
	u8			 reset_status;
	u8			 रुको_on_reset_completion;
	MPT_SCHEDULE_TARGET_RESET schedule_target_reset;
	MPT_FLUSH_RUNNING_CMDS schedule_dead_ioc_flush_running_cmds;
	काष्ठा work_काष्ठा	 sas_persist_task;

	काष्ठा work_काष्ठा	 fc_setup_reset_work;
	काष्ठा list_head	 fc_rports;
	काष्ठा work_काष्ठा	 fc_lsc_work;
	u8			 fc_link_speed[2];
	spinlock_t		 fc_rescan_work_lock;
	काष्ठा work_काष्ठा	 fc_rescan_work;
	अक्षर			 fc_rescan_work_q_name[MPT_KOBJ_NAME_LEN];
	काष्ठा workqueue_काष्ठा *fc_rescan_work_q;

	/* driver क्रमced bus resets count */
	अचिन्हित दीर्घ		  hard_resets;
	/* fw/बाह्यal bus resets count */
	अचिन्हित दीर्घ		  soft_resets;
	/* cmd समयouts */
	अचिन्हित दीर्घ		  समयouts;

	काष्ठा scsi_cmnd	**ScsiLookup;
	spinlock_t		  scsi_lookup_lock;
	u64			dma_mask;
	u32			  broadcast_aen_busy;
	अक्षर			 reset_work_q_name[MPT_KOBJ_NAME_LEN];
	काष्ठा workqueue_काष्ठा *reset_work_q;
	काष्ठा delayed_work	 fault_reset_work;

	u8			sg_addr_size;
	u8			in_rescan;
	u8			SGE_size;

पूर्ण MPT_ADAPTER;

/*
 *  New वापस value convention:
 *    1 = Ok to मुक्त associated request frame
 *    0 = not Ok ...
 */
प्रकार पूर्णांक (*MPT_CALLBACK)(MPT_ADAPTER *ioc, MPT_FRAME_HDR *req, MPT_FRAME_HDR *reply);
प्रकार पूर्णांक (*MPT_EVHANDLER)(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *evReply);
प्रकार पूर्णांक (*MPT_RESETHANDLER)(MPT_ADAPTER *ioc, पूर्णांक reset_phase);
/* reset_phase defs */
#घोषणा MPT_IOC_PRE_RESET		0
#घोषणा MPT_IOC_POST_RESET		1
#घोषणा MPT_IOC_SETUP_RESET		2

/*
 * Invent MPT host event (super-set of MPI Events)
 * Fitted to 1030's 64-byte [max] request frame size
 */
प्रकार काष्ठा _MPT_HOST_EVENT अणु
	EventNotअगरicationReply_t	 MpiEvent;	/* 8 32-bit words! */
	u32				 pad[6];
	व्योम				*next;
पूर्ण MPT_HOST_EVENT;

#घोषणा MPT_HOSTEVENT_IOC_BRINGUP	0x91
#घोषणा MPT_HOSTEVENT_IOC_RECOVER	0x92

/* Define the generic types based on the size
 * of the dma_addr_t type.
 */
प्रकार काष्ठा _mpt_sge अणु
	u32		FlagsLength;
	dma_addr_t	Address;
पूर्ण MptSge_t;


#घोषणा mpt_msg_flags(ioc) \
	(ioc->sg_addr_size == माप(u64)) ?		\
	MPI_SCSIIO_MSGFLGS_SENSE_WIDTH_64 : 		\
	MPI_SCSIIO_MSGFLGS_SENSE_WIDTH_32

#घोषणा MPT_SGE_FLAGS_64_BIT_ADDRESSING \
	(MPI_SGE_FLAGS_64_BIT_ADDRESSING << MPI_SGE_FLAGS_SHIFT)

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Funky (निजी) macros...
 */
#समावेश "mptdebug.h"

#घोषणा MPT_INDEX_2_MFPTR(ioc,idx) \
	(MPT_FRAME_HDR*)( (u8*)(ioc)->req_frames + (ioc)->req_sz * (idx) )

#घोषणा MFPTR_2_MPT_INDEX(ioc,mf) \
	(पूर्णांक)( ((u8*)mf - (u8*)(ioc)->req_frames) / (ioc)->req_sz )

#घोषणा MPT_INDEX_2_RFPTR(ioc,idx) \
	(MPT_FRAME_HDR*)( (u8*)(ioc)->reply_frames + (ioc)->req_sz * (idx) )

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#घोषणा SCSI_STD_SENSE_BYTES    18
#घोषणा SCSI_STD_INQUIRY_BYTES  36
#घोषणा SCSI_MAX_INQUIRY_BYTES  96

/*
 * MPT_SCSI_HOST defines - Used by the IOCTL and the SCSI drivers
 * Private to the driver.
 */
/* LOCAL काष्ठाure and fields used when processing
 * पूर्णांकernally generated commands. These include:
 * bus scan, dv and config requests.
 */
प्रकार काष्ठा _MPT_LOCAL_REPLY अणु
	ConfigPageHeader_t header;
	पूर्णांक	completion;
	u8	sense[SCSI_STD_SENSE_BYTES];
	u8	scsiStatus;
	u8	skip;
	u32	pad;
पूर्ण MPT_LOCAL_REPLY;


/* The TM_STATE variable is used to provide strict single thपढ़ोing of TM
 * requests as well as communicate TM error conditions.
 */
#घोषणा TM_STATE_NONE          (0)
#घोषणा	TM_STATE_IN_PROGRESS   (1)
#घोषणा	TM_STATE_ERROR	       (2)

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	More Dynamic Multi-Pathing stuff...
 */

/* Forward decl, a strange C thing, to prevent gcc compiler warnings */
काष्ठा scsi_cmnd;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * Generic काष्ठाure passed to the base mpt_config function.
 */
प्रकार काष्ठा _x_config_parms अणु
	जोड़ अणु
		ConfigExtendedPageHeader_t	*ehdr;
		ConfigPageHeader_t	*hdr;
	पूर्ण cfghdr;
	dma_addr_t		 physAddr;
	u32			 pageAddr;	/* properly क्रमmatted */
	u16			 status;
	u8			 action;
	u8			 dir;
	u8			 समयout;	/* seconds */
पूर्ण CONFIGPARMS;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Public entry poपूर्णांकs...
 */
बाह्य पूर्णांक	 mpt_attach(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id);
बाह्य व्योम	 mpt_detach(काष्ठा pci_dev *pdev);
#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक	 mpt_suspend(काष्ठा pci_dev *pdev, pm_message_t state);
बाह्य पूर्णांक	 mpt_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर
बाह्य u8	 mpt_रेजिस्टर(MPT_CALLBACK cbfunc, MPT_DRIVER_CLASS dclass,
		अक्षर *func_name);
बाह्य व्योम	 mpt_deरेजिस्टर(u8 cb_idx);
बाह्य पूर्णांक	 mpt_event_रेजिस्टर(u8 cb_idx, MPT_EVHANDLER ev_cbfunc);
बाह्य व्योम	 mpt_event_deरेजिस्टर(u8 cb_idx);
बाह्य पूर्णांक	 mpt_reset_रेजिस्टर(u8 cb_idx, MPT_RESETHANDLER reset_func);
बाह्य व्योम	 mpt_reset_deरेजिस्टर(u8 cb_idx);
बाह्य पूर्णांक	 mpt_device_driver_रेजिस्टर(काष्ठा mpt_pci_driver * dd_cbfunc, u8 cb_idx);
बाह्य व्योम	 mpt_device_driver_deरेजिस्टर(u8 cb_idx);
बाह्य MPT_FRAME_HDR	*mpt_get_msg_frame(u8 cb_idx, MPT_ADAPTER *ioc);
बाह्य व्योम	 mpt_मुक्त_msg_frame(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf);
बाह्य व्योम	 mpt_put_msg_frame(u8 cb_idx, MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf);
बाह्य व्योम	 mpt_put_msg_frame_hi_pri(u8 cb_idx, MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf);

बाह्य पूर्णांक	 mpt_send_handshake_request(u8 cb_idx, MPT_ADAPTER *ioc, पूर्णांक reqBytes, u32 *req, पूर्णांक sleepFlag);
बाह्य पूर्णांक	 mpt_verअगरy_adapter(पूर्णांक iocid, MPT_ADAPTER **iocpp);
बाह्य u32	 mpt_GetIocState(MPT_ADAPTER *ioc, पूर्णांक cooked);
बाह्य व्योम	 mpt_prपूर्णांक_ioc_summary(MPT_ADAPTER *ioc, अक्षर *buf, पूर्णांक *size, पूर्णांक len, पूर्णांक showlan);
बाह्य पूर्णांक	 mpt_HardResetHandler(MPT_ADAPTER *ioc, पूर्णांक sleepFlag);
बाह्य पूर्णांक	 mpt_Soft_Hard_ResetHandler(MPT_ADAPTER *ioc, पूर्णांक sleepFlag);
बाह्य पूर्णांक	 mpt_config(MPT_ADAPTER *ioc, CONFIGPARMS *cfg);
बाह्य पूर्णांक	 mpt_alloc_fw_memory(MPT_ADAPTER *ioc, पूर्णांक size);
बाह्य व्योम	 mpt_मुक्त_fw_memory(MPT_ADAPTER *ioc);
बाह्य पूर्णांक	 mpt_findImVolumes(MPT_ADAPTER *ioc);
बाह्य पूर्णांक	 mptbase_sas_persist_operation(MPT_ADAPTER *ioc, u8 persist_opcode);
बाह्य पूर्णांक	 mpt_raid_phys_disk_pg0(MPT_ADAPTER *ioc, u8 phys_disk_num, pRaidPhysDiskPage0_t phys_disk);
बाह्य पूर्णांक	mpt_raid_phys_disk_pg1(MPT_ADAPTER *ioc, u8 phys_disk_num,
		pRaidPhysDiskPage1_t phys_disk);
बाह्य पूर्णांक	mpt_raid_phys_disk_get_num_paths(MPT_ADAPTER *ioc,
		u8 phys_disk_num);
बाह्य पूर्णांक	 mpt_set_taskmgmt_in_progress_flag(MPT_ADAPTER *ioc);
बाह्य व्योम	 mpt_clear_taskmgmt_in_progress_flag(MPT_ADAPTER *ioc);
बाह्य व्योम     mpt_halt_firmware(MPT_ADAPTER *ioc);


/*
 *  Public data decl's...
 */
बाह्य काष्ठा list_head	  ioc_list;
बाह्य पूर्णांक mpt_fwfault_debug;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#पूर्ण_अगर		/* पूर्ण __KERNEL__ */

#अगर_घोषित CONFIG_64BIT
#घोषणा CAST_U32_TO_PTR(x)	((व्योम *)(u64)x)
#घोषणा CAST_PTR_TO_U32(x)	((u32)(u64)x)
#अन्यथा
#घोषणा CAST_U32_TO_PTR(x)	((व्योम *)x)
#घोषणा CAST_PTR_TO_U32(x)	((u32)x)
#पूर्ण_अगर

#घोषणा MPT_PROTOCOL_FLAGS_c_c_c_c(pflags) \
	((pflags) & MPI_PORTFACTS_PROTOCOL_INITIATOR)	? 'I' : 'i',	\
	((pflags) & MPI_PORTFACTS_PROTOCOL_TARGET)	? 'T' : 't',	\
	((pflags) & MPI_PORTFACTS_PROTOCOL_LAN)		? 'L' : 'l',	\
	((pflags) & MPI_PORTFACTS_PROTOCOL_LOGBUSADDR)	? 'B' : 'b'

/*
 *  Shअगरted SGE Defines - Use in SGE with FlagsLength member.
 *  Otherwise, use MPI_xxx defines (refer to "lsi/mpi.h" header).
 *  Defaults: 32 bit SGE, SYSTEM_ADDRESS अगर direction bit is 0, पढ़ो
 */
#घोषणा MPT_TRANSFER_IOC_TO_HOST		(0x00000000)
#घोषणा MPT_TRANSFER_HOST_TO_IOC		(0x04000000)
#घोषणा MPT_SGE_FLAGS_LAST_ELEMENT		(0x80000000)
#घोषणा MPT_SGE_FLAGS_END_OF_BUFFER		(0x40000000)
#घोषणा MPT_SGE_FLAGS_LOCAL_ADDRESS		(0x08000000)
#घोषणा MPT_SGE_FLAGS_सूचीECTION			(0x04000000)
#घोषणा MPT_SGE_FLAGS_END_OF_LIST		(0x01000000)

#घोषणा MPT_SGE_FLAGS_TRANSACTION_ELEMENT	(0x00000000)
#घोषणा MPT_SGE_FLAGS_SIMPLE_ELEMENT		(0x10000000)
#घोषणा MPT_SGE_FLAGS_CHAIN_ELEMENT		(0x30000000)
#घोषणा MPT_SGE_FLAGS_ELEMENT_MASK		(0x30000000)

#घोषणा MPT_SGE_FLAGS_SSIMPLE_READ \
	(MPT_SGE_FLAGS_LAST_ELEMENT |	\
	 MPT_SGE_FLAGS_END_OF_BUFFER |	\
	 MPT_SGE_FLAGS_END_OF_LIST |	\
	 MPT_SGE_FLAGS_SIMPLE_ELEMENT |	\
	 MPT_TRANSFER_IOC_TO_HOST)
#घोषणा MPT_SGE_FLAGS_SSIMPLE_WRITE \
	(MPT_SGE_FLAGS_LAST_ELEMENT |	\
	 MPT_SGE_FLAGS_END_OF_BUFFER |	\
	 MPT_SGE_FLAGS_END_OF_LIST |	\
	 MPT_SGE_FLAGS_SIMPLE_ELEMENT |	\
	 MPT_TRANSFER_HOST_TO_IOC)

/*पूर्ण-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#पूर्ण_अगर

