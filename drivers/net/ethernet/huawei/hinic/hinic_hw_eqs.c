<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/barrier.h>

#समावेश "hinic_hw_dev.h"
#समावेश "hinic_hw_csr.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_eqs.h"

#घोषणा HINIC_EQS_WQ_NAME                       "hinic_eqs"

#घोषणा GET_EQ_NUM_PAGES(eq, pg_size)           \
		(ALIGN((eq)->q_len * (eq)->elem_size, pg_size) / (pg_size))

#घोषणा GET_EQ_NUM_ELEMS_IN_PG(eq, pg_size)     ((pg_size) / (eq)->elem_size)

#घोषणा EQ_CONS_IDX_REG_ADDR(eq)        (((eq)->type == HINIC_AEQ) ? \
			HINIC_CSR_AEQ_CONS_IDX_ADDR((eq)->q_id) : \
			HINIC_CSR_CEQ_CONS_IDX_ADDR((eq)->q_id))

#घोषणा EQ_PROD_IDX_REG_ADDR(eq)        (((eq)->type == HINIC_AEQ) ? \
			HINIC_CSR_AEQ_PROD_IDX_ADDR((eq)->q_id) : \
			HINIC_CSR_CEQ_PROD_IDX_ADDR((eq)->q_id))

#घोषणा EQ_HI_PHYS_ADDR_REG(eq, pg_num) (((eq)->type == HINIC_AEQ) ? \
			HINIC_CSR_AEQ_HI_PHYS_ADDR_REG((eq)->q_id, pg_num) : \
			HINIC_CSR_CEQ_HI_PHYS_ADDR_REG((eq)->q_id, pg_num))

#घोषणा EQ_LO_PHYS_ADDR_REG(eq, pg_num) (((eq)->type == HINIC_AEQ) ? \
			HINIC_CSR_AEQ_LO_PHYS_ADDR_REG((eq)->q_id, pg_num) : \
			HINIC_CSR_CEQ_LO_PHYS_ADDR_REG((eq)->q_id, pg_num))

#घोषणा GET_EQ_ELEMENT(eq, idx)         \
		((eq)->virt_addr[(idx) / (eq)->num_elem_in_pg] + \
		 (((idx) & ((eq)->num_elem_in_pg - 1)) * (eq)->elem_size))

#घोषणा GET_AEQ_ELEM(eq, idx)           ((काष्ठा hinic_aeq_elem *) \
					GET_EQ_ELEMENT(eq, idx))

#घोषणा GET_CEQ_ELEM(eq, idx)           ((u32 *) \
					 GET_EQ_ELEMENT(eq, idx))

#घोषणा GET_CURR_AEQ_ELEM(eq)           GET_AEQ_ELEM(eq, (eq)->cons_idx)

#घोषणा GET_CURR_CEQ_ELEM(eq)           GET_CEQ_ELEM(eq, (eq)->cons_idx)

#घोषणा PAGE_IN_4K(page_size)           ((page_size) >> 12)
#घोषणा EQ_SET_HW_PAGE_SIZE_VAL(eq)     (ilog2(PAGE_IN_4K((eq)->page_size)))

#घोषणा ELEMENT_SIZE_IN_32B(eq)         (((eq)->elem_size) >> 5)
#घोषणा EQ_SET_HW_ELEM_SIZE_VAL(eq)     (ilog2(ELEMENT_SIZE_IN_32B(eq)))

#घोषणा EQ_MAX_PAGES                    8

#घोषणा CEQE_TYPE_SHIFT                 23
#घोषणा CEQE_TYPE_MASK                  0x7

#घोषणा CEQE_TYPE(ceqe)                 (((ceqe) >> CEQE_TYPE_SHIFT) &  \
					 CEQE_TYPE_MASK)

#घोषणा CEQE_DATA_MASK                  0x3FFFFFF
#घोषणा CEQE_DATA(ceqe)                 ((ceqe) & CEQE_DATA_MASK)

#घोषणा aeq_to_aeqs(eq)                 \
		container_of((eq) - (eq)->q_id, काष्ठा hinic_aeqs, aeq[0])

#घोषणा ceq_to_ceqs(eq)                 \
		container_of((eq) - (eq)->q_id, काष्ठा hinic_ceqs, ceq[0])

#घोषणा work_to_aeq_work(work)          \
		container_of(work, काष्ठा hinic_eq_work, work)

#घोषणा DMA_ATTR_AEQ_DEFAULT            0
#घोषणा DMA_ATTR_CEQ_DEFAULT            0

/* No coalescence */
#घोषणा THRESH_CEQ_DEFAULT              0

क्रमागत eq_पूर्णांक_mode अणु
	EQ_INT_MODE_ARMED,
	EQ_INT_MODE_ALWAYS
पूर्ण;

क्रमागत eq_arm_state अणु
	EQ_NOT_ARMED,
	EQ_ARMED
पूर्ण;

/**
 * hinic_aeq_रेजिस्टर_hw_cb - रेजिस्टर AEQ callback क्रम specअगरic event
 * @aeqs: poपूर्णांकer to Async eqs of the chip
 * @event: aeq event to रेजिस्टर callback क्रम it
 * @handle: निजी data will be used by the callback
 * @hwe_handler: callback function
 **/
