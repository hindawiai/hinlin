<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_ioctl.c
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
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
 *
 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#समावेश "esas2r.h"

/*
 * Buffered ioctl handlers.  A buffered ioctl is one which requires that we
 * allocate a DMA-able memory area to communicate with the firmware.  In
 * order to prevent continually allocating and मुक्तing consistent memory,
 * we will allocate a global buffer the first समय we need it and re-use
 * it क्रम subsequent ioctl calls that require it.
 */

u8 *esas2r_buffered_ioctl;
dma_addr_t esas2r_buffered_ioctl_addr;
u32 esas2r_buffered_ioctl_size;
काष्ठा pci_dev *esas2r_buffered_ioctl_pcid;

अटल DEFINE_SEMAPHORE(buffered_ioctl_semaphore);
प्रकार पूर्णांक (*BUFFERED_IOCTL_CALLBACK)(काष्ठा esas2r_adapter *,
				       काष्ठा esas2r_request *,
				       काष्ठा esas2r_sg_context *,
				       व्योम *);
प्रकार व्योम (*BUFFERED_IOCTL_DONE_CALLBACK)(काष्ठा esas2r_adapter *,
					     काष्ठा esas2r_request *, व्योम *);

काष्ठा esas2r_buffered_ioctl अणु
	काष्ठा esas2r_adapter *a;
	व्योम *ioctl;
	u32 length;
	u32 control_code;
	u32 offset;
	BUFFERED_IOCTL_CALLBACK
		callback;
	व्योम *context;
	BUFFERED_IOCTL_DONE_CALLBACK
		करोne_callback;
	व्योम *करोne_context;

पूर्ण;

अटल व्योम complete_fm_api_req(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq)
अणु
	a->fm_api_command_करोne = 1;
	wake_up_पूर्णांकerruptible(&a->fm_api_रुकोer);
पूर्ण

/* Callbacks क्रम building scatter/gather lists क्रम FM API requests */
अटल u32 get_physaddr_fm_api(काष्ठा esas2r_sg_context *sgc, u64 *addr)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)sgc->adapter;
	पूर्णांक offset = sgc->cur_offset - a->save_offset;

	(*addr) = a->firmware.phys + offset;
	वापस a->firmware.orig_len - offset;
पूर्ण

अटल u32 get_physaddr_fm_api_header(काष्ठा esas2r_sg_context *sgc, u64 *addr)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)sgc->adapter;
	पूर्णांक offset = sgc->cur_offset - a->save_offset;

	(*addr) = a->firmware.header_buff_phys + offset;
	वापस माप(काष्ठा esas2r_flash_img) - offset;
पूर्ण

/* Handle EXPRESS_IOCTL_RW_FIRMWARE ioctl with img_type = FW_IMG_FM_API. */
अटल व्योम करो_fm_api(काष्ठा esas2r_adapter *a, काष्ठा esas2r_flash_img *fi)
अणु
	काष्ठा esas2r_request *rq;

	अगर (mutex_lock_पूर्णांकerruptible(&a->fm_api_mutex)) अणु
		fi->status = FI_STAT_BUSY;
		वापस;
	पूर्ण

	rq = esas2r_alloc_request(a);
	अगर (rq == शून्य) अणु
		fi->status = FI_STAT_BUSY;
		जाओ मुक्त_sem;
	पूर्ण

	अगर (fi == &a->firmware.header) अणु
		a->firmware.header_buff = dma_alloc_coherent(&a->pcid->dev,
							     (माप_प्रकार)माप(
								     काष्ठा
								     esas2r_flash_img),
							     (dma_addr_t *)&a->
							     firmware.
							     header_buff_phys,
							     GFP_KERNEL);

		अगर (a->firmware.header_buff == शून्य) अणु
			esas2r_debug("failed to allocate header buffer!");
			fi->status = FI_STAT_BUSY;
			जाओ मुक्त_req;
		पूर्ण

		स_नकल(a->firmware.header_buff, fi,
		       माप(काष्ठा esas2r_flash_img));
		a->save_offset = a->firmware.header_buff;
		a->fm_api_sgc.get_phys_addr =
			(PGETPHYSADDR)get_physaddr_fm_api_header;
	पूर्ण अन्यथा अणु
		a->save_offset = (u8 *)fi;
		a->fm_api_sgc.get_phys_addr =
			(PGETPHYSADDR)get_physaddr_fm_api;
	पूर्ण

	rq->comp_cb = complete_fm_api_req;
	a->fm_api_command_करोne = 0;
	a->fm_api_sgc.cur_offset = a->save_offset;

	अगर (!esas2r_fm_api(a, (काष्ठा esas2r_flash_img *)a->save_offset, rq,
			   &a->fm_api_sgc))
		जाओ all_करोne;

	/* Now रुको around क्रम it to complete. */
	जबतक (!a->fm_api_command_करोne)
		रुको_event_पूर्णांकerruptible(a->fm_api_रुकोer,
					 a->fm_api_command_करोne);
all_करोne:
	अगर (fi == &a->firmware.header) अणु
		स_नकल(fi, a->firmware.header_buff,
		       माप(काष्ठा esas2r_flash_img));

		dma_मुक्त_coherent(&a->pcid->dev,
				  (माप_प्रकार)माप(काष्ठा esas2r_flash_img),
				  a->firmware.header_buff,
				  (dma_addr_t)a->firmware.header_buff_phys);
	पूर्ण
मुक्त_req:
	esas2r_मुक्त_request(a, (काष्ठा esas2r_request *)rq);
मुक्त_sem:
	mutex_unlock(&a->fm_api_mutex);
	वापस;

पूर्ण

अटल व्योम complete_nvr_req(काष्ठा esas2r_adapter *a,
			     काष्ठा esas2r_request *rq)
अणु
	a->nvram_command_करोne = 1;
	wake_up_पूर्णांकerruptible(&a->nvram_रुकोer);
पूर्ण

/* Callback क्रम building scatter/gather lists क्रम buffered ioctls */
अटल u32 get_physaddr_buffered_ioctl(काष्ठा esas2r_sg_context *sgc,
				       u64 *addr)
अणु
	पूर्णांक offset = (u8 *)sgc->cur_offset - esas2r_buffered_ioctl;

	(*addr) = esas2r_buffered_ioctl_addr + offset;
	वापस esas2r_buffered_ioctl_size - offset;
पूर्ण

अटल व्योम complete_buffered_ioctl_req(काष्ठा esas2r_adapter *a,
					काष्ठा esas2r_request *rq)
अणु
	a->buffered_ioctl_करोne = 1;
	wake_up_पूर्णांकerruptible(&a->buffered_ioctl_रुकोer);
पूर्ण

अटल u8 handle_buffered_ioctl(काष्ठा esas2r_buffered_ioctl *bi)
अणु
	काष्ठा esas2r_adapter *a = bi->a;
	काष्ठा esas2r_request *rq;
	काष्ठा esas2r_sg_context sgc;
	u8 result = IOCTL_SUCCESS;

	अगर (करोwn_पूर्णांकerruptible(&buffered_ioctl_semaphore))
		वापस IOCTL_OUT_OF_RESOURCES;

	/* allocate a buffer or use the existing buffer. */
	अगर (esas2r_buffered_ioctl) अणु
		अगर (esas2r_buffered_ioctl_size < bi->length) अणु
			/* मुक्त the too-small buffer and get a new one */
			dma_मुक्त_coherent(&a->pcid->dev,
					  (माप_प्रकार)esas2r_buffered_ioctl_size,
					  esas2r_buffered_ioctl,
					  esas2r_buffered_ioctl_addr);

			जाओ allocate_buffer;
		पूर्ण
	पूर्ण अन्यथा अणु
allocate_buffer:
		esas2r_buffered_ioctl_size = bi->length;
		esas2r_buffered_ioctl_pcid = a->pcid;
		esas2r_buffered_ioctl = dma_alloc_coherent(&a->pcid->dev,
							   (माप_प्रकार)
							   esas2r_buffered_ioctl_size,
							   &
							   esas2r_buffered_ioctl_addr,
							   GFP_KERNEL);
	पूर्ण

	अगर (!esas2r_buffered_ioctl) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "could not allocate %d bytes of consistent memory "
			   "for a buffered ioctl!",
			   bi->length);

		esas2r_debug("buffered ioctl alloc failure");
		result = IOCTL_OUT_OF_RESOURCES;
		जाओ निकास_cleanly;
	पूर्ण

	स_नकल(esas2r_buffered_ioctl, bi->ioctl, bi->length);

	rq = esas2r_alloc_request(a);
	अगर (rq == शून्य) अणु
		esas2r_log(ESAS2R_LOG_CRIT,
			   "could not allocate an internal request");

		result = IOCTL_OUT_OF_RESOURCES;
		esas2r_debug("buffered ioctl - no requests");
		जाओ निकास_cleanly;
	पूर्ण

	a->buffered_ioctl_करोne = 0;
	rq->comp_cb = complete_buffered_ioctl_req;
	sgc.cur_offset = esas2r_buffered_ioctl + bi->offset;
	sgc.get_phys_addr = (PGETPHYSADDR)get_physaddr_buffered_ioctl;
	sgc.length = esas2r_buffered_ioctl_size;

	अगर (!(*bi->callback)(a, rq, &sgc, bi->context)) अणु
		/* completed immediately, no need to रुको */
		a->buffered_ioctl_करोne = 0;
		जाओ मुक्त_andनिकास_cleanly;
	पूर्ण

	/* now रुको around क्रम it to complete. */
	जबतक (!a->buffered_ioctl_करोne)
		रुको_event_पूर्णांकerruptible(a->buffered_ioctl_रुकोer,
					 a->buffered_ioctl_करोne);

