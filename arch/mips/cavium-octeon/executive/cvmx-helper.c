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
#समावेश <linux/bug.h>
#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>

#समावेश <यंत्र/octeon/cvmx-fpa.h>
#समावेश <यंत्र/octeon/cvmx-pip.h>
#समावेश <यंत्र/octeon/cvmx-pko.h>
#समावेश <यंत्र/octeon/cvmx-ipd.h>
#समावेश <यंत्र/octeon/cvmx-spi.h>
#समावेश <यंत्र/octeon/cvmx-helper.h>
#समावेश <यंत्र/octeon/cvmx-helper-board.h>

#समावेश <यंत्र/octeon/cvmx-pip-defs.h>
#समावेश <यंत्र/octeon/cvmx-asxx-defs.h>

/* Port count per पूर्णांकerface */
अटल पूर्णांक पूर्णांकerface_port_count[9];

/**
 * Return the number of पूर्णांकerfaces the chip has. Each पूर्णांकerface
 * may have multiple ports. Most chips support two पूर्णांकerfaces,
 * but the CNX0XX and CNX1XX are exceptions. These only support
 * one पूर्णांकerface.
 *
 * Returns Number of पूर्णांकerfaces on chip
 */
पूर्णांक cvmx_helper_get_number_of_पूर्णांकerfaces(व्योम)
अणु
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		वापस 9;
	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN52XX))
		वापस 4;
	अगर (OCTEON_IS_MODEL(OCTEON_CN7XXX))
		वापस 5;
	अन्यथा
		वापस 3;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_get_number_of_पूर्णांकerfaces);

/**
 * Return the number of ports on an पूर्णांकerface. Depending on the
 * chip and configuration, this can be 1-16. A value of 0
 * specअगरies that the पूर्णांकerface करोesn't exist or isn't usable.
 *
 * @पूर्णांकerface: Interface to get the port count क्रम
 *
 * Returns Number of ports on पूर्णांकerface. Can be Zero.
 */
पूर्णांक cvmx_helper_ports_on_पूर्णांकerface(पूर्णांक पूर्णांकerface)
अणु
	वापस पूर्णांकerface_port_count[पूर्णांकerface];
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_ports_on_पूर्णांकerface);

/**
 * @INTERNAL
 * Return पूर्णांकerface mode क्रम CN68xx.
 */
अटल cvmx_helper_पूर्णांकerface_mode_t __cvmx_get_mode_cn68xx(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_mio_qlmx_cfg qlm_cfg;
	चयन (पूर्णांकerface) अणु
	हाल 0:
		qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(0));
		/* QLM is disabled when QLM SPD is 15. */
		अगर (qlm_cfg.s.qlm_spd == 15)
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

		अगर (qlm_cfg.s.qlm_cfg == 2)
			वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
		अन्यथा अगर (qlm_cfg.s.qlm_cfg == 3)
			वापस CVMX_HELPER_INTERFACE_MODE_XAUI;
		अन्यथा
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	हाल 2:
	हाल 3:
	हाल 4:
		qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(पूर्णांकerface));
		/* QLM is disabled when QLM SPD is 15. */
		अगर (qlm_cfg.s.qlm_spd == 15)
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

		अगर (qlm_cfg.s.qlm_cfg == 2)
			वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
		अन्यथा अगर (qlm_cfg.s.qlm_cfg == 3)
			वापस CVMX_HELPER_INTERFACE_MODE_XAUI;
		अन्यथा
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	हाल 7:
		qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(3));
		/* QLM is disabled when QLM SPD is 15. */
		अगर (qlm_cfg.s.qlm_spd == 15) अणु
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
		पूर्ण अन्यथा अगर (qlm_cfg.s.qlm_cfg != 0) अणु
			qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(1));
			अगर (qlm_cfg.s.qlm_cfg != 0)
				वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
		पूर्ण
		वापस CVMX_HELPER_INTERFACE_MODE_NPI;
	हाल 8:
		वापस CVMX_HELPER_INTERFACE_MODE_LOOP;
	शेष:
		वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	पूर्ण
पूर्ण

/**
 * @INTERNAL
 * Return पूर्णांकerface mode क्रम an Octeon II
 */
