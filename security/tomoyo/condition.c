<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/condition.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश "common.h"
#समावेश <linux/slab.h>

/* List of "struct tomoyo_condition". */
LIST_HEAD(tomoyo_condition_list);

/**
 * tomoyo_argv - Check argv[] in "struct linux_binbrm".
 *
 * @index:   Index number of @arg_ptr.
 * @arg_ptr: Contents of argv[@index].
 * @argc:    Length of @argv.
 * @argv:    Poपूर्णांकer to "struct tomoyo_argv".
 * @checked: Set to true अगर @argv[@index] was found.
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_argv(स्थिर अचिन्हित पूर्णांक index, स्थिर अक्षर *arg_ptr,
			स्थिर पूर्णांक argc, स्थिर काष्ठा tomoyo_argv *argv,
			u8 *checked)
अणु
	पूर्णांक i;
	काष्ठा tomoyo_path_info arg;

	arg.name = arg_ptr;
	क्रम (i = 0; i < argc; argv++, checked++, i++) अणु
		bool result;

		अगर (index != argv->index)
			जारी;
		*checked = 1;
		tomoyo_fill_path_info(&arg);
		result = tomoyo_path_matches_pattern(&arg, argv->value);
		अगर (argv->is_not)
			result = !result;
		अगर (!result)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * tomoyo_envp - Check envp[] in "struct linux_binbrm".
 *
 * @env_name:  The name of environment variable.
 * @env_value: The value of environment variable.
 * @envc:      Length of @envp.
 * @envp:      Poपूर्णांकer to "struct tomoyo_envp".
 * @checked:   Set to true अगर @envp[@env_name] was found.
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_envp(स्थिर अक्षर *env_name, स्थिर अक्षर *env_value,
			स्थिर पूर्णांक envc, स्थिर काष्ठा tomoyo_envp *envp,
			u8 *checked)
अणु
	पूर्णांक i;
	काष्ठा tomoyo_path_info name;
	काष्ठा tomoyo_path_info value;

	name.name = env_name;
	tomoyo_fill_path_info(&name);
	value.name = env_value;
	tomoyo_fill_path_info(&value);
	क्रम (i = 0; i < envc; envp++, checked++, i++) अणु
		bool result;

		अगर (!tomoyo_path_matches_pattern(&name, envp->name))
			जारी;
		*checked = 1;
		अगर (envp->value) अणु
			result = tomoyo_path_matches_pattern(&value,
							     envp->value);
			अगर (envp->is_not)
				result = !result;
		पूर्ण अन्यथा अणु
			result = true;
			अगर (!envp->is_not)
				result = !result;
		पूर्ण
		अगर (!result)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * tomoyo_scan_bprm - Scan "struct linux_binprm".
 *
 * @ee:   Poपूर्णांकer to "struct tomoyo_execve".
 * @argc: Length of @argc.
 * @argv: Poपूर्णांकer to "struct tomoyo_argv".
 * @envc: Length of @envp.
 * @envp: Poपूर्णांकer to "struct tomoyo_envp".
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_scan_bprm(काष्ठा tomoyo_execve *ee,
			     स्थिर u16 argc, स्थिर काष्ठा tomoyo_argv *argv,
			     स्थिर u16 envc, स्थिर काष्ठा tomoyo_envp *envp)
अणु
	काष्ठा linux_binprm *bprm = ee->bprm;
	काष्ठा tomoyo_page_dump *dump = &ee->dump;
	अक्षर *arg_ptr = ee->पंचांगp;
	पूर्णांक arg_len = 0;
	अचिन्हित दीर्घ pos = bprm->p;
	पूर्णांक offset = pos % PAGE_SIZE;
	पूर्णांक argv_count = bprm->argc;
	पूर्णांक envp_count = bprm->envc;
	bool result = true;
	u8 local_checked[32];
	u8 *checked;

	अगर (argc + envc <= माप(local_checked)) अणु
		checked = local_checked;
		स_रखो(local_checked, 0, माप(local_checked));
	पूर्ण अन्यथा अणु
		checked = kzalloc(argc + envc, GFP_NOFS);
		अगर (!checked)
			वापस false;
	पूर्ण
	जबतक (argv_count || envp_count) अणु
		अगर (!tomoyo_dump_page(bprm, pos, dump)) अणु
			result = false;
			जाओ out;
		पूर्ण
		pos += PAGE_SIZE - offset;
		जबतक (offset < PAGE_SIZE) अणु
			/* Read. */
			स्थिर अक्षर *kaddr = dump->data;
			स्थिर अचिन्हित अक्षर c = kaddr[offset++];

			अगर (c && arg_len < TOMOYO_EXEC_TMPSIZE - 10) अणु
				अगर (c == '\\') अणु
					arg_ptr[arg_len++] = '\\';
					arg_ptr[arg_len++] = '\\';
				पूर्ण अन्यथा अगर (c > ' ' && c < 127) अणु
					arg_ptr[arg_len++] = c;
				पूर्ण अन्यथा अणु
					arg_ptr[arg_len++] = '\\';
					arg_ptr[arg_len++] = (c >> 6) + '0';
					arg_ptr[arg_len++] =
						((c >> 3) & 7) + '0';
					arg_ptr[arg_len++] = (c & 7) + '0';
				पूर्ण
			पूर्ण अन्यथा अणु
				arg_ptr[arg_len] = '\0';
			पूर्ण
			अगर (c)
				जारी;
			/* Check. */
			अगर (argv_count) अणु
				अगर (!tomoyo_argv(bprm->argc - argv_count,
						 arg_ptr, argc, argv,
						 checked)) अणु
					result = false;
					अवरोध;
				पूर्ण
				argv_count--;
			पूर्ण अन्यथा अगर (envp_count) अणु
				अक्षर *cp = म_अक्षर(arg_ptr, '=');

				अगर (cp) अणु
					*cp = '\0';
					अगर (!tomoyo_envp(arg_ptr, cp + 1,
							 envc, envp,
							 checked + argc)) अणु
						result = false;
						अवरोध;
					पूर्ण
				पूर्ण
				envp_count--;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
			arg_len = 0;
		पूर्ण
		offset = 0;
		अगर (!result)
			अवरोध;
	पूर्ण
out:
	अगर (result) अणु
		पूर्णांक i;

		/* Check not-yet-checked entries. */
		क्रम (i = 0; i < argc; i++) अणु
			अगर (checked[i])
				जारी;
			/*
			 * Return true only अगर all unchecked indexes in
			 * bprm->argv[] are not matched.
			 */
			अगर (argv[i].is_not)
				जारी;
			result = false;
			अवरोध;
		पूर्ण
		क्रम (i = 0; i < envc; envp++, i++) अणु
			अगर (checked[argc + i])
				जारी;
			/*
			 * Return true only अगर all unchecked environ variables
			 * in bprm->envp[] are either undefined or not matched.
			 */
			अगर ((!envp->value && !envp->is_not) ||
			    (envp->value && envp->is_not))
				जारी;
			result = false;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (checked != local_checked)
		kमुक्त(checked);
	वापस result;
पूर्ण

/**
 * tomoyo_scan_exec_realpath - Check "exec.realpath" parameter of "struct tomoyo_condition".
 *
 * @file:  Poपूर्णांकer to "struct file".
 * @ptr:   Poपूर्णांकer to "struct tomoyo_name_union".
 * @match: True अगर "exec.realpath=", false अगर "exec.realpath!=".
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_scan_exec_realpath(काष्ठा file *file,
				      स्थिर काष्ठा tomoyo_name_जोड़ *ptr,
				      स्थिर bool match)
अणु
	bool result;
	काष्ठा tomoyo_path_info exe;

	अगर (!file)
		वापस false;
	exe.name = tomoyo_realpath_from_path(&file->f_path);
	अगर (!exe.name)
		वापस false;
	tomoyo_fill_path_info(&exe);
	result = tomoyo_compare_name_जोड़(&exe, ptr);
	kमुक्त(exe.name);
	वापस result == match;
पूर्ण

/**
 * tomoyo_get_dqword - tomoyo_get_name() क्रम a quoted string.
 *
 * @start: String to save.
 *
 * Returns poपूर्णांकer to "struct tomoyo_path_info" on success, शून्य otherwise.
 */
अटल स्थिर काष्ठा tomoyo_path_info *tomoyo_get_dqword(अक्षर *start)
अणु
	अक्षर *cp = start + म_माप(start) - 1;

	अगर (cp == start || *start++ != '"' || *cp != '"')
		वापस शून्य;
	*cp = '\0';
	अगर (*start && !tomoyo_correct_word(start))
		वापस शून्य;
	वापस tomoyo_get_name(start);
पूर्ण

/**
 * tomoyo_parse_name_जोड़_quoted - Parse a quoted word.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 * @ptr:   Poपूर्णांकer to "struct tomoyo_name_union".
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_parse_name_जोड़_quoted(काष्ठा tomoyo_acl_param *param,
					   काष्ठा tomoyo_name_जोड़ *ptr)
अणु
	अक्षर *filename = param->data;

	अगर (*filename == '@')
		वापस tomoyo_parse_name_जोड़(param, ptr);
	ptr->filename = tomoyo_get_dqword(filename);
	वापस ptr->filename != शून्य;
पूर्ण

/**
 * tomoyo_parse_argv - Parse an argv[] condition part.
 *
 * @left:  Lefthand value.
 * @right: Righthand value.
 * @argv:  Poपूर्णांकer to "struct tomoyo_argv".
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_parse_argv(अक्षर *left, अक्षर *right,
			      काष्ठा tomoyo_argv *argv)
अणु
	अगर (tomoyo_parse_uदीर्घ(&argv->index, &left) !=
	    TOMOYO_VALUE_TYPE_DECIMAL || *left++ != ']' || *left)
		वापस false;
	argv->value = tomoyo_get_dqword(right);
	वापस argv->value != शून्य;
पूर्ण

/**
 * tomoyo_parse_envp - Parse an envp[] condition part.
 *
 * @left:  Lefthand value.
 * @right: Righthand value.
 * @envp:  Poपूर्णांकer to "struct tomoyo_envp".
 *
 * Returns true on success, false otherwise.
 */
