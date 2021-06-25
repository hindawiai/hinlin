<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2009 Cavium Networks
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
 * Automatically generated functions useful क्रम enabling
 * and decoding RSL_INT_BLOCKS पूर्णांकerrupts.
 *
 */

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-gmxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-pcsx-defs.h>
#समावेश <यंत्र/octeon/cvmx-pcsxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-spxx-defs.h>
#समावेश <यंत्र/octeon/cvmx-stxx-defs.h>

#अगर_अघोषित PRINT_ERROR
#घोषणा PRINT_ERROR(क्रमmat, ...)
#पूर्ण_अगर


/**
 * __cvmx_पूर्णांकerrupt_gmxx_rxx_पूर्णांक_en_enable enables all पूर्णांकerrupt bits in cvmx_gmxx_rxx_पूर्णांक_en_t
 */
व्योम __cvmx_पूर्णांकerrupt_gmxx_rxx_पूर्णांक_en_enable(पूर्णांक index, पूर्णांक block)
अणु
	जोड़ cvmx_gmxx_rxx_पूर्णांक_en gmx_rx_पूर्णांक_en;
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_INT_REG(index, block),
		       cvmx_पढ़ो_csr(CVMX_GMXX_RXX_INT_REG(index, block)));
	gmx_rx_पूर्णांक_en.u64 = 0;
	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX)) अणु
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_29_63 */
		gmx_rx_पूर्णांक_en.s.hg2cc = 1;
		gmx_rx_पूर्णांक_en.s.hg2fld = 1;
		gmx_rx_पूर्णांक_en.s.undat = 1;
		gmx_rx_पूर्णांक_en.s.uneop = 1;
		gmx_rx_पूर्णांक_en.s.unsop = 1;
		gmx_rx_पूर्णांक_en.s.bad_term = 1;
		gmx_rx_पूर्णांक_en.s.bad_seq = 1;
		gmx_rx_पूर्णांक_en.s.rem_fault = 1;
		gmx_rx_पूर्णांक_en.s.loc_fault = 1;
		gmx_rx_पूर्णांक_en.s.छोड़ो_drp = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_16_18 */
		/*gmx_rx_पूर्णांक_en.s.अगरgerr = 1; */
		/*gmx_rx_पूर्णांक_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_पूर्णांक_en.s.falerr = 1; // False carrier error or extend error after slotसमय */
		/*gmx_rx_पूर्णांक_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_पूर्णांक_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_पूर्णांक_en.s.ovrerr = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_9_9 */
		gmx_rx_पूर्णांक_en.s.skperr = 1;
		gmx_rx_पूर्णांक_en.s.rcverr = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_5_6 */
		/*gmx_rx_पूर्णांक_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.jabber = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_2_2 */
		gmx_rx_पूर्णांक_en.s.carext = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_0_0 */
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN30XX)) अणु
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_19_63 */
		/*gmx_rx_पूर्णांक_en.s.phy_dupx = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_spd = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_link = 1; */
		/*gmx_rx_पूर्णांक_en.s.अगरgerr = 1; */
		/*gmx_rx_पूर्णांक_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_पूर्णांक_en.s.falerr = 1; // False carrier error or extend error after slotसमय */
		/*gmx_rx_पूर्णांक_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_पूर्णांक_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_पूर्णांक_en.s.ovrerr = 1;
		gmx_rx_पूर्णांक_en.s.niberr = 1;
		gmx_rx_पूर्णांक_en.s.skperr = 1;
		gmx_rx_पूर्णांक_en.s.rcverr = 1;
		/*gmx_rx_पूर्णांक_en.s.lenerr = 1; // Length errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.alnerr = 1;
		/*gmx_rx_पूर्णांक_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.jabber = 1;
		gmx_rx_पूर्णांक_en.s.maxerr = 1;
		gmx_rx_पूर्णांक_en.s.carext = 1;
		gmx_rx_पूर्णांक_en.s.minerr = 1;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_20_63 */
		gmx_rx_पूर्णांक_en.s.छोड़ो_drp = 1;
		/*gmx_rx_पूर्णांक_en.s.phy_dupx = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_spd = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_link = 1; */
		/*gmx_rx_पूर्णांक_en.s.अगरgerr = 1; */
		/*gmx_rx_पूर्णांक_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_पूर्णांक_en.s.falerr = 1; // False carrier error or extend error after slotसमय */
		/*gmx_rx_पूर्णांक_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_पूर्णांक_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_पूर्णांक_en.s.ovrerr = 1;
		gmx_rx_पूर्णांक_en.s.niberr = 1;
		gmx_rx_पूर्णांक_en.s.skperr = 1;
		gmx_rx_पूर्णांक_en.s.rcverr = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_6_6 */
		gmx_rx_पूर्णांक_en.s.alnerr = 1;
		/*gmx_rx_पूर्णांक_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.jabber = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_2_2 */
		gmx_rx_पूर्णांक_en.s.carext = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_0_0 */
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)) अणु
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_19_63 */
		/*gmx_rx_पूर्णांक_en.s.phy_dupx = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_spd = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_link = 1; */
		/*gmx_rx_पूर्णांक_en.s.अगरgerr = 1; */
		/*gmx_rx_पूर्णांक_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_पूर्णांक_en.s.falerr = 1; // False carrier error or extend error after slotसमय */
		/*gmx_rx_पूर्णांक_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_पूर्णांक_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_पूर्णांक_en.s.ovrerr = 1;
		gmx_rx_पूर्णांक_en.s.niberr = 1;
		gmx_rx_पूर्णांक_en.s.skperr = 1;
		gmx_rx_पूर्णांक_en.s.rcverr = 1;
		/*gmx_rx_पूर्णांक_en.s.lenerr = 1; // Length errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.alnerr = 1;
		/*gmx_rx_पूर्णांक_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.jabber = 1;
		gmx_rx_पूर्णांक_en.s.maxerr = 1;
		gmx_rx_पूर्णांक_en.s.carext = 1;
		gmx_rx_पूर्णांक_en.s.minerr = 1;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN31XX)) अणु
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_19_63 */
		/*gmx_rx_पूर्णांक_en.s.phy_dupx = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_spd = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_link = 1; */
		/*gmx_rx_पूर्णांक_en.s.अगरgerr = 1; */
		/*gmx_rx_पूर्णांक_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_पूर्णांक_en.s.falerr = 1; // False carrier error or extend error after slotसमय */
		/*gmx_rx_पूर्णांक_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_पूर्णांक_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_पूर्णांक_en.s.ovrerr = 1;
		gmx_rx_पूर्णांक_en.s.niberr = 1;
		gmx_rx_पूर्णांक_en.s.skperr = 1;
		gmx_rx_पूर्णांक_en.s.rcverr = 1;
		/*gmx_rx_पूर्णांक_en.s.lenerr = 1; // Length errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.alnerr = 1;
		/*gmx_rx_पूर्णांक_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.jabber = 1;
		gmx_rx_पूर्णांक_en.s.maxerr = 1;
		gmx_rx_पूर्णांक_en.s.carext = 1;
		gmx_rx_पूर्णांक_en.s.minerr = 1;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN58XX)) अणु
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_20_63 */
		gmx_rx_पूर्णांक_en.s.छोड़ो_drp = 1;
		/*gmx_rx_पूर्णांक_en.s.phy_dupx = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_spd = 1; */
		/*gmx_rx_पूर्णांक_en.s.phy_link = 1; */
		/*gmx_rx_पूर्णांक_en.s.अगरgerr = 1; */
		/*gmx_rx_पूर्णांक_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_पूर्णांक_en.s.falerr = 1; // False carrier error or extend error after slotसमय */
		/*gmx_rx_पूर्णांक_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_पूर्णांक_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_पूर्णांक_en.s.ovrerr = 1;
		gmx_rx_पूर्णांक_en.s.niberr = 1;
		gmx_rx_पूर्णांक_en.s.skperr = 1;
		gmx_rx_पूर्णांक_en.s.rcverr = 1;
		/*gmx_rx_पूर्णांक_en.s.lenerr = 1; // Length errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.alnerr = 1;
		/*gmx_rx_पूर्णांक_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.jabber = 1;
		gmx_rx_पूर्णांक_en.s.maxerr = 1;
		gmx_rx_पूर्णांक_en.s.carext = 1;
		gmx_rx_पूर्णांक_en.s.minerr = 1;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_29_63 */
		gmx_rx_पूर्णांक_en.s.hg2cc = 1;
		gmx_rx_पूर्णांक_en.s.hg2fld = 1;
		gmx_rx_पूर्णांक_en.s.undat = 1;
		gmx_rx_पूर्णांक_en.s.uneop = 1;
		gmx_rx_पूर्णांक_en.s.unsop = 1;
		gmx_rx_पूर्णांक_en.s.bad_term = 1;
		gmx_rx_पूर्णांक_en.s.bad_seq = 0;
		gmx_rx_पूर्णांक_en.s.rem_fault = 1;
		gmx_rx_पूर्णांक_en.s.loc_fault = 0;
		gmx_rx_पूर्णांक_en.s.छोड़ो_drp = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_16_18 */
		/*gmx_rx_पूर्णांक_en.s.अगरgerr = 1; */
		/*gmx_rx_पूर्णांक_en.s.coldet = 1; // Collision detect */
		/*gmx_rx_पूर्णांक_en.s.falerr = 1; // False carrier error or extend error after slotसमय */
		/*gmx_rx_पूर्णांक_en.s.rsverr = 1; // RGMII reserved opcodes */
		/*gmx_rx_पूर्णांक_en.s.pcterr = 1; // Bad Preamble / Protocol */
		gmx_rx_पूर्णांक_en.s.ovrerr = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_9_9 */
		gmx_rx_पूर्णांक_en.s.skperr = 1;
		gmx_rx_पूर्णांक_en.s.rcverr = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_5_6 */
		/*gmx_rx_पूर्णांक_en.s.fcserr = 1; // FCS errors are handled when we get work */
		gmx_rx_पूर्णांक_en.s.jabber = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_2_2 */
		gmx_rx_पूर्णांक_en.s.carext = 1;
		/* Skipping gmx_rx_पूर्णांक_en.s.reserved_0_0 */
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_GMXX_RXX_INT_EN(index, block), gmx_rx_पूर्णांक_en.u64);
पूर्ण
/**
 * __cvmx_पूर्णांकerrupt_pcsx_पूर्णांकx_en_reg_enable enables all पूर्णांकerrupt bits in cvmx_pcsx_पूर्णांकx_en_reg_t
 */
