<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/dst.h>

#समावेश "octeon-ethernet.h"
#समावेश "ethernet-defines.h"
#समावेश "ethernet-util.h"

अटल पूर्णांक number_spi_ports;
अटल पूर्णांक need_retrain[2] = अणु 0, 0 पूर्ण;

अटल व्योम cvm_oct_spxx_पूर्णांक_pr(जोड़ cvmx_spxx_पूर्णांक_reg spx_पूर्णांक_reg, पूर्णांक index)
अणु
	अगर (spx_पूर्णांक_reg.s.spf)
		pr_err("SPI%d: SRX Spi4 interface down\n", index);
	अगर (spx_पूर्णांक_reg.s.calerr)
		pr_err("SPI%d: SRX Spi4 Calendar table parity error\n", index);
	अगर (spx_पूर्णांक_reg.s.syncerr)
		pr_err("SPI%d: SRX Consecutive Spi4 DIP4 errors have exceeded SPX_ERR_CTL[ERRCNT]\n",
		       index);
	अगर (spx_पूर्णांक_reg.s.diperr)
		pr_err("SPI%d: SRX Spi4 DIP4 error\n", index);
	अगर (spx_पूर्णांक_reg.s.tpaovr)
		pr_err("SPI%d: SRX Selected port has hit TPA overflow\n",
		       index);
	अगर (spx_पूर्णांक_reg.s.rsverr)
		pr_err("SPI%d: SRX Spi4 reserved control word detected\n",
		       index);
	अगर (spx_पूर्णांक_reg.s.drwnng)
		pr_err("SPI%d: SRX Spi4 receive FIFO drowning/overflow\n",
		       index);
	अगर (spx_पूर्णांक_reg.s.clserr)
		pr_err("SPI%d: SRX Spi4 packet closed on non-16B alignment without EOP\n",
		       index);
	अगर (spx_पूर्णांक_reg.s.spiovr)
		pr_err("SPI%d: SRX Spi4 async FIFO overflow\n", index);
	अगर (spx_पूर्णांक_reg.s.abnorm)
		pr_err("SPI%d: SRX Abnormal packet termination (ERR bit)\n",
		       index);
	अगर (spx_पूर्णांक_reg.s.prtnxa)
		pr_err("SPI%d: SRX Port out of range\n", index);
पूर्ण

अटल व्योम cvm_oct_stxx_पूर्णांक_pr(जोड़ cvmx_stxx_पूर्णांक_reg stx_पूर्णांक_reg, पूर्णांक index)
अणु
	अगर (stx_पूर्णांक_reg.s.syncerr)
		pr_err("SPI%d: STX Interface encountered a fatal error\n",
		       index);
	अगर (stx_पूर्णांक_reg.s.frmerr)
		pr_err("SPI%d: STX FRMCNT has exceeded STX_DIP_CNT[MAXFRM]\n",
		       index);
	अगर (stx_पूर्णांक_reg.s.unxfrm)
		pr_err("SPI%d: STX Unexpected framing sequence\n", index);
	अगर (stx_पूर्णांक_reg.s.nosync)
		pr_err("SPI%d: STX ERRCNT has exceeded STX_DIP_CNT[MAXDIP]\n",
		       index);
	अगर (stx_पूर्णांक_reg.s.diperr)
		pr_err("SPI%d: STX DIP2 error on the Spi4 Status channel\n",
		       index);
	अगर (stx_पूर्णांक_reg.s.datovr)
		pr_err("SPI%d: STX Spi4 FIFO overflow error\n", index);
	अगर (stx_पूर्णांक_reg.s.ovrbst)
		pr_err("SPI%d: STX Transmit packet burst too big\n", index);
	अगर (stx_पूर्णांक_reg.s.calpar1)
		pr_err("SPI%d: STX Calendar Table Parity Error Bank%d\n",
		       index, 1);
	अगर (stx_पूर्णांक_reg.s.calpar0)
		pr_err("SPI%d: STX Calendar Table Parity Error Bank%d\n",
		       index, 0);
