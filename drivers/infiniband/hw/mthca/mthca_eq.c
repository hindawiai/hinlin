<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"
#समावेश "mthca_config_reg.h"

क्रमागत अणु
	MTHCA_NUM_ASYNC_EQE = 0x80,
	MTHCA_NUM_CMD_EQE   = 0x80,
	MTHCA_NUM_SPARE_EQE = 0x80,
	MTHCA_EQ_ENTRY_SIZE = 0x20
पूर्ण;

/*
 * Must be packed because start is 64 bits but only aligned to 32 bits.
 */
काष्ठा mthca_eq_context अणु
	__be32 flags;
	__be64 start;
	__be32 logsize_usrpage;
	__be32 tavor_pd;	/* reserved क्रम Arbel */
	u8     reserved1[3];
	u8     पूर्णांकr;
	__be32 arbel_pd;	/* lost_count क्रम Tavor */
	__be32 lkey;
	u32    reserved2[2];
	__be32 consumer_index;
	__be32 producer_index;
	u32    reserved3[4];
पूर्ण __packed;

#घोषणा MTHCA_EQ_STATUS_OK          ( 0 << 28)
#घोषणा MTHCA_EQ_STATUS_OVERFLOW    ( 9 << 28)
#घोषणा MTHCA_EQ_STATUS_WRITE_FAIL  (10 << 28)
#घोषणा MTHCA_EQ_OWNER_SW           ( 0 << 24)
#घोषणा MTHCA_EQ_OWNER_HW           ( 1 << 24)
#घोषणा MTHCA_EQ_FLAG_TR            ( 1 << 18)
#घोषणा MTHCA_EQ_FLAG_OI            ( 1 << 17)
#घोषणा MTHCA_EQ_STATE_ARMED        ( 1 <<  8)
#घोषणा MTHCA_EQ_STATE_FIRED        ( 2 <<  8)
#घोषणा MTHCA_EQ_STATE_ALWAYS_ARMED ( 3 <<  8)
#घोषणा MTHCA_EQ_STATE_ARBEL        ( 8 <<  8)

क्रमागत अणु
	MTHCA_EVENT_TYPE_COMP       	    = 0x00,
	MTHCA_EVENT_TYPE_PATH_MIG   	    = 0x01,
	MTHCA_EVENT_TYPE_COMM_EST   	    = 0x02,
	MTHCA_EVENT_TYPE_SQ_DRAINED 	    = 0x03,
	MTHCA_EVENT_TYPE_SRQ_QP_LAST_WQE    = 0x13,
	MTHCA_EVENT_TYPE_SRQ_LIMIT	    = 0x14,
	MTHCA_EVENT_TYPE_CQ_ERROR   	    = 0x04,
	MTHCA_EVENT_TYPE_WQ_CATAS_ERROR     = 0x05,
	MTHCA_EVENT_TYPE_EEC_CATAS_ERROR    = 0x06,
	MTHCA_EVENT_TYPE_PATH_MIG_FAILED    = 0x07,
	MTHCA_EVENT_TYPE_WQ_INVAL_REQ_ERROR = 0x10,
	MTHCA_EVENT_TYPE_WQ_ACCESS_ERROR    = 0x11,
	MTHCA_EVENT_TYPE_SRQ_CATAS_ERROR    = 0x12,
	MTHCA_EVENT_TYPE_LOCAL_CATAS_ERROR  = 0x08,
	MTHCA_EVENT_TYPE_PORT_CHANGE        = 0x09,
	MTHCA_EVENT_TYPE_EQ_OVERFLOW        = 0x0f,
	MTHCA_EVENT_TYPE_ECC_DETECT         = 0x0e,
	MTHCA_EVENT_TYPE_CMD                = 0x0a
पूर्ण;

#घोषणा MTHCA_ASYNC_EVENT_MASK ((1ULL << MTHCA_EVENT_TYPE_PATH_MIG)           | \
				(1ULL << MTHCA_EVENT_TYPE_COMM_EST)           | \
				(1ULL << MTHCA_EVENT_TYPE_SQ_DRAINED)         | \
				(1ULL << MTHCA_EVENT_TYPE_CQ_ERROR)           | \
				(1ULL << MTHCA_EVENT_TYPE_WQ_CATAS_ERROR)     | \
				(1ULL << MTHCA_EVENT_TYPE_EEC_CATAS_ERROR)    | \
				(1ULL << MTHCA_EVENT_TYPE_PATH_MIG_FAILED)    | \
				(1ULL << MTHCA_EVENT_TYPE_WQ_INVAL_REQ_ERROR) | \
				(1ULL << MTHCA_EVENT_TYPE_WQ_ACCESS_ERROR)    | \
				(1ULL << MTHCA_EVENT_TYPE_LOCAL_CATAS_ERROR)  | \
				(1ULL << MTHCA_EVENT_TYPE_PORT_CHANGE)        | \
				(1ULL << MTHCA_EVENT_TYPE_ECC_DETECT))
