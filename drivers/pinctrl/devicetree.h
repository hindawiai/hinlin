<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Internal पूर्णांकerface to pinctrl device tree पूर्णांकegration
 *
 * Copyright (C) 2012 NVIDIA CORPORATION. All rights reserved.
 */

काष्ठा of_phandle_args;

#अगर_घोषित CONFIG_OF

व्योम pinctrl_dt_मुक्त_maps(काष्ठा pinctrl *p);
पूर्णांक pinctrl_dt_to_map(काष्ठा pinctrl *p, काष्ठा pinctrl_dev *pctldev);

पूर्णांक pinctrl_count_index_with_args(स्थिर काष्ठा device_node *np,
				  स्थिर अक्षर *list_name);

पूर्णांक pinctrl_parse_index_with_args(स्थिर काष्ठा device_node *np,
				  स्थिर अक्षर *list_name, पूर्णांक index,
				  काष्ठा of_phandle_args *out_args);

#अन्यथा

अटल अंतरभूत पूर्णांक pinctrl_dt_to_map(काष्ठा pinctrl *p,
				    काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pinctrl_dt_मुक्त_maps(काष्ठा pinctrl *p)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pinctrl_count_index_with_args(स्थिर काष्ठा device_node *np,
						स्थिर अक्षर *list_name)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक
pinctrl_parse_index_with_args(स्थिर काष्ठा device_node *np,
			      स्थिर अक्षर *list_name, पूर्णांक index,
			      काष्ठा of_phandle_args *out_args)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर
