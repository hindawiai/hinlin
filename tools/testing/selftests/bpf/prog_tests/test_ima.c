<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright (C) 2020 Google LLC.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sys/रुको.h>
#समावेश <test_progs.h>
#समावेश <linux/ring_buffer.h>

#समावेश "ima.skel.h"

अटल पूर्णांक run_measured_process(स्थिर अक्षर *measured_dir, u32 *monitored_pid)
अणु
	पूर्णांक child_pid, child_status;

	child_pid = विभाजन();
	अगर (child_pid == 0) अणु
		*monitored_pid = getpid();
		execlp("./ima_setup.sh", "./ima_setup.sh", "run", measured_dir,
		       शून्य);
		निकास(त्रुटि_सं);

	पूर्ण अन्यथा अगर (child_pid > 0) अणु
		रुकोpid(child_pid, &child_status, 0);
		वापस WEXITSTATUS(child_status);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल u64 ima_hash_from_bpf;

अटल पूर्णांक process_sample(व्योम *ctx, व्योम *data, माप_प्रकार len)
अणु
	ima_hash_from_bpf = *((u64 *)data);
	वापस 0;
पूर्ण

व्योम test_test_ima(व्योम)
अणु
	अक्षर measured_dir_ढाँचा[] = "/tmp/ima_measuredXXXXXX";
	काष्ठा ring_buffer *ringbuf;
	स्थिर अक्षर *measured_dir;
	अक्षर cmd[256];

	पूर्णांक err, duration = 0;
	काष्ठा ima *skel = शून्य;

	skel = ima__खोलो_and_load();
	अगर (CHECK(!skel, "skel_load", "skeleton failed\n"))
		जाओ बंद_prog;

	ringbuf = ring_buffer__new(bpf_map__fd(skel->maps.ringbuf),
				   process_sample, शून्य, शून्य);
	अगर (!ASSERT_OK_PTR(ringbuf, "ringbuf"))
		जाओ बंद_prog;

	err = ima__attach(skel);
	अगर (CHECK(err, "attach", "attach failed: %d\n", err))
		जाओ बंद_prog;

	measured_dir = mkdtemp(measured_dir_ढाँचा);
	अगर (CHECK(measured_dir == शून्य, "mkdtemp", "err %d\n", त्रुटि_सं))
		जाओ बंद_prog;

	snम_लिखो(cmd, माप(cmd), "./ima_setup.sh setup %s", measured_dir);
	err = प्रणाली(cmd);
	अगर (CHECK(err, "failed to run command", "%s, errno = %d\n", cmd, त्रुटि_सं))
		जाओ बंद_clean;

	err = run_measured_process(measured_dir, &skel->bss->monitored_pid);
	अगर (CHECK(err, "run_measured_process", "err = %d\n", err))
		जाओ बंद_clean;

	err = ring_buffer__consume(ringbuf);
	ASSERT_EQ(err, 1, "num_samples_or_err");
	ASSERT_NEQ(ima_hash_from_bpf, 0, "ima_hash");

बंद_clean:
	snम_लिखो(cmd, माप(cmd), "./ima_setup.sh cleanup %s", measured_dir);
	err = प्रणाली(cmd);
	CHECK(err, "failed to run command", "%s, errno = %d\n", cmd, त्रुटि_सं);
बंद_prog:
	ima__destroy(skel);
पूर्ण
