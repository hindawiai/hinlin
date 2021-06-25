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
 * Support library क्रम the SPI
 */
#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>

#समावेश <यंत्र/octeon/cvmx-pko.h>
#समावेश <यंत्र/octeon/cvmx-spi.h>

#समावेश <यंत्र/octeon/cvmx-spxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-stxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-srxx-defs.h>

#घोषणा INVOKE_CB(function_p, args...)		\
	करो अणु					\
		अगर (function_p) अणु		\
			res = function_p(args); \
			अगर (res)		\
				वापस res;	\
		पूर्ण				\
	पूर्ण जबतक (0)

#अगर CVMX_ENABLE_DEBUG_PRINTS
अटल स्थिर अक्षर *modes[] =
    अणु "UNKNOWN", "TX Halfplex", "Rx Halfplex", "Duplex" पूर्ण;
#पूर्ण_अगर

/* Default callbacks, can be overridden
 *  using cvmx_spi_get_callbacks/cvmx_spi_set_callbacks
 */
अटल cvmx_spi_callbacks_t cvmx_spi_callbacks = अणु
	.reset_cb = cvmx_spi_reset_cb,
	.calendar_setup_cb = cvmx_spi_calendar_setup_cb,
	.घड़ी_detect_cb = cvmx_spi_घड़ी_detect_cb,
	.training_cb = cvmx_spi_training_cb,
	.calendar_sync_cb = cvmx_spi_calendar_sync_cb,
	.पूर्णांकerface_up_cb = cvmx_spi_पूर्णांकerface_up_cb
पूर्ण;

/**
 * Get current SPI4 initialization callbacks
 *
 * @callbacks:	Poपूर्णांकer to the callbacks काष्ठाure.to fill
 *
 * Returns Poपूर्णांकer to cvmx_spi_callbacks_t काष्ठाure.
 */
व्योम cvmx_spi_get_callbacks(cvmx_spi_callbacks_t *callbacks)
अणु
	स_नकल(callbacks, &cvmx_spi_callbacks, माप(cvmx_spi_callbacks));
पूर्ण

/**
 * Set new SPI4 initialization callbacks
 *
 * @new_callbacks:  Poपूर्णांकer to an updated callbacks काष्ठाure.
 */
व्योम cvmx_spi_set_callbacks(cvmx_spi_callbacks_t *new_callbacks)
अणु
	स_नकल(&cvmx_spi_callbacks, new_callbacks, माप(cvmx_spi_callbacks));
पूर्ण

/**
 * Initialize and start the SPI पूर्णांकerface.
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम घड़ी synchronization in seconds
 * @num_ports: Number of SPI ports to configure
 *
 * Returns Zero on success, negative of failure.
 */
पूर्णांक cvmx_spi_start_पूर्णांकerface(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode, पूर्णांक समयout,
			     पूर्णांक num_ports)
अणु
	पूर्णांक res = -1;

	अगर (!(OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX)))
		वापस res;

	/* Callback to perक्रमm SPI4 reset */
	INVOKE_CB(cvmx_spi_callbacks.reset_cb, पूर्णांकerface, mode);

	/* Callback to perक्रमm calendar setup */
	INVOKE_CB(cvmx_spi_callbacks.calendar_setup_cb, पूर्णांकerface, mode,
		  num_ports);

	/* Callback to perक्रमm घड़ी detection */
	INVOKE_CB(cvmx_spi_callbacks.घड़ी_detect_cb, पूर्णांकerface, mode, समयout);

	/* Callback to perक्रमm SPI4 link training */
	INVOKE_CB(cvmx_spi_callbacks.training_cb, पूर्णांकerface, mode, समयout);

	/* Callback to perक्रमm calendar sync */
	INVOKE_CB(cvmx_spi_callbacks.calendar_sync_cb, पूर्णांकerface, mode,
		  समयout);

	/* Callback to handle पूर्णांकerface coming up */
	INVOKE_CB(cvmx_spi_callbacks.पूर्णांकerface_up_cb, पूर्णांकerface, mode);

	वापस res;
पूर्ण

/**
 * This routine restarts the SPI पूर्णांकerface after it has lost synchronization
 * with its correspondent प्रणाली.
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम घड़ी synchronization in seconds
 *
 * Returns Zero on success, negative of failure.
 */
