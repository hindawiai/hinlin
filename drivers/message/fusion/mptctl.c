<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptctl.c
 *      mpt Ioctl driver.
 *      For use with LSI PCI chip/adapters
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>	/* क्रम mdelay */
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/compat.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>

#घोषणा COPYRIGHT	"Copyright (c) 1999-2008 LSI Corporation"
#घोषणा MODULEAUTHOR	"LSI Corporation"
#समावेश "mptbase.h"
#समावेश "mptctl.h"

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#घोषणा my_NAME		"Fusion MPT misc device (ioctl) driver"
#घोषणा my_VERSION	MPT_LINUX_VERSION_COMMON
#घोषणा MYNAM		"mptctl"

MODULE_AUTHOR(MODULEAUTHOR);
MODULE_DESCRIPTION(my_NAME);
MODULE_LICENSE("GPL");
MODULE_VERSION(my_VERSION);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

अटल DEFINE_MUTEX(mpctl_mutex);
अटल u8 mptctl_id = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8 mptctl_taskmgmt_id = MPT_MAX_PROTOCOL_DRIVERS;

अटल DECLARE_WAIT_QUEUE_HEAD ( mptctl_रुको );

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

काष्ठा buflist अणु
	u8	*kptr;
	पूर्णांक	 len;
पूर्ण;

/*
 * Function prototypes. Called from OS entry poपूर्णांक mptctl_ioctl.
 * arg contents specअगरic to function.
 */
अटल पूर्णांक mptctl_fw_करोwnload(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);
अटल पूर्णांक mptctl_getiocinfo(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg, अचिन्हित पूर्णांक cmd);
अटल पूर्णांक mptctl_gettargetinfo(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);
अटल पूर्णांक mptctl_पढ़ोtest(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);
अटल पूर्णांक mptctl_mpt_command(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);
अटल पूर्णांक mptctl_eventquery(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);
अटल पूर्णांक mptctl_eventenable(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);
अटल पूर्णांक mptctl_eventreport(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);
अटल पूर्णांक mptctl_replace_fw(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);

अटल पूर्णांक mptctl_करो_reset(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);
अटल पूर्णांक mptctl_hp_hostinfo(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg, अचिन्हित पूर्णांक cmd);
अटल पूर्णांक mptctl_hp_targetinfo(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg);

अटल पूर्णांक  mptctl_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम mptctl_हटाओ(काष्ठा pci_dev *);

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ compat_mpctl_ioctl(काष्ठा file *f, अचिन्हित cmd, अचिन्हित दीर्घ arg);
#पूर्ण_अगर
/*
 * Private function calls.
 */
अटल पूर्णांक mptctl_करो_mpt_command(MPT_ADAPTER *iocp, काष्ठा mpt_ioctl_command karg, व्योम __user *mfPtr);
अटल पूर्णांक mptctl_करो_fw_करोwnload(MPT_ADAPTER *iocp, अक्षर __user *ufwbuf, माप_प्रकार fwlen);
अटल MptSge_t *kbuf_alloc_2_sgl(पूर्णांक bytes, u32 dir, पूर्णांक sge_offset, पूर्णांक *frags,
		काष्ठा buflist **blp, dma_addr_t *sglbuf_dma, MPT_ADAPTER *ioc);
अटल व्योम kमुक्त_sgl(MptSge_t *sgl, dma_addr_t sgl_dma,
		काष्ठा buflist *buflist, MPT_ADAPTER *ioc);

/*
 * Reset Handler cleanup function
 */
अटल पूर्णांक  mptctl_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase);

/*
 * Event Handler function
 */
अटल पूर्णांक mptctl_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply);
अटल काष्ठा fasync_काष्ठा *async_queue=शून्य;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * Scatter gather list (SGL) sizes and limits...
 */
//#घोषणा MAX_SCSI_FRAGS	9
#घोषणा MAX_FRAGS_SPILL1	9
#घोषणा MAX_FRAGS_SPILL2	15
#घोषणा FRAGS_PER_BUCKET	(MAX_FRAGS_SPILL2 + 1)

//#घोषणा MAX_CHAIN_FRAGS	64
//#घोषणा MAX_CHAIN_FRAGS	(15+15+15+16)
#घोषणा MAX_CHAIN_FRAGS		(4 * MAX_FRAGS_SPILL2 + 1)

//  Define max sg LIST bytes ( == (#frags + #chains) * 8 bytes each)
//  Works out to: 592d bytes!     (9+1)*8 + 4*(15+1)*8
//                  ^----------------- 80 + 512
#घोषणा MAX_SGL_BYTES		((MAX_FRAGS_SPILL1 + 1 + (4 * FRAGS_PER_BUCKET)) * 8)

/* linux only seems to ever give 128kB MAX contiguous (GFP_USER) mem bytes */
#घोषणा MAX_KMALLOC_SZ		(128*1024)

#घोषणा MPT_IOCTL_DEFAULT_TIMEOUT 10	/* Default समयout value (seconds) */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptctl_syscall_करोwn - Down the MPT adapter syscall semaphore.
 *	@ioc: Poपूर्णांकer to MPT adapter
 *	@nonblock: boolean, non-zero अगर O_NONBLOCK is set
 *
 *	All of the ioctl commands can potentially sleep, which is illegal
 *	with a spinlock held, thus we perक्रमm mutual exclusion here.
 *
 *	Returns negative त्रुटि_सं on error, or zero क्रम success.
 */
अटल अंतरभूत पूर्णांक
mptctl_syscall_करोwn(MPT_ADAPTER *ioc, पूर्णांक nonblock)
अणु
	पूर्णांक rc = 0;

	अगर (nonblock) अणु
		अगर (!mutex_trylock(&ioc->ioctl_cmds.mutex))
			rc = -EAGAIN;
	पूर्ण अन्यथा अणु
		अगर (mutex_lock_पूर्णांकerruptible(&ioc->ioctl_cmds.mutex))
			rc = -ERESTARTSYS;
	पूर्ण
	वापस rc;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  This is the callback क्रम any message we have posted. The message itself
 *  will be वापसed to the message pool when we वापस from the IRQ
 *
 *  This runs in irq context so be लघु and sweet.
 */
अटल पूर्णांक
mptctl_reply(MPT_ADAPTER *ioc, MPT_FRAME_HDR *req, MPT_FRAME_HDR *reply)
अणु
	अक्षर	*sense_data;
	पूर्णांक	req_index;
	पूर्णांक	sz;

	अगर (!req)
		वापस 0;

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "completing mpi function "
	    "(0x%02X), req=%p, reply=%p\n", ioc->name,  req->u.hdr.Function,
	    req, reply));

	/*
	 * Handling continuation of the same reply. Processing the first
	 * reply, and eating the other replys that come later.
	 */
	अगर (ioc->ioctl_cmds.msg_context != req->u.hdr.MsgContext)
		जाओ out_continuation;

	ioc->ioctl_cmds.status |= MPT_MGMT_STATUS_COMMAND_GOOD;

	अगर (!reply)
		जाओ out;

	ioc->ioctl_cmds.status |= MPT_MGMT_STATUS_RF_VALID;
	sz = min(ioc->reply_sz, 4*reply->u.reply.MsgLength);
	स_नकल(ioc->ioctl_cmds.reply, reply, sz);

	अगर (reply->u.reply.IOCStatus || reply->u.reply.IOCLogInfo)
		dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "iocstatus (0x%04X), loginfo (0x%08X)\n", ioc->name,
		    le16_to_cpu(reply->u.reply.IOCStatus),
		    le32_to_cpu(reply->u.reply.IOCLogInfo)));

	अगर ((req->u.hdr.Function == MPI_FUNCTION_SCSI_IO_REQUEST) ||
		(req->u.hdr.Function ==
		 MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH)) अणु

		अगर (reply->u.sreply.SCSIStatus || reply->u.sreply.SCSIState)
			dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"scsi_status (0x%02x), scsi_state (0x%02x), "
			"tag = (0x%04x), transfer_count (0x%08x)\n", ioc->name,
			reply->u.sreply.SCSIStatus,
			reply->u.sreply.SCSIState,
			le16_to_cpu(reply->u.sreply.TaskTag),
			le32_to_cpu(reply->u.sreply.TransferCount)));

		अगर (reply->u.sreply.SCSIState &
			MPI_SCSI_STATE_AUTOSENSE_VALID) अणु
			sz = req->u.scsireq.SenseBufferLength;
			req_index =
			    le16_to_cpu(req->u.frame.hwhdr.msgctxu.fld.req_idx);
			sense_data = ((u8 *)ioc->sense_buf_pool +
			     (req_index * MPT_SENSE_BUFFER_ALLOC));
			स_नकल(ioc->ioctl_cmds.sense, sense_data, sz);
			ioc->ioctl_cmds.status |= MPT_MGMT_STATUS_SENSE_VALID;
		पूर्ण
	पूर्ण

 out:
	/* We are करोne, issue wake up
	 */
	अगर (ioc->ioctl_cmds.status & MPT_MGMT_STATUS_PENDING) अणु
		अगर (req->u.hdr.Function == MPI_FUNCTION_SCSI_TASK_MGMT) अणु
			mpt_clear_taskmgmt_in_progress_flag(ioc);
			ioc->ioctl_cmds.status &= ~MPT_MGMT_STATUS_PENDING;
			complete(&ioc->ioctl_cmds.करोne);
			अगर (ioc->bus_type == SAS)
				ioc->schedule_target_reset(ioc);
		पूर्ण अन्यथा अणु
			ioc->ioctl_cmds.status &= ~MPT_MGMT_STATUS_PENDING;
			complete(&ioc->ioctl_cmds.करोne);
		पूर्ण
	पूर्ण

 out_continuation:
	अगर (reply && (reply->u.reply.MsgFlags &
	    MPI_MSGFLAGS_CONTINUATION_REPLY))
		वापस 0;
	वापस 1;
पूर्ण


अटल पूर्णांक
mptctl_taskmgmt_reply(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *mr)
अणु
	अगर (!mf)
		वापस 0;

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"TaskMgmt completed (mf=%p, mr=%p)\n",
		ioc->name, mf, mr));

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

अटल पूर्णांक
mptctl_करो_taskmgmt(MPT_ADAPTER *ioc, u8 पंचांग_type, u8 bus_id, u8 target_id)
अणु
	MPT_FRAME_HDR	*mf;
	SCSITaskMgmt_t	*pScsiTm;
	SCSITaskMgmtReply_t *pScsiTmReply;
	पूर्णांक		 ii;
	पूर्णांक		 retval;
	अचिन्हित दीर्घ	 समयout;
	u16		 iocstatus;


	mutex_lock(&ioc->taskmgmt_cmds.mutex);
	अगर (mpt_set_taskmgmt_in_progress_flag(ioc) != 0) अणु
		mutex_unlock(&ioc->taskmgmt_cmds.mutex);
		वापस -EPERM;
	पूर्ण

	retval = 0;

	mf = mpt_get_msg_frame(mptctl_taskmgmt_id, ioc);
	अगर (mf == शून्य) अणु
		dपंचांगprपूर्णांकk(ioc,
			prपूर्णांकk(MYIOC_s_WARN_FMT "TaskMgmt, no msg frames!!\n",
			ioc->name));
		mpt_clear_taskmgmt_in_progress_flag(ioc);
		retval = -ENOMEM;
		जाओ पंचांग_करोne;
	पूर्ण

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "TaskMgmt request (mf=%p)\n",
		ioc->name, mf));

	pScsiTm = (SCSITaskMgmt_t *) mf;
	स_रखो(pScsiTm, 0, माप(SCSITaskMgmt_t));
	pScsiTm->Function = MPI_FUNCTION_SCSI_TASK_MGMT;
	pScsiTm->TaskType = पंचांग_type;
	अगर ((पंचांग_type == MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS) &&
		(ioc->bus_type == FC))
		pScsiTm->MsgFlags =
				MPI_SCSITASKMGMT_MSGFLAGS_LIPRESET_RESET_OPTION;
	pScsiTm->TargetID = target_id;
	pScsiTm->Bus = bus_id;
	pScsiTm->ChainOffset = 0;
	pScsiTm->Reserved = 0;
	pScsiTm->Reserved1 = 0;
	pScsiTm->TaskMsgContext = 0;
	क्रम (ii= 0; ii < 8; ii++)
		pScsiTm->LUN[ii] = 0;
	क्रम (ii=0; ii < 7; ii++)
		pScsiTm->Reserved2[ii] = 0;

	चयन (ioc->bus_type) अणु
	हाल FC:
		समयout = 40;
		अवरोध;
	हाल SAS:
		समयout = 30;
		अवरोध;
	हाल SPI:
		शेष:
		समयout = 10;
		अवरोध;
	पूर्ण

	dपंचांगprपूर्णांकk(ioc,
		prपूर्णांकk(MYIOC_s_DEBUG_FMT "TaskMgmt type=%d timeout=%ld\n",
		ioc->name, पंचांग_type, समयout));

	INITIALIZE_MGMT_STATUS(ioc->taskmgmt_cmds.status)
	अगर ((ioc->facts.IOCCapabilities & MPI_IOCFACTS_CAPABILITY_HIGH_PRI_Q) &&
	    (ioc->facts.MsgVersion >= MPI_VERSION_01_05))
		mpt_put_msg_frame_hi_pri(mptctl_taskmgmt_id, ioc, mf);
	अन्यथा अणु
		retval = mpt_send_handshake_request(mptctl_taskmgmt_id, ioc,
		    माप(SCSITaskMgmt_t), (u32 *)pScsiTm, CAN_SLEEP);
		अगर (retval != 0) अणु
			dfailprपूर्णांकk(ioc,
				prपूर्णांकk(MYIOC_s_ERR_FMT
				"TaskMgmt send_handshake FAILED!"
				" (ioc %p, mf %p, rc=%d) \n", ioc->name,
				ioc, mf, retval));
			mpt_मुक्त_msg_frame(ioc, mf);
			mpt_clear_taskmgmt_in_progress_flag(ioc);
			जाओ पंचांग_करोne;
		पूर्ण
	पूर्ण

	/* Now रुको क्रम the command to complete */
	ii = रुको_क्रम_completion_समयout(&ioc->taskmgmt_cmds.करोne, समयout*HZ);

	अगर (!(ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "TaskMgmt failed\n", ioc->name));
		mpt_मुक्त_msg_frame(ioc, mf);
		mpt_clear_taskmgmt_in_progress_flag(ioc);
		अगर (ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET)
			retval = 0;
		अन्यथा
			retval = -1; /* वापस failure */
		जाओ पंचांग_करोne;
	पूर्ण

	अगर (!(ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_RF_VALID)) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "TaskMgmt failed\n", ioc->name));
		retval = -1; /* वापस failure */
		जाओ पंचांग_करोne;
	पूर्ण

	pScsiTmReply = (SCSITaskMgmtReply_t *) ioc->taskmgmt_cmds.reply;
	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "TaskMgmt fw_channel = %d, fw_id = %d, task_type=0x%02X, "
	    "iocstatus=0x%04X\n\tloginfo=0x%08X, response_code=0x%02X, "
	    "term_cmnds=%d\n", ioc->name, pScsiTmReply->Bus,
	    pScsiTmReply->TargetID, पंचांग_type,
	    le16_to_cpu(pScsiTmReply->IOCStatus),
	    le32_to_cpu(pScsiTmReply->IOCLogInfo),
	    pScsiTmReply->ResponseCode,
	    le32_to_cpu(pScsiTmReply->TerminationCount)));

	iocstatus = le16_to_cpu(pScsiTmReply->IOCStatus) & MPI_IOCSTATUS_MASK;

	अगर (iocstatus == MPI_IOCSTATUS_SCSI_TASK_TERMINATED ||
	   iocstatus == MPI_IOCSTATUS_SCSI_IOC_TERMINATED ||
	   iocstatus == MPI_IOCSTATUS_SUCCESS)
		retval = 0;
	अन्यथा अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "TaskMgmt failed\n", ioc->name));
		retval = -1; /* वापस failure */
	पूर्ण

 पंचांग_करोne:
	mutex_unlock(&ioc->taskmgmt_cmds.mutex);
	CLEAR_MGMT_STATUS(ioc->taskmgmt_cmds.status)
	वापस retval;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* mptctl_समयout_expired
 *
 * Expecting an पूर्णांकerrupt, however समयd out.
 *
 */
