<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_ZONES_H
#घोषणा _NF_CONNTRACK_ZONES_H

#समावेश <linux/netfilter/nf_conntrack_zones_common.h>
#समावेश <net/netfilter/nf_conntrack.h>

अटल अंतरभूत स्थिर काष्ठा nf_conntrack_zone *
nf_ct_zone(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	वापस &ct->zone;
#अन्यथा
	वापस &nf_ct_zone_dflt;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत स्थिर काष्ठा nf_conntrack_zone *
nf_ct_zone_init(काष्ठा nf_conntrack_zone *zone, u16 id, u8 dir, u8 flags)
अणु
	zone->id = id;
	zone->flags = flags;
	zone->dir = dir;

	वापस zone;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा nf_conntrack_zone *
nf_ct_zone_पंचांगpl(स्थिर काष्ठा nf_conn *पंचांगpl, स्थिर काष्ठा sk_buff *skb,
		काष्ठा nf_conntrack_zone *पंचांगp)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	अगर (!पंचांगpl)
		वापस &nf_ct_zone_dflt;

	अगर (पंचांगpl->zone.flags & NF_CT_FLAG_MARK)
		वापस nf_ct_zone_init(पंचांगp, skb->mark, पंचांगpl->zone.dir, 0);
#पूर्ण_अगर
	वापस nf_ct_zone(पंचांगpl);
पूर्ण

अटल अंतरभूत व्योम nf_ct_zone_add(काष्ठा nf_conn *ct,
				  स्थिर काष्ठा nf_conntrack_zone *zone)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	ct->zone = *zone;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool nf_ct_zone_matches_dir(स्थिर काष्ठा nf_conntrack_zone *zone,
					  क्रमागत ip_conntrack_dir dir)
अणु
	वापस zone->dir & (1 << dir);
पूर्ण

अटल अंतरभूत u16 nf_ct_zone_id(स्थिर काष्ठा nf_conntrack_zone *zone,
				क्रमागत ip_conntrack_dir dir)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	वापस nf_ct_zone_matches_dir(zone, dir) ?
	       zone->id : NF_CT_DEFAULT_ZONE_ID;
#अन्यथा
	वापस NF_CT_DEFAULT_ZONE_ID;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool nf_ct_zone_equal(स्थिर काष्ठा nf_conn *a,
				    स्थिर काष्ठा nf_conntrack_zone *b,
				    क्रमागत ip_conntrack_dir dir)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	वापस nf_ct_zone_id(nf_ct_zone(a), dir) ==
	       nf_ct_zone_id(b, dir);
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool nf_ct_zone_equal_any(स्थिर काष्ठा nf_conn *a,
					स्थिर काष्ठा nf_conntrack_zone *b)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	वापस nf_ct_zone(a)->id == b->id;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _NF_CONNTRACK_ZONES_H */