पूर्णांक cvmx_spi_restart_पूर्णांकerface(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode, पूर्णांक समयout)
अणु
	पूर्णांक res = -1;

	अगर (!(OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX)))
		वापस res;

	cvmx_dम_लिखो("SPI%d: Restart %s\n", पूर्णांकerface, modes[mode]);

	/* Callback to perक्रमm SPI4 reset */
	INVOKE_CB(cvmx_spi_callbacks.reset_cb, पूर्णांकerface, mode);

	/* NOTE: Calendar setup is not perक्रमmed during restart */
	/*	 Refer to cvmx_spi_start_पूर्णांकerface() क्रम the full sequence */

	/* Callback to perक्रमm घड़ी detection */
	INVOKE_CB(cvmx_spi_callbacks.घड़ी_detect_cb, पूर्णांकerface, mode, समयout);

	/* Callback to perक्रमm SPI4 link training */
	INVOKE_CB(cvmx_spi_callbacks.training_cb, पूर्णांकerface, mode, समयout);

	/* Callback to perक्रमm calendar sync */
	INVOKE_CB(cvmx_spi_callbacks.calendar_sync_cb, पूर्णांकerface, mode,
		  समयout);

	/* Callback to handle पूर्णांकerface coming up */
	INVOKE_CB(cvmx_spi_callbacks.पूर्णांकerface_up_cb, पूर्णांकerface, mode);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_spi_restart_पूर्णांकerface);