अटल bool tomoyo_parse_envp(अक्षर *left, अक्षर *right,
			      काष्ठा tomoyo_envp *envp)
अणु
	स्थिर काष्ठा tomoyo_path_info *name;
	स्थिर काष्ठा tomoyo_path_info *value;
	अक्षर *cp = left + म_माप(left) - 1;

	अगर (*cp-- != ']' || *cp != '"')
		जाओ out;
	*cp = '\0';
	अगर (!tomoyo_correct_word(left))
		जाओ out;
	name = tomoyo_get_name(left);
	अगर (!name)
		जाओ out;
	अगर (!म_भेद(right, "NULL")) अणु
		value = शून्य;
	पूर्ण अन्यथा अणु
		value = tomoyo_get_dqword(right);
		अगर (!value) अणु
			tomoyo_put_name(name);
			जाओ out;
		पूर्ण
	पूर्ण
	envp->name = name;
	envp->value = value;
	वापस true;
out:
	वापस false;
पूर्ण

/**
 * tomoyo_same_condition - Check क्रम duplicated "struct tomoyo_condition" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_condition".
 * @b: Poपूर्णांकer to "struct tomoyo_condition".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल अंतरभूत bool tomoyo_same_condition(स्थिर काष्ठा tomoyo_condition *a,
					 स्थिर काष्ठा tomoyo_condition *b)
अणु
	वापस a->size == b->size && a->condc == b->condc &&
		a->numbers_count == b->numbers_count &&
		a->names_count == b->names_count &&
		a->argc == b->argc && a->envc == b->envc &&
		a->grant_log == b->grant_log && a->transit == b->transit &&
		!स_भेद(a + 1, b + 1, a->size - माप(*a));
पूर्ण

/**
 * tomoyo_condition_type - Get condition type.
 *
 * @word: Keyword string.
 *
 * Returns one of values in "enum tomoyo_conditions_index" on success,
 * TOMOYO_MAX_CONDITION_KEYWORD otherwise.
 */
अटल u8 tomoyo_condition_type(स्थिर अक्षर *word)
अणु
	u8 i;

	क्रम (i = 0; i < TOMOYO_MAX_CONDITION_KEYWORD; i++) अणु
		अगर (!म_भेद(word, tomoyo_condition_keyword[i]))
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

/* Define this to enable debug mode. */
/* #घोषणा DEBUG_CONDITION */

#अगर_घोषित DEBUG_CONDITION
#घोषणा dprपूर्णांकk prपूर्णांकk
#अन्यथा
#घोषणा dprपूर्णांकk(...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * tomoyo_commit_condition - Commit "struct tomoyo_condition".
 *
 * @entry: Poपूर्णांकer to "struct tomoyo_condition".
 *
 * Returns poपूर्णांकer to "struct tomoyo_condition" on success, शून्य otherwise.
 *
 * This function merges duplicated entries. This function वापसs शून्य अगर
 * @entry is not duplicated but memory quota क्रम policy has exceeded.
 */
अटल काष्ठा tomoyo_condition *tomoyo_commit_condition
(काष्ठा tomoyo_condition *entry)
अणु
	काष्ठा tomoyo_condition *ptr;
	bool found = false;

	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock)) अणु
		dprपूर्णांकk(KERN_WARNING "%u: %s failed\n", __LINE__, __func__);
		ptr = शून्य;
		found = true;
		जाओ out;
	पूर्ण
	list_क्रम_each_entry(ptr, &tomoyo_condition_list, head.list) अणु
		अगर (!tomoyo_same_condition(ptr, entry) ||
		    atomic_पढ़ो(&ptr->head.users) == TOMOYO_GC_IN_PROGRESS)
			जारी;
		/* Same entry found. Share this entry. */
		atomic_inc(&ptr->head.users);
		found = true;
		अवरोध;
	पूर्ण
	अगर (!found) अणु
		अगर (tomoyo_memory_ok(entry)) अणु
			atomic_set(&entry->head.users, 1);
			list_add(&entry->head.list, &tomoyo_condition_list);
		पूर्ण अन्यथा अणु
			found = true;
			ptr = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
out:
	अगर (found) अणु
		tomoyo_del_condition(&entry->head.list);
		kमुक्त(entry);
		entry = ptr;
	पूर्ण
	वापस entry;
पूर्ण

/**
 * tomoyo_get_transit_preference - Parse करोमुख्य transition preference क्रम execve().
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 * @e:     Poपूर्णांकer to "struct tomoyo_condition".
 *
 * Returns the condition string part.
 */
अटल अक्षर *tomoyo_get_transit_preference(काष्ठा tomoyo_acl_param *param,
					   काष्ठा tomoyo_condition *e)
अणु
	अक्षर * स्थिर pos = param->data;
	bool flag;

	अगर (*pos == '<') अणु
		e->transit = tomoyo_get_करोमुख्यname(param);
		जाओ करोne;
	पूर्ण
	अणु
		अक्षर *cp = म_अक्षर(pos, ' ');

		अगर (cp)
			*cp = '\0';
		flag = tomoyo_correct_path(pos) || !म_भेद(pos, "keep") ||
			!म_भेद(pos, "initialize") || !म_भेद(pos, "reset") ||
			!म_भेद(pos, "child") || !म_भेद(pos, "parent");
		अगर (cp)
			*cp = ' ';
	पूर्ण
	अगर (!flag)
		वापस pos;
	e->transit = tomoyo_get_name(tomoyo_पढ़ो_token(param));
