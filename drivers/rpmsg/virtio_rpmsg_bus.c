<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Virtio-based remote processor messaging bus
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/dma-mapping.h>
#समावेश <linux/idr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/rpmsg/byteorder.h>
#समावेश <linux/rpmsg/ns.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/रुको.h>

#समावेश "rpmsg_internal.h"

/**
 * काष्ठा virtproc_info - भव remote processor state
 * @vdev:	the virtio device
 * @rvq:	rx virtqueue
 * @svq:	tx virtqueue
 * @rbufs:	kernel address of rx buffers
 * @sbufs:	kernel address of tx buffers
 * @num_bufs:	total number of buffers क्रम rx and tx
 * @buf_size:   size of one rx or tx buffer
 * @last_sbuf:	index of last tx buffer used
 * @bufs_dma:	dma base addr of the buffers
 * @tx_lock:	protects svq, sbufs and sleepers, to allow concurrent senders.
 *		sending a message might require waking up a करोzing remote
 *		processor, which involves sleeping, hence the mutex.
 * @endpoपूर्णांकs:	idr of local endpoपूर्णांकs, allows fast retrieval
 * @endpoपूर्णांकs_lock: lock of the endpoपूर्णांकs set
 * @sendq:	रुको queue of sending contexts रुकोing क्रम a tx buffers
 * @sleepers:	number of senders that are रुकोing क्रम a tx buffer
 *
 * This काष्ठाure stores the rpmsg state of a given virtio remote processor
 * device (there might be several virtio proc devices क्रम each physical
 * remote processor).
 */
काष्ठा virtproc_info अणु
	काष्ठा virtio_device *vdev;
	काष्ठा virtqueue *rvq, *svq;
	व्योम *rbufs, *sbufs;
	अचिन्हित पूर्णांक num_bufs;
	अचिन्हित पूर्णांक buf_size;
	पूर्णांक last_sbuf;
	dma_addr_t bufs_dma;
	काष्ठा mutex tx_lock;
	काष्ठा idr endpoपूर्णांकs;
	काष्ठा mutex endpoपूर्णांकs_lock;
	रुको_queue_head_t sendq;
	atomic_t sleepers;
पूर्ण;

/* The feature biपंचांगap क्रम virtio rpmsg */
#घोषणा VIRTIO_RPMSG_F_NS	0 /* RP supports name service notअगरications */

/**
 * काष्ठा rpmsg_hdr - common header क्रम all rpmsg messages
 * @src: source address
 * @dst: destination address
 * @reserved: reserved क्रम future use
 * @len: length of payload (in bytes)
 * @flags: message flags
 * @data: @len bytes of message payload data
 *
 * Every message sent(/received) on the rpmsg bus begins with this header.
 */
काष्ठा rpmsg_hdr अणु
	__rpmsg32 src;
	__rpmsg32 dst;
	__rpmsg32 reserved;
	__rpmsg16 len;
	__rpmsg16 flags;
	u8 data[];
पूर्ण __packed;


/**
 * काष्ठा virtio_rpmsg_channel - rpmsg channel descriptor
 * @rpdev: the rpmsg channel device
 * @vrp: the virtio remote processor device this channel beदीर्घs to
 *
 * This काष्ठाure stores the channel that links the rpmsg device to the virtio
 * remote processor device.
 */
काष्ठा virtio_rpmsg_channel अणु
	काष्ठा rpmsg_device rpdev;

	काष्ठा virtproc_info *vrp;
पूर्ण;

#घोषणा to_virtio_rpmsg_channel(_rpdev) \
	container_of(_rpdev, काष्ठा virtio_rpmsg_channel, rpdev)

/*
 * We're allocating buffers of 512 bytes each क्रम communications. The
 * number of buffers will be computed from the number of buffers supported
 * by the vring, upto a maximum of 512 buffers (256 in each direction).
 *
 * Each buffer will have 16 bytes क्रम the msg header and 496 bytes क्रम
 * the payload.
 *
 * This will utilize a maximum total space of 256KB क्रम the buffers.
 *
 * We might also want to add support क्रम user-provided buffers in समय.
 * This will allow bigger buffer size flexibility, and can also be used
 * to achieve zero-copy messaging.
 *
 * Note that these numbers are purely a decision of this driver - we
 * can change this without changing anything in the firmware of the remote
 * processor.
 */
#घोषणा MAX_RPMSG_NUM_BUFS	(512)
#घोषणा MAX_RPMSG_BUF_SIZE	(512)

/*
 * Local addresses are dynamically allocated on-demand.
 * We करो not dynamically assign addresses from the low 1024 range,
 * in order to reserve that address range क्रम predefined services.
 */
#घोषणा RPMSG_RESERVED_ADDRESSES	(1024)

अटल व्योम virtio_rpmsg_destroy_ept(काष्ठा rpmsg_endpoपूर्णांक *ept);
अटल पूर्णांक virtio_rpmsg_send(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len);
अटल पूर्णांक virtio_rpmsg_sendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len,
			       u32 dst);
अटल पूर्णांक virtio_rpmsg_send_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src,
					u32 dst, व्योम *data, पूर्णांक len);
अटल पूर्णांक virtio_rpmsg_trysend(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len);
अटल पूर्णांक virtio_rpmsg_trysendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data,
				  पूर्णांक len, u32 dst);
