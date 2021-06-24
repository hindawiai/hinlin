<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <यंत्र/bug.h>
#समावेश <dirent.h>

#समावेश "data.h"
#समावेश "util.h" // rm_rf_perf_data()
#समावेश "debug.h"
#समावेश "header.h"
#समावेश <पूर्णांकernal/lib.h>

अटल व्योम बंद_dir(काष्ठा perf_data_file *files, पूर्णांक nr)
अणु
	जबतक (--nr >= 1) अणु
		बंद(files[nr].fd);
		zमुक्त(&files[nr].path);
	पूर्ण
	मुक्त(files);
पूर्ण

व्योम perf_data__बंद_dir(काष्ठा perf_data *data)
अणु
	बंद_dir(data->dir.files, data->dir.nr);
पूर्ण

पूर्णांक perf_data__create_dir(काष्ठा perf_data *data, पूर्णांक nr)
अणु
	काष्ठा perf_data_file *files = शून्य;
	पूर्णांक i, ret;

	अगर (WARN_ON(!data->is_dir))
		वापस -EINVAL;

	files = zalloc(nr * माप(*files));
	अगर (!files)
		वापस -ENOMEM;

	data->dir.version = PERF_सूची_VERSION;
	data->dir.files   = files;
	data->dir.nr      = nr;

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा perf_data_file *file = &files[i];

		ret = aप्र_लिखो(&file->path, "%s/data.%d", data->path, i);
		अगर (ret < 0)
			जाओ out_err;

		ret = खोलो(file->path, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
		अगर (ret < 0)
			जाओ out_err;

		file->fd = ret;
	पूर्ण

	वापस 0;

out_err:
	बंद_dir(files, i);
	वापस ret;
पूर्ण

पूर्णांक perf_data__खोलो_dir(काष्ठा perf_data *data)
अणु
	काष्ठा perf_data_file *files = शून्य;
	काष्ठा dirent *dent;
	पूर्णांक ret = -1;
	सूची *dir;
	पूर्णांक nr = 0;

	/*
	 * Directory containing a single regular perf data file which is alपढ़ोy
	 * खोलो, means there is nothing more to करो here.
	 */
	अगर (perf_data__is_single_file(data))
		वापस 0;

	अगर (WARN_ON(!data->is_dir))
		वापस -EINVAL;

	/* The version is provided by सूची_FORMAT feature. */
	अगर (WARN_ON(data->dir.version != PERF_सूची_VERSION))
		वापस -1;

	dir = सूची_खोलो(data->path);
	अगर (!dir)
		वापस -EINVAL;

	जबतक ((dent = सूची_पढ़ो(dir)) != शून्य) अणु
		काष्ठा perf_data_file *file;
		अक्षर path[PATH_MAX];
		काष्ठा stat st;

		snम_लिखो(path, माप(path), "%s/%s", data->path, dent->d_name);
		अगर (stat(path, &st))
			जारी;

		अगर (!S_ISREG(st.st_mode) || म_भेदन(dent->d_name, "data.", 5))
			जारी;

		ret = -ENOMEM;

		file = पुनः_स्मृति(files, (nr + 1) * माप(*files));
		अगर (!file)
			जाओ out_err;

		files = file;
		file = &files[nr++];

		file->path = strdup(path);
		अगर (!file->path)
			जाओ out_err;

		ret = खोलो(file->path, O_RDONLY);
		अगर (ret < 0)
			जाओ out_err;

		file->fd = ret;
		file->size = st.st_size;
	पूर्ण

	अगर (!files)
		वापस -EINVAL;

	data->dir.files = files;
	data->dir.nr    = nr;
	वापस 0;

out_err:
	बंद_dir(files, nr);
	वापस ret;
पूर्ण

पूर्णांक perf_data__update_dir(काष्ठा perf_data *data)
अणु
	पूर्णांक i;

	अगर (WARN_ON(!data->is_dir))
		वापस -EINVAL;

	क्रम (i = 0; i < data->dir.nr; i++) अणु
		काष्ठा perf_data_file *file = &data->dir.files[i];
		काष्ठा stat st;

		अगर (ख_स्थिति(file->fd, &st))
			वापस -1;

		file->size = st.st_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool check_pipe(काष्ठा perf_data *data)
अणु
	काष्ठा stat st;
	bool is_pipe = false;
	पूर्णांक fd = perf_data__is_पढ़ो(data) ?
		 STDIN_खाताNO : STDOUT_खाताNO;

	अगर (!data->path) अणु
		अगर (!ख_स्थिति(fd, &st) && S_ISFIFO(st.st_mode))
			is_pipe = true;
	पूर्ण अन्यथा अणु
		अगर (!म_भेद(data->path, "-"))
			is_pipe = true;
	पूर्ण

	अगर (is_pipe) अणु
		अगर (data->use_stdio) अणु
			स्थिर अक्षर *mode;

			mode = perf_data__is_पढ़ो(data) ? "r" : "w";
			data->file.fptr = fकरोpen(fd, mode);

			अगर (data->file.fptr == शून्य) अणु
				data->file.fd = fd;
				data->use_stdio = false;
			पूर्ण
		पूर्ण अन्यथा अणु
			data->file.fd = fd;
		पूर्ण
	पूर्ण

	वापस data->is_pipe = is_pipe;
पूर्ण

अटल पूर्णांक check_backup(काष्ठा perf_data *data)
अणु
	काष्ठा stat st;

	अगर (perf_data__is_पढ़ो(data))
		वापस 0;

	अगर (!stat(data->path, &st) && st.st_size) अणु
		अक्षर oldname[PATH_MAX];
		पूर्णांक ret;

		snम_लिखो(oldname, माप(oldname), "%s.old",
			 data->path);

		ret = rm_rf_perf_data(oldname);
		अगर (ret) अणु
			pr_err("Can't remove old data: %s (%s)\n",
			       ret == -2 ?
			       "Unknown file found" : म_त्रुटि(त्रुटि_सं),
			       oldname);
			वापस -1;
		पूर्ण

		अगर (नाम(data->path, oldname)) अणु
			pr_err("Can't move data: %s (%s to %s)\n",
			       म_त्रुटि(त्रुटि_सं),
			       data->path, oldname);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_dir(काष्ठा perf_data *data)
अणु
	काष्ठा stat st;

	अगर (stat(data->path, &st))
		वापस false;

	वापस (st.st_mode & S_IFMT) == S_IFसूची;
पूर्ण

अटल पूर्णांक खोलो_file_पढ़ो(काष्ठा perf_data *data)
अणु
	काष्ठा stat st;
	पूर्णांक fd;
	अक्षर sbuf[STRERR_बफ_मानE];

	fd = खोलो(data->file.path, O_RDONLY);
	अगर (fd < 0) अणु
		पूर्णांक err = त्रुटि_सं;

		pr_err("failed to open %s: %s", data->file.path,
			str_error_r(err, sbuf, माप(sbuf)));
		अगर (err == ENOENT && !म_भेद(data->file.path, "perf.data"))
			pr_err("  (try 'perf record' first)");
		pr_err("\n");
		वापस -err;
	पूर्ण

	अगर (ख_स्थिति(fd, &st) < 0)
		जाओ out_बंद;

	अगर (!data->क्रमce && st.st_uid && (st.st_uid != geteuid())) अणु
		pr_err("File %s not owned by current user or root (use -f to override)\n",
		       data->file.path);
		जाओ out_बंद;
	पूर्ण

	अगर (!st.st_size) अणु
		pr_info("zero-sized data (%s), nothing to do!\n",
			data->file.path);
		जाओ out_बंद;
	पूर्ण

	data->file.size = st.st_size;
	वापस fd;

 out_बंद:
	बंद(fd);
	वापस -1;
पूर्ण

अटल पूर्णांक खोलो_file_ग_लिखो(काष्ठा perf_data *data)
अणु
	पूर्णांक fd;
	अक्षर sbuf[STRERR_बफ_मानE];

	fd = खोलो(data->file.path, O_CREAT|O_RDWR|O_TRUNC|O_CLOEXEC,
		  S_IRUSR|S_IWUSR);

	अगर (fd < 0)
		pr_err("failed to open %s : %s\n", data->file.path,
			str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));

	वापस fd;
