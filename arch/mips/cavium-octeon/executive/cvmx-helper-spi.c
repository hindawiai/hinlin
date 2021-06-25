<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (C) 2003-2018 Cavium, Inc.
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
 * Functions क्रम SPI initialization, configuration,
 * and monitoring.
 */
#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>
#समावेश <यंत्र/octeon/cvmx-spi.h>
#समावेश <यंत्र/octeon/cvmx-helper.h>

#समावेश <यंत्र/octeon/cvmx-pip-defs.h>
#समावेश <यंत्र/octeon/cvmx-pko-defs.h>
#समावेश <यंत्र/octeon/cvmx-spxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-stxx-defs.h>

/*
 * CVMX_HELPER_SPI_TIMEOUT is used to determine how दीर्घ the SPI
 * initialization routines रुको क्रम SPI training. You can override the
 * value using executive-config.h अगर necessary.
 */
#अगर_अघोषित CVMX_HELPER_SPI_TIMEOUT
#घोषणा CVMX_HELPER_SPI_TIMEOUT 10
#पूर्ण_अगर

पूर्णांक __cvmx_helper_spi_क्रमागतerate(पूर्णांक पूर्णांकerface)
अणु
	अगर ((cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) &&
	    cvmx_spi4000_is_present(पूर्णांकerface)) अणु
		वापस 10;
	पूर्ण अन्यथा अणु
		वापस 16;
	पूर्ण
पूर्ण

/**
 * Probe a SPI पूर्णांकerface and determine the number of ports
 * connected to it. The SPI पूर्णांकerface should still be करोwn after
 * this call.
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Number of ports on the पूर्णांकerface. Zero to disable.
 */
पूर्णांक __cvmx_helper_spi_probe(पूर्णांक पूर्णांकerface)
अणु
	पूर्णांक num_ports = 0;

	अगर ((cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) &&
	    cvmx_spi4000_is_present(पूर्णांकerface)) अणु
		num_ports = 10;
	पूर्ण अन्यथा अणु
		जोड़ cvmx_pko_reg_crc_enable enable;
		num_ports = 16;
		/*
		 * Unlike the SPI4000, most SPI devices करोn't
		 * स्वतःmatically put on the L2 CRC. For everything
		 * except क्रम the SPI4000 have PKO append the L2 CRC
		 * to the packet.
		 */
		enable.u64 = cvmx_पढ़ो_csr(CVMX_PKO_REG_CRC_ENABLE);
		enable.s.enable |= 0xffff << (पूर्णांकerface * 16);
		cvmx_ग_लिखो_csr(CVMX_PKO_REG_CRC_ENABLE, enable.u64);
	पूर्ण
	__cvmx_helper_setup_gmx(पूर्णांकerface, num_ports);
	वापस num_ports;
पूर्ण

/**
 * Bringup and enable a SPI पूर्णांकerface. After this call packet I/O
 * should be fully functional. This is called with IPD enabled but
 * PKO disabled.
 *
 * @पूर्णांकerface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक __cvmx_helper_spi_enable(पूर्णांक पूर्णांकerface)
अणु
	/*
	 * Normally the ethernet L2 CRC is checked and stripped in the
	 * GMX block.  When you are using SPI, this isn' the हाल and
	 * IPD needs to check the L2 CRC.
	 */
	पूर्णांक num_ports = cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface);
	पूर्णांक ipd_port;
	क्रम (ipd_port = पूर्णांकerface * 16; ipd_port < पूर्णांकerface * 16 + num_ports;
	     ipd_port++) अणु
		जोड़ cvmx_pip_prt_cfgx port_config;
		port_config.u64 = cvmx_पढ़ो_csr(CVMX_PIP_PRT_CFGX(ipd_port));
		port_config.s.crc_en = 1;
		cvmx_ग_लिखो_csr(CVMX_PIP_PRT_CFGX(ipd_port), port_config.u64);
	पूर्ण

	अगर (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) अणु
		cvmx_spi_start_पूर्णांकerface(पूर्णांकerface, CVMX_SPI_MODE_DUPLEX,
					 CVMX_HELPER_SPI_TIMEOUT, num_ports);
		अगर (cvmx_spi4000_is_present(पूर्णांकerface))
			cvmx_spi4000_initialize(पूर्णांकerface);
	पूर्ण
	__cvmx_पूर्णांकerrupt_spxx_पूर्णांक_msk_enable(पूर्णांकerface);
	__cvmx_पूर्णांकerrupt_stxx_पूर्णांक_msk_enable(पूर्णांकerface);
	__cvmx_पूर्णांकerrupt_gmxx_enable(पूर्णांकerface);
	वापस 0;
पूर्ण

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
जोड़ cvmx_helper_link_info __cvmx_helper_spi_link_get(पूर्णांक ipd_port)
अणु
	जोड़ cvmx_helper_link_info result;
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);
	result.u64 = 0;

	अगर (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM) अणु
		/* The simulator gives you a simulated full duplex link */
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 10000;
	पूर्ण अन्यथा अगर (cvmx_spi4000_is_present(पूर्णांकerface)) अणु
		जोड़ cvmx_gmxx_rxx_rx_inbnd inband =
		    cvmx_spi4000_check_speed(पूर्णांकerface, index);
		result.s.link_up = inband.s.status;
		result.s.full_duplex = inband.s.duplex;
		चयन (inband.s.speed) अणु
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
			result.s.speed = 0;
			result.s.link_up = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* For generic SPI we can't determine the link, just वापस some
		   sane results */
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 10000;
	पूर्ण
	वापस result;
पूर्ण

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
पूर्णांक __cvmx_helper_spi_link_set(पूर्णांक ipd_port, जोड़ cvmx_helper_link_info link_info)
अणु
	/* Nothing to करो. If we have a SPI4000 then the setup was alपढ़ोy perक्रमmed
	   by cvmx_spi4000_check_speed(). If not then there isn't any link
	   info */
	वापस 0;
पूर्ण
