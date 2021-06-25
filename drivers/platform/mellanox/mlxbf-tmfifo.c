<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Mellanox BlueField SoC TmFअगरo driver
 *
 * Copyright (C) 2019 Mellanox Technologies
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/efi.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_console.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_net.h>
#समावेश <linux/virtio_ring.h>

#समावेश "mlxbf-tmfifo-regs.h"

/* Vring size. */
#घोषणा MLXBF_TMFIFO_VRING_SIZE			SZ_1K

/* Console Tx buffer size. */
#घोषणा MLXBF_TMFIFO_CON_TX_BUF_SIZE		SZ_32K

/* Console Tx buffer reserved space. */
#घोषणा MLXBF_TMFIFO_CON_TX_BUF_RSV_SIZE	8

/* House-keeping समयr पूर्णांकerval. */
#घोषणा MLXBF_TMFIFO_TIMER_INTERVAL		(HZ / 10)

/* Virtual devices sharing the TM FIFO. */
#घोषणा MLXBF_TMFIFO_VDEV_MAX		(VIRTIO_ID_CONSOLE + 1)

/*
 * Reserve 1/16 of TmFअगरo space, so console messages are not starved by
 * the networking traffic.
 */
#घोषणा MLXBF_TMFIFO_RESERVE_RATIO		16

/* Message with data needs at least two words (क्रम header & data). */
#घोषणा MLXBF_TMFIFO_DATA_MIN_WORDS		2

काष्ठा mlxbf_पंचांगfअगरo;

/**
 * mlxbf_पंचांगfअगरo_vring - Structure of the TmFअगरo भव ring
 * @va: भव address of the ring
 * @dma: dma address of the ring
 * @vq: poपूर्णांकer to the virtio virtqueue
 * @desc: current descriptor of the pending packet
 * @desc_head: head descriptor of the pending packet
 * @cur_len: processed length of the current descriptor
 * @rem_len: reमुख्यing length of the pending packet
 * @pkt_len: total length of the pending packet
 * @next_avail: next avail descriptor id
 * @num: vring size (number of descriptors)
 * @align: vring alignment size
 * @index: vring index
 * @vdev_id: vring virtio id (VIRTIO_ID_xxx)
 * @fअगरo: poपूर्णांकer to the पंचांगfअगरo काष्ठाure
 */
काष्ठा mlxbf_पंचांगfअगरo_vring अणु
	व्योम *va;
	dma_addr_t dma;
	काष्ठा virtqueue *vq;
	काष्ठा vring_desc *desc;
	काष्ठा vring_desc *desc_head;
	पूर्णांक cur_len;
	पूर्णांक rem_len;
	u32 pkt_len;
	u16 next_avail;
	पूर्णांक num;
	पूर्णांक align;
	पूर्णांक index;
	पूर्णांक vdev_id;
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo;
पूर्ण;

/* Interrupt types. */
क्रमागत अणु
	MLXBF_TM_RX_LWM_IRQ,
	MLXBF_TM_RX_HWM_IRQ,
	MLXBF_TM_TX_LWM_IRQ,
	MLXBF_TM_TX_HWM_IRQ,
	MLXBF_TM_MAX_IRQ
पूर्ण;

/* Ring types (Rx & Tx). */
क्रमागत अणु
	MLXBF_TMFIFO_VRING_RX,
	MLXBF_TMFIFO_VRING_TX,
	MLXBF_TMFIFO_VRING_MAX
पूर्ण;

/**
 * mlxbf_पंचांगfअगरo_vdev - Structure of the TmFअगरo भव device
 * @vdev: virtio device, in which the vdev.id.device field has the
 *        VIRTIO_ID_xxx id to distinguish the भव device.
 * @status: status of the device
 * @features: supported features of the device
 * @vrings: array of पंचांगfअगरo vrings of this device
 * @config.cons: भव console config -
 *               select अगर vdev.id.device is VIRTIO_ID_CONSOLE
 * @config.net: भव network config -
 *              select अगर vdev.id.device is VIRTIO_ID_NET
 * @tx_buf: tx buffer used to buffer data beक्रमe writing पूर्णांकo the FIFO
 */
काष्ठा mlxbf_पंचांगfअगरo_vdev अणु
	काष्ठा virtio_device vdev;
	u8 status;
	u64 features;
	काष्ठा mlxbf_पंचांगfअगरo_vring vrings[MLXBF_TMFIFO_VRING_MAX];
	जोड़ अणु
		काष्ठा virtio_console_config cons;
		काष्ठा virtio_net_config net;
	पूर्ण config;
	काष्ठा circ_buf tx_buf;
पूर्ण;

/**
 * mlxbf_पंचांगfअगरo_irq_info - Structure of the पूर्णांकerrupt inक्रमmation
 * @fअगरo: poपूर्णांकer to the पंचांगfअगरo काष्ठाure
 * @irq: पूर्णांकerrupt number
 * @index: index पूर्णांकo the पूर्णांकerrupt array
 */
काष्ठा mlxbf_पंचांगfअगरo_irq_info अणु
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo;
	पूर्णांक irq;
	पूर्णांक index;
पूर्ण;

/**
 * mlxbf_पंचांगfअगरo - Structure of the TmFअगरo
 * @vdev: array of the भव devices running over the TmFअगरo
 * @lock: lock to protect the TmFअगरo access
 * @rx_base: mapped रेजिस्टर base address क्रम the Rx FIFO
 * @tx_base: mapped रेजिस्टर base address क्रम the Tx FIFO
 * @rx_fअगरo_size: number of entries of the Rx FIFO
 * @tx_fअगरo_size: number of entries of the Tx FIFO
 * @pend_events: pending bits क्रम deferred events
 * @irq_info: पूर्णांकerrupt inक्रमmation
 * @work: work काष्ठा क्रम deferred process
 * @समयr: background समयr
 * @vring: Tx/Rx ring
 * @spin_lock: Tx/Rx spin lock
 * @is_पढ़ोy: पढ़ोy flag
 */
काष्ठा mlxbf_पंचांगfअगरo अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *vdev[MLXBF_TMFIFO_VDEV_MAX];
	काष्ठा mutex lock;		/* TmFअगरo lock */
	व्योम __iomem *rx_base;
	व्योम __iomem *tx_base;
	पूर्णांक rx_fअगरo_size;
	पूर्णांक tx_fअगरo_size;
	अचिन्हित दीर्घ pend_events;
	काष्ठा mlxbf_पंचांगfअगरo_irq_info irq_info[MLXBF_TM_MAX_IRQ];
	काष्ठा work_काष्ठा work;
	काष्ठा समयr_list समयr;
	काष्ठा mlxbf_पंचांगfअगरo_vring *vring[2];
	spinlock_t spin_lock[2];	/* spin lock */
	bool is_पढ़ोy;
