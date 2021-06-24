<शैली गुरु>
/*
 * Copyright 2016-2018 Advanced Micro Devices, Inc.
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
 */

#समावेश "kfd_priv.h"
#समावेश "kfd_events.h"
#समावेश "soc15_int.h"
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_smi_events.h"
#समावेश "amdgpu.h"

क्रमागत SQ_INTERRUPT_WORD_ENCODING अणु
	SQ_INTERRUPT_WORD_ENCODING_AUTO = 0x0,
	SQ_INTERRUPT_WORD_ENCODING_INST,
	SQ_INTERRUPT_WORD_ENCODING_ERROR,
पूर्ण;

क्रमागत SQ_INTERRUPT_ERROR_TYPE अणु
	SQ_INTERRUPT_ERROR_TYPE_EDC_FUE = 0x0,
	SQ_INTERRUPT_ERROR_TYPE_ILLEGAL_INST,
	SQ_INTERRUPT_ERROR_TYPE_MEMVIOL,
	SQ_INTERRUPT_ERROR_TYPE_EDC_FED,
पूर्ण;

/* SQ_INTERRUPT_WORD_AUTO_CTXID */
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__THREAD_TRACE__SHIFT 0
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__WLT__SHIFT 1
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__THREAD_TRACE_BUF_FULL__SHIFT 2
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__REG_TIMESTAMP__SHIFT 3
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__CMD_TIMESTAMP__SHIFT 4
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__HOST_CMD_OVERFLOW__SHIFT 5
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__HOST_REG_OVERFLOW__SHIFT 6
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__IMMED_OVERFLOW__SHIFT 7
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__THREAD_TRACE_UTC_ERROR__SHIFT 8
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__SE_ID__SHIFT 24
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__ENCODING__SHIFT 26

#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__THREAD_TRACE_MASK 0x00000001
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__WLT_MASK 0x00000002
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__THREAD_TRACE_BUF_FULL_MASK 0x00000004
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__REG_TIMESTAMP_MASK 0x00000008
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__CMD_TIMESTAMP_MASK 0x00000010
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__HOST_CMD_OVERFLOW_MASK 0x00000020
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__HOST_REG_OVERFLOW_MASK 0x00000040
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__IMMED_OVERFLOW_MASK 0x00000080
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__THREAD_TRACE_UTC_ERROR_MASK 0x00000100
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__SE_ID_MASK 0x03000000
#घोषणा SQ_INTERRUPT_WORD_AUTO_CTXID__ENCODING_MASK 0x0c000000

/* SQ_INTERRUPT_WORD_WAVE_CTXID */
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__DATA__SHIFT 0
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__SH_ID__SHIFT 12
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__PRIV__SHIFT 13
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__WAVE_ID__SHIFT 14
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__SIMD_ID__SHIFT 18
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__CU_ID__SHIFT 20
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__SE_ID__SHIFT 24
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__ENCODING__SHIFT 26

#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__DATA_MASK 0x00000fff
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__SH_ID_MASK 0x00001000
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__PRIV_MASK 0x00002000
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__WAVE_ID_MASK 0x0003c000
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__SIMD_ID_MASK 0x000c0000
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__CU_ID_MASK 0x00f00000
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__SE_ID_MASK 0x03000000
#घोषणा SQ_INTERRUPT_WORD_WAVE_CTXID__ENCODING_MASK 0x0c000000

#घोषणा KFD_CONTEXT_ID_GET_SQ_INT_DATA(ctx0, ctx1)                             \
	((ctx0 & 0xfff) | ((ctx0 >> 16) & 0xf000) | ((ctx1 << 16) & 0xff0000))

#घोषणा KFD_SQ_INT_DATA__ERR_TYPE_MASK 0xF00000
#घोषणा KFD_SQ_INT_DATA__ERR_TYPE__SHIFT 20

अटल bool event_पूर्णांकerrupt_isr_v9(काष्ठा kfd_dev *dev,
					स्थिर uपूर्णांक32_t *ih_ring_entry,
					uपूर्णांक32_t *patched_ihre,
					bool *patched_flag)
