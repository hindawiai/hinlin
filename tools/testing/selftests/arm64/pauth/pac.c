<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#घोषणा _GNU_SOURCE

#समावेश <sys/auxv.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <संकेत.स>
#समावेश <समलाँघ.स>
#समावेश <sched.h>

#समावेश "../../kselftest_harness.h"
#समावेश "helper.h"

#घोषणा PAC_COLLISION_ATTEMPTS 10
/*
 * The kernel sets TBID by शेष. So bits 55 and above should reमुख्य
 * untouched no matter what.
 * The VA space size is 48 bits. Bigger is opt-in.
 */
#घोषणा PAC_MASK (~0xff80ffffffffffff)
#घोषणा ARBITRARY_VALUE (0x1234)
#घोषणा ASSERT_PAUTH_ENABLED() \
करो अणु \
	अचिन्हित दीर्घ hwcaps = getauxval(AT_HWCAP); \
	/* data key inकाष्ठाions are not in NOP space. This prevents a संक_अवैध */ \
	ASSERT_NE(0, hwcaps & HWCAP_PACA) TH_LOG("PAUTH not enabled"); \
पूर्ण जबतक (0)
#घोषणा ASSERT_GENERIC_PAUTH_ENABLED() \
करो अणु \
	अचिन्हित दीर्घ hwcaps = getauxval(AT_HWCAP); \
	/* generic key inकाष्ठाions are not in NOP space. This prevents a संक_अवैध */ \
	ASSERT_NE(0, hwcaps & HWCAP_PACG) TH_LOG("Generic PAUTH not enabled"); \
पूर्ण जबतक (0)

व्योम sign_specअगरic(काष्ठा signatures *sign, माप_प्रकार val)
अणु
	sign->keyia = keyia_sign(val);
	sign->keyib = keyib_sign(val);
	sign->keyda = keyda_sign(val);
	sign->keydb = keydb_sign(val);
पूर्ण

व्योम sign_all(काष्ठा signatures *sign, माप_प्रकार val)
अणु
	sign->keyia = keyia_sign(val);
	sign->keyib = keyib_sign(val);
	sign->keyda = keyda_sign(val);
	sign->keydb = keydb_sign(val);
	sign->keyg  = keyg_sign(val);
पूर्ण

पूर्णांक n_same(काष्ठा signatures *old, काष्ठा signatures *new, पूर्णांक nkeys)
अणु
	पूर्णांक res = 0;

	res += old->keyia == new->keyia;
	res += old->keyib == new->keyib;
	res += old->keyda == new->keyda;
	res += old->keydb == new->keydb;
	अगर (nkeys == NKEYS)
		res += old->keyg == new->keyg;

	वापस res;
पूर्ण

पूर्णांक n_same_single_set(काष्ठा signatures *sign, पूर्णांक nkeys)
अणु
	माप_प्रकार vals[nkeys];
	पूर्णांक same = 0;

	vals[0] = sign->keyia & PAC_MASK;
	vals[1] = sign->keyib & PAC_MASK;
	vals[2] = sign->keyda & PAC_MASK;
	vals[3] = sign->keydb & PAC_MASK;

	अगर (nkeys >= 4)
		vals[4] = sign->keyg & PAC_MASK;

	क्रम (पूर्णांक i = 0; i < nkeys - 1; i++) अणु
		क्रम (पूर्णांक j = i + 1; j < nkeys; j++) अणु
			अगर (vals[i] == vals[j])
				same += 1;
		पूर्ण
	पूर्ण
	वापस same;
पूर्ण

