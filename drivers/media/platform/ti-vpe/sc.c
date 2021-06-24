<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Scaler library
 *
 * Copyright (c) 2013 Texas Instruments Inc.
 *
 * David Griego, <dagriego@biglakesoftware.com>
 * Dale Farnsworth, <dale@farnsworth.org>
 * Archit Taneja, <archit@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "sc.h"
#समावेश "sc_coeff.h"

व्योम sc_dump_regs(काष्ठा sc_data *sc)
अणु
	काष्ठा device *dev = &sc->pdev->dev;

#घोषणा DUMPREG(r) dev_dbg(dev, "%-35s %08x\n", #r, \
	ioपढ़ो32(sc->base + CFG_##r))

	dev_dbg(dev, "SC Registers @ %pa:\n", &sc->res->start);

	DUMPREG(SC0);
	DUMPREG(SC1);
	DUMPREG(SC2);
	DUMPREG(SC3);
	DUMPREG(SC4);
	DUMPREG(SC5);
	DUMPREG(SC6);
	DUMPREG(SC8);
	DUMPREG(SC9);
	DUMPREG(SC10);
	DUMPREG(SC11);
	DUMPREG(SC12);
	DUMPREG(SC13);
	DUMPREG(SC17);
	DUMPREG(SC18);
	DUMPREG(SC19);
	DUMPREG(SC20);
	DUMPREG(SC21);
	DUMPREG(SC22);
	DUMPREG(SC23);
	DUMPREG(SC24);
	DUMPREG(SC25);

#अघोषित DUMPREG
पूर्ण
EXPORT_SYMBOL(sc_dump_regs);

/*
 * set the horizontal scaler coefficients according to the ratio of output to
 * input widths, after accounting क्रम up to two levels of decimation
 */
व्योम sc_set_hs_coeffs(काष्ठा sc_data *sc, व्योम *addr, अचिन्हित पूर्णांक src_w,
		अचिन्हित पूर्णांक dst_w)
अणु
	पूर्णांक sixteenths;
	पूर्णांक idx;
	पूर्णांक i, j;
	u16 *coeff_h = addr;
	स्थिर u16 *cp;

	अगर (dst_w > src_w) अणु
		idx = HS_UP_SCALE;
	पूर्ण अन्यथा अणु
		अगर ((dst_w << 1) < src_w)
			dst_w <<= 1;	/* first level decimation */
		अगर ((dst_w << 1) < src_w)
			dst_w <<= 1;	/* second level decimation */

		अगर (dst_w == src_w) अणु
			idx = HS_LE_16_16_SCALE;
		पूर्ण अन्यथा अणु
			sixteenths = (dst_w << 4) / src_w;
			अगर (sixteenths < 8)
				sixteenths = 8;
			idx = HS_LT_9_16_SCALE + sixteenths - 8;
		पूर्ण
	पूर्ण

	cp = scaler_hs_coeffs[idx];

	क्रम (i = 0; i < SC_NUM_PHASES * 2; i++) अणु
		क्रम (j = 0; j < SC_H_NUM_TAPS; j++)
			*coeff_h++ = *cp++;
		/*
		 * क्रम each phase, the scaler expects space क्रम 8 coefficients
		 * in it's memory. For the horizontal scaler, we copy the first
		 * 7 coefficients and skip the last slot to move to the next
		 * row to hold coefficients क्रम the next phase
		 */
		coeff_h += SC_NUM_TAPS_MEM_ALIGN - SC_H_NUM_TAPS;
	पूर्ण

	sc->load_coeff_h = true;
पूर्ण
EXPORT_SYMBOL(sc_set_hs_coeffs);

/*
 * set the vertical scaler coefficients according to the ratio of output to
 * input heights
 */
व्योम sc_set_vs_coeffs(काष्ठा sc_data *sc, व्योम *addr, अचिन्हित पूर्णांक src_h,
		अचिन्हित पूर्णांक dst_h)
अणु
	पूर्णांक sixteenths;
	पूर्णांक idx;
	पूर्णांक i, j;
	u16 *coeff_v = addr;
	स्थिर u16 *cp;

	अगर (dst_h > src_h) अणु
		idx = VS_UP_SCALE;
	पूर्ण अन्यथा अगर (dst_h == src_h) अणु
		idx = VS_1_TO_1_SCALE;
	पूर्ण अन्यथा अणु
		sixteenths = (dst_h << 4) / src_h;
		अगर (sixteenths < 8)
			sixteenths = 8;
		idx = VS_LT_9_16_SCALE + sixteenths - 8;
	पूर्ण

	cp = scaler_vs_coeffs[idx];

	क्रम (i = 0; i < SC_NUM_PHASES * 2; i++) अणु
		क्रम (j = 0; j < SC_V_NUM_TAPS; j++)
			*coeff_v++ = *cp++;
		/*
		 * क्रम the vertical scaler, we copy the first 5 coefficients and
		 * skip the last 3 slots to move to the next row to hold
		 * coefficients क्रम the next phase
		 */
		coeff_v += SC_NUM_TAPS_MEM_ALIGN - SC_V_NUM_TAPS;
	पूर्ण

	sc->load_coeff_v = true;
पूर्ण
EXPORT_SYMBOL(sc_set_vs_coeffs);

व्योम sc_config_scaler(काष्ठा sc_data *sc, u32 *sc_reg0, u32 *sc_reg8,
		u32 *sc_reg17, अचिन्हित पूर्णांक src_w, अचिन्हित पूर्णांक src_h,
		अचिन्हित पूर्णांक dst_w, अचिन्हित पूर्णांक dst_h)
अणु
	काष्ठा device *dev = &sc->pdev->dev;
	u32 val;
	पूर्णांक dcm_x, dcm_shअगरt;
	bool use_rav;
	अचिन्हित दीर्घ llपंचांगp;
	u32 lin_acc_inc, lin_acc_inc_u;
	u32 col_acc_offset;
	u16 factor = 0;
	पूर्णांक row_acc_init_rav = 0, row_acc_init_rav_b = 0;
	u32 row_acc_inc = 0, row_acc_offset = 0, row_acc_offset_b = 0;
	/*
	 * location of SC रेजिस्टर in payload memory with respect to the first
	 * रेजिस्टर in the mmr address data block
	 */
	u32 *sc_reg9 = sc_reg8 + 1;
	u32 *sc_reg12 = sc_reg8 + 4;
	u32 *sc_reg13 = sc_reg8 + 5;
	u32 *sc_reg24 = sc_reg17 + 7;

	val = sc_reg0[0];

	/* clear all the features(they may get enabled अन्यथाwhere later) */
	val &= ~(CFG_SELFGEN_FID | CFG_TRIM | CFG_ENABLE_SIN2_VER_INTP |
		CFG_INTERLACE_I | CFG_DCM_4X | CFG_DCM_2X | CFG_AUTO_HS |
		CFG_ENABLE_EV | CFG_USE_RAV | CFG_INVT_FID | CFG_SC_BYPASS |
		CFG_INTERLACE_O | CFG_Y_PK_EN | CFG_HP_BYPASS | CFG_LINEAR);

	अगर (src_w == dst_w && src_h == dst_h) अणु
		val |= CFG_SC_BYPASS;
		sc_reg0[0] = val;
		वापस;
	पूर्ण

	/* we only support linear scaling क्रम now */
	val |= CFG_LINEAR;

	/* configure horizontal scaler */

	/* enable 2X or 4X decimation */
	dcm_x = src_w / dst_w;
	अगर (dcm_x > 4) अणु
		val |= CFG_DCM_4X;
		dcm_shअगरt = 2;
	पूर्ण अन्यथा अगर (dcm_x > 2) अणु
		val |= CFG_DCM_2X;
		dcm_shअगरt = 1;
	पूर्ण अन्यथा अणु
		dcm_shअगरt = 0;
	पूर्ण

	llपंचांगp = dst_w - 1;
	lin_acc_inc = भाग64_u64(((u64)(src_w >> dcm_shअगरt) - 1) << 24, llपंचांगp);
	lin_acc_inc_u = 0;
	col_acc_offset = 0;

	dev_dbg(dev, "hs config: src_w = %d, dst_w = %d, decimation = %s, lin_acc_inc = %08x\n",
		src_w, dst_w, dcm_shअगरt == 2 ? "4x" :
		(dcm_shअगरt == 1 ? "2x" : "none"), lin_acc_inc);

	/* configure vertical scaler */

	/* use RAV क्रम vertical scaler अगर vertical करोwnscaling is > 4x */
	अगर (dst_h < (src_h >> 2)) अणु
		use_rav = true;
		val |= CFG_USE_RAV;
	पूर्ण अन्यथा अणु
		use_rav = false;
	पूर्ण

	अगर (use_rav) अणु
		/* use RAV */
		factor = (u16) ((dst_h << 10) / src_h);

		row_acc_init_rav = factor + ((1 + factor) >> 1);
		अगर (row_acc_init_rav >= 1024)
			row_acc_init_rav -= 1024;

		row_acc_init_rav_b = row_acc_init_rav +
				(1 + (row_acc_init_rav >> 1)) -
				(1024 >> 1);

		अगर (row_acc_init_rav_b < 0) अणु
			row_acc_init_rav_b += row_acc_init_rav;
			row_acc_init_rav *= 2;
		पूर्ण

		dev_dbg(dev, "vs config(RAV): src_h = %d, dst_h = %d, factor = %d, acc_init = %08x, acc_init_b = %08x\n",
			src_h, dst_h, factor, row_acc_init_rav,
			row_acc_init_rav_b);
	पूर्ण अन्यथा अणु
		/* use polyphase */
		row_acc_inc = ((src_h - 1) << 16) / (dst_h - 1);
		row_acc_offset = 0;
		row_acc_offset_b = 0;

		dev_dbg(dev, "vs config(POLY): src_h = %d, dst_h = %d,row_acc_inc = %08x\n",
			src_h, dst_h, row_acc_inc);
	पूर्ण


	sc_reg0[0] = val;
	sc_reg0[1] = row_acc_inc;
	sc_reg0[2] = row_acc_offset;
	sc_reg0[3] = row_acc_offset_b;

	sc_reg0[4] = ((lin_acc_inc_u & CFG_LIN_ACC_INC_U_MASK) <<
			CFG_LIN_ACC_INC_U_SHIFT) | (dst_w << CFG_TAR_W_SHIFT) |
			(dst_h << CFG_TAR_H_SHIFT);

	sc_reg0[5] = (src_w << CFG_SRC_W_SHIFT) | (src_h << CFG_SRC_H_SHIFT);

	sc_reg0[6] = (row_acc_init_rav_b << CFG_ROW_ACC_INIT_RAV_B_SHIFT) |
		(row_acc_init_rav << CFG_ROW_ACC_INIT_RAV_SHIFT);

	*sc_reg9 = lin_acc_inc;

	*sc_reg12 = col_acc_offset << CFG_COL_ACC_OFFSET_SHIFT;

	*sc_reg13 = factor;

	*sc_reg24 = (src_w << CFG_ORG_W_SHIFT) | (src_h << CFG_ORG_H_SHIFT);
पूर्ण
EXPORT_SYMBOL(sc_config_scaler);

काष्ठा sc_data *sc_create(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *res_name)
अणु
	काष्ठा sc_data *sc;

	dev_dbg(&pdev->dev, "sc_create\n");

	sc = devm_kzalloc(&pdev->dev, माप(*sc), GFP_KERNEL);
	अगर (!sc) अणु
		dev_err(&pdev->dev, "couldn't alloc sc_data\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	sc->pdev = pdev;

	sc->res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, res_name);
	अगर (!sc->res) अणु
		dev_err(&pdev->dev, "missing '%s' platform resources data\n",
			res_name);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	sc->base = devm_ioremap_resource(&pdev->dev, sc->res);
	अगर (IS_ERR(sc->base))
		वापस ERR_CAST(sc->base);

	वापस sc;
पूर्ण
EXPORT_SYMBOL(sc_create);

MODULE_DESCRIPTION("TI VIP/VPE Scaler");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_LICENSE("GPL v2");
