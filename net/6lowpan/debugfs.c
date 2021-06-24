<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Authors:
 * (C) 2015 Pengutronix, Alexander Aring <aar@pengutronix.de>
 * Copyright (c)  2015 Nordic Semiconductor. All Rights Reserved.
 */

#समावेश <net/6lowpan.h>

#समावेश "6lowpan_i.h"

#घोषणा LOWPAN_DEBUGFS_CTX_PFX_NUM_ARGS	8

अटल काष्ठा dentry *lowpan_debugfs;

अटल पूर्णांक lowpan_ctx_flag_active_set(व्योम *data, u64 val)
अणु
	काष्ठा lowpan_iphc_ctx *ctx = data;

	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	अगर (val)
		set_bit(LOWPAN_IPHC_CTX_FLAG_ACTIVE, &ctx->flags);
	अन्यथा
		clear_bit(LOWPAN_IPHC_CTX_FLAG_ACTIVE, &ctx->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_ctx_flag_active_get(व्योम *data, u64 *val)
अणु
	*val = lowpan_iphc_ctx_is_active(data);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(lowpan_ctx_flag_active_fops,
			 lowpan_ctx_flag_active_get,
			 lowpan_ctx_flag_active_set, "%llu\n");

अटल पूर्णांक lowpan_ctx_flag_c_set(व्योम *data, u64 val)
अणु
	काष्ठा lowpan_iphc_ctx *ctx = data;

	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	अगर (val)
		set_bit(LOWPAN_IPHC_CTX_FLAG_COMPRESSION, &ctx->flags);
	अन्यथा
		clear_bit(LOWPAN_IPHC_CTX_FLAG_COMPRESSION, &ctx->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_ctx_flag_c_get(व्योम *data, u64 *val)
अणु
	*val = lowpan_iphc_ctx_is_compression(data);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(lowpan_ctx_flag_c_fops, lowpan_ctx_flag_c_get,
			 lowpan_ctx_flag_c_set, "%llu\n");

अटल पूर्णांक lowpan_ctx_plen_set(व्योम *data, u64 val)
अणु
	काष्ठा lowpan_iphc_ctx *ctx = data;
	काष्ठा lowpan_iphc_ctx_table *t =
		container_of(ctx, काष्ठा lowpan_iphc_ctx_table, table[ctx->id]);

	अगर (val > 128)
		वापस -EINVAL;

	spin_lock_bh(&t->lock);
	ctx->plen = val;
	spin_unlock_bh(&t->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_ctx_plen_get(व्योम *data, u64 *val)
अणु
	काष्ठा lowpan_iphc_ctx *ctx = data;
	काष्ठा lowpan_iphc_ctx_table *t =
		container_of(ctx, काष्ठा lowpan_iphc_ctx_table, table[ctx->id]);

	spin_lock_bh(&t->lock);
	*val = ctx->plen;
	spin_unlock_bh(&t->lock);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(lowpan_ctx_plen_fops, lowpan_ctx_plen_get,
			 lowpan_ctx_plen_set, "%llu\n");

अटल पूर्णांक lowpan_ctx_pfx_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा lowpan_iphc_ctx *ctx = file->निजी;
	काष्ठा lowpan_iphc_ctx_table *t =
		container_of(ctx, काष्ठा lowpan_iphc_ctx_table, table[ctx->id]);

	spin_lock_bh(&t->lock);
	seq_म_लिखो(file, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
		   be16_to_cpu(ctx->pfx.s6_addr16[0]),
		   be16_to_cpu(ctx->pfx.s6_addr16[1]),
		   be16_to_cpu(ctx->pfx.s6_addr16[2]),
		   be16_to_cpu(ctx->pfx.s6_addr16[3]),
		   be16_to_cpu(ctx->pfx.s6_addr16[4]),
		   be16_to_cpu(ctx->pfx.s6_addr16[5]),
		   be16_to_cpu(ctx->pfx.s6_addr16[6]),
		   be16_to_cpu(ctx->pfx.s6_addr16[7]));
	spin_unlock_bh(&t->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_ctx_pfx_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, lowpan_ctx_pfx_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार lowpan_ctx_pfx_ग_लिखो(काष्ठा file *fp,
				    स्थिर अक्षर __user *user_buf, माप_प्रकार count,
				    loff_t *ppos)
अणु
	अक्षर buf[128] = अणुपूर्ण;
	काष्ठा seq_file *file = fp->निजी_data;
	काष्ठा lowpan_iphc_ctx *ctx = file->निजी;
	काष्ठा lowpan_iphc_ctx_table *t =
		container_of(ctx, काष्ठा lowpan_iphc_ctx_table, table[ctx->id]);
	पूर्णांक status = count, n, i;
	अचिन्हित पूर्णांक addr[8];

	अगर (copy_from_user(&buf, user_buf, min_t(माप_प्रकार, माप(buf) - 1,
						 count))) अणु
		status = -EFAULT;
		जाओ out;
	पूर्ण

	n = माला_पूछो(buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
		   &addr[0], &addr[1], &addr[2], &addr[3], &addr[4],
		   &addr[5], &addr[6], &addr[7]);
	अगर (n != LOWPAN_DEBUGFS_CTX_PFX_NUM_ARGS) अणु
		status = -EINVAL;
		जाओ out;
	पूर्ण

	spin_lock_bh(&t->lock);
	क्रम (i = 0; i < 8; i++)
		ctx->pfx.s6_addr16[i] = cpu_to_be16(addr[i] & 0xffff);
	spin_unlock_bh(&t->lock);

out:
	वापस status;
पूर्ण

अटल स्थिर काष्ठा file_operations lowpan_ctx_pfx_fops = अणु
	.खोलो		= lowpan_ctx_pfx_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= lowpan_ctx_pfx_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल व्योम lowpan_dev_debugfs_ctx_init(काष्ठा net_device *dev,
					काष्ठा dentry *ctx, u8 id)
अणु
	काष्ठा lowpan_dev *ldev = lowpan_dev(dev);
	काष्ठा dentry *root;
	अक्षर buf[32];

	WARN_ON_ONCE(id > LOWPAN_IPHC_CTX_TABLE_SIZE);

	प्र_लिखो(buf, "%d", id);

	root = debugfs_create_dir(buf, ctx);

	debugfs_create_file("active", 0644, root, &ldev->ctx.table[id],
			    &lowpan_ctx_flag_active_fops);

	debugfs_create_file("compression", 0644, root, &ldev->ctx.table[id],
			    &lowpan_ctx_flag_c_fops);

	debugfs_create_file("prefix", 0644, root, &ldev->ctx.table[id],
			    &lowpan_ctx_pfx_fops);

	debugfs_create_file("prefix_len", 0644, root, &ldev->ctx.table[id],
			    &lowpan_ctx_plen_fops);
पूर्ण

अटल पूर्णांक lowpan_context_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा lowpan_iphc_ctx_table *t = file->निजी;
	पूर्णांक i;

	seq_म_लिखो(file, "%3s|%-43s|%c\n", "cid", "prefix", 'C');
	seq_माला_दो(file, "-------------------------------------------------\n");

	spin_lock_bh(&t->lock);
	क्रम (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++) अणु
		अगर (!lowpan_iphc_ctx_is_active(&t->table[i]))
			जारी;

		seq_म_लिखो(file, "%3d|%39pI6c/%-3d|%d\n", t->table[i].id,
			   &t->table[i].pfx, t->table[i].plen,
			   lowpan_iphc_ctx_is_compression(&t->table[i]));
	पूर्ण
	spin_unlock_bh(&t->lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(lowpan_context);

अटल पूर्णांक lowpan_लघु_addr_get(व्योम *data, u64 *val)
अणु
	काष्ठा wpan_dev *wdev = data;

	rtnl_lock();
	*val = le16_to_cpu(wdev->लघु_addr);
	rtnl_unlock();

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(lowpan_लघु_addr_fops, lowpan_लघु_addr_get, शून्य,
			 "0x%04llx\n");

अटल व्योम lowpan_dev_debugfs_802154_init(स्थिर काष्ठा net_device *dev,
					  काष्ठा lowpan_dev *ldev)
अणु
	काष्ठा dentry *root;

	अगर (!lowpan_is_ll(dev, LOWPAN_LLTYPE_IEEE802154))
		वापस;

	root = debugfs_create_dir("ieee802154", ldev->अगरace_debugfs);

	debugfs_create_file("short_addr", 0444, root,
			    lowpan_802154_dev(dev)->wdev->ieee802154_ptr,
			    &lowpan_लघु_addr_fops);
पूर्ण

व्योम lowpan_dev_debugfs_init(काष्ठा net_device *dev)
अणु
	काष्ठा lowpan_dev *ldev = lowpan_dev(dev);
	काष्ठा dentry *contexts;
	पूर्णांक i;

	/* creating the root */
	ldev->अगरace_debugfs = debugfs_create_dir(dev->name, lowpan_debugfs);

	contexts = debugfs_create_dir("contexts", ldev->अगरace_debugfs);

	debugfs_create_file("show", 0644, contexts, &lowpan_dev(dev)->ctx,
			    &lowpan_context_fops);

	क्रम (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++)
		lowpan_dev_debugfs_ctx_init(dev, contexts, i);

	lowpan_dev_debugfs_802154_init(dev, ldev);
पूर्ण

व्योम lowpan_dev_debugfs_निकास(काष्ठा net_device *dev)
अणु
	debugfs_हटाओ_recursive(lowpan_dev(dev)->अगरace_debugfs);
पूर्ण

व्योम __init lowpan_debugfs_init(व्योम)
अणु
	lowpan_debugfs = debugfs_create_dir("6lowpan", शून्य);
पूर्ण

व्योम lowpan_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(lowpan_debugfs);
पूर्ण
