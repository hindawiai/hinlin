<शैली गुरु>
/*
 *  sync / sw_sync असलtraction
 *  Copyright 2015-2016 Collabora Ltd.
 *
 *  Based on the implementation from the Android Open Source Project,
 *
 *  Copyright 2012 Google, Inc
 *
 *  Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 *  copy of this software and associated करोcumentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to करो so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <fcntl.h>
#समावेश <दो_स्मृति.h>
#समावेश <poll.h>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>

#समावेश "sync.h"
#समावेश "sw_sync.h"

#समावेश <linux/sync_file.h>


/* SW_SYNC ioctls */
काष्ठा sw_sync_create_fence_data अणु
	__u32	value;
	अक्षर	name[32];
	__s32	fence;
पूर्ण;

#घोषणा SW_SYNC_IOC_MAGIC		'W'
#घोषणा SW_SYNC_IOC_CREATE_FENCE	_IOWR(SW_SYNC_IOC_MAGIC, 0,\
					      काष्ठा sw_sync_create_fence_data)
#घोषणा SW_SYNC_IOC_INC			_IOW(SW_SYNC_IOC_MAGIC, 1, __u32)


पूर्णांक sync_रुको(पूर्णांक fd, पूर्णांक समयout)
अणु
	काष्ठा pollfd fds;

	fds.fd = fd;
	fds.events = POLLIN | POLLERR;

	वापस poll(&fds, 1, समयout);
पूर्ण

पूर्णांक sync_merge(स्थिर अक्षर *name, पूर्णांक fd1, पूर्णांक fd2)
अणु
	काष्ठा sync_merge_data data = अणुपूर्ण;
	पूर्णांक err;

	data.fd2 = fd2;
	म_नकलन(data.name, name, माप(data.name) - 1);
	data.name[माप(data.name) - 1] = '\0';

	err = ioctl(fd1, SYNC_IOC_MERGE, &data);
	अगर (err < 0)
		वापस err;

	वापस data.fence;
पूर्ण

अटल काष्ठा sync_file_info *sync_file_info(पूर्णांक fd)
अणु
	काष्ठा sync_file_info *info;
	काष्ठा sync_fence_info *fence_info;
	पूर्णांक err, num_fences;

	info = सुस्मृति(1, माप(*info));
	अगर (info == शून्य)
		वापस शून्य;

	err = ioctl(fd, SYNC_IOC_खाता_INFO, info);
	अगर (err < 0) अणु
		मुक्त(info);
		वापस शून्य;
	पूर्ण

	num_fences = info->num_fences;

	अगर (num_fences) अणु
		info->flags = 0;
		info->num_fences = num_fences;

		fence_info = सुस्मृति(num_fences, माप(*fence_info));
		अगर (!fence_info) अणु
			मुक्त(info);
			वापस शून्य;
		पूर्ण

		info->sync_fence_info = (uपूर्णांक64_t)(अचिन्हित दीर्घ)fence_info;

		err = ioctl(fd, SYNC_IOC_खाता_INFO, info);
		अगर (err < 0) अणु
			मुक्त(fence_info);
			मुक्त(info);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस info;
पूर्ण

अटल व्योम sync_file_info_मुक्त(काष्ठा sync_file_info *info)
अणु
	मुक्त((व्योम *)(अचिन्हित दीर्घ)info->sync_fence_info);
	मुक्त(info);
पूर्ण

पूर्णांक sync_fence_size(पूर्णांक fd)
अणु
	पूर्णांक count;
	काष्ठा sync_file_info *info = sync_file_info(fd);

	अगर (!info)
		वापस 0;

	count = info->num_fences;

	sync_file_info_मुक्त(info);

	वापस count;
पूर्ण

पूर्णांक sync_fence_count_with_status(पूर्णांक fd, पूर्णांक status)
अणु
	अचिन्हित पूर्णांक i, count = 0;
	काष्ठा sync_fence_info *fence_info = शून्य;
	काष्ठा sync_file_info *info = sync_file_info(fd);

	अगर (!info)
		वापस -1;

	fence_info = (काष्ठा sync_fence_info *)(अचिन्हित दीर्घ)info->sync_fence_info;
	क्रम (i = 0 ; i < info->num_fences ; i++) अणु
		अगर (fence_info[i].status == status)
			count++;
	पूर्ण

	sync_file_info_मुक्त(info);

	वापस count;
पूर्ण

पूर्णांक sw_sync_समयline_create(व्योम)
अणु
	वापस खोलो("/sys/kernel/debug/sync/sw_sync", O_RDWR);
पूर्ण

पूर्णांक sw_sync_समयline_inc(पूर्णांक fd, अचिन्हित पूर्णांक count)
अणु
	__u32 arg = count;

	वापस ioctl(fd, SW_SYNC_IOC_INC, &arg);
पूर्ण

पूर्णांक sw_sync_समयline_is_valid(पूर्णांक fd)
अणु
	पूर्णांक status;

	अगर (fd == -1)
		वापस 0;

	status = fcntl(fd, F_GETFD, 0);
	वापस (status >= 0);
पूर्ण

व्योम sw_sync_समयline_destroy(पूर्णांक fd)
अणु
	अगर (sw_sync_समयline_is_valid(fd))
		बंद(fd);
पूर्ण

पूर्णांक sw_sync_fence_create(पूर्णांक fd, स्थिर अक्षर *name, अचिन्हित पूर्णांक value)
अणु
	काष्ठा sw_sync_create_fence_data data = अणुपूर्ण;
	पूर्णांक err;

	data.value = value;
	म_नकलन(data.name, name, माप(data.name) - 1);
	data.name[माप(data.name) - 1] = '\0';

	err = ioctl(fd, SW_SYNC_IOC_CREATE_FENCE, &data);
	अगर (err < 0)
		वापस err;

	वापस data.fence;
पूर्ण

पूर्णांक sw_sync_fence_is_valid(पूर्णांक fd)
अणु
	/* Same code! */
	वापस sw_sync_समयline_is_valid(fd);
पूर्ण

व्योम sw_sync_fence_destroy(पूर्णांक fd)
अणु
	अगर (sw_sync_fence_is_valid(fd))
		बंद(fd);
पूर्ण