पूर्ण;

/**
 * mlxbf_पंचांगfअगरo_msg_hdr - Structure of the TmFअगरo message header
 * @type: message type
 * @len: payload length in network byte order. Messages sent पूर्णांकo the FIFO
 *       will be पढ़ो by the other side as data stream in the same byte order.
 *       The length needs to be encoded पूर्णांकo network order so both sides
 *       could understand it.
 */
काष्ठा mlxbf_पंचांगfअगरo_msg_hdr अणु
	u8 type;
	__be16 len;
	u8 unused[5];
पूर्ण __packed __aligned(माप(u64));

/*
 * Default MAC.
 * This MAC address will be पढ़ो from EFI persistent variable अगर configured.
 * It can also be reconfigured with standard Linux tools.
 */
अटल u8 mlxbf_पंचांगfअगरo_net_शेष_mac[ETH_ALEN] = अणु
	0x00, 0x1A, 0xCA, 0xFF, 0xFF, 0x01
पूर्ण;

/* EFI variable name of the MAC address. */
अटल efi_अक्षर16_t mlxbf_पंचांगfअगरo_efi_name[] = L"RshimMacAddr";

/* Maximum L2 header length. */
#घोषणा MLXBF_TMFIFO_NET_L2_OVERHEAD	36

/* Supported virtio-net features. */
#घोषणा MLXBF_TMFIFO_NET_FEATURES \
	(BIT_ULL(VIRTIO_NET_F_MTU) | BIT_ULL(VIRTIO_NET_F_STATUS) | \
	 BIT_ULL(VIRTIO_NET_F_MAC))

#घोषणा mlxbf_vdev_to_पंचांगfअगरo(d) container_of(d, काष्ठा mlxbf_पंचांगfअगरo_vdev, vdev)

