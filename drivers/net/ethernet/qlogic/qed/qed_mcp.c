<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/etherdevice.h>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dcbx.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sriov.h"

#घोषणा GRCBASE_MCP     0xe00000

#घोषणा QED_MCP_RESP_ITER_US	10

#घोषणा QED_DRV_MB_MAX_RETRIES	(500 * 1000)	/* Account क्रम 5 sec */
#घोषणा QED_MCP_RESET_RETRIES	(50 * 1000)	/* Account क्रम 500 msec */

#घोषणा DRV_INNER_WR(_p_hwfn, _p_ptt, _ptr, _offset, _val)	     \
	qed_wr(_p_hwfn, _p_ptt, (_p_hwfn->mcp_info->_ptr + _offset), \
	       _val)

#घोषणा DRV_INNER_RD(_p_hwfn, _p_ptt, _ptr, _offset) \
	qed_rd(_p_hwfn, _p_ptt, (_p_hwfn->mcp_info->_ptr + _offset))

#घोषणा DRV_MB_WR(_p_hwfn, _p_ptt, _field, _val)  \
	DRV_INNER_WR(p_hwfn, _p_ptt, drv_mb_addr, \
		     दुरत्व(काष्ठा खुला_drv_mb, _field), _val)

#घोषणा DRV_MB_RD(_p_hwfn, _p_ptt, _field)	   \
	DRV_INNER_RD(_p_hwfn, _p_ptt, drv_mb_addr, \
		     दुरत्व(काष्ठा खुला_drv_mb, _field))

#घोषणा PDA_COMP (((FW_MAJOR_VERSION) + (FW_MINOR_VERSION << 8)) << \
		  DRV_ID_PDA_COMP_VER_SHIFT)

#घोषणा MCP_BYTES_PER_MBIT_SHIFT 17

bool qed_mcp_is_init(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn->mcp_info || !p_hwfn->mcp_info->खुला_base)
		वापस false;
	वापस true;
पूर्ण

व्योम qed_mcp_cmd_port_init(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->खुला_base,
					PUBLIC_PORT);
	u32 mfw_mb_offsize = qed_rd(p_hwfn, p_ptt, addr);

	p_hwfn->mcp_info->port_addr = SECTION_ADDR(mfw_mb_offsize,
						   MFW_PORT(p_hwfn));
	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "port_addr = 0x%x, port_id 0x%02x\n",
		   p_hwfn->mcp_info->port_addr, MFW_PORT(p_hwfn));
पूर्ण

व्योम qed_mcp_पढ़ो_mb(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 length = MFW_DRV_MSG_MAX_DWORDS(p_hwfn->mcp_info->mfw_mb_length);
	u32 पंचांगp, i;

	अगर (!p_hwfn->mcp_info->खुला_base)
		वापस;

	क्रम (i = 0; i < length; i++) अणु
		पंचांगp = qed_rd(p_hwfn, p_ptt,
			     p_hwfn->mcp_info->mfw_mb_addr +
			     (i << 2) + माप(u32));

		/* The MB data is actually BE; Need to क्रमce it to cpu */
		((u32 *)p_hwfn->mcp_info->mfw_mb_cur)[i] =
			be32_to_cpu((__क्रमce __be32)पंचांगp);
	पूर्ण
पूर्ण

काष्ठा qed_mcp_cmd_elem अणु
	काष्ठा list_head list;
	काष्ठा qed_mcp_mb_params *p_mb_params;
	u16 expected_seq_num;
	bool b_is_completed;
पूर्ण;

/* Must be called जबतक cmd_lock is acquired */
अटल काष्ठा qed_mcp_cmd_elem *
qed_mcp_cmd_add_elem(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_mcp_mb_params *p_mb_params,
		     u16 expected_seq_num)
अणु
	काष्ठा qed_mcp_cmd_elem *p_cmd_elem = शून्य;

	p_cmd_elem = kzalloc(माप(*p_cmd_elem), GFP_ATOMIC);
	अगर (!p_cmd_elem)
		जाओ out;

	p_cmd_elem->p_mb_params = p_mb_params;
	p_cmd_elem->expected_seq_num = expected_seq_num;
	list_add(&p_cmd_elem->list, &p_hwfn->mcp_info->cmd_list);
out:
	वापस p_cmd_elem;
पूर्ण

/* Must be called जबतक cmd_lock is acquired */
अटल व्योम qed_mcp_cmd_del_elem(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_mcp_cmd_elem *p_cmd_elem)
अणु
	list_del(&p_cmd_elem->list);
	kमुक्त(p_cmd_elem);
पूर्ण

/* Must be called जबतक cmd_lock is acquired */
अटल काष्ठा qed_mcp_cmd_elem *qed_mcp_cmd_get_elem(काष्ठा qed_hwfn *p_hwfn,
						     u16 seq_num)
अणु
	काष्ठा qed_mcp_cmd_elem *p_cmd_elem = शून्य;

	list_क्रम_each_entry(p_cmd_elem, &p_hwfn->mcp_info->cmd_list, list) अणु
		अगर (p_cmd_elem->expected_seq_num == seq_num)
			वापस p_cmd_elem;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक qed_mcp_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (p_hwfn->mcp_info) अणु
		काष्ठा qed_mcp_cmd_elem *p_cmd_elem, *p_पंचांगp;

		kमुक्त(p_hwfn->mcp_info->mfw_mb_cur);
		kमुक्त(p_hwfn->mcp_info->mfw_mb_shaकरोw);

		spin_lock_bh(&p_hwfn->mcp_info->cmd_lock);
		list_क्रम_each_entry_safe(p_cmd_elem,
					 p_पंचांगp,
					 &p_hwfn->mcp_info->cmd_list, list) अणु
			qed_mcp_cmd_del_elem(p_hwfn, p_cmd_elem);
		पूर्ण
		spin_unlock_bh(&p_hwfn->mcp_info->cmd_lock);
	पूर्ण

	kमुक्त(p_hwfn->mcp_info);
	p_hwfn->mcp_info = शून्य;

	वापस 0;
पूर्ण

/* Maximum of 1 sec to रुको क्रम the SHMEM पढ़ोy indication */
#घोषणा QED_MCP_SHMEM_RDY_MAX_RETRIES	20
#घोषणा QED_MCP_SHMEM_RDY_ITER_MS	50

अटल पूर्णांक qed_load_mcp_offsets(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_info *p_info = p_hwfn->mcp_info;
	u8 cnt = QED_MCP_SHMEM_RDY_MAX_RETRIES;
	u8 msec = QED_MCP_SHMEM_RDY_ITER_MS;
	u32 drv_mb_offsize, mfw_mb_offsize;
	u32 mcp_pf_id = MCP_PF_ID(p_hwfn);

	p_info->खुला_base = qed_rd(p_hwfn, p_ptt, MISC_REG_SHARED_MEM_ADDR);
	अगर (!p_info->खुला_base) अणु
		DP_NOTICE(p_hwfn,
			  "The address of the MCP scratch-pad is not configured\n");
		वापस -EINVAL;
	पूर्ण

	p_info->खुला_base |= GRCBASE_MCP;

	/* Get the MFW MB address and number of supported messages */
	mfw_mb_offsize = qed_rd(p_hwfn, p_ptt,
				SECTION_OFFSIZE_ADDR(p_info->खुला_base,
						     PUBLIC_MFW_MB));
	p_info->mfw_mb_addr = SECTION_ADDR(mfw_mb_offsize, mcp_pf_id);
	p_info->mfw_mb_length = (u16)qed_rd(p_hwfn, p_ptt,
					    p_info->mfw_mb_addr +
					    दुरत्व(काष्ठा खुला_mfw_mb,
						     sup_msgs));

	/* The driver can notअगरy that there was an MCP reset, and might पढ़ो the
	 * SHMEM values beक्रमe the MFW has completed initializing them.
	 * To aव्योम this, the "sup_msgs" field in the MFW mailbox is used as a
	 * data पढ़ोy indication.
	 */
	जबतक (!p_info->mfw_mb_length && --cnt) अणु
		msleep(msec);
		p_info->mfw_mb_length =
			(u16)qed_rd(p_hwfn, p_ptt,
				    p_info->mfw_mb_addr +
				    दुरत्व(काष्ठा खुला_mfw_mb, sup_msgs));
	पूर्ण

	अगर (!cnt) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to get the SHMEM ready notification after %d msec\n",
			  QED_MCP_SHMEM_RDY_MAX_RETRIES * msec);
		वापस -EBUSY;
	पूर्ण

	/* Calculate the driver and MFW mailbox address */
	drv_mb_offsize = qed_rd(p_hwfn, p_ptt,
				SECTION_OFFSIZE_ADDR(p_info->खुला_base,
						     PUBLIC_DRV_MB));
	p_info->drv_mb_addr = SECTION_ADDR(drv_mb_offsize, mcp_pf_id);
	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "drv_mb_offsiz = 0x%x, drv_mb_addr = 0x%x mcp_pf_id = 0x%x\n",
		   drv_mb_offsize, p_info->drv_mb_addr, mcp_pf_id);

	/* Get the current driver mailbox sequence beक्रमe sending
	 * the first command
	 */
	p_info->drv_mb_seq = DRV_MB_RD(p_hwfn, p_ptt, drv_mb_header) &
			     DRV_MSG_SEQ_NUMBER_MASK;

	/* Get current FW pulse sequence */
	p_info->drv_pulse_seq = DRV_MB_RD(p_hwfn, p_ptt, drv_pulse_mb) &
				DRV_PULSE_SEQ_MASK;

	p_info->mcp_hist = qed_rd(p_hwfn, p_ptt, MISCS_REG_GENERIC_POR_0);

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_cmd_init(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_info *p_info;
	u32 size;

	/* Allocate mcp_info काष्ठाure */
	p_hwfn->mcp_info = kzalloc(माप(*p_hwfn->mcp_info), GFP_KERNEL);
	अगर (!p_hwfn->mcp_info)
		जाओ err;
	p_info = p_hwfn->mcp_info;

	/* Initialize the MFW spinlock */
	spin_lock_init(&p_info->cmd_lock);
	spin_lock_init(&p_info->link_lock);

	INIT_LIST_HEAD(&p_info->cmd_list);

	अगर (qed_load_mcp_offsets(p_hwfn, p_ptt) != 0) अणु
		DP_NOTICE(p_hwfn, "MCP is not initialized\n");
		/* Do not मुक्त mcp_info here, since खुला_base indicate that
		 * the MCP is not initialized
		 */
		वापस 0;
	पूर्ण

	size = MFW_DRV_MSG_MAX_DWORDS(p_info->mfw_mb_length) * माप(u32);
	p_info->mfw_mb_cur = kzalloc(size, GFP_KERNEL);
	p_info->mfw_mb_shaकरोw = kzalloc(size, GFP_KERNEL);
	अगर (!p_info->mfw_mb_cur || !p_info->mfw_mb_shaकरोw)
		जाओ err;

	वापस 0;

err:
	qed_mcp_मुक्त(p_hwfn);
	वापस -ENOMEM;
पूर्ण

अटल व्योम qed_mcp_reपढ़ो_offsets(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt)
अणु
	u32 generic_por_0 = qed_rd(p_hwfn, p_ptt, MISCS_REG_GENERIC_POR_0);

	/* Use MCP history रेजिस्टर to check अगर MCP reset occurred between init
	 * समय and now.
	 */
	अगर (p_hwfn->mcp_info->mcp_hist != generic_por_0) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SP,
			   "Rereading MCP offsets [mcp_hist 0x%08x, generic_por_0 0x%08x]\n",
			   p_hwfn->mcp_info->mcp_hist, generic_por_0);

		qed_load_mcp_offsets(p_hwfn, p_ptt);
		qed_mcp_cmd_port_init(p_hwfn, p_ptt);
	पूर्ण
पूर्ण

पूर्णांक qed_mcp_reset(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 org_mcp_reset_seq, seq, delay = QED_MCP_RESP_ITER_US, cnt = 0;
	पूर्णांक rc = 0;

	अगर (p_hwfn->mcp_info->b_block_cmd) अणु
		DP_NOTICE(p_hwfn,
			  "The MFW is not responsive. Avoid sending MCP_RESET mailbox command.\n");
		वापस -EBUSY;
	पूर्ण

	/* Ensure that only a single thपढ़ो is accessing the mailbox */
	spin_lock_bh(&p_hwfn->mcp_info->cmd_lock);

	org_mcp_reset_seq = qed_rd(p_hwfn, p_ptt, MISCS_REG_GENERIC_POR_0);

	/* Set drv command aदीर्घ with the updated sequence */
	qed_mcp_reपढ़ो_offsets(p_hwfn, p_ptt);
	seq = ++p_hwfn->mcp_info->drv_mb_seq;
	DRV_MB_WR(p_hwfn, p_ptt, drv_mb_header, (DRV_MSG_CODE_MCP_RESET | seq));

	करो अणु
		/* Wait क्रम MFW response */
		udelay(delay);
		/* Give the FW up to 500 second (50*1000*10usec) */
	पूर्ण जबतक ((org_mcp_reset_seq == qed_rd(p_hwfn, p_ptt,
					      MISCS_REG_GENERIC_POR_0)) &&
		 (cnt++ < QED_MCP_RESET_RETRIES));

	अगर (org_mcp_reset_seq !=
	    qed_rd(p_hwfn, p_ptt, MISCS_REG_GENERIC_POR_0)) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "MCP was reset after %d usec\n", cnt * delay);
	पूर्ण अन्यथा अणु
		DP_ERR(p_hwfn, "Failed to reset MCP\n");
		rc = -EAGAIN;
	पूर्ण

	spin_unlock_bh(&p_hwfn->mcp_info->cmd_lock);

	वापस rc;
पूर्ण

/* Must be called जबतक cmd_lock is acquired */
अटल bool qed_mcp_has_pending_cmd(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_mcp_cmd_elem *p_cmd_elem;

	/* There is at most one pending command at a certain समय, and अगर it
	 * exists - it is placed at the HEAD of the list.
	 */
	अगर (!list_empty(&p_hwfn->mcp_info->cmd_list)) अणु
		p_cmd_elem = list_first_entry(&p_hwfn->mcp_info->cmd_list,
					      काष्ठा qed_mcp_cmd_elem, list);
		वापस !p_cmd_elem->b_is_completed;
	पूर्ण

	वापस false;
पूर्ण

/* Must be called जबतक cmd_lock is acquired */
अटल पूर्णांक
qed_mcp_update_pending_cmd(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_mb_params *p_mb_params;
	काष्ठा qed_mcp_cmd_elem *p_cmd_elem;
	u32 mcp_resp;
	u16 seq_num;

	mcp_resp = DRV_MB_RD(p_hwfn, p_ptt, fw_mb_header);
	seq_num = (u16)(mcp_resp & FW_MSG_SEQ_NUMBER_MASK);

	/* Return अगर no new non-handled response has been received */
	अगर (seq_num != p_hwfn->mcp_info->drv_mb_seq)
		वापस -EAGAIN;

	p_cmd_elem = qed_mcp_cmd_get_elem(p_hwfn, seq_num);
	अगर (!p_cmd_elem) अणु
		DP_ERR(p_hwfn,
		       "Failed to find a pending mailbox cmd that expects sequence number %d\n",
		       seq_num);
		वापस -EINVAL;
	पूर्ण

	p_mb_params = p_cmd_elem->p_mb_params;

	/* Get the MFW response aदीर्घ with the sequence number */
	p_mb_params->mcp_resp = mcp_resp;

	/* Get the MFW param */
	p_mb_params->mcp_param = DRV_MB_RD(p_hwfn, p_ptt, fw_mb_param);

	/* Get the जोड़ data */
	अगर (p_mb_params->p_data_dst != शून्य && p_mb_params->data_dst_size) अणु
		u32 जोड़_data_addr = p_hwfn->mcp_info->drv_mb_addr +
				      दुरत्व(काष्ठा खुला_drv_mb,
					       जोड़_data);
		qed_स_नकल_from(p_hwfn, p_ptt, p_mb_params->p_data_dst,
				जोड़_data_addr, p_mb_params->data_dst_size);
	पूर्ण

	p_cmd_elem->b_is_completed = true;

	वापस 0;
पूर्ण

/* Must be called जबतक cmd_lock is acquired */
अटल व्योम __qed_mcp_cmd_and_जोड़(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    काष्ठा qed_mcp_mb_params *p_mb_params,
				    u16 seq_num)
अणु
	जोड़ drv_जोड़_data जोड़_data;
	u32 जोड़_data_addr;

	/* Set the जोड़ data */
	जोड़_data_addr = p_hwfn->mcp_info->drv_mb_addr +
			  दुरत्व(काष्ठा खुला_drv_mb, जोड़_data);
	स_रखो(&जोड़_data, 0, माप(जोड़_data));
	अगर (p_mb_params->p_data_src != शून्य && p_mb_params->data_src_size)
		स_नकल(&जोड़_data, p_mb_params->p_data_src,
		       p_mb_params->data_src_size);
	qed_स_नकल_to(p_hwfn, p_ptt, जोड़_data_addr, &जोड़_data,
		      माप(जोड़_data));

	/* Set the drv param */
	DRV_MB_WR(p_hwfn, p_ptt, drv_mb_param, p_mb_params->param);

	/* Set the drv command aदीर्घ with the sequence number */
	DRV_MB_WR(p_hwfn, p_ptt, drv_mb_header, (p_mb_params->cmd | seq_num));

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "MFW mailbox: command 0x%08x param 0x%08x\n",
		   (p_mb_params->cmd | seq_num), p_mb_params->param);
पूर्ण

अटल व्योम qed_mcp_cmd_set_blocking(काष्ठा qed_hwfn *p_hwfn, bool block_cmd)
अणु
	p_hwfn->mcp_info->b_block_cmd = block_cmd;

	DP_INFO(p_hwfn, "%s sending of mailbox commands to the MFW\n",
		block_cmd ? "Block" : "Unblock");
पूर्ण

अटल व्योम qed_mcp_prपूर्णांक_cpu_info(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt)
अणु
	u32 cpu_mode, cpu_state, cpu_pc_0, cpu_pc_1, cpu_pc_2;
	u32 delay = QED_MCP_RESP_ITER_US;

	cpu_mode = qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_MODE);
	cpu_state = qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_STATE);
	cpu_pc_0 = qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_PROGRAM_COUNTER);
	udelay(delay);
	cpu_pc_1 = qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_PROGRAM_COUNTER);
	udelay(delay);
	cpu_pc_2 = qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_PROGRAM_COUNTER);

	DP_NOTICE(p_hwfn,
		  "MCP CPU info: mode 0x%08x, state 0x%08x, pc {0x%08x, 0x%08x, 0x%08x}\n",
		  cpu_mode, cpu_state, cpu_pc_0, cpu_pc_1, cpu_pc_2);
पूर्ण

अटल पूर्णांक
_qed_mcp_cmd_and_जोड़(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       काष्ठा qed_mcp_mb_params *p_mb_params,
		       u32 max_retries, u32 usecs)
