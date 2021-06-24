<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptioctl.h
 *      Fusion MPT misc device (ioctl) driver.
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

#अगर_अघोषित MPTCTL_H_INCLUDED
#घोषणा MPTCTL_H_INCLUDED
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/



/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *
 */
#घोषणा MPT_MISCDEV_BASENAME            "mptctl"
#घोषणा MPT_MISCDEV_PATHNAME            "/dev/" MPT_MISCDEV_BASENAME

#घोषणा MPT_PRODUCT_LENGTH              12

/*
 *  Generic MPT Control IOCTLs and काष्ठाures
 */
#घोषणा MPT_MAGIC_NUMBER	'm'

#घोषणा MPTRWPERF		_IOWR(MPT_MAGIC_NUMBER,0,काष्ठा mpt_raw_r_w)

#घोषणा MPTFWDOWNLOAD		_IOWR(MPT_MAGIC_NUMBER,15,काष्ठा mpt_fw_xfer)
#घोषणा MPTCOMMAND		_IOWR(MPT_MAGIC_NUMBER,20,काष्ठा mpt_ioctl_command)

#अगर defined(__KERNEL__) && defined(CONFIG_COMPAT)
#घोषणा MPTFWDOWNLOAD32		_IOWR(MPT_MAGIC_NUMBER,15,काष्ठा mpt_fw_xfer32)
#घोषणा MPTCOMMAND32		_IOWR(MPT_MAGIC_NUMBER,20,काष्ठा mpt_ioctl_command32)
#पूर्ण_अगर

#घोषणा MPTIOCINFO		_IOWR(MPT_MAGIC_NUMBER,17,काष्ठा mpt_ioctl_iocinfo)
#घोषणा MPTIOCINFO1		_IOWR(MPT_MAGIC_NUMBER,17,काष्ठा mpt_ioctl_iocinfo_rev0)
#घोषणा MPTIOCINFO2		_IOWR(MPT_MAGIC_NUMBER,17,काष्ठा mpt_ioctl_iocinfo_rev1)
#घोषणा MPTTARGETINFO		_IOWR(MPT_MAGIC_NUMBER,18,काष्ठा mpt_ioctl_targetinfo)
#घोषणा MPTTEST			_IOWR(MPT_MAGIC_NUMBER,19,काष्ठा mpt_ioctl_test)
#घोषणा MPTEVENTQUERY		_IOWR(MPT_MAGIC_NUMBER,21,काष्ठा mpt_ioctl_eventquery)
#घोषणा MPTEVENTENABLE		_IOWR(MPT_MAGIC_NUMBER,22,काष्ठा mpt_ioctl_eventenable)
#घोषणा MPTEVENTREPORT		_IOWR(MPT_MAGIC_NUMBER,23,काष्ठा mpt_ioctl_eventreport)
#घोषणा MPTHARDRESET		_IOWR(MPT_MAGIC_NUMBER,24,काष्ठा mpt_ioctl_diag_reset)
#घोषणा MPTFWREPLACE		_IOWR(MPT_MAGIC_NUMBER,25,काष्ठा mpt_ioctl_replace_fw)

/*
 * SPARC PLATFORM REMARKS:
 * IOCTL data काष्ठाures that contain poपूर्णांकers
 * will have dअगरferent sizes in the driver and applications
 * (as the app. will not use 8-byte poपूर्णांकers).
 * Apps should use MPTFWDOWNLOAD and MPTCOMMAND.
 * The driver will convert data from
 * mpt_fw_xfer32 (mpt_ioctl_command32) to mpt_fw_xfer (mpt_ioctl_command)
 * पूर्णांकernally.
 *
 * If data काष्ठाures change size, must handle as in IOCGETINFO.
 */
काष्ठा mpt_fw_xfer अणु
	अचिन्हित पूर्णांक	 iocnum;	/* IOC unit number */
	अचिन्हित पूर्णांक	 fwlen;
	व्योम		__user *bufp;	/* Poपूर्णांकer to firmware buffer */