अटल cvmx_helper_पूर्णांकerface_mode_t __cvmx_get_mode_octeon2(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_gmxx_inf_mode mode;

	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		वापस __cvmx_get_mode_cn68xx(पूर्णांकerface);

	अगर (पूर्णांकerface == 2)
		वापस CVMX_HELPER_INTERFACE_MODE_NPI;

	अगर (पूर्णांकerface == 3)
		वापस CVMX_HELPER_INTERFACE_MODE_LOOP;

	/* Only present in CN63XX & CN66XX Octeon model */
	अगर ((OCTEON_IS_MODEL(OCTEON_CN63XX) &&
	     (पूर्णांकerface == 4 || पूर्णांकerface == 5)) ||
	    (OCTEON_IS_MODEL(OCTEON_CN66XX) &&
	     पूर्णांकerface >= 4 && पूर्णांकerface <= 7)) अणु
		वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN66XX)) अणु
		जोड़ cvmx_mio_qlmx_cfg mio_qlm_cfg;

		/* QLM2 is SGMII0 and QLM1 is SGMII1 */
		अगर (पूर्णांकerface == 0)
			mio_qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(2));
		अन्यथा अगर (पूर्णांकerface == 1)
			mio_qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(1));
		अन्यथा
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

		अगर (mio_qlm_cfg.s.qlm_spd == 15)
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

		अगर (mio_qlm_cfg.s.qlm_cfg == 9)
			वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
		अन्यथा अगर (mio_qlm_cfg.s.qlm_cfg == 11)
			वापस CVMX_HELPER_INTERFACE_MODE_XAUI;
		अन्यथा
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN61XX)) अणु
		जोड़ cvmx_mio_qlmx_cfg qlm_cfg;

		अगर (पूर्णांकerface == 0) अणु
			qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(2));
			अगर (qlm_cfg.s.qlm_cfg == 2)
				वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
			अन्यथा अगर (qlm_cfg.s.qlm_cfg == 3)
				वापस CVMX_HELPER_INTERFACE_MODE_XAUI;
			अन्यथा
				वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
		पूर्ण अन्यथा अगर (पूर्णांकerface == 1) अणु
			qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(0));
			अगर (qlm_cfg.s.qlm_cfg == 2)
				वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
			अन्यथा अगर (qlm_cfg.s.qlm_cfg == 3)
				वापस CVMX_HELPER_INTERFACE_MODE_XAUI;
			अन्यथा
				वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
		पूर्ण
	पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CNF71XX)) अणु
		अगर (पूर्णांकerface == 0) अणु
			जोड़ cvmx_mio_qlmx_cfg qlm_cfg;
			qlm_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(0));
			अगर (qlm_cfg.s.qlm_cfg == 2)
				वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
		पूर्ण
		वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	पूर्ण

	अगर (पूर्णांकerface == 1 && OCTEON_IS_MODEL(OCTEON_CN63XX))
		वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

	mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));

	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
		चयन (mode.cn61xx.mode) अणु
		हाल 0:
			वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
		हाल 1:
			वापस CVMX_HELPER_INTERFACE_MODE_XAUI;
		शेष:
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!mode.s.en)
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

		अगर (mode.s.type)
			वापस CVMX_HELPER_INTERFACE_MODE_GMII;
		अन्यथा
			वापस CVMX_HELPER_INTERFACE_MODE_RGMII;
	पूर्ण
पूर्ण

/**
 * @INTERNAL
 * Return पूर्णांकerface mode क्रम CN7XXX.
 */
अटल cvmx_helper_पूर्णांकerface_mode_t __cvmx_get_mode_cn7xxx(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_gmxx_inf_mode mode;

	mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));

	चयन (पूर्णांकerface) अणु
	हाल 0:
	हाल 1:
		चयन (mode.cn68xx.mode) अणु
		हाल 0:
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
		हाल 1:
		हाल 2:
			वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
		हाल 3:
			वापस CVMX_HELPER_INTERFACE_MODE_XAUI;
		शेष:
			वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
		पूर्ण
	हाल 2:
		वापस CVMX_HELPER_INTERFACE_MODE_NPI;
	हाल 3:
		वापस CVMX_HELPER_INTERFACE_MODE_LOOP;
	हाल 4:
		/* TODO: Implement support क्रम AGL (RGMII). */
		वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	शेष:
		वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	पूर्ण
पूर्ण

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
cvmx_helper_पूर्णांकerface_mode_t cvmx_helper_पूर्णांकerface_get_mode(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_gmxx_inf_mode mode;

	अगर (पूर्णांकerface < 0 ||
	    पूर्णांकerface >= cvmx_helper_get_number_of_पूर्णांकerfaces())
		वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

	/*
	 * OCTEON III models
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN7XXX))
		वापस __cvmx_get_mode_cn7xxx(पूर्णांकerface);

	/*
	 * Octeon II models
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF71XX))
		वापस __cvmx_get_mode_octeon2(पूर्णांकerface);

	/*
	 * Octeon and Octeon Plus models
	 */
	अगर (पूर्णांकerface == 2)
		वापस CVMX_HELPER_INTERFACE_MODE_NPI;

	अगर (पूर्णांकerface == 3) अणु
		अगर (OCTEON_IS_MODEL(OCTEON_CN56XX)
		    || OCTEON_IS_MODEL(OCTEON_CN52XX))
			वापस CVMX_HELPER_INTERFACE_MODE_LOOP;
		अन्यथा
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
	पूर्ण

	/* Interface 1 is always disabled on CN31XX and CN30XX */
	अगर ((पूर्णांकerface == 1)
	    && (OCTEON_IS_MODEL(OCTEON_CN31XX) || OCTEON_IS_MODEL(OCTEON_CN30XX)
		|| OCTEON_IS_MODEL(OCTEON_CN50XX)
		|| OCTEON_IS_MODEL(OCTEON_CN52XX)))
		वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

	mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));

	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
		चयन (mode.cn52xx.mode) अणु
		हाल 0:
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
		हाल 1:
			वापस CVMX_HELPER_INTERFACE_MODE_XAUI;
		हाल 2:
			वापस CVMX_HELPER_INTERFACE_MODE_SGMII;
		हाल 3:
			वापस CVMX_HELPER_INTERFACE_MODE_PICMG;
		शेष:
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!mode.s.en)
			वापस CVMX_HELPER_INTERFACE_MODE_DISABLED;

		अगर (mode.s.type) अणु
			अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)
			    || OCTEON_IS_MODEL(OCTEON_CN58XX))
				वापस CVMX_HELPER_INTERFACE_MODE_SPI;
			अन्यथा
				वापस CVMX_HELPER_INTERFACE_MODE_GMII;
		पूर्ण अन्यथा
			वापस CVMX_HELPER_INTERFACE_MODE_RGMII;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_पूर्णांकerface_get_mode);

