<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2010 Cavium Networks
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
#अगर_अघोषित __OCTEON_MODEL_H__
#घोषणा __OCTEON_MODEL_H__

/*
 * The defines below should be used with the OCTEON_IS_MODEL() macro
 * to determine what model of chip the software is running on.	Models
 * ending in 'XX' match multiple models (families), जबतक specअगरic
 * models match only that model.  If a pass (revision) is specअगरied,
 * then only that revision will be matched.  Care should be taken when
 * checking क्रम both specअगरic models and families that the specअगरic
 * models are checked क्रम first.  While these defines are similar to
 * the processor ID, they are not पूर्णांकended to be used by anything
 * other that the OCTEON_IS_MODEL framework, and the values are
 * subject to change at anyसमय without notice.
 *
 * NOTE: only the OCTEON_IS_MODEL() macro/function and the OCTEON_CN*
 * macros should be used outside of this file.	All other macros are
 * क्रम पूर्णांकernal use only, and may change without notice.
 */

#घोषणा OCTEON_FAMILY_MASK	0x00ffff00
#घोषणा OCTEON_PRID_MASK	0x00ffffff

/* Flag bits in top byte */
/* Ignores revision in model checks */
#घोषणा OM_IGNORE_REVISION	  0x01000000
/* Check submodels */
#घोषणा OM_CHECK_SUBMODEL	  0x02000000
/* Match all models previous than the one specअगरied */
#घोषणा OM_MATCH_PREVIOUS_MODELS  0x04000000
/* Ignores the minor revison on newer parts */
#घोषणा OM_IGNORE_MINOR_REVISION  0x08000000
#घोषणा OM_FLAG_MASK		  0xff000000

/* Match all cn5XXX Octeon models. */
#घोषणा OM_MATCH_5XXX_FAMILY_MODELS	0x20000000
/* Match all cn6XXX Octeon models. */
#घोषणा OM_MATCH_6XXX_FAMILY_MODELS	0x40000000
/* Match all cnf7XXX Octeon models. */
#घोषणा OM_MATCH_F7XXX_FAMILY_MODELS	0x80000000
/* Match all cn7XXX Octeon models. */
#घोषणा OM_MATCH_7XXX_FAMILY_MODELS     0x10000000
#घोषणा OM_MATCH_FAMILY_MODELS		(OM_MATCH_5XXX_FAMILY_MODELS |	\
					 OM_MATCH_6XXX_FAMILY_MODELS |	\
					 OM_MATCH_F7XXX_FAMILY_MODELS | \
					 OM_MATCH_7XXX_FAMILY_MODELS)
/*
 * CN7XXX models with new revision encoding
 */

#घोषणा OCTEON_CNF75XX_PASS1_0	0x000d9800
#घोषणा OCTEON_CNF75XX		(OCTEON_CNF75XX_PASS1_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CNF75XX_PASS1_X	(OCTEON_CNF75XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)

#घोषणा OCTEON_CN73XX_PASS1_0	0x000d9700
#घोषणा OCTEON_CN73XX_PASS1_1	0x000d9701
#घोषणा OCTEON_CN73XX		(OCTEON_CN73XX_PASS1_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN73XX_PASS1_X	(OCTEON_CN73XX_PASS1_0 | \
				 OM_IGNORE_MINOR_REVISION)

#घोषणा OCTEON_CN70XX_PASS1_0	0x000d9600
#घोषणा OCTEON_CN70XX_PASS1_1	0x000d9601
#घोषणा OCTEON_CN70XX_PASS1_2	0x000d9602

#घोषणा OCTEON_CN70XX_PASS2_0	0x000d9608

#घोषणा OCTEON_CN70XX		(OCTEON_CN70XX_PASS1_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN70XX_PASS1_X	(OCTEON_CN70XX_PASS1_0 | \
				 OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN70XX_PASS2_X	(OCTEON_CN70XX_PASS2_0 | \
				 OM_IGNORE_MINOR_REVISION)

#घोषणा OCTEON_CN71XX		OCTEON_CN70XX

#घोषणा OCTEON_CN78XX_PASS1_0	0x000d9500
#घोषणा OCTEON_CN78XX_PASS1_1	0x000d9501
#घोषणा OCTEON_CN78XX_PASS2_0	0x000d9508

#घोषणा OCTEON_CN78XX		(OCTEON_CN78XX_PASS1_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN78XX_PASS1_X	(OCTEON_CN78XX_PASS1_0 | \
				 OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN78XX_PASS2_X	(OCTEON_CN78XX_PASS2_0 | \
				 OM_IGNORE_MINOR_REVISION)

#घोषणा OCTEON_CN76XX		(0x000d9540 | OM_CHECK_SUBMODEL)

/*
 * CNF7XXX models with new revision encoding
 */
#घोषणा OCTEON_CNF71XX_PASS1_0	0x000d9400
#घोषणा OCTEON_CNF71XX_PASS1_1  0x000d9401

#घोषणा OCTEON_CNF71XX		(OCTEON_CNF71XX_PASS1_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CNF71XX_PASS1_X	(OCTEON_CNF71XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)

/*
 * CN6XXX models with new revision encoding
 */
#घोषणा OCTEON_CN68XX_PASS1_0	0x000d9100
#घोषणा OCTEON_CN68XX_PASS1_1	0x000d9101
#घोषणा OCTEON_CN68XX_PASS1_2	0x000d9102
#घोषणा OCTEON_CN68XX_PASS2_0	0x000d9108
#घोषणा OCTEON_CN68XX_PASS2_1   0x000d9109
#घोषणा OCTEON_CN68XX_PASS2_2   0x000d910a

#घोषणा OCTEON_CN68XX		(OCTEON_CN68XX_PASS2_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN68XX_PASS1_X	(OCTEON_CN68XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN68XX_PASS2_X	(OCTEON_CN68XX_PASS2_0 | OM_IGNORE_MINOR_REVISION)

#घोषणा OCTEON_CN68XX_PASS1	OCTEON_CN68XX_PASS1_X
#घोषणा OCTEON_CN68XX_PASS2	OCTEON_CN68XX_PASS2_X

#घोषणा OCTEON_CN66XX_PASS1_0	0x000d9200
#घोषणा OCTEON_CN66XX_PASS1_2	0x000d9202

#घोषणा OCTEON_CN66XX		(OCTEON_CN66XX_PASS1_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN66XX_PASS1_X	(OCTEON_CN66XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)

#घोषणा OCTEON_CN63XX_PASS1_0	0x000d9000
#घोषणा OCTEON_CN63XX_PASS1_1	0x000d9001
#घोषणा OCTEON_CN63XX_PASS1_2	0x000d9002
#घोषणा OCTEON_CN63XX_PASS2_0	0x000d9008
#घोषणा OCTEON_CN63XX_PASS2_1	0x000d9009
#घोषणा OCTEON_CN63XX_PASS2_2	0x000d900a

#घोषणा OCTEON_CN63XX		(OCTEON_CN63XX_PASS2_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN63XX_PASS1_X	(OCTEON_CN63XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN63XX_PASS2_X	(OCTEON_CN63XX_PASS2_0 | OM_IGNORE_MINOR_REVISION)

/* CN62XX is same as CN63XX with 1 MB cache */
#घोषणा OCTEON_CN62XX           OCTEON_CN63XX

#घोषणा OCTEON_CN61XX_PASS1_0	0x000d9300
#घोषणा OCTEON_CN61XX_PASS1_1   0x000d9301

#घोषणा OCTEON_CN61XX		(OCTEON_CN61XX_PASS1_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN61XX_PASS1_X	(OCTEON_CN61XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)

/* CN60XX is same as CN61XX with 512 KB cache */
#घोषणा OCTEON_CN60XX           OCTEON_CN61XX

/*
 * CN5XXX models with new revision encoding
 */