पूर्ण;

#अगर defined(__KERNEL__) && defined(CONFIG_COMPAT)
काष्ठा mpt_fw_xfer32 अणु
	अचिन्हित पूर्णांक iocnum;
	अचिन्हित पूर्णांक fwlen;
	u32 bufp;
पूर्ण;
#पूर्ण_अगर	/*पूर्ण*/

/*
 *  IOCTL header काष्ठाure.
 *  iocnum - must be defined.
 *  port - must be defined क्रम all IOCTL commands other than MPTIOCINFO
 *  maxDataSize - ignored on MPTCOMMAND commands
 *		- ignored on MPTFWREPLACE commands
 *		- on query commands, reports the maximum number of bytes to be वापसed
 *		  to the host driver (count includes the header).
 *		  That is, set to माप(काष्ठा mpt_ioctl_iocinfo) क्रम fixed sized commands.
 *		  Set to माप(काष्ठा mpt_ioctl_targetinfo) + datasize क्रम variable
 *			sized commands. (MPTTARGETINFO, MPTEVENTREPORT)
 */
प्रकार काष्ठा _mpt_ioctl_header अणु
	अचिन्हित पूर्णांक	 iocnum;	/* IOC unit number */
	अचिन्हित पूर्णांक	 port;		/* IOC port number */
	पूर्णांक		 maxDataSize;	/* Maximum Num. bytes to transfer on पढ़ो */
पूर्ण mpt_ioctl_header;

/*
 * Issue a diagnostic reset
 */
काष्ठा mpt_ioctl_diag_reset अणु
	mpt_ioctl_header hdr;
पूर्ण;


/*
 *  PCI bus/device/function inक्रमmation काष्ठाure.
 */
काष्ठा mpt_ioctl_pci_info अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक  deviceNumber   :  5;
			अचिन्हित पूर्णांक  functionNumber :  3;
			अचिन्हित पूर्णांक  busNumber      : 24;
		पूर्ण bits;
		अचिन्हित पूर्णांक  asUदीर्घ;
	पूर्ण u;
पूर्ण;

काष्ठा mpt_ioctl_pci_info2 अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक  deviceNumber   :  5;
			अचिन्हित पूर्णांक  functionNumber :  3;
			अचिन्हित पूर्णांक  busNumber      : 24;
		पूर्ण bits;
		अचिन्हित पूर्णांक  asUदीर्घ;
	पूर्ण u;
  पूर्णांक segmentID;
पूर्ण;

/*
 *  Adapter Inक्रमmation Page
 *  Read only.
 *  Data starts at offset 0xC
 */
#घोषणा MPT_IOCTL_INTERFACE_SCSI	(0x00)
#घोषणा MPT_IOCTL_INTERFACE_FC		(0x01)
#घोषणा MPT_IOCTL_INTERFACE_FC_IP	(0x02)
#घोषणा MPT_IOCTL_INTERFACE_SAS		(0x03)
#घोषणा MPT_IOCTL_VERSION_LENGTH	(32)

काष्ठा mpt_ioctl_iocinfo अणु
	mpt_ioctl_header hdr;
	पूर्णांक		 adapterType;	/* SCSI or FCP */
	पूर्णांक		 port;		/* port number */
	पूर्णांक		 pciId;		/* PCI Id. */
	पूर्णांक		 hwRev;		/* hardware revision */
	पूर्णांक		 subSystemDevice;	/* PCI subप्रणाली Device ID */
	पूर्णांक		 subSystemVenकरोr;	/* PCI subप्रणाली Venकरोr ID */
	पूर्णांक		 numDevices;		/* number of devices */
	पूर्णांक		 FWVersion;		/* FW Version (पूर्णांकeger) */
	पूर्णांक		 BIOSVersion;		/* BIOS Version (पूर्णांकeger) */
	अक्षर		 driverVersion[MPT_IOCTL_VERSION_LENGTH];	/* Driver Version (string) */
	अक्षर		 busChangeEvent;
	अक्षर		 hostId;
	अक्षर		 rsvd[2];
	काष्ठा mpt_ioctl_pci_info2  pciInfo; /* Added Rev 2 */
