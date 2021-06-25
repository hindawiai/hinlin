<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ccw based virtio transport
 *
 * Copyright IBM Corp. 2012, 2014
 *
 *    Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/err.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/pfn.h>
#समावेश <linux/async.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पन.स>
#समावेश <linux/kvm_para.h>
#समावेश <linux/notअगरier.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/virtio-ccw.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/airq.h>

/*
 * virtio related functions
 */

काष्ठा vq_config_block अणु
	__u16 index;
	__u16 num;
पूर्ण __packed;

#घोषणा VIRTIO_CCW_CONFIG_SIZE 0x100
/* same as PCI config space size, should be enough क्रम all drivers */

काष्ठा vcdev_dma_area अणु
	अचिन्हित दीर्घ indicators;
	अचिन्हित दीर्घ indicators2;
	काष्ठा vq_config_block config_block;
	__u8 status;
पूर्ण;

काष्ठा virtio_ccw_device अणु
	काष्ठा virtio_device vdev;
	__u8 config[VIRTIO_CCW_CONFIG_SIZE];
	काष्ठा ccw_device *cdev;
	__u32 curr_io;
	पूर्णांक err;
	अचिन्हित पूर्णांक revision; /* Transport revision */
	रुको_queue_head_t रुको_q;
	spinlock_t lock;
	काष्ठा mutex io_lock; /* Serializes I/O requests */
	काष्ठा list_head virtqueues;
	bool is_thinपूर्णांक;
	bool going_away;
	bool device_lost;
	अचिन्हित पूर्णांक config_पढ़ोy;
	व्योम *airq_info;
	काष्ठा vcdev_dma_area *dma_area;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ *indicators(काष्ठा virtio_ccw_device *vcdev)
अणु
	वापस &vcdev->dma_area->indicators;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *indicators2(काष्ठा virtio_ccw_device *vcdev)
अणु
	वापस &vcdev->dma_area->indicators2;
पूर्ण

काष्ठा vq_info_block_legacy अणु
	__u64 queue;
	__u32 align;
	__u16 index;
	__u16 num;
पूर्ण __packed;

काष्ठा vq_info_block अणु
	__u64 desc;
	__u32 res0;
	__u16 index;
	__u16 num;
	__u64 avail;
	__u64 used;
पूर्ण __packed;

काष्ठा virtio_feature_desc अणु
	__le32 features;
	__u8 index;
पूर्ण __packed;

काष्ठा virtio_thinपूर्णांक_area अणु
	अचिन्हित दीर्घ summary_indicator;
	अचिन्हित दीर्घ indicator;
	u64 bit_nr;
	u8 isc;
पूर्ण __packed;

काष्ठा virtio_rev_info अणु
	__u16 revision;
	__u16 length;
	__u8 data[];
पूर्ण;

/* the highest virtio-ccw revision we support */
#घोषणा VIRTIO_CCW_REV_MAX 2

काष्ठा virtio_ccw_vq_info अणु
	काष्ठा virtqueue *vq;
	पूर्णांक num;
	जोड़ अणु
		काष्ठा vq_info_block s;
		काष्ठा vq_info_block_legacy l;
	पूर्ण *info_block;
	पूर्णांक bit_nr;
	काष्ठा list_head node;
	दीर्घ cookie;
पूर्ण;

#घोषणा VIRTIO_AIRQ_ISC IO_SCH_ISC /* inherit from subchannel */

#घोषणा VIRTIO_IV_BITS (L1_CACHE_BYTES * 8)
#घोषणा MAX_AIRQ_AREAS 20

अटल पूर्णांक virtio_ccw_use_airq = 1;

काष्ठा airq_info अणु
	rwlock_t lock;
	u8 summary_indicator_idx;
	काष्ठा airq_काष्ठा airq;
	काष्ठा airq_iv *aiv;
पूर्ण;
अटल काष्ठा airq_info *airq_areas[MAX_AIRQ_AREAS];
अटल DEFINE_MUTEX(airq_areas_lock);

अटल u8 *summary_indicators;

अटल अंतरभूत u8 *get_summary_indicator(काष्ठा airq_info *info)
अणु
	वापस summary_indicators + info->summary_indicator_idx;
पूर्ण

#घोषणा CCW_CMD_SET_VQ 0x13
#घोषणा CCW_CMD_VDEV_RESET 0x33
#घोषणा CCW_CMD_SET_IND 0x43
#घोषणा CCW_CMD_SET_CONF_IND 0x53
#घोषणा CCW_CMD_READ_FEAT 0x12
#घोषणा CCW_CMD_WRITE_FEAT 0x11
#घोषणा CCW_CMD_READ_CONF 0x22
#घोषणा CCW_CMD_WRITE_CONF 0x21
#घोषणा CCW_CMD_WRITE_STATUS 0x31
#घोषणा CCW_CMD_READ_VQ_CONF 0x32
#घोषणा CCW_CMD_READ_STATUS 0x72
#घोषणा CCW_CMD_SET_IND_ADAPTER 0x73
#घोषणा CCW_CMD_SET_VIRTIO_REV 0x83

#घोषणा VIRTIO_CCW_DOING_SET_VQ 0x00010000
#घोषणा VIRTIO_CCW_DOING_RESET 0x00040000
#घोषणा VIRTIO_CCW_DOING_READ_FEAT 0x00080000
#घोषणा VIRTIO_CCW_DOING_WRITE_FEAT 0x00100000
#घोषणा VIRTIO_CCW_DOING_READ_CONFIG 0x00200000
#घोषणा VIRTIO_CCW_DOING_WRITE_CONFIG 0x00400000
#घोषणा VIRTIO_CCW_DOING_WRITE_STATUS 0x00800000
#घोषणा VIRTIO_CCW_DOING_SET_IND 0x01000000
#घोषणा VIRTIO_CCW_DOING_READ_VQ_CONF 0x02000000
#घोषणा VIRTIO_CCW_DOING_SET_CONF_IND 0x04000000
#घोषणा VIRTIO_CCW_DOING_SET_IND_ADAPTER 0x08000000
#घोषणा VIRTIO_CCW_DOING_SET_VIRTIO_REV 0x10000000
#घोषणा VIRTIO_CCW_DOING_READ_STATUS 0x20000000
#घोषणा VIRTIO_CCW_INTPARM_MASK 0xffff0000

अटल काष्ठा virtio_ccw_device *to_vc_device(काष्ठा virtio_device *vdev)
अणु
	वापस container_of(vdev, काष्ठा virtio_ccw_device, vdev);
पूर्ण

