<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "iavf.h"
#समावेश "iavf_prototype.h"
#समावेश "iavf_client.h"
/* All iavf tracepoपूर्णांकs are defined by the include below, which must
 * be included exactly once across the whole kernel with
 * CREATE_TRACE_POINTS defined
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "iavf_trace.h"

अटल पूर्णांक iavf_setup_all_tx_resources(काष्ठा iavf_adapter *adapter);
अटल पूर्णांक iavf_setup_all_rx_resources(काष्ठा iavf_adapter *adapter);
अटल पूर्णांक iavf_बंद(काष्ठा net_device *netdev);
अटल पूर्णांक iavf_init_get_resources(काष्ठा iavf_adapter *adapter);
अटल पूर्णांक iavf_check_reset_complete(काष्ठा iavf_hw *hw);

अक्षर iavf_driver_name[] = "iavf";
अटल स्थिर अक्षर iavf_driver_string[] =
	"Intel(R) Ethernet Adaptive Virtual Function Network Driver";

अटल स्थिर अक्षर iavf_copyright[] =
	"Copyright (c) 2013 - 2018 Intel Corporation.";

/* iavf_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id iavf_pci_tbl[] = अणु
	अणुPCI_VDEVICE(INTEL, IAVF_DEV_ID_VF), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, IAVF_DEV_ID_VF_HV), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, IAVF_DEV_ID_X722_VF), 0पूर्ण,
	अणुPCI_VDEVICE(INTEL, IAVF_DEV_ID_ADAPTIVE_VF), 0पूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, iavf_pci_tbl);

MODULE_ALIAS("i40evf");
MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION("Intel(R) Ethernet Adaptive Virtual Function Network Driver");
MODULE_LICENSE("GPL v2");

अटल स्थिर काष्ठा net_device_ops iavf_netdev_ops;
काष्ठा workqueue_काष्ठा *iavf_wq;

/**
 * iavf_allocate_dma_mem_d - OS specअगरic memory alloc क्रम shared code
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to fill out
 * @size: size of memory requested
 * @alignment: what to align the allocation to
 **/
क्रमागत iavf_status iavf_allocate_dma_mem_d(काष्ठा iavf_hw *hw,
					 काष्ठा iavf_dma_mem *mem,
					 u64 size, u32 alignment)
अणु
	काष्ठा iavf_adapter *adapter = (काष्ठा iavf_adapter *)hw->back;

	अगर (!mem)
		वापस IAVF_ERR_PARAM;

	mem->size = ALIGN(size, alignment);
	mem->va = dma_alloc_coherent(&adapter->pdev->dev, mem->size,
				     (dma_addr_t *)&mem->pa, GFP_KERNEL);
	अगर (mem->va)
		वापस 0;
	अन्यथा
		वापस IAVF_ERR_NO_MEMORY;
पूर्ण

/**
 * iavf_मुक्त_dma_mem_d - OS specअगरic memory मुक्त क्रम shared code
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to मुक्त
 **/
क्रमागत iavf_status iavf_मुक्त_dma_mem_d(काष्ठा iavf_hw *hw,
				     काष्ठा iavf_dma_mem *mem)
अणु
	काष्ठा iavf_adapter *adapter = (काष्ठा iavf_adapter *)hw->back;

	अगर (!mem || !mem->va)
		वापस IAVF_ERR_PARAM;
	dma_मुक्त_coherent(&adapter->pdev->dev, mem->size,
			  mem->va, (dma_addr_t)mem->pa);
	वापस 0;
पूर्ण

/**
 * iavf_allocate_virt_mem_d - OS specअगरic memory alloc क्रम shared code
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to fill out
 * @size: size of memory requested
 **/
क्रमागत iavf_status iavf_allocate_virt_mem_d(काष्ठा iavf_hw *hw,
					  काष्ठा iavf_virt_mem *mem, u32 size)
अणु
	अगर (!mem)
		वापस IAVF_ERR_PARAM;

	mem->size = size;
	mem->va = kzalloc(size, GFP_KERNEL);

	अगर (mem->va)
		वापस 0;
	अन्यथा
		वापस IAVF_ERR_NO_MEMORY;
पूर्ण

/**
 * iavf_मुक्त_virt_mem_d - OS specअगरic memory मुक्त क्रम shared code
 * @hw:   poपूर्णांकer to the HW काष्ठाure
 * @mem:  ptr to mem काष्ठा to मुक्त
 **/
क्रमागत iavf_status iavf_मुक्त_virt_mem_d(काष्ठा iavf_hw *hw,
				      काष्ठा iavf_virt_mem *mem)
अणु
	अगर (!mem)
		वापस IAVF_ERR_PARAM;

	/* it's ok to kमुक्त a शून्य poपूर्णांकer */
	kमुक्त(mem->va);

	वापस 0;
पूर्ण

/**
 * iavf_schedule_reset - Set the flags and schedule a reset event
 * @adapter: board निजी काष्ठाure
 **/
व्योम iavf_schedule_reset(काष्ठा iavf_adapter *adapter)
अणु
	अगर (!(adapter->flags &
	      (IAVF_FLAG_RESET_PENDING | IAVF_FLAG_RESET_NEEDED))) अणु
		adapter->flags |= IAVF_FLAG_RESET_NEEDED;
		queue_work(iavf_wq, &adapter->reset_task);
	पूर्ण
पूर्ण

/**
 * iavf_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: queue number that is timing out
 **/
अटल व्योम iavf_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	adapter->tx_समयout_count++;
	iavf_schedule_reset(adapter);
पूर्ण

/**
 * iavf_misc_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_misc_irq_disable(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;

	अगर (!adapter->msix_entries)
		वापस;

	wr32(hw, IAVF_VFINT_DYN_CTL01, 0);

	iavf_flush(hw);

	synchronize_irq(adapter->msix_entries[0].vector);
पूर्ण

/**
 * iavf_misc_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_misc_irq_enable(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;

	wr32(hw, IAVF_VFINT_DYN_CTL01, IAVF_VFINT_DYN_CTL01_INTENA_MASK |
				       IAVF_VFINT_DYN_CTL01_ITR_INDX_MASK);
	wr32(hw, IAVF_VFINT_ICR0_ENA1, IAVF_VFINT_ICR0_ENA1_ADMINQ_MASK);

	iavf_flush(hw);
पूर्ण

/**
 * iavf_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_irq_disable(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक i;
	काष्ठा iavf_hw *hw = &adapter->hw;

	अगर (!adapter->msix_entries)
		वापस;

	क्रम (i = 1; i < adapter->num_msix_vectors; i++) अणु
		wr32(hw, IAVF_VFINT_DYN_CTLN1(i - 1), 0);
		synchronize_irq(adapter->msix_entries[i].vector);
	पूर्ण
	iavf_flush(hw);
पूर्ण

/**
 * iavf_irq_enable_queues - Enable पूर्णांकerrupt क्रम specअगरied queues
 * @adapter: board निजी काष्ठाure
 * @mask: biपंचांगap of queues to enable
 **/
व्योम iavf_irq_enable_queues(काष्ठा iavf_adapter *adapter, u32 mask)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 1; i < adapter->num_msix_vectors; i++) अणु
		अगर (mask & BIT(i - 1)) अणु
			wr32(hw, IAVF_VFINT_DYN_CTLN1(i - 1),
			     IAVF_VFINT_DYN_CTLN1_INTENA_MASK |
			     IAVF_VFINT_DYN_CTLN1_ITR_INDX_MASK);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * iavf_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 * @flush: boolean value whether to run rd32()
 **/
व्योम iavf_irq_enable(काष्ठा iavf_adapter *adapter, bool flush)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;

	iavf_misc_irq_enable(adapter);
	iavf_irq_enable_queues(adapter, ~0);

	अगर (flush)
		iavf_flush(hw);
पूर्ण

/**
 * iavf_msix_aq - Interrupt handler क्रम vector 0
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to netdev
 **/
अटल irqवापस_t iavf_msix_aq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	काष्ठा iavf_hw *hw = &adapter->hw;

	/* handle non-queue पूर्णांकerrupts, these पढ़ोs clear the रेजिस्टरs */
	rd32(hw, IAVF_VFINT_ICR01);
	rd32(hw, IAVF_VFINT_ICR0_ENA1);

	/* schedule work on the निजी workqueue */
	queue_work(iavf_wq, &adapter->adminq_task);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * iavf_msix_clean_rings - MSIX mode Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a q_vector
 **/