मुक्त_andनिकास_cleanly:
	अगर (result == IOCTL_SUCCESS && bi->करोne_callback)
		(*bi->करोne_callback)(a, rq, bi->करोne_context);

	esas2r_मुक्त_request(a, rq);

निकास_cleanly:
	अगर (result == IOCTL_SUCCESS)
		स_नकल(bi->ioctl, esas2r_buffered_ioctl, bi->length);

	up(&buffered_ioctl_semaphore);
	वापस result;
पूर्ण

/* SMP ioctl support */
अटल पूर्णांक smp_ioctl_callback(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_request *rq,
			      काष्ठा esas2r_sg_context *sgc, व्योम *context)
अणु
	काष्ठा atto_ioctl_smp *si =
		(काष्ठा atto_ioctl_smp *)esas2r_buffered_ioctl;

	esas2r_sgc_init(sgc, a, rq, rq->vrq->ioctl.sge);
	esas2r_build_ioctl_req(a, rq, sgc->length, VDA_IOCTL_SMP);

	अगर (!esas2r_build_sg_list(a, rq, sgc)) अणु
		si->status = ATTO_STS_OUT_OF_RSRC;
		वापस false;
	पूर्ण

	esas2r_start_request(a, rq);
	वापस true;
पूर्ण

अटल u8 handle_smp_ioctl(काष्ठा esas2r_adapter *a, काष्ठा atto_ioctl_smp *si)
अणु
	काष्ठा esas2r_buffered_ioctl bi;

	स_रखो(&bi, 0, माप(bi));

	bi.a = a;
	bi.ioctl = si;
	bi.length = माप(काष्ठा atto_ioctl_smp)
		    + le32_to_cpu(si->req_length)
		    + le32_to_cpu(si->rsp_length);
	bi.offset = 0;
	bi.callback = smp_ioctl_callback;
	वापस handle_buffered_ioctl(&bi);
पूर्ण


/* CSMI ioctl support */
अटल व्योम esas2r_csmi_ioctl_tunnel_comp_cb(काष्ठा esas2r_adapter *a,
					     काष्ठा esas2r_request *rq)
अणु
	rq->target_id = le16_to_cpu(rq->func_rsp.ioctl_rsp.csmi.target_id);
	rq->vrq->scsi.flags |= cpu_to_le32(rq->func_rsp.ioctl_rsp.csmi.lun);

	/* Now call the original completion callback. */
	(*rq->aux_req_cb)(a, rq);
पूर्ण

/* Tunnel a CSMI IOCTL to the back end driver क्रम processing. */
अटल bool csmi_ioctl_tunnel(काष्ठा esas2r_adapter *a,
			      जोड़ atto_ioctl_csmi *ci,
			      काष्ठा esas2r_request *rq,
			      काष्ठा esas2r_sg_context *sgc,
			      u32 ctrl_code,
			      u16 target_id)
अणु
	काष्ठा atto_vda_ioctl_req *ioctl = &rq->vrq->ioctl;

	अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
		वापस false;

	esas2r_sgc_init(sgc, a, rq, rq->vrq->ioctl.sge);
	esas2r_build_ioctl_req(a, rq, sgc->length, VDA_IOCTL_CSMI);
	ioctl->csmi.ctrl_code = cpu_to_le32(ctrl_code);
	ioctl->csmi.target_id = cpu_to_le16(target_id);
	ioctl->csmi.lun = (u8)le32_to_cpu(rq->vrq->scsi.flags);

	/*
	 * Always usurp the completion callback since the पूर्णांकerrupt callback
	 * mechanism may be used.
	 */
	rq->aux_req_cx = ci;
	rq->aux_req_cb = rq->comp_cb;
	rq->comp_cb = esas2r_csmi_ioctl_tunnel_comp_cb;

	अगर (!esas2r_build_sg_list(a, rq, sgc))
		वापस false;

	esas2r_start_request(a, rq);
	वापस true;
पूर्ण

अटल bool check_lun(काष्ठा scsi_lun lun)
अणु
	bool result;

	result = ((lun.scsi_lun[7] == 0) &&
		  (lun.scsi_lun[6] == 0) &&
		  (lun.scsi_lun[5] == 0) &&
		  (lun.scsi_lun[4] == 0) &&
		  (lun.scsi_lun[3] == 0) &&
		  (lun.scsi_lun[2] == 0) &&
/* Byte 1 is पूर्णांकentionally skipped */
		  (lun.scsi_lun[0] == 0));

	वापस result;
पूर्ण

अटल पूर्णांक csmi_ioctl_callback(काष्ठा esas2r_adapter *a,
			       काष्ठा esas2r_request *rq,
			       काष्ठा esas2r_sg_context *sgc, व्योम *context)
अणु
	काष्ठा atto_csmi *ci = (काष्ठा atto_csmi *)context;
	जोड़ atto_ioctl_csmi *ioctl_csmi =
		(जोड़ atto_ioctl_csmi *)esas2r_buffered_ioctl;
	u8 path = 0;
	u8 tid = 0;
	u8 lun = 0;
	u32 sts = CSMI_STS_SUCCESS;
	काष्ठा esas2r_target *t;
	अचिन्हित दीर्घ flags;

	अगर (ci->control_code == CSMI_CC_GET_DEV_ADDR) अणु
		काष्ठा atto_csmi_get_dev_addr *gda = &ci->data.dev_addr;

		path = gda->path_id;
		tid = gda->target_id;
		lun = gda->lun;
	पूर्ण अन्यथा अगर (ci->control_code == CSMI_CC_TASK_MGT) अणु
		काष्ठा atto_csmi_task_mgmt *पंचांग = &ci->data.tsk_mgt;

		path = पंचांग->path_id;
		tid = पंचांग->target_id;
		lun = पंचांग->lun;
	पूर्ण

	अगर (path > 0) अणु
		rq->func_rsp.ioctl_rsp.csmi.csmi_status = cpu_to_le32(
			CSMI_STS_INV_PARAM);
		वापस false;
	पूर्ण

	rq->target_id = tid;
	rq->vrq->scsi.flags |= cpu_to_le32(lun);

	चयन (ci->control_code) अणु
	हाल CSMI_CC_GET_DRVR_INFO:
	अणु
		काष्ठा atto_csmi_get_driver_info *gdi = &ioctl_csmi->drvr_info;

		म_नकल(gdi->description, esas2r_get_model_name(a));
		gdi->csmi_major_rev = CSMI_MAJOR_REV;
		gdi->csmi_minor_rev = CSMI_MINOR_REV;
		अवरोध;
	पूर्ण

	हाल CSMI_CC_GET_CNTLR_CFG:
	अणु
		काष्ठा atto_csmi_get_cntlr_cfg *gcc = &ioctl_csmi->cntlr_cfg;

		gcc->base_io_addr = 0;
		pci_पढ़ो_config_dword(a->pcid, PCI_BASE_ADDRESS_2,
				      &gcc->base_memaddr_lo);
		pci_पढ़ो_config_dword(a->pcid, PCI_BASE_ADDRESS_3,
				      &gcc->base_memaddr_hi);
		gcc->board_id = MAKEDWORD(a->pcid->subप्रणाली_device,
					  a->pcid->subप्रणाली_venकरोr);
		gcc->slot_num = CSMI_SLOT_NUM_UNKNOWN;
		gcc->cntlr_class = CSMI_CNTLR_CLASS_HBA;
		gcc->io_bus_type = CSMI_BUS_TYPE_PCI;
		gcc->pci_addr.bus_num = a->pcid->bus->number;
		gcc->pci_addr.device_num = PCI_SLOT(a->pcid->devfn);
		gcc->pci_addr.function_num = PCI_FUNC(a->pcid->devfn);

		स_रखो(gcc->serial_num, 0, माप(gcc->serial_num));

		gcc->major_rev = LOBYTE(LOWORD(a->fw_version));
		gcc->minor_rev = HIBYTE(LOWORD(a->fw_version));
		gcc->build_rev = LOBYTE(HIWORD(a->fw_version));
		gcc->release_rev = HIBYTE(HIWORD(a->fw_version));
		gcc->bios_major_rev = HIBYTE(HIWORD(a->flash_ver));
		gcc->bios_minor_rev = LOBYTE(HIWORD(a->flash_ver));
		gcc->bios_build_rev = LOWORD(a->flash_ver);

		अगर (test_bit(AF2_THUNDERLINK, &a->flags2))
			gcc->cntlr_flags = CSMI_CNTLRF_SAS_HBA
					   | CSMI_CNTLRF_SATA_HBA;
		अन्यथा
			gcc->cntlr_flags = CSMI_CNTLRF_SAS_RAID
					   | CSMI_CNTLRF_SATA_RAID;

		gcc->rrom_major_rev = 0;
		gcc->rrom_minor_rev = 0;
		gcc->rrom_build_rev = 0;
		gcc->rrom_release_rev = 0;
		gcc->rrom_biosmajor_rev = 0;
		gcc->rrom_biosminor_rev = 0;
		gcc->rrom_biosbuild_rev = 0;
		gcc->rrom_biosrelease_rev = 0;
		अवरोध;
	पूर्ण

	हाल CSMI_CC_GET_CNTLR_STS:
	अणु
		काष्ठा atto_csmi_get_cntlr_sts *gcs = &ioctl_csmi->cntlr_sts;

		अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
			gcs->status = CSMI_CNTLR_STS_FAILED;
		अन्यथा
			gcs->status = CSMI_CNTLR_STS_GOOD;

		gcs->offline_reason = CSMI_OFFLINE_NO_REASON;
		अवरोध;
	पूर्ण

	हाल CSMI_CC_FW_DOWNLOAD:
	हाल CSMI_CC_GET_RAID_INFO:
	हाल CSMI_CC_GET_RAID_CFG:

		sts = CSMI_STS_BAD_CTRL_CODE;
		अवरोध;

	हाल CSMI_CC_SMP_PASSTHRU:
	हाल CSMI_CC_SSP_PASSTHRU:
	हाल CSMI_CC_STP_PASSTHRU:
	हाल CSMI_CC_GET_PHY_INFO:
	हाल CSMI_CC_SET_PHY_INFO:
	हाल CSMI_CC_GET_LINK_ERRORS:
	हाल CSMI_CC_GET_SATA_SIG:
	हाल CSMI_CC_GET_CONN_INFO:
	हाल CSMI_CC_PHY_CTRL:

		अगर (!csmi_ioctl_tunnel(a, ioctl_csmi, rq, sgc,
				       ci->control_code,
				       ESAS2R_TARG_ID_INV)) अणु
			sts = CSMI_STS_FAILED;
			अवरोध;
		पूर्ण

		वापस true;

	हाल CSMI_CC_GET_SCSI_ADDR:
	अणु
		काष्ठा atto_csmi_get_scsi_addr *gsa = &ioctl_csmi->scsi_addr;

		काष्ठा scsi_lun lun;

		स_नकल(&lun, gsa->sas_lun, माप(काष्ठा scsi_lun));

		अगर (!check_lun(lun)) अणु
			sts = CSMI_STS_NO_SCSI_ADDR;
			अवरोध;
		पूर्ण

		/* make sure the device is present */
		spin_lock_irqsave(&a->mem_lock, flags);
		t = esas2r_targ_db_find_by_sas_addr(a, (u64 *)gsa->sas_addr);
		spin_unlock_irqrestore(&a->mem_lock, flags);

		अगर (t == शून्य) अणु
			sts = CSMI_STS_NO_SCSI_ADDR;
			अवरोध;
		पूर्ण

		gsa->host_index = 0xFF;
		gsa->lun = gsa->sas_lun[1];
		rq->target_id = esas2r_targ_get_id(t, a);
		अवरोध;
	पूर्ण

	हाल CSMI_CC_GET_DEV_ADDR:
	अणु
		काष्ठा atto_csmi_get_dev_addr *gda = &ioctl_csmi->dev_addr;

		/* make sure the target is present */
		t = a->targetdb + rq->target_id;

		अगर (t >= a->targetdb_end
		    || t->target_state != TS_PRESENT
		    || t->sas_addr == 0) अणु
			sts = CSMI_STS_NO_DEV_ADDR;
			अवरोध;
		पूर्ण

		/* fill in the result */
		*(u64 *)gda->sas_addr = t->sas_addr;
		स_रखो(gda->sas_lun, 0, माप(gda->sas_lun));
		gda->sas_lun[1] = (u8)le32_to_cpu(rq->vrq->scsi.flags);
		अवरोध;
	पूर्ण

	हाल CSMI_CC_TASK_MGT:

		/* make sure the target is present */
		t = a->targetdb + rq->target_id;

		अगर (t >= a->targetdb_end
		    || t->target_state != TS_PRESENT
		    || !(t->flags & TF_PASS_THRU)) अणु
			sts = CSMI_STS_NO_DEV_ADDR;
			अवरोध;
		पूर्ण

		अगर (!csmi_ioctl_tunnel(a, ioctl_csmi, rq, sgc,
				       ci->control_code,
				       t->phys_targ_id)) अणु
			sts = CSMI_STS_FAILED;
			अवरोध;
		पूर्ण

		वापस true;

	शेष:

		sts = CSMI_STS_BAD_CTRL_CODE;
		अवरोध;
	पूर्ण

	rq->func_rsp.ioctl_rsp.csmi.csmi_status = cpu_to_le32(sts);

	वापस false;
