<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pci.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>

#समावेश "nitrox_dev.h"
#समावेश "nitrox_csr.h"
#समावेश "nitrox_common.h"
#समावेश "nitrox_hal.h"
#समावेश "nitrox_isr.h"
#समावेश "nitrox_mbx.h"

/*
 * One vector क्रम each type of ring
 *  - NPS packet ring, AQMQ ring and ZQMQ ring
 */
#घोषणा NR_RING_VECTORS 3
#घोषणा NR_NON_RING_VECTORS 1
/* base entry क्रम packet ring/port */
#घोषणा PKT_RING_MSIX_BASE 0
#घोषणा NON_RING_MSIX_BASE 192

/**
 * nps_pkt_slc_isr - IRQ handler क्रम NPS solicit port
 * @irq: irq number
 * @data: argument
 */
अटल irqवापस_t nps_pkt_slc_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nitrox_q_vector *qvec = data;
	जोड़ nps_pkt_slc_cnts slc_cnts;
	काष्ठा nitrox_cmdq *cmdq = qvec->cmdq;

	slc_cnts.value = पढ़ोq(cmdq->compl_cnt_csr_addr);
	/* New packet on SLC output port */
	अगर (slc_cnts.s.slc_पूर्णांक)
		tasklet_hi_schedule(&qvec->resp_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम clear_nps_core_err_पूर्णांकr(काष्ठा nitrox_device *ndev)
अणु
	u64 value;

	/* Write 1 to clear */
	value = nitrox_पढ़ो_csr(ndev, NPS_CORE_INT);
	nitrox_ग_लिखो_csr(ndev, NPS_CORE_INT, value);

	dev_err_ratelimited(DEV(ndev), "NSP_CORE_INT  0x%016llx\n", value);
पूर्ण

अटल व्योम clear_nps_pkt_err_पूर्णांकr(काष्ठा nitrox_device *ndev)
अणु
	जोड़ nps_pkt_पूर्णांक pkt_पूर्णांक;
	अचिन्हित दीर्घ value, offset;
	पूर्णांक i;

	pkt_पूर्णांक.value = nitrox_पढ़ो_csr(ndev, NPS_PKT_INT);
	dev_err_ratelimited(DEV(ndev), "NPS_PKT_INT  0x%016llx\n",
			    pkt_पूर्णांक.value);

	अगर (pkt_पूर्णांक.s.slc_err) अणु
		offset = NPS_PKT_SLC_ERR_TYPE;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
		dev_err_ratelimited(DEV(ndev),
				    "NPS_PKT_SLC_ERR_TYPE  0x%016lx\n", value);

		offset = NPS_PKT_SLC_RERR_LO;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
		/* enable the solicit ports */
		क्रम_each_set_bit(i, &value, BITS_PER_LONG)
			enable_pkt_solicit_port(ndev, i);

		dev_err_ratelimited(DEV(ndev),
				    "NPS_PKT_SLC_RERR_LO  0x%016lx\n", value);

		offset = NPS_PKT_SLC_RERR_HI;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
		dev_err_ratelimited(DEV(ndev),
				    "NPS_PKT_SLC_RERR_HI  0x%016lx\n", value);
	पूर्ण

	अगर (pkt_पूर्णांक.s.in_err) अणु
		offset = NPS_PKT_IN_ERR_TYPE;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
		dev_err_ratelimited(DEV(ndev),
				    "NPS_PKT_IN_ERR_TYPE  0x%016lx\n", value);
		offset = NPS_PKT_IN_RERR_LO;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
		/* enable the input ring */
		क्रम_each_set_bit(i, &value, BITS_PER_LONG)
			enable_pkt_input_ring(ndev, i);

		dev_err_ratelimited(DEV(ndev),
				    "NPS_PKT_IN_RERR_LO  0x%016lx\n", value);

		offset = NPS_PKT_IN_RERR_HI;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
		dev_err_ratelimited(DEV(ndev),
				    "NPS_PKT_IN_RERR_HI  0x%016lx\n", value);
	पूर्ण
पूर्ण

अटल व्योम clear_pom_err_पूर्णांकr(काष्ठा nitrox_device *ndev)
अणु
	u64 value;

	value = nitrox_पढ़ो_csr(ndev, POM_INT);
	nitrox_ग_लिखो_csr(ndev, POM_INT, value);
	dev_err_ratelimited(DEV(ndev), "POM_INT  0x%016llx\n", value);
पूर्ण

अटल व्योम clear_pem_err_पूर्णांकr(काष्ठा nitrox_device *ndev)
अणु
	u64 value;

	value = nitrox_पढ़ो_csr(ndev, PEM0_INT);
	nitrox_ग_लिखो_csr(ndev, PEM0_INT, value);
	dev_err_ratelimited(DEV(ndev), "PEM(0)_INT  0x%016llx\n", value);
पूर्ण

अटल व्योम clear_lbc_err_पूर्णांकr(काष्ठा nitrox_device *ndev)
अणु
	जोड़ lbc_पूर्णांक lbc_पूर्णांक;
	u64 value, offset;
	पूर्णांक i;

	lbc_पूर्णांक.value = nitrox_पढ़ो_csr(ndev, LBC_INT);
	dev_err_ratelimited(DEV(ndev), "LBC_INT  0x%016llx\n", lbc_पूर्णांक.value);

	अगर (lbc_पूर्णांक.s.dma_rd_err) अणु
		क्रम (i = 0; i < NR_CLUSTERS; i++) अणु
			offset = EFL_CORE_VF_ERR_INT0X(i);
			value = nitrox_पढ़ो_csr(ndev, offset);
			nitrox_ग_लिखो_csr(ndev, offset, value);
			offset = EFL_CORE_VF_ERR_INT1X(i);
			value = nitrox_पढ़ो_csr(ndev, offset);
			nitrox_ग_लिखो_csr(ndev, offset, value);
		पूर्ण
	पूर्ण

	अगर (lbc_पूर्णांक.s.cam_soft_err) अणु
		dev_err_ratelimited(DEV(ndev), "CAM_SOFT_ERR, invalidating LBC\n");
		invalidate_lbc(ndev);
	पूर्ण

	अगर (lbc_पूर्णांक.s.pref_dat_len_mismatch_err) अणु
		offset = LBC_PLM_VF1_64_INT;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
		offset = LBC_PLM_VF65_128_INT;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
	पूर्ण

	अगर (lbc_पूर्णांक.s.rd_dat_len_mismatch_err) अणु
		offset = LBC_ELM_VF1_64_INT;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
		offset = LBC_ELM_VF65_128_INT;
		value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, value);
	पूर्ण
	nitrox_ग_लिखो_csr(ndev, LBC_INT, lbc_पूर्णांक.value);