पूर्ण;

काष्ठा mpt_ioctl_iocinfo_rev1 अणु
	mpt_ioctl_header hdr;
	पूर्णांक		 adapterType;	/* SCSI or FCP */
	पूर्णांक		 port;		/* port number */
	पूर्णांक		 pciId;		/* PCI Id. */
	पूर्णांक		 hwRev;		/* hardware revision */
	पूर्णांक		 subSystemDevice;	/* PCI subप्रणाली Device ID */
	पूर्णांक		 subSystemVenकरोr;	/* PCI subप्रणाली Venकरोr ID */
	पूर्णांक		 numDevices;		/* number of devices */
	पूर्णांक		 FWVersion;		/* FW Version (पूर्णांकeger) */
	पूर्णांक		 BIOSVersion;		/* BIOS Version (पूर्णांकeger) */
	अक्षर		 driverVersion[MPT_IOCTL_VERSION_LENGTH];	/* Driver Version (string) */
	अक्षर		 busChangeEvent;
	अक्षर		 hostId;
	अक्षर		 rsvd[2];
	काष्ठा mpt_ioctl_pci_info  pciInfo; /* Added Rev 1 */
पूर्ण;

/* Original काष्ठाure, must always accept these
 * IOCTLs. 4 byte pads can occur based on arch with
 * above काष्ठाure. Wish to re-align, but cannot.
 */
काष्ठा mpt_ioctl_iocinfo_rev0 अणु
	mpt_ioctl_header hdr;
	पूर्णांक		 adapterType;	/* SCSI or FCP */
	पूर्णांक		 port;		/* port number */
	पूर्णांक		 pciId;		/* PCI Id. */
	पूर्णांक		 hwRev;		/* hardware revision */
	पूर्णांक		 subSystemDevice;	/* PCI subप्रणाली Device ID */
	पूर्णांक		 subSystemVenकरोr;	/* PCI subप्रणाली Venकरोr ID */
	पूर्णांक		 numDevices;		/* number of devices */
	पूर्णांक		 FWVersion;		/* FW Version (पूर्णांकeger) */
	पूर्णांक		 BIOSVersion;		/* BIOS Version (पूर्णांकeger) */
	अक्षर		 driverVersion[MPT_IOCTL_VERSION_LENGTH];	/* Driver Version (string) */
	अक्षर		 busChangeEvent;
	अक्षर		 hostId;
	अक्षर		 rsvd[2];
पूर्ण;

/*
 * Device Inक्रमmation Page
 * Report the number of, and ids of, all tarमाला_लो
 * on this IOC.  The ids array is a packed काष्ठाure
 * of the known targetInfo.
 * bits 31-24: reserved
 *      23-16: LUN
 *      15- 8: Bus Number
 *       7- 0: Target ID
 */
काष्ठा mpt_ioctl_targetinfo अणु
	mpt_ioctl_header hdr;
	पूर्णांक		 numDevices;	/* Num tarमाला_लो on this ioc */
	पूर्णांक		 targetInfo[1];
पूर्ण;


/*
 * Event reporting IOCTL's.  These IOCTL's will
 * use the following defines:
 */
काष्ठा mpt_ioctl_eventquery अणु
	mpt_ioctl_header hdr;
	अचिन्हित लघु	 eventEntries;
	अचिन्हित लघु	 reserved;
	अचिन्हित पूर्णांक	 eventTypes;
पूर्ण;

काष्ठा mpt_ioctl_eventenable अणु
	mpt_ioctl_header hdr;
	अचिन्हित पूर्णांक	 eventTypes;
