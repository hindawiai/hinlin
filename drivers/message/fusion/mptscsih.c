<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptscsih.c
 *      For use with LSI PCI chip/adapter(s)
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
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kdev_t.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>	/* क्रम mdelay */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>	/* notअगरier code */
#समावेश <linux/workqueue.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_dbg.h>

#समावेश "mptbase.h"
#समावेश "mptscsih.h"
#समावेश "lsi/mpi_log_sas.h"

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#घोषणा my_NAME		"Fusion MPT SCSI Host driver"
#घोषणा my_VERSION	MPT_LINUX_VERSION_COMMON
#घोषणा MYNAM		"mptscsih"

MODULE_AUTHOR(MODULEAUTHOR);
MODULE_DESCRIPTION(my_NAME);
MODULE_LICENSE("GPL");
MODULE_VERSION(my_VERSION);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Other निजी/क्रमward protos...
 */
काष्ठा scsi_cmnd	*mptscsih_get_scsi_lookup(MPT_ADAPTER *ioc, पूर्णांक i);
अटल काष्ठा scsi_cmnd * mptscsih_अ_लोlear_scsi_lookup(MPT_ADAPTER *ioc, पूर्णांक i);
अटल व्योम	mptscsih_set_scsi_lookup(MPT_ADAPTER *ioc, पूर्णांक i, काष्ठा scsi_cmnd *scmd);
अटल पूर्णांक	SCPNT_TO_LOOKUP_IDX(MPT_ADAPTER *ioc, काष्ठा scsi_cmnd *scmd);
पूर्णांक		mptscsih_io_करोne(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *r);
अटल व्योम	mptscsih_report_queue_full(काष्ठा scsi_cmnd *sc, SCSIIOReply_t *pScsiReply, SCSIIORequest_t *pScsiReq);
पूर्णांक		mptscsih_taskmgmt_complete(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *r);

अटल पूर्णांक	mptscsih_AddSGE(MPT_ADAPTER *ioc, काष्ठा scsi_cmnd *SCpnt,
				 SCSIIORequest_t *pReq, पूर्णांक req_idx);
अटल व्योम	mptscsih_मुक्तChainBuffers(MPT_ADAPTER *ioc, पूर्णांक req_idx);
अटल व्योम	mptscsih_copy_sense_data(काष्ठा scsi_cmnd *sc, MPT_SCSI_HOST *hd, MPT_FRAME_HDR *mf, SCSIIOReply_t *pScsiReply);

पूर्णांक	mptscsih_IssueTaskMgmt(MPT_SCSI_HOST *hd, u8 type, u8 channel, u8 id,
		u64 lun, पूर्णांक ctx2पात, uदीर्घ समयout);

पूर्णांक		mptscsih_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक post_reset);
पूर्णांक		mptscsih_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply);

व्योम
mptscsih_taskmgmt_response_code(MPT_ADAPTER *ioc, u8 response_code);
अटल पूर्णांक	mptscsih_get_completion_code(MPT_ADAPTER *ioc,
		MPT_FRAME_HDR *req, MPT_FRAME_HDR *reply);
पूर्णांक		mptscsih_scandv_complete(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *r);
अटल पूर्णांक	mptscsih_करो_cmd(MPT_SCSI_HOST *hd, INTERNAL_CMD *iocmd);
अटल व्योम	mptscsih_synchronize_cache(MPT_SCSI_HOST *hd, VirtDevice *vdevice);

अटल पूर्णांक
mptscsih_taskmgmt_reply(MPT_ADAPTER *ioc, u8 type,
				SCSITaskMgmtReply_t *pScsiTmReply);
व्योम 		mptscsih_हटाओ(काष्ठा pci_dev *);
व्योम 		mptscsih_shutकरोwn(काष्ठा pci_dev *);
#अगर_घोषित CONFIG_PM
पूर्णांक 		mptscsih_suspend(काष्ठा pci_dev *pdev, pm_message_t state);
पूर्णांक 		mptscsih_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_getFreeChainBuffer - Function to get a मुक्त chain
 *	from the MPT_SCSI_HOST FreeChainQ.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@req_idx: Index of the SCSI IO request frame. (output)
 *
 *	वापस SUCCESS or FAILED
 */
अटल अंतरभूत पूर्णांक
mptscsih_getFreeChainBuffer(MPT_ADAPTER *ioc, पूर्णांक *retIndex)
अणु
	MPT_FRAME_HDR *chainBuf;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	पूर्णांक chain_idx;

	dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "getFreeChainBuffer called\n",
	    ioc->name));
	spin_lock_irqsave(&ioc->FreeQlock, flags);
	अगर (!list_empty(&ioc->FreeChainQ)) अणु
		पूर्णांक offset;

		chainBuf = list_entry(ioc->FreeChainQ.next, MPT_FRAME_HDR,
				u.frame.linkage.list);
		list_del(&chainBuf->u.frame.linkage.list);
		offset = (u8 *)chainBuf - (u8 *)ioc->ChainBuffer;
		chain_idx = offset / ioc->req_sz;
		rc = SUCCESS;
		dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "getFreeChainBuffer chainBuf=%p ChainBuffer=%p offset=%d chain_idx=%d\n",
		    ioc->name, chainBuf, ioc->ChainBuffer, offset, chain_idx));
	पूर्ण अन्यथा अणु
		rc = FAILED;
		chain_idx = MPT_HOST_NO_CHAIN;
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT "getFreeChainBuffer failed\n",
		    ioc->name));
	पूर्ण
	spin_unlock_irqrestore(&ioc->FreeQlock, flags);

	*retIndex = chain_idx;
	वापस rc;
पूर्ण /* mptscsih_getFreeChainBuffer() */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_AddSGE - Add a SGE (plus chain buffers) to the
 *	SCSIIORequest_t Message Frame.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@SCpnt: Poपूर्णांकer to scsi_cmnd काष्ठाure
 *	@pReq: Poपूर्णांकer to SCSIIORequest_t काष्ठाure
 *
 *	Returns ...
 */
अटल पूर्णांक
mptscsih_AddSGE(MPT_ADAPTER *ioc, काष्ठा scsi_cmnd *SCpnt,
		SCSIIORequest_t *pReq, पूर्णांक req_idx)
अणु
	अक्षर 	*psge;
	अक्षर	*chainSge;
	काष्ठा scatterlist *sg;
	पूर्णांक	 frm_sz;
	पूर्णांक	 sges_left, sg_करोne;
	पूर्णांक	 chain_idx = MPT_HOST_NO_CHAIN;
	पूर्णांक	 sgeOffset;
	पूर्णांक	 numSgeSlots, numSgeThisFrame;
	u32	 sgflags, sgdir, thisxfer = 0;
	पूर्णांक	 chain_dma_off = 0;
	पूर्णांक	 newIndex;
	पूर्णांक	 ii;
	dma_addr_t v2;
	u32	RequestNB;

	sgdir = le32_to_cpu(pReq->Control) & MPI_SCSIIO_CONTROL_DATAसूचीECTION_MASK;
	अगर (sgdir == MPI_SCSIIO_CONTROL_WRITE)  अणु
		sgdir = MPT_TRANSFER_HOST_TO_IOC;
	पूर्ण अन्यथा अणु
		sgdir = MPT_TRANSFER_IOC_TO_HOST;
	पूर्ण

	psge = (अक्षर *) &pReq->SGL;
	frm_sz = ioc->req_sz;

	/* Map the data portion, अगर any.
	 * sges_left  = 0 अगर no data transfer.
	 */
	sges_left = scsi_dma_map(SCpnt);
	अगर (sges_left < 0)
		वापस FAILED;

	/* Handle the SG हाल.
	 */
	sg = scsi_sglist(SCpnt);
	sg_करोne  = 0;
	sgeOffset = माप(SCSIIORequest_t) - माप(SGE_IO_UNION);
	chainSge = शून्य;

	/* Prior to entering this loop - the following must be set
	 * current MF:  sgeOffset (bytes)
	 *              chainSge (Null अगर original MF is not a chain buffer)
	 *              sg_करोne (num SGE करोne क्रम this MF)
	 */

nextSGEset:
	numSgeSlots = ((frm_sz - sgeOffset) / ioc->SGE_size);
	numSgeThisFrame = (sges_left < numSgeSlots) ? sges_left : numSgeSlots;

	sgflags = MPT_SGE_FLAGS_SIMPLE_ELEMENT | sgdir;

	/* Get first (num - 1) SG elements
	 * Skip any SG entries with a length of 0
	 * NOTE: at finish, sg and psge poपूर्णांकed to NEXT data/location positions
	 */
	क्रम (ii=0; ii < (numSgeThisFrame-1); ii++) अणु
		thisxfer = sg_dma_len(sg);
		अगर (thisxfer == 0) अणु
			/* Get next SG element from the OS */
			sg = sg_next(sg);
			sg_करोne++;
			जारी;
		पूर्ण

		v2 = sg_dma_address(sg);
		ioc->add_sge(psge, sgflags | thisxfer, v2);

		/* Get next SG element from the OS */
		sg = sg_next(sg);
		psge += ioc->SGE_size;
		sgeOffset += ioc->SGE_size;
		sg_करोne++;
	पूर्ण

	अगर (numSgeThisFrame == sges_left) अणु
		/* Add last element, end of buffer and end of list flags.
		 */
		sgflags |= MPT_SGE_FLAGS_LAST_ELEMENT |
				MPT_SGE_FLAGS_END_OF_BUFFER |
				MPT_SGE_FLAGS_END_OF_LIST;

		/* Add last SGE and set termination flags.
		 * Note: Last SGE may have a length of 0 - which should be ok.
		 */
		thisxfer = sg_dma_len(sg);

		v2 = sg_dma_address(sg);
		ioc->add_sge(psge, sgflags | thisxfer, v2);
		sgeOffset += ioc->SGE_size;
		sg_करोne++;

		अगर (chainSge) अणु
			/* The current buffer is a chain buffer,
			 * but there is not another one.
			 * Update the chain element
			 * Offset and Length fields.
			 */
			ioc->add_chain((अक्षर *)chainSge, 0, sgeOffset,
				ioc->ChainBufferDMA + chain_dma_off);
		पूर्ण अन्यथा अणु
			/* The current buffer is the original MF
			 * and there is no Chain buffer.
			 */
			pReq->ChainOffset = 0;
			RequestNB = (((sgeOffset - 1) >> ioc->NBShअगरtFactor)  + 1) & 0x03;
			dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "Single Buffer RequestNB=%x, sgeOffset=%d\n", ioc->name, RequestNB, sgeOffset));
			ioc->RequestNB[req_idx] = RequestNB;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* At least one chain buffer is needed.
		 * Complete the first MF
		 *  - last SGE element, set the LastElement bit
		 *  - set ChainOffset (words) क्रम orig MF
		 *             (OR finish previous MF chain buffer)
		 *  - update MFStructPtr ChainIndex
		 *  - Populate chain element
		 * Also
		 * Loop until करोne.
		 */

		dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "SG: Chain Required! sg done %d\n",
				ioc->name, sg_करोne));

		/* Set LAST_ELEMENT flag क्रम last non-chain element
		 * in the buffer. Since psge poपूर्णांकs at the NEXT
		 * SGE element, go back one SGE element, update the flags
		 * and reset the poपूर्णांकer. (Note: sgflags & thisxfer are alपढ़ोy
		 * set properly).
		 */
		अगर (sg_करोne) अणु
			u32 *pपंचांगp = (u32 *) (psge - ioc->SGE_size);
			sgflags = le32_to_cpu(*pपंचांगp);
			sgflags |= MPT_SGE_FLAGS_LAST_ELEMENT;
			*pपंचांगp = cpu_to_le32(sgflags);
		पूर्ण

		अगर (chainSge) अणु
			/* The current buffer is a chain buffer.
			 * chainSge poपूर्णांकs to the previous Chain Element.
			 * Update its chain element Offset and Length (must
			 * include chain element size) fields.
			 * Old chain element is now complete.
			 */
			u8 nextChain = (u8) (sgeOffset >> 2);
			sgeOffset += ioc->SGE_size;
			ioc->add_chain((अक्षर *)chainSge, nextChain, sgeOffset,
					 ioc->ChainBufferDMA + chain_dma_off);
		पूर्ण अन्यथा अणु
			/* The original MF buffer requires a chain buffer -
			 * set the offset.
			 * Last element in this MF is a chain element.
			 */
			pReq->ChainOffset = (u8) (sgeOffset >> 2);
			RequestNB = (((sgeOffset - 1) >> ioc->NBShअगरtFactor)  + 1) & 0x03;
			dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Chain Buffer Needed, RequestNB=%x sgeOffset=%d\n", ioc->name, RequestNB, sgeOffset));
			ioc->RequestNB[req_idx] = RequestNB;
		पूर्ण

		sges_left -= sg_करोne;


		/* NOTE: psge poपूर्णांकs to the beginning of the chain element
		 * in current buffer. Get a chain buffer.
		 */
		अगर ((mptscsih_getFreeChainBuffer(ioc, &newIndex)) == FAILED) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "getFreeChainBuffer FAILED SCSI cmd=%02x (%p)\n",
 			    ioc->name, pReq->CDB[0], SCpnt));
			वापस FAILED;
		पूर्ण

		/* Update the tracking arrays.
		 * If chainSge == शून्य, update ReqToChain, अन्यथा ChainToChain
		 */
		अगर (chainSge) अणु
			ioc->ChainToChain[chain_idx] = newIndex;
		पूर्ण अन्यथा अणु
			ioc->ReqToChain[req_idx] = newIndex;
		पूर्ण
		chain_idx = newIndex;
		chain_dma_off = ioc->req_sz * chain_idx;

		/* Populate the chainSGE क्रम the current buffer.
		 * - Set chain buffer poपूर्णांकer to psge and fill
		 *   out the Address and Flags fields.
		 */
		chainSge = (अक्षर *) psge;
		dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "  Current buff @ %p (index 0x%x)",
		    ioc->name, psge, req_idx));

		/* Start the SGE क्रम the next buffer
		 */
		psge = (अक्षर *) (ioc->ChainBuffer + chain_dma_off);
		sgeOffset = 0;
		sg_करोne = 0;

		dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "  Chain buff @ %p (index 0x%x)\n",
		    ioc->name, psge, chain_idx));

		/* Start the SGE क्रम the next buffer
		 */

		जाओ nextSGEset;
	पूर्ण

	वापस SUCCESS;
पूर्ण /* mptscsih_AddSGE() */

अटल व्योम
mptscsih_issue_sep_command(MPT_ADAPTER *ioc, VirtTarget *vtarget,
    U32 SlotStatus)
अणु
	MPT_FRAME_HDR *mf;
	SEPRequest_t 	 *SEPMsg;

	अगर (ioc->bus_type != SAS)
		वापस;

	/* Not supported क्रम hidden raid components
	 */
	अगर (vtarget->tflags & MPT_TARGET_FLAGS_RAID_COMPONENT)
		वापस;

	अगर ((mf = mpt_get_msg_frame(ioc->InternalCtx, ioc)) == शून्य) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT "%s: no msg frames!!\n",
		    ioc->name,__func__));
		वापस;
	पूर्ण

	SEPMsg = (SEPRequest_t *)mf;
	SEPMsg->Function = MPI_FUNCTION_SCSI_ENCLOSURE_PROCESSOR;
	SEPMsg->Bus = vtarget->channel;
	SEPMsg->TargetID = vtarget->id;
	SEPMsg->Action = MPI_SEP_REQ_ACTION_WRITE_STATUS;
	SEPMsg->SlotStatus = SlotStatus;
	devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Sending SEP cmd=%x channel=%d id=%d\n",
	    ioc->name, SlotStatus, SEPMsg->Bus, SEPMsg->TargetID));
	mpt_put_msg_frame(ioc->DoneCtx, ioc, mf);
