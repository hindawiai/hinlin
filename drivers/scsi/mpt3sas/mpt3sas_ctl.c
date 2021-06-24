<शैली गुरु>
/*
 * Management Module Support क्रम MPT (Message Passing Technology) based
 * controllers
 *
 * This code is based on drivers/scsi/mpt3sas/mpt3sas_ctl.c
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/compat.h>
#समावेश <linux/poll.h>

#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#समावेश "mpt3sas_base.h"
#समावेश "mpt3sas_ctl.h"


अटल काष्ठा fasync_काष्ठा *async_queue;
अटल DECLARE_WAIT_QUEUE_HEAD(ctl_poll_रुको);


/**
 * क्रमागत block_state - blocking state
 * @NON_BLOCKING: non blocking
 * @BLOCKING: blocking
 *
 * These states are क्रम ioctls that need to रुको क्रम a response
 * from firmware, so they probably require sleep.
 */
क्रमागत block_state अणु
	NON_BLOCKING,
	BLOCKING,
पूर्ण;

/**
 * _ctl_display_some_debug - debug routine
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @calling_function_name: string pass from calling function
 * @mpi_reply: reply message frame
 * Context: none.
 *
 * Function क्रम displaying debug info helpful when debugging issues
 * in this module.
 */
अटल व्योम
_ctl_display_some_debug(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	अक्षर *calling_function_name, MPI2DefaultReply_t *mpi_reply)
अणु
	Mpi2ConfigRequest_t *mpi_request;
	अक्षर *desc = शून्य;

	अगर (!(ioc->logging_level & MPT_DEBUG_IOCTL))
		वापस;

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	चयन (mpi_request->Function) अणु
	हाल MPI2_FUNCTION_SCSI_IO_REQUEST:
	अणु
		Mpi2SCSIIORequest_t *scsi_request =
		    (Mpi2SCSIIORequest_t *)mpi_request;

		snम_लिखो(ioc->पंचांगp_string, MPT_STRING_LENGTH,
		    "scsi_io, cmd(0x%02x), cdb_len(%d)",
		    scsi_request->CDB.CDB32[0],
		    le16_to_cpu(scsi_request->IoFlags) & 0xF);
		desc = ioc->पंचांगp_string;
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_SCSI_TASK_MGMT:
		desc = "task_mgmt";
		अवरोध;
	हाल MPI2_FUNCTION_IOC_INIT:
		desc = "ioc_init";
		अवरोध;
	हाल MPI2_FUNCTION_IOC_FACTS:
		desc = "ioc_facts";
		अवरोध;
	हाल MPI2_FUNCTION_CONFIG:
	अणु
		Mpi2ConfigRequest_t *config_request =
		    (Mpi2ConfigRequest_t *)mpi_request;

		snम_लिखो(ioc->पंचांगp_string, MPT_STRING_LENGTH,
		    "config, type(0x%02x), ext_type(0x%02x), number(%d)",
		    (config_request->Header.PageType &
		     MPI2_CONFIG_PAGETYPE_MASK), config_request->ExtPageType,
		    config_request->Header.PageNumber);
		desc = ioc->पंचांगp_string;
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_PORT_FACTS:
		desc = "port_facts";
		अवरोध;
	हाल MPI2_FUNCTION_PORT_ENABLE:
		desc = "port_enable";
		अवरोध;
	हाल MPI2_FUNCTION_EVENT_NOTIFICATION:
		desc = "event_notification";
		अवरोध;
	हाल MPI2_FUNCTION_FW_DOWNLOAD:
		desc = "fw_download";
		अवरोध;
	हाल MPI2_FUNCTION_FW_UPLOAD:
		desc = "fw_upload";
		अवरोध;
	हाल MPI2_FUNCTION_RAID_ACTION:
		desc = "raid_action";
		अवरोध;
	हाल MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH:
	अणु
		Mpi2SCSIIORequest_t *scsi_request =
		    (Mpi2SCSIIORequest_t *)mpi_request;

		snम_लिखो(ioc->पंचांगp_string, MPT_STRING_LENGTH,
		    "raid_pass, cmd(0x%02x), cdb_len(%d)",
		    scsi_request->CDB.CDB32[0],
		    le16_to_cpu(scsi_request->IoFlags) & 0xF);
		desc = ioc->पंचांगp_string;
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_SAS_IO_UNIT_CONTROL:
		desc = "sas_iounit_cntl";
		अवरोध;
	हाल MPI2_FUNCTION_SATA_PASSTHROUGH:
		desc = "sata_pass";
		अवरोध;
	हाल MPI2_FUNCTION_DIAG_BUFFER_POST:
		desc = "diag_buffer_post";
		अवरोध;
	हाल MPI2_FUNCTION_DIAG_RELEASE:
		desc = "diag_release";
		अवरोध;
	हाल MPI2_FUNCTION_SMP_PASSTHROUGH:
		desc = "smp_passthrough";
		अवरोध;
	हाल MPI2_FUNCTION_TOOLBOX:
		desc = "toolbox";
		अवरोध;
	हाल MPI2_FUNCTION_NVME_ENCAPSULATED:
		desc = "nvme_encapsulated";
		अवरोध;
	पूर्ण

	अगर (!desc)
		वापस;

	ioc_info(ioc, "%s: %s, smid(%d)\n", calling_function_name, desc, smid);

	अगर (!mpi_reply)
		वापस;

	अगर (mpi_reply->IOCStatus || mpi_reply->IOCLogInfo)
		ioc_info(ioc, "\tiocstatus(0x%04x), loginfo(0x%08x)\n",
			 le16_to_cpu(mpi_reply->IOCStatus),
			 le32_to_cpu(mpi_reply->IOCLogInfo));

	अगर (mpi_request->Function == MPI2_FUNCTION_SCSI_IO_REQUEST ||
	    mpi_request->Function ==
	    MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH) अणु
		Mpi2SCSIIOReply_t *scsi_reply =
		    (Mpi2SCSIIOReply_t *)mpi_reply;
		काष्ठा _sas_device *sas_device = शून्य;
		काष्ठा _pcie_device *pcie_device = शून्य;

		sas_device = mpt3sas_get_sdev_by_handle(ioc,
		    le16_to_cpu(scsi_reply->DevHandle));
		अगर (sas_device) अणु
			ioc_warn(ioc, "\tsas_address(0x%016llx), phy(%d)\n",
				 (u64)sas_device->sas_address,
				 sas_device->phy);
			ioc_warn(ioc, "\tenclosure_logical_id(0x%016llx), slot(%d)\n",
				 (u64)sas_device->enclosure_logical_id,
				 sas_device->slot);
			sas_device_put(sas_device);
		पूर्ण
		अगर (!sas_device) अणु
			pcie_device = mpt3sas_get_pdev_by_handle(ioc,
				le16_to_cpu(scsi_reply->DevHandle));
			अगर (pcie_device) अणु
				ioc_warn(ioc, "\tWWID(0x%016llx), port(%d)\n",
					 (अचिन्हित दीर्घ दीर्घ)pcie_device->wwid,
					 pcie_device->port_num);
				अगर (pcie_device->enclosure_handle != 0)
					ioc_warn(ioc, "\tenclosure_logical_id(0x%016llx), slot(%d)\n",
						 (u64)pcie_device->enclosure_logical_id,
						 pcie_device->slot);
				pcie_device_put(pcie_device);
			पूर्ण
		पूर्ण
		अगर (scsi_reply->SCSIState || scsi_reply->SCSIStatus)
			ioc_info(ioc, "\tscsi_state(0x%02x), scsi_status(0x%02x)\n",
				 scsi_reply->SCSIState,
				 scsi_reply->SCSIStatus);
	पूर्ण
पूर्ण

/**
 * mpt3sas_ctl_करोne - ctl module completion routine
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 * Context: none.
 *
 * The callback handler when using ioc->ctl_cb_idx.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
u8
mpt3sas_ctl_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
अणु
	MPI2DefaultReply_t *mpi_reply;
	Mpi2SCSIIOReply_t *scsiio_reply;
	Mpi26NVMeEncapsulatedErrorReply_t *nvme_error_reply;
	स्थिर व्योम *sense_data;
	u32 sz;

	अगर (ioc->ctl_cmds.status == MPT3_CMD_NOT_USED)
		वापस 1;
	अगर (ioc->ctl_cmds.smid != smid)
		वापस 1;
	ioc->ctl_cmds.status |= MPT3_CMD_COMPLETE;
	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (mpi_reply) अणु
		स_नकल(ioc->ctl_cmds.reply, mpi_reply, mpi_reply->MsgLength*4);
		ioc->ctl_cmds.status |= MPT3_CMD_REPLY_VALID;
		/* get sense data */
		अगर (mpi_reply->Function == MPI2_FUNCTION_SCSI_IO_REQUEST ||
		    mpi_reply->Function ==
		    MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH) अणु
			scsiio_reply = (Mpi2SCSIIOReply_t *)mpi_reply;
			अगर (scsiio_reply->SCSIState &
			    MPI2_SCSI_STATE_AUTOSENSE_VALID) अणु
				sz = min_t(u32, SCSI_SENSE_BUFFERSIZE,
				    le32_to_cpu(scsiio_reply->SenseCount));
				sense_data = mpt3sas_base_get_sense_buffer(ioc,
				    smid);
				स_नकल(ioc->ctl_cmds.sense, sense_data, sz);
			पूर्ण
		पूर्ण
		/*
		 * Get Error Response data क्रम NVMe device. The ctl_cmds.sense
		 * buffer is used to store the Error Response data.
		 */
		अगर (mpi_reply->Function == MPI2_FUNCTION_NVME_ENCAPSULATED) अणु
			nvme_error_reply =
			    (Mpi26NVMeEncapsulatedErrorReply_t *)mpi_reply;
			sz = min_t(u32, NVME_ERROR_RESPONSE_SIZE,
			    le16_to_cpu(nvme_error_reply->ErrorResponseCount));
			sense_data = mpt3sas_base_get_sense_buffer(ioc, smid);
			स_नकल(ioc->ctl_cmds.sense, sense_data, sz);
		पूर्ण
	पूर्ण

	_ctl_display_some_debug(ioc, smid, "ctl_done", mpi_reply);
	ioc->ctl_cmds.status &= ~MPT3_CMD_PENDING;
	complete(&ioc->ctl_cmds.करोne);
	वापस 1;
पूर्ण

/**
 * _ctl_check_event_type - determines when an event needs logging
 * @ioc: per adapter object
 * @event: firmware event
 *
 * The biपंचांगask in ioc->event_type[] indicates which events should be
 * be saved in the driver event_log.  This biपंचांगask is set by application.
 *
 * Return: 1 when event should be captured, or zero means no match.
 */
अटल पूर्णांक
_ctl_check_event_type(काष्ठा MPT3SAS_ADAPTER *ioc, u16 event)
अणु
	u16 i;
	u32 desired_event;

	अगर (event >= 128 || !event || !ioc->event_log)
		वापस 0;

	desired_event = (1 << (event % 32));
	अगर (!desired_event)
		desired_event = 1;
	i = event / 32;
	वापस desired_event & ioc->event_type[i];
पूर्ण

/**
 * mpt3sas_ctl_add_to_event_log - add event
 * @ioc: per adapter object
 * @mpi_reply: reply message frame
 */
व्योम
mpt3sas_ctl_add_to_event_log(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventNotअगरicationReply_t *mpi_reply)
अणु
	काष्ठा MPT3_IOCTL_EVENTS *event_log;
	u16 event;
	पूर्णांक i;
	u32 sz, event_data_sz;
	u8 send_aen = 0;

	अगर (!ioc->event_log)
		वापस;

	event = le16_to_cpu(mpi_reply->Event);

	अगर (_ctl_check_event_type(ioc, event)) अणु

		/* insert entry पूर्णांकo circular event_log */
		i = ioc->event_context % MPT3SAS_CTL_EVENT_LOG_SIZE;
		event_log = ioc->event_log;
		event_log[i].event = event;
		event_log[i].context = ioc->event_context++;

		event_data_sz = le16_to_cpu(mpi_reply->EventDataLength)*4;
		sz = min_t(u32, event_data_sz, MPT3_EVENT_DATA_SIZE);
		स_रखो(event_log[i].data, 0, MPT3_EVENT_DATA_SIZE);
		स_नकल(event_log[i].data, mpi_reply->EventData, sz);
		send_aen = 1;
	पूर्ण

	/* This aen_event_पढ़ो_flag flag is set until the
	 * application has पढ़ो the event log.
	 * For MPI2_EVENT_LOG_ENTRY_ADDED, we always notअगरy.
	 */
	अगर (event == MPI2_EVENT_LOG_ENTRY_ADDED ||
	    (send_aen && !ioc->aen_event_पढ़ो_flag)) अणु
		ioc->aen_event_पढ़ो_flag = 1;
		wake_up_पूर्णांकerruptible(&ctl_poll_रुको);
		अगर (async_queue)
			समाप्त_fasync(&async_queue, SIGIO, POLL_IN);
	पूर्ण
पूर्ण

/**
 * mpt3sas_ctl_event_callback - firmware event handler (called at ISR समय)
 * @ioc: per adapter object
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 * Context: पूर्णांकerrupt.
 *
 * This function merely adds a new work task पूर्णांकo ioc->firmware_event_thपढ़ो.
 * The tasks are worked from _firmware_event_work in user context.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
u8
mpt3sas_ctl_event_callback(काष्ठा MPT3SAS_ADAPTER *ioc, u8 msix_index,
	u32 reply)
अणु
	Mpi2EventNotअगरicationReply_t *mpi_reply;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (mpi_reply)
		mpt3sas_ctl_add_to_event_log(ioc, mpi_reply);
	वापस 1;
पूर्ण

/**
 * _ctl_verअगरy_adapter - validates ioc_number passed from application
 * @ioc_number: ?
 * @iocpp: The ioc poपूर्णांकer is वापसed in this.
 * @mpi_version: will be MPI2_VERSION क्रम mpt2ctl ioctl device &
 * MPI25_VERSION | MPI26_VERSION क्रम mpt3ctl ioctl device.
 *
 * Return: (-1) means error, अन्यथा ioc_number.
 */
अटल पूर्णांक
_ctl_verअगरy_adapter(पूर्णांक ioc_number, काष्ठा MPT3SAS_ADAPTER **iocpp,
							पूर्णांक mpi_version)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc;
	पूर्णांक version = 0;
	/* global ioc lock to protect controller on list operations */
	spin_lock(&gioc_lock);
	list_क्रम_each_entry(ioc, &mpt3sas_ioc_list, list) अणु
		अगर (ioc->id != ioc_number)
			जारी;
		/* Check whether this ioctl command is from right
		 * ioctl device or not, अगर not जारी the search.
		 */
		version = ioc->hba_mpi_version_beदीर्घed;
		/* MPI25_VERSION and MPI26_VERSION uses same ioctl
		 * device.
		 */
		अगर (mpi_version == (MPI25_VERSION | MPI26_VERSION)) अणु
			अगर ((version == MPI25_VERSION) ||
				(version == MPI26_VERSION))
				जाओ out;
			अन्यथा
				जारी;
		पूर्ण अन्यथा अणु
			अगर (version != mpi_version)
				जारी;
		पूर्ण
out:
		spin_unlock(&gioc_lock);
		*iocpp = ioc;
		वापस ioc_number;
	पूर्ण
	spin_unlock(&gioc_lock);
	*iocpp = शून्य;
	वापस -1;
पूर्ण

/**
 * mpt3sas_ctl_pre_reset_handler - reset callback handler (क्रम ctl)
 * @ioc: per adapter object
 *
 * The handler क्रम करोing any required cleanup or initialization.
 */
व्योम mpt3sas_ctl_pre_reset_handler(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक i;
	u8 issue_reset;

	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "%s: MPT3_IOC_PRE_RESET\n", __func__));
	क्रम (i = 0; i < MPI2_DIAG_BUF_TYPE_COUNT; i++) अणु
		अगर (!(ioc->diag_buffer_status[i] &
		      MPT3_DIAG_BUFFER_IS_REGISTERED))
			जारी;
		अगर ((ioc->diag_buffer_status[i] &
		     MPT3_DIAG_BUFFER_IS_RELEASED))
			जारी;

		/*
		 * add a log message to indicate the release
		 */
		ioc_info(ioc,
		    "%s: Releasing the trace buffer due to adapter reset.",
		    __func__);
		ioc->htb_rel.buffer_rel_condition =
		    MPT3_DIAG_BUFFER_REL_TRIGGER;
		mpt3sas_send_diag_release(ioc, i, &issue_reset);
	पूर्ण