पूर्ण;

#अगर_अघोषित __KERNEL__
प्रकार काष्ठा अणु
	uपूर्णांक	event;
	uपूर्णांक	eventContext;
	uपूर्णांक	data[2];
पूर्ण MPT_IOCTL_EVENTS;
#पूर्ण_अगर

काष्ठा mpt_ioctl_eventreport अणु
	mpt_ioctl_header	hdr;
	MPT_IOCTL_EVENTS	eventData[1];
पूर्ण;

#घोषणा MPT_MAX_NAME	32
काष्ठा mpt_ioctl_test अणु
	mpt_ioctl_header hdr;
	u8		 name[MPT_MAX_NAME];
	पूर्णांक		 chip_type;
	u8		 product [MPT_PRODUCT_LENGTH];
पूर्ण;

/* Replace the FW image cached in host driver memory
 * newImageSize - image size in bytes
 * newImage - first byte of the new image
 */
प्रकार काष्ठा mpt_ioctl_replace_fw अणु
	mpt_ioctl_header hdr;
	पूर्णांक		 newImageSize;
	u8		 newImage[1];
पूर्ण mpt_ioctl_replace_fw_t;

/* General MPT Pass through data strucutre
 *
 * iocnum
 * समयout - in seconds, command समयout. If 0, set by driver to
 *		शेष value.
 * replyFrameBufPtr - reply location
 * dataInBufPtr - destination क्रम पढ़ो
 * dataOutBufPtr - data source क्रम ग_लिखो
 * senseDataPtr - sense data location
 * maxReplyBytes - maximum number of reply bytes to be sent to app.
 * dataInSize - num bytes क्रम data transfer in (पढ़ो)
 * dataOutSize - num bytes क्रम data transfer out (ग_लिखो)
 * dataSgeOffset - offset in words from the start of the request message
 *		to the first SGL
 * MF[1];
 *
 * Remark:  Some config pages have bi-directional transfer,
 * both a पढ़ो and a ग_लिखो. The basic काष्ठाure allows क्रम
 * a bidirectional set up. Normal messages will have one or
 * both of these buffers शून्य.
 */
काष्ठा mpt_ioctl_command अणु
	mpt_ioctl_header hdr;
	पूर्णांक		समयout;	/* optional (seconds) */
	अक्षर		__user *replyFrameBufPtr;
	अक्षर		__user *dataInBufPtr;
	अक्षर		__user *dataOutBufPtr;
	अक्षर		__user *senseDataPtr;
	पूर्णांक		maxReplyBytes;
	पूर्णांक		dataInSize;
	पूर्णांक		dataOutSize;
	पूर्णांक		maxSenseBytes;
	पूर्णांक		dataSgeOffset;
	अक्षर		MF[1];
पूर्ण;

/*
 * SPARC PLATFORM: See earlier remark.
 */
#अगर defined(__KERNEL__) && defined(CONFIG_COMPAT)
काष्ठा mpt_ioctl_command32 अणु
	mpt_ioctl_header hdr;
	पूर्णांक	समयout;
	u32	replyFrameBufPtr;
	u32	dataInBufPtr;
	u32	dataOutBufPtr;
	u32	senseDataPtr;
	पूर्णांक	maxReplyBytes;
	पूर्णांक	dataInSize;
	पूर्णांक	dataOutSize;
	पूर्णांक	maxSenseBytes;
	पूर्णांक	dataSgeOffset;
	अक्षर	MF[1];
पूर्ण;
#पूर्ण_अगर	/*पूर्ण*/


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#घोषणा CPQFCTS_IOC_MAGIC 'Z'
#घोषणा HP_IOC_MAGIC 'Z'
#घोषणा HP_GETHOSTINFO		_IOR(HP_IOC_MAGIC, 20, hp_host_info_t)
#घोषणा HP_GETHOSTINFO1		_IOR(HP_IOC_MAGIC, 20, hp_host_info_rev0_t)
#घोषणा HP_GETTARGETINFO	_IOR(HP_IOC_MAGIC, 21, hp_target_info_t)

