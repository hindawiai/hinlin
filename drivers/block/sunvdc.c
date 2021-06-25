<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* sunvdc.c: Sun LDOM Virtual Disk Client.
 *
 * Copyright (C) 2007, 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/genhd.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/ldc.h>

#घोषणा DRV_MODULE_NAME		"sunvdc"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_MODULE_VERSION	"1.2"
#घोषणा DRV_MODULE_RELDATE	"November 24, 2014"

अटल अक्षर version[] =
	DRV_MODULE_NAME ".c:v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";
MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("Sun LDOM virtual disk client driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

#घोषणा VDC_TX_RING_SIZE	512
#घोषणा VDC_DEFAULT_BLK_SIZE	512

#घोषणा MAX_XFER_BLKS		(128 * 1024)
#घोषणा MAX_XFER_SIZE		(MAX_XFER_BLKS / VDC_DEFAULT_BLK_SIZE)
#घोषणा MAX_RING_COOKIES	((MAX_XFER_BLKS / PAGE_SIZE) + 2)

#घोषणा WAITING_FOR_LINK_UP	0x01
#घोषणा WAITING_FOR_TX_SPACE	0x02
#घोषणा WAITING_FOR_GEN_CMD	0x04
#घोषणा WAITING_FOR_ANY		-1

#घोषणा	VDC_MAX_RETRIES	10

अटल काष्ठा workqueue_काष्ठा *sunvdc_wq;

काष्ठा vdc_req_entry अणु
	काष्ठा request		*req;
पूर्ण;

काष्ठा vdc_port अणु
	काष्ठा vio_driver_state	vio;

	काष्ठा gendisk		*disk;

	काष्ठा vdc_completion	*cmp;

	u64			req_id;
	u64			seq;
	काष्ठा vdc_req_entry	rq_arr[VDC_TX_RING_SIZE];

	अचिन्हित दीर्घ		ring_cookies;

	u64			max_xfer_size;
	u32			vdisk_block_size;
	u32			drain;

	u64			ldc_समयout;
	काष्ठा delayed_work	ldc_reset_समयr_work;
	काष्ठा work_काष्ठा	ldc_reset_work;

	/* The server fills these in क्रम us in the disk attribute
	 * ACK packet.
	 */
	u64			operations;
	u32			vdisk_size;
	u8			vdisk_type;
	u8			vdisk_mtype;
	u32			vdisk_phys_blksz;

	काष्ठा blk_mq_tag_set	tag_set;

	अक्षर			disk_name[32];
पूर्ण;

अटल व्योम vdc_ldc_reset(काष्ठा vdc_port *port);
अटल व्योम vdc_ldc_reset_work(काष्ठा work_काष्ठा *work);
अटल व्योम vdc_ldc_reset_समयr_work(काष्ठा work_काष्ठा *work);

अटल अंतरभूत काष्ठा vdc_port *to_vdc_port(काष्ठा vio_driver_state *vio)
अणु
	वापस container_of(vio, काष्ठा vdc_port, vio);
पूर्ण

/* Ordered from largest major to lowest */
अटल काष्ठा vio_version vdc_versions[] = अणु
	अणु .major = 1, .minor = 2 पूर्ण,
	अणु .major = 1, .minor = 1 पूर्ण,
	अणु .major = 1, .minor = 0 पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक vdc_version_supported(काष्ठा vdc_port *port,
					u16 major, u16 minor)
अणु
	वापस port->vio.ver.major == major && port->vio.ver.minor >= minor;
पूर्ण

#घोषणा VDCBLK_NAME	"vdisk"
अटल पूर्णांक vdc_major;
#घोषणा PARTITION_SHIFT	3

अटल अंतरभूत u32 vdc_tx_dring_avail(काष्ठा vio_dring_state *dr)
अणु
	वापस vio_dring_avail(dr, VDC_TX_RING_SIZE);
पूर्ण

अटल पूर्णांक vdc_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	sector_t nsect = get_capacity(disk);
	sector_t cylinders = nsect;

	geo->heads = 0xff;
	geo->sectors = 0x3f;
	sector_भाग(cylinders, geo->heads * geo->sectors);
	geo->cylinders = cylinders;
	अगर ((sector_t)(geo->cylinders + 1) * geo->heads * geo->sectors < nsect)
		geo->cylinders = 0xffff;

	वापस 0;
पूर्ण

/* Add ioctl/CDROM_GET_CAPABILITY to support cdrom_id in udev
 * when vdisk_mtype is VD_MEDIA_TYPE_CD or VD_MEDIA_TYPE_DVD.
 * Needed to be able to install inside an lकरोm from an iso image.
 */
अटल पूर्णांक vdc_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		     अचिन्हित command, अचिन्हित दीर्घ argument)
अणु
	पूर्णांक i;
	काष्ठा gendisk *disk;

	चयन (command) अणु
	हाल CDROMMULTISESSION:
		pr_debug(PFX "Multisession CDs not supported\n");
		क्रम (i = 0; i < माप(काष्ठा cdrom_multisession); i++)
			अगर (put_user(0, (अक्षर __user *)(argument + i)))
				वापस -EFAULT;
		वापस 0;

	हाल CDROM_GET_CAPABILITY:
		disk = bdev->bd_disk;

		अगर (bdev->bd_disk && (disk->flags & GENHD_FL_CD))
			वापस 0;
		वापस -EINVAL;

	शेष:
		pr_debug(PFX "ioctl %08x not supported\n", command);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा block_device_operations vdc_fops = अणु
	.owner		= THIS_MODULE,
	.getgeo		= vdc_getgeo,
	.ioctl		= vdc_ioctl,
	.compat_ioctl	= blkdev_compat_ptr_ioctl,
