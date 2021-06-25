<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_top.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt, __func__

#समावेश <linux/spi/spi.h>

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_गणित.स>

#समावेश "cxd2880.h"
#समावेश "cxd2880_tnrdmd_mon.h"
#समावेश "cxd2880_tnrdmd_dvbt2_mon.h"
#समावेश "cxd2880_tnrdmd_dvbt_mon.h"
#समावेश "cxd2880_integ.h"
#समावेश "cxd2880_tnrdmd_dvbt2.h"
#समावेश "cxd2880_tnrdmd_dvbt.h"
#समावेश "cxd2880_devio_spi.h"
#समावेश "cxd2880_spi_device.h"
#समावेश "cxd2880_tnrdmd_driver_version.h"

काष्ठा cxd2880_priv अणु
	काष्ठा cxd2880_tnrdmd tnrdmd;
	काष्ठा spi_device *spi;
	काष्ठा cxd2880_io regio;
	काष्ठा cxd2880_spi_device spi_device;
	काष्ठा cxd2880_spi cxd2880_spi;
	काष्ठा cxd2880_dvbt_tune_param dvbt_tune_param;
	काष्ठा cxd2880_dvbt2_tune_param dvbt2_tune_param;
	काष्ठा mutex *spi_mutex; /* For SPI access exclusive control */
	अचिन्हित दीर्घ pre_ber_update;
	अचिन्हित दीर्घ pre_ber_पूर्णांकerval;
	अचिन्हित दीर्घ post_ber_update;
	अचिन्हित दीर्घ post_ber_पूर्णांकerval;
	अचिन्हित दीर्घ ucblock_update;
	अचिन्हित दीर्घ ucblock_पूर्णांकerval;
	क्रमागत fe_status s;
पूर्ण;

अटल पूर्णांक cxd2880_pre_bit_err_t(काष्ठा cxd2880_tnrdmd *tnrdmd,
				 u32 *pre_bit_err, u32 *pre_bit_count)
अणु
	u8 rdata[2];
	पूर्णांक ret;

	अगर (!tnrdmd || !pre_bit_err || !pre_bit_count)
		वापस -EINVAL;

	अगर (tnrdmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnrdmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnrdmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnrdmd);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x10);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x39, rdata, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	अगर ((rdata[0] & 0x01) == 0) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस -EAGAIN;
	पूर्ण

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x22, rdata, 2);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	*pre_bit_err = (rdata[0] << 8) | rdata[1];

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x6f, rdata, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	slvt_unमुक्तze_reg(tnrdmd);

	*pre_bit_count = ((rdata[0] & 0x07) == 0) ?
			 256 : (0x1000 << (rdata[0] & 0x07));

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_pre_bit_err_t2(काष्ठा cxd2880_tnrdmd *tnrdmd,
				  u32 *pre_bit_err,
				  u32 *pre_bit_count)
अणु
	u32 period_exp = 0;
	u32 n_ldpc = 0;
	u8 data[5];
	पूर्णांक ret;

	अगर (!tnrdmd || !pre_bit_err || !pre_bit_count)
		वापस -EINVAL;

	अगर (tnrdmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnrdmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnrdmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnrdmd);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x3c, data, माप(data));
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	अगर (!(data[0] & 0x01)) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस -EAGAIN;
	पूर्ण
	*pre_bit_err =
	((data[1] & 0x0f) << 24) | (data[2] << 16) | (data[3] << 8) | data[4];

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0xa0, data, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	अगर (((क्रमागत cxd2880_dvbt2_plp_fec)(data[0] & 0x03)) ==
	    CXD2880_DVBT2_FEC_LDPC_16K)
		n_ldpc = 16200;
	अन्यथा
		n_ldpc = 64800;
	slvt_unमुक्तze_reg(tnrdmd);

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x20);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x6f, data, 1);
	अगर (ret)
		वापस ret;

	period_exp = data[0] & 0x0f;

	*pre_bit_count = (1U << period_exp) * n_ldpc;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_post_bit_err_t(काष्ठा cxd2880_tnrdmd *tnrdmd,
				  u32 *post_bit_err,
				  u32 *post_bit_count)
अणु
	u8 rdata[3];
	u32 bit_error = 0;
	u32 period_exp = 0;
	पूर्णांक ret;

	अगर (!tnrdmd || !post_bit_err || !post_bit_count)
		वापस -EINVAL;

	अगर (tnrdmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnrdmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnrdmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0d);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x15, rdata, 3);
	अगर (ret)
		वापस ret;

	अगर ((rdata[0] & 0x40) == 0)
		वापस -EAGAIN;

	*post_bit_err = ((rdata[0] & 0x3f) << 16) | (rdata[1] << 8) | rdata[2];

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x10);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x60, rdata, 1);
	अगर (ret)
		वापस ret;

	period_exp = (rdata[0] & 0x1f);

	अगर (period_exp <= 11 && (bit_error > (1U << period_exp) * 204 * 8))
		वापस -EAGAIN;

	*post_bit_count = (1U << period_exp) * 204 * 8;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_post_bit_err_t2(काष्ठा cxd2880_tnrdmd *tnrdmd,
				   u32 *post_bit_err,
				   u32 *post_bit_count)
अणु
	u32 period_exp = 0;
	u32 n_bch = 0;
	u8 data[3];
	क्रमागत cxd2880_dvbt2_plp_fec plp_fec_type =
		CXD2880_DVBT2_FEC_LDPC_16K;
	क्रमागत cxd2880_dvbt2_plp_code_rate plp_code_rate =
		CXD2880_DVBT2_R1_2;
	पूर्णांक ret;
	अटल स्थिर u16 n_bch_bits_lookup[2][8] = अणु
		अणु7200, 9720, 10800, 11880, 12600, 13320, 5400, 6480पूर्ण,
		अणु32400, 38880, 43200, 48600, 51840, 54000, 21600, 25920पूर्ण
	पूर्ण;

	अगर (!tnrdmd || !post_bit_err || !post_bit_count)
		वापस -EINVAL;

	अगर (tnrdmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnrdmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnrdmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = slvt_मुक्तze_reg(tnrdmd);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0b);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x15, data, 3);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	अगर (!(data[0] & 0x40)) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस -EAGAIN;
	पूर्ण

	*post_bit_err =
		((data[0] & 0x3f) << 16) | (data[1] << 8) | data[2];

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x9d, data, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	plp_code_rate =
	(क्रमागत cxd2880_dvbt2_plp_code_rate)(data[0] & 0x07);

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0xa0, data, 1);
	अगर (ret) अणु
		slvt_unमुक्तze_reg(tnrdmd);
		वापस ret;
	पूर्ण

	plp_fec_type = (क्रमागत cxd2880_dvbt2_plp_fec)(data[0] & 0x03);

	slvt_unमुक्तze_reg(tnrdmd);

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x20);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x72, data, 1);
	अगर (ret)
		वापस ret;

	period_exp = data[0] & 0x0f;

	अगर (plp_fec_type > CXD2880_DVBT2_FEC_LDPC_64K ||
	    plp_code_rate > CXD2880_DVBT2_R2_5)
		वापस -EAGAIN;

	n_bch = n_bch_bits_lookup[plp_fec_type][plp_code_rate];

	अगर (*post_bit_err > ((1U << period_exp) * n_bch))
		वापस -EAGAIN;

	*post_bit_count = (1U << period_exp) * n_bch;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_पढ़ो_block_err_t(काष्ठा cxd2880_tnrdmd *tnrdmd,
				    u32 *block_err,
				    u32 *block_count)