अटल पूर्णांक virtio_rpmsg_trysend_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src,
					   u32 dst, व्योम *data, पूर्णांक len);
अटल काष्ठा rpmsg_device *__rpmsg_create_channel(काष्ठा virtproc_info *vrp,
						   काष्ठा rpmsg_channel_info *chinfo);

अटल स्थिर काष्ठा rpmsg_endpoपूर्णांक_ops virtio_endpoपूर्णांक_ops = अणु
	.destroy_ept = virtio_rpmsg_destroy_ept,
	.send = virtio_rpmsg_send,
	.sendto = virtio_rpmsg_sendto,
	.send_offchannel = virtio_rpmsg_send_offchannel,
	.trysend = virtio_rpmsg_trysend,
	.trysendto = virtio_rpmsg_trysendto,
	.trysend_offchannel = virtio_rpmsg_trysend_offchannel,
पूर्ण;

/**
 * rpmsg_sg_init - initialize scatterlist according to cpu address location
 * @sg: scatterlist to fill
 * @cpu_addr: भव address of the buffer
 * @len: buffer length
 *
 * An पूर्णांकernal function filling scatterlist according to भव address
 * location (in vदो_स्मृति or in kernel).
 */
अटल व्योम
rpmsg_sg_init(काष्ठा scatterlist *sg, व्योम *cpu_addr, अचिन्हित पूर्णांक len)
अणु
	अगर (is_vदो_स्मृति_addr(cpu_addr)) अणु
		sg_init_table(sg, 1);
		sg_set_page(sg, vदो_स्मृति_to_page(cpu_addr), len,
			    offset_in_page(cpu_addr));
	पूर्ण अन्यथा अणु
		WARN_ON(!virt_addr_valid(cpu_addr));
		sg_init_one(sg, cpu_addr, len);
	पूर्ण
पूर्ण

/**
 * __ept_release() - deallocate an rpmsg endpoपूर्णांक
 * @kref: the ept's reference count
 *
 * This function deallocates an ept, and is invoked when its @kref refcount
 * drops to zero.
 *
 * Never invoke this function directly!
 */
अटल व्योम __ept_release(काष्ठा kref *kref)
अणु
	काष्ठा rpmsg_endpoपूर्णांक *ept = container_of(kref, काष्ठा rpmsg_endpoपूर्णांक,
						  refcount);
	/*
	 * At this poपूर्णांक no one holds a reference to ept anymore,
	 * so we can directly मुक्त it
	 */
	kमुक्त(ept);
पूर्ण

/* क्रम more info, see below करोcumentation of rpmsg_create_ept() */
अटल काष्ठा rpmsg_endpoपूर्णांक *__rpmsg_create_ept(काष्ठा virtproc_info *vrp,
						 काष्ठा rpmsg_device *rpdev,
						 rpmsg_rx_cb_t cb,
						 व्योम *priv, u32 addr)
अणु
	पूर्णांक id_min, id_max, id;
	काष्ठा rpmsg_endpoपूर्णांक *ept;
	काष्ठा device *dev = rpdev ? &rpdev->dev : &vrp->vdev->dev;

	ept = kzalloc(माप(*ept), GFP_KERNEL);
	अगर (!ept)
		वापस शून्य;

	kref_init(&ept->refcount);
	mutex_init(&ept->cb_lock);

	ept->rpdev = rpdev;
	ept->cb = cb;
	ept->priv = priv;
	ept->ops = &virtio_endpoपूर्णांक_ops;

	/* करो we need to allocate a local address ? */
	अगर (addr == RPMSG_ADDR_ANY) अणु
		id_min = RPMSG_RESERVED_ADDRESSES;
		id_max = 0;
	पूर्ण अन्यथा अणु
		id_min = addr;
		id_max = addr + 1;
	पूर्ण

	mutex_lock(&vrp->endpoपूर्णांकs_lock);

	/* bind the endpoपूर्णांक to an rpmsg address (and allocate one अगर needed) */
	id = idr_alloc(&vrp->endpoपूर्णांकs, ept, id_min, id_max, GFP_KERNEL);
	अगर (id < 0) अणु
		dev_err(dev, "idr_alloc failed: %d\n", id);
		जाओ मुक्त_ept;
	पूर्ण
	ept->addr = id;

	mutex_unlock(&vrp->endpoपूर्णांकs_lock);

	वापस ept;

मुक्त_ept:
	mutex_unlock(&vrp->endpoपूर्णांकs_lock);
	kref_put(&ept->refcount, __ept_release);
	वापस शून्य;
पूर्ण

अटल काष्ठा rpmsg_device *virtio_rpmsg_create_channel(काष्ठा rpmsg_device *rpdev,
							काष्ठा rpmsg_channel_info *chinfo)
अणु
	काष्ठा virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);
	काष्ठा virtproc_info *vrp = vch->vrp;

	वापस __rpmsg_create_channel(vrp, chinfo);
पूर्ण

अटल पूर्णांक virtio_rpmsg_release_channel(काष्ठा rpmsg_device *rpdev,
					काष्ठा rpmsg_channel_info *chinfo)
अणु
	काष्ठा virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);
	काष्ठा virtproc_info *vrp = vch->vrp;

	वापस rpmsg_unरेजिस्टर_device(&vrp->vdev->dev, chinfo);
