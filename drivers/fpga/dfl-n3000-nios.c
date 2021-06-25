<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DFL device driver क्रम Nios निजी feature on Intel PAC (Programmable
 * Acceleration Card) N3000
 *
 * Copyright (C) 2019-2020 Intel Corporation, Inc.
 *
 * Authors:
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Xu Yilun <yilun.xu@पूर्णांकel.com>
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/dfl.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/spi/altera.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>

/*
 * N3000 Nios निजी feature रेजिस्टरs, named as NIOS_SPI_XX on spec.
 * NS is the abbreviation of NIOS_SPI.
 */
#घोषणा N3000_NS_PARAM				0x8
#घोषणा N3000_NS_PARAM_SHIFT_MODE_MSK		BIT_ULL(1)
#घोषणा N3000_NS_PARAM_SHIFT_MODE_MSB		0
#घोषणा N3000_NS_PARAM_SHIFT_MODE_LSB		1
#घोषणा N3000_NS_PARAM_DATA_WIDTH		GENMASK_ULL(7, 2)
#घोषणा N3000_NS_PARAM_NUM_CS			GENMASK_ULL(13, 8)
#घोषणा N3000_NS_PARAM_CLK_POL			BIT_ULL(14)
#घोषणा N3000_NS_PARAM_CLK_PHASE		BIT_ULL(15)
#घोषणा N3000_NS_PARAM_PERIPHERAL_ID		GENMASK_ULL(47, 32)

#घोषणा N3000_NS_CTRL				0x10
#घोषणा N3000_NS_CTRL_WR_DATA			GENMASK_ULL(31, 0)
#घोषणा N3000_NS_CTRL_ADDR			GENMASK_ULL(44, 32)
#घोषणा N3000_NS_CTRL_CMD_MSK			GENMASK_ULL(63, 62)
#घोषणा N3000_NS_CTRL_CMD_NOP			0
#घोषणा N3000_NS_CTRL_CMD_RD			1
#घोषणा N3000_NS_CTRL_CMD_WR			2

#घोषणा N3000_NS_STAT				0x18
#घोषणा N3000_NS_STAT_RD_DATA			GENMASK_ULL(31, 0)
#घोषणा N3000_NS_STAT_RW_VAL			BIT_ULL(32)

/* Nios handshake रेजिस्टरs, indirect access */
#घोषणा N3000_NIOS_INIT				0x1000
#घोषणा N3000_NIOS_INIT_DONE			BIT(0)
#घोषणा N3000_NIOS_INIT_START			BIT(1)
/* Mode क्रम reसमयr A, link 0, the same below */
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_A0_MSK	GENMASK(9, 8)
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_A1_MSK	GENMASK(11, 10)
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_A2_MSK	GENMASK(13, 12)
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_A3_MSK	GENMASK(15, 14)
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_B0_MSK	GENMASK(17, 16)
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_B1_MSK	GENMASK(19, 18)
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_B2_MSK	GENMASK(21, 20)
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_B3_MSK	GENMASK(23, 22)
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_NO		0x0
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_KR		0x1
#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_RS		0x2

#घोषणा N3000_NIOS_FW_VERSION			0x1004
#घोषणा N3000_NIOS_FW_VERSION_PATCH		GENMASK(23, 20)
#घोषणा N3000_NIOS_FW_VERSION_MINOR		GENMASK(27, 24)
#घोषणा N3000_NIOS_FW_VERSION_MAJOR		GENMASK(31, 28)

