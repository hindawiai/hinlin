<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The Virtio 9p transport driver
 *
 * This is a block based transport driver based on the lguest block driver
 * code.
 *
 *  Copyright (C) 2007, 2008 Eric Van Hensbergen, IBM Corporation
 *
 *  Based on virtio console driver
 *  Copyright (C) 2006, 2007 Rusty Russell, IBM Corporation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/un.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/inet.h>
#समावेश <linux/idr.h>
#समावेश <linux/file.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <net/9p/9p.h>
#समावेश <linux/parser.h>
#समावेश <net/9p/client.h>
#समावेश <net/9p/transport.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/swap.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_9p.h>
#समावेश "trans_common.h"

#घोषणा VIRTQUEUE_NUM	128

/* a single mutex to manage channel initialization and attachment */
अटल DEFINE_MUTEX(virtio_9p_lock);
अटल DECLARE_WAIT_QUEUE_HEAD(vp_wq);
अटल atomic_t vp_pinned = ATOMIC_INIT(0);

/**
 * काष्ठा virtio_chan - per-instance transport inक्रमmation
 * @inuse: whether the channel is in use
 * @lock: protects multiple elements within this काष्ठाure
 * @client: client instance
 * @vdev: virtio dev associated with this channel
 * @vq: virtio queue associated with this channel
 * @ring_bufs_avail: flag to indicate there is some available in the ring buf
 * @vc_wq: रुको queue क्रम रुकोing क्रम thing to be added to ring buf
 * @p9_max_pages: maximum number of pinned pages
 * @sg: scatter gather list which is used to pack a request (रक्षित?)
 * @chan_list: linked list of channels
 *
 * We keep all per-channel inक्रमmation in a काष्ठाure.
 * This काष्ठाure is allocated within the devices dev->mem space.
 * A poपूर्णांकer to the काष्ठाure will get put in the transport निजी.
 *
 */

काष्ठा virtio_chan अणु
	bool inuse;

	spinlock_t lock;

	काष्ठा p9_client *client;
	काष्ठा virtio_device *vdev;
	काष्ठा virtqueue *vq;
	पूर्णांक ring_bufs_avail;
	रुको_queue_head_t *vc_wq;
	/* This is global limit. Since we करोn't have a global काष्ठाure,
	 * will be placing it in each channel.
	 */
	अचिन्हित दीर्घ p9_max_pages;
	/* Scatterlist: can be too big क्रम stack. */
	काष्ठा scatterlist sg[VIRTQUEUE_NUM];
	/**
	 * @tag: name to identअगरy a mount null terminated
	 */
	अक्षर *tag;

	काष्ठा list_head chan_list;
पूर्ण;

अटल काष्ठा list_head virtio_chan_list;

/* How many bytes left in this page. */
अटल अचिन्हित पूर्णांक rest_of_page(व्योम *data)
अणु
	वापस PAGE_SIZE - offset_in_page(data);
पूर्ण

/**
 * p9_virtio_बंद - reclaim resources of a channel
 * @client: client instance
 *
 * This reclaims a channel by मुक्तing its resources and
 * reseting its inuse flag.
 *
 */

अटल व्योम p9_virtio_बंद(काष्ठा p9_client *client)
अणु
	काष्ठा virtio_chan *chan = client->trans;

	mutex_lock(&virtio_9p_lock);
	अगर (chan)
		chan->inuse = false;
	mutex_unlock(&virtio_9p_lock);
पूर्ण

/**
 * req_करोne - callback which संकेतs activity from the server
 * @vq: virtio queue activity was received on
 *
 * This notअगरies us that the server has triggered some activity
 * on the virtio channel - most likely a response to request we
 * sent.  Figure out which requests now have responses and wake up
 * those thपढ़ोs.
 *
 * Bugs: could करो with some additional sanity checking, but appears to work.
 *
 */