पूर्ण


अटल व्योम csmi_ioctl_करोne_callback(काष्ठा esas2r_adapter *a,
				     काष्ठा esas2r_request *rq, व्योम *context)
अणु
	काष्ठा atto_csmi *ci = (काष्ठा atto_csmi *)context;
	जोड़ atto_ioctl_csmi *ioctl_csmi =
		(जोड़ atto_ioctl_csmi *)esas2r_buffered_ioctl;

	चयन (ci->control_code) अणु
	हाल CSMI_CC_GET_DRVR_INFO:
	अणु
		काष्ठा atto_csmi_get_driver_info *gdi =
			&ioctl_csmi->drvr_info;

		म_नकल(gdi->name, ESAS2R_VERSION_STR);

		gdi->major_rev = ESAS2R_MAJOR_REV;
		gdi->minor_rev = ESAS2R_MINOR_REV;
		gdi->build_rev = 0;
		gdi->release_rev = 0;
		अवरोध;
	पूर्ण

	हाल CSMI_CC_GET_SCSI_ADDR:
	अणु
		काष्ठा atto_csmi_get_scsi_addr *gsa = &ioctl_csmi->scsi_addr;

		अगर (le32_to_cpu(rq->func_rsp.ioctl_rsp.csmi.csmi_status) ==
		    CSMI_STS_SUCCESS) अणु
			gsa->target_id = rq->target_id;
			gsa->path_id = 0;
		पूर्ण

		अवरोध;
	पूर्ण
	पूर्ण

	ci->status = le32_to_cpu(rq->func_rsp.ioctl_rsp.csmi.csmi_status);
पूर्ण


अटल u8 handle_csmi_ioctl(काष्ठा esas2r_adapter *a, काष्ठा atto_csmi *ci)
अणु
	काष्ठा esas2r_buffered_ioctl bi;

	स_रखो(&bi, 0, माप(bi));

	bi.a = a;
	bi.ioctl = &ci->data;
	bi.length = माप(जोड़ atto_ioctl_csmi);
	bi.offset = 0;
	bi.callback = csmi_ioctl_callback;
	bi.context = ci;
	bi.करोne_callback = csmi_ioctl_करोne_callback;
	bi.करोne_context = ci;

	वापस handle_buffered_ioctl(&bi);
पूर्ण

/* ATTO HBA ioctl support */

/* Tunnel an ATTO HBA IOCTL to the back end driver क्रम processing. */
अटल bool hba_ioctl_tunnel(काष्ठा esas2r_adapter *a,
			     काष्ठा atto_ioctl *hi,
			     काष्ठा esas2r_request *rq,
			     काष्ठा esas2r_sg_context *sgc)
अणु
	esas2r_sgc_init(sgc, a, rq, rq->vrq->ioctl.sge);

	esas2r_build_ioctl_req(a, rq, sgc->length, VDA_IOCTL_HBA);

	अगर (!esas2r_build_sg_list(a, rq, sgc)) अणु
		hi->status = ATTO_STS_OUT_OF_RSRC;

		वापस false;
	पूर्ण

	esas2r_start_request(a, rq);

	वापस true;
पूर्ण

अटल व्योम scsi_passthru_comp_cb(काष्ठा esas2r_adapter *a,
				  काष्ठा esas2r_request *rq)
अणु
	काष्ठा atto_ioctl *hi = (काष्ठा atto_ioctl *)rq->aux_req_cx;
	काष्ठा atto_hba_scsi_pass_thru *spt = &hi->data.scsi_pass_thru;
	u8 sts = ATTO_SPT_RS_FAILED;

	spt->scsi_status = rq->func_rsp.scsi_rsp.scsi_stat;
	spt->sense_length = rq->sense_len;
	spt->residual_length =
		le32_to_cpu(rq->func_rsp.scsi_rsp.residual_length);

	चयन (rq->req_stat) अणु
	हाल RS_SUCCESS:
	हाल RS_SCSI_ERROR:
		sts = ATTO_SPT_RS_SUCCESS;
		अवरोध;
	हाल RS_UNDERRUN:
		sts = ATTO_SPT_RS_UNDERRUN;
		अवरोध;
	हाल RS_OVERRUN:
		sts = ATTO_SPT_RS_OVERRUN;
		अवरोध;
	हाल RS_SEL:
	हाल RS_SEL2:
		sts = ATTO_SPT_RS_NO_DEVICE;
		अवरोध;
	हाल RS_NO_LUN:
		sts = ATTO_SPT_RS_NO_LUN;
		अवरोध;
	हाल RS_TIMEOUT:
		sts = ATTO_SPT_RS_TIMEOUT;
		अवरोध;
	हाल RS_DEGRADED:
		sts = ATTO_SPT_RS_DEGRADED;
		अवरोध;
	हाल RS_BUSY:
		sts = ATTO_SPT_RS_BUSY;
		अवरोध;
	हाल RS_ABORTED:
		sts = ATTO_SPT_RS_ABORTED;
		अवरोध;
	हाल RS_RESET:
		sts = ATTO_SPT_RS_BUS_RESET;
		अवरोध;
	पूर्ण

	spt->req_status = sts;

	/* Update the target ID to the next one present. */
	spt->target_id =
		esas2r_targ_db_find_next_present(a, (u16)spt->target_id);

	/* Done, call the completion callback. */
	(*rq->aux_req_cb)(a, rq);
पूर्ण

अटल पूर्णांक hba_ioctl_callback(काष्ठा esas2r_adapter *a,
			      काष्ठा esas2r_request *rq,
			      काष्ठा esas2r_sg_context *sgc,
			      व्योम *context)