अणु
	u32 cnt = 0, msecs = DIV_ROUND_UP(usecs, 1000);
	काष्ठा qed_mcp_cmd_elem *p_cmd_elem;
	u16 seq_num;
	पूर्णांक rc = 0;

	/* Wait until the mailbox is non-occupied */
	करो अणु
		/* Exit the loop अगर there is no pending command, or अगर the
		 * pending command is completed during this iteration.
		 * The spinlock stays locked until the command is sent.
		 */

		spin_lock_bh(&p_hwfn->mcp_info->cmd_lock);

		अगर (!qed_mcp_has_pending_cmd(p_hwfn))
			अवरोध;

		rc = qed_mcp_update_pending_cmd(p_hwfn, p_ptt);
		अगर (!rc)
			अवरोध;
		अन्यथा अगर (rc != -EAGAIN)
			जाओ err;

		spin_unlock_bh(&p_hwfn->mcp_info->cmd_lock);

		अगर (QED_MB_FLAGS_IS_SET(p_mb_params, CAN_SLEEP))
			msleep(msecs);
		अन्यथा
			udelay(usecs);
	पूर्ण जबतक (++cnt < max_retries);

	अगर (cnt >= max_retries) अणु
		DP_NOTICE(p_hwfn,
			  "The MFW mailbox is occupied by an uncompleted command. Failed to send command 0x%08x [param 0x%08x].\n",
			  p_mb_params->cmd, p_mb_params->param);
		वापस -EAGAIN;
	पूर्ण

	/* Send the mailbox command */
	qed_mcp_reपढ़ो_offsets(p_hwfn, p_ptt);
	seq_num = ++p_hwfn->mcp_info->drv_mb_seq;
	p_cmd_elem = qed_mcp_cmd_add_elem(p_hwfn, p_mb_params, seq_num);
	अगर (!p_cmd_elem) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	__qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, p_mb_params, seq_num);
	spin_unlock_bh(&p_hwfn->mcp_info->cmd_lock);

	/* Wait क्रम the MFW response */
	करो अणु
		/* Exit the loop अगर the command is alपढ़ोy completed, or अगर the
		 * command is completed during this iteration.
		 * The spinlock stays locked until the list element is हटाओd.
		 */

		अगर (QED_MB_FLAGS_IS_SET(p_mb_params, CAN_SLEEP))
			msleep(msecs);
		अन्यथा
			udelay(usecs);

		spin_lock_bh(&p_hwfn->mcp_info->cmd_lock);

		अगर (p_cmd_elem->b_is_completed)
			अवरोध;

		rc = qed_mcp_update_pending_cmd(p_hwfn, p_ptt);
		अगर (!rc)
			अवरोध;
		अन्यथा अगर (rc != -EAGAIN)
			जाओ err;

		spin_unlock_bh(&p_hwfn->mcp_info->cmd_lock);
	पूर्ण जबतक (++cnt < max_retries);

	अगर (cnt >= max_retries) अणु
		DP_NOTICE(p_hwfn,
			  "The MFW failed to respond to command 0x%08x [param 0x%08x].\n",
			  p_mb_params->cmd, p_mb_params->param);
		qed_mcp_prपूर्णांक_cpu_info(p_hwfn, p_ptt);

		spin_lock_bh(&p_hwfn->mcp_info->cmd_lock);
		qed_mcp_cmd_del_elem(p_hwfn, p_cmd_elem);
		spin_unlock_bh(&p_hwfn->mcp_info->cmd_lock);

		अगर (!QED_MB_FLAGS_IS_SET(p_mb_params, AVOID_BLOCK))
			qed_mcp_cmd_set_blocking(p_hwfn, true);

		qed_hw_err_notअगरy(p_hwfn, p_ptt,
				  QED_HW_ERR_MFW_RESP_FAIL, शून्य);
		वापस -EAGAIN;
	पूर्ण

	qed_mcp_cmd_del_elem(p_hwfn, p_cmd_elem);
	spin_unlock_bh(&p_hwfn->mcp_info->cmd_lock);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "MFW mailbox: response 0x%08x param 0x%08x [after %d.%03d ms]\n",
		   p_mb_params->mcp_resp,
		   p_mb_params->mcp_param,
		   (cnt * usecs) / 1000, (cnt * usecs) % 1000);

	/* Clear the sequence number from the MFW response */
	p_mb_params->mcp_resp &= FW_MSG_CODE_MASK;

	वापस 0;

err:
	spin_unlock_bh(&p_hwfn->mcp_info->cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_mcp_cmd_and_जोड़(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 काष्ठा qed_mcp_mb_params *p_mb_params)
अणु
	माप_प्रकार जोड़_data_size = माप(जोड़ drv_जोड़_data);
	u32 max_retries = QED_DRV_MB_MAX_RETRIES;
	u32 usecs = QED_MCP_RESP_ITER_US;

	/* MCP not initialized */
	अगर (!qed_mcp_is_init(p_hwfn)) अणु
		DP_NOTICE(p_hwfn, "MFW is not initialized!\n");
		वापस -EBUSY;
	पूर्ण

	अगर (p_hwfn->mcp_info->b_block_cmd) अणु
		DP_NOTICE(p_hwfn,
			  "The MFW is not responsive. Avoid sending mailbox command 0x%08x [param 0x%08x].\n",
			  p_mb_params->cmd, p_mb_params->param);
		वापस -EBUSY;
	पूर्ण

	अगर (p_mb_params->data_src_size > जोड़_data_size ||
	    p_mb_params->data_dst_size > जोड़_data_size) अणु
		DP_ERR(p_hwfn,
		       "The provided size is larger than the union data size [src_size %u, dst_size %u, union_data_size %zu]\n",
		       p_mb_params->data_src_size,
		       p_mb_params->data_dst_size, जोड़_data_size);
		वापस -EINVAL;
	पूर्ण

	अगर (QED_MB_FLAGS_IS_SET(p_mb_params, CAN_SLEEP)) अणु
		max_retries = DIV_ROUND_UP(max_retries, 1000);
		usecs *= 1000;
	पूर्ण

	वापस _qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, p_mb_params, max_retries,
				      usecs);
पूर्ण

पूर्णांक qed_mcp_cmd(काष्ठा qed_hwfn *p_hwfn,
		काष्ठा qed_ptt *p_ptt,
		u32 cmd,
		u32 param,
		u32 *o_mcp_resp,
		u32 *o_mcp_param)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	पूर्णांक rc;

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = cmd;
	mb_params.param = param;

	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		वापस rc;

	*o_mcp_resp = mb_params.mcp_resp;
	*o_mcp_param = mb_params.mcp_param;

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_mcp_nvm_wr_cmd(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt,
		   u32 cmd,
		   u32 param,
		   u32 *o_mcp_resp,
		   u32 *o_mcp_param, u32 i_txn_size, u32 *i_buf)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	पूर्णांक rc;

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = cmd;
	mb_params.param = param;
	mb_params.p_data_src = i_buf;
	mb_params.data_src_size = (u8)i_txn_size;
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		वापस rc;

	*o_mcp_resp = mb_params.mcp_resp;
	*o_mcp_param = mb_params.mcp_param;

	/* nvm_info needs to be updated */
	p_hwfn->nvm_info.valid = false;

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_nvm_rd_cmd(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       u32 cmd,
		       u32 param,
		       u32 *o_mcp_resp,
		       u32 *o_mcp_param, u32 *o_txn_size, u32 *o_buf)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	u8 raw_data[MCP_DRV_NVM_BUF_LEN];
	पूर्णांक rc;

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = cmd;
	mb_params.param = param;
	mb_params.p_data_dst = raw_data;

	/* Use the maximal value since the actual one is part of the response */
	mb_params.data_dst_size = MCP_DRV_NVM_BUF_LEN;

	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		वापस rc;

	*o_mcp_resp = mb_params.mcp_resp;
	*o_mcp_param = mb_params.mcp_param;

	*o_txn_size = *o_mcp_param;
	स_नकल(o_buf, raw_data, *o_txn_size);

	वापस 0;
पूर्ण

अटल bool
qed_mcp_can_क्रमce_load(u8 drv_role,
		       u8 exist_drv_role,
		       क्रमागत qed_override_क्रमce_load override_क्रमce_load)
अणु
	bool can_क्रमce_load = false;

	चयन (override_क्रमce_load) अणु
	हाल QED_OVERRIDE_FORCE_LOAD_ALWAYS:
		can_क्रमce_load = true;
		अवरोध;
	हाल QED_OVERRIDE_FORCE_LOAD_NEVER:
		can_क्रमce_load = false;
		अवरोध;
	शेष:
		can_क्रमce_load = (drv_role == DRV_ROLE_OS &&
				  exist_drv_role == DRV_ROLE_PREBOOT) ||
				 (drv_role == DRV_ROLE_KDUMP &&
				  exist_drv_role == DRV_ROLE_OS);
		अवरोध;
	पूर्ण

	वापस can_क्रमce_load;
पूर्ण

अटल पूर्णांक qed_mcp_cancel_load_req(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt)
अणु
	u32 resp = 0, param = 0;
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_CANCEL_LOAD_REQ, 0,
			 &resp, &param);
	अगर (rc)
		DP_NOTICE(p_hwfn,
			  "Failed to send cancel load request, rc = %d\n", rc);

	वापस rc;
पूर्ण

#घोषणा CONFIG_QEDE_BITMAP_IDX		BIT(0)
#घोषणा CONFIG_QED_SRIOV_BITMAP_IDX	BIT(1)
#घोषणा CONFIG_QEDR_BITMAP_IDX		BIT(2)
#घोषणा CONFIG_QEDF_BITMAP_IDX		BIT(4)
#घोषणा CONFIG_QEDI_BITMAP_IDX		BIT(5)
#घोषणा CONFIG_QED_LL2_BITMAP_IDX	BIT(6)

अटल u32 qed_get_config_biपंचांगap(व्योम)
अणु
	u32 config_biपंचांगap = 0x0;

	अगर (IS_ENABLED(CONFIG_QEDE))
		config_biपंचांगap |= CONFIG_QEDE_BITMAP_IDX;

	अगर (IS_ENABLED(CONFIG_QED_SRIOV))
		config_biपंचांगap |= CONFIG_QED_SRIOV_BITMAP_IDX;

	अगर (IS_ENABLED(CONFIG_QED_RDMA))
		config_biपंचांगap |= CONFIG_QEDR_BITMAP_IDX;

	अगर (IS_ENABLED(CONFIG_QED_FCOE))
		config_biपंचांगap |= CONFIG_QEDF_BITMAP_IDX;

	अगर (IS_ENABLED(CONFIG_QED_ISCSI))
		config_biपंचांगap |= CONFIG_QEDI_BITMAP_IDX;

	अगर (IS_ENABLED(CONFIG_QED_LL2))
		config_biपंचांगap |= CONFIG_QED_LL2_BITMAP_IDX;

	वापस config_biपंचांगap;
पूर्ण

काष्ठा qed_load_req_in_params अणु
	u8 hsi_ver;
#घोषणा QED_LOAD_REQ_HSI_VER_DEFAULT	0
#घोषणा QED_LOAD_REQ_HSI_VER_1		1
	u32 drv_ver_0;
	u32 drv_ver_1;
	u32 fw_ver;
	u8 drv_role;
	u8 समयout_val;
	u8 क्रमce_cmd;
	bool aव्योम_eng_reset;
पूर्ण;

काष्ठा qed_load_req_out_params अणु
	u32 load_code;
	u32 exist_drv_ver_0;
	u32 exist_drv_ver_1;
	u32 exist_fw_ver;
	u8 exist_drv_role;
	u8 mfw_hsi_ver;
	bool drv_exists;
पूर्ण;

अटल पूर्णांक
__qed_mcp_load_req(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt,
		   काष्ठा qed_load_req_in_params *p_in_params,
		   काष्ठा qed_load_req_out_params *p_out_params)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	काष्ठा load_req_stc load_req;
	काष्ठा load_rsp_stc load_rsp;
	u32 hsi_ver;
	पूर्णांक rc;

	स_रखो(&load_req, 0, माप(load_req));
	load_req.drv_ver_0 = p_in_params->drv_ver_0;
	load_req.drv_ver_1 = p_in_params->drv_ver_1;
	load_req.fw_ver = p_in_params->fw_ver;
	QED_MFW_SET_FIELD(load_req.misc0, LOAD_REQ_ROLE, p_in_params->drv_role);
	QED_MFW_SET_FIELD(load_req.misc0, LOAD_REQ_LOCK_TO,
			  p_in_params->समयout_val);
	QED_MFW_SET_FIELD(load_req.misc0, LOAD_REQ_FORCE,
			  p_in_params->क्रमce_cmd);
	QED_MFW_SET_FIELD(load_req.misc0, LOAD_REQ_FLAGS0,
			  p_in_params->aव्योम_eng_reset);

	hsi_ver = (p_in_params->hsi_ver == QED_LOAD_REQ_HSI_VER_DEFAULT) ?
		  DRV_ID_MCP_HSI_VER_CURRENT :
		  (p_in_params->hsi_ver << DRV_ID_MCP_HSI_VER_SHIFT);

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_LOAD_REQ;
	mb_params.param = PDA_COMP | hsi_ver | p_hwfn->cdev->drv_type;
	mb_params.p_data_src = &load_req;
	mb_params.data_src_size = माप(load_req);
	mb_params.p_data_dst = &load_rsp;
	mb_params.data_dst_size = माप(load_rsp);
	mb_params.flags = QED_MB_FLAG_CAN_SLEEP | QED_MB_FLAG_AVOID_BLOCK;

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "Load Request: param 0x%08x [init_hw %d, drv_type %d, hsi_ver %d, pda 0x%04x]\n",
		   mb_params.param,
		   QED_MFW_GET_FIELD(mb_params.param, DRV_ID_DRV_INIT_HW),
		   QED_MFW_GET_FIELD(mb_params.param, DRV_ID_DRV_TYPE),
		   QED_MFW_GET_FIELD(mb_params.param, DRV_ID_MCP_HSI_VER),
		   QED_MFW_GET_FIELD(mb_params.param, DRV_ID_PDA_COMP_VER));

	अगर (p_in_params->hsi_ver != QED_LOAD_REQ_HSI_VER_1) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Load Request: drv_ver 0x%08x_0x%08x, fw_ver 0x%08x, misc0 0x%08x [role %d, timeout %d, force %d, flags0 0x%x]\n",
			   load_req.drv_ver_0,
			   load_req.drv_ver_1,
			   load_req.fw_ver,
			   load_req.misc0,
			   QED_MFW_GET_FIELD(load_req.misc0, LOAD_REQ_ROLE),
			   QED_MFW_GET_FIELD(load_req.misc0,
					     LOAD_REQ_LOCK_TO),
			   QED_MFW_GET_FIELD(load_req.misc0, LOAD_REQ_FORCE),
			   QED_MFW_GET_FIELD(load_req.misc0, LOAD_REQ_FLAGS0));
	पूर्ण

	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to send load request, rc = %d\n", rc);
		वापस rc;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "Load Response: resp 0x%08x\n", mb_params.mcp_resp);
	p_out_params->load_code = mb_params.mcp_resp;

	अगर (p_in_params->hsi_ver != QED_LOAD_REQ_HSI_VER_1 &&
	    p_out_params->load_code != FW_MSG_CODE_DRV_LOAD_REFUSED_HSI_1) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SP,
			   "Load Response: exist_drv_ver 0x%08x_0x%08x, exist_fw_ver 0x%08x, misc0 0x%08x [exist_role %d, mfw_hsi %d, flags0 0x%x]\n",
			   load_rsp.drv_ver_0,
			   load_rsp.drv_ver_1,
			   load_rsp.fw_ver,
			   load_rsp.misc0,
			   QED_MFW_GET_FIELD(load_rsp.misc0, LOAD_RSP_ROLE),
			   QED_MFW_GET_FIELD(load_rsp.misc0, LOAD_RSP_HSI),
			   QED_MFW_GET_FIELD(load_rsp.misc0, LOAD_RSP_FLAGS0));

		p_out_params->exist_drv_ver_0 = load_rsp.drv_ver_0;
		p_out_params->exist_drv_ver_1 = load_rsp.drv_ver_1;
		p_out_params->exist_fw_ver = load_rsp.fw_ver;
		p_out_params->exist_drv_role =
		    QED_MFW_GET_FIELD(load_rsp.misc0, LOAD_RSP_ROLE);
		p_out_params->mfw_hsi_ver =
		    QED_MFW_GET_FIELD(load_rsp.misc0, LOAD_RSP_HSI);
		p_out_params->drv_exists =
		    QED_MFW_GET_FIELD(load_rsp.misc0, LOAD_RSP_FLAGS0) &
		    LOAD_RSP_FLAGS0_DRV_EXISTS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक eocre_get_mfw_drv_role(काष्ठा qed_hwfn *p_hwfn,
				  क्रमागत qed_drv_role drv_role,
				  u8 *p_mfw_drv_role)
अणु
	चयन (drv_role) अणु
	हाल QED_DRV_ROLE_OS:
		*p_mfw_drv_role = DRV_ROLE_OS;
		अवरोध;
	हाल QED_DRV_ROLE_KDUMP:
		*p_mfw_drv_role = DRV_ROLE_KDUMP;
		अवरोध;
	शेष:
		DP_ERR(p_hwfn, "Unexpected driver role %d\n", drv_role);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत qed_load_req_क्रमce अणु
	QED_LOAD_REQ_FORCE_NONE,
	QED_LOAD_REQ_FORCE_PF,
	QED_LOAD_REQ_FORCE_ALL,
पूर्ण;

अटल व्योम qed_get_mfw_क्रमce_cmd(काष्ठा qed_hwfn *p_hwfn,

				  क्रमागत qed_load_req_क्रमce क्रमce_cmd,
				  u8 *p_mfw_क्रमce_cmd)
अणु
	चयन (क्रमce_cmd) अणु
	हाल QED_LOAD_REQ_FORCE_NONE:
		*p_mfw_क्रमce_cmd = LOAD_REQ_FORCE_NONE;
		अवरोध;
	हाल QED_LOAD_REQ_FORCE_PF:
		*p_mfw_क्रमce_cmd = LOAD_REQ_FORCE_PF;
		अवरोध;
	हाल QED_LOAD_REQ_FORCE_ALL:
		*p_mfw_क्रमce_cmd = LOAD_REQ_FORCE_ALL;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक qed_mcp_load_req(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt,
		     काष्ठा qed_load_req_params *p_params)
