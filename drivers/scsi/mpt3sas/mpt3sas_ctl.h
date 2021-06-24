<शैली गुरु>
/*
 * Management Module Support क्रम MPT (Message Passing Technology) based
 * controllers
 *
 * This code is based on drivers/scsi/mpt3sas/mpt3sas_ctl.h
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

#अगर_अघोषित MPT3SAS_CTL_H_INCLUDED
#घोषणा MPT3SAS_CTL_H_INCLUDED

#अगर_घोषित __KERNEL__
#समावेश <linux/miscdevice.h>
#पूर्ण_अगर

#समावेश "mpt3sas_base.h"

#अगर_अघोषित MPT2SAS_MINOR
#घोषणा MPT2SAS_MINOR		(MPT_MINOR + 1)
#पूर्ण_अगर
#अगर_अघोषित MPT3SAS_MINOR
#घोषणा MPT3SAS_MINOR		(MPT_MINOR + 2)
#पूर्ण_अगर
#घोषणा MPT2SAS_DEV_NAME	"mpt2ctl"
#घोषणा MPT3SAS_DEV_NAME	"mpt3ctl"
#घोषणा MPT3_MAGIC_NUMBER	'L'
#घोषणा MPT3_IOCTL_DEFAULT_TIMEOUT (10) /* in seconds */

/**
 * IOCTL opcodes
 */
#घोषणा MPT3IOCINFO	_IOWR(MPT3_MAGIC_NUMBER, 17, \
	काष्ठा mpt3_ioctl_iocinfo)
#घोषणा MPT3COMMAND	_IOWR(MPT3_MAGIC_NUMBER, 20, \
	काष्ठा mpt3_ioctl_command)
#अगर_घोषित CONFIG_COMPAT
#घोषणा MPT3COMMAND32	_IOWR(MPT3_MAGIC_NUMBER, 20, \
	काष्ठा mpt3_ioctl_command32)
#पूर्ण_अगर
#घोषणा MPT3EVENTQUERY	_IOWR(MPT3_MAGIC_NUMBER, 21, \
	काष्ठा mpt3_ioctl_eventquery)
#घोषणा MPT3EVENTENABLE	_IOWR(MPT3_MAGIC_NUMBER, 22, \
	काष्ठा mpt3_ioctl_eventenable)
#घोषणा MPT3EVENTREPORT	_IOWR(MPT3_MAGIC_NUMBER, 23, \
	काष्ठा mpt3_ioctl_eventreport)
#घोषणा MPT3HARDRESET	_IOWR(MPT3_MAGIC_NUMBER, 24, \
	काष्ठा mpt3_ioctl_diag_reset)
#घोषणा MPT3BTDHMAPPING	_IOWR(MPT3_MAGIC_NUMBER, 31, \
	काष्ठा mpt3_ioctl_btdh_mapping)

/* diag buffer support */
#घोषणा MPT3DIAGREGISTER _IOWR(MPT3_MAGIC_NUMBER, 26, \
	काष्ठा mpt3_diag_रेजिस्टर)
#घोषणा MPT3DIAGRELEASE	_IOWR(MPT3_MAGIC_NUMBER, 27, \
	काष्ठा mpt3_diag_release)
#घोषणा MPT3DIAGUNREGISTER _IOWR(MPT3_MAGIC_NUMBER, 28, \
	काष्ठा mpt3_diag_unरेजिस्टर)
#घोषणा MPT3DIAGQUERY	_IOWR(MPT3_MAGIC_NUMBER, 29, \
	काष्ठा mpt3_diag_query)
#घोषणा MPT3DIAGREADBUFFER _IOWR(MPT3_MAGIC_NUMBER, 30, \
	काष्ठा mpt3_diag_पढ़ो_buffer)
#घोषणा MPT3ADDNLDIAGQUERY _IOWR(MPT3_MAGIC_NUMBER, 32, \
	काष्ठा mpt3_addnl_diag_query)

/* Trace Buffer शेष UniqueId */
#घोषणा MPT2DIAGBUFFUNIQUEID (0x07075900)
#घोषणा MPT3DIAGBUFFUNIQUEID (0x4252434D)

/* UID not found */
#घोषणा MPT3_DIAG_UID_NOT_FOUND (0xFF)


/**
 * काष्ठा mpt3_ioctl_header - मुख्य header काष्ठाure
 * @ioc_number -  IOC unit number
 * @port_number - IOC port number
 * @max_data_size - maximum number bytes to transfer on पढ़ो
 */
काष्ठा mpt3_ioctl_header अणु
	uपूर्णांक32_t ioc_number;
	uपूर्णांक32_t port_number;
	uपूर्णांक32_t max_data_size;