अणु
	काष्ठा atto_ioctl *hi = (काष्ठा atto_ioctl *)esas2r_buffered_ioctl;

	hi->status = ATTO_STS_SUCCESS;

	चयन (hi->function) अणु
	हाल ATTO_FUNC_GET_ADAP_INFO:
	अणु
		u8 *class_code = (u8 *)&a->pcid->class;

		काष्ठा atto_hba_get_adapter_info *gai =
			&hi->data.get_adap_info;

		अगर (hi->flags & HBAF_TUNNEL) अणु
			hi->status = ATTO_STS_UNSUPPORTED;
			अवरोध;
		पूर्ण

		अगर (hi->version > ATTO_VER_GET_ADAP_INFO0) अणु
			hi->status = ATTO_STS_INV_VERSION;
			hi->version = ATTO_VER_GET_ADAP_INFO0;
			अवरोध;
		पूर्ण

		स_रखो(gai, 0, माप(*gai));

		gai->pci.venकरोr_id = a->pcid->venकरोr;
		gai->pci.device_id = a->pcid->device;
		gai->pci.ss_venकरोr_id = a->pcid->subप्रणाली_venकरोr;
		gai->pci.ss_device_id = a->pcid->subप्रणाली_device;
		gai->pci.class_code[0] = class_code[0];
		gai->pci.class_code[1] = class_code[1];
		gai->pci.class_code[2] = class_code[2];
		gai->pci.rev_id = a->pcid->revision;
		gai->pci.bus_num = a->pcid->bus->number;
		gai->pci.dev_num = PCI_SLOT(a->pcid->devfn);
		gai->pci.func_num = PCI_FUNC(a->pcid->devfn);

		अगर (pci_is_pcie(a->pcid)) अणु
			u16 stat;
			u32 caps;

			pcie_capability_पढ़ो_word(a->pcid, PCI_EXP_LNKSTA,
						  &stat);
			pcie_capability_पढ़ो_dword(a->pcid, PCI_EXP_LNKCAP,
						   &caps);

			gai->pci.link_speed_curr =
				(u8)(stat & PCI_EXP_LNKSTA_CLS);
			gai->pci.link_speed_max =
				(u8)(caps & PCI_EXP_LNKCAP_SLS);
			gai->pci.link_width_curr =
				(u8)((stat & PCI_EXP_LNKSTA_NLW)
				     >> PCI_EXP_LNKSTA_NLW_SHIFT);
			gai->pci.link_width_max =
				(u8)((caps & PCI_EXP_LNKCAP_MLW)
				     >> 4);
		पूर्ण

		gai->pci.msi_vector_cnt = 1;

		अगर (a->pcid->msix_enabled)
			gai->pci.पूर्णांकerrupt_mode = ATTO_GAI_PCIIM_MSIX;
		अन्यथा अगर (a->pcid->msi_enabled)
			gai->pci.पूर्णांकerrupt_mode = ATTO_GAI_PCIIM_MSI;
		अन्यथा
			gai->pci.पूर्णांकerrupt_mode = ATTO_GAI_PCIIM_LEGACY;

		gai->adap_type = ATTO_GAI_AT_ESASRAID2;

		अगर (test_bit(AF2_THUNDERLINK, &a->flags2))
			gai->adap_type = ATTO_GAI_AT_TLSASHBA;

		अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
			gai->adap_flags |= ATTO_GAI_AF_DEGRADED;

		gai->adap_flags |= ATTO_GAI_AF_SPT_SUPP |
				   ATTO_GAI_AF_DEVADDR_SUPP;

		अगर (a->pcid->subप्रणाली_device == ATTO_ESAS_R60F
		    || a->pcid->subप्रणाली_device == ATTO_ESAS_R608
		    || a->pcid->subप्रणाली_device == ATTO_ESAS_R644
		    || a->pcid->subप्रणाली_device == ATTO_TSSC_3808E)
			gai->adap_flags |= ATTO_GAI_AF_VIRT_SES;

		gai->num_ports = ESAS2R_NUM_PHYS;
		gai->num_phys = ESAS2R_NUM_PHYS;

		म_नकल(gai->firmware_rev, a->fw_rev);
		म_नकल(gai->flash_rev, a->flash_rev);
		म_नकल(gai->model_name_लघु, esas2r_get_model_name_लघु(a));
		म_नकल(gai->model_name, esas2r_get_model_name(a));

		gai->num_tarमाला_लो = ESAS2R_MAX_TARGETS;

		gai->num_busses = 1;
		gai->num_targsper_bus = gai->num_tarमाला_लो;
		gai->num_lunsper_targ = 256;

		अगर (a->pcid->subप्रणाली_device == ATTO_ESAS_R6F0
		    || a->pcid->subप्रणाली_device == ATTO_ESAS_R60F)
			gai->num_connectors = 4;
		अन्यथा
			gai->num_connectors = 2;

		gai->adap_flags2 |= ATTO_GAI_AF2_ADAP_CTRL_SUPP;

		gai->num_tarमाला_लो_backend = a->num_tarमाला_लो_backend;

		gai->tunnel_flags = a->ioctl_tunnel
				    & (ATTO_GAI_TF_MEM_RW
				       | ATTO_GAI_TF_TRACE
				       | ATTO_GAI_TF_SCSI_PASS_THRU
				       | ATTO_GAI_TF_GET_DEV_ADDR
				       | ATTO_GAI_TF_PHY_CTRL
				       | ATTO_GAI_TF_CONN_CTRL
				       | ATTO_GAI_TF_GET_DEV_INFO);
		अवरोध;
	पूर्ण

	हाल ATTO_FUNC_GET_ADAP_ADDR:
	अणु
		काष्ठा atto_hba_get_adapter_address *gaa =
			&hi->data.get_adap_addr;

		अगर (hi->flags & HBAF_TUNNEL) अणु
			hi->status = ATTO_STS_UNSUPPORTED;
			अवरोध;
		पूर्ण

		अगर (hi->version > ATTO_VER_GET_ADAP_ADDR0) अणु
			hi->status = ATTO_STS_INV_VERSION;
			hi->version = ATTO_VER_GET_ADAP_ADDR0;
		पूर्ण अन्यथा अगर (gaa->addr_type == ATTO_GAA_AT_PORT
			   || gaa->addr_type == ATTO_GAA_AT_NODE) अणु
			अगर (gaa->addr_type == ATTO_GAA_AT_PORT
			    && gaa->port_id >= ESAS2R_NUM_PHYS) अणु
				hi->status = ATTO_STS_NOT_APPL;
			पूर्ण अन्यथा अणु
				स_नकल((u64 *)gaa->address,
				       &a->nvram->sas_addr[0], माप(u64));
				gaa->addr_len = माप(u64);
			पूर्ण
		पूर्ण अन्यथा अणु
			hi->status = ATTO_STS_INV_PARAM;
		पूर्ण

		अवरोध;
	पूर्ण

	हाल ATTO_FUNC_MEM_RW:
	अणु
		अगर (hi->flags & HBAF_TUNNEL) अणु
			अगर (hba_ioctl_tunnel(a, hi, rq, sgc))
				वापस true;

			अवरोध;
		पूर्ण

		hi->status = ATTO_STS_UNSUPPORTED;

		अवरोध;
	पूर्ण

	हाल ATTO_FUNC_TRACE:
	अणु
		काष्ठा atto_hba_trace *trc = &hi->data.trace;

		अगर (hi->flags & HBAF_TUNNEL) अणु
			अगर (hba_ioctl_tunnel(a, hi, rq, sgc))
				वापस true;

			अवरोध;
		पूर्ण

		अगर (hi->version > ATTO_VER_TRACE1) अणु
			hi->status = ATTO_STS_INV_VERSION;
			hi->version = ATTO_VER_TRACE1;
			अवरोध;
		पूर्ण

		अगर (trc->trace_type == ATTO_TRC_TT_FWCOREDUMP
		    && hi->version >= ATTO_VER_TRACE1) अणु
			अगर (trc->trace_func == ATTO_TRC_TF_UPLOAD) अणु
				u32 len = hi->data_length;
				u32 offset = trc->current_offset;
				u32 total_len = ESAS2R_FWCOREDUMP_SZ;

				/* Size is zero अगर a core dump isn't present */
				अगर (!test_bit(AF2_COREDUMP_SAVED, &a->flags2))
					total_len = 0;

				अगर (len > total_len)
					len = total_len;

				अगर (offset >= total_len
				    || offset + len > total_len
				    || len == 0) अणु
					hi->status = ATTO_STS_INV_PARAM;
					अवरोध;
				पूर्ण

				स_नकल(trc + 1,
				       a->fw_coredump_buff + offset,
				       len);

				hi->data_length = len;
			पूर्ण अन्यथा अगर (trc->trace_func == ATTO_TRC_TF_RESET) अणु
				स_रखो(a->fw_coredump_buff, 0,
				       ESAS2R_FWCOREDUMP_SZ);

				clear_bit(AF2_COREDUMP_SAVED, &a->flags2);
			पूर्ण अन्यथा अगर (trc->trace_func != ATTO_TRC_TF_GET_INFO) अणु
				hi->status = ATTO_STS_UNSUPPORTED;
				अवरोध;
			पूर्ण

			/* Always वापस all the info we can. */
			trc->trace_mask = 0;
			trc->current_offset = 0;
			trc->total_length = ESAS2R_FWCOREDUMP_SZ;

			/* Return zero length buffer अगर core dump not present */
			अगर (!test_bit(AF2_COREDUMP_SAVED, &a->flags2))
				trc->total_length = 0;
		पूर्ण अन्यथा अणु
			hi->status = ATTO_STS_UNSUPPORTED;
		पूर्ण

		अवरोध;
	पूर्ण

	हाल ATTO_FUNC_SCSI_PASS_THRU:
	अणु
		काष्ठा atto_hba_scsi_pass_thru *spt = &hi->data.scsi_pass_thru;
		काष्ठा scsi_lun lun;

		स_नकल(&lun, spt->lun, माप(काष्ठा scsi_lun));

		अगर (hi->flags & HBAF_TUNNEL) अणु
			अगर (hba_ioctl_tunnel(a, hi, rq, sgc))
				वापस true;

			अवरोध;
		पूर्ण

		अगर (hi->version > ATTO_VER_SCSI_PASS_THRU0) अणु
			hi->status = ATTO_STS_INV_VERSION;
			hi->version = ATTO_VER_SCSI_PASS_THRU0;
			अवरोध;
		पूर्ण

		अगर (spt->target_id >= ESAS2R_MAX_TARGETS || !check_lun(lun)) अणु
			hi->status = ATTO_STS_INV_PARAM;
			अवरोध;
		पूर्ण

		esas2r_sgc_init(sgc, a, rq, शून्य);

		sgc->length = hi->data_length;
		sgc->cur_offset += दुरत्व(काष्ठा atto_ioctl, data.byte)
				   + माप(काष्ठा atto_hba_scsi_pass_thru);

		/* Finish request initialization */
		rq->target_id = (u16)spt->target_id;
		rq->vrq->scsi.flags |= cpu_to_le32(spt->lun[1]);
		स_नकल(rq->vrq->scsi.cdb, spt->cdb, 16);
		rq->vrq->scsi.length = cpu_to_le32(hi->data_length);
		rq->sense_len = spt->sense_length;
		rq->sense_buf = (u8 *)spt->sense_data;
		/* NOTE: we ignore spt->समयout */

		/*
		 * always usurp the completion callback since the पूर्णांकerrupt
		 * callback mechanism may be used.
		 */

		rq->aux_req_cx = hi;
		rq->aux_req_cb = rq->comp_cb;
		rq->comp_cb = scsi_passthru_comp_cb;

		अगर (spt->flags & ATTO_SPTF_DATA_IN) अणु
			rq->vrq->scsi.flags |= cpu_to_le32(FCP_CMND_RDD);
		पूर्ण अन्यथा अगर (spt->flags & ATTO_SPTF_DATA_OUT) अणु
			rq->vrq->scsi.flags |= cpu_to_le32(FCP_CMND_WRD);
		पूर्ण अन्यथा अणु
			अगर (sgc->length) अणु
				hi->status = ATTO_STS_INV_PARAM;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (spt->flags & ATTO_SPTF_ORDERED_Q)
			rq->vrq->scsi.flags |=
				cpu_to_le32(FCP_CMND_TA_ORDRD_Q);
		अन्यथा अगर (spt->flags & ATTO_SPTF_HEAD_OF_Q)
			rq->vrq->scsi.flags |= cpu_to_le32(FCP_CMND_TA_HEAD_Q);


		अगर (!esas2r_build_sg_list(a, rq, sgc)) अणु
			hi->status = ATTO_STS_OUT_OF_RSRC;
			अवरोध;
		पूर्ण

		esas2r_start_request(a, rq);

		वापस true;
	पूर्ण

	हाल ATTO_FUNC_GET_DEV_ADDR:
	अणु
		काष्ठा atto_hba_get_device_address *gda =
			&hi->data.get_dev_addr;
		काष्ठा esas2r_target *t;

		अगर (hi->flags & HBAF_TUNNEL) अणु
			अगर (hba_ioctl_tunnel(a, hi, rq, sgc))
				वापस true;

			अवरोध;
		पूर्ण

		अगर (hi->version > ATTO_VER_GET_DEV_ADDR0) अणु
			hi->status = ATTO_STS_INV_VERSION;
			hi->version = ATTO_VER_GET_DEV_ADDR0;
			अवरोध;
		पूर्ण

		अगर (gda->target_id >= ESAS2R_MAX_TARGETS) अणु
			hi->status = ATTO_STS_INV_PARAM;
			अवरोध;
		पूर्ण

		t = a->targetdb + (u16)gda->target_id;

		अगर (t->target_state != TS_PRESENT) अणु
			hi->status = ATTO_STS_FAILED;
		पूर्ण अन्यथा अगर (gda->addr_type == ATTO_GDA_AT_PORT) अणु
			अगर (t->sas_addr == 0) अणु
				hi->status = ATTO_STS_UNSUPPORTED;
			पूर्ण अन्यथा अणु
				*(u64 *)gda->address = t->sas_addr;

				gda->addr_len = माप(u64);
			पूर्ण
		पूर्ण अन्यथा अगर (gda->addr_type == ATTO_GDA_AT_NODE) अणु
			hi->status = ATTO_STS_NOT_APPL;
		पूर्ण अन्यथा अणु
			hi->status = ATTO_STS_INV_PARAM;
		पूर्ण

		/* update the target ID to the next one present. */

		gda->target_id =
			esas2r_targ_db_find_next_present(a,
							 (u16)gda->target_id);
		अवरोध;
	पूर्ण

	हाल ATTO_FUNC_PHY_CTRL:
	हाल ATTO_FUNC_CONN_CTRL:
	अणु
		अगर (hba_ioctl_tunnel(a, hi, rq, sgc))
			वापस true;

		अवरोध;
	पूर्ण

	हाल ATTO_FUNC_ADAP_CTRL:
	अणु
		काष्ठा atto_hba_adap_ctrl *ac = &hi->data.adap_ctrl;

		अगर (hi->flags & HBAF_TUNNEL) अणु
			hi->status = ATTO_STS_UNSUPPORTED;
			अवरोध;
		पूर्ण

		अगर (hi->version > ATTO_VER_ADAP_CTRL0) अणु
			hi->status = ATTO_STS_INV_VERSION;
			hi->version = ATTO_VER_ADAP_CTRL0;
			अवरोध;
		पूर्ण

		अगर (ac->adap_func == ATTO_AC_AF_HARD_RST) अणु
			esas2r_reset_adapter(a);
		पूर्ण अन्यथा अगर (ac->adap_func != ATTO_AC_AF_GET_STATE) अणु
			hi->status = ATTO_STS_UNSUPPORTED;
			अवरोध;
		पूर्ण

		अगर (test_bit(AF_CHPRST_NEEDED, &a->flags))
			ac->adap_state = ATTO_AC_AS_RST_SCHED;
		अन्यथा अगर (test_bit(AF_CHPRST_PENDING, &a->flags))
			ac->adap_state = ATTO_AC_AS_RST_IN_PROG;
		अन्यथा अगर (test_bit(AF_DISC_PENDING, &a->flags))
			ac->adap_state = ATTO_AC_AS_RST_DISC;
		अन्यथा अगर (test_bit(AF_DISABLED, &a->flags))
			ac->adap_state = ATTO_AC_AS_DISABLED;
		अन्यथा अगर (test_bit(AF_DEGRADED_MODE, &a->flags))
			ac->adap_state = ATTO_AC_AS_DEGRADED;
		अन्यथा
			ac->adap_state = ATTO_AC_AS_OK;

		अवरोध;
	पूर्ण

	हाल ATTO_FUNC_GET_DEV_INFO:
	अणु
		काष्ठा atto_hba_get_device_info *gdi = &hi->data.get_dev_info;
		काष्ठा esas2r_target *t;

		अगर (hi->flags & HBAF_TUNNEL) अणु
			अगर (hba_ioctl_tunnel(a, hi, rq, sgc))
				वापस true;

			अवरोध;
		पूर्ण

		अगर (hi->version > ATTO_VER_GET_DEV_INFO0) अणु
			hi->status = ATTO_STS_INV_VERSION;
			hi->version = ATTO_VER_GET_DEV_INFO0;
			अवरोध;
		पूर्ण

		अगर (gdi->target_id >= ESAS2R_MAX_TARGETS) अणु
			hi->status = ATTO_STS_INV_PARAM;
			अवरोध;
		पूर्ण

		t = a->targetdb + (u16)gdi->target_id;

		/* update the target ID to the next one present. */

		gdi->target_id =
			esas2r_targ_db_find_next_present(a,
							 (u16)gdi->target_id);

		अगर (t->target_state != TS_PRESENT) अणु
			hi->status = ATTO_STS_FAILED;
			अवरोध;
		पूर्ण

		hi->status = ATTO_STS_UNSUPPORTED;
		अवरोध;
	पूर्ण

	शेष:

		hi->status = ATTO_STS_INV_FUNC;
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hba_ioctl_करोne_callback(काष्ठा esas2r_adapter *a,
				    काष्ठा esas2r_request *rq, व्योम *context)
