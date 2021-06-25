<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/rocker/rocker.c - Rocker चयन device driver
 * Copyright (c) 2014-2016 Jiri Pirko <jiri@mellanox.com>
 * Copyright (c) 2014 Scott Feldman <sfeldma@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sort.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/bitops.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/workqueue.h>
#समावेश <net/चयनdev.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/netevent.h>
#समावेश <net/arp.h>
#समावेश <net/fib_rules.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <generated/utsrelease.h>

#समावेश "rocker_hw.h"
#समावेश "rocker.h"
#समावेश "rocker_tlv.h"

अटल स्थिर अक्षर rocker_driver_name[] = "rocker";

अटल स्थिर काष्ठा pci_device_id rocker_pci_id_table[] = अणु
	अणुPCI_VDEVICE(REDHAT, PCI_DEVICE_ID_REDHAT_ROCKER), 0पूर्ण,
	अणु0, पूर्ण
पूर्ण;

काष्ठा rocker_रुको अणु
	रुको_queue_head_t रुको;
	bool करोne;
	bool noरुको;
पूर्ण;

अटल व्योम rocker_रुको_reset(काष्ठा rocker_रुको *रुको)
अणु
	रुको->करोne = false;
	रुको->noरुको = false;
पूर्ण

अटल व्योम rocker_रुको_init(काष्ठा rocker_रुको *रुको)
अणु
	init_रुकोqueue_head(&रुको->रुको);
	rocker_रुको_reset(रुको);
पूर्ण

अटल काष्ठा rocker_रुको *rocker_रुको_create(व्योम)
अणु
	काष्ठा rocker_रुको *रुको;

	रुको = kzalloc(माप(*रुको), GFP_KERNEL);
	अगर (!रुको)
		वापस शून्य;
	वापस रुको;
पूर्ण

अटल व्योम rocker_रुको_destroy(काष्ठा rocker_रुको *रुको)
अणु
	kमुक्त(रुको);
पूर्ण

अटल bool rocker_रुको_event_समयout(काष्ठा rocker_रुको *रुको,
				      अचिन्हित दीर्घ समयout)
अणु
	रुको_event_समयout(रुको->रुको, रुको->करोne, HZ / 10);
	अगर (!रुको->करोne)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम rocker_रुको_wake_up(काष्ठा rocker_रुको *रुको)
अणु
	रुको->करोne = true;
	wake_up(&रुको->रुको);
पूर्ण

अटल u32 rocker_msix_vector(स्थिर काष्ठा rocker *rocker, अचिन्हित पूर्णांक vector)
अणु
	वापस rocker->msix_entries[vector].vector;
पूर्ण

अटल u32 rocker_msix_tx_vector(स्थिर काष्ठा rocker_port *rocker_port)
अणु
	वापस rocker_msix_vector(rocker_port->rocker,
				  ROCKER_MSIX_VEC_TX(rocker_port->port_number));
पूर्ण

अटल u32 rocker_msix_rx_vector(स्थिर काष्ठा rocker_port *rocker_port)
अणु
	वापस rocker_msix_vector(rocker_port->rocker,
				  ROCKER_MSIX_VEC_RX(rocker_port->port_number));
पूर्ण

#घोषणा rocker_ग_लिखो32(rocker, reg, val)	\
	ग_लिखोl((val), (rocker)->hw_addr + (ROCKER_ ## reg))
#घोषणा rocker_पढ़ो32(rocker, reg)	\
	पढ़ोl((rocker)->hw_addr + (ROCKER_ ## reg))
#घोषणा rocker_ग_लिखो64(rocker, reg, val)	\
	ग_लिखोq((val), (rocker)->hw_addr + (ROCKER_ ## reg))
#घोषणा rocker_पढ़ो64(rocker, reg)	\
	पढ़ोq((rocker)->hw_addr + (ROCKER_ ## reg))

/*****************************
 * HW basic testing functions
 *****************************/

अटल पूर्णांक rocker_reg_test(स्थिर काष्ठा rocker *rocker)
अणु
	स्थिर काष्ठा pci_dev *pdev = rocker->pdev;
	u64 test_reg;
	u64 rnd;

	rnd = pअक्रमom_u32();
	rnd >>= 1;
	rocker_ग_लिखो32(rocker, TEST_REG, rnd);
	test_reg = rocker_पढ़ो32(rocker, TEST_REG);
	अगर (test_reg != rnd * 2) अणु
		dev_err(&pdev->dev, "unexpected 32bit register value %08llx, expected %08llx\n",
			test_reg, rnd * 2);
		वापस -EIO;
	पूर्ण

	rnd = pअक्रमom_u32();
	rnd <<= 31;
	rnd |= pअक्रमom_u32();
	rocker_ग_लिखो64(rocker, TEST_REG64, rnd);
	test_reg = rocker_पढ़ो64(rocker, TEST_REG64);
	अगर (test_reg != rnd * 2) अणु
		dev_err(&pdev->dev, "unexpected 64bit register value %16llx, expected %16llx\n",
			test_reg, rnd * 2);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rocker_dma_test_one(स्थिर काष्ठा rocker *rocker,
			       काष्ठा rocker_रुको *रुको, u32 test_type,
			       dma_addr_t dma_handle, स्थिर अचिन्हित अक्षर *buf,
			       स्थिर अचिन्हित अक्षर *expect, माप_प्रकार size)
अणु
	स्थिर काष्ठा pci_dev *pdev = rocker->pdev;
	पूर्णांक i;

	rocker_रुको_reset(रुको);
	rocker_ग_लिखो32(rocker, TEST_DMA_CTRL, test_type);

	अगर (!rocker_रुको_event_समयout(रुको, HZ / 10)) अणु
		dev_err(&pdev->dev, "no interrupt received within a timeout\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		अगर (buf[i] != expect[i]) अणु
			dev_err(&pdev->dev, "unexpected memory content %02x at byte %x\n, %02x expected",
				buf[i], i, expect[i]);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा ROCKER_TEST_DMA_BUF_SIZE (PAGE_SIZE * 4)
#घोषणा ROCKER_TEST_DMA_FILL_PATTERN 0x96

अटल पूर्णांक rocker_dma_test_offset(स्थिर काष्ठा rocker *rocker,
				  काष्ठा rocker_रुको *रुको, पूर्णांक offset)
अणु
	काष्ठा pci_dev *pdev = rocker->pdev;
	अचिन्हित अक्षर *alloc;
	अचिन्हित अक्षर *buf;
	अचिन्हित अक्षर *expect;
	dma_addr_t dma_handle;
	पूर्णांक i;
	पूर्णांक err;

	alloc = kzalloc(ROCKER_TEST_DMA_BUF_SIZE * 2 + offset,
			GFP_KERNEL | GFP_DMA);
	अगर (!alloc)
		वापस -ENOMEM;
	buf = alloc + offset;
	expect = buf + ROCKER_TEST_DMA_BUF_SIZE;

	dma_handle = dma_map_single(&pdev->dev, buf, ROCKER_TEST_DMA_BUF_SIZE,
				    DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&pdev->dev, dma_handle)) अणु
		err = -EIO;
		जाओ मुक्त_alloc;
	पूर्ण

	rocker_ग_लिखो64(rocker, TEST_DMA_ADDR, dma_handle);
	rocker_ग_लिखो32(rocker, TEST_DMA_SIZE, ROCKER_TEST_DMA_BUF_SIZE);

	स_रखो(expect, ROCKER_TEST_DMA_FILL_PATTERN, ROCKER_TEST_DMA_BUF_SIZE);
	err = rocker_dma_test_one(rocker, रुको, ROCKER_TEST_DMA_CTRL_FILL,
				  dma_handle, buf, expect,
				  ROCKER_TEST_DMA_BUF_SIZE);
	अगर (err)
		जाओ unmap;

	स_रखो(expect, 0, ROCKER_TEST_DMA_BUF_SIZE);
	err = rocker_dma_test_one(rocker, रुको, ROCKER_TEST_DMA_CTRL_CLEAR,
				  dma_handle, buf, expect,
				  ROCKER_TEST_DMA_BUF_SIZE);
	अगर (err)
		जाओ unmap;

	pअक्रमom_bytes(buf, ROCKER_TEST_DMA_BUF_SIZE);
	क्रम (i = 0; i < ROCKER_TEST_DMA_BUF_SIZE; i++)
		expect[i] = ~buf[i];
	err = rocker_dma_test_one(rocker, रुको, ROCKER_TEST_DMA_CTRL_INVERT,
				  dma_handle, buf, expect,
				  ROCKER_TEST_DMA_BUF_SIZE);
	अगर (err)
		जाओ unmap;

unmap:
	dma_unmap_single(&pdev->dev, dma_handle, ROCKER_TEST_DMA_BUF_SIZE,
			 DMA_BIसूचीECTIONAL);
मुक्त_alloc:
	kमुक्त(alloc);

	वापस err;
पूर्ण

अटल पूर्णांक rocker_dma_test(स्थिर काष्ठा rocker *rocker,
			   काष्ठा rocker_रुको *रुको)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < 8; i++) अणु
		err = rocker_dma_test_offset(rocker, रुको, i);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t rocker_test_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rocker_रुको *रुको = dev_id;

	rocker_रुको_wake_up(रुको);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rocker_basic_hw_test(स्थिर काष्ठा rocker *rocker)
अणु
	स्थिर काष्ठा pci_dev *pdev = rocker->pdev;
	काष्ठा rocker_रुको रुको;
	पूर्णांक err;

	err = rocker_reg_test(rocker);
	अगर (err) अणु
		dev_err(&pdev->dev, "reg test failed\n");
		वापस err;
	पूर्ण

	err = request_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_TEST),
			  rocker_test_irq_handler, 0,
			  rocker_driver_name, &रुको);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot assign test irq\n");
		वापस err;
	पूर्ण

	rocker_रुको_init(&रुको);
	rocker_ग_लिखो32(rocker, TEST_IRQ, ROCKER_MSIX_VEC_TEST);

	अगर (!rocker_रुको_event_समयout(&रुको, HZ / 10)) अणु
		dev_err(&pdev->dev, "no interrupt received within a timeout\n");
		err = -EIO;
		जाओ मुक्त_irq;
	पूर्ण

	err = rocker_dma_test(rocker, &रुको);
	अगर (err)
		dev_err(&pdev->dev, "dma test failed\n");

मुक्त_irq:
	मुक्त_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_TEST), &रुको);
	वापस err;
पूर्ण

/******************************************
 * DMA rings and descriptors manipulations
 ******************************************/

अटल u32 __pos_inc(u32 pos, माप_प्रकार limit)
अणु
	वापस ++pos == limit ? 0 : pos;
पूर्ण

अटल पूर्णांक rocker_desc_err(स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	पूर्णांक err = desc_info->desc->comp_err & ~ROCKER_DMA_DESC_COMP_ERR_GEN;

	चयन (err) अणु
	हाल ROCKER_OK:
		वापस 0;
	हाल -ROCKER_ENOENT:
		वापस -ENOENT;
	हाल -ROCKER_ENXIO:
		वापस -ENXIO;
	हाल -ROCKER_ENOMEM:
		वापस -ENOMEM;
	हाल -ROCKER_EEXIST:
		वापस -EEXIST;
	हाल -ROCKER_EINVAL:
		वापस -EINVAL;
	हाल -ROCKER_EMSGSIZE:
		वापस -EMSGSIZE;
	हाल -ROCKER_ENOTSUP:
		वापस -EOPNOTSUPP;
	हाल -ROCKER_ENOBUFS:
		वापस -ENOBUFS;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम rocker_desc_gen_clear(स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	desc_info->desc->comp_err &= ~ROCKER_DMA_DESC_COMP_ERR_GEN;
पूर्ण

अटल bool rocker_desc_gen(स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	u32 comp_err = desc_info->desc->comp_err;

	वापस comp_err & ROCKER_DMA_DESC_COMP_ERR_GEN ? true : false;
पूर्ण

अटल व्योम *
rocker_desc_cookie_ptr_get(स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)desc_info->desc->cookie;
पूर्ण

अटल व्योम rocker_desc_cookie_ptr_set(स्थिर काष्ठा rocker_desc_info *desc_info,
				       व्योम *ptr)
अणु
	desc_info->desc->cookie = (uपूर्णांकptr_t) ptr;
पूर्ण

अटल काष्ठा rocker_desc_info *
rocker_desc_head_get(स्थिर काष्ठा rocker_dma_ring_info *info)
अणु
	काष्ठा rocker_desc_info *desc_info;
	u32 head = __pos_inc(info->head, info->size);

	desc_info = &info->desc_info[info->head];
	अगर (head == info->tail)
		वापस शून्य; /* ring full */
	desc_info->tlv_size = 0;
	वापस desc_info;
पूर्ण

अटल व्योम rocker_desc_commit(स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	desc_info->desc->buf_size = desc_info->data_size;
	desc_info->desc->tlv_size = desc_info->tlv_size;
पूर्ण

अटल व्योम rocker_desc_head_set(स्थिर काष्ठा rocker *rocker,
				 काष्ठा rocker_dma_ring_info *info,
				 स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	u32 head = __pos_inc(info->head, info->size);

	BUG_ON(head == info->tail);
	rocker_desc_commit(desc_info);
	info->head = head;
	rocker_ग_लिखो32(rocker, DMA_DESC_HEAD(info->type), head);
पूर्ण

अटल काष्ठा rocker_desc_info *
rocker_desc_tail_get(काष्ठा rocker_dma_ring_info *info)
अणु
	काष्ठा rocker_desc_info *desc_info;

	अगर (info->tail == info->head)
		वापस शून्य; /* nothing to be करोne between head and tail */
	desc_info = &info->desc_info[info->tail];
	अगर (!rocker_desc_gen(desc_info))
		वापस शून्य; /* gen bit not set, desc is not पढ़ोy yet */
	info->tail = __pos_inc(info->tail, info->size);
	desc_info->tlv_size = desc_info->desc->tlv_size;
	वापस desc_info;
पूर्ण

अटल व्योम rocker_dma_ring_credits_set(स्थिर काष्ठा rocker *rocker,
					स्थिर काष्ठा rocker_dma_ring_info *info,
					u32 credits)
अणु
	अगर (credits)
		rocker_ग_लिखो32(rocker, DMA_DESC_CREDITS(info->type), credits);
पूर्ण

अटल अचिन्हित दीर्घ rocker_dma_ring_size_fix(माप_प्रकार size)
अणु
	वापस max(ROCKER_DMA_SIZE_MIN,
		   min(roundup_घात_of_two(size), ROCKER_DMA_SIZE_MAX));
पूर्ण

अटल पूर्णांक rocker_dma_ring_create(स्थिर काष्ठा rocker *rocker,
				  अचिन्हित पूर्णांक type,
				  माप_प्रकार size,
				  काष्ठा rocker_dma_ring_info *info)
अणु
	पूर्णांक i;

	BUG_ON(size != rocker_dma_ring_size_fix(size));
	info->size = size;
	info->type = type;
	info->head = 0;
	info->tail = 0;
	info->desc_info = kसुस्मृति(info->size, माप(*info->desc_info),
				  GFP_KERNEL);
	अगर (!info->desc_info)
		वापस -ENOMEM;

	info->desc = dma_alloc_coherent(&rocker->pdev->dev,
					info->size * माप(*info->desc),
					&info->mapaddr, GFP_KERNEL);
	अगर (!info->desc) अणु
		kमुक्त(info->desc_info);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < info->size; i++)
		info->desc_info[i].desc = &info->desc[i];

	rocker_ग_लिखो32(rocker, DMA_DESC_CTRL(info->type),
		       ROCKER_DMA_DESC_CTRL_RESET);
	rocker_ग_लिखो64(rocker, DMA_DESC_ADDR(info->type), info->mapaddr);
	rocker_ग_लिखो32(rocker, DMA_DESC_SIZE(info->type), info->size);

	वापस 0;
पूर्ण

अटल व्योम rocker_dma_ring_destroy(स्थिर काष्ठा rocker *rocker,
				    स्थिर काष्ठा rocker_dma_ring_info *info)
अणु
	rocker_ग_लिखो64(rocker, DMA_DESC_ADDR(info->type), 0);

	dma_मुक्त_coherent(&rocker->pdev->dev,
			  info->size * माप(काष्ठा rocker_desc), info->desc,
			  info->mapaddr);
	kमुक्त(info->desc_info);
पूर्ण

अटल व्योम rocker_dma_ring_pass_to_producer(स्थिर काष्ठा rocker *rocker,
					     काष्ठा rocker_dma_ring_info *info)
अणु
	पूर्णांक i;

	BUG_ON(info->head || info->tail);

	/* When ring is consumer, we need to advance head क्रम each desc.
	 * That tells hw that the desc is पढ़ोy to be used by it.
	 */
	क्रम (i = 0; i < info->size - 1; i++)
		rocker_desc_head_set(rocker, info, &info->desc_info[i]);
	rocker_desc_commit(&info->desc_info[i]);
पूर्ण

अटल पूर्णांक rocker_dma_ring_bufs_alloc(स्थिर काष्ठा rocker *rocker,
				      स्थिर काष्ठा rocker_dma_ring_info *info,
				      पूर्णांक direction, माप_प्रकार buf_size)
अणु
	काष्ठा pci_dev *pdev = rocker->pdev;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < info->size; i++) अणु
		काष्ठा rocker_desc_info *desc_info = &info->desc_info[i];
		काष्ठा rocker_desc *desc = &info->desc[i];
		dma_addr_t dma_handle;
		अक्षर *buf;

		buf = kzalloc(buf_size, GFP_KERNEL | GFP_DMA);
		अगर (!buf) अणु
			err = -ENOMEM;
			जाओ rollback;
		पूर्ण

		dma_handle = dma_map_single(&pdev->dev, buf, buf_size,
					    direction);
		अगर (dma_mapping_error(&pdev->dev, dma_handle)) अणु
			kमुक्त(buf);
			err = -EIO;
			जाओ rollback;
		पूर्ण

		desc_info->data = buf;
		desc_info->data_size = buf_size;
		dma_unmap_addr_set(desc_info, mapaddr, dma_handle);

		desc->buf_addr = dma_handle;
		desc->buf_size = buf_size;
	पूर्ण
	वापस 0;

rollback:
	क्रम (i--; i >= 0; i--) अणु
		स्थिर काष्ठा rocker_desc_info *desc_info = &info->desc_info[i];

		dma_unmap_single(&pdev->dev,
				 dma_unmap_addr(desc_info, mapaddr),
				 desc_info->data_size, direction);
		kमुक्त(desc_info->data);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम rocker_dma_ring_bufs_मुक्त(स्थिर काष्ठा rocker *rocker,
				      स्थिर काष्ठा rocker_dma_ring_info *info,
				      पूर्णांक direction)
अणु
	काष्ठा pci_dev *pdev = rocker->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < info->size; i++) अणु
		स्थिर काष्ठा rocker_desc_info *desc_info = &info->desc_info[i];
		काष्ठा rocker_desc *desc = &info->desc[i];

		desc->buf_addr = 0;
		desc->buf_size = 0;
		dma_unmap_single(&pdev->dev,
				 dma_unmap_addr(desc_info, mapaddr),
				 desc_info->data_size, direction);
		kमुक्त(desc_info->data);
	पूर्ण
पूर्ण

अटल पूर्णांक rocker_dma_cmd_ring_रुको_alloc(काष्ठा rocker_desc_info *desc_info)
अणु
	काष्ठा rocker_रुको *रुको;

	रुको = rocker_रुको_create();
	अगर (!रुको)
		वापस -ENOMEM;
	rocker_desc_cookie_ptr_set(desc_info, रुको);
	वापस 0;
पूर्ण

अटल व्योम
rocker_dma_cmd_ring_रुको_मुक्त(स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	काष्ठा rocker_रुको *रुको = rocker_desc_cookie_ptr_get(desc_info);

	rocker_रुको_destroy(रुको);
पूर्ण

अटल पूर्णांक rocker_dma_cmd_ring_रुकोs_alloc(स्थिर काष्ठा rocker *rocker)
अणु
	स्थिर काष्ठा rocker_dma_ring_info *cmd_ring = &rocker->cmd_ring;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < cmd_ring->size; i++) अणु
		err = rocker_dma_cmd_ring_रुको_alloc(&cmd_ring->desc_info[i]);
		अगर (err)
			जाओ rollback;
	पूर्ण
	वापस 0;

rollback:
	क्रम (i--; i >= 0; i--)
		rocker_dma_cmd_ring_रुको_मुक्त(&cmd_ring->desc_info[i]);
	वापस err;
पूर्ण

अटल व्योम rocker_dma_cmd_ring_रुकोs_मुक्त(स्थिर काष्ठा rocker *rocker)
अणु
	स्थिर काष्ठा rocker_dma_ring_info *cmd_ring = &rocker->cmd_ring;
	पूर्णांक i;

	क्रम (i = 0; i < cmd_ring->size; i++)
		rocker_dma_cmd_ring_रुको_मुक्त(&cmd_ring->desc_info[i]);
पूर्ण

अटल पूर्णांक rocker_dma_rings_init(काष्ठा rocker *rocker)
अणु
	स्थिर काष्ठा pci_dev *pdev = rocker->pdev;
	पूर्णांक err;

	err = rocker_dma_ring_create(rocker, ROCKER_DMA_CMD,
				     ROCKER_DMA_CMD_DEFAULT_SIZE,
				     &rocker->cmd_ring);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to create command dma ring\n");
		वापस err;
	पूर्ण

	spin_lock_init(&rocker->cmd_ring_lock);

	err = rocker_dma_ring_bufs_alloc(rocker, &rocker->cmd_ring,
					 DMA_BIसूचीECTIONAL, PAGE_SIZE);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to alloc command dma ring buffers\n");
		जाओ err_dma_cmd_ring_bufs_alloc;
	पूर्ण

	err = rocker_dma_cmd_ring_रुकोs_alloc(rocker);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to alloc command dma ring waits\n");
		जाओ err_dma_cmd_ring_रुकोs_alloc;
	पूर्ण

	err = rocker_dma_ring_create(rocker, ROCKER_DMA_EVENT,
				     ROCKER_DMA_EVENT_DEFAULT_SIZE,
				     &rocker->event_ring);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to create event dma ring\n");
		जाओ err_dma_event_ring_create;
	पूर्ण

	err = rocker_dma_ring_bufs_alloc(rocker, &rocker->event_ring,
					 DMA_FROM_DEVICE, PAGE_SIZE);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to alloc event dma ring buffers\n");
		जाओ err_dma_event_ring_bufs_alloc;
	पूर्ण
	rocker_dma_ring_pass_to_producer(rocker, &rocker->event_ring);
	वापस 0;

err_dma_event_ring_bufs_alloc:
	rocker_dma_ring_destroy(rocker, &rocker->event_ring);
err_dma_event_ring_create:
	rocker_dma_cmd_ring_रुकोs_मुक्त(rocker);
err_dma_cmd_ring_रुकोs_alloc:
	rocker_dma_ring_bufs_मुक्त(rocker, &rocker->cmd_ring,
				  DMA_BIसूचीECTIONAL);
err_dma_cmd_ring_bufs_alloc:
	rocker_dma_ring_destroy(rocker, &rocker->cmd_ring);
	वापस err;
पूर्ण

अटल व्योम rocker_dma_rings_fini(काष्ठा rocker *rocker)
अणु
	rocker_dma_ring_bufs_मुक्त(rocker, &rocker->event_ring,
				  DMA_BIसूचीECTIONAL);
	rocker_dma_ring_destroy(rocker, &rocker->event_ring);
	rocker_dma_cmd_ring_रुकोs_मुक्त(rocker);
	rocker_dma_ring_bufs_मुक्त(rocker, &rocker->cmd_ring,
				  DMA_BIसूचीECTIONAL);
	rocker_dma_ring_destroy(rocker, &rocker->cmd_ring);
पूर्ण

अटल पूर्णांक rocker_dma_rx_ring_skb_map(स्थिर काष्ठा rocker_port *rocker_port,
				      काष्ठा rocker_desc_info *desc_info,
				      काष्ठा sk_buff *skb, माप_प्रकार buf_len)
अणु
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	काष्ठा pci_dev *pdev = rocker->pdev;
	dma_addr_t dma_handle;

	dma_handle = dma_map_single(&pdev->dev, skb->data, buf_len,
				    DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, dma_handle))
		वापस -EIO;
	अगर (rocker_tlv_put_u64(desc_info, ROCKER_TLV_RX_FRAG_ADDR, dma_handle))
		जाओ tlv_put_failure;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_RX_FRAG_MAX_LEN, buf_len))
		जाओ tlv_put_failure;
	वापस 0;

tlv_put_failure:
	dma_unmap_single(&pdev->dev, dma_handle, buf_len, DMA_FROM_DEVICE);
	desc_info->tlv_size = 0;
	वापस -EMSGSIZE;
पूर्ण

अटल माप_प्रकार rocker_port_rx_buf_len(स्थिर काष्ठा rocker_port *rocker_port)
अणु
	वापस rocker_port->dev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
पूर्ण

अटल पूर्णांक rocker_dma_rx_ring_skb_alloc(स्थिर काष्ठा rocker_port *rocker_port,
					काष्ठा rocker_desc_info *desc_info)
अणु
	काष्ठा net_device *dev = rocker_port->dev;
	काष्ठा sk_buff *skb;
	माप_प्रकार buf_len = rocker_port_rx_buf_len(rocker_port);
	पूर्णांक err;

	/* Ensure that hw will see tlv_size zero in हाल of an error.
	 * That tells hw to use another descriptor.
	 */
	rocker_desc_cookie_ptr_set(desc_info, शून्य);
	desc_info->tlv_size = 0;

	skb = netdev_alloc_skb_ip_align(dev, buf_len);
	अगर (!skb)
		वापस -ENOMEM;
	err = rocker_dma_rx_ring_skb_map(rocker_port, desc_info, skb, buf_len);
	अगर (err) अणु
		dev_kमुक्त_skb_any(skb);
		वापस err;
	पूर्ण
	rocker_desc_cookie_ptr_set(desc_info, skb);
	वापस 0;
पूर्ण

अटल व्योम rocker_dma_rx_ring_skb_unmap(स्थिर काष्ठा rocker *rocker,
					 स्थिर काष्ठा rocker_tlv **attrs)
अणु
	काष्ठा pci_dev *pdev = rocker->pdev;
	dma_addr_t dma_handle;
	माप_प्रकार len;

	अगर (!attrs[ROCKER_TLV_RX_FRAG_ADDR] ||
	    !attrs[ROCKER_TLV_RX_FRAG_MAX_LEN])
		वापस;
	dma_handle = rocker_tlv_get_u64(attrs[ROCKER_TLV_RX_FRAG_ADDR]);
	len = rocker_tlv_get_u16(attrs[ROCKER_TLV_RX_FRAG_MAX_LEN]);
	dma_unmap_single(&pdev->dev, dma_handle, len, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम rocker_dma_rx_ring_skb_मुक्त(स्थिर काष्ठा rocker *rocker,
					स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_RX_MAX + 1];
	काष्ठा sk_buff *skb = rocker_desc_cookie_ptr_get(desc_info);

	अगर (!skb)
		वापस;
	rocker_tlv_parse_desc(attrs, ROCKER_TLV_RX_MAX, desc_info);
	rocker_dma_rx_ring_skb_unmap(rocker, attrs);
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल पूर्णांक rocker_dma_rx_ring_skbs_alloc(स्थिर काष्ठा rocker_port *rocker_port)
अणु
	स्थिर काष्ठा rocker_dma_ring_info *rx_ring = &rocker_port->rx_ring;
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < rx_ring->size; i++) अणु
		err = rocker_dma_rx_ring_skb_alloc(rocker_port,
						   &rx_ring->desc_info[i]);
		अगर (err)
			जाओ rollback;
	पूर्ण
	वापस 0;

rollback:
	क्रम (i--; i >= 0; i--)
		rocker_dma_rx_ring_skb_मुक्त(rocker, &rx_ring->desc_info[i]);
	वापस err;
पूर्ण

अटल व्योम rocker_dma_rx_ring_skbs_मुक्त(स्थिर काष्ठा rocker_port *rocker_port)
अणु
	स्थिर काष्ठा rocker_dma_ring_info *rx_ring = &rocker_port->rx_ring;
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	पूर्णांक i;

	क्रम (i = 0; i < rx_ring->size; i++)
		rocker_dma_rx_ring_skb_मुक्त(rocker, &rx_ring->desc_info[i]);
पूर्ण

अटल पूर्णांक rocker_port_dma_rings_init(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker *rocker = rocker_port->rocker;
	पूर्णांक err;

	err = rocker_dma_ring_create(rocker,
				     ROCKER_DMA_TX(rocker_port->port_number),
				     ROCKER_DMA_TX_DEFAULT_SIZE,
				     &rocker_port->tx_ring);
	अगर (err) अणु
		netdev_err(rocker_port->dev, "failed to create tx dma ring\n");
		वापस err;
	पूर्ण

	err = rocker_dma_ring_bufs_alloc(rocker, &rocker_port->tx_ring,
					 DMA_TO_DEVICE,
					 ROCKER_DMA_TX_DESC_SIZE);
	अगर (err) अणु
		netdev_err(rocker_port->dev, "failed to alloc tx dma ring buffers\n");
		जाओ err_dma_tx_ring_bufs_alloc;
	पूर्ण

	err = rocker_dma_ring_create(rocker,
				     ROCKER_DMA_RX(rocker_port->port_number),
				     ROCKER_DMA_RX_DEFAULT_SIZE,
				     &rocker_port->rx_ring);
	अगर (err) अणु
		netdev_err(rocker_port->dev, "failed to create rx dma ring\n");
		जाओ err_dma_rx_ring_create;
	पूर्ण

	err = rocker_dma_ring_bufs_alloc(rocker, &rocker_port->rx_ring,
					 DMA_BIसूचीECTIONAL,
					 ROCKER_DMA_RX_DESC_SIZE);
	अगर (err) अणु
		netdev_err(rocker_port->dev, "failed to alloc rx dma ring buffers\n");
		जाओ err_dma_rx_ring_bufs_alloc;
	पूर्ण

	err = rocker_dma_rx_ring_skbs_alloc(rocker_port);
	अगर (err) अणु
		netdev_err(rocker_port->dev, "failed to alloc rx dma ring skbs\n");
		जाओ err_dma_rx_ring_skbs_alloc;
	पूर्ण
	rocker_dma_ring_pass_to_producer(rocker, &rocker_port->rx_ring);

	वापस 0;

err_dma_rx_ring_skbs_alloc:
	rocker_dma_ring_bufs_मुक्त(rocker, &rocker_port->rx_ring,
				  DMA_BIसूचीECTIONAL);
err_dma_rx_ring_bufs_alloc:
	rocker_dma_ring_destroy(rocker, &rocker_port->rx_ring);
err_dma_rx_ring_create:
	rocker_dma_ring_bufs_मुक्त(rocker, &rocker_port->tx_ring,
				  DMA_TO_DEVICE);
err_dma_tx_ring_bufs_alloc:
	rocker_dma_ring_destroy(rocker, &rocker_port->tx_ring);
	वापस err;
पूर्ण

अटल व्योम rocker_port_dma_rings_fini(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker *rocker = rocker_port->rocker;

	rocker_dma_rx_ring_skbs_मुक्त(rocker_port);
	rocker_dma_ring_bufs_मुक्त(rocker, &rocker_port->rx_ring,
				  DMA_BIसूचीECTIONAL);
	rocker_dma_ring_destroy(rocker, &rocker_port->rx_ring);
	rocker_dma_ring_bufs_मुक्त(rocker, &rocker_port->tx_ring,
				  DMA_TO_DEVICE);
	rocker_dma_ring_destroy(rocker, &rocker_port->tx_ring);
पूर्ण

अटल व्योम rocker_port_set_enable(स्थिर काष्ठा rocker_port *rocker_port,
				   bool enable)
अणु
	u64 val = rocker_पढ़ो64(rocker_port->rocker, PORT_PHYS_ENABLE);

	अगर (enable)
		val |= 1ULL << rocker_port->pport;
	अन्यथा
		val &= ~(1ULL << rocker_port->pport);
	rocker_ग_लिखो64(rocker_port->rocker, PORT_PHYS_ENABLE, val);
पूर्ण

/********************************
 * Interrupt handler and helpers
 ********************************/

अटल irqवापस_t rocker_cmd_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rocker *rocker = dev_id;
	स्थिर काष्ठा rocker_desc_info *desc_info;
	काष्ठा rocker_रुको *रुको;
	u32 credits = 0;

	spin_lock(&rocker->cmd_ring_lock);
	जबतक ((desc_info = rocker_desc_tail_get(&rocker->cmd_ring))) अणु
		रुको = rocker_desc_cookie_ptr_get(desc_info);
		अगर (रुको->noरुको) अणु
			rocker_desc_gen_clear(desc_info);
		पूर्ण अन्यथा अणु
			rocker_रुको_wake_up(रुको);
		पूर्ण
		credits++;
	पूर्ण
	spin_unlock(&rocker->cmd_ring_lock);
	rocker_dma_ring_credits_set(rocker, &rocker->cmd_ring, credits);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rocker_port_link_up(स्थिर काष्ठा rocker_port *rocker_port)
अणु
	netअगर_carrier_on(rocker_port->dev);
	netdev_info(rocker_port->dev, "Link is up\n");
पूर्ण

अटल व्योम rocker_port_link_करोwn(स्थिर काष्ठा rocker_port *rocker_port)
अणु
	netअगर_carrier_off(rocker_port->dev);
	netdev_info(rocker_port->dev, "Link is down\n");
पूर्ण

अटल पूर्णांक rocker_event_link_change(स्थिर काष्ठा rocker *rocker,
				    स्थिर काष्ठा rocker_tlv *info)
अणु
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_EVENT_LINK_CHANGED_MAX + 1];
	अचिन्हित पूर्णांक port_number;
	bool link_up;
	काष्ठा rocker_port *rocker_port;

	rocker_tlv_parse_nested(attrs, ROCKER_TLV_EVENT_LINK_CHANGED_MAX, info);
	अगर (!attrs[ROCKER_TLV_EVENT_LINK_CHANGED_PPORT] ||
	    !attrs[ROCKER_TLV_EVENT_LINK_CHANGED_LINKUP])
		वापस -EIO;
	port_number =
		rocker_tlv_get_u32(attrs[ROCKER_TLV_EVENT_LINK_CHANGED_PPORT]) - 1;
	link_up = rocker_tlv_get_u8(attrs[ROCKER_TLV_EVENT_LINK_CHANGED_LINKUP]);

	अगर (port_number >= rocker->port_count)
		वापस -EINVAL;

	rocker_port = rocker->ports[port_number];
	अगर (netअगर_carrier_ok(rocker_port->dev) != link_up) अणु
		अगर (link_up)
			rocker_port_link_up(rocker_port);
		अन्यथा
			rocker_port_link_करोwn(rocker_port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rocker_world_port_ev_mac_vlan_seen(काष्ठा rocker_port *rocker_port,
					      स्थिर अचिन्हित अक्षर *addr,
					      __be16 vlan_id);

अटल पूर्णांक rocker_event_mac_vlan_seen(स्थिर काष्ठा rocker *rocker,
				      स्थिर काष्ठा rocker_tlv *info)
अणु
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_EVENT_MAC_VLAN_MAX + 1];
	अचिन्हित पूर्णांक port_number;
	काष्ठा rocker_port *rocker_port;
	स्थिर अचिन्हित अक्षर *addr;
	__be16 vlan_id;

	rocker_tlv_parse_nested(attrs, ROCKER_TLV_EVENT_MAC_VLAN_MAX, info);
	अगर (!attrs[ROCKER_TLV_EVENT_MAC_VLAN_PPORT] ||
	    !attrs[ROCKER_TLV_EVENT_MAC_VLAN_MAC] ||
	    !attrs[ROCKER_TLV_EVENT_MAC_VLAN_VLAN_ID])
		वापस -EIO;
	port_number =
		rocker_tlv_get_u32(attrs[ROCKER_TLV_EVENT_MAC_VLAN_PPORT]) - 1;
	addr = rocker_tlv_data(attrs[ROCKER_TLV_EVENT_MAC_VLAN_MAC]);
	vlan_id = rocker_tlv_get_be16(attrs[ROCKER_TLV_EVENT_MAC_VLAN_VLAN_ID]);

	अगर (port_number >= rocker->port_count)
		वापस -EINVAL;

	rocker_port = rocker->ports[port_number];
	वापस rocker_world_port_ev_mac_vlan_seen(rocker_port, addr, vlan_id);
पूर्ण

अटल पूर्णांक rocker_event_process(स्थिर काष्ठा rocker *rocker,
				स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_EVENT_MAX + 1];
	स्थिर काष्ठा rocker_tlv *info;
	u16 type;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_EVENT_MAX, desc_info);
	अगर (!attrs[ROCKER_TLV_EVENT_TYPE] ||
	    !attrs[ROCKER_TLV_EVENT_INFO])
		वापस -EIO;

	type = rocker_tlv_get_u16(attrs[ROCKER_TLV_EVENT_TYPE]);
	info = attrs[ROCKER_TLV_EVENT_INFO];

	चयन (type) अणु
	हाल ROCKER_TLV_EVENT_TYPE_LINK_CHANGED:
		वापस rocker_event_link_change(rocker, info);
	हाल ROCKER_TLV_EVENT_TYPE_MAC_VLAN_SEEN:
		वापस rocker_event_mac_vlan_seen(rocker, info);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल irqवापस_t rocker_event_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rocker *rocker = dev_id;
	स्थिर काष्ठा pci_dev *pdev = rocker->pdev;
	स्थिर काष्ठा rocker_desc_info *desc_info;
	u32 credits = 0;
	पूर्णांक err;

	जबतक ((desc_info = rocker_desc_tail_get(&rocker->event_ring))) अणु
		err = rocker_desc_err(desc_info);
		अगर (err) अणु
			dev_err(&pdev->dev, "event desc received with err %d\n",
				err);
		पूर्ण अन्यथा अणु
			err = rocker_event_process(rocker, desc_info);
			अगर (err)
				dev_err(&pdev->dev, "event processing failed with err %d\n",
					err);
		पूर्ण
		rocker_desc_gen_clear(desc_info);
		rocker_desc_head_set(rocker, &rocker->event_ring, desc_info);
		credits++;
	पूर्ण
	rocker_dma_ring_credits_set(rocker, &rocker->event_ring, credits);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rocker_tx_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rocker_port *rocker_port = dev_id;

	napi_schedule(&rocker_port->napi_tx);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rocker_rx_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rocker_port *rocker_port = dev_id;

	napi_schedule(&rocker_port->napi_rx);
	वापस IRQ_HANDLED;
पूर्ण

/********************
 * Command पूर्णांकerface
 ********************/

पूर्णांक rocker_cmd_exec(काष्ठा rocker_port *rocker_port, bool noरुको,
		    rocker_cmd_prep_cb_t prepare, व्योम *prepare_priv,
		    rocker_cmd_proc_cb_t process, व्योम *process_priv)
अणु
	काष्ठा rocker *rocker = rocker_port->rocker;
	काष्ठा rocker_desc_info *desc_info;
	काष्ठा rocker_रुको *रुको;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक err;

	spin_lock_irqsave(&rocker->cmd_ring_lock, lock_flags);

	desc_info = rocker_desc_head_get(&rocker->cmd_ring);
	अगर (!desc_info) अणु
		spin_unlock_irqrestore(&rocker->cmd_ring_lock, lock_flags);
		वापस -EAGAIN;
	पूर्ण

	रुको = rocker_desc_cookie_ptr_get(desc_info);
	rocker_रुको_init(रुको);
	रुको->noरुको = noरुको;

	err = prepare(rocker_port, desc_info, prepare_priv);
	अगर (err) अणु
		spin_unlock_irqrestore(&rocker->cmd_ring_lock, lock_flags);
		वापस err;
	पूर्ण

	rocker_desc_head_set(rocker, &rocker->cmd_ring, desc_info);

	spin_unlock_irqrestore(&rocker->cmd_ring_lock, lock_flags);

	अगर (noरुको)
		वापस 0;

	अगर (!rocker_रुको_event_समयout(रुको, HZ / 10))
		वापस -EIO;

	err = rocker_desc_err(desc_info);
	अगर (err)
		वापस err;

	अगर (process)
		err = process(rocker_port, desc_info, process_priv);

	rocker_desc_gen_clear(desc_info);
	वापस err;
पूर्ण

अटल पूर्णांक
rocker_cmd_get_port_settings_prep(स्थिर काष्ठा rocker_port *rocker_port,
				  काष्ठा rocker_desc_info *desc_info,
				  व्योम *priv)
अणु
	काष्ठा rocker_tlv *cmd_info;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE,
			       ROCKER_TLV_CMD_TYPE_GET_PORT_SETTINGS))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_PPORT,
			       rocker_port->pport))
		वापस -EMSGSIZE;
	rocker_tlv_nest_end(desc_info, cmd_info);
	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_get_port_settings_ethtool_proc(स्थिर काष्ठा rocker_port *rocker_port,
					  स्थिर काष्ठा rocker_desc_info *desc_info,
					  व्योम *priv)
