<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013 Texas Instruments Inc.
 *
 * David Griego, <dagriego@biglakesoftware.com>
 * Dale Farnsworth, <dale@farnsworth.org>
 * Archit Taneja, <archit@ti.com>
 */
#अगर_अघोषित TI_SC_H
#घोषणा TI_SC_H

/* Scaler regs */
#घोषणा CFG_SC0				0x0
#घोषणा CFG_INTERLACE_O			(1 << 0)
#घोषणा CFG_LINEAR			(1 << 1)
#घोषणा CFG_SC_BYPASS			(1 << 2)
#घोषणा CFG_INVT_FID			(1 << 3)
#घोषणा CFG_USE_RAV			(1 << 4)
#घोषणा CFG_ENABLE_EV			(1 << 5)
#घोषणा CFG_AUTO_HS			(1 << 6)
#घोषणा CFG_DCM_2X			(1 << 7)
#घोषणा CFG_DCM_4X			(1 << 8)
#घोषणा CFG_HP_BYPASS			(1 << 9)
#घोषणा CFG_INTERLACE_I			(1 << 10)
#घोषणा CFG_ENABLE_SIN2_VER_INTP	(1 << 11)
#घोषणा CFG_Y_PK_EN			(1 << 14)
#घोषणा CFG_TRIM			(1 << 15)
#घोषणा CFG_SELFGEN_FID			(1 << 16)

#घोषणा CFG_SC1				0x4
#घोषणा CFG_ROW_ACC_INC_MASK		0x07ffffff
#घोषणा CFG_ROW_ACC_INC_SHIFT		0

#घोषणा CFG_SC2				0x08
#घोषणा CFG_ROW_ACC_OFFSET_MASK		0x0fffffff
#घोषणा CFG_ROW_ACC_OFFSET_SHIFT	0

#घोषणा CFG_SC3				0x0c
#घोषणा CFG_ROW_ACC_OFFSET_B_MASK	0x0fffffff
#घोषणा CFG_ROW_ACC_OFFSET_B_SHIFT	0

#घोषणा CFG_SC4				0x10
#घोषणा CFG_TAR_H_MASK			0x07ff
#घोषणा CFG_TAR_H_SHIFT			0
#घोषणा CFG_TAR_W_MASK			0x07ff
#घोषणा CFG_TAR_W_SHIFT			12
#घोषणा CFG_LIN_ACC_INC_U_MASK		0x07
#घोषणा CFG_LIN_ACC_INC_U_SHIFT		24
#घोषणा CFG_NLIN_ACC_INIT_U_MASK	0x07
#घोषणा CFG_NLIN_ACC_INIT_U_SHIFT	28

#घोषणा CFG_SC5				0x14
#घोषणा CFG_SRC_H_MASK			0x07ff
#घोषणा CFG_SRC_H_SHIFT			0
#घोषणा CFG_SRC_W_MASK			0x07ff
#घोषणा CFG_SRC_W_SHIFT			12
#घोषणा CFG_NLIN_ACC_INC_U_MASK		0x07
#घोषणा CFG_NLIN_ACC_INC_U_SHIFT	24

#घोषणा CFG_SC6				0x18
#घोषणा CFG_ROW_ACC_INIT_RAV_MASK	0x03ff
#घोषणा CFG_ROW_ACC_INIT_RAV_SHIFT	0
#घोषणा CFG_ROW_ACC_INIT_RAV_B_MASK	0x03ff
#घोषणा CFG_ROW_ACC_INIT_RAV_B_SHIFT	10

#घोषणा CFG_SC8				0x20
#घोषणा CFG_NLIN_LEFT_MASK		0x07ff
#घोषणा CFG_NLIN_LEFT_SHIFT		0
#घोषणा CFG_NLIN_RIGHT_MASK		0x07ff
#घोषणा CFG_NLIN_RIGHT_SHIFT		12

#घोषणा CFG_SC9				0x24
#घोषणा CFG_LIN_ACC_INC			CFG_SC9

#घोषणा CFG_SC10			0x28
#घोषणा CFG_NLIN_ACC_INIT		CFG_SC10

#घोषणा CFG_SC11			0x2c
#घोषणा CFG_NLIN_ACC_INC		CFG_SC11

#घोषणा CFG_SC12			0x30
#घोषणा CFG_COL_ACC_OFFSET_MASK		0x01ffffff
#घोषणा CFG_COL_ACC_OFFSET_SHIFT	0

#घोषणा CFG_SC13			0x34
#घोषणा CFG_SC_FACTOR_RAV_MASK		0xff
#घोषणा CFG_SC_FACTOR_RAV_SHIFT		0
#घोषणा CFG_CHROMA_INTP_THR_MASK	0x03ff
#घोषणा CFG_CHROMA_INTP_THR_SHIFT	12
#घोषणा CFG_DELTA_CHROMA_THR_MASK	0x0f
#घोषणा CFG_DELTA_CHROMA_THR_SHIFT	24

#घोषणा CFG_SC17			0x44
#घोषणा CFG_EV_THR_MASK			0x03ff
#घोषणा CFG_EV_THR_SHIFT		12
#घोषणा CFG_DELTA_LUMA_THR_MASK		0x0f
#घोषणा CFG_DELTA_LUMA_THR_SHIFT	24
#घोषणा CFG_DELTA_EV_THR_MASK		0x0f
#घोषणा CFG_DELTA_EV_THR_SHIFT		28

#घोषणा CFG_SC18			0x48
#घोषणा CFG_HS_FACTOR_MASK		0x03ff
#घोषणा CFG_HS_FACTOR_SHIFT		0
#घोषणा CFG_CONF_DEFAULT_MASK		0x01ff
#घोषणा CFG_CONF_DEFAULT_SHIFT		16

