<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2016-2018, The Linux Foundation. All rights reserved. */

#अगर_अघोषित __QCOM_COMMAND_DB_H__
#घोषणा __QCOM_COMMAND_DB_H__

#समावेश <linux/err.h>

क्रमागत cmd_db_hw_type अणु
	CMD_DB_HW_INVALID = 0,
	CMD_DB_HW_MIN     = 3,
	CMD_DB_HW_ARC     = CMD_DB_HW_MIN,
	CMD_DB_HW_VRM     = 4,
	CMD_DB_HW_BCM     = 5,
	CMD_DB_HW_MAX     = CMD_DB_HW_BCM,
	CMD_DB_HW_ALL     = 0xff,
पूर्ण;

#अगर IS_ENABLED(CONFIG_QCOM_COMMAND_DB)
u32 cmd_db_पढ़ो_addr(स्थिर अक्षर *resource_id);

स्थिर व्योम *cmd_db_पढ़ो_aux_data(स्थिर अक्षर *resource_id, माप_प्रकार *len);

क्रमागत cmd_db_hw_type cmd_db_पढ़ो_slave_id(स्थिर अक्षर *resource_id);

पूर्णांक cmd_db_पढ़ोy(व्योम);
#अन्यथा
अटल अंतरभूत u32 cmd_db_पढ़ो_addr(स्थिर अक्षर *resource_id)
अणु वापस 0; पूर्ण

अटल अंतरभूत स्थिर व्योम *cmd_db_पढ़ो_aux_data(स्थिर अक्षर *resource_id, माप_प्रकार *len)
अणु वापस ERR_PTR(-ENODEV); पूर्ण

अटल अंतरभूत क्रमागत cmd_db_hw_type cmd_db_पढ़ो_slave_id(स्थिर अक्षर *resource_id)
अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत पूर्णांक cmd_db_पढ़ोy(व्योम)
अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर /* CONFIG_QCOM_COMMAND_DB */
#पूर्ण_अगर /* __QCOM_COMMAND_DB_H__ */