अटल व्योम drop_airq_indicator(काष्ठा virtqueue *vq, काष्ठा airq_info *info)
अणु
	अचिन्हित दीर्घ i, flags;

	ग_लिखो_lock_irqsave(&info->lock, flags);
	क्रम (i = 0; i < airq_iv_end(info->aiv); i++) अणु
		अगर (vq == (व्योम *)airq_iv_get_ptr(info->aiv, i)) अणु
			airq_iv_मुक्त_bit(info->aiv, i);
			airq_iv_set_ptr(info->aiv, i, 0);
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_irqrestore(&info->lock, flags);
पूर्ण

अटल व्योम virtio_airq_handler(काष्ठा airq_काष्ठा *airq, bool भग्नing)
अणु
	काष्ठा airq_info *info = container_of(airq, काष्ठा airq_info, airq);
	अचिन्हित दीर्घ ai;

	inc_irq_stat(IRQIO_VAI);
	पढ़ो_lock(&info->lock);
	/* Walk through indicators field, summary indicator active. */
	क्रम (ai = 0;;) अणु
		ai = airq_iv_scan(info->aiv, ai, airq_iv_end(info->aiv));
		अगर (ai == -1UL)
			अवरोध;
		vring_पूर्णांकerrupt(0, (व्योम *)airq_iv_get_ptr(info->aiv, ai));
	पूर्ण
	*(get_summary_indicator(info)) = 0;
	smp_wmb();
	/* Walk through indicators field, summary indicator not active. */
	क्रम (ai = 0;;) अणु
		ai = airq_iv_scan(info->aiv, ai, airq_iv_end(info->aiv));
		अगर (ai == -1UL)
			अवरोध;
		vring_पूर्णांकerrupt(0, (व्योम *)airq_iv_get_ptr(info->aiv, ai));
	पूर्ण
	पढ़ो_unlock(&info->lock);
पूर्ण

अटल काष्ठा airq_info *new_airq_info(पूर्णांक index)
अणु
	काष्ठा airq_info *info;
	पूर्णांक rc;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस शून्य;
	rwlock_init(&info->lock);
	info->aiv = airq_iv_create(VIRTIO_IV_BITS, AIRQ_IV_ALLOC | AIRQ_IV_PTR
				   | AIRQ_IV_CACHELINE);
	अगर (!info->aiv) अणु
		kमुक्त(info);
		वापस शून्य;
	पूर्ण
	info->airq.handler = virtio_airq_handler;
	info->summary_indicator_idx = index;
	info->airq.lsi_ptr = get_summary_indicator(info);
	info->airq.lsi_mask = 0xff;
	info->airq.isc = VIRTIO_AIRQ_ISC;
	rc = रेजिस्टर_adapter_पूर्णांकerrupt(&info->airq);
	अगर (rc) अणु
		airq_iv_release(info->aiv);
		kमुक्त(info);
		वापस शून्य;
	पूर्ण
	वापस info;
पूर्ण

अटल अचिन्हित दीर्घ get_airq_indicator(काष्ठा virtqueue *vqs[], पूर्णांक nvqs,
					u64 *first, व्योम **airq_info)
अणु
	पूर्णांक i, j;
	काष्ठा airq_info *info;
	अचिन्हित दीर्घ indicator_addr = 0;
	अचिन्हित दीर्घ bit, flags;

	क्रम (i = 0; i < MAX_AIRQ_AREAS && !indicator_addr; i++) अणु
		mutex_lock(&airq_areas_lock);
		अगर (!airq_areas[i])
			airq_areas[i] = new_airq_info(i);
		info = airq_areas[i];
		mutex_unlock(&airq_areas_lock);
		अगर (!info)
			वापस 0;
		ग_लिखो_lock_irqsave(&info->lock, flags);
		bit = airq_iv_alloc(info->aiv, nvqs);
		अगर (bit == -1UL) अणु
			/* Not enough vacancies. */
			ग_लिखो_unlock_irqrestore(&info->lock, flags);
			जारी;
		पूर्ण
		*first = bit;
		*airq_info = info;
		indicator_addr = (अचिन्हित दीर्घ)info->aiv->vector;
		क्रम (j = 0; j < nvqs; j++) अणु
			airq_iv_set_ptr(info->aiv, bit + j,
					(अचिन्हित दीर्घ)vqs[j]);
		पूर्ण
		ग_लिखो_unlock_irqrestore(&info->lock, flags);
	पूर्ण
	वापस indicator_addr;
पूर्ण

अटल व्योम virtio_ccw_drop_indicators(काष्ठा virtio_ccw_device *vcdev)
अणु
	काष्ठा virtio_ccw_vq_info *info;

	अगर (!vcdev->airq_info)
		वापस;
	list_क्रम_each_entry(info, &vcdev->virtqueues, node)
		drop_airq_indicator(info->vq, vcdev->airq_info);
पूर्ण

