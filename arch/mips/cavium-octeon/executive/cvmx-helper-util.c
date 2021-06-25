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
 * Small helper utilities.
 */
#समावेश <linux/kernel.h>

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>

#समावेश <यंत्र/octeon/cvmx-fpa.h>
#समावेश <यंत्र/octeon/cvmx-pip.h>
#समावेश <यंत्र/octeon/cvmx-pko.h>
#समावेश <यंत्र/octeon/cvmx-ipd.h>
#समावेश <यंत्र/octeon/cvmx-spi.h>

#समावेश <यंत्र/octeon/cvmx-helper.h>
#समावेश <यंत्र/octeon/cvmx-helper-util.h>

#समावेश <यंत्र/octeon/cvmx-ipd-defs.h>

/**
 * Convert a पूर्णांकerface mode पूर्णांकo a human पढ़ोable string
 *
 * @mode:   Mode to convert
 *
 * Returns String
 */
स्थिर अक्षर *cvmx_helper_पूर्णांकerface_mode_to_string(cvmx_helper_पूर्णांकerface_mode_t
						 mode)
अणु
	चयन (mode) अणु
	हाल CVMX_HELPER_INTERFACE_MODE_DISABLED:
		वापस "DISABLED";
	हाल CVMX_HELPER_INTERFACE_MODE_RGMII:
		वापस "RGMII";
	हाल CVMX_HELPER_INTERFACE_MODE_GMII:
		वापस "GMII";
	हाल CVMX_HELPER_INTERFACE_MODE_SPI:
		वापस "SPI";
	हाल CVMX_HELPER_INTERFACE_MODE_PCIE:
		वापस "PCIE";
	हाल CVMX_HELPER_INTERFACE_MODE_XAUI:
		वापस "XAUI";
	हाल CVMX_HELPER_INTERFACE_MODE_SGMII:
		वापस "SGMII";
	हाल CVMX_HELPER_INTERFACE_MODE_PICMG:
		वापस "PICMG";
	हाल CVMX_HELPER_INTERFACE_MODE_NPI:
		वापस "NPI";
	हाल CVMX_HELPER_INTERFACE_MODE_LOOP:
		वापस "LOOP";
	पूर्ण
	वापस "UNKNOWN";
पूर्ण

/**
 * Setup Ranकरोm Early Drop on a specअगरic input queue
 *
 * @queue:  Input queue to setup RED on (0-7)
 * @pass_thresh:
 *		 Packets will begin slowly dropping when there are less than
 *		 this many packet buffers मुक्त in FPA 0.
 * @drop_thresh:
 *		 All incoming packets will be dropped when there are less
 *		 than this many मुक्त packet buffers in FPA 0.
 * Returns Zero on success. Negative on failure
 */
अटल पूर्णांक cvmx_helper_setup_red_queue(पूर्णांक queue, पूर्णांक pass_thresh,
				       पूर्णांक drop_thresh)
अणु
	जोड़ cvmx_ipd_qosx_red_marks red_marks;
	जोड़ cvmx_ipd_red_quex_param red_param;

	/* Set RED to begin dropping packets when there are pass_thresh buffers
	   left. It will linearly drop more packets until reaching drop_thresh
	   buffers */
	red_marks.u64 = 0;
	red_marks.s.drop = drop_thresh;
	red_marks.s.pass = pass_thresh;
	cvmx_ग_लिखो_csr(CVMX_IPD_QOSX_RED_MARKS(queue), red_marks.u64);

	/* Use the actual queue 0 counter, not the average */
	red_param.u64 = 0;
	red_param.s.prb_con =
	    (255ul << 24) / (red_marks.s.pass - red_marks.s.drop);
	red_param.s.avg_con = 1;
	red_param.s.new_con = 255;
	red_param.s.use_pcnt = 1;
	cvmx_ग_लिखो_csr(CVMX_IPD_RED_QUEX_PARAM(queue), red_param.u64);
	वापस 0;
पूर्ण

/**
 * Setup Ranकरोm Early Drop to स्वतःmatically begin dropping packets.
 *
 * @pass_thresh:
 *		 Packets will begin slowly dropping when there are less than
 *		 this many packet buffers मुक्त in FPA 0.
 * @drop_thresh:
 *		 All incoming packets will be dropped when there are less
 *		 than this many मुक्त packet buffers in FPA 0.
 * Returns Zero on success. Negative on failure
 */