अटल irqवापस_t iavf_msix_clean_rings(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iavf_q_vector *q_vector = data;

	अगर (!q_vector->tx.ring && !q_vector->rx.ring)
		वापस IRQ_HANDLED;

	napi_schedule_irqoff(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * iavf_map_vector_to_rxq - associate irqs with rx queues
 * @adapter: board निजी काष्ठाure
 * @v_idx: पूर्णांकerrupt number
 * @r_idx: queue number
 **/
अटल व्योम
iavf_map_vector_to_rxq(काष्ठा iavf_adapter *adapter, पूर्णांक v_idx, पूर्णांक r_idx)
अणु
	काष्ठा iavf_q_vector *q_vector = &adapter->q_vectors[v_idx];
	काष्ठा iavf_ring *rx_ring = &adapter->rx_rings[r_idx];
	काष्ठा iavf_hw *hw = &adapter->hw;

	rx_ring->q_vector = q_vector;
	rx_ring->next = q_vector->rx.ring;
	rx_ring->vsi = &adapter->vsi;
	q_vector->rx.ring = rx_ring;
	q_vector->rx.count++;
	q_vector->rx.next_update = jअगरfies + 1;
	q_vector->rx.target_itr = ITR_TO_REG(rx_ring->itr_setting);
	q_vector->ring_mask |= BIT(r_idx);
	wr32(hw, IAVF_VFINT_ITRN1(IAVF_RX_ITR, q_vector->reg_idx),
	     q_vector->rx.current_itr >> 1);
	q_vector->rx.current_itr = q_vector->rx.target_itr;
पूर्ण

/**
 * iavf_map_vector_to_txq - associate irqs with tx queues
 * @adapter: board निजी काष्ठाure
 * @v_idx: पूर्णांकerrupt number
 * @t_idx: queue number
 **/
अटल व्योम
iavf_map_vector_to_txq(काष्ठा iavf_adapter *adapter, पूर्णांक v_idx, पूर्णांक t_idx)
अणु
	काष्ठा iavf_q_vector *q_vector = &adapter->q_vectors[v_idx];
	काष्ठा iavf_ring *tx_ring = &adapter->tx_rings[t_idx];
	काष्ठा iavf_hw *hw = &adapter->hw;

	tx_ring->q_vector = q_vector;
	tx_ring->next = q_vector->tx.ring;
	tx_ring->vsi = &adapter->vsi;
	q_vector->tx.ring = tx_ring;
	q_vector->tx.count++;
	q_vector->tx.next_update = jअगरfies + 1;
	q_vector->tx.target_itr = ITR_TO_REG(tx_ring->itr_setting);
	q_vector->num_ringpairs++;
	wr32(hw, IAVF_VFINT_ITRN1(IAVF_TX_ITR, q_vector->reg_idx),
	     q_vector->tx.target_itr >> 1);
	q_vector->tx.current_itr = q_vector->tx.target_itr;
पूर्ण

/**
 * iavf_map_rings_to_vectors - Maps descriptor rings to vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * This function maps descriptor rings to the queue-specअगरic vectors
 * we were allotted through the MSI-X enabling code.  Ideally, we'd have
 * one vector per ring/queue, but on a स्थिरrained vector budget, we
 * group the rings as "efficiently" as possible.  You would add new
 * mapping configurations in here.
 **/
अटल व्योम iavf_map_rings_to_vectors(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक rings_reमुख्यing = adapter->num_active_queues;
	पूर्णांक ridx = 0, vidx = 0;
	पूर्णांक q_vectors;

	q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	क्रम (; ridx < rings_reमुख्यing; ridx++) अणु
		iavf_map_vector_to_rxq(adapter, vidx, ridx);
		iavf_map_vector_to_txq(adapter, vidx, ridx);

		/* In the हाल where we have more queues than vectors, जारी
		 * round-robin on vectors until all queues are mapped.
		 */
		अगर (++vidx >= q_vectors)
			vidx = 0;
	पूर्ण

	adapter->aq_required |= IAVF_FLAG_AQ_MAP_VECTORS;
पूर्ण

/**
 * iavf_irq_affinity_notअगरy - Callback क्रम affinity changes
 * @notअगरy: context as to what irq was changed
 * @mask: the new affinity mask
 *
 * This is a callback function used by the irq_set_affinity_notअगरier function
 * so that we may रेजिस्टर to receive changes to the irq affinity masks.
 **/
अटल व्योम iavf_irq_affinity_notअगरy(काष्ठा irq_affinity_notअगरy *notअगरy,
				     स्थिर cpumask_t *mask)
अणु
	काष्ठा iavf_q_vector *q_vector =
		container_of(notअगरy, काष्ठा iavf_q_vector, affinity_notअगरy);

	cpumask_copy(&q_vector->affinity_mask, mask);
पूर्ण

/**
 * iavf_irq_affinity_release - Callback क्रम affinity notअगरier release
 * @ref: पूर्णांकernal core kernel usage
 *
 * This is a callback function used by the irq_set_affinity_notअगरier function
 * to inक्रमm the current notअगरication subscriber that they will no दीर्घer
 * receive notअगरications.
 **/
अटल व्योम iavf_irq_affinity_release(काष्ठा kref *ref) अणुपूर्ण

/**
 * iavf_request_traffic_irqs - Initialize MSI-X पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 * @basename: device basename
 *
 * Allocates MSI-X vectors क्रम tx and rx handling, and requests
 * पूर्णांकerrupts from the kernel.
 **/
अटल पूर्णांक
iavf_request_traffic_irqs(काष्ठा iavf_adapter *adapter, अक्षर *basename)
अणु
	अचिन्हित पूर्णांक vector, q_vectors;
	अचिन्हित पूर्णांक rx_पूर्णांक_idx = 0, tx_पूर्णांक_idx = 0;
	पूर्णांक irq_num, err;
	पूर्णांक cpu;

	iavf_irq_disable(adapter);
	/* Decrement क्रम Other and TCP Timer vectors */
	q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	क्रम (vector = 0; vector < q_vectors; vector++) अणु
		काष्ठा iavf_q_vector *q_vector = &adapter->q_vectors[vector];

		irq_num = adapter->msix_entries[vector + NONQ_VECS].vector;

		अगर (q_vector->tx.ring && q_vector->rx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "iavf-%s-TxRx-%d", basename, rx_पूर्णांक_idx++);
			tx_पूर्णांक_idx++;
		पूर्ण अन्यथा अगर (q_vector->rx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "iavf-%s-rx-%d", basename, rx_पूर्णांक_idx++);
		पूर्ण अन्यथा अगर (q_vector->tx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "iavf-%s-tx-%d", basename, tx_पूर्णांक_idx++);
		पूर्ण अन्यथा अणु
			/* skip this unused q_vector */
			जारी;
		पूर्ण
		err = request_irq(irq_num,
				  iavf_msix_clean_rings,
				  0,
				  q_vector->name,
				  q_vector);
		अगर (err) अणु
			dev_info(&adapter->pdev->dev,
				 "Request_irq failed, error: %d\n", err);
			जाओ मुक्त_queue_irqs;
		पूर्ण
		/* रेजिस्टर क्रम affinity change notअगरications */
		q_vector->affinity_notअगरy.notअगरy = iavf_irq_affinity_notअगरy;
		q_vector->affinity_notअगरy.release =
						   iavf_irq_affinity_release;
		irq_set_affinity_notअगरier(irq_num, &q_vector->affinity_notअगरy);
		/* Spपढ़ो the IRQ affinity hपूर्णांकs across online CPUs. Note that
		 * get_cpu_mask वापसs a mask with a permanent lअगरeसमय so
		 * it's safe to use as a hपूर्णांक क्रम irq_set_affinity_hपूर्णांक.
		 */
		cpu = cpumask_local_spपढ़ो(q_vector->v_idx, -1);
		irq_set_affinity_hपूर्णांक(irq_num, get_cpu_mask(cpu));
	पूर्ण

	वापस 0;

मुक्त_queue_irqs:
	जबतक (vector) अणु
		vector--;
		irq_num = adapter->msix_entries[vector + NONQ_VECS].vector;
		irq_set_affinity_notअगरier(irq_num, शून्य);
		irq_set_affinity_hपूर्णांक(irq_num, शून्य);
		मुक्त_irq(irq_num, &adapter->q_vectors[vector]);
	पूर्ण
	वापस err;
पूर्ण

/**
 * iavf_request_misc_irq - Initialize MSI-X पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * Allocates MSI-X vector 0 and requests पूर्णांकerrupts from the kernel. This
 * vector is only क्रम the admin queue, and stays active even when the netdev
 * is बंदd.
 **/
अटल पूर्णांक iavf_request_misc_irq(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	snम_लिखो(adapter->misc_vector_name,
		 माप(adapter->misc_vector_name) - 1, "iavf-%s:mbx",
		 dev_name(&adapter->pdev->dev));
	err = request_irq(adapter->msix_entries[0].vector,
			  &iavf_msix_aq, 0,
			  adapter->misc_vector_name, netdev);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"request_irq for %s failed: %d\n",
			adapter->misc_vector_name, err);
		मुक्त_irq(adapter->msix_entries[0].vector, netdev);
	पूर्ण
	वापस err;
पूर्ण

/**
 * iavf_मुक्त_traffic_irqs - Free MSI-X पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * Frees all MSI-X vectors other than 0.
 **/
अटल व्योम iavf_मुक्त_traffic_irqs(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक vector, irq_num, q_vectors;

	अगर (!adapter->msix_entries)
		वापस;

	q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	क्रम (vector = 0; vector < q_vectors; vector++) अणु
		irq_num = adapter->msix_entries[vector + NONQ_VECS].vector;
		irq_set_affinity_notअगरier(irq_num, शून्य);
		irq_set_affinity_hपूर्णांक(irq_num, शून्य);
		मुक्त_irq(irq_num, &adapter->q_vectors[vector]);
	पूर्ण
पूर्ण

/**
 * iavf_मुक्त_misc_irq - Free MSI-X miscellaneous vector
 * @adapter: board निजी काष्ठाure
 *
 * Frees MSI-X vector 0.
 **/
अटल व्योम iavf_मुक्त_misc_irq(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (!adapter->msix_entries)
		वापस;

	मुक्त_irq(adapter->msix_entries[0].vector, netdev);
पूर्ण

/**
 * iavf_configure_tx - Configure Transmit Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/
अटल व्योम iavf_configure_tx(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_active_queues; i++)
		adapter->tx_rings[i].tail = hw->hw_addr + IAVF_QTX_TAIL1(i);
पूर्ण

/**
 * iavf_configure_rx - Configure Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/
अटल व्योम iavf_configure_rx(काष्ठा iavf_adapter *adapter)
अणु
	अचिन्हित पूर्णांक rx_buf_len = IAVF_RXBUFFER_2048;
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक i;

	/* Legacy Rx will always शेष to a 2048 buffer size. */
#अगर (PAGE_SIZE < 8192)
	अगर (!(adapter->flags & IAVF_FLAG_LEGACY_RX)) अणु
		काष्ठा net_device *netdev = adapter->netdev;

		/* For jumbo frames on प्रणालीs with 4K pages we have to use
		 * an order 1 page, so we might as well increase the size
		 * of our Rx buffer to make better use of the available space
		 */
		rx_buf_len = IAVF_RXBUFFER_3072;

		/* We use a 1536 buffer size क्रम configurations with
		 * standard Ethernet mtu.  On x86 this gives us enough room
		 * क्रम shared info and 192 bytes of padding.
		 */
		अगर (!IAVF_2K_TOO_SMALL_WITH_PADDING &&
		    (netdev->mtu <= ETH_DATA_LEN))
			rx_buf_len = IAVF_RXBUFFER_1536 - NET_IP_ALIGN;
	पूर्ण
#पूर्ण_अगर

	क्रम (i = 0; i < adapter->num_active_queues; i++) अणु
		adapter->rx_rings[i].tail = hw->hw_addr + IAVF_QRX_TAIL1(i);
		adapter->rx_rings[i].rx_buf_len = rx_buf_len;

		अगर (adapter->flags & IAVF_FLAG_LEGACY_RX)
			clear_ring_build_skb_enabled(&adapter->rx_rings[i]);
		अन्यथा
			set_ring_build_skb_enabled(&adapter->rx_rings[i]);
	पूर्ण
पूर्ण

/**
 * iavf_find_vlan - Search filter list क्रम specअगरic vlan filter
 * @adapter: board निजी काष्ठाure
 * @vlan: vlan tag
 *
 * Returns ptr to the filter object or शून्य. Must be called जबतक holding the
 * mac_vlan_list_lock.
 **/
अटल काष्ठा
iavf_vlan_filter *iavf_find_vlan(काष्ठा iavf_adapter *adapter, u16 vlan)
अणु
	काष्ठा iavf_vlan_filter *f;

	list_क्रम_each_entry(f, &adapter->vlan_filter_list, list) अणु
		अगर (vlan == f->vlan)
			वापस f;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * iavf_add_vlan - Add a vlan filter to the list
 * @adapter: board निजी काष्ठाure
 * @vlan: VLAN tag
 *
 * Returns ptr to the filter object or शून्य when no memory available.
 **/
अटल काष्ठा
iavf_vlan_filter *iavf_add_vlan(काष्ठा iavf_adapter *adapter, u16 vlan)
अणु
	काष्ठा iavf_vlan_filter *f = शून्य;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	f = iavf_find_vlan(adapter, vlan);
	अगर (!f) अणु
		f = kzalloc(माप(*f), GFP_ATOMIC);
		अगर (!f)
			जाओ clearout;

		f->vlan = vlan;

		list_add_tail(&f->list, &adapter->vlan_filter_list);
		f->add = true;
		adapter->aq_required |= IAVF_FLAG_AQ_ADD_VLAN_FILTER;
	पूर्ण

clearout:
	spin_unlock_bh(&adapter->mac_vlan_list_lock);
	वापस f;
पूर्ण

/**
 * iavf_del_vlan - Remove a vlan filter from the list
 * @adapter: board निजी काष्ठाure
 * @vlan: VLAN tag
 **/
अटल व्योम iavf_del_vlan(काष्ठा iavf_adapter *adapter, u16 vlan)
अणु
	काष्ठा iavf_vlan_filter *f;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	f = iavf_find_vlan(adapter, vlan);
	अगर (f) अणु
		f->हटाओ = true;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_VLAN_FILTER;
	पूर्ण

	spin_unlock_bh(&adapter->mac_vlan_list_lock);
पूर्ण

/**
 * iavf_vlan_rx_add_vid - Add a VLAN filter to a device
 * @netdev: network device काष्ठा
 * @proto: unused protocol data
 * @vid: VLAN tag
 **/
अटल पूर्णांक iavf_vlan_rx_add_vid(काष्ठा net_device *netdev,
				__always_unused __be16 proto, u16 vid)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	अगर (!VLAN_ALLOWED(adapter))
		वापस -EIO;
	अगर (iavf_add_vlan(adapter, vid) == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * iavf_vlan_rx_समाप्त_vid - Remove a VLAN filter from a device
 * @netdev: network device काष्ठा
 * @proto: unused protocol data
 * @vid: VLAN tag
 **/
अटल पूर्णांक iavf_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				 __always_unused __be16 proto, u16 vid)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	अगर (VLAN_ALLOWED(adapter)) अणु
		iavf_del_vlan(adapter, vid);
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

/**
 * iavf_find_filter - Search filter list क्रम specअगरic mac filter
 * @adapter: board निजी काष्ठाure
 * @macaddr: the MAC address
 *
 * Returns ptr to the filter object or शून्य. Must be called जबतक holding the
 * mac_vlan_list_lock.
 **/
अटल काष्ठा
iavf_mac_filter *iavf_find_filter(काष्ठा iavf_adapter *adapter,
				  स्थिर u8 *macaddr)
अणु
	काष्ठा iavf_mac_filter *f;

	अगर (!macaddr)
		वापस शून्य;

	list_क्रम_each_entry(f, &adapter->mac_filter_list, list) अणु
		अगर (ether_addr_equal(macaddr, f->macaddr))
			वापस f;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * iavf_add_filter - Add a mac filter to the filter list
 * @adapter: board निजी काष्ठाure
 * @macaddr: the MAC address
 *
 * Returns ptr to the filter object or शून्य when no memory available.
 **/
काष्ठा iavf_mac_filter *iavf_add_filter(काष्ठा iavf_adapter *adapter,
					स्थिर u8 *macaddr)
अणु
	काष्ठा iavf_mac_filter *f;

	अगर (!macaddr)
		वापस शून्य;

	f = iavf_find_filter(adapter, macaddr);
	अगर (!f) अणु
		f = kzalloc(माप(*f), GFP_ATOMIC);
		अगर (!f)
			वापस f;

		ether_addr_copy(f->macaddr, macaddr);

		list_add_tail(&f->list, &adapter->mac_filter_list);
		f->add = true;
		adapter->aq_required |= IAVF_FLAG_AQ_ADD_MAC_FILTER;
	पूर्ण अन्यथा अणु
		f->हटाओ = false;
	पूर्ण

	वापस f;
पूर्ण

/**
 * iavf_set_mac - NDO callback to set port mac address
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक iavf_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	काष्ठा iavf_hw *hw = &adapter->hw;
	काष्ठा iavf_mac_filter *f;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (ether_addr_equal(netdev->dev_addr, addr->sa_data))
		वापस 0;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	f = iavf_find_filter(adapter, hw->mac.addr);
	अगर (f) अणु
		f->हटाओ = true;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_MAC_FILTER;
	पूर्ण

	f = iavf_add_filter(adapter, addr->sa_data);

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	अगर (f) अणु
		ether_addr_copy(hw->mac.addr, addr->sa_data);
	पूर्ण

	वापस (f == शून्य) ? -ENOMEM : 0;
पूर्ण

/**
 * iavf_addr_sync - Callback क्रम dev_(mc|uc)_sync to add address
 * @netdev: the netdevice
 * @addr: address to add
 *
 * Called by __dev_(mc|uc)_sync when an address needs to be added. We call
 * __dev_(uc|mc)_sync from .set_rx_mode and guarantee to hold the hash lock.
 */
अटल पूर्णांक iavf_addr_sync(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	अगर (iavf_add_filter(adapter, addr))
		वापस 0;
	अन्यथा
		वापस -ENOMEM;
पूर्ण

/**
 * iavf_addr_unsync - Callback क्रम dev_(mc|uc)_sync to हटाओ address
 * @netdev: the netdevice
 * @addr: address to add
 *
 * Called by __dev_(mc|uc)_sync when an address needs to be हटाओd. We call
 * __dev_(uc|mc)_sync from .set_rx_mode and guarantee to hold the hash lock.
 */
अटल पूर्णांक iavf_addr_unsync(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	काष्ठा iavf_mac_filter *f;

	/* Under some circumstances, we might receive a request to delete
	 * our own device address from our uc list. Because we store the
	 * device address in the VSI's MAC/VLAN filter list, we need to ignore
	 * such requests and not delete our device address from this list.
	 */
	अगर (ether_addr_equal(addr, netdev->dev_addr))
		वापस 0;

	f = iavf_find_filter(adapter, addr);
	अगर (f) अणु
		f->हटाओ = true;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_MAC_FILTER;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * iavf_set_rx_mode - NDO callback to set the netdev filters
 * @netdev: network पूर्णांकerface device काष्ठाure
 **/
अटल व्योम iavf_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	spin_lock_bh(&adapter->mac_vlan_list_lock);
	__dev_uc_sync(netdev, iavf_addr_sync, iavf_addr_unsync);
	__dev_mc_sync(netdev, iavf_addr_sync, iavf_addr_unsync);
	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	अगर (netdev->flags & IFF_PROMISC &&
	    !(adapter->flags & IAVF_FLAG_PROMISC_ON))
		adapter->aq_required |= IAVF_FLAG_AQ_REQUEST_PROMISC;
	अन्यथा अगर (!(netdev->flags & IFF_PROMISC) &&
		 adapter->flags & IAVF_FLAG_PROMISC_ON)
		adapter->aq_required |= IAVF_FLAG_AQ_RELEASE_PROMISC;

	अगर (netdev->flags & IFF_ALLMULTI &&
	    !(adapter->flags & IAVF_FLAG_ALLMULTI_ON))
		adapter->aq_required |= IAVF_FLAG_AQ_REQUEST_ALLMULTI;
	अन्यथा अगर (!(netdev->flags & IFF_ALLMULTI) &&
		 adapter->flags & IAVF_FLAG_ALLMULTI_ON)
		adapter->aq_required |= IAVF_FLAG_AQ_RELEASE_ALLMULTI;
पूर्ण

/**
 * iavf_napi_enable_all - enable NAPI on all queue vectors
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_napi_enable_all(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक q_idx;
	काष्ठा iavf_q_vector *q_vector;
	पूर्णांक q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	क्रम (q_idx = 0; q_idx < q_vectors; q_idx++) अणु
		काष्ठा napi_काष्ठा *napi;

		q_vector = &adapter->q_vectors[q_idx];
		napi = &q_vector->napi;
		napi_enable(napi);
	पूर्ण
पूर्ण

/**
 * iavf_napi_disable_all - disable NAPI on all queue vectors
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_napi_disable_all(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक q_idx;
	काष्ठा iavf_q_vector *q_vector;
	पूर्णांक q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	क्रम (q_idx = 0; q_idx < q_vectors; q_idx++) अणु
		q_vector = &adapter->q_vectors[q_idx];
		napi_disable(&q_vector->napi);
	पूर्ण
पूर्ण

/**
 * iavf_configure - set up transmit and receive data काष्ठाures
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_configure(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i;

	iavf_set_rx_mode(netdev);

	iavf_configure_tx(adapter);
	iavf_configure_rx(adapter);
	adapter->aq_required |= IAVF_FLAG_AQ_CONFIGURE_QUEUES;

	क्रम (i = 0; i < adapter->num_active_queues; i++) अणु
		काष्ठा iavf_ring *ring = &adapter->rx_rings[i];

		iavf_alloc_rx_buffers(ring, IAVF_DESC_UNUSED(ring));
	पूर्ण
पूर्ण

/**
 * iavf_up_complete - Finish the last steps of bringing up a connection
 * @adapter: board निजी काष्ठाure
 *
 * Expects to be called जबतक holding the __IAVF_IN_CRITICAL_TASK bit lock.
 **/
अटल व्योम iavf_up_complete(काष्ठा iavf_adapter *adapter)
अणु
	adapter->state = __IAVF_RUNNING;
	clear_bit(__IAVF_VSI_DOWN, adapter->vsi.state);

	iavf_napi_enable_all(adapter);

	adapter->aq_required |= IAVF_FLAG_AQ_ENABLE_QUEUES;
	अगर (CLIENT_ENABLED(adapter))
		adapter->flags |= IAVF_FLAG_CLIENT_NEEDS_OPEN;
	mod_delayed_work(iavf_wq, &adapter->watchकरोg_task, 0);
पूर्ण

/**
 * iavf_करोwn - Shutकरोwn the connection processing
 * @adapter: board निजी काष्ठाure
 *
 * Expects to be called जबतक holding the __IAVF_IN_CRITICAL_TASK bit lock.
 **/
व्योम iavf_करोwn(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा iavf_vlan_filter *vlf;
	काष्ठा iavf_cloud_filter *cf;
	काष्ठा iavf_fdir_fltr *fdir;
	काष्ठा iavf_mac_filter *f;
	काष्ठा iavf_adv_rss *rss;

	अगर (adapter->state <= __IAVF_DOWN_PENDING)
		वापस;

	netअगर_carrier_off(netdev);
	netअगर_tx_disable(netdev);
	adapter->link_up = false;
	iavf_napi_disable_all(adapter);
	iavf_irq_disable(adapter);

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	/* clear the sync flag on all filters */
	__dev_uc_unsync(adapter->netdev, शून्य);
	__dev_mc_unsync(adapter->netdev, शून्य);

	/* हटाओ all MAC filters */
	list_क्रम_each_entry(f, &adapter->mac_filter_list, list) अणु
		f->हटाओ = true;
	पूर्ण

	/* हटाओ all VLAN filters */
	list_क्रम_each_entry(vlf, &adapter->vlan_filter_list, list) अणु
		vlf->हटाओ = true;
	पूर्ण

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	/* हटाओ all cloud filters */
	spin_lock_bh(&adapter->cloud_filter_list_lock);
	list_क्रम_each_entry(cf, &adapter->cloud_filter_list, list) अणु
		cf->del = true;
	पूर्ण
	spin_unlock_bh(&adapter->cloud_filter_list_lock);

	/* हटाओ all Flow Director filters */
	spin_lock_bh(&adapter->fdir_fltr_lock);
	list_क्रम_each_entry(fdir, &adapter->fdir_list_head, list) अणु
		fdir->state = IAVF_Fसूची_FLTR_DEL_REQUEST;
	पूर्ण
	spin_unlock_bh(&adapter->fdir_fltr_lock);

	/* हटाओ all advance RSS configuration */
	spin_lock_bh(&adapter->adv_rss_lock);
	list_क्रम_each_entry(rss, &adapter->adv_rss_list_head, list)
		rss->state = IAVF_ADV_RSS_DEL_REQUEST;
	spin_unlock_bh(&adapter->adv_rss_lock);

	अगर (!(adapter->flags & IAVF_FLAG_PF_COMMS_FAILED) &&
	    adapter->state != __IAVF_RESETTING) अणु
		/* cancel any current operation */
		adapter->current_op = VIRTCHNL_OP_UNKNOWN;
		/* Schedule operations to बंद करोwn the HW. Don't रुको
		 * here क्रम this to complete. The watchकरोg is still running
		 * and it will take care of this.
		 */
		adapter->aq_required = IAVF_FLAG_AQ_DEL_MAC_FILTER;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_VLAN_FILTER;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_CLOUD_FILTER;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_Fसूची_FILTER;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_ADV_RSS_CFG;
		adapter->aq_required |= IAVF_FLAG_AQ_DISABLE_QUEUES;
	पूर्ण

	mod_delayed_work(iavf_wq, &adapter->watchकरोg_task, 0);
पूर्ण

/**
 * iavf_acquire_msix_vectors - Setup the MSIX capability
 * @adapter: board निजी काष्ठाure
 * @vectors: number of vectors to request
 *
 * Work with the OS to set up the MSIX vectors needed.
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक
iavf_acquire_msix_vectors(काष्ठा iavf_adapter *adapter, पूर्णांक vectors)
अणु
	पूर्णांक err, vector_threshold;

	/* We'll want at least 3 (vector_threshold):
	 * 0) Other (Admin Queue and link, mostly)
	 * 1) TxQ[0] Cleanup
	 * 2) RxQ[0] Cleanup
	 */
	vector_threshold = MIN_MSIX_COUNT;

	/* The more we get, the more we will assign to Tx/Rx Cleanup
	 * क्रम the separate queues...where Rx Cleanup >= Tx Cleanup.
	 * Right now, we simply care about how many we'll get; we'll
	 * set them up later जबतक requesting irq's.
	 */
	err = pci_enable_msix_range(adapter->pdev, adapter->msix_entries,
				    vector_threshold, vectors);
	अगर (err < 0) अणु
		dev_err(&adapter->pdev->dev, "Unable to allocate MSI-X interrupts\n");
		kमुक्त(adapter->msix_entries);
		adapter->msix_entries = शून्य;
		वापस err;
	पूर्ण

	/* Adjust क्रम only the vectors we'll use, which is minimum
	 * of max_msix_q_vectors + NONQ_VECS, or the number of
	 * vectors we were allocated.
	 */
	adapter->num_msix_vectors = err;
	वापस 0;
पूर्ण

/**
 * iavf_मुक्त_queues - Free memory क्रम all rings
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Free all of the memory associated with queue pairs.
 **/
अटल व्योम iavf_मुक्त_queues(काष्ठा iavf_adapter *adapter)
अणु
	अगर (!adapter->vsi_res)
		वापस;
	adapter->num_active_queues = 0;
	kमुक्त(adapter->tx_rings);
	adapter->tx_rings = शून्य;
	kमुक्त(adapter->rx_rings);
	adapter->rx_rings = शून्य;
पूर्ण

/**
 * iavf_alloc_queues - Allocate memory क्रम all rings
 * @adapter: board निजी काष्ठाure to initialize
 *
 * We allocate one ring per queue at run-समय since we करोn't know the
 * number of queues at compile-समय.  The polling_netdev array is
 * पूर्णांकended क्रम Multiqueue, but should work fine with a single queue.
 **/
अटल पूर्णांक iavf_alloc_queues(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक i, num_active_queues;

	/* If we're in reset reallocating queues we don't actually know yet क्रम
	 * certain the PF gave us the number of queues we asked क्रम but we'll
	 * assume it did.  Once basic reset is finished we'll confirm once we
	 * start negotiating config with PF.
	 */
	अगर (adapter->num_req_queues)
		num_active_queues = adapter->num_req_queues;
	अन्यथा अगर ((adapter->vf_res->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ADQ) &&
		 adapter->num_tc)
		num_active_queues = adapter->ch_config.total_qps;
	अन्यथा
		num_active_queues = min_t(पूर्णांक,
					  adapter->vsi_res->num_queue_pairs,
					  (पूर्णांक)(num_online_cpus()));


	adapter->tx_rings = kसुस्मृति(num_active_queues,
				    माप(काष्ठा iavf_ring), GFP_KERNEL);
	अगर (!adapter->tx_rings)
		जाओ err_out;
	adapter->rx_rings = kसुस्मृति(num_active_queues,
				    माप(काष्ठा iavf_ring), GFP_KERNEL);
	अगर (!adapter->rx_rings)
		जाओ err_out;

	क्रम (i = 0; i < num_active_queues; i++) अणु
		काष्ठा iavf_ring *tx_ring;
		काष्ठा iavf_ring *rx_ring;

		tx_ring = &adapter->tx_rings[i];

		tx_ring->queue_index = i;
		tx_ring->netdev = adapter->netdev;
		tx_ring->dev = &adapter->pdev->dev;
		tx_ring->count = adapter->tx_desc_count;
		tx_ring->itr_setting = IAVF_ITR_TX_DEF;
		अगर (adapter->flags & IAVF_FLAG_WB_ON_ITR_CAPABLE)
			tx_ring->flags |= IAVF_TXR_FLAGS_WB_ON_ITR;

		rx_ring = &adapter->rx_rings[i];
		rx_ring->queue_index = i;
		rx_ring->netdev = adapter->netdev;
		rx_ring->dev = &adapter->pdev->dev;
		rx_ring->count = adapter->rx_desc_count;
		rx_ring->itr_setting = IAVF_ITR_RX_DEF;
	पूर्ण

	adapter->num_active_queues = num_active_queues;

	वापस 0;

err_out:
	iavf_मुक्त_queues(adapter);
	वापस -ENOMEM;
पूर्ण

/**
 * iavf_set_पूर्णांकerrupt_capability - set MSI-X or FAIL अगर not supported
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Attempt to configure the पूर्णांकerrupts using the best available
 * capabilities of the hardware and the kernel.
 **/
अटल पूर्णांक iavf_set_पूर्णांकerrupt_capability(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक vector, v_budget;
	पूर्णांक pairs = 0;
	पूर्णांक err = 0;

	अगर (!adapter->vsi_res) अणु
		err = -EIO;
		जाओ out;
	पूर्ण
	pairs = adapter->num_active_queues;

	/* It's easy to be greedy for MSI-X vectors, but it really doesn't करो
	 * us much good अगर we have more vectors than CPUs. However, we alपढ़ोy
	 * limit the total number of queues by the number of CPUs so we करो not
	 * need any further limiting here.
	 */
	v_budget = min_t(पूर्णांक, pairs + NONQ_VECS,
			 (पूर्णांक)adapter->vf_res->max_vectors);

	adapter->msix_entries = kसुस्मृति(v_budget,
					माप(काष्ठा msix_entry), GFP_KERNEL);
	अगर (!adapter->msix_entries) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (vector = 0; vector < v_budget; vector++)
		adapter->msix_entries[vector].entry = vector;

	err = iavf_acquire_msix_vectors(adapter, v_budget);

out:
	netअगर_set_real_num_rx_queues(adapter->netdev, pairs);
	netअगर_set_real_num_tx_queues(adapter->netdev, pairs);
	वापस err;
पूर्ण

/**
 * iavf_config_rss_aq - Configure RSS keys and lut by using AQ commands
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक iavf_config_rss_aq(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_aqc_get_set_rss_key_data *rss_key =
		(काष्ठा iavf_aqc_get_set_rss_key_data *)adapter->rss_key;
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक ret = 0;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot configure RSS, command %d pending\n",
			adapter->current_op);
		वापस -EBUSY;
	पूर्ण

	ret = iavf_aq_set_rss_key(hw, adapter->vsi.id, rss_key);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev, "Cannot set RSS key, err %s aq_err %s\n",
			iavf_stat_str(hw, ret),
			iavf_aq_str(hw, hw->aq.asq_last_status));
		वापस ret;

	पूर्ण

	ret = iavf_aq_set_rss_lut(hw, adapter->vsi.id, false,
				  adapter->rss_lut, adapter->rss_lut_size);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev, "Cannot set RSS lut, err %s aq_err %s\n",
			iavf_stat_str(hw, ret),
			iavf_aq_str(hw, hw->aq.asq_last_status));
	पूर्ण

	वापस ret;

पूर्ण

/**
 * iavf_config_rss_reg - Configure RSS keys and lut by writing रेजिस्टरs
 * @adapter: board निजी काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक iavf_config_rss_reg(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;
	u32 *dw;
	u16 i;

	dw = (u32 *)adapter->rss_key;
	क्रम (i = 0; i <= adapter->rss_key_size / 4; i++)
		wr32(hw, IAVF_VFQF_HKEY(i), dw[i]);

	dw = (u32 *)adapter->rss_lut;
	क्रम (i = 0; i <= adapter->rss_lut_size / 4; i++)
		wr32(hw, IAVF_VFQF_HLUT(i), dw[i]);

	iavf_flush(hw);

	वापस 0;
पूर्ण

/**
 * iavf_config_rss - Configure RSS keys and lut
 * @adapter: board निजी काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
पूर्णांक iavf_config_rss(काष्ठा iavf_adapter *adapter)
अणु

	अगर (RSS_PF(adapter)) अणु
		adapter->aq_required |= IAVF_FLAG_AQ_SET_RSS_LUT |
					IAVF_FLAG_AQ_SET_RSS_KEY;
		वापस 0;
	पूर्ण अन्यथा अगर (RSS_AQ(adapter)) अणु
		वापस iavf_config_rss_aq(adapter);
	पूर्ण अन्यथा अणु
		वापस iavf_config_rss_reg(adapter);
	पूर्ण
पूर्ण

/**
 * iavf_fill_rss_lut - Fill the lut with शेष values
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_fill_rss_lut(काष्ठा iavf_adapter *adapter)
अणु
	u16 i;

	क्रम (i = 0; i < adapter->rss_lut_size; i++)
		adapter->rss_lut[i] = i % adapter->num_active_queues;
पूर्ण

/**
 * iavf_init_rss - Prepare क्रम RSS
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक iavf_init_rss(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक ret;

	अगर (!RSS_PF(adapter)) अणु
		/* Enable PCTYPES क्रम RSS, TCP/UDP with IPv4/IPv6 */
		अगर (adapter->vf_res->vf_cap_flags &
		    VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2)
			adapter->hena = IAVF_DEFAULT_RSS_HENA_EXPANDED;
		अन्यथा
			adapter->hena = IAVF_DEFAULT_RSS_HENA;

		wr32(hw, IAVF_VFQF_HENA(0), (u32)adapter->hena);
		wr32(hw, IAVF_VFQF_HENA(1), (u32)(adapter->hena >> 32));
	पूर्ण

	iavf_fill_rss_lut(adapter);
	netdev_rss_key_fill((व्योम *)adapter->rss_key, adapter->rss_key_size);
	ret = iavf_config_rss(adapter);

	वापस ret;
पूर्ण

/**
 * iavf_alloc_q_vectors - Allocate memory क्रम पूर्णांकerrupt vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * We allocate one q_vector per queue पूर्णांकerrupt.  If allocation fails we
 * वापस -ENOMEM.
 **/
अटल पूर्णांक iavf_alloc_q_vectors(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक q_idx = 0, num_q_vectors;
	काष्ठा iavf_q_vector *q_vector;

	num_q_vectors = adapter->num_msix_vectors - NONQ_VECS;
	adapter->q_vectors = kसुस्मृति(num_q_vectors, माप(*q_vector),
				     GFP_KERNEL);
	अगर (!adapter->q_vectors)
		वापस -ENOMEM;

	क्रम (q_idx = 0; q_idx < num_q_vectors; q_idx++) अणु
		q_vector = &adapter->q_vectors[q_idx];
		q_vector->adapter = adapter;
		q_vector->vsi = &adapter->vsi;
		q_vector->v_idx = q_idx;
		q_vector->reg_idx = q_idx;
		cpumask_copy(&q_vector->affinity_mask, cpu_possible_mask);
		netअगर_napi_add(adapter->netdev, &q_vector->napi,
			       iavf_napi_poll, NAPI_POLL_WEIGHT);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_मुक्त_q_vectors - Free memory allocated क्रम पूर्णांकerrupt vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * This function मुक्तs the memory allocated to the q_vectors.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 **/
अटल व्योम iavf_मुक्त_q_vectors(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक q_idx, num_q_vectors;
	पूर्णांक napi_vectors;

	अगर (!adapter->q_vectors)
		वापस;

	num_q_vectors = adapter->num_msix_vectors - NONQ_VECS;
	napi_vectors = adapter->num_active_queues;

	क्रम (q_idx = 0; q_idx < num_q_vectors; q_idx++) अणु
		काष्ठा iavf_q_vector *q_vector = &adapter->q_vectors[q_idx];

		अगर (q_idx < napi_vectors)
			netअगर_napi_del(&q_vector->napi);
	पूर्ण
	kमुक्त(adapter->q_vectors);
	adapter->q_vectors = शून्य;
पूर्ण

/**
 * iavf_reset_पूर्णांकerrupt_capability - Reset MSIX setup
 * @adapter: board निजी काष्ठाure
 *
 **/
व्योम iavf_reset_पूर्णांकerrupt_capability(काष्ठा iavf_adapter *adapter)
अणु
	अगर (!adapter->msix_entries)
		वापस;

	pci_disable_msix(adapter->pdev);
	kमुक्त(adapter->msix_entries);
	adapter->msix_entries = शून्य;
पूर्ण

/**
 * iavf_init_पूर्णांकerrupt_scheme - Determine अगर MSIX is supported and init
 * @adapter: board निजी काष्ठाure to initialize
 *
 **/
पूर्णांक iavf_init_पूर्णांकerrupt_scheme(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक err;

	err = iavf_alloc_queues(adapter);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Unable to allocate memory for queues\n");
		जाओ err_alloc_queues;
	पूर्ण

	rtnl_lock();
	err = iavf_set_पूर्णांकerrupt_capability(adapter);
	rtnl_unlock();
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Unable to setup interrupt capabilities\n");
		जाओ err_set_पूर्णांकerrupt;
	पूर्ण

	err = iavf_alloc_q_vectors(adapter);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Unable to allocate memory for queue vectors\n");
		जाओ err_alloc_q_vectors;
	पूर्ण

	/* If we've made it so far while ADq flag being ON, then we haven't
	 * bailed out anywhere in middle. And ADq isn't just enabled but actual
	 * resources have been allocated in the reset path.
	 * Now we can truly claim that ADq is enabled.
	 */
	अगर ((adapter->vf_res->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ADQ) &&
	    adapter->num_tc)
		dev_info(&adapter->pdev->dev, "ADq Enabled, %u TCs created",
			 adapter->num_tc);

	dev_info(&adapter->pdev->dev, "Multiqueue %s: Queue pair count = %u",
		 (adapter->num_active_queues > 1) ? "Enabled" : "Disabled",
		 adapter->num_active_queues);

	वापस 0;
err_alloc_q_vectors:
	iavf_reset_पूर्णांकerrupt_capability(adapter);
err_set_पूर्णांकerrupt:
	iavf_मुक्त_queues(adapter);
err_alloc_queues:
	वापस err;
पूर्ण

/**
 * iavf_मुक्त_rss - Free memory used by RSS काष्ठाs
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_मुक्त_rss(काष्ठा iavf_adapter *adapter)
अणु
	kमुक्त(adapter->rss_key);
	adapter->rss_key = शून्य;

	kमुक्त(adapter->rss_lut);
	adapter->rss_lut = शून्य;
पूर्ण

/**
 * iavf_reinit_पूर्णांकerrupt_scheme - Reallocate queues and vectors
 * @adapter: board निजी काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक iavf_reinit_पूर्णांकerrupt_scheme(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	अगर (netअगर_running(netdev))
		iavf_मुक्त_traffic_irqs(adapter);
	iavf_मुक्त_misc_irq(adapter);
	iavf_reset_पूर्णांकerrupt_capability(adapter);
	iavf_मुक्त_q_vectors(adapter);
	iavf_मुक्त_queues(adapter);

	err =  iavf_init_पूर्णांकerrupt_scheme(adapter);
	अगर (err)
		जाओ err;

	netअगर_tx_stop_all_queues(netdev);

	err = iavf_request_misc_irq(adapter);
	अगर (err)
		जाओ err;

	set_bit(__IAVF_VSI_DOWN, adapter->vsi.state);

	iavf_map_rings_to_vectors(adapter);

	अगर (RSS_AQ(adapter))
		adapter->aq_required |= IAVF_FLAG_AQ_CONFIGURE_RSS;
	अन्यथा
		err = iavf_init_rss(adapter);
err:
	वापस err;
पूर्ण

/**
 * iavf_process_aq_command - process aq_required flags
 * and sends aq command
 * @adapter: poपूर्णांकer to iavf adapter काष्ठाure
 *
 * Returns 0 on success
 * Returns error code अगर no command was sent
 * or error code अगर the command failed.
 **/
अटल पूर्णांक iavf_process_aq_command(काष्ठा iavf_adapter *adapter)
अणु
	अगर (adapter->aq_required & IAVF_FLAG_AQ_GET_CONFIG)
		वापस iavf_send_vf_config_msg(adapter);
	अगर (adapter->aq_required & IAVF_FLAG_AQ_DISABLE_QUEUES) अणु
		iavf_disable_queues(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_MAP_VECTORS) अणु
		iavf_map_queues(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_ADD_MAC_FILTER) अणु
		iavf_add_ether_addrs(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_ADD_VLAN_FILTER) अणु
		iavf_add_vlans(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_DEL_MAC_FILTER) अणु
		iavf_del_ether_addrs(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_DEL_VLAN_FILTER) अणु
		iavf_del_vlans(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_ENABLE_VLAN_STRIPPING) अणु
		iavf_enable_vlan_stripping(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_DISABLE_VLAN_STRIPPING) अणु
		iavf_disable_vlan_stripping(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_CONFIGURE_QUEUES) अणु
		iavf_configure_queues(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_ENABLE_QUEUES) अणु
		iavf_enable_queues(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_CONFIGURE_RSS) अणु
		/* This message goes straight to the firmware, not the
		 * PF, so we करोn't have to set current_op as we will
		 * not get a response through the ARQ.
		 */
		adapter->aq_required &= ~IAVF_FLAG_AQ_CONFIGURE_RSS;
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_GET_HENA) अणु
		iavf_get_hena(adapter);
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_SET_HENA) अणु
		iavf_set_hena(adapter);
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_SET_RSS_KEY) अणु
		iavf_set_rss_key(adapter);
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_SET_RSS_LUT) अणु
		iavf_set_rss_lut(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_REQUEST_PROMISC) अणु
		iavf_set_promiscuous(adapter, FLAG_VF_UNICAST_PROMISC |
				       FLAG_VF_MULTICAST_PROMISC);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_REQUEST_ALLMULTI) अणु
		iavf_set_promiscuous(adapter, FLAG_VF_MULTICAST_PROMISC);
		वापस 0;
	पूर्ण

	अगर ((adapter->aq_required & IAVF_FLAG_AQ_RELEASE_PROMISC) &&
	    (adapter->aq_required & IAVF_FLAG_AQ_RELEASE_ALLMULTI)) अणु
		iavf_set_promiscuous(adapter, 0);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_ENABLE_CHANNELS) अणु
		iavf_enable_channels(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_DISABLE_CHANNELS) अणु
		iavf_disable_channels(adapter);
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_ADD_CLOUD_FILTER) अणु
		iavf_add_cloud_filter(adapter);
		वापस 0;
	पूर्ण

	अगर (adapter->aq_required & IAVF_FLAG_AQ_DEL_CLOUD_FILTER) अणु
		iavf_del_cloud_filter(adapter);
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_DEL_CLOUD_FILTER) अणु
		iavf_del_cloud_filter(adapter);
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_ADD_CLOUD_FILTER) अणु
		iavf_add_cloud_filter(adapter);
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_ADD_Fसूची_FILTER) अणु
		iavf_add_fdir_filter(adapter);
		वापस IAVF_SUCCESS;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_DEL_Fसूची_FILTER) अणु
		iavf_del_fdir_filter(adapter);
		वापस IAVF_SUCCESS;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_ADD_ADV_RSS_CFG) अणु
		iavf_add_adv_rss_cfg(adapter);
		वापस 0;
	पूर्ण
	अगर (adapter->aq_required & IAVF_FLAG_AQ_DEL_ADV_RSS_CFG) अणु
		iavf_del_adv_rss_cfg(adapter);
		वापस 0;
	पूर्ण
	वापस -EAGAIN;
पूर्ण

/**
 * iavf_startup - first step of driver startup
 * @adapter: board निजी काष्ठाure
 *
 * Function process __IAVF_STARTUP driver state.
 * When success the state is changed to __IAVF_INIT_VERSION_CHECK
 * when fails it वापसs -EAGAIN
 **/
अटल पूर्णांक iavf_startup(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक err;

	WARN_ON(adapter->state != __IAVF_STARTUP);

	/* driver loaded, probe complete */
	adapter->flags &= ~IAVF_FLAG_PF_COMMS_FAILED;
	adapter->flags &= ~IAVF_FLAG_RESET_PENDING;
	err = iavf_set_mac_type(hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to set MAC type (%d)\n", err);
		जाओ err;
	पूर्ण

	err = iavf_check_reset_complete(hw);
	अगर (err) अणु
		dev_info(&pdev->dev, "Device is still in reset (%d), retrying\n",
			 err);
		जाओ err;
	पूर्ण
	hw->aq.num_arq_entries = IAVF_AQ_LEN;
	hw->aq.num_asq_entries = IAVF_AQ_LEN;
	hw->aq.arq_buf_size = IAVF_MAX_AQ_BUF_SIZE;
	hw->aq.asq_buf_size = IAVF_MAX_AQ_BUF_SIZE;

	err = iavf_init_adminq(hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init Admin Queue (%d)\n", err);
		जाओ err;
	पूर्ण
	err = iavf_send_api_ver(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to send to PF (%d)\n", err);
		iavf_shutकरोwn_adminq(hw);
		जाओ err;
	पूर्ण
	adapter->state = __IAVF_INIT_VERSION_CHECK;
err:
	वापस err;
पूर्ण

/**
 * iavf_init_version_check - second step of driver startup
 * @adapter: board निजी काष्ठाure
 *
 * Function process __IAVF_INIT_VERSION_CHECK driver state.
 * When success the state is changed to __IAVF_INIT_GET_RESOURCES
 * when fails it वापसs -EAGAIN
 **/
अटल पूर्णांक iavf_init_version_check(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक err = -EAGAIN;

	WARN_ON(adapter->state != __IAVF_INIT_VERSION_CHECK);

	अगर (!iavf_asq_करोne(hw)) अणु
		dev_err(&pdev->dev, "Admin queue command never completed\n");
		iavf_shutकरोwn_adminq(hw);
		adapter->state = __IAVF_STARTUP;
		जाओ err;
	पूर्ण

	/* aq msg sent, aरुकोing reply */
	err = iavf_verअगरy_api_ver(adapter);
	अगर (err) अणु
		अगर (err == IAVF_ERR_ADMIN_QUEUE_NO_WORK)
			err = iavf_send_api_ver(adapter);
		अन्यथा
			dev_err(&pdev->dev, "Unsupported PF API version %d.%d, expected %d.%d\n",
				adapter->pf_version.major,
				adapter->pf_version.minor,
				VIRTCHNL_VERSION_MAJOR,
				VIRTCHNL_VERSION_MINOR);
		जाओ err;
	पूर्ण
	err = iavf_send_vf_config_msg(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to send config request (%d)\n",
			err);
		जाओ err;
	पूर्ण
	adapter->state = __IAVF_INIT_GET_RESOURCES;

err:
	वापस err;
पूर्ण

/**
 * iavf_init_get_resources - third step of driver startup
 * @adapter: board निजी काष्ठाure
 *
 * Function process __IAVF_INIT_GET_RESOURCES driver state and
 * finishes driver initialization procedure.
 * When success the state is changed to __IAVF_DOWN
 * when fails it वापसs -EAGAIN
 **/
अटल पूर्णांक iavf_init_get_resources(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक err;

	WARN_ON(adapter->state != __IAVF_INIT_GET_RESOURCES);
	/* aq msg sent, aरुकोing reply */
	अगर (!adapter->vf_res) अणु
		adapter->vf_res = kzalloc(IAVF_VIRTCHNL_VF_RESOURCE_SIZE,
					  GFP_KERNEL);
		अगर (!adapter->vf_res) अणु
			err = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण
	err = iavf_get_vf_config(adapter);
	अगर (err == IAVF_ERR_ADMIN_QUEUE_NO_WORK) अणु
		err = iavf_send_vf_config_msg(adapter);
		जाओ err;
	पूर्ण अन्यथा अगर (err == IAVF_ERR_PARAM) अणु
		/* We only get ERR_PARAM अगर the device is in a very bad
		 * state or अगर we've been disabled क्रम previous bad
		 * behavior. Either way, we're करोne now.
		 */
		iavf_shutकरोwn_adminq(hw);
		dev_err(&pdev->dev, "Unable to get VF config due to PF error condition, not retrying\n");
		वापस 0;
	पूर्ण
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to get VF config (%d)\n", err);
		जाओ err_alloc;
	पूर्ण

	err = iavf_process_config(adapter);
	अगर (err)
		जाओ err_alloc;
	adapter->current_op = VIRTCHNL_OP_UNKNOWN;

	adapter->flags |= IAVF_FLAG_RX_CSUM_ENABLED;

	netdev->netdev_ops = &iavf_netdev_ops;
	iavf_set_ethtool_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;

	/* MTU range: 68 - 9710 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = IAVF_MAX_RXBUFFER - IAVF_PACKET_HDR_PAD;

	अगर (!is_valid_ether_addr(adapter->hw.mac.addr)) अणु
		dev_info(&pdev->dev, "Invalid MAC address %pM, using random\n",
			 adapter->hw.mac.addr);
		eth_hw_addr_अक्रमom(netdev);
		ether_addr_copy(adapter->hw.mac.addr, netdev->dev_addr);
	पूर्ण अन्यथा अणु
		ether_addr_copy(netdev->dev_addr, adapter->hw.mac.addr);
		ether_addr_copy(netdev->perm_addr, adapter->hw.mac.addr);
	पूर्ण

	adapter->tx_desc_count = IAVF_DEFAULT_TXD;
	adapter->rx_desc_count = IAVF_DEFAULT_RXD;
	err = iavf_init_पूर्णांकerrupt_scheme(adapter);
	अगर (err)
		जाओ err_sw_init;
	iavf_map_rings_to_vectors(adapter);
	अगर (adapter->vf_res->vf_cap_flags &
		VIRTCHNL_VF_OFFLOAD_WB_ON_ITR)
		adapter->flags |= IAVF_FLAG_WB_ON_ITR_CAPABLE;

	err = iavf_request_misc_irq(adapter);
	अगर (err)
		जाओ err_sw_init;

	netअगर_carrier_off(netdev);
	adapter->link_up = false;

	/* set the semaphore to prevent any callbacks after device registration
	 * up to समय when state of driver will be set to __IAVF_DOWN
	 */
	rtnl_lock();
	अगर (!adapter->netdev_रेजिस्टरed) अणु
		err = रेजिस्टर_netdevice(netdev);
		अगर (err) अणु
			rtnl_unlock();
			जाओ err_रेजिस्टर;
		पूर्ण
	पूर्ण

	adapter->netdev_रेजिस्टरed = true;

	netअगर_tx_stop_all_queues(netdev);
	अगर (CLIENT_ALLOWED(adapter)) अणु
		err = iavf_lan_add_device(adapter);
		अगर (err)
			dev_info(&pdev->dev, "Failed to add VF to client API service list: %d\n",
				 err);
	पूर्ण
	dev_info(&pdev->dev, "MAC address: %pM\n", adapter->hw.mac.addr);
	अगर (netdev->features & NETIF_F_GRO)
		dev_info(&pdev->dev, "GRO is enabled\n");

	adapter->state = __IAVF_DOWN;
	set_bit(__IAVF_VSI_DOWN, adapter->vsi.state);
	rtnl_unlock();

	iavf_misc_irq_enable(adapter);
	wake_up(&adapter->करोwn_रुकोqueue);

	adapter->rss_key = kzalloc(adapter->rss_key_size, GFP_KERNEL);
	adapter->rss_lut = kzalloc(adapter->rss_lut_size, GFP_KERNEL);
	अगर (!adapter->rss_key || !adapter->rss_lut) अणु
		err = -ENOMEM;
		जाओ err_mem;
	पूर्ण
	अगर (RSS_AQ(adapter))
		adapter->aq_required |= IAVF_FLAG_AQ_CONFIGURE_RSS;
	अन्यथा
		iavf_init_rss(adapter);

	वापस err;
err_mem:
	iavf_मुक्त_rss(adapter);
err_रेजिस्टर:
	iavf_मुक्त_misc_irq(adapter);
err_sw_init:
	iavf_reset_पूर्णांकerrupt_capability(adapter);
err_alloc:
	kमुक्त(adapter->vf_res);
	adapter->vf_res = शून्य;
err:
	वापस err;
पूर्ण

/**
 * iavf_watchकरोg_task - Periodic call-back task
 * @work: poपूर्णांकer to work_काष्ठा
 **/
अटल व्योम iavf_watchकरोg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iavf_adapter *adapter = container_of(work,
						    काष्ठा iavf_adapter,
						    watchकरोg_task.work);
	काष्ठा iavf_hw *hw = &adapter->hw;
	u32 reg_val;

	अगर (test_and_set_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section))
		जाओ restart_watchकरोg;

	अगर (adapter->flags & IAVF_FLAG_PF_COMMS_FAILED)
		adapter->state = __IAVF_COMM_FAILED;

	चयन (adapter->state) अणु
	हाल __IAVF_COMM_FAILED:
		reg_val = rd32(hw, IAVF_VFGEN_RSTAT) &
			  IAVF_VFGEN_RSTAT_VFR_STATE_MASK;
		अगर (reg_val == VIRTCHNL_VFR_VFACTIVE ||
		    reg_val == VIRTCHNL_VFR_COMPLETED) अणु
			/* A chance क्रम redemption! */
			dev_err(&adapter->pdev->dev,
				"Hardware came out of reset. Attempting reinit.\n");
			adapter->state = __IAVF_STARTUP;
			adapter->flags &= ~IAVF_FLAG_PF_COMMS_FAILED;
			queue_delayed_work(iavf_wq, &adapter->init_task, 10);
			clear_bit(__IAVF_IN_CRITICAL_TASK,
				  &adapter->crit_section);
			/* Don't reschedule the watchdog, since we've restarted
			 * the init task. When init_task contacts the PF and
			 * माला_लो everything set up again, it'll restart the
			 * watchकरोg क्रम us. Down, boy. Sit. Stay. Woof.
			 */
			वापस;
		पूर्ण
		adapter->aq_required = 0;
		adapter->current_op = VIRTCHNL_OP_UNKNOWN;
		clear_bit(__IAVF_IN_CRITICAL_TASK,
			  &adapter->crit_section);
		queue_delayed_work(iavf_wq,
				   &adapter->watchकरोg_task,
				   msecs_to_jअगरfies(10));
		जाओ watchकरोg_करोne;
	हाल __IAVF_RESETTING:
		clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);
		queue_delayed_work(iavf_wq, &adapter->watchकरोg_task, HZ * 2);
		वापस;
	हाल __IAVF_DOWN:
	हाल __IAVF_DOWN_PENDING:
	हाल __IAVF_TESTING:
	हाल __IAVF_RUNNING:
		अगर (adapter->current_op) अणु
			अगर (!iavf_asq_करोne(hw)) अणु
				dev_dbg(&adapter->pdev->dev,
					"Admin queue timeout\n");
				iavf_send_api_ver(adapter);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* An error will be वापसed अगर no commands were
			 * processed; use this opportunity to update stats
			 */
			अगर (iavf_process_aq_command(adapter) &&
			    adapter->state == __IAVF_RUNNING)
				iavf_request_stats(adapter);
		पूर्ण
		अवरोध;
	हाल __IAVF_REMOVE:
		clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);
		वापस;
	शेष:
		जाओ restart_watchकरोg;
	पूर्ण

		/* check क्रम hw reset */
	reg_val = rd32(hw, IAVF_VF_ARQLEN1) & IAVF_VF_ARQLEN1_ARQENABLE_MASK;
	अगर (!reg_val) अणु
		adapter->state = __IAVF_RESETTING;
		adapter->flags |= IAVF_FLAG_RESET_PENDING;
		adapter->aq_required = 0;
		adapter->current_op = VIRTCHNL_OP_UNKNOWN;
		dev_err(&adapter->pdev->dev, "Hardware reset detected\n");
		queue_work(iavf_wq, &adapter->reset_task);
		जाओ watchकरोg_करोne;
	पूर्ण

	schedule_delayed_work(&adapter->client_task, msecs_to_jअगरfies(5));
watchकरोg_करोne:
	अगर (adapter->state == __IAVF_RUNNING ||
	    adapter->state == __IAVF_COMM_FAILED)
		iavf_detect_recover_hung(&adapter->vsi);
	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);
restart_watchकरोg:
	अगर (adapter->aq_required)
		queue_delayed_work(iavf_wq, &adapter->watchकरोg_task,
				   msecs_to_jअगरfies(20));
	अन्यथा
		queue_delayed_work(iavf_wq, &adapter->watchकरोg_task, HZ * 2);
	queue_work(iavf_wq, &adapter->adminq_task);
पूर्ण

अटल व्योम iavf_disable_vf(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_mac_filter *f, *fपंचांगp;
	काष्ठा iavf_vlan_filter *fv, *fvपंचांगp;
	काष्ठा iavf_cloud_filter *cf, *cfपंचांगp;

	adapter->flags |= IAVF_FLAG_PF_COMMS_FAILED;

	/* We करोn't use netअगर_running() because it may be true prior to
	 * nकरो_खोलो() वापसing, so we can't assume it means all our खोलो
	 * tasks have finished, since we're not holding the rtnl_lock here.
	 */
	अगर (adapter->state == __IAVF_RUNNING) अणु
		set_bit(__IAVF_VSI_DOWN, adapter->vsi.state);
		netअगर_carrier_off(adapter->netdev);
		netअगर_tx_disable(adapter->netdev);
		adapter->link_up = false;
		iavf_napi_disable_all(adapter);
		iavf_irq_disable(adapter);
		iavf_मुक्त_traffic_irqs(adapter);
		iavf_मुक्त_all_tx_resources(adapter);
		iavf_मुक्त_all_rx_resources(adapter);
	पूर्ण

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	/* Delete all of the filters */
	list_क्रम_each_entry_safe(f, fपंचांगp, &adapter->mac_filter_list, list) अणु
		list_del(&f->list);
		kमुक्त(f);
	पूर्ण

	list_क्रम_each_entry_safe(fv, fvपंचांगp, &adapter->vlan_filter_list, list) अणु
		list_del(&fv->list);
		kमुक्त(fv);
	पूर्ण

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	spin_lock_bh(&adapter->cloud_filter_list_lock);
	list_क्रम_each_entry_safe(cf, cfपंचांगp, &adapter->cloud_filter_list, list) अणु
		list_del(&cf->list);
		kमुक्त(cf);
		adapter->num_cloud_filters--;
	पूर्ण
	spin_unlock_bh(&adapter->cloud_filter_list_lock);

	iavf_मुक्त_misc_irq(adapter);
	iavf_reset_पूर्णांकerrupt_capability(adapter);
	iavf_मुक्त_queues(adapter);
	iavf_मुक्त_q_vectors(adapter);
	स_रखो(adapter->vf_res, 0, IAVF_VIRTCHNL_VF_RESOURCE_SIZE);
	iavf_shutकरोwn_adminq(&adapter->hw);
	adapter->netdev->flags &= ~IFF_UP;
	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);
	adapter->flags &= ~IAVF_FLAG_RESET_PENDING;
	adapter->state = __IAVF_DOWN;
	wake_up(&adapter->करोwn_रुकोqueue);
	dev_info(&adapter->pdev->dev, "Reset task did not complete, VF disabled\n");
पूर्ण

/**
 * iavf_reset_task - Call-back task to handle hardware reset
 * @work: poपूर्णांकer to work_काष्ठा
 *
 * During reset we need to shut करोwn and reinitialize the admin queue
 * beक्रमe we can use it to communicate with the PF again. We also clear
 * and reinit the rings because that context is lost as well.
 **/
अटल व्योम iavf_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iavf_adapter *adapter = container_of(work,
						      काष्ठा iavf_adapter,
						      reset_task);
	काष्ठा virtchnl_vf_resource *vfres = adapter->vf_res;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा iavf_hw *hw = &adapter->hw;
	काष्ठा iavf_mac_filter *f, *fपंचांगp;
	काष्ठा iavf_vlan_filter *vlf;
	काष्ठा iavf_cloud_filter *cf;
	u32 reg_val;
	पूर्णांक i = 0, err;
	bool running;

	/* When device is being हटाओd it करोesn't make sense to run the reset
	 * task, just वापस in such a हाल.
	 */
	अगर (test_bit(__IAVF_IN_REMOVE_TASK, &adapter->crit_section))
		वापस;

	जबतक (test_and_set_bit(__IAVF_IN_CLIENT_TASK,
				&adapter->crit_section))
		usleep_range(500, 1000);
	अगर (CLIENT_ENABLED(adapter)) अणु
		adapter->flags &= ~(IAVF_FLAG_CLIENT_NEEDS_OPEN |
				    IAVF_FLAG_CLIENT_NEEDS_CLOSE |
				    IAVF_FLAG_CLIENT_NEEDS_L2_PARAMS |
				    IAVF_FLAG_SERVICE_CLIENT_REQUESTED);
		cancel_delayed_work_sync(&adapter->client_task);
		iavf_notअगरy_client_बंद(&adapter->vsi, true);
	पूर्ण
	iavf_misc_irq_disable(adapter);
	अगर (adapter->flags & IAVF_FLAG_RESET_NEEDED) अणु
		adapter->flags &= ~IAVF_FLAG_RESET_NEEDED;
		/* Restart the AQ here. If we have been reset but didn't
		 * detect it, or अगर the PF had to reinit, our AQ will be hosed.
		 */
		iavf_shutकरोwn_adminq(hw);
		iavf_init_adminq(hw);
		iavf_request_reset(adapter);
	पूर्ण
	adapter->flags |= IAVF_FLAG_RESET_PENDING;

	/* poll until we see the reset actually happen */
	क्रम (i = 0; i < IAVF_RESET_WAIT_DETECTED_COUNT; i++) अणु
		reg_val = rd32(hw, IAVF_VF_ARQLEN1) &
			  IAVF_VF_ARQLEN1_ARQENABLE_MASK;
		अगर (!reg_val)
			अवरोध;
		usleep_range(5000, 10000);
	पूर्ण
	अगर (i == IAVF_RESET_WAIT_DETECTED_COUNT) अणु
		dev_info(&adapter->pdev->dev, "Never saw reset\n");
		जाओ जारी_reset; /* act like the reset happened */
	पूर्ण

	/* रुको until the reset is complete and the PF is responding to us */
	क्रम (i = 0; i < IAVF_RESET_WAIT_COMPLETE_COUNT; i++) अणु
		/* sleep first to make sure a minimum रुको समय is met */
		msleep(IAVF_RESET_WAIT_MS);

		reg_val = rd32(hw, IAVF_VFGEN_RSTAT) &
			  IAVF_VFGEN_RSTAT_VFR_STATE_MASK;
		अगर (reg_val == VIRTCHNL_VFR_VFACTIVE)
			अवरोध;
	पूर्ण

	pci_set_master(adapter->pdev);

	अगर (i == IAVF_RESET_WAIT_COMPLETE_COUNT) अणु
		dev_err(&adapter->pdev->dev, "Reset never finished (%x)\n",
			reg_val);
		iavf_disable_vf(adapter);
		clear_bit(__IAVF_IN_CLIENT_TASK, &adapter->crit_section);
		वापस; /* Do not attempt to reinit. It's dead, Jim. */
	पूर्ण

जारी_reset:
	/* We करोn't use netअगर_running() because it may be true prior to
	 * nकरो_खोलो() वापसing, so we can't assume it means all our खोलो
	 * tasks have finished, since we're not holding the rtnl_lock here.
	 */
	running = ((adapter->state == __IAVF_RUNNING) ||
		   (adapter->state == __IAVF_RESETTING));

	अगर (running) अणु
		netअगर_carrier_off(netdev);
		netअगर_tx_stop_all_queues(netdev);
		adapter->link_up = false;
		iavf_napi_disable_all(adapter);
	पूर्ण
	iavf_irq_disable(adapter);

	adapter->state = __IAVF_RESETTING;
	adapter->flags &= ~IAVF_FLAG_RESET_PENDING;

	/* मुक्त the Tx/Rx rings and descriptors, might be better to just
	 * re-use them someसमय in the future
	 */
	iavf_मुक्त_all_rx_resources(adapter);
	iavf_मुक्त_all_tx_resources(adapter);

	adapter->flags |= IAVF_FLAG_QUEUES_DISABLED;
	/* समाप्त and reinit the admin queue */
	iavf_shutकरोwn_adminq(hw);
	adapter->current_op = VIRTCHNL_OP_UNKNOWN;
	err = iavf_init_adminq(hw);
	अगर (err)
		dev_info(&adapter->pdev->dev, "Failed to init adminq: %d\n",
			 err);
	adapter->aq_required = 0;

	अगर (adapter->flags & IAVF_FLAG_REINIT_ITR_NEEDED) अणु
		err = iavf_reinit_पूर्णांकerrupt_scheme(adapter);
		अगर (err)
			जाओ reset_err;
	पूर्ण

	adapter->aq_required |= IAVF_FLAG_AQ_GET_CONFIG;
	adapter->aq_required |= IAVF_FLAG_AQ_MAP_VECTORS;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	/* Delete filter क्रम the current MAC address, it could have
	 * been changed by the PF via administratively set MAC.
	 * Will be re-added via VIRTCHNL_OP_GET_VF_RESOURCES.
	 */
	list_क्रम_each_entry_safe(f, fपंचांगp, &adapter->mac_filter_list, list) अणु
		अगर (ether_addr_equal(f->macaddr, adapter->hw.mac.addr)) अणु
			list_del(&f->list);
			kमुक्त(f);
		पूर्ण
	पूर्ण
	/* re-add all MAC filters */
	list_क्रम_each_entry(f, &adapter->mac_filter_list, list) अणु
		f->add = true;
	पूर्ण
	/* re-add all VLAN filters */
	list_क्रम_each_entry(vlf, &adapter->vlan_filter_list, list) अणु
		vlf->add = true;
	पूर्ण

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	/* check अगर TCs are running and re-add all cloud filters */
	spin_lock_bh(&adapter->cloud_filter_list_lock);
	अगर ((vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ADQ) &&
	    adapter->num_tc) अणु
		list_क्रम_each_entry(cf, &adapter->cloud_filter_list, list) अणु
			cf->add = true;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&adapter->cloud_filter_list_lock);

	adapter->aq_required |= IAVF_FLAG_AQ_ADD_MAC_FILTER;
	adapter->aq_required |= IAVF_FLAG_AQ_ADD_VLAN_FILTER;
	adapter->aq_required |= IAVF_FLAG_AQ_ADD_CLOUD_FILTER;
	iavf_misc_irq_enable(adapter);

	mod_delayed_work(iavf_wq, &adapter->watchकरोg_task, 2);

	/* We were running when the reset started, so we need to restore some
	 * state here.
	 */
	अगर (running) अणु
		/* allocate transmit descriptors */
		err = iavf_setup_all_tx_resources(adapter);
		अगर (err)
			जाओ reset_err;

		/* allocate receive descriptors */
		err = iavf_setup_all_rx_resources(adapter);
		अगर (err)
			जाओ reset_err;

		अगर (adapter->flags & IAVF_FLAG_REINIT_ITR_NEEDED) अणु
			err = iavf_request_traffic_irqs(adapter, netdev->name);
			अगर (err)
				जाओ reset_err;

			adapter->flags &= ~IAVF_FLAG_REINIT_ITR_NEEDED;
		पूर्ण

		iavf_configure(adapter);

		iavf_up_complete(adapter);

		iavf_irq_enable(adapter, true);
	पूर्ण अन्यथा अणु
		adapter->state = __IAVF_DOWN;
		wake_up(&adapter->करोwn_रुकोqueue);
	पूर्ण
	clear_bit(__IAVF_IN_CLIENT_TASK, &adapter->crit_section);
	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	वापस;
reset_err:
	clear_bit(__IAVF_IN_CLIENT_TASK, &adapter->crit_section);
	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);
	dev_err(&adapter->pdev->dev, "failed to allocate resources during reinit\n");
	iavf_बंद(netdev);
पूर्ण

/**
 * iavf_adminq_task - worker thपढ़ो to clean the admin queue
 * @work: poपूर्णांकer to work_काष्ठा containing our data
 **/
अटल व्योम iavf_adminq_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iavf_adapter *adapter =
		container_of(work, काष्ठा iavf_adapter, adminq_task);
	काष्ठा iavf_hw *hw = &adapter->hw;
	काष्ठा iavf_arq_event_info event;
	क्रमागत virtchnl_ops v_op;
	क्रमागत iavf_status ret, v_ret;
	u32 val, oldval;
	u16 pending;

	अगर (adapter->flags & IAVF_FLAG_PF_COMMS_FAILED)
		जाओ out;

	event.buf_len = IAVF_MAX_AQ_BUF_SIZE;
	event.msg_buf = kzalloc(event.buf_len, GFP_KERNEL);
	अगर (!event.msg_buf)
		जाओ out;

	करो अणु
		ret = iavf_clean_arq_element(hw, &event, &pending);
		v_op = (क्रमागत virtchnl_ops)le32_to_cpu(event.desc.cookie_high);
		v_ret = (क्रमागत iavf_status)le32_to_cpu(event.desc.cookie_low);

		अगर (ret || !v_op)
			अवरोध; /* No event to process or error cleaning ARQ */

		iavf_virtchnl_completion(adapter, v_op, v_ret, event.msg_buf,
					 event.msg_len);
		अगर (pending != 0)
			स_रखो(event.msg_buf, 0, IAVF_MAX_AQ_BUF_SIZE);
	पूर्ण जबतक (pending);

	अगर ((adapter->flags &
	     (IAVF_FLAG_RESET_PENDING | IAVF_FLAG_RESET_NEEDED)) ||
	    adapter->state == __IAVF_RESETTING)
		जाओ मुक्तकरोm;

	/* check क्रम error indications */
	val = rd32(hw, hw->aq.arq.len);
	अगर (val == 0xdeadbeef) /* indicates device in reset */
		जाओ मुक्तकरोm;
	oldval = val;
	अगर (val & IAVF_VF_ARQLEN1_ARQVFE_MASK) अणु
		dev_info(&adapter->pdev->dev, "ARQ VF Error detected\n");
		val &= ~IAVF_VF_ARQLEN1_ARQVFE_MASK;
	पूर्ण
	अगर (val & IAVF_VF_ARQLEN1_ARQOVFL_MASK) अणु
		dev_info(&adapter->pdev->dev, "ARQ Overflow Error detected\n");
		val &= ~IAVF_VF_ARQLEN1_ARQOVFL_MASK;
	पूर्ण
	अगर (val & IAVF_VF_ARQLEN1_ARQCRIT_MASK) अणु
		dev_info(&adapter->pdev->dev, "ARQ Critical Error detected\n");
		val &= ~IAVF_VF_ARQLEN1_ARQCRIT_MASK;
	पूर्ण
	अगर (oldval != val)
		wr32(hw, hw->aq.arq.len, val);

	val = rd32(hw, hw->aq.asq.len);
	oldval = val;
	अगर (val & IAVF_VF_ATQLEN1_ATQVFE_MASK) अणु
		dev_info(&adapter->pdev->dev, "ASQ VF Error detected\n");
		val &= ~IAVF_VF_ATQLEN1_ATQVFE_MASK;
	पूर्ण
	अगर (val & IAVF_VF_ATQLEN1_ATQOVFL_MASK) अणु
		dev_info(&adapter->pdev->dev, "ASQ Overflow Error detected\n");
		val &= ~IAVF_VF_ATQLEN1_ATQOVFL_MASK;
	पूर्ण
	अगर (val & IAVF_VF_ATQLEN1_ATQCRIT_MASK) अणु
		dev_info(&adapter->pdev->dev, "ASQ Critical Error detected\n");
		val &= ~IAVF_VF_ATQLEN1_ATQCRIT_MASK;
	पूर्ण
	अगर (oldval != val)
		wr32(hw, hw->aq.asq.len, val);

मुक्तकरोm:
	kमुक्त(event.msg_buf);
out:
	/* re-enable Admin queue पूर्णांकerrupt cause */
	iavf_misc_irq_enable(adapter);
पूर्ण

/**
 * iavf_client_task - worker thपढ़ो to perक्रमm client work
 * @work: poपूर्णांकer to work_काष्ठा containing our data
 *
 * This task handles client पूर्णांकeractions. Because client calls can be
 * reentrant, we can't handle them in the watchकरोg.
 **/
अटल व्योम iavf_client_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iavf_adapter *adapter =
		container_of(work, काष्ठा iavf_adapter, client_task.work);

	/* If we can't get the client bit, just give up. We'll be rescheduled
	 * later.
	 */

	अगर (test_and_set_bit(__IAVF_IN_CLIENT_TASK, &adapter->crit_section))
		वापस;

	अगर (adapter->flags & IAVF_FLAG_SERVICE_CLIENT_REQUESTED) अणु
		iavf_client_subtask(adapter);
		adapter->flags &= ~IAVF_FLAG_SERVICE_CLIENT_REQUESTED;
		जाओ out;
	पूर्ण
	अगर (adapter->flags & IAVF_FLAG_CLIENT_NEEDS_L2_PARAMS) अणु
		iavf_notअगरy_client_l2_params(&adapter->vsi);
		adapter->flags &= ~IAVF_FLAG_CLIENT_NEEDS_L2_PARAMS;
		जाओ out;
	पूर्ण
	अगर (adapter->flags & IAVF_FLAG_CLIENT_NEEDS_CLOSE) अणु
		iavf_notअगरy_client_बंद(&adapter->vsi, false);
		adapter->flags &= ~IAVF_FLAG_CLIENT_NEEDS_CLOSE;
		जाओ out;
	पूर्ण
	अगर (adapter->flags & IAVF_FLAG_CLIENT_NEEDS_OPEN) अणु
		iavf_notअगरy_client_खोलो(&adapter->vsi);
		adapter->flags &= ~IAVF_FLAG_CLIENT_NEEDS_OPEN;
	पूर्ण
out:
	clear_bit(__IAVF_IN_CLIENT_TASK, &adapter->crit_section);
पूर्ण

/**
 * iavf_मुक्त_all_tx_resources - Free Tx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 **/
व्योम iavf_मुक्त_all_tx_resources(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक i;

	अगर (!adapter->tx_rings)
		वापस;

	क्रम (i = 0; i < adapter->num_active_queues; i++)
		अगर (adapter->tx_rings[i].desc)
			iavf_मुक्त_tx_resources(&adapter->tx_rings[i]);
पूर्ण

/**
 * iavf_setup_all_tx_resources - allocate all queues Tx resources
 * @adapter: board निजी काष्ठाure
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक iavf_setup_all_tx_resources(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_active_queues; i++) अणु
		adapter->tx_rings[i].count = adapter->tx_desc_count;
		err = iavf_setup_tx_descriptors(&adapter->tx_rings[i]);
		अगर (!err)
			जारी;
		dev_err(&adapter->pdev->dev,
			"Allocation for Tx Queue %u failed\n", i);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * iavf_setup_all_rx_resources - allocate all queues Rx resources
 * @adapter: board निजी काष्ठाure
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक iavf_setup_all_rx_resources(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_active_queues; i++) अणु
		adapter->rx_rings[i].count = adapter->rx_desc_count;
		err = iavf_setup_rx_descriptors(&adapter->rx_rings[i]);
		अगर (!err)
			जारी;
		dev_err(&adapter->pdev->dev,
			"Allocation for Rx Queue %u failed\n", i);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/**
 * iavf_मुक्त_all_rx_resources - Free Rx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all receive software resources
 **/
व्योम iavf_मुक्त_all_rx_resources(काष्ठा iavf_adapter *adapter)
अणु
	पूर्णांक i;

	अगर (!adapter->rx_rings)
		वापस;

	क्रम (i = 0; i < adapter->num_active_queues; i++)
		अगर (adapter->rx_rings[i].desc)
			iavf_मुक्त_rx_resources(&adapter->rx_rings[i]);
पूर्ण

/**
 * iavf_validate_tx_bandwidth - validate the max Tx bandwidth
 * @adapter: board निजी काष्ठाure
 * @max_tx_rate: max Tx bw क्रम a tc
 **/
अटल पूर्णांक iavf_validate_tx_bandwidth(काष्ठा iavf_adapter *adapter,
				      u64 max_tx_rate)
अणु
	पूर्णांक speed = 0, ret = 0;

	अगर (ADV_LINK_SUPPORT(adapter)) अणु
		अगर (adapter->link_speed_mbps < U32_MAX) अणु
			speed = adapter->link_speed_mbps;
			जाओ validate_bw;
		पूर्ण अन्यथा अणु
			dev_err(&adapter->pdev->dev, "Unknown link speed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	चयन (adapter->link_speed) अणु
	हाल VIRTCHNL_LINK_SPEED_40GB:
		speed = SPEED_40000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_25GB:
		speed = SPEED_25000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_20GB:
		speed = SPEED_20000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_10GB:
		speed = SPEED_10000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_5GB:
		speed = SPEED_5000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_2_5GB:
		speed = SPEED_2500;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_1GB:
		speed = SPEED_1000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_100MB:
		speed = SPEED_100;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

validate_bw:
	अगर (max_tx_rate > speed) अणु
		dev_err(&adapter->pdev->dev,
			"Invalid tx rate specified\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * iavf_validate_ch_config - validate queue mapping info
 * @adapter: board निजी काष्ठाure
 * @mqprio_qopt: queue parameters
 *
 * This function validates अगर the config provided by the user to
 * configure queue channels is valid or not. Returns 0 on a valid
 * config.
 **/
अटल पूर्णांक iavf_validate_ch_config(काष्ठा iavf_adapter *adapter,
				   काष्ठा tc_mqprio_qopt_offload *mqprio_qopt)
अणु
	u64 total_max_rate = 0;
	पूर्णांक i, num_qps = 0;
	u64 tx_rate = 0;
	पूर्णांक ret = 0;

	अगर (mqprio_qopt->qopt.num_tc > IAVF_MAX_TRAFFIC_CLASS ||
	    mqprio_qopt->qopt.num_tc < 1)
		वापस -EINVAL;

	क्रम (i = 0; i <= mqprio_qopt->qopt.num_tc - 1; i++) अणु
		अगर (!mqprio_qopt->qopt.count[i] ||
		    mqprio_qopt->qopt.offset[i] != num_qps)
			वापस -EINVAL;
		अगर (mqprio_qopt->min_rate[i]) अणु
			dev_err(&adapter->pdev->dev,
				"Invalid min tx rate (greater than 0) specified\n");
			वापस -EINVAL;
		पूर्ण
		/*convert to Mbps */
		tx_rate = भाग_u64(mqprio_qopt->max_rate[i],
				  IAVF_MBPS_DIVISOR);
		total_max_rate += tx_rate;
		num_qps += mqprio_qopt->qopt.count[i];
	पूर्ण
	अगर (num_qps > IAVF_MAX_REQ_QUEUES)
		वापस -EINVAL;

	ret = iavf_validate_tx_bandwidth(adapter, total_max_rate);
	वापस ret;
पूर्ण

/**
 * iavf_del_all_cloud_filters - delete all cloud filters on the traffic classes
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम iavf_del_all_cloud_filters(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_cloud_filter *cf, *cfपंचांगp;

	spin_lock_bh(&adapter->cloud_filter_list_lock);
	list_क्रम_each_entry_safe(cf, cfपंचांगp, &adapter->cloud_filter_list,
				 list) अणु
		list_del(&cf->list);
		kमुक्त(cf);
		adapter->num_cloud_filters--;
	पूर्ण
	spin_unlock_bh(&adapter->cloud_filter_list_lock);
पूर्ण

/**
 * __iavf_setup_tc - configure multiple traffic classes
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @type_data: tc offload data
 *
 * This function processes the config inक्रमmation provided by the
 * user to configure traffic classes/queue channels and packages the
 * inक्रमmation to request the PF to setup traffic classes.
 *
 * Returns 0 on success.
 **/
अटल पूर्णांक __iavf_setup_tc(काष्ठा net_device *netdev, व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt_offload *mqprio_qopt = type_data;
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	काष्ठा virtchnl_vf_resource *vfres = adapter->vf_res;
	u8 num_tc = 0, total_qps = 0;
	पूर्णांक ret = 0, netdev_tc = 0;
	u64 max_tx_rate;
	u16 mode;
	पूर्णांक i;

	num_tc = mqprio_qopt->qopt.num_tc;
	mode = mqprio_qopt->mode;

	/* delete queue_channel */
	अगर (!mqprio_qopt->qopt.hw) अणु
		अगर (adapter->ch_config.state == __IAVF_TC_RUNNING) अणु
			/* reset the tc configuration */
			netdev_reset_tc(netdev);
			adapter->num_tc = 0;
			netअगर_tx_stop_all_queues(netdev);
			netअगर_tx_disable(netdev);
			iavf_del_all_cloud_filters(adapter);
			adapter->aq_required = IAVF_FLAG_AQ_DISABLE_CHANNELS;
			जाओ निकास;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* add queue channel */
	अगर (mode == TC_MQPRIO_MODE_CHANNEL) अणु
		अगर (!(vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ADQ)) अणु
			dev_err(&adapter->pdev->dev, "ADq not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (adapter->ch_config.state != __IAVF_TC_INVALID) अणु
			dev_err(&adapter->pdev->dev, "TC configuration already exists\n");
			वापस -EINVAL;
		पूर्ण

		ret = iavf_validate_ch_config(adapter, mqprio_qopt);
		अगर (ret)
			वापस ret;
		/* Return अगर same TC config is requested */
		अगर (adapter->num_tc == num_tc)
			वापस 0;
		adapter->num_tc = num_tc;

		क्रम (i = 0; i < IAVF_MAX_TRAFFIC_CLASS; i++) अणु
			अगर (i < num_tc) अणु
				adapter->ch_config.ch_info[i].count =
					mqprio_qopt->qopt.count[i];
				adapter->ch_config.ch_info[i].offset =
					mqprio_qopt->qopt.offset[i];
				total_qps += mqprio_qopt->qopt.count[i];
				max_tx_rate = mqprio_qopt->max_rate[i];
				/* convert to Mbps */
				max_tx_rate = भाग_u64(max_tx_rate,
						      IAVF_MBPS_DIVISOR);
				adapter->ch_config.ch_info[i].max_tx_rate =
					max_tx_rate;
			पूर्ण अन्यथा अणु
				adapter->ch_config.ch_info[i].count = 1;
				adapter->ch_config.ch_info[i].offset = 0;
			पूर्ण
		पूर्ण
		adapter->ch_config.total_qps = total_qps;
		netअगर_tx_stop_all_queues(netdev);
		netअगर_tx_disable(netdev);
		adapter->aq_required |= IAVF_FLAG_AQ_ENABLE_CHANNELS;
		netdev_reset_tc(netdev);
		/* Report the tc mapping up the stack */
		netdev_set_num_tc(adapter->netdev, num_tc);
		क्रम (i = 0; i < IAVF_MAX_TRAFFIC_CLASS; i++) अणु
			u16 qcount = mqprio_qopt->qopt.count[i];
			u16 qoffset = mqprio_qopt->qopt.offset[i];

			अगर (i < num_tc)
				netdev_set_tc_queue(netdev, netdev_tc++, qcount,
						    qoffset);
		पूर्ण
	पूर्ण
निकास:
	वापस ret;
पूर्ण

/**
 * iavf_parse_cls_flower - Parse tc flower filters provided by kernel
 * @adapter: board निजी काष्ठाure
 * @f: poपूर्णांकer to काष्ठा flow_cls_offload
 * @filter: poपूर्णांकer to cloud filter काष्ठाure
 */
अटल पूर्णांक iavf_parse_cls_flower(काष्ठा iavf_adapter *adapter,
				 काष्ठा flow_cls_offload *f,
				 काष्ठा iavf_cloud_filter *filter)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	u16 n_proto_mask = 0;
	u16 n_proto_key = 0;
	u8 field_flags = 0;
	u16 addr_type = 0;
	u16 n_proto = 0;
	पूर्णांक i = 0;
	काष्ठा virtchnl_filter *vf = &filter->f;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID))) अणु
		dev_err(&adapter->pdev->dev, "Unsupported key used: 0x%x\n",
			dissector->used_keys);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) अणु
		काष्ठा flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		अगर (match.mask->keyid != 0)
			field_flags |= IAVF_CLOUD_FIELD_TEN_ID;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		n_proto_key = ntohs(match.key->n_proto);
		n_proto_mask = ntohs(match.mask->n_proto);

		अगर (n_proto_key == ETH_P_ALL) अणु
			n_proto_key = 0;
			n_proto_mask = 0;
		पूर्ण
		n_proto = n_proto_key & n_proto_mask;
		अगर (n_proto != ETH_P_IP && n_proto != ETH_P_IPV6)
			वापस -EINVAL;
		अगर (n_proto == ETH_P_IPV6) अणु
			/* specअगरy flow type as TCP IPv6 */
			vf->flow_type = VIRTCHNL_TCP_V6_FLOW;
		पूर्ण

		अगर (match.key->ip_proto != IPPROTO_TCP) अणु
			dev_info(&adapter->pdev->dev, "Only TCP transport is supported\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);

		/* use is_broadcast and is_zero to check क्रम all 0xf or 0 */
		अगर (!is_zero_ether_addr(match.mask->dst)) अणु
			अगर (is_broadcast_ether_addr(match.mask->dst)) अणु
				field_flags |= IAVF_CLOUD_FIELD_OMAC;
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev, "Bad ether dest mask %pM\n",
					match.mask->dst);
				वापस IAVF_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (!is_zero_ether_addr(match.mask->src)) अणु
			अगर (is_broadcast_ether_addr(match.mask->src)) अणु
				field_flags |= IAVF_CLOUD_FIELD_IMAC;
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev, "Bad ether src mask %pM\n",
					match.mask->src);
				वापस IAVF_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (!is_zero_ether_addr(match.key->dst))
			अगर (is_valid_ether_addr(match.key->dst) ||
			    is_multicast_ether_addr(match.key->dst)) अणु
				/* set the mask अगर a valid dst_mac address */
				क्रम (i = 0; i < ETH_ALEN; i++)
					vf->mask.tcp_spec.dst_mac[i] |= 0xff;
				ether_addr_copy(vf->data.tcp_spec.dst_mac,
						match.key->dst);
			पूर्ण

		अगर (!is_zero_ether_addr(match.key->src))
			अगर (is_valid_ether_addr(match.key->src) ||
			    is_multicast_ether_addr(match.key->src)) अणु
				/* set the mask अगर a valid dst_mac address */
				क्रम (i = 0; i < ETH_ALEN; i++)
					vf->mask.tcp_spec.src_mac[i] |= 0xff;
				ether_addr_copy(vf->data.tcp_spec.src_mac,
						match.key->src);
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		अगर (match.mask->vlan_id) अणु
			अगर (match.mask->vlan_id == VLAN_VID_MASK) अणु
				field_flags |= IAVF_CLOUD_FIELD_IVLAN;
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev, "Bad vlan mask %u\n",
					match.mask->vlan_id);
				वापस IAVF_ERR_CONFIG;
			पूर्ण
		पूर्ण
		vf->mask.tcp_spec.vlan_id |= cpu_to_be16(0xffff);
		vf->data.tcp_spec.vlan_id = cpu_to_be16(match.key->vlan_id);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		अगर (match.mask->dst) अणु
			अगर (match.mask->dst == cpu_to_be32(0xffffffff)) अणु
				field_flags |= IAVF_CLOUD_FIELD_IIP;
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev, "Bad ip dst mask 0x%08x\n",
					be32_to_cpu(match.mask->dst));
				वापस IAVF_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (match.mask->src) अणु
			अगर (match.mask->src == cpu_to_be32(0xffffffff)) अणु
				field_flags |= IAVF_CLOUD_FIELD_IIP;
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev, "Bad ip src mask 0x%08x\n",
					be32_to_cpu(match.mask->dst));
				वापस IAVF_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (field_flags & IAVF_CLOUD_FIELD_TEN_ID) अणु
			dev_info(&adapter->pdev->dev, "Tenant id not allowed for ip filter\n");
			वापस IAVF_ERR_CONFIG;
		पूर्ण
		अगर (match.key->dst) अणु
			vf->mask.tcp_spec.dst_ip[0] |= cpu_to_be32(0xffffffff);
			vf->data.tcp_spec.dst_ip[0] = match.key->dst;
		पूर्ण
		अगर (match.key->src) अणु
			vf->mask.tcp_spec.src_ip[0] |= cpu_to_be32(0xffffffff);
			vf->data.tcp_spec.src_ip[0] = match.key->src;
		पूर्ण
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);

		/* validate mask, make sure it is not IPV6_ADDR_ANY */
		अगर (ipv6_addr_any(&match.mask->dst)) अणु
			dev_err(&adapter->pdev->dev, "Bad ipv6 dst mask 0x%02x\n",
				IPV6_ADDR_ANY);
			वापस IAVF_ERR_CONFIG;
		पूर्ण

		/* src and dest IPv6 address should not be LOOPBACK
		 * (0:0:0:0:0:0:0:1) which can be represented as ::1
		 */
		अगर (ipv6_addr_loopback(&match.key->dst) ||
		    ipv6_addr_loopback(&match.key->src)) अणु
			dev_err(&adapter->pdev->dev,
				"ipv6 addr should not be loopback\n");
			वापस IAVF_ERR_CONFIG;
		पूर्ण
		अगर (!ipv6_addr_any(&match.mask->dst) ||
		    !ipv6_addr_any(&match.mask->src))
			field_flags |= IAVF_CLOUD_FIELD_IIP;

		क्रम (i = 0; i < 4; i++)
			vf->mask.tcp_spec.dst_ip[i] |= cpu_to_be32(0xffffffff);
		स_नकल(&vf->data.tcp_spec.dst_ip, &match.key->dst.s6_addr32,
		       माप(vf->data.tcp_spec.dst_ip));
		क्रम (i = 0; i < 4; i++)
			vf->mask.tcp_spec.src_ip[i] |= cpu_to_be32(0xffffffff);
		स_नकल(&vf->data.tcp_spec.src_ip, &match.key->src.s6_addr32,
		       माप(vf->data.tcp_spec.src_ip));
	पूर्ण
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		अगर (match.mask->src) अणु
			अगर (match.mask->src == cpu_to_be16(0xffff)) अणु
				field_flags |= IAVF_CLOUD_FIELD_IIP;
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev, "Bad src port mask %u\n",
					be16_to_cpu(match.mask->src));
				वापस IAVF_ERR_CONFIG;
			पूर्ण
		पूर्ण

		अगर (match.mask->dst) अणु
			अगर (match.mask->dst == cpu_to_be16(0xffff)) अणु
				field_flags |= IAVF_CLOUD_FIELD_IIP;
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev, "Bad dst port mask %u\n",
					be16_to_cpu(match.mask->dst));
				वापस IAVF_ERR_CONFIG;
			पूर्ण
		पूर्ण
		अगर (match.key->dst) अणु
			vf->mask.tcp_spec.dst_port |= cpu_to_be16(0xffff);
			vf->data.tcp_spec.dst_port = match.key->dst;
		पूर्ण

		अगर (match.key->src) अणु
			vf->mask.tcp_spec.src_port |= cpu_to_be16(0xffff);
			vf->data.tcp_spec.src_port = match.key->src;
		पूर्ण
	पूर्ण
	vf->field_flags = field_flags;

	वापस 0;
