<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2018 Microchip Technology Inc. */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>
#समावेश <linux/microchipphy.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/crc16.h>
#समावेश "lan743x_main.h"
#समावेश "lan743x_ethtool.h"

अटल व्योम lan743x_pci_cleanup(काष्ठा lan743x_adapter *adapter)
अणु
	pci_release_selected_regions(adapter->pdev,
				     pci_select_bars(adapter->pdev,
						     IORESOURCE_MEM));
	pci_disable_device(adapter->pdev);
पूर्ण

अटल पूर्णांक lan743x_pci_init(काष्ठा lan743x_adapter *adapter,
			    काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ bars = 0;
	पूर्णांक ret;

	adapter->pdev = pdev;
	ret = pci_enable_device_mem(pdev);
	अगर (ret)
		जाओ वापस_error;

	netअगर_info(adapter, probe, adapter->netdev,
		   "PCI: Vendor ID = 0x%04X, Device ID = 0x%04X\n",
		   pdev->venकरोr, pdev->device);
	bars = pci_select_bars(pdev, IORESOURCE_MEM);
	अगर (!test_bit(0, &bars))
		जाओ disable_device;

	ret = pci_request_selected_regions(pdev, bars, DRIVER_NAME);
	अगर (ret)
		जाओ disable_device;

	pci_set_master(pdev);
	वापस 0;

disable_device:
	pci_disable_device(adapter->pdev);

वापस_error:
	वापस ret;
पूर्ण

u32 lan743x_csr_पढ़ो(काष्ठा lan743x_adapter *adapter, पूर्णांक offset)
अणु
	वापस ioपढ़ो32(&adapter->csr.csr_address[offset]);
पूर्ण

व्योम lan743x_csr_ग_लिखो(काष्ठा lan743x_adapter *adapter, पूर्णांक offset,
		       u32 data)
अणु
	ioग_लिखो32(data, &adapter->csr.csr_address[offset]);
पूर्ण

#घोषणा LAN743X_CSR_READ_OP(offset)	lan743x_csr_पढ़ो(adapter, offset)

अटल पूर्णांक lan743x_csr_light_reset(काष्ठा lan743x_adapter *adapter)
अणु
	u32 data;

	data = lan743x_csr_पढ़ो(adapter, HW_CFG);
	data |= HW_CFG_LRST_;
	lan743x_csr_ग_लिखो(adapter, HW_CFG, data);

	वापस पढ़ोx_poll_समयout(LAN743X_CSR_READ_OP, HW_CFG, data,
				  !(data & HW_CFG_LRST_), 100000, 10000000);
पूर्ण

अटल पूर्णांक lan743x_csr_रुको_क्रम_bit(काष्ठा lan743x_adapter *adapter,
				    पूर्णांक offset, u32 bit_mask,
				    पूर्णांक target_value, पूर्णांक usleep_min,
				    पूर्णांक usleep_max, पूर्णांक count)
अणु
	u32 data;

	वापस पढ़ोx_poll_समयout(LAN743X_CSR_READ_OP, offset, data,
				  target_value == ((data & bit_mask) ? 1 : 0),
				  usleep_max, usleep_min * count);
पूर्ण

अटल पूर्णांक lan743x_csr_init(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_csr *csr = &adapter->csr;
	resource_माप_प्रकार bar_start, bar_length;
	पूर्णांक result;

	bar_start = pci_resource_start(adapter->pdev, 0);
	bar_length = pci_resource_len(adapter->pdev, 0);
	csr->csr_address = devm_ioremap(&adapter->pdev->dev,
					bar_start, bar_length);
	अगर (!csr->csr_address) अणु
		result = -ENOMEM;
		जाओ clean_up;
	पूर्ण

	csr->id_rev = lan743x_csr_पढ़ो(adapter, ID_REV);
	csr->fpga_rev = lan743x_csr_पढ़ो(adapter, FPGA_REV);
	netअगर_info(adapter, probe, adapter->netdev,
		   "ID_REV = 0x%08X, FPGA_REV = %d.%d\n",
		   csr->id_rev,	FPGA_REV_GET_MAJOR_(csr->fpga_rev),
		   FPGA_REV_GET_MINOR_(csr->fpga_rev));
	अगर (!ID_REV_IS_VALID_CHIP_ID_(csr->id_rev)) अणु
		result = -ENODEV;
		जाओ clean_up;
	पूर्ण

	csr->flags = LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR;
	चयन (csr->id_rev & ID_REV_CHIP_REV_MASK_) अणु
	हाल ID_REV_CHIP_REV_A0_:
		csr->flags |= LAN743X_CSR_FLAG_IS_A0;
		csr->flags &= ~LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR;
		अवरोध;
	हाल ID_REV_CHIP_REV_B0_:
		csr->flags |= LAN743X_CSR_FLAG_IS_B0;
		अवरोध;
	पूर्ण

	result = lan743x_csr_light_reset(adapter);
	अगर (result)
		जाओ clean_up;
	वापस 0;
clean_up:
	वापस result;
पूर्ण

अटल व्योम lan743x_पूर्णांकr_software_isr(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_पूर्णांकr *पूर्णांकr = &adapter->पूर्णांकr;

	/* disable the पूर्णांकerrupt to prevent repeated re-triggering */
	lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, INT_BIT_SW_GP_);
	पूर्णांकr->software_isr_flag = true;
	wake_up(&पूर्णांकr->software_isr_wq);
पूर्ण

अटल व्योम lan743x_tx_isr(व्योम *context, u32 पूर्णांक_sts, u32 flags)
अणु
	काष्ठा lan743x_tx *tx = context;
	काष्ठा lan743x_adapter *adapter = tx->adapter;
	bool enable_flag = true;

	lan743x_csr_पढ़ो(adapter, INT_EN_SET);
	अगर (flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CLEAR) अणु
		lan743x_csr_ग_लिखो(adapter, INT_EN_CLR,
				  INT_BIT_DMA_TX_(tx->channel_number));
	पूर्ण

	अगर (पूर्णांक_sts & INT_BIT_DMA_TX_(tx->channel_number)) अणु
		u32 ioc_bit = DMAC_INT_BIT_TX_IOC_(tx->channel_number);
		u32 dmac_पूर्णांक_sts;
		u32 dmac_पूर्णांक_en;

		अगर (flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_READ)
			dmac_पूर्णांक_sts = lan743x_csr_पढ़ो(adapter, DMAC_INT_STS);
		अन्यथा
			dmac_पूर्णांक_sts = ioc_bit;
		अगर (flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CHECK)
			dmac_पूर्णांक_en = lan743x_csr_पढ़ो(adapter,
						       DMAC_INT_EN_SET);
		अन्यथा
			dmac_पूर्णांक_en = ioc_bit;

		dmac_पूर्णांक_en &= ioc_bit;
		dmac_पूर्णांक_sts &= dmac_पूर्णांक_en;
		अगर (dmac_पूर्णांक_sts & ioc_bit) अणु
			napi_schedule(&tx->napi);
			enable_flag = false;/* poll func will enable later */
		पूर्ण
	पूर्ण

	अगर (enable_flag)
		/* enable isr */
		lan743x_csr_ग_लिखो(adapter, INT_EN_SET,
				  INT_BIT_DMA_TX_(tx->channel_number));
पूर्ण

अटल व्योम lan743x_rx_isr(व्योम *context, u32 पूर्णांक_sts, u32 flags)
अणु
	काष्ठा lan743x_rx *rx = context;
	काष्ठा lan743x_adapter *adapter = rx->adapter;
	bool enable_flag = true;

	अगर (flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CLEAR) अणु
		lan743x_csr_ग_लिखो(adapter, INT_EN_CLR,
				  INT_BIT_DMA_RX_(rx->channel_number));
	पूर्ण

	अगर (पूर्णांक_sts & INT_BIT_DMA_RX_(rx->channel_number)) अणु
		u32 rx_frame_bit = DMAC_INT_BIT_RXFRM_(rx->channel_number);
		u32 dmac_पूर्णांक_sts;
		u32 dmac_पूर्णांक_en;

		अगर (flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_READ)
			dmac_पूर्णांक_sts = lan743x_csr_पढ़ो(adapter, DMAC_INT_STS);
		अन्यथा
			dmac_पूर्णांक_sts = rx_frame_bit;
		अगर (flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CHECK)
			dmac_पूर्णांक_en = lan743x_csr_पढ़ो(adapter,
						       DMAC_INT_EN_SET);
		अन्यथा
			dmac_पूर्णांक_en = rx_frame_bit;

		dmac_पूर्णांक_en &= rx_frame_bit;
		dmac_पूर्णांक_sts &= dmac_पूर्णांक_en;
		अगर (dmac_पूर्णांक_sts & rx_frame_bit) अणु
			napi_schedule(&rx->napi);
			enable_flag = false;/* poll funct will enable later */
		पूर्ण
	पूर्ण

	अगर (enable_flag) अणु
		/* enable isr */
		lan743x_csr_ग_लिखो(adapter, INT_EN_SET,
				  INT_BIT_DMA_RX_(rx->channel_number));
	पूर्ण
पूर्ण

अटल व्योम lan743x_पूर्णांकr_shared_isr(व्योम *context, u32 पूर्णांक_sts, u32 flags)
अणु
	काष्ठा lan743x_adapter *adapter = context;
	अचिन्हित पूर्णांक channel;

	अगर (पूर्णांक_sts & INT_BIT_ALL_RX_) अणु
		क्रम (channel = 0; channel < LAN743X_USED_RX_CHANNELS;
			channel++) अणु
			u32 पूर्णांक_bit = INT_BIT_DMA_RX_(channel);

			अगर (पूर्णांक_sts & पूर्णांक_bit) अणु
				lan743x_rx_isr(&adapter->rx[channel],
					       पूर्णांक_bit, flags);
				पूर्णांक_sts &= ~पूर्णांक_bit;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (पूर्णांक_sts & INT_BIT_ALL_TX_) अणु
		क्रम (channel = 0; channel < LAN743X_USED_TX_CHANNELS;
			channel++) अणु
			u32 पूर्णांक_bit = INT_BIT_DMA_TX_(channel);

			अगर (पूर्णांक_sts & पूर्णांक_bit) अणु
				lan743x_tx_isr(&adapter->tx[channel],
					       पूर्णांक_bit, flags);
				पूर्णांक_sts &= ~पूर्णांक_bit;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (पूर्णांक_sts & INT_BIT_ALL_OTHER_) अणु
		अगर (पूर्णांक_sts & INT_BIT_SW_GP_) अणु
			lan743x_पूर्णांकr_software_isr(adapter);
			पूर्णांक_sts &= ~INT_BIT_SW_GP_;
		पूर्ण
		अगर (पूर्णांक_sts & INT_BIT_1588_) अणु
			lan743x_ptp_isr(adapter);
			पूर्णांक_sts &= ~INT_BIT_1588_;
		पूर्ण
	पूर्ण
	अगर (पूर्णांक_sts)
		lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, पूर्णांक_sts);
पूर्ण

अटल irqवापस_t lan743x_पूर्णांकr_entry_isr(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा lan743x_vector *vector = ptr;
	काष्ठा lan743x_adapter *adapter = vector->adapter;
	irqवापस_t result = IRQ_NONE;
	u32 पूर्णांक_enables;
	u32 पूर्णांक_sts;

	अगर (vector->flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_READ) अणु
		पूर्णांक_sts = lan743x_csr_पढ़ो(adapter, INT_STS);
	पूर्ण अन्यथा अगर (vector->flags &
		   (LAN743X_VECTOR_FLAG_SOURCE_STATUS_R2C |
		   LAN743X_VECTOR_FLAG_SOURCE_ENABLE_R2C)) अणु
		पूर्णांक_sts = lan743x_csr_पढ़ो(adapter, INT_STS_R2C);
	पूर्ण अन्यथा अणु
		/* use mask as implied status */
		पूर्णांक_sts = vector->पूर्णांक_mask | INT_BIT_MAS_;
	पूर्ण

	अगर (!(पूर्णांक_sts & INT_BIT_MAS_))
		जाओ irq_करोne;

	अगर (vector->flags & LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_CLEAR)
		/* disable vector पूर्णांकerrupt */
		lan743x_csr_ग_लिखो(adapter,
				  INT_VEC_EN_CLR,
				  INT_VEC_EN_(vector->vector_index));

	अगर (vector->flags & LAN743X_VECTOR_FLAG_MASTER_ENABLE_CLEAR)
		/* disable master पूर्णांकerrupt */
		lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, INT_BIT_MAS_);

	अगर (vector->flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CHECK) अणु
		पूर्णांक_enables = lan743x_csr_पढ़ो(adapter, INT_EN_SET);
	पूर्ण अन्यथा अणु
		/*  use vector mask as implied enable mask */
		पूर्णांक_enables = vector->पूर्णांक_mask;
	पूर्ण

	पूर्णांक_sts &= पूर्णांक_enables;
	पूर्णांक_sts &= vector->पूर्णांक_mask;
	अगर (पूर्णांक_sts) अणु
		अगर (vector->handler) अणु
			vector->handler(vector->context,
					पूर्णांक_sts, vector->flags);
		पूर्ण अन्यथा अणु
			/* disable पूर्णांकerrupts on this vector */
			lan743x_csr_ग_लिखो(adapter, INT_EN_CLR,
					  vector->पूर्णांक_mask);
		पूर्ण
		result = IRQ_HANDLED;
	पूर्ण

	अगर (vector->flags & LAN743X_VECTOR_FLAG_MASTER_ENABLE_SET)
		/* enable master पूर्णांकerrupt */
		lan743x_csr_ग_लिखो(adapter, INT_EN_SET, INT_BIT_MAS_);

	अगर (vector->flags & LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_SET)
		/* enable vector पूर्णांकerrupt */
		lan743x_csr_ग_लिखो(adapter,
				  INT_VEC_EN_SET,
				  INT_VEC_EN_(vector->vector_index));
irq_करोne:
	वापस result;
पूर्ण

अटल पूर्णांक lan743x_पूर्णांकr_test_isr(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_पूर्णांकr *पूर्णांकr = &adapter->पूर्णांकr;
	पूर्णांक ret;

	पूर्णांकr->software_isr_flag = false;

	/* enable and activate test पूर्णांकerrupt */
	lan743x_csr_ग_लिखो(adapter, INT_EN_SET, INT_BIT_SW_GP_);
	lan743x_csr_ग_लिखो(adapter, INT_SET, INT_BIT_SW_GP_);

	ret = रुको_event_समयout(पूर्णांकr->software_isr_wq,
				 पूर्णांकr->software_isr_flag,
				 msecs_to_jअगरfies(200));

	/* disable test पूर्णांकerrupt */
	lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, INT_BIT_SW_GP_);

	वापस ret > 0 ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक lan743x_पूर्णांकr_रेजिस्टर_isr(काष्ठा lan743x_adapter *adapter,
				     पूर्णांक vector_index, u32 flags,
				     u32 पूर्णांक_mask,
				     lan743x_vector_handler handler,
				     व्योम *context)
अणु
	काष्ठा lan743x_vector *vector = &adapter->पूर्णांकr.vector_list
					[vector_index];
	पूर्णांक ret;

	vector->adapter = adapter;
	vector->flags = flags;
	vector->vector_index = vector_index;
	vector->पूर्णांक_mask = पूर्णांक_mask;
	vector->handler = handler;
	vector->context = context;

	ret = request_irq(vector->irq,
			  lan743x_पूर्णांकr_entry_isr,
			  (flags & LAN743X_VECTOR_FLAG_IRQ_SHARED) ?
			  IRQF_SHARED : 0, DRIVER_NAME, vector);
	अगर (ret) अणु
		vector->handler = शून्य;
		vector->context = शून्य;
		vector->पूर्णांक_mask = 0;
		vector->flags = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम lan743x_पूर्णांकr_unरेजिस्टर_isr(काष्ठा lan743x_adapter *adapter,
					पूर्णांक vector_index)
अणु
	काष्ठा lan743x_vector *vector = &adapter->पूर्णांकr.vector_list
					[vector_index];

	मुक्त_irq(vector->irq, vector);
	vector->handler = शून्य;
	vector->context = शून्य;
	vector->पूर्णांक_mask = 0;
	vector->flags = 0;
पूर्ण

अटल u32 lan743x_पूर्णांकr_get_vector_flags(काष्ठा lan743x_adapter *adapter,
					 u32 पूर्णांक_mask)
अणु
	पूर्णांक index;

	क्रम (index = 0; index < LAN743X_MAX_VECTOR_COUNT; index++) अणु
		अगर (adapter->पूर्णांकr.vector_list[index].पूर्णांक_mask & पूर्णांक_mask)
			वापस adapter->पूर्णांकr.vector_list[index].flags;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम lan743x_पूर्णांकr_बंद(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_पूर्णांकr *पूर्णांकr = &adapter->पूर्णांकr;
	पूर्णांक index = 0;

	lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, INT_BIT_MAS_);
	lan743x_csr_ग_लिखो(adapter, INT_VEC_EN_CLR, 0x000000FF);

	क्रम (index = 0; index < LAN743X_MAX_VECTOR_COUNT; index++) अणु
		अगर (पूर्णांकr->flags & INTR_FLAG_IRQ_REQUESTED(index)) अणु
			lan743x_पूर्णांकr_unरेजिस्टर_isr(adapter, index);
			पूर्णांकr->flags &= ~INTR_FLAG_IRQ_REQUESTED(index);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr->flags & INTR_FLAG_MSI_ENABLED) अणु
		pci_disable_msi(adapter->pdev);
		पूर्णांकr->flags &= ~INTR_FLAG_MSI_ENABLED;
	पूर्ण

	अगर (पूर्णांकr->flags & INTR_FLAG_MSIX_ENABLED) अणु
		pci_disable_msix(adapter->pdev);
		पूर्णांकr->flags &= ~INTR_FLAG_MSIX_ENABLED;
	पूर्ण
