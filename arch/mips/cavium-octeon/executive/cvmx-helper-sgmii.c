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
 * Functions क्रम SGMII initialization, configuration,
 * and monitoring.
 */

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>

#समावेश <यंत्र/octeon/cvmx-helper.h>
#समावेश <यंत्र/octeon/cvmx-helper-board.h>

#समावेश <यंत्र/octeon/cvmx-gmxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-pcsx-defs.h>
#समावेश <यंत्र/octeon/cvmx-pcsxx-defs.h>

/**
 * Perक्रमm initialization required only once क्रम an SGMII port.
 *
 * @पूर्णांकerface: Interface to init
 * @index:     Index of prot on the पूर्णांकerface
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_sgmii_hardware_init_one_समय(पूर्णांक पूर्णांकerface, पूर्णांक index)
अणु
	स्थिर uपूर्णांक64_t घड़ी_mhz = cvmx_sysinfo_get()->cpu_घड़ी_hz / 1000000;
	जोड़ cvmx_pcsx_miscx_ctl_reg pcs_misc_ctl_reg;
	जोड़ cvmx_pcsx_linkx_समयr_count_reg pcsx_linkx_समयr_count_reg;
	जोड़ cvmx_gmxx_prtx_cfg gmxx_prtx_cfg;

	/* Disable GMX */
	gmxx_prtx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
	gmxx_prtx_cfg.s.en = 0;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), gmxx_prtx_cfg.u64);

	/*
	 * Write PCS*_LINK*_TIMER_COUNT_REG[COUNT] with the
	 * appropriate value. 1000BASE-X specअगरies a 10ms
	 * पूर्णांकerval. SGMII specअगरies a 1.6ms पूर्णांकerval.
	 */
	pcs_misc_ctl_reg.u64 =
	    cvmx_पढ़ो_csr(CVMX_PCSX_MISCX_CTL_REG(index, पूर्णांकerface));
	pcsx_linkx_समयr_count_reg.u64 =
	    cvmx_पढ़ो_csr(CVMX_PCSX_LINKX_TIMER_COUNT_REG(index, पूर्णांकerface));
	अगर (pcs_misc_ctl_reg.s.mode) अणु
		/* 1000BASE-X */
		pcsx_linkx_समयr_count_reg.s.count =
		    (10000ull * घड़ी_mhz) >> 10;
	पूर्ण अन्यथा अणु
		/* SGMII */
		pcsx_linkx_समयr_count_reg.s.count =
		    (1600ull * घड़ी_mhz) >> 10;
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_PCSX_LINKX_TIMER_COUNT_REG(index, पूर्णांकerface),
		       pcsx_linkx_समयr_count_reg.u64);

	/*
	 * Write the advertisement रेजिस्टर to be used as the
	 * tx_Config_Reg<D15:D0> of the स्वतःnegotiation.  In
	 * 1000BASE-X mode, tx_Config_Reg<D15:D0> is PCS*_AN*_ADV_REG.
	 * In SGMII PHY mode, tx_Config_Reg<D15:D0> is
	 * PCS*_SGM*_AN_ADV_REG.  In SGMII MAC mode,
	 * tx_Config_Reg<D15:D0> is the fixed value 0x4001, so this
	 * step can be skipped.
	 */
	अगर (pcs_misc_ctl_reg.s.mode) अणु
		/* 1000BASE-X */
		जोड़ cvmx_pcsx_anx_adv_reg pcsx_anx_adv_reg;
		pcsx_anx_adv_reg.u64 =
		    cvmx_पढ़ो_csr(CVMX_PCSX_ANX_ADV_REG(index, पूर्णांकerface));
		pcsx_anx_adv_reg.s.rem_flt = 0;
		pcsx_anx_adv_reg.s.छोड़ो = 3;
		pcsx_anx_adv_reg.s.hfd = 1;
		pcsx_anx_adv_reg.s.fd = 1;
		cvmx_ग_लिखो_csr(CVMX_PCSX_ANX_ADV_REG(index, पूर्णांकerface),
			       pcsx_anx_adv_reg.u64);
	पूर्ण अन्यथा अणु
		जोड़ cvmx_pcsx_miscx_ctl_reg pcsx_miscx_ctl_reg;
		pcsx_miscx_ctl_reg.u64 =
		    cvmx_पढ़ो_csr(CVMX_PCSX_MISCX_CTL_REG(index, पूर्णांकerface));
		अगर (pcsx_miscx_ctl_reg.s.mac_phy) अणु
			/* PHY Mode */
			जोड़ cvmx_pcsx_sgmx_an_adv_reg pcsx_sgmx_an_adv_reg;
			pcsx_sgmx_an_adv_reg.u64 =
			    cvmx_पढ़ो_csr(CVMX_PCSX_SGMX_AN_ADV_REG
					  (index, पूर्णांकerface));
			pcsx_sgmx_an_adv_reg.s.link = 1;
			pcsx_sgmx_an_adv_reg.s.dup = 1;
			pcsx_sgmx_an_adv_reg.s.speed = 2;
			cvmx_ग_लिखो_csr(CVMX_PCSX_SGMX_AN_ADV_REG
				       (index, पूर्णांकerface),
				       pcsx_sgmx_an_adv_reg.u64);
		पूर्ण अन्यथा अणु
			/* MAC Mode - Nothing to करो */
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Initialize the SERTES link क्रम the first समय or after a loss
 * of link.
 *
 * @पूर्णांकerface: Interface to init
 * @index:     Index of prot on the पूर्णांकerface
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_sgmii_hardware_init_link(पूर्णांक पूर्णांकerface, पूर्णांक index)
अणु
	जोड़ cvmx_pcsx_mrx_control_reg control_reg;

	/*
	 * Take PCS through a reset sequence.
	 * PCS*_MR*_CONTROL_REG[PWR_DN] should be cleared to zero.
	 * Write PCS*_MR*_CONTROL_REG[RESET]=1 (जबतक not changing the
	 * value of the other PCS*_MR*_CONTROL_REG bits).  Read
	 * PCS*_MR*_CONTROL_REG[RESET] until it changes value to
	 * zero.
	 */
	control_reg.u64 =
	    cvmx_पढ़ो_csr(CVMX_PCSX_MRX_CONTROL_REG(index, पूर्णांकerface));
	अगर (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) अणु
		control_reg.s.reset = 1;
		cvmx_ग_लिखो_csr(CVMX_PCSX_MRX_CONTROL_REG(index, पूर्णांकerface),
			       control_reg.u64);
		अगर (CVMX_WAIT_FOR_FIELD64
		    (CVMX_PCSX_MRX_CONTROL_REG(index, पूर्णांकerface),
		     जोड़ cvmx_pcsx_mrx_control_reg, reset, ==, 0, 10000)) अणु
			cvmx_dम_लिखो("SGMII%d: Timeout waiting for port %d "
				     "to finish reset\n",
			     पूर्णांकerface, index);
			वापस -1;
		पूर्ण
	पूर्ण

	/*
	 * Write PCS*_MR*_CONTROL_REG[RST_AN]=1 to ensure a fresh
	 * sgmii negotiation starts.
	 */
	control_reg.s.rst_an = 1;
	control_reg.s.an_en = 1;
	control_reg.s.pwr_dn = 0;
	cvmx_ग_लिखो_csr(CVMX_PCSX_MRX_CONTROL_REG(index, पूर्णांकerface),
		       control_reg.u64);

	/*
	 * Wait क्रम PCS*_MR*_STATUS_REG[AN_CPT] to be set, indicating
	 * that sgmii स्वतःnegotiation is complete. In MAC mode this
	 * isn't an ethernet link, but a link between Octeon and the
	 * PHY.
	 */
	अगर ((cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) &&
	    CVMX_WAIT_FOR_FIELD64(CVMX_PCSX_MRX_STATUS_REG(index, पूर्णांकerface),
				  जोड़ cvmx_pcsx_mrx_status_reg, an_cpt, ==, 1,
				  10000)) अणु
		/* cvmx_dम_लिखो("SGMII%d: Port %d link timeout\n", पूर्णांकerface, index); */
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Configure an SGMII link to the specअगरied speed after the SERTES
 * link is up.
 *
 * @पूर्णांकerface: Interface to init
 * @index:     Index of prot on the पूर्णांकerface
 * @link_info: Link state to configure
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_sgmii_hardware_init_link_speed(पूर्णांक पूर्णांकerface,
							पूर्णांक index,
							जोड़ cvmx_helper_link_info
							link_info)