/**
 * Configure the IPD/PIP tagging and QoS options क्रम a specअगरic
 * port. This function determines the POW work queue entry
 * contents क्रम a port. The setup perक्रमmed here is controlled by
 * the defines in executive-config.h.
 *
 * @ipd_port: Port to configure. This follows the IPD numbering, not the
 *		   per पूर्णांकerface numbering
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_port_setup_ipd(पूर्णांक ipd_port)
अणु
	जोड़ cvmx_pip_prt_cfgx port_config;
	जोड़ cvmx_pip_prt_tagx tag_config;

	port_config.u64 = cvmx_पढ़ो_csr(CVMX_PIP_PRT_CFGX(ipd_port));
	tag_config.u64 = cvmx_पढ़ो_csr(CVMX_PIP_PRT_TAGX(ipd_port));

	/* Have each port go to a dअगरferent POW queue */
	port_config.s.qos = ipd_port & 0x7;

	/* Process the headers and place the IP header in the work queue */
	port_config.s.mode = CVMX_HELPER_INPUT_PORT_SKIP_MODE;

	tag_config.s.ip6_src_flag = CVMX_HELPER_INPUT_TAG_IPV6_SRC_IP;
	tag_config.s.ip6_dst_flag = CVMX_HELPER_INPUT_TAG_IPV6_DST_IP;
	tag_config.s.ip6_sprt_flag = CVMX_HELPER_INPUT_TAG_IPV6_SRC_PORT;
	tag_config.s.ip6_dprt_flag = CVMX_HELPER_INPUT_TAG_IPV6_DST_PORT;
	tag_config.s.ip6_nxth_flag = CVMX_HELPER_INPUT_TAG_IPV6_NEXT_HEADER;
	tag_config.s.ip4_src_flag = CVMX_HELPER_INPUT_TAG_IPV4_SRC_IP;
	tag_config.s.ip4_dst_flag = CVMX_HELPER_INPUT_TAG_IPV4_DST_IP;
	tag_config.s.ip4_sprt_flag = CVMX_HELPER_INPUT_TAG_IPV4_SRC_PORT;
	tag_config.s.ip4_dprt_flag = CVMX_HELPER_INPUT_TAG_IPV4_DST_PORT;
	tag_config.s.ip4_pctl_flag = CVMX_HELPER_INPUT_TAG_IPV4_PROTOCOL;
	tag_config.s.inc_prt_flag = CVMX_HELPER_INPUT_TAG_INPUT_PORT;
	tag_config.s.tcp6_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	tag_config.s.tcp4_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	tag_config.s.ip6_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	tag_config.s.ip4_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	tag_config.s.non_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	/* Put all packets in group 0. Other groups can be used by the app */
	tag_config.s.grp = 0;

	cvmx_pip_config_port(ipd_port, port_config, tag_config);

	वापस 0;
पूर्ण

/**
 * This function sets the पूर्णांकerface_port_count[पूर्णांकerface] correctly,
 * without modअगरying any hardware configuration.  Hardware setup of
 * the ports will be perक्रमmed later.
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक cvmx_helper_पूर्णांकerface_क्रमागतerate(पूर्णांक पूर्णांकerface)
अणु
	चयन (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface)) अणु
		/* These types करोn't support ports to IPD/PKO */
	हाल CVMX_HELPER_INTERFACE_MODE_DISABLED:
	हाल CVMX_HELPER_INTERFACE_MODE_PCIE:
		पूर्णांकerface_port_count[पूर्णांकerface] = 0;
		अवरोध;
		/* XAUI is a single high speed port */
	हाल CVMX_HELPER_INTERFACE_MODE_XAUI:
		पूर्णांकerface_port_count[पूर्णांकerface] =
		    __cvmx_helper_xaui_क्रमागतerate(पूर्णांकerface);
		अवरोध;
		/*
		 * RGMII/GMII/MII are all treated about the same. Most
		 * functions refer to these ports as RGMII.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_RGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_GMII:
		पूर्णांकerface_port_count[पूर्णांकerface] =
		    __cvmx_helper_rgmii_क्रमागतerate(पूर्णांकerface);
		अवरोध;
		/*
		 * SPI4 can have 1-16 ports depending on the device at
		 * the other end.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_SPI:
		पूर्णांकerface_port_count[पूर्णांकerface] =
		    __cvmx_helper_spi_क्रमागतerate(पूर्णांकerface);
		अवरोध;
		/*
		 * SGMII can have 1-4 ports depending on how many are
		 * hooked up.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_SGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_PICMG:
		पूर्णांकerface_port_count[पूर्णांकerface] =
		    __cvmx_helper_sgmii_क्रमागतerate(पूर्णांकerface);
		अवरोध;
		/* PCI target Network Packet Interface */
	हाल CVMX_HELPER_INTERFACE_MODE_NPI:
		पूर्णांकerface_port_count[पूर्णांकerface] =
		    __cvmx_helper_npi_क्रमागतerate(पूर्णांकerface);
		अवरोध;
		/*
		 * Special loopback only ports. These are not the same
		 * as other ports in loopback mode.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_LOOP:
		पूर्णांकerface_port_count[पूर्णांकerface] =
		    __cvmx_helper_loop_क्रमागतerate(पूर्णांकerface);
		अवरोध;
	पूर्ण

	पूर्णांकerface_port_count[पूर्णांकerface] =
	    __cvmx_helper_board_पूर्णांकerface_probe(पूर्णांकerface,
						पूर्णांकerface_port_count
						[पूर्णांकerface]);

	/* Make sure all global variables propagate to other cores */
	CVMX_SYNCWS;

	वापस 0;