करोne:
	अगर (e->transit)
		वापस param->data;
	/*
	 * Return a bad पढ़ो-only condition string that will let
	 * tomoyo_get_condition() वापस शून्य.
	 */
	वापस "/";
पूर्ण

/**
 * tomoyo_get_condition - Parse condition part.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns poपूर्णांकer to "struct tomoyo_condition" on success, शून्य otherwise.
 */
काष्ठा tomoyo_condition *tomoyo_get_condition(काष्ठा tomoyo_acl_param *param)
अणु
	काष्ठा tomoyo_condition *entry = शून्य;
	काष्ठा tomoyo_condition_element *condp = शून्य;
	काष्ठा tomoyo_number_जोड़ *numbers_p = शून्य;
	काष्ठा tomoyo_name_जोड़ *names_p = शून्य;
	काष्ठा tomoyo_argv *argv = शून्य;
	काष्ठा tomoyo_envp *envp = शून्य;
	काष्ठा tomoyo_condition e = अणु पूर्ण;
	अक्षर * स्थिर start_of_string =
		tomoyo_get_transit_preference(param, &e);
	अक्षर * स्थिर end_of_string = start_of_string + म_माप(start_of_string);
	अक्षर *pos;

rerun:
	pos = start_of_string;
	जबतक (1) अणु
		u8 left = -1;
		u8 right = -1;
		अक्षर *left_word = pos;
		अक्षर *cp;
		अक्षर *right_word;
		bool is_not;

		अगर (!*left_word)
			अवरोध;
		/*
		 * Since left-hand condition करोes not allow use of "path_group"
		 * or "number_group" and environment variable's names करो not
		 * accept '=', it is guaranteed that the original line consists
		 * of one or more repetition of $left$चालक$right blocks
		 * where "$left is free from '=' and ' '" and "$चालक is
		 * either '=' or '!='" and "$right is free from ' '".
		 * Thereक्रमe, we can reस्थिरruct the original line at the end
		 * of dry run even अगर we overग_लिखो $चालक with '\0'.
		 */
		cp = म_अक्षर(pos, ' ');
		अगर (cp) अणु
			*cp = '\0'; /* Will restore later. */
			pos = cp + 1;
		पूर्ण अन्यथा अणु
			pos = "";
		पूर्ण
		right_word = म_अक्षर(left_word, '=');
		अगर (!right_word || right_word == left_word)
			जाओ out;
		is_not = *(right_word - 1) == '!';
		अगर (is_not)
			*(right_word++ - 1) = '\0'; /* Will restore later. */
		अन्यथा अगर (*(right_word + 1) != '=')
			*right_word++ = '\0'; /* Will restore later. */
		अन्यथा
			जाओ out;
		dprपूर्णांकk(KERN_WARNING "%u: <%s>%s=<%s>\n", __LINE__, left_word,
			is_not ? "!" : "", right_word);
		अगर (!म_भेद(left_word, "grant_log")) अणु
			अगर (entry) अणु
				अगर (is_not ||
				    entry->grant_log != TOMOYO_GRANTLOG_AUTO)
					जाओ out;
				अन्यथा अगर (!म_भेद(right_word, "yes"))
					entry->grant_log = TOMOYO_GRANTLOG_YES;
				अन्यथा अगर (!म_भेद(right_word, "no"))
					entry->grant_log = TOMOYO_GRANTLOG_NO;
				अन्यथा
					जाओ out;
			पूर्ण
			जारी;
		पूर्ण
		अगर (!म_भेदन(left_word, "exec.argv[", 10)) अणु
			अगर (!argv) अणु
				e.argc++;
				e.condc++;
			पूर्ण अन्यथा अणु
				e.argc--;
				e.condc--;
				left = TOMOYO_ARGV_ENTRY;
				argv->is_not = is_not;
				अगर (!tomoyo_parse_argv(left_word + 10,
						       right_word, argv++))
					जाओ out;
			पूर्ण
			जाओ store_value;
		पूर्ण
		अगर (!म_भेदन(left_word, "exec.envp[\"", 11)) अणु
			अगर (!envp) अणु
				e.envc++;
				e.condc++;
			पूर्ण अन्यथा अणु
				e.envc--;
				e.condc--;
				left = TOMOYO_ENVP_ENTRY;
				envp->is_not = is_not;
				अगर (!tomoyo_parse_envp(left_word + 11,
						       right_word, envp++))
					जाओ out;
			पूर्ण
			जाओ store_value;
		पूर्ण
		left = tomoyo_condition_type(left_word);
		dprपूर्णांकk(KERN_WARNING "%u: <%s> left=%u\n", __LINE__, left_word,
			left);
		अगर (left == TOMOYO_MAX_CONDITION_KEYWORD) अणु
			अगर (!numbers_p) अणु
				e.numbers_count++;
			पूर्ण अन्यथा अणु
				e.numbers_count--;
				left = TOMOYO_NUMBER_UNION;
				param->data = left_word;
				अगर (*left_word == '@' ||
				    !tomoyo_parse_number_जोड़(param,
							       numbers_p++))
					जाओ out;
			पूर्ण
		पूर्ण
		अगर (!condp)
			e.condc++;
		अन्यथा
			e.condc--;
		अगर (left == TOMOYO_EXEC_REALPATH ||
		    left == TOMOYO_SYMLINK_TARGET) अणु
			अगर (!names_p) अणु
				e.names_count++;
			पूर्ण अन्यथा अणु
				e.names_count--;
				right = TOMOYO_NAME_UNION;
				param->data = right_word;
				अगर (!tomoyo_parse_name_जोड़_quoted(param,
								    names_p++))
					जाओ out;
			पूर्ण
			जाओ store_value;
		पूर्ण
		right = tomoyo_condition_type(right_word);
		अगर (right == TOMOYO_MAX_CONDITION_KEYWORD) अणु
			अगर (!numbers_p) अणु
				e.numbers_count++;
			पूर्ण अन्यथा अणु
				e.numbers_count--;
				right = TOMOYO_NUMBER_UNION;
				param->data = right_word;
				अगर (!tomoyo_parse_number_जोड़(param,
							       numbers_p++))
					जाओ out;
			पूर्ण
		पूर्ण