अटल पूर्णांक करोing_io(काष्ठा virtio_ccw_device *vcdev, __u32 flag)
अणु
	अचिन्हित दीर्घ flags;
	__u32 ret;

	spin_lock_irqsave(get_ccwdev_lock(vcdev->cdev), flags);
	अगर (vcdev->err)
		ret = 0;
	अन्यथा
		ret = vcdev->curr_io & flag;
	spin_unlock_irqrestore(get_ccwdev_lock(vcdev->cdev), flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ccw_io_helper(काष्ठा virtio_ccw_device *vcdev,
			 काष्ठा ccw1 *ccw, __u32 पूर्णांकparm)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	पूर्णांक flag = पूर्णांकparm & VIRTIO_CCW_INTPARM_MASK;

	mutex_lock(&vcdev->io_lock);
	करो अणु
		spin_lock_irqsave(get_ccwdev_lock(vcdev->cdev), flags);
		ret = ccw_device_start(vcdev->cdev, ccw, पूर्णांकparm, 0, 0);
		अगर (!ret) अणु
			अगर (!vcdev->curr_io)
				vcdev->err = 0;
			vcdev->curr_io |= flag;
		पूर्ण
		spin_unlock_irqrestore(get_ccwdev_lock(vcdev->cdev), flags);
		cpu_relax();
	पूर्ण जबतक (ret == -EBUSY);
	रुको_event(vcdev->रुको_q, करोing_io(vcdev, flag) == 0);
	ret = ret ? ret : vcdev->err;
	mutex_unlock(&vcdev->io_lock);
	वापस ret;
पूर्ण

अटल व्योम virtio_ccw_drop_indicator(काष्ठा virtio_ccw_device *vcdev,
				      काष्ठा ccw1 *ccw)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ *indicatorp = शून्य;
	काष्ठा virtio_thinपूर्णांक_area *thinपूर्णांक_area = शून्य;
	काष्ठा airq_info *airq_info = vcdev->airq_info;

	अगर (vcdev->is_thinपूर्णांक) अणु
		thinपूर्णांक_area = ccw_device_dma_zalloc(vcdev->cdev,
						     माप(*thinपूर्णांक_area));
		अगर (!thinपूर्णांक_area)
			वापस;
		thinपूर्णांक_area->summary_indicator =
			(अचिन्हित दीर्घ) get_summary_indicator(airq_info);
		thinपूर्णांक_area->isc = VIRTIO_AIRQ_ISC;
		ccw->cmd_code = CCW_CMD_SET_IND_ADAPTER;
		ccw->count = माप(*thinपूर्णांक_area);
		ccw->cda = (__u32)(अचिन्हित दीर्घ) thinपूर्णांक_area;
	पूर्ण अन्यथा अणु
		/* payload is the address of the indicators */
		indicatorp = ccw_device_dma_zalloc(vcdev->cdev,
						   माप(indicators(vcdev)));
		अगर (!indicatorp)
			वापस;
		*indicatorp = 0;
		ccw->cmd_code = CCW_CMD_SET_IND;
		ccw->count = माप(indicators(vcdev));
		ccw->cda = (__u32)(अचिन्हित दीर्घ) indicatorp;
	पूर्ण
	/* Deरेजिस्टर indicators from host. */
	*indicators(vcdev) = 0;
	ccw->flags = 0;
	ret = ccw_io_helper(vcdev, ccw,
			    vcdev->is_thinपूर्णांक ?
			    VIRTIO_CCW_DOING_SET_IND_ADAPTER :
			    VIRTIO_CCW_DOING_SET_IND);
	अगर (ret && (ret != -ENODEV))
		dev_info(&vcdev->cdev->dev,
			 "Failed to deregister indicators (%d)\n", ret);
	अन्यथा अगर (vcdev->is_thinपूर्णांक)
		virtio_ccw_drop_indicators(vcdev);
	ccw_device_dma_मुक्त(vcdev->cdev, indicatorp, माप(indicators(vcdev)));
	ccw_device_dma_मुक्त(vcdev->cdev, thinपूर्णांक_area, माप(*thinपूर्णांक_area));
पूर्ण

अटल अंतरभूत दीर्घ __करो_kvm_notअगरy(काष्ठा subchannel_id schid,
				   अचिन्हित दीर्घ queue_index,
				   दीर्घ cookie)
अणु
	रेजिस्टर अचिन्हित दीर्घ __nr यंत्र("1") = KVM_S390_VIRTIO_CCW_NOTIFY;
	रेजिस्टर काष्ठा subchannel_id __schid यंत्र("2") = schid;
	रेजिस्टर अचिन्हित दीर्घ __index यंत्र("3") = queue_index;
	रेजिस्टर दीर्घ __rc यंत्र("2");
	रेजिस्टर दीर्घ __cookie यंत्र("4") = cookie;

	यंत्र अस्थिर ("diag 2,4,0x500\n"
		      : "=d" (__rc) : "d" (__nr), "d" (__schid), "d" (__index),
		      "d"(__cookie)
		      : "memory", "cc");
	वापस __rc;
पूर्ण

अटल अंतरभूत दीर्घ करो_kvm_notअगरy(काष्ठा subchannel_id schid,
				 अचिन्हित दीर्घ queue_index,
				 दीर्घ cookie)
अणु
	diag_stat_inc(DIAG_STAT_X500);
	वापस __करो_kvm_notअगरy(schid, queue_index, cookie);
पूर्ण

अटल bool virtio_ccw_kvm_notअगरy(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_ccw_vq_info *info = vq->priv;
	काष्ठा virtio_ccw_device *vcdev;
	काष्ठा subchannel_id schid;

	vcdev = to_vc_device(info->vq->vdev);
	ccw_device_get_schid(vcdev->cdev, &schid);
	info->cookie = करो_kvm_notअगरy(schid, vq->index, info->cookie);
	अगर (info->cookie < 0)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक virtio_ccw_पढ़ो_vq_conf(काष्ठा virtio_ccw_device *vcdev,
				   काष्ठा ccw1 *ccw, पूर्णांक index)
अणु
	पूर्णांक ret;

	vcdev->dma_area->config_block.index = index;
	ccw->cmd_code = CCW_CMD_READ_VQ_CONF;
	ccw->flags = 0;
	ccw->count = माप(काष्ठा vq_config_block);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)(&vcdev->dma_area->config_block);
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_READ_VQ_CONF);
	अगर (ret)
		वापस ret;
	वापस vcdev->dma_area->config_block.num ?: -ENOENT;
पूर्ण

अटल व्योम virtio_ccw_del_vq(काष्ठा virtqueue *vq, काष्ठा ccw1 *ccw)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vq->vdev);
	काष्ठा virtio_ccw_vq_info *info = vq->priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	अचिन्हित पूर्णांक index = vq->index;

	/* Remove from our list. */
	spin_lock_irqsave(&vcdev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vcdev->lock, flags);

	/* Release from host. */
	अगर (vcdev->revision == 0) अणु
		info->info_block->l.queue = 0;
		info->info_block->l.align = 0;
		info->info_block->l.index = index;
		info->info_block->l.num = 0;
		ccw->count = माप(info->info_block->l);
	पूर्ण अन्यथा अणु
		info->info_block->s.desc = 0;
		info->info_block->s.index = index;
		info->info_block->s.num = 0;
		info->info_block->s.avail = 0;
		info->info_block->s.used = 0;
		ccw->count = माप(info->info_block->s);
	पूर्ण
	ccw->cmd_code = CCW_CMD_SET_VQ;
	ccw->flags = 0;
	ccw->cda = (__u32)(अचिन्हित दीर्घ)(info->info_block);
	ret = ccw_io_helper(vcdev, ccw,
			    VIRTIO_CCW_DOING_SET_VQ | index);
	/*
	 * -ENODEV isn't considered an error: The device is gone anyway.
	 * This may happen on device detach.
	 */
	अगर (ret && (ret != -ENODEV))
		dev_warn(&vq->vdev->dev, "Error %d while deleting queue %d\n",
			 ret, index);

	vring_del_virtqueue(vq);
	ccw_device_dma_मुक्त(vcdev->cdev, info->info_block,
			    माप(*info->info_block));
	kमुक्त(info);
पूर्ण

अटल व्योम virtio_ccw_del_vqs(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtqueue *vq, *n;
	काष्ठा ccw1 *ccw;
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस;

	virtio_ccw_drop_indicator(vcdev, ccw);

	list_क्रम_each_entry_safe(vq, n, &vdev->vqs, list)
		virtio_ccw_del_vq(vq, ccw);

	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
पूर्ण

अटल काष्ठा virtqueue *virtio_ccw_setup_vq(काष्ठा virtio_device *vdev,
					     पूर्णांक i, vq_callback_t *callback,
					     स्थिर अक्षर *name, bool ctx,
					     काष्ठा ccw1 *ccw)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	पूर्णांक err;
	काष्ठा virtqueue *vq = शून्य;
	काष्ठा virtio_ccw_vq_info *info;
	u64 queue;
	अचिन्हित दीर्घ flags;
	bool may_reduce;

	/* Allocate queue. */
	info = kzalloc(माप(काष्ठा virtio_ccw_vq_info), GFP_KERNEL);
	अगर (!info) अणु
		dev_warn(&vcdev->cdev->dev, "no info\n");
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण
	info->info_block = ccw_device_dma_zalloc(vcdev->cdev,
						 माप(*info->info_block));
	अगर (!info->info_block) अणु
		dev_warn(&vcdev->cdev->dev, "no info block\n");
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण
	info->num = virtio_ccw_पढ़ो_vq_conf(vcdev, ccw, i);
	अगर (info->num < 0) अणु
		err = info->num;
		जाओ out_err;
	पूर्ण
	may_reduce = vcdev->revision > 0;
	vq = vring_create_virtqueue(i, info->num, KVM_VIRTIO_CCW_RING_ALIGN,
				    vdev, true, may_reduce, ctx,
				    virtio_ccw_kvm_notअगरy, callback, name);

	अगर (!vq) अणु
		/* For now, we fail अगर we can't get the requested size. */
		dev_warn(&vcdev->cdev->dev, "no vq\n");
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण
	/* it may have been reduced */
	info->num = virtqueue_get_vring_size(vq);

	/* Register it with the host. */
	queue = virtqueue_get_desc_addr(vq);
	अगर (vcdev->revision == 0) अणु
		info->info_block->l.queue = queue;
		info->info_block->l.align = KVM_VIRTIO_CCW_RING_ALIGN;
		info->info_block->l.index = i;
		info->info_block->l.num = info->num;
		ccw->count = माप(info->info_block->l);
	पूर्ण अन्यथा अणु
		info->info_block->s.desc = queue;
		info->info_block->s.index = i;
		info->info_block->s.num = info->num;
		info->info_block->s.avail = (__u64)virtqueue_get_avail_addr(vq);
		info->info_block->s.used = (__u64)virtqueue_get_used_addr(vq);
		ccw->count = माप(info->info_block->s);
	पूर्ण
	ccw->cmd_code = CCW_CMD_SET_VQ;
	ccw->flags = 0;
	ccw->cda = (__u32)(अचिन्हित दीर्घ)(info->info_block);
	err = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_SET_VQ | i);
	अगर (err) अणु
		dev_warn(&vcdev->cdev->dev, "SET_VQ failed\n");
		जाओ out_err;
	पूर्ण

	info->vq = vq;
	vq->priv = info;

	/* Save it to our list. */
	spin_lock_irqsave(&vcdev->lock, flags);
	list_add(&info->node, &vcdev->virtqueues);
	spin_unlock_irqrestore(&vcdev->lock, flags);

	वापस vq;

out_err:
	अगर (vq)
		vring_del_virtqueue(vq);
	अगर (info) अणु
		ccw_device_dma_मुक्त(vcdev->cdev, info->info_block,
				    माप(*info->info_block));
	पूर्ण
	kमुक्त(info);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक virtio_ccw_रेजिस्टर_adapter_ind(काष्ठा virtio_ccw_device *vcdev,
					   काष्ठा virtqueue *vqs[], पूर्णांक nvqs,
					   काष्ठा ccw1 *ccw)
अणु
	पूर्णांक ret;
	काष्ठा virtio_thinपूर्णांक_area *thinपूर्णांक_area = शून्य;
	काष्ठा airq_info *info;

	thinपूर्णांक_area = ccw_device_dma_zalloc(vcdev->cdev,
					     माप(*thinपूर्णांक_area));
	अगर (!thinपूर्णांक_area) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	/* Try to get an indicator. */
	thinपूर्णांक_area->indicator = get_airq_indicator(vqs, nvqs,
						     &thinपूर्णांक_area->bit_nr,
						     &vcdev->airq_info);
	अगर (!thinपूर्णांक_area->indicator) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण
	info = vcdev->airq_info;
	thinपूर्णांक_area->summary_indicator =
		(अचिन्हित दीर्घ) get_summary_indicator(info);
	thinपूर्णांक_area->isc = VIRTIO_AIRQ_ISC;
	ccw->cmd_code = CCW_CMD_SET_IND_ADAPTER;
	ccw->flags = CCW_FLAG_SLI;
	ccw->count = माप(*thinपूर्णांक_area);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)thinपूर्णांक_area;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_SET_IND_ADAPTER);
	अगर (ret) अणु
		अगर (ret == -EOPNOTSUPP) अणु
			/*
			 * The host करोes not support adapter पूर्णांकerrupts
			 * क्रम virtio-ccw, stop trying.
			 */
			virtio_ccw_use_airq = 0;
			pr_info("Adapter interrupts unsupported on host\n");
		पूर्ण अन्यथा
			dev_warn(&vcdev->cdev->dev,
				 "enabling adapter interrupts = %d\n", ret);
		virtio_ccw_drop_indicators(vcdev);
	पूर्ण
out:
	ccw_device_dma_मुक्त(vcdev->cdev, thinपूर्णांक_area, माप(*thinपूर्णांक_area));
	वापस ret;
पूर्ण