पूर्ण;

अटल व्योम vdc_blk_queue_start(काष्ठा vdc_port *port)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	/* restart blk queue when ring is half emptied. also called after
	 * handshake completes, so check क्रम initial handshake beक्रमe we've
	 * allocated a disk.
	 */
	अगर (port->disk && vdc_tx_dring_avail(dr) * 100 / VDC_TX_RING_SIZE >= 50)
		blk_mq_start_stopped_hw_queues(port->disk->queue, true);
पूर्ण

अटल व्योम vdc_finish(काष्ठा vio_driver_state *vio, पूर्णांक err, पूर्णांक रुकोing_क्रम)
अणु
	अगर (vio->cmp &&
	    (रुकोing_क्रम == -1 ||
	     vio->cmp->रुकोing_क्रम == रुकोing_क्रम)) अणु
		vio->cmp->err = err;
		complete(&vio->cmp->com);
		vio->cmp = शून्य;
	पूर्ण
पूर्ण

अटल व्योम vdc_handshake_complete(काष्ठा vio_driver_state *vio)
अणु
	काष्ठा vdc_port *port = to_vdc_port(vio);

	cancel_delayed_work(&port->ldc_reset_समयr_work);
	vdc_finish(vio, 0, WAITING_FOR_LINK_UP);
	vdc_blk_queue_start(port);
पूर्ण

अटल पूर्णांक vdc_handle_unknown(काष्ठा vdc_port *port, व्योम *arg)
अणु
	काष्ठा vio_msg_tag *pkt = arg;

	prपूर्णांकk(KERN_ERR PFX "Received unknown msg [%02x:%02x:%04x:%08x]\n",
	       pkt->type, pkt->stype, pkt->stype_env, pkt->sid);
	prपूर्णांकk(KERN_ERR PFX "Resetting connection.\n");

	ldc_disconnect(port->vio.lp);

	वापस -ECONNRESET;
पूर्ण

अटल पूर्णांक vdc_send_attr(काष्ठा vio_driver_state *vio)
अणु
	काष्ठा vdc_port *port = to_vdc_port(vio);
	काष्ठा vio_disk_attr_info pkt;

	स_रखो(&pkt, 0, माप(pkt));

	pkt.tag.type = VIO_TYPE_CTRL;
	pkt.tag.stype = VIO_SUBTYPE_INFO;
	pkt.tag.stype_env = VIO_ATTR_INFO;
	pkt.tag.sid = vio_send_sid(vio);

	pkt.xfer_mode = VIO_DRING_MODE;
	pkt.vdisk_block_size = port->vdisk_block_size;
	pkt.max_xfer_size = port->max_xfer_size;

	viodbg(HS, "SEND ATTR xfer_mode[0x%x] blksz[%u] max_xfer[%llu]\n",
	       pkt.xfer_mode, pkt.vdisk_block_size, pkt.max_xfer_size);

	वापस vio_ldc_send(&port->vio, &pkt, माप(pkt));
पूर्ण

अटल पूर्णांक vdc_handle_attr(काष्ठा vio_driver_state *vio, व्योम *arg)
अणु
	काष्ठा vdc_port *port = to_vdc_port(vio);
	काष्ठा vio_disk_attr_info *pkt = arg;

	viodbg(HS, "GOT ATTR stype[0x%x] ops[%llx] disk_size[%llu] disk_type[%x] "
	       "mtype[0x%x] xfer_mode[0x%x] blksz[%u] max_xfer[%llu]\n",
	       pkt->tag.stype, pkt->operations,
	       pkt->vdisk_size, pkt->vdisk_type, pkt->vdisk_mtype,
	       pkt->xfer_mode, pkt->vdisk_block_size,
	       pkt->max_xfer_size);

	अगर (pkt->tag.stype == VIO_SUBTYPE_ACK) अणु
		चयन (pkt->vdisk_type) अणु
		हाल VD_DISK_TYPE_DISK:
		हाल VD_DISK_TYPE_SLICE:
			अवरोध;

		शेष:
			prपूर्णांकk(KERN_ERR PFX "%s: Bogus vdisk_type 0x%x\n",
			       vio->name, pkt->vdisk_type);
			वापस -ECONNRESET;
		पूर्ण

		अगर (pkt->vdisk_block_size > port->vdisk_block_size) अणु
			prपूर्णांकk(KERN_ERR PFX "%s: BLOCK size increased "
			       "%u --> %u\n",
			       vio->name,
			       port->vdisk_block_size, pkt->vdisk_block_size);
			वापस -ECONNRESET;
		पूर्ण

		port->operations = pkt->operations;
		port->vdisk_type = pkt->vdisk_type;
		अगर (vdc_version_supported(port, 1, 1)) अणु
			port->vdisk_size = pkt->vdisk_size;
			port->vdisk_mtype = pkt->vdisk_mtype;
		पूर्ण
		अगर (pkt->max_xfer_size < port->max_xfer_size)
			port->max_xfer_size = pkt->max_xfer_size;
		port->vdisk_block_size = pkt->vdisk_block_size;

		port->vdisk_phys_blksz = VDC_DEFAULT_BLK_SIZE;
		अगर (vdc_version_supported(port, 1, 2))
			port->vdisk_phys_blksz = pkt->phys_block_size;

		वापस 0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR PFX "%s: Attribute NACK\n", vio->name);

		वापस -ECONNRESET;
	पूर्ण