पूर्ण

अटल पूर्णांक lan743x_पूर्णांकr_खोलो(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा msix_entry msix_entries[LAN743X_MAX_VECTOR_COUNT];
	काष्ठा lan743x_पूर्णांकr *पूर्णांकr = &adapter->पूर्णांकr;
	u32 पूर्णांक_vec_en_स्वतः_clr = 0;
	u32 पूर्णांक_vec_map0 = 0;
	u32 पूर्णांक_vec_map1 = 0;
	पूर्णांक ret = -ENODEV;
	पूर्णांक index = 0;
	u32 flags = 0;

	पूर्णांकr->number_of_vectors = 0;

	/* Try to set up MSIX पूर्णांकerrupts */
	स_रखो(&msix_entries[0], 0,
	       माप(काष्ठा msix_entry) * LAN743X_MAX_VECTOR_COUNT);
	क्रम (index = 0; index < LAN743X_MAX_VECTOR_COUNT; index++)
		msix_entries[index].entry = index;
	ret = pci_enable_msix_range(adapter->pdev,
				    msix_entries, 1,
				    1 + LAN743X_USED_TX_CHANNELS +
				    LAN743X_USED_RX_CHANNELS);

	अगर (ret > 0) अणु
		पूर्णांकr->flags |= INTR_FLAG_MSIX_ENABLED;
		पूर्णांकr->number_of_vectors = ret;
		पूर्णांकr->using_vectors = true;
		क्रम (index = 0; index < पूर्णांकr->number_of_vectors; index++)
			पूर्णांकr->vector_list[index].irq = msix_entries
						       [index].vector;
		netअगर_info(adapter, अगरup, adapter->netdev,
			   "using MSIX interrupts, number of vectors = %d\n",
			   पूर्णांकr->number_of_vectors);
	पूर्ण

	/* If MSIX failed try to setup using MSI पूर्णांकerrupts */
	अगर (!पूर्णांकr->number_of_vectors) अणु
		अगर (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0)) अणु
			अगर (!pci_enable_msi(adapter->pdev)) अणु
				पूर्णांकr->flags |= INTR_FLAG_MSI_ENABLED;
				पूर्णांकr->number_of_vectors = 1;
				पूर्णांकr->using_vectors = true;
				पूर्णांकr->vector_list[0].irq =
					adapter->pdev->irq;
				netअगर_info(adapter, अगरup, adapter->netdev,
					   "using MSI interrupts, number of vectors = %d\n",
					   पूर्णांकr->number_of_vectors);
			पूर्ण
		पूर्ण
	पूर्ण

	/* If MSIX, and MSI failed, setup using legacy पूर्णांकerrupt */
	अगर (!पूर्णांकr->number_of_vectors) अणु
		पूर्णांकr->number_of_vectors = 1;
		पूर्णांकr->using_vectors = false;
		पूर्णांकr->vector_list[0].irq = पूर्णांकr->irq;
		netअगर_info(adapter, अगरup, adapter->netdev,
			   "using legacy interrupts\n");
	पूर्ण

	/* At this poपूर्णांक we must have at least one irq */
	lan743x_csr_ग_लिखो(adapter, INT_VEC_EN_CLR, 0xFFFFFFFF);

	/* map all पूर्णांकerrupts to vector 0 */
	lan743x_csr_ग_लिखो(adapter, INT_VEC_MAP0, 0x00000000);
	lan743x_csr_ग_लिखो(adapter, INT_VEC_MAP1, 0x00000000);
	lan743x_csr_ग_लिखो(adapter, INT_VEC_MAP2, 0x00000000);
	flags = LAN743X_VECTOR_FLAG_SOURCE_STATUS_READ |
		LAN743X_VECTOR_FLAG_SOURCE_STATUS_W2C |
		LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CHECK |
		LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CLEAR;

	अगर (पूर्णांकr->using_vectors) अणु
		flags |= LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_CLEAR |
			 LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_SET;
	पूर्ण अन्यथा अणु
		flags |= LAN743X_VECTOR_FLAG_MASTER_ENABLE_CLEAR |
			 LAN743X_VECTOR_FLAG_MASTER_ENABLE_SET |
			 LAN743X_VECTOR_FLAG_IRQ_SHARED;
	पूर्ण

	अगर (adapter->csr.flags & LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR) अणु
		flags &= ~LAN743X_VECTOR_FLAG_SOURCE_STATUS_READ;
		flags &= ~LAN743X_VECTOR_FLAG_SOURCE_STATUS_W2C;
		flags &= ~LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CLEAR;
		flags &= ~LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CHECK;
		flags |= LAN743X_VECTOR_FLAG_SOURCE_STATUS_R2C;
		flags |= LAN743X_VECTOR_FLAG_SOURCE_ENABLE_R2C;
	पूर्ण

	init_रुकोqueue_head(&पूर्णांकr->software_isr_wq);

	ret = lan743x_पूर्णांकr_रेजिस्टर_isr(adapter, 0, flags,
					INT_BIT_ALL_RX_ | INT_BIT_ALL_TX_ |
					INT_BIT_ALL_OTHER_,
					lan743x_पूर्णांकr_shared_isr, adapter);
	अगर (ret)
		जाओ clean_up;
	पूर्णांकr->flags |= INTR_FLAG_IRQ_REQUESTED(0);

	अगर (पूर्णांकr->using_vectors)
		lan743x_csr_ग_लिखो(adapter, INT_VEC_EN_SET,
				  INT_VEC_EN_(0));

	अगर (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0)) अणु
		lan743x_csr_ग_लिखो(adapter, INT_MOD_CFG0, LAN743X_INT_MOD);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_CFG1, LAN743X_INT_MOD);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_CFG2, LAN743X_INT_MOD);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_CFG3, LAN743X_INT_MOD);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_CFG4, LAN743X_INT_MOD);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_CFG5, LAN743X_INT_MOD);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_CFG6, LAN743X_INT_MOD);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_CFG7, LAN743X_INT_MOD);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_MAP0, 0x00005432);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_MAP1, 0x00000001);
		lan743x_csr_ग_लिखो(adapter, INT_MOD_MAP2, 0x00FFFFFF);
	पूर्ण

	/* enable पूर्णांकerrupts */
	lan743x_csr_ग_लिखो(adapter, INT_EN_SET, INT_BIT_MAS_);
	ret = lan743x_पूर्णांकr_test_isr(adapter);
	अगर (ret)
		जाओ clean_up;

	अगर (पूर्णांकr->number_of_vectors > 1) अणु
		पूर्णांक number_of_tx_vectors = पूर्णांकr->number_of_vectors - 1;

		अगर (number_of_tx_vectors > LAN743X_USED_TX_CHANNELS)
			number_of_tx_vectors = LAN743X_USED_TX_CHANNELS;
		flags = LAN743X_VECTOR_FLAG_SOURCE_STATUS_READ |
			LAN743X_VECTOR_FLAG_SOURCE_STATUS_W2C |
			LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CHECK |
			LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CLEAR |
			LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_CLEAR |
			LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_SET;

		अगर (adapter->csr.flags &
		   LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR) अणु
			flags = LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_SET |
				LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_SET |
				LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_CLEAR |
				LAN743X_VECTOR_FLAG_SOURCE_STATUS_AUTO_CLEAR;
		पूर्ण

		क्रम (index = 0; index < number_of_tx_vectors; index++) अणु
			u32 पूर्णांक_bit = INT_BIT_DMA_TX_(index);
			पूर्णांक vector = index + 1;

			/* map TX पूर्णांकerrupt to vector */
			पूर्णांक_vec_map1 |= INT_VEC_MAP1_TX_VEC_(index, vector);
			lan743x_csr_ग_लिखो(adapter, INT_VEC_MAP1, पूर्णांक_vec_map1);

			/* Remove TX पूर्णांकerrupt from shared mask */
			पूर्णांकr->vector_list[0].पूर्णांक_mask &= ~पूर्णांक_bit;
			ret = lan743x_पूर्णांकr_रेजिस्टर_isr(adapter, vector, flags,
							पूर्णांक_bit, lan743x_tx_isr,
							&adapter->tx[index]);
			अगर (ret)
				जाओ clean_up;
			पूर्णांकr->flags |= INTR_FLAG_IRQ_REQUESTED(vector);
			अगर (!(flags &
			    LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_SET))
				lan743x_csr_ग_लिखो(adapter, INT_VEC_EN_SET,
						  INT_VEC_EN_(vector));
		पूर्ण
	पूर्ण
	अगर ((पूर्णांकr->number_of_vectors - LAN743X_USED_TX_CHANNELS) > 1) अणु
		पूर्णांक number_of_rx_vectors = पूर्णांकr->number_of_vectors -
					   LAN743X_USED_TX_CHANNELS - 1;

		अगर (number_of_rx_vectors > LAN743X_USED_RX_CHANNELS)
			number_of_rx_vectors = LAN743X_USED_RX_CHANNELS;

		flags = LAN743X_VECTOR_FLAG_SOURCE_STATUS_READ |
			LAN743X_VECTOR_FLAG_SOURCE_STATUS_W2C |
			LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CHECK |
			LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CLEAR |
			LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_CLEAR |
			LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_SET;

		अगर (adapter->csr.flags &
		    LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR) अणु
			flags = LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_CLEAR |
				LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_SET |
				LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_SET |
				LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_CLEAR |
				LAN743X_VECTOR_FLAG_SOURCE_STATUS_AUTO_CLEAR;
		पूर्ण
		क्रम (index = 0; index < number_of_rx_vectors; index++) अणु
			पूर्णांक vector = index + 1 + LAN743X_USED_TX_CHANNELS;
			u32 पूर्णांक_bit = INT_BIT_DMA_RX_(index);

			/* map RX पूर्णांकerrupt to vector */
			पूर्णांक_vec_map0 |= INT_VEC_MAP0_RX_VEC_(index, vector);
			lan743x_csr_ग_लिखो(adapter, INT_VEC_MAP0, पूर्णांक_vec_map0);
			अगर (flags &
			    LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_CLEAR) अणु
				पूर्णांक_vec_en_स्वतः_clr |= INT_VEC_EN_(vector);
				lan743x_csr_ग_लिखो(adapter, INT_VEC_EN_AUTO_CLR,
						  पूर्णांक_vec_en_स्वतः_clr);
			पूर्ण

			/* Remove RX पूर्णांकerrupt from shared mask */
			पूर्णांकr->vector_list[0].पूर्णांक_mask &= ~पूर्णांक_bit;
			ret = lan743x_पूर्णांकr_रेजिस्टर_isr(adapter, vector, flags,
							पूर्णांक_bit, lan743x_rx_isr,
							&adapter->rx[index]);
			अगर (ret)
				जाओ clean_up;
			पूर्णांकr->flags |= INTR_FLAG_IRQ_REQUESTED(vector);

			lan743x_csr_ग_लिखो(adapter, INT_VEC_EN_SET,
					  INT_VEC_EN_(vector));
		पूर्ण
	पूर्ण
	वापस 0;

clean_up:
	lan743x_पूर्णांकr_बंद(adapter);
	वापस ret;
पूर्ण

अटल पूर्णांक lan743x_dp_ग_लिखो(काष्ठा lan743x_adapter *adapter,
			    u32 select, u32 addr, u32 length, u32 *buf)
अणु
	u32 dp_sel;
	पूर्णांक i;

	अगर (lan743x_csr_रुको_क्रम_bit(adapter, DP_SEL, DP_SEL_DPRDY_,
				     1, 40, 100, 100))
		वापस -EIO;
	dp_sel = lan743x_csr_पढ़ो(adapter, DP_SEL);
	dp_sel &= ~DP_SEL_MASK_;
	dp_sel |= select;
	lan743x_csr_ग_लिखो(adapter, DP_SEL, dp_sel);

	क्रम (i = 0; i < length; i++) अणु
		lan743x_csr_ग_लिखो(adapter, DP_ADDR, addr + i);
		lan743x_csr_ग_लिखो(adapter, DP_DATA_0, buf[i]);
		lan743x_csr_ग_लिखो(adapter, DP_CMD, DP_CMD_WRITE_);
		अगर (lan743x_csr_रुको_क्रम_bit(adapter, DP_SEL, DP_SEL_DPRDY_,
					     1, 40, 100, 100))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 lan743x_mac_mii_access(u16 id, u16 index, पूर्णांक पढ़ो)
अणु
	u32 ret;

	ret = (id << MAC_MII_ACC_PHY_ADDR_SHIFT_) &
		MAC_MII_ACC_PHY_ADDR_MASK_;
	ret |= (index << MAC_MII_ACC_MIIRINDA_SHIFT_) &
		MAC_MII_ACC_MIIRINDA_MASK_;

	अगर (पढ़ो)
		ret |= MAC_MII_ACC_MII_READ_;
	अन्यथा
		ret |= MAC_MII_ACC_MII_WRITE_;
	ret |= MAC_MII_ACC_MII_BUSY_;

	वापस ret;
पूर्ण

अटल पूर्णांक lan743x_mac_mii_रुको_till_not_busy(काष्ठा lan743x_adapter *adapter)
अणु
	u32 data;

	वापस पढ़ोx_poll_समयout(LAN743X_CSR_READ_OP, MAC_MII_ACC, data,
				  !(data & MAC_MII_ACC_MII_BUSY_), 0, 1000000);
पूर्ण

अटल पूर्णांक lan743x_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक index)
अणु
	काष्ठा lan743x_adapter *adapter = bus->priv;
	u32 val, mii_access;
	पूर्णांक ret;

	/* comfirm MII not busy */
	ret = lan743x_mac_mii_रुको_till_not_busy(adapter);
	अगर (ret < 0)
		वापस ret;

	/* set the address, index & direction (पढ़ो from PHY) */
	mii_access = lan743x_mac_mii_access(phy_id, index, MAC_MII_READ);
	lan743x_csr_ग_लिखो(adapter, MAC_MII_ACC, mii_access);
	ret = lan743x_mac_mii_रुको_till_not_busy(adapter);
	अगर (ret < 0)
		वापस ret;

	val = lan743x_csr_पढ़ो(adapter, MAC_MII_DATA);
	वापस (पूर्णांक)(val & 0xFFFF);
पूर्ण

अटल पूर्णांक lan743x_mdiobus_ग_लिखो(काष्ठा mii_bus *bus,
				 पूर्णांक phy_id, पूर्णांक index, u16 regval)
अणु
	काष्ठा lan743x_adapter *adapter = bus->priv;
	u32 val, mii_access;
	पूर्णांक ret;

	/* confirm MII not busy */
	ret = lan743x_mac_mii_रुको_till_not_busy(adapter);
	अगर (ret < 0)
		वापस ret;
	val = (u32)regval;
	lan743x_csr_ग_लिखो(adapter, MAC_MII_DATA, val);

	/* set the address, index & direction (ग_लिखो to PHY) */
	mii_access = lan743x_mac_mii_access(phy_id, index, MAC_MII_WRITE);
	lan743x_csr_ग_लिखो(adapter, MAC_MII_ACC, mii_access);
	ret = lan743x_mac_mii_रुको_till_not_busy(adapter);
	वापस ret;
पूर्ण

अटल व्योम lan743x_mac_set_address(काष्ठा lan743x_adapter *adapter,
				    u8 *addr)
अणु
	u32 addr_lo, addr_hi;

	addr_lo = addr[0] |
		addr[1] << 8 |
		addr[2] << 16 |
		addr[3] << 24;
	addr_hi = addr[4] |
		addr[5] << 8;
	lan743x_csr_ग_लिखो(adapter, MAC_RX_ADDRL, addr_lo);
	lan743x_csr_ग_लिखो(adapter, MAC_RX_ADDRH, addr_hi);

	ether_addr_copy(adapter->mac_address, addr);
	netअगर_info(adapter, drv, adapter->netdev,
		   "MAC address set to %pM\n", addr);
पूर्ण

अटल पूर्णांक lan743x_mac_init(काष्ठा lan743x_adapter *adapter)
अणु
	bool mac_address_valid = true;
	काष्ठा net_device *netdev;
	u32 mac_addr_hi = 0;
	u32 mac_addr_lo = 0;
	u32 data;

	netdev = adapter->netdev;

	/* disable स्वतः duplex, and speed detection. Phylib करोes that */
	data = lan743x_csr_पढ़ो(adapter, MAC_CR);
	data &= ~(MAC_CR_ADD_ | MAC_CR_ASD_);
	data |= MAC_CR_CNTR_RST_;
	lan743x_csr_ग_लिखो(adapter, MAC_CR, data);

	अगर (!is_valid_ether_addr(adapter->mac_address)) अणु
		mac_addr_hi = lan743x_csr_पढ़ो(adapter, MAC_RX_ADDRH);
		mac_addr_lo = lan743x_csr_पढ़ो(adapter, MAC_RX_ADDRL);
		adapter->mac_address[0] = mac_addr_lo & 0xFF;
		adapter->mac_address[1] = (mac_addr_lo >> 8) & 0xFF;
		adapter->mac_address[2] = (mac_addr_lo >> 16) & 0xFF;
		adapter->mac_address[3] = (mac_addr_lo >> 24) & 0xFF;
		adapter->mac_address[4] = mac_addr_hi & 0xFF;
		adapter->mac_address[5] = (mac_addr_hi >> 8) & 0xFF;

		अगर (((mac_addr_hi & 0x0000FFFF) == 0x0000FFFF) &&
		    mac_addr_lo == 0xFFFFFFFF) अणु
			mac_address_valid = false;
		पूर्ण अन्यथा अगर (!is_valid_ether_addr(adapter->mac_address)) अणु
			mac_address_valid = false;
		पूर्ण

		अगर (!mac_address_valid)
			eth_अक्रमom_addr(adapter->mac_address);
	पूर्ण
	lan743x_mac_set_address(adapter, adapter->mac_address);
	ether_addr_copy(netdev->dev_addr, adapter->mac_address);

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_mac_खोलो(काष्ठा lan743x_adapter *adapter)
अणु
	u32 temp;

	temp = lan743x_csr_पढ़ो(adapter, MAC_RX);
	lan743x_csr_ग_लिखो(adapter, MAC_RX, temp | MAC_RX_RXEN_);
	temp = lan743x_csr_पढ़ो(adapter, MAC_TX);
	lan743x_csr_ग_लिखो(adapter, MAC_TX, temp | MAC_TX_TXEN_);
	वापस 0;
पूर्ण

अटल व्योम lan743x_mac_बंद(काष्ठा lan743x_adapter *adapter)
अणु
	u32 temp;

	temp = lan743x_csr_पढ़ो(adapter, MAC_TX);
	temp &= ~MAC_TX_TXEN_;
	lan743x_csr_ग_लिखो(adapter, MAC_TX, temp);
	lan743x_csr_रुको_क्रम_bit(adapter, MAC_TX, MAC_TX_TXD_,
				 1, 1000, 20000, 100);

	temp = lan743x_csr_पढ़ो(adapter, MAC_RX);
	temp &= ~MAC_RX_RXEN_;
	lan743x_csr_ग_लिखो(adapter, MAC_RX, temp);
	lan743x_csr_रुको_क्रम_bit(adapter, MAC_RX, MAC_RX_RXD_,
				 1, 1000, 20000, 100);
पूर्ण

अटल व्योम lan743x_mac_flow_ctrl_set_enables(काष्ठा lan743x_adapter *adapter,
					      bool tx_enable, bool rx_enable)
अणु
	u32 flow_setting = 0;

	/* set maximum छोड़ो समय because when fअगरo space मुक्तs
	 * up a zero value छोड़ो frame will be sent to release the छोड़ो
	 */
	flow_setting = MAC_FLOW_CR_FCPT_MASK_;
	अगर (tx_enable)
		flow_setting |= MAC_FLOW_CR_TX_FCEN_;
	अगर (rx_enable)
		flow_setting |= MAC_FLOW_CR_RX_FCEN_;
	lan743x_csr_ग_लिखो(adapter, MAC_FLOW, flow_setting);
पूर्ण

अटल पूर्णांक lan743x_mac_set_mtu(काष्ठा lan743x_adapter *adapter, पूर्णांक new_mtu)
अणु
	पूर्णांक enabled = 0;
	u32 mac_rx = 0;

	mac_rx = lan743x_csr_पढ़ो(adapter, MAC_RX);
	अगर (mac_rx & MAC_RX_RXEN_) अणु
		enabled = 1;
		अगर (mac_rx & MAC_RX_RXD_) अणु
			lan743x_csr_ग_लिखो(adapter, MAC_RX, mac_rx);
			mac_rx &= ~MAC_RX_RXD_;
		पूर्ण
		mac_rx &= ~MAC_RX_RXEN_;
		lan743x_csr_ग_लिखो(adapter, MAC_RX, mac_rx);
		lan743x_csr_रुको_क्रम_bit(adapter, MAC_RX, MAC_RX_RXD_,
					 1, 1000, 20000, 100);
		lan743x_csr_ग_लिखो(adapter, MAC_RX, mac_rx | MAC_RX_RXD_);
	पूर्ण

	mac_rx &= ~(MAC_RX_MAX_SIZE_MASK_);
	mac_rx |= (((new_mtu + ETH_HLEN + ETH_FCS_LEN)
		  << MAC_RX_MAX_SIZE_SHIFT_) & MAC_RX_MAX_SIZE_MASK_);
	lan743x_csr_ग_लिखो(adapter, MAC_RX, mac_rx);

	अगर (enabled) अणु
		mac_rx |= MAC_RX_RXEN_;
		lan743x_csr_ग_लिखो(adapter, MAC_RX, mac_rx);
	पूर्ण
	वापस 0;
पूर्ण

/* PHY */
अटल पूर्णांक lan743x_phy_reset(काष्ठा lan743x_adapter *adapter)
अणु
	u32 data;

	/* Only called with in probe, and beक्रमe mdiobus_रेजिस्टर */

	data = lan743x_csr_पढ़ो(adapter, PMT_CTL);
	data |= PMT_CTL_ETH_PHY_RST_;
	lan743x_csr_ग_लिखो(adapter, PMT_CTL, data);

	वापस पढ़ोx_poll_समयout(LAN743X_CSR_READ_OP, PMT_CTL, data,
				  (!(data & PMT_CTL_ETH_PHY_RST_) &&
				  (data & PMT_CTL_READY_)),
				  50000, 1000000);
पूर्ण

अटल व्योम lan743x_phy_update_flowcontrol(काष्ठा lan743x_adapter *adapter,
					   u8 duplex, u16 local_adv,
					   u16 remote_adv)
अणु
	काष्ठा lan743x_phy *phy = &adapter->phy;
	u8 cap;

	अगर (phy->fc_स्वतःneg)
		cap = mii_resolve_flowctrl_fdx(local_adv, remote_adv);
	अन्यथा
		cap = phy->fc_request_control;

	lan743x_mac_flow_ctrl_set_enables(adapter,
					  cap & FLOW_CTRL_TX,
					  cap & FLOW_CTRL_RX);
पूर्ण

अटल पूर्णांक lan743x_phy_init(काष्ठा lan743x_adapter *adapter)
अणु
	वापस lan743x_phy_reset(adapter);
पूर्ण

अटल व्योम lan743x_phy_link_status_change(काष्ठा net_device *netdev)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	काष्ठा phy_device *phydev = netdev->phydev;
	u32 data;

	phy_prपूर्णांक_status(phydev);
	अगर (phydev->state == PHY_RUNNING) अणु
		काष्ठा ethtool_link_ksettings ksettings;
		पूर्णांक remote_advertisement = 0;
		पूर्णांक local_advertisement = 0;

		data = lan743x_csr_पढ़ो(adapter, MAC_CR);

		/* set पूर्णांकerface mode */
		अगर (phy_पूर्णांकerface_is_rgmii(phydev))
			/* RGMII */
			data &= ~MAC_CR_MII_EN_;
		अन्यथा
			/* GMII */
			data |= MAC_CR_MII_EN_;

		/* set duplex mode */
		अगर (phydev->duplex)
			data |= MAC_CR_DPX_;
		अन्यथा
			data &= ~MAC_CR_DPX_;

		/* set bus speed */
		चयन (phydev->speed) अणु
		हाल SPEED_10:
			data &= ~MAC_CR_CFG_H_;
			data &= ~MAC_CR_CFG_L_;
		अवरोध;
		हाल SPEED_100:
			data &= ~MAC_CR_CFG_H_;
			data |= MAC_CR_CFG_L_;
		अवरोध;
		हाल SPEED_1000:
			data |= MAC_CR_CFG_H_;
			data &= ~MAC_CR_CFG_L_;
		अवरोध;
		पूर्ण
		lan743x_csr_ग_लिखो(adapter, MAC_CR, data);

		स_रखो(&ksettings, 0, माप(ksettings));
		phy_ethtool_get_link_ksettings(netdev, &ksettings);
		local_advertisement =
			linkmode_adv_to_mii_adv_t(phydev->advertising);
		remote_advertisement =
			linkmode_adv_to_mii_adv_t(phydev->lp_advertising);

		lan743x_phy_update_flowcontrol(adapter,
					       ksettings.base.duplex,
					       local_advertisement,
					       remote_advertisement);
		lan743x_ptp_update_latency(adapter, ksettings.base.speed);
	पूर्ण
पूर्ण

