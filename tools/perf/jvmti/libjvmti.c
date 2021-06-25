<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <sys/types.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <err.h>
#समावेश <jvmti.h>
#अगर_घोषित HAVE_JVMTI_CMLR
#समावेश <jvmticmlr.h>
#पूर्ण_अगर
#समावेश <सीमा.स>

#समावेश "jvmti_agent.h"

अटल पूर्णांक has_line_numbers;
व्योम *jvmti_agent;

अटल व्योम prपूर्णांक_error(jvmtiEnv *jvmti, स्थिर अक्षर *msg, jvmtiError ret)
अणु
	अक्षर *err_msg = शून्य;
	jvmtiError err;
	err = (*jvmti)->GetErrorName(jvmti, ret, &err_msg);
	अगर (err == JVMTI_ERROR_NONE) अणु
		warnx("%s failed with %s", msg, err_msg);
		(*jvmti)->Deallocate(jvmti, (अचिन्हित अक्षर *)err_msg);
	पूर्ण अन्यथा अणु
		warnx("%s failed with an unknown error %d", msg, ret);
	पूर्ण
पूर्ण

#अगर_घोषित HAVE_JVMTI_CMLR
अटल jvmtiError
करो_get_line_number(jvmtiEnv *jvmti, व्योम *pc, jmethodID m, jपूर्णांक bci,
		   jvmti_line_info_t *tab)
अणु
	jपूर्णांक i, nr_lines = 0;
	jvmtiLineNumberEntry *loc_tab = शून्य;
	jvmtiError ret;
	jपूर्णांक src_line = -1;

	ret = (*jvmti)->GetLineNumberTable(jvmti, m, &nr_lines, &loc_tab);
	अगर (ret == JVMTI_ERROR_ABSENT_INFORMATION || ret == JVMTI_ERROR_NATIVE_METHOD) अणु
		/* No debug inक्रमmation क्रम this method */
		वापस ret;
	पूर्ण अन्यथा अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "GetLineNumberTable", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < nr_lines && loc_tab[i].start_location <= bci; i++) अणु
		src_line = i;
	पूर्ण

	अगर (src_line != -1) अणु
		tab->pc = (अचिन्हित दीर्घ)pc;
		tab->line_number = loc_tab[src_line].line_number;
		tab->discrim = 0; /* not yet used */
		tab->methodID = m;

		ret = JVMTI_ERROR_NONE;
	पूर्ण अन्यथा अणु
		ret = JVMTI_ERROR_ABSENT_INFORMATION;
	पूर्ण

	(*jvmti)->Deallocate(jvmti, (अचिन्हित अक्षर *)loc_tab);

	वापस ret;
पूर्ण

अटल jvmtiError
get_line_numbers(jvmtiEnv *jvmti, स्थिर व्योम *compile_info, jvmti_line_info_t **tab, पूर्णांक *nr_lines)
अणु
	स्थिर jvmtiCompiledMethodLoadRecordHeader *hdr;
	jvmtiCompiledMethodLoadInlineRecord *rec;
	PCStackInfo *c;
	jपूर्णांक ret;
	पूर्णांक nr_total = 0;
	पूर्णांक i, lines_total = 0;

	अगर (!(tab && nr_lines))
		वापस JVMTI_ERROR_शून्य_POINTER;

	/*
	 * Phase 1 -- get the number of lines necessary
	 */
	क्रम (hdr = compile_info; hdr != शून्य; hdr = hdr->next) अणु
		अगर (hdr->kind == JVMTI_CMLR_INLINE_INFO) अणु
			rec = (jvmtiCompiledMethodLoadInlineRecord *)hdr;
			nr_total += rec->numpcs;
		पूर्ण
	पूर्ण

	अगर (nr_total == 0)
		वापस JVMTI_ERROR_NOT_FOUND;

	/*
	 * Phase 2 -- allocate big enough line table
	 */
	*tab = दो_स्मृति(nr_total * माप(**tab));
	अगर (!*tab)
		वापस JVMTI_ERROR_OUT_OF_MEMORY;

	क्रम (hdr = compile_info; hdr != शून्य; hdr = hdr->next) अणु
		अगर (hdr->kind == JVMTI_CMLR_INLINE_INFO) अणु
			rec = (jvmtiCompiledMethodLoadInlineRecord *)hdr;
			क्रम (i = 0; i < rec->numpcs; i++) अणु
				c = rec->pcinfo + i;
                                /*
                                 * c->methods is the stack of अंतरभूतd method calls
                                 * at c->pc. [0] is the leaf method. Caller frames
                                 * are ignored at the moment.
                                 */
				ret = करो_get_line_number(jvmti, c->pc,
							 c->methods[0],
							 c->bcis[0],
							 *tab + lines_total);
				अगर (ret == JVMTI_ERROR_NONE)
					lines_total++;
			पूर्ण
		पूर्ण
	पूर्ण
	*nr_lines = lines_total;
	वापस JVMTI_ERROR_NONE;
पूर्ण
#अन्यथा /* HAVE_JVMTI_CMLR */

अटल jvmtiError
get_line_numbers(jvmtiEnv *jvmti __maybe_unused, स्थिर व्योम *compile_info __maybe_unused,
		 jvmti_line_info_t **tab __maybe_unused, पूर्णांक *nr_lines __maybe_unused)
अणु
	वापस JVMTI_ERROR_NONE;
पूर्ण
#पूर्ण_अगर /* HAVE_JVMTI_CMLR */

अटल व्योम
copy_class_filename(स्थिर अक्षर * class_sign, स्थिर अक्षर * file_name, अक्षर * result, माप_प्रकार max_length)
अणु
	/*
	* Assume path name is class hierarchy, this is a common practice with Java programs
	*/
	अगर (*class_sign == 'L') अणु
		पूर्णांक j, i = 0;
		अक्षर *p = म_खोजप(class_sign, '/');
		अगर (p) अणु
			/* drop the 'L' prefix and copy up to the final '/' */
			क्रम (i = 0; i < (p - class_sign); i++)
				result[i] = class_sign[i+1];
		पूर्ण
		/*
		* append file name, we use loops and not string ops to aव्योम modअगरying
		* class_sign which is used later क्रम the symbol name
		*/
		क्रम (j = 0; i < (max_length - 1) && file_name && j < म_माप(file_name); j++, i++)
			result[i] = file_name[j];

		result[i] = '\0';
	पूर्ण अन्यथा अणु
		/* fallback हाल */
		strlcpy(result, file_name, max_length);
	पूर्ण
पूर्ण

अटल jvmtiError
get_source_filename(jvmtiEnv *jvmti, jmethodID methodID, अक्षर ** buffer)
अणु
	jvmtiError ret;
	jclass decl_class;
	अक्षर *file_name = शून्य;
	अक्षर *class_sign = शून्य;
	अक्षर fn[PATH_MAX];
	माप_प्रकार len;

	ret = (*jvmti)->GetMethodDeclaringClass(jvmti, methodID, &decl_class);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "GetMethodDeclaringClass", ret);
		वापस ret;
	पूर्ण

	ret = (*jvmti)->GetSourceFileName(jvmti, decl_class, &file_name);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "GetSourceFileName", ret);
		वापस ret;
	पूर्ण

	ret = (*jvmti)->GetClassSignature(jvmti, decl_class, &class_sign, शून्य);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "GetClassSignature", ret);
		जाओ मुक्त_file_name_error;
	पूर्ण

	copy_class_filename(class_sign, file_name, fn, PATH_MAX);
	len = म_माप(fn);
	*buffer = दो_स्मृति((len + 1) * माप(अक्षर));
	अगर (!*buffer) अणु
		prपूर्णांक_error(jvmti, "GetClassSignature", ret);
		ret = JVMTI_ERROR_OUT_OF_MEMORY;
		जाओ मुक्त_class_sign_error;
	पूर्ण
	म_नकल(*buffer, fn);
	ret = JVMTI_ERROR_NONE;

मुक्त_class_sign_error:
	(*jvmti)->Deallocate(jvmti, (अचिन्हित अक्षर *)class_sign);
मुक्त_file_name_error:
	(*jvmti)->Deallocate(jvmti, (अचिन्हित अक्षर *)file_name);

	वापस ret;
पूर्ण