व्योम hinic_aeq_रेजिस्टर_hw_cb(काष्ठा hinic_aeqs *aeqs,
			      क्रमागत hinic_aeq_type event, व्योम *handle,
			      व्योम (*hwe_handler)(व्योम *handle, व्योम *data,
						  u8 size))
अणु
	काष्ठा hinic_hw_event_cb *hwe_cb = &aeqs->hwe_cb[event];

	hwe_cb->hwe_handler = hwe_handler;
	hwe_cb->handle = handle;
	hwe_cb->hwe_state = HINIC_EQE_ENABLED;
पूर्ण

/**
 * hinic_aeq_unरेजिस्टर_hw_cb - unरेजिस्टर the AEQ callback क्रम specअगरic event
 * @aeqs: poपूर्णांकer to Async eqs of the chip
 * @event: aeq event to unरेजिस्टर callback क्रम it
 **/
व्योम hinic_aeq_unरेजिस्टर_hw_cb(काष्ठा hinic_aeqs *aeqs,
				क्रमागत hinic_aeq_type event)
अणु
	काष्ठा hinic_hw_event_cb *hwe_cb = &aeqs->hwe_cb[event];

	hwe_cb->hwe_state &= ~HINIC_EQE_ENABLED;

	जबतक (hwe_cb->hwe_state & HINIC_EQE_RUNNING)
		schedule();

	hwe_cb->hwe_handler = शून्य;
पूर्ण

/**
 * hinic_ceq_रेजिस्टर_cb - रेजिस्टर CEQ callback क्रम specअगरic event
 * @ceqs: poपूर्णांकer to Completion eqs part of the chip
 * @event: ceq event to रेजिस्टर callback क्रम it
 * @handle: निजी data will be used by the callback
 * @handler: callback function
 **/
व्योम hinic_ceq_रेजिस्टर_cb(काष्ठा hinic_ceqs *ceqs,
			   क्रमागत hinic_ceq_type event, व्योम *handle,
			   व्योम (*handler)(व्योम *handle, u32 ceqe_data))
अणु
	काष्ठा hinic_ceq_cb *ceq_cb = &ceqs->ceq_cb[event];

	ceq_cb->handler = handler;
	ceq_cb->handle = handle;
	ceq_cb->ceqe_state = HINIC_EQE_ENABLED;
पूर्ण

/**
 * hinic_ceq_unरेजिस्टर_cb - unरेजिस्टर the CEQ callback क्रम specअगरic event
 * @ceqs: poपूर्णांकer to Completion eqs part of the chip
 * @event: ceq event to unरेजिस्टर callback क्रम it
 **/
व्योम hinic_ceq_unरेजिस्टर_cb(काष्ठा hinic_ceqs *ceqs,
			     क्रमागत hinic_ceq_type event)
अणु
	काष्ठा hinic_ceq_cb *ceq_cb = &ceqs->ceq_cb[event];

	ceq_cb->ceqe_state &= ~HINIC_EQE_ENABLED;

	जबतक (ceq_cb->ceqe_state & HINIC_EQE_RUNNING)
		schedule();

	ceq_cb->handler = शून्य;
पूर्ण

अटल u8 eq_cons_idx_checksum_set(u32 val)
अणु
	u8 checksum = 0;
	पूर्णांक idx;

	क्रम (idx = 0; idx < 32; idx += 4)
		checksum ^= ((val >> idx) & 0xF);

	वापस (checksum & 0xF);
पूर्ण

/**
 * eq_update_ci - update the HW cons idx of event queue
 * @eq: the event queue to update the cons idx क्रम
 * @arm_state: the arm bit value of eq's पूर्णांकerrupt
 **/
अटल व्योम eq_update_ci(काष्ठा hinic_eq *eq, u32 arm_state)
अणु
	u32 val, addr = EQ_CONS_IDX_REG_ADDR(eq);

	/* Read Modअगरy Write */
	val = hinic_hwअगर_पढ़ो_reg(eq->hwअगर, addr);

	val = HINIC_EQ_CI_CLEAR(val, IDX)       &
	      HINIC_EQ_CI_CLEAR(val, WRAPPED)   &
	      HINIC_EQ_CI_CLEAR(val, INT_ARMED) &
	      HINIC_EQ_CI_CLEAR(val, XOR_CHKSUM);

	val |= HINIC_EQ_CI_SET(eq->cons_idx, IDX)    |
	       HINIC_EQ_CI_SET(eq->wrapped, WRAPPED) |
	       HINIC_EQ_CI_SET(arm_state, INT_ARMED);

	val |= HINIC_EQ_CI_SET(eq_cons_idx_checksum_set(val), XOR_CHKSUM);

	hinic_hwअगर_ग_लिखो_reg(eq->hwअगर, addr, val);
पूर्ण

/**
 * aeq_irq_handler - handler क्रम the AEQ event
 * @eq: the Async Event Queue that received the event
 **/