/* The reसमयrs we use on Intel PAC N3000 is Parkvale, abbreviated to PKVL */
#घोषणा N3000_NIOS_PKVL_A_MODE_STS		0x1020
#घोषणा N3000_NIOS_PKVL_B_MODE_STS		0x1024
#घोषणा N3000_NIOS_PKVL_MODE_STS_GROUP_MSK	GENMASK(15, 8)
#घोषणा N3000_NIOS_PKVL_MODE_STS_GROUP_OK	0x0
#घोषणा N3000_NIOS_PKVL_MODE_STS_ID_MSK		GENMASK(7, 0)
/* When GROUP MASK field == GROUP_OK  */
#घोषणा N3000_NIOS_PKVL_MODE_ID_RESET		0x0
#घोषणा N3000_NIOS_PKVL_MODE_ID_4X10G		0x1
#घोषणा N3000_NIOS_PKVL_MODE_ID_4X25G		0x2
#घोषणा N3000_NIOS_PKVL_MODE_ID_2X25G		0x3
#घोषणा N3000_NIOS_PKVL_MODE_ID_2X25G_2X10G	0x4
#घोषणा N3000_NIOS_PKVL_MODE_ID_1X25G		0x5

#घोषणा N3000_NIOS_REGBUS_RETRY_COUNT		10000	/* loop count */

#घोषणा N3000_NIOS_INIT_TIMEOUT			10000000	/* usec */
#घोषणा N3000_NIOS_INIT_TIME_INTV		100000		/* usec */

#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_MSK_ALL	\
	(N3000_NIOS_INIT_REQ_FEC_MODE_A0_MSK |	\
	 N3000_NIOS_INIT_REQ_FEC_MODE_A1_MSK |	\
	 N3000_NIOS_INIT_REQ_FEC_MODE_A2_MSK |	\
	 N3000_NIOS_INIT_REQ_FEC_MODE_A3_MSK |	\
	 N3000_NIOS_INIT_REQ_FEC_MODE_B0_MSK |	\
	 N3000_NIOS_INIT_REQ_FEC_MODE_B1_MSK |	\
	 N3000_NIOS_INIT_REQ_FEC_MODE_B2_MSK |	\
	 N3000_NIOS_INIT_REQ_FEC_MODE_B3_MSK)

#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_NO_ALL			\
	(FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A0_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_NO) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A1_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_NO) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A2_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_NO) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A3_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_NO) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B0_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_NO) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B1_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_NO) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B2_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_NO) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B3_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_NO))

#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_KR_ALL			\
	(FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A0_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_KR) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A1_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_KR) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A2_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_KR) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A3_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_KR) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B0_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_KR) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B1_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_KR) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B2_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_KR) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B3_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_KR))

#घोषणा N3000_NIOS_INIT_REQ_FEC_MODE_RS_ALL			\
	(FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A0_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_RS) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A1_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_RS) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A2_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_RS) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_A3_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_RS) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B0_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_RS) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B1_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_RS) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B2_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_RS) |		\
	 FIELD_PREP(N3000_NIOS_INIT_REQ_FEC_MODE_B3_MSK,	\
		    N3000_NIOS_INIT_REQ_FEC_MODE_RS))

काष्ठा n3000_nios अणु
	व्योम __iomem *base;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *altera_spi;
पूर्ण;

अटल sमाप_प्रकार nios_fw_version_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा n3000_nios *nn = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(nn->regmap, N3000_NIOS_FW_VERSION, &val);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "%x.%x.%x\n",
			  (u8)FIELD_GET(N3000_NIOS_FW_VERSION_MAJOR, val),
			  (u8)FIELD_GET(N3000_NIOS_FW_VERSION_MINOR, val),
			  (u8)FIELD_GET(N3000_NIOS_FW_VERSION_PATCH, val));
पूर्ण
अटल DEVICE_ATTR_RO(nios_fw_version);

#घोषणा IS_MODE_STATUS_OK(mode_stat)					\
	(FIELD_GET(N3000_NIOS_PKVL_MODE_STS_GROUP_MSK, (mode_stat)) ==	\
	 N3000_NIOS_PKVL_MODE_STS_GROUP_OK)

#घोषणा IS_RETIMER_FEC_SUPPORTED(reसमयr_mode)			\
	((reसमयr_mode) != N3000_NIOS_PKVL_MODE_ID_RESET &&	\
	 (reसमयr_mode) != N3000_NIOS_PKVL_MODE_ID_4X10G)

