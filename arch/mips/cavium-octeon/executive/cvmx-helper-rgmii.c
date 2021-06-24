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
 * Functions क्रम RGMII/GMII/MII initialization, configuration,
 * and monitoring.
 */
#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>

#समावेश <यंत्र/octeon/cvmx-pko.h>
#समावेश <यंत्र/octeon/cvmx-helper.h>
#समावेश <यंत्र/octeon/cvmx-helper-board.h>

#समावेश <यंत्र/octeon/cvmx-npi-defs.h>
#समावेश <यंत्र/octeon/cvmx-gmxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-asxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-dbg-defs.h>

/**
 * Probe RGMII ports and determine the number present
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Number of RGMII/GMII/MII ports (0-4).
 */
पूर्णांक __cvmx_helper_rgmii_probe(पूर्णांक पूर्णांकerface)
अणु
	पूर्णांक num_ports = 0;
	जोड़ cvmx_gmxx_inf_mode mode;
	mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));

	अगर (mode.s.type) अणु
		अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)
		    || OCTEON_IS_MODEL(OCTEON_CN58XX)) अणु
			cvmx_dम_लिखो("ERROR: RGMII initialize called in "
				     "SPI interface\n");
		पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN31XX)
			   || OCTEON_IS_MODEL(OCTEON_CN30XX)
			   || OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
			/*
			 * On these chips "type" says we're in
			 * GMII/MII mode. This limits us to 2 ports
			 */
			num_ports = 2;
		पूर्ण अन्यथा अणु
			cvmx_dम_लिखो("ERROR: Unsupported Octeon model in %s\n",
				     __func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)
		    || OCTEON_IS_MODEL(OCTEON_CN58XX)) अणु
			num_ports = 4;
		पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN31XX)
			   || OCTEON_IS_MODEL(OCTEON_CN30XX)
			   || OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
			num_ports = 3;
		पूर्ण अन्यथा अणु
			cvmx_dम_लिखो("ERROR: Unsupported Octeon model in %s\n",
				     __func__);
		पूर्ण
	पूर्ण
	वापस num_ports;
पूर्ण

/**
 * Put an RGMII पूर्णांकerface in loopback mode. Internal packets sent
 * out will be received back again on the same port. Externally
 * received packets will echo back out.
 *
 * @port:   IPD port number to loop.
 */
