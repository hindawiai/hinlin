<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BPF_LIRC_H
#घोषणा _BPF_LIRC_H

#समावेश <uapi/linux/bpf.h>

#अगर_घोषित CONFIG_BPF_LIRC_MODE2
पूर्णांक lirc_prog_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog);
पूर्णांक lirc_prog_detach(स्थिर जोड़ bpf_attr *attr);
पूर्णांक lirc_prog_query(स्थिर जोड़ bpf_attr *attr, जोड़ bpf_attr __user *uattr);
#अन्यथा
अटल अंतरभूत पूर्णांक lirc_prog_attach(स्थिर जोड़ bpf_attr *attr,
				   काष्ठा bpf_prog *prog)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक lirc_prog_detach(स्थिर जोड़ bpf_attr *attr)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक lirc_prog_query(स्थिर जोड़ bpf_attr *attr,
				  जोड़ bpf_attr __user *uattr)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _BPF_LIRC_H */
