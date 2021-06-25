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
 * Functions क्रम RGMII/GMII/MII initialization, configuration,
 * and monitoring.
 *
 */
#अगर_अघोषित __CVMX_HELPER_RGMII_H__
#घोषणा __CVMX_HELPER_RGMII_H__

/**
 * Probe RGMII ports and determine the number present
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Number of RGMII/GMII/MII ports (0-4).
 */
बाह्य पूर्णांक __cvmx_helper_rgmii_probe(पूर्णांक पूर्णांकerface);
#घोषणा __cvmx_helper_rgmii_क्रमागतerate __cvmx_helper_rgmii_probe

/**
 * Put an RGMII पूर्णांकerface in loopback mode. Internal packets sent
 * out will be received back again on the same port. Externally
 * received packets will echo back out.
 *
 * @port:   IPD port number to loop.
 */
बाह्य व्योम cvmx_helper_rgmii_पूर्णांकernal_loopback(पूर्णांक port);

/**
 * Configure all of the ASX, GMX, and PKO रेजिस्टरs required
 * to get RGMII to function on the supplied पूर्णांकerface.
 *
 * @पूर्णांकerface: PKO Interface to configure (0 or 1)
 *
 * Returns Zero on success
 */
बाह्य पूर्णांक __cvmx_helper_rgmii_enable(पूर्णांक पूर्णांकerface);

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
बाह्य जोड़ cvmx_helper_link_info __cvmx_helper_rgmii_link_get(पूर्णांक ipd_port);

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
बाह्य पूर्णांक __cvmx_helper_rgmii_link_set(पूर्णांक ipd_port,
					जोड़ cvmx_helper_link_info link_info);

#पूर्ण_अगर
