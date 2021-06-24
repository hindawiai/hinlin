<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/स्थिति.स>
#समावेश <init.h>
#समावेश <os.h>

#घोषणा UML_सूची "~/.uml/"

#घोषणा UMID_LEN 64

/* Changed by set_umid, which is run early in boot */
अटल अक्षर umid[UMID_LEN] = अणु 0 पूर्ण;

/* Changed by set_uml_dir and make_uml_dir, which are run early in boot */
अटल अक्षर *uml_dir = UML_सूची;

अटल पूर्णांक __init make_uml_dir(व्योम)
अणु
	अक्षर dir[512] = अणु '\0' पूर्ण;
	पूर्णांक len, err;

	अगर (*uml_dir == '~') अणु
		अक्षर *home = दो_पर्या("HOME");

		err = -ENOENT;
		अगर (home == शून्य) अणु
			prपूर्णांकk(UM_KERN_ERR
				"%s: no value in environment for $HOME\n",
				__func__);
			जाओ err;
		पूर्ण
		strlcpy(dir, home, माप(dir));
		uml_dir++;
	पूर्ण
	strlcat(dir, uml_dir, माप(dir));
	len = म_माप(dir);
	अगर (len > 0 && dir[len - 1] != '/')
		strlcat(dir, "/", माप(dir));

	err = -ENOMEM;
	uml_dir = दो_स्मृति(म_माप(dir) + 1);
	अगर (uml_dir == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "%s : malloc failed, errno = %d\n",
			__func__, त्रुटि_सं);
		जाओ err;
	पूर्ण
	म_नकल(uml_dir, dir);

	अगर ((सूची_गढ़ो(uml_dir, 0777) < 0) && (त्रुटि_सं != EEXIST)) अणु
		prपूर्णांकk(UM_KERN_ERR "Failed to mkdir '%s': %s\n",
			uml_dir, म_त्रुटि(त्रुटि_सं));
		err = -त्रुटि_सं;
		जाओ err_मुक्त;
	पूर्ण
	वापस 0;

err_मुक्त:
	मुक्त(uml_dir);
err:
	uml_dir = शून्य;
	वापस err;
पूर्ण

/*
 * Unlinks the files contained in @dir and then हटाओs @dir.
 * Doesn't handle directory trees, so it's not like rm -rf, but almost such. We
 * ignore ENOENT errors क्रम anything (they happen, strangely enough - possibly
 * due to races between multiple dying UML thपढ़ोs).
 */
अटल पूर्णांक हटाओ_files_and_dir(अक्षर *dir)
अणु
	सूची *directory;
	काष्ठा dirent *ent;
	पूर्णांक len;
	अक्षर file[256];
	पूर्णांक ret;

	directory = सूची_खोलो(dir);
	अगर (directory == शून्य) अणु
		अगर (त्रुटि_सं != ENOENT)
			वापस -त्रुटि_सं;
		अन्यथा
			वापस 0;
	पूर्ण

	जबतक ((ent = सूची_पढ़ो(directory)) != शून्य) अणु
		अगर (!म_भेद(ent->d_name, ".") || !म_भेद(ent->d_name, ".."))
			जारी;
		len = म_माप(dir) + म_माप("/") + म_माप(ent->d_name) + 1;
		अगर (len > माप(file)) अणु
			ret = -E2BIG;
			जाओ out;
		पूर्ण

		प्र_लिखो(file, "%s/%s", dir, ent->d_name);
		अगर (unlink(file) < 0 && त्रुटि_सं != ENOENT) अणु
			ret = -त्रुटि_सं;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (सूची_हटाओ(dir) < 0 && त्रुटि_सं != ENOENT) अणु
		ret = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	ret = 0;
out:
	बंद_सूची(directory);
	वापस ret;
पूर्ण

/*
 * This says that there isn't alपढ़ोy a user of the specअगरied directory even अगर
 * there are errors during the checking.  This is because अगर these errors
 * happen, the directory is unusable by the pre-existing UML, so we might as
 * well take it over.  This could happen either by
 * 	the existing UML somehow corrupting its umid directory
 * 	something other than UML sticking stuff in the directory
 *	this boot racing with a shutकरोwn of the other UML
 * In any of these हालs, the directory isn't useful क्रम anything अन्यथा.
 *
 * Boolean वापस: 1 अगर in use, 0 otherwise.
 */