अटल व्योम lan743x_phy_बंद(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	phy_stop(netdev->phydev);
	phy_disconnect(netdev->phydev);
	netdev->phydev = शून्य;
पूर्ण

अटल पूर्णांक lan743x_phy_खोलो(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा lan743x_phy *phy = &adapter->phy;
	काष्ठा phy_device *phydev;
	पूर्णांक ret = -EIO;

	/* try devicetree phy, or fixed link */
	phydev = of_phy_get_and_connect(netdev, adapter->pdev->dev.of_node,
					lan743x_phy_link_status_change);

	अगर (!phydev) अणु
		/* try पूर्णांकernal phy */
		phydev = phy_find_first(adapter->mdiobus);
		अगर (!phydev)
			जाओ वापस_error;

		ret = phy_connect_direct(netdev, phydev,
					 lan743x_phy_link_status_change,
					 PHY_INTERFACE_MODE_GMII);
		अगर (ret)
			जाओ वापस_error;
	पूर्ण

	/* MAC करोesn't support 1000T Half */
	phy_हटाओ_link_mode(phydev, ETHTOOL_LINK_MODE_1000baseT_Half_BIT);

	/* support both flow controls */
	phy_support_asym_छोड़ो(phydev);
	phy->fc_request_control = (FLOW_CTRL_RX | FLOW_CTRL_TX);
	phy->fc_स्वतःneg = phydev->स्वतःneg;

	phy_start(phydev);
	phy_start_aneg(phydev);
	phy_attached_info(phydev);
	वापस 0;

वापस_error:
	वापस ret;
पूर्ण

अटल व्योम lan743x_rfe_खोलो(काष्ठा lan743x_adapter *adapter)
अणु
	lan743x_csr_ग_लिखो(adapter, RFE_RSS_CFG,
		RFE_RSS_CFG_UDP_IPV6_EX_ |
		RFE_RSS_CFG_TCP_IPV6_EX_ |
		RFE_RSS_CFG_IPV6_EX_ |
		RFE_RSS_CFG_UDP_IPV6_ |
		RFE_RSS_CFG_TCP_IPV6_ |
		RFE_RSS_CFG_IPV6_ |
		RFE_RSS_CFG_UDP_IPV4_ |
		RFE_RSS_CFG_TCP_IPV4_ |
		RFE_RSS_CFG_IPV4_ |
		RFE_RSS_CFG_VALID_HASH_BITS_ |
		RFE_RSS_CFG_RSS_QUEUE_ENABLE_ |
		RFE_RSS_CFG_RSS_HASH_STORE_ |
		RFE_RSS_CFG_RSS_ENABLE_);
पूर्ण

अटल व्योम lan743x_rfe_update_mac_address(काष्ठा lan743x_adapter *adapter)
अणु
	u8 *mac_addr;
	u32 mac_addr_hi = 0;
	u32 mac_addr_lo = 0;

	/* Add mac address to perfect Filter */
	mac_addr = adapter->mac_address;
	mac_addr_lo = ((((u32)(mac_addr[0])) << 0) |
		      (((u32)(mac_addr[1])) << 8) |
		      (((u32)(mac_addr[2])) << 16) |
		      (((u32)(mac_addr[3])) << 24));
	mac_addr_hi = ((((u32)(mac_addr[4])) << 0) |
		      (((u32)(mac_addr[5])) << 8));

	lan743x_csr_ग_लिखो(adapter, RFE_ADDR_FILT_LO(0), mac_addr_lo);
	lan743x_csr_ग_लिखो(adapter, RFE_ADDR_FILT_HI(0),
			  mac_addr_hi | RFE_ADDR_FILT_HI_VALID_);
पूर्ण

अटल व्योम lan743x_rfe_set_multicast(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u32 hash_table[DP_SEL_VHF_HASH_LEN];
	u32 rfctl;
	u32 data;

	rfctl = lan743x_csr_पढ़ो(adapter, RFE_CTL);
	rfctl &= ~(RFE_CTL_AU_ | RFE_CTL_AM_ |
		 RFE_CTL_DA_PERFECT_ | RFE_CTL_MCAST_HASH_);
	rfctl |= RFE_CTL_AB_;
	अगर (netdev->flags & IFF_PROMISC) अणु
		rfctl |= RFE_CTL_AM_ | RFE_CTL_AU_;
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_ALLMULTI)
			rfctl |= RFE_CTL_AM_;
	पूर्ण

	स_रखो(hash_table, 0, DP_SEL_VHF_HASH_LEN * माप(u32));
	अगर (netdev_mc_count(netdev)) अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i;

		rfctl |= RFE_CTL_DA_PERFECT_;
		i = 1;
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			/* set first 32 पूर्णांकo Perfect Filter */
			अगर (i < 33) अणु
				lan743x_csr_ग_लिखो(adapter,
						  RFE_ADDR_FILT_HI(i), 0);
				data = ha->addr[3];
				data = ha->addr[2] | (data << 8);
				data = ha->addr[1] | (data << 8);
				data = ha->addr[0] | (data << 8);
				lan743x_csr_ग_लिखो(adapter,
						  RFE_ADDR_FILT_LO(i), data);
				data = ha->addr[5];
				data = ha->addr[4] | (data << 8);
				data |= RFE_ADDR_FILT_HI_VALID_;
				lan743x_csr_ग_लिखो(adapter,
						  RFE_ADDR_FILT_HI(i), data);
			पूर्ण अन्यथा अणु
				u32 bitnum = (ether_crc(ETH_ALEN, ha->addr) >>
					     23) & 0x1FF;
				hash_table[bitnum / 32] |= (1 << (bitnum % 32));
				rfctl |= RFE_CTL_MCAST_HASH_;
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	lan743x_dp_ग_लिखो(adapter, DP_SEL_RFE_RAM,
			 DP_SEL_VHF_VLAN_LEN,
			 DP_SEL_VHF_HASH_LEN, hash_table);
	lan743x_csr_ग_लिखो(adapter, RFE_CTL, rfctl);
पूर्ण

अटल पूर्णांक lan743x_dmac_init(काष्ठा lan743x_adapter *adapter)
अणु
	u32 data = 0;

	lan743x_csr_ग_लिखो(adapter, DMAC_CMD, DMAC_CMD_SWR_);
	lan743x_csr_रुको_क्रम_bit(adapter, DMAC_CMD, DMAC_CMD_SWR_,
				 0, 1000, 20000, 100);
	चयन (DEFAULT_DMA_DESCRIPTOR_SPACING) अणु
	हाल DMA_DESCRIPTOR_SPACING_16:
		data = DMAC_CFG_MAX_DSPACE_16_;
		अवरोध;
	हाल DMA_DESCRIPTOR_SPACING_32:
		data = DMAC_CFG_MAX_DSPACE_32_;
		अवरोध;
	हाल DMA_DESCRIPTOR_SPACING_64:
		data = DMAC_CFG_MAX_DSPACE_64_;
		अवरोध;
	हाल DMA_DESCRIPTOR_SPACING_128:
		data = DMAC_CFG_MAX_DSPACE_128_;
		अवरोध;
	शेष:
		वापस -EPERM;
	पूर्ण
	अगर (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0))
		data |= DMAC_CFG_COAL_EN_;
	data |= DMAC_CFG_CH_ARB_SEL_RX_HIGH_;
	data |= DMAC_CFG_MAX_READ_REQ_SET_(6);
	lan743x_csr_ग_लिखो(adapter, DMAC_CFG, data);
	data = DMAC_COAL_CFG_TIMER_LIMIT_SET_(1);
	data |= DMAC_COAL_CFG_TIMER_TX_START_;
	data |= DMAC_COAL_CFG_FLUSH_INTS_;
	data |= DMAC_COAL_CFG_INT_EXIT_COAL_;
	data |= DMAC_COAL_CFG_CSR_EXIT_COAL_;
	data |= DMAC_COAL_CFG_TX_THRES_SET_(0x0A);
	data |= DMAC_COAL_CFG_RX_THRES_SET_(0x0C);
	lan743x_csr_ग_लिखो(adapter, DMAC_COAL_CFG, data);
	data = DMAC_OBFF_TX_THRES_SET_(0x08);
	data |= DMAC_OBFF_RX_THRES_SET_(0x0A);
	lan743x_csr_ग_लिखो(adapter, DMAC_OBFF_CFG, data);
	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_dmac_tx_get_state(काष्ठा lan743x_adapter *adapter,
				     पूर्णांक tx_channel)
अणु
	u32 dmac_cmd = 0;

	dmac_cmd = lan743x_csr_पढ़ो(adapter, DMAC_CMD);
	वापस DMAC_CHANNEL_STATE_SET((dmac_cmd &
				      DMAC_CMD_START_T_(tx_channel)),
				      (dmac_cmd &
				      DMAC_CMD_STOP_T_(tx_channel)));
पूर्ण

अटल पूर्णांक lan743x_dmac_tx_रुको_till_stopped(काष्ठा lan743x_adapter *adapter,
					     पूर्णांक tx_channel)
अणु
	पूर्णांक समयout = 100;
	पूर्णांक result = 0;

	जबतक (समयout &&
	       ((result = lan743x_dmac_tx_get_state(adapter, tx_channel)) ==
	       DMAC_CHANNEL_STATE_STOP_PENDING)) अणु
		usleep_range(1000, 20000);
		समयout--;
	पूर्ण
	अगर (result == DMAC_CHANNEL_STATE_STOP_PENDING)
		result = -ENODEV;
	वापस result;
पूर्ण

अटल पूर्णांक lan743x_dmac_rx_get_state(काष्ठा lan743x_adapter *adapter,
				     पूर्णांक rx_channel)
अणु
	u32 dmac_cmd = 0;

	dmac_cmd = lan743x_csr_पढ़ो(adapter, DMAC_CMD);
	वापस DMAC_CHANNEL_STATE_SET((dmac_cmd &
				      DMAC_CMD_START_R_(rx_channel)),
				      (dmac_cmd &
				      DMAC_CMD_STOP_R_(rx_channel)));
पूर्ण

अटल पूर्णांक lan743x_dmac_rx_रुको_till_stopped(काष्ठा lan743x_adapter *adapter,
					     पूर्णांक rx_channel)
अणु
	पूर्णांक समयout = 100;
	पूर्णांक result = 0;

	जबतक (समयout &&
	       ((result = lan743x_dmac_rx_get_state(adapter, rx_channel)) ==
	       DMAC_CHANNEL_STATE_STOP_PENDING)) अणु
		usleep_range(1000, 20000);
		समयout--;
	पूर्ण
	अगर (result == DMAC_CHANNEL_STATE_STOP_PENDING)
		result = -ENODEV;
	वापस result;
पूर्ण

अटल व्योम lan743x_tx_release_desc(काष्ठा lan743x_tx *tx,
				    पूर्णांक descriptor_index, bool cleanup)
अणु
	काष्ठा lan743x_tx_buffer_info *buffer_info = शून्य;
	काष्ठा lan743x_tx_descriptor *descriptor = शून्य;
	u32 descriptor_type = 0;
	bool ignore_sync;

	descriptor = &tx->ring_cpu_ptr[descriptor_index];
	buffer_info = &tx->buffer_info[descriptor_index];
	अगर (!(buffer_info->flags & TX_BUFFER_INFO_FLAG_ACTIVE))
		जाओ करोne;

	descriptor_type = le32_to_cpu(descriptor->data0) &
			  TX_DESC_DATA0_DTYPE_MASK_;
	अगर (descriptor_type == TX_DESC_DATA0_DTYPE_DATA_)
		जाओ clean_up_data_descriptor;
	अन्यथा
		जाओ clear_active;

clean_up_data_descriptor:
	अगर (buffer_info->dma_ptr) अणु
		अगर (buffer_info->flags &
		    TX_BUFFER_INFO_FLAG_SKB_FRAGMENT) अणु
			dma_unmap_page(&tx->adapter->pdev->dev,
				       buffer_info->dma_ptr,
				       buffer_info->buffer_length,
				       DMA_TO_DEVICE);
		पूर्ण अन्यथा अणु
			dma_unmap_single(&tx->adapter->pdev->dev,
					 buffer_info->dma_ptr,
					 buffer_info->buffer_length,
					 DMA_TO_DEVICE);
		पूर्ण
		buffer_info->dma_ptr = 0;
		buffer_info->buffer_length = 0;
	पूर्ण
	अगर (!buffer_info->skb)
		जाओ clear_active;

	अगर (!(buffer_info->flags & TX_BUFFER_INFO_FLAG_TIMESTAMP_REQUESTED)) अणु
		dev_kमुक्त_skb_any(buffer_info->skb);
		जाओ clear_skb;
	पूर्ण

	अगर (cleanup) अणु
		lan743x_ptp_unrequest_tx_बारtamp(tx->adapter);
		dev_kमुक्त_skb_any(buffer_info->skb);
	पूर्ण अन्यथा अणु
		ignore_sync = (buffer_info->flags &
			       TX_BUFFER_INFO_FLAG_IGNORE_SYNC) != 0;
		lan743x_ptp_tx_बारtamp_skb(tx->adapter,
					     buffer_info->skb, ignore_sync);
	पूर्ण

clear_skb:
	buffer_info->skb = शून्य;

clear_active:
	buffer_info->flags &= ~TX_BUFFER_INFO_FLAG_ACTIVE;

करोne:
	स_रखो(buffer_info, 0, माप(*buffer_info));
	स_रखो(descriptor, 0, माप(*descriptor));
पूर्ण

अटल पूर्णांक lan743x_tx_next_index(काष्ठा lan743x_tx *tx, पूर्णांक index)
अणु
	वापस ((++index) % tx->ring_size);
पूर्ण

अटल व्योम lan743x_tx_release_completed_descriptors(काष्ठा lan743x_tx *tx)
अणु
	जबतक (le32_to_cpu(*tx->head_cpu_ptr) != (tx->last_head)) अणु
		lan743x_tx_release_desc(tx, tx->last_head, false);
		tx->last_head = lan743x_tx_next_index(tx, tx->last_head);
	पूर्ण
पूर्ण

अटल व्योम lan743x_tx_release_all_descriptors(काष्ठा lan743x_tx *tx)
अणु
	u32 original_head = 0;

	original_head = tx->last_head;
	करो अणु
		lan743x_tx_release_desc(tx, tx->last_head, true);
		tx->last_head = lan743x_tx_next_index(tx, tx->last_head);
	पूर्ण जबतक (tx->last_head != original_head);
	स_रखो(tx->ring_cpu_ptr, 0,
	       माप(*tx->ring_cpu_ptr) * (tx->ring_size));
	स_रखो(tx->buffer_info, 0,
	       माप(*tx->buffer_info) * (tx->ring_size));
पूर्ण

अटल पूर्णांक lan743x_tx_get_desc_cnt(काष्ठा lan743x_tx *tx,
				   काष्ठा sk_buff *skb)
अणु
	पूर्णांक result = 1; /* 1 क्रम the मुख्य skb buffer */
	पूर्णांक nr_frags = 0;

	अगर (skb_is_gso(skb))
		result++; /* requires an extension descriptor */
	nr_frags = skb_shinfo(skb)->nr_frags;
	result += nr_frags; /* 1 क्रम each fragment buffer */
	वापस result;
पूर्ण

अटल पूर्णांक lan743x_tx_get_avail_desc(काष्ठा lan743x_tx *tx)
अणु
	पूर्णांक last_head = tx->last_head;
	पूर्णांक last_tail = tx->last_tail;

	अगर (last_tail >= last_head)
		वापस tx->ring_size - last_tail + last_head - 1;
	अन्यथा
		वापस last_head - last_tail - 1;
पूर्ण

व्योम lan743x_tx_set_बारtamping_mode(काष्ठा lan743x_tx *tx,
				      bool enable_बारtamping,
				      bool enable_onestep_sync)
अणु
	अगर (enable_बारtamping)
		tx->ts_flags |= TX_TS_FLAG_TIMESTAMPING_ENABLED;
	अन्यथा
		tx->ts_flags &= ~TX_TS_FLAG_TIMESTAMPING_ENABLED;
	अगर (enable_onestep_sync)
		tx->ts_flags |= TX_TS_FLAG_ONE_STEP_SYNC;
	अन्यथा
		tx->ts_flags &= ~TX_TS_FLAG_ONE_STEP_SYNC;
पूर्ण

अटल पूर्णांक lan743x_tx_frame_start(काष्ठा lan743x_tx *tx,
				  अचिन्हित अक्षर *first_buffer,
				  अचिन्हित पूर्णांक first_buffer_length,
				  अचिन्हित पूर्णांक frame_length,
				  bool समय_stamp,
				  bool check_sum)
अणु
	/* called only from within lan743x_tx_xmit_frame.
	 * assuming tx->ring_lock has alपढ़ोy been acquired.
	 */
	काष्ठा lan743x_tx_descriptor *tx_descriptor = शून्य;
	काष्ठा lan743x_tx_buffer_info *buffer_info = शून्य;
	काष्ठा lan743x_adapter *adapter = tx->adapter;
	काष्ठा device *dev = &adapter->pdev->dev;
	dma_addr_t dma_ptr;

	tx->frame_flags |= TX_FRAME_FLAG_IN_PROGRESS;
	tx->frame_first = tx->last_tail;
	tx->frame_tail = tx->frame_first;

	tx_descriptor = &tx->ring_cpu_ptr[tx->frame_tail];
	buffer_info = &tx->buffer_info[tx->frame_tail];
	dma_ptr = dma_map_single(dev, first_buffer, first_buffer_length,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma_ptr))
		वापस -ENOMEM;

	tx_descriptor->data1 = cpu_to_le32(DMA_ADDR_LOW32(dma_ptr));
	tx_descriptor->data2 = cpu_to_le32(DMA_ADDR_HIGH32(dma_ptr));
	tx_descriptor->data3 = cpu_to_le32((frame_length << 16) &
		TX_DESC_DATA3_FRAME_LENGTH_MSS_MASK_);

	buffer_info->skb = शून्य;
	buffer_info->dma_ptr = dma_ptr;
	buffer_info->buffer_length = first_buffer_length;
	buffer_info->flags |= TX_BUFFER_INFO_FLAG_ACTIVE;

	tx->frame_data0 = (first_buffer_length &
		TX_DESC_DATA0_BUF_LENGTH_MASK_) |
		TX_DESC_DATA0_DTYPE_DATA_ |
		TX_DESC_DATA0_FS_ |
		TX_DESC_DATA0_FCS_;
	अगर (समय_stamp)
		tx->frame_data0 |= TX_DESC_DATA0_TSE_;

	अगर (check_sum)
		tx->frame_data0 |= TX_DESC_DATA0_ICE_ |
				   TX_DESC_DATA0_IPE_ |
				   TX_DESC_DATA0_TPE_;

	/* data0 will be programmed in one of other frame assembler functions */
	वापस 0;
पूर्ण

अटल व्योम lan743x_tx_frame_add_lso(काष्ठा lan743x_tx *tx,
				     अचिन्हित पूर्णांक frame_length,
				     पूर्णांक nr_frags)
अणु
	/* called only from within lan743x_tx_xmit_frame.
	 * assuming tx->ring_lock has alपढ़ोy been acquired.
	 */
	काष्ठा lan743x_tx_descriptor *tx_descriptor = शून्य;
	काष्ठा lan743x_tx_buffer_info *buffer_info = शून्य;

	/* wrap up previous descriptor */
	tx->frame_data0 |= TX_DESC_DATA0_EXT_;
	अगर (nr_frags <= 0) अणु
		tx->frame_data0 |= TX_DESC_DATA0_LS_;
		tx->frame_data0 |= TX_DESC_DATA0_IOC_;
	पूर्ण
	tx_descriptor = &tx->ring_cpu_ptr[tx->frame_tail];
	tx_descriptor->data0 = cpu_to_le32(tx->frame_data0);

	/* move to next descriptor */
	tx->frame_tail = lan743x_tx_next_index(tx, tx->frame_tail);
	tx_descriptor = &tx->ring_cpu_ptr[tx->frame_tail];
	buffer_info = &tx->buffer_info[tx->frame_tail];

	/* add extension descriptor */
	tx_descriptor->data1 = 0;
	tx_descriptor->data2 = 0;
	tx_descriptor->data3 = 0;

	buffer_info->skb = शून्य;
	buffer_info->dma_ptr = 0;
	buffer_info->buffer_length = 0;
	buffer_info->flags |= TX_BUFFER_INFO_FLAG_ACTIVE;

	tx->frame_data0 = (frame_length & TX_DESC_DATA0_EXT_PAY_LENGTH_MASK_) |
			  TX_DESC_DATA0_DTYPE_EXT_ |
			  TX_DESC_DATA0_EXT_LSO_;

	/* data0 will be programmed in one of other frame assembler functions */
पूर्ण

अटल पूर्णांक lan743x_tx_frame_add_fragment(काष्ठा lan743x_tx *tx,
					 स्थिर skb_frag_t *fragment,
					 अचिन्हित पूर्णांक frame_length)