अणु
	काष्ठा atto_ioctl *ioctl_hba =
		(काष्ठा atto_ioctl *)esas2r_buffered_ioctl;

	esas2r_debug("hba_ioctl_done_callback %d", a->index);

	अगर (ioctl_hba->function == ATTO_FUNC_GET_ADAP_INFO) अणु
		काष्ठा atto_hba_get_adapter_info *gai =
			&ioctl_hba->data.get_adap_info;

		esas2r_debug("ATTO_FUNC_GET_ADAP_INFO");

		gai->drvr_rev_major = ESAS2R_MAJOR_REV;
		gai->drvr_rev_minor = ESAS2R_MINOR_REV;

		म_नकल(gai->drvr_rev_ascii, ESAS2R_VERSION_STR);
		म_नकल(gai->drvr_name, ESAS2R_DRVR_NAME);

		gai->num_busses = 1;
		gai->num_targsper_bus = ESAS2R_MAX_ID + 1;
		gai->num_lunsper_targ = 1;
	पूर्ण
पूर्ण

u8 handle_hba_ioctl(काष्ठा esas2r_adapter *a,
		    काष्ठा atto_ioctl *ioctl_hba)
अणु
	काष्ठा esas2r_buffered_ioctl bi;

	स_रखो(&bi, 0, माप(bi));

	bi.a = a;
	bi.ioctl = ioctl_hba;
	bi.length = माप(काष्ठा atto_ioctl) + ioctl_hba->data_length;
	bi.callback = hba_ioctl_callback;
	bi.context = शून्य;
	bi.करोne_callback = hba_ioctl_करोne_callback;
	bi.करोne_context = शून्य;
	bi.offset = 0;

	वापस handle_buffered_ioctl(&bi);