अटल व्योम
mptctl_समयout_expired(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret_val = -1;
	SCSIIORequest_t *scsi_req = (SCSIIORequest_t *) mf;
	u8 function = mf->u.hdr.Function;

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT ": %s\n",
		ioc->name, __func__));

	अगर (mpt_fwfault_debug)
		mpt_halt_firmware(ioc);

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress) अणु
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		CLEAR_MGMT_PENDING_STATUS(ioc->ioctl_cmds.status)
		mpt_मुक्त_msg_frame(ioc, mf);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);


	CLEAR_MGMT_PENDING_STATUS(ioc->ioctl_cmds.status)

	अगर (ioc->bus_type == SAS) अणु
		अगर (function == MPI_FUNCTION_SCSI_IO_REQUEST)
			ret_val = mptctl_करो_taskmgmt(ioc,
				MPI_SCSITASKMGMT_TASKTYPE_TARGET_RESET,
				scsi_req->Bus, scsi_req->TargetID);
		अन्यथा अगर (function == MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH)
			ret_val = mptctl_करो_taskmgmt(ioc,
				MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS,
				scsi_req->Bus, 0);
		अगर (!ret_val)
			वापस;
	पूर्ण अन्यथा अणु
		अगर ((function == MPI_FUNCTION_SCSI_IO_REQUEST) ||
			(function == MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH))
			ret_val = mptctl_करो_taskmgmt(ioc,
				MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS,
				scsi_req->Bus, 0);
		अगर (!ret_val)
			वापस;
	पूर्ण

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Calling Reset! \n",
		 ioc->name));
	mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
	mpt_मुक्त_msg_frame(ioc, mf);
पूर्ण


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* mptctl_ioc_reset
 *
 * Clean-up functionality. Used only अगर there has been a
 * reload of the FW due.
 *
 */
अटल पूर्णांक
mptctl_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase)
अणु
	चयन(reset_phase) अणु
	हाल MPT_IOC_SETUP_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_SETUP_RESET\n", ioc->name, __func__));
		अवरोध;
	हाल MPT_IOC_PRE_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_PRE_RESET\n", ioc->name, __func__));
		अवरोध;
	हाल MPT_IOC_POST_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_POST_RESET\n", ioc->name, __func__));
		अगर (ioc->ioctl_cmds.status & MPT_MGMT_STATUS_PENDING) अणु
			ioc->ioctl_cmds.status |= MPT_MGMT_STATUS_DID_IOCRESET;
			complete(&ioc->ioctl_cmds.करोne);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* ASYNC Event Notअगरication Support */
अटल पूर्णांक
mptctl_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply)
अणु
	u8 event;

	event = le32_to_cpu(pEvReply->Event) & 0xFF;

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s() called\n",
	    ioc->name, __func__));
	अगर(async_queue == शून्य)
		वापस 1;

	/* Raise SIGIO क्रम persistent events.
	 * TODO - this define is not in MPI spec yet,
	 * but they plan to set it to 0x21
	 */
	अगर (event == 0x21) अणु
		ioc->aen_event_पढ़ो_flag=1;
		dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Raised SIGIO to application\n",
		    ioc->name));
		devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "Raised SIGIO to application\n", ioc->name));
		समाप्त_fasync(&async_queue, SIGIO, POLL_IN);
		वापस 1;
	 पूर्ण

	/* This flag is set after SIGIO was उठाओd, and
	 * reमुख्यs set until the application has पढ़ो
	 * the event log via ioctl=MPTEVENTREPORT
	 */
	अगर(ioc->aen_event_पढ़ो_flag)
		वापस 1;

	/* Signal only क्रम the events that are
	 * requested क्रम by the application
	 */
	अगर (ioc->events && (ioc->eventTypes & ( 1 << event))) अणु
		ioc->aen_event_पढ़ो_flag=1;
		dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "Raised SIGIO to application\n", ioc->name));
		devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "Raised SIGIO to application\n", ioc->name));
		समाप्त_fasync(&async_queue, SIGIO, POLL_IN);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक
mptctl_fasync(पूर्णांक fd, काष्ठा file *filep, पूर्णांक mode)
अणु
	MPT_ADAPTER	*ioc;
	पूर्णांक ret;

	mutex_lock(&mpctl_mutex);
	list_क्रम_each_entry(ioc, &ioc_list, list)
		ioc->aen_event_पढ़ो_flag=0;

	ret = fasync_helper(fd, filep, mode, &async_queue);
	mutex_unlock(&mpctl_mutex);
	वापस ret;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  MPT ioctl handler
 *  cmd - specअगरy the particular IOCTL command to be issued
 *  arg - data specअगरic to the command. Must not be null.
 */
अटल दीर्घ
__mptctl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	mpt_ioctl_header __user *uhdr = (व्योम __user *) arg;
	mpt_ioctl_header	 khdr;
	पूर्णांक iocnum;
	अचिन्हित iocnumX;
	पूर्णांक nonblock = (file->f_flags & O_NONBLOCK);
	पूर्णांक ret;
	MPT_ADAPTER *iocp = शून्य;

	अगर (copy_from_user(&khdr, uhdr, माप(khdr))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s::mptctl_ioctl() @%d - "
				"Unable to copy mpt_ioctl_header data @ %p\n",
				__खाता__, __LINE__, uhdr);
		वापस -EFAULT;
	पूर्ण
	ret = -ENXIO;				/* (-6) No such device or address */

	/* Verअगरy पूर्णांकended MPT adapter - set iocnum and the adapter
	 * poपूर्णांकer (iocp)
	 */
	iocnumX = khdr.iocnum & 0xFF;
	अगर (((iocnum = mpt_verअगरy_adapter(iocnumX, &iocp)) < 0) ||
	    (iocp == शून्य))
		वापस -ENODEV;

	अगर (!iocp->active) अणु
		prपूर्णांकk(KERN_DEBUG MYNAM "%s::mptctl_ioctl() @%d - Controller disabled.\n",
				__खाता__, __LINE__);
		वापस -EFAULT;
	पूर्ण

	/* Handle those commands that are just वापसing
	 * inक्रमmation stored in the driver.
	 * These commands should never समय out and are unaffected
	 * by TM and FW reloads.
	 */
	अगर ((cmd & ~IOCSIZE_MASK) == (MPTIOCINFO & ~IOCSIZE_MASK)) अणु
		वापस mptctl_getiocinfo(iocp, arg, _IOC_SIZE(cmd));
	पूर्ण अन्यथा अगर (cmd == MPTTARGETINFO) अणु
		वापस mptctl_gettargetinfo(iocp, arg);
	पूर्ण अन्यथा अगर (cmd == MPTTEST) अणु
		वापस mptctl_पढ़ोtest(iocp, arg);
	पूर्ण अन्यथा अगर (cmd == MPTEVENTQUERY) अणु
		वापस mptctl_eventquery(iocp, arg);
	पूर्ण अन्यथा अगर (cmd == MPTEVENTENABLE) अणु
		वापस mptctl_eventenable(iocp, arg);
	पूर्ण अन्यथा अगर (cmd == MPTEVENTREPORT) अणु
		वापस mptctl_eventreport(iocp, arg);
	पूर्ण अन्यथा अगर (cmd == MPTFWREPLACE) अणु
		वापस mptctl_replace_fw(iocp, arg);
	पूर्ण

	/* All of these commands require an पूर्णांकerrupt or
	 * are unknown/illegal.
	 */
	अगर ((ret = mptctl_syscall_करोwn(iocp, nonblock)) != 0)
		वापस ret;

	अगर (cmd == MPTFWDOWNLOAD)
		ret = mptctl_fw_करोwnload(iocp, arg);
	अन्यथा अगर (cmd == MPTCOMMAND)
		ret = mptctl_mpt_command(iocp, arg);
	अन्यथा अगर (cmd == MPTHARDRESET)
		ret = mptctl_करो_reset(iocp, arg);
	अन्यथा अगर ((cmd & ~IOCSIZE_MASK) == (HP_GETHOSTINFO & ~IOCSIZE_MASK))
		ret = mptctl_hp_hostinfo(iocp, arg, _IOC_SIZE(cmd));
	अन्यथा अगर (cmd == HP_GETTARGETINFO)
		ret = mptctl_hp_targetinfo(iocp, arg);
	अन्यथा
		ret = -EINVAL;

	mutex_unlock(&iocp->ioctl_cmds.mutex);

	वापस ret;
पूर्ण

