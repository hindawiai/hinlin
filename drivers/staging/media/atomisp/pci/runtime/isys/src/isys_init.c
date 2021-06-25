<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "input_system.h"

#समावेश "ia_css_isys.h"
#समावेश "platform_support.h"

#अगर_घोषित ISP2401
#समावेश "isys_dma_public.h"	/* isys2401_dma_set_max_burst_size() */
#समावेश "isys_irq.h"
#पूर्ण_अगर

#अगर !defined(ISP2401)
input_प्रणाली_err_t ia_css_isys_init(व्योम)
अणु
	backend_channel_cfg_t backend_ch0;
	backend_channel_cfg_t backend_ch1;
	target_cfg2400_t targetB;
	target_cfg2400_t targetC;
	u32 acq_mem_region_size = 24;
	u32 acq_nof_mem_regions = 2;
	input_प्रणाली_err_t error = INPUT_SYSTEM_ERR_NO_ERROR;

	स_रखो(&backend_ch0, 0, माप(backend_channel_cfg_t));
	स_रखो(&backend_ch1, 0, माप(backend_channel_cfg_t));
	स_रखो(&targetB, 0, माप(targetB));
	स_रखो(&targetC, 0, माप(targetC));

	error = input_प्रणाली_configuration_reset();
	अगर (error != INPUT_SYSTEM_ERR_NO_ERROR)
		वापस error;

	error = input_प्रणाली_csi_xmem_channel_cfg(
		    0,			/*ch_id                 */
		    INPUT_SYSTEM_PORT_A,	/*port                  */
		    backend_ch0,		/*backend_ch            */
		    32,			/*mem_region_size       */
		    6,			/*nof_mem_regions       */
		    acq_mem_region_size,	/*acq_mem_region_size   */
		    acq_nof_mem_regions,	/*acq_nof_mem_regions   */
		    targetB,		/*target                */
		    3);			/*nof_xmem_buffers      */
	अगर (error != INPUT_SYSTEM_ERR_NO_ERROR)
		वापस error;

	error = input_प्रणाली_csi_xmem_channel_cfg(
		    1,			/*ch_id                 */
		    INPUT_SYSTEM_PORT_B,	/*port                  */
		    backend_ch0,		/*backend_ch            */
		    16,			/*mem_region_size       */
		    3,			/*nof_mem_regions       */
		    acq_mem_region_size,	/*acq_mem_region_size   */
		    acq_nof_mem_regions,	/*acq_nof_mem_regions   */
		    targetB,		/*target                */
		    3);			/*nof_xmem_buffers      */
	अगर (error != INPUT_SYSTEM_ERR_NO_ERROR)
		वापस error;

	error = input_प्रणाली_csi_xmem_channel_cfg(
		    2,			/*ch_id                 */
		    INPUT_SYSTEM_PORT_C,	/*port                  */
		    backend_ch1,		/*backend_ch            */
		    32,			/*mem_region_size       */
		    3,			/*nof_mem_regions       */
		    acq_mem_region_size,	/*acq_mem_region_size   */
		    acq_nof_mem_regions,	/*acq_nof_mem_regions   */
		    targetC,		/*target                */
		    2);			/*nof_xmem_buffers      */
	अगर (error != INPUT_SYSTEM_ERR_NO_ERROR)
		वापस error;

	error = input_प्रणाली_configuration_commit();

	वापस error;
पूर्ण
#या_अगर defined(ISP2401)
input_प्रणाली_err_t ia_css_isys_init(व्योम)
अणु
	ia_css_isys_csi_rx_lut_rmgr_init();
	ia_css_isys_ibuf_rmgr_init();
	ia_css_isys_dma_channel_rmgr_init();
	ia_css_isys_stream2mmio_sid_rmgr_init();

	isys2401_dma_set_max_burst_size(ISYS2401_DMA0_ID,
					1 /* Non Burst DMA transactions */);

	/* Enable 2401 input प्रणाली IRQ status क्रम driver to retrieve */
	isys_irqc_status_enable(ISYS_IRQ0_ID);
	isys_irqc_status_enable(ISYS_IRQ1_ID);
	isys_irqc_status_enable(ISYS_IRQ2_ID);

	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण
#पूर्ण_अगर

#अगर !defined(ISP2401)
व्योम ia_css_isys_uninit(व्योम)
अणु
पूर्ण
#या_अगर defined(ISP2401)
व्योम ia_css_isys_uninit(व्योम)
अणु
	ia_css_isys_csi_rx_lut_rmgr_uninit();
	ia_css_isys_ibuf_rmgr_uninit();
	ia_css_isys_dma_channel_rmgr_uninit();
	ia_css_isys_stream2mmio_sid_rmgr_uninit();
पूर्ण
#पूर्ण_अगर