पूर्ण

अटल irqवापस_t cvm_oct_spi_spx_पूर्णांक(पूर्णांक index)
अणु
	जोड़ cvmx_spxx_पूर्णांक_reg spx_पूर्णांक_reg;
	जोड़ cvmx_stxx_पूर्णांक_reg stx_पूर्णांक_reg;

	spx_पूर्णांक_reg.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_INT_REG(index));
	cvmx_ग_लिखो_csr(CVMX_SPXX_INT_REG(index), spx_पूर्णांक_reg.u64);
	अगर (!need_retrain[index]) अणु
		spx_पूर्णांक_reg.u64 &= cvmx_पढ़ो_csr(CVMX_SPXX_INT_MSK(index));
		cvm_oct_spxx_पूर्णांक_pr(spx_पूर्णांक_reg, index);
	पूर्ण

	stx_पूर्णांक_reg.u64 = cvmx_पढ़ो_csr(CVMX_STXX_INT_REG(index));
	cvmx_ग_लिखो_csr(CVMX_STXX_INT_REG(index), stx_पूर्णांक_reg.u64);
	अगर (!need_retrain[index]) अणु
		stx_पूर्णांक_reg.u64 &= cvmx_पढ़ो_csr(CVMX_STXX_INT_MSK(index));
		cvm_oct_stxx_पूर्णांक_pr(stx_पूर्णांक_reg, index);
	पूर्ण

	cvmx_ग_लिखो_csr(CVMX_SPXX_INT_MSK(index), 0);
	cvmx_ग_लिखो_csr(CVMX_STXX_INT_MSK(index), 0);
	need_retrain[index] = 1;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cvm_oct_spi_rml_पूर्णांकerrupt(पूर्णांक cpl, व्योम *dev_id)
अणु
	irqवापस_t वापस_status = IRQ_NONE;
	जोड़ cvmx_npi_rsl_पूर्णांक_blocks rsl_पूर्णांक_blocks;

	/* Check and see अगर this पूर्णांकerrupt was caused by the GMX block */
	rsl_पूर्णांक_blocks.u64 = cvmx_पढ़ो_csr(CVMX_NPI_RSL_INT_BLOCKS);
	अगर (rsl_पूर्णांक_blocks.s.spx1) /* 19 - SPX1_INT_REG & STX1_INT_REG */
		वापस_status = cvm_oct_spi_spx_पूर्णांक(1);

	अगर (rsl_पूर्णांक_blocks.s.spx0) /* 18 - SPX0_INT_REG & STX0_INT_REG */
		वापस_status = cvm_oct_spi_spx_पूर्णांक(0);

	वापस वापस_status;
पूर्ण

