<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2016  Cavium Inc. (support@cavium.com).
 *
 */

/*
 * Module to support operations on biपंचांगap of cores. Coremask can be used to
 * select a specअगरic core, a group of cores, or all available cores, क्रम
 * initialization and dअगरferentiation of roles within a single shared binary
 * executable image.
 *
 * The core numbers used in this file are the same value as what is found in
 * the COP0_EBASE रेजिस्टर and the rdhwr 0 inकाष्ठाion.
 *
 * For the CN78XX and other multi-node environments the core numbers are not
 * contiguous.  The core numbers क्रम the CN78XX are as follows:
 *
 * Node 0:	Cores 0 - 47
 * Node 1:	Cores 128 - 175
 * Node 2:	Cores 256 - 303
 * Node 3:	Cores 384 - 431
 *
 */

#अगर_अघोषित __CVMX_COREMASK_H__
#घोषणा __CVMX_COREMASK_H__

#घोषणा CVMX_MIPS_MAX_CORES 1024
/* bits per holder */
#घोषणा CVMX_COREMASK_ELTSZ 64

/* cvmx_coremask_t's size in u64 */
#घोषणा CVMX_COREMASK_BMPSZ (CVMX_MIPS_MAX_CORES / CVMX_COREMASK_ELTSZ)


/* cvmx_coremask_t */
काष्ठा cvmx_coremask अणु
	u64 coremask_biपंचांगap[CVMX_COREMASK_BMPSZ];
पूर्ण;

/*
 * Is ``core'' set in the coremask?
 */
अटल अंतरभूत bool cvmx_coremask_is_core_set(स्थिर काष्ठा cvmx_coremask *pcm,
					    पूर्णांक core)
अणु
	पूर्णांक n, i;

	n = core % CVMX_COREMASK_ELTSZ;
	i = core / CVMX_COREMASK_ELTSZ;

	वापस (pcm->coremask_biपंचांगap[i] & ((u64)1 << n)) != 0;
पूर्ण

/*
 * Make a copy of a coremask
 */
अटल अंतरभूत व्योम cvmx_coremask_copy(काष्ठा cvmx_coremask *dest,
				      स्थिर काष्ठा cvmx_coremask *src)
अणु
	स_नकल(dest, src, माप(*dest));
पूर्ण

/*
 * Set the lower 64-bit of the coremask.
 */
अटल अंतरभूत व्योम cvmx_coremask_set64(काष्ठा cvmx_coremask *pcm,
				       uपूर्णांक64_t coremask_64)
अणु
	pcm->coremask_biपंचांगap[0] = coremask_64;
पूर्ण

/*
 * Clear ``core'' from the coremask.
 */
अटल अंतरभूत व्योम cvmx_coremask_clear_core(काष्ठा cvmx_coremask *pcm, पूर्णांक core)
अणु
	पूर्णांक n, i;

	n = core % CVMX_COREMASK_ELTSZ;
	i = core / CVMX_COREMASK_ELTSZ;
	pcm->coremask_biपंचांगap[i] &= ~(1ull << n);
पूर्ण

#पूर्ण_अगर /* __CVMX_COREMASK_H__ */
