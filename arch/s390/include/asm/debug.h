<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *   S/390 debug facility
 *
 *    Copyright IBM Corp. 1999, 2020
 */
#अगर_अघोषित DEBUG_H
#घोषणा DEBUG_H

#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/refcount.h>
#समावेश <linux/fs.h>

#घोषणा DEBUG_MAX_LEVEL		   6  /* debug levels range from 0 to 6 */
#घोषणा DEBUG_OFF_LEVEL		   -1 /* level where debug is चयनed off */
#घोषणा DEBUG_FLUSH_ALL		   -1 /* parameter to flush all areas */
#घोषणा DEBUG_MAX_VIEWS		   10 /* max number of views in proc fs */
#घोषणा DEBUG_MAX_NAME_LEN	   64 /* max length क्रम a debugfs file name */
#घोषणा DEBUG_DEFAULT_LEVEL	   3  /* initial debug level */

#घोषणा DEBUG_सूची_ROOT "s390dbf" /* name of debug root directory in proc fs */

#घोषणा DEBUG_DATA(entry) (अक्षर *)(entry + 1) /* data is stored behind */
					      /* the entry inक्रमmation */

#घोषणा __DEBUG_FEATURE_VERSION	   3  /* version of debug feature */

काष्ठा __debug_entry अणु
	अचिन्हित दीर्घ घड़ी	: 60;
	अचिन्हित दीर्घ exception	:  1;
	अचिन्हित दीर्घ level	:  3;
	व्योम *caller;
	अचिन्हित लघु cpu;
पूर्ण __packed;

प्रकार काष्ठा __debug_entry debug_entry_t;

काष्ठा debug_view;

प्रकार काष्ठा debug_info अणु
	काष्ठा debug_info *next;
	काष्ठा debug_info *prev;
	refcount_t ref_count;
	spinlock_t lock;
	पूर्णांक level;
	पूर्णांक nr_areas;
	पूर्णांक pages_per_area;
	पूर्णांक buf_size;
	पूर्णांक entry_size;
	debug_entry_t ***areas;
	पूर्णांक active_area;
	पूर्णांक *active_pages;
	पूर्णांक *active_entries;
	काष्ठा dentry *debugfs_root_entry;
	काष्ठा dentry *debugfs_entries[DEBUG_MAX_VIEWS];
	काष्ठा debug_view *views[DEBUG_MAX_VIEWS];
	अक्षर name[DEBUG_MAX_NAME_LEN];
	umode_t mode;
पूर्ण debug_info_t;

प्रकार पूर्णांक (debug_header_proc_t) (debug_info_t *id,
				   काष्ठा debug_view *view,
				   पूर्णांक area,
				   debug_entry_t *entry,
				   अक्षर *out_buf);

प्रकार पूर्णांक (debug_क्रमmat_proc_t) (debug_info_t *id,
				   काष्ठा debug_view *view, अक्षर *out_buf,
				   स्थिर अक्षर *in_buf);
प्रकार पूर्णांक (debug_prolog_proc_t) (debug_info_t *id,
				   काष्ठा debug_view *view,
				   अक्षर *out_buf);
प्रकार पूर्णांक (debug_input_proc_t) (debug_info_t *id,
				  काष्ठा debug_view *view,
				  काष्ठा file *file,
				  स्थिर अक्षर __user *user_buf,
				  माप_प्रकार in_buf_size, loff_t *offset);

पूर्णांक debug_dflt_header_fn(debug_info_t *id, काष्ठा debug_view *view,
			 पूर्णांक area, debug_entry_t *entry, अक्षर *out_buf);

काष्ठा debug_view अणु
	अक्षर name[DEBUG_MAX_NAME_LEN];
	debug_prolog_proc_t *prolog_proc;
	debug_header_proc_t *header_proc;
	debug_क्रमmat_proc_t *क्रमmat_proc;
	debug_input_proc_t  *input_proc;
	व्योम		    *निजी_data;
पूर्ण;

बाह्य काष्ठा debug_view debug_hex_ascii_view;
बाह्य काष्ठा debug_view debug_प्र_लिखो_view;

/* करो NOT use the _common functions */

debug_entry_t *debug_event_common(debug_info_t *id, पूर्णांक level,
				  स्थिर व्योम *data, पूर्णांक length);

