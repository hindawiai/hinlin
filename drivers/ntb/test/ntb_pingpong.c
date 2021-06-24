<शैली गुरु>
/*
 *   This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *   Copyright (C) 2017 T-Platक्रमms. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License क्रम more details.
 *
 *   BSD LICENSE
 *
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *   Copyright (C) 2017 T-Platक्रमms. All Rights Reserved.
 *
 *   Redistribution and use in source and binary क्रमms, with or without
 *   modअगरication, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copy
 *       notice, this list of conditions and the following disclaimer in
 *       the करोcumentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to enकरोrse or promote products derived
 *       from this software without specअगरic prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * PCIe NTB Pingpong Linux driver
 */

/*
 * How to use this tool, by example.
 *
 * Assuming $DBG_सूची is something like:
 * '/sys/kernel/debug/ntb_perf/0000:00:03.0'
 * Suppose aside from local device there is at least one remote device
 * connected to NTB with index 0.
 *-----------------------------------------------------------------------------
 * Eg: install driver with specअगरied delay between करोorbell event and response
 *
 * root@self# insmod ntb_pingpong.ko delay_ms=1000
 *-----------------------------------------------------------------------------
 * Eg: get number of ping-pong cycles perक्रमmed
 *
 * root@self# cat $DBG_सूची/count
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/bitops.h>

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/ntb.h>

#घोषणा DRIVER_NAME		"ntb_pingpong"
#घोषणा DRIVER_VERSION		"2.0"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(DRIVER_VERSION);
MODULE_AUTHOR("Allen Hubbe <Allen.Hubbe@emc.com>");
MODULE_DESCRIPTION("PCIe NTB Simple Pingpong Client");

अटल अचिन्हित पूर्णांक unsafe;
module_param(unsafe, uपूर्णांक, 0644);
MODULE_PARM_DESC(unsafe, "Run even though ntb operations may be unsafe");

अटल अचिन्हित पूर्णांक delay_ms = 1000;
module_param(delay_ms, uपूर्णांक, 0644);
MODULE_PARM_DESC(delay_ms, "Milliseconds to delay the response to peer");

काष्ठा pp_ctx अणु
	काष्ठा ntb_dev *ntb;
	काष्ठा hrसमयr समयr;
	u64 in_db;
	u64 out_db;
	पूर्णांक out_pidx;
	u64 nmask;
	u64 pmask;
	atomic_t count;
	spinlock_t lock;
	काष्ठा dentry *dbgfs_dir;
पूर्ण;
#घोषणा to_pp_समयr(__समयr) \
	container_of(__समयr, काष्ठा pp_ctx, समयr)

अटल काष्ठा dentry *pp_dbgfs_topdir;

अटल पूर्णांक pp_find_next_peer(काष्ठा pp_ctx *pp)
अणु
	u64 link, out_db;
	पूर्णांक pidx;

	link = ntb_link_is_up(pp->ntb, शून्य, शून्य);

	/* Find next available peer */
	अगर (link & pp->nmask)
		pidx = __ffs64(link & pp->nmask);
	अन्यथा अगर (link & pp->pmask)
		pidx = __ffs64(link & pp->pmask);
	अन्यथा
		वापस -ENODEV;

	out_db = BIT_ULL(ntb_peer_port_number(pp->ntb, pidx));

	spin_lock(&pp->lock);
	pp->out_pidx = pidx;
	pp->out_db = out_db;
	spin_unlock(&pp->lock);

	वापस 0;
पूर्ण

अटल व्योम pp_setup(काष्ठा pp_ctx *pp)
अणु
	पूर्णांक ret;

	ntb_db_set_mask(pp->ntb, pp->in_db);

	hrसमयr_cancel(&pp->समयr);

	ret = pp_find_next_peer(pp);
	अगर (ret == -ENODEV) अणु
		dev_dbg(&pp->ntb->dev, "Got no peers, so cancel\n");
		वापस;
	पूर्ण

	dev_dbg(&pp->ntb->dev, "Ping-pong started with port %d, db %#llx\n",
		ntb_peer_port_number(pp->ntb, pp->out_pidx), pp->out_db);

	hrसमयr_start(&pp->समयr, ms_to_kसमय(delay_ms), HRTIMER_MODE_REL);
पूर्ण

अटल व्योम pp_clear(काष्ठा pp_ctx *pp)
अणु
	hrसमयr_cancel(&pp->समयr);

	ntb_db_set_mask(pp->ntb, pp->in_db);

	dev_dbg(&pp->ntb->dev, "Ping-pong cancelled\n");