store_value:
		अगर (!condp) अणु
			dprपूर्णांकk(KERN_WARNING "%u: dry_run left=%u right=%u match=%u\n",
				__LINE__, left, right, !is_not);
			जारी;
		पूर्ण
		condp->left = left;
		condp->right = right;
		condp->equals = !is_not;
		dprपूर्णांकk(KERN_WARNING "%u: left=%u right=%u match=%u\n",
			__LINE__, condp->left, condp->right,
			condp->equals);
		condp++;
	पूर्ण
	dprपूर्णांकk(KERN_INFO "%u: cond=%u numbers=%u names=%u ac=%u ec=%u\n",
		__LINE__, e.condc, e.numbers_count, e.names_count, e.argc,
		e.envc);
	अगर (entry) अणु
		BUG_ON(e.names_count | e.numbers_count | e.argc | e.envc |
		       e.condc);
		वापस tomoyo_commit_condition(entry);
	पूर्ण
	e.size = माप(*entry)
		+ e.condc * माप(काष्ठा tomoyo_condition_element)
		+ e.numbers_count * माप(काष्ठा tomoyo_number_जोड़)
		+ e.names_count * माप(काष्ठा tomoyo_name_जोड़)
		+ e.argc * माप(काष्ठा tomoyo_argv)
		+ e.envc * माप(काष्ठा tomoyo_envp);
	entry = kzalloc(e.size, GFP_NOFS);
	अगर (!entry)
		जाओ out2;
	*entry = e;
	e.transit = शून्य;
	condp = (काष्ठा tomoyo_condition_element *) (entry + 1);
	numbers_p = (काष्ठा tomoyo_number_जोड़ *) (condp + e.condc);
	names_p = (काष्ठा tomoyo_name_जोड़ *) (numbers_p + e.numbers_count);
	argv = (काष्ठा tomoyo_argv *) (names_p + e.names_count);
	envp = (काष्ठा tomoyo_envp *) (argv + e.argc);
	अणु
		bool flag = false;

		क्रम (pos = start_of_string; pos < end_of_string; pos++) अणु
			अगर (*pos)
				जारी;
			अगर (flag) /* Restore " ". */
				*pos = ' ';
			अन्यथा अगर (*(pos + 1) == '=') /* Restore "!=". */
				*pos = '!';
			अन्यथा /* Restore "=". */
				*pos = '=';
			flag = !flag;
		पूर्ण
	पूर्ण
	जाओ rerun;
out:
	dprपूर्णांकk(KERN_WARNING "%u: %s failed\n", __LINE__, __func__);
	अगर (entry) अणु
		tomoyo_del_condition(&entry->head.list);
		kमुक्त(entry);
	पूर्ण
out2:
	tomoyo_put_name(e.transit);
	वापस शून्य;
पूर्ण

/**
 * tomoyo_get_attributes - Revalidate "struct inode".
 *
 * @obj: Poपूर्णांकer to "struct tomoyo_obj_info".
 *
 * Returns nothing.
 */
व्योम tomoyo_get_attributes(काष्ठा tomoyo_obj_info *obj)
अणु
	u8 i;
	काष्ठा dentry *dentry = शून्य;

	क्रम (i = 0; i < TOMOYO_MAX_PATH_STAT; i++) अणु
		काष्ठा inode *inode;

		चयन (i) अणु
		हाल TOMOYO_PATH1:
			dentry = obj->path1.dentry;
			अगर (!dentry)
				जारी;
			अवरोध;
		हाल TOMOYO_PATH2:
			dentry = obj->path2.dentry;
			अगर (!dentry)
				जारी;
			अवरोध;
		शेष:
			अगर (!dentry)
				जारी;
			dentry = dget_parent(dentry);
			अवरोध;
		पूर्ण
		inode = d_backing_inode(dentry);
		अगर (inode) अणु
			काष्ठा tomoyo_mini_stat *stat = &obj->stat[i];

			stat->uid  = inode->i_uid;
			stat->gid  = inode->i_gid;
			stat->ino  = inode->i_ino;
			stat->mode = inode->i_mode;
			stat->dev  = inode->i_sb->s_dev;
			stat->rdev = inode->i_rdev;
			obj->stat_valid[i] = true;
		पूर्ण
		अगर (i & 1) /* TOMOYO_PATH1_PARENT or TOMOYO_PATH2_PARENT */
			dput(dentry);
	पूर्ण
