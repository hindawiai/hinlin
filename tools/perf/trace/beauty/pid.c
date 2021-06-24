<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1

माप_प्रकार syscall_arg__scnम_लिखो_pid(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	पूर्णांक pid = arg->val;
	काष्ठा trace *trace = arg->trace;
	माप_प्रकार prपूर्णांकed = scnम_लिखो(bf, size, "%d", pid);
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(trace->host, pid, pid);

	अगर (thपढ़ो != शून्य) अणु
		अगर (!thपढ़ो->comm_set)
			thपढ़ो__set_comm_from_proc(thपढ़ो);

		अगर (thपढ़ो->comm_set)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
					     " (%s)", thपढ़ो__comm_str(thपढ़ो));
		thपढ़ो__put(thपढ़ो);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण
