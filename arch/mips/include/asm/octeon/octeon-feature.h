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
 * File defining checks क्रम dअगरferent Octeon features.
 */

#अगर_अघोषित __OCTEON_FEATURE_H__
#घोषणा __OCTEON_FEATURE_H__
#समावेश <यंत्र/octeon/cvmx-mio-defs.h>
#समावेश <यंत्र/octeon/cvmx-rnm-defs.h>

क्रमागत octeon_feature अणु
	/* CN68XX uses port kinds क्रम packet पूर्णांकerface */
	OCTEON_FEATURE_PKND,
	/* CN68XX has dअगरferent fields in word0 - word2 */
	OCTEON_FEATURE_CN68XX_WQE,
	/*
	 * Octeon models in the CN5XXX family and higher support
	 * atomic add inकाष्ठाions to memory (saa/saad).
	 */
	OCTEON_FEATURE_SAAD,
	/* Does this Octeon support the ZIP offload engine? */
	OCTEON_FEATURE_ZIP,
	OCTEON_FEATURE_DORM_CRYPTO,
	/* Does this Octeon support PCI express? */
	OCTEON_FEATURE_PCIE,
	/* Does this Octeon support SRIOs */
	OCTEON_FEATURE_SRIO,
	/*  Does this Octeon support Interlaken */
	OCTEON_FEATURE_ILK,
	/* Some Octeon models support पूर्णांकernal memory क्रम storing
	 * cryptographic keys */
	OCTEON_FEATURE_KEY_MEMORY,
	/* Octeon has a LED controller क्रम banks of बाह्यal LEDs */
	OCTEON_FEATURE_LED_CONTROLLER,
	/* Octeon has a trace buffer */
	OCTEON_FEATURE_TRA,
	/* Octeon has a management port */
	OCTEON_FEATURE_MGMT_PORT,
	/* Octeon has a raid unit */
	OCTEON_FEATURE_RAID,
	/* Octeon has a builtin USB */
	OCTEON_FEATURE_USB,
	/* Octeon IPD can run without using work queue entries */
	OCTEON_FEATURE_NO_WPTR,
	/* Octeon has DFA state machines */
	OCTEON_FEATURE_DFA,
	/* Octeon MDIO block supports clause 45 transactions क्रम 10
	 * Gig support */
	OCTEON_FEATURE_MDIO_CLAUSE_45,
	/*
	 *  CN52XX and CN56XX used a block named NPEI क्रम PCIe
	 *  access. Newer chips replaced this with SLI+DPI.
	 */
	OCTEON_FEATURE_NPEI,
	OCTEON_FEATURE_HFA,
	OCTEON_FEATURE_DFM,
	OCTEON_FEATURE_CIU2,
	OCTEON_FEATURE_CIU3,
	/* Octeon has FPA first seen on 78XX */
	OCTEON_FEATURE_FPA3,
	OCTEON_FEATURE_FAU,
	OCTEON_MAX_FEATURE
पूर्ण;

क्रमागत octeon_feature_bits अणु
	OCTEON_HAS_CRYPTO = 0x0001,	/* Crypto acceleration using COP2 */
पूर्ण;
बाह्य क्रमागत octeon_feature_bits __octeon_feature_bits;

/**
 * octeon_has_crypto() - Check अगर this OCTEON has crypto acceleration support.
 *
 * Returns: Non-zero अगर the feature exists. Zero अगर the feature करोes not exist.
 */
अटल अंतरभूत पूर्णांक octeon_has_crypto(व्योम)
अणु
	वापस __octeon_feature_bits & OCTEON_HAS_CRYPTO;
पूर्ण

/**
 * Determine अगर the current Octeon supports a specअगरic feature. These
 * checks have been optimized to be fairly quick, but they should still
 * be kept out of fast path code.
 *
 * @feature: Feature to check क्रम. This should always be a स्थिरant so the
 *		  compiler can हटाओ the चयन statement through optimization.
 *
 * Returns Non zero अगर the feature exists. Zero अगर the feature करोes not
 *	   exist.
 */
