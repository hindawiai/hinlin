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

/**
 *
 * Helper utilities क्रम qlm_jtag.
 *
 */

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-helper-jtag.h>


/**
 * Initialize the पूर्णांकernal QLM JTAG logic to allow programming
 * of the JTAG chain by the cvmx_helper_qlm_jtag_*() functions.
 * These functions should only be used at the direction of Cavium
 * Networks. Programming incorrect values पूर्णांकo the JTAG chain
 * can cause chip damage.
 */
व्योम cvmx_helper_qlm_jtag_init(व्योम)
अणु
	जोड़ cvmx_ciu_qlm_jtgc jtgc;
	uपूर्णांक32_t घड़ी_भाग = 0;
	uपूर्णांक32_t भागisor = cvmx_sysinfo_get()->cpu_घड़ी_hz / (25 * 1000000);
	भागisor = (भागisor - 1) >> 2;
	/* Convert the भागisor पूर्णांकo a घातer of 2 shअगरt */
	जबतक (भागisor) अणु
		घड़ी_भाग++;
		भागisor = भागisor >> 1;
	पूर्ण

	/*
	 * Clock भागider क्रम QLM JTAG operations.  eclk is भागided by
	 * 2^(CLK_DIV + 2)
	 */
	jtgc.u64 = 0;
	jtgc.s.clk_भाग = घड़ी_भाग;
	jtgc.s.mux_sel = 0;
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX))
		jtgc.s.bypass = 0x3;
	अन्यथा
		jtgc.s.bypass = 0xf;
	cvmx_ग_लिखो_csr(CVMX_CIU_QLM_JTGC, jtgc.u64);
	cvmx_पढ़ो_csr(CVMX_CIU_QLM_JTGC);
पूर्ण

/**
 * Write up to 32bits पूर्णांकo the QLM jtag chain. Bits are shअगरted
 * पूर्णांकo the MSB and out the LSB, so you should shअगरt in the low
 * order bits followed by the high order bits. The JTAG chain is
 * 4 * 268 bits दीर्घ, or 1072.
 *
 * @qlm:    QLM to shअगरt value पूर्णांकo
 * @bits:   Number of bits to shअगरt in (1-32).
 * @data:   Data to shअगरt in. Bit 0 enters the chain first, followed by
 *		 bit 1, etc.
 *
 * Returns The low order bits of the JTAG chain that shअगरted out of the
 *	   circle.
 */
uपूर्णांक32_t cvmx_helper_qlm_jtag_shअगरt(पूर्णांक qlm, पूर्णांक bits, uपूर्णांक32_t data)
अणु
	जोड़ cvmx_ciu_qlm_jtgd jtgd;
	jtgd.u64 = 0;
	jtgd.s.shअगरt = 1;
	jtgd.s.shft_cnt = bits - 1;
	jtgd.s.shft_reg = data;
	अगर (!OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X))
		jtgd.s.select = 1 << qlm;
	cvmx_ग_लिखो_csr(CVMX_CIU_QLM_JTGD, jtgd.u64);
	करो अणु
		jtgd.u64 = cvmx_पढ़ो_csr(CVMX_CIU_QLM_JTGD);
	पूर्ण जबतक (jtgd.s.shअगरt);
	वापस jtgd.s.shft_reg >> (32 - bits);
पूर्ण

/**
 * Shअगरt दीर्घ sequences of zeros पूर्णांकo the QLM JTAG chain. It is
 * common to need to shअगरt more than 32 bits of zeros पूर्णांकo the
 * chain. This function is a convience wrapper around
 * cvmx_helper_qlm_jtag_shअगरt() to shअगरt more than 32 bits of
 * zeros at a समय.
 *
 * @qlm:    QLM to shअगरt zeros पूर्णांकo
 * @bits:
 */
व्योम cvmx_helper_qlm_jtag_shअगरt_zeros(पूर्णांक qlm, पूर्णांक bits)
अणु
	जबतक (bits > 0) अणु
		पूर्णांक n = bits;
		अगर (n > 32)
			n = 32;
		cvmx_helper_qlm_jtag_shअगरt(qlm, n, 0);
		bits -= n;
	पूर्ण
पूर्ण

/**
 * Program the QLM JTAG chain पूर्णांकo all lanes of the QLM. You must
 * have alपढ़ोy shअगरted in 268*4, or 1072 bits पूर्णांकo the JTAG
 * chain. Updating invalid values can possibly cause chip damage.
 *
 * @qlm:    QLM to program
 */
व्योम cvmx_helper_qlm_jtag_update(पूर्णांक qlm)
अणु
	जोड़ cvmx_ciu_qlm_jtgd jtgd;

	/* Update the new data */
	jtgd.u64 = 0;
	jtgd.s.update = 1;
	अगर (!OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X))
		jtgd.s.select = 1 << qlm;
	cvmx_ग_लिखो_csr(CVMX_CIU_QLM_JTGD, jtgd.u64);
	करो अणु
		jtgd.u64 = cvmx_पढ़ो_csr(CVMX_CIU_QLM_JTGD);
	पूर्ण जबतक (jtgd.s.update);
पूर्ण
