<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <माला.स>

#समावेश "debug.h"
#समावेश "tests/tests.h"
#समावेश "arch-tests.h"
#समावेश "../../../../arch/x86/include/asm/insn.h"

#समावेश "intel-pt-decoder/intel-pt-insn-decoder.h"

काष्ठा test_data अणु
	u8 data[MAX_INSN_SIZE];
	पूर्णांक expected_length;
	पूर्णांक expected_rel;
	स्थिर अक्षर *expected_op_str;
	स्थिर अक्षर *expected_branch_str;
	स्थिर अक्षर *यंत्र_rep;
पूर्ण;

काष्ठा test_data test_data_32[] = अणु
#समावेश "insn-x86-dat-32.c"
	अणुअणु0x0f, 0x01, 0xeeपूर्ण, 3, 0, शून्य, शून्य, "0f 01 ee             \trdpkru"पूर्ण,
	अणुअणु0x0f, 0x01, 0xefपूर्ण, 3, 0, शून्य, शून्य, "0f 01 ef             \twrpkru"पूर्ण,
	अणुअणु0पूर्ण, 0, 0, शून्य, शून्य, शून्यपूर्ण,
पूर्ण;

काष्ठा test_data test_data_64[] = अणु
#समावेश "insn-x86-dat-64.c"
	अणुअणु0x0f, 0x01, 0xeeपूर्ण, 3, 0, शून्य, शून्य, "0f 01 ee             \trdpkru"पूर्ण,
	अणुअणु0x0f, 0x01, 0xefपूर्ण, 3, 0, शून्य, शून्य, "0f 01 ef             \twrpkru"पूर्ण,
	अणुअणु0पूर्ण, 0, 0, शून्य, शून्य, शून्यपूर्ण,
पूर्ण;

अटल पूर्णांक get_op(स्थिर अक्षर *op_str)
अणु
	काष्ठा val_data अणु
		स्थिर अक्षर *name;
		पूर्णांक val;
	पूर्ण vals[] = अणु
		अणु"other",   INTEL_PT_OP_OTHERपूर्ण,
		अणु"call",    INTEL_PT_OP_CALLपूर्ण,
		अणु"ret",     INTEL_PT_OP_RETपूर्ण,
		अणु"jcc",     INTEL_PT_OP_JCCपूर्ण,
		अणु"jmp",     INTEL_PT_OP_JMPपूर्ण,
		अणु"loop",    INTEL_PT_OP_LOOPपूर्ण,
		अणु"iret",    INTEL_PT_OP_IRETपूर्ण,
		अणु"int",     INTEL_PT_OP_INTपूर्ण,
		अणु"syscall", INTEL_PT_OP_SYSCALLपूर्ण,
		अणु"sysret",  INTEL_PT_OP_SYSRETपूर्ण,
		अणु"vmentry",  INTEL_PT_OP_VMENTRYपूर्ण,
		अणुशून्य, 0पूर्ण,
	पूर्ण;
	काष्ठा val_data *val;

	अगर (!op_str || !म_माप(op_str))
		वापस 0;

	क्रम (val = vals; val->name; val++) अणु
		अगर (!म_भेद(val->name, op_str))
			वापस val->val;
	पूर्ण

	pr_debug("Failed to get op\n");

	वापस -1;
पूर्ण

अटल पूर्णांक get_branch(स्थिर अक्षर *branch_str)
अणु
	काष्ठा val_data अणु
		स्थिर अक्षर *name;
		पूर्णांक val;
	पूर्ण vals[] = अणु
		अणु"no_branch",     INTEL_PT_BR_NO_BRANCHपूर्ण,
		अणु"indirect",      INTEL_PT_BR_INसूचीECTपूर्ण,
		अणु"conditional",   INTEL_PT_BR_CONDITIONALपूर्ण,
		अणु"unconditional", INTEL_PT_BR_UNCONDITIONALपूर्ण,
		अणुशून्य, 0पूर्ण,
	पूर्ण;
	काष्ठा val_data *val;

	अगर (!branch_str || !म_माप(branch_str))
		वापस 0;

	क्रम (val = vals; val->name; val++) अणु
		अगर (!म_भेद(val->name, branch_str))
			वापस val->val;
	पूर्ण

	pr_debug("Failed to get branch\n");

	वापस -1;
पूर्ण

अटल पूर्णांक test_data_item(काष्ठा test_data *dat, पूर्णांक x86_64)
अणु
	काष्ठा पूर्णांकel_pt_insn पूर्णांकel_pt_insn;
	पूर्णांक op, branch, ret;
	काष्ठा insn insn;

	ret = insn_decode(&insn, dat->data, MAX_INSN_SIZE,
			  x86_64 ? INSN_MODE_64 : INSN_MODE_32);
	अगर (ret < 0) अणु
		pr_debug("Failed to decode: %s\n", dat->यंत्र_rep);
		वापस -1;
	पूर्ण

	अगर (insn.length != dat->expected_length) अणु
		pr_debug("Failed to decode length (%d vs expected %d): %s\n",
			 insn.length, dat->expected_length, dat->यंत्र_rep);
		वापस -1;
	पूर्ण

	op = get_op(dat->expected_op_str);
	branch = get_branch(dat->expected_branch_str);

	अगर (पूर्णांकel_pt_get_insn(dat->data, MAX_INSN_SIZE, x86_64, &पूर्णांकel_pt_insn)) अणु
		pr_debug("Intel PT failed to decode: %s\n", dat->यंत्र_rep);
		वापस -1;
	पूर्ण

	अगर ((पूर्णांक)पूर्णांकel_pt_insn.op != op) अणु
		pr_debug("Failed to decode 'op' value (%d vs expected %d): %s\n",
			 पूर्णांकel_pt_insn.op, op, dat->यंत्र_rep);
		वापस -1;
	पूर्ण

	अगर ((पूर्णांक)पूर्णांकel_pt_insn.branch != branch) अणु
		pr_debug("Failed to decode 'branch' value (%d vs expected %d): %s\n",
			 पूर्णांकel_pt_insn.branch, branch, dat->यंत्र_rep);
		वापस -1;
	पूर्ण

	अगर (पूर्णांकel_pt_insn.rel != dat->expected_rel) अणु
		pr_debug("Failed to decode 'rel' value (%#x vs expected %#x): %s\n",
			 पूर्णांकel_pt_insn.rel, dat->expected_rel, dat->यंत्र_rep);
		वापस -1;
	पूर्ण

	pr_debug("Decoded ok: %s\n", dat->यंत्र_rep);

	वापस 0;
पूर्ण

अटल पूर्णांक test_data_set(काष्ठा test_data *dat_set, पूर्णांक x86_64)
अणु
	काष्ठा test_data *dat;
	पूर्णांक ret = 0;

	क्रम (dat = dat_set; dat->expected_length; dat++) अणु
		अगर (test_data_item(dat, x86_64))
			ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * test__insn_x86 - test x86 inकाष्ठाion decoder - new inकाष्ठाions.
 *
 * This function implements a test that decodes a selection of inकाष्ठाions and
 * checks the results.  The Intel PT function that further categorizes
 * inकाष्ठाions (i.e. पूर्णांकel_pt_get_insn()) is also checked.
 *
 * The inकाष्ठाions are originally in insn-x86-dat-src.c which has been
 * processed by scripts gen-insn-x86-dat.sh and gen-insn-x86-dat.awk to produce
 * insn-x86-dat-32.c and insn-x86-dat-64.c which are included पूर्णांकo this program.
 * i.e. to add new inकाष्ठाions to the test, edit insn-x86-dat-src.c, run the
 * gen-insn-x86-dat.sh script, make perf, and then run the test.
 *
 * If the test passes %0 is वापसed, otherwise %-1 is वापसed.  Use the
 * verbose (-v) option to see all the inकाष्ठाions and whether or not they
 * decoded successfully.
 */
पूर्णांक test__insn_x86(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret = 0;

	अगर (test_data_set(test_data_32, 0))
		ret = -1;

	अगर (test_data_set(test_data_64, 1))
		ret = -1;

	वापस ret;
पूर्ण
