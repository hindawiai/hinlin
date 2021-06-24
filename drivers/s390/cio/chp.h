<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2007, 2010
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#अगर_अघोषित S390_CHP_H
#घोषणा S390_CHP_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/chpid.h>
#समावेश "chsc.h"
#समावेश "css.h"

#घोषणा CHP_STATUS_STANDBY		0
#घोषणा CHP_STATUS_CONFIGURED		1
#घोषणा CHP_STATUS_RESERVED		2
#घोषणा CHP_STATUS_NOT_RECOGNIZED	3

#घोषणा CHP_ONLINE 0
#घोषणा CHP_OFFLINE 1
#घोषणा CHP_VARY_ON 2
#घोषणा CHP_VARY_OFF 3
#घोषणा CHP_FCES_EVENT 4

काष्ठा chp_link अणु
	काष्ठा chp_id chpid;
	u32 fla_mask;
	u16 fla;
पूर्ण;

अटल अंतरभूत पूर्णांक chp_test_bit(u8 *biपंचांगap, पूर्णांक num)
अणु
	पूर्णांक byte = num >> 3;
	पूर्णांक mask = 128 >> (num & 7);

	वापस (biपंचांगap[byte] & mask) ? 1 : 0;
पूर्ण


काष्ठा channel_path अणु
	काष्ठा device dev;
	काष्ठा chp_id chpid;
	काष्ठा mutex lock; /* Serialize access to below members. */
	पूर्णांक state;
	काष्ठा channel_path_desc_fmt0 desc;
	काष्ठा channel_path_desc_fmt1 desc_fmt1;
	काष्ठा channel_path_desc_fmt3 desc_fmt3;
	/* Channel-measurement related stuff: */
	पूर्णांक cmg;
	पूर्णांक shared;
	काष्ठा cmg_अक्षरs cmg_अक्षरs;
पूर्ण;

/* Return channel_path काष्ठा क्रम given chpid. */
अटल अंतरभूत काष्ठा channel_path *chpid_to_chp(काष्ठा chp_id chpid)
अणु
	वापस css_by_id(chpid.cssid)->chps[chpid.id];
पूर्ण

पूर्णांक chp_get_status(काष्ठा chp_id chpid);
u8 chp_get_sch_opm(काष्ठा subchannel *sch);
पूर्णांक chp_is_रेजिस्टरed(काष्ठा chp_id chpid);
काष्ठा channel_path_desc_fmt0 *chp_get_chp_desc(काष्ठा chp_id chpid);
व्योम chp_हटाओ_cmg_attr(काष्ठा channel_path *chp);
पूर्णांक chp_add_cmg_attr(काष्ठा channel_path *chp);
पूर्णांक chp_update_desc(काष्ठा channel_path *chp);
पूर्णांक chp_new(काष्ठा chp_id chpid);
व्योम chp_cfg_schedule(काष्ठा chp_id chpid, पूर्णांक configure);
व्योम chp_cfg_cancel_deconfigure(काष्ठा chp_id chpid);
पूर्णांक chp_info_get_status(काष्ठा chp_id chpid);
पूर्णांक chp_ssd_get_mask(काष्ठा chsc_ssd_info *, काष्ठा chp_link *);
#पूर्ण_अगर /* S390_CHP_H */
