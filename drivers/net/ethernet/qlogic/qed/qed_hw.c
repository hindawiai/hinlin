<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/qed/qed_chain.h>
#समावेश "qed.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sriov.h"

#घोषणा QED_BAR_ACQUIRE_TIMEOUT 1000

/* Invalid values */
#घोषणा QED_BAR_INVALID_OFFSET          (cpu_to_le32(-1))

काष्ठा qed_ptt अणु
	काष्ठा list_head	list_entry;
	अचिन्हित पूर्णांक		idx;
	काष्ठा pxp_ptt_entry	pxp;
	u8			hwfn_id;
पूर्ण;

काष्ठा qed_ptt_pool अणु
	काष्ठा list_head	मुक्त_list;
	spinlock_t		lock; /* ptt synchronized access */
	काष्ठा qed_ptt		ptts[PXP_EXTERNAL_BAR_PF_WINDOW_NUM];
पूर्ण;

पूर्णांक qed_ptt_pool_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ptt_pool *p_pool = kदो_स्मृति(माप(*p_pool), GFP_KERNEL);
	पूर्णांक i;

	अगर (!p_pool)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&p_pool->मुक्त_list);
	क्रम (i = 0; i < PXP_EXTERNAL_BAR_PF_WINDOW_NUM; i++) अणु
		p_pool->ptts[i].idx = i;
		p_pool->ptts[i].pxp.offset = QED_BAR_INVALID_OFFSET;
		p_pool->ptts[i].pxp.pretend.control = 0;
		p_pool->ptts[i].hwfn_id = p_hwfn->my_id;
		अगर (i >= RESERVED_PTT_MAX)
			list_add(&p_pool->ptts[i].list_entry,
				 &p_pool->मुक्त_list);
	पूर्ण

	p_hwfn->p_ptt_pool = p_pool;
	spin_lock_init(&p_pool->lock);

	वापस 0;
पूर्ण