/* Free vrings of the FIFO device. */
अटल व्योम mlxbf_पंचांगfअगरo_मुक्त_vrings(काष्ठा mlxbf_पंचांगfअगरo *fअगरo,
				     काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vring *vring;
	पूर्णांक i, size;

	क्रम (i = 0; i < ARRAY_SIZE(पंचांग_vdev->vrings); i++) अणु
		vring = &पंचांग_vdev->vrings[i];
		अगर (vring->va) अणु
			size = vring_size(vring->num, vring->align);
			dma_मुक्त_coherent(पंचांग_vdev->vdev.dev.parent, size,
					  vring->va, vring->dma);
			vring->va = शून्य;
			अगर (vring->vq) अणु
				vring_del_virtqueue(vring->vq);
				vring->vq = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Allocate vrings क्रम the FIFO. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_alloc_vrings(काष्ठा mlxbf_पंचांगfअगरo *fअगरo,
				     काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vring *vring;
	काष्ठा device *dev;
	dma_addr_t dma;
	पूर्णांक i, size;
	व्योम *va;

	क्रम (i = 0; i < ARRAY_SIZE(पंचांग_vdev->vrings); i++) अणु
		vring = &पंचांग_vdev->vrings[i];
		vring->fअगरo = fअगरo;
		vring->num = MLXBF_TMFIFO_VRING_SIZE;
		vring->align = SMP_CACHE_BYTES;
		vring->index = i;
		vring->vdev_id = पंचांग_vdev->vdev.id.device;
		dev = &पंचांग_vdev->vdev.dev;

		size = vring_size(vring->num, vring->align);
		va = dma_alloc_coherent(dev->parent, size, &dma, GFP_KERNEL);
		अगर (!va) अणु
			mlxbf_पंचांगfअगरo_मुक्त_vrings(fअगरo, पंचांग_vdev);
			dev_err(dev->parent, "dma_alloc_coherent failed\n");
			वापस -ENOMEM;
		पूर्ण

		vring->va = va;
		vring->dma = dma;
	पूर्ण

	वापस 0;
पूर्ण

/* Disable पूर्णांकerrupts of the FIFO device. */
अटल व्योम mlxbf_पंचांगfअगरo_disable_irqs(काष्ठा mlxbf_पंचांगfअगरo *fअगरo)
अणु
	पूर्णांक i, irq;

	क्रम (i = 0; i < MLXBF_TM_MAX_IRQ; i++) अणु
		irq = fअगरo->irq_info[i].irq;
		fअगरo->irq_info[i].irq = 0;
		disable_irq(irq);
	पूर्ण
पूर्ण

/* Interrupt handler. */
अटल irqवापस_t mlxbf_पंचांगfअगरo_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_irq_info *irq_info = arg;

	अगर (!test_and_set_bit(irq_info->index, &irq_info->fअगरo->pend_events))
		schedule_work(&irq_info->fअगरo->work);

	वापस IRQ_HANDLED;
पूर्ण

/* Get the next packet descriptor from the vring. */
अटल काष्ठा vring_desc *
mlxbf_पंचांगfअगरo_get_next_desc(काष्ठा mlxbf_पंचांगfअगरo_vring *vring)
अणु
	स्थिर काष्ठा vring *vr = virtqueue_get_vring(vring->vq);
	काष्ठा virtio_device *vdev = vring->vq->vdev;
	अचिन्हित पूर्णांक idx, head;

	अगर (vring->next_avail == virtio16_to_cpu(vdev, vr->avail->idx))
		वापस शून्य;

	/* Make sure 'avail->idx' is visible alपढ़ोy. */
	virtio_rmb(false);

	idx = vring->next_avail % vr->num;
	head = virtio16_to_cpu(vdev, vr->avail->ring[idx]);
	अगर (WARN_ON(head >= vr->num))
		वापस शून्य;

	vring->next_avail++;

	वापस &vr->desc[head];
पूर्ण

/* Release virtio descriptor. */
अटल व्योम mlxbf_पंचांगfअगरo_release_desc(काष्ठा mlxbf_पंचांगfअगरo_vring *vring,
				      काष्ठा vring_desc *desc, u32 len)
अणु
	स्थिर काष्ठा vring *vr = virtqueue_get_vring(vring->vq);
	काष्ठा virtio_device *vdev = vring->vq->vdev;
	u16 idx, vr_idx;

	vr_idx = virtio16_to_cpu(vdev, vr->used->idx);
	idx = vr_idx % vr->num;
	vr->used->ring[idx].id = cpu_to_virtio32(vdev, desc - vr->desc);
	vr->used->ring[idx].len = cpu_to_virtio32(vdev, len);

	/*
	 * Virtio could poll and check the 'idx' to decide whether the desc is
	 * करोne or not. Add a memory barrier here to make sure the update above
	 * completes beक्रमe updating the idx.
	 */
	virtio_mb(false);
	vr->used->idx = cpu_to_virtio16(vdev, vr_idx + 1);
पूर्ण

/* Get the total length of the descriptor chain. */
अटल u32 mlxbf_पंचांगfअगरo_get_pkt_len(काष्ठा mlxbf_पंचांगfअगरo_vring *vring,
				    काष्ठा vring_desc *desc)
अणु
	स्थिर काष्ठा vring *vr = virtqueue_get_vring(vring->vq);
	काष्ठा virtio_device *vdev = vring->vq->vdev;
	u32 len = 0, idx;

	जबतक (desc) अणु
		len += virtio32_to_cpu(vdev, desc->len);
		अगर (!(virtio16_to_cpu(vdev, desc->flags) & VRING_DESC_F_NEXT))
			अवरोध;
		idx = virtio16_to_cpu(vdev, desc->next);
		desc = &vr->desc[idx];
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम mlxbf_पंचांगfअगरo_release_pending_pkt(काष्ठा mlxbf_पंचांगfअगरo_vring *vring)
अणु
	काष्ठा vring_desc *desc_head;
	u32 len = 0;

	अगर (vring->desc_head) अणु
		desc_head = vring->desc_head;
		len = vring->pkt_len;
	पूर्ण अन्यथा अणु
		desc_head = mlxbf_पंचांगfअगरo_get_next_desc(vring);
		len = mlxbf_पंचांगfअगरo_get_pkt_len(vring, desc_head);
	पूर्ण

	अगर (desc_head)
		mlxbf_पंचांगfअगरo_release_desc(vring, desc_head, len);

	vring->pkt_len = 0;
	vring->desc = शून्य;
	vring->desc_head = शून्य;
पूर्ण

अटल व्योम mlxbf_पंचांगfअगरo_init_net_desc(काष्ठा mlxbf_पंचांगfअगरo_vring *vring,
				       काष्ठा vring_desc *desc, bool is_rx)
अणु
	काष्ठा virtio_device *vdev = vring->vq->vdev;
	काष्ठा virtio_net_hdr *net_hdr;

	net_hdr = phys_to_virt(virtio64_to_cpu(vdev, desc->addr));
	स_रखो(net_hdr, 0, माप(*net_hdr));
पूर्ण

/* Get and initialize the next packet. */
अटल काष्ठा vring_desc *
mlxbf_पंचांगfअगरo_get_next_pkt(काष्ठा mlxbf_पंचांगfअगरo_vring *vring, bool is_rx)
अणु
	काष्ठा vring_desc *desc;

	desc = mlxbf_पंचांगfअगरo_get_next_desc(vring);
	अगर (desc && is_rx && vring->vdev_id == VIRTIO_ID_NET)
		mlxbf_पंचांगfअगरo_init_net_desc(vring, desc, is_rx);

	vring->desc_head = desc;
	vring->desc = desc;

	वापस desc;
पूर्ण

/* House-keeping समयr. */
अटल व्योम mlxbf_पंचांगfअगरo_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo = container_of(t, काष्ठा mlxbf_पंचांगfअगरo, समयr);
	पूर्णांक rx, tx;

	rx = !test_and_set_bit(MLXBF_TM_RX_HWM_IRQ, &fअगरo->pend_events);
	tx = !test_and_set_bit(MLXBF_TM_TX_LWM_IRQ, &fअगरo->pend_events);

	अगर (rx || tx)
		schedule_work(&fअगरo->work);

	mod_समयr(&fअगरo->समयr, jअगरfies + MLXBF_TMFIFO_TIMER_INTERVAL);
पूर्ण

/* Copy one console packet पूर्णांकo the output buffer. */
अटल व्योम mlxbf_पंचांगfअगरo_console_output_one(काष्ठा mlxbf_पंचांगfअगरo_vdev *cons,
					    काष्ठा mlxbf_पंचांगfअगरo_vring *vring,
					    काष्ठा vring_desc *desc)
अणु
	स्थिर काष्ठा vring *vr = virtqueue_get_vring(vring->vq);
	काष्ठा virtio_device *vdev = &cons->vdev;
	u32 len, idx, seg;
	व्योम *addr;

	जबतक (desc) अणु
		addr = phys_to_virt(virtio64_to_cpu(vdev, desc->addr));
		len = virtio32_to_cpu(vdev, desc->len);

		seg = CIRC_SPACE_TO_END(cons->tx_buf.head, cons->tx_buf.tail,
					MLXBF_TMFIFO_CON_TX_BUF_SIZE);
		अगर (len <= seg) अणु
			स_नकल(cons->tx_buf.buf + cons->tx_buf.head, addr, len);
		पूर्ण अन्यथा अणु
			स_नकल(cons->tx_buf.buf + cons->tx_buf.head, addr, seg);
			addr += seg;
			स_नकल(cons->tx_buf.buf, addr, len - seg);
		पूर्ण
		cons->tx_buf.head = (cons->tx_buf.head + len) %
			MLXBF_TMFIFO_CON_TX_BUF_SIZE;

		अगर (!(virtio16_to_cpu(vdev, desc->flags) & VRING_DESC_F_NEXT))
			अवरोध;
		idx = virtio16_to_cpu(vdev, desc->next);
		desc = &vr->desc[idx];
	पूर्ण
पूर्ण

/* Copy console data पूर्णांकo the output buffer. */
अटल व्योम mlxbf_पंचांगfअगरo_console_output(काष्ठा mlxbf_पंचांगfअगरo_vdev *cons,
					काष्ठा mlxbf_पंचांगfअगरo_vring *vring)
अणु
	काष्ठा vring_desc *desc;
	u32 len, avail;

	desc = mlxbf_पंचांगfअगरo_get_next_desc(vring);
	जबतक (desc) अणु
		/* Release the packet अगर not enough space. */
		len = mlxbf_पंचांगfअगरo_get_pkt_len(vring, desc);
		avail = CIRC_SPACE(cons->tx_buf.head, cons->tx_buf.tail,
				   MLXBF_TMFIFO_CON_TX_BUF_SIZE);
		अगर (len + MLXBF_TMFIFO_CON_TX_BUF_RSV_SIZE > avail) अणु
			mlxbf_पंचांगfअगरo_release_desc(vring, desc, len);
			अवरोध;
		पूर्ण

		mlxbf_पंचांगfअगरo_console_output_one(cons, vring, desc);
		mlxbf_पंचांगfअगरo_release_desc(vring, desc, len);
		desc = mlxbf_पंचांगfअगरo_get_next_desc(vring);
	पूर्ण
पूर्ण

/* Get the number of available words in Rx FIFO क्रम receiving. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_get_rx_avail(काष्ठा mlxbf_पंचांगfअगरo *fअगरo)
अणु
	u64 sts;

	sts = पढ़ोq(fअगरo->rx_base + MLXBF_TMFIFO_RX_STS);
	वापस FIELD_GET(MLXBF_TMFIFO_RX_STS__COUNT_MASK, sts);
पूर्ण

/* Get the number of available words in the TmFअगरo क्रम sending. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_get_tx_avail(काष्ठा mlxbf_पंचांगfअगरo *fअगरo, पूर्णांक vdev_id)
अणु
	पूर्णांक tx_reserve;
	u32 count;
	u64 sts;

	/* Reserve some room in FIFO क्रम console messages. */
	अगर (vdev_id == VIRTIO_ID_NET)
		tx_reserve = fअगरo->tx_fअगरo_size / MLXBF_TMFIFO_RESERVE_RATIO;
	अन्यथा
		tx_reserve = 1;

	sts = पढ़ोq(fअगरo->tx_base + MLXBF_TMFIFO_TX_STS);
	count = FIELD_GET(MLXBF_TMFIFO_TX_STS__COUNT_MASK, sts);
	वापस fअगरo->tx_fअगरo_size - tx_reserve - count;
पूर्ण

/* Console Tx (move data from the output buffer पूर्णांकo the TmFअगरo). */
अटल व्योम mlxbf_पंचांगfअगरo_console_tx(काष्ठा mlxbf_पंचांगfअगरo *fअगरo, पूर्णांक avail)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_msg_hdr hdr;
	काष्ठा mlxbf_पंचांगfअगरo_vdev *cons;
	अचिन्हित दीर्घ flags;
	पूर्णांक size, seg;
	व्योम *addr;
	u64 data;

	/* Return अगर not enough space available. */
	अगर (avail < MLXBF_TMFIFO_DATA_MIN_WORDS)
		वापस;

	cons = fअगरo->vdev[VIRTIO_ID_CONSOLE];
	अगर (!cons || !cons->tx_buf.buf)
		वापस;

	/* Return अगर no data to send. */
	size = CIRC_CNT(cons->tx_buf.head, cons->tx_buf.tail,
			MLXBF_TMFIFO_CON_TX_BUF_SIZE);
	अगर (size == 0)
		वापस;

	/* Adjust the size to available space. */
	अगर (size + माप(hdr) > avail * माप(u64))
		size = avail * माप(u64) - माप(hdr);

	/* Write header. */
	hdr.type = VIRTIO_ID_CONSOLE;
	hdr.len = htons(size);
	ग_लिखोq(*(u64 *)&hdr, fअगरo->tx_base + MLXBF_TMFIFO_TX_DATA);

	/* Use spin-lock to protect the 'cons->tx_buf'. */
	spin_lock_irqsave(&fअगरo->spin_lock[0], flags);

	जबतक (size > 0) अणु
		addr = cons->tx_buf.buf + cons->tx_buf.tail;

		seg = CIRC_CNT_TO_END(cons->tx_buf.head, cons->tx_buf.tail,
				      MLXBF_TMFIFO_CON_TX_BUF_SIZE);
		अगर (seg >= माप(u64)) अणु
			स_नकल(&data, addr, माप(u64));
		पूर्ण अन्यथा अणु
			स_नकल(&data, addr, seg);
			स_नकल((u8 *)&data + seg, cons->tx_buf.buf,
			       माप(u64) - seg);
		पूर्ण
		ग_लिखोq(data, fअगरo->tx_base + MLXBF_TMFIFO_TX_DATA);

		अगर (size >= माप(u64)) अणु
			cons->tx_buf.tail = (cons->tx_buf.tail + माप(u64)) %
				MLXBF_TMFIFO_CON_TX_BUF_SIZE;
			size -= माप(u64);
		पूर्ण अन्यथा अणु
			cons->tx_buf.tail = (cons->tx_buf.tail + size) %
				MLXBF_TMFIFO_CON_TX_BUF_SIZE;
			size = 0;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&fअगरo->spin_lock[0], flags);
पूर्ण

/* Rx/Tx one word in the descriptor buffer. */
अटल व्योम mlxbf_पंचांगfअगरo_rxtx_word(काष्ठा mlxbf_पंचांगfअगरo_vring *vring,
				   काष्ठा vring_desc *desc,
				   bool is_rx, पूर्णांक len)
अणु
	काष्ठा virtio_device *vdev = vring->vq->vdev;
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo = vring->fअगरo;
	व्योम *addr;
	u64 data;

	/* Get the buffer address of this desc. */
	addr = phys_to_virt(virtio64_to_cpu(vdev, desc->addr));

	/* Read a word from FIFO क्रम Rx. */
	अगर (is_rx)
		data = पढ़ोq(fअगरo->rx_base + MLXBF_TMFIFO_RX_DATA);

	अगर (vring->cur_len + माप(u64) <= len) अणु
		/* The whole word. */
		अगर (is_rx)
			स_नकल(addr + vring->cur_len, &data, माप(u64));
		अन्यथा
			स_नकल(&data, addr + vring->cur_len, माप(u64));
		vring->cur_len += माप(u64);
	पूर्ण अन्यथा अणु
		/* Leftover bytes. */
		अगर (is_rx)
			स_नकल(addr + vring->cur_len, &data,
			       len - vring->cur_len);
		अन्यथा
			स_नकल(&data, addr + vring->cur_len,
			       len - vring->cur_len);
		vring->cur_len = len;
	पूर्ण

	/* Write the word पूर्णांकo FIFO क्रम Tx. */
	अगर (!is_rx)
		ग_लिखोq(data, fअगरo->tx_base + MLXBF_TMFIFO_TX_DATA);
पूर्ण

/*
 * Rx/Tx packet header.
 *
 * In Rx हाल, the packet might be found to beदीर्घ to a dअगरferent vring since
 * the TmFअगरo is shared by dअगरferent services. In such हाल, the 'vring_change'
 * flag is set.
 */
अटल व्योम mlxbf_पंचांगfअगरo_rxtx_header(काष्ठा mlxbf_पंचांगfअगरo_vring *vring,
				     काष्ठा vring_desc *desc,
				     bool is_rx, bool *vring_change)
अणु
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo = vring->fअगरo;
	काष्ठा virtio_net_config *config;
	काष्ठा mlxbf_पंचांगfअगरo_msg_hdr hdr;
	पूर्णांक vdev_id, hdr_len;

	/* Read/Write packet header. */
	अगर (is_rx) अणु
		/* Drain one word from the FIFO. */
		*(u64 *)&hdr = पढ़ोq(fअगरo->rx_base + MLXBF_TMFIFO_RX_DATA);

		/* Skip the length 0 packets (keepalive). */
		अगर (hdr.len == 0)
			वापस;

		/* Check packet type. */
		अगर (hdr.type == VIRTIO_ID_NET) अणु
			vdev_id = VIRTIO_ID_NET;
			hdr_len = माप(काष्ठा virtio_net_hdr);
			config = &fअगरo->vdev[vdev_id]->config.net;
			/* A legacy-only पूर्णांकerface क्रम now. */
			अगर (ntohs(hdr.len) >
			    __virtio16_to_cpu(virtio_legacy_is_little_endian(),
					      config->mtu) +
			    MLXBF_TMFIFO_NET_L2_OVERHEAD)
				वापस;
		पूर्ण अन्यथा अणु
			vdev_id = VIRTIO_ID_CONSOLE;
			hdr_len = 0;
		पूर्ण

		/*
		 * Check whether the new packet still beदीर्घs to this vring.
		 * If not, update the pkt_len of the new vring.
		 */
		अगर (vdev_id != vring->vdev_id) अणु
			काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_dev2 = fअगरo->vdev[vdev_id];

			अगर (!पंचांग_dev2)
				वापस;
			vring->desc = desc;
			vring = &पंचांग_dev2->vrings[MLXBF_TMFIFO_VRING_RX];
			*vring_change = true;
		पूर्ण
		vring->pkt_len = ntohs(hdr.len) + hdr_len;
	पूर्ण अन्यथा अणु
		/* Network virtio has an extra header. */
		hdr_len = (vring->vdev_id == VIRTIO_ID_NET) ?
			   माप(काष्ठा virtio_net_hdr) : 0;
		vring->pkt_len = mlxbf_पंचांगfअगरo_get_pkt_len(vring, desc);
		hdr.type = (vring->vdev_id == VIRTIO_ID_NET) ?
			    VIRTIO_ID_NET : VIRTIO_ID_CONSOLE;
		hdr.len = htons(vring->pkt_len - hdr_len);
		ग_लिखोq(*(u64 *)&hdr, fअगरo->tx_base + MLXBF_TMFIFO_TX_DATA);
	पूर्ण

	vring->cur_len = hdr_len;
	vring->rem_len = vring->pkt_len;
	fअगरo->vring[is_rx] = vring;
पूर्ण

/*
 * Rx/Tx one descriptor.
 *
 * Return true to indicate more data available.
 */
अटल bool mlxbf_पंचांगfअगरo_rxtx_one_desc(काष्ठा mlxbf_पंचांगfअगरo_vring *vring,
				       bool is_rx, पूर्णांक *avail)
अणु
	स्थिर काष्ठा vring *vr = virtqueue_get_vring(vring->vq);
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo = vring->fअगरo;
	काष्ठा virtio_device *vdev;
	bool vring_change = false;
	काष्ठा vring_desc *desc;
	अचिन्हित दीर्घ flags;
	u32 len, idx;

	vdev = &fअगरo->vdev[vring->vdev_id]->vdev;

	/* Get the descriptor of the next packet. */
	अगर (!vring->desc) अणु
		desc = mlxbf_पंचांगfअगरo_get_next_pkt(vring, is_rx);
		अगर (!desc)
			वापस false;
	पूर्ण अन्यथा अणु
		desc = vring->desc;
	पूर्ण

	/* Beginning of a packet. Start to Rx/Tx packet header. */
	अगर (vring->pkt_len == 0) अणु
		mlxbf_पंचांगfअगरo_rxtx_header(vring, desc, is_rx, &vring_change);
		(*avail)--;

		/* Return अगर new packet is क्रम another ring. */
		अगर (vring_change)
			वापस false;
		जाओ mlxbf_पंचांगfअगरo_desc_करोne;
	पूर्ण

	/* Get the length of this desc. */
	len = virtio32_to_cpu(vdev, desc->len);
	अगर (len > vring->rem_len)
		len = vring->rem_len;

	/* Rx/Tx one word (8 bytes) अगर not करोne. */
	अगर (vring->cur_len < len) अणु
		mlxbf_पंचांगfअगरo_rxtx_word(vring, desc, is_rx, len);
		(*avail)--;
	पूर्ण

	/* Check again whether it's करोne. */
	अगर (vring->cur_len == len) अणु
		vring->cur_len = 0;
		vring->rem_len -= len;

		/* Get the next desc on the chain. */
		अगर (vring->rem_len > 0 &&
		    (virtio16_to_cpu(vdev, desc->flags) & VRING_DESC_F_NEXT)) अणु
			idx = virtio16_to_cpu(vdev, desc->next);
			desc = &vr->desc[idx];
			जाओ mlxbf_पंचांगfअगरo_desc_करोne;
		पूर्ण

		/* Done and release the pending packet. */
		mlxbf_पंचांगfअगरo_release_pending_pkt(vring);
		desc = शून्य;
		fअगरo->vring[is_rx] = शून्य;

		/*
		 * Make sure the load/store are in order beक्रमe
		 * वापसing back to virtio.
		 */
		virtio_mb(false);

		/* Notअगरy upper layer that packet is करोne. */
		spin_lock_irqsave(&fअगरo->spin_lock[is_rx], flags);
		vring_पूर्णांकerrupt(0, vring->vq);
		spin_unlock_irqrestore(&fअगरo->spin_lock[is_rx], flags);
	पूर्ण

mlxbf_पंचांगfअगरo_desc_करोne:
	/* Save the current desc. */
	vring->desc = desc;

	वापस true;
पूर्ण

/* Rx & Tx processing of a queue. */
अटल व्योम mlxbf_पंचांगfअगरo_rxtx(काष्ठा mlxbf_पंचांगfअगरo_vring *vring, bool is_rx)
अणु
	पूर्णांक avail = 0, devid = vring->vdev_id;
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo;
	bool more;

	fअगरo = vring->fअगरo;

	/* Return अगर vdev is not पढ़ोy. */
	अगर (!fअगरo->vdev[devid])
		वापस;

	/* Return अगर another vring is running. */
	अगर (fअगरo->vring[is_rx] && fअगरo->vring[is_rx] != vring)
		वापस;

	/* Only handle console and network क्रम now. */
	अगर (WARN_ON(devid != VIRTIO_ID_NET && devid != VIRTIO_ID_CONSOLE))
		वापस;

	करो अणु
		/* Get available FIFO space. */
		अगर (avail == 0) अणु
			अगर (is_rx)
				avail = mlxbf_पंचांगfअगरo_get_rx_avail(fअगरo);
			अन्यथा
				avail = mlxbf_पंचांगfअगरo_get_tx_avail(fअगरo, devid);
			अगर (avail <= 0)
				अवरोध;
		पूर्ण

		/* Console output always comes from the Tx buffer. */
		अगर (!is_rx && devid == VIRTIO_ID_CONSOLE) अणु
			mlxbf_पंचांगfअगरo_console_tx(fअगरo, avail);
			अवरोध;
		पूर्ण

		/* Handle one descriptor. */
		more = mlxbf_पंचांगfअगरo_rxtx_one_desc(vring, is_rx, &avail);
	पूर्ण जबतक (more);
पूर्ण

/* Handle Rx or Tx queues. */
अटल व्योम mlxbf_पंचांगfअगरo_work_rxtx(काष्ठा mlxbf_पंचांगfअगरo *fअगरo, पूर्णांक queue_id,
				   पूर्णांक irq_id, bool is_rx)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev;
	काष्ठा mlxbf_पंचांगfअगरo_vring *vring;
	पूर्णांक i;

	अगर (!test_and_clear_bit(irq_id, &fअगरo->pend_events) ||
	    !fअगरo->irq_info[irq_id].irq)
		वापस;

	क्रम (i = 0; i < MLXBF_TMFIFO_VDEV_MAX; i++) अणु
		पंचांग_vdev = fअगरo->vdev[i];
		अगर (पंचांग_vdev) अणु
			vring = &पंचांग_vdev->vrings[queue_id];
			अगर (vring->vq)
				mlxbf_पंचांगfअगरo_rxtx(vring, is_rx);
		पूर्ण
	पूर्ण
पूर्ण

/* Work handler क्रम Rx and Tx हाल. */
अटल व्योम mlxbf_पंचांगfअगरo_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo;

	fअगरo = container_of(work, काष्ठा mlxbf_पंचांगfअगरo, work);
	अगर (!fअगरo->is_पढ़ोy)
		वापस;

	mutex_lock(&fअगरo->lock);

	/* Tx (Send data to the TmFअगरo). */
	mlxbf_पंचांगfअगरo_work_rxtx(fअगरo, MLXBF_TMFIFO_VRING_TX,
			       MLXBF_TM_TX_LWM_IRQ, false);

	/* Rx (Receive data from the TmFअगरo). */
	mlxbf_पंचांगfअगरo_work_rxtx(fअगरo, MLXBF_TMFIFO_VRING_RX,
			       MLXBF_TM_RX_HWM_IRQ, true);

	mutex_unlock(&fअगरo->lock);
पूर्ण

/* The notअगरy function is called when new buffers are posted. */
अटल bool mlxbf_पंचांगfअगरo_virtio_notअगरy(काष्ठा virtqueue *vq)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vring *vring = vq->priv;
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev;
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo;
	अचिन्हित दीर्घ flags;

	fअगरo = vring->fअगरo;

	/*
	 * Virtio मुख्यtains vrings in pairs, even number ring क्रम Rx
	 * and odd number ring क्रम Tx.
	 */
	अगर (vring->index & BIT(0)) अणु
		/*
		 * Console could make blocking call with पूर्णांकerrupts disabled.
		 * In such हाल, the vring needs to be served right away. For
		 * other हालs, just set the TX LWM bit to start Tx in the
		 * worker handler.
		 */
		अगर (vring->vdev_id == VIRTIO_ID_CONSOLE) अणु
			spin_lock_irqsave(&fअगरo->spin_lock[0], flags);
			पंचांग_vdev = fअगरo->vdev[VIRTIO_ID_CONSOLE];
			mlxbf_पंचांगfअगरo_console_output(पंचांग_vdev, vring);
			spin_unlock_irqrestore(&fअगरo->spin_lock[0], flags);
		पूर्ण अन्यथा अगर (test_and_set_bit(MLXBF_TM_TX_LWM_IRQ,
					    &fअगरo->pend_events)) अणु
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (test_and_set_bit(MLXBF_TM_RX_HWM_IRQ, &fअगरo->pend_events))
			वापस true;
	पूर्ण

	schedule_work(&fअगरo->work);

	वापस true;
पूर्ण

/* Get the array of feature bits क्रम this device. */
अटल u64 mlxbf_पंचांगfअगरo_virtio_get_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);

	वापस पंचांग_vdev->features;