पूर्ण

अटल व्योम vdc_end_special(काष्ठा vdc_port *port, काष्ठा vio_disk_desc *desc)
अणु
	पूर्णांक err = desc->status;

	vdc_finish(&port->vio, -err, WAITING_FOR_GEN_CMD);
पूर्ण

अटल व्योम vdc_end_one(काष्ठा vdc_port *port, काष्ठा vio_dring_state *dr,
			अचिन्हित पूर्णांक index)
अणु
	काष्ठा vio_disk_desc *desc = vio_dring_entry(dr, index);
	काष्ठा vdc_req_entry *rqe = &port->rq_arr[index];
	काष्ठा request *req;

	अगर (unlikely(desc->hdr.state != VIO_DESC_DONE))
		वापस;

	ldc_unmap(port->vio.lp, desc->cookies, desc->ncookies);
	desc->hdr.state = VIO_DESC_FREE;
	dr->cons = vio_dring_next(dr, index);

	req = rqe->req;
	अगर (req == शून्य) अणु
		vdc_end_special(port, desc);
		वापस;
	पूर्ण

	rqe->req = शून्य;

	blk_mq_end_request(req, desc->status ? BLK_STS_IOERR : 0);

	vdc_blk_queue_start(port);
पूर्ण

अटल पूर्णांक vdc_ack(काष्ठा vdc_port *port, व्योम *msgbuf)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	काष्ठा vio_dring_data *pkt = msgbuf;

	अगर (unlikely(pkt->dring_ident != dr->ident ||
		     pkt->start_idx != pkt->end_idx ||
		     pkt->start_idx >= VDC_TX_RING_SIZE))
		वापस 0;

	vdc_end_one(port, dr, pkt->start_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक vdc_nack(काष्ठा vdc_port *port, व्योम *msgbuf)
अणु
	/* XXX Implement me XXX */
	वापस 0;
पूर्ण

अटल व्योम vdc_event(व्योम *arg, पूर्णांक event)
अणु
	काष्ठा vdc_port *port = arg;
	काष्ठा vio_driver_state *vio = &port->vio;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&vio->lock, flags);

	अगर (unlikely(event == LDC_EVENT_RESET)) अणु
		vio_link_state_change(vio, event);
		queue_work(sunvdc_wq, &port->ldc_reset_work);
		जाओ out;
	पूर्ण

	अगर (unlikely(event == LDC_EVENT_UP)) अणु
		vio_link_state_change(vio, event);
		जाओ out;
	पूर्ण

	अगर (unlikely(event != LDC_EVENT_DATA_READY)) अणु
		pr_warn(PFX "Unexpected LDC event %d\n", event);
		जाओ out;
	पूर्ण

	err = 0;
	जबतक (1) अणु
		जोड़ अणु
			काष्ठा vio_msg_tag tag;
			u64 raw[8];
		पूर्ण msgbuf;

		err = ldc_पढ़ो(vio->lp, &msgbuf, माप(msgbuf));
		अगर (unlikely(err < 0)) अणु
			अगर (err == -ECONNRESET)
				vio_conn_reset(vio);
			अवरोध;
		पूर्ण
		अगर (err == 0)
			अवरोध;
		viodbg(DATA, "TAG [%02x:%02x:%04x:%08x]\n",
		       msgbuf.tag.type,
		       msgbuf.tag.stype,
		       msgbuf.tag.stype_env,
		       msgbuf.tag.sid);
		err = vio_validate_sid(vio, &msgbuf.tag);
		अगर (err < 0)
			अवरोध;

		अगर (likely(msgbuf.tag.type == VIO_TYPE_DATA)) अणु
			अगर (msgbuf.tag.stype == VIO_SUBTYPE_ACK)
				err = vdc_ack(port, &msgbuf);
			अन्यथा अगर (msgbuf.tag.stype == VIO_SUBTYPE_NACK)
				err = vdc_nack(port, &msgbuf);
			अन्यथा
				err = vdc_handle_unknown(port, &msgbuf);
		पूर्ण अन्यथा अगर (msgbuf.tag.type == VIO_TYPE_CTRL) अणु
			err = vio_control_pkt_engine(vio, &msgbuf);
		पूर्ण अन्यथा अणु
			err = vdc_handle_unknown(port, &msgbuf);
		पूर्ण
		अगर (err < 0)
			अवरोध;
	पूर्ण
	अगर (err < 0)
		vdc_finish(&port->vio, err, WAITING_FOR_ANY);
out:
	spin_unlock_irqrestore(&vio->lock, flags);
पूर्ण

अटल पूर्णांक __vdc_tx_trigger(काष्ठा vdc_port *port)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	काष्ठा vio_dring_data hdr = अणु
		.tag = अणु
			.type		= VIO_TYPE_DATA,
			.stype		= VIO_SUBTYPE_INFO,
			.stype_env	= VIO_DRING_DATA,
			.sid		= vio_send_sid(&port->vio),
		पूर्ण,
		.dring_ident		= dr->ident,
		.start_idx		= dr->prod,
		.end_idx		= dr->prod,
	पूर्ण;
	पूर्णांक err, delay;
	पूर्णांक retries = 0;

	hdr.seq = dr->snd_nxt;
	delay = 1;
	करो अणु
		err = vio_ldc_send(&port->vio, &hdr, माप(hdr));
		अगर (err > 0) अणु
			dr->snd_nxt++;
			अवरोध;
		पूर्ण
		udelay(delay);
		अगर ((delay <<= 1) > 128)
			delay = 128;
		अगर (retries++ > VDC_MAX_RETRIES)
			अवरोध;
	पूर्ण जबतक (err == -EAGAIN);

	अगर (err == -ENOTCONN)
		vdc_ldc_reset(port);
	वापस err;