अटल दीर्घ
mptctl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;
	mutex_lock(&mpctl_mutex);
	ret = __mptctl_ioctl(file, cmd, arg);
	mutex_unlock(&mpctl_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक mptctl_करो_reset(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_diag_reset __user *urinfo = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_diag_reset krinfo;

	अगर (copy_from_user(&krinfo, urinfo, माप(काष्ठा mpt_ioctl_diag_reset))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_do_reset - "
				"Unable to copy mpt_ioctl_diag_reset struct @ %p\n",
				__खाता__, __LINE__, urinfo);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(iocp, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_do_reset called.\n",
	    iocp->name));

	अगर (mpt_HardResetHandler(iocp, CAN_SLEEP) != 0) अणु
		prपूर्णांकk (MYIOC_s_ERR_FMT "%s@%d::mptctl_do_reset - reset failed.\n",
			iocp->name, __खाता__, __LINE__);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * MPT FW करोwnload function.  Cast the arg पूर्णांकo the mpt_fw_xfer काष्ठाure.
 * This काष्ठाure contains: iocnum, firmware length (bytes),
 *      poपूर्णांकer to user space memory where the fw image is stored.
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EFAULT अगर data unavailable
 *		-ENXIO  अगर no such device
 *		-EAGAIN अगर resource problem
 *		-ENOMEM अगर no memory क्रम SGE
 *		-EMLINK अगर too many chain buffers required
 *		-EBADRQC अगर adapter करोes not support FW करोwnload
 *		-EBUSY अगर adapter is busy
 *		-ENOMSG अगर FW upload वापसed bad status
 */
अटल पूर्णांक
mptctl_fw_करोwnload(MPT_ADAPTER *iocp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_fw_xfer __user *ufwdl = (व्योम __user *) arg;
	काष्ठा mpt_fw_xfer	 kfwdl;

	अगर (copy_from_user(&kfwdl, ufwdl, माप(काष्ठा mpt_fw_xfer))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::_ioctl_fwdl - "
				"Unable to copy mpt_fw_xfer struct @ %p\n",
				__खाता__, __LINE__, ufwdl);
		वापस -EFAULT;
	पूर्ण

	वापस mptctl_करो_fw_करोwnload(iocp, kfwdl.bufp, kfwdl.fwlen);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * FW Download engine.
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EFAULT अगर data unavailable
 *		-ENXIO  अगर no such device
 *		-EAGAIN अगर resource problem
 *		-ENOMEM अगर no memory क्रम SGE
 *		-EMLINK अगर too many chain buffers required
 *		-EBADRQC अगर adapter करोes not support FW करोwnload
 *		-EBUSY अगर adapter is busy
 *		-ENOMSG अगर FW upload वापसed bad status
 */
अटल पूर्णांक
mptctl_करो_fw_करोwnload(MPT_ADAPTER *iocp, अक्षर __user *ufwbuf, माप_प्रकार fwlen)
अणु
	FWDownload_t		*dlmsg;
	MPT_FRAME_HDR		*mf;
	FWDownloadTCSGE_t	*ptsge;
	MptSge_t		*sgl, *sgIn;
	अक्षर			*sgOut;
	काष्ठा buflist		*buflist;
	काष्ठा buflist		*bl;
	dma_addr_t		 sgl_dma;
	पूर्णांक			 ret;
	पूर्णांक			 numfrags = 0;
	पूर्णांक			 maxfrags;
	पूर्णांक			 n = 0;
	u32			 sgdir;
	u32			 nib;
	पूर्णांक			 fw_bytes_copied = 0;
	पूर्णांक			 i;
	पूर्णांक			 sge_offset = 0;
	u16			 iocstat;
	pFWDownloadReply_t	 ReplyMsg = शून्य;
	अचिन्हित दीर्घ		 समयleft;

	/*  Valid device. Get a message frame and स्थिरruct the FW करोwnload message.
	*/
	अगर ((mf = mpt_get_msg_frame(mptctl_id, iocp)) == शून्य)
		वापस -EAGAIN;

	dctlprपूर्णांकk(iocp, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "mptctl_do_fwdl called. mptctl_id = %xh.\n", iocp->name, mptctl_id));
	dctlprपूर्णांकk(iocp, prपूर्णांकk(MYIOC_s_DEBUG_FMT "DbG: kfwdl.bufp  = %p\n",
	    iocp->name, ufwbuf));
	dctlprपूर्णांकk(iocp, prपूर्णांकk(MYIOC_s_DEBUG_FMT "DbG: kfwdl.fwlen = %d\n",
	    iocp->name, (पूर्णांक)fwlen));

	dlmsg = (FWDownload_t*) mf;
	ptsge = (FWDownloadTCSGE_t *) &dlmsg->SGL;
	sgOut = (अक्षर *) (ptsge + 1);

	/*
	 * Conकाष्ठा f/w करोwnload request
	 */
	dlmsg->ImageType = MPI_FW_DOWNLOAD_ITYPE_FW;
	dlmsg->Reserved = 0;
	dlmsg->ChainOffset = 0;
	dlmsg->Function = MPI_FUNCTION_FW_DOWNLOAD;
	dlmsg->Reserved1[0] = dlmsg->Reserved1[1] = dlmsg->Reserved1[2] = 0;
	अगर (iocp->facts.MsgVersion >= MPI_VERSION_01_05)
		dlmsg->MsgFlags = MPI_FW_DOWNLOAD_MSGFLGS_LAST_SEGMENT;
	अन्यथा
		dlmsg->MsgFlags = 0;


	/* Set up the Transaction SGE.
	 */
	ptsge->Reserved = 0;
	ptsge->ContextSize = 0;
	ptsge->DetailsLength = 12;
	ptsge->Flags = MPI_SGE_FLAGS_TRANSACTION_ELEMENT;
	ptsge->Reserved_0100_Checksum = 0;
	ptsge->ImageOffset = 0;
	ptsge->ImageSize = cpu_to_le32(fwlen);

	/* Add the SGL
	 */

	/*
	 * Need to kदो_स्मृति area(s) क्रम holding firmware image bytes.
	 * But we need to करो it piece meal, using a proper
	 * scatter gather list (with 128kB MAX hunks).
	 *
	 * A practical limit here might be # of sg hunks that fit पूर्णांकo
	 * a single IOC request frame; 12 or 8 (see below), so:
	 * For FC9xx: 12 x 128kB == 1.5 mB (max)
	 * For C1030:  8 x 128kB == 1   mB (max)
	 * We could support chaining, but things get ugly(ier:)
	 *
	 * Set the sge_offset to the start of the sgl (bytes).
	 */
	sgdir = 0x04000000;		/* IOC will READ from sys mem */
	sge_offset = माप(MPIHeader_t) + माप(FWDownloadTCSGE_t);
	अगर ((sgl = kbuf_alloc_2_sgl(fwlen, sgdir, sge_offset,
				    &numfrags, &buflist, &sgl_dma, iocp)) == शून्य)
		वापस -ENOMEM;

	/*
	 * We should only need SGL with 2 simple_32bit entries (up to 256 kB)
	 * क्रम FC9xx f/w image, but calculate max number of sge hunks
	 * we can fit पूर्णांकo a request frame, and limit ourselves to that.
	 * (currently no chain support)
	 * maxfrags = (Request Size - FWकरोwnload Size ) / Size of 32 bit SGE
	 *	Request		maxfrags
	 *	128		12
	 *	96		8
	 *	64		4
	 */
	maxfrags = (iocp->req_sz - माप(MPIHeader_t) -
			माप(FWDownloadTCSGE_t))
			/ iocp->SGE_size;
	अगर (numfrags > maxfrags) अणु
		ret = -EMLINK;
		जाओ fwdl_out;
	पूर्ण

	dctlprपूर्णांकk(iocp, prपूर्णांकk(MYIOC_s_DEBUG_FMT "DbG: sgl buffer = %p, sgfrags = %d\n",
	    iocp->name, sgl, numfrags));

	/*
	 * Parse SG list, copying sgl itself,
	 * plus f/w image hunks from user space as we go...
	 */
	ret = -EFAULT;
	sgIn = sgl;
	bl = buflist;
	क्रम (i=0; i < numfrags; i++) अणु

		/* Get the SGE type: 0 - TCSGE, 3 - Chain, 1 - Simple SGE
		 * Skip everything but Simple. If simple, copy from
		 *	user space पूर्णांकo kernel space.
		 * Note: we should not have anything but Simple as
		 *	Chain SGE are illegal.
		 */
		nib = (sgIn->FlagsLength & 0x30000000) >> 28;
		अगर (nib == 0 || nib == 3) अणु
			;
		पूर्ण अन्यथा अगर (sgIn->Address) अणु
			iocp->add_sge(sgOut, sgIn->FlagsLength, sgIn->Address);
			n++;
			अगर (copy_from_user(bl->kptr, ufwbuf+fw_bytes_copied, bl->len)) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::_ioctl_fwdl - "
					"Unable to copy f/w buffer hunk#%d @ %p\n",
					iocp->name, __खाता__, __LINE__, n, ufwbuf);
				जाओ fwdl_out;
			पूर्ण
			fw_bytes_copied += bl->len;
		पूर्ण
		sgIn++;
		bl++;
		sgOut += iocp->SGE_size;
	पूर्ण

	DBG_DUMP_FW_DOWNLOAD(iocp, (u32 *)mf, numfrags);

	/*
	 * Finally, perक्रमm firmware करोwnload.
	 */
	ReplyMsg = शून्य;
	SET_MGMT_MSG_CONTEXT(iocp->ioctl_cmds.msg_context, dlmsg->MsgContext);
	INITIALIZE_MGMT_STATUS(iocp->ioctl_cmds.status)
	mpt_put_msg_frame(mptctl_id, iocp, mf);

	/* Now रुको क्रम the command to complete */
retry_रुको:
	समयleft = रुको_क्रम_completion_समयout(&iocp->ioctl_cmds.करोne, HZ*60);
	अगर (!(iocp->ioctl_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		ret = -ETIME;
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: failed\n", iocp->name, __func__);
		अगर (iocp->ioctl_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET) अणु
			mpt_मुक्त_msg_frame(iocp, mf);
			जाओ fwdl_out;
		पूर्ण
		अगर (!समयleft) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
			       "FW download timeout, doorbell=0x%08x\n",
			       iocp->name, mpt_GetIocState(iocp, 0));
			mptctl_समयout_expired(iocp, mf);
		पूर्ण अन्यथा
			जाओ retry_रुको;
		जाओ fwdl_out;
	पूर्ण

	अगर (!(iocp->ioctl_cmds.status & MPT_MGMT_STATUS_RF_VALID)) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: failed\n", iocp->name, __func__);
		mpt_मुक्त_msg_frame(iocp, mf);
		ret = -ENODATA;
		जाओ fwdl_out;
	पूर्ण

	अगर (sgl)
		kमुक्त_sgl(sgl, sgl_dma, buflist, iocp);

	ReplyMsg = (pFWDownloadReply_t)iocp->ioctl_cmds.reply;
	iocstat = le16_to_cpu(ReplyMsg->IOCStatus) & MPI_IOCSTATUS_MASK;
	अगर (iocstat == MPI_IOCSTATUS_SUCCESS) अणु
		prपूर्णांकk(MYIOC_s_INFO_FMT "F/W update successful!\n", iocp->name);
		वापस 0;
	पूर्ण अन्यथा अगर (iocstat == MPI_IOCSTATUS_INVALID_FUNCTION) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "Hmmm...  F/W download not supported!?!\n",
			iocp->name);
		prपूर्णांकk(MYIOC_s_WARN_FMT "(time to go bang on somebodies door)\n",
			iocp->name);
		वापस -EBADRQC;
	पूर्ण अन्यथा अगर (iocstat == MPI_IOCSTATUS_BUSY) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "IOC_BUSY!\n", iocp->name);
		prपूर्णांकk(MYIOC_s_WARN_FMT "(try again later?)\n", iocp->name);
		वापस -EBUSY;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "ioctl_fwdl() returned [bad] status = %04xh\n",
			iocp->name, iocstat);
		prपूर्णांकk(MYIOC_s_WARN_FMT "(bad VooDoo)\n", iocp->name);
		वापस -ENOMSG;
	पूर्ण
	वापस 0;

fwdl_out:

	CLEAR_MGMT_STATUS(iocp->ioctl_cmds.status);
	SET_MGMT_MSG_CONTEXT(iocp->ioctl_cmds.msg_context, 0);
        kमुक्त_sgl(sgl, sgl_dma, buflist, iocp);
	वापस ret;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * SGE Allocation routine
 *
 * Inमाला_दो:	bytes - number of bytes to be transferred
 *		sgdir - data direction
 *		sge_offset - offset (in bytes) from the start of the request
 *			frame to the first SGE
 *		ioc - poपूर्णांकer to the mptadapter
 * Outमाला_दो:	frags - number of scatter gather elements
 *		blp - poपूर्णांक to the buflist poपूर्णांकer
 *		sglbuf_dma - poपूर्णांकer to the (dma) sgl
 * Returns:	Null अगर failes
 *		poपूर्णांकer to the (भव) sgl अगर successful.
 */
अटल MptSge_t *
kbuf_alloc_2_sgl(पूर्णांक bytes, u32 sgdir, पूर्णांक sge_offset, पूर्णांक *frags,
		 काष्ठा buflist **blp, dma_addr_t *sglbuf_dma, MPT_ADAPTER *ioc)
अणु
	MptSge_t	*sglbuf = शून्य;		/* poपूर्णांकer to array of SGE */
						/* and chain buffers */
	काष्ठा buflist	*buflist = शून्य;	/* kernel routine */
	MptSge_t	*sgl;
	पूर्णांक		 numfrags = 0;
	पूर्णांक		 fragcnt = 0;
	पूर्णांक		 alloc_sz = min(bytes,MAX_KMALLOC_SZ);	// aव्योम kernel warning msg!
	पूर्णांक		 bytes_allocd = 0;
	पूर्णांक		 this_alloc;
	dma_addr_t	 pa;					// phys addr
	पूर्णांक		 i, buflist_ent;
	पूर्णांक		 sg_spill = MAX_FRAGS_SPILL1;
	पूर्णांक		 dir;

	अगर (bytes < 0)
		वापस शून्य;

	/* initialization */
	*frags = 0;
	*blp = शून्य;

	/* Allocate and initialize an array of kernel
	 * काष्ठाures क्रम the SG elements.
	 */
	i = MAX_SGL_BYTES / 8;
	buflist = kzalloc(i, GFP_USER);
	अगर (!buflist)
		वापस शून्य;
	buflist_ent = 0;

	/* Allocate a single block of memory to store the sg elements and
	 * the chain buffers.  The calling routine is responsible क्रम
	 * copying the data in this array पूर्णांकo the correct place in the
	 * request and chain buffers.
	 */
	sglbuf = pci_alloc_consistent(ioc->pcidev, MAX_SGL_BYTES, sglbuf_dma);
	अगर (sglbuf == शून्य)
		जाओ मुक्त_and_fail;

	अगर (sgdir & 0x04000000)
		dir = PCI_DMA_TODEVICE;
	अन्यथा
		dir = PCI_DMA_FROMDEVICE;

	/* At start:
	 *	sgl = sglbuf = poपूर्णांक to beginning of sg buffer
	 *	buflist_ent = 0 = first kernel काष्ठाure
	 *	sg_spill = number of SGE that can be written beक्रमe the first
	 *		chain element.
	 *
	 */
	sgl = sglbuf;
	sg_spill = ((ioc->req_sz - sge_offset)/ioc->SGE_size) - 1;
	जबतक (bytes_allocd < bytes) अणु
		this_alloc = min(alloc_sz, bytes-bytes_allocd);
		buflist[buflist_ent].len = this_alloc;
		buflist[buflist_ent].kptr = pci_alloc_consistent(ioc->pcidev,
								 this_alloc,
								 &pa);
		अगर (buflist[buflist_ent].kptr == शून्य) अणु
			alloc_sz = alloc_sz / 2;
			अगर (alloc_sz == 0) अणु
				prपूर्णांकk(MYIOC_s_WARN_FMT "-SG: No can do - "
				    "not enough memory!   :-(\n", ioc->name);
				prपूर्णांकk(MYIOC_s_WARN_FMT "-SG: (freeing %d frags)\n",
					ioc->name, numfrags);
				जाओ मुक्त_and_fail;
			पूर्ण
			जारी;
		पूर्ण अन्यथा अणु
			dma_addr_t dma_addr;

			bytes_allocd += this_alloc;
			sgl->FlagsLength = (0x10000000|sgdir|this_alloc);
			dma_addr = pci_map_single(ioc->pcidev,
				buflist[buflist_ent].kptr, this_alloc, dir);
			sgl->Address = dma_addr;

			fragcnt++;
			numfrags++;
			sgl++;
			buflist_ent++;
		पूर्ण

		अगर (bytes_allocd >= bytes)
			अवरोध;

		/* Need to chain? */
		अगर (fragcnt == sg_spill) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
			    "-SG: No can do - " "Chain required!   :-(\n", ioc->name);
			prपूर्णांकk(MYIOC_s_WARN_FMT "(freeing %d frags)\n", ioc->name, numfrags);
			जाओ मुक्त_and_fail;
		पूर्ण

		/* overflow check... */
		अगर (numfrags*8 > MAX_SGL_BYTES)अणु
			/* GRRRRR... */
			prपूर्णांकk(MYIOC_s_WARN_FMT "-SG: No can do - "
				"too many SG frags!   :-(\n", ioc->name);
			prपूर्णांकk(MYIOC_s_WARN_FMT "-SG: (freeing %d frags)\n",
				ioc->name, numfrags);
			जाओ मुक्त_and_fail;
		पूर्ण
	पूर्ण

	/* Last sge fixup: set LE+eol+eob bits */
	sgl[-1].FlagsLength |= 0xC1000000;

	*frags = numfrags;
	*blp = buflist;

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "-SG: kbuf_alloc_2_sgl() - "
	   "%d SG frags generated!\n", ioc->name, numfrags));

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "-SG: kbuf_alloc_2_sgl() - "
	   "last (big) alloc_sz=%d\n", ioc->name, alloc_sz));

	वापस sglbuf;

