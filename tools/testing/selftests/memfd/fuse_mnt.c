<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * memfd test file-प्रणाली
 * This file uses FUSE to create a dummy file-प्रणाली with only one file /memfd.
 * This file is पढ़ो-only and takes 1s per पढ़ो.
 *
 * This file-प्रणाली is used by the memfd test-हालs to क्रमce the kernel to pin
 * pages during पढ़ोs(). Due to the 1s delay of this file-प्रणाली, this is a
 * nice way to test race-conditions against get_user_pages() in the kernel.
 *
 * We use direct_io==1 to क्रमce the kernel to use direct-IO क्रम this
 * file-प्रणाली.
 */

#घोषणा FUSE_USE_VERSION 26

#समावेश <fuse.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>

अटल स्थिर अक्षर memfd_content[] = "memfd-example-content";
अटल स्थिर अक्षर memfd_path[] = "/memfd";

अटल पूर्णांक memfd_getattr(स्थिर अक्षर *path, काष्ठा stat *st)
अणु
	स_रखो(st, 0, माप(*st));

	अगर (!म_भेद(path, "/")) अणु
		st->st_mode = S_IFसूची | 0755;
		st->st_nlink = 2;
	पूर्ण अन्यथा अगर (!म_भेद(path, memfd_path)) अणु
		st->st_mode = S_IFREG | 0444;
		st->st_nlink = 1;
		st->st_size = म_माप(memfd_content);
	पूर्ण अन्यथा अणु
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक memfd_सूची_पढ़ो(स्थिर अक्षर *path,
			 व्योम *buf,
			 fuse_fill_dir_t filler,
			 off_t offset,
			 काष्ठा fuse_file_info *fi)
अणु
	अगर (म_भेद(path, "/"))
		वापस -ENOENT;

	filler(buf, ".", शून्य, 0);
	filler(buf, "..", शून्य, 0);
	filler(buf, memfd_path + 1, शून्य, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक memfd_खोलो(स्थिर अक्षर *path, काष्ठा fuse_file_info *fi)
अणु
	अगर (म_भेद(path, memfd_path))
		वापस -ENOENT;

	अगर ((fi->flags & 3) != O_RDONLY)
		वापस -EACCES;

	/* क्रमce direct-IO */
	fi->direct_io = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक memfd_पढ़ो(स्थिर अक्षर *path,
		      अक्षर *buf,
		      माप_प्रकार size,
		      off_t offset,
		      काष्ठा fuse_file_info *fi)
अणु
	माप_प्रकार len;

	अगर (म_भेद(path, memfd_path) != 0)
		वापस -ENOENT;

	sleep(1);

	len = म_माप(memfd_content);
	अगर (offset < len) अणु
		अगर (offset + size > len)
			size = len - offset;

		स_नकल(buf, memfd_content + offset, size);
	पूर्ण अन्यथा अणु
		size = 0;
	पूर्ण

	वापस size;
पूर्ण

अटल काष्ठा fuse_operations memfd_ops = अणु
	.getattr	= memfd_getattr,
	.सूची_पढ़ो	= memfd_सूची_पढ़ो,
	.खोलो		= memfd_खोलो,
	.पढ़ो		= memfd_पढ़ो,
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस fuse_मुख्य(argc, argv, &memfd_ops, शून्य);
पूर्ण
