<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

/**
 * cvm_oct_get_buffer_ptr - convert packet data address to poपूर्णांकer
 * @packet_ptr: Packet data hardware address
 *
 * Returns Packet buffer poपूर्णांकer
 */
अटल अंतरभूत व्योम *cvm_oct_get_buffer_ptr(जोड़ cvmx_buf_ptr packet_ptr)
अणु
	वापस cvmx_phys_to_ptr(((packet_ptr.s.addr >> 7) - packet_ptr.s.back)
				<< 7);
पूर्ण

/**
 * INTERFACE - convert IPD port to logical पूर्णांकerface
 * @ipd_port: Port to check
 *
 * Returns Logical पूर्णांकerface
 */
अटल अंतरभूत पूर्णांक INTERFACE(पूर्णांक ipd_port)
अणु
	पूर्णांक पूर्णांकerface;

	अगर (ipd_port == CVMX_PIP_NUM_INPUT_PORTS)
		वापस 10;
	पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	अगर (पूर्णांकerface >= 0)
		वापस पूर्णांकerface;
	panic("Illegal ipd_port %d passed to %s\n", ipd_port, __func__);
पूर्ण

/**
 * INDEX - convert IPD/PKO port number to the port's पूर्णांकerface index
 * @ipd_port: Port to check
 *
 * Returns Index पूर्णांकo पूर्णांकerface port list
 */
अटल अंतरभूत पूर्णांक INDEX(पूर्णांक ipd_port)
अणु
	वापस cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);
पूर्ण