अणु
	काष्ठा qed_load_req_out_params out_params;
	काष्ठा qed_load_req_in_params in_params;
	u8 mfw_drv_role, mfw_क्रमce_cmd;
	पूर्णांक rc;

	स_रखो(&in_params, 0, माप(in_params));
	in_params.hsi_ver = QED_LOAD_REQ_HSI_VER_DEFAULT;
	in_params.drv_ver_0 = QED_VERSION;
	in_params.drv_ver_1 = qed_get_config_biपंचांगap();
	in_params.fw_ver = STORM_FW_VERSION;
	rc = eocre_get_mfw_drv_role(p_hwfn, p_params->drv_role, &mfw_drv_role);
	अगर (rc)
		वापस rc;

	in_params.drv_role = mfw_drv_role;
	in_params.समयout_val = p_params->समयout_val;
	qed_get_mfw_क्रमce_cmd(p_hwfn,
			      QED_LOAD_REQ_FORCE_NONE, &mfw_क्रमce_cmd);

	in_params.क्रमce_cmd = mfw_क्रमce_cmd;
	in_params.aव्योम_eng_reset = p_params->aव्योम_eng_reset;

	स_रखो(&out_params, 0, माप(out_params));
	rc = __qed_mcp_load_req(p_hwfn, p_ptt, &in_params, &out_params);
	अगर (rc)
		वापस rc;

	/* First handle हालs where another load request should/might be sent:
	 * - MFW expects the old पूर्णांकerface [HSI version = 1]
	 * - MFW responds that a क्रमce load request is required
	 */
	अगर (out_params.load_code == FW_MSG_CODE_DRV_LOAD_REFUSED_HSI_1) अणु
		DP_INFO(p_hwfn,
			"MFW refused a load request due to HSI > 1. Resending with HSI = 1\n");

		in_params.hsi_ver = QED_LOAD_REQ_HSI_VER_1;
		स_रखो(&out_params, 0, माप(out_params));
		rc = __qed_mcp_load_req(p_hwfn, p_ptt, &in_params, &out_params);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अगर (out_params.load_code ==
		   FW_MSG_CODE_DRV_LOAD_REFUSED_REQUIRES_FORCE) अणु
		अगर (qed_mcp_can_क्रमce_load(in_params.drv_role,
					   out_params.exist_drv_role,
					   p_params->override_क्रमce_load)) अणु
			DP_INFO(p_hwfn,
				"A force load is required [{role, fw_ver, drv_ver}: loading={%d, 0x%08x, x%08x_0x%08x}, existing={%d, 0x%08x, 0x%08x_0x%08x}]\n",
				in_params.drv_role, in_params.fw_ver,
				in_params.drv_ver_0, in_params.drv_ver_1,
				out_params.exist_drv_role,
				out_params.exist_fw_ver,
				out_params.exist_drv_ver_0,
				out_params.exist_drv_ver_1);

			qed_get_mfw_क्रमce_cmd(p_hwfn,
					      QED_LOAD_REQ_FORCE_ALL,
					      &mfw_क्रमce_cmd);

			in_params.क्रमce_cmd = mfw_क्रमce_cmd;
			स_रखो(&out_params, 0, माप(out_params));
			rc = __qed_mcp_load_req(p_hwfn, p_ptt, &in_params,
						&out_params);
			अगर (rc)
				वापस rc;
		पूर्ण अन्यथा अणु
			DP_NOTICE(p_hwfn,
				  "A force load is required [{role, fw_ver, drv_ver}: loading={%d, 0x%08x, x%08x_0x%08x}, existing={%d, 0x%08x, 0x%08x_0x%08x}] - Avoid\n",
				  in_params.drv_role, in_params.fw_ver,
				  in_params.drv_ver_0, in_params.drv_ver_1,
				  out_params.exist_drv_role,
				  out_params.exist_fw_ver,
				  out_params.exist_drv_ver_0,
				  out_params.exist_drv_ver_1);
			DP_NOTICE(p_hwfn,
				  "Avoid sending a force load request to prevent disruption of active PFs\n");

			qed_mcp_cancel_load_req(p_hwfn, p_ptt);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Now handle the other types of responses.
	 * The "REFUSED_HSI_1" and "REFUSED_REQUIRES_FORCE" responses are not
	 * expected here after the additional revised load requests were sent.
	 */
	चयन (out_params.load_code) अणु
	हाल FW_MSG_CODE_DRV_LOAD_ENGINE:
	हाल FW_MSG_CODE_DRV_LOAD_PORT:
	हाल FW_MSG_CODE_DRV_LOAD_FUNCTION:
		अगर (out_params.mfw_hsi_ver != QED_LOAD_REQ_HSI_VER_1 &&
		    out_params.drv_exists) अणु
			/* The role and fw/driver version match, but the PF is
			 * alपढ़ोy loaded and has not been unloaded gracefully.
			 */
			DP_NOTICE(p_hwfn,
				  "PF is already loaded\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn,
			  "Unexpected refusal to load request [resp 0x%08x]. Aborting.\n",
			  out_params.load_code);
		वापस -EBUSY;
	पूर्ण

	p_params->load_code = out_params.load_code;

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_load_करोne(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 resp = 0, param = 0;
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_LOAD_DONE, 0, &resp,
			 &param);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to send a LOAD_DONE command, rc = %d\n", rc);
		वापस rc;
	पूर्ण

	/* Check अगर there is a DID mismatch between nvm-cfg/efuse */
	अगर (param & FW_MB_PARAM_LOAD_DONE_DID_EFUSE_ERROR)
		DP_NOTICE(p_hwfn,
			  "warning: device configuration is not supported on this board type. The device may not function as expected.\n");

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_unload_req(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	u32 wol_param;

	चयन (p_hwfn->cdev->wol_config) अणु
	हाल QED_OV_WOL_DISABLED:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_DISABLED;
		अवरोध;
	हाल QED_OV_WOL_ENABLED:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_ENABLED;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn,
			  "Unknown WoL configuration %02x\n",
			  p_hwfn->cdev->wol_config);
		fallthrough;
	हाल QED_OV_WOL_DEFAULT:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_MCP;
	पूर्ण

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_UNLOAD_REQ;
	mb_params.param = wol_param;
	mb_params.flags = QED_MB_FLAG_CAN_SLEEP | QED_MB_FLAG_AVOID_BLOCK;

	वापस qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
पूर्ण

पूर्णांक qed_mcp_unload_करोne(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	काष्ठा mcp_mac wol_mac;

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_UNLOAD_DONE;

	/* Set the primary MAC अगर WoL is enabled */
	अगर (p_hwfn->cdev->wol_config == QED_OV_WOL_ENABLED) अणु
		u8 *p_mac = p_hwfn->cdev->wol_mac;

		स_रखो(&wol_mac, 0, माप(wol_mac));
		wol_mac.mac_upper = p_mac[0] << 8 | p_mac[1];
		wol_mac.mac_lower = p_mac[2] << 24 | p_mac[3] << 16 |
				    p_mac[4] << 8 | p_mac[5];

		DP_VERBOSE(p_hwfn,
			   (QED_MSG_SP | NETIF_MSG_IFDOWN),
			   "Setting WoL MAC: %pM --> [%08x,%08x]\n",
			   p_mac, wol_mac.mac_upper, wol_mac.mac_lower);

		mb_params.p_data_src = &wol_mac;
		mb_params.data_src_size = माप(wol_mac);
	पूर्ण

	वापस qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
पूर्ण

अटल व्योम qed_mcp_handle_vf_flr(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt)
अणु
	u32 addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->खुला_base,
					PUBLIC_PATH);
	u32 mfw_path_offsize = qed_rd(p_hwfn, p_ptt, addr);
	u32 path_addr = SECTION_ADDR(mfw_path_offsize,
				     QED_PATH_ID(p_hwfn));
	u32 disabled_vfs[VF_MAX_STATIC / 32];
	पूर्णांक i;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "Reading Disabled VF information from [offset %08x], path_addr %08x\n",
		   mfw_path_offsize, path_addr);

	क्रम (i = 0; i < (VF_MAX_STATIC / 32); i++) अणु
		disabled_vfs[i] = qed_rd(p_hwfn, p_ptt,
					 path_addr +
					 दुरत्व(काष्ठा खुला_path,
						  mcp_vf_disabled) +
					 माप(u32) * i);
		DP_VERBOSE(p_hwfn, (QED_MSG_SP | QED_MSG_IOV),
			   "FLR-ed VFs [%08x,...,%08x] - %08x\n",
			   i * 32, (i + 1) * 32 - 1, disabled_vfs[i]);
	पूर्ण

	अगर (qed_iov_mark_vf_flr(p_hwfn, disabled_vfs))
		qed_schedule_iov(p_hwfn, QED_IOV_WQ_FLR_FLAG);
पूर्ण

पूर्णांक qed_mcp_ack_vf_flr(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_ptt *p_ptt, u32 *vfs_to_ack)
अणु
	u32 addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->खुला_base,
					PUBLIC_FUNC);
	u32 mfw_func_offsize = qed_rd(p_hwfn, p_ptt, addr);
	u32 func_addr = SECTION_ADDR(mfw_func_offsize,
				     MCP_PF_ID(p_hwfn));
	काष्ठा qed_mcp_mb_params mb_params;
	पूर्णांक rc;
	पूर्णांक i;

	क्रम (i = 0; i < (VF_MAX_STATIC / 32); i++)
		DP_VERBOSE(p_hwfn, (QED_MSG_SP | QED_MSG_IOV),
			   "Acking VFs [%08x,...,%08x] - %08x\n",
			   i * 32, (i + 1) * 32 - 1, vfs_to_ack[i]);

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_VF_DISABLED_DONE;
	mb_params.p_data_src = vfs_to_ack;
	mb_params.data_src_size = VF_MAX_STATIC / 8;
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to pass ACK for VF flr to MFW\n");
		वापस -EBUSY;
	पूर्ण

	/* Clear the ACK bits */
	क्रम (i = 0; i < (VF_MAX_STATIC / 32); i++)
		qed_wr(p_hwfn, p_ptt,
		       func_addr +
		       दुरत्व(काष्ठा खुला_func, drv_ack_vf_disabled) +
		       i * माप(u32), 0);

	वापस rc;
पूर्ण

अटल व्योम qed_mcp_handle_transceiver_change(काष्ठा qed_hwfn *p_hwfn,
					      काष्ठा qed_ptt *p_ptt)
अणु
	u32 transceiver_state;

	transceiver_state = qed_rd(p_hwfn, p_ptt,
				   p_hwfn->mcp_info->port_addr +
				   दुरत्व(काष्ठा खुला_port,
					    transceiver_data));

	DP_VERBOSE(p_hwfn,
		   (NETIF_MSG_HW | QED_MSG_SP),
		   "Received transceiver state update [0x%08x] from mfw [Addr 0x%x]\n",
		   transceiver_state,
		   (u32)(p_hwfn->mcp_info->port_addr +
			  दुरत्व(काष्ठा खुला_port, transceiver_data)));

	transceiver_state = GET_FIELD(transceiver_state,
				      ETH_TRANSCEIVER_STATE);

	अगर (transceiver_state == ETH_TRANSCEIVER_STATE_PRESENT)
		DP_NOTICE(p_hwfn, "Transceiver is present.\n");
	अन्यथा
		DP_NOTICE(p_hwfn, "Transceiver is unplugged.\n");
पूर्ण

अटल व्योम qed_mcp_पढ़ो_eee_config(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    काष्ठा qed_mcp_link_state *p_link)
अणु
	u32 eee_status, val;

	p_link->eee_adv_caps = 0;
	p_link->eee_lp_adv_caps = 0;
	eee_status = qed_rd(p_hwfn,
			    p_ptt,
			    p_hwfn->mcp_info->port_addr +
			    दुरत्व(काष्ठा खुला_port, eee_status));
	p_link->eee_active = !!(eee_status & EEE_ACTIVE_BIT);
	val = (eee_status & EEE_LD_ADV_STATUS_MASK) >> EEE_LD_ADV_STATUS_OFFSET;
	अगर (val & EEE_1G_ADV)
		p_link->eee_adv_caps |= QED_EEE_1G_ADV;
	अगर (val & EEE_10G_ADV)
		p_link->eee_adv_caps |= QED_EEE_10G_ADV;
	val = (eee_status & EEE_LP_ADV_STATUS_MASK) >> EEE_LP_ADV_STATUS_OFFSET;
	अगर (val & EEE_1G_ADV)
		p_link->eee_lp_adv_caps |= QED_EEE_1G_ADV;
	अगर (val & EEE_10G_ADV)
		p_link->eee_lp_adv_caps |= QED_EEE_10G_ADV;
पूर्ण

अटल u32 qed_mcp_get_shmem_func(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  काष्ठा खुला_func *p_data, पूर्णांक pfid)
अणु
	u32 addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->खुला_base,
					PUBLIC_FUNC);
	u32 mfw_path_offsize = qed_rd(p_hwfn, p_ptt, addr);
	u32 func_addr;
	u32 i, size;

	func_addr = SECTION_ADDR(mfw_path_offsize, pfid);
	स_रखो(p_data, 0, माप(*p_data));

	size = min_t(u32, माप(*p_data), QED_SECTION_SIZE(mfw_path_offsize));
	क्रम (i = 0; i < size / माप(u32); i++)
		((u32 *)p_data)[i] = qed_rd(p_hwfn, p_ptt,
					    func_addr + (i << 2));
	वापस size;
पूर्ण

अटल व्योम qed_पढ़ो_pf_bandwidth(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा खुला_func *p_shmem_info)
अणु
	काष्ठा qed_mcp_function_info *p_info;

	p_info = &p_hwfn->mcp_info->func_info;

	p_info->bandwidth_min = QED_MFW_GET_FIELD(p_shmem_info->config,
						  FUNC_MF_CFG_MIN_BW);
	अगर (p_info->bandwidth_min < 1 || p_info->bandwidth_min > 100) अणु
		DP_INFO(p_hwfn,
			"bandwidth minimum out of bounds [%02x]. Set to 1\n",
			p_info->bandwidth_min);
		p_info->bandwidth_min = 1;
	पूर्ण

	p_info->bandwidth_max = QED_MFW_GET_FIELD(p_shmem_info->config,
						  FUNC_MF_CFG_MAX_BW);
	अगर (p_info->bandwidth_max < 1 || p_info->bandwidth_max > 100) अणु
		DP_INFO(p_hwfn,
			"bandwidth maximum out of bounds [%02x]. Set to 100\n",
			p_info->bandwidth_max);
		p_info->bandwidth_max = 100;
	पूर्ण
पूर्ण

अटल व्योम qed_mcp_handle_link_change(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt, bool b_reset)
अणु
	काष्ठा qed_mcp_link_state *p_link;
	u8 max_bw, min_bw;
	u32 status = 0;

	/* Prevent SW/attentions from करोing this at the same समय */
	spin_lock_bh(&p_hwfn->mcp_info->link_lock);

	p_link = &p_hwfn->mcp_info->link_output;
	स_रखो(p_link, 0, माप(*p_link));
	अगर (!b_reset) अणु
		status = qed_rd(p_hwfn, p_ptt,
				p_hwfn->mcp_info->port_addr +
				दुरत्व(काष्ठा खुला_port, link_status));
		DP_VERBOSE(p_hwfn, (NETIF_MSG_LINK | QED_MSG_SP),
			   "Received link update [0x%08x] from mfw [Addr 0x%x]\n",
			   status,
			   (u32)(p_hwfn->mcp_info->port_addr +
				 दुरत्व(काष्ठा खुला_port, link_status)));
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Resetting link indications\n");
		जाओ out;
	पूर्ण

	अगर (p_hwfn->b_drv_link_init) अणु
		/* Link indication with modern MFW arrives as per-PF
		 * indication.
		 */
		अगर (p_hwfn->mcp_info->capabilities &
		    FW_MB_PARAM_FEATURE_SUPPORT_VLINK) अणु
			काष्ठा खुला_func shmem_info;

			qed_mcp_get_shmem_func(p_hwfn, p_ptt, &shmem_info,
					       MCP_PF_ID(p_hwfn));
			p_link->link_up = !!(shmem_info.status &
					     FUNC_STATUS_VIRTUAL_LINK_UP);
			qed_पढ़ो_pf_bandwidth(p_hwfn, &shmem_info);
			DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
				   "Virtual link_up = %d\n", p_link->link_up);
		पूर्ण अन्यथा अणु
			p_link->link_up = !!(status & LINK_STATUS_LINK_UP);
			DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
				   "Physical link_up = %d\n", p_link->link_up);
		पूर्ण
	पूर्ण अन्यथा अणु
		p_link->link_up = false;
	पूर्ण

	p_link->full_duplex = true;
	चयन ((status & LINK_STATUS_SPEED_AND_DUPLEX_MASK)) अणु
	हाल LINK_STATUS_SPEED_AND_DUPLEX_100G:
		p_link->speed = 100000;
		अवरोध;
	हाल LINK_STATUS_SPEED_AND_DUPLEX_50G:
		p_link->speed = 50000;
		अवरोध;
	हाल LINK_STATUS_SPEED_AND_DUPLEX_40G:
		p_link->speed = 40000;
		अवरोध;
	हाल LINK_STATUS_SPEED_AND_DUPLEX_25G:
		p_link->speed = 25000;
		अवरोध;
	हाल LINK_STATUS_SPEED_AND_DUPLEX_20G:
		p_link->speed = 20000;
		अवरोध;
	हाल LINK_STATUS_SPEED_AND_DUPLEX_10G:
		p_link->speed = 10000;
		अवरोध;
	हाल LINK_STATUS_SPEED_AND_DUPLEX_1000THD:
		p_link->full_duplex = false;
		fallthrough;
	हाल LINK_STATUS_SPEED_AND_DUPLEX_1000TFD:
		p_link->speed = 1000;
		अवरोध;
	शेष:
		p_link->speed = 0;
		p_link->link_up = 0;
	पूर्ण

	अगर (p_link->link_up && p_link->speed)
		p_link->line_speed = p_link->speed;
	अन्यथा
		p_link->line_speed = 0;

	max_bw = p_hwfn->mcp_info->func_info.bandwidth_max;
	min_bw = p_hwfn->mcp_info->func_info.bandwidth_min;

	/* Max bandwidth configuration */
	__qed_configure_pf_max_bandwidth(p_hwfn, p_ptt, p_link, max_bw);

	/* Min bandwidth configuration */
	__qed_configure_pf_min_bandwidth(p_hwfn, p_ptt, p_link, min_bw);
	qed_configure_vp_wfq_on_link_change(p_hwfn->cdev, p_ptt,
					    p_link->min_pf_rate);

	p_link->an = !!(status & LINK_STATUS_AUTO_NEGOTIATE_ENABLED);
	p_link->an_complete = !!(status &
				 LINK_STATUS_AUTO_NEGOTIATE_COMPLETE);
	p_link->parallel_detection = !!(status &
					LINK_STATUS_PARALLEL_DETECTION_USED);
	p_link->pfc_enabled = !!(status & LINK_STATUS_PFC_ENABLED);

	p_link->partner_adv_speed |=
		(status & LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE) ?
		QED_LINK_PARTNER_SPEED_1G_FD : 0;
	p_link->partner_adv_speed |=
		(status & LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE) ?
		QED_LINK_PARTNER_SPEED_1G_HD : 0;
	p_link->partner_adv_speed |=
		(status & LINK_STATUS_LINK_PARTNER_10G_CAPABLE) ?
		QED_LINK_PARTNER_SPEED_10G : 0;
	p_link->partner_adv_speed |=
		(status & LINK_STATUS_LINK_PARTNER_20G_CAPABLE) ?
		QED_LINK_PARTNER_SPEED_20G : 0;
	p_link->partner_adv_speed |=
		(status & LINK_STATUS_LINK_PARTNER_25G_CAPABLE) ?
		QED_LINK_PARTNER_SPEED_25G : 0;
	p_link->partner_adv_speed |=
		(status & LINK_STATUS_LINK_PARTNER_40G_CAPABLE) ?
		QED_LINK_PARTNER_SPEED_40G : 0;
	p_link->partner_adv_speed |=
		(status & LINK_STATUS_LINK_PARTNER_50G_CAPABLE) ?
		QED_LINK_PARTNER_SPEED_50G : 0;
	p_link->partner_adv_speed |=
		(status & LINK_STATUS_LINK_PARTNER_100G_CAPABLE) ?
		QED_LINK_PARTNER_SPEED_100G : 0;

	p_link->partner_tx_flow_ctrl_en =
		!!(status & LINK_STATUS_TX_FLOW_CONTROL_ENABLED);
	p_link->partner_rx_flow_ctrl_en =
		!!(status & LINK_STATUS_RX_FLOW_CONTROL_ENABLED);

	चयन (status & LINK_STATUS_LINK_PARTNER_FLOW_CONTROL_MASK) अणु
	हाल LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE:
		p_link->partner_adv_छोड़ो = QED_LINK_PARTNER_SYMMETRIC_PAUSE;
		अवरोध;
	हाल LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE:
		p_link->partner_adv_छोड़ो = QED_LINK_PARTNER_ASYMMETRIC_PAUSE;
		अवरोध;
	हाल LINK_STATUS_LINK_PARTNER_BOTH_PAUSE:
		p_link->partner_adv_छोड़ो = QED_LINK_PARTNER_BOTH_PAUSE;
		अवरोध;
	शेष:
		p_link->partner_adv_छोड़ो = 0;
	पूर्ण

	p_link->sfp_tx_fault = !!(status & LINK_STATUS_SFP_TX_FAULT);

	अगर (p_hwfn->mcp_info->capabilities & FW_MB_PARAM_FEATURE_SUPPORT_EEE)
		qed_mcp_पढ़ो_eee_config(p_hwfn, p_ptt, p_link);

	अगर (p_hwfn->mcp_info->capabilities &
	    FW_MB_PARAM_FEATURE_SUPPORT_FEC_CONTROL) अणु
		चयन (status & LINK_STATUS_FEC_MODE_MASK) अणु
		हाल LINK_STATUS_FEC_MODE_NONE:
			p_link->fec_active = QED_FEC_MODE_NONE;
			अवरोध;
		हाल LINK_STATUS_FEC_MODE_FIRECODE_CL74:
			p_link->fec_active = QED_FEC_MODE_FIRECODE;
			अवरोध;
		हाल LINK_STATUS_FEC_MODE_RS_CL91:
			p_link->fec_active = QED_FEC_MODE_RS;
			अवरोध;
		शेष:
			p_link->fec_active = QED_FEC_MODE_AUTO;
		पूर्ण
	पूर्ण अन्यथा अणु
		p_link->fec_active = QED_FEC_MODE_UNSUPPORTED;
	पूर्ण

	qed_link_update(p_hwfn, p_ptt);
out:
	spin_unlock_bh(&p_hwfn->mcp_info->link_lock);
पूर्ण

