<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Copyright (c) 2004-2005 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Header file क्रम Samsung CPU support
 */

/* toकरो - fix when rmk changes iodescs to use `व्योम __iomem *` */

#अगर_अघोषित __SAMSUNG_PLAT_CPU_H
#घोषणा __SAMSUNG_PLAT_CPU_H

बाह्य अचिन्हित दीर्घ samsung_cpu_id;

#घोषणा S3C2410_CPU_ID		0x32410000
#घोषणा S3C2410_CPU_MASK	0xFFFFFFFF

#घोषणा S3C24XX_CPU_ID		0x32400000
#घोषणा S3C24XX_CPU_MASK	0xFFF00000

#घोषणा S3C2412_CPU_ID		0x32412000
#घोषणा S3C2412_CPU_MASK	0xFFFFF000

#घोषणा S3C6400_CPU_ID		0x36400000
#घोषणा S3C6410_CPU_ID		0x36410000
#घोषणा S3C64XX_CPU_MASK	0xFFFFF000

#घोषणा S5PV210_CPU_ID		0x43110000
#घोषणा S5PV210_CPU_MASK	0xFFFFF000

#घोषणा IS_SAMSUNG_CPU(name, id, mask)		\
अटल अंतरभूत पूर्णांक is_samsung_##name(व्योम)	\
अणु						\
	वापस ((samsung_cpu_id & mask) == (id & mask));	\
पूर्ण

IS_SAMSUNG_CPU(s3c2410, S3C2410_CPU_ID, S3C2410_CPU_MASK)
IS_SAMSUNG_CPU(s3c24xx, S3C24XX_CPU_ID, S3C24XX_CPU_MASK)
IS_SAMSUNG_CPU(s3c2412, S3C2412_CPU_ID, S3C2412_CPU_MASK)
IS_SAMSUNG_CPU(s3c6400, S3C6400_CPU_ID, S3C64XX_CPU_MASK)
IS_SAMSUNG_CPU(s3c6410, S3C6410_CPU_ID, S3C64XX_CPU_MASK)

#अगर defined(CONFIG_CPU_S3C2410) || defined(CONFIG_CPU_S3C2412) || \
    defined(CONFIG_CPU_S3C2416) || defined(CONFIG_CPU_S3C2440) || \
    defined(CONFIG_CPU_S3C2442) || defined(CONFIG_CPU_S3C244X) || \
    defined(CONFIG_CPU_S3C2443)
# define soc_is_s3c24xx()	is_samsung_s3c24xx()
# define soc_is_s3c2410()	is_samsung_s3c2410()
#अन्यथा
# define soc_is_s3c24xx()	0
# define soc_is_s3c2410()	0
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C2412)
# define soc_is_s3c2412()	is_samsung_s3c2412()
#अन्यथा
# define soc_is_s3c2412()	0
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C6400) || defined(CONFIG_CPU_S3C6410)
# define soc_is_s3c6400()	is_samsung_s3c6400()
# define soc_is_s3c6410()	is_samsung_s3c6410()
# define soc_is_s3c64xx()	(is_samsung_s3c6400() || is_samsung_s3c6410())
#अन्यथा
# define soc_is_s3c6400()	0
# define soc_is_s3c6410()	0
# define soc_is_s3c64xx()	0
#पूर्ण_अगर

#घोषणा IODESC_ENT(x) अणु (अचिन्हित दीर्घ)S3C24XX_VA_##x, __phys_to_pfn(S3C24XX_PA_##x), S3C24XX_SZ_##x, MT_DEVICE पूर्ण

#अगर_अघोषित KHZ
#घोषणा KHZ (1000)
#पूर्ण_अगर

#अगर_अघोषित MHZ
#घोषणा MHZ (1000*1000)
#पूर्ण_अगर

#घोषणा prपूर्णांक_mhz(m) ((m) / MHZ), (((m) / 1000) % 1000)

/* क्रमward declaration */
काष्ठा s3c24xx_uart_resources;
काष्ठा platक्रमm_device;
काष्ठा s3c2410_uartcfg;
काष्ठा map_desc;

/* per-cpu initialisation function table. */

काष्ठा cpu_table अणु
	अचिन्हित दीर्घ	idcode;
	अचिन्हित दीर्घ	idmask;
	व्योम		(*map_io)(व्योम);
	व्योम		(*init_uarts)(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no);
	व्योम		(*init_घड़ीs)(पूर्णांक xtal);
	पूर्णांक		(*init)(व्योम);
	स्थिर अक्षर	*name;
पूर्ण;

बाह्य व्योम s3c_init_cpu(अचिन्हित दीर्घ idcode,
			 काष्ठा cpu_table *cpus, अचिन्हित पूर्णांक cputab_size);

/* core initialisation functions */

बाह्य व्योम s3c24xx_init_io(काष्ठा map_desc *mach_desc, पूर्णांक size);

बाह्य व्योम s3c64xx_init_cpu(व्योम);

बाह्य व्योम s3c24xx_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no);

बाह्य व्योम s3c24xx_init_घड़ीs(पूर्णांक xtal);

बाह्य व्योम s3c24xx_init_uartdevs(अक्षर *name,
				  काष्ठा s3c24xx_uart_resources *res,
				  काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no);

बाह्य काष्ठा syscore_ops s3c2410_pm_syscore_ops;
बाह्य काष्ठा syscore_ops s3c2412_pm_syscore_ops;
बाह्य काष्ठा syscore_ops s3c2416_pm_syscore_ops;
बाह्य काष्ठा syscore_ops s3c244x_pm_syscore_ops;

बाह्य काष्ठा bus_type s3c6410_subsys;

#पूर्ण_अगर
