<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *   Copyright (C) 2017 T-Platक्रमms All Rights Reserved.
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
 *   Copyright (C) 2017 T-Platक्रमms All Rights Reserved.
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
 * PCIe NTB Debugging Tool Linux driver
 */

/*
 * How to use this tool, by example.
 *
 * Assuming $DBG_सूची is something like:
 * '/sys/kernel/debug/ntb_tool/0000:00:03.0'
 * Suppose aside from local device there is at least one remote device
 * connected to NTB with index 0.
 *-----------------------------------------------------------------------------
 * Eg: check local/peer device inक्रमmation.
 *
 * # Get local device port number
 * root@self# cat $DBG_सूची/port
 *
 * # Check local device functionality
 * root@self# ls $DBG_सूची
 * db            msg1          msg_sts     peer4/        port
 * db_event      msg2          peer0/      peer5/        spad0
 * db_mask       msg3          peer1/      peer_db       spad1
 * link          msg_event     peer2/      peer_db_mask  spad2
 * msg0          msg_mask      peer3/      peer_spad     spad3
 * # As one can see it supports:
 * # 1) four inbound message रेजिस्टरs
 * # 2) four inbound scratchpads
 * # 3) up to six peer devices
 *
 * # Check peer device port number
 * root@self# cat $DBG_सूची/peer0/port
 *
 * # Check peer device(s) functionality to be used
 * root@self# ls $DBG_सूची/peer0
 * link             mw_trans0       mw_trans6        port
 * link_event       mw_trans1       mw_trans7        spad0
 * msg0             mw_trans2       peer_mw_trans0   spad1
 * msg1             mw_trans3       peer_mw_trans1   spad2
 * msg2             mw_trans4       peer_mw_trans2   spad3
 * msg3             mw_trans5       peer_mw_trans3
 * # As one can see we got:
 * # 1) four outbound message रेजिस्टरs
 * # 2) four outbound scratchpads
 * # 3) eight inbound memory winकरोws
 * # 4) four outbound memory winकरोws
 *-----------------------------------------------------------------------------
 * Eg: NTB link tests
 *
 * # Set local link up/करोwn
 * root@self# echo Y > $DBG_सूची/link
 * root@self# echo N > $DBG_सूची/link
 *
 * # Check अगर link with peer device is up/करोwn:
 * root@self# cat $DBG_सूची/peer0/link
 *
 * # Block until the link is up/करोwn
 * root@self# echo Y > $DBG_सूची/peer0/link_event
 * root@self# echo N > $DBG_सूची/peer0/link_event
 *-----------------------------------------------------------------------------
 * Eg: Doorbell रेजिस्टरs tests (some functionality might be असलent)
 *
 * # Set/clear/get local करोorbell
 * root@self# echo 's 1' > $DBG_सूची/db
 * root@self# echo 'c 1' > $DBG_सूची/db
 * root@self# cat  $DBG_सूची/db
 *
 * # Set/clear/get local करोorbell mask
 * root@self# echo 's 1' > $DBG_सूची/db_mask
 * root@self# echo 'c 1' > $DBG_सूची/db_mask
 * root@self# cat $DBG_सूची/db_mask
 *
 * # Ring/clear/get peer करोorbell
 * root@peer# echo 's 1' > $DBG_सूची/peer_db
 * root@peer# echo 'c 1' > $DBG_सूची/peer_db
 * root@peer# cat $DBG_सूची/peer_db
 *
 * # Set/clear/get peer करोorbell mask
 * root@self# echo 's 1' > $DBG_सूची/peer_db_mask
 * root@self# echo 'c 1' > $DBG_सूची/peer_db_mask
 * root@self# cat $DBG_सूची/peer_db_mask
 *
 * # Block until local करोorbell is set with specअगरied value
 * root@self# echo 1 > $DBG_सूची/db_event
 *-----------------------------------------------------------------------------
 * Eg: Message रेजिस्टरs tests (functionality might be असलent)
 *
 * # Set/clear/get in/out message रेजिस्टरs status
 * root@self# echo 's 1' > $DBG_सूची/msg_sts
 * root@self# echo 'c 1' > $DBG_सूची/msg_sts
 * root@self# cat $DBG_सूची/msg_sts
 *
 * # Set/clear in/out message रेजिस्टरs mask
 * root@self# echo 's 1' > $DBG_सूची/msg_mask
 * root@self# echo 'c 1' > $DBG_सूची/msg_mask
 *
 * # Get inbound message रेजिस्टर #0 value and source of port index
 * root@self# cat  $DBG_सूची/msg0
 *
 * # Send some data to peer over outbound message रेजिस्टर #0
 * root@self# echo 0x01020304 > $DBG_सूची/peer0/msg0
 *-----------------------------------------------------------------------------
 * Eg: Scratchpad रेजिस्टरs tests (functionality might be असलent)
 *
 * # Write/पढ़ो to/from local scratchpad रेजिस्टर #0
 * root@peer# echo 0x01020304 > $DBG_सूची/spad0
 * root@peer# cat $DBG_सूची/spad0
 *
 * # Write/पढ़ो to/from peer scratchpad रेजिस्टर #0
 * root@peer# echo 0x01020304 > $DBG_सूची/peer0/spad0
 * root@peer# cat $DBG_सूची/peer0/spad0
 *-----------------------------------------------------------------------------
 * Eg: Memory winकरोws tests
 *
 * # Create inbound memory winकरोw buffer of specअगरied size/get its base address
 * root@peer# echo 16384 > $DBG_सूची/peer0/mw_trans0
 * root@peer# cat $DBG_सूची/peer0/mw_trans0
 *
 * # Write/पढ़ो data to/from inbound memory winकरोw
 * root@peer# echo Hello > $DBG_सूची/peer0/mw0
 * root@peer# head -c 7 $DBG_सूची/peer0/mw0
 *
 * # Map outbound memory winकरोw/check it settings (on peer device)
 * root@peer# echo 0xADD0BA5E:16384 > $DBG_सूची/peer0/peer_mw_trans0
 * root@peer# cat $DBG_सूची/peer0/peer_mw_trans0
 *
 * # Write/पढ़ो data to/from outbound memory winकरोw (on peer device)
 * root@peer# echo olleH > $DBG_सूची/peer0/peer_mw0
 * root@peer# head -c 7 $DBG_सूची/peer0/peer_mw0
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/ntb.h>

#घोषणा DRIVER_NAME		"ntb_tool"
#घोषणा DRIVER_VERSION		"2.0"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(DRIVER_VERSION);
MODULE_AUTHOR("Allen Hubbe <Allen.Hubbe@emc.com>");
MODULE_DESCRIPTION("PCIe NTB Debugging Tool");

/*
 * Inbound and outbound memory winकरोws descriptor. Union members selection
 * depends on the MW type the काष्ठाure describes. mm_base/dma_base are the
 * भव and DMA address of an inbound MW. io_base/tr_base are the MMIO
 * mapped भव and xlat addresses of an outbound MW respectively.
 */
