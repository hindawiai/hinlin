<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/vfs.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <sys/mount.h>

#समावेश "fs.h"
#समावेश "debug-internal.h"

#घोषणा _STR(x) #x
#घोषणा STR(x) _STR(x)

#अगर_अघोषित SYSFS_MAGIC
#घोषणा SYSFS_MAGIC            0x62656572
#पूर्ण_अगर

#अगर_अघोषित PROC_SUPER_MAGIC
#घोषणा PROC_SUPER_MAGIC       0x9fa0
#पूर्ण_अगर

#अगर_अघोषित DEBUGFS_MAGIC
#घोषणा DEBUGFS_MAGIC          0x64626720
#पूर्ण_अगर

#अगर_अघोषित TRACEFS_MAGIC
#घोषणा TRACEFS_MAGIC          0x74726163
#पूर्ण_अगर

#अगर_अघोषित HUGETLBFS_MAGIC
#घोषणा HUGETLBFS_MAGIC        0x958458f6
#पूर्ण_अगर

#अगर_अघोषित BPF_FS_MAGIC
#घोषणा BPF_FS_MAGIC           0xcafe4a11
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर sysfs__fs_known_mountpoपूर्णांकs[] = अणु
	"/sys",
	0,
पूर्ण;

अटल स्थिर अक्षर * स्थिर procfs__known_mountpoपूर्णांकs[] = अणु
	"/proc",
	0,
पूर्ण;

#अगर_अघोषित DEBUGFS_DEFAULT_PATH
#घोषणा DEBUGFS_DEFAULT_PATH "/sys/kernel/debug"
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर debugfs__known_mountpoपूर्णांकs[] = अणु
	DEBUGFS_DEFAULT_PATH,
	"/debug",
	0,
पूर्ण;


#अगर_अघोषित TRACEFS_DEFAULT_PATH
#घोषणा TRACEFS_DEFAULT_PATH "/sys/kernel/tracing"
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर tracefs__known_mountpoपूर्णांकs[] = अणु
	TRACEFS_DEFAULT_PATH,
	"/sys/kernel/debug/tracing",
	"/tracing",
	"/trace",
	0,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hugetlbfs__known_mountpoपूर्णांकs[] = अणु
	0,
पूर्ण;

अटल स्थिर अक्षर * स्थिर bpf_fs__known_mountpoपूर्णांकs[] = अणु
	"/sys/fs/bpf",
	0,
पूर्ण;

काष्ठा fs अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर * स्थिर	*mounts;
	अक्षर			 path[PATH_MAX];
	bool			 found;
	bool			 checked;
	दीर्घ			 magic;
पूर्ण;

क्रमागत अणु
	FS__SYSFS   = 0,
	FS__PROCFS  = 1,
	FS__DEBUGFS = 2,
	FS__TRACEFS = 3,
	FS__HUGETLBFS = 4,
	FS__BPF_FS = 5,
पूर्ण;

#अगर_अघोषित TRACEFS_MAGIC
#घोषणा TRACEFS_MAGIC 0x74726163
#पूर्ण_अगर

अटल काष्ठा fs fs__entries[] = अणु
	[FS__SYSFS] = अणु
		.name	= "sysfs",
		.mounts	= sysfs__fs_known_mountpoपूर्णांकs,
		.magic	= SYSFS_MAGIC,
		.checked = false,
	पूर्ण,
	[FS__PROCFS] = अणु
		.name	= "proc",
		.mounts	= procfs__known_mountpoपूर्णांकs,
		.magic	= PROC_SUPER_MAGIC,
		.checked = false,
	पूर्ण,
	[FS__DEBUGFS] = अणु
		.name	= "debugfs",
		.mounts	= debugfs__known_mountpoपूर्णांकs,
		.magic	= DEBUGFS_MAGIC,
		.checked = false,
	पूर्ण,
	[FS__TRACEFS] = अणु
		.name	= "tracefs",
		.mounts	= tracefs__known_mountpoपूर्णांकs,
		.magic	= TRACEFS_MAGIC,
		.checked = false,
	पूर्ण,
	[FS__HUGETLBFS] = अणु
		.name	= "hugetlbfs",
		.mounts = hugetlbfs__known_mountpoपूर्णांकs,
		.magic	= HUGETLBFS_MAGIC,
		.checked = false,
	पूर्ण,
	[FS__BPF_FS] = अणु
		.name	= "bpf",
		.mounts = bpf_fs__known_mountpoपूर्णांकs,
		.magic	= BPF_FS_MAGIC,
		.checked = false,
	पूर्ण,