अटल व्योम aeq_irq_handler(काष्ठा hinic_eq *eq)
अणु
	काष्ठा hinic_aeqs *aeqs = aeq_to_aeqs(eq);
	काष्ठा hinic_hwअगर *hwअगर = aeqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_aeq_elem *aeqe_curr;
	काष्ठा hinic_hw_event_cb *hwe_cb;
	क्रमागत hinic_aeq_type event;
	अचिन्हित दीर्घ eqe_state;
	u32 aeqe_desc;
	पूर्णांक i, size;

	क्रम (i = 0; i < eq->q_len; i++) अणु
		aeqe_curr = GET_CURR_AEQ_ELEM(eq);

		/* Data in HW is in Big endian Format */
		aeqe_desc = be32_to_cpu(aeqe_curr->desc);

		/* HW toggles the wrapped bit, when it adds eq element */
		अगर (HINIC_EQ_ELEM_DESC_GET(aeqe_desc, WRAPPED) == eq->wrapped)
			अवरोध;

		dma_rmb();

		event = HINIC_EQ_ELEM_DESC_GET(aeqe_desc, TYPE);
		अगर (event >= HINIC_MAX_AEQ_EVENTS) अणु
			dev_err(&pdev->dev, "Unknown AEQ Event %d\n", event);
			वापस;
		पूर्ण

		अगर (!HINIC_EQ_ELEM_DESC_GET(aeqe_desc, SRC)) अणु
			hwe_cb = &aeqs->hwe_cb[event];

			size = HINIC_EQ_ELEM_DESC_GET(aeqe_desc, SIZE);

			eqe_state = cmpxchg(&hwe_cb->hwe_state,
					    HINIC_EQE_ENABLED,
					    HINIC_EQE_ENABLED |
					    HINIC_EQE_RUNNING);
			अगर ((eqe_state == HINIC_EQE_ENABLED) &&
			    (hwe_cb->hwe_handler))
				hwe_cb->hwe_handler(hwe_cb->handle,
						    aeqe_curr->data, size);
			अन्यथा
				dev_err(&pdev->dev, "Unhandled AEQ Event %d\n",
					event);

			hwe_cb->hwe_state &= ~HINIC_EQE_RUNNING;
		पूर्ण

		eq->cons_idx++;

		अगर (eq->cons_idx == eq->q_len) अणु
			eq->cons_idx = 0;
			eq->wrapped = !eq->wrapped;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ceq_event_handler - handler क्रम the ceq events
 * @ceqs: ceqs part of the chip
 * @ceqe: ceq element that describes the event
 **/
अटल व्योम ceq_event_handler(काष्ठा hinic_ceqs *ceqs, u32 ceqe)
अणु
	काष्ठा hinic_hwअगर *hwअगर = ceqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	काष्ठा hinic_ceq_cb *ceq_cb;
	क्रमागत hinic_ceq_type event;
	अचिन्हित दीर्घ eqe_state;

	event = CEQE_TYPE(ceqe);
	अगर (event >= HINIC_MAX_CEQ_EVENTS) अणु
		dev_err(&pdev->dev, "Unknown CEQ event, event = %d\n", event);
		वापस;
	पूर्ण

	ceq_cb = &ceqs->ceq_cb[event];

	eqe_state = cmpxchg(&ceq_cb->ceqe_state,
			    HINIC_EQE_ENABLED,
			    HINIC_EQE_ENABLED | HINIC_EQE_RUNNING);

	अगर ((eqe_state == HINIC_EQE_ENABLED) && (ceq_cb->handler))
		ceq_cb->handler(ceq_cb->handle, CEQE_DATA(ceqe));
	अन्यथा
		dev_err(&pdev->dev, "Unhandled CEQ Event %d\n", event);

	ceq_cb->ceqe_state &= ~HINIC_EQE_RUNNING;
पूर्ण

/**
 * ceq_irq_handler - handler क्रम the CEQ event
 * @eq: the Completion Event Queue that received the event
 **/
अटल व्योम ceq_irq_handler(काष्ठा hinic_eq *eq)
अणु
	काष्ठा hinic_ceqs *ceqs = ceq_to_ceqs(eq);
	u32 ceqe;
	पूर्णांक i;

	क्रम (i = 0; i < eq->q_len; i++) अणु
		ceqe = *(GET_CURR_CEQ_ELEM(eq));

		/* Data in HW is in Big endian Format */
		ceqe = be32_to_cpu(ceqe);

		/* HW toggles the wrapped bit, when it adds eq element event */
		अगर (HINIC_EQ_ELEM_DESC_GET(ceqe, WRAPPED) == eq->wrapped)
			अवरोध;

		ceq_event_handler(ceqs, ceqe);

		eq->cons_idx++;

		अगर (eq->cons_idx == eq->q_len) अणु
			eq->cons_idx = 0;
			eq->wrapped = !eq->wrapped;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * eq_irq_handler - handler क्रम the EQ event
 * @data: the Event Queue that received the event
 **/
अटल व्योम eq_irq_handler(व्योम *data)
अणु
	काष्ठा hinic_eq *eq = data;

	अगर (eq->type == HINIC_AEQ)
		aeq_irq_handler(eq);
	अन्यथा अगर (eq->type == HINIC_CEQ)
		ceq_irq_handler(eq);

	eq_update_ci(eq, EQ_ARMED);
पूर्ण

/**
 * eq_irq_work - the work of the EQ that received the event
 * @work: the work काष्ठा that is associated with the EQ
 **/
अटल व्योम eq_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hinic_eq_work *aeq_work = work_to_aeq_work(work);
	काष्ठा hinic_eq *aeq;

	aeq = aeq_work->data;
	eq_irq_handler(aeq);
