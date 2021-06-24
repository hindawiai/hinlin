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
 * Functions क्रम SGMII initialization, configuration,
 * and monitoring.
 *
 */
#अगर_अघोषित __CVMX_HELPER_SGMII_H__
#घोषणा __CVMX_HELPER_SGMII_H__

/**
 * Probe a SGMII पूर्णांकerface and determine the number of ports
 * connected to it. The SGMII पूर्णांकerface should still be करोwn after
 * this call.
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Number of ports on the पूर्णांकerface. Zero to disable.
 */
बाह्य पूर्णांक __cvmx_helper_sgmii_probe(पूर्णांक पूर्णांकerface);
बाह्य पूर्णांक __cvmx_helper_sgmii_क्रमागतerate(पूर्णांक पूर्णांकerface);

/**
 * Bringup and enable a SGMII पूर्णांकerface. After this call packet
 * I/O should be fully functional. This is called with IPD
 * enabled but PKO disabled.
 *
 * @पूर्णांकerface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
बाह्य पूर्णांक __cvmx_helper_sgmii_enable(पूर्णांक पूर्णांकerface);

/**
 * Return the link state of an IPD/PKO port as वापसed by
 * स्वतः negotiation. The result of this function may not match
 * Octeon's link config अगर स्वतः negotiation has changed since
 * the last call to cvmx_helper_link_set().
 *
 * @ipd_port: IPD/PKO port to query
 *
 * Returns Link state
 */
बाह्य जोड़ cvmx_helper_link_info __cvmx_helper_sgmii_link_get(पूर्णांक ipd_port);

/**
 * Configure an IPD/PKO port क्रम the specअगरied link state. This
 * function करोes not influence स्वतः negotiation at the PHY level.
 * The passed link state must always match the link state वापसed
 * by cvmx_helper_link_get().
 *
 * @ipd_port:  IPD/PKO port to configure
 * @link_info: The new link state
 *
 * Returns Zero on success, negative on failure
 */
बाह्य पूर्णांक __cvmx_helper_sgmii_link_set(पूर्णांक ipd_port,
					जोड़ cvmx_helper_link_info link_info);

#पूर्ण_अगर