अटल पूर्णांक virtio_ccw_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
			       काष्ठा virtqueue *vqs[],
			       vq_callback_t *callbacks[],
			       स्थिर अक्षर * स्थिर names[],
			       स्थिर bool *ctx,
			       काष्ठा irq_affinity *desc)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	अचिन्हित दीर्घ *indicatorp = शून्य;
	पूर्णांक ret, i, queue_idx = 0;
	काष्ठा ccw1 *ccw;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस -ENOMEM;

	क्रम (i = 0; i < nvqs; ++i) अणु
		अगर (!names[i]) अणु
			vqs[i] = शून्य;
			जारी;
		पूर्ण

		vqs[i] = virtio_ccw_setup_vq(vdev, queue_idx++, callbacks[i],
					     names[i], ctx ? ctx[i] : false,
					     ccw);
		अगर (IS_ERR(vqs[i])) अणु
			ret = PTR_ERR(vqs[i]);
			vqs[i] = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण
	ret = -ENOMEM;
	/*
	 * We need a data area under 2G to communicate. Our payload is
	 * the address of the indicators.
	*/
	indicatorp = ccw_device_dma_zalloc(vcdev->cdev,
					   माप(indicators(vcdev)));
	अगर (!indicatorp)
		जाओ out;
	*indicatorp = (अचिन्हित दीर्घ) indicators(vcdev);
	अगर (vcdev->is_thinपूर्णांक) अणु
		ret = virtio_ccw_रेजिस्टर_adapter_ind(vcdev, vqs, nvqs, ccw);
		अगर (ret)
			/* no error, just fall back to legacy पूर्णांकerrupts */
			vcdev->is_thinपूर्णांक = false;
	पूर्ण
	अगर (!vcdev->is_thinपूर्णांक) अणु
		/* Register queue indicators with host. */
		*indicators(vcdev) = 0;
		ccw->cmd_code = CCW_CMD_SET_IND;
		ccw->flags = 0;
		ccw->count = माप(indicators(vcdev));
		ccw->cda = (__u32)(अचिन्हित दीर्घ) indicatorp;
		ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_SET_IND);
		अगर (ret)
			जाओ out;
	पूर्ण
	/* Register indicators2 with host क्रम config changes */
	*indicatorp = (अचिन्हित दीर्घ) indicators2(vcdev);
	*indicators2(vcdev) = 0;
	ccw->cmd_code = CCW_CMD_SET_CONF_IND;
	ccw->flags = 0;
	ccw->count = माप(indicators2(vcdev));
	ccw->cda = (__u32)(अचिन्हित दीर्घ) indicatorp;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_SET_CONF_IND);
	अगर (ret)
		जाओ out;

	अगर (indicatorp)
		ccw_device_dma_मुक्त(vcdev->cdev, indicatorp,
				    माप(indicators(vcdev)));
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
	वापस 0;
out:
	अगर (indicatorp)
		ccw_device_dma_मुक्त(vcdev->cdev, indicatorp,
				    माप(indicators(vcdev)));
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
	virtio_ccw_del_vqs(vdev);
	वापस ret;
पूर्ण

अटल व्योम virtio_ccw_reset(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	काष्ठा ccw1 *ccw;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस;

	/* Zero status bits. */
	vcdev->dma_area->status = 0;

	/* Send a reset ccw on device. */
	ccw->cmd_code = CCW_CMD_VDEV_RESET;
	ccw->flags = 0;
	ccw->count = 0;
	ccw->cda = 0;
	ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_RESET);
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
पूर्ण

अटल u64 virtio_ccw_get_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	काष्ठा virtio_feature_desc *features;
	पूर्णांक ret;
	u64 rc;
	काष्ठा ccw1 *ccw;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस 0;

	features = ccw_device_dma_zalloc(vcdev->cdev, माप(*features));
	अगर (!features) अणु
		rc = 0;
		जाओ out_मुक्त;
	पूर्ण
	/* Read the feature bits from the host. */
	features->index = 0;
	ccw->cmd_code = CCW_CMD_READ_FEAT;
	ccw->flags = 0;
	ccw->count = माप(*features);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)features;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_READ_FEAT);
	अगर (ret) अणु
		rc = 0;
		जाओ out_मुक्त;
	पूर्ण

	rc = le32_to_cpu(features->features);

	अगर (vcdev->revision == 0)
		जाओ out_मुक्त;

	/* Read second half of the feature bits from the host. */
	features->index = 1;
	ccw->cmd_code = CCW_CMD_READ_FEAT;
	ccw->flags = 0;
	ccw->count = माप(*features);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)features;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_READ_FEAT);
	अगर (ret == 0)
		rc |= (u64)le32_to_cpu(features->features) << 32;

out_मुक्त:
	ccw_device_dma_मुक्त(vcdev->cdev, features, माप(*features));
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
	वापस rc;
पूर्ण

अटल व्योम ccw_transport_features(काष्ठा virtio_device *vdev)
अणु
	/*
	 * Currently nothing to करो here.
	 */
पूर्ण

अटल पूर्णांक virtio_ccw_finalize_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	काष्ठा virtio_feature_desc *features;
	काष्ठा ccw1 *ccw;
	पूर्णांक ret;

	अगर (vcdev->revision >= 1 &&
	    !__virtio_test_bit(vdev, VIRTIO_F_VERSION_1)) अणु
		dev_err(&vdev->dev, "virtio: device uses revision 1 "
			"but does not have VIRTIO_F_VERSION_1\n");
		वापस -EINVAL;
	पूर्ण

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस -ENOMEM;

	features = ccw_device_dma_zalloc(vcdev->cdev, माप(*features));
	अगर (!features) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	/* Give virtio_ring a chance to accept features. */
	vring_transport_features(vdev);

	/* Give virtio_ccw a chance to accept features. */
	ccw_transport_features(vdev);

	features->index = 0;
	features->features = cpu_to_le32((u32)vdev->features);
	/* Write the first half of the feature bits to the host. */
	ccw->cmd_code = CCW_CMD_WRITE_FEAT;
	ccw->flags = 0;
	ccw->count = माप(*features);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)features;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_WRITE_FEAT);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (vcdev->revision == 0)
		जाओ out_मुक्त;

	features->index = 1;
	features->features = cpu_to_le32(vdev->features >> 32);
	/* Write the second half of the feature bits to the host. */
	ccw->cmd_code = CCW_CMD_WRITE_FEAT;
	ccw->flags = 0;
	ccw->count = माप(*features);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)features;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_WRITE_FEAT);

out_मुक्त:
	ccw_device_dma_मुक्त(vcdev->cdev, features, माप(*features));
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));

	वापस ret;
पूर्ण

अटल व्योम virtio_ccw_get_config(काष्ठा virtio_device *vdev,
				  अचिन्हित पूर्णांक offset, व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	पूर्णांक ret;
	काष्ठा ccw1 *ccw;
	व्योम *config_area;
	अचिन्हित दीर्घ flags;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस;

	config_area = ccw_device_dma_zalloc(vcdev->cdev,
					    VIRTIO_CCW_CONFIG_SIZE);
	अगर (!config_area)
		जाओ out_मुक्त;

	/* Read the config area from the host. */
	ccw->cmd_code = CCW_CMD_READ_CONF;
	ccw->flags = 0;
	ccw->count = offset + len;
	ccw->cda = (__u32)(अचिन्हित दीर्घ)config_area;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_READ_CONFIG);
	अगर (ret)
		जाओ out_मुक्त;

	spin_lock_irqsave(&vcdev->lock, flags);
	स_नकल(vcdev->config, config_area, offset + len);
	अगर (vcdev->config_पढ़ोy < offset + len)
		vcdev->config_पढ़ोy = offset + len;
	spin_unlock_irqrestore(&vcdev->lock, flags);
	अगर (buf)
		स_नकल(buf, config_area + offset, len);

out_मुक्त:
	ccw_device_dma_मुक्त(vcdev->cdev, config_area, VIRTIO_CCW_CONFIG_SIZE);
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
पूर्ण

