<शैली गुरु>
/*
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/parser.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/inet.h>
#समावेश <rdma/ib_cache.h>

#समावेश <linux/atomic.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/srp.h>
#समावेश <scsi/scsi_transport_srp.h>

#समावेश "ib_srp.h"

#घोषणा DRV_NAME	"ib_srp"
#घोषणा PFX		DRV_NAME ": "

MODULE_AUTHOR("Roland Dreier");
MODULE_DESCRIPTION("InfiniBand SCSI RDMA Protocol initiator");
MODULE_LICENSE("Dual BSD/GPL");

#अगर !defined(CONFIG_DYNAMIC_DEBUG)
#घोषणा DEFINE_DYNAMIC_DEBUG_METADATA(name, fmt)
#घोषणा DYNAMIC_DEBUG_BRANCH(descriptor) false
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक srp_sg_tablesize;
अटल अचिन्हित पूर्णांक cmd_sg_entries;
अटल अचिन्हित पूर्णांक indirect_sg_entries;
अटल bool allow_ext_sg;
अटल bool रेजिस्टर_always = true;
अटल bool never_रेजिस्टर;
अटल पूर्णांक topspin_workarounds = 1;

module_param(srp_sg_tablesize, uपूर्णांक, 0444);
MODULE_PARM_DESC(srp_sg_tablesize, "Deprecated name for cmd_sg_entries");

module_param(cmd_sg_entries, uपूर्णांक, 0444);
MODULE_PARM_DESC(cmd_sg_entries,
		 "Default number of gather/scatter entries in the SRP command (default is 12, max 255)");

module_param(indirect_sg_entries, uपूर्णांक, 0444);
MODULE_PARM_DESC(indirect_sg_entries,
		 "Default max number of gather/scatter entries (default is 12, max is " __stringअगरy(SG_MAX_SEGMENTS) ")");

module_param(allow_ext_sg, bool, 0444);
MODULE_PARM_DESC(allow_ext_sg,
		  "Default behavior when there are more than cmd_sg_entries S/G entries after mapping; fails the request when false (default false)");

module_param(topspin_workarounds, पूर्णांक, 0444);
MODULE_PARM_DESC(topspin_workarounds,
		 "Enable workarounds for Topspin/Cisco SRP target bugs if != 0");

module_param(रेजिस्टर_always, bool, 0444);
MODULE_PARM_DESC(रेजिस्टर_always,
		 "Use memory registration even for contiguous memory regions");

module_param(never_रेजिस्टर, bool, 0444);
MODULE_PARM_DESC(never_रेजिस्टर, "Never register memory");

अटल स्थिर काष्ठा kernel_param_ops srp_पंचांगo_ops;

अटल पूर्णांक srp_reconnect_delay = 10;
module_param_cb(reconnect_delay, &srp_पंचांगo_ops, &srp_reconnect_delay,
		S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(reconnect_delay, "Time between successive reconnect attempts");

अटल पूर्णांक srp_fast_io_fail_पंचांगo = 15;
module_param_cb(fast_io_fail_पंचांगo, &srp_पंचांगo_ops, &srp_fast_io_fail_पंचांगo,
		S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(fast_io_fail_पंचांगo,
		 "Number of seconds between the observation of a transport"
		 " layer error and failing all I/O. \"off\" means that this"
		 " functionality is disabled.");

अटल पूर्णांक srp_dev_loss_पंचांगo = 600;
module_param_cb(dev_loss_पंचांगo, &srp_पंचांगo_ops, &srp_dev_loss_पंचांगo,
		S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dev_loss_पंचांगo,
		 "Maximum number of seconds that the SRP transport should"
		 " insulate transport layer errors. After this time has been"
		 " exceeded the SCSI host is removed. Should be"
		 " between 1 and " __stringअगरy(SCSI_DEVICE_BLOCK_MAX_TIMEOUT)
		 " if fast_io_fail_tmo has not been set. \"off\" means that"
		 " this functionality is disabled.");

अटल bool srp_use_imm_data = true;
module_param_named(use_imm_data, srp_use_imm_data, bool, 0644);
MODULE_PARM_DESC(use_imm_data,
		 "Whether or not to request permission to use immediate data during SRP login.");

अटल अचिन्हित पूर्णांक srp_max_imm_data = 8 * 1024;
module_param_named(max_imm_data, srp_max_imm_data, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_imm_data, "Maximum immediate data size.");

अटल अचिन्हित ch_count;
module_param(ch_count, uपूर्णांक, 0444);
MODULE_PARM_DESC(ch_count,
		 "Number of RDMA channels to use for communication with an SRP target. Using more than one channel improves performance if the HCA supports multiple completion vectors. The default value is the minimum of four times the number of online CPU sockets and the number of completion vectors supported by the HCA.");

अटल पूर्णांक srp_add_one(काष्ठा ib_device *device);
अटल व्योम srp_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data);
अटल व्योम srp_नाम_dev(काष्ठा ib_device *device, व्योम *client_data);
अटल व्योम srp_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम srp_handle_qp_err(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc,
		स्थिर अक्षर *opname);
अटल पूर्णांक srp_ib_cm_handler(काष्ठा ib_cm_id *cm_id,
			     स्थिर काष्ठा ib_cm_event *event);
अटल पूर्णांक srp_rdma_cm_handler(काष्ठा rdma_cm_id *cm_id,
			       काष्ठा rdma_cm_event *event);

अटल काष्ठा scsi_transport_ढाँचा *ib_srp_transport_ढाँचा;
अटल काष्ठा workqueue_काष्ठा *srp_हटाओ_wq;

अटल काष्ठा ib_client srp_client = अणु
	.name   = "srp",
	.add    = srp_add_one,
	.हटाओ = srp_हटाओ_one,
	.नाम = srp_नाम_dev
पूर्ण;

अटल काष्ठा ib_sa_client srp_sa_client;

अटल पूर्णांक srp_पंचांगo_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक पंचांगo = *(पूर्णांक *)kp->arg;

	अगर (पंचांगo >= 0)
		वापस sysfs_emit(buffer, "%d\n", पंचांगo);
	अन्यथा
		वापस sysfs_emit(buffer, "off\n");
पूर्ण

अटल पूर्णांक srp_पंचांगo_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक पंचांगo, res;

	res = srp_parse_पंचांगo(&पंचांगo, val);
	अगर (res)
		जाओ out;

	अगर (kp->arg == &srp_reconnect_delay)
		res = srp_पंचांगo_valid(पंचांगo, srp_fast_io_fail_पंचांगo,
				    srp_dev_loss_पंचांगo);
	अन्यथा अगर (kp->arg == &srp_fast_io_fail_पंचांगo)
		res = srp_पंचांगo_valid(srp_reconnect_delay, पंचांगo, srp_dev_loss_पंचांगo);
	अन्यथा
		res = srp_पंचांगo_valid(srp_reconnect_delay, srp_fast_io_fail_पंचांगo,
				    पंचांगo);
	अगर (res)
		जाओ out;
	*(पूर्णांक *)kp->arg = पंचांगo;

out:
	वापस res;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops srp_पंचांगo_ops = अणु
	.get = srp_पंचांगo_get,
	.set = srp_पंचांगo_set,
पूर्ण;

अटल अंतरभूत काष्ठा srp_target_port *host_to_target(काष्ठा Scsi_Host *host)
अणु
	वापस (काष्ठा srp_target_port *) host->hostdata;
पूर्ण

अटल स्थिर अक्षर *srp_target_info(काष्ठा Scsi_Host *host)
अणु
	वापस host_to_target(host)->target_name;
पूर्ण

अटल पूर्णांक srp_target_is_topspin(काष्ठा srp_target_port *target)
अणु
	अटल स्थिर u8 topspin_oui[3] = अणु 0x00, 0x05, 0xad पूर्ण;
	अटल स्थिर u8 cisco_oui[3]   = अणु 0x00, 0x1b, 0x0d पूर्ण;

	वापस topspin_workarounds &&
		(!स_भेद(&target->ioc_guid, topspin_oui, माप topspin_oui) ||
		 !स_भेद(&target->ioc_guid, cisco_oui, माप cisco_oui));
पूर्ण

अटल काष्ठा srp_iu *srp_alloc_iu(काष्ठा srp_host *host, माप_प्रकार size,
				   gfp_t gfp_mask,
				   क्रमागत dma_data_direction direction)
अणु
	काष्ठा srp_iu *iu;

	iu = kदो_स्मृति(माप *iu, gfp_mask);
	अगर (!iu)
		जाओ out;

	iu->buf = kzalloc(size, gfp_mask);
	अगर (!iu->buf)
		जाओ out_मुक्त_iu;

	iu->dma = ib_dma_map_single(host->srp_dev->dev, iu->buf, size,
				    direction);
	अगर (ib_dma_mapping_error(host->srp_dev->dev, iu->dma))
		जाओ out_मुक्त_buf;

	iu->size      = size;
	iu->direction = direction;

	वापस iu;

out_मुक्त_buf:
	kमुक्त(iu->buf);
out_मुक्त_iu:
	kमुक्त(iu);
out:
	वापस शून्य;
पूर्ण

अटल व्योम srp_मुक्त_iu(काष्ठा srp_host *host, काष्ठा srp_iu *iu)
अणु
	अगर (!iu)
		वापस;

	ib_dma_unmap_single(host->srp_dev->dev, iu->dma, iu->size,
			    iu->direction);
	kमुक्त(iu->buf);
	kमुक्त(iu);
पूर्ण

अटल व्योम srp_qp_event(काष्ठा ib_event *event, व्योम *context)
अणु
	pr_debug("QP event %s (%d)\n",
		 ib_event_msg(event->event), event->event);
पूर्ण

अटल पूर्णांक srp_init_ib_qp(काष्ठा srp_target_port *target,
			  काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_attr *attr;
	पूर्णांक ret;

	attr = kदो_स्मृति(माप *attr, GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	ret = ib_find_cached_pkey(target->srp_host->srp_dev->dev,
				  target->srp_host->port,
				  be16_to_cpu(target->ib_cm.pkey),
				  &attr->pkey_index);
	अगर (ret)
		जाओ out;

	attr->qp_state        = IB_QPS_INIT;
	attr->qp_access_flags = (IB_ACCESS_REMOTE_READ |
				    IB_ACCESS_REMOTE_WRITE);
	attr->port_num        = target->srp_host->port;

	ret = ib_modअगरy_qp(qp, attr,
			   IB_QP_STATE		|
			   IB_QP_PKEY_INDEX	|
			   IB_QP_ACCESS_FLAGS	|
			   IB_QP_PORT);

out:
	kमुक्त(attr);
	वापस ret;
पूर्ण

अटल पूर्णांक srp_new_ib_cm_id(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा ib_cm_id *new_cm_id;

	new_cm_id = ib_create_cm_id(target->srp_host->srp_dev->dev,
				    srp_ib_cm_handler, ch);
	अगर (IS_ERR(new_cm_id))
		वापस PTR_ERR(new_cm_id);

	अगर (ch->ib_cm.cm_id)
		ib_destroy_cm_id(ch->ib_cm.cm_id);
	ch->ib_cm.cm_id = new_cm_id;
	अगर (rdma_cap_opa_ah(target->srp_host->srp_dev->dev,
			    target->srp_host->port))
		ch->ib_cm.path.rec_type = SA_PATH_REC_TYPE_OPA;
	अन्यथा
		ch->ib_cm.path.rec_type = SA_PATH_REC_TYPE_IB;
	ch->ib_cm.path.sgid = target->sgid;
	ch->ib_cm.path.dgid = target->ib_cm.orig_dgid;
	ch->ib_cm.path.pkey = target->ib_cm.pkey;
	ch->ib_cm.path.service_id = target->ib_cm.service_id;

	वापस 0;
पूर्ण

अटल पूर्णांक srp_new_rdma_cm_id(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा rdma_cm_id *new_cm_id;
	पूर्णांक ret;

	new_cm_id = rdma_create_id(target->net, srp_rdma_cm_handler, ch,
				   RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(new_cm_id)) अणु
		ret = PTR_ERR(new_cm_id);
		new_cm_id = शून्य;
		जाओ out;
	पूर्ण

	init_completion(&ch->करोne);
	ret = rdma_resolve_addr(new_cm_id, target->rdma_cm.src_specअगरied ?
				&target->rdma_cm.src.sa : शून्य,
				&target->rdma_cm.dst.sa,
				SRP_PATH_REC_TIMEOUT_MS);
	अगर (ret) अणु
		pr_err("No route available from %pISpsc to %pISpsc (%d)\n",
		       &target->rdma_cm.src, &target->rdma_cm.dst, ret);
		जाओ out;
	पूर्ण
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&ch->करोne);
	अगर (ret < 0)
		जाओ out;

	ret = ch->status;
	अगर (ret) अणु
		pr_err("Resolving address %pISpsc failed (%d)\n",
		       &target->rdma_cm.dst, ret);
		जाओ out;
	पूर्ण

	swap(ch->rdma_cm.cm_id, new_cm_id);

out:
	अगर (new_cm_id)
		rdma_destroy_id(new_cm_id);

	वापस ret;
पूर्ण

अटल पूर्णांक srp_new_cm_id(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;

	वापस target->using_rdma_cm ? srp_new_rdma_cm_id(ch) :
		srp_new_ib_cm_id(ch);
पूर्ण

/**
 * srp_destroy_fr_pool() - मुक्त the resources owned by a pool
 * @pool: Fast registration pool to be destroyed.
 */
अटल व्योम srp_destroy_fr_pool(काष्ठा srp_fr_pool *pool)
अणु
	पूर्णांक i;
	काष्ठा srp_fr_desc *d;

	अगर (!pool)
		वापस;

	क्रम (i = 0, d = &pool->desc[0]; i < pool->size; i++, d++) अणु
		अगर (d->mr)
			ib_dereg_mr(d->mr);
	पूर्ण
	kमुक्त(pool);
पूर्ण

/**
 * srp_create_fr_pool() - allocate and initialize a pool क्रम fast registration
 * @device:            IB device to allocate fast registration descriptors क्रम.
 * @pd:                Protection करोमुख्य associated with the FR descriptors.
 * @pool_size:         Number of descriptors to allocate.
 * @max_page_list_len: Maximum fast registration work request page list length.
 */
अटल काष्ठा srp_fr_pool *srp_create_fr_pool(काष्ठा ib_device *device,
					      काष्ठा ib_pd *pd, पूर्णांक pool_size,
					      पूर्णांक max_page_list_len)
अणु
	काष्ठा srp_fr_pool *pool;
	काष्ठा srp_fr_desc *d;
	काष्ठा ib_mr *mr;
	पूर्णांक i, ret = -EINVAL;
	क्रमागत ib_mr_type mr_type;

	अगर (pool_size <= 0)
		जाओ err;
	ret = -ENOMEM;
	pool = kzalloc(काष्ठा_size(pool, desc, pool_size), GFP_KERNEL);
	अगर (!pool)
		जाओ err;
	pool->size = pool_size;
	pool->max_page_list_len = max_page_list_len;
	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->मुक्त_list);

	अगर (device->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG)
		mr_type = IB_MR_TYPE_SG_GAPS;
	अन्यथा
		mr_type = IB_MR_TYPE_MEM_REG;

	क्रम (i = 0, d = &pool->desc[0]; i < pool->size; i++, d++) अणु
		mr = ib_alloc_mr(pd, mr_type, max_page_list_len);
		अगर (IS_ERR(mr)) अणु
			ret = PTR_ERR(mr);
			अगर (ret == -ENOMEM)
				pr_info("%s: ib_alloc_mr() failed. Try to reduce max_cmd_per_lun, max_sect or ch_count\n",
					dev_name(&device->dev));
			जाओ destroy_pool;
		पूर्ण
		d->mr = mr;
		list_add_tail(&d->entry, &pool->मुक्त_list);
	पूर्ण

out:
	वापस pool;

destroy_pool:
	srp_destroy_fr_pool(pool);

err:
	pool = ERR_PTR(ret);
	जाओ out;
पूर्ण

/**
 * srp_fr_pool_get() - obtain a descriptor suitable क्रम fast registration
 * @pool: Pool to obtain descriptor from.
 */
अटल काष्ठा srp_fr_desc *srp_fr_pool_get(काष्ठा srp_fr_pool *pool)
अणु
	काष्ठा srp_fr_desc *d = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pool->lock, flags);
	अगर (!list_empty(&pool->मुक्त_list)) अणु
		d = list_first_entry(&pool->मुक्त_list, typeof(*d), entry);
		list_del(&d->entry);
	पूर्ण
	spin_unlock_irqrestore(&pool->lock, flags);

	वापस d;
पूर्ण

/**
 * srp_fr_pool_put() - put an FR descriptor back in the मुक्त list
 * @pool: Pool the descriptor was allocated from.
 * @desc: Poपूर्णांकer to an array of fast registration descriptor poपूर्णांकers.
 * @n:    Number of descriptors to put back.
 *
 * Note: The caller must alपढ़ोy have queued an invalidation request क्रम
 * desc->mr->rkey beक्रमe calling this function.
 */
अटल व्योम srp_fr_pool_put(काष्ठा srp_fr_pool *pool, काष्ठा srp_fr_desc **desc,
			    पूर्णांक n)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&pool->lock, flags);
	क्रम (i = 0; i < n; i++)
		list_add(&desc[i]->entry, &pool->मुक्त_list);
	spin_unlock_irqrestore(&pool->lock, flags);
पूर्ण

अटल काष्ठा srp_fr_pool *srp_alloc_fr_pool(काष्ठा srp_target_port *target)
अणु
	काष्ठा srp_device *dev = target->srp_host->srp_dev;

	वापस srp_create_fr_pool(dev->dev, dev->pd, target->mr_pool_size,
				  dev->max_pages_per_mr);
पूर्ण

/**
 * srp_destroy_qp() - destroy an RDMA queue pair
 * @ch: SRP RDMA channel.
 *
 * Drain the qp beक्रमe destroying it.  This aव्योमs that the receive
 * completion handler can access the queue pair जबतक it is
 * being destroyed.
 */
अटल व्योम srp_destroy_qp(काष्ठा srp_rdma_ch *ch)
अणु
	spin_lock_irq(&ch->lock);
	ib_process_cq_direct(ch->send_cq, -1);
	spin_unlock_irq(&ch->lock);

	ib_drain_qp(ch->qp);
	ib_destroy_qp(ch->qp);
पूर्ण

अटल पूर्णांक srp_create_ch_ib(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा srp_device *dev = target->srp_host->srp_dev;
	स्थिर काष्ठा ib_device_attr *attr = &dev->dev->attrs;
	काष्ठा ib_qp_init_attr *init_attr;
	काष्ठा ib_cq *recv_cq, *send_cq;
	काष्ठा ib_qp *qp;
	काष्ठा srp_fr_pool *fr_pool = शून्य;
	स्थिर पूर्णांक m = 1 + dev->use_fast_reg * target->mr_per_cmd * 2;
	पूर्णांक ret;

	init_attr = kzalloc(माप *init_attr, GFP_KERNEL);
	अगर (!init_attr)
		वापस -ENOMEM;

	/* queue_size + 1 क्रम ib_drain_rq() */
	recv_cq = ib_alloc_cq(dev->dev, ch, target->queue_size + 1,
				ch->comp_vector, IB_POLL_SOFTIRQ);
	अगर (IS_ERR(recv_cq)) अणु
		ret = PTR_ERR(recv_cq);
		जाओ err;
	पूर्ण

	send_cq = ib_alloc_cq(dev->dev, ch, m * target->queue_size,
				ch->comp_vector, IB_POLL_सूचीECT);
	अगर (IS_ERR(send_cq)) अणु
		ret = PTR_ERR(send_cq);
		जाओ err_recv_cq;
	पूर्ण

	init_attr->event_handler       = srp_qp_event;
	init_attr->cap.max_send_wr     = m * target->queue_size;
	init_attr->cap.max_recv_wr     = target->queue_size + 1;
	init_attr->cap.max_recv_sge    = 1;
	init_attr->cap.max_send_sge    = min(SRP_MAX_SGE, attr->max_send_sge);
	init_attr->sq_sig_type         = IB_SIGNAL_REQ_WR;
	init_attr->qp_type             = IB_QPT_RC;
	init_attr->send_cq             = send_cq;
	init_attr->recv_cq             = recv_cq;

	ch->max_imm_sge = min(init_attr->cap.max_send_sge - 1U, 255U);

	अगर (target->using_rdma_cm) अणु
		ret = rdma_create_qp(ch->rdma_cm.cm_id, dev->pd, init_attr);
		qp = ch->rdma_cm.cm_id->qp;
	पूर्ण अन्यथा अणु
		qp = ib_create_qp(dev->pd, init_attr);
		अगर (!IS_ERR(qp)) अणु
			ret = srp_init_ib_qp(target, qp);
			अगर (ret)
				ib_destroy_qp(qp);
		पूर्ण अन्यथा अणु
			ret = PTR_ERR(qp);
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		pr_err("QP creation failed for dev %s: %d\n",
		       dev_name(&dev->dev->dev), ret);
		जाओ err_send_cq;
	पूर्ण

	अगर (dev->use_fast_reg) अणु
		fr_pool = srp_alloc_fr_pool(target);
		अगर (IS_ERR(fr_pool)) अणु
			ret = PTR_ERR(fr_pool);
			shost_prपूर्णांकk(KERN_WARNING, target->scsi_host, PFX
				     "FR pool allocation failed (%d)\n", ret);
			जाओ err_qp;
		पूर्ण
	पूर्ण

	अगर (ch->qp)
		srp_destroy_qp(ch);
	अगर (ch->recv_cq)
		ib_मुक्त_cq(ch->recv_cq);
	अगर (ch->send_cq)
		ib_मुक्त_cq(ch->send_cq);

	ch->qp = qp;
	ch->recv_cq = recv_cq;
	ch->send_cq = send_cq;

	अगर (dev->use_fast_reg) अणु
		अगर (ch->fr_pool)
			srp_destroy_fr_pool(ch->fr_pool);
		ch->fr_pool = fr_pool;
	पूर्ण

	kमुक्त(init_attr);
	वापस 0;

err_qp:
	अगर (target->using_rdma_cm)
		rdma_destroy_qp(ch->rdma_cm.cm_id);
	अन्यथा
		ib_destroy_qp(qp);

err_send_cq:
	ib_मुक्त_cq(send_cq);

err_recv_cq:
	ib_मुक्त_cq(recv_cq);

err:
	kमुक्त(init_attr);
	वापस ret;
पूर्ण

/*
 * Note: this function may be called without srp_alloc_iu_bufs() having been
 * invoked. Hence the ch->[rt]x_ring checks.
 */
अटल व्योम srp_मुक्त_ch_ib(काष्ठा srp_target_port *target,
			   काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_device *dev = target->srp_host->srp_dev;
	पूर्णांक i;

	अगर (!ch->target)
		वापस;

	अगर (target->using_rdma_cm) अणु
		अगर (ch->rdma_cm.cm_id) अणु
			rdma_destroy_id(ch->rdma_cm.cm_id);
			ch->rdma_cm.cm_id = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ch->ib_cm.cm_id) अणु
			ib_destroy_cm_id(ch->ib_cm.cm_id);
			ch->ib_cm.cm_id = शून्य;
		पूर्ण
	पूर्ण

	/* If srp_new_cm_id() succeeded but srp_create_ch_ib() not, वापस. */
	अगर (!ch->qp)
		वापस;

	अगर (dev->use_fast_reg) अणु
		अगर (ch->fr_pool)
			srp_destroy_fr_pool(ch->fr_pool);
	पूर्ण

	srp_destroy_qp(ch);
	ib_मुक्त_cq(ch->send_cq);
	ib_मुक्त_cq(ch->recv_cq);

	/*
	 * Aव्योम that the SCSI error handler tries to use this channel after
	 * it has been मुक्तd. The SCSI error handler can namely जारी
	 * trying to perक्रमm recovery actions after scsi_हटाओ_host()
	 * वापसed.
	 */
	ch->target = शून्य;

	ch->qp = शून्य;
	ch->send_cq = ch->recv_cq = शून्य;

	अगर (ch->rx_ring) अणु
		क्रम (i = 0; i < target->queue_size; ++i)
			srp_मुक्त_iu(target->srp_host, ch->rx_ring[i]);
		kमुक्त(ch->rx_ring);
		ch->rx_ring = शून्य;
	पूर्ण
	अगर (ch->tx_ring) अणु
		क्रम (i = 0; i < target->queue_size; ++i)
			srp_मुक्त_iu(target->srp_host, ch->tx_ring[i]);
		kमुक्त(ch->tx_ring);
		ch->tx_ring = शून्य;
	पूर्ण
पूर्ण

अटल व्योम srp_path_rec_completion(पूर्णांक status,
				    काष्ठा sa_path_rec *pathrec,
				    व्योम *ch_ptr)
अणु
	काष्ठा srp_rdma_ch *ch = ch_ptr;
	काष्ठा srp_target_port *target = ch->target;

	ch->status = status;
	अगर (status)
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
			     PFX "Got failed path rec status %d\n", status);
	अन्यथा
		ch->ib_cm.path = *pathrec;
	complete(&ch->करोne);
पूर्ण

अटल पूर्णांक srp_ib_lookup_path(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	पूर्णांक ret;

	ch->ib_cm.path.numb_path = 1;

	init_completion(&ch->करोne);

	ch->ib_cm.path_query_id = ib_sa_path_rec_get(&srp_sa_client,
					       target->srp_host->srp_dev->dev,
					       target->srp_host->port,
					       &ch->ib_cm.path,
					       IB_SA_PATH_REC_SERVICE_ID |
					       IB_SA_PATH_REC_DGID	 |
					       IB_SA_PATH_REC_SGID	 |
					       IB_SA_PATH_REC_NUMB_PATH	 |
					       IB_SA_PATH_REC_PKEY,
					       SRP_PATH_REC_TIMEOUT_MS,
					       GFP_KERNEL,
					       srp_path_rec_completion,
					       ch, &ch->ib_cm.path_query);
	अगर (ch->ib_cm.path_query_id < 0)
		वापस ch->ib_cm.path_query_id;

	ret = रुको_क्रम_completion_पूर्णांकerruptible(&ch->करोne);
	अगर (ret < 0)
		वापस ret;

	अगर (ch->status < 0)
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "Path record query failed: sgid %pI6, dgid %pI6, pkey %#04x, service_id %#16llx\n",
			     ch->ib_cm.path.sgid.raw, ch->ib_cm.path.dgid.raw,
			     be16_to_cpu(target->ib_cm.pkey),
			     be64_to_cpu(target->ib_cm.service_id));

	वापस ch->status;
पूर्ण

अटल पूर्णांक srp_rdma_lookup_path(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	पूर्णांक ret;

	init_completion(&ch->करोne);

	ret = rdma_resolve_route(ch->rdma_cm.cm_id, SRP_PATH_REC_TIMEOUT_MS);
	अगर (ret)
		वापस ret;

	रुको_क्रम_completion_पूर्णांकerruptible(&ch->करोne);

	अगर (ch->status != 0)
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "Path resolution failed\n");

	वापस ch->status;
पूर्ण