पूर्ण

/**
 * mpt3sas_ctl_clear_outstanding_ioctls - clears outstanding ioctl cmd.
 * @ioc: per adapter object
 *
 * The handler क्रम करोing any required cleanup or initialization.
 */
व्योम mpt3sas_ctl_clear_outstanding_ioctls(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	dपंचांगprपूर्णांकk(ioc,
	    ioc_info(ioc, "%s: clear outstanding ioctl cmd\n", __func__));
	अगर (ioc->ctl_cmds.status & MPT3_CMD_PENDING) अणु
		ioc->ctl_cmds.status |= MPT3_CMD_RESET;
		mpt3sas_base_मुक्त_smid(ioc, ioc->ctl_cmds.smid);
		complete(&ioc->ctl_cmds.करोne);
	पूर्ण
पूर्ण

/**
 * mpt3sas_ctl_reset_करोne_handler - reset callback handler (क्रम ctl)
 * @ioc: per adapter object
 *
 * The handler क्रम करोing any required cleanup or initialization.
 */
व्योम mpt3sas_ctl_reset_करोne_handler(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक i;

	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "%s: MPT3_IOC_DONE_RESET\n", __func__));

	क्रम (i = 0; i < MPI2_DIAG_BUF_TYPE_COUNT; i++) अणु
		अगर (!(ioc->diag_buffer_status[i] &
		      MPT3_DIAG_BUFFER_IS_REGISTERED))
			जारी;
		अगर ((ioc->diag_buffer_status[i] &
		     MPT3_DIAG_BUFFER_IS_RELEASED))
			जारी;
		ioc->diag_buffer_status[i] |=
			MPT3_DIAG_BUFFER_IS_DIAG_RESET;
	पूर्ण
पूर्ण

/**
 * _ctl_fasync -
 * @fd: ?
 * @filep: ?
 * @mode: ?
 *
 * Called when application request fasyn callback handler.
 */
अटल पूर्णांक
_ctl_fasync(पूर्णांक fd, काष्ठा file *filep, पूर्णांक mode)
अणु
	वापस fasync_helper(fd, filep, mode, &async_queue);
पूर्ण

/**
 * _ctl_poll -
 * @filep: ?
 * @रुको: ?
 *
 */
अटल __poll_t
_ctl_poll(काष्ठा file *filep, poll_table *रुको)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc;

	poll_रुको(filep, &ctl_poll_रुको, रुको);

	/* global ioc lock to protect controller on list operations */
	spin_lock(&gioc_lock);
	list_क्रम_each_entry(ioc, &mpt3sas_ioc_list, list) अणु
		अगर (ioc->aen_event_पढ़ो_flag) अणु
			spin_unlock(&gioc_lock);
			वापस EPOLLIN | EPOLLRDNORM;
		पूर्ण
	पूर्ण
	spin_unlock(&gioc_lock);
	वापस 0;
पूर्ण

/**
 * _ctl_set_task_mid - assign an active smid to पंचांग request
 * @ioc: per adapter object
 * @karg: (काष्ठा mpt3_ioctl_command)
 * @पंचांग_request: poपूर्णांकer to mf from user space
 *
 * Return: 0 when an smid अगर found, अन्यथा fail.
 * during failure, the reply frame is filled.
 */
अटल पूर्णांक
_ctl_set_task_mid(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा mpt3_ioctl_command *karg,
	Mpi2SCSITaskManagementRequest_t *पंचांग_request)
अणु
	u8 found = 0;
	u16 smid;
	u16 handle;
	काष्ठा scsi_cmnd *scmd;
	काष्ठा MPT3SAS_DEVICE *priv_data;
	Mpi2SCSITaskManagementReply_t *पंचांग_reply;
	u32 sz;
	u32 lun;
	अक्षर *desc = शून्य;

	अगर (पंचांग_request->TaskType == MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK)
		desc = "abort_task";
	अन्यथा अगर (पंचांग_request->TaskType == MPI2_SCSITASKMGMT_TASKTYPE_QUERY_TASK)
		desc = "query_task";
	अन्यथा
		वापस 0;

	lun = scsilun_to_पूर्णांक((काष्ठा scsi_lun *)पंचांग_request->LUN);

	handle = le16_to_cpu(पंचांग_request->DevHandle);
	क्रम (smid = ioc->scsiio_depth; smid && !found; smid--) अणु
		काष्ठा scsiio_tracker *st;

		scmd = mpt3sas_scsih_scsi_lookup_get(ioc, smid);
		अगर (!scmd)
			जारी;
		अगर (lun != scmd->device->lun)
			जारी;
		priv_data = scmd->device->hostdata;
		अगर (priv_data->sas_target == शून्य)
			जारी;
		अगर (priv_data->sas_target->handle != handle)
			जारी;
		st = scsi_cmd_priv(scmd);

		/*
		 * If the given TaskMID from the user space is zero, then the
		 * first outstanding smid will be picked up.  Otherwise,
		 * targeted smid will be the one.
		 */
		अगर (!पंचांग_request->TaskMID || पंचांग_request->TaskMID == st->smid) अणु
			पंचांग_request->TaskMID = cpu_to_le16(st->smid);
			found = 1;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		dctlprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: handle(0x%04x), lun(%d), no active mid!!\n",
				    desc, le16_to_cpu(पंचांग_request->DevHandle),
				    lun));
		पंचांग_reply = ioc->ctl_cmds.reply;
		पंचांग_reply->DevHandle = पंचांग_request->DevHandle;
		पंचांग_reply->Function = MPI2_FUNCTION_SCSI_TASK_MGMT;
		पंचांग_reply->TaskType = पंचांग_request->TaskType;
		पंचांग_reply->MsgLength = माप(Mpi2SCSITaskManagementReply_t)/4;
		पंचांग_reply->VP_ID = पंचांग_request->VP_ID;
		पंचांग_reply->VF_ID = पंचांग_request->VF_ID;
		sz = min_t(u32, karg->max_reply_bytes, ioc->reply_sz);
		अगर (copy_to_user(karg->reply_frame_buf_ptr, ioc->ctl_cmds.reply,
		    sz))
			pr_err("failure at %s:%d/%s()!\n", __खाता__,
			    __LINE__, __func__);
		वापस 1;
	पूर्ण

	dctlprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: handle(0x%04x), lun(%d), task_mid(%d)\n",
			    desc, le16_to_cpu(पंचांग_request->DevHandle), lun,
			    le16_to_cpu(पंचांग_request->TaskMID)));
	वापस 0;
पूर्ण

/**
 * _ctl_करो_mpt_command - मुख्य handler क्रम MPT3COMMAND opcode
 * @ioc: per adapter object
 * @karg: (काष्ठा mpt3_ioctl_command)
 * @mf: poपूर्णांकer to mf in user space
 */
अटल दीर्घ
_ctl_करो_mpt_command(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा mpt3_ioctl_command karg,
	व्योम __user *mf)