debug_entry_t *debug_exception_common(debug_info_t *id, पूर्णांक level,
				      स्थिर व्योम *data, पूर्णांक length);

/* Debug Feature API: */

debug_info_t *debug_रेजिस्टर(स्थिर अक्षर *name, पूर्णांक pages, पूर्णांक nr_areas,
			     पूर्णांक buf_size);

debug_info_t *debug_रेजिस्टर_mode(स्थिर अक्षर *name, पूर्णांक pages, पूर्णांक nr_areas,
				  पूर्णांक buf_size, umode_t mode, uid_t uid,
				  gid_t gid);

व्योम debug_unरेजिस्टर(debug_info_t *id);

व्योम debug_set_level(debug_info_t *id, पूर्णांक new_level);

व्योम debug_set_critical(व्योम);

व्योम debug_stop_all(व्योम);

/**
 * debug_level_enabled() - Returns true अगर debug events क्रम the specअगरied
 *			   level would be logged. Otherwise वापसs false.
 *
 * @id:		handle क्रम debug log
 * @level:	debug level
 *
 * Return:
 * - %true अगर level is less or equal to the current debug level.
 */
अटल अंतरभूत bool debug_level_enabled(debug_info_t *id, पूर्णांक level)
अणु
	वापस level <= id->level;
पूर्ण

/**
 * debug_event() - ग_लिखोs binary debug entry to active debug area
 *		   (अगर level <= actual debug level)
 *
 * @id:		handle क्रम debug log
 * @level:	debug level
 * @data:	poपूर्णांकer to data क्रम debug entry
 * @length:	length of data in bytes
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 */
अटल अंतरभूत debug_entry_t *debug_event(debug_info_t *id, पूर्णांक level,
					 व्योम *data, पूर्णांक length)
अणु
	अगर ((!id) || (level > id->level) || (id->pages_per_area == 0))
		वापस शून्य;
	वापस debug_event_common(id, level, data, length);
पूर्ण

/**
 * debug_पूर्णांक_event() - ग_लिखोs अचिन्हित पूर्णांकeger debug entry to active debug area
 *		       (अगर level <= actual debug level)
 *
 * @id:		handle क्रम debug log
 * @level:	debug level
 * @tag:	पूर्णांकeger value क्रम debug entry
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 */
अटल अंतरभूत debug_entry_t *debug_पूर्णांक_event(debug_info_t *id, पूर्णांक level,
					     अचिन्हित पूर्णांक tag)
अणु
	अचिन्हित पूर्णांक t = tag;

	अगर ((!id) || (level > id->level) || (id->pages_per_area == 0))
		वापस शून्य;
	वापस debug_event_common(id, level, &t, माप(अचिन्हित पूर्णांक));
पूर्ण

/**
 * debug_दीर्घ_event() - ग_लिखोs अचिन्हित दीर्घ debug entry to active debug area
 *		       (अगर level <= actual debug level)
 *
 * @id:		handle क्रम debug log
 * @level:	debug level
 * @tag:	दीर्घ पूर्णांकeger value क्रम debug entry
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 */
अटल अंतरभूत debug_entry_t *debug_दीर्घ_event(debug_info_t *id, पूर्णांक level,
					      अचिन्हित दीर्घ tag)
अणु
	अचिन्हित दीर्घ t = tag;

	अगर ((!id) || (level > id->level) || (id->pages_per_area == 0))
		वापस शून्य;
	वापस debug_event_common(id, level, &t, माप(अचिन्हित दीर्घ));
पूर्ण

/**
 * debug_text_event() - ग_लिखोs string debug entry in ascii क्रमmat to active
 *			debug area (अगर level <= actual debug level)
 *
 * @id:		handle क्रम debug log
 * @level:	debug level
 * @txt:	string क्रम debug entry
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 */
अटल अंतरभूत debug_entry_t *debug_text_event(debug_info_t *id, पूर्णांक level,
					      स्थिर अक्षर *txt)
अणु
	अगर ((!id) || (level > id->level) || (id->pages_per_area == 0))
		वापस शून्य;
	वापस debug_event_common(id, level, txt, म_माप(txt));
पूर्ण

/*
 * IMPORTANT: Use "%s" in प्र_लिखो क्रमmat strings with care! Only poपूर्णांकers are
 * stored in the s390dbf. See Documentation/s390/s390dbf.rst क्रम more details!
 */