काष्ठा tool_mw अणु
	पूर्णांक widx;
	पूर्णांक pidx;
	काष्ठा tool_ctx *tc;
	जोड़ अणु
		u8 *mm_base;
		u8 __iomem *io_base;
	पूर्ण;
	जोड़ अणु
		dma_addr_t dma_base;
		u64 tr_base;
	पूर्ण;
	resource_माप_प्रकार size;
	काष्ठा dentry *dbgfs_file;
पूर्ण;

/*
 * Wrapper काष्ठाure is used to distinguish the outbound MW peers reference
 * within the corresponding DebugFS directory IO operation.
 */
काष्ठा tool_mw_wrap अणु
	पूर्णांक pidx;
	काष्ठा tool_mw *mw;
पूर्ण;

काष्ठा tool_msg अणु
	पूर्णांक midx;
	पूर्णांक pidx;
	काष्ठा tool_ctx *tc;
पूर्ण;

काष्ठा tool_spad अणु
	पूर्णांक sidx;
	पूर्णांक pidx;
	काष्ठा tool_ctx *tc;
पूर्ण;

काष्ठा tool_peer अणु
	पूर्णांक pidx;
	काष्ठा tool_ctx *tc;
	पूर्णांक inmw_cnt;
	काष्ठा tool_mw *inmws;
	पूर्णांक ouपंचांगw_cnt;
	काष्ठा tool_mw_wrap *ouपंचांगws;
	पूर्णांक ouपंचांगsg_cnt;
	काष्ठा tool_msg *ouपंचांगsgs;
	पूर्णांक outspad_cnt;
	काष्ठा tool_spad *outspads;
	काष्ठा dentry *dbgfs_dir;
पूर्ण;

काष्ठा tool_ctx अणु
	काष्ठा ntb_dev *ntb;
	रुको_queue_head_t link_wq;
	रुको_queue_head_t db_wq;
	रुको_queue_head_t msg_wq;
	पूर्णांक ouपंचांगw_cnt;
	काष्ठा tool_mw *ouपंचांगws;
	पूर्णांक peer_cnt;
	काष्ठा tool_peer *peers;
	पूर्णांक inmsg_cnt;
	काष्ठा tool_msg *inmsgs;
	पूर्णांक inspad_cnt;
	काष्ठा tool_spad *inspads;
	काष्ठा dentry *dbgfs_dir;
पूर्ण;

#घोषणा TOOL_FOPS_RDWR(__name, __पढ़ो, __ग_लिखो) \
	स्थिर काष्ठा file_operations __name = अणु	\
		.owner = THIS_MODULE,		\
		.खोलो = simple_खोलो,		\
		.पढ़ो = __पढ़ो,			\
		.ग_लिखो = __ग_लिखो,		\
	पूर्ण

#घोषणा TOOL_BUF_LEN 32

अटल काष्ठा dentry *tool_dbgfs_topdir;

/*==============================================================================
 *                               NTB events handlers
 *==============================================================================
 */

अटल व्योम tool_link_event(व्योम *ctx)
अणु
	काष्ठा tool_ctx *tc = ctx;
	क्रमागत ntb_speed speed;
	क्रमागत ntb_width width;
	पूर्णांक up;

	up = ntb_link_is_up(tc->ntb, &speed, &width);

	dev_dbg(&tc->ntb->dev, "link is %s speed %d width %d\n",
		up ? "up" : "down", speed, width);

	wake_up(&tc->link_wq);
पूर्ण

अटल व्योम tool_db_event(व्योम *ctx, पूर्णांक vec)
अणु
	काष्ठा tool_ctx *tc = ctx;
	u64 db_bits, db_mask;

	db_mask = ntb_db_vector_mask(tc->ntb, vec);
	db_bits = ntb_db_पढ़ो(tc->ntb);

	dev_dbg(&tc->ntb->dev, "doorbell vec %d mask %#llx bits %#llx\n",
		vec, db_mask, db_bits);

	wake_up(&tc->db_wq);
पूर्ण

अटल व्योम tool_msg_event(व्योम *ctx)
अणु
	काष्ठा tool_ctx *tc = ctx;
	u64 msg_sts;

	msg_sts = ntb_msg_पढ़ो_sts(tc->ntb);

	dev_dbg(&tc->ntb->dev, "message bits %#llx\n", msg_sts);

	wake_up(&tc->msg_wq);
पूर्ण

अटल स्थिर काष्ठा ntb_ctx_ops tool_ops = अणु
	.link_event = tool_link_event,
	.db_event = tool_db_event,
	.msg_event = tool_msg_event
पूर्ण;

/*==============================================================================
 *                        Common पढ़ो/ग_लिखो methods
 *==============================================================================
 */

अटल sमाप_प्रकार tool_fn_पढ़ो(काष्ठा tool_ctx *tc, अक्षर __user *ubuf,
			    माप_प्रकार size, loff_t *offp,
			    u64 (*fn_पढ़ो)(काष्ठा ntb_dev *))
अणु
	माप_प्रकार buf_size;
	अक्षर buf[TOOL_BUF_LEN];
	sमाप_प्रकार pos;

	अगर (!fn_पढ़ो)
		वापस -EINVAL;

	buf_size = min(size, माप(buf));

	pos = scnम_लिखो(buf, buf_size, "%#llx\n", fn_पढ़ो(tc->ntb));

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
पूर्ण

अटल sमाप_प्रकार tool_fn_ग_लिखो(काष्ठा tool_ctx *tc,
			     स्थिर अक्षर __user *ubuf,
			     माप_प्रकार size, loff_t *offp,
			     पूर्णांक (*fn_set)(काष्ठा ntb_dev *, u64),
			     पूर्णांक (*fn_clear)(काष्ठा ntb_dev *, u64))
अणु
	अक्षर *buf, cmd;
	sमाप_प्रकार ret;
	u64 bits;
	पूर्णांक n;

	buf = kदो_स्मृति(size + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = simple_ग_लिखो_to_buffer(buf, size, offp, ubuf, size);
	अगर (ret < 0) अणु
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	buf[size] = 0;

	n = माला_पूछो(buf, "%c %lli", &cmd, &bits);

	kमुक्त(buf);

	अगर (n != 2) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (cmd == 's') अणु
		अगर (!fn_set)
			ret = -EINVAL;
		अन्यथा
			ret = fn_set(tc->ntb, bits);
	पूर्ण अन्यथा अगर (cmd == 'c') अणु
		अगर (!fn_clear)
			ret = -EINVAL;
		अन्यथा
			ret = fn_clear(tc->ntb, bits);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret ? : size;
पूर्ण

/*==============================================================================
 *                            Port पढ़ो/ग_लिखो methods
 *==============================================================================
 */

अटल sमाप_प्रकार tool_port_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
			      माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;
	अक्षर buf[TOOL_BUF_LEN];
	पूर्णांक pos;

	pos = scnम_लिखो(buf, माप(buf), "%d\n", ntb_port_number(tc->ntb));

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_port_fops,
		      tool_port_पढ़ो,
		      शून्य);