पूर्ण

अटल काष्ठा rpmsg_endpoपूर्णांक *virtio_rpmsg_create_ept(काष्ठा rpmsg_device *rpdev,
						      rpmsg_rx_cb_t cb,
						      व्योम *priv,
						      काष्ठा rpmsg_channel_info chinfo)
अणु
	काष्ठा virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);

	वापस __rpmsg_create_ept(vch->vrp, rpdev, cb, priv, chinfo.src);
पूर्ण

/**
 * __rpmsg_destroy_ept() - destroy an existing rpmsg endpoपूर्णांक
 * @vrp: virtproc which owns this ept
 * @ept: endpoing to destroy
 *
 * An पूर्णांकernal function which destroy an ept without assuming it is
 * bound to an rpmsg channel. This is needed क्रम handling the पूर्णांकernal
 * name service endpoपूर्णांक, which isn't bound to an rpmsg channel.
 * See also __rpmsg_create_ept().
 */
अटल व्योम
__rpmsg_destroy_ept(काष्ठा virtproc_info *vrp, काष्ठा rpmsg_endpoपूर्णांक *ept)
अणु
	/* make sure new inbound messages can't find this ept anymore */
	mutex_lock(&vrp->endpoपूर्णांकs_lock);
	idr_हटाओ(&vrp->endpoपूर्णांकs, ept->addr);
	mutex_unlock(&vrp->endpoपूर्णांकs_lock);

	/* make sure in-flight inbound messages won't invoke cb anymore */
	mutex_lock(&ept->cb_lock);
	ept->cb = शून्य;
	mutex_unlock(&ept->cb_lock);

	kref_put(&ept->refcount, __ept_release);
पूर्ण

अटल व्योम virtio_rpmsg_destroy_ept(काष्ठा rpmsg_endpoपूर्णांक *ept)
अणु
	काष्ठा virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(ept->rpdev);

	__rpmsg_destroy_ept(vch->vrp, ept);
पूर्ण

अटल पूर्णांक virtio_rpmsg_announce_create(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);
	काष्ठा virtproc_info *vrp = vch->vrp;
	काष्ठा device *dev = &rpdev->dev;
	पूर्णांक err = 0;

	/* need to tell remote processor's name service about this channel ? */
	अगर (rpdev->announce && rpdev->ept &&
	    virtio_has_feature(vrp->vdev, VIRTIO_RPMSG_F_NS)) अणु
		काष्ठा rpmsg_ns_msg nsm;

		म_नकलन(nsm.name, rpdev->id.name, RPMSG_NAME_SIZE);
		nsm.addr = cpu_to_rpmsg32(rpdev, rpdev->ept->addr);
		nsm.flags = cpu_to_rpmsg32(rpdev, RPMSG_NS_CREATE);

		err = rpmsg_sendto(rpdev->ept, &nsm, माप(nsm), RPMSG_NS_ADDR);
		अगर (err)
			dev_err(dev, "failed to announce service %d\n", err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक virtio_rpmsg_announce_destroy(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);
	काष्ठा virtproc_info *vrp = vch->vrp;
	काष्ठा device *dev = &rpdev->dev;
	पूर्णांक err = 0;

	/* tell remote processor's name service we're removing this channel */
	अगर (rpdev->announce && rpdev->ept &&
	    virtio_has_feature(vrp->vdev, VIRTIO_RPMSG_F_NS)) अणु
		काष्ठा rpmsg_ns_msg nsm;

		म_नकलन(nsm.name, rpdev->id.name, RPMSG_NAME_SIZE);
		nsm.addr = cpu_to_rpmsg32(rpdev, rpdev->ept->addr);
		nsm.flags = cpu_to_rpmsg32(rpdev, RPMSG_NS_DESTROY);

		err = rpmsg_sendto(rpdev->ept, &nsm, माप(nsm), RPMSG_NS_ADDR);
		अगर (err)
			dev_err(dev, "failed to announce service %d\n", err);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा rpmsg_device_ops virtio_rpmsg_ops = अणु
	.create_channel = virtio_rpmsg_create_channel,
	.release_channel = virtio_rpmsg_release_channel,
	.create_ept = virtio_rpmsg_create_ept,
	.announce_create = virtio_rpmsg_announce_create,
	.announce_destroy = virtio_rpmsg_announce_destroy,
पूर्ण;

अटल व्योम virtio_rpmsg_release_device(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_device *rpdev = to_rpmsg_device(dev);
	काष्ठा virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);

	kमुक्त(vch);
पूर्ण

/*
 * create an rpmsg channel using its name and address info.
 * this function will be used to create both अटल and dynamic
 * channels.
 */
अटल काष्ठा rpmsg_device *__rpmsg_create_channel(काष्ठा virtproc_info *vrp,
						   काष्ठा rpmsg_channel_info *chinfo)
अणु
	काष्ठा virtio_rpmsg_channel *vch;
	काष्ठा rpmsg_device *rpdev;
	काष्ठा device *पंचांगp, *dev = &vrp->vdev->dev;
	पूर्णांक ret;

	/* make sure a similar channel करोesn't alपढ़ोy exist */
	पंचांगp = rpmsg_find_device(dev, chinfo);
	अगर (पंचांगp) अणु
		/* decrement the matched device's refcount back */
		put_device(पंचांगp);
		dev_err(dev, "channel %s:%x:%x already exist\n",
				chinfo->name, chinfo->src, chinfo->dst);
		वापस शून्य;
	पूर्ण

	vch = kzalloc(माप(*vch), GFP_KERNEL);
	अगर (!vch)
		वापस शून्य;

	/* Link the channel to our vrp */
	vch->vrp = vrp;

	/* Assign खुला inक्रमmation to the rpmsg_device */
	rpdev = &vch->rpdev;
	rpdev->src = chinfo->src;
	rpdev->dst = chinfo->dst;
	rpdev->ops = &virtio_rpmsg_ops;
	rpdev->little_endian = virtio_is_little_endian(vrp->vdev);

	/*
	 * rpmsg server channels has predefined local address (क्रम now),
	 * and their existence needs to be announced remotely
	 */
	rpdev->announce = rpdev->src != RPMSG_ADDR_ANY;

	म_नकलन(rpdev->id.name, chinfo->name, RPMSG_NAME_SIZE);

	rpdev->dev.parent = &vrp->vdev->dev;
	rpdev->dev.release = virtio_rpmsg_release_device;
	ret = rpmsg_रेजिस्टर_device(rpdev);
	अगर (ret)
		वापस शून्य;

	वापस rpdev;
पूर्ण

/* super simple buffer "allocator" that is just enough क्रम now */
अटल व्योम *get_a_tx_buf(काष्ठा virtproc_info *vrp)
अणु
	अचिन्हित पूर्णांक len;
	व्योम *ret;

	/* support multiple concurrent senders */
	mutex_lock(&vrp->tx_lock);

	/*
	 * either pick the next unused tx buffer
	 * (half of our buffers are used क्रम sending messages)
	 */
	अगर (vrp->last_sbuf < vrp->num_bufs / 2)
		ret = vrp->sbufs + vrp->buf_size * vrp->last_sbuf++;
	/* or recycle a used one */
	अन्यथा
		ret = virtqueue_get_buf(vrp->svq, &len);

	mutex_unlock(&vrp->tx_lock);

	वापस ret;
पूर्ण

/**
 * rpmsg_upref_sleepers() - enable "tx-complete" पूर्णांकerrupts, अगर needed
 * @vrp: भव remote processor state
 *
 * This function is called beक्रमe a sender is blocked, रुकोing क्रम
 * a tx buffer to become available.
 *
 * If we alपढ़ोy have blocking senders, this function merely increases
 * the "sleepers" reference count, and निकासs.
 *
 * Otherwise, अगर this is the first sender to block, we also enable
 * virtio's tx callbacks, so we'd be immediately notअगरied when a tx
 * buffer is consumed (we rely on virtio's tx callback in order
 * to wake up sleeping senders as soon as a tx buffer is used by the
 * remote processor).
 */
अटल व्योम rpmsg_upref_sleepers(काष्ठा virtproc_info *vrp)
अणु
	/* support multiple concurrent senders */
	mutex_lock(&vrp->tx_lock);

	/* are we the first sleeping context रुकोing क्रम tx buffers ? */
	अगर (atomic_inc_वापस(&vrp->sleepers) == 1)
		/* enable "tx-complete" पूर्णांकerrupts beक्रमe करोzing off */
		virtqueue_enable_cb(vrp->svq);

	mutex_unlock(&vrp->tx_lock);
पूर्ण

/**
 * rpmsg_करोwnref_sleepers() - disable "tx-complete" पूर्णांकerrupts, अगर needed
 * @vrp: भव remote processor state
 *
 * This function is called after a sender, that रुकोed क्रम a tx buffer
 * to become available, is unblocked.
 *
 * If we still have blocking senders, this function merely decreases
 * the "sleepers" reference count, and निकासs.
 *
 * Otherwise, अगर there are no more blocking senders, we also disable
 * virtio's tx callbacks, to aव्योम the overhead incurred with handling
 * those (now redundant) पूर्णांकerrupts.
 */
अटल व्योम rpmsg_करोwnref_sleepers(काष्ठा virtproc_info *vrp)
अणु
	/* support multiple concurrent senders */
	mutex_lock(&vrp->tx_lock);

	/* are we the last sleeping context रुकोing क्रम tx buffers ? */
	अगर (atomic_dec_and_test(&vrp->sleepers))
		/* disable "tx-complete" पूर्णांकerrupts */
		virtqueue_disable_cb(vrp->svq);

	mutex_unlock(&vrp->tx_lock);
पूर्ण

/**
 * rpmsg_send_offchannel_raw() - send a message across to the remote processor
 * @rpdev: the rpmsg channel
 * @src: source address
 * @dst: destination address
 * @data: payload of message
 * @len: length of payload
 * @रुको: indicates whether caller should block in हाल no TX buffers available
 *
 * This function is the base implementation क्रम all of the rpmsg sending API.
 *
 * It will send @data of length @len to @dst, and say it's from @src. The
 * message will be sent to the remote processor which the @rpdev channel
 * beदीर्घs to.
 *
 * The message is sent using one of the TX buffers that are available क्रम
 * communication with this remote processor.
 *
 * If @रुको is true, the caller will be blocked until either a TX buffer is
 * available, or 15 seconds elapses (we करोn't want callers to
 * sleep indefinitely due to misbehaving remote processors), and in that
 * हाल -ERESTARTSYS is वापसed. The number '15' itself was picked
 * arbitrarily; there's little poपूर्णांक in asking drivers to provide a समयout
 * value themselves.
 *
 * Otherwise, अगर @रुको is false, and there are no TX buffers available,
 * the function will immediately fail, and -ENOMEM will be वापसed.
 *
 * Normally drivers shouldn't use this function directly; instead, drivers
 * should use the appropriate rpmsg_अणुtryपूर्णsendअणुto, _offchannelपूर्ण API
 * (see include/linux/rpmsg.h).
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
अटल पूर्णांक rpmsg_send_offchannel_raw(काष्ठा rpmsg_device *rpdev,
				     u32 src, u32 dst,
				     व्योम *data, पूर्णांक len, bool रुको)
अणु
	काष्ठा virtio_rpmsg_channel *vch = to_virtio_rpmsg_channel(rpdev);
	काष्ठा virtproc_info *vrp = vch->vrp;
	काष्ठा device *dev = &rpdev->dev;
	काष्ठा scatterlist sg;
	काष्ठा rpmsg_hdr *msg;
	पूर्णांक err;

	/* bcasting isn't allowed */
	अगर (src == RPMSG_ADDR_ANY || dst == RPMSG_ADDR_ANY) अणु
		dev_err(dev, "invalid addr (src 0x%x, dst 0x%x)\n", src, dst);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We currently use fixed-sized buffers, and thereक्रमe the payload
	 * length is limited.
	 *
	 * One of the possible improvements here is either to support
	 * user-provided buffers (and then we can also support zero-copy
	 * messaging), or to improve the buffer allocator, to support
	 * variable-length buffer sizes.
	 */
	अगर (len > vrp->buf_size - माप(काष्ठा rpmsg_hdr)) अणु
		dev_err(dev, "message is too big (%d)\n", len);
		वापस -EMSGSIZE;
	पूर्ण

	/* grab a buffer */
	msg = get_a_tx_buf(vrp);
	अगर (!msg && !रुको)
		वापस -ENOMEM;

	/* no मुक्त buffer ? रुको क्रम one (but bail after 15 seconds) */
	जबतक (!msg) अणु
		/* enable "tx-complete" पूर्णांकerrupts, अगर not alपढ़ोy enabled */
		rpmsg_upref_sleepers(vrp);

		/*
		 * sleep until a मुक्त buffer is available or 15 secs elapse.
		 * the समयout period is not configurable because there's
		 * little poपूर्णांक in asking drivers to specअगरy that.
		 * अगर later this happens to be required, it'd be easy to add.
		 */
		err = रुको_event_पूर्णांकerruptible_समयout(vrp->sendq,
					(msg = get_a_tx_buf(vrp)),
					msecs_to_jअगरfies(15000));

		/* disable "tx-complete" पूर्णांकerrupts अगर we're the last sleeper */
		rpmsg_करोwnref_sleepers(vrp);

		/* समयout ? */
		अगर (!err) अणु
			dev_err(dev, "timeout waiting for a tx buffer\n");
			वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण

	msg->len = cpu_to_rpmsg16(rpdev, len);
	msg->flags = 0;
	msg->src = cpu_to_rpmsg32(rpdev, src);
	msg->dst = cpu_to_rpmsg32(rpdev, dst);
	msg->reserved = 0;
	स_नकल(msg->data, data, len);

	dev_dbg(dev, "TX From 0x%x, To 0x%x, Len %d, Flags %d, Reserved %d\n",
		src, dst, len, msg->flags, msg->reserved);
#अगर defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("rpmsg_virtio TX: ", DUMP_PREFIX_NONE, 16, 1,
			 msg, माप(*msg) + len, true);
