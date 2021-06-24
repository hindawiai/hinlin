<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BCM947xx nvram variable access
 *
 * Copyright (C) 2005 Broadcom Corporation
 * Copyright (C) 2006 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2010-2012 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/bcm47xx_nvram.h>

#घोषणा NVRAM_MAGIC			0x48534C46	/* 'FLSH' */
#घोषणा NVRAM_SPACE			0x10000
#घोषणा NVRAM_MAX_GPIO_ENTRIES		32
#घोषणा NVRAM_MAX_GPIO_VALUE_LEN	30

#घोषणा FLASH_MIN		0x00020000	/* Minimum flash size */

काष्ठा nvram_header अणु
	u32 magic;
	u32 len;
	u32 crc_ver_init;	/* 0:7 crc, 8:15 ver, 16:31 sdram_init */
	u32 config_refresh;	/* 0:15 sdram_config, 16:31 sdram_refresh */
	u32 config_ncdl;	/* ncdl values क्रम memc */
पूर्ण;

अटल अक्षर nvram_buf[NVRAM_SPACE];
अटल माप_प्रकार nvram_len;
अटल स्थिर u32 nvram_sizes[] = अणु0x6000, 0x8000, 0xF000, 0x10000पूर्ण;

/**
 * bcm47xx_nvram_is_valid - check क्रम a valid NVRAM at specअगरied memory
 */
अटल bool bcm47xx_nvram_is_valid(व्योम __iomem *nvram)
अणु
	वापस ((काष्ठा nvram_header *)nvram)->magic == NVRAM_MAGIC;
पूर्ण

/**
 * bcm47xx_nvram_copy - copy NVRAM to पूर्णांकernal buffer
 */
अटल व्योम bcm47xx_nvram_copy(व्योम __iomem *nvram_start, माप_प्रकार res_size)
अणु
	काष्ठा nvram_header __iomem *header = nvram_start;
	माप_प्रकार copy_size;

	copy_size = header->len;
	अगर (copy_size > res_size) अणु
		pr_err("The nvram size according to the header seems to be bigger than the partition on flash\n");
		copy_size = res_size;
	पूर्ण
	अगर (copy_size >= NVRAM_SPACE) अणु
		pr_err("nvram on flash (%zu bytes) is bigger than the reserved space in memory, will just copy the first %i bytes\n",
		       copy_size, NVRAM_SPACE - 1);
		copy_size = NVRAM_SPACE - 1;
	पूर्ण

	__ioपढ़ो32_copy(nvram_buf, nvram_start, DIV_ROUND_UP(copy_size, 4));
	nvram_buf[NVRAM_SPACE - 1] = '\0';
	nvram_len = copy_size;
पूर्ण

/**
 * bcm47xx_nvram_find_and_copy - find NVRAM on flash mapping & copy it
 */
अटल पूर्णांक bcm47xx_nvram_find_and_copy(व्योम __iomem *flash_start, माप_प्रकार res_size)
अणु
	माप_प्रकार flash_size;
	माप_प्रकार offset;
	पूर्णांक i;

	अगर (nvram_len) अणु
		pr_warn("nvram already initialized\n");
		वापस -EEXIST;
	पूर्ण

	/* TODO: when nvram is on nand flash check क्रम bad blocks first. */

	/* Try every possible flash size and check क्रम NVRAM at its end */
	क्रम (flash_size = FLASH_MIN; flash_size <= res_size; flash_size <<= 1) अणु
		क्रम (i = 0; i < ARRAY_SIZE(nvram_sizes); i++) अणु
			offset = flash_size - nvram_sizes[i];
			अगर (bcm47xx_nvram_is_valid(flash_start + offset))
				जाओ found;
		पूर्ण
	पूर्ण

	/* Try embedded NVRAM at 4 KB and 1 KB as last resorts */

	offset = 4096;
	अगर (bcm47xx_nvram_is_valid(flash_start + offset))
		जाओ found;

	offset = 1024;
	अगर (bcm47xx_nvram_is_valid(flash_start + offset))
		जाओ found;

	pr_err("no nvram found\n");
	वापस -ENXIO;

found:
	bcm47xx_nvram_copy(flash_start + offset, res_size - offset);

	वापस 0;
पूर्ण

/*
 * On bcm47xx we need access to the NVRAM very early, so we can't use mtd
 * subप्रणाली to access flash. We can't even use platक्रमm device / driver to
 * store memory offset.
 * To handle this we provide following symbol. It's supposed to be called as
 * soon as we get info about flash device, beक्रमe any NVRAM entry is needed.
 */
