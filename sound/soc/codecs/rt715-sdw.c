<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rt715-sdw.c -- rt715 ALSA SoC audio driver
 *
 * Copyright(c) 2019 Realtek Semiconductor Corp.
 *
 * ALC715 ASoC Codec Driver based Intel Dummy SdW codec driver
 *
 */
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश "rt715.h"
#समावेश "rt715-sdw.h"

अटल bool rt715_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x00e0 ... 0x00e5:
	हाल 0x00ee ... 0x00ef:
	हाल 0x00f0 ... 0x00f5:
	हाल 0x00fe ... 0x00ff:
	हाल 0x02e0:
	हाल 0x02f0:
	हाल 0x04e0:
	हाल 0x04f0:
	हाल 0x06e0:
	हाल 0x06f0:
	हाल 0x2000 ... 0x2016:
	हाल 0x201a ... 0x2027:
	हाल 0x2029 ... 0x202a:
	हाल 0x202d ... 0x2034:
	हाल 0x2200 ... 0x2204:
	हाल 0x2206 ... 0x2212:
	हाल 0x2220 ... 0x2223:
	हाल 0x2230 ... 0x2239:
	हाल 0x22f0 ... 0x22f3:
	हाल 0x3122:
	हाल 0x3123:
	हाल 0x3124:
	हाल 0x3125:
	हाल 0x3607:
	हाल 0x3608:
	हाल 0x3609:
	हाल 0x3610:
	हाल 0x3611:
	हाल 0x3627:
	हाल 0x3712:
	हाल 0x3713:
	हाल 0x3718:
	हाल 0x3719:
	हाल 0x371a:
	हाल 0x371b:
	हाल 0x371d:
	हाल 0x3729:
	हाल 0x385e:
	हाल 0x3859:
	हाल 0x4c12:
	हाल 0x4c13:
	हाल 0x4c1d:
	हाल 0x4c29:
	हाल 0x4d12:
	हाल 0x4d13:
	हाल 0x4d1d:
	हाल 0x4d29:
	हाल 0x4e12:
	हाल 0x4e13:
	हाल 0x4e1d:
	हाल 0x4e29:
	हाल 0x4f12:
	हाल 0x4f13:
	हाल 0x4f1d:
	हाल 0x4f29:
	हाल 0x7207:
	हाल 0x7208:
	हाल 0x7209:
	हाल 0x7227:
	हाल 0x7307:
	हाल 0x7308:
	हाल 0x7309:
	हाल 0x7312:
	हाल 0x7313:
	हाल 0x7318:
	हाल 0x7319:
	हाल 0x731a:
	हाल 0x731b:
	हाल 0x731d:
	हाल 0x7327:
	हाल 0x7329:
	हाल 0x8287:
	हाल 0x8288:
	हाल 0x8289:
	हाल 0x82a7:
	हाल 0x8387:
	हाल 0x8388:
	हाल 0x8389:
	हाल 0x8392:
	हाल 0x8393:
	हाल 0x8398:
	हाल 0x8399:
	हाल 0x839a:
	हाल 0x839b:
	हाल 0x839d:
	हाल 0x83a7:
	हाल 0x83a9:
	हाल 0x752039:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt715_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x00e5:
	हाल 0x00f0:
	हाल 0x00f3:
	हाल 0x00f5:
	हाल 0x2009:
	हाल 0x2016:
	हाल 0x201b:
	हाल 0x201c:
	हाल 0x201d:
	हाल 0x201f:
	हाल 0x2023:
	हाल 0x2230:
	हाल 0x200b ... 0x200e: /* i2c पढ़ो */
	हाल 0x2012 ... 0x2015: /* HD-A पढ़ो */
	हाल 0x202d ... 0x202f: /* BRA */
	हाल 0x2201 ... 0x2212: /* i2c debug */
	हाल 0x2220 ... 0x2223: /* decoded HD-A */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक rt715_sdw_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा rt715_priv *rt715 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक sdw_data_3, sdw_data_2, sdw_data_1, sdw_data_0;
	अचिन्हित पूर्णांक reg2 = 0, reg3 = 0, reg4 = 0, mask, nid, val2;
	अचिन्हित पूर्णांक is_hda_reg = 1, is_index_reg = 0;
	पूर्णांक ret;

	अगर (reg > 0xffff)
		is_index_reg = 1;

	mask = reg & 0xf000;

	अगर (is_index_reg) अणु /* index रेजिस्टरs */
		val2 = reg & 0xff;
		reg = reg >> 8;
		nid = reg & 0xff;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg, 0);
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg2, val2);
		अगर (ret < 0)
			वापस ret;

		reg3 = RT715_PRIV_DATA_R_H | nid;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg3,
			((*val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg4 = reg3 + 0x1000;
		reg4 |= 0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg4, (*val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask   == 0x3000) अणु
		reg += 0x8000;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg, *val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask == 0x7000) अणु
		reg += 0x2000;
		reg |= 0x800;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg,
			((*val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg2, (*val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर ((reg & 0xff00) == 0x8300) अणु /* क्रम R channel */
		reg2 = reg - 0x1000;
		reg2 &= ~0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg2,
			((*val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg, (*val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask == 0x9000) अणु
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg,
			((*val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg2, (*val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask == 0xb000) अणु
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg, *val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(rt715->sdw_regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
		is_hda_reg = 0;
	पूर्ण

	अगर (is_hda_reg || is_index_reg) अणु
		sdw_data_3 = 0;
		sdw_data_2 = 0;
		sdw_data_1 = 0;
		sdw_data_0 = 0;
		ret = regmap_पढ़ो(rt715->sdw_regmap, RT715_READ_HDA_3,
			&sdw_data_3);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(rt715->sdw_regmap, RT715_READ_HDA_2,
			&sdw_data_2);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(rt715->sdw_regmap, RT715_READ_HDA_1,
			&sdw_data_1);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(rt715->sdw_regmap, RT715_READ_HDA_0,
			&sdw_data_0);
		अगर (ret < 0)
			वापस ret;
		*val = ((sdw_data_3 & 0xff) << 24) |
			((sdw_data_2 & 0xff) << 16) |
			((sdw_data_1 & 0xff) << 8) | (sdw_data_0 & 0xff);
	पूर्ण

	अगर (is_hda_reg == 0)
		dev_dbg(dev, "[%s] %04x => %08x\n", __func__, reg, *val);
	अन्यथा अगर (is_index_reg)
		dev_dbg(dev, "[%s] %04x %04x %04x %04x => %08x\n", __func__,
			reg, reg2, reg3, reg4, *val);
	अन्यथा
		dev_dbg(dev, "[%s] %04x %04x => %08x\n",
		__func__, reg, reg2, *val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_sdw_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा rt715_priv *rt715 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg2 = 0, reg3, reg4, nid, mask, val2;
	अचिन्हित पूर्णांक is_index_reg = 0;
	पूर्णांक ret;

	अगर (reg > 0xffff)
		is_index_reg = 1;

	mask = reg & 0xf000;

	अगर (is_index_reg) अणु /* index रेजिस्टरs */
		val2 = reg & 0xff;
		reg = reg >> 8;
		nid = reg & 0xff;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg, 0);
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg2, val2);
		अगर (ret < 0)
			वापस ret;

		reg3 = RT715_PRIV_DATA_W_H | nid;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg3,
			((val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg4 = reg3 + 0x1000;
		reg4 |= 0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg4, (val & 0xff));
		अगर (ret < 0)
			वापस ret;
		is_index_reg = 1;
	पूर्ण अन्यथा अगर (reg < 0x4fff) अणु
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (reg == RT715_FUNC_RESET) अणु
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask == 0x7000) अणु
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg,
			((val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg2, (val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर ((reg & 0xff00) == 0x8300) अणु  /* क्रम R channel */
		reg2 = reg - 0x1000;
		reg2 &= ~0x80;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg2,
			((val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		ret = regmap_ग_लिखो(rt715->sdw_regmap, reg, (val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (reg2 == 0)
		dev_dbg(dev, "[%s] %04x <= %04x\n", __func__, reg, val);
	अन्यथा अगर (is_index_reg)
		dev_dbg(dev, "[%s] %04x %04x %04x %04x <= %04x %04x\n",
			__func__, reg, reg2, reg3, reg4, val2, val);
	अन्यथा
		dev_dbg(dev, "[%s] %04x %04x <= %04x\n",
		__func__, reg, reg2, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config rt715_regmap = अणु
	.reg_bits = 24,
	.val_bits = 32,
	.पढ़ोable_reg = rt715_पढ़ोable_रेजिस्टर, /* Readable रेजिस्टरs */
	.अस्थिर_reg = rt715_अस्थिर_रेजिस्टर, /* अस्थिर रेजिस्टर */
	.max_रेजिस्टर = 0x752039, /* Maximum number of रेजिस्टर */
	.reg_शेषs = rt715_reg_शेषs, /* Defaults */
	.num_reg_शेषs = ARRAY_SIZE(rt715_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.reg_पढ़ो = rt715_sdw_पढ़ो,
	.reg_ग_लिखो = rt715_sdw_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt715_sdw_regmap = अणु
	.name = "sdw",
	.reg_bits = 32, /* Total रेजिस्टर space क्रम SDW */
	.val_bits = 8, /* Total number of bits in रेजिस्टर */
	.max_रेजिस्टर = 0xff01, /* Maximum number of रेजिस्टर */
	.cache_type = REGCACHE_NONE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

पूर्णांक hda_to_sdw(अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक payload,
	       अचिन्हित पूर्णांक *sdw_addr_h, अचिन्हित पूर्णांक *sdw_data_h,
	       अचिन्हित पूर्णांक *sdw_addr_l, अचिन्हित पूर्णांक *sdw_data_l)
अणु
	अचिन्हित पूर्णांक offset_h, offset_l, e_verb;

	अगर (((verb & 0xff) != 0) || verb == 0xf00) अणु /* 12 bits command */
		अगर (verb == 0x7ff) /* special हाल */
			offset_h = 0;
		अन्यथा
			offset_h = 0x3000;

		अगर (verb & 0x800) /* get command */
			e_verb = (verb - 0xf00) | 0x80;
		अन्यथा /* set command */
			e_verb = (verb - 0x700);

		*sdw_data_h = payload; /* 7 bits payload */
		*sdw_addr_l = *sdw_data_l = 0;
	पूर्ण अन्यथा अणु /* 4 bits command */
		अगर ((verb & 0x800) == 0x800) अणु /* पढ़ो */
			offset_h = 0x9000;
			offset_l = 0xa000;
		पूर्ण अन्यथा अणु /* ग_लिखो */
			offset_h = 0x7000;
			offset_l = 0x8000;
		पूर्ण
		e_verb = verb >> 8;
		*sdw_data_h = (payload >> 8); /* 16 bits payload [15:8] */
		*sdw_addr_l = (e_verb << 8) | nid | 0x80; /* 0x80: valid bit */
		*sdw_addr_l += offset_l;
		*sdw_data_l = payload & 0xff;
	पूर्ण

	*sdw_addr_h = (e_verb << 8) | nid;
	*sdw_addr_h += offset_h;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hda_to_sdw);

अटल पूर्णांक rt715_update_status(काष्ठा sdw_slave *slave,
				क्रमागत sdw_slave_status status)
अणु
	काष्ठा rt715_priv *rt715 = dev_get_drvdata(&slave->dev);

	/* Update the status */
	rt715->status = status;
	/*
	 * Perक्रमm initialization only अगर slave status is present and
	 * hw_init flag is false
	 */
	अगर (rt715->hw_init || rt715->status != SDW_SLAVE_ATTACHED)
		वापस 0;

	/* perक्रमm I/O transfers required क्रम Slave initialization */
	वापस rt715_io_init(&slave->dev, slave);
पूर्ण

अटल पूर्णांक rt715_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक nval, i;
	u32 bit;
	अचिन्हित दीर्घ addr;
	काष्ठा sdw_dpn_prop *dpn;

	prop->scp_पूर्णांक1_mask = SDW_SCP_INT1_IMPL_DEF | SDW_SCP_INT1_BUS_CLASH |
		SDW_SCP_INT1_PARITY;
	prop->quirks = SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY;

	prop->paging_support = false;

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

	/* wake-up event */
	prop->wake_capable = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_bus_config(काष्ठा sdw_slave *slave,
				काष्ठा sdw_bus_params *params)
अणु
	काष्ठा rt715_priv *rt715 = dev_get_drvdata(&slave->dev);
	पूर्णांक ret;

	स_नकल(&rt715->params, params, माप(*params));

	ret = rt715_घड़ी_config(&slave->dev);
	अगर (ret < 0)
		dev_err(&slave->dev, "Invalid clk config");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_slave_ops rt715_slave_ops = अणु
	.पढ़ो_prop = rt715_पढ़ो_prop,
	.update_status = rt715_update_status,
	.bus_config = rt715_bus_config,
पूर्ण;

अटल पूर्णांक rt715_sdw_probe(काष्ठा sdw_slave *slave,
			   स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा regmap *sdw_regmap, *regmap;

	/* Regmap Initialization */
	sdw_regmap = devm_regmap_init_sdw(slave, &rt715_sdw_regmap);
	अगर (IS_ERR(sdw_regmap))
		वापस PTR_ERR(sdw_regmap);

	regmap = devm_regmap_init(&slave->dev, शून्य, &slave->dev,
		&rt715_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	rt715_init(&slave->dev, sdw_regmap, regmap, slave);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_device_id rt715_id[] = अणु
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x714, 0x2, 0, 0),
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x715, 0x2, 0, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, rt715_id);

अटल पूर्णांक __maybe_unused rt715_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा rt715_priv *rt715 = dev_get_drvdata(dev);

	अगर (!rt715->hw_init)
		वापस 0;

	regcache_cache_only(rt715->regmap, true);

	वापस 0;
पूर्ण

#घोषणा RT715_PROBE_TIMEOUT 5000

अटल पूर्णांक __maybe_unused rt715_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा rt715_priv *rt715 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;

	अगर (!rt715->hw_init)
		वापस 0;

	अगर (!slave->unattach_request)
		जाओ regmap_sync;

	समय = रुको_क्रम_completion_समयout(&slave->initialization_complete,
					   msecs_to_jअगरfies(RT715_PROBE_TIMEOUT));
	अगर (!समय) अणु
		dev_err(&slave->dev, "Initialization not complete, timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

regmap_sync:
	slave->unattach_request = 0;
	regcache_cache_only(rt715->regmap, false);
	regcache_sync_region(rt715->regmap, 0x3000, 0x8fff);
	regcache_sync_region(rt715->regmap, 0x752039, 0x752039);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt715_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rt715_dev_suspend, rt715_dev_resume)
	SET_RUNTIME_PM_OPS(rt715_dev_suspend, rt715_dev_resume, शून्य)
पूर्ण;

अटल काष्ठा sdw_driver rt715_sdw_driver = अणु
	.driver = अणु
		   .name = "rt715",
		   .owner = THIS_MODULE,
		   .pm = &rt715_pm,
		   पूर्ण,
	.probe = rt715_sdw_probe,
	.ops = &rt715_slave_ops,
	.id_table = rt715_id,
पूर्ण;
module_sdw_driver(rt715_sdw_driver);

MODULE_DESCRIPTION("ASoC RT715 driver SDW");
MODULE_AUTHOR("Jack Yu <jack.yu@realtek.com>");
MODULE_LICENSE("GPL v2");
