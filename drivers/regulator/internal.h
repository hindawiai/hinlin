<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * पूर्णांकernal.h  --  Voltage/Current Regulator framework पूर्णांकernal code
 *
 * Copyright 2007, 2008 Wolfson Microelectronics PLC.
 * Copyright 2008 SlimLogic Ltd.
 *
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 */

#अगर_अघोषित __REGULATOR_INTERNAL_H
#घोषणा __REGULATOR_INTERNAL_H

#समावेश <linux/suspend.h>

#घोषणा REGULATOR_STATES_NUM	(PM_SUSPEND_MAX + 1)

काष्ठा regulator_voltage अणु
	पूर्णांक min_uV;
	पूर्णांक max_uV;
पूर्ण;

/*
 * काष्ठा regulator
 *
 * One क्रम each consumer device.
 * @voltage - a voltage array क्रम each state of runसमय, i.e.:
 *            PM_SUSPEND_ON
 *            PM_SUSPEND_TO_IDLE
 *            PM_SUSPEND_STANDBY
 *            PM_SUSPEND_MEM
 *            PM_SUSPEND_MAX
 */
काष्ठा regulator अणु
	काष्ठा device *dev;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक always_on:1;
	अचिन्हित पूर्णांक bypass:1;
	अचिन्हित पूर्णांक device_link:1;
	पूर्णांक uA_load;
	अचिन्हित पूर्णांक enable_count;
	अचिन्हित पूर्णांक deferred_disables;
	काष्ठा regulator_voltage voltage[REGULATOR_STATES_NUM];
	स्थिर अक्षर *supply_name;
	काष्ठा device_attribute dev_attr;
	काष्ठा regulator_dev *rdev;
	काष्ठा dentry *debugfs;
पूर्ण;

बाह्य काष्ठा class regulator_class;

अटल अंतरभूत काष्ठा regulator_dev *dev_to_rdev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा regulator_dev, dev);
पूर्ण

#अगर_घोषित CONFIG_OF
काष्ठा regulator_dev *of_find_regulator_by_node(काष्ठा device_node *np);
काष्ठा regulator_init_data *regulator_of_get_init_data(काष्ठा device *dev,
			         स्थिर काष्ठा regulator_desc *desc,
				 काष्ठा regulator_config *config,
				 काष्ठा device_node **node);

काष्ठा regulator_dev *of_parse_coupled_regulator(काष्ठा regulator_dev *rdev,
						 पूर्णांक index);

पूर्णांक of_get_n_coupled(काष्ठा regulator_dev *rdev);

bool of_check_coupling_data(काष्ठा regulator_dev *rdev);

#अन्यथा
अटल अंतरभूत काष्ठा regulator_dev *
of_find_regulator_by_node(काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा regulator_init_data *
regulator_of_get_init_data(काष्ठा device *dev,
			   स्थिर काष्ठा regulator_desc *desc,
			   काष्ठा regulator_config *config,
			   काष्ठा device_node **node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा regulator_dev *
of_parse_coupled_regulator(काष्ठा regulator_dev *rdev,
			   पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_get_n_coupled(काष्ठा regulator_dev *rdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool of_check_coupling_data(काष्ठा regulator_dev *rdev)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर
क्रमागत regulator_get_type अणु
	NORMAL_GET,
	EXCLUSIVE_GET,
	OPTIONAL_GET,
	MAX_GET_TYPE
पूर्ण;

काष्ठा regulator *_regulator_get(काष्ठा device *dev, स्थिर अक्षर *id,
				 क्रमागत regulator_get_type get_type);
#पूर्ण_अगर
