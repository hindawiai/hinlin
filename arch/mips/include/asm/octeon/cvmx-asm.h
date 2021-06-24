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
 * This is file defines ASM primitives क्रम the executive.
 */
#अगर_अघोषित __CVMX_ASM_H__
#घोषणा __CVMX_ASM_H__

#समावेश <यंत्र/octeon/octeon-model.h>

/* other useful stuff */
#घोषणा CVMX_SYNC यंत्र अस्थिर ("sync" : : : "memory")
/* String version of SYNCW macro क्रम using in अंतरभूत यंत्र स्थिरructs */
#घोषणा CVMX_SYNCW_STR "syncw\nsyncw\n"
#अगर_घोषित __OCTEON__

/* Deprecated, will be हटाओd in future release */
#घोषणा CVMX_SYNCIO यंत्र अस्थिर ("nop")

#घोषणा CVMX_SYNCIOBDMA यंत्र अस्थिर ("synciobdma" : : : "memory")

/* Deprecated, will be हटाओd in future release */
#घोषणा CVMX_SYNCIOALL यंत्र अस्थिर ("nop")

/*
 * We actually use two syncw inकाष्ठाions in a row when we need a ग_लिखो
 * memory barrier. This is because the CN3XXX series of Octeons have
 * errata Core-401. This can cause a single syncw to not enक्रमce
 * ordering under very rare conditions. Even अगर it is rare, better safe
 * than sorry.
 */
#घोषणा CVMX_SYNCW यंत्र अस्थिर ("syncw\n\tsyncw" : : : "memory")

/*
 * Define new sync inकाष्ठाions to be normal SYNC inकाष्ठाions क्रम
 * operating प्रणालीs that use thपढ़ोs.
 */
#घोषणा CVMX_SYNCWS CVMX_SYNCW
#घोषणा CVMX_SYNCS  CVMX_SYNC
#घोषणा CVMX_SYNCWS_STR CVMX_SYNCW_STR
#अन्यथा
/*
 * Not using a Cavium compiler, always use the slower sync so the
 * assembler stays happy.
 */
/* Deprecated, will be हटाओd in future release */
#घोषणा CVMX_SYNCIO यंत्र अस्थिर ("nop")

#घोषणा CVMX_SYNCIOBDMA यंत्र अस्थिर ("sync" : : : "memory")

/* Deprecated, will be हटाओd in future release */
#घोषणा CVMX_SYNCIOALL यंत्र अस्थिर ("nop")

#घोषणा CVMX_SYNCW यंत्र अस्थिर ("sync" : : : "memory")
#घोषणा CVMX_SYNCWS CVMX_SYNCW
#घोषणा CVMX_SYNCS  CVMX_SYNC
#घोषणा CVMX_SYNCWS_STR CVMX_SYNCW_STR
#पूर्ण_अगर

/*
 * CVMX_PREPARE_FOR_STORE makes each byte of the block unpredictable
 * (actually old value or zero) until that byte is stored to (by this or
 * another processor. Note that the value of each byte is not only
 * unpredictable, but may also change again - up until the poपूर्णांक when one
 * of the cores stores to the byte.
 */
#घोषणा CVMX_PREPARE_FOR_STORE(address, offset) \
	यंत्र अस्थिर ("pref 30, " CVMX_TMP_STR(offset) "(%[rbase])" : : \
	[rbase] "d" (address))
/*
 * This is a command headed to the L2 controller to tell it to clear
 * its dirty bit क्रम a block. Basically, SW is telling HW that the
 * current version of the block will not be used.
 */
#घोषणा CVMX_DONT_WRITE_BACK(address, offset) \
	यंत्र अस्थिर ("pref 29, " CVMX_TMP_STR(offset) "(%[rbase])" : : \
	[rbase] "d" (address))

/* flush stores, invalidate entire icache */
#घोषणा CVMX_ICACHE_INVALIDATE \
	अणु CVMX_SYNC; यंत्र अस्थिर ("synci 0($0)" : : ); पूर्ण

/* flush stores, invalidate entire icache */
#घोषणा CVMX_ICACHE_INVALIDATE2 \
	अणु CVMX_SYNC; यंत्र अस्थिर ("cache 0, 0($0)" : : ); पूर्ण

/* complete prefetches, invalidate entire dcache */
#घोषणा CVMX_DCACHE_INVALIDATE \
	अणु CVMX_SYNC; यंत्र अस्थिर ("cache 9, 0($0)" : : ); पूर्ण

#घोषणा CVMX_CACHE(op, address, offset)					\
	यंत्र अस्थिर ("cache " CVMX_TMP_STR(op) ", " CVMX_TMP_STR(offset) "(%[rbase])" \
		: : [rbase] "d" (address) )
/* fetch and lock the state. */
#घोषणा CVMX_CACHE_LCKL2(address, offset) CVMX_CACHE(31, address, offset)
/* unlock the state. */
#घोषणा CVMX_CACHE_WBIL2(address, offset) CVMX_CACHE(23, address, offset)
/* invalidate the cache block and clear the USED bits क्रम the block */
#घोषणा CVMX_CACHE_WBIL2I(address, offset) CVMX_CACHE(3, address, offset)
/* load भव tag and data क्रम the L2 cache block पूर्णांकo L2C_TAD0_TAG रेजिस्टर */
#घोषणा CVMX_CACHE_LTGL2I(address, offset) CVMX_CACHE(7, address, offset)

#घोषणा CVMX_POP(result, input) \
	यंत्र ("pop %[rd],%[rs]" : [rd] "=d" (result) : [rs] "d" (input))
#घोषणा CVMX_DPOP(result, input) \
	यंत्र ("dpop %[rd],%[rs]" : [rd] "=d" (result) : [rs] "d" (input))

/* some new cop0-like stuff */
#घोषणा CVMX_RDHWR(result, regstr) \
	यंत्र अस्थिर ("rdhwr %[rt],$" CVMX_TMP_STR(regstr) : [rt] "=d" (result))
#घोषणा CVMX_RDHWRNV(result, regstr) \
	यंत्र ("rdhwr %[rt],$" CVMX_TMP_STR(regstr) : [rt] "=d" (result))
#पूर्ण_अगर /* __CVMX_ASM_H__ */
