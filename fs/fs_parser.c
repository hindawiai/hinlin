<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Fileप्रणाली parameter parser.
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <linux/namei.h>
#समावेश "internal.h"

अटल स्थिर काष्ठा स्थिरant_table bool_names[] = अणु
	अणु "0",		false पूर्ण,
	अणु "1",		true पूर्ण,
	अणु "false",	false पूर्ण,
	अणु "no",		false पूर्ण,
	अणु "true",	true पूर्ण,
	अणु "yes",	true पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table *
__lookup_स्थिरant(स्थिर काष्ठा स्थिरant_table *tbl, स्थिर अक्षर *name)
अणु
	क्रम ( ; tbl->name; tbl++)
		अगर (म_भेद(name, tbl->name) == 0)
			वापस tbl;
	वापस शून्य;
पूर्ण

/**
 * lookup_स्थिरant - Look up a स्थिरant by name in an ordered table
 * @tbl: The table of स्थिरants to search.
 * @name: The name to look up.
 * @not_found: The value to वापस अगर the name is not found.
 */
पूर्णांक lookup_स्थिरant(स्थिर काष्ठा स्थिरant_table *tbl, स्थिर अक्षर *name, पूर्णांक not_found)
अणु
	स्थिर काष्ठा स्थिरant_table *p = __lookup_स्थिरant(tbl, name);

	वापस p ? p->value : not_found;
पूर्ण
EXPORT_SYMBOL(lookup_स्थिरant);

अटल अंतरभूत bool is_flag(स्थिर काष्ठा fs_parameter_spec *p)
अणु
	वापस p->type == शून्य;
पूर्ण

अटल स्थिर काष्ठा fs_parameter_spec *fs_lookup_key(
	स्थिर काष्ठा fs_parameter_spec *desc,
	काष्ठा fs_parameter *param, bool *negated)
अणु
	स्थिर काष्ठा fs_parameter_spec *p, *other = शून्य;
	स्थिर अक्षर *name = param->key;
	bool want_flag = param->type == fs_value_is_flag;

	*negated = false;
	क्रम (p = desc; p->name; p++) अणु
		अगर (म_भेद(p->name, name) != 0)
			जारी;
		अगर (likely(is_flag(p) == want_flag))
			वापस p;
		other = p;
	पूर्ण
	अगर (want_flag) अणु
		अगर (name[0] == 'n' && name[1] == 'o' && name[2]) अणु
			क्रम (p = desc; p->name; p++) अणु
				अगर (म_भेद(p->name, name + 2) != 0)
					जारी;
				अगर (!(p->flags & fs_param_neg_with_no))
					जारी;
				*negated = true;
				वापस p;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस other;
पूर्ण

/*
 * fs_parse - Parse a fileप्रणाली configuration parameter
 * @fc: The fileप्रणाली context to log errors through.
 * @desc: The parameter description to use.
 * @param: The parameter.
 * @result: Where to place the result of the parse
 *
 * Parse a fileप्रणाली configuration parameter and attempt a conversion क्रम a
 * simple parameter क्रम which this is requested.  If successful, the determined
 * parameter ID is placed पूर्णांकo @result->key, the desired type is indicated in
 * @result->t and any converted value is placed पूर्णांकo an appropriate member of
 * the जोड़ in @result.
 *
 * The function वापसs the parameter number अगर the parameter was matched,
 * -ENOPARAM अगर it wasn't matched and @desc->ignore_unknown indicated that
 * unknown parameters are okay and -EINVAL अगर there was a conversion issue or
 * the parameter wasn't recognised and unknowns aren't okay.
 */
पूर्णांक __fs_parse(काष्ठा p_log *log,
	     स्थिर काष्ठा fs_parameter_spec *desc,
	     काष्ठा fs_parameter *param,
	     काष्ठा fs_parse_result *result)
