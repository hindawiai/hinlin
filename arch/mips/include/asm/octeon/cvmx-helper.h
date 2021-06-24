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

/*
 *
 * Helper functions क्रम common, but complicated tasks.
 *
 */

#अगर_अघोषित __CVMX_HELPER_H__
#घोषणा __CVMX_HELPER_H__

#समावेश <यंत्र/octeon/cvmx-config.h>
#समावेश <यंत्र/octeon/cvmx-fpa.h>
#समावेश <यंत्र/octeon/cvmx-wqe.h>

प्रकार क्रमागत अणु
	CVMX_HELPER_INTERFACE_MODE_DISABLED,
	CVMX_HELPER_INTERFACE_MODE_RGMII,
	CVMX_HELPER_INTERFACE_MODE_GMII,
	CVMX_HELPER_INTERFACE_MODE_SPI,
	CVMX_HELPER_INTERFACE_MODE_PCIE,
	CVMX_HELPER_INTERFACE_MODE_XAUI,
	CVMX_HELPER_INTERFACE_MODE_SGMII,
	CVMX_HELPER_INTERFACE_MODE_PICMG,
	CVMX_HELPER_INTERFACE_MODE_NPI,
	CVMX_HELPER_INTERFACE_MODE_LOOP,
पूर्ण cvmx_helper_पूर्णांकerface_mode_t;

जोड़ cvmx_helper_link_info अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t link_up:1;	    /**< Is the physical link up? */
		uपूर्णांक64_t full_duplex:1;	    /**< 1 अगर the link is full duplex */
		uपूर्णांक64_t speed:18;	    /**< Speed of the link in Mbps */
	पूर्ण s;
पूर्ण;

#समावेश <यंत्र/octeon/cvmx-helper-errata.h>
#समावेश <यंत्र/octeon/cvmx-helper-loop.h>
#समावेश <यंत्र/octeon/cvmx-helper-npi.h>
#समावेश <यंत्र/octeon/cvmx-helper-rgmii.h>
#समावेश <यंत्र/octeon/cvmx-helper-sgmii.h>
#समावेश <यंत्र/octeon/cvmx-helper-spi.h>
#समावेश <यंत्र/octeon/cvmx-helper-util.h>
#समावेश <यंत्र/octeon/cvmx-helper-xaui.h>

/**
 * This function enables the IPD and also enables the packet पूर्णांकerfaces.
 * The packet पूर्णांकerfaces (RGMII and SPI) must be enabled after the
 * IPD.	 This should be called by the user program after any additional
 * IPD configuration changes are made अगर CVMX_HELPER_ENABLE_IPD
 * is not set in the executive-config.h file.
 *
 * Returns 0 on success
 *	   -1 on failure
 */
बाह्य पूर्णांक cvmx_helper_ipd_and_packet_input_enable(व्योम);

/**
 * Initialize the PIP, IPD, and PKO hardware to support
 * simple priority based queues क्रम the ethernet ports. Each
 * port is configured with a number of priority queues based
 * on CVMX_PKO_QUEUES_PER_PORT_* where each queue is lower
 * priority than the previous.
 *
 * Returns Zero on success, non-zero on failure
 */
बाह्य पूर्णांक cvmx_helper_initialize_packet_io_global(व्योम);

/**
 * Does core local initialization क्रम packet io
 *
 * Returns Zero on success, non-zero on failure
 */
बाह्य पूर्णांक cvmx_helper_initialize_packet_io_local(व्योम);

/**
 * Returns the number of ports on the given पूर्णांकerface.
 * The पूर्णांकerface must be initialized beक्रमe the port count
 * can be वापसed.
 *
 * @पूर्णांकerface: Which पूर्णांकerface to वापस port count क्रम.
 *
 * Returns Port count क्रम पूर्णांकerface
 *	   -1 क्रम uninitialized पूर्णांकerface
 */
बाह्य पूर्णांक cvmx_helper_ports_on_पूर्णांकerface(पूर्णांक पूर्णांकerface);

/**
 * Return the number of पूर्णांकerfaces the chip has. Each पूर्णांकerface
 * may have multiple ports. Most chips support two पूर्णांकerfaces,
 * but the CNX0XX and CNX1XX are exceptions. These only support
 * one पूर्णांकerface.
 *
 * Returns Number of पूर्णांकerfaces on chip
 */
बाह्य पूर्णांक cvmx_helper_get_number_of_पूर्णांकerfaces(व्योम);

/**
 * Get the operating mode of an पूर्णांकerface. Depending on the Octeon
 * chip and configuration, this function वापसs an क्रमागतeration
 * of the type of packet I/O supported by an पूर्णांकerface.
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Mode of the पूर्णांकerface. Unknown or unsupported पूर्णांकerfaces वापस
 *	   DISABLED.
 */
बाह्य cvmx_helper_पूर्णांकerface_mode_t cvmx_helper_पूर्णांकerface_get_mode(पूर्णांक
								   पूर्णांकerface);

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
बाह्य जोड़ cvmx_helper_link_info cvmx_helper_link_get(पूर्णांक ipd_port);

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
बाह्य पूर्णांक cvmx_helper_link_set(पूर्णांक ipd_port,
				जोड़ cvmx_helper_link_info link_info);

/**
 * This function probes an पूर्णांकerface to determine the actual
 * number of hardware ports connected to it. It करोesn't setup the
 * ports or enable them. The मुख्य goal here is to set the global
 * पूर्णांकerface_port_count[पूर्णांकerface] correctly. Hardware setup of the
 * ports will be perक्रमmed later.
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Zero on success, negative on failure
 */
बाह्य पूर्णांक cvmx_helper_पूर्णांकerface_probe(पूर्णांक पूर्णांकerface);
बाह्य पूर्णांक cvmx_helper_पूर्णांकerface_क्रमागतerate(पूर्णांक पूर्णांकerface);

#पूर्ण_अगर /* __CVMX_HELPER_H__ */
