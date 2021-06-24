<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2014 Imagination Technologies Ltd.
 */
#अगर_अघोषित __ASM_CDMM_H
#घोषणा __ASM_CDMM_H

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>

/**
 * काष्ठा mips_cdmm_device - Represents a single device on a CDMM bus.
 * @dev:	Driver model device object.
 * @cpu:	CPU which can access this device.
 * @res:	MMIO resource.
 * @type:	Device type identअगरier.
 * @rev:	Device revision number.
 */
काष्ठा mips_cdmm_device अणु
	काष्ठा device		dev;
	अचिन्हित पूर्णांक		cpu;
	काष्ठा resource		res;
	अचिन्हित पूर्णांक		type;
	अचिन्हित पूर्णांक		rev;
पूर्ण;

/**
 * काष्ठा mips_cdmm_driver - Represents a driver क्रम a CDMM device.
 * @drv:	Driver model driver object.
 * @probe	Callback क्रम probing newly discovered devices.
 * @हटाओ:	Callback to हटाओ the device.
 * @shutकरोwn:	Callback on प्रणाली shutकरोwn.
 * @cpu_करोwn:	Callback when the parent CPU is going करोwn.
 *		Any CPU pinned thपढ़ोs/समयrs should be disabled.
 * @cpu_up:	Callback when the parent CPU is coming back up again.
 *		CPU pinned thपढ़ोs/समयrs can be restarted.
 * @id_table:	Table क्रम CDMM IDs to match against.
 */
काष्ठा mips_cdmm_driver अणु
	काष्ठा device_driver	drv;
	पूर्णांक			(*probe)(काष्ठा mips_cdmm_device *);
	पूर्णांक			(*हटाओ)(काष्ठा mips_cdmm_device *);
	व्योम			(*shutकरोwn)(काष्ठा mips_cdmm_device *);
	पूर्णांक			(*cpu_करोwn)(काष्ठा mips_cdmm_device *);
	पूर्णांक			(*cpu_up)(काष्ठा mips_cdmm_device *);
	स्थिर काष्ठा mips_cdmm_device_id *id_table;
पूर्ण;

/**
 * mips_cdmm_phys_base() - Choose a physical base address क्रम CDMM region.
 *
 * Picking a suitable physical address at which to map the CDMM region is
 * platक्रमm specअगरic, so this function can be defined by platक्रमm code to
 * pick a suitable value अगर none is configured by the bootloader.
 *
 * This address must be 32kB aligned, and the region occupies a maximum of 32kB
 * of physical address space which must not be used क्रम anything अन्यथा.
 *
 * Returns:	Physical base address क्रम CDMM region, or 0 on failure.
 */
phys_addr_t mips_cdmm_phys_base(व्योम);

बाह्य काष्ठा bus_type mips_cdmm_bustype;
व्योम __iomem *mips_cdmm_early_probe(अचिन्हित पूर्णांक dev_type);

#घोषणा to_mips_cdmm_device(d)	container_of(d, काष्ठा mips_cdmm_device, dev)

#घोषणा mips_cdmm_get_drvdata(d)	dev_get_drvdata(&d->dev)
#घोषणा mips_cdmm_set_drvdata(d, p)	dev_set_drvdata(&d->dev, p)

पूर्णांक mips_cdmm_driver_रेजिस्टर(काष्ठा mips_cdmm_driver *);
व्योम mips_cdmm_driver_unरेजिस्टर(काष्ठा mips_cdmm_driver *);

/*
 * module_mips_cdmm_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_mips_cdmm_driver(__mips_cdmm_driver) \
	module_driver(__mips_cdmm_driver, mips_cdmm_driver_रेजिस्टर, \
			mips_cdmm_driver_unरेजिस्टर)

/*
 * builtin_mips_cdmm_driver() - Helper macro क्रम drivers that करोn't करो anything
 * special in init and have no निकास. This eliminates some boilerplate. Each
 * driver may only use this macro once, and calling it replaces device_initcall
 * (or in some हालs, the legacy __initcall). This is meant to be a direct
 * parallel of module_mips_cdmm_driver() above but without the __निकास stuff that
 * is not used क्रम builtin हालs.
 */
#घोषणा builtin_mips_cdmm_driver(__mips_cdmm_driver) \
	builtin_driver(__mips_cdmm_driver, mips_cdmm_driver_रेजिस्टर)

/* drivers/tty/mips_ejtag_fdc.c */

#अगर_घोषित CONFIG_MIPS_EJTAG_FDC_EARLYCON
पूर्णांक setup_early_fdc_console(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक setup_early_fdc_console(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_CDMM_H */