व्योम qed_ptt_invalidate(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक i;

	क्रम (i = 0; i < PXP_EXTERNAL_BAR_PF_WINDOW_NUM; i++) अणु
		p_ptt = &p_hwfn->p_ptt_pool->ptts[i];
		p_ptt->pxp.offset = QED_BAR_INVALID_OFFSET;
	पूर्ण
पूर्ण

व्योम qed_ptt_pool_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	kमुक्त(p_hwfn->p_ptt_pool);
	p_hwfn->p_ptt_pool = शून्य;
पूर्ण

काष्ठा qed_ptt *qed_ptt_acquire(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ptt *p_ptt;
	अचिन्हित पूर्णांक i;

	/* Take the मुक्त PTT from the list */
	क्रम (i = 0; i < QED_BAR_ACQUIRE_TIMEOUT; i++) अणु
		spin_lock_bh(&p_hwfn->p_ptt_pool->lock);

		अगर (!list_empty(&p_hwfn->p_ptt_pool->मुक्त_list)) अणु
			p_ptt = list_first_entry(&p_hwfn->p_ptt_pool->मुक्त_list,
						 काष्ठा qed_ptt, list_entry);
			list_del(&p_ptt->list_entry);

			spin_unlock_bh(&p_hwfn->p_ptt_pool->lock);

			DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
				   "allocated ptt %d\n", p_ptt->idx);
			वापस p_ptt;
		पूर्ण

		spin_unlock_bh(&p_hwfn->p_ptt_pool->lock);
		usleep_range(1000, 2000);
	पूर्ण

	DP_NOTICE(p_hwfn, "PTT acquire timeout - failed to allocate PTT\n");
	वापस शून्य;
पूर्ण

व्योम qed_ptt_release(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	spin_lock_bh(&p_hwfn->p_ptt_pool->lock);
	list_add(&p_ptt->list_entry, &p_hwfn->p_ptt_pool->मुक्त_list);
	spin_unlock_bh(&p_hwfn->p_ptt_pool->lock);
पूर्ण

u32 qed_ptt_get_hw_addr(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	/* The HW is using DWORDS and we need to translate it to Bytes */
	वापस le32_to_cpu(p_ptt->pxp.offset) << 2;
पूर्ण

अटल u32 qed_ptt_config_addr(काष्ठा qed_ptt *p_ptt)
अणु
	वापस PXP_PF_WINDOW_ADMIN_PER_PF_START +
	       p_ptt->idx * माप(काष्ठा pxp_ptt_entry);
पूर्ण

u32 qed_ptt_get_bar_addr(काष्ठा qed_ptt *p_ptt)
अणु
	वापस PXP_EXTERNAL_BAR_PF_WINDOW_START +
	       p_ptt->idx * PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE;
पूर्ण

व्योम qed_ptt_set_win(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt, u32 new_hw_addr)
अणु
	u32 prev_hw_addr;

	prev_hw_addr = qed_ptt_get_hw_addr(p_hwfn, p_ptt);

	अगर (new_hw_addr == prev_hw_addr)
		वापस;

	/* Update PTT entery in admin winकरोw */
	DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
		   "Updating PTT entry %d to offset 0x%x\n",
		   p_ptt->idx, new_hw_addr);

	/* The HW is using DWORDS and the address is in Bytes */
	p_ptt->pxp.offset = cpu_to_le32(new_hw_addr >> 2);

	REG_WR(p_hwfn,
	       qed_ptt_config_addr(p_ptt) +
	       दुरत्व(काष्ठा pxp_ptt_entry, offset),
	       le32_to_cpu(p_ptt->pxp.offset));
पूर्ण

अटल u32 qed_set_ptt(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt, u32 hw_addr)
अणु
	u32 win_hw_addr = qed_ptt_get_hw_addr(p_hwfn, p_ptt);
	u32 offset;

	offset = hw_addr - win_hw_addr;

	अगर (p_ptt->hwfn_id != p_hwfn->my_id)
		DP_NOTICE(p_hwfn,
			  "ptt[%d] of hwfn[%02x] is used by hwfn[%02x]!\n",
			  p_ptt->idx, p_ptt->hwfn_id, p_hwfn->my_id);

	/* Verअगरy the address is within the winकरोw */
	अगर (hw_addr < win_hw_addr ||
	    offset >= PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE) अणु
		qed_ptt_set_win(p_hwfn, p_ptt, hw_addr);
		offset = 0;
	पूर्ण

	वापस qed_ptt_get_bar_addr(p_ptt) + offset;
पूर्ण

काष्ठा qed_ptt *qed_get_reserved_ptt(काष्ठा qed_hwfn *p_hwfn,
				     क्रमागत reserved_ptts ptt_idx)
अणु
	अगर (ptt_idx >= RESERVED_PTT_MAX) अणु
		DP_NOTICE(p_hwfn,
			  "Requested PTT %d is out of range\n", ptt_idx);
		वापस शून्य;
	पूर्ण

	वापस &p_hwfn->p_ptt_pool->ptts[ptt_idx];
पूर्ण

व्योम qed_wr(काष्ठा qed_hwfn *p_hwfn,
	    काष्ठा qed_ptt *p_ptt,
	    u32 hw_addr, u32 val)
अणु
	u32 bar_addr = qed_set_ptt(p_hwfn, p_ptt, hw_addr);

	REG_WR(p_hwfn, bar_addr, val);
	DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
		   "bar_addr 0x%x, hw_addr 0x%x, val 0x%x\n",
		   bar_addr, hw_addr, val);
पूर्ण

u32 qed_rd(काष्ठा qed_hwfn *p_hwfn,
	   काष्ठा qed_ptt *p_ptt,
	   u32 hw_addr)
अणु
	u32 bar_addr = qed_set_ptt(p_hwfn, p_ptt, hw_addr);
	u32 val = REG_RD(p_hwfn, bar_addr);

	DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
		   "bar_addr 0x%x, hw_addr 0x%x, val 0x%x\n",
		   bar_addr, hw_addr, val);

	वापस val;
पूर्ण

अटल व्योम qed_स_नकल_hw(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt,
			  व्योम *addr, u32 hw_addr, माप_प्रकार n, bool to_device)
अणु
	u32 dw_count, *host_addr, hw_offset;
	माप_प्रकार quota, करोne = 0;
	u32 __iomem *reg_addr;

	जबतक (करोne < n) अणु
		quota = min_t(माप_प्रकार, n - करोne,
			      PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE);

		अगर (IS_PF(p_hwfn->cdev)) अणु
			qed_ptt_set_win(p_hwfn, p_ptt, hw_addr + करोne);
			hw_offset = qed_ptt_get_bar_addr(p_ptt);
		पूर्ण अन्यथा अणु
			hw_offset = hw_addr + करोne;
		पूर्ण

		dw_count = quota / 4;
		host_addr = (u32 *)((u8 *)addr + करोne);
		reg_addr = (u32 __iomem *)REG_ADDR(p_hwfn, hw_offset);
		अगर (to_device)
			जबतक (dw_count--)
				सूचीECT_REG_WR(reg_addr++, *host_addr++);
		अन्यथा
			जबतक (dw_count--)
				*host_addr++ = सूचीECT_REG_RD(reg_addr++);

		करोne += quota;
	पूर्ण
पूर्ण

व्योम qed_स_नकल_from(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt, व्योम *dest, u32 hw_addr, माप_प्रकार n)
अणु
	DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
		   "hw_addr 0x%x, dest %p hw_addr 0x%x, size %lu\n",
		   hw_addr, dest, hw_addr, (अचिन्हित दीर्घ)n);

	qed_स_नकल_hw(p_hwfn, p_ptt, dest, hw_addr, n, false);
