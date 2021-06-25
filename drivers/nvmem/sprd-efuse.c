<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Spपढ़ोtrum Communications Inc.

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा SPRD_EFUSE_ENABLE		0x20
#घोषणा SPRD_EFUSE_ERR_FLAG		0x24
#घोषणा SPRD_EFUSE_ERR_CLR		0x28
#घोषणा SPRD_EFUSE_MAGIC_NUM		0x2c
#घोषणा SPRD_EFUSE_FW_CFG		0x50
#घोषणा SPRD_EFUSE_PW_SWT		0x54
#घोषणा SPRD_EFUSE_MEM(val)		(0x1000 + ((val) << 2))

#घोषणा SPRD_EFUSE_VDD_EN		BIT(0)
#घोषणा SPRD_EFUSE_AUTO_CHECK_EN	BIT(1)
#घोषणा SPRD_EFUSE_DOUBLE_EN		BIT(2)
#घोषणा SPRD_EFUSE_MARGIN_RD_EN		BIT(3)
#घोषणा SPRD_EFUSE_LOCK_WR_EN		BIT(4)

#घोषणा SPRD_EFUSE_ERR_CLR_MASK		GENMASK(13, 0)

#घोषणा SPRD_EFUSE_ENK1_ON		BIT(0)
#घोषणा SPRD_EFUSE_ENK2_ON		BIT(1)
#घोषणा SPRD_EFUSE_PROG_EN		BIT(2)

#घोषणा SPRD_EFUSE_MAGIC_NUMBER		0x8810

/* Block width (bytes) definitions */
#घोषणा SPRD_EFUSE_BLOCK_WIDTH		4

/*
 * The Spपढ़ोtrum AP efuse contains 2 parts: normal efuse and secure efuse,
 * and we can only access the normal efuse in kernel. So define the normal
 * block offset index and normal block numbers.
 */
#घोषणा SPRD_EFUSE_NORMAL_BLOCK_NUMS	24
#घोषणा SPRD_EFUSE_NORMAL_BLOCK_OFFSET	72

/* Timeout (ms) क्रम the trylock of hardware spinlocks */
#घोषणा SPRD_EFUSE_HWLOCK_TIMEOUT	5000

/*
 * Since dअगरferent Spपढ़ोtrum SoC chip can have dअगरferent normal block numbers
 * and offset. And some SoC can support block द्विगुन feature, which means
 * when पढ़ोing or writing data to efuse memory, the controller can save द्विगुन
 * data in हाल one data become incorrect after a दीर्घ period.
 *
 * Thus we should save them in the device data काष्ठाure.
 */
काष्ठा sprd_efuse_variant_data अणु
	u32 blk_nums;
	u32 blk_offset;
	bool blk_द्विगुन;
पूर्ण;

काष्ठा sprd_efuse अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा hwspinlock *hwlock;
	काष्ठा mutex mutex;
	व्योम __iomem *base;
	स्थिर काष्ठा sprd_efuse_variant_data *data;
पूर्ण;

अटल स्थिर काष्ठा sprd_efuse_variant_data ums312_data = अणु
	.blk_nums = SPRD_EFUSE_NORMAL_BLOCK_NUMS,
	.blk_offset = SPRD_EFUSE_NORMAL_BLOCK_OFFSET,
	.blk_द्विगुन = false,
पूर्ण;

/*
 * On Spपढ़ोtrum platक्रमm, we have multi-subप्रणालीs will access the unique
 * efuse controller, so we need one hardware spinlock to synchronize between
 * the multiple subप्रणालीs.
 */
अटल पूर्णांक sprd_efuse_lock(काष्ठा sprd_efuse *efuse)
अणु
	पूर्णांक ret;

	mutex_lock(&efuse->mutex);

	ret = hwspin_lock_समयout_raw(efuse->hwlock,
				      SPRD_EFUSE_HWLOCK_TIMEOUT);
	अगर (ret) अणु
		dev_err(efuse->dev, "timeout get the hwspinlock\n");
		mutex_unlock(&efuse->mutex);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_efuse_unlock(काष्ठा sprd_efuse *efuse)
