<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OF घड़ी helpers
 */

#अगर_अघोषित __LINUX_OF_CLK_H
#घोषणा __LINUX_OF_CLK_H

काष्ठा device_node;
काष्ठा of_device_id;

#अगर defined(CONFIG_COMMON_CLK) && defined(CONFIG_OF)

अचिन्हित पूर्णांक of_clk_get_parent_count(स्थिर काष्ठा device_node *np);
स्थिर अक्षर *of_clk_get_parent_name(स्थिर काष्ठा device_node *np, पूर्णांक index);
व्योम of_clk_init(स्थिर काष्ठा of_device_id *matches);

#अन्यथा /* !CONFIG_COMMON_CLK || !CONFIG_OF */

अटल अंतरभूत अचिन्हित पूर्णांक of_clk_get_parent_count(स्थिर काष्ठा device_node *np)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत स्थिर अक्षर *of_clk_get_parent_name(स्थिर काष्ठा device_node *np,
						 पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम of_clk_init(स्थिर काष्ठा of_device_id *matches) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_COMMON_CLK || !CONFIG_OF */

#पूर्ण_अगर /* __LINUX_OF_CLK_H */