व्योम __cvmx_पूर्णांकerrupt_pcsx_पूर्णांकx_en_reg_enable(पूर्णांक index, पूर्णांक block)
अणु
	जोड़ cvmx_pcsx_पूर्णांकx_en_reg pcs_पूर्णांक_en_reg;
	cvmx_ग_लिखो_csr(CVMX_PCSX_INTX_REG(index, block),
		       cvmx_पढ़ो_csr(CVMX_PCSX_INTX_REG(index, block)));
	pcs_पूर्णांक_en_reg.u64 = 0;
	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX)) अणु
		/* Skipping pcs_पूर्णांक_en_reg.s.reserved_12_63 */
		/*pcs_पूर्णांक_en_reg.s.dup = 1; // This happens during normal operation */
		pcs_पूर्णांक_en_reg.s.sync_bad_en = 1;
		pcs_पूर्णांक_en_reg.s.an_bad_en = 1;
		pcs_पूर्णांक_en_reg.s.rxlock_en = 1;
		pcs_पूर्णांक_en_reg.s.rxbad_en = 1;
		/*pcs_पूर्णांक_en_reg.s.rxerr_en = 1; // This happens during normal operation */
		pcs_पूर्णांक_en_reg.s.txbad_en = 1;
		pcs_पूर्णांक_en_reg.s.txfअगरo_en = 1;
		pcs_पूर्णांक_en_reg.s.txfअगरu_en = 1;
		pcs_पूर्णांक_en_reg.s.an_err_en = 1;
		/*pcs_पूर्णांक_en_reg.s.xmit_en = 1; // This happens during normal operation */
		/*pcs_पूर्णांक_en_reg.s.lnkspd_en = 1; // This happens during normal operation */
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
		/* Skipping pcs_पूर्णांक_en_reg.s.reserved_12_63 */
		/*pcs_पूर्णांक_en_reg.s.dup = 1; // This happens during normal operation */
		pcs_पूर्णांक_en_reg.s.sync_bad_en = 1;
		pcs_पूर्णांक_en_reg.s.an_bad_en = 1;
		pcs_पूर्णांक_en_reg.s.rxlock_en = 1;
		pcs_पूर्णांक_en_reg.s.rxbad_en = 1;
		/*pcs_पूर्णांक_en_reg.s.rxerr_en = 1; // This happens during normal operation */
		pcs_पूर्णांक_en_reg.s.txbad_en = 1;
		pcs_पूर्णांक_en_reg.s.txfअगरo_en = 1;
		pcs_पूर्णांक_en_reg.s.txfअगरu_en = 1;
		pcs_पूर्णांक_en_reg.s.an_err_en = 1;
		/*pcs_पूर्णांक_en_reg.s.xmit_en = 1; // This happens during normal operation */
		/*pcs_पूर्णांक_en_reg.s.lnkspd_en = 1; // This happens during normal operation */
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_PCSX_INTX_EN_REG(index, block), pcs_पूर्णांक_en_reg.u64);
पूर्ण
/**
 * __cvmx_पूर्णांकerrupt_pcsxx_पूर्णांक_en_reg_enable enables all पूर्णांकerrupt bits in cvmx_pcsxx_पूर्णांक_en_reg_t
 */