पूर्ण


पूर्णांक esas2r_ग_लिखो_params(काष्ठा esas2r_adapter *a, काष्ठा esas2r_request *rq,
			काष्ठा esas2r_sas_nvram *data)
अणु
	पूर्णांक result = 0;

	a->nvram_command_करोne = 0;
	rq->comp_cb = complete_nvr_req;

	अगर (esas2r_nvram_ग_लिखो(a, rq, data)) अणु
		/* now रुको around क्रम it to complete. */
		जबतक (!a->nvram_command_करोne)
			रुको_event_पूर्णांकerruptible(a->nvram_रुकोer,
						 a->nvram_command_करोne);
		;

		/* करोne, check the status. */
		अगर (rq->req_stat == RS_SUCCESS)
			result = 1;
	पूर्ण
	वापस result;
पूर्ण


/* This function only cares about ATTO-specअगरic ioctls (atto_express_ioctl) */
पूर्णांक esas2r_ioctl_handler(व्योम *hostdata, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा atto_express_ioctl *ioctl = शून्य;
	काष्ठा esas2r_adapter *a;
	काष्ठा esas2r_request *rq;
	u16 code;
	पूर्णांक err;

	esas2r_log(ESAS2R_LOG_DEBG, "ioctl (%p, %x, %p)", hostdata, cmd, arg);

	अगर ((arg == शून्य)
	    || (cmd < EXPRESS_IOCTL_MIN)
	    || (cmd > EXPRESS_IOCTL_MAX))
		वापस -ENOTSUPP;

	ioctl = memdup_user(arg, माप(काष्ठा atto_express_ioctl));
	अगर (IS_ERR(ioctl)) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "ioctl_handler access_ok failed for cmd %u, address %p",
			   cmd, arg);
		वापस PTR_ERR(ioctl);
	पूर्ण

	/* verअगरy the signature */

	अगर (स_भेद(ioctl->header.signature,
		   EXPRESS_IOCTL_SIGNATURE,
		   EXPRESS_IOCTL_SIGNATURE_SIZE) != 0) अणु
		esas2r_log(ESAS2R_LOG_WARN, "invalid signature");
		kमुक्त(ioctl);

		वापस -ENOTSUPP;
	पूर्ण

	/* assume success */

	ioctl->header.वापस_code = IOCTL_SUCCESS;
	err = 0;

	/*
	 * handle EXPRESS_IOCTL_GET_CHANNELS
	 * without paying attention to channel
	 */

	अगर (cmd == EXPRESS_IOCTL_GET_CHANNELS) अणु
		पूर्णांक i = 0, k = 0;

		ioctl->data.chanlist.num_channels = 0;

		जबतक (i < MAX_ADAPTERS) अणु
			अगर (esas2r_adapters[i]) अणु
				ioctl->data.chanlist.num_channels++;
				ioctl->data.chanlist.channel[k] = i;
				k++;
			पूर्ण
			i++;
		पूर्ण

		जाओ ioctl_करोne;
	पूर्ण

	/* get the channel */

	अगर (ioctl->header.channel == 0xFF) अणु
		a = (काष्ठा esas2r_adapter *)hostdata;
	पूर्ण अन्यथा अणु
		अगर (ioctl->header.channel >= MAX_ADAPTERS ||
			esas2r_adapters[ioctl->header.channel] == शून्य) अणु
			ioctl->header.वापस_code = IOCTL_BAD_CHANNEL;
			esas2r_log(ESAS2R_LOG_WARN, "bad channel value");
			kमुक्त(ioctl);

			वापस -ENOTSUPP;
		पूर्ण
		a = esas2r_adapters[ioctl->header.channel];
	पूर्ण

	चयन (cmd) अणु
	हाल EXPRESS_IOCTL_RW_FIRMWARE:

		अगर (ioctl->data.fwrw.img_type == FW_IMG_FM_API) अणु
			err = esas2r_ग_लिखो_fw(a,
					      (अक्षर *)ioctl->data.fwrw.image,
					      0,
					      माप(काष्ठा
						     atto_express_ioctl));

			अगर (err >= 0) अणु
				err = esas2r_पढ़ो_fw(a,
						     (अक्षर *)ioctl->data.fwrw.
						     image,
						     0,
						     माप(काष्ठा
							    atto_express_ioctl));
			पूर्ण
		पूर्ण अन्यथा अगर (ioctl->data.fwrw.img_type == FW_IMG_FS_API) अणु
			err = esas2r_ग_लिखो_fs(a,
					      (अक्षर *)ioctl->data.fwrw.image,
					      0,
					      माप(काष्ठा
						     atto_express_ioctl));

			अगर (err >= 0) अणु
				err = esas2r_पढ़ो_fs(a,
						     (अक्षर *)ioctl->data.fwrw.
						     image,
						     0,
						     माप(काष्ठा
							    atto_express_ioctl));
			पूर्ण
		पूर्ण अन्यथा अणु
			ioctl->header.वापस_code = IOCTL_BAD_FLASH_IMGTYPE;
		पूर्ण

		अवरोध;

	हाल EXPRESS_IOCTL_READ_PARAMS:

		स_नकल(ioctl->data.prw.data_buffer, a->nvram,
		       माप(काष्ठा esas2r_sas_nvram));
		ioctl->data.prw.code = 1;
		अवरोध;

	हाल EXPRESS_IOCTL_WRITE_PARAMS:

		rq = esas2r_alloc_request(a);
		अगर (rq == शून्य) अणु
			kमुक्त(ioctl);
			esas2r_log(ESAS2R_LOG_WARN,
			   "could not allocate an internal request");
			वापस -ENOMEM;
		पूर्ण

		code = esas2r_ग_लिखो_params(a, rq,
					   (काष्ठा esas2r_sas_nvram *)ioctl->data.prw.data_buffer);
		ioctl->data.prw.code = code;

		esas2r_मुक्त_request(a, rq);

		अवरोध;

	हाल EXPRESS_IOCTL_DEFAULT_PARAMS:

		esas2r_nvram_get_शेषs(a,
					  (काष्ठा esas2r_sas_nvram *)ioctl->data.prw.data_buffer);
		ioctl->data.prw.code = 1;
		अवरोध;

	हाल EXPRESS_IOCTL_CHAN_INFO:

		ioctl->data.chaninfo.major_rev = ESAS2R_MAJOR_REV;
		ioctl->data.chaninfo.minor_rev = ESAS2R_MINOR_REV;
		ioctl->data.chaninfo.IRQ = a->pcid->irq;
		ioctl->data.chaninfo.device_id = a->pcid->device;
		ioctl->data.chaninfo.venकरोr_id = a->pcid->venकरोr;
		ioctl->data.chaninfo.ven_dev_id = a->pcid->subप्रणाली_device;
		ioctl->data.chaninfo.revision_id = a->pcid->revision;
		ioctl->data.chaninfo.pci_bus = a->pcid->bus->number;
		ioctl->data.chaninfo.pci_dev_func = a->pcid->devfn;
		ioctl->data.chaninfo.core_rev = 0;
		ioctl->data.chaninfo.host_no = a->host->host_no;
		ioctl->data.chaninfo.hbaapi_rev = 0;
		अवरोध;

	हाल EXPRESS_IOCTL_SMP:
		ioctl->header.वापस_code = handle_smp_ioctl(a,
							     &ioctl->data.
							     ioctl_smp);
		अवरोध;

	हाल EXPRESS_CSMI:
		ioctl->header.वापस_code =
			handle_csmi_ioctl(a, &ioctl->data.csmi);
		अवरोध;

	हाल EXPRESS_IOCTL_HBA:
		ioctl->header.वापस_code = handle_hba_ioctl(a,
							     &ioctl->data.
							     ioctl_hba);
		अवरोध;

	हाल EXPRESS_IOCTL_VDA:
		err = esas2r_ग_लिखो_vda(a,
				       (अक्षर *)&ioctl->data.ioctl_vda,
				       0,
				       माप(काष्ठा atto_ioctl_vda) +
				       ioctl->data.ioctl_vda.data_length);

		अगर (err >= 0) अणु
			err = esas2r_पढ़ो_vda(a,
					      (अक्षर *)&ioctl->data.ioctl_vda,
					      0,
					      माप(काष्ठा atto_ioctl_vda) +
					      ioctl->data.ioctl_vda.data_length);
		पूर्ण




		अवरोध;

	हाल EXPRESS_IOCTL_GET_MOD_INFO:

		ioctl->data.modinfo.adapter = a;
		ioctl->data.modinfo.pci_dev = a->pcid;
		ioctl->data.modinfo.scsi_host = a->host;
		ioctl->data.modinfo.host_no = a->host->host_no;

		अवरोध;

	शेष:
		esas2r_debug("esas2r_ioctl invalid cmd %p!", cmd);
		ioctl->header.वापस_code = IOCTL_ERR_INVCMD;
	पूर्ण

