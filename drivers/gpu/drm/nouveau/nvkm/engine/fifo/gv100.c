<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश "gk104.h"
#समावेश "cgrp.h"
#समावेश "changk104.h"
#समावेश "user.h"

#समावेश <core/gpuobj.h>

#समावेश <nvअगर/class.h>

व्योम
gv100_fअगरo_runlist_chan(काष्ठा gk104_fअगरo_chan *chan,
			काष्ठा nvkm_memory *memory, u32 offset)
अणु
	काष्ठा nvkm_memory *usermem = chan->fअगरo->user.mem;
	स्थिर u64 user = nvkm_memory_addr(usermem) + (chan->base.chid * 0x200);
	स्थिर u64 inst = chan->base.inst->addr;

	nvkm_wo32(memory, offset + 0x0, lower_32_bits(user));
	nvkm_wo32(memory, offset + 0x4, upper_32_bits(user));
	nvkm_wo32(memory, offset + 0x8, lower_32_bits(inst) | chan->base.chid);
	nvkm_wo32(memory, offset + 0xc, upper_32_bits(inst));
पूर्ण

व्योम
gv100_fअगरo_runlist_cgrp(काष्ठा nvkm_fअगरo_cgrp *cgrp,
			काष्ठा nvkm_memory *memory, u32 offset)
अणु
	nvkm_wo32(memory, offset + 0x0, (128 << 24) | (3 << 16) | 0x00000001);
	nvkm_wo32(memory, offset + 0x4, cgrp->chan_nr);
	nvkm_wo32(memory, offset + 0x8, cgrp->id);
	nvkm_wo32(memory, offset + 0xc, 0x00000000);
पूर्ण