व्योम __cvmx_पूर्णांकerrupt_pcsxx_पूर्णांक_en_reg_enable(पूर्णांक index)
अणु
	जोड़ cvmx_pcsxx_पूर्णांक_en_reg pcsx_पूर्णांक_en_reg;
	cvmx_ग_लिखो_csr(CVMX_PCSXX_INT_REG(index),
		       cvmx_पढ़ो_csr(CVMX_PCSXX_INT_REG(index)));
	pcsx_पूर्णांक_en_reg.u64 = 0;
	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX)) अणु
		/* Skipping pcsx_पूर्णांक_en_reg.s.reserved_6_63 */
		pcsx_पूर्णांक_en_reg.s.algnlos_en = 1;
		pcsx_पूर्णांक_en_reg.s.synlos_en = 1;
		pcsx_पूर्णांक_en_reg.s.bitlckls_en = 1;
		pcsx_पूर्णांक_en_reg.s.rxsynbad_en = 1;
		pcsx_पूर्णांक_en_reg.s.rxbad_en = 1;
		pcsx_पूर्णांक_en_reg.s.txflt_en = 1;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
		/* Skipping pcsx_पूर्णांक_en_reg.s.reserved_6_63 */
		pcsx_पूर्णांक_en_reg.s.algnlos_en = 1;
		pcsx_पूर्णांक_en_reg.s.synlos_en = 1;
		pcsx_पूर्णांक_en_reg.s.bitlckls_en = 0;	/* Happens अगर XAUI module is not installed */
		pcsx_पूर्णांक_en_reg.s.rxsynbad_en = 1;
		pcsx_पूर्णांक_en_reg.s.rxbad_en = 1;
		pcsx_पूर्णांक_en_reg.s.txflt_en = 1;
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_PCSXX_INT_EN_REG(index), pcsx_पूर्णांक_en_reg.u64);
पूर्ण