पूर्ण

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
पूर्णांक cvmx_helper_पूर्णांकerface_probe(पूर्णांक पूर्णांकerface)
अणु
	cvmx_helper_पूर्णांकerface_क्रमागतerate(पूर्णांकerface);
	/* At this stage in the game we करोn't want packets to be moving yet.
	   The following probe calls should perक्रमm hardware setup
	   needed to determine port counts. Receive must still be disabled */
	चयन (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface)) अणु
		/* These types करोn't support ports to IPD/PKO */
	हाल CVMX_HELPER_INTERFACE_MODE_DISABLED:
	हाल CVMX_HELPER_INTERFACE_MODE_PCIE:
		अवरोध;
		/* XAUI is a single high speed port */
	हाल CVMX_HELPER_INTERFACE_MODE_XAUI:
		__cvmx_helper_xaui_probe(पूर्णांकerface);
		अवरोध;
		/*
		 * RGMII/GMII/MII are all treated about the same. Most
		 * functions refer to these ports as RGMII.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_RGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_GMII:
		__cvmx_helper_rgmii_probe(पूर्णांकerface);
		अवरोध;
		/*
		 * SPI4 can have 1-16 ports depending on the device at
		 * the other end.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_SPI:
		__cvmx_helper_spi_probe(पूर्णांकerface);
		अवरोध;
		/*
		 * SGMII can have 1-4 ports depending on how many are
		 * hooked up.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_SGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_PICMG:
		__cvmx_helper_sgmii_probe(पूर्णांकerface);
		अवरोध;
		/* PCI target Network Packet Interface */
	हाल CVMX_HELPER_INTERFACE_MODE_NPI:
		__cvmx_helper_npi_probe(पूर्णांकerface);
		अवरोध;
		/*
		 * Special loopback only ports. These are not the same
		 * as other ports in loopback mode.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_LOOP:
		__cvmx_helper_loop_probe(पूर्णांकerface);
		अवरोध;
	पूर्ण

	/* Make sure all global variables propagate to other cores */
	CVMX_SYNCWS;

	वापस 0;
पूर्ण

/**
 * Setup the IPD/PIP क्रम the ports on an पूर्णांकerface. Packet
 * classअगरication and tagging are set क्रम every port on the
 * पूर्णांकerface. The number of ports on the पूर्णांकerface must alपढ़ोy
 * have been probed.
 *
 * @पूर्णांकerface: Interface to setup IPD/PIP क्रम
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_पूर्णांकerface_setup_ipd(पूर्णांक पूर्णांकerface)
अणु
	पूर्णांक ipd_port = cvmx_helper_get_ipd_port(पूर्णांकerface, 0);
	पूर्णांक num_ports = पूर्णांकerface_port_count[पूर्णांकerface];

	जबतक (num_ports--) अणु
		__cvmx_helper_port_setup_ipd(ipd_port);
		ipd_port++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Setup global setting क्रम IPD/PIP not related to a specअगरic
 * पूर्णांकerface or port. This must be called beक्रमe IPD is enabled.
 *
 * Returns Zero on success, negative on failure.
 */
अटल पूर्णांक __cvmx_helper_global_setup_ipd(व्योम)
अणु
	/* Setup the global packet input options */
	cvmx_ipd_config(CVMX_FPA_PACKET_POOL_SIZE / 8,
			CVMX_HELPER_FIRST_MBUFF_SKIP / 8,
			CVMX_HELPER_NOT_FIRST_MBUFF_SKIP / 8,
			/* The +8 is to account क्रम the next ptr */
			(CVMX_HELPER_FIRST_MBUFF_SKIP + 8) / 128,
			/* The +8 is to account क्रम the next ptr */
			(CVMX_HELPER_NOT_FIRST_MBUFF_SKIP + 8) / 128,
			CVMX_FPA_WQE_POOL,
			CVMX_IPD_OPC_MODE_STT,
			CVMX_HELPER_ENABLE_BACK_PRESSURE);
	वापस 0;
पूर्ण

/**
 * Setup the PKO क्रम the ports on an पूर्णांकerface. The number of
 * queues per port and the priority of each PKO output queue
 * is set here. PKO must be disabled when this function is called.
 *
 * @पूर्णांकerface: Interface to setup PKO क्रम
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_पूर्णांकerface_setup_pko(पूर्णांक पूर्णांकerface)
अणु
	/*
	 * Each packet output queue has an associated priority. The
	 * higher the priority, the more often it can send a packet. A
	 * priority of 8 means it can send in all 8 rounds of
	 * contention. We're going to make each queue one less than
	 * the last.  The vector of priorities has been extended to
	 * support CN5xxx CPUs, where up to 16 queues can be
	 * associated to a port.  To keep backward compatibility we
	 * करोn't change the initial 8 priorities and replicate them in
	 * the second half.  With per-core PKO queues (PKO lockless
	 * operation) all queues have the same priority.
	 */
	uपूर्णांक64_t priorities[16] =
	    अणु 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 पूर्ण;

	/*
	 * Setup the IPD/PIP and PKO क्रम the ports discovered
	 * above. Here packet classअगरication, tagging and output
	 * priorities are set.
	 */
	पूर्णांक ipd_port = cvmx_helper_get_ipd_port(पूर्णांकerface, 0);
	पूर्णांक num_ports = पूर्णांकerface_port_count[पूर्णांकerface];
	जबतक (num_ports--) अणु
		cvmx_pko_config_port(ipd_port,
				     cvmx_pko_get_base_queue_per_core(ipd_port,
								      0),
				     cvmx_pko_get_num_queues(ipd_port),
				     priorities);
		ipd_port++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Setup global setting क्रम PKO not related to a specअगरic
 * पूर्णांकerface or port. This must be called beक्रमe PKO is enabled.
 *
 * Returns Zero on success, negative on failure.
 */