अणु
	MPI2RequestHeader_t *mpi_request = शून्य, *request;
	MPI2DefaultReply_t *mpi_reply;
	Mpi26NVMeEncapsulatedRequest_t *nvme_encap_request = शून्य;
	काष्ठा _pcie_device *pcie_device = शून्य;
	u16 smid;
	अचिन्हित दीर्घ समयout;
	u8 issue_reset;
	u32 sz, sz_arg;
	व्योम *psge;
	व्योम *data_out = शून्य;
	dma_addr_t data_out_dma = 0;
	माप_प्रकार data_out_sz = 0;
	व्योम *data_in = शून्य;
	dma_addr_t data_in_dma = 0;
	माप_प्रकार data_in_sz = 0;
	दीर्घ ret;
	u16 device_handle = MPT3SAS_INVALID_DEVICE_HANDLE;

	issue_reset = 0;

	अगर (ioc->ctl_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: ctl_cmd in use\n", __func__);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = mpt3sas_रुको_क्रम_ioc(ioc,	IOC_OPERATIONAL_WAIT_COUNT);
	अगर (ret)
		जाओ out;

	mpi_request = kzalloc(ioc->request_sz, GFP_KERNEL);
	अगर (!mpi_request) अणु
		ioc_err(ioc, "%s: failed obtaining a memory for mpi_request\n",
			__func__);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Check क्रम overflow and wraparound */
	अगर (karg.data_sge_offset * 4 > ioc->request_sz ||
	    karg.data_sge_offset > (अच_पूर्णांक_उच्च / 4)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* copy in request message frame from user */
	अगर (copy_from_user(mpi_request, mf, karg.data_sge_offset*4)) अणु
		pr_err("failure at %s:%d/%s()!\n", __खाता__, __LINE__,
		    __func__);
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (mpi_request->Function == MPI2_FUNCTION_SCSI_TASK_MGMT) अणु
		smid = mpt3sas_base_get_smid_hpr(ioc, ioc->ctl_cb_idx);
		अगर (!smid) अणु
			ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
			ret = -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Use first reserved smid क्रम passthrough ioctls */
		smid = ioc->scsiio_depth - INTERNAL_SCSIIO_CMDS_COUNT + 1;
	पूर्ण

	ret = 0;
	ioc->ctl_cmds.status = MPT3_CMD_PENDING;
	स_रखो(ioc->ctl_cmds.reply, 0, ioc->reply_sz);
	request = mpt3sas_base_get_msg_frame(ioc, smid);
	स_रखो(request, 0, ioc->request_sz);
	स_नकल(request, mpi_request, karg.data_sge_offset*4);
	ioc->ctl_cmds.smid = smid;
	data_out_sz = karg.data_out_size;
	data_in_sz = karg.data_in_size;

	अगर (mpi_request->Function == MPI2_FUNCTION_SCSI_IO_REQUEST ||
	    mpi_request->Function == MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH ||
	    mpi_request->Function == MPI2_FUNCTION_SCSI_TASK_MGMT ||
	    mpi_request->Function == MPI2_FUNCTION_SATA_PASSTHROUGH ||
	    mpi_request->Function == MPI2_FUNCTION_NVME_ENCAPSULATED) अणु

		device_handle = le16_to_cpu(mpi_request->FunctionDependent1);
		अगर (!device_handle || (device_handle >
		    ioc->facts.MaxDevHandle)) अणु
			ret = -EINVAL;
			mpt3sas_base_मुक्त_smid(ioc, smid);
			जाओ out;
		पूर्ण
	पूर्ण

	/* obtain dma-able memory क्रम data transfer */
	अगर (data_out_sz) /* WRITE */ अणु
		data_out = dma_alloc_coherent(&ioc->pdev->dev, data_out_sz,
				&data_out_dma, GFP_KERNEL);
		अगर (!data_out) अणु
			pr_err("failure at %s:%d/%s()!\n", __खाता__,
			    __LINE__, __func__);
			ret = -ENOMEM;
			mpt3sas_base_मुक्त_smid(ioc, smid);
			जाओ out;
		पूर्ण
		अगर (copy_from_user(data_out, karg.data_out_buf_ptr,
			data_out_sz)) अणु
			pr_err("failure at %s:%d/%s()!\n", __खाता__,
			    __LINE__, __func__);
			ret =  -EFAULT;
			mpt3sas_base_मुक्त_smid(ioc, smid);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (data_in_sz) /* READ */ अणु
		data_in = dma_alloc_coherent(&ioc->pdev->dev, data_in_sz,
				&data_in_dma, GFP_KERNEL);
		अगर (!data_in) अणु
			pr_err("failure at %s:%d/%s()!\n", __खाता__,
			    __LINE__, __func__);
			ret = -ENOMEM;
			mpt3sas_base_मुक्त_smid(ioc, smid);
			जाओ out;
		पूर्ण
	पूर्ण

	psge = (व्योम *)request + (karg.data_sge_offset*4);

	/* send command to firmware */
	_ctl_display_some_debug(ioc, smid, "ctl_request", शून्य);

	init_completion(&ioc->ctl_cmds.करोne);
	चयन (mpi_request->Function) अणु
	हाल MPI2_FUNCTION_NVME_ENCAPSULATED:
	अणु
		nvme_encap_request = (Mpi26NVMeEncapsulatedRequest_t *)request;
		अगर (!ioc->pcie_sg_lookup) अणु
			dपंचांगprपूर्णांकk(ioc, ioc_info(ioc,
			    "HBA doesn't support NVMe. Rejecting NVMe Encapsulated request.\n"
			    ));

			अगर (ioc->logging_level & MPT_DEBUG_TM)
				_debug_dump_mf(nvme_encap_request,
				    ioc->request_sz/4);
			mpt3sas_base_मुक्त_smid(ioc, smid);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		/*
		 * Get the Physical Address of the sense buffer.
		 * Use Error Response buffer address field to hold the sense
		 * buffer address.
		 * Clear the पूर्णांकernal sense buffer, which will potentially hold
		 * the Completion Queue Entry on वापस, or 0 अगर no Entry.
		 * Build the PRPs and set direction bits.
		 * Send the request.
		 */
		nvme_encap_request->ErrorResponseBaseAddress =
		    cpu_to_le64(ioc->sense_dma & 0xFFFFFFFF00000000UL);
		nvme_encap_request->ErrorResponseBaseAddress |=
		   cpu_to_le64(le32_to_cpu(
		   mpt3sas_base_get_sense_buffer_dma(ioc, smid)));
		nvme_encap_request->ErrorResponseAllocationLength =
					cpu_to_le16(NVME_ERROR_RESPONSE_SIZE);
		स_रखो(ioc->ctl_cmds.sense, 0, NVME_ERROR_RESPONSE_SIZE);
		ioc->build_nvme_prp(ioc, smid, nvme_encap_request,
		    data_out_dma, data_out_sz, data_in_dma, data_in_sz);
		अगर (test_bit(device_handle, ioc->device_हटाओ_in_progress)) अणु
			dपंचांगprपूर्णांकk(ioc,
				  ioc_info(ioc, "handle(0x%04x): ioctl failed due to device removal in progress\n",
					   device_handle));
			mpt3sas_base_मुक्त_smid(ioc, smid);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		mpt3sas_base_put_smid_nvme_encap(ioc, smid);
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_SCSI_IO_REQUEST:
	हाल MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH:
	अणु
		Mpi2SCSIIORequest_t *scsiio_request =
		    (Mpi2SCSIIORequest_t *)request;
		scsiio_request->SenseBufferLength = SCSI_SENSE_BUFFERSIZE;
		scsiio_request->SenseBufferLowAddress =
		    mpt3sas_base_get_sense_buffer_dma(ioc, smid);
		स_रखो(ioc->ctl_cmds.sense, 0, SCSI_SENSE_BUFFERSIZE);
		अगर (test_bit(device_handle, ioc->device_हटाओ_in_progress)) अणु
			dपंचांगprपूर्णांकk(ioc,
				  ioc_info(ioc, "handle(0x%04x) :ioctl failed due to device removal in progress\n",
					   device_handle));
			mpt3sas_base_मुक्त_smid(ioc, smid);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ioc->build_sg(ioc, psge, data_out_dma, data_out_sz,
		    data_in_dma, data_in_sz);
		अगर (mpi_request->Function == MPI2_FUNCTION_SCSI_IO_REQUEST)
			ioc->put_smid_scsi_io(ioc, smid, device_handle);
		अन्यथा
			ioc->put_smid_शेष(ioc, smid);
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_SCSI_TASK_MGMT:
	अणु
		Mpi2SCSITaskManagementRequest_t *पंचांग_request =
		    (Mpi2SCSITaskManagementRequest_t *)request;

		dपंचांगprपूर्णांकk(ioc,
			  ioc_info(ioc, "TASK_MGMT: handle(0x%04x), task_type(0x%02x)\n",
				   le16_to_cpu(पंचांग_request->DevHandle),
				   पंचांग_request->TaskType));
		ioc->got_task_पात_from_ioctl = 1;
		अगर (पंचांग_request->TaskType ==
		    MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK ||
		    पंचांग_request->TaskType ==
		    MPI2_SCSITASKMGMT_TASKTYPE_QUERY_TASK) अणु
			अगर (_ctl_set_task_mid(ioc, &karg, पंचांग_request)) अणु
				mpt3sas_base_मुक्त_smid(ioc, smid);
				ioc->got_task_पात_from_ioctl = 0;
				जाओ out;
			पूर्ण
		पूर्ण
		ioc->got_task_पात_from_ioctl = 0;

		अगर (test_bit(device_handle, ioc->device_हटाओ_in_progress)) अणु
			dपंचांगprपूर्णांकk(ioc,
				  ioc_info(ioc, "handle(0x%04x) :ioctl failed due to device removal in progress\n",
					   device_handle));
			mpt3sas_base_मुक्त_smid(ioc, smid);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		mpt3sas_scsih_set_पंचांग_flag(ioc, le16_to_cpu(
		    पंचांग_request->DevHandle));
		ioc->build_sg_mpi(ioc, psge, data_out_dma, data_out_sz,
		    data_in_dma, data_in_sz);
		ioc->put_smid_hi_priority(ioc, smid, 0);
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_SMP_PASSTHROUGH:
	अणु
		Mpi2SmpPassthroughRequest_t *smp_request =
		    (Mpi2SmpPassthroughRequest_t *)mpi_request;
		u8 *data;

		अगर (!ioc->multipath_on_hba) अणु
			/* ioc determines which port to use */
			smp_request->PhysicalPort = 0xFF;
		पूर्ण
		अगर (smp_request->PassthroughFlags &
		    MPI2_SMP_PT_REQ_PT_FLAGS_IMMEDIATE)
			data = (u8 *)&smp_request->SGL;
		अन्यथा अणु
			अगर (unlikely(data_out == शून्य)) अणु
				pr_err("failure at %s:%d/%s()!\n",
				    __खाता__, __LINE__, __func__);
				mpt3sas_base_मुक्त_smid(ioc, smid);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			data = data_out;
		पूर्ण

		अगर (data[1] == 0x91 && (data[10] == 1 || data[10] == 2)) अणु
			ioc->ioc_link_reset_in_progress = 1;
			ioc->ignore_loginfos = 1;
		पूर्ण
		ioc->build_sg(ioc, psge, data_out_dma, data_out_sz, data_in_dma,
		    data_in_sz);
		ioc->put_smid_शेष(ioc, smid);
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_SATA_PASSTHROUGH:
	अणु
		अगर (test_bit(device_handle, ioc->device_हटाओ_in_progress)) अणु
			dपंचांगprपूर्णांकk(ioc,
				  ioc_info(ioc, "handle(0x%04x) :ioctl failed due to device removal in progress\n",
					   device_handle));
			mpt3sas_base_मुक्त_smid(ioc, smid);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ioc->build_sg(ioc, psge, data_out_dma, data_out_sz, data_in_dma,
		    data_in_sz);
		ioc->put_smid_शेष(ioc, smid);
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_FW_DOWNLOAD:
	हाल MPI2_FUNCTION_FW_UPLOAD:
	अणु
		ioc->build_sg(ioc, psge, data_out_dma, data_out_sz, data_in_dma,
		    data_in_sz);
		ioc->put_smid_शेष(ioc, smid);
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_TOOLBOX:
	अणु
		Mpi2ToolboxCleanRequest_t *toolbox_request =
			(Mpi2ToolboxCleanRequest_t *)mpi_request;

		अगर ((toolbox_request->Tool == MPI2_TOOLBOX_DIAGNOSTIC_CLI_TOOL)
		    || (toolbox_request->Tool ==
		    MPI26_TOOLBOX_BACKEND_PCIE_LANE_MARGIN))
			ioc->build_sg(ioc, psge, data_out_dma, data_out_sz,
				data_in_dma, data_in_sz);
		अन्यथा अगर (toolbox_request->Tool ==
				MPI2_TOOLBOX_MEMORY_MOVE_TOOL) अणु
			Mpi2ToolboxMemMoveRequest_t *mem_move_request =
					(Mpi2ToolboxMemMoveRequest_t *)request;
			Mpi2SGESimple64_t पंचांगp, *src = शून्य, *dst = शून्य;

			ioc->build_sg_mpi(ioc, psge, data_out_dma,
					data_out_sz, data_in_dma, data_in_sz);
			अगर (data_out_sz && !data_in_sz) अणु
				dst =
				    (Mpi2SGESimple64_t *)&mem_move_request->SGL;
				src = (व्योम *)dst + ioc->sge_size;

				स_नकल(&पंचांगp, src, ioc->sge_size);
				स_नकल(src, dst, ioc->sge_size);
				स_नकल(dst, &पंचांगp, ioc->sge_size);
			पूर्ण
			अगर (ioc->logging_level & MPT_DEBUG_TM) अणु
				ioc_info(ioc,
				  "Mpi2ToolboxMemMoveRequest_t request msg\n");
				_debug_dump_mf(mem_move_request,
							ioc->request_sz/4);
			पूर्ण
		पूर्ण अन्यथा
			ioc->build_sg_mpi(ioc, psge, data_out_dma, data_out_sz,
			    data_in_dma, data_in_sz);
		ioc->put_smid_शेष(ioc, smid);
		अवरोध;
	पूर्ण
	हाल MPI2_FUNCTION_SAS_IO_UNIT_CONTROL:
	अणु
		Mpi2SasIoUnitControlRequest_t *sasiounit_request =
		    (Mpi2SasIoUnitControlRequest_t *)mpi_request;

		अगर (sasiounit_request->Operation == MPI2_SAS_OP_PHY_HARD_RESET
		    || sasiounit_request->Operation ==
		    MPI2_SAS_OP_PHY_LINK_RESET) अणु
			ioc->ioc_link_reset_in_progress = 1;
			ioc->ignore_loginfos = 1;
		पूर्ण
		/* drop to शेष हाल क्रम posting the request */
	पूर्ण
		fallthrough;
	शेष:
		ioc->build_sg_mpi(ioc, psge, data_out_dma, data_out_sz,
		    data_in_dma, data_in_sz);
		ioc->put_smid_शेष(ioc, smid);
		अवरोध;
	पूर्ण

	अगर (karg.समयout < MPT3_IOCTL_DEFAULT_TIMEOUT)
		समयout = MPT3_IOCTL_DEFAULT_TIMEOUT;
	अन्यथा
		समयout = karg.समयout;
	रुको_क्रम_completion_समयout(&ioc->ctl_cmds.करोne, समयout*HZ);
	अगर (mpi_request->Function == MPI2_FUNCTION_SCSI_TASK_MGMT) अणु
		Mpi2SCSITaskManagementRequest_t *पंचांग_request =
		    (Mpi2SCSITaskManagementRequest_t *)mpi_request;
		mpt3sas_scsih_clear_पंचांग_flag(ioc, le16_to_cpu(
		    पंचांग_request->DevHandle));
		mpt3sas_trigger_master(ioc, MASTER_TRIGGER_TASK_MANAGMENT);
	पूर्ण अन्यथा अगर ((mpi_request->Function == MPI2_FUNCTION_SMP_PASSTHROUGH ||
	    mpi_request->Function == MPI2_FUNCTION_SAS_IO_UNIT_CONTROL) &&
		ioc->ioc_link_reset_in_progress) अणु
		ioc->ioc_link_reset_in_progress = 0;
		ioc->ignore_loginfos = 0;
	पूर्ण
	अगर (!(ioc->ctl_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc,
		    ioc->ctl_cmds.status, mpi_request,
		    karg.data_sge_offset, issue_reset);
		जाओ issue_host_reset;
	पूर्ण

	mpi_reply = ioc->ctl_cmds.reply;

	अगर (mpi_reply->Function == MPI2_FUNCTION_SCSI_TASK_MGMT &&
	    (ioc->logging_level & MPT_DEBUG_TM)) अणु
		Mpi2SCSITaskManagementReply_t *पंचांग_reply =
		    (Mpi2SCSITaskManagementReply_t *)mpi_reply;

		ioc_info(ioc, "TASK_MGMT: IOCStatus(0x%04x), IOCLogInfo(0x%08x), TerminationCount(0x%08x)\n",
			 le16_to_cpu(पंचांग_reply->IOCStatus),
			 le32_to_cpu(पंचांग_reply->IOCLogInfo),
			 le32_to_cpu(पंचांग_reply->TerminationCount));
	पूर्ण

	/* copy out xdata to user */
	अगर (data_in_sz) अणु
		अगर (copy_to_user(karg.data_in_buf_ptr, data_in,
		    data_in_sz)) अणु
			pr_err("failure at %s:%d/%s()!\n", __खाता__,
			    __LINE__, __func__);
			ret = -ENODATA;
			जाओ out;
		पूर्ण
	पूर्ण

	/* copy out reply message frame to user */
	अगर (karg.max_reply_bytes) अणु
		sz = min_t(u32, karg.max_reply_bytes, ioc->reply_sz);
		अगर (copy_to_user(karg.reply_frame_buf_ptr, ioc->ctl_cmds.reply,
		    sz)) अणु
			pr_err("failure at %s:%d/%s()!\n", __खाता__,
			    __LINE__, __func__);
			ret = -ENODATA;
			जाओ out;
		पूर्ण
	पूर्ण

	/* copy out sense/NVMe Error Response to user */
	अगर (karg.max_sense_bytes && (mpi_request->Function ==
	    MPI2_FUNCTION_SCSI_IO_REQUEST || mpi_request->Function ==
	    MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH || mpi_request->Function ==
	    MPI2_FUNCTION_NVME_ENCAPSULATED)) अणु
		अगर (karg.sense_data_ptr == शून्य) अणु
			ioc_info(ioc, "Response buffer provided by application is NULL; Response data will not be returned\n");
			जाओ out;
		पूर्ण
		sz_arg = (mpi_request->Function ==
		MPI2_FUNCTION_NVME_ENCAPSULATED) ? NVME_ERROR_RESPONSE_SIZE :
							SCSI_SENSE_BUFFERSIZE;
		sz = min_t(u32, karg.max_sense_bytes, sz_arg);
		अगर (copy_to_user(karg.sense_data_ptr, ioc->ctl_cmds.sense,
		    sz)) अणु
			pr_err("failure at %s:%d/%s()!\n", __खाता__,
				__LINE__, __func__);
			ret = -ENODATA;
			जाओ out;
		पूर्ण
	पूर्ण

 issue_host_reset:
	अगर (issue_reset) अणु
		ret = -ENODATA;
		अगर ((mpi_request->Function == MPI2_FUNCTION_SCSI_IO_REQUEST ||
		    mpi_request->Function ==
		    MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH ||
		    mpi_request->Function == MPI2_FUNCTION_SATA_PASSTHROUGH)) अणु
			ioc_info(ioc, "issue target reset: handle = (0x%04x)\n",
				 le16_to_cpu(mpi_request->FunctionDependent1));
			mpt3sas_halt_firmware(ioc);
			pcie_device = mpt3sas_get_pdev_by_handle(ioc,
				le16_to_cpu(mpi_request->FunctionDependent1));
			अगर (pcie_device && (!ioc->पंचांग_custom_handling) &&
			    (!(mpt3sas_scsih_is_pcie_scsi_device(
			    pcie_device->device_info))))
				mpt3sas_scsih_issue_locked_पंचांग(ioc,
				  le16_to_cpu(mpi_request->FunctionDependent1),
				  0, 0, 0,
				  MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET, 0,
				  0, pcie_device->reset_समयout,
			MPI26_SCSITASKMGMT_MSGFLAGS_PROTOCOL_LVL_RST_PCIE);
			अन्यथा
				mpt3sas_scsih_issue_locked_पंचांग(ioc,
				  le16_to_cpu(mpi_request->FunctionDependent1),
				  0, 0, 0,
				  MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET, 0,
				  0, 30, MPI2_SCSITASKMGMT_MSGFLAGS_LINK_RESET);
		पूर्ण अन्यथा
			mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	पूर्ण

 out:
	अगर (pcie_device)
		pcie_device_put(pcie_device);

	/* मुक्त memory associated with sg buffers */
	अगर (data_in)
		dma_मुक्त_coherent(&ioc->pdev->dev, data_in_sz, data_in,
		    data_in_dma);

	अगर (data_out)
		dma_मुक्त_coherent(&ioc->pdev->dev, data_out_sz, data_out,
		    data_out_dma);

	kमुक्त(mpi_request);
	ioc->ctl_cmds.status = MPT3_CMD_NOT_USED;
	वापस ret;
पूर्ण

/**
 * _ctl_getiocinfo - मुख्य handler क्रम MPT3IOCINFO opcode
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 */
अटल दीर्घ
_ctl_getiocinfo(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_ioctl_iocinfo karg;

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s: enter\n",
				 __func__));

	स_रखो(&karg, 0 , माप(karg));
	अगर (ioc->pfacts)
		karg.port_number = ioc->pfacts[0].PortNumber;
	karg.hw_rev = ioc->pdev->revision;
	karg.pci_id = ioc->pdev->device;
	karg.subप्रणाली_device = ioc->pdev->subप्रणाली_device;
	karg.subप्रणाली_venकरोr = ioc->pdev->subप्रणाली_venकरोr;
	karg.pci_inक्रमmation.u.bits.bus = ioc->pdev->bus->number;
	karg.pci_inक्रमmation.u.bits.device = PCI_SLOT(ioc->pdev->devfn);
	karg.pci_inक्रमmation.u.bits.function = PCI_FUNC(ioc->pdev->devfn);
	karg.pci_inक्रमmation.segment_id = pci_करोमुख्य_nr(ioc->pdev->bus);
	karg.firmware_version = ioc->facts.FWVersion.Word;
	म_नकल(karg.driver_version, ioc->driver_name);
	म_जोड़ो(karg.driver_version, "-");
	चयन  (ioc->hba_mpi_version_beदीर्घed) अणु
	हाल MPI2_VERSION:
		अगर (ioc->is_warpdrive)
			karg.adapter_type = MPT2_IOCTL_INTERFACE_SAS2_SSS6200;
		अन्यथा
			karg.adapter_type = MPT2_IOCTL_INTERFACE_SAS2;
		म_जोड़ो(karg.driver_version, MPT2SAS_DRIVER_VERSION);
		अवरोध;
	हाल MPI25_VERSION:
	हाल MPI26_VERSION:
		अगर (ioc->is_gen35_ioc)
			karg.adapter_type = MPT3_IOCTL_INTERFACE_SAS35;
		अन्यथा
			karg.adapter_type = MPT3_IOCTL_INTERFACE_SAS3;
		म_जोड़ो(karg.driver_version, MPT3SAS_DRIVER_VERSION);
		अवरोध;
	पूर्ण
	karg.bios_version = le32_to_cpu(ioc->bios_pg3.BiosVersion);

	अगर (copy_to_user(arg, &karg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * _ctl_eventquery - मुख्य handler क्रम MPT3EVENTQUERY opcode
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 */
अटल दीर्घ
_ctl_eventquery(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_ioctl_eventquery karg;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s: enter\n",
				 __func__));

	karg.event_entries = MPT3SAS_CTL_EVENT_LOG_SIZE;
	स_नकल(karg.event_types, ioc->event_type,
	    MPI2_EVENT_NOTIFY_EVENTMASK_WORDS * माप(u32));

	अगर (copy_to_user(arg, &karg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * _ctl_eventenable - मुख्य handler क्रम MPT3EVENTENABLE opcode
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 */
अटल दीर्घ
_ctl_eventenable(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_ioctl_eventenable karg;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s: enter\n",
				 __func__));

	स_नकल(ioc->event_type, karg.event_types,
	    MPI2_EVENT_NOTIFY_EVENTMASK_WORDS * माप(u32));
	mpt3sas_base_validate_event_type(ioc, ioc->event_type);

	अगर (ioc->event_log)
		वापस 0;
	/* initialize event_log */
	ioc->event_context = 0;
	ioc->aen_event_पढ़ो_flag = 0;
	ioc->event_log = kसुस्मृति(MPT3SAS_CTL_EVENT_LOG_SIZE,
	    माप(काष्ठा MPT3_IOCTL_EVENTS), GFP_KERNEL);
	अगर (!ioc->event_log) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * _ctl_eventreport - मुख्य handler क्रम MPT3EVENTREPORT opcode
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 */
अटल दीर्घ
_ctl_eventreport(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_ioctl_eventreport karg;
	u32 number_bytes, max_events, max;
	काष्ठा mpt3_ioctl_eventreport __user *uarg = arg;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s: enter\n",
				 __func__));

	number_bytes = karg.hdr.max_data_size -
	    माप(काष्ठा mpt3_ioctl_header);
	max_events = number_bytes/माप(काष्ठा MPT3_IOCTL_EVENTS);
	max = min_t(u32, MPT3SAS_CTL_EVENT_LOG_SIZE, max_events);

	/* If fewer than 1 event is requested, there must have
	 * been some type of error.
	 */
	अगर (!max || !ioc->event_log)
		वापस -ENODATA;

	number_bytes = max * माप(काष्ठा MPT3_IOCTL_EVENTS);
	अगर (copy_to_user(uarg->event_data, ioc->event_log, number_bytes)) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	/* reset flag so SIGIO can restart */
	ioc->aen_event_पढ़ो_flag = 0;
	वापस 0;
पूर्ण

/**
 * _ctl_करो_reset - मुख्य handler क्रम MPT3HARDRESET opcode
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 */
अटल दीर्घ
_ctl_करो_reset(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_ioctl_diag_reset karg;
	पूर्णांक retval;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (ioc->shost_recovery || ioc->pci_error_recovery ||
	    ioc->is_driver_loading)
		वापस -EAGAIN;

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s: enter\n",
				 __func__));

	ioc->reset_from_user = 1;
	retval = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	ioc_info(ioc,
	    "Ioctl: host reset: %s\n", ((!retval) ? "SUCCESS" : "FAILED"));
	वापस 0;
पूर्ण

/**
 * _ctl_btdh_search_sas_device - searching क्रम sas device
 * @ioc: per adapter object
 * @btdh: btdh ioctl payload
 */
अटल पूर्णांक
_ctl_btdh_search_sas_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा mpt3_ioctl_btdh_mapping *btdh)
अणु
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (list_empty(&ioc->sas_device_list))
		वापस rc;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	list_क्रम_each_entry(sas_device, &ioc->sas_device_list, list) अणु
		अगर (btdh->bus == 0xFFFFFFFF && btdh->id == 0xFFFFFFFF &&
		    btdh->handle == sas_device->handle) अणु
			btdh->bus = sas_device->channel;
			btdh->id = sas_device->id;
			rc = 1;
			जाओ out;
		पूर्ण अन्यथा अगर (btdh->bus == sas_device->channel && btdh->id ==
		    sas_device->id && btdh->handle == 0xFFFF) अणु
			btdh->handle = sas_device->handle;
			rc = 1;
			जाओ out;
		पूर्ण
	पूर्ण
 out:
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	वापस rc;
पूर्ण

/**
 * _ctl_btdh_search_pcie_device - searching क्रम pcie device
 * @ioc: per adapter object
 * @btdh: btdh ioctl payload
 */
अटल पूर्णांक
_ctl_btdh_search_pcie_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा mpt3_ioctl_btdh_mapping *btdh)
अणु
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (list_empty(&ioc->pcie_device_list))
		वापस rc;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_list, list) अणु
		अगर (btdh->bus == 0xFFFFFFFF && btdh->id == 0xFFFFFFFF &&
			   btdh->handle == pcie_device->handle) अणु
			btdh->bus = pcie_device->channel;
			btdh->id = pcie_device->id;
			rc = 1;
			जाओ out;
		पूर्ण अन्यथा अगर (btdh->bus == pcie_device->channel && btdh->id ==
			   pcie_device->id && btdh->handle == 0xFFFF) अणु
			btdh->handle = pcie_device->handle;
			rc = 1;
			जाओ out;
		पूर्ण
	पूर्ण
 out:
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
	वापस rc;