पूर्ण;

अटल bool fs__पढ़ो_mounts(काष्ठा fs *fs)
अणु
	bool found = false;
	अक्षर type[100];
	खाता *fp;

	fp = ख_खोलो("/proc/mounts", "r");
	अगर (fp == शून्य)
		वापस शून्य;

	जबतक (!found &&
	       ख_पूछो(fp, "%*s %" STR(PATH_MAX) "s %99s %*s %*d %*d\n",
		      fs->path, type) == 2) अणु

		अगर (म_भेद(type, fs->name) == 0)
			found = true;
	पूर्ण

	ख_बंद(fp);
	fs->checked = true;
	वापस fs->found = found;
पूर्ण

अटल पूर्णांक fs__valid_mount(स्थिर अक्षर *fs, दीर्घ magic)
अणु
	काष्ठा statfs st_fs;

	अगर (statfs(fs, &st_fs) < 0)
		वापस -ENOENT;
	अन्यथा अगर ((दीर्घ)st_fs.f_type != magic)
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल bool fs__check_mounts(काष्ठा fs *fs)
अणु
	स्थिर अक्षर * स्थिर *ptr;

	ptr = fs->mounts;
	जबतक (*ptr) अणु
		अगर (fs__valid_mount(*ptr, fs->magic) == 0) अणु
			fs->found = true;
			म_नकल(fs->path, *ptr);
			वापस true;
		पूर्ण
		ptr++;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम mem_बड़े(अक्षर *f, माप_प्रकार len)
अणु
	जबतक (len) अणु
		*f = बड़े(*f);
		f++;
		len--;
	पूर्ण
पूर्ण

/*
 * Check क्रम "NAME_PATH" environment variable to override fs location (क्रम
 * testing). This matches the recommendation in Documentation/admin-guide/sysfs-rules.rst
 * क्रम SYSFS_PATH.
 */
अटल bool fs__env_override(काष्ठा fs *fs)
अणु
	अक्षर *override_path;
	माप_प्रकार name_len = म_माप(fs->name);
	/* name + "_PATH" + '\0' */
	अक्षर upper_name[name_len + 5 + 1];

	स_नकल(upper_name, fs->name, name_len);
	mem_बड़े(upper_name, name_len);
	म_नकल(&upper_name[name_len], "_PATH");

	override_path = दो_पर्या(upper_name);
	अगर (!override_path)
		वापस false;

	fs->found = true;
	fs->checked = true;
	म_नकलन(fs->path, override_path, माप(fs->path) - 1);
	fs->path[माप(fs->path) - 1] = '\0';
	वापस true;
पूर्ण

अटल स्थिर अक्षर *fs__get_mountpoपूर्णांक(काष्ठा fs *fs)
अणु
	अगर (fs__env_override(fs))
		वापस fs->path;

	अगर (fs__check_mounts(fs))
		वापस fs->path;

	अगर (fs__पढ़ो_mounts(fs))
		वापस fs->path;

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *fs__mountpoपूर्णांक(पूर्णांक idx)
अणु
	काष्ठा fs *fs = &fs__entries[idx];

	अगर (fs->found)
		वापस (स्थिर अक्षर *)fs->path;

	/* the mount poपूर्णांक was alपढ़ोy checked क्रम the mount poपूर्णांक
	 * but and did not exist, so वापस शून्य to aव्योम scanning again.
	 * This makes the found and not found paths cost equivalent
	 * in हाल of multiple calls.
	 */
	अगर (fs->checked)
		वापस शून्य;

	वापस fs__get_mountpoपूर्णांक(fs);
पूर्ण

अटल स्थिर अक्षर *mount_overload(काष्ठा fs *fs)
अणु
	माप_प्रकार name_len = म_माप(fs->name);
	/* "PERF_" + name + "_ENVIRONMENT" + '\0' */
	अक्षर upper_name[5 + name_len + 12 + 1];

	snम_लिखो(upper_name, name_len, "PERF_%s_ENVIRONMENT", fs->name);
	mem_बड़े(upper_name, name_len);

	वापस दो_पर्या(upper_name) ?: *fs->mounts;
पूर्ण

