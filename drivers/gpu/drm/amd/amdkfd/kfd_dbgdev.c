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

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>

#समावेश "kfd_pm4_headers.h"
#समावेश "kfd_pm4_headers_diq.h"
#समावेश "kfd_kernel_queue.h"
#समावेश "kfd_priv.h"
#समावेश "kfd_pm4_opcodes.h"
#समावेश "cik_regs.h"
#समावेश "kfd_dbgmgr.h"
#समावेश "kfd_dbgdev.h"
#समावेश "kfd_device_queue_manager.h"

अटल व्योम dbgdev_address_watch_disable_nodiq(काष्ठा kfd_dev *dev)
अणु
	dev->kfd2kgd->address_watch_disable(dev->kgd);
पूर्ण

अटल पूर्णांक dbgdev_diq_submit_ib(काष्ठा kfd_dbgdev *dbgdev,
				u32 pasid, uपूर्णांक64_t vmid0_address,
				uपूर्णांक32_t *packet_buff, माप_प्रकार size_in_bytes)
अणु
	काष्ठा pm4__release_mem *rm_packet;
	काष्ठा pm4__indirect_buffer_pasid *ib_packet;
	काष्ठा kfd_mem_obj *mem_obj;
	माप_प्रकार pq_packets_size_in_bytes;
	जोड़ ULARGE_INTEGER *largep;
	जोड़ ULARGE_INTEGER addr;
	काष्ठा kernel_queue *kq;
	uपूर्णांक64_t *rm_state;
	अचिन्हित पूर्णांक *ib_packet_buff;
	पूर्णांक status;

	अगर (WARN_ON(!size_in_bytes))
		वापस -EINVAL;

	kq = dbgdev->kq;

	pq_packets_size_in_bytes = माप(काष्ठा pm4__release_mem) +
				माप(काष्ठा pm4__indirect_buffer_pasid);

	/*
	 * We acquire a buffer from DIQ
	 * The receive packet buff will be sitting on the Indirect Buffer
	 * and in the PQ we put the IB packet + sync packet(s).
	 */
	status = kq_acquire_packet_buffer(kq,
				pq_packets_size_in_bytes / माप(uपूर्णांक32_t),
				&ib_packet_buff);
	अगर (status) अणु
		pr_err("kq_acquire_packet_buffer failed\n");
		वापस status;
	पूर्ण

	स_रखो(ib_packet_buff, 0, pq_packets_size_in_bytes);

	ib_packet = (काष्ठा pm4__indirect_buffer_pasid *) (ib_packet_buff);

	ib_packet->header.count = 3;
	ib_packet->header.opcode = IT_INसूचीECT_BUFFER_PASID;
	ib_packet->header.type = PM4_TYPE_3;

	largep = (जोड़ ULARGE_INTEGER *) &vmid0_address;

	ib_packet->bitfields2.ib_base_lo = largep->u.low_part >> 2;
	ib_packet->bitfields3.ib_base_hi = largep->u.high_part;

	ib_packet->control = (1 << 23) | (1 << 31) |
			((size_in_bytes / 4) & 0xfffff);

	ib_packet->bitfields5.pasid = pasid;

	/*
	 * क्रम now we use release mem क्रम GPU-CPU synchronization
	 * Consider WaitRegMem + WriteData as a better alternative
	 * we get a GART allocations ( gpu/cpu mapping),
	 * क्रम the sync variable, and रुको until:
	 * (a) Sync with HW
	 * (b) Sync var is written by CP to mem.
	 */
	rm_packet = (काष्ठा pm4__release_mem *) (ib_packet_buff +
			(माप(काष्ठा pm4__indirect_buffer_pasid) /
					माप(अचिन्हित पूर्णांक)));

	status = kfd_gtt_sa_allocate(dbgdev->dev, माप(uपूर्णांक64_t),
					&mem_obj);

	अगर (status) अणु
		pr_err("Failed to allocate GART memory\n");
		kq_rollback_packet(kq);
		वापस status;
	पूर्ण

	rm_state = (uपूर्णांक64_t *) mem_obj->cpu_ptr;

	*rm_state = QUEUESTATE__ACTIVE_COMPLETION_PENDING;

	rm_packet->header.opcode = IT_RELEASE_MEM;
	rm_packet->header.type = PM4_TYPE_3;
	rm_packet->header.count = माप(काष्ठा pm4__release_mem) / 4 - 2;

	rm_packet->bitfields2.event_type = CACHE_FLUSH_AND_INV_TS_EVENT;
	rm_packet->bitfields2.event_index =
				event_index___release_mem__end_of_pipe;

	rm_packet->bitfields2.cache_policy = cache_policy___release_mem__lru;
	rm_packet->bitfields2.atc = 0;
	rm_packet->bitfields2.tc_wb_action_ena = 1;

	addr.quad_part = mem_obj->gpu_addr;

	rm_packet->bitfields4.address_lo_32b = addr.u.low_part >> 2;
	rm_packet->address_hi = addr.u.high_part;

	rm_packet->bitfields3.data_sel =
				data_sel___release_mem__send_64_bit_data;

	rm_packet->bitfields3.पूर्णांक_sel =
			पूर्णांक_sel___release_mem__send_data_after_ग_लिखो_confirm;

	rm_packet->bitfields3.dst_sel =
			dst_sel___release_mem__memory_controller;

	rm_packet->data_lo = QUEUESTATE__ACTIVE;

	kq_submit_packet(kq);

	/* Wait till CP ग_लिखोs sync code: */
	status = amdkfd_fence_रुको_समयout(
			rm_state,
			QUEUESTATE__ACTIVE, 1500);

	kfd_gtt_sa_मुक्त(dbgdev->dev, mem_obj);

	वापस status;