पूर्णांक cvmx_helper_setup_red(पूर्णांक pass_thresh, पूर्णांक drop_thresh)
अणु
	जोड़ cvmx_ipd_portx_bp_page_cnt page_cnt;
	जोड़ cvmx_ipd_bp_prt_red_end ipd_bp_prt_red_end;
	जोड़ cvmx_ipd_red_port_enable red_port_enable;
	पूर्णांक queue;
	पूर्णांक पूर्णांकerface;
	पूर्णांक port;

	/* Disable backpressure based on queued buffers. It needs SW support */
	page_cnt.u64 = 0;
	page_cnt.s.bp_enb = 0;
	page_cnt.s.page_cnt = 100;
	क्रम (पूर्णांकerface = 0; पूर्णांकerface < 2; पूर्णांकerface++) अणु
		क्रम (port = cvmx_helper_get_first_ipd_port(पूर्णांकerface);
		     port < cvmx_helper_get_last_ipd_port(पूर्णांकerface); port++)
			cvmx_ग_लिखो_csr(CVMX_IPD_PORTX_BP_PAGE_CNT(port),
				       page_cnt.u64);
	पूर्ण

	क्रम (queue = 0; queue < 8; queue++)
		cvmx_helper_setup_red_queue(queue, pass_thresh, drop_thresh);

	/* Shutoff the dropping based on the per port page count. SW isn't
	   decrementing it right now */
	ipd_bp_prt_red_end.u64 = 0;
	ipd_bp_prt_red_end.s.prt_enb = 0;
	cvmx_ग_लिखो_csr(CVMX_IPD_BP_PRT_RED_END, ipd_bp_prt_red_end.u64);

	red_port_enable.u64 = 0;
	red_port_enable.s.prt_enb = 0xfffffffffull;
	red_port_enable.s.avg_dly = 10000;
	red_port_enable.s.prb_dly = 10000;
	cvmx_ग_लिखो_csr(CVMX_IPD_RED_PORT_ENABLE, red_port_enable.u64);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_setup_red);

/**
 * Setup the common GMX settings that determine the number of
 * ports. These setting apply to almost all configurations of all
 * chips.
 *
 * @पूर्णांकerface: Interface to configure
 * @num_ports: Number of ports on the पूर्णांकerface
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक __cvmx_helper_setup_gmx(पूर्णांक पूर्णांकerface, पूर्णांक num_ports)
अणु
	जोड़ cvmx_gmxx_tx_prts gmx_tx_prts;
	जोड़ cvmx_gmxx_rx_prts gmx_rx_prts;
	जोड़ cvmx_pko_reg_gmx_port_mode pko_mode;
	जोड़ cvmx_gmxx_txx_thresh gmx_tx_thresh;
	पूर्णांक index;

	/* Tell GMX the number of TX ports on this पूर्णांकerface */
	gmx_tx_prts.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_TX_PRTS(पूर्णांकerface));
	gmx_tx_prts.s.prts = num_ports;
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_PRTS(पूर्णांकerface), gmx_tx_prts.u64);

	/* Tell GMX the number of RX ports on this पूर्णांकerface.  This only
	 ** applies to *GMII and XAUI ports */
	अगर (cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface) ==
	    CVMX_HELPER_INTERFACE_MODE_RGMII
	    || cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface) ==
	    CVMX_HELPER_INTERFACE_MODE_SGMII
	    || cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface) ==
	    CVMX_HELPER_INTERFACE_MODE_GMII
	    || cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface) ==
	    CVMX_HELPER_INTERFACE_MODE_XAUI) अणु
		अगर (num_ports > 4) अणु
			cvmx_dम_लिखो("__cvmx_helper_setup_gmx: Illegal "
				     "num_ports\n");
			वापस -1;
		पूर्ण

		gmx_rx_prts.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_RX_PRTS(पूर्णांकerface));
		gmx_rx_prts.s.prts = num_ports;
		cvmx_ग_लिखो_csr(CVMX_GMXX_RX_PRTS(पूर्णांकerface), gmx_rx_prts.u64);
	पूर्ण

	/* Skip setting CVMX_PKO_REG_GMX_PORT_MODE on 30XX, 31XX, and 50XX */
	अगर (!OCTEON_IS_MODEL(OCTEON_CN30XX) && !OCTEON_IS_MODEL(OCTEON_CN31XX)
	    && !OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
		/* Tell PKO the number of ports on this पूर्णांकerface */
		pko_mode.u64 = cvmx_पढ़ो_csr(CVMX_PKO_REG_GMX_PORT_MODE);
		अगर (पूर्णांकerface == 0) अणु
			अगर (num_ports == 1)
				pko_mode.s.mode0 = 4;
			अन्यथा अगर (num_ports == 2)
				pko_mode.s.mode0 = 3;
			अन्यथा अगर (num_ports <= 4)
				pko_mode.s.mode0 = 2;
			अन्यथा अगर (num_ports <= 8)
				pko_mode.s.mode0 = 1;
			अन्यथा
				pko_mode.s.mode0 = 0;
		पूर्ण अन्यथा अणु
			अगर (num_ports == 1)
				pko_mode.s.mode1 = 4;
			अन्यथा अगर (num_ports == 2)
				pko_mode.s.mode1 = 3;
			अन्यथा अगर (num_ports <= 4)
				pko_mode.s.mode1 = 2;
			अन्यथा अगर (num_ports <= 8)
				pko_mode.s.mode1 = 1;
			अन्यथा
				pko_mode.s.mode1 = 0;
		पूर्ण
		cvmx_ग_लिखो_csr(CVMX_PKO_REG_GMX_PORT_MODE, pko_mode.u64);
	पूर्ण

	/*
	 * Set GMX to buffer as much data as possible beक्रमe starting
	 * transmit.  This reduces the chances that we have a TX under
	 * run due to memory contention. Any packet that fits entirely
	 * in the GMX FIFO can never have an under run regardless of
	 * memory load.
	 */
	gmx_tx_thresh.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_TXX_THRESH(0, पूर्णांकerface));
	अगर (OCTEON_IS_MODEL(OCTEON_CN30XX) || OCTEON_IS_MODEL(OCTEON_CN31XX)
	    || OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
		/* These chips have a fixed max threshold of 0x40 */
		gmx_tx_thresh.s.cnt = 0x40;
	पूर्ण अन्यथा अणु
		/* Choose the max value क्रम the number of ports */
		अगर (num_ports <= 1)
			gmx_tx_thresh.s.cnt = 0x100 / 1;
		अन्यथा अगर (num_ports == 2)
			gmx_tx_thresh.s.cnt = 0x100 / 2;
		अन्यथा
			gmx_tx_thresh.s.cnt = 0x100 / 4;
	पूर्ण
	/*
	 * SPI and XAUI can have lots of ports but the GMX hardware
	 * only ever has a max of 4.
	 */
	अगर (num_ports > 4)
		num_ports = 4;
	क्रम (index = 0; index < num_ports; index++)
		cvmx_ग_लिखो_csr(CVMX_GMXX_TXX_THRESH(index, पूर्णांकerface),
			       gmx_tx_thresh.u64);

	वापस 0;
पूर्ण

/**
 * Returns the IPD/PKO port number क्रम a port on the given
 * पूर्णांकerface.
 *
 * @पूर्णांकerface: Interface to use
 * @port:      Port on the पूर्णांकerface
 *
 * Returns IPD/PKO port number
 */
पूर्णांक cvmx_helper_get_ipd_port(पूर्णांक पूर्णांकerface, पूर्णांक port)
अणु
	चयन (पूर्णांकerface) अणु
	हाल 0:
		वापस port;
	हाल 1:
		वापस port + 16;
	हाल 2:
		वापस port + 32;
	हाल 3:
		वापस port + 36;
	हाल 4:
		वापस port + 40;
	हाल 5:
		वापस port + 44;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_get_ipd_port);

