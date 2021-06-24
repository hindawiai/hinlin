<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2017-2019 NXP */

#समावेश "enetc_pf.h"

अटल व्योम enetc_msg_disable_mr_पूर्णांक(काष्ठा enetc_hw *hw)
अणु
	u32 psiier = enetc_rd(hw, ENETC_PSIIER);
	/* disable MR पूर्णांक source(s) */
	enetc_wr(hw, ENETC_PSIIER, psiier & ~ENETC_PSIIER_MR_MASK);
पूर्ण

अटल व्योम enetc_msg_enable_mr_पूर्णांक(काष्ठा enetc_hw *hw)
अणु
	u32 psiier = enetc_rd(hw, ENETC_PSIIER);

	enetc_wr(hw, ENETC_PSIIER, psiier | ENETC_PSIIER_MR_MASK);
पूर्ण

अटल irqवापस_t enetc_msg_psi_msix(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा enetc_si *si = (काष्ठा enetc_si *)data;
	काष्ठा enetc_pf *pf = enetc_si_priv(si);

	enetc_msg_disable_mr_पूर्णांक(&si->hw);
	schedule_work(&pf->msg_task);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम enetc_msg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enetc_pf *pf = container_of(work, काष्ठा enetc_pf, msg_task);
	काष्ठा enetc_hw *hw = &pf->si->hw;
	अचिन्हित दीर्घ mr_mask;
	पूर्णांक i;

	क्रम (;;) अणु
		mr_mask = enetc_rd(hw, ENETC_PSIMSGRR) & ENETC_PSIMSGRR_MR_MASK;
		अगर (!mr_mask) अणु
			/* re-arm MR पूर्णांकerrupts, w1c the IDR reg */
			enetc_wr(hw, ENETC_PSIIDR, ENETC_PSIIER_MR_MASK);
			enetc_msg_enable_mr_पूर्णांक(hw);
			वापस;
		पूर्ण

		क्रम (i = 0; i < pf->num_vfs; i++) अणु
			u32 psimsgrr;
			u16 msg_code;

			अगर (!(ENETC_PSIMSGRR_MR(i) & mr_mask))
				जारी;

			enetc_msg_handle_rxmsg(pf, i, &msg_code);

			psimsgrr = ENETC_SIMSGSR_SET_MC(msg_code);
			psimsgrr |= ENETC_PSIMSGRR_MR(i); /* w1c */
			enetc_wr(hw, ENETC_PSIMSGRR, psimsgrr);
		पूर्ण
	पूर्ण
पूर्ण

/* Init */
अटल पूर्णांक enetc_msg_alloc_mbx(काष्ठा enetc_si *si, पूर्णांक idx)
अणु
	काष्ठा enetc_pf *pf = enetc_si_priv(si);
	काष्ठा device *dev = &si->pdev->dev;
	काष्ठा enetc_hw *hw = &si->hw;
	काष्ठा enetc_msg_swbd *msg;
	u32 val;

	msg = &pf->rxmsg[idx];
	/* allocate and set receive buffer */
	msg->size = ENETC_DEFAULT_MSG_SIZE;

	msg->vaddr = dma_alloc_coherent(dev, msg->size, &msg->dma,
					GFP_KERNEL);
	अगर (!msg->vaddr) अणु
		dev_err(dev, "msg: fail to alloc dma buffer of size: %d\n",
			msg->size);
		वापस -ENOMEM;
	पूर्ण

	/* set multiple of 32 bytes */
	val = lower_32_bits(msg->dma);
	enetc_wr(hw, ENETC_PSIVMSGRCVAR0(idx), val);
	val = upper_32_bits(msg->dma);
	enetc_wr(hw, ENETC_PSIVMSGRCVAR1(idx), val);

	वापस 0;
पूर्ण

अटल व्योम enetc_msg_मुक्त_mbx(काष्ठा enetc_si *si, पूर्णांक idx)
अणु
	काष्ठा enetc_pf *pf = enetc_si_priv(si);
	काष्ठा enetc_hw *hw = &si->hw;
	काष्ठा enetc_msg_swbd *msg;

	msg = &pf->rxmsg[idx];
	dma_मुक्त_coherent(&si->pdev->dev, msg->size, msg->vaddr, msg->dma);
	स_रखो(msg, 0, माप(*msg));

	enetc_wr(hw, ENETC_PSIVMSGRCVAR0(idx), 0);
	enetc_wr(hw, ENETC_PSIVMSGRCVAR1(idx), 0);
पूर्ण

पूर्णांक enetc_msg_psi_init(काष्ठा enetc_pf *pf)
अणु
	काष्ठा enetc_si *si = pf->si;
	पूर्णांक vector, i, err;

	/* रेजिस्टर message passing पूर्णांकerrupt handler */
	snम_लिखो(pf->msg_पूर्णांक_name, माप(pf->msg_पूर्णांक_name), "%s-vfmsg",
		 si->ndev->name);
	vector = pci_irq_vector(si->pdev, ENETC_SI_INT_IDX);
	err = request_irq(vector, enetc_msg_psi_msix, 0, pf->msg_पूर्णांक_name, si);
	अगर (err) अणु
		dev_err(&si->pdev->dev,
			"PSI messaging: request_irq() failed!\n");
		वापस err;
	पूर्ण

	/* set one IRQ entry क्रम PSI message receive notअगरication (SI पूर्णांक) */
	enetc_wr(&si->hw, ENETC_SIMSIVR, ENETC_SI_INT_IDX);

	/* initialize PSI mailbox */
	INIT_WORK(&pf->msg_task, enetc_msg_task);

	क्रम (i = 0; i < pf->num_vfs; i++) अणु
		err = enetc_msg_alloc_mbx(si, i);
		अगर (err)
			जाओ err_init_mbx;
	पूर्ण

	/* enable MR पूर्णांकerrupts */
	enetc_msg_enable_mr_पूर्णांक(&si->hw);

	वापस 0;

err_init_mbx:
	क्रम (i--; i >= 0; i--)
		enetc_msg_मुक्त_mbx(si, i);

	मुक्त_irq(vector, si);

	वापस err;
पूर्ण

व्योम enetc_msg_psi_मुक्त(काष्ठा enetc_pf *pf)
अणु
	काष्ठा enetc_si *si = pf->si;
	पूर्णांक i;

	cancel_work_sync(&pf->msg_task);

	/* disable MR पूर्णांकerrupts */
	enetc_msg_disable_mr_पूर्णांक(&si->hw);

	क्रम (i = 0; i < pf->num_vfs; i++)
		enetc_msg_मुक्त_mbx(si, i);

	/* de-रेजिस्टर message passing पूर्णांकerrupt handler */
	मुक्त_irq(pci_irq_vector(si->pdev, ENETC_SI_INT_IDX), si);
पूर्ण