#पूर्ण_अगर

	rpmsg_sg_init(&sg, msg, माप(*msg) + len);

	mutex_lock(&vrp->tx_lock);

	/* add message to the remote processor's virtqueue */
	err = virtqueue_add_outbuf(vrp->svq, &sg, 1, msg, GFP_KERNEL);
	अगर (err) अणु
		/*
		 * need to reclaim the buffer here, otherwise it's lost
		 * (memory won't leak, but rpmsg won't use it again क्रम TX).
		 * this will रुको क्रम a buffer management overhaul.
		 */
		dev_err(dev, "virtqueue_add_outbuf failed: %d\n", err);
		जाओ out;
	पूर्ण

	/* tell the remote processor it has a pending message to पढ़ो */
	virtqueue_kick(vrp->svq);
out:
	mutex_unlock(&vrp->tx_lock);
	वापस err;
पूर्ण

अटल पूर्णांक virtio_rpmsg_send(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	काष्ठा rpmsg_device *rpdev = ept->rpdev;
	u32 src = ept->addr, dst = rpdev->dst;

	वापस rpmsg_send_offchannel_raw(rpdev, src, dst, data, len, true);
पूर्ण

अटल पूर्णांक virtio_rpmsg_sendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len,
			       u32 dst)
अणु
	काष्ठा rpmsg_device *rpdev = ept->rpdev;
	u32 src = ept->addr;

	वापस rpmsg_send_offchannel_raw(rpdev, src, dst, data, len, true);
