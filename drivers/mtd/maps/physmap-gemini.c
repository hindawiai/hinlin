<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cortina Systems Gemini OF physmap add-on
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * This SoC has an elaborate flash control रेजिस्टर, so we need to
 * detect and set it up when booting on this platक्रमm.
 */
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/xip.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश "physmap-gemini.h"

/*
 * The Flash-relevant parts of the global status रेजिस्टर
 * These would also be relevant क्रम a न_अंकD driver.
 */
#घोषणा GLOBAL_STATUS			0x04
#घोषणा FLASH_TYPE_MASK			(0x3 << 24)
#घोषणा FLASH_TYPE_न_अंकD_2K		(0x3 << 24)
#घोषणा FLASH_TYPE_न_अंकD_512		(0x2 << 24)
#घोषणा FLASH_TYPE_PARALLEL		(0x1 << 24)
#घोषणा FLASH_TYPE_SERIAL		(0x0 << 24)
/* अगर parallel */
#घोषणा FLASH_WIDTH_16BIT		(1 << 23)	/* अन्यथा 8 bit */
/* अगर serial */
#घोषणा FLASH_ATMEL			(1 << 23)	/* अन्यथा STM */

#घोषणा FLASH_SIZE_MASK			(0x3 << 21)
#घोषणा न_अंकD_256M			(0x3 << 21)	/* and more */
#घोषणा न_अंकD_128M			(0x2 << 21)
#घोषणा न_अंकD_64M			(0x1 << 21)
#घोषणा न_अंकD_32M			(0x0 << 21)
#घोषणा ATMEL_16M			(0x3 << 21)	/* and more */
#घोषणा ATMEL_8M			(0x2 << 21)
#घोषणा ATMEL_4M_2M			(0x1 << 21)
#घोषणा ATMEL_1M			(0x0 << 21)	/* and less */
#घोषणा STM_32M				(1 << 22)	/* and more */
#घोषणा STM_16M				(0 << 22)	/* and less */

#घोषणा FLASH_PARALLEL_HIGH_PIN_CNT	(1 << 20)	/* अन्यथा low pin cnt */

काष्ठा gemini_flash अणु
	काष्ठा device *dev;
	काष्ठा pinctrl *p;
	काष्ठा pinctrl_state *enabled_state;
	काष्ठा pinctrl_state *disabled_state;
पूर्ण;

/* Static local state */
अटल काष्ठा gemini_flash *gf;

अटल व्योम gemini_flash_enable_pins(व्योम)
अणु
	पूर्णांक ret;

	अगर (IS_ERR(gf->enabled_state))
		वापस;
	ret = pinctrl_select_state(gf->p, gf->enabled_state);
	अगर (ret)
		dev_err(gf->dev, "failed to enable pins\n");
पूर्ण

अटल व्योम gemini_flash_disable_pins(व्योम)
अणु
	पूर्णांक ret;

	अगर (IS_ERR(gf->disabled_state))
		वापस;
	ret = pinctrl_select_state(gf->p, gf->disabled_state);
	अगर (ret)
		dev_err(gf->dev, "failed to disable pins\n");
पूर्ण

अटल map_word __xipram gemini_flash_map_पढ़ो(काष्ठा map_info *map,
					       अचिन्हित दीर्घ ofs)
अणु
	map_word ret;

	gemini_flash_enable_pins();
	ret = अंतरभूत_map_पढ़ो(map, ofs);
	gemini_flash_disable_pins();

	वापस ret;
पूर्ण

अटल व्योम __xipram gemini_flash_map_ग_लिखो(काष्ठा map_info *map,
					    स्थिर map_word datum,
					    अचिन्हित दीर्घ ofs)
अणु
	gemini_flash_enable_pins();
	अंतरभूत_map_ग_लिखो(map, datum, ofs);
	gemini_flash_disable_pins();
पूर्ण

अटल व्योम __xipram gemini_flash_map_copy_from(काष्ठा map_info *map,
						व्योम *to, अचिन्हित दीर्घ from,
						sमाप_प्रकार len)
अणु
	gemini_flash_enable_pins();
	अंतरभूत_map_copy_from(map, to, from, len);
	gemini_flash_disable_pins();
पूर्ण

अटल व्योम __xipram gemini_flash_map_copy_to(काष्ठा map_info *map,
					      अचिन्हित दीर्घ to,
					      स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	gemini_flash_enable_pins();
	अंतरभूत_map_copy_to(map, to, from, len);
	gemini_flash_disable_pins();
पूर्ण

पूर्णांक of_flash_probe_gemini(काष्ठा platक्रमm_device *pdev,
			  काष्ठा device_node *np,
			  काष्ठा map_info *map)
अणु
	काष्ठा regmap *rmap;
	काष्ठा device *dev = &pdev->dev;
	u32 val;
	पूर्णांक ret;

	/* Multiplatक्रमm guard */
	अगर (!of_device_is_compatible(np, "cortina,gemini-flash"))
		वापस 0;

	gf = devm_kzalloc(dev, माप(*gf), GFP_KERNEL);
	अगर (!gf)
		वापस -ENOMEM;
	gf->dev = dev;

	rmap = syscon_regmap_lookup_by_phandle(np, "syscon");
	अगर (IS_ERR(rmap)) अणु
		dev_err(dev, "no syscon\n");
		वापस PTR_ERR(rmap);
	पूर्ण

	ret = regmap_पढ़ो(rmap, GLOBAL_STATUS, &val);
	अगर (ret) अणु
		dev_err(dev, "failed to read global status register\n");
		वापस -ENODEV;
	पूर्ण
	dev_dbg(dev, "global status reg: %08x\n", val);

	/*
	 * It would be contradictory अगर a physmap flash was NOT parallel.
	 */
	अगर ((val & FLASH_TYPE_MASK) != FLASH_TYPE_PARALLEL) अणु
		dev_err(dev, "flash is not parallel\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Complain अगर DT data and hardware definition is dअगरferent.
	 */
	अगर (val & FLASH_WIDTH_16BIT) अणु
		अगर (map->bankwidth != 2)
			dev_warn(dev, "flash hardware say flash is 16 bit wide but DT says it is %d bits wide\n",
				 map->bankwidth * 8);
	पूर्ण अन्यथा अणु
		अगर (map->bankwidth != 1)
			dev_warn(dev, "flash hardware say flash is 8 bit wide but DT says it is %d bits wide\n",
				 map->bankwidth * 8);
	पूर्ण

	gf->p = devm_pinctrl_get(dev);
	अगर (IS_ERR(gf->p)) अणु
		dev_err(dev, "no pinctrl handle\n");
		ret = PTR_ERR(gf->p);
		वापस ret;
	पूर्ण

	gf->enabled_state = pinctrl_lookup_state(gf->p, "enabled");
	अगर (IS_ERR(gf->enabled_state))
		dev_err(dev, "no enabled pin control state\n");

	gf->disabled_state = pinctrl_lookup_state(gf->p, "disabled");
	अगर (IS_ERR(gf->enabled_state)) अणु
		dev_err(dev, "no disabled pin control state\n");
	पूर्ण अन्यथा अणु
		ret = pinctrl_select_state(gf->p, gf->disabled_state);
		अगर (ret)
			dev_err(gf->dev, "failed to disable pins\n");
	पूर्ण

	map->पढ़ो = gemini_flash_map_पढ़ो;
	map->ग_लिखो = gemini_flash_map_ग_लिखो;
	map->copy_from = gemini_flash_map_copy_from;
	map->copy_to = gemini_flash_map_copy_to;

	dev_info(dev, "initialized Gemini-specific physmap control\n");

	वापस 0;
पूर्ण