पूर्ण

#अगर_घोषित CONFIG_FUSION_LOGGING
/**
 *	mptscsih_info_scsiio - debug prपूर्णांक info on reply frame
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@sc: original scsi cmnd poपूर्णांकer
 *	@pScsiReply: Poपूर्णांकer to MPT reply frame
 *
 *	MPT_DEBUG_REPLY needs to be enabled to obtain this info
 *
 *	Refer to lsi/mpi.h.
 **/
अटल व्योम
mptscsih_info_scsiio(MPT_ADAPTER *ioc, काष्ठा scsi_cmnd *sc, SCSIIOReply_t * pScsiReply)
अणु
	अक्षर	*desc = शून्य;
	अक्षर	*desc1 = शून्य;
	u16	ioc_status;
	u8	skey, asc, ascq;

	ioc_status = le16_to_cpu(pScsiReply->IOCStatus) & MPI_IOCSTATUS_MASK;

	चयन (ioc_status) अणु

	हाल MPI_IOCSTATUS_SUCCESS:
		desc = "success";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_INVALID_BUS:
		desc = "invalid bus";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_INVALID_TARGETID:
		desc = "invalid target_id";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE:
		desc = "device not there";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_DATA_OVERRUN:
		desc = "data overrun";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_DATA_UNDERRUN:
		desc = "data underrun";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_IO_DATA_ERROR:
		desc = "I/O data error";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR:
		desc = "protocol error";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_TASK_TERMINATED:
		desc = "task terminated";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH:
		desc = "residual mismatch";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_TASK_MGMT_FAILED:
		desc = "task management failed";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_IOC_TERMINATED:
		desc = "IOC terminated";
		अवरोध;
	हाल MPI_IOCSTATUS_SCSI_EXT_TERMINATED:
		desc = "ext terminated";
		अवरोध;
	शेष:
		desc = "";
		अवरोध;
	पूर्ण

	चयन (pScsiReply->SCSIStatus)
	अणु

	हाल MPI_SCSI_STATUS_SUCCESS:
		desc1 = "success";
		अवरोध;
	हाल MPI_SCSI_STATUS_CHECK_CONDITION:
		desc1 = "check condition";
		अवरोध;
	हाल MPI_SCSI_STATUS_CONDITION_MET:
		desc1 = "condition met";
		अवरोध;
	हाल MPI_SCSI_STATUS_BUSY:
		desc1 = "busy";
		अवरोध;
	हाल MPI_SCSI_STATUS_INTERMEDIATE:
		desc1 = "intermediate";
		अवरोध;
	हाल MPI_SCSI_STATUS_INTERMEDIATE_CONDMET:
		desc1 = "intermediate condmet";
		अवरोध;
	हाल MPI_SCSI_STATUS_RESERVATION_CONFLICT:
		desc1 = "reservation conflict";
		अवरोध;
	हाल MPI_SCSI_STATUS_COMMAND_TERMINATED:
		desc1 = "command terminated";
		अवरोध;
	हाल MPI_SCSI_STATUS_TASK_SET_FULL:
		desc1 = "task set full";
		अवरोध;
	हाल MPI_SCSI_STATUS_ACA_ACTIVE:
		desc1 = "aca active";
		अवरोध;
	हाल MPI_SCSI_STATUS_FCPEXT_DEVICE_LOGGED_OUT:
		desc1 = "fcpext device logged out";
		अवरोध;
	हाल MPI_SCSI_STATUS_FCPEXT_NO_LINK:
		desc1 = "fcpext no link";
		अवरोध;
	हाल MPI_SCSI_STATUS_FCPEXT_UNASSIGNED:
		desc1 = "fcpext unassigned";
		अवरोध;
	शेष:
		desc1 = "";
		अवरोध;
	पूर्ण

	scsi_prपूर्णांक_command(sc);
	prपूर्णांकk(MYIOC_s_DEBUG_FMT "\tfw_channel = %d, fw_id = %d, lun = %llu\n",
	    ioc->name, pScsiReply->Bus, pScsiReply->TargetID, sc->device->lun);
	prपूर्णांकk(MYIOC_s_DEBUG_FMT "\trequest_len = %d, underflow = %d, "
	    "resid = %d\n", ioc->name, scsi_bufflen(sc), sc->underflow,
	    scsi_get_resid(sc));
	prपूर्णांकk(MYIOC_s_DEBUG_FMT "\ttag = %d, transfer_count = %d, "
	    "sc->result = %08X\n", ioc->name, le16_to_cpu(pScsiReply->TaskTag),
	    le32_to_cpu(pScsiReply->TransferCount), sc->result);

	prपूर्णांकk(MYIOC_s_DEBUG_FMT "\tiocstatus = %s (0x%04x), "
	    "scsi_status = %s (0x%02x), scsi_state = (0x%02x)\n",
	    ioc->name, desc, ioc_status, desc1, pScsiReply->SCSIStatus,
	    pScsiReply->SCSIState);

	अगर (pScsiReply->SCSIState & MPI_SCSI_STATE_AUTOSENSE_VALID) अणु
		skey = sc->sense_buffer[2] & 0x0F;
		asc = sc->sense_buffer[12];
		ascq = sc->sense_buffer[13];

		prपूर्णांकk(MYIOC_s_DEBUG_FMT "\t[sense_key,asc,ascq]: "
		    "[0x%02x,0x%02x,0x%02x]\n", ioc->name, skey, asc, ascq);
	पूर्ण

	/*
	 *  Look क्रम + dump FCP ResponseInfo[]!
	 */
	अगर (pScsiReply->SCSIState & MPI_SCSI_STATE_RESPONSE_INFO_VALID &&
	    pScsiReply->ResponseInfo)
		prपूर्णांकk(MYIOC_s_DEBUG_FMT "response_info = %08xh\n",
		    ioc->name, le32_to_cpu(pScsiReply->ResponseInfo));
पूर्ण
#पूर्ण_अगर

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_io_करोne - Main SCSI IO callback routine रेजिस्टरed to
 *	Fusion MPT (base) driver
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@mf: Poपूर्णांकer to original MPT request frame
 *	@r: Poपूर्णांकer to MPT reply frame (शून्य अगर TurboReply)
 *
 *	This routine is called from mpt.c::mpt_पूर्णांकerrupt() at the completion
 *	of any SCSI IO request.
 *	This routine is रेजिस्टरed with the Fusion MPT (base) driver at driver
 *	load/init समय via the mpt_रेजिस्टर() API call.
 *
 *	Returns 1 indicating alloc'd request frame ptr should be मुक्तd.
 */