पूर्ण

/**
 * iavf_handle_tclass - Forward to a traffic class on the device
 * @adapter: board निजी काष्ठाure
 * @tc: traffic class index on the device
 * @filter: poपूर्णांकer to cloud filter काष्ठाure
 */
अटल पूर्णांक iavf_handle_tclass(काष्ठा iavf_adapter *adapter, u32 tc,
			      काष्ठा iavf_cloud_filter *filter)
अणु
	अगर (tc == 0)
		वापस 0;
	अगर (tc < adapter->num_tc) अणु
		अगर (!filter->f.data.tcp_spec.dst_port) अणु
			dev_err(&adapter->pdev->dev,
				"Specify destination port to redirect to traffic class other than TC0\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* redirect to a traffic class on the same device */
	filter->f.action = VIRTCHNL_ACTION_TC_REसूचीECT;
	filter->f.action_meta = tc;
	वापस 0;
पूर्ण

/**
 * iavf_configure_clsflower - Add tc flower filters
 * @adapter: board निजी काष्ठाure
 * @cls_flower: Poपूर्णांकer to काष्ठा flow_cls_offload
 */
अटल पूर्णांक iavf_configure_clsflower(काष्ठा iavf_adapter *adapter,
				    काष्ठा flow_cls_offload *cls_flower)
अणु
	पूर्णांक tc = tc_classid_to_hwtc(adapter->netdev, cls_flower->classid);
	काष्ठा iavf_cloud_filter *filter = शून्य;
	पूर्णांक err = -EINVAL, count = 50;

	अगर (tc < 0) अणु
		dev_err(&adapter->pdev->dev, "Invalid traffic class\n");
		वापस -EINVAL;
	पूर्ण

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (!filter)
		वापस -ENOMEM;

	जबतक (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section)) अणु
		अगर (--count == 0)
			जाओ err;
		udelay(1);
	पूर्ण

	filter->cookie = cls_flower->cookie;

	/* set the mask to all zeroes to begin with */
	स_रखो(&filter->f.mask.tcp_spec, 0, माप(काष्ठा virtchnl_l4_spec));
	/* start out with flow type and eth type IPv4 to begin with */
	filter->f.flow_type = VIRTCHNL_TCP_V4_FLOW;
	err = iavf_parse_cls_flower(adapter, cls_flower, filter);
	अगर (err < 0)
		जाओ err;

	err = iavf_handle_tclass(adapter, tc, filter);
	अगर (err < 0)
		जाओ err;

	/* add filter to the list */
	spin_lock_bh(&adapter->cloud_filter_list_lock);
	list_add_tail(&filter->list, &adapter->cloud_filter_list);
	adapter->num_cloud_filters++;
	filter->add = true;
	adapter->aq_required |= IAVF_FLAG_AQ_ADD_CLOUD_FILTER;
	spin_unlock_bh(&adapter->cloud_filter_list_lock);