पूर्ण

अटल पूर्णांक __send_request(काष्ठा request *req)
अणु
	काष्ठा vdc_port *port = req->rq_disk->निजी_data;
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	काष्ठा scatterlist sg[MAX_RING_COOKIES];
	काष्ठा vdc_req_entry *rqe;
	काष्ठा vio_disk_desc *desc;
	अचिन्हित पूर्णांक map_perm;
	पूर्णांक nsg, err, i;
	u64 len;
	u8 op;

	अगर (WARN_ON(port->ring_cookies > MAX_RING_COOKIES))
		वापस -EINVAL;

	map_perm = LDC_MAP_SHADOW | LDC_MAP_सूचीECT | LDC_MAP_IO;

	अगर (rq_data_dir(req) == READ) अणु
		map_perm |= LDC_MAP_W;
		op = VD_OP_BREAD;
	पूर्ण अन्यथा अणु
		map_perm |= LDC_MAP_R;
		op = VD_OP_BWRITE;
	पूर्ण

	sg_init_table(sg, port->ring_cookies);
	nsg = blk_rq_map_sg(req->q, req, sg);

	len = 0;
	क्रम (i = 0; i < nsg; i++)
		len += sg[i].length;

	desc = vio_dring_cur(dr);

	err = ldc_map_sg(port->vio.lp, sg, nsg,
			 desc->cookies, port->ring_cookies,
			 map_perm);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "ldc_map_sg() failure, err=%d.\n", err);
		वापस err;
	पूर्ण

	rqe = &port->rq_arr[dr->prod];
	rqe->req = req;

	desc->hdr.ack = VIO_ACK_ENABLE;
	desc->req_id = port->req_id;
	desc->operation = op;
	अगर (port->vdisk_type == VD_DISK_TYPE_DISK) अणु
		desc->slice = 0xff;
	पूर्ण अन्यथा अणु
		desc->slice = 0;
	पूर्ण
	desc->status = ~0;
	desc->offset = (blk_rq_pos(req) << 9) / port->vdisk_block_size;
	desc->size = len;
	desc->ncookies = err;

	/* This has to be a non-SMP ग_लिखो barrier because we are writing
	 * to memory which is shared with the peer LDOM.
	 */
	wmb();
	desc->hdr.state = VIO_DESC_READY;

	err = __vdc_tx_trigger(port);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "vdc_tx_trigger() failure, err=%d\n", err);
	पूर्ण अन्यथा अणु
		port->req_id++;
		dr->prod = vio_dring_next(dr, dr->prod);
	पूर्ण

	वापस err;
पूर्ण

अटल blk_status_t vdc_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा vdc_port *port = hctx->queue->queuedata;
	काष्ठा vio_dring_state *dr;
	अचिन्हित दीर्घ flags;

	dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	blk_mq_start_request(bd->rq);

	spin_lock_irqsave(&port->vio.lock, flags);

	/*
	 * Doing drain, just end the request in error
	 */
	अगर (unlikely(port->drain)) अणु
		spin_unlock_irqrestore(&port->vio.lock, flags);
		वापस BLK_STS_IOERR;
	पूर्ण

	अगर (unlikely(vdc_tx_dring_avail(dr) < 1)) अणु
		spin_unlock_irqrestore(&port->vio.lock, flags);
		blk_mq_stop_hw_queue(hctx);
		वापस BLK_STS_DEV_RESOURCE;
	पूर्ण

	अगर (__send_request(bd->rq) < 0) अणु
		spin_unlock_irqrestore(&port->vio.lock, flags);
		वापस BLK_STS_IOERR;
	पूर्ण

	spin_unlock_irqrestore(&port->vio.lock, flags);
	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक generic_request(काष्ठा vdc_port *port, u8 op, व्योम *buf, पूर्णांक len)
