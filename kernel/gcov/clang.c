<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Google, Inc.
 * modअगरied from kernel/gcov/gcc_4_7.c
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modअगरied under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 * LLVM uses profiling data that's deliberately similar to GCC, but has a
 * very dअगरferent way of exporting that data.  LLVM calls llvm_gcov_init() once
 * per module, and provides a couple of callbacks that we can use to ask क्रम
 * more data.
 *
 * We care about the "writeout" callback, which in turn calls back पूर्णांकo
 * compiler-rt/this module to dump all the gathered coverage data to disk:
 *
 *    llvm_gcda_start_file()
 *      llvm_gcda_emit_function()
 *      llvm_gcda_emit_arcs()
 *      llvm_gcda_emit_function()
 *      llvm_gcda_emit_arcs()
 *      [... repeats क्रम each function ...]
 *    llvm_gcda_summary_info()
 *    llvm_gcda_end_file()
 *
 * This design is much more stateless and unकाष्ठाured than gcc's, and is
 * पूर्णांकended to run at process निकास.  This क्रमces us to keep some local state
 * about which module we're dealing with at the moment.  On the other hand, it
 * also means we करोn't depend as much on how LLVM represents profiling data
 * पूर्णांकernally.
 *
 * See LLVM's lib/Transक्रमms/Instrumentation/GCOVProfiling.cpp क्रम more
 * details on how this works, particularly GCOVProfiler::emitProfileArcs(),
 * GCOVProfiler::insertCounterWriteout(), and
 * GCOVProfiler::insertFlush().
 */

#घोषणा pr_fmt(fmt)	"gcov: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश "gcov.h"

प्रकार व्योम (*llvm_gcov_callback)(व्योम);

काष्ठा gcov_info अणु
	काष्ठा list_head head;

	स्थिर अक्षर *filename;
	अचिन्हित पूर्णांक version;
	u32 checksum;

	काष्ठा list_head functions;
पूर्ण;

काष्ठा gcov_fn_info अणु
	काष्ठा list_head head;

	u32 ident;
	u32 checksum;
	u32 cfg_checksum;

	u32 num_counters;
	u64 *counters;
पूर्ण;

अटल काष्ठा gcov_info *current_info;

अटल LIST_HEAD(clang_gcov_list);

व्योम llvm_gcov_init(llvm_gcov_callback ग_लिखोout, llvm_gcov_callback flush)
अणु
	काष्ठा gcov_info *info = kzalloc(माप(*info), GFP_KERNEL);

	अगर (!info)
		वापस;

	INIT_LIST_HEAD(&info->head);
	INIT_LIST_HEAD(&info->functions);

	mutex_lock(&gcov_lock);

	list_add_tail(&info->head, &clang_gcov_list);
	current_info = info;
	ग_लिखोout();
	current_info = शून्य;
	अगर (gcov_events_enabled)
		gcov_event(GCOV_ADD, info);

	mutex_unlock(&gcov_lock);
पूर्ण
EXPORT_SYMBOL(llvm_gcov_init);

व्योम llvm_gcda_start_file(स्थिर अक्षर *orig_filename, u32 version, u32 checksum)
अणु
	current_info->filename = orig_filename;
	current_info->version = version;
	current_info->checksum = checksum;
पूर्ण
EXPORT_SYMBOL(llvm_gcda_start_file);

व्योम llvm_gcda_emit_function(u32 ident, u32 func_checksum, u32 cfg_checksum)
अणु
	काष्ठा gcov_fn_info *info = kzalloc(माप(*info), GFP_KERNEL);

	अगर (!info)
		वापस;

	INIT_LIST_HEAD(&info->head);
	info->ident = ident;
	info->checksum = func_checksum;
	info->cfg_checksum = cfg_checksum;
	list_add_tail(&info->head, &current_info->functions);
पूर्ण
EXPORT_SYMBOL(llvm_gcda_emit_function);

व्योम llvm_gcda_emit_arcs(u32 num_counters, u64 *counters)
अणु
	काष्ठा gcov_fn_info *info = list_last_entry(&current_info->functions,
			काष्ठा gcov_fn_info, head);

	info->num_counters = num_counters;
	info->counters = counters;
पूर्ण
EXPORT_SYMBOL(llvm_gcda_emit_arcs);

व्योम llvm_gcda_summary_info(व्योम)
अणु
पूर्ण
EXPORT_SYMBOL(llvm_gcda_summary_info);

व्योम llvm_gcda_end_file(व्योम)
अणु
पूर्ण
EXPORT_SYMBOL(llvm_gcda_end_file);

/**
 * gcov_info_filename - वापस info filename
 * @info: profiling data set
 */