अटल अंतरभूत bool octeon_has_feature(क्रमागत octeon_feature feature)
अणु
	चयन (feature) अणु
	हाल OCTEON_FEATURE_SAAD:
		वापस !OCTEON_IS_MODEL(OCTEON_CN3XXX);

	हाल OCTEON_FEATURE_DORM_CRYPTO:
		अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
			जोड़ cvmx_mio_fus_dat2 fus_2;
			fus_2.u64 = cvmx_पढ़ो_csr(CVMX_MIO_FUS_DAT2);
			वापस !fus_2.s.nocrypto && !fus_2.s.nomul && fus_2.s.करोrm_crypto;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण

	हाल OCTEON_FEATURE_PCIE:
		वापस OCTEON_IS_MODEL(OCTEON_CN56XX)
			|| OCTEON_IS_MODEL(OCTEON_CN52XX)
			|| OCTEON_IS_MODEL(OCTEON_CN6XXX)
			|| OCTEON_IS_MODEL(OCTEON_CN7XXX);

	हाल OCTEON_FEATURE_SRIO:
		वापस OCTEON_IS_MODEL(OCTEON_CN63XX)
			|| OCTEON_IS_MODEL(OCTEON_CN66XX);

	हाल OCTEON_FEATURE_ILK:
		वापस (OCTEON_IS_MODEL(OCTEON_CN68XX));

	हाल OCTEON_FEATURE_KEY_MEMORY:
		वापस OCTEON_IS_MODEL(OCTEON_CN38XX)
			|| OCTEON_IS_MODEL(OCTEON_CN58XX)
			|| OCTEON_IS_MODEL(OCTEON_CN56XX)
			|| OCTEON_IS_MODEL(OCTEON_CN6XXX);

	हाल OCTEON_FEATURE_LED_CONTROLLER:
		वापस OCTEON_IS_MODEL(OCTEON_CN38XX)
			|| OCTEON_IS_MODEL(OCTEON_CN58XX)
			|| OCTEON_IS_MODEL(OCTEON_CN56XX);

	हाल OCTEON_FEATURE_TRA:
		वापस !(OCTEON_IS_MODEL(OCTEON_CN30XX)
			 || OCTEON_IS_MODEL(OCTEON_CN50XX));
	हाल OCTEON_FEATURE_MGMT_PORT:
		वापस OCTEON_IS_MODEL(OCTEON_CN56XX)
			|| OCTEON_IS_MODEL(OCTEON_CN52XX)
			|| OCTEON_IS_MODEL(OCTEON_CN6XXX);

	हाल OCTEON_FEATURE_RAID:
		वापस OCTEON_IS_MODEL(OCTEON_CN56XX)
			|| OCTEON_IS_MODEL(OCTEON_CN52XX)
			|| OCTEON_IS_MODEL(OCTEON_CN6XXX);

	हाल OCTEON_FEATURE_USB:
		वापस !(OCTEON_IS_MODEL(OCTEON_CN38XX)
			 || OCTEON_IS_MODEL(OCTEON_CN58XX));

	हाल OCTEON_FEATURE_NO_WPTR:
		वापस (OCTEON_IS_MODEL(OCTEON_CN56XX)
			|| OCTEON_IS_MODEL(OCTEON_CN52XX)
			|| OCTEON_IS_MODEL(OCTEON_CN6XXX))
			  && !OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X)
			  && !OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X);

	हाल OCTEON_FEATURE_MDIO_CLAUSE_45:
		वापस !(OCTEON_IS_MODEL(OCTEON_CN3XXX)
			 || OCTEON_IS_MODEL(OCTEON_CN58XX)
			 || OCTEON_IS_MODEL(OCTEON_CN50XX));

	हाल OCTEON_FEATURE_NPEI:
		वापस OCTEON_IS_MODEL(OCTEON_CN56XX)
			|| OCTEON_IS_MODEL(OCTEON_CN52XX);

	हाल OCTEON_FEATURE_PKND:
		वापस OCTEON_IS_MODEL(OCTEON_CN68XX);

	हाल OCTEON_FEATURE_CN68XX_WQE:
		वापस OCTEON_IS_MODEL(OCTEON_CN68XX);

	हाल OCTEON_FEATURE_CIU2:
		वापस OCTEON_IS_MODEL(OCTEON_CN68XX);
	हाल OCTEON_FEATURE_CIU3:
	हाल OCTEON_FEATURE_FPA3:
		वापस OCTEON_IS_MODEL(OCTEON_CN78XX)
			|| OCTEON_IS_MODEL(OCTEON_CNF75XX)
			|| OCTEON_IS_MODEL(OCTEON_CN73XX);
	हाल OCTEON_FEATURE_FAU:
		वापस !(OCTEON_IS_MODEL(OCTEON_CN78XX)
			 || OCTEON_IS_MODEL(OCTEON_CNF75XX)
			 || OCTEON_IS_MODEL(OCTEON_CN73XX));

	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

#पूर्ण_अगर /* __OCTEON_FEATURE_H__ */
