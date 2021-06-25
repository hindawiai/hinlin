<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश "amdgpu.h"
#समावेश "nbio/nbio_2_3_offset.h"
#समावेश "nbio/nbio_2_3_sh_mask.h"
#समावेश "gc/gc_10_1_0_offset.h"
#समावेश "gc/gc_10_1_0_sh_mask.h"
#समावेश "soc15.h"
#समावेश "navi10_ih.h"
#समावेश "soc15_common.h"
#समावेश "mxgpu_nv.h"

अटल व्योम xgpu_nv_mailbox_send_ack(काष्ठा amdgpu_device *adev)
अणु
	WREG8(NV_MAIBOX_CONTROL_RCV_OFFSET_BYTE, 2);
पूर्ण

अटल व्योम xgpu_nv_mailbox_set_valid(काष्ठा amdgpu_device *adev, bool val)
अणु
	WREG8(NV_MAIBOX_CONTROL_TRN_OFFSET_BYTE, val ? 1 : 0);
पूर्ण

/*
 * this peek_msg could *only* be called in IRQ routine becuase in IRQ routine
 * RCV_MSG_VALID filed of BIF_BX_PF_MAILBOX_CONTROL must alपढ़ोy be set to 1
 * by host.
 *
 * अगर called no in IRQ routine, this peek_msg cannot guaranteed to वापस the
 * correct value since it करोesn't वापस the RCV_DW0 under the हाल that
 * RCV_MSG_VALID is set by host.
 */