पूर्ण

/**
 * tomoyo_condition - Check condition part.
 *
 * @r:    Poपूर्णांकer to "struct tomoyo_request_info".
 * @cond: Poपूर्णांकer to "struct tomoyo_condition". Maybe शून्य.
 *
 * Returns true on success, false otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
bool tomoyo_condition(काष्ठा tomoyo_request_info *r,
		      स्थिर काष्ठा tomoyo_condition *cond)
अणु
	u32 i;
	अचिन्हित दीर्घ min_v[2] = अणु 0, 0 पूर्ण;
	अचिन्हित दीर्घ max_v[2] = अणु 0, 0 पूर्ण;
	स्थिर काष्ठा tomoyo_condition_element *condp;
	स्थिर काष्ठा tomoyo_number_जोड़ *numbers_p;
	स्थिर काष्ठा tomoyo_name_जोड़ *names_p;
	स्थिर काष्ठा tomoyo_argv *argv;
	स्थिर काष्ठा tomoyo_envp *envp;
	काष्ठा tomoyo_obj_info *obj;
	u16 condc;
	u16 argc;
	u16 envc;
	काष्ठा linux_binprm *bprm = शून्य;

	अगर (!cond)
		वापस true;
	condc = cond->condc;
	argc = cond->argc;
	envc = cond->envc;
	obj = r->obj;
	अगर (r->ee)
		bprm = r->ee->bprm;
	अगर (!bprm && (argc || envc))
		वापस false;
	condp = (काष्ठा tomoyo_condition_element *) (cond + 1);
	numbers_p = (स्थिर काष्ठा tomoyo_number_जोड़ *) (condp + condc);
	names_p = (स्थिर काष्ठा tomoyo_name_जोड़ *)
		(numbers_p + cond->numbers_count);
	argv = (स्थिर काष्ठा tomoyo_argv *) (names_p + cond->names_count);
	envp = (स्थिर काष्ठा tomoyo_envp *) (argv + argc);
	क्रम (i = 0; i < condc; i++) अणु
		स्थिर bool match = condp->equals;
		स्थिर u8 left = condp->left;
		स्थिर u8 right = condp->right;
		bool is_bitop[2] = अणु false, false पूर्ण;
		u8 j;

		condp++;
		/* Check argv[] and envp[] later. */
		अगर (left == TOMOYO_ARGV_ENTRY || left == TOMOYO_ENVP_ENTRY)
			जारी;
		/* Check string expressions. */
		अगर (right == TOMOYO_NAME_UNION) अणु
			स्थिर काष्ठा tomoyo_name_जोड़ *ptr = names_p++;
			काष्ठा tomoyo_path_info *symlink;
			काष्ठा tomoyo_execve *ee;
			काष्ठा file *file;

			चयन (left) अणु
			हाल TOMOYO_SYMLINK_TARGET:
				symlink = obj ? obj->symlink_target : शून्य;
				अगर (!symlink ||
				    !tomoyo_compare_name_जोड़(symlink, ptr)
				    == match)
					जाओ out;
				अवरोध;
			हाल TOMOYO_EXEC_REALPATH:
				ee = r->ee;
				file = ee ? ee->bprm->file : शून्य;
				अगर (!tomoyo_scan_exec_realpath(file, ptr,
							       match))
					जाओ out;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण
		/* Check numeric or bit-op expressions. */
		क्रम (j = 0; j < 2; j++) अणु
			स्थिर u8 index = j ? right : left;
			अचिन्हित दीर्घ value = 0;

			चयन (index) अणु
			हाल TOMOYO_TASK_UID:
				value = from_kuid(&init_user_ns, current_uid());
				अवरोध;
			हाल TOMOYO_TASK_EUID:
				value = from_kuid(&init_user_ns, current_euid());
				अवरोध;
			हाल TOMOYO_TASK_SUID:
				value = from_kuid(&init_user_ns, current_suid());
				अवरोध;
			हाल TOMOYO_TASK_FSUID:
				value = from_kuid(&init_user_ns, current_fsuid());
				अवरोध;
			हाल TOMOYO_TASK_GID:
				value = from_kgid(&init_user_ns, current_gid());
				अवरोध;
			हाल TOMOYO_TASK_EGID:
				value = from_kgid(&init_user_ns, current_egid());
				अवरोध;
			हाल TOMOYO_TASK_SGID:
				value = from_kgid(&init_user_ns, current_sgid());
				अवरोध;
			हाल TOMOYO_TASK_FSGID:
				value = from_kgid(&init_user_ns, current_fsgid());
				अवरोध;
			हाल TOMOYO_TASK_PID:
				value = tomoyo_sys_getpid();
				अवरोध;
			हाल TOMOYO_TASK_PPID:
				value = tomoyo_sys_getppid();
				अवरोध;
			हाल TOMOYO_TYPE_IS_SOCKET:
				value = S_IFSOCK;
				अवरोध;
			हाल TOMOYO_TYPE_IS_SYMLINK:
				value = S_IFLNK;
				अवरोध;
			हाल TOMOYO_TYPE_IS_खाता:
				value = S_IFREG;
				अवरोध;
			हाल TOMOYO_TYPE_IS_BLOCK_DEV:
				value = S_IFBLK;
				अवरोध;
			हाल TOMOYO_TYPE_IS_सूचीECTORY:
				value = S_IFसूची;
				अवरोध;
			हाल TOMOYO_TYPE_IS_CHAR_DEV:
				value = S_IFCHR;
				अवरोध;
			हाल TOMOYO_TYPE_IS_FIFO:
				value = S_IFIFO;
				अवरोध;
			हाल TOMOYO_MODE_SETUID:
				value = S_ISUID;
				अवरोध;
			हाल TOMOYO_MODE_SETGID:
				value = S_ISGID;
				अवरोध;
			हाल TOMOYO_MODE_STICKY:
				value = S_ISVTX;
				अवरोध;
			हाल TOMOYO_MODE_OWNER_READ:
				value = 0400;
				अवरोध;
			हाल TOMOYO_MODE_OWNER_WRITE:
				value = 0200;
				अवरोध;
			हाल TOMOYO_MODE_OWNER_EXECUTE:
				value = 0100;
				अवरोध;
			हाल TOMOYO_MODE_GROUP_READ:
				value = 0040;
				अवरोध;
			हाल TOMOYO_MODE_GROUP_WRITE:
				value = 0020;
				अवरोध;
			हाल TOMOYO_MODE_GROUP_EXECUTE:
				value = 0010;
				अवरोध;
			हाल TOMOYO_MODE_OTHERS_READ:
				value = 0004;
				अवरोध;
			हाल TOMOYO_MODE_OTHERS_WRITE:
				value = 0002;
				अवरोध;
			हाल TOMOYO_MODE_OTHERS_EXECUTE:
				value = 0001;
				अवरोध;
			हाल TOMOYO_EXEC_ARGC:
				अगर (!bprm)
					जाओ out;
				value = bprm->argc;
				अवरोध;
			हाल TOMOYO_EXEC_ENVC:
				अगर (!bprm)
					जाओ out;
				value = bprm->envc;
				अवरोध;
			हाल TOMOYO_NUMBER_UNION:
				/* Fetch values later. */
				अवरोध;
			शेष:
				अगर (!obj)
					जाओ out;
				अगर (!obj->validate_करोne) अणु
					tomoyo_get_attributes(obj);
					obj->validate_करोne = true;
				पूर्ण
				अणु
					u8 stat_index;
					काष्ठा tomoyo_mini_stat *stat;

					चयन (index) अणु
					हाल TOMOYO_PATH1_UID:
					हाल TOMOYO_PATH1_GID:
					हाल TOMOYO_PATH1_INO:
					हाल TOMOYO_PATH1_MAJOR:
					हाल TOMOYO_PATH1_MINOR:
					हाल TOMOYO_PATH1_TYPE:
					हाल TOMOYO_PATH1_DEV_MAJOR:
					हाल TOMOYO_PATH1_DEV_MINOR:
					हाल TOMOYO_PATH1_PERM:
						stat_index = TOMOYO_PATH1;
						अवरोध;
					हाल TOMOYO_PATH2_UID:
					हाल TOMOYO_PATH2_GID:
					हाल TOMOYO_PATH2_INO:
					हाल TOMOYO_PATH2_MAJOR:
					हाल TOMOYO_PATH2_MINOR:
					हाल TOMOYO_PATH2_TYPE:
					हाल TOMOYO_PATH2_DEV_MAJOR:
					हाल TOMOYO_PATH2_DEV_MINOR:
					हाल TOMOYO_PATH2_PERM:
						stat_index = TOMOYO_PATH2;
						अवरोध;
					हाल TOMOYO_PATH1_PARENT_UID:
					हाल TOMOYO_PATH1_PARENT_GID:
					हाल TOMOYO_PATH1_PARENT_INO:
					हाल TOMOYO_PATH1_PARENT_PERM:
						stat_index =
							TOMOYO_PATH1_PARENT;
						अवरोध;
					हाल TOMOYO_PATH2_PARENT_UID:
					हाल TOMOYO_PATH2_PARENT_GID:
					हाल TOMOYO_PATH2_PARENT_INO:
					हाल TOMOYO_PATH2_PARENT_PERM:
						stat_index =
							TOMOYO_PATH2_PARENT;
						अवरोध;
					शेष:
						जाओ out;
					पूर्ण
					अगर (!obj->stat_valid[stat_index])
						जाओ out;
					stat = &obj->stat[stat_index];
					चयन (index) अणु
					हाल TOMOYO_PATH1_UID:
					हाल TOMOYO_PATH2_UID:
					हाल TOMOYO_PATH1_PARENT_UID:
					हाल TOMOYO_PATH2_PARENT_UID:
						value = from_kuid(&init_user_ns, stat->uid);
						अवरोध;
					हाल TOMOYO_PATH1_GID:
					हाल TOMOYO_PATH2_GID:
					हाल TOMOYO_PATH1_PARENT_GID:
					हाल TOMOYO_PATH2_PARENT_GID:
						value = from_kgid(&init_user_ns, stat->gid);
						अवरोध;
					हाल TOMOYO_PATH1_INO:
					हाल TOMOYO_PATH2_INO:
					हाल TOMOYO_PATH1_PARENT_INO:
					हाल TOMOYO_PATH2_PARENT_INO:
						value = stat->ino;
						अवरोध;
					हाल TOMOYO_PATH1_MAJOR:
					हाल TOMOYO_PATH2_MAJOR:
						value = MAJOR(stat->dev);
						अवरोध;
					हाल TOMOYO_PATH1_MINOR:
					हाल TOMOYO_PATH2_MINOR:
						value = MINOR(stat->dev);
						अवरोध;
					हाल TOMOYO_PATH1_TYPE:
					हाल TOMOYO_PATH2_TYPE:
						value = stat->mode & S_IFMT;
						अवरोध;
					हाल TOMOYO_PATH1_DEV_MAJOR:
					हाल TOMOYO_PATH2_DEV_MAJOR:
						value = MAJOR(stat->rdev);
						अवरोध;
					हाल TOMOYO_PATH1_DEV_MINOR:
					हाल TOMOYO_PATH2_DEV_MINOR:
						value = MINOR(stat->rdev);
						अवरोध;
					हाल TOMOYO_PATH1_PERM:
					हाल TOMOYO_PATH2_PERM:
					हाल TOMOYO_PATH1_PARENT_PERM:
					हाल TOMOYO_PATH2_PARENT_PERM:
						value = stat->mode & S_IALLUGO;
						अवरोध;
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
			max_v[j] = value;
			min_v[j] = value;
			चयन (index) अणु
			हाल TOMOYO_MODE_SETUID:
			हाल TOMOYO_MODE_SETGID:
			हाल TOMOYO_MODE_STICKY:
			हाल TOMOYO_MODE_OWNER_READ:
			हाल TOMOYO_MODE_OWNER_WRITE:
			हाल TOMOYO_MODE_OWNER_EXECUTE:
			हाल TOMOYO_MODE_GROUP_READ:
			हाल TOMOYO_MODE_GROUP_WRITE:
			हाल TOMOYO_MODE_GROUP_EXECUTE:
			हाल TOMOYO_MODE_OTHERS_READ:
			हाल TOMOYO_MODE_OTHERS_WRITE:
			हाल TOMOYO_MODE_OTHERS_EXECUTE:
				is_bitop[j] = true;
			पूर्ण
		पूर्ण
		अगर (left == TOMOYO_NUMBER_UNION) अणु
			/* Fetch values now. */
			स्थिर काष्ठा tomoyo_number_जोड़ *ptr = numbers_p++;

			min_v[0] = ptr->values[0];
			max_v[0] = ptr->values[1];
		पूर्ण
		अगर (right == TOMOYO_NUMBER_UNION) अणु
			/* Fetch values now. */
			स्थिर काष्ठा tomoyo_number_जोड़ *ptr = numbers_p++;

			अगर (ptr->group) अणु
				अगर (tomoyo_number_matches_group(min_v[0],
								max_v[0],
								ptr->group)
				    == match)
					जारी;
			पूर्ण अन्यथा अणु
				अगर ((min_v[0] <= ptr->values[1] &&
				     max_v[0] >= ptr->values[0]) == match)
					जारी;
			पूर्ण
			जाओ out;
		पूर्ण
		/*
		 * Bit operation is valid only when counterpart value
		 * represents permission.
		 */
		अगर (is_bitop[0] && is_bitop[1]) अणु
			जाओ out;
		पूर्ण अन्यथा अगर (is_bitop[0]) अणु
			चयन (right) अणु
			हाल TOMOYO_PATH1_PERM:
			हाल TOMOYO_PATH1_PARENT_PERM:
			हाल TOMOYO_PATH2_PERM:
			हाल TOMOYO_PATH2_PARENT_PERM:
				अगर (!(max_v[0] & max_v[1]) == !match)
					जारी;
			पूर्ण
			जाओ out;
		पूर्ण अन्यथा अगर (is_bitop[1]) अणु
			चयन (left) अणु
			हाल TOMOYO_PATH1_PERM:
			हाल TOMOYO_PATH1_PARENT_PERM:
			हाल TOMOYO_PATH2_PERM:
			हाल TOMOYO_PATH2_PARENT_PERM:
				अगर (!(max_v[0] & max_v[1]) == !match)
					जारी;
			पूर्ण
			जाओ out;
		पूर्ण
		/* Normal value range comparison. */
		अगर ((min_v[0] <= max_v[1] && max_v[0] >= min_v[1]) == match)
			जारी;
out:
		वापस false;
	पूर्ण
	/* Check argv[] and envp[] now. */
	अगर (r->ee && (argc || envc))
		वापस tomoyo_scan_bprm(r->ee, argc, argv, envc, envp);
	वापस true;
पूर्ण
