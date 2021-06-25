<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/delay.h>
#समावेश <linux/nospec.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_transport_internal.h"
#समावेश "adf_transport_access_macros.h"
#समावेश "adf_cfg.h"
#समावेश "adf_common_drv.h"

अटल अंतरभूत u32 adf_modulo(u32 data, u32 shअगरt)
अणु
	u32 भाग = data >> shअगरt;
	u32 mult = भाग << shअगरt;

	वापस data - mult;
पूर्ण

अटल अंतरभूत पूर्णांक adf_check_ring_alignment(u64 addr, u64 size)
अणु
	अगर (((size - 1) & addr) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक adf_verअगरy_ring_size(u32 msg_size, u32 msg_num)
अणु
	पूर्णांक i = ADF_MIN_RING_SIZE;

	क्रम (; i <= ADF_MAX_RING_SIZE; i++)
		अगर ((msg_size * msg_num) == ADF_SIZE_TO_RING_SIZE_IN_BYTES(i))
			वापस i;

	वापस ADF_DEFAULT_RING_SIZE;
पूर्ण

अटल पूर्णांक adf_reserve_ring(काष्ठा adf_etr_bank_data *bank, u32 ring)
अणु
	spin_lock(&bank->lock);
	अगर (bank->ring_mask & (1 << ring)) अणु
		spin_unlock(&bank->lock);
		वापस -EFAULT;
	पूर्ण
	bank->ring_mask |= (1 << ring);
	spin_unlock(&bank->lock);
	वापस 0;
पूर्ण

अटल व्योम adf_unreserve_ring(काष्ठा adf_etr_bank_data *bank, u32 ring)
अणु
	spin_lock(&bank->lock);
	bank->ring_mask &= ~(1 << ring);
	spin_unlock(&bank->lock);
पूर्ण

अटल व्योम adf_enable_ring_irq(काष्ठा adf_etr_bank_data *bank, u32 ring)
अणु
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(bank->accel_dev);

	spin_lock_bh(&bank->lock);
	bank->irq_mask |= (1 << ring);
	spin_unlock_bh(&bank->lock);
	csr_ops->ग_लिखो_csr_पूर्णांक_col_en(bank->csr_addr, bank->bank_number,
				      bank->irq_mask);
	csr_ops->ग_लिखो_csr_पूर्णांक_col_ctl(bank->csr_addr, bank->bank_number,
				       bank->irq_coalesc_समयr);
पूर्ण

अटल व्योम adf_disable_ring_irq(काष्ठा adf_etr_bank_data *bank, u32 ring)
अणु
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(bank->accel_dev);

	spin_lock_bh(&bank->lock);
	bank->irq_mask &= ~(1 << ring);
	spin_unlock_bh(&bank->lock);
	csr_ops->ग_लिखो_csr_पूर्णांक_col_en(bank->csr_addr, bank->bank_number,
				      bank->irq_mask);
पूर्ण

पूर्णांक adf_send_message(काष्ठा adf_etr_ring_data *ring, u32 *msg)
अणु
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(ring->bank->accel_dev);

	अगर (atomic_add_वापस(1, ring->inflights) >
	    ADF_MAX_INFLIGHTS(ring->ring_size, ring->msg_size)) अणु
		atomic_dec(ring->inflights);
		वापस -EAGAIN;
	पूर्ण
	spin_lock_bh(&ring->lock);
	स_नकल((व्योम *)((uपूर्णांकptr_t)ring->base_addr + ring->tail), msg,
	       ADF_MSG_SIZE_TO_BYTES(ring->msg_size));

	ring->tail = adf_modulo(ring->tail +
				ADF_MSG_SIZE_TO_BYTES(ring->msg_size),
				ADF_RING_SIZE_MODULO(ring->ring_size));
	csr_ops->ग_लिखो_csr_ring_tail(ring->bank->csr_addr,
				     ring->bank->bank_number, ring->ring_number,
				     ring->tail);
	spin_unlock_bh(&ring->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक adf_handle_response(काष्ठा adf_etr_ring_data *ring)
अणु
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(ring->bank->accel_dev);
	u32 msg_counter = 0;
	u32 *msg = (u32 *)((uपूर्णांकptr_t)ring->base_addr + ring->head);

	जबतक (*msg != ADF_RING_EMPTY_SIG) अणु
		ring->callback((u32 *)msg);
		atomic_dec(ring->inflights);
		*msg = ADF_RING_EMPTY_SIG;
		ring->head = adf_modulo(ring->head +
					ADF_MSG_SIZE_TO_BYTES(ring->msg_size),
					ADF_RING_SIZE_MODULO(ring->ring_size));
		msg_counter++;
		msg = (u32 *)((uपूर्णांकptr_t)ring->base_addr + ring->head);
	पूर्ण
	अगर (msg_counter > 0) अणु
		csr_ops->ग_लिखो_csr_ring_head(ring->bank->csr_addr,
					     ring->bank->bank_number,
					     ring->ring_number, ring->head);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adf_configure_tx_ring(काष्ठा adf_etr_ring_data *ring)
अणु
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(ring->bank->accel_dev);
	u32 ring_config = BUILD_RING_CONFIG(ring->ring_size);

	csr_ops->ग_लिखो_csr_ring_config(ring->bank->csr_addr,
				       ring->bank->bank_number,
				       ring->ring_number, ring_config);

पूर्ण

अटल व्योम adf_configure_rx_ring(काष्ठा adf_etr_ring_data *ring)
अणु
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(ring->bank->accel_dev);
	u32 ring_config =
			BUILD_RESP_RING_CONFIG(ring->ring_size,
					       ADF_RING_NEAR_WATERMARK_512,
					       ADF_RING_NEAR_WATERMARK_0);

	csr_ops->ग_लिखो_csr_ring_config(ring->bank->csr_addr,
				       ring->bank->bank_number,
				       ring->ring_number, ring_config);
पूर्ण

अटल पूर्णांक adf_init_ring(काष्ठा adf_etr_ring_data *ring)
अणु
	काष्ठा adf_etr_bank_data *bank = ring->bank;
	काष्ठा adf_accel_dev *accel_dev = bank->accel_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(accel_dev);
	u64 ring_base;
	u32 ring_size_bytes =
			ADF_SIZE_TO_RING_SIZE_IN_BYTES(ring->ring_size);

	ring_size_bytes = ADF_RING_SIZE_BYTES_MIN(ring_size_bytes);
	ring->base_addr = dma_alloc_coherent(&GET_DEV(accel_dev),
					     ring_size_bytes, &ring->dma_addr,
					     GFP_KERNEL);
	अगर (!ring->base_addr)
		वापस -ENOMEM;

	स_रखो(ring->base_addr, 0x7F, ring_size_bytes);
	/* The base_addr has to be aligned to the size of the buffer */
	अगर (adf_check_ring_alignment(ring->dma_addr, ring_size_bytes)) अणु
		dev_err(&GET_DEV(accel_dev), "Ring address not aligned\n");
		dma_मुक्त_coherent(&GET_DEV(accel_dev), ring_size_bytes,
				  ring->base_addr, ring->dma_addr);
		ring->base_addr = शून्य;
		वापस -EFAULT;
	पूर्ण

	अगर (hw_data->tx_rings_mask & (1 << ring->ring_number))
		adf_configure_tx_ring(ring);

	अन्यथा
		adf_configure_rx_ring(ring);

	ring_base = csr_ops->build_csr_ring_base_addr(ring->dma_addr,
						      ring->ring_size);

	csr_ops->ग_लिखो_csr_ring_base(ring->bank->csr_addr,
				     ring->bank->bank_number, ring->ring_number,
				     ring_base);
	spin_lock_init(&ring->lock);
	वापस 0;
पूर्ण

अटल व्योम adf_cleanup_ring(काष्ठा adf_etr_ring_data *ring)
अणु
	u32 ring_size_bytes =
			ADF_SIZE_TO_RING_SIZE_IN_BYTES(ring->ring_size);
	ring_size_bytes = ADF_RING_SIZE_BYTES_MIN(ring_size_bytes);

	अगर (ring->base_addr) अणु
		स_रखो(ring->base_addr, 0x7F, ring_size_bytes);
		dma_मुक्त_coherent(&GET_DEV(ring->bank->accel_dev),
				  ring_size_bytes, ring->base_addr,
				  ring->dma_addr);
	पूर्ण
पूर्ण

पूर्णांक adf_create_ring(काष्ठा adf_accel_dev *accel_dev, स्थिर अक्षर *section,
		    u32 bank_num, u32 num_msgs,
		    u32 msg_size, स्थिर अक्षर *ring_name,
		    adf_callback_fn callback, पूर्णांक poll_mode,
		    काष्ठा adf_etr_ring_data **ring_ptr)
अणु
	काष्ठा adf_etr_data *transport_data = accel_dev->transport;
	u8 num_rings_per_bank = GET_NUM_RINGS_PER_BANK(accel_dev);
	काष्ठा adf_etr_bank_data *bank;
	काष्ठा adf_etr_ring_data *ring;
	अक्षर val[ADF_CFG_MAX_VAL_LEN_IN_BYTES];
	u32 ring_num;
	पूर्णांक ret;

	अगर (bank_num >= GET_MAX_BANKS(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Invalid bank number\n");
		वापस -EFAULT;
	पूर्ण
	अगर (msg_size > ADF_MSG_SIZE_TO_BYTES(ADF_MAX_MSG_SIZE)) अणु
		dev_err(&GET_DEV(accel_dev), "Invalid msg size\n");
		वापस -EFAULT;
	पूर्ण
	अगर (ADF_MAX_INFLIGHTS(adf_verअगरy_ring_size(msg_size, num_msgs),
			      ADF_BYTES_TO_MSG_SIZE(msg_size)) < 2) अणु
		dev_err(&GET_DEV(accel_dev),
			"Invalid ring size for given msg size\n");
		वापस -EFAULT;
	पूर्ण
	अगर (adf_cfg_get_param_value(accel_dev, section, ring_name, val)) अणु
		dev_err(&GET_DEV(accel_dev), "Section %s, no such entry : %s\n",
			section, ring_name);
		वापस -EFAULT;
	पूर्ण
	अगर (kstrtouपूर्णांक(val, 10, &ring_num)) अणु
		dev_err(&GET_DEV(accel_dev), "Can't get ring number\n");
		वापस -EFAULT;
	पूर्ण
	अगर (ring_num >= num_rings_per_bank) अणु
		dev_err(&GET_DEV(accel_dev), "Invalid ring number\n");
		वापस -EFAULT;
	पूर्ण

	ring_num = array_index_nospec(ring_num, num_rings_per_bank);
	bank = &transport_data->banks[bank_num];
	अगर (adf_reserve_ring(bank, ring_num)) अणु
		dev_err(&GET_DEV(accel_dev), "Ring %d, %s already exists.\n",
			ring_num, ring_name);
		वापस -EFAULT;
	पूर्ण
	ring = &bank->rings[ring_num];
	ring->ring_number = ring_num;
	ring->bank = bank;
	ring->callback = callback;
	ring->msg_size = ADF_BYTES_TO_MSG_SIZE(msg_size);
	ring->ring_size = adf_verअगरy_ring_size(msg_size, num_msgs);
	ring->head = 0;
	ring->tail = 0;
	atomic_set(ring->inflights, 0);
	ret = adf_init_ring(ring);
	अगर (ret)
		जाओ err;

	/* Enable HW arbitration क्रम the given ring */
	adf_update_ring_arb(ring);

	अगर (adf_ring_debugfs_add(ring, ring_name)) अणु
		dev_err(&GET_DEV(accel_dev),
			"Couldn't add ring debugfs entry\n");
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	/* Enable पूर्णांकerrupts अगर needed */
	अगर (callback && (!poll_mode))
		adf_enable_ring_irq(bank, ring->ring_number);
	*ring_ptr = ring;
	वापस 0;
err:
	adf_cleanup_ring(ring);
	adf_unreserve_ring(bank, ring_num);
	adf_update_ring_arb(ring);
	वापस ret;
पूर्ण

व्योम adf_हटाओ_ring(काष्ठा adf_etr_ring_data *ring)
अणु
	काष्ठा adf_etr_bank_data *bank = ring->bank;
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(bank->accel_dev);

	/* Disable पूर्णांकerrupts क्रम the given ring */
	adf_disable_ring_irq(bank, ring->ring_number);

	/* Clear PCI config space */

	csr_ops->ग_लिखो_csr_ring_config(bank->csr_addr, bank->bank_number,
				       ring->ring_number, 0);
	csr_ops->ग_लिखो_csr_ring_base(bank->csr_addr, bank->bank_number,
				     ring->ring_number, 0);
	adf_ring_debugfs_rm(ring);
	adf_unreserve_ring(bank, ring->ring_number);
	/* Disable HW arbitration क्रम the given ring */
	adf_update_ring_arb(ring);
	adf_cleanup_ring(ring);
पूर्ण

अटल व्योम adf_ring_response_handler(काष्ठा adf_etr_bank_data *bank)
अणु
	काष्ठा adf_accel_dev *accel_dev = bank->accel_dev;
	u8 num_rings_per_bank = GET_NUM_RINGS_PER_BANK(accel_dev);
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(accel_dev);
	अचिन्हित दीर्घ empty_rings;
	पूर्णांक i;

	empty_rings = csr_ops->पढ़ो_csr_e_stat(bank->csr_addr,
					       bank->bank_number);
	empty_rings = ~empty_rings & bank->irq_mask;

	क्रम_each_set_bit(i, &empty_rings, num_rings_per_bank)
		adf_handle_response(&bank->rings[i]);
पूर्ण

व्योम adf_response_handler(uपूर्णांकptr_t bank_addr)
अणु
	काष्ठा adf_etr_bank_data *bank = (व्योम *)bank_addr;
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(bank->accel_dev);

	/* Handle all the responses and reenable IRQs */
	adf_ring_response_handler(bank);

	csr_ops->ग_लिखो_csr_पूर्णांक_flag_and_col(bank->csr_addr, bank->bank_number,
					    bank->irq_mask);
पूर्ण

अटल अंतरभूत पूर्णांक adf_get_cfg_पूर्णांक(काष्ठा adf_accel_dev *accel_dev,
				  स्थिर अक्षर *section, स्थिर अक्षर *क्रमmat,
				  u32 key, u32 *value)
अणु
	अक्षर key_buf[ADF_CFG_MAX_KEY_LEN_IN_BYTES];
	अक्षर val_buf[ADF_CFG_MAX_VAL_LEN_IN_BYTES];

	snम_लिखो(key_buf, ADF_CFG_MAX_KEY_LEN_IN_BYTES, क्रमmat, key);

	अगर (adf_cfg_get_param_value(accel_dev, section, key_buf, val_buf))
		वापस -EFAULT;

	अगर (kstrtouपूर्णांक(val_buf, 10, value))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम adf_get_coalesc_समयr(काष्ठा adf_etr_bank_data *bank,
				  स्थिर अक्षर *section,
				  u32 bank_num_in_accel)
अणु
	अगर (adf_get_cfg_पूर्णांक(bank->accel_dev, section,
			    ADF_ETRMGR_COALESCE_TIMER_FORMAT,
			    bank_num_in_accel, &bank->irq_coalesc_समयr))
		bank->irq_coalesc_समयr = ADF_COALESCING_DEF_TIME;

	अगर (ADF_COALESCING_MAX_TIME < bank->irq_coalesc_समयr ||
	    ADF_COALESCING_MIN_TIME > bank->irq_coalesc_समयr)
		bank->irq_coalesc_समयr = ADF_COALESCING_DEF_TIME;
पूर्ण

अटल पूर्णांक adf_init_bank(काष्ठा adf_accel_dev *accel_dev,
			 काष्ठा adf_etr_bank_data *bank,
			 u32 bank_num, व्योम __iomem *csr_addr)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u8 num_rings_per_bank = hw_data->num_rings_per_bank;
	काष्ठा adf_hw_csr_ops *csr_ops = &hw_data->csr_ops;
	u32 irq_mask = BIT(num_rings_per_bank) - 1;
	काष्ठा adf_etr_ring_data *ring;
	काष्ठा adf_etr_ring_data *tx_ring;
	u32 i, coalesc_enabled = 0;
	अचिन्हित दीर्घ ring_mask;
	पूर्णांक size;

	स_रखो(bank, 0, माप(*bank));
	bank->bank_number = bank_num;
	bank->csr_addr = csr_addr;
	bank->accel_dev = accel_dev;
	spin_lock_init(&bank->lock);

	/* Allocate the rings in the bank */
	size = num_rings_per_bank * माप(काष्ठा adf_etr_ring_data);
	bank->rings = kzalloc_node(size, GFP_KERNEL,
				   dev_to_node(&GET_DEV(accel_dev)));
	अगर (!bank->rings)
		वापस -ENOMEM;

	/* Enable IRQ coalescing always. This will allow to use
	 * the optimised flag and coalesc रेजिस्टर.
	 * If it is disabled in the config file just use min समय value */
	अगर ((adf_get_cfg_पूर्णांक(accel_dev, "Accelerator0",
			     ADF_ETRMGR_COALESCING_ENABLED_FORMAT, bank_num,
			     &coalesc_enabled) == 0) && coalesc_enabled)
		adf_get_coalesc_समयr(bank, "Accelerator0", bank_num);
	अन्यथा
		bank->irq_coalesc_समयr = ADF_COALESCING_MIN_TIME;

	क्रम (i = 0; i < num_rings_per_bank; i++) अणु
		csr_ops->ग_लिखो_csr_ring_config(csr_addr, bank_num, i, 0);
		csr_ops->ग_लिखो_csr_ring_base(csr_addr, bank_num, i, 0);

		ring = &bank->rings[i];
		अगर (hw_data->tx_rings_mask & (1 << i)) अणु
			ring->inflights =
				kzalloc_node(माप(atomic_t),
					     GFP_KERNEL,
					     dev_to_node(&GET_DEV(accel_dev)));
			अगर (!ring->inflights)
				जाओ err;
		पूर्ण अन्यथा अणु
			अगर (i < hw_data->tx_rx_gap) अणु
				dev_err(&GET_DEV(accel_dev),
					"Invalid tx rings mask config\n");
				जाओ err;
			पूर्ण
			tx_ring = &bank->rings[i - hw_data->tx_rx_gap];
			ring->inflights = tx_ring->inflights;
		पूर्ण
	पूर्ण
	अगर (adf_bank_debugfs_add(bank)) अणु
		dev_err(&GET_DEV(accel_dev),
			"Failed to add bank debugfs entry\n");
		जाओ err;
	पूर्ण

	csr_ops->ग_लिखो_csr_पूर्णांक_flag(csr_addr, bank_num, irq_mask);
	csr_ops->ग_लिखो_csr_पूर्णांक_srcsel(csr_addr, bank_num);

	वापस 0;
err:
	ring_mask = hw_data->tx_rings_mask;
	क्रम_each_set_bit(i, &ring_mask, num_rings_per_bank) अणु
		ring = &bank->rings[i];
		kमुक्त(ring->inflights);
		ring->inflights = शून्य;
	पूर्ण
	kमुक्त(bank->rings);
	वापस -ENOMEM;
पूर्ण

/**
 * adf_init_etr_data() - Initialize transport rings क्रम acceleration device
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function is the initializes the communications channels (rings) to the
 * acceleration device accel_dev.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_init_etr_data(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_etr_data *etr_data;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	व्योम __iomem *csr_addr;
	u32 size;
	u32 num_banks = 0;
	पूर्णांक i, ret;

	etr_data = kzalloc_node(माप(*etr_data), GFP_KERNEL,
				dev_to_node(&GET_DEV(accel_dev)));
	अगर (!etr_data)
		वापस -ENOMEM;

	num_banks = GET_MAX_BANKS(accel_dev);
	size = num_banks * माप(काष्ठा adf_etr_bank_data);
	etr_data->banks = kzalloc_node(size, GFP_KERNEL,
				       dev_to_node(&GET_DEV(accel_dev)));
	अगर (!etr_data->banks) अणु
		ret = -ENOMEM;
		जाओ err_bank;
	पूर्ण

	accel_dev->transport = etr_data;
	i = hw_data->get_etr_bar_id(hw_data);
	csr_addr = accel_dev->accel_pci_dev.pci_bars[i].virt_addr;

	/* accel_dev->debugfs_dir should always be non-शून्य here */
	etr_data->debug = debugfs_create_dir("transport",
					     accel_dev->debugfs_dir);

	क्रम (i = 0; i < num_banks; i++) अणु
		ret = adf_init_bank(accel_dev, &etr_data->banks[i], i,
				    csr_addr);
		अगर (ret)
			जाओ err_bank_all;
	पूर्ण

	वापस 0;

err_bank_all:
	debugfs_हटाओ(etr_data->debug);
	kमुक्त(etr_data->banks);
err_bank:
	kमुक्त(etr_data);
	accel_dev->transport = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adf_init_etr_data);

अटल व्योम cleanup_bank(काष्ठा adf_etr_bank_data *bank)
अणु
	काष्ठा adf_accel_dev *accel_dev = bank->accel_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u8 num_rings_per_bank = hw_data->num_rings_per_bank;
	u32 i;

	क्रम (i = 0; i < num_rings_per_bank; i++) अणु
		काष्ठा adf_etr_ring_data *ring = &bank->rings[i];

		अगर (bank->ring_mask & (1 << i))
			adf_cleanup_ring(ring);

		अगर (hw_data->tx_rings_mask & (1 << i))
			kमुक्त(ring->inflights);
	पूर्ण
	kमुक्त(bank->rings);
	adf_bank_debugfs_rm(bank);
	स_रखो(bank, 0, माप(*bank));
पूर्ण

अटल व्योम adf_cleanup_etr_handles(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_etr_data *etr_data = accel_dev->transport;
	u32 i, num_banks = GET_MAX_BANKS(accel_dev);

	क्रम (i = 0; i < num_banks; i++)
		cleanup_bank(&etr_data->banks[i]);
पूर्ण

/**
 * adf_cleanup_etr_data() - Clear transport rings क्रम acceleration device
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 *
 * Function is the clears the communications channels (rings) of the
 * acceleration device accel_dev.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम adf_cleanup_etr_data(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_etr_data *etr_data = accel_dev->transport;

	अगर (etr_data) अणु
		adf_cleanup_etr_handles(accel_dev);
		debugfs_हटाओ(etr_data->debug);
		kमुक्त(etr_data->banks->rings);
		kमुक्त(etr_data->banks);
		kमुक्त(etr_data);
		accel_dev->transport = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(adf_cleanup_etr_data);
