<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/log2.h>
#समावेश <linux/माला.स>

#समावेश "pci_hw.h"
#समावेश "pci.h"
#समावेश "core.h"
#समावेश "cmd.h"
#समावेश "port.h"
#समावेश "resources.h"

#घोषणा mlxsw_pci_ग_लिखो32(mlxsw_pci, reg, val) \
	ioग_लिखो32be(val, (mlxsw_pci)->hw_addr + (MLXSW_PCI_ ## reg))
#घोषणा mlxsw_pci_पढ़ो32(mlxsw_pci, reg) \
	ioपढ़ो32be((mlxsw_pci)->hw_addr + (MLXSW_PCI_ ## reg))

क्रमागत mlxsw_pci_queue_type अणु
	MLXSW_PCI_QUEUE_TYPE_SDQ,
	MLXSW_PCI_QUEUE_TYPE_RDQ,
	MLXSW_PCI_QUEUE_TYPE_CQ,
	MLXSW_PCI_QUEUE_TYPE_EQ,
पूर्ण;

#घोषणा MLXSW_PCI_QUEUE_TYPE_COUNT	4

अटल स्थिर u16 mlxsw_pci_करोorbell_type_offset[] = अणु
	MLXSW_PCI_DOORBELL_SDQ_OFFSET,	/* क्रम type MLXSW_PCI_QUEUE_TYPE_SDQ */
	MLXSW_PCI_DOORBELL_RDQ_OFFSET,	/* क्रम type MLXSW_PCI_QUEUE_TYPE_RDQ */
	MLXSW_PCI_DOORBELL_CQ_OFFSET,	/* क्रम type MLXSW_PCI_QUEUE_TYPE_CQ */
	MLXSW_PCI_DOORBELL_EQ_OFFSET,	/* क्रम type MLXSW_PCI_QUEUE_TYPE_EQ */
पूर्ण;

अटल स्थिर u16 mlxsw_pci_करोorbell_arm_type_offset[] = अणु
	0, /* unused */
	0, /* unused */
	MLXSW_PCI_DOORBELL_ARM_CQ_OFFSET, /* क्रम type MLXSW_PCI_QUEUE_TYPE_CQ */
	MLXSW_PCI_DOORBELL_ARM_EQ_OFFSET, /* क्रम type MLXSW_PCI_QUEUE_TYPE_EQ */
पूर्ण;

काष्ठा mlxsw_pci_mem_item अणु
	अक्षर *buf;
	dma_addr_t mapaddr;
	माप_प्रकार size;
पूर्ण;

काष्ठा mlxsw_pci_queue_elem_info अणु
	अक्षर *elem; /* poपूर्णांकer to actual dma mapped element mem chunk */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा sk_buff *skb;
		पूर्ण sdq;
		काष्ठा अणु
			काष्ठा sk_buff *skb;
		पूर्ण rdq;
	पूर्ण u;
पूर्ण;

काष्ठा mlxsw_pci_queue अणु
	spinlock_t lock; /* क्रम queue accesses */
	काष्ठा mlxsw_pci_mem_item mem_item;
	काष्ठा mlxsw_pci_queue_elem_info *elem_info;
	u16 producer_counter;
	u16 consumer_counter;
	u16 count; /* number of elements in queue */
	u8 num; /* queue number */
	u8 elem_size; /* size of one element */
	क्रमागत mlxsw_pci_queue_type type;
	काष्ठा tasklet_काष्ठा tasklet; /* queue processing tasklet */
	काष्ठा mlxsw_pci *pci;
	जोड़ अणु
		काष्ठा अणु
			u32 comp_sdq_count;
			u32 comp_rdq_count;
			क्रमागत mlxsw_pci_cqe_v v;
		पूर्ण cq;
		काष्ठा अणु
			u32 ev_cmd_count;
			u32 ev_comp_count;
			u32 ev_other_count;
		पूर्ण eq;
	पूर्ण u;
पूर्ण;

काष्ठा mlxsw_pci_queue_type_group अणु
	काष्ठा mlxsw_pci_queue *q;
	u8 count; /* number of queues in group */
पूर्ण;

काष्ठा mlxsw_pci अणु
	काष्ठा pci_dev *pdev;
	u8 __iomem *hw_addr;
	u64 मुक्त_running_घड़ी_offset;
	काष्ठा mlxsw_pci_queue_type_group queues[MLXSW_PCI_QUEUE_TYPE_COUNT];
	u32 करोorbell_offset;
	काष्ठा mlxsw_core *core;
	काष्ठा अणु
		काष्ठा mlxsw_pci_mem_item *items;
		अचिन्हित पूर्णांक count;
	पूर्ण fw_area;
	काष्ठा अणु
		काष्ठा mlxsw_pci_mem_item out_mbox;
		काष्ठा mlxsw_pci_mem_item in_mbox;
		काष्ठा mutex lock; /* Lock access to command रेजिस्टरs */
		bool nopoll;
		रुको_queue_head_t रुको;
		bool रुको_करोne;
		काष्ठा अणु
			u8 status;
			u64 out_param;
		पूर्ण comp;
	पूर्ण cmd;
	काष्ठा mlxsw_bus_info bus_info;
	स्थिर काष्ठा pci_device_id *id;
	क्रमागत mlxsw_pci_cqe_v max_cqe_ver; /* Maximal supported CQE version */
	u8 num_sdq_cqs; /* Number of CQs used क्रम SDQs */
पूर्ण;

अटल व्योम mlxsw_pci_queue_tasklet_schedule(काष्ठा mlxsw_pci_queue *q)
अणु
	tasklet_schedule(&q->tasklet);
पूर्ण

अटल अक्षर *__mlxsw_pci_queue_elem_get(काष्ठा mlxsw_pci_queue *q,
					माप_प्रकार elem_size, पूर्णांक elem_index)
अणु
	वापस q->mem_item.buf + (elem_size * elem_index);
पूर्ण

अटल काष्ठा mlxsw_pci_queue_elem_info *
mlxsw_pci_queue_elem_info_get(काष्ठा mlxsw_pci_queue *q, पूर्णांक elem_index)
अणु
	वापस &q->elem_info[elem_index];
पूर्ण

अटल काष्ठा mlxsw_pci_queue_elem_info *
mlxsw_pci_queue_elem_info_producer_get(काष्ठा mlxsw_pci_queue *q)
अणु
	पूर्णांक index = q->producer_counter & (q->count - 1);

	अगर ((u16) (q->producer_counter - q->consumer_counter) == q->count)
		वापस शून्य;
	वापस mlxsw_pci_queue_elem_info_get(q, index);
पूर्ण

अटल काष्ठा mlxsw_pci_queue_elem_info *
mlxsw_pci_queue_elem_info_consumer_get(काष्ठा mlxsw_pci_queue *q)
अणु
	पूर्णांक index = q->consumer_counter & (q->count - 1);

	वापस mlxsw_pci_queue_elem_info_get(q, index);
पूर्ण

अटल अक्षर *mlxsw_pci_queue_elem_get(काष्ठा mlxsw_pci_queue *q, पूर्णांक elem_index)
अणु
	वापस mlxsw_pci_queue_elem_info_get(q, elem_index)->elem;
पूर्ण

अटल bool mlxsw_pci_elem_hw_owned(काष्ठा mlxsw_pci_queue *q, bool owner_bit)
अणु
	वापस owner_bit != !!(q->consumer_counter & q->count);
पूर्ण

अटल काष्ठा mlxsw_pci_queue_type_group *
mlxsw_pci_queue_type_group_get(काष्ठा mlxsw_pci *mlxsw_pci,
			       क्रमागत mlxsw_pci_queue_type q_type)
अणु
	वापस &mlxsw_pci->queues[q_type];
पूर्ण

अटल u8 __mlxsw_pci_queue_count(काष्ठा mlxsw_pci *mlxsw_pci,
				  क्रमागत mlxsw_pci_queue_type q_type)
अणु
	काष्ठा mlxsw_pci_queue_type_group *queue_group;

	queue_group = mlxsw_pci_queue_type_group_get(mlxsw_pci, q_type);
	वापस queue_group->count;
पूर्ण

अटल u8 mlxsw_pci_sdq_count(काष्ठा mlxsw_pci *mlxsw_pci)
अणु
	वापस __mlxsw_pci_queue_count(mlxsw_pci, MLXSW_PCI_QUEUE_TYPE_SDQ);
पूर्ण

अटल u8 mlxsw_pci_cq_count(काष्ठा mlxsw_pci *mlxsw_pci)
अणु
	वापस __mlxsw_pci_queue_count(mlxsw_pci, MLXSW_PCI_QUEUE_TYPE_CQ);
पूर्ण

अटल काष्ठा mlxsw_pci_queue *
__mlxsw_pci_queue_get(काष्ठा mlxsw_pci *mlxsw_pci,
		      क्रमागत mlxsw_pci_queue_type q_type, u8 q_num)
अणु
	वापस &mlxsw_pci->queues[q_type].q[q_num];
पूर्ण

अटल काष्ठा mlxsw_pci_queue *mlxsw_pci_sdq_get(काष्ठा mlxsw_pci *mlxsw_pci,
						 u8 q_num)
अणु
	वापस __mlxsw_pci_queue_get(mlxsw_pci,
				     MLXSW_PCI_QUEUE_TYPE_SDQ, q_num);
पूर्ण

अटल काष्ठा mlxsw_pci_queue *mlxsw_pci_rdq_get(काष्ठा mlxsw_pci *mlxsw_pci,
						 u8 q_num)
अणु
	वापस __mlxsw_pci_queue_get(mlxsw_pci,
				     MLXSW_PCI_QUEUE_TYPE_RDQ, q_num);
पूर्ण

अटल काष्ठा mlxsw_pci_queue *mlxsw_pci_cq_get(काष्ठा mlxsw_pci *mlxsw_pci,
						u8 q_num)
अणु
	वापस __mlxsw_pci_queue_get(mlxsw_pci, MLXSW_PCI_QUEUE_TYPE_CQ, q_num);
पूर्ण

अटल काष्ठा mlxsw_pci_queue *mlxsw_pci_eq_get(काष्ठा mlxsw_pci *mlxsw_pci,
						u8 q_num)
अणु
	वापस __mlxsw_pci_queue_get(mlxsw_pci, MLXSW_PCI_QUEUE_TYPE_EQ, q_num);
पूर्ण

अटल व्योम __mlxsw_pci_queue_करोorbell_set(काष्ठा mlxsw_pci *mlxsw_pci,
					   काष्ठा mlxsw_pci_queue *q,
					   u16 val)
अणु
	mlxsw_pci_ग_लिखो32(mlxsw_pci,
			  DOORBELL(mlxsw_pci->करोorbell_offset,
				   mlxsw_pci_करोorbell_type_offset[q->type],
				   q->num), val);
पूर्ण

अटल व्योम __mlxsw_pci_queue_करोorbell_arm_set(काष्ठा mlxsw_pci *mlxsw_pci,
					       काष्ठा mlxsw_pci_queue *q,
					       u16 val)
अणु
	mlxsw_pci_ग_लिखो32(mlxsw_pci,
			  DOORBELL(mlxsw_pci->करोorbell_offset,
				   mlxsw_pci_करोorbell_arm_type_offset[q->type],
				   q->num), val);
पूर्ण

अटल व्योम mlxsw_pci_queue_करोorbell_producer_ring(काष्ठा mlxsw_pci *mlxsw_pci,
						   काष्ठा mlxsw_pci_queue *q)
अणु
	wmb(); /* ensure all ग_लिखोs are करोne beक्रमe we ring a bell */
	__mlxsw_pci_queue_करोorbell_set(mlxsw_pci, q, q->producer_counter);
पूर्ण

अटल व्योम mlxsw_pci_queue_करोorbell_consumer_ring(काष्ठा mlxsw_pci *mlxsw_pci,
						   काष्ठा mlxsw_pci_queue *q)
अणु
	wmb(); /* ensure all ग_लिखोs are करोne beक्रमe we ring a bell */
	__mlxsw_pci_queue_करोorbell_set(mlxsw_pci, q,
				       q->consumer_counter + q->count);
पूर्ण

अटल व्योम
mlxsw_pci_queue_करोorbell_arm_consumer_ring(काष्ठा mlxsw_pci *mlxsw_pci,
					   काष्ठा mlxsw_pci_queue *q)
अणु
	wmb(); /* ensure all ग_लिखोs are करोne beक्रमe we ring a bell */
	__mlxsw_pci_queue_करोorbell_arm_set(mlxsw_pci, q, q->consumer_counter);
पूर्ण

अटल dma_addr_t __mlxsw_pci_queue_page_get(काष्ठा mlxsw_pci_queue *q,
					     पूर्णांक page_index)
अणु
	वापस q->mem_item.mapaddr + MLXSW_PCI_PAGE_SIZE * page_index;
पूर्ण

अटल पूर्णांक mlxsw_pci_sdq_init(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
			      काष्ठा mlxsw_pci_queue *q)
अणु
	पूर्णांक tclass;
	पूर्णांक i;
	पूर्णांक err;

	q->producer_counter = 0;
	q->consumer_counter = 0;
	tclass = q->num == MLXSW_PCI_SDQ_EMAD_INDEX ? MLXSW_PCI_SDQ_EMAD_TC :
						      MLXSW_PCI_SDQ_CTL_TC;

	/* Set CQ of same number of this SDQ. */
	mlxsw_cmd_mbox_sw2hw_dq_cq_set(mbox, q->num);
	mlxsw_cmd_mbox_sw2hw_dq_sdq_tclass_set(mbox, tclass);
	mlxsw_cmd_mbox_sw2hw_dq_log2_dq_sz_set(mbox, 3); /* 8 pages */
	क्रम (i = 0; i < MLXSW_PCI_AQ_PAGES; i++) अणु
		dma_addr_t mapaddr = __mlxsw_pci_queue_page_get(q, i);

		mlxsw_cmd_mbox_sw2hw_dq_pa_set(mbox, i, mapaddr);
	पूर्ण

	err = mlxsw_cmd_sw2hw_sdq(mlxsw_pci->core, mbox, q->num);
	अगर (err)
		वापस err;
	mlxsw_pci_queue_करोorbell_producer_ring(mlxsw_pci, q);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_pci_sdq_fini(काष्ठा mlxsw_pci *mlxsw_pci,
			       काष्ठा mlxsw_pci_queue *q)
अणु
	mlxsw_cmd_hw2sw_sdq(mlxsw_pci->core, q->num);
पूर्ण

अटल पूर्णांक mlxsw_pci_wqe_frag_map(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *wqe,
				  पूर्णांक index, अक्षर *frag_data, माप_प्रकार frag_len,
				  पूर्णांक direction)
अणु
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;
	dma_addr_t mapaddr;

	mapaddr = dma_map_single(&pdev->dev, frag_data, frag_len, direction);
	अगर (unlikely(dma_mapping_error(&pdev->dev, mapaddr))) अणु
		dev_err_ratelimited(&pdev->dev, "failed to dma map tx frag\n");
		वापस -EIO;
	पूर्ण
	mlxsw_pci_wqe_address_set(wqe, index, mapaddr);
	mlxsw_pci_wqe_byte_count_set(wqe, index, frag_len);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_pci_wqe_frag_unmap(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *wqe,
				     पूर्णांक index, पूर्णांक direction)
अणु
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;
	माप_प्रकार frag_len = mlxsw_pci_wqe_byte_count_get(wqe, index);
	dma_addr_t mapaddr = mlxsw_pci_wqe_address_get(wqe, index);

	अगर (!frag_len)
		वापस;
	dma_unmap_single(&pdev->dev, mapaddr, frag_len, direction);
पूर्ण

अटल पूर्णांक mlxsw_pci_rdq_skb_alloc(काष्ठा mlxsw_pci *mlxsw_pci,
				   काष्ठा mlxsw_pci_queue_elem_info *elem_info)
अणु
	माप_प्रकार buf_len = MLXSW_PORT_MAX_MTU;
	अक्षर *wqe = elem_info->elem;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	elem_info->u.rdq.skb = शून्य;
	skb = netdev_alloc_skb_ip_align(शून्य, buf_len);
	अगर (!skb)
		वापस -ENOMEM;

	/* Assume that wqe was previously zeroed. */

	err = mlxsw_pci_wqe_frag_map(mlxsw_pci, wqe, 0, skb->data,
				     buf_len, DMA_FROM_DEVICE);
	अगर (err)
		जाओ err_frag_map;

	elem_info->u.rdq.skb = skb;
	वापस 0;

err_frag_map:
	dev_kमुक्त_skb_any(skb);
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_rdq_skb_मुक्त(काष्ठा mlxsw_pci *mlxsw_pci,
				   काष्ठा mlxsw_pci_queue_elem_info *elem_info)
अणु
	काष्ठा sk_buff *skb;
	अक्षर *wqe;

	skb = elem_info->u.rdq.skb;
	wqe = elem_info->elem;

	mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, 0, DMA_FROM_DEVICE);
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल पूर्णांक mlxsw_pci_rdq_init(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
			      काष्ठा mlxsw_pci_queue *q)
अणु
	काष्ठा mlxsw_pci_queue_elem_info *elem_info;
	u8 sdq_count = mlxsw_pci_sdq_count(mlxsw_pci);
	पूर्णांक i;
	पूर्णांक err;

	q->producer_counter = 0;
	q->consumer_counter = 0;

	/* Set CQ of same number of this RDQ with base
	 * above SDQ count as the lower ones are asचिन्हित to SDQs.
	 */
	mlxsw_cmd_mbox_sw2hw_dq_cq_set(mbox, sdq_count + q->num);
	mlxsw_cmd_mbox_sw2hw_dq_log2_dq_sz_set(mbox, 3); /* 8 pages */
	क्रम (i = 0; i < MLXSW_PCI_AQ_PAGES; i++) अणु
		dma_addr_t mapaddr = __mlxsw_pci_queue_page_get(q, i);

		mlxsw_cmd_mbox_sw2hw_dq_pa_set(mbox, i, mapaddr);
	पूर्ण

	err = mlxsw_cmd_sw2hw_rdq(mlxsw_pci->core, mbox, q->num);
	अगर (err)
		वापस err;

	mlxsw_pci_queue_करोorbell_producer_ring(mlxsw_pci, q);

	क्रम (i = 0; i < q->count; i++) अणु
		elem_info = mlxsw_pci_queue_elem_info_producer_get(q);
		BUG_ON(!elem_info);
		err = mlxsw_pci_rdq_skb_alloc(mlxsw_pci, elem_info);
		अगर (err)
			जाओ rollback;
		/* Everything is set up, ring करोorbell to pass elem to HW */
		q->producer_counter++;
		mlxsw_pci_queue_करोorbell_producer_ring(mlxsw_pci, q);
	पूर्ण

	वापस 0;

rollback:
	क्रम (i--; i >= 0; i--) अणु
		elem_info = mlxsw_pci_queue_elem_info_get(q, i);
		mlxsw_pci_rdq_skb_मुक्त(mlxsw_pci, elem_info);
	पूर्ण
	mlxsw_cmd_hw2sw_rdq(mlxsw_pci->core, q->num);

	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_rdq_fini(काष्ठा mlxsw_pci *mlxsw_pci,
			       काष्ठा mlxsw_pci_queue *q)
अणु
	काष्ठा mlxsw_pci_queue_elem_info *elem_info;
	पूर्णांक i;

	mlxsw_cmd_hw2sw_rdq(mlxsw_pci->core, q->num);
	क्रम (i = 0; i < q->count; i++) अणु
		elem_info = mlxsw_pci_queue_elem_info_get(q, i);
		mlxsw_pci_rdq_skb_मुक्त(mlxsw_pci, elem_info);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_pci_cq_pre_init(काष्ठा mlxsw_pci *mlxsw_pci,
				  काष्ठा mlxsw_pci_queue *q)
अणु
	q->u.cq.v = mlxsw_pci->max_cqe_ver;

	/* For SDQ it is poपूर्णांकless to use CQEv2, so use CQEv1 instead */
	अगर (q->u.cq.v == MLXSW_PCI_CQE_V2 &&
	    q->num < mlxsw_pci->num_sdq_cqs)
		q->u.cq.v = MLXSW_PCI_CQE_V1;
पूर्ण

अटल पूर्णांक mlxsw_pci_cq_init(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
			     काष्ठा mlxsw_pci_queue *q)
अणु
	पूर्णांक i;
	पूर्णांक err;

	q->consumer_counter = 0;

	क्रम (i = 0; i < q->count; i++) अणु
		अक्षर *elem = mlxsw_pci_queue_elem_get(q, i);

		mlxsw_pci_cqe_owner_set(q->u.cq.v, elem, 1);
	पूर्ण

	अगर (q->u.cq.v == MLXSW_PCI_CQE_V1)
		mlxsw_cmd_mbox_sw2hw_cq_cqe_ver_set(mbox,
				MLXSW_CMD_MBOX_SW2HW_CQ_CQE_VER_1);
	अन्यथा अगर (q->u.cq.v == MLXSW_PCI_CQE_V2)
		mlxsw_cmd_mbox_sw2hw_cq_cqe_ver_set(mbox,
				MLXSW_CMD_MBOX_SW2HW_CQ_CQE_VER_2);

	mlxsw_cmd_mbox_sw2hw_cq_c_eqn_set(mbox, MLXSW_PCI_EQ_COMP_NUM);
	mlxsw_cmd_mbox_sw2hw_cq_st_set(mbox, 0);
	mlxsw_cmd_mbox_sw2hw_cq_log_cq_size_set(mbox, ilog2(q->count));
	क्रम (i = 0; i < MLXSW_PCI_AQ_PAGES; i++) अणु
		dma_addr_t mapaddr = __mlxsw_pci_queue_page_get(q, i);

		mlxsw_cmd_mbox_sw2hw_cq_pa_set(mbox, i, mapaddr);
	पूर्ण
	err = mlxsw_cmd_sw2hw_cq(mlxsw_pci->core, mbox, q->num);
	अगर (err)
		वापस err;
	mlxsw_pci_queue_करोorbell_consumer_ring(mlxsw_pci, q);
	mlxsw_pci_queue_करोorbell_arm_consumer_ring(mlxsw_pci, q);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_pci_cq_fini(काष्ठा mlxsw_pci *mlxsw_pci,
			      काष्ठा mlxsw_pci_queue *q)
अणु
	mlxsw_cmd_hw2sw_cq(mlxsw_pci->core, q->num);
पूर्ण

अटल व्योम mlxsw_pci_cqe_sdq_handle(काष्ठा mlxsw_pci *mlxsw_pci,
				     काष्ठा mlxsw_pci_queue *q,
				     u16 consumer_counter_limit,
				     अक्षर *cqe)
अणु
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;
	काष्ठा mlxsw_pci_queue_elem_info *elem_info;
	काष्ठा mlxsw_tx_info tx_info;
	अक्षर *wqe;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	spin_lock(&q->lock);
	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	tx_info = mlxsw_skb_cb(elem_info->u.sdq.skb)->tx_info;
	skb = elem_info->u.sdq.skb;
	wqe = elem_info->elem;
	क्रम (i = 0; i < MLXSW_PCI_WQE_SG_ENTRIES; i++)
		mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, i, DMA_TO_DEVICE);

	अगर (unlikely(!tx_info.is_emad &&
		     skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) अणु
		mlxsw_core_ptp_transmitted(mlxsw_pci->core, skb,
					   tx_info.local_port);
		skb = शून्य;
	पूर्ण

	अगर (skb)
		dev_kमुक्त_skb_any(skb);
	elem_info->u.sdq.skb = शून्य;

	अगर (q->consumer_counter++ != consumer_counter_limit)
		dev_dbg_ratelimited(&pdev->dev, "Consumer counter does not match limit in SDQ\n");
	spin_unlock(&q->lock);
पूर्ण

अटल व्योम mlxsw_pci_cqe_rdq_md_tx_port_init(काष्ठा sk_buff *skb,
					      स्थिर अक्षर *cqe)
अणु
	काष्ठा mlxsw_skb_cb *cb = mlxsw_skb_cb(skb);

	अगर (mlxsw_pci_cqe2_tx_lag_get(cqe)) अणु
		cb->rx_md_info.tx_port_is_lag = true;
		cb->rx_md_info.tx_lag_id = mlxsw_pci_cqe2_tx_lag_id_get(cqe);
		cb->rx_md_info.tx_lag_port_index =
			mlxsw_pci_cqe2_tx_lag_subport_get(cqe);
	पूर्ण अन्यथा अणु
		cb->rx_md_info.tx_port_is_lag = false;
		cb->rx_md_info.tx_sys_port =
			mlxsw_pci_cqe2_tx_प्रणाली_port_get(cqe);
	पूर्ण

	अगर (cb->rx_md_info.tx_sys_port != MLXSW_PCI_CQE2_TX_PORT_MULTI_PORT &&
	    cb->rx_md_info.tx_sys_port != MLXSW_PCI_CQE2_TX_PORT_INVALID)
		cb->rx_md_info.tx_port_valid = 1;
	अन्यथा
		cb->rx_md_info.tx_port_valid = 0;
पूर्ण

अटल व्योम mlxsw_pci_cqe_rdq_md_init(काष्ठा sk_buff *skb, स्थिर अक्षर *cqe)
अणु
	काष्ठा mlxsw_skb_cb *cb = mlxsw_skb_cb(skb);

	cb->rx_md_info.tx_congestion = mlxsw_pci_cqe2_mirror_cong_get(cqe);
	अगर (cb->rx_md_info.tx_congestion != MLXSW_PCI_CQE2_MIRROR_CONG_INVALID)
		cb->rx_md_info.tx_congestion_valid = 1;
	अन्यथा
		cb->rx_md_info.tx_congestion_valid = 0;
	cb->rx_md_info.tx_congestion <<= MLXSW_PCI_CQE2_MIRROR_CONG_SHIFT;

	cb->rx_md_info.latency = mlxsw_pci_cqe2_mirror_latency_get(cqe);
	अगर (cb->rx_md_info.latency != MLXSW_PCI_CQE2_MIRROR_LATENCY_INVALID)
		cb->rx_md_info.latency_valid = 1;
	अन्यथा
		cb->rx_md_info.latency_valid = 0;

	cb->rx_md_info.tx_tc = mlxsw_pci_cqe2_mirror_tclass_get(cqe);
	अगर (cb->rx_md_info.tx_tc != MLXSW_PCI_CQE2_MIRROR_TCLASS_INVALID)
		cb->rx_md_info.tx_tc_valid = 1;
	अन्यथा
		cb->rx_md_info.tx_tc_valid = 0;

	mlxsw_pci_cqe_rdq_md_tx_port_init(skb, cqe);
पूर्ण

अटल व्योम mlxsw_pci_cqe_rdq_handle(काष्ठा mlxsw_pci *mlxsw_pci,
				     काष्ठा mlxsw_pci_queue *q,
				     u16 consumer_counter_limit,
				     क्रमागत mlxsw_pci_cqe_v cqe_v, अक्षर *cqe)
अणु
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;
	काष्ठा mlxsw_pci_queue_elem_info *elem_info;
	काष्ठा mlxsw_rx_info rx_info = अणुपूर्ण;
	अक्षर *wqe;
	काष्ठा sk_buff *skb;
	u16 byte_count;
	पूर्णांक err;

	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	skb = elem_info->u.sdq.skb;
	अगर (!skb)
		वापस;
	wqe = elem_info->elem;
	mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, 0, DMA_FROM_DEVICE);

	अगर (q->consumer_counter++ != consumer_counter_limit)
		dev_dbg_ratelimited(&pdev->dev, "Consumer counter does not match limit in RDQ\n");

	अगर (mlxsw_pci_cqe_lag_get(cqe_v, cqe)) अणु
		rx_info.is_lag = true;
		rx_info.u.lag_id = mlxsw_pci_cqe_lag_id_get(cqe_v, cqe);
		rx_info.lag_port_index =
			mlxsw_pci_cqe_lag_subport_get(cqe_v, cqe);
	पूर्ण अन्यथा अणु
		rx_info.is_lag = false;
		rx_info.u.sys_port = mlxsw_pci_cqe_प्रणाली_port_get(cqe);
	पूर्ण

	rx_info.trap_id = mlxsw_pci_cqe_trap_id_get(cqe);

	अगर (rx_info.trap_id == MLXSW_TRAP_ID_DISCARD_INGRESS_ACL ||
	    rx_info.trap_id == MLXSW_TRAP_ID_DISCARD_EGRESS_ACL) अणु
		u32 cookie_index = 0;

		अगर (mlxsw_pci->max_cqe_ver >= MLXSW_PCI_CQE_V2)
			cookie_index = mlxsw_pci_cqe2_user_def_val_orig_pkt_len_get(cqe);
		mlxsw_skb_cb(skb)->rx_md_info.cookie_index = cookie_index;
	पूर्ण अन्यथा अगर (rx_info.trap_id >= MLXSW_TRAP_ID_MIRROR_SESSION0 &&
		   rx_info.trap_id <= MLXSW_TRAP_ID_MIRROR_SESSION7 &&
		   mlxsw_pci->max_cqe_ver >= MLXSW_PCI_CQE_V2) अणु
		rx_info.mirror_reason = mlxsw_pci_cqe2_mirror_reason_get(cqe);
		mlxsw_pci_cqe_rdq_md_init(skb, cqe);
	पूर्ण अन्यथा अगर (rx_info.trap_id == MLXSW_TRAP_ID_PKT_SAMPLE &&
		   mlxsw_pci->max_cqe_ver >= MLXSW_PCI_CQE_V2) अणु
		mlxsw_pci_cqe_rdq_md_tx_port_init(skb, cqe);
	पूर्ण

	byte_count = mlxsw_pci_cqe_byte_count_get(cqe);
	अगर (mlxsw_pci_cqe_crc_get(cqe_v, cqe))
		byte_count -= ETH_FCS_LEN;
	skb_put(skb, byte_count);
	mlxsw_core_skb_receive(mlxsw_pci->core, skb, &rx_info);

	स_रखो(wqe, 0, q->elem_size);
	err = mlxsw_pci_rdq_skb_alloc(mlxsw_pci, elem_info);
	अगर (err)
		dev_dbg_ratelimited(&pdev->dev, "Failed to alloc skb for RDQ\n");
	/* Everything is set up, ring करोorbell to pass elem to HW */
	q->producer_counter++;
	mlxsw_pci_queue_करोorbell_producer_ring(mlxsw_pci, q);
	वापस;
पूर्ण

अटल अक्षर *mlxsw_pci_cq_sw_cqe_get(काष्ठा mlxsw_pci_queue *q)
अणु
	काष्ठा mlxsw_pci_queue_elem_info *elem_info;
	अक्षर *elem;
	bool owner_bit;

	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	elem = elem_info->elem;
	owner_bit = mlxsw_pci_cqe_owner_get(q->u.cq.v, elem);
	अगर (mlxsw_pci_elem_hw_owned(q, owner_bit))
		वापस शून्य;
	q->consumer_counter++;
	rmb(); /* make sure we पढ़ो owned bit beक्रमe the rest of elem */
	वापस elem;
पूर्ण

अटल व्योम mlxsw_pci_cq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mlxsw_pci_queue *q = from_tasklet(q, t, tasklet);
	काष्ठा mlxsw_pci *mlxsw_pci = q->pci;
	अक्षर *cqe;
	पूर्णांक items = 0;
	पूर्णांक credits = q->count >> 1;

	जबतक ((cqe = mlxsw_pci_cq_sw_cqe_get(q))) अणु
		u16 wqe_counter = mlxsw_pci_cqe_wqe_counter_get(cqe);
		u8 sendq = mlxsw_pci_cqe_sr_get(q->u.cq.v, cqe);
		u8 dqn = mlxsw_pci_cqe_dqn_get(q->u.cq.v, cqe);
		अक्षर ncqe[MLXSW_PCI_CQE_SIZE_MAX];

		स_नकल(ncqe, cqe, q->elem_size);
		mlxsw_pci_queue_करोorbell_consumer_ring(mlxsw_pci, q);

		अगर (sendq) अणु
			काष्ठा mlxsw_pci_queue *sdq;

			sdq = mlxsw_pci_sdq_get(mlxsw_pci, dqn);
			mlxsw_pci_cqe_sdq_handle(mlxsw_pci, sdq,
						 wqe_counter, ncqe);
			q->u.cq.comp_sdq_count++;
		पूर्ण अन्यथा अणु
			काष्ठा mlxsw_pci_queue *rdq;

			rdq = mlxsw_pci_rdq_get(mlxsw_pci, dqn);
			mlxsw_pci_cqe_rdq_handle(mlxsw_pci, rdq,
						 wqe_counter, q->u.cq.v, ncqe);
			q->u.cq.comp_rdq_count++;
		पूर्ण
		अगर (++items == credits)
			अवरोध;
	पूर्ण
	अगर (items)
		mlxsw_pci_queue_करोorbell_arm_consumer_ring(mlxsw_pci, q);
पूर्ण

अटल u16 mlxsw_pci_cq_elem_count(स्थिर काष्ठा mlxsw_pci_queue *q)
अणु
	वापस q->u.cq.v == MLXSW_PCI_CQE_V2 ? MLXSW_PCI_CQE2_COUNT :
					       MLXSW_PCI_CQE01_COUNT;
पूर्ण

अटल u8 mlxsw_pci_cq_elem_size(स्थिर काष्ठा mlxsw_pci_queue *q)
अणु
	वापस q->u.cq.v == MLXSW_PCI_CQE_V2 ? MLXSW_PCI_CQE2_SIZE :
					       MLXSW_PCI_CQE01_SIZE;
पूर्ण

अटल पूर्णांक mlxsw_pci_eq_init(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
			     काष्ठा mlxsw_pci_queue *q)
अणु
	पूर्णांक i;
	पूर्णांक err;

	q->consumer_counter = 0;

	क्रम (i = 0; i < q->count; i++) अणु
		अक्षर *elem = mlxsw_pci_queue_elem_get(q, i);

		mlxsw_pci_eqe_owner_set(elem, 1);
	पूर्ण

	mlxsw_cmd_mbox_sw2hw_eq_पूर्णांक_msix_set(mbox, 1); /* MSI-X used */
	mlxsw_cmd_mbox_sw2hw_eq_st_set(mbox, 1); /* armed */
	mlxsw_cmd_mbox_sw2hw_eq_log_eq_size_set(mbox, ilog2(q->count));
	क्रम (i = 0; i < MLXSW_PCI_AQ_PAGES; i++) अणु
		dma_addr_t mapaddr = __mlxsw_pci_queue_page_get(q, i);

		mlxsw_cmd_mbox_sw2hw_eq_pa_set(mbox, i, mapaddr);
	पूर्ण
	err = mlxsw_cmd_sw2hw_eq(mlxsw_pci->core, mbox, q->num);
	अगर (err)
		वापस err;
	mlxsw_pci_queue_करोorbell_consumer_ring(mlxsw_pci, q);
	mlxsw_pci_queue_करोorbell_arm_consumer_ring(mlxsw_pci, q);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_pci_eq_fini(काष्ठा mlxsw_pci *mlxsw_pci,
			      काष्ठा mlxsw_pci_queue *q)
अणु
	mlxsw_cmd_hw2sw_eq(mlxsw_pci->core, q->num);
पूर्ण

अटल व्योम mlxsw_pci_eq_cmd_event(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *eqe)
अणु
	mlxsw_pci->cmd.comp.status = mlxsw_pci_eqe_cmd_status_get(eqe);
	mlxsw_pci->cmd.comp.out_param =
		((u64) mlxsw_pci_eqe_cmd_out_param_h_get(eqe)) << 32 |
		mlxsw_pci_eqe_cmd_out_param_l_get(eqe);
	mlxsw_pci->cmd.रुको_करोne = true;
	wake_up(&mlxsw_pci->cmd.रुको);
पूर्ण

अटल अक्षर *mlxsw_pci_eq_sw_eqe_get(काष्ठा mlxsw_pci_queue *q)
अणु
	काष्ठा mlxsw_pci_queue_elem_info *elem_info;
	अक्षर *elem;
	bool owner_bit;

	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	elem = elem_info->elem;
	owner_bit = mlxsw_pci_eqe_owner_get(elem);
	अगर (mlxsw_pci_elem_hw_owned(q, owner_bit))
		वापस शून्य;
	q->consumer_counter++;
	rmb(); /* make sure we पढ़ो owned bit beक्रमe the rest of elem */
	वापस elem;
पूर्ण

अटल व्योम mlxsw_pci_eq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mlxsw_pci_queue *q = from_tasklet(q, t, tasklet);
	काष्ठा mlxsw_pci *mlxsw_pci = q->pci;
	u8 cq_count = mlxsw_pci_cq_count(mlxsw_pci);
	अचिन्हित दीर्घ active_cqns[BITS_TO_LONGS(MLXSW_PCI_CQS_MAX)];
	अक्षर *eqe;
	u8 cqn;
	bool cq_handle = false;
	पूर्णांक items = 0;
	पूर्णांक credits = q->count >> 1;

	स_रखो(&active_cqns, 0, माप(active_cqns));

	जबतक ((eqe = mlxsw_pci_eq_sw_eqe_get(q))) अणु

		/* Command पूर्णांकerface completion events are always received on
		 * queue MLXSW_PCI_EQ_ASYNC_NUM (EQ0) and completion events
		 * are mapped to queue MLXSW_PCI_EQ_COMP_NUM (EQ1).
		 */
		चयन (q->num) अणु
		हाल MLXSW_PCI_EQ_ASYNC_NUM:
			mlxsw_pci_eq_cmd_event(mlxsw_pci, eqe);
			q->u.eq.ev_cmd_count++;
			अवरोध;
		हाल MLXSW_PCI_EQ_COMP_NUM:
			cqn = mlxsw_pci_eqe_cqn_get(eqe);
			set_bit(cqn, active_cqns);
			cq_handle = true;
			q->u.eq.ev_comp_count++;
			अवरोध;
		शेष:
			q->u.eq.ev_other_count++;
		पूर्ण
		अगर (++items == credits)
			अवरोध;
	पूर्ण
	अगर (items) अणु
		mlxsw_pci_queue_करोorbell_consumer_ring(mlxsw_pci, q);
		mlxsw_pci_queue_करोorbell_arm_consumer_ring(mlxsw_pci, q);
	पूर्ण

	अगर (!cq_handle)
		वापस;
	क्रम_each_set_bit(cqn, active_cqns, cq_count) अणु
		q = mlxsw_pci_cq_get(mlxsw_pci, cqn);
		mlxsw_pci_queue_tasklet_schedule(q);
	पूर्ण
पूर्ण

काष्ठा mlxsw_pci_queue_ops अणु
	स्थिर अक्षर *name;
	क्रमागत mlxsw_pci_queue_type type;
	व्योम (*pre_init)(काष्ठा mlxsw_pci *mlxsw_pci,
			 काष्ठा mlxsw_pci_queue *q);
	पूर्णांक (*init)(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
		    काष्ठा mlxsw_pci_queue *q);
	व्योम (*fini)(काष्ठा mlxsw_pci *mlxsw_pci,
		     काष्ठा mlxsw_pci_queue *q);
	व्योम (*tasklet)(काष्ठा tasklet_काष्ठा *t);
	u16 (*elem_count_f)(स्थिर काष्ठा mlxsw_pci_queue *q);
	u8 (*elem_size_f)(स्थिर काष्ठा mlxsw_pci_queue *q);
	u16 elem_count;
	u8 elem_size;
पूर्ण;

अटल स्थिर काष्ठा mlxsw_pci_queue_ops mlxsw_pci_sdq_ops = अणु
	.type		= MLXSW_PCI_QUEUE_TYPE_SDQ,
	.init		= mlxsw_pci_sdq_init,
	.fini		= mlxsw_pci_sdq_fini,
	.elem_count	= MLXSW_PCI_WQE_COUNT,
	.elem_size	= MLXSW_PCI_WQE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_pci_queue_ops mlxsw_pci_rdq_ops = अणु
	.type		= MLXSW_PCI_QUEUE_TYPE_RDQ,
	.init		= mlxsw_pci_rdq_init,
	.fini		= mlxsw_pci_rdq_fini,
	.elem_count	= MLXSW_PCI_WQE_COUNT,
	.elem_size	= MLXSW_PCI_WQE_SIZE
पूर्ण;

अटल स्थिर काष्ठा mlxsw_pci_queue_ops mlxsw_pci_cq_ops = अणु
	.type		= MLXSW_PCI_QUEUE_TYPE_CQ,
	.pre_init	= mlxsw_pci_cq_pre_init,
	.init		= mlxsw_pci_cq_init,
	.fini		= mlxsw_pci_cq_fini,
	.tasklet	= mlxsw_pci_cq_tasklet,
	.elem_count_f	= mlxsw_pci_cq_elem_count,
	.elem_size_f	= mlxsw_pci_cq_elem_size
पूर्ण;

अटल स्थिर काष्ठा mlxsw_pci_queue_ops mlxsw_pci_eq_ops = अणु
	.type		= MLXSW_PCI_QUEUE_TYPE_EQ,
	.init		= mlxsw_pci_eq_init,
	.fini		= mlxsw_pci_eq_fini,
	.tasklet	= mlxsw_pci_eq_tasklet,
	.elem_count	= MLXSW_PCI_EQE_COUNT,
	.elem_size	= MLXSW_PCI_EQE_SIZE
पूर्ण;

अटल पूर्णांक mlxsw_pci_queue_init(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
				स्थिर काष्ठा mlxsw_pci_queue_ops *q_ops,
				काष्ठा mlxsw_pci_queue *q, u8 q_num)
अणु
	काष्ठा mlxsw_pci_mem_item *mem_item = &q->mem_item;
	पूर्णांक i;
	पूर्णांक err;

	q->num = q_num;
	अगर (q_ops->pre_init)
		q_ops->pre_init(mlxsw_pci, q);

	spin_lock_init(&q->lock);
	q->count = q_ops->elem_count_f ? q_ops->elem_count_f(q) :
					 q_ops->elem_count;
	q->elem_size = q_ops->elem_size_f ? q_ops->elem_size_f(q) :
					    q_ops->elem_size;
	q->type = q_ops->type;
	q->pci = mlxsw_pci;

	अगर (q_ops->tasklet)
		tasklet_setup(&q->tasklet, q_ops->tasklet);

	mem_item->size = MLXSW_PCI_AQ_SIZE;
	mem_item->buf = dma_alloc_coherent(&mlxsw_pci->pdev->dev,
					   mem_item->size, &mem_item->mapaddr,
					   GFP_KERNEL);
	अगर (!mem_item->buf)
		वापस -ENOMEM;

	q->elem_info = kसुस्मृति(q->count, माप(*q->elem_info), GFP_KERNEL);
	अगर (!q->elem_info) अणु
		err = -ENOMEM;
		जाओ err_elem_info_alloc;
	पूर्ण

	/* Initialize dma mapped elements info elem_info क्रम
	 * future easy access.
	 */
	क्रम (i = 0; i < q->count; i++) अणु
		काष्ठा mlxsw_pci_queue_elem_info *elem_info;

		elem_info = mlxsw_pci_queue_elem_info_get(q, i);
		elem_info->elem =
			__mlxsw_pci_queue_elem_get(q, q->elem_size, i);
	पूर्ण

	mlxsw_cmd_mbox_zero(mbox);
	err = q_ops->init(mlxsw_pci, mbox, q);
	अगर (err)
		जाओ err_q_ops_init;
	वापस 0;

err_q_ops_init:
	kमुक्त(q->elem_info);
err_elem_info_alloc:
	dma_मुक्त_coherent(&mlxsw_pci->pdev->dev, mem_item->size,
			  mem_item->buf, mem_item->mapaddr);
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_queue_fini(काष्ठा mlxsw_pci *mlxsw_pci,
				 स्थिर काष्ठा mlxsw_pci_queue_ops *q_ops,
				 काष्ठा mlxsw_pci_queue *q)
अणु
	काष्ठा mlxsw_pci_mem_item *mem_item = &q->mem_item;

	q_ops->fini(mlxsw_pci, q);
	kमुक्त(q->elem_info);
	dma_मुक्त_coherent(&mlxsw_pci->pdev->dev, mem_item->size,
			  mem_item->buf, mem_item->mapaddr);
पूर्ण

अटल पूर्णांक mlxsw_pci_queue_group_init(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
				      स्थिर काष्ठा mlxsw_pci_queue_ops *q_ops,
				      u8 num_qs)
अणु
	काष्ठा mlxsw_pci_queue_type_group *queue_group;
	पूर्णांक i;
	पूर्णांक err;

	queue_group = mlxsw_pci_queue_type_group_get(mlxsw_pci, q_ops->type);
	queue_group->q = kसुस्मृति(num_qs, माप(*queue_group->q), GFP_KERNEL);
	अगर (!queue_group->q)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_qs; i++) अणु
		err = mlxsw_pci_queue_init(mlxsw_pci, mbox, q_ops,
					   &queue_group->q[i], i);
		अगर (err)
			जाओ err_queue_init;
	पूर्ण
	queue_group->count = num_qs;

	वापस 0;

err_queue_init:
	क्रम (i--; i >= 0; i--)
		mlxsw_pci_queue_fini(mlxsw_pci, q_ops, &queue_group->q[i]);
	kमुक्त(queue_group->q);
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_queue_group_fini(काष्ठा mlxsw_pci *mlxsw_pci,
				       स्थिर काष्ठा mlxsw_pci_queue_ops *q_ops)
अणु
	काष्ठा mlxsw_pci_queue_type_group *queue_group;
	पूर्णांक i;

	queue_group = mlxsw_pci_queue_type_group_get(mlxsw_pci, q_ops->type);
	क्रम (i = 0; i < queue_group->count; i++)
		mlxsw_pci_queue_fini(mlxsw_pci, q_ops, &queue_group->q[i]);
	kमुक्त(queue_group->q);
पूर्ण

अटल पूर्णांक mlxsw_pci_aqs_init(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox)
अणु
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;
	u8 num_sdqs;
	u8 sdq_log2sz;
	u8 num_rdqs;
	u8 rdq_log2sz;
	u8 num_cqs;
	u8 cq_log2sz;
	u8 cqv2_log2sz;
	u8 num_eqs;
	u8 eq_log2sz;
	पूर्णांक err;

	mlxsw_cmd_mbox_zero(mbox);
	err = mlxsw_cmd_query_aq_cap(mlxsw_pci->core, mbox);
	अगर (err)
		वापस err;

	num_sdqs = mlxsw_cmd_mbox_query_aq_cap_max_num_sdqs_get(mbox);
	sdq_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_sdq_sz_get(mbox);
	num_rdqs = mlxsw_cmd_mbox_query_aq_cap_max_num_rdqs_get(mbox);
	rdq_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_rdq_sz_get(mbox);
	num_cqs = mlxsw_cmd_mbox_query_aq_cap_max_num_cqs_get(mbox);
	cq_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_cq_sz_get(mbox);
	cqv2_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_cqv2_sz_get(mbox);
	num_eqs = mlxsw_cmd_mbox_query_aq_cap_max_num_eqs_get(mbox);
	eq_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_eq_sz_get(mbox);

	अगर (num_sdqs + num_rdqs > num_cqs ||
	    num_sdqs < MLXSW_PCI_SDQS_MIN ||
	    num_cqs > MLXSW_PCI_CQS_MAX || num_eqs != MLXSW_PCI_EQS_COUNT) अणु
		dev_err(&pdev->dev, "Unsupported number of queues\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((1 << sdq_log2sz != MLXSW_PCI_WQE_COUNT) ||
	    (1 << rdq_log2sz != MLXSW_PCI_WQE_COUNT) ||
	    (1 << cq_log2sz != MLXSW_PCI_CQE01_COUNT) ||
	    (mlxsw_pci->max_cqe_ver == MLXSW_PCI_CQE_V2 &&
	     (1 << cqv2_log2sz != MLXSW_PCI_CQE2_COUNT)) ||
	    (1 << eq_log2sz != MLXSW_PCI_EQE_COUNT)) अणु
		dev_err(&pdev->dev, "Unsupported number of async queue descriptors\n");
		वापस -EINVAL;
	पूर्ण

	mlxsw_pci->num_sdq_cqs = num_sdqs;

	err = mlxsw_pci_queue_group_init(mlxsw_pci, mbox, &mlxsw_pci_eq_ops,
					 num_eqs);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize event queues\n");
		वापस err;
	पूर्ण

	err = mlxsw_pci_queue_group_init(mlxsw_pci, mbox, &mlxsw_pci_cq_ops,
					 num_cqs);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize completion queues\n");
		जाओ err_cqs_init;
	पूर्ण

	err = mlxsw_pci_queue_group_init(mlxsw_pci, mbox, &mlxsw_pci_sdq_ops,
					 num_sdqs);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize send descriptor queues\n");
		जाओ err_sdqs_init;
	पूर्ण

	err = mlxsw_pci_queue_group_init(mlxsw_pci, mbox, &mlxsw_pci_rdq_ops,
					 num_rdqs);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize receive descriptor queues\n");
		जाओ err_rdqs_init;
	पूर्ण

	/* We have to poll in command पूर्णांकerface until queues are initialized */
	mlxsw_pci->cmd.nopoll = true;
	वापस 0;

err_rdqs_init:
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_sdq_ops);
err_sdqs_init:
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_cq_ops);
err_cqs_init:
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_eq_ops);
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_aqs_fini(काष्ठा mlxsw_pci *mlxsw_pci)
अणु
	mlxsw_pci->cmd.nopoll = false;
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_rdq_ops);
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_sdq_ops);
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_cq_ops);
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_eq_ops);
पूर्ण