पूर्ण

व्योम qed_स_नकल_to(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt, u32 hw_addr, व्योम *src, माप_प्रकार n)
अणु
	DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
		   "hw_addr 0x%x, hw_addr 0x%x, src %p size %lu\n",
		   hw_addr, hw_addr, src, (अचिन्हित दीर्घ)n);

	qed_स_नकल_hw(p_hwfn, p_ptt, src, hw_addr, n, true);
पूर्ण

व्योम qed_fid_pretend(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt, u16 fid)
अणु
	u16 control = 0;

	SET_FIELD(control, PXP_PRETEND_CMD_IS_CONCRETE, 1);
	SET_FIELD(control, PXP_PRETEND_CMD_PRETEND_FUNCTION, 1);

	/* Every pretend unकरोs previous pretends, including
	 * previous port pretend.
	 */
	SET_FIELD(control, PXP_PRETEND_CMD_PORT, 0);
	SET_FIELD(control, PXP_PRETEND_CMD_USE_PORT, 0);
	SET_FIELD(control, PXP_PRETEND_CMD_PRETEND_PORT, 1);

	अगर (!GET_FIELD(fid, PXP_CONCRETE_FID_VFVALID))
		fid = GET_FIELD(fid, PXP_CONCRETE_FID_PFID);

	p_ptt->pxp.pretend.control = cpu_to_le16(control);
	p_ptt->pxp.pretend.fid.concrete_fid.fid = cpu_to_le16(fid);

	REG_WR(p_hwfn,
	       qed_ptt_config_addr(p_ptt) +
	       दुरत्व(काष्ठा pxp_ptt_entry, pretend),
	       *(u32 *)&p_ptt->pxp.pretend);
पूर्ण

व्योम qed_port_pretend(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt, u8 port_id)
अणु
	u16 control = 0;

	SET_FIELD(control, PXP_PRETEND_CMD_PORT, port_id);
	SET_FIELD(control, PXP_PRETEND_CMD_USE_PORT, 1);
	SET_FIELD(control, PXP_PRETEND_CMD_PRETEND_PORT, 1);

	p_ptt->pxp.pretend.control = cpu_to_le16(control);

	REG_WR(p_hwfn,
	       qed_ptt_config_addr(p_ptt) +
	       दुरत्व(काष्ठा pxp_ptt_entry, pretend),
	       *(u32 *)&p_ptt->pxp.pretend);
पूर्ण