व्योम cvmx_helper_rgmii_पूर्णांकernal_loopback(पूर्णांक port)
अणु
	पूर्णांक पूर्णांकerface = (port >> 4) & 1;
	पूर्णांक index = port & 0xf;
	uपूर्णांक64_t पंचांगp;

	जोड़ cvmx_gmxx_prtx_cfg gmx_cfg;
	gmx_cfg.u64 = 0;
	gmx_cfg.s.duplex = 1;
	gmx_cfg.s.slotसमय = 1;
	gmx_cfg.s.speed = 1;
	cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_CLK(index, पूर्णांकerface), 1);
	cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_SLOT(index, पूर्णांकerface), 0x200);
	cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_BURST(index, पूर्णांकerface), 0x2000);
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), gmx_cfg.u64);
	पंचांगp = cvmx_पढ़ो_csr(CVMX_ASXX_PRT_LOOP(पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_ASXX_PRT_LOOP(पूर्णांकerface), (1 << index) | पंचांगp);
	पंचांगp = cvmx_पढ़ो_csr(CVMX_ASXX_TX_PRT_EN(पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_ASXX_TX_PRT_EN(पूर्णांकerface), (1 << index) | पंचांगp);
	पंचांगp = cvmx_पढ़ो_csr(CVMX_ASXX_RX_PRT_EN(पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_ASXX_RX_PRT_EN(पूर्णांकerface), (1 << index) | पंचांगp);
	gmx_cfg.s.en = 1;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), gmx_cfg.u64);
पूर्ण

/**
 * Workaround ASX setup errata with CN38XX pass1
 *
 * @पूर्णांकerface: Interface to setup
 * @port:      Port to setup (0..3)
 * @cpu_घड़ी_hz:
 *		    Chip frequency in Hertz
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_errata_asx_pass1(पूर्णांक पूर्णांकerface, पूर्णांक port,
					  पूर्णांक cpu_घड़ी_hz)
अणु
	/* Set hi water mark as per errata GMX-4 */
	अगर (cpu_घड़ी_hz >= 325000000 && cpu_घड़ी_hz < 375000000)
		cvmx_ग_लिखो_csr(CVMX_ASXX_TX_HI_WATERX(port, पूर्णांकerface), 12);
	अन्यथा अगर (cpu_घड़ी_hz >= 375000000 && cpu_घड़ी_hz < 437000000)
		cvmx_ग_लिखो_csr(CVMX_ASXX_TX_HI_WATERX(port, पूर्णांकerface), 11);
	अन्यथा अगर (cpu_घड़ी_hz >= 437000000 && cpu_घड़ी_hz < 550000000)
		cvmx_ग_लिखो_csr(CVMX_ASXX_TX_HI_WATERX(port, पूर्णांकerface), 10);
	अन्यथा अगर (cpu_घड़ी_hz >= 550000000 && cpu_घड़ी_hz < 687000000)
		cvmx_ग_लिखो_csr(CVMX_ASXX_TX_HI_WATERX(port, पूर्णांकerface), 9);
	अन्यथा
		cvmx_dम_लिखो("Illegal clock frequency (%d). "
			"CVMX_ASXX_TX_HI_WATERX not set\n", cpu_घड़ी_hz);
	वापस 0;
पूर्ण

/**
 * Configure all of the ASX, GMX, and PKO रेजिस्टरs required
 * to get RGMII to function on the supplied पूर्णांकerface.
 *
 * @पूर्णांकerface: PKO Interface to configure (0 or 1)
 *
 * Returns Zero on success
 */
पूर्णांक __cvmx_helper_rgmii_enable(पूर्णांक पूर्णांकerface)
अणु
	पूर्णांक num_ports = cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface);
	पूर्णांक port;
	काष्ठा cvmx_sysinfo *sys_info_ptr = cvmx_sysinfo_get();
	जोड़ cvmx_gmxx_inf_mode mode;
	जोड़ cvmx_asxx_tx_prt_en asx_tx;
	जोड़ cvmx_asxx_rx_prt_en asx_rx;

	mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));

	अगर (mode.s.en == 0)
		वापस -1;
	अगर ((OCTEON_IS_MODEL(OCTEON_CN38XX) ||
	     OCTEON_IS_MODEL(OCTEON_CN58XX)) && mode.s.type == 1)
		/* Ignore SPI पूर्णांकerfaces */
		वापस -1;

	/* Configure the ASX रेजिस्टरs needed to use the RGMII ports */
	asx_tx.u64 = 0;
	asx_tx.s.prt_en = cvmx_build_mask(num_ports);
	cvmx_ग_लिखो_csr(CVMX_ASXX_TX_PRT_EN(पूर्णांकerface), asx_tx.u64);

	asx_rx.u64 = 0;
	asx_rx.s.prt_en = cvmx_build_mask(num_ports);
	cvmx_ग_लिखो_csr(CVMX_ASXX_RX_PRT_EN(पूर्णांकerface), asx_rx.u64);

	/* Configure the GMX रेजिस्टरs needed to use the RGMII ports */
	क्रम (port = 0; port < num_ports; port++) अणु
		/* Setting of CVMX_GMXX_TXX_THRESH has been moved to
		   __cvmx_helper_setup_gmx() */

		अगर (cvmx_octeon_is_pass1())
			__cvmx_helper_errata_asx_pass1(पूर्णांकerface, port,
						       sys_info_ptr->
						       cpu_घड़ी_hz);
		अन्यथा अणु
			/*
			 * Configure more flexible RGMII preamble
			 * checking. Pass 1 करोesn't support this
			 * feature.
			 */
			जोड़ cvmx_gmxx_rxx_frm_ctl frm_ctl;
			frm_ctl.u64 =
			    cvmx_पढ़ो_csr(CVMX_GMXX_RXX_FRM_CTL
					  (port, पूर्णांकerface));
			/* New field, so must be compile समय */
			frm_ctl.s.pre_मुक्त = 1;
			cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_FRM_CTL(port, पूर्णांकerface),
				       frm_ctl.u64);
		पूर्ण

		/*
		 * Each छोड़ो frame transmitted will ask क्रम about 10M
		 * bit बार beक्रमe resume.  If buffer space comes
		 * available beक्रमe that समय has expired, an XON
		 * छोड़ो frame (0 समय) will be transmitted to restart
		 * the flow.
		 */
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_PAUSE_PKT_TIME(port, पूर्णांकerface),
			       20000);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_PAUSE_PKT_INTERVAL
			       (port, पूर्णांकerface), 19000);

		अगर (OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
			cvmx_ग_लिखो_csr(CVMX_ASXX_TX_CLK_SETX(port, पूर्णांकerface),
				       16);
			cvmx_ग_लिखो_csr(CVMX_ASXX_RX_CLK_SETX(port, पूर्णांकerface),
				       16);
		पूर्ण अन्यथा अणु
			cvmx_ग_लिखो_csr(CVMX_ASXX_TX_CLK_SETX(port, पूर्णांकerface),
				       24);
			cvmx_ग_लिखो_csr(CVMX_ASXX_RX_CLK_SETX(port, पूर्णांकerface),
				       24);
		पूर्ण
	पूर्ण

	__cvmx_helper_setup_gmx(पूर्णांकerface, num_ports);

	/* enable the ports now */
	क्रम (port = 0; port < num_ports; port++) अणु
		जोड़ cvmx_gmxx_prtx_cfg gmx_cfg;

		gmx_cfg.u64 =
		    cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(port, पूर्णांकerface));
		gmx_cfg.s.en = 1;
		cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(port, पूर्णांकerface),
			       gmx_cfg.u64);
	पूर्ण
	__cvmx_पूर्णांकerrupt_asxx_enable(पूर्णांकerface);
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
जोड़ cvmx_helper_link_info __cvmx_helper_rgmii_link_get(पूर्णांक ipd_port)
अणु
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);
	जोड़ cvmx_asxx_prt_loop asxx_prt_loop;

	asxx_prt_loop.u64 = cvmx_पढ़ो_csr(CVMX_ASXX_PRT_LOOP(पूर्णांकerface));
	अगर (asxx_prt_loop.s.पूर्णांक_loop & (1 << index)) अणु
		/* Force 1Gbps full duplex on पूर्णांकernal loopback */
		जोड़ cvmx_helper_link_info result;
		result.u64 = 0;
		result.s.full_duplex = 1;
		result.s.link_up = 1;
		result.s.speed = 1000;
		वापस result;
	पूर्ण अन्यथा
		वापस __cvmx_helper_board_link_get(ipd_port);
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
पूर्णांक __cvmx_helper_rgmii_link_set(पूर्णांक ipd_port,
				 जोड़ cvmx_helper_link_info link_info)