अणु
	u8 rdata[3];
	पूर्णांक ret;

	अगर (!tnrdmd || !block_err || !block_count)
		वापस -EINVAL;

	अगर (tnrdmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnrdmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	अगर (tnrdmd->sys != CXD2880_DTV_SYS_DVBT)
		वापस -EINVAL;

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0d);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x18, rdata, 3);
	अगर (ret)
		वापस ret;

	अगर ((rdata[0] & 0x01) == 0)
		वापस -EAGAIN;

	*block_err = (rdata[1] << 8) | rdata[2];

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x10);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x5c, rdata, 1);
	अगर (ret)
		वापस ret;

	*block_count = 1U << (rdata[0] & 0x0f);

	अगर ((*block_count == 0) || (*block_err > *block_count))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_पढ़ो_block_err_t2(काष्ठा cxd2880_tnrdmd *tnrdmd,
				     u32 *block_err,
				     u32 *block_count)
अणु
	u8 rdata[3];
	पूर्णांक ret;

	अगर (!tnrdmd || !block_err || !block_count)
		वापस -EINVAL;

	अगर (tnrdmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnrdmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;
	अगर (tnrdmd->sys != CXD2880_DTV_SYS_DVBT2)
		वापस -EINVAL;

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0b);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x18, rdata, 3);
	अगर (ret)
		वापस ret;

	अगर ((rdata[0] & 0x01) == 0)
		वापस -EAGAIN;

	*block_err = (rdata[1] << 8) | rdata[2];

	ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x24);
	अगर (ret)
		वापस ret;

	ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0xdc, rdata, 1);
	अगर (ret)
		वापस ret;

	*block_count = 1U << (rdata[0] & 0x0f);

	अगर ((*block_count == 0) || (*block_err > *block_count))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल व्योम cxd2880_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2880_priv *priv = शून्य;

	अगर (!fe) अणु
		pr_err("invalid arg.\n");
		वापस;
	पूर्ण
	priv = fe->demodulator_priv;
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक cxd2880_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv = शून्य;
	काष्ठा cxd2880_tnrdmd_create_param create_param;

	अगर (!fe) अणु
		pr_err("invalid arg.\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;

	create_param.ts_output_अगर = CXD2880_TNRDMD_TSOUT_IF_SPI;
	create_param.xtal_share_type = CXD2880_TNRDMD_XTAL_SHARE_NONE;
	create_param.en_पूर्णांकernal_lकरो = 1;
	create_param.xosc_cap = 18;
	create_param.xosc_i = 8;
	create_param.stationary_use = 1;

	mutex_lock(priv->spi_mutex);
	अगर (priv->tnrdmd.io != &priv->regio) अणु
		ret = cxd2880_tnrdmd_create(&priv->tnrdmd,
					    &priv->regio, &create_param);
		अगर (ret) अणु
			mutex_unlock(priv->spi_mutex);
			pr_info("cxd2880 tnrdmd create failed %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	ret = cxd2880_पूर्णांकeg_init(&priv->tnrdmd);
	अगर (ret) अणु
		mutex_unlock(priv->spi_mutex);
		pr_err("cxd2880 integ init failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
				     CXD2880_TNRDMD_CFG_TSPIN_CURRENT,
				     0x00);
	अगर (ret) अणु
		mutex_unlock(priv->spi_mutex);
		pr_err("cxd2880 set config failed %d\n", ret);
		वापस ret;
	पूर्ण
	mutex_unlock(priv->spi_mutex);

	pr_debug("OK.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_sleep(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv = शून्य;

	अगर (!fe) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_sleep(&priv->tnrdmd);
	mutex_unlock(priv->spi_mutex);

	pr_debug("tnrdmd_sleep ret %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					u16 *strength)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv = शून्य;
	काष्ठा dtv_frontend_properties *c = शून्य;
	पूर्णांक level = 0;

	अगर (!fe || !strength) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;

	mutex_lock(priv->spi_mutex);
	अगर (c->delivery_प्रणाली == SYS_DVBT ||
	    c->delivery_प्रणाली == SYS_DVBT2) अणु
		ret = cxd2880_tnrdmd_mon_rf_lvl(&priv->tnrdmd, &level);
	पूर्ण अन्यथा अणु
		pr_debug("invalid system\n");
		mutex_unlock(priv->spi_mutex);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(priv->spi_mutex);

	level /= 125;
	/*
	 * level should be between -105dBm and -30dBm.
	 * E.g. they should be between:
	 * -105000/125 = -840 and -30000/125 = -240
	 */
	level = clamp(level, -840, -240);
	/* scale value to 0x0000-0xffff */
	*strength = ((level + 840) * 0xffff) / (-240 + 840);

	अगर (ret)
		pr_debug("ret = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	पूर्णांक ret;
	पूर्णांक snrvalue = 0;
	काष्ठा cxd2880_priv *priv = शून्य;
	काष्ठा dtv_frontend_properties *c = शून्य;

	अगर (!fe || !snr) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;

	mutex_lock(priv->spi_mutex);
	अगर (c->delivery_प्रणाली == SYS_DVBT) अणु
		ret = cxd2880_tnrdmd_dvbt_mon_snr(&priv->tnrdmd,
						  &snrvalue);
	पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
		ret = cxd2880_tnrdmd_dvbt2_mon_snr(&priv->tnrdmd,
						   &snrvalue);
	पूर्ण अन्यथा अणु
		pr_err("invalid system\n");
		mutex_unlock(priv->spi_mutex);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(priv->spi_mutex);

	अगर (snrvalue < 0)
		snrvalue = 0;
	*snr = snrvalue;

	अगर (ret)
		pr_debug("ret = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv = शून्य;
	काष्ठा dtv_frontend_properties *c = शून्य;

	अगर (!fe || !ucblocks) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;

	mutex_lock(priv->spi_mutex);
	अगर (c->delivery_प्रणाली == SYS_DVBT) अणु
		ret = cxd2880_tnrdmd_dvbt_mon_packet_error_number(&priv->tnrdmd,
								  ucblocks);
	पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
		ret = cxd2880_tnrdmd_dvbt2_mon_packet_error_number(&priv->tnrdmd,
								   ucblocks);
	पूर्ण अन्यथा अणु
		pr_err("invalid system\n");
		mutex_unlock(priv->spi_mutex);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(priv->spi_mutex);

	अगर (ret)
		pr_debug("ret = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	*ber = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_set_ber_per_period_t(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv;
	काष्ठा cxd2880_dvbt_tpsinfo info;
	क्रमागत cxd2880_dtv_bandwidth bw;
	u32 pre_ber_rate = 0;
	u32 post_ber_rate = 0;
	u32 ucblock_rate = 0;
	u32 mes_exp = 0;
	अटल स्थिर पूर्णांक cr_table[5] = अणु31500, 42000, 47250, 52500, 55125पूर्ण;
	अटल स्थिर पूर्णांक denominator_tbl[4] = अणु125664, 129472, 137088, 152320पूर्ण;

	अगर (!fe) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;
	bw = priv->dvbt_tune_param.bandwidth;

	ret = cxd2880_tnrdmd_dvbt_mon_tps_info(&priv->tnrdmd,
					       &info);
	अगर (ret) अणु
		pr_err("tps monitor error ret = %d\n", ret);
		info.hierarchy = CXD2880_DVBT_HIERARCHY_NON;
		info.स्थिरellation = CXD2880_DVBT_CONSTELLATION_QPSK;
		info.guard = CXD2880_DVBT_GUARD_1_4;
		info.rate_hp = CXD2880_DVBT_CODERATE_1_2;
		info.rate_lp = CXD2880_DVBT_CODERATE_1_2;
	पूर्ण

	अगर (info.hierarchy == CXD2880_DVBT_HIERARCHY_NON) अणु
		pre_ber_rate = 63000000 * bw * (info.स्थिरellation * 2 + 2) /
			       denominator_tbl[info.guard];

		post_ber_rate =	1000 * cr_table[info.rate_hp] * bw *
				(info.स्थिरellation * 2 + 2) /
				denominator_tbl[info.guard];

		ucblock_rate = 875 * cr_table[info.rate_hp] * bw *
			       (info.स्थिरellation * 2 + 2) /
			       denominator_tbl[info.guard];
	पूर्ण अन्यथा अणु
		u8 data = 0;
		काष्ठा cxd2880_tnrdmd *tnrdmd = &priv->tnrdmd;

		ret = tnrdmd->io->ग_लिखो_reg(tnrdmd->io,
					    CXD2880_IO_TGT_DMD,
					    0x00, 0x10);
		अगर (!ret) अणु
			ret = tnrdmd->io->पढ़ो_regs(tnrdmd->io,
						    CXD2880_IO_TGT_DMD,
						    0x67, &data, 1);
			अगर (ret)
				data = 0x00;
		पूर्ण अन्यथा अणु
			data = 0x00;
		पूर्ण

		अगर (data & 0x01) अणु /* Low priority */
			pre_ber_rate =
				63000000 * bw * (info.स्थिरellation * 2 + 2) /
				denominator_tbl[info.guard];

			post_ber_rate = 1000 * cr_table[info.rate_lp] * bw *
					(info.स्थिरellation * 2 + 2) /
					denominator_tbl[info.guard];

			ucblock_rate = (1000 * 7 / 8) *	cr_table[info.rate_lp] *
				       bw * (info.स्थिरellation * 2 + 2) /
				       denominator_tbl[info.guard];
		पूर्ण अन्यथा अणु /* High priority */
			pre_ber_rate =
				63000000 * bw * 2 / denominator_tbl[info.guard];

			post_ber_rate = 1000 * cr_table[info.rate_hp] * bw * 2 /
					denominator_tbl[info.guard];

			ucblock_rate = (1000 * 7 / 8) * cr_table[info.rate_hp] *
					bw * 2 / denominator_tbl[info.guard];
		पूर्ण
	पूर्ण

	mes_exp = pre_ber_rate < 8192 ? 8 : पूर्णांकlog2(pre_ber_rate) >> 24;
	priv->pre_ber_पूर्णांकerval =
		((1U << mes_exp) * 1000 + (pre_ber_rate / 2)) /
		pre_ber_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT_VBER_PERIOD,
			       mes_exp == 8 ? 0 : mes_exp - 12);

	mes_exp = पूर्णांकlog2(post_ber_rate) >> 24;
	priv->post_ber_पूर्णांकerval =
		((1U << mes_exp) * 1000 + (post_ber_rate / 2)) /
		post_ber_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT_BERN_PERIOD,
			       mes_exp);

	mes_exp = पूर्णांकlog2(ucblock_rate) >> 24;
	priv->ucblock_पूर्णांकerval =
		((1U << mes_exp) * 1000 + (ucblock_rate / 2)) /
		ucblock_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT_PER_MES,
			       mes_exp);

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_set_ber_per_period_t2(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv;
	काष्ठा cxd2880_dvbt2_l1pre l1pre;
	काष्ठा cxd2880_dvbt2_l1post l1post;
	काष्ठा cxd2880_dvbt2_plp plp;
	काष्ठा cxd2880_dvbt2_bbheader bbheader;
	क्रमागत cxd2880_dtv_bandwidth bw = CXD2880_DTV_BW_1_7_MHZ;
	u32 pre_ber_rate = 0;
	u32 post_ber_rate = 0;
	u32 ucblock_rate = 0;
	u32 mes_exp = 0;
	u32 term_a = 0;
	u32 term_b = 0;
	u32 denominator = 0;
	अटल स्थिर u32 gi_tbl[7] = अणु32, 64, 128, 256, 8, 152, 76पूर्ण;
	अटल स्थिर u8 n_tbl[6] = अणु8, 2, 4, 16, 1, 1पूर्ण;
	अटल स्थिर u8 mode_tbl[6] = अणु2, 8, 4, 1, 16, 32पूर्ण;
	अटल स्थिर u32 kbch_tbl[2][8] = अणु
		अणु6952, 9472, 10552, 11632, 12352, 13072, 5152, 6232पूर्ण,
		अणु32128, 38608, 42960, 48328, 51568, 53760, 0, 0पूर्ण
	पूर्ण;

	अगर (!fe) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;
	bw = priv->dvbt2_tune_param.bandwidth;

	ret = cxd2880_tnrdmd_dvbt2_mon_l1_pre(&priv->tnrdmd, &l1pre);
	अगर (ret) अणु
		pr_info("l1 pre error\n");
		जाओ error_ber_setting;
	पूर्ण

	ret = cxd2880_tnrdmd_dvbt2_mon_active_plp(&priv->tnrdmd,
						  CXD2880_DVBT2_PLP_DATA, &plp);
	अगर (ret) अणु
		pr_info("plp info error\n");
		जाओ error_ber_setting;
	पूर्ण

	ret = cxd2880_tnrdmd_dvbt2_mon_l1_post(&priv->tnrdmd, &l1post);
	अगर (ret) अणु
		pr_info("l1 post error\n");
		जाओ error_ber_setting;
	पूर्ण

	term_a =
		(mode_tbl[l1pre.fft_mode] * (1024 + gi_tbl[l1pre.gi])) *
		(l1pre.num_symbols + n_tbl[l1pre.fft_mode]) + 2048;

	अगर (l1pre.mixed && l1post.fef_पूर्णांकvl) अणु
		term_b = (l1post.fef_length + (l1post.fef_पूर्णांकvl / 2)) /
			 l1post.fef_पूर्णांकvl;
	पूर्ण अन्यथा अणु
		term_b = 0;
	पूर्ण

	चयन (bw) अणु
	हाल CXD2880_DTV_BW_1_7_MHZ:
		denominator = ((term_a + term_b) * 71 + (131 / 2)) / 131;
		अवरोध;
	हाल CXD2880_DTV_BW_5_MHZ:
		denominator = ((term_a + term_b) * 7 + 20) / 40;
		अवरोध;
	हाल CXD2880_DTV_BW_6_MHZ:
		denominator = ((term_a + term_b) * 7 + 24) / 48;
		अवरोध;
	हाल CXD2880_DTV_BW_7_MHZ:
		denominator = ((term_a + term_b) + 4) / 8;
		अवरोध;
	हाल CXD2880_DTV_BW_8_MHZ:
	शेष:
		denominator = ((term_a + term_b) * 7 + 32) / 64;
		अवरोध;
	पूर्ण

	अगर (plp.til_type && plp.til_len) अणु
		pre_ber_rate =
			(plp.num_blocks_max * 1000000 + (denominator / 2)) /
			denominator;
		pre_ber_rate = (pre_ber_rate + (plp.til_len / 2)) /
			       plp.til_len;
	पूर्ण अन्यथा अणु
		pre_ber_rate =
			(plp.num_blocks_max * 1000000 + (denominator / 2)) /
			denominator;
	पूर्ण

	post_ber_rate = pre_ber_rate;

	mes_exp = पूर्णांकlog2(pre_ber_rate) >> 24;
	priv->pre_ber_पूर्णांकerval =
		((1U << mes_exp) * 1000 + (pre_ber_rate / 2)) /
		pre_ber_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_LBER_MES,
			       mes_exp);

	mes_exp = पूर्णांकlog2(post_ber_rate) >> 24;
	priv->post_ber_पूर्णांकerval =
		((1U << mes_exp) * 1000 + (post_ber_rate / 2)) /
		post_ber_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_BBER_MES,
			       mes_exp);

	ret = cxd2880_tnrdmd_dvbt2_mon_bbheader(&priv->tnrdmd,
						CXD2880_DVBT2_PLP_DATA,
						&bbheader);
	अगर (ret) अणु
		pr_info("bb header error\n");
		जाओ error_ucblock_setting;
	पूर्ण

	अगर (bbheader.plp_mode == CXD2880_DVBT2_PLP_MODE_NM) अणु
		अगर (!bbheader.issy_indicator) अणु
			ucblock_rate =
				(pre_ber_rate * kbch_tbl[plp.fec][plp.plp_cr] +
				752) / 1504;
		पूर्ण अन्यथा अणु
			ucblock_rate =
				(pre_ber_rate * kbch_tbl[plp.fec][plp.plp_cr] +
				764) / 1528;
		पूर्ण
	पूर्ण अन्यथा अगर (bbheader.plp_mode == CXD2880_DVBT2_PLP_MODE_HEM) अणु
		ucblock_rate =
			(pre_ber_rate * kbch_tbl[plp.fec][plp.plp_cr] + 748) /
			1496;
	पूर्ण अन्यथा अणु
		pr_info("plp mode is not Normal or HEM\n");
		जाओ error_ucblock_setting;
	पूर्ण

	mes_exp = पूर्णांकlog2(ucblock_rate) >> 24;
	priv->ucblock_पूर्णांकerval =
		((1U << mes_exp) * 1000 + (ucblock_rate / 2)) /
		ucblock_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_PER_MES,
			       mes_exp);

	वापस 0;

error_ber_setting:
	priv->pre_ber_पूर्णांकerval = 1000;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
				     CXD2880_TNRDMD_CFG_DVBT2_LBER_MES, 0);

	priv->post_ber_पूर्णांकerval = 1000;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_BBER_MES, 0);