अटल jvmtiError
fill_source_filenames(jvmtiEnv *jvmti, पूर्णांक nr_lines,
		      स्थिर jvmti_line_info_t * line_tab,
		      अक्षर ** file_names)
अणु
	पूर्णांक index;
	jvmtiError ret;

	क्रम (index = 0; index < nr_lines; ++index) अणु
		ret = get_source_filename(jvmti, line_tab[index].methodID, &(file_names[index]));
		अगर (ret != JVMTI_ERROR_NONE)
			वापस ret;
	पूर्ण

	वापस JVMTI_ERROR_NONE;
पूर्ण

अटल व्योम JNICALL
compiled_method_load_cb(jvmtiEnv *jvmti,
			jmethodID method,
			jपूर्णांक code_size,
			व्योम स्थिर *code_addr,
			jपूर्णांक map_length,
			jvmtiAddrLocationMap स्थिर *map,
			स्थिर व्योम *compile_info)
अणु
	jvmti_line_info_t *line_tab = शून्य;
	अक्षर ** line_file_names = शून्य;
	jclass decl_class;
	अक्षर *class_sign = शून्य;
	अक्षर *func_name = शून्य;
	अक्षर *func_sign = शून्य;
	uपूर्णांक64_t addr = (uपूर्णांक64_t)(uपूर्णांकptr_t)code_addr;
	jvmtiError ret;
	पूर्णांक nr_lines = 0; /* in line_tab[] */
	माप_प्रकार len;
	पूर्णांक output_debug_info = 0;

	ret = (*jvmti)->GetMethodDeclaringClass(jvmti, method,
						&decl_class);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "GetMethodDeclaringClass", ret);
		वापस;
	पूर्ण

	अगर (has_line_numbers && map && map_length) अणु
		ret = get_line_numbers(jvmti, compile_info, &line_tab, &nr_lines);
		अगर (ret != JVMTI_ERROR_NONE) अणु
			अगर (ret != JVMTI_ERROR_NOT_FOUND) अणु
				warnx("jvmti: cannot get line table for method");
			पूर्ण
			nr_lines = 0;
		पूर्ण अन्यथा अगर (nr_lines > 0) अणु
			line_file_names = दो_स्मृति(माप(अक्षर*) * nr_lines);
			अगर (!line_file_names) अणु
				warnx("jvmti: cannot allocate space for line table method names");
			पूर्ण अन्यथा अणु
				स_रखो(line_file_names, 0, माप(अक्षर*) * nr_lines);
				ret = fill_source_filenames(jvmti, nr_lines, line_tab, line_file_names);
				अगर (ret != JVMTI_ERROR_NONE) अणु
					warnx("jvmti: fill_source_filenames failed");
				पूर्ण अन्यथा अणु
					output_debug_info = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ret = (*jvmti)->GetClassSignature(jvmti, decl_class,
					  &class_sign, शून्य);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "GetClassSignature", ret);
		जाओ error;
	पूर्ण

	ret = (*jvmti)->GetMethodName(jvmti, method, &func_name,
				      &func_sign, शून्य);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "GetMethodName", ret);
		जाओ error;
	पूर्ण

	/*
	 * ग_लिखो source line info record अगर we have it
	 */
	अगर (output_debug_info)
		अगर (jvmti_ग_लिखो_debug_info(jvmti_agent, addr, nr_lines, line_tab, (स्थिर अक्षर * स्थिर *) line_file_names))
			warnx("jvmti: write_debug_info() failed");

	len = म_माप(func_name) + म_माप(class_sign) + म_माप(func_sign) + 2;
	अणु
		अक्षर str[len];
		snम_लिखो(str, len, "%s%s%s", class_sign, func_name, func_sign);

		अगर (jvmti_ग_लिखो_code(jvmti_agent, str, addr, code_addr, code_size))
			warnx("jvmti: write_code() failed");
	पूर्ण
error:
	(*jvmti)->Deallocate(jvmti, (अचिन्हित अक्षर *)func_name);
	(*jvmti)->Deallocate(jvmti, (अचिन्हित अक्षर *)func_sign);
	(*jvmti)->Deallocate(jvmti, (अचिन्हित अक्षर *)class_sign);
	मुक्त(line_tab);
	जबतक (line_file_names && (nr_lines > 0)) अणु
	    अगर (line_file_names[nr_lines - 1]) अणु
	        मुक्त(line_file_names[nr_lines - 1]);
	    पूर्ण
	    nr_lines -= 1;
	पूर्ण
	मुक्त(line_file_names);