पूर्ण

/**
 * _ctl_btdh_search_raid_device - searching क्रम raid device
 * @ioc: per adapter object
 * @btdh: btdh ioctl payload
 */
अटल पूर्णांक
_ctl_btdh_search_raid_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा mpt3_ioctl_btdh_mapping *btdh)
अणु
	काष्ठा _raid_device *raid_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (list_empty(&ioc->raid_device_list))
		वापस rc;

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	list_क्रम_each_entry(raid_device, &ioc->raid_device_list, list) अणु
		अगर (btdh->bus == 0xFFFFFFFF && btdh->id == 0xFFFFFFFF &&
		    btdh->handle == raid_device->handle) अणु
			btdh->bus = raid_device->channel;
			btdh->id = raid_device->id;
			rc = 1;
			जाओ out;
		पूर्ण अन्यथा अगर (btdh->bus == raid_device->channel && btdh->id ==
		    raid_device->id && btdh->handle == 0xFFFF) अणु
			btdh->handle = raid_device->handle;
			rc = 1;
			जाओ out;
		पूर्ण
	पूर्ण
 out:
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
	वापस rc;
पूर्ण

/**
 * _ctl_btdh_mapping - मुख्य handler क्रम MPT3BTDHMAPPING opcode
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 */
अटल दीर्घ
_ctl_btdh_mapping(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_ioctl_btdh_mapping karg;
	पूर्णांक rc;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	rc = _ctl_btdh_search_sas_device(ioc, &karg);
	अगर (!rc)
		rc = _ctl_btdh_search_pcie_device(ioc, &karg);
	अगर (!rc)
		_ctl_btdh_search_raid_device(ioc, &karg);

	अगर (copy_to_user(arg, &karg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * _ctl_diag_capability - वापस diag buffer capability
 * @ioc: per adapter object
 * @buffer_type: specअगरies either TRACE, SNAPSHOT, or EXTENDED
 *
 * वापसs 1 when diag buffer support is enabled in firmware
 */
अटल u8
_ctl_diag_capability(काष्ठा MPT3SAS_ADAPTER *ioc, u8 buffer_type)
अणु
	u8 rc = 0;

	चयन (buffer_type) अणु
	हाल MPI2_DIAG_BUF_TYPE_TRACE:
		अगर (ioc->facts.IOCCapabilities &
		    MPI2_IOCFACTS_CAPABILITY_DIAG_TRACE_BUFFER)
			rc = 1;
		अवरोध;
	हाल MPI2_DIAG_BUF_TYPE_SNAPSHOT:
		अगर (ioc->facts.IOCCapabilities &
		    MPI2_IOCFACTS_CAPABILITY_SNAPSHOT_BUFFER)
			rc = 1;
		अवरोध;
	हाल MPI2_DIAG_BUF_TYPE_EXTENDED:
		अगर (ioc->facts.IOCCapabilities &
		    MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER)
			rc = 1;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * _ctl_diag_get_bufftype - वापस diag buffer type
 *              either TRACE, SNAPSHOT, or EXTENDED
 * @ioc: per adapter object
 * @unique_id: specअगरies the unique_id क्रम the buffer
 *
 * वापसs MPT3_DIAG_UID_NOT_FOUND अगर the id not found
 */
अटल u8
_ctl_diag_get_bufftype(काष्ठा MPT3SAS_ADAPTER *ioc, u32 unique_id)
अणु
	u8  index;

	क्रम (index = 0; index < MPI2_DIAG_BUF_TYPE_COUNT; index++) अणु
		अगर (ioc->unique_id[index] == unique_id)
			वापस index;
	पूर्ण

	वापस MPT3_DIAG_UID_NOT_FOUND;
पूर्ण

/**
 * _ctl_diag_रेजिस्टर_2 - wrapper क्रम रेजिस्टरing diag buffer support
 * @ioc: per adapter object
 * @diag_रेजिस्टर: the diag_रेजिस्टर काष्ठा passed in from user space
 *
 */
अटल दीर्घ
_ctl_diag_रेजिस्टर_2(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा mpt3_diag_रेजिस्टर *diag_रेजिस्टर)
अणु
	पूर्णांक rc, i;
	व्योम *request_data = शून्य;
	dma_addr_t request_data_dma;
	u32 request_data_sz = 0;
	Mpi2DiagBufferPostRequest_t *mpi_request;
	Mpi2DiagBufferPostReply_t *mpi_reply;
	u8 buffer_type;
	u16 smid;
	u16 ioc_status;
	u32 ioc_state;
	u8 issue_reset = 0;

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
	अगर (ioc_state != MPI2_IOC_STATE_OPERATIONAL) अणु
		ioc_err(ioc, "%s: failed due to ioc not operational\n",
			__func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (ioc->ctl_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: ctl_cmd in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	buffer_type = diag_रेजिस्टर->buffer_type;
	अगर (!_ctl_diag_capability(ioc, buffer_type)) अणु
		ioc_err(ioc, "%s: doesn't have capability for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -EPERM;
	पूर्ण

	अगर (diag_रेजिस्टर->unique_id == 0) अणु
		ioc_err(ioc,
		    "%s: Invalid UID(0x%08x), buffer_type(0x%02x)\n", __func__,
		    diag_रेजिस्टर->unique_id, buffer_type);
		वापस -EINVAL;
	पूर्ण

	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_APP_OWNED) &&
	    !(ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_RELEASED)) अणु
		ioc_err(ioc,
		    "%s: buffer_type(0x%02x) is already registered by application with UID(0x%08x)\n",
		    __func__, buffer_type, ioc->unique_id[buffer_type]);
		वापस -EINVAL;
	पूर्ण

	अगर (ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) अणु
		/*
		 * If driver posts buffer initially, then an application wants
		 * to Register that buffer (own it) without Releasing first,
		 * the application Register command MUST have the same buffer
		 * type and size in the Register command (obtained from the
		 * Query command). Otherwise that Register command will be
		 * failed. If the application has released the buffer but wants
		 * to re-रेजिस्टर it, it should be allowed as दीर्घ as the
		 * Unique-Id/Size match.
		 */

		अगर (ioc->unique_id[buffer_type] == MPT3DIAGBUFFUNIQUEID &&
		    ioc->diag_buffer_sz[buffer_type] ==
		    diag_रेजिस्टर->requested_buffer_size) अणु

			अगर (!(ioc->diag_buffer_status[buffer_type] &
			     MPT3_DIAG_BUFFER_IS_RELEASED)) अणु
				dctlprपूर्णांकk(ioc, ioc_info(ioc,
				    "%s: diag_buffer (%d) ownership changed. old-ID(0x%08x), new-ID(0x%08x)\n",
				    __func__, buffer_type,
				    ioc->unique_id[buffer_type],
				    diag_रेजिस्टर->unique_id));

				/*
				 * Application wants to own the buffer with
				 * the same size.
				 */
				ioc->unique_id[buffer_type] =
				    diag_रेजिस्टर->unique_id;
				rc = 0; /* success */
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (ioc->unique_id[buffer_type] !=
		    MPT3DIAGBUFFUNIQUEID) अणु
			अगर (ioc->unique_id[buffer_type] !=
			    diag_रेजिस्टर->unique_id ||
			    ioc->diag_buffer_sz[buffer_type] !=
			    diag_रेजिस्टर->requested_buffer_size ||
			    !(ioc->diag_buffer_status[buffer_type] &
			    MPT3_DIAG_BUFFER_IS_RELEASED)) अणु
				ioc_err(ioc,
				    "%s: already has a registered buffer for buffer_type(0x%02x)\n",
				    __func__, buffer_type);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			ioc_err(ioc, "%s: already has a registered buffer for buffer_type(0x%02x)\n",
			    __func__, buffer_type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED) अणु

		अगर (ioc->unique_id[buffer_type] != MPT3DIAGBUFFUNIQUEID ||
		    ioc->diag_buffer_sz[buffer_type] !=
		    diag_रेजिस्टर->requested_buffer_size) अणु

			ioc_err(ioc,
			    "%s: already a buffer is allocated for buffer_type(0x%02x) of size %d bytes, so please try registering again with same size\n",
			     __func__, buffer_type,
			    ioc->diag_buffer_sz[buffer_type]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (diag_रेजिस्टर->requested_buffer_size % 4)  अणु
		ioc_err(ioc, "%s: the requested_buffer_size is not 4 byte aligned\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	smid = mpt3sas_base_get_smid(ioc, ioc->ctl_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	rc = 0;
	ioc->ctl_cmds.status = MPT3_CMD_PENDING;
	स_रखो(ioc->ctl_cmds.reply, 0, ioc->reply_sz);
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->ctl_cmds.smid = smid;

	request_data = ioc->diag_buffer[buffer_type];
	request_data_sz = diag_रेजिस्टर->requested_buffer_size;
	ioc->unique_id[buffer_type] = diag_रेजिस्टर->unique_id;
	/* Reset ioc variables used क्रम additional query commands */
	ioc->reset_from_user = 0;
	स_रखो(&ioc->htb_rel, 0, माप(काष्ठा htb_rel_query));
	ioc->diag_buffer_status[buffer_type] &=
	    MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED;
	स_नकल(ioc->product_specअगरic[buffer_type],
	    diag_रेजिस्टर->product_specअगरic, MPT3_PRODUCT_SPECIFIC_DWORDS);
	ioc->diagnostic_flags[buffer_type] = diag_रेजिस्टर->diagnostic_flags;

	अगर (request_data) अणु
		request_data_dma = ioc->diag_buffer_dma[buffer_type];
		अगर (request_data_sz != ioc->diag_buffer_sz[buffer_type]) अणु
			dma_मुक्त_coherent(&ioc->pdev->dev,
					ioc->diag_buffer_sz[buffer_type],
					request_data, request_data_dma);
			request_data = शून्य;
		पूर्ण
	पूर्ण

	अगर (request_data == शून्य) अणु
		ioc->diag_buffer_sz[buffer_type] = 0;
		ioc->diag_buffer_dma[buffer_type] = 0;
		request_data = dma_alloc_coherent(&ioc->pdev->dev,
				request_data_sz, &request_data_dma, GFP_KERNEL);
		अगर (request_data == शून्य) अणु
			ioc_err(ioc, "%s: failed allocating memory for diag buffers, requested size(%d)\n",
				__func__, request_data_sz);
			mpt3sas_base_मुक्त_smid(ioc, smid);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		ioc->diag_buffer[buffer_type] = request_data;
		ioc->diag_buffer_sz[buffer_type] = request_data_sz;
		ioc->diag_buffer_dma[buffer_type] = request_data_dma;
	पूर्ण

	mpi_request->Function = MPI2_FUNCTION_DIAG_BUFFER_POST;
	mpi_request->BufferType = diag_रेजिस्टर->buffer_type;
	mpi_request->Flags = cpu_to_le32(diag_रेजिस्टर->diagnostic_flags);
	mpi_request->BufferAddress = cpu_to_le64(request_data_dma);
	mpi_request->BufferLength = cpu_to_le32(request_data_sz);
	mpi_request->VF_ID = 0; /* TODO */
	mpi_request->VP_ID = 0;

	dctlprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: diag_buffer(0x%p), dma(0x%llx), sz(%d)\n",
			    __func__, request_data,
			    (अचिन्हित दीर्घ दीर्घ)request_data_dma,
			    le32_to_cpu(mpi_request->BufferLength)));

	क्रम (i = 0; i < MPT3_PRODUCT_SPECIFIC_DWORDS; i++)
		mpi_request->ProductSpecअगरic[i] =
			cpu_to_le32(ioc->product_specअगरic[buffer_type][i]);

	init_completion(&ioc->ctl_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->ctl_cmds.करोne,
	    MPT3_IOCTL_DEFAULT_TIMEOUT*HZ);

	अगर (!(ioc->ctl_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc,
		    ioc->ctl_cmds.status, mpi_request,
		    माप(Mpi2DiagBufferPostRequest_t)/4, issue_reset);
		जाओ issue_host_reset;
	पूर्ण

	/* process the completed Reply Message Frame */
	अगर ((ioc->ctl_cmds.status & MPT3_CMD_REPLY_VALID) == 0) अणु
		ioc_err(ioc, "%s: no reply message\n", __func__);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	mpi_reply = ioc->ctl_cmds.reply;
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus) & MPI2_IOCSTATUS_MASK;

	अगर (ioc_status == MPI2_IOCSTATUS_SUCCESS) अणु
		ioc->diag_buffer_status[buffer_type] |=
			MPT3_DIAG_BUFFER_IS_REGISTERED;
		dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s: success\n", __func__));
	पूर्ण अन्यथा अणु
		ioc_info(ioc, "%s: ioc_status(0x%04x) log_info(0x%08x)\n",
			 __func__,
			 ioc_status, le32_to_cpu(mpi_reply->IOCLogInfo));
		rc = -EFAULT;
	पूर्ण

 issue_host_reset:
	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);

 out:

	अगर (rc && request_data) अणु
		dma_मुक्त_coherent(&ioc->pdev->dev, request_data_sz,
		    request_data, request_data_dma);
		ioc->diag_buffer_status[buffer_type] &=
		    ~MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED;
	पूर्ण

	ioc->ctl_cmds.status = MPT3_CMD_NOT_USED;
	वापस rc;
पूर्ण

/**
 * mpt3sas_enable_diag_buffer - enabling diag_buffers support driver load समय
 * @ioc: per adapter object
 * @bits_to_रेजिस्टर: bitwise field where trace is bit 0, and snapshot is bit 1
 *
 * This is called when command line option diag_buffer_enable is enabled
 * at driver load समय.
 */
व्योम
mpt3sas_enable_diag_buffer(काष्ठा MPT3SAS_ADAPTER *ioc, u8 bits_to_रेजिस्टर)
अणु
	काष्ठा mpt3_diag_रेजिस्टर diag_रेजिस्टर;
	u32 ret_val;
	u32 trace_buff_size = ioc->manu_pg11.HostTraceBufferMaxSizeKB<<10;
	u32 min_trace_buff_size = 0;
	u32 decr_trace_buff_size = 0;

	स_रखो(&diag_रेजिस्टर, 0, माप(काष्ठा mpt3_diag_रेजिस्टर));

	अगर (bits_to_रेजिस्टर & 1) अणु
		ioc_info(ioc, "registering trace buffer support\n");
		ioc->diag_trigger_master.MasterData =
		    (MASTER_TRIGGER_FW_FAULT + MASTER_TRIGGER_ADAPTER_RESET);
		diag_रेजिस्टर.buffer_type = MPI2_DIAG_BUF_TYPE_TRACE;
		diag_रेजिस्टर.unique_id =
		    (ioc->hba_mpi_version_beदीर्घed == MPI2_VERSION) ?
		    (MPT2DIAGBUFFUNIQUEID):(MPT3DIAGBUFFUNIQUEID);

		अगर (trace_buff_size != 0) अणु
			diag_रेजिस्टर.requested_buffer_size = trace_buff_size;
			min_trace_buff_size =
			    ioc->manu_pg11.HostTraceBufferMinSizeKB<<10;
			decr_trace_buff_size =
			    ioc->manu_pg11.HostTraceBufferDecrementSizeKB<<10;

			अगर (min_trace_buff_size > trace_buff_size) अणु
				/* The buff size is not set correctly */
				ioc_err(ioc,
				    "Min Trace Buff size (%d KB) greater than Max Trace Buff size (%d KB)\n",
				     min_trace_buff_size>>10,
				     trace_buff_size>>10);
				ioc_err(ioc,
				    "Using zero Min Trace Buff Size\n");
				min_trace_buff_size = 0;
			पूर्ण

			अगर (decr_trace_buff_size == 0) अणु
				/*
				 * retry the min size अगर decrement
				 * is not available.
				 */
				decr_trace_buff_size =
				    trace_buff_size - min_trace_buff_size;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* रेजिस्टर क्रम 2MB buffers  */
			diag_रेजिस्टर.requested_buffer_size = 2 * (1024 * 1024);
		पूर्ण

		करो अणु
			ret_val = _ctl_diag_रेजिस्टर_2(ioc,  &diag_रेजिस्टर);

			अगर (ret_val == -ENOMEM && min_trace_buff_size &&
			    (trace_buff_size - decr_trace_buff_size) >=
			    min_trace_buff_size) अणु
				/* adjust the buffer size */
				trace_buff_size -= decr_trace_buff_size;
				diag_रेजिस्टर.requested_buffer_size =
				    trace_buff_size;
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण जबतक (true);

		अगर (ret_val == -ENOMEM)
			ioc_err(ioc,
			    "Cannot allocate trace buffer memory. Last memory tried = %d KB\n",
			    diag_रेजिस्टर.requested_buffer_size>>10);
		अन्यथा अगर (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE]
		    & MPT3_DIAG_BUFFER_IS_REGISTERED) अणु
			ioc_err(ioc, "Trace buffer memory %d KB allocated\n",
			    diag_रेजिस्टर.requested_buffer_size>>10);
			अगर (ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION)
				ioc->diag_buffer_status[
				    MPI2_DIAG_BUF_TYPE_TRACE] |=
				    MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED;
		पूर्ण
	पूर्ण

	अगर (bits_to_रेजिस्टर & 2) अणु
		ioc_info(ioc, "registering snapshot buffer support\n");
		diag_रेजिस्टर.buffer_type = MPI2_DIAG_BUF_TYPE_SNAPSHOT;
		/* रेजिस्टर क्रम 2MB buffers  */
		diag_रेजिस्टर.requested_buffer_size = 2 * (1024 * 1024);
		diag_रेजिस्टर.unique_id = 0x7075901;
		_ctl_diag_रेजिस्टर_2(ioc,  &diag_रेजिस्टर);
	पूर्ण

	अगर (bits_to_रेजिस्टर & 4) अणु
		ioc_info(ioc, "registering extended buffer support\n");
		diag_रेजिस्टर.buffer_type = MPI2_DIAG_BUF_TYPE_EXTENDED;
		/* रेजिस्टर क्रम 2MB buffers  */
		diag_रेजिस्टर.requested_buffer_size = 2 * (1024 * 1024);
		diag_रेजिस्टर.unique_id = 0x7075901;
		_ctl_diag_रेजिस्टर_2(ioc,  &diag_रेजिस्टर);
	पूर्ण
पूर्ण

/**
 * _ctl_diag_रेजिस्टर - application रेजिस्टर with driver
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 *
 * This will allow the driver to setup any required buffers that will be
 * needed by firmware to communicate with the driver.
 */
अटल दीर्घ
_ctl_diag_रेजिस्टर(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_diag_रेजिस्टर karg;
	दीर्घ rc;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	rc = _ctl_diag_रेजिस्टर_2(ioc, &karg);

	अगर (!rc && (ioc->diag_buffer_status[karg.buffer_type] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED))
		ioc->diag_buffer_status[karg.buffer_type] |=
		    MPT3_DIAG_BUFFER_IS_APP_OWNED;

	वापस rc;
पूर्ण

/**
 * _ctl_diag_unरेजिस्टर - application unरेजिस्टर with driver
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 *
 * This will allow the driver to cleanup any memory allocated क्रम diag
 * messages and to मुक्त up any resources.
 */
अटल दीर्घ
_ctl_diag_unरेजिस्टर(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_diag_unरेजिस्टर karg;
	व्योम *request_data;
	dma_addr_t request_data_dma;
	u32 request_data_sz;
	u8 buffer_type;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	buffer_type = _ctl_diag_get_bufftype(ioc, karg.unique_id);
	अगर (buffer_type == MPT3_DIAG_UID_NOT_FOUND) अणु
		ioc_err(ioc, "%s: buffer with unique_id(0x%08x) not found\n",
		    __func__, karg.unique_id);
		वापस -EINVAL;
	पूर्ण

	अगर (!_ctl_diag_capability(ioc, buffer_type)) अणु
		ioc_err(ioc, "%s: doesn't have capability for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -EPERM;
	पूर्ण

	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		ioc_err(ioc, "%s: buffer_type(0x%02x) is not registered\n",
			__func__, buffer_type);
		वापस -EINVAL;
	पूर्ण
	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) == 0) अणु
		ioc_err(ioc, "%s: buffer_type(0x%02x) has not been released\n",
			__func__, buffer_type);
		वापस -EINVAL;
	पूर्ण

	अगर (karg.unique_id != ioc->unique_id[buffer_type]) अणु
		ioc_err(ioc, "%s: unique_id(0x%08x) is not registered\n",
			__func__, karg.unique_id);
		वापस -EINVAL;
	पूर्ण

	request_data = ioc->diag_buffer[buffer_type];
	अगर (!request_data) अणु
		ioc_err(ioc, "%s: doesn't have memory allocated for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -ENOMEM;
	पूर्ण

	अगर (ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED) अणु
		ioc->unique_id[buffer_type] = MPT3DIAGBUFFUNIQUEID;
		ioc->diag_buffer_status[buffer_type] &=
		    ~MPT3_DIAG_BUFFER_IS_APP_OWNED;
		ioc->diag_buffer_status[buffer_type] &=
		    ~MPT3_DIAG_BUFFER_IS_REGISTERED;
	पूर्ण अन्यथा अणु
		request_data_sz = ioc->diag_buffer_sz[buffer_type];
		request_data_dma = ioc->diag_buffer_dma[buffer_type];
		dma_मुक्त_coherent(&ioc->pdev->dev, request_data_sz,
				request_data, request_data_dma);
		ioc->diag_buffer[buffer_type] = शून्य;
		ioc->diag_buffer_status[buffer_type] = 0;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * _ctl_diag_query - query relevant info associated with diag buffers
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 *
 * The application will send only buffer_type and unique_id.  Driver will
 * inspect unique_id first, अगर valid, fill in all the info.  If unique_id is
 * 0x00, the driver will वापस info specअगरied by Buffer Type.
 */
अटल दीर्घ
_ctl_diag_query(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_diag_query karg;
	व्योम *request_data;
	पूर्णांक i;
	u8 buffer_type;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	karg.application_flags = 0;
	buffer_type = karg.buffer_type;

	अगर (!_ctl_diag_capability(ioc, buffer_type)) अणु
		ioc_err(ioc, "%s: doesn't have capability for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -EPERM;
	पूर्ण

	अगर (!(ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED)) अणु
		अगर ((ioc->diag_buffer_status[buffer_type] &
		    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
			ioc_err(ioc, "%s: buffer_type(0x%02x) is not registered\n",
				__func__, buffer_type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (karg.unique_id) अणु
		अगर (karg.unique_id != ioc->unique_id[buffer_type]) अणु
			ioc_err(ioc, "%s: unique_id(0x%08x) is not registered\n",
				__func__, karg.unique_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	request_data = ioc->diag_buffer[buffer_type];
	अगर (!request_data) अणु
		ioc_err(ioc, "%s: doesn't have buffer for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -ENOMEM;
	पूर्ण

	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED))
		karg.application_flags |= MPT3_APP_FLAGS_BUFFER_VALID;

	अगर (!(ioc->diag_buffer_status[buffer_type] &
	     MPT3_DIAG_BUFFER_IS_RELEASED))
		karg.application_flags |= MPT3_APP_FLAGS_FW_BUFFER_ACCESS;

	अगर (!(ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED))
		karg.application_flags |= MPT3_APP_FLAGS_DYNAMIC_BUFFER_ALLOC;

	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_APP_OWNED))
		karg.application_flags |= MPT3_APP_FLAGS_APP_OWNED;

	क्रम (i = 0; i < MPT3_PRODUCT_SPECIFIC_DWORDS; i++)
		karg.product_specअगरic[i] =
		    ioc->product_specअगरic[buffer_type][i];

	karg.total_buffer_size = ioc->diag_buffer_sz[buffer_type];
	karg.driver_added_buffer_size = 0;
	karg.unique_id = ioc->unique_id[buffer_type];
	karg.diagnostic_flags = ioc->diagnostic_flags[buffer_type];

	अगर (copy_to_user(arg, &karg, माप(काष्ठा mpt3_diag_query))) अणु
		ioc_err(ioc, "%s: unable to write mpt3_diag_query data @ %p\n",
			__func__, arg);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mpt3sas_send_diag_release - Diag Release Message
 * @ioc: per adapter object
 * @buffer_type: specअगरies either TRACE, SNAPSHOT, or EXTENDED
 * @issue_reset: specअगरies whether host reset is required.
 *
 */
पूर्णांक
mpt3sas_send_diag_release(काष्ठा MPT3SAS_ADAPTER *ioc, u8 buffer_type,
	u8 *issue_reset)
अणु
	Mpi2DiagReleaseRequest_t *mpi_request;
	Mpi2DiagReleaseReply_t *mpi_reply;
	u16 smid;
	u16 ioc_status;
	u32 ioc_state;
	पूर्णांक rc;
	u8 reset_needed = 0;

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	rc = 0;
	*issue_reset = 0;


	ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
	अगर (ioc_state != MPI2_IOC_STATE_OPERATIONAL) अणु
		अगर (ioc->diag_buffer_status[buffer_type] &
		    MPT3_DIAG_BUFFER_IS_REGISTERED)
			ioc->diag_buffer_status[buffer_type] |=
			    MPT3_DIAG_BUFFER_IS_RELEASED;
		dctlprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: skipping due to FAULT state\n",
				    __func__));
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (ioc->ctl_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: ctl_cmd in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	smid = mpt3sas_base_get_smid(ioc, ioc->ctl_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	ioc->ctl_cmds.status = MPT3_CMD_PENDING;
	स_रखो(ioc->ctl_cmds.reply, 0, ioc->reply_sz);
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->ctl_cmds.smid = smid;

	mpi_request->Function = MPI2_FUNCTION_DIAG_RELEASE;
	mpi_request->BufferType = buffer_type;
	mpi_request->VF_ID = 0; /* TODO */
	mpi_request->VP_ID = 0;

	init_completion(&ioc->ctl_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->ctl_cmds.करोne,
	    MPT3_IOCTL_DEFAULT_TIMEOUT*HZ);

	अगर (!(ioc->ctl_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc,
		    ioc->ctl_cmds.status, mpi_request,
		    माप(Mpi2DiagReleaseRequest_t)/4, reset_needed);
		 *issue_reset = reset_needed;
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	/* process the completed Reply Message Frame */
	अगर ((ioc->ctl_cmds.status & MPT3_CMD_REPLY_VALID) == 0) अणु
		ioc_err(ioc, "%s: no reply message\n", __func__);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	mpi_reply = ioc->ctl_cmds.reply;
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus) & MPI2_IOCSTATUS_MASK;

	अगर (ioc_status == MPI2_IOCSTATUS_SUCCESS) अणु
		ioc->diag_buffer_status[buffer_type] |=
		    MPT3_DIAG_BUFFER_IS_RELEASED;
		dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s: success\n", __func__));
	पूर्ण अन्यथा अणु
		ioc_info(ioc, "%s: ioc_status(0x%04x) log_info(0x%08x)\n",
			 __func__,
			 ioc_status, le32_to_cpu(mpi_reply->IOCLogInfo));
		rc = -EFAULT;
	पूर्ण

 out:
	ioc->ctl_cmds.status = MPT3_CMD_NOT_USED;
	वापस rc;
पूर्ण

/**
 * _ctl_diag_release - request to send Diag Release Message to firmware
 * @ioc: ?
 * @arg: user space buffer containing ioctl content
 *
 * This allows ownership of the specअगरied buffer to वापसed to the driver,
 * allowing an application to पढ़ो the buffer without fear that firmware is
 * overwriting inक्रमmation in the buffer.
 */
अटल दीर्घ
_ctl_diag_release(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_diag_release karg;
	व्योम *request_data;
	पूर्णांक rc;
	u8 buffer_type;
	u8 issue_reset = 0;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	buffer_type = _ctl_diag_get_bufftype(ioc, karg.unique_id);
	अगर (buffer_type == MPT3_DIAG_UID_NOT_FOUND) अणु
		ioc_err(ioc, "%s: buffer with unique_id(0x%08x) not found\n",
		    __func__, karg.unique_id);
		वापस -EINVAL;
	पूर्ण

	अगर (!_ctl_diag_capability(ioc, buffer_type)) अणु
		ioc_err(ioc, "%s: doesn't have capability for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -EPERM;
	पूर्ण

	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		ioc_err(ioc, "%s: buffer_type(0x%02x) is not registered\n",
			__func__, buffer_type);
		वापस -EINVAL;
	पूर्ण

	अगर (karg.unique_id != ioc->unique_id[buffer_type]) अणु
		ioc_err(ioc, "%s: unique_id(0x%08x) is not registered\n",
			__func__, karg.unique_id);
		वापस -EINVAL;
	पूर्ण

	अगर (ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) अणु
		ioc_err(ioc, "%s: buffer_type(0x%02x) is already released\n",
			__func__, buffer_type);
		वापस -EINVAL;
	पूर्ण

	request_data = ioc->diag_buffer[buffer_type];

	अगर (!request_data) अणु
		ioc_err(ioc, "%s: doesn't have memory allocated for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -ENOMEM;
	पूर्ण

	/* buffers were released by due to host reset */
	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_DIAG_RESET)) अणु
		ioc->diag_buffer_status[buffer_type] |=
		    MPT3_DIAG_BUFFER_IS_RELEASED;
		ioc->diag_buffer_status[buffer_type] &=
		    ~MPT3_DIAG_BUFFER_IS_DIAG_RESET;
		ioc_err(ioc, "%s: buffer_type(0x%02x) was released due to host reset\n",
			__func__, buffer_type);
		वापस 0;
	पूर्ण

	rc = mpt3sas_send_diag_release(ioc, buffer_type, &issue_reset);

	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);

	वापस rc;
पूर्ण

/**
 * _ctl_diag_पढ़ो_buffer - request क्रम copy of the diag buffer
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 */
अटल दीर्घ
_ctl_diag_पढ़ो_buffer(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_diag_पढ़ो_buffer karg;
	काष्ठा mpt3_diag_पढ़ो_buffer __user *uarg = arg;
	व्योम *request_data, *diag_data;
	Mpi2DiagBufferPostRequest_t *mpi_request;
	Mpi2DiagBufferPostReply_t *mpi_reply;
	पूर्णांक rc, i;
	u8 buffer_type;
	अचिन्हित दीर्घ request_size, copy_size;
	u16 smid;
	u16 ioc_status;
	u8 issue_reset = 0;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s\n",
				 __func__));

	buffer_type = _ctl_diag_get_bufftype(ioc, karg.unique_id);
	अगर (buffer_type == MPT3_DIAG_UID_NOT_FOUND) अणु
		ioc_err(ioc, "%s: buffer with unique_id(0x%08x) not found\n",
		    __func__, karg.unique_id);
		वापस -EINVAL;
	पूर्ण

	अगर (!_ctl_diag_capability(ioc, buffer_type)) अणु
		ioc_err(ioc, "%s: doesn't have capability for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -EPERM;
	पूर्ण

	अगर (karg.unique_id != ioc->unique_id[buffer_type]) अणु
		ioc_err(ioc, "%s: unique_id(0x%08x) is not registered\n",
			__func__, karg.unique_id);
		वापस -EINVAL;
	पूर्ण

	request_data = ioc->diag_buffer[buffer_type];
	अगर (!request_data) अणु
		ioc_err(ioc, "%s: doesn't have buffer for buffer_type(0x%02x)\n",
			__func__, buffer_type);
		वापस -ENOMEM;
	पूर्ण

	request_size = ioc->diag_buffer_sz[buffer_type];

	अगर ((karg.starting_offset % 4) || (karg.bytes_to_पढ़ो % 4)) अणु
		ioc_err(ioc, "%s: either the starting_offset or bytes_to_read are not 4 byte aligned\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (karg.starting_offset > request_size)
		वापस -EINVAL;

	diag_data = (व्योम *)(request_data + karg.starting_offset);
	dctlprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: diag_buffer(%p), offset(%d), sz(%d)\n",
			    __func__, diag_data, karg.starting_offset,
			    karg.bytes_to_पढ़ो));

	/* Truncate data on requests that are too large */
	अगर ((diag_data + karg.bytes_to_पढ़ो < diag_data) ||
	    (diag_data + karg.bytes_to_पढ़ो > request_data + request_size))
		copy_size = request_size - karg.starting_offset;
	अन्यथा
		copy_size = karg.bytes_to_पढ़ो;

	अगर (copy_to_user((व्योम __user *)uarg->diagnostic_data,
	    diag_data, copy_size)) अणु
		ioc_err(ioc, "%s: Unable to write mpt_diag_read_buffer_t data @ %p\n",
			__func__, diag_data);
		वापस -EFAULT;
	पूर्ण

	अगर ((karg.flags & MPT3_FLAGS_REREGISTER) == 0)
		वापस 0;

	dctlprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: Reregister buffer_type(0x%02x)\n",
			    __func__, buffer_type));
	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) == 0) अणु
		dctlprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: buffer_type(0x%02x) is still registered\n",
				    __func__, buffer_type));
		वापस 0;
	पूर्ण
	/* Get a मुक्त request frame and save the message context.
	*/

	अगर (ioc->ctl_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: ctl_cmd in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	smid = mpt3sas_base_get_smid(ioc, ioc->ctl_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	rc = 0;
	ioc->ctl_cmds.status = MPT3_CMD_PENDING;
	स_रखो(ioc->ctl_cmds.reply, 0, ioc->reply_sz);
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->ctl_cmds.smid = smid;

	mpi_request->Function = MPI2_FUNCTION_DIAG_BUFFER_POST;
	mpi_request->BufferType = buffer_type;
	mpi_request->BufferLength =
	    cpu_to_le32(ioc->diag_buffer_sz[buffer_type]);
	mpi_request->BufferAddress =
	    cpu_to_le64(ioc->diag_buffer_dma[buffer_type]);
	क्रम (i = 0; i < MPT3_PRODUCT_SPECIFIC_DWORDS; i++)
		mpi_request->ProductSpecअगरic[i] =
			cpu_to_le32(ioc->product_specअगरic[buffer_type][i]);
	mpi_request->VF_ID = 0; /* TODO */
	mpi_request->VP_ID = 0;

	init_completion(&ioc->ctl_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->ctl_cmds.करोne,
	    MPT3_IOCTL_DEFAULT_TIMEOUT*HZ);

	अगर (!(ioc->ctl_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc,
		    ioc->ctl_cmds.status, mpi_request,
		    माप(Mpi2DiagBufferPostRequest_t)/4, issue_reset);
		जाओ issue_host_reset;
	पूर्ण

	/* process the completed Reply Message Frame */
	अगर ((ioc->ctl_cmds.status & MPT3_CMD_REPLY_VALID) == 0) अणु
		ioc_err(ioc, "%s: no reply message\n", __func__);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	mpi_reply = ioc->ctl_cmds.reply;
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus) & MPI2_IOCSTATUS_MASK;

	अगर (ioc_status == MPI2_IOCSTATUS_SUCCESS) अणु
		ioc->diag_buffer_status[buffer_type] |=
		    MPT3_DIAG_BUFFER_IS_REGISTERED;
		ioc->diag_buffer_status[buffer_type] &=
		    ~MPT3_DIAG_BUFFER_IS_RELEASED;
		dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s: success\n", __func__));
	पूर्ण अन्यथा अणु
		ioc_info(ioc, "%s: ioc_status(0x%04x) log_info(0x%08x)\n",
			 __func__, ioc_status,
			 le32_to_cpu(mpi_reply->IOCLogInfo));
		rc = -EFAULT;
	पूर्ण

 issue_host_reset:
	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);

 out:

	ioc->ctl_cmds.status = MPT3_CMD_NOT_USED;
	वापस rc;
पूर्ण

/**
 * _ctl_addnl_diag_query - query relevant info associated with diag buffers
 * @ioc: per adapter object
 * @arg: user space buffer containing ioctl content
 *
 * The application will send only unique_id.  Driver will
 * inspect unique_id first, अगर valid, fill the details related to cause
 * क्रम diag buffer release.
 */
अटल दीर्घ
_ctl_addnl_diag_query(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम __user *arg)
अणु
	काष्ठा mpt3_addnl_diag_query karg;
	u32 buffer_type = 0;

	अगर (copy_from_user(&karg, arg, माप(karg))) अणु
		pr_err("%s: failure at %s:%d/%s()!\n",
		    ioc->name, __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण
	dctlprपूर्णांकk(ioc, ioc_info(ioc, "%s\n",  __func__));
	अगर (karg.unique_id == 0) अणु
		ioc_err(ioc, "%s: unique_id is(0x%08x)\n",
		    __func__, karg.unique_id);
		वापस -EPERM;
	पूर्ण
	buffer_type = _ctl_diag_get_bufftype(ioc, karg.unique_id);
	अगर (buffer_type == MPT3_DIAG_UID_NOT_FOUND) अणु
		ioc_err(ioc, "%s: buffer with unique_id(0x%08x) not found\n",
		    __func__, karg.unique_id);
		वापस -EPERM;
	पूर्ण
	स_रखो(&karg.rel_query, 0, माप(karg.rel_query));
	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		ioc_info(ioc, "%s: buffer_type(0x%02x) is not registered\n",
		    __func__, buffer_type);
		जाओ out;
	पूर्ण
	अगर ((ioc->diag_buffer_status[buffer_type] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) == 0) अणु
		ioc_err(ioc, "%s: buffer_type(0x%02x) is not released\n",
		    __func__, buffer_type);
		वापस -EPERM;
	पूर्ण
	स_नकल(&karg.rel_query, &ioc->htb_rel, माप(karg.rel_query));
out:
	अगर (copy_to_user(arg, &karg, माप(काष्ठा mpt3_addnl_diag_query))) अणु
		ioc_err(ioc, "%s: unable to write mpt3_addnl_diag_query data @ %p\n",
		    __func__, arg);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/**
 * _ctl_compat_mpt_command - convert 32bit poपूर्णांकers to 64bit.
 * @ioc: per adapter object
 * @cmd: ioctl opcode
 * @arg: (काष्ठा mpt3_ioctl_command32)
 *
 * MPT3COMMAND32 - Handle 32bit applications running on 64bit os.
 */
अटल दीर्घ
_ctl_compat_mpt_command(काष्ठा MPT3SAS_ADAPTER *ioc, अचिन्हित cmd,
	व्योम __user *arg)
अणु
	काष्ठा mpt3_ioctl_command32 karg32;
	काष्ठा mpt3_ioctl_command32 __user *uarg;
	काष्ठा mpt3_ioctl_command karg;

	अगर (_IOC_SIZE(cmd) != माप(काष्ठा mpt3_ioctl_command32))
		वापस -EINVAL;

	uarg = (काष्ठा mpt3_ioctl_command32 __user *) arg;

	अगर (copy_from_user(&karg32, (अक्षर __user *)arg, माप(karg32))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	स_रखो(&karg, 0, माप(काष्ठा mpt3_ioctl_command));
	karg.hdr.ioc_number = karg32.hdr.ioc_number;
	karg.hdr.port_number = karg32.hdr.port_number;
	karg.hdr.max_data_size = karg32.hdr.max_data_size;
	karg.समयout = karg32.समयout;
	karg.max_reply_bytes = karg32.max_reply_bytes;
	karg.data_in_size = karg32.data_in_size;
	karg.data_out_size = karg32.data_out_size;
	karg.max_sense_bytes = karg32.max_sense_bytes;
	karg.data_sge_offset = karg32.data_sge_offset;
	karg.reply_frame_buf_ptr = compat_ptr(karg32.reply_frame_buf_ptr);
	karg.data_in_buf_ptr = compat_ptr(karg32.data_in_buf_ptr);
	karg.data_out_buf_ptr = compat_ptr(karg32.data_out_buf_ptr);
	karg.sense_data_ptr = compat_ptr(karg32.sense_data_ptr);
	वापस _ctl_करो_mpt_command(ioc, karg, &uarg->mf);
पूर्ण
#पूर्ण_अगर

/**
 * _ctl_ioctl_मुख्य - मुख्य ioctl entry poपूर्णांक
 * @file:  (काष्ठा file)
 * @cmd:  ioctl opcode
 * @arg:  user space data buffer
 * @compat:  handles 32 bit applications in 64bit os
 * @mpi_version: will be MPI2_VERSION क्रम mpt2ctl ioctl device &
 * MPI25_VERSION | MPI26_VERSION क्रम mpt3ctl ioctl device.
 */
अटल दीर्घ
_ctl_ioctl_मुख्य(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम __user *arg,
	u8 compat, u16 mpi_version)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc;
	काष्ठा mpt3_ioctl_header ioctl_header;
	क्रमागत block_state state;
	दीर्घ ret = -ENOIOCTLCMD;

	/* get IOCTL header */
	अगर (copy_from_user(&ioctl_header, (अक्षर __user *)arg,
	    माप(काष्ठा mpt3_ioctl_header))) अणु
		pr_err("failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (_ctl_verअगरy_adapter(ioctl_header.ioc_number,
				&ioc, mpi_version) == -1 || !ioc)
		वापस -ENODEV;

	/* pci_access_mutex lock acquired by ioctl path */
	mutex_lock(&ioc->pci_access_mutex);

	अगर (ioc->shost_recovery || ioc->pci_error_recovery ||
	    ioc->is_driver_loading || ioc->हटाओ_host) अणु
		ret = -EAGAIN;
		जाओ out_unlock_pciaccess;
	पूर्ण

	state = (file->f_flags & O_NONBLOCK) ? NON_BLOCKING : BLOCKING;
	अगर (state == NON_BLOCKING) अणु
		अगर (!mutex_trylock(&ioc->ctl_cmds.mutex)) अणु
			ret = -EAGAIN;
			जाओ out_unlock_pciaccess;
		पूर्ण
	पूर्ण अन्यथा अगर (mutex_lock_पूर्णांकerruptible(&ioc->ctl_cmds.mutex)) अणु
		ret = -ERESTARTSYS;
		जाओ out_unlock_pciaccess;
	पूर्ण


	चयन (cmd) अणु
	हाल MPT3IOCINFO:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_ioctl_iocinfo))
			ret = _ctl_getiocinfo(ioc, arg);
		अवरोध;