स्थिर अक्षर *gcov_info_filename(काष्ठा gcov_info *info)
अणु
	वापस info->filename;
पूर्ण

/**
 * gcov_info_version - वापस info version
 * @info: profiling data set
 */
अचिन्हित पूर्णांक gcov_info_version(काष्ठा gcov_info *info)
अणु
	वापस info->version;
पूर्ण

/**
 * gcov_info_next - वापस next profiling data set
 * @info: profiling data set
 *
 * Returns next gcov_info following @info or first gcov_info in the chain अगर
 * @info is %शून्य.
 */
काष्ठा gcov_info *gcov_info_next(काष्ठा gcov_info *info)
अणु
	अगर (!info)
		वापस list_first_entry_or_null(&clang_gcov_list,
				काष्ठा gcov_info, head);
	अगर (list_is_last(&info->head, &clang_gcov_list))
		वापस शून्य;
	वापस list_next_entry(info, head);
पूर्ण

/**
 * gcov_info_link - link/add profiling data set to the list
 * @info: profiling data set
 */
व्योम gcov_info_link(काष्ठा gcov_info *info)
अणु
	list_add_tail(&info->head, &clang_gcov_list);
पूर्ण

/**
 * gcov_info_unlink - unlink/हटाओ profiling data set from the list
 * @prev: previous profiling data set
 * @info: profiling data set
 */
व्योम gcov_info_unlink(काष्ठा gcov_info *prev, काष्ठा gcov_info *info)
अणु
	/* Generic code unlinks जबतक iterating. */
	__list_del_entry(&info->head);
पूर्ण

/**
 * gcov_info_within_module - check अगर a profiling data set beदीर्घs to a module
 * @info: profiling data set
 * @mod: module
 *
 * Returns true अगर profiling data beदीर्घs module, false otherwise.
 */
bool gcov_info_within_module(काष्ठा gcov_info *info, काष्ठा module *mod)
अणु
	वापस within_module((अचिन्हित दीर्घ)info->filename, mod);
पूर्ण

/* Symbolic links to be created क्रम each profiling data file. */
स्थिर काष्ठा gcov_link gcov_link[] = अणु
	अणु OBJ_TREE, "gcno" पूर्ण,	/* Link to .gcno file in $(objtree). */
	अणु 0, शून्यपूर्ण,
पूर्ण;

/**
 * gcov_info_reset - reset profiling data to zero
 * @info: profiling data set
 */
व्योम gcov_info_reset(काष्ठा gcov_info *info)
अणु
	काष्ठा gcov_fn_info *fn;

	list_क्रम_each_entry(fn, &info->functions, head)
		स_रखो(fn->counters, 0,
				माप(fn->counters[0]) * fn->num_counters);
पूर्ण

/**
 * gcov_info_is_compatible - check अगर profiling data can be added
 * @info1: first profiling data set
 * @info2: second profiling data set
 *
 * Returns non-zero अगर profiling data can be added, zero otherwise.
 */
पूर्णांक gcov_info_is_compatible(काष्ठा gcov_info *info1, काष्ठा gcov_info *info2)
अणु
	काष्ठा gcov_fn_info *fn_ptr1 = list_first_entry_or_null(
			&info1->functions, काष्ठा gcov_fn_info, head);
	काष्ठा gcov_fn_info *fn_ptr2 = list_first_entry_or_null(
			&info2->functions, काष्ठा gcov_fn_info, head);

	अगर (info1->checksum != info2->checksum)
		वापस false;
	अगर (!fn_ptr1)
		वापस fn_ptr1 == fn_ptr2;
	जबतक (!list_is_last(&fn_ptr1->head, &info1->functions) &&
		!list_is_last(&fn_ptr2->head, &info2->functions)) अणु
		अगर (fn_ptr1->checksum != fn_ptr2->checksum)
			वापस false;
		अगर (fn_ptr1->cfg_checksum != fn_ptr2->cfg_checksum)
			वापस false;
		fn_ptr1 = list_next_entry(fn_ptr1, head);
		fn_ptr2 = list_next_entry(fn_ptr2, head);
	पूर्ण
	वापस list_is_last(&fn_ptr1->head, &info1->functions) &&
		list_is_last(&fn_ptr2->head, &info2->functions);
पूर्ण

/**
 * gcov_info_add - add up profiling data
 * @dest: profiling data set to which data is added
 * @source: profiling data set which is added
 *
 * Adds profiling counts of @source to @dest.
 */