अणु
	hwspin_unlock_raw(efuse->hwlock);
	mutex_unlock(&efuse->mutex);
पूर्ण

अटल व्योम sprd_efuse_set_prog_घातer(काष्ठा sprd_efuse *efuse, bool en)
अणु
	u32 val = पढ़ोl(efuse->base + SPRD_EFUSE_PW_SWT);

	अगर (en)
		val &= ~SPRD_EFUSE_ENK2_ON;
	अन्यथा
		val &= ~SPRD_EFUSE_ENK1_ON;

	ग_लिखोl(val, efuse->base + SPRD_EFUSE_PW_SWT);

	/* Open or बंद efuse घातer need रुको 1000us to make घातer stable. */
	usleep_range(1000, 1200);

	अगर (en)
		val |= SPRD_EFUSE_ENK1_ON;
	अन्यथा
		val |= SPRD_EFUSE_ENK2_ON;

	ग_लिखोl(val, efuse->base + SPRD_EFUSE_PW_SWT);

	/* Open or बंद efuse घातer need रुको 1000us to make घातer stable. */
	usleep_range(1000, 1200);
पूर्ण

अटल व्योम sprd_efuse_set_पढ़ो_घातer(काष्ठा sprd_efuse *efuse, bool en)
अणु
	u32 val = पढ़ोl(efuse->base + SPRD_EFUSE_ENABLE);

	अगर (en)
		val |= SPRD_EFUSE_VDD_EN;
	अन्यथा
		val &= ~SPRD_EFUSE_VDD_EN;

	ग_लिखोl(val, efuse->base + SPRD_EFUSE_ENABLE);

	/* Open or बंद efuse घातer need रुको 1000us to make घातer stable. */
	usleep_range(1000, 1200);
पूर्ण

अटल व्योम sprd_efuse_set_prog_lock(काष्ठा sprd_efuse *efuse, bool en)
अणु
	u32 val = पढ़ोl(efuse->base + SPRD_EFUSE_ENABLE);

	अगर (en)
		val |= SPRD_EFUSE_LOCK_WR_EN;
	अन्यथा
		val &= ~SPRD_EFUSE_LOCK_WR_EN;

	ग_लिखोl(val, efuse->base + SPRD_EFUSE_ENABLE);
पूर्ण

अटल व्योम sprd_efuse_set_स्वतः_check(काष्ठा sprd_efuse *efuse, bool en)
अणु
	u32 val = पढ़ोl(efuse->base + SPRD_EFUSE_ENABLE);

	अगर (en)
		val |= SPRD_EFUSE_AUTO_CHECK_EN;
	अन्यथा
		val &= ~SPRD_EFUSE_AUTO_CHECK_EN;

	ग_लिखोl(val, efuse->base + SPRD_EFUSE_ENABLE);
पूर्ण

अटल व्योम sprd_efuse_set_data_द्विगुन(काष्ठा sprd_efuse *efuse, bool en)
अणु
	u32 val = पढ़ोl(efuse->base + SPRD_EFUSE_ENABLE);

	अगर (en)
		val |= SPRD_EFUSE_DOUBLE_EN;
	अन्यथा
		val &= ~SPRD_EFUSE_DOUBLE_EN;

	ग_लिखोl(val, efuse->base + SPRD_EFUSE_ENABLE);
पूर्ण

अटल व्योम sprd_efuse_set_prog_en(काष्ठा sprd_efuse *efuse, bool en)
अणु
	u32 val = पढ़ोl(efuse->base + SPRD_EFUSE_PW_SWT);

	अगर (en)
		val |= SPRD_EFUSE_PROG_EN;
	अन्यथा
		val &= ~SPRD_EFUSE_PROG_EN;

	ग_लिखोl(val, efuse->base + SPRD_EFUSE_PW_SWT);
पूर्ण

अटल पूर्णांक sprd_efuse_raw_prog(काष्ठा sprd_efuse *efuse, u32 blk, bool करोub,
			       bool lock, u32 *data)