अणु
	पूर्णांक is_enabled;
	जोड़ cvmx_gmxx_prtx_cfg gmxx_prtx_cfg;
	जोड़ cvmx_pcsx_miscx_ctl_reg pcsx_miscx_ctl_reg;

	/* Disable GMX beक्रमe we make any changes. Remember the enable state */
	gmxx_prtx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
	is_enabled = gmxx_prtx_cfg.s.en;
	gmxx_prtx_cfg.s.en = 0;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), gmxx_prtx_cfg.u64);

	/* Wait क्रम GMX to be idle */
	अगर (CVMX_WAIT_FOR_FIELD64
	    (CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), जोड़ cvmx_gmxx_prtx_cfg,
	     rx_idle, ==, 1, 10000)
	    || CVMX_WAIT_FOR_FIELD64(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface),
				     जोड़ cvmx_gmxx_prtx_cfg, tx_idle, ==, 1,
				     10000)) अणु
		cvmx_dम_लिखो
		    ("SGMII%d: Timeout waiting for port %d to be idle\n",
		     पूर्णांकerface, index);
		वापस -1;
	पूर्ण

	/* Read GMX CFG again to make sure the disable completed */
	gmxx_prtx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));

	/*
	 * Get the misc control क्रम PCS. We will need to set the
	 * duplication amount.
	 */
	pcsx_miscx_ctl_reg.u64 =
	    cvmx_पढ़ो_csr(CVMX_PCSX_MISCX_CTL_REG(index, पूर्णांकerface));

	/*
	 * Use GMXENO to क्रमce the link करोwn अगर the status we get says
	 * it should be करोwn.
	 */
	pcsx_miscx_ctl_reg.s.gmxeno = !link_info.s.link_up;

	/* Only change the duplex setting अगर the link is up */
	अगर (link_info.s.link_up)
		gmxx_prtx_cfg.s.duplex = link_info.s.full_duplex;

	/* Do speed based setting क्रम GMX */
	चयन (link_info.s.speed) अणु
	हाल 10:
		gmxx_prtx_cfg.s.speed = 0;
		gmxx_prtx_cfg.s.speed_msb = 1;
		gmxx_prtx_cfg.s.slotसमय = 0;
		/* Setting from GMX-603 */
		pcsx_miscx_ctl_reg.s.samp_pt = 25;
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_SLOT(index, पूर्णांकerface), 64);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_BURST(index, पूर्णांकerface), 0);
		अवरोध;
	हाल 100:
		gmxx_prtx_cfg.s.speed = 0;
		gmxx_prtx_cfg.s.speed_msb = 0;
		gmxx_prtx_cfg.s.slotसमय = 0;
		pcsx_miscx_ctl_reg.s.samp_pt = 0x5;
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_SLOT(index, पूर्णांकerface), 64);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_BURST(index, पूर्णांकerface), 0);
		अवरोध;
	हाल 1000:
		gmxx_prtx_cfg.s.speed = 1;
		gmxx_prtx_cfg.s.speed_msb = 0;
		gmxx_prtx_cfg.s.slotसमय = 1;
		pcsx_miscx_ctl_reg.s.samp_pt = 1;
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_SLOT(index, पूर्णांकerface), 512);
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_BURST(index, पूर्णांकerface), 8192);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Write the new misc control क्रम PCS */
	cvmx_ग_लिखो_csr(CVMX_PCSX_MISCX_CTL_REG(index, पूर्णांकerface),
		       pcsx_miscx_ctl_reg.u64);

	/* Write the new GMX settings with the port still disabled */
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), gmxx_prtx_cfg.u64);

	/* Read GMX CFG again to make sure the config completed */
	gmxx_prtx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));

	/* Restore the enabled / disabled state */
	gmxx_prtx_cfg.s.en = is_enabled;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), gmxx_prtx_cfg.u64);

	वापस 0;