पूर्ण

अटल व्योम pp_ping(काष्ठा pp_ctx *pp)
अणु
	u32 count;

	count = atomic_पढ़ो(&pp->count);

	spin_lock(&pp->lock);
	ntb_peer_spad_ग_लिखो(pp->ntb, pp->out_pidx, 0, count);
	ntb_peer_msg_ग_लिखो(pp->ntb, pp->out_pidx, 0, count);

	dev_dbg(&pp->ntb->dev, "Ping port %d spad %#x, msg %#x\n",
		ntb_peer_port_number(pp->ntb, pp->out_pidx), count, count);

	ntb_peer_db_set(pp->ntb, pp->out_db);
	ntb_db_clear_mask(pp->ntb, pp->in_db);
	spin_unlock(&pp->lock);
पूर्ण

अटल व्योम pp_pong(काष्ठा pp_ctx *pp)
अणु
	u32 msg_data = -1, spad_data = -1;
	पूर्णांक pidx = 0;

	/* Read pong data */
	spad_data = ntb_spad_पढ़ो(pp->ntb, 0);
	msg_data = ntb_msg_पढ़ो(pp->ntb, &pidx, 0);
	ntb_msg_clear_sts(pp->ntb, -1);

	/*
	 * Scratchpad and message data may dअगरfer, since message रेजिस्टर can't
	 * be rewritten unless status is cleared. Additionally either of them
	 * might be unsupported
	 */
	dev_dbg(&pp->ntb->dev, "Pong spad %#x, msg %#x (port %d)\n",
		spad_data, msg_data, ntb_peer_port_number(pp->ntb, pidx));

	atomic_inc(&pp->count);

	ntb_db_set_mask(pp->ntb, pp->in_db);
	ntb_db_clear(pp->ntb, pp->in_db);

	hrसमयr_start(&pp->समयr, ms_to_kसमय(delay_ms), HRTIMER_MODE_REL);
पूर्ण

अटल क्रमागत hrसमयr_restart pp_समयr_func(काष्ठा hrसमयr *t)
अणु
	काष्ठा pp_ctx *pp = to_pp_समयr(t);

	pp_ping(pp);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम pp_link_event(व्योम *ctx)
अणु
	काष्ठा pp_ctx *pp = ctx;

	pp_setup(pp);
पूर्ण

अटल व्योम pp_db_event(व्योम *ctx, पूर्णांक vec)
अणु
	काष्ठा pp_ctx *pp = ctx;

	pp_pong(pp);
पूर्ण

अटल स्थिर काष्ठा ntb_ctx_ops pp_ops = अणु
	.link_event = pp_link_event,
	.db_event = pp_db_event
पूर्ण;

