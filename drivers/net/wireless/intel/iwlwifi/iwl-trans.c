<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 * Copyright (C) 2019-2021 Intel Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/द्वा_खोज.h>

#समावेश "fw/api/tx.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-drv.h"
#समावेश "iwl-fh.h"
#समावेश "queue/tx.h"
#समावेश <linux/dmapool.h>
#समावेश "fw/api/commands.h"

काष्ठा iwl_trans *iwl_trans_alloc(अचिन्हित पूर्णांक priv_size,
				  काष्ठा device *dev,
				  स्थिर काष्ठा iwl_trans_ops *ops,
				  स्थिर काष्ठा iwl_cfg_trans_params *cfg_trans)
अणु
	काष्ठा iwl_trans *trans;
#अगर_घोषित CONFIG_LOCKDEP
	अटल काष्ठा lock_class_key __key;
#पूर्ण_अगर

	trans = devm_kzalloc(dev, माप(*trans) + priv_size, GFP_KERNEL);
	अगर (!trans)
		वापस शून्य;

	trans->trans_cfg = cfg_trans;

#अगर_घोषित CONFIG_LOCKDEP
	lockdep_init_map(&trans->sync_cmd_lockdep_map, "sync_cmd_lockdep_map",
			 &__key, 0);
#पूर्ण_अगर

	trans->dev = dev;
	trans->ops = ops;
	trans->num_rx_queues = 1;

	WARN_ON(!ops->रुको_txq_empty && !ops->रुको_tx_queues_empty);

	अगर (trans->trans_cfg->use_tfh) अणु
		trans->txqs.tfd.addr_size = 64;
		trans->txqs.tfd.max_tbs = IWL_TFH_NUM_TBS;
		trans->txqs.tfd.size = माप(काष्ठा iwl_tfh_tfd);
	पूर्ण अन्यथा अणु
		trans->txqs.tfd.addr_size = 36;
		trans->txqs.tfd.max_tbs = IWL_NUM_OF_TBS;
		trans->txqs.tfd.size = माप(काष्ठा iwl_tfd);
	पूर्ण
	trans->max_skb_frags = IWL_TRANS_MAX_FRAGS(trans);

	वापस trans;
पूर्ण

पूर्णांक iwl_trans_init(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक txcmd_size, txcmd_align;

	अगर (!trans->trans_cfg->gen2) अणु
		txcmd_size = माप(काष्ठा iwl_tx_cmd);
		txcmd_align = माप(व्योम *);
	पूर्ण अन्यथा अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210) अणु
		txcmd_size = माप(काष्ठा iwl_tx_cmd_gen2);
		txcmd_align = 64;
	पूर्ण अन्यथा अणु
		txcmd_size = माप(काष्ठा iwl_tx_cmd_gen3);
		txcmd_align = 128;
	पूर्ण

	txcmd_size += माप(काष्ठा iwl_cmd_header);
	txcmd_size += 36; /* biggest possible 802.11 header */

	/* Ensure device TX cmd cannot reach/cross a page boundary in gen2 */
	अगर (WARN_ON(trans->trans_cfg->gen2 && txcmd_size >= txcmd_align))
		वापस -EINVAL;

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		trans->txqs.bc_tbl_size = माप(काष्ठा iwl_gen3_bc_tbl);
	अन्यथा
		trans->txqs.bc_tbl_size = माप(काष्ठा iwlagn_scd_bc_tbl);
	/*
	 * For gen2 devices, we use a single allocation क्रम each byte-count
	 * table, but they're pretty small (1k) so use a DMA pool that we
	 * allocate here.
	 */
	अगर (trans->trans_cfg->gen2) अणु
		trans->txqs.bc_pool = dmam_pool_create("iwlwifi:bc", trans->dev,
						       trans->txqs.bc_tbl_size,
						       256, 0);
		अगर (!trans->txqs.bc_pool)
			वापस -ENOMEM;
	पूर्ण

	/* Some things must not change even अगर the config करोes */
	WARN_ON(trans->txqs.tfd.addr_size !=
		(trans->trans_cfg->use_tfh ? 64 : 36));

	snम_लिखो(trans->dev_cmd_pool_name, माप(trans->dev_cmd_pool_name),
		 "iwl_cmd_pool:%s", dev_name(trans->dev));
	trans->dev_cmd_pool =
		kmem_cache_create(trans->dev_cmd_pool_name,
				  txcmd_size, txcmd_align,
				  SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!trans->dev_cmd_pool)
		वापस -ENOMEM;

	trans->txqs.tso_hdr_page = alloc_percpu(काष्ठा iwl_tso_hdr_page);
	अगर (!trans->txqs.tso_hdr_page) अणु
		kmem_cache_destroy(trans->dev_cmd_pool);
		वापस -ENOMEM;
	पूर्ण

	/* Initialize the रुको queue क्रम commands */
	init_रुकोqueue_head(&trans->रुको_command_queue);

	वापस 0;
पूर्ण