पूर्णांक
mptscsih_io_करोne(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *mr)
अणु
	काष्ठा scsi_cmnd	*sc;
	MPT_SCSI_HOST	*hd;
	SCSIIORequest_t	*pScsiReq;
	SCSIIOReply_t	*pScsiReply;
	u16		 req_idx, req_idx_MR;
	VirtDevice	 *vdevice;
	VirtTarget	 *vtarget;

	hd = shost_priv(ioc->sh);
	req_idx = le16_to_cpu(mf->u.frame.hwhdr.msgctxu.fld.req_idx);
	req_idx_MR = (mr != शून्य) ?
	    le16_to_cpu(mr->u.frame.hwhdr.msgctxu.fld.req_idx) : req_idx;

	/* Special हाल, where alपढ़ोy मुक्तd message frame is received from
	 * Firmware. It happens with Resetting IOC.
	 * Return immediately. Do not care
	 */
	अगर ((req_idx != req_idx_MR) ||
	    (le32_to_cpu(mf->u.frame.linkage.arg1) == 0xdeadbeaf))
		वापस 0;

	sc = mptscsih_अ_लोlear_scsi_lookup(ioc, req_idx);
	अगर (sc == शून्य) अणु
		MPIHeader_t *hdr = (MPIHeader_t *)mf;

		/* Remark: ग_लिखोSDP1 will use the ScsiDoneCtx
		 * If a SCSI I/O cmd, device disabled by OS and
		 * completion करोne. Cannot touch sc काष्ठा. Just मुक्त mem.
		 */
		अगर (hdr->Function == MPI_FUNCTION_SCSI_IO_REQUEST)
			prपूर्णांकk(MYIOC_s_ERR_FMT "NULL ScsiCmd ptr!\n",
			ioc->name);

		mptscsih_मुक्तChainBuffers(ioc, req_idx);
		वापस 1;
	पूर्ण

	अगर ((अचिन्हित अक्षर *)mf != sc->host_scribble) अणु
		mptscsih_मुक्तChainBuffers(ioc, req_idx);
		वापस 1;
	पूर्ण

	अगर (ioc->bus_type == SAS) अणु
		VirtDevice *vdevice = sc->device->hostdata;

		अगर (!vdevice || !vdevice->vtarget ||
		    vdevice->vtarget->deleted) अणु
			sc->result = DID_NO_CONNECT << 16;
			जाओ out;
		पूर्ण
	पूर्ण

	sc->host_scribble = शून्य;
	sc->result = DID_OK << 16;		/* Set शेष reply as OK */
	pScsiReq = (SCSIIORequest_t *) mf;
	pScsiReply = (SCSIIOReply_t *) mr;

	अगर((ioc->facts.MsgVersion >= MPI_VERSION_01_05) && pScsiReply)अणु
		dmfprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"ScsiDone (mf=%p,mr=%p,sc=%p,idx=%d,task-tag=%d)\n",
			ioc->name, mf, mr, sc, req_idx, pScsiReply->TaskTag));
	पूर्णअन्यथाअणु
		dmfprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"ScsiDone (mf=%p,mr=%p,sc=%p,idx=%d)\n",
			ioc->name, mf, mr, sc, req_idx));
	पूर्ण

	अगर (pScsiReply == शून्य) अणु
		/* special context reply handling */
		;
	पूर्ण अन्यथा अणु
		u32	 xfer_cnt;
		u16	 status;
		u8	 scsi_state, scsi_status;
		u32	 log_info;

		status = le16_to_cpu(pScsiReply->IOCStatus) & MPI_IOCSTATUS_MASK;

		scsi_state = pScsiReply->SCSIState;
		scsi_status = pScsiReply->SCSIStatus;
		xfer_cnt = le32_to_cpu(pScsiReply->TransferCount);
		scsi_set_resid(sc, scsi_bufflen(sc) - xfer_cnt);
		log_info = le32_to_cpu(pScsiReply->IOCLogInfo);

		/*
		 *  अगर we get a data underrun indication, yet no data was
		 *  transferred and the SCSI status indicates that the
		 *  command was never started, change the data underrun
		 *  to success
		 */
		अगर (status == MPI_IOCSTATUS_SCSI_DATA_UNDERRUN && xfer_cnt == 0 &&
		    (scsi_status == MPI_SCSI_STATUS_BUSY ||
		     scsi_status == MPI_SCSI_STATUS_RESERVATION_CONFLICT ||
		     scsi_status == MPI_SCSI_STATUS_TASK_SET_FULL)) अणु
			status = MPI_IOCSTATUS_SUCCESS;
		पूर्ण

		अगर (scsi_state & MPI_SCSI_STATE_AUTOSENSE_VALID)
			mptscsih_copy_sense_data(sc, hd, mf, pScsiReply);

		/*
		 *  Look क्रम + dump FCP ResponseInfo[]!
		 */
		अगर (scsi_state & MPI_SCSI_STATE_RESPONSE_INFO_VALID &&
		    pScsiReply->ResponseInfo) अणु
			prपूर्णांकk(MYIOC_s_NOTE_FMT "[%d:%d:%d:%llu] "
			"FCP_ResponseInfo=%08xh\n", ioc->name,
			sc->device->host->host_no, sc->device->channel,
			sc->device->id, sc->device->lun,
			le32_to_cpu(pScsiReply->ResponseInfo));
		पूर्ण

		चयन(status) अणु
		हाल MPI_IOCSTATUS_BUSY:			/* 0x0002 */
		हाल MPI_IOCSTATUS_INSUFFICIENT_RESOURCES:	/* 0x0006 */
			/* CHECKME!
			 * Maybe: DRIVER_BUSY | SUGGEST_RETRY | DID_SOFT_ERROR (retry)
			 * But not: DID_BUS_BUSY lest one risk
			 * समाप्तing पूर्णांकerrupt handler:-(
			 */
			sc->result = SAM_STAT_BUSY;
			अवरोध;

		हाल MPI_IOCSTATUS_SCSI_INVALID_BUS:		/* 0x0041 */
		हाल MPI_IOCSTATUS_SCSI_INVALID_TARGETID:	/* 0x0042 */
			sc->result = DID_BAD_TARGET << 16;
			अवरोध;

		हाल MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE:	/* 0x0043 */
			/* Spoof to SCSI Selection Timeout! */
			अगर (ioc->bus_type != FC)
				sc->result = DID_NO_CONNECT << 16;
			/* अन्यथा fibre, just stall until rescan event */
			अन्यथा
				sc->result = DID_REQUEUE << 16;

			अगर (hd->sel_समयout[pScsiReq->TargetID] < 0xFFFF)
				hd->sel_समयout[pScsiReq->TargetID]++;

			vdevice = sc->device->hostdata;
			अगर (!vdevice)
				अवरोध;
			vtarget = vdevice->vtarget;
			अगर (vtarget->tflags & MPT_TARGET_FLAGS_LED_ON) अणु
				mptscsih_issue_sep_command(ioc, vtarget,
				    MPI_SEP_REQ_SLOTSTATUS_UNCONFIGURED);
				vtarget->tflags &= ~MPT_TARGET_FLAGS_LED_ON;
			पूर्ण
			अवरोध;

		हाल MPI_IOCSTATUS_SCSI_IOC_TERMINATED:		/* 0x004B */
			अगर ( ioc->bus_type == SAS ) अणु
				u16 ioc_status =
				    le16_to_cpu(pScsiReply->IOCStatus);
				अगर ((ioc_status &
					MPI_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE)
					&&
					((log_info & SAS_LOGINFO_MASK) ==
					SAS_LOGINFO_NEXUS_LOSS)) अणु
						VirtDevice *vdevice =
						sc->device->hostdata;

					    /* flag the device as being in
					     * device removal delay so we can
					     * notअगरy the midlayer to hold off
					     * on समयout eh */
						अगर (vdevice && vdevice->
							vtarget &&
							vdevice->vtarget->
							raidVolume)
							prपूर्णांकk(KERN_INFO
							"Skipping Raid Volume"
							"for inDMD\n");
						अन्यथा अगर (vdevice &&
							vdevice->vtarget)
							vdevice->vtarget->
								inDMD = 1;

					    sc->result =
						    (DID_TRANSPORT_DISRUPTED
						    << 16);
					    अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (ioc->bus_type == FC) अणु
				/*
				 * The FC IOC may समाप्त a request क्रम variety of
				 * reasons, some of which may be recovered by a
				 * retry, some which are unlikely to be
				 * recovered. Return DID_ERROR instead of
				 * DID_RESET to permit retry of the command,
				 * just not an infinite number of them
				 */
				sc->result = DID_ERROR << 16;
				अवरोध;
			पूर्ण

			/*
			 * Allow non-SAS & non-NEXUS_LOSS to drop पूर्णांकo below code
			 */
			fallthrough;

		हाल MPI_IOCSTATUS_SCSI_TASK_TERMINATED:	/* 0x0048 */
			/* Linux handles an unsolicited DID_RESET better
			 * than an unsolicited DID_ABORT.
			 */
			sc->result = DID_RESET << 16;
			अवरोध;

		हाल MPI_IOCSTATUS_SCSI_EXT_TERMINATED:		/* 0x004C */
			अगर (ioc->bus_type == FC)
				sc->result = DID_ERROR << 16;
			अन्यथा
				sc->result = DID_RESET << 16;
			अवरोध;

		हाल MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH:	/* 0x0049 */
			scsi_set_resid(sc, scsi_bufflen(sc) - xfer_cnt);
			अगर((xfer_cnt==0)||(sc->underflow > xfer_cnt))
				sc->result=DID_SOFT_ERROR << 16;
			अन्यथा /* Sufficient data transfer occurred */
				sc->result = (DID_OK << 16) | scsi_status;
			dreplyprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "RESIDUAL_MISMATCH: result=%x on channel=%d id=%d\n",
			    ioc->name, sc->result, sc->device->channel, sc->device->id));
			अवरोध;

		हाल MPI_IOCSTATUS_SCSI_DATA_UNDERRUN:		/* 0x0045 */
			/*
			 *  Do upfront check क्रम valid SenseData and give it
			 *  precedence!
			 */
			sc->result = (DID_OK << 16) | scsi_status;
			अगर (!(scsi_state & MPI_SCSI_STATE_AUTOSENSE_VALID)) अणु

				/*
				 * For an Errata on LSI53C1030
				 * When the length of request data
				 * and transfer data are dअगरferent
				 * with result of command (READ or VERIFY),
				 * DID_SOFT_ERROR is set.
				 */
				अगर (ioc->bus_type == SPI) अणु
					अगर ((pScsiReq->CDB[0] == READ_6  && ((pScsiReq->CDB[1] & 0x02) == 0)) ||
					    pScsiReq->CDB[0] == READ_10 ||
					    pScsiReq->CDB[0] == READ_12 ||
						(pScsiReq->CDB[0] == READ_16 &&
						((pScsiReq->CDB[1] & 0x02) == 0)) ||
					    pScsiReq->CDB[0] == VERIFY  ||
					    pScsiReq->CDB[0] == VERIFY_16) अणु
						अगर (scsi_bufflen(sc) !=
							xfer_cnt) अणु
							sc->result =
							DID_SOFT_ERROR << 16;
						    prपूर्णांकk(KERN_WARNING "Errata"
						    "on LSI53C1030 occurred."
						    "sc->req_bufflen=0x%02x,"
						    "xfer_cnt=0x%02x\n",
						    scsi_bufflen(sc),
						    xfer_cnt);
						पूर्ण
					पूर्ण
				पूर्ण

				अगर (xfer_cnt < sc->underflow) अणु
					अगर (scsi_status == SAM_STAT_BUSY)
						sc->result = SAM_STAT_BUSY;
					अन्यथा
						sc->result = DID_SOFT_ERROR << 16;
				पूर्ण
				अगर (scsi_state & (MPI_SCSI_STATE_AUTOSENSE_FAILED | MPI_SCSI_STATE_NO_SCSI_STATUS)) अणु
					/* What to करो?
				 	*/
					sc->result = DID_SOFT_ERROR << 16;
				पूर्ण
				अन्यथा अगर (scsi_state & MPI_SCSI_STATE_TERMINATED) अणु
					/*  Not real sure here either...  */
					sc->result = DID_RESET << 16;
				पूर्ण
			पूर्ण


			dreplyprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "  sc->underflow={report ERR if < %02xh bytes xfer'd}\n",
			    ioc->name, sc->underflow));
			dreplyprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "  ActBytesXferd=%02xh\n", ioc->name, xfer_cnt));

			/* Report Queue Full
			 */
			अगर (scsi_status == MPI_SCSI_STATUS_TASK_SET_FULL)
				mptscsih_report_queue_full(sc, pScsiReply, pScsiReq);

			अवरोध;

		हाल MPI_IOCSTATUS_SCSI_DATA_OVERRUN:		/* 0x0044 */
			scsi_set_resid(sc, 0);
			fallthrough;
		हाल MPI_IOCSTATUS_SCSI_RECOVERED_ERROR:	/* 0x0040 */
		हाल MPI_IOCSTATUS_SUCCESS:			/* 0x0000 */
			sc->result = (DID_OK << 16) | scsi_status;
			अगर (scsi_state == 0) अणु
				;
			पूर्ण अन्यथा अगर (scsi_state &
			    MPI_SCSI_STATE_AUTOSENSE_VALID) अणु

				/*
				 * For potential trouble on LSI53C1030.
				 * (date:2007.xx.)
				 * It is checked whether the length of
				 * request data is equal to
				 * the length of transfer and residual.
				 * MEDIUM_ERROR is set by incorrect data.
				 */
				अगर ((ioc->bus_type == SPI) &&
					(sc->sense_buffer[2] & 0x20)) अणु
					u32	 dअगरftransfer;
					dअगरftransfer =
					sc->sense_buffer[3] << 24 |
					sc->sense_buffer[4] << 16 |
					sc->sense_buffer[5] << 8 |
					sc->sense_buffer[6];
					अगर (((sc->sense_buffer[3] & 0x80) ==
						0x80) && (scsi_bufflen(sc)
						!= xfer_cnt)) अणु
						sc->sense_buffer[2] =
						    MEDIUM_ERROR;
						sc->sense_buffer[12] = 0xff;
						sc->sense_buffer[13] = 0xff;
						prपूर्णांकk(KERN_WARNING"Errata"
						"on LSI53C1030 occurred."
						"sc->req_bufflen=0x%02x,"
						"xfer_cnt=0x%02x\n" ,
						scsi_bufflen(sc),
						xfer_cnt);
					पूर्ण
					अगर (((sc->sense_buffer[3] & 0x80)
						!= 0x80) &&
						(scsi_bufflen(sc) !=
						xfer_cnt + dअगरftransfer)) अणु
						sc->sense_buffer[2] =
							MEDIUM_ERROR;
						sc->sense_buffer[12] = 0xff;
						sc->sense_buffer[13] = 0xff;
						prपूर्णांकk(KERN_WARNING
						"Errata on LSI53C1030 occurred"
						"sc->req_bufflen=0x%02x,"
						" xfer_cnt=0x%02x,"
						"difftransfer=0x%02x\n",
						scsi_bufflen(sc),
						xfer_cnt,
						dअगरftransfer);
					पूर्ण
				पूर्ण

				/*
				 * If running against circa 200003dd 909 MPT f/w,
				 * may get this (AUTOSENSE_VALID) क्रम actual TASK_SET_FULL
				 * (QUEUE_FULL) वापसed from device! --> get 0x0000?128
				 * and with SenseBytes set to 0.
				 */
				अगर (pScsiReply->SCSIStatus == MPI_SCSI_STATUS_TASK_SET_FULL)
					mptscsih_report_queue_full(sc, pScsiReply, pScsiReq);

			पूर्ण
			अन्यथा अगर (scsi_state &
			         (MPI_SCSI_STATE_AUTOSENSE_FAILED | MPI_SCSI_STATE_NO_SCSI_STATUS)
			   ) अणु
				/*
				 * What to करो?
				 */
				sc->result = DID_SOFT_ERROR << 16;
			पूर्ण
			अन्यथा अगर (scsi_state & MPI_SCSI_STATE_TERMINATED) अणु
				/*  Not real sure here either...  */
				sc->result = DID_RESET << 16;
			पूर्ण
			अन्यथा अगर (scsi_state & MPI_SCSI_STATE_QUEUE_TAG_REJECTED) अणु
				/* Device Inq. data indicates that it supports
				 * QTags, but rejects QTag messages.
				 * This command completed OK.
				 *
				 * Not real sure here either so करो nothing...  */
			पूर्ण

			अगर (sc->result == MPI_SCSI_STATUS_TASK_SET_FULL)
				mptscsih_report_queue_full(sc, pScsiReply, pScsiReq);

			/* Add handling of:
			 * Reservation Conflict, Busy,
			 * Command Terminated, CHECK
			 */
			अवरोध;

		हाल MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR:		/* 0x0047 */
			sc->result = DID_SOFT_ERROR << 16;
			अवरोध;

		हाल MPI_IOCSTATUS_INVALID_FUNCTION:		/* 0x0001 */
		हाल MPI_IOCSTATUS_INVALID_SGL:			/* 0x0003 */
		हाल MPI_IOCSTATUS_INTERNAL_ERROR:		/* 0x0004 */
		हाल MPI_IOCSTATUS_RESERVED:			/* 0x0005 */
		हाल MPI_IOCSTATUS_INVALID_FIELD:		/* 0x0007 */
		हाल MPI_IOCSTATUS_INVALID_STATE:		/* 0x0008 */
		हाल MPI_IOCSTATUS_SCSI_IO_DATA_ERROR:		/* 0x0046 */
		हाल MPI_IOCSTATUS_SCSI_TASK_MGMT_FAILED:	/* 0x004A */
		शेष:
			/*
			 * What to करो?
			 */
			sc->result = DID_SOFT_ERROR << 16;
			अवरोध;

		पूर्ण	/* चयन(status) */

#अगर_घोषित CONFIG_FUSION_LOGGING
		अगर (sc->result && (ioc->debug_level & MPT_DEBUG_REPLY))
			mptscsih_info_scsiio(ioc, sc, pScsiReply);
#पूर्ण_अगर

	पूर्ण /* end of address reply हाल */
out:
	/* Unmap the DMA buffers, अगर any. */
	scsi_dma_unmap(sc);

	sc->scsi_करोne(sc);		/* Issue the command callback */

	/* Free Chain buffers */
	mptscsih_मुक्तChainBuffers(ioc, req_idx);
	वापस 1;
पूर्ण

/*
 *	mptscsih_flush_running_cmds - For each command found, search
 *		Scsi_Host instance taskQ and reply to OS.
 *		Called only अगर recovering from a FW reload.
 *	@hd: Poपूर्णांकer to a SCSI HOST काष्ठाure
 *
 *	Returns: None.
 *
 *	Must be called जबतक new I/Os are being queued.
 */
व्योम
mptscsih_flush_running_cmds(MPT_SCSI_HOST *hd)
अणु
	MPT_ADAPTER *ioc = hd->ioc;
	काष्ठा scsi_cmnd *sc;
	SCSIIORequest_t	*mf = शून्य;
	पूर्णांक		 ii;
	पूर्णांक		 channel, id;

	क्रम (ii= 0; ii < ioc->req_depth; ii++) अणु
		sc = mptscsih_अ_लोlear_scsi_lookup(ioc, ii);
		अगर (!sc)
			जारी;
		mf = (SCSIIORequest_t *)MPT_INDEX_2_MFPTR(ioc, ii);
		अगर (!mf)
			जारी;
		channel = mf->Bus;
		id = mf->TargetID;
		mptscsih_मुक्तChainBuffers(ioc, ii);
		mpt_मुक्त_msg_frame(ioc, (MPT_FRAME_HDR *)mf);
		अगर ((अचिन्हित अक्षर *)mf != sc->host_scribble)
			जारी;
		scsi_dma_unmap(sc);
		sc->result = DID_RESET << 16;
		sc->host_scribble = शून्य;
		dपंचांगprपूर्णांकk(ioc, sdev_prपूर्णांकk(KERN_INFO, sc->device, MYIOC_s_FMT
		    "completing cmds: fw_channel %d, fw_id %d, sc=%p, mf = %p, "
		    "idx=%x\n", ioc->name, channel, id, sc, mf, ii));
		sc->scsi_करोne(sc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mptscsih_flush_running_cmds);

/*
 *	mptscsih_search_running_cmds - Delete any commands associated
 *		with the specअगरied target and lun. Function called only
 *		when a lun is disable by mid-layer.
 *		Do NOT access the referenced scsi_cmnd काष्ठाure or
 *		members. Will cause either a paging or शून्य ptr error.
 *		(BUT, BUT, BUT, the code करोes reference it! - mdr)
 *      @hd: Poपूर्णांकer to a SCSI HOST काष्ठाure
 *	@vdevice: per device निजी data
 *
 *	Returns: None.
 *
 *	Called from slave_destroy.
 */
अटल व्योम
mptscsih_search_running_cmds(MPT_SCSI_HOST *hd, VirtDevice *vdevice)
अणु
	SCSIIORequest_t	*mf = शून्य;
	पूर्णांक		 ii;
	काष्ठा scsi_cmnd *sc;
	काष्ठा scsi_lun  lun;
	MPT_ADAPTER *ioc = hd->ioc;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	क्रम (ii = 0; ii < ioc->req_depth; ii++) अणु
		अगर ((sc = ioc->ScsiLookup[ii]) != शून्य) अणु

			mf = (SCSIIORequest_t *)MPT_INDEX_2_MFPTR(ioc, ii);
			अगर (mf == शून्य)
				जारी;
			/* If the device is a hidden raid component, then its
			 * expected that the mf->function will be RAID_SCSI_IO
			 */
			अगर (vdevice->vtarget->tflags &
			    MPT_TARGET_FLAGS_RAID_COMPONENT && mf->Function !=
			    MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH)
				जारी;

			पूर्णांक_to_scsilun(vdevice->lun, &lun);
			अगर ((mf->Bus != vdevice->vtarget->channel) ||
			    (mf->TargetID != vdevice->vtarget->id) ||
			    स_भेद(lun.scsi_lun, mf->LUN, 8))
				जारी;

			अगर ((अचिन्हित अक्षर *)mf != sc->host_scribble)
				जारी;
			ioc->ScsiLookup[ii] = शून्य;
			spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
			mptscsih_मुक्तChainBuffers(ioc, ii);
			mpt_मुक्त_msg_frame(ioc, (MPT_FRAME_HDR *)mf);
			scsi_dma_unmap(sc);
			sc->host_scribble = शून्य;
			sc->result = DID_NO_CONNECT << 16;
			dपंचांगprपूर्णांकk(ioc, sdev_prपूर्णांकk(KERN_INFO, sc->device,
			   MYIOC_s_FMT "completing cmds: fw_channel %d, "
			   "fw_id %d, sc=%p, mf = %p, idx=%x\n", ioc->name,
			   vdevice->vtarget->channel, vdevice->vtarget->id,
			   sc, mf, ii));
			sc->scsi_करोne(sc);
			spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
	वापस;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_report_queue_full - Report QUEUE_FULL status वापसed
 *	from a SCSI target device.
 *	@sc: Poपूर्णांकer to scsi_cmnd काष्ठाure
 *	@pScsiReply: Poपूर्णांकer to SCSIIOReply_t
 *	@pScsiReq: Poपूर्णांकer to original SCSI request
 *
 *	This routine periodically reports QUEUE_FULL status वापसed from a
 *	SCSI target device.  It reports this to the console via kernel
 *	prपूर्णांकk() API call, not more than once every 10 seconds.
 */