अणु
	/* called only from within lan743x_tx_xmit_frame
	 * assuming tx->ring_lock has alपढ़ोy been acquired
	 */
	काष्ठा lan743x_tx_descriptor *tx_descriptor = शून्य;
	काष्ठा lan743x_tx_buffer_info *buffer_info = शून्य;
	काष्ठा lan743x_adapter *adapter = tx->adapter;
	काष्ठा device *dev = &adapter->pdev->dev;
	अचिन्हित पूर्णांक fragment_length = 0;
	dma_addr_t dma_ptr;

	fragment_length = skb_frag_size(fragment);
	अगर (!fragment_length)
		वापस 0;

	/* wrap up previous descriptor */
	tx_descriptor = &tx->ring_cpu_ptr[tx->frame_tail];
	tx_descriptor->data0 = cpu_to_le32(tx->frame_data0);

	/* move to next descriptor */
	tx->frame_tail = lan743x_tx_next_index(tx, tx->frame_tail);
	tx_descriptor = &tx->ring_cpu_ptr[tx->frame_tail];
	buffer_info = &tx->buffer_info[tx->frame_tail];
	dma_ptr = skb_frag_dma_map(dev, fragment,
				   0, fragment_length,
				   DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma_ptr)) अणु
		पूर्णांक desc_index;

		/* cleanup all previously setup descriptors */
		desc_index = tx->frame_first;
		जबतक (desc_index != tx->frame_tail) अणु
			lan743x_tx_release_desc(tx, desc_index, true);
			desc_index = lan743x_tx_next_index(tx, desc_index);
		पूर्ण
		dma_wmb();
		tx->frame_flags &= ~TX_FRAME_FLAG_IN_PROGRESS;
		tx->frame_first = 0;
		tx->frame_data0 = 0;
		tx->frame_tail = 0;
		वापस -ENOMEM;
	पूर्ण

	tx_descriptor->data1 = cpu_to_le32(DMA_ADDR_LOW32(dma_ptr));
	tx_descriptor->data2 = cpu_to_le32(DMA_ADDR_HIGH32(dma_ptr));
	tx_descriptor->data3 = cpu_to_le32((frame_length << 16) &
			       TX_DESC_DATA3_FRAME_LENGTH_MSS_MASK_);

	buffer_info->skb = शून्य;
	buffer_info->dma_ptr = dma_ptr;
	buffer_info->buffer_length = fragment_length;
	buffer_info->flags |= TX_BUFFER_INFO_FLAG_ACTIVE;
	buffer_info->flags |= TX_BUFFER_INFO_FLAG_SKB_FRAGMENT;

	tx->frame_data0 = (fragment_length & TX_DESC_DATA0_BUF_LENGTH_MASK_) |
			  TX_DESC_DATA0_DTYPE_DATA_ |
			  TX_DESC_DATA0_FCS_;

	/* data0 will be programmed in one of other frame assembler functions */
	वापस 0;
पूर्ण

अटल व्योम lan743x_tx_frame_end(काष्ठा lan743x_tx *tx,
				 काष्ठा sk_buff *skb,
				 bool समय_stamp,
				 bool ignore_sync)
अणु
	/* called only from within lan743x_tx_xmit_frame
	 * assuming tx->ring_lock has alपढ़ोy been acquired
	 */
	काष्ठा lan743x_tx_descriptor *tx_descriptor = शून्य;
	काष्ठा lan743x_tx_buffer_info *buffer_info = शून्य;
	काष्ठा lan743x_adapter *adapter = tx->adapter;
	u32 tx_tail_flags = 0;

	/* wrap up previous descriptor */
	अगर ((tx->frame_data0 & TX_DESC_DATA0_DTYPE_MASK_) ==
	    TX_DESC_DATA0_DTYPE_DATA_) अणु
		tx->frame_data0 |= TX_DESC_DATA0_LS_;
		tx->frame_data0 |= TX_DESC_DATA0_IOC_;
	पूर्ण

	tx_descriptor = &tx->ring_cpu_ptr[tx->frame_tail];
	buffer_info = &tx->buffer_info[tx->frame_tail];
	buffer_info->skb = skb;
	अगर (समय_stamp)
		buffer_info->flags |= TX_BUFFER_INFO_FLAG_TIMESTAMP_REQUESTED;
	अगर (ignore_sync)
		buffer_info->flags |= TX_BUFFER_INFO_FLAG_IGNORE_SYNC;

	tx_descriptor->data0 = cpu_to_le32(tx->frame_data0);
	tx->frame_tail = lan743x_tx_next_index(tx, tx->frame_tail);
	tx->last_tail = tx->frame_tail;

	dma_wmb();

	अगर (tx->vector_flags & LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_SET)
		tx_tail_flags |= TX_TAIL_SET_TOP_INT_VEC_EN_;
	अगर (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_SET)
		tx_tail_flags |= TX_TAIL_SET_DMAC_INT_EN_ |
		TX_TAIL_SET_TOP_INT_EN_;

	lan743x_csr_ग_लिखो(adapter, TX_TAIL(tx->channel_number),
			  tx_tail_flags | tx->frame_tail);
	tx->frame_flags &= ~TX_FRAME_FLAG_IN_PROGRESS;
पूर्ण

अटल netdev_tx_t lan743x_tx_xmit_frame(काष्ठा lan743x_tx *tx,
					 काष्ठा sk_buff *skb)
अणु
	पूर्णांक required_number_of_descriptors = 0;
	अचिन्हित पूर्णांक start_frame_length = 0;
	अचिन्हित पूर्णांक frame_length = 0;
	अचिन्हित पूर्णांक head_length = 0;
	अचिन्हित दीर्घ irq_flags = 0;
	bool करो_बारtamp = false;
	bool ignore_sync = false;
	पूर्णांक nr_frags = 0;
	bool gso = false;
	पूर्णांक j;

	required_number_of_descriptors = lan743x_tx_get_desc_cnt(tx, skb);

	spin_lock_irqsave(&tx->ring_lock, irq_flags);
	अगर (required_number_of_descriptors >
		lan743x_tx_get_avail_desc(tx)) अणु
		अगर (required_number_of_descriptors > (tx->ring_size - 1)) अणु
			dev_kमुक्त_skb_irq(skb);
		पूर्ण अन्यथा अणु
			/* save to overflow buffer */
			tx->overflow_skb = skb;
			netअगर_stop_queue(tx->adapter->netdev);
		पूर्ण
		जाओ unlock;
	पूर्ण

	/* space available, transmit skb  */
	अगर ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
	    (tx->ts_flags & TX_TS_FLAG_TIMESTAMPING_ENABLED) &&
	    (lan743x_ptp_request_tx_बारtamp(tx->adapter))) अणु
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		करो_बारtamp = true;
		अगर (tx->ts_flags & TX_TS_FLAG_ONE_STEP_SYNC)
			ignore_sync = true;
	पूर्ण
	head_length = skb_headlen(skb);
	frame_length = skb_pagelen(skb);
	nr_frags = skb_shinfo(skb)->nr_frags;
	start_frame_length = frame_length;
	gso = skb_is_gso(skb);
	अगर (gso) अणु
		start_frame_length = max(skb_shinfo(skb)->gso_size,
					 (अचिन्हित लघु)8);
	पूर्ण

	अगर (lan743x_tx_frame_start(tx,
				   skb->data, head_length,
				   start_frame_length,
				   करो_बारtamp,
				   skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		dev_kमुक्त_skb_irq(skb);
		जाओ unlock;
	पूर्ण

	अगर (gso)
		lan743x_tx_frame_add_lso(tx, frame_length, nr_frags);

	अगर (nr_frags <= 0)
		जाओ finish;

	क्रम (j = 0; j < nr_frags; j++) अणु
		स्थिर skb_frag_t *frag = &(skb_shinfo(skb)->frags[j]);

		अगर (lan743x_tx_frame_add_fragment(tx, frag, frame_length)) अणु
			/* upon error no need to call
			 *	lan743x_tx_frame_end
			 * frame assembler clean up was perक्रमmed inside
			 *	lan743x_tx_frame_add_fragment
			 */
			dev_kमुक्त_skb_irq(skb);
			जाओ unlock;
		पूर्ण
	पूर्ण

finish:
	lan743x_tx_frame_end(tx, skb, करो_बारtamp, ignore_sync);

unlock:
	spin_unlock_irqrestore(&tx->ring_lock, irq_flags);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक lan743x_tx_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक weight)
अणु
	काष्ठा lan743x_tx *tx = container_of(napi, काष्ठा lan743x_tx, napi);
	काष्ठा lan743x_adapter *adapter = tx->adapter;
	bool start_transmitter = false;
	अचिन्हित दीर्घ irq_flags = 0;
	u32 ioc_bit = 0;

	ioc_bit = DMAC_INT_BIT_TX_IOC_(tx->channel_number);
	lan743x_csr_पढ़ो(adapter, DMAC_INT_STS);
	अगर (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_W2C)
		lan743x_csr_ग_लिखो(adapter, DMAC_INT_STS, ioc_bit);
	spin_lock_irqsave(&tx->ring_lock, irq_flags);

	/* clean up tx ring */
	lan743x_tx_release_completed_descriptors(tx);
	अगर (netअगर_queue_stopped(adapter->netdev)) अणु
		अगर (tx->overflow_skb) अणु
			अगर (lan743x_tx_get_desc_cnt(tx, tx->overflow_skb) <=
				lan743x_tx_get_avail_desc(tx))
				start_transmitter = true;
		पूर्ण अन्यथा अणु
			netअगर_wake_queue(adapter->netdev);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&tx->ring_lock, irq_flags);

	अगर (start_transmitter) अणु
		/* space is now available, transmit overflow skb */
		lan743x_tx_xmit_frame(tx, tx->overflow_skb);
		tx->overflow_skb = शून्य;
		netअगर_wake_queue(adapter->netdev);
	पूर्ण

	अगर (!napi_complete(napi))
		जाओ करोne;

	/* enable isr */
	lan743x_csr_ग_लिखो(adapter, INT_EN_SET,
			  INT_BIT_DMA_TX_(tx->channel_number));
	lan743x_csr_पढ़ो(adapter, INT_STS);

करोne:
	वापस 0;
पूर्ण

अटल व्योम lan743x_tx_ring_cleanup(काष्ठा lan743x_tx *tx)
अणु
	अगर (tx->head_cpu_ptr) अणु
		dma_मुक्त_coherent(&tx->adapter->pdev->dev,
				  माप(*tx->head_cpu_ptr), tx->head_cpu_ptr,
				  tx->head_dma_ptr);
		tx->head_cpu_ptr = शून्य;
		tx->head_dma_ptr = 0;
	पूर्ण
	kमुक्त(tx->buffer_info);
	tx->buffer_info = शून्य;

	अगर (tx->ring_cpu_ptr) अणु
		dma_मुक्त_coherent(&tx->adapter->pdev->dev,
				  tx->ring_allocation_size, tx->ring_cpu_ptr,
				  tx->ring_dma_ptr);
		tx->ring_allocation_size = 0;
		tx->ring_cpu_ptr = शून्य;
		tx->ring_dma_ptr = 0;
	पूर्ण
	tx->ring_size = 0;
पूर्ण

अटल पूर्णांक lan743x_tx_ring_init(काष्ठा lan743x_tx *tx)
अणु
	माप_प्रकार ring_allocation_size = 0;
	व्योम *cpu_ptr = शून्य;
	dma_addr_t dma_ptr;
	पूर्णांक ret = -ENOMEM;

	tx->ring_size = LAN743X_TX_RING_SIZE;
	अगर (tx->ring_size & ~TX_CFG_B_TX_RING_LEN_MASK_) अणु
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण
	ring_allocation_size = ALIGN(tx->ring_size *
				     माप(काष्ठा lan743x_tx_descriptor),
				     PAGE_SIZE);
	dma_ptr = 0;
	cpu_ptr = dma_alloc_coherent(&tx->adapter->pdev->dev,
				     ring_allocation_size, &dma_ptr, GFP_KERNEL);
	अगर (!cpu_ptr) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	tx->ring_allocation_size = ring_allocation_size;
	tx->ring_cpu_ptr = (काष्ठा lan743x_tx_descriptor *)cpu_ptr;
	tx->ring_dma_ptr = dma_ptr;

	cpu_ptr = kसुस्मृति(tx->ring_size, माप(*tx->buffer_info), GFP_KERNEL);
	अगर (!cpu_ptr) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण
	tx->buffer_info = (काष्ठा lan743x_tx_buffer_info *)cpu_ptr;
	dma_ptr = 0;
	cpu_ptr = dma_alloc_coherent(&tx->adapter->pdev->dev,
				     माप(*tx->head_cpu_ptr), &dma_ptr,
				     GFP_KERNEL);
	अगर (!cpu_ptr) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	tx->head_cpu_ptr = cpu_ptr;
	tx->head_dma_ptr = dma_ptr;
	अगर (tx->head_dma_ptr & 0x3) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	lan743x_tx_ring_cleanup(tx);
	वापस ret;
पूर्ण

अटल व्योम lan743x_tx_बंद(काष्ठा lan743x_tx *tx)
अणु
	काष्ठा lan743x_adapter *adapter = tx->adapter;

	lan743x_csr_ग_लिखो(adapter,
			  DMAC_CMD,
			  DMAC_CMD_STOP_T_(tx->channel_number));
	lan743x_dmac_tx_रुको_till_stopped(adapter, tx->channel_number);

	lan743x_csr_ग_लिखो(adapter,
			  DMAC_INT_EN_CLR,
			  DMAC_INT_BIT_TX_IOC_(tx->channel_number));
	lan743x_csr_ग_लिखो(adapter, INT_EN_CLR,
			  INT_BIT_DMA_TX_(tx->channel_number));
	napi_disable(&tx->napi);
	netअगर_napi_del(&tx->napi);

	lan743x_csr_ग_लिखो(adapter, FCT_TX_CTL,
			  FCT_TX_CTL_DIS_(tx->channel_number));
	lan743x_csr_रुको_क्रम_bit(adapter, FCT_TX_CTL,
				 FCT_TX_CTL_EN_(tx->channel_number),
				 0, 1000, 20000, 100);

	lan743x_tx_release_all_descriptors(tx);

	अगर (tx->overflow_skb) अणु
		dev_kमुक्त_skb(tx->overflow_skb);
		tx->overflow_skb = शून्य;
	पूर्ण

	lan743x_tx_ring_cleanup(tx);
पूर्ण

