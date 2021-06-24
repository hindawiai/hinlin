<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "test_stack_var_off.skel.h"

/* Test पढ़ो and ग_लिखोs to the stack perक्रमmed with offsets that are not
 * अटलally known.
 */
व्योम test_stack_var_off(व्योम)
अणु
	पूर्णांक duration = 0;
	काष्ठा test_stack_var_off *skel;

	skel = test_stack_var_off__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;

	/* Give pid to bpf prog so it करोesn't trigger क्रम anyone अन्यथा. */
	skel->bss->test_pid = getpid();
	/* Initialize the probe's input. */
	skel->bss->input[0] = 2;
	skel->bss->input[1] = 42;  /* This will be वापसed in probe_res. */

	अगर (!ASSERT_OK(test_stack_var_off__attach(skel), "skel_attach"))
		जाओ cleanup;

	/* Trigger probe. */
	usleep(1);

	अगर (CHECK(skel->bss->probe_res != 42, "check_probe_res",
		  "wrong probe res: %d\n", skel->bss->probe_res))
		जाओ cleanup;

cleanup:
	test_stack_var_off__destroy(skel);
पूर्ण
