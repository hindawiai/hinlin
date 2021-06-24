<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Fileप्रणाली parameter description and parser
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_FS_PARSER_H
#घोषणा _LINUX_FS_PARSER_H

#समावेश <linux/fs_context.h>

काष्ठा path;

काष्ठा स्थिरant_table अणु
	स्थिर अक्षर	*name;
	पूर्णांक		value;
पूर्ण;

काष्ठा fs_parameter_spec;
काष्ठा fs_parse_result;
प्रकार पूर्णांक fs_param_type(काष्ठा p_log *,
			  स्थिर काष्ठा fs_parameter_spec *,
			  काष्ठा fs_parameter *,
			  काष्ठा fs_parse_result *);
/*
 * The type of parameter expected.
 */
fs_param_type fs_param_is_bool, fs_param_is_u32, fs_param_is_s32, fs_param_is_u64,
	fs_param_is_क्रमागत, fs_param_is_string, fs_param_is_blob, fs_param_is_blockdev,
	fs_param_is_path, fs_param_is_fd;

/*
 * Specअगरication of the type of value a parameter wants.
 *
 * Note that the fsparam_flag(), fsparam_string(), fsparam_u32(), ... macros
 * should be used to generate elements of this type.
 */
काष्ठा fs_parameter_spec अणु
	स्थिर अक्षर		*name;
	fs_param_type		*type;	/* The desired parameter type */
	u8			opt;	/* Option number (वापसed by fs_parse()) */
	अचिन्हित लघु		flags;
#घोषणा fs_param_neg_with_no	0x0002	/* "noxxx" is negative param */
#घोषणा fs_param_neg_with_empty	0x0004	/* "xxx=" is negative param */
#घोषणा fs_param_deprecated	0x0008	/* The param is deprecated */
	स्थिर व्योम		*data;
पूर्ण;

/*
 * Result of parse.
 */
काष्ठा fs_parse_result अणु
	bool			negated;	/* T अगर param was "noxxx" */
	जोड़ अणु
		bool		boolean;	/* For spec_bool */
		पूर्णांक		पूर्णांक_32;		/* For spec_s32/spec_क्रमागत */
		अचिन्हित पूर्णांक	uपूर्णांक_32;	/* For spec_u32अणु,_octal,_hexपूर्ण/spec_क्रमागत */
		u64		uपूर्णांक_64;	/* For spec_u64 */
	पूर्ण;
पूर्ण;

बाह्य पूर्णांक __fs_parse(काष्ठा p_log *log,
		    स्थिर काष्ठा fs_parameter_spec *desc,
		    काष्ठा fs_parameter *value,
		    काष्ठा fs_parse_result *result);

अटल अंतरभूत पूर्णांक fs_parse(काष्ठा fs_context *fc,
	     स्थिर काष्ठा fs_parameter_spec *desc,
	     काष्ठा fs_parameter *param,
	     काष्ठा fs_parse_result *result)
अणु
	वापस __fs_parse(&fc->log, desc, param, result);
पूर्ण

बाह्य पूर्णांक fs_lookup_param(काष्ठा fs_context *fc,
			   काष्ठा fs_parameter *param,
			   bool want_bdev,
			   काष्ठा path *_path);

बाह्य पूर्णांक lookup_स्थिरant(स्थिर काष्ठा स्थिरant_table tbl[], स्थिर अक्षर *name, पूर्णांक not_found);

#अगर_घोषित CONFIG_VALIDATE_FS_PARSER
बाह्य bool validate_स्थिरant_table(स्थिर काष्ठा स्थिरant_table *tbl, माप_प्रकार tbl_size,
				    पूर्णांक low, पूर्णांक high, पूर्णांक special);
बाह्य bool fs_validate_description(स्थिर अक्षर *name,
				    स्थिर काष्ठा fs_parameter_spec *desc);
#अन्यथा
अटल अंतरभूत bool validate_स्थिरant_table(स्थिर काष्ठा स्थिरant_table *tbl, माप_प्रकार tbl_size,
					   पूर्णांक low, पूर्णांक high, पूर्णांक special)
अणु वापस true; पूर्ण
अटल अंतरभूत bool fs_validate_description(स्थिर अक्षर *name,
					   स्थिर काष्ठा fs_parameter_spec *desc)
अणु वापस true; पूर्ण
#पूर्ण_अगर

/*
 * Parameter type, name, index and flags element स्थिरructors.  Use as:
 *
 *  fsparam_xxxx("foo", Opt_foo)
 *
 * If existing helpers are not enough, direct use of __fsparam() would
 * work, but any such हाल is probably a sign that new helper is needed.
 * Helpers will reमुख्य stable; low-level implementation may change.
 */
#घोषणा __fsparam(TYPE, NAME, OPT, FLAGS, DATA) \
	अणु \
		.name = NAME, \
		.opt = OPT, \
		.type = TYPE, \
		.flags = FLAGS, \
		.data = DATA \
	पूर्ण

#घोषणा fsparam_flag(NAME, OPT)	__fsparam(शून्य, NAME, OPT, 0, शून्य)
#घोषणा fsparam_flag_no(NAME, OPT) \
			__fsparam(शून्य, NAME, OPT, fs_param_neg_with_no, शून्य)
#घोषणा fsparam_bool(NAME, OPT)	__fsparam(fs_param_is_bool, NAME, OPT, 0, शून्य)
#घोषणा fsparam_u32(NAME, OPT)	__fsparam(fs_param_is_u32, NAME, OPT, 0, शून्य)
#घोषणा fsparam_u32oct(NAME, OPT) \
			__fsparam(fs_param_is_u32, NAME, OPT, 0, (व्योम *)8)
#घोषणा fsparam_u32hex(NAME, OPT) \
			__fsparam(fs_param_is_u32_hex, NAME, OPT, 0, (व्योम *)16)
#घोषणा fsparam_s32(NAME, OPT)	__fsparam(fs_param_is_s32, NAME, OPT, 0, शून्य)
#घोषणा fsparam_u64(NAME, OPT)	__fsparam(fs_param_is_u64, NAME, OPT, 0, शून्य)
#घोषणा fsparam_क्रमागत(NAME, OPT, array)	__fsparam(fs_param_is_क्रमागत, NAME, OPT, 0, array)
#घोषणा fsparam_string(NAME, OPT) \
				__fsparam(fs_param_is_string, NAME, OPT, 0, शून्य)
#घोषणा fsparam_blob(NAME, OPT)	__fsparam(fs_param_is_blob, NAME, OPT, 0, शून्य)
#घोषणा fsparam_bdev(NAME, OPT)	__fsparam(fs_param_is_blockdev, NAME, OPT, 0, शून्य)
#घोषणा fsparam_path(NAME, OPT)	__fsparam(fs_param_is_path, NAME, OPT, 0, शून्य)
#घोषणा fsparam_fd(NAME, OPT)	__fsparam(fs_param_is_fd, NAME, OPT, 0, शून्य)

#पूर्ण_अगर /* _LINUX_FS_PARSER_H */