अटल व्योम
mlxsw_pci_config_profile_swid_config(काष्ठा mlxsw_pci *mlxsw_pci,
				     अक्षर *mbox, पूर्णांक index,
				     स्थिर काष्ठा mlxsw_swid_config *swid)
अणु
	u8 mask = 0;

	अगर (swid->used_type) अणु
		mlxsw_cmd_mbox_config_profile_swid_config_type_set(
			mbox, index, swid->type);
		mask |= 1;
	पूर्ण
	अगर (swid->used_properties) अणु
		mlxsw_cmd_mbox_config_profile_swid_config_properties_set(
			mbox, index, swid->properties);
		mask |= 2;
	पूर्ण
	mlxsw_cmd_mbox_config_profile_swid_config_mask_set(mbox, index, mask);
पूर्ण

अटल पूर्णांक
mlxsw_pci_profile_get_kvd_sizes(स्थिर काष्ठा mlxsw_pci *mlxsw_pci,
				स्थिर काष्ठा mlxsw_config_profile *profile,
				काष्ठा mlxsw_res *res)
अणु
	u64 single_size, द्विगुन_size, linear_size;
	पूर्णांक err;

	err = mlxsw_core_kvd_sizes_get(mlxsw_pci->core, profile,
				       &single_size, &द्विगुन_size,
				       &linear_size);
	अगर (err)
		वापस err;

	MLXSW_RES_SET(res, KVD_SINGLE_SIZE, single_size);
	MLXSW_RES_SET(res, KVD_DOUBLE_SIZE, द्विगुन_size);
	MLXSW_RES_SET(res, KVD_LINEAR_SIZE, linear_size);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_pci_config_profile(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
				    स्थिर काष्ठा mlxsw_config_profile *profile,
				    काष्ठा mlxsw_res *res)