अटल व्योम
mptscsih_report_queue_full(काष्ठा scsi_cmnd *sc, SCSIIOReply_t *pScsiReply, SCSIIORequest_t *pScsiReq)
अणु
	दीर्घ समय = jअगरfies;
	MPT_SCSI_HOST		*hd;
	MPT_ADAPTER	*ioc;

	अगर (sc->device == शून्य)
		वापस;
	अगर (sc->device->host == शून्य)
		वापस;
	अगर ((hd = shost_priv(sc->device->host)) == शून्य)
		वापस;
	ioc = hd->ioc;
	अगर (समय - hd->last_queue_full > 10 * HZ) अणु
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT "Device (%d:%d:%llu) reported QUEUE_FULL!\n",
				ioc->name, 0, sc->device->id, sc->device->lun));
		hd->last_queue_full = समय;
	पूर्ण
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_हटाओ - Removed scsi devices
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 *
 *
 */
व्योम
mptscsih_हटाओ(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER 		*ioc = pci_get_drvdata(pdev);
	काष्ठा Scsi_Host 	*host = ioc->sh;
	MPT_SCSI_HOST		*hd;
	पूर्णांक sz1;

	अगर (host == शून्य)
		hd = शून्य;
	अन्यथा
		hd = shost_priv(host);

	mptscsih_shutकरोwn(pdev);

	sz1=0;

	अगर (ioc->ScsiLookup != शून्य) अणु
		sz1 = ioc->req_depth * माप(व्योम *);
		kमुक्त(ioc->ScsiLookup);
		ioc->ScsiLookup = शून्य;
	पूर्ण

	dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Free'd ScsiLookup (%d) memory\n",
	    ioc->name, sz1));

	अगर (hd)
		kमुक्त(hd->info_kbuf);

	/* शून्य the Scsi_Host poपूर्णांकer
	 */
	ioc->sh = शून्य;

	अगर (host)
		scsi_host_put(host);
	mpt_detach(pdev);

पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_shutकरोwn - reboot notअगरier
 *
 */
व्योम
mptscsih_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
पूर्ण

#अगर_घोषित CONFIG_PM
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_suspend - Fusion MPT scsi driver suspend routine.
 *
 *
 */
पूर्णांक
mptscsih_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	MPT_ADAPTER 		*ioc = pci_get_drvdata(pdev);

	scsi_block_requests(ioc->sh);
	flush_scheduled_work();
	mptscsih_shutकरोwn(pdev);
	वापस mpt_suspend(pdev,state);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_resume - Fusion MPT scsi driver resume routine.
 *
 *
 */
पूर्णांक
mptscsih_resume(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER 		*ioc = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = mpt_resume(pdev);
	scsi_unblock_requests(ioc->sh);
	वापस rc;
पूर्ण

#पूर्ण_अगर

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_info - Return inक्रमmation about MPT adapter
 *	@SChost: Poपूर्णांकer to Scsi_Host काष्ठाure
 *
 *	(linux scsi_host_ढाँचा.info routine)
 *
 *	Returns poपूर्णांकer to buffer where inक्रमmation was written.
 */
स्थिर अक्षर *
mptscsih_info(काष्ठा Scsi_Host *SChost)
अणु
	MPT_SCSI_HOST *h;
	पूर्णांक size = 0;

	h = shost_priv(SChost);

	अगर (h->info_kbuf == शून्य)
		अगर ((h->info_kbuf = kदो_स्मृति(0x1000 /* 4Kb */, GFP_KERNEL)) == शून्य)
			वापस h->info_kbuf;
	h->info_kbuf[0] = '\0';

	mpt_prपूर्णांक_ioc_summary(h->ioc, h->info_kbuf, &size, 0, 0);
	h->info_kbuf[size-1] = '\0';

	वापस h->info_kbuf;
पूर्ण

पूर्णांक mptscsih_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER	*ioc = hd->ioc;

	seq_म_लिखो(m, "%s: %s, ", ioc->name, ioc->prod_name);
	seq_म_लिखो(m, "%s%08xh, ", MPT_FW_REV_MAGIC_ID_STRING, ioc->facts.FWVersion.Word);
	seq_म_लिखो(m, "Ports=%d, ", ioc->facts.NumberOfPorts);
	seq_म_लिखो(m, "MaxQ=%d\n", ioc->req_depth);

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#घोषणा ADD_INDEX_LOG(req_ent)	करो अणु पूर्ण जबतक(0)

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_qcmd - Primary Fusion MPT SCSI initiator IO start routine.
 *	@SCpnt: Poपूर्णांकer to scsi_cmnd काष्ठाure
 *
 *	(linux scsi_host_ढाँचा.queuecommand routine)
 *	This is the primary SCSI IO start routine.  Create a MPI SCSIIORequest
 *	from a linux scsi_cmnd request and send it to the IOC.
 *
 *	Returns 0. (rtn value discarded by linux scsi mid-layer)
 */
पूर्णांक
mptscsih_qcmd(काष्ठा scsi_cmnd *SCpnt)
अणु
	MPT_SCSI_HOST		*hd;
	MPT_FRAME_HDR		*mf;
	SCSIIORequest_t		*pScsiReq;
	VirtDevice		*vdevice = SCpnt->device->hostdata;
	u32	 datalen;
	u32	 scsictl;
	u32	 scsidir;
	u32	 cmd_len;
	पूर्णांक	 my_idx;
	पूर्णांक	 ii;
	MPT_ADAPTER *ioc;

	hd = shost_priv(SCpnt->device->host);
	ioc = hd->ioc;

	dmfprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "qcmd: SCpnt=%p\n",
		ioc->name, SCpnt));

	अगर (ioc->taskmgmt_quiesce_io)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/*
	 *  Put together a MPT SCSI request...
	 */
	अगर ((mf = mpt_get_msg_frame(ioc->DoneCtx, ioc)) == शून्य) अणु
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT "QueueCmd, no msg frames!!\n",
				ioc->name));
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	pScsiReq = (SCSIIORequest_t *) mf;

	my_idx = le16_to_cpu(mf->u.frame.hwhdr.msgctxu.fld.req_idx);

	ADD_INDEX_LOG(my_idx);

	/*    TUR's being issued with scsictl=0x02000000 (DATA_IN)!
	 *    Seems we may receive a buffer (datalen>0) even when there
	 *    will be no data transfer!  GRRRRR...
	 */
	अगर (SCpnt->sc_data_direction == DMA_FROM_DEVICE) अणु
		datalen = scsi_bufflen(SCpnt);
		scsidir = MPI_SCSIIO_CONTROL_READ;	/* DATA IN  (host<--ioc<--dev) */
	पूर्ण अन्यथा अगर (SCpnt->sc_data_direction == DMA_TO_DEVICE) अणु
		datalen = scsi_bufflen(SCpnt);
		scsidir = MPI_SCSIIO_CONTROL_WRITE;	/* DATA OUT (host-->ioc-->dev) */
	पूर्ण अन्यथा अणु
		datalen = 0;
		scsidir = MPI_SCSIIO_CONTROL_NODATATRANSFER;
	पूर्ण

	/* Default to untagged. Once a target काष्ठाure has been allocated,
	 * use the Inquiry data to determine अगर device supports tagged.
	 */
	अगर ((vdevice->vtarget->tflags & MPT_TARGET_FLAGS_Q_YES) &&
	    SCpnt->device->tagged_supported)
		scsictl = scsidir | MPI_SCSIIO_CONTROL_SIMPLEQ;
	अन्यथा
		scsictl = scsidir | MPI_SCSIIO_CONTROL_UNTAGGED;


	/* Use the above inक्रमmation to set up the message frame
	 */
	pScsiReq->TargetID = (u8) vdevice->vtarget->id;
	pScsiReq->Bus = vdevice->vtarget->channel;
	pScsiReq->ChainOffset = 0;
	अगर (vdevice->vtarget->tflags &  MPT_TARGET_FLAGS_RAID_COMPONENT)
		pScsiReq->Function = MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH;
	अन्यथा
		pScsiReq->Function = MPI_FUNCTION_SCSI_IO_REQUEST;
	pScsiReq->CDBLength = SCpnt->cmd_len;
	pScsiReq->SenseBufferLength = MPT_SENSE_BUFFER_SIZE;
	pScsiReq->Reserved = 0;
	pScsiReq->MsgFlags = mpt_msg_flags(ioc);
	पूर्णांक_to_scsilun(SCpnt->device->lun, (काष्ठा scsi_lun *)pScsiReq->LUN);
	pScsiReq->Control = cpu_to_le32(scsictl);

	/*
	 *  Write SCSI CDB पूर्णांकo the message
	 */
	cmd_len = SCpnt->cmd_len;
	क्रम (ii=0; ii < cmd_len; ii++)
		pScsiReq->CDB[ii] = SCpnt->cmnd[ii];

	क्रम (ii=cmd_len; ii < 16; ii++)
		pScsiReq->CDB[ii] = 0;

	/* DataLength */
	pScsiReq->DataLength = cpu_to_le32(datalen);

	/* SenseBuffer low address */
	pScsiReq->SenseBufferLowAddr = cpu_to_le32(ioc->sense_buf_low_dma
					   + (my_idx * MPT_SENSE_BUFFER_ALLOC));

	/* Now add the SG list
	 * Always have a SGE even अगर null length.
	 */
	अगर (datalen == 0) अणु
		/* Add a शून्य SGE */
		ioc->add_sge((अक्षर *)&pScsiReq->SGL,
			MPT_SGE_FLAGS_SSIMPLE_READ | 0,
			(dma_addr_t) -1);
	पूर्ण अन्यथा अणु
		/* Add a 32 or 64 bit SGE */
		अगर (mptscsih_AddSGE(ioc, SCpnt, pScsiReq, my_idx) != SUCCESS)
			जाओ fail;
	पूर्ण

	SCpnt->host_scribble = (अचिन्हित अक्षर *)mf;
	mptscsih_set_scsi_lookup(ioc, my_idx, SCpnt);

	mpt_put_msg_frame(ioc->DoneCtx, ioc, mf);
	dmfprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Issued SCSI cmd (%p) mf=%p idx=%d\n",
			ioc->name, SCpnt, mf, my_idx));
	DBG_DUMP_REQUEST_FRAME(ioc, (u32 *)mf);
	वापस 0;

 fail:
	mptscsih_मुक्तChainBuffers(ioc, my_idx);
	mpt_मुक्त_msg_frame(ioc, mf);
	वापस SCSI_MLQUEUE_HOST_BUSY;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_मुक्तChainBuffers - Function to मुक्त chain buffers associated
 *	with a SCSI IO request
 *	@hd: Poपूर्णांकer to the MPT_SCSI_HOST instance
 *	@req_idx: Index of the SCSI IO request frame.
 *
 *	Called अगर SG chain buffer allocation fails and mptscsih callbacks.
 *	No वापस.
 */
अटल व्योम
mptscsih_मुक्तChainBuffers(MPT_ADAPTER *ioc, पूर्णांक req_idx)
अणु
	MPT_FRAME_HDR *chain;
	अचिन्हित दीर्घ flags;
	पूर्णांक chain_idx;
	पूर्णांक next;

	/* Get the first chain index and reset
	 * tracker state.
	 */
	chain_idx = ioc->ReqToChain[req_idx];
	ioc->ReqToChain[req_idx] = MPT_HOST_NO_CHAIN;

	जबतक (chain_idx != MPT_HOST_NO_CHAIN) अणु

		/* Save the next chain buffer index */
		next = ioc->ChainToChain[chain_idx];

		/* Free this chain buffer and reset
		 * tracker
		 */
		ioc->ChainToChain[chain_idx] = MPT_HOST_NO_CHAIN;

		chain = (MPT_FRAME_HDR *) (ioc->ChainBuffer
					+ (chain_idx * ioc->req_sz));

		spin_lock_irqsave(&ioc->FreeQlock, flags);
		list_add_tail(&chain->u.frame.linkage.list, &ioc->FreeChainQ);
		spin_unlock_irqrestore(&ioc->FreeQlock, flags);

		dmfprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "FreeChainBuffers (index %d)\n",
				ioc->name, chain_idx));

		/* handle next */
		chain_idx = next;
	पूर्ण
	वापस;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	Reset Handling
 */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_IssueTaskMgmt - Generic send Task Management function.
 *	@hd: Poपूर्णांकer to MPT_SCSI_HOST काष्ठाure
 *	@type: Task Management type
 *	@channel: channel number क्रम task management
 *	@id: Logical Target ID क्रम reset (अगर appropriate)
 *	@lun: Logical Unit क्रम reset (अगर appropriate)
 *	@ctx2पात: Context क्रम the task to be पातed (अगर appropriate)
 *	@समयout: समयout क्रम task management control
 *
 *	Remark: _HardResetHandler can be invoked from an पूर्णांकerrupt thपढ़ो (समयr)
 *	or a non-पूर्णांकerrupt thपढ़ो.  In the क्रमmer, must not call schedule().
 *
 *	Not all fields are meaningfull क्रम all task types.
 *
 *	Returns 0 क्रम SUCCESS, or FAILED.
 *
 **/
पूर्णांक
mptscsih_IssueTaskMgmt(MPT_SCSI_HOST *hd, u8 type, u8 channel, u8 id, u64 lun,
	पूर्णांक ctx2पात, uदीर्घ समयout)