err:
	अगर (err)
		kमुक्त(filter);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);
	वापस err;
पूर्ण

/* iavf_find_cf - Find the cloud filter in the list
 * @adapter: Board निजी काष्ठाure
 * @cookie: filter specअगरic cookie
 *
 * Returns ptr to the filter object or शून्य. Must be called जबतक holding the
 * cloud_filter_list_lock.
 */
अटल काष्ठा iavf_cloud_filter *iavf_find_cf(काष्ठा iavf_adapter *adapter,
					      अचिन्हित दीर्घ *cookie)
अणु
	काष्ठा iavf_cloud_filter *filter = शून्य;

	अगर (!cookie)
		वापस शून्य;

	list_क्रम_each_entry(filter, &adapter->cloud_filter_list, list) अणु
		अगर (!स_भेद(cookie, &filter->cookie, माप(filter->cookie)))
			वापस filter;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * iavf_delete_clsflower - Remove tc flower filters
 * @adapter: board निजी काष्ठाure
 * @cls_flower: Poपूर्णांकer to काष्ठा flow_cls_offload
 */
अटल पूर्णांक iavf_delete_clsflower(काष्ठा iavf_adapter *adapter,
				 काष्ठा flow_cls_offload *cls_flower)
अणु
	काष्ठा iavf_cloud_filter *filter = शून्य;
	पूर्णांक err = 0;

	spin_lock_bh(&adapter->cloud_filter_list_lock);
	filter = iavf_find_cf(adapter, &cls_flower->cookie);
	अगर (filter) अणु
		filter->del = true;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_CLOUD_FILTER;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण
	spin_unlock_bh(&adapter->cloud_filter_list_lock);

	वापस err;
