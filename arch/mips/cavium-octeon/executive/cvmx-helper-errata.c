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
 * Fixes and workaround क्रम Octeon chip errata. This file
 * contains functions called by cvmx-helper to workaround known
 * chip errata. For the most part, code करोesn't need to call
 * these functions directly.
 *
 */
#समावेश <linux/export.h>

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-helper-jtag.h>

/**
 * Due to errata G-720, the 2nd order CDR circuit on CN52XX pass
 * 1 करोesn't work properly. The following code disables 2nd order
 * CDR क्रम the specअगरied QLM.
 *
 * @qlm:    QLM to disable 2nd order CDR क्रम.
 */
व्योम __cvmx_helper_errata_qlm_disable_2nd_order_cdr(पूर्णांक qlm)
अणु
	पूर्णांक lane;
	cvmx_helper_qlm_jtag_init();
	/* We need to load all four lanes of the QLM, a total of 1072 bits */
	क्रम (lane = 0; lane < 4; lane++) अणु
		/*
		 * Each lane has 268 bits. We need to set
		 * cfg_cdr_incx<67:64> = 3 and cfg_cdr_secord<77> =
		 * 1. All other bits are zero. Bits go in LSB first,
		 * so start off with the zeros क्रम bits <63:0>.
		 */
		cvmx_helper_qlm_jtag_shअगरt_zeros(qlm, 63 - 0 + 1);
		/* cfg_cdr_incx<67:64>=3 */
		cvmx_helper_qlm_jtag_shअगरt(qlm, 67 - 64 + 1, 3);
		/* Zeros क्रम bits <76:68> */
		cvmx_helper_qlm_jtag_shअगरt_zeros(qlm, 76 - 68 + 1);
		/* cfg_cdr_secord<77>=1 */
		cvmx_helper_qlm_jtag_shअगरt(qlm, 77 - 77 + 1, 1);
		/* Zeros क्रम bits <267:78> */
		cvmx_helper_qlm_jtag_shअगरt_zeros(qlm, 267 - 78 + 1);
	पूर्ण
	cvmx_helper_qlm_jtag_update(qlm);
पूर्ण
EXPORT_SYMBOL(__cvmx_helper_errata_qlm_disable_2nd_order_cdr);