व्योम qed_port_unpretend(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u16 control = 0;

	SET_FIELD(control, PXP_PRETEND_CMD_PORT, 0);
	SET_FIELD(control, PXP_PRETEND_CMD_USE_PORT, 0);
	SET_FIELD(control, PXP_PRETEND_CMD_PRETEND_PORT, 1);

	p_ptt->pxp.pretend.control = cpu_to_le16(control);

	REG_WR(p_hwfn,
	       qed_ptt_config_addr(p_ptt) +
	       दुरत्व(काष्ठा pxp_ptt_entry, pretend),
	       *(u32 *)&p_ptt->pxp.pretend);
पूर्ण

व्योम qed_port_fid_pretend(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u8 port_id, u16 fid)
अणु
	u16 control = 0;

	SET_FIELD(control, PXP_PRETEND_CMD_PORT, port_id);
	SET_FIELD(control, PXP_PRETEND_CMD_USE_PORT, 1);
	SET_FIELD(control, PXP_PRETEND_CMD_PRETEND_PORT, 1);
	SET_FIELD(control, PXP_PRETEND_CMD_IS_CONCRETE, 1);
	SET_FIELD(control, PXP_PRETEND_CMD_PRETEND_FUNCTION, 1);
	अगर (!GET_FIELD(fid, PXP_CONCRETE_FID_VFVALID))
		fid = GET_FIELD(fid, PXP_CONCRETE_FID_PFID);
	p_ptt->pxp.pretend.control = cpu_to_le16(control);
	p_ptt->pxp.pretend.fid.concrete_fid.fid = cpu_to_le16(fid);
	REG_WR(p_hwfn,
	       qed_ptt_config_addr(p_ptt) +
	       दुरत्व(काष्ठा pxp_ptt_entry, pretend),
	       *(u32 *)&p_ptt->pxp.pretend);
पूर्ण

u32 qed_vfid_to_concrete(काष्ठा qed_hwfn *p_hwfn, u8 vfid)
अणु
	u32 concrete_fid = 0;

	SET_FIELD(concrete_fid, PXP_CONCRETE_FID_PFID, p_hwfn->rel_pf_id);
	SET_FIELD(concrete_fid, PXP_CONCRETE_FID_VFID, vfid);
	SET_FIELD(concrete_fid, PXP_CONCRETE_FID_VFVALID, 1);

	वापस concrete_fid;
पूर्ण

/* DMAE */
#घोषणा QED_DMAE_FLAGS_IS_SET(params, flag) \
	((params) != शून्य && GET_FIELD((params)->flags, QED_DMAE_PARAMS_##flag))

अटल व्योम qed_dmae_opcode(काष्ठा qed_hwfn *p_hwfn,
			    स्थिर u8 is_src_type_grc,
			    स्थिर u8 is_dst_type_grc,
			    काष्ठा qed_dmae_params *p_params)
अणु
	u8 src_pfid, dst_pfid, port_id;
	u16 opcode_b = 0;
	u32 opcode = 0;

	/* Whether the source is the PCIe or the GRC.
	 * 0- The source is the PCIe
	 * 1- The source is the GRC.
	 */
	SET_FIELD(opcode, DMAE_CMD_SRC,
		  (is_src_type_grc ? dmae_cmd_src_grc : dmae_cmd_src_pcie));
	src_pfid = QED_DMAE_FLAGS_IS_SET(p_params, SRC_PF_VALID) ?
	    p_params->src_pfid : p_hwfn->rel_pf_id;
	SET_FIELD(opcode, DMAE_CMD_SRC_PF_ID, src_pfid);

	/* The destination of the DMA can be: 0-None 1-PCIe 2-GRC 3-None */
	SET_FIELD(opcode, DMAE_CMD_DST,
		  (is_dst_type_grc ? dmae_cmd_dst_grc : dmae_cmd_dst_pcie));
	dst_pfid = QED_DMAE_FLAGS_IS_SET(p_params, DST_PF_VALID) ?
	    p_params->dst_pfid : p_hwfn->rel_pf_id;
	SET_FIELD(opcode, DMAE_CMD_DST_PF_ID, dst_pfid);


	/* Whether to ग_लिखो a completion word to the completion destination:
	 * 0-Do not ग_लिखो a completion word
	 * 1-Write the completion word
	 */
	SET_FIELD(opcode, DMAE_CMD_COMP_WORD_EN, 1);
	SET_FIELD(opcode, DMAE_CMD_SRC_ADDR_RESET, 1);

	अगर (QED_DMAE_FLAGS_IS_SET(p_params, COMPLETION_DST))
		SET_FIELD(opcode, DMAE_CMD_COMP_FUNC, 1);

	/* swapping mode 3 - big endian */
	SET_FIELD(opcode, DMAE_CMD_ENDIANITY_MODE, DMAE_CMD_ENDIANITY);

	port_id = (QED_DMAE_FLAGS_IS_SET(p_params, PORT_VALID)) ?
	    p_params->port_id : p_hwfn->port_id;
	SET_FIELD(opcode, DMAE_CMD_PORT_ID, port_id);

	/* reset source address in next go */
	SET_FIELD(opcode, DMAE_CMD_SRC_ADDR_RESET, 1);

	/* reset dest address in next go */
	SET_FIELD(opcode, DMAE_CMD_DST_ADDR_RESET, 1);

	/* SRC/DST VFID: all 1's - pf, otherwise VF id */
	अगर (QED_DMAE_FLAGS_IS_SET(p_params, SRC_VF_VALID)) अणु
		SET_FIELD(opcode, DMAE_CMD_SRC_VF_ID_VALID, 1);
		SET_FIELD(opcode_b, DMAE_CMD_SRC_VF_ID, p_params->src_vfid);
	पूर्ण अन्यथा अणु
		SET_FIELD(opcode_b, DMAE_CMD_SRC_VF_ID, 0xFF);
	पूर्ण
	अगर (QED_DMAE_FLAGS_IS_SET(p_params, DST_VF_VALID)) अणु
		SET_FIELD(opcode, DMAE_CMD_DST_VF_ID_VALID, 1);
		SET_FIELD(opcode_b, DMAE_CMD_DST_VF_ID, p_params->dst_vfid);
	पूर्ण अन्यथा अणु
		SET_FIELD(opcode_b, DMAE_CMD_DST_VF_ID, 0xFF);
	पूर्ण

	p_hwfn->dmae_info.p_dmae_cmd->opcode = cpu_to_le32(opcode);
	p_hwfn->dmae_info.p_dmae_cmd->opcode_b = cpu_to_le16(opcode_b);
पूर्ण

u32 qed_dmae_idx_to_go_cmd(u8 idx)
अणु
	/* All the DMAE 'go' रेजिस्टरs क्रमm an array in पूर्णांकernal memory */
	वापस DMAE_REG_GO_C0 + (idx << 2);
पूर्ण

अटल पूर्णांक qed_dmae_post_command(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा dmae_cmd *p_command = p_hwfn->dmae_info.p_dmae_cmd;
	u8 idx_cmd = p_hwfn->dmae_info.channel, i;
	पूर्णांक qed_status = 0;

	/* verअगरy address is not शून्य */
	अगर ((((!p_command->dst_addr_lo) && (!p_command->dst_addr_hi)) ||
	     ((!p_command->src_addr_lo) && (!p_command->src_addr_hi)))) अणु
		DP_NOTICE(p_hwfn,
			  "source or destination address 0 idx_cmd=%d\n"
			  "opcode = [0x%08x,0x%04x] len=0x%x src=0x%x:%x dst=0x%x:%x\n",
			  idx_cmd,
			  le32_to_cpu(p_command->opcode),
			  le16_to_cpu(p_command->opcode_b),
			  le16_to_cpu(p_command->length_dw),
			  le32_to_cpu(p_command->src_addr_hi),
			  le32_to_cpu(p_command->src_addr_lo),
			  le32_to_cpu(p_command->dst_addr_hi),
			  le32_to_cpu(p_command->dst_addr_lo));

		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(p_hwfn,
		   NETIF_MSG_HW,
		   "Posting DMAE command [idx %d]: opcode = [0x%08x,0x%04x] len=0x%x src=0x%x:%x dst=0x%x:%x\n",
		   idx_cmd,
		   le32_to_cpu(p_command->opcode),
		   le16_to_cpu(p_command->opcode_b),
		   le16_to_cpu(p_command->length_dw),
		   le32_to_cpu(p_command->src_addr_hi),
		   le32_to_cpu(p_command->src_addr_lo),
		   le32_to_cpu(p_command->dst_addr_hi),
		   le32_to_cpu(p_command->dst_addr_lo));

	/* Copy the command to DMAE - need to करो it beक्रमe every call
	 * क्रम source/dest address no reset.
	 * The first 9 DWs are the command रेजिस्टरs, the 10 DW is the
	 * GO रेजिस्टर, and the rest are result रेजिस्टरs
	 * (which are पढ़ो only by the client).
	 */
	क्रम (i = 0; i < DMAE_CMD_SIZE; i++) अणु
		u32 data = (i < DMAE_CMD_SIZE_TO_FILL) ?
			   *(((u32 *)p_command) + i) : 0;

		qed_wr(p_hwfn, p_ptt,
		       DMAE_REG_CMD_MEM +
		       (idx_cmd * DMAE_CMD_SIZE * माप(u32)) +
		       (i * माप(u32)), data);
	पूर्ण

	qed_wr(p_hwfn, p_ptt, qed_dmae_idx_to_go_cmd(idx_cmd), DMAE_GO_VALUE);

	वापस qed_status;
पूर्ण

पूर्णांक qed_dmae_info_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	dma_addr_t *p_addr = &p_hwfn->dmae_info.completion_word_phys_addr;
	काष्ठा dmae_cmd **p_cmd = &p_hwfn->dmae_info.p_dmae_cmd;
	u32 **p_buff = &p_hwfn->dmae_info.p_पूर्णांकermediate_buffer;
	u32 **p_comp = &p_hwfn->dmae_info.p_completion_word;

	*p_comp = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				     माप(u32), p_addr, GFP_KERNEL);
	अगर (!*p_comp)
		जाओ err;

	p_addr = &p_hwfn->dmae_info.dmae_cmd_phys_addr;
	*p_cmd = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    माप(काष्ठा dmae_cmd),
				    p_addr, GFP_KERNEL);
	अगर (!*p_cmd)
		जाओ err;

	p_addr = &p_hwfn->dmae_info.पूर्णांकermediate_buffer_phys_addr;
	*p_buff = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				     माप(u32) * DMAE_MAX_RW_SIZE,
				     p_addr, GFP_KERNEL);
	अगर (!*p_buff)
		जाओ err;

	p_hwfn->dmae_info.channel = p_hwfn->rel_pf_id;

	वापस 0;
err:
	qed_dmae_info_मुक्त(p_hwfn);
	वापस -ENOMEM;
पूर्ण

व्योम qed_dmae_info_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	dma_addr_t p_phys;

	/* Just make sure no one is in the middle */
	mutex_lock(&p_hwfn->dmae_info.mutex);

	अगर (p_hwfn->dmae_info.p_completion_word) अणु
		p_phys = p_hwfn->dmae_info.completion_word_phys_addr;
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  माप(u32),
				  p_hwfn->dmae_info.p_completion_word, p_phys);
		p_hwfn->dmae_info.p_completion_word = शून्य;
	पूर्ण

	अगर (p_hwfn->dmae_info.p_dmae_cmd) अणु
		p_phys = p_hwfn->dmae_info.dmae_cmd_phys_addr;
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  माप(काष्ठा dmae_cmd),
				  p_hwfn->dmae_info.p_dmae_cmd, p_phys);
		p_hwfn->dmae_info.p_dmae_cmd = शून्य;
	पूर्ण

	अगर (p_hwfn->dmae_info.p_पूर्णांकermediate_buffer) अणु
		p_phys = p_hwfn->dmae_info.पूर्णांकermediate_buffer_phys_addr;
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  माप(u32) * DMAE_MAX_RW_SIZE,
				  p_hwfn->dmae_info.p_पूर्णांकermediate_buffer,
				  p_phys);
		p_hwfn->dmae_info.p_पूर्णांकermediate_buffer = शून्य;
	पूर्ण

	mutex_unlock(&p_hwfn->dmae_info.mutex);
