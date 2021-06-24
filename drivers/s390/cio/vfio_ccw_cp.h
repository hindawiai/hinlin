<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * channel program पूर्णांकerfaces
 *
 * Copyright IBM Corp. 2017
 *
 * Author(s): Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>
 *            Xiao Feng Ren <renxiaof@linux.vnet.ibm.com>
 */

#अगर_अघोषित _VFIO_CCW_CP_H_
#घोषणा _VFIO_CCW_CP_H_

#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/scsw.h>

#समावेश "orb.h"
#समावेश "vfio_ccw_trace.h"

/*
 * Max length क्रम ccw chain.
 * XXX: Limit to 256, need to check more?
 */
#घोषणा CCWCHAIN_LEN_MAX	256

/**
 * काष्ठा channel_program - manage inक्रमmation क्रम channel program
 * @ccwchain_list: list head of ccwchains
 * @orb: orb क्रम the currently processed ssch request
 * @mdev: the mediated device to perक्रमm page pinning/unpinning
 * @initialized: whether this instance is actually initialized
 *
 * @ccwchain_list is the head of a ccwchain list, that contents the
 * translated result of the guest channel program that poपूर्णांकed out by
 * the iova parameter when calling cp_init.
 */
काष्ठा channel_program अणु
	काष्ठा list_head ccwchain_list;
	जोड़ orb orb;
	काष्ठा device *mdev;
	bool initialized;
	काष्ठा ccw1 *guest_cp;
पूर्ण;

बाह्य पूर्णांक cp_init(काष्ठा channel_program *cp, काष्ठा device *mdev,
		   जोड़ orb *orb);
बाह्य व्योम cp_मुक्त(काष्ठा channel_program *cp);
बाह्य पूर्णांक cp_prefetch(काष्ठा channel_program *cp);
बाह्य जोड़ orb *cp_get_orb(काष्ठा channel_program *cp, u32 पूर्णांकparm, u8 lpm);
बाह्य व्योम cp_update_scsw(काष्ठा channel_program *cp, जोड़ scsw *scsw);
बाह्य bool cp_iova_pinned(काष्ठा channel_program *cp, u64 iova);

#पूर्ण_अगर