अणु
	MPT_FRAME_HDR	*mf;
	SCSITaskMgmt_t	*pScsiTm;
	पूर्णांक		 ii;
	पूर्णांक		 retval;
	MPT_ADAPTER 	*ioc = hd->ioc;
	u8		 issue_hard_reset;
	u32		 ioc_raw_state;
	अचिन्हित दीर्घ	 समय_count;

	issue_hard_reset = 0;
	ioc_raw_state = mpt_GetIocState(ioc, 0);

	अगर ((ioc_raw_state & MPI_IOC_STATE_MASK) != MPI_IOC_STATE_OPERATIONAL) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
			"TaskMgmt type=%x: IOC Not operational (0x%x)!\n",
			ioc->name, type, ioc_raw_state);
		prपूर्णांकk(MYIOC_s_WARN_FMT "Issuing HardReset from %s!!\n",
		    ioc->name, __func__);
		अगर (mpt_HardResetHandler(ioc, CAN_SLEEP) < 0)
			prपूर्णांकk(MYIOC_s_WARN_FMT "TaskMgmt HardReset "
			    "FAILED!!\n", ioc->name);
		वापस 0;
	पूर्ण

	/* DOORBELL ACTIVE check is not required अगर
	*  MPI_IOCFACTS_CAPABILITY_HIGH_PRI_Q is supported.
	*/

	अगर (!((ioc->facts.IOCCapabilities & MPI_IOCFACTS_CAPABILITY_HIGH_PRI_Q)
		 && (ioc->facts.MsgVersion >= MPI_VERSION_01_05)) &&
		(ioc_raw_state & MPI_DOORBELL_ACTIVE)) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
			"TaskMgmt type=%x: ioc_state: "
			"DOORBELL_ACTIVE (0x%x)!\n",
			ioc->name, type, ioc_raw_state);
		वापस FAILED;
	पूर्ण

	mutex_lock(&ioc->taskmgmt_cmds.mutex);
	अगर (mpt_set_taskmgmt_in_progress_flag(ioc) != 0) अणु
		mf = शून्य;
		retval = FAILED;
		जाओ out;
	पूर्ण

	/* Return Fail to calling function अगर no message frames available.
	 */
	अगर ((mf = mpt_get_msg_frame(ioc->TaskCtx, ioc)) == शून्य) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"TaskMgmt no msg frames!!\n", ioc->name));
		retval = FAILED;
		mpt_clear_taskmgmt_in_progress_flag(ioc);
		जाओ out;
	पूर्ण
	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "TaskMgmt request (mf=%p)\n",
			ioc->name, mf));

	/* Format the Request
	 */
	pScsiTm = (SCSITaskMgmt_t *) mf;
	pScsiTm->TargetID = id;
	pScsiTm->Bus = channel;
	pScsiTm->ChainOffset = 0;
	pScsiTm->Function = MPI_FUNCTION_SCSI_TASK_MGMT;

	pScsiTm->Reserved = 0;
	pScsiTm->TaskType = type;
	pScsiTm->Reserved1 = 0;
	pScsiTm->MsgFlags = (type == MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS)
                    ? MPI_SCSITASKMGMT_MSGFLAGS_LIPRESET_RESET_OPTION : 0;

	पूर्णांक_to_scsilun(lun, (काष्ठा scsi_lun *)pScsiTm->LUN);

	क्रम (ii=0; ii < 7; ii++)
		pScsiTm->Reserved2[ii] = 0;

	pScsiTm->TaskMsgContext = ctx2पात;

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "TaskMgmt: ctx2abort (0x%08x) "
		"task_type = 0x%02X, timeout = %ld\n", ioc->name, ctx2पात,
		type, समयout));

	DBG_DUMP_TM_REQUEST_FRAME(ioc, (u32 *)pScsiTm);

	INITIALIZE_MGMT_STATUS(ioc->taskmgmt_cmds.status)
	समय_count = jअगरfies;
	अगर ((ioc->facts.IOCCapabilities & MPI_IOCFACTS_CAPABILITY_HIGH_PRI_Q) &&
	    (ioc->facts.MsgVersion >= MPI_VERSION_01_05))
		mpt_put_msg_frame_hi_pri(ioc->TaskCtx, ioc, mf);
	अन्यथा अणु
		retval = mpt_send_handshake_request(ioc->TaskCtx, ioc,
			माप(SCSITaskMgmt_t), (u32*)pScsiTm, CAN_SLEEP);
		अगर (retval) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				"TaskMgmt handshake FAILED!(mf=%p, rc=%d) \n",
				ioc->name, mf, retval));
			mpt_मुक्त_msg_frame(ioc, mf);
			mpt_clear_taskmgmt_in_progress_flag(ioc);
			जाओ out;
		पूर्ण
	पूर्ण

	रुको_क्रम_completion_समयout(&ioc->taskmgmt_cmds.करोne,
		समयout*HZ);
	अगर (!(ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		retval = FAILED;
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
		    "TaskMgmt TIMED OUT!(mf=%p)\n", ioc->name, mf));
		mpt_clear_taskmgmt_in_progress_flag(ioc);
		अगर (ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET)
			जाओ out;
		issue_hard_reset = 1;
		जाओ out;
	पूर्ण

	retval = mptscsih_taskmgmt_reply(ioc, type,
	    (SCSITaskMgmtReply_t *) ioc->taskmgmt_cmds.reply);

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "TaskMgmt completed (%d seconds)\n",
	    ioc->name, jअगरfies_to_msecs(jअगरfies - समय_count)/1000));

 out:

	CLEAR_MGMT_STATUS(ioc->taskmgmt_cmds.status)
	अगर (issue_hard_reset) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
		       "Issuing Reset from %s!! doorbell=0x%08x\n",
		       ioc->name, __func__, mpt_GetIocState(ioc, 0));
		retval = (ioc->bus_type == SAS) ?
			mpt_HardResetHandler(ioc, CAN_SLEEP) :
			mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
		mpt_मुक्त_msg_frame(ioc, mf);
	पूर्ण

	retval = (retval == 0) ? 0 : FAILED;
	mutex_unlock(&ioc->taskmgmt_cmds.mutex);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(mptscsih_IssueTaskMgmt);

अटल पूर्णांक
mptscsih_get_पंचांग_समयout(MPT_ADAPTER *ioc)
अणु
	चयन (ioc->bus_type) अणु
	हाल FC:
		वापस 40;
	हाल SAS:
		वापस 30;
	हाल SPI:
	शेष:
		वापस 10;
	पूर्ण
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_पात - Abort linux scsi_cmnd routine, new_eh variant
 *	@SCpnt: Poपूर्णांकer to scsi_cmnd काष्ठाure, IO to be पातed
 *
 *	(linux scsi_host_ढाँचा.eh_पात_handler routine)
 *
 *	Returns SUCCESS or FAILED.
 **/
पूर्णांक
mptscsih_पात(काष्ठा scsi_cmnd * SCpnt)
अणु
	MPT_SCSI_HOST	*hd;
	MPT_FRAME_HDR	*mf;
	u32		 ctx2पात;
	पूर्णांक		 scpnt_idx;
	पूर्णांक		 retval;
	VirtDevice	 *vdevice;
	MPT_ADAPTER	*ioc;

	/* If we can't locate our host adapter काष्ठाure, वापस FAILED status.
	 */
	अगर ((hd = shost_priv(SCpnt->device->host)) == शून्य) अणु
		SCpnt->result = DID_RESET << 16;
		SCpnt->scsi_करोne(SCpnt);
		prपूर्णांकk(KERN_ERR MYNAM ": task abort: "
		    "can't locate host! (sc=%p)\n", SCpnt);
		वापस FAILED;
	पूर्ण

	ioc = hd->ioc;
	prपूर्णांकk(MYIOC_s_INFO_FMT "attempting task abort! (sc=%p)\n",
	       ioc->name, SCpnt);
	scsi_prपूर्णांक_command(SCpnt);

	vdevice = SCpnt->device->hostdata;
	अगर (!vdevice || !vdevice->vtarget) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "task abort: device has been deleted (sc=%p)\n",
		    ioc->name, SCpnt));
		SCpnt->result = DID_NO_CONNECT << 16;
		SCpnt->scsi_करोne(SCpnt);
		retval = SUCCESS;
		जाओ out;
	पूर्ण

	/* Task पातs are not supported क्रम hidden raid components.
	 */
	अगर (vdevice->vtarget->tflags & MPT_TARGET_FLAGS_RAID_COMPONENT) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "task abort: hidden raid component (sc=%p)\n",
		    ioc->name, SCpnt));
		SCpnt->result = DID_RESET << 16;
		retval = FAILED;
		जाओ out;
	पूर्ण

	/* Task पातs are not supported क्रम volumes.
	 */
	अगर (vdevice->vtarget->raidVolume) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "task abort: raid volume (sc=%p)\n",
		    ioc->name, SCpnt));
		SCpnt->result = DID_RESET << 16;
		retval = FAILED;
		जाओ out;
	पूर्ण

	/* Find this command
	 */
	अगर ((scpnt_idx = SCPNT_TO_LOOKUP_IDX(ioc, SCpnt)) < 0) अणु
		/* Cmd not found in ScsiLookup.
		 * Do OS callback.
		 */
		SCpnt->result = DID_RESET << 16;
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "task abort: "
		   "Command not in the active list! (sc=%p)\n", ioc->name,
		   SCpnt));
		retval = SUCCESS;
		जाओ out;
	पूर्ण

	अगर (ioc->समयouts < -1)
		ioc->समयouts++;

	अगर (mpt_fwfault_debug)
		mpt_halt_firmware(ioc);

	/* Most important!  Set TaskMsgContext to SCpnt's MsgContext!
	 * (the IO to be ABORT'd)
	 *
	 * NOTE: Since we करो not byteswap MsgContext, we करो not
	 *	 swap it here either.  It is an opaque cookie to
	 *	 the controller, so it करोes not matter. -DaveM
	 */
	mf = MPT_INDEX_2_MFPTR(ioc, scpnt_idx);
	ctx2पात = mf->u.frame.hwhdr.msgctxu.MsgContext;
	retval = mptscsih_IssueTaskMgmt(hd,
			 MPI_SCSITASKMGMT_TASKTYPE_ABORT_TASK,
			 vdevice->vtarget->channel,
			 vdevice->vtarget->id, vdevice->lun,
			 ctx2पात, mptscsih_get_पंचांग_समयout(ioc));

	अगर (SCPNT_TO_LOOKUP_IDX(ioc, SCpnt) == scpnt_idx) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "task abort: command still in active list! (sc=%p)\n",
		    ioc->name, SCpnt));
		retval = FAILED;
	पूर्ण अन्यथा अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "task abort: command cleared from active list! (sc=%p)\n",
		    ioc->name, SCpnt));
		retval = SUCCESS;
	पूर्ण

 out:
	prपूर्णांकk(MYIOC_s_INFO_FMT "task abort: %s (rv=%04x) (sc=%p)\n",
	    ioc->name, ((retval == SUCCESS) ? "SUCCESS" : "FAILED"), retval,
	    SCpnt);

	वापस retval;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_dev_reset - Perक्रमm a SCSI TARGET_RESET!  new_eh variant
 *	@SCpnt: Poपूर्णांकer to scsi_cmnd काष्ठाure, IO which reset is due to
 *
 *	(linux scsi_host_ढाँचा.eh_dev_reset_handler routine)
 *
 *	Returns SUCCESS or FAILED.
 **/
पूर्णांक
mptscsih_dev_reset(काष्ठा scsi_cmnd * SCpnt)
अणु
	MPT_SCSI_HOST	*hd;
	पूर्णांक		 retval;
	VirtDevice	 *vdevice;
	MPT_ADAPTER	*ioc;

	/* If we can't locate our host adapter काष्ठाure, वापस FAILED status.
	 */
	अगर ((hd = shost_priv(SCpnt->device->host)) == शून्य)अणु
		prपूर्णांकk(KERN_ERR MYNAM ": target reset: "
		   "Can't locate host! (sc=%p)\n", SCpnt);
		वापस FAILED;
	पूर्ण

	ioc = hd->ioc;
	prपूर्णांकk(MYIOC_s_INFO_FMT "attempting target reset! (sc=%p)\n",
	       ioc->name, SCpnt);
	scsi_prपूर्णांक_command(SCpnt);

	vdevice = SCpnt->device->hostdata;
	अगर (!vdevice || !vdevice->vtarget) अणु
		retval = 0;
		जाओ out;
	पूर्ण

	/* Target reset to hidden raid component is not supported
	 */
	अगर (vdevice->vtarget->tflags & MPT_TARGET_FLAGS_RAID_COMPONENT) अणु
		retval = FAILED;
		जाओ out;
	पूर्ण

	retval = mptscsih_IssueTaskMgmt(hd,
				MPI_SCSITASKMGMT_TASKTYPE_TARGET_RESET,
				vdevice->vtarget->channel,
				vdevice->vtarget->id, 0, 0,
				mptscsih_get_पंचांग_समयout(ioc));

 out:
	prपूर्णांकk (MYIOC_s_INFO_FMT "target reset: %s (sc=%p)\n",
	    ioc->name, ((retval == 0) ? "SUCCESS" : "FAILED" ), SCpnt);

	अगर (retval == 0)
		वापस SUCCESS;
	अन्यथा
		वापस FAILED;
पूर्ण


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_bus_reset - Perक्रमm a SCSI BUS_RESET!	new_eh variant
 *	@SCpnt: Poपूर्णांकer to scsi_cmnd काष्ठाure, IO which reset is due to
 *
 *	(linux scsi_host_ढाँचा.eh_bus_reset_handler routine)
 *
 *	Returns SUCCESS or FAILED.
 **/
पूर्णांक
mptscsih_bus_reset(काष्ठा scsi_cmnd * SCpnt)
अणु
	MPT_SCSI_HOST	*hd;
	पूर्णांक		 retval;
	VirtDevice	 *vdevice;
	MPT_ADAPTER	*ioc;

	/* If we can't locate our host adapter काष्ठाure, वापस FAILED status.
	 */
	अगर ((hd = shost_priv(SCpnt->device->host)) == शून्य)अणु
		prपूर्णांकk(KERN_ERR MYNAM ": bus reset: "
		   "Can't locate host! (sc=%p)\n", SCpnt);
		वापस FAILED;
	पूर्ण

	ioc = hd->ioc;
	prपूर्णांकk(MYIOC_s_INFO_FMT "attempting bus reset! (sc=%p)\n",
	       ioc->name, SCpnt);
	scsi_prपूर्णांक_command(SCpnt);

	अगर (ioc->समयouts < -1)
		ioc->समयouts++;

	vdevice = SCpnt->device->hostdata;
	अगर (!vdevice || !vdevice->vtarget)
		वापस SUCCESS;
	retval = mptscsih_IssueTaskMgmt(hd,
					MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS,
					vdevice->vtarget->channel, 0, 0, 0,
					mptscsih_get_पंचांग_समयout(ioc));

	prपूर्णांकk(MYIOC_s_INFO_FMT "bus reset: %s (sc=%p)\n",
	    ioc->name, ((retval == 0) ? "SUCCESS" : "FAILED" ), SCpnt);

	अगर (retval == 0)
		वापस SUCCESS;
	अन्यथा
		वापस FAILED;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_host_reset - Perक्रमm a SCSI host adapter RESET (new_eh variant)
 *	@SCpnt: Poपूर्णांकer to scsi_cmnd काष्ठाure, IO which reset is due to
 *
 *	(linux scsi_host_ढाँचा.eh_host_reset_handler routine)
 *
 *	Returns SUCCESS or FAILED.
 */
पूर्णांक
mptscsih_host_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	MPT_SCSI_HOST *  hd;
	पूर्णांक              status = SUCCESS;
	MPT_ADAPTER	*ioc;
	पूर्णांक		retval;

	/*  If we can't locate the host to reset, then we failed. */
	अगर ((hd = shost_priv(SCpnt->device->host)) == शून्य)अणु
		prपूर्णांकk(KERN_ERR MYNAM ": host reset: "
		    "Can't locate host! (sc=%p)\n", SCpnt);
		वापस FAILED;
	पूर्ण

	/* make sure we have no outstanding commands at this stage */
	mptscsih_flush_running_cmds(hd);

	ioc = hd->ioc;
	prपूर्णांकk(MYIOC_s_INFO_FMT "attempting host reset! (sc=%p)\n",
	    ioc->name, SCpnt);

	/*  If our attempts to reset the host failed, then वापस a failed
	 *  status.  The host will be taken off line by the SCSI mid-layer.
	 */
	retval = mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
	अगर (retval < 0)
		status = FAILED;
	अन्यथा
		status = SUCCESS;

	prपूर्णांकk(MYIOC_s_INFO_FMT "host reset: %s (sc=%p)\n",
	    ioc->name, ((retval == 0) ? "SUCCESS" : "FAILED" ), SCpnt);

	वापस status;
पूर्ण

अटल पूर्णांक
mptscsih_taskmgmt_reply(MPT_ADAPTER *ioc, u8 type,
	SCSITaskMgmtReply_t *pScsiTmReply)