पूर्ण

अटल पूर्णांक dbgdev_रेजिस्टर_nodiq(काष्ठा kfd_dbgdev *dbgdev)
अणु
	/*
	 * no action is needed in this हाल,
	 * just make sure diq will not be used
	 */

	dbgdev->kq = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक dbgdev_रेजिस्टर_diq(काष्ठा kfd_dbgdev *dbgdev)
अणु
	काष्ठा queue_properties properties;
	अचिन्हित पूर्णांक qid;
	काष्ठा kernel_queue *kq = शून्य;
	पूर्णांक status;

	properties.type = KFD_QUEUE_TYPE_DIQ;

	status = pqm_create_queue(dbgdev->pqm, dbgdev->dev, शून्य,
				&properties, &qid, शून्य);

	अगर (status) अणु
		pr_err("Failed to create DIQ\n");
		वापस status;
	पूर्ण

	pr_debug("DIQ Created with queue id: %d\n", qid);

	kq = pqm_get_kernel_queue(dbgdev->pqm, qid);

	अगर (!kq) अणु
		pr_err("Error getting DIQ\n");
		pqm_destroy_queue(dbgdev->pqm, qid);
		वापस -EFAULT;
	पूर्ण

	dbgdev->kq = kq;

	वापस status;
पूर्ण