अणु
	स्थिर काष्ठा fs_parameter_spec *p;

	result->uपूर्णांक_64 = 0;

	p = fs_lookup_key(desc, param, &result->negated);
	अगर (!p)
		वापस -ENOPARAM;

	अगर (p->flags & fs_param_deprecated)
		warn_plog(log, "Deprecated parameter '%s'", param->key);

	/* Try to turn the type we were given पूर्णांकo the type desired by the
	 * parameter and give an error अगर we can't.
	 */
	अगर (is_flag(p)) अणु
		अगर (param->type != fs_value_is_flag)
			वापस inval_plog(log, "Unexpected value for '%s'",
				      param->key);
		result->boolean = !result->negated;
	पूर्ण अन्यथा  अणु
		पूर्णांक ret = p->type(log, p, param, result);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस p->opt;
पूर्ण
EXPORT_SYMBOL(__fs_parse);

/**
 * fs_lookup_param - Look up a path referred to by a parameter
 * @fc: The fileप्रणाली context to log errors through.
 * @param: The parameter.
 * @want_bdev: T अगर want a blockdev
 * @_path: The result of the lookup
 */
पूर्णांक fs_lookup_param(काष्ठा fs_context *fc,
		    काष्ठा fs_parameter *param,
		    bool want_bdev,
		    काष्ठा path *_path)
अणु
	काष्ठा filename *f;
	अचिन्हित पूर्णांक flags = 0;
	bool put_f;
	पूर्णांक ret;

	चयन (param->type) अणु
	हाल fs_value_is_string:
		f = getname_kernel(param->string);
		अगर (IS_ERR(f))
			वापस PTR_ERR(f);
		put_f = true;
		अवरोध;
	हाल fs_value_is_filename:
		f = param->name;
		put_f = false;
		अवरोध;
	शेष:
		वापस invalf(fc, "%s: not usable as path", param->key);
	पूर्ण

	f->refcnt++; /* filename_lookup() drops our ref. */
	ret = filename_lookup(param->dirfd, f, flags, _path, शून्य);
	अगर (ret < 0) अणु
		errorf(fc, "%s: Lookup failure for '%s'", param->key, f->name);
		जाओ out;
	पूर्ण

	अगर (want_bdev &&
	    !S_ISBLK(d_backing_inode(_path->dentry)->i_mode)) अणु
		path_put(_path);
		_path->dentry = शून्य;
		_path->mnt = शून्य;
		errorf(fc, "%s: Non-blockdev passed as '%s'",
		       param->key, f->name);
		ret = -ENOTBLK;
	पूर्ण

out:
	अगर (put_f)
		putname(f);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(fs_lookup_param);

अटल पूर्णांक fs_param_bad_value(काष्ठा p_log *log, काष्ठा fs_parameter *param)
अणु
	वापस inval_plog(log, "Bad value for '%s'", param->key);
पूर्ण

पूर्णांक fs_param_is_bool(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		     काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	पूर्णांक b;
	अगर (param->type != fs_value_is_string)
		वापस fs_param_bad_value(log, param);
	b = lookup_स्थिरant(bool_names, param->string, -1);
	अगर (b == -1)
		वापस fs_param_bad_value(log, param);
	result->boolean = b;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_bool);

पूर्णांक fs_param_is_u32(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		    काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	पूर्णांक base = (अचिन्हित दीर्घ)p->data;
	अगर (param->type != fs_value_is_string ||
	    kstrtouपूर्णांक(param->string, base, &result->uपूर्णांक_32) < 0)
		वापस fs_param_bad_value(log, param);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_u32);

पूर्णांक fs_param_is_s32(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		    काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	अगर (param->type != fs_value_is_string ||
	    kstrtoपूर्णांक(param->string, 0, &result->पूर्णांक_32) < 0)
		वापस fs_param_bad_value(log, param);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_s32);

पूर्णांक fs_param_is_u64(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		    काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	अगर (param->type != fs_value_is_string ||
	    kम_से_अदीर्घl(param->string, 0, &result->uपूर्णांक_64) < 0)
		वापस fs_param_bad_value(log, param);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_u64);

पूर्णांक fs_param_is_क्रमागत(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		     काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	स्थिर काष्ठा स्थिरant_table *c;
	अगर (param->type != fs_value_is_string)
		वापस fs_param_bad_value(log, param);
	c = __lookup_स्थिरant(p->data, param->string);
	अगर (!c)
		वापस fs_param_bad_value(log, param);
	result->uपूर्णांक_32 = c->value;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_क्रमागत);