#घोषणा OCTEON_CN58XX_PASS1_0	0x000d0300
#घोषणा OCTEON_CN58XX_PASS1_1	0x000d0301
#घोषणा OCTEON_CN58XX_PASS1_2	0x000d0303
#घोषणा OCTEON_CN58XX_PASS2_0	0x000d0308
#घोषणा OCTEON_CN58XX_PASS2_1	0x000d0309
#घोषणा OCTEON_CN58XX_PASS2_2	0x000d030a
#घोषणा OCTEON_CN58XX_PASS2_3	0x000d030b

#घोषणा OCTEON_CN58XX		(OCTEON_CN58XX_PASS2_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN58XX_PASS1_X	(OCTEON_CN58XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN58XX_PASS2_X	(OCTEON_CN58XX_PASS2_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN58XX_PASS1	OCTEON_CN58XX_PASS1_X
#घोषणा OCTEON_CN58XX_PASS2	OCTEON_CN58XX_PASS2_X

#घोषणा OCTEON_CN56XX_PASS1_0	0x000d0400
#घोषणा OCTEON_CN56XX_PASS1_1	0x000d0401
#घोषणा OCTEON_CN56XX_PASS2_0	0x000d0408
#घोषणा OCTEON_CN56XX_PASS2_1	0x000d0409

#घोषणा OCTEON_CN56XX		(OCTEON_CN56XX_PASS2_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN56XX_PASS1_X	(OCTEON_CN56XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN56XX_PASS2_X	(OCTEON_CN56XX_PASS2_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN56XX_PASS1	OCTEON_CN56XX_PASS1_X
#घोषणा OCTEON_CN56XX_PASS2	OCTEON_CN56XX_PASS2_X

#घोषणा OCTEON_CN57XX		OCTEON_CN56XX
#घोषणा OCTEON_CN57XX_PASS1	OCTEON_CN56XX_PASS1
#घोषणा OCTEON_CN57XX_PASS2	OCTEON_CN56XX_PASS2

#घोषणा OCTEON_CN55XX		OCTEON_CN56XX
#घोषणा OCTEON_CN55XX_PASS1	OCTEON_CN56XX_PASS1
#घोषणा OCTEON_CN55XX_PASS2	OCTEON_CN56XX_PASS2

#घोषणा OCTEON_CN54XX		OCTEON_CN56XX
#घोषणा OCTEON_CN54XX_PASS1	OCTEON_CN56XX_PASS1
#घोषणा OCTEON_CN54XX_PASS2	OCTEON_CN56XX_PASS2

#घोषणा OCTEON_CN50XX_PASS1_0	0x000d0600

#घोषणा OCTEON_CN50XX		(OCTEON_CN50XX_PASS1_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN50XX_PASS1_X	(OCTEON_CN50XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN50XX_PASS1	OCTEON_CN50XX_PASS1_X

/*
 * NOTE: Octeon CN5000F model is not identअगरiable using the
 * OCTEON_IS_MODEL() functions, but are treated as CN50XX.
 */

#घोषणा OCTEON_CN52XX_PASS1_0	0x000d0700
#घोषणा OCTEON_CN52XX_PASS2_0	0x000d0708

#घोषणा OCTEON_CN52XX		(OCTEON_CN52XX_PASS2_0 | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN52XX_PASS1_X	(OCTEON_CN52XX_PASS1_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN52XX_PASS2_X	(OCTEON_CN52XX_PASS2_0 | OM_IGNORE_MINOR_REVISION)
#घोषणा OCTEON_CN52XX_PASS1	OCTEON_CN52XX_PASS1_X
#घोषणा OCTEON_CN52XX_PASS2	OCTEON_CN52XX_PASS2_X

/*
 * CN3XXX models with old revision enconding
 */
#घोषणा OCTEON_CN38XX_PASS1	0x000d0000
#घोषणा OCTEON_CN38XX_PASS2	0x000d0001
#घोषणा OCTEON_CN38XX_PASS3	0x000d0003
#घोषणा OCTEON_CN38XX		(OCTEON_CN38XX_PASS3 | OM_IGNORE_REVISION)