पूर्ण

/* Confirm device features to use. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_virtio_finalize_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);

	पंचांग_vdev->features = vdev->features;

	वापस 0;
पूर्ण

/* Free virtqueues found by find_vqs(). */
अटल व्योम mlxbf_पंचांगfअगरo_virtio_del_vqs(काष्ठा virtio_device *vdev)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);
	काष्ठा mlxbf_पंचांगfअगरo_vring *vring;
	काष्ठा virtqueue *vq;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(पंचांग_vdev->vrings); i++) अणु
		vring = &पंचांग_vdev->vrings[i];

		/* Release the pending packet. */
		अगर (vring->desc)
			mlxbf_पंचांगfअगरo_release_pending_pkt(vring);
		vq = vring->vq;
		अगर (vq) अणु
			vring->vq = शून्य;
			vring_del_virtqueue(vq);
		पूर्ण
	पूर्ण
पूर्ण

/* Create and initialize the भव queues. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_virtio_find_vqs(काष्ठा virtio_device *vdev,
					अचिन्हित पूर्णांक nvqs,
					काष्ठा virtqueue *vqs[],
					vq_callback_t *callbacks[],
					स्थिर अक्षर * स्थिर names[],
					स्थिर bool *ctx,
					काष्ठा irq_affinity *desc)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);
	काष्ठा mlxbf_पंचांगfअगरo_vring *vring;
	काष्ठा virtqueue *vq;
	पूर्णांक i, ret, size;

	अगर (nvqs > ARRAY_SIZE(पंचांग_vdev->vrings))
		वापस -EINVAL;

	क्रम (i = 0; i < nvqs; ++i) अणु
		अगर (!names[i]) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		vring = &पंचांग_vdev->vrings[i];

		/* zero vring */
		size = vring_size(vring->num, vring->align);
		स_रखो(vring->va, 0, size);
		vq = vring_new_virtqueue(i, vring->num, vring->align, vdev,
					 false, false, vring->va,
					 mlxbf_पंचांगfअगरo_virtio_notअगरy,
					 callbacks[i], names[i]);
		अगर (!vq) अणु
			dev_err(&vdev->dev, "vring_new_virtqueue failed\n");
			ret = -ENOMEM;
			जाओ error;
		पूर्ण

		vqs[i] = vq;
		vring->vq = vq;
		vq->priv = vring;
	पूर्ण

	वापस 0;

