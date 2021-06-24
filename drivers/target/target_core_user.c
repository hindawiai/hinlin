<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Shaohua Li <shli@kernel.org>
 * Copyright (C) 2014 Red Hat, Inc.
 * Copyright (C) 2015 Arrikto, Inc.
 * Copyright (C) 2017 Chinamobile, Inc.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/parser.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/xarray.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/bitops.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/configfs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <net/genetlink.h>
#समावेश <scsi/scsi_common.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <target/target_core_backend.h>

#समावेश <linux/target_core_user.h>

/**
 * DOC: Userspace I/O
 * Userspace I/O
 * -------------
 *
 * Define a shared-memory पूर्णांकerface क्रम LIO to pass SCSI commands and
 * data to userspace क्रम processing. This is to allow backends that
 * are too complex क्रम in-kernel support to be possible.
 *
 * It uses the UIO framework to करो a lot of the device-creation and
 * पूर्णांकrospection work क्रम us.
 *
 * See the .h file क्रम how the ring is laid out. Note that जबतक the
 * command ring is defined, the particulars of the data area are
 * not. Offset values in the command entry poपूर्णांक to other locations
 * पूर्णांकernal to the mmap-ed area. There is separate space outside the
 * command ring क्रम data buffers. This leaves maximum flexibility क्रम
 * moving buffer allocations, or even page flipping or other
 * allocation techniques, without altering the command ring layout.
 *
 * SECURITY:
 * The user process must be assumed to be malicious. There's no way to
 * prevent it अवरोधing the command ring protocol अगर it wants, but in
 * order to prevent other issues we must only ever पढ़ो *data* from
 * the shared memory area, not offsets or sizes. This applies to
 * command ring entries as well as the mailbox. Extra code needed क्रम
 * this may have a 'UAM' comment.
 */

#घोषणा TCMU_TIME_OUT (30 * MSEC_PER_SEC)

/* For mailbox plus cmd ring, the size is fixed 8MB */
#घोषणा MB_CMDR_SIZE (8 * 1024 * 1024)
/* Offset of cmd ring is size of mailbox */
#घोषणा CMDR_OFF माप(काष्ठा tcmu_mailbox)
#घोषणा CMDR_SIZE (MB_CMDR_SIZE - CMDR_OFF)

/*
 * For data area, the शेष block size is PAGE_SIZE and
 * the शेष total size is 256K * PAGE_SIZE.
 */
#घोषणा DATA_PAGES_PER_BLK_DEF 1
#घोषणा DATA_AREA_PAGES_DEF (256 * 1024)

#घोषणा TCMU_MBS_TO_PAGES(_mbs) ((माप_प्रकार)_mbs << (20 - PAGE_SHIFT))
#घोषणा TCMU_PAGES_TO_MBS(_pages) (_pages >> (20 - PAGE_SHIFT))

/*
 * Default number of global data blocks(512K * PAGE_SIZE)
 * when the unmap thपढ़ो will be started.
 */
#घोषणा TCMU_GLOBAL_MAX_PAGES_DEF (512 * 1024)

अटल u8 tcmu_kern_cmd_reply_supported;
अटल u8 tcmu_netlink_blocked;

अटल काष्ठा device *tcmu_root_device;

काष्ठा tcmu_hba अणु
	u32 host_id;
पूर्ण;

#घोषणा TCMU_CONFIG_LEN 256

अटल DEFINE_MUTEX(tcmu_nl_cmd_mutex);
अटल LIST_HEAD(tcmu_nl_cmd_list);

काष्ठा tcmu_dev;

काष्ठा tcmu_nl_cmd अणु
	/* wake up thपढ़ो रुकोing क्रम reply */
	काष्ठा completion complete;
	काष्ठा list_head nl_list;
	काष्ठा tcmu_dev *udev;
	पूर्णांक cmd;
	पूर्णांक status;
पूर्ण;

काष्ठा tcmu_dev अणु
	काष्ठा list_head node;
	काष्ठा kref kref;

	काष्ठा se_device se_dev;
	काष्ठा se_dev_plug se_plug;

	अक्षर *name;
	काष्ठा se_hba *hba;

#घोषणा TCMU_DEV_BIT_OPEN 0
#घोषणा TCMU_DEV_BIT_BROKEN 1
#घोषणा TCMU_DEV_BIT_BLOCKED 2
#घोषणा TCMU_DEV_BIT_TMR_NOTIFY 3
#घोषणा TCM_DEV_BIT_PLUGGED 4
	अचिन्हित दीर्घ flags;

	काष्ठा uio_info uio_info;

	काष्ठा inode *inode;

	uपूर्णांक64_t dev_size;

	काष्ठा tcmu_mailbox *mb_addr;
	व्योम *cmdr;
	u32 cmdr_size;
	u32 cmdr_last_cleaned;
	/* Offset of data area from start of mb */
	/* Must add data_off and mb_addr to get the address */
	माप_प्रकार data_off;
	पूर्णांक data_area_mb;
	uपूर्णांक32_t max_blocks;
	माप_प्रकार mmap_pages;

	काष्ठा mutex cmdr_lock;
	काष्ठा list_head qfull_queue;
	काष्ठा list_head पंचांगr_queue;

	uपूर्णांक32_t dbi_max;
	uपूर्णांक32_t dbi_thresh;
	अचिन्हित दीर्घ *data_biपंचांगap;
	काष्ठा xarray data_pages;
	uपूर्णांक32_t data_pages_per_blk;
	uपूर्णांक32_t data_blk_size;

	काष्ठा xarray commands;

	काष्ठा समयr_list cmd_समयr;
	अचिन्हित पूर्णांक cmd_समय_out;
	काष्ठा list_head inflight_queue;

	काष्ठा समयr_list qfull_समयr;
	पूर्णांक qfull_समय_out;

	काष्ठा list_head समयकरोut_entry;

	काष्ठा tcmu_nl_cmd curr_nl_cmd;

	अक्षर dev_config[TCMU_CONFIG_LEN];

	पूर्णांक nl_reply_supported;
पूर्ण;

#घोषणा TCMU_DEV(_se_dev) container_of(_se_dev, काष्ठा tcmu_dev, se_dev)

काष्ठा tcmu_cmd अणु
	काष्ठा se_cmd *se_cmd;
	काष्ठा tcmu_dev *tcmu_dev;
	काष्ठा list_head queue_entry;

	uपूर्णांक16_t cmd_id;

	/* Can't use se_cmd when cleaning up expired cmds, because अगर
	   cmd has been completed then accessing se_cmd is off limits */
	uपूर्णांक32_t dbi_cnt;
	uपूर्णांक32_t dbi_bidi_cnt;
	uपूर्णांक32_t dbi_cur;
	uपूर्णांक32_t *dbi;

	uपूर्णांक32_t data_len_bidi;

	अचिन्हित दीर्घ deadline;

#घोषणा TCMU_CMD_BIT_EXPIRED 0
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा tcmu_पंचांगr अणु
	काष्ठा list_head queue_entry;

	uपूर्णांक8_t पंचांगr_type;
	uपूर्णांक32_t पंचांगr_cmd_cnt;
	पूर्णांक16_t पंचांगr_cmd_ids[];
पूर्ण;

/*
 * To aव्योम dead lock the mutex lock order should always be:
 *
 * mutex_lock(&root_udev_mutex);
 * ...
 * mutex_lock(&tcmu_dev->cmdr_lock);
 * mutex_unlock(&tcmu_dev->cmdr_lock);
 * ...
 * mutex_unlock(&root_udev_mutex);
 */
अटल DEFINE_MUTEX(root_udev_mutex);
अटल LIST_HEAD(root_udev);

अटल DEFINE_SPINLOCK(समयd_out_udevs_lock);
अटल LIST_HEAD(समयd_out_udevs);

अटल काष्ठा kmem_cache *tcmu_cmd_cache;

अटल atomic_t global_page_count = ATOMIC_INIT(0);
अटल काष्ठा delayed_work tcmu_unmap_work;
अटल पूर्णांक tcmu_global_max_pages = TCMU_GLOBAL_MAX_PAGES_DEF;