अटल व्योम cvm_oct_spi_enable_error_reporting(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_spxx_पूर्णांक_msk spxx_पूर्णांक_msk;
	जोड़ cvmx_stxx_पूर्णांक_msk stxx_पूर्णांक_msk;

	spxx_पूर्णांक_msk.u64 = cvmx_पढ़ो_csr(CVMX_SPXX_INT_MSK(पूर्णांकerface));
	spxx_पूर्णांक_msk.s.calerr = 1;
	spxx_पूर्णांक_msk.s.syncerr = 1;
	spxx_पूर्णांक_msk.s.diperr = 1;
	spxx_पूर्णांक_msk.s.tpaovr = 1;
	spxx_पूर्णांक_msk.s.rsverr = 1;
	spxx_पूर्णांक_msk.s.drwnng = 1;
	spxx_पूर्णांक_msk.s.clserr = 1;
	spxx_पूर्णांक_msk.s.spiovr = 1;
	spxx_पूर्णांक_msk.s.abnorm = 1;
	spxx_पूर्णांक_msk.s.prtnxa = 1;
	cvmx_ग_लिखो_csr(CVMX_SPXX_INT_MSK(पूर्णांकerface), spxx_पूर्णांक_msk.u64);

	stxx_पूर्णांक_msk.u64 = cvmx_पढ़ो_csr(CVMX_STXX_INT_MSK(पूर्णांकerface));
	stxx_पूर्णांक_msk.s.frmerr = 1;
	stxx_पूर्णांक_msk.s.unxfrm = 1;
	stxx_पूर्णांक_msk.s.nosync = 1;
	stxx_पूर्णांक_msk.s.diperr = 1;
	stxx_पूर्णांक_msk.s.datovr = 1;
	stxx_पूर्णांक_msk.s.ovrbst = 1;
	stxx_पूर्णांक_msk.s.calpar1 = 1;
	stxx_पूर्णांक_msk.s.calpar0 = 1;
	cvmx_ग_लिखो_csr(CVMX_STXX_INT_MSK(पूर्णांकerface), stxx_पूर्णांक_msk.u64);
पूर्ण

अटल व्योम cvm_oct_spi_poll(काष्ठा net_device *dev)
अणु
	अटल पूर्णांक spi4000_port;
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	पूर्णांक पूर्णांकerface;

	क्रम (पूर्णांकerface = 0; पूर्णांकerface < 2; पूर्णांकerface++) अणु
		अगर ((priv->port == पूर्णांकerface * 16) && need_retrain[पूर्णांकerface]) अणु
			अगर (cvmx_spi_restart_पूर्णांकerface
			    (पूर्णांकerface, CVMX_SPI_MODE_DUPLEX, 10) == 0) अणु
				need_retrain[पूर्णांकerface] = 0;
				cvm_oct_spi_enable_error_reporting(पूर्णांकerface);
			पूर्ण
		पूर्ण

		/*
		 * The SPI4000 TWSI पूर्णांकerface is very slow. In order
		 * not to bring the प्रणाली to a crawl, we only poll a
		 * single port every second. This means negotiation
		 * speed changes take up to 10 seconds, but at least
		 * we करोn't waste असलurd amounts of समय रुकोing क्रम
		 * TWSI.
		 */
		अगर (priv->port == spi4000_port) अणु
			/*
			 * This function करोes nothing अगर it is called on an
			 * पूर्णांकerface without a SPI4000.
			 */
			cvmx_spi4000_check_speed(पूर्णांकerface, priv->port);
			/*
			 * Normal ordering increments. By decrementing
			 * we only match once per iteration.
			 */
			spi4000_port--;
			अगर (spi4000_port < 0)
				spi4000_port = 10;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक cvm_oct_spi_init(काष्ठा net_device *dev)
अणु
	पूर्णांक r;
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);

	अगर (number_spi_ports == 0) अणु
		r = request_irq(OCTEON_IRQ_RML, cvm_oct_spi_rml_पूर्णांकerrupt,
				IRQF_SHARED, "SPI", &number_spi_ports);
		अगर (r)
			वापस r;
	पूर्ण
	number_spi_ports++;

	अगर (priv->port == 0 || priv->port == 16) अणु
		cvm_oct_spi_enable_error_reporting(INTERFACE(priv->port));
		priv->poll = cvm_oct_spi_poll;
	पूर्ण
	cvm_oct_common_init(dev);
	वापस 0;
पूर्ण

व्योम cvm_oct_spi_uninit(काष्ठा net_device *dev)
अणु
	पूर्णांक पूर्णांकerface;

	cvm_oct_common_uninit(dev);
	number_spi_ports--;
	अगर (number_spi_ports == 0) अणु
		क्रम (पूर्णांकerface = 0; पूर्णांकerface < 2; पूर्णांकerface++) अणु
			cvmx_ग_लिखो_csr(CVMX_SPXX_INT_MSK(पूर्णांकerface), 0);
			cvmx_ग_लिखो_csr(CVMX_STXX_INT_MSK(पूर्णांकerface), 0);
		पूर्ण
		मुक्त_irq(OCTEON_IRQ_RML, &number_spi_ports);
	पूर्ण
पूर्ण