पूर्णांक qed_mcp_set_link(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt, bool b_up)
अणु
	काष्ठा qed_mcp_link_params *params = &p_hwfn->mcp_info->link_input;
	काष्ठा qed_mcp_mb_params mb_params;
	काष्ठा eth_phy_cfg phy_cfg;
	u32 cmd, fec_bit = 0;
	u32 val, ext_speed;
	पूर्णांक rc = 0;

	/* Set the shmem configuration according to params */
	स_रखो(&phy_cfg, 0, माप(phy_cfg));
	cmd = b_up ? DRV_MSG_CODE_INIT_PHY : DRV_MSG_CODE_LINK_RESET;
	अगर (!params->speed.स्वतःneg)
		phy_cfg.speed = params->speed.क्रमced_speed;
	phy_cfg.छोड़ो |= (params->छोड़ो.स्वतःneg) ? ETH_PAUSE_AUTONEG : 0;
	phy_cfg.छोड़ो |= (params->छोड़ो.क्रमced_rx) ? ETH_PAUSE_RX : 0;
	phy_cfg.छोड़ो |= (params->छोड़ो.क्रमced_tx) ? ETH_PAUSE_TX : 0;
	phy_cfg.adv_speed = params->speed.advertised_speeds;
	phy_cfg.loopback_mode = params->loopback_mode;

	/* There are MFWs that share this capability regardless of whether
	 * this is feasible or not. And given that at the very least adv_caps
	 * would be set पूर्णांकernally by qed, we want to make sure LFA would
	 * still work.
	 */
	अगर ((p_hwfn->mcp_info->capabilities &
	     FW_MB_PARAM_FEATURE_SUPPORT_EEE) && params->eee.enable) अणु
		phy_cfg.eee_cfg |= EEE_CFG_EEE_ENABLED;
		अगर (params->eee.tx_lpi_enable)
			phy_cfg.eee_cfg |= EEE_CFG_TX_LPI;
		अगर (params->eee.adv_caps & QED_EEE_1G_ADV)
			phy_cfg.eee_cfg |= EEE_CFG_ADV_SPEED_1G;
		अगर (params->eee.adv_caps & QED_EEE_10G_ADV)
			phy_cfg.eee_cfg |= EEE_CFG_ADV_SPEED_10G;
		phy_cfg.eee_cfg |= (params->eee.tx_lpi_समयr <<
				    EEE_TX_TIMER_USEC_OFFSET) &
				   EEE_TX_TIMER_USEC_MASK;
	पूर्ण

	अगर (p_hwfn->mcp_info->capabilities &
	    FW_MB_PARAM_FEATURE_SUPPORT_FEC_CONTROL) अणु
		अगर (params->fec & QED_FEC_MODE_NONE)
			fec_bit |= FEC_FORCE_MODE_NONE;
		अन्यथा अगर (params->fec & QED_FEC_MODE_FIRECODE)
			fec_bit |= FEC_FORCE_MODE_FIRECODE;
		अन्यथा अगर (params->fec & QED_FEC_MODE_RS)
			fec_bit |= FEC_FORCE_MODE_RS;
		अन्यथा अगर (params->fec & QED_FEC_MODE_AUTO)
			fec_bit |= FEC_FORCE_MODE_AUTO;

		SET_MFW_FIELD(phy_cfg.fec_mode, FEC_FORCE_MODE, fec_bit);
	पूर्ण

	अगर (p_hwfn->mcp_info->capabilities &
	    FW_MB_PARAM_FEATURE_SUPPORT_EXT_SPEED_FEC_CONTROL) अणु
		ext_speed = 0;
		अगर (params->ext_speed.स्वतःneg)
			ext_speed |= ETH_EXT_SPEED_AN;

		val = params->ext_speed.क्रमced_speed;
		अगर (val & QED_EXT_SPEED_1G)
			ext_speed |= ETH_EXT_SPEED_1G;
		अगर (val & QED_EXT_SPEED_10G)
			ext_speed |= ETH_EXT_SPEED_10G;
		अगर (val & QED_EXT_SPEED_20G)
			ext_speed |= ETH_EXT_SPEED_20G;
		अगर (val & QED_EXT_SPEED_25G)
			ext_speed |= ETH_EXT_SPEED_25G;
		अगर (val & QED_EXT_SPEED_40G)
			ext_speed |= ETH_EXT_SPEED_40G;
		अगर (val & QED_EXT_SPEED_50G_R)
			ext_speed |= ETH_EXT_SPEED_50G_BASE_R;
		अगर (val & QED_EXT_SPEED_50G_R2)
			ext_speed |= ETH_EXT_SPEED_50G_BASE_R2;
		अगर (val & QED_EXT_SPEED_100G_R2)
			ext_speed |= ETH_EXT_SPEED_100G_BASE_R2;
		अगर (val & QED_EXT_SPEED_100G_R4)
			ext_speed |= ETH_EXT_SPEED_100G_BASE_R4;
		अगर (val & QED_EXT_SPEED_100G_P4)
			ext_speed |= ETH_EXT_SPEED_100G_BASE_P4;

		SET_MFW_FIELD(phy_cfg.extended_speed, ETH_EXT_SPEED,
			      ext_speed);

		ext_speed = 0;

		val = params->ext_speed.advertised_speeds;
		अगर (val & QED_EXT_SPEED_MASK_1G)
			ext_speed |= ETH_EXT_ADV_SPEED_1G;
		अगर (val & QED_EXT_SPEED_MASK_10G)
			ext_speed |= ETH_EXT_ADV_SPEED_10G;
		अगर (val & QED_EXT_SPEED_MASK_20G)
			ext_speed |= ETH_EXT_ADV_SPEED_20G;
		अगर (val & QED_EXT_SPEED_MASK_25G)
			ext_speed |= ETH_EXT_ADV_SPEED_25G;
		अगर (val & QED_EXT_SPEED_MASK_40G)
			ext_speed |= ETH_EXT_ADV_SPEED_40G;
		अगर (val & QED_EXT_SPEED_MASK_50G_R)
			ext_speed |= ETH_EXT_ADV_SPEED_50G_BASE_R;
		अगर (val & QED_EXT_SPEED_MASK_50G_R2)
			ext_speed |= ETH_EXT_ADV_SPEED_50G_BASE_R2;
		अगर (val & QED_EXT_SPEED_MASK_100G_R2)
			ext_speed |= ETH_EXT_ADV_SPEED_100G_BASE_R2;
		अगर (val & QED_EXT_SPEED_MASK_100G_R4)
			ext_speed |= ETH_EXT_ADV_SPEED_100G_BASE_R4;
		अगर (val & QED_EXT_SPEED_MASK_100G_P4)
			ext_speed |= ETH_EXT_ADV_SPEED_100G_BASE_P4;

		phy_cfg.extended_speed |= ext_speed;

		SET_MFW_FIELD(phy_cfg.fec_mode, FEC_EXTENDED_MODE,
			      params->ext_fec_mode);
	पूर्ण

	p_hwfn->b_drv_link_init = b_up;

	अगर (b_up) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Configuring Link: Speed 0x%08x, Pause 0x%08x, Adv. Speed 0x%08x, Loopback 0x%08x, FEC 0x%08x, Ext. Speed 0x%08x\n",
			   phy_cfg.speed, phy_cfg.छोड़ो, phy_cfg.adv_speed,
			   phy_cfg.loopback_mode, phy_cfg.fec_mode,
			   phy_cfg.extended_speed);
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK, "Resetting link\n");
	पूर्ण

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = cmd;
	mb_params.p_data_src = &phy_cfg;
	mb_params.data_src_size = माप(phy_cfg);
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);

	/* अगर mcp fails to respond we must पात */
	अगर (rc) अणु
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");
		वापस rc;
	पूर्ण

	/* Mimic link-change attention, करोne क्रम several reasons:
	 *  - On reset, there's no guarantee MFW would trigger
	 *    an attention.
	 *  - On initialization, older MFWs might not indicate link change
	 *    during LFA, so we'll never get an UP indication.
	 */
	qed_mcp_handle_link_change(p_hwfn, p_ptt, !b_up);

	वापस 0;
पूर्ण

u32 qed_get_process_समाप्त_counter(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt)
अणु
	u32 path_offsize_addr, path_offsize, path_addr, proc_समाप्त_cnt;

	अगर (IS_VF(p_hwfn->cdev))
		वापस -EINVAL;

	path_offsize_addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->खुला_base,
						 PUBLIC_PATH);
	path_offsize = qed_rd(p_hwfn, p_ptt, path_offsize_addr);
	path_addr = SECTION_ADDR(path_offsize, QED_PATH_ID(p_hwfn));

	proc_समाप्त_cnt = qed_rd(p_hwfn, p_ptt,
			       path_addr +
			       दुरत्व(काष्ठा खुला_path, process_समाप्त)) &
			PROCESS_KILL_COUNTER_MASK;

	वापस proc_समाप्त_cnt;
पूर्ण

अटल व्योम qed_mcp_handle_process_समाप्त(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u32 proc_समाप्त_cnt;

	/* Prevent possible attentions/पूर्णांकerrupts during the recovery handling
	 * and till its load phase, during which they will be re-enabled.
	 */
	qed_पूर्णांक_igu_disable_पूर्णांक(p_hwfn, p_ptt);

	DP_NOTICE(p_hwfn, "Received a process kill indication\n");

	/* The following operations should be करोne once, and thus in CMT mode
	 * are carried out by only the first HW function.
	 */
	अगर (p_hwfn != QED_LEADING_HWFN(cdev))
		वापस;

	अगर (cdev->recov_in_prog) अणु
		DP_NOTICE(p_hwfn,
			  "Ignoring the indication since a recovery process is already in progress\n");
		वापस;
	पूर्ण

	cdev->recov_in_prog = true;

	proc_समाप्त_cnt = qed_get_process_समाप्त_counter(p_hwfn, p_ptt);
	DP_NOTICE(p_hwfn, "Process kill counter: %d\n", proc_समाप्त_cnt);

	qed_schedule_recovery_handler(p_hwfn);
पूर्ण

अटल व्योम qed_mcp_send_protocol_stats(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt,
					क्रमागत MFW_DRV_MSG_TYPE type)
अणु
	क्रमागत qed_mcp_protocol_type stats_type;
	जोड़ qed_mcp_protocol_stats stats;
	काष्ठा qed_mcp_mb_params mb_params;
	u32 hsi_param;

	चयन (type) अणु
	हाल MFW_DRV_MSG_GET_LAN_STATS:
		stats_type = QED_MCP_LAN_STATS;
		hsi_param = DRV_MSG_CODE_STATS_TYPE_LAN;
		अवरोध;
	हाल MFW_DRV_MSG_GET_FCOE_STATS:
		stats_type = QED_MCP_FCOE_STATS;
		hsi_param = DRV_MSG_CODE_STATS_TYPE_FCOE;
		अवरोध;
	हाल MFW_DRV_MSG_GET_ISCSI_STATS:
		stats_type = QED_MCP_ISCSI_STATS;
		hsi_param = DRV_MSG_CODE_STATS_TYPE_ISCSI;
		अवरोध;
	हाल MFW_DRV_MSG_GET_RDMA_STATS:
		stats_type = QED_MCP_RDMA_STATS;
		hsi_param = DRV_MSG_CODE_STATS_TYPE_RDMA;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Invalid protocol type %d\n", type);
		वापस;
	पूर्ण

	qed_get_protocol_stats(p_hwfn->cdev, stats_type, &stats);

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_GET_STATS;
	mb_params.param = hsi_param;
	mb_params.p_data_src = &stats;
	mb_params.data_src_size = माप(stats);
	qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
पूर्ण

अटल व्योम qed_mcp_update_bw(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_function_info *p_info;
	काष्ठा खुला_func shmem_info;
	u32 resp = 0, param = 0;

	qed_mcp_get_shmem_func(p_hwfn, p_ptt, &shmem_info, MCP_PF_ID(p_hwfn));

	qed_पढ़ो_pf_bandwidth(p_hwfn, &shmem_info);

	p_info = &p_hwfn->mcp_info->func_info;

	qed_configure_pf_min_bandwidth(p_hwfn->cdev, p_info->bandwidth_min);
	qed_configure_pf_max_bandwidth(p_hwfn->cdev, p_info->bandwidth_max);

	/* Acknowledge the MFW */
	qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_BW_UPDATE_ACK, 0, &resp,
		    &param);
पूर्ण

अटल व्योम qed_mcp_update_stag(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा खुला_func shmem_info;
	u32 resp = 0, param = 0;

	qed_mcp_get_shmem_func(p_hwfn, p_ptt, &shmem_info, MCP_PF_ID(p_hwfn));

	p_hwfn->mcp_info->func_info.ovlan = (u16)shmem_info.ovlan_stag &
						 FUNC_MF_CFG_OV_STAG_MASK;
	p_hwfn->hw_info.ovlan = p_hwfn->mcp_info->func_info.ovlan;
	अगर (test_bit(QED_MF_OVLAN_CLSS, &p_hwfn->cdev->mf_bits)) अणु
		अगर (p_hwfn->hw_info.ovlan != QED_MCP_VLAN_UNSET) अणु
			qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_FUNC_TAG_VALUE,
			       p_hwfn->hw_info.ovlan);
			qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_FUNC_TAG_EN, 1);

			/* Configure DB to add बाह्यal vlan to EDPM packets */
			qed_wr(p_hwfn, p_ptt, DORQ_REG_TAG1_OVRD_MODE, 1);
			qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_EXT_VID_BB_K2,
			       p_hwfn->hw_info.ovlan);
		पूर्ण अन्यथा अणु
			qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_FUNC_TAG_EN, 0);
			qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_FUNC_TAG_VALUE, 0);
			qed_wr(p_hwfn, p_ptt, DORQ_REG_TAG1_OVRD_MODE, 0);
			qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_EXT_VID_BB_K2, 0);
		पूर्ण

		qed_sp_pf_update_stag(p_hwfn);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_SP, "ovlan = %d hw_mode = 0x%x\n",
		   p_hwfn->mcp_info->func_info.ovlan, p_hwfn->hw_info.hw_mode);

	/* Acknowledge the MFW */
	qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_S_TAG_UPDATE_ACK, 0,
		    &resp, &param);
पूर्ण

अटल व्योम qed_mcp_handle_fan_failure(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt)
अणु
	/* A single notअगरication should be sent to upper driver in CMT mode */
	अगर (p_hwfn != QED_LEADING_HWFN(p_hwfn->cdev))
		वापस;

	qed_hw_err_notअगरy(p_hwfn, p_ptt, QED_HW_ERR_FAN_FAIL,
			  "Fan failure was detected on the network interface card and it's going to be shut down.\n");
पूर्ण

काष्ठा qed_mdump_cmd_params अणु
	u32 cmd;
	व्योम *p_data_src;
	u8 data_src_size;
	व्योम *p_data_dst;
	u8 data_dst_size;
	u32 mcp_resp;
पूर्ण;