अटल sमाप_प्रकार tool_peer_port_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				   माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_peer *peer = filep->निजी_data;
	काष्ठा tool_ctx *tc = peer->tc;
	अक्षर buf[TOOL_BUF_LEN];
	पूर्णांक pos;

	pos = scnम_लिखो(buf, माप(buf), "%d\n",
		ntb_peer_port_number(tc->ntb, peer->pidx));

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_peer_port_fops,
		      tool_peer_port_पढ़ो,
		      शून्य);

अटल पूर्णांक tool_init_peers(काष्ठा tool_ctx *tc)
अणु
	पूर्णांक pidx;

	tc->peer_cnt = ntb_peer_port_count(tc->ntb);
	tc->peers = devm_kसुस्मृति(&tc->ntb->dev, tc->peer_cnt,
				 माप(*tc->peers), GFP_KERNEL);
	अगर (tc->peers == शून्य)
		वापस -ENOMEM;

	क्रम (pidx = 0; pidx < tc->peer_cnt; pidx++) अणु
		tc->peers[pidx].pidx = pidx;
		tc->peers[pidx].tc = tc;
	पूर्ण

	वापस 0;
पूर्ण

/*==============================================================================
 *                       Link state पढ़ो/ग_लिखो methods
 *==============================================================================
 */

अटल sमाप_प्रकार tool_link_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;
	bool val;
	पूर्णांक ret;

	ret = kstrtobool_from_user(ubuf, size, &val);
	अगर (ret)
		वापस ret;

	अगर (val)
		ret = ntb_link_enable(tc->ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	अन्यथा
		ret = ntb_link_disable(tc->ntb);

	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_link_fops,
		      शून्य,
		      tool_link_ग_लिखो);

अटल sमाप_प्रकार tool_peer_link_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				   माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_peer *peer = filep->निजी_data;
	काष्ठा tool_ctx *tc = peer->tc;
	अक्षर buf[3];

	अगर (ntb_link_is_up(tc->ntb, शून्य, शून्य) & BIT(peer->pidx))
		buf[0] = 'Y';
	अन्यथा
		buf[0] = 'N';
	buf[1] = '\n';
	buf[2] = '\0';

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp, buf, 2);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_peer_link_fops,
		      tool_peer_link_पढ़ो,
		      शून्य);

अटल sमाप_प्रकार tool_peer_link_event_ग_लिखो(काष्ठा file *filep,
					  स्थिर अक्षर __user *ubuf,
					  माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_peer *peer = filep->निजी_data;
	काष्ठा tool_ctx *tc = peer->tc;
	u64 link_msk;
	bool val;
	पूर्णांक ret;

	ret = kstrtobool_from_user(ubuf, size, &val);
	अगर (ret)
		वापस ret;

	link_msk = BIT_ULL_MASK(peer->pidx);

	अगर (रुको_event_पूर्णांकerruptible(tc->link_wq,
		!!(ntb_link_is_up(tc->ntb, शून्य, शून्य) & link_msk) == val))
		वापस -ERESTART;

	वापस size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_peer_link_event_fops,
		      शून्य,
		      tool_peer_link_event_ग_लिखो);

/*==============================================================================
 *                  Memory winकरोws पढ़ो/ग_लिखो/setting methods
 *==============================================================================
 */

अटल sमाप_प्रकार tool_mw_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
			    माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_mw *inmw = filep->निजी_data;

	अगर (inmw->mm_base == शून्य)
		वापस -ENXIO;

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp,
				       inmw->mm_base, inmw->size);
पूर्ण

अटल sमाप_प्रकार tool_mw_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
			     माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_mw *inmw = filep->निजी_data;

	अगर (inmw->mm_base == शून्य)
		वापस -ENXIO;

	वापस simple_ग_लिखो_to_buffer(inmw->mm_base, inmw->size, offp,
				      ubuf, size);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_mw_fops,
		      tool_mw_पढ़ो,
		      tool_mw_ग_लिखो);

अटल पूर्णांक tool_setup_mw(काष्ठा tool_ctx *tc, पूर्णांक pidx, पूर्णांक widx,
			 माप_प्रकार req_size)
अणु
	resource_माप_प्रकार size, addr_align, size_align;
	काष्ठा tool_mw *inmw = &tc->peers[pidx].inmws[widx];
	अक्षर buf[TOOL_BUF_LEN];
	पूर्णांक ret;

	अगर (inmw->mm_base != शून्य)
		वापस 0;

	ret = ntb_mw_get_align(tc->ntb, pidx, widx, &addr_align,
				&size_align, &size);
	अगर (ret)
		वापस ret;

	inmw->size = min_t(resource_माप_प्रकार, req_size, size);
	inmw->size = round_up(inmw->size, addr_align);
	inmw->size = round_up(inmw->size, size_align);
	inmw->mm_base = dma_alloc_coherent(&tc->ntb->pdev->dev, inmw->size,
					   &inmw->dma_base, GFP_KERNEL);
	अगर (!inmw->mm_base)
		वापस -ENOMEM;

	अगर (!IS_ALIGNED(inmw->dma_base, addr_align)) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_dma;
	पूर्ण

	ret = ntb_mw_set_trans(tc->ntb, pidx, widx, inmw->dma_base, inmw->size);
	अगर (ret)
		जाओ err_मुक्त_dma;

	snम_लिखो(buf, माप(buf), "mw%d", widx);
	inmw->dbgfs_file = debugfs_create_file(buf, 0600,
					       tc->peers[pidx].dbgfs_dir, inmw,
					       &tool_mw_fops);

	वापस 0;

err_मुक्त_dma:
	dma_मुक्त_coherent(&tc->ntb->pdev->dev, inmw->size, inmw->mm_base,
			  inmw->dma_base);
	inmw->mm_base = शून्य;
	inmw->dma_base = 0;
	inmw->size = 0;

	वापस ret;
पूर्ण

अटल व्योम tool_मुक्त_mw(काष्ठा tool_ctx *tc, पूर्णांक pidx, पूर्णांक widx)
अणु
	काष्ठा tool_mw *inmw = &tc->peers[pidx].inmws[widx];

	debugfs_हटाओ(inmw->dbgfs_file);

	अगर (inmw->mm_base != शून्य) अणु
		ntb_mw_clear_trans(tc->ntb, pidx, widx);
		dma_मुक्त_coherent(&tc->ntb->pdev->dev, inmw->size,
				  inmw->mm_base, inmw->dma_base);
	पूर्ण

	inmw->mm_base = शून्य;
	inmw->dma_base = 0;
	inmw->size = 0;
	inmw->dbgfs_file = शून्य;