#घोषणा CFG_SC19			0x4c
#घोषणा CFG_HPF_COEFF0_MASK		0xff
#घोषणा CFG_HPF_COEFF0_SHIFT		0
#घोषणा CFG_HPF_COEFF1_MASK		0xff
#घोषणा CFG_HPF_COEFF1_SHIFT		8
#घोषणा CFG_HPF_COEFF2_MASK		0xff
#घोषणा CFG_HPF_COEFF2_SHIFT		16
#घोषणा CFG_HPF_COEFF3_MASK		0xff
#घोषणा CFG_HPF_COEFF3_SHIFT		23

#घोषणा CFG_SC20			0x50
#घोषणा CFG_HPF_COEFF4_MASK		0xff
#घोषणा CFG_HPF_COEFF4_SHIFT		0
#घोषणा CFG_HPF_COEFF5_MASK		0xff
#घोषणा CFG_HPF_COEFF5_SHIFT		8
#घोषणा CFG_HPF_NORM_SHIFT_MASK		0x07
#घोषणा CFG_HPF_NORM_SHIFT_SHIFT	16
#घोषणा CFG_NL_LIMIT_MASK		0x1ff
#घोषणा CFG_NL_LIMIT_SHIFT		20

#घोषणा CFG_SC21			0x54
#घोषणा CFG_NL_LO_THR_MASK		0x01ff
#घोषणा CFG_NL_LO_THR_SHIFT		0
#घोषणा CFG_NL_LO_SLOPE_MASK		0xff
#घोषणा CFG_NL_LO_SLOPE_SHIFT		16

#घोषणा CFG_SC22			0x58
#घोषणा CFG_NL_HI_THR_MASK		0x01ff
#घोषणा CFG_NL_HI_THR_SHIFT		0
#घोषणा CFG_NL_HI_SLOPE_SH_MASK		0x07
#घोषणा CFG_NL_HI_SLOPE_SH_SHIFT	16

#घोषणा CFG_SC23			0x5c
#घोषणा CFG_GRADIENT_THR_MASK		0x07ff
#घोषणा CFG_GRADIENT_THR_SHIFT		0
#घोषणा CFG_GRADIENT_THR_RANGE_MASK	0x0f
#घोषणा CFG_GRADIENT_THR_RANGE_SHIFT	12
#घोषणा CFG_MIN_GY_THR_MASK		0xff
#घोषणा CFG_MIN_GY_THR_SHIFT		16
#घोषणा CFG_MIN_GY_THR_RANGE_MASK	0x0f
#घोषणा CFG_MIN_GY_THR_RANGE_SHIFT	28

#घोषणा CFG_SC24			0x60
#घोषणा CFG_ORG_H_MASK			0x07ff
#घोषणा CFG_ORG_H_SHIFT			0
#घोषणा CFG_ORG_W_MASK			0x07ff
#घोषणा CFG_ORG_W_SHIFT			16

#घोषणा CFG_SC25			0x64
#घोषणा CFG_OFF_H_MASK			0x07ff
#घोषणा CFG_OFF_H_SHIFT			0
#घोषणा CFG_OFF_W_MASK			0x07ff
#घोषणा CFG_OFF_W_SHIFT			16

/* number of phases supported by the polyphase scalers */
#घोषणा SC_NUM_PHASES			32

/* number of taps used by horizontal polyphase scaler */
#घोषणा SC_H_NUM_TAPS			7

/* number of taps used by vertical polyphase scaler */
#घोषणा SC_V_NUM_TAPS			5

/* number of taps expected by the scaler in it's coefficient memory */
#घोषणा SC_NUM_TAPS_MEM_ALIGN		8

/* Maximum frame width the scaler can handle (in pixels) */
#घोषणा SC_MAX_PIXEL_WIDTH		2047

/* Maximum frame height the scaler can handle (in lines) */
#घोषणा SC_MAX_PIXEL_HEIGHT		2047

/*
 * coefficient memory size in bytes:
 * num phases x num sets(luma and chroma) x num taps(aligned) x coeff size
 */
#घोषणा SC_COEF_SRAM_SIZE	(SC_NUM_PHASES * 2 * SC_NUM_TAPS_MEM_ALIGN * 2)

काष्ठा sc_data अणु
	व्योम __iomem		*base;
	काष्ठा resource		*res;

	dma_addr_t		loaded_coeff_h; /* loaded h coeffs in SC */
	dma_addr_t		loaded_coeff_v; /* loaded v coeffs in SC */

	bool			load_coeff_h;	/* have new h SC coeffs */
	bool			load_coeff_v;	/* have new v SC coeffs */

	काष्ठा platक्रमm_device *pdev;
पूर्ण;

व्योम sc_dump_regs(काष्ठा sc_data *sc);
व्योम sc_set_hs_coeffs(काष्ठा sc_data *sc, व्योम *addr, अचिन्हित पूर्णांक src_w,
		अचिन्हित पूर्णांक dst_w);
व्योम sc_set_vs_coeffs(काष्ठा sc_data *sc, व्योम *addr, अचिन्हित पूर्णांक src_h,
		अचिन्हित पूर्णांक dst_h);
व्योम sc_config_scaler(काष्ठा sc_data *sc, u32 *sc_reg0, u32 *sc_reg8,
		u32 *sc_reg17, अचिन्हित पूर्णांक src_w, अचिन्हित पूर्णांक src_h,
		अचिन्हित पूर्णांक dst_w, अचिन्हित पूर्णांक dst_h);
काष्ठा sc_data *sc_create(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *res_name);

#पूर्ण_अगर