मुक्त_and_fail:
	अगर (sglbuf != शून्य) अणु
		क्रम (i = 0; i < numfrags; i++) अणु
			dma_addr_t dma_addr;
			u8 *kptr;
			पूर्णांक len;

			अगर ((sglbuf[i].FlagsLength >> 24) == 0x30)
				जारी;

			dma_addr = sglbuf[i].Address;
			kptr = buflist[i].kptr;
			len = buflist[i].len;

			pci_मुक्त_consistent(ioc->pcidev, len, kptr, dma_addr);
		पूर्ण
		pci_मुक्त_consistent(ioc->pcidev, MAX_SGL_BYTES, sglbuf, *sglbuf_dma);
	पूर्ण
	kमुक्त(buflist);
	वापस शून्य;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * Routine to मुक्त the SGL elements.
 */
अटल व्योम
kमुक्त_sgl(MptSge_t *sgl, dma_addr_t sgl_dma, काष्ठा buflist *buflist, MPT_ADAPTER *ioc)
अणु
	MptSge_t	*sg = sgl;
	काष्ठा buflist	*bl = buflist;
	u32		 nib;
	पूर्णांक		 dir;
	पूर्णांक		 n = 0;

	अगर (sg->FlagsLength & 0x04000000)
		dir = PCI_DMA_TODEVICE;
	अन्यथा
		dir = PCI_DMA_FROMDEVICE;

	nib = (sg->FlagsLength & 0xF0000000) >> 28;
	जबतक (! (nib & 0x4)) अणु /* eob */
		/* skip ignore/chain. */
		अगर (nib == 0 || nib == 3) अणु
			;
		पूर्ण अन्यथा अगर (sg->Address) अणु
			dma_addr_t dma_addr;
			व्योम *kptr;
			पूर्णांक len;

			dma_addr = sg->Address;
			kptr = bl->kptr;
			len = bl->len;
			pci_unmap_single(ioc->pcidev, dma_addr, len, dir);
			pci_मुक्त_consistent(ioc->pcidev, len, kptr, dma_addr);
			n++;
		पूर्ण
		sg++;
		bl++;
		nib = (le32_to_cpu(sg->FlagsLength) & 0xF0000000) >> 28;
	पूर्ण

	/* we're at eob! */
	अगर (sg->Address) अणु
		dma_addr_t dma_addr;
		व्योम *kptr;
		पूर्णांक len;

		dma_addr = sg->Address;
		kptr = bl->kptr;
		len = bl->len;
		pci_unmap_single(ioc->pcidev, dma_addr, len, dir);
		pci_मुक्त_consistent(ioc->pcidev, len, kptr, dma_addr);
		n++;
	पूर्ण

	pci_मुक्त_consistent(ioc->pcidev, MAX_SGL_BYTES, sgl, sgl_dma);
	kमुक्त(buflist);
	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "-SG: Free'd 1 SGL buf + %d kbufs!\n",
	    ioc->name, n));
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptctl_getiocinfo - Query the host adapter क्रम IOC inक्रमmation.
 *	@arg: User space argument
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EFAULT अगर data unavailable
 *		-ENODEV  अगर no such device/adapter
 */
अटल पूर्णांक
mptctl_getiocinfo (MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg, अचिन्हित पूर्णांक data_size)
अणु
	काष्ठा mpt_ioctl_iocinfo __user *uarg = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_iocinfo *karg;
	काष्ठा pci_dev		*pdev;
	अचिन्हित पूर्णांक		port;
	पूर्णांक			cim_rev;
	काष्ठा scsi_device 	*sdev;
	VirtDevice		*vdevice;

	/* Add of PCI INFO results in unaligned access क्रम
	 * IA64 and Sparc. Reset दीर्घ to पूर्णांक. Return no PCI
	 * data क्रम obsolete क्रमmat.
	 */
	अगर (data_size == माप(काष्ठा mpt_ioctl_iocinfo_rev0))
		cim_rev = 0;
	अन्यथा अगर (data_size == माप(काष्ठा mpt_ioctl_iocinfo_rev1))
		cim_rev = 1;
	अन्यथा अगर (data_size == माप(काष्ठा mpt_ioctl_iocinfo))
		cim_rev = 2;
	अन्यथा अगर (data_size == (माप(काष्ठा mpt_ioctl_iocinfo_rev0)+12))
		cim_rev = 0;	/* obsolete */
	अन्यथा
		वापस -EFAULT;

	karg = memdup_user(uarg, data_size);
	अगर (IS_ERR(karg)) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mpt_ioctl_iocinfo() - memdup_user returned error [%ld]\n",
				__खाता__, __LINE__, PTR_ERR(karg));
		वापस PTR_ERR(karg);
	पूर्ण

	/* Verअगरy the data transfer size is correct. */
	अगर (karg->hdr.maxDataSize != data_size) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_getiocinfo - "
			"Structure size mismatch. Command not completed.\n",
			ioc->name, __खाता__, __LINE__);
		kमुक्त(karg);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_getiocinfo called.\n",
	    ioc->name));

	/* Fill in the data and वापस the काष्ठाure to the calling
	 * program
	 */
	अगर (ioc->bus_type == SAS)
		karg->adapterType = MPT_IOCTL_INTERFACE_SAS;
	अन्यथा अगर (ioc->bus_type == FC)
		karg->adapterType = MPT_IOCTL_INTERFACE_FC;
	अन्यथा
		karg->adapterType = MPT_IOCTL_INTERFACE_SCSI;

	अगर (karg->hdr.port > 1) अणु
		kमुक्त(karg);
		वापस -EINVAL;
	पूर्ण
	port = karg->hdr.port;

	karg->port = port;
	pdev = (काष्ठा pci_dev *) ioc->pcidev;

	karg->pciId = pdev->device;
	karg->hwRev = pdev->revision;
	karg->subSystemDevice = pdev->subप्रणाली_device;
	karg->subSystemVenकरोr = pdev->subप्रणाली_venकरोr;

	अगर (cim_rev == 1) अणु
		/* Get the PCI bus, device, and function numbers क्रम the IOC
		 */
		karg->pciInfo.u.bits.busNumber = pdev->bus->number;
		karg->pciInfo.u.bits.deviceNumber = PCI_SLOT( pdev->devfn );
		karg->pciInfo.u.bits.functionNumber = PCI_FUNC( pdev->devfn );
	पूर्ण अन्यथा अगर (cim_rev == 2) अणु
		/* Get the PCI bus, device, function and segment ID numbers
		   क्रम the IOC */
		karg->pciInfo.u.bits.busNumber = pdev->bus->number;
		karg->pciInfo.u.bits.deviceNumber = PCI_SLOT( pdev->devfn );
		karg->pciInfo.u.bits.functionNumber = PCI_FUNC( pdev->devfn );
		karg->pciInfo.segmentID = pci_करोमुख्य_nr(pdev->bus);
	पूर्ण

	/* Get number of devices
         */
	karg->numDevices = 0;
	अगर (ioc->sh) अणु
		shost_क्रम_each_device(sdev, ioc->sh) अणु
			vdevice = sdev->hostdata;
			अगर (vdevice == शून्य || vdevice->vtarget == शून्य)
				जारी;
			अगर (vdevice->vtarget->tflags &
			    MPT_TARGET_FLAGS_RAID_COMPONENT)
				जारी;
			karg->numDevices++;
		पूर्ण
	पूर्ण

	/* Set the BIOS and FW Version
	 */
	karg->FWVersion = ioc->facts.FWVersion.Word;
	karg->BIOSVersion = ioc->biosVersion;

	/* Set the Version Strings.
	 */
	म_नकलन (karg->driverVersion, MPT_LINUX_PACKAGE_NAME, MPT_IOCTL_VERSION_LENGTH);
	karg->driverVersion[MPT_IOCTL_VERSION_LENGTH-1]='\0';

	karg->busChangeEvent = 0;
	karg->hostId = ioc->pfacts[port].PortSCSIID;
	karg->rsvd[0] = karg->rsvd[1] = 0;

	/* Copy the data from kernel memory to user memory
	 */
	अगर (copy_to_user((अक्षर __user *)arg, karg, data_size)) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_getiocinfo - "
			"Unable to write out mpt_ioctl_iocinfo struct @ %p\n",
			ioc->name, __खाता__, __LINE__, uarg);
		kमुक्त(karg);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(karg);
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptctl_gettargetinfo - Query the host adapter क्रम target inक्रमmation.
 *	@arg: User space argument
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EFAULT अगर data unavailable
 *		-ENODEV  अगर no such device/adapter
 */
अटल पूर्णांक
mptctl_gettargetinfo (MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_targetinfo __user *uarg = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_targetinfo karg;
	VirtDevice		*vdevice;
	अक्षर			*pmem;
	पूर्णांक			*pdata;
	पूर्णांक			numDevices = 0;
	पूर्णांक			lun;
	पूर्णांक			maxWordsLeft;
	पूर्णांक			numBytes;
	काष्ठा scsi_device 	*sdev;

	अगर (copy_from_user(&karg, uarg, माप(काष्ठा mpt_ioctl_targetinfo))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_gettargetinfo - "
			"Unable to read in mpt_ioctl_targetinfo struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_gettargetinfo called.\n",
	    ioc->name));
	numBytes = karg.hdr.maxDataSize - माप(mpt_ioctl_header);
	maxWordsLeft = numBytes/माप(पूर्णांक);

	अगर (maxWordsLeft <= 0) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_gettargetinfo() - no memory available!\n",
			ioc->name, __खाता__, __LINE__);
		वापस -ENOMEM;
	पूर्ण

	/* Fill in the data and वापस the काष्ठाure to the calling
	 * program
	 */

	/* काष्ठा mpt_ioctl_targetinfo करोes not contain sufficient space
	 * क्रम the target काष्ठाures so when the IOCTL is called, there is
	 * not sufficient stack space क्रम the काष्ठाure. Allocate memory,
	 * populate the memory, copy back to the user, then मुक्त memory.
	 * targetInfo क्रमmat:
	 * bits 31-24: reserved
	 *      23-16: LUN
	 *      15- 8: Bus Number
	 *       7- 0: Target ID
	 */
	pmem = kzalloc(numBytes, GFP_KERNEL);
	अगर (!pmem) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_gettargetinfo() - no memory available!\n",
			ioc->name, __खाता__, __LINE__);
		वापस -ENOMEM;
	पूर्ण
	pdata =  (पूर्णांक *) pmem;

	/* Get number of devices
         */
	अगर (ioc->sh)अणु
		shost_क्रम_each_device(sdev, ioc->sh) अणु
			अगर (!maxWordsLeft)
				जारी;
			vdevice = sdev->hostdata;
			अगर (vdevice == शून्य || vdevice->vtarget == शून्य)
				जारी;
			अगर (vdevice->vtarget->tflags &
			    MPT_TARGET_FLAGS_RAID_COMPONENT)
				जारी;
			lun = (vdevice->vtarget->raidVolume) ? 0x80 : vdevice->lun;
			*pdata = (((u8)lun << 16) + (vdevice->vtarget->channel << 8) +
			    (vdevice->vtarget->id ));
			pdata++;
			numDevices++;
			--maxWordsLeft;
		पूर्ण
	पूर्ण
	karg.numDevices = numDevices;

	/* Copy part of the data from kernel memory to user memory
	 */
	अगर (copy_to_user((अक्षर __user *)arg, &karg,
				माप(काष्ठा mpt_ioctl_targetinfo))) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_gettargetinfo - "
			"Unable to write out mpt_ioctl_targetinfo struct @ %p\n",
			ioc->name, __खाता__, __LINE__, uarg);
		kमुक्त(pmem);
		वापस -EFAULT;
	पूर्ण

	/* Copy the reमुख्यing data from kernel memory to user memory
	 */
	अगर (copy_to_user(uarg->targetInfo, pmem, numBytes)) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_gettargetinfo - "
			"Unable to write out mpt_ioctl_targetinfo struct @ %p\n",
			ioc->name, __खाता__, __LINE__, pdata);
		kमुक्त(pmem);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(pmem);

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* MPT IOCTL Test function.
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EFAULT अगर data unavailable
 *		-ENODEV  अगर no such device/adapter
 */
