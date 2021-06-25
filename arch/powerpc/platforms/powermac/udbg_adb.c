<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bitops.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/cuda.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/xmon.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/bootx.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/udbg.h>

/*
 * This implementation is "special", it can "patch" the current
 * udbg implementation and work on top of it. It must thus be
 * initialized last
 */

अटल व्योम (*udbg_adb_old_अ_दो)(अक्षर c);
अटल पूर्णांक (*udbg_adb_old_अ_लो)(व्योम);
अटल पूर्णांक (*udbg_adb_old_अ_लो_poll)(व्योम);

अटल क्रमागत अणु
	input_adb_none,
	input_adb_pmu,
	input_adb_cuda,
पूर्ण input_type = input_adb_none;

पूर्णांक xmon_wants_key, xmon_adb_keycode;

अटल अंतरभूत व्योम udbg_adb_poll(व्योम)
अणु
#अगर_घोषित CONFIG_ADB_PMU
	अगर (input_type == input_adb_pmu)
		pmu_poll_adb();
#पूर्ण_अगर /* CONFIG_ADB_PMU */
#अगर_घोषित CONFIG_ADB_CUDA
	अगर (input_type == input_adb_cuda)
		cuda_poll();
#पूर्ण_अगर /* CONFIG_ADB_CUDA */
पूर्ण

#अगर_घोषित CONFIG_BOOTX_TEXT

अटल पूर्णांक udbg_adb_use_btext;
अटल पूर्णांक xmon_adb_shअगरtstate;

अटल अचिन्हित अक्षर xmon_keytab[128] =
	"asdfhgzxcv\000bqwer"				/* 0x00 - 0x0f */
	"yt123465=97-80]o"				/* 0x10 - 0x1f */
	"u[ip\rlj'k;\\,/nm."				/* 0x20 - 0x2f */
	"\t `\177\0\033\0\0\0\0\0\0\0\0\0\0"		/* 0x30 - 0x3f */
	"\0.\0*\0+\0\0\0\0\0/\r\0-\0"			/* 0x40 - 0x4f */
	"\0\0000123456789\0\0\0";			/* 0x50 - 0x5f */

अटल अचिन्हित अक्षर xmon_shअगरt_keytab[128] =
	"ASDFHGZXCV\000BQWER"				/* 0x00 - 0x0f */
	"YT!@#$^%+(&_*)पूर्णO"				/* 0x10 - 0x1f */
	"U{IP\rLJ\"K:|<?NM>"				/* 0x20 - 0x2f */
	"\t ~\177\0\033\0\0\0\0\0\0\0\0\0\0"		/* 0x30 - 0x3f */
	"\0.\0*\0+\0\0\0\0\0/\r\0-\0"			/* 0x40 - 0x4f */
	"\0\0000123456789\0\0\0";			/* 0x50 - 0x5f */

अटल पूर्णांक udbg_adb_local_अ_लो(व्योम)
अणु
	पूर्णांक k, t, on;

	xmon_wants_key = 1;
	क्रम (;;) अणु
		xmon_adb_keycode = -1;
		t = 0;
		on = 0;
		k = -1;
		करो अणु
			अगर (--t < 0) अणु
				on = 1 - on;
				btext_drawअक्षर(on? 0xdb: 0x20);
				btext_drawअक्षर('\b');
				t = 200000;
			पूर्ण
			udbg_adb_poll();
			अगर (udbg_adb_old_अ_लो_poll)
				k = udbg_adb_old_अ_लो_poll();
		पूर्ण जबतक (k == -1 && xmon_adb_keycode == -1);
		अगर (on)
			btext_drawstring(" \b");
		अगर (k != -1)
			वापस k;
		k = xmon_adb_keycode;

		/* test क्रम shअगरt keys */
		अगर ((k & 0x7f) == 0x38 || (k & 0x7f) == 0x7b) अणु
			xmon_adb_shअगरtstate = (k & 0x80) == 0;
			जारी;
		पूर्ण
		अगर (k >= 0x80)
			जारी;	/* ignore up transitions */
		k = (xmon_adb_shअगरtstate? xmon_shअगरt_keytab: xmon_keytab)[k];
		अगर (k != 0)
			अवरोध;
	पूर्ण
	xmon_wants_key = 0;
	वापस k;
पूर्ण
#पूर्ण_अगर /* CONFIG_BOOTX_TEXT */

अटल पूर्णांक udbg_adb_अ_लो(व्योम)
अणु
#अगर_घोषित CONFIG_BOOTX_TEXT
	अगर (udbg_adb_use_btext && input_type != input_adb_none)
		वापस udbg_adb_local_अ_लो();
#पूर्ण_अगर
	अगर (udbg_adb_old_अ_लो)
		वापस udbg_adb_old_अ_लो();
	वापस -1;
पूर्ण

/* अ_लो_poll() is not really used, unless you have the xmon-over modem
 * hack that करोesn't quite concern us here, thus we just poll the low level
 * ADB driver to prevent it from timing out and call back the original poll
 * routine.
 */
अटल पूर्णांक udbg_adb_अ_लो_poll(व्योम)
अणु
	udbg_adb_poll();

	अगर (udbg_adb_old_अ_लो_poll)
		वापस udbg_adb_old_अ_लो_poll();
	वापस -1;
पूर्ण

अटल व्योम udbg_adb_अ_दो(अक्षर c)
अणु
#अगर_घोषित CONFIG_BOOTX_TEXT
	अगर (udbg_adb_use_btext)
		btext_drawअक्षर(c);
#पूर्ण_अगर
	अगर (udbg_adb_old_अ_दो)
		वापस udbg_adb_old_अ_दो(c);
पूर्ण

व्योम __init udbg_adb_init_early(व्योम)
अणु
#अगर_घोषित CONFIG_BOOTX_TEXT
	अगर (btext_find_display(1) == 0) अणु
		udbg_adb_use_btext = 1;
		udbg_अ_दो = udbg_adb_अ_दो;
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक __init udbg_adb_init(पूर्णांक क्रमce_btext)
अणु
	काष्ठा device_node *np;

	/* Capture existing callbacks */
	udbg_adb_old_अ_दो = udbg_अ_दो;
	udbg_adb_old_अ_लो = udbg_अ_लो;
	udbg_adb_old_अ_लो_poll = udbg_अ_लो_poll;

	/* Check अगर our early init was alपढ़ोy called */
	अगर (udbg_adb_old_अ_दो == udbg_adb_अ_दो)
		udbg_adb_old_अ_दो = शून्य;
#अगर_घोषित CONFIG_BOOTX_TEXT
	अगर (udbg_adb_old_अ_दो == btext_drawअक्षर)
		udbg_adb_old_अ_दो = शून्य;
#पूर्ण_अगर

	/* Set ours as output */
	udbg_अ_दो = udbg_adb_अ_दो;
	udbg_अ_लो = udbg_adb_अ_लो;
	udbg_अ_लो_poll = udbg_adb_अ_लो_poll;

#अगर_घोषित CONFIG_BOOTX_TEXT
	/* Check अगर we should use btext output */
	अगर (btext_find_display(क्रमce_btext) == 0)
		udbg_adb_use_btext = 1;
#पूर्ण_अगर

	/* See अगर there is a keyboard in the device tree with a parent
	 * of type "adb". If not, we वापस a failure, but we keep the
	 * bext output set क्रम now
	 */
	क्रम_each_node_by_name(np, "keyboard") अणु
		काष्ठा device_node *parent = of_get_parent(np);
		पूर्णांक found = of_node_is_type(parent, "adb");
		of_node_put(parent);
		अगर (found)
			अवरोध;
	पूर्ण
	अगर (np == शून्य)
		वापस -ENODEV;
	of_node_put(np);

#अगर_घोषित CONFIG_ADB_PMU
	अगर (find_via_pmu())
		input_type = input_adb_pmu;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_CUDA
	अगर (find_via_cuda())
		input_type = input_adb_cuda;
#पूर्ण_अगर

	/* Same as above: nothing found, keep btext set क्रम output */
	अगर (input_type == input_adb_none)
		वापस -ENODEV;

	वापस 0;
पूर्ण