अटल पूर्णांक lan743x_tx_खोलो(काष्ठा lan743x_tx *tx)
अणु
	काष्ठा lan743x_adapter *adapter = शून्य;
	u32 data = 0;
	पूर्णांक ret;

	adapter = tx->adapter;
	ret = lan743x_tx_ring_init(tx);
	अगर (ret)
		वापस ret;

	/* initialize fअगरo */
	lan743x_csr_ग_लिखो(adapter, FCT_TX_CTL,
			  FCT_TX_CTL_RESET_(tx->channel_number));
	lan743x_csr_रुको_क्रम_bit(adapter, FCT_TX_CTL,
				 FCT_TX_CTL_RESET_(tx->channel_number),
				 0, 1000, 20000, 100);

	/* enable fअगरo */
	lan743x_csr_ग_लिखो(adapter, FCT_TX_CTL,
			  FCT_TX_CTL_EN_(tx->channel_number));

	/* reset tx channel */
	lan743x_csr_ग_लिखो(adapter, DMAC_CMD,
			  DMAC_CMD_TX_SWR_(tx->channel_number));
	lan743x_csr_रुको_क्रम_bit(adapter, DMAC_CMD,
				 DMAC_CMD_TX_SWR_(tx->channel_number),
				 0, 1000, 20000, 100);

	/* Write TX_BASE_ADDR */
	lan743x_csr_ग_लिखो(adapter,
			  TX_BASE_ADDRH(tx->channel_number),
			  DMA_ADDR_HIGH32(tx->ring_dma_ptr));
	lan743x_csr_ग_लिखो(adapter,
			  TX_BASE_ADDRL(tx->channel_number),
			  DMA_ADDR_LOW32(tx->ring_dma_ptr));

	/* Write TX_CFG_B */
	data = lan743x_csr_पढ़ो(adapter, TX_CFG_B(tx->channel_number));
	data &= ~TX_CFG_B_TX_RING_LEN_MASK_;
	data |= ((tx->ring_size) & TX_CFG_B_TX_RING_LEN_MASK_);
	अगर (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0))
		data |= TX_CFG_B_TDMABL_512_;
	lan743x_csr_ग_लिखो(adapter, TX_CFG_B(tx->channel_number), data);

	/* Write TX_CFG_A */
	data = TX_CFG_A_TX_TMR_HPWB_SEL_IOC_ | TX_CFG_A_TX_HP_WB_EN_;
	अगर (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0)) अणु
		data |= TX_CFG_A_TX_HP_WB_ON_INT_TMR_;
		data |= TX_CFG_A_TX_PF_THRES_SET_(0x10);
		data |= TX_CFG_A_TX_PF_PRI_THRES_SET_(0x04);
		data |= TX_CFG_A_TX_HP_WB_THRES_SET_(0x07);
	पूर्ण
	lan743x_csr_ग_लिखो(adapter, TX_CFG_A(tx->channel_number), data);

	/* Write TX_HEAD_WRITEBACK_ADDR */
	lan743x_csr_ग_लिखो(adapter,
			  TX_HEAD_WRITEBACK_ADDRH(tx->channel_number),
			  DMA_ADDR_HIGH32(tx->head_dma_ptr));
	lan743x_csr_ग_लिखो(adapter,
			  TX_HEAD_WRITEBACK_ADDRL(tx->channel_number),
			  DMA_ADDR_LOW32(tx->head_dma_ptr));

	/* set last head */
	tx->last_head = lan743x_csr_पढ़ो(adapter, TX_HEAD(tx->channel_number));

	/* ग_लिखो TX_TAIL */
	tx->last_tail = 0;
	lan743x_csr_ग_लिखो(adapter, TX_TAIL(tx->channel_number),
			  (u32)(tx->last_tail));
	tx->vector_flags = lan743x_पूर्णांकr_get_vector_flags(adapter,
							 INT_BIT_DMA_TX_
							 (tx->channel_number));
	netअगर_tx_napi_add(adapter->netdev,
			  &tx->napi, lan743x_tx_napi_poll,
			  tx->ring_size - 1);
	napi_enable(&tx->napi);

	data = 0;
	अगर (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_CLEAR)
		data |= TX_CFG_C_TX_TOP_INT_EN_AUTO_CLR_;
	अगर (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_AUTO_CLEAR)
		data |= TX_CFG_C_TX_DMA_INT_STS_AUTO_CLR_;
	अगर (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_R2C)
		data |= TX_CFG_C_TX_INT_STS_R2C_MODE_MASK_;
	अगर (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_R2C)
		data |= TX_CFG_C_TX_INT_EN_R2C_;
	lan743x_csr_ग_लिखो(adapter, TX_CFG_C(tx->channel_number), data);

	अगर (!(tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_SET))
		lan743x_csr_ग_लिखो(adapter, INT_EN_SET,
				  INT_BIT_DMA_TX_(tx->channel_number));
	lan743x_csr_ग_लिखो(adapter, DMAC_INT_EN_SET,
			  DMAC_INT_BIT_TX_IOC_(tx->channel_number));

	/*  start dmac channel */
	lan743x_csr_ग_लिखो(adapter, DMAC_CMD,
			  DMAC_CMD_START_T_(tx->channel_number));
	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_rx_next_index(काष्ठा lan743x_rx *rx, पूर्णांक index)
अणु
	वापस ((++index) % rx->ring_size);
पूर्ण

अटल व्योम lan743x_rx_update_tail(काष्ठा lan743x_rx *rx, पूर्णांक index)
अणु
	/* update the tail once per 8 descriptors */
	अगर ((index & 7) == 7)
		lan743x_csr_ग_लिखो(rx->adapter, RX_TAIL(rx->channel_number),
				  index);
पूर्ण

अटल पूर्णांक lan743x_rx_init_ring_element(काष्ठा lan743x_rx *rx, पूर्णांक index)
अणु
	काष्ठा net_device *netdev = rx->adapter->netdev;
	काष्ठा device *dev = &rx->adapter->pdev->dev;
	काष्ठा lan743x_rx_buffer_info *buffer_info;
	अचिन्हित पूर्णांक buffer_length, used_length;
	काष्ठा lan743x_rx_descriptor *descriptor;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_ptr;

	buffer_length = netdev->mtu + ETH_HLEN + ETH_FCS_LEN + RX_HEAD_PADDING;

	descriptor = &rx->ring_cpu_ptr[index];
	buffer_info = &rx->buffer_info[index];
	skb = __netdev_alloc_skb(netdev, buffer_length, GFP_ATOMIC | GFP_DMA);
	अगर (!skb)
		वापस -ENOMEM;
	dma_ptr = dma_map_single(dev, skb->data, buffer_length, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, dma_ptr)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस -ENOMEM;
	पूर्ण
	अगर (buffer_info->dma_ptr) अणु
		/* sync used area of buffer only */
		अगर (le32_to_cpu(descriptor->data0) & RX_DESC_DATA0_LS_)
			/* frame length is valid only अगर LS bit is set.
			 * it's a safe upper bound क्रम the used area in this
			 * buffer.
			 */
			used_length = min(RX_DESC_DATA0_FRAME_LENGTH_GET_
					  (le32_to_cpu(descriptor->data0)),
					  buffer_info->buffer_length);
		अन्यथा
			used_length = buffer_info->buffer_length;
		dma_sync_single_क्रम_cpu(dev, buffer_info->dma_ptr,
					used_length,
					DMA_FROM_DEVICE);
		dma_unmap_single_attrs(dev, buffer_info->dma_ptr,
				       buffer_info->buffer_length,
				       DMA_FROM_DEVICE,
				       DMA_ATTR_SKIP_CPU_SYNC);
	पूर्ण

	buffer_info->skb = skb;
	buffer_info->dma_ptr = dma_ptr;
	buffer_info->buffer_length = buffer_length;
	descriptor->data1 = cpu_to_le32(DMA_ADDR_LOW32(buffer_info->dma_ptr));
	descriptor->data2 = cpu_to_le32(DMA_ADDR_HIGH32(buffer_info->dma_ptr));
	descriptor->data3 = 0;
	descriptor->data0 = cpu_to_le32((RX_DESC_DATA0_OWN_ |
			    (buffer_length & RX_DESC_DATA0_BUF_LENGTH_MASK_)));
	lan743x_rx_update_tail(rx, index);

	वापस 0;
पूर्ण

अटल व्योम lan743x_rx_reuse_ring_element(काष्ठा lan743x_rx *rx, पूर्णांक index)
अणु
	काष्ठा lan743x_rx_buffer_info *buffer_info;
	काष्ठा lan743x_rx_descriptor *descriptor;

	descriptor = &rx->ring_cpu_ptr[index];
	buffer_info = &rx->buffer_info[index];

	descriptor->data1 = cpu_to_le32(DMA_ADDR_LOW32(buffer_info->dma_ptr));
	descriptor->data2 = cpu_to_le32(DMA_ADDR_HIGH32(buffer_info->dma_ptr));
	descriptor->data3 = 0;
	descriptor->data0 = cpu_to_le32((RX_DESC_DATA0_OWN_ |
			    ((buffer_info->buffer_length) &
			    RX_DESC_DATA0_BUF_LENGTH_MASK_)));
	lan743x_rx_update_tail(rx, index);
पूर्ण

अटल व्योम lan743x_rx_release_ring_element(काष्ठा lan743x_rx *rx, पूर्णांक index)
अणु
	काष्ठा lan743x_rx_buffer_info *buffer_info;
	काष्ठा lan743x_rx_descriptor *descriptor;

	descriptor = &rx->ring_cpu_ptr[index];
	buffer_info = &rx->buffer_info[index];

	स_रखो(descriptor, 0, माप(*descriptor));

	अगर (buffer_info->dma_ptr) अणु
		dma_unmap_single(&rx->adapter->pdev->dev,
				 buffer_info->dma_ptr,
				 buffer_info->buffer_length,
				 DMA_FROM_DEVICE);
		buffer_info->dma_ptr = 0;
	पूर्ण

	अगर (buffer_info->skb) अणु
		dev_kमुक्त_skb(buffer_info->skb);
		buffer_info->skb = शून्य;
	पूर्ण

	स_रखो(buffer_info, 0, माप(*buffer_info));
पूर्ण

अटल काष्ठा sk_buff *
lan743x_rx_trim_skb(काष्ठा sk_buff *skb, पूर्णांक frame_length)
अणु
	अगर (skb_linearize(skb)) अणु
		dev_kमुक्त_skb_irq(skb);
		वापस शून्य;
	पूर्ण
	frame_length = max_t(पूर्णांक, 0, frame_length - ETH_FCS_LEN);
	अगर (skb->len > frame_length) अणु
		skb->tail -= skb->len - frame_length;
		skb->len = frame_length;
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक lan743x_rx_process_buffer(काष्ठा lan743x_rx *rx)
अणु
	पूर्णांक current_head_index = le32_to_cpu(*rx->head_cpu_ptr);
	काष्ठा lan743x_rx_descriptor *descriptor, *desc_ext;
	काष्ठा net_device *netdev = rx->adapter->netdev;
	पूर्णांक result = RX_PROCESS_RESULT_NOTHING_TO_DO;
	काष्ठा lan743x_rx_buffer_info *buffer_info;
	पूर्णांक frame_length, buffer_length;
	पूर्णांक extension_index = -1;
	bool is_last, is_first;
	काष्ठा sk_buff *skb;

	अगर (current_head_index < 0 || current_head_index >= rx->ring_size)
		जाओ करोne;

	अगर (rx->last_head < 0 || rx->last_head >= rx->ring_size)
		जाओ करोne;

	अगर (rx->last_head == current_head_index)
		जाओ करोne;

	descriptor = &rx->ring_cpu_ptr[rx->last_head];
	अगर (le32_to_cpu(descriptor->data0) & RX_DESC_DATA0_OWN_)
		जाओ करोne;
	buffer_info = &rx->buffer_info[rx->last_head];

	is_last = le32_to_cpu(descriptor->data0) & RX_DESC_DATA0_LS_;
	is_first = le32_to_cpu(descriptor->data0) & RX_DESC_DATA0_FS_;

	अगर (is_last && le32_to_cpu(descriptor->data0) & RX_DESC_DATA0_EXT_) अणु
		/* extension is expected to follow */
		पूर्णांक index = lan743x_rx_next_index(rx, rx->last_head);

		अगर (index == current_head_index)
			/* extension not yet available */
			जाओ करोne;
		desc_ext = &rx->ring_cpu_ptr[index];
		अगर (le32_to_cpu(desc_ext->data0) & RX_DESC_DATA0_OWN_)
			/* extension not yet available */
			जाओ करोne;
		अगर (!(le32_to_cpu(desc_ext->data0) & RX_DESC_DATA0_EXT_))
			जाओ move_क्रमward;
		extension_index = index;
	पूर्ण

	/* Only the last buffer in a multi-buffer frame contains the total frame
	 * length. The chip occasionally sends more buffers than strictly
	 * required to reach the total frame length.
	 * Handle this by adding all buffers to the skb in their entirety.
	 * Once the real frame length is known, trim the skb.
	 */
	frame_length =
		RX_DESC_DATA0_FRAME_LENGTH_GET_(le32_to_cpu(descriptor->data0));
	buffer_length = buffer_info->buffer_length;

	netdev_dbg(netdev, "%s%schunk: %d/%d",
		   is_first ? "first " : "      ",
		   is_last  ? "last  " : "      ",
		   frame_length, buffer_length);

	/* save existing skb, allocate new skb and map to dma */
	skb = buffer_info->skb;
	अगर (lan743x_rx_init_ring_element(rx, rx->last_head)) अणु
		/* failed to allocate next skb.
		 * Memory is very low.
		 * Drop this packet and reuse buffer.
		 */
		lan743x_rx_reuse_ring_element(rx, rx->last_head);
		/* drop packet that was being assembled */
		dev_kमुक्त_skb_irq(rx->skb_head);
		rx->skb_head = शून्य;
		जाओ process_extension;
	पूर्ण

	/* add buffers to skb via skb->frag_list */
	अगर (is_first) अणु
		skb_reserve(skb, RX_HEAD_PADDING);
		skb_put(skb, buffer_length - RX_HEAD_PADDING);
		अगर (rx->skb_head)
			dev_kमुक्त_skb_irq(rx->skb_head);
		rx->skb_head = skb;
	पूर्ण अन्यथा अगर (rx->skb_head) अणु
		skb_put(skb, buffer_length);
		अगर (skb_shinfo(rx->skb_head)->frag_list)
			rx->skb_tail->next = skb;
		अन्यथा
			skb_shinfo(rx->skb_head)->frag_list = skb;
		rx->skb_tail = skb;
		rx->skb_head->len += skb->len;
		rx->skb_head->data_len += skb->len;
		rx->skb_head->truesize += skb->truesize;
	पूर्ण अन्यथा अणु
		/* packet to assemble has alपढ़ोy been dropped because one or
		 * more of its buffers could not be allocated
		 */
		netdev_dbg(netdev, "drop buffer intended for dropped packet");
		dev_kमुक्त_skb_irq(skb);
	पूर्ण

process_extension:
	अगर (extension_index >= 0) अणु
		u32 ts_sec;
		u32 ts_nsec;

		ts_sec = le32_to_cpu(desc_ext->data1);
		ts_nsec = (le32_to_cpu(desc_ext->data2) &
			  RX_DESC_DATA2_TS_NS_MASK_);
		अगर (rx->skb_head)
			skb_hwtstamps(rx->skb_head)->hwtstamp =
				kसमय_set(ts_sec, ts_nsec);
		lan743x_rx_reuse_ring_element(rx, extension_index);
		rx->last_head = extension_index;
		netdev_dbg(netdev, "process extension");
	पूर्ण

	अगर (is_last && rx->skb_head)
		rx->skb_head = lan743x_rx_trim_skb(rx->skb_head, frame_length);

	अगर (is_last && rx->skb_head) अणु
		rx->skb_head->protocol = eth_type_trans(rx->skb_head,
							rx->adapter->netdev);
		netdev_dbg(netdev, "sending %d byte frame to OS",
			   rx->skb_head->len);
		napi_gro_receive(&rx->napi, rx->skb_head);
		rx->skb_head = शून्य;
	पूर्ण

move_क्रमward:
	/* push tail and head क्रमward */
	rx->last_tail = rx->last_head;
	rx->last_head = lan743x_rx_next_index(rx, rx->last_head);
	result = RX_PROCESS_RESULT_BUFFER_RECEIVED;
करोne:
	वापस result;
पूर्ण

अटल पूर्णांक lan743x_rx_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक weight)
अणु
	काष्ठा lan743x_rx *rx = container_of(napi, काष्ठा lan743x_rx, napi);
	काष्ठा lan743x_adapter *adapter = rx->adapter;
	पूर्णांक result = RX_PROCESS_RESULT_NOTHING_TO_DO;
	u32 rx_tail_flags = 0;
	पूर्णांक count;

	अगर (rx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_W2C) अणु
		/* clear पूर्णांक status bit beक्रमe पढ़ोing packet */
		lan743x_csr_ग_लिखो(adapter, DMAC_INT_STS,
				  DMAC_INT_BIT_RXFRM_(rx->channel_number));
	पूर्ण
	क्रम (count = 0; count < weight; count++) अणु
		result = lan743x_rx_process_buffer(rx);
		अगर (result == RX_PROCESS_RESULT_NOTHING_TO_DO)
			अवरोध;
	पूर्ण
	rx->frame_count += count;
	अगर (count == weight || result == RX_PROCESS_RESULT_BUFFER_RECEIVED)
		वापस weight;

	अगर (!napi_complete_करोne(napi, count))
		वापस count;

	/* re-arm पूर्णांकerrupts, must ग_लिखो to rx tail on some chip variants */
	अगर (rx->vector_flags & LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_SET)
		rx_tail_flags |= RX_TAIL_SET_TOP_INT_VEC_EN_;
	अगर (rx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_SET) अणु
		rx_tail_flags |= RX_TAIL_SET_TOP_INT_EN_;
	पूर्ण अन्यथा अणु
		lan743x_csr_ग_लिखो(adapter, INT_EN_SET,
				  INT_BIT_DMA_RX_(rx->channel_number));
	पूर्ण

	अगर (rx_tail_flags)
		lan743x_csr_ग_लिखो(adapter, RX_TAIL(rx->channel_number),
				  rx_tail_flags | rx->last_tail);

	वापस count;
पूर्ण