पूर्ण

अटल पूर्णांक virtio_rpmsg_send_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src,
					u32 dst, व्योम *data, पूर्णांक len)
अणु
	काष्ठा rpmsg_device *rpdev = ept->rpdev;

	वापस rpmsg_send_offchannel_raw(rpdev, src, dst, data, len, true);
पूर्ण

अटल पूर्णांक virtio_rpmsg_trysend(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len)
अणु
	काष्ठा rpmsg_device *rpdev = ept->rpdev;
	u32 src = ept->addr, dst = rpdev->dst;

	वापस rpmsg_send_offchannel_raw(rpdev, src, dst, data, len, false);
पूर्ण

अटल पूर्णांक virtio_rpmsg_trysendto(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data,
				  पूर्णांक len, u32 dst)
अणु
	काष्ठा rpmsg_device *rpdev = ept->rpdev;
	u32 src = ept->addr;

	वापस rpmsg_send_offchannel_raw(rpdev, src, dst, data, len, false);
पूर्ण

अटल पूर्णांक virtio_rpmsg_trysend_offchannel(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src,
					   u32 dst, व्योम *data, पूर्णांक len)
अणु
	काष्ठा rpmsg_device *rpdev = ept->rpdev;

	वापस rpmsg_send_offchannel_raw(rpdev, src, dst, data, len, false);
पूर्ण

अटल पूर्णांक rpmsg_recv_single(काष्ठा virtproc_info *vrp, काष्ठा device *dev,
			     काष्ठा rpmsg_hdr *msg, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rpmsg_endpoपूर्णांक *ept;
	काष्ठा scatterlist sg;
	bool little_endian = virtio_is_little_endian(vrp->vdev);
	अचिन्हित पूर्णांक msg_len = __rpmsg16_to_cpu(little_endian, msg->len);
	पूर्णांक err;

	dev_dbg(dev, "From: 0x%x, To: 0x%x, Len: %d, Flags: %d, Reserved: %d\n",
		__rpmsg32_to_cpu(little_endian, msg->src),
		__rpmsg32_to_cpu(little_endian, msg->dst), msg_len,
		__rpmsg16_to_cpu(little_endian, msg->flags),
		__rpmsg32_to_cpu(little_endian, msg->reserved));
#अगर defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("rpmsg_virtio RX: ", DUMP_PREFIX_NONE, 16, 1,
			 msg, माप(*msg) + msg_len, true);
