<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/माला.स>
#समावेश <termios.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <dirent.h>
#समावेश "subcmd-util.h"
#समावेश "help.h"
#समावेश "exec-cmd.h"

व्योम add_cmdname(काष्ठा cmdnames *cmds, स्थिर अक्षर *name, माप_प्रकार len)
अणु
	काष्ठा cmdname *ent = दो_स्मृति(माप(*ent) + len + 1);

	ent->len = len;
	स_नकल(ent->name, name, len);
	ent->name[len] = 0;

	ALLOC_GROW(cmds->names, cmds->cnt + 1, cmds->alloc);
	cmds->names[cmds->cnt++] = ent;
पूर्ण

व्योम clean_cmdnames(काष्ठा cmdnames *cmds)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cmds->cnt; ++i)
		zमुक्त(&cmds->names[i]);
	zमुक्त(&cmds->names);
	cmds->cnt = 0;
	cmds->alloc = 0;
पूर्ण

पूर्णांक cmdname_compare(स्थिर व्योम *a_, स्थिर व्योम *b_)
अणु
	काष्ठा cmdname *a = *(काष्ठा cmdname **)a_;
	काष्ठा cmdname *b = *(काष्ठा cmdname **)b_;
	वापस म_भेद(a->name, b->name);
पूर्ण

व्योम uniq(काष्ठा cmdnames *cmds)
अणु
	अचिन्हित पूर्णांक i, j;

	अगर (!cmds->cnt)
		वापस;

	क्रम (i = j = 1; i < cmds->cnt; i++)
		अगर (म_भेद(cmds->names[i]->name, cmds->names[i-1]->name))
			cmds->names[j++] = cmds->names[i];

	cmds->cnt = j;
पूर्ण

व्योम exclude_cmds(काष्ठा cmdnames *cmds, काष्ठा cmdnames *excludes)
अणु
	माप_प्रकार ci, cj, ei;
	पूर्णांक cmp;

	ci = cj = ei = 0;
	जबतक (ci < cmds->cnt && ei < excludes->cnt) अणु
		cmp = म_भेद(cmds->names[ci]->name, excludes->names[ei]->name);
		अगर (cmp < 0) अणु
			cmds->names[cj++] = cmds->names[ci++];
		पूर्ण अन्यथा अगर (cmp == 0) अणु
			ci++;
			ei++;
		पूर्ण अन्यथा अगर (cmp > 0) अणु
			ei++;
		पूर्ण
	पूर्ण

	जबतक (ci < cmds->cnt)
		cmds->names[cj++] = cmds->names[ci++];

	cmds->cnt = cj;
पूर्ण

अटल व्योम get_term_dimensions(काष्ठा winsize *ws)
अणु
	अक्षर *s = दो_पर्या("LINES");

	अगर (s != शून्य) अणु
		ws->ws_row = म_से_प(s);
		s = दो_पर्या("COLUMNS");
		अगर (s != शून्य) अणु
			ws->ws_col = म_से_प(s);
			अगर (ws->ws_row && ws->ws_col)
				वापस;
		पूर्ण
	पूर्ण
#अगर_घोषित TIOCGWINSZ
	अगर (ioctl(1, TIOCGWINSZ, ws) == 0 &&
	    ws->ws_row && ws->ws_col)
		वापस;
#पूर्ण_अगर
	ws->ws_row = 25;
	ws->ws_col = 80;
पूर्ण

अटल व्योम pretty_prपूर्णांक_string_list(काष्ठा cmdnames *cmds, पूर्णांक दीर्घest)
अणु
	पूर्णांक cols = 1, rows;
	पूर्णांक space = दीर्घest + 1; /* min 1 SP between words */
	काष्ठा winsize win;
	पूर्णांक max_cols;
	पूर्णांक i, j;

	get_term_dimensions(&win);
	max_cols = win.ws_col - 1; /* करोn't prपूर्णांक *on* the edge */

	अगर (space < max_cols)
		cols = max_cols / space;
	rows = (cmds->cnt + cols - 1) / cols;

	क्रम (i = 0; i < rows; i++) अणु
		म_लिखो("  ");

		क्रम (j = 0; j < cols; j++) अणु
			अचिन्हित पूर्णांक n = j * rows + i;
			अचिन्हित पूर्णांक size = space;

			अगर (n >= cmds->cnt)
				अवरोध;
			अगर (j == cols-1 || n + rows >= cmds->cnt)
				size = 1;
			म_लिखो("%-*s", size, cmds->names[n]->name);
		पूर्ण
		अक्षर_दो('\n');
	पूर्ण
पूर्ण

अटल पूर्णांक is_executable(स्थिर अक्षर *name)
अणु
	काष्ठा stat st;

	अगर (stat(name, &st) || /* stat, not lstat */
	    !S_ISREG(st.st_mode))
		वापस 0;

	वापस st.st_mode & S_IXUSR;