पूर्णांक exec_sign_all(काष्ठा signatures *चिन्हित_vals, माप_प्रकार val)
अणु
	पूर्णांक new_मानक_निवेश[2];
	पूर्णांक new_मानक_निकास[2];
	पूर्णांक status;
	पूर्णांक i;
	sमाप_प्रकार ret;
	pid_t pid;
	cpu_set_t mask;

	ret = pipe(new_मानक_निवेश);
	अगर (ret == -1) अणु
		लिखो_त्रुटि("pipe returned error");
		वापस -1;
	पूर्ण

	ret = pipe(new_मानक_निकास);
	अगर (ret == -1) अणु
		लिखो_त्रुटि("pipe returned error");
		वापस -1;
	पूर्ण

	/*
	 * pin this process and all its children to a single CPU, so it can also
	 * guarantee a context चयन with its child
	 */
	sched_getaffinity(0, माप(mask), &mask);

	क्रम (i = 0; i < माप(cpu_set_t); i++)
		अगर (CPU_ISSET(i, &mask))
			अवरोध;

	CPU_ZERO(&mask);
	CPU_SET(i, &mask);
	sched_setaffinity(0, माप(mask), &mask);

	pid = विभाजन();
	// child
	अगर (pid == 0) अणु
		dup2(new_मानक_निवेश[0], STDIN_खाताNO);
		अगर (ret == -1) अणु
			लिखो_त्रुटि("dup2 returned error");
			निकास(1);
		पूर्ण

		dup2(new_मानक_निकास[1], STDOUT_खाताNO);
		अगर (ret == -1) अणु
			लिखो_त्रुटि("dup2 returned error");
			निकास(1);
		पूर्ण

		बंद(new_मानक_निवेश[0]);
		बंद(new_मानक_निवेश[1]);
		बंद(new_मानक_निकास[0]);
		बंद(new_मानक_निकास[1]);

		ret = execl("exec_target", "exec_target", (अक्षर *)शून्य);
		अगर (ret == -1) अणु
			लिखो_त्रुटि("exec returned error");
			निकास(1);
		पूर्ण
	पूर्ण

	बंद(new_मानक_निवेश[0]);
	बंद(new_मानक_निकास[1]);

	ret = ग_लिखो(new_मानक_निवेश[1], &val, माप(माप_प्रकार));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("write returned error");
		वापस -1;
	पूर्ण

	/*
	 * रुको क्रम the worker to finish, so that पढ़ो() पढ़ोs all data
	 * will also context चयन with worker so that this function can be used
	 * क्रम context चयन tests
	 */
	रुकोpid(pid, &status, 0);
	अगर (WIFEXITED(status) == 0) अणु
		ख_लिखो(मानक_त्रुटि, "worker exited unexpectedly\n");
		वापस -1;
	पूर्ण
	अगर (WEXITSTATUS(status) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "worker exited with error\n");
		वापस -1;
	पूर्ण

	ret = पढ़ो(new_मानक_निकास[0], चिन्हित_vals, माप(काष्ठा signatures));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("read returned error");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

sigलाँघ_बफ jmpbuf;
व्योम pac_संकेत_handler(पूर्णांक signum, siginfo_t *si, व्योम *uc)
अणु
	अगर (signum == संक_अंश || signum == संक_अवैध)
		sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

/* check that a corrupted PAC results in संक_अंश or संक_अवैध */
TEST(corrupt_pac)
अणु
	काष्ठा sigaction sa;

	ASSERT_PAUTH_ENABLED();
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) == 0) अणु
		sa.sa_sigaction = pac_संकेत_handler;
		sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
		sigemptyset(&sa.sa_mask);

		sigaction(संक_अंश, &sa, शून्य);
		sigaction(संक_अवैध, &sa, शून्य);

		pac_corruptor();
		ASSERT_TRUE(0) TH_LOG("SIGSEGV/SIGILL signal did not occur");
	पूर्ण
पूर्ण

/*
 * There are no separate pac* and aut* controls so checking only the pac*
 * inकाष्ठाions is sufficient
 */
TEST(pac_inकाष्ठाions_not_nop)
अणु
	माप_प्रकार keyia = 0;
	माप_प्रकार keyib = 0;
	माप_प्रकार keyda = 0;
	माप_प्रकार keydb = 0;

	ASSERT_PAUTH_ENABLED();

	क्रम (पूर्णांक i = 0; i < PAC_COLLISION_ATTEMPTS; i++) अणु
		keyia |= keyia_sign(i) & PAC_MASK;
		keyib |= keyib_sign(i) & PAC_MASK;
		keyda |= keyda_sign(i) & PAC_MASK;
		keydb |= keydb_sign(i) & PAC_MASK;
	पूर्ण

	ASSERT_NE(0, keyia) TH_LOG("keyia instructions did nothing");
	ASSERT_NE(0, keyib) TH_LOG("keyib instructions did nothing");
	ASSERT_NE(0, keyda) TH_LOG("keyda instructions did nothing");
	ASSERT_NE(0, keydb) TH_LOG("keydb instructions did nothing");
पूर्ण

TEST(pac_inकाष्ठाions_not_nop_generic)
अणु
	माप_प्रकार keyg = 0;

	ASSERT_GENERIC_PAUTH_ENABLED();

	क्रम (पूर्णांक i = 0; i < PAC_COLLISION_ATTEMPTS; i++)
		keyg |= keyg_sign(i) & PAC_MASK;

	ASSERT_NE(0, keyg)  TH_LOG("keyg instructions did nothing");
पूर्ण