अटल व्योम req_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_chan *chan = vq->vdev->priv;
	अचिन्हित पूर्णांक len;
	काष्ठा p9_req_t *req;
	bool need_wakeup = false;
	अचिन्हित दीर्घ flags;

	p9_debug(P9_DEBUG_TRANS, ": request done\n");

	spin_lock_irqsave(&chan->lock, flags);
	जबतक ((req = virtqueue_get_buf(chan->vq, &len)) != शून्य) अणु
		अगर (!chan->ring_bufs_avail) अणु
			chan->ring_bufs_avail = 1;
			need_wakeup = true;
		पूर्ण

		अगर (len) अणु
			req->rc.size = len;
			p9_client_cb(chan->client, req, REQ_STATUS_RCVD);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chan->lock, flags);
	/* Wakeup अगर anyone रुकोing क्रम VirtIO ring space. */
	अगर (need_wakeup)
		wake_up(chan->vc_wq);
पूर्ण

/**
 * pack_sg_list - pack a scatter gather list from a linear buffer
 * @sg: scatter/gather list to pack पूर्णांकo
 * @start: which segment of the sg_list to start at
 * @limit: maximum segment to pack data to
 * @data: data to pack पूर्णांकo scatter/gather list
 * @count: amount of data to pack पूर्णांकo the scatter/gather list
 *
 * sg_lists have multiple segments of various sizes.  This will pack
 * arbitrary data पूर्णांकo an existing scatter gather list, segmenting the
 * data as necessary within स्थिरraपूर्णांकs.
 *
 */

अटल पूर्णांक pack_sg_list(काष्ठा scatterlist *sg, पूर्णांक start,
			पूर्णांक limit, अक्षर *data, पूर्णांक count)
अणु
	पूर्णांक s;
	पूर्णांक index = start;

	जबतक (count) अणु
		s = rest_of_page(data);
		अगर (s > count)
			s = count;
		BUG_ON(index >= limit);
		/* Make sure we करोn't terminate early. */
		sg_unmark_end(&sg[index]);
		sg_set_buf(&sg[index++], data, s);
		count -= s;
		data += s;
	पूर्ण
	अगर (index-start)
		sg_mark_end(&sg[index - 1]);
	वापस index-start;
पूर्ण