पूर्ण

अटल व्योम clear_efl_err_पूर्णांकr(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_CLUSTERS; i++) अणु
		जोड़ efl_core_पूर्णांक core_पूर्णांक;
		u64 value, offset;

		offset = EFL_CORE_INTX(i);
		core_पूर्णांक.value = nitrox_पढ़ो_csr(ndev, offset);
		nitrox_ग_लिखो_csr(ndev, offset, core_पूर्णांक.value);
		dev_err_ratelimited(DEV(ndev), "ELF_CORE(%d)_INT  0x%016llx\n",
				    i, core_पूर्णांक.value);
		अगर (core_पूर्णांक.s.se_err) अणु
			offset = EFL_CORE_SE_ERR_INTX(i);
			value = nitrox_पढ़ो_csr(ndev, offset);
			nitrox_ग_लिखो_csr(ndev, offset, value);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम clear_bmi_err_पूर्णांकr(काष्ठा nitrox_device *ndev)
अणु
	u64 value;

	value = nitrox_पढ़ो_csr(ndev, BMI_INT);
	nitrox_ग_लिखो_csr(ndev, BMI_INT, value);
	dev_err_ratelimited(DEV(ndev), "BMI_INT  0x%016llx\n", value);
पूर्ण

अटल व्योम nps_core_पूर्णांक_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा nitrox_q_vector *qvec = (व्योम *)(uपूर्णांकptr_t)(data);
	काष्ठा nitrox_device *ndev = qvec->ndev;

	/* अगर pf mode करो queue recovery */
	अगर (ndev->mode == __NDEV_MODE_PF) अणु
	पूर्ण अन्यथा अणु
		/**
		 * अगर VF(s) enabled communicate the error inक्रमmation
		 * to VF(s)
		 */
	पूर्ण
पूर्ण

/*
 * nps_core_पूर्णांक_isr - पूर्णांकerrupt handler क्रम NITROX errors and
 *   mailbox communication
 */