पूर्ण

/**
 * ceq_tasklet - the tasklet of the EQ that received the event
 * @t: the tasklet काष्ठा poपूर्णांकer
 **/
अटल व्योम ceq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा hinic_eq *ceq = from_tasklet(ceq, t, ceq_tasklet);

	eq_irq_handler(ceq);
पूर्ण

/**
 * aeq_पूर्णांकerrupt - aeq पूर्णांकerrupt handler
 * @irq: irq number
 * @data: the Async Event Queue that collected the event
 **/
अटल irqवापस_t aeq_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hinic_eq_work *aeq_work;
	काष्ठा hinic_eq *aeq = data;
	काष्ठा hinic_aeqs *aeqs;

	/* clear resend समयr cnt रेजिस्टर */
	hinic_msix_attr_cnt_clear(aeq->hwअगर, aeq->msix_entry.entry);

	aeq_work = &aeq->aeq_work;
	aeq_work->data = aeq;

	aeqs = aeq_to_aeqs(aeq);
	queue_work(aeqs->workq, &aeq_work->work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ceq_पूर्णांकerrupt - ceq पूर्णांकerrupt handler
 * @irq: irq number
 * @data: the Completion Event Queue that collected the event
 **/
अटल irqवापस_t ceq_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hinic_eq *ceq = data;

	/* clear resend समयr cnt रेजिस्टर */
	hinic_msix_attr_cnt_clear(ceq->hwअगर, ceq->msix_entry.entry);

	tasklet_schedule(&ceq->ceq_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 get_ctrl0_val(काष्ठा hinic_eq *eq, u32 addr)
अणु
	काष्ठा msix_entry *msix_entry = &eq->msix_entry;
	क्रमागत hinic_eq_type type = eq->type;
	u32 val, ctrl0;

	अगर (type == HINIC_AEQ) अणु
		/* RMW Ctrl0 */
		addr = HINIC_CSR_AEQ_CTRL_0_ADDR(eq->q_id);

		val = hinic_hwअगर_पढ़ो_reg(eq->hwअगर, addr);

		val = HINIC_AEQ_CTRL_0_CLEAR(val, INT_IDX)      &
		      HINIC_AEQ_CTRL_0_CLEAR(val, DMA_ATTR)     &
		      HINIC_AEQ_CTRL_0_CLEAR(val, PCI_INTF_IDX) &
		      HINIC_AEQ_CTRL_0_CLEAR(val, INT_MODE);

		ctrl0 = HINIC_AEQ_CTRL_0_SET(msix_entry->entry, INT_IDX)     |
			HINIC_AEQ_CTRL_0_SET(DMA_ATTR_AEQ_DEFAULT, DMA_ATTR) |
			HINIC_AEQ_CTRL_0_SET(HINIC_HWIF_PCI_INTF(eq->hwअगर),
					     PCI_INTF_IDX)                   |
			HINIC_AEQ_CTRL_0_SET(EQ_INT_MODE_ARMED, INT_MODE);

		val |= ctrl0;
	पूर्ण अन्यथा अणु
		/* RMW Ctrl0 */
		addr = HINIC_CSR_CEQ_CTRL_0_ADDR(eq->q_id);

		val = hinic_hwअगर_पढ़ो_reg(eq->hwअगर, addr);

		val = HINIC_CEQ_CTRL_0_CLEAR(val, INTR_IDX)     &
		      HINIC_CEQ_CTRL_0_CLEAR(val, DMA_ATTR)     &
		      HINIC_CEQ_CTRL_0_CLEAR(val, KICK_THRESH)  &
		      HINIC_CEQ_CTRL_0_CLEAR(val, PCI_INTF_IDX) &
		      HINIC_CEQ_CTRL_0_CLEAR(val, INTR_MODE);

		ctrl0 = HINIC_CEQ_CTRL_0_SET(msix_entry->entry, INTR_IDX)     |
			HINIC_CEQ_CTRL_0_SET(DMA_ATTR_CEQ_DEFAULT, DMA_ATTR)  |
			HINIC_CEQ_CTRL_0_SET(THRESH_CEQ_DEFAULT, KICK_THRESH) |
			HINIC_CEQ_CTRL_0_SET(HINIC_HWIF_PCI_INTF(eq->hwअगर),
					     PCI_INTF_IDX)                    |
			HINIC_CEQ_CTRL_0_SET(EQ_INT_MODE_ARMED, INTR_MODE);

		val |= ctrl0;
	पूर्ण
	वापस val;
पूर्ण

अटल व्योम set_ctrl0(काष्ठा hinic_eq *eq)
अणु
	u32 val, addr;

	अगर (eq->type == HINIC_AEQ)
		addr = HINIC_CSR_AEQ_CTRL_0_ADDR(eq->q_id);
	अन्यथा
		addr = HINIC_CSR_CEQ_CTRL_0_ADDR(eq->q_id);

	val = get_ctrl0_val(eq, addr);

	hinic_hwअगर_ग_लिखो_reg(eq->hwअगर, addr, val);
पूर्ण

अटल u32 get_ctrl1_val(काष्ठा hinic_eq *eq, u32 addr)
अणु
	u32 page_size_val, elem_size, val, ctrl1;
	क्रमागत hinic_eq_type type = eq->type;

	अगर (type == HINIC_AEQ) अणु
		/* RMW Ctrl1 */
		addr = HINIC_CSR_AEQ_CTRL_1_ADDR(eq->q_id);

		page_size_val = EQ_SET_HW_PAGE_SIZE_VAL(eq);
		elem_size = EQ_SET_HW_ELEM_SIZE_VAL(eq);

		val = hinic_hwअगर_पढ़ो_reg(eq->hwअगर, addr);

		val = HINIC_AEQ_CTRL_1_CLEAR(val, LEN)          &
		      HINIC_AEQ_CTRL_1_CLEAR(val, ELEM_SIZE)    &
		      HINIC_AEQ_CTRL_1_CLEAR(val, PAGE_SIZE);

		ctrl1 = HINIC_AEQ_CTRL_1_SET(eq->q_len, LEN)            |
			HINIC_AEQ_CTRL_1_SET(elem_size, ELEM_SIZE)      |
			HINIC_AEQ_CTRL_1_SET(page_size_val, PAGE_SIZE);

		val |= ctrl1;
	पूर्ण अन्यथा अणु
		/* RMW Ctrl1 */
		addr = HINIC_CSR_CEQ_CTRL_1_ADDR(eq->q_id);

		page_size_val = EQ_SET_HW_PAGE_SIZE_VAL(eq);

		val = hinic_hwअगर_पढ़ो_reg(eq->hwअगर, addr);

		val = HINIC_CEQ_CTRL_1_CLEAR(val, LEN) &
		      HINIC_CEQ_CTRL_1_CLEAR(val, PAGE_SIZE);

		ctrl1 = HINIC_CEQ_CTRL_1_SET(eq->q_len, LEN) |
			HINIC_CEQ_CTRL_1_SET(page_size_val, PAGE_SIZE);

		val |= ctrl1;
	पूर्ण
	वापस val;
पूर्ण

अटल व्योम set_ctrl1(काष्ठा hinic_eq *eq)
अणु
	u32 addr, val;

	अगर (eq->type == HINIC_AEQ)
		addr = HINIC_CSR_AEQ_CTRL_1_ADDR(eq->q_id);
	अन्यथा
		addr = HINIC_CSR_CEQ_CTRL_1_ADDR(eq->q_id);

	val = get_ctrl1_val(eq, addr);

	hinic_hwअगर_ग_लिखो_reg(eq->hwअगर, addr, val);
पूर्ण

अटल पूर्णांक set_ceq_ctrl_reg(काष्ठा hinic_eq *eq)
अणु
	काष्ठा hinic_ceq_ctrl_reg ceq_ctrl = अणु0पूर्ण;
	काष्ठा hinic_hwdev *hwdev = eq->hwdev;
	u16 out_size = माप(ceq_ctrl);
	u16 in_size = माप(ceq_ctrl);
	काष्ठा hinic_pfhwdev *pfhwdev;
	u32 addr;
	पूर्णांक err;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	addr = HINIC_CSR_CEQ_CTRL_0_ADDR(eq->q_id);
	ceq_ctrl.ctrl0 = get_ctrl0_val(eq, addr);
	addr = HINIC_CSR_CEQ_CTRL_1_ADDR(eq->q_id);
	ceq_ctrl.ctrl1 = get_ctrl1_val(eq, addr);

	ceq_ctrl.func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	ceq_ctrl.q_id = eq->q_id;

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_CEQ_CTRL_REG_WR_BY_UP,
				&ceq_ctrl, in_size,
				&ceq_ctrl, &out_size, HINIC_MGMT_MSG_SYNC);
	अगर (err || !out_size || ceq_ctrl.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to set ceq %d ctrl reg, err: %d status: 0x%x, out_size: 0x%x\n",
			eq->q_id, err, ceq_ctrl.status, out_size);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * set_eq_ctrls - setting eq's ctrl रेजिस्टरs
 * @eq: the Event Queue क्रम setting
 **/
अटल पूर्णांक set_eq_ctrls(काष्ठा hinic_eq *eq)
अणु
	अगर (HINIC_IS_VF(eq->hwअगर) && eq->type == HINIC_CEQ)
		वापस set_ceq_ctrl_reg(eq);

	set_ctrl0(eq);
	set_ctrl1(eq);
	वापस 0;
पूर्ण

/**
 * aeq_elements_init - initialize all the elements in the aeq
 * @eq: the Async Event Queue
 * @init_val: value to initialize the elements with it
 **/
अटल व्योम aeq_elements_init(काष्ठा hinic_eq *eq, u32 init_val)
अणु
	काष्ठा hinic_aeq_elem *aeqe;
	पूर्णांक i;

	क्रम (i = 0; i < eq->q_len; i++) अणु
		aeqe = GET_AEQ_ELEM(eq, i);
		aeqe->desc = cpu_to_be32(init_val);
	पूर्ण

	wmb();  /* Write the initilzation values */
पूर्ण

/**
 * ceq_elements_init - Initialize all the elements in the ceq
 * @eq: the event queue
 * @init_val: value to init with it the elements
 **/
अटल व्योम ceq_elements_init(काष्ठा hinic_eq *eq, u32 init_val)
अणु
	u32 *ceqe;
	पूर्णांक i;

	क्रम (i = 0; i < eq->q_len; i++) अणु
		ceqe = GET_CEQ_ELEM(eq, i);
		*(ceqe) = cpu_to_be32(init_val);
	पूर्ण

	wmb();  /* Write the initilzation values */
पूर्ण

/**
 * alloc_eq_pages - allocate the pages क्रम the queue
 * @eq: the event queue
 *
 * Return 0 - Success, Negative - Failure
 **/
अटल पूर्णांक alloc_eq_pages(काष्ठा hinic_eq *eq)
अणु
	काष्ठा hinic_hwअगर *hwअगर = eq->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u32 init_val, addr, val;
	माप_प्रकार addr_size;
	पूर्णांक err, pg;

	addr_size = eq->num_pages * माप(*eq->dma_addr);
	eq->dma_addr = devm_kzalloc(&pdev->dev, addr_size, GFP_KERNEL);
	अगर (!eq->dma_addr)
		वापस -ENOMEM;

	addr_size = eq->num_pages * माप(*eq->virt_addr);
	eq->virt_addr = devm_kzalloc(&pdev->dev, addr_size, GFP_KERNEL);
	अगर (!eq->virt_addr) अणु
		err = -ENOMEM;
		जाओ err_virt_addr_alloc;
	पूर्ण

	क्रम (pg = 0; pg < eq->num_pages; pg++) अणु
		eq->virt_addr[pg] = dma_alloc_coherent(&pdev->dev,
						       eq->page_size,
						       &eq->dma_addr[pg],
						       GFP_KERNEL);
		अगर (!eq->virt_addr[pg]) अणु
			err = -ENOMEM;
			जाओ err_dma_alloc;
		पूर्ण

		addr = EQ_HI_PHYS_ADDR_REG(eq, pg);
		val = upper_32_bits(eq->dma_addr[pg]);

		hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);

		addr = EQ_LO_PHYS_ADDR_REG(eq, pg);
		val = lower_32_bits(eq->dma_addr[pg]);

		hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);
	पूर्ण

	init_val = HINIC_EQ_ELEM_DESC_SET(eq->wrapped, WRAPPED);

	अगर (eq->type == HINIC_AEQ)
		aeq_elements_init(eq, init_val);
	अन्यथा अगर (eq->type == HINIC_CEQ)
		ceq_elements_init(eq, init_val);

	वापस 0;

