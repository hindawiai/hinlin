<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2007 Jon Loeliger, Freescale Semiconductor, Inc.
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>

#समावेश "dtc.h"
#समावेश "srcpos.h"

/* A node in our list of directories to search क्रम source/include files */
काष्ठा search_path अणु
	काष्ठा search_path *next;	/* next node in list, शून्य क्रम end */
	स्थिर अक्षर *स_नाम;		/* name of directory to search */
पूर्ण;

/* This is the list of directories that we search क्रम source files */
अटल काष्ठा search_path *search_path_head, **search_path_tail;

/* Detect infinite include recursion. */
#घोषणा MAX_SRCखाता_DEPTH     (200)
अटल पूर्णांक srcfile_depth; /* = 0 */

अटल अक्षर *get_स_नाम(स्थिर अक्षर *path)
अणु
	स्थिर अक्षर *slash = म_खोजप(path, '/');

	अगर (slash) अणु
		पूर्णांक len = slash - path;
		अक्षर *dir = xदो_स्मृति(len + 1);

		स_नकल(dir, path, len);
		dir[len] = '\0';
		वापस dir;
	पूर्ण
	वापस शून्य;
पूर्ण

खाता *depfile; /* = शून्य */
काष्ठा srcfile_state *current_srcfile; /* = शून्य */
अटल अक्षर *initial_path; /* = शून्य */
अटल पूर्णांक initial_pathlen; /* = 0 */
अटल bool initial_cpp = true;

अटल व्योम set_initial_path(अक्षर *fname)
अणु
	पूर्णांक i, len = म_माप(fname);

	xaप्र_लिखो(&initial_path, "%s", fname);
	initial_pathlen = 0;
	क्रम (i = 0; i != len; i++)
		अगर (initial_path[i] == '/')
			initial_pathlen++;
पूर्ण

अटल अक्षर *लघुen_to_initial_path(अक्षर *fname)
अणु
	अक्षर *p1, *p2, *prevslash1 = शून्य;
	पूर्णांक slashes = 0;

	क्रम (p1 = fname, p2 = initial_path; *p1 && *p2; p1++, p2++) अणु
		अगर (*p1 != *p2)
			अवरोध;
		अगर (*p1 == '/') अणु
			prevslash1 = p1;
			slashes++;
		पूर्ण
	पूर्ण
	p1 = prevslash1 + 1;
	अगर (prevslash1) अणु
		पूर्णांक dअगरf = initial_pathlen - slashes, i, j;
		पूर्णांक restlen = म_माप(fname) - (p1 - fname);
		अक्षर *res;

		res = xदो_स्मृति((3 * dअगरf) + restlen + 1);
		क्रम (i = 0, j = 0; i != dअगरf; i++) अणु
			res[j++] = '.';
			res[j++] = '.';
			res[j++] = '/';
		पूर्ण
		म_नकल(res + j, p1);
		वापस res;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * Try to खोलो a file in a given directory.
 *
 * If the filename is an असलolute path, then स_नाम is ignored. If it is a
 * relative path, then we look in that directory क्रम the file.
 *
 * @param स_नाम	Directory to look in, or शून्य क्रम none
 * @param fname		Filename to look क्रम
 * @param fp		Set to शून्य अगर file did not खोलो
 * @वापस allocated filename on success (caller must मुक्त), शून्य on failure
 */
अटल अक्षर *try_खोलो(स्थिर अक्षर *स_नाम, स्थिर अक्षर *fname, खाता **fp)
अणु
	अक्षर *fullname;

	अगर (!स_नाम || fname[0] == '/')
		fullname = xstrdup(fname);
	अन्यथा
		fullname = join_path(स_नाम, fname);

	*fp = ख_खोलो(fullname, "rb");
	अगर (!*fp) अणु
		मुक्त(fullname);
		fullname = शून्य;
	पूर्ण

	वापस fullname;
पूर्ण

/**
 * Open a file क्रम पढ़ो access
 *
 * If it is a relative filename, we search the full search path क्रम it.
 *
 * @param fname	Filename to खोलो
 * @param fp	Returns poपूर्णांकer to खोलोed खाता, or शून्य on failure
 * @वापस poपूर्णांकer to allocated filename, which caller must मुक्त
 */
अटल अक्षर *ख_खोलो_any_on_path(स्थिर अक्षर *fname, खाता **fp)
अणु
	स्थिर अक्षर *cur_dir = शून्य;
	काष्ठा search_path *node;
	अक्षर *fullname;

	/* Try current directory first */
	निश्चित(fp);
	अगर (current_srcfile)
		cur_dir = current_srcfile->dir;
	fullname = try_खोलो(cur_dir, fname, fp);

	/* Failing that, try each search path in turn */
	क्रम (node = search_path_head; !*fp && node; node = node->next)
		fullname = try_खोलो(node->स_नाम, fname, fp);

	वापस fullname;
पूर्ण

खाता *srcfile_relative_खोलो(स्थिर अक्षर *fname, अक्षर **fullnamep)
अणु
	खाता *f;
	अक्षर *fullname;

	अगर (streq(fname, "-")) अणु
		f = मानक_निवेश;
		fullname = xstrdup("<stdin>");
	पूर्ण अन्यथा अणु
		fullname = ख_खोलो_any_on_path(fname, &f);
		अगर (!f)
			die("Couldn't open \"%s\": %s\n", fname,
			    म_त्रुटि(त्रुटि_सं));
	पूर्ण

	अगर (depfile)
		ख_लिखो(depfile, " %s", fullname);

	अगर (fullnamep)
		*fullnamep = fullname;
	अन्यथा
		मुक्त(fullname);

	वापस f;
पूर्ण

व्योम srcfile_push(स्थिर अक्षर *fname)
अणु
	काष्ठा srcfile_state *srcfile;

	अगर (srcfile_depth++ >= MAX_SRCखाता_DEPTH)
		die("Includes nested too deeply");

	srcfile = xदो_स्मृति(माप(*srcfile));

	srcfile->f = srcfile_relative_खोलो(fname, &srcfile->name);
	srcfile->dir = get_स_नाम(srcfile->name);
	srcfile->prev = current_srcfile;

	srcfile->lineno = 1;
	srcfile->colno = 1;

	current_srcfile = srcfile;

	अगर (srcfile_depth == 1)
		set_initial_path(srcfile->name);
पूर्ण

bool srcfile_pop(व्योम)
अणु
	काष्ठा srcfile_state *srcfile = current_srcfile;

	निश्चित(srcfile);

	current_srcfile = srcfile->prev;

	अगर (ख_बंद(srcfile->f))
		die("Error closing \"%s\": %s\n", srcfile->name,
		    म_त्रुटि(त्रुटि_सं));

	/* FIXME: We allow the srcfile_state काष्ठाure to leak,
	 * because it could still be referenced from a location
	 * variable being carried through the parser somewhere.  To
	 * fix this we could either allocate all the files from a
	 * table, or use a pool allocator. */

	वापस current_srcfile ? true : false;
पूर्ण

व्योम srcfile_add_search_path(स्थिर अक्षर *स_नाम)
अणु
	काष्ठा search_path *node;

	/* Create the node */
	node = xदो_स्मृति(माप(*node));
	node->next = शून्य;
	node->स_नाम = xstrdup(स_नाम);

	/* Add to the end of our list */
	अगर (search_path_tail)
		*search_path_tail = node;
	अन्यथा
		search_path_head = node;
	search_path_tail = &node->next;
पूर्ण

व्योम srcpos_update(काष्ठा srcpos *pos, स्थिर अक्षर *text, पूर्णांक len)
अणु
	पूर्णांक i;

	pos->file = current_srcfile;

	pos->first_line = current_srcfile->lineno;
	pos->first_column = current_srcfile->colno;

	क्रम (i = 0; i < len; i++)
		अगर (text[i] == '\n') अणु
			current_srcfile->lineno++;
			current_srcfile->colno = 1;
		पूर्ण अन्यथा अणु
			current_srcfile->colno++;
		पूर्ण

	pos->last_line = current_srcfile->lineno;
	pos->last_column = current_srcfile->colno;
पूर्ण

काष्ठा srcpos *
srcpos_copy(काष्ठा srcpos *pos)
अणु
	काष्ठा srcpos *pos_new;
	काष्ठा srcfile_state *srcfile_state;

	अगर (!pos)
		वापस शून्य;

	pos_new = xदो_स्मृति(माप(काष्ठा srcpos));
	निश्चित(pos->next == शून्य);
	स_नकल(pos_new, pos, माप(काष्ठा srcpos));

	/* allocate without मुक्त */
	srcfile_state = xदो_स्मृति(माप(काष्ठा srcfile_state));
	स_नकल(srcfile_state, pos->file, माप(काष्ठा srcfile_state));
	pos_new->file = srcfile_state;

	वापस pos_new;
