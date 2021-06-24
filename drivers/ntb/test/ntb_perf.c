<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2015 Intel Corporation. All rights reserved.
 *   Copyright(c) 2017 T-Platक्रमms. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2015 Intel Corporation. All rights reserved.
 *   Copyright(c) 2017 T-Platक्रमms. All Rights Reserved.
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
 * PCIe NTB Perf Linux driver
 */

/*
 * How to use this tool, by example.
 *
 * Assuming $DBG_सूची is something like:
 * '/sys/kernel/debug/ntb_perf/0000:00:03.0'
 * Suppose aside from local device there is at least one remote device
 * connected to NTB with index 0.
 *-----------------------------------------------------------------------------
 * Eg: install driver with specअगरied chunk/total orders and dma-enabled flag
 *
 * root@self# insmod ntb_perf.ko chunk_order=19 total_order=28 use_dma
 *-----------------------------------------------------------------------------
 * Eg: check NTB ports (index) and MW mapping inक्रमmation
 *
 * root@self# cat $DBG_सूची/info
 *-----------------------------------------------------------------------------
 * Eg: start perक्रमmance test with peer (index 0) and get the test metrics
 *
 * root@self# echo 0 > $DBG_सूची/run
 * root@self# cat $DBG_सूची/run
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pci.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/sizes.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/ntb.h>

#घोषणा DRIVER_NAME		"ntb_perf"
#घोषणा DRIVER_VERSION		"2.0"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(DRIVER_VERSION);
MODULE_AUTHOR("Dave Jiang <dave.jiang@intel.com>");
MODULE_DESCRIPTION("PCIe NTB Performance Measurement Tool");

#घोषणा MAX_THREADS_CNT		32
#घोषणा DEF_THREADS_CNT		1
#घोषणा MAX_CHUNK_SIZE		SZ_1M
#घोषणा MAX_CHUNK_ORDER		20 /* no larger than 1M */

#घोषणा DMA_TRIES		100
#घोषणा DMA_MDELAY		10

#घोषणा MSG_TRIES		1000
#घोषणा MSG_UDELAY_LOW		1000000
#घोषणा MSG_UDELAY_HIGH		2000000

#घोषणा PERF_BUF_LEN 1024

अटल अचिन्हित दीर्घ max_mw_size;
module_param(max_mw_size, uदीर्घ, 0644);
MODULE_PARM_DESC(max_mw_size, "Upper limit of memory window size");

अटल अचिन्हित अक्षर chunk_order = 19; /* 512K */
module_param(chunk_order, byte, 0644);
MODULE_PARM_DESC(chunk_order, "Data chunk order [2^n] to transfer");

अटल अचिन्हित अक्षर total_order = 30; /* 1G */
module_param(total_order, byte, 0644);
MODULE_PARM_DESC(total_order, "Total data order [2^n] to transfer");

अटल bool use_dma; /* शेष to 0 */
module_param(use_dma, bool, 0644);
MODULE_PARM_DESC(use_dma, "Use DMA engine to measure performance");

/*==============================================================================
 *                         Perf driver data definition
 *==============================================================================
 */

क्रमागत perf_cmd अणु
	PERF_CMD_INVAL = -1,/* invalid spad command */
	PERF_CMD_SSIZE = 0, /* send out buffer size */
	PERF_CMD_RSIZE = 1, /* recv in  buffer size */
	PERF_CMD_SXLAT = 2, /* send in  buffer xlat */
	PERF_CMD_RXLAT = 3, /* recv out buffer xlat */
	PERF_CMD_CLEAR = 4, /* clear allocated memory */
	PERF_STS_DONE  = 5, /* init is करोne */
	PERF_STS_LNKUP = 6, /* link up state flag */
पूर्ण;

काष्ठा perf_ctx;

काष्ठा perf_peer अणु
	काष्ठा perf_ctx	*perf;
	पूर्णांक pidx;
	पूर्णांक gidx;

	/* Outbound MW params */
	u64 outbuf_xlat;
	resource_माप_प्रकार outbuf_size;
	व्योम __iomem *outbuf;
	phys_addr_t out_phys_addr;
	dma_addr_t dma_dst_addr;
	/* Inbound MW params */
	dma_addr_t inbuf_xlat;
	resource_माप_प्रकार inbuf_size;
	व्योम		*inbuf;

	/* NTB connection setup service */
	काष्ठा work_काष्ठा	service;
	अचिन्हित दीर्घ		sts;

	काष्ठा completion init_comp;
पूर्ण;
#घोषणा to_peer_service(__work) \
	container_of(__work, काष्ठा perf_peer, service)

काष्ठा perf_thपढ़ो अणु
	काष्ठा perf_ctx *perf;
	पूर्णांक tidx;

	/* DMA-based test sync parameters */
	atomic_t dma_sync;
	रुको_queue_head_t dma_रुको;
	काष्ठा dma_chan *dma_chan;

	/* Data source and measured statistics */
	व्योम *src;
	u64 copied;
	kसमय_प्रकार duration;
	पूर्णांक status;
	काष्ठा work_काष्ठा work;
पूर्ण;
#घोषणा to_thपढ़ो_work(__work) \
	container_of(__work, काष्ठा perf_thपढ़ो, work)

काष्ठा perf_ctx अणु
	काष्ठा ntb_dev *ntb;

	/* Global device index and peers descriptors */
	पूर्णांक gidx;
	पूर्णांक pcnt;
	काष्ठा perf_peer *peers;

	/* Perक्रमmance measuring work-thपढ़ोs पूर्णांकerface */
	अचिन्हित दीर्घ busy_flag;
	रुको_queue_head_t tरुको;
	atomic_t tsync;
	u8 tcnt;
	काष्ठा perf_peer *test_peer;
	काष्ठा perf_thपढ़ो thपढ़ोs[MAX_THREADS_CNT];

	/* Scratchpad/Message IO operations */
	पूर्णांक (*cmd_send)(काष्ठा perf_peer *peer, क्रमागत perf_cmd cmd, u64 data);
	पूर्णांक (*cmd_recv)(काष्ठा perf_ctx *perf, पूर्णांक *pidx, क्रमागत perf_cmd *cmd,
			u64 *data);

	काष्ठा dentry *dbgfs_dir;
पूर्ण;

/*
 * Scratchpads-base commands पूर्णांकerface
 */
#घोषणा PERF_SPAD_CNT(_pcnt) \
	(3*((_pcnt) + 1))
#घोषणा PERF_SPAD_CMD(_gidx) \
	(3*(_gidx))
#घोषणा PERF_SPAD_LDATA(_gidx) \
	(3*(_gidx) + 1)
#घोषणा PERF_SPAD_HDATA(_gidx) \
	(3*(_gidx) + 2)
#घोषणा PERF_SPAD_NOTIFY(_gidx) \
	(BIT_ULL(_gidx))

/*
 * Messages-base commands पूर्णांकerface
 */