अटल पूर्णांक __cvmx_helper_global_setup_pko(व्योम)
अणु
	/*
	 * Disable tagरुको FAU समयout. This needs to be करोne beक्रमe
	 * anyone might start packet output using tags.
	 */
	जोड़ cvmx_iob_fau_समयout fau_to;
	fau_to.u64 = 0;
	fau_to.s.tout_val = 0xfff;
	fau_to.s.tout_enb = 0;
	cvmx_ग_लिखो_csr(CVMX_IOB_FAU_TIMEOUT, fau_to.u64);

	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX)) अणु
		जोड़ cvmx_pko_reg_min_pkt min_pkt;

		min_pkt.u64 = 0;
		min_pkt.s.size1 = 59;
		min_pkt.s.size2 = 59;
		min_pkt.s.size3 = 59;
		min_pkt.s.size4 = 59;
		min_pkt.s.size5 = 59;
		min_pkt.s.size6 = 59;
		min_pkt.s.size7 = 59;
		cvmx_ग_लिखो_csr(CVMX_PKO_REG_MIN_PKT, min_pkt.u64);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Setup global backpressure setting.
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_global_setup_backpressure(व्योम)
अणु
#अगर CVMX_HELPER_DISABLE_RGMII_BACKPRESSURE
	/* Disable backpressure अगर configured to करो so */
	/* Disable backpressure (छोड़ो frame) generation */
	पूर्णांक num_पूर्णांकerfaces = cvmx_helper_get_number_of_पूर्णांकerfaces();
	पूर्णांक पूर्णांकerface;
	क्रम (पूर्णांकerface = 0; पूर्णांकerface < num_पूर्णांकerfaces; पूर्णांकerface++) अणु
		चयन (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface)) अणु
		हाल CVMX_HELPER_INTERFACE_MODE_DISABLED:
		हाल CVMX_HELPER_INTERFACE_MODE_PCIE:
		हाल CVMX_HELPER_INTERFACE_MODE_NPI:
		हाल CVMX_HELPER_INTERFACE_MODE_LOOP:
		हाल CVMX_HELPER_INTERFACE_MODE_XAUI:
			अवरोध;
		हाल CVMX_HELPER_INTERFACE_MODE_RGMII:
		हाल CVMX_HELPER_INTERFACE_MODE_GMII:
		हाल CVMX_HELPER_INTERFACE_MODE_SPI:
		हाल CVMX_HELPER_INTERFACE_MODE_SGMII:
		हाल CVMX_HELPER_INTERFACE_MODE_PICMG:
			cvmx_gmx_set_backpressure_override(पूर्णांकerface, 0xf);
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * Enable packet input/output from the hardware. This function is
 * called after all पूर्णांकernal setup is complete and IPD is enabled.
 * After this function completes, packets will be accepted from the
 * hardware ports. PKO should still be disabled to make sure packets
 * aren't sent out partially setup hardware.
 *
 * @पूर्णांकerface: Interface to enable
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_packet_hardware_enable(पूर्णांक पूर्णांकerface)
अणु
	पूर्णांक result = 0;
	चयन (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface)) अणु
		/* These types करोn't support ports to IPD/PKO */
	हाल CVMX_HELPER_INTERFACE_MODE_DISABLED:
	हाल CVMX_HELPER_INTERFACE_MODE_PCIE:
		/* Nothing to करो */
		अवरोध;
		/* XAUI is a single high speed port */
	हाल CVMX_HELPER_INTERFACE_MODE_XAUI:
		result = __cvmx_helper_xaui_enable(पूर्णांकerface);
		अवरोध;
		/*
		 * RGMII/GMII/MII are all treated about the same. Most
		 * functions refer to these ports as RGMII
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_RGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_GMII:
		result = __cvmx_helper_rgmii_enable(पूर्णांकerface);
		अवरोध;
		/*
		 * SPI4 can have 1-16 ports depending on the device at
		 * the other end
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_SPI:
		result = __cvmx_helper_spi_enable(पूर्णांकerface);
		अवरोध;
		/*
		 * SGMII can have 1-4 ports depending on how many are
		 * hooked up
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_SGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_PICMG:
		result = __cvmx_helper_sgmii_enable(पूर्णांकerface);
		अवरोध;
		/* PCI target Network Packet Interface */
	हाल CVMX_HELPER_INTERFACE_MODE_NPI:
		result = __cvmx_helper_npi_enable(पूर्णांकerface);
		अवरोध;
		/*
		 * Special loopback only ports. These are not the same
		 * as other ports in loopback mode
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_LOOP:
		result = __cvmx_helper_loop_enable(पूर्णांकerface);
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

/**
 * Function to adjust पूर्णांकernal IPD poपूर्णांकer alignments
 *
 * Returns 0 on success
 *	   !0 on failure
 */