अणु
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_cmd_mbox_zero(mbox);

	अगर (profile->used_max_vepa_channels) अणु
		mlxsw_cmd_mbox_config_profile_set_max_vepa_channels_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_vepa_channels_set(
			mbox, profile->max_vepa_channels);
	पूर्ण
	अगर (profile->used_max_mid) अणु
		mlxsw_cmd_mbox_config_profile_set_max_mid_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_mid_set(
			mbox, profile->max_mid);
	पूर्ण
	अगर (profile->used_max_pgt) अणु
		mlxsw_cmd_mbox_config_profile_set_max_pgt_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_pgt_set(
			mbox, profile->max_pgt);
	पूर्ण
	अगर (profile->used_max_प्रणाली_port) अणु
		mlxsw_cmd_mbox_config_profile_set_max_प्रणाली_port_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_प्रणाली_port_set(
			mbox, profile->max_प्रणाली_port);
	पूर्ण
	अगर (profile->used_max_vlan_groups) अणु
		mlxsw_cmd_mbox_config_profile_set_max_vlan_groups_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_vlan_groups_set(
			mbox, profile->max_vlan_groups);
	पूर्ण
	अगर (profile->used_max_regions) अणु
		mlxsw_cmd_mbox_config_profile_set_max_regions_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_regions_set(
			mbox, profile->max_regions);
	पूर्ण
	अगर (profile->used_flood_tables) अणु
		mlxsw_cmd_mbox_config_profile_set_flood_tables_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_flood_tables_set(
			mbox, profile->max_flood_tables);
		mlxsw_cmd_mbox_config_profile_max_vid_flood_tables_set(
			mbox, profile->max_vid_flood_tables);
		mlxsw_cmd_mbox_config_profile_max_fid_offset_flood_tables_set(
			mbox, profile->max_fid_offset_flood_tables);
		mlxsw_cmd_mbox_config_profile_fid_offset_flood_table_size_set(
			mbox, profile->fid_offset_flood_table_size);
		mlxsw_cmd_mbox_config_profile_max_fid_flood_tables_set(
			mbox, profile->max_fid_flood_tables);
		mlxsw_cmd_mbox_config_profile_fid_flood_table_size_set(
			mbox, profile->fid_flood_table_size);
	पूर्ण
	अगर (profile->used_flood_mode) अणु
		mlxsw_cmd_mbox_config_profile_set_flood_mode_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_flood_mode_set(
			mbox, profile->flood_mode);
	पूर्ण
	अगर (profile->used_max_ib_mc) अणु
		mlxsw_cmd_mbox_config_profile_set_max_ib_mc_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_ib_mc_set(
			mbox, profile->max_ib_mc);
	पूर्ण
	अगर (profile->used_max_pkey) अणु
		mlxsw_cmd_mbox_config_profile_set_max_pkey_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_max_pkey_set(
			mbox, profile->max_pkey);
	पूर्ण
	अगर (profile->used_ar_sec) अणु
		mlxsw_cmd_mbox_config_profile_set_ar_sec_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_ar_sec_set(
			mbox, profile->ar_sec);
	पूर्ण
	अगर (profile->used_adaptive_routing_group_cap) अणु
		mlxsw_cmd_mbox_config_profile_set_adaptive_routing_group_cap_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_adaptive_routing_group_cap_set(
			mbox, profile->adaptive_routing_group_cap);
	पूर्ण
	अगर (profile->used_kvd_sizes && MLXSW_RES_VALID(res, KVD_SIZE)) अणु
		err = mlxsw_pci_profile_get_kvd_sizes(mlxsw_pci, profile, res);
		अगर (err)
			वापस err;

		mlxsw_cmd_mbox_config_profile_set_kvd_linear_size_set(mbox, 1);
		mlxsw_cmd_mbox_config_profile_kvd_linear_size_set(mbox,
					MLXSW_RES_GET(res, KVD_LINEAR_SIZE));
		mlxsw_cmd_mbox_config_profile_set_kvd_hash_single_size_set(mbox,
									   1);
		mlxsw_cmd_mbox_config_profile_kvd_hash_single_size_set(mbox,
					MLXSW_RES_GET(res, KVD_SINGLE_SIZE));
		mlxsw_cmd_mbox_config_profile_set_kvd_hash_द्विगुन_size_set(
								mbox, 1);
		mlxsw_cmd_mbox_config_profile_kvd_hash_द्विगुन_size_set(mbox,
					MLXSW_RES_GET(res, KVD_DOUBLE_SIZE));
	पूर्ण
	अगर (profile->used_kvh_xlt_cache_mode) अणु
		mlxsw_cmd_mbox_config_profile_set_kvh_xlt_cache_mode_set(
			mbox, 1);
		mlxsw_cmd_mbox_config_profile_kvh_xlt_cache_mode_set(
			mbox, profile->kvh_xlt_cache_mode);
	पूर्ण

	क्रम (i = 0; i < MLXSW_CONFIG_PROखाता_SWID_COUNT; i++)
		mlxsw_pci_config_profile_swid_config(mlxsw_pci, mbox, i,
						     &profile->swid_config[i]);

	अगर (mlxsw_pci->max_cqe_ver > MLXSW_PCI_CQE_V0) अणु
		mlxsw_cmd_mbox_config_profile_set_cqe_version_set(mbox, 1);
		mlxsw_cmd_mbox_config_profile_cqe_version_set(mbox, 1);
	पूर्ण

	वापस mlxsw_cmd_config_profile_set(mlxsw_pci->core, mbox);