अणु
	u32 status;
	पूर्णांक ret = 0;

	/*
	 * We need set the correct magic number beक्रमe writing the efuse to
	 * allow programming, and block other programming until we clear the
	 * magic number.
	 */
	ग_लिखोl(SPRD_EFUSE_MAGIC_NUMBER,
	       efuse->base + SPRD_EFUSE_MAGIC_NUM);

	/*
	 * Power on the efuse, enable programme and enable द्विगुन data
	 * अगर asked.
	 */
	sprd_efuse_set_prog_घातer(efuse, true);
	sprd_efuse_set_prog_en(efuse, true);
	sprd_efuse_set_data_द्विगुन(efuse, करोub);

	/*
	 * Enable the स्वतः-check function to validate अगर the programming is
	 * successful.
	 */
	अगर (lock)
		sprd_efuse_set_स्वतः_check(efuse, true);

	ग_लिखोl(*data, efuse->base + SPRD_EFUSE_MEM(blk));

	/* Disable स्वतः-check and data द्विगुन after programming */
	अगर (lock)
		sprd_efuse_set_स्वतः_check(efuse, false);
	sprd_efuse_set_data_द्विगुन(efuse, false);

	/*
	 * Check the efuse error status, अगर the programming is successful,
	 * we should lock this efuse block to aव्योम programming again.
	 */
	status = पढ़ोl(efuse->base + SPRD_EFUSE_ERR_FLAG);
	अगर (status) अणु
		dev_err(efuse->dev,
			"write error status %d of block %d\n", ret, blk);

		ग_लिखोl(SPRD_EFUSE_ERR_CLR_MASK,
		       efuse->base + SPRD_EFUSE_ERR_CLR);
		ret = -EBUSY;
	पूर्ण अन्यथा अगर (lock) अणु
		sprd_efuse_set_prog_lock(efuse, lock);
		ग_लिखोl(0, efuse->base + SPRD_EFUSE_MEM(blk));
		sprd_efuse_set_prog_lock(efuse, false);
	पूर्ण

	sprd_efuse_set_prog_घातer(efuse, false);
	ग_लिखोl(0, efuse->base + SPRD_EFUSE_MAGIC_NUM);

	वापस ret;
पूर्ण

अटल पूर्णांक sprd_efuse_raw_पढ़ो(काष्ठा sprd_efuse *efuse, पूर्णांक blk, u32 *val,
			       bool करोub)
