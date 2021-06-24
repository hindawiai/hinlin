<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/options.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Option parsing
 */

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/parser.h>
#समावेश <linux/nls.h>
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश "hfsplus_fs.h"

क्रमागत अणु
	opt_creator, opt_type,
	opt_umask, opt_uid, opt_gid,
	opt_part, opt_session, opt_nls,
	opt_nodecompose, opt_decompose,
	opt_barrier, opt_nobarrier,
	opt_क्रमce, opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणु opt_creator, "creator=%s" पूर्ण,
	अणु opt_type, "type=%s" पूर्ण,
	अणु opt_umask, "umask=%o" पूर्ण,
	अणु opt_uid, "uid=%u" पूर्ण,
	अणु opt_gid, "gid=%u" पूर्ण,
	अणु opt_part, "part=%u" पूर्ण,
	अणु opt_session, "session=%u" पूर्ण,
	अणु opt_nls, "nls=%s" पूर्ण,
	अणु opt_decompose, "decompose" पूर्ण,
	अणु opt_nodecompose, "nodecompose" पूर्ण,
	अणु opt_barrier, "barrier" पूर्ण,
	अणु opt_nobarrier, "nobarrier" पूर्ण,
	अणु opt_क्रमce, "force" पूर्ण,
	अणु opt_err, शून्य पूर्ण
पूर्ण;

/* Initialize an options object to reasonable शेषs */
व्योम hfsplus_fill_शेषs(काष्ठा hfsplus_sb_info *opts)
अणु
	अगर (!opts)
		वापस;

	opts->creator = HFSPLUS_DEF_CR_TYPE;
	opts->type = HFSPLUS_DEF_CR_TYPE;
	opts->umask = current_umask();
	opts->uid = current_uid();
	opts->gid = current_gid();
	opts->part = -1;
	opts->session = -1;
पूर्ण

/* convert a "four byte character" to a 32 bit पूर्णांक with error checks */
अटल अंतरभूत पूर्णांक match_fourअक्षर(substring_t *arg, u32 *result)
अणु
	अगर (arg->to - arg->from != 4)
		वापस -EINVAL;
	स_नकल(result, arg->from, 4);
	वापस 0;
पूर्ण

पूर्णांक hfsplus_parse_options_remount(अक्षर *input, पूर्णांक *क्रमce)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक token;

	अगर (!input)
		वापस 1;

	जबतक ((p = strsep(&input, ",")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल opt_क्रमce:
			*क्रमce = 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/* Parse options from mount. Returns 0 on failure */
/* input is the options passed to mount() as a string */
पूर्णांक hfsplus_parse_options(अक्षर *input, काष्ठा hfsplus_sb_info *sbi)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक पंचांगp, token;

	अगर (!input)
		जाओ करोne;

	जबतक ((p = strsep(&input, ",")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल opt_creator:
			अगर (match_fourअक्षर(&args[0], &sbi->creator)) अणु
				pr_err("creator requires a 4 character value\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_type:
			अगर (match_fourअक्षर(&args[0], &sbi->type)) अणु
				pr_err("type requires a 4 character value\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_umask:
			अगर (match_octal(&args[0], &पंचांगp)) अणु
				pr_err("umask requires a value\n");
				वापस 0;
			पूर्ण
			sbi->umask = (umode_t)पंचांगp;
			अवरोध;
		हाल opt_uid:
			अगर (match_पूर्णांक(&args[0], &पंचांगp)) अणु
				pr_err("uid requires an argument\n");
				वापस 0;
			पूर्ण
			sbi->uid = make_kuid(current_user_ns(), (uid_t)पंचांगp);
			अगर (!uid_valid(sbi->uid)) अणु
				pr_err("invalid uid specified\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_gid:
			अगर (match_पूर्णांक(&args[0], &पंचांगp)) अणु
				pr_err("gid requires an argument\n");
				वापस 0;
			पूर्ण
			sbi->gid = make_kgid(current_user_ns(), (gid_t)पंचांगp);
			अगर (!gid_valid(sbi->gid)) अणु
				pr_err("invalid gid specified\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_part:
			अगर (match_पूर्णांक(&args[0], &sbi->part)) अणु
				pr_err("part requires an argument\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_session:
			अगर (match_पूर्णांक(&args[0], &sbi->session)) अणु
				pr_err("session requires an argument\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_nls:
			अगर (sbi->nls) अणु
				pr_err("unable to change nls mapping\n");
				वापस 0;
			पूर्ण
			p = match_strdup(&args[0]);
			अगर (p)
				sbi->nls = load_nls(p);
			अगर (!sbi->nls) अणु
				pr_err("unable to load nls mapping \"%s\"\n",
				       p);
				kमुक्त(p);
				वापस 0;
			पूर्ण
			kमुक्त(p);
			अवरोध;
		हाल opt_decompose:
			clear_bit(HFSPLUS_SB_NODECOMPOSE, &sbi->flags);
			अवरोध;
		हाल opt_nodecompose:
			set_bit(HFSPLUS_SB_NODECOMPOSE, &sbi->flags);
			अवरोध;
		हाल opt_barrier:
			clear_bit(HFSPLUS_SB_NOBARRIER, &sbi->flags);
			अवरोध;
		हाल opt_nobarrier:
			set_bit(HFSPLUS_SB_NOBARRIER, &sbi->flags);
			अवरोध;
		हाल opt_क्रमce:
			set_bit(HFSPLUS_SB_FORCE, &sbi->flags);
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

करोne:
	अगर (!sbi->nls) अणु
		/* try utf8 first, as this is the old शेष behaviour */
		sbi->nls = load_nls("utf8");
		अगर (!sbi->nls)
			sbi->nls = load_nls_शेष();
		अगर (!sbi->nls)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक hfsplus_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(root->d_sb);

	अगर (sbi->creator != HFSPLUS_DEF_CR_TYPE)
		seq_show_option_n(seq, "creator", (अक्षर *)&sbi->creator, 4);
	अगर (sbi->type != HFSPLUS_DEF_CR_TYPE)
		seq_show_option_n(seq, "type", (अक्षर *)&sbi->type, 4);
	seq_म_लिखो(seq, ",umask=%o,uid=%u,gid=%u", sbi->umask,
			from_kuid_munged(&init_user_ns, sbi->uid),
			from_kgid_munged(&init_user_ns, sbi->gid));
	अगर (sbi->part >= 0)
		seq_म_लिखो(seq, ",part=%u", sbi->part);
	अगर (sbi->session >= 0)
		seq_म_लिखो(seq, ",session=%u", sbi->session);
	अगर (sbi->nls)
		seq_म_लिखो(seq, ",nls=%s", sbi->nls->अक्षरset);
	अगर (test_bit(HFSPLUS_SB_NODECOMPOSE, &sbi->flags))
		seq_माला_दो(seq, ",nodecompose");
	अगर (test_bit(HFSPLUS_SB_NOBARRIER, &sbi->flags))
		seq_माला_दो(seq, ",nobarrier");
	वापस 0;
पूर्ण
