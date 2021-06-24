<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_SCHID_H
#घोषणा ASM_SCHID_H

#समावेश <linux/माला.स>
#समावेश <uapi/यंत्र/schid.h>

/* Helper function क्रम sane state of pre-allocated subchannel_id. */
अटल अंतरभूत व्योम
init_subchannel_id(काष्ठा subchannel_id *schid)
अणु
	स_रखो(schid, 0, माप(काष्ठा subchannel_id));
	schid->one = 1;
पूर्ण

अटल अंतरभूत पूर्णांक
schid_equal(काष्ठा subchannel_id *schid1, काष्ठा subchannel_id *schid2)
अणु
	वापस !स_भेद(schid1, schid2, माप(काष्ठा subchannel_id));
पूर्ण

#पूर्ण_अगर /* ASM_SCHID_H */
