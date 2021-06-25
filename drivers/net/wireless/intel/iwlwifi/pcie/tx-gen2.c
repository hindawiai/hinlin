<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#समावेश <net/tso.h>
#समावेश <linux/tcp.h>

#समावेश "iwl-debug.h"
#समावेश "iwl-csr.h"
#समावेश "iwl-io.h"
#समावेश "internal.h"
#समावेश "fw/api/tx.h"
#समावेश "queue/tx.h"

/*************** HOST COMMAND QUEUE FUNCTIONS   *****/

/*
 * iwl_pcie_gen2_enqueue_hcmd - enqueue a uCode command
 * @priv: device निजी data poपूर्णांक
 * @cmd: a poपूर्णांकer to the ucode command काष्ठाure
 *
 * The function वापसs < 0 values to indicate the operation
 * failed. On success, it वापसs the index (>= 0) of command in the
 * command queue.
 */
पूर्णांक iwl_pcie_gen2_enqueue_hcmd(काष्ठा iwl_trans *trans,
			       काष्ठा iwl_host_cmd *cmd)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_txq *txq = trans->txqs.txq[trans->txqs.cmd.q_id];
	काष्ठा iwl_device_cmd *out_cmd;
	काष्ठा iwl_cmd_meta *out_meta;
	व्योम *dup_buf = शून्य;
	dma_addr_t phys_addr;
	पूर्णांक i, cmd_pos, idx;
	u16 copy_size, cmd_size, tb0_size;
	bool had_nocopy = false;
	u8 group_id = iwl_cmd_groupid(cmd->id);
	स्थिर u8 *cmddata[IWL_MAX_CMD_TBS_PER_TFD];
	u16 cmdlen[IWL_MAX_CMD_TBS_PER_TFD];
	काष्ठा iwl_tfh_tfd *tfd;
	अचिन्हित दीर्घ flags;

	copy_size = माप(काष्ठा iwl_cmd_header_wide);
	cmd_size = माप(काष्ठा iwl_cmd_header_wide);

	क्रम (i = 0; i < IWL_MAX_CMD_TBS_PER_TFD; i++) अणु
		cmddata[i] = cmd->data[i];
		cmdlen[i] = cmd->len[i];

		अगर (!cmd->len[i])
			जारी;

		/* need at least IWL_FIRST_TB_SIZE copied */
		अगर (copy_size < IWL_FIRST_TB_SIZE) अणु
			पूर्णांक copy = IWL_FIRST_TB_SIZE - copy_size;

			अगर (copy > cmdlen[i])
				copy = cmdlen[i];
			cmdlen[i] -= copy;
			cmddata[i] += copy;
			copy_size += copy;
		पूर्ण

		अगर (cmd->dataflags[i] & IWL_HCMD_DFL_NOCOPY) अणु
			had_nocopy = true;
			अगर (WARN_ON(cmd->dataflags[i] & IWL_HCMD_DFL_DUP)) अणु
				idx = -EINVAL;
				जाओ मुक्त_dup_buf;
			पूर्ण
		पूर्ण अन्यथा अगर (cmd->dataflags[i] & IWL_HCMD_DFL_DUP) अणु
			/*
			 * This is also a chunk that isn't copied
			 * to the अटल buffer so set had_nocopy.
			 */
			had_nocopy = true;

			/* only allowed once */
			अगर (WARN_ON(dup_buf)) अणु
				idx = -EINVAL;
				जाओ मुक्त_dup_buf;
			पूर्ण

			dup_buf = kmemdup(cmddata[i], cmdlen[i],
					  GFP_ATOMIC);
			अगर (!dup_buf)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			/* NOCOPY must not be followed by normal! */
			अगर (WARN_ON(had_nocopy)) अणु
				idx = -EINVAL;
				जाओ मुक्त_dup_buf;
			पूर्ण
			copy_size += cmdlen[i];
		पूर्ण
		cmd_size += cmd->len[i];
	पूर्ण

	/*
	 * If any of the command काष्ठाures end up being larger than the
	 * TFD_MAX_PAYLOAD_SIZE and they aren't dynamically allocated पूर्णांकo
	 * separate TFDs, then we will need to increase the size of the buffers
	 */
	अगर (WARN(copy_size > TFD_MAX_PAYLOAD_SIZE,
		 "Command %s (%#x) is too large (%d bytes)\n",
		 iwl_get_cmd_string(trans, cmd->id), cmd->id, copy_size)) अणु
		idx = -EINVAL;
		जाओ मुक्त_dup_buf;
	पूर्ण

	spin_lock_irqsave(&txq->lock, flags);

	idx = iwl_txq_get_cmd_index(txq, txq->ग_लिखो_ptr);
	tfd = iwl_txq_get_tfd(trans, txq, txq->ग_लिखो_ptr);
	स_रखो(tfd, 0, माप(*tfd));

	अगर (iwl_txq_space(trans, txq) < ((cmd->flags & CMD_ASYNC) ? 2 : 1)) अणु
		spin_unlock_irqrestore(&txq->lock, flags);

		IWL_ERR(trans, "No space in command queue\n");
		iwl_op_mode_cmd_queue_full(trans->op_mode);
		idx = -ENOSPC;
		जाओ मुक्त_dup_buf;
	पूर्ण

	out_cmd = txq->entries[idx].cmd;
	out_meta = &txq->entries[idx].meta;

	/* re-initialize to शून्य */
	स_रखो(out_meta, 0, माप(*out_meta));
	अगर (cmd->flags & CMD_WANT_SKB)
		out_meta->source = cmd;

	/* set up the header */
	out_cmd->hdr_wide.cmd = iwl_cmd_opcode(cmd->id);
	out_cmd->hdr_wide.group_id = group_id;
	out_cmd->hdr_wide.version = iwl_cmd_version(cmd->id);
	out_cmd->hdr_wide.length =
		cpu_to_le16(cmd_size - माप(काष्ठा iwl_cmd_header_wide));
	out_cmd->hdr_wide.reserved = 0;
	out_cmd->hdr_wide.sequence =
		cpu_to_le16(QUEUE_TO_SEQ(trans->txqs.cmd.q_id) |
					 INDEX_TO_SEQ(txq->ग_लिखो_ptr));

	cmd_pos = माप(काष्ठा iwl_cmd_header_wide);
	copy_size = माप(काष्ठा iwl_cmd_header_wide);

	/* and copy the data that needs to be copied */
	क्रम (i = 0; i < IWL_MAX_CMD_TBS_PER_TFD; i++) अणु
		पूर्णांक copy;

		अगर (!cmd->len[i])
			जारी;

		/* copy everything अगर not nocopy/dup */
		अगर (!(cmd->dataflags[i] & (IWL_HCMD_DFL_NOCOPY |
					   IWL_HCMD_DFL_DUP))) अणु
			copy = cmd->len[i];

			स_नकल((u8 *)out_cmd + cmd_pos, cmd->data[i], copy);
			cmd_pos += copy;
			copy_size += copy;
			जारी;
		पूर्ण

		/*
		 * Otherwise we need at least IWL_FIRST_TB_SIZE copied
		 * in total (क्रम bi-directional DMA), but copy up to what
		 * we can fit पूर्णांकo the payload क्रम debug dump purposes.
		 */
		copy = min_t(पूर्णांक, TFD_MAX_PAYLOAD_SIZE - cmd_pos, cmd->len[i]);

		स_नकल((u8 *)out_cmd + cmd_pos, cmd->data[i], copy);
		cmd_pos += copy;

		/* However, treat copy_size the proper way, we need it below */
		अगर (copy_size < IWL_FIRST_TB_SIZE) अणु
			copy = IWL_FIRST_TB_SIZE - copy_size;

			अगर (copy > cmd->len[i])
				copy = cmd->len[i];
			copy_size += copy;
		पूर्ण
	पूर्ण

	IWL_DEBUG_HC(trans,
		     "Sending command %s (%.2x.%.2x), seq: 0x%04X, %d bytes at %d[%d]:%d\n",
		     iwl_get_cmd_string(trans, cmd->id), group_id,
		     out_cmd->hdr.cmd, le16_to_cpu(out_cmd->hdr.sequence),
		     cmd_size, txq->ग_लिखो_ptr, idx, trans->txqs.cmd.q_id);

	/* start the TFD with the minimum copy bytes */
	tb0_size = min_t(पूर्णांक, copy_size, IWL_FIRST_TB_SIZE);
	स_नकल(&txq->first_tb_bufs[idx], out_cmd, tb0_size);
	iwl_txq_gen2_set_tb(trans, tfd, iwl_txq_get_first_tb_dma(txq, idx),
			    tb0_size);

	/* map first command fragment, अगर any reमुख्यs */
	अगर (copy_size > tb0_size) अणु
		phys_addr = dma_map_single(trans->dev,
					   (u8 *)out_cmd + tb0_size,
					   copy_size - tb0_size,
					   DMA_TO_DEVICE);
		अगर (dma_mapping_error(trans->dev, phys_addr)) अणु
			idx = -ENOMEM;
			iwl_txq_gen2_tfd_unmap(trans, out_meta, tfd);
			जाओ out;
		पूर्ण
		iwl_txq_gen2_set_tb(trans, tfd, phys_addr,
				    copy_size - tb0_size);
	पूर्ण

	/* map the reमुख्यing (adjusted) nocopy/dup fragments */
	क्रम (i = 0; i < IWL_MAX_CMD_TBS_PER_TFD; i++) अणु
		स्थिर व्योम *data = cmddata[i];

		अगर (!cmdlen[i])
			जारी;
		अगर (!(cmd->dataflags[i] & (IWL_HCMD_DFL_NOCOPY |
					   IWL_HCMD_DFL_DUP)))
			जारी;
		अगर (cmd->dataflags[i] & IWL_HCMD_DFL_DUP)
			data = dup_buf;
		phys_addr = dma_map_single(trans->dev, (व्योम *)data,
					   cmdlen[i], DMA_TO_DEVICE);
		अगर (dma_mapping_error(trans->dev, phys_addr)) अणु
			idx = -ENOMEM;
			iwl_txq_gen2_tfd_unmap(trans, out_meta, tfd);
			जाओ out;
		पूर्ण
		iwl_txq_gen2_set_tb(trans, tfd, phys_addr, cmdlen[i]);
	पूर्ण

	BUILD_BUG_ON(IWL_TFH_NUM_TBS > माप(out_meta->tbs) * BITS_PER_BYTE);
	out_meta->flags = cmd->flags;
	अगर (WARN_ON_ONCE(txq->entries[idx].मुक्त_buf))
		kमुक्त_sensitive(txq->entries[idx].मुक्त_buf);
	txq->entries[idx].मुक्त_buf = dup_buf;

	trace_iwlwअगरi_dev_hcmd(trans->dev, cmd, cmd_size, &out_cmd->hdr_wide);

	/* start समयr अगर queue currently empty */
	अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr && txq->wd_समयout)
		mod_समयr(&txq->stuck_समयr, jअगरfies + txq->wd_समयout);

	spin_lock(&trans_pcie->reg_lock);
	/* Increment and update queue's ग_लिखो index */
	txq->ग_लिखो_ptr = iwl_txq_inc_wrap(trans, txq->ग_लिखो_ptr);
	iwl_txq_inc_wr_ptr(trans, txq);
	spin_unlock(&trans_pcie->reg_lock);

out:
	spin_unlock_irqrestore(&txq->lock, flags);
मुक्त_dup_buf:
	अगर (idx < 0)
		kमुक्त(dup_buf);
	वापस idx;
पूर्ण
