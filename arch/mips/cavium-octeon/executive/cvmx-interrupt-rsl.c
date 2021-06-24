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
 * Utility functions to decode Octeon's RSL_INT_BLOCKS
 * पूर्णांकerrupts पूर्णांकo error messages.
 */

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-asxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-gmxx-defs.h>

#अगर_अघोषित PRINT_ERROR
#घोषणा PRINT_ERROR(क्रमmat, ...)
#पूर्ण_अगर

व्योम __cvmx_पूर्णांकerrupt_gmxx_rxx_पूर्णांक_en_enable(पूर्णांक index, पूर्णांक block);

/**
 * Enable ASX error पूर्णांकerrupts that exist on CN3XXX, CN50XX, and
 * CN58XX.
 *
 * @block:  Interface to enable 0-1
 */
व्योम __cvmx_पूर्णांकerrupt_asxx_enable(पूर्णांक block)
अणु
	पूर्णांक mask;
	जोड़ cvmx_asxx_पूर्णांक_en csr;
	/*
	 * CN38XX and CN58XX have two पूर्णांकerfaces with 4 ports per
	 * पूर्णांकerface. All other chips have a max of 3 ports on
	 * पूर्णांकerface 0
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX))
		mask = 0xf;	/* Set enables क्रम 4 ports */
	अन्यथा
		mask = 0x7;	/* Set enables क्रम 3 ports */

	/* Enable पूर्णांकerface पूर्णांकerrupts */
	csr.u64 = cvmx_पढ़ो_csr(CVMX_ASXX_INT_EN(block));
	csr.s.txpsh = mask;
	csr.s.txpop = mask;
	csr.s.ovrflw = mask;
	cvmx_ग_लिखो_csr(CVMX_ASXX_INT_EN(block), csr.u64);
पूर्ण
/**
 * Enable GMX error reporting क्रम the supplied पूर्णांकerface
 *
 * @पूर्णांकerface: Interface to enable
 */
व्योम __cvmx_पूर्णांकerrupt_gmxx_enable(पूर्णांक पूर्णांकerface)
अणु
	जोड़ cvmx_gmxx_inf_mode mode;
	जोड़ cvmx_gmxx_tx_पूर्णांक_en gmx_tx_पूर्णांक_en;
	पूर्णांक num_ports;
	पूर्णांक index;

	mode.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));

	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
		अगर (mode.s.en) अणु
			चयन (mode.cn52xx.mode) अणु
			हाल 1: /* XAUI */
				num_ports = 1;
				अवरोध;
			हाल 2: /* SGMII */
			हाल 3: /* PICMG */
				num_ports = 4;
				अवरोध;
			शेष:	/* Disabled */
				num_ports = 0;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			num_ports = 0;
	पूर्ण अन्यथा अणु
		अगर (mode.s.en) अणु
			अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)
			    || OCTEON_IS_MODEL(OCTEON_CN58XX)) अणु
				/*
				 * SPI on CN38XX and CN58XX report all
				 * errors through port 0.  RGMII needs
				 * to check all 4 ports
				 */
				अगर (mode.s.type)
					num_ports = 1;
				अन्यथा
					num_ports = 4;
			पूर्ण अन्यथा अणु
				/*
				 * CN30XX, CN31XX, and CN50XX have two
				 * or three ports. GMII and MII has 2,
				 * RGMII has three
				 */
				अगर (mode.s.type)
					num_ports = 2;
				अन्यथा
					num_ports = 3;
			पूर्ण
		पूर्ण अन्यथा
			num_ports = 0;
	पूर्ण

	gmx_tx_पूर्णांक_en.u64 = 0;
	अगर (num_ports) अणु
		अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)
		    || OCTEON_IS_MODEL(OCTEON_CN58XX))
			gmx_tx_पूर्णांक_en.cn38xx.ncb_nxa = 1;
		gmx_tx_पूर्णांक_en.s.pko_nxa = 1;
	पूर्ण
	gmx_tx_पूर्णांक_en.s.undflw = (1 << num_ports) - 1;
	cvmx_ग_लिखो_csr(CVMX_GMXX_TX_INT_EN(पूर्णांकerface), gmx_tx_पूर्णांक_en.u64);
	क्रम (index = 0; index < num_ports; index++)
		__cvmx_पूर्णांकerrupt_gmxx_rxx_पूर्णांक_en_enable(index, पूर्णांकerface);
पूर्ण
