<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tegra host1x Channel
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#अगर_अघोषित __HOST1X_CHANNEL_H
#घोषणा __HOST1X_CHANNEL_H

#समावेश <linux/पन.स>
#समावेश <linux/kref.h>

#समावेश "cdma.h"

काष्ठा host1x;
काष्ठा host1x_channel;

काष्ठा host1x_channel_list अणु
	काष्ठा host1x_channel *channels;
	अचिन्हित दीर्घ *allocated_channels;
पूर्ण;

काष्ठा host1x_channel अणु
	काष्ठा kref refcount;
	अचिन्हित पूर्णांक id;
	काष्ठा mutex submitlock;
	व्योम __iomem *regs;
	काष्ठा host1x_client *client;
	काष्ठा device *dev;
	काष्ठा host1x_cdma cdma;
पूर्ण;

/* channel list operations */
पूर्णांक host1x_channel_list_init(काष्ठा host1x_channel_list *chlist,
			     अचिन्हित पूर्णांक num_channels);
व्योम host1x_channel_list_मुक्त(काष्ठा host1x_channel_list *chlist);
काष्ठा host1x_channel *host1x_channel_get_index(काष्ठा host1x *host,
						अचिन्हित पूर्णांक index);

#पूर्ण_अगर