ioctl_करोne:

	अगर (err < 0) अणु
		esas2r_log(ESAS2R_LOG_WARN, "err %d on ioctl cmd %u", err,
			   cmd);

		चयन (err) अणु
		हाल -ENOMEM:
		हाल -EBUSY:
			ioctl->header.वापस_code = IOCTL_OUT_OF_RESOURCES;
			अवरोध;

		हाल -ENOSYS:
		हाल -EINVAL:
			ioctl->header.वापस_code = IOCTL_INVALID_PARAM;
			अवरोध;

		शेष:
			ioctl->header.वापस_code = IOCTL_GENERAL_ERROR;
			अवरोध;
		पूर्ण

	पूर्ण

	/* Always copy the buffer back, अगर only to pick up the status */
	err = copy_to_user(arg, ioctl, माप(काष्ठा atto_express_ioctl));
	अगर (err != 0) अणु
		esas2r_log(ESAS2R_LOG_WARN,
			   "ioctl_handler copy_to_user didn't copy everything (err %d, cmd %u)",
			   err, cmd);
		kमुक्त(ioctl);

		वापस -EFAULT;
	पूर्ण

	kमुक्त(ioctl);

	वापस 0;
पूर्ण

पूर्णांक esas2r_ioctl(काष्ठा scsi_device *sd, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	वापस esas2r_ioctl_handler(sd->host->hostdata, cmd, arg);
पूर्ण

अटल व्योम मुक्त_fw_buffers(काष्ठा esas2r_adapter *a)
अणु
	अगर (a->firmware.data) अणु
		dma_मुक्त_coherent(&a->pcid->dev,
				  (माप_प्रकार)a->firmware.orig_len,
				  a->firmware.data,
				  (dma_addr_t)a->firmware.phys);

		a->firmware.data = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक allocate_fw_buffers(काष्ठा esas2r_adapter *a, u32 length)
अणु
	मुक्त_fw_buffers(a);

	a->firmware.orig_len = length;

	a->firmware.data = dma_alloc_coherent(&a->pcid->dev,
					      (माप_प्रकार)length,
					      (dma_addr_t *)&a->firmware.phys,
					      GFP_KERNEL);

	अगर (!a->firmware.data) अणु
		esas2r_debug("buffer alloc failed!");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* Handle a call to पढ़ो firmware. */
पूर्णांक esas2r_पढ़ो_fw(काष्ठा esas2r_adapter *a, अक्षर *buf, दीर्घ off, पूर्णांक count)
अणु
	esas2r_trace_enter();
	/* अगर the cached header is a status, simply copy it over and वापस. */
	अगर (a->firmware.state == FW_STATUS_ST) अणु
		पूर्णांक size = min_t(पूर्णांक, count, माप(a->firmware.header));
		esas2r_trace_निकास();
		स_नकल(buf, &a->firmware.header, size);
		esas2r_debug("esas2r_read_fw: STATUS size %d", size);
		वापस size;
	पूर्ण

	/*
	 * अगर the cached header is a command, करो it अगर at
	 * offset 0, otherwise copy the pieces.
	 */

	अगर (a->firmware.state == FW_COMMAND_ST) अणु
		u32 length = a->firmware.header.length;
		esas2r_trace_निकास();

		esas2r_debug("esas2r_read_fw: COMMAND length %d off %d",
			     length,
			     off);

		अगर (off == 0) अणु
			अगर (a->firmware.header.action == FI_ACT_UP) अणु
				अगर (!allocate_fw_buffers(a, length))
					वापस -ENOMEM;


				/* copy header over */

				स_नकल(a->firmware.data,
				       &a->firmware.header,
				       माप(a->firmware.header));

				करो_fm_api(a,
					  (काष्ठा esas2r_flash_img *)a->firmware.data);
			पूर्ण अन्यथा अगर (a->firmware.header.action == FI_ACT_UPSZ) अणु
				पूर्णांक size =
					min((पूर्णांक)count,
					    (पूर्णांक)माप(a->firmware.header));
				करो_fm_api(a, &a->firmware.header);
				स_नकल(buf, &a->firmware.header, size);
				esas2r_debug("FI_ACT_UPSZ size %d", size);
				वापस size;
			पूर्ण अन्यथा अणु
				esas2r_debug("invalid action %d",
					     a->firmware.header.action);
				वापस -ENOSYS;
			पूर्ण
		पूर्ण

		अगर (count + off > length)
			count = length - off;

		अगर (count < 0)
			वापस 0;

		अगर (!a->firmware.data) अणु
			esas2r_debug(
				"read: nonzero offset but no buffer available!");
			वापस -ENOMEM;
		पूर्ण

		esas2r_debug("esas2r_read_fw: off %d count %d length %d ", off,
			     count,
			     length);

		स_नकल(buf, &a->firmware.data[off], count);

		/* when करोne, release the buffer */

		अगर (length <= off + count) अणु
			esas2r_debug("esas2r_read_fw: freeing buffer!");

			मुक्त_fw_buffers(a);
		पूर्ण

		वापस count;
	पूर्ण

	esas2r_trace_निकास();
	esas2r_debug("esas2r_read_fw: invalid firmware state %d",
		     a->firmware.state);

	वापस -EINVAL;
पूर्ण

/* Handle a call to ग_लिखो firmware. */
पूर्णांक esas2r_ग_लिखो_fw(काष्ठा esas2r_adapter *a, स्थिर अक्षर *buf, दीर्घ off,
		    पूर्णांक count)
अणु
	u32 length;

	अगर (off == 0) अणु
		काष्ठा esas2r_flash_img *header =
			(काष्ठा esas2r_flash_img *)buf;

		/* assume version 0 flash image */

		पूर्णांक min_size = माप(काष्ठा esas2r_flash_img_v0);

		a->firmware.state = FW_INVALID_ST;

		/* validate the version field first */

		अगर (count < 4
		    ||  header->fi_version > FI_VERSION_1) अणु
			esas2r_debug(
				"esas2r_write_fw: short header or invalid version");
			वापस -EINVAL;
		पूर्ण

		/* See अगर its a version 1 flash image */

		अगर (header->fi_version == FI_VERSION_1)
			min_size = माप(काष्ठा esas2r_flash_img);

		/* If this is the start, the header must be full and valid. */
		अगर (count < min_size) अणु
			esas2r_debug("esas2r_write_fw: short header, aborting");
			वापस -EINVAL;
		पूर्ण

		/* Make sure the size is reasonable. */
		length = header->length;

		अगर (length > 1024 * 1024) अणु
			esas2r_debug(
				"esas2r_write_fw: hosed, length %d  fi_version %d",
				length, header->fi_version);
			वापस -EINVAL;
		पूर्ण

		/*
		 * If this is a ग_लिखो command, allocate memory because
		 * we have to cache everything. otherwise, just cache
		 * the header, because the पढ़ो op will करो the command.
		 */

		अगर (header->action == FI_ACT_DOWN) अणु
			अगर (!allocate_fw_buffers(a, length))
				वापस -ENOMEM;

			/*
			 * Store the command, so there is context on subsequent
			 * calls.
			 */
			स_नकल(&a->firmware.header,
			       buf,
			       माप(*header));
		पूर्ण अन्यथा अगर (header->action == FI_ACT_UP
			   ||  header->action == FI_ACT_UPSZ) अणु
			/* Save the command, result will be picked up on पढ़ो */
			स_नकल(&a->firmware.header,
			       buf,
			       माप(*header));

			a->firmware.state = FW_COMMAND_ST;

			esas2r_debug(
				"esas2r_write_fw: COMMAND, count %d, action %d ",
				count, header->action);

			/*
			 * Pretend we took the whole buffer,
			 * so we करोn't get bothered again.
			 */

			वापस count;
		पूर्ण अन्यथा अणु
			esas2r_debug("esas2r_write_fw: invalid action %d ",
				     a->firmware.header.action);
			वापस -ENOSYS;
		पूर्ण
	पूर्ण अन्यथा अणु
		length = a->firmware.header.length;
	पूर्ण

	/*
	 * We only get here on a करोwnload command, regardless of offset.
	 * the chunks written by the प्रणाली need to be cached, and when
	 * the final one arrives, issue the fmapi command.
	 */

	अगर (off + count > length)
		count = length - off;

	अगर (count > 0) अणु
		esas2r_debug("esas2r_write_fw: off %d count %d length %d", off,
			     count,
			     length);

		/*
		 * On a full upload, the प्रणाली tries sending the whole buffer.
		 * there's nothing to करो with it, so just drop it here, beक्रमe
		 * trying to copy over पूर्णांकo unallocated memory!
		 */
		अगर (a->firmware.header.action == FI_ACT_UP)
			वापस count;

		अगर (!a->firmware.data) अणु
			esas2r_debug(
				"write: nonzero offset but no buffer available!");
			वापस -ENOMEM;
		पूर्ण

		स_नकल(&a->firmware.data[off], buf, count);

		अगर (length == off + count) अणु
			करो_fm_api(a,
				  (काष्ठा esas2r_flash_img *)a->firmware.data);

			/*
			 * Now copy the header result to be picked up by the
			 * next पढ़ो
			 */
			स_नकल(&a->firmware.header,
			       a->firmware.data,
			       माप(a->firmware.header));

			a->firmware.state = FW_STATUS_ST;

			esas2r_debug("write completed");

			/*
			 * Since the प्रणाली has the data buffered, the only way
			 * this can leak is अगर a root user ग_लिखोs a program
			 * that ग_लिखोs a लघुer buffer than it claims, and the
			 * copyin fails.
			 */
			मुक्त_fw_buffers(a);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/* Callback क्रम the completion of a VDA request. */
अटल व्योम vda_complete_req(काष्ठा esas2r_adapter *a,
			     काष्ठा esas2r_request *rq)
अणु
	a->vda_command_करोne = 1;
	wake_up_पूर्णांकerruptible(&a->vda_रुकोer);
पूर्ण

/* Scatter/gather callback क्रम VDA requests */
अटल u32 get_physaddr_vda(काष्ठा esas2r_sg_context *sgc, u64 *addr)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)sgc->adapter;
	पूर्णांक offset = (u8 *)sgc->cur_offset - (u8 *)a->vda_buffer;

	(*addr) = a->ppvda_buffer + offset;
	वापस VDA_MAX_BUFFER_SIZE - offset;
