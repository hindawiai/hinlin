<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * System Control Driver
 *
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2012 Linaro Ltd.
 *
 * Author: Dong Aisheng <करोng.aisheng@linaro.org>
 */

#अगर_अघोषित __LINUX_MFD_SYSCON_H__
#घोषणा __LINUX_MFD_SYSCON_H__

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>

काष्ठा device_node;

#अगर_घोषित CONFIG_MFD_SYSCON
बाह्य काष्ठा regmap *device_node_to_regmap(काष्ठा device_node *np);
बाह्य काष्ठा regmap *syscon_node_to_regmap(काष्ठा device_node *np);
बाह्य काष्ठा regmap *syscon_regmap_lookup_by_compatible(स्थिर अक्षर *s);
बाह्य काष्ठा regmap *syscon_regmap_lookup_by_phandle(
					काष्ठा device_node *np,
					स्थिर अक्षर *property);
बाह्य काष्ठा regmap *syscon_regmap_lookup_by_phandle_args(
					काष्ठा device_node *np,
					स्थिर अक्षर *property,
					पूर्णांक arg_count,
					अचिन्हित पूर्णांक *out_args);
बाह्य काष्ठा regmap *syscon_regmap_lookup_by_phandle_optional(
					काष्ठा device_node *np,
					स्थिर अक्षर *property);
#अन्यथा
अटल अंतरभूत काष्ठा regmap *device_node_to_regmap(काष्ठा device_node *np)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा regmap *syscon_node_to_regmap(काष्ठा device_node *np)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा regmap *syscon_regmap_lookup_by_compatible(स्थिर अक्षर *s)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा regmap *syscon_regmap_lookup_by_phandle(
					काष्ठा device_node *np,
					स्थिर अक्षर *property)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा regmap *syscon_regmap_lookup_by_phandle_args(
					काष्ठा device_node *np,
					स्थिर अक्षर *property,
					पूर्णांक arg_count,
					अचिन्हित पूर्णांक *out_args)
अणु
	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा regmap *syscon_regmap_lookup_by_phandle_optional(
					काष्ठा device_node *np,
					स्थिर अक्षर *property)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_MFD_SYSCON_H__ */
