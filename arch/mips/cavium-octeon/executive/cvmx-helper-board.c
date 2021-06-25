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
 * Helper functions to असलtract board specअगरic data about
 * network ports from the rest of the cvmx-helper files.
 */

#समावेश <linux/bug.h>
#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-bootinfo.h>

#समावेश <यंत्र/octeon/cvmx-config.h>

#समावेश <यंत्र/octeon/cvmx-helper.h>
#समावेश <यंत्र/octeon/cvmx-helper-util.h>
#समावेश <यंत्र/octeon/cvmx-helper-board.h>

#समावेश <यंत्र/octeon/cvmx-gmxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-asxx-defs.h>

/**
 * Return the MII PHY address associated with the given IPD
 * port. A result of -1 means there isn't a MII capable PHY
 * connected to this port. On chips supporting multiple MII
 * busses the bus number is encoded in bits <15:8>.
 *
 * This function must be modअगरied क्रम every new Octeon board.
 * Internally it uses चयन statements based on the cvmx_sysinfo
 * data to determine board types and revisions. It replies on the
 * fact that every Octeon board receives a unique board type
 * क्रमागतeration from the bootloader.
 *
 * @ipd_port: Octeon IPD port to get the MII address क्रम.
 *
 * Returns MII PHY address and bus number or -1.
 */
पूर्णांक cvmx_helper_board_get_mii_address(पूर्णांक ipd_port)
अणु
	चयन (cvmx_sysinfo_get()->board_type) अणु
	हाल CVMX_BOARD_TYPE_SIM:
		/* Simulator करोesn't have MII */
		वापस -1;
	हाल CVMX_BOARD_TYPE_EBT3000:
	हाल CVMX_BOARD_TYPE_EBT5800:
	हाल CVMX_BOARD_TYPE_THUNDER:
	हाल CVMX_BOARD_TYPE_NICPRO2:
		/* Interface 0 is SPI4, पूर्णांकerface 1 is RGMII */
		अगर ((ipd_port >= 16) && (ipd_port < 20))
			वापस ipd_port - 16;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_KODAMA:
	हाल CVMX_BOARD_TYPE_EBH3100:
	हाल CVMX_BOARD_TYPE_HIKARI:
	हाल CVMX_BOARD_TYPE_CN3010_EVB_HS5:
	हाल CVMX_BOARD_TYPE_CN3005_EVB_HS5:
	हाल CVMX_BOARD_TYPE_CN3020_EVB_HS5:
		/*
		 * Port 0 is WAN connected to a PHY, Port 1 is GMII
		 * connected to a चयन
		 */
		अगर (ipd_port == 0)
			वापस 4;
		अन्यथा अगर (ipd_port == 1)
			वापस 9;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_NAC38:
		/* Board has 8 RGMII ports PHYs are 0-7 */
		अगर ((ipd_port >= 0) && (ipd_port < 4))
			वापस ipd_port;
		अन्यथा अगर ((ipd_port >= 16) && (ipd_port < 20))
			वापस ipd_port - 16 + 4;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_EBH3000:
		/* Board has dual SPI4 and no PHYs */
		वापस -1;
	हाल CVMX_BOARD_TYPE_EBH5200:
	हाल CVMX_BOARD_TYPE_EBH5201:
	हाल CVMX_BOARD_TYPE_EBT5200:
		/* Board has 2 management ports */
		अगर ((ipd_port >= CVMX_HELPER_BOARD_MGMT_IPD_PORT) &&
		    (ipd_port < (CVMX_HELPER_BOARD_MGMT_IPD_PORT + 2)))
			वापस ipd_port - CVMX_HELPER_BOARD_MGMT_IPD_PORT;
		/*
		 * Board has 4 SGMII ports. The PHYs start right after the MII
		 * ports MII0 = 0, MII1 = 1, SGMII = 2-5.
		 */
		अगर ((ipd_port >= 0) && (ipd_port < 4))
			वापस ipd_port + 2;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_EBH5600:
	हाल CVMX_BOARD_TYPE_EBH5601:
	हाल CVMX_BOARD_TYPE_EBH5610:
		/* Board has 1 management port */
		अगर (ipd_port == CVMX_HELPER_BOARD_MGMT_IPD_PORT)
			वापस 0;
		/*
		 * Board has 8 SGMII ports. 4 connect out, two connect
		 * to a चयन, and 2 loop to each other
		 */
		अगर ((ipd_port >= 0) && (ipd_port < 4))
			वापस ipd_port + 1;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_CUST_NB5:
		अगर (ipd_port == 2)
			वापस 4;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_NIC_XLE_4G:
		/* Board has 4 SGMII ports. connected QLM3(पूर्णांकerface 1) */
		अगर ((ipd_port >= 16) && (ipd_port < 20))
			वापस ipd_port - 16 + 1;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_NIC_XLE_10G:
	हाल CVMX_BOARD_TYPE_NIC10E:
		वापस -1;
	हाल CVMX_BOARD_TYPE_NIC4E:
		अगर (ipd_port >= 0 && ipd_port <= 3)
			वापस (ipd_port + 0x1f) & 0x1f;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_NIC2E:
		अगर (ipd_port >= 0 && ipd_port <= 1)
			वापस ipd_port + 1;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_BBGW_REF:
		/*
		 * No PHYs are connected to Octeon, everything is
		 * through चयन.
		 */
		वापस -1;

	हाल CVMX_BOARD_TYPE_CUST_WSX16:
		अगर (ipd_port >= 0 && ipd_port <= 3)
			वापस ipd_port;
		अन्यथा अगर (ipd_port >= 16 && ipd_port <= 19)
			वापस ipd_port - 16 + 4;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_UBNT_E100:
		अगर (ipd_port >= 0 && ipd_port <= 2)
			वापस 7 - ipd_port;
		अन्यथा
			वापस -1;
	हाल CVMX_BOARD_TYPE_KONTRON_S1901:
		अगर (ipd_port == CVMX_HELPER_BOARD_MGMT_IPD_PORT)
			वापस 1;
		अन्यथा
			वापस -1;

	पूर्ण

	/* Some unknown board. Somebody क्रमgot to update this function... */
	cvmx_dम_लिखो
	    ("cvmx_helper_board_get_mii_address: Unknown board type %d\n",
	     cvmx_sysinfo_get()->board_type);
	वापस -1;
पूर्ण

/**
 * This function is the board specअगरic method of determining an
 * ethernet ports link speed. Most Octeon boards have Marvell PHYs
 * and are handled by the fall through हाल. This function must be
 * updated क्रम boards that करोn't have the normal Marvell PHYs.
 *
 * This function must be modअगरied क्रम every new Octeon board.
 * Internally it uses चयन statements based on the cvmx_sysinfo
 * data to determine board types and revisions. It relies on the
 * fact that every Octeon board receives a unique board type
 * क्रमागतeration from the bootloader.
 *
 * @ipd_port: IPD input port associated with the port we want to get link
 *		   status क्रम.
 *
 * Returns The ports link status. If the link isn't fully resolved, this must
 *	   वापस zero.
 */
जोड़ cvmx_helper_link_info __cvmx_helper_board_link_get(पूर्णांक ipd_port)
अणु
	जोड़ cvmx_helper_link_info result;

	WARN(!octeon_is_simulation(),
	     "Using deprecated link status - please update your DT");

	/* Unless we fix it later, all links are शेषed to करोwn */
	result.u64 = 0;

	अगर (octeon_is_simulation()) अणु
		/* The simulator gives you a simulated 1Gbps full duplex link */
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 1000;
		वापस result;
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN3XXX)
		   || OCTEON_IS_MODEL(OCTEON_CN58XX)
		   || OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
		/*
		 * We करोn't have a PHY address, so attempt to use
		 * in-band status. It is really important that boards
		 * not supporting in-band status never get
		 * here. Reading broken in-band status tends to करो bad
		 * things
		 */
		जोड़ cvmx_gmxx_rxx_rx_inbnd inband_status;
		पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
		पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);
		inband_status.u64 =
		    cvmx_पढ़ो_csr(CVMX_GMXX_RXX_RX_INBND(index, पूर्णांकerface));

		result.s.link_up = inband_status.s.status;
		result.s.full_duplex = inband_status.s.duplex;
		चयन (inband_status.s.speed) अणु
		हाल 0: /* 10 Mbps */
			result.s.speed = 10;
			अवरोध;
		हाल 1: /* 100 Mbps */
			result.s.speed = 100;
			अवरोध;
		हाल 2: /* 1 Gbps */
			result.s.speed = 1000;
			अवरोध;
		हाल 3: /* Illegal */
			result.u64 = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We करोn't have a PHY address and we don't have
		 * in-band status. There is no way to determine the
		 * link speed. Return करोwn assuming this port isn't
		 * wired
		 */
		result.u64 = 0;
	पूर्ण

	/* If link is करोwn, वापस all fields as zero. */
	अगर (!result.s.link_up)
		result.u64 = 0;

	वापस result;
पूर्ण

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
पूर्णांक __cvmx_helper_board_पूर्णांकerface_probe(पूर्णांक पूर्णांकerface, पूर्णांक supported_ports)
अणु
	चयन (cvmx_sysinfo_get()->board_type) अणु
	हाल CVMX_BOARD_TYPE_CN3005_EVB_HS5:
		अगर (पूर्णांकerface == 0)
			वापस 2;
		अवरोध;
	हाल CVMX_BOARD_TYPE_BBGW_REF:
		अगर (पूर्णांकerface == 0)
			वापस 2;
		अवरोध;
	हाल CVMX_BOARD_TYPE_NIC_XLE_4G:
		अगर (पूर्णांकerface == 0)
			वापस 0;
		अवरोध;
		/* The 2nd पूर्णांकerface on the EBH5600 is connected to the Marvel चयन,
		   which we करोn't support. Disable ports connected to it */
	हाल CVMX_BOARD_TYPE_EBH5600:
		अगर (पूर्णांकerface == 1)
			वापस 0;
		अवरोध;
	पूर्ण
	वापस supported_ports;
पूर्ण

/**
 * Get the घड़ी type used क्रम the USB block based on board type.
 * Used by the USB code क्रम स्वतः configuration of घड़ी type.
 *
 * Return USB घड़ी type क्रमागतeration
 */
क्रमागत cvmx_helper_board_usb_घड़ी_प्रकारypes __cvmx_helper_board_usb_get_घड़ी_प्रकारype(व्योम)
अणु
	चयन (cvmx_sysinfo_get()->board_type) अणु
	हाल CVMX_BOARD_TYPE_BBGW_REF:
	हाल CVMX_BOARD_TYPE_LANAI2_A:
	हाल CVMX_BOARD_TYPE_LANAI2_U:
	हाल CVMX_BOARD_TYPE_LANAI2_G:
	हाल CVMX_BOARD_TYPE_NIC10E_66:
	हाल CVMX_BOARD_TYPE_UBNT_E100:
		वापस USB_CLOCK_TYPE_CRYSTAL_12;
	हाल CVMX_BOARD_TYPE_NIC10E:
		वापस USB_CLOCK_TYPE_REF_12;
	शेष:
		अवरोध;
	पूर्ण
	/* Most boards except NIC10e use a 12MHz crystal */
	अगर (OCTEON_IS_OCTEON2())
		वापस USB_CLOCK_TYPE_CRYSTAL_12;
	वापस USB_CLOCK_TYPE_REF_48;
पूर्ण
