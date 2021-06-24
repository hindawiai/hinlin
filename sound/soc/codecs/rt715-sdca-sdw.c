<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt715-sdca-sdw.c -- rt715 ALSA SoC audio driver
//
// Copyright(c) 2020 Realtek Semiconductor Corp.
//
//

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश "rt715-sdca.h"
#समावेश "rt715-sdca-sdw.h"

अटल bool rt715_sdca_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x201a ... 0x2027:
	हाल 0x2029 ... 0x202a:
	हाल 0x202d ... 0x2034:
	हाल 0x2200 ... 0x2204:
	हाल 0x2206 ... 0x2212:
	हाल 0x2230 ... 0x2239:
	हाल 0x2f5b:
	हाल SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_SMPU_TRIG_ST_EN,
		RT715_SDCA_SMPU_TRIG_ST_CTRL, CH_00):
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt715_sdca_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x201b:
	हाल 0x201c:
	हाल 0x201d:
	हाल 0x201f:
	हाल 0x2021:
	हाल 0x2023:
	हाल 0x2230:
	हाल 0x202d ... 0x202f: /* BRA */
	हाल 0x2200 ... 0x2212: /* i2c debug */
	हाल 0x2f07:
	हाल 0x2f1b ... 0x2f1e:
	हाल 0x2f30 ... 0x2f34:
	हाल 0x2f50 ... 0x2f51:
	हाल 0x2f53 ... 0x2f59:
	हाल 0x2f5c ... 0x2f5f:
	हाल SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_SMPU_TRIG_ST_EN,
		RT715_SDCA_SMPU_TRIG_ST_CTRL, CH_00): /* VAD Searching status */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt715_sdca_mbq_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x2000000:
	हाल 0x200002b:
	हाल 0x2000036:
	हाल 0x2000037:
	हाल 0x2000039:
	हाल 0x6100000:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt715_sdca_mbq_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x2000000:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rt715_sdca_regmap = अणु
	.reg_bits = 32,
	.val_bits = 8,
	.पढ़ोable_reg = rt715_sdca_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = rt715_sdca_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = 0x43ffffff,
	.reg_शेषs = rt715_reg_शेषs_sdca,
	.num_reg_शेषs = ARRAY_SIZE(rt715_reg_शेषs_sdca),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt715_sdca_mbq_regmap = अणु
	.name = "sdw-mbq",
	.reg_bits = 32,
	.val_bits = 16,
	.पढ़ोable_reg = rt715_sdca_mbq_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = rt715_sdca_mbq_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = 0x43ffffff,
	.reg_शेषs = rt715_mbq_reg_शेषs_sdca,
	.num_reg_शेषs = ARRAY_SIZE(rt715_mbq_reg_शेषs_sdca),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक rt715_sdca_update_status(काष्ठा sdw_slave *slave,
				क्रमागत sdw_slave_status status)
अणु
	काष्ठा rt715_sdca_priv *rt715 = dev_get_drvdata(&slave->dev);

	/* Update the status */
	rt715->status = status;

	/*
	 * Perक्रमm initialization only अगर slave status is present and
	 * hw_init flag is false
	 */
	अगर (rt715->hw_init || rt715->status != SDW_SLAVE_ATTACHED)
		वापस 0;

	/* perक्रमm I/O transfers required क्रम Slave initialization */
	वापस rt715_sdca_io_init(&slave->dev, slave);
पूर्ण

अटल पूर्णांक rt715_sdca_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक nval, i;
	u32 bit;
	अचिन्हित दीर्घ addr;
	काष्ठा sdw_dpn_prop *dpn;

	prop->paging_support = true;

	/* first we need to allocate memory क्रम set bits in port lists */
	prop->source_ports = 0x50;/* BITMAP: 01010000 */
	prop->sink_ports = 0x0;	/* BITMAP:  00000000 */

	nval = hweight32(prop->source_ports);
	prop->src_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
					माप(*prop->src_dpn_prop),
					GFP_KERNEL);
	अगर (!prop->src_dpn_prop)
		वापस -ENOMEM;

	dpn = prop->src_dpn_prop;
	i = 0;
	addr = prop->source_ports;
	क्रम_each_set_bit(bit, &addr, 32) अणु
		dpn[i].num = bit;
		dpn[i].simple_ch_prep_sm = true;
		dpn[i].ch_prep_समयout = 10;
		i++;
	पूर्ण

	/* set the समयout values */
	prop->clk_stop_समयout = 20;

	वापस 0;