अणु
	काष्ठा ethtool_link_ksettings *ecmd = priv;
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	स्थिर काष्ठा rocker_tlv *info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MAX + 1];
	u32 speed;
	u8 duplex;
	u8 स्वतःneg;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);
	अगर (!attrs[ROCKER_TLV_CMD_INFO])
		वापस -EIO;

	rocker_tlv_parse_nested(info_attrs, ROCKER_TLV_CMD_PORT_SETTINGS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);
	अगर (!info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_SPEED] ||
	    !info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_DUPLEX] ||
	    !info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_AUTONEG])
		वापस -EIO;

	speed = rocker_tlv_get_u32(info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_SPEED]);
	duplex = rocker_tlv_get_u8(info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_DUPLEX]);
	स्वतःneg = rocker_tlv_get_u8(info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_AUTONEG]);

	ethtool_link_ksettings_zero_link_mode(ecmd, supported);
	ethtool_link_ksettings_add_link_mode(ecmd, supported, TP);

	ecmd->base.phy_address = 0xff;
	ecmd->base.port = PORT_TP;
	ecmd->base.speed = speed;
	ecmd->base.duplex = duplex ? DUPLEX_FULL : DUPLEX_HALF;
	ecmd->base.स्वतःneg = स्वतःneg ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_get_port_settings_macaddr_proc(स्थिर काष्ठा rocker_port *rocker_port,
					  स्थिर काष्ठा rocker_desc_info *desc_info,
					  व्योम *priv)
अणु
	अचिन्हित अक्षर *macaddr = priv;
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	स्थिर काष्ठा rocker_tlv *info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MAX + 1];
	स्थिर काष्ठा rocker_tlv *attr;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);
	अगर (!attrs[ROCKER_TLV_CMD_INFO])
		वापस -EIO;

	rocker_tlv_parse_nested(info_attrs, ROCKER_TLV_CMD_PORT_SETTINGS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);
	attr = info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MACADDR];
	अगर (!attr)
		वापस -EIO;

	अगर (rocker_tlv_len(attr) != ETH_ALEN)
		वापस -EINVAL;

	ether_addr_copy(macaddr, rocker_tlv_data(attr));
	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_get_port_settings_mode_proc(स्थिर काष्ठा rocker_port *rocker_port,
				       स्थिर काष्ठा rocker_desc_info *desc_info,
				       व्योम *priv)
अणु
	u8 *p_mode = priv;
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	स्थिर काष्ठा rocker_tlv *info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MAX + 1];
	स्थिर काष्ठा rocker_tlv *attr;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);
	अगर (!attrs[ROCKER_TLV_CMD_INFO])
		वापस -EIO;

	rocker_tlv_parse_nested(info_attrs, ROCKER_TLV_CMD_PORT_SETTINGS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);
	attr = info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MODE];
	अगर (!attr)
		वापस -EIO;

	*p_mode = rocker_tlv_get_u8(info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MODE]);
	वापस 0;
पूर्ण

काष्ठा port_name अणु
	अक्षर *buf;
	माप_प्रकार len;
पूर्ण;

अटल पूर्णांक
rocker_cmd_get_port_settings_phys_name_proc(स्थिर काष्ठा rocker_port *rocker_port,
					    स्थिर काष्ठा rocker_desc_info *desc_info,
					    व्योम *priv)
अणु
	स्थिर काष्ठा rocker_tlv *info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MAX + 1];
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	काष्ठा port_name *name = priv;
	स्थिर काष्ठा rocker_tlv *attr;
	माप_प्रकार i, j, len;
	स्थिर अक्षर *str;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);
	अगर (!attrs[ROCKER_TLV_CMD_INFO])
		वापस -EIO;

	rocker_tlv_parse_nested(info_attrs, ROCKER_TLV_CMD_PORT_SETTINGS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);
	attr = info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_PHYS_NAME];
	अगर (!attr)
		वापस -EIO;

	len = min_t(माप_प्रकार, rocker_tlv_len(attr), name->len);
	str = rocker_tlv_data(attr);

	/* make sure name only contains alphanumeric अक्षरacters */
	क्रम (i = j = 0; i < len; ++i) अणु
		अगर (है_अक्षर_अंक(str[i])) अणु
			name->buf[j] = str[i];
			j++;
		पूर्ण
	पूर्ण

	अगर (j == 0)
		वापस -EIO;

	name->buf[j] = '\0';

	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_set_port_settings_ethtool_prep(स्थिर काष्ठा rocker_port *rocker_port,
					  काष्ठा rocker_desc_info *desc_info,
					  व्योम *priv)
अणु
	काष्ठा ethtool_link_ksettings *ecmd = priv;
	काष्ठा rocker_tlv *cmd_info;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE,
			       ROCKER_TLV_CMD_TYPE_SET_PORT_SETTINGS))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_PPORT,
			       rocker_port->pport))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_SPEED,
			       ecmd->base.speed))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u8(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_DUPLEX,
			      ecmd->base.duplex))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u8(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_AUTONEG,
			      ecmd->base.स्वतःneg))
		वापस -EMSGSIZE;
	rocker_tlv_nest_end(desc_info, cmd_info);
	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_set_port_settings_macaddr_prep(स्थिर काष्ठा rocker_port *rocker_port,
					  काष्ठा rocker_desc_info *desc_info,
					  व्योम *priv)
अणु
	स्थिर अचिन्हित अक्षर *macaddr = priv;
	काष्ठा rocker_tlv *cmd_info;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE,
			       ROCKER_TLV_CMD_TYPE_SET_PORT_SETTINGS))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_PPORT,
			       rocker_port->pport))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_MACADDR,
			   ETH_ALEN, macaddr))
		वापस -EMSGSIZE;
	rocker_tlv_nest_end(desc_info, cmd_info);
	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_set_port_settings_mtu_prep(स्थिर काष्ठा rocker_port *rocker_port,
				      काष्ठा rocker_desc_info *desc_info,
				      व्योम *priv)
अणु
	पूर्णांक mtu = *(पूर्णांक *)priv;
	काष्ठा rocker_tlv *cmd_info;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE,
			       ROCKER_TLV_CMD_TYPE_SET_PORT_SETTINGS))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_PPORT,
			       rocker_port->pport))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_MTU,
			       mtu))
		वापस -EMSGSIZE;
	rocker_tlv_nest_end(desc_info, cmd_info);
	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_set_port_learning_prep(स्थिर काष्ठा rocker_port *rocker_port,
				  काष्ठा rocker_desc_info *desc_info,
				  व्योम *priv)
अणु
	bool learning = *(bool *)priv;
	काष्ठा rocker_tlv *cmd_info;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE,
			       ROCKER_TLV_CMD_TYPE_SET_PORT_SETTINGS))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_PPORT,
			       rocker_port->pport))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u8(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_LEARNING,
			      learning))
		वापस -EMSGSIZE;
	rocker_tlv_nest_end(desc_info, cmd_info);
	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_get_port_settings_ethtool(काष्ठा rocker_port *rocker_port,
				     काष्ठा ethtool_link_ksettings *ecmd)
अणु
	वापस rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_get_port_settings_prep, शून्य,
			       rocker_cmd_get_port_settings_ethtool_proc,
			       ecmd);
पूर्ण

अटल पूर्णांक rocker_cmd_get_port_settings_macaddr(काष्ठा rocker_port *rocker_port,
						अचिन्हित अक्षर *macaddr)
अणु
	वापस rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_get_port_settings_prep, शून्य,
			       rocker_cmd_get_port_settings_macaddr_proc,
			       macaddr);
पूर्ण

अटल पूर्णांक rocker_cmd_get_port_settings_mode(काष्ठा rocker_port *rocker_port,
					     u8 *p_mode)
अणु
	वापस rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_get_port_settings_prep, शून्य,
			       rocker_cmd_get_port_settings_mode_proc, p_mode);
पूर्ण

अटल पूर्णांक
rocker_cmd_set_port_settings_ethtool(काष्ठा rocker_port *rocker_port,
				     स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा ethtool_link_ksettings copy_ecmd;

	स_नकल(&copy_ecmd, ecmd, माप(copy_ecmd));

	वापस rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_set_port_settings_ethtool_prep,
			       &copy_ecmd, शून्य, शून्य);
पूर्ण

अटल पूर्णांक rocker_cmd_set_port_settings_macaddr(काष्ठा rocker_port *rocker_port,
						अचिन्हित अक्षर *macaddr)
अणु
	वापस rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_set_port_settings_macaddr_prep,
			       macaddr, शून्य, शून्य);
पूर्ण

अटल पूर्णांक rocker_cmd_set_port_settings_mtu(काष्ठा rocker_port *rocker_port,
					    पूर्णांक mtu)
अणु
	वापस rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_set_port_settings_mtu_prep,
			       &mtu, शून्य, शून्य);
पूर्ण

पूर्णांक rocker_port_set_learning(काष्ठा rocker_port *rocker_port,
			     bool learning)
अणु
	वापस rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_set_port_learning_prep,
			       &learning, शून्य, शून्य);
पूर्ण

/**********************
 * Worlds manipulation
 **********************/

अटल काष्ठा rocker_world_ops *rocker_world_ops[] = अणु
	&rocker_ofdpa_ops,
पूर्ण;

#घोषणा ROCKER_WORLD_OPS_LEN ARRAY_SIZE(rocker_world_ops)

अटल काष्ठा rocker_world_ops *rocker_world_ops_find(u8 mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ROCKER_WORLD_OPS_LEN; i++)
		अगर (rocker_world_ops[i]->mode == mode)
			वापस rocker_world_ops[i];
	वापस शून्य;
पूर्ण

अटल पूर्णांक rocker_world_init(काष्ठा rocker *rocker, u8 mode)
अणु
	काष्ठा rocker_world_ops *wops;
	पूर्णांक err;

	wops = rocker_world_ops_find(mode);
	अगर (!wops) अणु
		dev_err(&rocker->pdev->dev, "port mode \"%d\" is not supported\n",
			mode);
		वापस -EINVAL;
	पूर्ण
	rocker->wops = wops;
	rocker->wpriv = kzalloc(wops->priv_size, GFP_KERNEL);
	अगर (!rocker->wpriv)
		वापस -ENOMEM;
	अगर (!wops->init)
		वापस 0;
	err = wops->init(rocker);
	अगर (err)
		kमुक्त(rocker->wpriv);
	वापस err;
पूर्ण

अटल व्योम rocker_world_fini(काष्ठा rocker *rocker)
अणु
	काष्ठा rocker_world_ops *wops = rocker->wops;

	अगर (!wops || !wops->fini)
		वापस;
	wops->fini(rocker);
	kमुक्त(rocker->wpriv);
पूर्ण

अटल पूर्णांक rocker_world_check_init(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker *rocker = rocker_port->rocker;
	u8 mode;
	पूर्णांक err;

	err = rocker_cmd_get_port_settings_mode(rocker_port, &mode);
	अगर (err) अणु
		dev_err(&rocker->pdev->dev, "failed to get port mode\n");
		वापस err;
	पूर्ण
	अगर (rocker->wops) अणु
		अगर (rocker->wops->mode != mode) अणु
			dev_err(&rocker->pdev->dev, "hardware has ports in different worlds, which is not supported\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस rocker_world_init(rocker, mode);
पूर्ण

अटल पूर्णांक rocker_world_port_pre_init(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;
	पूर्णांक err;

	rocker_port->wpriv = kzalloc(wops->port_priv_size, GFP_KERNEL);
	अगर (!rocker_port->wpriv)
		वापस -ENOMEM;
	अगर (!wops->port_pre_init)
		वापस 0;
	err = wops->port_pre_init(rocker_port);
	अगर (err)
		kमुक्त(rocker_port->wpriv);
	वापस 0;
पूर्ण

अटल पूर्णांक rocker_world_port_init(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_init)
		वापस 0;
	वापस wops->port_init(rocker_port);
पूर्ण

अटल व्योम rocker_world_port_fini(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_fini)
		वापस;
	wops->port_fini(rocker_port);
पूर्ण

अटल व्योम rocker_world_port_post_fini(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_post_fini)
		वापस;
	wops->port_post_fini(rocker_port);
	kमुक्त(rocker_port->wpriv);
पूर्ण

अटल पूर्णांक rocker_world_port_खोलो(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_खोलो)
		वापस 0;
	वापस wops->port_खोलो(rocker_port);
पूर्ण

अटल व्योम rocker_world_port_stop(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_stop)
		वापस;
	wops->port_stop(rocker_port);
पूर्ण

अटल पूर्णांक rocker_world_port_attr_stp_state_set(काष्ठा rocker_port *rocker_port,
						u8 state)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_attr_stp_state_set)
		वापस -EOPNOTSUPP;

	वापस wops->port_attr_stp_state_set(rocker_port, state);
पूर्ण

अटल पूर्णांक
rocker_world_port_attr_bridge_flags_support_get(स्थिर काष्ठा rocker_port *
						rocker_port,
						अचिन्हित दीर्घ *
						p_brport_flags_support)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_attr_bridge_flags_support_get)
		वापस -EOPNOTSUPP;
	वापस wops->port_attr_bridge_flags_support_get(rocker_port,
							p_brport_flags_support);
पूर्ण

अटल पूर्णांक
rocker_world_port_attr_pre_bridge_flags_set(काष्ठा rocker_port *rocker_port,
					    काष्ठा चयनdev_brport_flags flags)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;
	अचिन्हित दीर्घ brport_flags_s;
	पूर्णांक err;

	अगर (!wops->port_attr_bridge_flags_set)
		वापस -EOPNOTSUPP;

	err = rocker_world_port_attr_bridge_flags_support_get(rocker_port,
							      &brport_flags_s);
	अगर (err)
		वापस err;

	अगर (flags.mask & ~brport_flags_s)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_world_port_attr_bridge_flags_set(काष्ठा rocker_port *rocker_port,
					काष्ठा चयनdev_brport_flags flags)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_attr_bridge_flags_set)
		वापस -EOPNOTSUPP;

	वापस wops->port_attr_bridge_flags_set(rocker_port, flags.val);