अटल पूर्णांक get_reसमयr_mode(काष्ठा n3000_nios *nn, अचिन्हित पूर्णांक mode_stat_reg,
			    अचिन्हित पूर्णांक *reसमयr_mode)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(nn->regmap, mode_stat_reg, &val);
	अगर (ret)
		वापस ret;

	अगर (!IS_MODE_STATUS_OK(val))
		वापस -EFAULT;

	*reसमयr_mode = FIELD_GET(N3000_NIOS_PKVL_MODE_STS_ID_MSK, val);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार reसमयr_A_mode_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा n3000_nios *nn = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	ret = get_reसमयr_mode(nn, N3000_NIOS_PKVL_A_MODE_STS, &mode);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "0x%x\n", mode);
पूर्ण
अटल DEVICE_ATTR_RO(reसमयr_A_mode);

अटल sमाप_प्रकार reसमयr_B_mode_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा n3000_nios *nn = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	ret = get_reसमयr_mode(nn, N3000_NIOS_PKVL_B_MODE_STS, &mode);
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "0x%x\n", mode);
पूर्ण
अटल DEVICE_ATTR_RO(reसमयr_B_mode);

अटल sमाप_प्रकार fec_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक val, reसमयr_a_mode, reसमयr_b_mode, fec_modes;
	काष्ठा n3000_nios *nn = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* FEC mode setting is not supported in early FW versions */
	ret = regmap_पढ़ो(nn->regmap, N3000_NIOS_FW_VERSION, &val);
	अगर (ret)
		वापस ret;

	अगर (FIELD_GET(N3000_NIOS_FW_VERSION_MAJOR, val) < 3)
		वापस sysfs_emit(buf, "not supported\n");

	/* If no 25G links, FEC mode setting is not supported either */
	ret = get_reसमयr_mode(nn, N3000_NIOS_PKVL_A_MODE_STS, &reसमयr_a_mode);
	अगर (ret)
		वापस ret;

	ret = get_reसमयr_mode(nn, N3000_NIOS_PKVL_B_MODE_STS, &reसमयr_b_mode);
	अगर (ret)
		वापस ret;

	अगर (!IS_RETIMER_FEC_SUPPORTED(reसमयr_a_mode) &&
	    !IS_RETIMER_FEC_SUPPORTED(reसमयr_b_mode))
		वापस sysfs_emit(buf, "not supported\n");

	/* get the valid FEC mode क्रम 25G links */
	ret = regmap_पढ़ो(nn->regmap, N3000_NIOS_INIT, &val);
	अगर (ret)
		वापस ret;

	/*
	 * FEC mode should always be the same क्रम all links, as we set them
	 * in this way.
	 */
	fec_modes = (val & N3000_NIOS_INIT_REQ_FEC_MODE_MSK_ALL);
	अगर (fec_modes == N3000_NIOS_INIT_REQ_FEC_MODE_NO_ALL)
		वापस sysfs_emit(buf, "no\n");
	अन्यथा अगर (fec_modes == N3000_NIOS_INIT_REQ_FEC_MODE_KR_ALL)
		वापस sysfs_emit(buf, "kr\n");
	अन्यथा अगर (fec_modes == N3000_NIOS_INIT_REQ_FEC_MODE_RS_ALL)
		वापस sysfs_emit(buf, "rs\n");

	वापस -EFAULT;
पूर्ण
अटल DEVICE_ATTR_RO(fec_mode);

अटल काष्ठा attribute *n3000_nios_attrs[] = अणु
	&dev_attr_nios_fw_version.attr,
	&dev_attr_reसमयr_A_mode.attr,
	&dev_attr_reसमयr_B_mode.attr,
	&dev_attr_fec_mode.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(n3000_nios);

