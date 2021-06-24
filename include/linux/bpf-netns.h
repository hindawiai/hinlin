<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BPF_NETNS_H
#घोषणा _BPF_NETNS_H

#समावेश <linux/mutex.h>
#समावेश <uapi/linux/bpf.h>

क्रमागत netns_bpf_attach_type अणु
	NETNS_BPF_INVALID = -1,
	NETNS_BPF_FLOW_DISSECTOR = 0,
	NETNS_BPF_SK_LOOKUP,
	MAX_NETNS_BPF_ATTACH_TYPE
पूर्ण;

अटल अंतरभूत क्रमागत netns_bpf_attach_type
to_netns_bpf_attach_type(क्रमागत bpf_attach_type attach_type)
अणु
	चयन (attach_type) अणु
	हाल BPF_FLOW_DISSECTOR:
		वापस NETNS_BPF_FLOW_DISSECTOR;
	हाल BPF_SK_LOOKUP:
		वापस NETNS_BPF_SK_LOOKUP;
	शेष:
		वापस NETNS_BPF_INVALID;
	पूर्ण
पूर्ण

/* Protects updates to netns_bpf */
बाह्य काष्ठा mutex netns_bpf_mutex;

जोड़ bpf_attr;
काष्ठा bpf_prog;

#अगर_घोषित CONFIG_NET
पूर्णांक netns_bpf_prog_query(स्थिर जोड़ bpf_attr *attr,
			 जोड़ bpf_attr __user *uattr);
पूर्णांक netns_bpf_prog_attach(स्थिर जोड़ bpf_attr *attr,
			  काष्ठा bpf_prog *prog);
पूर्णांक netns_bpf_prog_detach(स्थिर जोड़ bpf_attr *attr, क्रमागत bpf_prog_type ptype);
पूर्णांक netns_bpf_link_create(स्थिर जोड़ bpf_attr *attr,
			  काष्ठा bpf_prog *prog);
#अन्यथा
अटल अंतरभूत पूर्णांक netns_bpf_prog_query(स्थिर जोड़ bpf_attr *attr,
				       जोड़ bpf_attr __user *uattr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक netns_bpf_prog_attach(स्थिर जोड़ bpf_attr *attr,
					काष्ठा bpf_prog *prog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक netns_bpf_prog_detach(स्थिर जोड़ bpf_attr *attr,
					क्रमागत bpf_prog_type ptype)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक netns_bpf_link_create(स्थिर जोड़ bpf_attr *attr,
					काष्ठा bpf_prog *prog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _BPF_NETNS_H */