पूर्ण

अटल पूर्णांक mlxsw_pci_boardinfo_xm_process(काष्ठा mlxsw_pci *mlxsw_pci,
					  काष्ठा mlxsw_bus_info *bus_info,
					  अक्षर *mbox)
अणु
	पूर्णांक count = mlxsw_cmd_mbox_boardinfo_xm_num_local_ports_get(mbox);
	पूर्णांक i;

	अगर (!mlxsw_cmd_mbox_boardinfo_xm_exists_get(mbox))
		वापस 0;

	bus_info->xm_exists = true;

	अगर (count > MLXSW_BUS_INFO_XM_LOCAL_PORTS_MAX) अणु
		dev_err(&mlxsw_pci->pdev->dev, "Invalid number of XM local ports\n");
		वापस -EINVAL;
	पूर्ण
	bus_info->xm_local_ports_count = count;
	क्रम (i = 0; i < count; i++)
		bus_info->xm_local_ports[i] =
			mlxsw_cmd_mbox_boardinfo_xm_local_port_entry_get(mbox,
									 i);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_pci_boardinfo(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox)
अणु
	काष्ठा mlxsw_bus_info *bus_info = &mlxsw_pci->bus_info;
	पूर्णांक err;

	mlxsw_cmd_mbox_zero(mbox);
	err = mlxsw_cmd_boardinfo(mlxsw_pci->core, mbox);
	अगर (err)
		वापस err;
	mlxsw_cmd_mbox_boardinfo_vsd_स_नकल_from(mbox, bus_info->vsd);
	mlxsw_cmd_mbox_boardinfo_psid_स_नकल_from(mbox, bus_info->psid);

	वापस mlxsw_pci_boardinfo_xm_process(mlxsw_pci, bus_info, mbox);
