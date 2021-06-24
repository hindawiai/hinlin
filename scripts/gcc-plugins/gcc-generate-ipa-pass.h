<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generator क्रम IPA pass related boilerplate code/data
 *
 * Supports gcc 4.5-6
 *
 * Usage:
 *
 * 1. beक्रमe inclusion define PASS_NAME
 * 2. beक्रमe inclusion define NO_* क्रम unimplemented callbacks
 *    NO_GENERATE_SUMMARY
 *    NO_READ_SUMMARY
 *    NO_WRITE_SUMMARY
 *    NO_READ_OPTIMIZATION_SUMMARY
 *    NO_WRITE_OPTIMIZATION_SUMMARY
 *    NO_STMT_FIXUP
 *    NO_FUNCTION_TRANSFORM
 *    NO_VARIABLE_TRANSFORM
 *    NO_GATE
 *    NO_EXECUTE
 * 3. beक्रमe inclusion define PROPERTIES_* and *TODO_FLAGS_* to override
 *    the शेष 0 values
 * 4. क्रम convenience, all the above will be undefined after inclusion!
 * 5. the only exported name is make_PASS_NAME_pass() to रेजिस्टर with gcc
 */

#अगर_अघोषित PASS_NAME
#त्रुटि at least PASS_NAME must be defined
#अन्यथा
#घोषणा __GCC_PLUGIN_STRINGIFY(n)	#n
#घोषणा _GCC_PLUGIN_STRINGIFY(n)	__GCC_PLUGIN_STRINGIFY(n)
#घोषणा _GCC_PLUGIN_CONCAT2(x, y)	x ## y
#घोषणा _GCC_PLUGIN_CONCAT3(x, y, z)	x ## y ## z

#घोषणा __PASS_NAME_PASS_DATA(n)	_GCC_PLUGIN_CONCAT2(n, _pass_data)
#घोषणा _PASS_NAME_PASS_DATA		__PASS_NAME_PASS_DATA(PASS_NAME)

#घोषणा __PASS_NAME_PASS(n)		_GCC_PLUGIN_CONCAT2(n, _pass)
#घोषणा _PASS_NAME_PASS			__PASS_NAME_PASS(PASS_NAME)

#घोषणा _PASS_NAME_NAME			_GCC_PLUGIN_STRINGIFY(PASS_NAME)

#घोषणा __MAKE_PASS_NAME_PASS(n)	_GCC_PLUGIN_CONCAT3(make_, n, _pass)
#घोषणा _MAKE_PASS_NAME_PASS		__MAKE_PASS_NAME_PASS(PASS_NAME)

#अगर_घोषित NO_GENERATE_SUMMARY
#घोषणा _GENERATE_SUMMARY शून्य
#अन्यथा
#घोषणा __GENERATE_SUMMARY(n)		_GCC_PLUGIN_CONCAT2(n, _generate_summary)
#घोषणा _GENERATE_SUMMARY		__GENERATE_SUMMARY(PASS_NAME)
#पूर्ण_अगर

#अगर_घोषित NO_READ_SUMMARY
#घोषणा _READ_SUMMARY शून्य
#अन्यथा
#घोषणा __READ_SUMMARY(n)		_GCC_PLUGIN_CONCAT2(n, _पढ़ो_summary)
#घोषणा _READ_SUMMARY			__READ_SUMMARY(PASS_NAME)
#पूर्ण_अगर

#अगर_घोषित NO_WRITE_SUMMARY
#घोषणा _WRITE_SUMMARY शून्य
#अन्यथा
#घोषणा __WRITE_SUMMARY(n)		_GCC_PLUGIN_CONCAT2(n, _ग_लिखो_summary)
#घोषणा _WRITE_SUMMARY			__WRITE_SUMMARY(PASS_NAME)
#पूर्ण_अगर

#अगर_घोषित NO_READ_OPTIMIZATION_SUMMARY
#घोषणा _READ_OPTIMIZATION_SUMMARY शून्य
#अन्यथा
#घोषणा __READ_OPTIMIZATION_SUMMARY(n)	_GCC_PLUGIN_CONCAT2(n, _पढ़ो_optimization_summary)
#घोषणा _READ_OPTIMIZATION_SUMMARY	__READ_OPTIMIZATION_SUMMARY(PASS_NAME)
#पूर्ण_अगर