अटल पूर्णांक srp_lookup_path(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;

	वापस target->using_rdma_cm ? srp_rdma_lookup_path(ch) :
		srp_ib_lookup_path(ch);
पूर्ण

अटल u8 srp_get_subnet_समयout(काष्ठा srp_host *host)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक ret;
	u8 subnet_समयout = 18;

	ret = ib_query_port(host->srp_dev->dev, host->port, &attr);
	अगर (ret == 0)
		subnet_समयout = attr.subnet_समयout;

	अगर (unlikely(subnet_समयout < 15))
		pr_warn("%s: subnet timeout %d may cause SRP login to fail.\n",
			dev_name(&host->srp_dev->dev->dev), subnet_समयout);

	वापस subnet_समयout;
पूर्ण

अटल पूर्णांक srp_send_req(काष्ठा srp_rdma_ch *ch, uपूर्णांक32_t max_iu_len,
			bool multich)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा अणु
		काष्ठा rdma_conn_param	  rdma_param;
		काष्ठा srp_login_req_rdma rdma_req;
		काष्ठा ib_cm_req_param	  ib_param;
		काष्ठा srp_login_req	  ib_req;
	पूर्ण *req = शून्य;
	अक्षर *ipi, *tpi;
	पूर्णांक status;

	req = kzalloc(माप *req, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	req->ib_param.flow_control = 1;
	req->ib_param.retry_count = target->tl_retry_count;

	/*
	 * Pick some arbitrary शेषs here; we could make these
	 * module parameters अगर anyone cared about setting them.
	 */
	req->ib_param.responder_resources = 4;
	req->ib_param.rnr_retry_count = 7;
	req->ib_param.max_cm_retries = 15;

	req->ib_req.opcode = SRP_LOGIN_REQ;
	req->ib_req.tag = 0;
	req->ib_req.req_it_iu_len = cpu_to_be32(max_iu_len);
	req->ib_req.req_buf_fmt	= cpu_to_be16(SRP_BUF_FORMAT_सूचीECT |
					      SRP_BUF_FORMAT_INसूचीECT);
	req->ib_req.req_flags = (multich ? SRP_MULTICHAN_MULTI :
				 SRP_MULTICHAN_SINGLE);
	अगर (srp_use_imm_data) अणु
		req->ib_req.req_flags |= SRP_IMMED_REQUESTED;
		req->ib_req.imm_data_offset = cpu_to_be16(SRP_IMM_DATA_OFFSET);
	पूर्ण

	अगर (target->using_rdma_cm) अणु
		req->rdma_param.flow_control = req->ib_param.flow_control;
		req->rdma_param.responder_resources =
			req->ib_param.responder_resources;
		req->rdma_param.initiator_depth = req->ib_param.initiator_depth;
		req->rdma_param.retry_count = req->ib_param.retry_count;
		req->rdma_param.rnr_retry_count = req->ib_param.rnr_retry_count;
		req->rdma_param.निजी_data = &req->rdma_req;
		req->rdma_param.निजी_data_len = माप(req->rdma_req);

		req->rdma_req.opcode = req->ib_req.opcode;
		req->rdma_req.tag = req->ib_req.tag;
		req->rdma_req.req_it_iu_len = req->ib_req.req_it_iu_len;
		req->rdma_req.req_buf_fmt = req->ib_req.req_buf_fmt;
		req->rdma_req.req_flags	= req->ib_req.req_flags;
		req->rdma_req.imm_data_offset = req->ib_req.imm_data_offset;

		ipi = req->rdma_req.initiator_port_id;
		tpi = req->rdma_req.target_port_id;
	पूर्ण अन्यथा अणु
		u8 subnet_समयout;

		subnet_समयout = srp_get_subnet_समयout(target->srp_host);

		req->ib_param.primary_path = &ch->ib_cm.path;
		req->ib_param.alternate_path = शून्य;
		req->ib_param.service_id = target->ib_cm.service_id;
		get_अक्रमom_bytes(&req->ib_param.starting_psn, 4);
		req->ib_param.starting_psn &= 0xffffff;
		req->ib_param.qp_num = ch->qp->qp_num;
		req->ib_param.qp_type = ch->qp->qp_type;
		req->ib_param.local_cm_response_समयout = subnet_समयout + 2;
		req->ib_param.remote_cm_response_समयout = subnet_समयout + 2;
		req->ib_param.निजी_data = &req->ib_req;
		req->ib_param.निजी_data_len = माप(req->ib_req);

		ipi = req->ib_req.initiator_port_id;
		tpi = req->ib_req.target_port_id;
	पूर्ण

	/*
	 * In the published SRP specअगरication (draft rev. 16a), the
	 * port identअगरier क्रमmat is 8 bytes of ID extension followed
	 * by 8 bytes of GUID.  Older drafts put the two halves in the
	 * opposite order, so that the GUID comes first.
	 *
	 * Tarमाला_लो conक्रमming to these obsolete drafts can be
	 * recognized by the I/O Class they report.
	 */
	अगर (target->io_class == SRP_REV10_IB_IO_CLASS) अणु
		स_नकल(ipi,     &target->sgid.global.पूर्णांकerface_id, 8);
		स_नकल(ipi + 8, &target->initiator_ext, 8);
		स_नकल(tpi,     &target->ioc_guid, 8);
		स_नकल(tpi + 8, &target->id_ext, 8);
	पूर्ण अन्यथा अणु
		स_नकल(ipi,     &target->initiator_ext, 8);
		स_नकल(ipi + 8, &target->sgid.global.पूर्णांकerface_id, 8);
		स_नकल(tpi,     &target->id_ext, 8);
		स_नकल(tpi + 8, &target->ioc_guid, 8);
	पूर्ण

	/*
	 * Topspin/Cisco SRP tarमाला_लो will reject our login unless we
	 * zero out the first 8 bytes of our initiator port ID and set
	 * the second 8 bytes to the local node GUID.
	 */
	अगर (srp_target_is_topspin(target)) अणु
		shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host,
			     PFX "Topspin/Cisco initiator port ID workaround "
			     "activated for target GUID %016llx\n",
			     be64_to_cpu(target->ioc_guid));
		स_रखो(ipi, 0, 8);
		स_नकल(ipi + 8, &target->srp_host->srp_dev->dev->node_guid, 8);
	पूर्ण

	अगर (target->using_rdma_cm)
		status = rdma_connect(ch->rdma_cm.cm_id, &req->rdma_param);
	अन्यथा
		status = ib_send_cm_req(ch->ib_cm.cm_id, &req->ib_param);

	kमुक्त(req);

	वापस status;
पूर्ण

अटल bool srp_queue_हटाओ_work(काष्ठा srp_target_port *target)
अणु
	bool changed = false;

	spin_lock_irq(&target->lock);
	अगर (target->state != SRP_TARGET_REMOVED) अणु
		target->state = SRP_TARGET_REMOVED;
		changed = true;
	पूर्ण
	spin_unlock_irq(&target->lock);

	अगर (changed)
		queue_work(srp_हटाओ_wq, &target->हटाओ_work);

	वापस changed;
पूर्ण

अटल व्योम srp_disconnect_target(काष्ठा srp_target_port *target)
अणु
	काष्ठा srp_rdma_ch *ch;
	पूर्णांक i, ret;

	/* XXX should send SRP_I_LOGOUT request */

	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		ch->connected = false;
		ret = 0;
		अगर (target->using_rdma_cm) अणु
			अगर (ch->rdma_cm.cm_id)
				rdma_disconnect(ch->rdma_cm.cm_id);
		पूर्ण अन्यथा अणु
			अगर (ch->ib_cm.cm_id)
				ret = ib_send_cm_dreq(ch->ib_cm.cm_id,
						      शून्य, 0);
		पूर्ण
		अगर (ret < 0) अणु
			shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host,
				     PFX "Sending CM DREQ failed\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम srp_मुक्त_req_data(काष्ठा srp_target_port *target,
			      काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_device *dev = target->srp_host->srp_dev;
	काष्ठा ib_device *ibdev = dev->dev;
	काष्ठा srp_request *req;
	पूर्णांक i;

	अगर (!ch->req_ring)
		वापस;

	क्रम (i = 0; i < target->req_ring_size; ++i) अणु
		req = &ch->req_ring[i];
		अगर (dev->use_fast_reg)
			kमुक्त(req->fr_list);
		अगर (req->indirect_dma_addr) अणु
			ib_dma_unmap_single(ibdev, req->indirect_dma_addr,
					    target->indirect_size,
					    DMA_TO_DEVICE);
		पूर्ण
		kमुक्त(req->indirect_desc);
	पूर्ण

	kमुक्त(ch->req_ring);
	ch->req_ring = शून्य;
पूर्ण

अटल पूर्णांक srp_alloc_req_data(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा srp_device *srp_dev = target->srp_host->srp_dev;
	काष्ठा ib_device *ibdev = srp_dev->dev;
	काष्ठा srp_request *req;
	व्योम *mr_list;
	dma_addr_t dma_addr;
	पूर्णांक i, ret = -ENOMEM;

	ch->req_ring = kसुस्मृति(target->req_ring_size, माप(*ch->req_ring),
			       GFP_KERNEL);
	अगर (!ch->req_ring)
		जाओ out;

	क्रम (i = 0; i < target->req_ring_size; ++i) अणु
		req = &ch->req_ring[i];
		mr_list = kदो_स्मृति_array(target->mr_per_cmd, माप(व्योम *),
					GFP_KERNEL);
		अगर (!mr_list)
			जाओ out;
		अगर (srp_dev->use_fast_reg)
			req->fr_list = mr_list;
		req->indirect_desc = kदो_स्मृति(target->indirect_size, GFP_KERNEL);
		अगर (!req->indirect_desc)
			जाओ out;

		dma_addr = ib_dma_map_single(ibdev, req->indirect_desc,
					     target->indirect_size,
					     DMA_TO_DEVICE);
		अगर (ib_dma_mapping_error(ibdev, dma_addr))
			जाओ out;

		req->indirect_dma_addr = dma_addr;
	पूर्ण
	ret = 0;

out:
	वापस ret;
पूर्ण

/**
 * srp_del_scsi_host_attr() - Remove attributes defined in the host ढाँचा.
 * @shost: SCSI host whose attributes to हटाओ from sysfs.
 *
 * Note: Any attributes defined in the host ढाँचा and that did not exist
 * beक्रमe invocation of this function will be ignored.
 */
अटल व्योम srp_del_scsi_host_attr(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा device_attribute **attr;

	क्रम (attr = shost->hostt->shost_attrs; attr && *attr; ++attr)
		device_हटाओ_file(&shost->shost_dev, *attr);
पूर्ण

अटल व्योम srp_हटाओ_target(काष्ठा srp_target_port *target)
अणु
	काष्ठा srp_rdma_ch *ch;
	पूर्णांक i;

	WARN_ON_ONCE(target->state != SRP_TARGET_REMOVED);

	srp_del_scsi_host_attr(target->scsi_host);
	srp_rport_get(target->rport);
	srp_हटाओ_host(target->scsi_host);
	scsi_हटाओ_host(target->scsi_host);
	srp_stop_rport_समयrs(target->rport);
	srp_disconnect_target(target);
	kobj_ns_drop(KOBJ_NS_TYPE_NET, target->net);
	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		srp_मुक्त_ch_ib(target, ch);
	पूर्ण
	cancel_work_sync(&target->tl_err_work);
	srp_rport_put(target->rport);
	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		srp_मुक्त_req_data(target, ch);
	पूर्ण
	kमुक्त(target->ch);
	target->ch = शून्य;

	spin_lock(&target->srp_host->target_lock);
	list_del(&target->list);
	spin_unlock(&target->srp_host->target_lock);

	scsi_host_put(target->scsi_host);
पूर्ण

अटल व्योम srp_हटाओ_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा srp_target_port *target =
		container_of(work, काष्ठा srp_target_port, हटाओ_work);

	WARN_ON_ONCE(target->state != SRP_TARGET_REMOVED);

	srp_हटाओ_target(target);
पूर्ण

अटल व्योम srp_rport_delete(काष्ठा srp_rport *rport)
अणु
	काष्ठा srp_target_port *target = rport->lld_data;

	srp_queue_हटाओ_work(target);
पूर्ण

/**
 * srp_connected_ch() - number of connected channels
 * @target: SRP target port.
 */
अटल पूर्णांक srp_connected_ch(काष्ठा srp_target_port *target)
अणु
	पूर्णांक i, c = 0;

	क्रम (i = 0; i < target->ch_count; i++)
		c += target->ch[i].connected;

	वापस c;
पूर्ण

अटल पूर्णांक srp_connect_ch(काष्ठा srp_rdma_ch *ch, uपूर्णांक32_t max_iu_len,
			  bool multich)
अणु
	काष्ठा srp_target_port *target = ch->target;
	पूर्णांक ret;

	WARN_ON_ONCE(!multich && srp_connected_ch(target) > 0);

	ret = srp_lookup_path(ch);
	अगर (ret)
		जाओ out;

	जबतक (1) अणु
		init_completion(&ch->करोne);
		ret = srp_send_req(ch, max_iu_len, multich);
		अगर (ret)
			जाओ out;
		ret = रुको_क्रम_completion_पूर्णांकerruptible(&ch->करोne);
		अगर (ret < 0)
			जाओ out;

		/*
		 * The CM event handling code will set status to
		 * SRP_PORT_REसूचीECT अगर we get a port redirect REJ
		 * back, or SRP_DLID_REसूचीECT अगर we get a lid/qp
		 * redirect REJ back.
		 */
		ret = ch->status;
		चयन (ret) अणु
		हाल 0:
			ch->connected = true;
			जाओ out;

		हाल SRP_PORT_REसूचीECT:
			ret = srp_lookup_path(ch);
			अगर (ret)
				जाओ out;
			अवरोध;

		हाल SRP_DLID_REसूचीECT:
			अवरोध;

		हाल SRP_STALE_CONN:
			shost_prपूर्णांकk(KERN_ERR, target->scsi_host, PFX
				     "giving up on stale connection\n");
			ret = -ECONNRESET;
			जाओ out;

		शेष:
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret <= 0 ? ret : -ENODEV;
पूर्ण

अटल व्योम srp_inv_rkey_err_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	srp_handle_qp_err(cq, wc, "INV RKEY");
पूर्ण

अटल पूर्णांक srp_inv_rkey(काष्ठा srp_request *req, काष्ठा srp_rdma_ch *ch,
		u32 rkey)
अणु
	काष्ठा ib_send_wr wr = अणु
		.opcode		    = IB_WR_LOCAL_INV,
		.next		    = शून्य,
		.num_sge	    = 0,
		.send_flags	    = 0,
		.ex.invalidate_rkey = rkey,
	पूर्ण;

	wr.wr_cqe = &req->reg_cqe;
	req->reg_cqe.करोne = srp_inv_rkey_err_करोne;
	वापस ib_post_send(ch->qp, &wr, शून्य);
पूर्ण

अटल व्योम srp_unmap_data(काष्ठा scsi_cmnd *scmnd,
			   काष्ठा srp_rdma_ch *ch,
			   काष्ठा srp_request *req)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा srp_device *dev = target->srp_host->srp_dev;
	काष्ठा ib_device *ibdev = dev->dev;
	पूर्णांक i, res;

	अगर (!scsi_sglist(scmnd) ||
	    (scmnd->sc_data_direction != DMA_TO_DEVICE &&
	     scmnd->sc_data_direction != DMA_FROM_DEVICE))
		वापस;

	अगर (dev->use_fast_reg) अणु
		काष्ठा srp_fr_desc **pfr;

		क्रम (i = req->nmdesc, pfr = req->fr_list; i > 0; i--, pfr++) अणु
			res = srp_inv_rkey(req, ch, (*pfr)->mr->rkey);
			अगर (res < 0) अणु
				shost_prपूर्णांकk(KERN_ERR, target->scsi_host, PFX
				  "Queueing INV WR for rkey %#x failed (%d)\n",
				  (*pfr)->mr->rkey, res);
				queue_work(प्रणाली_दीर्घ_wq,
					   &target->tl_err_work);
			पूर्ण
		पूर्ण
		अगर (req->nmdesc)
			srp_fr_pool_put(ch->fr_pool, req->fr_list,
					req->nmdesc);
	पूर्ण

	ib_dma_unmap_sg(ibdev, scsi_sglist(scmnd), scsi_sg_count(scmnd),
			scmnd->sc_data_direction);
पूर्ण

/**
 * srp_claim_req - Take ownership of the scmnd associated with a request.
 * @ch: SRP RDMA channel.
 * @req: SRP request.
 * @sdev: If not शून्य, only take ownership क्रम this SCSI device.
 * @scmnd: If शून्य, take ownership of @req->scmnd. If not शून्य, only take
 *         ownership of @req->scmnd अगर it equals @scmnd.
 *
 * Return value:
 * Either शून्य or a poपूर्णांकer to the SCSI command the caller became owner of.
 */
अटल काष्ठा scsi_cmnd *srp_claim_req(काष्ठा srp_rdma_ch *ch,
				       काष्ठा srp_request *req,
				       काष्ठा scsi_device *sdev,
				       काष्ठा scsi_cmnd *scmnd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ch->lock, flags);
	अगर (req->scmnd &&
	    (!sdev || req->scmnd->device == sdev) &&
	    (!scmnd || req->scmnd == scmnd)) अणु
		scmnd = req->scmnd;
		req->scmnd = शून्य;
	पूर्ण अन्यथा अणु
		scmnd = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&ch->lock, flags);

	वापस scmnd;
पूर्ण

/**
 * srp_मुक्त_req() - Unmap data and adjust ch->req_lim.
 * @ch:     SRP RDMA channel.
 * @req:    Request to be मुक्तd.
 * @scmnd:  SCSI command associated with @req.
 * @req_lim_delta: Amount to be added to @target->req_lim.
 */
अटल व्योम srp_मुक्त_req(काष्ठा srp_rdma_ch *ch, काष्ठा srp_request *req,
			 काष्ठा scsi_cmnd *scmnd, s32 req_lim_delta)
अणु
	अचिन्हित दीर्घ flags;

	srp_unmap_data(scmnd, ch, req);

	spin_lock_irqsave(&ch->lock, flags);
	ch->req_lim += req_lim_delta;
	spin_unlock_irqrestore(&ch->lock, flags);
पूर्ण

अटल व्योम srp_finish_req(काष्ठा srp_rdma_ch *ch, काष्ठा srp_request *req,
			   काष्ठा scsi_device *sdev, पूर्णांक result)
अणु
	काष्ठा scsi_cmnd *scmnd = srp_claim_req(ch, req, sdev, शून्य);

	अगर (scmnd) अणु
		srp_मुक्त_req(ch, req, scmnd, 0);
		scmnd->result = result;
		scmnd->scsi_करोne(scmnd);
	पूर्ण
पूर्ण

अटल व्योम srp_terminate_io(काष्ठा srp_rport *rport)
अणु
	काष्ठा srp_target_port *target = rport->lld_data;
	काष्ठा srp_rdma_ch *ch;
	पूर्णांक i, j;

	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];

		क्रम (j = 0; j < target->req_ring_size; ++j) अणु
			काष्ठा srp_request *req = &ch->req_ring[j];

			srp_finish_req(ch, req, शून्य,
				       DID_TRANSPORT_FAILFAST << 16);
		पूर्ण
	पूर्ण
पूर्ण

/* Calculate maximum initiator to target inक्रमmation unit length. */
अटल uपूर्णांक32_t srp_max_it_iu_len(पूर्णांक cmd_sg_cnt, bool use_imm_data,
				  uपूर्णांक32_t max_it_iu_size)
अणु
	uपूर्णांक32_t max_iu_len = माप(काष्ठा srp_cmd) + SRP_MAX_ADD_CDB_LEN +
		माप(काष्ठा srp_indirect_buf) +
		cmd_sg_cnt * माप(काष्ठा srp_direct_buf);

	अगर (use_imm_data)
		max_iu_len = max(max_iu_len, SRP_IMM_DATA_OFFSET +
				 srp_max_imm_data);

	अगर (max_it_iu_size)
		max_iu_len = min(max_iu_len, max_it_iu_size);

	pr_debug("max_iu_len = %d\n", max_iu_len);

	वापस max_iu_len;
पूर्ण

/*
 * It is up to the caller to ensure that srp_rport_reconnect() calls are
 * serialized and that no concurrent srp_queuecommand(), srp_पात(),
 * srp_reset_device() or srp_reset_host() calls will occur जबतक this function
 * is in progress. One way to realize that is not to call this function
 * directly but to call srp_reconnect_rport() instead since that last function
 * serializes calls of this function via rport->mutex and also blocks
 * srp_queuecommand() calls beक्रमe invoking this function.
 */
अटल पूर्णांक srp_rport_reconnect(काष्ठा srp_rport *rport)
अणु
	काष्ठा srp_target_port *target = rport->lld_data;
	काष्ठा srp_rdma_ch *ch;
	uपूर्णांक32_t max_iu_len = srp_max_it_iu_len(target->cmd_sg_cnt,
						srp_use_imm_data,
						target->max_it_iu_size);
	पूर्णांक i, j, ret = 0;
	bool multich = false;

	srp_disconnect_target(target);

	अगर (target->state == SRP_TARGET_SCANNING)
		वापस -ENODEV;

	/*
	 * Now get a new local CM ID so that we aव्योम confusing the target in
	 * हाल things are really fouled up. Doing so also ensures that all CM
	 * callbacks will have finished beक्रमe a new QP is allocated.
	 */
	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		ret += srp_new_cm_id(ch);
	पूर्ण
	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		क्रम (j = 0; j < target->req_ring_size; ++j) अणु
			काष्ठा srp_request *req = &ch->req_ring[j];

			srp_finish_req(ch, req, शून्य, DID_RESET << 16);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		/*
		 * Whether or not creating a new CM ID succeeded, create a new
		 * QP. This guarantees that all completion callback function
		 * invocations have finished beक्रमe request resetting starts.
		 */
		ret += srp_create_ch_ib(ch);

		INIT_LIST_HEAD(&ch->मुक्त_tx);
		क्रम (j = 0; j < target->queue_size; ++j)
			list_add(&ch->tx_ring[j]->list, &ch->मुक्त_tx);
	पूर्ण

	target->qp_in_error = false;

	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		अगर (ret)
			अवरोध;
		ret = srp_connect_ch(ch, max_iu_len, multich);
		multich = true;
	पूर्ण

	अगर (ret == 0)
		shost_prपूर्णांकk(KERN_INFO, target->scsi_host,
			     PFX "reconnect succeeded\n");

	वापस ret;
पूर्ण

अटल व्योम srp_map_desc(काष्ठा srp_map_state *state, dma_addr_t dma_addr,
			 अचिन्हित पूर्णांक dma_len, u32 rkey)
अणु
	काष्ठा srp_direct_buf *desc = state->desc;

	WARN_ON_ONCE(!dma_len);

	desc->va = cpu_to_be64(dma_addr);
	desc->key = cpu_to_be32(rkey);
	desc->len = cpu_to_be32(dma_len);

	state->total_len += dma_len;
	state->desc++;
	state->ndesc++;
पूर्ण

अटल व्योम srp_reg_mr_err_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	srp_handle_qp_err(cq, wc, "FAST REG");
पूर्ण

/*
 * Map up to sg_nents elements of state->sg where *sg_offset_p is the offset
 * where to start in the first element. If sg_offset_p != शून्य then
 * *sg_offset_p is updated to the offset in state->sg[retval] of the first
 * byte that has not yet been mapped.
 */
अटल पूर्णांक srp_map_finish_fr(काष्ठा srp_map_state *state,
			     काष्ठा srp_request *req,
			     काष्ठा srp_rdma_ch *ch, पूर्णांक sg_nents,
			     अचिन्हित पूर्णांक *sg_offset_p)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा srp_device *dev = target->srp_host->srp_dev;
	काष्ठा ib_reg_wr wr;
	काष्ठा srp_fr_desc *desc;
	u32 rkey;
	पूर्णांक n, err;

	अगर (state->fr.next >= state->fr.end) अणु
		shost_prपूर्णांकk(KERN_ERR, ch->target->scsi_host,
			     PFX "Out of MRs (mr_per_cmd = %d)\n",
			     ch->target->mr_per_cmd);
		वापस -ENOMEM;
	पूर्ण

	WARN_ON_ONCE(!dev->use_fast_reg);

	अगर (sg_nents == 1 && target->global_rkey) अणु
		अचिन्हित पूर्णांक sg_offset = sg_offset_p ? *sg_offset_p : 0;

		srp_map_desc(state, sg_dma_address(state->sg) + sg_offset,
			     sg_dma_len(state->sg) - sg_offset,
			     target->global_rkey);
		अगर (sg_offset_p)
			*sg_offset_p = 0;
		वापस 1;
	पूर्ण

	desc = srp_fr_pool_get(ch->fr_pool);
	अगर (!desc)
		वापस -ENOMEM;

	rkey = ib_inc_rkey(desc->mr->rkey);
	ib_update_fast_reg_key(desc->mr, rkey);

	n = ib_map_mr_sg(desc->mr, state->sg, sg_nents, sg_offset_p,
			 dev->mr_page_size);
	अगर (unlikely(n < 0)) अणु
		srp_fr_pool_put(ch->fr_pool, &desc, 1);
		pr_debug("%s: ib_map_mr_sg(%d, %d) returned %d.\n",
			 dev_name(&req->scmnd->device->sdev_gendev), sg_nents,
			 sg_offset_p ? *sg_offset_p : -1, n);
		वापस n;
	पूर्ण

	WARN_ON_ONCE(desc->mr->length == 0);

	req->reg_cqe.करोne = srp_reg_mr_err_करोne;

	wr.wr.next = शून्य;
	wr.wr.opcode = IB_WR_REG_MR;
	wr.wr.wr_cqe = &req->reg_cqe;
	wr.wr.num_sge = 0;
	wr.wr.send_flags = 0;
	wr.mr = desc->mr;
	wr.key = desc->mr->rkey;
	wr.access = (IB_ACCESS_LOCAL_WRITE |
		     IB_ACCESS_REMOTE_READ |
		     IB_ACCESS_REMOTE_WRITE);

	*state->fr.next++ = desc;
	state->nmdesc++;

	srp_map_desc(state, desc->mr->iova,
		     desc->mr->length, desc->mr->rkey);

	err = ib_post_send(ch->qp, &wr.wr, शून्य);
	अगर (unlikely(err)) अणु
		WARN_ON_ONCE(err == -ENOMEM);
		वापस err;
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक srp_map_sg_fr(काष्ठा srp_map_state *state, काष्ठा srp_rdma_ch *ch,
			 काष्ठा srp_request *req, काष्ठा scatterlist *scat,
			 पूर्णांक count)
अणु
	अचिन्हित पूर्णांक sg_offset = 0;

	state->fr.next = req->fr_list;
	state->fr.end = req->fr_list + ch->target->mr_per_cmd;
	state->sg = scat;

	अगर (count == 0)
		वापस 0;

	जबतक (count) अणु
		पूर्णांक i, n;

		n = srp_map_finish_fr(state, req, ch, count, &sg_offset);
		अगर (unlikely(n < 0))
			वापस n;

		count -= n;
		क्रम (i = 0; i < n; i++)
			state->sg = sg_next(state->sg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक srp_map_sg_dma(काष्ठा srp_map_state *state, काष्ठा srp_rdma_ch *ch,
			  काष्ठा srp_request *req, काष्ठा scatterlist *scat,
			  पूर्णांक count)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(scat, sg, count, i) अणु
		srp_map_desc(state, sg_dma_address(sg), sg_dma_len(sg),
			     target->global_rkey);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Register the indirect data buffer descriptor with the HCA.
 *
 * Note: since the indirect data buffer descriptor has been allocated with
 * kदो_स्मृति() it is guaranteed that this buffer is a physically contiguous
 * memory buffer.
 */
अटल पूर्णांक srp_map_idb(काष्ठा srp_rdma_ch *ch, काष्ठा srp_request *req,
		       व्योम **next_mr, व्योम **end_mr, u32 idb_len,
		       __be32 *idb_rkey)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा srp_device *dev = target->srp_host->srp_dev;
	काष्ठा srp_map_state state;
	काष्ठा srp_direct_buf idb_desc;
	काष्ठा scatterlist idb_sg[1];
	पूर्णांक ret;

	स_रखो(&state, 0, माप(state));
	स_रखो(&idb_desc, 0, माप(idb_desc));
	state.gen.next = next_mr;
	state.gen.end = end_mr;
	state.desc = &idb_desc;
	state.base_dma_addr = req->indirect_dma_addr;
	state.dma_len = idb_len;

	अगर (dev->use_fast_reg) अणु
		state.sg = idb_sg;
		sg_init_one(idb_sg, req->indirect_desc, idb_len);
		idb_sg->dma_address = req->indirect_dma_addr; /* hack! */
#अगर_घोषित CONFIG_NEED_SG_DMA_LENGTH
		idb_sg->dma_length = idb_sg->length;	      /* hack^2 */
#पूर्ण_अगर
		ret = srp_map_finish_fr(&state, req, ch, 1, शून्य);
		अगर (ret < 0)
			वापस ret;
		WARN_ON_ONCE(ret < 1);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	*idb_rkey = idb_desc.key;

	वापस 0;
पूर्ण

अटल व्योम srp_check_mapping(काष्ठा srp_map_state *state,
			      काष्ठा srp_rdma_ch *ch, काष्ठा srp_request *req,
			      काष्ठा scatterlist *scat, पूर्णांक count)
अणु
	काष्ठा srp_device *dev = ch->target->srp_host->srp_dev;
	काष्ठा srp_fr_desc **pfr;
	u64 desc_len = 0, mr_len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < state->ndesc; i++)
		desc_len += be32_to_cpu(req->indirect_desc[i].len);
	अगर (dev->use_fast_reg)
		क्रम (i = 0, pfr = req->fr_list; i < state->nmdesc; i++, pfr++)
			mr_len += (*pfr)->mr->length;
	अगर (desc_len != scsi_bufflen(req->scmnd) ||
	    mr_len > scsi_bufflen(req->scmnd))
		pr_err("Inconsistent: scsi len %d <> desc len %lld <> mr len %lld; ndesc %d; nmdesc = %d\n",
		       scsi_bufflen(req->scmnd), desc_len, mr_len,
		       state->ndesc, state->nmdesc);
पूर्ण

/**
 * srp_map_data() - map SCSI data buffer onto an SRP request
 * @scmnd: SCSI command to map
 * @ch: SRP RDMA channel
 * @req: SRP request
 *
 * Returns the length in bytes of the SRP_CMD IU or a negative value अगर
 * mapping failed. The size of any immediate data is not included in the
 * वापस value.
 */
अटल पूर्णांक srp_map_data(काष्ठा scsi_cmnd *scmnd, काष्ठा srp_rdma_ch *ch,
			काष्ठा srp_request *req)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा scatterlist *scat, *sg;
	काष्ठा srp_cmd *cmd = req->cmd->buf;
	पूर्णांक i, len, nents, count, ret;
	काष्ठा srp_device *dev;
	काष्ठा ib_device *ibdev;
	काष्ठा srp_map_state state;
	काष्ठा srp_indirect_buf *indirect_hdr;
	u64 data_len;
	u32 idb_len, table_len;
	__be32 idb_rkey;
	u8 fmt;

	req->cmd->num_sge = 1;

	अगर (!scsi_sglist(scmnd) || scmnd->sc_data_direction == DMA_NONE)
		वापस माप(काष्ठा srp_cmd) + cmd->add_cdb_len;

	अगर (scmnd->sc_data_direction != DMA_FROM_DEVICE &&
	    scmnd->sc_data_direction != DMA_TO_DEVICE) अणु
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "Unhandled data direction %d\n",
			     scmnd->sc_data_direction);
		वापस -EINVAL;
	पूर्ण

	nents = scsi_sg_count(scmnd);
	scat  = scsi_sglist(scmnd);
	data_len = scsi_bufflen(scmnd);

	dev = target->srp_host->srp_dev;
	ibdev = dev->dev;

	count = ib_dma_map_sg(ibdev, scat, nents, scmnd->sc_data_direction);
	अगर (unlikely(count == 0))
		वापस -EIO;

	अगर (ch->use_imm_data &&
	    count <= ch->max_imm_sge &&
	    SRP_IMM_DATA_OFFSET + data_len <= ch->max_it_iu_len &&
	    scmnd->sc_data_direction == DMA_TO_DEVICE) अणु
		काष्ठा srp_imm_buf *buf;
		काष्ठा ib_sge *sge = &req->cmd->sge[1];

		fmt = SRP_DATA_DESC_IMM;
		len = SRP_IMM_DATA_OFFSET;
		req->nmdesc = 0;
		buf = (व्योम *)cmd->add_data + cmd->add_cdb_len;
		buf->len = cpu_to_be32(data_len);
		WARN_ON_ONCE((व्योम *)(buf + 1) > (व्योम *)cmd + len);
		क्रम_each_sg(scat, sg, count, i) अणु
			sge[i].addr   = sg_dma_address(sg);
			sge[i].length = sg_dma_len(sg);
			sge[i].lkey   = target->lkey;
		पूर्ण
		req->cmd->num_sge += count;
		जाओ map_complete;
	पूर्ण

	fmt = SRP_DATA_DESC_सूचीECT;
	len = माप(काष्ठा srp_cmd) + cmd->add_cdb_len +
		माप(काष्ठा srp_direct_buf);

	अगर (count == 1 && target->global_rkey) अणु
		/*
		 * The midlayer only generated a single gather/scatter
		 * entry, or DMA mapping coalesced everything to a
		 * single entry.  So a direct descriptor aदीर्घ with
		 * the DMA MR suffices.
		 */
		काष्ठा srp_direct_buf *buf;

		buf = (व्योम *)cmd->add_data + cmd->add_cdb_len;
		buf->va  = cpu_to_be64(sg_dma_address(scat));
		buf->key = cpu_to_be32(target->global_rkey);
		buf->len = cpu_to_be32(sg_dma_len(scat));

		req->nmdesc = 0;
		जाओ map_complete;
	पूर्ण

	/*
	 * We have more than one scatter/gather entry, so build our indirect
	 * descriptor table, trying to merge as many entries as we can.
	 */
	indirect_hdr = (व्योम *)cmd->add_data + cmd->add_cdb_len;

	ib_dma_sync_single_क्रम_cpu(ibdev, req->indirect_dma_addr,
				   target->indirect_size, DMA_TO_DEVICE);

	स_रखो(&state, 0, माप(state));
	state.desc = req->indirect_desc;
	अगर (dev->use_fast_reg)
		ret = srp_map_sg_fr(&state, ch, req, scat, count);
	अन्यथा
		ret = srp_map_sg_dma(&state, ch, req, scat, count);
	req->nmdesc = state.nmdesc;
	अगर (ret < 0)
		जाओ unmap;

	अणु
		DEFINE_DYNAMIC_DEBUG_METADATA(ddm,
			"Memory mapping consistency check");
		अगर (DYNAMIC_DEBUG_BRANCH(ddm))
			srp_check_mapping(&state, ch, req, scat, count);
	पूर्ण

	/* We've mapped the request, now pull as much of the indirect
	 * descriptor table as we can पूर्णांकo the command buffer. If this
	 * target is not using an बाह्यal indirect table, we are
	 * guaranteed to fit पूर्णांकo the command, as the SCSI layer won't
	 * give us more S/G entries than we allow.
	 */
	अगर (state.ndesc == 1) अणु
		/*
		 * Memory registration collapsed the sg-list पूर्णांकo one entry,
		 * so use a direct descriptor.
		 */
		काष्ठा srp_direct_buf *buf;

		buf = (व्योम *)cmd->add_data + cmd->add_cdb_len;
		*buf = req->indirect_desc[0];
		जाओ map_complete;
	पूर्ण

	अगर (unlikely(target->cmd_sg_cnt < state.ndesc &&
						!target->allow_ext_sg)) अणु
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
			     "Could not fit S/G list into SRP_CMD\n");
		ret = -EIO;
		जाओ unmap;
	पूर्ण

	count = min(state.ndesc, target->cmd_sg_cnt);
	table_len = state.ndesc * माप (काष्ठा srp_direct_buf);
	idb_len = माप(काष्ठा srp_indirect_buf) + table_len;

	fmt = SRP_DATA_DESC_INसूचीECT;
	len = माप(काष्ठा srp_cmd) + cmd->add_cdb_len +
		माप(काष्ठा srp_indirect_buf);
	len += count * माप (काष्ठा srp_direct_buf);

	स_नकल(indirect_hdr->desc_list, req->indirect_desc,
	       count * माप (काष्ठा srp_direct_buf));

	अगर (!target->global_rkey) अणु
		ret = srp_map_idb(ch, req, state.gen.next, state.gen.end,
				  idb_len, &idb_rkey);
		अगर (ret < 0)
			जाओ unmap;
		req->nmdesc++;
	पूर्ण अन्यथा अणु
		idb_rkey = cpu_to_be32(target->global_rkey);
	पूर्ण

	indirect_hdr->table_desc.va = cpu_to_be64(req->indirect_dma_addr);
	indirect_hdr->table_desc.key = idb_rkey;
	indirect_hdr->table_desc.len = cpu_to_be32(table_len);
	indirect_hdr->len = cpu_to_be32(state.total_len);

	अगर (scmnd->sc_data_direction == DMA_TO_DEVICE)
		cmd->data_out_desc_cnt = count;
	अन्यथा
		cmd->data_in_desc_cnt = count;

	ib_dma_sync_single_क्रम_device(ibdev, req->indirect_dma_addr, table_len,
				      DMA_TO_DEVICE);

