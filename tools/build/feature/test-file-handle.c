<शैली गुरु>
#घोषणा _GNU_SOURCE
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा अणु
		काष्ठा file_handle fh;
		uपूर्णांक64_t cgroup_id;
	पूर्ण handle;
	पूर्णांक mount_id;

	name_to_handle_at(AT_FDCWD, "/", &handle.fh, &mount_id, 0);
	वापस 0;
पूर्ण