अणु
	uपूर्णांक16_t source_id, client_id, pasid, vmid;
	स्थिर uपूर्णांक32_t *data = ih_ring_entry;

	/* Only handle पूर्णांकerrupts from KFD VMIDs */
	vmid = SOC15_VMID_FROM_IH_ENTRY(ih_ring_entry);
	अगर (vmid < dev->vm_info.first_vmid_kfd ||
	    vmid > dev->vm_info.last_vmid_kfd)
		वापस false;

	source_id = SOC15_SOURCE_ID_FROM_IH_ENTRY(ih_ring_entry);
	client_id = SOC15_CLIENT_ID_FROM_IH_ENTRY(ih_ring_entry);
	pasid = SOC15_PASID_FROM_IH_ENTRY(ih_ring_entry);

	/* Only handle clients we care about */
	अगर (client_id != SOC15_IH_CLIENTID_GRBM_CP &&
	    client_id != SOC15_IH_CLIENTID_SDMA0 &&
	    client_id != SOC15_IH_CLIENTID_SDMA1 &&
	    client_id != SOC15_IH_CLIENTID_SDMA2 &&
	    client_id != SOC15_IH_CLIENTID_SDMA3 &&
	    client_id != SOC15_IH_CLIENTID_SDMA4 &&
	    client_id != SOC15_IH_CLIENTID_SDMA5 &&
	    client_id != SOC15_IH_CLIENTID_SDMA6 &&
	    client_id != SOC15_IH_CLIENTID_SDMA7 &&
	    client_id != SOC15_IH_CLIENTID_VMC &&
	    client_id != SOC15_IH_CLIENTID_VMC1 &&
	    client_id != SOC15_IH_CLIENTID_UTCL2 &&
	    client_id != SOC15_IH_CLIENTID_SE0SH &&
	    client_id != SOC15_IH_CLIENTID_SE1SH &&
	    client_id != SOC15_IH_CLIENTID_SE2SH &&
	    client_id != SOC15_IH_CLIENTID_SE3SH)
		वापस false;

	/* This is a known issue क्रम gfx9. Under non HWS, pasid is not set
	 * in the पूर्णांकerrupt payload, so we need to find out the pasid on our
	 * own.
	 */
	अगर (!pasid && dev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS) अणु
		स्थिर uपूर्णांक32_t pasid_mask = 0xffff;

		*patched_flag = true;
		स_नकल(patched_ihre, ih_ring_entry,
				dev->device_info->ih_ring_entry_size);

		pasid = dev->dqm->vmid_pasid[vmid];

		/* Patch the pasid field */
		patched_ihre[3] = cpu_to_le32((le32_to_cpu(patched_ihre[3])
					& ~pasid_mask) | pasid);
	पूर्ण

	pr_debug("client id 0x%x, source id %d, vmid %d, pasid 0x%x. raw data:\n",
		 client_id, source_id, vmid, pasid);
	pr_debug("%8X, %8X, %8X, %8X, %8X, %8X, %8X, %8X.\n",
		 data[0], data[1], data[2], data[3],
		 data[4], data[5], data[6], data[7]);

	/* If there is no valid PASID, it's likely a bug */
	अगर (WARN_ONCE(pasid == 0, "Bug: No PASID in KFD interrupt"))
		वापस false;

	/* Interrupt types we care about: various संकेतs and faults.
	 * They will be क्रमwarded to a work queue (see below).
	 */
	वापस source_id == SOC15_INTSRC_CP_END_OF_PIPE ||
		source_id == SOC15_INTSRC_SDMA_TRAP ||
		source_id == SOC15_INTSRC_SQ_INTERRUPT_MSG ||
		source_id == SOC15_INTSRC_CP_BAD_OPCODE ||
		((client_id == SOC15_IH_CLIENTID_VMC ||
		client_id == SOC15_IH_CLIENTID_VMC1 ||
		client_id == SOC15_IH_CLIENTID_UTCL2) &&
		!amdgpu_no_queue_eviction_on_vm_fault);
पूर्ण

अटल व्योम event_पूर्णांकerrupt_wq_v9(काष्ठा kfd_dev *dev,
					स्थिर uपूर्णांक32_t *ih_ring_entry)