#घोषणा MTHCA_SRQ_EVENT_MASK   ((1ULL << MTHCA_EVENT_TYPE_SRQ_CATAS_ERROR)    | \
				(1ULL << MTHCA_EVENT_TYPE_SRQ_QP_LAST_WQE)    | \
				(1ULL << MTHCA_EVENT_TYPE_SRQ_LIMIT))
#घोषणा MTHCA_CMD_EVENT_MASK    (1ULL << MTHCA_EVENT_TYPE_CMD)

#घोषणा MTHCA_EQ_DB_INC_CI     (1 << 24)
#घोषणा MTHCA_EQ_DB_REQ_NOT    (2 << 24)
#घोषणा MTHCA_EQ_DB_DISARM_CQ  (3 << 24)
#घोषणा MTHCA_EQ_DB_SET_CI     (4 << 24)
#घोषणा MTHCA_EQ_DB_ALWAYS_ARM (5 << 24)

काष्ठा mthca_eqe अणु
	u8 reserved1;
	u8 type;
	u8 reserved2;
	u8 subtype;
	जोड़ अणु
		u32 raw[6];
		काष्ठा अणु
			__be32 cqn;
		पूर्ण __packed comp;
		काष्ठा अणु
			u16    reserved1;
			__be16 token;
			u32    reserved2;
			u8     reserved3[3];
			u8     status;
			__be64 out_param;
		पूर्ण __packed cmd;
		काष्ठा अणु
			__be32 qpn;
		पूर्ण __packed qp;
		काष्ठा अणु
			__be32 srqn;
		पूर्ण __packed srq;
		काष्ठा अणु
			__be32 cqn;
			u32    reserved1;
			u8     reserved2[3];
			u8     syndrome;
		पूर्ण __packed cq_err;
		काष्ठा अणु
			u32    reserved1[2];
			__be32 port;
		पूर्ण __packed port_change;
	पूर्ण event;
	u8 reserved3[3];
	u8 owner;
पूर्ण __packed;

#घोषणा  MTHCA_EQ_ENTRY_OWNER_SW      (0 << 7)
#घोषणा  MTHCA_EQ_ENTRY_OWNER_HW      (1 << 7)

अटल अंतरभूत u64 async_mask(काष्ठा mthca_dev *dev)
अणु
	वापस dev->mthca_flags & MTHCA_FLAG_SRQ ?
		MTHCA_ASYNC_EVENT_MASK | MTHCA_SRQ_EVENT_MASK :
		MTHCA_ASYNC_EVENT_MASK;
पूर्ण

अटल अंतरभूत व्योम tavor_set_eq_ci(काष्ठा mthca_dev *dev, काष्ठा mthca_eq *eq, u32 ci)
अणु
	/*
	 * This barrier makes sure that all updates to ownership bits
	 * करोne by set_eqe_hw() hit memory beक्रमe the consumer index
	 * is updated.  set_eq_ci() allows the HCA to possibly ग_लिखो
	 * more EQ entries, and we want to aव्योम the exceedingly
	 * unlikely possibility of the HCA writing an entry and then
	 * having set_eqe_hw() overग_लिखो the owner field.
	 */
	wmb();
	mthca_ग_लिखो64(MTHCA_EQ_DB_SET_CI | eq->eqn, ci & (eq->nent - 1),
		      dev->kar + MTHCA_EQ_DOORBELL,
		      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
पूर्ण

अटल अंतरभूत व्योम arbel_set_eq_ci(काष्ठा mthca_dev *dev, काष्ठा mthca_eq *eq, u32 ci)
अणु
	/* See comment in tavor_set_eq_ci() above. */
	wmb();
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32(ci),
		     dev->eq_regs.arbel.eq_set_ci_base + eq->eqn * 8);
	/* We still want ordering, just not swabbing, so add a barrier */
	mb();
पूर्ण

अटल अंतरभूत व्योम set_eq_ci(काष्ठा mthca_dev *dev, काष्ठा mthca_eq *eq, u32 ci)
अणु
	अगर (mthca_is_memमुक्त(dev))
		arbel_set_eq_ci(dev, eq, ci);
	अन्यथा
		tavor_set_eq_ci(dev, eq, ci);
पूर्ण