व्योम iwl_trans_मुक्त(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक i;

	अगर (trans->txqs.tso_hdr_page) अणु
		क्रम_each_possible_cpu(i) अणु
			काष्ठा iwl_tso_hdr_page *p =
				per_cpu_ptr(trans->txqs.tso_hdr_page, i);

			अगर (p && p->page)
				__मुक्त_page(p->page);
		पूर्ण

		मुक्त_percpu(trans->txqs.tso_hdr_page);
	पूर्ण

	kmem_cache_destroy(trans->dev_cmd_pool);
पूर्ण

पूर्णांक iwl_trans_send_cmd(काष्ठा iwl_trans *trans, काष्ठा iwl_host_cmd *cmd)
अणु
	पूर्णांक ret;

	अगर (unlikely(!(cmd->flags & CMD_SEND_IN_RFKILL) &&
		     test_bit(STATUS_RFKILL_OPMODE, &trans->status)))
		वापस -ERFKILL;

	/*
	 * We can't test IWL_MVM_STATUS_IN_D3 in mvm->status because this
	 * bit is set early in the D3 flow, beक्रमe we send all the commands
	 * that configure the firmware क्रम D3 operation (घातer, patterns, ...)
	 * and we करोn't want to flag all those with CMD_SEND_IN_D3.
	 * So use the प्रणाली_pm_mode instead. The only command sent after
	 * we set प्रणाली_pm_mode is D3_CONFIG_CMD, which we now flag with
	 * CMD_SEND_IN_D3.
	 */
	अगर (unlikely(trans->प्रणाली_pm_mode == IWL_PLAT_PM_MODE_D3 &&
		     !(cmd->flags & CMD_SEND_IN_D3)))
		वापस -EHOSTDOWN;

	अगर (unlikely(test_bit(STATUS_FW_ERROR, &trans->status)))
		वापस -EIO;

	अगर (unlikely(trans->state != IWL_TRANS_FW_ALIVE)) अणु
		IWL_ERR(trans, "%s bad state = %d\n", __func__, trans->state);
		वापस -EIO;
	पूर्ण

	अगर (WARN_ON((cmd->flags & CMD_WANT_ASYNC_CALLBACK) &&
		    !(cmd->flags & CMD_ASYNC)))
		वापस -EINVAL;

	अगर (!(cmd->flags & CMD_ASYNC))
		lock_map_acquire_पढ़ो(&trans->sync_cmd_lockdep_map);

	अगर (trans->wide_cmd_header && !iwl_cmd_groupid(cmd->id)) अणु
		अगर (cmd->id != REPLY_ERROR)
			cmd->id = DEF_ID(cmd->id);
	पूर्ण

	ret = iwl_trans_txq_send_hcmd(trans, cmd);

	अगर (!(cmd->flags & CMD_ASYNC))
		lock_map_release(&trans->sync_cmd_lockdep_map);

	अगर (WARN_ON((cmd->flags & CMD_WANT_SKB) && !ret && !cmd->resp_pkt))
		वापस -EIO;

	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_trans_send_cmd);

/* Comparator क्रम काष्ठा iwl_hcmd_names.
 * Used in the binary search over a list of host commands.
 *
 * @key: command_id that we're looking क्रम.
 * @elt: काष्ठा iwl_hcmd_names candidate क्रम match.
 *
 * @वापस 0 अगरf equal.
 */
अटल पूर्णांक iwl_hcmd_names_cmp(स्थिर व्योम *key, स्थिर व्योम *elt)
अणु
	स्थिर काष्ठा iwl_hcmd_names *name = elt;
	u8 cmd1 = *(u8 *)key;
	u8 cmd2 = name->cmd_id;

	वापस (cmd1 - cmd2);
पूर्ण

स्थिर अक्षर *iwl_get_cmd_string(काष्ठा iwl_trans *trans, u32 id)
अणु
	u8 grp, cmd;
	काष्ठा iwl_hcmd_names *ret;
	स्थिर काष्ठा iwl_hcmd_arr *arr;
	माप_प्रकार size = माप(काष्ठा iwl_hcmd_names);

	grp = iwl_cmd_groupid(id);
	cmd = iwl_cmd_opcode(id);

	अगर (!trans->command_groups || grp >= trans->command_groups_size ||
	    !trans->command_groups[grp].arr)
		वापस "UNKNOWN";

	arr = &trans->command_groups[grp];
	ret = द्वा_खोज(&cmd, arr->arr, arr->size, size, iwl_hcmd_names_cmp);
	अगर (!ret)
		वापस "UNKNOWN";
	वापस ret->cmd_name;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_get_cmd_string);

पूर्णांक iwl_cmd_groups_verअगरy_sorted(स्थिर काष्ठा iwl_trans_config *trans)
अणु
	पूर्णांक i, j;
	स्थिर काष्ठा iwl_hcmd_arr *arr;

	क्रम (i = 0; i < trans->command_groups_size; i++) अणु
		arr = &trans->command_groups[i];
		अगर (!arr->arr)
			जारी;
		क्रम (j = 0; j < arr->size - 1; j++)
			अगर (arr->arr[j].cmd_id > arr->arr[j + 1].cmd_id)
				वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_cmd_groups_verअगरy_sorted);