पूर्ण

अटल पूर्णांक qed_dmae_operation_रुको(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 रुको_cnt_limit = 10000, रुको_cnt = 0;
	पूर्णांक qed_status = 0;

	barrier();
	जबतक (*p_hwfn->dmae_info.p_completion_word != DMAE_COMPLETION_VAL) अणु
		udelay(DMAE_MIN_WAIT_TIME);
		अगर (++रुको_cnt > रुको_cnt_limit) अणु
			DP_NOTICE(p_hwfn->cdev,
				  "Timed-out waiting for operation to complete. Completion word is 0x%08x expected 0x%08x.\n",
				  *p_hwfn->dmae_info.p_completion_word,
				 DMAE_COMPLETION_VAL);
			qed_status = -EBUSY;
			अवरोध;
		पूर्ण

		/* to sync the completion_word since we are not
		 * using the अस्थिर keyword क्रम p_completion_word
		 */
		barrier();
	पूर्ण

	अगर (qed_status == 0)
		*p_hwfn->dmae_info.p_completion_word = 0;

	वापस qed_status;
पूर्ण

अटल पूर्णांक qed_dmae_execute_sub_operation(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_ptt *p_ptt,
					  u64 src_addr,
					  u64 dst_addr,
					  u8 src_type,
					  u8 dst_type,
					  u32 length_dw)
अणु
	dma_addr_t phys = p_hwfn->dmae_info.पूर्णांकermediate_buffer_phys_addr;
	काष्ठा dmae_cmd *cmd = p_hwfn->dmae_info.p_dmae_cmd;
	पूर्णांक qed_status = 0;

	चयन (src_type) अणु
	हाल QED_DMAE_ADDRESS_GRC:
	हाल QED_DMAE_ADDRESS_HOST_PHYS:
		cmd->src_addr_hi = cpu_to_le32(upper_32_bits(src_addr));
		cmd->src_addr_lo = cpu_to_le32(lower_32_bits(src_addr));
		अवरोध;
	/* क्रम भव source addresses we use the पूर्णांकermediate buffer. */
	हाल QED_DMAE_ADDRESS_HOST_VIRT:
		cmd->src_addr_hi = cpu_to_le32(upper_32_bits(phys));
		cmd->src_addr_lo = cpu_to_le32(lower_32_bits(phys));
		स_नकल(&p_hwfn->dmae_info.p_पूर्णांकermediate_buffer[0],
		       (व्योम *)(uपूर्णांकptr_t)src_addr,
		       length_dw * माप(u32));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dst_type) अणु
	हाल QED_DMAE_ADDRESS_GRC:
	हाल QED_DMAE_ADDRESS_HOST_PHYS:
		cmd->dst_addr_hi = cpu_to_le32(upper_32_bits(dst_addr));
		cmd->dst_addr_lo = cpu_to_le32(lower_32_bits(dst_addr));
		अवरोध;
	/* क्रम भव source addresses we use the पूर्णांकermediate buffer. */
	हाल QED_DMAE_ADDRESS_HOST_VIRT:
		cmd->dst_addr_hi = cpu_to_le32(upper_32_bits(phys));
		cmd->dst_addr_lo = cpu_to_le32(lower_32_bits(phys));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cmd->length_dw = cpu_to_le16((u16)length_dw);

	qed_dmae_post_command(p_hwfn, p_ptt);

	qed_status = qed_dmae_operation_रुको(p_hwfn);

	अगर (qed_status) अणु
		DP_NOTICE(p_hwfn,
			  "qed_dmae_host2grc: Wait Failed. source_addr 0x%llx, grc_addr 0x%llx, size_in_dwords 0x%x\n",
			  src_addr, dst_addr, length_dw);
		वापस qed_status;
	पूर्ण

	अगर (dst_type == QED_DMAE_ADDRESS_HOST_VIRT)
		स_नकल((व्योम *)(uपूर्णांकptr_t)(dst_addr),
		       &p_hwfn->dmae_info.p_पूर्णांकermediate_buffer[0],
		       length_dw * माप(u32));

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dmae_execute_command(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    u64 src_addr, u64 dst_addr,
				    u8 src_type, u8 dst_type,
				    u32 size_in_dwords,
				    काष्ठा qed_dmae_params *p_params)