अटल पूर्णांक dbgdev_unरेजिस्टर_nodiq(काष्ठा kfd_dbgdev *dbgdev)
अणु
	/* disable watch address */
	dbgdev_address_watch_disable_nodiq(dbgdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक dbgdev_unरेजिस्टर_diq(काष्ठा kfd_dbgdev *dbgdev)
अणु
	/* toकरो - disable address watch */
	पूर्णांक status;

	status = pqm_destroy_queue(dbgdev->pqm,
			dbgdev->kq->queue->properties.queue_id);
	dbgdev->kq = शून्य;

	वापस status;
पूर्ण

अटल व्योम dbgdev_address_watch_set_रेजिस्टरs(
			स्थिर काष्ठा dbg_address_watch_info *adw_info,
			जोड़ TCP_WATCH_ADDR_H_BITS *addrHi,
			जोड़ TCP_WATCH_ADDR_L_BITS *addrLo,
			जोड़ TCP_WATCH_CNTL_BITS *cntl,
			अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक vmid)
अणु
	जोड़ ULARGE_INTEGER addr;

	addr.quad_part = 0;
	addrHi->u32All = 0;
	addrLo->u32All = 0;
	cntl->u32All = 0;

	अगर (adw_info->watch_mask)
		cntl->bitfields.mask =
			(uपूर्णांक32_t) (adw_info->watch_mask[index] &
					ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK);
	अन्यथा
		cntl->bitfields.mask = ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK;

	addr.quad_part = (अचिन्हित दीर्घ दीर्घ) adw_info->watch_address[index];

	addrHi->bitfields.addr = addr.u.high_part &
					ADDRESS_WATCH_REG_ADDHIGH_MASK;
	addrLo->bitfields.addr =
			(addr.u.low_part >> ADDRESS_WATCH_REG_ADDLOW_SHIFT);

	cntl->bitfields.mode = adw_info->watch_mode[index];
	cntl->bitfields.vmid = (uपूर्णांक32_t) vmid;
	/* क्रम now assume it is an ATC address */
	cntl->u32All |= ADDRESS_WATCH_REG_CNTL_ATC_BIT;

	pr_debug("\t\t%20s %08x\n", "set reg mask :", cntl->bitfields.mask);
	pr_debug("\t\t%20s %08x\n", "set reg add high :",
			addrHi->bitfields.addr);
	pr_debug("\t\t%20s %08x\n", "set reg add low :",
			addrLo->bitfields.addr);
पूर्ण

अटल पूर्णांक dbgdev_address_watch_nodiq(काष्ठा kfd_dbgdev *dbgdev,
				      काष्ठा dbg_address_watch_info *adw_info)
अणु
	जोड़ TCP_WATCH_ADDR_H_BITS addrHi;
	जोड़ TCP_WATCH_ADDR_L_BITS addrLo;
	जोड़ TCP_WATCH_CNTL_BITS cntl;
	काष्ठा kfd_process_device *pdd;
	अचिन्हित पूर्णांक i;

	/* taking the vmid क्रम that process on the safe way using pdd */
	pdd = kfd_get_process_device_data(dbgdev->dev,
					adw_info->process);
	अगर (!pdd) अणु
		pr_err("Failed to get pdd for wave control no DIQ\n");
		वापस -EFAULT;
	पूर्ण

	addrHi.u32All = 0;
	addrLo.u32All = 0;
	cntl.u32All = 0;

	अगर ((adw_info->num_watch_poपूर्णांकs > MAX_WATCH_ADDRESSES) ||
			(adw_info->num_watch_poपूर्णांकs == 0)) अणु
		pr_err("num_watch_points is invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!adw_info->watch_mode || !adw_info->watch_address) अणु
		pr_err("adw_info fields are not valid\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < adw_info->num_watch_poपूर्णांकs; i++) अणु
		dbgdev_address_watch_set_रेजिस्टरs(adw_info, &addrHi, &addrLo,
						&cntl, i, pdd->qpd.vmid);

		pr_debug("\t\t%30s\n", "* * * * * * * * * * * * * * * * * *");
		pr_debug("\t\t%20s %08x\n", "register index :", i);
		pr_debug("\t\t%20s %08x\n", "vmid is :", pdd->qpd.vmid);
		pr_debug("\t\t%20s %08x\n", "Address Low is :",
				addrLo.bitfields.addr);
		pr_debug("\t\t%20s %08x\n", "Address high is :",
				addrHi.bitfields.addr);
		pr_debug("\t\t%20s %08x\n", "Address high is :",
				addrHi.bitfields.addr);
		pr_debug("\t\t%20s %08x\n", "Control Mask is :",
				cntl.bitfields.mask);
		pr_debug("\t\t%20s %08x\n", "Control Mode is :",
				cntl.bitfields.mode);
		pr_debug("\t\t%20s %08x\n", "Control Vmid is :",
				cntl.bitfields.vmid);
		pr_debug("\t\t%20s %08x\n", "Control atc  is :",
				cntl.bitfields.atc);
		pr_debug("\t\t%30s\n", "* * * * * * * * * * * * * * * * * *");

		pdd->dev->kfd2kgd->address_watch_execute(
						dbgdev->dev->kgd,
						i,
						cntl.u32All,
						addrHi.u32All,
						addrLo.u32All);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dbgdev_address_watch_diq(काष्ठा kfd_dbgdev *dbgdev,
				    काष्ठा dbg_address_watch_info *adw_info)
अणु
	काष्ठा pm4__set_config_reg *packets_vec;
	जोड़ TCP_WATCH_ADDR_H_BITS addrHi;
	जोड़ TCP_WATCH_ADDR_L_BITS addrLo;
	जोड़ TCP_WATCH_CNTL_BITS cntl;
	काष्ठा kfd_mem_obj *mem_obj;
	अचिन्हित पूर्णांक aw_reg_add_dword;
	uपूर्णांक32_t *packet_buff_uपूर्णांक;
	अचिन्हित पूर्णांक i;
	पूर्णांक status;
	माप_प्रकार ib_size = माप(काष्ठा pm4__set_config_reg) * 4;
	/* we करो not control the vmid in DIQ mode, just a place holder */
	अचिन्हित पूर्णांक vmid = 0;

	addrHi.u32All = 0;
	addrLo.u32All = 0;
	cntl.u32All = 0;

	अगर ((adw_info->num_watch_poपूर्णांकs > MAX_WATCH_ADDRESSES) ||
			(adw_info->num_watch_poपूर्णांकs == 0)) अणु
		pr_err("num_watch_points is invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!adw_info->watch_mode || !adw_info->watch_address) अणु
		pr_err("adw_info fields are not valid\n");
		वापस -EINVAL;
	पूर्ण

	status = kfd_gtt_sa_allocate(dbgdev->dev, ib_size, &mem_obj);

	अगर (status) अणु
		pr_err("Failed to allocate GART memory\n");
		वापस status;
	पूर्ण

	packet_buff_uपूर्णांक = mem_obj->cpu_ptr;

	स_रखो(packet_buff_uपूर्णांक, 0, ib_size);

	packets_vec = (काष्ठा pm4__set_config_reg *) (packet_buff_uपूर्णांक);

	packets_vec[0].header.count = 1;
	packets_vec[0].header.opcode = IT_SET_CONFIG_REG;
	packets_vec[0].header.type = PM4_TYPE_3;
	packets_vec[0].bitfields2.vmid_shअगरt = ADDRESS_WATCH_CNTL_OFFSET;
	packets_vec[0].bitfields2.insert_vmid = 1;
	packets_vec[1].ordinal1 = packets_vec[0].ordinal1;
	packets_vec[1].bitfields2.insert_vmid = 0;
	packets_vec[2].ordinal1 = packets_vec[0].ordinal1;
	packets_vec[2].bitfields2.insert_vmid = 0;
	packets_vec[3].ordinal1 = packets_vec[0].ordinal1;
	packets_vec[3].bitfields2.vmid_shअगरt = ADDRESS_WATCH_CNTL_OFFSET;
	packets_vec[3].bitfields2.insert_vmid = 1;

	क्रम (i = 0; i < adw_info->num_watch_poपूर्णांकs; i++) अणु
		dbgdev_address_watch_set_रेजिस्टरs(adw_info,
						&addrHi,
						&addrLo,
						&cntl,
						i,
						vmid);

		pr_debug("\t\t%30s\n", "* * * * * * * * * * * * * * * * * *");
		pr_debug("\t\t%20s %08x\n", "register index :", i);
		pr_debug("\t\t%20s %08x\n", "vmid is :", vmid);
		pr_debug("\t\t%20s %p\n", "Add ptr is :",
				adw_info->watch_address);
		pr_debug("\t\t%20s %08llx\n", "Add     is :",
				adw_info->watch_address[i]);
		pr_debug("\t\t%20s %08x\n", "Address Low is :",
				addrLo.bitfields.addr);
		pr_debug("\t\t%20s %08x\n", "Address high is :",
				addrHi.bitfields.addr);
		pr_debug("\t\t%20s %08x\n", "Control Mask is :",
				cntl.bitfields.mask);
		pr_debug("\t\t%20s %08x\n", "Control Mode is :",
				cntl.bitfields.mode);
		pr_debug("\t\t%20s %08x\n", "Control Vmid is :",
				cntl.bitfields.vmid);
		pr_debug("\t\t%20s %08x\n", "Control atc  is :",
				cntl.bitfields.atc);
		pr_debug("\t\t%30s\n", "* * * * * * * * * * * * * * * * * *");

		aw_reg_add_dword =
				dbgdev->dev->kfd2kgd->address_watch_get_offset(
					dbgdev->dev->kgd,
					i,
					ADDRESS_WATCH_REG_CNTL);

		packets_vec[0].bitfields2.reg_offset =
					aw_reg_add_dword - AMD_CONFIG_REG_BASE;

		packets_vec[0].reg_data[0] = cntl.u32All;

		aw_reg_add_dword =
				dbgdev->dev->kfd2kgd->address_watch_get_offset(
					dbgdev->dev->kgd,
					i,
					ADDRESS_WATCH_REG_ADDR_HI);

		packets_vec[1].bitfields2.reg_offset =
					aw_reg_add_dword - AMD_CONFIG_REG_BASE;
		packets_vec[1].reg_data[0] = addrHi.u32All;

		aw_reg_add_dword =
				dbgdev->dev->kfd2kgd->address_watch_get_offset(
					dbgdev->dev->kgd,
					i,
					ADDRESS_WATCH_REG_ADDR_LO);

		packets_vec[2].bitfields2.reg_offset =
				aw_reg_add_dword - AMD_CONFIG_REG_BASE;
		packets_vec[2].reg_data[0] = addrLo.u32All;

		/* enable watch flag अगर address is not zero*/
		अगर (adw_info->watch_address[i] > 0)
			cntl.bitfields.valid = 1;
		अन्यथा
			cntl.bitfields.valid = 0;

		aw_reg_add_dword =
				dbgdev->dev->kfd2kgd->address_watch_get_offset(
					dbgdev->dev->kgd,
					i,
					ADDRESS_WATCH_REG_CNTL);

		packets_vec[3].bitfields2.reg_offset =
					aw_reg_add_dword - AMD_CONFIG_REG_BASE;
		packets_vec[3].reg_data[0] = cntl.u32All;

		status = dbgdev_diq_submit_ib(
					dbgdev,
					adw_info->process->pasid,
					mem_obj->gpu_addr,
					packet_buff_uपूर्णांक,
					ib_size);

		अगर (status) अणु
			pr_err("Failed to submit IB to DIQ\n");
			अवरोध;
		पूर्ण
	पूर्ण

	kfd_gtt_sa_मुक्त(dbgdev->dev, mem_obj);
	वापस status;
पूर्ण

अटल पूर्णांक dbgdev_wave_control_set_रेजिस्टरs(
				काष्ठा dbg_wave_control_info *wac_info,
				जोड़ SQ_CMD_BITS *in_reg_sq_cmd,
				जोड़ GRBM_GFX_INDEX_BITS *in_reg_gfx_index)
अणु
	पूर्णांक status = 0;
	जोड़ SQ_CMD_BITS reg_sq_cmd;
	जोड़ GRBM_GFX_INDEX_BITS reg_gfx_index;
	काष्ठा HsaDbgWaveMsgAMDGen2 *pMsg;

	reg_sq_cmd.u32All = 0;
	reg_gfx_index.u32All = 0;
	pMsg = &wac_info->dbgWave_msg.DbgWaveMsg.WaveMsgInfoGen2;

	चयन (wac_info->mode) अणु
	/* Send command to single wave */
	हाल HSA_DBG_WAVEMODE_SINGLE:
		/*
		 * Limit access to the process waves only,
		 * by setting vmid check
		 */
		reg_sq_cmd.bits.check_vmid = 1;
		reg_sq_cmd.bits.simd_id = pMsg->ui32.SIMD;
		reg_sq_cmd.bits.wave_id = pMsg->ui32.WaveId;
		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_SINGLE;

		reg_gfx_index.bits.sh_index = pMsg->ui32.ShaderArray;
		reg_gfx_index.bits.se_index = pMsg->ui32.ShaderEngine;
		reg_gfx_index.bits.instance_index = pMsg->ui32.HSACU;

		अवरोध;

	/* Send command to all waves with matching VMID */
	हाल HSA_DBG_WAVEMODE_BROADCAST_PROCESS:

		reg_gfx_index.bits.sh_broadcast_ग_लिखोs = 1;
		reg_gfx_index.bits.se_broadcast_ग_लिखोs = 1;
		reg_gfx_index.bits.instance_broadcast_ग_लिखोs = 1;

		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_BROADCAST;

		अवरोध;

	/* Send command to all CU waves with matching VMID */
	हाल HSA_DBG_WAVEMODE_BROADCAST_PROCESS_CU:

		reg_sq_cmd.bits.check_vmid = 1;
		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_BROADCAST;

		reg_gfx_index.bits.sh_index = pMsg->ui32.ShaderArray;
		reg_gfx_index.bits.se_index = pMsg->ui32.ShaderEngine;
		reg_gfx_index.bits.instance_index = pMsg->ui32.HSACU;

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (wac_info->opeअक्रम) अणु
	हाल HSA_DBG_WAVEOP_HALT:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_HALT;
		अवरोध;

	हाल HSA_DBG_WAVEOP_RESUME:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_RESUME;
		अवरोध;

	हाल HSA_DBG_WAVEOP_KILL:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_KILL;
		अवरोध;

	हाल HSA_DBG_WAVEOP_DEBUG:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_DEBUG;
		अवरोध;

	हाल HSA_DBG_WAVEOP_TRAP:
		अगर (wac_info->trapId < MAX_TRAPID) अणु
			reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_TRAP;
			reg_sq_cmd.bits.trap_id = wac_info->trapId;
		पूर्ण अन्यथा अणु
			status = -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		status = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (status == 0) अणु
		*in_reg_sq_cmd = reg_sq_cmd;
		*in_reg_gfx_index = reg_gfx_index;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक dbgdev_wave_control_diq(काष्ठा kfd_dbgdev *dbgdev,
					काष्ठा dbg_wave_control_info *wac_info)
अणु

	पूर्णांक status;
	जोड़ SQ_CMD_BITS reg_sq_cmd;
	जोड़ GRBM_GFX_INDEX_BITS reg_gfx_index;
	काष्ठा kfd_mem_obj *mem_obj;
	uपूर्णांक32_t *packet_buff_uपूर्णांक;
	काष्ठा pm4__set_config_reg *packets_vec;
	माप_प्रकार ib_size = माप(काष्ठा pm4__set_config_reg) * 3;

	reg_sq_cmd.u32All = 0;

	status = dbgdev_wave_control_set_रेजिस्टरs(wac_info, &reg_sq_cmd,
							&reg_gfx_index);
	अगर (status) अणु
		pr_err("Failed to set wave control registers\n");
		वापस status;
	पूर्ण

	/* we करो not control the VMID in DIQ, so reset it to a known value */
	reg_sq_cmd.bits.vm_id = 0;

	pr_debug("\t\t %30s\n", "* * * * * * * * * * * * * * * * * *");

	pr_debug("\t\t mode      is: %u\n", wac_info->mode);
	pr_debug("\t\t operand   is: %u\n", wac_info->opeअक्रम);
	pr_debug("\t\t trap id   is: %u\n", wac_info->trapId);
	pr_debug("\t\t msg value is: %u\n",
			wac_info->dbgWave_msg.DbgWaveMsg.WaveMsgInfoGen2.Value);
	pr_debug("\t\t vmid      is: N/A\n");

	pr_debug("\t\t chk_vmid  is : %u\n", reg_sq_cmd.bitfields.check_vmid);
	pr_debug("\t\t command   is : %u\n", reg_sq_cmd.bitfields.cmd);
	pr_debug("\t\t queue id  is : %u\n", reg_sq_cmd.bitfields.queue_id);
	pr_debug("\t\t simd id   is : %u\n", reg_sq_cmd.bitfields.simd_id);
	pr_debug("\t\t mode      is : %u\n", reg_sq_cmd.bitfields.mode);
	pr_debug("\t\t vm_id     is : %u\n", reg_sq_cmd.bitfields.vm_id);
	pr_debug("\t\t wave_id   is : %u\n", reg_sq_cmd.bitfields.wave_id);

	pr_debug("\t\t ibw       is : %u\n",
			reg_gfx_index.bitfields.instance_broadcast_ग_लिखोs);
	pr_debug("\t\t ii        is : %u\n",
			reg_gfx_index.bitfields.instance_index);
	pr_debug("\t\t sebw      is : %u\n",
			reg_gfx_index.bitfields.se_broadcast_ग_लिखोs);
	pr_debug("\t\t se_ind    is : %u\n", reg_gfx_index.bitfields.se_index);
	pr_debug("\t\t sh_ind    is : %u\n", reg_gfx_index.bitfields.sh_index);
	pr_debug("\t\t sbw       is : %u\n",
			reg_gfx_index.bitfields.sh_broadcast_ग_लिखोs);

	pr_debug("\t\t %30s\n", "* * * * * * * * * * * * * * * * * *");

	status = kfd_gtt_sa_allocate(dbgdev->dev, ib_size, &mem_obj);

	अगर (status != 0) अणु
		pr_err("Failed to allocate GART memory\n");
		वापस status;
	पूर्ण

	packet_buff_uपूर्णांक = mem_obj->cpu_ptr;

	स_रखो(packet_buff_uपूर्णांक, 0, ib_size);

	packets_vec =  (काष्ठा pm4__set_config_reg *) packet_buff_uपूर्णांक;
	packets_vec[0].header.count = 1;
	packets_vec[0].header.opcode = IT_SET_UCONFIG_REG;
	packets_vec[0].header.type = PM4_TYPE_3;
	packets_vec[0].bitfields2.reg_offset =
			GRBM_GFX_INDEX / 4 - USERCONFIG_REG_BASE;

	packets_vec[0].bitfields2.insert_vmid = 0;
	packets_vec[0].reg_data[0] = reg_gfx_index.u32All;

	packets_vec[1].header.count = 1;
	packets_vec[1].header.opcode = IT_SET_CONFIG_REG;
	packets_vec[1].header.type = PM4_TYPE_3;
	packets_vec[1].bitfields2.reg_offset = SQ_CMD / 4 - AMD_CONFIG_REG_BASE;

	packets_vec[1].bitfields2.vmid_shअगरt = SQ_CMD_VMID_OFFSET;
	packets_vec[1].bitfields2.insert_vmid = 1;
	packets_vec[1].reg_data[0] = reg_sq_cmd.u32All;

	/* Restore the GRBM_GFX_INDEX रेजिस्टर */

	reg_gfx_index.u32All = 0;
	reg_gfx_index.bits.sh_broadcast_ग_लिखोs = 1;
	reg_gfx_index.bits.instance_broadcast_ग_लिखोs = 1;
	reg_gfx_index.bits.se_broadcast_ग_लिखोs = 1;


	packets_vec[2].ordinal1 = packets_vec[0].ordinal1;
	packets_vec[2].bitfields2.reg_offset =
				GRBM_GFX_INDEX / 4 - USERCONFIG_REG_BASE;

	packets_vec[2].bitfields2.insert_vmid = 0;
	packets_vec[2].reg_data[0] = reg_gfx_index.u32All;

	status = dbgdev_diq_submit_ib(
			dbgdev,
			wac_info->process->pasid,
			mem_obj->gpu_addr,
			packet_buff_uपूर्णांक,
			ib_size);

	अगर (status)
		pr_err("Failed to submit IB to DIQ\n");

	kfd_gtt_sa_मुक्त(dbgdev->dev, mem_obj);

	वापस status;
पूर्ण

अटल पूर्णांक dbgdev_wave_control_nodiq(काष्ठा kfd_dbgdev *dbgdev,
					काष्ठा dbg_wave_control_info *wac_info)
अणु
	पूर्णांक status;
	जोड़ SQ_CMD_BITS reg_sq_cmd;
	जोड़ GRBM_GFX_INDEX_BITS reg_gfx_index;
	काष्ठा kfd_process_device *pdd;

	reg_sq_cmd.u32All = 0;

	/* taking the VMID क्रम that process on the safe way using PDD */
	pdd = kfd_get_process_device_data(dbgdev->dev, wac_info->process);

	अगर (!pdd) अणु
		pr_err("Failed to get pdd for wave control no DIQ\n");
		वापस -EFAULT;
	पूर्ण
	status = dbgdev_wave_control_set_रेजिस्टरs(wac_info, &reg_sq_cmd,
							&reg_gfx_index);
	अगर (status) अणु
		pr_err("Failed to set wave control registers\n");
		वापस status;
	पूर्ण

	/* क्रम non DIQ we need to patch the VMID: */

	reg_sq_cmd.bits.vm_id = pdd->qpd.vmid;

	pr_debug("\t\t %30s\n", "* * * * * * * * * * * * * * * * * *");

	pr_debug("\t\t mode      is: %u\n", wac_info->mode);
	pr_debug("\t\t operand   is: %u\n", wac_info->opeअक्रम);
	pr_debug("\t\t trap id   is: %u\n", wac_info->trapId);
	pr_debug("\t\t msg value is: %u\n",
			wac_info->dbgWave_msg.DbgWaveMsg.WaveMsgInfoGen2.Value);
	pr_debug("\t\t vmid      is: %u\n", pdd->qpd.vmid);

	pr_debug("\t\t chk_vmid  is : %u\n", reg_sq_cmd.bitfields.check_vmid);
	pr_debug("\t\t command   is : %u\n", reg_sq_cmd.bitfields.cmd);
	pr_debug("\t\t queue id  is : %u\n", reg_sq_cmd.bitfields.queue_id);
	pr_debug("\t\t simd id   is : %u\n", reg_sq_cmd.bitfields.simd_id);
	pr_debug("\t\t mode      is : %u\n", reg_sq_cmd.bitfields.mode);
	pr_debug("\t\t vm_id     is : %u\n", reg_sq_cmd.bitfields.vm_id);
	pr_debug("\t\t wave_id   is : %u\n", reg_sq_cmd.bitfields.wave_id);

	pr_debug("\t\t ibw       is : %u\n",
			reg_gfx_index.bitfields.instance_broadcast_ग_लिखोs);
	pr_debug("\t\t ii        is : %u\n",
			reg_gfx_index.bitfields.instance_index);
	pr_debug("\t\t sebw      is : %u\n",
			reg_gfx_index.bitfields.se_broadcast_ग_लिखोs);
	pr_debug("\t\t se_ind    is : %u\n", reg_gfx_index.bitfields.se_index);
	pr_debug("\t\t sh_ind    is : %u\n", reg_gfx_index.bitfields.sh_index);
	pr_debug("\t\t sbw       is : %u\n",
			reg_gfx_index.bitfields.sh_broadcast_ग_लिखोs);

	pr_debug("\t\t %30s\n", "* * * * * * * * * * * * * * * * * *");

	वापस dbgdev->dev->kfd2kgd->wave_control_execute(dbgdev->dev->kgd,
							reg_gfx_index.u32All,
							reg_sq_cmd.u32All);
पूर्ण

पूर्णांक dbgdev_wave_reset_wavefronts(काष्ठा kfd_dev *dev, काष्ठा kfd_process *p)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक vmid;
	uपूर्णांक16_t queried_pasid;
	जोड़ SQ_CMD_BITS reg_sq_cmd;
	जोड़ GRBM_GFX_INDEX_BITS reg_gfx_index;
	काष्ठा kfd_process_device *pdd;
	काष्ठा dbg_wave_control_info wac_info;
	पूर्णांक first_vmid_to_scan = dev->vm_info.first_vmid_kfd;
	पूर्णांक last_vmid_to_scan = dev->vm_info.last_vmid_kfd;

	reg_sq_cmd.u32All = 0;
	status = 0;

	wac_info.mode = HSA_DBG_WAVEMODE_BROADCAST_PROCESS;
	wac_info.opeअक्रम = HSA_DBG_WAVEOP_KILL;

	pr_debug("Killing all process wavefronts\n");

	/* Scan all रेजिस्टरs in the range ATC_VMID8_PASID_MAPPING ..
	 * ATC_VMID15_PASID_MAPPING
	 * to check which VMID the current process is mapped to.
	 */

	क्रम (vmid = first_vmid_to_scan; vmid <= last_vmid_to_scan; vmid++) अणु
		status = dev->kfd2kgd->get_atc_vmid_pasid_mapping_info
				(dev->kgd, vmid, &queried_pasid);

		अगर (status && queried_pasid == p->pasid) अणु
			pr_debug("Killing wave fronts of vmid %d and pasid 0x%x\n",
					vmid, p->pasid);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (vmid > last_vmid_to_scan) अणु
		pr_err("Didn't find vmid for pasid 0x%x\n", p->pasid);
		वापस -EFAULT;
	पूर्ण

	/* taking the VMID क्रम that process on the safe way using PDD */
	pdd = kfd_get_process_device_data(dev, p);
	अगर (!pdd)
		वापस -EFAULT;

	status = dbgdev_wave_control_set_रेजिस्टरs(&wac_info, &reg_sq_cmd,
			&reg_gfx_index);
	अगर (status != 0)
		वापस -EINVAL;

	/* क्रम non DIQ we need to patch the VMID: */
	reg_sq_cmd.bits.vm_id = vmid;

	dev->kfd2kgd->wave_control_execute(dev->kgd,
					reg_gfx_index.u32All,
					reg_sq_cmd.u32All);

	वापस 0;
पूर्ण

व्योम kfd_dbgdev_init(काष्ठा kfd_dbgdev *pdbgdev, काष्ठा kfd_dev *pdev,
			क्रमागत DBGDEV_TYPE type)
अणु
	pdbgdev->dev = pdev;
	pdbgdev->kq = शून्य;
	pdbgdev->type = type;
	pdbgdev->pqm = शून्य;

	चयन (type) अणु
	हाल DBGDEV_TYPE_NODIQ:
		pdbgdev->dbgdev_रेजिस्टर = dbgdev_रेजिस्टर_nodiq;
		pdbgdev->dbgdev_unरेजिस्टर = dbgdev_unरेजिस्टर_nodiq;
		pdbgdev->dbgdev_wave_control = dbgdev_wave_control_nodiq;
		pdbgdev->dbgdev_address_watch = dbgdev_address_watch_nodiq;
		अवरोध;
	हाल DBGDEV_TYPE_DIQ:
	शेष:
		pdbgdev->dbgdev_रेजिस्टर = dbgdev_रेजिस्टर_diq;
		pdbgdev->dbgdev_unरेजिस्टर = dbgdev_unरेजिस्टर_diq;
		pdbgdev->dbgdev_wave_control =  dbgdev_wave_control_diq;
		pdbgdev->dbgdev_address_watch = dbgdev_address_watch_diq;
		अवरोध;
	पूर्ण

पूर्ण