अटल पूर्णांक n3000_nios_init_करोne_check(काष्ठा n3000_nios *nn)
अणु
	अचिन्हित पूर्णांक val, state_a, state_b;
	काष्ठा device *dev = nn->dev;
	पूर्णांक ret, ret2;

	/*
	 * The SPI is shared by the Nios core inside the FPGA, Nios will use
	 * this SPI master to करो some one समय initialization after घातer up,
	 * and then release the control to OS. The driver needs to poll on
	 * INIT_DONE to see when driver could take the control.
	 *
	 * Please note that after Nios firmware version 3.0.0, INIT_START is
	 * पूर्णांकroduced, so driver needs to trigger START firstly and then check
	 * INIT_DONE.
	 */

	ret = regmap_पढ़ो(nn->regmap, N3000_NIOS_FW_VERSION, &val);
	अगर (ret)
		वापस ret;

	/*
	 * If Nios version रेजिस्टर is totally uninitialized(== 0x0), then the
	 * Nios firmware is missing. So host could take control of SPI master
	 * safely, but initialization work क्रम Nios is not करोne. To restore the
	 * card, we need to reprogram a new Nios firmware via the BMC chip on
	 * SPI bus. So the driver करोesn't error out, it जारीs to create the
	 * spi controller device and spi_board_info क्रम BMC.
	 */
	अगर (val == 0) अणु
		dev_err(dev, "Nios version reg = 0x%x, skip INIT_DONE check, but the retimer may be uninitialized\n",
			val);
		वापस 0;
	पूर्ण

	अगर (FIELD_GET(N3000_NIOS_FW_VERSION_MAJOR, val) >= 3) अणु
		/* पढ़ो NIOS_INIT to check अगर reसमयr initialization is करोne */
		ret = regmap_पढ़ो(nn->regmap, N3000_NIOS_INIT, &val);
		अगर (ret)
			वापस ret;

		/* check अगर reसमयrs are initialized alपढ़ोy */
		अगर (val & (N3000_NIOS_INIT_DONE | N3000_NIOS_INIT_START))
			जाओ nios_init_करोne;

		/* configure FEC mode per module param */
		val = N3000_NIOS_INIT_START;

		/*
		 * When the reसमयr is to be set to 10G mode, there is no FEC
		 * mode setting, so the REQ_FEC_MODE field will be ignored by
		 * Nios firmware in this हाल. But we should still fill the FEC
		 * mode field cause host could not get the reसमयr working mode
		 * until the Nios init is करोne.
		 *
		 * For now the driver करोesn't support the reसमयr FEC mode
		 * चयनing per user's request. It is always set to Reed
		 * Solomon FEC.
		 *
		 * The driver will set the same FEC mode क्रम all links.
		 */
		val |= N3000_NIOS_INIT_REQ_FEC_MODE_RS_ALL;

		ret = regmap_ग_लिखो(nn->regmap, N3000_NIOS_INIT, val);
		अगर (ret)
			वापस ret;
	पूर्ण