अटल पूर्णांक
mptctl_पढ़ोtest (MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_test __user *uarg = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_test	 karg;

	अगर (copy_from_user(&karg, uarg, माप(काष्ठा mpt_ioctl_test))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_readtest - "
			"Unable to read in mpt_ioctl_test struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_readtest called.\n",
	    ioc->name));
	/* Fill in the data and वापस the काष्ठाure to the calling
	 * program
	 */

#अगर_घोषित MFCNT
	karg.chip_type = ioc->mfcnt;
#अन्यथा
	karg.chip_type = ioc->pcidev->device;
#पूर्ण_अगर
	म_नकलन (karg.name, ioc->name, MPT_MAX_NAME);
	karg.name[MPT_MAX_NAME-1]='\0';
	म_नकलन (karg.product, ioc->prod_name, MPT_PRODUCT_LENGTH);
	karg.product[MPT_PRODUCT_LENGTH-1]='\0';

	/* Copy the data from kernel memory to user memory
	 */
	अगर (copy_to_user((अक्षर __user *)arg, &karg, माप(काष्ठा mpt_ioctl_test))) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_readtest - "
			"Unable to write out mpt_ioctl_test struct @ %p\n",
			ioc->name, __खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptctl_eventquery - Query the host adapter क्रम the event types
 *	that are being logged.
 *	@arg: User space argument
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EFAULT अगर data unavailable
 *		-ENODEV  अगर no such device/adapter
 */
अटल पूर्णांक
mptctl_eventquery (MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_eventquery __user *uarg = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_eventquery	 karg;

	अगर (copy_from_user(&karg, uarg, माप(काष्ठा mpt_ioctl_eventquery))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_eventquery - "
			"Unable to read in mpt_ioctl_eventquery struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_eventquery called.\n",
	    ioc->name));
	karg.eventEntries = MPTCTL_EVENT_LOG_SIZE;
	karg.eventTypes = ioc->eventTypes;

	/* Copy the data from kernel memory to user memory
	 */
	अगर (copy_to_user((अक्षर __user *)arg, &karg, माप(काष्ठा mpt_ioctl_eventquery))) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_eventquery - "
			"Unable to write out mpt_ioctl_eventquery struct @ %p\n",
			ioc->name, __खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mptctl_eventenable (MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_eventenable __user *uarg = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_eventenable	 karg;

	अगर (copy_from_user(&karg, uarg, माप(काष्ठा mpt_ioctl_eventenable))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_eventenable - "
			"Unable to read in mpt_ioctl_eventenable struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_eventenable called.\n",
	    ioc->name));
	अगर (ioc->events == शून्य) अणु
		/* Have not yet allocated memory - करो so now.
		 */
		पूर्णांक sz = MPTCTL_EVENT_LOG_SIZE * माप(MPT_IOCTL_EVENTS);
		ioc->events = kzalloc(sz, GFP_KERNEL);
		अगर (!ioc->events) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT
			    ": ERROR - Insufficient memory to add adapter!\n",
			    ioc->name);
			वापस -ENOMEM;
		पूर्ण
		ioc->alloc_total += sz;

		ioc->eventContext = 0;
        पूर्ण

	/* Update the IOC event logging flag.
	 */
	ioc->eventTypes = karg.eventTypes;

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mptctl_eventreport (MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_eventreport __user *uarg = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_eventreport	 karg;
	पूर्णांक			 numBytes, maxEvents, max;

	अगर (copy_from_user(&karg, uarg, माप(काष्ठा mpt_ioctl_eventreport))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_eventreport - "
			"Unable to read in mpt_ioctl_eventreport struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_eventreport called.\n",
	    ioc->name));

	numBytes = karg.hdr.maxDataSize - माप(mpt_ioctl_header);
	maxEvents = numBytes/माप(MPT_IOCTL_EVENTS);


	max = MPTCTL_EVENT_LOG_SIZE < maxEvents ? MPTCTL_EVENT_LOG_SIZE : maxEvents;

	/* If fewer than 1 event is requested, there must have
	 * been some type of error.
	 */
	अगर ((max < 1) || !ioc->events)
		वापस -ENODATA;

	/* reset this flag so SIGIO can restart */
	ioc->aen_event_पढ़ो_flag=0;

	/* Copy the data from kernel memory to user memory
	 */
	numBytes = max * माप(MPT_IOCTL_EVENTS);
	अगर (copy_to_user(uarg->eventData, ioc->events, numBytes)) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_eventreport - "
			"Unable to write out mpt_ioctl_eventreport struct @ %p\n",
			ioc->name, __खाता__, __LINE__, ioc->events);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mptctl_replace_fw (MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_replace_fw __user *uarg = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_replace_fw	 karg;
	पूर्णांक			 newFwSize;

	अगर (copy_from_user(&karg, uarg, माप(काष्ठा mpt_ioctl_replace_fw))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_replace_fw - "
			"Unable to read in mpt_ioctl_replace_fw struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_replace_fw called.\n",
	    ioc->name));
	/* If caching FW, Free the old FW image
	 */
	अगर (ioc->cached_fw == शून्य)
		वापस 0;

	mpt_मुक्त_fw_memory(ioc);

	/* Allocate memory क्रम the new FW image
	 */
	newFwSize = ALIGN(karg.newImageSize, 4);

	mpt_alloc_fw_memory(ioc, newFwSize);
	अगर (ioc->cached_fw == शून्य)
		वापस -ENOMEM;

	/* Copy the data from user memory to kernel space
	 */
	अगर (copy_from_user(ioc->cached_fw, uarg->newImage, newFwSize)) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_replace_fw - "
				"Unable to read in mpt_ioctl_replace_fw image "
				"@ %p\n", ioc->name, __खाता__, __LINE__, uarg);
		mpt_मुक्त_fw_memory(ioc);
		वापस -EFAULT;
	पूर्ण

	/* Update IOCFactsReply
	 */
	ioc->facts.FWImageSize = newFwSize;
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* MPT IOCTL MPTCOMMAND function.
 * Cast the arg पूर्णांकo the mpt_ioctl_mpt_command काष्ठाure.
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EBUSY  अगर previous command समयout and IOC reset is not complete.
 *		-EFAULT अगर data unavailable
 *		-ENODEV अगर no such device/adapter
 *		-ETIME	अगर समयr expires
 *		-ENOMEM अगर memory allocation error
 */