#अगर_घोषित CONFIG_COMPAT
	हाल MPT3COMMAND32:
#पूर्ण_अगर
	हाल MPT3COMMAND:
	अणु
		काष्ठा mpt3_ioctl_command __user *uarg;
		काष्ठा mpt3_ioctl_command karg;

#अगर_घोषित CONFIG_COMPAT
		अगर (compat) अणु
			ret = _ctl_compat_mpt_command(ioc, cmd, arg);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		अगर (copy_from_user(&karg, arg, माप(karg))) अणु
			pr_err("failure at %s:%d/%s()!\n",
			    __खाता__, __LINE__, __func__);
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (karg.hdr.ioc_number != ioctl_header.ioc_number) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_ioctl_command)) अणु
			uarg = arg;
			ret = _ctl_करो_mpt_command(ioc, karg, &uarg->mf);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MPT3EVENTQUERY:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_ioctl_eventquery))
			ret = _ctl_eventquery(ioc, arg);
		अवरोध;
	हाल MPT3EVENTENABLE:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_ioctl_eventenable))
			ret = _ctl_eventenable(ioc, arg);
		अवरोध;
	हाल MPT3EVENTREPORT:
		ret = _ctl_eventreport(ioc, arg);
		अवरोध;
	हाल MPT3HARDRESET:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_ioctl_diag_reset))
			ret = _ctl_करो_reset(ioc, arg);
		अवरोध;
	हाल MPT3BTDHMAPPING:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_ioctl_btdh_mapping))
			ret = _ctl_btdh_mapping(ioc, arg);
		अवरोध;
	हाल MPT3DIAGREGISTER:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_diag_रेजिस्टर))
			ret = _ctl_diag_रेजिस्टर(ioc, arg);
		अवरोध;
	हाल MPT3DIAGUNREGISTER:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_diag_unरेजिस्टर))
			ret = _ctl_diag_unरेजिस्टर(ioc, arg);
		अवरोध;
	हाल MPT3DIAGQUERY:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_diag_query))
			ret = _ctl_diag_query(ioc, arg);
		अवरोध;
	हाल MPT3DIAGRELEASE:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_diag_release))
			ret = _ctl_diag_release(ioc, arg);
		अवरोध;
	हाल MPT3DIAGREADBUFFER:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_diag_पढ़ो_buffer))
			ret = _ctl_diag_पढ़ो_buffer(ioc, arg);
		अवरोध;
	हाल MPT3ADDNLDIAGQUERY:
		अगर (_IOC_SIZE(cmd) == माप(काष्ठा mpt3_addnl_diag_query))
			ret = _ctl_addnl_diag_query(ioc, arg);
		अवरोध;
	शेष:
		dctlprपूर्णांकk(ioc,
			   ioc_info(ioc, "unsupported ioctl opcode(0x%08x)\n",
				    cmd));
		अवरोध;
	पूर्ण

	mutex_unlock(&ioc->ctl_cmds.mutex);