अणु
	काष्ठा vio_dring_state *dr;
	काष्ठा vio_completion comp;
	काष्ठा vio_disk_desc *desc;
	अचिन्हित पूर्णांक map_perm;
	अचिन्हित दीर्घ flags;
	पूर्णांक op_len, err;
	व्योम *req_buf;

	अगर (!(((u64)1 << (u64)op) & port->operations))
		वापस -EOPNOTSUPP;

	चयन (op) अणु
	हाल VD_OP_BREAD:
	हाल VD_OP_BWRITE:
	शेष:
		वापस -EINVAL;

	हाल VD_OP_FLUSH:
		op_len = 0;
		map_perm = 0;
		अवरोध;

	हाल VD_OP_GET_WCE:
		op_len = माप(u32);
		map_perm = LDC_MAP_W;
		अवरोध;

	हाल VD_OP_SET_WCE:
		op_len = माप(u32);
		map_perm = LDC_MAP_R;
		अवरोध;

	हाल VD_OP_GET_VTOC:
		op_len = माप(काष्ठा vio_disk_vtoc);
		map_perm = LDC_MAP_W;
		अवरोध;

	हाल VD_OP_SET_VTOC:
		op_len = माप(काष्ठा vio_disk_vtoc);
		map_perm = LDC_MAP_R;
		अवरोध;

	हाल VD_OP_GET_DISKGEOM:
		op_len = माप(काष्ठा vio_disk_geom);
		map_perm = LDC_MAP_W;
		अवरोध;

	हाल VD_OP_SET_DISKGEOM:
		op_len = माप(काष्ठा vio_disk_geom);
		map_perm = LDC_MAP_R;
		अवरोध;

	हाल VD_OP_SCSICMD:
		op_len = 16;
		map_perm = LDC_MAP_RW;
		अवरोध;

	हाल VD_OP_GET_DEVID:
		op_len = माप(काष्ठा vio_disk_devid);
		map_perm = LDC_MAP_W;
		अवरोध;

	हाल VD_OP_GET_EFI:
	हाल VD_OP_SET_EFI:
		वापस -EOPNOTSUPP;
	पूर्ण

	map_perm |= LDC_MAP_SHADOW | LDC_MAP_सूचीECT | LDC_MAP_IO;

	op_len = (op_len + 7) & ~7;
	req_buf = kzalloc(op_len, GFP_KERNEL);
	अगर (!req_buf)
		वापस -ENOMEM;

	अगर (len > op_len)
		len = op_len;

	अगर (map_perm & LDC_MAP_R)
		स_नकल(req_buf, buf, len);

	spin_lock_irqsave(&port->vio.lock, flags);

	dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	/* XXX If we want to use this code generically we have to
	 * XXX handle TX ring exhaustion etc.
	 */
	desc = vio_dring_cur(dr);

	err = ldc_map_single(port->vio.lp, req_buf, op_len,
			     desc->cookies, port->ring_cookies,
			     map_perm);
	अगर (err < 0) अणु
		spin_unlock_irqrestore(&port->vio.lock, flags);
		kमुक्त(req_buf);
		वापस err;
	पूर्ण

	init_completion(&comp.com);
	comp.रुकोing_क्रम = WAITING_FOR_GEN_CMD;
	port->vio.cmp = &comp;

	desc->hdr.ack = VIO_ACK_ENABLE;
	desc->req_id = port->req_id;
	desc->operation = op;
	desc->slice = 0;
	desc->status = ~0;
	desc->offset = 0;
	desc->size = op_len;
	desc->ncookies = err;

	/* This has to be a non-SMP ग_लिखो barrier because we are writing
	 * to memory which is shared with the peer LDOM.
	 */
	wmb();
	desc->hdr.state = VIO_DESC_READY;

	err = __vdc_tx_trigger(port);
	अगर (err >= 0) अणु
		port->req_id++;
		dr->prod = vio_dring_next(dr, dr->prod);
		spin_unlock_irqrestore(&port->vio.lock, flags);

		रुको_क्रम_completion(&comp.com);
		err = comp.err;
	पूर्ण अन्यथा अणु
		port->vio.cmp = शून्य;
		spin_unlock_irqrestore(&port->vio.lock, flags);
	पूर्ण

	अगर (map_perm & LDC_MAP_W)
		स_नकल(buf, req_buf, len);

	kमुक्त(req_buf);

	वापस err;
पूर्ण

अटल पूर्णांक vdc_alloc_tx_ring(काष्ठा vdc_port *port)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	अचिन्हित दीर्घ len, entry_size;
	पूर्णांक ncookies;
	व्योम *dring;

	entry_size = माप(काष्ठा vio_disk_desc) +
		(माप(काष्ठा ldc_trans_cookie) * port->ring_cookies);
	len = (VDC_TX_RING_SIZE * entry_size);

	ncookies = VIO_MAX_RING_COOKIES;
	dring = ldc_alloc_exp_dring(port->vio.lp, len,
				    dr->cookies, &ncookies,
				    (LDC_MAP_SHADOW |
				     LDC_MAP_सूचीECT |
				     LDC_MAP_RW));
	अगर (IS_ERR(dring))
		वापस PTR_ERR(dring);

	dr->base = dring;
	dr->entry_size = entry_size;
	dr->num_entries = VDC_TX_RING_SIZE;
	dr->prod = dr->cons = 0;
	dr->pending = VDC_TX_RING_SIZE;
	dr->ncookies = ncookies;

	वापस 0;
पूर्ण

अटल व्योम vdc_मुक्त_tx_ring(काष्ठा vdc_port *port)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];

	अगर (dr->base) अणु
		ldc_मुक्त_exp_dring(port->vio.lp, dr->base,
				   (dr->entry_size * dr->num_entries),
				   dr->cookies, dr->ncookies);
		dr->base = शून्य;
		dr->entry_size = 0;
		dr->num_entries = 0;
		dr->pending = 0;
		dr->ncookies = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक vdc_port_up(काष्ठा vdc_port *port)
अणु
	काष्ठा vio_completion comp;

	init_completion(&comp.com);
	comp.err = 0;
	comp.रुकोing_क्रम = WAITING_FOR_LINK_UP;
	port->vio.cmp = &comp;

	vio_port_up(&port->vio);
	रुको_क्रम_completion(&comp.com);
	वापस comp.err;
पूर्ण

अटल व्योम vdc_port_करोwn(काष्ठा vdc_port *port)
अणु
	ldc_disconnect(port->vio.lp);
	ldc_unbind(port->vio.lp);
	vdc_मुक्त_tx_ring(port);
	vio_ldc_मुक्त(&port->vio);
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops vdc_mq_ops = अणु
	.queue_rq	= vdc_queue_rq,
पूर्ण;