nios_init_करोne:
	/* polls on NIOS_INIT_DONE */
	ret = regmap_पढ़ो_poll_समयout(nn->regmap, N3000_NIOS_INIT, val,
				       val & N3000_NIOS_INIT_DONE,
				       N3000_NIOS_INIT_TIME_INTV,
				       N3000_NIOS_INIT_TIMEOUT);
	अगर (ret)
		dev_err(dev, "NIOS_INIT_DONE %s\n",
			(ret == -ETIMEDOUT) ? "timed out" : "check error");

	ret2 = regmap_पढ़ो(nn->regmap, N3000_NIOS_PKVL_A_MODE_STS, &state_a);
	अगर (ret2)
		वापस ret2;

	ret2 = regmap_पढ़ो(nn->regmap, N3000_NIOS_PKVL_B_MODE_STS, &state_b);
	अगर (ret2)
		वापस ret2;

	अगर (!ret) अणु
		/*
		 * After INIT_DONE is detected, it still needs to check अगर the
		 * Nios firmware reports any error during the reसमयr
		 * configuration.
		 */
		अगर (IS_MODE_STATUS_OK(state_a) && IS_MODE_STATUS_OK(state_b))
			वापस 0;

		/*
		 * If the reसमयr configuration is failed, the Nios firmware
		 * will still release the spi controller क्रम host to
		 * communicate with the BMC. It makes possible क्रम people to
		 * reprogram a new Nios firmware and restore the card. So the
		 * driver करोesn't error out, it जारीs to create the spi
		 * controller device and spi_board_info क्रम BMC.
		 */
		dev_err(dev, "NIOS_INIT_DONE OK, but err on retimer init\n");
	पूर्ण

	dev_err(nn->dev, "PKVL_A_MODE_STS 0x%x\n", state_a);
	dev_err(nn->dev, "PKVL_B_MODE_STS 0x%x\n", state_b);

	वापस ret;
पूर्ण

अटल काष्ठा spi_board_info m10_n3000_info = अणु
	.modalias = "m10-n3000",
	.max_speed_hz = 12500000,
	.bus_num = 0,
	.chip_select = 0,
पूर्ण;

अटल पूर्णांक create_altera_spi_controller(काष्ठा n3000_nios *nn)
अणु
	काष्ठा altera_spi_platक्रमm_data pdata = अणु 0 पूर्ण;
	काष्ठा platक्रमm_device_info pdevinfo = अणु 0 पूर्ण;
	व्योम __iomem *base = nn->base;
	u64 v;

	v = पढ़ोq(base + N3000_NS_PARAM);

	pdata.mode_bits = SPI_CS_HIGH;
	अगर (FIELD_GET(N3000_NS_PARAM_CLK_POL, v))
		pdata.mode_bits |= SPI_CPOL;
	अगर (FIELD_GET(N3000_NS_PARAM_CLK_PHASE, v))
		pdata.mode_bits |= SPI_CPHA;

	pdata.num_chipselect = FIELD_GET(N3000_NS_PARAM_NUM_CS, v);
	pdata.bits_per_word_mask =
		SPI_BPW_RANGE_MASK(1, FIELD_GET(N3000_NS_PARAM_DATA_WIDTH, v));

	pdata.num_devices = 1;
	pdata.devices = &m10_n3000_info;

	dev_dbg(nn->dev, "%s cs %u bpm 0x%x mode 0x%x\n", __func__,
		pdata.num_chipselect, pdata.bits_per_word_mask,
		pdata.mode_bits);

	pdevinfo.name = "subdev_spi_altera";
	pdevinfo.id = PLATFORM_DEVID_AUTO;
	pdevinfo.parent = nn->dev;
	pdevinfo.data = &pdata;
	pdevinfo.size_data = माप(pdata);

	nn->altera_spi = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	वापस PTR_ERR_OR_ZERO(nn->altera_spi);
पूर्ण

अटल व्योम destroy_altera_spi_controller(काष्ठा n3000_nios *nn)
अणु
	platक्रमm_device_unरेजिस्टर(nn->altera_spi);
पूर्ण