पूर्ण

अटल पूर्णांक खोलो_file(काष्ठा perf_data *data)
अणु
	पूर्णांक fd;

	fd = perf_data__is_पढ़ो(data) ?
	     खोलो_file_पढ़ो(data) : खोलो_file_ग_लिखो(data);

	अगर (fd < 0) अणु
		zमुक्त(&data->file.path);
		वापस -1;
	पूर्ण

	data->file.fd = fd;
	वापस 0;
पूर्ण

अटल पूर्णांक खोलो_file_dup(काष्ठा perf_data *data)
अणु
	data->file.path = strdup(data->path);
	अगर (!data->file.path)
		वापस -ENOMEM;

	वापस खोलो_file(data);
पूर्ण

अटल पूर्णांक खोलो_dir(काष्ठा perf_data *data)
अणु
	पूर्णांक ret;

	/*
	 * So far we खोलो only the header, so we can पढ़ो the data version and
	 * layout.
	 */
	अगर (aप्र_लिखो(&data->file.path, "%s/data", data->path) < 0)
		वापस -1;

	अगर (perf_data__is_ग_लिखो(data) &&
	    सूची_गढ़ो(data->path, S_IRWXU) < 0)
		वापस -1;

	ret = खोलो_file(data);

	/* Cleanup whatever we managed to create so far. */
	अगर (ret && perf_data__is_ग_लिखो(data))
		rm_rf_perf_data(data->path);

	वापस ret;
पूर्ण

पूर्णांक perf_data__खोलो(काष्ठा perf_data *data)
अणु
	अगर (check_pipe(data))
		वापस 0;

	/* currently it allows stdio क्रम pipe only */
	data->use_stdio = false;

	अगर (!data->path)
		data->path = "perf.data";

	अगर (check_backup(data))
		वापस -1;

	अगर (perf_data__is_पढ़ो(data))
		data->is_dir = is_dir(data);

	वापस perf_data__is_dir(data) ?
	       खोलो_dir(data) : खोलो_file_dup(data);
पूर्ण

व्योम perf_data__बंद(काष्ठा perf_data *data)
अणु
	अगर (perf_data__is_dir(data))
		perf_data__बंद_dir(data);

	zमुक्त(&data->file.path);

	अगर (data->use_stdio)
		ख_बंद(data->file.fptr);
	अन्यथा
		बंद(data->file.fd);
पूर्ण

sमाप_प्रकार perf_data__पढ़ो(काष्ठा perf_data *data, व्योम *buf, माप_प्रकार size)
अणु
	अगर (data->use_stdio) अणु
		अगर (ख_पढ़ो(buf, size, 1, data->file.fptr) == 1)
			वापस size;
		वापस ख_पूर्ण(data->file.fptr) ? 0 : -1;
	पूर्ण
	वापस पढ़ोn(data->file.fd, buf, size);
पूर्ण

sमाप_प्रकार perf_data_file__ग_लिखो(काष्ठा perf_data_file *file,
			      व्योम *buf, माप_प्रकार size)
अणु
	वापस ग_लिखोn(file->fd, buf, size);
पूर्ण

sमाप_प्रकार perf_data__ग_लिखो(काष्ठा perf_data *data,
			      व्योम *buf, माप_प्रकार size)
अणु
	अगर (data->use_stdio) अणु
		अगर (ख_डालो(buf, size, 1, data->file.fptr) == 1)
			वापस size;
		वापस -1;
	पूर्ण
	वापस perf_data_file__ग_लिखो(&data->file, buf, size);
पूर्ण

पूर्णांक perf_data__चयन(काष्ठा perf_data *data,
			   स्थिर अक्षर *postfix,
			   माप_प्रकार pos, bool at_निकास,
			   अक्षर **new_filepath)
अणु
	पूर्णांक ret;

	अगर (check_pipe(data))
		वापस -EINVAL;
	अगर (perf_data__is_पढ़ो(data))
		वापस -EINVAL;

	अगर (aप्र_लिखो(new_filepath, "%s.%s", data->path, postfix) < 0)
		वापस -ENOMEM;

	/*
	 * Only fire a warning, करोn't वापस error, जारी fill
	 * original file.
	 */
	अगर (नाम(data->path, *new_filepath))
		pr_warning("Failed to rename %s to %s\n", data->path, *new_filepath);

	अगर (!at_निकास) अणु
		बंद(data->file.fd);
		ret = perf_data__खोलो(data);
		अगर (ret < 0)
			जाओ out;

		अगर (lseek(data->file.fd, pos, शुरू_से) == (off_t)-1) अणु
			ret = -त्रुटि_सं;
			pr_debug("Failed to lseek to %zu: %s",
				 pos, म_त्रुटि(त्रुटि_सं));
			जाओ out;
		पूर्ण
	पूर्ण
	ret = data->file.fd;
out:
	वापस ret;
पूर्ण

अचिन्हित दीर्घ perf_data__size(काष्ठा perf_data *data)
अणु
	u64 size = data->file.size;
	पूर्णांक i;

	अगर (perf_data__is_single_file(data))
		वापस size;

	क्रम (i = 0; i < data->dir.nr; i++) अणु
		काष्ठा perf_data_file *file = &data->dir.files[i];

		size += file->size;
	पूर्ण

	वापस size;
पूर्ण

पूर्णांक perf_data__make_kcore_dir(काष्ठा perf_data *data, अक्षर *buf, माप_प्रकार buf_sz)
अणु
	पूर्णांक ret;

	अगर (!data->is_dir)
		वापस -1;

	ret = snम_लिखो(buf, buf_sz, "%s/kcore_dir", data->path);
	अगर (ret < 0 || (माप_प्रकार)ret >= buf_sz)
		वापस -1;

	वापस सूची_गढ़ो(buf, S_IRWXU);
पूर्ण

अक्षर *perf_data__kallsyms_name(काष्ठा perf_data *data)
अणु
	अक्षर *kallsyms_name;
	काष्ठा stat st;

	अगर (!data->is_dir)
		वापस शून्य;

	अगर (aप्र_लिखो(&kallsyms_name, "%s/kcore_dir/kallsyms", data->path) < 0)
		वापस शून्य;

	अगर (stat(kallsyms_name, &st)) अणु
		मुक्त(kallsyms_name);
		वापस शून्य;
	पूर्ण

	वापस kallsyms_name;
पूर्ण

bool is_perf_data(स्थिर अक्षर *path)
अणु
	bool ret = false;
	खाता *file;
	u64 magic;

	file = ख_खोलो(path, "r");
	अगर (!file)
		वापस false;

	अगर (ख_पढ़ो(&magic, 1, 8, file) < 8)
		जाओ out;

	ret = is_perf_magic(magic);
out:
	ख_बंद(file);
	वापस ret;
पूर्ण