पूर्ण

काष्ठा srcpos *srcpos_extend(काष्ठा srcpos *pos, काष्ठा srcpos *newtail)
अणु
	काष्ठा srcpos *p;

	अगर (!pos)
		वापस newtail;

	क्रम (p = pos; p->next != शून्य; p = p->next);
	p->next = newtail;
	वापस pos;
पूर्ण

अक्षर *
srcpos_string(काष्ठा srcpos *pos)
अणु
	स्थिर अक्षर *fname = "<no-file>";
	अक्षर *pos_str;

	अगर (pos->file && pos->file->name)
		fname = pos->file->name;


	अगर (pos->first_line != pos->last_line)
		xaप्र_लिखो(&pos_str, "%s:%d.%d-%d.%d", fname,
			  pos->first_line, pos->first_column,
			  pos->last_line, pos->last_column);
	अन्यथा अगर (pos->first_column != pos->last_column)
		xaप्र_लिखो(&pos_str, "%s:%d.%d-%d", fname,
			  pos->first_line, pos->first_column,
			  pos->last_column);
	अन्यथा
		xaप्र_लिखो(&pos_str, "%s:%d.%d", fname,
			  pos->first_line, pos->first_column);

	वापस pos_str;
पूर्ण

अटल अक्षर *
srcpos_string_comment(काष्ठा srcpos *pos, bool first_line, पूर्णांक level)
अणु
	अक्षर *pos_str, *fname, *first, *rest;
	bool fresh_fname = false;

	अगर (!pos) अणु
		अगर (level > 1) अणु
			xaप्र_लिखो(&pos_str, "<no-file>:<no-line>");
			वापस pos_str;
		पूर्ण अन्यथा अणु
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (!pos->file)
		fname = "<no-file>";
	अन्यथा अगर (!pos->file->name)
		fname = "<no-filename>";
	अन्यथा अगर (level > 1)
		fname = pos->file->name;
	अन्यथा अणु
		fname = लघुen_to_initial_path(pos->file->name);
		अगर (fname)
			fresh_fname = true;
		अन्यथा
			fname = pos->file->name;
	पूर्ण

	अगर (level > 1)
		xaप्र_लिखो(&first, "%s:%d:%d-%d:%d", fname,
			  pos->first_line, pos->first_column,
			  pos->last_line, pos->last_column);
	अन्यथा
		xaप्र_लिखो(&first, "%s:%d", fname,
			  first_line ? pos->first_line : pos->last_line);

	अगर (fresh_fname)
		मुक्त(fname);

	अगर (pos->next != शून्य) अणु
		rest = srcpos_string_comment(pos->next, first_line, level);
		xaप्र_लिखो(&pos_str, "%s, %s", first, rest);
		मुक्त(first);
		मुक्त(rest);
	पूर्ण अन्यथा अणु
		pos_str = first;
	पूर्ण

	वापस pos_str;
पूर्ण

अक्षर *srcpos_string_first(काष्ठा srcpos *pos, पूर्णांक level)
अणु
	वापस srcpos_string_comment(pos, true, level);
पूर्ण

अक्षर *srcpos_string_last(काष्ठा srcpos *pos, पूर्णांक level)
अणु
	वापस srcpos_string_comment(pos, false, level);
पूर्ण

व्योम srcpos_verror(काष्ठा srcpos *pos, स्थिर अक्षर *prefix,
		   स्थिर अक्षर *fmt, बहु_सूची va)
अणु
	अक्षर *srcstr;

	srcstr = srcpos_string(pos);

	ख_लिखो(मानक_त्रुटि, "%s: %s ", prefix, srcstr);
	भख_लिखो(मानक_त्रुटि, fmt, va);
	ख_लिखो(मानक_त्रुटि, "\n");

	मुक्त(srcstr);
पूर्ण

व्योम srcpos_error(काष्ठा srcpos *pos, स्थिर अक्षर *prefix,
		  स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;

	बहु_शुरू(va, fmt);
	srcpos_verror(pos, prefix, fmt, va);
	बहु_पूर्ण(va);
पूर्ण

व्योम srcpos_set_line(अक्षर *f, पूर्णांक l)
अणु
	current_srcfile->name = f;
	current_srcfile->lineno = l;

	अगर (initial_cpp) अणु
		initial_cpp = false;
		set_initial_path(f);
	पूर्ण
पूर्ण