/* We करोn't currently allow canceling of virtio requests */
अटल पूर्णांक p9_virtio_cancel(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	वापस 1;
पूर्ण

/* Reply won't come, so drop req ref */
अटल पूर्णांक p9_virtio_cancelled(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	p9_req_put(req);
	वापस 0;
पूर्ण

/**
 * pack_sg_list_p - Just like pack_sg_list. Instead of taking a buffer,
 * this takes a list of pages.
 * @sg: scatter/gather list to pack पूर्णांकo
 * @start: which segment of the sg_list to start at
 * @limit: maximum number of pages in sg list.
 * @pdata: a list of pages to add पूर्णांकo sg.
 * @nr_pages: number of pages to pack पूर्णांकo the scatter/gather list
 * @offs: amount of data in the beginning of first page _not_ to pack
 * @count: amount of data to pack पूर्णांकo the scatter/gather list
 */
अटल पूर्णांक
pack_sg_list_p(काष्ठा scatterlist *sg, पूर्णांक start, पूर्णांक limit,
	       काष्ठा page **pdata, पूर्णांक nr_pages, माप_प्रकार offs, पूर्णांक count)
अणु
	पूर्णांक i = 0, s;
	पूर्णांक data_off = offs;
	पूर्णांक index = start;

	BUG_ON(nr_pages > (limit - start));
	/*
	 * अगर the first page करोesn't start at
	 * page boundary find the offset
	 */
	जबतक (nr_pages) अणु
		s = PAGE_SIZE - data_off;
		अगर (s > count)
			s = count;
		BUG_ON(index >= limit);
		/* Make sure we करोn't terminate early. */
		sg_unmark_end(&sg[index]);
		sg_set_page(&sg[index++], pdata[i++], s, data_off);
		data_off = 0;
		count -= s;
		nr_pages--;
	पूर्ण

	अगर (index-start)
		sg_mark_end(&sg[index - 1]);
	वापस index - start;
पूर्ण

/**
 * p9_virtio_request - issue a request
 * @client: client instance issuing the request
 * @req: request to be issued
 *
 */

अटल पूर्णांक
p9_virtio_request(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	पूर्णांक err;
	पूर्णांक in, out, out_sgs, in_sgs;
	अचिन्हित दीर्घ flags;
	काष्ठा virtio_chan *chan = client->trans;
	काष्ठा scatterlist *sgs[2];

	p9_debug(P9_DEBUG_TRANS, "9p debug: virtio request\n");

	req->status = REQ_STATUS_SENT;
req_retry:
	spin_lock_irqsave(&chan->lock, flags);

	out_sgs = in_sgs = 0;
	/* Handle out VirtIO ring buffers */
	out = pack_sg_list(chan->sg, 0,
			   VIRTQUEUE_NUM, req->tc.sdata, req->tc.size);
	अगर (out)
		sgs[out_sgs++] = chan->sg;

	in = pack_sg_list(chan->sg, out,
			  VIRTQUEUE_NUM, req->rc.sdata, req->rc.capacity);
	अगर (in)
		sgs[out_sgs + in_sgs++] = chan->sg + out;

	err = virtqueue_add_sgs(chan->vq, sgs, out_sgs, in_sgs, req,
				GFP_ATOMIC);
	अगर (err < 0) अणु
		अगर (err == -ENOSPC) अणु
			chan->ring_bufs_avail = 0;
			spin_unlock_irqrestore(&chan->lock, flags);
			err = रुको_event_समाप्तable(*chan->vc_wq,
						  chan->ring_bufs_avail);
			अगर (err  == -ERESTARTSYS)
				वापस err;

			p9_debug(P9_DEBUG_TRANS, "Retry virtio request\n");
			जाओ req_retry;
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&chan->lock, flags);
			p9_debug(P9_DEBUG_TRANS,
				 "virtio rpc add_sgs returned failure\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	virtqueue_kick(chan->vq);
	spin_unlock_irqrestore(&chan->lock, flags);

	p9_debug(P9_DEBUG_TRANS, "virtio request kicked\n");
	वापस 0;
पूर्ण

अटल पूर्णांक p9_get_mapped_pages(काष्ठा virtio_chan *chan,
			       काष्ठा page ***pages,
			       काष्ठा iov_iter *data,
			       पूर्णांक count,
			       माप_प्रकार *offs,
			       पूर्णांक *need_drop)
अणु
	पूर्णांक nr_pages;
	पूर्णांक err;

	अगर (!iov_iter_count(data))
		वापस 0;

	अगर (!iov_iter_is_kvec(data)) अणु
		पूर्णांक n;
		/*
		 * We allow only p9_max_pages pinned. We रुको क्रम the
		 * Other zc request to finish here
		 */
		अगर (atomic_पढ़ो(&vp_pinned) >= chan->p9_max_pages) अणु
			err = रुको_event_समाप्तable(vp_wq,
			      (atomic_पढ़ो(&vp_pinned) < chan->p9_max_pages));
			अगर (err == -ERESTARTSYS)
				वापस err;
		पूर्ण
		n = iov_iter_get_pages_alloc(data, pages, count, offs);
		अगर (n < 0)
			वापस n;
		*need_drop = 1;
		nr_pages = DIV_ROUND_UP(n + *offs, PAGE_SIZE);
		atomic_add(nr_pages, &vp_pinned);
		वापस n;
	पूर्ण अन्यथा अणु
		/* kernel buffer, no need to pin pages */
		पूर्णांक index;
		माप_प्रकार len;
		व्योम *p;

		/* we'd already checked that it's non-empty */
		जबतक (1) अणु
			len = iov_iter_single_seg_count(data);
			अगर (likely(len)) अणु
				p = data->kvec->iov_base + data->iov_offset;
				अवरोध;
			पूर्ण
			iov_iter_advance(data, 0);
		पूर्ण
		अगर (len > count)
			len = count;

		nr_pages = DIV_ROUND_UP((अचिन्हित दीर्घ)p + len, PAGE_SIZE) -
			   (अचिन्हित दीर्घ)p / PAGE_SIZE;

		*pages = kदो_स्मृति_array(nr_pages, माप(काष्ठा page *),
				       GFP_NOFS);
		अगर (!*pages)
			वापस -ENOMEM;

		*need_drop = 0;
		p -= (*offs = offset_in_page(p));
		क्रम (index = 0; index < nr_pages; index++) अणु
			अगर (is_vदो_स्मृति_addr(p))
				(*pages)[index] = vदो_स्मृति_to_page(p);
			अन्यथा
				(*pages)[index] = kmap_to_page(p);
			p += PAGE_SIZE;
		पूर्ण
		वापस len;
	पूर्ण
पूर्ण

/**
 * p9_virtio_zc_request - issue a zero copy request
 * @client: client instance issuing the request
 * @req: request to be issued
 * @uidata: user buffer that should be used क्रम zero copy पढ़ो
 * @uodata: user buffer that should be used क्रम zero copy ग_लिखो
 * @inlen: पढ़ो buffer size
 * @outlen: ग_लिखो buffer size
 * @in_hdr_len: पढ़ोer header size, This is the size of response protocol data
 *
 */
अटल पूर्णांक
p9_virtio_zc_request(काष्ठा p9_client *client, काष्ठा p9_req_t *req,
		     काष्ठा iov_iter *uidata, काष्ठा iov_iter *uodata,
		     पूर्णांक inlen, पूर्णांक outlen, पूर्णांक in_hdr_len)
अणु
	पूर्णांक in, out, err, out_sgs, in_sgs;
	अचिन्हित दीर्घ flags;
	पूर्णांक in_nr_pages = 0, out_nr_pages = 0;
	काष्ठा page **in_pages = शून्य, **out_pages = शून्य;
	काष्ठा virtio_chan *chan = client->trans;
	काष्ठा scatterlist *sgs[4];
	माप_प्रकार offs;
	पूर्णांक need_drop = 0;
	पूर्णांक kicked = 0;

	p9_debug(P9_DEBUG_TRANS, "virtio request\n");

	अगर (uodata) अणु
		__le32 sz;
		पूर्णांक n = p9_get_mapped_pages(chan, &out_pages, uodata,
					    outlen, &offs, &need_drop);
		अगर (n < 0) अणु
			err = n;
			जाओ err_out;
		पूर्ण
		out_nr_pages = DIV_ROUND_UP(n + offs, PAGE_SIZE);
		अगर (n != outlen) अणु
			__le32 v = cpu_to_le32(n);
			स_नकल(&req->tc.sdata[req->tc.size - 4], &v, 4);
			outlen = n;
		पूर्ण
		/* The size field of the message must include the length of the
		 * header and the length of the data.  We didn't actually know
		 * the length of the data until this poपूर्णांक so add it in now.
		 */
		sz = cpu_to_le32(req->tc.size + outlen);
		स_नकल(&req->tc.sdata[0], &sz, माप(sz));
	पूर्ण अन्यथा अगर (uidata) अणु
		पूर्णांक n = p9_get_mapped_pages(chan, &in_pages, uidata,
					    inlen, &offs, &need_drop);
		अगर (n < 0) अणु
			err = n;
			जाओ err_out;
		पूर्ण
		in_nr_pages = DIV_ROUND_UP(n + offs, PAGE_SIZE);
		अगर (n != inlen) अणु
			__le32 v = cpu_to_le32(n);
			स_नकल(&req->tc.sdata[req->tc.size - 4], &v, 4);
			inlen = n;
		पूर्ण
	पूर्ण
	req->status = REQ_STATUS_SENT;
req_retry_pinned:
	spin_lock_irqsave(&chan->lock, flags);

	out_sgs = in_sgs = 0;

	/* out data */
	out = pack_sg_list(chan->sg, 0,
			   VIRTQUEUE_NUM, req->tc.sdata, req->tc.size);

	अगर (out)
		sgs[out_sgs++] = chan->sg;

	अगर (out_pages) अणु
		sgs[out_sgs++] = chan->sg + out;
		out += pack_sg_list_p(chan->sg, out, VIRTQUEUE_NUM,
				      out_pages, out_nr_pages, offs, outlen);
	पूर्ण

	/*
	 * Take care of in data
	 * For example TREAD have 11.
	 * 11 is the पढ़ो/ग_लिखो header = PDU Header(7) + IO Size (4).
	 * Arrange in such a way that server places header in the
	 * alloced memory and payload onto the user buffer.
	 */
	in = pack_sg_list(chan->sg, out,
			  VIRTQUEUE_NUM, req->rc.sdata, in_hdr_len);
	अगर (in)
		sgs[out_sgs + in_sgs++] = chan->sg + out;

	अगर (in_pages) अणु
		sgs[out_sgs + in_sgs++] = chan->sg + out + in;
		in += pack_sg_list_p(chan->sg, out + in, VIRTQUEUE_NUM,
				     in_pages, in_nr_pages, offs, inlen);
	पूर्ण

	BUG_ON(out_sgs + in_sgs > ARRAY_SIZE(sgs));
	err = virtqueue_add_sgs(chan->vq, sgs, out_sgs, in_sgs, req,
				GFP_ATOMIC);
	अगर (err < 0) अणु
		अगर (err == -ENOSPC) अणु
			chan->ring_bufs_avail = 0;
			spin_unlock_irqrestore(&chan->lock, flags);
			err = रुको_event_समाप्तable(*chan->vc_wq,
						  chan->ring_bufs_avail);
			अगर (err  == -ERESTARTSYS)
				जाओ err_out;

			p9_debug(P9_DEBUG_TRANS, "Retry virtio request\n");
			जाओ req_retry_pinned;
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&chan->lock, flags);
			p9_debug(P9_DEBUG_TRANS,
				 "virtio rpc add_sgs returned failure\n");
			err = -EIO;
			जाओ err_out;
		पूर्ण
	पूर्ण
	virtqueue_kick(chan->vq);
	spin_unlock_irqrestore(&chan->lock, flags);
	kicked = 1;
	p9_debug(P9_DEBUG_TRANS, "virtio request kicked\n");
	err = रुको_event_समाप्तable(req->wq, req->status >= REQ_STATUS_RCVD);
	/*
	 * Non kernel buffers are pinned, unpin them
	 */
err_out:
	अगर (need_drop) अणु
		अगर (in_pages) अणु
			p9_release_pages(in_pages, in_nr_pages);
			atomic_sub(in_nr_pages, &vp_pinned);
		पूर्ण
		अगर (out_pages) अणु
			p9_release_pages(out_pages, out_nr_pages);
			atomic_sub(out_nr_pages, &vp_pinned);
		पूर्ण
		/* wakeup anybody रुकोing क्रम slots to pin pages */
		wake_up(&vp_wq);
	पूर्ण
	kvमुक्त(in_pages);
	kvमुक्त(out_pages);
	अगर (!kicked) अणु
		/* reply won't come */
		p9_req_put(req);
	पूर्ण
	वापस err;
पूर्ण

अटल sमाप_प्रकार p9_mount_tag_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा virtio_chan *chan;
	काष्ठा virtio_device *vdev;
	पूर्णांक tag_len;

	vdev = dev_to_virtio(dev);
	chan = vdev->priv;
	tag_len = म_माप(chan->tag);

	स_नकल(buf, chan->tag, tag_len + 1);

	वापस tag_len + 1;
पूर्ण

अटल DEVICE_ATTR(mount_tag, 0444, p9_mount_tag_show, शून्य);

/**
 * p9_virtio_probe - probe क्रम existence of 9P virtio channels
 * @vdev: virtio device to probe
 *
 * This probes क्रम existing virtio channels.
 *
 */

अटल पूर्णांक p9_virtio_probe(काष्ठा virtio_device *vdev)
अणु
	__u16 tag_len;
	अक्षर *tag;
	पूर्णांक err;
	काष्ठा virtio_chan *chan;

	अगर (!vdev->config->get) अणु
		dev_err(&vdev->dev, "%s failure: config access disabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	chan = kदो_स्मृति(माप(काष्ठा virtio_chan), GFP_KERNEL);
	अगर (!chan) अणु
		pr_err("Failed to allocate virtio 9P channel\n");
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	chan->vdev = vdev;

	/* We expect one virtqueue, क्रम requests. */
	chan->vq = virtio_find_single_vq(vdev, req_करोne, "requests");
	अगर (IS_ERR(chan->vq)) अणु
		err = PTR_ERR(chan->vq);
		जाओ out_मुक्त_chan;
	पूर्ण
	chan->vq->vdev->priv = chan;
	spin_lock_init(&chan->lock);

	sg_init_table(chan->sg, VIRTQUEUE_NUM);

	chan->inuse = false;
	अगर (virtio_has_feature(vdev, VIRTIO_9P_MOUNT_TAG)) अणु
		virtio_cपढ़ो(vdev, काष्ठा virtio_9p_config, tag_len, &tag_len);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ out_मुक्त_vq;
	पूर्ण
	tag = kzalloc(tag_len + 1, GFP_KERNEL);
	अगर (!tag) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_vq;
	पूर्ण

	virtio_cपढ़ो_bytes(vdev, दुरत्व(काष्ठा virtio_9p_config, tag),
			   tag, tag_len);
	chan->tag = tag;
	err = sysfs_create_file(&(vdev->dev.kobj), &dev_attr_mount_tag.attr);
	अगर (err) अणु
		जाओ out_मुक्त_tag;
	पूर्ण
	chan->vc_wq = kदो_स्मृति(माप(रुको_queue_head_t), GFP_KERNEL);
	अगर (!chan->vc_wq) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_tag;
	पूर्ण
	init_रुकोqueue_head(chan->vc_wq);
	chan->ring_bufs_avail = 1;
	/* Ceiling limit to aव्योम denial of service attacks */
	chan->p9_max_pages = nr_मुक्त_buffer_pages()/4;

	virtio_device_पढ़ोy(vdev);

	mutex_lock(&virtio_9p_lock);
	list_add_tail(&chan->chan_list, &virtio_chan_list);
	mutex_unlock(&virtio_9p_lock);

	/* Let udev rules use the new mount_tag attribute. */
	kobject_uevent(&(vdev->dev.kobj), KOBJ_CHANGE);

	वापस 0;

out_मुक्त_tag:
	kमुक्त(tag);
out_मुक्त_vq:
	vdev->config->del_vqs(vdev);
out_मुक्त_chan:
	kमुक्त(chan);
fail:
	वापस err;
पूर्ण


/**
 * p9_virtio_create - allocate a new virtio channel
 * @client: client instance invoking this transport
 * @devname: string identअगरying the channel to connect to (unused)
 * @args: args passed from sys_mount() क्रम per-transport options (unused)
 *
 * This sets up a transport channel क्रम 9p communication.  Right now
 * we only match the first available channel, but eventually we couldlook up
 * alternate channels by matching devname versus a virtio_config entry.
 * We use a simple reference count mechanism to ensure that only a single
 * mount has a channel खोलो at a समय.
 *
 */

अटल पूर्णांक
p9_virtio_create(काष्ठा p9_client *client, स्थिर अक्षर *devname, अक्षर *args)
अणु
	काष्ठा virtio_chan *chan;
	पूर्णांक ret = -ENOENT;
	पूर्णांक found = 0;

	अगर (devname == शून्य)
		वापस -EINVAL;

	mutex_lock(&virtio_9p_lock);
	list_क्रम_each_entry(chan, &virtio_chan_list, chan_list) अणु
		अगर (!म_भेद(devname, chan->tag)) अणु
			अगर (!chan->inuse) अणु
				chan->inuse = true;
				found = 1;
				अवरोध;
			पूर्ण
			ret = -EBUSY;
		पूर्ण
	पूर्ण
	mutex_unlock(&virtio_9p_lock);

	अगर (!found) अणु
		pr_err("no channels available for device %s\n", devname);
		वापस ret;
	पूर्ण

	client->trans = (व्योम *)chan;
	client->status = Connected;
	chan->client = client;

	वापस 0;
पूर्ण

/**
 * p9_virtio_हटाओ - clean up resources associated with a virtio device
 * @vdev: virtio device to हटाओ
 *
 */

अटल व्योम p9_virtio_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_chan *chan = vdev->priv;
	अचिन्हित दीर्घ warning_समय;

	mutex_lock(&virtio_9p_lock);

	/* Remove self from list so we करोn't get new users. */
	list_del(&chan->chan_list);
	warning_समय = jअगरfies;

	/* Wait क्रम existing users to बंद. */
	जबतक (chan->inuse) अणु
		mutex_unlock(&virtio_9p_lock);
		msleep(250);
		अगर (समय_after(jअगरfies, warning_समय + 10 * HZ)) अणु
			dev_emerg(&vdev->dev,
				  "p9_virtio_remove: waiting for device in use.\n");
			warning_समय = jअगरfies;
		पूर्ण
		mutex_lock(&virtio_9p_lock);
	पूर्ण

	mutex_unlock(&virtio_9p_lock);

	vdev->config->reset(vdev);
	vdev->config->del_vqs(vdev);

	sysfs_हटाओ_file(&(vdev->dev.kobj), &dev_attr_mount_tag.attr);
	kobject_uevent(&(vdev->dev.kobj), KOBJ_CHANGE);
	kमुक्त(chan->tag);
	kमुक्त(chan->vc_wq);
	kमुक्त(chan);

पूर्ण

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_9P, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक features[] = अणु
	VIRTIO_9P_MOUNT_TAG,
पूर्ण;

/* The standard "struct lguest_driver": */
अटल काष्ठा virtio_driver p9_virtio_drv = अणु
	.feature_table  = features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver.name    = KBUILD_MODNAME,
	.driver.owner	= THIS_MODULE,
	.id_table	= id_table,
	.probe		= p9_virtio_probe,
	.हटाओ		= p9_virtio_हटाओ,
पूर्ण;

अटल काष्ठा p9_trans_module p9_virtio_trans = अणु
	.name = "virtio",
	.create = p9_virtio_create,
	.बंद = p9_virtio_बंद,
	.request = p9_virtio_request,
	.zc_request = p9_virtio_zc_request,
	.cancel = p9_virtio_cancel,
	.cancelled = p9_virtio_cancelled,
	/*
	 * We leave one entry क्रम input and one entry क्रम response
	 * headers. We also skip one more entry to accomodate, address
	 * that are not at page boundary, that can result in an extra
	 * page in zero copy.
	 */
	.maxsize = PAGE_SIZE * (VIRTQUEUE_NUM - 3),
	.def = 1,
	.owner = THIS_MODULE,
पूर्ण;

/* The standard init function */
अटल पूर्णांक __init p9_virtio_init(व्योम)
अणु
	पूर्णांक rc;

	INIT_LIST_HEAD(&virtio_chan_list);

	v9fs_रेजिस्टर_trans(&p9_virtio_trans);
	rc = रेजिस्टर_virtio_driver(&p9_virtio_drv);
	अगर (rc)
		v9fs_unरेजिस्टर_trans(&p9_virtio_trans);

	वापस rc;
पूर्ण

अटल व्योम __निकास p9_virtio_cleanup(व्योम)
अणु
	unरेजिस्टर_virtio_driver(&p9_virtio_drv);
	v9fs_unरेजिस्टर_trans(&p9_virtio_trans);
पूर्ण

module_init(p9_virtio_init);
module_निकास(p9_virtio_cleanup);

MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_AUTHOR("Eric Van Hensbergen <ericvh@gmail.com>");
MODULE_DESCRIPTION("Virtio 9p Transport");
MODULE_LICENSE("GPL");
