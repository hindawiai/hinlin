<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2007, 2012
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#अगर_अघोषित S390_IDSET_H
#घोषणा S390_IDSET_H

#समावेश <यंत्र/schid.h>

काष्ठा idset;

व्योम idset_मुक्त(काष्ठा idset *set);
व्योम idset_fill(काष्ठा idset *set);

काष्ठा idset *idset_sch_new(व्योम);
व्योम idset_sch_add(काष्ठा idset *set, काष्ठा subchannel_id id);
व्योम idset_sch_del(काष्ठा idset *set, काष्ठा subchannel_id id);
व्योम idset_sch_del_subseq(काष्ठा idset *set, काष्ठा subchannel_id schid);
पूर्णांक idset_sch_contains(काष्ठा idset *set, काष्ठा subchannel_id id);
पूर्णांक idset_is_empty(काष्ठा idset *set);
व्योम idset_add_set(काष्ठा idset *to, काष्ठा idset *from);

#पूर्ण_अगर /* S390_IDSET_H */