पूर्ण

अटल व्योम JNICALL
code_generated_cb(jvmtiEnv *jvmti,
		  अक्षर स्थिर *name,
		  व्योम स्थिर *code_addr,
		  jपूर्णांक code_size)
अणु
	uपूर्णांक64_t addr = (uपूर्णांक64_t)(अचिन्हित दीर्घ)code_addr;
	पूर्णांक ret;

	ret = jvmti_ग_लिखो_code(jvmti_agent, name, addr, code_addr, code_size);
	अगर (ret)
		warnx("jvmti: write_code() failed for code_generated");
पूर्ण

JNIEXPORT jपूर्णांक JNICALL
Agent_OnLoad(JavaVM *jvm, अक्षर *options, व्योम *reserved __maybe_unused)
अणु
	jvmtiEventCallbacks cb;
	jvmtiCapabilities caps1;
	jvmtiJlocationFormat क्रमmat;
	jvmtiEnv *jvmti = शून्य;
	jपूर्णांक ret;

	jvmti_agent = jvmti_खोलो();
	अगर (!jvmti_agent) अणु
		warnx("jvmti: open_agent failed");
		वापस -1;
	पूर्ण

	/*
	 * Request a JVMTI पूर्णांकerface version 1 environment
	 */
	ret = (*jvm)->GetEnv(jvm, (व्योम *)&jvmti, JVMTI_VERSION_1);
	अगर (ret != JNI_OK) अणु
		warnx("jvmti: jvmti version 1 not supported");
		वापस -1;
	पूर्ण

	/*
	 * acquire method_load capability, we require it
	 * request line numbers (optional)
	 */
	स_रखो(&caps1, 0, माप(caps1));
	caps1.can_generate_compiled_method_load_events = 1;

	ret = (*jvmti)->AddCapabilities(jvmti, &caps1);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "AddCapabilities", ret);
		वापस -1;
	पूर्ण
	ret = (*jvmti)->GetJLocationFormat(jvmti, &क्रमmat);
        अगर (ret == JVMTI_ERROR_NONE && क्रमmat == JVMTI_JLOCATION_JVMBCI) अणु
                स_रखो(&caps1, 0, माप(caps1));
                caps1.can_get_line_numbers = 1;
                caps1.can_get_source_file_name = 1;
		ret = (*jvmti)->AddCapabilities(jvmti, &caps1);
                अगर (ret == JVMTI_ERROR_NONE)
                        has_line_numbers = 1;
        पूर्ण अन्यथा अगर (ret != JVMTI_ERROR_NONE)
		prपूर्णांक_error(jvmti, "GetJLocationFormat", ret);


	स_रखो(&cb, 0, माप(cb));

	cb.CompiledMethodLoad   = compiled_method_load_cb;
	cb.DynamicCodeGenerated = code_generated_cb;

	ret = (*jvmti)->SetEventCallbacks(jvmti, &cb, माप(cb));
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "SetEventCallbacks", ret);
		वापस -1;
	पूर्ण

	ret = (*jvmti)->SetEventNotअगरicationMode(jvmti, JVMTI_ENABLE,
			JVMTI_EVENT_COMPILED_METHOD_LOAD, शून्य);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "SetEventNotificationMode(METHOD_LOAD)", ret);
		वापस -1;
	पूर्ण

	ret = (*jvmti)->SetEventNotअगरicationMode(jvmti, JVMTI_ENABLE,
			JVMTI_EVENT_DYNAMIC_CODE_GENERATED, शून्य);
	अगर (ret != JVMTI_ERROR_NONE) अणु
		prपूर्णांक_error(jvmti, "SetEventNotificationMode(CODE_GENERATED)", ret);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

JNIEXPORT व्योम JNICALL
Agent_OnUnload(JavaVM *jvm __maybe_unused)
अणु
	पूर्णांक ret;

	ret = jvmti_बंद(jvmti_agent);
	अगर (ret)
		errx(1, "Error: op_close_agent()");
पूर्ण