अटल पूर्णांक
mptctl_mpt_command (MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_command __user *uarg = (व्योम __user *) arg;
	काष्ठा mpt_ioctl_command  karg;
	पूर्णांक		rc;


	अगर (copy_from_user(&karg, uarg, माप(काष्ठा mpt_ioctl_command))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_mpt_command - "
			"Unable to read in mpt_ioctl_command struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	rc = mptctl_करो_mpt_command (ioc, karg, &uarg->MF);

	वापस rc;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Worker routine क्रम the IOCTL MPTCOMMAND and MPTCOMMAND32 (sparc) commands.
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EBUSY  अगर previous command समयout and IOC reset is not complete.
 *		-EFAULT अगर data unavailable
 *		-ENODEV अगर no such device/adapter
 *		-ETIME	अगर समयr expires
 *		-ENOMEM अगर memory allocation error
 *		-EPERM अगर SCSI I/O and target is untagged
 */
अटल पूर्णांक
mptctl_करो_mpt_command (MPT_ADAPTER *ioc, काष्ठा mpt_ioctl_command karg, व्योम __user *mfPtr)
अणु
	MPT_FRAME_HDR	*mf = शून्य;
	MPIHeader_t	*hdr;
	अक्षर		*psge;
	काष्ठा buflist	bufIn;	/* data In buffer */
	काष्ठा buflist	bufOut; /* data Out buffer */
	dma_addr_t	dma_addr_in;
	dma_addr_t	dma_addr_out;
	पूर्णांक		sgSize = 0;	/* Num SG elements */
	पूर्णांक		flagsLength;
	पूर्णांक		sz, rc = 0;
	पूर्णांक		msgContext;
	u16		req_idx;
	uदीर्घ 		समयout;
	अचिन्हित दीर्घ	समयleft;
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ	 flags;
	u8		 function;

	/* bufIn and bufOut are used क्रम user to kernel space transfers
	 */
	bufIn.kptr = bufOut.kptr = शून्य;
	bufIn.len = bufOut.len = 0;

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress) अणु
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_do_mpt_command - "
			"Busy with diagnostic reset\n", __खाता__, __LINE__);
		वापस -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);

	/* Basic sanity checks to prevent underflows or पूर्णांकeger overflows */
	अगर (karg.maxReplyBytes < 0 ||
	    karg.dataInSize < 0 ||
	    karg.dataOutSize < 0 ||
	    karg.dataSgeOffset < 0 ||
	    karg.maxSenseBytes < 0 ||
	    karg.dataSgeOffset > ioc->req_sz / 4)
		वापस -EINVAL;

	/* Verअगरy that the final request frame will not be too large.
	 */
	sz = karg.dataSgeOffset * 4;
	अगर (karg.dataInSize > 0)
		sz += ioc->SGE_size;
	अगर (karg.dataOutSize > 0)
		sz += ioc->SGE_size;

	अगर (sz > ioc->req_sz) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
			"Request frame too large (%d) maximum (%d)\n",
			ioc->name, __खाता__, __LINE__, sz, ioc->req_sz);
		वापस -EFAULT;
	पूर्ण

	/* Get a मुक्त request frame and save the message context.
	 */
        अगर ((mf = mpt_get_msg_frame(mptctl_id, ioc)) == शून्य)
                वापस -EAGAIN;

	hdr = (MPIHeader_t *) mf;
	msgContext = le32_to_cpu(hdr->MsgContext);
	req_idx = le16_to_cpu(mf->u.frame.hwhdr.msgctxu.fld.req_idx);

	/* Copy the request frame
	 * Reset the saved message context.
	 * Request frame in user space
	 */
	अगर (copy_from_user(mf, mfPtr, karg.dataSgeOffset * 4)) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
			"Unable to read MF from mpt_ioctl_command struct @ %p\n",
			ioc->name, __खाता__, __LINE__, mfPtr);
		function = -1;
		rc = -EFAULT;
		जाओ करोne_मुक्त_mem;
	पूर्ण
	hdr->MsgContext = cpu_to_le32(msgContext);
	function = hdr->Function;


	/* Verअगरy that this request is allowed.
	 */
	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "sending mpi function (0x%02X), req=%p\n",
	    ioc->name, hdr->Function, mf));

	चयन (function) अणु
	हाल MPI_FUNCTION_IOC_FACTS:
	हाल MPI_FUNCTION_PORT_FACTS:
		karg.dataOutSize  = karg.dataInSize = 0;
		अवरोध;

	हाल MPI_FUNCTION_CONFIG:
	अणु
		Config_t *config_frame;
		config_frame = (Config_t *)mf;
		dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "\ttype=0x%02x ext_type=0x%02x "
		    "number=0x%02x action=0x%02x\n", ioc->name,
		    config_frame->Header.PageType,
		    config_frame->ExtPageType,
		    config_frame->Header.PageNumber,
		    config_frame->Action));
		अवरोध;
	पूर्ण

	हाल MPI_FUNCTION_FC_COMMON_TRANSPORT_SEND:
	हाल MPI_FUNCTION_FC_EX_LINK_SRVC_SEND:
	हाल MPI_FUNCTION_FW_UPLOAD:
	हाल MPI_FUNCTION_SCSI_ENCLOSURE_PROCESSOR:
	हाल MPI_FUNCTION_FW_DOWNLOAD:
	हाल MPI_FUNCTION_FC_PRIMITIVE_SEND:
	हाल MPI_FUNCTION_TOOLBOX:
	हाल MPI_FUNCTION_SAS_IO_UNIT_CONTROL:
		अवरोध;

	हाल MPI_FUNCTION_SCSI_IO_REQUEST:
		अगर (ioc->sh) अणु
			SCSIIORequest_t *pScsiReq = (SCSIIORequest_t *) mf;
			पूर्णांक qtag = MPI_SCSIIO_CONTROL_UNTAGGED;
			पूर्णांक scsidir = 0;
			पूर्णांक dataSize;
			u32 id;

			id = (ioc->devices_per_bus == 0) ? 256 : ioc->devices_per_bus;
			अगर (pScsiReq->TargetID > id) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
					"Target ID out of bounds. \n",
					ioc->name, __खाता__, __LINE__);
				rc = -ENODEV;
				जाओ करोne_मुक्त_mem;
			पूर्ण

			अगर (pScsiReq->Bus >= ioc->number_of_buses) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
					"Target Bus out of bounds. \n",
					ioc->name, __खाता__, __LINE__);
				rc = -ENODEV;
				जाओ करोne_मुक्त_mem;
			पूर्ण

			pScsiReq->MsgFlags &= ~MPI_SCSIIO_MSGFLGS_SENSE_WIDTH;
			pScsiReq->MsgFlags |= mpt_msg_flags(ioc);


			/* verअगरy that app has not requested
			 *	more sense data than driver
			 *	can provide, अगर so, reset this parameter
			 * set the sense buffer poपूर्णांकer low address
			 * update the control field to specअगरy Q type
			 */
			अगर (karg.maxSenseBytes > MPT_SENSE_BUFFER_SIZE)
				pScsiReq->SenseBufferLength = MPT_SENSE_BUFFER_SIZE;
			अन्यथा
				pScsiReq->SenseBufferLength = karg.maxSenseBytes;

			pScsiReq->SenseBufferLowAddr =
				cpu_to_le32(ioc->sense_buf_low_dma
				   + (req_idx * MPT_SENSE_BUFFER_ALLOC));

			shost_क्रम_each_device(sdev, ioc->sh) अणु
				काष्ठा scsi_target *starget = scsi_target(sdev);
				VirtTarget *vtarget = starget->hostdata;

				अगर (vtarget == शून्य)
					जारी;

				अगर ((pScsiReq->TargetID == vtarget->id) &&
				    (pScsiReq->Bus == vtarget->channel) &&
				    (vtarget->tflags & MPT_TARGET_FLAGS_Q_YES))
					qtag = MPI_SCSIIO_CONTROL_SIMPLEQ;
			पूर्ण

			/* Have the IOCTL driver set the direction based
			 * on the dataOutSize (ordering issue with Sparc).
			 */
			अगर (karg.dataOutSize > 0) अणु
				scsidir = MPI_SCSIIO_CONTROL_WRITE;
				dataSize = karg.dataOutSize;
			पूर्ण अन्यथा अणु
				scsidir = MPI_SCSIIO_CONTROL_READ;
				dataSize = karg.dataInSize;
			पूर्ण

			pScsiReq->Control = cpu_to_le32(scsidir | qtag);
			pScsiReq->DataLength = cpu_to_le32(dataSize);


		पूर्ण अन्यथा अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
				"SCSI driver is not loaded. \n",
				ioc->name, __खाता__, __LINE__);
			rc = -EFAULT;
			जाओ करोne_मुक्त_mem;
		पूर्ण
		अवरोध;

	हाल MPI_FUNCTION_SMP_PASSTHROUGH:
		/* Check mf->PassthruFlags to determine अगर
		 * transfer is ImmediateMode or not.
		 * Immediate mode वापसs data in the ReplyFrame.
		 * Else, we are sending request and response data
		 * in two SGLs at the end of the mf.
		 */
		अवरोध;

	हाल MPI_FUNCTION_SATA_PASSTHROUGH:
		अगर (!ioc->sh) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
				"SCSI driver is not loaded. \n",
				ioc->name, __खाता__, __LINE__);
			rc = -EFAULT;
			जाओ करोne_मुक्त_mem;
		पूर्ण
		अवरोध;

	हाल MPI_FUNCTION_RAID_ACTION:
		/* Just add a SGE
		 */
		अवरोध;

	हाल MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH:
		अगर (ioc->sh) अणु
			SCSIIORequest_t *pScsiReq = (SCSIIORequest_t *) mf;
			पूर्णांक qtag = MPI_SCSIIO_CONTROL_SIMPLEQ;
			पूर्णांक scsidir = MPI_SCSIIO_CONTROL_READ;
			पूर्णांक dataSize;

			pScsiReq->MsgFlags &= ~MPI_SCSIIO_MSGFLGS_SENSE_WIDTH;
			pScsiReq->MsgFlags |= mpt_msg_flags(ioc);


			/* verअगरy that app has not requested
			 *	more sense data than driver
			 *	can provide, अगर so, reset this parameter
			 * set the sense buffer poपूर्णांकer low address
			 * update the control field to specअगरy Q type
			 */
			अगर (karg.maxSenseBytes > MPT_SENSE_BUFFER_SIZE)
				pScsiReq->SenseBufferLength = MPT_SENSE_BUFFER_SIZE;
			अन्यथा
				pScsiReq->SenseBufferLength = karg.maxSenseBytes;

			pScsiReq->SenseBufferLowAddr =
				cpu_to_le32(ioc->sense_buf_low_dma
				   + (req_idx * MPT_SENSE_BUFFER_ALLOC));

			/* All commands to physical devices are tagged
			 */

			/* Have the IOCTL driver set the direction based
			 * on the dataOutSize (ordering issue with Sparc).
			 */
			अगर (karg.dataOutSize > 0) अणु
				scsidir = MPI_SCSIIO_CONTROL_WRITE;
				dataSize = karg.dataOutSize;
			पूर्ण अन्यथा अणु
				scsidir = MPI_SCSIIO_CONTROL_READ;
				dataSize = karg.dataInSize;
			पूर्ण

			pScsiReq->Control = cpu_to_le32(scsidir | qtag);
			pScsiReq->DataLength = cpu_to_le32(dataSize);

		पूर्ण अन्यथा अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
				"SCSI driver is not loaded. \n",
				ioc->name, __खाता__, __LINE__);
			rc = -EFAULT;
			जाओ करोne_मुक्त_mem;
		पूर्ण
		अवरोध;

	हाल MPI_FUNCTION_SCSI_TASK_MGMT:
	अणु
		SCSITaskMgmt_t	*pScsiTm;
		pScsiTm = (SCSITaskMgmt_t *)mf;
		dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"\tTaskType=0x%x MsgFlags=0x%x "
			"TaskMsgContext=0x%x id=%d channel=%d\n",
			ioc->name, pScsiTm->TaskType, le32_to_cpu
			(pScsiTm->TaskMsgContext), pScsiTm->MsgFlags,
			pScsiTm->TargetID, pScsiTm->Bus));
		अवरोध;
	पूर्ण

	हाल MPI_FUNCTION_IOC_INIT:
		अणु
			IOCInit_t	*pInit = (IOCInit_t *) mf;
			u32		high_addr, sense_high;

			/* Verअगरy that all entries in the IOC INIT match
			 * existing setup (and in LE क्रमmat).
			 */
			अगर (माप(dma_addr_t) == माप(u64)) अणु
				high_addr = cpu_to_le32((u32)((u64)ioc->req_frames_dma >> 32));
				sense_high= cpu_to_le32((u32)((u64)ioc->sense_buf_pool_dma >> 32));
			पूर्ण अन्यथा अणु
				high_addr = 0;
				sense_high= 0;
			पूर्ण

			अगर ((pInit->Flags != 0) || (pInit->MaxDevices != ioc->facts.MaxDevices) ||
				(pInit->MaxBuses != ioc->facts.MaxBuses) ||
				(pInit->ReplyFrameSize != cpu_to_le16(ioc->reply_sz)) ||
				(pInit->HostMfaHighAddr != high_addr) ||
				(pInit->SenseBufferHighAddr != sense_high)) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
					"IOC_INIT issued with 1 or more incorrect parameters. Rejected.\n",
					ioc->name, __खाता__, __LINE__);
				rc = -EFAULT;
				जाओ करोne_मुक्त_mem;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		/*
		 * MPI_FUNCTION_PORT_ENABLE
		 * MPI_FUNCTION_TARGET_CMD_BUFFER_POST
		 * MPI_FUNCTION_TARGET_ASSIST
		 * MPI_FUNCTION_TARGET_STATUS_SEND
		 * MPI_FUNCTION_TARGET_MODE_ABORT
		 * MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET
		 * MPI_FUNCTION_IO_UNIT_RESET
		 * MPI_FUNCTION_HANDSHAKE
		 * MPI_FUNCTION_REPLY_FRAME_REMOVAL
		 * MPI_FUNCTION_EVENT_NOTIFICATION
		 *  (driver handles event notअगरication)
		 * MPI_FUNCTION_EVENT_ACK
		 */

		/*  What to करो with these???  CHECK ME!!!
			MPI_FUNCTION_FC_LINK_SRVC_BUF_POST
			MPI_FUNCTION_FC_LINK_SRVC_RSP
			MPI_FUNCTION_FC_ABORT
			MPI_FUNCTION_LAN_SEND
			MPI_FUNCTION_LAN_RECEIVE
		 	MPI_FUNCTION_LAN_RESET
		*/

		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
			"Illegal request (function 0x%x) \n",
			ioc->name, __खाता__, __LINE__, hdr->Function);
		rc = -EFAULT;
		जाओ करोne_मुक्त_mem;
	पूर्ण

	/* Add the SGL ( at most one data in SGE and one data out SGE )
	 * In the हाल of two SGE's - the data out (ग_लिखो) will always
	 * preceede the data in (पढ़ो) SGE. psgList is used to मुक्त the
	 * allocated memory.
	 */
	psge = (अक्षर *) (((पूर्णांक *) mf) + karg.dataSgeOffset);
	flagsLength = 0;

	अगर (karg.dataOutSize > 0)
		sgSize ++;

	अगर (karg.dataInSize > 0)
		sgSize ++;

	अगर (sgSize > 0) अणु

		/* Set up the dataOut memory allocation */
		अगर (karg.dataOutSize > 0) अणु
			अगर (karg.dataInSize > 0) अणु
				flagsLength = ( MPI_SGE_FLAGS_SIMPLE_ELEMENT |
						MPI_SGE_FLAGS_END_OF_BUFFER |
						MPI_SGE_FLAGS_सूचीECTION)
						<< MPI_SGE_FLAGS_SHIFT;
			पूर्ण अन्यथा अणु
				flagsLength = MPT_SGE_FLAGS_SSIMPLE_WRITE;
			पूर्ण
			flagsLength |= karg.dataOutSize;
			bufOut.len = karg.dataOutSize;
			bufOut.kptr = pci_alloc_consistent(
					ioc->pcidev, bufOut.len, &dma_addr_out);

			अगर (bufOut.kptr == शून्य) अणु
				rc = -ENOMEM;
				जाओ करोne_मुक्त_mem;
			पूर्ण अन्यथा अणु
				/* Set up this SGE.
				 * Copy to MF and to sglbuf
				 */
				ioc->add_sge(psge, flagsLength, dma_addr_out);
				psge += ioc->SGE_size;

				/* Copy user data to kernel space.
				 */
				अगर (copy_from_user(bufOut.kptr,
						karg.dataOutBufPtr,
						bufOut.len)) अणु
					prपूर्णांकk(MYIOC_s_ERR_FMT
						"%s@%d::mptctl_do_mpt_command - Unable "
						"to read user data "
						"struct @ %p\n",
						ioc->name, __खाता__, __LINE__,karg.dataOutBufPtr);
					rc =  -EFAULT;
					जाओ करोne_मुक्त_mem;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (karg.dataInSize > 0) अणु
			flagsLength = MPT_SGE_FLAGS_SSIMPLE_READ;
			flagsLength |= karg.dataInSize;

			bufIn.len = karg.dataInSize;
			bufIn.kptr = pci_alloc_consistent(ioc->pcidev,
					bufIn.len, &dma_addr_in);

			अगर (bufIn.kptr == शून्य) अणु
				rc = -ENOMEM;
				जाओ करोne_मुक्त_mem;
			पूर्ण अन्यथा अणु
				/* Set up this SGE
				 * Copy to MF and to sglbuf
				 */
				ioc->add_sge(psge, flagsLength, dma_addr_in);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा  अणु
		/* Add a शून्य SGE
		 */
		ioc->add_sge(psge, flagsLength, (dma_addr_t) -1);
	पूर्ण

	SET_MGMT_MSG_CONTEXT(ioc->ioctl_cmds.msg_context, hdr->MsgContext);
	INITIALIZE_MGMT_STATUS(ioc->ioctl_cmds.status)
	अगर (hdr->Function == MPI_FUNCTION_SCSI_TASK_MGMT) अणु

		mutex_lock(&ioc->taskmgmt_cmds.mutex);
		अगर (mpt_set_taskmgmt_in_progress_flag(ioc) != 0) अणु
			mutex_unlock(&ioc->taskmgmt_cmds.mutex);
			जाओ करोne_मुक्त_mem;
		पूर्ण

		DBG_DUMP_TM_REQUEST_FRAME(ioc, (u32 *)mf);

		अगर ((ioc->facts.IOCCapabilities & MPI_IOCFACTS_CAPABILITY_HIGH_PRI_Q) &&
		    (ioc->facts.MsgVersion >= MPI_VERSION_01_05))
			mpt_put_msg_frame_hi_pri(mptctl_id, ioc, mf);
		अन्यथा अणु
			rc =mpt_send_handshake_request(mptctl_id, ioc,
				माप(SCSITaskMgmt_t), (u32*)mf, CAN_SLEEP);
			अगर (rc != 0) अणु
				dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				    "send_handshake FAILED! (ioc %p, mf %p)\n",
				    ioc->name, ioc, mf));
				mpt_clear_taskmgmt_in_progress_flag(ioc);
				rc = -ENODATA;
				mutex_unlock(&ioc->taskmgmt_cmds.mutex);
				जाओ करोne_मुक्त_mem;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा
		mpt_put_msg_frame(mptctl_id, ioc, mf);

	/* Now रुको क्रम the command to complete */
	समयout = (karg.समयout > 0) ? karg.समयout : MPT_IOCTL_DEFAULT_TIMEOUT;