#घोषणा OCTEON_CN36XX		OCTEON_CN38XX
#घोषणा OCTEON_CN36XX_PASS2	OCTEON_CN38XX_PASS2
#घोषणा OCTEON_CN36XX_PASS3	OCTEON_CN38XX_PASS3

/* The OCTEON_CN31XX matches CN31XX models and the CN3020 */
#घोषणा OCTEON_CN31XX_PASS1	0x000d0100
#घोषणा OCTEON_CN31XX_PASS1_1	0x000d0102
#घोषणा OCTEON_CN31XX		(OCTEON_CN31XX_PASS1 | OM_IGNORE_REVISION)

/*
 * This model is only used क्रम पूर्णांकernal checks, it is not a valid
 * model क्रम the OCTEON_MODEL environment variable.  This matches the
 * CN3010 and CN3005 but NOT the CN3020.
 */
#घोषणा OCTEON_CN30XX_PASS1	0x000d0200
#घोषणा OCTEON_CN30XX_PASS1_1	0x000d0202
#घोषणा OCTEON_CN30XX		(OCTEON_CN30XX_PASS1 | OM_IGNORE_REVISION)

#घोषणा OCTEON_CN3005_PASS1	(0x000d0210 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3005_PASS1_0	(0x000d0210 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3005_PASS1_1	(0x000d0212 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3005		(OCTEON_CN3005_PASS1 | OM_IGNORE_REVISION | OM_CHECK_SUBMODEL)

#घोषणा OCTEON_CN3010_PASS1	(0x000d0200 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3010_PASS1_0	(0x000d0200 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3010_PASS1_1	(0x000d0202 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3010		(OCTEON_CN3010_PASS1 | OM_IGNORE_REVISION | OM_CHECK_SUBMODEL)

#घोषणा OCTEON_CN3020_PASS1	(0x000d0110 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3020_PASS1_0	(0x000d0110 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3020_PASS1_1	(0x000d0112 | OM_CHECK_SUBMODEL)
#घोषणा OCTEON_CN3020		(OCTEON_CN3020_PASS1 | OM_IGNORE_REVISION | OM_CHECK_SUBMODEL)

/*
 * This matches the complete family of CN3xxx CPUs, and not subsequent
 * models
 */
#घोषणा OCTEON_CN3XXX		(OCTEON_CN58XX_PASS1_0 | OM_MATCH_PREVIOUS_MODELS | OM_IGNORE_REVISION)
#घोषणा OCTEON_CN5XXX		(OCTEON_CN58XX_PASS1_0 | OM_MATCH_5XXX_FAMILY_MODELS)
#घोषणा OCTEON_CN6XXX		(OCTEON_CN63XX_PASS1_0 | OM_MATCH_6XXX_FAMILY_MODELS)
#घोषणा OCTEON_CNF7XXX		(OCTEON_CNF71XX_PASS1_0 | \
				 OM_MATCH_F7XXX_FAMILY_MODELS)
#घोषणा OCTEON_CN7XXX		(OCTEON_CN78XX_PASS1_0 | \
				 OM_MATCH_7XXX_FAMILY_MODELS)

/* The revision byte (low byte) has two dअगरferent encodings.
 * CN3XXX:
 *
 *     bits
 *     <7:5>: reserved (0)
 *     <4>:   alternate package
 *     <3:0>: revision
 *
 * CN5XXX and older models:
 *
 *     bits
 *     <7>:   reserved (0)
 *     <6>:   alternate package
 *     <5:3>: major revision
 *     <2:0>: minor revision
 *
 */

/* Masks used क्रम the various types of model/family/revision matching */
#घोषणा OCTEON_38XX_FAMILY_MASK	     0x00ffff00
#घोषणा OCTEON_38XX_FAMILY_REV_MASK  0x00ffff0f
#घोषणा OCTEON_38XX_MODEL_MASK	     0x00ffff10
#घोषणा OCTEON_38XX_MODEL_REV_MASK   (OCTEON_38XX_FAMILY_REV_MASK | OCTEON_38XX_MODEL_MASK)