map_complete:
	अगर (scmnd->sc_data_direction == DMA_TO_DEVICE)
		cmd->buf_fmt = fmt << 4;
	अन्यथा
		cmd->buf_fmt = fmt;

	वापस len;

unmap:
	srp_unmap_data(scmnd, ch, req);
	अगर (ret == -ENOMEM && req->nmdesc >= target->mr_pool_size)
		ret = -E2BIG;
	वापस ret;
पूर्ण

/*
 * Return an IU and possible credit to the मुक्त pool
 */
अटल व्योम srp_put_tx_iu(काष्ठा srp_rdma_ch *ch, काष्ठा srp_iu *iu,
			  क्रमागत srp_iu_type iu_type)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ch->lock, flags);
	list_add(&iu->list, &ch->मुक्त_tx);
	अगर (iu_type != SRP_IU_RSP)
		++ch->req_lim;
	spin_unlock_irqrestore(&ch->lock, flags);
पूर्ण

/*
 * Must be called with ch->lock held to protect req_lim and मुक्त_tx.
 * If IU is not sent, it must be वापसed using srp_put_tx_iu().
 *
 * Note:
 * An upper limit क्रम the number of allocated inक्रमmation units क्रम each
 * request type is:
 * - SRP_IU_CMD: SRP_CMD_SQ_SIZE, since the SCSI mid-layer never queues
 *   more than Scsi_Host.can_queue requests.
 * - SRP_IU_TSK_MGMT: SRP_TSK_MGMT_SQ_SIZE.
 * - SRP_IU_RSP: 1, since a conक्रमming SRP target never sends more than
 *   one unanswered SRP request to an initiator.
 */
अटल काष्ठा srp_iu *__srp_get_tx_iu(काष्ठा srp_rdma_ch *ch,
				      क्रमागत srp_iu_type iu_type)
अणु
	काष्ठा srp_target_port *target = ch->target;
	s32 rsv = (iu_type == SRP_IU_TSK_MGMT) ? 0 : SRP_TSK_MGMT_SQ_SIZE;
	काष्ठा srp_iu *iu;

	lockdep_निश्चित_held(&ch->lock);

	ib_process_cq_direct(ch->send_cq, -1);

	अगर (list_empty(&ch->मुक्त_tx))
		वापस शून्य;

	/* Initiator responses to target requests करो not consume credits */
	अगर (iu_type != SRP_IU_RSP) अणु
		अगर (ch->req_lim <= rsv) अणु
			++target->zero_req_lim;
			वापस शून्य;
		पूर्ण

		--ch->req_lim;
	पूर्ण

	iu = list_first_entry(&ch->मुक्त_tx, काष्ठा srp_iu, list);
	list_del(&iu->list);
	वापस iu;
पूर्ण

/*
 * Note: अगर this function is called from inside ib_drain_sq() then it will
 * be called without ch->lock being held. If ib_drain_sq() dequeues a WQE
 * with status IB_WC_SUCCESS then that's a bug.
 */
अटल व्योम srp_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा srp_iu *iu = container_of(wc->wr_cqe, काष्ठा srp_iu, cqe);
	काष्ठा srp_rdma_ch *ch = cq->cq_context;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		srp_handle_qp_err(cq, wc, "SEND");
		वापस;
	पूर्ण

	lockdep_निश्चित_held(&ch->lock);

	list_add(&iu->list, &ch->मुक्त_tx);
पूर्ण

/**
 * srp_post_send() - send an SRP inक्रमmation unit
 * @ch: RDMA channel over which to send the inक्रमmation unit.
 * @iu: Inक्रमmation unit to send.
 * @len: Length of the inक्रमmation unit excluding immediate data.
 */
अटल पूर्णांक srp_post_send(काष्ठा srp_rdma_ch *ch, काष्ठा srp_iu *iu, पूर्णांक len)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा ib_send_wr wr;

	अगर (WARN_ON_ONCE(iu->num_sge > SRP_MAX_SGE))
		वापस -EINVAL;

	iu->sge[0].addr   = iu->dma;
	iu->sge[0].length = len;
	iu->sge[0].lkey   = target->lkey;

	iu->cqe.करोne = srp_send_करोne;

	wr.next       = शून्य;
	wr.wr_cqe     = &iu->cqe;
	wr.sg_list    = &iu->sge[0];
	wr.num_sge    = iu->num_sge;
	wr.opcode     = IB_WR_SEND;
	wr.send_flags = IB_SEND_SIGNALED;

	वापस ib_post_send(ch->qp, &wr, शून्य);
पूर्ण

अटल पूर्णांक srp_post_recv(काष्ठा srp_rdma_ch *ch, काष्ठा srp_iu *iu)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा ib_recv_wr wr;
	काष्ठा ib_sge list;

	list.addr   = iu->dma;
	list.length = iu->size;
	list.lkey   = target->lkey;

	iu->cqe.करोne = srp_recv_करोne;

	wr.next     = शून्य;
	wr.wr_cqe   = &iu->cqe;
	wr.sg_list  = &list;
	wr.num_sge  = 1;

	वापस ib_post_recv(ch->qp, &wr, शून्य);
पूर्ण

अटल व्योम srp_process_rsp(काष्ठा srp_rdma_ch *ch, काष्ठा srp_rsp *rsp)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा srp_request *req;
	काष्ठा scsi_cmnd *scmnd;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(rsp->tag & SRP_TAG_TSK_MGMT)) अणु
		spin_lock_irqsave(&ch->lock, flags);
		ch->req_lim += be32_to_cpu(rsp->req_lim_delta);
		अगर (rsp->tag == ch->tsk_mgmt_tag) अणु
			ch->tsk_mgmt_status = -1;
			अगर (be32_to_cpu(rsp->resp_data_len) >= 4)
				ch->tsk_mgmt_status = rsp->data[3];
			complete(&ch->tsk_mgmt_करोne);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
				     "Received tsk mgmt response too late for tag %#llx\n",
				     rsp->tag);
		पूर्ण
		spin_unlock_irqrestore(&ch->lock, flags);
	पूर्ण अन्यथा अणु
		scmnd = scsi_host_find_tag(target->scsi_host, rsp->tag);
		अगर (scmnd && scmnd->host_scribble) अणु
			req = (व्योम *)scmnd->host_scribble;
			scmnd = srp_claim_req(ch, req, शून्य, scmnd);
		पूर्ण अन्यथा अणु
			scmnd = शून्य;
		पूर्ण
		अगर (!scmnd) अणु
			shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
				     "Null scmnd for RSP w/tag %#016llx received on ch %td / QP %#x\n",
				     rsp->tag, ch - target->ch, ch->qp->qp_num);

			spin_lock_irqsave(&ch->lock, flags);
			ch->req_lim += be32_to_cpu(rsp->req_lim_delta);
			spin_unlock_irqrestore(&ch->lock, flags);

			वापस;
		पूर्ण
		scmnd->result = rsp->status;

		अगर (rsp->flags & SRP_RSP_FLAG_SNSVALID) अणु
			स_नकल(scmnd->sense_buffer, rsp->data +
			       be32_to_cpu(rsp->resp_data_len),
			       min_t(पूर्णांक, be32_to_cpu(rsp->sense_data_len),
				     SCSI_SENSE_BUFFERSIZE));
		पूर्ण

		अगर (unlikely(rsp->flags & SRP_RSP_FLAG_DIUNDER))
			scsi_set_resid(scmnd, be32_to_cpu(rsp->data_in_res_cnt));
		अन्यथा अगर (unlikely(rsp->flags & SRP_RSP_FLAG_DIOVER))
			scsi_set_resid(scmnd, -be32_to_cpu(rsp->data_in_res_cnt));
		अन्यथा अगर (unlikely(rsp->flags & SRP_RSP_FLAG_DOUNDER))
			scsi_set_resid(scmnd, be32_to_cpu(rsp->data_out_res_cnt));
		अन्यथा अगर (unlikely(rsp->flags & SRP_RSP_FLAG_DOOVER))
			scsi_set_resid(scmnd, -be32_to_cpu(rsp->data_out_res_cnt));

		srp_मुक्त_req(ch, req, scmnd,
			     be32_to_cpu(rsp->req_lim_delta));

		scmnd->host_scribble = शून्य;
		scmnd->scsi_करोne(scmnd);
	पूर्ण
पूर्ण

अटल पूर्णांक srp_response_common(काष्ठा srp_rdma_ch *ch, s32 req_delta,
			       व्योम *rsp, पूर्णांक len)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा ib_device *dev = target->srp_host->srp_dev->dev;
	अचिन्हित दीर्घ flags;
	काष्ठा srp_iu *iu;
	पूर्णांक err;

	spin_lock_irqsave(&ch->lock, flags);
	ch->req_lim += req_delta;
	iu = __srp_get_tx_iu(ch, SRP_IU_RSP);
	spin_unlock_irqrestore(&ch->lock, flags);

	अगर (!iu) अणु
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host, PFX
			     "no IU available to send response\n");
		वापस 1;
	पूर्ण

	iu->num_sge = 1;
	ib_dma_sync_single_क्रम_cpu(dev, iu->dma, len, DMA_TO_DEVICE);
	स_नकल(iu->buf, rsp, len);
	ib_dma_sync_single_क्रम_device(dev, iu->dma, len, DMA_TO_DEVICE);

	err = srp_post_send(ch, iu, len);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host, PFX
			     "unable to post response: %d\n", err);
		srp_put_tx_iu(ch, iu, SRP_IU_RSP);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम srp_process_cred_req(काष्ठा srp_rdma_ch *ch,
				 काष्ठा srp_cred_req *req)
अणु
	काष्ठा srp_cred_rsp rsp = अणु
		.opcode = SRP_CRED_RSP,
		.tag = req->tag,
	पूर्ण;
	s32 delta = be32_to_cpu(req->req_lim_delta);

	अगर (srp_response_common(ch, delta, &rsp, माप(rsp)))
		shost_prपूर्णांकk(KERN_ERR, ch->target->scsi_host, PFX
			     "problems processing SRP_CRED_REQ\n");
पूर्ण

अटल व्योम srp_process_aer_req(काष्ठा srp_rdma_ch *ch,
				काष्ठा srp_aer_req *req)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा srp_aer_rsp rsp = अणु
		.opcode = SRP_AER_RSP,
		.tag = req->tag,
	पूर्ण;
	s32 delta = be32_to_cpu(req->req_lim_delta);

	shost_prपूर्णांकk(KERN_ERR, target->scsi_host, PFX
		     "ignoring AER for LUN %llu\n", scsilun_to_पूर्णांक(&req->lun));

	अगर (srp_response_common(ch, delta, &rsp, माप(rsp)))
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host, PFX
			     "problems processing SRP_AER_REQ\n");
