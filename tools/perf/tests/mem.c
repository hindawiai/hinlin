<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util/map_symbol.h"
#समावेश "util/mem-events.h"
#समावेश "util/symbol.h"
#समावेश "linux/perf_event.h"
#समावेश "util/debug.h"
#समावेश "tests.h"
#समावेश <माला.स>

अटल पूर्णांक check(जोड़ perf_mem_data_src data_src,
		  स्थिर अक्षर *string)
अणु
	अक्षर out[100];
	अक्षर failure[100];
	काष्ठा mem_info mi = अणु .data_src = data_src पूर्ण;

	पूर्णांक n;

	n = perf_mem__snp_scnम_लिखो(out, माप out, &mi);
	n += perf_mem__lvl_scnम_लिखो(out + n, माप out - n, &mi);
	scnम_लिखो(failure, माप failure, "unexpected %s", out);
	TEST_ASSERT_VAL(failure, !म_भेद(string, out));
	वापस 0;
पूर्ण

पूर्णांक test__mem(काष्ठा test *text __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret = 0;
	जोड़ perf_mem_data_src src;

	स_रखो(&src, 0, माप(src));

	src.mem_lvl = PERF_MEM_LVL_HIT;
	src.mem_lvl_num = 4;

	ret |= check(src, "N/AL4 hit");

	src.mem_remote = 1;

	ret |= check(src, "N/ARemote L4 hit");

	src.mem_lvl = PERF_MEM_LVL_MISS;
	src.mem_lvl_num = PERF_MEM_LVLNUM_PMEM;
	src.mem_remote = 0;

	ret |= check(src, "N/APMEM miss");

	src.mem_remote = 1;

	ret |= check(src, "N/ARemote PMEM miss");

	src.mem_snoopx = PERF_MEM_SNOOPX_FWD;
	src.mem_lvl_num = PERF_MEM_LVLNUM_RAM;

	ret |= check(src , "FwdRemote RAM miss");

	वापस ret;
पूर्ण