अणु
	u32 status;

	/*
	 * Need घातer on the efuse beक्रमe पढ़ोing data from efuse, and will
	 * घातer off the efuse after पढ़ोing process.
	 */
	sprd_efuse_set_पढ़ो_घातer(efuse, true);

	/* Enable द्विगुन data अगर asked */
	sprd_efuse_set_data_द्विगुन(efuse, करोub);

	/* Start to पढ़ो data from efuse block */
	*val = पढ़ोl(efuse->base + SPRD_EFUSE_MEM(blk));

	/* Disable द्विगुन data */
	sprd_efuse_set_data_द्विगुन(efuse, false);

	/* Power off the efuse */
	sprd_efuse_set_पढ़ो_घातer(efuse, false);

	/*
	 * Check the efuse error status and clear them अगर there are some
	 * errors occurred.
	 */
	status = पढ़ोl(efuse->base + SPRD_EFUSE_ERR_FLAG);
	अगर (status) अणु
		dev_err(efuse->dev,
			"read error status %d of block %d\n", status, blk);

		ग_लिखोl(SPRD_EFUSE_ERR_CLR_MASK,
		       efuse->base + SPRD_EFUSE_ERR_CLR);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_efuse_पढ़ो(व्योम *context, u32 offset, व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा sprd_efuse *efuse = context;
	bool blk_द्विगुन = efuse->data->blk_द्विगुन;
	u32 index = offset / SPRD_EFUSE_BLOCK_WIDTH + efuse->data->blk_offset;
	u32 blk_offset = (offset % SPRD_EFUSE_BLOCK_WIDTH) * BITS_PER_BYTE;
	u32 data;
	पूर्णांक ret;

	ret = sprd_efuse_lock(efuse);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(efuse->clk);
	अगर (ret)
		जाओ unlock;

	ret = sprd_efuse_raw_पढ़ो(efuse, index, &data, blk_द्विगुन);
	अगर (!ret) अणु
		data >>= blk_offset;
		स_नकल(val, &data, bytes);
	पूर्ण

	clk_disable_unprepare(efuse->clk);

unlock:
	sprd_efuse_unlock(efuse);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_efuse_ग_लिखो(व्योम *context, u32 offset, व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा sprd_efuse *efuse = context;
	bool blk_द्विगुन = efuse->data->blk_द्विगुन;
	bool lock;
	पूर्णांक ret;

	ret = sprd_efuse_lock(efuse);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(efuse->clk);
	अगर (ret)
		जाओ unlock;

	/*
	 * If the writing bytes are equal with the block width, which means the
	 * whole block will be programmed. For this हाल, we should not allow
	 * this block to be programmed again by locking this block.
	 *
	 * If the block was programmed partially, we should allow this block to
	 * be programmed again.
	 */
	अगर (bytes < SPRD_EFUSE_BLOCK_WIDTH)
		lock = false;
	अन्यथा
		lock = true;

	ret = sprd_efuse_raw_prog(efuse, offset, blk_द्विगुन, lock, val);

	clk_disable_unprepare(efuse->clk);

unlock:
	sprd_efuse_unlock(efuse);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_efuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_config econfig = अणु पूर्ण;
	काष्ठा sprd_efuse *efuse;
	स्थिर काष्ठा sprd_efuse_variant_data *pdata;
	पूर्णांक ret;

	pdata = of_device_get_match_data(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No matching driver data found\n");
		वापस -EINVAL;
	पूर्ण

	efuse = devm_kzalloc(&pdev->dev, माप(*efuse), GFP_KERNEL);
	अगर (!efuse)
		वापस -ENOMEM;

	efuse->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(efuse->base))
		वापस PTR_ERR(efuse->base);

	ret = of_hwspin_lock_get_id(np, 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get hwlock id\n");
		वापस ret;
	पूर्ण

	efuse->hwlock = devm_hwspin_lock_request_specअगरic(&pdev->dev, ret);
	अगर (!efuse->hwlock) अणु
		dev_err(&pdev->dev, "failed to request hwlock\n");
		वापस -ENXIO;
	पूर्ण

	efuse->clk = devm_clk_get(&pdev->dev, "enable");
	अगर (IS_ERR(efuse->clk)) अणु
		dev_err(&pdev->dev, "failed to get enable clock\n");
		वापस PTR_ERR(efuse->clk);
	पूर्ण

	mutex_init(&efuse->mutex);
	efuse->dev = &pdev->dev;
	efuse->data = pdata;

	econfig.stride = 1;
	econfig.word_size = 1;
	econfig.पढ़ो_only = false;
	econfig.name = "sprd-efuse";
	econfig.size = efuse->data->blk_nums * SPRD_EFUSE_BLOCK_WIDTH;
	econfig.reg_पढ़ो = sprd_efuse_पढ़ो;
	econfig.reg_ग_लिखो = sprd_efuse_ग_लिखो;
	econfig.priv = efuse;
	econfig.dev = &pdev->dev;
	nvmem = devm_nvmem_रेजिस्टर(&pdev->dev, &econfig);
	अगर (IS_ERR(nvmem)) अणु
		dev_err(&pdev->dev, "failed to register nvmem\n");
		वापस PTR_ERR(nvmem);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_efuse_of_match[] = अणु
	अणु .compatible = "sprd,ums312-efuse", .data = &ums312_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sprd_efuse_driver = अणु
	.probe = sprd_efuse_probe,
	.driver = अणु
		.name = "sprd-efuse",
		.of_match_table = sprd_efuse_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sprd_efuse_driver);

MODULE_AUTHOR("Freeman Liu <freeman.liu@spreadtrum.com>");
MODULE_DESCRIPTION("Spreadtrum AP efuse driver");
MODULE_LICENSE("GPL v2");