पूर्ण

अटल sमाप_प्रकार tool_mw_trans_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				  माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_mw *inmw = filep->निजी_data;
	resource_माप_प्रकार addr_align;
	resource_माप_प्रकार size_align;
	resource_माप_प्रकार size_max;
	sमाप_प्रकार ret, off = 0;
	माप_प्रकार buf_size;
	अक्षर *buf;

	buf_size = min_t(माप_प्रकार, size, 512);

	buf = kदो_स्मृति(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = ntb_mw_get_align(inmw->tc->ntb, inmw->pidx, inmw->widx,
			       &addr_align, &size_align, &size_max);
	अगर (ret)
		जाओ err;

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Inbound MW     \t%d\n",
			 inmw->widx);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Port           \t%d (%d)\n",
			 ntb_peer_port_number(inmw->tc->ntb, inmw->pidx),
			 inmw->pidx);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Window Address \t0x%pK\n", inmw->mm_base);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "DMA Address    \t%pad\n",
			 &inmw->dma_base);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Window Size    \t%pap\n",
			 &inmw->size);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Alignment      \t%pap\n",
			 &addr_align);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Size Alignment \t%pap\n",
			 &size_align);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Size Max       \t%pap\n",
			 &size_max);

	ret = simple_पढ़ो_from_buffer(ubuf, size, offp, buf, off);

err:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार tool_mw_trans_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
				   माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_mw *inmw = filep->निजी_data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक_from_user(ubuf, size, 0, &val);
	अगर (ret)
		वापस ret;

	tool_मुक्त_mw(inmw->tc, inmw->pidx, inmw->widx);
	अगर (val) अणु
		ret = tool_setup_mw(inmw->tc, inmw->pidx, inmw->widx, val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_mw_trans_fops,
		      tool_mw_trans_पढ़ो,
		      tool_mw_trans_ग_लिखो);

अटल sमाप_प्रकार tool_peer_mw_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				 माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_mw *ouपंचांगw = filep->निजी_data;
	loff_t pos = *offp;
	sमाप_प्रकार ret;
	व्योम *buf;

	अगर (ouपंचांगw->io_base == शून्य)
		वापस -EIO;

	अगर (pos >= ouपंचांगw->size || !size)
		वापस 0;

	अगर (size > ouपंचांगw->size - pos)
		size = ouपंचांगw->size - pos;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	स_नकल_fromio(buf, ouपंचांगw->io_base + pos, size);
	ret = copy_to_user(ubuf, buf, size);
	अगर (ret == size) अणु
		ret = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	size -= ret;
	*offp = pos + size;
	ret = size;

err_मुक्त:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार tool_peer_mw_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
				  माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_mw *ouपंचांगw = filep->निजी_data;
	sमाप_प्रकार ret;
	loff_t pos = *offp;
	व्योम *buf;

	अगर (ouपंचांगw->io_base == शून्य)
		वापस -EIO;

	अगर (pos >= ouपंचांगw->size || !size)
		वापस 0;
	अगर (size > ouपंचांगw->size - pos)
		size = ouपंचांगw->size - pos;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = copy_from_user(buf, ubuf, size);
	अगर (ret == size) अणु
		ret = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	size -= ret;
	*offp = pos + size;
	ret = size;

	स_नकल_toio(ouपंचांगw->io_base + pos, buf, size);

err_मुक्त:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_peer_mw_fops,
		      tool_peer_mw_पढ़ो,
		      tool_peer_mw_ग_लिखो);

अटल पूर्णांक tool_setup_peer_mw(काष्ठा tool_ctx *tc, पूर्णांक pidx, पूर्णांक widx,
			      u64 req_addr, माप_प्रकार req_size)
अणु
	काष्ठा tool_mw *ouपंचांगw = &tc->ouपंचांगws[widx];
	resource_माप_प्रकार map_size;
	phys_addr_t map_base;
	अक्षर buf[TOOL_BUF_LEN];
	पूर्णांक ret;

	अगर (ouपंचांगw->io_base != शून्य)
		वापस 0;

	ret = ntb_peer_mw_get_addr(tc->ntb, widx, &map_base, &map_size);
	अगर (ret)
		वापस ret;

	ret = ntb_peer_mw_set_trans(tc->ntb, pidx, widx, req_addr, req_size);
	अगर (ret)
		वापस ret;

	ouपंचांगw->io_base = ioremap_wc(map_base, map_size);
	अगर (ouपंचांगw->io_base == शून्य) अणु
		ret = -EFAULT;
		जाओ err_clear_trans;
	पूर्ण

	ouपंचांगw->tr_base = req_addr;
	ouपंचांगw->size = req_size;
	ouपंचांगw->pidx = pidx;

	snम_लिखो(buf, माप(buf), "peer_mw%d", widx);
	ouपंचांगw->dbgfs_file = debugfs_create_file(buf, 0600,
					       tc->peers[pidx].dbgfs_dir, ouपंचांगw,
					       &tool_peer_mw_fops);

	वापस 0;

err_clear_trans:
	ntb_peer_mw_clear_trans(tc->ntb, pidx, widx);

	वापस ret;
पूर्ण

अटल व्योम tool_मुक्त_peer_mw(काष्ठा tool_ctx *tc, पूर्णांक widx)
अणु
	काष्ठा tool_mw *ouपंचांगw = &tc->ouपंचांगws[widx];

	debugfs_हटाओ(ouपंचांगw->dbgfs_file);

	अगर (ouपंचांगw->io_base != शून्य) अणु
		iounmap(tc->ouपंचांगws[widx].io_base);
		ntb_peer_mw_clear_trans(tc->ntb, ouपंचांगw->pidx, widx);
	पूर्ण

	ouपंचांगw->io_base = शून्य;
	ouपंचांगw->tr_base = 0;
	ouपंचांगw->size = 0;
	ouपंचांगw->pidx = -1;
	ouपंचांगw->dbgfs_file = शून्य;
पूर्ण