पूर्ण;

/**
 * काष्ठा mpt3_ioctl_diag_reset - diagnostic reset
 * @hdr - generic header
 */
काष्ठा mpt3_ioctl_diag_reset अणु
	काष्ठा mpt3_ioctl_header hdr;
पूर्ण;


/**
 * काष्ठा mpt3_ioctl_pci_info - pci device info
 * @device - pci device id
 * @function - pci function id
 * @bus - pci bus id
 * @segment_id - pci segment id
 */
काष्ठा mpt3_ioctl_pci_info अणु
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t device:5;
			uपूर्णांक32_t function:3;
			uपूर्णांक32_t bus:24;
		पूर्ण bits;
		uपूर्णांक32_t  word;
	पूर्ण u;
	uपूर्णांक32_t segment_id;
पूर्ण;


#घोषणा MPT2_IOCTL_INTERFACE_SCSI	(0x00)
#घोषणा MPT2_IOCTL_INTERFACE_FC		(0x01)
#घोषणा MPT2_IOCTL_INTERFACE_FC_IP	(0x02)
#घोषणा MPT2_IOCTL_INTERFACE_SAS	(0x03)
#घोषणा MPT2_IOCTL_INTERFACE_SAS2	(0x04)
#घोषणा MPT2_IOCTL_INTERFACE_SAS2_SSS6200	(0x05)
#घोषणा MPT3_IOCTL_INTERFACE_SAS3	(0x06)
#घोषणा MPT3_IOCTL_INTERFACE_SAS35	(0x07)
#घोषणा MPT2_IOCTL_VERSION_LENGTH	(32)

/**
 * काष्ठा mpt3_ioctl_iocinfo - generic controller info
 * @hdr - generic header
 * @adapter_type - type of adapter (spi, fc, sas)
 * @port_number - port number
 * @pci_id - PCI Id
 * @hw_rev - hardware revision
 * @sub_प्रणाली_device - PCI subप्रणाली Device ID
 * @sub_प्रणाली_venकरोr - PCI subप्रणाली Venकरोr ID
 * @rsvd0 - reserved
 * @firmware_version - firmware version
 * @bios_version - BIOS version
 * @driver_version - driver version - 32 ASCII अक्षरacters
 * @rsvd1 - reserved
 * @scsi_id - scsi id of adapter 0
 * @rsvd2 - reserved
 * @pci_inक्रमmation - pci info (2nd revision)
 */
काष्ठा mpt3_ioctl_iocinfo अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक32_t adapter_type;
	uपूर्णांक32_t port_number;
	uपूर्णांक32_t pci_id;
	uपूर्णांक32_t hw_rev;
	uपूर्णांक32_t subप्रणाली_device;
	uपूर्णांक32_t subप्रणाली_venकरोr;
	uपूर्णांक32_t rsvd0;
	uपूर्णांक32_t firmware_version;
	uपूर्णांक32_t bios_version;
	uपूर्णांक8_t driver_version[MPT2_IOCTL_VERSION_LENGTH];
	uपूर्णांक8_t rsvd1;
	uपूर्णांक8_t scsi_id;
	uपूर्णांक16_t rsvd2;
	काष्ठा mpt3_ioctl_pci_info pci_inक्रमmation;
पूर्ण;


/* number of event log entries */
#घोषणा MPT3SAS_CTL_EVENT_LOG_SIZE (200)

/**
 * काष्ठा mpt3_ioctl_eventquery - query event count and type
 * @hdr - generic header
 * @event_entries - number of events वापसed by get_event_report
 * @rsvd - reserved
 * @event_types - type of events currently being captured
 */
काष्ठा mpt3_ioctl_eventquery अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक16_t event_entries;
	uपूर्णांक16_t rsvd;
	uपूर्णांक32_t event_types[MPI2_EVENT_NOTIFY_EVENTMASK_WORDS];
पूर्ण;

/**
 * काष्ठा mpt3_ioctl_eventenable - enable/disable event capturing
 * @hdr - generic header
 * @event_types - toggle off/on type of events to be captured
 */
काष्ठा mpt3_ioctl_eventenable अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक32_t event_types[4];
पूर्ण;

#घोषणा MPT3_EVENT_DATA_SIZE (192)
/**
 * काष्ठा MPT3_IOCTL_EVENTS -
 * @event - the event that was reported
 * @context - unique value क्रम each event asचिन्हित by driver
 * @data - event data वापसed in fw reply message
 */