अटल पूर्णांक
qed_mcp_mdump_cmd(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_ptt *p_ptt,
		  काष्ठा qed_mdump_cmd_params *p_mdump_cmd_params)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	पूर्णांक rc;

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_MDUMP_CMD;
	mb_params.param = p_mdump_cmd_params->cmd;
	mb_params.p_data_src = p_mdump_cmd_params->p_data_src;
	mb_params.data_src_size = p_mdump_cmd_params->data_src_size;
	mb_params.p_data_dst = p_mdump_cmd_params->p_data_dst;
	mb_params.data_dst_size = p_mdump_cmd_params->data_dst_size;
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		वापस rc;

	p_mdump_cmd_params->mcp_resp = mb_params.mcp_resp;

	अगर (p_mdump_cmd_params->mcp_resp == FW_MSG_CODE_MDUMP_INVALID_CMD) अणु
		DP_INFO(p_hwfn,
			"The mdump sub command is unsupported by the MFW [mdump_cmd 0x%x]\n",
			p_mdump_cmd_params->cmd);
		rc = -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (p_mdump_cmd_params->mcp_resp == FW_MSG_CODE_UNSUPPORTED) अणु
		DP_INFO(p_hwfn,
			"The mdump command is not supported by the MFW\n");
		rc = -EOPNOTSUPP;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qed_mcp_mdump_ack(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mdump_cmd_params mdump_cmd_params;

	स_रखो(&mdump_cmd_params, 0, माप(mdump_cmd_params));
	mdump_cmd_params.cmd = DRV_MSG_CODE_MDUMP_ACK;

	वापस qed_mcp_mdump_cmd(p_hwfn, p_ptt, &mdump_cmd_params);
पूर्ण

पूर्णांक
qed_mcp_mdump_get_retain(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 काष्ठा mdump_retain_data_stc *p_mdump_retain)
अणु
	काष्ठा qed_mdump_cmd_params mdump_cmd_params;
	पूर्णांक rc;

	स_रखो(&mdump_cmd_params, 0, माप(mdump_cmd_params));
	mdump_cmd_params.cmd = DRV_MSG_CODE_MDUMP_GET_RETAIN;
	mdump_cmd_params.p_data_dst = p_mdump_retain;
	mdump_cmd_params.data_dst_size = माप(*p_mdump_retain);

	rc = qed_mcp_mdump_cmd(p_hwfn, p_ptt, &mdump_cmd_params);
	अगर (rc)
		वापस rc;

	अगर (mdump_cmd_params.mcp_resp != FW_MSG_CODE_OK) अणु
		DP_INFO(p_hwfn,
			"Failed to get the mdump retained data [mcp_resp 0x%x]\n",
			mdump_cmd_params.mcp_resp);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_mcp_handle_critical_error(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा mdump_retain_data_stc mdump_retain;
	पूर्णांक rc;

	/* In CMT mode - no need क्रम more than a single acknowledgment to the
	 * MFW, and no more than a single notअगरication to the upper driver.
	 */
	अगर (p_hwfn != QED_LEADING_HWFN(p_hwfn->cdev))
		वापस;

	rc = qed_mcp_mdump_get_retain(p_hwfn, p_ptt, &mdump_retain);
	अगर (rc == 0 && mdump_retain.valid)
		DP_NOTICE(p_hwfn,
			  "The MFW notified that a critical error occurred in the device [epoch 0x%08x, pf 0x%x, status 0x%08x]\n",
			  mdump_retain.epoch,
			  mdump_retain.pf, mdump_retain.status);
	अन्यथा
		DP_NOTICE(p_hwfn,
			  "The MFW notified that a critical error occurred in the device\n");

	DP_NOTICE(p_hwfn,
		  "Acknowledging the notification to not allow the MFW crash dump [driver debug data collection is preferable]\n");
	qed_mcp_mdump_ack(p_hwfn, p_ptt);

	qed_hw_err_notअगरy(p_hwfn, p_ptt, QED_HW_ERR_HW_ATTN, शून्य);
पूर्ण

व्योम qed_mcp_पढ़ो_ufp_config(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा खुला_func shmem_info;
	u32 port_cfg, val;

	अगर (!test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
		वापस;

	स_रखो(&p_hwfn->ufp_info, 0, माप(p_hwfn->ufp_info));
	port_cfg = qed_rd(p_hwfn, p_ptt, p_hwfn->mcp_info->port_addr +
			  दुरत्व(काष्ठा खुला_port, oem_cfg_port));
	val = (port_cfg & OEM_CFG_CHANNEL_TYPE_MASK) >>
		OEM_CFG_CHANNEL_TYPE_OFFSET;
	अगर (val != OEM_CFG_CHANNEL_TYPE_STAGGED)
		DP_NOTICE(p_hwfn,
			  "Incorrect UFP Channel type  %d port_id 0x%02x\n",
			  val, MFW_PORT(p_hwfn));

	val = (port_cfg & OEM_CFG_SCHED_TYPE_MASK) >> OEM_CFG_SCHED_TYPE_OFFSET;
	अगर (val == OEM_CFG_SCHED_TYPE_ETS) अणु
		p_hwfn->ufp_info.mode = QED_UFP_MODE_ETS;
	पूर्ण अन्यथा अगर (val == OEM_CFG_SCHED_TYPE_VNIC_BW) अणु
		p_hwfn->ufp_info.mode = QED_UFP_MODE_VNIC_BW;
	पूर्ण अन्यथा अणु
		p_hwfn->ufp_info.mode = QED_UFP_MODE_UNKNOWN;
		DP_NOTICE(p_hwfn,
			  "Unknown UFP scheduling mode %d port_id 0x%02x\n",
			  val, MFW_PORT(p_hwfn));
	पूर्ण

	qed_mcp_get_shmem_func(p_hwfn, p_ptt, &shmem_info, MCP_PF_ID(p_hwfn));
	val = (shmem_info.oem_cfg_func & OEM_CFG_FUNC_TC_MASK) >>
		OEM_CFG_FUNC_TC_OFFSET;
	p_hwfn->ufp_info.tc = (u8)val;
	val = (shmem_info.oem_cfg_func & OEM_CFG_FUNC_HOST_PRI_CTRL_MASK) >>
		OEM_CFG_FUNC_HOST_PRI_CTRL_OFFSET;
	अगर (val == OEM_CFG_FUNC_HOST_PRI_CTRL_VNIC) अणु
		p_hwfn->ufp_info.pri_type = QED_UFP_PRI_VNIC;
	पूर्ण अन्यथा अगर (val == OEM_CFG_FUNC_HOST_PRI_CTRL_OS) अणु
		p_hwfn->ufp_info.pri_type = QED_UFP_PRI_OS;
	पूर्ण अन्यथा अणु
		p_hwfn->ufp_info.pri_type = QED_UFP_PRI_UNKNOWN;
		DP_NOTICE(p_hwfn,
			  "Unknown Host priority control %d port_id 0x%02x\n",
			  val, MFW_PORT(p_hwfn));
	पूर्ण

	DP_NOTICE(p_hwfn,
		  "UFP shmem config: mode = %d tc = %d pri_type = %d port_id 0x%02x\n",
		  p_hwfn->ufp_info.mode, p_hwfn->ufp_info.tc,
		  p_hwfn->ufp_info.pri_type, MFW_PORT(p_hwfn));
पूर्ण

अटल पूर्णांक
qed_mcp_handle_ufp_event(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	qed_mcp_पढ़ो_ufp_config(p_hwfn, p_ptt);

	अगर (p_hwfn->ufp_info.mode == QED_UFP_MODE_VNIC_BW) अणु
		p_hwfn->qm_info.ooo_tc = p_hwfn->ufp_info.tc;
		qed_hw_info_set_offload_tc(&p_hwfn->hw_info,
					   p_hwfn->ufp_info.tc);

		qed_qm_reconf(p_hwfn, p_ptt);
	पूर्ण अन्यथा अगर (p_hwfn->ufp_info.mode == QED_UFP_MODE_ETS) अणु
		/* Merge UFP TC with the dcbx TC data */
		qed_dcbx_mib_update_event(p_hwfn, p_ptt,
					  QED_DCBX_OPERATIONAL_MIB);
	पूर्ण अन्यथा अणु
		DP_ERR(p_hwfn, "Invalid sched type, discard the UFP config\n");
		वापस -EINVAL;
	पूर्ण

	/* update storm FW with negotiation results */
	qed_sp_pf_update_ufp(p_hwfn);

	/* update stag pcp value */
	qed_sp_pf_update_stag(p_hwfn);

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_handle_events(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_info *info = p_hwfn->mcp_info;
	पूर्णांक rc = 0;
	bool found = false;
	u16 i;

	DP_VERBOSE(p_hwfn, QED_MSG_SP, "Received message from MFW\n");

	/* Read Messages from MFW */
	qed_mcp_पढ़ो_mb(p_hwfn, p_ptt);

	/* Compare current messages to old ones */
	क्रम (i = 0; i < info->mfw_mb_length; i++) अणु
		अगर (info->mfw_mb_cur[i] == info->mfw_mb_shaकरोw[i])
			जारी;

		found = true;

		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Msg [%d] - old CMD 0x%02x, new CMD 0x%02x\n",
			   i, info->mfw_mb_shaकरोw[i], info->mfw_mb_cur[i]);

		चयन (i) अणु
		हाल MFW_DRV_MSG_LINK_CHANGE:
			qed_mcp_handle_link_change(p_hwfn, p_ptt, false);
			अवरोध;
		हाल MFW_DRV_MSG_VF_DISABLED:
			qed_mcp_handle_vf_flr(p_hwfn, p_ptt);
			अवरोध;
		हाल MFW_DRV_MSG_LLDP_DATA_UPDATED:
			qed_dcbx_mib_update_event(p_hwfn, p_ptt,
						  QED_DCBX_REMOTE_LLDP_MIB);
			अवरोध;
		हाल MFW_DRV_MSG_DCBX_REMOTE_MIB_UPDATED:
			qed_dcbx_mib_update_event(p_hwfn, p_ptt,
						  QED_DCBX_REMOTE_MIB);
			अवरोध;
		हाल MFW_DRV_MSG_DCBX_OPERATIONAL_MIB_UPDATED:
			qed_dcbx_mib_update_event(p_hwfn, p_ptt,
						  QED_DCBX_OPERATIONAL_MIB);
			अवरोध;
		हाल MFW_DRV_MSG_OEM_CFG_UPDATE:
			qed_mcp_handle_ufp_event(p_hwfn, p_ptt);
			अवरोध;
		हाल MFW_DRV_MSG_TRANSCEIVER_STATE_CHANGE:
			qed_mcp_handle_transceiver_change(p_hwfn, p_ptt);
			अवरोध;
		हाल MFW_DRV_MSG_ERROR_RECOVERY:
			qed_mcp_handle_process_समाप्त(p_hwfn, p_ptt);
			अवरोध;
		हाल MFW_DRV_MSG_GET_LAN_STATS:
		हाल MFW_DRV_MSG_GET_FCOE_STATS:
		हाल MFW_DRV_MSG_GET_ISCSI_STATS:
		हाल MFW_DRV_MSG_GET_RDMA_STATS:
			qed_mcp_send_protocol_stats(p_hwfn, p_ptt, i);
			अवरोध;
		हाल MFW_DRV_MSG_BW_UPDATE:
			qed_mcp_update_bw(p_hwfn, p_ptt);
			अवरोध;
		हाल MFW_DRV_MSG_S_TAG_UPDATE:
			qed_mcp_update_stag(p_hwfn, p_ptt);
			अवरोध;
		हाल MFW_DRV_MSG_FAILURE_DETECTED:
			qed_mcp_handle_fan_failure(p_hwfn, p_ptt);
			अवरोध;
		हाल MFW_DRV_MSG_CRITICAL_ERROR_OCCURRED:
			qed_mcp_handle_critical_error(p_hwfn, p_ptt);
			अवरोध;
		हाल MFW_DRV_MSG_GET_TLV_REQ:
			qed_mfw_tlv_req(p_hwfn);
			अवरोध;
		शेष:
			DP_INFO(p_hwfn, "Unimplemented MFW message %d\n", i);
			rc = -EINVAL;
		पूर्ण
	पूर्ण

	/* ACK everything */
	क्रम (i = 0; i < MFW_DRV_MSG_MAX_DWORDS(info->mfw_mb_length); i++) अणु
		__be32 val = cpu_to_be32(((u32 *)info->mfw_mb_cur)[i]);

		/* MFW expect answer in BE, so we क्रमce ग_लिखो in that क्रमmat */
		qed_wr(p_hwfn, p_ptt,
		       info->mfw_mb_addr + माप(u32) +
		       MFW_DRV_MSG_MAX_DWORDS(info->mfw_mb_length) *
		       माप(u32) + i * माप(u32),
		       (__क्रमce u32)val);
	पूर्ण

	अगर (!found) अणु
		DP_NOTICE(p_hwfn,
			  "Received an MFW message indication but no new message!\n");
		rc = -EINVAL;
	पूर्ण

	/* Copy the new mfw messages पूर्णांकo the shaकरोw */
	स_नकल(info->mfw_mb_shaकरोw, info->mfw_mb_cur, info->mfw_mb_length);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_get_mfw_ver(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt,
			u32 *p_mfw_ver, u32 *p_running_bundle_id)
अणु
	u32 global_offsize;

	अगर (IS_VF(p_hwfn->cdev)) अणु
		अगर (p_hwfn->vf_iov_info) अणु
			काष्ठा pfvf_acquire_resp_tlv *p_resp;

			p_resp = &p_hwfn->vf_iov_info->acquire_resp;
			*p_mfw_ver = p_resp->pfdev_info.mfw_ver;
			वापस 0;
		पूर्ण अन्यथा अणु
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF requested MFW version prior to ACQUIRE\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	global_offsize = qed_rd(p_hwfn, p_ptt,
				SECTION_OFFSIZE_ADDR(p_hwfn->
						     mcp_info->खुला_base,
						     PUBLIC_GLOBAL));
	*p_mfw_ver =
	    qed_rd(p_hwfn, p_ptt,
		   SECTION_ADDR(global_offsize,
				0) + दुरत्व(काष्ठा खुला_global, mfw_ver));

	अगर (p_running_bundle_id != शून्य) अणु
		*p_running_bundle_id = qed_rd(p_hwfn, p_ptt,
					      SECTION_ADDR(global_offsize, 0) +
					      दुरत्व(काष्ठा खुला_global,
						       running_bundle_id));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_get_mbi_ver(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt, u32 *p_mbi_ver)
अणु
	u32 nvm_cfg_addr, nvm_cfg1_offset, mbi_ver_addr;

	अगर (IS_VF(p_hwfn->cdev))
		वापस -EINVAL;

	/* Read the address of the nvm_cfg */
	nvm_cfg_addr = qed_rd(p_hwfn, p_ptt, MISC_REG_GEN_PURP_CR0);
	अगर (!nvm_cfg_addr) अणु
		DP_NOTICE(p_hwfn, "Shared memory not initialized\n");
		वापस -EINVAL;
	पूर्ण

	/* Read the offset of nvm_cfg1 */
	nvm_cfg1_offset = qed_rd(p_hwfn, p_ptt, nvm_cfg_addr + 4);

	mbi_ver_addr = MCP_REG_SCRATCH + nvm_cfg1_offset +
		       दुरत्व(काष्ठा nvm_cfg1, glob) +
		       दुरत्व(काष्ठा nvm_cfg1_glob, mbi_version);
	*p_mbi_ver = qed_rd(p_hwfn, p_ptt,
			    mbi_ver_addr) &
		     (NVM_CFG1_GLOB_MBI_VERSION_0_MASK |
		      NVM_CFG1_GLOB_MBI_VERSION_1_MASK |
		      NVM_CFG1_GLOB_MBI_VERSION_2_MASK);

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_get_media_type(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt, u32 *p_media_type)
अणु
	*p_media_type = MEDIA_UNSPECIFIED;

	अगर (IS_VF(p_hwfn->cdev))
		वापस -EINVAL;

	अगर (!qed_mcp_is_init(p_hwfn)) अणु
		DP_NOTICE(p_hwfn, "MFW is not initialized!\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!p_ptt) अणु
		*p_media_type = MEDIA_UNSPECIFIED;
		वापस -EINVAL;
	पूर्ण

	*p_media_type = qed_rd(p_hwfn, p_ptt,
			       p_hwfn->mcp_info->port_addr +
			       दुरत्व(काष्ठा खुला_port,
					media_type));

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_get_transceiver_data(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 u32 *p_transceiver_state,
				 u32 *p_transceiver_type)
अणु
	u32 transceiver_info;

	*p_transceiver_type = ETH_TRANSCEIVER_TYPE_NONE;
	*p_transceiver_state = ETH_TRANSCEIVER_STATE_UPDATING;

	अगर (IS_VF(p_hwfn->cdev))
		वापस -EINVAL;

	अगर (!qed_mcp_is_init(p_hwfn)) अणु
		DP_NOTICE(p_hwfn, "MFW is not initialized!\n");
		वापस -EBUSY;
	पूर्ण

	transceiver_info = qed_rd(p_hwfn, p_ptt,
				  p_hwfn->mcp_info->port_addr +
				  दुरत्व(काष्ठा खुला_port,
					   transceiver_data));

	*p_transceiver_state = (transceiver_info &
				ETH_TRANSCEIVER_STATE_MASK) >>
				ETH_TRANSCEIVER_STATE_OFFSET;

	अगर (*p_transceiver_state == ETH_TRANSCEIVER_STATE_PRESENT)
		*p_transceiver_type = (transceiver_info &
				       ETH_TRANSCEIVER_TYPE_MASK) >>
				       ETH_TRANSCEIVER_TYPE_OFFSET;
	अन्यथा
		*p_transceiver_type = ETH_TRANSCEIVER_TYPE_UNKNOWN;

	वापस 0;
पूर्ण
अटल bool qed_is_transceiver_पढ़ोy(u32 transceiver_state,
				     u32 transceiver_type)
अणु
	अगर ((transceiver_state & ETH_TRANSCEIVER_STATE_PRESENT) &&
	    ((transceiver_state & ETH_TRANSCEIVER_STATE_UPDATING) == 0x0) &&
	    (transceiver_type != ETH_TRANSCEIVER_TYPE_NONE))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक qed_mcp_trans_speed_mask(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt, u32 *p_speed_mask)
अणु
	u32 transceiver_type, transceiver_state;
	पूर्णांक ret;

	ret = qed_mcp_get_transceiver_data(p_hwfn, p_ptt, &transceiver_state,
					   &transceiver_type);
	अगर (ret)
		वापस ret;

	अगर (qed_is_transceiver_पढ़ोy(transceiver_state, transceiver_type) ==
				     false)
		वापस -EINVAL;

	चयन (transceiver_type) अणु
	हाल ETH_TRANSCEIVER_TYPE_1G_LX:
	हाल ETH_TRANSCEIVER_TYPE_1G_SX:
	हाल ETH_TRANSCEIVER_TYPE_1G_PCC:
	हाल ETH_TRANSCEIVER_TYPE_1G_ACC:
	हाल ETH_TRANSCEIVER_TYPE_1000BASET:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_10G_SR:
	हाल ETH_TRANSCEIVER_TYPE_10G_LR:
	हाल ETH_TRANSCEIVER_TYPE_10G_LRM:
	हाल ETH_TRANSCEIVER_TYPE_10G_ER:
	हाल ETH_TRANSCEIVER_TYPE_10G_PCC:
	हाल ETH_TRANSCEIVER_TYPE_10G_ACC:
	हाल ETH_TRANSCEIVER_TYPE_4x10G:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_40G_LR4:
	हाल ETH_TRANSCEIVER_TYPE_40G_SR4:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_SR:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_LR:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_100G_AOC:
	हाल ETH_TRANSCEIVER_TYPE_100G_SR4:
	हाल ETH_TRANSCEIVER_TYPE_100G_LR4:
	हाल ETH_TRANSCEIVER_TYPE_100G_ER4:
	हाल ETH_TRANSCEIVER_TYPE_100G_ACC:
		*p_speed_mask =
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_25G_SR:
	हाल ETH_TRANSCEIVER_TYPE_25G_LR:
	हाल ETH_TRANSCEIVER_TYPE_25G_AOC:
	हाल ETH_TRANSCEIVER_TYPE_25G_ACC_S:
	हाल ETH_TRANSCEIVER_TYPE_25G_ACC_M:
	हाल ETH_TRANSCEIVER_TYPE_25G_ACC_L:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_25G_CA_N:
	हाल ETH_TRANSCEIVER_TYPE_25G_CA_S:
	हाल ETH_TRANSCEIVER_TYPE_25G_CA_L:
	हाल ETH_TRANSCEIVER_TYPE_4x25G_CR:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_25G_SR:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_25G_LR:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G |
				NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_40G_CR4:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_CR:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_100G_CR4:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_CR:
		*p_speed_mask =
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_SR:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_LR:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_AOC:
		*p_speed_mask =
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G |
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_XLPPI:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G;
		अवरोध;
	हाल ETH_TRANSCEIVER_TYPE_10G_BASET:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_1G_10G_SR:
	हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_1G_10G_LR:
		*p_speed_mask = NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G |
				NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G;
		अवरोध;
	शेष:
		DP_INFO(p_hwfn, "Unknown transceiver type 0x%x\n",
			transceiver_type);
		*p_speed_mask = 0xff;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_get_board_config(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt, u32 *p_board_config)
अणु
	u32 nvm_cfg_addr, nvm_cfg1_offset, port_cfg_addr;

	अगर (IS_VF(p_hwfn->cdev))
		वापस -EINVAL;

	अगर (!qed_mcp_is_init(p_hwfn)) अणु
		DP_NOTICE(p_hwfn, "MFW is not initialized!\n");
		वापस -EBUSY;
	पूर्ण
	अगर (!p_ptt) अणु
		*p_board_config = NVM_CFG1_PORT_PORT_TYPE_UNDEFINED;
		वापस -EINVAL;
	पूर्ण

	nvm_cfg_addr = qed_rd(p_hwfn, p_ptt, MISC_REG_GEN_PURP_CR0);
	nvm_cfg1_offset = qed_rd(p_hwfn, p_ptt, nvm_cfg_addr + 4);
	port_cfg_addr = MCP_REG_SCRATCH + nvm_cfg1_offset +
			दुरत्व(काष्ठा nvm_cfg1, port[MFW_PORT(p_hwfn)]);
	*p_board_config = qed_rd(p_hwfn, p_ptt,
				 port_cfg_addr +
				 दुरत्व(काष्ठा nvm_cfg1_port,
					  board_cfg));

	वापस 0;
पूर्ण

/* Old MFW has a global configuration क्रम all PFs regarding RDMA support */
अटल व्योम
qed_mcp_get_shmem_proto_legacy(काष्ठा qed_hwfn *p_hwfn,
			       क्रमागत qed_pci_personality *p_proto)
अणु
	/* There wasn't ever a legacy MFW that published iwarp.
	 * So at this poपूर्णांक, this is either plain l2 or RoCE.
	 */
	अगर (test_bit(QED_DEV_CAP_ROCE, &p_hwfn->hw_info.device_capabilities))
		*p_proto = QED_PCI_ETH_ROCE;
	अन्यथा
		*p_proto = QED_PCI_ETH;

	DP_VERBOSE(p_hwfn, NETIF_MSG_IFUP,
		   "According to Legacy capabilities, L2 personality is %08x\n",
		   (u32) *p_proto);
पूर्ण

अटल पूर्णांक
qed_mcp_get_shmem_proto_mfw(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt,
			    क्रमागत qed_pci_personality *p_proto)
अणु
	u32 resp = 0, param = 0;
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt,
			 DRV_MSG_CODE_GET_PF_RDMA_PROTOCOL, 0, &resp, &param);
	अगर (rc)
		वापस rc;
	अगर (resp != FW_MSG_CODE_OK) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_IFUP,
			   "MFW lacks support for command; Returns %08x\n",
			   resp);
		वापस -EINVAL;
	पूर्ण

	चयन (param) अणु
	हाल FW_MB_PARAM_GET_PF_RDMA_NONE:
		*p_proto = QED_PCI_ETH;
		अवरोध;
	हाल FW_MB_PARAM_GET_PF_RDMA_ROCE:
		*p_proto = QED_PCI_ETH_ROCE;
		अवरोध;
	हाल FW_MB_PARAM_GET_PF_RDMA_IWARP:
		*p_proto = QED_PCI_ETH_IWARP;
		अवरोध;
	हाल FW_MB_PARAM_GET_PF_RDMA_BOTH:
		*p_proto = QED_PCI_ETH_RDMA;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn,
			  "MFW answers GET_PF_RDMA_PROTOCOL but param is %08x\n",
			  param);
		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(p_hwfn,
		   NETIF_MSG_IFUP,
		   "According to capabilities, L2 personality is %08x [resp %08x param %08x]\n",
		   (u32) *p_proto, resp, param);
	वापस 0;
पूर्ण

अटल पूर्णांक
qed_mcp_get_shmem_proto(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा खुला_func *p_info,
			काष्ठा qed_ptt *p_ptt,
			क्रमागत qed_pci_personality *p_proto)
अणु
	पूर्णांक rc = 0;

	चयन (p_info->config & FUNC_MF_CFG_PROTOCOL_MASK) अणु
	हाल FUNC_MF_CFG_PROTOCOL_ETHERNET:
		अगर (!IS_ENABLED(CONFIG_QED_RDMA))
			*p_proto = QED_PCI_ETH;
		अन्यथा अगर (qed_mcp_get_shmem_proto_mfw(p_hwfn, p_ptt, p_proto))
			qed_mcp_get_shmem_proto_legacy(p_hwfn, p_proto);
		अवरोध;
	हाल FUNC_MF_CFG_PROTOCOL_ISCSI:
		*p_proto = QED_PCI_ISCSI;
		अवरोध;
	हाल FUNC_MF_CFG_PROTOCOL_FCOE:
		*p_proto = QED_PCI_FCOE;
		अवरोध;
	हाल FUNC_MF_CFG_PROTOCOL_ROCE:
		DP_NOTICE(p_hwfn, "RoCE personality is not a valid value!\n");
		fallthrough;
	शेष:
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_fill_shmem_func_info(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_function_info *info;
	काष्ठा खुला_func shmem_info;

	qed_mcp_get_shmem_func(p_hwfn, p_ptt, &shmem_info, MCP_PF_ID(p_hwfn));
	info = &p_hwfn->mcp_info->func_info;

	info->छोड़ो_on_host = (shmem_info.config &
			       FUNC_MF_CFG_PAUSE_ON_HOST_RING) ? 1 : 0;

	अगर (qed_mcp_get_shmem_proto(p_hwfn, &shmem_info, p_ptt,
				    &info->protocol)) अणु
		DP_ERR(p_hwfn, "Unknown personality %08x\n",
		       (u32)(shmem_info.config & FUNC_MF_CFG_PROTOCOL_MASK));
		वापस -EINVAL;
	पूर्ण

	qed_पढ़ो_pf_bandwidth(p_hwfn, &shmem_info);

	अगर (shmem_info.mac_upper || shmem_info.mac_lower) अणु
		info->mac[0] = (u8)(shmem_info.mac_upper >> 8);
		info->mac[1] = (u8)(shmem_info.mac_upper);
		info->mac[2] = (u8)(shmem_info.mac_lower >> 24);
		info->mac[3] = (u8)(shmem_info.mac_lower >> 16);
		info->mac[4] = (u8)(shmem_info.mac_lower >> 8);
		info->mac[5] = (u8)(shmem_info.mac_lower);

		/* Store primary MAC क्रम later possible WoL */
		स_नकल(&p_hwfn->cdev->wol_mac, info->mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		DP_NOTICE(p_hwfn, "MAC is 0 in shmem\n");
	पूर्ण

	info->wwn_port = (u64)shmem_info.fcoe_wwn_port_name_lower |
			 (((u64)shmem_info.fcoe_wwn_port_name_upper) << 32);
	info->wwn_node = (u64)shmem_info.fcoe_wwn_node_name_lower |
			 (((u64)shmem_info.fcoe_wwn_node_name_upper) << 32);

	info->ovlan = (u16)(shmem_info.ovlan_stag & FUNC_MF_CFG_OV_STAG_MASK);

	info->mtu = (u16)shmem_info.mtu_size;

	p_hwfn->hw_info.b_wol_support = QED_WOL_SUPPORT_NONE;
	p_hwfn->cdev->wol_config = (u8)QED_OV_WOL_DEFAULT;
	अगर (qed_mcp_is_init(p_hwfn)) अणु
		u32 resp = 0, param = 0;
		पूर्णांक rc;

		rc = qed_mcp_cmd(p_hwfn, p_ptt,
				 DRV_MSG_CODE_OS_WOL, 0, &resp, &param);
		अगर (rc)
			वापस rc;
		अगर (resp == FW_MSG_CODE_OS_WOL_SUPPORTED)
			p_hwfn->hw_info.b_wol_support = QED_WOL_SUPPORT_PME;
	पूर्ण

	DP_VERBOSE(p_hwfn, (QED_MSG_SP | NETIF_MSG_IFUP),
		   "Read configuration from shmem: pause_on_host %02x protocol %02x BW [%02x - %02x] MAC %pM wwn port %llx node %llx ovlan %04x wol %02x\n",
		info->छोड़ो_on_host, info->protocol,
		info->bandwidth_min, info->bandwidth_max,
		info->mac,
		info->wwn_port, info->wwn_node,
		info->ovlan, (u8)p_hwfn->hw_info.b_wol_support);

	वापस 0;
पूर्ण

काष्ठा qed_mcp_link_params
*qed_mcp_get_link_params(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn || !p_hwfn->mcp_info)
		वापस शून्य;
	वापस &p_hwfn->mcp_info->link_input;
पूर्ण

काष्ठा qed_mcp_link_state
*qed_mcp_get_link_state(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn || !p_hwfn->mcp_info)
		वापस शून्य;
	वापस &p_hwfn->mcp_info->link_output;
पूर्ण

काष्ठा qed_mcp_link_capabilities
*qed_mcp_get_link_capabilities(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (!p_hwfn || !p_hwfn->mcp_info)
		वापस शून्य;
	वापस &p_hwfn->mcp_info->link_capabilities;
पूर्ण

पूर्णांक qed_mcp_drain(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 resp = 0, param = 0;
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt,
			 DRV_MSG_CODE_NIG_DRAIN, 1000, &resp, &param);

	/* Wait क्रम the drain to complete beक्रमe वापसing */
	msleep(1020);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_get_flash_size(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt, u32 *p_flash_size)
अणु
	u32 flash_size;

	अगर (IS_VF(p_hwfn->cdev))
		वापस -EINVAL;

	flash_size = qed_rd(p_hwfn, p_ptt, MCP_REG_NVM_CFG4);
	flash_size = (flash_size & MCP_REG_NVM_CFG4_FLASH_SIZE) >>
		      MCP_REG_NVM_CFG4_FLASH_SIZE_SHIFT;
	flash_size = (1 << (flash_size + MCP_BYTES_PER_MBIT_SHIFT));

	*p_flash_size = flash_size;

	वापस 0;
पूर्ण

पूर्णांक qed_start_recovery_process(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;

	अगर (cdev->recov_in_prog) अणु
		DP_NOTICE(p_hwfn,
			  "Avoid triggering a recovery since such a process is already in progress\n");
		वापस -EAGAIN;
	पूर्ण

	DP_NOTICE(p_hwfn, "Triggering a recovery process\n");
	qed_wr(p_hwfn, p_ptt, MISC_REG_AEU_GENERAL_ATTN_35, 0x1);

	वापस 0;
पूर्ण

#घोषणा QED_RECOVERY_PROLOG_SLEEP_MS    100

पूर्णांक qed_recovery_prolog(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_मुख्य_ptt;
	पूर्णांक rc;

	/* Allow ongoing PCIe transactions to complete */
	msleep(QED_RECOVERY_PROLOG_SLEEP_MS);

	/* Clear the PF's पूर्णांकernal FID_enable in the PXP */
	rc = qed_pglueb_set_pfid_enable(p_hwfn, p_ptt, false);
	अगर (rc)
		DP_NOTICE(p_hwfn,
			  "qed_pglueb_set_pfid_enable() failed. rc = %d.\n",
			  rc);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_mcp_config_vf_msix_bb(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u8 vf_id, u8 num)
अणु
	u32 resp = 0, param = 0, rc_param = 0;
	पूर्णांक rc;

	/* Only Leader can configure MSIX, and need to take CMT पूर्णांकo account */
	अगर (!IS_LEAD_HWFN(p_hwfn))
		वापस 0;
	num *= p_hwfn->cdev->num_hwfns;

	param |= (vf_id << DRV_MB_PARAM_CFG_VF_MSIX_VF_ID_SHIFT) &
		 DRV_MB_PARAM_CFG_VF_MSIX_VF_ID_MASK;
	param |= (num << DRV_MB_PARAM_CFG_VF_MSIX_SB_NUM_SHIFT) &
		 DRV_MB_PARAM_CFG_VF_MSIX_SB_NUM_MASK;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_CFG_VF_MSIX, param,
			 &resp, &rc_param);

	अगर (resp != FW_MSG_CODE_DRV_CFG_VF_MSIX_DONE) अणु
		DP_NOTICE(p_hwfn, "VF[%d]: MFW failed to set MSI-X\n", vf_id);
		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Requested 0x%02x MSI-x interrupts from VF 0x%02x\n",
			   num, vf_id);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_mcp_config_vf_msix_ah(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u8 num)
अणु
	u32 resp = 0, param = num, rc_param = 0;
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_CFG_PF_VFS_MSIX,
			 param, &resp, &rc_param);

	अगर (resp != FW_MSG_CODE_DRV_CFG_PF_VFS_MSIX_DONE) अणु
		DP_NOTICE(p_hwfn, "MFW failed to set MSI-X for VFs\n");
		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Requested 0x%02x MSI-x interrupts for VFs\n", num);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_config_vf_msix(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt, u8 vf_id, u8 num)
अणु
	अगर (QED_IS_BB(p_hwfn->cdev))
		वापस qed_mcp_config_vf_msix_bb(p_hwfn, p_ptt, vf_id, num);
	अन्यथा
		वापस qed_mcp_config_vf_msix_ah(p_hwfn, p_ptt, num);
पूर्ण

पूर्णांक
qed_mcp_send_drv_version(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 काष्ठा qed_mcp_drv_version *p_ver)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	काष्ठा drv_version_stc drv_version;
	__be32 val;
	u32 i;
	पूर्णांक rc;

	स_रखो(&drv_version, 0, माप(drv_version));
	drv_version.version = p_ver->version;
	क्रम (i = 0; i < (MCP_DRV_VER_STR_SIZE - 4) / माप(u32); i++) अणु
		val = cpu_to_be32(*((u32 *)&p_ver->name[i * माप(u32)]));
		*(__be32 *)&drv_version.name[i * माप(u32)] = val;
	पूर्ण

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_SET_VERSION;
	mb_params.p_data_src = &drv_version;
	mb_params.data_src_size = माप(drv_version);
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");

	वापस rc;
पूर्ण

/* A maximal 100 msec रुकोing समय क्रम the MCP to halt */
#घोषणा QED_MCP_HALT_SLEEP_MS		10
#घोषणा QED_MCP_HALT_MAX_RETRIES	10

पूर्णांक qed_mcp_halt(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 resp = 0, param = 0, cpu_state, cnt = 0;
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_MCP_HALT, 0, &resp,
			 &param);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");
		वापस rc;
	पूर्ण

	करो अणु
		msleep(QED_MCP_HALT_SLEEP_MS);
		cpu_state = qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_STATE);
		अगर (cpu_state & MCP_REG_CPU_STATE_SOFT_HALTED)
			अवरोध;
	पूर्ण जबतक (++cnt < QED_MCP_HALT_MAX_RETRIES);

	अगर (cnt == QED_MCP_HALT_MAX_RETRIES) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to halt the MCP [CPU_MODE = 0x%08x, CPU_STATE = 0x%08x]\n",
			  qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_MODE), cpu_state);
		वापस -EBUSY;
	पूर्ण

	qed_mcp_cmd_set_blocking(p_hwfn, true);

	वापस 0;
पूर्ण

#घोषणा QED_MCP_RESUME_SLEEP_MS	10

पूर्णांक qed_mcp_resume(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 cpu_mode, cpu_state;

	qed_wr(p_hwfn, p_ptt, MCP_REG_CPU_STATE, 0xffffffff);

	cpu_mode = qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_MODE);
	cpu_mode &= ~MCP_REG_CPU_MODE_SOFT_HALT;
	qed_wr(p_hwfn, p_ptt, MCP_REG_CPU_MODE, cpu_mode);
	msleep(QED_MCP_RESUME_SLEEP_MS);
	cpu_state = qed_rd(p_hwfn, p_ptt, MCP_REG_CPU_STATE);

	अगर (cpu_state & MCP_REG_CPU_STATE_SOFT_HALTED) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to resume the MCP [CPU_MODE = 0x%08x, CPU_STATE = 0x%08x]\n",
			  cpu_mode, cpu_state);
		वापस -EBUSY;
	पूर्ण

	qed_mcp_cmd_set_blocking(p_hwfn, false);

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_ov_update_current_config(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     क्रमागत qed_ov_client client)
अणु
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	पूर्णांक rc;

	चयन (client) अणु
	हाल QED_OV_CLIENT_DRV:
		drv_mb_param = DRV_MB_PARAM_OV_CURR_CFG_OS;
		अवरोध;
	हाल QED_OV_CLIENT_USER:
		drv_mb_param = DRV_MB_PARAM_OV_CURR_CFG_OTHER;
		अवरोध;
	हाल QED_OV_CLIENT_VENDOR_SPEC:
		drv_mb_param = DRV_MB_PARAM_OV_CURR_CFG_VENDOR_SPEC;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Invalid client type %d\n", client);
		वापस -EINVAL;
	पूर्ण

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_CURR_CFG,
			 drv_mb_param, &resp, &param);
	अगर (rc)
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_ov_update_driver_state(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   क्रमागत qed_ov_driver_state drv_state)
अणु
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	पूर्णांक rc;

	चयन (drv_state) अणु
	हाल QED_OV_DRIVER_STATE_NOT_LOADED:
		drv_mb_param = DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_NOT_LOADED;
		अवरोध;
	हाल QED_OV_DRIVER_STATE_DISABLED:
		drv_mb_param = DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_DISABLED;
		अवरोध;
	हाल QED_OV_DRIVER_STATE_ACTIVE:
		drv_mb_param = DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_ACTIVE;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Invalid driver state %d\n", drv_state);
		वापस -EINVAL;
	पूर्ण

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE,
			 drv_mb_param, &resp, &param);
	अगर (rc)
		DP_ERR(p_hwfn, "Failed to send driver state\n");

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_ov_update_mtu(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u16 mtu)
अणु
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	पूर्णांक rc;

	drv_mb_param = (u32)mtu << DRV_MB_PARAM_OV_MTU_SIZE_SHIFT;
	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_MTU,
			 drv_mb_param, &resp, &param);
	अगर (rc)
		DP_ERR(p_hwfn, "Failed to send mtu value, rc = %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_ov_update_mac(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u8 *mac)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	u32 mfw_mac[2];
	पूर्णांक rc;

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_SET_VMAC;
	mb_params.param = DRV_MSG_CODE_VMAC_TYPE_MAC <<
			  DRV_MSG_CODE_VMAC_TYPE_SHIFT;
	mb_params.param |= MCP_PF_ID(p_hwfn);

	/* MCP is BE, and on LE platक्रमms PCI would swap access to SHMEM
	 * in 32-bit granularity.
	 * So the MAC has to be set in native order [and not byte order],
	 * otherwise it would be पढ़ो incorrectly by MFW after swap.
	 */
	mfw_mac[0] = mac[0] << 24 | mac[1] << 16 | mac[2] << 8 | mac[3];
	mfw_mac[1] = mac[4] << 24 | mac[5] << 16;

	mb_params.p_data_src = (u8 *)mfw_mac;
	mb_params.data_src_size = 8;
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		DP_ERR(p_hwfn, "Failed to send mac address, rc = %d\n", rc);

	/* Store primary MAC क्रम later possible WoL */
	स_नकल(p_hwfn->cdev->wol_mac, mac, ETH_ALEN);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_ov_update_wol(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, क्रमागत qed_ov_wol wol)
अणु
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	पूर्णांक rc;

	अगर (p_hwfn->hw_info.b_wol_support == QED_WOL_SUPPORT_NONE) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Can't change WoL configuration when WoL isn't supported\n");
		वापस -EINVAL;
	पूर्ण

	चयन (wol) अणु
	हाल QED_OV_WOL_DEFAULT:
		drv_mb_param = DRV_MB_PARAM_WOL_DEFAULT;
		अवरोध;
	हाल QED_OV_WOL_DISABLED:
		drv_mb_param = DRV_MB_PARAM_WOL_DISABLED;
		अवरोध;
	हाल QED_OV_WOL_ENABLED:
		drv_mb_param = DRV_MB_PARAM_WOL_ENABLED;
		अवरोध;
	शेष:
		DP_ERR(p_hwfn, "Invalid wol state %d\n", wol);
		वापस -EINVAL;
	पूर्ण

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_WOL,
			 drv_mb_param, &resp, &param);
	अगर (rc)
		DP_ERR(p_hwfn, "Failed to send wol mode, rc = %d\n", rc);

	/* Store the WoL update क्रम a future unload */
	p_hwfn->cdev->wol_config = (u8)wol;

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_ov_update_eचयन(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      क्रमागत qed_ov_eचयन eचयन)
अणु
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	पूर्णांक rc;

	चयन (eचयन) अणु
	हाल QED_OV_ESWITCH_NONE:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_NONE;
		अवरोध;
	हाल QED_OV_ESWITCH_VEB:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_VEB;
		अवरोध;
	हाल QED_OV_ESWITCH_VEPA:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_VEPA;
		अवरोध;
	शेष:
		DP_ERR(p_hwfn, "Invalid eswitch mode %d\n", eचयन);
		वापस -EINVAL;
	पूर्ण

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_ESWITCH_MODE,
			 drv_mb_param, &resp, &param);
	अगर (rc)
		DP_ERR(p_hwfn, "Failed to send eswitch mode, rc = %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_set_led(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt, क्रमागत qed_led_mode mode)
अणु
	u32 resp = 0, param = 0, drv_mb_param;
	पूर्णांक rc;

	चयन (mode) अणु
	हाल QED_LED_MODE_ON:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_ON;
		अवरोध;
	हाल QED_LED_MODE_OFF:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_OFF;
		अवरोध;
	हाल QED_LED_MODE_RESTORE:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_OPER;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Invalid LED mode %d\n", mode);
		वापस -EINVAL;
	पूर्ण

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_SET_LED_MODE,
			 drv_mb_param, &resp, &param);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_mask_parities(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u32 mask_parities)
