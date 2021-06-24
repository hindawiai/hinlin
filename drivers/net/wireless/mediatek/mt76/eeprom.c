<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/etherdevice.h>
#समावेश "mt76.h"

पूर्णांक mt76_get_of_eeprom(काष्ठा mt76_dev *dev, व्योम *eep, पूर्णांक offset, पूर्णांक len)
अणु
#अगर defined(CONFIG_OF) && defined(CONFIG_MTD)
	काष्ठा device_node *np = dev->dev->of_node;
	काष्ठा mtd_info *mtd;
	स्थिर __be32 *list;
	स्थिर अक्षर *part;
	phandle phandle;
	पूर्णांक size;
	माप_प्रकार retlen;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENOENT;

	list = of_get_property(np, "mediatek,mtd-eeprom", &size);
	अगर (!list)
		वापस -ENOENT;

	phandle = be32_to_cpup(list++);
	अगर (!phandle)
		वापस -ENOENT;

	np = of_find_node_by_phandle(phandle);
	अगर (!np)
		वापस -EINVAL;

	part = of_get_property(np, "label", शून्य);
	अगर (!part)
		part = np->name;

	mtd = get_mtd_device_nm(part);
	अगर (IS_ERR(mtd)) अणु
		ret =  PTR_ERR(mtd);
		जाओ out_put_node;
	पूर्ण

	अगर (size <= माप(*list)) अणु
		ret = -EINVAL;
		जाओ out_put_node;
	पूर्ण

	offset = be32_to_cpup(list);
	ret = mtd_पढ़ो(mtd, offset, len, &retlen, eep);
	put_mtd_device(mtd);
	अगर (ret)
		जाओ out_put_node;

	अगर (retlen < len) अणु
		ret = -EINVAL;
		जाओ out_put_node;
	पूर्ण

	अगर (of_property_पढ़ो_bool(dev->dev->of_node, "big-endian")) अणु
		u8 *data = (u8 *)eep;
		पूर्णांक i;

		/* convert eeprom data in Little Endian */
		क्रम (i = 0; i < round_करोwn(len, 2); i += 2)
			put_unaligned_le16(get_unaligned_be16(&data[i]),
					   &data[i]);
	पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE
	dev->test_mtd.name = devm_kstrdup(dev->dev, part, GFP_KERNEL);
	dev->test_mtd.offset = offset;
#पूर्ण_अगर

out_put_node:
	of_node_put(np);
	वापस ret;
#अन्यथा
	वापस -ENOENT;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(mt76_get_of_eeprom);