अटल व्योम lan743x_rx_ring_cleanup(काष्ठा lan743x_rx *rx)
अणु
	अगर (rx->buffer_info && rx->ring_cpu_ptr) अणु
		पूर्णांक index;

		क्रम (index = 0; index < rx->ring_size; index++)
			lan743x_rx_release_ring_element(rx, index);
	पूर्ण

	अगर (rx->head_cpu_ptr) अणु
		dma_मुक्त_coherent(&rx->adapter->pdev->dev,
				  माप(*rx->head_cpu_ptr), rx->head_cpu_ptr,
				  rx->head_dma_ptr);
		rx->head_cpu_ptr = शून्य;
		rx->head_dma_ptr = 0;
	पूर्ण

	kमुक्त(rx->buffer_info);
	rx->buffer_info = शून्य;

	अगर (rx->ring_cpu_ptr) अणु
		dma_मुक्त_coherent(&rx->adapter->pdev->dev,
				  rx->ring_allocation_size, rx->ring_cpu_ptr,
				  rx->ring_dma_ptr);
		rx->ring_allocation_size = 0;
		rx->ring_cpu_ptr = शून्य;
		rx->ring_dma_ptr = 0;
	पूर्ण

	rx->ring_size = 0;
	rx->last_head = 0;
पूर्ण

अटल पूर्णांक lan743x_rx_ring_init(काष्ठा lan743x_rx *rx)
अणु
	माप_प्रकार ring_allocation_size = 0;
	dma_addr_t dma_ptr = 0;
	व्योम *cpu_ptr = शून्य;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक index = 0;

	rx->ring_size = LAN743X_RX_RING_SIZE;
	अगर (rx->ring_size <= 1) अणु
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण
	अगर (rx->ring_size & ~RX_CFG_B_RX_RING_LEN_MASK_) अणु
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण
	ring_allocation_size = ALIGN(rx->ring_size *
				     माप(काष्ठा lan743x_rx_descriptor),
				     PAGE_SIZE);
	dma_ptr = 0;
	cpu_ptr = dma_alloc_coherent(&rx->adapter->pdev->dev,
				     ring_allocation_size, &dma_ptr, GFP_KERNEL);
	अगर (!cpu_ptr) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण
	rx->ring_allocation_size = ring_allocation_size;
	rx->ring_cpu_ptr = (काष्ठा lan743x_rx_descriptor *)cpu_ptr;
	rx->ring_dma_ptr = dma_ptr;

	cpu_ptr = kसुस्मृति(rx->ring_size, माप(*rx->buffer_info),
			  GFP_KERNEL);
	अगर (!cpu_ptr) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण
	rx->buffer_info = (काष्ठा lan743x_rx_buffer_info *)cpu_ptr;
	dma_ptr = 0;
	cpu_ptr = dma_alloc_coherent(&rx->adapter->pdev->dev,
				     माप(*rx->head_cpu_ptr), &dma_ptr,
				     GFP_KERNEL);
	अगर (!cpu_ptr) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	rx->head_cpu_ptr = cpu_ptr;
	rx->head_dma_ptr = dma_ptr;
	अगर (rx->head_dma_ptr & 0x3) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	rx->last_head = 0;
	क्रम (index = 0; index < rx->ring_size; index++) अणु
		ret = lan743x_rx_init_ring_element(rx, index);
		अगर (ret)
			जाओ cleanup;
	पूर्ण
	वापस 0;

cleanup:
	lan743x_rx_ring_cleanup(rx);
	वापस ret;
पूर्ण

अटल व्योम lan743x_rx_बंद(काष्ठा lan743x_rx *rx)
अणु
	काष्ठा lan743x_adapter *adapter = rx->adapter;

	lan743x_csr_ग_लिखो(adapter, FCT_RX_CTL,
			  FCT_RX_CTL_DIS_(rx->channel_number));
	lan743x_csr_रुको_क्रम_bit(adapter, FCT_RX_CTL,
				 FCT_RX_CTL_EN_(rx->channel_number),
				 0, 1000, 20000, 100);

	lan743x_csr_ग_लिखो(adapter, DMAC_CMD,
			  DMAC_CMD_STOP_R_(rx->channel_number));
	lan743x_dmac_rx_रुको_till_stopped(adapter, rx->channel_number);

	lan743x_csr_ग_लिखो(adapter, DMAC_INT_EN_CLR,
			  DMAC_INT_BIT_RXFRM_(rx->channel_number));
	lan743x_csr_ग_लिखो(adapter, INT_EN_CLR,
			  INT_BIT_DMA_RX_(rx->channel_number));
	napi_disable(&rx->napi);

	netअगर_napi_del(&rx->napi);

	lan743x_rx_ring_cleanup(rx);
पूर्ण

अटल पूर्णांक lan743x_rx_खोलो(काष्ठा lan743x_rx *rx)
अणु
	काष्ठा lan743x_adapter *adapter = rx->adapter;
	u32 data = 0;
	पूर्णांक ret;

	rx->frame_count = 0;
	ret = lan743x_rx_ring_init(rx);
	अगर (ret)
		जाओ वापस_error;

	netअगर_napi_add(adapter->netdev,
		       &rx->napi, lan743x_rx_napi_poll,
		       NAPI_POLL_WEIGHT);

	lan743x_csr_ग_लिखो(adapter, DMAC_CMD,
			  DMAC_CMD_RX_SWR_(rx->channel_number));
	lan743x_csr_रुको_क्रम_bit(adapter, DMAC_CMD,
				 DMAC_CMD_RX_SWR_(rx->channel_number),
				 0, 1000, 20000, 100);

	/* set ring base address */
	lan743x_csr_ग_लिखो(adapter,
			  RX_BASE_ADDRH(rx->channel_number),
			  DMA_ADDR_HIGH32(rx->ring_dma_ptr));
	lan743x_csr_ग_लिखो(adapter,
			  RX_BASE_ADDRL(rx->channel_number),
			  DMA_ADDR_LOW32(rx->ring_dma_ptr));

	/* set rx ग_लिखो back address */
	lan743x_csr_ग_लिखो(adapter,
			  RX_HEAD_WRITEBACK_ADDRH(rx->channel_number),
			  DMA_ADDR_HIGH32(rx->head_dma_ptr));
	lan743x_csr_ग_लिखो(adapter,
			  RX_HEAD_WRITEBACK_ADDRL(rx->channel_number),
			  DMA_ADDR_LOW32(rx->head_dma_ptr));
	data = RX_CFG_A_RX_HP_WB_EN_;
	अगर (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0)) अणु
		data |= (RX_CFG_A_RX_WB_ON_INT_TMR_ |
			RX_CFG_A_RX_WB_THRES_SET_(0x7) |
			RX_CFG_A_RX_PF_THRES_SET_(16) |
			RX_CFG_A_RX_PF_PRI_THRES_SET_(4));
	पूर्ण

	/* set RX_CFG_A */
	lan743x_csr_ग_लिखो(adapter,
			  RX_CFG_A(rx->channel_number), data);

	/* set RX_CFG_B */
	data = lan743x_csr_पढ़ो(adapter, RX_CFG_B(rx->channel_number));
	data &= ~RX_CFG_B_RX_PAD_MASK_;
	अगर (!RX_HEAD_PADDING)
		data |= RX_CFG_B_RX_PAD_0_;
	अन्यथा
		data |= RX_CFG_B_RX_PAD_2_;
	data &= ~RX_CFG_B_RX_RING_LEN_MASK_;
	data |= ((rx->ring_size) & RX_CFG_B_RX_RING_LEN_MASK_);
	data |= RX_CFG_B_TS_ALL_RX_;
	अगर (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0))
		data |= RX_CFG_B_RDMABL_512_;

	lan743x_csr_ग_लिखो(adapter, RX_CFG_B(rx->channel_number), data);
	rx->vector_flags = lan743x_पूर्णांकr_get_vector_flags(adapter,
							 INT_BIT_DMA_RX_
							 (rx->channel_number));

	/* set RX_CFG_C */
	data = 0;
	अगर (rx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_CLEAR)
		data |= RX_CFG_C_RX_TOP_INT_EN_AUTO_CLR_;
	अगर (rx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_AUTO_CLEAR)
		data |= RX_CFG_C_RX_DMA_INT_STS_AUTO_CLR_;
	अगर (rx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_R2C)
		data |= RX_CFG_C_RX_INT_STS_R2C_MODE_MASK_;
	अगर (rx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_R2C)
		data |= RX_CFG_C_RX_INT_EN_R2C_;
	lan743x_csr_ग_लिखो(adapter, RX_CFG_C(rx->channel_number), data);

	rx->last_tail = ((u32)(rx->ring_size - 1));
	lan743x_csr_ग_लिखो(adapter, RX_TAIL(rx->channel_number),
			  rx->last_tail);
	rx->last_head = lan743x_csr_पढ़ो(adapter, RX_HEAD(rx->channel_number));
	अगर (rx->last_head) अणु
		ret = -EIO;
		जाओ napi_delete;
	पूर्ण

	napi_enable(&rx->napi);

	lan743x_csr_ग_लिखो(adapter, INT_EN_SET,
			  INT_BIT_DMA_RX_(rx->channel_number));
	lan743x_csr_ग_लिखो(adapter, DMAC_INT_STS,
			  DMAC_INT_BIT_RXFRM_(rx->channel_number));
	lan743x_csr_ग_लिखो(adapter, DMAC_INT_EN_SET,
			  DMAC_INT_BIT_RXFRM_(rx->channel_number));
	lan743x_csr_ग_लिखो(adapter, DMAC_CMD,
			  DMAC_CMD_START_R_(rx->channel_number));

	/* initialize fअगरo */
	lan743x_csr_ग_लिखो(adapter, FCT_RX_CTL,
			  FCT_RX_CTL_RESET_(rx->channel_number));
	lan743x_csr_रुको_क्रम_bit(adapter, FCT_RX_CTL,
				 FCT_RX_CTL_RESET_(rx->channel_number),
				 0, 1000, 20000, 100);
	lan743x_csr_ग_लिखो(adapter, FCT_FLOW(rx->channel_number),
			  FCT_FLOW_CTL_REQ_EN_ |
			  FCT_FLOW_CTL_ON_THRESHOLD_SET_(0x2A) |
			  FCT_FLOW_CTL_OFF_THRESHOLD_SET_(0xA));

	/* enable fअगरo */
	lan743x_csr_ग_लिखो(adapter, FCT_RX_CTL,
			  FCT_RX_CTL_EN_(rx->channel_number));
	वापस 0;

napi_delete:
	netअगर_napi_del(&rx->napi);
	lan743x_rx_ring_cleanup(rx);

वापस_error:
	वापस ret;
पूर्ण

