<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _NF_CONNTRACK_LABELS_H
#घोषणा _NF_CONNTRACK_LABELS_H

#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>
#समावेश <linux/types.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <uapi/linux/netfilter/xt_connlabel.h>

#घोषणा NF_CT_LABELS_MAX_SIZE ((XT_CONNLABEL_MAXBIT + 1) / BITS_PER_BYTE)

काष्ठा nf_conn_labels अणु
	अचिन्हित दीर्घ bits[NF_CT_LABELS_MAX_SIZE / माप(दीर्घ)];
पूर्ण;

अटल अंतरभूत काष्ठा nf_conn_labels *nf_ct_labels_find(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	वापस nf_ct_ext_find(ct, NF_CT_EXT_LABELS);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा nf_conn_labels *nf_ct_labels_ext_add(काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	काष्ठा net *net = nf_ct_net(ct);

	अगर (net->ct.labels_used == 0)
		वापस शून्य;

	वापस nf_ct_ext_add(ct, NF_CT_EXT_LABELS, GFP_ATOMIC);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

पूर्णांक nf_connlabels_replace(काष्ठा nf_conn *ct,
			  स्थिर u32 *data, स्थिर u32 *mask, अचिन्हित पूर्णांक words);

#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
पूर्णांक nf_conntrack_labels_init(व्योम);
व्योम nf_conntrack_labels_fini(व्योम);
पूर्णांक nf_connlabels_get(काष्ठा net *net, अचिन्हित पूर्णांक bit);
व्योम nf_connlabels_put(काष्ठा net *net);
#अन्यथा
अटल अंतरभूत पूर्णांक nf_conntrack_labels_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nf_conntrack_labels_fini(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक nf_connlabels_get(काष्ठा net *net, अचिन्हित पूर्णांक bit) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम nf_connlabels_put(काष्ठा net *net) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _NF_CONNTRACK_LABELS_H */
