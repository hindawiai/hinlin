<शैली गुरु>
/*
 * This module provides common API to set Diagnostic trigger क्रम MPT
 * (Message Passing Technology) based controllers
 *
 * This code is based on drivers/scsi/mpt3sas/mpt3sas_trigger_diag.c
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

/**
 * _mpt3sas_उठाओ_sigio - notअगरiy app
 * @ioc: per adapter object
 * @event_data: ?
 */
अटल व्योम
_mpt3sas_उठाओ_sigio(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T *event_data)
अणु
	Mpi2EventNotअगरicationReply_t *mpi_reply;
	u16 sz, event_data_sz;
	अचिन्हित दीर्घ flags;

	dTriggerDiagPrपूर्णांकk(ioc, ioc_info(ioc, "%s: enter\n", __func__));

	sz = दुरत्व(Mpi2EventNotअगरicationReply_t, EventData) +
	    माप(काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T) + 4;
	mpi_reply = kzalloc(sz, GFP_KERNEL);
	अगर (!mpi_reply)
		जाओ out;
	mpi_reply->Event = cpu_to_le16(MPI3_EVENT_DIAGNOSTIC_TRIGGER_FIRED);
	event_data_sz = (माप(काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T) + 4) / 4;
	mpi_reply->EventDataLength = cpu_to_le16(event_data_sz);
	स_नकल(&mpi_reply->EventData, event_data,
	    माप(काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T));
	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: add to driver event log\n",
				    __func__));
	mpt3sas_ctl_add_to_event_log(ioc, mpi_reply);
	kमुक्त(mpi_reply);
 out:

	/* clearing the diag_trigger_active flag */
	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);
	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: clearing diag_trigger_active flag\n",
				    __func__));
	ioc->diag_trigger_active = 0;
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);

	dTriggerDiagPrपूर्णांकk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
पूर्ण

/**
 * mpt3sas_process_trigger_data - process the event data क्रम the trigger
 * @ioc: per adapter object
 * @event_data: ?
 */
व्योम
mpt3sas_process_trigger_data(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T *event_data)
अणु
	u8 issue_reset = 0;
	u32 *trig_data = (u32 *)&event_data->u.master;

	dTriggerDiagPrपूर्णांकk(ioc, ioc_info(ioc, "%s: enter\n", __func__));

	/* release the diag buffer trace */
	अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) == 0) अणु
		/*
		 * add a log message so that user knows which event caused
		 * the release
		 */
		ioc_info(ioc,
		    "%s: Releasing the trace buffer. Trigger_Type 0x%08x, Data[0] 0x%08x, Data[1] 0x%08x\n",
		    __func__, event_data->trigger_type,
		    trig_data[0], trig_data[1]);
		mpt3sas_send_diag_release(ioc, MPI2_DIAG_BUF_TYPE_TRACE,
		    &issue_reset);
	पूर्ण

	ioc->htb_rel.buffer_rel_condition = MPT3_DIAG_BUFFER_REL_TRIGGER;
	अगर (event_data) अणु
		ioc->htb_rel.trigger_type = event_data->trigger_type;
		चयन (event_data->trigger_type) अणु
		हाल MPT3SAS_TRIGGER_SCSI:
			स_नकल(&ioc->htb_rel.trigger_info_dwords,
			    &event_data->u.scsi,
			    माप(काष्ठा SL_WH_SCSI_TRIGGER_T));
			अवरोध;
		हाल MPT3SAS_TRIGGER_MPI:
			स_नकल(&ioc->htb_rel.trigger_info_dwords,
			    &event_data->u.mpi,
			    माप(काष्ठा SL_WH_MPI_TRIGGER_T));
			अवरोध;
		हाल MPT3SAS_TRIGGER_MASTER:
			ioc->htb_rel.trigger_info_dwords[0] =
			    event_data->u.master.MasterData;
			अवरोध;
		हाल MPT3SAS_TRIGGER_EVENT:
			स_नकल(&ioc->htb_rel.trigger_info_dwords,
			    &event_data->u.event,
			    माप(काष्ठा SL_WH_EVENT_TRIGGER_T));
			अवरोध;
		शेष:
			ioc_err(ioc, "%d - Is not a valid Trigger type\n",
			    event_data->trigger_type);
			अवरोध;
		पूर्ण
	पूर्ण
	_mpt3sas_उठाओ_sigio(ioc, event_data);

	dTriggerDiagPrपूर्णांकk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
पूर्ण

/**
 * mpt3sas_trigger_master - Master trigger handler
 * @ioc: per adapter object
 * @trigger_biपंचांगask:
 *
 */