error:
	mlxbf_पंचांगfअगरo_virtio_del_vqs(vdev);
	वापस ret;
पूर्ण

/* Read the status byte. */
अटल u8 mlxbf_पंचांगfअगरo_virtio_get_status(काष्ठा virtio_device *vdev)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);

	वापस पंचांग_vdev->status;
पूर्ण

/* Write the status byte. */
अटल व्योम mlxbf_पंचांगfअगरo_virtio_set_status(काष्ठा virtio_device *vdev,
					   u8 status)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);

	पंचांग_vdev->status = status;
पूर्ण

/* Reset the device. Not much here क्रम now. */
अटल व्योम mlxbf_पंचांगfअगरo_virtio_reset(काष्ठा virtio_device *vdev)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);

	पंचांग_vdev->status = 0;
पूर्ण

/* Read the value of a configuration field. */
अटल व्योम mlxbf_पंचांगfअगरo_virtio_get(काष्ठा virtio_device *vdev,
				    अचिन्हित पूर्णांक offset,
				    व्योम *buf,
				    अचिन्हित पूर्णांक len)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);

	अगर ((u64)offset + len > माप(पंचांग_vdev->config))
		वापस;

	स_नकल(buf, (u8 *)&पंचांग_vdev->config + offset, len);
पूर्ण

