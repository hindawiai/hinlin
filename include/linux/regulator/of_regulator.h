<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OpenFirmware regulator support routines
 *
 */

#अगर_अघोषित __LINUX_OF_REG_H
#घोषणा __LINUX_OF_REG_H

काष्ठा regulator_desc;

काष्ठा of_regulator_match अणु
	स्थिर अक्षर *name;
	व्योम *driver_data;
	काष्ठा regulator_init_data *init_data;
	काष्ठा device_node *of_node;
	स्थिर काष्ठा regulator_desc *desc;
पूर्ण;

#अगर defined(CONFIG_OF)
बाह्य काष्ठा regulator_init_data
	*of_get_regulator_init_data(काष्ठा device *dev,
				    काष्ठा device_node *node,
				    स्थिर काष्ठा regulator_desc *desc);
बाह्य पूर्णांक of_regulator_match(काष्ठा device *dev, काष्ठा device_node *node,
			      काष्ठा of_regulator_match *matches,
			      अचिन्हित पूर्णांक num_matches);
#अन्यथा
अटल अंतरभूत काष्ठा regulator_init_data
	*of_get_regulator_init_data(काष्ठा device *dev,
				    काष्ठा device_node *node,
				    स्थिर काष्ठा regulator_desc *desc)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_regulator_match(काष्ठा device *dev,
				     काष्ठा device_node *node,
				     काष्ठा of_regulator_match *matches,
				     अचिन्हित पूर्णांक num_matches)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

#पूर्ण_अगर /* __LINUX_OF_REG_H */