retry_रुको:
	समयleft = रुको_क्रम_completion_समयout(&ioc->ioctl_cmds.करोne,
				HZ*समयout);
	अगर (!(ioc->ioctl_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		rc = -ETIME;
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT "%s: TIMED OUT!\n",
		    ioc->name, __func__));
		अगर (ioc->ioctl_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET) अणु
			अगर (function == MPI_FUNCTION_SCSI_TASK_MGMT)
				mutex_unlock(&ioc->taskmgmt_cmds.mutex);
			जाओ करोne_मुक्त_mem;
		पूर्ण
		अगर (!समयleft) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
			       "mpt cmd timeout, doorbell=0x%08x"
			       " function=0x%x\n",
			       ioc->name, mpt_GetIocState(ioc, 0), function);
			अगर (function == MPI_FUNCTION_SCSI_TASK_MGMT)
				mutex_unlock(&ioc->taskmgmt_cmds.mutex);
			mptctl_समयout_expired(ioc, mf);
			mf = शून्य;
		पूर्ण अन्यथा
			जाओ retry_रुको;
		जाओ करोne_मुक्त_mem;
	पूर्ण

	अगर (function == MPI_FUNCTION_SCSI_TASK_MGMT)
		mutex_unlock(&ioc->taskmgmt_cmds.mutex);


	mf = शून्य;

	/* If a valid reply frame, copy to the user.
	 * Offset 2: reply length in U32's
	 */
	अगर (ioc->ioctl_cmds.status & MPT_MGMT_STATUS_RF_VALID) अणु
		अगर (karg.maxReplyBytes < ioc->reply_sz) अणु
			sz = min(karg.maxReplyBytes,
				4*ioc->ioctl_cmds.reply[2]);
		पूर्ण अन्यथा अणु
			 sz = min(ioc->reply_sz, 4*ioc->ioctl_cmds.reply[2]);
		पूर्ण
		अगर (sz > 0) अणु
			अगर (copy_to_user(karg.replyFrameBufPtr,
				 ioc->ioctl_cmds.reply, sz))अणु
				 prपूर्णांकk(MYIOC_s_ERR_FMT
				     "%s@%d::mptctl_do_mpt_command - "
				 "Unable to write out reply frame %p\n",
				 ioc->name, __खाता__, __LINE__, karg.replyFrameBufPtr);
				 rc =  -ENODATA;
				 जाओ करोne_मुक्त_mem;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If valid sense data, copy to user.
	 */
	अगर (ioc->ioctl_cmds.status & MPT_MGMT_STATUS_SENSE_VALID) अणु
		sz = min(karg.maxSenseBytes, MPT_SENSE_BUFFER_SIZE);
		अगर (sz > 0) अणु
			अगर (copy_to_user(karg.senseDataPtr,
				ioc->ioctl_cmds.sense, sz)) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
				"Unable to write sense data to user %p\n",
				ioc->name, __खाता__, __LINE__,
				karg.senseDataPtr);
				rc =  -ENODATA;
				जाओ करोne_मुक्त_mem;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If the overall status is _GOOD and data in, copy data
	 * to user.
	 */
	अगर ((ioc->ioctl_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD) &&
				(karg.dataInSize > 0) && (bufIn.kptr)) अणु

		अगर (copy_to_user(karg.dataInBufPtr,
				 bufIn.kptr, karg.dataInSize)) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_do_mpt_command - "
				"Unable to write data to user %p\n",
				ioc->name, __खाता__, __LINE__,
				karg.dataInBufPtr);
			rc =  -ENODATA;
		पूर्ण
	पूर्ण

करोne_मुक्त_mem:

	CLEAR_MGMT_STATUS(ioc->ioctl_cmds.status)
	SET_MGMT_MSG_CONTEXT(ioc->ioctl_cmds.msg_context, 0);

	/* Free the allocated memory.
	 */
	अगर (bufOut.kptr != शून्य) अणु
		pci_मुक्त_consistent(ioc->pcidev,
			bufOut.len, (व्योम *) bufOut.kptr, dma_addr_out);
	पूर्ण

	अगर (bufIn.kptr != शून्य) अणु
		pci_मुक्त_consistent(ioc->pcidev,
			bufIn.len, (व्योम *) bufIn.kptr, dma_addr_in);
	पूर्ण

	/* mf is null अगर command issued successfully
	 * otherwise, failure occurred after mf acquired.
	 */
	अगर (mf)
		mpt_मुक्त_msg_frame(ioc, mf);

	वापस rc;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Prototype Routine क्रम the HOST INFO command.
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EFAULT अगर data unavailable
 *		-EBUSY  अगर previous command समयout and IOC reset is not complete.
 *		-ENODEV अगर no such device/adapter
 *		-ETIME	अगर समयr expires
 *		-ENOMEM अगर memory allocation error
 */
अटल पूर्णांक
mptctl_hp_hostinfo(MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg, अचिन्हित पूर्णांक data_size)
अणु
	hp_host_info_t	__user *uarg = (व्योम __user *) arg;
	काष्ठा pci_dev		*pdev;
	अक्षर                    *pbuf=शून्य;
	dma_addr_t		buf_dma;
	hp_host_info_t		karg;
	CONFIGPARMS		cfg;
	ConfigPageHeader_t	hdr;
	पूर्णांक			rc, cim_rev;
	ToolboxIstwiReadWriteRequest_t	*IstwiRWRequest;
	MPT_FRAME_HDR		*mf = शून्य;
	अचिन्हित दीर्घ		समयleft;
	पूर्णांक			retval;
	u32			msgcontext;

	/* Reset दीर्घ to पूर्णांक. Should affect IA64 and SPARC only
	 */
	अगर (data_size == माप(hp_host_info_t))
		cim_rev = 1;
	अन्यथा अगर (data_size == माप(hp_host_info_rev0_t))
		cim_rev = 0;	/* obsolete */
	अन्यथा
		वापस -EFAULT;

	अगर (copy_from_user(&karg, uarg, माप(hp_host_info_t))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_hp_host_info - "
			"Unable to read in hp_host_info struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT ": mptctl_hp_hostinfo called.\n",
	    ioc->name));

	/* Fill in the data and वापस the काष्ठाure to the calling
	 * program
	 */
	pdev = (काष्ठा pci_dev *) ioc->pcidev;

	karg.venकरोr = pdev->venकरोr;
	karg.device = pdev->device;
	karg.subप्रणाली_id = pdev->subप्रणाली_device;
	karg.subप्रणाली_venकरोr = pdev->subप्रणाली_venकरोr;
	karg.devfn = pdev->devfn;
	karg.bus = pdev->bus->number;

	/* Save the SCSI host no. अगर
	 * SCSI driver loaded
	 */
	अगर (ioc->sh != शून्य)
		karg.host_no = ioc->sh->host_no;
	अन्यथा
		karg.host_no =  -1;

	/* Reक्रमmat the fw_version पूर्णांकo a string */
	snम_लिखो(karg.fw_version, माप(karg.fw_version),
		 "%.2hhu.%.2hhu.%.2hhu.%.2hhu",
		 ioc->facts.FWVersion.Struct.Major,
		 ioc->facts.FWVersion.Struct.Minor,
		 ioc->facts.FWVersion.Struct.Unit,
		 ioc->facts.FWVersion.Struct.Dev);

	/* Issue a config request to get the device serial number
	 */
	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_MANUFACTURING;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = 0;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;	/* पढ़ो */
	cfg.समयout = 10;

	म_नकलन(karg.serial_number, " ", 24);
	अगर (mpt_config(ioc, &cfg) == 0) अणु
		अगर (cfg.cfghdr.hdr->PageLength > 0) अणु
			/* Issue the second config page request */
			cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

			pbuf = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4, &buf_dma);
			अगर (pbuf) अणु
				cfg.physAddr = buf_dma;
				अगर (mpt_config(ioc, &cfg) == 0) अणु
					ManufacturingPage0_t *pdata = (ManufacturingPage0_t *) pbuf;
					अगर (म_माप(pdata->BoardTracerNumber) > 1) अणु
						strlcpy(karg.serial_number,
							pdata->BoardTracerNumber, 24);
					पूर्ण
				पूर्ण
				pci_मुक्त_consistent(ioc->pcidev, hdr.PageLength * 4, pbuf, buf_dma);
				pbuf = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	rc = mpt_GetIocState(ioc, 1);
	चयन (rc) अणु
	हाल MPI_IOC_STATE_OPERATIONAL:
		karg.ioc_status =  HP_STATUS_OK;
		अवरोध;

	हाल MPI_IOC_STATE_FAULT:
		karg.ioc_status =  HP_STATUS_FAILED;
		अवरोध;

	हाल MPI_IOC_STATE_RESET:
	हाल MPI_IOC_STATE_READY:
	शेष:
		karg.ioc_status =  HP_STATUS_OTHER;
		अवरोध;
	पूर्ण

	karg.base_io_addr = pci_resource_start(pdev, 0);

	अगर ((ioc->bus_type == SAS) || (ioc->bus_type == FC))
		karg.bus_phys_width = HP_BUS_WIDTH_UNK;
	अन्यथा
		karg.bus_phys_width = HP_BUS_WIDTH_16;

	karg.hard_resets = 0;
	karg.soft_resets = 0;
	karg.समयouts = 0;
	अगर (ioc->sh != शून्य) अणु
		MPT_SCSI_HOST *hd =  shost_priv(ioc->sh);

		अगर (hd && (cim_rev == 1)) अणु
			karg.hard_resets = ioc->hard_resets;
			karg.soft_resets = ioc->soft_resets;
			karg.समयouts = ioc->समयouts;
		पूर्ण
	पूर्ण

	/* 
	 * Gather ISTWI(Industry Standard Two Wire Interface) Data
	 */
	अगर ((mf = mpt_get_msg_frame(mptctl_id, ioc)) == शून्य) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT
			"%s, no msg frames!!\n", ioc->name, __func__));
		जाओ out;
	पूर्ण

	IstwiRWRequest = (ToolboxIstwiReadWriteRequest_t *)mf;
	msgcontext = IstwiRWRequest->MsgContext;
	स_रखो(IstwiRWRequest,0,माप(ToolboxIstwiReadWriteRequest_t));
	IstwiRWRequest->MsgContext = msgcontext;
	IstwiRWRequest->Function = MPI_FUNCTION_TOOLBOX;
	IstwiRWRequest->Tool = MPI_TOOLBOX_ISTWI_READ_WRITE_TOOL;
	IstwiRWRequest->Flags = MPI_TB_ISTWI_FLAGS_READ;
	IstwiRWRequest->NumAddressBytes = 0x01;
	IstwiRWRequest->DataLength = cpu_to_le16(0x04);
	अगर (pdev->devfn & 1)
		IstwiRWRequest->DeviceAddr = 0xB2;
	अन्यथा
		IstwiRWRequest->DeviceAddr = 0xB0;

	pbuf = pci_alloc_consistent(ioc->pcidev, 4, &buf_dma);
	अगर (!pbuf)
		जाओ out;
	ioc->add_sge((अक्षर *)&IstwiRWRequest->SGL,
	    (MPT_SGE_FLAGS_SSIMPLE_READ|4), buf_dma);

	retval = 0;
	SET_MGMT_MSG_CONTEXT(ioc->ioctl_cmds.msg_context,
				IstwiRWRequest->MsgContext);
	INITIALIZE_MGMT_STATUS(ioc->ioctl_cmds.status)
	mpt_put_msg_frame(mptctl_id, ioc, mf);

