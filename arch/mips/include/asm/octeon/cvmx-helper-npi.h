<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/**
 * @file
 *
 * Functions क्रम NPI initialization, configuration,
 * and monitoring.
 *
 */
#अगर_अघोषित __CVMX_HELPER_NPI_H__
#घोषणा __CVMX_HELPER_NPI_H__

/**
 * Probe a NPI पूर्णांकerface and determine the number of ports
 * connected to it. The NPI पूर्णांकerface should still be करोwn after
 * this call.
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Number of ports on the पूर्णांकerface. Zero to disable.
 */
बाह्य पूर्णांक __cvmx_helper_npi_probe(पूर्णांक पूर्णांकerface);
#घोषणा __cvmx_helper_npi_क्रमागतerate __cvmx_helper_npi_probe

/**
 * Bringup and enable a NPI पूर्णांकerface. After this call packet
 * I/O should be fully functional. This is called with IPD
 * enabled but PKO disabled.
 *
 * @पूर्णांकerface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
बाह्य पूर्णांक __cvmx_helper_npi_enable(पूर्णांक पूर्णांकerface);

#पूर्ण_अगर