पूर्ण

अटल व्योम srp_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा srp_iu *iu = container_of(wc->wr_cqe, काष्ठा srp_iu, cqe);
	काष्ठा srp_rdma_ch *ch = cq->cq_context;
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा ib_device *dev = target->srp_host->srp_dev->dev;
	पूर्णांक res;
	u8 opcode;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		srp_handle_qp_err(cq, wc, "RECV");
		वापस;
	पूर्ण

	ib_dma_sync_single_क्रम_cpu(dev, iu->dma, ch->max_ti_iu_len,
				   DMA_FROM_DEVICE);

	opcode = *(u8 *) iu->buf;

	अगर (0) अणु
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
			     PFX "recv completion, opcode 0x%02x\n", opcode);
		prपूर्णांक_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 8, 1,
			       iu->buf, wc->byte_len, true);
	पूर्ण

	चयन (opcode) अणु
	हाल SRP_RSP:
		srp_process_rsp(ch, iu->buf);
		अवरोध;

	हाल SRP_CRED_REQ:
		srp_process_cred_req(ch, iu->buf);
		अवरोध;

	हाल SRP_AER_REQ:
		srp_process_aer_req(ch, iu->buf);
		अवरोध;

	हाल SRP_T_LOGOUT:
		/* XXX Handle target logout */
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "Got target logout request\n");
		अवरोध;

	शेष:
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "Unhandled SRP opcode 0x%02x\n", opcode);
		अवरोध;
	पूर्ण

	ib_dma_sync_single_क्रम_device(dev, iu->dma, ch->max_ti_iu_len,
				      DMA_FROM_DEVICE);

	res = srp_post_recv(ch, iu);
	अगर (res != 0)
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
			     PFX "Recv failed with error code %d\n", res);
पूर्ण

/**
 * srp_tl_err_work() - handle a transport layer error
 * @work: Work काष्ठाure embedded in an SRP target port.
 *
 * Note: This function may get invoked beक्रमe the rport has been created,
 * hence the target->rport test.
 */
अटल व्योम srp_tl_err_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा srp_target_port *target;

	target = container_of(work, काष्ठा srp_target_port, tl_err_work);
	अगर (target->rport)
		srp_start_tl_fail_समयrs(target->rport);
पूर्ण

अटल व्योम srp_handle_qp_err(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc,
		स्थिर अक्षर *opname)
अणु
	काष्ठा srp_rdma_ch *ch = cq->cq_context;
	काष्ठा srp_target_port *target = ch->target;

	अगर (ch->connected && !target->qp_in_error) अणु
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
			     PFX "failed %s status %s (%d) for CQE %p\n",
			     opname, ib_wc_status_msg(wc->status), wc->status,
			     wc->wr_cqe);
		queue_work(प्रणाली_दीर्घ_wq, &target->tl_err_work);
	पूर्ण
	target->qp_in_error = true;
पूर्ण

अटल पूर्णांक srp_queuecommand(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *scmnd)
अणु
	काष्ठा srp_target_port *target = host_to_target(shost);
	काष्ठा srp_rdma_ch *ch;
	काष्ठा srp_request *req;
	काष्ठा srp_iu *iu;
	काष्ठा srp_cmd *cmd;
	काष्ठा ib_device *dev;
	अचिन्हित दीर्घ flags;
	u32 tag;
	u16 idx;
	पूर्णांक len, ret;

	scmnd->result = srp_chkपढ़ोy(target->rport);
	अगर (unlikely(scmnd->result))
		जाओ err;

	WARN_ON_ONCE(scmnd->request->tag < 0);
	tag = blk_mq_unique_tag(scmnd->request);
	ch = &target->ch[blk_mq_unique_tag_to_hwq(tag)];
	idx = blk_mq_unique_tag_to_tag(tag);
	WARN_ONCE(idx >= target->req_ring_size, "%s: tag %#x: idx %d >= %d\n",
		  dev_name(&shost->shost_gendev), tag, idx,
		  target->req_ring_size);

	spin_lock_irqsave(&ch->lock, flags);
	iu = __srp_get_tx_iu(ch, SRP_IU_CMD);
	spin_unlock_irqrestore(&ch->lock, flags);

	अगर (!iu)
		जाओ err;

	req = &ch->req_ring[idx];
	dev = target->srp_host->srp_dev->dev;
	ib_dma_sync_single_क्रम_cpu(dev, iu->dma, ch->max_it_iu_len,
				   DMA_TO_DEVICE);

	scmnd->host_scribble = (व्योम *) req;

	cmd = iu->buf;
	स_रखो(cmd, 0, माप *cmd);

	cmd->opcode = SRP_CMD;
	पूर्णांक_to_scsilun(scmnd->device->lun, &cmd->lun);
	cmd->tag    = tag;
	स_नकल(cmd->cdb, scmnd->cmnd, scmnd->cmd_len);
	अगर (unlikely(scmnd->cmd_len > माप(cmd->cdb))) अणु
		cmd->add_cdb_len = round_up(scmnd->cmd_len - माप(cmd->cdb),
					    4);
		अगर (WARN_ON_ONCE(cmd->add_cdb_len > SRP_MAX_ADD_CDB_LEN))
			जाओ err_iu;
	पूर्ण

	req->scmnd    = scmnd;
	req->cmd      = iu;

	len = srp_map_data(scmnd, ch, req);
	अगर (len < 0) अणु
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
			     PFX "Failed to map data (%d)\n", len);
		/*
		 * If we ran out of memory descriptors (-ENOMEM) because an
		 * application is queuing many requests with more than
		 * max_pages_per_mr sg-list elements, tell the SCSI mid-layer
		 * to reduce queue depth temporarily.
		 */
		scmnd->result = len == -ENOMEM ?
			DID_OK << 16 | QUEUE_FULL << 1 : DID_ERROR << 16;
		जाओ err_iu;
	पूर्ण

	ib_dma_sync_single_क्रम_device(dev, iu->dma, ch->max_it_iu_len,
				      DMA_TO_DEVICE);

	अगर (srp_post_send(ch, iu, len)) अणु
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host, PFX "Send failed\n");
		scmnd->result = DID_ERROR << 16;
		जाओ err_unmap;
	पूर्ण

	वापस 0;

err_unmap:
	srp_unmap_data(scmnd, ch, req);

err_iu:
	srp_put_tx_iu(ch, iu, SRP_IU_CMD);

	/*
	 * Aव्योम that the loops that iterate over the request ring can
	 * encounter a dangling SCSI command poपूर्णांकer.
	 */
	req->scmnd = शून्य;

err:
	अगर (scmnd->result) अणु
		scmnd->scsi_करोne(scmnd);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Note: the resources allocated in this function are मुक्तd in
 * srp_मुक्त_ch_ib().
 */
अटल पूर्णांक srp_alloc_iu_bufs(काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	पूर्णांक i;

	ch->rx_ring = kसुस्मृति(target->queue_size, माप(*ch->rx_ring),
			      GFP_KERNEL);
	अगर (!ch->rx_ring)
		जाओ err_no_ring;
	ch->tx_ring = kसुस्मृति(target->queue_size, माप(*ch->tx_ring),
			      GFP_KERNEL);
	अगर (!ch->tx_ring)
		जाओ err_no_ring;

	क्रम (i = 0; i < target->queue_size; ++i) अणु
		ch->rx_ring[i] = srp_alloc_iu(target->srp_host,
					      ch->max_ti_iu_len,
					      GFP_KERNEL, DMA_FROM_DEVICE);
		अगर (!ch->rx_ring[i])
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < target->queue_size; ++i) अणु
		ch->tx_ring[i] = srp_alloc_iu(target->srp_host,
					      ch->max_it_iu_len,
					      GFP_KERNEL, DMA_TO_DEVICE);
		अगर (!ch->tx_ring[i])
			जाओ err;

		list_add(&ch->tx_ring[i]->list, &ch->मुक्त_tx);
	पूर्ण

	वापस 0;

err:
	क्रम (i = 0; i < target->queue_size; ++i) अणु
		srp_मुक्त_iu(target->srp_host, ch->rx_ring[i]);
		srp_मुक्त_iu(target->srp_host, ch->tx_ring[i]);
	पूर्ण


err_no_ring:
	kमुक्त(ch->tx_ring);
	ch->tx_ring = शून्य;
	kमुक्त(ch->rx_ring);
	ch->rx_ring = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल uपूर्णांक32_t srp_compute_rq_पंचांगo(काष्ठा ib_qp_attr *qp_attr, पूर्णांक attr_mask)
अणु
	uपूर्णांक64_t T_tr_ns, max_compl_समय_ms;
	uपूर्णांक32_t rq_पंचांगo_jअगरfies;

	/*
	 * According to section 11.2.4.2 in the IBTA spec (Modअगरy Queue Pair,
	 * table 91), both the QP समयout and the retry count have to be set
	 * क्रम RC QP's during the RTR to RTS transition.
	 */
	WARN_ON_ONCE((attr_mask & (IB_QP_TIMEOUT | IB_QP_RETRY_CNT)) !=
		     (IB_QP_TIMEOUT | IB_QP_RETRY_CNT));

	/*
	 * Set target->rq_पंचांगo_jअगरfies to one second more than the largest समय
	 * it can take beक्रमe an error completion is generated. See also
	 * C9-140..142 in the IBTA spec क्रम more inक्रमmation about how to
	 * convert the QP Local ACK Timeout value to nanoseconds.
	 */
	T_tr_ns = 4096 * (1ULL << qp_attr->समयout);
	max_compl_समय_ms = qp_attr->retry_cnt * 4 * T_tr_ns;
	करो_भाग(max_compl_समय_ms, NSEC_PER_MSEC);
	rq_पंचांगo_jअगरfies = msecs_to_jअगरfies(max_compl_समय_ms + 1000);

	वापस rq_पंचांगo_jअगरfies;
पूर्ण

अटल व्योम srp_cm_rep_handler(काष्ठा ib_cm_id *cm_id,
			       स्थिर काष्ठा srp_login_rsp *lrsp,
			       काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा ib_qp_attr *qp_attr = शून्य;
	पूर्णांक attr_mask = 0;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (lrsp->opcode == SRP_LOGIN_RSP) अणु
		ch->max_ti_iu_len = be32_to_cpu(lrsp->max_ti_iu_len);
		ch->req_lim       = be32_to_cpu(lrsp->req_lim_delta);
		ch->use_imm_data  = srp_use_imm_data &&
			(lrsp->rsp_flags & SRP_LOGIN_RSP_IMMED_SUPP);
		ch->max_it_iu_len = srp_max_it_iu_len(target->cmd_sg_cnt,
						      ch->use_imm_data,
						      target->max_it_iu_size);
		WARN_ON_ONCE(ch->max_it_iu_len >
			     be32_to_cpu(lrsp->max_it_iu_len));

		अगर (ch->use_imm_data)
			shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host,
				     PFX "using immediate data\n");

		/*
		 * Reserve credits क्रम task management so we करोn't
		 * bounce requests back to the SCSI mid-layer.
		 */
		target->scsi_host->can_queue
			= min(ch->req_lim - SRP_TSK_MGMT_SQ_SIZE,
			      target->scsi_host->can_queue);
		target->scsi_host->cmd_per_lun
			= min_t(पूर्णांक, target->scsi_host->can_queue,
				target->scsi_host->cmd_per_lun);
	पूर्ण अन्यथा अणु
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "Unhandled RSP opcode %#x\n", lrsp->opcode);
		ret = -ECONNRESET;
		जाओ error;
	पूर्ण

	अगर (!ch->rx_ring) अणु
		ret = srp_alloc_iu_bufs(ch);
		अगर (ret)
			जाओ error;
	पूर्ण

	क्रम (i = 0; i < target->queue_size; i++) अणु
		काष्ठा srp_iu *iu = ch->rx_ring[i];

		ret = srp_post_recv(ch, iu);
		अगर (ret)
			जाओ error;
	पूर्ण

	अगर (!target->using_rdma_cm) अणु
		ret = -ENOMEM;
		qp_attr = kदो_स्मृति(माप(*qp_attr), GFP_KERNEL);
		अगर (!qp_attr)
			जाओ error;

		qp_attr->qp_state = IB_QPS_RTR;
		ret = ib_cm_init_qp_attr(cm_id, qp_attr, &attr_mask);
		अगर (ret)
			जाओ error_मुक्त;

		ret = ib_modअगरy_qp(ch->qp, qp_attr, attr_mask);
		अगर (ret)
			जाओ error_मुक्त;

		qp_attr->qp_state = IB_QPS_RTS;
		ret = ib_cm_init_qp_attr(cm_id, qp_attr, &attr_mask);
		अगर (ret)
			जाओ error_मुक्त;

		target->rq_पंचांगo_jअगरfies = srp_compute_rq_पंचांगo(qp_attr, attr_mask);

		ret = ib_modअगरy_qp(ch->qp, qp_attr, attr_mask);
		अगर (ret)
			जाओ error_मुक्त;

		ret = ib_send_cm_rtu(cm_id, शून्य, 0);
	पूर्ण

error_मुक्त:
	kमुक्त(qp_attr);

error:
	ch->status = ret;
पूर्ण

अटल व्योम srp_ib_cm_rej_handler(काष्ठा ib_cm_id *cm_id,
				  स्थिर काष्ठा ib_cm_event *event,
				  काष्ठा srp_rdma_ch *ch)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा Scsi_Host *shost = target->scsi_host;
	काष्ठा ib_class_port_info *cpi;
	पूर्णांक opcode;
	u16 dlid;

	चयन (event->param.rej_rcvd.reason) अणु
	हाल IB_CM_REJ_PORT_CM_REसूचीECT:
		cpi = event->param.rej_rcvd.ari;
		dlid = be16_to_cpu(cpi->redirect_lid);
		sa_path_set_dlid(&ch->ib_cm.path, dlid);
		ch->ib_cm.path.pkey = cpi->redirect_pkey;
		cm_id->remote_cm_qpn = be32_to_cpu(cpi->redirect_qp) & 0x00ffffff;
		स_नकल(ch->ib_cm.path.dgid.raw, cpi->redirect_gid, 16);

		ch->status = dlid ? SRP_DLID_REसूचीECT : SRP_PORT_REसूचीECT;
		अवरोध;

	हाल IB_CM_REJ_PORT_REसूचीECT:
		अगर (srp_target_is_topspin(target)) अणु
			जोड़ ib_gid *dgid = &ch->ib_cm.path.dgid;

			/*
			 * Topspin/Cisco SRP gateways incorrectly send
			 * reject reason code 25 when they mean 24
			 * (port redirect).
			 */
			स_नकल(dgid->raw, event->param.rej_rcvd.ari, 16);

			shost_prपूर्णांकk(KERN_DEBUG, shost,
				     PFX "Topspin/Cisco redirect to target port GID %016llx%016llx\n",
				     be64_to_cpu(dgid->global.subnet_prefix),
				     be64_to_cpu(dgid->global.पूर्णांकerface_id));

			ch->status = SRP_PORT_REसूचीECT;
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_WARNING, shost,
				     "  REJ reason: IB_CM_REJ_PORT_REDIRECT\n");
			ch->status = -ECONNRESET;
		पूर्ण
		अवरोध;

	हाल IB_CM_REJ_DUPLICATE_LOCAL_COMM_ID:
		shost_prपूर्णांकk(KERN_WARNING, shost,
			    "  REJ reason: IB_CM_REJ_DUPLICATE_LOCAL_COMM_ID\n");
		ch->status = -ECONNRESET;
		अवरोध;

	हाल IB_CM_REJ_CONSUMER_DEFINED:
		opcode = *(u8 *) event->निजी_data;
		अगर (opcode == SRP_LOGIN_REJ) अणु
			काष्ठा srp_login_rej *rej = event->निजी_data;
			u32 reason = be32_to_cpu(rej->reason);

			अगर (reason == SRP_LOGIN_REJ_REQ_IT_IU_LENGTH_TOO_LARGE)
				shost_prपूर्णांकk(KERN_WARNING, shost,
					     PFX "SRP_LOGIN_REJ: requested max_it_iu_len too large\n");
			अन्यथा
				shost_prपूर्णांकk(KERN_WARNING, shost, PFX
					     "SRP LOGIN from %pI6 to %pI6 REJECTED, reason 0x%08x\n",
					     target->sgid.raw,
					     target->ib_cm.orig_dgid.raw,
					     reason);
		पूर्ण अन्यथा
			shost_prपूर्णांकk(KERN_WARNING, shost,
				     "  REJ reason: IB_CM_REJ_CONSUMER_DEFINED,"
				     " opcode 0x%02x\n", opcode);
		ch->status = -ECONNRESET;
		अवरोध;

	हाल IB_CM_REJ_STALE_CONN:
		shost_prपूर्णांकk(KERN_WARNING, shost, "  REJ reason: stale connection\n");
		ch->status = SRP_STALE_CONN;
		अवरोध;

	शेष:
		shost_prपूर्णांकk(KERN_WARNING, shost, "  REJ reason 0x%x\n",
			     event->param.rej_rcvd.reason);
		ch->status = -ECONNRESET;
	पूर्ण
पूर्ण

अटल पूर्णांक srp_ib_cm_handler(काष्ठा ib_cm_id *cm_id,
			     स्थिर काष्ठा ib_cm_event *event)
अणु
	काष्ठा srp_rdma_ch *ch = cm_id->context;
	काष्ठा srp_target_port *target = ch->target;
	पूर्णांक comp = 0;

	चयन (event->event) अणु
	हाल IB_CM_REQ_ERROR:
		shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host,
			     PFX "Sending CM REQ failed\n");
		comp = 1;
		ch->status = -ECONNRESET;
		अवरोध;

	हाल IB_CM_REP_RECEIVED:
		comp = 1;
		srp_cm_rep_handler(cm_id, event->निजी_data, ch);
		अवरोध;

	हाल IB_CM_REJ_RECEIVED:
		shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host, PFX "REJ received\n");
		comp = 1;

		srp_ib_cm_rej_handler(cm_id, event, ch);
		अवरोध;

	हाल IB_CM_DREQ_RECEIVED:
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "DREQ received - connection closed\n");
		ch->connected = false;
		अगर (ib_send_cm_drep(cm_id, शून्य, 0))
			shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
				     PFX "Sending CM DREP failed\n");
		queue_work(प्रणाली_दीर्घ_wq, &target->tl_err_work);
		अवरोध;

	हाल IB_CM_TIMEWAIT_EXIT:
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
			     PFX "connection closed\n");
		comp = 1;

		ch->status = 0;
		अवरोध;

	हाल IB_CM_MRA_RECEIVED:
	हाल IB_CM_DREQ_ERROR:
	हाल IB_CM_DREP_RECEIVED:
		अवरोध;

	शेष:
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "Unhandled CM event %d\n", event->event);
		अवरोध;
	पूर्ण

	अगर (comp)
		complete(&ch->करोne);

	वापस 0;