retry_रुको:
	समयleft = रुको_क्रम_completion_समयout(&ioc->ioctl_cmds.करोne,
			HZ*MPT_IOCTL_DEFAULT_TIMEOUT);
	अगर (!(ioc->ioctl_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		retval = -ETIME;
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: failed\n", ioc->name, __func__);
		अगर (ioc->ioctl_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET) अणु
			mpt_मुक्त_msg_frame(ioc, mf);
			जाओ out;
		पूर्ण
		अगर (!समयleft) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
			       "HOST INFO command timeout, doorbell=0x%08x\n",
			       ioc->name, mpt_GetIocState(ioc, 0));
			mptctl_समयout_expired(ioc, mf);
		पूर्ण अन्यथा
			जाओ retry_रुको;
		जाओ out;
	पूर्ण

	/*
	 *ISTWI Data Definition
	 * pbuf[0] = FW_VERSION = 0x4
	 * pbuf[1] = Bay Count = 6 or 4 or 2, depending on
	 *  the config, you should be seeing one out of these three values
	 * pbuf[2] = Drive Installed Map = bit pattern depend on which
	 *   bays have drives in them
	 * pbuf[3] = Checksum (0x100 = (byte0 + byte2 + byte3)
	 */
	अगर (ioc->ioctl_cmds.status & MPT_MGMT_STATUS_RF_VALID)
		karg.rsvd = *(u32 *)pbuf;

 out:
	CLEAR_MGMT_STATUS(ioc->ioctl_cmds.status)
	SET_MGMT_MSG_CONTEXT(ioc->ioctl_cmds.msg_context, 0);

	अगर (pbuf)
		pci_मुक्त_consistent(ioc->pcidev, 4, pbuf, buf_dma);

	/* Copy the data from kernel memory to user memory
	 */
	अगर (copy_to_user((अक्षर __user *)arg, &karg, माप(hp_host_info_t))) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_hpgethostinfo - "
			"Unable to write out hp_host_info @ %p\n",
			ioc->name, __खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	वापस 0;

पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Prototype Routine क्रम the TARGET INFO command.
 *
 * Outमाला_दो:	None.
 * Return:	0 अगर successful
 *		-EFAULT अगर data unavailable
 *		-EBUSY  अगर previous command समयout and IOC reset is not complete.
 *		-ENODEV अगर no such device/adapter
 *		-ETIME	अगर समयr expires
 *		-ENOMEM अगर memory allocation error
 */
अटल पूर्णांक
mptctl_hp_targetinfo(MPT_ADAPTER *ioc, अचिन्हित दीर्घ arg)
अणु
	hp_target_info_t __user *uarg = (व्योम __user *) arg;
	SCSIDevicePage0_t	*pg0_alloc;
	SCSIDevicePage3_t	*pg3_alloc;
	MPT_SCSI_HOST 		*hd = शून्य;
	hp_target_info_t	karg;
	पूर्णांक			data_sz;
	dma_addr_t		page_dma;
	CONFIGPARMS	 	cfg;
	ConfigPageHeader_t	hdr;
	पूर्णांक			पंचांगp, np, rc = 0;

	अगर (copy_from_user(&karg, uarg, माप(hp_target_info_t))) अणु
		prपूर्णांकk(KERN_ERR MYNAM "%s@%d::mptctl_hp_targetinfo - "
			"Unable to read in hp_host_targetinfo struct @ %p\n",
				__खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	अगर (karg.hdr.id >= MPT_MAX_FC_DEVICES)
		वापस -EINVAL;
	dctlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mptctl_hp_targetinfo called.\n",
	    ioc->name));

	/*  There is nothing to करो क्रम FCP parts.
	 */
	अगर ((ioc->bus_type == SAS) || (ioc->bus_type == FC))
		वापस 0;

	अगर ((ioc->spi_data.sdp0length == 0) || (ioc->sh == शून्य))
		वापस 0;

	अगर (ioc->sh->host_no != karg.hdr.host)
		वापस -ENODEV;

       /* Get the data transfer speeds
        */
	data_sz = ioc->spi_data.sdp0length * 4;
	pg0_alloc = pci_alloc_consistent(ioc->pcidev, data_sz, &page_dma);
	अगर (pg0_alloc) अणु
		hdr.PageVersion = ioc->spi_data.sdp0version;
		hdr.PageLength = data_sz;
		hdr.PageNumber = 0;
		hdr.PageType = MPI_CONFIG_PAGETYPE_SCSI_DEVICE;

		cfg.cfghdr.hdr = &hdr;
		cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
		cfg.dir = 0;
		cfg.समयout = 0;
		cfg.physAddr = page_dma;

		cfg.pageAddr = (karg.hdr.channel << 8) | karg.hdr.id;

		अगर ((rc = mpt_config(ioc, &cfg)) == 0) अणु
			np = le32_to_cpu(pg0_alloc->NegotiatedParameters);
			karg.negotiated_width = np & MPI_SCSIDEVPAGE0_NP_WIDE ?
					HP_BUS_WIDTH_16 : HP_BUS_WIDTH_8;

			अगर (np & MPI_SCSIDEVPAGE0_NP_NEG_SYNC_OFFSET_MASK) अणु
				पंचांगp = (np & MPI_SCSIDEVPAGE0_NP_NEG_SYNC_PERIOD_MASK) >> 8;
				अगर (पंचांगp < 0x09)
					karg.negotiated_speed = HP_DEV_SPEED_ULTRA320;
				अन्यथा अगर (पंचांगp <= 0x09)
					karg.negotiated_speed = HP_DEV_SPEED_ULTRA160;
				अन्यथा अगर (पंचांगp <= 0x0A)
					karg.negotiated_speed = HP_DEV_SPEED_ULTRA2;
				अन्यथा अगर (पंचांगp <= 0x0C)
					karg.negotiated_speed = HP_DEV_SPEED_ULTRA;
				अन्यथा अगर (पंचांगp <= 0x25)
					karg.negotiated_speed = HP_DEV_SPEED_FAST;
				अन्यथा
					karg.negotiated_speed = HP_DEV_SPEED_ASYNC;
			पूर्ण अन्यथा
				karg.negotiated_speed = HP_DEV_SPEED_ASYNC;
		पूर्ण

		pci_मुक्त_consistent(ioc->pcidev, data_sz, (u8 *) pg0_alloc, page_dma);
	पूर्ण

	/* Set शेषs
	 */
	karg.message_rejects = -1;
	karg.phase_errors = -1;
	karg.parity_errors = -1;
	karg.select_समयouts = -1;

	/* Get the target error parameters
	 */
	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 3;
	hdr.PageType = MPI_CONFIG_PAGETYPE_SCSI_DEVICE;

	cfg.cfghdr.hdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.समयout = 0;
	cfg.physAddr = -1;
	अगर ((mpt_config(ioc, &cfg) == 0) && (cfg.cfghdr.hdr->PageLength > 0)) अणु
		/* Issue the second config page request */
		cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
		data_sz = (पूर्णांक) cfg.cfghdr.hdr->PageLength * 4;
		pg3_alloc = pci_alloc_consistent(ioc->pcidev, data_sz, &page_dma);
		अगर (pg3_alloc) अणु
			cfg.physAddr = page_dma;
			cfg.pageAddr = (karg.hdr.channel << 8) | karg.hdr.id;
			अगर ((rc = mpt_config(ioc, &cfg)) == 0) अणु
				karg.message_rejects = (u32) le16_to_cpu(pg3_alloc->MsgRejectCount);
				karg.phase_errors = (u32) le16_to_cpu(pg3_alloc->PhaseErrorCount);
				karg.parity_errors = (u32) le16_to_cpu(pg3_alloc->ParityErrorCount);
			पूर्ण
			pci_मुक्त_consistent(ioc->pcidev, data_sz, (u8 *) pg3_alloc, page_dma);
		पूर्ण
	पूर्ण
	hd = shost_priv(ioc->sh);
	अगर (hd != शून्य)
		karg.select_समयouts = hd->sel_समयout[karg.hdr.id];

	/* Copy the data from kernel memory to user memory
	 */
	अगर (copy_to_user((अक्षर __user *)arg, &karg, माप(hp_target_info_t))) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s@%d::mptctl_hp_target_info - "
			"Unable to write out mpt_ioctl_targetinfo struct @ %p\n",
			ioc->name, __खाता__, __LINE__, uarg);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

अटल स्थिर काष्ठा file_operations mptctl_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.fasync = 	mptctl_fasync,
	.unlocked_ioctl = mptctl_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = compat_mpctl_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा miscdevice mptctl_miscdev = अणु
	MPT_MINOR,
	MYNAM,
	&mptctl_fops
पूर्ण;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#अगर_घोषित CONFIG_COMPAT

अटल पूर्णांक
compat_mptfwxfer_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_fw_xfer32 kfw32;
	काष्ठा mpt_fw_xfer kfw;
	MPT_ADAPTER *iocp = शून्य;
	पूर्णांक iocnum, iocnumX;
	पूर्णांक nonblock = (filp->f_flags & O_NONBLOCK);
	पूर्णांक ret;


	अगर (copy_from_user(&kfw32, (अक्षर __user *)arg, माप(kfw32)))
		वापस -EFAULT;

	/* Verअगरy पूर्णांकended MPT adapter */
	iocnumX = kfw32.iocnum & 0xFF;
	अगर (((iocnum = mpt_verअगरy_adapter(iocnumX, &iocp)) < 0) ||
	    (iocp == शून्य)) अणु
		prपूर्णांकk(KERN_DEBUG MYNAM "::compat_mptfwxfer_ioctl @%d - ioc%d not found!\n",
			__LINE__, iocnumX);
		वापस -ENODEV;
	पूर्ण

	अगर ((ret = mptctl_syscall_करोwn(iocp, nonblock)) != 0)
		वापस ret;

	dctlprपूर्णांकk(iocp, prपूर्णांकk(MYIOC_s_DEBUG_FMT "compat_mptfwxfer_ioctl() called\n",
	    iocp->name));
	kfw.iocnum = iocnum;
	kfw.fwlen = kfw32.fwlen;
	kfw.bufp = compat_ptr(kfw32.bufp);

	ret = mptctl_करो_fw_करोwnload(iocp, kfw.bufp, kfw.fwlen);

	mutex_unlock(&iocp->ioctl_cmds.mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
compat_mpt_command(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा mpt_ioctl_command32 karg32;
	काष्ठा mpt_ioctl_command32 __user *uarg = (काष्ठा mpt_ioctl_command32 __user *) arg;
	काष्ठा mpt_ioctl_command karg;
	MPT_ADAPTER *iocp = शून्य;
	पूर्णांक iocnum, iocnumX;
	पूर्णांक nonblock = (filp->f_flags & O_NONBLOCK);
	पूर्णांक ret;

	अगर (copy_from_user(&karg32, (अक्षर __user *)arg, माप(karg32)))
		वापस -EFAULT;

	/* Verअगरy पूर्णांकended MPT adapter */
	iocnumX = karg32.hdr.iocnum & 0xFF;
	अगर (((iocnum = mpt_verअगरy_adapter(iocnumX, &iocp)) < 0) ||
	    (iocp == शून्य)) अणु
		prपूर्णांकk(KERN_DEBUG MYNAM "::compat_mpt_command @%d - ioc%d not found!\n",
			__LINE__, iocnumX);
		वापस -ENODEV;
	पूर्ण

	अगर ((ret = mptctl_syscall_करोwn(iocp, nonblock)) != 0)
		वापस ret;

	dctlprपूर्णांकk(iocp, prपूर्णांकk(MYIOC_s_DEBUG_FMT "compat_mpt_command() called\n",
	    iocp->name));
	/* Copy data to karg */
	karg.hdr.iocnum = karg32.hdr.iocnum;
	karg.hdr.port = karg32.hdr.port;
	karg.समयout = karg32.समयout;
	karg.maxReplyBytes = karg32.maxReplyBytes;

	karg.dataInSize = karg32.dataInSize;
	karg.dataOutSize = karg32.dataOutSize;
	karg.maxSenseBytes = karg32.maxSenseBytes;
	karg.dataSgeOffset = karg32.dataSgeOffset;

	karg.replyFrameBufPtr = (अक्षर __user *)(अचिन्हित दीर्घ)karg32.replyFrameBufPtr;
	karg.dataInBufPtr = (अक्षर __user *)(अचिन्हित दीर्घ)karg32.dataInBufPtr;
	karg.dataOutBufPtr = (अक्षर __user *)(अचिन्हित दीर्घ)karg32.dataOutBufPtr;
	karg.senseDataPtr = (अक्षर __user *)(अचिन्हित दीर्घ)karg32.senseDataPtr;

	/* Pass new काष्ठाure to करो_mpt_command
	 */
	ret = mptctl_करो_mpt_command (iocp, karg, &uarg->MF);

	mutex_unlock(&iocp->ioctl_cmds.mutex);

	वापस ret;
पूर्ण

अटल दीर्घ compat_mpctl_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;
	mutex_lock(&mpctl_mutex);
	चयन (cmd) अणु
	हाल MPTIOCINFO:
	हाल MPTIOCINFO1:
	हाल MPTIOCINFO2:
	हाल MPTTARGETINFO:
	हाल MPTEVENTQUERY:
	हाल MPTEVENTENABLE:
	हाल MPTEVENTREPORT:
	हाल MPTHARDRESET:
	हाल HP_GETHOSTINFO:
	हाल HP_GETTARGETINFO:
	हाल MPTTEST:
		ret = __mptctl_ioctl(f, cmd, arg);
		अवरोध;
	हाल MPTCOMMAND32:
		ret = compat_mpt_command(f, cmd, arg);
		अवरोध;
	हाल MPTFWDOWNLOAD32:
		ret = compat_mptfwxfer_ioctl(f, cmd, arg);
		अवरोध;
	शेष:
		ret = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	mutex_unlock(&mpctl_mutex);
	वापस ret;
पूर्ण

#पूर्ण_अगर


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptctl_probe - Installs ioctl devices per bus.
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 *
 */

अटल पूर्णांक
mptctl_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	MPT_ADAPTER *ioc = pci_get_drvdata(pdev);

	mutex_init(&ioc->ioctl_cmds.mutex);
	init_completion(&ioc->ioctl_cmds.करोne);
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptctl_हटाओ - Removed ioctl devices
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 *
 *
 */
अटल व्योम
mptctl_हटाओ(काष्ठा pci_dev *pdev)
अणु
पूर्ण

अटल काष्ठा mpt_pci_driver mptctl_driver = अणु
  .probe		= mptctl_probe,
  .हटाओ		= mptctl_हटाओ,
पूर्ण;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक __init mptctl_init(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक where = 1;

	show_mpपंचांगod_ver(my_NAME, my_VERSION);

	mpt_device_driver_रेजिस्टर(&mptctl_driver, MPTCTL_DRIVER);

	/* Register this device */
	err = misc_रेजिस्टर(&mptctl_miscdev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR MYNAM ": Can't register misc device [minor=%d].\n", MPT_MINOR);
		जाओ out_fail;
	पूर्ण
	prपूर्णांकk(KERN_INFO MYNAM ": Registered with Fusion MPT base driver\n");
	prपूर्णांकk(KERN_INFO MYNAM ": /dev/%s @ (major,minor=%d,%d)\n",
			 mptctl_miscdev.name, MISC_MAJOR, mptctl_miscdev.minor);

	/*
	 *  Install our handler
	 */
	++where;
	mptctl_id = mpt_रेजिस्टर(mptctl_reply, MPTCTL_DRIVER,
	    "mptctl_reply");
	अगर (!mptctl_id || mptctl_id >= MPT_MAX_PROTOCOL_DRIVERS) अणु
		prपूर्णांकk(KERN_ERR MYNAM ": ERROR: Failed to register with Fusion MPT base driver\n");
		misc_deरेजिस्टर(&mptctl_miscdev);
		err = -EBUSY;
		जाओ out_fail;
	पूर्ण

	mptctl_taskmgmt_id = mpt_रेजिस्टर(mptctl_taskmgmt_reply, MPTCTL_DRIVER,
	    "mptctl_taskmgmt_reply");
	अगर (!mptctl_taskmgmt_id || mptctl_taskmgmt_id >= MPT_MAX_PROTOCOL_DRIVERS) अणु
		prपूर्णांकk(KERN_ERR MYNAM ": ERROR: Failed to register with Fusion MPT base driver\n");
		mpt_deरेजिस्टर(mptctl_id);
		misc_deरेजिस्टर(&mptctl_miscdev);
		err = -EBUSY;
		जाओ out_fail;
	पूर्ण

	mpt_reset_रेजिस्टर(mptctl_id, mptctl_ioc_reset);
	mpt_event_रेजिस्टर(mptctl_id, mptctl_event_process);

	वापस 0;

out_fail:

	mpt_device_driver_deरेजिस्टर(MPTCTL_DRIVER);

	वापस err;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल व्योम mptctl_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&mptctl_miscdev);
	prपूर्णांकk(KERN_INFO MYNAM ": Deregistered /dev/%s @ (major,minor=%d,%d)\n",
			 mptctl_miscdev.name, MISC_MAJOR, mptctl_miscdev.minor);

	/* De-रेजिस्टर event handler from base module */
	mpt_event_deरेजिस्टर(mptctl_id);

	/* De-रेजिस्टर reset handler from base module */
	mpt_reset_deरेजिस्टर(mptctl_id);

	/* De-रेजिस्टर callback handler from base module */
	mpt_deरेजिस्टर(mptctl_taskmgmt_id);
	mpt_deरेजिस्टर(mptctl_id);

        mpt_device_driver_deरेजिस्टर(MPTCTL_DRIVER);

पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

module_init(mptctl_init);
module_निकास(mptctl_निकास);