/**
 * Callback to perक्रमm SPI4 reset
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
पूर्णांक cvmx_spi_reset_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode)
अणु
	जोड़ cvmx_spxx_dbg_deskew_ctl spxx_dbg_deskew_ctl;
	जोड़ cvmx_spxx_clk_ctl spxx_clk_ctl;
	जोड़ cvmx_spxx_bist_stat spxx_bist_stat;
	जोड़ cvmx_spxx_पूर्णांक_msk spxx_पूर्णांक_msk;
	जोड़ cvmx_stxx_पूर्णांक_msk stxx_पूर्णांक_msk;
	जोड़ cvmx_spxx_trn4_ctl spxx_trn4_ctl;
	पूर्णांक index;
	uपूर्णांक64_t MS = cvmx_sysinfo_get()->cpu_घड़ी_hz / 1000;

	/* Disable SPI error events जबतक we run BIST */
	spxx_पूर्णांक_msk.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_INT_MSK(पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_SPXX_INT_MSK(पूर्णांकerface), 0);
	stxx_पूर्णांक_msk.u64 = cvmx_पढ़ो_csr(CVMX_STXX_INT_MSK(पूर्णांकerface));
	cvmx_ग_लिखो_csr(CVMX_STXX_INT_MSK(पूर्णांकerface), 0);

	/* Run BIST in the SPI पूर्णांकerface */
	cvmx_ग_लिखो_csr(CVMX_SRXX_COM_CTL(पूर्णांकerface), 0);
	cvmx_ग_लिखो_csr(CVMX_STXX_COM_CTL(पूर्णांकerface), 0);
	spxx_clk_ctl.u64 = 0;
	spxx_clk_ctl.s.runbist = 1;
	cvmx_ग_लिखो_csr(CVMX_SPXX_CLK_CTL(पूर्णांकerface), spxx_clk_ctl.u64);
	__delay(10 * MS);
	spxx_bist_stat.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_BIST_STAT(पूर्णांकerface));
	अगर (spxx_bist_stat.s.stat0)
		cvmx_dम_लिखो
		    ("ERROR SPI%d: BIST failed on receive datapath FIFO\n",
		     पूर्णांकerface);
	अगर (spxx_bist_stat.s.stat1)
		cvmx_dम_लिखो("ERROR SPI%d: BIST failed on RX calendar table\n",
			     पूर्णांकerface);
	अगर (spxx_bist_stat.s.stat2)
		cvmx_dम_लिखो("ERROR SPI%d: BIST failed on TX calendar table\n",
			     पूर्णांकerface);

	/* Clear the calendar table after BIST to fix parity errors */
	क्रम (index = 0; index < 32; index++) अणु
		जोड़ cvmx_srxx_spi4_calx srxx_spi4_calx;
		जोड़ cvmx_stxx_spi4_calx stxx_spi4_calx;

		srxx_spi4_calx.u64 = 0;
		srxx_spi4_calx.s.oddpar = 1;
		cvmx_ग_लिखो_csr(CVMX_SRXX_SPI4_CALX(index, पूर्णांकerface),
			       srxx_spi4_calx.u64);

		stxx_spi4_calx.u64 = 0;
		stxx_spi4_calx.s.oddpar = 1;
		cvmx_ग_लिखो_csr(CVMX_STXX_SPI4_CALX(index, पूर्णांकerface),
			       stxx_spi4_calx.u64);
	पूर्ण

	/* Re enable reporting of error पूर्णांकerrupts */
	cvmx_ग_लिखो_csr(CVMX_SPXX_INT_REG(पूर्णांकerface),
		       cvmx_पढ़ो_csr(CVMX_SPXX_INT_REG(पूर्णांकerface)));
	cvmx_ग_लिखो_csr(CVMX_SPXX_INT_MSK(पूर्णांकerface), spxx_पूर्णांक_msk.u64);
	cvmx_ग_लिखो_csr(CVMX_STXX_INT_REG(पूर्णांकerface),
		       cvmx_पढ़ो_csr(CVMX_STXX_INT_REG(पूर्णांकerface)));
	cvmx_ग_लिखो_csr(CVMX_STXX_INT_MSK(पूर्णांकerface), stxx_पूर्णांक_msk.u64);

	/* Setup the CLKDLY right in the middle */
	spxx_clk_ctl.u64 = 0;
	spxx_clk_ctl.s.seetrn = 0;
	spxx_clk_ctl.s.clkdly = 0x10;
	spxx_clk_ctl.s.runbist = 0;
	spxx_clk_ctl.s.statdrv = 0;
	/* This should always be on the opposite edge as statdrv */
	spxx_clk_ctl.s.statrcv = 1;
	spxx_clk_ctl.s.sndtrn = 0;
	spxx_clk_ctl.s.drptrn = 0;
	spxx_clk_ctl.s.rcvtrn = 0;
	spxx_clk_ctl.s.srxdlck = 0;
	cvmx_ग_लिखो_csr(CVMX_SPXX_CLK_CTL(पूर्णांकerface), spxx_clk_ctl.u64);
	__delay(100 * MS);

	/* Reset SRX0 DLL */
	spxx_clk_ctl.s.srxdlck = 1;
	cvmx_ग_लिखो_csr(CVMX_SPXX_CLK_CTL(पूर्णांकerface), spxx_clk_ctl.u64);

	/* Waiting क्रम Inf0 Spi4 RX DLL to lock */
	__delay(100 * MS);

	/* Enable dynamic alignment */
	spxx_trn4_ctl.s.trntest = 0;
	spxx_trn4_ctl.s.jitter = 1;
	spxx_trn4_ctl.s.clr_boot = 1;
	spxx_trn4_ctl.s.set_boot = 0;
	अगर (OCTEON_IS_MODEL(OCTEON_CN58XX))
		spxx_trn4_ctl.s.maxdist = 3;
	अन्यथा
		spxx_trn4_ctl.s.maxdist = 8;
	spxx_trn4_ctl.s.macro_en = 1;
	spxx_trn4_ctl.s.mux_en = 1;
	cvmx_ग_लिखो_csr(CVMX_SPXX_TRN4_CTL(पूर्णांकerface), spxx_trn4_ctl.u64);

	spxx_dbg_deskew_ctl.u64 = 0;
	cvmx_ग_लिखो_csr(CVMX_SPXX_DBG_DESKEW_CTL(पूर्णांकerface),
		       spxx_dbg_deskew_ctl.u64);

	वापस 0;
पूर्ण