अटल व्योम virtio_ccw_set_config(काष्ठा virtio_device *vdev,
				  अचिन्हित पूर्णांक offset, स्थिर व्योम *buf,
				  अचिन्हित len)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	काष्ठा ccw1 *ccw;
	व्योम *config_area;
	अचिन्हित दीर्घ flags;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस;

	config_area = ccw_device_dma_zalloc(vcdev->cdev,
					    VIRTIO_CCW_CONFIG_SIZE);
	अगर (!config_area)
		जाओ out_मुक्त;

	/* Make sure we करोn't overग_लिखो fields. */
	अगर (vcdev->config_पढ़ोy < offset)
		virtio_ccw_get_config(vdev, 0, शून्य, offset);
	spin_lock_irqsave(&vcdev->lock, flags);
	स_नकल(&vcdev->config[offset], buf, len);
	/* Write the config area to the host. */
	स_नकल(config_area, vcdev->config, माप(vcdev->config));
	spin_unlock_irqrestore(&vcdev->lock, flags);
	ccw->cmd_code = CCW_CMD_WRITE_CONF;
	ccw->flags = 0;
	ccw->count = offset + len;
	ccw->cda = (__u32)(अचिन्हित दीर्घ)config_area;
	ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_WRITE_CONFIG);

out_मुक्त:
	ccw_device_dma_मुक्त(vcdev->cdev, config_area, VIRTIO_CCW_CONFIG_SIZE);
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
पूर्ण

अटल u8 virtio_ccw_get_status(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	u8 old_status = vcdev->dma_area->status;
	काष्ठा ccw1 *ccw;

	अगर (vcdev->revision < 2)
		वापस vcdev->dma_area->status;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस old_status;

	ccw->cmd_code = CCW_CMD_READ_STATUS;
	ccw->flags = 0;
	ccw->count = माप(vcdev->dma_area->status);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)&vcdev->dma_area->status;
	ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_READ_STATUS);
/*
 * If the channel program failed (should only happen अगर the device
 * was hotunplugged, and then we clean up via the machine check
 * handler anyway), vcdev->dma_area->status was not overwritten and we just
 * वापस the old status, which is fine.
*/
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));

	वापस vcdev->dma_area->status;
पूर्ण

अटल व्योम virtio_ccw_set_status(काष्ठा virtio_device *vdev, u8 status)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);
	u8 old_status = vcdev->dma_area->status;
	काष्ठा ccw1 *ccw;
	पूर्णांक ret;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस;

	/* Write the status to the host. */
	vcdev->dma_area->status = status;
	ccw->cmd_code = CCW_CMD_WRITE_STATUS;
	ccw->flags = 0;
	ccw->count = माप(status);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)&vcdev->dma_area->status;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_WRITE_STATUS);
	/* Write failed? We assume status is unchanged. */
	अगर (ret)
		vcdev->dma_area->status = old_status;
	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
पूर्ण

अटल स्थिर अक्षर *virtio_ccw_bus_name(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(vdev);

	वापस dev_name(&vcdev->cdev->dev);
पूर्ण

अटल स्थिर काष्ठा virtio_config_ops virtio_ccw_config_ops = अणु
	.get_features = virtio_ccw_get_features,
	.finalize_features = virtio_ccw_finalize_features,
	.get = virtio_ccw_get_config,
	.set = virtio_ccw_set_config,
	.get_status = virtio_ccw_get_status,
	.set_status = virtio_ccw_set_status,
	.reset = virtio_ccw_reset,
	.find_vqs = virtio_ccw_find_vqs,
	.del_vqs = virtio_ccw_del_vqs,
	.bus_name = virtio_ccw_bus_name,
पूर्ण;


/*
 * ccw bus driver related functions
 */

अटल व्योम virtio_ccw_release_dev(काष्ठा device *_d)
अणु
	काष्ठा virtio_device *dev = dev_to_virtio(_d);
	काष्ठा virtio_ccw_device *vcdev = to_vc_device(dev);

	ccw_device_dma_मुक्त(vcdev->cdev, vcdev->dma_area,
			    माप(*vcdev->dma_area));
	kमुक्त(vcdev);
पूर्ण

अटल पूर्णांक irb_is_error(काष्ठा irb *irb)
अणु
	अगर (scsw_cstat(&irb->scsw) != 0)
		वापस 1;
	अगर (scsw_dstat(&irb->scsw) & ~(DEV_STAT_CHN_END | DEV_STAT_DEV_END))
		वापस 1;
	अगर (scsw_cc(&irb->scsw) != 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा virtqueue *virtio_ccw_vq_by_ind(काष्ठा virtio_ccw_device *vcdev,
					      पूर्णांक index)
अणु
	काष्ठा virtio_ccw_vq_info *info;
	अचिन्हित दीर्घ flags;
	काष्ठा virtqueue *vq;

	vq = शून्य;
	spin_lock_irqsave(&vcdev->lock, flags);
	list_क्रम_each_entry(info, &vcdev->virtqueues, node) अणु
		अगर (info->vq->index == index) अणु
			vq = info->vq;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vcdev->lock, flags);
	वापस vq;
पूर्ण

अटल व्योम virtio_ccw_check_activity(काष्ठा virtio_ccw_device *vcdev,
				      __u32 activity)
अणु
	अगर (vcdev->curr_io & activity) अणु
		चयन (activity) अणु
		हाल VIRTIO_CCW_DOING_READ_FEAT:
		हाल VIRTIO_CCW_DOING_WRITE_FEAT:
		हाल VIRTIO_CCW_DOING_READ_CONFIG:
		हाल VIRTIO_CCW_DOING_WRITE_CONFIG:
		हाल VIRTIO_CCW_DOING_WRITE_STATUS:
		हाल VIRTIO_CCW_DOING_READ_STATUS:
		हाल VIRTIO_CCW_DOING_SET_VQ:
		हाल VIRTIO_CCW_DOING_SET_IND:
		हाल VIRTIO_CCW_DOING_SET_CONF_IND:
		हाल VIRTIO_CCW_DOING_RESET:
		हाल VIRTIO_CCW_DOING_READ_VQ_CONF:
		हाल VIRTIO_CCW_DOING_SET_IND_ADAPTER:
		हाल VIRTIO_CCW_DOING_SET_VIRTIO_REV:
			vcdev->curr_io &= ~activity;
			wake_up(&vcdev->रुको_q);
			अवरोध;
		शेष:
			/* करोn't know what to करो... */
			dev_warn(&vcdev->cdev->dev,
				 "Suspicious activity '%08x'\n", activity);
			WARN_ON(1);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम virtio_ccw_पूर्णांक_handler(काष्ठा ccw_device *cdev,
				   अचिन्हित दीर्घ पूर्णांकparm,
				   काष्ठा irb *irb)
अणु
	__u32 activity = पूर्णांकparm & VIRTIO_CCW_INTPARM_MASK;
	काष्ठा virtio_ccw_device *vcdev = dev_get_drvdata(&cdev->dev);
	पूर्णांक i;
	काष्ठा virtqueue *vq;

	अगर (!vcdev)
		वापस;
	अगर (IS_ERR(irb)) अणु
		vcdev->err = PTR_ERR(irb);
		virtio_ccw_check_activity(vcdev, activity);
		/* Don't poke around indicators, something's wrong. */
		वापस;
	पूर्ण
	/* Check अगर it's a notअगरication from the host. */
	अगर ((पूर्णांकparm == 0) &&
	    (scsw_stctl(&irb->scsw) ==
	     (SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND))) अणु
		/* OK */
	पूर्ण
	अगर (irb_is_error(irb)) अणु
		/* Command reject? */
		अगर ((scsw_dstat(&irb->scsw) & DEV_STAT_UNIT_CHECK) &&
		    (irb->ecw[0] & SNS0_CMD_REJECT))
			vcdev->err = -EOPNOTSUPP;
		अन्यथा
			/* Map everything अन्यथा to -EIO. */
			vcdev->err = -EIO;
	पूर्ण
	virtio_ccw_check_activity(vcdev, activity);
	क्रम_each_set_bit(i, indicators(vcdev),
			 माप(*indicators(vcdev)) * BITS_PER_BYTE) अणु
		/* The bit clear must happen beक्रमe the vring kick. */
		clear_bit(i, indicators(vcdev));
		barrier();
		vq = virtio_ccw_vq_by_ind(vcdev, i);
		vring_पूर्णांकerrupt(0, vq);
	पूर्ण
	अगर (test_bit(0, indicators2(vcdev))) अणु
		virtio_config_changed(&vcdev->vdev);
		clear_bit(0, indicators2(vcdev));
	पूर्ण
पूर्ण

/*
 * We usually want to स्वतःonline all devices, but give the admin
 * a way to exempt devices from this.
 */
#घोषणा __DEV_WORDS ((__MAX_SUBCHANNEL + (8*माप(दीर्घ) - 1)) / \
		     (8*माप(दीर्घ)))