#पूर्ण_अगर

	/*
	 * We currently use fixed-sized buffers, so trivially sanitize
	 * the reported payload length.
	 */
	अगर (len > vrp->buf_size ||
	    msg_len > (len - माप(काष्ठा rpmsg_hdr))) अणु
		dev_warn(dev, "inbound msg too big: (%d, %d)\n", len, msg_len);
		वापस -EINVAL;
	पूर्ण

	/* use the dst addr to fetch the callback of the appropriate user */
	mutex_lock(&vrp->endpoपूर्णांकs_lock);

	ept = idr_find(&vrp->endpoपूर्णांकs, __rpmsg32_to_cpu(little_endian, msg->dst));

	/* let's make sure no one deallocates ept जबतक we use it */
	अगर (ept)
		kref_get(&ept->refcount);

	mutex_unlock(&vrp->endpoपूर्णांकs_lock);

	अगर (ept) अणु
		/* make sure ept->cb करोesn't go away जबतक we use it */
		mutex_lock(&ept->cb_lock);

		अगर (ept->cb)
			ept->cb(ept->rpdev, msg->data, msg_len, ept->priv,
				__rpmsg32_to_cpu(little_endian, msg->src));

		mutex_unlock(&ept->cb_lock);

		/* farewell, ept, we करोn't need you anymore */
		kref_put(&ept->refcount, __ept_release);
	पूर्ण अन्यथा
		dev_warn(dev, "msg received with no recipient\n");

	/* publish the real size of the buffer */
	rpmsg_sg_init(&sg, msg, vrp->buf_size);

	/* add the buffer back to the remote processor's virtqueue */
	err = virtqueue_add_inbuf(vrp->rvq, &sg, 1, msg, GFP_KERNEL);
	अगर (err < 0) अणु
		dev_err(dev, "failed to add a virtqueue buffer: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* called when an rx buffer is used, and it's समय to digest a message */
अटल व्योम rpmsg_recv_करोne(काष्ठा virtqueue *rvq)
अणु
	काष्ठा virtproc_info *vrp = rvq->vdev->priv;
	काष्ठा device *dev = &rvq->vdev->dev;
	काष्ठा rpmsg_hdr *msg;
	अचिन्हित पूर्णांक len, msgs_received = 0;
	पूर्णांक err;

	msg = virtqueue_get_buf(rvq, &len);
	अगर (!msg) अणु
		dev_err(dev, "uhm, incoming signal, but no used buffer ?\n");
		वापस;
	पूर्ण

	जबतक (msg) अणु
		err = rpmsg_recv_single(vrp, dev, msg, len);
		अगर (err)
			अवरोध;

		msgs_received++;

		msg = virtqueue_get_buf(rvq, &len);
	पूर्ण

	dev_dbg(dev, "Received %u messages\n", msgs_received);

	/* tell the remote processor we added another available rx buffer */
	अगर (msgs_received)
		virtqueue_kick(vrp->rvq);
पूर्ण

/*
 * This is invoked whenever the remote processor completed processing
 * a TX msg we just sent it, and the buffer is put back to the used ring.
 *
 * Normally, though, we suppress this "tx complete" पूर्णांकerrupt in order to
 * aव्योम the incurred overhead.
 */
अटल व्योम rpmsg_xmit_करोne(काष्ठा virtqueue *svq)
अणु
	काष्ठा virtproc_info *vrp = svq->vdev->priv;

	dev_dbg(&svq->vdev->dev, "%s\n", __func__);

	/* wake up potential senders that are रुकोing क्रम a tx buffer */
	wake_up_पूर्णांकerruptible(&vrp->sendq);
पूर्ण

/*
 * Called to expose to user a /dev/rpmsg_ctrlX पूर्णांकerface allowing to
 * create endpoपूर्णांक-to-endpoपूर्णांक communication without associated RPMsg channel.
 * The endpoपूर्णांकs are rattached to the ctrldev RPMsg device.
 */
अटल काष्ठा rpmsg_device *rpmsg_virtio_add_ctrl_dev(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtproc_info *vrp = vdev->priv;
	काष्ठा virtio_rpmsg_channel *vch;
	काष्ठा rpmsg_device *rpdev_ctrl;
	पूर्णांक err = 0;

	vch = kzalloc(माप(*vch), GFP_KERNEL);
	अगर (!vch)
		वापस ERR_PTR(-ENOMEM);

	/* Link the channel to the vrp */
	vch->vrp = vrp;

	/* Assign खुला inक्रमmation to the rpmsg_device */
	rpdev_ctrl = &vch->rpdev;
	rpdev_ctrl->ops = &virtio_rpmsg_ops;

	rpdev_ctrl->dev.parent = &vrp->vdev->dev;
	rpdev_ctrl->dev.release = virtio_rpmsg_release_device;
	rpdev_ctrl->little_endian = virtio_is_little_endian(vrp->vdev);

	err = rpmsg_chrdev_रेजिस्टर_device(rpdev_ctrl);
	अगर (err) अणु
		kमुक्त(vch);
		वापस ERR_PTR(err);
	पूर्ण

	वापस rpdev_ctrl;
पूर्ण

अटल व्योम rpmsg_virtio_del_ctrl_dev(काष्ठा rpmsg_device *rpdev_ctrl)
अणु
	अगर (!rpdev_ctrl)
		वापस;
	kमुक्त(to_virtio_rpmsg_channel(rpdev_ctrl));
पूर्ण

अटल पूर्णांक rpmsg_probe(काष्ठा virtio_device *vdev)
अणु
	vq_callback_t *vq_cbs[] = अणु rpmsg_recv_करोne, rpmsg_xmit_करोne पूर्ण;
	अटल स्थिर अक्षर * स्थिर names[] = अणु "input", "output" पूर्ण;
	काष्ठा virtqueue *vqs[2];
	काष्ठा virtproc_info *vrp;
	काष्ठा virtio_rpmsg_channel *vch = शून्य;
	काष्ठा rpmsg_device *rpdev_ns, *rpdev_ctrl;
	व्योम *bufs_va;
	पूर्णांक err = 0, i;
	माप_प्रकार total_buf_space;
	bool notअगरy;

	vrp = kzalloc(माप(*vrp), GFP_KERNEL);
	अगर (!vrp)
		वापस -ENOMEM;

	vrp->vdev = vdev;

	idr_init(&vrp->endpoपूर्णांकs);
	mutex_init(&vrp->endpoपूर्णांकs_lock);
	mutex_init(&vrp->tx_lock);
	init_रुकोqueue_head(&vrp->sendq);

	/* We expect two virtqueues, rx and tx (and in this order) */
	err = virtio_find_vqs(vdev, 2, vqs, vq_cbs, names, शून्य);
	अगर (err)
		जाओ मुक्त_vrp;

	vrp->rvq = vqs[0];
	vrp->svq = vqs[1];

	/* we expect symmetric tx/rx vrings */
	WARN_ON(virtqueue_get_vring_size(vrp->rvq) !=
		virtqueue_get_vring_size(vrp->svq));

	/* we need less buffers अगर vrings are small */
	अगर (virtqueue_get_vring_size(vrp->rvq) < MAX_RPMSG_NUM_BUFS / 2)
		vrp->num_bufs = virtqueue_get_vring_size(vrp->rvq) * 2;
	अन्यथा
		vrp->num_bufs = MAX_RPMSG_NUM_BUFS;

	vrp->buf_size = MAX_RPMSG_BUF_SIZE;

	total_buf_space = vrp->num_bufs * vrp->buf_size;

	/* allocate coherent memory क्रम the buffers */
	bufs_va = dma_alloc_coherent(vdev->dev.parent,
				     total_buf_space, &vrp->bufs_dma,
				     GFP_KERNEL);
	अगर (!bufs_va) अणु
		err = -ENOMEM;
		जाओ vqs_del;
	पूर्ण

	dev_dbg(&vdev->dev, "buffers: va %pK, dma %pad\n",
		bufs_va, &vrp->bufs_dma);

	/* half of the buffers is dedicated क्रम RX */
	vrp->rbufs = bufs_va;

	/* and half is dedicated क्रम TX */
	vrp->sbufs = bufs_va + total_buf_space / 2;

	/* set up the receive buffers */
	क्रम (i = 0; i < vrp->num_bufs / 2; i++) अणु
		काष्ठा scatterlist sg;
		व्योम *cpu_addr = vrp->rbufs + i * vrp->buf_size;

		rpmsg_sg_init(&sg, cpu_addr, vrp->buf_size);

		err = virtqueue_add_inbuf(vrp->rvq, &sg, 1, cpu_addr,
					  GFP_KERNEL);
		WARN_ON(err); /* sanity check; this can't really happen */
	पूर्ण

	/* suppress "tx-complete" पूर्णांकerrupts */
	virtqueue_disable_cb(vrp->svq);

	vdev->priv = vrp;

	rpdev_ctrl = rpmsg_virtio_add_ctrl_dev(vdev);
	अगर (IS_ERR(rpdev_ctrl)) अणु
		err = PTR_ERR(rpdev_ctrl);
		जाओ मुक्त_coherent;
	पूर्ण

	/* अगर supported by the remote processor, enable the name service */
	अगर (virtio_has_feature(vdev, VIRTIO_RPMSG_F_NS)) अणु
		vch = kzalloc(माप(*vch), GFP_KERNEL);
		अगर (!vch) अणु
			err = -ENOMEM;
			जाओ मुक्त_ctrldev;
		पूर्ण

		/* Link the channel to our vrp */
		vch->vrp = vrp;

		/* Assign खुला inक्रमmation to the rpmsg_device */
		rpdev_ns = &vch->rpdev;
		rpdev_ns->ops = &virtio_rpmsg_ops;
		rpdev_ns->little_endian = virtio_is_little_endian(vrp->vdev);

		rpdev_ns->dev.parent = &vrp->vdev->dev;
		rpdev_ns->dev.release = virtio_rpmsg_release_device;

		err = rpmsg_ns_रेजिस्टर_device(rpdev_ns);
		अगर (err)
			जाओ मुक्त_vch;
	पूर्ण

	/*
	 * Prepare to kick but करोn't notify yet - we can't करो this beक्रमe
	 * device is पढ़ोy.
	 */
	notअगरy = virtqueue_kick_prepare(vrp->rvq);

	/* From this poपूर्णांक on, we can notअगरy and get callbacks. */
	virtio_device_पढ़ोy(vdev);

	/* tell the remote processor it can start sending messages */
	/*
	 * this might be concurrent with callbacks, but we are only
	 * करोing notअगरy, not a full kick here, so that's ok.
	 */
	अगर (notअगरy)
		virtqueue_notअगरy(vrp->rvq);

	dev_info(&vdev->dev, "rpmsg host is online\n");

	वापस 0;

मुक्त_vch:
	kमुक्त(vch);
मुक्त_ctrldev:
	rpmsg_virtio_del_ctrl_dev(rpdev_ctrl);
मुक्त_coherent:
	dma_मुक्त_coherent(vdev->dev.parent, total_buf_space,
			  bufs_va, vrp->bufs_dma);
vqs_del:
	vdev->config->del_vqs(vrp->vdev);
मुक्त_vrp:
	kमुक्त(vrp);
	वापस err;
पूर्ण

अटल पूर्णांक rpmsg_हटाओ_device(काष्ठा device *dev, व्योम *data)
अणु
	device_unरेजिस्टर(dev);

	वापस 0;
पूर्ण

अटल व्योम rpmsg_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtproc_info *vrp = vdev->priv;
	माप_प्रकार total_buf_space = vrp->num_bufs * vrp->buf_size;
	पूर्णांक ret;

	vdev->config->reset(vdev);

	ret = device_क्रम_each_child(&vdev->dev, शून्य, rpmsg_हटाओ_device);
	अगर (ret)
		dev_warn(&vdev->dev, "can't remove rpmsg device: %d\n", ret);

	idr_destroy(&vrp->endpoपूर्णांकs);

	vdev->config->del_vqs(vrp->vdev);

	dma_मुक्त_coherent(vdev->dev.parent, total_buf_space,
			  vrp->rbufs, vrp->bufs_dma);

	kमुक्त(vrp);
पूर्ण

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_RPMSG, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक features[] = अणु
	VIRTIO_RPMSG_F_NS,
पूर्ण;

अटल काष्ठा virtio_driver virtio_ipc_driver = अणु
	.feature_table	= features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver.name	= KBUILD_MODNAME,
	.driver.owner	= THIS_MODULE,
	.id_table	= id_table,
	.probe		= rpmsg_probe,
	.हटाओ		= rpmsg_हटाओ,
पूर्ण;

अटल पूर्णांक __init rpmsg_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_virtio_driver(&virtio_ipc_driver);
	अगर (ret)
		pr_err("failed to register virtio driver: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(rpmsg_init);

अटल व्योम __निकास rpmsg_fini(व्योम)
अणु
	unरेजिस्टर_virtio_driver(&virtio_ipc_driver);
पूर्ण
module_निकास(rpmsg_fini);

MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio-based remote processor messaging bus");
MODULE_LICENSE("GPL v2");
