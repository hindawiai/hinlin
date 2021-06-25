<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CFMUXL_H_
#घोषणा CFMUXL_H_
#समावेश <net/caअगर/caअगर_layer.h>

काष्ठा cfsrvl;
काष्ठा cffrml;

काष्ठा cflayer *cfmuxl_create(व्योम);
पूर्णांक cfmuxl_set_uplayer(काष्ठा cflayer *layr, काष्ठा cflayer *up, u8 linkid);
काष्ठा cflayer *cfmuxl_हटाओ_dnlayer(काष्ठा cflayer *layr, u8 phyid);
पूर्णांक cfmuxl_set_dnlayer(काष्ठा cflayer *layr, काष्ठा cflayer *up, u8 phyid);
काष्ठा cflayer *cfmuxl_हटाओ_uplayer(काष्ठा cflayer *layr, u8 linkid);

#पूर्ण_अगर				/* CFMUXL_H_ */