#अगर_घोषित NO_WRITE_OPTIMIZATION_SUMMARY
#घोषणा _WRITE_OPTIMIZATION_SUMMARY शून्य
#अन्यथा
#घोषणा __WRITE_OPTIMIZATION_SUMMARY(n)	_GCC_PLUGIN_CONCAT2(n, _ग_लिखो_optimization_summary)
#घोषणा _WRITE_OPTIMIZATION_SUMMARY	__WRITE_OPTIMIZATION_SUMMARY(PASS_NAME)
#पूर्ण_अगर

#अगर_घोषित NO_STMT_FIXUP
#घोषणा _STMT_FIXUP शून्य
#अन्यथा
#घोषणा __STMT_FIXUP(n)			_GCC_PLUGIN_CONCAT2(n, _sपंचांगt_fixup)
#घोषणा _STMT_FIXUP			__STMT_FIXUP(PASS_NAME)
#पूर्ण_अगर

#अगर_घोषित NO_FUNCTION_TRANSFORM
#घोषणा _FUNCTION_TRANSFORM शून्य
#अन्यथा
#घोषणा __FUNCTION_TRANSFORM(n)		_GCC_PLUGIN_CONCAT2(n, _function_transक्रमm)
#घोषणा _FUNCTION_TRANSFORM		__FUNCTION_TRANSFORM(PASS_NAME)
#पूर्ण_अगर

#अगर_घोषित NO_VARIABLE_TRANSFORM
#घोषणा _VARIABLE_TRANSFORM शून्य
#अन्यथा
#घोषणा __VARIABLE_TRANSFORM(n)		_GCC_PLUGIN_CONCAT2(n, _variable_transक्रमm)
#घोषणा _VARIABLE_TRANSFORM		__VARIABLE_TRANSFORM(PASS_NAME)
#पूर्ण_अगर

#अगर_घोषित NO_GATE
#घोषणा _GATE शून्य
#घोषणा _HAS_GATE false
#अन्यथा
#घोषणा __GATE(n)			_GCC_PLUGIN_CONCAT2(n, _gate)
#घोषणा _GATE				__GATE(PASS_NAME)
#घोषणा _HAS_GATE true
#पूर्ण_अगर

#अगर_घोषित NO_EXECUTE
#घोषणा _EXECUTE शून्य
#घोषणा _HAS_EXECUTE false
#अन्यथा
#घोषणा __EXECUTE(n)			_GCC_PLUGIN_CONCAT2(n, _execute)
#घोषणा _EXECUTE			__EXECUTE(PASS_NAME)
#घोषणा _HAS_EXECUTE true
#पूर्ण_अगर

#अगर_अघोषित PROPERTIES_REQUIRED
#घोषणा PROPERTIES_REQUIRED 0
#पूर्ण_अगर

#अगर_अघोषित PROPERTIES_PROVIDED
#घोषणा PROPERTIES_PROVIDED 0
#पूर्ण_अगर

#अगर_अघोषित PROPERTIES_DESTROYED
#घोषणा PROPERTIES_DESTROYED 0
#पूर्ण_अगर

#अगर_अघोषित TODO_FLAGS_START
#घोषणा TODO_FLAGS_START 0
#पूर्ण_अगर

#अगर_अघोषित TODO_FLAGS_FINISH
#घोषणा TODO_FLAGS_FINISH 0
#पूर्ण_अगर

#अगर_अघोषित FUNCTION_TRANSFORM_TODO_FLAGS_START
#घोषणा FUNCTION_TRANSFORM_TODO_FLAGS_START 0
#पूर्ण_अगर

namespace अणु
अटल स्थिर pass_data _PASS_NAME_PASS_DATA = अणु
		.type			= IPA_PASS,
		.name			= _PASS_NAME_NAME,
		.optinfo_flags		= OPTGROUP_NONE,
#अगर BUILDING_GCC_VERSION >= 5000
#या_अगर BUILDING_GCC_VERSION == 4009
		.has_gate		= _HAS_GATE,
		.has_execute		= _HAS_EXECUTE,
#अन्यथा
		.gate			= _GATE,
		.execute		= _EXECUTE,
		.sub			= शून्य,
		.next			= शून्य,
		.अटल_pass_number	= 0,
#पूर्ण_अगर
		.tv_id			= TV_NONE,
		.properties_required	= PROPERTIES_REQUIRED,
		.properties_provided	= PROPERTIES_PROVIDED,
		.properties_destroyed	= PROPERTIES_DESTROYED,
		.toकरो_flags_start	= TODO_FLAGS_START,
		.toकरो_flags_finish	= TODO_FLAGS_FINISH,
पूर्ण;

