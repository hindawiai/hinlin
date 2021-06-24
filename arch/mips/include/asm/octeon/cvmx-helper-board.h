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
 *
 * Helper functions to असलtract board specअगरic data about
 * network ports from the rest of the cvmx-helper files.
 *
 */
#अगर_अघोषित __CVMX_HELPER_BOARD_H__
#घोषणा __CVMX_HELPER_BOARD_H__

#समावेश <यंत्र/octeon/cvmx-helper.h>

क्रमागत cvmx_helper_board_usb_घड़ी_प्रकारypes अणु
	USB_CLOCK_TYPE_REF_12,
	USB_CLOCK_TYPE_REF_24,
	USB_CLOCK_TYPE_REF_48,
	USB_CLOCK_TYPE_CRYSTAL_12,
पूर्ण;

प्रकार क्रमागत अणु
	set_phy_link_flags_स्वतःneg = 0x1,
	set_phy_link_flags_flow_control_करोnt_touch = 0x0 << 1,
	set_phy_link_flags_flow_control_enable = 0x1 << 1,
	set_phy_link_flags_flow_control_disable = 0x2 << 1,
	set_phy_link_flags_flow_control_mask = 0x3 << 1,	/* Mask क्रम 2 bit wide flow control field */
पूर्ण cvmx_helper_board_set_phy_link_flags_types_t;

/*
 * Fake IPD port, the RGMII/MII पूर्णांकerface may use dअगरferent PHY, use
 * this macro to वापस appropriate MIX address to पढ़ो the PHY.
 */
#घोषणा CVMX_HELPER_BOARD_MGMT_IPD_PORT	    -10

/**
 * Return the MII PHY address associated with the given IPD
 * port. A result of -1 means there isn't a MII capable PHY
 * connected to this port. On chips supporting multiple MII
 * busses the bus number is encoded in bits <15:8>.
 *
 * This function must be modअगरed क्रम every new Octeon board.
 * Internally it uses चयन statements based on the cvmx_sysinfo
 * data to determine board types and revisions. It relys on the
 * fact that every Octeon board receives a unique board type
 * क्रमागतeration from the bootloader.
 *
 * @ipd_port: Octeon IPD port to get the MII address क्रम.
 *
 * Returns MII PHY address and bus number or -1.
 */
बाह्य पूर्णांक cvmx_helper_board_get_mii_address(पूर्णांक ipd_port);

/**
 * This function is the board specअगरic method of determining an
 * ethernet ports link speed. Most Octeon boards have Marvell PHYs
 * and are handled by the fall through हाल. This function must be
 * updated क्रम boards that करोn't have the normal Marvell PHYs.
 *
 * This function must be modअगरed क्रम every new Octeon board.
 * Internally it uses चयन statements based on the cvmx_sysinfo
 * data to determine board types and revisions. It relys on the
 * fact that every Octeon board receives a unique board type
 * क्रमागतeration from the bootloader.
 *
 * @ipd_port: IPD input port associated with the port we want to get link
 *		   status क्रम.
 *
 * Returns The ports link status. If the link isn't fully resolved, this must
 *	   वापस zero.
 */
बाह्य जोड़ cvmx_helper_link_info __cvmx_helper_board_link_get(पूर्णांक ipd_port);

/**
 * This function is called by cvmx_helper_पूर्णांकerface_probe() after it
 * determines the number of ports Octeon can support on a specअगरic
 * पूर्णांकerface. This function is the per board location to override
 * this value. It is called with the number of ports Octeon might
 * support and should वापस the number of actual ports on the
 * board.
 *
 * This function must be modअगरed क्रम every new Octeon board.
 * Internally it uses चयन statements based on the cvmx_sysinfo
 * data to determine board types and revisions. It relys on the
 * fact that every Octeon board receives a unique board type
 * क्रमागतeration from the bootloader.
 *
 * @पूर्णांकerface: Interface to probe
 * @supported_ports:
 *		    Number of ports Octeon supports.
 *
 * Returns Number of ports the actual board supports. Many बार this will
 *	   simple be "support_ports".
 */
बाह्य पूर्णांक __cvmx_helper_board_पूर्णांकerface_probe(पूर्णांक पूर्णांकerface,
					       पूर्णांक supported_ports);

क्रमागत cvmx_helper_board_usb_घड़ी_प्रकारypes __cvmx_helper_board_usb_get_घड़ी_प्रकारype(व्योम);

#पूर्ण_अगर /* __CVMX_HELPER_BOARD_H__ */
