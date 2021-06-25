<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Copyright IBM Corp. 2001, 2007
 *	Authors:	Peter Tiedemann (ptiedem@de.ibm.com)
 *
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश "ctcm_dbug.h"

/*
 * Debug Facility Stuff
 */

काष्ठा ctcm_dbf_info ctcm_dbf[CTCM_DBF_INFOS] = अणु
	[CTCM_DBF_SETUP]     = अणु"ctc_setup", 8, 1, 64, CTC_DBF_INFO, शून्यपूर्ण,
	[CTCM_DBF_ERROR]     = अणु"ctc_error", 8, 1, 64, CTC_DBF_ERROR, शून्यपूर्ण,
	[CTCM_DBF_TRACE]     = अणु"ctc_trace", 8, 1, 64, CTC_DBF_ERROR, शून्यपूर्ण,
	[CTCM_DBF_MPC_SETUP] = अणु"mpc_setup", 8, 1, 80, CTC_DBF_INFO, शून्यपूर्ण,
	[CTCM_DBF_MPC_ERROR] = अणु"mpc_error", 8, 1, 80, CTC_DBF_ERROR, शून्यपूर्ण,
	[CTCM_DBF_MPC_TRACE] = अणु"mpc_trace", 8, 1, 80, CTC_DBF_ERROR, शून्यपूर्ण,
पूर्ण;

व्योम ctcm_unरेजिस्टर_dbf_views(व्योम)
अणु
	पूर्णांक x;
	क्रम (x = 0; x < CTCM_DBF_INFOS; x++) अणु
		debug_unरेजिस्टर(ctcm_dbf[x].id);
		ctcm_dbf[x].id = शून्य;
	पूर्ण
पूर्ण

पूर्णांक ctcm_रेजिस्टर_dbf_views(व्योम)
अणु
	पूर्णांक x;
	क्रम (x = 0; x < CTCM_DBF_INFOS; x++) अणु
		/* रेजिस्टर the areas */
		ctcm_dbf[x].id = debug_रेजिस्टर(ctcm_dbf[x].name,
						ctcm_dbf[x].pages,
						ctcm_dbf[x].areas,
						ctcm_dbf[x].len);
		अगर (ctcm_dbf[x].id == शून्य) अणु
			ctcm_unरेजिस्टर_dbf_views();
			वापस -ENOMEM;
		पूर्ण

		/* रेजिस्टर a view */
		debug_रेजिस्टर_view(ctcm_dbf[x].id, &debug_hex_ascii_view);
		/* set a passing level */
		debug_set_level(ctcm_dbf[x].id, ctcm_dbf[x].level);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ctcm_dbf_दीर्घtext(क्रमागत ctcm_dbf_names dbf_nix, पूर्णांक level, अक्षर *fmt, ...)
अणु
	अक्षर dbf_txt_buf[64];
	बहु_सूची args;

	अगर (!debug_level_enabled(ctcm_dbf[dbf_nix].id, level))
		वापस;
	बहु_शुरू(args, fmt);
	vsnम_लिखो(dbf_txt_buf, माप(dbf_txt_buf), fmt, args);
	बहु_पूर्ण(args);

	debug_text_event(ctcm_dbf[dbf_nix].id, level, dbf_txt_buf);
पूर्ण