अटल अंतरभूत व्योम tavor_eq_req_not(काष्ठा mthca_dev *dev, पूर्णांक eqn)
अणु
	mthca_ग_लिखो64(MTHCA_EQ_DB_REQ_NOT | eqn, 0,
		      dev->kar + MTHCA_EQ_DOORBELL,
		      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
पूर्ण

अटल अंतरभूत व्योम arbel_eq_req_not(काष्ठा mthca_dev *dev, u32 eqn_mask)
अणु
	ग_लिखोl(eqn_mask, dev->eq_regs.arbel.eq_arm);
पूर्ण

अटल अंतरभूत व्योम disarm_cq(काष्ठा mthca_dev *dev, पूर्णांक eqn, पूर्णांक cqn)
अणु
	अगर (!mthca_is_memमुक्त(dev)) अणु
		mthca_ग_लिखो64(MTHCA_EQ_DB_DISARM_CQ | eqn, cqn,
			      dev->kar + MTHCA_EQ_DOORBELL,
			      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा mthca_eqe *get_eqe(काष्ठा mthca_eq *eq, u32 entry)
अणु
	अचिन्हित दीर्घ off = (entry & (eq->nent - 1)) * MTHCA_EQ_ENTRY_SIZE;
	वापस eq->page_list[off / PAGE_SIZE].buf + off % PAGE_SIZE;
पूर्ण

अटल अंतरभूत काष्ठा mthca_eqe *next_eqe_sw(काष्ठा mthca_eq *eq)
अणु
	काष्ठा mthca_eqe *eqe;
	eqe = get_eqe(eq, eq->cons_index);
	वापस (MTHCA_EQ_ENTRY_OWNER_HW & eqe->owner) ? शून्य : eqe;
पूर्ण

अटल अंतरभूत व्योम set_eqe_hw(काष्ठा mthca_eqe *eqe)
अणु
	eqe->owner =  MTHCA_EQ_ENTRY_OWNER_HW;
पूर्ण

अटल व्योम port_change(काष्ठा mthca_dev *dev, पूर्णांक port, पूर्णांक active)
अणु
	काष्ठा ib_event record;

	mthca_dbg(dev, "Port change to %s for port %d\n",
		  active ? "active" : "down", port);

	record.device = &dev->ib_dev;
	record.event  = active ? IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;
	record.element.port_num = port;

	ib_dispatch_event(&record);
पूर्ण

अटल पूर्णांक mthca_eq_पूर्णांक(काष्ठा mthca_dev *dev, काष्ठा mthca_eq *eq)
अणु
	काष्ठा mthca_eqe *eqe;
	पूर्णांक disarm_cqn;
	पूर्णांक eqes_found = 0;
	पूर्णांक set_ci = 0;

	जबतक ((eqe = next_eqe_sw(eq))) अणु
		/*
		 * Make sure we पढ़ो EQ entry contents after we've
		 * checked the ownership bit.
		 */
		rmb();

		चयन (eqe->type) अणु
		हाल MTHCA_EVENT_TYPE_COMP:
			disarm_cqn = be32_to_cpu(eqe->event.comp.cqn) & 0xffffff;
			disarm_cq(dev, eq->eqn, disarm_cqn);
			mthca_cq_completion(dev, disarm_cqn);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_PATH_MIG:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_PATH_MIG);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_COMM_EST:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_COMM_EST);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_SQ_DRAINED:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_SQ_DRAINED);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_SRQ_QP_LAST_WQE:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_QP_LAST_WQE_REACHED);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_SRQ_LIMIT:
			mthca_srq_event(dev, be32_to_cpu(eqe->event.srq.srqn) & 0xffffff,
					IB_EVENT_SRQ_LIMIT_REACHED);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_WQ_CATAS_ERROR:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_QP_FATAL);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_PATH_MIG_FAILED:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_PATH_MIG_ERR);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_QP_REQ_ERR);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_WQ_ACCESS_ERROR:
			mthca_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) & 0xffffff,
				       IB_EVENT_QP_ACCESS_ERR);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_CMD:
			mthca_cmd_event(dev,
					be16_to_cpu(eqe->event.cmd.token),
					eqe->event.cmd.status,
					be64_to_cpu(eqe->event.cmd.out_param));
			अवरोध;

		हाल MTHCA_EVENT_TYPE_PORT_CHANGE:
			port_change(dev,
				    (be32_to_cpu(eqe->event.port_change.port) >> 28) & 3,
				    eqe->subtype == 0x4);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_CQ_ERROR:
			mthca_warn(dev, "CQ %s on CQN %06x\n",
				   eqe->event.cq_err.syndrome == 1 ?
				   "overrun" : "access violation",
				   be32_to_cpu(eqe->event.cq_err.cqn) & 0xffffff);
			mthca_cq_event(dev, be32_to_cpu(eqe->event.cq_err.cqn),
				       IB_EVENT_CQ_ERR);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_EQ_OVERFLOW:
			mthca_warn(dev, "EQ overrun on EQN %d\n", eq->eqn);
			अवरोध;

		हाल MTHCA_EVENT_TYPE_EEC_CATAS_ERROR:
		हाल MTHCA_EVENT_TYPE_SRQ_CATAS_ERROR:
		हाल MTHCA_EVENT_TYPE_LOCAL_CATAS_ERROR:
		हाल MTHCA_EVENT_TYPE_ECC_DETECT:
		शेष:
			mthca_warn(dev, "Unhandled event %02x(%02x) on EQ %d\n",
				   eqe->type, eqe->subtype, eq->eqn);
			अवरोध;
		पूर्ण

		set_eqe_hw(eqe);
		++eq->cons_index;
		eqes_found = 1;
		++set_ci;

		/*
		 * The HCA will think the queue has overflowed अगर we
		 * करोn't tell it we've been processing events.  We
		 * create our EQs with MTHCA_NUM_SPARE_EQE extra
		 * entries, so we must update our consumer index at
		 * least that often.
		 */
		अगर (unlikely(set_ci >= MTHCA_NUM_SPARE_EQE)) अणु
			/*
			 * Conditional on hca_type is OK here because
			 * this is a rare हाल, not the fast path.
			 */
			set_eq_ci(dev, eq, eq->cons_index);
			set_ci = 0;
		पूर्ण
	पूर्ण

	/*
	 * Rely on caller to set consumer index so that we करोn't have
	 * to test hca_type in our पूर्णांकerrupt handling fast path.
	 */
	वापस eqes_found;