out_unlock_pciaccess:
	mutex_unlock(&ioc->pci_access_mutex);
	वापस ret;
पूर्ण

/**
 * _ctl_ioctl - mpt3ctl मुख्य ioctl entry poपूर्णांक (unlocked)
 * @file: (काष्ठा file)
 * @cmd: ioctl opcode
 * @arg: ?
 */
अटल दीर्घ
_ctl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	/* pass MPI25_VERSION | MPI26_VERSION value,
	 * to indicate that this ioctl cmd
	 * came from mpt3ctl ioctl device.
	 */
	ret = _ctl_ioctl_मुख्य(file, cmd, (व्योम __user *)arg, 0,
		MPI25_VERSION | MPI26_VERSION);
	वापस ret;
पूर्ण

/**
 * _ctl_mpt2_ioctl - mpt2ctl मुख्य ioctl entry poपूर्णांक (unlocked)
 * @file: (काष्ठा file)
 * @cmd: ioctl opcode
 * @arg: ?
 */
अटल दीर्घ
_ctl_mpt2_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	/* pass MPI2_VERSION value, to indicate that this ioctl cmd
	 * came from mpt2ctl ioctl device.
	 */
	ret = _ctl_ioctl_मुख्य(file, cmd, (व्योम __user *)arg, 0, MPI2_VERSION);
	वापस ret;