पूर्ण

/**
 * iavf_setup_tc_cls_flower - flower classअगरier offloads
 * @adapter: board निजी काष्ठाure
 * @cls_flower: poपूर्णांकer to flow_cls_offload काष्ठा with flow info
 */
अटल पूर्णांक iavf_setup_tc_cls_flower(काष्ठा iavf_adapter *adapter,
				    काष्ठा flow_cls_offload *cls_flower)
अणु
	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस iavf_configure_clsflower(adapter, cls_flower);
	हाल FLOW_CLS_DESTROY:
		वापस iavf_delete_clsflower(adapter, cls_flower);
	हाल FLOW_CLS_STATS:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * iavf_setup_tc_block_cb - block callback क्रम tc
 * @type: type of offload
 * @type_data: offload data
 * @cb_priv:
 *
 * This function is the block callback क्रम traffic classes
 **/
अटल पूर्णांक iavf_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				  व्योम *cb_priv)
अणु
	काष्ठा iavf_adapter *adapter = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(adapter->netdev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस iavf_setup_tc_cls_flower(cb_priv, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(iavf_block_cb_list);

/**
 * iavf_setup_tc - configure multiple traffic classes
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @type: type of offload
 * @type_data: tc offload data
 *
 * This function is the callback to nकरो_setup_tc in the
 * netdev_ops.
 *
 * Returns 0 on success
 **/
अटल पूर्णांक iavf_setup_tc(काष्ठा net_device *netdev, क्रमागत tc_setup_type type,
			 व्योम *type_data)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	चयन (type) अणु
	हाल TC_SETUP_QDISC_MQPRIO:
		वापस __iavf_setup_tc(netdev, type_data);
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &iavf_block_cb_list,
						  iavf_setup_tc_block_cb,
						  adapter, adapter, true);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * iavf_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
अटल पूर्णांक iavf_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	अगर (adapter->flags & IAVF_FLAG_PF_COMMS_FAILED) अणु
		dev_err(&adapter->pdev->dev, "Unable to open device due to PF driver failure.\n");
		वापस -EIO;
	पूर्ण

	जबतक (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section))
		usleep_range(500, 1000);

	अगर (adapter->state != __IAVF_DOWN) अणु
		err = -EBUSY;
		जाओ err_unlock;
	पूर्ण

	/* allocate transmit descriptors */
	err = iavf_setup_all_tx_resources(adapter);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = iavf_setup_all_rx_resources(adapter);
	अगर (err)
		जाओ err_setup_rx;

	/* clear any pending पूर्णांकerrupts, may स्वतः mask */
	err = iavf_request_traffic_irqs(adapter, netdev->name);
	अगर (err)
		जाओ err_req_irq;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	iavf_add_filter(adapter, adapter->hw.mac.addr);

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	iavf_configure(adapter);

	iavf_up_complete(adapter);

	iavf_irq_enable(adapter, true);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	वापस 0;