पूर्ण

अटल पूर्णांक mlxsw_pci_fw_area_init(काष्ठा mlxsw_pci *mlxsw_pci, अक्षर *mbox,
				  u16 num_pages)
अणु
	काष्ठा mlxsw_pci_mem_item *mem_item;
	पूर्णांक nent = 0;
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_pci->fw_area.items = kसुस्मृति(num_pages, माप(*mem_item),
					   GFP_KERNEL);
	अगर (!mlxsw_pci->fw_area.items)
		वापस -ENOMEM;
	mlxsw_pci->fw_area.count = num_pages;

	mlxsw_cmd_mbox_zero(mbox);
	क्रम (i = 0; i < num_pages; i++) अणु
		mem_item = &mlxsw_pci->fw_area.items[i];

		mem_item->size = MLXSW_PCI_PAGE_SIZE;
		mem_item->buf = dma_alloc_coherent(&mlxsw_pci->pdev->dev,
						   mem_item->size,
						   &mem_item->mapaddr, GFP_KERNEL);
		अगर (!mem_item->buf) अणु
			err = -ENOMEM;
			जाओ err_alloc;
		पूर्ण
		mlxsw_cmd_mbox_map_fa_pa_set(mbox, nent, mem_item->mapaddr);
		mlxsw_cmd_mbox_map_fa_log2size_set(mbox, nent, 0); /* 1 page */
		अगर (++nent == MLXSW_CMD_MAP_FA_VPM_ENTRIES_MAX) अणु
			err = mlxsw_cmd_map_fa(mlxsw_pci->core, mbox, nent);
			अगर (err)
				जाओ err_cmd_map_fa;
			nent = 0;
			mlxsw_cmd_mbox_zero(mbox);
		पूर्ण
	पूर्ण

	अगर (nent) अणु
		err = mlxsw_cmd_map_fa(mlxsw_pci->core, mbox, nent);
		अगर (err)
			जाओ err_cmd_map_fa;
	पूर्ण

	वापस 0;