/**
 * Callback to setup calendar and miscellaneous settings beक्रमe घड़ी detection
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @num_ports: Number of ports to configure on SPI
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
पूर्णांक cvmx_spi_calendar_setup_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
			       पूर्णांक num_ports)
अणु
	पूर्णांक port;
	पूर्णांक index;
	अगर (mode & CVMX_SPI_MODE_RX_HALFPLEX) अणु
		जोड़ cvmx_srxx_com_ctl srxx_com_ctl;
		जोड़ cvmx_srxx_spi4_stat srxx_spi4_stat;

		/* SRX0 number of Ports */
		srxx_com_ctl.u64 = 0;
		srxx_com_ctl.s.prts = num_ports - 1;
		srxx_com_ctl.s.st_en = 0;
		srxx_com_ctl.s.inf_en = 0;
		cvmx_ग_लिखो_csr(CVMX_SRXX_COM_CTL(पूर्णांकerface), srxx_com_ctl.u64);

		/* SRX0 Calendar Table. This round robbins through all ports */
		port = 0;
		index = 0;
		जबतक (port < num_ports) अणु
			जोड़ cvmx_srxx_spi4_calx srxx_spi4_calx;
			srxx_spi4_calx.u64 = 0;
			srxx_spi4_calx.s.prt0 = port++;
			srxx_spi4_calx.s.prt1 = port++;
			srxx_spi4_calx.s.prt2 = port++;
			srxx_spi4_calx.s.prt3 = port++;
			srxx_spi4_calx.s.oddpar =
			    ~(cvmx_dpop(srxx_spi4_calx.u64) & 1);
			cvmx_ग_लिखो_csr(CVMX_SRXX_SPI4_CALX(index, पूर्णांकerface),
				       srxx_spi4_calx.u64);
			index++;
		पूर्ण
		srxx_spi4_stat.u64 = 0;
		srxx_spi4_stat.s.len = num_ports;
		srxx_spi4_stat.s.m = 1;
		cvmx_ग_लिखो_csr(CVMX_SRXX_SPI4_STAT(पूर्णांकerface),
			       srxx_spi4_stat.u64);
	पूर्ण

	अगर (mode & CVMX_SPI_MODE_TX_HALFPLEX) अणु
		जोड़ cvmx_stxx_arb_ctl stxx_arb_ctl;
		जोड़ cvmx_gmxx_tx_spi_max gmxx_tx_spi_max;
		जोड़ cvmx_gmxx_tx_spi_thresh gmxx_tx_spi_thresh;
		जोड़ cvmx_gmxx_tx_spi_ctl gmxx_tx_spi_ctl;
		जोड़ cvmx_stxx_spi4_stat stxx_spi4_stat;
		जोड़ cvmx_stxx_spi4_dat stxx_spi4_dat;

		/* STX0 Config */
		stxx_arb_ctl.u64 = 0;
		stxx_arb_ctl.s.igntpa = 0;
		stxx_arb_ctl.s.mपूर्णांकrn = 0;
		cvmx_ग_लिखो_csr(CVMX_STXX_ARB_CTL(पूर्णांकerface), stxx_arb_ctl.u64);

		gmxx_tx_spi_max.u64 = 0;
		gmxx_tx_spi_max.s.max1 = 8;
		gmxx_tx_spi_max.s.max2 = 4;
		gmxx_tx_spi_max.s.slice = 0;
		cvmx_ग_लिखो_csr(CVMX_GMXX_TX_SPI_MAX(पूर्णांकerface),
			       gmxx_tx_spi_max.u64);

		gmxx_tx_spi_thresh.u64 = 0;
		gmxx_tx_spi_thresh.s.thresh = 4;
		cvmx_ग_लिखो_csr(CVMX_GMXX_TX_SPI_THRESH(पूर्णांकerface),
			       gmxx_tx_spi_thresh.u64);

		gmxx_tx_spi_ctl.u64 = 0;
		gmxx_tx_spi_ctl.s.tpa_clr = 0;
		gmxx_tx_spi_ctl.s.cont_pkt = 0;
		cvmx_ग_लिखो_csr(CVMX_GMXX_TX_SPI_CTL(पूर्णांकerface),
			       gmxx_tx_spi_ctl.u64);

		/* STX0 Training Control */
		stxx_spi4_dat.u64 = 0;
		/*Minimum needed by dynamic alignment */
		stxx_spi4_dat.s.alpha = 32;
		stxx_spi4_dat.s.max_t = 0xFFFF; /*Minimum पूर्णांकerval is 0x20 */
		cvmx_ग_लिखो_csr(CVMX_STXX_SPI4_DAT(पूर्णांकerface),
			       stxx_spi4_dat.u64);

		/* STX0 Calendar Table. This round robbins through all ports */
		port = 0;
		index = 0;
		जबतक (port < num_ports) अणु
			जोड़ cvmx_stxx_spi4_calx stxx_spi4_calx;
			stxx_spi4_calx.u64 = 0;
			stxx_spi4_calx.s.prt0 = port++;
			stxx_spi4_calx.s.prt1 = port++;
			stxx_spi4_calx.s.prt2 = port++;
			stxx_spi4_calx.s.prt3 = port++;
			stxx_spi4_calx.s.oddpar =
			    ~(cvmx_dpop(stxx_spi4_calx.u64) & 1);
			cvmx_ग_लिखो_csr(CVMX_STXX_SPI4_CALX(index, पूर्णांकerface),
				       stxx_spi4_calx.u64);
			index++;
		पूर्ण
		stxx_spi4_stat.u64 = 0;
		stxx_spi4_stat.s.len = num_ports;
		stxx_spi4_stat.s.m = 1;
		cvmx_ग_लिखो_csr(CVMX_STXX_SPI4_STAT(पूर्णांकerface),
			       stxx_spi4_stat.u64);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Callback to perक्रमm घड़ी detection
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम घड़ी synchronization in seconds
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
पूर्णांक cvmx_spi_घड़ी_detect_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode, पूर्णांक समयout)
अणु
	पूर्णांक घड़ी_प्रकारransitions;
	जोड़ cvmx_spxx_clk_stat stat;
	uपूर्णांक64_t समयout_समय;
	uपूर्णांक64_t MS = cvmx_sysinfo_get()->cpu_घड़ी_hz / 1000;

	/*
	 * Regardless of operating mode, both Tx and Rx घड़ीs must be
	 * present क्रम the SPI पूर्णांकerface to operate.
	 */
	cvmx_dम_लिखो("SPI%d: Waiting to see TsClk...\n", पूर्णांकerface);
	समयout_समय = cvmx_get_cycle() + 1000ull * MS * समयout;
	/*
	 * Require 100 घड़ी transitions in order to aव्योम any noise
	 * in the beginning.
	 */
	घड़ी_प्रकारransitions = 100;
	करो अणु
		stat.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_CLK_STAT(पूर्णांकerface));
		अगर (stat.s.s4clk0 && stat.s.s4clk1 && घड़ी_प्रकारransitions) अणु
			/*
			 * We've seen a घड़ी transition, so decrement
			 * the number we still need.
			 */
			घड़ी_प्रकारransitions--;
			cvmx_ग_लिखो_csr(CVMX_SPXX_CLK_STAT(पूर्णांकerface), stat.u64);
			stat.s.s4clk0 = 0;
			stat.s.s4clk1 = 0;
		पूर्ण
		अगर (cvmx_get_cycle() > समयout_समय) अणु
			cvmx_dम_लिखो("SPI%d: Timeout\n", पूर्णांकerface);
			वापस -1;
		पूर्ण
	पूर्ण जबतक (stat.s.s4clk0 == 0 || stat.s.s4clk1 == 0);

	cvmx_dम_लिखो("SPI%d: Waiting to see RsClk...\n", पूर्णांकerface);
	समयout_समय = cvmx_get_cycle() + 1000ull * MS * समयout;
	/*
	 * Require 100 घड़ी transitions in order to aव्योम any noise in the
	 * beginning.
	 */
	घड़ी_प्रकारransitions = 100;
	करो अणु
		stat.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_CLK_STAT(पूर्णांकerface));
		अगर (stat.s.d4clk0 && stat.s.d4clk1 && घड़ी_प्रकारransitions) अणु
			/*
			 * We've seen a घड़ी transition, so decrement
			 * the number we still need
			 */
			घड़ी_प्रकारransitions--;
			cvmx_ग_लिखो_csr(CVMX_SPXX_CLK_STAT(पूर्णांकerface), stat.u64);
			stat.s.d4clk0 = 0;
			stat.s.d4clk1 = 0;
		पूर्ण
		अगर (cvmx_get_cycle() > समयout_समय) अणु
			cvmx_dम_लिखो("SPI%d: Timeout\n", पूर्णांकerface);
			वापस -1;
		पूर्ण
	पूर्ण जबतक (stat.s.d4clk0 == 0 || stat.s.d4clk1 == 0);

	वापस 0;