/* CN5XXX and later use dअगरferent layout of bits in the revision ID field */
#घोषणा OCTEON_58XX_FAMILY_MASK	     OCTEON_38XX_FAMILY_MASK
#घोषणा OCTEON_58XX_FAMILY_REV_MASK  0x00ffff3f
#घोषणा OCTEON_58XX_MODEL_MASK	     0x00ffff40
#घोषणा OCTEON_58XX_MODEL_REV_MASK   (OCTEON_58XX_FAMILY_REV_MASK | OCTEON_58XX_MODEL_MASK)
#घोषणा OCTEON_58XX_MODEL_MINOR_REV_MASK (OCTEON_58XX_MODEL_REV_MASK & 0x00ffff38)
#घोषणा OCTEON_5XXX_MODEL_MASK	     0x00ff0fc0

अटल अंतरभूत uपूर्णांक32_t cvmx_get_proc_id(व्योम) __attribute__ ((pure));
अटल अंतरभूत uपूर्णांक64_t cvmx_पढ़ो_csr(uपूर्णांक64_t csr_addr);

#घोषणा __OCTEON_MATCH_MASK__(x, y, z) (((x) & (z)) == ((y) & (z)))

/*
 * __OCTEON_IS_MODEL_COMPILE__(arg_model, chip_model)
 * वापसs true अगर chip_model is identical or beदीर्घ to the OCTEON
 * model group specअगरied in arg_model.
 */
/* NOTE: This क्रम पूर्णांकernal use only! */
#घोषणा __OCTEON_IS_MODEL_COMPILE__(arg_model, chip_model)		\
((((arg_model & OCTEON_38XX_FAMILY_MASK) < OCTEON_CN58XX_PASS1_0)  && ( \
		((((arg_model) & (OM_FLAG_MASK)) == (OM_IGNORE_REVISION | OM_CHECK_SUBMODEL)) \
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_38XX_MODEL_MASK)) || \
		((((arg_model) & (OM_FLAG_MASK)) == 0)			\
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_38XX_FAMILY_REV_MASK)) || \
		((((arg_model) & (OM_FLAG_MASK)) == OM_IGNORE_REVISION) \
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_38XX_FAMILY_MASK)) || \
		((((arg_model) & (OM_FLAG_MASK)) == OM_CHECK_SUBMODEL)	\
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_38XX_MODEL_REV_MASK)) || \
		((((arg_model) & (OM_MATCH_PREVIOUS_MODELS)) == OM_MATCH_PREVIOUS_MODELS) \
			&& (((chip_model) & OCTEON_38XX_MODEL_MASK) < ((arg_model) & OCTEON_38XX_MODEL_MASK))) \
		)) ||							\
	(((arg_model & OCTEON_38XX_FAMILY_MASK) >= OCTEON_CN58XX_PASS1_0)  && ( \
		((((arg_model) & (OM_FLAG_MASK)) == (OM_IGNORE_REVISION | OM_CHECK_SUBMODEL)) \
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_58XX_MODEL_MASK)) || \
		((((arg_model) & (OM_FLAG_MASK)) == 0)			\
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_58XX_FAMILY_REV_MASK)) || \
		((((arg_model) & (OM_FLAG_MASK)) == OM_IGNORE_MINOR_REVISION) \
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_58XX_MODEL_MINOR_REV_MASK)) || \
		((((arg_model) & (OM_FLAG_MASK)) == OM_IGNORE_REVISION) \
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_58XX_FAMILY_MASK)) || \
		((((arg_model) & (OM_FLAG_MASK)) == OM_CHECK_SUBMODEL)	\
			&& __OCTEON_MATCH_MASK__((chip_model), (arg_model), OCTEON_58XX_MODEL_MASK)) || \
		((((arg_model) & (OM_MATCH_5XXX_FAMILY_MODELS)) == OM_MATCH_5XXX_FAMILY_MODELS) \
			&& ((chip_model & OCTEON_PRID_MASK) >= OCTEON_CN58XX_PASS1_0) \
			&& ((chip_model & OCTEON_PRID_MASK) < OCTEON_CN63XX_PASS1_0)) || \
		((((arg_model) & (OM_MATCH_6XXX_FAMILY_MODELS)) == OM_MATCH_6XXX_FAMILY_MODELS) \
			&& ((chip_model & OCTEON_PRID_MASK) >= OCTEON_CN63XX_PASS1_0) \
			&& ((chip_model & OCTEON_PRID_MASK) < OCTEON_CNF71XX_PASS1_0)) || \
		((((arg_model) & (OM_MATCH_F7XXX_FAMILY_MODELS)) == OM_MATCH_F7XXX_FAMILY_MODELS) \
			&& ((chip_model & OCTEON_PRID_MASK) >= OCTEON_CNF71XX_PASS1_0) \
			&& ((chip_model & OCTEON_PRID_MASK) < OCTEON_CN78XX_PASS1_0)) || \
		((((arg_model) & (OM_MATCH_7XXX_FAMILY_MODELS)) == OM_MATCH_7XXX_FAMILY_MODELS) \
			&& ((chip_model & OCTEON_PRID_MASK) >= OCTEON_CN78XX_PASS1_0)) || \
		((((arg_model) & (OM_MATCH_PREVIOUS_MODELS)) == OM_MATCH_PREVIOUS_MODELS) \
			&& (((chip_model) & OCTEON_58XX_MODEL_MASK) < ((arg_model) & OCTEON_58XX_MODEL_MASK))) \
		)))