अटल sमाप_प्रकार tool_peer_mw_trans_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
					माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_mw_wrap *ouपंचांगw_wrap = filep->निजी_data;
	काष्ठा tool_mw *ouपंचांगw = ouपंचांगw_wrap->mw;
	resource_माप_प्रकार map_size;
	phys_addr_t map_base;
	sमाप_प्रकार off = 0;
	माप_प्रकार buf_size;
	अक्षर *buf;
	पूर्णांक ret;

	ret = ntb_peer_mw_get_addr(ouपंचांगw->tc->ntb, ouपंचांगw->widx,
				  &map_base, &map_size);
	अगर (ret)
		वापस ret;

	buf_size = min_t(माप_प्रकार, size, 512);

	buf = kदो_स्मृति(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Outbound MW:        \t%d\n", ouपंचांगw->widx);

	अगर (ouपंचांगw->io_base != शून्य) अणु
		off += scnम_लिखो(buf + off, buf_size - off,
			"Port attached       \t%d (%d)\n",
			ntb_peer_port_number(ouपंचांगw->tc->ntb, ouपंचांगw->pidx),
			ouपंचांगw->pidx);
	पूर्ण अन्यथा अणु
		off += scnम_लिखो(buf + off, buf_size - off,
				 "Port attached       \t-1 (-1)\n");
	पूर्ण

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Virtual address     \t0x%pK\n", ouपंचांगw->io_base);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Phys Address        \t%pap\n", &map_base);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Mapping Size        \t%pap\n", &map_size);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Translation Address \t0x%016llx\n", ouपंचांगw->tr_base);

	off += scnम_लिखो(buf + off, buf_size - off,
			 "Window Size         \t%pap\n", &ouपंचांगw->size);

	ret = simple_पढ़ो_from_buffer(ubuf, size, offp, buf, off);
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार tool_peer_mw_trans_ग_लिखो(काष्ठा file *filep,
					स्थिर अक्षर __user *ubuf,
					माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_mw_wrap *ouपंचांगw_wrap = filep->निजी_data;
	काष्ठा tool_mw *ouपंचांगw = ouपंचांगw_wrap->mw;
	माप_प्रकार buf_size, wsize;
	अक्षर buf[TOOL_BUF_LEN];
	पूर्णांक ret, n;
	u64 addr;

	buf_size = min(size, (माप(buf) - 1));
	अगर (copy_from_user(buf, ubuf, buf_size))
		वापस -EFAULT;

	buf[buf_size] = '\0';

	n = माला_पूछो(buf, "%lli:%zi", &addr, &wsize);
	अगर (n != 2)
		वापस -EINVAL;

	tool_मुक्त_peer_mw(ouपंचांगw->tc, ouपंचांगw->widx);
	अगर (wsize) अणु
		ret = tool_setup_peer_mw(ouपंचांगw->tc, ouपंचांगw_wrap->pidx,
					 ouपंचांगw->widx, addr, wsize);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_peer_mw_trans_fops,
		      tool_peer_mw_trans_पढ़ो,
		      tool_peer_mw_trans_ग_लिखो);

अटल पूर्णांक tool_init_mws(काष्ठा tool_ctx *tc)
अणु
	पूर्णांक widx, pidx;

	/* Initialize outbound memory winकरोws */
	tc->ouपंचांगw_cnt = ntb_peer_mw_count(tc->ntb);
	tc->ouपंचांगws = devm_kसुस्मृति(&tc->ntb->dev, tc->ouपंचांगw_cnt,
				  माप(*tc->ouपंचांगws), GFP_KERNEL);
	अगर (tc->ouपंचांगws == शून्य)
		वापस -ENOMEM;

	क्रम (widx = 0; widx < tc->ouपंचांगw_cnt; widx++) अणु
		tc->ouपंचांगws[widx].widx = widx;
		tc->ouपंचांगws[widx].pidx = -1;
		tc->ouपंचांगws[widx].tc = tc;
	पूर्ण

	/* Initialize inbound memory winकरोws and outbound MWs wrapper */
	क्रम (pidx = 0; pidx < tc->peer_cnt; pidx++) अणु
		tc->peers[pidx].inmw_cnt = ntb_mw_count(tc->ntb, pidx);
		tc->peers[pidx].inmws =
			devm_kसुस्मृति(&tc->ntb->dev, tc->peers[pidx].inmw_cnt,
				    माप(*tc->peers[pidx].inmws), GFP_KERNEL);
		अगर (tc->peers[pidx].inmws == शून्य)
			वापस -ENOMEM;

		क्रम (widx = 0; widx < tc->peers[pidx].inmw_cnt; widx++) अणु
			tc->peers[pidx].inmws[widx].widx = widx;
			tc->peers[pidx].inmws[widx].pidx = pidx;
			tc->peers[pidx].inmws[widx].tc = tc;
		पूर्ण

		tc->peers[pidx].ouपंचांगw_cnt = ntb_peer_mw_count(tc->ntb);
		tc->peers[pidx].ouपंचांगws =
			devm_kसुस्मृति(&tc->ntb->dev, tc->peers[pidx].ouपंचांगw_cnt,
				   माप(*tc->peers[pidx].ouपंचांगws), GFP_KERNEL);

		क्रम (widx = 0; widx < tc->peers[pidx].ouपंचांगw_cnt; widx++) अणु
			tc->peers[pidx].ouपंचांगws[widx].pidx = pidx;
			tc->peers[pidx].ouपंचांगws[widx].mw = &tc->ouपंचांगws[widx];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tool_clear_mws(काष्ठा tool_ctx *tc)
अणु
	पूर्णांक widx, pidx;

	/* Free outbound memory winकरोws */
	क्रम (widx = 0; widx < tc->ouपंचांगw_cnt; widx++)
		tool_मुक्त_peer_mw(tc, widx);

	/* Free outbound memory winकरोws */
	क्रम (pidx = 0; pidx < tc->peer_cnt; pidx++)
		क्रम (widx = 0; widx < tc->peers[pidx].inmw_cnt; widx++)
			tool_मुक्त_mw(tc, pidx, widx);
पूर्ण

/*==============================================================================
 *                       Doorbell पढ़ो/ग_लिखो methods
 *==============================================================================
 */

अटल sमाप_प्रकार tool_db_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
			    माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_पढ़ो(tc, ubuf, size, offp, tc->ntb->ops->db_पढ़ो);
पूर्ण

अटल sमाप_प्रकार tool_db_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
			     माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_ग_लिखो(tc, ubuf, size, offp, tc->ntb->ops->db_set,
			     tc->ntb->ops->db_clear);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_db_fops,
		      tool_db_पढ़ो,
		      tool_db_ग_लिखो);

अटल sमाप_प्रकार tool_db_valid_mask_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				       माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_पढ़ो(tc, ubuf, size, offp, tc->ntb->ops->db_valid_mask);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_db_valid_mask_fops,
		      tool_db_valid_mask_पढ़ो,
		      शून्य);

अटल sमाप_प्रकार tool_db_mask_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				 माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_पढ़ो(tc, ubuf, size, offp, tc->ntb->ops->db_पढ़ो_mask);
पूर्ण

अटल sमाप_प्रकार tool_db_mask_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_ग_लिखो(tc, ubuf, size, offp, tc->ntb->ops->db_set_mask,
			     tc->ntb->ops->db_clear_mask);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_db_mask_fops,
		      tool_db_mask_पढ़ो,
		      tool_db_mask_ग_लिखो);

अटल sमाप_प्रकार tool_peer_db_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				 माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_पढ़ो(tc, ubuf, size, offp, tc->ntb->ops->peer_db_पढ़ो);
पूर्ण