TEST(single_thपढ़ो_dअगरferent_keys)
अणु
	पूर्णांक same = 10;
	पूर्णांक nkeys = NKEYS;
	पूर्णांक पंचांगp;
	काष्ठा signatures चिन्हित_vals;
	अचिन्हित दीर्घ hwcaps = getauxval(AT_HWCAP);

	/* generic and data key inकाष्ठाions are not in NOP space. This prevents a संक_अवैध */
	ASSERT_NE(0, hwcaps & HWCAP_PACA) TH_LOG("PAUTH not enabled");
	अगर (!(hwcaps & HWCAP_PACG)) अणु
		TH_LOG("WARNING: Generic PAUTH not enabled. Skipping generic key checks");
		nkeys = NKEYS - 1;
	पूर्ण

	/*
	 * In Linux the PAC field can be up to 7 bits wide. Even अगर keys are
	 * dअगरferent, there is about 5% chance क्रम PACs to collide with
	 * dअगरferent addresses. This chance rapidly increases with fewer bits
	 * allocated क्रम the PAC (e.g. wider address). A comparison of the keys
	 * directly will be more reliable.
	 * All चिन्हित values need to be dअगरferent at least once out of n
	 * attempts to be certain that the keys are dअगरferent
	 */
	क्रम (पूर्णांक i = 0; i < PAC_COLLISION_ATTEMPTS; i++) अणु
		अगर (nkeys == NKEYS)
			sign_all(&चिन्हित_vals, i);
		अन्यथा
			sign_specअगरic(&चिन्हित_vals, i);

		पंचांगp = n_same_single_set(&चिन्हित_vals, nkeys);
		अगर (पंचांगp < same)
			same = पंचांगp;
	पूर्ण

	ASSERT_EQ(0, same) TH_LOG("%d keys clashed every time", same);
पूर्ण

/*
 * विभाजन() करोes not change keys. Only exec() करोes so call a worker program.
 * Its only job is to sign a value and report back the resutls
 */
TEST(exec_changed_keys)
अणु
	काष्ठा signatures new_keys;
	काष्ठा signatures old_keys;
	पूर्णांक ret;
	पूर्णांक same = 10;
	पूर्णांक nkeys = NKEYS;
	अचिन्हित दीर्घ hwcaps = getauxval(AT_HWCAP);

	/* generic and data key inकाष्ठाions are not in NOP space. This prevents a संक_अवैध */
	ASSERT_NE(0, hwcaps & HWCAP_PACA) TH_LOG("PAUTH not enabled");
	अगर (!(hwcaps & HWCAP_PACG)) अणु
		TH_LOG("WARNING: Generic PAUTH not enabled. Skipping generic key checks");
		nkeys = NKEYS - 1;
	पूर्ण

	क्रम (पूर्णांक i = 0; i < PAC_COLLISION_ATTEMPTS; i++) अणु
		ret = exec_sign_all(&new_keys, i);
		ASSERT_EQ(0, ret) TH_LOG("failed to run worker");

		अगर (nkeys == NKEYS)
			sign_all(&old_keys, i);
		अन्यथा
			sign_specअगरic(&old_keys, i);

		ret = n_same(&old_keys, &new_keys, nkeys);
		अगर (ret < same)
			same = ret;
	पूर्ण

	ASSERT_EQ(0, same) TH_LOG("exec() did not change %d keys", same);
पूर्ण

TEST(context_चयन_keep_keys)
अणु
	पूर्णांक ret;
	काष्ठा signatures trash;
	काष्ठा signatures beक्रमe;
	काष्ठा signatures after;

	ASSERT_PAUTH_ENABLED();

	sign_specअगरic(&beक्रमe, ARBITRARY_VALUE);

	/* will context चयन with a process with dअगरferent keys at least once */
	ret = exec_sign_all(&trash, ARBITRARY_VALUE);
	ASSERT_EQ(0, ret) TH_LOG("failed to run worker");

	sign_specअगरic(&after, ARBITRARY_VALUE);

	ASSERT_EQ(beक्रमe.keyia, after.keyia) TH_LOG("keyia changed after context switching");
	ASSERT_EQ(beक्रमe.keyib, after.keyib) TH_LOG("keyib changed after context switching");
	ASSERT_EQ(beक्रमe.keyda, after.keyda) TH_LOG("keyda changed after context switching");
	ASSERT_EQ(beक्रमe.keydb, after.keydb) TH_LOG("keydb changed after context switching");
पूर्ण

TEST(context_चयन_keep_keys_generic)
अणु
	पूर्णांक ret;
	काष्ठा signatures trash;
	माप_प्रकार beक्रमe;
	माप_प्रकार after;

	ASSERT_GENERIC_PAUTH_ENABLED();

	beक्रमe = keyg_sign(ARBITRARY_VALUE);

	/* will context चयन with a process with dअगरferent keys at least once */
	ret = exec_sign_all(&trash, ARBITRARY_VALUE);
	ASSERT_EQ(0, ret) TH_LOG("failed to run worker");

	after = keyg_sign(ARBITRARY_VALUE);

	ASSERT_EQ(beक्रमe, after) TH_LOG("keyg changed after context switching");
पूर्ण

TEST_HARNESS_MAIN