अणु
	dma_addr_t phys = p_hwfn->dmae_info.completion_word_phys_addr;
	u16 length_cur = 0, i = 0, cnt_split = 0, length_mod = 0;
	काष्ठा dmae_cmd *cmd = p_hwfn->dmae_info.p_dmae_cmd;
	u64 src_addr_split = 0, dst_addr_split = 0;
	u16 length_limit = DMAE_MAX_RW_SIZE;
	पूर्णांक qed_status = 0;
	u32 offset = 0;

	अगर (p_hwfn->cdev->recov_in_prog) अणु
		DP_VERBOSE(p_hwfn,
			   NETIF_MSG_HW,
			   "Recovery is in progress. Avoid DMAE transaction [{src: addr 0x%llx, type %d}, {dst: addr 0x%llx, type %d}, size %d].\n",
			   src_addr, src_type, dst_addr, dst_type,
			   size_in_dwords);

		/* Let the flow complete w/o any error handling */
		वापस 0;
	पूर्ण

	qed_dmae_opcode(p_hwfn,
			(src_type == QED_DMAE_ADDRESS_GRC),
			(dst_type == QED_DMAE_ADDRESS_GRC),
			p_params);

	cmd->comp_addr_lo = cpu_to_le32(lower_32_bits(phys));
	cmd->comp_addr_hi = cpu_to_le32(upper_32_bits(phys));
	cmd->comp_val = cpu_to_le32(DMAE_COMPLETION_VAL);

	/* Check अगर the grc_addr is valid like < MAX_GRC_OFFSET */
	cnt_split = size_in_dwords / length_limit;
	length_mod = size_in_dwords % length_limit;

	src_addr_split = src_addr;
	dst_addr_split = dst_addr;

	क्रम (i = 0; i <= cnt_split; i++) अणु
		offset = length_limit * i;

		अगर (!QED_DMAE_FLAGS_IS_SET(p_params, RW_REPL_SRC)) अणु
			अगर (src_type == QED_DMAE_ADDRESS_GRC)
				src_addr_split = src_addr + offset;
			अन्यथा
				src_addr_split = src_addr + (offset * 4);
		पूर्ण

		अगर (dst_type == QED_DMAE_ADDRESS_GRC)
			dst_addr_split = dst_addr + offset;
		अन्यथा
			dst_addr_split = dst_addr + (offset * 4);

		length_cur = (cnt_split == i) ? length_mod : length_limit;

		/* might be zero on last iteration */
		अगर (!length_cur)
			जारी;

		qed_status = qed_dmae_execute_sub_operation(p_hwfn,
							    p_ptt,
							    src_addr_split,
							    dst_addr_split,
							    src_type,
							    dst_type,
							    length_cur);
		अगर (qed_status) अणु
			qed_hw_err_notअगरy(p_hwfn, p_ptt, QED_HW_ERR_DMAE_FAIL,
					  "qed_dmae_execute_sub_operation Failed with error 0x%x. source_addr 0x%llx, destination addr 0x%llx, size_in_dwords 0x%x\n",
					  qed_status, src_addr,
					  dst_addr, length_cur);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस qed_status;