err_dma_alloc:
	जबतक (--pg >= 0)
		dma_मुक्त_coherent(&pdev->dev, eq->page_size,
				  eq->virt_addr[pg],
				  eq->dma_addr[pg]);

	devm_kमुक्त(&pdev->dev, eq->virt_addr);

err_virt_addr_alloc:
	devm_kमुक्त(&pdev->dev, eq->dma_addr);
	वापस err;
पूर्ण

/**
 * मुक्त_eq_pages - मुक्त the pages of the queue
 * @eq: the Event Queue
 **/
अटल व्योम मुक्त_eq_pages(काष्ठा hinic_eq *eq)
अणु
	काष्ठा hinic_hwअगर *hwअगर = eq->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक pg;

	क्रम (pg = 0; pg < eq->num_pages; pg++)
		dma_मुक्त_coherent(&pdev->dev, eq->page_size,
				  eq->virt_addr[pg],
				  eq->dma_addr[pg]);

	devm_kमुक्त(&pdev->dev, eq->virt_addr);
	devm_kमुक्त(&pdev->dev, eq->dma_addr);
पूर्ण

/**
 * init_eq - initialize Event Queue
 * @eq: the event queue
 * @hwअगर: the HW पूर्णांकerface of a PCI function device
 * @type: the type of the event queue, aeq or ceq
 * @q_id: Queue id number
 * @q_len: the number of EQ elements
 * @page_size: the page size of the pages in the event queue
 * @entry: msix entry associated with the event queue
 *
 * Return 0 - Success, Negative - Failure
 **/
