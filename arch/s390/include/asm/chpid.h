<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2007, 2012
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */
#अगर_अघोषित _ASM_S390_CHPID_H
#घोषणा _ASM_S390_CHPID_H

#समावेश <uapi/यंत्र/chpid.h>
#समावेश <यंत्र/cपन.स>

काष्ठा channel_path_desc_fmt0 अणु
	u8 flags;
	u8 lsn;
	u8 desc;
	u8 chpid;
	u8 swla;
	u8 zeroes;
	u8 chla;
	u8 chpp;
पूर्ण __packed;

अटल अंतरभूत व्योम chp_id_init(काष्ठा chp_id *chpid)
अणु
	स_रखो(chpid, 0, माप(काष्ठा chp_id));
पूर्ण

अटल अंतरभूत पूर्णांक chp_id_is_equal(काष्ठा chp_id *a, काष्ठा chp_id *b)
अणु
	वापस (a->id == b->id) && (a->cssid == b->cssid);
पूर्ण

अटल अंतरभूत व्योम chp_id_next(काष्ठा chp_id *chpid)
अणु
	अगर (chpid->id < __MAX_CHPID)
		chpid->id++;
	अन्यथा अणु
		chpid->id = 0;
		chpid->cssid++;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक chp_id_is_valid(काष्ठा chp_id *chpid)
अणु
	वापस (chpid->cssid <= __MAX_CSSID);
पूर्ण


#घोषणा chp_id_क्रम_each(c) \
	क्रम (chp_id_init(c); chp_id_is_valid(c); chp_id_next(c))
#पूर्ण_अगर /* _ASM_S390_CHPID_H */
