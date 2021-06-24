<शैली गुरु>
/*
 * This is the Fusion MPT base driver providing common API layer पूर्णांकerface
 * to set Diagnostic triggers क्रम MPT (Message Passing Technology) based
 * controllers
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
  /* Diagnostic Trigger Configuration Data Structures */

#अगर_अघोषित MPT3SAS_TRIGGER_DIAG_H_INCLUDED
#घोषणा MPT3SAS_TRIGGER_DIAG_H_INCLUDED

/* limitation on number of entries */
#घोषणा NUM_VALID_ENTRIES               (20)

/* trigger types */
#घोषणा MPT3SAS_TRIGGER_MASTER          (1)
#घोषणा MPT3SAS_TRIGGER_EVENT           (2)
#घोषणा MPT3SAS_TRIGGER_SCSI            (3)
#घोषणा MPT3SAS_TRIGGER_MPI             (4)

/* trigger names */
#घोषणा MASTER_TRIGGER_खाता_NAME        "diag_trigger_master"
#घोषणा EVENT_TRIGGERS_खाता_NAME        "diag_trigger_event"
#घोषणा SCSI_TRIGGERS_खाता_NAME         "diag_trigger_scsi"
#घोषणा MPI_TRIGGER_खाता_NAME           "diag_trigger_mpi"

/* master trigger biपंचांगask */
#घोषणा MASTER_TRIGGER_FW_FAULT         (0x00000001)
#घोषणा MASTER_TRIGGER_ADAPTER_RESET    (0x00000002)
#घोषणा MASTER_TRIGGER_TASK_MANAGMENT   (0x00000004)
#घोषणा MASTER_TRIGGER_DEVICE_REMOVAL   (0x00000008)

/* fake firmware event क्रम trigger */
#घोषणा MPI3_EVENT_DIAGNOSTIC_TRIGGER_FIRED	(0x6E)

/**
 * MasterTrigger is a single U32 passed to/from sysfs.
 *
 * Bit Flags (enables) include:
 * 1. FW Faults
 * 2. Adapter Reset issued by driver
 * 3. TMs
 * 4. Device Remove Event sent by FW
 */

काष्ठा SL_WH_MASTER_TRIGGER_T अणु
	uपूर्णांक32_t MasterData;
पूर्ण;

/**
 * काष्ठा SL_WH_EVENT_TRIGGER_T -  Definition of an event trigger element
 * @EventValue: Event Code to trigger on
 * @LogEntryQualअगरier: Type of FW event that logged (Log Entry Added Event only)
 *
 * Defines an event that should induce a DIAG_TRIGGER driver event अगर observed.
 */
काष्ठा SL_WH_EVENT_TRIGGER_T अणु
	uपूर्णांक16_t EventValue;
	uपूर्णांक16_t LogEntryQualअगरier;
पूर्ण;

/**
 * काष्ठा SL_WH_EVENT_TRIGGERS_T -  Structure passed to/from sysfs containing a
 *    list of Event Triggers to be monitored क्रम.
 * @ValidEntries: Number of _SL_WH_EVENT_TRIGGER_T काष्ठाures contained in this
 *    काष्ठाure.
 * @EventTriggerEntry: List of Event trigger elements.
 *
 * This binary काष्ठाure is transferred via sysfs to get/set Event Triggers
 * in the Linux Driver.
 */

काष्ठा SL_WH_EVENT_TRIGGERS_T अणु
	uपूर्णांक32_t ValidEntries;
	काष्ठा SL_WH_EVENT_TRIGGER_T EventTriggerEntry[NUM_VALID_ENTRIES];
पूर्ण;

/**
 * काष्ठा SL_WH_SCSI_TRIGGER_T -  Definition of a SCSI trigger element
 * @ASCQ: Additional Sense Code Qualअगरier.  Can be specअगरic or 0xFF क्रम
 *     wildcard.
 * @ASC: Additional Sense Code.  Can be specअगरic or 0xFF क्रम wildcard
 * @SenseKey: SCSI Sense Key
 *
 * Defines a sense key (single or many variants) that should induce a
 * DIAG_TRIGGER driver event अगर observed.
 */
काष्ठा SL_WH_SCSI_TRIGGER_T अणु
	U8 ASCQ;
	U8 ASC;
	U8 SenseKey;
	U8 Reserved;
पूर्ण;

/**
 * काष्ठा SL_WH_SCSI_TRIGGERS_T -  Structure passed to/from sysfs containing a
 *    list of SCSI sense codes that should trigger a DIAG_SERVICE event when
 *    observed.
 * @ValidEntries: Number of _SL_WH_SCSI_TRIGGER_T काष्ठाures contained in this
 *    काष्ठाure.
 * @SCSITriggerEntry: List of SCSI Sense Code trigger elements.
 *
 * This binary काष्ठाure is transferred via sysfs to get/set SCSI Sense Code
 * Triggers in the Linux Driver.
 */
काष्ठा SL_WH_SCSI_TRIGGERS_T अणु
	uपूर्णांक32_t ValidEntries;
	काष्ठा SL_WH_SCSI_TRIGGER_T SCSITriggerEntry[NUM_VALID_ENTRIES];
पूर्ण;

/**
 * काष्ठा SL_WH_MPI_TRIGGER_T -  Definition of an MPI trigger element
 * @IOCStatus: MPI IOCStatus
 * @IocLogInfo: MPI IocLogInfo.  Can be specअगरic or 0xFFFFFFFF क्रम wildcard
 *
 * Defines a MPI IOCStatus/IocLogInfo pair that should induce a DIAG_TRIGGER
 * driver event अगर observed.
 */
काष्ठा SL_WH_MPI_TRIGGER_T अणु
	uपूर्णांक16_t IOCStatus;
	uपूर्णांक16_t Reserved;
	uपूर्णांक32_t IocLogInfo;
पूर्ण;

/**
 * काष्ठा SL_WH_MPI_TRIGGERS_T -  Structure passed to/from sysfs containing a
 *    list of MPI IOCStatus/IocLogInfo pairs that should trigger a DIAG_SERVICE
 *    event when observed.
 * @ValidEntries: Number of _SL_WH_MPI_TRIGGER_T काष्ठाures contained in this
 *    काष्ठाure.
 * @MPITriggerEntry: List of MPI IOCStatus/IocLogInfo trigger elements.
 *
 * This binary काष्ठाure is transferred via sysfs to get/set MPI Error Triggers
 * in the Linux Driver.
 */
काष्ठा SL_WH_MPI_TRIGGERS_T अणु
	uपूर्णांक32_t ValidEntries;
	काष्ठा SL_WH_MPI_TRIGGER_T MPITriggerEntry[NUM_VALID_ENTRIES];
पूर्ण;

/**
 * काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T -  event data क्रम trigger
 * @trigger_type: trigger type (see MPT3SAS_TRIGGER_XXXX)
 * @u: trigger condition that caused trigger to be sent
 */
काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T अणु
	uपूर्णांक32_t trigger_type;
	जोड़ अणु
		काष्ठा SL_WH_MASTER_TRIGGER_T master;
		काष्ठा SL_WH_EVENT_TRIGGER_T event;
		काष्ठा SL_WH_SCSI_TRIGGER_T scsi;
		काष्ठा SL_WH_MPI_TRIGGER_T mpi;
	पूर्ण u;
पूर्ण;
#पूर्ण_अगर /* MPT3SAS_TRIGGER_DIAG_H_INCLUDED */