अणु
	u32 resp = 0, param = 0;
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_MASK_PARITIES,
			 mask_parities, &resp, &param);

	अगर (rc) अणु
		DP_ERR(p_hwfn,
		       "MCP response failure for mask parities, aborting\n");
	पूर्ण अन्यथा अगर (resp != FW_MSG_CODE_OK) अणु
		DP_ERR(p_hwfn,
		       "MCP did not acknowledge mask parity request. Old MFW?\n");
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_nvm_पढ़ो(काष्ठा qed_dev *cdev, u32 addr, u8 *p_buf, u32 len)
अणु
	u32 bytes_left = len, offset = 0, bytes_to_copy, पढ़ो_len = 0;
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	u32 resp = 0, resp_param = 0;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = 0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EBUSY;

	जबतक (bytes_left > 0) अणु
		bytes_to_copy = min_t(u32, bytes_left, MCP_DRV_NVM_BUF_LEN);

		rc = qed_mcp_nvm_rd_cmd(p_hwfn, p_ptt,
					DRV_MSG_CODE_NVM_READ_NVRAM,
					addr + offset +
					(bytes_to_copy <<
					 DRV_MB_PARAM_NVM_LEN_OFFSET),
					&resp, &resp_param,
					&पढ़ो_len,
					(u32 *)(p_buf + offset));

		अगर (rc || (resp != FW_MSG_CODE_NVM_OK)) अणु
			DP_NOTICE(cdev, "MCP command rc = %d\n", rc);
			अवरोध;
		पूर्ण

		/* This can be a lengthy process, and it's possible scheduler
		 * isn't preemptable. Sleep a bit to prevent CPU hogging.
		 */
		अगर (bytes_left % 0x1000 <
		    (bytes_left - पढ़ो_len) % 0x1000)
			usleep_range(1000, 2000);

		offset += पढ़ो_len;
		bytes_left -= पढ़ो_len;
	पूर्ण

	cdev->mcp_nvm_resp = resp;
	qed_ptt_release(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_nvm_resp(काष्ठा qed_dev *cdev, u8 *p_buf)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EBUSY;

	स_नकल(p_buf, &cdev->mcp_nvm_resp, माप(cdev->mcp_nvm_resp));
	qed_ptt_release(p_hwfn, p_ptt);

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_nvm_ग_लिखो(काष्ठा qed_dev *cdev,
		      u32 cmd, u32 addr, u8 *p_buf, u32 len)
अणु
	u32 buf_idx = 0, buf_size, nvm_cmd, nvm_offset, resp = 0, param;
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = -EINVAL;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EBUSY;

	चयन (cmd) अणु
	हाल QED_PUT_खाता_BEGIN:
		nvm_cmd = DRV_MSG_CODE_NVM_PUT_खाता_BEGIN;
		अवरोध;
	हाल QED_PUT_खाता_DATA:
		nvm_cmd = DRV_MSG_CODE_NVM_PUT_खाता_DATA;
		अवरोध;
	हाल QED_NVM_WRITE_NVRAM:
		nvm_cmd = DRV_MSG_CODE_NVM_WRITE_NVRAM;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Invalid nvm write command 0x%x\n", cmd);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	buf_size = min_t(u32, (len - buf_idx), MCP_DRV_NVM_BUF_LEN);
	जबतक (buf_idx < len) अणु
		अगर (cmd == QED_PUT_खाता_BEGIN)
			nvm_offset = addr;
		अन्यथा
			nvm_offset = ((buf_size <<
				       DRV_MB_PARAM_NVM_LEN_OFFSET) | addr) +
				       buf_idx;
		rc = qed_mcp_nvm_wr_cmd(p_hwfn, p_ptt, nvm_cmd, nvm_offset,
					&resp, &param, buf_size,
					(u32 *)&p_buf[buf_idx]);
		अगर (rc) अणु
			DP_NOTICE(cdev, "nvm write failed, rc = %d\n", rc);
			resp = FW_MSG_CODE_ERROR;
			अवरोध;
		पूर्ण

		अगर (resp != FW_MSG_CODE_OK &&
		    resp != FW_MSG_CODE_NVM_OK &&
		    resp != FW_MSG_CODE_NVM_PUT_खाता_FINISH_OK) अणु
			DP_NOTICE(cdev,
				  "nvm write failed, resp = 0x%08x\n", resp);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		/* This can be a lengthy process, and it's possible scheduler
		 * isn't pre-emptable. Sleep a bit to prevent CPU hogging.
		 */
		अगर (buf_idx % 0x1000 > (buf_idx + buf_size) % 0x1000)
			usleep_range(1000, 2000);

		/* For MBI upgrade, MFW response includes the next buffer offset
		 * to be delivered to MFW.
		 */
		अगर (param && cmd == QED_PUT_खाता_DATA) अणु
			buf_idx = QED_MFW_GET_FIELD(param,
					FW_MB_PARAM_NVM_PUT_खाता_REQ_OFFSET);
			buf_size = QED_MFW_GET_FIELD(param,
					 FW_MB_PARAM_NVM_PUT_खाता_REQ_SIZE);
		पूर्ण अन्यथा अणु
			buf_idx += buf_size;
			buf_size = min_t(u32, (len - buf_idx),
					 MCP_DRV_NVM_BUF_LEN);
		पूर्ण
	पूर्ण

	cdev->mcp_nvm_resp = resp;
out:
	qed_ptt_release(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_phy_sfp_पढ़ो(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			 u32 port, u32 addr, u32 offset, u32 len, u8 *p_buf)
अणु
	u32 bytes_left, bytes_to_copy, buf_size, nvm_offset = 0;
	u32 resp, param;
	पूर्णांक rc;

	nvm_offset |= (port << DRV_MB_PARAM_TRANSCEIVER_PORT_OFFSET) &
		       DRV_MB_PARAM_TRANSCEIVER_PORT_MASK;
	nvm_offset |= (addr << DRV_MB_PARAM_TRANSCEIVER_I2C_ADDRESS_OFFSET) &
		       DRV_MB_PARAM_TRANSCEIVER_I2C_ADDRESS_MASK;

	addr = offset;
	offset = 0;
	bytes_left = len;
	जबतक (bytes_left > 0) अणु
		bytes_to_copy = min_t(u32, bytes_left,
				      MAX_I2C_TRANSACTION_SIZE);
		nvm_offset &= (DRV_MB_PARAM_TRANSCEIVER_I2C_ADDRESS_MASK |
			       DRV_MB_PARAM_TRANSCEIVER_PORT_MASK);
		nvm_offset |= ((addr + offset) <<
			       DRV_MB_PARAM_TRANSCEIVER_OFFSET_OFFSET) &
			       DRV_MB_PARAM_TRANSCEIVER_OFFSET_MASK;
		nvm_offset |= (bytes_to_copy <<
			       DRV_MB_PARAM_TRANSCEIVER_SIZE_OFFSET) &
			       DRV_MB_PARAM_TRANSCEIVER_SIZE_MASK;
		rc = qed_mcp_nvm_rd_cmd(p_hwfn, p_ptt,
					DRV_MSG_CODE_TRANSCEIVER_READ,
					nvm_offset, &resp, &param, &buf_size,
					(u32 *)(p_buf + offset));
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to send a transceiver read command to the MFW. rc = %d.\n",
				  rc);
			वापस rc;
		पूर्ण

		अगर (resp == FW_MSG_CODE_TRANSCEIVER_NOT_PRESENT)
			वापस -ENODEV;
		अन्यथा अगर (resp != FW_MSG_CODE_TRANSCEIVER_DIAG_OK)
			वापस -EINVAL;

		offset += buf_size;
		bytes_left -= buf_size;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_bist_रेजिस्टर_test(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 drv_mb_param = 0, rsp, param;
	पूर्णांक rc = 0;

	drv_mb_param = (DRV_MB_PARAM_BIST_REGISTER_TEST <<
			DRV_MB_PARAM_BIST_TEST_INDEX_SHIFT);

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_BIST_TEST,
			 drv_mb_param, &rsp, &param);

	अगर (rc)
		वापस rc;

	अगर (((rsp & FW_MSG_CODE_MASK) != FW_MSG_CODE_OK) ||
	    (param != DRV_MB_PARAM_BIST_RC_PASSED))
		rc = -EAGAIN;

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_bist_घड़ी_प्रकारest(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 drv_mb_param, rsp, param;
	पूर्णांक rc = 0;

	drv_mb_param = (DRV_MB_PARAM_BIST_CLOCK_TEST <<
			DRV_MB_PARAM_BIST_TEST_INDEX_SHIFT);

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_BIST_TEST,
			 drv_mb_param, &rsp, &param);

	अगर (rc)
		वापस rc;

	अगर (((rsp & FW_MSG_CODE_MASK) != FW_MSG_CODE_OK) ||
	    (param != DRV_MB_PARAM_BIST_RC_PASSED))
		rc = -EAGAIN;

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_bist_nvm_get_num_images(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    u32 *num_images)
अणु
	u32 drv_mb_param = 0, rsp;
	पूर्णांक rc = 0;

	drv_mb_param = (DRV_MB_PARAM_BIST_NVM_TEST_NUM_IMAGES <<
			DRV_MB_PARAM_BIST_TEST_INDEX_SHIFT);

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_BIST_TEST,
			 drv_mb_param, &rsp, num_images);
	अगर (rc)
		वापस rc;

	अगर (((rsp & FW_MSG_CODE_MASK) != FW_MSG_CODE_OK))
		rc = -EINVAL;

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_bist_nvm_get_image_att(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   काष्ठा bist_nvm_image_att *p_image_att,
				   u32 image_index)