व्योम
mt76_eeprom_override(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा device_node *np = dev->dev->of_node;

	of_get_mac_address(np, phy->macaddr);

	अगर (!is_valid_ether_addr(phy->macaddr)) अणु
		eth_अक्रमom_addr(phy->macaddr);
		dev_info(dev->dev,
			 "Invalid MAC address, using random address %pM\n",
			 phy->macaddr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76_eeprom_override);

अटल bool mt76_string_prop_find(काष्ठा property *prop, स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *cp = शून्य;

	अगर (!prop || !str || !str[0])
		वापस false;

	जबतक ((cp = of_prop_next_string(prop, cp)) != शून्य)
		अगर (!strहालcmp(cp, str))
			वापस true;

	वापस false;
पूर्ण

अटल काष्ठा device_node *
mt76_find_घातer_limits_node(काष्ठा mt76_dev *dev)
अणु
	काष्ठा device_node *np = dev->dev->of_node;
	स्थिर अक्षर *स्थिर region_names[] = अणु
		[NL80211_DFS_ETSI] = "etsi",
		[NL80211_DFS_FCC] = "fcc",
		[NL80211_DFS_JP] = "jp",
	पूर्ण;
	काष्ठा device_node *cur, *fallback = शून्य;
	स्थिर अक्षर *region_name = शून्य;

	अगर (dev->region < ARRAY_SIZE(region_names))
		region_name = region_names[dev->region];

	np = of_get_child_by_name(np, "power-limits");
	अगर (!np)
		वापस शून्य;

	क्रम_each_child_of_node(np, cur) अणु
		काष्ठा property *country = of_find_property(cur, "country", शून्य);
		काष्ठा property *regd = of_find_property(cur, "regdomain", शून्य);

		अगर (!country && !regd) अणु
			fallback = cur;
			जारी;
		पूर्ण

		अगर (mt76_string_prop_find(country, dev->alpha2) ||
		    mt76_string_prop_find(regd, region_name))
			वापस cur;
	पूर्ण

	वापस fallback;
पूर्ण

अटल स्थिर __be32 *
mt76_get_of_array(काष्ठा device_node *np, अक्षर *name, माप_प्रकार *len, पूर्णांक min)
अणु
	काष्ठा property *prop = of_find_property(np, name, शून्य);

	अगर (!prop || !prop->value || prop->length < min * 4)
		वापस शून्य;

	*len = prop->length;

	वापस prop->value;
पूर्ण

अटल काष्ठा device_node *
mt76_find_channel_node(काष्ठा device_node *np, काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा device_node *cur;
	स्थिर __be32 *val;
	माप_प्रकार len;

	क्रम_each_child_of_node(np, cur) अणु
		val = mt76_get_of_array(cur, "channels", &len, 2);
		अगर (!val)
			जारी;

		जबतक (len >= 2 * माप(*val)) अणु
			अगर (chan->hw_value >= be32_to_cpu(val[0]) &&
			    chan->hw_value <= be32_to_cpu(val[1]))
				वापस cur;

			val += 2;
			len -= 2 * माप(*val);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल s8
mt76_get_txs_delta(काष्ठा device_node *np, u8 nss)
अणु
	स्थिर __be32 *val;
	माप_प्रकार len;

	val = mt76_get_of_array(np, "txs-delta", &len, nss);
	अगर (!val)
		वापस 0;

	वापस be32_to_cpu(val[nss - 1]);
पूर्ण

अटल व्योम
mt76_apply_array_limit(s8 *pwr, माप_प्रकार pwr_len, स्थिर __be32 *data,
		       s8 target_घातer, s8 nss_delta, s8 *max_घातer)
अणु
	पूर्णांक i;

	अगर (!data)
		वापस;

	क्रम (i = 0; i < pwr_len; i++) अणु
		pwr[i] = min_t(s8, target_घातer,
			       be32_to_cpu(data[i]) + nss_delta);
		*max_घातer = max(*max_घातer, pwr[i]);
	पूर्ण
पूर्ण

अटल व्योम
mt76_apply_multi_array_limit(s8 *pwr, माप_प्रकार pwr_len, s8 pwr_num,
			     स्थिर __be32 *data, माप_प्रकार len, s8 target_घातer,
			     s8 nss_delta, s8 *max_घातer)
अणु
	पूर्णांक i, cur;

	अगर (!data)
		वापस;

	len /= 4;
	cur = be32_to_cpu(data[0]);
	क्रम (i = 0; i < pwr_num; i++) अणु
		अगर (len < pwr_len + 1)
			अवरोध;

		mt76_apply_array_limit(pwr + pwr_len * i, pwr_len, data + 1,
				       target_घातer, nss_delta, max_घातer);
		अगर (--cur > 0)
			जारी;

		data += pwr_len + 1;
		len -= pwr_len + 1;
		अगर (!len)
			अवरोध;

		cur = be32_to_cpu(data[0]);
	पूर्ण
पूर्ण

s8 mt76_get_rate_घातer_limits(काष्ठा mt76_phy *phy,
			      काष्ठा ieee80211_channel *chan,
			      काष्ठा mt76_घातer_limits *dest,
			      s8 target_घातer)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा device_node *np;
	स्थिर __be32 *val;
	अक्षर name[16];
	u32 mcs_rates = dev->drv->mcs_rates;
	u32 ru_rates = ARRAY_SIZE(dest->ru[0]);
	अक्षर band;
	माप_प्रकार len;
	s8 max_घातer = 0;
	s8 txs_delta;

	अगर (!mcs_rates)
		mcs_rates = 10;

	स_रखो(dest, target_घातer, माप(*dest));

	अगर (!IS_ENABLED(CONFIG_OF))
		वापस target_घातer;

	np = mt76_find_घातer_limits_node(dev);
	अगर (!np)
		वापस target_घातer;

	चयन (chan->band) अणु
	हाल NL80211_BAND_2GHZ:
		band = '2';
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		band = '5';
		अवरोध;
	शेष:
		वापस target_घातer;
	पूर्ण

	snम_लिखो(name, माप(name), "txpower-%cg", band);
	np = of_get_child_by_name(np, name);
	अगर (!np)
		वापस target_घातer;

	np = mt76_find_channel_node(np, chan);
	अगर (!np)
		वापस target_घातer;

	txs_delta = mt76_get_txs_delta(np, hweight8(phy->antenna_mask));

	val = mt76_get_of_array(np, "rates-cck", &len, ARRAY_SIZE(dest->cck));
	mt76_apply_array_limit(dest->cck, ARRAY_SIZE(dest->cck), val,
			       target_घातer, txs_delta, &max_घातer);

	val = mt76_get_of_array(np, "rates-ofdm",
				&len, ARRAY_SIZE(dest->ofdm));
	mt76_apply_array_limit(dest->ofdm, ARRAY_SIZE(dest->ofdm), val,
			       target_घातer, txs_delta, &max_घातer);

	val = mt76_get_of_array(np, "rates-mcs", &len, mcs_rates + 1);
	mt76_apply_multi_array_limit(dest->mcs[0], ARRAY_SIZE(dest->mcs[0]),
				     ARRAY_SIZE(dest->mcs), val, len,
				     target_घातer, txs_delta, &max_घातer);

	val = mt76_get_of_array(np, "rates-ru", &len, ru_rates + 1);
	mt76_apply_multi_array_limit(dest->ru[0], ARRAY_SIZE(dest->ru[0]),
				     ARRAY_SIZE(dest->ru), val, len,
				     target_घातer, txs_delta, &max_घातer);

	वापस max_घातer;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_get_rate_घातer_limits);

पूर्णांक
mt76_eeprom_init(काष्ठा mt76_dev *dev, पूर्णांक len)
अणु
	dev->eeprom.size = len;
	dev->eeprom.data = devm_kzalloc(dev->dev, len, GFP_KERNEL);
	अगर (!dev->eeprom.data)
		वापस -ENOMEM;

	वापस !mt76_get_of_eeprom(dev, dev->eeprom.data, 0, len);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_eeprom_init);