पूर्ण

/**
 * Bring up the SGMII पूर्णांकerface to be पढ़ोy क्रम packet I/O but
 * leave I/O disabled using the GMX override. This function
 * follows the bringup करोcumented in 10.6.3 of the manual.
 *
 * @पूर्णांकerface: Interface to bringup
 * @num_ports: Number of ports on the पूर्णांकerface
 *
 * Returns Zero on success, negative on failure
 */
अटल पूर्णांक __cvmx_helper_sgmii_hardware_init(पूर्णांक पूर्णांकerface, पूर्णांक num_ports)
अणु
	पूर्णांक index;

	__cvmx_helper_setup_gmx(पूर्णांकerface, num_ports);

	क्रम (index = 0; index < num_ports; index++) अणु
		पूर्णांक ipd_port = cvmx_helper_get_ipd_port(पूर्णांकerface, index);
		__cvmx_helper_sgmii_hardware_init_one_समय(पूर्णांकerface, index);
		/* Linux kernel driver will call ....link_set with the
		 * proper link state. In the simulator there is no
		 * link state polling and hence it is set from
		 * here.
		 */
		अगर (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM)
			__cvmx_helper_sgmii_link_set(ipd_port,
				       __cvmx_helper_sgmii_link_get(ipd_port));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __cvmx_helper_sgmii_क्रमागतerate(पूर्णांक पूर्णांकerface)