/* Write the value of a configuration field. */
अटल व्योम mlxbf_पंचांगfअगरo_virtio_set(काष्ठा virtio_device *vdev,
				    अचिन्हित पूर्णांक offset,
				    स्थिर व्योम *buf,
				    अचिन्हित पूर्णांक len)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);

	अगर ((u64)offset + len > माप(पंचांग_vdev->config))
		वापस;

	स_नकल((u8 *)&पंचांग_vdev->config + offset, buf, len);
पूर्ण

अटल व्योम पंचांगfअगरo_virtio_dev_release(काष्ठा device *device)
अणु
	काष्ठा virtio_device *vdev =
			container_of(device, काष्ठा virtio_device, dev);
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev = mlxbf_vdev_to_पंचांगfअगरo(vdev);

	kमुक्त(पंचांग_vdev);
पूर्ण

/* Virtio config operations. */
अटल स्थिर काष्ठा virtio_config_ops mlxbf_पंचांगfअगरo_virtio_config_ops = अणु
	.get_features = mlxbf_पंचांगfअगरo_virtio_get_features,
	.finalize_features = mlxbf_पंचांगfअगरo_virtio_finalize_features,
	.find_vqs = mlxbf_पंचांगfअगरo_virtio_find_vqs,
	.del_vqs = mlxbf_पंचांगfअगरo_virtio_del_vqs,
	.reset = mlxbf_पंचांगfअगरo_virtio_reset,
	.set_status = mlxbf_पंचांगfअगरo_virtio_set_status,
	.get_status = mlxbf_पंचांगfअगरo_virtio_get_status,
	.get = mlxbf_पंचांगfअगरo_virtio_get,
	.set = mlxbf_पंचांगfअगरo_virtio_set,