पूर्ण

अटल काष्ठा sdw_slave_ops rt715_sdca_slave_ops = अणु
	.पढ़ो_prop = rt715_sdca_पढ़ो_prop,
	.update_status = rt715_sdca_update_status,
पूर्ण;

अटल पूर्णांक rt715_sdca_sdw_probe(काष्ठा sdw_slave *slave,
			   स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा regmap *mbq_regmap, *regmap;

	slave->ops = &rt715_sdca_slave_ops;

	/* Regmap Initialization */
	mbq_regmap = devm_regmap_init_sdw_mbq(slave, &rt715_sdca_mbq_regmap);
	अगर (IS_ERR(mbq_regmap))
		वापस PTR_ERR(mbq_regmap);

	regmap = devm_regmap_init_sdw(slave, &rt715_sdca_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस rt715_sdca_init(&slave->dev, mbq_regmap, regmap, slave);
पूर्ण

अटल स्थिर काष्ठा sdw_device_id rt715_sdca_id[] = अणु
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x715, 0x3, 0x1, 0),
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x714, 0x3, 0x1, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, rt715_sdca_id);

अटल पूर्णांक __maybe_unused rt715_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा rt715_sdca_priv *rt715 = dev_get_drvdata(dev);

	अगर (!rt715->hw_init)
		वापस 0;

	regcache_cache_only(rt715->regmap, true);
	regcache_mark_dirty(rt715->regmap);
	regcache_cache_only(rt715->mbq_regmap, true);
	regcache_mark_dirty(rt715->mbq_regmap);

	वापस 0;
पूर्ण

#घोषणा RT715_PROBE_TIMEOUT 5000

अटल पूर्णांक __maybe_unused rt715_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा rt715_sdca_priv *rt715 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;

	अगर (!rt715->hw_init)
		वापस 0;

	अगर (!slave->unattach_request)
		जाओ regmap_sync;

	समय = रुको_क्रम_completion_समयout(&slave->क्रमागतeration_complete,
					   msecs_to_jअगरfies(RT715_PROBE_TIMEOUT));
	अगर (!समय) अणु
		dev_err(&slave->dev, "Enumeration not complete, timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

regmap_sync:
	slave->unattach_request = 0;
	regcache_cache_only(rt715->regmap, false);
	regcache_sync_region(rt715->regmap,
		SDW_SDCA_CTL(FUN_JACK_CODEC, RT715_SDCA_ST_EN, RT715_SDCA_ST_CTRL,
			CH_00),
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_SMPU_TRIG_ST_EN,
			RT715_SDCA_SMPU_TRIG_ST_CTRL, CH_00));
	regcache_cache_only(rt715->mbq_regmap, false);
	regcache_sync_region(rt715->mbq_regmap, 0x2000000, 0x61020ff);
	regcache_sync_region(rt715->mbq_regmap,
		SDW_SDCA_CTL(FUN_JACK_CODEC, RT715_SDCA_ST_EN, RT715_SDCA_ST_CTRL,
			CH_00),
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_SMPU_TRIG_ST_EN,
			RT715_SDCA_SMPU_TRIG_ST_CTRL, CH_00));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt715_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rt715_dev_suspend, rt715_dev_resume)
	SET_RUNTIME_PM_OPS(rt715_dev_suspend, rt715_dev_resume, शून्य)
पूर्ण;

अटल काष्ठा sdw_driver rt715_sdw_driver = अणु
	.driver = अणु
		.name = "rt715-sdca",
		.owner = THIS_MODULE,
		.pm = &rt715_pm,
	पूर्ण,
	.probe = rt715_sdca_sdw_probe,
	.ops = &rt715_sdca_slave_ops,
	.id_table = rt715_sdca_id,
पूर्ण;
module_sdw_driver(rt715_sdw_driver);

MODULE_DESCRIPTION("ASoC RT715 driver SDW SDCA");
MODULE_AUTHOR("Jack Yu <jack.yu@realtek.com>");
MODULE_LICENSE("GPL v2");