अणु
	u32 buf_size = 0, param, resp = 0, resp_param = 0;
	पूर्णांक rc;

	param = DRV_MB_PARAM_BIST_NVM_TEST_IMAGE_BY_INDEX <<
		DRV_MB_PARAM_BIST_TEST_INDEX_SHIFT;
	param |= image_index << DRV_MB_PARAM_BIST_TEST_IMAGE_INDEX_SHIFT;

	rc = qed_mcp_nvm_rd_cmd(p_hwfn, p_ptt,
				DRV_MSG_CODE_BIST_TEST, param,
				&resp, &resp_param,
				&buf_size,
				(u32 *)p_image_att);
	अगर (rc)
		वापस rc;

	अगर (((resp & FW_MSG_CODE_MASK) != FW_MSG_CODE_OK) ||
	    (p_image_att->वापस_code != 1))
		rc = -EINVAL;

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_nvm_info_populate(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_nvm_image_info nvm_info;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc;
	u32 i;

	अगर (p_hwfn->nvm_info.valid)
		वापस 0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt) अणु
		DP_ERR(p_hwfn, "failed to acquire ptt\n");
		वापस -EBUSY;
	पूर्ण

	/* Acquire from MFW the amount of available images */
	nvm_info.num_images = 0;
	rc = qed_mcp_bist_nvm_get_num_images(p_hwfn,
					     p_ptt, &nvm_info.num_images);
	अगर (rc == -EOPNOTSUPP) अणु
		DP_INFO(p_hwfn, "DRV_MSG_CODE_BIST_TEST is not supported\n");
		जाओ out;
	पूर्ण अन्यथा अगर (rc || !nvm_info.num_images) अणु
		DP_ERR(p_hwfn, "Failed getting number of images\n");
		जाओ err0;
	पूर्ण

	nvm_info.image_att = kदो_स्मृति_array(nvm_info.num_images,
					   माप(काष्ठा bist_nvm_image_att),
					   GFP_KERNEL);
	अगर (!nvm_info.image_att) अणु
		rc = -ENOMEM;
		जाओ err0;
	पूर्ण

	/* Iterate over images and get their attributes */
	क्रम (i = 0; i < nvm_info.num_images; i++) अणु
		rc = qed_mcp_bist_nvm_get_image_att(p_hwfn, p_ptt,
						    &nvm_info.image_att[i], i);
		अगर (rc) अणु
			DP_ERR(p_hwfn,
			       "Failed getting image index %d attributes\n", i);
			जाओ err1;
		पूर्ण

		DP_VERBOSE(p_hwfn, QED_MSG_SP, "image index %d, size %x\n", i,
			   nvm_info.image_att[i].len);
	पूर्ण
out:
	/* Update hwfn's nvm_info */
	अगर (nvm_info.num_images) अणु
		p_hwfn->nvm_info.num_images = nvm_info.num_images;
		kमुक्त(p_hwfn->nvm_info.image_att);
		p_hwfn->nvm_info.image_att = nvm_info.image_att;
		p_hwfn->nvm_info.valid = true;
	पूर्ण

	qed_ptt_release(p_hwfn, p_ptt);
	वापस 0;

err1:
	kमुक्त(nvm_info.image_att);
err0:
	qed_ptt_release(p_hwfn, p_ptt);
	वापस rc;
पूर्ण

व्योम qed_mcp_nvm_info_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	kमुक्त(p_hwfn->nvm_info.image_att);
	p_hwfn->nvm_info.image_att = शून्य;
	p_hwfn->nvm_info.valid = false;
पूर्ण

पूर्णांक
qed_mcp_get_nvm_image_att(काष्ठा qed_hwfn *p_hwfn,
			  क्रमागत qed_nvm_images image_id,
			  काष्ठा qed_nvm_image_att *p_image_att)
अणु
	क्रमागत nvm_image_type type;
	u32 i;

	/* Translate image_id पूर्णांकo MFW definitions */
	चयन (image_id) अणु
	हाल QED_NVM_IMAGE_ISCSI_CFG:
		type = NVM_TYPE_ISCSI_CFG;
		अवरोध;
	हाल QED_NVM_IMAGE_FCOE_CFG:
		type = NVM_TYPE_FCOE_CFG;
		अवरोध;
	हाल QED_NVM_IMAGE_MDUMP:
		type = NVM_TYPE_MDUMP;
		अवरोध;
	हाल QED_NVM_IMAGE_NVM_CFG1:
		type = NVM_TYPE_NVM_CFG1;
		अवरोध;
	हाल QED_NVM_IMAGE_DEFAULT_CFG:
		type = NVM_TYPE_DEFAULT_CFG;
		अवरोध;
	हाल QED_NVM_IMAGE_NVM_META:
		type = NVM_TYPE_META;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unknown request of image_id %08x\n",
			  image_id);
		वापस -EINVAL;
	पूर्ण

	qed_mcp_nvm_info_populate(p_hwfn);
	क्रम (i = 0; i < p_hwfn->nvm_info.num_images; i++)
		अगर (type == p_hwfn->nvm_info.image_att[i].image_type)
			अवरोध;
	अगर (i == p_hwfn->nvm_info.num_images) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_STORAGE,
			   "Failed to find nvram image of type %08x\n",
			   image_id);
		वापस -ENOENT;
	पूर्ण

	p_image_att->start_addr = p_hwfn->nvm_info.image_att[i].nvm_start_addr;
	p_image_att->length = p_hwfn->nvm_info.image_att[i].len;

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_get_nvm_image(काष्ठा qed_hwfn *p_hwfn,
			  क्रमागत qed_nvm_images image_id,
			  u8 *p_buffer, u32 buffer_len)
अणु
	काष्ठा qed_nvm_image_att image_att;
	पूर्णांक rc;

	स_रखो(p_buffer, 0, buffer_len);

	rc = qed_mcp_get_nvm_image_att(p_hwfn, image_id, &image_att);
	अगर (rc)
		वापस rc;

	/* Validate sizes - both the image's and the supplied buffer's */
	अगर (image_att.length <= 4) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_STORAGE,
			   "Image [%d] is too small - only %d bytes\n",
			   image_id, image_att.length);
		वापस -EINVAL;
	पूर्ण

	अगर (image_att.length > buffer_len) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_STORAGE,
			   "Image [%d] is too big - %08x bytes where only %08x are available\n",
			   image_id, image_att.length, buffer_len);
		वापस -ENOMEM;
	पूर्ण

	वापस qed_mcp_nvm_पढ़ो(p_hwfn->cdev, image_att.start_addr,
				p_buffer, image_att.length);
पूर्ण

अटल क्रमागत resource_id_क्रमागत qed_mcp_get_mfw_res_id(क्रमागत qed_resources res_id)
अणु
	क्रमागत resource_id_क्रमागत mfw_res_id = RESOURCE_NUM_INVALID;

	चयन (res_id) अणु
	हाल QED_SB:
		mfw_res_id = RESOURCE_NUM_SB_E;
		अवरोध;
	हाल QED_L2_QUEUE:
		mfw_res_id = RESOURCE_NUM_L2_QUEUE_E;
		अवरोध;
	हाल QED_VPORT:
		mfw_res_id = RESOURCE_NUM_VPORT_E;
		अवरोध;
	हाल QED_RSS_ENG:
		mfw_res_id = RESOURCE_NUM_RSS_ENGINES_E;
		अवरोध;
	हाल QED_PQ:
		mfw_res_id = RESOURCE_NUM_PQ_E;
		अवरोध;
	हाल QED_RL:
		mfw_res_id = RESOURCE_NUM_RL_E;
		अवरोध;
	हाल QED_MAC:
	हाल QED_VLAN:
		/* Each VFC resource can accommodate both a MAC and a VLAN */
		mfw_res_id = RESOURCE_VFC_FILTER_E;
		अवरोध;
	हाल QED_ILT:
		mfw_res_id = RESOURCE_ILT_E;
		अवरोध;
	हाल QED_LL2_RAM_QUEUE:
		mfw_res_id = RESOURCE_LL2_QUEUE_E;
		अवरोध;
	हाल QED_LL2_CTX_QUEUE:
		mfw_res_id = RESOURCE_LL2_CQS_E;
		अवरोध;
	हाल QED_RDMA_CNQ_RAM:
	हाल QED_CMDQS_CQS:
		/* CNQ/CMDQS are the same resource */
		mfw_res_id = RESOURCE_CQS_E;
		अवरोध;
	हाल QED_RDMA_STATS_QUEUE:
		mfw_res_id = RESOURCE_RDMA_STATS_QUEUE_E;
		अवरोध;
	हाल QED_BDQ:
		mfw_res_id = RESOURCE_BDQ_E;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस mfw_res_id;
पूर्ण

#घोषणा QED_RESC_ALLOC_VERSION_MAJOR    2
#घोषणा QED_RESC_ALLOC_VERSION_MINOR    0
#घोषणा QED_RESC_ALLOC_VERSION				     \
	((QED_RESC_ALLOC_VERSION_MAJOR <<		     \
	  DRV_MB_PARAM_RESOURCE_ALLOC_VERSION_MAJOR_SHIFT) | \
	 (QED_RESC_ALLOC_VERSION_MINOR <<		     \
	  DRV_MB_PARAM_RESOURCE_ALLOC_VERSION_MINOR_SHIFT))

काष्ठा qed_resc_alloc_in_params अणु
	u32 cmd;
	क्रमागत qed_resources res_id;
	u32 resc_max_val;
पूर्ण;

काष्ठा qed_resc_alloc_out_params अणु
	u32 mcp_resp;
	u32 mcp_param;
	u32 resc_num;
	u32 resc_start;
	u32 vf_resc_num;
	u32 vf_resc_start;
	u32 flags;
पूर्ण;

अटल पूर्णांक
qed_mcp_resc_allocation_msg(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt,
			    काष्ठा qed_resc_alloc_in_params *p_in_params,
			    काष्ठा qed_resc_alloc_out_params *p_out_params)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	काष्ठा resource_info mfw_resc_info;
	पूर्णांक rc;

	स_रखो(&mfw_resc_info, 0, माप(mfw_resc_info));

	mfw_resc_info.res_id = qed_mcp_get_mfw_res_id(p_in_params->res_id);
	अगर (mfw_resc_info.res_id == RESOURCE_NUM_INVALID) अणु
		DP_ERR(p_hwfn,
		       "Failed to match resource %d [%s] with the MFW resources\n",
		       p_in_params->res_id,
		       qed_hw_get_resc_name(p_in_params->res_id));
		वापस -EINVAL;
	पूर्ण

	चयन (p_in_params->cmd) अणु
	हाल DRV_MSG_SET_RESOURCE_VALUE_MSG:
		mfw_resc_info.size = p_in_params->resc_max_val;
		fallthrough;
	हाल DRV_MSG_GET_RESOURCE_ALLOC_MSG:
		अवरोध;
	शेष:
		DP_ERR(p_hwfn, "Unexpected resource alloc command [0x%08x]\n",
		       p_in_params->cmd);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = p_in_params->cmd;
	mb_params.param = QED_RESC_ALLOC_VERSION;
	mb_params.p_data_src = &mfw_resc_info;
	mb_params.data_src_size = माप(mfw_resc_info);
	mb_params.p_data_dst = mb_params.p_data_src;
	mb_params.data_dst_size = mb_params.data_src_size;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "Resource message request: cmd 0x%08x, res_id %d [%s], hsi_version %d.%d, val 0x%x\n",
		   p_in_params->cmd,
		   p_in_params->res_id,
		   qed_hw_get_resc_name(p_in_params->res_id),
		   QED_MFW_GET_FIELD(mb_params.param,
				     DRV_MB_PARAM_RESOURCE_ALLOC_VERSION_MAJOR),
		   QED_MFW_GET_FIELD(mb_params.param,
				     DRV_MB_PARAM_RESOURCE_ALLOC_VERSION_MINOR),
		   p_in_params->resc_max_val);

	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		वापस rc;

	p_out_params->mcp_resp = mb_params.mcp_resp;
	p_out_params->mcp_param = mb_params.mcp_param;
	p_out_params->resc_num = mfw_resc_info.size;
	p_out_params->resc_start = mfw_resc_info.offset;
	p_out_params->vf_resc_num = mfw_resc_info.vf_size;
	p_out_params->vf_resc_start = mfw_resc_info.vf_offset;
	p_out_params->flags = mfw_resc_info.flags;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "Resource message response: mfw_hsi_version %d.%d, num 0x%x, start 0x%x, vf_num 0x%x, vf_start 0x%x, flags 0x%08x\n",
		   QED_MFW_GET_FIELD(p_out_params->mcp_param,
				     FW_MB_PARAM_RESOURCE_ALLOC_VERSION_MAJOR),
		   QED_MFW_GET_FIELD(p_out_params->mcp_param,
				     FW_MB_PARAM_RESOURCE_ALLOC_VERSION_MINOR),
		   p_out_params->resc_num,
		   p_out_params->resc_start,
		   p_out_params->vf_resc_num,
		   p_out_params->vf_resc_start, p_out_params->flags);

	वापस 0;
पूर्ण

पूर्णांक
qed_mcp_set_resc_max_val(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 क्रमागत qed_resources res_id,
			 u32 resc_max_val, u32 *p_mcp_resp)
अणु
	काष्ठा qed_resc_alloc_out_params out_params;
	काष्ठा qed_resc_alloc_in_params in_params;
	पूर्णांक rc;

	स_रखो(&in_params, 0, माप(in_params));
	in_params.cmd = DRV_MSG_SET_RESOURCE_VALUE_MSG;
	in_params.res_id = res_id;
	in_params.resc_max_val = resc_max_val;
	स_रखो(&out_params, 0, माप(out_params));
	rc = qed_mcp_resc_allocation_msg(p_hwfn, p_ptt, &in_params,
					 &out_params);
	अगर (rc)
		वापस rc;

	*p_mcp_resp = out_params.mcp_resp;

	वापस 0;
पूर्ण

