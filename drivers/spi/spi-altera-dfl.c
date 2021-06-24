<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// DFL bus driver क्रम Altera SPI Master
//
// Copyright (C) 2020 Intel Corporation, Inc.
//
// Authors:
//   Matthew Gerlach <matthew.gerlach@linux.पूर्णांकel.com>
//

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitfield.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/altera.h>
#समावेश <linux/dfl.h>

#घोषणा FME_FEATURE_ID_MAX10_SPI	0xe
#घोषणा FME_FEATURE_REV_MAX10_SPI_N5010	0x1

#घोषणा SPI_CORE_PARAMETER      0x8
#घोषणा SHIFT_MODE              BIT_ULL(1)
#घोषणा SHIFT_MODE_MSB          0
#घोषणा SHIFT_MODE_LSB          1
#घोषणा DATA_WIDTH              GENMASK_ULL(7, 2)
#घोषणा NUM_CHIPSELECT          GENMASK_ULL(13, 8)
#घोषणा CLK_POLARITY            BIT_ULL(14)
#घोषणा CLK_PHASE               BIT_ULL(15)
#घोषणा PERIPHERAL_ID           GENMASK_ULL(47, 32)
#घोषणा SPI_CLK                 GENMASK_ULL(31, 22)
#घोषणा SPI_INसूचीECT_ACC_OFST   0x10

#घोषणा INसूचीECT_ADDR           (SPI_INसूचीECT_ACC_OFST+0x0)
#घोषणा INसूचीECT_WR             BIT_ULL(8)
#घोषणा INसूचीECT_RD             BIT_ULL(9)
#घोषणा INसूचीECT_RD_DATA        (SPI_INसूचीECT_ACC_OFST+0x8)
#घोषणा INसूचीECT_DATA_MASK      GENMASK_ULL(31, 0)
#घोषणा INसूचीECT_DEBUG          BIT_ULL(32)
#घोषणा INसूचीECT_WR_DATA        (SPI_INसूचीECT_ACC_OFST+0x10)
#घोषणा INसूचीECT_TIMEOUT        10000

अटल पूर्णांक indirect_bus_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक *val)
अणु
	व्योम __iomem *base = context;
	पूर्णांक loops;
	u64 v;

	ग_लिखोq((reg >> 2) | INसूचीECT_RD, base + INसूचीECT_ADDR);

	loops = 0;
	जबतक ((पढ़ोq(base + INसूचीECT_ADDR) & INसूचीECT_RD) &&
	       (loops++ < INसूचीECT_TIMEOUT))
		cpu_relax();

	अगर (loops >= INसूचीECT_TIMEOUT) अणु
		pr_err("%s timed out %d\n", __func__, loops);
		वापस -ETIME;
	पूर्ण

	v = पढ़ोq(base + INसूचीECT_RD_DATA);

	*val = v & INसूचीECT_DATA_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक indirect_bus_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	व्योम __iomem *base = context;
	पूर्णांक loops;

	ग_लिखोq(val, base + INसूचीECT_WR_DATA);
	ग_लिखोq((reg >> 2) | INसूचीECT_WR, base + INसूचीECT_ADDR);

	loops = 0;
	जबतक ((पढ़ोq(base + INसूचीECT_ADDR) & INसूचीECT_WR) &&
	       (loops++ < INसूचीECT_TIMEOUT))
		cpu_relax();

	अगर (loops >= INसूचीECT_TIMEOUT) अणु
		pr_err("%s timed out %d\n", __func__, loops);
		वापस -ETIME;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config indirect_regbus_cfg = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,
	.max_रेजिस्टर = 24,

	.reg_ग_लिखो = indirect_bus_reg_ग_लिखो,
	.reg_पढ़ो = indirect_bus_reg_पढ़ो,
पूर्ण;

अटल काष्ठा spi_board_info m10_bmc_info = अणु
	.modalias = "m10-d5005",
	.max_speed_hz = 12500000,
	.bus_num = 0,
	.chip_select = 0,
पूर्ण;

अटल व्योम config_spi_master(व्योम __iomem *base, काष्ठा spi_master *master)
अणु
	u64 v;

	v = पढ़ोq(base + SPI_CORE_PARAMETER);

	master->mode_bits = SPI_CS_HIGH;
	अगर (FIELD_GET(CLK_POLARITY, v))
		master->mode_bits |= SPI_CPOL;
	अगर (FIELD_GET(CLK_PHASE, v))
		master->mode_bits |= SPI_CPHA;

	master->num_chipselect = FIELD_GET(NUM_CHIPSELECT, v);
	master->bits_per_word_mask =
		SPI_BPW_RANGE_MASK(1, FIELD_GET(DATA_WIDTH, v));
पूर्ण

अटल पूर्णांक dfl_spi_altera_probe(काष्ठा dfl_device *dfl_dev)
अणु
	काष्ठा device *dev = &dfl_dev->dev;
	काष्ठा spi_master *master;
	काष्ठा altera_spi *hw;
	व्योम __iomem *base;
	पूर्णांक err = -ENODEV;

	master = spi_alloc_master(dev, माप(काष्ठा altera_spi));
	अगर (!master)
		वापस -ENOMEM;

	master->bus_num = dfl_dev->id;

	hw = spi_master_get_devdata(master);

	hw->dev = dev;

	base = devm_ioremap_resource(dev, &dfl_dev->mmio_res);

	अगर (IS_ERR(base)) अणु
		dev_err(dev, "%s get mem resource fail!\n", __func__);
		वापस PTR_ERR(base);
	पूर्ण

	config_spi_master(base, master);
	dev_dbg(dev, "%s cs %u bpm 0x%x mode 0x%x\n", __func__,
		master->num_chipselect, master->bits_per_word_mask,
		master->mode_bits);

	hw->regmap = devm_regmap_init(dev, शून्य, base, &indirect_regbus_cfg);
	अगर (IS_ERR(hw->regmap))
		वापस PTR_ERR(hw->regmap);

	hw->irq = -EINVAL;

	altera_spi_init_master(master);

	err = devm_spi_रेजिस्टर_master(dev, master);
	अगर (err) अणु
		dev_err(dev, "%s failed to register spi master %d\n", __func__, err);
		जाओ निकास;
	पूर्ण

	अगर (!spi_new_device(master,  &m10_bmc_info)) अणु
		dev_err(dev, "%s failed to create SPI device: %s\n",
			__func__, m10_bmc_info.modalias);
	पूर्ण

	वापस 0;
निकास:
	spi_master_put(master);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा dfl_device_id dfl_spi_altera_ids[] = अणु
	अणु FME_ID, FME_FEATURE_ID_MAX10_SPI पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा dfl_driver dfl_spi_altera_driver = अणु
	.drv	= अणु
		.name       = "dfl-spi-altera",
	पूर्ण,
	.id_table = dfl_spi_altera_ids,
	.probe   = dfl_spi_altera_probe,
पूर्ण;

module_dfl_driver(dfl_spi_altera_driver);

MODULE_DEVICE_TABLE(dfl, dfl_spi_altera_ids);
MODULE_DESCRIPTION("DFL spi altera driver");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
