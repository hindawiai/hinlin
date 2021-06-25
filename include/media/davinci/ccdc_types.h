<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2008-2009 Texas Instruments Inc
 *
 **************************************************************************/
#अगर_अघोषित _CCDC_TYPES_H
#घोषणा _CCDC_TYPES_H
क्रमागत ccdc_pixfmt अणु
	CCDC_PIXFMT_RAW,
	CCDC_PIXFMT_YCBCR_16BIT,
	CCDC_PIXFMT_YCBCR_8BIT
पूर्ण;

क्रमागत ccdc_frmfmt अणु
	CCDC_FRMFMT_PROGRESSIVE,
	CCDC_FRMFMT_INTERLACED
पूर्ण;

/* PIXEL ORDER IN MEMORY from LSB to MSB */
/* only applicable क्रम 8-bit input mode  */
क्रमागत ccdc_pixorder अणु
	CCDC_PIXORDER_YCBYCR,
	CCDC_PIXORDER_CBYCRY,
पूर्ण;

क्रमागत ccdc_buftype अणु
	CCDC_BUFTYPE_FLD_INTERLEAVED,
	CCDC_BUFTYPE_FLD_SEPARATED
पूर्ण;
#पूर्ण_अगर