अटल अंतरभूत पूर्णांक is_umdir_used(अक्षर *dir)
अणु
	अक्षर pid[माप("nnnnnnnnn")], *end, *file;
	पूर्णांक dead, fd, p, n, err;
	माप_प्रकार filelen = म_माप(dir) + माप("/pid") + 1;

	file = दो_स्मृति(filelen);
	अगर (!file)
		वापस -ENOMEM;

	snम_लिखो(file, filelen, "%s/pid", dir);

	dead = 0;
	fd = खोलो(file, O_RDONLY);
	अगर (fd < 0) अणु
		fd = -त्रुटि_सं;
		अगर (fd != -ENOENT) अणु
			prपूर्णांकk(UM_KERN_ERR "is_umdir_used : couldn't open pid "
			       "file '%s', err = %d\n", file, -fd);
		पूर्ण
		जाओ out;
	पूर्ण

	err = 0;
	n = पढ़ो(fd, pid, माप(pid));
	अगर (n < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "is_umdir_used : couldn't read pid file "
		       "'%s', err = %d\n", file, त्रुटि_सं);
		जाओ out_बंद;
	पूर्ण अन्यथा अगर (n == 0) अणु
		prपूर्णांकk(UM_KERN_ERR "is_umdir_used : couldn't read pid file "
		       "'%s', 0-byte read\n", file);
		जाओ out_बंद;
	पूर्ण

	p = म_से_अदीर्घ(pid, &end, 0);
	अगर (end == pid) अणु
		prपूर्णांकk(UM_KERN_ERR "is_umdir_used : couldn't parse pid file "
		       "'%s', errno = %d\n", file, त्रुटि_सं);
		जाओ out_बंद;
	पूर्ण

	अगर ((समाप्त(p, 0) == 0) || (त्रुटि_सं != ESRCH)) अणु
		prपूर्णांकk(UM_KERN_ERR "umid \"%s\" is already in use by pid %d\n",
		       umid, p);
		वापस 1;
	पूर्ण

out_बंद:
	बंद(fd);
out:
	मुक्त(file);
	वापस 0;
पूर्ण

/*
 * Try to हटाओ the directory @dir unless it's in use.
 * Precondition: @dir exists.
 * Returns 0 क्रम success, < 0 क्रम failure in removal or अगर the directory is in
 * use.
 */