अणु
	uपूर्णांक16_t source_id, client_id, pasid, vmid;
	uपूर्णांक32_t context_id0, context_id1;
	uपूर्णांक32_t sq_पूर्णांकr_err, sq_पूर्णांक_data, encoding;

	source_id = SOC15_SOURCE_ID_FROM_IH_ENTRY(ih_ring_entry);
	client_id = SOC15_CLIENT_ID_FROM_IH_ENTRY(ih_ring_entry);
	pasid = SOC15_PASID_FROM_IH_ENTRY(ih_ring_entry);
	vmid = SOC15_VMID_FROM_IH_ENTRY(ih_ring_entry);
	context_id0 = SOC15_CONTEXT_ID0_FROM_IH_ENTRY(ih_ring_entry);
	context_id1 = SOC15_CONTEXT_ID1_FROM_IH_ENTRY(ih_ring_entry);

	अगर (client_id == SOC15_IH_CLIENTID_GRBM_CP ||
	    client_id == SOC15_IH_CLIENTID_SE0SH ||
	    client_id == SOC15_IH_CLIENTID_SE1SH ||
	    client_id == SOC15_IH_CLIENTID_SE2SH ||
	    client_id == SOC15_IH_CLIENTID_SE3SH) अणु
		अगर (source_id == SOC15_INTSRC_CP_END_OF_PIPE)
			kfd_संकेत_event_पूर्णांकerrupt(pasid, context_id0, 32);
		अन्यथा अगर (source_id == SOC15_INTSRC_SQ_INTERRUPT_MSG) अणु
			sq_पूर्णांक_data = KFD_CONTEXT_ID_GET_SQ_INT_DATA(context_id0, context_id1);
			encoding = REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, ENCODING);
			चयन (encoding) अणु
			हाल SQ_INTERRUPT_WORD_ENCODING_AUTO:
				pr_debug(
					"sq_intr: auto, se %d, ttrace %d, wlt %d, ttrac_buf_full %d, reg_tms %d, cmd_tms %d, host_cmd_ovf %d, host_reg_ovf %d, immed_ovf %d, ttrace_utc_err %d\n",
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, SE_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, THREAD_TRACE),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, WLT),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, THREAD_TRACE_BUF_FULL),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, REG_TIMESTAMP),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, CMD_TIMESTAMP),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, HOST_CMD_OVERFLOW),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, HOST_REG_OVERFLOW),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, IMMED_OVERFLOW),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_AUTO_CTXID, THREAD_TRACE_UTC_ERROR));
				अवरोध;
			हाल SQ_INTERRUPT_WORD_ENCODING_INST:
				pr_debug("sq_intr: inst, se %d, data 0x%x, sh %d, priv %d, wave_id %d, simd_id %d, cu_id %d, intr_data 0x%x\n",
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, SE_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, DATA),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, SH_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, PRIV),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, WAVE_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, SIMD_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, CU_ID),
					sq_पूर्णांक_data);
				अवरोध;
			हाल SQ_INTERRUPT_WORD_ENCODING_ERROR:
				sq_पूर्णांकr_err = REG_GET_FIELD(sq_पूर्णांक_data, KFD_SQ_INT_DATA, ERR_TYPE);
				pr_warn("sq_intr: error, se %d, data 0x%x, sh %d, priv %d, wave_id %d, simd_id %d, cu_id %d, err_type %d\n",
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, SE_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, DATA),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, SH_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, PRIV),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, WAVE_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, SIMD_ID),
					REG_GET_FIELD(context_id0, SQ_INTERRUPT_WORD_WAVE_CTXID, CU_ID),
					sq_पूर्णांकr_err);
				अगर (sq_पूर्णांकr_err != SQ_INTERRUPT_ERROR_TYPE_ILLEGAL_INST &&
					sq_पूर्णांकr_err != SQ_INTERRUPT_ERROR_TYPE_MEMVIOL) अणु
					kfd_संकेत_hw_exception_event(pasid);
					amdgpu_amdkfd_gpu_reset(dev->kgd);
					वापस;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			kfd_संकेत_event_पूर्णांकerrupt(pasid, context_id0 & 0xffffff, 24);
		पूर्ण अन्यथा अगर (source_id == SOC15_INTSRC_CP_BAD_OPCODE)
			kfd_संकेत_hw_exception_event(pasid);
	पूर्ण अन्यथा अगर (client_id == SOC15_IH_CLIENTID_SDMA0 ||
		   client_id == SOC15_IH_CLIENTID_SDMA1 ||
		   client_id == SOC15_IH_CLIENTID_SDMA2 ||
		   client_id == SOC15_IH_CLIENTID_SDMA3 ||
		   client_id == SOC15_IH_CLIENTID_SDMA4 ||
		   client_id == SOC15_IH_CLIENTID_SDMA5 ||
		   client_id == SOC15_IH_CLIENTID_SDMA6 ||
		   client_id == SOC15_IH_CLIENTID_SDMA7) अणु
		अगर (source_id == SOC15_INTSRC_SDMA_TRAP)
			kfd_संकेत_event_पूर्णांकerrupt(pasid, context_id0 & 0xfffffff, 28);
	पूर्ण अन्यथा अगर (client_id == SOC15_IH_CLIENTID_VMC ||
		   client_id == SOC15_IH_CLIENTID_VMC1 ||
		   client_id == SOC15_IH_CLIENTID_UTCL2) अणु
		काष्ठा kfd_vm_fault_info info = अणु0पूर्ण;
		uपूर्णांक16_t ring_id = SOC15_RING_ID_FROM_IH_ENTRY(ih_ring_entry);

		info.vmid = vmid;
		info.mc_id = client_id;
		info.page_addr = ih_ring_entry[4] |
			(uपूर्णांक64_t)(ih_ring_entry[5] & 0xf) << 32;
		info.prot_valid = ring_id & 0x08;
		info.prot_पढ़ो  = ring_id & 0x10;
		info.prot_ग_लिखो = ring_id & 0x20;

		kfd_smi_event_update_vmfault(dev, pasid);
		kfd_process_vm_fault(dev->dqm, pasid);
		kfd_संकेत_vm_fault_event(dev, pasid, &info);
	पूर्ण
पूर्ण

स्थिर काष्ठा kfd_event_पूर्णांकerrupt_class event_पूर्णांकerrupt_class_v9 = अणु
	.पूर्णांकerrupt_isr = event_पूर्णांकerrupt_isr_v9,
	.पूर्णांकerrupt_wq = event_पूर्णांकerrupt_wq_v9,
पूर्ण;