#घोषणा PERF_MSG_CNT		3
#घोषणा PERF_MSG_CMD		0
#घोषणा PERF_MSG_LDATA		1
#घोषणा PERF_MSG_HDATA		2

/*==============================================================================
 *                           Static data declarations
 *==============================================================================
 */

अटल काष्ठा dentry *perf_dbgfs_topdir;

अटल काष्ठा workqueue_काष्ठा *perf_wq __पढ़ो_mostly;

/*==============================================================================
 *                  NTB cross-link commands execution service
 *==============================================================================
 */

अटल व्योम perf_terminate_test(काष्ठा perf_ctx *perf);

अटल अंतरभूत bool perf_link_is_up(काष्ठा perf_peer *peer)
अणु
	u64 link;

	link = ntb_link_is_up(peer->perf->ntb, शून्य, शून्य);
	वापस !!(link & BIT_ULL_MASK(peer->pidx));
पूर्ण

अटल पूर्णांक perf_spad_cmd_send(काष्ठा perf_peer *peer, क्रमागत perf_cmd cmd,
			      u64 data)
अणु
	काष्ठा perf_ctx *perf = peer->perf;
	पूर्णांक try;
	u32 sts;

	dev_dbg(&perf->ntb->dev, "CMD send: %d 0x%llx\n", cmd, data);

	/*
	 * Perक्रमm predefined number of attempts beक्रमe give up.
	 * We are sending the data to the port specअगरic scratchpad, so
	 * to prevent a multi-port access race-condition. Additionally
	 * there is no need in local locking since only thपढ़ो-safe
	 * service work is using this method.
	 */
	क्रम (try = 0; try < MSG_TRIES; try++) अणु
		अगर (!perf_link_is_up(peer))
			वापस -ENOLINK;

		sts = ntb_peer_spad_पढ़ो(perf->ntb, peer->pidx,
					 PERF_SPAD_CMD(perf->gidx));
		अगर (sts != PERF_CMD_INVAL) अणु
			usleep_range(MSG_UDELAY_LOW, MSG_UDELAY_HIGH);
			जारी;
		पूर्ण

		ntb_peer_spad_ग_लिखो(perf->ntb, peer->pidx,
				    PERF_SPAD_LDATA(perf->gidx),
				    lower_32_bits(data));
		ntb_peer_spad_ग_लिखो(perf->ntb, peer->pidx,
				    PERF_SPAD_HDATA(perf->gidx),
				    upper_32_bits(data));
		ntb_peer_spad_ग_लिखो(perf->ntb, peer->pidx,
				    PERF_SPAD_CMD(perf->gidx),
				    cmd);
		ntb_peer_db_set(perf->ntb, PERF_SPAD_NOTIFY(peer->gidx));

		dev_dbg(&perf->ntb->dev, "DB ring peer %#llx\n",
			PERF_SPAD_NOTIFY(peer->gidx));

		अवरोध;
	पूर्ण

	वापस try < MSG_TRIES ? 0 : -EAGAIN;
पूर्ण

अटल पूर्णांक perf_spad_cmd_recv(काष्ठा perf_ctx *perf, पूर्णांक *pidx,
			      क्रमागत perf_cmd *cmd, u64 *data)
अणु
	काष्ठा perf_peer *peer;
	u32 val;

	ntb_db_clear(perf->ntb, PERF_SPAD_NOTIFY(perf->gidx));

	/*
	 * We start scanning all over, since cleared DB may have been set
	 * by any peer. Yes, it makes peer with smaller index being
	 * serviced with greater priority, but it's convenient क्रम spad
	 * and message code unअगरication and simplicity.
	 */
	क्रम (*pidx = 0; *pidx < perf->pcnt; (*pidx)++) अणु
		peer = &perf->peers[*pidx];

		अगर (!perf_link_is_up(peer))
			जारी;

		val = ntb_spad_पढ़ो(perf->ntb, PERF_SPAD_CMD(peer->gidx));
		अगर (val == PERF_CMD_INVAL)
			जारी;

		*cmd = val;

		val = ntb_spad_पढ़ो(perf->ntb, PERF_SPAD_LDATA(peer->gidx));
		*data = val;

		val = ntb_spad_पढ़ो(perf->ntb, PERF_SPAD_HDATA(peer->gidx));
		*data |= (u64)val << 32;

		/* Next command can be retrieved from now */
		ntb_spad_ग_लिखो(perf->ntb, PERF_SPAD_CMD(peer->gidx),
			       PERF_CMD_INVAL);

		dev_dbg(&perf->ntb->dev, "CMD recv: %d 0x%llx\n", *cmd, *data);

		वापस 0;
	पूर्ण

	वापस -ENODATA;
पूर्ण

अटल पूर्णांक perf_msg_cmd_send(काष्ठा perf_peer *peer, क्रमागत perf_cmd cmd,
			     u64 data)
अणु
	काष्ठा perf_ctx *perf = peer->perf;
	पूर्णांक try, ret;
	u64 outbits;

	dev_dbg(&perf->ntb->dev, "CMD send: %d 0x%llx\n", cmd, data);

	/*
	 * Perक्रमm predefined number of attempts beक्रमe give up. Message
	 * रेजिस्टरs are मुक्त of race-condition problem when accessed
	 * from dअगरferent ports, so we करोn't need splitting रेजिस्टरs
	 * by global device index. We also won't have local locking,
	 * since the method is used from service work only.
	 */
	outbits = ntb_msg_outbits(perf->ntb);
	क्रम (try = 0; try < MSG_TRIES; try++) अणु
		अगर (!perf_link_is_up(peer))
			वापस -ENOLINK;

		ret = ntb_msg_clear_sts(perf->ntb, outbits);
		अगर (ret)
			वापस ret;

		ntb_peer_msg_ग_लिखो(perf->ntb, peer->pidx, PERF_MSG_LDATA,
				   lower_32_bits(data));

		अगर (ntb_msg_पढ़ो_sts(perf->ntb) & outbits) अणु
			usleep_range(MSG_UDELAY_LOW, MSG_UDELAY_HIGH);
			जारी;
		पूर्ण

		ntb_peer_msg_ग_लिखो(perf->ntb, peer->pidx, PERF_MSG_HDATA,
				   upper_32_bits(data));

		/* This call shall trigger peer message event */
		ntb_peer_msg_ग_लिखो(perf->ntb, peer->pidx, PERF_MSG_CMD, cmd);

		अवरोध;
	पूर्ण

	वापस try < MSG_TRIES ? 0 : -EAGAIN;
पूर्ण

अटल पूर्णांक perf_msg_cmd_recv(काष्ठा perf_ctx *perf, पूर्णांक *pidx,
			     क्रमागत perf_cmd *cmd, u64 *data)