काष्ठा MPT3_IOCTL_EVENTS अणु
	uपूर्णांक32_t event;
	uपूर्णांक32_t context;
	uपूर्णांक8_t data[MPT3_EVENT_DATA_SIZE];
पूर्ण;

/**
 * काष्ठा mpt3_ioctl_eventreport - returing event log
 * @hdr - generic header
 * @event_data - (see काष्ठा MPT3_IOCTL_EVENTS)
 */
काष्ठा mpt3_ioctl_eventreport अणु
	काष्ठा mpt3_ioctl_header hdr;
	काष्ठा MPT3_IOCTL_EVENTS event_data[1];
पूर्ण;

/**
 * काष्ठा mpt3_ioctl_command - generic mpt firmware passthru ioctl
 * @hdr - generic header
 * @समयout - command समयout in seconds. (अगर zero then use driver शेष
 *  value).
 * @reply_frame_buf_ptr - reply location
 * @data_in_buf_ptr - destination क्रम पढ़ो
 * @data_out_buf_ptr - data source क्रम ग_लिखो
 * @sense_data_ptr - sense data location
 * @max_reply_bytes - maximum number of reply bytes to be sent to app.
 * @data_in_size - number bytes क्रम data transfer in (पढ़ो)
 * @data_out_size - number bytes क्रम data transfer out (ग_लिखो)
 * @max_sense_bytes - maximum number of bytes क्रम स्वतः sense buffers
 * @data_sge_offset - offset in words from the start of the request message to
 * the first SGL
 * @mf[1];
 */
काष्ठा mpt3_ioctl_command अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक32_t समयout;
	व्योम __user *reply_frame_buf_ptr;
	व्योम __user *data_in_buf_ptr;
	व्योम __user *data_out_buf_ptr;
	व्योम __user *sense_data_ptr;
	uपूर्णांक32_t max_reply_bytes;
	uपूर्णांक32_t data_in_size;
	uपूर्णांक32_t data_out_size;
	uपूर्णांक32_t max_sense_bytes;
	uपूर्णांक32_t data_sge_offset;
	uपूर्णांक8_t mf[1];
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
काष्ठा mpt3_ioctl_command32 अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक32_t समयout;
	uपूर्णांक32_t reply_frame_buf_ptr;
	uपूर्णांक32_t data_in_buf_ptr;
	uपूर्णांक32_t data_out_buf_ptr;
	uपूर्णांक32_t sense_data_ptr;
	uपूर्णांक32_t max_reply_bytes;
	uपूर्णांक32_t data_in_size;
	uपूर्णांक32_t data_out_size;
	uपूर्णांक32_t max_sense_bytes;
	uपूर्णांक32_t data_sge_offset;
	uपूर्णांक8_t mf[1];
पूर्ण;
#पूर्ण_अगर

/**
 * काष्ठा mpt3_ioctl_btdh_mapping - mapping info
 * @hdr - generic header
 * @id - target device identअगरication number
 * @bus - SCSI bus number that the target device exists on
 * @handle - device handle क्रम the target device
 * @rsvd - reserved
 *
 * To obtain a bus/id the application sets
 * handle to valid handle, and bus/id to 0xFFFF.
 *
 * To obtain the device handle the application sets
 * bus/id valid value, and the handle to 0xFFFF.
 */
काष्ठा mpt3_ioctl_btdh_mapping अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक32_t id;
	uपूर्णांक32_t bus;
	uपूर्णांक16_t handle;
	uपूर्णांक16_t rsvd;
पूर्ण;



/* application flags क्रम mpt3_diag_रेजिस्टर, mpt3_diag_query */
#घोषणा MPT3_APP_FLAGS_APP_OWNED	(0x0001)
#घोषणा MPT3_APP_FLAGS_BUFFER_VALID	(0x0002)
#घोषणा MPT3_APP_FLAGS_FW_BUFFER_ACCESS	(0x0004)
#घोषणा MPT3_APP_FLAGS_DYNAMIC_BUFFER_ALLOC (0x0008)

/* flags क्रम mpt3_diag_पढ़ो_buffer */
#घोषणा MPT3_FLAGS_REREGISTER		(0x0001)

#घोषणा MPT3_PRODUCT_SPECIFIC_DWORDS		23

/**
 * काष्ठा mpt3_diag_रेजिस्टर - application रेजिस्टर with driver
 * @hdr - generic header
 * @reserved -
 * @buffer_type - specअगरies either TRACE, SNAPSHOT, or EXTENDED
 * @application_flags - misc flags
 * @diagnostic_flags - specअगरies flags affecting command processing
 * @product_specअगरic - product specअगरic inक्रमmation
 * @requested_buffer_size - buffers size in bytes
 * @unique_id - tag specअगरied by application that is used to संकेत ownership
 *  of the buffer.
 *
 * This will allow the driver to setup any required buffers that will be
 * needed by firmware to communicate with the driver.
 */