पूर्ण

/* Handle a call to पढ़ो a VDA command. */
पूर्णांक esas2r_पढ़ो_vda(काष्ठा esas2r_adapter *a, अक्षर *buf, दीर्घ off, पूर्णांक count)
अणु
	अगर (!a->vda_buffer)
		वापस -ENOMEM;

	अगर (off == 0) अणु
		काष्ठा esas2r_request *rq;
		काष्ठा atto_ioctl_vda *vi =
			(काष्ठा atto_ioctl_vda *)a->vda_buffer;
		काष्ठा esas2r_sg_context sgc;
		bool रुको_क्रम_completion;

		/*
		 * Presumeably, someone has alपढ़ोy written to the vda_buffer,
		 * and now they are पढ़ोing the node the response, so now we
		 * will actually issue the request to the chip and reply.
		 */

		/* allocate a request */
		rq = esas2r_alloc_request(a);
		अगर (rq == शून्य) अणु
			esas2r_debug("esas2r_read_vda: out of requests");
			वापस -EBUSY;
		पूर्ण

		rq->comp_cb = vda_complete_req;

		sgc.first_req = rq;
		sgc.adapter = a;
		sgc.cur_offset = a->vda_buffer + VDA_BUFFER_HEADER_SZ;
		sgc.get_phys_addr = (PGETPHYSADDR)get_physaddr_vda;

		a->vda_command_करोne = 0;

		रुको_क्रम_completion =
			esas2r_process_vda_ioctl(a, vi, rq, &sgc);

		अगर (रुको_क्रम_completion) अणु
			/* now रुको around क्रम it to complete. */

			जबतक (!a->vda_command_करोne)
				रुको_event_पूर्णांकerruptible(a->vda_रुकोer,
							 a->vda_command_करोne);
		पूर्ण

		esas2r_मुक्त_request(a, (काष्ठा esas2r_request *)rq);
	पूर्ण

	अगर (off > VDA_MAX_BUFFER_SIZE)
		वापस 0;

	अगर (count + off > VDA_MAX_BUFFER_SIZE)
		count = VDA_MAX_BUFFER_SIZE - off;

	अगर (count < 0)
		वापस 0;

	स_नकल(buf, a->vda_buffer + off, count);

	वापस count;
पूर्ण

/* Handle a call to ग_लिखो a VDA command. */
पूर्णांक esas2r_ग_लिखो_vda(काष्ठा esas2r_adapter *a, स्थिर अक्षर *buf, दीर्घ off,
		     पूर्णांक count)
अणु
	/*
	 * allocate memory क्रम it, अगर not alपढ़ोy करोne.  once allocated,
	 * we will keep it around until the driver is unloaded.
	 */

	अगर (!a->vda_buffer) अणु
		dma_addr_t dma_addr;
		a->vda_buffer = dma_alloc_coherent(&a->pcid->dev,
						   (माप_प्रकार)
						   VDA_MAX_BUFFER_SIZE,
						   &dma_addr,
						   GFP_KERNEL);

		a->ppvda_buffer = dma_addr;
	पूर्ण

	अगर (!a->vda_buffer)
		वापस -ENOMEM;

	अगर (off > VDA_MAX_BUFFER_SIZE)
		वापस 0;

	अगर (count + off > VDA_MAX_BUFFER_SIZE)
		count = VDA_MAX_BUFFER_SIZE - off;

	अगर (count < 1)
		वापस 0;

	स_नकल(a->vda_buffer + off, buf, count);

	वापस count;
पूर्ण

/* Callback क्रम the completion of an FS_API request.*/
अटल व्योम fs_api_complete_req(काष्ठा esas2r_adapter *a,
				काष्ठा esas2r_request *rq)
अणु
	a->fs_api_command_करोne = 1;

	wake_up_पूर्णांकerruptible(&a->fs_api_रुकोer);
पूर्ण

/* Scatter/gather callback क्रम VDA requests */
अटल u32 get_physaddr_fs_api(काष्ठा esas2r_sg_context *sgc, u64 *addr)
अणु
	काष्ठा esas2r_adapter *a = (काष्ठा esas2r_adapter *)sgc->adapter;
	काष्ठा esas2r_ioctl_fs *fs =
		(काष्ठा esas2r_ioctl_fs *)a->fs_api_buffer;
	u32 offset = (u8 *)sgc->cur_offset - (u8 *)fs;

	(*addr) = a->ppfs_api_buffer + offset;

	वापस a->fs_api_buffer_size - offset;
पूर्ण

/* Handle a call to पढ़ो firmware via FS_API. */
पूर्णांक esas2r_पढ़ो_fs(काष्ठा esas2r_adapter *a, अक्षर *buf, दीर्घ off, पूर्णांक count)
अणु
	अगर (!a->fs_api_buffer)
		वापस -ENOMEM;

	अगर (off == 0) अणु
		काष्ठा esas2r_request *rq;
		काष्ठा esas2r_sg_context sgc;
		काष्ठा esas2r_ioctl_fs *fs =
			(काष्ठा esas2r_ioctl_fs *)a->fs_api_buffer;

		/* If another flash request is alपढ़ोy in progress, वापस. */
		अगर (mutex_lock_पूर्णांकerruptible(&a->fs_api_mutex)) अणु
busy:
			fs->status = ATTO_STS_OUT_OF_RSRC;
			वापस -EBUSY;
		पूर्ण

		/*
		 * Presumeably, someone has alपढ़ोy written to the
		 * fs_api_buffer, and now they are पढ़ोing the node the
		 * response, so now we will actually issue the request to the
		 * chip and reply. Allocate a request
		 */

		rq = esas2r_alloc_request(a);
		अगर (rq == शून्य) अणु
			esas2r_debug("esas2r_read_fs: out of requests");
			mutex_unlock(&a->fs_api_mutex);
			जाओ busy;
		पूर्ण

		rq->comp_cb = fs_api_complete_req;

		/* Set up the SGCONTEXT क्रम to build the s/g table */

		sgc.cur_offset = fs->data;
		sgc.get_phys_addr = (PGETPHYSADDR)get_physaddr_fs_api;

		a->fs_api_command_करोne = 0;

		अगर (!esas2r_process_fs_ioctl(a, fs, rq, &sgc)) अणु
			अगर (fs->status == ATTO_STS_OUT_OF_RSRC)
				count = -EBUSY;

			जाओ करोnt_रुको;
		पूर्ण

		/* Now रुको around क्रम it to complete. */

		जबतक (!a->fs_api_command_करोne)
			रुको_event_पूर्णांकerruptible(a->fs_api_रुकोer,
						 a->fs_api_command_करोne);
		;
करोnt_रुको:
		/* Free the request and keep going */
		mutex_unlock(&a->fs_api_mutex);
		esas2r_मुक्त_request(a, (काष्ठा esas2r_request *)rq);

		/* Pick up possible error code from above */
		अगर (count < 0)
			वापस count;
	पूर्ण

	अगर (off > a->fs_api_buffer_size)
		वापस 0;

	अगर (count + off > a->fs_api_buffer_size)
		count = a->fs_api_buffer_size - off;

	अगर (count < 0)
		वापस 0;

	स_नकल(buf, a->fs_api_buffer + off, count);

	वापस count;
पूर्ण

/* Handle a call to ग_लिखो firmware via FS_API. */
पूर्णांक esas2r_ग_लिखो_fs(काष्ठा esas2r_adapter *a, स्थिर अक्षर *buf, दीर्घ off,
		    पूर्णांक count)
अणु
	अगर (off == 0) अणु
		काष्ठा esas2r_ioctl_fs *fs = (काष्ठा esas2r_ioctl_fs *)buf;
		u32 length = fs->command.length + दुरत्व(
			काष्ठा esas2r_ioctl_fs,
			data);

		/*
		 * Special हाल, क्रम BEGIN commands, the length field
		 * is lying to us, so just get enough क्रम the header.
		 */

		अगर (fs->command.command == ESAS2R_FS_CMD_BEGINW)
			length = दुरत्व(काष्ठा esas2r_ioctl_fs, data);

		/*
		 * Beginning a command.  We assume we'll get at least
		 * enough in the first ग_लिखो so we can look at the
		 * header and see how much we need to alloc.
		 */

		अगर (count < दुरत्व(काष्ठा esas2r_ioctl_fs, data))
			वापस -EINVAL;

		/* Allocate a buffer or use the existing buffer. */
		अगर (a->fs_api_buffer) अणु
			अगर (a->fs_api_buffer_size < length) अणु
				/* Free too-small buffer and get a new one */
				dma_मुक्त_coherent(&a->pcid->dev,
						  (माप_प्रकार)a->fs_api_buffer_size,
						  a->fs_api_buffer,
						  (dma_addr_t)a->ppfs_api_buffer);

				जाओ re_allocate_buffer;
			पूर्ण
		पूर्ण अन्यथा अणु
re_allocate_buffer:
			a->fs_api_buffer_size = length;

			a->fs_api_buffer = dma_alloc_coherent(&a->pcid->dev,
							      (माप_प्रकार)a->fs_api_buffer_size,
							      (dma_addr_t *)&a->ppfs_api_buffer,
							      GFP_KERNEL);
		पूर्ण
	पूर्ण

	अगर (!a->fs_api_buffer)
		वापस -ENOMEM;

	अगर (off > a->fs_api_buffer_size)
		वापस 0;

	अगर (count + off > a->fs_api_buffer_size)
		count = a->fs_api_buffer_size - off;

	अगर (count < 1)
		वापस 0;

	स_नकल(a->fs_api_buffer + off, buf, count);

	वापस count;
पूर्ण
