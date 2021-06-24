<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "adf_transport_internal.h"

#घोषणा ADF_ARB_NUM 4
#घोषणा ADF_ARB_REG_SIZE 0x4

#घोषणा WRITE_CSR_ARB_SARCONFIG(csr_addr, arb_offset, index, value) \
	ADF_CSR_WR(csr_addr, (arb_offset) + \
	(ADF_ARB_REG_SIZE * (index)), value)

#घोषणा WRITE_CSR_ARB_WT2SAM(csr_addr, arb_offset, wt_offset, index, value) \
	ADF_CSR_WR(csr_addr, ((arb_offset) + (wt_offset)) + \
	(ADF_ARB_REG_SIZE * (index)), value)

पूर्णांक adf_init_arb(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	व्योम __iomem *csr = accel_dev->transport->banks[0].csr_addr;
	अचिन्हित दीर्घ ae_mask = hw_data->ae_mask;
	u32 arb_off, wt_off, arb_cfg;
	स्थिर u32 *thd_2_arb_cfg;
	काष्ठा arb_info info;
	पूर्णांक arb, i;

	hw_data->get_arb_info(&info);
	arb_cfg = info.arb_cfg;
	arb_off = info.arb_offset;
	wt_off = info.wt2sam_offset;

	/* Service arb configured क्रम 32 bytes responses and
	 * ring flow control check enabled. */
	क्रम (arb = 0; arb < ADF_ARB_NUM; arb++)
		WRITE_CSR_ARB_SARCONFIG(csr, arb_off, arb, arb_cfg);

	/* Map worker thपढ़ोs to service arbiters */
	thd_2_arb_cfg = hw_data->get_arb_mapping();

	क्रम_each_set_bit(i, &ae_mask, hw_data->num_engines)
		WRITE_CSR_ARB_WT2SAM(csr, arb_off, wt_off, i, thd_2_arb_cfg[i]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_init_arb);

व्योम adf_update_ring_arb(काष्ठा adf_etr_ring_data *ring)
अणु
	काष्ठा adf_accel_dev *accel_dev = ring->bank->accel_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(accel_dev);
	u32 tx_ring_mask = hw_data->tx_rings_mask;
	u32 shअगरt = hw_data->tx_rx_gap;
	u32 arben, arben_tx, arben_rx;
	u32 rx_ring_mask;

	/*
	 * Enable arbitration on a ring only अगर the TX half of the ring mask
	 * matches the RX part. This results in ग_लिखोs to CSR on both TX and
	 * RX update - only one is necessary, but both are करोne क्रम
	 * simplicity.
	 */
	rx_ring_mask = tx_ring_mask << shअगरt;
	arben_tx = (ring->bank->ring_mask & tx_ring_mask) >> 0;
	arben_rx = (ring->bank->ring_mask & rx_ring_mask) >> shअगरt;
	arben = arben_tx & arben_rx;

	csr_ops->ग_लिखो_csr_ring_srv_arb_en(ring->bank->csr_addr,
					   ring->bank->bank_number, arben);
पूर्ण

व्योम adf_निकास_arb(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(accel_dev);
	u32 arb_off, wt_off;
	काष्ठा arb_info info;
	व्योम __iomem *csr;
	अचिन्हित पूर्णांक i;

	hw_data->get_arb_info(&info);
	arb_off = info.arb_offset;
	wt_off = info.wt2sam_offset;

	अगर (!accel_dev->transport)
		वापस;

	csr = accel_dev->transport->banks[0].csr_addr;

	hw_data->get_arb_info(&info);

	/* Reset arbiter configuration */
	क्रम (i = 0; i < ADF_ARB_NUM; i++)
		WRITE_CSR_ARB_SARCONFIG(csr, arb_off, i, 0);

	/* Unmap worker thपढ़ोs to service arbiters */
	क्रम (i = 0; i < hw_data->num_engines; i++)
		WRITE_CSR_ARB_WT2SAM(csr, arb_off, wt_off, i, 0);

	/* Disable arbitration on all rings */
	क्रम (i = 0; i < GET_MAX_BANKS(accel_dev); i++)
		csr_ops->ग_लिखो_csr_ring_srv_arb_en(csr, i, 0);
पूर्ण
EXPORT_SYMBOL_GPL(adf_निकास_arb);