अटल पूर्णांक init_eq(काष्ठा hinic_eq *eq, काष्ठा hinic_hwअगर *hwअगर,
		   क्रमागत hinic_eq_type type, पूर्णांक q_id, u32 q_len, u32 page_size,
		   काष्ठा msix_entry entry)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	eq->hwअगर = hwअगर;
	eq->type = type;
	eq->q_id = q_id;
	eq->q_len = q_len;
	eq->page_size = page_size;

	/* Clear PI and CI, also clear the ARM bit */
	hinic_hwअगर_ग_लिखो_reg(eq->hwअगर, EQ_CONS_IDX_REG_ADDR(eq), 0);
	hinic_hwअगर_ग_लिखो_reg(eq->hwअगर, EQ_PROD_IDX_REG_ADDR(eq), 0);

	eq->cons_idx = 0;
	eq->wrapped = 0;

	अगर (type == HINIC_AEQ) अणु
		eq->elem_size = HINIC_AEQE_SIZE;
	पूर्ण अन्यथा अगर (type == HINIC_CEQ) अणु
		eq->elem_size = HINIC_CEQE_SIZE;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Invalid EQ type\n");
		वापस -EINVAL;
	पूर्ण

	eq->num_pages = GET_EQ_NUM_PAGES(eq, page_size);
	eq->num_elem_in_pg = GET_EQ_NUM_ELEMS_IN_PG(eq, page_size);

	eq->msix_entry = entry;

	अगर (eq->num_elem_in_pg & (eq->num_elem_in_pg - 1)) अणु
		dev_err(&pdev->dev, "num elements in eq page != power of 2\n");
		वापस -EINVAL;
	पूर्ण

	अगर (eq->num_pages > EQ_MAX_PAGES) अणु
		dev_err(&pdev->dev, "too many pages for eq\n");
		वापस -EINVAL;
	पूर्ण

	err = set_eq_ctrls(eq);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to set eq ctrls\n");
		वापस err;
	पूर्ण

	eq_update_ci(eq, EQ_ARMED);

	err = alloc_eq_pages(eq);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate pages for eq\n");
		वापस err;
	पूर्ण

	अगर (type == HINIC_AEQ) अणु
		काष्ठा hinic_eq_work *aeq_work = &eq->aeq_work;

		INIT_WORK(&aeq_work->work, eq_irq_work);
	पूर्ण अन्यथा अगर (type == HINIC_CEQ) अणु
		tasklet_setup(&eq->ceq_tasklet, ceq_tasklet);
	पूर्ण

	/* set the attributes of the msix entry */
	hinic_msix_attr_set(eq->hwअगर, eq->msix_entry.entry,
			    HINIC_EQ_MSIX_PENDING_LIMIT_DEFAULT,
			    HINIC_EQ_MSIX_COALESC_TIMER_DEFAULT,
			    HINIC_EQ_MSIX_LLI_TIMER_DEFAULT,
			    HINIC_EQ_MSIX_LLI_CREDIT_LIMIT_DEFAULT,
			    HINIC_EQ_MSIX_RESEND_TIMER_DEFAULT);

	अगर (type == HINIC_AEQ) अणु
		snम_लिखो(eq->irq_name, माप(eq->irq_name), "hinic_aeq%d@pci:%s", eq->q_id,
			 pci_name(pdev));
		err = request_irq(entry.vector, aeq_पूर्णांकerrupt, 0, eq->irq_name, eq);
	पूर्ण अन्यथा अगर (type == HINIC_CEQ) अणु
		snम_लिखो(eq->irq_name, माप(eq->irq_name), "hinic_ceq%d@pci:%s", eq->q_id,
			 pci_name(pdev));
		err = request_irq(entry.vector, ceq_पूर्णांकerrupt, 0, eq->irq_name, eq);
	पूर्ण

	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request irq for the EQ\n");
		जाओ err_req_irq;
	पूर्ण

	वापस 0;