अणु
	u16			 iocstatus;
	u32			 termination_count;
	पूर्णांक			 retval;

	अगर (!(ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_RF_VALID)) अणु
		retval = FAILED;
		जाओ out;
	पूर्ण

	DBG_DUMP_TM_REPLY_FRAME(ioc, (u32 *)pScsiTmReply);

	iocstatus = le16_to_cpu(pScsiTmReply->IOCStatus) & MPI_IOCSTATUS_MASK;
	termination_count = le32_to_cpu(pScsiTmReply->TerminationCount);

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "TaskMgmt fw_channel = %d, fw_id = %d, task_type = 0x%02X,\n"
	    "\tiocstatus = 0x%04X, loginfo = 0x%08X, response_code = 0x%02X,\n"
	    "\tterm_cmnds = %d\n", ioc->name, pScsiTmReply->Bus,
	    pScsiTmReply->TargetID, type, le16_to_cpu(pScsiTmReply->IOCStatus),
	    le32_to_cpu(pScsiTmReply->IOCLogInfo), pScsiTmReply->ResponseCode,
	    termination_count));

	अगर (ioc->facts.MsgVersion >= MPI_VERSION_01_05 &&
	    pScsiTmReply->ResponseCode)
		mptscsih_taskmgmt_response_code(ioc,
		    pScsiTmReply->ResponseCode);

	अगर (iocstatus == MPI_IOCSTATUS_SUCCESS) अणु
		retval = 0;
		जाओ out;
	पूर्ण

	retval = FAILED;
	अगर (type == MPI_SCSITASKMGMT_TASKTYPE_ABORT_TASK) अणु
		अगर (termination_count == 1)
			retval = 0;
		जाओ out;
	पूर्ण

	अगर (iocstatus == MPI_IOCSTATUS_SCSI_TASK_TERMINATED ||
	   iocstatus == MPI_IOCSTATUS_SCSI_IOC_TERMINATED)
		retval = 0;

 out:
	वापस retval;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
व्योम
mptscsih_taskmgmt_response_code(MPT_ADAPTER *ioc, u8 response_code)
अणु
	अक्षर *desc;

	चयन (response_code) अणु
	हाल MPI_SCSITASKMGMT_RSP_TM_COMPLETE:
		desc = "The task completed.";
		अवरोध;
	हाल MPI_SCSITASKMGMT_RSP_INVALID_FRAME:
		desc = "The IOC received an invalid frame status.";
		अवरोध;
	हाल MPI_SCSITASKMGMT_RSP_TM_NOT_SUPPORTED:
		desc = "The task type is not supported.";
		अवरोध;
	हाल MPI_SCSITASKMGMT_RSP_TM_FAILED:
		desc = "The requested task failed.";
		अवरोध;
	हाल MPI_SCSITASKMGMT_RSP_TM_SUCCEEDED:
		desc = "The task completed successfully.";
		अवरोध;
	हाल MPI_SCSITASKMGMT_RSP_TM_INVALID_LUN:
		desc = "The LUN request is invalid.";
		अवरोध;
	हाल MPI_SCSITASKMGMT_RSP_IO_QUEUED_ON_IOC:
		desc = "The task is in the IOC queue and has not been sent to target.";
		अवरोध;
	शेष:
		desc = "unknown";
		अवरोध;
	पूर्ण
	prपूर्णांकk(MYIOC_s_INFO_FMT "Response Code(0x%08x): F/W: %s\n",
		ioc->name, response_code, desc);
पूर्ण
EXPORT_SYMBOL(mptscsih_taskmgmt_response_code);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_taskmgmt_complete - Registered with Fusion MPT base driver
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@mf: Poपूर्णांकer to SCSI task mgmt request frame
 *	@mr: Poपूर्णांकer to SCSI task mgmt reply frame
 *
 *	This routine is called from mptbase.c::mpt_पूर्णांकerrupt() at the completion
 *	of any SCSI task management request.
 *	This routine is रेजिस्टरed with the MPT (base) driver at driver
 *	load/init समय via the mpt_रेजिस्टर() API call.
 *
 *	Returns 1 indicating alloc'd request frame ptr should be मुक्तd.
 **/
पूर्णांक
mptscsih_taskmgmt_complete(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf,
	MPT_FRAME_HDR *mr)
अणु
	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"TaskMgmt completed (mf=%p, mr=%p)\n", ioc->name, mf, mr));

	ioc->taskmgmt_cmds.status |= MPT_MGMT_STATUS_COMMAND_GOOD;

	अगर (!mr)
		जाओ out;

	ioc->taskmgmt_cmds.status |= MPT_MGMT_STATUS_RF_VALID;
	स_नकल(ioc->taskmgmt_cmds.reply, mr,
	    min(MPT_DEFAULT_FRAME_SIZE, 4 * mr->u.reply.MsgLength));
 out:
	अगर (ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_PENDING) अणु
		mpt_clear_taskmgmt_in_progress_flag(ioc);
		ioc->taskmgmt_cmds.status &= ~MPT_MGMT_STATUS_PENDING;
		complete(&ioc->taskmgmt_cmds.करोne);
		अगर (ioc->bus_type == SAS)
			ioc->schedule_target_reset(ioc);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	This is anyones guess quite frankly.
 */
पूर्णांक
mptscsih_bios_param(काष्ठा scsi_device * sdev, काष्ठा block_device *bdev,
		sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक		heads;
	पूर्णांक		sectors;
	sector_t	cylinders;
	uदीर्घ 		dummy;

	heads = 64;
	sectors = 32;

	dummy = heads * sectors;
	cylinders = capacity;
	sector_भाग(cylinders,dummy);

	/*
	 * Handle extended translation size क्रम logical drives
	 * > 1Gb
	 */
	अगर ((uदीर्घ)capacity >= 0x200000) अणु
		heads = 255;
		sectors = 63;
		dummy = heads * sectors;
		cylinders = capacity;
		sector_भाग(cylinders,dummy);
	पूर्ण

	/* वापस result */
	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;

	वापस 0;
पूर्ण

/* Search IOC page 3 to determine अगर this is hidden physical disk
 *
 */
पूर्णांक
mptscsih_is_phys_disk(MPT_ADAPTER *ioc, u8 channel, u8 id)
अणु
	काष्ठा inactive_raid_component_info *component_info;
	पूर्णांक i, j;
	RaidPhysDiskPage1_t *phys_disk;
	पूर्णांक rc = 0;
	पूर्णांक num_paths;

	अगर (!ioc->raid_data.pIocPg3)
		जाओ out;
	क्रम (i = 0; i < ioc->raid_data.pIocPg3->NumPhysDisks; i++) अणु
		अगर ((id == ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskID) &&
		    (channel == ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskBus)) अणु
			rc = 1;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ioc->bus_type != SAS)
		जाओ out;

	/*
	 * Check अगर dual path
	 */
	क्रम (i = 0; i < ioc->raid_data.pIocPg3->NumPhysDisks; i++) अणु
		num_paths = mpt_raid_phys_disk_get_num_paths(ioc,
		    ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskNum);
		अगर (num_paths < 2)
			जारी;
		phys_disk = kzalloc(दुरत्व(RaidPhysDiskPage1_t, Path) +
		   (num_paths * माप(RAID_PHYS_DISK1_PATH)), GFP_KERNEL);
		अगर (!phys_disk)
			जारी;
		अगर ((mpt_raid_phys_disk_pg1(ioc,
		    ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskNum,
		    phys_disk))) अणु
			kमुक्त(phys_disk);
			जारी;
		पूर्ण
		क्रम (j = 0; j < num_paths; j++) अणु
			अगर ((phys_disk->Path[j].Flags &
			    MPI_RAID_PHYSDISK1_FLAG_INVALID))
				जारी;
			अगर ((phys_disk->Path[j].Flags &
			    MPI_RAID_PHYSDISK1_FLAG_BROKEN))
				जारी;
			अगर ((id == phys_disk->Path[j].PhysDiskID) &&
			    (channel == phys_disk->Path[j].PhysDiskBus)) अणु
				rc = 1;
				kमुक्त(phys_disk);
				जाओ out;
			पूर्ण
		पूर्ण
		kमुक्त(phys_disk);
	पूर्ण


	/*
	 * Check inactive list क्रम matching phys disks
	 */
	अगर (list_empty(&ioc->raid_data.inactive_list))
		जाओ out;

	mutex_lock(&ioc->raid_data.inactive_list_mutex);
	list_क्रम_each_entry(component_info, &ioc->raid_data.inactive_list,
	    list) अणु
		अगर ((component_info->d.PhysDiskID == id) &&
		    (component_info->d.PhysDiskBus == channel))
			rc = 1;
	पूर्ण
	mutex_unlock(&ioc->raid_data.inactive_list_mutex);

 out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(mptscsih_is_phys_disk);

u8
mptscsih_raid_id_to_num(MPT_ADAPTER *ioc, u8 channel, u8 id)
अणु
	काष्ठा inactive_raid_component_info *component_info;
	पूर्णांक i, j;
	RaidPhysDiskPage1_t *phys_disk;
	पूर्णांक rc = -ENXIO;
	पूर्णांक num_paths;

	अगर (!ioc->raid_data.pIocPg3)
		जाओ out;
	क्रम (i = 0; i < ioc->raid_data.pIocPg3->NumPhysDisks; i++) अणु
		अगर ((id == ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskID) &&
		    (channel == ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskBus)) अणु
			rc = ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskNum;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ioc->bus_type != SAS)
		जाओ out;

	/*
	 * Check अगर dual path
	 */
	क्रम (i = 0; i < ioc->raid_data.pIocPg3->NumPhysDisks; i++) अणु
		num_paths = mpt_raid_phys_disk_get_num_paths(ioc,
		    ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskNum);
		अगर (num_paths < 2)
			जारी;
		phys_disk = kzalloc(दुरत्व(RaidPhysDiskPage1_t, Path) +
		   (num_paths * माप(RAID_PHYS_DISK1_PATH)), GFP_KERNEL);
		अगर (!phys_disk)
			जारी;
		अगर ((mpt_raid_phys_disk_pg1(ioc,
		    ioc->raid_data.pIocPg3->PhysDisk[i].PhysDiskNum,
		    phys_disk))) अणु
			kमुक्त(phys_disk);
			जारी;
		पूर्ण
		क्रम (j = 0; j < num_paths; j++) अणु
			अगर ((phys_disk->Path[j].Flags &
			    MPI_RAID_PHYSDISK1_FLAG_INVALID))
				जारी;
			अगर ((phys_disk->Path[j].Flags &
			    MPI_RAID_PHYSDISK1_FLAG_BROKEN))
				जारी;
			अगर ((id == phys_disk->Path[j].PhysDiskID) &&
			    (channel == phys_disk->Path[j].PhysDiskBus)) अणु
				rc = phys_disk->PhysDiskNum;
				kमुक्त(phys_disk);
				जाओ out;
			पूर्ण
		पूर्ण
		kमुक्त(phys_disk);
	पूर्ण

	/*
	 * Check inactive list क्रम matching phys disks
	 */
	अगर (list_empty(&ioc->raid_data.inactive_list))
		जाओ out;

	mutex_lock(&ioc->raid_data.inactive_list_mutex);
	list_क्रम_each_entry(component_info, &ioc->raid_data.inactive_list,
	    list) अणु
		अगर ((component_info->d.PhysDiskID == id) &&
		    (component_info->d.PhysDiskBus == channel))
			rc = component_info->d.PhysDiskNum;
	पूर्ण
	mutex_unlock(&ioc->raid_data.inactive_list_mutex);

 out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(mptscsih_raid_id_to_num);

/*
 *	OS entry poपूर्णांक to allow क्रम host driver to मुक्त allocated memory
 *	Called अगर no device present or device being unloaded
 */
व्योम
mptscsih_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host	*host = sdev->host;
	MPT_SCSI_HOST		*hd = shost_priv(host);
	VirtTarget		*vtarget;
	VirtDevice		*vdevice;
	काष्ठा scsi_target 	*starget;

	starget = scsi_target(sdev);
	vtarget = starget->hostdata;
	vdevice = sdev->hostdata;
	अगर (!vdevice)
		वापस;

	mptscsih_search_running_cmds(hd, vdevice);
	vtarget->num_luns--;
	mptscsih_synchronize_cache(hd, vdevice);
	kमुक्त(vdevice);
	sdev->hostdata = शून्य;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_change_queue_depth - This function will set a devices queue depth
 *	@sdev: per scsi_device poपूर्णांकer
 *	@qdepth: requested queue depth
 *
 *	Adding support क्रम new 'change_queue_depth' api.
*/
पूर्णांक
mptscsih_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	MPT_SCSI_HOST		*hd = shost_priv(sdev->host);
	VirtTarget 		*vtarget;
	काष्ठा scsi_target 	*starget;
	पूर्णांक			max_depth;
	MPT_ADAPTER		*ioc = hd->ioc;

	starget = scsi_target(sdev);
	vtarget = starget->hostdata;

	अगर (ioc->bus_type == SPI) अणु
		अगर (!(vtarget->tflags & MPT_TARGET_FLAGS_Q_YES))
			max_depth = 1;
		अन्यथा अगर (sdev->type == TYPE_DISK &&
			 vtarget->minSyncFactor <= MPT_ULTRA160)
			max_depth = MPT_SCSI_CMD_PER_DEV_HIGH;
		अन्यथा
			max_depth = MPT_SCSI_CMD_PER_DEV_LOW;
	पूर्ण अन्यथा
		 max_depth = ioc->sh->can_queue;

	अगर (!sdev->tagged_supported)
		max_depth = 1;

	अगर (qdepth > max_depth)
		qdepth = max_depth;

	वापस scsi_change_queue_depth(sdev, qdepth);
पूर्ण

/*
 *	OS entry poपूर्णांक to adjust the queue_depths on a per-device basis.
 *	Called once per device the bus scan. Use it to क्रमce the queue_depth
 *	member to 1 अगर a device करोes not support Q tags.
 *	Return non-zero अगर fails.
 */
पूर्णांक
mptscsih_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host	*sh = sdev->host;
	VirtTarget		*vtarget;
	VirtDevice		*vdevice;
	काष्ठा scsi_target 	*starget;
	MPT_SCSI_HOST		*hd = shost_priv(sh);
	MPT_ADAPTER		*ioc = hd->ioc;

	starget = scsi_target(sdev);
	vtarget = starget->hostdata;
	vdevice = sdev->hostdata;

	dsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"device @ %p, channel=%d, id=%d, lun=%llu\n",
		ioc->name, sdev, sdev->channel, sdev->id, sdev->lun));
	अगर (ioc->bus_type == SPI)
		dsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "sdtr %d wdtr %d ppr %d inq length=%d\n",
		    ioc->name, sdev->sdtr, sdev->wdtr,
		    sdev->ppr, sdev->inquiry_len));

	vdevice->configured_lun = 1;

	dsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"Queue depth=%d, tflags=%x\n",
		ioc->name, sdev->queue_depth, vtarget->tflags));

	अगर (ioc->bus_type == SPI)
		dsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "negoFlags=%x, maxOffset=%x, SyncFactor=%x\n",
		    ioc->name, vtarget->negoFlags, vtarget->maxOffset,
		    vtarget->minSyncFactor));

	mptscsih_change_queue_depth(sdev, MPT_SCSI_CMD_PER_DEV_HIGH);
	dsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"tagged %d, simple %d\n",
		ioc->name,sdev->tagged_supported, sdev->simple_tags));

	blk_queue_dma_alignment (sdev->request_queue, 512 - 1);

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Private routines...
 */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Utility function to copy sense data from the scsi_cmnd buffer
 * to the FC and SCSI target काष्ठाures.
 *
 */
