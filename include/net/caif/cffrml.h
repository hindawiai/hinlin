<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CFFRML_H_
#घोषणा CFFRML_H_
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <linux/netdevice.h>

काष्ठा cffrml;
काष्ठा cflayer *cffrml_create(u16 phyid, bool use_fcs);
व्योम cffrml_मुक्त(काष्ठा cflayer *layr);
व्योम cffrml_set_uplayer(काष्ठा cflayer *this, काष्ठा cflayer *up);
व्योम cffrml_set_dnlayer(काष्ठा cflayer *this, काष्ठा cflayer *dn);
व्योम cffrml_put(काष्ठा cflayer *layr);
व्योम cffrml_hold(काष्ठा cflayer *layr);
पूर्णांक cffrml_refcnt_पढ़ो(काष्ठा cflayer *layr);

#पूर्ण_अगर /* CFFRML_H_ */