पूर्ण

पूर्णांक qed_dmae_host2grc(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      u64 source_addr, u32 grc_addr, u32 size_in_dwords,
		      काष्ठा qed_dmae_params *p_params)
अणु
	u32 grc_addr_in_dw = grc_addr / माप(u32);
	पूर्णांक rc;


	mutex_lock(&p_hwfn->dmae_info.mutex);

	rc = qed_dmae_execute_command(p_hwfn, p_ptt, source_addr,
				      grc_addr_in_dw,
				      QED_DMAE_ADDRESS_HOST_VIRT,
				      QED_DMAE_ADDRESS_GRC,
				      size_in_dwords, p_params);

	mutex_unlock(&p_hwfn->dmae_info.mutex);

	वापस rc;
पूर्ण

पूर्णांक qed_dmae_grc2host(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      u32 grc_addr,
		      dma_addr_t dest_addr, u32 size_in_dwords,
		      काष्ठा qed_dmae_params *p_params)
अणु
	u32 grc_addr_in_dw = grc_addr / माप(u32);
	पूर्णांक rc;


	mutex_lock(&p_hwfn->dmae_info.mutex);

	rc = qed_dmae_execute_command(p_hwfn, p_ptt, grc_addr_in_dw,
				      dest_addr, QED_DMAE_ADDRESS_GRC,
				      QED_DMAE_ADDRESS_HOST_VIRT,
				      size_in_dwords, p_params);

	mutex_unlock(&p_hwfn->dmae_info.mutex);

	वापस rc;