पूर्ण

अटल irqवापस_t mthca_tavor_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_ptr)
अणु
	काष्ठा mthca_dev *dev = dev_ptr;
	u32 ecr;
	पूर्णांक i;

	अगर (dev->eq_table.clr_mask)
		ग_लिखोl(dev->eq_table.clr_mask, dev->eq_table.clr_पूर्णांक);

	ecr = पढ़ोl(dev->eq_regs.tavor.ecr_base + 4);
	अगर (!ecr)
		वापस IRQ_NONE;

	ग_लिखोl(ecr, dev->eq_regs.tavor.ecr_base +
	       MTHCA_ECR_CLR_BASE - MTHCA_ECR_BASE + 4);

	क्रम (i = 0; i < MTHCA_NUM_EQ; ++i)
		अगर (ecr & dev->eq_table.eq[i].eqn_mask) अणु
			अगर (mthca_eq_पूर्णांक(dev, &dev->eq_table.eq[i]))
				tavor_set_eq_ci(dev, &dev->eq_table.eq[i],
						dev->eq_table.eq[i].cons_index);
			tavor_eq_req_not(dev, dev->eq_table.eq[i].eqn);
		पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mthca_tavor_msi_x_पूर्णांकerrupt(पूर्णांक irq, व्योम *eq_ptr)
अणु
	काष्ठा mthca_eq  *eq  = eq_ptr;
	काष्ठा mthca_dev *dev = eq->dev;

	mthca_eq_पूर्णांक(dev, eq);
	tavor_set_eq_ci(dev, eq, eq->cons_index);
	tavor_eq_req_not(dev, eq->eqn);

	/* MSI-X vectors always beदीर्घ to us */
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mthca_arbel_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_ptr)
अणु
	काष्ठा mthca_dev *dev = dev_ptr;
	पूर्णांक work = 0;
	पूर्णांक i;

	अगर (dev->eq_table.clr_mask)
		ग_लिखोl(dev->eq_table.clr_mask, dev->eq_table.clr_पूर्णांक);

	क्रम (i = 0; i < MTHCA_NUM_EQ; ++i)
		अगर (mthca_eq_पूर्णांक(dev, &dev->eq_table.eq[i])) अणु
			work = 1;
			arbel_set_eq_ci(dev, &dev->eq_table.eq[i],
					dev->eq_table.eq[i].cons_index);
		पूर्ण

	arbel_eq_req_not(dev, dev->eq_table.arm_mask);

	वापस IRQ_RETVAL(work);
पूर्ण

अटल irqवापस_t mthca_arbel_msi_x_पूर्णांकerrupt(पूर्णांक irq, व्योम *eq_ptr)
अणु
	काष्ठा mthca_eq  *eq  = eq_ptr;
	काष्ठा mthca_dev *dev = eq->dev;

	mthca_eq_पूर्णांक(dev, eq);
	arbel_set_eq_ci(dev, eq, eq->cons_index);
	arbel_eq_req_not(dev, eq->eqn_mask);

	/* MSI-X vectors always beदीर्घ to us */
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mthca_create_eq(काष्ठा mthca_dev *dev,
			   पूर्णांक nent,
			   u8 पूर्णांकr,
			   काष्ठा mthca_eq *eq)
