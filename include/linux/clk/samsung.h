<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020 Krzysztof Kozlowski <krzk@kernel.org>
 */

#अगर_अघोषित __LINUX_CLK_SAMSUNG_H_
#घोषणा __LINUX_CLK_SAMSUNG_H_

#समावेश <linux/compiler_types.h>

काष्ठा device_node;

#अगर_घोषित CONFIG_S3C64XX_COMMON_CLK
व्योम s3c64xx_clk_init(काष्ठा device_node *np, अचिन्हित दीर्घ xtal_f,
		      अचिन्हित दीर्घ xusbxti_f, bool s3c6400,
		      व्योम __iomem *base);
#अन्यथा
अटल अंतरभूत व्योम s3c64xx_clk_init(काष्ठा device_node *np,
				    अचिन्हित दीर्घ xtal_f,
				    अचिन्हित दीर्घ xusbxti_f,
				    bool s3c6400, व्योम __iomem *base) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_S3C64XX_COMMON_CLK */

#अगर_घोषित CONFIG_S3C2410_COMMON_CLK
व्योम s3c2410_common_clk_init(काष्ठा device_node *np, अचिन्हित दीर्घ xti_f,
			     पूर्णांक current_soc,
			     व्योम __iomem *reg_base);
#अन्यथा
अटल अंतरभूत व्योम s3c2410_common_clk_init(काष्ठा device_node *np,
					   अचिन्हित दीर्घ xti_f,
					   पूर्णांक current_soc,
					   व्योम __iomem *reg_base) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_S3C2410_COMMON_CLK */

#अगर_घोषित CONFIG_S3C2412_COMMON_CLK
व्योम s3c2412_common_clk_init(काष्ठा device_node *np, अचिन्हित दीर्घ xti_f,
			     अचिन्हित दीर्घ ext_f, व्योम __iomem *reg_base);
#अन्यथा
अटल अंतरभूत व्योम s3c2412_common_clk_init(काष्ठा device_node *np,
					   अचिन्हित दीर्घ xti_f,
					   अचिन्हित दीर्घ ext_f,
					   व्योम __iomem *reg_base) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_S3C2412_COMMON_CLK */

#अगर_घोषित CONFIG_S3C2443_COMMON_CLK
व्योम s3c2443_common_clk_init(काष्ठा device_node *np, अचिन्हित दीर्घ xti_f,
			     पूर्णांक current_soc,
			     व्योम __iomem *reg_base);
#अन्यथा
अटल अंतरभूत व्योम s3c2443_common_clk_init(काष्ठा device_node *np,
					   अचिन्हित दीर्घ xti_f,
					   पूर्णांक current_soc,
					   व्योम __iomem *reg_base) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_S3C2443_COMMON_CLK */

#पूर्ण_अगर /* __LINUX_CLK_SAMSUNG_H_ */