पूर्ण;

/* Create vdev क्रम the FIFO. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_create_vdev(काष्ठा device *dev,
				    काष्ठा mlxbf_पंचांगfअगरo *fअगरo,
				    पूर्णांक vdev_id, u64 features,
				    व्योम *config, u32 size)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev, *reg_dev = शून्य;
	पूर्णांक ret;

	mutex_lock(&fअगरo->lock);

	पंचांग_vdev = fअगरo->vdev[vdev_id];
	अगर (पंचांग_vdev) अणु
		dev_err(dev, "vdev %d already exists\n", vdev_id);
		ret = -EEXIST;
		जाओ fail;
	पूर्ण

	पंचांग_vdev = kzalloc(माप(*पंचांग_vdev), GFP_KERNEL);
	अगर (!पंचांग_vdev) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	पंचांग_vdev->vdev.id.device = vdev_id;
	पंचांग_vdev->vdev.config = &mlxbf_पंचांगfअगरo_virtio_config_ops;
	पंचांग_vdev->vdev.dev.parent = dev;
	पंचांग_vdev->vdev.dev.release = पंचांगfअगरo_virtio_dev_release;
	पंचांग_vdev->features = features;
	अगर (config)
		स_नकल(&पंचांग_vdev->config, config, size);

	अगर (mlxbf_पंचांगfअगरo_alloc_vrings(fअगरo, पंचांग_vdev)) अणु
		dev_err(dev, "unable to allocate vring\n");
		ret = -ENOMEM;
		जाओ vdev_fail;
	पूर्ण

	/* Allocate an output buffer क्रम the console device. */
	अगर (vdev_id == VIRTIO_ID_CONSOLE)
		पंचांग_vdev->tx_buf.buf = devm_kदो_स्मृति(dev,
						   MLXBF_TMFIFO_CON_TX_BUF_SIZE,
						   GFP_KERNEL);
	fअगरo->vdev[vdev_id] = पंचांग_vdev;

	/* Register the virtio device. */
	ret = रेजिस्टर_virtio_device(&पंचांग_vdev->vdev);
	reg_dev = पंचांग_vdev;
	अगर (ret) अणु
		dev_err(dev, "register_virtio_device failed\n");
		जाओ vdev_fail;
	पूर्ण

	mutex_unlock(&fअगरo->lock);
	वापस 0;

vdev_fail:
	mlxbf_पंचांगfअगरo_मुक्त_vrings(fअगरo, पंचांग_vdev);
	fअगरo->vdev[vdev_id] = शून्य;
	अगर (reg_dev)
		put_device(&पंचांग_vdev->vdev.dev);
	अन्यथा
		kमुक्त(पंचांग_vdev);
fail:
	mutex_unlock(&fअगरo->lock);
	वापस ret;
पूर्ण

/* Delete vdev क्रम the FIFO. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_delete_vdev(काष्ठा mlxbf_पंचांगfअगरo *fअगरo, पूर्णांक vdev_id)
अणु
	काष्ठा mlxbf_पंचांगfअगरo_vdev *पंचांग_vdev;

	mutex_lock(&fअगरo->lock);

	/* Unरेजिस्टर vdev. */
	पंचांग_vdev = fअगरo->vdev[vdev_id];
	अगर (पंचांग_vdev) अणु
		unरेजिस्टर_virtio_device(&पंचांग_vdev->vdev);
		mlxbf_पंचांगfअगरo_मुक्त_vrings(fअगरo, पंचांग_vdev);
		fअगरo->vdev[vdev_id] = शून्य;
	पूर्ण

	mutex_unlock(&fअगरo->lock);

	वापस 0;
पूर्ण

/* Read the configured network MAC address from efi variable. */
अटल व्योम mlxbf_पंचांगfअगरo_get_cfg_mac(u8 *mac)
अणु
	efi_guid_t guid = EFI_GLOBAL_VARIABLE_GUID;
	अचिन्हित दीर्घ size = ETH_ALEN;
	u8 buf[ETH_ALEN];
	efi_status_t rc;

	rc = efi.get_variable(mlxbf_पंचांगfअगरo_efi_name, &guid, शून्य, &size, buf);
	अगर (rc == EFI_SUCCESS && size == ETH_ALEN)
		ether_addr_copy(mac, buf);
	अन्यथा
		ether_addr_copy(mac, mlxbf_पंचांगfअगरo_net_शेष_mac);
पूर्ण