पूर्ण

अटल व्योम srp_rdma_cm_rej_handler(काष्ठा srp_rdma_ch *ch,
				    काष्ठा rdma_cm_event *event)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा Scsi_Host *shost = target->scsi_host;
	पूर्णांक opcode;

	चयन (event->status) अणु
	हाल IB_CM_REJ_DUPLICATE_LOCAL_COMM_ID:
		shost_prपूर्णांकk(KERN_WARNING, shost,
			    "  REJ reason: IB_CM_REJ_DUPLICATE_LOCAL_COMM_ID\n");
		ch->status = -ECONNRESET;
		अवरोध;

	हाल IB_CM_REJ_CONSUMER_DEFINED:
		opcode = *(u8 *) event->param.conn.निजी_data;
		अगर (opcode == SRP_LOGIN_REJ) अणु
			काष्ठा srp_login_rej *rej =
				(काष्ठा srp_login_rej *)
				event->param.conn.निजी_data;
			u32 reason = be32_to_cpu(rej->reason);

			अगर (reason == SRP_LOGIN_REJ_REQ_IT_IU_LENGTH_TOO_LARGE)
				shost_prपूर्णांकk(KERN_WARNING, shost,
					     PFX "SRP_LOGIN_REJ: requested max_it_iu_len too large\n");
			अन्यथा
				shost_prपूर्णांकk(KERN_WARNING, shost,
					    PFX "SRP LOGIN REJECTED, reason 0x%08x\n", reason);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_WARNING, shost,
				     "  REJ reason: IB_CM_REJ_CONSUMER_DEFINED, opcode 0x%02x\n",
				     opcode);
		पूर्ण
		ch->status = -ECONNRESET;
		अवरोध;

	हाल IB_CM_REJ_STALE_CONN:
		shost_prपूर्णांकk(KERN_WARNING, shost,
			     "  REJ reason: stale connection\n");
		ch->status = SRP_STALE_CONN;
		अवरोध;

	शेष:
		shost_prपूर्णांकk(KERN_WARNING, shost, "  REJ reason 0x%x\n",
			     event->status);
		ch->status = -ECONNRESET;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक srp_rdma_cm_handler(काष्ठा rdma_cm_id *cm_id,
			       काष्ठा rdma_cm_event *event)
अणु
	काष्ठा srp_rdma_ch *ch = cm_id->context;
	काष्ठा srp_target_port *target = ch->target;
	पूर्णांक comp = 0;

	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_ADDR_RESOLVED:
		ch->status = 0;
		comp = 1;
		अवरोध;

	हाल RDMA_CM_EVENT_ADDR_ERROR:
		ch->status = -ENXIO;
		comp = 1;
		अवरोध;

	हाल RDMA_CM_EVENT_ROUTE_RESOLVED:
		ch->status = 0;
		comp = 1;
		अवरोध;

	हाल RDMA_CM_EVENT_ROUTE_ERROR:
	हाल RDMA_CM_EVENT_UNREACHABLE:
		ch->status = -EHOSTUNREACH;
		comp = 1;
		अवरोध;

	हाल RDMA_CM_EVENT_CONNECT_ERROR:
		shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host,
			     PFX "Sending CM REQ failed\n");
		comp = 1;
		ch->status = -ECONNRESET;
		अवरोध;

	हाल RDMA_CM_EVENT_ESTABLISHED:
		comp = 1;
		srp_cm_rep_handler(शून्य, event->param.conn.निजी_data, ch);
		अवरोध;

	हाल RDMA_CM_EVENT_REJECTED:
		shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host, PFX "REJ received\n");
		comp = 1;

		srp_rdma_cm_rej_handler(ch, event);
		अवरोध;

	हाल RDMA_CM_EVENT_DISCONNECTED:
		अगर (ch->connected) अणु
			shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
				     PFX "received DREQ\n");
			rdma_disconnect(ch->rdma_cm.cm_id);
			comp = 1;
			ch->status = 0;
			queue_work(प्रणाली_दीर्घ_wq, &target->tl_err_work);
		पूर्ण
		अवरोध;

	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
		shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
			     PFX "connection closed\n");

		comp = 1;
		ch->status = 0;
		अवरोध;

	शेष:
		shost_prपूर्णांकk(KERN_WARNING, target->scsi_host,
			     PFX "Unhandled CM event %d\n", event->event);
		अवरोध;
	पूर्ण

	अगर (comp)
		complete(&ch->करोne);

	वापस 0;
पूर्ण

/**
 * srp_change_queue_depth - setting device queue depth
 * @sdev: scsi device काष्ठा
 * @qdepth: requested queue depth
 *
 * Returns queue depth.
 */
अटल पूर्णांक
srp_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	अगर (!sdev->tagged_supported)
		qdepth = 1;
	वापस scsi_change_queue_depth(sdev, qdepth);
पूर्ण

अटल पूर्णांक srp_send_tsk_mgmt(काष्ठा srp_rdma_ch *ch, u64 req_tag, u64 lun,
			     u8 func, u8 *status)
अणु
	काष्ठा srp_target_port *target = ch->target;
	काष्ठा srp_rport *rport = target->rport;
	काष्ठा ib_device *dev = target->srp_host->srp_dev->dev;
	काष्ठा srp_iu *iu;
	काष्ठा srp_tsk_mgmt *tsk_mgmt;
	पूर्णांक res;

	अगर (!ch->connected || target->qp_in_error)
		वापस -1;

	/*
	 * Lock the rport mutex to aव्योम that srp_create_ch_ib() is
	 * invoked जबतक a task management function is being sent.
	 */
	mutex_lock(&rport->mutex);
	spin_lock_irq(&ch->lock);
	iu = __srp_get_tx_iu(ch, SRP_IU_TSK_MGMT);
	spin_unlock_irq(&ch->lock);

	अगर (!iu) अणु
		mutex_unlock(&rport->mutex);

		वापस -1;
	पूर्ण

	iu->num_sge = 1;

	ib_dma_sync_single_क्रम_cpu(dev, iu->dma, माप *tsk_mgmt,
				   DMA_TO_DEVICE);
	tsk_mgmt = iu->buf;
	स_रखो(tsk_mgmt, 0, माप *tsk_mgmt);

	tsk_mgmt->opcode 	= SRP_TSK_MGMT;
	पूर्णांक_to_scsilun(lun, &tsk_mgmt->lun);
	tsk_mgmt->tsk_mgmt_func = func;
	tsk_mgmt->task_tag	= req_tag;

	spin_lock_irq(&ch->lock);
	ch->tsk_mgmt_tag = (ch->tsk_mgmt_tag + 1) | SRP_TAG_TSK_MGMT;
	tsk_mgmt->tag = ch->tsk_mgmt_tag;
	spin_unlock_irq(&ch->lock);

	init_completion(&ch->tsk_mgmt_करोne);

	ib_dma_sync_single_क्रम_device(dev, iu->dma, माप *tsk_mgmt,
				      DMA_TO_DEVICE);
	अगर (srp_post_send(ch, iu, माप(*tsk_mgmt))) अणु
		srp_put_tx_iu(ch, iu, SRP_IU_TSK_MGMT);
		mutex_unlock(&rport->mutex);

		वापस -1;
	पूर्ण
	res = रुको_क्रम_completion_समयout(&ch->tsk_mgmt_करोne,
					msecs_to_jअगरfies(SRP_ABORT_TIMEOUT_MS));
	अगर (res > 0 && status)
		*status = ch->tsk_mgmt_status;
	mutex_unlock(&rport->mutex);

	WARN_ON_ONCE(res < 0);

	वापस res > 0 ? 0 : -1;
पूर्ण

अटल पूर्णांक srp_पात(काष्ठा scsi_cmnd *scmnd)
अणु
	काष्ठा srp_target_port *target = host_to_target(scmnd->device->host);
	काष्ठा srp_request *req = (काष्ठा srp_request *) scmnd->host_scribble;
	u32 tag;
	u16 ch_idx;
	काष्ठा srp_rdma_ch *ch;
	पूर्णांक ret;

	shost_prपूर्णांकk(KERN_ERR, target->scsi_host, "SRP abort called\n");

	अगर (!req)
		वापस SUCCESS;
	tag = blk_mq_unique_tag(scmnd->request);
	ch_idx = blk_mq_unique_tag_to_hwq(tag);
	अगर (WARN_ON_ONCE(ch_idx >= target->ch_count))
		वापस SUCCESS;
	ch = &target->ch[ch_idx];
	अगर (!srp_claim_req(ch, req, शून्य, scmnd))
		वापस SUCCESS;
	shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
		     "Sending SRP abort for tag %#x\n", tag);
	अगर (srp_send_tsk_mgmt(ch, tag, scmnd->device->lun,
			      SRP_TSK_ABORT_TASK, शून्य) == 0)
		ret = SUCCESS;
	अन्यथा अगर (target->rport->state == SRP_RPORT_LOST)
		ret = FAST_IO_FAIL;
	अन्यथा
		ret = FAILED;
	अगर (ret == SUCCESS) अणु
		srp_मुक्त_req(ch, req, scmnd, 0);
		scmnd->result = DID_ABORT << 16;
		scmnd->scsi_करोne(scmnd);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक srp_reset_device(काष्ठा scsi_cmnd *scmnd)
अणु
	काष्ठा srp_target_port *target = host_to_target(scmnd->device->host);
	काष्ठा srp_rdma_ch *ch;
	u8 status;

	shost_prपूर्णांकk(KERN_ERR, target->scsi_host, "SRP reset_device called\n");

	ch = &target->ch[0];
	अगर (srp_send_tsk_mgmt(ch, SRP_TAG_NO_REQ, scmnd->device->lun,
			      SRP_TSK_LUN_RESET, &status))
		वापस FAILED;
	अगर (status)
		वापस FAILED;

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक srp_reset_host(काष्ठा scsi_cmnd *scmnd)
अणु
	काष्ठा srp_target_port *target = host_to_target(scmnd->device->host);

	shost_prपूर्णांकk(KERN_ERR, target->scsi_host, PFX "SRP reset_host called\n");

	वापस srp_reconnect_rport(target->rport) == 0 ? SUCCESS : FAILED;
पूर्ण

अटल पूर्णांक srp_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा srp_target_port *target = host_to_target(shost);

	अगर (target->target_can_queue)
		starget->can_queue = target->target_can_queue;
	वापस 0;
पूर्ण

अटल पूर्णांक srp_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा srp_target_port *target = host_to_target(shost);
	काष्ठा request_queue *q = sdev->request_queue;
	अचिन्हित दीर्घ समयout;

	अगर (sdev->type == TYPE_DISK) अणु
		समयout = max_t(अचिन्हित, 30 * HZ, target->rq_पंचांगo_jअगरfies);
		blk_queue_rq_समयout(q, समयout);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_id_ext(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "0x%016llx\n", be64_to_cpu(target->id_ext));
पूर्ण

अटल sमाप_प्रकार show_ioc_guid(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "0x%016llx\n", be64_to_cpu(target->ioc_guid));
पूर्ण