व्योम
mpt3sas_trigger_master(काष्ठा MPT3SAS_ADAPTER *ioc, u32 trigger_biपंचांगask)
अणु
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T event_data;
	अचिन्हित दीर्घ flags;
	u8 found_match = 0;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);

	अगर (trigger_biपंचांगask & MASTER_TRIGGER_FW_FAULT ||
	    trigger_biपंचांगask & MASTER_TRIGGER_ADAPTER_RESET)
		जाओ by_pass_checks;

	/* check to see अगर trace buffers are currently रेजिस्टरed */
	अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		वापस;
	पूर्ण

	/* check to see अगर trace buffers are currently released */
	अगर (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		वापस;
	पूर्ण

 by_pass_checks:

	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enter - trigger_bitmask = 0x%08x\n",
				    __func__, trigger_biपंचांगask));

	/* करोn't send trigger अगर an trigger is currently active */
	अगर (ioc->diag_trigger_active) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		जाओ out;
	पूर्ण

	/* check क्रम the trigger condition */
	अगर (ioc->diag_trigger_master.MasterData & trigger_biपंचांगask) अणु
		found_match = 1;
		ioc->diag_trigger_active = 1;
		dTriggerDiagPrपूर्णांकk(ioc,
				   ioc_info(ioc, "%s: setting diag_trigger_active flag\n",
					    __func__));
	पूर्ण
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);

	अगर (!found_match)
		जाओ out;

	स_रखो(&event_data, 0, माप(काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T));
	event_data.trigger_type = MPT3SAS_TRIGGER_MASTER;
	event_data.u.master.MasterData = trigger_biपंचांगask;

	अगर (trigger_biपंचांगask & MASTER_TRIGGER_FW_FAULT ||
	    trigger_biपंचांगask & MASTER_TRIGGER_ADAPTER_RESET) अणु
		ioc->htb_rel.trigger_type = MPT3SAS_TRIGGER_MASTER;
		ioc->htb_rel.trigger_info_dwords[0] = trigger_biपंचांगask;
		अगर (ioc->reset_from_user)
			ioc->htb_rel.trigger_info_dwords[1] =
			    MPT_DIAG_RESET_ISSUED_BY_USER;
		_mpt3sas_उठाओ_sigio(ioc, &event_data);
	पूर्ण अन्यथा
		mpt3sas_send_trigger_data_event(ioc, &event_data);

 out:
	dTriggerDiagPrपूर्णांकk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
पूर्ण

/**
 * mpt3sas_trigger_event - Event trigger handler
 * @ioc: per adapter object
 * @event: ?
 * @log_entry_qualअगरier: ?
 *
 */
व्योम
mpt3sas_trigger_event(काष्ठा MPT3SAS_ADAPTER *ioc, u16 event,
	u16 log_entry_qualअगरier)
अणु
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T event_data;
	काष्ठा SL_WH_EVENT_TRIGGER_T *event_trigger;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	u8 found_match;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);

	/* check to see अगर trace buffers are currently रेजिस्टरed */
	अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		वापस;
	पूर्ण

	/* check to see अगर trace buffers are currently released */
	अगर (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		वापस;
	पूर्ण

	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enter - event = 0x%04x, log_entry_qualifier = 0x%04x\n",
				    __func__, event, log_entry_qualअगरier));

	/* करोn't send trigger अगर an trigger is currently active */
	अगर (ioc->diag_trigger_active) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		जाओ out;
	पूर्ण

	/* check क्रम the trigger condition */
	event_trigger = ioc->diag_trigger_event.EventTriggerEntry;
	क्रम (i = 0 , found_match = 0; i < ioc->diag_trigger_event.ValidEntries
	    && !found_match; i++, event_trigger++) अणु
		अगर (event_trigger->EventValue != event)
			जारी;
		अगर (event == MPI2_EVENT_LOG_ENTRY_ADDED) अणु
			अगर (event_trigger->LogEntryQualअगरier ==
			    log_entry_qualअगरier)
				found_match = 1;
			जारी;
		पूर्ण
		found_match = 1;
		ioc->diag_trigger_active = 1;
		dTriggerDiagPrपूर्णांकk(ioc,
				   ioc_info(ioc, "%s: setting diag_trigger_active flag\n",
					    __func__));
	पूर्ण
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);

	अगर (!found_match)
		जाओ out;

	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: setting diag_trigger_active flag\n",
				    __func__));
	स_रखो(&event_data, 0, माप(काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T));
	event_data.trigger_type = MPT3SAS_TRIGGER_EVENT;
	event_data.u.event.EventValue = event;
	event_data.u.event.LogEntryQualअगरier = log_entry_qualअगरier;
	mpt3sas_send_trigger_data_event(ioc, &event_data);
 out:
	dTriggerDiagPrपूर्णांकk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
पूर्ण

/**
 * mpt3sas_trigger_scsi - SCSI trigger handler
 * @ioc: per adapter object
 * @sense_key: ?
 * @asc: ?
 * @ascq: ?
 *
 */