अटल स्थिर अक्षर *fs__mount(पूर्णांक idx)
अणु
	काष्ठा fs *fs = &fs__entries[idx];
	स्थिर अक्षर *mountpoपूर्णांक;

	अगर (fs__mountpoपूर्णांक(idx))
		वापस (स्थिर अक्षर *)fs->path;

	mountpoपूर्णांक = mount_overload(fs);

	अगर (mount(शून्य, mountpoपूर्णांक, fs->name, 0, शून्य) < 0)
		वापस शून्य;

	वापस fs__check_mounts(fs) ? fs->path : शून्य;
पूर्ण

#घोषणा FS(name, idx)				\
स्थिर अक्षर *name##__mountpoपूर्णांक(व्योम)		\
अणु						\
	वापस fs__mountpoपूर्णांक(idx);		\
पूर्ण						\
						\
स्थिर अक्षर *name##__mount(व्योम)			\
अणु						\
	वापस fs__mount(idx);			\
पूर्ण						\
						\
bool name##__configured(व्योम)			\
अणु						\
	वापस name##__mountpoपूर्णांक() != शून्य;	\
पूर्ण

FS(sysfs,   FS__SYSFS);
FS(procfs,  FS__PROCFS);
FS(debugfs, FS__DEBUGFS);
FS(tracefs, FS__TRACEFS);
FS(hugetlbfs, FS__HUGETLBFS);
FS(bpf_fs, FS__BPF_FS);

पूर्णांक filename__पढ़ो_पूर्णांक(स्थिर अक्षर *filename, पूर्णांक *value)
अणु
	अक्षर line[64];
	पूर्णांक fd = खोलो(filename, O_RDONLY), err = -1;

	अगर (fd < 0)
		वापस -1;

	अगर (पढ़ो(fd, line, माप(line)) > 0) अणु
		*value = म_से_प(line);
		err = 0;
	पूर्ण

	बंद(fd);
	वापस err;
पूर्ण

अटल पूर्णांक filename__पढ़ो_ull_base(स्थिर अक्षर *filename,
				   अचिन्हित दीर्घ दीर्घ *value, पूर्णांक base)
अणु
	अक्षर line[64];
	पूर्णांक fd = खोलो(filename, O_RDONLY), err = -1;

	अगर (fd < 0)
		वापस -1;

	अगर (पढ़ो(fd, line, माप(line)) > 0) अणु
		*value = म_से_अदीर्घl(line, शून्य, base);
		अगर (*value != ULदीर्घ_उच्च)
			err = 0;
	पूर्ण

	बंद(fd);
	वापस err;
पूर्ण

/*
 * Parses @value out of @filename with म_से_अदीर्घl.
 * By using 16 क्रम base to treat the number as hex.
 */
पूर्णांक filename__पढ़ो_xll(स्थिर अक्षर *filename, अचिन्हित दीर्घ दीर्घ *value)
अणु
	वापस filename__पढ़ो_ull_base(filename, value, 16);
पूर्ण

/*
 * Parses @value out of @filename with म_से_अदीर्घl.
 * By using 0 क्रम base, the म_से_अदीर्घl detects the
 * base स्वतःmatically (see man म_से_अदीर्घl).
 */
पूर्णांक filename__पढ़ो_ull(स्थिर अक्षर *filename, अचिन्हित दीर्घ दीर्घ *value)
अणु
	वापस filename__पढ़ो_ull_base(filename, value, 0);
पूर्ण

#घोषणा STRERR_बफ_मानE  128     /* For the buffer size of म_त्रुटि_r */

पूर्णांक filename__पढ़ो_str(स्थिर अक्षर *filename, अक्षर **buf, माप_प्रकार *sizep)
अणु
	माप_प्रकार size = 0, alloc_size = 0;
	व्योम *bf = शून्य, *nbf;
	पूर्णांक fd, n, err = 0;
	अक्षर sbuf[STRERR_बफ_मानE];

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0)
		वापस -त्रुटि_सं;

	करो अणु
		अगर (size == alloc_size) अणु
			alloc_size += बफ_मान;
			nbf = पुनः_स्मृति(bf, alloc_size);
			अगर (!nbf) अणु
				err = -ENOMEM;
				अवरोध;
			पूर्ण

			bf = nbf;
		पूर्ण

		n = पढ़ो(fd, bf + size, alloc_size - size);
		अगर (n < 0) अणु
			अगर (size) अणु
				pr_warn("read failed %d: %s\n", त्रुटि_सं,
					म_त्रुटि_r(त्रुटि_सं, sbuf, माप(sbuf)));
				err = 0;
			पूर्ण अन्यथा
				err = -त्रुटि_सं;

			अवरोध;
		पूर्ण

		size += n;
	पूर्ण जबतक (n > 0);

	अगर (!err) अणु
		*sizep = size;
		*buf   = bf;
	पूर्ण अन्यथा
		मुक्त(bf);

	बंद(fd);
	वापस err;