अणु
	पूर्णांक npages;
	u64 *dma_list = शून्य;
	dma_addr_t t;
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_eq_context *eq_context;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	eq->dev  = dev;
	eq->nent = roundup_घात_of_two(max(nent, 2));
	npages = ALIGN(eq->nent * MTHCA_EQ_ENTRY_SIZE, PAGE_SIZE) / PAGE_SIZE;

	eq->page_list = kदो_स्मृति_array(npages, माप(*eq->page_list),
				      GFP_KERNEL);
	अगर (!eq->page_list)
		जाओ err_out;

	क्रम (i = 0; i < npages; ++i)
		eq->page_list[i].buf = शून्य;

	dma_list = kदो_स्मृति_array(npages, माप(*dma_list), GFP_KERNEL);
	अगर (!dma_list)
		जाओ err_out_मुक्त;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		जाओ err_out_मुक्त;
	eq_context = mailbox->buf;

	क्रम (i = 0; i < npages; ++i) अणु
		eq->page_list[i].buf = dma_alloc_coherent(&dev->pdev->dev,
							  PAGE_SIZE, &t, GFP_KERNEL);
		अगर (!eq->page_list[i].buf)
			जाओ err_out_मुक्त_pages;

		dma_list[i] = t;
		dma_unmap_addr_set(&eq->page_list[i], mapping, t);

		clear_page(eq->page_list[i].buf);
	पूर्ण

	क्रम (i = 0; i < eq->nent; ++i)
		set_eqe_hw(get_eqe(eq, i));

	eq->eqn = mthca_alloc(&dev->eq_table.alloc);
	अगर (eq->eqn == -1)
		जाओ err_out_मुक्त_pages;

	err = mthca_mr_alloc_phys(dev, dev->driver_pd.pd_num,
				  dma_list, PAGE_SHIFT, npages,
				  0, npages * PAGE_SIZE,
				  MTHCA_MPT_FLAG_LOCAL_WRITE |
				  MTHCA_MPT_FLAG_LOCAL_READ,
				  &eq->mr);
	अगर (err)
		जाओ err_out_मुक्त_eq;

	स_रखो(eq_context, 0, माप *eq_context);
	eq_context->flags           = cpu_to_be32(MTHCA_EQ_STATUS_OK   |
						  MTHCA_EQ_OWNER_HW    |
						  MTHCA_EQ_STATE_ARMED |
						  MTHCA_EQ_FLAG_TR);
	अगर (mthca_is_memमुक्त(dev))
		eq_context->flags  |= cpu_to_be32(MTHCA_EQ_STATE_ARBEL);

	eq_context->logsize_usrpage = cpu_to_be32((ffs(eq->nent) - 1) << 24);
	अगर (mthca_is_memमुक्त(dev)) अणु
		eq_context->arbel_pd = cpu_to_be32(dev->driver_pd.pd_num);
	पूर्ण अन्यथा अणु
		eq_context->logsize_usrpage |= cpu_to_be32(dev->driver_uar.index);
		eq_context->tavor_pd         = cpu_to_be32(dev->driver_pd.pd_num);
	पूर्ण
	eq_context->पूर्णांकr            = पूर्णांकr;
	eq_context->lkey            = cpu_to_be32(eq->mr.ibmr.lkey);

	err = mthca_SW2HW_EQ(dev, mailbox, eq->eqn);
	अगर (err) अणु
		mthca_warn(dev, "SW2HW_EQ returned %d\n", err);
		जाओ err_out_मुक्त_mr;
	पूर्ण

	kमुक्त(dma_list);
	mthca_मुक्त_mailbox(dev, mailbox);

	eq->eqn_mask   = swab32(1 << eq->eqn);
	eq->cons_index = 0;

	dev->eq_table.arm_mask |= eq->eqn_mask;

	mthca_dbg(dev, "Allocated EQ %d with %d entries\n",
		  eq->eqn, eq->nent);

	वापस err;

 err_out_मुक्त_mr:
	mthca_मुक्त_mr(dev, &eq->mr);

 err_out_मुक्त_eq:
	mthca_मुक्त(&dev->eq_table.alloc, eq->eqn);

 err_out_मुक्त_pages:
	क्रम (i = 0; i < npages; ++i)
		अगर (eq->page_list[i].buf)
			dma_मुक्त_coherent(&dev->pdev->dev, PAGE_SIZE,
					  eq->page_list[i].buf,
					  dma_unmap_addr(&eq->page_list[i],
							 mapping));

	mthca_मुक्त_mailbox(dev, mailbox);

 err_out_मुक्त:
	kमुक्त(eq->page_list);
	kमुक्त(dma_list);

 err_out:
	वापस err;