अटल irqवापस_t nps_core_पूर्णांक_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nitrox_q_vector *qvec = data;
	काष्ठा nitrox_device *ndev = qvec->ndev;
	जोड़ nps_core_पूर्णांक_active core_पूर्णांक;

	core_पूर्णांक.value = nitrox_पढ़ो_csr(ndev, NPS_CORE_INT_ACTIVE);

	अगर (core_पूर्णांक.s.nps_core)
		clear_nps_core_err_पूर्णांकr(ndev);

	अगर (core_पूर्णांक.s.nps_pkt)
		clear_nps_pkt_err_पूर्णांकr(ndev);

	अगर (core_पूर्णांक.s.pom)
		clear_pom_err_पूर्णांकr(ndev);

	अगर (core_पूर्णांक.s.pem)
		clear_pem_err_पूर्णांकr(ndev);

	अगर (core_पूर्णांक.s.lbc)
		clear_lbc_err_पूर्णांकr(ndev);

	अगर (core_पूर्णांक.s.efl)
		clear_efl_err_पूर्णांकr(ndev);

	अगर (core_पूर्णांक.s.bmi)
		clear_bmi_err_पूर्णांकr(ndev);

	/* Mailbox पूर्णांकerrupt */
	अगर (core_पूर्णांक.s.mbox)
		nitrox_pf2vf_mbox_handler(ndev);

	/* If more work callback the ISR, set resend */
	core_पूर्णांक.s.resend = 1;
	nitrox_ग_लिखो_csr(ndev, NPS_CORE_INT_ACTIVE, core_पूर्णांक.value);

	वापस IRQ_HANDLED;
पूर्ण

व्योम nitrox_unरेजिस्टर_पूर्णांकerrupts(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < ndev->num_vecs; i++) अणु
		काष्ठा nitrox_q_vector *qvec;
		पूर्णांक vec;

		qvec = ndev->qvec + i;
		अगर (!qvec->valid)
			जारी;

		/* get the vector number */
		vec = pci_irq_vector(pdev, i);
		irq_set_affinity_hपूर्णांक(vec, शून्य);
		मुक्त_irq(vec, qvec);

		tasklet_disable(&qvec->resp_tasklet);
		tasklet_समाप्त(&qvec->resp_tasklet);
		qvec->valid = false;
	पूर्ण
	kमुक्त(ndev->qvec);
	ndev->qvec = शून्य;
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

