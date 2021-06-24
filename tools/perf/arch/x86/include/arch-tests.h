<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_TESTS_H
#घोषणा ARCH_TESTS_H

#समावेश <linux/compiler.h>
काष्ठा test;

/* Tests */
पूर्णांक test__rdpmc(काष्ठा test *test __maybe_unused, पूर्णांक subtest);
पूर्णांक test__insn_x86(काष्ठा test *test __maybe_unused, पूर्णांक subtest);
पूर्णांक test__पूर्णांकel_pt_pkt_decoder(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__bp_modअगरy(काष्ठा test *test, पूर्णांक subtest);
पूर्णांक test__x86_sample_parsing(काष्ठा test *test, पूर्णांक subtest);

#अगर_घोषित HAVE_DWARF_UNWIND_SUPPORT
काष्ठा thपढ़ो;
काष्ठा perf_sample;
पूर्णांक test__arch_unwind_sample(काष्ठा perf_sample *sample,
			     काष्ठा thपढ़ो *thपढ़ो);
#पूर्ण_अगर

बाह्य काष्ठा test arch_tests[];

#पूर्ण_अगर