बाह्य debug_entry_t *
__debug_प्र_लिखो_event(debug_info_t *id, पूर्णांक level, अक्षर *string, ...)
	__attribute__ ((क्रमmat(म_लिखो, 3, 4)));

/**
 * debug_प्र_लिखो_event() - ग_लिखोs debug entry with क्रमmat string
 *			   and varargs (दीर्घs) to active debug area
 *			   (अगर level $<=$ actual debug level).
 *
 * @_id:	handle क्रम debug log
 * @_level:	debug level
 * @_fmt:	क्रमmat string क्रम debug entry
 * @...:	varargs used as in प्र_लिखो()
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 *
 * भग्नs and दीर्घ दीर्घ datatypes cannot be used as varargs.
 */
#घोषणा debug_प्र_लिखो_event(_id, _level, _fmt, ...)			\
(अणु									\
	debug_entry_t *__ret;						\
	debug_info_t *__id = _id;					\
	पूर्णांक __level = _level;						\
									\
	अगर ((!__id) || (__level > __id->level))				\
		__ret = शून्य;						\
	अन्यथा								\
		__ret = __debug_प्र_लिखो_event(__id, __level,		\
					      _fmt, ## __VA_ARGS__);	\
	__ret;								\
पूर्ण)

/**
 * debug_exception() - ग_लिखोs binary debug entry to active debug area
 *		       (अगर level <= actual debug level)
 *		       and चयनes to next debug area
 *
 * @id:		handle क्रम debug log
 * @level:	debug level
 * @data:	poपूर्णांकer to data क्रम debug entry
 * @length:	length of data in bytes
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 */
अटल अंतरभूत debug_entry_t *debug_exception(debug_info_t *id, पूर्णांक level,
					     व्योम *data, पूर्णांक length)
अणु
	अगर ((!id) || (level > id->level) || (id->pages_per_area == 0))
		वापस शून्य;
	वापस debug_exception_common(id, level, data, length);
पूर्ण

/**
 * debug_पूर्णांक_exception() - ग_लिखोs अचिन्हित पूर्णांक debug entry to active debug area
 *			   (अगर level <= actual debug level)
 *			   and चयनes to next debug area
 *
 * @id:		handle क्रम debug log
 * @level:	debug level
 * @tag:	पूर्णांकeger value क्रम debug entry
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 */
अटल अंतरभूत debug_entry_t *debug_पूर्णांक_exception(debug_info_t *id, पूर्णांक level,
						 अचिन्हित पूर्णांक tag)
अणु
	अचिन्हित पूर्णांक t = tag;

	अगर ((!id) || (level > id->level) || (id->pages_per_area == 0))
		वापस शून्य;
	वापस debug_exception_common(id, level, &t, माप(अचिन्हित पूर्णांक));
पूर्ण

/**
 * debug_दीर्घ_exception() - ग_लिखोs दीर्घ debug entry to active debug area
 *			   (अगर level <= actual debug level)
 *			   and चयनes to next debug area
 *
 * @id:		handle क्रम debug log
 * @level:	debug level
 * @tag:	दीर्घ पूर्णांकeger value क्रम debug entry
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 */
अटल अंतरभूत debug_entry_t *debug_दीर्घ_exception (debug_info_t *id, पूर्णांक level,
						   अचिन्हित दीर्घ tag)
अणु
	अचिन्हित दीर्घ t = tag;

	अगर ((!id) || (level > id->level) || (id->pages_per_area == 0))
		वापस शून्य;
	वापस debug_exception_common(id, level, &t, माप(अचिन्हित दीर्घ));
पूर्ण

/**
 * debug_text_exception() - ग_लिखोs string debug entry in ascii क्रमmat to active
 *			    debug area (अगर level <= actual debug level)
 *			    and चयनes to next debug area
 * area
 *
 * @id:	handle क्रम debug log
 * @level:	debug level
 * @txt:	string क्रम debug entry
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 */
अटल अंतरभूत debug_entry_t *debug_text_exception(debug_info_t *id, पूर्णांक level,
						  स्थिर अक्षर *txt)
अणु
	अगर ((!id) || (level > id->level) || (id->pages_per_area == 0))
		वापस शून्य;
	वापस debug_exception_common(id, level, txt, म_माप(txt));
पूर्ण

/*
 * IMPORTANT: Use "%s" in प्र_लिखो क्रमmat strings with care! Only poपूर्णांकers are
 * stored in the s390dbf. See Documentation/s390/s390dbf.rst क्रम more details!
 */
बाह्य debug_entry_t *
__debug_प्र_लिखो_exception(debug_info_t *id, पूर्णांक level, अक्षर *string, ...)
	__attribute__ ((क्रमmat(म_लिखो, 3, 4)));


/**
 * debug_प्र_लिखो_exception() - ग_लिखोs debug entry with क्रमmat string and
 *			       varargs (दीर्घs) to active debug area
 *			       (अगर level <= actual debug level)
 *			       and चयनes to next debug area.
 *
 * @_id:	handle क्रम debug log
 * @_level:	debug level
 * @_fmt:	क्रमmat string क्रम debug entry
 * @...:	varargs used as in प्र_लिखो()
 *
 * Return:
 * - Address of written debug entry
 * - %शून्य अगर error
 *
 * भग्नs and दीर्घ दीर्घ datatypes cannot be used as varargs.
 */
#घोषणा debug_प्र_लिखो_exception(_id, _level, _fmt, ...)			\
(अणु									\
	debug_entry_t *__ret;						\
	debug_info_t *__id = _id;					\
	पूर्णांक __level = _level;						\
									\
	अगर ((!__id) || (__level > __id->level))				\
		__ret = शून्य;						\
	अन्यथा								\
		__ret = __debug_प्र_लिखो_exception(__id, __level,	\
						  _fmt, ## __VA_ARGS__);\
	__ret;								\
पूर्ण)

पूर्णांक debug_रेजिस्टर_view(debug_info_t *id, काष्ठा debug_view *view);

पूर्णांक debug_unरेजिस्टर_view(debug_info_t *id, काष्ठा debug_view *view);

/*
   define the debug levels:
   - 0 No debugging output to console or syslog
   - 1 Log पूर्णांकernal errors to syslog, ignore check conditions
   - 2 Log पूर्णांकernal errors and check conditions to syslog
   - 3 Log पूर्णांकernal errors to console, log check conditions to syslog
   - 4 Log पूर्णांकernal errors and check conditions to console
   - 5 panic on पूर्णांकernal errors, log check conditions to console
   - 6 panic on both, पूर्णांकernal errors and check conditions
 */

#अगर_अघोषित DEBUG_LEVEL
#घोषणा DEBUG_LEVEL 4
#पूर्ण_अगर

#घोषणा INTERNAL_ERRMSG(x,y...) "E" __खाता__ "%d: " x, __LINE__, y
#घोषणा INTERNAL_WRNMSG(x,y...) "W" __खाता__ "%d: " x, __LINE__, y
#घोषणा INTERNAL_INFMSG(x,y...) "I" __खाता__ "%d: " x, __LINE__, y
#घोषणा INTERNAL_DEBMSG(x,y...) "D" __खाता__ "%d: " x, __LINE__, y

#अगर DEBUG_LEVEL > 0
#घोषणा PRINT_DEBUG(x...)	prपूर्णांकk(KERN_DEBUG PRINTK_HEADER x)
#घोषणा PRINT_INFO(x...)	prपूर्णांकk(KERN_INFO PRINTK_HEADER x)
#घोषणा PRINT_WARN(x...)	prपूर्णांकk(KERN_WARNING PRINTK_HEADER x)
#घोषणा PRINT_ERR(x...)		prपूर्णांकk(KERN_ERR PRINTK_HEADER x)
#घोषणा PRINT_FATAL(x...)	panic(PRINTK_HEADER x)
#अन्यथा
#घोषणा PRINT_DEBUG(x...)	prपूर्णांकk(KERN_DEBUG PRINTK_HEADER x)
#घोषणा PRINT_INFO(x...)	prपूर्णांकk(KERN_DEBUG PRINTK_HEADER x)
#घोषणा PRINT_WARN(x...)	prपूर्णांकk(KERN_DEBUG PRINTK_HEADER x)
#घोषणा PRINT_ERR(x...)		prपूर्णांकk(KERN_DEBUG PRINTK_HEADER x)
#घोषणा PRINT_FATAL(x...)	prपूर्णांकk(KERN_DEBUG PRINTK_HEADER x)
#पूर्ण_अगर /* DASD_DEBUG */

#पूर्ण_अगर /* DEBUG_H */