अटल sमाप_प्रकार show_service_id(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	अगर (target->using_rdma_cm)
		वापस -ENOENT;
	वापस sysfs_emit(buf, "0x%016llx\n",
			  be64_to_cpu(target->ib_cm.service_id));
पूर्ण

अटल sमाप_प्रकार show_pkey(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	अगर (target->using_rdma_cm)
		वापस -ENOENT;

	वापस sysfs_emit(buf, "0x%04x\n", be16_to_cpu(target->ib_cm.pkey));
पूर्ण

अटल sमाप_प्रकार show_sgid(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%pI6\n", target->sgid.raw);
पूर्ण

अटल sमाप_प्रकार show_dgid(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));
	काष्ठा srp_rdma_ch *ch = &target->ch[0];

	अगर (target->using_rdma_cm)
		वापस -ENOENT;

	वापस sysfs_emit(buf, "%pI6\n", ch->ib_cm.path.dgid.raw);
पूर्ण

अटल sमाप_प्रकार show_orig_dgid(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	अगर (target->using_rdma_cm)
		वापस -ENOENT;

	वापस sysfs_emit(buf, "%pI6\n", target->ib_cm.orig_dgid.raw);
पूर्ण

अटल sमाप_प्रकार show_req_lim(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));
	काष्ठा srp_rdma_ch *ch;
	पूर्णांक i, req_lim = पूर्णांक_उच्च;

	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		req_lim = min(req_lim, ch->req_lim);
	पूर्ण

	वापस sysfs_emit(buf, "%d\n", req_lim);
पूर्ण

अटल sमाप_प्रकार show_zero_req_lim(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%d\n", target->zero_req_lim);
पूर्ण

अटल sमाप_प्रकार show_local_ib_port(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%d\n", target->srp_host->port);
पूर्ण

अटल sमाप_प्रकार show_local_ib_device(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%s\n",
			  dev_name(&target->srp_host->srp_dev->dev->dev));
पूर्ण

अटल sमाप_प्रकार show_ch_count(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%d\n", target->ch_count);
पूर्ण

अटल sमाप_प्रकार show_comp_vector(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%d\n", target->comp_vector);
पूर्ण

अटल sमाप_प्रकार show_tl_retry_count(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%d\n", target->tl_retry_count);
पूर्ण

अटल sमाप_प्रकार show_cmd_sg_entries(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%u\n", target->cmd_sg_cnt);
पूर्ण

अटल sमाप_प्रकार show_allow_ext_sg(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा srp_target_port *target = host_to_target(class_to_shost(dev));

	वापस sysfs_emit(buf, "%s\n", target->allow_ext_sg ? "true" : "false");
पूर्ण

अटल DEVICE_ATTR(id_ext,	    S_IRUGO, show_id_ext,	   शून्य);
अटल DEVICE_ATTR(ioc_guid,	    S_IRUGO, show_ioc_guid,	   शून्य);
अटल DEVICE_ATTR(service_id,	    S_IRUGO, show_service_id,	   शून्य);
अटल DEVICE_ATTR(pkey,	    S_IRUGO, show_pkey,		   शून्य);
अटल DEVICE_ATTR(sgid,	    S_IRUGO, show_sgid,		   शून्य);
अटल DEVICE_ATTR(dgid,	    S_IRUGO, show_dgid,		   शून्य);
अटल DEVICE_ATTR(orig_dgid,	    S_IRUGO, show_orig_dgid,	   शून्य);
अटल DEVICE_ATTR(req_lim,         S_IRUGO, show_req_lim,         शून्य);
अटल DEVICE_ATTR(zero_req_lim,    S_IRUGO, show_zero_req_lim,	   शून्य);
अटल DEVICE_ATTR(local_ib_port,   S_IRUGO, show_local_ib_port,   शून्य);
अटल DEVICE_ATTR(local_ib_device, S_IRUGO, show_local_ib_device, शून्य);
अटल DEVICE_ATTR(ch_count,        S_IRUGO, show_ch_count,        शून्य);
अटल DEVICE_ATTR(comp_vector,     S_IRUGO, show_comp_vector,     शून्य);
अटल DEVICE_ATTR(tl_retry_count,  S_IRUGO, show_tl_retry_count,  शून्य);
अटल DEVICE_ATTR(cmd_sg_entries,  S_IRUGO, show_cmd_sg_entries,  शून्य);
अटल DEVICE_ATTR(allow_ext_sg,    S_IRUGO, show_allow_ext_sg,    शून्य);

अटल काष्ठा device_attribute *srp_host_attrs[] = अणु
	&dev_attr_id_ext,
	&dev_attr_ioc_guid,
	&dev_attr_service_id,
	&dev_attr_pkey,
	&dev_attr_sgid,
	&dev_attr_dgid,
	&dev_attr_orig_dgid,
	&dev_attr_req_lim,
	&dev_attr_zero_req_lim,
	&dev_attr_local_ib_port,
	&dev_attr_local_ib_device,
	&dev_attr_ch_count,
	&dev_attr_comp_vector,
	&dev_attr_tl_retry_count,
	&dev_attr_cmd_sg_entries,
	&dev_attr_allow_ext_sg,
	शून्य
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा srp_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= "InfiniBand SRP initiator",
	.proc_name			= DRV_NAME,
	.target_alloc			= srp_target_alloc,
	.slave_configure		= srp_slave_configure,
	.info				= srp_target_info,
	.queuecommand			= srp_queuecommand,
	.change_queue_depth             = srp_change_queue_depth,
	.eh_समयd_out			= srp_समयd_out,
	.eh_पात_handler		= srp_पात,
	.eh_device_reset_handler	= srp_reset_device,
	.eh_host_reset_handler		= srp_reset_host,
	.skip_settle_delay		= true,
	.sg_tablesize			= SRP_DEF_SG_TABLESIZE,
	.can_queue			= SRP_DEFAULT_CMD_SQ_SIZE,
	.this_id			= -1,
	.cmd_per_lun			= SRP_DEFAULT_CMD_SQ_SIZE,
	.shost_attrs			= srp_host_attrs,
	.track_queue_depth		= 1,
पूर्ण;

अटल पूर्णांक srp_sdev_count(काष्ठा Scsi_Host *host)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक c = 0;

	shost_क्रम_each_device(sdev, host)
		c++;

	वापस c;
पूर्ण

/*
 * Return values:
 * < 0 upon failure. Caller is responsible क्रम SRP target port cleanup.
 * 0 and target->state == SRP_TARGET_REMOVED अगर asynchronous target port
 *    removal has been scheduled.
 * 0 and target->state != SRP_TARGET_REMOVED upon success.
 */
अटल पूर्णांक srp_add_target(काष्ठा srp_host *host, काष्ठा srp_target_port *target)
अणु
	काष्ठा srp_rport_identअगरiers ids;
	काष्ठा srp_rport *rport;

	target->state = SRP_TARGET_SCANNING;
	प्र_लिखो(target->target_name, "SRP.T10:%016llX",
		be64_to_cpu(target->id_ext));

	अगर (scsi_add_host(target->scsi_host, host->srp_dev->dev->dev.parent))
		वापस -ENODEV;

	स_नकल(ids.port_id, &target->id_ext, 8);
	स_नकल(ids.port_id + 8, &target->ioc_guid, 8);
	ids.roles = SRP_RPORT_ROLE_TARGET;
	rport = srp_rport_add(target->scsi_host, &ids);
	अगर (IS_ERR(rport)) अणु
		scsi_हटाओ_host(target->scsi_host);
		वापस PTR_ERR(rport);
	पूर्ण

	rport->lld_data = target;
	target->rport = rport;

	spin_lock(&host->target_lock);
	list_add_tail(&target->list, &host->target_list);
	spin_unlock(&host->target_lock);

	scsi_scan_target(&target->scsi_host->shost_gendev,
			 0, target->scsi_id, SCAN_WILD_CARD, SCSI_SCAN_INITIAL);

	अगर (srp_connected_ch(target) < target->ch_count ||
	    target->qp_in_error) अणु
		shost_prपूर्णांकk(KERN_INFO, target->scsi_host,
			     PFX "SCSI scan failed - removing SCSI host\n");
		srp_queue_हटाओ_work(target);
		जाओ out;
	पूर्ण

	pr_debug("%s: SCSI scan succeeded - detected %d LUNs\n",
		 dev_name(&target->scsi_host->shost_gendev),
		 srp_sdev_count(target->scsi_host));

	spin_lock_irq(&target->lock);
	अगर (target->state == SRP_TARGET_SCANNING)
		target->state = SRP_TARGET_LIVE;
	spin_unlock_irq(&target->lock);

out:
	वापस 0;
पूर्ण

अटल व्योम srp_release_dev(काष्ठा device *dev)
अणु
	काष्ठा srp_host *host =
		container_of(dev, काष्ठा srp_host, dev);

	complete(&host->released);
पूर्ण

अटल काष्ठा class srp_class = अणु
	.name    = "infiniband_srp",
	.dev_release = srp_release_dev
पूर्ण;

/**
 * srp_conn_unique() - check whether the connection to a target is unique
 * @host:   SRP host.
 * @target: SRP target port.
 */
अटल bool srp_conn_unique(काष्ठा srp_host *host,
			    काष्ठा srp_target_port *target)
अणु
	काष्ठा srp_target_port *t;
	bool ret = false;

	अगर (target->state == SRP_TARGET_REMOVED)
		जाओ out;

	ret = true;

	spin_lock(&host->target_lock);
	list_क्रम_each_entry(t, &host->target_list, list) अणु
		अगर (t != target &&
		    target->id_ext == t->id_ext &&
		    target->ioc_guid == t->ioc_guid &&
		    target->initiator_ext == t->initiator_ext) अणु
			ret = false;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&host->target_lock);

out:
	वापस ret;
पूर्ण

/*
 * Target ports are added by writing
 *
 *     id_ext=<SRP ID ext>,ioc_guid=<SRP IOC GUID>,dgid=<dest GID>,
 *     pkey=<P_Key>,service_id=<service ID>
 * or
 *     id_ext=<SRP ID ext>,ioc_guid=<SRP IOC GUID>,
 *     [src=<IPv4 address>,]dest=<IPv4 address>:<port number>
 *
 * to the add_target sysfs attribute.
 */
क्रमागत अणु
	SRP_OPT_ERR		= 0,
	SRP_OPT_ID_EXT		= 1 << 0,
	SRP_OPT_IOC_GUID	= 1 << 1,
	SRP_OPT_DGID		= 1 << 2,
	SRP_OPT_PKEY		= 1 << 3,
	SRP_OPT_SERVICE_ID	= 1 << 4,
	SRP_OPT_MAX_SECT	= 1 << 5,
	SRP_OPT_MAX_CMD_PER_LUN	= 1 << 6,
	SRP_OPT_IO_CLASS	= 1 << 7,
	SRP_OPT_INITIATOR_EXT	= 1 << 8,
	SRP_OPT_CMD_SG_ENTRIES	= 1 << 9,
	SRP_OPT_ALLOW_EXT_SG	= 1 << 10,
	SRP_OPT_SG_TABLESIZE	= 1 << 11,
	SRP_OPT_COMP_VECTOR	= 1 << 12,
	SRP_OPT_TL_RETRY_COUNT	= 1 << 13,
	SRP_OPT_QUEUE_SIZE	= 1 << 14,
	SRP_OPT_IP_SRC		= 1 << 15,
	SRP_OPT_IP_DEST		= 1 << 16,
	SRP_OPT_TARGET_CAN_QUEUE= 1 << 17,
	SRP_OPT_MAX_IT_IU_SIZE  = 1 << 18,
	SRP_OPT_CH_COUNT	= 1 << 19,
पूर्ण;

अटल अचिन्हित पूर्णांक srp_opt_mandatory[] = अणु
	SRP_OPT_ID_EXT		|
	SRP_OPT_IOC_GUID	|
	SRP_OPT_DGID		|
	SRP_OPT_PKEY		|
	SRP_OPT_SERVICE_ID,
	SRP_OPT_ID_EXT		|
	SRP_OPT_IOC_GUID	|
	SRP_OPT_IP_DEST,
पूर्ण;

अटल स्थिर match_table_t srp_opt_tokens = अणु
	अणु SRP_OPT_ID_EXT,		"id_ext=%s" 		पूर्ण,
	अणु SRP_OPT_IOC_GUID,		"ioc_guid=%s" 		पूर्ण,
	अणु SRP_OPT_DGID,			"dgid=%s" 		पूर्ण,
	अणु SRP_OPT_PKEY,			"pkey=%x" 		पूर्ण,
	अणु SRP_OPT_SERVICE_ID,		"service_id=%s"		पूर्ण,
	अणु SRP_OPT_MAX_SECT,		"max_sect=%d" 		पूर्ण,
	अणु SRP_OPT_MAX_CMD_PER_LUN,	"max_cmd_per_lun=%d" 	पूर्ण,
	अणु SRP_OPT_TARGET_CAN_QUEUE,	"target_can_queue=%d"	पूर्ण,
	अणु SRP_OPT_IO_CLASS,		"io_class=%x"		पूर्ण,
	अणु SRP_OPT_INITIATOR_EXT,	"initiator_ext=%s"	पूर्ण,
	अणु SRP_OPT_CMD_SG_ENTRIES,	"cmd_sg_entries=%u"	पूर्ण,
	अणु SRP_OPT_ALLOW_EXT_SG,		"allow_ext_sg=%u"	पूर्ण,
	अणु SRP_OPT_SG_TABLESIZE,		"sg_tablesize=%u"	पूर्ण,
	अणु SRP_OPT_COMP_VECTOR,		"comp_vector=%u"	पूर्ण,
	अणु SRP_OPT_TL_RETRY_COUNT,	"tl_retry_count=%u"	पूर्ण,
	अणु SRP_OPT_QUEUE_SIZE,		"queue_size=%d"		पूर्ण,
	अणु SRP_OPT_IP_SRC,		"src=%s"		पूर्ण,
	अणु SRP_OPT_IP_DEST,		"dest=%s"		पूर्ण,
	अणु SRP_OPT_MAX_IT_IU_SIZE,	"max_it_iu_size=%d"	पूर्ण,
	अणु SRP_OPT_CH_COUNT,		"ch_count=%u",		पूर्ण,
	अणु SRP_OPT_ERR,			शून्य 			पूर्ण
पूर्ण;

/**
 * srp_parse_in - parse an IP address and port number combination
 * @net:	   [in]  Network namespace.
 * @sa:		   [out] Address family, IP address and port number.
 * @addr_port_str: [in]  IP address and port number.
 * @has_port:	   [out] Whether or not @addr_port_str includes a port number.
 *
 * Parse the following address क्रमmats:
 * - IPv4: <ip_address>:<port>, e.g. 1.2.3.4:5.
 * - IPv6: \[<ipv6_address>\]:<port>, e.g. [1::2:3%4]:5.
 */
अटल पूर्णांक srp_parse_in(काष्ठा net *net, काष्ठा sockaddr_storage *sa,
			स्थिर अक्षर *addr_port_str, bool *has_port)
अणु
	अक्षर *addr_end, *addr = kstrdup(addr_port_str, GFP_KERNEL);
	अक्षर *port_str;
	पूर्णांक ret;

	अगर (!addr)
		वापस -ENOMEM;
	port_str = म_खोजप(addr, ':');
	अगर (port_str && म_अक्षर(port_str, ']'))
		port_str = शून्य;
	अगर (port_str)
		*port_str++ = '\0';
	अगर (has_port)
		*has_port = port_str != शून्य;
	ret = inet_pton_with_scope(net, AF_INET, addr, port_str, sa);
	अगर (ret && addr[0]) अणु
		addr_end = addr + म_माप(addr) - 1;
		अगर (addr[0] == '[' && *addr_end == ']') अणु
			*addr_end = '\0';
			ret = inet_pton_with_scope(net, AF_INET6, addr + 1,
						   port_str, sa);
		पूर्ण
	पूर्ण
	kमुक्त(addr);
	pr_debug("%s -> %pISpfsc\n", addr_port_str, sa);
	वापस ret;
पूर्ण

अटल पूर्णांक srp_parse_options(काष्ठा net *net, स्थिर अक्षर *buf,
			     काष्ठा srp_target_port *target)
अणु
	अक्षर *options, *sep_opt;
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	अचिन्हित दीर्घ दीर्घ ull;
	bool has_port;
	पूर्णांक opt_mask = 0;
	पूर्णांक token;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	options = kstrdup(buf, GFP_KERNEL);
	अगर (!options)
		वापस -ENOMEM;

	sep_opt = options;
	जबतक ((p = strsep(&sep_opt, ",\n")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, srp_opt_tokens, args);
		opt_mask |= token;

		चयन (token) अणु
		हाल SRP_OPT_ID_EXT:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			ret = kम_से_अदीर्घl(p, 16, &ull);
			अगर (ret) अणु
				pr_warn("invalid id_ext parameter '%s'\n", p);
				kमुक्त(p);
				जाओ out;
			पूर्ण
			target->id_ext = cpu_to_be64(ull);
			kमुक्त(p);
			अवरोध;

		हाल SRP_OPT_IOC_GUID:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			ret = kम_से_अदीर्घl(p, 16, &ull);
			अगर (ret) अणु
				pr_warn("invalid ioc_guid parameter '%s'\n", p);
				kमुक्त(p);
				जाओ out;
			पूर्ण
			target->ioc_guid = cpu_to_be64(ull);
			kमुक्त(p);
			अवरोध;

		हाल SRP_OPT_DGID:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अगर (म_माप(p) != 32) अणु
				pr_warn("bad dest GID parameter '%s'\n", p);
				kमुक्त(p);
				जाओ out;
			पूर्ण

			ret = hex2bin(target->ib_cm.orig_dgid.raw, p, 16);
			kमुक्त(p);
			अगर (ret < 0)
				जाओ out;
			अवरोध;

		हाल SRP_OPT_PKEY:
			अगर (match_hex(args, &token)) अणु
				pr_warn("bad P_Key parameter '%s'\n", p);
				जाओ out;
			पूर्ण
			target->ib_cm.pkey = cpu_to_be16(token);
			अवरोध;

		हाल SRP_OPT_SERVICE_ID:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			ret = kम_से_अदीर्घl(p, 16, &ull);
			अगर (ret) अणु
				pr_warn("bad service_id parameter '%s'\n", p);
				kमुक्त(p);
				जाओ out;
			पूर्ण
			target->ib_cm.service_id = cpu_to_be64(ull);
			kमुक्त(p);
			अवरोध;

		हाल SRP_OPT_IP_SRC:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			ret = srp_parse_in(net, &target->rdma_cm.src.ss, p,
					   शून्य);
			अगर (ret < 0) अणु
				pr_warn("bad source parameter '%s'\n", p);
				kमुक्त(p);
				जाओ out;
			पूर्ण
			target->rdma_cm.src_specअगरied = true;
			kमुक्त(p);
			अवरोध;

		हाल SRP_OPT_IP_DEST:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			ret = srp_parse_in(net, &target->rdma_cm.dst.ss, p,
					   &has_port);
			अगर (!has_port)
				ret = -EINVAL;
			अगर (ret < 0) अणु
				pr_warn("bad dest parameter '%s'\n", p);
				kमुक्त(p);
				जाओ out;
			पूर्ण
			target->using_rdma_cm = true;
			kमुक्त(p);
			अवरोध;

		हाल SRP_OPT_MAX_SECT:
			अगर (match_पूर्णांक(args, &token)) अणु
				pr_warn("bad max sect parameter '%s'\n", p);
				जाओ out;
			पूर्ण
			target->scsi_host->max_sectors = token;
			अवरोध;

		हाल SRP_OPT_QUEUE_SIZE:
			अगर (match_पूर्णांक(args, &token) || token < 1) अणु
				pr_warn("bad queue_size parameter '%s'\n", p);
				जाओ out;
			पूर्ण
			target->scsi_host->can_queue = token;
			target->queue_size = token + SRP_RSP_SQ_SIZE +
					     SRP_TSK_MGMT_SQ_SIZE;
			अगर (!(opt_mask & SRP_OPT_MAX_CMD_PER_LUN))
				target->scsi_host->cmd_per_lun = token;
			अवरोध;

		हाल SRP_OPT_MAX_CMD_PER_LUN:
			अगर (match_पूर्णांक(args, &token) || token < 1) अणु
				pr_warn("bad max cmd_per_lun parameter '%s'\n",
					p);
				जाओ out;
			पूर्ण
			target->scsi_host->cmd_per_lun = token;
			अवरोध;

		हाल SRP_OPT_TARGET_CAN_QUEUE:
			अगर (match_पूर्णांक(args, &token) || token < 1) अणु
				pr_warn("bad max target_can_queue parameter '%s'\n",
					p);
				जाओ out;
			पूर्ण
			target->target_can_queue = token;
			अवरोध;

		हाल SRP_OPT_IO_CLASS:
			अगर (match_hex(args, &token)) अणु
				pr_warn("bad IO class parameter '%s'\n", p);
				जाओ out;
			पूर्ण
			अगर (token != SRP_REV10_IB_IO_CLASS &&
			    token != SRP_REV16A_IB_IO_CLASS) अणु
				pr_warn("unknown IO class parameter value %x specified (use %x or %x).\n",
					token, SRP_REV10_IB_IO_CLASS,
					SRP_REV16A_IB_IO_CLASS);
				जाओ out;
			पूर्ण
			target->io_class = token;
			अवरोध;

		हाल SRP_OPT_INITIATOR_EXT:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			ret = kम_से_अदीर्घl(p, 16, &ull);
			अगर (ret) अणु
				pr_warn("bad initiator_ext value '%s'\n", p);
				kमुक्त(p);
				जाओ out;
			पूर्ण
			target->initiator_ext = cpu_to_be64(ull);
			kमुक्त(p);
			अवरोध;

		हाल SRP_OPT_CMD_SG_ENTRIES:
			अगर (match_पूर्णांक(args, &token) || token < 1 || token > 255) अणु
				pr_warn("bad max cmd_sg_entries parameter '%s'\n",
					p);
				जाओ out;
			पूर्ण
			target->cmd_sg_cnt = token;
			अवरोध;

		हाल SRP_OPT_ALLOW_EXT_SG:
			अगर (match_पूर्णांक(args, &token)) अणु
				pr_warn("bad allow_ext_sg parameter '%s'\n", p);
				जाओ out;
			पूर्ण
			target->allow_ext_sg = !!token;
			अवरोध;

		हाल SRP_OPT_SG_TABLESIZE:
			अगर (match_पूर्णांक(args, &token) || token < 1 ||
					token > SG_MAX_SEGMENTS) अणु
				pr_warn("bad max sg_tablesize parameter '%s'\n",
					p);
				जाओ out;
			पूर्ण
			target->sg_tablesize = token;
			अवरोध;

		हाल SRP_OPT_COMP_VECTOR:
			अगर (match_पूर्णांक(args, &token) || token < 0) अणु
				pr_warn("bad comp_vector parameter '%s'\n", p);
				जाओ out;
			पूर्ण
			target->comp_vector = token;
			अवरोध;

		हाल SRP_OPT_TL_RETRY_COUNT:
			अगर (match_पूर्णांक(args, &token) || token < 2 || token > 7) अणु
				pr_warn("bad tl_retry_count parameter '%s' (must be a number between 2 and 7)\n",
					p);
				जाओ out;
			पूर्ण
			target->tl_retry_count = token;
			अवरोध;

		हाल SRP_OPT_MAX_IT_IU_SIZE:
			अगर (match_पूर्णांक(args, &token) || token < 0) अणु
				pr_warn("bad maximum initiator to target IU size '%s'\n", p);
				जाओ out;
			पूर्ण
			target->max_it_iu_size = token;
			अवरोध;

		हाल SRP_OPT_CH_COUNT:
			अगर (match_पूर्णांक(args, &token) || token < 1) अणु
				pr_warn("bad channel count %s\n", p);
				जाओ out;
			पूर्ण
			target->ch_count = token;
			अवरोध;

		शेष:
			pr_warn("unknown parameter or missing value '%s' in target creation request\n",
				p);
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(srp_opt_mandatory); i++) अणु
		अगर ((opt_mask & srp_opt_mandatory[i]) == srp_opt_mandatory[i]) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret)
		pr_warn("target creation request is missing one or more parameters\n");

	अगर (target->scsi_host->cmd_per_lun > target->scsi_host->can_queue
	    && (opt_mask & SRP_OPT_MAX_CMD_PER_LUN))
		pr_warn("cmd_per_lun = %d > queue_size = %d\n",
			target->scsi_host->cmd_per_lun,
			target->scsi_host->can_queue);

out:
	kमुक्त(options);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार srp_create_target(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा srp_host *host =
		container_of(dev, काष्ठा srp_host, dev);
	काष्ठा Scsi_Host *target_host;
	काष्ठा srp_target_port *target;
	काष्ठा srp_rdma_ch *ch;
	काष्ठा srp_device *srp_dev = host->srp_dev;
	काष्ठा ib_device *ibdev = srp_dev->dev;
	पूर्णांक ret, i, ch_idx;
	अचिन्हित पूर्णांक max_sectors_per_mr, mr_per_cmd = 0;
	bool multich = false;
	uपूर्णांक32_t max_iu_len;

	target_host = scsi_host_alloc(&srp_ढाँचा,
				      माप (काष्ठा srp_target_port));
	अगर (!target_host)
		वापस -ENOMEM;

	target_host->transportt  = ib_srp_transport_ढाँचा;
	target_host->max_channel = 0;
	target_host->max_id      = 1;
	target_host->max_lun     = -1LL;
	target_host->max_cmd_len = माप ((काष्ठा srp_cmd *) (व्योम *) 0L)->cdb;
	target_host->max_segment_size = ib_dma_max_seg_size(ibdev);

	अगर (!(ibdev->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG))
		target_host->virt_boundary_mask = ~srp_dev->mr_page_mask;

	target = host_to_target(target_host);

	target->net		= kobj_ns_grab_current(KOBJ_NS_TYPE_NET);
	target->io_class	= SRP_REV16A_IB_IO_CLASS;
	target->scsi_host	= target_host;
	target->srp_host	= host;
	target->lkey		= host->srp_dev->pd->local_dma_lkey;
	target->global_rkey	= host->srp_dev->global_rkey;
	target->cmd_sg_cnt	= cmd_sg_entries;
	target->sg_tablesize	= indirect_sg_entries ? : cmd_sg_entries;
	target->allow_ext_sg	= allow_ext_sg;
	target->tl_retry_count	= 7;
	target->queue_size	= SRP_DEFAULT_QUEUE_SIZE;

	/*
	 * Aव्योम that the SCSI host can be हटाओd by srp_हटाओ_target()
	 * beक्रमe this function वापसs.
	 */
	scsi_host_get(target->scsi_host);

	ret = mutex_lock_पूर्णांकerruptible(&host->add_target_mutex);
	अगर (ret < 0)
		जाओ put;

	ret = srp_parse_options(target->net, buf, target);
	अगर (ret)
		जाओ out;

	target->req_ring_size = target->queue_size - SRP_TSK_MGMT_SQ_SIZE;

	अगर (!srp_conn_unique(target->srp_host, target)) अणु
		अगर (target->using_rdma_cm) अणु
			shost_prपूर्णांकk(KERN_INFO, target->scsi_host,
				     PFX "Already connected to target port with id_ext=%016llx;ioc_guid=%016llx;dest=%pIS\n",
				     be64_to_cpu(target->id_ext),
				     be64_to_cpu(target->ioc_guid),
				     &target->rdma_cm.dst);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_INFO, target->scsi_host,
				     PFX "Already connected to target port with id_ext=%016llx;ioc_guid=%016llx;initiator_ext=%016llx\n",
				     be64_to_cpu(target->id_ext),
				     be64_to_cpu(target->ioc_guid),
				     be64_to_cpu(target->initiator_ext));
		पूर्ण
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	अगर (!srp_dev->has_fr && !target->allow_ext_sg &&
	    target->cmd_sg_cnt < target->sg_tablesize) अणु
		pr_warn("No MR pool and no external indirect descriptors, limiting sg_tablesize to cmd_sg_cnt\n");
		target->sg_tablesize = target->cmd_sg_cnt;
	पूर्ण

	अगर (srp_dev->use_fast_reg) अणु
		bool gaps_reg = (ibdev->attrs.device_cap_flags &
				 IB_DEVICE_SG_GAPS_REG);

		max_sectors_per_mr = srp_dev->max_pages_per_mr <<
				  (ilog2(srp_dev->mr_page_size) - 9);
		अगर (!gaps_reg) अणु
			/*
			 * FR can only map one HCA page per entry. If the start
			 * address is not aligned on a HCA page boundary two
			 * entries will be used क्रम the head and the tail
			 * although these two entries combined contain at most
			 * one HCA page of data. Hence the "+ 1" in the
			 * calculation below.
			 *
			 * The indirect data buffer descriptor is contiguous
			 * so the memory क्रम that buffer will only be
			 * रेजिस्टरed अगर रेजिस्टर_always is true. Hence add
			 * one to mr_per_cmd अगर रेजिस्टर_always has been set.
			 */
			mr_per_cmd = रेजिस्टर_always +
				(target->scsi_host->max_sectors + 1 +
				 max_sectors_per_mr - 1) / max_sectors_per_mr;
		पूर्ण अन्यथा अणु
			mr_per_cmd = रेजिस्टर_always +
				(target->sg_tablesize +
				 srp_dev->max_pages_per_mr - 1) /
				srp_dev->max_pages_per_mr;
		पूर्ण
		pr_debug("max_sectors = %u; max_pages_per_mr = %u; mr_page_size = %u; max_sectors_per_mr = %u; mr_per_cmd = %u\n",
			 target->scsi_host->max_sectors, srp_dev->max_pages_per_mr, srp_dev->mr_page_size,
			 max_sectors_per_mr, mr_per_cmd);
	पूर्ण

	target_host->sg_tablesize = target->sg_tablesize;
	target->mr_pool_size = target->scsi_host->can_queue * mr_per_cmd;
	target->mr_per_cmd = mr_per_cmd;
	target->indirect_size = target->sg_tablesize *
				माप (काष्ठा srp_direct_buf);
	max_iu_len = srp_max_it_iu_len(target->cmd_sg_cnt,
				       srp_use_imm_data,
				       target->max_it_iu_size);

	INIT_WORK(&target->tl_err_work, srp_tl_err_work);
	INIT_WORK(&target->हटाओ_work, srp_हटाओ_work);
	spin_lock_init(&target->lock);
	ret = rdma_query_gid(ibdev, host->port, 0, &target->sgid);
	अगर (ret)
		जाओ out;

	ret = -ENOMEM;
	अगर (target->ch_count == 0) अणु
		target->ch_count =
			min(ch_count ?:
				max(4 * num_online_nodes(),
				    ibdev->num_comp_vectors),
				num_online_cpus());
	पूर्ण

	target->ch = kसुस्मृति(target->ch_count, माप(*target->ch),
			     GFP_KERNEL);
	अगर (!target->ch)
		जाओ out;

	क्रम (ch_idx = 0; ch_idx < target->ch_count; ++ch_idx) अणु
		ch = &target->ch[ch_idx];
		ch->target = target;
		ch->comp_vector = ch_idx % ibdev->num_comp_vectors;
		spin_lock_init(&ch->lock);
		INIT_LIST_HEAD(&ch->मुक्त_tx);
		ret = srp_new_cm_id(ch);
		अगर (ret)
			जाओ err_disconnect;

		ret = srp_create_ch_ib(ch);
		अगर (ret)
			जाओ err_disconnect;

		ret = srp_alloc_req_data(ch);
		अगर (ret)
			जाओ err_disconnect;

		ret = srp_connect_ch(ch, max_iu_len, multich);
		अगर (ret) अणु
			अक्षर dst[64];

			अगर (target->using_rdma_cm)
				snम_लिखो(dst, माप(dst), "%pIS",
					&target->rdma_cm.dst);
			अन्यथा
				snम_लिखो(dst, माप(dst), "%pI6",
					target->ib_cm.orig_dgid.raw);
			shost_prपूर्णांकk(KERN_ERR, target->scsi_host,
				PFX "Connection %d/%d to %s failed\n",
				ch_idx,
				target->ch_count, dst);
			अगर (ch_idx == 0) अणु
				जाओ मुक्त_ch;
			पूर्ण अन्यथा अणु
				srp_मुक्त_ch_ib(target, ch);
				srp_मुक्त_req_data(target, ch);
				target->ch_count = ch - target->ch;
				जाओ connected;
			पूर्ण
		पूर्ण
		multich = true;
	पूर्ण

connected:
	target->scsi_host->nr_hw_queues = target->ch_count;

	ret = srp_add_target(host, target);
	अगर (ret)
		जाओ err_disconnect;

	अगर (target->state != SRP_TARGET_REMOVED) अणु
		अगर (target->using_rdma_cm) अणु
			shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host, PFX
				     "new target: id_ext %016llx ioc_guid %016llx sgid %pI6 dest %pIS\n",
				     be64_to_cpu(target->id_ext),
				     be64_to_cpu(target->ioc_guid),
				     target->sgid.raw, &target->rdma_cm.dst);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_DEBUG, target->scsi_host, PFX
				     "new target: id_ext %016llx ioc_guid %016llx pkey %04x service_id %016llx sgid %pI6 dgid %pI6\n",
				     be64_to_cpu(target->id_ext),
				     be64_to_cpu(target->ioc_guid),
				     be16_to_cpu(target->ib_cm.pkey),
				     be64_to_cpu(target->ib_cm.service_id),
				     target->sgid.raw,
				     target->ib_cm.orig_dgid.raw);
		पूर्ण
	पूर्ण

	ret = count;

out:
	mutex_unlock(&host->add_target_mutex);

put:
	scsi_host_put(target->scsi_host);
	अगर (ret < 0) अणु
		/*
		 * If a call to srp_हटाओ_target() has not been scheduled,
		 * drop the network namespace reference now that was obtained
		 * earlier in this function.
		 */
		अगर (target->state != SRP_TARGET_REMOVED)
			kobj_ns_drop(KOBJ_NS_TYPE_NET, target->net);
		scsi_host_put(target->scsi_host);
	पूर्ण

	वापस ret;

err_disconnect:
	srp_disconnect_target(target);

मुक्त_ch:
	क्रम (i = 0; i < target->ch_count; i++) अणु
		ch = &target->ch[i];
		srp_मुक्त_ch_ib(target, ch);
		srp_मुक्त_req_data(target, ch);
	पूर्ण

	kमुक्त(target->ch);
	जाओ out;
पूर्ण

अटल DEVICE_ATTR(add_target, S_IWUSR, शून्य, srp_create_target);

अटल sमाप_प्रकार show_ibdev(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा srp_host *host = container_of(dev, काष्ठा srp_host, dev);

	वापस sysfs_emit(buf, "%s\n", dev_name(&host->srp_dev->dev->dev));
पूर्ण

अटल DEVICE_ATTR(ibdev, S_IRUGO, show_ibdev, शून्य);

अटल sमाप_प्रकार show_port(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा srp_host *host = container_of(dev, काष्ठा srp_host, dev);

	वापस sysfs_emit(buf, "%d\n", host->port);
पूर्ण

अटल DEVICE_ATTR(port, S_IRUGO, show_port, शून्य);

अटल काष्ठा srp_host *srp_add_port(काष्ठा srp_device *device, u8 port)
अणु
	काष्ठा srp_host *host;

	host = kzalloc(माप *host, GFP_KERNEL);
	अगर (!host)
		वापस शून्य;

	INIT_LIST_HEAD(&host->target_list);
	spin_lock_init(&host->target_lock);
	init_completion(&host->released);
	mutex_init(&host->add_target_mutex);
	host->srp_dev = device;
	host->port = port;

	host->dev.class = &srp_class;
	host->dev.parent = device->dev->dev.parent;
	dev_set_name(&host->dev, "srp-%s-%d", dev_name(&device->dev->dev),
		     port);

	अगर (device_रेजिस्टर(&host->dev))
		जाओ मुक्त_host;
	अगर (device_create_file(&host->dev, &dev_attr_add_target))
		जाओ err_class;
	अगर (device_create_file(&host->dev, &dev_attr_ibdev))
		जाओ err_class;
	अगर (device_create_file(&host->dev, &dev_attr_port))
		जाओ err_class;

	वापस host;

err_class:
	device_unरेजिस्टर(&host->dev);

मुक्त_host:
	kमुक्त(host);

	वापस शून्य;
पूर्ण

अटल व्योम srp_नाम_dev(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा srp_device *srp_dev = client_data;
	काष्ठा srp_host *host, *पंचांगp_host;

	list_क्रम_each_entry_safe(host, पंचांगp_host, &srp_dev->dev_list, list) अणु
		अक्षर name[IB_DEVICE_NAME_MAX + 8];

		snम_लिखो(name, माप(name), "srp-%s-%d",
			 dev_name(&device->dev), host->port);
		device_नाम(&host->dev, name);
	पूर्ण
पूर्ण

अटल पूर्णांक srp_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा srp_device *srp_dev;
	काष्ठा ib_device_attr *attr = &device->attrs;
	काष्ठा srp_host *host;
	पूर्णांक mr_page_shअगरt;
	अचिन्हित पूर्णांक p;
	u64 max_pages_per_mr;
	अचिन्हित पूर्णांक flags = 0;

	srp_dev = kzalloc(माप(*srp_dev), GFP_KERNEL);
	अगर (!srp_dev)
		वापस -ENOMEM;

	/*
	 * Use the smallest page size supported by the HCA, करोwn to a
	 * minimum of 4096 bytes. We're unlikely to build large sglists
	 * out of smaller entries.
	 */
	mr_page_shअगरt		= max(12, ffs(attr->page_size_cap) - 1);
	srp_dev->mr_page_size	= 1 << mr_page_shअगरt;
	srp_dev->mr_page_mask	= ~((u64) srp_dev->mr_page_size - 1);
	max_pages_per_mr	= attr->max_mr_size;
	करो_भाग(max_pages_per_mr, srp_dev->mr_page_size);
	pr_debug("%s: %llu / %u = %llu <> %u\n", __func__,
		 attr->max_mr_size, srp_dev->mr_page_size,
		 max_pages_per_mr, SRP_MAX_PAGES_PER_MR);
	srp_dev->max_pages_per_mr = min_t(u64, SRP_MAX_PAGES_PER_MR,
					  max_pages_per_mr);

	srp_dev->has_fr = (attr->device_cap_flags &
			   IB_DEVICE_MEM_MGT_EXTENSIONS);
	अगर (!never_रेजिस्टर && !srp_dev->has_fr)
		dev_warn(&device->dev, "FR is not supported\n");
	अन्यथा अगर (!never_रेजिस्टर &&
		 attr->max_mr_size >= 2 * srp_dev->mr_page_size)
		srp_dev->use_fast_reg = srp_dev->has_fr;

	अगर (never_रेजिस्टर || !रेजिस्टर_always || !srp_dev->has_fr)
		flags |= IB_PD_UNSAFE_GLOBAL_RKEY;

	अगर (srp_dev->use_fast_reg) अणु
		srp_dev->max_pages_per_mr =
			min_t(u32, srp_dev->max_pages_per_mr,
			      attr->max_fast_reg_page_list_len);
	पूर्ण
	srp_dev->mr_max_size	= srp_dev->mr_page_size *
				   srp_dev->max_pages_per_mr;
	pr_debug("%s: mr_page_shift = %d, device->max_mr_size = %#llx, device->max_fast_reg_page_list_len = %u, max_pages_per_mr = %d, mr_max_size = %#x\n",
		 dev_name(&device->dev), mr_page_shअगरt, attr->max_mr_size,
		 attr->max_fast_reg_page_list_len,
		 srp_dev->max_pages_per_mr, srp_dev->mr_max_size);

	INIT_LIST_HEAD(&srp_dev->dev_list);

	srp_dev->dev = device;
	srp_dev->pd  = ib_alloc_pd(device, flags);
	अगर (IS_ERR(srp_dev->pd)) अणु
		पूर्णांक ret = PTR_ERR(srp_dev->pd);

		kमुक्त(srp_dev);
		वापस ret;
	पूर्ण

	अगर (flags & IB_PD_UNSAFE_GLOBAL_RKEY) अणु
		srp_dev->global_rkey = srp_dev->pd->unsafe_global_rkey;
		WARN_ON_ONCE(srp_dev->global_rkey == 0);
	पूर्ण

	rdma_क्रम_each_port (device, p) अणु
		host = srp_add_port(srp_dev, p);
		अगर (host)
			list_add_tail(&host->list, &srp_dev->dev_list);
	पूर्ण

	ib_set_client_data(device, &srp_client, srp_dev);
	वापस 0;
पूर्ण

अटल व्योम srp_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा srp_device *srp_dev;
	काष्ठा srp_host *host, *पंचांगp_host;
	काष्ठा srp_target_port *target;

	srp_dev = client_data;

	list_क्रम_each_entry_safe(host, पंचांगp_host, &srp_dev->dev_list, list) अणु
		device_unरेजिस्टर(&host->dev);
		/*
		 * Wait क्रम the sysfs entry to go away, so that no new
		 * target ports can be created.
		 */
		रुको_क्रम_completion(&host->released);

		/*
		 * Remove all target ports.
		 */
		spin_lock(&host->target_lock);
		list_क्रम_each_entry(target, &host->target_list, list)
			srp_queue_हटाओ_work(target);
		spin_unlock(&host->target_lock);

		/*
		 * Wait क्रम tl_err and target port removal tasks.
		 */
		flush_workqueue(प्रणाली_दीर्घ_wq);
		flush_workqueue(srp_हटाओ_wq);

		kमुक्त(host);
	पूर्ण

	ib_dealloc_pd(srp_dev->pd);

	kमुक्त(srp_dev);
पूर्ण

अटल काष्ठा srp_function_ढाँचा ib_srp_transport_functions = अणु
	.has_rport_state	 = true,
	.reset_समयr_अगर_blocked	 = true,
	.reconnect_delay	 = &srp_reconnect_delay,
	.fast_io_fail_पंचांगo	 = &srp_fast_io_fail_पंचांगo,
	.dev_loss_पंचांगo		 = &srp_dev_loss_पंचांगo,
	.reconnect		 = srp_rport_reconnect,
	.rport_delete		 = srp_rport_delete,
	.terminate_rport_io	 = srp_terminate_io,
पूर्ण;

अटल पूर्णांक __init srp_init_module(व्योम)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(माप(काष्ठा srp_imm_buf) != 4);
	BUILD_BUG_ON(माप(काष्ठा srp_login_req) != 64);
	BUILD_BUG_ON(माप(काष्ठा srp_login_req_rdma) != 56);
	BUILD_BUG_ON(माप(काष्ठा srp_cmd) != 48);

	अगर (srp_sg_tablesize) अणु
		pr_warn("srp_sg_tablesize is deprecated, please use cmd_sg_entries\n");
		अगर (!cmd_sg_entries)
			cmd_sg_entries = srp_sg_tablesize;
	पूर्ण

	अगर (!cmd_sg_entries)
		cmd_sg_entries = SRP_DEF_SG_TABLESIZE;

	अगर (cmd_sg_entries > 255) अणु
		pr_warn("Clamping cmd_sg_entries to 255\n");
		cmd_sg_entries = 255;
	पूर्ण

	अगर (!indirect_sg_entries)
		indirect_sg_entries = cmd_sg_entries;
	अन्यथा अगर (indirect_sg_entries < cmd_sg_entries) अणु
		pr_warn("Bumping up indirect_sg_entries to match cmd_sg_entries (%u)\n",
			cmd_sg_entries);
		indirect_sg_entries = cmd_sg_entries;
	पूर्ण

	अगर (indirect_sg_entries > SG_MAX_SEGMENTS) अणु
		pr_warn("Clamping indirect_sg_entries to %u\n",
			SG_MAX_SEGMENTS);
		indirect_sg_entries = SG_MAX_SEGMENTS;
	पूर्ण

	srp_हटाओ_wq = create_workqueue("srp_remove");
	अगर (!srp_हटाओ_wq) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = -ENOMEM;
	ib_srp_transport_ढाँचा =
		srp_attach_transport(&ib_srp_transport_functions);
	अगर (!ib_srp_transport_ढाँचा)
		जाओ destroy_wq;

	ret = class_रेजिस्टर(&srp_class);
	अगर (ret) अणु
		pr_err("couldn't register class infiniband_srp\n");
		जाओ release_tr;
	पूर्ण

	ib_sa_रेजिस्टर_client(&srp_sa_client);

	ret = ib_रेजिस्टर_client(&srp_client);
	अगर (ret) अणु
		pr_err("couldn't register IB client\n");
		जाओ unreg_sa;
	पूर्ण

out:
	वापस ret;

unreg_sa:
	ib_sa_unरेजिस्टर_client(&srp_sa_client);
	class_unरेजिस्टर(&srp_class);

release_tr:
	srp_release_transport(ib_srp_transport_ढाँचा);

destroy_wq:
	destroy_workqueue(srp_हटाओ_wq);
	जाओ out;
पूर्ण

अटल व्योम __निकास srp_cleanup_module(व्योम)
अणु
	ib_unरेजिस्टर_client(&srp_client);
	ib_sa_unरेजिस्टर_client(&srp_sa_client);
	class_unरेजिस्टर(&srp_class);
	srp_release_transport(ib_srp_transport_ढाँचा);
	destroy_workqueue(srp_हटाओ_wq);
पूर्ण

module_init(srp_init_module);
module_निकास(srp_cleanup_module);