पूर्णांक bcm47xx_nvram_init_from_mem(u32 base, u32 lim)
अणु
	व्योम __iomem *iobase;
	पूर्णांक err;

	iobase = ioremap(base, lim);
	अगर (!iobase)
		वापस -ENOMEM;

	err = bcm47xx_nvram_find_and_copy(iobase, lim);

	iounmap(iobase);

	वापस err;
पूर्ण

अटल पूर्णांक nvram_init(व्योम)
अणु
#अगर_घोषित CONFIG_MTD
	काष्ठा mtd_info *mtd;
	काष्ठा nvram_header header;
	माप_प्रकार bytes_पढ़ो;
	पूर्णांक err;

	mtd = get_mtd_device_nm("nvram");
	अगर (IS_ERR(mtd))
		वापस -ENODEV;

	err = mtd_पढ़ो(mtd, 0, माप(header), &bytes_पढ़ो, (uपूर्णांक8_t *)&header);
	अगर (!err && header.magic == NVRAM_MAGIC &&
	    header.len > माप(header)) अणु
		nvram_len = header.len;
		अगर (nvram_len >= NVRAM_SPACE) अणु
			pr_err("nvram on flash (%zu bytes) is bigger than the reserved space in memory, will just copy the first %i bytes\n",
				nvram_len, NVRAM_SPACE);
			nvram_len = NVRAM_SPACE - 1;
		पूर्ण

		err = mtd_पढ़ो(mtd, 0, nvram_len, &nvram_len,
			       (u8 *)nvram_buf);
		वापस err;
	पूर्ण
#पूर्ण_अगर

	वापस -ENXIO;
पूर्ण

पूर्णांक bcm47xx_nvram_दो_पर्या(स्थिर अक्षर *name, अक्षर *val, माप_प्रकार val_len)
अणु
	अक्षर *var, *value, *end, *eq;
	पूर्णांक err;

	अगर (!name)
		वापस -EINVAL;

	अगर (!nvram_len) अणु
		err = nvram_init();
		अगर (err)
			वापस err;
	पूर्ण

	/* Look क्रम name=value and वापस value */
	var = &nvram_buf[माप(काष्ठा nvram_header)];
	end = nvram_buf + माप(nvram_buf);
	जबतक (var < end && *var) अणु
		eq = म_अक्षर(var, '=');
		अगर (!eq)
			अवरोध;
		value = eq + 1;
		अगर (eq - var == म_माप(name) &&
		    म_भेदन(var, name, eq - var) == 0)
			वापस snम_लिखो(val, val_len, "%s", value);
		var = value + म_माप(value) + 1;
	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(bcm47xx_nvram_दो_पर्या);

पूर्णांक bcm47xx_nvram_gpio_pin(स्थिर अक्षर *name)
अणु
	पूर्णांक i, err;
	अक्षर nvram_var[] = "gpioXX";
	अक्षर buf[NVRAM_MAX_GPIO_VALUE_LEN];

	/* TODO: Optimize it to करोn't call दो_पर्या so many बार */
	क्रम (i = 0; i < NVRAM_MAX_GPIO_ENTRIES; i++) अणु
		err = snम_लिखो(nvram_var, माप(nvram_var), "gpio%i", i);
		अगर (err <= 0)
			जारी;
		err = bcm47xx_nvram_दो_पर्या(nvram_var, buf, माप(buf));
		अगर (err <= 0)
			जारी;
		अगर (!म_भेद(name, buf))
			वापस i;
	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(bcm47xx_nvram_gpio_pin);

अक्षर *bcm47xx_nvram_get_contents(माप_प्रकार *nvram_size)
अणु
	पूर्णांक err;
	अक्षर *nvram;

	अगर (!nvram_len) अणु
		err = nvram_init();
		अगर (err)
			वापस शून्य;
	पूर्ण

	*nvram_size = nvram_len - माप(काष्ठा nvram_header);
	nvram = vदो_स्मृति(*nvram_size);
	अगर (!nvram)
		वापस शून्य;
	स_नकल(nvram, &nvram_buf[माप(काष्ठा nvram_header)], *nvram_size);

	वापस nvram;
पूर्ण
EXPORT_SYMBOL(bcm47xx_nvram_get_contents);

MODULE_LICENSE("GPL v2");