पूर्ण

अटल पूर्णांक has_extension(स्थिर अक्षर *filename, स्थिर अक्षर *ext)
अणु
	माप_प्रकार len = म_माप(filename);
	माप_प्रकार extlen = म_माप(ext);

	वापस len > extlen && !स_भेद(filename + len - extlen, ext, extlen);
पूर्ण

अटल व्योम list_commands_in_dir(काष्ठा cmdnames *cmds,
					 स्थिर अक्षर *path,
					 स्थिर अक्षर *prefix)
अणु
	पूर्णांक prefix_len;
	सूची *dir = सूची_खोलो(path);
	काष्ठा dirent *de;
	अक्षर *buf = शून्य;

	अगर (!dir)
		वापस;
	अगर (!prefix)
		prefix = "perf-";
	prefix_len = म_माप(prefix);

	aम_जोड़ोf(&buf, "%s/", path);

	जबतक ((de = सूची_पढ़ो(dir)) != शून्य) अणु
		पूर्णांक entlen;

		अगर (!strstarts(de->d_name, prefix))
			जारी;

		aम_जोड़ो(&buf, de->d_name);
		अगर (!is_executable(buf))
			जारी;

		entlen = म_माप(de->d_name) - prefix_len;
		अगर (has_extension(de->d_name, ".exe"))
			entlen -= 4;

		add_cmdname(cmds, de->d_name + prefix_len, entlen);
	पूर्ण
	बंद_सूची(dir);
	मुक्त(buf);
पूर्ण

व्योम load_command_list(स्थिर अक्षर *prefix,
		काष्ठा cmdnames *मुख्य_cmds,
		काष्ठा cmdnames *other_cmds)
अणु
	स्थिर अक्षर *env_path = दो_पर्या("PATH");
	अक्षर *exec_path = get_argv_exec_path();

	अगर (exec_path) अणु
		list_commands_in_dir(मुख्य_cmds, exec_path, prefix);
		क्विक(मुख्य_cmds->names, मुख्य_cmds->cnt,
		      माप(*मुख्य_cmds->names), cmdname_compare);
		uniq(मुख्य_cmds);
	पूर्ण

	अगर (env_path) अणु
		अक्षर *paths, *path, *colon;
		path = paths = strdup(env_path);
		जबतक (1) अणु
			अगर ((colon = म_अक्षर(path, ':')))
				*colon = 0;
			अगर (!exec_path || म_भेद(path, exec_path))
				list_commands_in_dir(other_cmds, path, prefix);

			अगर (!colon)
				अवरोध;
			path = colon + 1;
		पूर्ण
		मुक्त(paths);

		क्विक(other_cmds->names, other_cmds->cnt,
		      माप(*other_cmds->names), cmdname_compare);
		uniq(other_cmds);
	पूर्ण
	मुक्त(exec_path);
	exclude_cmds(other_cmds, मुख्य_cmds);
पूर्ण

व्योम list_commands(स्थिर अक्षर *title, काष्ठा cmdnames *मुख्य_cmds,
		   काष्ठा cmdnames *other_cmds)
अणु
	अचिन्हित पूर्णांक i, दीर्घest = 0;

	क्रम (i = 0; i < मुख्य_cmds->cnt; i++)
		अगर (दीर्घest < मुख्य_cmds->names[i]->len)
			दीर्घest = मुख्य_cmds->names[i]->len;
	क्रम (i = 0; i < other_cmds->cnt; i++)
		अगर (दीर्घest < other_cmds->names[i]->len)
			दीर्घest = other_cmds->names[i]->len;

	अगर (मुख्य_cmds->cnt) अणु
		अक्षर *exec_path = get_argv_exec_path();
		म_लिखो("available %s in '%s'\n", title, exec_path);
		म_लिखो("----------------");
		mput_अक्षर('-', म_माप(title) + म_माप(exec_path));
		अक्षर_दो('\n');
		pretty_prपूर्णांक_string_list(मुख्य_cmds, दीर्घest);
		अक्षर_दो('\n');
		मुक्त(exec_path);
	पूर्ण

	अगर (other_cmds->cnt) अणु
		म_लिखो("%s available from elsewhere on your $PATH\n", title);
		म_लिखो("---------------------------------------");
		mput_अक्षर('-', म_माप(title));
		अक्षर_दो('\n');
		pretty_prपूर्णांक_string_list(other_cmds, दीर्घest);
		अक्षर_दो('\n');
	पूर्ण
पूर्ण

पूर्णांक is_in_cmdlist(काष्ठा cmdnames *c, स्थिर अक्षर *s)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < c->cnt; i++)
		अगर (!म_भेद(s, c->names[i]->name))
			वापस 1;
	वापस 0;
पूर्ण