पूर्ण

पूर्णांक qed_dmae_host2host(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       dma_addr_t source_addr,
		       dma_addr_t dest_addr,
		       u32 size_in_dwords, काष्ठा qed_dmae_params *p_params)
अणु
	पूर्णांक rc;

	mutex_lock(&(p_hwfn->dmae_info.mutex));

	rc = qed_dmae_execute_command(p_hwfn, p_ptt, source_addr,
				      dest_addr,
				      QED_DMAE_ADDRESS_HOST_PHYS,
				      QED_DMAE_ADDRESS_HOST_PHYS,
				      size_in_dwords, p_params);

	mutex_unlock(&(p_hwfn->dmae_info.mutex));

	वापस rc;
पूर्ण

व्योम qed_hw_err_notअगरy(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
		       क्रमागत qed_hw_err_type err_type, स्थिर अक्षर *fmt, ...)
अणु
	अक्षर buf[QED_HW_ERR_MAX_STR_SIZE];
	बहु_सूची vl;
	पूर्णांक len;

	अगर (fmt) अणु
		बहु_शुरू(vl, fmt);
		len = vsnम_लिखो(buf, QED_HW_ERR_MAX_STR_SIZE, fmt, vl);
		बहु_पूर्ण(vl);

		अगर (len > QED_HW_ERR_MAX_STR_SIZE - 1)
			len = QED_HW_ERR_MAX_STR_SIZE - 1;

		DP_NOTICE(p_hwfn, "%s", buf);
	पूर्ण

	/* Fan failure cannot be masked by handling of another HW error */
	अगर (p_hwfn->cdev->recov_in_prog &&
	    err_type != QED_HW_ERR_FAN_FAIL) अणु
		DP_VERBOSE(p_hwfn,
			   NETIF_MSG_DRV,
			   "Recovery is in progress. Avoid notifying about HW error %d.\n",
			   err_type);
		वापस;
	पूर्ण

	qed_hw_error_occurred(p_hwfn, err_type);

	अगर (fmt)
		qed_mcp_send_raw_debug_data(p_hwfn, p_ptt, buf, len);
पूर्ण

पूर्णांक qed_dmae_sanity(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt, स्थिर अक्षर *phase)
अणु
	u32 size = PAGE_SIZE / 2, val;
	पूर्णांक rc = 0;
	dma_addr_t p_phys;
	व्योम *p_virt;
	u32 *p_पंचांगp;

	p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    2 * size, &p_phys, GFP_KERNEL);
	अगर (!p_virt) अणु
		DP_NOTICE(p_hwfn,
			  "DMAE sanity [%s]: failed to allocate memory\n",
			  phase);
		वापस -ENOMEM;
	पूर्ण

	/* Fill the bottom half of the allocated memory with a known pattern */
	क्रम (p_पंचांगp = (u32 *)p_virt;
	     p_पंचांगp < (u32 *)((u8 *)p_virt + size); p_पंचांगp++) अणु
		/* Save the address itself as the value */
		val = (u32)(uपूर्णांकptr_t)p_पंचांगp;
		*p_पंचांगp = val;
	पूर्ण

	/* Zero the top half of the allocated memory */
	स_रखो((u8 *)p_virt + size, 0, size);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "DMAE sanity [%s]: src_addr={phys 0x%llx, virt %p}, dst_addr={phys 0x%llx, virt %p}, size 0x%x\n",
		   phase,
		   (u64)p_phys,
		   p_virt, (u64)(p_phys + size), (u8 *)p_virt + size, size);

	rc = qed_dmae_host2host(p_hwfn, p_ptt, p_phys, p_phys + size,
				size / 4, शून्य);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn,
			  "DMAE sanity [%s]: qed_dmae_host2host() failed. rc = %d.\n",
			  phase, rc);
		जाओ out;
	पूर्ण

	/* Verअगरy that the top half of the allocated memory has the pattern */
	क्रम (p_पंचांगp = (u32 *)((u8 *)p_virt + size);
	     p_पंचांगp < (u32 *)((u8 *)p_virt + (2 * size)); p_पंचांगp++) अणु
		/* The corresponding address in the bottom half */
		val = (u32)(uपूर्णांकptr_t)p_पंचांगp - size;

		अगर (*p_पंचांगp != val) अणु
			DP_NOTICE(p_hwfn,
				  "DMAE sanity [%s]: addr={phys 0x%llx, virt %p}, read_val 0x%08x, expected_val 0x%08x\n",
				  phase,
				  (u64)p_phys + ((u8 *)p_पंचांगp - (u8 *)p_virt),
				  p_पंचांगp, *p_पंचांगp, val);
			rc = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev, 2 * size, p_virt, p_phys);
	वापस rc;
पूर्ण