अणु
	वापस 4;
पूर्ण
/**
 * Probe a SGMII पूर्णांकerface and determine the number of ports
 * connected to it. The SGMII पूर्णांकerface should still be करोwn after
 * this call.
 *
 * @पूर्णांकerface: Interface to probe
 *
 * Returns Number of ports on the पूर्णांकerface. Zero to disable.
 */
पूर्णांक __cvmx_helper_sgmii_probe(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_gmxx_inf_mode mode;

	/*
	 * Due to errata GMX-700 on CN56XXp1.x and CN52XXp1.x, the
	 * पूर्णांकerface needs to be enabled beक्रमe IPD otherwise per port
	 * backpressure may not work properly
	 */
	mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));
	mode.s.en = 1;
	cvmx_ग_लिखो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface), mode.u64);
	वापस __cvmx_helper_sgmii_क्रमागतerate(पूर्णांकerface);
पूर्ण

/**
 * Bringup and enable a SGMII पूर्णांकerface. After this call packet
 * I/O should be fully functional. This is called with IPD
 * enabled but PKO disabled.
 *
 * @पूर्णांकerface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक __cvmx_helper_sgmii_enable(पूर्णांक पूर्णांकerface)
अणु
	पूर्णांक num_ports = cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface);
	पूर्णांक index;

	__cvmx_helper_sgmii_hardware_init(पूर्णांकerface, num_ports);

	क्रम (index = 0; index < num_ports; index++) अणु
		जोड़ cvmx_gmxx_prtx_cfg gmxx_prtx_cfg;
		gmxx_prtx_cfg.u64 =
		    cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
		gmxx_prtx_cfg.s.en = 1;
		cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface),
			       gmxx_prtx_cfg.u64);
		__cvmx_पूर्णांकerrupt_pcsx_पूर्णांकx_en_reg_enable(index, पूर्णांकerface);
	पूर्ण
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
जोड़ cvmx_helper_link_info __cvmx_helper_sgmii_link_get(पूर्णांक ipd_port)
अणु
	जोड़ cvmx_helper_link_info result;
	जोड़ cvmx_pcsx_miscx_ctl_reg pcs_misc_ctl_reg;
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);
	जोड़ cvmx_pcsx_mrx_control_reg pcsx_mrx_control_reg;

	result.u64 = 0;

	अगर (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM) अणु
		/* The simulator gives you a simulated 1Gbps full duplex link */
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 1000;
		वापस result;
	पूर्ण

	pcsx_mrx_control_reg.u64 =
	    cvmx_पढ़ो_csr(CVMX_PCSX_MRX_CONTROL_REG(index, पूर्णांकerface));
	अगर (pcsx_mrx_control_reg.s.loopbck1) अणु
		/* Force 1Gbps full duplex link क्रम पूर्णांकernal loopback */
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 1000;
		वापस result;
	पूर्ण

	pcs_misc_ctl_reg.u64 =
	    cvmx_पढ़ो_csr(CVMX_PCSX_MISCX_CTL_REG(index, पूर्णांकerface));
	अगर (pcs_misc_ctl_reg.s.mode) अणु
		/* 1000BASE-X */
		/* FIXME */
	पूर्ण अन्यथा अणु
		जोड़ cvmx_pcsx_miscx_ctl_reg pcsx_miscx_ctl_reg;
		pcsx_miscx_ctl_reg.u64 =
		    cvmx_पढ़ो_csr(CVMX_PCSX_MISCX_CTL_REG(index, पूर्णांकerface));
		अगर (pcsx_miscx_ctl_reg.s.mac_phy) अणु
			/* PHY Mode */
			जोड़ cvmx_pcsx_mrx_status_reg pcsx_mrx_status_reg;
			जोड़ cvmx_pcsx_anx_results_reg pcsx_anx_results_reg;

			/*
			 * Don't bother continuing अगर the SERTES low
			 * level link is करोwn
			 */
			pcsx_mrx_status_reg.u64 =
			    cvmx_पढ़ो_csr(CVMX_PCSX_MRX_STATUS_REG
					  (index, पूर्णांकerface));
			अगर (pcsx_mrx_status_reg.s.lnk_st == 0) अणु
				अगर (__cvmx_helper_sgmii_hardware_init_link
				    (पूर्णांकerface, index) != 0)
					वापस result;
			पूर्ण

			/* Read the स्वतःneg results */
			pcsx_anx_results_reg.u64 =
			    cvmx_पढ़ो_csr(CVMX_PCSX_ANX_RESULTS_REG
					  (index, पूर्णांकerface));
			अगर (pcsx_anx_results_reg.s.an_cpt) अणु
				/*
				 * Auto negotiation is complete. Set
				 * status accordingly.
				 */
				result.s.full_duplex =
				    pcsx_anx_results_reg.s.dup;
				result.s.link_up =
				    pcsx_anx_results_reg.s.link_ok;
				चयन (pcsx_anx_results_reg.s.spd) अणु
				हाल 0:
					result.s.speed = 10;
					अवरोध;
				हाल 1:
					result.s.speed = 100;
					अवरोध;
				हाल 2:
					result.s.speed = 1000;
					अवरोध;
				शेष:
					result.s.speed = 0;
					result.s.link_up = 0;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * Auto negotiation isn't
				 * complete. Return link करोwn.
				 */
				result.s.speed = 0;
				result.s.link_up = 0;
			पूर्ण
		पूर्ण अन्यथा अणु	/* MAC Mode */

			result = __cvmx_helper_board_link_get(ipd_port);
		पूर्ण
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
पूर्णांक __cvmx_helper_sgmii_link_set(पूर्णांक ipd_port,
				 जोड़ cvmx_helper_link_info link_info)
अणु
	पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(ipd_port);
	पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(ipd_port);
	__cvmx_helper_sgmii_hardware_init_link(पूर्णांकerface, index);
	वापस __cvmx_helper_sgmii_hardware_init_link_speed(पूर्णांकerface, index,
							    link_info);
पूर्ण