पूर्ण

/**
 * Callback to perक्रमm link training
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम link to be trained (in seconds)
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
पूर्णांक cvmx_spi_training_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode, पूर्णांक समयout)
अणु
	जोड़ cvmx_spxx_trn4_ctl spxx_trn4_ctl;
	जोड़ cvmx_spxx_clk_stat stat;
	uपूर्णांक64_t MS = cvmx_sysinfo_get()->cpu_घड़ी_hz / 1000;
	uपूर्णांक64_t समयout_समय = cvmx_get_cycle() + 1000ull * MS * समयout;
	पूर्णांक rx_training_needed;

	/* SRX0 & STX0 Inf0 Links are configured - begin training */
	जोड़ cvmx_spxx_clk_ctl spxx_clk_ctl;
	spxx_clk_ctl.u64 = 0;
	spxx_clk_ctl.s.seetrn = 0;
	spxx_clk_ctl.s.clkdly = 0x10;
	spxx_clk_ctl.s.runbist = 0;
	spxx_clk_ctl.s.statdrv = 0;
	/* This should always be on the opposite edge as statdrv */
	spxx_clk_ctl.s.statrcv = 1;
	spxx_clk_ctl.s.sndtrn = 1;
	spxx_clk_ctl.s.drptrn = 1;
	spxx_clk_ctl.s.rcvtrn = 1;
	spxx_clk_ctl.s.srxdlck = 1;
	cvmx_ग_लिखो_csr(CVMX_SPXX_CLK_CTL(पूर्णांकerface), spxx_clk_ctl.u64);
	__delay(1000 * MS);

	/* SRX0 clear the boot bit */
	spxx_trn4_ctl.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_TRN4_CTL(पूर्णांकerface));
	spxx_trn4_ctl.s.clr_boot = 1;
	cvmx_ग_लिखो_csr(CVMX_SPXX_TRN4_CTL(पूर्णांकerface), spxx_trn4_ctl.u64);

	/* Wait क्रम the training sequence to complete */
	cvmx_dम_लिखो("SPI%d: Waiting for training\n", पूर्णांकerface);
	__delay(1000 * MS);
	/* Wait a really दीर्घ समय here */
	समयout_समय = cvmx_get_cycle() + 1000ull * MS * 600;
	/*
	 * The HRM says we must रुको क्रम 34 + 16 * MAXDIST training sequences.
	 * We'll be pessimistic and रुको क्रम a lot more.
	 */
	rx_training_needed = 500;
	करो अणु
		stat.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_CLK_STAT(पूर्णांकerface));
		अगर (stat.s.srxtrn && rx_training_needed) अणु
			rx_training_needed--;
			cvmx_ग_लिखो_csr(CVMX_SPXX_CLK_STAT(पूर्णांकerface), stat.u64);
			stat.s.srxtrn = 0;
		पूर्ण
		अगर (cvmx_get_cycle() > समयout_समय) अणु
			cvmx_dम_लिखो("SPI%d: Timeout\n", पूर्णांकerface);
			वापस -1;
		पूर्ण
	पूर्ण जबतक (stat.s.srxtrn == 0);

	वापस 0;
