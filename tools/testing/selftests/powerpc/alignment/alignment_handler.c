<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Test the घातerpc alignment handler on POWER8/POWER9
 *
 * Copyright (C) 2017 IBM Corporation (Michael Neuling, Andrew Donnellan)
 */

/*
 * This selftest exercises the घातerpc alignment fault handler.
 *
 * We create two sets of source and destination buffers, one in regular memory,
 * the other cache-inhibited (by शेष we use /dev/fb0 क्रम this, but an
 * alterative path क्रम cache-inhibited memory may be provided, e.g. memtrace).
 *
 * We initialise the source buffers, then use whichever set of load/store
 * inकाष्ठाions is under test to copy bytes from the source buffers to the
 * destination buffers. For the regular buffers, these inकाष्ठाions will
 * execute normally. For the cache-inhibited buffers, these inकाष्ठाions
 * will trap and cause an alignment fault, and the alignment fault handler
 * will emulate the particular inकाष्ठाion under test. We then compare the
 * destination buffers to ensure that the native and emulated हालs give the
 * same result.
 *
 * TODO:
 *   - Any FIXMEs below
 *   - Test VSX regs < 32 and > 32
 *   - Test all loads and stores
 *   - Check update क्रमms करो update रेजिस्टर
 *   - Test alignment faults over page boundary
 *
 * Some old binutils may not support all the inकाष्ठाions.
 */


#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <getopt.h>
#समावेश <समलाँघ.स>
#समावेश <संकेत.स>

#समावेश "utils.h"
#समावेश "instructions.h"

पूर्णांक bufsize;
पूर्णांक debug;
पूर्णांक testing;
अस्थिर पूर्णांक gotsig;
bool prefixes_enabled;
अक्षर *cipath = "/dev/fb0";
दीर्घ cioffset;

व्योम sighandler(पूर्णांक sig, siginfo_t *info, व्योम *ctx)
अणु
	ucontext_t *ucp = ctx;

	अगर (!testing) अणु
		संकेत(sig, संक_पूर्व);
		समाप्त(0, sig);
	पूर्ण
	gotsig = sig;
#अगर_घोषित __घातerpc64__
	अगर (prefixes_enabled) अणु
		u32 inst = *(u32 *)ucp->uc_mcontext.gp_regs[PT_NIP];
		ucp->uc_mcontext.gp_regs[PT_NIP] += ((inst >> 26 == 1) ? 8 : 4);
	पूर्ण अन्यथा अणु
		ucp->uc_mcontext.gp_regs[PT_NIP] += 4;
	पूर्ण
#अन्यथा
	ucp->uc_mcontext.uc_regs->gregs[PT_NIP] += 4;
#पूर्ण_अगर
पूर्ण

#घोषणा XFORM(reg, n)  " " #reg " ,%"#n",%2 ;"
#घोषणा DFORM(reg, n)  " " #reg " ,0(%"#n") ;"

#घोषणा TEST(name, ld_op, st_op, क्रमm, ld_reg, st_reg)		\
	व्योम test_##name(अक्षर *s, अक्षर *d)			\
	अणु							\
		यंत्र अस्थिर(					\
			#ld_op क्रमm(ld_reg, 0)			\
			#st_op क्रमm(st_reg, 1)			\
			:: "r"(s), "r"(d), "r"(0)		\
			: "memory", "vs0", "vs32", "r31");	\
	पूर्ण							\
	rc |= करो_test(#name, test_##name)

#घोषणा TESTP(name, ld_op, st_op, ld_reg, st_reg)		\
	व्योम test_##name(अक्षर *s, अक्षर *d)			\
	अणु							\
		यंत्र अस्थिर(					\
			ld_op(ld_reg, %0, 0, 0)			\
			st_op(st_reg, %1, 0, 0)			\
			:: "r"(s), "r"(d), "r"(0)		\
			: "memory", "vs0", "vs32", "r31");	\
	पूर्ण							\
	rc |= करो_test(#name, test_##name)

#घोषणा LOAD_VSX_XFORM_TEST(op) TEST(op, op, stxvd2x, XFORM, 32, 32)
#घोषणा STORE_VSX_XFORM_TEST(op) TEST(op, lxvd2x, op, XFORM, 32, 32)
#घोषणा LOAD_VSX_DFORM_TEST(op) TEST(op, op, stxv, DFORM, 32, 32)
#घोषणा STORE_VSX_DFORM_TEST(op) TEST(op, lxv, op, DFORM, 32, 32)
#घोषणा LOAD_VMX_XFORM_TEST(op) TEST(op, op, stxvd2x, XFORM, 0, 32)
#घोषणा STORE_VMX_XFORM_TEST(op) TEST(op, lxvd2x, op, XFORM, 32, 0)
#घोषणा LOAD_VMX_DFORM_TEST(op) TEST(op, op, stxv, DFORM, 0, 32)
#घोषणा STORE_VMX_DFORM_TEST(op) TEST(op, lxv, op, DFORM, 32, 0)

#घोषणा LOAD_XFORM_TEST(op) TEST(op, op, stdx, XFORM, 31, 31)
#घोषणा STORE_XFORM_TEST(op) TEST(op, ldx, op, XFORM, 31, 31)
#घोषणा LOAD_DFORM_TEST(op) TEST(op, op, std, DFORM, 31, 31)
#घोषणा STORE_DFORM_TEST(op) TEST(op, ld, op, DFORM, 31, 31)

#घोषणा LOAD_FLOAT_DFORM_TEST(op)  TEST(op, op, stfd, DFORM, 0, 0)
#घोषणा STORE_FLOAT_DFORM_TEST(op) TEST(op, lfd, op, DFORM, 0, 0)
#घोषणा LOAD_FLOAT_XFORM_TEST(op)  TEST(op, op, stfdx, XFORM, 0, 0)
#घोषणा STORE_FLOAT_XFORM_TEST(op) TEST(op, lfdx, op, XFORM, 0, 0)

#घोषणा LOAD_MLS_PREFIX_TEST(op) TESTP(op, op, PSTD, 31, 31)
#घोषणा STORE_MLS_PREFIX_TEST(op) TESTP(op, PLD, op, 31, 31)

#घोषणा LOAD_8LS_PREFIX_TEST(op) TESTP(op, op, PSTD, 31, 31)
#घोषणा STORE_8LS_PREFIX_TEST(op) TESTP(op, PLD, op, 31, 31)

#घोषणा LOAD_FLOAT_MLS_PREFIX_TEST(op) TESTP(op, op, PSTFD, 0, 0)
#घोषणा STORE_FLOAT_MLS_PREFIX_TEST(op) TESTP(op, PLFD, op, 0, 0)

#घोषणा LOAD_VSX_8LS_PREFIX_TEST(op, tail) TESTP(op, op, PSTXV ## tail, 0, 32)
#घोषणा STORE_VSX_8LS_PREFIX_TEST(op, tail) TESTP(op, PLXV ## tail, op, 32, 0)

/* FIXME: Unimplemented tests: */
// STORE_DFORM_TEST(stq)   /* FIXME: need two रेजिस्टरs क्रम quad */
// STORE_DFORM_TEST(stswi) /* FIXME: string inकाष्ठाion */

// STORE_XFORM_TEST(stwat) /* AMO can't emulate or run on CI */
// STORE_XFORM_TEST(stdat) /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */


/* preload byte by byte */
व्योम preload_data(व्योम *dst, पूर्णांक offset, पूर्णांक width)
अणु
	अक्षर *c = dst;
	पूर्णांक i;

	c += offset;

	क्रम (i = 0 ; i < width ; i++)
		c[i] = i;
पूर्ण

पूर्णांक test_स_नकल(व्योम *dst, व्योम *src, पूर्णांक size, पूर्णांक offset,
		व्योम (*test_func)(अक्षर *, अक्षर *))
अणु
	अक्षर *s, *d;

	s = src;
	s += offset;
	d = dst;
	d += offset;

	निश्चित(size == 16);
	gotsig = 0;
	testing = 1;

	test_func(s, d); /* run the actual test */

	testing = 0;
	अगर (gotsig) अणु
		अगर (debug)
			म_लिखो("  Got signal %i\n", gotsig);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dumpdata(अक्षर *s1, अक्षर *s2, पूर्णांक n, अक्षर *test_name)
अणु
	पूर्णांक i;

	म_लिखो("  %s: unexpected result:\n", test_name);
	म_लिखो("    mem:");
	क्रम (i = 0; i < n; i++)
		म_लिखो(" %02x", s1[i]);
	म_लिखो("\n");
	म_लिखो("    ci: ");
	क्रम (i = 0; i < n; i++)
		म_लिखो(" %02x", s2[i]);
	म_लिखो("\n");
पूर्ण

पूर्णांक test_स_भेद(व्योम *s1, व्योम *s2, पूर्णांक n, पूर्णांक offset, अक्षर *test_name)
अणु
	अक्षर *s1c, *s2c;

	s1c = s1;
	s1c += offset;
	s2c = s2;
	s2c += offset;

	अगर (स_भेद(s1c, s2c, n)) अणु
		अगर (debug) अणु
			म_लिखो("\n  Compare failed. Offset:%i length:%i\n",
			       offset, n);
			dumpdata(s1c, s2c, n, test_name);
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Do two स_नकल tests using the same inकाष्ठाions. One cachable
 * memory and the other करोesn't.
 */
पूर्णांक करो_test(अक्षर *test_name, व्योम (*test_func)(अक्षर *, अक्षर *))
अणु
	पूर्णांक offset, width, fd, rc, r;
	व्योम *mem0, *mem1, *ci0, *ci1;

	म_लिखो("\tDoing %s:\t", test_name);

	fd = खोलो(cipath, O_RDWR);
	अगर (fd < 0) अणु
		म_लिखो("\n");
		लिखो_त्रुटि("Can't open ci file now?");
		वापस 1;
	पूर्ण

	ci0 = mmap(शून्य, bufsize, PROT_WRITE | PROT_READ, MAP_SHARED,
		   fd, cioffset);
	ci1 = mmap(शून्य, bufsize, PROT_WRITE | PROT_READ, MAP_SHARED,
		   fd, cioffset + bufsize);

	अगर ((ci0 == MAP_FAILED) || (ci1 == MAP_FAILED)) अणु
		म_लिखो("\n");
		लिखो_त्रुटि("mmap failed");
		SKIP_IF(1);
	पूर्ण

	rc = posix_memalign(&mem0, bufsize, bufsize);
	अगर (rc) अणु
		म_लिखो("\n");
		वापस rc;
	पूर्ण

	rc = posix_memalign(&mem1, bufsize, bufsize);
	अगर (rc) अणु
		म_लिखो("\n");
		मुक्त(mem0);
		वापस rc;
	पूर्ण

	rc = 0;
	/*
	 * offset = 0 is aligned but tests the workaround क्रम the P9N
	 * DD2.1 vector CI load issue (see 5080332c2c89 "घातerpc/64s:
	 * Add workaround क्रम P9 vector CI load issue")
	 */
	क्रम (offset = 0; offset < 16; offset++) अणु
		width = 16; /* vsx == 16 bytes */
		r = 0;

		/* load pattern पूर्णांकo memory byte by byte */
		preload_data(ci0, offset, width);
		preload_data(mem0, offset, width); // FIXME: हटाओ??
		स_नकल(ci0, mem0, bufsize);
		स_नकल(ci1, mem1, bufsize); /* initialise output to the same */

		/* sanity check */
		test_स_भेद(mem0, ci0, width, offset, test_name);

		r |= test_स_नकल(ci1,  ci0,  width, offset, test_func);
		r |= test_स_नकल(mem1, mem0, width, offset, test_func);
		अगर (r && !debug) अणु
			म_लिखो("FAILED: Got signal");
			rc = 1;
			अवरोध;
		पूर्ण

		r |= test_स_भेद(mem1, ci1, width, offset, test_name);
		अगर (r && !debug) अणु
			म_लिखो("FAILED: Wrong Data");
			rc = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rc == 0)
		म_लिखो("PASSED");

	म_लिखो("\n");

	munmap(ci0, bufsize);
	munmap(ci1, bufsize);
	मुक्त(mem0);
	मुक्त(mem1);
	बंद(fd);

	वापस rc;
पूर्ण

अटल bool can_खोलो_cअगरile(व्योम)
अणु
	पूर्णांक fd;

	fd = खोलो(cipath, O_RDWR);
	अगर (fd < 0)
		वापस false;

	बंद(fd);
	वापस true;
पूर्ण

पूर्णांक test_alignment_handler_vsx_206(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06));

	म_लिखो("VSX: 2.06B\n");
	LOAD_VSX_XFORM_TEST(lxvd2x);
	LOAD_VSX_XFORM_TEST(lxvw4x);
	LOAD_VSX_XFORM_TEST(lxsdx);
	LOAD_VSX_XFORM_TEST(lxvdsx);
	STORE_VSX_XFORM_TEST(stxvd2x);
	STORE_VSX_XFORM_TEST(stxvw4x);
	STORE_VSX_XFORM_TEST(stxsdx);
	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_vsx_207(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	म_लिखो("VSX: 2.07B\n");
	LOAD_VSX_XFORM_TEST(lxsspx);
	LOAD_VSX_XFORM_TEST(lxsiwax);
	LOAD_VSX_XFORM_TEST(lxsiwzx);
	STORE_VSX_XFORM_TEST(stxsspx);
	STORE_VSX_XFORM_TEST(stxsiwx);
	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_vsx_300(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_3_00));
	म_लिखो("VSX: 3.00B\n");
	LOAD_VMX_DFORM_TEST(lxsd);
	LOAD_VSX_XFORM_TEST(lxsibzx);
	LOAD_VSX_XFORM_TEST(lxsihzx);
	LOAD_VMX_DFORM_TEST(lxssp);
	LOAD_VSX_DFORM_TEST(lxv);
	LOAD_VSX_XFORM_TEST(lxvb16x);
	LOAD_VSX_XFORM_TEST(lxvh8x);
	LOAD_VSX_XFORM_TEST(lxvx);
	LOAD_VSX_XFORM_TEST(lxvwsx);
	LOAD_VSX_XFORM_TEST(lxvl);
	LOAD_VSX_XFORM_TEST(lxvll);
	STORE_VMX_DFORM_TEST(stxsd);
	STORE_VSX_XFORM_TEST(stxsibx);
	STORE_VSX_XFORM_TEST(stxsihx);
	STORE_VMX_DFORM_TEST(stxssp);
	STORE_VSX_DFORM_TEST(stxv);
	STORE_VSX_XFORM_TEST(stxvb16x);
	STORE_VSX_XFORM_TEST(stxvh8x);
	STORE_VSX_XFORM_TEST(stxvx);
	STORE_VSX_XFORM_TEST(stxvl);
	STORE_VSX_XFORM_TEST(stxvll);
	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_vsx_prefix(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_3_1));

	म_लिखो("VSX: PREFIX\n");
	LOAD_VSX_8LS_PREFIX_TEST(PLXSD, 0);
	LOAD_VSX_8LS_PREFIX_TEST(PLXSSP, 0);
	LOAD_VSX_8LS_PREFIX_TEST(PLXV0, 0);
	LOAD_VSX_8LS_PREFIX_TEST(PLXV1, 1);
	STORE_VSX_8LS_PREFIX_TEST(PSTXSD, 0);
	STORE_VSX_8LS_PREFIX_TEST(PSTXSSP, 0);
	STORE_VSX_8LS_PREFIX_TEST(PSTXV0, 0);
	STORE_VSX_8LS_PREFIX_TEST(PSTXV1, 1);
	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_पूर्णांकeger(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());

	म_लिखो("Integer\n");
	LOAD_DFORM_TEST(lbz);
	LOAD_DFORM_TEST(lbzu);
	LOAD_XFORM_TEST(lbzx);
	LOAD_XFORM_TEST(lbzux);
	LOAD_DFORM_TEST(lhz);
	LOAD_DFORM_TEST(lhzu);
	LOAD_XFORM_TEST(lhzx);
	LOAD_XFORM_TEST(lhzux);
	LOAD_DFORM_TEST(lha);
	LOAD_DFORM_TEST(lhau);
	LOAD_XFORM_TEST(lhax);
	LOAD_XFORM_TEST(lhaux);
	LOAD_XFORM_TEST(lhbrx);
	LOAD_DFORM_TEST(lwz);
	LOAD_DFORM_TEST(lwzu);
	LOAD_XFORM_TEST(lwzx);
	LOAD_XFORM_TEST(lwzux);
	LOAD_DFORM_TEST(lwa);
	LOAD_XFORM_TEST(lwax);
	LOAD_XFORM_TEST(lwaux);
	LOAD_XFORM_TEST(lwbrx);
	LOAD_DFORM_TEST(ld);
	LOAD_DFORM_TEST(ldu);
	LOAD_XFORM_TEST(ldx);
	LOAD_XFORM_TEST(ldux);
	STORE_DFORM_TEST(stb);
	STORE_XFORM_TEST(stbx);
	STORE_DFORM_TEST(stbu);
	STORE_XFORM_TEST(stbux);
	STORE_DFORM_TEST(sth);
	STORE_XFORM_TEST(sthx);
	STORE_DFORM_TEST(sthu);
	STORE_XFORM_TEST(sthux);
	STORE_XFORM_TEST(sthbrx);
	STORE_DFORM_TEST(stw);
	STORE_XFORM_TEST(stwx);
	STORE_DFORM_TEST(stwu);
	STORE_XFORM_TEST(stwux);
	STORE_XFORM_TEST(stwbrx);
	STORE_DFORM_TEST(std);
	STORE_XFORM_TEST(stdx);
	STORE_DFORM_TEST(stdu);
	STORE_XFORM_TEST(stdux);

#अगर_घोषित __BIG_ENDIAN__
	LOAD_DFORM_TEST(lmw);
	STORE_DFORM_TEST(sपंचांगw);
#पूर्ण_अगर

	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_पूर्णांकeger_206(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06));

	म_लिखो("Integer: 2.06\n");

	LOAD_XFORM_TEST(ldbrx);
	STORE_XFORM_TEST(stdbrx);

	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_पूर्णांकeger_prefix(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_3_1));

	म_लिखो("Integer: PREFIX\n");
	LOAD_MLS_PREFIX_TEST(PLBZ);
	LOAD_MLS_PREFIX_TEST(PLHZ);
	LOAD_MLS_PREFIX_TEST(PLHA);
	LOAD_MLS_PREFIX_TEST(PLWZ);
	LOAD_8LS_PREFIX_TEST(PLWA);
	LOAD_8LS_PREFIX_TEST(PLD);
	STORE_MLS_PREFIX_TEST(PSTB);
	STORE_MLS_PREFIX_TEST(PSTH);
	STORE_MLS_PREFIX_TEST(PSTW);
	STORE_8LS_PREFIX_TEST(PSTD);
	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_vmx(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap(PPC_FEATURE_HAS_ALTIVEC));

	म_लिखो("VMX\n");
	LOAD_VMX_XFORM_TEST(lvx);

	/*
	 * FIXME: These loads only load part of the रेजिस्टर, so our
	 * testing method करोesn't work. Also they don't take alignment
	 * faults, so it's kinda poपूर्णांकless anyway
	 *
	 LOAD_VMX_XFORM_TEST(lvebx)
	 LOAD_VMX_XFORM_TEST(lvehx)
	 LOAD_VMX_XFORM_TEST(lvewx)
	 LOAD_VMX_XFORM_TEST(lvxl)
	*/
	STORE_VMX_XFORM_TEST(stvx);
	STORE_VMX_XFORM_TEST(stvebx);
	STORE_VMX_XFORM_TEST(stvehx);
	STORE_VMX_XFORM_TEST(stvewx);
	STORE_VMX_XFORM_TEST(stvxl);
	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_fp(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());

	म_लिखो("Floating point\n");
	LOAD_FLOAT_DFORM_TEST(lfd);
	LOAD_FLOAT_XFORM_TEST(lfdx);
	LOAD_FLOAT_DFORM_TEST(lfdu);
	LOAD_FLOAT_XFORM_TEST(lfdux);
	LOAD_FLOAT_DFORM_TEST(lfs);
	LOAD_FLOAT_XFORM_TEST(lfsx);
	LOAD_FLOAT_DFORM_TEST(lfsu);
	LOAD_FLOAT_XFORM_TEST(lfsux);
	STORE_FLOAT_DFORM_TEST(stfd);
	STORE_FLOAT_XFORM_TEST(stfdx);
	STORE_FLOAT_DFORM_TEST(stfdu);
	STORE_FLOAT_XFORM_TEST(stfdux);
	STORE_FLOAT_DFORM_TEST(stfs);
	STORE_FLOAT_XFORM_TEST(stfsx);
	STORE_FLOAT_DFORM_TEST(stfsu);
	STORE_FLOAT_XFORM_TEST(stfsux);
	STORE_FLOAT_XFORM_TEST(stfiwx);

	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_fp_205(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_05));

	म_लिखो("Floating point: 2.05\n");

	LOAD_FLOAT_DFORM_TEST(lfdp);
	LOAD_FLOAT_XFORM_TEST(lfdpx);
	LOAD_FLOAT_XFORM_TEST(lfiwax);
	STORE_FLOAT_DFORM_TEST(stfdp);
	STORE_FLOAT_XFORM_TEST(stfdpx);

	वापस rc;
पूर्ण

पूर्णांक test_alignment_handler_fp_206(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06));

	म_लिखो("Floating point: 2.06\n");

	LOAD_FLOAT_XFORM_TEST(lfiwzx);

	वापस rc;
पूर्ण


पूर्णांक test_alignment_handler_fp_prefix(व्योम)
अणु
	पूर्णांक rc = 0;

	SKIP_IF(!can_खोलो_cअगरile());
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_3_1));

	म_लिखो("Floating point: PREFIX\n");
	LOAD_FLOAT_DFORM_TEST(lfs);
	LOAD_FLOAT_MLS_PREFIX_TEST(PLFS);
	LOAD_FLOAT_MLS_PREFIX_TEST(PLFD);
	STORE_FLOAT_MLS_PREFIX_TEST(PSTFS);
	STORE_FLOAT_MLS_PREFIX_TEST(PSTFD);
	वापस rc;
पूर्ण

व्योम usage(अक्षर *prog)
अणु
	म_लिखो("Usage: %s [options] [path [offset]]\n", prog);
	म_लिखो("  -d	Enable debug error output\n");
	म_लिखो("\n");
	म_लिखो("This test requires a POWER8, POWER9 or POWER10 CPU ");
	म_लिखो("and either a usable framebuffer at /dev/fb0 or ");
	म_लिखो("the path to usable cache inhibited memory and optional ");
	म_लिखो("offset to be provided\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु

	काष्ठा sigaction sa;
	पूर्णांक rc = 0;
	पूर्णांक option = 0;

	जबतक ((option = getopt(argc, argv, "d")) != -1) अणु
		चयन (option) अणु
		हाल 'd':
			debug++;
			अवरोध;
		शेष:
			usage(argv[0]);
			निकास(1);
		पूर्ण
	पूर्ण
	argc -= optind;
	argv += optind;

	अगर (argc > 0)
		cipath = argv[0];
	अगर (argc > 1)
		cioffset = म_से_दीर्घ(argv[1], 0, 0x10);

	bufsize = getpagesize();

	sa.sa_sigaction = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	अगर (sigaction(संक_अंश, &sa, शून्य) == -1
	    || sigaction(SIGBUS, &sa, शून्य) == -1
	    || sigaction(संक_अवैध, &sa, शून्य) == -1) अणु
		लिखो_त्रुटि("sigaction");
		निकास(1);
	पूर्ण

	prefixes_enabled = have_hwcap2(PPC_FEATURE2_ARCH_3_1);

	rc |= test_harness(test_alignment_handler_vsx_206,
			   "test_alignment_handler_vsx_206");
	rc |= test_harness(test_alignment_handler_vsx_207,
			   "test_alignment_handler_vsx_207");
	rc |= test_harness(test_alignment_handler_vsx_300,
			   "test_alignment_handler_vsx_300");
	rc |= test_harness(test_alignment_handler_vsx_prefix,
			   "test_alignment_handler_vsx_prefix");
	rc |= test_harness(test_alignment_handler_पूर्णांकeger,
			   "test_alignment_handler_integer");
	rc |= test_harness(test_alignment_handler_पूर्णांकeger_206,
			   "test_alignment_handler_integer_206");
	rc |= test_harness(test_alignment_handler_पूर्णांकeger_prefix,
			   "test_alignment_handler_integer_prefix");
	rc |= test_harness(test_alignment_handler_vmx,
			   "test_alignment_handler_vmx");
	rc |= test_harness(test_alignment_handler_fp,
			   "test_alignment_handler_fp");
	rc |= test_harness(test_alignment_handler_fp_205,
			   "test_alignment_handler_fp_205");
	rc |= test_harness(test_alignment_handler_fp_206,
			   "test_alignment_handler_fp_206");
	rc |= test_harness(test_alignment_handler_fp_prefix,
			   "test_alignment_handler_fp_prefix");
	वापस rc;
पूर्ण
