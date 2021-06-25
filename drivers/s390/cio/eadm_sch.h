<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित EADM_SCH_H
#घोषणा EADM_SCH_H

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश "orb.h"

काष्ठा eadm_निजी अणु
	जोड़ orb orb;
	क्रमागत अणुEADM_IDLE, EADM_BUSY, EADM_NOT_OPERपूर्ण state;
	काष्ठा completion *completion;
	काष्ठा subchannel *sch;
	काष्ठा समयr_list समयr;
	काष्ठा list_head head;
पूर्ण __aligned(8);

#घोषणा get_eadm_निजी(n) ((काष्ठा eadm_निजी *)dev_get_drvdata(&n->dev))
#घोषणा set_eadm_निजी(n, p) (dev_set_drvdata(&n->dev, p))

#पूर्ण_अगर