अटल sमाप_प्रकार tool_peer_db_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
				  माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_ग_लिखो(tc, ubuf, size, offp, tc->ntb->ops->peer_db_set,
			     tc->ntb->ops->peer_db_clear);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_peer_db_fops,
		      tool_peer_db_पढ़ो,
		      tool_peer_db_ग_लिखो);

अटल sमाप_प्रकार tool_peer_db_mask_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				   माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_पढ़ो(tc, ubuf, size, offp,
			    tc->ntb->ops->peer_db_पढ़ो_mask);
पूर्ण

अटल sमाप_प्रकार tool_peer_db_mask_ग_लिखो(काष्ठा file *filep,
				       स्थिर अक्षर __user *ubuf,
				       माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_ग_लिखो(tc, ubuf, size, offp,
			     tc->ntb->ops->peer_db_set_mask,
			     tc->ntb->ops->peer_db_clear_mask);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_peer_db_mask_fops,
		      tool_peer_db_mask_पढ़ो,
		      tool_peer_db_mask_ग_लिखो);

अटल sमाप_प्रकार tool_db_event_ग_लिखो(काष्ठा file *filep,
				   स्थिर अक्षर __user *ubuf,
				   माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;
	u64 val;
	पूर्णांक ret;

	ret = kstrtou64_from_user(ubuf, size, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (रुको_event_पूर्णांकerruptible(tc->db_wq, ntb_db_पढ़ो(tc->ntb) == val))
		वापस -ERESTART;

	वापस size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_db_event_fops,
		      शून्य,
		      tool_db_event_ग_लिखो);

/*==============================================================================
 *                       Scratchpads पढ़ो/ग_लिखो methods
 *==============================================================================
 */

अटल sमाप_प्रकार tool_spad_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
			      माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_spad *spad = filep->निजी_data;
	अक्षर buf[TOOL_BUF_LEN];
	sमाप_प्रकार pos;

	अगर (!spad->tc->ntb->ops->spad_पढ़ो)
		वापस -EINVAL;

	pos = scnम_लिखो(buf, माप(buf), "%#x\n",
		ntb_spad_पढ़ो(spad->tc->ntb, spad->sidx));

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
पूर्ण

अटल sमाप_प्रकार tool_spad_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_spad *spad = filep->निजी_data;
	u32 val;
	पूर्णांक ret;

	अगर (!spad->tc->ntb->ops->spad_ग_लिखो) अणु
		dev_dbg(&spad->tc->ntb->dev, "no spad write fn\n");
		वापस -EINVAL;
	पूर्ण

	ret = kstrtou32_from_user(ubuf, size, 0, &val);
	अगर (ret)
		वापस ret;

	ret = ntb_spad_ग_लिखो(spad->tc->ntb, spad->sidx, val);

	वापस ret ?: size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_spad_fops,
		      tool_spad_पढ़ो,
		      tool_spad_ग_लिखो);

अटल sमाप_प्रकार tool_peer_spad_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				   माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_spad *spad = filep->निजी_data;
	अक्षर buf[TOOL_BUF_LEN];
	sमाप_प्रकार pos;

	अगर (!spad->tc->ntb->ops->peer_spad_पढ़ो)
		वापस -EINVAL;

	pos = scnम_लिखो(buf, माप(buf), "%#x\n",
		ntb_peer_spad_पढ़ो(spad->tc->ntb, spad->pidx, spad->sidx));

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
पूर्ण

अटल sमाप_प्रकार tool_peer_spad_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
				    माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_spad *spad = filep->निजी_data;
	u32 val;
	पूर्णांक ret;

	अगर (!spad->tc->ntb->ops->peer_spad_ग_लिखो) अणु
		dev_dbg(&spad->tc->ntb->dev, "no spad write fn\n");
		वापस -EINVAL;
	पूर्ण

	ret = kstrtou32_from_user(ubuf, size, 0, &val);
	अगर (ret)
		वापस ret;

	ret = ntb_peer_spad_ग_लिखो(spad->tc->ntb, spad->pidx, spad->sidx, val);

	वापस ret ?: size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_peer_spad_fops,
		      tool_peer_spad_पढ़ो,
		      tool_peer_spad_ग_लिखो);

अटल पूर्णांक tool_init_spads(काष्ठा tool_ctx *tc)
अणु
	पूर्णांक sidx, pidx;

	/* Initialize inbound scratchpad काष्ठाures */
	tc->inspad_cnt = ntb_spad_count(tc->ntb);
	tc->inspads = devm_kसुस्मृति(&tc->ntb->dev, tc->inspad_cnt,
				   माप(*tc->inspads), GFP_KERNEL);
	अगर (tc->inspads == शून्य)
		वापस -ENOMEM;

	क्रम (sidx = 0; sidx < tc->inspad_cnt; sidx++) अणु
		tc->inspads[sidx].sidx = sidx;
		tc->inspads[sidx].pidx = -1;
		tc->inspads[sidx].tc = tc;
	पूर्ण

	/* Initialize outbound scratchpad काष्ठाures */
	क्रम (pidx = 0; pidx < tc->peer_cnt; pidx++) अणु
		tc->peers[pidx].outspad_cnt = ntb_spad_count(tc->ntb);
		tc->peers[pidx].outspads =
			devm_kसुस्मृति(&tc->ntb->dev, tc->peers[pidx].outspad_cnt,
				माप(*tc->peers[pidx].outspads), GFP_KERNEL);
		अगर (tc->peers[pidx].outspads == शून्य)
			वापस -ENOMEM;

		क्रम (sidx = 0; sidx < tc->peers[pidx].outspad_cnt; sidx++) अणु
			tc->peers[pidx].outspads[sidx].sidx = sidx;
			tc->peers[pidx].outspads[sidx].pidx = pidx;
			tc->peers[pidx].outspads[sidx].tc = tc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*==============================================================================
 *                       Messages पढ़ो/ग_लिखो methods
 *==============================================================================
 */

अटल sमाप_प्रकार tool_inmsg_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
			       माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_msg *msg = filep->निजी_data;
	अक्षर buf[TOOL_BUF_LEN];
	sमाप_प्रकार pos;
	u32 data;
	पूर्णांक pidx;

	data = ntb_msg_पढ़ो(msg->tc->ntb, &pidx, msg->midx);

	pos = scnम_लिखो(buf, माप(buf), "0x%08x<-%d\n", data, pidx);

	वापस simple_पढ़ो_from_buffer(ubuf, size, offp, buf, pos);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_inmsg_fops,
		      tool_inmsg_पढ़ो,
		      शून्य);