error_ucblock_setting:
	priv->ucblock_पूर्णांकerval = 1000;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_PER_MES, 8);

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_dvbt_tune(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			     काष्ठा cxd2880_dvbt_tune_param
			     *tune_param)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd || !tune_param)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	atomic_set(&tnr_dmd->cancel, 0);

	अगर (tune_param->bandwidth != CXD2880_DTV_BW_5_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_6_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_7_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_8_MHZ) अणु
		वापस -ENOTTY;
	पूर्ण

	ret = cxd2880_tnrdmd_dvbt_tune1(tnr_dmd, tune_param);
	अगर (ret)
		वापस ret;

	usleep_range(CXD2880_TNRDMD_WAIT_AGC_STABLE * 10000,
		     CXD2880_TNRDMD_WAIT_AGC_STABLE * 10000 + 1000);

	वापस cxd2880_tnrdmd_dvbt_tune2(tnr_dmd, tune_param);
पूर्ण

अटल पूर्णांक cxd2880_dvbt2_tune(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      काष्ठा cxd2880_dvbt2_tune_param
			      *tune_param)
अणु
	पूर्णांक ret;

	अगर (!tnr_dmd || !tune_param)
		वापस -EINVAL;

	अगर (tnr_dmd->भागer_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		वापस -EINVAL;

	अगर (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		वापस -EINVAL;

	atomic_set(&tnr_dmd->cancel, 0);

	अगर (tune_param->bandwidth != CXD2880_DTV_BW_1_7_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_5_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_6_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_7_MHZ &&
	    tune_param->bandwidth != CXD2880_DTV_BW_8_MHZ) अणु
		वापस -ENOTTY;
	पूर्ण

	अगर (tune_param->profile != CXD2880_DVBT2_PROखाता_BASE &&
	    tune_param->profile != CXD2880_DVBT2_PROखाता_LITE)
		वापस -EINVAL;

	ret = cxd2880_tnrdmd_dvbt2_tune1(tnr_dmd, tune_param);
	अगर (ret)
		वापस ret;

	usleep_range(CXD2880_TNRDMD_WAIT_AGC_STABLE * 10000,
		     CXD2880_TNRDMD_WAIT_AGC_STABLE * 10000 + 1000);

	वापस cxd2880_tnrdmd_dvbt2_tune2(tnr_dmd, tune_param);
पूर्ण

अटल पूर्णांक cxd2880_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा dtv_frontend_properties *c;
	काष्ठा cxd2880_priv *priv;
	क्रमागत cxd2880_dtv_bandwidth bw = CXD2880_DTV_BW_1_7_MHZ;

	अगर (!fe) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;

	c->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->pre_bit_error.stat[0].uvalue = 0;
	c->pre_bit_error.len = 1;
	c->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->pre_bit_count.stat[0].uvalue = 0;
	c->pre_bit_count.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.stat[0].uvalue = 0;
	c->post_bit_error.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].uvalue = 0;
	c->post_bit_count.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.stat[0].uvalue = 0;
	c->block_error.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.stat[0].uvalue = 0;
	c->block_count.len = 1;

	चयन (c->bandwidth_hz) अणु
	हाल 1712000:
		bw = CXD2880_DTV_BW_1_7_MHZ;
		अवरोध;
	हाल 5000000:
		bw = CXD2880_DTV_BW_5_MHZ;
		अवरोध;
	हाल 6000000:
		bw = CXD2880_DTV_BW_6_MHZ;
		अवरोध;
	हाल 7000000:
		bw = CXD2880_DTV_BW_7_MHZ;
		अवरोध;
	हाल 8000000:
		bw = CXD2880_DTV_BW_8_MHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	priv->s = 0;

	pr_info("sys:%d freq:%d bw:%d\n",
		c->delivery_प्रणाली, c->frequency, bw);
	mutex_lock(priv->spi_mutex);
	अगर (c->delivery_प्रणाली == SYS_DVBT) अणु
		priv->tnrdmd.sys = CXD2880_DTV_SYS_DVBT;
		priv->dvbt_tune_param.center_freq_khz = c->frequency / 1000;
		priv->dvbt_tune_param.bandwidth = bw;
		priv->dvbt_tune_param.profile = CXD2880_DVBT_PROखाता_HP;
		ret = cxd2880_dvbt_tune(&priv->tnrdmd,
					&priv->dvbt_tune_param);
	पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
		priv->tnrdmd.sys = CXD2880_DTV_SYS_DVBT2;
		priv->dvbt2_tune_param.center_freq_khz = c->frequency / 1000;
		priv->dvbt2_tune_param.bandwidth = bw;
		priv->dvbt2_tune_param.data_plp_id = (u16)c->stream_id;
		priv->dvbt2_tune_param.profile = CXD2880_DVBT2_PROखाता_BASE;
		ret = cxd2880_dvbt2_tune(&priv->tnrdmd,
					 &priv->dvbt2_tune_param);
	पूर्ण अन्यथा अणु
		pr_err("invalid system\n");
		mutex_unlock(priv->spi_mutex);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(priv->spi_mutex);

	pr_info("tune result %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_get_stats(काष्ठा dvb_frontend *fe,
			     क्रमागत fe_status status)
अणु
	काष्ठा cxd2880_priv *priv = शून्य;
	काष्ठा dtv_frontend_properties *c = शून्य;
	u32 pre_bit_err = 0, pre_bit_count = 0;
	u32 post_bit_err = 0, post_bit_count = 0;
	u32 block_err = 0, block_count = 0;
	पूर्णांक ret;

	अगर (!fe) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;

	अगर (!(status & FE_HAS_LOCK) || !(status & FE_HAS_CARRIER)) अणु
		c->pre_bit_error.len = 1;
		c->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->pre_bit_count.len = 1;
		c->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_error.len = 1;
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.len = 1;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.len = 1;
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.len = 1;
		c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

		वापस 0;
	पूर्ण

	अगर (समय_after(jअगरfies, priv->pre_ber_update)) अणु
		priv->pre_ber_update =
			 jअगरfies + msecs_to_jअगरfies(priv->pre_ber_पूर्णांकerval);
		अगर (c->delivery_प्रणाली == SYS_DVBT) अणु
			mutex_lock(priv->spi_mutex);
			ret = cxd2880_pre_bit_err_t(&priv->tnrdmd,
						    &pre_bit_err,
						    &pre_bit_count);
			mutex_unlock(priv->spi_mutex);
		पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
			mutex_lock(priv->spi_mutex);
			ret = cxd2880_pre_bit_err_t2(&priv->tnrdmd,
						     &pre_bit_err,
						     &pre_bit_count);
			mutex_unlock(priv->spi_mutex);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		अगर (!ret) अणु
			c->pre_bit_error.len = 1;
			c->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->pre_bit_error.stat[0].uvalue += pre_bit_err;
			c->pre_bit_count.len = 1;
			c->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
			c->pre_bit_count.stat[0].uvalue += pre_bit_count;
		पूर्ण अन्यथा अणु
			c->pre_bit_error.len = 1;
			c->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			c->pre_bit_count.len = 1;
			c->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			pr_debug("pre_bit_error_t failed %d\n", ret);
		पूर्ण
	पूर्ण

	अगर (समय_after(jअगरfies, priv->post_ber_update)) अणु
		priv->post_ber_update =
			jअगरfies + msecs_to_jअगरfies(priv->post_ber_पूर्णांकerval);
		अगर (c->delivery_प्रणाली == SYS_DVBT) अणु
			mutex_lock(priv->spi_mutex);
			ret = cxd2880_post_bit_err_t(&priv->tnrdmd,
						     &post_bit_err,
						     &post_bit_count);
			mutex_unlock(priv->spi_mutex);
		पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
			mutex_lock(priv->spi_mutex);
			ret = cxd2880_post_bit_err_t2(&priv->tnrdmd,
						      &post_bit_err,
						      &post_bit_count);
			mutex_unlock(priv->spi_mutex);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		अगर (!ret) अणु
			c->post_bit_error.len = 1;
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue += post_bit_err;
			c->post_bit_count.len = 1;
			c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_count.stat[0].uvalue += post_bit_count;
		पूर्ण अन्यथा अणु
			c->post_bit_error.len = 1;
			c->post_bit_error.stat[0].scale =
							FE_SCALE_NOT_AVAILABLE;
			c->post_bit_count.len = 1;
			c->post_bit_count.stat[0].scale =
							FE_SCALE_NOT_AVAILABLE;
			pr_debug("post_bit_err_t %d\n", ret);
		पूर्ण
	पूर्ण

	अगर (समय_after(jअगरfies, priv->ucblock_update)) अणु
		priv->ucblock_update =
			jअगरfies + msecs_to_jअगरfies(priv->ucblock_पूर्णांकerval);
		अगर (c->delivery_प्रणाली == SYS_DVBT) अणु
			mutex_lock(priv->spi_mutex);
			ret = cxd2880_पढ़ो_block_err_t(&priv->tnrdmd,
						       &block_err,
						       &block_count);
			mutex_unlock(priv->spi_mutex);
		पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
			mutex_lock(priv->spi_mutex);
			ret = cxd2880_पढ़ो_block_err_t2(&priv->tnrdmd,
							&block_err,
							&block_count);
			mutex_unlock(priv->spi_mutex);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अगर (!ret) अणु
			c->block_error.len = 1;
			c->block_error.stat[0].scale = FE_SCALE_COUNTER;
			c->block_error.stat[0].uvalue += block_err;
			c->block_count.len = 1;
			c->block_count.stat[0].scale = FE_SCALE_COUNTER;
			c->block_count.stat[0].uvalue += block_count;
		पूर्ण अन्यथा अणु
			c->block_error.len = 1;
			c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			c->block_count.len = 1;
			c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			pr_debug("read_block_err_t  %d\n", ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_check_l1post_plp(काष्ठा dvb_frontend *fe)
अणु
	u8 valid = 0;
	u8 plp_not_found;
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv = शून्य;

	अगर (!fe) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;

	ret = cxd2880_tnrdmd_dvbt2_check_l1post_valid(&priv->tnrdmd,
						      &valid);
	अगर (ret)
		वापस ret;

	अगर (!valid)
		वापस -EAGAIN;

	ret = cxd2880_tnrdmd_dvbt2_mon_data_plp_error(&priv->tnrdmd,
						      &plp_not_found);
	अगर (ret)
		वापस ret;

	अगर (plp_not_found) अणु
		priv->dvbt2_tune_param.tune_info =
			CXD2880_TNRDMD_DVBT2_TUNE_INFO_INVALID_PLP_ID;
	पूर्ण अन्यथा अणु
		priv->dvbt2_tune_param.tune_info =
			CXD2880_TNRDMD_DVBT2_TUNE_INFO_OK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *status)
अणु
	पूर्णांक ret;
	u8 sync = 0;
	u8 lock = 0;
	u8 unlock = 0;
	काष्ठा cxd2880_priv *priv = शून्य;
	काष्ठा dtv_frontend_properties *c = शून्य;

	अगर (!fe || !status) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;
	*status = 0;

	अगर (priv->tnrdmd.state == CXD2880_TNRDMD_STATE_ACTIVE) अणु
		mutex_lock(priv->spi_mutex);
		अगर (c->delivery_प्रणाली == SYS_DVBT) अणु
			ret = cxd2880_tnrdmd_dvbt_mon_sync_stat(&priv->tnrdmd,
								&sync,
								&lock,
								&unlock);
		पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
			ret = cxd2880_tnrdmd_dvbt2_mon_sync_stat(&priv->tnrdmd,
								 &sync,
								 &lock,
								 &unlock);
		पूर्ण अन्यथा अणु
			pr_err("invalid system");
			mutex_unlock(priv->spi_mutex);
			वापस -EINVAL;
		पूर्ण

		mutex_unlock(priv->spi_mutex);
		अगर (ret) अणु
			pr_err("failed. sys = %d\n", priv->tnrdmd.sys);
			वापस  ret;
		पूर्ण

		अगर (sync == 6) अणु
			*status = FE_HAS_SIGNAL |
				  FE_HAS_CARRIER;
		पूर्ण
		अगर (lock)
			*status |= FE_HAS_VITERBI |
				   FE_HAS_SYNC |
				   FE_HAS_LOCK;
	पूर्ण

	pr_debug("status %d\n", *status);

	अगर (priv->s == 0 && (*status & FE_HAS_LOCK) &&
	    (*status & FE_HAS_CARRIER)) अणु
		mutex_lock(priv->spi_mutex);
		अगर (c->delivery_प्रणाली == SYS_DVBT) अणु
			ret = cxd2880_set_ber_per_period_t(fe);
			priv->s = *status;
		पूर्ण अन्यथा अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
			ret = cxd2880_check_l1post_plp(fe);
			अगर (!ret) अणु
				ret = cxd2880_set_ber_per_period_t2(fe);
				priv->s = *status;
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_err("invalid system\n");
			mutex_unlock(priv->spi_mutex);
			वापस -EINVAL;
		पूर्ण
		mutex_unlock(priv->spi_mutex);
	पूर्ण

	cxd2880_get_stats(fe, *status);
	वापस  0;
पूर्ण

अटल पूर्णांक cxd2880_tune(काष्ठा dvb_frontend *fe,
			bool retune,
			अचिन्हित पूर्णांक mode_flags,
			अचिन्हित पूर्णांक *delay,
			क्रमागत fe_status *status)
अणु
	पूर्णांक ret;

	अगर (!fe || !delay || !status) अणु
		pr_err("invalid arg.");
		वापस -EINVAL;
	पूर्ण

	अगर (retune) अणु
		ret = cxd2880_set_frontend(fe);
		अगर (ret) अणु
			pr_err("cxd2880_set_frontend failed %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	*delay = HZ / 5;

	वापस cxd2880_पढ़ो_status(fe, status);
पूर्ण

अटल पूर्णांक cxd2880_get_frontend_t(काष्ठा dvb_frontend *fe,
				  काष्ठा dtv_frontend_properties *c)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv = शून्य;
	क्रमागत cxd2880_dvbt_mode mode = CXD2880_DVBT_MODE_2K;
	क्रमागत cxd2880_dvbt_guard guard = CXD2880_DVBT_GUARD_1_32;
	काष्ठा cxd2880_dvbt_tpsinfo tps;
	क्रमागत cxd2880_tnrdmd_spectrum_sense sense;
	u16 snr = 0;
	पूर्णांक strength = 0;

	अगर (!fe || !c) अणु
		pr_err("invalid arg\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt_mon_mode_guard(&priv->tnrdmd,
						 &mode, &guard);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		चयन (mode) अणु
		हाल CXD2880_DVBT_MODE_2K:
			c->transmission_mode = TRANSMISSION_MODE_2K;
			अवरोध;
		हाल CXD2880_DVBT_MODE_8K:
			c->transmission_mode = TRANSMISSION_MODE_8K;
			अवरोध;
		शेष:
			c->transmission_mode = TRANSMISSION_MODE_2K;
			pr_debug("transmission mode is invalid %d\n", mode);
			अवरोध;
		पूर्ण
		चयन (guard) अणु
		हाल CXD2880_DVBT_GUARD_1_32:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
			अवरोध;
		हाल CXD2880_DVBT_GUARD_1_16:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
			अवरोध;
		हाल CXD2880_DVBT_GUARD_1_8:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
			अवरोध;
		हाल CXD2880_DVBT_GUARD_1_4:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
			अवरोध;
		शेष:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
			pr_debug("guard interval is invalid %d\n",
				 guard);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->transmission_mode = TRANSMISSION_MODE_2K;
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		pr_debug("ModeGuard err %d\n", ret);
	पूर्ण

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt_mon_tps_info(&priv->tnrdmd, &tps);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		चयन (tps.hierarchy) अणु
		हाल CXD2880_DVBT_HIERARCHY_NON:
			c->hierarchy = HIERARCHY_NONE;
			अवरोध;
		हाल CXD2880_DVBT_HIERARCHY_1:
			c->hierarchy = HIERARCHY_1;
			अवरोध;
		हाल CXD2880_DVBT_HIERARCHY_2:
			c->hierarchy = HIERARCHY_2;
			अवरोध;
		हाल CXD2880_DVBT_HIERARCHY_4:
			c->hierarchy = HIERARCHY_4;
			अवरोध;
		शेष:
			c->hierarchy = HIERARCHY_NONE;
			pr_debug("TPSInfo hierarchy is invalid %d\n",
				 tps.hierarchy);
			अवरोध;
		पूर्ण

		चयन (tps.rate_hp) अणु
		हाल CXD2880_DVBT_CODERATE_1_2:
			c->code_rate_HP = FEC_1_2;
			अवरोध;
		हाल CXD2880_DVBT_CODERATE_2_3:
			c->code_rate_HP = FEC_2_3;
			अवरोध;
		हाल CXD2880_DVBT_CODERATE_3_4:
			c->code_rate_HP = FEC_3_4;
			अवरोध;
		हाल CXD2880_DVBT_CODERATE_5_6:
			c->code_rate_HP = FEC_5_6;
			अवरोध;
		हाल CXD2880_DVBT_CODERATE_7_8:
			c->code_rate_HP = FEC_7_8;
			अवरोध;
		शेष:
			c->code_rate_HP = FEC_NONE;
			pr_debug("TPSInfo rateHP is invalid %d\n",
				 tps.rate_hp);
			अवरोध;
		पूर्ण
		चयन (tps.rate_lp) अणु
		हाल CXD2880_DVBT_CODERATE_1_2:
			c->code_rate_LP = FEC_1_2;
			अवरोध;
		हाल CXD2880_DVBT_CODERATE_2_3:
			c->code_rate_LP = FEC_2_3;
			अवरोध;
		हाल CXD2880_DVBT_CODERATE_3_4:
			c->code_rate_LP = FEC_3_4;
			अवरोध;
		हाल CXD2880_DVBT_CODERATE_5_6:
			c->code_rate_LP = FEC_5_6;
			अवरोध;
		हाल CXD2880_DVBT_CODERATE_7_8:
			c->code_rate_LP = FEC_7_8;
			अवरोध;
		शेष:
			c->code_rate_LP = FEC_NONE;
			pr_debug("TPSInfo rateLP is invalid %d\n",
				 tps.rate_lp);
			अवरोध;
		पूर्ण
		चयन (tps.स्थिरellation) अणु
		हाल CXD2880_DVBT_CONSTELLATION_QPSK:
			c->modulation = QPSK;
			अवरोध;
		हाल CXD2880_DVBT_CONSTELLATION_16QAM:
			c->modulation = QAM_16;
			अवरोध;
		हाल CXD2880_DVBT_CONSTELLATION_64QAM:
			c->modulation = QAM_64;
			अवरोध;
		शेष:
			c->modulation = QPSK;
			pr_debug("TPSInfo constellation is invalid %d\n",
				 tps.स्थिरellation);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->hierarchy = HIERARCHY_NONE;
		c->code_rate_HP = FEC_NONE;
		c->code_rate_LP = FEC_NONE;
		c->modulation = QPSK;
		pr_debug("TPS info err %d\n", ret);
	पूर्ण

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt_mon_spectrum_sense(&priv->tnrdmd, &sense);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		चयन (sense) अणु
		हाल CXD2880_TNRDMD_SPECTRUM_NORMAL:
			c->inversion = INVERSION_OFF;
			अवरोध;
		हाल CXD2880_TNRDMD_SPECTRUM_INV:
			c->inversion = INVERSION_ON;
			अवरोध;
		शेष:
			c->inversion = INVERSION_OFF;
			pr_debug("spectrum sense is invalid %d\n", sense);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->inversion = INVERSION_OFF;
		pr_debug("spectrum_sense %d\n", ret);
	पूर्ण

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_mon_rf_lvl(&priv->tnrdmd, &strength);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_DECIBEL;
		c->strength.stat[0].svalue = strength;
	पूर्ण अन्यथा अणु
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		pr_debug("mon_rf_lvl %d\n", ret);
	पूर्ण

	ret = cxd2880_पढ़ो_snr(fe, &snr);
	अगर (!ret) अणु
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = snr;
	पूर्ण अन्यथा अणु
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		pr_debug("read_snr %d\n", ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_get_frontend_t2(काष्ठा dvb_frontend *fe,
				   काष्ठा dtv_frontend_properties *c)
अणु
	पूर्णांक ret;
	काष्ठा cxd2880_priv *priv = शून्य;
	काष्ठा cxd2880_dvbt2_l1pre l1pre;
	क्रमागत cxd2880_dvbt2_plp_code_rate coderate;
	क्रमागत cxd2880_dvbt2_plp_स्थिरell qam;
	क्रमागत cxd2880_tnrdmd_spectrum_sense sense;
	u16 snr = 0;
	पूर्णांक strength = 0;

	अगर (!fe || !c) अणु
		pr_err("invalid arg.\n");
		वापस -EINVAL;
	पूर्ण

	priv = fe->demodulator_priv;

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt2_mon_l1_pre(&priv->tnrdmd, &l1pre);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		चयन (l1pre.fft_mode) अणु
		हाल CXD2880_DVBT2_M2K:
			c->transmission_mode = TRANSMISSION_MODE_2K;
			अवरोध;
		हाल CXD2880_DVBT2_M8K:
			c->transmission_mode = TRANSMISSION_MODE_8K;
			अवरोध;
		हाल CXD2880_DVBT2_M4K:
			c->transmission_mode = TRANSMISSION_MODE_4K;
			अवरोध;
		हाल CXD2880_DVBT2_M1K:
			c->transmission_mode = TRANSMISSION_MODE_1K;
			अवरोध;
		हाल CXD2880_DVBT2_M16K:
			c->transmission_mode = TRANSMISSION_MODE_16K;
			अवरोध;
		हाल CXD2880_DVBT2_M32K:
			c->transmission_mode = TRANSMISSION_MODE_32K;
			अवरोध;
		शेष:
			c->transmission_mode = TRANSMISSION_MODE_2K;
			pr_debug("L1Pre fft_mode is invalid %d\n",
				 l1pre.fft_mode);
			अवरोध;
		पूर्ण
		चयन (l1pre.gi) अणु
		हाल CXD2880_DVBT2_G1_32:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
			अवरोध;
		हाल CXD2880_DVBT2_G1_16:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
			अवरोध;
		हाल CXD2880_DVBT2_G1_8:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
			अवरोध;
		हाल CXD2880_DVBT2_G1_4:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
			अवरोध;
		हाल CXD2880_DVBT2_G1_128:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_128;
			अवरोध;
		हाल CXD2880_DVBT2_G19_128:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_19_128;
			अवरोध;
		हाल CXD2880_DVBT2_G19_256:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_19_256;
			अवरोध;
		शेष:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
			pr_debug("L1Pre guard interval is invalid %d\n",
				 l1pre.gi);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->transmission_mode = TRANSMISSION_MODE_2K;
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		pr_debug("L1Pre err %d\n", ret);
	पूर्ण

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt2_mon_code_rate(&priv->tnrdmd,
						 CXD2880_DVBT2_PLP_DATA,
						 &coderate);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		चयन (coderate) अणु
		हाल CXD2880_DVBT2_R1_2:
			c->fec_inner = FEC_1_2;
			अवरोध;
		हाल CXD2880_DVBT2_R3_5:
			c->fec_inner = FEC_3_5;
			अवरोध;
		हाल CXD2880_DVBT2_R2_3:
			c->fec_inner = FEC_2_3;
			अवरोध;
		हाल CXD2880_DVBT2_R3_4:
			c->fec_inner = FEC_3_4;
			अवरोध;
		हाल CXD2880_DVBT2_R4_5:
			c->fec_inner = FEC_4_5;
			अवरोध;
		हाल CXD2880_DVBT2_R5_6:
			c->fec_inner = FEC_5_6;
			अवरोध;
		शेष:
			c->fec_inner = FEC_NONE;
			pr_debug("CodeRate is invalid %d\n", coderate);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->fec_inner = FEC_NONE;
		pr_debug("CodeRate %d\n", ret);
	पूर्ण

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt2_mon_qam(&priv->tnrdmd,
					   CXD2880_DVBT2_PLP_DATA,
					   &qam);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		चयन (qam) अणु
		हाल CXD2880_DVBT2_QPSK:
			c->modulation = QPSK;
			अवरोध;
		हाल CXD2880_DVBT2_QAM16:
			c->modulation = QAM_16;
			अवरोध;
		हाल CXD2880_DVBT2_QAM64:
			c->modulation = QAM_64;
			अवरोध;
		हाल CXD2880_DVBT2_QAM256:
			c->modulation = QAM_256;
			अवरोध;
		शेष:
			c->modulation = QPSK;
			pr_debug("QAM is invalid %d\n", qam);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->modulation = QPSK;
		pr_debug("QAM %d\n", ret);
	पूर्ण

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_dvbt2_mon_spectrum_sense(&priv->tnrdmd, &sense);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		चयन (sense) अणु
		हाल CXD2880_TNRDMD_SPECTRUM_NORMAL:
			c->inversion = INVERSION_OFF;
			अवरोध;
		हाल CXD2880_TNRDMD_SPECTRUM_INV:
			c->inversion = INVERSION_ON;
			अवरोध;
		शेष:
			c->inversion = INVERSION_OFF;
			pr_debug("spectrum sense is invalid %d\n", sense);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->inversion = INVERSION_OFF;
		pr_debug("SpectrumSense %d\n", ret);
	पूर्ण

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_mon_rf_lvl(&priv->tnrdmd, &strength);
	mutex_unlock(priv->spi_mutex);
	अगर (!ret) अणु
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_DECIBEL;
		c->strength.stat[0].svalue = strength;
	पूर्ण अन्यथा अणु
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		pr_debug("mon_rf_lvl %d\n", ret);
	पूर्ण

	ret = cxd2880_पढ़ो_snr(fe, &snr);
	अगर (!ret) अणु
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = snr;
	पूर्ण अन्यथा अणु
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		pr_debug("read_snr %d\n", ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2880_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *props)
अणु
	पूर्णांक ret;

	अगर (!fe || !props) अणु
		pr_err("invalid arg.");
		वापस -EINVAL;
	पूर्ण

	pr_debug("system=%d\n", fe->dtv_property_cache.delivery_प्रणाली);
	चयन (fe->dtv_property_cache.delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = cxd2880_get_frontend_t(fe, props);
		अवरोध;
	हाल SYS_DVBT2:
		ret = cxd2880_get_frontend_t2(fe, props);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत dvbfe_algo cxd2880_get_frontend_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल काष्ठा dvb_frontend_ops cxd2880_dvbt_t2_ops = अणु
	.info = अणु
		.name = "Sony CXD2880",
		.frequency_min_hz = 174 * MHz,
		.frequency_max_hz = 862 * MHz,
		.frequency_stepsize_hz = 1 * kHz,
		.caps = FE_CAN_INVERSION_AUTO |
				FE_CAN_FEC_1_2 |
				FE_CAN_FEC_2_3 |
				FE_CAN_FEC_3_4 |
				FE_CAN_FEC_4_5 |
				FE_CAN_FEC_5_6	|
				FE_CAN_FEC_7_8	|
				FE_CAN_FEC_AUTO |
				FE_CAN_QPSK |
				FE_CAN_QAM_16 |
				FE_CAN_QAM_32 |
				FE_CAN_QAM_64 |
				FE_CAN_QAM_128 |
				FE_CAN_QAM_256 |
				FE_CAN_QAM_AUTO |
				FE_CAN_TRANSMISSION_MODE_AUTO |
				FE_CAN_GUARD_INTERVAL_AUTO |
				FE_CAN_2G_MODULATION |
				FE_CAN_RECOVER |
				FE_CAN_MUTE_TS,
	पूर्ण,
	.delsys = अणु SYS_DVBT, SYS_DVBT2 पूर्ण,

	.release = cxd2880_release,
	.init = cxd2880_init,
	.sleep = cxd2880_sleep,
	.tune = cxd2880_tune,
	.set_frontend = cxd2880_set_frontend,
	.get_frontend = cxd2880_get_frontend,
	.पढ़ो_status = cxd2880_पढ़ो_status,
	.पढ़ो_ber = cxd2880_पढ़ो_ber,
	.पढ़ो_संकेत_strength = cxd2880_पढ़ो_संकेत_strength,
	.पढ़ो_snr = cxd2880_पढ़ो_snr,
	.पढ़ो_ucblocks = cxd2880_पढ़ो_ucblocks,
	.get_frontend_algo = cxd2880_get_frontend_algo,
पूर्ण;

काष्ठा dvb_frontend *cxd2880_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा cxd2880_config *cfg)
अणु
	पूर्णांक ret;
	क्रमागत cxd2880_tnrdmd_chip_id chipid =
					CXD2880_TNRDMD_CHIP_ID_UNKNOWN;
	अटल काष्ठा cxd2880_priv *priv;
	u8 data = 0;

	अगर (!fe) अणु
		pr_err("invalid arg.\n");
		वापस शून्य;
	पूर्ण

	priv = kzalloc(माप(काष्ठा cxd2880_priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;

	priv->spi = cfg->spi;
	priv->spi_mutex = cfg->spi_mutex;
	priv->spi_device.spi = cfg->spi;

	स_नकल(&fe->ops, &cxd2880_dvbt_t2_ops,
	       माप(काष्ठा dvb_frontend_ops));

	ret = cxd2880_spi_device_initialize(&priv->spi_device,
					    CXD2880_SPI_MODE_0,
					    55000000);
	अगर (ret) अणु
		pr_err("spi_device_initialize failed. %d\n", ret);
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	ret = cxd2880_spi_device_create_spi(&priv->cxd2880_spi,
					    &priv->spi_device);
	अगर (ret) अणु
		pr_err("spi_device_create_spi failed. %d\n", ret);
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	ret = cxd2880_io_spi_create(&priv->regio, &priv->cxd2880_spi, 0);
	अगर (ret) अणु
		pr_err("io_spi_create failed. %d\n", ret);
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण
	ret = priv->regio.ग_लिखो_reg(&priv->regio,
				    CXD2880_IO_TGT_SYS, 0x00, 0x00);
	अगर (ret) अणु
		pr_err("set bank to 0x00 failed.\n");
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण
	ret = priv->regio.पढ़ो_regs(&priv->regio,
				    CXD2880_IO_TGT_SYS, 0xfd, &data, 1);
	अगर (ret) अणु
		pr_err("read chip id failed.\n");
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	chipid = (क्रमागत cxd2880_tnrdmd_chip_id)data;
	अगर (chipid != CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X &&
	    chipid != CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_11) अणु
		pr_err("chip id invalid.\n");
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	fe->demodulator_priv = priv;
	pr_info("CXD2880 driver version: Ver %s\n",
		CXD2880_TNRDMD_DRIVER_VERSION);

	वापस fe;
पूर्ण
EXPORT_SYMBOL(cxd2880_attach);

MODULE_DESCRIPTION("Sony CXD2880 DVB-T2/T tuner + demod driver");
MODULE_AUTHOR("Sony Semiconductor Solutions Corporation");
MODULE_LICENSE("GPL v2");