err_req_irq:
	iavf_करोwn(adapter);
	iavf_मुक्त_traffic_irqs(adapter);
err_setup_rx:
	iavf_मुक्त_all_rx_resources(adapter);
err_setup_tx:
	iavf_मुक्त_all_tx_resources(adapter);
err_unlock:
	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	वापस err;
पूर्ण

/**
 * iavf_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled. All IRQs except vector 0 (reserved क्रम admin queue)
 * are मुक्तd, aदीर्घ with all transmit and receive resources.
 **/
अटल पूर्णांक iavf_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status;

	अगर (adapter->state <= __IAVF_DOWN_PENDING)
		वापस 0;

	जबतक (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section))
		usleep_range(500, 1000);

	set_bit(__IAVF_VSI_DOWN, adapter->vsi.state);
	अगर (CLIENT_ENABLED(adapter))
		adapter->flags |= IAVF_FLAG_CLIENT_NEEDS_CLOSE;

	iavf_करोwn(adapter);
	adapter->state = __IAVF_DOWN_PENDING;
	iavf_मुक्त_traffic_irqs(adapter);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	/* We explicitly करोn't मुक्त resources here because the hardware is
	 * still active and can DMA पूर्णांकo memory. Resources are cleared in
	 * iavf_virtchnl_completion() after we get confirmation from the PF
	 * driver that the rings have been stopped.
	 *
	 * Also, we रुको क्रम state to transition to __IAVF_DOWN beक्रमe
	 * वापसing. State change occurs in iavf_virtchnl_completion() after
	 * VF resources are released (which occurs after PF driver processes and
	 * responds to admin queue commands).
	 */

	status = रुको_event_समयout(adapter->करोwn_रुकोqueue,
				    adapter->state == __IAVF_DOWN,
				    msecs_to_jअगरfies(500));
	अगर (!status)
		netdev_warn(netdev, "Device resources not yet released\n");
	वापस 0;