err_cmd_map_fa:
err_alloc:
	क्रम (i--; i >= 0; i--) अणु
		mem_item = &mlxsw_pci->fw_area.items[i];

		dma_मुक्त_coherent(&mlxsw_pci->pdev->dev, mem_item->size,
				  mem_item->buf, mem_item->mapaddr);
	पूर्ण
	kमुक्त(mlxsw_pci->fw_area.items);
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_fw_area_fini(काष्ठा mlxsw_pci *mlxsw_pci)
अणु
	काष्ठा mlxsw_pci_mem_item *mem_item;
	पूर्णांक i;

	mlxsw_cmd_unmap_fa(mlxsw_pci->core);

	क्रम (i = 0; i < mlxsw_pci->fw_area.count; i++) अणु
		mem_item = &mlxsw_pci->fw_area.items[i];

		dma_मुक्त_coherent(&mlxsw_pci->pdev->dev, mem_item->size,
				  mem_item->buf, mem_item->mapaddr);
	पूर्ण
	kमुक्त(mlxsw_pci->fw_area.items);
पूर्ण

अटल irqवापस_t mlxsw_pci_eq_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = dev_id;
	काष्ठा mlxsw_pci_queue *q;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_PCI_EQS_COUNT; i++) अणु
		q = mlxsw_pci_eq_get(mlxsw_pci, i);
		mlxsw_pci_queue_tasklet_schedule(q);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mlxsw_pci_mbox_alloc(काष्ठा mlxsw_pci *mlxsw_pci,
				काष्ठा mlxsw_pci_mem_item *mbox)
अणु
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;
	पूर्णांक err = 0;

	mbox->size = MLXSW_CMD_MBOX_SIZE;
	mbox->buf = dma_alloc_coherent(&pdev->dev, MLXSW_CMD_MBOX_SIZE,
				       &mbox->mapaddr, GFP_KERNEL);
	अगर (!mbox->buf) अणु
		dev_err(&pdev->dev, "Failed allocating memory for mailbox\n");
		err = -ENOMEM;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_mbox_मुक्त(काष्ठा mlxsw_pci *mlxsw_pci,
				काष्ठा mlxsw_pci_mem_item *mbox)
अणु
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;

	dma_मुक्त_coherent(&pdev->dev, MLXSW_CMD_MBOX_SIZE, mbox->buf,
			  mbox->mapaddr);
पूर्ण

अटल पूर्णांक mlxsw_pci_sys_पढ़ोy_रुको(काष्ठा mlxsw_pci *mlxsw_pci,
				    स्थिर काष्ठा pci_device_id *id,
				    u32 *p_sys_status)
अणु
	अचिन्हित दीर्घ end;
	u32 val;

	अगर (id->device == PCI_DEVICE_ID_MELLANOX_SWITCHX2) अणु
		msleep(MLXSW_PCI_SW_RESET_TIMEOUT_MSECS);
		वापस 0;
	पूर्ण

	/* We must रुको क्रम the HW to become responsive. */
	msleep(MLXSW_PCI_SW_RESET_WAIT_MSECS);

	end = jअगरfies + msecs_to_jअगरfies(MLXSW_PCI_SW_RESET_TIMEOUT_MSECS);
	करो अणु
		val = mlxsw_pci_पढ़ो32(mlxsw_pci, FW_READY);
		अगर ((val & MLXSW_PCI_FW_READY_MASK) == MLXSW_PCI_FW_READY_MAGIC)
			वापस 0;
		cond_resched();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	*p_sys_status = val & MLXSW_PCI_FW_READY_MASK;

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक mlxsw_pci_sw_reset(काष्ठा mlxsw_pci *mlxsw_pci,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;
	अक्षर mrsr_pl[MLXSW_REG_MRSR_LEN];
	u32 sys_status;
	पूर्णांक err;

	err = mlxsw_pci_sys_पढ़ोy_रुको(mlxsw_pci, id, &sys_status);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to reach system ready status before reset. Status is 0x%x\n",
			sys_status);
		वापस err;
	पूर्ण

	mlxsw_reg_mrsr_pack(mrsr_pl);
	err = mlxsw_reg_ग_लिखो(mlxsw_pci->core, MLXSW_REG(mrsr), mrsr_pl);
	अगर (err)
		वापस err;

	err = mlxsw_pci_sys_पढ़ोy_रुको(mlxsw_pci, id, &sys_status);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to reach system ready status after reset. Status is 0x%x\n",
			sys_status);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_pci_alloc_irq_vectors(काष्ठा mlxsw_pci *mlxsw_pci)
अणु
	पूर्णांक err;

	err = pci_alloc_irq_vectors(mlxsw_pci->pdev, 1, 1, PCI_IRQ_MSIX);
	अगर (err < 0)
		dev_err(&mlxsw_pci->pdev->dev, "MSI-X init failed\n");
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_मुक्त_irq_vectors(काष्ठा mlxsw_pci *mlxsw_pci)
अणु
	pci_मुक्त_irq_vectors(mlxsw_pci->pdev);
पूर्ण

अटल पूर्णांक mlxsw_pci_init(व्योम *bus_priv, काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा mlxsw_config_profile *profile,
			  काष्ठा mlxsw_res *res)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = bus_priv;
	काष्ठा pci_dev *pdev = mlxsw_pci->pdev;
	अक्षर *mbox;
	u16 num_pages;
	पूर्णांक err;

	mlxsw_pci->core = mlxsw_core;

	mbox = mlxsw_cmd_mbox_alloc();
	अगर (!mbox)
		वापस -ENOMEM;

	err = mlxsw_pci_sw_reset(mlxsw_pci, mlxsw_pci->id);
	अगर (err)
		जाओ err_sw_reset;

	err = mlxsw_pci_alloc_irq_vectors(mlxsw_pci);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "MSI-X init failed\n");
		जाओ err_alloc_irq;
	पूर्ण

	err = mlxsw_cmd_query_fw(mlxsw_core, mbox);
	अगर (err)
		जाओ err_query_fw;

	mlxsw_pci->bus_info.fw_rev.major =
		mlxsw_cmd_mbox_query_fw_fw_rev_major_get(mbox);
	mlxsw_pci->bus_info.fw_rev.minor =
		mlxsw_cmd_mbox_query_fw_fw_rev_minor_get(mbox);
	mlxsw_pci->bus_info.fw_rev.subminor =
		mlxsw_cmd_mbox_query_fw_fw_rev_subminor_get(mbox);

	अगर (mlxsw_cmd_mbox_query_fw_cmd_पूर्णांकerface_rev_get(mbox) != 1) अणु
		dev_err(&pdev->dev, "Unsupported cmd interface revision ID queried from hw\n");
		err = -EINVAL;
		जाओ err_अगरace_rev;
	पूर्ण
	अगर (mlxsw_cmd_mbox_query_fw_करोorbell_page_bar_get(mbox) != 0) अणु
		dev_err(&pdev->dev, "Unsupported doorbell page bar queried from hw\n");
		err = -EINVAL;
		जाओ err_करोorbell_page_bar;
	पूर्ण

	mlxsw_pci->करोorbell_offset =
		mlxsw_cmd_mbox_query_fw_करोorbell_page_offset_get(mbox);

	अगर (mlxsw_cmd_mbox_query_fw_fr_rn_clk_bar_get(mbox) != 0) अणु
		dev_err(&pdev->dev, "Unsupported free running clock BAR queried from hw\n");
		err = -EINVAL;
		जाओ err_fr_rn_clk_bar;
	पूर्ण

	mlxsw_pci->मुक्त_running_घड़ी_offset =
		mlxsw_cmd_mbox_query_fw_मुक्त_running_घड़ी_offset_get(mbox);

	num_pages = mlxsw_cmd_mbox_query_fw_fw_pages_get(mbox);
	err = mlxsw_pci_fw_area_init(mlxsw_pci, mbox, num_pages);
	अगर (err)
		जाओ err_fw_area_init;

	err = mlxsw_pci_boardinfo(mlxsw_pci, mbox);
	अगर (err)
		जाओ err_boardinfo;

	err = mlxsw_core_resources_query(mlxsw_core, mbox, res);
	अगर (err)
		जाओ err_query_resources;

	अगर (MLXSW_CORE_RES_VALID(mlxsw_core, CQE_V2) &&
	    MLXSW_CORE_RES_GET(mlxsw_core, CQE_V2))
		mlxsw_pci->max_cqe_ver = MLXSW_PCI_CQE_V2;
	अन्यथा अगर (MLXSW_CORE_RES_VALID(mlxsw_core, CQE_V1) &&
		 MLXSW_CORE_RES_GET(mlxsw_core, CQE_V1))
		mlxsw_pci->max_cqe_ver = MLXSW_PCI_CQE_V1;
	अन्यथा अगर ((MLXSW_CORE_RES_VALID(mlxsw_core, CQE_V0) &&
		  MLXSW_CORE_RES_GET(mlxsw_core, CQE_V0)) ||
		 !MLXSW_CORE_RES_VALID(mlxsw_core, CQE_V0)) अणु
		mlxsw_pci->max_cqe_ver = MLXSW_PCI_CQE_V0;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Invalid supported CQE version combination reported\n");
		जाओ err_cqe_v_check;
	पूर्ण

	err = mlxsw_pci_config_profile(mlxsw_pci, mbox, profile, res);
	अगर (err)
		जाओ err_config_profile;

	err = mlxsw_pci_aqs_init(mlxsw_pci, mbox);
	अगर (err)
		जाओ err_aqs_init;

	err = request_irq(pci_irq_vector(pdev, 0),
			  mlxsw_pci_eq_irq_handler, 0,
			  mlxsw_pci->bus_info.device_kind, mlxsw_pci);
	अगर (err) अणु
		dev_err(&pdev->dev, "IRQ request failed\n");
		जाओ err_request_eq_irq;
	पूर्ण

	जाओ mbox_put;

err_request_eq_irq:
	mlxsw_pci_aqs_fini(mlxsw_pci);
err_aqs_init:
err_config_profile:
err_cqe_v_check:
err_query_resources:
err_boardinfo:
	mlxsw_pci_fw_area_fini(mlxsw_pci);
err_fw_area_init:
err_fr_rn_clk_bar:
err_करोorbell_page_bar:
err_अगरace_rev:
err_query_fw:
	mlxsw_pci_मुक्त_irq_vectors(mlxsw_pci);
err_alloc_irq:
err_sw_reset:
mbox_put:
	mlxsw_cmd_mbox_मुक्त(mbox);
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_fini(व्योम *bus_priv)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = bus_priv;

	मुक्त_irq(pci_irq_vector(mlxsw_pci->pdev, 0), mlxsw_pci);
	mlxsw_pci_aqs_fini(mlxsw_pci);
	mlxsw_pci_fw_area_fini(mlxsw_pci);
	mlxsw_pci_मुक्त_irq_vectors(mlxsw_pci);
पूर्ण

