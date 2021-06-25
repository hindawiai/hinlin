<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Bengt Jonsson <bengt.jonsson@stericsson.com> क्रम ST-Ericsson,
 *	   Jonas Aaberg <jonas.aberg@stericsson.com> क्रम ST-Ericsson
 */

#अगर_अघोषित DBX500_REGULATOR_H
#घोषणा DBX500_REGULATOR_H

#समावेश <linux/platक्रमm_device.h>

/**
 * काष्ठा dbx500_regulator_info - dbx500 regulator inक्रमmation
 * @desc: regulator description
 * @is_enabled: status of the regulator
 * @epod_id: id क्रम EPOD (घातer करोमुख्य)
 * @is_ramret: RAM retention चयन क्रम EPOD (घातer करोमुख्य)
 *
 */
काष्ठा dbx500_regulator_info अणु
	काष्ठा regulator_desc desc;
	bool is_enabled;
	u16 epod_id;
	bool is_ramret;
	bool exclude_from_घातer_state;
पूर्ण;

व्योम घातer_state_active_enable(व्योम);
पूर्णांक घातer_state_active_disable(व्योम);


#अगर_घोषित CONFIG_REGULATOR_DEBUG
पूर्णांक ux500_regulator_debug_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dbx500_regulator_info *regulator_info,
			       पूर्णांक num_regulators);

पूर्णांक ux500_regulator_debug_निकास(व्योम);
#अन्यथा

अटल अंतरभूत पूर्णांक ux500_regulator_debug_init(काष्ठा platक्रमm_device *pdev,
			     काष्ठा dbx500_regulator_info *regulator_info,
			     पूर्णांक num_regulators)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ux500_regulator_debug_निकास(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