err_req_irq:
	मुक्त_eq_pages(eq);
	वापस err;
पूर्ण

/**
 * हटाओ_eq - हटाओ Event Queue
 * @eq: the event queue
 **/
अटल व्योम हटाओ_eq(काष्ठा hinic_eq *eq)
अणु
	hinic_set_msix_state(eq->hwअगर, eq->msix_entry.entry,
			     HINIC_MSIX_DISABLE);
	मुक्त_irq(eq->msix_entry.vector, eq);

	अगर (eq->type == HINIC_AEQ) अणु
		काष्ठा hinic_eq_work *aeq_work = &eq->aeq_work;

		cancel_work_sync(&aeq_work->work);
		/* clear aeq_len to aव्योम hw access host memory */
		hinic_hwअगर_ग_लिखो_reg(eq->hwअगर,
				     HINIC_CSR_AEQ_CTRL_1_ADDR(eq->q_id), 0);
	पूर्ण अन्यथा अगर (eq->type == HINIC_CEQ) अणु
		tasklet_समाप्त(&eq->ceq_tasklet);
		/* clear ceq_len to aव्योम hw access host memory */
		hinic_hwअगर_ग_लिखो_reg(eq->hwअगर,
				     HINIC_CSR_CEQ_CTRL_1_ADDR(eq->q_id), 0);
	पूर्ण

	/* update cons_idx to aव्योम invalid पूर्णांकerrupt */
	eq->cons_idx = hinic_hwअगर_पढ़ो_reg(eq->hwअगर, EQ_PROD_IDX_REG_ADDR(eq));
	eq_update_ci(eq, EQ_NOT_ARMED);

	मुक्त_eq_pages(eq);
पूर्ण

/**
 * hinic_aeqs_init - initialize all the aeqs
 * @aeqs: poपूर्णांकer to Async eqs of the chip
 * @hwअगर: the HW पूर्णांकerface of a PCI function device
 * @num_aeqs: number of AEQs
 * @q_len: number of EQ elements
 * @page_size: the page size of the pages in the event queue
 * @msix_entries: msix entries associated with the event queues
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_aeqs_init(काष्ठा hinic_aeqs *aeqs, काष्ठा hinic_hwअगर *hwअगर,
		    पूर्णांक num_aeqs, u32 q_len, u32 page_size,
		    काष्ठा msix_entry *msix_entries)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err, i, q_id;

	aeqs->workq = create_singlethपढ़ो_workqueue(HINIC_EQS_WQ_NAME);
	अगर (!aeqs->workq)
		वापस -ENOMEM;

	aeqs->hwअगर = hwअगर;
	aeqs->num_aeqs = num_aeqs;

	क्रम (q_id = 0; q_id < num_aeqs; q_id++) अणु
		err = init_eq(&aeqs->aeq[q_id], hwअगर, HINIC_AEQ, q_id, q_len,
			      page_size, msix_entries[q_id]);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to init aeq %d\n", q_id);
			जाओ err_init_aeq;
		पूर्ण
	पूर्ण

	वापस 0;

err_init_aeq:
	क्रम (i = 0; i < q_id; i++)
		हटाओ_eq(&aeqs->aeq[i]);

	destroy_workqueue(aeqs->workq);
	वापस err;
पूर्ण

/**
 * hinic_aeqs_मुक्त - मुक्त all the aeqs
 * @aeqs: poपूर्णांकer to Async eqs of the chip
 **/
