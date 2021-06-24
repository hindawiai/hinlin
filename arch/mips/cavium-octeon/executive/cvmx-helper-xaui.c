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
 * Functions क्रम XAUI initialization, configuration,
 * and monitoring.
 *
 */

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>

#समावेश <यंत्र/octeon/cvmx-helper.h>

#समावेश <यंत्र/octeon/cvmx-pko-defs.h>
#समावेश <यंत्र/octeon/cvmx-gmxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-pcsx-defs.h>
#समावेश <यंत्र/octeon/cvmx-pcsxx-defs.h>

पूर्णांक __cvmx_helper_xaui_क्रमागतerate(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_gmxx_hg2_control gmx_hg2_control;

	/* If HiGig2 is enabled वापस 16 ports, otherwise वापस 1 port */
	gmx_hg2_control.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_HG2_CONTROL(पूर्णांकerface));
	अगर (gmx_hg2_control.s.hg2tx_en)
		वापस 16;
	अन्यथा
		वापस 1;
पूर्ण

/**
 * Probe a XAUI पूर्णांकerface and determine the number of ports
 * connected to it. The XAUI पूर्णांकerface should still be करोwn
 * after this call.
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Number of ports on the पूर्णांकerface. Zero to disable.
 */
पूर्णांक __cvmx_helper_xaui_probe(पूर्णांक पूर्णांकerface)
अणु
	पूर्णांक i;
	जोड़ cvmx_gmxx_inf_mode mode;

	/*
	 * Due to errata GMX-700 on CN56XXp1.x and CN52XXp1.x, the
	 * पूर्णांकerface needs to be enabled beक्रमe IPD otherwise per port
	 * backpressure may not work properly.
	 */
	mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));
	mode.s.en = 1;
	cvmx_ग_लिखो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface), mode.u64);

	__cvmx_helper_setup_gmx(पूर्णांकerface, 1);

	/*
	 * Setup PKO to support 16 ports क्रम HiGig2 भव
	 * ports. We're poपूर्णांकing all of the PKO packet ports क्रम this
	 * पूर्णांकerface to the XAUI. This allows us to use HiGig2
	 * backpressure per port.
	 */
	क्रम (i = 0; i < 16; i++) अणु
		जोड़ cvmx_pko_mem_port_ptrs pko_mem_port_ptrs;
		pko_mem_port_ptrs.u64 = 0;
		/*
		 * We set each PKO port to have equal priority in a
		 * round robin fashion.
		 */
		pko_mem_port_ptrs.s.अटल_p = 0;
		pko_mem_port_ptrs.s.qos_mask = 0xff;
		/* All PKO ports map to the same XAUI hardware port */
		pko_mem_port_ptrs.s.eid = पूर्णांकerface * 4;
		pko_mem_port_ptrs.s.pid = पूर्णांकerface * 16 + i;
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_PORT_PTRS, pko_mem_port_ptrs.u64);
	पूर्ण
	वापस __cvmx_helper_xaui_क्रमागतerate(पूर्णांकerface);
पूर्ण

/**
 * Bringup and enable a XAUI पूर्णांकerface. After this call packet
 * I/O should be fully functional. This is called with IPD
 * enabled but PKO disabled.
 *
 * @पूर्णांकerface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक __cvmx_helper_xaui_enable(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_gmxx_prtx_cfg gmx_cfg;
	जोड़ cvmx_pcsxx_control1_reg xauiCtl;
	जोड़ cvmx_pcsxx_misc_ctl_reg xauiMiscCtl;
	जोड़ cvmx_gmxx_tx_xaui_ctl gmxXauiTxCtl;
	जोड़ cvmx_gmxx_rxx_पूर्णांक_en gmx_rx_पूर्णांक_en;
	जोड़ cvmx_gmxx_tx_पूर्णांक_en gmx_tx_पूर्णांक_en;
	जोड़ cvmx_pcsxx_पूर्णांक_en_reg pcsx_पूर्णांक_en_reg;

	/* Setup PKND */
	अगर (octeon_has_feature(OCTEON_FEATURE_PKND)) अणु
		gmx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface));
		gmx_cfg.s.pknd = cvmx_helper_get_ipd_port(पूर्णांकerface, 0);
		cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface), gmx_cfg.u64);
	पूर्ण

	/* (1) Interface has alपढ़ोy been enabled. */

	/* (2) Disable GMX. */
	xauiMiscCtl.u64 = cvmx_पढ़ो_csr(CVMX_PCSXX_MISC_CTL_REG(पूर्णांकerface));
	xauiMiscCtl.s.gmxeno = 1;
	cvmx_ग_लिखो_csr(CVMX_PCSXX_MISC_CTL_REG(पूर्णांकerface), xauiMiscCtl.u64);

	/* (3) Disable GMX and PCSX पूर्णांकerrupts. */
	gmx_rx_पूर्णांक_en.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_RXX_INT_EN(0, पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_INT_EN(0, पूर्णांकerface), 0x0);
	gmx_tx_पूर्णांक_en.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_TX_INT_EN(पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_INT_EN(पूर्णांकerface), 0x0);
	pcsx_पूर्णांक_en_reg.u64 = cvmx_पढ़ो_csr(CVMX_PCSXX_INT_EN_REG(पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_PCSXX_INT_EN_REG(पूर्णांकerface), 0x0);

	/* (4) Bring up the PCSX and GMX reconciliation layer. */
	/* (4)a Set polarity and lane swapping. */
	/* (4)b */
	gmxXauiTxCtl.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_TX_XAUI_CTL(पूर्णांकerface));
	/* Enable better IFG packing and improves perक्रमmance */
	gmxXauiTxCtl.s.dic_en = 1;
	gmxXauiTxCtl.s.uni_en = 0;
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_XAUI_CTL(पूर्णांकerface), gmxXauiTxCtl.u64);

	/* (4)c Aply reset sequence */
	xauiCtl.u64 = cvmx_पढ़ो_csr(CVMX_PCSXX_CONTROL1_REG(पूर्णांकerface));
	xauiCtl.s.lo_pwr = 0;

	/* Issuing a reset here seems to hang some CN68XX chips. */
	अगर (!OCTEON_IS_MODEL(OCTEON_CN68XX_PASS1_X) &&
	    !OCTEON_IS_MODEL(OCTEON_CN68XX_PASS2_X))
		xauiCtl.s.reset = 1;

	cvmx_ग_लिखो_csr(CVMX_PCSXX_CONTROL1_REG(पूर्णांकerface), xauiCtl.u64);

	/* Wait क्रम PCS to come out of reset */
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_PCSXX_CONTROL1_REG(पूर्णांकerface), जोड़ cvmx_pcsxx_control1_reg,
	     reset, ==, 0, 10000))
		वापस -1;
	/* Wait क्रम PCS to be aligned */
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_PCSXX_10GBX_STATUS_REG(पूर्णांकerface),
	     जोड़ cvmx_pcsxx_10gbx_status_reg, alignd, ==, 1, 10000))
		वापस -1;
	/* Wait क्रम RX to be पढ़ोy */
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_GMXX_RX_XAUI_CTL(पूर्णांकerface), जोड़ cvmx_gmxx_rx_xaui_ctl,
		    status, ==, 0, 10000))
		वापस -1;

	/* (6) Configure GMX */
	gmx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface));
	gmx_cfg.s.en = 0;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface), gmx_cfg.u64);

	/* Wait क्रम GMX RX to be idle */
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface), जोड़ cvmx_gmxx_prtx_cfg,
		    rx_idle, ==, 1, 10000))
		वापस -1;
	/* Wait क्रम GMX TX to be idle */
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface), जोड़ cvmx_gmxx_prtx_cfg,
		    tx_idle, ==, 1, 10000))
		वापस -1;

	/* GMX configure */
	gmx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface));
	gmx_cfg.s.speed = 1;
	gmx_cfg.s.speed_msb = 0;
	gmx_cfg.s.slotसमय = 1;
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_PRTS(पूर्णांकerface), 1);
	cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_SLOT(0, पूर्णांकerface), 512);
	cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_BURST(0, पूर्णांकerface), 8192);
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface), gmx_cfg.u64);

	/* (7) Clear out any error state */
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_INT_REG(0, पूर्णांकerface),
		       cvmx_पढ़ो_csr(CVMX_GMXX_RXX_INT_REG(0, पूर्णांकerface)));
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_INT_REG(पूर्णांकerface),
		       cvmx_पढ़ो_csr(CVMX_GMXX_TX_INT_REG(पूर्णांकerface)));
	cvmx_ग_लिखो_csr(CVMX_PCSXX_INT_REG(पूर्णांकerface),
		       cvmx_पढ़ो_csr(CVMX_PCSXX_INT_REG(पूर्णांकerface)));

	/* Wait क्रम receive link */
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_PCSXX_STATUS1_REG(पूर्णांकerface), जोड़ cvmx_pcsxx_status1_reg,
	     rcv_lnk, ==, 1, 10000))
		वापस -1;
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_PCSXX_STATUS2_REG(पूर्णांकerface), जोड़ cvmx_pcsxx_status2_reg,
	     xmtflt, ==, 0, 10000))
		वापस -1;
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_PCSXX_STATUS2_REG(पूर्णांकerface), जोड़ cvmx_pcsxx_status2_reg,
	     rcvflt, ==, 0, 10000))
		वापस -1;

	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_INT_EN(0, पूर्णांकerface), gmx_rx_पूर्णांक_en.u64);
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_INT_EN(पूर्णांकerface), gmx_tx_पूर्णांक_en.u64);
	cvmx_ग_लिखो_csr(CVMX_PCSXX_INT_EN_REG(पूर्णांकerface), pcsx_पूर्णांक_en_reg.u64);

	/* (8) Enable packet reception */
	xauiMiscCtl.s.gmxeno = 0;
	cvmx_ग_लिखो_csr(CVMX_PCSXX_MISC_CTL_REG(पूर्णांकerface), xauiMiscCtl.u64);

	gmx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface));
	gmx_cfg.s.en = 1;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(0, पूर्णांकerface), gmx_cfg.u64);

	__cvmx_पूर्णांकerrupt_pcsx_पूर्णांकx_en_reg_enable(0, पूर्णांकerface);
	__cvmx_पूर्णांकerrupt_pcsx_पूर्णांकx_en_reg_enable(1, पूर्णांकerface);
	__cvmx_पूर्णांकerrupt_pcsx_पूर्णांकx_en_reg_enable(2, पूर्णांकerface);
	__cvmx_पूर्णांकerrupt_pcsx_पूर्णांकx_en_reg_enable(3, पूर्णांकerface);
	__cvmx_पूर्णांकerrupt_pcsxx_पूर्णांक_en_reg_enable(पूर्णांकerface);
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
जोड़ cvmx_helper_link_info __cvmx_helper_xaui_link_get(पूर्णांक ipd_port)
अणु
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	जोड़ cvmx_gmxx_tx_xaui_ctl gmxx_tx_xaui_ctl;
	जोड़ cvmx_gmxx_rx_xaui_ctl gmxx_rx_xaui_ctl;
	जोड़ cvmx_pcsxx_status1_reg pcsxx_status1_reg;
	जोड़ cvmx_helper_link_info result;

	gmxx_tx_xaui_ctl.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_TX_XAUI_CTL(पूर्णांकerface));
	gmxx_rx_xaui_ctl.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_RX_XAUI_CTL(पूर्णांकerface));
	pcsxx_status1_reg.u64 =
	    cvmx_पढ़ो_csr(CVMX_PCSXX_STATUS1_REG(पूर्णांकerface));
	result.u64 = 0;

	/* Only वापस a link अगर both RX and TX are happy */
	अगर ((gmxx_tx_xaui_ctl.s.ls == 0) && (gmxx_rx_xaui_ctl.s.status == 0) &&
	    (pcsxx_status1_reg.s.rcv_lnk == 1)) अणु
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 10000;
	पूर्ण अन्यथा अणु
		/* Disable GMX and PCSX पूर्णांकerrupts. */
		cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_INT_EN(0, पूर्णांकerface), 0x0);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TX_INT_EN(पूर्णांकerface), 0x0);
		cvmx_ग_लिखो_csr(CVMX_PCSXX_INT_EN_REG(पूर्णांकerface), 0x0);
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
पूर्णांक __cvmx_helper_xaui_link_set(पूर्णांक ipd_port, जोड़ cvmx_helper_link_info link_info)
अणु
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	जोड़ cvmx_gmxx_tx_xaui_ctl gmxx_tx_xaui_ctl;
	जोड़ cvmx_gmxx_rx_xaui_ctl gmxx_rx_xaui_ctl;

	gmxx_tx_xaui_ctl.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_TX_XAUI_CTL(पूर्णांकerface));
	gmxx_rx_xaui_ctl.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_RX_XAUI_CTL(पूर्णांकerface));

	/* If the link shouldn't be up, then just वापस */
	अगर (!link_info.s.link_up)
		वापस 0;

	/* Do nothing अगर both RX and TX are happy */
	अगर ((gmxx_tx_xaui_ctl.s.ls == 0) && (gmxx_rx_xaui_ctl.s.status == 0))
		वापस 0;

	/* Bring the link up */
	वापस __cvmx_helper_xaui_enable(पूर्णांकerface);
पूर्ण