व्योम gcov_info_add(काष्ठा gcov_info *dst, काष्ठा gcov_info *src)
अणु
	काष्ठा gcov_fn_info *dfn_ptr;
	काष्ठा gcov_fn_info *sfn_ptr = list_first_entry_or_null(&src->functions,
			काष्ठा gcov_fn_info, head);

	list_क्रम_each_entry(dfn_ptr, &dst->functions, head) अणु
		u32 i;

		क्रम (i = 0; i < sfn_ptr->num_counters; i++)
			dfn_ptr->counters[i] += sfn_ptr->counters[i];
	पूर्ण
पूर्ण

अटल काष्ठा gcov_fn_info *gcov_fn_info_dup(काष्ठा gcov_fn_info *fn)
अणु
	माप_प्रकार cv_size; /* counter values size */
	काष्ठा gcov_fn_info *fn_dup = kmemdup(fn, माप(*fn),
			GFP_KERNEL);
	अगर (!fn_dup)
		वापस शून्य;
	INIT_LIST_HEAD(&fn_dup->head);

	cv_size = fn->num_counters * माप(fn->counters[0]);
	fn_dup->counters = kvदो_स्मृति(cv_size, GFP_KERNEL);
	अगर (!fn_dup->counters) अणु
		kमुक्त(fn_dup);
		वापस शून्य;
	पूर्ण

	स_नकल(fn_dup->counters, fn->counters, cv_size);

	वापस fn_dup;
पूर्ण

/**
 * gcov_info_dup - duplicate profiling data set
 * @info: profiling data set to duplicate
 *
 * Return newly allocated duplicate on success, %शून्य on error.
 */
काष्ठा gcov_info *gcov_info_dup(काष्ठा gcov_info *info)
अणु
	काष्ठा gcov_info *dup;
	काष्ठा gcov_fn_info *fn;

	dup = kmemdup(info, माप(*dup), GFP_KERNEL);
	अगर (!dup)
		वापस शून्य;
	INIT_LIST_HEAD(&dup->head);
	INIT_LIST_HEAD(&dup->functions);
	dup->filename = kstrdup(info->filename, GFP_KERNEL);
	अगर (!dup->filename)
		जाओ err;

	list_क्रम_each_entry(fn, &info->functions, head) अणु
		काष्ठा gcov_fn_info *fn_dup = gcov_fn_info_dup(fn);

		अगर (!fn_dup)
			जाओ err;
		list_add_tail(&fn_dup->head, &dup->functions);
	पूर्ण

	वापस dup;

err:
	gcov_info_मुक्त(dup);
	वापस शून्य;
पूर्ण

/**
 * gcov_info_मुक्त - release memory क्रम profiling data set duplicate
 * @info: profiling data set duplicate to मुक्त
 */
व्योम gcov_info_मुक्त(काष्ठा gcov_info *info)
अणु
	काष्ठा gcov_fn_info *fn, *पंचांगp;

	list_क्रम_each_entry_safe(fn, पंचांगp, &info->functions, head) अणु
		kvमुक्त(fn->counters);
		list_del(&fn->head);
		kमुक्त(fn);
	पूर्ण
	kमुक्त(info->filename);
	kमुक्त(info);
पूर्ण

/**
 * convert_to_gcda - convert profiling data set to gcda file क्रमmat
 * @buffer: the buffer to store file data or %शून्य अगर no data should be stored
 * @info: profiling data set to be converted
 *
 * Returns the number of bytes that were/would have been stored पूर्णांकo the buffer.
 */
माप_प्रकार convert_to_gcda(अक्षर *buffer, काष्ठा gcov_info *info)
अणु
	काष्ठा gcov_fn_info *fi_ptr;
	माप_प्रकार pos = 0;

	/* File header. */
	pos += store_gcov_u32(buffer, pos, GCOV_DATA_MAGIC);
	pos += store_gcov_u32(buffer, pos, info->version);
	pos += store_gcov_u32(buffer, pos, info->checksum);

	list_क्रम_each_entry(fi_ptr, &info->functions, head) अणु
		u32 i;

		pos += store_gcov_u32(buffer, pos, GCOV_TAG_FUNCTION);
		pos += store_gcov_u32(buffer, pos, 3);
		pos += store_gcov_u32(buffer, pos, fi_ptr->ident);
		pos += store_gcov_u32(buffer, pos, fi_ptr->checksum);
		pos += store_gcov_u32(buffer, pos, fi_ptr->cfg_checksum);
		pos += store_gcov_u32(buffer, pos, GCOV_TAG_COUNTER_BASE);
		pos += store_gcov_u32(buffer, pos, fi_ptr->num_counters * 2);
		क्रम (i = 0; i < fi_ptr->num_counters; i++)
			pos += store_gcov_u64(buffer, pos, fi_ptr->counters[i]);
	पूर्ण

	वापस pos;
पूर्ण