व्योम hinic_aeqs_मुक्त(काष्ठा hinic_aeqs *aeqs)
अणु
	पूर्णांक q_id;

	क्रम (q_id = 0; q_id < aeqs->num_aeqs ; q_id++)
		हटाओ_eq(&aeqs->aeq[q_id]);

	destroy_workqueue(aeqs->workq);
पूर्ण

/**
 * hinic_ceqs_init - init all the ceqs
 * @ceqs: ceqs part of the chip
 * @hwअगर: the hardware पूर्णांकerface of a pci function device
 * @num_ceqs: number of CEQs
 * @q_len: number of EQ elements
 * @page_size: the page size of the event queue
 * @msix_entries: msix entries associated with the event queues
 *
 * Return 0 - Success, Negative - Failure
 **/
पूर्णांक hinic_ceqs_init(काष्ठा hinic_ceqs *ceqs, काष्ठा hinic_hwअगर *hwअगर,
		    पूर्णांक num_ceqs, u32 q_len, u32 page_size,
		    काष्ठा msix_entry *msix_entries)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक i, q_id, err;

	ceqs->hwअगर = hwअगर;
	ceqs->num_ceqs = num_ceqs;

	क्रम (q_id = 0; q_id < num_ceqs; q_id++) अणु
		ceqs->ceq[q_id].hwdev = ceqs->hwdev;
		err = init_eq(&ceqs->ceq[q_id], hwअगर, HINIC_CEQ, q_id, q_len,
			      page_size, msix_entries[q_id]);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to init ceq %d\n", q_id);
			जाओ err_init_ceq;
		पूर्ण
	पूर्ण

	वापस 0;

err_init_ceq:
	क्रम (i = 0; i < q_id; i++)
		हटाओ_eq(&ceqs->ceq[i]);

	वापस err;
पूर्ण

/**
 * hinic_ceqs_मुक्त - मुक्त all the ceqs
 * @ceqs: ceqs part of the chip
 **/
व्योम hinic_ceqs_मुक्त(काष्ठा hinic_ceqs *ceqs)
अणु
	पूर्णांक q_id;

	क्रम (q_id = 0; q_id < ceqs->num_ceqs; q_id++)
		हटाओ_eq(&ceqs->ceq[q_id]);
पूर्ण

व्योम hinic_dump_ceq_info(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_eq *eq = शून्य;
	u32 addr, ci, pi;
	पूर्णांक q_id;

	क्रम (q_id = 0; q_id < hwdev->func_to_io.ceqs.num_ceqs; q_id++) अणु
		eq = &hwdev->func_to_io.ceqs.ceq[q_id];
		addr = EQ_CONS_IDX_REG_ADDR(eq);
		ci = hinic_hwअगर_पढ़ो_reg(hwdev->hwअगर, addr);
		addr = EQ_PROD_IDX_REG_ADDR(eq);
		pi = hinic_hwअगर_पढ़ो_reg(hwdev->hwअगर, addr);
		dev_err(&hwdev->hwअगर->pdev->dev, "Ceq id: %d, ci: 0x%08x, sw_ci: 0x%08x, pi: 0x%x, tasklet_state: 0x%lx, wrap: %d, ceqe: 0x%x\n",
			q_id, ci, eq->cons_idx, pi,
			eq->ceq_tasklet.state,
			eq->wrapped, be32_to_cpu(*(__be32 *)(GET_CURR_CEQ_ELEM(eq))));
	पूर्ण
पूर्ण

व्योम hinic_dump_aeq_info(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_aeq_elem *aeqe_pos = शून्य;
	काष्ठा hinic_eq *eq = शून्य;
	u32 addr, ci, pi;
	पूर्णांक q_id;

	क्रम (q_id = 0; q_id < hwdev->aeqs.num_aeqs; q_id++) अणु
		eq = &hwdev->aeqs.aeq[q_id];
		addr = EQ_CONS_IDX_REG_ADDR(eq);
		ci = hinic_hwअगर_पढ़ो_reg(hwdev->hwअगर, addr);
		addr = EQ_PROD_IDX_REG_ADDR(eq);
		pi = hinic_hwअगर_पढ़ो_reg(hwdev->hwअगर, addr);
		aeqe_pos = GET_CURR_AEQ_ELEM(eq);
		dev_err(&hwdev->hwअगर->pdev->dev, "Aeq id: %d, ci: 0x%08x, pi: 0x%x, work_state: 0x%x, wrap: %d, desc: 0x%x\n",
			q_id, ci, pi, work_busy(&eq->aeq_work.work),
			eq->wrapped, be32_to_cpu(aeqe_pos->desc));
	पूर्ण
पूर्ण