अटल पूर्णांक umdir_take_अगर_dead(अक्षर *dir)
अणु
	पूर्णांक ret;
	अगर (is_umdir_used(dir))
		वापस -EEXIST;

	ret = हटाओ_files_and_dir(dir);
	अगर (ret) अणु
		prपूर्णांकk(UM_KERN_ERR "is_umdir_used - remove_files_and_dir "
		       "failed with err = %d\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __init create_pid_file(व्योम)
अणु
	अक्षर pid[माप("nnnnnnnnn")], *file;
	पूर्णांक fd, n;

	n = म_माप(uml_dir) + UMID_LEN + माप("/pid");
	file = दो_स्मृति(n);
	अगर (!file)
		वापस;

	अगर (umid_file_name("pid", file, n))
		जाओ out;

	fd = खोलो(file, O_RDWR | O_CREAT | O_EXCL, 0644);
	अगर (fd < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "Open of machine pid file \"%s\" failed: "
		       "%s\n", file, म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	snम_लिखो(pid, माप(pid), "%d\n", getpid());
	n = ग_लिखो(fd, pid, म_माप(pid));
	अगर (n != म_माप(pid))
		prपूर्णांकk(UM_KERN_ERR "Write of pid file failed - err = %d\n",
		       त्रुटि_सं);

	बंद(fd);
out:
	मुक्त(file);
पूर्ण

पूर्णांक __init set_umid(अक्षर *name)
अणु
	अगर (म_माप(name) > UMID_LEN - 1)
		वापस -E2BIG;

	strlcpy(umid, name, माप(umid));

	वापस 0;
पूर्ण

/* Changed in make_umid, which is called during early boot */
अटल पूर्णांक umid_setup = 0;

अटल पूर्णांक __init make_umid(व्योम)
अणु
	पूर्णांक fd, err;
	अक्षर पंचांगp[256];

	अगर (umid_setup)
		वापस 0;

	make_uml_dir();

	अगर (*umid == '\0') अणु
		strlcpy(पंचांगp, uml_dir, माप(पंचांगp));
		strlcat(पंचांगp, "XXXXXX", माप(पंचांगp));
		fd = mkstemp(पंचांगp);
		अगर (fd < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "make_umid - mkstemp(%s) failed: "
			       "%s\n", पंचांगp, म_त्रुटि(त्रुटि_सं));
			err = -त्रुटि_सं;
			जाओ err;
		पूर्ण

		बंद(fd);

		set_umid(&पंचांगp[म_माप(uml_dir)]);

		/*
		 * There's a nice tiny little race between this unlink and
		 * the सूची_गढ़ो below.  It'd be nice अगर there were a mkstemp
		 * क्रम directories.
		 */
		अगर (unlink(पंचांगp)) अणु
			err = -त्रुटि_सं;
			जाओ err;
		पूर्ण
	पूर्ण

	snम_लिखो(पंचांगp, माप(पंचांगp), "%s%s", uml_dir, umid);
	err = सूची_गढ़ो(पंचांगp, 0777);
	अगर (err < 0) अणु
		err = -त्रुटि_सं;
		अगर (err != -EEXIST)
			जाओ err;

		अगर (umdir_take_अगर_dead(पंचांगp) < 0)
			जाओ err;

		err = सूची_गढ़ो(पंचांगp, 0777);
	पूर्ण
	अगर (err) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "Failed to create '%s' - err = %d\n", umid,
		       त्रुटि_सं);
		जाओ err;
	पूर्ण

	umid_setup = 1;

	create_pid_file();

	err = 0;
 err:
	वापस err;
पूर्ण

अटल पूर्णांक __init make_umid_init(व्योम)
अणु
	अगर (!make_umid())
		वापस 0;

	/*
	 * If initializing with the given umid failed, then try again with
	 * a अक्रमom one.
	 */
	prपूर्णांकk(UM_KERN_ERR "Failed to initialize umid \"%s\", trying with a "
	       "random umid\n", umid);
	*umid = '\0';
	make_umid();

	वापस 0;
पूर्ण

__initcall(make_umid_init);

पूर्णांक __init umid_file_name(अक्षर *name, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक n, err;

	err = make_umid();
	अगर (err)
		वापस err;

	n = snम_लिखो(buf, len, "%s%s/%s", uml_dir, umid, name);
	अगर (n >= len) अणु
		prपूर्णांकk(UM_KERN_ERR "umid_file_name : buffer too short\n");
		वापस -E2BIG;
	पूर्ण

	वापस 0;
पूर्ण

अक्षर *get_umid(व्योम)
अणु
	वापस umid;
पूर्ण

अटल पूर्णांक __init set_uml_dir(अक्षर *name, पूर्णांक *add)
अणु
	अगर (*name == '\0') अणु
		os_warn("uml_dir can't be an empty string\n");
		वापस 0;
	पूर्ण

	अगर (name[म_माप(name) - 1] == '/') अणु
		uml_dir = name;
		वापस 0;
	पूर्ण

	uml_dir = दो_स्मृति(म_माप(name) + 2);
	अगर (uml_dir == शून्य) अणु
		os_warn("Failed to malloc uml_dir - error = %d\n", त्रुटि_सं);

		/*
		 * Return 0 here because करो_initcalls करोesn't look at
		 * the वापस value.
		 */
		वापस 0;
	पूर्ण
	प्र_लिखो(uml_dir, "%s/", name);

	वापस 0;
पूर्ण

__uml_setup("uml_dir=", set_uml_dir,
"uml_dir=<directory>\n"
"    The location to place the pid and umid files.\n\n"
);

अटल व्योम हटाओ_umid_dir(व्योम)
अणु
	अक्षर *dir, err;

	dir = दो_स्मृति(म_माप(uml_dir) + UMID_LEN + 1);
	अगर (!dir)
		वापस;

	प्र_लिखो(dir, "%s%s", uml_dir, umid);
	err = हटाओ_files_and_dir(dir);
	अगर (err)
		os_warn("%s - remove_files_and_dir failed with err = %d\n",
			__func__, err);

	मुक्त(dir);
पूर्ण

__uml_निकासcall(हटाओ_umid_dir);