/* Set TmFअगरo thresolds which is used to trigger पूर्णांकerrupts. */
अटल व्योम mlxbf_पंचांगfअगरo_set_threshold(काष्ठा mlxbf_पंचांगfअगरo *fअगरo)
अणु
	u64 ctl;

	/* Get Tx FIFO size and set the low/high watermark. */
	ctl = पढ़ोq(fअगरo->tx_base + MLXBF_TMFIFO_TX_CTL);
	fअगरo->tx_fअगरo_size =
		FIELD_GET(MLXBF_TMFIFO_TX_CTL__MAX_ENTRIES_MASK, ctl);
	ctl = (ctl & ~MLXBF_TMFIFO_TX_CTL__LWM_MASK) |
		FIELD_PREP(MLXBF_TMFIFO_TX_CTL__LWM_MASK,
			   fअगरo->tx_fअगरo_size / 2);
	ctl = (ctl & ~MLXBF_TMFIFO_TX_CTL__HWM_MASK) |
		FIELD_PREP(MLXBF_TMFIFO_TX_CTL__HWM_MASK,
			   fअगरo->tx_fअगरo_size - 1);
	ग_लिखोq(ctl, fअगरo->tx_base + MLXBF_TMFIFO_TX_CTL);

	/* Get Rx FIFO size and set the low/high watermark. */
	ctl = पढ़ोq(fअगरo->rx_base + MLXBF_TMFIFO_RX_CTL);
	fअगरo->rx_fअगरo_size =
		FIELD_GET(MLXBF_TMFIFO_RX_CTL__MAX_ENTRIES_MASK, ctl);
	ctl = (ctl & ~MLXBF_TMFIFO_RX_CTL__LWM_MASK) |
		FIELD_PREP(MLXBF_TMFIFO_RX_CTL__LWM_MASK, 0);
	ctl = (ctl & ~MLXBF_TMFIFO_RX_CTL__HWM_MASK) |
		FIELD_PREP(MLXBF_TMFIFO_RX_CTL__HWM_MASK, 1);
	ग_लिखोq(ctl, fअगरo->rx_base + MLXBF_TMFIFO_RX_CTL);
पूर्ण

अटल व्योम mlxbf_पंचांगfअगरo_cleanup(काष्ठा mlxbf_पंचांगfअगरo *fअगरo)
अणु
	पूर्णांक i;

	fअगरo->is_पढ़ोy = false;
	del_समयr_sync(&fअगरo->समयr);
	mlxbf_पंचांगfअगरo_disable_irqs(fअगरo);
	cancel_work_sync(&fअगरo->work);
	क्रम (i = 0; i < MLXBF_TMFIFO_VDEV_MAX; i++)
		mlxbf_पंचांगfअगरo_delete_vdev(fअगरo, i);
पूर्ण

/* Probe the TMFIFO. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा virtio_net_config net_config;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo;
	पूर्णांक i, rc;

	fअगरo = devm_kzalloc(dev, माप(*fअगरo), GFP_KERNEL);
	अगर (!fअगरo)
		वापस -ENOMEM;

	spin_lock_init(&fअगरo->spin_lock[0]);
	spin_lock_init(&fअगरo->spin_lock[1]);
	INIT_WORK(&fअगरo->work, mlxbf_पंचांगfअगरo_work_handler);
	mutex_init(&fअगरo->lock);

	/* Get the resource of the Rx FIFO. */
	fअगरo->rx_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(fअगरo->rx_base))
		वापस PTR_ERR(fअगरo->rx_base);

	/* Get the resource of the Tx FIFO. */
	fअगरo->tx_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(fअगरo->tx_base))
		वापस PTR_ERR(fअगरo->tx_base);

	platक्रमm_set_drvdata(pdev, fअगरo);

	समयr_setup(&fअगरo->समयr, mlxbf_पंचांगfअगरo_समयr, 0);

	क्रम (i = 0; i < MLXBF_TM_MAX_IRQ; i++) अणु
		fअगरo->irq_info[i].index = i;
		fअगरo->irq_info[i].fअगरo = fअगरo;
		fअगरo->irq_info[i].irq = platक्रमm_get_irq(pdev, i);
		rc = devm_request_irq(dev, fअगरo->irq_info[i].irq,
				      mlxbf_पंचांगfअगरo_irq_handler, 0,
				      "tmfifo", &fअगरo->irq_info[i]);
		अगर (rc) अणु
			dev_err(dev, "devm_request_irq failed\n");
			fअगरo->irq_info[i].irq = 0;
			वापस rc;
		पूर्ण
	पूर्ण

	mlxbf_पंचांगfअगरo_set_threshold(fअगरo);

	/* Create the console vdev. */
	rc = mlxbf_पंचांगfअगरo_create_vdev(dev, fअगरo, VIRTIO_ID_CONSOLE, 0, शून्य, 0);
	अगर (rc)
		जाओ fail;

	/* Create the network vdev. */
	स_रखो(&net_config, 0, माप(net_config));

	/* A legacy-only पूर्णांकerface क्रम now. */
	net_config.mtu = __cpu_to_virtio16(virtio_legacy_is_little_endian(),
					   ETH_DATA_LEN);
	net_config.status = __cpu_to_virtio16(virtio_legacy_is_little_endian(),
					      VIRTIO_NET_S_LINK_UP);
	mlxbf_पंचांगfअगरo_get_cfg_mac(net_config.mac);
	rc = mlxbf_पंचांगfअगरo_create_vdev(dev, fअगरo, VIRTIO_ID_NET,
				      MLXBF_TMFIFO_NET_FEATURES, &net_config,
				      माप(net_config));
	अगर (rc)
		जाओ fail;

	mod_समयr(&fअगरo->समयr, jअगरfies + MLXBF_TMFIFO_TIMER_INTERVAL);

	fअगरo->is_पढ़ोy = true;
	वापस 0;

fail:
	mlxbf_पंचांगfअगरo_cleanup(fअगरo);
	वापस rc;
पूर्ण

/* Device हटाओ function. */
अटल पूर्णांक mlxbf_पंचांगfअगरo_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxbf_पंचांगfअगरo *fअगरo = platक्रमm_get_drvdata(pdev);

	mlxbf_पंचांगfअगरo_cleanup(fअगरo);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id mlxbf_पंचांगfअगरo_acpi_match[] = अणु
	अणु "MLNXBF01", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mlxbf_पंचांगfअगरo_acpi_match);

अटल काष्ठा platक्रमm_driver mlxbf_पंचांगfअगरo_driver = अणु
	.probe = mlxbf_पंचांगfअगरo_probe,
	.हटाओ = mlxbf_पंचांगfअगरo_हटाओ,
	.driver = अणु
		.name = "bf-tmfifo",
		.acpi_match_table = mlxbf_पंचांगfअगरo_acpi_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mlxbf_पंचांगfअगरo_driver);

MODULE_DESCRIPTION("Mellanox BlueField SoC TmFifo Driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Mellanox Technologies");
