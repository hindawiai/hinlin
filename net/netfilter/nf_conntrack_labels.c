<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * test/set flag bits stored in conntrack extension area.
 *
 * (C) 2013 Astaro GmbH & Co KG
 */

#समावेश <linux/export.h>
#समावेश <linux/types.h>

#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>

अटल DEFINE_SPINLOCK(nf_connlabels_lock);

अटल पूर्णांक replace_u32(u32 *address, u32 mask, u32 new)
अणु
	u32 old, पंचांगp;

	करो अणु
		old = *address;
		पंचांगp = (old & mask) ^ new;
		अगर (old == पंचांगp)
			वापस 0;
	पूर्ण जबतक (cmpxchg(address, old, पंचांगp) != old);

	वापस 1;
पूर्ण

पूर्णांक nf_connlabels_replace(काष्ठा nf_conn *ct,
			  स्थिर u32 *data,
			  स्थिर u32 *mask, अचिन्हित पूर्णांक words32)
अणु
	काष्ठा nf_conn_labels *labels;
	अचिन्हित पूर्णांक size, i;
	पूर्णांक changed = 0;
	u32 *dst;

	labels = nf_ct_labels_find(ct);
	अगर (!labels)
		वापस -ENOSPC;

	size = माप(labels->bits);
	अगर (size < (words32 * माप(u32)))
		words32 = size / माप(u32);

	dst = (u32 *) labels->bits;
	क्रम (i = 0; i < words32; i++)
		changed |= replace_u32(&dst[i], mask ? ~mask[i] : 0, data[i]);

	size /= माप(u32);
	क्रम (i = words32; i < size; i++) /* pad */
		replace_u32(&dst[i], 0, 0);

	अगर (changed)
		nf_conntrack_event_cache(IPCT_LABEL, ct);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_connlabels_replace);

पूर्णांक nf_connlabels_get(काष्ठा net *net, अचिन्हित पूर्णांक bits)
अणु
	अगर (BIT_WORD(bits) >= NF_CT_LABELS_MAX_SIZE / माप(दीर्घ))
		वापस -दुस्फल;

	spin_lock(&nf_connlabels_lock);
	net->ct.labels_used++;
	spin_unlock(&nf_connlabels_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_connlabels_get);

व्योम nf_connlabels_put(काष्ठा net *net)
अणु
	spin_lock(&nf_connlabels_lock);
	net->ct.labels_used--;
	spin_unlock(&nf_connlabels_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_connlabels_put);

अटल स्थिर काष्ठा nf_ct_ext_type labels_extend = अणु
	.len    = माप(काष्ठा nf_conn_labels),
	.align  = __alignof__(काष्ठा nf_conn_labels),
	.id     = NF_CT_EXT_LABELS,
पूर्ण;

पूर्णांक nf_conntrack_labels_init(व्योम)
अणु
	BUILD_BUG_ON(NF_CT_LABELS_MAX_SIZE / माप(दीर्घ) >= U8_MAX);

	वापस nf_ct_extend_रेजिस्टर(&labels_extend);
पूर्ण

व्योम nf_conntrack_labels_fini(व्योम)
अणु
	nf_ct_extend_unरेजिस्टर(&labels_extend);
पूर्ण