/**
 * __cvmx_पूर्णांकerrupt_spxx_पूर्णांक_msk_enable enables all पूर्णांकerrupt bits in cvmx_spxx_पूर्णांक_msk_t
 */
व्योम __cvmx_पूर्णांकerrupt_spxx_पूर्णांक_msk_enable(पूर्णांक index)
अणु
	जोड़ cvmx_spxx_पूर्णांक_msk spx_पूर्णांक_msk;
	cvmx_ग_लिखो_csr(CVMX_SPXX_INT_REG(index),
		       cvmx_पढ़ो_csr(CVMX_SPXX_INT_REG(index)));
	spx_पूर्णांक_msk.u64 = 0;
	अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)) अणु
		/* Skipping spx_पूर्णांक_msk.s.reserved_12_63 */
		spx_पूर्णांक_msk.s.calerr = 1;
		spx_पूर्णांक_msk.s.syncerr = 1;
		spx_पूर्णांक_msk.s.diperr = 1;
		spx_पूर्णांक_msk.s.tpaovr = 1;
		spx_पूर्णांक_msk.s.rsverr = 1;
		spx_पूर्णांक_msk.s.drwnng = 1;
		spx_पूर्णांक_msk.s.clserr = 1;
		spx_पूर्णांक_msk.s.spiovr = 1;
		/* Skipping spx_पूर्णांक_msk.s.reserved_2_3 */
		spx_पूर्णांक_msk.s.abnorm = 1;
		spx_पूर्णांक_msk.s.prtnxa = 1;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN58XX)) अणु
		/* Skipping spx_पूर्णांक_msk.s.reserved_12_63 */
		spx_पूर्णांक_msk.s.calerr = 1;
		spx_पूर्णांक_msk.s.syncerr = 1;
		spx_पूर्णांक_msk.s.diperr = 1;
		spx_पूर्णांक_msk.s.tpaovr = 1;
		spx_पूर्णांक_msk.s.rsverr = 1;
		spx_पूर्णांक_msk.s.drwnng = 1;
		spx_पूर्णांक_msk.s.clserr = 1;
		spx_पूर्णांक_msk.s.spiovr = 1;
		/* Skipping spx_पूर्णांक_msk.s.reserved_2_3 */
		spx_पूर्णांक_msk.s.abnorm = 1;
		spx_पूर्णांक_msk.s.prtnxa = 1;
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_SPXX_INT_MSK(index), spx_पूर्णांक_msk.u64);
पूर्ण
/**
 * __cvmx_पूर्णांकerrupt_stxx_पूर्णांक_msk_enable enables all पूर्णांकerrupt bits in cvmx_stxx_पूर्णांक_msk_t
 */
