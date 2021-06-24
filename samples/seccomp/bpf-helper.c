<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Seccomp BPF helper functions
 *
 * Copyright (c) 2012 The Chromium OS Authors <chromium-os-dev@chromium.org>
 * Author: Will Drewry <wad@chromium.org>
 *
 * The code may be used by anyone क्रम any purpose,
 * and can serve as a starting poपूर्णांक क्रम developing
 * applications using prctl(PR_ATTACH_SECCOMP_FILTER).
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "bpf-helper.h"

पूर्णांक bpf_resolve_jumps(काष्ठा bpf_labels *labels,
		      काष्ठा sock_filter *filter, माप_प्रकार count)
अणु
	माप_प्रकार i;

	अगर (count < 1 || count > BPF_MAXINSNS)
		वापस -1;
	/*
	* Walk it once, backwards, to build the label table and करो fixups.
	* Since backward jumps are disallowed by BPF, this is easy.
	*/
	क्रम (i = 0; i < count; ++i) अणु
		माप_प्रकार offset = count - i - 1;
		काष्ठा sock_filter *instr = &filter[offset];
		अगर (instr->code != (BPF_JMP+BPF_JA))
			जारी;
		चयन ((instr->jt<<8)|instr->jf) अणु
		हाल (JUMP_JT<<8)|JUMP_JF:
			अगर (labels->labels[instr->k].location == 0xffffffff) अणु
				ख_लिखो(मानक_त्रुटि, "Unresolved label: '%s'\n",
					labels->labels[instr->k].label);
				वापस 1;
			पूर्ण
			instr->k = labels->labels[instr->k].location -
				    (offset + 1);
			instr->jt = 0;
			instr->jf = 0;
			जारी;
		हाल (LABEL_JT<<8)|LABEL_JF:
			अगर (labels->labels[instr->k].location != 0xffffffff) अणु
				ख_लिखो(मानक_त्रुटि, "Duplicate label use: '%s'\n",
					labels->labels[instr->k].label);
				वापस 1;
			पूर्ण
			labels->labels[instr->k].location = offset;
			instr->k = 0; /* fall through */
			instr->jt = 0;
			instr->jf = 0;
			जारी;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Simple lookup table क्रम labels. */
__u32 seccomp_bpf_label(काष्ठा bpf_labels *labels, स्थिर अक्षर *label)
अणु
	काष्ठा __bpf_label *begin = labels->labels, *end;
	पूर्णांक id;

	अगर (labels->count == BPF_LABELS_MAX) अणु
		ख_लिखो(मानक_त्रुटि, "Too many labels\n");
		निकास(1);
	पूर्ण
	अगर (labels->count == 0) अणु
		begin->label = label;
		begin->location = 0xffffffff;
		labels->count++;
		वापस 0;
	पूर्ण
	end = begin + labels->count;
	क्रम (id = 0; begin < end; ++begin, ++id) अणु
		अगर (!म_भेद(label, begin->label))
			वापस id;
	पूर्ण
	begin->label = label;
	begin->location = 0xffffffff;
	labels->count++;
	वापस id;
पूर्ण

व्योम seccomp_bpf_prपूर्णांक(काष्ठा sock_filter *filter, माप_प्रकार count)
अणु
	काष्ठा sock_filter *end = filter + count;
	क्रम ( ; filter < end; ++filter)
		म_लिखो("{ code=%u,jt=%u,jf=%u,k=%u },\n",
			filter->code, filter->jt, filter->jf, filter->k);
पूर्ण