पूर्ण

अटल पूर्णांक
rocker_world_port_attr_bridge_ageing_समय_set(काष्ठा rocker_port *rocker_port,
					      u32 ageing_समय)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_attr_bridge_ageing_समय_set)
		वापस -EOPNOTSUPP;

	वापस wops->port_attr_bridge_ageing_समय_set(rocker_port, ageing_समय);
पूर्ण

अटल पूर्णांक
rocker_world_port_obj_vlan_add(काष्ठा rocker_port *rocker_port,
			       स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_obj_vlan_add)
		वापस -EOPNOTSUPP;

	वापस wops->port_obj_vlan_add(rocker_port, vlan);
पूर्ण

अटल पूर्णांक
rocker_world_port_obj_vlan_del(काष्ठा rocker_port *rocker_port,
			       स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (netअगर_is_bridge_master(vlan->obj.orig_dev))
		वापस -EOPNOTSUPP;

	अगर (!wops->port_obj_vlan_del)
		वापस -EOPNOTSUPP;
	वापस wops->port_obj_vlan_del(rocker_port, vlan);
पूर्ण

अटल पूर्णांक
rocker_world_port_fdb_add(काष्ठा rocker_port *rocker_port,
			  काष्ठा चयनdev_notअगरier_fdb_info *info)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_obj_fdb_add)
		वापस -EOPNOTSUPP;

	वापस wops->port_obj_fdb_add(rocker_port, info->vid, info->addr);
पूर्ण

अटल पूर्णांक
rocker_world_port_fdb_del(काष्ठा rocker_port *rocker_port,
			  काष्ठा चयनdev_notअगरier_fdb_info *info)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_obj_fdb_del)
		वापस -EOPNOTSUPP;
	वापस wops->port_obj_fdb_del(rocker_port, info->vid, info->addr);
पूर्ण

अटल पूर्णांक rocker_world_port_master_linked(काष्ठा rocker_port *rocker_port,
					   काष्ठा net_device *master)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_master_linked)
		वापस -EOPNOTSUPP;
	वापस wops->port_master_linked(rocker_port, master);
पूर्ण

अटल पूर्णांक rocker_world_port_master_unlinked(काष्ठा rocker_port *rocker_port,
					     काष्ठा net_device *master)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_master_unlinked)
		वापस -EOPNOTSUPP;
	वापस wops->port_master_unlinked(rocker_port, master);
पूर्ण

अटल पूर्णांक rocker_world_port_neigh_update(काष्ठा rocker_port *rocker_port,
					  काष्ठा neighbour *n)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_neigh_update)
		वापस -EOPNOTSUPP;
	वापस wops->port_neigh_update(rocker_port, n);
पूर्ण

अटल पूर्णांक rocker_world_port_neigh_destroy(काष्ठा rocker_port *rocker_port,
					   काष्ठा neighbour *n)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_neigh_destroy)
		वापस -EOPNOTSUPP;
	वापस wops->port_neigh_destroy(rocker_port, n);
पूर्ण

अटल पूर्णांक rocker_world_port_ev_mac_vlan_seen(काष्ठा rocker_port *rocker_port,
					      स्थिर अचिन्हित अक्षर *addr,
					      __be16 vlan_id)
अणु
	काष्ठा rocker_world_ops *wops = rocker_port->rocker->wops;

	अगर (!wops->port_ev_mac_vlan_seen)
		वापस -EOPNOTSUPP;
	वापस wops->port_ev_mac_vlan_seen(rocker_port, addr, vlan_id);
पूर्ण

अटल पूर्णांक rocker_world_fib4_add(काष्ठा rocker *rocker,
				 स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा rocker_world_ops *wops = rocker->wops;

	अगर (!wops->fib4_add)
		वापस 0;
	वापस wops->fib4_add(rocker, fen_info);
पूर्ण

अटल पूर्णांक rocker_world_fib4_del(काष्ठा rocker *rocker,
				 स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा rocker_world_ops *wops = rocker->wops;

	अगर (!wops->fib4_del)
		वापस 0;
	वापस wops->fib4_del(rocker, fen_info);
पूर्ण

अटल व्योम rocker_world_fib4_पात(काष्ठा rocker *rocker)
अणु
	काष्ठा rocker_world_ops *wops = rocker->wops;

	अगर (wops->fib4_पात)
		wops->fib4_पात(rocker);
पूर्ण

/*****************
 * Net device ops
 *****************/

अटल पूर्णांक rocker_port_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	पूर्णांक err;

	err = rocker_port_dma_rings_init(rocker_port);
	अगर (err)
		वापस err;

	err = request_irq(rocker_msix_tx_vector(rocker_port),
			  rocker_tx_irq_handler, 0,
			  rocker_driver_name, rocker_port);
	अगर (err) अणु
		netdev_err(rocker_port->dev, "cannot assign tx irq\n");
		जाओ err_request_tx_irq;
	पूर्ण

	err = request_irq(rocker_msix_rx_vector(rocker_port),
			  rocker_rx_irq_handler, 0,
			  rocker_driver_name, rocker_port);
	अगर (err) अणु
		netdev_err(rocker_port->dev, "cannot assign rx irq\n");
		जाओ err_request_rx_irq;
	पूर्ण

	err = rocker_world_port_खोलो(rocker_port);
	अगर (err) अणु
		netdev_err(rocker_port->dev, "cannot open port in world\n");
		जाओ err_world_port_खोलो;
	पूर्ण

	napi_enable(&rocker_port->napi_tx);
	napi_enable(&rocker_port->napi_rx);
	अगर (!dev->proto_करोwn)
		rocker_port_set_enable(rocker_port, true);
	netअगर_start_queue(dev);
	वापस 0;

err_world_port_खोलो:
	मुक्त_irq(rocker_msix_rx_vector(rocker_port), rocker_port);
err_request_rx_irq:
	मुक्त_irq(rocker_msix_tx_vector(rocker_port), rocker_port);
err_request_tx_irq:
	rocker_port_dma_rings_fini(rocker_port);
	वापस err;
पूर्ण

अटल पूर्णांक rocker_port_stop(काष्ठा net_device *dev)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);

	netअगर_stop_queue(dev);
	rocker_port_set_enable(rocker_port, false);
	napi_disable(&rocker_port->napi_rx);
	napi_disable(&rocker_port->napi_tx);
	rocker_world_port_stop(rocker_port);
	मुक्त_irq(rocker_msix_rx_vector(rocker_port), rocker_port);
	मुक्त_irq(rocker_msix_tx_vector(rocker_port), rocker_port);
	rocker_port_dma_rings_fini(rocker_port);

	वापस 0;
पूर्ण

अटल व्योम rocker_tx_desc_frags_unmap(स्थिर काष्ठा rocker_port *rocker_port,
				       स्थिर काष्ठा rocker_desc_info *desc_info)
अणु
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	काष्ठा pci_dev *pdev = rocker->pdev;
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_TX_MAX + 1];
	काष्ठा rocker_tlv *attr;
	पूर्णांक rem;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_TX_MAX, desc_info);
	अगर (!attrs[ROCKER_TLV_TX_FRAGS])
		वापस;
	rocker_tlv_क्रम_each_nested(attr, attrs[ROCKER_TLV_TX_FRAGS], rem) अणु
		स्थिर काष्ठा rocker_tlv *frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_MAX + 1];
		dma_addr_t dma_handle;
		माप_प्रकार len;

		अगर (rocker_tlv_type(attr) != ROCKER_TLV_TX_FRAG)
			जारी;
		rocker_tlv_parse_nested(frag_attrs, ROCKER_TLV_TX_FRAG_ATTR_MAX,
					attr);
		अगर (!frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_ADDR] ||
		    !frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_LEN])
			जारी;
		dma_handle = rocker_tlv_get_u64(frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_ADDR]);
		len = rocker_tlv_get_u16(frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_LEN]);
		dma_unmap_single(&pdev->dev, dma_handle, len, DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल पूर्णांक rocker_tx_desc_frag_map_put(स्थिर काष्ठा rocker_port *rocker_port,
				       काष्ठा rocker_desc_info *desc_info,
				       अक्षर *buf, माप_प्रकार buf_len)
अणु
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	काष्ठा pci_dev *pdev = rocker->pdev;
	dma_addr_t dma_handle;
	काष्ठा rocker_tlv *frag;

	dma_handle = dma_map_single(&pdev->dev, buf, buf_len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(&pdev->dev, dma_handle))) अणु
		अगर (net_ratelimit())
			netdev_err(rocker_port->dev, "failed to dma map tx frag\n");
		वापस -EIO;
	पूर्ण
	frag = rocker_tlv_nest_start(desc_info, ROCKER_TLV_TX_FRAG);
	अगर (!frag)
		जाओ unmap_frag;
	अगर (rocker_tlv_put_u64(desc_info, ROCKER_TLV_TX_FRAG_ATTR_ADDR,
			       dma_handle))
		जाओ nest_cancel;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_TX_FRAG_ATTR_LEN,
			       buf_len))
		जाओ nest_cancel;
	rocker_tlv_nest_end(desc_info, frag);
	वापस 0;

nest_cancel:
	rocker_tlv_nest_cancel(desc_info, frag);
unmap_frag:
	dma_unmap_single(&pdev->dev, dma_handle, buf_len, DMA_TO_DEVICE);
	वापस -EMSGSIZE;
पूर्ण