काष्ठा mpt3_diag_रेजिस्टर अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक8_t reserved;
	uपूर्णांक8_t buffer_type;
	uपूर्णांक16_t application_flags;
	uपूर्णांक32_t diagnostic_flags;
	uपूर्णांक32_t product_specअगरic[MPT3_PRODUCT_SPECIFIC_DWORDS];
	uपूर्णांक32_t requested_buffer_size;
	uपूर्णांक32_t unique_id;
पूर्ण;

/**
 * काष्ठा mpt3_diag_unरेजिस्टर - application unरेजिस्टर with driver
 * @hdr - generic header
 * @unique_id - tag uniquely identअगरies the buffer to be unरेजिस्टरed
 *
 * This will allow the driver to cleanup any memory allocated क्रम diag
 * messages and to मुक्त up any resources.
 */
काष्ठा mpt3_diag_unरेजिस्टर अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक32_t unique_id;
पूर्ण;

/**
 * काष्ठा mpt3_diag_query - query relevant info associated with diag buffers
 * @hdr - generic header
 * @reserved -
 * @buffer_type - specअगरies either TRACE, SNAPSHOT, or EXTENDED
 * @application_flags - misc flags
 * @diagnostic_flags - specअगरies flags affecting command processing
 * @product_specअगरic - product specअगरic inक्रमmation
 * @total_buffer_size - diag buffer size in bytes
 * @driver_added_buffer_size - size of extra space appended to end of buffer
 * @unique_id - unique id associated with this buffer.
 *
 * The application will send only buffer_type and unique_id.  Driver will
 * inspect unique_id first, अगर valid, fill in all the info.  If unique_id is
 * 0x00, the driver will वापस info specअगरied by Buffer Type.
 */
काष्ठा mpt3_diag_query अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक8_t reserved;
	uपूर्णांक8_t buffer_type;
	uपूर्णांक16_t application_flags;
	uपूर्णांक32_t diagnostic_flags;
	uपूर्णांक32_t product_specअगरic[MPT3_PRODUCT_SPECIFIC_DWORDS];
	uपूर्णांक32_t total_buffer_size;
	uपूर्णांक32_t driver_added_buffer_size;
	uपूर्णांक32_t unique_id;
पूर्ण;

/**
 * काष्ठा mpt3_diag_release -  request to send Diag Release Message to firmware
 * @hdr - generic header
 * @unique_id - tag uniquely identअगरies the buffer to be released
 *
 * This allows ownership of the specअगरied buffer to वापसed to the driver,
 * allowing an application to पढ़ो the buffer without fear that firmware is
 * overwriting inक्रमmation in the buffer.
 */
काष्ठा mpt3_diag_release अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक32_t unique_id;
पूर्ण;

/**
 * काष्ठा mpt3_diag_पढ़ो_buffer - request क्रम copy of the diag buffer
 * @hdr - generic header
 * @status -
 * @reserved -
 * @flags - misc flags
 * @starting_offset - starting offset within drivers buffer where to start
 *  पढ़ोing data at पूर्णांकo the specअगरied application buffer
 * @bytes_to_पढ़ो - number of bytes to copy from the drivers buffer पूर्णांकo the
 *  application buffer starting at starting_offset.
 * @unique_id - unique id associated with this buffer.
 * @diagnostic_data - data payload
 */
काष्ठा mpt3_diag_पढ़ो_buffer अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक8_t status;
	uपूर्णांक8_t reserved;
	uपूर्णांक16_t flags;
	uपूर्णांक32_t starting_offset;
	uपूर्णांक32_t bytes_to_पढ़ो;
	uपूर्णांक32_t unique_id;
	uपूर्णांक32_t diagnostic_data[1];
पूर्ण;

/**
 * काष्ठा mpt3_addnl_diag_query - diagnostic buffer release reason
 * @hdr - generic header
 * @unique_id - unique id associated with this buffer.
 * @rel_query - release query.
 * @reserved2
 */
काष्ठा mpt3_addnl_diag_query अणु
	काष्ठा mpt3_ioctl_header hdr;
	uपूर्णांक32_t unique_id;
	काष्ठा htb_rel_query rel_query;
	uपूर्णांक32_t reserved2[2];
पूर्ण;

#पूर्ण_अगर /* MPT3SAS_CTL_H_INCLUDED */