पूर्ण
#अगर_घोषित CONFIG_COMPAT
/**
 * _ctl_ioctl_compat - मुख्य ioctl entry poपूर्णांक (compat)
 * @file: ?
 * @cmd: ?
 * @arg: ?
 *
 * This routine handles 32 bit applications in 64bit os.
 */
अटल दीर्घ
_ctl_ioctl_compat(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	ret = _ctl_ioctl_मुख्य(file, cmd, (व्योम __user *)arg, 1,
		MPI25_VERSION | MPI26_VERSION);
	वापस ret;
पूर्ण

/**
 * _ctl_mpt2_ioctl_compat - मुख्य ioctl entry poपूर्णांक (compat)
 * @file: ?
 * @cmd: ?
 * @arg: ?
 *
 * This routine handles 32 bit applications in 64bit os.
 */
अटल दीर्घ
_ctl_mpt2_ioctl_compat(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	ret = _ctl_ioctl_मुख्य(file, cmd, (व्योम __user *)arg, 1, MPI2_VERSION);
	वापस ret;
पूर्ण
#पूर्ण_अगर

/* scsi host attributes */
/**
 * version_fw_show - firmware version
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
version_fw_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%02d.%02d.%02d.%02d\n",
	    (ioc->facts.FWVersion.Word & 0xFF000000) >> 24,
	    (ioc->facts.FWVersion.Word & 0x00FF0000) >> 16,
	    (ioc->facts.FWVersion.Word & 0x0000FF00) >> 8,
	    ioc->facts.FWVersion.Word & 0x000000FF);
पूर्ण
अटल DEVICE_ATTR_RO(version_fw);

/**
 * version_bios_show - bios version
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
version_bios_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	u32 version = le32_to_cpu(ioc->bios_pg3.BiosVersion);

	वापस snम_लिखो(buf, PAGE_SIZE, "%02d.%02d.%02d.%02d\n",
	    (version & 0xFF000000) >> 24,
	    (version & 0x00FF0000) >> 16,
	    (version & 0x0000FF00) >> 8,
	    version & 0x000000FF);
पूर्ण
अटल DEVICE_ATTR_RO(version_bios);

/**
 * version_mpi_show - MPI (message passing पूर्णांकerface) version
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
version_mpi_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%03x.%02x\n",
	    ioc->facts.MsgVersion, ioc->facts.HeaderVersion >> 8);
पूर्ण
अटल DEVICE_ATTR_RO(version_mpi);

/**
 * version_product_show - product name
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
version_product_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, 16, "%s\n", ioc->manu_pg0.ChipName);
पूर्ण
अटल DEVICE_ATTR_RO(version_product);

/**
 * version_nvdata_persistent_show - ndvata persistent version
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
version_nvdata_persistent_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%08xh\n",
	    le32_to_cpu(ioc->iounit_pg0.NvdataVersionPersistent.Word));
पूर्ण
अटल DEVICE_ATTR_RO(version_nvdata_persistent);

/**
 * version_nvdata_शेष_show - nvdata शेष version
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
version_nvdata_शेष_show(काष्ठा device *cdev, काष्ठा device_attribute
	*attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%08xh\n",
	    le32_to_cpu(ioc->iounit_pg0.NvdataVersionDefault.Word));
पूर्ण
अटल DEVICE_ATTR_RO(version_nvdata_शेष);

/**
 * board_name_show - board name
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
board_name_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, 16, "%s\n", ioc->manu_pg0.BoardName);
पूर्ण
अटल DEVICE_ATTR_RO(board_name);

/**
 * board_assembly_show - board assembly name
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
board_assembly_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, 16, "%s\n", ioc->manu_pg0.BoardAssembly);
पूर्ण
अटल DEVICE_ATTR_RO(board_assembly);

/**
 * board_tracer_show - board tracer number
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
board_tracer_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, 16, "%s\n", ioc->manu_pg0.BoardTracerNumber);
पूर्ण
अटल DEVICE_ATTR_RO(board_tracer);

/**
 * io_delay_show - io missing delay
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is क्रम firmware implemention क्रम deboucing device
 * removal events.
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
io_delay_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%02d\n", ioc->io_missing_delay);
पूर्ण
अटल DEVICE_ATTR_RO(io_delay);

/**
 * device_delay_show - device missing delay
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is क्रम firmware implemention क्रम deboucing device
 * removal events.
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
device_delay_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%02d\n", ioc->device_missing_delay);
पूर्ण
अटल DEVICE_ATTR_RO(device_delay);

/**
 * fw_queue_depth_show - global credits
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is firmware queue depth limit
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
fw_queue_depth_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%02d\n", ioc->facts.RequestCredit);
पूर्ण
अटल DEVICE_ATTR_RO(fw_queue_depth);

/**
 * host_sas_address_show - sas address
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is the controller sas address
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
host_sas_address_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)

अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%016llx\n",
	    (अचिन्हित दीर्घ दीर्घ)ioc->sas_hba.sas_address);
पूर्ण
अटल DEVICE_ATTR_RO(host_sas_address);

/**
 * logging_level_show - logging level
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
logging_level_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%08xh\n", ioc->logging_level);
पूर्ण
अटल sमाप_प्रकार
logging_level_store(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	पूर्णांक val = 0;

	अगर (माला_पूछो(buf, "%x", &val) != 1)
		वापस -EINVAL;

	ioc->logging_level = val;
	ioc_info(ioc, "logging_level=%08xh\n",
		 ioc->logging_level);
	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR_RW(logging_level);

/**
 * fwfault_debug_show - show/store fwfault_debug
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * mpt3sas_fwfault_debug is command line option
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
fwfault_debug_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ioc->fwfault_debug);
पूर्ण
अटल sमाप_प्रकार
fwfault_debug_store(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	पूर्णांक val = 0;

	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;

	ioc->fwfault_debug = val;
	ioc_info(ioc, "fwfault_debug=%d\n",
		 ioc->fwfault_debug);
	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR_RW(fwfault_debug);

/**
 * ioc_reset_count_show - ioc reset count
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is firmware queue depth limit
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
ioc_reset_count_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ioc->ioc_reset_count);
पूर्ण
अटल DEVICE_ATTR_RO(ioc_reset_count);

/**
 * reply_queue_count_show - number of reply queues
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is number of reply queues
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
reply_queue_count_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 reply_queue_count;
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	अगर ((ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_MSI_X_INDEX) && ioc->msix_enable)
		reply_queue_count = ioc->reply_queue_count;
	अन्यथा
		reply_queue_count = 1;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", reply_queue_count);
पूर्ण
अटल DEVICE_ATTR_RO(reply_queue_count);

/**
 * BRM_status_show - Backup Rail Monitor Status
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is number of reply queues
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
BRM_status_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	Mpi2IOUnitPage3_t io_unit_pg3;
	Mpi2ConfigReply_t mpi_reply;
	u16 backup_rail_monitor_status = 0;
	u16 ioc_status;
	पूर्णांक sz;
	sमाप_प्रकार rc = 0;

	अगर (!ioc->is_warpdrive) अणु
		ioc_err(ioc, "%s: BRM attribute is only for warpdrive\n",
			__func__);
		वापस 0;
	पूर्ण
	/* pci_access_mutex lock acquired by sysfs show path */
	mutex_lock(&ioc->pci_access_mutex);
	अगर (ioc->pci_error_recovery || ioc->हटाओ_host)
		जाओ out;

	sz = माप(io_unit_pg3);
	स_रखो(&io_unit_pg3, 0, sz);

	अगर (mpt3sas_config_get_iounit_pg3(ioc, &mpi_reply, &io_unit_pg3, sz) !=
	    0) अणु
		ioc_err(ioc, "%s: failed reading iounit_pg3\n",
			__func__);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "%s: iounit_pg3 failed with ioc_status(0x%04x)\n",
			__func__, ioc_status);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (io_unit_pg3.GPIOCount < 25) अणु
		ioc_err(ioc, "%s: iounit_pg3.GPIOCount less than 25 entries, detected (%d) entries\n",
			__func__, io_unit_pg3.GPIOCount);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* BRM status is in bit zero of GPIOVal[24] */
	backup_rail_monitor_status = le16_to_cpu(io_unit_pg3.GPIOVal[24]);
	rc = snम_लिखो(buf, PAGE_SIZE, "%d\n", (backup_rail_monitor_status & 1));

 out:
	mutex_unlock(&ioc->pci_access_mutex);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(BRM_status);

काष्ठा DIAG_BUFFER_START अणु
	__le32	Size;
	__le32	DiagVersion;
	u8	BufferType;
	u8	Reserved[3];
	__le32	Reserved1;
	__le32	Reserved2;
	__le32	Reserved3;
पूर्ण;

/**
 * host_trace_buffer_size_show - host buffer size (trace only)
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
host_trace_buffer_size_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	u32 size = 0;
	काष्ठा DIAG_BUFFER_START *request_data;

	अगर (!ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE]) अणु
		ioc_err(ioc, "%s: host_trace_buffer is not registered\n",
			__func__);
		वापस 0;
	पूर्ण

	अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		ioc_err(ioc, "%s: host_trace_buffer is not registered\n",
			__func__);
		वापस 0;
	पूर्ण

	request_data = (काष्ठा DIAG_BUFFER_START *)
	    ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE];
	अगर ((le32_to_cpu(request_data->DiagVersion) == 0x00000000 ||
	    le32_to_cpu(request_data->DiagVersion) == 0x01000000 ||
	    le32_to_cpu(request_data->DiagVersion) == 0x01010000) &&
	    le32_to_cpu(request_data->Reserved3) == 0x4742444c)
		size = le32_to_cpu(request_data->Size);

	ioc->ring_buffer_sz = size;
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", size);
पूर्ण
अटल DEVICE_ATTR_RO(host_trace_buffer_size);

/**
 * host_trace_buffer_show - firmware ring buffer (trace only)
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' shost attribute.
 *
 * You will only be able to पढ़ो 4k bytes of ring buffer at a समय.
 * In order to पढ़ो beyond 4k bytes, you will have to ग_लिखो out the
 * offset to the same attribute, it will move the poपूर्णांकer.
 */
अटल sमाप_प्रकार
host_trace_buffer_show(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	व्योम *request_data;
	u32 size;

	अगर (!ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE]) अणु
		ioc_err(ioc, "%s: host_trace_buffer is not registered\n",
			__func__);
		वापस 0;
	पूर्ण

	अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		ioc_err(ioc, "%s: host_trace_buffer is not registered\n",
			__func__);
		वापस 0;
	पूर्ण

	अगर (ioc->ring_buffer_offset > ioc->ring_buffer_sz)
		वापस 0;

	size = ioc->ring_buffer_sz - ioc->ring_buffer_offset;
	size = (size >= PAGE_SIZE) ? (PAGE_SIZE - 1) : size;
	request_data = ioc->diag_buffer[0] + ioc->ring_buffer_offset;
	स_नकल(buf, request_data, size);
	वापस size;
पूर्ण

अटल sमाप_प्रकार
host_trace_buffer_store(काष्ठा device *cdev, काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	पूर्णांक val = 0;

	अगर (माला_पूछो(buf, "%d", &val) != 1)
		वापस -EINVAL;

	ioc->ring_buffer_offset = val;
	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR_RW(host_trace_buffer);


/*****************************************/

/**
 * host_trace_buffer_enable_show - firmware ring buffer (trace only)
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' shost attribute.
 *
 * This is a mechnism to post/release host_trace_buffers
 */
अटल sमाप_प्रकार
host_trace_buffer_enable_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	अगर ((!ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE]) ||
	   ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0))
		वापस snम_लिखो(buf, PAGE_SIZE, "off\n");
	अन्यथा अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_RELEASED))
		वापस snम_लिखो(buf, PAGE_SIZE, "release\n");
	अन्यथा
		वापस snम_लिखो(buf, PAGE_SIZE, "post\n");
पूर्ण

अटल sमाप_प्रकार
host_trace_buffer_enable_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अक्षर str[10] = "";
	काष्ठा mpt3_diag_रेजिस्टर diag_रेजिस्टर;
	u8 issue_reset = 0;

	/* करोn't allow post/release occurr जबतक recovery is active */
	अगर (ioc->shost_recovery || ioc->हटाओ_host ||
	    ioc->pci_error_recovery || ioc->is_driver_loading)
		वापस -EBUSY;

	अगर (माला_पूछो(buf, "%9s", str) != 1)
		वापस -EINVAL;

	अगर (!म_भेद(str, "post")) अणु
		/* निकास out अगर host buffers are alपढ़ोy posted */
		अगर ((ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE]) &&
		    (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_REGISTERED) &&
		    ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_RELEASED) == 0))
			जाओ out;
		स_रखो(&diag_रेजिस्टर, 0, माप(काष्ठा mpt3_diag_रेजिस्टर));
		ioc_info(ioc, "posting host trace buffers\n");
		diag_रेजिस्टर.buffer_type = MPI2_DIAG_BUF_TYPE_TRACE;

		अगर (ioc->manu_pg11.HostTraceBufferMaxSizeKB != 0 &&
		    ioc->diag_buffer_sz[MPI2_DIAG_BUF_TYPE_TRACE] != 0) अणु
			/* post the same buffer allocated previously */
			diag_रेजिस्टर.requested_buffer_size =
			    ioc->diag_buffer_sz[MPI2_DIAG_BUF_TYPE_TRACE];
		पूर्ण अन्यथा अणु
			/*
			 * Free the diag buffer memory which was previously
			 * allocated by an application.
			 */
			अगर ((ioc->diag_buffer_sz[MPI2_DIAG_BUF_TYPE_TRACE] != 0)
			    &&
			    (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
			    MPT3_DIAG_BUFFER_IS_APP_OWNED)) अणु
				dma_मुक्त_coherent(&ioc->pdev->dev,
						  ioc->diag_buffer_sz[MPI2_DIAG_BUF_TYPE_TRACE],
						  ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE],
						  ioc->diag_buffer_dma[MPI2_DIAG_BUF_TYPE_TRACE]);
				ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE] =
				    शून्य;
			पूर्ण

			diag_रेजिस्टर.requested_buffer_size = (1024 * 1024);
		पूर्ण

		diag_रेजिस्टर.unique_id =
		    (ioc->hba_mpi_version_beदीर्घed == MPI2_VERSION) ?
		    (MPT2DIAGBUFFUNIQUEID):(MPT3DIAGBUFFUNIQUEID);
		ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] = 0;
		_ctl_diag_रेजिस्टर_2(ioc,  &diag_रेजिस्टर);
		अगर (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_REGISTERED) अणु
			ioc_info(ioc,
			    "Trace buffer %d KB allocated through sysfs\n",
			    diag_रेजिस्टर.requested_buffer_size>>10);
			अगर (ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION)
				ioc->diag_buffer_status[
				    MPI2_DIAG_BUF_TYPE_TRACE] |=
				    MPT3_DIAG_BUFFER_IS_DRIVER_ALLOCATED;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(str, "release")) अणु
		/* निकास out अगर host buffers are alपढ़ोy released */
		अगर (!ioc->diag_buffer[MPI2_DIAG_BUF_TYPE_TRACE])
			जाओ out;
		अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0)
			जाओ out;
		अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
		    MPT3_DIAG_BUFFER_IS_RELEASED))
			जाओ out;
		ioc_info(ioc, "releasing host trace buffer\n");
		ioc->htb_rel.buffer_rel_condition = MPT3_DIAG_BUFFER_REL_SYSFS;
		mpt3sas_send_diag_release(ioc, MPI2_DIAG_BUF_TYPE_TRACE,
		    &issue_reset);
	पूर्ण

 out:
	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR_RW(host_trace_buffer_enable);