पूर्ण

अटल व्योम mthca_मुक्त_eq(काष्ठा mthca_dev *dev,
			  काष्ठा mthca_eq *eq)
अणु
	काष्ठा mthca_mailbox *mailbox;
	पूर्णांक err;
	पूर्णांक npages = (eq->nent * MTHCA_EQ_ENTRY_SIZE + PAGE_SIZE - 1) /
		PAGE_SIZE;
	पूर्णांक i;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस;

	err = mthca_HW2SW_EQ(dev, mailbox, eq->eqn);
	अगर (err)
		mthca_warn(dev, "HW2SW_EQ returned %d\n", err);

	dev->eq_table.arm_mask &= ~eq->eqn_mask;

	अगर (0) अणु
		mthca_dbg(dev, "Dumping EQ context %02x:\n", eq->eqn);
		क्रम (i = 0; i < माप (काष्ठा mthca_eq_context) / 4; ++i) अणु
			अगर (i % 4 == 0)
				prपूर्णांकk("[%02x] ", i * 4);
			prपूर्णांकk(" %08x", be32_to_cpup(mailbox->buf + i * 4));
			अगर ((i + 1) % 4 == 0)
				prपूर्णांकk("\n");
		पूर्ण
	पूर्ण

	mthca_मुक्त_mr(dev, &eq->mr);
	क्रम (i = 0; i < npages; ++i)
		pci_मुक्त_consistent(dev->pdev, PAGE_SIZE,
				    eq->page_list[i].buf,
				    dma_unmap_addr(&eq->page_list[i], mapping));

	kमुक्त(eq->page_list);
	mthca_मुक्त_mailbox(dev, mailbox);
पूर्ण

अटल व्योम mthca_मुक्त_irqs(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक i;

	अगर (dev->eq_table.have_irq)
		मुक्त_irq(dev->pdev->irq, dev);
	क्रम (i = 0; i < MTHCA_NUM_EQ; ++i)
		अगर (dev->eq_table.eq[i].have_irq) अणु
			मुक्त_irq(dev->eq_table.eq[i].msi_x_vector,
				 dev->eq_table.eq + i);
			dev->eq_table.eq[i].have_irq = 0;
		पूर्ण
पूर्ण

अटल पूर्णांक mthca_map_reg(काष्ठा mthca_dev *dev,
			 अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size,
			 व्योम __iomem **map)
अणु
	phys_addr_t base = pci_resource_start(dev->pdev, 0);

	*map = ioremap(base + offset, size);
	अगर (!*map)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_map_eq_regs(काष्ठा mthca_dev *dev)
अणु
	अगर (mthca_is_memमुक्त(dev)) अणु
		/*
		 * We assume that the EQ arm and EQ set CI रेजिस्टरs
		 * fall within the first BAR.  We can't trust the
		 * values firmware gives us, since those addresses are
		 * valid on the HCA's side of the PCI bus but not
		 * necessarily the host side.
		 */
		अगर (mthca_map_reg(dev, (pci_resource_len(dev->pdev, 0) - 1) &
				  dev->fw.arbel.clr_पूर्णांक_base, MTHCA_CLR_INT_SIZE,
				  &dev->clr_base)) अणु
			mthca_err(dev, "Couldn't map interrupt clear register, "
				  "aborting.\n");
			वापस -ENOMEM;
		पूर्ण

		/*
		 * Add 4 because we limit ourselves to EQs 0 ... 31,
		 * so we only need the low word of the रेजिस्टर.
		 */
		अगर (mthca_map_reg(dev, ((pci_resource_len(dev->pdev, 0) - 1) &
					dev->fw.arbel.eq_arm_base) + 4, 4,
				  &dev->eq_regs.arbel.eq_arm)) अणु
			mthca_err(dev, "Couldn't map EQ arm register, aborting.\n");
			iounmap(dev->clr_base);
			वापस -ENOMEM;
		पूर्ण

		अगर (mthca_map_reg(dev, (pci_resource_len(dev->pdev, 0) - 1) &
				  dev->fw.arbel.eq_set_ci_base,
				  MTHCA_EQ_SET_CI_SIZE,
				  &dev->eq_regs.arbel.eq_set_ci_base)) अणु
			mthca_err(dev, "Couldn't map EQ CI register, aborting.\n");
			iounmap(dev->eq_regs.arbel.eq_arm);
			iounmap(dev->clr_base);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mthca_map_reg(dev, MTHCA_CLR_INT_BASE, MTHCA_CLR_INT_SIZE,
				  &dev->clr_base)) अणु
			mthca_err(dev, "Couldn't map interrupt clear register, "
				  "aborting.\n");
			वापस -ENOMEM;
		पूर्ण

		अगर (mthca_map_reg(dev, MTHCA_ECR_BASE,
				  MTHCA_ECR_SIZE + MTHCA_ECR_CLR_SIZE,
				  &dev->eq_regs.tavor.ecr_base)) अणु
			mthca_err(dev, "Couldn't map ecr register, "
				  "aborting.\n");
			iounmap(dev->clr_base);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण

अटल व्योम mthca_unmap_eq_regs(काष्ठा mthca_dev *dev)
अणु
	अगर (mthca_is_memमुक्त(dev)) अणु
		iounmap(dev->eq_regs.arbel.eq_set_ci_base);
		iounmap(dev->eq_regs.arbel.eq_arm);
		iounmap(dev->clr_base);
	पूर्ण अन्यथा अणु
		iounmap(dev->eq_regs.tavor.ecr_base);
		iounmap(dev->clr_base);
	पूर्ण
पूर्ण

पूर्णांक mthca_map_eq_icm(काष्ठा mthca_dev *dev, u64 icm_virt)
अणु
	पूर्णांक ret;

	/*
	 * We assume that mapping one page is enough क्रम the whole EQ
	 * context table.  This is fine with all current HCAs, because
	 * we only use 32 EQs and each EQ uses 32 bytes of context
	 * memory, or 1 KB total.
	 */
	dev->eq_table.icm_virt = icm_virt;
	dev->eq_table.icm_page = alloc_page(GFP_HIGHUSER);
	अगर (!dev->eq_table.icm_page)
		वापस -ENOMEM;
	dev->eq_table.icm_dma  = pci_map_page(dev->pdev, dev->eq_table.icm_page, 0,
					      PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
	अगर (pci_dma_mapping_error(dev->pdev, dev->eq_table.icm_dma)) अणु
		__मुक्त_page(dev->eq_table.icm_page);
		वापस -ENOMEM;
	पूर्ण

	ret = mthca_MAP_ICM_page(dev, dev->eq_table.icm_dma, icm_virt);
	अगर (ret) अणु
		pci_unmap_page(dev->pdev, dev->eq_table.icm_dma, PAGE_SIZE,
			       PCI_DMA_BIसूचीECTIONAL);
		__मुक्त_page(dev->eq_table.icm_page);
	पूर्ण

	वापस ret;
पूर्ण

व्योम mthca_unmap_eq_icm(काष्ठा mthca_dev *dev)
अणु
	mthca_UNMAP_ICM(dev, dev->eq_table.icm_virt, 1);
	pci_unmap_page(dev->pdev, dev->eq_table.icm_dma, PAGE_SIZE,
		       PCI_DMA_BIसूचीECTIONAL);
	__मुक्त_page(dev->eq_table.icm_page);
पूर्ण

पूर्णांक mthca_init_eq_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक err;
	u8 पूर्णांकr;
	पूर्णांक i;

	err = mthca_alloc_init(&dev->eq_table.alloc,
			       dev->limits.num_eqs,
			       dev->limits.num_eqs - 1,
			       dev->limits.reserved_eqs);
	अगर (err)
		वापस err;

	err = mthca_map_eq_regs(dev);
	अगर (err)
		जाओ err_out_मुक्त;

	अगर (dev->mthca_flags & MTHCA_FLAG_MSI_X) अणु
		dev->eq_table.clr_mask = 0;
	पूर्ण अन्यथा अणु
		dev->eq_table.clr_mask =
			swab32(1 << (dev->eq_table.पूर्णांकa_pin & 31));
		dev->eq_table.clr_पूर्णांक  = dev->clr_base +
			(dev->eq_table.पूर्णांकa_pin < 32 ? 4 : 0);
	पूर्ण

	dev->eq_table.arm_mask = 0;

	पूर्णांकr = dev->eq_table.पूर्णांकa_pin;

	err = mthca_create_eq(dev, dev->limits.num_cqs + MTHCA_NUM_SPARE_EQE,
			      (dev->mthca_flags & MTHCA_FLAG_MSI_X) ? 128 : पूर्णांकr,
			      &dev->eq_table.eq[MTHCA_EQ_COMP]);
	अगर (err)
		जाओ err_out_unmap;

	err = mthca_create_eq(dev, MTHCA_NUM_ASYNC_EQE + MTHCA_NUM_SPARE_EQE,
			      (dev->mthca_flags & MTHCA_FLAG_MSI_X) ? 129 : पूर्णांकr,
			      &dev->eq_table.eq[MTHCA_EQ_ASYNC]);
	अगर (err)
		जाओ err_out_comp;

	err = mthca_create_eq(dev, MTHCA_NUM_CMD_EQE + MTHCA_NUM_SPARE_EQE,
			      (dev->mthca_flags & MTHCA_FLAG_MSI_X) ? 130 : पूर्णांकr,
			      &dev->eq_table.eq[MTHCA_EQ_CMD]);
	अगर (err)
		जाओ err_out_async;

	अगर (dev->mthca_flags & MTHCA_FLAG_MSI_X) अणु
		अटल स्थिर अक्षर *eq_name[] = अणु
			[MTHCA_EQ_COMP]  = DRV_NAME "-comp",
			[MTHCA_EQ_ASYNC] = DRV_NAME "-async",
			[MTHCA_EQ_CMD]   = DRV_NAME "-cmd"
		पूर्ण;

		क्रम (i = 0; i < MTHCA_NUM_EQ; ++i) अणु
			snम_लिखो(dev->eq_table.eq[i].irq_name,
				 IB_DEVICE_NAME_MAX,
				 "%s@pci:%s", eq_name[i],
				 pci_name(dev->pdev));
			err = request_irq(dev->eq_table.eq[i].msi_x_vector,
					  mthca_is_memमुक्त(dev) ?
					  mthca_arbel_msi_x_पूर्णांकerrupt :
					  mthca_tavor_msi_x_पूर्णांकerrupt,
					  0, dev->eq_table.eq[i].irq_name,
					  dev->eq_table.eq + i);
			अगर (err)
				जाओ err_out_cmd;
			dev->eq_table.eq[i].have_irq = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(dev->eq_table.eq[0].irq_name, IB_DEVICE_NAME_MAX,
			 DRV_NAME "@pci:%s", pci_name(dev->pdev));
		err = request_irq(dev->pdev->irq,
				  mthca_is_memमुक्त(dev) ?
				  mthca_arbel_पूर्णांकerrupt :
				  mthca_tavor_पूर्णांकerrupt,
				  IRQF_SHARED, dev->eq_table.eq[0].irq_name, dev);
		अगर (err)
			जाओ err_out_cmd;
		dev->eq_table.have_irq = 1;
	पूर्ण

	err = mthca_MAP_EQ(dev, async_mask(dev),
			   0, dev->eq_table.eq[MTHCA_EQ_ASYNC].eqn);
	अगर (err)
		mthca_warn(dev, "MAP_EQ for async EQ %d failed (%d)\n",
			   dev->eq_table.eq[MTHCA_EQ_ASYNC].eqn, err);

	err = mthca_MAP_EQ(dev, MTHCA_CMD_EVENT_MASK,
			   0, dev->eq_table.eq[MTHCA_EQ_CMD].eqn);
	अगर (err)
		mthca_warn(dev, "MAP_EQ for cmd EQ %d failed (%d)\n",
			   dev->eq_table.eq[MTHCA_EQ_CMD].eqn, err);

	क्रम (i = 0; i < MTHCA_NUM_EQ; ++i)
		अगर (mthca_is_memमुक्त(dev))
			arbel_eq_req_not(dev, dev->eq_table.eq[i].eqn_mask);
		अन्यथा
			tavor_eq_req_not(dev, dev->eq_table.eq[i].eqn);

	वापस 0;

err_out_cmd:
	mthca_मुक्त_irqs(dev);
	mthca_मुक्त_eq(dev, &dev->eq_table.eq[MTHCA_EQ_CMD]);

err_out_async:
	mthca_मुक्त_eq(dev, &dev->eq_table.eq[MTHCA_EQ_ASYNC]);

err_out_comp:
	mthca_मुक्त_eq(dev, &dev->eq_table.eq[MTHCA_EQ_COMP]);

err_out_unmap:
	mthca_unmap_eq_regs(dev);

err_out_मुक्त:
	mthca_alloc_cleanup(&dev->eq_table.alloc);
	वापस err;
पूर्ण

व्योम mthca_cleanup_eq_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक i;

	mthca_मुक्त_irqs(dev);

	mthca_MAP_EQ(dev, async_mask(dev),
		     1, dev->eq_table.eq[MTHCA_EQ_ASYNC].eqn);
	mthca_MAP_EQ(dev, MTHCA_CMD_EVENT_MASK,
		     1, dev->eq_table.eq[MTHCA_EQ_CMD].eqn);

	क्रम (i = 0; i < MTHCA_NUM_EQ; ++i)
		mthca_मुक्त_eq(dev, &dev->eq_table.eq[i]);

	mthca_unmap_eq_regs(dev);

	mthca_alloc_cleanup(&dev->eq_table.alloc);
पूर्ण