अटल sमाप_प्रकार tool_ouपंचांगsg_ग_लिखो(काष्ठा file *filep,
				 स्थिर अक्षर __user *ubuf,
				 माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_msg *msg = filep->निजी_data;
	u32 val;
	पूर्णांक ret;

	ret = kstrtou32_from_user(ubuf, size, 0, &val);
	अगर (ret)
		वापस ret;

	ret = ntb_peer_msg_ग_लिखो(msg->tc->ntb, msg->pidx, msg->midx, val);

	वापस ret ? : size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_ouपंचांगsg_fops,
		      शून्य,
		      tool_ouपंचांगsg_ग_लिखो);

अटल sमाप_प्रकार tool_msg_sts_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				 माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_पढ़ो(tc, ubuf, size, offp, tc->ntb->ops->msg_पढ़ो_sts);
पूर्ण

अटल sमाप_प्रकार tool_msg_sts_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
				  माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_ग_लिखो(tc, ubuf, size, offp, शून्य,
			     tc->ntb->ops->msg_clear_sts);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_msg_sts_fops,
		      tool_msg_sts_पढ़ो,
		      tool_msg_sts_ग_लिखो);

अटल sमाप_प्रकार tool_msg_inbits_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				    माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_पढ़ो(tc, ubuf, size, offp, tc->ntb->ops->msg_inbits);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_msg_inbits_fops,
		      tool_msg_inbits_पढ़ो,
		      शून्य);

अटल sमाप_प्रकार tool_msg_outbits_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				     माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_पढ़ो(tc, ubuf, size, offp, tc->ntb->ops->msg_outbits);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_msg_outbits_fops,
		      tool_msg_outbits_पढ़ो,
		      शून्य);

अटल sमाप_प्रकार tool_msg_mask_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
				   माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;

	वापस tool_fn_ग_लिखो(tc, ubuf, size, offp,
			     tc->ntb->ops->msg_set_mask,
			     tc->ntb->ops->msg_clear_mask);
पूर्ण

अटल TOOL_FOPS_RDWR(tool_msg_mask_fops,
		      शून्य,
		      tool_msg_mask_ग_लिखो);

अटल sमाप_प्रकार tool_msg_event_ग_लिखो(काष्ठा file *filep,
				    स्थिर अक्षर __user *ubuf,
				    माप_प्रकार size, loff_t *offp)