पूर्ण

/**
 * iavf_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक iavf_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	netdev->mtu = new_mtu;
	अगर (CLIENT_ENABLED(adapter)) अणु
		iavf_notअगरy_client_l2_params(&adapter->vsi);
		adapter->flags |= IAVF_FLAG_SERVICE_CLIENT_REQUESTED;
	पूर्ण
	adapter->flags |= IAVF_FLAG_RESET_NEEDED;
	queue_work(iavf_wq, &adapter->reset_task);

	वापस 0;
पूर्ण

/**
 * iavf_set_features - set the netdev feature flags
 * @netdev: ptr to the netdev being adjusted
 * @features: the feature set that the stack is suggesting
 * Note: expects to be called जबतक under rtnl_lock()
 **/
अटल पूर्णांक iavf_set_features(काष्ठा net_device *netdev,
			     netdev_features_t features)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	/* Don't allow changing VLAN_RX flag when adapter is not capable
	 * of VLAN offload
	 */
	अगर (!VLAN_ALLOWED(adapter)) अणु
		अगर ((netdev->features ^ features) & NETIF_F_HW_VLAN_CTAG_RX)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर ((netdev->features ^ features) & NETIF_F_HW_VLAN_CTAG_RX) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
			adapter->aq_required |=
				IAVF_FLAG_AQ_ENABLE_VLAN_STRIPPING;
		अन्यथा
			adapter->aq_required |=
				IAVF_FLAG_AQ_DISABLE_VLAN_STRIPPING;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_features_check - Validate encapsulated packet conक्रमms to limits
 * @skb: skb buff
 * @dev: This physical port's netdev
 * @features: Offload features that the stack believes apply
 **/
