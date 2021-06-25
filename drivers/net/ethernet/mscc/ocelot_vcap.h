<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/* Microsemi Ocelot Switch driver
 * Copyright (c) 2019 Microsemi Corporation
 */

#अगर_अघोषित _MSCC_OCELOT_VCAP_H_
#घोषणा _MSCC_OCELOT_VCAP_H_

#समावेश "ocelot.h"
#समावेश <soc/mscc/ocelot_vcap.h>
#समावेश <net/flow_offload.h>

#घोषणा OCELOT_POLICER_DISCARD 0x17f

पूर्णांक ocelot_vcap_filter_stats_update(काष्ठा ocelot *ocelot,
				    काष्ठा ocelot_vcap_filter *rule);

व्योम ocelot_detect_vcap_स्थिरants(काष्ठा ocelot *ocelot);
पूर्णांक ocelot_vcap_init(काष्ठा ocelot *ocelot);

पूर्णांक ocelot_setup_tc_cls_flower(काष्ठा ocelot_port_निजी *priv,
			       काष्ठा flow_cls_offload *f,
			       bool ingress);

#पूर्ण_अगर /* _MSCC_OCELOT_VCAP_H_ */