व्योम __cvmx_पूर्णांकerrupt_stxx_पूर्णांक_msk_enable(पूर्णांक index)
अणु
	जोड़ cvmx_stxx_पूर्णांक_msk stx_पूर्णांक_msk;
	cvmx_ग_लिखो_csr(CVMX_STXX_INT_REG(index),
		       cvmx_पढ़ो_csr(CVMX_STXX_INT_REG(index)));
	stx_पूर्णांक_msk.u64 = 0;
	अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)) अणु
		/* Skipping stx_पूर्णांक_msk.s.reserved_8_63 */
		stx_पूर्णांक_msk.s.frmerr = 1;
		stx_पूर्णांक_msk.s.unxfrm = 1;
		stx_पूर्णांक_msk.s.nosync = 1;
		stx_पूर्णांक_msk.s.diperr = 1;
		stx_पूर्णांक_msk.s.datovr = 1;
		stx_पूर्णांक_msk.s.ovrbst = 1;
		stx_पूर्णांक_msk.s.calpar1 = 1;
		stx_पूर्णांक_msk.s.calpar0 = 1;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN58XX)) अणु
		/* Skipping stx_पूर्णांक_msk.s.reserved_8_63 */
		stx_पूर्णांक_msk.s.frmerr = 1;
		stx_पूर्णांक_msk.s.unxfrm = 1;
		stx_पूर्णांक_msk.s.nosync = 1;
		stx_पूर्णांक_msk.s.diperr = 1;
		stx_पूर्णांक_msk.s.datovr = 1;
		stx_पूर्णांक_msk.s.ovrbst = 1;
		stx_पूर्णांक_msk.s.calpar1 = 1;
		stx_पूर्णांक_msk.s.calpar0 = 1;
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_STXX_INT_MSK(index), stx_पूर्णांक_msk.u64);
पूर्ण