पूर्णांक fs_param_is_string(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		       काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	अगर (param->type != fs_value_is_string || !*param->string)
		वापस fs_param_bad_value(log, param);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_string);

पूर्णांक fs_param_is_blob(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		     काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	अगर (param->type != fs_value_is_blob)
		वापस fs_param_bad_value(log, param);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_blob);

पूर्णांक fs_param_is_fd(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		  काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	चयन (param->type) अणु
	हाल fs_value_is_string:
		अगर (kstrtouपूर्णांक(param->string, 0, &result->uपूर्णांक_32) < 0)
			अवरोध;
		अगर (result->uपूर्णांक_32 <= पूर्णांक_उच्च)
			वापस 0;
		अवरोध;
	हाल fs_value_is_file:
		result->uपूर्णांक_32 = param->dirfd;
		अगर (result->uपूर्णांक_32 <= पूर्णांक_उच्च)
			वापस 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस fs_param_bad_value(log, param);
पूर्ण
EXPORT_SYMBOL(fs_param_is_fd);

पूर्णांक fs_param_is_blockdev(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		  काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_blockdev);

पूर्णांक fs_param_is_path(काष्ठा p_log *log, स्थिर काष्ठा fs_parameter_spec *p,
		     काष्ठा fs_parameter *param, काष्ठा fs_parse_result *result)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fs_param_is_path);

#अगर_घोषित CONFIG_VALIDATE_FS_PARSER
/**
 * validate_स्थिरant_table - Validate a स्थिरant table
 * @tbl: The स्थिरant table to validate.
 * @tbl_size: The size of the table.
 * @low: The lowest permissible value.
 * @high: The highest permissible value.
 * @special: One special permissible value outside of the range.
 */
bool validate_स्थिरant_table(स्थिर काष्ठा स्थिरant_table *tbl, माप_प्रकार tbl_size,
			     पूर्णांक low, पूर्णांक high, पूर्णांक special)
अणु
	माप_प्रकार i;
	bool good = true;

	अगर (tbl_size == 0) अणु
		pr_warn("VALIDATE C-TBL: Empty\n");
		वापस true;
	पूर्ण

	क्रम (i = 0; i < tbl_size; i++) अणु
		अगर (!tbl[i].name) अणु
			pr_err("VALIDATE C-TBL[%zu]: Null\n", i);
			good = false;
		पूर्ण अन्यथा अगर (i > 0 && tbl[i - 1].name) अणु
			पूर्णांक c = म_भेद(tbl[i-1].name, tbl[i].name);

			अगर (c == 0) अणु
				pr_err("VALIDATE C-TBL[%zu]: Duplicate %s\n",
				       i, tbl[i].name);
				good = false;
			पूर्ण
			अगर (c > 0) अणु
				pr_err("VALIDATE C-TBL[%zu]: Missorted %s>=%s\n",
				       i, tbl[i-1].name, tbl[i].name);
				good = false;
			पूर्ण
		पूर्ण

		अगर (tbl[i].value != special &&
		    (tbl[i].value < low || tbl[i].value > high)) अणु
			pr_err("VALIDATE C-TBL[%zu]: %s->%d const out of range (%d-%d)\n",
			       i, tbl[i].name, tbl[i].value, low, high);
			good = false;
		पूर्ण
	पूर्ण

	वापस good;
पूर्ण

/**
 * fs_validate_description - Validate a parameter description
 * @name: The parameter name to search क्रम.
 * @desc: The parameter description to validate.
 */
bool fs_validate_description(स्थिर अक्षर *name,
	स्थिर काष्ठा fs_parameter_spec *desc)
अणु
	स्थिर काष्ठा fs_parameter_spec *param, *p2;
	bool good = true;

	क्रम (param = desc; param->name; param++) अणु
		/* Check क्रम duplicate parameter names */
		क्रम (p2 = desc; p2 < param; p2++) अणु
			अगर (म_भेद(param->name, p2->name) == 0) अणु
				अगर (is_flag(param) != is_flag(p2))
					जारी;
				pr_err("VALIDATE %s: PARAM[%s]: Duplicate\n",
				       name, param->name);
				good = false;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस good;
पूर्ण
#पूर्ण_अगर /* CONFIG_VALIDATE_FS_PARSER */