पूर्णांक nitrox_रेजिस्टर_पूर्णांकerrupts(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->pdev;
	काष्ठा nitrox_q_vector *qvec;
	पूर्णांक nr_vecs, vec, cpu;
	पूर्णांक ret, i;

	/*
	 * PF MSI-X vectors
	 *
	 * Entry 0: NPS PKT ring 0
	 * Entry 1: AQMQ ring 0
	 * Entry 2: ZQM ring 0
	 * Entry 3: NPS PKT ring 1
	 * Entry 4: AQMQ ring 1
	 * Entry 5: ZQM ring 1
	 * ....
	 * Entry 192: NPS_CORE_INT_ACTIVE
	 */
	nr_vecs = pci_msix_vec_count(pdev);

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(pdev, nr_vecs, nr_vecs, PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dev_err(DEV(ndev), "msix vectors %d alloc failed\n", nr_vecs);
		वापस ret;
	पूर्ण
	ndev->num_vecs = nr_vecs;

	ndev->qvec = kसुस्मृति(nr_vecs, माप(*qvec), GFP_KERNEL);
	अगर (!ndev->qvec) अणु
		pci_मुक्त_irq_vectors(pdev);
		वापस -ENOMEM;
	पूर्ण

	/* request irqs क्रम packet rings/ports */
	क्रम (i = PKT_RING_MSIX_BASE; i < (nr_vecs - 1); i += NR_RING_VECTORS) अणु
		qvec = &ndev->qvec[i];

		qvec->ring = i / NR_RING_VECTORS;
		अगर (qvec->ring >= ndev->nr_queues)
			अवरोध;

		qvec->cmdq = &ndev->pkt_inq[qvec->ring];
		snम_लिखो(qvec->name, IRQ_NAMESZ, "nitrox-pkt%d", qvec->ring);
		/* get the vector number */
		vec = pci_irq_vector(pdev, i);
		ret = request_irq(vec, nps_pkt_slc_isr, 0, qvec->name, qvec);
		अगर (ret) अणु
			dev_err(DEV(ndev), "irq failed for pkt ring/port%d\n",
				qvec->ring);
			जाओ irq_fail;
		पूर्ण
		cpu = qvec->ring % num_online_cpus();
		irq_set_affinity_hपूर्णांक(vec, get_cpu_mask(cpu));

		tasklet_init(&qvec->resp_tasklet, pkt_slc_resp_tasklet,
			     (अचिन्हित दीर्घ)qvec);
		qvec->valid = true;
	पूर्ण

	/* request irqs क्रम non ring vectors */
	i = NON_RING_MSIX_BASE;
	qvec = &ndev->qvec[i];
	qvec->ndev = ndev;

	snम_लिखो(qvec->name, IRQ_NAMESZ, "nitrox-core-int%d", i);
	/* get the vector number */
	vec = pci_irq_vector(pdev, i);
	ret = request_irq(vec, nps_core_पूर्णांक_isr, 0, qvec->name, qvec);
	अगर (ret) अणु
		dev_err(DEV(ndev), "irq failed for nitrox-core-int%d\n", i);
		जाओ irq_fail;
	पूर्ण
	cpu = num_online_cpus();
	irq_set_affinity_hपूर्णांक(vec, get_cpu_mask(cpu));

	tasklet_init(&qvec->resp_tasklet, nps_core_पूर्णांक_tasklet,
		     (अचिन्हित दीर्घ)qvec);
	qvec->valid = true;

	वापस 0;

irq_fail:
	nitrox_unरेजिस्टर_पूर्णांकerrupts(ndev);
	वापस ret;
पूर्ण

व्योम nitrox_sriov_unरेजिस्टर_पूर्णांकerrupts(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < ndev->num_vecs; i++) अणु
		काष्ठा nitrox_q_vector *qvec;
		पूर्णांक vec;

		qvec = ndev->qvec + i;
		अगर (!qvec->valid)
			जारी;

		vec = ndev->iov.msix.vector;
		irq_set_affinity_hपूर्णांक(vec, शून्य);
		मुक्त_irq(vec, qvec);

		tasklet_disable(&qvec->resp_tasklet);
		tasklet_समाप्त(&qvec->resp_tasklet);
		qvec->valid = false;
	पूर्ण
	kमुक्त(ndev->qvec);
	ndev->qvec = शून्य;
	pci_disable_msix(pdev);
पूर्ण

पूर्णांक nitrox_sriov_रेजिस्टर_पूर्णांकerupts(काष्ठा nitrox_device *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->pdev;
	काष्ठा nitrox_q_vector *qvec;
	पूर्णांक vec, cpu;
	पूर्णांक ret;

	/**
	 * only non ring vectors i.e Entry 192 is available
	 * क्रम PF in SR-IOV mode.
	 */
	ndev->iov.msix.entry = NON_RING_MSIX_BASE;
	ret = pci_enable_msix_exact(pdev, &ndev->iov.msix, NR_NON_RING_VECTORS);
	अगर (ret) अणु
		dev_err(DEV(ndev), "failed to allocate nps-core-int%d\n",
			NON_RING_MSIX_BASE);
		वापस ret;
	पूर्ण

	qvec = kसुस्मृति(NR_NON_RING_VECTORS, माप(*qvec), GFP_KERNEL);
	अगर (!qvec) अणु
		pci_disable_msix(pdev);
		वापस -ENOMEM;
	पूर्ण
	qvec->ndev = ndev;

	ndev->qvec = qvec;
	ndev->num_vecs = NR_NON_RING_VECTORS;
	snम_लिखो(qvec->name, IRQ_NAMESZ, "nitrox-core-int%d",
		 NON_RING_MSIX_BASE);

	vec = ndev->iov.msix.vector;
	ret = request_irq(vec, nps_core_पूर्णांक_isr, 0, qvec->name, qvec);
	अगर (ret) अणु
		dev_err(DEV(ndev), "irq failed for nitrox-core-int%d\n",
			NON_RING_MSIX_BASE);
		जाओ iov_irq_fail;
	पूर्ण
	cpu = num_online_cpus();
	irq_set_affinity_hपूर्णांक(vec, get_cpu_mask(cpu));

	tasklet_init(&qvec->resp_tasklet, nps_core_पूर्णांक_tasklet,
		     (अचिन्हित दीर्घ)qvec);
	qvec->valid = true;

	वापस 0;

iov_irq_fail:
	nitrox_sriov_unरेजिस्टर_पूर्णांकerrupts(ndev);
	वापस ret;
पूर्ण