अणु
	काष्ठा tool_ctx *tc = filep->निजी_data;
	u64 val;
	पूर्णांक ret;

	ret = kstrtou64_from_user(ubuf, size, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (रुको_event_पूर्णांकerruptible(tc->msg_wq,
		ntb_msg_पढ़ो_sts(tc->ntb) == val))
		वापस -ERESTART;

	वापस size;
पूर्ण

अटल TOOL_FOPS_RDWR(tool_msg_event_fops,
		      शून्य,
		      tool_msg_event_ग_लिखो);

अटल पूर्णांक tool_init_msgs(काष्ठा tool_ctx *tc)
अणु
	पूर्णांक midx, pidx;

	/* Initialize inbound message काष्ठाures */
	tc->inmsg_cnt = ntb_msg_count(tc->ntb);
	tc->inmsgs = devm_kसुस्मृति(&tc->ntb->dev, tc->inmsg_cnt,
				   माप(*tc->inmsgs), GFP_KERNEL);
	अगर (tc->inmsgs == शून्य)
		वापस -ENOMEM;

	क्रम (midx = 0; midx < tc->inmsg_cnt; midx++) अणु
		tc->inmsgs[midx].midx = midx;
		tc->inmsgs[midx].pidx = -1;
		tc->inmsgs[midx].tc = tc;
	पूर्ण

	/* Initialize outbound message काष्ठाures */
	क्रम (pidx = 0; pidx < tc->peer_cnt; pidx++) अणु
		tc->peers[pidx].ouपंचांगsg_cnt = ntb_msg_count(tc->ntb);
		tc->peers[pidx].ouपंचांगsgs =
			devm_kसुस्मृति(&tc->ntb->dev, tc->peers[pidx].ouपंचांगsg_cnt,
				माप(*tc->peers[pidx].ouपंचांगsgs), GFP_KERNEL);
		अगर (tc->peers[pidx].ouपंचांगsgs == शून्य)
			वापस -ENOMEM;

		क्रम (midx = 0; midx < tc->peers[pidx].ouपंचांगsg_cnt; midx++) अणु
			tc->peers[pidx].ouपंचांगsgs[midx].midx = midx;
			tc->peers[pidx].ouपंचांगsgs[midx].pidx = pidx;
			tc->peers[pidx].ouपंचांगsgs[midx].tc = tc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*==============================================================================
 *                          Initialization methods
 *==============================================================================
 */

अटल काष्ठा tool_ctx *tool_create_data(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा tool_ctx *tc;

	tc = devm_kzalloc(&ntb->dev, माप(*tc), GFP_KERNEL);
	अगर (tc == शून्य)
		वापस ERR_PTR(-ENOMEM);

	tc->ntb = ntb;
	init_रुकोqueue_head(&tc->link_wq);
	init_रुकोqueue_head(&tc->db_wq);
	init_रुकोqueue_head(&tc->msg_wq);

	अगर (ntb_db_is_unsafe(ntb))
		dev_dbg(&ntb->dev, "doorbell is unsafe\n");

	अगर (ntb_spad_is_unsafe(ntb))
		dev_dbg(&ntb->dev, "scratchpad is unsafe\n");

	वापस tc;
पूर्ण

अटल व्योम tool_clear_data(काष्ठा tool_ctx *tc)
अणु
	wake_up(&tc->link_wq);
	wake_up(&tc->db_wq);
	wake_up(&tc->msg_wq);
पूर्ण

अटल पूर्णांक tool_init_ntb(काष्ठा tool_ctx *tc)
अणु
	वापस ntb_set_ctx(tc->ntb, tc, &tool_ops);
पूर्ण

अटल व्योम tool_clear_ntb(काष्ठा tool_ctx *tc)
अणु
	ntb_clear_ctx(tc->ntb);
	ntb_link_disable(tc->ntb);
पूर्ण

अटल व्योम tool_setup_dbgfs(काष्ठा tool_ctx *tc)
अणु
	पूर्णांक pidx, widx, sidx, midx;
	अक्षर buf[TOOL_BUF_LEN];

	/* This modules is useless without dbgfs... */
	अगर (!tool_dbgfs_topdir) अणु
		tc->dbgfs_dir = शून्य;
		वापस;
	पूर्ण

	tc->dbgfs_dir = debugfs_create_dir(dev_name(&tc->ntb->dev),
					   tool_dbgfs_topdir);
	अगर (!tc->dbgfs_dir)
		वापस;

	debugfs_create_file("port", 0600, tc->dbgfs_dir,
			    tc, &tool_port_fops);

	debugfs_create_file("link", 0600, tc->dbgfs_dir,
			    tc, &tool_link_fops);

	debugfs_create_file("db", 0600, tc->dbgfs_dir,
			    tc, &tool_db_fops);

	debugfs_create_file("db_valid_mask", 0600, tc->dbgfs_dir,
			    tc, &tool_db_valid_mask_fops);

	debugfs_create_file("db_mask", 0600, tc->dbgfs_dir,
			    tc, &tool_db_mask_fops);

	debugfs_create_file("db_event", 0600, tc->dbgfs_dir,
			    tc, &tool_db_event_fops);

	debugfs_create_file("peer_db", 0600, tc->dbgfs_dir,
			    tc, &tool_peer_db_fops);

	debugfs_create_file("peer_db_mask", 0600, tc->dbgfs_dir,
			    tc, &tool_peer_db_mask_fops);

	अगर (tc->inspad_cnt != 0) अणु
		क्रम (sidx = 0; sidx < tc->inspad_cnt; sidx++) अणु
			snम_लिखो(buf, माप(buf), "spad%d", sidx);

			debugfs_create_file(buf, 0600, tc->dbgfs_dir,
					   &tc->inspads[sidx], &tool_spad_fops);
		पूर्ण
	पूर्ण

	अगर (tc->inmsg_cnt != 0) अणु
		क्रम (midx = 0; midx < tc->inmsg_cnt; midx++) अणु
			snम_लिखो(buf, माप(buf), "msg%d", midx);
			debugfs_create_file(buf, 0600, tc->dbgfs_dir,
					   &tc->inmsgs[midx], &tool_inmsg_fops);
		पूर्ण

		debugfs_create_file("msg_sts", 0600, tc->dbgfs_dir,
				    tc, &tool_msg_sts_fops);

		debugfs_create_file("msg_inbits", 0600, tc->dbgfs_dir,
				    tc, &tool_msg_inbits_fops);

		debugfs_create_file("msg_outbits", 0600, tc->dbgfs_dir,
				    tc, &tool_msg_outbits_fops);

		debugfs_create_file("msg_mask", 0600, tc->dbgfs_dir,
				    tc, &tool_msg_mask_fops);

		debugfs_create_file("msg_event", 0600, tc->dbgfs_dir,
				    tc, &tool_msg_event_fops);
	पूर्ण

	क्रम (pidx = 0; pidx < tc->peer_cnt; pidx++) अणु
		snम_लिखो(buf, माप(buf), "peer%d", pidx);
		tc->peers[pidx].dbgfs_dir =
			debugfs_create_dir(buf, tc->dbgfs_dir);

		debugfs_create_file("port", 0600,
				    tc->peers[pidx].dbgfs_dir,
				    &tc->peers[pidx], &tool_peer_port_fops);

		debugfs_create_file("link", 0200,
				    tc->peers[pidx].dbgfs_dir,
				    &tc->peers[pidx], &tool_peer_link_fops);

		debugfs_create_file("link_event", 0200,
				  tc->peers[pidx].dbgfs_dir,
				  &tc->peers[pidx], &tool_peer_link_event_fops);

		क्रम (widx = 0; widx < tc->peers[pidx].inmw_cnt; widx++) अणु
			snम_लिखो(buf, माप(buf), "mw_trans%d", widx);
			debugfs_create_file(buf, 0600,
					    tc->peers[pidx].dbgfs_dir,
					    &tc->peers[pidx].inmws[widx],
					    &tool_mw_trans_fops);
		पूर्ण

		क्रम (widx = 0; widx < tc->peers[pidx].ouपंचांगw_cnt; widx++) अणु
			snम_लिखो(buf, माप(buf), "peer_mw_trans%d", widx);
			debugfs_create_file(buf, 0600,
					    tc->peers[pidx].dbgfs_dir,
					    &tc->peers[pidx].ouपंचांगws[widx],
					    &tool_peer_mw_trans_fops);
		पूर्ण

		क्रम (sidx = 0; sidx < tc->peers[pidx].outspad_cnt; sidx++) अणु
			snम_लिखो(buf, माप(buf), "spad%d", sidx);

			debugfs_create_file(buf, 0600,
					    tc->peers[pidx].dbgfs_dir,
					    &tc->peers[pidx].outspads[sidx],
					    &tool_peer_spad_fops);
		पूर्ण

		क्रम (midx = 0; midx < tc->peers[pidx].ouपंचांगsg_cnt; midx++) अणु
			snम_लिखो(buf, माप(buf), "msg%d", midx);
			debugfs_create_file(buf, 0600,
					    tc->peers[pidx].dbgfs_dir,
					    &tc->peers[pidx].ouपंचांगsgs[midx],
					    &tool_ouपंचांगsg_fops);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tool_clear_dbgfs(काष्ठा tool_ctx *tc)
अणु
	debugfs_हटाओ_recursive(tc->dbgfs_dir);
पूर्ण

अटल पूर्णांक tool_probe(काष्ठा ntb_client *self, काष्ठा ntb_dev *ntb)
अणु
	काष्ठा tool_ctx *tc;
	पूर्णांक ret;

	tc = tool_create_data(ntb);
	अगर (IS_ERR(tc))
		वापस PTR_ERR(tc);

	ret = tool_init_peers(tc);
	अगर (ret != 0)
		जाओ err_clear_data;

	ret = tool_init_mws(tc);
	अगर (ret != 0)
		जाओ err_clear_data;

	ret = tool_init_spads(tc);
	अगर (ret != 0)
		जाओ err_clear_mws;

	ret = tool_init_msgs(tc);
	अगर (ret != 0)
		जाओ err_clear_mws;

	ret = tool_init_ntb(tc);
	अगर (ret != 0)
		जाओ err_clear_mws;

	tool_setup_dbgfs(tc);

	वापस 0;

err_clear_mws:
	tool_clear_mws(tc);

err_clear_data:
	tool_clear_data(tc);

	वापस ret;
पूर्ण

अटल व्योम tool_हटाओ(काष्ठा ntb_client *self, काष्ठा ntb_dev *ntb)
अणु
	काष्ठा tool_ctx *tc = ntb->ctx;

	tool_clear_dbgfs(tc);

	tool_clear_ntb(tc);

	tool_clear_mws(tc);

	tool_clear_data(tc);
पूर्ण

अटल काष्ठा ntb_client tool_client = अणु
	.ops = अणु
		.probe = tool_probe,
		.हटाओ = tool_हटाओ,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init tool_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (debugfs_initialized())
		tool_dbgfs_topdir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	ret = ntb_रेजिस्टर_client(&tool_client);
	अगर (ret)
		debugfs_हटाओ_recursive(tool_dbgfs_topdir);

	वापस ret;
पूर्ण
module_init(tool_init);

अटल व्योम __निकास tool_निकास(व्योम)
अणु
	ntb_unरेजिस्टर_client(&tool_client);
	debugfs_हटाओ_recursive(tool_dbgfs_topdir);
पूर्ण
module_निकास(tool_निकास);
