<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __SH_CSS_FRAC_H
#घोषणा __SH_CSS_FRAC_H

#समावेश <math_support.h>

#घोषणा sISP_REG_BIT		      ISP_VEC_ELEMBITS
#घोषणा uISP_REG_BIT		      ((अचिन्हित पूर्णांक)(sISP_REG_BIT - 1))
#घोषणा sSHIFT				    (16 - sISP_REG_BIT)
#घोषणा uSHIFT				    ((अचिन्हित पूर्णांक)(16 - uISP_REG_BIT))
#घोषणा sFRACTION_BITS_FITTING(a) (a - sSHIFT)
#घोषणा uFRACTION_BITS_FITTING(a) ((अचिन्हित पूर्णांक)(a - uSHIFT))
#घोषणा sISP_VAL_MIN		      (-(1 << uISP_REG_BIT))
#घोषणा sISP_VAL_MAX		      ((1 << uISP_REG_BIT) - 1)
#घोषणा uISP_VAL_MIN		      (0U)
#घोषणा uISP_VAL_MAX		      ((अचिन्हित पूर्णांक)((1 << uISP_REG_BIT) - 1))

/* a:fraction bits क्रम 16bit precision, b:fraction bits क्रम ISP precision */
#घोषणा sDIGIT_FITTING(v, a, b) \
	min_t(पूर्णांक, max_t(पूर्णांक, (((v) >> sSHIFT) >> max(sFRACTION_BITS_FITTING(a) - (b), 0)), \
	  sISP_VAL_MIN), sISP_VAL_MAX)
#घोषणा uDIGIT_FITTING(v, a, b) \
	min((अचिन्हित पूर्णांक)max((अचिन्हित)(((v) >> uSHIFT) \
	>> max((पूर्णांक)(uFRACTION_BITS_FITTING(a) - (b)), 0)), \
	  uISP_VAL_MIN), uISP_VAL_MAX)

#पूर्ण_अगर /* __SH_CSS_FRAC_H */