अटल अचिन्हित दीर्घ devs_no_स्वतः[__MAX_SSID + 1][__DEV_WORDS];

अटल अक्षर *no_स्वतः = "";

module_param(no_स्वतः, अक्षरp, 0444);
MODULE_PARM_DESC(no_स्वतः, "list of ccw bus id ranges not to be auto-onlined");

अटल पूर्णांक virtio_ccw_check_स्वतःonline(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_dev_id id;

	ccw_device_get_id(cdev, &id);
	अगर (test_bit(id.devno, devs_no_स्वतः[id.ssid]))
		वापस 0;
	वापस 1;
पूर्ण

अटल व्योम virtio_ccw_स्वतः_online(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा ccw_device *cdev = data;
	पूर्णांक ret;

	ret = ccw_device_set_online(cdev);
	अगर (ret)
		dev_warn(&cdev->dev, "Failed to set online: %d\n", ret);
पूर्ण

अटल पूर्णांक virtio_ccw_probe(काष्ठा ccw_device *cdev)
अणु
	cdev->handler = virtio_ccw_पूर्णांक_handler;

	अगर (virtio_ccw_check_स्वतःonline(cdev))
		async_schedule(virtio_ccw_स्वतः_online, cdev);
	वापस 0;
पूर्ण

अटल काष्ठा virtio_ccw_device *virtio_grab_drvdata(काष्ठा ccw_device *cdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा virtio_ccw_device *vcdev;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	vcdev = dev_get_drvdata(&cdev->dev);
	अगर (!vcdev || vcdev->going_away) अणु
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		वापस शून्य;
	पूर्ण
	vcdev->going_away = true;
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	वापस vcdev;
पूर्ण

अटल व्योम virtio_ccw_हटाओ(काष्ठा ccw_device *cdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा virtio_ccw_device *vcdev = virtio_grab_drvdata(cdev);

	अगर (vcdev && cdev->online) अणु
		अगर (vcdev->device_lost)
			virtio_अवरोध_device(&vcdev->vdev);
		unरेजिस्टर_virtio_device(&vcdev->vdev);
		spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
		dev_set_drvdata(&cdev->dev, शून्य);
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	पूर्ण
	cdev->handler = शून्य;
पूर्ण

अटल पूर्णांक virtio_ccw_offline(काष्ठा ccw_device *cdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा virtio_ccw_device *vcdev = virtio_grab_drvdata(cdev);

	अगर (!vcdev)
		वापस 0;
	अगर (vcdev->device_lost)
		virtio_अवरोध_device(&vcdev->vdev);
	unरेजिस्टर_virtio_device(&vcdev->vdev);
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	dev_set_drvdata(&cdev->dev, शून्य);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_ccw_set_transport_rev(काष्ठा virtio_ccw_device *vcdev)
अणु
	काष्ठा virtio_rev_info *rev;
	काष्ठा ccw1 *ccw;
	पूर्णांक ret;

	ccw = ccw_device_dma_zalloc(vcdev->cdev, माप(*ccw));
	अगर (!ccw)
		वापस -ENOMEM;
	rev = ccw_device_dma_zalloc(vcdev->cdev, माप(*rev));
	अगर (!rev) अणु
		ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
		वापस -ENOMEM;
	पूर्ण

	/* Set transport revision */
	ccw->cmd_code = CCW_CMD_SET_VIRTIO_REV;
	ccw->flags = 0;
	ccw->count = माप(*rev);
	ccw->cda = (__u32)(अचिन्हित दीर्घ)rev;

	vcdev->revision = VIRTIO_CCW_REV_MAX;
	करो अणु
		rev->revision = vcdev->revision;
		/* none of our supported revisions carry payload */
		rev->length = 0;
		ret = ccw_io_helper(vcdev, ccw,
				    VIRTIO_CCW_DOING_SET_VIRTIO_REV);
		अगर (ret == -EOPNOTSUPP) अणु
			अगर (vcdev->revision == 0)
				/*
				 * The host device करोes not support setting
				 * the revision: let's operate it in legacy
				 * mode.
				 */
				ret = 0;
			अन्यथा
				vcdev->revision--;
		पूर्ण
	पूर्ण जबतक (ret == -EOPNOTSUPP);

	ccw_device_dma_मुक्त(vcdev->cdev, ccw, माप(*ccw));
	ccw_device_dma_मुक्त(vcdev->cdev, rev, माप(*rev));
	वापस ret;
पूर्ण

अटल पूर्णांक virtio_ccw_online(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret;
	काष्ठा virtio_ccw_device *vcdev;
	अचिन्हित दीर्घ flags;

	vcdev = kzalloc(माप(*vcdev), GFP_KERNEL);
	अगर (!vcdev) अणु
		dev_warn(&cdev->dev, "Could not get memory for virtio\n");
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	vcdev->vdev.dev.parent = &cdev->dev;
	vcdev->cdev = cdev;
	vcdev->dma_area = ccw_device_dma_zalloc(vcdev->cdev,
						माप(*vcdev->dma_area));
	अगर (!vcdev->dma_area) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	vcdev->is_thinपूर्णांक = virtio_ccw_use_airq; /* at least try */

	vcdev->vdev.dev.release = virtio_ccw_release_dev;
	vcdev->vdev.config = &virtio_ccw_config_ops;
	init_रुकोqueue_head(&vcdev->रुको_q);
	INIT_LIST_HEAD(&vcdev->virtqueues);
	spin_lock_init(&vcdev->lock);
	mutex_init(&vcdev->io_lock);

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	dev_set_drvdata(&cdev->dev, vcdev);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	vcdev->vdev.id.venकरोr = cdev->id.cu_type;
	vcdev->vdev.id.device = cdev->id.cu_model;

	ret = virtio_ccw_set_transport_rev(vcdev);
	अगर (ret)
		जाओ out_मुक्त;

	ret = रेजिस्टर_virtio_device(&vcdev->vdev);
	अगर (ret) अणु
		dev_warn(&cdev->dev, "Failed to register virtio device: %d\n",
			 ret);
		जाओ out_put;
	पूर्ण
	वापस 0;
out_put:
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	dev_set_drvdata(&cdev->dev, शून्य);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	put_device(&vcdev->vdev.dev);
	वापस ret;
out_मुक्त:
	अगर (vcdev) अणु
		ccw_device_dma_मुक्त(vcdev->cdev, vcdev->dma_area,
				    माप(*vcdev->dma_area));
	पूर्ण
	kमुक्त(vcdev);
	वापस ret;
पूर्ण

अटल पूर्णांक virtio_ccw_cio_notअगरy(काष्ठा ccw_device *cdev, पूर्णांक event)
अणु
	पूर्णांक rc;
	काष्ठा virtio_ccw_device *vcdev = dev_get_drvdata(&cdev->dev);

	/*
	 * Make sure vcdev is set
	 * i.e. set_offline/हटाओ callback not alपढ़ोy running
	 */
	अगर (!vcdev)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल CIO_GONE:
		vcdev->device_lost = true;
		rc = NOTIFY_DONE;
		अवरोध;
	हाल CIO_OPER:
		rc = NOTIFY_OK;
		अवरोध;
	शेष:
		rc = NOTIFY_DONE;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा ccw_device_id virtio_ids[] = अणु
	अणु CCW_DEVICE(0x3832, 0) पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा ccw_driver virtio_ccw_driver = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = "virtio_ccw",
	पूर्ण,
	.ids = virtio_ids,
	.probe = virtio_ccw_probe,
	.हटाओ = virtio_ccw_हटाओ,
	.set_offline = virtio_ccw_offline,
	.set_online = virtio_ccw_online,
	.notअगरy = virtio_ccw_cio_notअगरy,
	.पूर्णांक_class = IRQIO_VIR,
पूर्ण;

अटल पूर्णांक __init pure_hex(अक्षर **cp, अचिन्हित पूर्णांक *val, पूर्णांक min_digit,
			   पूर्णांक max_digit, पूर्णांक max_val)
अणु
	पूर्णांक dअगरf;

	dअगरf = 0;
	*val = 0;

	जबतक (dअगरf <= max_digit) अणु
		पूर्णांक value = hex_to_bin(**cp);

		अगर (value < 0)
			अवरोध;
		*val = *val * 16 + value;
		(*cp)++;
		dअगरf++;
	पूर्ण

	अगर ((dअगरf < min_digit) || (dअगरf > max_digit) || (*val > max_val))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक __init parse_busid(अक्षर *str, अचिन्हित पूर्णांक *cssid,
			      अचिन्हित पूर्णांक *ssid, अचिन्हित पूर्णांक *devno)
अणु
	अक्षर *str_work;
	पूर्णांक rc, ret;

	rc = 1;

	अगर (*str == '\0')
		जाओ out;

	str_work = str;
	ret = pure_hex(&str_work, cssid, 1, 2, __MAX_CSSID);
	अगर (ret || (str_work[0] != '.'))
		जाओ out;
	str_work++;
	ret = pure_hex(&str_work, ssid, 1, 1, __MAX_SSID);
	अगर (ret || (str_work[0] != '.'))
		जाओ out;
	str_work++;
	ret = pure_hex(&str_work, devno, 4, 4, __MAX_SUBCHANNEL);
	अगर (ret || (str_work[0] != '\0'))
		जाओ out;

	rc = 0;
out:
	वापस rc;
पूर्ण

अटल व्योम __init no_स्वतः_parse(व्योम)
अणु
	अचिन्हित पूर्णांक from_cssid, to_cssid, from_ssid, to_ssid, from, to;
	अक्षर *parm, *str;
	पूर्णांक rc;

	str = no_स्वतः;
	जबतक ((parm = strsep(&str, ","))) अणु
		rc = parse_busid(strsep(&parm, "-"), &from_cssid,
				 &from_ssid, &from);
		अगर (rc)
			जारी;
		अगर (parm != शून्य) अणु
			rc = parse_busid(parm, &to_cssid,
					 &to_ssid, &to);
			अगर ((from_ssid > to_ssid) ||
			    ((from_ssid == to_ssid) && (from > to)))
				rc = -EINVAL;
		पूर्ण अन्यथा अणु
			to_cssid = from_cssid;
			to_ssid = from_ssid;
			to = from;
		पूर्ण
		अगर (rc)
			जारी;
		जबतक ((from_ssid < to_ssid) ||
		       ((from_ssid == to_ssid) && (from <= to))) अणु
			set_bit(from, devs_no_स्वतः[from_ssid]);
			from++;
			अगर (from > __MAX_SUBCHANNEL) अणु
				from_ssid++;
				from = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init virtio_ccw_init(व्योम)
अणु
	पूर्णांक rc;

	/* parse no_स्वतः string beक्रमe we करो anything further */
	no_स्वतः_parse();

	summary_indicators = cio_dma_zalloc(MAX_AIRQ_AREAS);
	अगर (!summary_indicators)
		वापस -ENOMEM;
	rc = ccw_driver_रेजिस्टर(&virtio_ccw_driver);
	अगर (rc)
		cio_dma_मुक्त(summary_indicators, MAX_AIRQ_AREAS);
	वापस rc;
पूर्ण
device_initcall(virtio_ccw_init);