/**
 * Returns the पूर्णांकerface number क्रम an IPD/PKO port number.
 *
 * @ipd_port: IPD/PKO port number
 *
 * Returns Interface number
 */
पूर्णांक cvmx_helper_get_पूर्णांकerface_num(पूर्णांक ipd_port)
अणु
	अगर (ipd_port < 16)
		वापस 0;
	अन्यथा अगर (ipd_port < 32)
		वापस 1;
	अन्यथा अगर (ipd_port < 36)
		वापस 2;
	अन्यथा अगर (ipd_port < 40)
		वापस 3;
	अन्यथा अगर (ipd_port < 44)
		वापस 4;
	अन्यथा अगर (ipd_port < 48)
		वापस 5;
	अन्यथा
		cvmx_dम_लिखो("cvmx_helper_get_interface_num: Illegal IPD "
			     "port number\n");

	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_get_पूर्णांकerface_num);

/**
 * Returns the पूर्णांकerface index number क्रम an IPD/PKO port
 * number.
 *
 * @ipd_port: IPD/PKO port number
 *
 * Returns Interface index number
 */
पूर्णांक cvmx_helper_get_पूर्णांकerface_index_num(पूर्णांक ipd_port)
अणु
	अगर (ipd_port < 32)
		वापस ipd_port & 15;
	अन्यथा अगर (ipd_port < 36)
		वापस ipd_port & 3;
	अन्यथा अगर (ipd_port < 40)
		वापस ipd_port & 3;
	अन्यथा अगर (ipd_port < 44)
		वापस ipd_port & 3;
	अन्यथा अगर (ipd_port < 48)
		वापस ipd_port & 3;
	अन्यथा
		cvmx_dम_लिखो("cvmx_helper_get_interface_index_num: "
			     "Illegal IPD port number\n");

	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_helper_get_पूर्णांकerface_index_num);