अटल पूर्णांक pp_check_ntb(काष्ठा ntb_dev *ntb)
अणु
	u64 pmask;

	अगर (ntb_db_is_unsafe(ntb)) अणु
		dev_dbg(&ntb->dev, "Doorbell is unsafe\n");
		अगर (!unsafe)
			वापस -EINVAL;
	पूर्ण

	अगर (ntb_spad_is_unsafe(ntb)) अणु
		dev_dbg(&ntb->dev, "Scratchpad is unsafe\n");
		अगर (!unsafe)
			वापस -EINVAL;
	पूर्ण

	pmask = GENMASK_ULL(ntb_peer_port_count(ntb), 0);
	अगर ((ntb_db_valid_mask(ntb) & pmask) != pmask) अणु
		dev_err(&ntb->dev, "Unsupported DB configuration\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ntb_spad_count(ntb) < 1 && ntb_msg_count(ntb) < 1) अणु
		dev_err(&ntb->dev, "Scratchpads and messages unsupported\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (ntb_spad_count(ntb) < 1) अणु
		dev_dbg(&ntb->dev, "Scratchpads unsupported\n");
	पूर्ण अन्यथा अगर (ntb_msg_count(ntb) < 1) अणु
		dev_dbg(&ntb->dev, "Messages unsupported\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pp_ctx *pp_create_data(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा pp_ctx *pp;

	pp = devm_kzalloc(&ntb->dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस ERR_PTR(-ENOMEM);

	pp->ntb = ntb;
	atomic_set(&pp->count, 0);
	spin_lock_init(&pp->lock);
	hrसमयr_init(&pp->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	pp->समयr.function = pp_समयr_func;

	वापस pp;
पूर्ण

अटल व्योम pp_init_flds(काष्ठा pp_ctx *pp)
अणु
	पूर्णांक pidx, lport, pcnt;

	/* Find global port index */
	lport = ntb_port_number(pp->ntb);
	pcnt = ntb_peer_port_count(pp->ntb);
	क्रम (pidx = 0; pidx < pcnt; pidx++) अणु
		अगर (lport < ntb_peer_port_number(pp->ntb, pidx))
			अवरोध;
	पूर्ण

	pp->in_db = BIT_ULL(lport);
	pp->pmask = GENMASK_ULL(pidx, 0) >> 1;
	pp->nmask = GENMASK_ULL(pcnt - 1, pidx);

	dev_dbg(&pp->ntb->dev, "Inbound db %#llx, prev %#llx, next %#llx\n",
		pp->in_db, pp->pmask, pp->nmask);
पूर्ण

अटल पूर्णांक pp_mask_events(काष्ठा pp_ctx *pp)
अणु
	u64 db_mask, msg_mask;
	पूर्णांक ret;

	db_mask = ntb_db_valid_mask(pp->ntb);
	ret = ntb_db_set_mask(pp->ntb, db_mask);
	अगर (ret)
		वापस ret;

	/* Skip message events masking अगर unsupported */
	अगर (ntb_msg_count(pp->ntb) < 1)
		वापस 0;

	msg_mask = ntb_msg_outbits(pp->ntb) | ntb_msg_inbits(pp->ntb);
	वापस ntb_msg_set_mask(pp->ntb, msg_mask);
पूर्ण

अटल पूर्णांक pp_setup_ctx(काष्ठा pp_ctx *pp)
अणु
	पूर्णांक ret;

	ret = ntb_set_ctx(pp->ntb, pp, &pp_ops);
	अगर (ret)
		वापस ret;

	ntb_link_enable(pp->ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	/* Might be not necessary */
	ntb_link_event(pp->ntb);

	वापस 0;
पूर्ण

अटल व्योम pp_clear_ctx(काष्ठा pp_ctx *pp)
अणु
	ntb_link_disable(pp->ntb);

	ntb_clear_ctx(pp->ntb);
पूर्ण

अटल व्योम pp_setup_dbgfs(काष्ठा pp_ctx *pp)
अणु
	काष्ठा pci_dev *pdev = pp->ntb->pdev;

	pp->dbgfs_dir = debugfs_create_dir(pci_name(pdev), pp_dbgfs_topdir);

	debugfs_create_atomic_t("count", 0600, pp->dbgfs_dir, &pp->count);
पूर्ण

अटल व्योम pp_clear_dbgfs(काष्ठा pp_ctx *pp)
अणु
	debugfs_हटाओ_recursive(pp->dbgfs_dir);
पूर्ण

अटल पूर्णांक pp_probe(काष्ठा ntb_client *client, काष्ठा ntb_dev *ntb)
अणु
	काष्ठा pp_ctx *pp;
	पूर्णांक ret;

	ret = pp_check_ntb(ntb);
	अगर (ret)
		वापस ret;

	pp = pp_create_data(ntb);
	अगर (IS_ERR(pp))
		वापस PTR_ERR(pp);

	pp_init_flds(pp);

	ret = pp_mask_events(pp);
	अगर (ret)
		वापस ret;

	ret = pp_setup_ctx(pp);
	अगर (ret)
		वापस ret;

	pp_setup_dbgfs(pp);

	वापस 0;
पूर्ण

अटल व्योम pp_हटाओ(काष्ठा ntb_client *client, काष्ठा ntb_dev *ntb)
अणु
	काष्ठा pp_ctx *pp = ntb->ctx;

	pp_clear_dbgfs(pp);

	pp_clear_ctx(pp);

	pp_clear(pp);
पूर्ण

अटल काष्ठा ntb_client pp_client = अणु
	.ops = अणु
		.probe = pp_probe,
		.हटाओ = pp_हटाओ
	पूर्ण
पूर्ण;

अटल पूर्णांक __init pp_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (debugfs_initialized())
		pp_dbgfs_topdir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	ret = ntb_रेजिस्टर_client(&pp_client);
	अगर (ret)
		debugfs_हटाओ_recursive(pp_dbgfs_topdir);

	वापस ret;
पूर्ण
module_init(pp_init);

अटल व्योम __निकास pp_निकास(व्योम)
अणु
	ntb_unरेजिस्टर_client(&pp_client);
	debugfs_हटाओ_recursive(pp_dbgfs_topdir);
पूर्ण
module_निकास(pp_निकास);