अटल पूर्णांक __cvmx_helper_errata_fix_ipd_ptr_alignment(व्योम)
अणु
#घोषणा FIX_IPD_FIRST_BUFF_PAYLOAD_BYTES \
     (CVMX_FPA_PACKET_POOL_SIZE-8-CVMX_HELPER_FIRST_MBUFF_SKIP)
#घोषणा FIX_IPD_NON_FIRST_BUFF_PAYLOAD_BYTES \
	(CVMX_FPA_PACKET_POOL_SIZE-8-CVMX_HELPER_NOT_FIRST_MBUFF_SKIP)
#घोषणा FIX_IPD_OUTPORT 0
	/* Ports 0-15 are पूर्णांकerface 0, 16-31 are पूर्णांकerface 1 */
#घोषणा INTERFACE(port) (port >> 4)
#घोषणा INDEX(port) (port & 0xf)
	uपूर्णांक64_t *p64;
	जोड़ cvmx_pko_command_word0 pko_command;
	जोड़ cvmx_buf_ptr g_buffer, pkt_buffer;
	काष्ठा cvmx_wqe *work;
	पूर्णांक size, num_segs = 0, wqe_pcnt, pkt_pcnt;
	जोड़ cvmx_gmxx_prtx_cfg gmx_cfg;
	पूर्णांक retry_cnt;
	पूर्णांक retry_loop_cnt;
	पूर्णांक i;

	/* Save values क्रम restore at end */
	uपूर्णांक64_t prtx_cfg =
	    cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG
			  (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)));
	uपूर्णांक64_t tx_ptr_en =
	    cvmx_पढ़ो_csr(CVMX_ASXX_TX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)));
	uपूर्णांक64_t rx_ptr_en =
	    cvmx_पढ़ो_csr(CVMX_ASXX_RX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)));
	uपूर्णांक64_t rxx_jabber =
	    cvmx_पढ़ो_csr(CVMX_GMXX_RXX_JABBER
			  (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)));
	uपूर्णांक64_t frame_max =
	    cvmx_पढ़ो_csr(CVMX_GMXX_RXX_FRM_MAX
			  (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)));

	/* Configure port to gig FDX as required क्रम loopback mode */
	cvmx_helper_rgmii_पूर्णांकernal_loopback(FIX_IPD_OUTPORT);

	/*
	 * Disable reception on all ports so अगर traffic is present it
	 * will not पूर्णांकerfere.
	 */
	cvmx_ग_लिखो_csr(CVMX_ASXX_RX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)), 0);

	__delay(100000000ull);

	क्रम (retry_loop_cnt = 0; retry_loop_cnt < 10; retry_loop_cnt++) अणु
		retry_cnt = 100000;
		wqe_pcnt = cvmx_पढ़ो_csr(CVMX_IPD_PTR_COUNT);
		pkt_pcnt = (wqe_pcnt >> 7) & 0x7f;
		wqe_pcnt &= 0x7f;

		num_segs = (2 + pkt_pcnt - wqe_pcnt) & 3;

		अगर (num_segs == 0)
			जाओ fix_ipd_निकास;

		num_segs += 1;

		size =
		    FIX_IPD_FIRST_BUFF_PAYLOAD_BYTES +
		    ((num_segs - 1) * FIX_IPD_NON_FIRST_BUFF_PAYLOAD_BYTES) -
		    (FIX_IPD_NON_FIRST_BUFF_PAYLOAD_BYTES / 2);

		cvmx_ग_लिखो_csr(CVMX_ASXX_PRT_LOOP(INTERFACE(FIX_IPD_OUTPORT)),
			       1 << INDEX(FIX_IPD_OUTPORT));
		CVMX_SYNC;

		g_buffer.u64 = 0;
		g_buffer.s.addr =
		    cvmx_ptr_to_phys(cvmx_fpa_alloc(CVMX_FPA_WQE_POOL));
		अगर (g_buffer.s.addr == 0) अणु
			cvmx_dम_लिखो("WARNING: FIX_IPD_PTR_ALIGNMENT "
				     "buffer allocation failure.\n");
			जाओ fix_ipd_निकास;
		पूर्ण

		g_buffer.s.pool = CVMX_FPA_WQE_POOL;
		g_buffer.s.size = num_segs;

		pkt_buffer.u64 = 0;
		pkt_buffer.s.addr =
		    cvmx_ptr_to_phys(cvmx_fpa_alloc(CVMX_FPA_PACKET_POOL));
		अगर (pkt_buffer.s.addr == 0) अणु
			cvmx_dम_लिखो("WARNING: FIX_IPD_PTR_ALIGNMENT "
				     "buffer allocation failure.\n");
			जाओ fix_ipd_निकास;
		पूर्ण
		pkt_buffer.s.i = 1;
		pkt_buffer.s.pool = CVMX_FPA_PACKET_POOL;
		pkt_buffer.s.size = FIX_IPD_FIRST_BUFF_PAYLOAD_BYTES;

		p64 = (uपूर्णांक64_t *) cvmx_phys_to_ptr(pkt_buffer.s.addr);
		p64[0] = 0xffffffffffff0000ull;
		p64[1] = 0x08004510ull;
		p64[2] = ((uपूर्णांक64_t) (size - 14) << 48) | 0x5ae740004000ull;
		p64[3] = 0x3a5fc0a81073c0a8ull;

		क्रम (i = 0; i < num_segs; i++) अणु
			अगर (i > 0)
				pkt_buffer.s.size =
				    FIX_IPD_NON_FIRST_BUFF_PAYLOAD_BYTES;

			अगर (i == (num_segs - 1))
				pkt_buffer.s.i = 0;

			*(uपूर्णांक64_t *) cvmx_phys_to_ptr(g_buffer.s.addr +
						       8 * i) = pkt_buffer.u64;
		पूर्ण

		/* Build the PKO command */
		pko_command.u64 = 0;
		pko_command.s.segs = num_segs;
		pko_command.s.total_bytes = size;
		pko_command.s.करोntमुक्त = 0;
		pko_command.s.gather = 1;

		gmx_cfg.u64 =
		    cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG
				  (INDEX(FIX_IPD_OUTPORT),
				   INTERFACE(FIX_IPD_OUTPORT)));
		gmx_cfg.s.en = 1;
		cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG
			       (INDEX(FIX_IPD_OUTPORT),
				INTERFACE(FIX_IPD_OUTPORT)), gmx_cfg.u64);
		cvmx_ग_लिखो_csr(CVMX_ASXX_TX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)),
			       1 << INDEX(FIX_IPD_OUTPORT));
		cvmx_ग_लिखो_csr(CVMX_ASXX_RX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)),
			       1 << INDEX(FIX_IPD_OUTPORT));

		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_JABBER
			       (INDEX(FIX_IPD_OUTPORT),
				INTERFACE(FIX_IPD_OUTPORT)), 65392 - 14 - 4);
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_FRM_MAX
			       (INDEX(FIX_IPD_OUTPORT),
				INTERFACE(FIX_IPD_OUTPORT)), 65392 - 14 - 4);

		cvmx_pko_send_packet_prepare(FIX_IPD_OUTPORT,
					     cvmx_pko_get_base_queue
					     (FIX_IPD_OUTPORT),
					     CVMX_PKO_LOCK_CMD_QUEUE);
		cvmx_pko_send_packet_finish(FIX_IPD_OUTPORT,
					    cvmx_pko_get_base_queue
					    (FIX_IPD_OUTPORT), pko_command,
					    g_buffer, CVMX_PKO_LOCK_CMD_QUEUE);

		CVMX_SYNC;

		करो अणु
			work = cvmx_घात_work_request_sync(CVMX_POW_WAIT);
			retry_cnt--;
		पूर्ण जबतक ((work == शून्य) && (retry_cnt > 0));

		अगर (!retry_cnt)
			cvmx_dम_लिखो("WARNING: FIX_IPD_PTR_ALIGNMENT "
				     "get_work() timeout occurred.\n");

		/* Free packet */
		अगर (work)
			cvmx_helper_मुक्त_packet_data(work);
	पूर्ण