अटल पूर्णांक lan743x_netdev_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	पूर्णांक index;

	lan743x_tx_बंद(&adapter->tx[0]);

	क्रम (index = 0; index < LAN743X_USED_RX_CHANNELS; index++)
		lan743x_rx_बंद(&adapter->rx[index]);

	lan743x_ptp_बंद(adapter);

	lan743x_phy_बंद(adapter);

	lan743x_mac_बंद(adapter);

	lan743x_पूर्णांकr_बंद(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_netdev_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	पूर्णांक index;
	पूर्णांक ret;

	ret = lan743x_पूर्णांकr_खोलो(adapter);
	अगर (ret)
		जाओ वापस_error;

	ret = lan743x_mac_खोलो(adapter);
	अगर (ret)
		जाओ बंद_पूर्णांकr;

	ret = lan743x_phy_खोलो(adapter);
	अगर (ret)
		जाओ बंद_mac;

	ret = lan743x_ptp_खोलो(adapter);
	अगर (ret)
		जाओ बंद_phy;

	lan743x_rfe_खोलो(adapter);

	क्रम (index = 0; index < LAN743X_USED_RX_CHANNELS; index++) अणु
		ret = lan743x_rx_खोलो(&adapter->rx[index]);
		अगर (ret)
			जाओ बंद_rx;
	पूर्ण

	ret = lan743x_tx_खोलो(&adapter->tx[0]);
	अगर (ret)
		जाओ बंद_rx;

	वापस 0;

बंद_rx:
	क्रम (index = 0; index < LAN743X_USED_RX_CHANNELS; index++) अणु
		अगर (adapter->rx[index].ring_cpu_ptr)
			lan743x_rx_बंद(&adapter->rx[index]);
	पूर्ण
	lan743x_ptp_बंद(adapter);

बंद_phy:
	lan743x_phy_बंद(adapter);

बंद_mac:
	lan743x_mac_बंद(adapter);

बंद_पूर्णांकr:
	lan743x_पूर्णांकr_बंद(adapter);

वापस_error:
	netअगर_warn(adapter, अगरup, adapter->netdev,
		   "Error opening LAN743x\n");
	वापस ret;
पूर्ण

अटल netdev_tx_t lan743x_netdev_xmit_frame(काष्ठा sk_buff *skb,
					     काष्ठा net_device *netdev)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	वापस lan743x_tx_xmit_frame(&adapter->tx[0], skb);
पूर्ण

अटल पूर्णांक lan743x_netdev_ioctl(काष्ठा net_device *netdev,
				काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	अगर (!netअगर_running(netdev))
		वापस -EINVAL;
	अगर (cmd == SIOCSHWTSTAMP)
		वापस lan743x_ptp_ioctl(netdev, अगरr, cmd);
	वापस phy_mii_ioctl(netdev->phydev, अगरr, cmd);
पूर्ण

अटल व्योम lan743x_netdev_set_multicast(काष्ठा net_device *netdev)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	lan743x_rfe_set_multicast(adapter);
पूर्ण

अटल पूर्णांक lan743x_netdev_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret = 0;

	ret = lan743x_mac_set_mtu(adapter, new_mtu);
	अगर (!ret)
		netdev->mtu = new_mtu;
	वापस ret;
पूर्ण

अटल व्योम lan743x_netdev_get_stats64(काष्ठा net_device *netdev,
				       काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	stats->rx_packets = lan743x_csr_पढ़ो(adapter, STAT_RX_TOTAL_FRAMES);
	stats->tx_packets = lan743x_csr_पढ़ो(adapter, STAT_TX_TOTAL_FRAMES);
	stats->rx_bytes = lan743x_csr_पढ़ो(adapter,
					   STAT_RX_UNICAST_BYTE_COUNT) +
			  lan743x_csr_पढ़ो(adapter,
					   STAT_RX_BROADCAST_BYTE_COUNT) +
			  lan743x_csr_पढ़ो(adapter,
					   STAT_RX_MULTICAST_BYTE_COUNT);
	stats->tx_bytes = lan743x_csr_पढ़ो(adapter,
					   STAT_TX_UNICAST_BYTE_COUNT) +
			  lan743x_csr_पढ़ो(adapter,
					   STAT_TX_BROADCAST_BYTE_COUNT) +
			  lan743x_csr_पढ़ो(adapter,
					   STAT_TX_MULTICAST_BYTE_COUNT);
	stats->rx_errors = lan743x_csr_पढ़ो(adapter, STAT_RX_FCS_ERRORS) +
			   lan743x_csr_पढ़ो(adapter,
					    STAT_RX_ALIGNMENT_ERRORS) +
			   lan743x_csr_पढ़ो(adapter, STAT_RX_JABBER_ERRORS) +
			   lan743x_csr_पढ़ो(adapter,
					    STAT_RX_UNDERSIZE_FRAME_ERRORS) +
			   lan743x_csr_पढ़ो(adapter,
					    STAT_RX_OVERSIZE_FRAME_ERRORS);
	stats->tx_errors = lan743x_csr_पढ़ो(adapter, STAT_TX_FCS_ERRORS) +
			   lan743x_csr_पढ़ो(adapter,
					    STAT_TX_EXCESS_DEFERRAL_ERRORS) +
			   lan743x_csr_पढ़ो(adapter, STAT_TX_CARRIER_ERRORS);
	stats->rx_dropped = lan743x_csr_पढ़ो(adapter,
					     STAT_RX_DROPPED_FRAMES);
	stats->tx_dropped = lan743x_csr_पढ़ो(adapter,
					     STAT_TX_EXCESSIVE_COLLISION);
	stats->multicast = lan743x_csr_पढ़ो(adapter,
					    STAT_RX_MULTICAST_FRAMES) +
			   lan743x_csr_पढ़ो(adapter,
					    STAT_TX_MULTICAST_FRAMES);
	stats->collisions = lan743x_csr_पढ़ो(adapter,
					     STAT_TX_SINGLE_COLLISIONS) +
			    lan743x_csr_पढ़ो(adapter,
					     STAT_TX_MULTIPLE_COLLISIONS) +
			    lan743x_csr_पढ़ो(adapter,
					     STAT_TX_LATE_COLLISIONS);
पूर्ण

अटल पूर्णांक lan743x_netdev_set_mac_address(काष्ठा net_device *netdev,
					  व्योम *addr)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *sock_addr = addr;
	पूर्णांक ret;

	ret = eth_prepare_mac_addr_change(netdev, sock_addr);
	अगर (ret)
		वापस ret;
	ether_addr_copy(netdev->dev_addr, sock_addr->sa_data);
	lan743x_mac_set_address(adapter, sock_addr->sa_data);
	lan743x_rfe_update_mac_address(adapter);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops lan743x_netdev_ops = अणु
	.nकरो_खोलो		= lan743x_netdev_खोलो,
	.nकरो_stop		= lan743x_netdev_बंद,
	.nकरो_start_xmit		= lan743x_netdev_xmit_frame,
	.nकरो_करो_ioctl		= lan743x_netdev_ioctl,
	.nकरो_set_rx_mode	= lan743x_netdev_set_multicast,
	.nकरो_change_mtu		= lan743x_netdev_change_mtu,
	.nकरो_get_stats64	= lan743x_netdev_get_stats64,
	.nकरो_set_mac_address	= lan743x_netdev_set_mac_address,
पूर्ण;

अटल व्योम lan743x_hardware_cleanup(काष्ठा lan743x_adapter *adapter)
अणु
	lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, 0xFFFFFFFF);
पूर्ण

अटल व्योम lan743x_mdiobus_cleanup(काष्ठा lan743x_adapter *adapter)
अणु
	mdiobus_unरेजिस्टर(adapter->mdiobus);
पूर्ण

अटल व्योम lan743x_full_cleanup(काष्ठा lan743x_adapter *adapter)
अणु
	unरेजिस्टर_netdev(adapter->netdev);

	lan743x_mdiobus_cleanup(adapter);
	lan743x_hardware_cleanup(adapter);
	lan743x_pci_cleanup(adapter);
पूर्ण

अटल पूर्णांक lan743x_hardware_init(काष्ठा lan743x_adapter *adapter,
				 काष्ठा pci_dev *pdev)
अणु
	काष्ठा lan743x_tx *tx;
	पूर्णांक index;
	पूर्णांक ret;

	adapter->पूर्णांकr.irq = adapter->pdev->irq;
	lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, 0xFFFFFFFF);

	ret = lan743x_gpio_init(adapter);
	अगर (ret)
		वापस ret;

	ret = lan743x_mac_init(adapter);
	अगर (ret)
		वापस ret;

	ret = lan743x_phy_init(adapter);
	अगर (ret)
		वापस ret;

	ret = lan743x_ptp_init(adapter);
	अगर (ret)
		वापस ret;

	lan743x_rfe_update_mac_address(adapter);

	ret = lan743x_dmac_init(adapter);
	अगर (ret)
		वापस ret;

	क्रम (index = 0; index < LAN743X_USED_RX_CHANNELS; index++) अणु
		adapter->rx[index].adapter = adapter;
		adapter->rx[index].channel_number = index;
	पूर्ण

	tx = &adapter->tx[0];
	tx->adapter = adapter;
	tx->channel_number = 0;
	spin_lock_init(&tx->ring_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_mdiobus_init(काष्ठा lan743x_adapter *adapter)
अणु
	पूर्णांक ret;

	adapter->mdiobus = devm_mdiobus_alloc(&adapter->pdev->dev);
	अगर (!(adapter->mdiobus)) अणु
		ret = -ENOMEM;
		जाओ वापस_error;
	पूर्ण

	adapter->mdiobus->priv = (व्योम *)adapter;
	adapter->mdiobus->पढ़ो = lan743x_mdiobus_पढ़ो;
	adapter->mdiobus->ग_लिखो = lan743x_mdiobus_ग_लिखो;
	adapter->mdiobus->name = "lan743x-mdiobus";
	snम_लिखो(adapter->mdiobus->id, MII_BUS_ID_SIZE,
		 "pci-%s", pci_name(adapter->pdev));

	अगर ((adapter->csr.id_rev & ID_REV_ID_MASK_) == ID_REV_ID_LAN7430_)
		/* LAN7430 uses पूर्णांकernal phy at address 1 */
		adapter->mdiobus->phy_mask = ~(u32)BIT(1);

	/* रेजिस्टर mdiobus */
	ret = mdiobus_रेजिस्टर(adapter->mdiobus);
	अगर (ret < 0)
		जाओ वापस_error;
	वापस 0;

वापस_error:
	वापस ret;
पूर्ण

/* lan743x_pcidev_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @id: entry in lan743x_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 **/
अटल पूर्णांक lan743x_pcidev_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा lan743x_adapter *adapter = शून्य;
	काष्ठा net_device *netdev = शून्य;
	पूर्णांक ret = -ENODEV;

	netdev = devm_alloc_etherdev(&pdev->dev,
				     माप(काष्ठा lan743x_adapter));
	अगर (!netdev)
		जाओ वापस_error;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->msg_enable = NETIF_MSG_DRV | NETIF_MSG_PROBE |
			      NETIF_MSG_LINK | NETIF_MSG_IFUP |
			      NETIF_MSG_IFDOWN | NETIF_MSG_TX_QUEUED;
	netdev->max_mtu = LAN743X_MAX_FRAME_SIZE;

	of_get_mac_address(pdev->dev.of_node, adapter->mac_address);

	ret = lan743x_pci_init(adapter, pdev);
	अगर (ret)
		जाओ वापस_error;

	ret = lan743x_csr_init(adapter);
	अगर (ret)
		जाओ cleanup_pci;

	ret = lan743x_hardware_init(adapter, pdev);
	अगर (ret)
		जाओ cleanup_pci;

	ret = lan743x_mdiobus_init(adapter);
	अगर (ret)
		जाओ cleanup_hardware;

	adapter->netdev->netdev_ops = &lan743x_netdev_ops;
	adapter->netdev->ethtool_ops = &lan743x_ethtool_ops;
	adapter->netdev->features = NETIF_F_SG | NETIF_F_TSO | NETIF_F_HW_CSUM;
	adapter->netdev->hw_features = adapter->netdev->features;

	/* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

	ret = रेजिस्टर_netdev(adapter->netdev);
	अगर (ret < 0)
		जाओ cleanup_mdiobus;
	वापस 0;

cleanup_mdiobus:
	lan743x_mdiobus_cleanup(adapter);

cleanup_hardware:
	lan743x_hardware_cleanup(adapter);

cleanup_pci:
	lan743x_pci_cleanup(adapter);

वापस_error:
	pr_warn("Initialization failed\n");
	वापस ret;
पूर्ण

/**
 * lan743x_pcidev_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * this is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  This could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम lan743x_pcidev_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	lan743x_full_cleanup(adapter);
पूर्ण

अटल व्योम lan743x_pcidev_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	rtnl_lock();
	netअगर_device_detach(netdev);

	/* बंद netdev when netdev is at running state.
	 * For instance, it is true when प्रणाली goes to sleep by pm-suspend
	 * However, it is false when प्रणाली goes to sleep by suspend GUI menu
	 */
	अगर (netअगर_running(netdev))
		lan743x_netdev_बंद(netdev);
	rtnl_unlock();

#अगर_घोषित CONFIG_PM
	pci_save_state(pdev);
#पूर्ण_अगर

	/* clean up lan743x portion */
	lan743x_hardware_cleanup(adapter);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल u16 lan743x_pm_wakeframe_crc16(स्थिर u8 *buf, पूर्णांक len)
अणु
	वापस bitrev16(crc16(0xFFFF, buf, len));
पूर्ण

अटल व्योम lan743x_pm_set_wol(काष्ठा lan743x_adapter *adapter)
अणु
	स्थिर u8 ipv4_multicast[3] = अणु 0x01, 0x00, 0x5E पूर्ण;
	स्थिर u8 ipv6_multicast[3] = अणु 0x33, 0x33 पूर्ण;
	स्थिर u8 arp_type[2] = अणु 0x08, 0x06 पूर्ण;
	पूर्णांक mask_index;
	u32 pmtctl;
	u32 wucsr;
	u32 macrx;
	u16 crc;

	क्रम (mask_index = 0; mask_index < MAC_NUM_OF_WUF_CFG; mask_index++)
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_CFG(mask_index), 0);

	/* clear wake settings */
	pmtctl = lan743x_csr_पढ़ो(adapter, PMT_CTL);
	pmtctl |= PMT_CTL_WUPS_MASK_;
	pmtctl &= ~(PMT_CTL_GPIO_WAKEUP_EN_ | PMT_CTL_EEE_WAKEUP_EN_ |
		PMT_CTL_WOL_EN_ | PMT_CTL_MAC_D3_RX_CLK_OVR_ |
		PMT_CTL_RX_FCT_RFE_D3_CLK_OVR_ | PMT_CTL_ETH_PHY_WAKE_EN_);

	macrx = lan743x_csr_पढ़ो(adapter, MAC_RX);

	wucsr = 0;
	mask_index = 0;

	pmtctl |= PMT_CTL_ETH_PHY_D3_COLD_OVR_ | PMT_CTL_ETH_PHY_D3_OVR_;

	अगर (adapter->wolopts & WAKE_PHY) अणु
		pmtctl |= PMT_CTL_ETH_PHY_EDPD_PLL_CTL_;
		pmtctl |= PMT_CTL_ETH_PHY_WAKE_EN_;
	पूर्ण
	अगर (adapter->wolopts & WAKE_MAGIC) अणु
		wucsr |= MAC_WUCSR_MPEN_;
		macrx |= MAC_RX_RXEN_;
		pmtctl |= PMT_CTL_WOL_EN_ | PMT_CTL_MAC_D3_RX_CLK_OVR_;
	पूर्ण
	अगर (adapter->wolopts & WAKE_UCAST) अणु
		wucsr |= MAC_WUCSR_RFE_WAKE_EN_ | MAC_WUCSR_PFDA_EN_;
		macrx |= MAC_RX_RXEN_;
		pmtctl |= PMT_CTL_WOL_EN_ | PMT_CTL_MAC_D3_RX_CLK_OVR_;
		pmtctl |= PMT_CTL_RX_FCT_RFE_D3_CLK_OVR_;
	पूर्ण
	अगर (adapter->wolopts & WAKE_BCAST) अणु
		wucsr |= MAC_WUCSR_RFE_WAKE_EN_ | MAC_WUCSR_BCST_EN_;
		macrx |= MAC_RX_RXEN_;
		pmtctl |= PMT_CTL_WOL_EN_ | PMT_CTL_MAC_D3_RX_CLK_OVR_;
		pmtctl |= PMT_CTL_RX_FCT_RFE_D3_CLK_OVR_;
	पूर्ण
	अगर (adapter->wolopts & WAKE_MCAST) अणु
		/* IPv4 multicast */
		crc = lan743x_pm_wakeframe_crc16(ipv4_multicast, 3);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_CFG(mask_index),
				  MAC_WUF_CFG_EN_ | MAC_WUF_CFG_TYPE_MCAST_ |
				  (0 << MAC_WUF_CFG_OFFSET_SHIFT_) |
				  (crc & MAC_WUF_CFG_CRC16_MASK_));
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK0(mask_index), 7);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK1(mask_index), 0);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK2(mask_index), 0);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK3(mask_index), 0);
		mask_index++;

		/* IPv6 multicast */
		crc = lan743x_pm_wakeframe_crc16(ipv6_multicast, 2);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_CFG(mask_index),
				  MAC_WUF_CFG_EN_ | MAC_WUF_CFG_TYPE_MCAST_ |
				  (0 << MAC_WUF_CFG_OFFSET_SHIFT_) |
				  (crc & MAC_WUF_CFG_CRC16_MASK_));
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK0(mask_index), 3);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK1(mask_index), 0);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK2(mask_index), 0);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK3(mask_index), 0);
		mask_index++;

		wucsr |= MAC_WUCSR_RFE_WAKE_EN_ | MAC_WUCSR_WAKE_EN_;
		macrx |= MAC_RX_RXEN_;
		pmtctl |= PMT_CTL_WOL_EN_ | PMT_CTL_MAC_D3_RX_CLK_OVR_;
		pmtctl |= PMT_CTL_RX_FCT_RFE_D3_CLK_OVR_;
	पूर्ण
	अगर (adapter->wolopts & WAKE_ARP) अणु
		/* set MAC_WUF_CFG & WUF_MASK
		 * क्रम packettype (offset 12,13) = ARP (0x0806)
		 */
		crc = lan743x_pm_wakeframe_crc16(arp_type, 2);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_CFG(mask_index),
				  MAC_WUF_CFG_EN_ | MAC_WUF_CFG_TYPE_ALL_ |
				  (0 << MAC_WUF_CFG_OFFSET_SHIFT_) |
				  (crc & MAC_WUF_CFG_CRC16_MASK_));
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK0(mask_index), 0x3000);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK1(mask_index), 0);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK2(mask_index), 0);
		lan743x_csr_ग_लिखो(adapter, MAC_WUF_MASK3(mask_index), 0);
		mask_index++;

		wucsr |= MAC_WUCSR_RFE_WAKE_EN_ | MAC_WUCSR_WAKE_EN_;
		macrx |= MAC_RX_RXEN_;
		pmtctl |= PMT_CTL_WOL_EN_ | PMT_CTL_MAC_D3_RX_CLK_OVR_;
		pmtctl |= PMT_CTL_RX_FCT_RFE_D3_CLK_OVR_;
	पूर्ण

	lan743x_csr_ग_लिखो(adapter, MAC_WUCSR, wucsr);
	lan743x_csr_ग_लिखो(adapter, PMT_CTL, pmtctl);
	lan743x_csr_ग_लिखो(adapter, MAC_RX, macrx);
पूर्ण

अटल पूर्णांक lan743x_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);

	lan743x_pcidev_shutकरोwn(pdev);

	/* clear all wakes */
	lan743x_csr_ग_लिखो(adapter, MAC_WUCSR, 0);
	lan743x_csr_ग_लिखो(adapter, MAC_WUCSR2, 0);
	lan743x_csr_ग_लिखो(adapter, MAC_WK_SRC, 0xFFFFFFFF);

	अगर (adapter->wolopts)
		lan743x_pm_set_wol(adapter);

	/* Host sets PME_En, put D3hot */
	वापस pci_prepare_to_sleep(pdev);
पूर्ण

अटल पूर्णांक lan743x_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	ret = lan743x_hardware_init(adapter, pdev);
	अगर (ret) अणु
		netअगर_err(adapter, probe, adapter->netdev,
			  "lan743x_hardware_init returned %d\n", ret);
	पूर्ण

	/* खोलो netdev when netdev is at running state जबतक resume.
	 * For instance, it is true when प्रणाली wakesup after pm-suspend
	 * However, it is false when प्रणाली wakes up after suspend GUI menu
	 */
	अगर (netअगर_running(netdev))
		lan743x_netdev_खोलो(netdev);

	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops lan743x_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(lan743x_pm_suspend, lan743x_pm_resume)
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा pci_device_id lan743x_pcidev_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SMSC, PCI_DEVICE_ID_SMSC_LAN7430) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SMSC, PCI_DEVICE_ID_SMSC_LAN7431) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, lan743x_pcidev_tbl);

अटल काष्ठा pci_driver lan743x_pcidev_driver = अणु
	.name     = DRIVER_NAME,
	.id_table = lan743x_pcidev_tbl,
	.probe    = lan743x_pcidev_probe,
	.हटाओ   = lan743x_pcidev_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver.pm = &lan743x_pm_ops,
#पूर्ण_अगर
	.shutकरोwn = lan743x_pcidev_shutकरोwn,
पूर्ण;

module_pci_driver(lan743x_pcidev_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