स्थिर काष्ठा gk104_fअगरo_runlist_func
gv100_fअगरo_runlist = अणु
	.size = 16,
	.cgrp = gv100_fअगरo_runlist_cgrp,
	.chan = gv100_fअगरo_runlist_chan,
	.commit = gk104_fअगरo_runlist_commit,
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gv100_fअगरo_fault_gpcclient[] = अणु
	अणु 0x00, "T1_0" पूर्ण,
	अणु 0x01, "T1_1" पूर्ण,
	अणु 0x02, "T1_2" पूर्ण,
	अणु 0x03, "T1_3" पूर्ण,
	अणु 0x04, "T1_4" पूर्ण,
	अणु 0x05, "T1_5" पूर्ण,
	अणु 0x06, "T1_6" पूर्ण,
	अणु 0x07, "T1_7" पूर्ण,
	अणु 0x08, "PE_0" पूर्ण,
	अणु 0x09, "PE_1" पूर्ण,
	अणु 0x0a, "PE_2" पूर्ण,
	अणु 0x0b, "PE_3" पूर्ण,
	अणु 0x0c, "PE_4" पूर्ण,
	अणु 0x0d, "PE_5" पूर्ण,
	अणु 0x0e, "PE_6" पूर्ण,
	अणु 0x0f, "PE_7" पूर्ण,
	अणु 0x10, "RAST" पूर्ण,
	अणु 0x11, "GCC" पूर्ण,
	अणु 0x12, "GPCCS" पूर्ण,
	अणु 0x13, "PROP_0" पूर्ण,
	अणु 0x14, "PROP_1" पूर्ण,
	अणु 0x15, "PROP_2" पूर्ण,
	अणु 0x16, "PROP_3" पूर्ण,
	अणु 0x17, "GPM" पूर्ण,
	अणु 0x18, "LTP_UTLB_0" पूर्ण,
	अणु 0x19, "LTP_UTLB_1" पूर्ण,
	अणु 0x1a, "LTP_UTLB_2" पूर्ण,
	अणु 0x1b, "LTP_UTLB_3" पूर्ण,
	अणु 0x1c, "LTP_UTLB_4" पूर्ण,
	अणु 0x1d, "LTP_UTLB_5" पूर्ण,
	अणु 0x1e, "LTP_UTLB_6" पूर्ण,
	अणु 0x1f, "LTP_UTLB_7" पूर्ण,
	अणु 0x20, "RGG_UTLB" पूर्ण,
	अणु 0x21, "T1_8" पूर्ण,
	अणु 0x22, "T1_9" पूर्ण,
	अणु 0x23, "T1_10" पूर्ण,
	अणु 0x24, "T1_11" पूर्ण,
	अणु 0x25, "T1_12" पूर्ण,
	अणु 0x26, "T1_13" पूर्ण,
	अणु 0x27, "T1_14" पूर्ण,
	अणु 0x28, "T1_15" पूर्ण,
	अणु 0x29, "TPCCS_0" पूर्ण,
	अणु 0x2a, "TPCCS_1" पूर्ण,
	अणु 0x2b, "TPCCS_2" पूर्ण,
	अणु 0x2c, "TPCCS_3" पूर्ण,
	अणु 0x2d, "TPCCS_4" पूर्ण,
	अणु 0x2e, "TPCCS_5" पूर्ण,
	अणु 0x2f, "TPCCS_6" पूर्ण,
	अणु 0x30, "TPCCS_7" पूर्ण,
	अणु 0x31, "PE_8" पूर्ण,
	अणु 0x32, "PE_9" पूर्ण,
	अणु 0x33, "TPCCS_8" पूर्ण,
	अणु 0x34, "TPCCS_9" पूर्ण,
	अणु 0x35, "T1_16" पूर्ण,
	अणु 0x36, "T1_17" पूर्ण,
	अणु 0x37, "T1_18" पूर्ण,
	अणु 0x38, "T1_19" पूर्ण,
	अणु 0x39, "PE_10" पूर्ण,
	अणु 0x3a, "PE_11" पूर्ण,
	अणु 0x3b, "TPCCS_10" पूर्ण,
	अणु 0x3c, "TPCCS_11" पूर्ण,
	अणु 0x3d, "T1_20" पूर्ण,
	अणु 0x3e, "T1_21" पूर्ण,
	अणु 0x3f, "T1_22" पूर्ण,
	अणु 0x40, "T1_23" पूर्ण,
	अणु 0x41, "PE_12" पूर्ण,
	अणु 0x42, "PE_13" पूर्ण,
	अणु 0x43, "TPCCS_12" पूर्ण,
	अणु 0x44, "TPCCS_13" पूर्ण,
	अणु 0x45, "T1_24" पूर्ण,
	अणु 0x46, "T1_25" पूर्ण,
	अणु 0x47, "T1_26" पूर्ण,
	अणु 0x48, "T1_27" पूर्ण,
	अणु 0x49, "PE_14" पूर्ण,
	अणु 0x4a, "PE_15" पूर्ण,
	अणु 0x4b, "TPCCS_14" पूर्ण,
	अणु 0x4c, "TPCCS_15" पूर्ण,
	अणु 0x4d, "T1_28" पूर्ण,
	अणु 0x4e, "T1_29" पूर्ण,
	अणु 0x4f, "T1_30" पूर्ण,
	अणु 0x50, "T1_31" पूर्ण,
	अणु 0x51, "PE_16" पूर्ण,
	अणु 0x52, "PE_17" पूर्ण,
	अणु 0x53, "TPCCS_16" पूर्ण,
	अणु 0x54, "TPCCS_17" पूर्ण,
	अणु 0x55, "T1_32" पूर्ण,
	अणु 0x56, "T1_33" पूर्ण,
	अणु 0x57, "T1_34" पूर्ण,
	अणु 0x58, "T1_35" पूर्ण,
	अणु 0x59, "PE_18" पूर्ण,
	अणु 0x5a, "PE_19" पूर्ण,
	अणु 0x5b, "TPCCS_18" पूर्ण,
	अणु 0x5c, "TPCCS_19" पूर्ण,
	अणु 0x5d, "T1_36" पूर्ण,
	अणु 0x5e, "T1_37" पूर्ण,
	अणु 0x5f, "T1_38" पूर्ण,
	अणु 0x60, "T1_39" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gv100_fअगरo_fault_hubclient[] = अणु
	अणु 0x00, "VIP" पूर्ण,
	अणु 0x01, "CE0" पूर्ण,
	अणु 0x02, "CE1" पूर्ण,
	अणु 0x03, "DNISO" पूर्ण,
	अणु 0x04, "FE" पूर्ण,
	अणु 0x05, "FECS" पूर्ण,
	अणु 0x06, "HOST" पूर्ण,
	अणु 0x07, "HOST_CPU" पूर्ण,
	अणु 0x08, "HOST_CPU_NB" पूर्ण,
	अणु 0x09, "ISO" पूर्ण,
	अणु 0x0a, "MMU" पूर्ण,
	अणु 0x0b, "NVDEC" पूर्ण,
	अणु 0x0d, "NVENC1" पूर्ण,
	अणु 0x0e, "NISO" पूर्ण,
	अणु 0x0f, "P2P" पूर्ण,
	अणु 0x10, "PD" पूर्ण,
	अणु 0x11, "PERF" पूर्ण,
	अणु 0x12, "PMU" पूर्ण,
	अणु 0x13, "RASTERTWOD" पूर्ण,
	अणु 0x14, "SCC" पूर्ण,
	अणु 0x15, "SCC_NB" पूर्ण,
	अणु 0x16, "SEC" पूर्ण,
	अणु 0x17, "SSYNC" पूर्ण,
	अणु 0x18, "CE2" पूर्ण,
	अणु 0x19, "XV" पूर्ण,
	अणु 0x1a, "MMU_NB" पूर्ण,
	अणु 0x1b, "NVENC0" पूर्ण,
	अणु 0x1c, "DFALCON" पूर्ण,
	अणु 0x1d, "SKED" पूर्ण,
	अणु 0x1e, "AFALCON" पूर्ण,
	अणु 0x1f, "DONT_CARE" पूर्ण,
	अणु 0x20, "HSCE0" पूर्ण,
	अणु 0x21, "HSCE1" पूर्ण,
	अणु 0x22, "HSCE2" पूर्ण,
	अणु 0x23, "HSCE3" पूर्ण,
	अणु 0x24, "HSCE4" पूर्ण,
	अणु 0x25, "HSCE5" पूर्ण,
	अणु 0x26, "HSCE6" पूर्ण,
	अणु 0x27, "HSCE7" पूर्ण,
	अणु 0x28, "HSCE8" पूर्ण,
	अणु 0x29, "HSCE9" पूर्ण,
	अणु 0x2a, "HSHUB" पूर्ण,
	अणु 0x2b, "PTP_X0" पूर्ण,
	अणु 0x2c, "PTP_X1" पूर्ण,
	अणु 0x2d, "PTP_X2" पूर्ण,
	अणु 0x2e, "PTP_X3" पूर्ण,
	अणु 0x2f, "PTP_X4" पूर्ण,
	अणु 0x30, "PTP_X5" पूर्ण,
	अणु 0x31, "PTP_X6" पूर्ण,
	अणु 0x32, "PTP_X7" पूर्ण,
	अणु 0x33, "NVENC2" पूर्ण,
	अणु 0x34, "VPR_SCRUBBER0" पूर्ण,
	अणु 0x35, "VPR_SCRUBBER1" पूर्ण,
	अणु 0x36, "DWBIF" पूर्ण,
	अणु 0x37, "FBFALCON" पूर्ण,
	अणु 0x38, "CE_SHIM" पूर्ण,
	अणु 0x39, "GSP" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gv100_fअगरo_fault_reason[] = अणु
	अणु 0x00, "PDE" पूर्ण,
	अणु 0x01, "PDE_SIZE" पूर्ण,
	अणु 0x02, "PTE" पूर्ण,
	अणु 0x03, "VA_LIMIT_VIOLATION" पूर्ण,
	अणु 0x04, "UNBOUND_INST_BLOCK" पूर्ण,
	अणु 0x05, "PRIV_VIOLATION" पूर्ण,
	अणु 0x06, "RO_VIOLATION" पूर्ण,
	अणु 0x07, "WO_VIOLATION" पूर्ण,
	अणु 0x08, "PITCH_MASK_VIOLATION" पूर्ण,
	अणु 0x09, "WORK_CREATION" पूर्ण,
	अणु 0x0a, "UNSUPPORTED_APERTURE" पूर्ण,
	अणु 0x0b, "COMPRESSION_FAILURE" पूर्ण,
	अणु 0x0c, "UNSUPPORTED_KIND" पूर्ण,
	अणु 0x0d, "REGION_VIOLATION" पूर्ण,
	अणु 0x0e, "POISONED" पूर्ण,
	अणु 0x0f, "ATOMIC_VIOLATION" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत
gv100_fअगरo_fault_engine[] = अणु
	अणु 0x01, "DISPLAY" पूर्ण,
	अणु 0x03, "PTP" पूर्ण,
	अणु 0x04, "BAR1", शून्य, NVKM_SUBDEV_BAR पूर्ण,
	अणु 0x05, "BAR2", शून्य, NVKM_SUBDEV_INSTMEM पूर्ण,
	अणु 0x06, "PWR_PMU" पूर्ण,
	अणु 0x08, "IFB", शून्य, NVKM_ENGINE_IFB पूर्ण,
	अणु 0x09, "PERF" पूर्ण,
	अणु 0x1f, "PHYSICAL" पूर्ण,
	अणु 0x20, "HOST0" पूर्ण,
	अणु 0x21, "HOST1" पूर्ण,
	अणु 0x22, "HOST2" पूर्ण,
	अणु 0x23, "HOST3" पूर्ण,
	अणु 0x24, "HOST4" पूर्ण,
	अणु 0x25, "HOST5" पूर्ण,
	अणु 0x26, "HOST6" पूर्ण,
	अणु 0x27, "HOST7" पूर्ण,
	अणु 0x28, "HOST8" पूर्ण,
	अणु 0x29, "HOST9" पूर्ण,
	अणु 0x2a, "HOST10" पूर्ण,
	अणु 0x2b, "HOST11" पूर्ण,
	अणु 0x2c, "HOST12" पूर्ण,
	अणु 0x2d, "HOST13" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gv100_fअगरo_fault_access[] = अणु
	अणु 0x0, "VIRT_READ" पूर्ण,
	अणु 0x1, "VIRT_WRITE" पूर्ण,
	अणु 0x2, "VIRT_ATOMIC" पूर्ण,
	अणु 0x3, "VIRT_PREFETCH" पूर्ण,
	अणु 0x4, "VIRT_ATOMIC_WEAK" पूर्ण,
	अणु 0x8, "PHYS_READ" पूर्ण,
	अणु 0x9, "PHYS_WRITE" पूर्ण,
	अणु 0xa, "PHYS_ATOMIC" पूर्ण,
	अणु 0xb, "PHYS_PREFETCH" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gk104_fअगरo_func
gv100_fअगरo = अणु
	.pbdma = &gm200_fअगरo_pbdma,
	.fault.access = gv100_fअगरo_fault_access,
	.fault.engine = gv100_fअगरo_fault_engine,
	.fault.reason = gv100_fअगरo_fault_reason,
	.fault.hubclient = gv100_fअगरo_fault_hubclient,
	.fault.gpcclient = gv100_fअगरo_fault_gpcclient,
	.runlist = &gv100_fअगरo_runlist,
	.user = अणुअणु-1,-1,VOLTA_USERMODE_A      पूर्ण, gv100_fअगरo_user_new   पूर्ण,
	.chan = अणुअणु 0, 0,VOLTA_CHANNEL_GPFIFO_Aपूर्ण, gv100_fअगरo_gpfअगरo_new पूर्ण,
	.cgrp_क्रमce = true,
पूर्ण;

पूर्णांक
gv100_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस gk104_fअगरo_new_(&gv100_fअगरo, device, type, inst, 4096, pfअगरo);
पूर्ण