पूर्णांक
qed_mcp_get_resc_info(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      क्रमागत qed_resources res_id,
		      u32 *p_mcp_resp, u32 *p_resc_num, u32 *p_resc_start)
अणु
	काष्ठा qed_resc_alloc_out_params out_params;
	काष्ठा qed_resc_alloc_in_params in_params;
	पूर्णांक rc;

	स_रखो(&in_params, 0, माप(in_params));
	in_params.cmd = DRV_MSG_GET_RESOURCE_ALLOC_MSG;
	in_params.res_id = res_id;
	स_रखो(&out_params, 0, माप(out_params));
	rc = qed_mcp_resc_allocation_msg(p_hwfn, p_ptt, &in_params,
					 &out_params);
	अगर (rc)
		वापस rc;

	*p_mcp_resp = out_params.mcp_resp;

	अगर (*p_mcp_resp == FW_MSG_CODE_RESOURCE_ALLOC_OK) अणु
		*p_resc_num = out_params.resc_num;
		*p_resc_start = out_params.resc_start;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_initiate_pf_flr(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 mcp_resp, mcp_param;

	वापस qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_INITIATE_PF_FLR, 0,
			   &mcp_resp, &mcp_param);
पूर्ण

अटल पूर्णांक qed_mcp_resource_cmd(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt,
				u32 param, u32 *p_mcp_resp, u32 *p_mcp_param)
अणु
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_RESOURCE_CMD, param,
			 p_mcp_resp, p_mcp_param);
	अगर (rc)
		वापस rc;

	अगर (*p_mcp_resp == FW_MSG_CODE_UNSUPPORTED) अणु
		DP_INFO(p_hwfn,
			"The resource command is unsupported by the MFW\n");
		वापस -EINVAL;
	पूर्ण

	अगर (*p_mcp_param == RESOURCE_OPCODE_UNKNOWN_CMD) अणु
		u8 opcode = QED_MFW_GET_FIELD(param, RESOURCE_CMD_REQ_OPCODE);

		DP_NOTICE(p_hwfn,
			  "The resource command is unknown to the MFW [param 0x%08x, opcode %d]\n",
			  param, opcode);
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
__qed_mcp_resc_lock(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    काष्ठा qed_resc_lock_params *p_params)
अणु
	u32 param = 0, mcp_resp, mcp_param;
	u8 opcode;
	पूर्णांक rc;

	चयन (p_params->समयout) अणु
	हाल QED_MCP_RESC_LOCK_TO_DEFAULT:
		opcode = RESOURCE_OPCODE_REQ;
		p_params->समयout = 0;
		अवरोध;
	हाल QED_MCP_RESC_LOCK_TO_NONE:
		opcode = RESOURCE_OPCODE_REQ_WO_AGING;
		p_params->समयout = 0;
		अवरोध;
	शेष:
		opcode = RESOURCE_OPCODE_REQ_W_AGING;
		अवरोध;
	पूर्ण

	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_RESC, p_params->resource);
	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_OPCODE, opcode);
	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_AGE, p_params->समयout);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "Resource lock request: param 0x%08x [age %d, opcode %d, resource %d]\n",
		   param, p_params->समयout, opcode, p_params->resource);

	/* Attempt to acquire the resource */
	rc = qed_mcp_resource_cmd(p_hwfn, p_ptt, param, &mcp_resp, &mcp_param);
	अगर (rc)
		वापस rc;

	/* Analyze the response */
	p_params->owner = QED_MFW_GET_FIELD(mcp_param, RESOURCE_CMD_RSP_OWNER);
	opcode = QED_MFW_GET_FIELD(mcp_param, RESOURCE_CMD_RSP_OPCODE);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "Resource lock response: mcp_param 0x%08x [opcode %d, owner %d]\n",
		   mcp_param, opcode, p_params->owner);

	चयन (opcode) अणु
	हाल RESOURCE_OPCODE_GNT:
		p_params->b_granted = true;
		अवरोध;
	हाल RESOURCE_OPCODE_BUSY:
		p_params->b_granted = false;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn,
			  "Unexpected opcode in resource lock response [mcp_param 0x%08x, opcode %d]\n",
			  mcp_param, opcode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
qed_mcp_resc_lock(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_ptt *p_ptt, काष्ठा qed_resc_lock_params *p_params)
अणु
	u32 retry_cnt = 0;
	पूर्णांक rc;

	करो अणु
		/* No need क्रम an पूर्णांकerval beक्रमe the first iteration */
		अगर (retry_cnt) अणु
			अगर (p_params->sleep_b4_retry) अणु
				u16 retry_पूर्णांकerval_in_ms =
				    DIV_ROUND_UP(p_params->retry_पूर्णांकerval,
						 1000);

				msleep(retry_पूर्णांकerval_in_ms);
			पूर्ण अन्यथा अणु
				udelay(p_params->retry_पूर्णांकerval);
			पूर्ण
		पूर्ण

		rc = __qed_mcp_resc_lock(p_hwfn, p_ptt, p_params);
		अगर (rc)
			वापस rc;

		अगर (p_params->b_granted)
			अवरोध;
	पूर्ण जबतक (retry_cnt++ < p_params->retry_num);

	वापस 0;
पूर्ण

पूर्णांक
qed_mcp_resc_unlock(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    काष्ठा qed_resc_unlock_params *p_params)
अणु
	u32 param = 0, mcp_resp, mcp_param;
	u8 opcode;
	पूर्णांक rc;

	opcode = p_params->b_क्रमce ? RESOURCE_OPCODE_FORCE_RELEASE
				   : RESOURCE_OPCODE_RELEASE;
	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_RESC, p_params->resource);
	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_OPCODE, opcode);

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "Resource unlock request: param 0x%08x [opcode %d, resource %d]\n",
		   param, opcode, p_params->resource);

	/* Attempt to release the resource */
	rc = qed_mcp_resource_cmd(p_hwfn, p_ptt, param, &mcp_resp, &mcp_param);
	अगर (rc)
		वापस rc;

	/* Analyze the response */
	opcode = QED_MFW_GET_FIELD(mcp_param, RESOURCE_CMD_RSP_OPCODE);

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "Resource unlock response: mcp_param 0x%08x [opcode %d]\n",
		   mcp_param, opcode);

	चयन (opcode) अणु
	हाल RESOURCE_OPCODE_RELEASED_PREVIOUS:
		DP_INFO(p_hwfn,
			"Resource unlock request for an already released resource [%d]\n",
			p_params->resource);
		fallthrough;
	हाल RESOURCE_OPCODE_RELEASED:
		p_params->b_released = true;
		अवरोध;
	हाल RESOURCE_OPCODE_WRONG_OWNER:
		p_params->b_released = false;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn,
			  "Unexpected opcode in resource unlock response [mcp_param 0x%08x, opcode %d]\n",
			  mcp_param, opcode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम qed_mcp_resc_lock_शेष_init(काष्ठा qed_resc_lock_params *p_lock,
				    काष्ठा qed_resc_unlock_params *p_unlock,
				    क्रमागत qed_resc_lock
				    resource, bool b_is_permanent)
अणु
	अगर (p_lock) अणु
		स_रखो(p_lock, 0, माप(*p_lock));

		/* Permanent resources करोn't require aging, and there's no
		 * poपूर्णांक in trying to acquire them more than once since it's
		 * unexpected another entity would release them.
		 */
		अगर (b_is_permanent) अणु
			p_lock->समयout = QED_MCP_RESC_LOCK_TO_NONE;
		पूर्ण अन्यथा अणु
			p_lock->retry_num = QED_MCP_RESC_LOCK_RETRY_CNT_DFLT;
			p_lock->retry_पूर्णांकerval =
			    QED_MCP_RESC_LOCK_RETRY_VAL_DFLT;
			p_lock->sleep_b4_retry = true;
		पूर्ण

		p_lock->resource = resource;
	पूर्ण

	अगर (p_unlock) अणु
		स_रखो(p_unlock, 0, माप(*p_unlock));
		p_unlock->resource = resource;
	पूर्ण
पूर्ण

bool qed_mcp_is_smart_an_supported(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस !!(p_hwfn->mcp_info->capabilities &
		  FW_MB_PARAM_FEATURE_SUPPORT_SMARTLINQ);
पूर्ण

पूर्णांक qed_mcp_get_capabilities(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 mcp_resp;
	पूर्णांक rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_GET_MFW_FEATURE_SUPPORT,
			 0, &mcp_resp, &p_hwfn->mcp_info->capabilities);
	अगर (!rc)
		DP_VERBOSE(p_hwfn, (QED_MSG_SP | NETIF_MSG_PROBE),
			   "MFW supported features: %08x\n",
			   p_hwfn->mcp_info->capabilities);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_set_capabilities(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 mcp_resp, mcp_param, features;

	features = DRV_MB_PARAM_FEATURE_SUPPORT_PORT_EEE |
		   DRV_MB_PARAM_FEATURE_SUPPORT_FUNC_VLINK |
		   DRV_MB_PARAM_FEATURE_SUPPORT_PORT_FEC_CONTROL;

	अगर (QED_IS_E5(p_hwfn->cdev))
		features |=
		    DRV_MB_PARAM_FEATURE_SUPPORT_PORT_EXT_SPEED_FEC_CONTROL;

	वापस qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_FEATURE_SUPPORT,
			   features, &mcp_resp, &mcp_param);
पूर्ण

पूर्णांक qed_mcp_get_engine_config(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_mb_params mb_params = अणु0पूर्ण;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u8 fir_valid, l2_valid;
	पूर्णांक rc;

	mb_params.cmd = DRV_MSG_CODE_GET_ENGINE_CONFIG;
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		वापस rc;

	अगर (mb_params.mcp_resp == FW_MSG_CODE_UNSUPPORTED) अणु
		DP_INFO(p_hwfn,
			"The get_engine_config command is unsupported by the MFW\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	fir_valid = QED_MFW_GET_FIELD(mb_params.mcp_param,
				      FW_MB_PARAM_ENG_CFG_FIR_AFFIN_VALID);
	अगर (fir_valid)
		cdev->fir_affin =
		    QED_MFW_GET_FIELD(mb_params.mcp_param,
				      FW_MB_PARAM_ENG_CFG_FIR_AFFIN_VALUE);

	l2_valid = QED_MFW_GET_FIELD(mb_params.mcp_param,
				     FW_MB_PARAM_ENG_CFG_L2_AFFIN_VALID);
	अगर (l2_valid)
		cdev->l2_affin_hपूर्णांक =
		    QED_MFW_GET_FIELD(mb_params.mcp_param,
				      FW_MB_PARAM_ENG_CFG_L2_AFFIN_VALUE);

	DP_INFO(p_hwfn,
		"Engine affinity config: FIR={valid %hhd, value %hhd}, L2_hint={valid %hhd, value %hhd}\n",
		fir_valid, cdev->fir_affin, l2_valid, cdev->l2_affin_hपूर्णांक);

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_get_ppfid_biपंचांगap(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_mb_params mb_params = अणु0पूर्ण;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	पूर्णांक rc;

	mb_params.cmd = DRV_MSG_CODE_GET_PPFID_BITMAP;
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		वापस rc;

	अगर (mb_params.mcp_resp == FW_MSG_CODE_UNSUPPORTED) अणु
		DP_INFO(p_hwfn,
			"The get_ppfid_bitmap command is unsupported by the MFW\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	cdev->ppfid_biपंचांगap = QED_MFW_GET_FIELD(mb_params.mcp_param,
					       FW_MB_PARAM_PPFID_BITMAP);

	DP_VERBOSE(p_hwfn, QED_MSG_SP, "PPFID bitmap 0x%hhx\n",
		   cdev->ppfid_biपंचांगap);

	वापस 0;
पूर्ण

पूर्णांक qed_mcp_nvm_get_cfg(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			u16 option_id, u8 entity_id, u16 flags, u8 *p_buf,
			u32 *p_len)
अणु
	u32 mb_param = 0, resp, param;
	पूर्णांक rc;

	QED_MFW_SET_FIELD(mb_param, DRV_MB_PARAM_NVM_CFG_OPTION_ID, option_id);
	अगर (flags & QED_NVM_CFG_OPTION_INIT)
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_INIT, 1);
	अगर (flags & QED_NVM_CFG_OPTION_FREE)
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_FREE, 1);
	अगर (flags & QED_NVM_CFG_OPTION_ENTITY_SEL) अणु
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_SEL, 1);
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_ID,
				  entity_id);
	पूर्ण

	rc = qed_mcp_nvm_rd_cmd(p_hwfn, p_ptt,
				DRV_MSG_CODE_GET_NVM_CFG_OPTION,
				mb_param, &resp, &param, p_len, (u32 *)p_buf);

	वापस rc;
पूर्ण

पूर्णांक qed_mcp_nvm_set_cfg(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			u16 option_id, u8 entity_id, u16 flags, u8 *p_buf,
			u32 len)
अणु
	u32 mb_param = 0, resp, param;

	QED_MFW_SET_FIELD(mb_param, DRV_MB_PARAM_NVM_CFG_OPTION_ID, option_id);
	अगर (flags & QED_NVM_CFG_OPTION_ALL)
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_ALL, 1);
	अगर (flags & QED_NVM_CFG_OPTION_INIT)
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_INIT, 1);
	अगर (flags & QED_NVM_CFG_OPTION_COMMIT)
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_COMMIT, 1);
	अगर (flags & QED_NVM_CFG_OPTION_FREE)
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_FREE, 1);
	अगर (flags & QED_NVM_CFG_OPTION_ENTITY_SEL) अणु
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_SEL, 1);
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_ID,
				  entity_id);
	पूर्ण

	वापस qed_mcp_nvm_wr_cmd(p_hwfn, p_ptt,
				  DRV_MSG_CODE_SET_NVM_CFG_OPTION,
				  mb_param, &resp, &param, len, (u32 *)p_buf);
पूर्ण

#घोषणा QED_MCP_DBG_DATA_MAX_SIZE               MCP_DRV_NVM_BUF_LEN
#घोषणा QED_MCP_DBG_DATA_MAX_HEADER_SIZE        माप(u32)
#घोषणा QED_MCP_DBG_DATA_MAX_PAYLOAD_SIZE \
	(QED_MCP_DBG_DATA_MAX_SIZE - QED_MCP_DBG_DATA_MAX_HEADER_SIZE)

अटल पूर्णांक
__qed_mcp_send_debug_data(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u8 *p_buf, u8 size)
अणु
	काष्ठा qed_mcp_mb_params mb_params;
	पूर्णांक rc;

	अगर (size > QED_MCP_DBG_DATA_MAX_SIZE) अणु
		DP_ERR(p_hwfn,
		       "Debug data size is %d while it should not exceed %d\n",
		       size, QED_MCP_DBG_DATA_MAX_SIZE);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&mb_params, 0, माप(mb_params));
	mb_params.cmd = DRV_MSG_CODE_DEBUG_DATA_SEND;
	SET_MFW_FIELD(mb_params.param, DRV_MSG_CODE_DEBUG_DATA_SEND_SIZE, size);
	mb_params.p_data_src = p_buf;
	mb_params.data_src_size = size;
	rc = qed_mcp_cmd_and_जोड़(p_hwfn, p_ptt, &mb_params);
	अगर (rc)
		वापस rc;

	अगर (mb_params.mcp_resp == FW_MSG_CODE_UNSUPPORTED) अणु
		DP_INFO(p_hwfn,
			"The DEBUG_DATA_SEND command is unsupported by the MFW\n");
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (mb_params.mcp_resp == (u32)FW_MSG_CODE_DEBUG_NOT_ENABLED) अणु
		DP_INFO(p_hwfn, "The DEBUG_DATA_SEND command is not enabled\n");
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (mb_params.mcp_resp != (u32)FW_MSG_CODE_DEBUG_DATA_SEND_OK) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to send debug data to the MFW [resp 0x%08x]\n",
			  mb_params.mcp_resp);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत qed_mcp_dbg_data_type अणु
	QED_MCP_DBG_DATA_TYPE_RAW,
पूर्ण;

/* Header क्रमmat: [31:28] PFID, [27:20] flags, [19:12] type, [11:0] S/N */
#घोषणा QED_MCP_DBG_DATA_HDR_SN_OFFSET  0
#घोषणा QED_MCP_DBG_DATA_HDR_SN_MASK            0x00000fff
#घोषणा QED_MCP_DBG_DATA_HDR_TYPE_OFFSET        12
#घोषणा QED_MCP_DBG_DATA_HDR_TYPE_MASK  0x000ff000
#घोषणा QED_MCP_DBG_DATA_HDR_FLAGS_OFFSET       20
#घोषणा QED_MCP_DBG_DATA_HDR_FLAGS_MASK 0x0ff00000
#घोषणा QED_MCP_DBG_DATA_HDR_PF_OFFSET  28
#घोषणा QED_MCP_DBG_DATA_HDR_PF_MASK            0xf0000000

#घोषणा QED_MCP_DBG_DATA_HDR_FLAGS_FIRST        0x1
#घोषणा QED_MCP_DBG_DATA_HDR_FLAGS_LAST 0x2

अटल पूर्णांक
qed_mcp_send_debug_data(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt,
			क्रमागत qed_mcp_dbg_data_type type, u8 *p_buf, u32 size)
अणु
	u8 raw_data[QED_MCP_DBG_DATA_MAX_SIZE], *p_पंचांगp_buf = p_buf;
	u32 पंचांगp_size = size, *p_header, *p_payload;
	u8 flags = 0;
	u16 seq;
	पूर्णांक rc;

	p_header = (u32 *)raw_data;
	p_payload = (u32 *)(raw_data + QED_MCP_DBG_DATA_MAX_HEADER_SIZE);

	seq = (u16)atomic_inc_वापस(&p_hwfn->mcp_info->dbg_data_seq);

	/* First chunk is marked as 'first' */
	flags |= QED_MCP_DBG_DATA_HDR_FLAGS_FIRST;

	*p_header = 0;
	SET_MFW_FIELD(*p_header, QED_MCP_DBG_DATA_HDR_SN, seq);
	SET_MFW_FIELD(*p_header, QED_MCP_DBG_DATA_HDR_TYPE, type);
	SET_MFW_FIELD(*p_header, QED_MCP_DBG_DATA_HDR_FLAGS, flags);
	SET_MFW_FIELD(*p_header, QED_MCP_DBG_DATA_HDR_PF, p_hwfn->असल_pf_id);

	जबतक (पंचांगp_size > QED_MCP_DBG_DATA_MAX_PAYLOAD_SIZE) अणु
		स_नकल(p_payload, p_पंचांगp_buf, QED_MCP_DBG_DATA_MAX_PAYLOAD_SIZE);
		rc = __qed_mcp_send_debug_data(p_hwfn, p_ptt, raw_data,
					       QED_MCP_DBG_DATA_MAX_SIZE);
		अगर (rc)
			वापस rc;

		/* Clear the 'first' marking after sending the first chunk */
		अगर (p_पंचांगp_buf == p_buf) अणु
			flags &= ~QED_MCP_DBG_DATA_HDR_FLAGS_FIRST;
			SET_MFW_FIELD(*p_header, QED_MCP_DBG_DATA_HDR_FLAGS,
				      flags);
		पूर्ण

		p_पंचांगp_buf += QED_MCP_DBG_DATA_MAX_PAYLOAD_SIZE;
		पंचांगp_size -= QED_MCP_DBG_DATA_MAX_PAYLOAD_SIZE;
	पूर्ण

	/* Last chunk is marked as 'last' */
	flags |= QED_MCP_DBG_DATA_HDR_FLAGS_LAST;
	SET_MFW_FIELD(*p_header, QED_MCP_DBG_DATA_HDR_FLAGS, flags);
	स_नकल(p_payload, p_पंचांगp_buf, पंचांगp_size);

	/* Casting the left size to u8 is ok since at this poपूर्णांक it is <= 32 */
	वापस __qed_mcp_send_debug_data(p_hwfn, p_ptt, raw_data,
					 (u8)(QED_MCP_DBG_DATA_MAX_HEADER_SIZE +
					 पंचांगp_size));
पूर्ण

पूर्णांक
qed_mcp_send_raw_debug_data(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, u8 *p_buf, u32 size)
अणु
	वापस qed_mcp_send_debug_data(p_hwfn, p_ptt,
				       QED_MCP_DBG_DATA_TYPE_RAW, p_buf, size);
पूर्ण
