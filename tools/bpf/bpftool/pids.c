<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2020 Facebook */
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>

#समावेश "main.h"
#समावेश "skeleton/pid_iter.h"

#अगर_घोषित BPFTOOL_WITHOUT_SKELETONS

पूर्णांक build_obj_refs_table(काष्ठा obj_refs_table *table, क्रमागत bpf_obj_type type)
अणु
	वापस -ENOTSUP;
पूर्ण
व्योम delete_obj_refs_table(काष्ठा obj_refs_table *table) अणुपूर्ण
व्योम emit_obj_refs_plain(काष्ठा obj_refs_table *table, __u32 id, स्थिर अक्षर *prefix) अणुपूर्ण
व्योम emit_obj_refs_json(काष्ठा obj_refs_table *table, __u32 id, json_ग_लिखोr_t *json_ग_लिखोr) अणुपूर्ण

#अन्यथा /* BPFTOOL_WITHOUT_SKELETONS */

#समावेश "pid_iter.skel.h"

अटल व्योम add_ref(काष्ठा obj_refs_table *table, काष्ठा pid_iter_entry *e)
अणु
	काष्ठा obj_refs *refs;
	काष्ठा obj_ref *ref;
	व्योम *पंचांगp;
	पूर्णांक i;

	hash_क्रम_each_possible(table->table, refs, node, e->id) अणु
		अगर (refs->id != e->id)
			जारी;

		क्रम (i = 0; i < refs->ref_cnt; i++) अणु
			अगर (refs->refs[i].pid == e->pid)
				वापस;
		पूर्ण

		पंचांगp = पुनः_स्मृति(refs->refs, (refs->ref_cnt + 1) * माप(*ref));
		अगर (!पंचांगp) अणु
			p_err("failed to re-alloc memory for ID %u, PID %d, COMM %s...",
			      e->id, e->pid, e->comm);
			वापस;
		पूर्ण
		refs->refs = पंचांगp;
		ref = &refs->refs[refs->ref_cnt];
		ref->pid = e->pid;
		स_नकल(ref->comm, e->comm, माप(ref->comm));
		refs->ref_cnt++;

		वापस;
	पूर्ण

	/* new ref */
	refs = सुस्मृति(1, माप(*refs));
	अगर (!refs) अणु
		p_err("failed to alloc memory for ID %u, PID %d, COMM %s...",
		      e->id, e->pid, e->comm);
		वापस;
	पूर्ण

	refs->id = e->id;
	refs->refs = दो_स्मृति(माप(*refs->refs));
	अगर (!refs->refs) अणु
		मुक्त(refs);
		p_err("failed to alloc memory for ID %u, PID %d, COMM %s...",
		      e->id, e->pid, e->comm);
		वापस;
	पूर्ण
	ref = &refs->refs[0];
	ref->pid = e->pid;
	स_नकल(ref->comm, e->comm, माप(ref->comm));
	refs->ref_cnt = 1;
	hash_add(table->table, &refs->node, e->id);
पूर्ण

अटल पूर्णांक __म_लिखो(2, 0)
libbpf_prपूर्णांक_none(__maybe_unused क्रमागत libbpf_prपूर्णांक_level level,
		  __maybe_unused स्थिर अक्षर *क्रमmat,
		  __maybe_unused बहु_सूची args)
अणु
	वापस 0;
पूर्ण