अटल व्योम
mptscsih_copy_sense_data(काष्ठा scsi_cmnd *sc, MPT_SCSI_HOST *hd, MPT_FRAME_HDR *mf, SCSIIOReply_t *pScsiReply)
अणु
	VirtDevice	*vdevice;
	SCSIIORequest_t	*pReq;
	u32		 sense_count = le32_to_cpu(pScsiReply->SenseCount);
	MPT_ADAPTER 	*ioc = hd->ioc;

	/* Get target काष्ठाure
	 */
	pReq = (SCSIIORequest_t *) mf;
	vdevice = sc->device->hostdata;

	अगर (sense_count) अणु
		u8 *sense_data;
		पूर्णांक req_index;

		/* Copy the sense received पूर्णांकo the scsi command block. */
		req_index = le16_to_cpu(mf->u.frame.hwhdr.msgctxu.fld.req_idx);
		sense_data = ((u8 *)ioc->sense_buf_pool + (req_index * MPT_SENSE_BUFFER_ALLOC));
		स_नकल(sc->sense_buffer, sense_data, MPT_SENSE_BUFFER_ALLOC);

		/* Log SMART data (asc = 0x5D, non-IM हाल only) अगर required.
		 */
		अगर ((ioc->events) && (ioc->eventTypes & (1 << MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE))) अणु
			अगर ((sense_data[12] == 0x5D) && (vdevice->vtarget->raidVolume == 0)) अणु
				पूर्णांक idx;

				idx = ioc->eventContext % MPTCTL_EVENT_LOG_SIZE;
				ioc->events[idx].event = MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE;
				ioc->events[idx].eventContext = ioc->eventContext;

				ioc->events[idx].data[0] = (pReq->LUN[1] << 24) |
					(MPI_EVENT_SCSI_DEV_STAT_RC_SMART_DATA << 16) |
					(sc->device->channel << 8) | sc->device->id;

				ioc->events[idx].data[1] = (sense_data[13] << 8) | sense_data[12];

				ioc->eventContext++;
				अगर (ioc->pcidev->venकरोr ==
				    PCI_VENDOR_ID_IBM) अणु
					mptscsih_issue_sep_command(ioc,
					    vdevice->vtarget, MPI_SEP_REQ_SLOTSTATUS_PREDICTED_FAULT);
					vdevice->vtarget->tflags |=
					    MPT_TARGET_FLAGS_LED_ON;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Hmmm... SenseData len=0! (?)\n",
				ioc->name));
	पूर्ण
पूर्ण

/**
 * mptscsih_get_scsi_lookup - retrieves scmd entry
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @i: index पूर्णांकo the array
 *
 * Returns the scsi_cmd poपूर्णांकer
 */
काष्ठा scsi_cmnd *
mptscsih_get_scsi_lookup(MPT_ADAPTER *ioc, पूर्णांक i)
अणु
	अचिन्हित दीर्घ	flags;
	काष्ठा scsi_cmnd *scmd;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	scmd = ioc->ScsiLookup[i];
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);

	वापस scmd;
पूर्ण
EXPORT_SYMBOL(mptscsih_get_scsi_lookup);

/**
 * mptscsih_अ_लोlear_scsi_lookup -  retrieves and clears scmd entry from ScsiLookup[] array list
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @i: index पूर्णांकo the array
 *
 * Returns the scsi_cmd poपूर्णांकer
 *
 **/
अटल काष्ठा scsi_cmnd *
mptscsih_अ_लोlear_scsi_lookup(MPT_ADAPTER *ioc, पूर्णांक i)
अणु
	अचिन्हित दीर्घ	flags;
	काष्ठा scsi_cmnd *scmd;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	scmd = ioc->ScsiLookup[i];
	ioc->ScsiLookup[i] = शून्य;
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);

	वापस scmd;
पूर्ण

/**
 * mptscsih_set_scsi_lookup - ग_लिखो a scmd entry पूर्णांकo the ScsiLookup[] array list
 *
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @i: index पूर्णांकo the array
 * @scmd: scsi_cmnd poपूर्णांकer
 *
 **/
अटल व्योम
mptscsih_set_scsi_lookup(MPT_ADAPTER *ioc, पूर्णांक i, काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	ioc->ScsiLookup[i] = scmd;
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
पूर्ण

/**
 * SCPNT_TO_LOOKUP_IDX - searches क्रम a given scmd in the ScsiLookup[] array list
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @sc: scsi_cmnd poपूर्णांकer
 */
अटल पूर्णांक
SCPNT_TO_LOOKUP_IDX(MPT_ADAPTER *ioc, काष्ठा scsi_cmnd *sc)
अणु
	अचिन्हित दीर्घ	flags;
	पूर्णांक i, index=-1;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	क्रम (i = 0; i < ioc->req_depth; i++) अणु
		अगर (ioc->ScsiLookup[i] == sc) अणु
			index = i;
			जाओ out;
		पूर्ण
	पूर्ण

 out:
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
	वापस index;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
पूर्णांक
mptscsih_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase)
अणु
	MPT_SCSI_HOST	*hd;

	अगर (ioc->sh == शून्य || shost_priv(ioc->sh) == शून्य)
		वापस 0;

	hd = shost_priv(ioc->sh);
	चयन (reset_phase) अणु
	हाल MPT_IOC_SETUP_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_SETUP_RESET\n", ioc->name, __func__));
		अवरोध;
	हाल MPT_IOC_PRE_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_PRE_RESET\n", ioc->name, __func__));
		mptscsih_flush_running_cmds(hd);
		अवरोध;
	हाल MPT_IOC_POST_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_POST_RESET\n", ioc->name, __func__));
		अगर (ioc->पूर्णांकernal_cmds.status & MPT_MGMT_STATUS_PENDING) अणु
			ioc->पूर्णांकernal_cmds.status |=
				MPT_MGMT_STATUS_DID_IOCRESET;
			complete(&ioc->पूर्णांकernal_cmds.करोne);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 1;		/* currently means nothing really */
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
पूर्णांक
mptscsih_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply)
अणु
	u8 event = le32_to_cpu(pEvReply->Event) & 0xFF;

	devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"MPT event (=%02Xh) routed to SCSI host driver!\n",
		ioc->name, event));

	अगर ((event == MPI_EVENT_IOC_BUS_RESET ||
	    event == MPI_EVENT_EXT_BUS_RESET) &&
	    (ioc->bus_type == SPI) && (ioc->soft_resets < -1))
			ioc->soft_resets++;

	वापस 1;		/* currently means nothing really */
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Bus Scan and Doमुख्य Validation functionality ...
 */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptscsih_scandv_complete - Scan and DV callback routine रेजिस्टरed
 *	to Fustion MPT (base) driver.
 *
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@mf: Poपूर्णांकer to original MPT request frame
 *	@mr: Poपूर्णांकer to MPT reply frame (शून्य अगर TurboReply)
 *
 *	This routine is called from mpt.c::mpt_पूर्णांकerrupt() at the completion
 *	of any SCSI IO request.
 *	This routine is रेजिस्टरed with the Fusion MPT (base) driver at driver
 *	load/init समय via the mpt_रेजिस्टर() API call.
 *
 *	Returns 1 indicating alloc'd request frame ptr should be मुक्तd.
 *
 *	Remark: Sets a completion code and (possibly) saves sense data
 *	in the IOC member localReply काष्ठाure.
 *	Used ONLY क्रम DV and other पूर्णांकernal commands.
 */
पूर्णांक
mptscsih_scandv_complete(MPT_ADAPTER *ioc, MPT_FRAME_HDR *req,
				MPT_FRAME_HDR *reply)
अणु
	SCSIIORequest_t *pReq;
	SCSIIOReply_t	*pReply;
	u8		 cmd;
	u16		 req_idx;
	u8	*sense_data;
	पूर्णांक		 sz;

	ioc->पूर्णांकernal_cmds.status |= MPT_MGMT_STATUS_COMMAND_GOOD;
	ioc->पूर्णांकernal_cmds.completion_code = MPT_SCANDV_GOOD;
	अगर (!reply)
		जाओ out;

	pReply = (SCSIIOReply_t *) reply;
	pReq = (SCSIIORequest_t *) req;
	ioc->पूर्णांकernal_cmds.completion_code =
	    mptscsih_get_completion_code(ioc, req, reply);
	ioc->पूर्णांकernal_cmds.status |= MPT_MGMT_STATUS_RF_VALID;
	स_नकल(ioc->पूर्णांकernal_cmds.reply, reply,
	    min(MPT_DEFAULT_FRAME_SIZE, 4 * reply->u.reply.MsgLength));
	cmd = reply->u.hdr.Function;
	अगर (((cmd == MPI_FUNCTION_SCSI_IO_REQUEST) ||
	    (cmd == MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH)) &&
	    (pReply->SCSIState & MPI_SCSI_STATE_AUTOSENSE_VALID)) अणु
		req_idx = le16_to_cpu(req->u.frame.hwhdr.msgctxu.fld.req_idx);
		sense_data = ((u8 *)ioc->sense_buf_pool +
		    (req_idx * MPT_SENSE_BUFFER_ALLOC));
		sz = min_t(पूर्णांक, pReq->SenseBufferLength,
		    MPT_SENSE_BUFFER_ALLOC);
		स_नकल(ioc->पूर्णांकernal_cmds.sense, sense_data, sz);
	पूर्ण
 out:
	अगर (!(ioc->पूर्णांकernal_cmds.status & MPT_MGMT_STATUS_PENDING))
		वापस 0;
	ioc->पूर्णांकernal_cmds.status &= ~MPT_MGMT_STATUS_PENDING;
	complete(&ioc->पूर्णांकernal_cmds.करोne);
	वापस 1;
पूर्ण


/**
 *	mptscsih_get_completion_code - get completion code from MPT request
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@req: Poपूर्णांकer to original MPT request frame
 *	@reply: Poपूर्णांकer to MPT reply frame (शून्य अगर TurboReply)
 *
 **/
अटल पूर्णांक
mptscsih_get_completion_code(MPT_ADAPTER *ioc, MPT_FRAME_HDR *req,
				MPT_FRAME_HDR *reply)
अणु
	SCSIIOReply_t	*pReply;
	MpiRaidActionReply_t *pr;
	u8		 scsi_status;
	u16		 status;
	पूर्णांक		 completion_code;

	pReply = (SCSIIOReply_t *)reply;
	status = le16_to_cpu(pReply->IOCStatus) & MPI_IOCSTATUS_MASK;
	scsi_status = pReply->SCSIStatus;

	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "IOCStatus=%04xh, SCSIState=%02xh, SCSIStatus=%02xh,"
	    "IOCLogInfo=%08xh\n", ioc->name, status, pReply->SCSIState,
	    scsi_status, le32_to_cpu(pReply->IOCLogInfo)));

	चयन (status) अणु

	हाल MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE:	/* 0x0043 */
		completion_code = MPT_SCANDV_SELECTION_TIMEOUT;
		अवरोध;

	हाल MPI_IOCSTATUS_SCSI_IO_DATA_ERROR:		/* 0x0046 */
	हाल MPI_IOCSTATUS_SCSI_TASK_TERMINATED:	/* 0x0048 */
	हाल MPI_IOCSTATUS_SCSI_IOC_TERMINATED:		/* 0x004B */
	हाल MPI_IOCSTATUS_SCSI_EXT_TERMINATED:		/* 0x004C */
		completion_code = MPT_SCANDV_DID_RESET;
		अवरोध;

	हाल MPI_IOCSTATUS_BUSY:
	हाल MPI_IOCSTATUS_INSUFFICIENT_RESOURCES:
		completion_code = MPT_SCANDV_BUSY;
		अवरोध;

	हाल MPI_IOCSTATUS_SCSI_DATA_UNDERRUN:		/* 0x0045 */
	हाल MPI_IOCSTATUS_SCSI_RECOVERED_ERROR:	/* 0x0040 */
	हाल MPI_IOCSTATUS_SUCCESS:			/* 0x0000 */
		अगर (pReply->Function == MPI_FUNCTION_CONFIG) अणु
			completion_code = MPT_SCANDV_GOOD;
		पूर्ण अन्यथा अगर (pReply->Function == MPI_FUNCTION_RAID_ACTION) अणु
			pr = (MpiRaidActionReply_t *)reply;
			अगर (le16_to_cpu(pr->ActionStatus) ==
				MPI_RAID_ACTION_ASTATUS_SUCCESS)
				completion_code = MPT_SCANDV_GOOD;
			अन्यथा
				completion_code = MPT_SCANDV_SOME_ERROR;
		पूर्ण अन्यथा अगर (pReply->SCSIState & MPI_SCSI_STATE_AUTOSENSE_VALID)
			completion_code = MPT_SCANDV_SENSE;
		अन्यथा अगर (pReply->SCSIState & MPI_SCSI_STATE_AUTOSENSE_FAILED) अणु
			अगर (req->u.scsireq.CDB[0] == INQUIRY)
				completion_code = MPT_SCANDV_ISSUE_SENSE;
			अन्यथा
				completion_code = MPT_SCANDV_DID_RESET;
		पूर्ण अन्यथा अगर (pReply->SCSIState & MPI_SCSI_STATE_NO_SCSI_STATUS)
			completion_code = MPT_SCANDV_DID_RESET;
		अन्यथा अगर (pReply->SCSIState & MPI_SCSI_STATE_TERMINATED)
			completion_code = MPT_SCANDV_DID_RESET;
		अन्यथा अगर (scsi_status == MPI_SCSI_STATUS_BUSY)
			completion_code = MPT_SCANDV_BUSY;
		अन्यथा
			completion_code = MPT_SCANDV_GOOD;
		अवरोध;

	हाल MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR:		/* 0x0047 */
		अगर (pReply->SCSIState & MPI_SCSI_STATE_TERMINATED)
			completion_code = MPT_SCANDV_DID_RESET;
		अन्यथा
			completion_code = MPT_SCANDV_SOME_ERROR;
		अवरोध;
	शेष:
		completion_code = MPT_SCANDV_SOME_ERROR;
		अवरोध;

	पूर्ण	/* चयन(status) */

	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "  completionCode set to %08xh\n", ioc->name, completion_code));
	वापस completion_code;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_करो_cmd - Do पूर्णांकernal command.
 *	@hd: MPT_SCSI_HOST poपूर्णांकer
 *	@io: INTERNAL_CMD poपूर्णांकer.
 *
 *	Issue the specअगरied पूर्णांकernally generated command and करो command
 *	specअगरic cleanup. For bus scan / DV only.
 *	NOTES: If command is Inquiry and status is good,
 *	initialize a target काष्ठाure, save the data
 *
 *	Remark: Single thपढ़ोed access only.
 *
 *	Return:
 *		< 0 अगर an illegal command or no resources
 *
 *		   0 अगर good
 *
 *		 > 0 अगर command complete but some type of completion error.
 */