अटल पूर्णांक tcmu_set_global_max_data_area(स्थिर अक्षर *str,
					 स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret, max_area_mb;

	ret = kstrtoपूर्णांक(str, 10, &max_area_mb);
	अगर (ret)
		वापस -EINVAL;

	अगर (max_area_mb <= 0) अणु
		pr_err("global_max_data_area must be larger than 0.\n");
		वापस -EINVAL;
	पूर्ण

	tcmu_global_max_pages = TCMU_MBS_TO_PAGES(max_area_mb);
	अगर (atomic_पढ़ो(&global_page_count) > tcmu_global_max_pages)
		schedule_delayed_work(&tcmu_unmap_work, 0);
	अन्यथा
		cancel_delayed_work_sync(&tcmu_unmap_work);

	वापस 0;
पूर्ण

अटल पूर्णांक tcmu_get_global_max_data_area(अक्षर *buffer,
					 स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%d\n", TCMU_PAGES_TO_MBS(tcmu_global_max_pages));
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops tcmu_global_max_data_area_op = अणु
	.set = tcmu_set_global_max_data_area,
	.get = tcmu_get_global_max_data_area,
पूर्ण;

module_param_cb(global_max_data_area_mb, &tcmu_global_max_data_area_op, शून्य,
		S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(global_max_data_area_mb,
		 "Max MBs allowed to be allocated to all the tcmu device's "
		 "data areas.");

अटल पूर्णांक tcmu_get_block_netlink(अक्षर *buffer,
				  स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%s\n", tcmu_netlink_blocked ?
		       "blocked" : "unblocked");
पूर्ण

अटल पूर्णांक tcmu_set_block_netlink(स्थिर अक्षर *str,
				  स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	u8 val;

	ret = kstrtou8(str, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val > 1) अणु
		pr_err("Invalid block netlink value %u\n", val);
		वापस -EINVAL;
	पूर्ण

	tcmu_netlink_blocked = val;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops tcmu_block_netlink_op = अणु
	.set = tcmu_set_block_netlink,
	.get = tcmu_get_block_netlink,
पूर्ण;

module_param_cb(block_netlink, &tcmu_block_netlink_op, शून्य, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(block_netlink, "Block new netlink commands.");

अटल पूर्णांक tcmu_fail_netlink_cmd(काष्ठा tcmu_nl_cmd *nl_cmd)
अणु
	काष्ठा tcmu_dev *udev = nl_cmd->udev;

	अगर (!tcmu_netlink_blocked) अणु
		pr_err("Could not reset device's netlink interface. Netlink is not blocked.\n");
		वापस -EBUSY;
	पूर्ण

	अगर (nl_cmd->cmd != TCMU_CMD_UNSPEC) अणु
		pr_debug("Aborting nl cmd %d on %s\n", nl_cmd->cmd, udev->name);
		nl_cmd->status = -EINTR;
		list_del(&nl_cmd->nl_list);
		complete(&nl_cmd->complete);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tcmu_set_reset_netlink(स्थिर अक्षर *str,
				  स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा tcmu_nl_cmd *nl_cmd, *पंचांगp_cmd;
	पूर्णांक ret;
	u8 val;

	ret = kstrtou8(str, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val != 1) अणु
		pr_err("Invalid reset netlink value %u\n", val);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&tcmu_nl_cmd_mutex);
	list_क्रम_each_entry_safe(nl_cmd, पंचांगp_cmd, &tcmu_nl_cmd_list, nl_list) अणु
		ret = tcmu_fail_netlink_cmd(nl_cmd);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&tcmu_nl_cmd_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops tcmu_reset_netlink_op = अणु
	.set = tcmu_set_reset_netlink,
पूर्ण;

module_param_cb(reset_netlink, &tcmu_reset_netlink_op, शून्य, S_IWUSR);
MODULE_PARM_DESC(reset_netlink, "Reset netlink commands.");

/* multicast group */
क्रमागत tcmu_multicast_groups अणु
	TCMU_MCGRP_CONFIG,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group tcmu_mcgrps[] = अणु
	[TCMU_MCGRP_CONFIG] = अणु .name = "config", पूर्ण,
पूर्ण;

अटल काष्ठा nla_policy tcmu_attr_policy[TCMU_ATTR_MAX+1] = अणु
	[TCMU_ATTR_DEVICE]	= अणु .type = NLA_STRING पूर्ण,
	[TCMU_ATTR_MINOR]	= अणु .type = NLA_U32 पूर्ण,
	[TCMU_ATTR_CMD_STATUS]	= अणु .type = NLA_S32 पूर्ण,
	[TCMU_ATTR_DEVICE_ID]	= अणु .type = NLA_U32 पूर्ण,
	[TCMU_ATTR_SUPP_KERN_CMD_REPLY] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक tcmu_genl_cmd_करोne(काष्ठा genl_info *info, पूर्णांक completed_cmd)
अणु
	काष्ठा tcmu_dev *udev = शून्य;
	काष्ठा tcmu_nl_cmd *nl_cmd;
	पूर्णांक dev_id, rc, ret = 0;

	अगर (!info->attrs[TCMU_ATTR_CMD_STATUS] ||
	    !info->attrs[TCMU_ATTR_DEVICE_ID]) अणु
		prपूर्णांकk(KERN_ERR "TCMU_ATTR_CMD_STATUS or TCMU_ATTR_DEVICE_ID not set, doing nothing\n");
		वापस -EINVAL;
        पूर्ण

	dev_id = nla_get_u32(info->attrs[TCMU_ATTR_DEVICE_ID]);
	rc = nla_get_s32(info->attrs[TCMU_ATTR_CMD_STATUS]);

	mutex_lock(&tcmu_nl_cmd_mutex);
	list_क्रम_each_entry(nl_cmd, &tcmu_nl_cmd_list, nl_list) अणु
		अगर (nl_cmd->udev->se_dev.dev_index == dev_id) अणु
			udev = nl_cmd->udev;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!udev) अणु
		pr_err("tcmu nl cmd %u/%d completion could not find device with dev id %u.\n",
		       completed_cmd, rc, dev_id);
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण
	list_del(&nl_cmd->nl_list);

	pr_debug("%s genl cmd done got id %d curr %d done %d rc %d stat %d\n",
		 udev->name, dev_id, nl_cmd->cmd, completed_cmd, rc,
		 nl_cmd->status);

	अगर (nl_cmd->cmd != completed_cmd) अणु
		pr_err("Mismatched commands on %s (Expecting reply for %d. Current %d).\n",
		       udev->name, completed_cmd, nl_cmd->cmd);
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	nl_cmd->status = rc;
	complete(&nl_cmd->complete);
unlock:
	mutex_unlock(&tcmu_nl_cmd_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक tcmu_genl_rm_dev_करोne(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस tcmu_genl_cmd_करोne(info, TCMU_CMD_REMOVED_DEVICE);
पूर्ण

अटल पूर्णांक tcmu_genl_add_dev_करोne(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस tcmu_genl_cmd_करोne(info, TCMU_CMD_ADDED_DEVICE);
पूर्ण

अटल पूर्णांक tcmu_genl_reconfig_dev_करोne(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	वापस tcmu_genl_cmd_करोne(info, TCMU_CMD_RECONFIG_DEVICE);
पूर्ण

अटल पूर्णांक tcmu_genl_set_features(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अगर (info->attrs[TCMU_ATTR_SUPP_KERN_CMD_REPLY]) अणु
		tcmu_kern_cmd_reply_supported  =
			nla_get_u8(info->attrs[TCMU_ATTR_SUPP_KERN_CMD_REPLY]);
		prपूर्णांकk(KERN_INFO "tcmu daemon: command reply support %u.\n",
		       tcmu_kern_cmd_reply_supported);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops tcmu_genl_ops[] = अणु
	अणु
		.cmd	= TCMU_CMD_SET_FEATURES,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= tcmu_genl_set_features,
	पूर्ण,
	अणु
		.cmd	= TCMU_CMD_ADDED_DEVICE_DONE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= tcmu_genl_add_dev_करोne,
	पूर्ण,
	अणु
		.cmd	= TCMU_CMD_REMOVED_DEVICE_DONE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= tcmu_genl_rm_dev_करोne,
	पूर्ण,
	अणु
		.cmd	= TCMU_CMD_RECONFIG_DEVICE_DONE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags	= GENL_ADMIN_PERM,
		.करोit	= tcmu_genl_reconfig_dev_करोne,
	पूर्ण,
पूर्ण;

/* Our generic netlink family */
अटल काष्ठा genl_family tcmu_genl_family __ro_after_init = अणु
	.module = THIS_MODULE,
	.hdrsize = 0,
	.name = "TCM-USER",
	.version = 2,
	.maxattr = TCMU_ATTR_MAX,
	.policy = tcmu_attr_policy,
	.mcgrps = tcmu_mcgrps,
	.n_mcgrps = ARRAY_SIZE(tcmu_mcgrps),
	.netnsok = true,
	.small_ops = tcmu_genl_ops,
	.n_small_ops = ARRAY_SIZE(tcmu_genl_ops),
पूर्ण;

#घोषणा tcmu_cmd_set_dbi_cur(cmd, index) ((cmd)->dbi_cur = (index))
#घोषणा tcmu_cmd_reset_dbi_cur(cmd) tcmu_cmd_set_dbi_cur(cmd, 0)
#घोषणा tcmu_cmd_set_dbi(cmd, index) ((cmd)->dbi[(cmd)->dbi_cur++] = (index))
#घोषणा tcmu_cmd_get_dbi(cmd) ((cmd)->dbi[(cmd)->dbi_cur++])

अटल व्योम tcmu_cmd_मुक्त_data(काष्ठा tcmu_cmd *tcmu_cmd, uपूर्णांक32_t len)
अणु
	काष्ठा tcmu_dev *udev = tcmu_cmd->tcmu_dev;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < len; i++)
		clear_bit(tcmu_cmd->dbi[i], udev->data_biपंचांगap);
पूर्ण

अटल अंतरभूत पूर्णांक tcmu_get_empty_block(काष्ठा tcmu_dev *udev,
				       काष्ठा tcmu_cmd *tcmu_cmd,
				       पूर्णांक prev_dbi, पूर्णांक length, पूर्णांक *iov_cnt)
अणु
	XA_STATE(xas, &udev->data_pages, 0);
	काष्ठा page *page;
	पूर्णांक i, cnt, dbi, dpi;
	पूर्णांक page_cnt = DIV_ROUND_UP(length, PAGE_SIZE);

	dbi = find_first_zero_bit(udev->data_biपंचांगap, udev->dbi_thresh);
	अगर (dbi == udev->dbi_thresh)
		वापस -1;

	dpi = dbi * udev->data_pages_per_blk;
	/* Count the number of alपढ़ोy allocated pages */
	xas_set(&xas, dpi);
	rcu_पढ़ो_lock();
	क्रम (cnt = 0; xas_next(&xas) && cnt < page_cnt;)
		cnt++;
	rcu_पढ़ो_unlock();

	क्रम (i = cnt; i < page_cnt; i++) अणु
		/* try to get new page from the mm */
		page = alloc_page(GFP_NOIO);
		अगर (!page)
			अवरोध;

		अगर (xa_store(&udev->data_pages, dpi + i, page, GFP_NOIO)) अणु
			__मुक्त_page(page);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (atomic_add_वापस(i - cnt, &global_page_count) >
			      tcmu_global_max_pages)
		schedule_delayed_work(&tcmu_unmap_work, 0);

	अगर (i && dbi > udev->dbi_max)
		udev->dbi_max = dbi;

	set_bit(dbi, udev->data_biपंचांगap);
	tcmu_cmd_set_dbi(tcmu_cmd, dbi);

	अगर (dbi != prev_dbi + 1)
		*iov_cnt += 1;

	वापस i == page_cnt ? dbi : -1;
पूर्ण

अटल पूर्णांक tcmu_get_empty_blocks(काष्ठा tcmu_dev *udev,
				 काष्ठा tcmu_cmd *tcmu_cmd, पूर्णांक length)
अणु
	/* start value of dbi + 1 must not be a valid dbi */
	पूर्णांक dbi = -2;
	पूर्णांक blk_data_len, iov_cnt = 0;
	uपूर्णांक32_t blk_size = udev->data_blk_size;

	क्रम (; length > 0; length -= blk_size) अणु
		blk_data_len = min_t(uपूर्णांक32_t, length, blk_size);
		dbi = tcmu_get_empty_block(udev, tcmu_cmd, dbi, blk_data_len,
					   &iov_cnt);
		अगर (dbi < 0)
			वापस -1;
	पूर्ण
	वापस iov_cnt;
पूर्ण

अटल अंतरभूत व्योम tcmu_मुक्त_cmd(काष्ठा tcmu_cmd *tcmu_cmd)
अणु
	kमुक्त(tcmu_cmd->dbi);
	kmem_cache_मुक्त(tcmu_cmd_cache, tcmu_cmd);
पूर्ण

अटल अंतरभूत व्योम tcmu_cmd_set_block_cnts(काष्ठा tcmu_cmd *cmd)
अणु
	पूर्णांक i, len;
	काष्ठा se_cmd *se_cmd = cmd->se_cmd;
	uपूर्णांक32_t blk_size = cmd->tcmu_dev->data_blk_size;

	cmd->dbi_cnt = DIV_ROUND_UP(se_cmd->data_length, blk_size);

	अगर (se_cmd->se_cmd_flags & SCF_BIDI) अणु
		BUG_ON(!(se_cmd->t_bidi_data_sg && se_cmd->t_bidi_data_nents));
		क्रम (i = 0, len = 0; i < se_cmd->t_bidi_data_nents; i++)
			len += se_cmd->t_bidi_data_sg[i].length;
		cmd->dbi_bidi_cnt = DIV_ROUND_UP(len, blk_size);
		cmd->dbi_cnt += cmd->dbi_bidi_cnt;
		cmd->data_len_bidi = len;
	पूर्ण
पूर्ण

अटल पूर्णांक new_block_to_iov(काष्ठा tcmu_dev *udev, काष्ठा tcmu_cmd *cmd,
			    काष्ठा iovec **iov, पूर्णांक prev_dbi, पूर्णांक len)
अणु
	/* Get the next dbi */
	पूर्णांक dbi = tcmu_cmd_get_dbi(cmd);

	/* Do not add more than udev->data_blk_size to iov */
	len = min_t(पूर्णांक,  len, udev->data_blk_size);

	/*
	 * The following code will gather and map the blocks to the same iovec
	 * when the blocks are all next to each other.
	 */
	अगर (dbi != prev_dbi + 1) अणु
		/* dbi is not next to previous dbi, so start new iov */
		अगर (prev_dbi >= 0)
			(*iov)++;
		/* ग_लिखो offset relative to mb_addr */
		(*iov)->iov_base = (व्योम __user *)
				   (udev->data_off + dbi * udev->data_blk_size);
	पूर्ण
	(*iov)->iov_len += len;

	वापस dbi;
पूर्ण

अटल व्योम tcmu_setup_iovs(काष्ठा tcmu_dev *udev, काष्ठा tcmu_cmd *cmd,
			    काष्ठा iovec **iov, पूर्णांक data_length)
अणु
	/* start value of dbi + 1 must not be a valid dbi */
	पूर्णांक dbi = -2;

	/* We prepare the IOVs क्रम DMA_FROM_DEVICE transfer direction */
	क्रम (; data_length > 0; data_length -= udev->data_blk_size)
		dbi = new_block_to_iov(udev, cmd, iov, dbi, data_length);
पूर्ण

अटल काष्ठा tcmu_cmd *tcmu_alloc_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा se_device *se_dev = se_cmd->se_dev;
	काष्ठा tcmu_dev *udev = TCMU_DEV(se_dev);
	काष्ठा tcmu_cmd *tcmu_cmd;

	tcmu_cmd = kmem_cache_zalloc(tcmu_cmd_cache, GFP_NOIO);
	अगर (!tcmu_cmd)
		वापस शून्य;

	INIT_LIST_HEAD(&tcmu_cmd->queue_entry);
	tcmu_cmd->se_cmd = se_cmd;
	tcmu_cmd->tcmu_dev = udev;

	tcmu_cmd_set_block_cnts(tcmu_cmd);
	tcmu_cmd->dbi = kसुस्मृति(tcmu_cmd->dbi_cnt, माप(uपूर्णांक32_t),
				GFP_NOIO);
	अगर (!tcmu_cmd->dbi) अणु
		kmem_cache_मुक्त(tcmu_cmd_cache, tcmu_cmd);
		वापस शून्य;
	पूर्ण

	वापस tcmu_cmd;
पूर्ण

अटल अंतरभूत व्योम tcmu_flush_dcache_range(व्योम *vaddr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ offset = offset_in_page(vaddr);
	व्योम *start = vaddr - offset;

	size = round_up(size+offset, PAGE_SIZE);

	जबतक (size) अणु
		flush_dcache_page(vदो_स्मृति_to_page(start));
		start += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण
पूर्ण

/*
 * Some ring helper functions. We करोn't assume size is a घातer of 2 so
 * we can't use circ_buf.h.
 */
अटल अंतरभूत माप_प्रकार spc_used(माप_प्रकार head, माप_प्रकार tail, माप_प्रकार size)
अणु
	पूर्णांक dअगरf = head - tail;

	अगर (dअगरf >= 0)
		वापस dअगरf;
	अन्यथा
		वापस size + dअगरf;
पूर्ण

अटल अंतरभूत माप_प्रकार spc_मुक्त(माप_प्रकार head, माप_प्रकार tail, माप_प्रकार size)
अणु
	/* Keep 1 byte unused or we can't tell full from empty */
	वापस (size - spc_used(head, tail, size) - 1);
पूर्ण

अटल अंतरभूत माप_प्रकार head_to_end(माप_प्रकार head, माप_प्रकार size)
अणु
	वापस size - head;
पूर्ण

#घोषणा UPDATE_HEAD(head, used, size) smp_store_release(&head, ((head % size) + used) % size)

#घोषणा TCMU_SG_TO_DATA_AREA 1
#घोषणा TCMU_DATA_AREA_TO_SG 2

अटल अंतरभूत व्योम tcmu_copy_data(काष्ठा tcmu_dev *udev,
				  काष्ठा tcmu_cmd *tcmu_cmd, uपूर्णांक32_t direction,
				  काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sg_nents,
				  काष्ठा iovec **iov, माप_प्रकार data_len)
अणु
	/* start value of dbi + 1 must not be a valid dbi */
	पूर्णांक dbi = -2;
	माप_प्रकार page_reमुख्यing, cp_len;
	पूर्णांक page_cnt, page_inx, dpi;
	काष्ठा sg_mapping_iter sg_iter;
	अचिन्हित पूर्णांक sg_flags;
	काष्ठा page *page;
	व्योम *data_page_start, *data_addr;

	अगर (direction == TCMU_SG_TO_DATA_AREA)
		sg_flags = SG_MITER_ATOMIC | SG_MITER_FROM_SG;
	अन्यथा
		sg_flags = SG_MITER_ATOMIC | SG_MITER_TO_SG;
	sg_miter_start(&sg_iter, sg, sg_nents, sg_flags);

	जबतक (data_len) अणु
		अगर (direction == TCMU_SG_TO_DATA_AREA)
			dbi = new_block_to_iov(udev, tcmu_cmd, iov, dbi,
					       data_len);
		अन्यथा
			dbi = tcmu_cmd_get_dbi(tcmu_cmd);

		page_cnt = DIV_ROUND_UP(data_len, PAGE_SIZE);
		अगर (page_cnt > udev->data_pages_per_blk)
			page_cnt = udev->data_pages_per_blk;

		dpi = dbi * udev->data_pages_per_blk;
		क्रम (page_inx = 0; page_inx < page_cnt && data_len;
		     page_inx++, dpi++) अणु
			page = xa_load(&udev->data_pages, dpi);

			अगर (direction == TCMU_DATA_AREA_TO_SG)
				flush_dcache_page(page);
			data_page_start = kmap_atomic(page);
			page_reमुख्यing = PAGE_SIZE;

			जबतक (page_reमुख्यing && data_len) अणु
				अगर (!sg_miter_next(&sg_iter)) अणु
					/* set length to 0 to पात outer loop */
					data_len = 0;
					pr_debug("%s: aborting data copy due to exhausted sg_list\n",
						 __func__);
					अवरोध;
				पूर्ण
				cp_len = min3(sg_iter.length, page_reमुख्यing,
					      data_len);

				data_addr = data_page_start +
					    PAGE_SIZE - page_reमुख्यing;
				अगर (direction == TCMU_SG_TO_DATA_AREA)
					स_नकल(data_addr, sg_iter.addr, cp_len);
				अन्यथा
					स_नकल(sg_iter.addr, data_addr, cp_len);

				data_len -= cp_len;
				page_reमुख्यing -= cp_len;
				sg_iter.consumed = cp_len;
			पूर्ण
			sg_miter_stop(&sg_iter);

			kunmap_atomic(data_page_start);
			अगर (direction == TCMU_SG_TO_DATA_AREA)
				flush_dcache_page(page);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम scatter_data_area(काष्ठा tcmu_dev *udev, काष्ठा tcmu_cmd *tcmu_cmd,
			      काष्ठा iovec **iov)
अणु
	काष्ठा se_cmd *se_cmd = tcmu_cmd->se_cmd;

	tcmu_copy_data(udev, tcmu_cmd, TCMU_SG_TO_DATA_AREA, se_cmd->t_data_sg,
		       se_cmd->t_data_nents, iov, se_cmd->data_length);
पूर्ण

अटल व्योम gather_data_area(काष्ठा tcmu_dev *udev, काष्ठा tcmu_cmd *tcmu_cmd,
			     bool bidi, uपूर्णांक32_t पढ़ो_len)
अणु
	काष्ठा se_cmd *se_cmd = tcmu_cmd->se_cmd;
	काष्ठा scatterlist *data_sg;
	अचिन्हित पूर्णांक data_nents;

	अगर (!bidi) अणु
		data_sg = se_cmd->t_data_sg;
		data_nents = se_cmd->t_data_nents;
	पूर्ण अन्यथा अणु
		/*
		 * For bidi हाल, the first count blocks are क्रम Data-Out
		 * buffer blocks, and beक्रमe gathering the Data-In buffer
		 * the Data-Out buffer blocks should be skipped.
		 */
		tcmu_cmd_set_dbi_cur(tcmu_cmd,
				     tcmu_cmd->dbi_cnt - tcmu_cmd->dbi_bidi_cnt);

		data_sg = se_cmd->t_bidi_data_sg;
		data_nents = se_cmd->t_bidi_data_nents;
	पूर्ण

	tcmu_copy_data(udev, tcmu_cmd, TCMU_DATA_AREA_TO_SG, data_sg,
		       data_nents, शून्य, पढ़ो_len);
पूर्ण

अटल अंतरभूत माप_प्रकार spc_biपंचांगap_मुक्त(अचिन्हित दीर्घ *biपंचांगap, uपूर्णांक32_t thresh)
अणु
	वापस thresh - biपंचांगap_weight(biपंचांगap, thresh);
पूर्ण

/*
 * We can't queue a command until we have space available on the cmd ring.
 *
 * Called with ring lock held.
 */
अटल bool is_ring_space_avail(काष्ठा tcmu_dev *udev, माप_प्रकार cmd_size)
अणु
	काष्ठा tcmu_mailbox *mb = udev->mb_addr;
	माप_प्रकार space, cmd_needed;
	u32 cmd_head;

	tcmu_flush_dcache_range(mb, माप(*mb));

	cmd_head = mb->cmd_head % udev->cmdr_size; /* UAM */

	/*
	 * If cmd end-of-ring space is too small then we need space क्रम a NOP plus
	 * original cmd - cmds are पूर्णांकernally contiguous.
	 */
	अगर (head_to_end(cmd_head, udev->cmdr_size) >= cmd_size)
		cmd_needed = cmd_size;
	अन्यथा
		cmd_needed = cmd_size + head_to_end(cmd_head, udev->cmdr_size);

	space = spc_मुक्त(cmd_head, udev->cmdr_last_cleaned, udev->cmdr_size);
	अगर (space < cmd_needed) अणु
		pr_debug("no cmd space: %u %u %u\n", cmd_head,
		       udev->cmdr_last_cleaned, udev->cmdr_size);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * We have to allocate data buffers beक्रमe we can queue a command.
 * Returns -1 on error (not enough space) or number of needed iovs on success
 *
 * Called with ring lock held.
 */
अटल पूर्णांक tcmu_alloc_data_space(काष्ठा tcmu_dev *udev, काष्ठा tcmu_cmd *cmd,
				  पूर्णांक *iov_bidi_cnt)
अणु
	पूर्णांक space, iov_cnt = 0, ret = 0;

	अगर (!cmd->dbi_cnt)
		जाओ wr_iov_cnts;

	/* try to check and get the data blocks as needed */
	space = spc_biपंचांगap_मुक्त(udev->data_biपंचांगap, udev->dbi_thresh);
	अगर (space < cmd->dbi_cnt) अणु
		अचिन्हित दीर्घ blocks_left =
				(udev->max_blocks - udev->dbi_thresh) + space;

		अगर (blocks_left < cmd->dbi_cnt) अणु
			pr_debug("no data space: only %lu available, but ask for %u\n",
					blocks_left * udev->data_blk_size,
					cmd->dbi_cnt * udev->data_blk_size);
			वापस -1;
		पूर्ण

		udev->dbi_thresh += cmd->dbi_cnt;
		अगर (udev->dbi_thresh > udev->max_blocks)
			udev->dbi_thresh = udev->max_blocks;
	पूर्ण

	iov_cnt = tcmu_get_empty_blocks(udev, cmd, cmd->se_cmd->data_length);
	अगर (iov_cnt < 0)
		वापस -1;

	अगर (cmd->dbi_bidi_cnt) अणु
		ret = tcmu_get_empty_blocks(udev, cmd, cmd->data_len_bidi);
		अगर (ret < 0)
			वापस -1;
	पूर्ण
wr_iov_cnts:
	*iov_bidi_cnt = ret;
	वापस iov_cnt + ret;
पूर्ण

अटल अंतरभूत माप_प्रकार tcmu_cmd_get_base_cmd_size(माप_प्रकार iov_cnt)
अणु
	वापस max(दुरत्व(काष्ठा tcmu_cmd_entry, req.iov[iov_cnt]),
			माप(काष्ठा tcmu_cmd_entry));
पूर्ण

अटल अंतरभूत माप_प्रकार tcmu_cmd_get_cmd_size(काष्ठा tcmu_cmd *tcmu_cmd,
					   माप_प्रकार base_command_size)
अणु
	काष्ठा se_cmd *se_cmd = tcmu_cmd->se_cmd;
	माप_प्रकार command_size;

	command_size = base_command_size +
		round_up(scsi_command_size(se_cmd->t_task_cdb),
				TCMU_OP_ALIGN_SIZE);

	WARN_ON(command_size & (TCMU_OP_ALIGN_SIZE-1));

	वापस command_size;
पूर्ण

अटल व्योम tcmu_setup_cmd_समयr(काष्ठा tcmu_cmd *tcmu_cmd, अचिन्हित पूर्णांक पंचांगo,
				 काष्ठा समयr_list *समयr)
अणु
	अगर (!पंचांगo)
		वापस;

	tcmu_cmd->deadline = round_jअगरfies_up(jअगरfies + msecs_to_jअगरfies(पंचांगo));
	अगर (!समयr_pending(समयr))
		mod_समयr(समयr, tcmu_cmd->deadline);

	pr_debug("Timeout set up for cmd %p, dev = %s, tmo = %lu\n", tcmu_cmd,
		 tcmu_cmd->tcmu_dev->name, पंचांगo / MSEC_PER_SEC);
पूर्ण

अटल पूर्णांक add_to_qfull_queue(काष्ठा tcmu_cmd *tcmu_cmd)
अणु
	काष्ठा tcmu_dev *udev = tcmu_cmd->tcmu_dev;
	अचिन्हित पूर्णांक पंचांगo;

	/*
	 * For backwards compat अगर qfull_समय_out is not set use
	 * cmd_समय_out and अगर that's not set use the शेष समय out.
	 */
	अगर (!udev->qfull_समय_out)
		वापस -ETIMEDOUT;
	अन्यथा अगर (udev->qfull_समय_out > 0)
		पंचांगo = udev->qfull_समय_out;
	अन्यथा अगर (udev->cmd_समय_out)
		पंचांगo = udev->cmd_समय_out;
	अन्यथा
		पंचांगo = TCMU_TIME_OUT;

	tcmu_setup_cmd_समयr(tcmu_cmd, पंचांगo, &udev->qfull_समयr);

	list_add_tail(&tcmu_cmd->queue_entry, &udev->qfull_queue);
	pr_debug("adding cmd %p on dev %s to ring space wait queue\n",
		 tcmu_cmd, udev->name);
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t ring_insert_padding(काष्ठा tcmu_dev *udev, माप_प्रकार cmd_size)
अणु
	काष्ठा tcmu_cmd_entry_hdr *hdr;
	काष्ठा tcmu_mailbox *mb = udev->mb_addr;
	uपूर्णांक32_t cmd_head = mb->cmd_head % udev->cmdr_size; /* UAM */

	/* Insert a PAD अगर end-of-ring space is too small */
	अगर (head_to_end(cmd_head, udev->cmdr_size) < cmd_size) अणु
		माप_प्रकार pad_size = head_to_end(cmd_head, udev->cmdr_size);

		hdr = udev->cmdr + cmd_head;
		tcmu_hdr_set_op(&hdr->len_op, TCMU_OP_PAD);
		tcmu_hdr_set_len(&hdr->len_op, pad_size);
		hdr->cmd_id = 0; /* not used क्रम PAD */
		hdr->kflags = 0;
		hdr->uflags = 0;
		tcmu_flush_dcache_range(hdr, माप(*hdr));

		UPDATE_HEAD(mb->cmd_head, pad_size, udev->cmdr_size);
		tcmu_flush_dcache_range(mb, माप(*mb));

		cmd_head = mb->cmd_head % udev->cmdr_size; /* UAM */
		WARN_ON(cmd_head != 0);
	पूर्ण

	वापस cmd_head;
पूर्ण

अटल व्योम tcmu_unplug_device(काष्ठा se_dev_plug *se_plug)
अणु
	काष्ठा se_device *se_dev = se_plug->se_dev;
	काष्ठा tcmu_dev *udev = TCMU_DEV(se_dev);

	clear_bit(TCM_DEV_BIT_PLUGGED, &udev->flags);
	uio_event_notअगरy(&udev->uio_info);
पूर्ण

अटल काष्ठा se_dev_plug *tcmu_plug_device(काष्ठा se_device *se_dev)
अणु
	काष्ठा tcmu_dev *udev = TCMU_DEV(se_dev);

	अगर (!test_and_set_bit(TCM_DEV_BIT_PLUGGED, &udev->flags))
		वापस &udev->se_plug;

	वापस शून्य;
पूर्ण

/**
 * queue_cmd_ring - queue cmd to ring or पूर्णांकernally
 * @tcmu_cmd: cmd to queue
 * @scsi_err: TCM error code अगर failure (-1) वापसed.
 *
 * Returns:
 * -1 we cannot queue पूर्णांकernally or to the ring.
 *  0 success
 *  1 पूर्णांकernally queued to रुको क्रम ring memory to मुक्त.
 */
अटल पूर्णांक queue_cmd_ring(काष्ठा tcmu_cmd *tcmu_cmd, sense_reason_t *scsi_err)
अणु
	काष्ठा tcmu_dev *udev = tcmu_cmd->tcmu_dev;
	काष्ठा se_cmd *se_cmd = tcmu_cmd->se_cmd;
	माप_प्रकार base_command_size, command_size;
	काष्ठा tcmu_mailbox *mb = udev->mb_addr;
	काष्ठा tcmu_cmd_entry *entry;
	काष्ठा iovec *iov;
	पूर्णांक iov_cnt, iov_bidi_cnt;
	uपूर्णांक32_t cmd_id, cmd_head;
	uपूर्णांक64_t cdb_off;
	uपूर्णांक32_t blk_size = udev->data_blk_size;
	/* size of data buffer needed */
	माप_प्रकार data_length = (माप_प्रकार)tcmu_cmd->dbi_cnt * blk_size;

	*scsi_err = TCM_NO_SENSE;

	अगर (test_bit(TCMU_DEV_BIT_BLOCKED, &udev->flags)) अणु
		*scsi_err = TCM_LUN_BUSY;
		वापस -1;
	पूर्ण

	अगर (test_bit(TCMU_DEV_BIT_BROKEN, &udev->flags)) अणु
		*scsi_err = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		वापस -1;
	पूर्ण

	अगर (!list_empty(&udev->qfull_queue))
		जाओ queue;

	अगर (data_length > (माप_प्रकार)udev->max_blocks * blk_size) अणु
		pr_warn("TCMU: Request of size %zu is too big for %zu data area\n",
			data_length, (माप_प्रकार)udev->max_blocks * blk_size);
		*scsi_err = TCM_INVALID_CDB_FIELD;
		वापस -1;
	पूर्ण

	iov_cnt = tcmu_alloc_data_space(udev, tcmu_cmd, &iov_bidi_cnt);
	अगर (iov_cnt < 0)
		जाओ मुक्त_and_queue;

	/*
	 * Must be a certain minimum size क्रम response sense info, but
	 * also may be larger अगर the iov array is large.
	 */
	base_command_size = tcmu_cmd_get_base_cmd_size(iov_cnt);
	command_size = tcmu_cmd_get_cmd_size(tcmu_cmd, base_command_size);

	अगर (command_size > (udev->cmdr_size / 2)) अणु
		pr_warn("TCMU: Request of size %zu is too big for %u cmd ring\n",
			command_size, udev->cmdr_size);
		tcmu_cmd_मुक्त_data(tcmu_cmd, tcmu_cmd->dbi_cur);
		*scsi_err = TCM_INVALID_CDB_FIELD;
		वापस -1;
	पूर्ण

	अगर (!is_ring_space_avail(udev, command_size))
		/*
		 * Don't leave commands partially setup because the unmap
		 * thपढ़ो might need the blocks to make क्रमward progress.
		 */
		जाओ मुक्त_and_queue;

	अगर (xa_alloc(&udev->commands, &cmd_id, tcmu_cmd, XA_LIMIT(1, 0xffff),
		     GFP_NOWAIT) < 0) अणु
		pr_err("tcmu: Could not allocate cmd id.\n");

		tcmu_cmd_मुक्त_data(tcmu_cmd, tcmu_cmd->dbi_cnt);
		*scsi_err = TCM_OUT_OF_RESOURCES;
		वापस -1;
	पूर्ण
	tcmu_cmd->cmd_id = cmd_id;

	pr_debug("allocated cmd id %u for cmd %p dev %s\n", tcmu_cmd->cmd_id,
		 tcmu_cmd, udev->name);

	cmd_head = ring_insert_padding(udev, command_size);

	entry = udev->cmdr + cmd_head;
	स_रखो(entry, 0, command_size);
	tcmu_hdr_set_op(&entry->hdr.len_op, TCMU_OP_CMD);

	/* prepare iov list and copy data to data area अगर necessary */
	tcmu_cmd_reset_dbi_cur(tcmu_cmd);
	iov = &entry->req.iov[0];

	अगर (se_cmd->data_direction == DMA_TO_DEVICE ||
	    se_cmd->se_cmd_flags & SCF_BIDI)
		scatter_data_area(udev, tcmu_cmd, &iov);
	अन्यथा
		tcmu_setup_iovs(udev, tcmu_cmd, &iov, se_cmd->data_length);

	entry->req.iov_cnt = iov_cnt - iov_bidi_cnt;

	/* Handle BIDI commands */
	अगर (se_cmd->se_cmd_flags & SCF_BIDI) अणु
		iov++;
		tcmu_setup_iovs(udev, tcmu_cmd, &iov, tcmu_cmd->data_len_bidi);
		entry->req.iov_bidi_cnt = iov_bidi_cnt;
	पूर्ण

	tcmu_setup_cmd_समयr(tcmu_cmd, udev->cmd_समय_out, &udev->cmd_समयr);

	entry->hdr.cmd_id = tcmu_cmd->cmd_id;

	tcmu_hdr_set_len(&entry->hdr.len_op, command_size);

	/* All offsets relative to mb_addr, not start of entry! */
	cdb_off = CMDR_OFF + cmd_head + base_command_size;
	स_नकल((व्योम *) mb + cdb_off, se_cmd->t_task_cdb, scsi_command_size(se_cmd->t_task_cdb));
	entry->req.cdb_off = cdb_off;
	tcmu_flush_dcache_range(entry, command_size);

	UPDATE_HEAD(mb->cmd_head, command_size, udev->cmdr_size);
	tcmu_flush_dcache_range(mb, माप(*mb));

	list_add_tail(&tcmu_cmd->queue_entry, &udev->inflight_queue);

	अगर (!test_bit(TCM_DEV_BIT_PLUGGED, &udev->flags))
		uio_event_notअगरy(&udev->uio_info);

	वापस 0;

मुक्त_and_queue:
	tcmu_cmd_मुक्त_data(tcmu_cmd, tcmu_cmd->dbi_cur);
	tcmu_cmd_reset_dbi_cur(tcmu_cmd);

queue:
	अगर (add_to_qfull_queue(tcmu_cmd)) अणु
		*scsi_err = TCM_OUT_OF_RESOURCES;
		वापस -1;
	पूर्ण

	वापस 1;
पूर्ण

/**
 * queue_पंचांगr_ring - queue पंचांगr info to ring or पूर्णांकernally
 * @udev: related tcmu_dev
 * @पंचांगr: tcmu_पंचांगr containing पंचांगr info to queue
 *
 * Returns:
 *  0 success
 *  1 पूर्णांकernally queued to रुको क्रम ring memory to मुक्त.
 */
अटल पूर्णांक
queue_पंचांगr_ring(काष्ठा tcmu_dev *udev, काष्ठा tcmu_पंचांगr *पंचांगr)
अणु
	काष्ठा tcmu_पंचांगr_entry *entry;
	पूर्णांक cmd_size;
	पूर्णांक id_list_sz;
	काष्ठा tcmu_mailbox *mb = udev->mb_addr;
	uपूर्णांक32_t cmd_head;

	अगर (test_bit(TCMU_DEV_BIT_BROKEN, &udev->flags))
		जाओ out_मुक्त;

	id_list_sz = माप(पंचांगr->पंचांगr_cmd_ids[0]) * पंचांगr->पंचांगr_cmd_cnt;
	cmd_size = round_up(माप(*entry) + id_list_sz, TCMU_OP_ALIGN_SIZE);

	अगर (!list_empty(&udev->पंचांगr_queue) ||
	    !is_ring_space_avail(udev, cmd_size)) अणु
		list_add_tail(&पंचांगr->queue_entry, &udev->पंचांगr_queue);
		pr_debug("adding tmr %p on dev %s to TMR ring space wait queue\n",
			 पंचांगr, udev->name);
		वापस 1;
	पूर्ण

	cmd_head = ring_insert_padding(udev, cmd_size);

	entry = udev->cmdr + cmd_head;
	स_रखो(entry, 0, cmd_size);
	tcmu_hdr_set_op(&entry->hdr.len_op, TCMU_OP_TMR);
	tcmu_hdr_set_len(&entry->hdr.len_op, cmd_size);
	entry->पंचांगr_type = पंचांगr->पंचांगr_type;
	entry->cmd_cnt = पंचांगr->पंचांगr_cmd_cnt;
	स_नकल(&entry->cmd_ids[0], &पंचांगr->पंचांगr_cmd_ids[0], id_list_sz);
	tcmu_flush_dcache_range(entry, cmd_size);

	UPDATE_HEAD(mb->cmd_head, cmd_size, udev->cmdr_size);
	tcmu_flush_dcache_range(mb, माप(*mb));

	uio_event_notअगरy(&udev->uio_info);

out_मुक्त:
	kमुक्त(पंचांगr);

	वापस 0;
पूर्ण

अटल sense_reason_t
tcmu_queue_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा se_device *se_dev = se_cmd->se_dev;
	काष्ठा tcmu_dev *udev = TCMU_DEV(se_dev);
	काष्ठा tcmu_cmd *tcmu_cmd;
	sense_reason_t scsi_ret = TCM_CHECK_CONDITION_ABORT_CMD;
	पूर्णांक ret = -1;

	tcmu_cmd = tcmu_alloc_cmd(se_cmd);
	अगर (!tcmu_cmd)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	mutex_lock(&udev->cmdr_lock);
	अगर (!(se_cmd->transport_state & CMD_T_ABORTED))
		ret = queue_cmd_ring(tcmu_cmd, &scsi_ret);
	अगर (ret < 0)
		tcmu_मुक्त_cmd(tcmu_cmd);
	अन्यथा
		se_cmd->priv = tcmu_cmd;
	mutex_unlock(&udev->cmdr_lock);
	वापस scsi_ret;
पूर्ण

अटल व्योम tcmu_set_next_deadline(काष्ठा list_head *queue,
				   काष्ठा समयr_list *समयr)
अणु
	काष्ठा tcmu_cmd *cmd;

	अगर (!list_empty(queue)) अणु
		cmd = list_first_entry(queue, काष्ठा tcmu_cmd, queue_entry);
		mod_समयr(समयr, cmd->deadline);
	पूर्ण अन्यथा
		del_समयr(समयr);
पूर्ण

अटल पूर्णांक
tcmu_पंचांगr_type(क्रमागत tcm_पंचांगreq_table पंचांगf)
अणु
	चयन (पंचांगf) अणु
	हाल TMR_ABORT_TASK:		वापस TCMU_TMR_ABORT_TASK;
	हाल TMR_ABORT_TASK_SET:	वापस TCMU_TMR_ABORT_TASK_SET;
	हाल TMR_CLEAR_ACA:		वापस TCMU_TMR_CLEAR_ACA;
	हाल TMR_CLEAR_TASK_SET:	वापस TCMU_TMR_CLEAR_TASK_SET;
	हाल TMR_LUN_RESET:		वापस TCMU_TMR_LUN_RESET;
	हाल TMR_TARGET_WARM_RESET:	वापस TCMU_TMR_TARGET_WARM_RESET;
	हाल TMR_TARGET_COLD_RESET:	वापस TCMU_TMR_TARGET_COLD_RESET;
	हाल TMR_LUN_RESET_PRO:		वापस TCMU_TMR_LUN_RESET_PRO;
	शेष:			वापस TCMU_TMR_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम
tcmu_पंचांगr_notअगरy(काष्ठा se_device *se_dev, क्रमागत tcm_पंचांगreq_table पंचांगf,
		काष्ठा list_head *cmd_list)
अणु
	पूर्णांक i = 0, cmd_cnt = 0;
	bool unqueued = false;
	uपूर्णांक16_t *cmd_ids = शून्य;
	काष्ठा tcmu_cmd *cmd;
	काष्ठा se_cmd *se_cmd;
	काष्ठा tcmu_पंचांगr *पंचांगr;
	काष्ठा tcmu_dev *udev = TCMU_DEV(se_dev);

	mutex_lock(&udev->cmdr_lock);

	/* First we check क्रम पातed commands in qfull_queue */
	list_क्रम_each_entry(se_cmd, cmd_list, state_list) अणु
		i++;
		अगर (!se_cmd->priv)
			जारी;
		cmd = se_cmd->priv;
		/* Commands on qfull queue have no id yet */
		अगर (cmd->cmd_id) अणु
			cmd_cnt++;
			जारी;
		पूर्ण
		pr_debug("Removing aborted command %p from queue on dev %s.\n",
			 cmd, udev->name);

		list_del_init(&cmd->queue_entry);
		tcmu_मुक्त_cmd(cmd);
		se_cmd->priv = शून्य;
		target_complete_cmd(se_cmd, SAM_STAT_TASK_ABORTED);
		unqueued = true;
	पूर्ण
	अगर (unqueued)
		tcmu_set_next_deadline(&udev->qfull_queue, &udev->qfull_समयr);

	अगर (!test_bit(TCMU_DEV_BIT_TMR_NOTIFY, &udev->flags))
		जाओ unlock;

	pr_debug("TMR event %d on dev %s, aborted cmds %d, afflicted cmd_ids %d\n",
		 tcmu_पंचांगr_type(पंचांगf), udev->name, i, cmd_cnt);

	पंचांगr = kदो_स्मृति(माप(*पंचांगr) + cmd_cnt * माप(*cmd_ids), GFP_NOIO);
	अगर (!पंचांगr)
		जाओ unlock;

	पंचांगr->पंचांगr_type = tcmu_पंचांगr_type(पंचांगf);
	पंचांगr->पंचांगr_cmd_cnt = cmd_cnt;

	अगर (cmd_cnt != 0) अणु
		cmd_cnt = 0;
		list_क्रम_each_entry(se_cmd, cmd_list, state_list) अणु
			अगर (!se_cmd->priv)
				जारी;
			cmd = se_cmd->priv;
			अगर (cmd->cmd_id)
				पंचांगr->पंचांगr_cmd_ids[cmd_cnt++] = cmd->cmd_id;
		पूर्ण
	पूर्ण

	queue_पंचांगr_ring(udev, पंचांगr);

unlock:
	mutex_unlock(&udev->cmdr_lock);
पूर्ण

अटल व्योम tcmu_handle_completion(काष्ठा tcmu_cmd *cmd, काष्ठा tcmu_cmd_entry *entry)
अणु
	काष्ठा se_cmd *se_cmd = cmd->se_cmd;
	काष्ठा tcmu_dev *udev = cmd->tcmu_dev;
	bool पढ़ो_len_valid = false;
	uपूर्णांक32_t पढ़ो_len;

	/*
	 * cmd has been completed alपढ़ोy from समयout, just reclaim
	 * data area space and मुक्त cmd
	 */
	अगर (test_bit(TCMU_CMD_BIT_EXPIRED, &cmd->flags)) अणु
		WARN_ON_ONCE(se_cmd);
		जाओ out;
	पूर्ण

	list_del_init(&cmd->queue_entry);

	tcmu_cmd_reset_dbi_cur(cmd);

	अगर (entry->hdr.uflags & TCMU_UFLAG_UNKNOWN_OP) अणु
		pr_warn("TCMU: Userspace set UNKNOWN_OP flag on se_cmd %p\n",
			cmd->se_cmd);
		entry->rsp.scsi_status = SAM_STAT_CHECK_CONDITION;
		जाओ करोne;
	पूर्ण

	पढ़ो_len = se_cmd->data_length;
	अगर (se_cmd->data_direction == DMA_FROM_DEVICE &&
	    (entry->hdr.uflags & TCMU_UFLAG_READ_LEN) && entry->rsp.पढ़ो_len) अणु
		पढ़ो_len_valid = true;
		अगर (entry->rsp.पढ़ो_len < पढ़ो_len)
			पढ़ो_len = entry->rsp.पढ़ो_len;
	पूर्ण

	अगर (entry->rsp.scsi_status == SAM_STAT_CHECK_CONDITION) अणु
		transport_copy_sense_to_cmd(se_cmd, entry->rsp.sense_buffer);
		अगर (!पढ़ो_len_valid )
			जाओ करोne;
		अन्यथा
			se_cmd->se_cmd_flags |= SCF_TREAT_READ_AS_NORMAL;
	पूर्ण
	अगर (se_cmd->se_cmd_flags & SCF_BIDI) अणु
		/* Get Data-In buffer beक्रमe clean up */
		gather_data_area(udev, cmd, true, पढ़ो_len);
	पूर्ण अन्यथा अगर (se_cmd->data_direction == DMA_FROM_DEVICE) अणु
		gather_data_area(udev, cmd, false, पढ़ो_len);
	पूर्ण अन्यथा अगर (se_cmd->data_direction == DMA_TO_DEVICE) अणु
		/* TODO: */
	पूर्ण अन्यथा अगर (se_cmd->data_direction != DMA_NONE) अणु
		pr_warn("TCMU: data direction was %d!\n",
			se_cmd->data_direction);
	पूर्ण

करोne:
	se_cmd->priv = शून्य;
	अगर (पढ़ो_len_valid) अणु
		pr_debug("read_len = %d\n", पढ़ो_len);
		target_complete_cmd_with_length(cmd->se_cmd,
					entry->rsp.scsi_status, पढ़ो_len);
	पूर्ण अन्यथा
		target_complete_cmd(cmd->se_cmd, entry->rsp.scsi_status);

out:
	tcmu_cmd_मुक्त_data(cmd, cmd->dbi_cnt);
	tcmu_मुक्त_cmd(cmd);
पूर्ण

अटल पूर्णांक tcmu_run_पंचांगr_queue(काष्ठा tcmu_dev *udev)
अणु
	काष्ठा tcmu_पंचांगr *पंचांगr, *पंचांगp;
	LIST_HEAD(पंचांगrs);

	अगर (list_empty(&udev->पंचांगr_queue))
		वापस 1;

	pr_debug("running %s's tmr queue\n", udev->name);

	list_splice_init(&udev->पंचांगr_queue, &पंचांगrs);

	list_क्रम_each_entry_safe(पंचांगr, पंचांगp, &पंचांगrs, queue_entry) अणु
		list_del_init(&पंचांगr->queue_entry);

		pr_debug("removing tmr %p on dev %s from queue\n",
			 पंचांगr, udev->name);

		अगर (queue_पंचांगr_ring(udev, पंचांगr)) अणु
			pr_debug("ran out of space during tmr queue run\n");
			/*
			 * पंचांगr was requeued, so just put all पंचांगrs back in
			 * the queue
			 */
			list_splice_tail(&पंचांगrs, &udev->पंचांगr_queue);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल bool tcmu_handle_completions(काष्ठा tcmu_dev *udev)
अणु
	काष्ठा tcmu_mailbox *mb;
	काष्ठा tcmu_cmd *cmd;
	bool मुक्त_space = false;

	अगर (test_bit(TCMU_DEV_BIT_BROKEN, &udev->flags)) अणु
		pr_err("ring broken, not handling completions\n");
		वापस 0;
	पूर्ण

	mb = udev->mb_addr;
	tcmu_flush_dcache_range(mb, माप(*mb));

	जबतक (udev->cmdr_last_cleaned != READ_ONCE(mb->cmd_tail)) अणु

		काष्ठा tcmu_cmd_entry *entry = udev->cmdr + udev->cmdr_last_cleaned;

		/*
		 * Flush max. up to end of cmd ring since current entry might
		 * be a padding that is लघुer than माप(*entry)
		 */
		माप_प्रकार ring_left = head_to_end(udev->cmdr_last_cleaned,
					       udev->cmdr_size);
		tcmu_flush_dcache_range(entry, ring_left < माप(*entry) ?
					ring_left : माप(*entry));

		मुक्त_space = true;

		अगर (tcmu_hdr_get_op(entry->hdr.len_op) == TCMU_OP_PAD ||
		    tcmu_hdr_get_op(entry->hdr.len_op) == TCMU_OP_TMR) अणु
			UPDATE_HEAD(udev->cmdr_last_cleaned,
				    tcmu_hdr_get_len(entry->hdr.len_op),
				    udev->cmdr_size);
			जारी;
		पूर्ण
		WARN_ON(tcmu_hdr_get_op(entry->hdr.len_op) != TCMU_OP_CMD);

		cmd = xa_erase(&udev->commands, entry->hdr.cmd_id);
		अगर (!cmd) अणु
			pr_err("cmd_id %u not found, ring is broken\n",
			       entry->hdr.cmd_id);
			set_bit(TCMU_DEV_BIT_BROKEN, &udev->flags);
			वापस false;
		पूर्ण

		tcmu_handle_completion(cmd, entry);

		UPDATE_HEAD(udev->cmdr_last_cleaned,
			    tcmu_hdr_get_len(entry->hdr.len_op),
			    udev->cmdr_size);
	पूर्ण
	अगर (मुक्त_space)
		मुक्त_space = tcmu_run_पंचांगr_queue(udev);

	अगर (atomic_पढ़ो(&global_page_count) > tcmu_global_max_pages &&
	    xa_empty(&udev->commands) && list_empty(&udev->qfull_queue)) अणु
		/*
		 * Allocated blocks exceeded global block limit, currently no
		 * more pending or रुकोing commands so try to reclaim blocks.
		 */
		schedule_delayed_work(&tcmu_unmap_work, 0);
	पूर्ण
	अगर (udev->cmd_समय_out)
		tcmu_set_next_deadline(&udev->inflight_queue, &udev->cmd_समयr);

	वापस मुक्त_space;
पूर्ण

अटल व्योम tcmu_check_expired_ring_cmd(काष्ठा tcmu_cmd *cmd)
अणु
	काष्ठा se_cmd *se_cmd;

	अगर (!समय_after_eq(jअगरfies, cmd->deadline))
		वापस;

	set_bit(TCMU_CMD_BIT_EXPIRED, &cmd->flags);
	list_del_init(&cmd->queue_entry);
	se_cmd = cmd->se_cmd;
	se_cmd->priv = शून्य;
	cmd->se_cmd = शून्य;

	pr_debug("Timing out inflight cmd %u on dev %s.\n",
		 cmd->cmd_id, cmd->tcmu_dev->name);

	target_complete_cmd(se_cmd, SAM_STAT_CHECK_CONDITION);
पूर्ण

अटल व्योम tcmu_check_expired_queue_cmd(काष्ठा tcmu_cmd *cmd)
अणु
	काष्ठा se_cmd *se_cmd;

	अगर (!समय_after_eq(jअगरfies, cmd->deadline))
		वापस;

	pr_debug("Timing out queued cmd %p on dev %s.\n",
		  cmd, cmd->tcmu_dev->name);

	list_del_init(&cmd->queue_entry);
	se_cmd = cmd->se_cmd;
	tcmu_मुक्त_cmd(cmd);

	se_cmd->priv = शून्य;
	target_complete_cmd(se_cmd, SAM_STAT_TASK_SET_FULL);
पूर्ण

अटल व्योम tcmu_device_समयकरोut(काष्ठा tcmu_dev *udev)
अणु
	spin_lock(&समयd_out_udevs_lock);
	अगर (list_empty(&udev->समयकरोut_entry))
		list_add_tail(&udev->समयकरोut_entry, &समयd_out_udevs);
	spin_unlock(&समयd_out_udevs_lock);

	schedule_delayed_work(&tcmu_unmap_work, 0);
पूर्ण

अटल व्योम tcmu_cmd_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा tcmu_dev *udev = from_समयr(udev, t, cmd_समयr);

	pr_debug("%s cmd timeout has expired\n", udev->name);
	tcmu_device_समयकरोut(udev);
पूर्ण

अटल व्योम tcmu_qfull_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा tcmu_dev *udev = from_समयr(udev, t, qfull_समयr);

	pr_debug("%s qfull timeout has expired\n", udev->name);
	tcmu_device_समयकरोut(udev);
पूर्ण

अटल पूर्णांक tcmu_attach_hba(काष्ठा se_hba *hba, u32 host_id)
अणु
	काष्ठा tcmu_hba *tcmu_hba;

	tcmu_hba = kzalloc(माप(काष्ठा tcmu_hba), GFP_KERNEL);
	अगर (!tcmu_hba)
		वापस -ENOMEM;

	tcmu_hba->host_id = host_id;
	hba->hba_ptr = tcmu_hba;

	वापस 0;
पूर्ण

अटल व्योम tcmu_detach_hba(काष्ठा se_hba *hba)
अणु
	kमुक्त(hba->hba_ptr);
	hba->hba_ptr = शून्य;
पूर्ण

अटल काष्ठा se_device *tcmu_alloc_device(काष्ठा se_hba *hba, स्थिर अक्षर *name)
अणु
	काष्ठा tcmu_dev *udev;

	udev = kzalloc(माप(काष्ठा tcmu_dev), GFP_KERNEL);
	अगर (!udev)
		वापस शून्य;
	kref_init(&udev->kref);

	udev->name = kstrdup(name, GFP_KERNEL);
	अगर (!udev->name) अणु
		kमुक्त(udev);
		वापस शून्य;
	पूर्ण

	udev->hba = hba;
	udev->cmd_समय_out = TCMU_TIME_OUT;
	udev->qfull_समय_out = -1;

	udev->data_pages_per_blk = DATA_PAGES_PER_BLK_DEF;
	udev->max_blocks = DATA_AREA_PAGES_DEF / udev->data_pages_per_blk;
	udev->data_area_mb = TCMU_PAGES_TO_MBS(DATA_AREA_PAGES_DEF);

	mutex_init(&udev->cmdr_lock);

	INIT_LIST_HEAD(&udev->node);
	INIT_LIST_HEAD(&udev->समयकरोut_entry);
	INIT_LIST_HEAD(&udev->qfull_queue);
	INIT_LIST_HEAD(&udev->पंचांगr_queue);
	INIT_LIST_HEAD(&udev->inflight_queue);
	xa_init_flags(&udev->commands, XA_FLAGS_ALLOC1);

	समयr_setup(&udev->qfull_समयr, tcmu_qfull_समयकरोut, 0);
	समयr_setup(&udev->cmd_समयr, tcmu_cmd_समयकरोut, 0);

	xa_init(&udev->data_pages);

	वापस &udev->se_dev;
पूर्ण

अटल व्योम tcmu_dev_call_rcu(काष्ठा rcu_head *p)
अणु
	काष्ठा se_device *dev = container_of(p, काष्ठा se_device, rcu_head);
	काष्ठा tcmu_dev *udev = TCMU_DEV(dev);

	kमुक्त(udev->uio_info.name);
	kमुक्त(udev->name);
	kमुक्त(udev);
पूर्ण

अटल पूर्णांक tcmu_check_and_मुक्त_pending_cmd(काष्ठा tcmu_cmd *cmd)
अणु
	अगर (test_bit(TCMU_CMD_BIT_EXPIRED, &cmd->flags)) अणु
		kmem_cache_मुक्त(tcmu_cmd_cache, cmd);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल u32 tcmu_blocks_release(काष्ठा tcmu_dev *udev, अचिन्हित दीर्घ first,
				अचिन्हित दीर्घ last)
अणु
	XA_STATE(xas, &udev->data_pages, first * udev->data_pages_per_blk);
	काष्ठा page *page;
	u32 pages_मुक्तd = 0;

	xas_lock(&xas);
	xas_क्रम_each(&xas, page, (last + 1) * udev->data_pages_per_blk - 1) अणु
		xas_store(&xas, शून्य);
		__मुक्त_page(page);
		pages_मुक्तd++;
	पूर्ण
	xas_unlock(&xas);

	atomic_sub(pages_मुक्तd, &global_page_count);

	वापस pages_मुक्तd;
पूर्ण

अटल व्योम tcmu_हटाओ_all_queued_पंचांगr(काष्ठा tcmu_dev *udev)
अणु
	काष्ठा tcmu_पंचांगr *पंचांगr, *पंचांगp;

	list_क्रम_each_entry_safe(पंचांगr, पंचांगp, &udev->पंचांगr_queue, queue_entry) अणु
		list_del_init(&पंचांगr->queue_entry);
		kमुक्त(पंचांगr);
	पूर्ण
पूर्ण

अटल व्योम tcmu_dev_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा tcmu_dev *udev = container_of(kref, काष्ठा tcmu_dev, kref);
	काष्ठा se_device *dev = &udev->se_dev;
	काष्ठा tcmu_cmd *cmd;
	bool all_expired = true;
	अचिन्हित दीर्घ i;

	vमुक्त(udev->mb_addr);
	udev->mb_addr = शून्य;

	spin_lock_bh(&समयd_out_udevs_lock);
	अगर (!list_empty(&udev->समयकरोut_entry))
		list_del(&udev->समयकरोut_entry);
	spin_unlock_bh(&समयd_out_udevs_lock);

	/* Upper layer should drain all requests beक्रमe calling this */
	mutex_lock(&udev->cmdr_lock);
	xa_क्रम_each(&udev->commands, i, cmd) अणु
		अगर (tcmu_check_and_मुक्त_pending_cmd(cmd) != 0)
			all_expired = false;
	पूर्ण
	/* There can be left over TMR cmds. Remove them. */
	tcmu_हटाओ_all_queued_पंचांगr(udev);
	अगर (!list_empty(&udev->qfull_queue))
		all_expired = false;
	xa_destroy(&udev->commands);
	WARN_ON(!all_expired);

	tcmu_blocks_release(udev, 0, udev->dbi_max);
	biपंचांगap_मुक्त(udev->data_biपंचांगap);
	mutex_unlock(&udev->cmdr_lock);

	pr_debug("dev_kref_release\n");

	call_rcu(&dev->rcu_head, tcmu_dev_call_rcu);
पूर्ण

अटल व्योम run_qfull_queue(काष्ठा tcmu_dev *udev, bool fail)
अणु
	काष्ठा tcmu_cmd *tcmu_cmd, *पंचांगp_cmd;
	LIST_HEAD(cmds);
	sense_reason_t scsi_ret;
	पूर्णांक ret;

	अगर (list_empty(&udev->qfull_queue))
		वापस;

	pr_debug("running %s's cmdr queue forcefail %d\n", udev->name, fail);

	list_splice_init(&udev->qfull_queue, &cmds);

	list_क्रम_each_entry_safe(tcmu_cmd, पंचांगp_cmd, &cmds, queue_entry) अणु
		list_del_init(&tcmu_cmd->queue_entry);

		pr_debug("removing cmd %p on dev %s from queue\n",
			 tcmu_cmd, udev->name);

		अगर (fail) अणु
			/*
			 * We were not able to even start the command, so
			 * fail with busy to allow a retry in हाल runner
			 * was only temporarily करोwn. If the device is being
			 * हटाओd then LIO core will करो the right thing and
			 * fail the retry.
			 */
			tcmu_cmd->se_cmd->priv = शून्य;
			target_complete_cmd(tcmu_cmd->se_cmd, SAM_STAT_BUSY);
			tcmu_मुक्त_cmd(tcmu_cmd);
			जारी;
		पूर्ण

		ret = queue_cmd_ring(tcmu_cmd, &scsi_ret);
		अगर (ret < 0) अणु
			pr_debug("cmd %p on dev %s failed with %u\n",
				 tcmu_cmd, udev->name, scsi_ret);
			/*
			 * Ignore scsi_ret क्रम now. target_complete_cmd
			 * drops it.
			 */
			tcmu_cmd->se_cmd->priv = शून्य;
			target_complete_cmd(tcmu_cmd->se_cmd,
					    SAM_STAT_CHECK_CONDITION);
			tcmu_मुक्त_cmd(tcmu_cmd);
		पूर्ण अन्यथा अगर (ret > 0) अणु
			pr_debug("ran out of space during cmdr queue run\n");
			/*
			 * cmd was requeued, so just put all cmds back in
			 * the queue
			 */
			list_splice_tail(&cmds, &udev->qfull_queue);
			अवरोध;
		पूर्ण
	पूर्ण

	tcmu_set_next_deadline(&udev->qfull_queue, &udev->qfull_समयr);
पूर्ण

अटल पूर्णांक tcmu_irqcontrol(काष्ठा uio_info *info, s32 irq_on)
अणु
	काष्ठा tcmu_dev *udev = container_of(info, काष्ठा tcmu_dev, uio_info);

	mutex_lock(&udev->cmdr_lock);
	अगर (tcmu_handle_completions(udev))
		run_qfull_queue(udev, false);
	mutex_unlock(&udev->cmdr_lock);

	वापस 0;
पूर्ण

/*
 * mmap code from uio.c. Copied here because we want to hook mmap()
 * and this stuff must come aदीर्घ.
 */
अटल पूर्णांक tcmu_find_mem_index(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tcmu_dev *udev = vma->vm_निजी_data;
	काष्ठा uio_info *info = &udev->uio_info;

	अगर (vma->vm_pgoff < MAX_UIO_MAPS) अणु
		अगर (info->mem[vma->vm_pgoff].size == 0)
			वापस -1;
		वापस (पूर्णांक)vma->vm_pgoff;
	पूर्ण
	वापस -1;
पूर्ण

अटल काष्ठा page *tcmu_try_get_data_page(काष्ठा tcmu_dev *udev, uपूर्णांक32_t dpi)
अणु
	काष्ठा page *page;

	mutex_lock(&udev->cmdr_lock);
	page = xa_load(&udev->data_pages, dpi);
	अगर (likely(page)) अणु
		mutex_unlock(&udev->cmdr_lock);
		वापस page;
	पूर्ण

	/*
	 * Userspace messed up and passed in a address not in the
	 * data iov passed to it.
	 */
	pr_err("Invalid addr to data page mapping (dpi %u) on device %s\n",
	       dpi, udev->name);
	mutex_unlock(&udev->cmdr_lock);

	वापस शून्य;
पूर्ण

अटल व्योम tcmu_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tcmu_dev *udev = vma->vm_निजी_data;

	pr_debug("vma_open\n");

	kref_get(&udev->kref);
पूर्ण

अटल व्योम tcmu_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tcmu_dev *udev = vma->vm_निजी_data;

	pr_debug("vma_close\n");

	/* release ref from tcmu_vma_खोलो */
	kref_put(&udev->kref, tcmu_dev_kref_release);
पूर्ण

अटल vm_fault_t tcmu_vma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा tcmu_dev *udev = vmf->vma->vm_निजी_data;
	काष्ठा uio_info *info = &udev->uio_info;
	काष्ठा page *page;
	अचिन्हित दीर्घ offset;
	व्योम *addr;

	पूर्णांक mi = tcmu_find_mem_index(vmf->vma);
	अगर (mi < 0)
		वापस VM_FAULT_SIGBUS;

	/*
	 * We need to subtract mi because userspace uses offset = N*PAGE_SIZE
	 * to use mem[N].
	 */
	offset = (vmf->pgoff - mi) << PAGE_SHIFT;

	अगर (offset < udev->data_off) अणु
		/* For the vदो_स्मृति()ed cmd area pages */
		addr = (व्योम *)(अचिन्हित दीर्घ)info->mem[mi].addr + offset;
		page = vदो_स्मृति_to_page(addr);
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t dpi;

		/* For the dynamically growing data area pages */
		dpi = (offset - udev->data_off) / PAGE_SIZE;
		page = tcmu_try_get_data_page(udev, dpi);
		अगर (!page)
			वापस VM_FAULT_SIGBUS;
	पूर्ण

	get_page(page);
	vmf->page = page;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा tcmu_vm_ops = अणु
	.खोलो = tcmu_vma_खोलो,
	.बंद = tcmu_vma_बंद,
	.fault = tcmu_vma_fault,
पूर्ण;

अटल पूर्णांक tcmu_mmap(काष्ठा uio_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tcmu_dev *udev = container_of(info, काष्ठा tcmu_dev, uio_info);

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &tcmu_vm_ops;

	vma->vm_निजी_data = udev;

	/* Ensure the mmap is exactly the right size */
	अगर (vma_pages(vma) != udev->mmap_pages)
		वापस -EINVAL;

	tcmu_vma_खोलो(vma);

	वापस 0;
पूर्ण

अटल पूर्णांक tcmu_खोलो(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा tcmu_dev *udev = container_of(info, काष्ठा tcmu_dev, uio_info);

	/* O_EXCL not supported क्रम अक्षर devs, so fake it? */
	अगर (test_and_set_bit(TCMU_DEV_BIT_OPEN, &udev->flags))
		वापस -EBUSY;

	udev->inode = inode;

	pr_debug("open\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tcmu_release(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा tcmu_dev *udev = container_of(info, काष्ठा tcmu_dev, uio_info);

	clear_bit(TCMU_DEV_BIT_OPEN, &udev->flags);

	pr_debug("close\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tcmu_init_genl_cmd_reply(काष्ठा tcmu_dev *udev, पूर्णांक cmd)
अणु
	काष्ठा tcmu_nl_cmd *nl_cmd = &udev->curr_nl_cmd;

	अगर (!tcmu_kern_cmd_reply_supported)
		वापस 0;

	अगर (udev->nl_reply_supported <= 0)
		वापस 0;

	mutex_lock(&tcmu_nl_cmd_mutex);

	अगर (tcmu_netlink_blocked) अणु
		mutex_unlock(&tcmu_nl_cmd_mutex);
		pr_warn("Failing nl cmd %d on %s. Interface is blocked.\n", cmd,
			udev->name);
		वापस -EAGAIN;
	पूर्ण

	अगर (nl_cmd->cmd != TCMU_CMD_UNSPEC) अणु
		mutex_unlock(&tcmu_nl_cmd_mutex);
		pr_warn("netlink cmd %d already executing on %s\n",
			 nl_cmd->cmd, udev->name);
		वापस -EBUSY;
	पूर्ण

	स_रखो(nl_cmd, 0, माप(*nl_cmd));
	nl_cmd->cmd = cmd;
	nl_cmd->udev = udev;
	init_completion(&nl_cmd->complete);
	INIT_LIST_HEAD(&nl_cmd->nl_list);

	list_add_tail(&nl_cmd->nl_list, &tcmu_nl_cmd_list);

	mutex_unlock(&tcmu_nl_cmd_mutex);
	वापस 0;
पूर्ण

अटल व्योम tcmu_destroy_genl_cmd_reply(काष्ठा tcmu_dev *udev)
अणु
	काष्ठा tcmu_nl_cmd *nl_cmd = &udev->curr_nl_cmd;

	अगर (!tcmu_kern_cmd_reply_supported)
		वापस;

	अगर (udev->nl_reply_supported <= 0)
		वापस;

	mutex_lock(&tcmu_nl_cmd_mutex);

	list_del(&nl_cmd->nl_list);
	स_रखो(nl_cmd, 0, माप(*nl_cmd));

	mutex_unlock(&tcmu_nl_cmd_mutex);
पूर्ण

अटल पूर्णांक tcmu_रुको_genl_cmd_reply(काष्ठा tcmu_dev *udev)
अणु
	काष्ठा tcmu_nl_cmd *nl_cmd = &udev->curr_nl_cmd;
	पूर्णांक ret;

	अगर (!tcmu_kern_cmd_reply_supported)
		वापस 0;

	अगर (udev->nl_reply_supported <= 0)
		वापस 0;

	pr_debug("sleeping for nl reply\n");
	रुको_क्रम_completion(&nl_cmd->complete);

	mutex_lock(&tcmu_nl_cmd_mutex);
	nl_cmd->cmd = TCMU_CMD_UNSPEC;
	ret = nl_cmd->status;
	mutex_unlock(&tcmu_nl_cmd_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tcmu_netlink_event_init(काष्ठा tcmu_dev *udev,
				   क्रमागत tcmu_genl_cmd cmd,
				   काष्ठा sk_buff **buf, व्योम **hdr)
अणु
	काष्ठा sk_buff *skb;
	व्योम *msg_header;
	पूर्णांक ret = -ENOMEM;

	skb = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस ret;

	msg_header = genlmsg_put(skb, 0, 0, &tcmu_genl_family, 0, cmd);
	अगर (!msg_header)
		जाओ मुक्त_skb;

	ret = nla_put_string(skb, TCMU_ATTR_DEVICE, udev->uio_info.name);
	अगर (ret < 0)
		जाओ मुक्त_skb;

	ret = nla_put_u32(skb, TCMU_ATTR_MINOR, udev->uio_info.uio_dev->minor);
	अगर (ret < 0)
		जाओ मुक्त_skb;

	ret = nla_put_u32(skb, TCMU_ATTR_DEVICE_ID, udev->se_dev.dev_index);
	अगर (ret < 0)
		जाओ मुक्त_skb;

	*buf = skb;
	*hdr = msg_header;
	वापस ret;

मुक्त_skb:
	nlmsg_मुक्त(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक tcmu_netlink_event_send(काष्ठा tcmu_dev *udev,
				   क्रमागत tcmu_genl_cmd cmd,
				   काष्ठा sk_buff *skb, व्योम *msg_header)
अणु
	पूर्णांक ret;

	genlmsg_end(skb, msg_header);

	ret = tcmu_init_genl_cmd_reply(udev, cmd);
	अगर (ret) अणु
		nlmsg_मुक्त(skb);
		वापस ret;
	पूर्ण

	ret = genlmsg_multicast_allns(&tcmu_genl_family, skb, 0,
				      TCMU_MCGRP_CONFIG, GFP_KERNEL);

	/* Wait during an add as the listener may not be up yet */
	अगर (ret == 0 ||
	   (ret == -ESRCH && cmd == TCMU_CMD_ADDED_DEVICE))
		वापस tcmu_रुको_genl_cmd_reply(udev);
	अन्यथा
		tcmu_destroy_genl_cmd_reply(udev);

	वापस ret;
पूर्ण

अटल पूर्णांक tcmu_send_dev_add_event(काष्ठा tcmu_dev *udev)
अणु
	काष्ठा sk_buff *skb = शून्य;
	व्योम *msg_header = शून्य;
	पूर्णांक ret = 0;

	ret = tcmu_netlink_event_init(udev, TCMU_CMD_ADDED_DEVICE, &skb,
				      &msg_header);
	अगर (ret < 0)
		वापस ret;
	वापस tcmu_netlink_event_send(udev, TCMU_CMD_ADDED_DEVICE, skb,
				       msg_header);
पूर्ण

अटल पूर्णांक tcmu_send_dev_हटाओ_event(काष्ठा tcmu_dev *udev)
अणु
	काष्ठा sk_buff *skb = शून्य;
	व्योम *msg_header = शून्य;
	पूर्णांक ret = 0;

	ret = tcmu_netlink_event_init(udev, TCMU_CMD_REMOVED_DEVICE,
				      &skb, &msg_header);
	अगर (ret < 0)
		वापस ret;
	वापस tcmu_netlink_event_send(udev, TCMU_CMD_REMOVED_DEVICE,
				       skb, msg_header);
पूर्ण

अटल पूर्णांक tcmu_update_uio_info(काष्ठा tcmu_dev *udev)
अणु
	काष्ठा tcmu_hba *hba = udev->hba->hba_ptr;
	काष्ठा uio_info *info;
	अक्षर *str;

	info = &udev->uio_info;

	अगर (udev->dev_config[0])
		str = kaप्र_लिखो(GFP_KERNEL, "tcm-user/%u/%s/%s", hba->host_id,
				udev->name, udev->dev_config);
	अन्यथा
		str = kaप्र_लिखो(GFP_KERNEL, "tcm-user/%u/%s", hba->host_id,
				udev->name);
	अगर (!str)
		वापस -ENOMEM;

	/* If the old string exists, मुक्त it */
	kमुक्त(info->name);
	info->name = str;

	वापस 0;
पूर्ण

अटल पूर्णांक tcmu_configure_device(काष्ठा se_device *dev)
अणु
	काष्ठा tcmu_dev *udev = TCMU_DEV(dev);
	काष्ठा uio_info *info;
	काष्ठा tcmu_mailbox *mb;
	माप_प्रकार data_size;
	पूर्णांक ret = 0;

	ret = tcmu_update_uio_info(udev);
	अगर (ret)
		वापस ret;

	info = &udev->uio_info;

	mutex_lock(&udev->cmdr_lock);
	udev->data_biपंचांगap = biपंचांगap_zalloc(udev->max_blocks, GFP_KERNEL);
	mutex_unlock(&udev->cmdr_lock);
	अगर (!udev->data_biपंचांगap) अणु
		ret = -ENOMEM;
		जाओ err_biपंचांगap_alloc;
	पूर्ण

	mb = vzalloc(MB_CMDR_SIZE);
	अगर (!mb) अणु
		ret = -ENOMEM;
		जाओ err_vzalloc;
	पूर्ण

	/* mailbox fits in first part of CMDR space */
	udev->mb_addr = mb;
	udev->cmdr = (व्योम *)mb + CMDR_OFF;
	udev->cmdr_size = CMDR_SIZE;
	udev->data_off = MB_CMDR_SIZE;
	data_size = TCMU_MBS_TO_PAGES(udev->data_area_mb) << PAGE_SHIFT;
	udev->mmap_pages = (data_size + MB_CMDR_SIZE) >> PAGE_SHIFT;
	udev->data_blk_size = udev->data_pages_per_blk * PAGE_SIZE;
	udev->dbi_thresh = 0; /* Default in Idle state */

	/* Initialise the mailbox of the ring buffer */
	mb->version = TCMU_MAILBOX_VERSION;
	mb->flags = TCMU_MAILBOX_FLAG_CAP_OOOC |
		    TCMU_MAILBOX_FLAG_CAP_READ_LEN |
		    TCMU_MAILBOX_FLAG_CAP_TMR;
	mb->cmdr_off = CMDR_OFF;
	mb->cmdr_size = udev->cmdr_size;

	WARN_ON(!PAGE_ALIGNED(udev->data_off));
	WARN_ON(data_size % PAGE_SIZE);

	info->version = __stringअगरy(TCMU_MAILBOX_VERSION);

	info->mem[0].name = "tcm-user command & data buffer";
	info->mem[0].addr = (phys_addr_t)(uपूर्णांकptr_t)udev->mb_addr;
	info->mem[0].size = data_size + MB_CMDR_SIZE;
	info->mem[0].memtype = UIO_MEM_NONE;

	info->irqcontrol = tcmu_irqcontrol;
	info->irq = UIO_IRQ_CUSTOM;

	info->mmap = tcmu_mmap;
	info->खोलो = tcmu_खोलो;
	info->release = tcmu_release;

	ret = uio_रेजिस्टर_device(tcmu_root_device, info);
	अगर (ret)
		जाओ err_रेजिस्टर;

	/* User can set hw_block_size beक्रमe enable the device */
	अगर (dev->dev_attrib.hw_block_size == 0)
		dev->dev_attrib.hw_block_size = 512;
	/* Other attributes can be configured in userspace */
	अगर (!dev->dev_attrib.hw_max_sectors)
		dev->dev_attrib.hw_max_sectors = 128;
	अगर (!dev->dev_attrib.emulate_ग_लिखो_cache)
		dev->dev_attrib.emulate_ग_लिखो_cache = 0;
	dev->dev_attrib.hw_queue_depth = 128;

	/* If user didn't explicitly disable netlink reply support, use
	 * module scope setting.
	 */
	अगर (udev->nl_reply_supported >= 0)
		udev->nl_reply_supported = tcmu_kern_cmd_reply_supported;

	/*
	 * Get a ref inहाल userspace करोes a बंद on the uio device beक्रमe
	 * LIO has initiated tcmu_मुक्त_device.
	 */
	kref_get(&udev->kref);

	ret = tcmu_send_dev_add_event(udev);
	अगर (ret)
		जाओ err_netlink;

	mutex_lock(&root_udev_mutex);
	list_add(&udev->node, &root_udev);
	mutex_unlock(&root_udev_mutex);

	वापस 0;

err_netlink:
	kref_put(&udev->kref, tcmu_dev_kref_release);
	uio_unरेजिस्टर_device(&udev->uio_info);
err_रेजिस्टर:
	vमुक्त(udev->mb_addr);
	udev->mb_addr = शून्य;
err_vzalloc:
	biपंचांगap_मुक्त(udev->data_biपंचांगap);
	udev->data_biपंचांगap = शून्य;
err_biपंचांगap_alloc:
	kमुक्त(info->name);
	info->name = शून्य;

	वापस ret;
पूर्ण

अटल व्योम tcmu_मुक्त_device(काष्ठा se_device *dev)
अणु
	काष्ठा tcmu_dev *udev = TCMU_DEV(dev);

	/* release ref from init */
	kref_put(&udev->kref, tcmu_dev_kref_release);
पूर्ण

अटल व्योम tcmu_destroy_device(काष्ठा se_device *dev)
अणु
	काष्ठा tcmu_dev *udev = TCMU_DEV(dev);

	del_समयr_sync(&udev->cmd_समयr);
	del_समयr_sync(&udev->qfull_समयr);

	mutex_lock(&root_udev_mutex);
	list_del(&udev->node);
	mutex_unlock(&root_udev_mutex);

	tcmu_send_dev_हटाओ_event(udev);

	uio_unरेजिस्टर_device(&udev->uio_info);

	/* release ref from configure */
	kref_put(&udev->kref, tcmu_dev_kref_release);
पूर्ण

अटल व्योम tcmu_unblock_dev(काष्ठा tcmu_dev *udev)
अणु
	mutex_lock(&udev->cmdr_lock);
	clear_bit(TCMU_DEV_BIT_BLOCKED, &udev->flags);
	mutex_unlock(&udev->cmdr_lock);
पूर्ण

अटल व्योम tcmu_block_dev(काष्ठा tcmu_dev *udev)
अणु
	mutex_lock(&udev->cmdr_lock);

	अगर (test_and_set_bit(TCMU_DEV_BIT_BLOCKED, &udev->flags))
		जाओ unlock;

	/* complete IO that has executed successfully */
	tcmu_handle_completions(udev);
	/* fail IO रुकोing to be queued */
	run_qfull_queue(udev, true);

unlock:
	mutex_unlock(&udev->cmdr_lock);
पूर्ण

अटल व्योम tcmu_reset_ring(काष्ठा tcmu_dev *udev, u8 err_level)
अणु
	काष्ठा tcmu_mailbox *mb;
	काष्ठा tcmu_cmd *cmd;
	अचिन्हित दीर्घ i;

	mutex_lock(&udev->cmdr_lock);

	xa_क्रम_each(&udev->commands, i, cmd) अणु
		pr_debug("removing cmd %u on dev %s from ring (is expired %d)\n",
			  cmd->cmd_id, udev->name,
			  test_bit(TCMU_CMD_BIT_EXPIRED, &cmd->flags));

		xa_erase(&udev->commands, i);
		अगर (!test_bit(TCMU_CMD_BIT_EXPIRED, &cmd->flags)) अणु
			WARN_ON(!cmd->se_cmd);
			list_del_init(&cmd->queue_entry);
			cmd->se_cmd->priv = शून्य;
			अगर (err_level == 1) अणु
				/*
				 * Userspace was not able to start the
				 * command or it is retryable.
				 */
				target_complete_cmd(cmd->se_cmd, SAM_STAT_BUSY);
			पूर्ण अन्यथा अणु
				/* hard failure */
				target_complete_cmd(cmd->se_cmd,
						    SAM_STAT_CHECK_CONDITION);
			पूर्ण
		पूर्ण
		tcmu_cmd_मुक्त_data(cmd, cmd->dbi_cnt);
		tcmu_मुक्त_cmd(cmd);
	पूर्ण

	mb = udev->mb_addr;
	tcmu_flush_dcache_range(mb, माप(*mb));
	pr_debug("mb last %u head %u tail %u\n", udev->cmdr_last_cleaned,
		 mb->cmd_tail, mb->cmd_head);

	udev->cmdr_last_cleaned = 0;
	mb->cmd_tail = 0;
	mb->cmd_head = 0;
	tcmu_flush_dcache_range(mb, माप(*mb));
	clear_bit(TCMU_DEV_BIT_BROKEN, &udev->flags);

	del_समयr(&udev->cmd_समयr);

	/*
	 * ring is empty and qfull queue never contains पातed commands.
	 * So TMRs in पंचांगr queue करो not contain relevant cmd_ids.
	 * After a ring reset userspace should करो a fresh start, so
	 * even LUN RESET message is no दीर्घer relevant.
	 * Thereक्रमe हटाओ all TMRs from qfull queue
	 */
	tcmu_हटाओ_all_queued_पंचांगr(udev);

	run_qfull_queue(udev, false);

	mutex_unlock(&udev->cmdr_lock);
पूर्ण

क्रमागत अणु
	Opt_dev_config, Opt_dev_size, Opt_hw_block_size, Opt_hw_max_sectors,
	Opt_nl_reply_supported, Opt_max_data_area_mb, Opt_data_pages_per_blk,
	Opt_err,
पूर्ण;

अटल match_table_t tokens = अणु
	अणुOpt_dev_config, "dev_config=%s"पूर्ण,
	अणुOpt_dev_size, "dev_size=%s"पूर्ण,
	अणुOpt_hw_block_size, "hw_block_size=%d"पूर्ण,
	अणुOpt_hw_max_sectors, "hw_max_sectors=%d"पूर्ण,
	अणुOpt_nl_reply_supported, "nl_reply_supported=%d"पूर्ण,
	अणुOpt_max_data_area_mb, "max_data_area_mb=%d"पूर्ण,
	अणुOpt_data_pages_per_blk, "data_pages_per_blk=%d"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक tcmu_set_dev_attrib(substring_t *arg, u32 *dev_attrib)
अणु
	पूर्णांक val, ret;

	ret = match_पूर्णांक(arg, &val);
	अगर (ret < 0) अणु
		pr_err("match_int() failed for dev attrib. Error %d.\n",
		       ret);
		वापस ret;
	पूर्ण

	अगर (val <= 0) अणु
		pr_err("Invalid dev attrib value %d. Must be greater than zero.\n",
		       val);
		वापस -EINVAL;
	पूर्ण
	*dev_attrib = val;
	वापस 0;
पूर्ण

अटल पूर्णांक tcmu_set_max_blocks_param(काष्ठा tcmu_dev *udev, substring_t *arg)
अणु
	पूर्णांक val, ret;
	uपूर्णांक32_t pages_per_blk = udev->data_pages_per_blk;

	ret = match_पूर्णांक(arg, &val);
	अगर (ret < 0) अणु
		pr_err("match_int() failed for max_data_area_mb=. Error %d.\n",
		       ret);
		वापस ret;
	पूर्ण
	अगर (val <= 0) अणु
		pr_err("Invalid max_data_area %d.\n", val);
		वापस -EINVAL;
	पूर्ण
	अगर (val > TCMU_PAGES_TO_MBS(tcmu_global_max_pages)) अणु
		pr_err("%d is too large. Adjusting max_data_area_mb to global limit of %u\n",
		       val, TCMU_PAGES_TO_MBS(tcmu_global_max_pages));
		val = TCMU_PAGES_TO_MBS(tcmu_global_max_pages);
	पूर्ण
	अगर (TCMU_MBS_TO_PAGES(val) < pages_per_blk) अणु
		pr_err("Invalid max_data_area %d (%zu pages): smaller than data_pages_per_blk (%u pages).\n",
		       val, TCMU_MBS_TO_PAGES(val), pages_per_blk);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&udev->cmdr_lock);
	अगर (udev->data_biपंचांगap) अणु
		pr_err("Cannot set max_data_area_mb after it has been enabled.\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	udev->data_area_mb = val;
	udev->max_blocks = TCMU_MBS_TO_PAGES(val) / pages_per_blk;

unlock:
	mutex_unlock(&udev->cmdr_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक tcmu_set_data_pages_per_blk(काष्ठा tcmu_dev *udev, substring_t *arg)
अणु
	पूर्णांक val, ret;

	ret = match_पूर्णांक(arg, &val);
	अगर (ret < 0) अणु
		pr_err("match_int() failed for data_pages_per_blk=. Error %d.\n",
		       ret);
		वापस ret;
	पूर्ण

	अगर (val > TCMU_MBS_TO_PAGES(udev->data_area_mb)) अणु
		pr_err("Invalid data_pages_per_blk %d: greater than max_data_area_mb %d -> %zd pages).\n",
		       val, udev->data_area_mb,
		       TCMU_MBS_TO_PAGES(udev->data_area_mb));
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&udev->cmdr_lock);
	अगर (udev->data_biपंचांगap) अणु
		pr_err("Cannot set data_pages_per_blk after it has been enabled.\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	udev->data_pages_per_blk = val;
	udev->max_blocks = TCMU_MBS_TO_PAGES(udev->data_area_mb) / val;

unlock:
	mutex_unlock(&udev->cmdr_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार tcmu_set_configfs_dev_params(काष्ठा se_device *dev,
		स्थिर अक्षर *page, sमाप_प्रकार count)
अणु
	काष्ठा tcmu_dev *udev = TCMU_DEV(dev);
	अक्षर *orig, *ptr, *opts;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक ret = 0, token;

	opts = kstrdup(page, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;

	orig = opts;

	जबतक ((ptr = strsep(&opts, ",\n")) != शून्य) अणु
		अगर (!*ptr)
			जारी;

		token = match_token(ptr, tokens, args);
		चयन (token) अणु
		हाल Opt_dev_config:
			अगर (match_strlcpy(udev->dev_config, &args[0],
					  TCMU_CONFIG_LEN) == 0) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			pr_debug("TCMU: Referencing Path: %s\n", udev->dev_config);
			अवरोध;
		हाल Opt_dev_size:
			ret = match_u64(&args[0], &udev->dev_size);
			अगर (ret < 0)
				pr_err("match_u64() failed for dev_size=. Error %d.\n",
				       ret);
			अवरोध;
		हाल Opt_hw_block_size:
			ret = tcmu_set_dev_attrib(&args[0],
					&(dev->dev_attrib.hw_block_size));
			अवरोध;
		हाल Opt_hw_max_sectors:
			ret = tcmu_set_dev_attrib(&args[0],
					&(dev->dev_attrib.hw_max_sectors));
			अवरोध;
		हाल Opt_nl_reply_supported:
			ret = match_पूर्णांक(&args[0], &udev->nl_reply_supported);
			अगर (ret < 0)
				pr_err("match_int() failed for nl_reply_supported=. Error %d.\n",
				       ret);
			अवरोध;
		हाल Opt_max_data_area_mb:
			ret = tcmu_set_max_blocks_param(udev, &args[0]);
			अवरोध;
		हाल Opt_data_pages_per_blk:
			ret = tcmu_set_data_pages_per_blk(udev, &args[0]);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (ret)
			अवरोध;
	पूर्ण

	kमुक्त(orig);
	वापस (!ret) ? count : ret;
पूर्ण

अटल sमाप_प्रकार tcmu_show_configfs_dev_params(काष्ठा se_device *dev, अक्षर *b)
अणु
	काष्ठा tcmu_dev *udev = TCMU_DEV(dev);
	sमाप_प्रकार bl = 0;

	bl = प्र_लिखो(b + bl, "Config: %s ",
		     udev->dev_config[0] ? udev->dev_config : "NULL");
	bl += प्र_लिखो(b + bl, "Size: %llu ", udev->dev_size);
	bl += प्र_लिखो(b + bl, "MaxDataAreaMB: %u ", udev->data_area_mb);
	bl += प्र_लिखो(b + bl, "DataPagesPerBlk: %u\n", udev->data_pages_per_blk);

	वापस bl;
पूर्ण

अटल sector_t tcmu_get_blocks(काष्ठा se_device *dev)
अणु
	काष्ठा tcmu_dev *udev = TCMU_DEV(dev);

	वापस भाग_u64(udev->dev_size - dev->dev_attrib.block_size,
		       dev->dev_attrib.block_size);
पूर्ण

अटल sense_reason_t
tcmu_parse_cdb(काष्ठा se_cmd *cmd)
अणु
	वापस passthrough_parse_cdb(cmd, tcmu_queue_cmd);
पूर्ण

अटल sमाप_प्रकार tcmu_cmd_समय_out_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
					काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);

	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n", udev->cmd_समय_out / MSEC_PER_SEC);
पूर्ण

अटल sमाप_प्रकार tcmu_cmd_समय_out_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				       माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
					काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = container_of(da->da_dev,
					काष्ठा tcmu_dev, se_dev);
	u32 val;
	पूर्णांक ret;

	अगर (da->da_dev->export_count) अणु
		pr_err("Unable to set tcmu cmd_time_out while exports exist\n");
		वापस -EINVAL;
	पूर्ण

	ret = kstrtou32(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	udev->cmd_समय_out = val * MSEC_PER_SEC;
	वापस count;
पूर्ण
CONFIGFS_ATTR(tcmu_, cmd_समय_out);

अटल sमाप_प्रकार tcmu_qfull_समय_out_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);

	वापस snम_लिखो(page, PAGE_SIZE, "%ld\n", udev->qfull_समय_out <= 0 ?
			udev->qfull_समय_out :
			udev->qfull_समय_out / MSEC_PER_SEC);
पूर्ण

अटल sमाप_प्रकार tcmu_qfull_समय_out_store(काष्ठा config_item *item,
					 स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
					काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);
	s32 val;
	पूर्णांक ret;

	ret = kstrtos32(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val >= 0) अणु
		udev->qfull_समय_out = val * MSEC_PER_SEC;
	पूर्ण अन्यथा अगर (val == -1) अणु
		udev->qfull_समय_out = val;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "Invalid qfull timeout value %d\n", val);
		वापस -EINVAL;
	पूर्ण
	वापस count;
पूर्ण
CONFIGFS_ATTR(tcmu_, qfull_समय_out);

अटल sमाप_प्रकार tcmu_max_data_area_mb_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", udev->data_area_mb);
पूर्ण
CONFIGFS_ATTR_RO(tcmu_, max_data_area_mb);

अटल sमाप_प्रकार tcmu_data_pages_per_blk_show(काष्ठा config_item *item,
					    अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", udev->data_pages_per_blk);
पूर्ण
CONFIGFS_ATTR_RO(tcmu_, data_pages_per_blk);

अटल sमाप_प्रकार tcmu_dev_config_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", udev->dev_config);
पूर्ण

अटल पूर्णांक tcmu_send_dev_config_event(काष्ठा tcmu_dev *udev,
				      स्थिर अक्षर *reconfig_data)
अणु
	काष्ठा sk_buff *skb = शून्य;
	व्योम *msg_header = शून्य;
	पूर्णांक ret = 0;

	ret = tcmu_netlink_event_init(udev, TCMU_CMD_RECONFIG_DEVICE,
				      &skb, &msg_header);
	अगर (ret < 0)
		वापस ret;
	ret = nla_put_string(skb, TCMU_ATTR_DEV_CFG, reconfig_data);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(skb);
		वापस ret;
	पूर्ण
	वापस tcmu_netlink_event_send(udev, TCMU_CMD_RECONFIG_DEVICE,
				       skb, msg_header);
पूर्ण


अटल sमाप_प्रकार tcmu_dev_config_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				     माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);
	पूर्णांक ret, len;

	len = म_माप(page);
	अगर (!len || len > TCMU_CONFIG_LEN - 1)
		वापस -EINVAL;

	/* Check अगर device has been configured beक्रमe */
	अगर (target_dev_configured(&udev->se_dev)) अणु
		ret = tcmu_send_dev_config_event(udev, page);
		अगर (ret) अणु
			pr_err("Unable to reconfigure device\n");
			वापस ret;
		पूर्ण
		strlcpy(udev->dev_config, page, TCMU_CONFIG_LEN);

		ret = tcmu_update_uio_info(udev);
		अगर (ret)
			वापस ret;
		वापस count;
	पूर्ण
	strlcpy(udev->dev_config, page, TCMU_CONFIG_LEN);

	वापस count;
पूर्ण
CONFIGFS_ATTR(tcmu_, dev_config);

अटल sमाप_प्रकार tcmu_dev_size_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);

	वापस snम_लिखो(page, PAGE_SIZE, "%llu\n", udev->dev_size);
पूर्ण

अटल पूर्णांक tcmu_send_dev_size_event(काष्ठा tcmu_dev *udev, u64 size)
अणु
	काष्ठा sk_buff *skb = शून्य;
	व्योम *msg_header = शून्य;
	पूर्णांक ret = 0;

	ret = tcmu_netlink_event_init(udev, TCMU_CMD_RECONFIG_DEVICE,
				      &skb, &msg_header);
	अगर (ret < 0)
		वापस ret;
	ret = nla_put_u64_64bit(skb, TCMU_ATTR_DEV_SIZE,
				size, TCMU_ATTR_PAD);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(skb);
		वापस ret;
	पूर्ण
	वापस tcmu_netlink_event_send(udev, TCMU_CMD_RECONFIG_DEVICE,
				       skb, msg_header);
पूर्ण

अटल sमाप_प्रकार tcmu_dev_size_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				   माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);
	u64 val;
	पूर्णांक ret;

	ret = kstrtou64(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	/* Check अगर device has been configured beक्रमe */
	अगर (target_dev_configured(&udev->se_dev)) अणु
		ret = tcmu_send_dev_size_event(udev, val);
		अगर (ret) अणु
			pr_err("Unable to reconfigure device\n");
			वापस ret;
		पूर्ण
	पूर्ण
	udev->dev_size = val;
	वापस count;
पूर्ण
CONFIGFS_ATTR(tcmu_, dev_size);

अटल sमाप_प्रकार tcmu_nl_reply_supported_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);

	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", udev->nl_reply_supported);
पूर्ण

अटल sमाप_प्रकार tcmu_nl_reply_supported_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
						काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);
	s8 val;
	पूर्णांक ret;

	ret = kstrtos8(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	udev->nl_reply_supported = val;
	वापस count;
पूर्ण
CONFIGFS_ATTR(tcmu_, nl_reply_supported);

अटल sमाप_प्रकार tcmu_emulate_ग_लिखो_cache_show(काष्ठा config_item *item,
					     अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
					काष्ठा se_dev_attrib, da_group);

	वापस snम_लिखो(page, PAGE_SIZE, "%i\n", da->emulate_ग_लिखो_cache);
पूर्ण

अटल पूर्णांक tcmu_send_emulate_ग_लिखो_cache(काष्ठा tcmu_dev *udev, u8 val)
अणु
	काष्ठा sk_buff *skb = शून्य;
	व्योम *msg_header = शून्य;
	पूर्णांक ret = 0;

	ret = tcmu_netlink_event_init(udev, TCMU_CMD_RECONFIG_DEVICE,
				      &skb, &msg_header);
	अगर (ret < 0)
		वापस ret;
	ret = nla_put_u8(skb, TCMU_ATTR_WRITECACHE, val);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(skb);
		वापस ret;
	पूर्ण
	वापस tcmu_netlink_event_send(udev, TCMU_CMD_RECONFIG_DEVICE,
				       skb, msg_header);
पूर्ण

अटल sमाप_प्रकार tcmu_emulate_ग_लिखो_cache_store(काष्ठा config_item *item,
					      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
					काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);
	u8 val;
	पूर्णांक ret;

	ret = kstrtou8(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	/* Check अगर device has been configured beक्रमe */
	अगर (target_dev_configured(&udev->se_dev)) अणु
		ret = tcmu_send_emulate_ग_लिखो_cache(udev, val);
		अगर (ret) अणु
			pr_err("Unable to reconfigure device\n");
			वापस ret;
		पूर्ण
	पूर्ण

	da->emulate_ग_लिखो_cache = val;
	वापस count;
पूर्ण
CONFIGFS_ATTR(tcmu_, emulate_ग_लिखो_cache);

अटल sमाप_प्रकार tcmu_पंचांगr_notअगरication_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
					काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);

	वापस snम_लिखो(page, PAGE_SIZE, "%i\n",
			test_bit(TCMU_DEV_BIT_TMR_NOTIFY, &udev->flags));
पूर्ण

अटल sमाप_प्रकार tcmu_पंचांगr_notअगरication_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = container_of(to_config_group(item),
					काष्ठा se_dev_attrib, da_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(da->da_dev);
	u8 val;
	पूर्णांक ret;

	ret = kstrtou8(page, 0, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val > 1)
		वापस -EINVAL;

	अगर (val)
		set_bit(TCMU_DEV_BIT_TMR_NOTIFY, &udev->flags);
	अन्यथा
		clear_bit(TCMU_DEV_BIT_TMR_NOTIFY, &udev->flags);
	वापस count;
पूर्ण
CONFIGFS_ATTR(tcmu_, पंचांगr_notअगरication);

अटल sमाप_प्रकार tcmu_block_dev_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *se_dev = container_of(to_config_group(item),
						काष्ठा se_device,
						dev_action_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(se_dev);

	अगर (test_bit(TCMU_DEV_BIT_BLOCKED, &udev->flags))
		वापस snम_लिखो(page, PAGE_SIZE, "%s\n", "blocked");
	अन्यथा
		वापस snम_लिखो(page, PAGE_SIZE, "%s\n", "unblocked");
पूर्ण

अटल sमाप_प्रकार tcmu_block_dev_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				    माप_प्रकार count)
अणु
	काष्ठा se_device *se_dev = container_of(to_config_group(item),
						काष्ठा se_device,
						dev_action_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(se_dev);
	u8 val;
	पूर्णांक ret;

	अगर (!target_dev_configured(&udev->se_dev)) अणु
		pr_err("Device is not configured.\n");
		वापस -EINVAL;
	पूर्ण

	ret = kstrtou8(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val > 1) अणु
		pr_err("Invalid block value %d\n", val);
		वापस -EINVAL;
	पूर्ण

	अगर (!val)
		tcmu_unblock_dev(udev);
	अन्यथा
		tcmu_block_dev(udev);
	वापस count;
पूर्ण
CONFIGFS_ATTR(tcmu_, block_dev);

अटल sमाप_प्रकार tcmu_reset_ring_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				     माप_प्रकार count)
अणु
	काष्ठा se_device *se_dev = container_of(to_config_group(item),
						काष्ठा se_device,
						dev_action_group);
	काष्ठा tcmu_dev *udev = TCMU_DEV(se_dev);
	u8 val;
	पूर्णांक ret;

	अगर (!target_dev_configured(&udev->se_dev)) अणु
		pr_err("Device is not configured.\n");
		वापस -EINVAL;
	पूर्ण

	ret = kstrtou8(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val != 1 && val != 2) अणु
		pr_err("Invalid reset ring value %d\n", val);
		वापस -EINVAL;
	पूर्ण

	tcmu_reset_ring(udev, val);
	वापस count;
पूर्ण
CONFIGFS_ATTR_WO(tcmu_, reset_ring);

अटल काष्ठा configfs_attribute *tcmu_attrib_attrs[] = अणु
	&tcmu_attr_cmd_समय_out,
	&tcmu_attr_qfull_समय_out,
	&tcmu_attr_max_data_area_mb,
	&tcmu_attr_data_pages_per_blk,
	&tcmu_attr_dev_config,
	&tcmu_attr_dev_size,
	&tcmu_attr_emulate_ग_लिखो_cache,
	&tcmu_attr_पंचांगr_notअगरication,
	&tcmu_attr_nl_reply_supported,
	शून्य,
पूर्ण;

अटल काष्ठा configfs_attribute **tcmu_attrs;

अटल काष्ठा configfs_attribute *tcmu_action_attrs[] = अणु
	&tcmu_attr_block_dev,
	&tcmu_attr_reset_ring,
	शून्य,
पूर्ण;

अटल काष्ठा target_backend_ops tcmu_ops = अणु
	.name			= "user",
	.owner			= THIS_MODULE,
	.transport_flags_शेष = TRANSPORT_FLAG_PASSTHROUGH,
	.transport_flags_changeable = TRANSPORT_FLAG_PASSTHROUGH_PGR |
				      TRANSPORT_FLAG_PASSTHROUGH_ALUA,
	.attach_hba		= tcmu_attach_hba,
	.detach_hba		= tcmu_detach_hba,
	.alloc_device		= tcmu_alloc_device,
	.configure_device	= tcmu_configure_device,
	.destroy_device		= tcmu_destroy_device,
	.मुक्त_device		= tcmu_मुक्त_device,
	.unplug_device		= tcmu_unplug_device,
	.plug_device		= tcmu_plug_device,
	.parse_cdb		= tcmu_parse_cdb,
	.पंचांगr_notअगरy		= tcmu_पंचांगr_notअगरy,
	.set_configfs_dev_params = tcmu_set_configfs_dev_params,
	.show_configfs_dev_params = tcmu_show_configfs_dev_params,
	.get_device_type	= sbc_get_device_type,
	.get_blocks		= tcmu_get_blocks,
	.tb_dev_action_attrs	= tcmu_action_attrs,
पूर्ण;

अटल व्योम find_मुक्त_blocks(व्योम)
अणु
	काष्ठा tcmu_dev *udev;
	loff_t off;
	u32 pages_मुक्तd, total_pages_मुक्तd = 0;
	u32 start, end, block, total_blocks_मुक्तd = 0;

	अगर (atomic_पढ़ो(&global_page_count) <= tcmu_global_max_pages)
		वापस;

	mutex_lock(&root_udev_mutex);
	list_क्रम_each_entry(udev, &root_udev, node) अणु
		mutex_lock(&udev->cmdr_lock);

		अगर (!target_dev_configured(&udev->se_dev)) अणु
			mutex_unlock(&udev->cmdr_lock);
			जारी;
		पूर्ण

		/* Try to complete the finished commands first */
		अगर (tcmu_handle_completions(udev))
			run_qfull_queue(udev, false);

		/* Skip the udevs in idle */
		अगर (!udev->dbi_thresh) अणु
			mutex_unlock(&udev->cmdr_lock);
			जारी;
		पूर्ण

		end = udev->dbi_max + 1;
		block = find_last_bit(udev->data_biपंचांगap, end);
		अगर (block == udev->dbi_max) अणु
			/*
			 * The last bit is dbi_max, so it is not possible
			 * reclaim any blocks.
			 */
			mutex_unlock(&udev->cmdr_lock);
			जारी;
		पूर्ण अन्यथा अगर (block == end) अणु
			/* The current udev will जाओ idle state */
			udev->dbi_thresh = start = 0;
			udev->dbi_max = 0;
		पूर्ण अन्यथा अणु
			udev->dbi_thresh = start = block + 1;
			udev->dbi_max = block;
		पूर्ण

		/* Here will truncate the data area from off */
		off = udev->data_off + (loff_t)start * udev->data_blk_size;
		unmap_mapping_range(udev->inode->i_mapping, off, 0, 1);

		/* Release the block pages */
		pages_मुक्तd = tcmu_blocks_release(udev, start, end - 1);
		mutex_unlock(&udev->cmdr_lock);

		total_pages_मुक्तd += pages_मुक्तd;
		total_blocks_मुक्तd += end - start;
		pr_debug("Freed %u pages (total %u) from %u blocks (total %u) from %s.\n",
			 pages_मुक्तd, total_pages_मुक्तd, end - start,
			 total_blocks_मुक्तd, udev->name);
	पूर्ण
	mutex_unlock(&root_udev_mutex);

	अगर (atomic_पढ़ो(&global_page_count) > tcmu_global_max_pages)
		schedule_delayed_work(&tcmu_unmap_work, msecs_to_jअगरfies(5000));
पूर्ण

अटल व्योम check_समयकरोut_devices(व्योम)
अणु
	काष्ठा tcmu_dev *udev, *पंचांगp_dev;
	काष्ठा tcmu_cmd *cmd, *पंचांगp_cmd;
	LIST_HEAD(devs);

	spin_lock_bh(&समयd_out_udevs_lock);
	list_splice_init(&समयd_out_udevs, &devs);

	list_क्रम_each_entry_safe(udev, पंचांगp_dev, &devs, समयकरोut_entry) अणु
		list_del_init(&udev->समयकरोut_entry);
		spin_unlock_bh(&समयd_out_udevs_lock);

		mutex_lock(&udev->cmdr_lock);

		/*
		 * If cmd_समय_out is disabled but qfull is set deadline
		 * will only reflect the qfull समयout. Ignore it.
		 */
		अगर (udev->cmd_समय_out) अणु
			list_क्रम_each_entry_safe(cmd, पंचांगp_cmd,
						 &udev->inflight_queue,
						 queue_entry) अणु
				tcmu_check_expired_ring_cmd(cmd);
			पूर्ण
			tcmu_set_next_deadline(&udev->inflight_queue,
					       &udev->cmd_समयr);
		पूर्ण
		list_क्रम_each_entry_safe(cmd, पंचांगp_cmd, &udev->qfull_queue,
					 queue_entry) अणु
			tcmu_check_expired_queue_cmd(cmd);
		पूर्ण
		tcmu_set_next_deadline(&udev->qfull_queue, &udev->qfull_समयr);

		mutex_unlock(&udev->cmdr_lock);

		spin_lock_bh(&समयd_out_udevs_lock);
	पूर्ण

	spin_unlock_bh(&समयd_out_udevs_lock);
पूर्ण

अटल व्योम tcmu_unmap_work_fn(काष्ठा work_काष्ठा *work)
अणु
	check_समयकरोut_devices();
	find_मुक्त_blocks();
पूर्ण

अटल पूर्णांक __init tcmu_module_init(व्योम)
अणु
	पूर्णांक ret, i, k, len = 0;

	BUILD_BUG_ON((माप(काष्ठा tcmu_cmd_entry) % TCMU_OP_ALIGN_SIZE) != 0);

	INIT_DELAYED_WORK(&tcmu_unmap_work, tcmu_unmap_work_fn);

	tcmu_cmd_cache = kmem_cache_create("tcmu_cmd_cache",
				माप(काष्ठा tcmu_cmd),
				__alignof__(काष्ठा tcmu_cmd),
				0, शून्य);
	अगर (!tcmu_cmd_cache)
		वापस -ENOMEM;

	tcmu_root_device = root_device_रेजिस्टर("tcm_user");
	अगर (IS_ERR(tcmu_root_device)) अणु
		ret = PTR_ERR(tcmu_root_device);
		जाओ out_मुक्त_cache;
	पूर्ण

	ret = genl_रेजिस्टर_family(&tcmu_genl_family);
	अगर (ret < 0) अणु
		जाओ out_unreg_device;
	पूर्ण

	क्रम (i = 0; passthrough_attrib_attrs[i] != शून्य; i++)
		len += माप(काष्ठा configfs_attribute *);
	क्रम (i = 0; passthrough_pr_attrib_attrs[i] != शून्य; i++)
		len += माप(काष्ठा configfs_attribute *);
	क्रम (i = 0; tcmu_attrib_attrs[i] != शून्य; i++)
		len += माप(काष्ठा configfs_attribute *);
	len += माप(काष्ठा configfs_attribute *);

	tcmu_attrs = kzalloc(len, GFP_KERNEL);
	अगर (!tcmu_attrs) अणु
		ret = -ENOMEM;
		जाओ out_unreg_genl;
	पूर्ण

	क्रम (i = 0; passthrough_attrib_attrs[i] != शून्य; i++)
		tcmu_attrs[i] = passthrough_attrib_attrs[i];
	क्रम (k = 0; passthrough_pr_attrib_attrs[k] != शून्य; k++)
		tcmu_attrs[i++] = passthrough_pr_attrib_attrs[k];
	क्रम (k = 0; tcmu_attrib_attrs[k] != शून्य; k++)
		tcmu_attrs[i++] = tcmu_attrib_attrs[k];
	tcmu_ops.tb_dev_attrib_attrs = tcmu_attrs;

	ret = transport_backend_रेजिस्टर(&tcmu_ops);
	अगर (ret)
		जाओ out_attrs;

	वापस 0;

out_attrs:
	kमुक्त(tcmu_attrs);
out_unreg_genl:
	genl_unरेजिस्टर_family(&tcmu_genl_family);
out_unreg_device:
	root_device_unरेजिस्टर(tcmu_root_device);
out_मुक्त_cache:
	kmem_cache_destroy(tcmu_cmd_cache);

	वापस ret;
पूर्ण

अटल व्योम __निकास tcmu_module_निकास(व्योम)
अणु
	cancel_delayed_work_sync(&tcmu_unmap_work);
	target_backend_unरेजिस्टर(&tcmu_ops);
	kमुक्त(tcmu_attrs);
	genl_unरेजिस्टर_family(&tcmu_genl_family);
	root_device_unरेजिस्टर(tcmu_root_device);
	kmem_cache_destroy(tcmu_cmd_cache);
पूर्ण

MODULE_DESCRIPTION("TCM USER subsystem plugin");
MODULE_AUTHOR("Shaohua Li <shli@kernel.org>");
MODULE_AUTHOR("Andy Grover <agrover@redhat.com>");
MODULE_LICENSE("GPL");

module_init(tcmu_module_init);
module_निकास(tcmu_module_निकास);
