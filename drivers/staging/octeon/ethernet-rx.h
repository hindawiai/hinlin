<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

व्योम cvm_oct_poll_controller(काष्ठा net_device *dev);
व्योम cvm_oct_rx_initialize(व्योम);
व्योम cvm_oct_rx_shutकरोwn(व्योम);

अटल अंतरभूत व्योम cvm_oct_rx_refill_pool(पूर्णांक fill_threshold)
अणु
	पूर्णांक number_to_मुक्त;
	पूर्णांक num_मुक्तd;
	/* Refill the packet buffer pool */
	number_to_मुक्त =
		cvmx_fau_fetch_and_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE, 0);

	अगर (number_to_मुक्त > fill_threshold) अणु
		cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE,
				      -number_to_मुक्त);
		num_मुक्तd = cvm_oct_mem_fill_fpa(CVMX_FPA_PACKET_POOL,
						 CVMX_FPA_PACKET_POOL_SIZE,
						 number_to_मुक्त);
		अगर (num_मुक्तd != number_to_मुक्त) अणु
			cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE,
					      number_to_मुक्त - num_मुक्तd);
		पूर्ण
	पूर्ण
पूर्ण