अटल व्योम cleanup_queue(काष्ठा request_queue *q)
अणु
	काष्ठा vdc_port *port = q->queuedata;

	blk_cleanup_queue(q);
	blk_mq_मुक्त_tag_set(&port->tag_set);
पूर्ण

अटल काष्ठा request_queue *init_queue(काष्ठा vdc_port *port)
अणु
	काष्ठा request_queue *q;

	q = blk_mq_init_sq_queue(&port->tag_set, &vdc_mq_ops, VDC_TX_RING_SIZE,
					BLK_MQ_F_SHOULD_MERGE);
	अगर (IS_ERR(q))
		वापस q;

	q->queuedata = port;
	वापस q;
पूर्ण

अटल पूर्णांक probe_disk(काष्ठा vdc_port *port)
अणु
	काष्ठा request_queue *q;
	काष्ठा gendisk *g;
	पूर्णांक err;

	err = vdc_port_up(port);
	अगर (err)
		वापस err;

	/* Using version 1.2 means vdisk_phys_blksz should be set unless the
	 * disk is reserved by another प्रणाली.
	 */
	अगर (vdc_version_supported(port, 1, 2) && !port->vdisk_phys_blksz)
		वापस -ENODEV;

	अगर (vdc_version_supported(port, 1, 1)) अणु
		/* vdisk_size should be set during the handshake, अगर it wasn't
		 * then the underlying disk is reserved by another प्रणाली
		 */
		अगर (port->vdisk_size == -1)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		काष्ठा vio_disk_geom geom;

		err = generic_request(port, VD_OP_GET_DISKGEOM,
				      &geom, माप(geom));
		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR PFX "VD_OP_GET_DISKGEOM returns "
			       "error %d\n", err);
			वापस err;
		पूर्ण
		port->vdisk_size = ((u64)geom.num_cyl *
				    (u64)geom.num_hd *
				    (u64)geom.num_sec);
	पूर्ण

	q = init_queue(port);
	अगर (IS_ERR(q)) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: Could not allocate queue.\n",
		       port->vio.name);
		वापस PTR_ERR(q);
	पूर्ण
	g = alloc_disk(1 << PARTITION_SHIFT);
	अगर (!g) अणु
		prपूर्णांकk(KERN_ERR PFX "%s: Could not allocate gendisk.\n",
		       port->vio.name);
		cleanup_queue(q);
		वापस -ENOMEM;
	पूर्ण

	port->disk = g;

	/* Each segment in a request is up to an aligned page in size. */
	blk_queue_segment_boundary(q, PAGE_SIZE - 1);
	blk_queue_max_segment_size(q, PAGE_SIZE);

	blk_queue_max_segments(q, port->ring_cookies);
	blk_queue_max_hw_sectors(q, port->max_xfer_size);
	g->major = vdc_major;
	g->first_minor = port->vio.vdev->dev_no << PARTITION_SHIFT;
	म_नकल(g->disk_name, port->disk_name);

	g->fops = &vdc_fops;
	g->queue = q;
	g->निजी_data = port;

	set_capacity(g, port->vdisk_size);

	अगर (vdc_version_supported(port, 1, 1)) अणु
		चयन (port->vdisk_mtype) अणु
		हाल VD_MEDIA_TYPE_CD:
			pr_info(PFX "Virtual CDROM %s\n", port->disk_name);
			g->flags |= GENHD_FL_CD;
			g->flags |= GENHD_FL_REMOVABLE;
			set_disk_ro(g, 1);
			अवरोध;

		हाल VD_MEDIA_TYPE_DVD:
			pr_info(PFX "Virtual DVD %s\n", port->disk_name);
			g->flags |= GENHD_FL_CD;
			g->flags |= GENHD_FL_REMOVABLE;
			set_disk_ro(g, 1);
			अवरोध;

		हाल VD_MEDIA_TYPE_FIXED:
			pr_info(PFX "Virtual Hard disk %s\n", port->disk_name);
			अवरोध;
		पूर्ण
	पूर्ण

	blk_queue_physical_block_size(q, port->vdisk_phys_blksz);

	pr_info(PFX "%s: %u sectors (%u MB) protocol %d.%d\n",
	       g->disk_name,
	       port->vdisk_size, (port->vdisk_size >> (20 - 9)),
	       port->vio.ver.major, port->vio.ver.minor);

	device_add_disk(&port->vio.vdev->dev, g, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा ldc_channel_config vdc_ldc_cfg = अणु
	.event		= vdc_event,
	.mtu		= 64,
	.mode		= LDC_MODE_UNRELIABLE,
पूर्ण;

अटल काष्ठा vio_driver_ops vdc_vio_ops = अणु
	.send_attr		= vdc_send_attr,
	.handle_attr		= vdc_handle_attr,
	.handshake_complete	= vdc_handshake_complete,
पूर्ण;

अटल व्योम prपूर्णांक_version(व्योम)
अणु
	अटल पूर्णांक version_prपूर्णांकed;

	अगर (version_prपूर्णांकed++ == 0)
		prपूर्णांकk(KERN_INFO "%s", version);
पूर्ण

काष्ठा vdc_check_port_data अणु
	पूर्णांक	dev_no;
	अक्षर	*type;
पूर्ण;

अटल पूर्णांक vdc_device_probed(काष्ठा device *dev, व्योम *arg)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(dev);
	काष्ठा vdc_check_port_data *port_data;

	port_data = (काष्ठा vdc_check_port_data *)arg;

	अगर ((vdev->dev_no == port_data->dev_no) &&
	    (!(म_भेद((अक्षर *)&vdev->type, port_data->type))) &&
		dev_get_drvdata(dev)) अणु
		/* This device has alपढ़ोy been configured
		 * by vdc_port_probe()
		 */
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

/* Determine whether the VIO device is part of an mpgroup
 * by locating all the भव-device-port nodes associated
 * with the parent भव-device node क्रम the VIO device
 * and checking whether any of these nodes are vdc-ports
 * which have alपढ़ोy been configured.
 *
 * Returns true अगर this device is part of an mpgroup and has
 * alपढ़ोy been probed.
 */
अटल bool vdc_port_mpgroup_check(काष्ठा vio_dev *vdev)
अणु
	काष्ठा vdc_check_port_data port_data;
	काष्ठा device *dev;

	port_data.dev_no = vdev->dev_no;
	port_data.type = (अक्षर *)&vdev->type;

	dev = device_find_child(vdev->dev.parent, &port_data,
				vdc_device_probed);

	अगर (dev)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक vdc_port_probe(काष्ठा vio_dev *vdev, स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा mdesc_handle *hp;
	काष्ठा vdc_port *port;
	पूर्णांक err;
	स्थिर u64 *ldc_समयout;

	prपूर्णांक_version();

	hp = mdesc_grab();

	err = -ENODEV;
	अगर ((vdev->dev_no << PARTITION_SHIFT) & ~(u64)MINORMASK) अणु
		prपूर्णांकk(KERN_ERR PFX "Port id [%llu] too large.\n",
		       vdev->dev_no);
		जाओ err_out_release_mdesc;
	पूर्ण

	/* Check अगर this device is part of an mpgroup */
	अगर (vdc_port_mpgroup_check(vdev)) अणु
		prपूर्णांकk(KERN_WARNING
			"VIO: Ignoring extra vdisk port %s",
			dev_name(&vdev->dev));
		जाओ err_out_release_mdesc;
	पूर्ण

	port = kzalloc(माप(*port), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!port) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate vdc_port.\n");
		जाओ err_out_release_mdesc;
	पूर्ण

	अगर (vdev->dev_no >= 26)
		snम_लिखो(port->disk_name, माप(port->disk_name),
			 VDCBLK_NAME "%c%c",
			 'a' + ((पूर्णांक)vdev->dev_no / 26) - 1,
			 'a' + ((पूर्णांक)vdev->dev_no % 26));
	अन्यथा
		snम_लिखो(port->disk_name, माप(port->disk_name),
			 VDCBLK_NAME "%c", 'a' + ((पूर्णांक)vdev->dev_no % 26));
	port->vdisk_size = -1;

	/* Actual wall समय may be द्विगुन due to करो_generic_file_पढ़ो() करोing
	 * a पढ़ोahead I/O first, and once that fails it will try to पढ़ो a
	 * single page.
	 */
	ldc_समयout = mdesc_get_property(hp, vdev->mp, "vdc-timeout", शून्य);
	port->ldc_समयout = ldc_समयout ? *ldc_समयout : 0;
	INIT_DELAYED_WORK(&port->ldc_reset_समयr_work, vdc_ldc_reset_समयr_work);
	INIT_WORK(&port->ldc_reset_work, vdc_ldc_reset_work);

	err = vio_driver_init(&port->vio, vdev, VDEV_DISK,
			      vdc_versions, ARRAY_SIZE(vdc_versions),
			      &vdc_vio_ops, port->disk_name);
	अगर (err)
		जाओ err_out_मुक्त_port;

	port->vdisk_block_size = VDC_DEFAULT_BLK_SIZE;
	port->max_xfer_size = MAX_XFER_SIZE;
	port->ring_cookies = MAX_RING_COOKIES;

	err = vio_ldc_alloc(&port->vio, &vdc_ldc_cfg, port);
	अगर (err)
		जाओ err_out_मुक्त_port;

	err = vdc_alloc_tx_ring(port);
	अगर (err)
		जाओ err_out_मुक्त_ldc;

	err = probe_disk(port);
	अगर (err)
		जाओ err_out_मुक्त_tx_ring;

	/* Note that the device driver_data is used to determine
	 * whether the port has been probed.
	 */
	dev_set_drvdata(&vdev->dev, port);

	mdesc_release(hp);

	वापस 0;

err_out_मुक्त_tx_ring:
	vdc_मुक्त_tx_ring(port);

err_out_मुक्त_ldc:
	vio_ldc_मुक्त(&port->vio);

err_out_मुक्त_port:
	kमुक्त(port);

err_out_release_mdesc:
	mdesc_release(hp);
	वापस err;
पूर्ण

अटल पूर्णांक vdc_port_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा vdc_port *port = dev_get_drvdata(&vdev->dev);

	अगर (port) अणु
		blk_mq_stop_hw_queues(port->disk->queue);

		flush_work(&port->ldc_reset_work);
		cancel_delayed_work_sync(&port->ldc_reset_समयr_work);
		del_समयr_sync(&port->vio.समयr);

		del_gendisk(port->disk);
		cleanup_queue(port->disk->queue);
		put_disk(port->disk);
		port->disk = शून्य;

		vdc_मुक्त_tx_ring(port);
		vio_ldc_मुक्त(&port->vio);

		dev_set_drvdata(&vdev->dev, शून्य);

		kमुक्त(port);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vdc_requeue_inflight(काष्ठा vdc_port *port)
अणु
	काष्ठा vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	u32 idx;

	क्रम (idx = dr->cons; idx != dr->prod; idx = vio_dring_next(dr, idx)) अणु
		काष्ठा vio_disk_desc *desc = vio_dring_entry(dr, idx);
		काष्ठा vdc_req_entry *rqe = &port->rq_arr[idx];
		काष्ठा request *req;

		ldc_unmap(port->vio.lp, desc->cookies, desc->ncookies);
		desc->hdr.state = VIO_DESC_FREE;
		dr->cons = vio_dring_next(dr, idx);

		req = rqe->req;
		अगर (req == शून्य) अणु
			vdc_end_special(port, desc);
			जारी;
		पूर्ण

		rqe->req = शून्य;
		blk_mq_requeue_request(req, false);
	पूर्ण
पूर्ण

अटल व्योम vdc_queue_drain(काष्ठा vdc_port *port)
अणु
	काष्ठा request_queue *q = port->disk->queue;

	/*
	 * Mark the queue as draining, then मुक्तze/quiesce to ensure
	 * that all existing requests are seen in ->queue_rq() and समाप्तed
	 */
	port->drain = 1;
	spin_unlock_irq(&port->vio.lock);

	blk_mq_मुक्तze_queue(q);
	blk_mq_quiesce_queue(q);

	spin_lock_irq(&port->vio.lock);
	port->drain = 0;
	blk_mq_unquiesce_queue(q);
	blk_mq_unमुक्तze_queue(q);
पूर्ण

अटल व्योम vdc_ldc_reset_समयr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vdc_port *port;
	काष्ठा vio_driver_state *vio;

	port = container_of(work, काष्ठा vdc_port, ldc_reset_समयr_work.work);
	vio = &port->vio;

	spin_lock_irq(&vio->lock);
	अगर (!(port->vपन.सs_state & VIO_HS_COMPLETE)) अणु
		pr_warn(PFX "%s ldc down %llu seconds, draining queue\n",
			port->disk_name, port->ldc_समयout);
		vdc_queue_drain(port);
		vdc_blk_queue_start(port);
	पूर्ण
	spin_unlock_irq(&vio->lock);
पूर्ण

अटल व्योम vdc_ldc_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vdc_port *port;
	काष्ठा vio_driver_state *vio;
	अचिन्हित दीर्घ flags;

	port = container_of(work, काष्ठा vdc_port, ldc_reset_work);
	vio = &port->vio;

	spin_lock_irqsave(&vio->lock, flags);
	vdc_ldc_reset(port);
	spin_unlock_irqrestore(&vio->lock, flags);
पूर्ण

अटल व्योम vdc_ldc_reset(काष्ठा vdc_port *port)
अणु
	पूर्णांक err;

	निश्चित_spin_locked(&port->vio.lock);

	pr_warn(PFX "%s ldc link reset\n", port->disk_name);
	blk_mq_stop_hw_queues(port->disk->queue);
	vdc_requeue_inflight(port);
	vdc_port_करोwn(port);

	err = vio_ldc_alloc(&port->vio, &vdc_ldc_cfg, port);
	अगर (err) अणु
		pr_err(PFX "%s vio_ldc_alloc:%d\n", port->disk_name, err);
		वापस;
	पूर्ण

	err = vdc_alloc_tx_ring(port);
	अगर (err) अणु
		pr_err(PFX "%s vio_alloc_tx_ring:%d\n", port->disk_name, err);
		जाओ err_मुक्त_ldc;
	पूर्ण

	अगर (port->ldc_समयout)
		mod_delayed_work(प्रणाली_wq, &port->ldc_reset_समयr_work,
			  round_jअगरfies(jअगरfies + HZ * port->ldc_समयout));
	mod_समयr(&port->vio.समयr, round_jअगरfies(jअगरfies + HZ));
	वापस;

err_मुक्त_ldc:
	vio_ldc_मुक्त(&port->vio);
पूर्ण

अटल स्थिर काष्ठा vio_device_id vdc_port_match[] = अणु
	अणु
		.type = "vdc-port",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(vio, vdc_port_match);

अटल काष्ठा vio_driver vdc_port_driver = अणु
	.id_table	= vdc_port_match,
	.probe		= vdc_port_probe,
	.हटाओ		= vdc_port_हटाओ,
	.name		= "vdc_port",
पूर्ण;

अटल पूर्णांक __init vdc_init(व्योम)
अणु
	पूर्णांक err;

	sunvdc_wq = alloc_workqueue("sunvdc", 0, 0);
	अगर (!sunvdc_wq)
		वापस -ENOMEM;

	err = रेजिस्टर_blkdev(0, VDCBLK_NAME);
	अगर (err < 0)
		जाओ out_मुक्त_wq;

	vdc_major = err;

	err = vio_रेजिस्टर_driver(&vdc_port_driver);
	अगर (err)
		जाओ out_unरेजिस्टर_blkdev;

	वापस 0;

out_unरेजिस्टर_blkdev:
	unरेजिस्टर_blkdev(vdc_major, VDCBLK_NAME);
	vdc_major = 0;

out_मुक्त_wq:
	destroy_workqueue(sunvdc_wq);
	वापस err;
पूर्ण

अटल व्योम __निकास vdc_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&vdc_port_driver);
	unरेजिस्टर_blkdev(vdc_major, VDCBLK_NAME);
	destroy_workqueue(sunvdc_wq);
पूर्ण

module_init(vdc_init);
module_निकास(vdc_निकास);