पूर्णांक build_obj_refs_table(काष्ठा obj_refs_table *table, क्रमागत bpf_obj_type type)
अणु
	काष्ठा pid_iter_entry *e;
	अक्षर buf[4096 / माप(*e) * माप(*e)];
	काष्ठा pid_iter_bpf *skel;
	पूर्णांक err, ret, fd = -1, i;
	libbpf_prपूर्णांक_fn_t शेष_prपूर्णांक;

	hash_init(table->table);
	set_max_rlimit();

	skel = pid_iter_bpf__खोलो();
	अगर (!skel) अणु
		p_err("failed to open PID iterator skeleton");
		वापस -1;
	पूर्ण

	skel->rodata->obj_type = type;

	/* we करोn't want output polluted with libbpf errors अगर bpf_iter is not
	 * supported
	 */
	शेष_prपूर्णांक = libbpf_set_prपूर्णांक(libbpf_prपूर्णांक_none);
	err = pid_iter_bpf__load(skel);
	libbpf_set_prपूर्णांक(शेष_prपूर्णांक);
	अगर (err) अणु
		/* too bad, kernel करोesn't support BPF iterators yet */
		err = 0;
		जाओ out;
	पूर्ण
	err = pid_iter_bpf__attach(skel);
	अगर (err) अणु
		/* अगर we loaded above successfully, attach has to succeed */
		p_err("failed to attach PID iterator: %d", err);
		जाओ out;
	पूर्ण

	fd = bpf_iter_create(bpf_link__fd(skel->links.iter));
	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		p_err("failed to create PID iterator session: %d", err);
		जाओ out;
	पूर्ण

	जबतक (true) अणु
		ret = पढ़ो(fd, buf, माप(buf));
		अगर (ret < 0) अणु
			अगर (त्रुटि_सं == EAGAIN)
				जारी;
			err = -त्रुटि_सं;
			p_err("failed to read PID iterator output: %d", err);
			जाओ out;
		पूर्ण
		अगर (ret == 0)
			अवरोध;
		अगर (ret % माप(*e)) अणु
			err = -EINVAL;
			p_err("invalid PID iterator output format");
			जाओ out;
		पूर्ण
		ret /= माप(*e);

		e = (व्योम *)buf;
		क्रम (i = 0; i < ret; i++, e++) अणु
			add_ref(table, e);
		पूर्ण
	पूर्ण
	err = 0;
out:
	अगर (fd >= 0)
		बंद(fd);
	pid_iter_bpf__destroy(skel);
	वापस err;
पूर्ण

व्योम delete_obj_refs_table(काष्ठा obj_refs_table *table)
अणु
	काष्ठा obj_refs *refs;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित पूर्णांक bkt;

	hash_क्रम_each_safe(table->table, bkt, पंचांगp, refs, node) अणु
		hash_del(&refs->node);
		मुक्त(refs->refs);
		मुक्त(refs);
	पूर्ण
पूर्ण

व्योम emit_obj_refs_json(काष्ठा obj_refs_table *table, __u32 id,
			json_ग_लिखोr_t *json_ग_लिखोr)
अणु
	काष्ठा obj_refs *refs;
	काष्ठा obj_ref *ref;
	पूर्णांक i;

	अगर (hash_empty(table->table))
		वापस;

	hash_क्रम_each_possible(table->table, refs, node, id) अणु
		अगर (refs->id != id)
			जारी;
		अगर (refs->ref_cnt == 0)
			अवरोध;

		jsonw_name(json_ग_लिखोr, "pids");
		jsonw_start_array(json_ग_लिखोr);
		क्रम (i = 0; i < refs->ref_cnt; i++) अणु
			ref = &refs->refs[i];
			jsonw_start_object(json_ग_लिखोr);
			jsonw_पूर्णांक_field(json_ग_लिखोr, "pid", ref->pid);
			jsonw_string_field(json_ग_लिखोr, "comm", ref->comm);
			jsonw_end_object(json_ग_लिखोr);
		पूर्ण
		jsonw_end_array(json_ग_लिखोr);
		अवरोध;
	पूर्ण
पूर्ण

व्योम emit_obj_refs_plain(काष्ठा obj_refs_table *table, __u32 id, स्थिर अक्षर *prefix)
अणु
	काष्ठा obj_refs *refs;
	काष्ठा obj_ref *ref;
	पूर्णांक i;

	अगर (hash_empty(table->table))
		वापस;

	hash_क्रम_each_possible(table->table, refs, node, id) अणु
		अगर (refs->id != id)
			जारी;
		अगर (refs->ref_cnt == 0)
			अवरोध;

		म_लिखो("%s", prefix);
		क्रम (i = 0; i < refs->ref_cnt; i++) अणु
			ref = &refs->refs[i];
			म_लिखो("%s%s(%d)", i == 0 ? "" : ", ", ref->comm, ref->pid);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण


#पूर्ण_अगर