/* NOTE: This क्रम पूर्णांकernal use only!!!!! */
अटल अंतरभूत पूर्णांक __octeon_is_model_runसमय__(uपूर्णांक32_t model)
अणु
	uपूर्णांक32_t cpuid = cvmx_get_proc_id();

	वापस __OCTEON_IS_MODEL_COMPILE__(model, cpuid);
पूर्ण

/*
 * The OCTEON_IS_MODEL macro should be used क्रम all Octeon model checking करोne
 * in a program.
 * This should be kept runसमय अगर at all possible  and must be conditionalized
 * with OCTEON_IS_COMMON_BINARY() अगर runसमय checking support is required.
 *
 * Use of the macro in preprocessor directives ( #अगर OCTEON_IS_MODEL(...) )
 * is NOT SUPPORTED, and should be replaced with CVMX_COMPILED_FOR()
 * I.e.:
 *  #अगर OCTEON_IS_MODEL(OCTEON_CN56XX)	->  #अगर CVMX_COMPILED_FOR(OCTEON_CN56XX)
 */
#घोषणा OCTEON_IS_MODEL(x) __octeon_is_model_runसमय__(x)
#घोषणा OCTEON_IS_COMMON_BINARY() 1
#अघोषित OCTEON_MODEL

#घोषणा OCTEON_IS_OCTEON1()	OCTEON_IS_MODEL(OCTEON_CN3XXX)
#घोषणा OCTEON_IS_OCTEONPLUS()	OCTEON_IS_MODEL(OCTEON_CN5XXX)
#घोषणा OCTEON_IS_OCTEON2()						\
	(OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF71XX))

#घोषणा OCTEON_IS_OCTEON3()	OCTEON_IS_MODEL(OCTEON_CN7XXX)

#घोषणा OCTEON_IS_OCTEON1PLUS()	(OCTEON_IS_OCTEON1() || OCTEON_IS_OCTEONPLUS())

स्थिर अक्षर *__init octeon_model_get_string(uपूर्णांक32_t chip_id);

/*
 * Return the octeon family, i.e., ProcessorID of the PrID रेजिस्टर.
 *
 * @वापस the octeon family on success, ((unपूर्णांक32_t)-1) on error.
 */
अटल अंतरभूत uपूर्णांक32_t cvmx_get_octeon_family(व्योम)
अणु
	वापस cvmx_get_proc_id() & OCTEON_FAMILY_MASK;
पूर्ण

#समावेश <यंत्र/octeon/octeon-feature.h>

#पूर्ण_अगर /* __OCTEON_MODEL_H__ */