अटल पूर्णांक
mptscsih_करो_cmd(MPT_SCSI_HOST *hd, INTERNAL_CMD *io)
अणु
	MPT_FRAME_HDR	*mf;
	SCSIIORequest_t	*pScsiReq;
	पूर्णांक		 my_idx, ii, dir;
	पूर्णांक		 समयout;
	अक्षर		 cmdLen;
	अक्षर		 CDB[]=अणु0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0पूर्ण;
	u8		 cmd = io->cmd;
	MPT_ADAPTER *ioc = hd->ioc;
	पूर्णांक		 ret = 0;
	अचिन्हित दीर्घ	 समयleft;
	अचिन्हित दीर्घ	 flags;

	/* करोn't send पूर्णांकernal command during diag reset */
	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress) अणु
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"%s: busy with host reset\n", ioc->name, __func__));
		वापस MPT_SCANDV_BUSY;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);

	mutex_lock(&ioc->पूर्णांकernal_cmds.mutex);

	/* Set command specअगरic inक्रमmation
	 */
	चयन (cmd) अणु
	हाल INQUIRY:
		cmdLen = 6;
		dir = MPI_SCSIIO_CONTROL_READ;
		CDB[0] = cmd;
		CDB[4] = io->size;
		समयout = 10;
		अवरोध;

	हाल TEST_UNIT_READY:
		cmdLen = 6;
		dir = MPI_SCSIIO_CONTROL_READ;
		समयout = 10;
		अवरोध;

	हाल START_STOP:
		cmdLen = 6;
		dir = MPI_SCSIIO_CONTROL_READ;
		CDB[0] = cmd;
		CDB[4] = 1;	/*Spin up the disk */
		समयout = 15;
		अवरोध;

	हाल REQUEST_SENSE:
		cmdLen = 6;
		CDB[0] = cmd;
		CDB[4] = io->size;
		dir = MPI_SCSIIO_CONTROL_READ;
		समयout = 10;
		अवरोध;

	हाल READ_BUFFER:
		cmdLen = 10;
		dir = MPI_SCSIIO_CONTROL_READ;
		CDB[0] = cmd;
		अगर (io->flags & MPT_ICFLAG_ECHO) अणु
			CDB[1] = 0x0A;
		पूर्ण अन्यथा अणु
			CDB[1] = 0x02;
		पूर्ण

		अगर (io->flags & MPT_ICFLAG_BUF_CAP) अणु
			CDB[1] |= 0x01;
		पूर्ण
		CDB[6] = (io->size >> 16) & 0xFF;
		CDB[7] = (io->size >>  8) & 0xFF;
		CDB[8] = io->size & 0xFF;
		समयout = 10;
		अवरोध;

	हाल WRITE_BUFFER:
		cmdLen = 10;
		dir = MPI_SCSIIO_CONTROL_WRITE;
		CDB[0] = cmd;
		अगर (io->flags & MPT_ICFLAG_ECHO) अणु
			CDB[1] = 0x0A;
		पूर्ण अन्यथा अणु
			CDB[1] = 0x02;
		पूर्ण
		CDB[6] = (io->size >> 16) & 0xFF;
		CDB[7] = (io->size >>  8) & 0xFF;
		CDB[8] = io->size & 0xFF;
		समयout = 10;
		अवरोध;

	हाल RESERVE:
		cmdLen = 6;
		dir = MPI_SCSIIO_CONTROL_READ;
		CDB[0] = cmd;
		समयout = 10;
		अवरोध;

	हाल RELEASE:
		cmdLen = 6;
		dir = MPI_SCSIIO_CONTROL_READ;
		CDB[0] = cmd;
		समयout = 10;
		अवरोध;

	हाल SYNCHRONIZE_CACHE:
		cmdLen = 10;
		dir = MPI_SCSIIO_CONTROL_READ;
		CDB[0] = cmd;
//		CDB[1] = 0x02;	/* set immediate bit */
		समयout = 10;
		अवरोध;

	शेष:
		/* Error Case */
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/* Get and Populate a मुक्त Frame
	 * MsgContext set in mpt_get_msg_frame call
	 */
	अगर ((mf = mpt_get_msg_frame(ioc->InternalCtx, ioc)) == शून्य) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT "%s: No msg frames!\n",
		    ioc->name, __func__));
		ret = MPT_SCANDV_BUSY;
		जाओ out;
	पूर्ण

	pScsiReq = (SCSIIORequest_t *) mf;

	/* Get the request index */
	my_idx = le16_to_cpu(mf->u.frame.hwhdr.msgctxu.fld.req_idx);
	ADD_INDEX_LOG(my_idx); /* क्रम debug */

	अगर (io->flags & MPT_ICFLAG_PHYS_DISK) अणु
		pScsiReq->TargetID = io->physDiskNum;
		pScsiReq->Bus = 0;
		pScsiReq->ChainOffset = 0;
		pScsiReq->Function = MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH;
	पूर्ण अन्यथा अणु
		pScsiReq->TargetID = io->id;
		pScsiReq->Bus = io->channel;
		pScsiReq->ChainOffset = 0;
		pScsiReq->Function = MPI_FUNCTION_SCSI_IO_REQUEST;
	पूर्ण

	pScsiReq->CDBLength = cmdLen;
	pScsiReq->SenseBufferLength = MPT_SENSE_BUFFER_SIZE;

	pScsiReq->Reserved = 0;

	pScsiReq->MsgFlags = mpt_msg_flags(ioc);
	/* MsgContext set in mpt_get_msg_fram call  */

	पूर्णांक_to_scsilun(io->lun, (काष्ठा scsi_lun *)pScsiReq->LUN);

	अगर (io->flags & MPT_ICFLAG_TAGGED_CMD)
		pScsiReq->Control = cpu_to_le32(dir | MPI_SCSIIO_CONTROL_SIMPLEQ);
	अन्यथा
		pScsiReq->Control = cpu_to_le32(dir | MPI_SCSIIO_CONTROL_UNTAGGED);

	अगर (cmd == REQUEST_SENSE) अणु
		pScsiReq->Control = cpu_to_le32(dir | MPI_SCSIIO_CONTROL_UNTAGGED);
		devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: Untagged! 0x%02x\n", ioc->name, __func__, cmd));
	पूर्ण

	क्रम (ii = 0; ii < 16; ii++)
		pScsiReq->CDB[ii] = CDB[ii];

	pScsiReq->DataLength = cpu_to_le32(io->size);
	pScsiReq->SenseBufferLowAddr = cpu_to_le32(ioc->sense_buf_low_dma
					   + (my_idx * MPT_SENSE_BUFFER_ALLOC));

	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "%s: Sending Command 0x%02x for fw_channel=%d fw_id=%d lun=%llu\n",
	    ioc->name, __func__, cmd, io->channel, io->id, io->lun));

	अगर (dir == MPI_SCSIIO_CONTROL_READ)
		ioc->add_sge((अक्षर *) &pScsiReq->SGL,
		    MPT_SGE_FLAGS_SSIMPLE_READ | io->size, io->data_dma);
	अन्यथा
		ioc->add_sge((अक्षर *) &pScsiReq->SGL,
		    MPT_SGE_FLAGS_SSIMPLE_WRITE | io->size, io->data_dma);

	INITIALIZE_MGMT_STATUS(ioc->पूर्णांकernal_cmds.status)
	mpt_put_msg_frame(ioc->InternalCtx, ioc, mf);
	समयleft = रुको_क्रम_completion_समयout(&ioc->पूर्णांकernal_cmds.करोne,
	    समयout*HZ);
	अगर (!(ioc->पूर्णांकernal_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		ret = MPT_SCANDV_DID_RESET;
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: TIMED OUT for cmd=0x%02x\n", ioc->name, __func__,
		    cmd));
		अगर (ioc->पूर्णांकernal_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET) अणु
			mpt_मुक्त_msg_frame(ioc, mf);
			जाओ out;
		पूर्ण
		अगर (!समयleft) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
			       "Issuing Reset from %s!! doorbell=0x%08xh"
			       " cmd=0x%02x\n",
			       ioc->name, __func__, mpt_GetIocState(ioc, 0),
			       cmd);
			mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
			mpt_मुक्त_msg_frame(ioc, mf);
		पूर्ण
		जाओ out;
	पूर्ण

	ret = ioc->पूर्णांकernal_cmds.completion_code;
	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s: success, rc=0x%02x\n",
			ioc->name, __func__, ret));

 out:
	CLEAR_MGMT_STATUS(ioc->पूर्णांकernal_cmds.status)
	mutex_unlock(&ioc->पूर्णांकernal_cmds.mutex);
	वापस ret;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptscsih_synchronize_cache - Send SYNCHRONIZE_CACHE to all disks.
 *	@hd: Poपूर्णांकer to a SCSI HOST काष्ठाure
 *	@vdevice: भव target device
 *
 *	Uses the ISR, but with special processing.
 *	MUST be single-thपढ़ोed.
 *
 */
अटल व्योम
mptscsih_synchronize_cache(MPT_SCSI_HOST *hd, VirtDevice *vdevice)
अणु
	INTERNAL_CMD		 iocmd;

	/* Ignore hidden raid components, this is handled when the command
	 * is sent to the volume
	 */
	अगर (vdevice->vtarget->tflags & MPT_TARGET_FLAGS_RAID_COMPONENT)
		वापस;

	अगर (vdevice->vtarget->type != TYPE_DISK || vdevice->vtarget->deleted ||
	    !vdevice->configured_lun)
		वापस;

	/* Following parameters will not change
	 * in this routine.
	 */
	iocmd.cmd = SYNCHRONIZE_CACHE;
	iocmd.flags = 0;
	iocmd.physDiskNum = -1;
	iocmd.data = शून्य;
	iocmd.data_dma = -1;
	iocmd.size = 0;
	iocmd.rsvd = iocmd.rsvd2 = 0;
	iocmd.channel = vdevice->vtarget->channel;
	iocmd.id = vdevice->vtarget->id;
	iocmd.lun = vdevice->lun;

	mptscsih_करो_cmd(hd, &iocmd);
पूर्ण

अटल sमाप_प्रकार
mptscsih_version_fw_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%02d.%02d.%02d.%02d\n",
	    (ioc->facts.FWVersion.Word & 0xFF000000) >> 24,
	    (ioc->facts.FWVersion.Word & 0x00FF0000) >> 16,
	    (ioc->facts.FWVersion.Word & 0x0000FF00) >> 8,
	    ioc->facts.FWVersion.Word & 0x000000FF);
पूर्ण
अटल DEVICE_ATTR(version_fw, S_IRUGO, mptscsih_version_fw_show, शून्य);

अटल sमाप_प्रकार
mptscsih_version_bios_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%02x.%02x.%02x.%02x\n",
	    (ioc->biosVersion & 0xFF000000) >> 24,
	    (ioc->biosVersion & 0x00FF0000) >> 16,
	    (ioc->biosVersion & 0x0000FF00) >> 8,
	    ioc->biosVersion & 0x000000FF);
पूर्ण
अटल DEVICE_ATTR(version_bios, S_IRUGO, mptscsih_version_bios_show, शून्य);

अटल sमाप_प्रकार
mptscsih_version_mpi_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%03x\n", ioc->facts.MsgVersion);
पूर्ण
अटल DEVICE_ATTR(version_mpi, S_IRUGO, mptscsih_version_mpi_show, शून्य);

अटल sमाप_प्रकार
mptscsih_version_product_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ioc->prod_name);
पूर्ण
अटल DEVICE_ATTR(version_product, S_IRUGO,
    mptscsih_version_product_show, शून्य);

अटल sमाप_प्रकार
mptscsih_version_nvdata_persistent_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%02xh\n",
	    ioc->nvdata_version_persistent);
पूर्ण
अटल DEVICE_ATTR(version_nvdata_persistent, S_IRUGO,
    mptscsih_version_nvdata_persistent_show, शून्य);

अटल sमाप_प्रकार
mptscsih_version_nvdata_शेष_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%02xh\n",ioc->nvdata_version_शेष);
पूर्ण
अटल DEVICE_ATTR(version_nvdata_शेष, S_IRUGO,
    mptscsih_version_nvdata_शेष_show, शून्य);

अटल sमाप_प्रकार
mptscsih_board_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ioc->board_name);
पूर्ण
अटल DEVICE_ATTR(board_name, S_IRUGO, mptscsih_board_name_show, शून्य);

अटल sमाप_प्रकार
mptscsih_board_assembly_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ioc->board_assembly);
पूर्ण
अटल DEVICE_ATTR(board_assembly, S_IRUGO,
    mptscsih_board_assembly_show, शून्य);

अटल sमाप_प्रकार
mptscsih_board_tracer_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", ioc->board_tracer);
पूर्ण
अटल DEVICE_ATTR(board_tracer, S_IRUGO,
    mptscsih_board_tracer_show, शून्य);

अटल sमाप_प्रकार
mptscsih_io_delay_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%02d\n", ioc->io_missing_delay);
पूर्ण
अटल DEVICE_ATTR(io_delay, S_IRUGO,
    mptscsih_io_delay_show, शून्य);

अटल sमाप_प्रकार
mptscsih_device_delay_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%02d\n", ioc->device_missing_delay);
पूर्ण
अटल DEVICE_ATTR(device_delay, S_IRUGO,
    mptscsih_device_delay_show, शून्य);

अटल sमाप_प्रकार
mptscsih_debug_level_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;

	वापस snम_लिखो(buf, PAGE_SIZE, "%08xh\n", ioc->debug_level);
पूर्ण
अटल sमाप_प्रकार
mptscsih_debug_level_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER *ioc = hd->ioc;
	पूर्णांक val = 0;

	अगर (माला_पूछो(buf, "%x", &val) != 1)
		वापस -EINVAL;

	ioc->debug_level = val;
	prपूर्णांकk(MYIOC_s_INFO_FMT "debug_level=%08xh\n",
				ioc->name, ioc->debug_level);
	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR(debug_level, S_IRUGO | S_IWUSR,
	mptscsih_debug_level_show, mptscsih_debug_level_store);

काष्ठा device_attribute *mptscsih_host_attrs[] = अणु
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
	&dev_attr_debug_level,
	शून्य,
पूर्ण;

EXPORT_SYMBOL(mptscsih_host_attrs);

EXPORT_SYMBOL(mptscsih_हटाओ);
EXPORT_SYMBOL(mptscsih_shutकरोwn);
#अगर_घोषित CONFIG_PM
EXPORT_SYMBOL(mptscsih_suspend);
EXPORT_SYMBOL(mptscsih_resume);
#पूर्ण_अगर
EXPORT_SYMBOL(mptscsih_show_info);
EXPORT_SYMBOL(mptscsih_info);
EXPORT_SYMBOL(mptscsih_qcmd);
EXPORT_SYMBOL(mptscsih_slave_destroy);
EXPORT_SYMBOL(mptscsih_slave_configure);
EXPORT_SYMBOL(mptscsih_पात);
EXPORT_SYMBOL(mptscsih_dev_reset);
EXPORT_SYMBOL(mptscsih_bus_reset);
EXPORT_SYMBOL(mptscsih_host_reset);
EXPORT_SYMBOL(mptscsih_bios_param);
EXPORT_SYMBOL(mptscsih_io_करोne);
EXPORT_SYMBOL(mptscsih_taskmgmt_complete);
EXPORT_SYMBOL(mptscsih_scandv_complete);
EXPORT_SYMBOL(mptscsih_event_process);
EXPORT_SYMBOL(mptscsih_ioc_reset);
EXPORT_SYMBOL(mptscsih_change_queue_depth);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