अणु
	u64 inbits;
	u32 val;

	inbits = ntb_msg_inbits(perf->ntb);

	अगर (hweight64(ntb_msg_पढ़ो_sts(perf->ntb) & inbits) < 3)
		वापस -ENODATA;

	val = ntb_msg_पढ़ो(perf->ntb, pidx, PERF_MSG_CMD);
	*cmd = val;

	val = ntb_msg_पढ़ो(perf->ntb, pidx, PERF_MSG_LDATA);
	*data = val;

	val = ntb_msg_पढ़ो(perf->ntb, pidx, PERF_MSG_HDATA);
	*data |= (u64)val << 32;

	/* Next command can be retrieved from now */
	ntb_msg_clear_sts(perf->ntb, inbits);

	dev_dbg(&perf->ntb->dev, "CMD recv: %d 0x%llx\n", *cmd, *data);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_cmd_send(काष्ठा perf_peer *peer, क्रमागत perf_cmd cmd, u64 data)
अणु
	काष्ठा perf_ctx *perf = peer->perf;

	अगर (cmd == PERF_CMD_SSIZE || cmd == PERF_CMD_SXLAT)
		वापस perf->cmd_send(peer, cmd, data);

	dev_err(&perf->ntb->dev, "Send invalid command\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक perf_cmd_exec(काष्ठा perf_peer *peer, क्रमागत perf_cmd cmd)
अणु
	चयन (cmd) अणु
	हाल PERF_CMD_SSIZE:
	हाल PERF_CMD_RSIZE:
	हाल PERF_CMD_SXLAT:
	हाल PERF_CMD_RXLAT:
	हाल PERF_CMD_CLEAR:
		अवरोध;
	शेष:
		dev_err(&peer->perf->ntb->dev, "Exec invalid command\n");
		वापस -EINVAL;
	पूर्ण

	/* No need of memory barrier, since bit ops have invernal lock */
	set_bit(cmd, &peer->sts);

	dev_dbg(&peer->perf->ntb->dev, "CMD exec: %d\n", cmd);

	(व्योम)queue_work(प्रणाली_highpri_wq, &peer->service);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_cmd_recv(काष्ठा perf_ctx *perf)
अणु
	काष्ठा perf_peer *peer;
	पूर्णांक ret, pidx, cmd;
	u64 data;

	जबतक (!(ret = perf->cmd_recv(perf, &pidx, &cmd, &data))) अणु
		peer = &perf->peers[pidx];

		चयन (cmd) अणु
		हाल PERF_CMD_SSIZE:
			peer->inbuf_size = data;
			वापस perf_cmd_exec(peer, PERF_CMD_RSIZE);
		हाल PERF_CMD_SXLAT:
			peer->outbuf_xlat = data;
			वापस perf_cmd_exec(peer, PERF_CMD_RXLAT);
		शेष:
			dev_err(&perf->ntb->dev, "Recv invalid command\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Return 0 अगर no data left to process, otherwise an error */
	वापस ret == -ENODATA ? 0 : ret;
पूर्ण

अटल व्योम perf_link_event(व्योम *ctx)
अणु
	काष्ठा perf_ctx *perf = ctx;
	काष्ठा perf_peer *peer;
	bool lnk_up;
	पूर्णांक pidx;

	क्रम (pidx = 0; pidx < perf->pcnt; pidx++) अणु
		peer = &perf->peers[pidx];

		lnk_up = perf_link_is_up(peer);

		अगर (lnk_up &&
		    !test_and_set_bit(PERF_STS_LNKUP, &peer->sts)) अणु
			perf_cmd_exec(peer, PERF_CMD_SSIZE);
		पूर्ण अन्यथा अगर (!lnk_up &&
			   test_and_clear_bit(PERF_STS_LNKUP, &peer->sts)) अणु
			perf_cmd_exec(peer, PERF_CMD_CLEAR);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम perf_db_event(व्योम *ctx, पूर्णांक vec)
अणु
	काष्ठा perf_ctx *perf = ctx;

	dev_dbg(&perf->ntb->dev, "DB vec %d mask %#llx bits %#llx\n", vec,
		ntb_db_vector_mask(perf->ntb, vec), ntb_db_पढ़ो(perf->ntb));

	/* Just receive all available commands */
	(व्योम)perf_cmd_recv(perf);
पूर्ण

अटल व्योम perf_msg_event(व्योम *ctx)
अणु
	काष्ठा perf_ctx *perf = ctx;

	dev_dbg(&perf->ntb->dev, "Msg status bits %#llx\n",
		ntb_msg_पढ़ो_sts(perf->ntb));

	/* Messages are only sent one-by-one */
	(व्योम)perf_cmd_recv(perf);
पूर्ण

अटल स्थिर काष्ठा ntb_ctx_ops perf_ops = अणु
	.link_event = perf_link_event,
	.db_event = perf_db_event,
	.msg_event = perf_msg_event
पूर्ण;

अटल व्योम perf_मुक्त_outbuf(काष्ठा perf_peer *peer)
अणु
	(व्योम)ntb_peer_mw_clear_trans(peer->perf->ntb, peer->pidx, peer->gidx);
पूर्ण

अटल पूर्णांक perf_setup_outbuf(काष्ठा perf_peer *peer)
अणु
	काष्ठा perf_ctx *perf = peer->perf;
	पूर्णांक ret;

	/* Outbuf size can be unaligned due to custom max_mw_size */
	ret = ntb_peer_mw_set_trans(perf->ntb, peer->pidx, peer->gidx,
				    peer->outbuf_xlat, peer->outbuf_size);
	अगर (ret) अणु
		dev_err(&perf->ntb->dev, "Failed to set outbuf translation\n");
		वापस ret;
	पूर्ण

	/* Initialization is finally करोne */
	set_bit(PERF_STS_DONE, &peer->sts);
	complete_all(&peer->init_comp);

	वापस 0;
पूर्ण

अटल व्योम perf_मुक्त_inbuf(काष्ठा perf_peer *peer)
अणु
	अगर (!peer->inbuf)
		वापस;

	(व्योम)ntb_mw_clear_trans(peer->perf->ntb, peer->pidx, peer->gidx);
	dma_मुक्त_coherent(&peer->perf->ntb->pdev->dev, peer->inbuf_size,
			  peer->inbuf, peer->inbuf_xlat);
	peer->inbuf = शून्य;
पूर्ण

अटल पूर्णांक perf_setup_inbuf(काष्ठा perf_peer *peer)
अणु
	resource_माप_प्रकार xlat_align, size_align, size_max;
	काष्ठा perf_ctx *perf = peer->perf;
	पूर्णांक ret;

	/* Get inbound MW parameters */
	ret = ntb_mw_get_align(perf->ntb, peer->pidx, perf->gidx,
			       &xlat_align, &size_align, &size_max);
	अगर (ret) अणु
		dev_err(&perf->ntb->dev, "Couldn't get inbuf restrictions\n");
		वापस ret;
	पूर्ण

	अगर (peer->inbuf_size > size_max) अणु
		dev_err(&perf->ntb->dev, "Too big inbuf size %pa > %pa\n",
			&peer->inbuf_size, &size_max);
		वापस -EINVAL;
	पूर्ण

	peer->inbuf_size = round_up(peer->inbuf_size, size_align);

	perf_मुक्त_inbuf(peer);

	peer->inbuf = dma_alloc_coherent(&perf->ntb->pdev->dev,
					 peer->inbuf_size, &peer->inbuf_xlat,
					 GFP_KERNEL);
	अगर (!peer->inbuf) अणु
		dev_err(&perf->ntb->dev, "Failed to alloc inbuf of %pa\n",
			&peer->inbuf_size);
		वापस -ENOMEM;
	पूर्ण
	अगर (!IS_ALIGNED(peer->inbuf_xlat, xlat_align)) अणु
		dev_err(&perf->ntb->dev, "Unaligned inbuf allocated\n");
		जाओ err_मुक्त_inbuf;
	पूर्ण

	ret = ntb_mw_set_trans(perf->ntb, peer->pidx, peer->gidx,
			       peer->inbuf_xlat, peer->inbuf_size);
	अगर (ret) अणु
		dev_err(&perf->ntb->dev, "Failed to set inbuf translation\n");
		जाओ err_मुक्त_inbuf;
	पूर्ण

	/*
	 * We submit inbuf xlat transmission cmd क्रम execution here to follow
	 * the code architecture, even though this method is called from service
	 * work itself so the command will be executed right after it वापसs.
	 */
	(व्योम)perf_cmd_exec(peer, PERF_CMD_SXLAT);

	वापस 0;

err_मुक्त_inbuf:
	perf_मुक्त_inbuf(peer);

	वापस ret;
पूर्ण

अटल व्योम perf_service_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा perf_peer *peer = to_peer_service(work);

	अगर (test_and_clear_bit(PERF_CMD_SSIZE, &peer->sts))
		perf_cmd_send(peer, PERF_CMD_SSIZE, peer->outbuf_size);

	अगर (test_and_clear_bit(PERF_CMD_RSIZE, &peer->sts))
		perf_setup_inbuf(peer);

	अगर (test_and_clear_bit(PERF_CMD_SXLAT, &peer->sts))
		perf_cmd_send(peer, PERF_CMD_SXLAT, peer->inbuf_xlat);

	अगर (test_and_clear_bit(PERF_CMD_RXLAT, &peer->sts))
		perf_setup_outbuf(peer);

	अगर (test_and_clear_bit(PERF_CMD_CLEAR, &peer->sts)) अणु
		init_completion(&peer->init_comp);
		clear_bit(PERF_STS_DONE, &peer->sts);
		अगर (test_bit(0, &peer->perf->busy_flag) &&
		    peer == peer->perf->test_peer) अणु
			dev_warn(&peer->perf->ntb->dev,
				"Freeing while test on-fly\n");
			perf_terminate_test(peer->perf);
		पूर्ण
		perf_मुक्त_outbuf(peer);
		perf_मुक्त_inbuf(peer);
	पूर्ण
पूर्ण

अटल पूर्णांक perf_init_service(काष्ठा perf_ctx *perf)
अणु
	u64 mask;

	अगर (ntb_peer_mw_count(perf->ntb) < perf->pcnt) अणु
		dev_err(&perf->ntb->dev, "Not enough memory windows\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ntb_msg_count(perf->ntb) >= PERF_MSG_CNT) अणु
		perf->cmd_send = perf_msg_cmd_send;
		perf->cmd_recv = perf_msg_cmd_recv;

		dev_dbg(&perf->ntb->dev, "Message service initialized\n");

		वापस 0;
	पूर्ण

	dev_dbg(&perf->ntb->dev, "Message service unsupported\n");

	mask = GENMASK_ULL(perf->pcnt, 0);
	अगर (ntb_spad_count(perf->ntb) >= PERF_SPAD_CNT(perf->pcnt) &&
	    (ntb_db_valid_mask(perf->ntb) & mask) == mask) अणु
		perf->cmd_send = perf_spad_cmd_send;
		perf->cmd_recv = perf_spad_cmd_recv;

		dev_dbg(&perf->ntb->dev, "Scratchpad service initialized\n");

		वापस 0;
	पूर्ण

	dev_dbg(&perf->ntb->dev, "Scratchpad service unsupported\n");

	dev_err(&perf->ntb->dev, "Command services unsupported\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक perf_enable_service(काष्ठा perf_ctx *perf)
अणु
	u64 mask, incmd_bit;
	पूर्णांक ret, sidx, scnt;

	mask = ntb_db_valid_mask(perf->ntb);
	(व्योम)ntb_db_set_mask(perf->ntb, mask);

	ret = ntb_set_ctx(perf->ntb, perf, &perf_ops);
	अगर (ret)
		वापस ret;

	अगर (perf->cmd_send == perf_msg_cmd_send) अणु
		u64 inbits, outbits;

		inbits = ntb_msg_inbits(perf->ntb);
		outbits = ntb_msg_outbits(perf->ntb);
		(व्योम)ntb_msg_set_mask(perf->ntb, inbits | outbits);

		incmd_bit = BIT_ULL(__ffs64(inbits));
		ret = ntb_msg_clear_mask(perf->ntb, incmd_bit);

		dev_dbg(&perf->ntb->dev, "MSG sts unmasked %#llx\n", incmd_bit);
	पूर्ण अन्यथा अणु
		scnt = ntb_spad_count(perf->ntb);
		क्रम (sidx = 0; sidx < scnt; sidx++)
			ntb_spad_ग_लिखो(perf->ntb, sidx, PERF_CMD_INVAL);
		incmd_bit = PERF_SPAD_NOTIFY(perf->gidx);
		ret = ntb_db_clear_mask(perf->ntb, incmd_bit);

		dev_dbg(&perf->ntb->dev, "DB bits unmasked %#llx\n", incmd_bit);
	पूर्ण
	अगर (ret) अणु
		ntb_clear_ctx(perf->ntb);
		वापस ret;
	पूर्ण

	ntb_link_enable(perf->ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	/* Might be not necessary */
	ntb_link_event(perf->ntb);

	वापस 0;
पूर्ण

अटल व्योम perf_disable_service(काष्ठा perf_ctx *perf)
अणु
	पूर्णांक pidx;

	अगर (perf->cmd_send == perf_msg_cmd_send) अणु
		u64 inbits;

		inbits = ntb_msg_inbits(perf->ntb);
		(व्योम)ntb_msg_set_mask(perf->ntb, inbits);
	पूर्ण अन्यथा अणु
		(व्योम)ntb_db_set_mask(perf->ntb, PERF_SPAD_NOTIFY(perf->gidx));
	पूर्ण

	ntb_clear_ctx(perf->ntb);

	क्रम (pidx = 0; pidx < perf->pcnt; pidx++)
		perf_cmd_exec(&perf->peers[pidx], PERF_CMD_CLEAR);

	क्रम (pidx = 0; pidx < perf->pcnt; pidx++)
		flush_work(&perf->peers[pidx].service);

	क्रम (pidx = 0; pidx < perf->pcnt; pidx++) अणु
		काष्ठा perf_peer *peer = &perf->peers[pidx];

		ntb_spad_ग_लिखो(perf->ntb, PERF_SPAD_CMD(peer->gidx), 0);
	पूर्ण

	ntb_db_clear(perf->ntb, PERF_SPAD_NOTIFY(perf->gidx));

	ntb_link_disable(perf->ntb);
पूर्ण

/*==============================================================================
 *                      Perक्रमmance measuring work-thपढ़ो
 *==============================================================================
 */

अटल व्योम perf_dma_copy_callback(व्योम *data)
अणु
	काष्ठा perf_thपढ़ो *pthr = data;

	atomic_dec(&pthr->dma_sync);
	wake_up(&pthr->dma_रुको);
पूर्ण

अटल पूर्णांक perf_copy_chunk(काष्ठा perf_thपढ़ो *pthr,
			   व्योम __iomem *dst, व्योम *src, माप_प्रकार len)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dmaengine_unmap_data *unmap;
	काष्ठा device *dma_dev;
	पूर्णांक try = 0, ret = 0;
	काष्ठा perf_peer *peer = pthr->perf->test_peer;
	व्योम __iomem *vbase;
	व्योम __iomem *dst_vaddr;
	dma_addr_t dst_dma_addr;

	अगर (!use_dma) अणु
		स_नकल_toio(dst, src, len);
		जाओ ret_check_tsync;
	पूर्ण

	dma_dev = pthr->dma_chan->device->dev;

	अगर (!is_dma_copy_aligned(pthr->dma_chan->device, offset_in_page(src),
				 offset_in_page(dst), len))
		वापस -EIO;

	vbase = peer->outbuf;
	dst_vaddr = dst;
	dst_dma_addr = peer->dma_dst_addr + (dst_vaddr - vbase);

	unmap = dmaengine_get_unmap_data(dma_dev, 1, GFP_NOWAIT);
	अगर (!unmap)
		वापस -ENOMEM;

	unmap->len = len;
	unmap->addr[0] = dma_map_page(dma_dev, virt_to_page(src),
		offset_in_page(src), len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dma_dev, unmap->addr[0])) अणु
		ret = -EIO;
		जाओ err_मुक्त_resource;
	पूर्ण
	unmap->to_cnt = 1;

	करो अणु
		tx = dmaengine_prep_dma_स_नकल(pthr->dma_chan, dst_dma_addr,
			unmap->addr[0], len, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!tx)
			msleep(DMA_MDELAY);
	पूर्ण जबतक (!tx && (try++ < DMA_TRIES));

	अगर (!tx) अणु
		ret = -EIO;
		जाओ err_मुक्त_resource;
	पूर्ण

	tx->callback = perf_dma_copy_callback;
	tx->callback_param = pthr;
	dma_set_unmap(tx, unmap);

	ret = dma_submit_error(dmaengine_submit(tx));
	अगर (ret) अणु
		dmaengine_unmap_put(unmap);
		जाओ err_मुक्त_resource;
	पूर्ण

	dmaengine_unmap_put(unmap);

	atomic_inc(&pthr->dma_sync);
	dma_async_issue_pending(pthr->dma_chan);

ret_check_tsync:
	वापस likely(atomic_पढ़ो(&pthr->perf->tsync) > 0) ? 0 : -EINTR;

err_मुक्त_resource:
	dmaengine_unmap_put(unmap);

	वापस ret;
पूर्ण

अटल bool perf_dma_filter(काष्ठा dma_chan *chan, व्योम *data)
अणु
	काष्ठा perf_ctx *perf = data;
	पूर्णांक node;

	node = dev_to_node(&perf->ntb->dev);

	वापस node == NUMA_NO_NODE || node == dev_to_node(chan->device->dev);
पूर्ण

अटल पूर्णांक perf_init_test(काष्ठा perf_thपढ़ो *pthr)
अणु
	काष्ठा perf_ctx *perf = pthr->perf;
	dma_cap_mask_t dma_mask;
	काष्ठा perf_peer *peer = pthr->perf->test_peer;

	pthr->src = kदो_स्मृति_node(perf->test_peer->outbuf_size, GFP_KERNEL,
				 dev_to_node(&perf->ntb->dev));
	अगर (!pthr->src)
		वापस -ENOMEM;

	get_अक्रमom_bytes(pthr->src, perf->test_peer->outbuf_size);

	अगर (!use_dma)
		वापस 0;

	dma_cap_zero(dma_mask);
	dma_cap_set(DMA_MEMCPY, dma_mask);
	pthr->dma_chan = dma_request_channel(dma_mask, perf_dma_filter, perf);
	अगर (!pthr->dma_chan) अणु
		dev_err(&perf->ntb->dev, "%d: Failed to get DMA channel\n",
			pthr->tidx);
		जाओ err_मुक्त;
	पूर्ण
	peer->dma_dst_addr =
		dma_map_resource(pthr->dma_chan->device->dev,
				 peer->out_phys_addr, peer->outbuf_size,
				 DMA_FROM_DEVICE, 0);
	अगर (dma_mapping_error(pthr->dma_chan->device->dev,
			      peer->dma_dst_addr)) अणु
		dev_err(pthr->dma_chan->device->dev, "%d: Failed to map DMA addr\n",
			pthr->tidx);
		peer->dma_dst_addr = 0;
		dma_release_channel(pthr->dma_chan);
		जाओ err_मुक्त;
	पूर्ण
	dev_dbg(pthr->dma_chan->device->dev, "%d: Map MMIO %pa to DMA addr %pad\n",
			pthr->tidx,
			&peer->out_phys_addr,
			&peer->dma_dst_addr);

	atomic_set(&pthr->dma_sync, 0);
	वापस 0;

err_मुक्त:
	atomic_dec(&perf->tsync);
	wake_up(&perf->tरुको);
	kमुक्त(pthr->src);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक perf_run_test(काष्ठा perf_thपढ़ो *pthr)
अणु
	काष्ठा perf_peer *peer = pthr->perf->test_peer;
	काष्ठा perf_ctx *perf = pthr->perf;
	व्योम __iomem *flt_dst, *bnd_dst;
	u64 total_size, chunk_size;
	व्योम *flt_src;
	पूर्णांक ret = 0;

	total_size = 1ULL << total_order;
	chunk_size = 1ULL << chunk_order;
	chunk_size = min_t(u64, peer->outbuf_size, chunk_size);

	flt_src = pthr->src;
	bnd_dst = peer->outbuf + peer->outbuf_size;
	flt_dst = peer->outbuf;

	pthr->duration = kसमय_get();

	/* Copied field is cleared on test launch stage */
	जबतक (pthr->copied < total_size) अणु
		ret = perf_copy_chunk(pthr, flt_dst, flt_src, chunk_size);
		अगर (ret) अणु
			dev_err(&perf->ntb->dev, "%d: Got error %d on test\n",
				pthr->tidx, ret);
			वापस ret;
		पूर्ण

		pthr->copied += chunk_size;

		flt_dst += chunk_size;
		flt_src += chunk_size;
		अगर (flt_dst >= bnd_dst || flt_dst < peer->outbuf) अणु
			flt_dst = peer->outbuf;
			flt_src = pthr->src;
		पूर्ण

		/* Give up CPU to give a chance क्रम other thपढ़ोs to use it */
		schedule();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_sync_test(काष्ठा perf_thपढ़ो *pthr)
अणु
	काष्ठा perf_ctx *perf = pthr->perf;

	अगर (!use_dma)
		जाओ no_dma_ret;

	रुको_event(pthr->dma_रुको,
		   (atomic_पढ़ो(&pthr->dma_sync) == 0 ||
		    atomic_पढ़ो(&perf->tsync) < 0));

	अगर (atomic_पढ़ो(&perf->tsync) < 0)
		वापस -EINTR;

no_dma_ret:
	pthr->duration = kसमय_sub(kसमय_get(), pthr->duration);

	dev_dbg(&perf->ntb->dev, "%d: copied %llu bytes\n",
		pthr->tidx, pthr->copied);

	dev_dbg(&perf->ntb->dev, "%d: lasted %llu usecs\n",
		pthr->tidx, kसमय_प्रकारo_us(pthr->duration));

	dev_dbg(&perf->ntb->dev, "%d: %llu MBytes/s\n", pthr->tidx,
		भाग64_u64(pthr->copied, kसमय_प्रकारo_us(pthr->duration)));

	वापस 0;
पूर्ण

अटल व्योम perf_clear_test(काष्ठा perf_thपढ़ो *pthr)
अणु
	काष्ठा perf_ctx *perf = pthr->perf;

	अगर (!use_dma)
		जाओ no_dma_notअगरy;

	/*
	 * If test finished without errors, termination isn't needed.
	 * We call it anyway just to be sure of the transfers completion.
	 */
	(व्योम)dmaengine_terminate_sync(pthr->dma_chan);
	अगर (pthr->perf->test_peer->dma_dst_addr)
		dma_unmap_resource(pthr->dma_chan->device->dev,
				   pthr->perf->test_peer->dma_dst_addr,
				   pthr->perf->test_peer->outbuf_size,
				   DMA_FROM_DEVICE, 0);

	dma_release_channel(pthr->dma_chan);

no_dma_notअगरy:
	atomic_dec(&perf->tsync);
	wake_up(&perf->tरुको);
	kमुक्त(pthr->src);
पूर्ण

अटल व्योम perf_thपढ़ो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा perf_thपढ़ो *pthr = to_thपढ़ो_work(work);
	पूर्णांक ret;

	/*
	 * Perक्रमm stages in compliance with use_dma flag value.
	 * Test status is changed only अगर error happened, otherwise
	 * status -ENODATA is kept जबतक test is on-fly. Results
	 * synchronization is perक्रमmed only अगर test fininshed
	 * without an error or पूर्णांकerruption.
	 */
	ret = perf_init_test(pthr);
	अगर (ret) अणु
		pthr->status = ret;
		वापस;
	पूर्ण

	ret = perf_run_test(pthr);
	अगर (ret) अणु
		pthr->status = ret;
		जाओ err_clear_test;
	पूर्ण

	pthr->status = perf_sync_test(pthr);

err_clear_test:
	perf_clear_test(pthr);
पूर्ण

अटल पूर्णांक perf_set_tcnt(काष्ठा perf_ctx *perf, u8 tcnt)
अणु
	अगर (tcnt == 0 || tcnt > MAX_THREADS_CNT)
		वापस -EINVAL;

	अगर (test_and_set_bit_lock(0, &perf->busy_flag))
		वापस -EBUSY;

	perf->tcnt = tcnt;

	clear_bit_unlock(0, &perf->busy_flag);

	वापस 0;
पूर्ण

अटल व्योम perf_terminate_test(काष्ठा perf_ctx *perf)
अणु
	पूर्णांक tidx;

	atomic_set(&perf->tsync, -1);
	wake_up(&perf->tरुको);

	क्रम (tidx = 0; tidx < MAX_THREADS_CNT; tidx++) अणु
		wake_up(&perf->thपढ़ोs[tidx].dma_रुको);
		cancel_work_sync(&perf->thपढ़ोs[tidx].work);
	पूर्ण
पूर्ण

अटल पूर्णांक perf_submit_test(काष्ठा perf_peer *peer)
अणु
	काष्ठा perf_ctx *perf = peer->perf;
	काष्ठा perf_thपढ़ो *pthr;
	पूर्णांक tidx, ret;

	ret = रुको_क्रम_completion_पूर्णांकerruptible(&peer->init_comp);
	अगर (ret < 0)
		वापस ret;

	अगर (test_and_set_bit_lock(0, &perf->busy_flag))
		वापस -EBUSY;

	perf->test_peer = peer;
	atomic_set(&perf->tsync, perf->tcnt);

	क्रम (tidx = 0; tidx < MAX_THREADS_CNT; tidx++) अणु
		pthr = &perf->thपढ़ोs[tidx];

		pthr->status = -ENODATA;
		pthr->copied = 0;
		pthr->duration = kसमय_set(0, 0);
		अगर (tidx < perf->tcnt)
			(व्योम)queue_work(perf_wq, &pthr->work);
	पूर्ण

	ret = रुको_event_पूर्णांकerruptible(perf->tरुको,
				       atomic_पढ़ो(&perf->tsync) <= 0);
	अगर (ret == -ERESTARTSYS) अणु
		perf_terminate_test(perf);
		ret = -EINTR;
	पूर्ण

	clear_bit_unlock(0, &perf->busy_flag);

	वापस ret;
पूर्ण

अटल पूर्णांक perf_पढ़ो_stats(काष्ठा perf_ctx *perf, अक्षर *buf,
			   माप_प्रकार size, sमाप_प्रकार *pos)
अणु
	काष्ठा perf_thपढ़ो *pthr;
	पूर्णांक tidx;

	अगर (test_and_set_bit_lock(0, &perf->busy_flag))
		वापस -EBUSY;

	(*pos) += scnम_लिखो(buf + *pos, size - *pos,
		"    Peer %d test statistics:\n", perf->test_peer->pidx);

	क्रम (tidx = 0; tidx < MAX_THREADS_CNT; tidx++) अणु
		pthr = &perf->thपढ़ोs[tidx];

		अगर (pthr->status == -ENODATA)
			जारी;

		अगर (pthr->status) अणु
			(*pos) += scnम_लिखो(buf + *pos, size - *pos,
				"%d: error status %d\n", tidx, pthr->status);
			जारी;
		पूर्ण

		(*pos) += scnम_लिखो(buf + *pos, size - *pos,
			"%d: copied %llu bytes in %llu usecs, %llu MBytes/s\n",
			tidx, pthr->copied, kसमय_प्रकारo_us(pthr->duration),
			भाग64_u64(pthr->copied, kसमय_प्रकारo_us(pthr->duration)));
	पूर्ण

	clear_bit_unlock(0, &perf->busy_flag);

	वापस 0;
पूर्ण

अटल व्योम perf_init_thपढ़ोs(काष्ठा perf_ctx *perf)
अणु
	काष्ठा perf_thपढ़ो *pthr;
	पूर्णांक tidx;

	perf->tcnt = DEF_THREADS_CNT;
	perf->test_peer = &perf->peers[0];
	init_रुकोqueue_head(&perf->tरुको);

	क्रम (tidx = 0; tidx < MAX_THREADS_CNT; tidx++) अणु
		pthr = &perf->thपढ़ोs[tidx];

		pthr->perf = perf;
		pthr->tidx = tidx;
		pthr->status = -ENODATA;
		init_रुकोqueue_head(&pthr->dma_रुको);
		INIT_WORK(&pthr->work, perf_thपढ़ो_work);
	पूर्ण
पूर्ण

अटल व्योम perf_clear_thपढ़ोs(काष्ठा perf_ctx *perf)
अणु
	perf_terminate_test(perf);
पूर्ण

/*==============================================================================
 *                               DebugFS nodes
 *==============================================================================
 */

अटल sमाप_प्रकार perf_dbgfs_पढ़ो_info(काष्ठा file *filep, अक्षर __user *ubuf,
				    माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा perf_ctx *perf = filep->निजी_data;
	काष्ठा perf_peer *peer;
	माप_प्रकार buf_size;
	sमाप_प्रकार pos = 0;
	पूर्णांक ret, pidx;
	अक्षर *buf;

	buf_size = min_t(माप_प्रकार, size, 0x1000U);

	buf = kदो_स्मृति(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos += scnम_लिखो(buf + pos, buf_size - pos,
		"    Performance measuring tool info:\n\n");

	pos += scnम_लिखो(buf + pos, buf_size - pos,
		"Local port %d, Global index %d\n", ntb_port_number(perf->ntb),
		perf->gidx);
	pos += scnम_लिखो(buf + pos, buf_size - pos, "Test status: ");
	अगर (test_bit(0, &perf->busy_flag)) अणु
		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"on-fly with port %d (%d)\n",
			ntb_peer_port_number(perf->ntb, perf->test_peer->pidx),
			perf->test_peer->pidx);
	पूर्ण अन्यथा अणु
		pos += scnम_लिखो(buf + pos, buf_size - pos, "idle\n");
	पूर्ण

	क्रम (pidx = 0; pidx < perf->pcnt; pidx++) अणु
		peer = &perf->peers[pidx];

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"Port %d (%d), Global index %d:\n",
			ntb_peer_port_number(perf->ntb, peer->pidx), peer->pidx,
			peer->gidx);

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"\tLink status: %s\n",
			test_bit(PERF_STS_LNKUP, &peer->sts) ? "up" : "down");

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"\tOut buffer addr 0x%pK\n", peer->outbuf);

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"\tOut buff phys addr %pa[p]\n", &peer->out_phys_addr);

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"\tOut buffer size %pa\n", &peer->outbuf_size);

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"\tOut buffer xlat 0x%016llx[p]\n", peer->outbuf_xlat);

		अगर (!peer->inbuf) अणु
			pos += scnम_लिखो(buf + pos, buf_size - pos,
				"\tIn buffer addr: unallocated\n");
			जारी;
		पूर्ण

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"\tIn buffer addr 0x%pK\n", peer->inbuf);

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"\tIn buffer size %pa\n", &peer->inbuf_size);

		pos += scnम_लिखो(buf + pos, buf_size - pos,
			"\tIn buffer xlat %pad[p]\n", &peer->inbuf_xlat);
	पूर्ण

	ret = simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations perf_dbgfs_info = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = perf_dbgfs_पढ़ो_info