अटल netdev_tx_t rocker_port_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	काष्ठा rocker *rocker = rocker_port->rocker;
	काष्ठा rocker_desc_info *desc_info;
	काष्ठा rocker_tlv *frags;
	पूर्णांक i;
	पूर्णांक err;

	desc_info = rocker_desc_head_get(&rocker_port->tx_ring);
	अगर (unlikely(!desc_info)) अणु
		अगर (net_ratelimit())
			netdev_err(dev, "tx ring full when queue awake\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	rocker_desc_cookie_ptr_set(desc_info, skb);

	frags = rocker_tlv_nest_start(desc_info, ROCKER_TLV_TX_FRAGS);
	अगर (!frags)
		जाओ out;
	err = rocker_tx_desc_frag_map_put(rocker_port, desc_info,
					  skb->data, skb_headlen(skb));
	अगर (err)
		जाओ nest_cancel;
	अगर (skb_shinfo(skb)->nr_frags > ROCKER_TX_FRAGS_MAX) अणु
		err = skb_linearize(skb);
		अगर (err)
			जाओ unmap_frags;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		err = rocker_tx_desc_frag_map_put(rocker_port, desc_info,
						  skb_frag_address(frag),
						  skb_frag_size(frag));
		अगर (err)
			जाओ unmap_frags;
	पूर्ण
	rocker_tlv_nest_end(desc_info, frags);

	rocker_desc_gen_clear(desc_info);
	rocker_desc_head_set(rocker, &rocker_port->tx_ring, desc_info);

	desc_info = rocker_desc_head_get(&rocker_port->tx_ring);
	अगर (!desc_info)
		netअगर_stop_queue(dev);

	वापस NETDEV_TX_OK;

unmap_frags:
	rocker_tx_desc_frags_unmap(rocker_port, desc_info);
nest_cancel:
	rocker_tlv_nest_cancel(desc_info, frags);
out:
	dev_kमुक्त_skb(skb);
	dev->stats.tx_dropped++;

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक rocker_port_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	err = rocker_cmd_set_port_settings_macaddr(rocker_port, addr->sa_data);
	अगर (err)
		वापस err;
	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	वापस 0;
पूर्ण

अटल पूर्णांक rocker_port_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	पूर्णांक running = netअगर_running(dev);
	पूर्णांक err;

	अगर (running)
		rocker_port_stop(dev);

	netdev_info(dev, "MTU change from %d to %d\n", dev->mtu, new_mtu);
	dev->mtu = new_mtu;

	err = rocker_cmd_set_port_settings_mtu(rocker_port, new_mtu);
	अगर (err)
		वापस err;

	अगर (running)
		err = rocker_port_खोलो(dev);

	वापस err;
पूर्ण

अटल पूर्णांक rocker_port_get_phys_port_name(काष्ठा net_device *dev,
					  अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	काष्ठा port_name name = अणु .buf = buf, .len = len पूर्ण;
	पूर्णांक err;

	err = rocker_cmd_exec(rocker_port, false,
			      rocker_cmd_get_port_settings_prep, शून्य,
			      rocker_cmd_get_port_settings_phys_name_proc,
			      &name);

	वापस err ? -EOPNOTSUPP : 0;
पूर्ण

अटल पूर्णांक rocker_port_change_proto_करोwn(काष्ठा net_device *dev,
					 bool proto_करोwn)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);

	अगर (rocker_port->dev->flags & IFF_UP)
		rocker_port_set_enable(rocker_port, !proto_करोwn);
	rocker_port->dev->proto_करोwn = proto_करोwn;
	वापस 0;
पूर्ण

अटल व्योम rocker_port_neigh_destroy(काष्ठा net_device *dev,
				      काष्ठा neighbour *n)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(n->dev);
	पूर्णांक err;

	err = rocker_world_port_neigh_destroy(rocker_port, n);
	अगर (err)
		netdev_warn(rocker_port->dev, "failed to handle neigh destroy (err %d)\n",
			    err);
पूर्ण

अटल पूर्णांक rocker_port_get_port_parent_id(काष्ठा net_device *dev,
					  काष्ठा netdev_phys_item_id *ppid)
अणु
	स्थिर काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;

	ppid->id_len = माप(rocker->hw.id);
	स_नकल(&ppid->id, &rocker->hw.id, ppid->id_len);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops rocker_port_netdev_ops = अणु
	.nकरो_खोलो			= rocker_port_खोलो,
	.nकरो_stop			= rocker_port_stop,
	.nकरो_start_xmit			= rocker_port_xmit,
	.nकरो_set_mac_address		= rocker_port_set_mac_address,
	.nकरो_change_mtu			= rocker_port_change_mtu,
	.nकरो_get_phys_port_name		= rocker_port_get_phys_port_name,
	.nकरो_change_proto_करोwn		= rocker_port_change_proto_करोwn,
	.nकरो_neigh_destroy		= rocker_port_neigh_destroy,
	.nकरो_get_port_parent_id		= rocker_port_get_port_parent_id,
पूर्ण;

/********************
 * swdev पूर्णांकerface
 ********************/

अटल पूर्णांक rocker_port_attr_set(काष्ठा net_device *dev,
				स्थिर काष्ठा चयनdev_attr *attr)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	पूर्णांक err = 0;

	चयन (attr->id) अणु
	हाल SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		err = rocker_world_port_attr_stp_state_set(rocker_port,
							   attr->u.stp_state);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		err = rocker_world_port_attr_pre_bridge_flags_set(rocker_port,
								  attr->u.brport_flags);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		err = rocker_world_port_attr_bridge_flags_set(rocker_port,
							      attr->u.brport_flags);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
		err = rocker_world_port_attr_bridge_ageing_समय_set(rocker_port,
								    attr->u.ageing_समय);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक rocker_port_obj_add(काष्ठा net_device *dev,
			       स्थिर काष्ठा चयनdev_obj *obj)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	पूर्णांक err = 0;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = rocker_world_port_obj_vlan_add(rocker_port,
						     SWITCHDEV_OBJ_PORT_VLAN(obj));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक rocker_port_obj_del(काष्ठा net_device *dev,
			       स्थिर काष्ठा चयनdev_obj *obj)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);
	पूर्णांक err = 0;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = rocker_world_port_obj_vlan_del(rocker_port,
						     SWITCHDEV_OBJ_PORT_VLAN(obj));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

काष्ठा rocker_fib_event_work अणु
	काष्ठा work_काष्ठा work;
	जोड़ अणु
		काष्ठा fib_entry_notअगरier_info fen_info;
		काष्ठा fib_rule_notअगरier_info fr_info;
	पूर्ण;
	काष्ठा rocker *rocker;
	अचिन्हित दीर्घ event;
पूर्ण;

अटल व्योम rocker_router_fib_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rocker_fib_event_work *fib_work =
		container_of(work, काष्ठा rocker_fib_event_work, work);
	काष्ठा rocker *rocker = fib_work->rocker;
	काष्ठा fib_rule *rule;
	पूर्णांक err;

	/* Protect पूर्णांकernal काष्ठाures from changes */
	rtnl_lock();
	चयन (fib_work->event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
		err = rocker_world_fib4_add(rocker, &fib_work->fen_info);
		अगर (err)
			rocker_world_fib4_पात(rocker);
		fib_info_put(fib_work->fen_info.fi);
		अवरोध;
	हाल FIB_EVENT_ENTRY_DEL:
		rocker_world_fib4_del(rocker, &fib_work->fen_info);
		fib_info_put(fib_work->fen_info.fi);
		अवरोध;
	हाल FIB_EVENT_RULE_ADD:
	हाल FIB_EVENT_RULE_DEL:
		rule = fib_work->fr_info.rule;
		अगर (!fib4_rule_शेष(rule))
			rocker_world_fib4_पात(rocker);
		fib_rule_put(rule);
		अवरोध;
	पूर्ण
	rtnl_unlock();
	kमुक्त(fib_work);
पूर्ण

/* Called with rcu_पढ़ो_lock() */
अटल पूर्णांक rocker_router_fib_event(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा rocker *rocker = container_of(nb, काष्ठा rocker, fib_nb);
	काष्ठा rocker_fib_event_work *fib_work;
	काष्ठा fib_notअगरier_info *info = ptr;

	अगर (info->family != AF_INET)
		वापस NOTIFY_DONE;

	fib_work = kzalloc(माप(*fib_work), GFP_ATOMIC);
	अगर (WARN_ON(!fib_work))
		वापस NOTIFY_BAD;

	INIT_WORK(&fib_work->work, rocker_router_fib_event_work);
	fib_work->rocker = rocker;
	fib_work->event = event;

	चयन (event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_DEL:
		अगर (info->family == AF_INET) अणु
			काष्ठा fib_entry_notअगरier_info *fen_info = ptr;

			अगर (fen_info->fi->fib_nh_is_v6) अणु
				NL_SET_ERR_MSG_MOD(info->extack, "IPv6 gateway with IPv4 route is not supported");
				kमुक्त(fib_work);
				वापस notअगरier_from_त्रुटि_सं(-EINVAL);
			पूर्ण
			अगर (fen_info->fi->nh) अणु
				NL_SET_ERR_MSG_MOD(info->extack, "IPv4 route with nexthop objects is not supported");
				kमुक्त(fib_work);
				वापस notअगरier_from_त्रुटि_सं(-EINVAL);
			पूर्ण
		पूर्ण

		स_नकल(&fib_work->fen_info, ptr, माप(fib_work->fen_info));
		/* Take referece on fib_info to prevent it from being
		 * मुक्तd जबतक work is queued. Release it afterwards.
		 */
		fib_info_hold(fib_work->fen_info.fi);
		अवरोध;
	हाल FIB_EVENT_RULE_ADD:
	हाल FIB_EVENT_RULE_DEL:
		स_नकल(&fib_work->fr_info, ptr, माप(fib_work->fr_info));
		fib_rule_get(fib_work->fr_info.rule);
		अवरोध;
	पूर्ण

	queue_work(rocker->rocker_owq, &fib_work->work);

	वापस NOTIFY_DONE;
पूर्ण

/********************
 * ethtool पूर्णांकerface
 ********************/

अटल पूर्णांक
rocker_port_get_link_ksettings(काष्ठा net_device *dev,
			       काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);

	वापस rocker_cmd_get_port_settings_ethtool(rocker_port, ecmd);
पूर्ण

अटल पूर्णांक
rocker_port_set_link_ksettings(काष्ठा net_device *dev,
			       स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);

	वापस rocker_cmd_set_port_settings_ethtool(rocker_port, ecmd);
पूर्ण

अटल व्योम rocker_port_get_drvinfo(काष्ठा net_device *dev,
				    काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, rocker_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->version, UTS_RELEASE, माप(drvinfo->version));
पूर्ण

अटल काष्ठा rocker_port_stats अणु
	अक्षर str[ETH_GSTRING_LEN];
	पूर्णांक type;
पूर्ण rocker_port_stats[] = अणु
	अणु "rx_packets", ROCKER_TLV_CMD_PORT_STATS_RX_PKTS,    पूर्ण,
	अणु "rx_bytes",   ROCKER_TLV_CMD_PORT_STATS_RX_BYTES,   पूर्ण,
	अणु "rx_dropped", ROCKER_TLV_CMD_PORT_STATS_RX_DROPPED, पूर्ण,
	अणु "rx_errors",  ROCKER_TLV_CMD_PORT_STATS_RX_ERRORS,  पूर्ण,

	अणु "tx_packets", ROCKER_TLV_CMD_PORT_STATS_TX_PKTS,    पूर्ण,
	अणु "tx_bytes",   ROCKER_TLV_CMD_PORT_STATS_TX_BYTES,   पूर्ण,
	अणु "tx_dropped", ROCKER_TLV_CMD_PORT_STATS_TX_DROPPED, पूर्ण,
	अणु "tx_errors",  ROCKER_TLV_CMD_PORT_STATS_TX_ERRORS,  पूर्ण,
पूर्ण;

#घोषणा ROCKER_PORT_STATS_LEN  ARRAY_SIZE(rocker_port_stats)

अटल व्योम rocker_port_get_strings(काष्ठा net_device *netdev, u32 stringset,
				    u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(rocker_port_stats); i++) अणु
			स_नकल(p, rocker_port_stats[i].str, ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
rocker_cmd_get_port_stats_prep(स्थिर काष्ठा rocker_port *rocker_port,
			       काष्ठा rocker_desc_info *desc_info,
			       व्योम *priv)
अणु
	काष्ठा rocker_tlv *cmd_stats;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE,
			       ROCKER_TLV_CMD_TYPE_GET_PORT_STATS))
		वापस -EMSGSIZE;

	cmd_stats = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_stats)
		वापस -EMSGSIZE;

	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_STATS_PPORT,
			       rocker_port->pport))
		वापस -EMSGSIZE;

	rocker_tlv_nest_end(desc_info, cmd_stats);

	वापस 0;
पूर्ण

अटल पूर्णांक
rocker_cmd_get_port_stats_ethtool_proc(स्थिर काष्ठा rocker_port *rocker_port,
				       स्थिर काष्ठा rocker_desc_info *desc_info,
				       व्योम *priv)
अणु
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	स्थिर काष्ठा rocker_tlv *stats_attrs[ROCKER_TLV_CMD_PORT_STATS_MAX + 1];
	स्थिर काष्ठा rocker_tlv *pattr;
	u32 pport;
	u64 *data = priv;
	पूर्णांक i;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);

	अगर (!attrs[ROCKER_TLV_CMD_INFO])
		वापस -EIO;

	rocker_tlv_parse_nested(stats_attrs, ROCKER_TLV_CMD_PORT_STATS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);

	अगर (!stats_attrs[ROCKER_TLV_CMD_PORT_STATS_PPORT])
		वापस -EIO;

	pport = rocker_tlv_get_u32(stats_attrs[ROCKER_TLV_CMD_PORT_STATS_PPORT]);
	अगर (pport != rocker_port->pport)
		वापस -EIO;

	क्रम (i = 0; i < ARRAY_SIZE(rocker_port_stats); i++) अणु
		pattr = stats_attrs[rocker_port_stats[i].type];
		अगर (!pattr)
			जारी;

		data[i] = rocker_tlv_get_u64(pattr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rocker_cmd_get_port_stats_ethtool(काष्ठा rocker_port *rocker_port,
					     व्योम *priv)
अणु
	वापस rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_get_port_stats_prep, शून्य,
			       rocker_cmd_get_port_stats_ethtool_proc,
			       priv);
पूर्ण