अटल क्रमागत idh_event xgpu_nv_mailbox_peek_msg(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG32_NO_KIQ(mmMAILBOX_MSGBUF_RCV_DW0);
पूर्ण


अटल पूर्णांक xgpu_nv_mailbox_rcv_msg(काष्ठा amdgpu_device *adev,
				   क्रमागत idh_event event)
अणु
	u32 reg;

	reg = RREG32_NO_KIQ(mmMAILBOX_MSGBUF_RCV_DW0);
	अगर (reg != event)
		वापस -ENOENT;

	xgpu_nv_mailbox_send_ack(adev);

	वापस 0;
पूर्ण

अटल uपूर्णांक8_t xgpu_nv_peek_ack(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG8(NV_MAIBOX_CONTROL_TRN_OFFSET_BYTE) & 2;
पूर्ण

अटल पूर्णांक xgpu_nv_poll_ack(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक समयout  = NV_MAILBOX_POLL_ACK_TIMEDOUT;
	u8 reg;

	करो अणु
		reg = RREG8(NV_MAIBOX_CONTROL_TRN_OFFSET_BYTE);
		अगर (reg & 2)
			वापस 0;

		mdelay(5);
		समयout -= 5;
	पूर्ण जबतक (समयout > 1);

	pr_err("Doesn't get TRN_MSG_ACK from pf in %d msec\n", NV_MAILBOX_POLL_ACK_TIMEDOUT);

	वापस -ETIME;
पूर्ण

अटल पूर्णांक xgpu_nv_poll_msg(काष्ठा amdgpu_device *adev, क्रमागत idh_event event)
अणु
	पूर्णांक r, समयout = NV_MAILBOX_POLL_MSG_TIMEDOUT;

	करो अणु
		r = xgpu_nv_mailbox_rcv_msg(adev, event);
		अगर (!r)
			वापस 0;

		msleep(10);
		समयout -= 10;
	पूर्ण जबतक (समयout > 1);


	वापस -ETIME;
पूर्ण

अटल व्योम xgpu_nv_mailbox_trans_msg (काष्ठा amdgpu_device *adev,
	      क्रमागत idh_request req, u32 data1, u32 data2, u32 data3)
अणु
	पूर्णांक r;
	uपूर्णांक8_t trn;

	/* IMPORTANT:
	 * clear TRN_MSG_VALID valid to clear host's RCV_MSG_ACK
	 * and with host's RCV_MSG_ACK cleared hw automatically clear host's RCV_MSG_ACK
	 * which lead to VF's TRN_MSG_ACK cleared, otherwise below xgpu_nv_poll_ack()
	 * will वापस immediatly
	 */
	करो अणु
		xgpu_nv_mailbox_set_valid(adev, false);
		trn = xgpu_nv_peek_ack(adev);
		अगर (trn) अणु
			pr_err("trn=%x ACK should not assert! wait again !\n", trn);
			msleep(1);
		पूर्ण
	पूर्ण जबतक (trn);

	WREG32_NO_KIQ(mmMAILBOX_MSGBUF_TRN_DW0, req);
	WREG32_NO_KIQ(mmMAILBOX_MSGBUF_TRN_DW1, data1);
	WREG32_NO_KIQ(mmMAILBOX_MSGBUF_TRN_DW2, data2);
	WREG32_NO_KIQ(mmMAILBOX_MSGBUF_TRN_DW3, data3);
	xgpu_nv_mailbox_set_valid(adev, true);

	/* start to poll ack */
	r = xgpu_nv_poll_ack(adev);
	अगर (r)
		pr_err("Doesn't get ack from pf, continue\n");

	xgpu_nv_mailbox_set_valid(adev, false);
पूर्ण

अटल पूर्णांक xgpu_nv_send_access_requests(काष्ठा amdgpu_device *adev,
					क्रमागत idh_request req)
अणु
	पूर्णांक r;
	क्रमागत idh_event event = -1;

	xgpu_nv_mailbox_trans_msg(adev, req, 0, 0, 0);

	चयन (req) अणु
	हाल IDH_REQ_GPU_INIT_ACCESS:
	हाल IDH_REQ_GPU_FINI_ACCESS:
	हाल IDH_REQ_GPU_RESET_ACCESS:
		event = IDH_READY_TO_ACCESS_GPU;
		अवरोध;
	हाल IDH_REQ_GPU_INIT_DATA:
		event = IDH_REQ_GPU_INIT_DATA_READY;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (event != -1) अणु
		r = xgpu_nv_poll_msg(adev, event);
		अगर (r) अणु
			अगर (req != IDH_REQ_GPU_INIT_DATA) अणु
				pr_err("Doesn't get msg:%d from pf, error=%d\n", event, r);
				वापस r;
			पूर्ण
			अन्यथा /* host करोesn't support REQ_GPU_INIT_DATA handshake */
				adev->virt.req_init_data_ver = 0;
		पूर्ण अन्यथा अणु
			अगर (req == IDH_REQ_GPU_INIT_DATA)
			अणु
				adev->virt.req_init_data_ver =
					RREG32_NO_KIQ(mmMAILBOX_MSGBUF_RCV_DW1);

				/* assume V1 in हाल host करोesn't set version number */
				अगर (adev->virt.req_init_data_ver < 1)
					adev->virt.req_init_data_ver = 1;
			पूर्ण
		पूर्ण

		/* Retrieve checksum from mailbox2 */
		अगर (req == IDH_REQ_GPU_INIT_ACCESS || req == IDH_REQ_GPU_RESET_ACCESS) अणु
			adev->virt.fw_reserve.checksum_key =
				RREG32_NO_KIQ(mmMAILBOX_MSGBUF_RCV_DW2);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgpu_nv_request_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret, i = 0;

	जबतक (i < NV_MAILBOX_POLL_MSG_REP_MAX) अणु
		ret = xgpu_nv_send_access_requests(adev, IDH_REQ_GPU_RESET_ACCESS);
		अगर (!ret)
			अवरोध;
		i++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xgpu_nv_request_full_gpu_access(काष्ठा amdgpu_device *adev,
					   bool init)
अणु
	क्रमागत idh_request req;

	req = init ? IDH_REQ_GPU_INIT_ACCESS : IDH_REQ_GPU_FINI_ACCESS;
	वापस xgpu_nv_send_access_requests(adev, req);
पूर्ण

अटल पूर्णांक xgpu_nv_release_full_gpu_access(काष्ठा amdgpu_device *adev,
					   bool init)
अणु
	क्रमागत idh_request req;
	पूर्णांक r = 0;

	req = init ? IDH_REL_GPU_INIT_ACCESS : IDH_REL_GPU_FINI_ACCESS;
	r = xgpu_nv_send_access_requests(adev, req);

	वापस r;
पूर्ण

अटल पूर्णांक xgpu_nv_request_init_data(काष्ठा amdgpu_device *adev)
अणु
	वापस xgpu_nv_send_access_requests(adev, IDH_REQ_GPU_INIT_DATA);
पूर्ण

अटल पूर्णांक xgpu_nv_mailbox_ack_irq(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("get ack intr and do nothing.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक xgpu_nv_set_mailbox_ack_irq(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 पंचांगp = RREG32_NO_KIQ(mmMAILBOX_INT_CNTL);

	अगर (state == AMDGPU_IRQ_STATE_ENABLE)
		पंचांगp |= 2;
	अन्यथा
		पंचांगp &= ~2;

	WREG32_NO_KIQ(mmMAILBOX_INT_CNTL, पंचांगp);

	वापस 0;
पूर्ण

अटल व्योम xgpu_nv_mailbox_flr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_virt *virt = container_of(work, काष्ठा amdgpu_virt, flr_work);
	काष्ठा amdgpu_device *adev = container_of(virt, काष्ठा amdgpu_device, virt);
	पूर्णांक समयout = NV_MAILBOX_POLL_FLR_TIMEDOUT;

	/* block amdgpu_gpu_recover till msg FLR COMPLETE received,
	 * otherwise the mailbox msg will be ruined/reseted by
	 * the VF FLR.
	 */
	अगर (!करोwn_पढ़ो_trylock(&adev->reset_sem))
		वापस;

	amdgpu_virt_fini_data_exchange(adev);
	atomic_set(&adev->in_gpu_reset, 1);

	करो अणु
		अगर (xgpu_nv_mailbox_peek_msg(adev) == IDH_FLR_NOTIFICATION_CMPL)
			जाओ flr_करोne;

		msleep(10);
		समयout -= 10;
	पूर्ण जबतक (समयout > 1);

flr_करोne:
	atomic_set(&adev->in_gpu_reset, 0);
	up_पढ़ो(&adev->reset_sem);

	/* Trigger recovery क्रम world चयन failure अगर no TDR */
	अगर (amdgpu_device_should_recover_gpu(adev)
		&& (!amdgpu_device_has_job_running(adev) ||
		adev->sdma_समयout == MAX_SCHEDULE_TIMEOUT ||
		adev->gfx_समयout == MAX_SCHEDULE_TIMEOUT ||
		adev->compute_समयout == MAX_SCHEDULE_TIMEOUT ||
		adev->video_समयout == MAX_SCHEDULE_TIMEOUT))
		amdgpu_device_gpu_recover(adev, शून्य);
पूर्ण

अटल पूर्णांक xgpu_nv_set_mailbox_rcv_irq(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_irq_src *src,
				       अचिन्हित type,
				       क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 पंचांगp = RREG32_NO_KIQ(mmMAILBOX_INT_CNTL);

	अगर (state == AMDGPU_IRQ_STATE_ENABLE)
		पंचांगp |= 1;
	अन्यथा
		पंचांगp &= ~1;

	WREG32_NO_KIQ(mmMAILBOX_INT_CNTL, पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक xgpu_nv_mailbox_rcv_irq(काष्ठा amdgpu_device *adev,
				   काष्ठा amdgpu_irq_src *source,
				   काष्ठा amdgpu_iv_entry *entry)
अणु
	क्रमागत idh_event event = xgpu_nv_mailbox_peek_msg(adev);

	चयन (event) अणु
	हाल IDH_FLR_NOTIFICATION:
		अगर (amdgpu_sriov_runसमय(adev))
			schedule_work(&adev->virt.flr_work);
		अवरोध;
		/* READY_TO_ACCESS_GPU is fetched by kernel polling, IRQ can ignore
		 * it byfar since that polling thपढ़ो will handle it,
		 * other msg like flr complete is not handled here.
		 */
	हाल IDH_CLR_MSG_BUF:
	हाल IDH_FLR_NOTIFICATION_CMPL:
	हाल IDH_READY_TO_ACCESS_GPU:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs xgpu_nv_mailbox_ack_irq_funcs = अणु
	.set = xgpu_nv_set_mailbox_ack_irq,
	.process = xgpu_nv_mailbox_ack_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs xgpu_nv_mailbox_rcv_irq_funcs = अणु
	.set = xgpu_nv_set_mailbox_rcv_irq,
	.process = xgpu_nv_mailbox_rcv_irq,
पूर्ण;

व्योम xgpu_nv_mailbox_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->virt.ack_irq.num_types = 1;
	adev->virt.ack_irq.funcs = &xgpu_nv_mailbox_ack_irq_funcs;
	adev->virt.rcv_irq.num_types = 1;
	adev->virt.rcv_irq.funcs = &xgpu_nv_mailbox_rcv_irq_funcs;
पूर्ण

पूर्णांक xgpu_nv_mailbox_add_irq_id(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_BIF, 135, &adev->virt.rcv_irq);
	अगर (r)
		वापस r;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_BIF, 138, &adev->virt.ack_irq);
	अगर (r) अणु
		amdgpu_irq_put(adev, &adev->virt.rcv_irq, 0);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक xgpu_nv_mailbox_get_irq(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	r = amdgpu_irq_get(adev, &adev->virt.rcv_irq, 0);
	अगर (r)
		वापस r;
	r = amdgpu_irq_get(adev, &adev->virt.ack_irq, 0);
	अगर (r) अणु
		amdgpu_irq_put(adev, &adev->virt.rcv_irq, 0);
		वापस r;
	पूर्ण

	INIT_WORK(&adev->virt.flr_work, xgpu_nv_mailbox_flr_work);

	वापस 0;
पूर्ण

व्योम xgpu_nv_mailbox_put_irq(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_irq_put(adev, &adev->virt.ack_irq, 0);
	amdgpu_irq_put(adev, &adev->virt.rcv_irq, 0);
पूर्ण

स्थिर काष्ठा amdgpu_virt_ops xgpu_nv_virt_ops = अणु
	.req_full_gpu	= xgpu_nv_request_full_gpu_access,
	.rel_full_gpu	= xgpu_nv_release_full_gpu_access,
	.req_init_data  = xgpu_nv_request_init_data,
	.reset_gpu = xgpu_nv_request_reset,
	.रुको_reset = शून्य,
	.trans_msg = xgpu_nv_mailbox_trans_msg,
पूर्ण;
