<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 */
#अगर_अघोषित _SJA1105_DYNAMIC_CONFIG_H
#घोषणा _SJA1105_DYNAMIC_CONFIG_H

#समावेश "sja1105.h"
#समावेश <linux/packing.h>

/* Special index that can be used क्रम sja1105_dynamic_config_पढ़ो */
#घोषणा SJA1105_SEARCH		-1

काष्ठा sja1105_dyn_cmd;

काष्ठा sja1105_dynamic_table_ops अणु
	/* This वापसs माप_प्रकार just to keep same prototype as the
	 * अटल config ops, of which we are reusing some functions.
	 */
	माप_प्रकार (*entry_packing)(व्योम *buf, व्योम *entry_ptr, क्रमागत packing_op op);
	व्योम (*cmd_packing)(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
			    क्रमागत packing_op op);
	माप_प्रकार max_entry_count;
	माप_प्रकार packed_size;
	u64 addr;
	u8 access;
पूर्ण;

काष्ठा sja1105_mgmt_entry अणु
	u64 tsreg;
	u64 takets;
	u64 macaddr;
	u64 destports;
	u64 enfport;
	u64 index;
पूर्ण;

बाह्य स्थिर काष्ठा sja1105_dynamic_table_ops sja1105et_dyn_ops[BLK_IDX_MAX_DYN];
बाह्य स्थिर काष्ठा sja1105_dynamic_table_ops sja1105pqrs_dyn_ops[BLK_IDX_MAX_DYN];

#पूर्ण_अगर
