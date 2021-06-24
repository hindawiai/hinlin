<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BPF_UTIL__
#घोषणा __BPF_UTIL__

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <bpf/libbpf.h> /* libbpf_num_possible_cpus */

अटल अंतरभूत अचिन्हित पूर्णांक bpf_num_possible_cpus(व्योम)
अणु
	पूर्णांक possible_cpus = libbpf_num_possible_cpus();

	अगर (possible_cpus < 0) अणु
		म_लिखो("Failed to get # of possible cpus: '%s'!\n",
		       म_त्रुटि(-possible_cpus));
		निकास(1);
	पूर्ण
	वापस possible_cpus;
पूर्ण

#घोषणा __bpf_percpu_val_align	__attribute__((__aligned__(8)))

#घोषणा BPF_DECLARE_PERCPU(type, name)				\
	काष्ठा अणु type v; /* padding */ पूर्ण __bpf_percpu_val_align	\
		name[bpf_num_possible_cpus()]
#घोषणा bpf_percpu(name, cpu) name[(cpu)].v

#अगर_अघोषित ARRAY_SIZE
# define ARRAY_SIZE(x) (माप(x) / माप((x)[0]))
#पूर्ण_अगर

#अगर_अघोषित माप_field
#घोषणा माप_field(TYPE, MEMBER) माप((((TYPE *)0)->MEMBER))
#पूर्ण_अगर

#अगर_अघोषित दुरत्वend
#घोषणा दुरत्वend(TYPE, MEMBER) \
	(दुरत्व(TYPE, MEMBER)	+ माप_field(TYPE, MEMBER))
#पूर्ण_अगर

#पूर्ण_अगर /* __BPF_UTIL__ */
