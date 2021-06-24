<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CFSRVL_H_
#घोषणा CFSRVL_H_
#समावेश <linux/list.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/kref.h>
#समावेश <linux/rculist.h>

काष्ठा cfsrvl अणु
	काष्ठा cflayer layer;
	bool खोलो;
	bool phy_flow_on;
	bool modem_flow_on;
	bool supports_flowctrl;
	व्योम (*release)(काष्ठा cflayer *layer);
	काष्ठा dev_info dev_info;
	व्योम (*hold)(काष्ठा cflayer *lyr);
	व्योम (*put)(काष्ठा cflayer *lyr);
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा cflayer *cfvei_create(u8 linkid, काष्ठा dev_info *dev_info);
काष्ठा cflayer *cfdgml_create(u8 linkid, काष्ठा dev_info *dev_info);
काष्ठा cflayer *cfutill_create(u8 linkid, काष्ठा dev_info *dev_info);
काष्ठा cflayer *cfvidl_create(u8 linkid, काष्ठा dev_info *dev_info);
काष्ठा cflayer *cfrfml_create(u8 linkid, काष्ठा dev_info *dev_info,
				पूर्णांक mtu_size);
काष्ठा cflayer *cfdbgl_create(u8 linkid, काष्ठा dev_info *dev_info);

व्योम cfsrvl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
		     पूर्णांक phyid);

bool cfsrvl_phyid_match(काष्ठा cflayer *layer, पूर्णांक phyid);

व्योम cfsrvl_init(काष्ठा cfsrvl *service,
			u8 channel_id,
			काष्ठा dev_info *dev_info,
			bool supports_flowctrl);
bool cfsrvl_पढ़ोy(काष्ठा cfsrvl *service, पूर्णांक *err);
u8 cfsrvl_getphyid(काष्ठा cflayer *layer);

अटल अंतरभूत व्योम cfsrvl_get(काष्ठा cflayer *layr)
अणु
	काष्ठा cfsrvl *s = container_of(layr, काष्ठा cfsrvl, layer);
	अगर (layr == शून्य || layr->up == शून्य || s->hold == शून्य)
		वापस;

	s->hold(layr->up);
पूर्ण

अटल अंतरभूत व्योम cfsrvl_put(काष्ठा cflayer *layr)
अणु
	काष्ठा cfsrvl *s = container_of(layr, काष्ठा cfsrvl, layer);
	अगर (layr == शून्य || layr->up == शून्य || s->hold == शून्य)
		वापस;

	s->put(layr->up);
पूर्ण
#पूर्ण_अगर				/* CFSRVL_H_ */