class _PASS_NAME_PASS : खुला ipa_opt_pass_d अणु
खुला:
	_PASS_NAME_PASS() : ipa_opt_pass_d(_PASS_NAME_PASS_DATA,
			 g,
			 _GENERATE_SUMMARY,
			 _WRITE_SUMMARY,
			 _READ_SUMMARY,
			 _WRITE_OPTIMIZATION_SUMMARY,
			 _READ_OPTIMIZATION_SUMMARY,
			 _STMT_FIXUP,
			 FUNCTION_TRANSFORM_TODO_FLAGS_START,
			 _FUNCTION_TRANSFORM,
			 _VARIABLE_TRANSFORM) अणुपूर्ण

#अगर_अघोषित NO_GATE
#अगर BUILDING_GCC_VERSION >= 5000
	भव bool gate(function *) अणु वापस _GATE(); पूर्ण
#अन्यथा
	भव bool gate(व्योम) अणु वापस _GATE(); पूर्ण
#पूर्ण_अगर

	भव opt_pass *clone() अणु वापस new _PASS_NAME_PASS(); पूर्ण

#अगर_अघोषित NO_EXECUTE
#अगर BUILDING_GCC_VERSION >= 5000
	भव अचिन्हित पूर्णांक execute(function *) अणु वापस _EXECUTE(); पूर्ण
#अन्यथा
	भव अचिन्हित पूर्णांक execute(व्योम) अणु वापस _EXECUTE(); पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;
पूर्ण

opt_pass *_MAKE_PASS_NAME_PASS(व्योम)
अणु
	वापस new _PASS_NAME_PASS();
पूर्ण
#अन्यथा
काष्ठा opt_pass *_MAKE_PASS_NAME_PASS(व्योम)
अणु
	वापस &_PASS_NAME_PASS.pass;
पूर्ण
#पूर्ण_अगर

/* clean up user provided defines */
#अघोषित PASS_NAME
#अघोषित NO_GENERATE_SUMMARY
#अघोषित NO_WRITE_SUMMARY
#अघोषित NO_READ_SUMMARY
#अघोषित NO_WRITE_OPTIMIZATION_SUMMARY
#अघोषित NO_READ_OPTIMIZATION_SUMMARY
#अघोषित NO_STMT_FIXUP
#अघोषित NO_FUNCTION_TRANSFORM
#अघोषित NO_VARIABLE_TRANSFORM
#अघोषित NO_GATE
#अघोषित NO_EXECUTE

#अघोषित FUNCTION_TRANSFORM_TODO_FLAGS_START
#अघोषित PROPERTIES_DESTROYED
#अघोषित PROPERTIES_PROVIDED
#अघोषित PROPERTIES_REQUIRED
#अघोषित TODO_FLAGS_FINISH
#अघोषित TODO_FLAGS_START

/* clean up generated defines */
#अघोषित _EXECUTE
#अघोषित __EXECUTE
#अघोषित _FUNCTION_TRANSFORM
#अघोषित __FUNCTION_TRANSFORM
#अघोषित _GATE
#अघोषित __GATE
#अघोषित _GCC_PLUGIN_CONCAT2
#अघोषित _GCC_PLUGIN_CONCAT3
#अघोषित _GCC_PLUGIN_STRINGIFY
#अघोषित __GCC_PLUGIN_STRINGIFY
#अघोषित _GENERATE_SUMMARY
#अघोषित __GENERATE_SUMMARY
#अघोषित _HAS_EXECUTE
#अघोषित _HAS_GATE
#अघोषित _MAKE_PASS_NAME_PASS
#अघोषित __MAKE_PASS_NAME_PASS
#अघोषित _PASS_NAME_NAME
#अघोषित _PASS_NAME_PASS
#अघोषित __PASS_NAME_PASS
#अघोषित _PASS_NAME_PASS_DATA
#अघोषित __PASS_NAME_PASS_DATA
#अघोषित _READ_OPTIMIZATION_SUMMARY
#अघोषित __READ_OPTIMIZATION_SUMMARY
#अघोषित _READ_SUMMARY
#अघोषित __READ_SUMMARY
#अघोषित _STMT_FIXUP
#अघोषित __STMT_FIXUP
#अघोषित _VARIABLE_TRANSFORM
#अघोषित __VARIABLE_TRANSFORM
#अघोषित _WRITE_OPTIMIZATION_SUMMARY
#अघोषित __WRITE_OPTIMIZATION_SUMMARY
#अघोषित _WRITE_SUMMARY
#अघोषित __WRITE_SUMMARY

#पूर्ण_अगर /* PASS_NAME */