/*********** diagnostic trigger suppport *********************************/

/**
 * diag_trigger_master_show - show the diag_trigger_master attribute
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
diag_trigger_master_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)

अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार rc;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	rc = माप(काष्ठा SL_WH_MASTER_TRIGGER_T);
	स_नकल(buf, &ioc->diag_trigger_master, rc);
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	वापस rc;
पूर्ण

/**
 * diag_trigger_master_store - store the diag_trigger_master attribute
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 * @count: ?
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
diag_trigger_master_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)

अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार rc;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	rc = min(माप(काष्ठा SL_WH_MASTER_TRIGGER_T), count);
	स_रखो(&ioc->diag_trigger_master, 0,
	    माप(काष्ठा SL_WH_MASTER_TRIGGER_T));
	स_नकल(&ioc->diag_trigger_master, buf, rc);
	ioc->diag_trigger_master.MasterData |=
	    (MASTER_TRIGGER_FW_FAULT + MASTER_TRIGGER_ADAPTER_RESET);
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(diag_trigger_master);


/**
 * diag_trigger_event_show - show the diag_trigger_event attribute
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
diag_trigger_event_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार rc;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	rc = माप(काष्ठा SL_WH_EVENT_TRIGGERS_T);
	स_नकल(buf, &ioc->diag_trigger_event, rc);
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	वापस rc;
पूर्ण

/**
 * diag_trigger_event_store - store the diag_trigger_event attribute
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 * @count: ?
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
diag_trigger_event_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)

अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार sz;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	sz = min(माप(काष्ठा SL_WH_EVENT_TRIGGERS_T), count);
	स_रखो(&ioc->diag_trigger_event, 0,
	    माप(काष्ठा SL_WH_EVENT_TRIGGERS_T));
	स_नकल(&ioc->diag_trigger_event, buf, sz);
	अगर (ioc->diag_trigger_event.ValidEntries > NUM_VALID_ENTRIES)
		ioc->diag_trigger_event.ValidEntries = NUM_VALID_ENTRIES;
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	वापस sz;
पूर्ण
अटल DEVICE_ATTR_RW(diag_trigger_event);


/**
 * diag_trigger_scsi_show - show the diag_trigger_scsi attribute
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
diag_trigger_scsi_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार rc;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	rc = माप(काष्ठा SL_WH_SCSI_TRIGGERS_T);
	स_नकल(buf, &ioc->diag_trigger_scsi, rc);
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	वापस rc;
पूर्ण

/**
 * diag_trigger_scsi_store - store the diag_trigger_scsi attribute
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 * @count: ?
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
diag_trigger_scsi_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार sz;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	sz = min(माप(ioc->diag_trigger_scsi), count);
	स_रखो(&ioc->diag_trigger_scsi, 0, माप(ioc->diag_trigger_scsi));
	स_नकल(&ioc->diag_trigger_scsi, buf, sz);
	अगर (ioc->diag_trigger_scsi.ValidEntries > NUM_VALID_ENTRIES)
		ioc->diag_trigger_scsi.ValidEntries = NUM_VALID_ENTRIES;
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	वापस sz;
पूर्ण
अटल DEVICE_ATTR_RW(diag_trigger_scsi);


/**
 * diag_trigger_mpi_show - show the diag_trigger_mpi attribute
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
diag_trigger_mpi_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार rc;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	rc = माप(काष्ठा SL_WH_MPI_TRIGGERS_T);
	स_नकल(buf, &ioc->diag_trigger_mpi, rc);
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	वापस rc;
पूर्ण

/**
 * diag_trigger_mpi_store - store the diag_trigger_mpi attribute
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 * @count: ?
 *
 * A sysfs 'read/write' shost attribute.
 */
अटल sमाप_प्रकार
diag_trigger_mpi_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार sz;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	sz = min(माप(काष्ठा SL_WH_MPI_TRIGGERS_T), count);
	स_रखो(&ioc->diag_trigger_mpi, 0,
	    माप(ioc->diag_trigger_mpi));
	स_नकल(&ioc->diag_trigger_mpi, buf, sz);
	अगर (ioc->diag_trigger_mpi.ValidEntries > NUM_VALID_ENTRIES)
		ioc->diag_trigger_mpi.ValidEntries = NUM_VALID_ENTRIES;
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
	वापस sz;
पूर्ण

अटल DEVICE_ATTR_RW(diag_trigger_mpi);

/*********** diagnostic trigger suppport *** END ****************************/

/*****************************************/

/**
 * drv_support_biपंचांगap_show - driver supported feature biपंचांगap
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: unused
 * @buf: the buffer वापसed
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
drv_support_biपंचांगap_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n", ioc->drv_support_biपंचांगap);
पूर्ण
अटल DEVICE_ATTR_RO(drv_support_biपंचांगap);

/**
 * enable_sdev_max_qd_show - display whether sdev max qd is enabled/disabled
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: unused
 * @buf: the buffer वापसed
 *
 * A sysfs पढ़ो/ग_लिखो shost attribute. This attribute is used to set the
 * tarमाला_लो queue depth to HBA IO queue depth अगर this attribute is enabled.
 */
अटल sमाप_प्रकार
enable_sdev_max_qd_show(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ioc->enable_sdev_max_qd);
पूर्ण

/**
 * enable_sdev_max_qd_store - Enable/disable sdev max qd
 * @cdev: poपूर्णांकer to embedded class device
 * @attr: unused
 * @buf: the buffer वापसed
 * @count: unused
 *
 * A sysfs पढ़ो/ग_लिखो shost attribute. This attribute is used to set the
 * tarमाला_लो queue depth to HBA IO queue depth अगर this attribute is enabled.
 * If this attribute is disabled then tarमाला_लो will have corresponding शेष
 * queue depth.
 */
अटल sमाप_प्रकार
enable_sdev_max_qd_store(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	पूर्णांक val = 0;
	काष्ठा scsi_device *sdev;
	काष्ठा _raid_device *raid_device;
	पूर्णांक qdepth;

	अगर (kstrtoपूर्णांक(buf, 0, &val) != 0)
		वापस -EINVAL;

	चयन (val) अणु
	हाल 0:
		ioc->enable_sdev_max_qd = 0;
		shost_क्रम_each_device(sdev, ioc->shost) अणु
			sas_device_priv_data = sdev->hostdata;
			अगर (!sas_device_priv_data)
				जारी;
			sas_target_priv_data = sas_device_priv_data->sas_target;
			अगर (!sas_target_priv_data)
				जारी;

			अगर (sas_target_priv_data->flags &
			    MPT_TARGET_FLAGS_VOLUME) अणु
				raid_device =
				    mpt3sas_raid_device_find_by_handle(ioc,
				    sas_target_priv_data->handle);

				चयन (raid_device->volume_type) अणु
				हाल MPI2_RAID_VOL_TYPE_RAID0:
					अगर (raid_device->device_info &
					    MPI2_SAS_DEVICE_INFO_SSP_TARGET)
						qdepth =
						    MPT3SAS_SAS_QUEUE_DEPTH;
					अन्यथा
						qdepth =
						    MPT3SAS_SATA_QUEUE_DEPTH;
					अवरोध;
				हाल MPI2_RAID_VOL_TYPE_RAID1E:
				हाल MPI2_RAID_VOL_TYPE_RAID1:
				हाल MPI2_RAID_VOL_TYPE_RAID10:
				हाल MPI2_RAID_VOL_TYPE_UNKNOWN:
				शेष:
					qdepth = MPT3SAS_RAID_QUEUE_DEPTH;
				पूर्ण
			पूर्ण अन्यथा अगर (sas_target_priv_data->flags &
			    MPT_TARGET_FLAGS_PCIE_DEVICE)
				qdepth = MPT3SAS_NVME_QUEUE_DEPTH;
			अन्यथा
				qdepth = MPT3SAS_SAS_QUEUE_DEPTH;

			mpt3sas_scsih_change_queue_depth(sdev, qdepth);
		पूर्ण
		अवरोध;
	हाल 1:
		ioc->enable_sdev_max_qd = 1;
		shost_क्रम_each_device(sdev, ioc->shost)
			mpt3sas_scsih_change_queue_depth(sdev,
			    shost->can_queue);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR_RW(enable_sdev_max_qd);

काष्ठा device_attribute *mpt3sas_host_attrs[] = अणु
	&dev_attr_version_fw,
	&dev_attr_version_bios,
	&dev_attr_version_mpi,
	&dev_attr_version_product,
	&dev_attr_version_nvdata_persistent,
	&dev_attr_version_nvdata_शेष,
	&dev_attr_board_name,
	&dev_attr_board_assembly,
	&dev_attr_board_tracer,
	&dev_attr_io_delay,
	&dev_attr_device_delay,
	&dev_attr_logging_level,
	&dev_attr_fwfault_debug,
	&dev_attr_fw_queue_depth,
	&dev_attr_host_sas_address,
	&dev_attr_ioc_reset_count,
	&dev_attr_host_trace_buffer_size,
	&dev_attr_host_trace_buffer,
	&dev_attr_host_trace_buffer_enable,
	&dev_attr_reply_queue_count,
	&dev_attr_diag_trigger_master,
	&dev_attr_diag_trigger_event,
	&dev_attr_diag_trigger_scsi,
	&dev_attr_diag_trigger_mpi,
	&dev_attr_drv_support_biपंचांगap,
	&dev_attr_BRM_status,
	&dev_attr_enable_sdev_max_qd,
	शून्य,
पूर्ण;

/* device attributes */

/**
 * sas_address_show - sas address
 * @dev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is the sas address क्रम the target
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
sas_address_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data = sdev->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%016llx\n",
	    (अचिन्हित दीर्घ दीर्घ)sas_device_priv_data->sas_target->sas_address);
पूर्ण
अटल DEVICE_ATTR_RO(sas_address);

/**
 * sas_device_handle_show - device handle
 * @dev: poपूर्णांकer to embedded class device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * This is the firmware asचिन्हित device handle
 *
 * A sysfs 'read-only' shost attribute.
 */
अटल sमाप_प्रकार
sas_device_handle_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data = sdev->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%04x\n",
	    sas_device_priv_data->sas_target->handle);
पूर्ण
अटल DEVICE_ATTR_RO(sas_device_handle);

/**
 * sas_ncq_prio_enable_show - send prioritized io commands to device
 * @dev: poपूर्णांकer to embedded device
 * @attr: ?
 * @buf: the buffer वापसed
 *
 * A sysfs 'read/write' sdev attribute, only works with SATA
 */
अटल sमाप_प्रकार
sas_ncq_prio_enable_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data = sdev->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			sas_device_priv_data->ncq_prio_enable);
पूर्ण

अटल sमाप_प्रकार
sas_ncq_prio_enable_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data = sdev->hostdata;
	bool ncq_prio_enable = 0;

	अगर (kstrtobool(buf, &ncq_prio_enable))
		वापस -EINVAL;

	अगर (!scsih_ncq_prio_supp(sdev))
		वापस -EINVAL;

	sas_device_priv_data->ncq_prio_enable = ncq_prio_enable;
	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR_RW(sas_ncq_prio_enable);

काष्ठा device_attribute *mpt3sas_dev_attrs[] = अणु
	&dev_attr_sas_address,
	&dev_attr_sas_device_handle,
	&dev_attr_sas_ncq_prio_enable,
	शून्य,
पूर्ण;

/* file operations table क्रम mpt3ctl device */
अटल स्थिर काष्ठा file_operations ctl_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = _ctl_ioctl,
	.poll = _ctl_poll,
	.fasync = _ctl_fasync,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = _ctl_ioctl_compat,
#पूर्ण_अगर
पूर्ण;

/* file operations table क्रम mpt2ctl device */
अटल स्थिर काष्ठा file_operations ctl_gen2_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = _ctl_mpt2_ioctl,
	.poll = _ctl_poll,
	.fasync = _ctl_fasync,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = _ctl_mpt2_ioctl_compat,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा miscdevice ctl_dev = अणु
	.minor  = MPT3SAS_MINOR,
	.name   = MPT3SAS_DEV_NAME,
	.fops   = &ctl_fops,
पूर्ण;

अटल काष्ठा miscdevice gen2_ctl_dev = अणु
	.minor  = MPT2SAS_MINOR,
	.name   = MPT2SAS_DEV_NAME,
	.fops   = &ctl_gen2_fops,
पूर्ण;

/**
 * mpt3sas_ctl_init - मुख्य entry poपूर्णांक क्रम ctl.
 * @hbas_to_क्रमागतerate: ?
 */
व्योम
mpt3sas_ctl_init(uलघु hbas_to_क्रमागतerate)
अणु
	async_queue = शून्य;

	/* Don't रेजिस्टर mpt3ctl ioctl device अगर
	 * hbas_to_क्रमागतarate is one.
	 */
	अगर (hbas_to_क्रमागतerate != 1)
		अगर (misc_रेजिस्टर(&ctl_dev) < 0)
			pr_err("%s can't register misc device [minor=%d]\n",
			    MPT3SAS_DRIVER_NAME, MPT3SAS_MINOR);

	/* Don't रेजिस्टर mpt3ctl ioctl device अगर
	 * hbas_to_क्रमागतarate is two.
	 */
	अगर (hbas_to_क्रमागतerate != 2)
		अगर (misc_रेजिस्टर(&gen2_ctl_dev) < 0)
			pr_err("%s can't register misc device [minor=%d]\n",
			    MPT2SAS_DRIVER_NAME, MPT2SAS_MINOR);

	init_रुकोqueue_head(&ctl_poll_रुको);
पूर्ण

/**
 * mpt3sas_ctl_निकास - निकास poपूर्णांक क्रम ctl
 * @hbas_to_क्रमागतerate: ?
 */
व्योम
mpt3sas_ctl_निकास(uलघु hbas_to_क्रमागतerate)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc;
	पूर्णांक i;

	list_क्रम_each_entry(ioc, &mpt3sas_ioc_list, list) अणु

		/* मुक्त memory associated to diag buffers */
		क्रम (i = 0; i < MPI2_DIAG_BUF_TYPE_COUNT; i++) अणु
			अगर (!ioc->diag_buffer[i])
				जारी;
			dma_मुक्त_coherent(&ioc->pdev->dev,
					  ioc->diag_buffer_sz[i],
					  ioc->diag_buffer[i],
					  ioc->diag_buffer_dma[i]);
			ioc->diag_buffer[i] = शून्य;
			ioc->diag_buffer_status[i] = 0;
		पूर्ण

		kमुक्त(ioc->event_log);
	पूर्ण
	अगर (hbas_to_क्रमागतerate != 1)
		misc_deरेजिस्टर(&ctl_dev);
	अगर (hbas_to_क्रमागतerate != 2)
		misc_deरेजिस्टर(&gen2_ctl_dev);
पूर्ण