पूर्ण;

अटल sमाप_प्रकार perf_dbgfs_पढ़ो_run(काष्ठा file *filep, अक्षर __user *ubuf,
				   माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा perf_ctx *perf = filep->निजी_data;
	sमाप_प्रकार ret, pos = 0;
	अक्षर *buf;

	buf = kदो_स्मृति(PERF_BUF_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = perf_पढ़ो_stats(perf, buf, PERF_BUF_LEN, &pos);
	अगर (ret)
		जाओ err_मुक्त;

	ret = simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
err_मुक्त:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार perf_dbgfs_ग_लिखो_run(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
				    माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा perf_ctx *perf = filep->निजी_data;
	काष्ठा perf_peer *peer;
	पूर्णांक pidx, ret;

	ret = kstrtoपूर्णांक_from_user(ubuf, size, 0, &pidx);
	अगर (ret)
		वापस ret;

	अगर (pidx < 0 || pidx >= perf->pcnt)
		वापस -EINVAL;

	peer = &perf->peers[pidx];

	ret = perf_submit_test(peer);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations perf_dbgfs_run = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = perf_dbgfs_पढ़ो_run,
	.ग_लिखो = perf_dbgfs_ग_लिखो_run
पूर्ण;

अटल sमाप_प्रकार perf_dbgfs_पढ़ो_tcnt(काष्ठा file *filep, अक्षर __user *ubuf,
				    माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा perf_ctx *perf = filep->निजी_data;
	अक्षर buf[8];
	sमाप_प्रकार pos;

	pos = scnम_लिखो(buf, माप(buf), "%hhu\n", perf->tcnt);

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
पूर्ण

अटल sमाप_प्रकार perf_dbgfs_ग_लिखो_tcnt(काष्ठा file *filep,
				     स्थिर अक्षर __user *ubuf,
				     माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा perf_ctx *perf = filep->निजी_data;
	पूर्णांक ret;
	u8 val;

	ret = kstrtou8_from_user(ubuf, size, 0, &val);
	अगर (ret)
		वापस ret;

	ret = perf_set_tcnt(perf, val);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations perf_dbgfs_tcnt = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = perf_dbgfs_पढ़ो_tcnt,
	.ग_लिखो = perf_dbgfs_ग_लिखो_tcnt
पूर्ण;

अटल व्योम perf_setup_dbgfs(काष्ठा perf_ctx *perf)
अणु
	काष्ठा pci_dev *pdev = perf->ntb->pdev;

	perf->dbgfs_dir = debugfs_create_dir(pci_name(pdev), perf_dbgfs_topdir);
	अगर (!perf->dbgfs_dir) अणु
		dev_warn(&perf->ntb->dev, "DebugFS unsupported\n");
		वापस;
	पूर्ण

	debugfs_create_file("info", 0600, perf->dbgfs_dir, perf,
			    &perf_dbgfs_info);

	debugfs_create_file("run", 0600, perf->dbgfs_dir, perf,
			    &perf_dbgfs_run);

	debugfs_create_file("threads_count", 0600, perf->dbgfs_dir, perf,
			    &perf_dbgfs_tcnt);

	/* They are made पढ़ो-only क्रम test exec safety and पूर्णांकegrity */
	debugfs_create_u8("chunk_order", 0500, perf->dbgfs_dir, &chunk_order);

	debugfs_create_u8("total_order", 0500, perf->dbgfs_dir, &total_order);

	debugfs_create_bool("use_dma", 0500, perf->dbgfs_dir, &use_dma);
पूर्ण

अटल व्योम perf_clear_dbgfs(काष्ठा perf_ctx *perf)
अणु
	debugfs_हटाओ_recursive(perf->dbgfs_dir);
पूर्ण

/*==============================================================================
 *                        Basic driver initialization
 *==============================================================================
 */

अटल काष्ठा perf_ctx *perf_create_data(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा perf_ctx *perf;

	perf = devm_kzalloc(&ntb->dev, माप(*perf), GFP_KERNEL);
	अगर (!perf)
		वापस ERR_PTR(-ENOMEM);

	perf->pcnt = ntb_peer_port_count(ntb);
	perf->peers = devm_kसुस्मृति(&ntb->dev, perf->pcnt, माप(*perf->peers),
				  GFP_KERNEL);
	अगर (!perf->peers)
		वापस ERR_PTR(-ENOMEM);

	perf->ntb = ntb;

	वापस perf;
पूर्ण

अटल पूर्णांक perf_setup_peer_mw(काष्ठा perf_peer *peer)
अणु
	काष्ठा perf_ctx *perf = peer->perf;
	phys_addr_t phys_addr;
	पूर्णांक ret;

	/* Get outbound MW parameters and map it */
	ret = ntb_peer_mw_get_addr(perf->ntb, perf->gidx, &phys_addr,
				   &peer->outbuf_size);
	अगर (ret)
		वापस ret;

	peer->outbuf = devm_ioremap_wc(&perf->ntb->dev, phys_addr,
					peer->outbuf_size);
	अगर (!peer->outbuf)
		वापस -ENOMEM;

	peer->out_phys_addr = phys_addr;

	अगर (max_mw_size && peer->outbuf_size > max_mw_size) अणु
		peer->outbuf_size = max_mw_size;
		dev_warn(&peer->perf->ntb->dev,
			"Peer %d outbuf reduced to %pa\n", peer->pidx,
			&peer->outbuf_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_init_peers(काष्ठा perf_ctx *perf)
अणु
	काष्ठा perf_peer *peer;
	पूर्णांक pidx, lport, ret;

	lport = ntb_port_number(perf->ntb);
	perf->gidx = -1;
	क्रम (pidx = 0; pidx < perf->pcnt; pidx++) अणु
		peer = &perf->peers[pidx];

		peer->perf = perf;
		peer->pidx = pidx;
		अगर (lport < ntb_peer_port_number(perf->ntb, pidx)) अणु
			अगर (perf->gidx == -1)
				perf->gidx = pidx;
			peer->gidx = pidx + 1;
		पूर्ण अन्यथा अणु
			peer->gidx = pidx;
		पूर्ण
		INIT_WORK(&peer->service, perf_service_work);
		init_completion(&peer->init_comp);
	पूर्ण
	अगर (perf->gidx == -1)
		perf->gidx = pidx;

	/*
	 * Hardware with only two ports may not have unique port
	 * numbers. In this हाल, the gidxs should all be zero.
	 */
	अगर (perf->pcnt == 1 &&  ntb_port_number(perf->ntb) == 0 &&
	    ntb_peer_port_number(perf->ntb, 0) == 0) अणु
		perf->gidx = 0;
		perf->peers[0].gidx = 0;
	पूर्ण

	क्रम (pidx = 0; pidx < perf->pcnt; pidx++) अणु
		ret = perf_setup_peer_mw(&perf->peers[pidx]);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev_dbg(&perf->ntb->dev, "Global port index %d\n", perf->gidx);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_probe(काष्ठा ntb_client *client, काष्ठा ntb_dev *ntb)
अणु
	काष्ठा perf_ctx *perf;
	पूर्णांक ret;

	perf = perf_create_data(ntb);
	अगर (IS_ERR(perf))
		वापस PTR_ERR(perf);

	ret = perf_init_peers(perf);
	अगर (ret)
		वापस ret;

	perf_init_thपढ़ोs(perf);

	ret = perf_init_service(perf);
	अगर (ret)
		वापस ret;

	ret = perf_enable_service(perf);
	अगर (ret)
		वापस ret;

	perf_setup_dbgfs(perf);

	वापस 0;
पूर्ण

अटल व्योम perf_हटाओ(काष्ठा ntb_client *client, काष्ठा ntb_dev *ntb)
अणु
	काष्ठा perf_ctx *perf = ntb->ctx;

	perf_clear_dbgfs(perf);

	perf_disable_service(perf);

	perf_clear_thपढ़ोs(perf);
पूर्ण

अटल काष्ठा ntb_client perf_client = अणु
	.ops = अणु
		.probe = perf_probe,
		.हटाओ = perf_हटाओ
	पूर्ण
पूर्ण;

अटल पूर्णांक __init perf_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (chunk_order > MAX_CHUNK_ORDER) अणु
		chunk_order = MAX_CHUNK_ORDER;
		pr_info("Chunk order reduced to %hhu\n", chunk_order);
	पूर्ण

	अगर (total_order < chunk_order) अणु
		total_order = chunk_order;
		pr_info("Total data order reduced to %hhu\n", total_order);
	पूर्ण

	perf_wq = alloc_workqueue("perf_wq", WQ_UNBOUND | WQ_SYSFS, 0);
	अगर (!perf_wq)
		वापस -ENOMEM;

	अगर (debugfs_initialized())
		perf_dbgfs_topdir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	ret = ntb_रेजिस्टर_client(&perf_client);
	अगर (ret) अणु
		debugfs_हटाओ_recursive(perf_dbgfs_topdir);
		destroy_workqueue(perf_wq);
	पूर्ण

	वापस ret;
पूर्ण
module_init(perf_init);

अटल व्योम __निकास perf_निकास(व्योम)
अणु
	ntb_unरेजिस्टर_client(&perf_client);
	debugfs_हटाओ_recursive(perf_dbgfs_topdir);
	destroy_workqueue(perf_wq);
पूर्ण
module_निकास(perf_निकास);