अणु
	पूर्णांक result = 0;
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);
	जोड़ cvmx_gmxx_prtx_cfg original_gmx_cfg;
	जोड़ cvmx_gmxx_prtx_cfg new_gmx_cfg;
	जोड़ cvmx_pko_mem_queue_qos pko_mem_queue_qos;
	जोड़ cvmx_pko_mem_queue_qos pko_mem_queue_qos_save[16];
	जोड़ cvmx_gmxx_tx_ovr_bp gmx_tx_ovr_bp;
	जोड़ cvmx_gmxx_tx_ovr_bp gmx_tx_ovr_bp_save;
	पूर्णांक i;

	/* Ignore speed sets in the simulator */
	अगर (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM)
		वापस 0;

	/* Read the current settings so we know the current enable state */
	original_gmx_cfg.u64 =
	    cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
	new_gmx_cfg = original_gmx_cfg;

	/* Disable the lowest level RX */
	cvmx_ग_लिखो_csr(CVMX_ASXX_RX_PRT_EN(पूर्णांकerface),
		       cvmx_पढ़ो_csr(CVMX_ASXX_RX_PRT_EN(पूर्णांकerface)) &
				     ~(1 << index));

	स_रखो(pko_mem_queue_qos_save, 0, माप(pko_mem_queue_qos_save));
	/* Disable all queues so that TX should become idle */
	क्रम (i = 0; i < cvmx_pko_get_num_queues(ipd_port); i++) अणु
		पूर्णांक queue = cvmx_pko_get_base_queue(ipd_port) + i;
		cvmx_ग_लिखो_csr(CVMX_PKO_REG_READ_IDX, queue);
		pko_mem_queue_qos.u64 = cvmx_पढ़ो_csr(CVMX_PKO_MEM_QUEUE_QOS);
		pko_mem_queue_qos.s.pid = ipd_port;
		pko_mem_queue_qos.s.qid = queue;
		pko_mem_queue_qos_save[i] = pko_mem_queue_qos;
		pko_mem_queue_qos.s.qos_mask = 0;
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_QUEUE_QOS, pko_mem_queue_qos.u64);
	पूर्ण

	/* Disable backpressure */
	gmx_tx_ovr_bp.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_TX_OVR_BP(पूर्णांकerface));
	gmx_tx_ovr_bp_save = gmx_tx_ovr_bp;
	gmx_tx_ovr_bp.s.bp &= ~(1 << index);
	gmx_tx_ovr_bp.s.en |= 1 << index;
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_OVR_BP(पूर्णांकerface), gmx_tx_ovr_bp.u64);
	cvmx_पढ़ो_csr(CVMX_GMXX_TX_OVR_BP(पूर्णांकerface));

	/*
	 * Poll the GMX state machine रुकोing क्रम it to become
	 * idle. Preferably we should only change speed when it is
	 * idle. If it करोesn't become idle we will still करो the speed
	 * change, but there is a slight chance that GMX will
	 * lockup.
	 */
	cvmx_ग_लिखो_csr(CVMX_NPI_DBG_SELECT,
		       पूर्णांकerface * 0x800 + index * 0x100 + 0x880);
	CVMX_WAIT_FOR_FIELD64(CVMX_DBG_DATA, जोड़ cvmx_dbg_data, data & 7,
			==, 0, 10000);
	CVMX_WAIT_FOR_FIELD64(CVMX_DBG_DATA, जोड़ cvmx_dbg_data, data & 0xf,
			==, 0, 10000);

	/* Disable the port beक्रमe we make any changes */
	new_gmx_cfg.s.en = 0;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), new_gmx_cfg.u64);
	cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));

	/* Set full/half duplex */
	अगर (cvmx_octeon_is_pass1())
		/* Half duplex is broken क्रम 38XX Pass 1 */
		new_gmx_cfg.s.duplex = 1;
	अन्यथा अगर (!link_info.s.link_up)
		/* Force full duplex on करोwn links */
		new_gmx_cfg.s.duplex = 1;
	अन्यथा
		new_gmx_cfg.s.duplex = link_info.s.full_duplex;

	/* Set the link speed. Anything unknown is set to 1Gbps */
	अगर (link_info.s.speed == 10) अणु
		new_gmx_cfg.s.slotसमय = 0;
		new_gmx_cfg.s.speed = 0;
	पूर्ण अन्यथा अगर (link_info.s.speed == 100) अणु
		new_gmx_cfg.s.slotसमय = 0;
		new_gmx_cfg.s.speed = 0;
	पूर्ण अन्यथा अणु
		new_gmx_cfg.s.slotसमय = 1;
		new_gmx_cfg.s.speed = 1;
	पूर्ण

	/* Adjust the घड़ीs */
	अगर (link_info.s.speed == 10) अणु
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_CLK(index, पूर्णांकerface), 50);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_SLOT(index, पूर्णांकerface), 0x40);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_BURST(index, पूर्णांकerface), 0);
	पूर्ण अन्यथा अगर (link_info.s.speed == 100) अणु
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_CLK(index, पूर्णांकerface), 5);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_SLOT(index, पूर्णांकerface), 0x40);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_BURST(index, पूर्णांकerface), 0);
	पूर्ण अन्यथा अणु
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_CLK(index, पूर्णांकerface), 1);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_SLOT(index, पूर्णांकerface), 0x200);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_BURST(index, पूर्णांकerface), 0x2000);
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN30XX) || OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
		अगर ((link_info.s.speed == 10) || (link_info.s.speed == 100)) अणु
			जोड़ cvmx_gmxx_inf_mode mode;
			mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));

	/*
	 * Port	 .en  .type  .p0mii  Configuration
	 * ----	 ---  -----  ------  -----------------------------------------
	 *  X	   0	 X	X    All links are disabled.
	 *  0	   1	 X	0    Port 0 is RGMII
	 *  0	   1	 X	1    Port 0 is MII
	 *  1	   1	 0	X    Ports 1 and 2 are configured as RGMII ports.
	 *  1	   1	 1	X    Port 1: GMII/MII; Port 2: disabled. GMII or
	 *			     MII port is selected by GMX_PRT1_CFG[SPEED].
	 */

			/* In MII mode, CLK_CNT = 1. */
			अगर (((index == 0) && (mode.s.p0mii == 1))
			    || ((index != 0) && (mode.s.type == 1))) अणु
				cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_CLK
					       (index, पूर्णांकerface), 1);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Do a पढ़ो to make sure all setup stuff is complete */
	cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));

	/* Save the new GMX setting without enabling the port */
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), new_gmx_cfg.u64);

	/* Enable the lowest level RX */
	cvmx_ग_लिखो_csr(CVMX_ASXX_RX_PRT_EN(पूर्णांकerface),
		       cvmx_पढ़ो_csr(CVMX_ASXX_RX_PRT_EN(पूर्णांकerface)) | (1 <<
									index));

	/* Re-enable the TX path */
	क्रम (i = 0; i < cvmx_pko_get_num_queues(ipd_port); i++) अणु
		पूर्णांक queue = cvmx_pko_get_base_queue(ipd_port) + i;
		cvmx_ग_लिखो_csr(CVMX_PKO_REG_READ_IDX, queue);
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_QUEUE_QOS,
			       pko_mem_queue_qos_save[i].u64);
	पूर्ण

	/* Restore backpressure */
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_OVR_BP(पूर्णांकerface), gmx_tx_ovr_bp_save.u64);

	/* Restore the GMX enable state. Port config is complete */
	new_gmx_cfg.s.en = original_gmx_cfg.s.en;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), new_gmx_cfg.u64);

	वापस result;
पूर्ण