fix_ipd_निकास:

	/* Return CSR configs to saved values */
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG
		       (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)),
		       prtx_cfg);
	cvmx_ग_लिखो_csr(CVMX_ASXX_TX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)),
		       tx_ptr_en);
	cvmx_ग_लिखो_csr(CVMX_ASXX_RX_PRT_EN(INTERFACE(FIX_IPD_OUTPORT)),
		       rx_ptr_en);
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_JABBER
		       (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)),
		       rxx_jabber);
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_FRM_MAX
		       (INDEX(FIX_IPD_OUTPORT), INTERFACE(FIX_IPD_OUTPORT)),
		       frame_max);
	cvmx_ग_लिखो_csr(CVMX_ASXX_PRT_LOOP(INTERFACE(FIX_IPD_OUTPORT)), 0);

	CVMX_SYNC;
	अगर (num_segs)
		cvmx_dम_लिखो("WARNING: FIX_IPD_PTR_ALIGNMENT failed.\n");

	वापस !!num_segs;

पूर्ण

/**
 * Called after all पूर्णांकernal packet IO paths are setup. This
 * function enables IPD/PIP and begins packet input and output.
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक cvmx_helper_ipd_and_packet_input_enable(व्योम)
अणु
	पूर्णांक num_पूर्णांकerfaces;
	पूर्णांक पूर्णांकerface;

	/* Enable IPD */
	cvmx_ipd_enable();

	/*
	 * Time to enable hardware ports packet input and output. Note
	 * that at this poपूर्णांक IPD/PIP must be fully functional and PKO
	 * must be disabled
	 */
	num_पूर्णांकerfaces = cvmx_helper_get_number_of_पूर्णांकerfaces();
	क्रम (पूर्णांकerface = 0; पूर्णांकerface < num_पूर्णांकerfaces; पूर्णांकerface++) अणु
		अगर (cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface) > 0)
			__cvmx_helper_packet_hardware_enable(पूर्णांकerface);
	पूर्ण

	/* Finally enable PKO now that the entire path is up and running */
	cvmx_pko_enable();

	अगर ((OCTEON_IS_MODEL(OCTEON_CN31XX_PASS1)
	     || OCTEON_IS_MODEL(OCTEON_CN30XX_PASS1))
	    && (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM))
		__cvmx_helper_errata_fix_ipd_ptr_alignment();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_ipd_and_packet_input_enable);

/**
 * Initialize the PIP, IPD, and PKO hardware to support
 * simple priority based queues क्रम the ethernet ports. Each
 * port is configured with a number of priority queues based
 * on CVMX_PKO_QUEUES_PER_PORT_* where each queue is lower
 * priority than the previous.
 *
 * Returns Zero on success, non-zero on failure
 */