प्रकार काष्ठा _hp_header अणु
	अचिन्हित पूर्णांक iocnum;
	अचिन्हित पूर्णांक host;
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक lun;
पूर्ण hp_header_t;

/*
 *  Header:
 *  iocnum 	required (input)
 *  host 	ignored
 *  channe	ignored
 *  id		ignored
 *  lun		ignored
 */
प्रकार काष्ठा _hp_host_info अणु
	hp_header_t	 hdr;
	u16		 venकरोr;
	u16		 device;
	u16		 subप्रणाली_venकरोr;
	u16		 subप्रणाली_id;
	u8		 devfn;
	u8		 bus;
	uलघु		 host_no;		/* SCSI Host number, अगर scsi driver not loaded*/
	u8		 fw_version[16];	/* string */
	u8		 serial_number[24];	/* string */
	u32		 ioc_status;
	u32		 bus_phys_width;
	u32		 base_io_addr;
	u32		 rsvd;
	अचिन्हित पूर्णांक	 hard_resets;		/* driver initiated resets */
	अचिन्हित पूर्णांक	 soft_resets;		/* ioc, बाह्यal resets */
	अचिन्हित पूर्णांक	 समयouts;		/* num समयouts */
पूर्ण hp_host_info_t;

/* replace uदीर्घs with uपूर्णांकs, need to preserve backwards
 * compatibility.
 */
प्रकार काष्ठा _hp_host_info_rev0 अणु
	hp_header_t	 hdr;
	u16		 venकरोr;
	u16		 device;
	u16		 subप्रणाली_venकरोr;
	u16		 subप्रणाली_id;
	u8		 devfn;
	u8		 bus;
	uलघु		 host_no;		/* SCSI Host number, अगर scsi driver not loaded*/
	u8		 fw_version[16];	/* string */
	u8		 serial_number[24];	/* string */
	u32		 ioc_status;
	u32		 bus_phys_width;
	u32		 base_io_addr;
	u32		 rsvd;
	अचिन्हित दीर्घ	 hard_resets;		/* driver initiated resets */
	अचिन्हित दीर्घ	 soft_resets;		/* ioc, बाह्यal resets */
	अचिन्हित दीर्घ	 समयouts;		/* num समयouts */
पूर्ण hp_host_info_rev0_t;

/*
 *  Header:
 *  iocnum 	required (input)
 *  host 	required
 *  channel	required	(bus number)
 *  id		required
 *  lun		ignored
 *
 *  All error values between 0 and 0xFFFF in size.
 */
प्रकार काष्ठा _hp_target_info अणु
	hp_header_t	 hdr;
	u32 parity_errors;
	u32 phase_errors;
	u32 select_समयouts;
	u32 message_rejects;
	u32 negotiated_speed;
	u8  negotiated_width;
	u8  rsvd[7];				/* 8 byte alignment */
पूर्ण hp_target_info_t;

#घोषणा HP_STATUS_OTHER		1
#घोषणा HP_STATUS_OK		2
#घोषणा HP_STATUS_FAILED	3

#घोषणा HP_BUS_WIDTH_UNK	1
#घोषणा HP_BUS_WIDTH_8		2
#घोषणा HP_BUS_WIDTH_16		3
#घोषणा HP_BUS_WIDTH_32		4

#घोषणा HP_DEV_SPEED_ASYNC	2
#घोषणा HP_DEV_SPEED_FAST	3
#घोषणा HP_DEV_SPEED_ULTRA	4
#घोषणा HP_DEV_SPEED_ULTRA2	5
#घोषणा HP_DEV_SPEED_ULTRA160	6
#घोषणा HP_DEV_SPEED_SCSI1	7
#घोषणा HP_DEV_SPEED_ULTRA320	8

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#पूर्ण_अगर