अटल काष्ठा mlxsw_pci_queue *
mlxsw_pci_sdq_pick(काष्ठा mlxsw_pci *mlxsw_pci,
		   स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	u8 ctl_sdq_count = mlxsw_pci_sdq_count(mlxsw_pci) - 1;
	u8 sdqn;

	अगर (tx_info->is_emad) अणु
		sdqn = MLXSW_PCI_SDQ_EMAD_INDEX;
	पूर्ण अन्यथा अणु
		BUILD_BUG_ON(MLXSW_PCI_SDQ_EMAD_INDEX != 0);
		sdqn = 1 + (tx_info->local_port % ctl_sdq_count);
	पूर्ण

	वापस mlxsw_pci_sdq_get(mlxsw_pci, sdqn);
पूर्ण

अटल bool mlxsw_pci_skb_transmit_busy(व्योम *bus_priv,
					स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = bus_priv;
	काष्ठा mlxsw_pci_queue *q = mlxsw_pci_sdq_pick(mlxsw_pci, tx_info);

	वापस !mlxsw_pci_queue_elem_info_producer_get(q);
पूर्ण

अटल पूर्णांक mlxsw_pci_skb_transmit(व्योम *bus_priv, काष्ठा sk_buff *skb,
				  स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = bus_priv;
	काष्ठा mlxsw_pci_queue *q;
	काष्ठा mlxsw_pci_queue_elem_info *elem_info;
	अक्षर *wqe;
	पूर्णांक i;
	पूर्णांक err;

	अगर (skb_shinfo(skb)->nr_frags > MLXSW_PCI_WQE_SG_ENTRIES - 1) अणु
		err = skb_linearize(skb);
		अगर (err)
			वापस err;
	पूर्ण

	q = mlxsw_pci_sdq_pick(mlxsw_pci, tx_info);
	spin_lock_bh(&q->lock);
	elem_info = mlxsw_pci_queue_elem_info_producer_get(q);
	अगर (!elem_info) अणु
		/* queue is full */
		err = -EAGAIN;
		जाओ unlock;
	पूर्ण
	mlxsw_skb_cb(skb)->tx_info = *tx_info;
	elem_info->u.sdq.skb = skb;

	wqe = elem_info->elem;
	mlxsw_pci_wqe_c_set(wqe, 1); /* always report completion */
	mlxsw_pci_wqe_lp_set(wqe, !!tx_info->is_emad);
	mlxsw_pci_wqe_type_set(wqe, MLXSW_PCI_WQE_TYPE_ETHERNET);

	err = mlxsw_pci_wqe_frag_map(mlxsw_pci, wqe, 0, skb->data,
				     skb_headlen(skb), DMA_TO_DEVICE);
	अगर (err)
		जाओ unlock;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		err = mlxsw_pci_wqe_frag_map(mlxsw_pci, wqe, i + 1,
					     skb_frag_address(frag),
					     skb_frag_size(frag),
					     DMA_TO_DEVICE);
		अगर (err)
			जाओ unmap_frags;
	पूर्ण

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	/* Set unused sq entries byte count to zero. */
	क्रम (i++; i < MLXSW_PCI_WQE_SG_ENTRIES; i++)
		mlxsw_pci_wqe_byte_count_set(wqe, i, 0);

	/* Everything is set up, ring producer करोorbell to get HW going */
	q->producer_counter++;
	mlxsw_pci_queue_करोorbell_producer_ring(mlxsw_pci, q);

	जाओ unlock;

unmap_frags:
	क्रम (; i >= 0; i--)
		mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, i, DMA_TO_DEVICE);
unlock:
	spin_unlock_bh(&q->lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_pci_cmd_exec(व्योम *bus_priv, u16 opcode, u8 opcode_mod,
			      u32 in_mod, bool out_mbox_direct,
			      अक्षर *in_mbox, माप_प्रकार in_mbox_size,
			      अक्षर *out_mbox, माप_प्रकार out_mbox_size,
			      u8 *p_status)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = bus_priv;
	dma_addr_t in_mapaddr = 0, out_mapaddr = 0;
	bool evreq = mlxsw_pci->cmd.nopoll;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(MLXSW_PCI_CIR_TIMEOUT_MSECS);
	bool *p_रुको_करोne = &mlxsw_pci->cmd.रुको_करोne;
	पूर्णांक err;

	*p_status = MLXSW_CMD_STATUS_OK;

	err = mutex_lock_पूर्णांकerruptible(&mlxsw_pci->cmd.lock);
	अगर (err)
		वापस err;

	अगर (in_mbox) अणु
		स_नकल(mlxsw_pci->cmd.in_mbox.buf, in_mbox, in_mbox_size);
		in_mapaddr = mlxsw_pci->cmd.in_mbox.mapaddr;
	पूर्ण
	mlxsw_pci_ग_लिखो32(mlxsw_pci, CIR_IN_PARAM_HI, upper_32_bits(in_mapaddr));
	mlxsw_pci_ग_लिखो32(mlxsw_pci, CIR_IN_PARAM_LO, lower_32_bits(in_mapaddr));

	अगर (out_mbox)
		out_mapaddr = mlxsw_pci->cmd.out_mbox.mapaddr;
	mlxsw_pci_ग_लिखो32(mlxsw_pci, CIR_OUT_PARAM_HI, upper_32_bits(out_mapaddr));
	mlxsw_pci_ग_लिखो32(mlxsw_pci, CIR_OUT_PARAM_LO, lower_32_bits(out_mapaddr));

	mlxsw_pci_ग_लिखो32(mlxsw_pci, CIR_IN_MODIFIER, in_mod);
	mlxsw_pci_ग_लिखो32(mlxsw_pci, CIR_TOKEN, 0);

	*p_रुको_करोne = false;

	wmb(); /* all needs to be written beक्रमe we ग_लिखो control रेजिस्टर */
	mlxsw_pci_ग_लिखो32(mlxsw_pci, CIR_CTRL,
			  MLXSW_PCI_CIR_CTRL_GO_BIT |
			  (evreq ? MLXSW_PCI_CIR_CTRL_EVREQ_BIT : 0) |
			  (opcode_mod << MLXSW_PCI_CIR_CTRL_OPCODE_MOD_SHIFT) |
			  opcode);

	अगर (!evreq) अणु
		अचिन्हित दीर्घ end;

		end = jअगरfies + समयout;
		करो अणु
			u32 ctrl = mlxsw_pci_पढ़ो32(mlxsw_pci, CIR_CTRL);

			अगर (!(ctrl & MLXSW_PCI_CIR_CTRL_GO_BIT)) अणु
				*p_रुको_करोne = true;
				*p_status = ctrl >> MLXSW_PCI_CIR_CTRL_STATUS_SHIFT;
				अवरोध;
			पूर्ण
			cond_resched();
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));
	पूर्ण अन्यथा अणु
		रुको_event_समयout(mlxsw_pci->cmd.रुको, *p_रुको_करोne, समयout);
		*p_status = mlxsw_pci->cmd.comp.status;
	पूर्ण

	err = 0;
	अगर (*p_रुको_करोne) अणु
		अगर (*p_status)
			err = -EIO;
	पूर्ण अन्यथा अणु
		err = -ETIMEDOUT;
	पूर्ण

	अगर (!err && out_mbox && out_mbox_direct) अणु
		/* Some commands करोn't use output param as address to mailbox
		 * but they store output directly पूर्णांकo रेजिस्टरs. In that हाल,
		 * copy रेजिस्टरs पूर्णांकo mbox buffer.
		 */
		__be32 पंचांगp;

		अगर (!evreq) अणु
			पंचांगp = cpu_to_be32(mlxsw_pci_पढ़ो32(mlxsw_pci,
							   CIR_OUT_PARAM_HI));
			स_नकल(out_mbox, &पंचांगp, माप(पंचांगp));
			पंचांगp = cpu_to_be32(mlxsw_pci_पढ़ो32(mlxsw_pci,
							   CIR_OUT_PARAM_LO));
			स_नकल(out_mbox + माप(पंचांगp), &पंचांगp, माप(पंचांगp));
		पूर्ण
	पूर्ण अन्यथा अगर (!err && out_mbox) अणु
		स_नकल(out_mbox, mlxsw_pci->cmd.out_mbox.buf, out_mbox_size);
	पूर्ण

	mutex_unlock(&mlxsw_pci->cmd.lock);

	वापस err;
पूर्ण

अटल u32 mlxsw_pci_पढ़ो_frc_h(व्योम *bus_priv)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = bus_priv;
	u64 frc_offset;

	frc_offset = mlxsw_pci->मुक्त_running_घड़ी_offset;
	वापस mlxsw_pci_पढ़ो32(mlxsw_pci, FREE_RUNNING_CLOCK_H(frc_offset));
पूर्ण

अटल u32 mlxsw_pci_पढ़ो_frc_l(व्योम *bus_priv)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = bus_priv;
	u64 frc_offset;

	frc_offset = mlxsw_pci->मुक्त_running_घड़ी_offset;
	वापस mlxsw_pci_पढ़ो32(mlxsw_pci, FREE_RUNNING_CLOCK_L(frc_offset));
पूर्ण

अटल स्थिर काष्ठा mlxsw_bus mlxsw_pci_bus = अणु
	.kind			= "pci",
	.init			= mlxsw_pci_init,
	.fini			= mlxsw_pci_fini,
	.skb_transmit_busy	= mlxsw_pci_skb_transmit_busy,
	.skb_transmit		= mlxsw_pci_skb_transmit,
	.cmd_exec		= mlxsw_pci_cmd_exec,
	.पढ़ो_frc_h		= mlxsw_pci_पढ़ो_frc_h,
	.पढ़ो_frc_l		= mlxsw_pci_पढ़ो_frc_l,
	.features		= MLXSW_BUS_F_TXRX | MLXSW_BUS_F_RESET,
पूर्ण;

अटल पूर्णांक mlxsw_pci_cmd_init(काष्ठा mlxsw_pci *mlxsw_pci)
अणु
	पूर्णांक err;

	mutex_init(&mlxsw_pci->cmd.lock);
	init_रुकोqueue_head(&mlxsw_pci->cmd.रुको);

	err = mlxsw_pci_mbox_alloc(mlxsw_pci, &mlxsw_pci->cmd.in_mbox);
	अगर (err)
		जाओ err_in_mbox_alloc;

	err = mlxsw_pci_mbox_alloc(mlxsw_pci, &mlxsw_pci->cmd.out_mbox);
	अगर (err)
		जाओ err_out_mbox_alloc;

	वापस 0;

err_out_mbox_alloc:
	mlxsw_pci_mbox_मुक्त(mlxsw_pci, &mlxsw_pci->cmd.in_mbox);
err_in_mbox_alloc:
	mutex_destroy(&mlxsw_pci->cmd.lock);
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_cmd_fini(काष्ठा mlxsw_pci *mlxsw_pci)
अणु
	mlxsw_pci_mbox_मुक्त(mlxsw_pci, &mlxsw_pci->cmd.out_mbox);
	mlxsw_pci_mbox_मुक्त(mlxsw_pci, &mlxsw_pci->cmd.in_mbox);
	mutex_destroy(&mlxsw_pci->cmd.lock);
पूर्ण

अटल पूर्णांक mlxsw_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर अक्षर *driver_name = pdev->driver->name;
	काष्ठा mlxsw_pci *mlxsw_pci;
	पूर्णांक err;

	mlxsw_pci = kzalloc(माप(*mlxsw_pci), GFP_KERNEL);
	अगर (!mlxsw_pci)
		वापस -ENOMEM;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_enable_device failed\n");
		जाओ err_pci_enable_device;
	पूर्ण

	err = pci_request_regions(pdev, driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_request_regions failed\n");
		जाओ err_pci_request_regions;
	पूर्ण

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err) अणु
		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "dma_set_mask failed\n");
			जाओ err_pci_set_dma_mask;
		पूर्ण
	पूर्ण

	अगर (pci_resource_len(pdev, 0) < MLXSW_PCI_BAR0_SIZE) अणु
		dev_err(&pdev->dev, "invalid PCI region size\n");
		err = -EINVAL;
		जाओ err_pci_resource_len_check;
	पूर्ण

	mlxsw_pci->hw_addr = ioremap(pci_resource_start(pdev, 0),
				     pci_resource_len(pdev, 0));
	अगर (!mlxsw_pci->hw_addr) अणु
		dev_err(&pdev->dev, "ioremap failed\n");
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण
	pci_set_master(pdev);

	mlxsw_pci->pdev = pdev;
	pci_set_drvdata(pdev, mlxsw_pci);

	err = mlxsw_pci_cmd_init(mlxsw_pci);
	अगर (err)
		जाओ err_pci_cmd_init;

	mlxsw_pci->bus_info.device_kind = driver_name;
	mlxsw_pci->bus_info.device_name = pci_name(mlxsw_pci->pdev);
	mlxsw_pci->bus_info.dev = &pdev->dev;
	mlxsw_pci->bus_info.पढ़ो_frc_capable = true;
	mlxsw_pci->id = id;

	err = mlxsw_core_bus_device_रेजिस्टर(&mlxsw_pci->bus_info,
					     &mlxsw_pci_bus, mlxsw_pci, false,
					     शून्य, शून्य);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot register bus device\n");
		जाओ err_bus_device_रेजिस्टर;
	पूर्ण

	वापस 0;

err_bus_device_रेजिस्टर:
	mlxsw_pci_cmd_fini(mlxsw_pci);
err_pci_cmd_init:
	iounmap(mlxsw_pci->hw_addr);
err_ioremap:
err_pci_resource_len_check:
err_pci_set_dma_mask:
	pci_release_regions(pdev);
err_pci_request_regions:
	pci_disable_device(pdev);
err_pci_enable_device:
	kमुक्त(mlxsw_pci);
	वापस err;
पूर्ण

अटल व्योम mlxsw_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlxsw_pci *mlxsw_pci = pci_get_drvdata(pdev);

	mlxsw_core_bus_device_unरेजिस्टर(mlxsw_pci->core, false);
	mlxsw_pci_cmd_fini(mlxsw_pci);
	iounmap(mlxsw_pci->hw_addr);
	pci_release_regions(mlxsw_pci->pdev);
	pci_disable_device(mlxsw_pci->pdev);
	kमुक्त(mlxsw_pci);
पूर्ण

पूर्णांक mlxsw_pci_driver_रेजिस्टर(काष्ठा pci_driver *pci_driver)
अणु
	pci_driver->probe = mlxsw_pci_probe;
	pci_driver->हटाओ = mlxsw_pci_हटाओ;
	वापस pci_रेजिस्टर_driver(pci_driver);
पूर्ण
EXPORT_SYMBOL(mlxsw_pci_driver_रेजिस्टर);

व्योम mlxsw_pci_driver_unरेजिस्टर(काष्ठा pci_driver *pci_driver)
अणु
	pci_unरेजिस्टर_driver(pci_driver);
पूर्ण
EXPORT_SYMBOL(mlxsw_pci_driver_unरेजिस्टर);

अटल पूर्णांक __init mlxsw_pci_module_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास mlxsw_pci_module_निकास(व्योम)
अणु
पूर्ण

module_init(mlxsw_pci_module_init);
module_निकास(mlxsw_pci_module_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Mellanox switch PCI interface driver");