अटल व्योम rocker_port_get_stats(काष्ठा net_device *dev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा rocker_port *rocker_port = netdev_priv(dev);

	अगर (rocker_cmd_get_port_stats_ethtool(rocker_port, data) != 0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(rocker_port_stats); ++i)
			data[i] = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक rocker_port_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ROCKER_PORT_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops rocker_port_ethtool_ops = अणु
	.get_drvinfo		= rocker_port_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_strings		= rocker_port_get_strings,
	.get_ethtool_stats	= rocker_port_get_stats,
	.get_sset_count		= rocker_port_get_sset_count,
	.get_link_ksettings	= rocker_port_get_link_ksettings,
	.set_link_ksettings	= rocker_port_set_link_ksettings,
पूर्ण;

/*****************
 * NAPI पूर्णांकerface
 *****************/

अटल काष्ठा rocker_port *rocker_port_napi_tx_get(काष्ठा napi_काष्ठा *napi)
अणु
	वापस container_of(napi, काष्ठा rocker_port, napi_tx);
पूर्ण

अटल पूर्णांक rocker_port_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा rocker_port *rocker_port = rocker_port_napi_tx_get(napi);
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	स्थिर काष्ठा rocker_desc_info *desc_info;
	u32 credits = 0;
	पूर्णांक err;

	/* Cleanup tx descriptors */
	जबतक ((desc_info = rocker_desc_tail_get(&rocker_port->tx_ring))) अणु
		काष्ठा sk_buff *skb;

		err = rocker_desc_err(desc_info);
		अगर (err && net_ratelimit())
			netdev_err(rocker_port->dev, "tx desc received with err %d\n",
				   err);
		rocker_tx_desc_frags_unmap(rocker_port, desc_info);

		skb = rocker_desc_cookie_ptr_get(desc_info);
		अगर (err == 0) अणु
			rocker_port->dev->stats.tx_packets++;
			rocker_port->dev->stats.tx_bytes += skb->len;
		पूर्ण अन्यथा अणु
			rocker_port->dev->stats.tx_errors++;
		पूर्ण

		dev_kमुक्त_skb_any(skb);
		credits++;
	पूर्ण

	अगर (credits && netअगर_queue_stopped(rocker_port->dev))
		netअगर_wake_queue(rocker_port->dev);

	napi_complete(napi);
	rocker_dma_ring_credits_set(rocker, &rocker_port->tx_ring, credits);

	वापस 0;
पूर्ण

अटल पूर्णांक rocker_port_rx_proc(स्थिर काष्ठा rocker *rocker,
			       स्थिर काष्ठा rocker_port *rocker_port,
			       काष्ठा rocker_desc_info *desc_info)
अणु
	स्थिर काष्ठा rocker_tlv *attrs[ROCKER_TLV_RX_MAX + 1];
	काष्ठा sk_buff *skb = rocker_desc_cookie_ptr_get(desc_info);
	माप_प्रकार rx_len;
	u16 rx_flags = 0;

	अगर (!skb)
		वापस -ENOENT;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_RX_MAX, desc_info);
	अगर (!attrs[ROCKER_TLV_RX_FRAG_LEN])
		वापस -EINVAL;
	अगर (attrs[ROCKER_TLV_RX_FLAGS])
		rx_flags = rocker_tlv_get_u16(attrs[ROCKER_TLV_RX_FLAGS]);

	rocker_dma_rx_ring_skb_unmap(rocker, attrs);

	rx_len = rocker_tlv_get_u16(attrs[ROCKER_TLV_RX_FRAG_LEN]);
	skb_put(skb, rx_len);
	skb->protocol = eth_type_trans(skb, rocker_port->dev);

	अगर (rx_flags & ROCKER_RX_FLAGS_FWD_OFFLOAD)
		skb->offload_fwd_mark = 1;

	rocker_port->dev->stats.rx_packets++;
	rocker_port->dev->stats.rx_bytes += skb->len;

	netअगर_receive_skb(skb);

	वापस rocker_dma_rx_ring_skb_alloc(rocker_port, desc_info);
पूर्ण

अटल काष्ठा rocker_port *rocker_port_napi_rx_get(काष्ठा napi_काष्ठा *napi)
अणु
	वापस container_of(napi, काष्ठा rocker_port, napi_rx);
पूर्ण

अटल पूर्णांक rocker_port_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा rocker_port *rocker_port = rocker_port_napi_rx_get(napi);
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	काष्ठा rocker_desc_info *desc_info;
	u32 credits = 0;
	पूर्णांक err;

	/* Process rx descriptors */
	जबतक (credits < budget &&
	       (desc_info = rocker_desc_tail_get(&rocker_port->rx_ring))) अणु
		err = rocker_desc_err(desc_info);
		अगर (err) अणु
			अगर (net_ratelimit())
				netdev_err(rocker_port->dev, "rx desc received with err %d\n",
					   err);
		पूर्ण अन्यथा अणु
			err = rocker_port_rx_proc(rocker, rocker_port,
						  desc_info);
			अगर (err && net_ratelimit())
				netdev_err(rocker_port->dev, "rx processing failed with err %d\n",
					   err);
		पूर्ण
		अगर (err)
			rocker_port->dev->stats.rx_errors++;

		rocker_desc_gen_clear(desc_info);
		rocker_desc_head_set(rocker, &rocker_port->rx_ring, desc_info);
		credits++;
	पूर्ण

	अगर (credits < budget)
		napi_complete_करोne(napi, credits);

	rocker_dma_ring_credits_set(rocker, &rocker_port->rx_ring, credits);

	वापस credits;
पूर्ण

/*****************
 * PCI driver ops
 *****************/

अटल व्योम rocker_carrier_init(स्थिर काष्ठा rocker_port *rocker_port)
अणु
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	u64 link_status = rocker_पढ़ो64(rocker, PORT_PHYS_LINK_STATUS);
	bool link_up;

	link_up = link_status & (1 << rocker_port->pport);
	अगर (link_up)
		netअगर_carrier_on(rocker_port->dev);
	अन्यथा
		netअगर_carrier_off(rocker_port->dev);
पूर्ण

अटल व्योम rocker_हटाओ_ports(काष्ठा rocker *rocker)
अणु
	काष्ठा rocker_port *rocker_port;
	पूर्णांक i;

	क्रम (i = 0; i < rocker->port_count; i++) अणु
		rocker_port = rocker->ports[i];
		अगर (!rocker_port)
			जारी;
		rocker_world_port_fini(rocker_port);
		unरेजिस्टर_netdev(rocker_port->dev);
		rocker_world_port_post_fini(rocker_port);
		मुक्त_netdev(rocker_port->dev);
	पूर्ण
	rocker_world_fini(rocker);
	kमुक्त(rocker->ports);
पूर्ण

अटल व्योम rocker_port_dev_addr_init(काष्ठा rocker_port *rocker_port)
अणु
	स्थिर काष्ठा rocker *rocker = rocker_port->rocker;
	स्थिर काष्ठा pci_dev *pdev = rocker->pdev;
	पूर्णांक err;

	err = rocker_cmd_get_port_settings_macaddr(rocker_port,
						   rocker_port->dev->dev_addr);
	अगर (err) अणु
		dev_warn(&pdev->dev, "failed to get mac address, using random\n");
		eth_hw_addr_अक्रमom(rocker_port->dev);
	पूर्ण
पूर्ण

#घोषणा ROCKER_PORT_MIN_MTU	ETH_MIN_MTU
#घोषणा ROCKER_PORT_MAX_MTU	9000
अटल पूर्णांक rocker_probe_port(काष्ठा rocker *rocker, अचिन्हित पूर्णांक port_number)
अणु
	काष्ठा pci_dev *pdev = rocker->pdev;
	काष्ठा rocker_port *rocker_port;
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_etherdev(माप(काष्ठा rocker_port));
	अगर (!dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);
	rocker_port = netdev_priv(dev);
	rocker_port->dev = dev;
	rocker_port->rocker = rocker;
	rocker_port->port_number = port_number;
	rocker_port->pport = port_number + 1;

	err = rocker_world_check_init(rocker_port);
	अगर (err) अणु
		dev_err(&pdev->dev, "world init failed\n");
		जाओ err_world_check_init;
	पूर्ण

	rocker_port_dev_addr_init(rocker_port);
	dev->netdev_ops = &rocker_port_netdev_ops;
	dev->ethtool_ops = &rocker_port_ethtool_ops;
	netअगर_tx_napi_add(dev, &rocker_port->napi_tx, rocker_port_poll_tx,
			  NAPI_POLL_WEIGHT);
	netअगर_napi_add(dev, &rocker_port->napi_rx, rocker_port_poll_rx,
		       NAPI_POLL_WEIGHT);
	rocker_carrier_init(rocker_port);

	dev->features |= NETIF_F_NETNS_LOCAL | NETIF_F_SG;

	/* MTU range: 68 - 9000 */
	dev->min_mtu = ROCKER_PORT_MIN_MTU;
	dev->max_mtu = ROCKER_PORT_MAX_MTU;

	err = rocker_world_port_pre_init(rocker_port);
	अगर (err) अणु
		dev_err(&pdev->dev, "port world pre-init failed\n");
		जाओ err_world_port_pre_init;
	पूर्ण
	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "register_netdev failed\n");
		जाओ err_रेजिस्टर_netdev;
	पूर्ण
	rocker->ports[port_number] = rocker_port;

	err = rocker_world_port_init(rocker_port);
	अगर (err) अणु
		dev_err(&pdev->dev, "port world init failed\n");
		जाओ err_world_port_init;
	पूर्ण

	वापस 0;

err_world_port_init:
	rocker->ports[port_number] = शून्य;
	unरेजिस्टर_netdev(dev);
err_रेजिस्टर_netdev:
	rocker_world_port_post_fini(rocker_port);
err_world_port_pre_init:
err_world_check_init:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक rocker_probe_ports(काष्ठा rocker *rocker)
अणु
	पूर्णांक i;
	माप_प्रकार alloc_size;
	पूर्णांक err;

	alloc_size = माप(काष्ठा rocker_port *) * rocker->port_count;
	rocker->ports = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!rocker->ports)
		वापस -ENOMEM;
	क्रम (i = 0; i < rocker->port_count; i++) अणु
		err = rocker_probe_port(rocker, i);
		अगर (err)
			जाओ हटाओ_ports;
	पूर्ण
	वापस 0;

हटाओ_ports:
	rocker_हटाओ_ports(rocker);
	वापस err;
पूर्ण

अटल पूर्णांक rocker_msix_init(काष्ठा rocker *rocker)
अणु
	काष्ठा pci_dev *pdev = rocker->pdev;
	पूर्णांक msix_entries;
	पूर्णांक i;
	पूर्णांक err;

	msix_entries = pci_msix_vec_count(pdev);
	अगर (msix_entries < 0)
		वापस msix_entries;

	अगर (msix_entries != ROCKER_MSIX_VEC_COUNT(rocker->port_count))
		वापस -EINVAL;

	rocker->msix_entries = kदो_स्मृति_array(msix_entries,
					     माप(काष्ठा msix_entry),
					     GFP_KERNEL);
	अगर (!rocker->msix_entries)
		वापस -ENOMEM;

	क्रम (i = 0; i < msix_entries; i++)
		rocker->msix_entries[i].entry = i;

	err = pci_enable_msix_exact(pdev, rocker->msix_entries, msix_entries);
	अगर (err < 0)
		जाओ err_enable_msix;

	वापस 0;

err_enable_msix:
	kमुक्त(rocker->msix_entries);
	वापस err;
पूर्ण

अटल व्योम rocker_msix_fini(स्थिर काष्ठा rocker *rocker)
अणु
	pci_disable_msix(rocker->pdev);
	kमुक्त(rocker->msix_entries);
पूर्ण