पूर्ण

/**
 * Callback to perक्रमm calendar data synchronization
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम calendar data in seconds
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
पूर्णांक cvmx_spi_calendar_sync_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode, पूर्णांक समयout)
अणु
	uपूर्णांक64_t MS = cvmx_sysinfo_get()->cpu_घड़ी_hz / 1000;
	अगर (mode & CVMX_SPI_MODE_RX_HALFPLEX) अणु
		/* SRX0 पूर्णांकerface should be good, send calendar data */
		जोड़ cvmx_srxx_com_ctl srxx_com_ctl;
		cvmx_dम_लिखो
		    ("SPI%d: Rx is synchronized, start sending calendar data\n",
		     पूर्णांकerface);
		srxx_com_ctl.u64 = cvmx_पढ़ो_csr(CVMX_SRXX_COM_CTL(पूर्णांकerface));
		srxx_com_ctl.s.inf_en = 1;
		srxx_com_ctl.s.st_en = 1;
		cvmx_ग_लिखो_csr(CVMX_SRXX_COM_CTL(पूर्णांकerface), srxx_com_ctl.u64);
	पूर्ण

	अगर (mode & CVMX_SPI_MODE_TX_HALFPLEX) अणु
		/* STX0 has achieved sync */
		/* The corespondant board should be sending calendar data */
		/* Enable the STX0 STAT receiver. */
		जोड़ cvmx_spxx_clk_stat stat;
		uपूर्णांक64_t समयout_समय;
		जोड़ cvmx_stxx_com_ctl stxx_com_ctl;
		stxx_com_ctl.u64 = 0;
		stxx_com_ctl.s.st_en = 1;
		cvmx_ग_लिखो_csr(CVMX_STXX_COM_CTL(पूर्णांकerface), stxx_com_ctl.u64);

		/* Waiting क्रम calendar sync on STX0 STAT */
		cvmx_dम_लिखो("SPI%d: Waiting to sync on STX[%d] STAT\n",
			     पूर्णांकerface, पूर्णांकerface);
		समयout_समय = cvmx_get_cycle() + 1000ull * MS * समयout;
		/* SPX0_CLK_STAT - SPX0_CLK_STAT[STXCAL] should be 1 (bit10) */
		करो अणु
			stat.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_CLK_STAT(पूर्णांकerface));
			अगर (cvmx_get_cycle() > समयout_समय) अणु
				cvmx_dम_लिखो("SPI%d: Timeout\n", पूर्णांकerface);
				वापस -1;
			पूर्ण
		पूर्ण जबतक (stat.s.stxcal == 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Callback to handle पूर्णांकerface up
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
पूर्णांक cvmx_spi_पूर्णांकerface_up_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode)
अणु
	जोड़ cvmx_gmxx_rxx_frm_min gmxx_rxx_frm_min;
	जोड़ cvmx_gmxx_rxx_frm_max gmxx_rxx_frm_max;
	जोड़ cvmx_gmxx_rxx_jabber gmxx_rxx_jabber;

	अगर (mode & CVMX_SPI_MODE_RX_HALFPLEX) अणु
		जोड़ cvmx_srxx_com_ctl srxx_com_ctl;
		srxx_com_ctl.u64 = cvmx_पढ़ो_csr(CVMX_SRXX_COM_CTL(पूर्णांकerface));
		srxx_com_ctl.s.inf_en = 1;
		cvmx_ग_लिखो_csr(CVMX_SRXX_COM_CTL(पूर्णांकerface), srxx_com_ctl.u64);
		cvmx_dम_लिखो("SPI%d: Rx is now up\n", पूर्णांकerface);
	पूर्ण

	अगर (mode & CVMX_SPI_MODE_TX_HALFPLEX) अणु
		जोड़ cvmx_stxx_com_ctl stxx_com_ctl;
		stxx_com_ctl.u64 = cvmx_पढ़ो_csr(CVMX_STXX_COM_CTL(पूर्णांकerface));
		stxx_com_ctl.s.inf_en = 1;
		cvmx_ग_लिखो_csr(CVMX_STXX_COM_CTL(पूर्णांकerface), stxx_com_ctl.u64);
		cvmx_dम_लिखो("SPI%d: Tx is now up\n", पूर्णांकerface);
	पूर्ण

	gmxx_rxx_frm_min.u64 = 0;
	gmxx_rxx_frm_min.s.len = 64;
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_FRM_MIN(0, पूर्णांकerface),
		       gmxx_rxx_frm_min.u64);
	gmxx_rxx_frm_max.u64 = 0;
	gmxx_rxx_frm_max.s.len = 64 * 1024 - 4;
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_FRM_MAX(0, पूर्णांकerface),
		       gmxx_rxx_frm_max.u64);
	gmxx_rxx_jabber.u64 = 0;
	gmxx_rxx_jabber.s.cnt = 64 * 1024 - 4;
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_JABBER(0, पूर्णांकerface), gmxx_rxx_jabber.u64);

	वापस 0;
पूर्ण