अटल netdev_features_t iavf_features_check(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	माप_प्रकार len;

	/* No poपूर्णांक in करोing any of this अगर neither checksum nor GSO are
	 * being requested क्रम this frame.  We can rule out both by just
	 * checking क्रम CHECKSUM_PARTIAL
	 */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस features;

	/* We cannot support GSO अगर the MSS is going to be less than
	 * 64 bytes.  If it is then we need to drop support क्रम GSO.
	 */
	अगर (skb_is_gso(skb) && (skb_shinfo(skb)->gso_size < 64))
		features &= ~NETIF_F_GSO_MASK;

	/* MACLEN can support at most 63 words */
	len = skb_network_header(skb) - skb->data;
	अगर (len & ~(63 * 2))
		जाओ out_err;

	/* IPLEN and EIPLEN can support at most 127 dwords */
	len = skb_transport_header(skb) - skb_network_header(skb);
	अगर (len & ~(127 * 4))
		जाओ out_err;

	अगर (skb->encapsulation) अणु
		/* L4TUNLEN can support 127 words */
		len = skb_inner_network_header(skb) - skb_transport_header(skb);
		अगर (len & ~(127 * 2))
			जाओ out_err;

		/* IPLEN can support at most 127 dwords */
		len = skb_inner_transport_header(skb) -
		      skb_inner_network_header(skb);
		अगर (len & ~(127 * 4))
			जाओ out_err;
	पूर्ण

	/* No need to validate L4LEN as TCP is the only protocol with a
	 * a flexible value and we support all possible values supported
	 * by TCP, which is at most 15 dwords
	 */

	वापस features;
out_err:
	वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
पूर्ण

/**
 * iavf_fix_features - fix up the netdev feature bits
 * @netdev: our net device
 * @features: desired feature bits
 *
 * Returns fixed-up features bits
 **/
अटल netdev_features_t iavf_fix_features(काष्ठा net_device *netdev,
					   netdev_features_t features)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	अगर (!(adapter->vf_res->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_VLAN))
		features &= ~(NETIF_F_HW_VLAN_CTAG_TX |
			      NETIF_F_HW_VLAN_CTAG_RX |
			      NETIF_F_HW_VLAN_CTAG_FILTER);

	वापस features;
पूर्ण

अटल स्थिर काष्ठा net_device_ops iavf_netdev_ops = अणु
	.nकरो_खोलो		= iavf_खोलो,
	.nकरो_stop		= iavf_बंद,
	.nकरो_start_xmit		= iavf_xmit_frame,
	.nकरो_set_rx_mode	= iavf_set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= iavf_set_mac,
	.nकरो_change_mtu		= iavf_change_mtu,
	.nकरो_tx_समयout		= iavf_tx_समयout,
	.nकरो_vlan_rx_add_vid	= iavf_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= iavf_vlan_rx_समाप्त_vid,
	.nकरो_features_check	= iavf_features_check,
	.nकरो_fix_features	= iavf_fix_features,
	.nकरो_set_features	= iavf_set_features,
	.nकरो_setup_tc		= iavf_setup_tc,
पूर्ण;

/**
 * iavf_check_reset_complete - check that VF reset is complete
 * @hw: poपूर्णांकer to hw काष्ठा
 *
 * Returns 0 अगर device is पढ़ोy to use, or -EBUSY अगर it's in reset.
 **/
अटल पूर्णांक iavf_check_reset_complete(काष्ठा iavf_hw *hw)
अणु
	u32 rstat;
	पूर्णांक i;

	क्रम (i = 0; i < IAVF_RESET_WAIT_COMPLETE_COUNT; i++) अणु
		rstat = rd32(hw, IAVF_VFGEN_RSTAT) &
			     IAVF_VFGEN_RSTAT_VFR_STATE_MASK;
		अगर ((rstat == VIRTCHNL_VFR_VFACTIVE) ||
		    (rstat == VIRTCHNL_VFR_COMPLETED))
			वापस 0;
		usleep_range(10, 20);
	पूर्ण
	वापस -EBUSY;
पूर्ण

/**
 * iavf_process_config - Process the config inक्रमmation we got from the PF
 * @adapter: board निजी काष्ठाure
 *
 * Verअगरy that we have a valid config काष्ठा, and set up our netdev features
 * and our VSI काष्ठा.
 **/
पूर्णांक iavf_process_config(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_vf_resource *vfres = adapter->vf_res;
	पूर्णांक i, num_req_queues = adapter->num_req_queues;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा iavf_vsi *vsi = &adapter->vsi;
	netdev_features_t hw_enc_features;
	netdev_features_t hw_features;

	/* got VF config message back from PF, now we can parse it */
	क्रम (i = 0; i < vfres->num_vsis; i++) अणु
		अगर (vfres->vsi_res[i].vsi_type == VIRTCHNL_VSI_SRIOV)
			adapter->vsi_res = &vfres->vsi_res[i];
	पूर्ण
	अगर (!adapter->vsi_res) अणु
		dev_err(&adapter->pdev->dev, "No LAN VSI found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (num_req_queues &&
	    num_req_queues > adapter->vsi_res->num_queue_pairs) अणु
		/* Problem.  The PF gave us fewer queues than what we had
		 * negotiated in our request.  Need a reset to see अगर we can't
		 * get back to a working state.
		 */
		dev_err(&adapter->pdev->dev,
			"Requested %d queues, but PF only gave us %d.\n",
			num_req_queues,
			adapter->vsi_res->num_queue_pairs);
		adapter->flags |= IAVF_FLAG_REINIT_ITR_NEEDED;
		adapter->num_req_queues = adapter->vsi_res->num_queue_pairs;
		iavf_schedule_reset(adapter);
		वापस -ENODEV;
	पूर्ण
	adapter->num_req_queues = 0;

	hw_enc_features = NETIF_F_SG			|
			  NETIF_F_IP_CSUM		|
			  NETIF_F_IPV6_CSUM		|
			  NETIF_F_HIGHDMA		|
			  NETIF_F_SOFT_FEATURES	|
			  NETIF_F_TSO			|
			  NETIF_F_TSO_ECN		|
			  NETIF_F_TSO6			|
			  NETIF_F_SCTP_CRC		|
			  NETIF_F_RXHASH		|
			  NETIF_F_RXCSUM		|
			  0;

	/* advertise to stack only अगर offloads क्रम encapsulated packets is
	 * supported
	 */
	अगर (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ENCAP) अणु
		hw_enc_features |= NETIF_F_GSO_UDP_TUNNEL	|
				   NETIF_F_GSO_GRE		|
				   NETIF_F_GSO_GRE_CSUM		|
				   NETIF_F_GSO_IPXIP4		|
				   NETIF_F_GSO_IPXIP6		|
				   NETIF_F_GSO_UDP_TUNNEL_CSUM	|
				   NETIF_F_GSO_PARTIAL		|
				   0;

		अगर (!(vfres->vf_cap_flags &
		      VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM))
			netdev->gso_partial_features |=
				NETIF_F_GSO_UDP_TUNNEL_CSUM;

		netdev->gso_partial_features |= NETIF_F_GSO_GRE_CSUM;
		netdev->hw_enc_features |= NETIF_F_TSO_MANGLEID;
		netdev->hw_enc_features |= hw_enc_features;
	पूर्ण
	/* record features VLANs can make use of */
	netdev->vlan_features |= hw_enc_features | NETIF_F_TSO_MANGLEID;

	/* Write features and hw_features separately to aव्योम polluting
	 * with, or dropping, features that are set when we रेजिस्टरed.
	 */
	hw_features = hw_enc_features;

	/* Enable VLAN features अगर supported */
	अगर (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_VLAN)
		hw_features |= (NETIF_F_HW_VLAN_CTAG_TX |
				NETIF_F_HW_VLAN_CTAG_RX);
	/* Enable cloud filter अगर ADQ is supported */
	अगर (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ADQ)
		hw_features |= NETIF_F_HW_TC;
	अगर (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_USO)
		hw_features |= NETIF_F_GSO_UDP_L4;

	netdev->hw_features |= hw_features;

	netdev->features |= hw_features;

	अगर (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_VLAN)
		netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* Do not turn on offloads when they are requested to be turned off.
	 * TSO needs minimum 576 bytes to work correctly.
	 */
	अगर (netdev->wanted_features) अणु
		अगर (!(netdev->wanted_features & NETIF_F_TSO) ||
		    netdev->mtu < 576)
			netdev->features &= ~NETIF_F_TSO;
		अगर (!(netdev->wanted_features & NETIF_F_TSO6) ||
		    netdev->mtu < 576)
			netdev->features &= ~NETIF_F_TSO6;
		अगर (!(netdev->wanted_features & NETIF_F_TSO_ECN))
			netdev->features &= ~NETIF_F_TSO_ECN;
		अगर (!(netdev->wanted_features & NETIF_F_GRO))
			netdev->features &= ~NETIF_F_GRO;
		अगर (!(netdev->wanted_features & NETIF_F_GSO))
			netdev->features &= ~NETIF_F_GSO;
	पूर्ण

	adapter->vsi.id = adapter->vsi_res->vsi_id;

	adapter->vsi.back = adapter;
	adapter->vsi.base_vector = 1;
	adapter->vsi.work_limit = IAVF_DEFAULT_IRQ_WORK;
	vsi->netdev = adapter->netdev;
	vsi->qs_handle = adapter->vsi_res->qset_handle;
	अगर (vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_RSS_PF) अणु
		adapter->rss_key_size = vfres->rss_key_size;
		adapter->rss_lut_size = vfres->rss_lut_size;
	पूर्ण अन्यथा अणु
		adapter->rss_key_size = IAVF_HKEY_ARRAY_SIZE;
		adapter->rss_lut_size = IAVF_HLUT_ARRAY_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_init_task - worker thपढ़ो to perक्रमm delayed initialization
 * @work: poपूर्णांकer to work_काष्ठा containing our data
 *
 * This task completes the work that was begun in probe. Due to the nature
 * of VF-PF communications, we may need to रुको tens of milliseconds to get
 * responses back from the PF. Rather than busy-रुको in probe and bog करोwn the
 * whole प्रणाली, we'll करो it in a task so we can sleep.
 * This task only runs during driver init. Once we've established
 * communications with the PF driver and set up our netdev, the watchकरोg
 * takes over.
 **/
अटल व्योम iavf_init_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iavf_adapter *adapter = container_of(work,
						    काष्ठा iavf_adapter,
						    init_task.work);
	काष्ठा iavf_hw *hw = &adapter->hw;

	चयन (adapter->state) अणु
	हाल __IAVF_STARTUP:
		अगर (iavf_startup(adapter) < 0)
			जाओ init_failed;
		अवरोध;
	हाल __IAVF_INIT_VERSION_CHECK:
		अगर (iavf_init_version_check(adapter) < 0)
			जाओ init_failed;
		अवरोध;
	हाल __IAVF_INIT_GET_RESOURCES:
		अगर (iavf_init_get_resources(adapter) < 0)
			जाओ init_failed;
		वापस;
	शेष:
		जाओ init_failed;
	पूर्ण

	queue_delayed_work(iavf_wq, &adapter->init_task,
			   msecs_to_jअगरfies(30));
	वापस;
init_failed:
	अगर (++adapter->aq_रुको_count > IAVF_AQ_MAX_ERR) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to communicate with PF; waiting before retry\n");
		adapter->flags |= IAVF_FLAG_PF_COMMS_FAILED;
		iavf_shutकरोwn_adminq(hw);
		adapter->state = __IAVF_STARTUP;
		queue_delayed_work(iavf_wq, &adapter->init_task, HZ * 5);
		वापस;
	पूर्ण
	queue_delayed_work(iavf_wq, &adapter->init_task, HZ);
पूर्ण

/**
 * iavf_shutकरोwn - Shutकरोwn the device in preparation क्रम a reboot
 * @pdev: pci device काष्ठाure
 **/
अटल व्योम iavf_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		iavf_बंद(netdev);

	/* Prevent the watchकरोg from running. */
	adapter->state = __IAVF_REMOVE;
	adapter->aq_required = 0;

#अगर_घोषित CONFIG_PM
	pci_save_state(pdev);

#पूर्ण_अगर
	pci_disable_device(pdev);
पूर्ण

/**
 * iavf_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in iavf_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * iavf_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 **/
अटल पूर्णांक iavf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा iavf_adapter *adapter = शून्य;
	काष्ठा iavf_hw *hw = शून्य;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err) अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"DMA configuration failed: 0x%x\n", err);
			जाओ err_dma;
		पूर्ण
	पूर्ण

	err = pci_request_regions(pdev, iavf_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"pci_request_regions failed 0x%x\n", err);
		जाओ err_pci_reg;
	पूर्ण

	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);

	netdev = alloc_etherdev_mq(माप(काष्ठा iavf_adapter),
				   IAVF_MAX_REQ_QUEUES);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);

	adapter->netdev = netdev;
	adapter->pdev = pdev;

	hw = &adapter->hw;
	hw->back = adapter;

	adapter->msg_enable = BIT(DEFAULT_DEBUG_LEVEL_SHIFT) - 1;
	adapter->state = __IAVF_STARTUP;

	/* Call save state here because it relies on the adapter काष्ठा. */
	pci_save_state(pdev);

	hw->hw_addr = ioremap(pci_resource_start(pdev, 0),
			      pci_resource_len(pdev, 0));
	अगर (!hw->hw_addr) अणु
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	pci_पढ़ो_config_byte(pdev, PCI_REVISION_ID, &hw->revision_id);
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;
	hw->bus.device = PCI_SLOT(pdev->devfn);
	hw->bus.func = PCI_FUNC(pdev->devfn);
	hw->bus.bus_id = pdev->bus->number;

	/* set up the locks क्रम the AQ, करो this only once in probe
	 * and destroy them only once in हटाओ
	 */
	mutex_init(&hw->aq.asq_mutex);
	mutex_init(&hw->aq.arq_mutex);

	spin_lock_init(&adapter->mac_vlan_list_lock);
	spin_lock_init(&adapter->cloud_filter_list_lock);
	spin_lock_init(&adapter->fdir_fltr_lock);
	spin_lock_init(&adapter->adv_rss_lock);

	INIT_LIST_HEAD(&adapter->mac_filter_list);
	INIT_LIST_HEAD(&adapter->vlan_filter_list);
	INIT_LIST_HEAD(&adapter->cloud_filter_list);
	INIT_LIST_HEAD(&adapter->fdir_list_head);
	INIT_LIST_HEAD(&adapter->adv_rss_list_head);

	INIT_WORK(&adapter->reset_task, iavf_reset_task);
	INIT_WORK(&adapter->adminq_task, iavf_adminq_task);
	INIT_DELAYED_WORK(&adapter->watchकरोg_task, iavf_watchकरोg_task);
	INIT_DELAYED_WORK(&adapter->client_task, iavf_client_task);
	INIT_DELAYED_WORK(&adapter->init_task, iavf_init_task);
	queue_delayed_work(iavf_wq, &adapter->init_task,
			   msecs_to_jअगरfies(5 * (pdev->devfn & 0x07)));

	/* Setup the रुको queue क्रम indicating transition to करोwn status */
	init_रुकोqueue_head(&adapter->करोwn_रुकोqueue);

	वापस 0;

err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * iavf_suspend - Power management suspend routine
 * @dev_d: device info poपूर्णांकer
 *
 * Called when the प्रणाली (VM) is entering sleep/suspend.
 **/
अटल पूर्णांक __maybe_unused iavf_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev_d);
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	जबतक (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section))
		usleep_range(500, 1000);

	अगर (netअगर_running(netdev)) अणु
		rtnl_lock();
		iavf_करोwn(adapter);
		rtnl_unlock();
	पूर्ण
	iavf_मुक्त_misc_irq(adapter);
	iavf_reset_पूर्णांकerrupt_capability(adapter);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	वापस 0;
पूर्ण

/**
 * iavf_resume - Power management resume routine
 * @dev_d: device info poपूर्णांकer
 *
 * Called when the प्रणाली (VM) is resumed from sleep/suspend.
 **/
अटल पूर्णांक __maybe_unused iavf_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	u32 err;

	pci_set_master(pdev);

	rtnl_lock();
	err = iavf_set_पूर्णांकerrupt_capability(adapter);
	अगर (err) अणु
		rtnl_unlock();
		dev_err(&pdev->dev, "Cannot enable MSI-X interrupts.\n");
		वापस err;
	पूर्ण
	err = iavf_request_misc_irq(adapter);
	rtnl_unlock();
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot get interrupt vector.\n");
		वापस err;
	पूर्ण

	queue_work(iavf_wq, &adapter->reset_task);

	netअगर_device_attach(netdev);

	वापस err;
पूर्ण

/**
 * iavf_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * iavf_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम iavf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	काष्ठा iavf_fdir_fltr *fdir, *fdirपंचांगp;
	काष्ठा iavf_vlan_filter *vlf, *vlfपंचांगp;
	काष्ठा iavf_adv_rss *rss, *rssपंचांगp;
	काष्ठा iavf_mac_filter *f, *fपंचांगp;
	काष्ठा iavf_cloud_filter *cf, *cfपंचांगp;
	काष्ठा iavf_hw *hw = &adapter->hw;
	पूर्णांक err;
	/* Indicate we are in हटाओ and not to run reset_task */
	set_bit(__IAVF_IN_REMOVE_TASK, &adapter->crit_section);
	cancel_delayed_work_sync(&adapter->init_task);
	cancel_work_sync(&adapter->reset_task);
	cancel_delayed_work_sync(&adapter->client_task);
	अगर (adapter->netdev_रेजिस्टरed) अणु
		unरेजिस्टर_netdev(netdev);
		adapter->netdev_रेजिस्टरed = false;
	पूर्ण
	अगर (CLIENT_ALLOWED(adapter)) अणु
		err = iavf_lan_del_device(adapter);
		अगर (err)
			dev_warn(&pdev->dev, "Failed to delete client device: %d\n",
				 err);
	पूर्ण

	/* Shut करोwn all the garbage mashers on the detention level */
	adapter->state = __IAVF_REMOVE;
	adapter->aq_required = 0;
	adapter->flags &= ~IAVF_FLAG_REINIT_ITR_NEEDED;
	iavf_request_reset(adapter);
	msleep(50);
	/* If the FW isn't responding, kick it once, but only once. */
	अगर (!iavf_asq_करोne(hw)) अणु
		iavf_request_reset(adapter);
		msleep(50);
	पूर्ण
	iavf_मुक्त_all_tx_resources(adapter);
	iavf_मुक्त_all_rx_resources(adapter);
	iavf_misc_irq_disable(adapter);
	iavf_मुक्त_misc_irq(adapter);
	iavf_reset_पूर्णांकerrupt_capability(adapter);
	iavf_मुक्त_q_vectors(adapter);

	cancel_delayed_work_sync(&adapter->watchकरोg_task);

	cancel_work_sync(&adapter->adminq_task);

	iavf_मुक्त_rss(adapter);

	अगर (hw->aq.asq.count)
		iavf_shutकरोwn_adminq(hw);

	/* destroy the locks only once, here */
	mutex_destroy(&hw->aq.arq_mutex);
	mutex_destroy(&hw->aq.asq_mutex);

	iounmap(hw->hw_addr);
	pci_release_regions(pdev);
	iavf_मुक्त_queues(adapter);
	kमुक्त(adapter->vf_res);
	spin_lock_bh(&adapter->mac_vlan_list_lock);
	/* If we got हटाओd beक्रमe an up/करोwn sequence, we've got a filter
	 * hanging out there that we need to get rid of.
	 */
	list_क्रम_each_entry_safe(f, fपंचांगp, &adapter->mac_filter_list, list) अणु
		list_del(&f->list);
		kमुक्त(f);
	पूर्ण
	list_क्रम_each_entry_safe(vlf, vlfपंचांगp, &adapter->vlan_filter_list,
				 list) अणु
		list_del(&vlf->list);
		kमुक्त(vlf);
	पूर्ण

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	spin_lock_bh(&adapter->cloud_filter_list_lock);
	list_क्रम_each_entry_safe(cf, cfपंचांगp, &adapter->cloud_filter_list, list) अणु
		list_del(&cf->list);
		kमुक्त(cf);
	पूर्ण
	spin_unlock_bh(&adapter->cloud_filter_list_lock);

	spin_lock_bh(&adapter->fdir_fltr_lock);
	list_क्रम_each_entry_safe(fdir, fdirपंचांगp, &adapter->fdir_list_head, list) अणु
		list_del(&fdir->list);
		kमुक्त(fdir);
	पूर्ण
	spin_unlock_bh(&adapter->fdir_fltr_lock);

	spin_lock_bh(&adapter->adv_rss_lock);
	list_क्रम_each_entry_safe(rss, rssपंचांगp, &adapter->adv_rss_list_head,
				 list) अणु
		list_del(&rss->list);
		kमुक्त(rss);
	पूर्ण
	spin_unlock_bh(&adapter->adv_rss_lock);

	मुक्त_netdev(netdev);

	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(iavf_pm_ops, iavf_suspend, iavf_resume);

अटल काष्ठा pci_driver iavf_driver = अणु
	.name      = iavf_driver_name,
	.id_table  = iavf_pci_tbl,
	.probe     = iavf_probe,
	.हटाओ    = iavf_हटाओ,
	.driver.pm = &iavf_pm_ops,
	.shutकरोwn  = iavf_shutकरोwn,
पूर्ण;

/**
 * iavf_init_module - Driver Registration Routine
 *
 * iavf_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init iavf_init_module(व्योम)
अणु
	पूर्णांक ret;

	pr_info("iavf: %s\n", iavf_driver_string);

	pr_info("%s\n", iavf_copyright);

	iavf_wq = alloc_workqueue("%s", WQ_UNBOUND | WQ_MEM_RECLAIM, 1,
				  iavf_driver_name);
	अगर (!iavf_wq) अणु
		pr_err("%s: Failed to create workqueue\n", iavf_driver_name);
		वापस -ENOMEM;
	पूर्ण
	ret = pci_रेजिस्टर_driver(&iavf_driver);
	वापस ret;
पूर्ण

module_init(iavf_init_module);

/**
 * iavf_निकास_module - Driver Exit Cleanup Routine
 *
 * iavf_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/
अटल व्योम __निकास iavf_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&iavf_driver);
	destroy_workqueue(iavf_wq);
पूर्ण

module_निकास(iavf_निकास_module);

/* iavf_मुख्य.c */