पूर्णांक cvmx_helper_initialize_packet_io_global(व्योम)
अणु
	पूर्णांक result = 0;
	पूर्णांक पूर्णांकerface;
	जोड़ cvmx_l2c_cfg l2c_cfg;
	स्थिर पूर्णांक num_पूर्णांकerfaces = cvmx_helper_get_number_of_पूर्णांकerfaces();

	/*
	 * CN52XX pass 1: Due to a bug in 2nd order CDR, it needs to
	 * be disabled.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_0))
		__cvmx_helper_errata_qlm_disable_2nd_order_cdr(1);

	/*
	 * Tell L2 to give the IOB अटलally higher priority compared
	 * to the cores. This aव्योमs conditions where IO blocks might
	 * be starved under very high L2 loads.
	 */
	l2c_cfg.u64 = cvmx_पढ़ो_csr(CVMX_L2C_CFG);
	l2c_cfg.s.lrf_arb_mode = 0;
	l2c_cfg.s.rfb_arb_mode = 0;
	cvmx_ग_लिखो_csr(CVMX_L2C_CFG, l2c_cfg.u64);

	cvmx_pko_initialize_global();
	क्रम (पूर्णांकerface = 0; पूर्णांकerface < num_पूर्णांकerfaces; पूर्णांकerface++) अणु
		result |= cvmx_helper_पूर्णांकerface_probe(पूर्णांकerface);
		अगर (cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface) > 0)
			cvmx_dम_लिखो("Interface %d has %d ports (%s)\n",
				     पूर्णांकerface,
				     cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface),
				     cvmx_helper_पूर्णांकerface_mode_to_string
				     (cvmx_helper_पूर्णांकerface_get_mode
				      (पूर्णांकerface)));
		result |= __cvmx_helper_पूर्णांकerface_setup_ipd(पूर्णांकerface);
		result |= __cvmx_helper_पूर्णांकerface_setup_pko(पूर्णांकerface);
	पूर्ण

	result |= __cvmx_helper_global_setup_ipd();
	result |= __cvmx_helper_global_setup_pko();

	/* Enable any flow control and backpressure */
	result |= __cvmx_helper_global_setup_backpressure();

#अगर CVMX_HELPER_ENABLE_IPD
	result |= cvmx_helper_ipd_and_packet_input_enable();
#पूर्ण_अगर
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_initialize_packet_io_global);

/**
 * Does core local initialization क्रम packet io
 *
 * Returns Zero on success, non-zero on failure
 */
पूर्णांक cvmx_helper_initialize_packet_io_local(व्योम)
अणु
	वापस cvmx_pko_initialize_local();
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
जोड़ cvmx_helper_link_info cvmx_helper_link_get(पूर्णांक ipd_port)
अणु
	जोड़ cvmx_helper_link_info result;
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);

	/* The शेष result will be a करोwn link unless the code below
	   changes it */
	result.u64 = 0;

	अगर (index >= cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface))
		वापस result;

	चयन (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface)) अणु
	हाल CVMX_HELPER_INTERFACE_MODE_DISABLED:
	हाल CVMX_HELPER_INTERFACE_MODE_PCIE:
		/* Network links are not supported */
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_XAUI:
		result = __cvmx_helper_xaui_link_get(ipd_port);
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_GMII:
		अगर (index == 0)
			result = __cvmx_helper_rgmii_link_get(ipd_port);
		अन्यथा अणु
			WARN(1, "Using deprecated link status - please update your DT");
			result.s.full_duplex = 1;
			result.s.link_up = 1;
			result.s.speed = 1000;
		पूर्ण
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_RGMII:
		result = __cvmx_helper_rgmii_link_get(ipd_port);
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_SPI:
		result = __cvmx_helper_spi_link_get(ipd_port);
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_SGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_PICMG:
		result = __cvmx_helper_sgmii_link_get(ipd_port);
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_NPI:
	हाल CVMX_HELPER_INTERFACE_MODE_LOOP:
		/* Network links are not supported */
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_link_get);

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
पूर्णांक cvmx_helper_link_set(पूर्णांक ipd_port, जोड़ cvmx_helper_link_info link_info)
अणु
	पूर्णांक result = -1;
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);

	अगर (index >= cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface))
		वापस -1;

	चयन (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface)) अणु
	हाल CVMX_HELPER_INTERFACE_MODE_DISABLED:
	हाल CVMX_HELPER_INTERFACE_MODE_PCIE:
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_XAUI:
		result = __cvmx_helper_xaui_link_set(ipd_port, link_info);
		अवरोध;
		/*
		 * RGMII/GMII/MII are all treated about the same. Most
		 * functions refer to these ports as RGMII.
		 */
	हाल CVMX_HELPER_INTERFACE_MODE_RGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_GMII:
		result = __cvmx_helper_rgmii_link_set(ipd_port, link_info);
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_SPI:
		result = __cvmx_helper_spi_link_set(ipd_port, link_info);
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_SGMII:
	हाल CVMX_HELPER_INTERFACE_MODE_PICMG:
		result = __cvmx_helper_sgmii_link_set(ipd_port, link_info);
		अवरोध;
	हाल CVMX_HELPER_INTERFACE_MODE_NPI:
	हाल CVMX_HELPER_INTERFACE_MODE_LOOP:
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_link_set);