व्योम
mpt3sas_trigger_scsi(काष्ठा MPT3SAS_ADAPTER *ioc, u8 sense_key, u8 asc,
	u8 ascq)
अणु
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T event_data;
	काष्ठा SL_WH_SCSI_TRIGGER_T *scsi_trigger;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	u8 found_match;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);

	/* check to see अगर trace buffers are currently रेजिस्टरed */
	अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		वापस;
	पूर्ण

	/* check to see अगर trace buffers are currently released */
	अगर (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		वापस;
	पूर्ण

	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enter - sense_key = 0x%02x, asc = 0x%02x, ascq = 0x%02x\n",
				    __func__, sense_key, asc, ascq));

	/* करोn't send trigger अगर an trigger is currently active */
	अगर (ioc->diag_trigger_active) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		जाओ out;
	पूर्ण

	/* check क्रम the trigger condition */
	scsi_trigger = ioc->diag_trigger_scsi.SCSITriggerEntry;
	क्रम (i = 0 , found_match = 0; i < ioc->diag_trigger_scsi.ValidEntries
	    && !found_match; i++, scsi_trigger++) अणु
		अगर (scsi_trigger->SenseKey != sense_key)
			जारी;
		अगर (!(scsi_trigger->ASC == 0xFF || scsi_trigger->ASC == asc))
			जारी;
		अगर (!(scsi_trigger->ASCQ == 0xFF || scsi_trigger->ASCQ == ascq))
			जारी;
		found_match = 1;
		ioc->diag_trigger_active = 1;
	पूर्ण
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);

	अगर (!found_match)
		जाओ out;

	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: setting diag_trigger_active flag\n",
				    __func__));
	स_रखो(&event_data, 0, माप(काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T));
	event_data.trigger_type = MPT3SAS_TRIGGER_SCSI;
	event_data.u.scsi.SenseKey = sense_key;
	event_data.u.scsi.ASC = asc;
	event_data.u.scsi.ASCQ = ascq;
	mpt3sas_send_trigger_data_event(ioc, &event_data);
 out:
	dTriggerDiagPrपूर्णांकk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
पूर्ण

/**
 * mpt3sas_trigger_mpi - MPI trigger handler
 * @ioc: per adapter object
 * @ioc_status: ?
 * @loginfo: ?
 *
 */
व्योम
mpt3sas_trigger_mpi(काष्ठा MPT3SAS_ADAPTER *ioc, u16 ioc_status, u32 loginfo)
अणु
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T event_data;
	काष्ठा SL_WH_MPI_TRIGGER_T *mpi_trigger;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	u8 found_match;

	spin_lock_irqsave(&ioc->diag_trigger_lock, flags);

	/* check to see अगर trace buffers are currently रेजिस्टरed */
	अगर ((ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_REGISTERED) == 0) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		वापस;
	पूर्ण

	/* check to see अगर trace buffers are currently released */
	अगर (ioc->diag_buffer_status[MPI2_DIAG_BUF_TYPE_TRACE] &
	    MPT3_DIAG_BUFFER_IS_RELEASED) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		वापस;
	पूर्ण

	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enter - ioc_status = 0x%04x, loginfo = 0x%08x\n",
				    __func__, ioc_status, loginfo));

	/* करोn't send trigger अगर an trigger is currently active */
	अगर (ioc->diag_trigger_active) अणु
		spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);
		जाओ out;
	पूर्ण

	/* check क्रम the trigger condition */
	mpi_trigger = ioc->diag_trigger_mpi.MPITriggerEntry;
	क्रम (i = 0 , found_match = 0; i < ioc->diag_trigger_mpi.ValidEntries
	    && !found_match; i++, mpi_trigger++) अणु
		अगर (mpi_trigger->IOCStatus != ioc_status)
			जारी;
		अगर (!(mpi_trigger->IocLogInfo == 0xFFFFFFFF ||
		    mpi_trigger->IocLogInfo == loginfo))
			जारी;
		found_match = 1;
		ioc->diag_trigger_active = 1;
	पूर्ण
	spin_unlock_irqrestore(&ioc->diag_trigger_lock, flags);

	अगर (!found_match)
		जाओ out;

	dTriggerDiagPrपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: setting diag_trigger_active flag\n",
				    __func__));
	स_रखो(&event_data, 0, माप(काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T));
	event_data.trigger_type = MPT3SAS_TRIGGER_MPI;
	event_data.u.mpi.IOCStatus = ioc_status;
	event_data.u.mpi.IocLogInfo = loginfo;
	mpt3sas_send_trigger_data_event(ioc, &event_data);
 out:
	dTriggerDiagPrपूर्णांकk(ioc, ioc_info(ioc, "%s: exit\n",
					 __func__));
पूर्ण