पूर्ण

पूर्णांक filename__ग_लिखो_पूर्णांक(स्थिर अक्षर *filename, पूर्णांक value)
अणु
	पूर्णांक fd = खोलो(filename, O_WRONLY), err = -1;
	अक्षर buf[64];

	अगर (fd < 0)
		वापस err;

	प्र_लिखो(buf, "%d", value);
	अगर (ग_लिखो(fd, buf, माप(buf)) == माप(buf))
		err = 0;

	बंद(fd);
	वापस err;
पूर्ण

पूर्णांक procfs__पढ़ो_str(स्थिर अक्षर *entry, अक्षर **buf, माप_प्रकार *sizep)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *procfs = procfs__mountpoपूर्णांक();

	अगर (!procfs)
		वापस -1;

	snम_लिखो(path, माप(path), "%s/%s", procfs, entry);

	वापस filename__पढ़ो_str(path, buf, sizep);
पूर्ण

अटल पूर्णांक sysfs__पढ़ो_ull_base(स्थिर अक्षर *entry,
				अचिन्हित दीर्घ दीर्घ *value, पूर्णांक base)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस -1;

	snम_लिखो(path, माप(path), "%s/%s", sysfs, entry);

	वापस filename__पढ़ो_ull_base(path, value, base);
पूर्ण

पूर्णांक sysfs__पढ़ो_xll(स्थिर अक्षर *entry, अचिन्हित दीर्घ दीर्घ *value)
अणु
	वापस sysfs__पढ़ो_ull_base(entry, value, 16);
पूर्ण

पूर्णांक sysfs__पढ़ो_ull(स्थिर अक्षर *entry, अचिन्हित दीर्घ दीर्घ *value)
अणु
	वापस sysfs__पढ़ो_ull_base(entry, value, 0);
पूर्ण

पूर्णांक sysfs__पढ़ो_पूर्णांक(स्थिर अक्षर *entry, पूर्णांक *value)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस -1;

	snम_लिखो(path, माप(path), "%s/%s", sysfs, entry);

	वापस filename__पढ़ो_पूर्णांक(path, value);
पूर्ण

पूर्णांक sysfs__पढ़ो_str(स्थिर अक्षर *entry, अक्षर **buf, माप_प्रकार *sizep)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस -1;

	snम_लिखो(path, माप(path), "%s/%s", sysfs, entry);

	वापस filename__पढ़ो_str(path, buf, sizep);
पूर्ण

पूर्णांक sysfs__पढ़ो_bool(स्थिर अक्षर *entry, bool *value)
अणु
	अक्षर *buf;
	माप_प्रकार size;
	पूर्णांक ret;

	ret = sysfs__पढ़ो_str(entry, &buf, &size);
	अगर (ret < 0)
		वापस ret;

	चयन (buf[0]) अणु
	हाल '1':
	हाल 'y':
	हाल 'Y':
		*value = true;
		अवरोध;
	हाल '0':
	हाल 'n':
	हाल 'N':
		*value = false;
		अवरोध;
	शेष:
		ret = -1;
	पूर्ण

	मुक्त(buf);

	वापस ret;
पूर्ण
पूर्णांक sysctl__पढ़ो_पूर्णांक(स्थिर अक्षर *sysctl, पूर्णांक *value)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *procfs = procfs__mountpoपूर्णांक();

	अगर (!procfs)
		वापस -1;

	snम_लिखो(path, माप(path), "%s/sys/%s", procfs, sysctl);

	वापस filename__पढ़ो_पूर्णांक(path, value);
पूर्ण

पूर्णांक sysfs__ग_लिखो_पूर्णांक(स्थिर अक्षर *entry, पूर्णांक value)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs)
		वापस -1;

	अगर (snम_लिखो(path, माप(path), "%s/%s", sysfs, entry) >= PATH_MAX)
		वापस -1;

	वापस filename__ग_लिखो_पूर्णांक(path, value);
पूर्ण
