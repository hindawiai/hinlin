<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007, 2012
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश "idset.h"
#समावेश "css.h"

काष्ठा idset अणु
	पूर्णांक num_ssid;
	पूर्णांक num_id;
	अचिन्हित दीर्घ biपंचांगap[];
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ biपंचांगap_size(पूर्णांक num_ssid, पूर्णांक num_id)
अणु
	वापस BITS_TO_LONGS(num_ssid * num_id) * माप(अचिन्हित दीर्घ);
पूर्ण

अटल काष्ठा idset *idset_new(पूर्णांक num_ssid, पूर्णांक num_id)
अणु
	काष्ठा idset *set;

	set = vदो_स्मृति(माप(काष्ठा idset) + biपंचांगap_size(num_ssid, num_id));
	अगर (set) अणु
		set->num_ssid = num_ssid;
		set->num_id = num_id;
		स_रखो(set->biपंचांगap, 0, biपंचांगap_size(num_ssid, num_id));
	पूर्ण
	वापस set;
पूर्ण

व्योम idset_मुक्त(काष्ठा idset *set)
अणु
	vमुक्त(set);
पूर्ण

व्योम idset_fill(काष्ठा idset *set)
अणु
	स_रखो(set->biपंचांगap, 0xff, biपंचांगap_size(set->num_ssid, set->num_id));
पूर्ण

अटल अंतरभूत व्योम idset_add(काष्ठा idset *set, पूर्णांक ssid, पूर्णांक id)
अणु
	set_bit(ssid * set->num_id + id, set->biपंचांगap);
पूर्ण

अटल अंतरभूत व्योम idset_del(काष्ठा idset *set, पूर्णांक ssid, पूर्णांक id)
अणु
	clear_bit(ssid * set->num_id + id, set->biपंचांगap);
पूर्ण

अटल अंतरभूत पूर्णांक idset_contains(काष्ठा idset *set, पूर्णांक ssid, पूर्णांक id)
अणु
	वापस test_bit(ssid * set->num_id + id, set->biपंचांगap);
पूर्ण

काष्ठा idset *idset_sch_new(व्योम)
अणु
	वापस idset_new(max_ssid + 1, __MAX_SUBCHANNEL + 1);
पूर्ण

व्योम idset_sch_add(काष्ठा idset *set, काष्ठा subchannel_id schid)
अणु
	idset_add(set, schid.ssid, schid.sch_no);
पूर्ण

व्योम idset_sch_del(काष्ठा idset *set, काष्ठा subchannel_id schid)
अणु
	idset_del(set, schid.ssid, schid.sch_no);
पूर्ण

/* Clear ids starting from @schid up to end of subchannel set. */
व्योम idset_sch_del_subseq(काष्ठा idset *set, काष्ठा subchannel_id schid)
अणु
	पूर्णांक pos = schid.ssid * set->num_id + schid.sch_no;

	biपंचांगap_clear(set->biपंचांगap, pos, set->num_id - schid.sch_no);
पूर्ण

पूर्णांक idset_sch_contains(काष्ठा idset *set, काष्ठा subchannel_id schid)
अणु
	वापस idset_contains(set, schid.ssid, schid.sch_no);
पूर्ण

पूर्णांक idset_is_empty(काष्ठा idset *set)
अणु
	वापस biपंचांगap_empty(set->biपंचांगap, set->num_ssid * set->num_id);
पूर्ण

व्योम idset_add_set(काष्ठा idset *to, काष्ठा idset *from)
अणु
	पूर्णांक len = min(to->num_ssid * to->num_id, from->num_ssid * from->num_id);

	biपंचांगap_or(to->biपंचांगap, to->biपंचांगap, from->biपंचांगap, len);
पूर्ण