अटल पूर्णांक n3000_nios_poll_stat_समयout(व्योम __iomem *base, u64 *v)
अणु
	पूर्णांक loops;

	/*
	 * We करोn't use the समय based समयout here क्रम perक्रमmance.
	 *
	 * The regbus पढ़ो/ग_लिखो is on the critical path of Intel PAC N3000
	 * image programing. The समय based समयout checking will add too much
	 * overhead on it. Usually the state changes in 1 or 2 loops on the
	 * test server, and we set 10000 बार loop here क्रम safety.
	 */
	क्रम (loops = N3000_NIOS_REGBUS_RETRY_COUNT; loops > 0 ; loops--) अणु
		*v = पढ़ोq(base + N3000_NS_STAT);
		अगर (*v & N3000_NS_STAT_RW_VAL)
			अवरोध;
		cpu_relax();
	पूर्ण

	वापस (loops > 0) ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक n3000_nios_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा n3000_nios *nn = context;
	u64 v;
	पूर्णांक ret;

	v = FIELD_PREP(N3000_NS_CTRL_CMD_MSK, N3000_NS_CTRL_CMD_WR) |
	    FIELD_PREP(N3000_NS_CTRL_ADDR, reg) |
	    FIELD_PREP(N3000_NS_CTRL_WR_DATA, val);
	ग_लिखोq(v, nn->base + N3000_NS_CTRL);

	ret = n3000_nios_poll_stat_समयout(nn->base, &v);
	अगर (ret)
		dev_err(nn->dev, "fail to write reg 0x%x val 0x%x: %d\n",
			reg, val, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक n3000_nios_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा n3000_nios *nn = context;
	u64 v;
	पूर्णांक ret;

	v = FIELD_PREP(N3000_NS_CTRL_CMD_MSK, N3000_NS_CTRL_CMD_RD) |
	    FIELD_PREP(N3000_NS_CTRL_ADDR, reg);
	ग_लिखोq(v, nn->base + N3000_NS_CTRL);

	ret = n3000_nios_poll_stat_समयout(nn->base, &v);
	अगर (ret)
		dev_err(nn->dev, "fail to read reg 0x%x: %d\n", reg, ret);
	अन्यथा
		*val = FIELD_GET(N3000_NS_STAT_RD_DATA, v);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regmap_config n3000_nios_regbus_cfg = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,

	.reg_ग_लिखो = n3000_nios_reg_ग_लिखो,
	.reg_पढ़ो = n3000_nios_reg_पढ़ो,
पूर्ण;

अटल पूर्णांक n3000_nios_probe(काष्ठा dfl_device *ddev)
अणु
	काष्ठा device *dev = &ddev->dev;
	काष्ठा n3000_nios *nn;
	पूर्णांक ret;

	nn = devm_kzalloc(dev, माप(*nn), GFP_KERNEL);
	अगर (!nn)
		वापस -ENOMEM;

	dev_set_drvdata(&ddev->dev, nn);

	nn->dev = dev;

	nn->base = devm_ioremap_resource(&ddev->dev, &ddev->mmio_res);
	अगर (IS_ERR(nn->base))
		वापस PTR_ERR(nn->base);

	nn->regmap = devm_regmap_init(dev, शून्य, nn, &n3000_nios_regbus_cfg);
	अगर (IS_ERR(nn->regmap))
		वापस PTR_ERR(nn->regmap);

	ret = n3000_nios_init_करोne_check(nn);
	अगर (ret)
		वापस ret;

	ret = create_altera_spi_controller(nn);
	अगर (ret)
		dev_err(dev, "altera spi controller create failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम n3000_nios_हटाओ(काष्ठा dfl_device *ddev)
अणु
	काष्ठा n3000_nios *nn = dev_get_drvdata(&ddev->dev);

	destroy_altera_spi_controller(nn);
पूर्ण

#घोषणा FME_FEATURE_ID_N3000_NIOS	0xd

अटल स्थिर काष्ठा dfl_device_id n3000_nios_ids[] = अणु
	अणु FME_ID, FME_FEATURE_ID_N3000_NIOS पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dfl, n3000_nios_ids);

अटल काष्ठा dfl_driver n3000_nios_driver = अणु
	.drv	= अणु
		.name       = "dfl-n3000-nios",
		.dev_groups = n3000_nios_groups,
	पूर्ण,
	.id_table = n3000_nios_ids,
	.probe   = n3000_nios_probe,
	.हटाओ  = n3000_nios_हटाओ,
पूर्ण;

module_dfl_driver(n3000_nios_driver);

MODULE_DESCRIPTION("Driver for Nios private feature on Intel PAC N3000");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