अटल bool rocker_port_dev_check(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->netdev_ops == &rocker_port_netdev_ops;
पूर्ण

अटल पूर्णांक
rocker_चयनdev_port_attr_set_event(काष्ठा net_device *netdev,
		काष्ठा चयनdev_notअगरier_port_attr_info *port_attr_info)
अणु
	पूर्णांक err;

	err = rocker_port_attr_set(netdev, port_attr_info->attr);

	port_attr_info->handled = true;
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

काष्ठा rocker_चयनdev_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा चयनdev_notअगरier_fdb_info fdb_info;
	काष्ठा rocker_port *rocker_port;
	अचिन्हित दीर्घ event;
पूर्ण;

अटल व्योम
rocker_fdb_offload_notअगरy(काष्ठा rocker_port *rocker_port,
			  काष्ठा चयनdev_notअगरier_fdb_info *recv_info)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info;

	info.addr = recv_info->addr;
	info.vid = recv_info->vid;
	info.offloaded = true;
	call_चयनdev_notअगरiers(SWITCHDEV_FDB_OFFLOADED,
				 rocker_port->dev, &info.info, शून्य);
पूर्ण

अटल व्योम rocker_चयनdev_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rocker_चयनdev_event_work *चयनdev_work =
		container_of(work, काष्ठा rocker_चयनdev_event_work, work);
	काष्ठा rocker_port *rocker_port = चयनdev_work->rocker_port;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	पूर्णांक err;

	rtnl_lock();
	चयन (चयनdev_work->event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb_info = &चयनdev_work->fdb_info;
		अगर (!fdb_info->added_by_user || fdb_info->is_local)
			अवरोध;
		err = rocker_world_port_fdb_add(rocker_port, fdb_info);
		अगर (err) अणु
			netdev_dbg(rocker_port->dev, "fdb add failed err=%d\n", err);
			अवरोध;
		पूर्ण
		rocker_fdb_offload_notअगरy(rocker_port, fdb_info);
		अवरोध;
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		fdb_info = &चयनdev_work->fdb_info;
		अगर (!fdb_info->added_by_user || fdb_info->is_local)
			अवरोध;
		err = rocker_world_port_fdb_del(rocker_port, fdb_info);
		अगर (err)
			netdev_dbg(rocker_port->dev, "fdb add failed err=%d\n", err);
		अवरोध;
	पूर्ण
	rtnl_unlock();

	kमुक्त(चयनdev_work->fdb_info.addr);
	kमुक्त(चयनdev_work);
	dev_put(rocker_port->dev);
पूर्ण

/* called under rcu_पढ़ो_lock() */
अटल पूर्णांक rocker_चयनdev_event(काष्ठा notअगरier_block *unused,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	काष्ठा rocker_चयनdev_event_work *चयनdev_work;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info = ptr;
	काष्ठा rocker_port *rocker_port;

	अगर (!rocker_port_dev_check(dev))
		वापस NOTIFY_DONE;

	अगर (event == SWITCHDEV_PORT_ATTR_SET)
		वापस rocker_चयनdev_port_attr_set_event(dev, ptr);

	rocker_port = netdev_priv(dev);
	चयनdev_work = kzalloc(माप(*चयनdev_work), GFP_ATOMIC);
	अगर (WARN_ON(!चयनdev_work))
		वापस NOTIFY_BAD;

	INIT_WORK(&चयनdev_work->work, rocker_चयनdev_event_work);
	चयनdev_work->rocker_port = rocker_port;
	चयनdev_work->event = event;

	चयन (event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		स_नकल(&चयनdev_work->fdb_info, ptr,
		       माप(चयनdev_work->fdb_info));
		चयनdev_work->fdb_info.addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
		अगर (unlikely(!चयनdev_work->fdb_info.addr)) अणु
			kमुक्त(चयनdev_work);
			वापस NOTIFY_BAD;
		पूर्ण

		ether_addr_copy((u8 *)चयनdev_work->fdb_info.addr,
				fdb_info->addr);
		/* Take a reference on the rocker device */
		dev_hold(dev);
		अवरोध;
	शेष:
		kमुक्त(चयनdev_work);
		वापस NOTIFY_DONE;
	पूर्ण

	queue_work(rocker_port->rocker->rocker_owq,
		   &चयनdev_work->work);
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक
rocker_चयनdev_port_obj_event(अचिन्हित दीर्घ event, काष्ठा net_device *netdev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
		err = rocker_port_obj_add(netdev, port_obj_info->obj);
		अवरोध;
	हाल SWITCHDEV_PORT_OBJ_DEL:
		err = rocker_port_obj_del(netdev, port_obj_info->obj);
		अवरोध;
	पूर्ण

	port_obj_info->handled = true;
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक rocker_चयनdev_blocking_event(काष्ठा notअगरier_block *unused,
					   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);

	अगर (!rocker_port_dev_check(dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
	हाल SWITCHDEV_PORT_OBJ_DEL:
		वापस rocker_चयनdev_port_obj_event(event, dev, ptr);
	हाल SWITCHDEV_PORT_ATTR_SET:
		वापस rocker_चयनdev_port_attr_set_event(dev, ptr);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rocker_चयनdev_notअगरier = अणु
	.notअगरier_call = rocker_चयनdev_event,
पूर्ण;

अटल काष्ठा notअगरier_block rocker_चयनdev_blocking_notअगरier = अणु
	.notअगरier_call = rocker_चयनdev_blocking_event,
पूर्ण;

अटल पूर्णांक rocker_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा notअगरier_block *nb;
	काष्ठा rocker *rocker;
	पूर्णांक err;

	rocker = kzalloc(माप(*rocker), GFP_KERNEL);
	अगर (!rocker)
		वापस -ENOMEM;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_enable_device failed\n");
		जाओ err_pci_enable_device;
	पूर्ण

	err = pci_request_regions(pdev, rocker_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_request_regions failed\n");
		जाओ err_pci_request_regions;
	पूर्ण

	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	अगर (!err) अणु
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64));
		अगर (err) अणु
			dev_err(&pdev->dev, "dma_set_coherent_mask failed\n");
			जाओ err_pci_set_dma_mask;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "dma_set_mask failed\n");
			जाओ err_pci_set_dma_mask;
		पूर्ण
	पूर्ण

	अगर (pci_resource_len(pdev, 0) < ROCKER_PCI_BAR0_SIZE) अणु
		dev_err(&pdev->dev, "invalid PCI region size\n");
		err = -EINVAL;
		जाओ err_pci_resource_len_check;
	पूर्ण

	rocker->hw_addr = ioremap(pci_resource_start(pdev, 0),
				  pci_resource_len(pdev, 0));
	अगर (!rocker->hw_addr) अणु
		dev_err(&pdev->dev, "ioremap failed\n");
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण
	pci_set_master(pdev);

	rocker->pdev = pdev;
	pci_set_drvdata(pdev, rocker);

	rocker->port_count = rocker_पढ़ो32(rocker, PORT_PHYS_COUNT);

	err = rocker_msix_init(rocker);
	अगर (err) अणु
		dev_err(&pdev->dev, "MSI-X init failed\n");
		जाओ err_msix_init;
	पूर्ण

	err = rocker_basic_hw_test(rocker);
	अगर (err) अणु
		dev_err(&pdev->dev, "basic hw test failed\n");
		जाओ err_basic_hw_test;
	पूर्ण

	rocker_ग_लिखो32(rocker, CONTROL, ROCKER_CONTROL_RESET);

	err = rocker_dma_rings_init(rocker);
	अगर (err)
		जाओ err_dma_rings_init;

	err = request_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_CMD),
			  rocker_cmd_irq_handler, 0,
			  rocker_driver_name, rocker);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot assign cmd irq\n");
		जाओ err_request_cmd_irq;
	पूर्ण

	err = request_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_EVENT),
			  rocker_event_irq_handler, 0,
			  rocker_driver_name, rocker);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot assign event irq\n");
		जाओ err_request_event_irq;
	पूर्ण

	rocker->rocker_owq = alloc_ordered_workqueue(rocker_driver_name,
						     WQ_MEM_RECLAIM);
	अगर (!rocker->rocker_owq) अणु
		err = -ENOMEM;
		जाओ err_alloc_ordered_workqueue;
	पूर्ण

	err = rocker_probe_ports(rocker);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to probe ports\n");
		जाओ err_probe_ports;
	पूर्ण

	/* Only FIBs poपूर्णांकing to our own netdevs are programmed पूर्णांकo
	 * the device, so no need to pass a callback.
	 */
	rocker->fib_nb.notअगरier_call = rocker_router_fib_event;
	err = रेजिस्टर_fib_notअगरier(&init_net, &rocker->fib_nb, शून्य, शून्य);
	अगर (err)
		जाओ err_रेजिस्टर_fib_notअगरier;

	err = रेजिस्टर_चयनdev_notअगरier(&rocker_चयनdev_notअगरier);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register switchdev notifier\n");
		जाओ err_रेजिस्टर_चयनdev_notअगरier;
	पूर्ण

	nb = &rocker_चयनdev_blocking_notअगरier;
	err = रेजिस्टर_चयनdev_blocking_notअगरier(nb);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register switchdev blocking notifier\n");
		जाओ err_रेजिस्टर_चयनdev_blocking_notअगरier;
	पूर्ण

	rocker->hw.id = rocker_पढ़ो64(rocker, SWITCH_ID);

	dev_info(&pdev->dev, "Rocker switch with id %*phN\n",
		 (पूर्णांक)माप(rocker->hw.id), &rocker->hw.id);

	वापस 0;

err_रेजिस्टर_चयनdev_blocking_notअगरier:
	unरेजिस्टर_चयनdev_notअगरier(&rocker_चयनdev_notअगरier);
err_रेजिस्टर_चयनdev_notअगरier:
	unरेजिस्टर_fib_notअगरier(&init_net, &rocker->fib_nb);
err_रेजिस्टर_fib_notअगरier:
	rocker_हटाओ_ports(rocker);
err_probe_ports:
	destroy_workqueue(rocker->rocker_owq);
err_alloc_ordered_workqueue:
	मुक्त_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_EVENT), rocker);
err_request_event_irq:
	मुक्त_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_CMD), rocker);
err_request_cmd_irq:
	rocker_dma_rings_fini(rocker);
err_dma_rings_init:
err_basic_hw_test:
	rocker_msix_fini(rocker);
err_msix_init:
	iounmap(rocker->hw_addr);
err_ioremap:
err_pci_resource_len_check:
err_pci_set_dma_mask:
	pci_release_regions(pdev);
err_pci_request_regions:
	pci_disable_device(pdev);
err_pci_enable_device:
	kमुक्त(rocker);
	वापस err;
पूर्ण

अटल व्योम rocker_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा rocker *rocker = pci_get_drvdata(pdev);
	काष्ठा notअगरier_block *nb;

	nb = &rocker_चयनdev_blocking_notअगरier;
	unरेजिस्टर_चयनdev_blocking_notअगरier(nb);

	unरेजिस्टर_चयनdev_notअगरier(&rocker_चयनdev_notअगरier);
	unरेजिस्टर_fib_notअगरier(&init_net, &rocker->fib_nb);
	rocker_हटाओ_ports(rocker);
	rocker_ग_लिखो32(rocker, CONTROL, ROCKER_CONTROL_RESET);
	destroy_workqueue(rocker->rocker_owq);
	मुक्त_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_EVENT), rocker);
	मुक्त_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_CMD), rocker);
	rocker_dma_rings_fini(rocker);
	rocker_msix_fini(rocker);
	iounmap(rocker->hw_addr);
	pci_release_regions(rocker->pdev);
	pci_disable_device(rocker->pdev);
	kमुक्त(rocker);
पूर्ण

अटल काष्ठा pci_driver rocker_pci_driver = अणु
	.name		= rocker_driver_name,
	.id_table	= rocker_pci_id_table,
	.probe		= rocker_probe,
	.हटाओ		= rocker_हटाओ,
पूर्ण;

/************************************
 * Net device notअगरier event handler
 ************************************/

अटल bool rocker_port_dev_check_under(स्थिर काष्ठा net_device *dev,
					काष्ठा rocker *rocker)
अणु
	काष्ठा rocker_port *rocker_port;

	अगर (!rocker_port_dev_check(dev))
		वापस false;

	rocker_port = netdev_priv(dev);
	अगर (rocker_port->rocker != rocker)
		वापस false;

	वापस true;
पूर्ण

काष्ठा rocker_walk_data अणु
	काष्ठा rocker *rocker;
	काष्ठा rocker_port *port;
पूर्ण;

अटल पूर्णांक rocker_lower_dev_walk(काष्ठा net_device *lower_dev,
				 काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा rocker_walk_data *data = (काष्ठा rocker_walk_data *)priv->data;
	पूर्णांक ret = 0;

	अगर (rocker_port_dev_check_under(lower_dev, data->rocker)) अणु
		data->port = netdev_priv(lower_dev);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा rocker_port *rocker_port_dev_lower_find(काष्ठा net_device *dev,
					       काष्ठा rocker *rocker)
अणु
	काष्ठा netdev_nested_priv priv;
	काष्ठा rocker_walk_data data;

	अगर (rocker_port_dev_check_under(dev, rocker))
		वापस netdev_priv(dev);

	data.rocker = rocker;
	data.port = शून्य;
	priv.data = (व्योम *)&data;
	netdev_walk_all_lower_dev(dev, rocker_lower_dev_walk, &priv);

	वापस data.port;
पूर्ण

अटल पूर्णांक rocker_netdevice_event(काष्ठा notअगरier_block *unused,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_changeupper_info *info;
	काष्ठा rocker_port *rocker_port;
	पूर्णांक err;

	अगर (!rocker_port_dev_check(dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		info = ptr;
		अगर (!info->master)
			जाओ out;
		rocker_port = netdev_priv(dev);
		अगर (info->linking) अणु
			err = rocker_world_port_master_linked(rocker_port,
							      info->upper_dev);
			अगर (err)
				netdev_warn(dev, "failed to reflect master linked (err %d)\n",
					    err);
		पूर्ण अन्यथा अणु
			err = rocker_world_port_master_unlinked(rocker_port,
								info->upper_dev);
			अगर (err)
				netdev_warn(dev, "failed to reflect master unlinked (err %d)\n",
					    err);
		पूर्ण
	पूर्ण
out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rocker_netdevice_nb __पढ़ो_mostly = अणु
	.notअगरier_call = rocker_netdevice_event,
पूर्ण;

/************************************
 * Net event notअगरier event handler
 ************************************/

अटल पूर्णांक rocker_netevent_event(काष्ठा notअगरier_block *unused,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा rocker_port *rocker_port;
	काष्ठा net_device *dev;
	काष्ठा neighbour *n = ptr;
	पूर्णांक err;

	चयन (event) अणु
	हाल NETEVENT_NEIGH_UPDATE:
		अगर (n->tbl != &arp_tbl)
			वापस NOTIFY_DONE;
		dev = n->dev;
		अगर (!rocker_port_dev_check(dev))
			वापस NOTIFY_DONE;
		rocker_port = netdev_priv(dev);
		err = rocker_world_port_neigh_update(rocker_port, n);
		अगर (err)
			netdev_warn(dev, "failed to handle neigh update (err %d)\n",
				    err);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rocker_netevent_nb __पढ़ो_mostly = अणु
	.notअगरier_call = rocker_netevent_event,
पूर्ण;

/***********************
 * Module init and निकास
 ***********************/

अटल पूर्णांक __init rocker_module_init(व्योम)
अणु
	पूर्णांक err;

	रेजिस्टर_netdevice_notअगरier(&rocker_netdevice_nb);
	रेजिस्टर_netevent_notअगरier(&rocker_netevent_nb);
	err = pci_रेजिस्टर_driver(&rocker_pci_driver);
	अगर (err)
		जाओ err_pci_रेजिस्टर_driver;
	वापस 0;

err_pci_रेजिस्टर_driver:
	unरेजिस्टर_netevent_notअगरier(&rocker_netevent_nb);
	unरेजिस्टर_netdevice_notअगरier(&rocker_netdevice_nb);
	वापस err;
पूर्ण

अटल व्योम __निकास rocker_module_निकास(व्योम)
अणु
	unरेजिस्टर_netevent_notअगरier(&rocker_netevent_nb);
	unरेजिस्टर_netdevice_notअगरier(&rocker_netdevice_nb);
	pci_unरेजिस्टर_driver(&rocker_pci_driver);
पूर्ण

module_init(rocker_module_init);
module_निकास(rocker_module_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jiri@resnulli.us>");
MODULE_AUTHOR("Scott Feldman <sfeldma@gmail.com>");
MODULE_DESCRIPTION("Rocker switch device driver");
MODULE_DEVICE_TABLE(pci, rocker_pci_id_table);
