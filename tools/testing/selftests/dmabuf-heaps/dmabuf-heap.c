<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>

#समावेश <linux/dma-buf.h>
#समावेश <drm/drm.h>

#समावेश "../../../../include/uapi/linux/dma-heap.h"

#घोषणा DEVPATH "/dev/dma_heap"

अटल पूर्णांक check_vgem(पूर्णांक fd)
अणु
	drm_version_t version = अणु 0 पूर्ण;
	अक्षर name[5];
	पूर्णांक ret;

	version.name_len = 4;
	version.name = name;

	ret = ioctl(fd, DRM_IOCTL_VERSION, &version);
	अगर (ret)
		वापस 0;

	वापस !म_भेद(name, "vgem");
पूर्ण

अटल पूर्णांक खोलो_vgem(व्योम)
अणु
	पूर्णांक i, fd;
	स्थिर अक्षर *drmstr = "/dev/dri/card";

	fd = -1;
	क्रम (i = 0; i < 16; i++) अणु
		अक्षर name[80];

		snम_लिखो(name, 80, "%s%u", drmstr, i);

		fd = खोलो(name, O_RDWR);
		अगर (fd < 0)
			जारी;

		अगर (!check_vgem(fd)) अणु
			बंद(fd);
			fd = -1;
			जारी;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस fd;
पूर्ण

अटल पूर्णांक import_vgem_fd(पूर्णांक vgem_fd, पूर्णांक dma_buf_fd, uपूर्णांक32_t *handle)
अणु
	काष्ठा drm_prime_handle import_handle = अणु
		.fd = dma_buf_fd,
		.flags = 0,
		.handle = 0,
	 पूर्ण;
	पूर्णांक ret;

	ret = ioctl(vgem_fd, DRM_IOCTL_PRIME_FD_TO_HANDLE, &import_handle);
	अगर (ret == 0)
		*handle = import_handle.handle;
	वापस ret;
पूर्ण

अटल व्योम बंद_handle(पूर्णांक vgem_fd, uपूर्णांक32_t handle)
अणु
	काष्ठा drm_gem_बंद बंद = अणु
		.handle = handle,
	पूर्ण;

	ioctl(vgem_fd, DRM_IOCTL_GEM_CLOSE, &बंद);
पूर्ण

अटल पूर्णांक dmabuf_heap_खोलो(अक्षर *name)
अणु
	पूर्णांक ret, fd;
	अक्षर buf[256];

	ret = snम_लिखो(buf, 256, "%s/%s", DEVPATH, name);
	अगर (ret < 0) अणु
		म_लिखो("snprintf failed!\n");
		वापस ret;
	पूर्ण

	fd = खोलो(buf, O_RDWR);
	अगर (fd < 0)
		म_लिखो("open %s failed!\n", buf);
	वापस fd;
पूर्ण

अटल पूर्णांक dmabuf_heap_alloc_fdflags(पूर्णांक fd, माप_प्रकार len, अचिन्हित पूर्णांक fd_flags,
				     अचिन्हित पूर्णांक heap_flags, पूर्णांक *dmabuf_fd)
अणु
	काष्ठा dma_heap_allocation_data data = अणु
		.len = len,
		.fd = 0,
		.fd_flags = fd_flags,
		.heap_flags = heap_flags,
	पूर्ण;
	पूर्णांक ret;

	अगर (!dmabuf_fd)
		वापस -EINVAL;

	ret = ioctl(fd, DMA_HEAP_IOCTL_ALLOC, &data);
	अगर (ret < 0)
		वापस ret;
	*dmabuf_fd = (पूर्णांक)data.fd;
	वापस ret;
पूर्ण

अटल पूर्णांक dmabuf_heap_alloc(पूर्णांक fd, माप_प्रकार len, अचिन्हित पूर्णांक flags,
			     पूर्णांक *dmabuf_fd)
अणु
	वापस dmabuf_heap_alloc_fdflags(fd, len, O_RDWR | O_CLOEXEC, flags,
					 dmabuf_fd);
पूर्ण

अटल पूर्णांक dmabuf_sync(पूर्णांक fd, पूर्णांक start_stop)
अणु
	काष्ठा dma_buf_sync sync = अणु
		.flags = start_stop | DMA_BUF_SYNC_RW,
	पूर्ण;

	वापस ioctl(fd, DMA_BUF_IOCTL_SYNC, &sync);
पूर्ण

#घोषणा ONE_MEG (1024 * 1024)

अटल पूर्णांक test_alloc_and_import(अक्षर *heap_name)
अणु
	पूर्णांक heap_fd = -1, dmabuf_fd = -1, importer_fd = -1;
	uपूर्णांक32_t handle = 0;
	व्योम *p = शून्य;
	पूर्णांक ret;

	heap_fd = dmabuf_heap_खोलो(heap_name);
	अगर (heap_fd < 0)
		वापस -1;

	म_लिखो("  Testing allocation and importing:  ");
	ret = dmabuf_heap_alloc(heap_fd, ONE_MEG, 0, &dmabuf_fd);
	अगर (ret) अणु
		म_लिखो("FAIL (Allocation Failed!)\n");
		ret = -1;
		जाओ out;
	पूर्ण
	/* mmap and ग_लिखो a simple pattern */
	p = mmap(शून्य,
		 ONE_MEG,
		 PROT_READ | PROT_WRITE,
		 MAP_SHARED,
		 dmabuf_fd,
		 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("FAIL (mmap() failed)\n");
		ret = -1;
		जाओ out;
	पूर्ण

	dmabuf_sync(dmabuf_fd, DMA_BUF_SYNC_START);
	स_रखो(p, 1, ONE_MEG / 2);
	स_रखो((अक्षर *)p + ONE_MEG / 2, 0, ONE_MEG / 2);
	dmabuf_sync(dmabuf_fd, DMA_BUF_SYNC_END);

	importer_fd = खोलो_vgem();
	अगर (importer_fd < 0) अणु
		ret = importer_fd;
		म_लिखो("(Could not open vgem - skipping):  ");
	पूर्ण अन्यथा अणु
		ret = import_vgem_fd(importer_fd, dmabuf_fd, &handle);
		अगर (ret < 0) अणु
			म_लिखो("FAIL (Failed to import buffer)\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = dmabuf_sync(dmabuf_fd, DMA_BUF_SYNC_START);
	अगर (ret < 0) अणु
		म_लिखो("FAIL (DMA_BUF_SYNC_START failed!)\n");
		जाओ out;
	पूर्ण

	स_रखो(p, 0xff, ONE_MEG);
	ret = dmabuf_sync(dmabuf_fd, DMA_BUF_SYNC_END);
	अगर (ret < 0) अणु
		म_लिखो("FAIL (DMA_BUF_SYNC_END failed!)\n");
		जाओ out;
	पूर्ण

	बंद_handle(importer_fd, handle);
	ret = 0;
	म_लिखो(" OK\n");
out:
	अगर (p)
		munmap(p, ONE_MEG);
	अगर (importer_fd >= 0)
		बंद(importer_fd);
	अगर (dmabuf_fd >= 0)
		बंद(dmabuf_fd);
	अगर (heap_fd >= 0)
		बंद(heap_fd);

	वापस ret;
पूर्ण

अटल पूर्णांक test_alloc_zeroed(अक्षर *heap_name, माप_प्रकार size)
अणु
	पूर्णांक heap_fd = -1, dmabuf_fd[32];
	पूर्णांक i, j, ret;
	व्योम *p = शून्य;
	अक्षर *c;

	म_लिखो("  Testing alloced %ldk buffers are zeroed:  ", size / 1024);
	heap_fd = dmabuf_heap_खोलो(heap_name);
	अगर (heap_fd < 0)
		वापस -1;

	/* Allocate and fill a bunch of buffers */
	क्रम (i = 0; i < 32; i++) अणु
		ret = dmabuf_heap_alloc(heap_fd, size, 0, &dmabuf_fd[i]);
		अगर (ret < 0) अणु
			म_लिखो("FAIL (Allocation (%i) failed)\n", i);
			जाओ out;
		पूर्ण
		/* mmap and fill with simple pattern */
		p = mmap(शून्य, size, PROT_READ | PROT_WRITE, MAP_SHARED, dmabuf_fd[i], 0);
		अगर (p == MAP_FAILED) अणु
			म_लिखो("FAIL (mmap() failed!)\n");
			ret = -1;
			जाओ out;
		पूर्ण
		dmabuf_sync(dmabuf_fd[i], DMA_BUF_SYNC_START);
		स_रखो(p, 0xff, size);
		dmabuf_sync(dmabuf_fd[i], DMA_BUF_SYNC_END);
		munmap(p, size);
	पूर्ण
	/* बंद them all */
	क्रम (i = 0; i < 32; i++)
		बंद(dmabuf_fd[i]);

	/* Allocate and validate all buffers are zeroed */
	क्रम (i = 0; i < 32; i++) अणु
		ret = dmabuf_heap_alloc(heap_fd, size, 0, &dmabuf_fd[i]);
		अगर (ret < 0) अणु
			म_लिखो("FAIL (Allocation (%i) failed)\n", i);
			जाओ out;
		पूर्ण

		/* mmap and validate everything is zero */
		p = mmap(शून्य, size, PROT_READ | PROT_WRITE, MAP_SHARED, dmabuf_fd[i], 0);
		अगर (p == MAP_FAILED) अणु
			म_लिखो("FAIL (mmap() failed!)\n");
			ret = -1;
			जाओ out;
		पूर्ण
		dmabuf_sync(dmabuf_fd[i], DMA_BUF_SYNC_START);
		c = (अक्षर *)p;
		क्रम (j = 0; j < size; j++) अणु
			अगर (c[j] != 0) अणु
				म_लिखो("FAIL (Allocated buffer not zeroed @ %i)\n", j);
				अवरोध;
			पूर्ण
		पूर्ण
		dmabuf_sync(dmabuf_fd[i], DMA_BUF_SYNC_END);
		munmap(p, size);
	पूर्ण
	/* बंद them all */
	क्रम (i = 0; i < 32; i++)
		बंद(dmabuf_fd[i]);

	बंद(heap_fd);
	म_लिखो("OK\n");
	वापस 0;

out:
	जबतक (i > 0) अणु
		बंद(dmabuf_fd[i]);
		i--;
	पूर्ण
	बंद(heap_fd);
	वापस ret;
पूर्ण

/* Test the ioctl version compatibility w/ a smaller काष्ठाure then expected */
अटल पूर्णांक dmabuf_heap_alloc_older(पूर्णांक fd, माप_प्रकार len, अचिन्हित पूर्णांक flags,
				   पूर्णांक *dmabuf_fd)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक older_alloc_ioctl;
	काष्ठा dma_heap_allocation_data_smaller अणु
		__u64 len;
		__u32 fd;
		__u32 fd_flags;
	पूर्ण data = अणु
		.len = len,
		.fd = 0,
		.fd_flags = O_RDWR | O_CLOEXEC,
	पूर्ण;

	older_alloc_ioctl = _IOWR(DMA_HEAP_IOC_MAGIC, 0x0,
				  काष्ठा dma_heap_allocation_data_smaller);
	अगर (!dmabuf_fd)
		वापस -EINVAL;

	ret = ioctl(fd, older_alloc_ioctl, &data);
	अगर (ret < 0)
		वापस ret;
	*dmabuf_fd = (पूर्णांक)data.fd;
	वापस ret;
पूर्ण

/* Test the ioctl version compatibility w/ a larger काष्ठाure then expected */
अटल पूर्णांक dmabuf_heap_alloc_newer(पूर्णांक fd, माप_प्रकार len, अचिन्हित पूर्णांक flags,
				   पूर्णांक *dmabuf_fd)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक newer_alloc_ioctl;
	काष्ठा dma_heap_allocation_data_bigger अणु
		__u64 len;
		__u32 fd;
		__u32 fd_flags;
		__u64 heap_flags;
		__u64 garbage1;
		__u64 garbage2;
		__u64 garbage3;
	पूर्ण data = अणु
		.len = len,
		.fd = 0,
		.fd_flags = O_RDWR | O_CLOEXEC,
		.heap_flags = flags,
		.garbage1 = 0xffffffff,
		.garbage2 = 0x88888888,
		.garbage3 = 0x11111111,
	पूर्ण;

	newer_alloc_ioctl = _IOWR(DMA_HEAP_IOC_MAGIC, 0x0,
				  काष्ठा dma_heap_allocation_data_bigger);
	अगर (!dmabuf_fd)
		वापस -EINVAL;

	ret = ioctl(fd, newer_alloc_ioctl, &data);
	अगर (ret < 0)
		वापस ret;

	*dmabuf_fd = (पूर्णांक)data.fd;
	वापस ret;
पूर्ण

अटल पूर्णांक test_alloc_compat(अक्षर *heap_name)
अणु
	पूर्णांक heap_fd = -1, dmabuf_fd = -1;
	पूर्णांक ret;

	heap_fd = dmabuf_heap_खोलो(heap_name);
	अगर (heap_fd < 0)
		वापस -1;

	म_लिखो("  Testing (theoretical)older alloc compat:  ");
	ret = dmabuf_heap_alloc_older(heap_fd, ONE_MEG, 0, &dmabuf_fd);
	अगर (ret) अणु
		म_लिखो("FAIL (Older compat allocation failed!)\n");
		ret = -1;
		जाओ out;
	पूर्ण
	बंद(dmabuf_fd);
	म_लिखो("OK\n");

	म_लिखो("  Testing (theoretical)newer alloc compat:  ");
	ret = dmabuf_heap_alloc_newer(heap_fd, ONE_MEG, 0, &dmabuf_fd);
	अगर (ret) अणु
		म_लिखो("FAIL (Newer compat allocation failed!)\n");
		ret = -1;
		जाओ out;
	पूर्ण
	म_लिखो("OK\n");
out:
	अगर (dmabuf_fd >= 0)
		बंद(dmabuf_fd);
	अगर (heap_fd >= 0)
		बंद(heap_fd);

	वापस ret;
पूर्ण

अटल पूर्णांक test_alloc_errors(अक्षर *heap_name)
अणु
	पूर्णांक heap_fd = -1, dmabuf_fd = -1;
	पूर्णांक ret;

	heap_fd = dmabuf_heap_खोलो(heap_name);
	अगर (heap_fd < 0)
		वापस -1;

	म_लिखो("  Testing expected error cases:  ");
	ret = dmabuf_heap_alloc(0, ONE_MEG, 0x111111, &dmabuf_fd);
	अगर (!ret) अणु
		म_लिखो("FAIL (Did not see expected error (invalid fd)!)\n");
		ret = -1;
		जाओ out;
	पूर्ण

	ret = dmabuf_heap_alloc(heap_fd, ONE_MEG, 0x111111, &dmabuf_fd);
	अगर (!ret) अणु
		म_लिखो("FAIL (Did not see expected error (invalid heap flags)!)\n");
		ret = -1;
		जाओ out;
	पूर्ण

	ret = dmabuf_heap_alloc_fdflags(heap_fd, ONE_MEG,
					~(O_RDWR | O_CLOEXEC), 0, &dmabuf_fd);
	अगर (!ret) अणु
		म_लिखो("FAIL (Did not see expected error (invalid fd flags)!)\n");
		ret = -1;
		जाओ out;
	पूर्ण

	म_लिखो("OK\n");
	ret = 0;
out:
	अगर (dmabuf_fd >= 0)
		बंद(dmabuf_fd);
	अगर (heap_fd >= 0)
		बंद(heap_fd);

	वापस ret;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	सूची *d;
	काष्ठा dirent *dir;
	पूर्णांक ret = -1;

	d = सूची_खोलो(DEVPATH);
	अगर (!d) अणु
		म_लिखो("No %s directory?\n", DEVPATH);
		वापस -1;
	पूर्ण

	जबतक ((dir = सूची_पढ़ो(d)) != शून्य) अणु
		अगर (!म_भेदन(dir->d_name, ".", 2))
			जारी;
		अगर (!म_भेदन(dir->d_name, "..", 3))
			जारी;

		म_लिखो("Testing heap: %s\n", dir->d_name);
		म_लिखो("=======================================\n");
		ret = test_alloc_and_import(dir->d_name);
		अगर (ret)
			अवरोध;

		ret = test_alloc_zeroed(dir->d_name, 4 * 1024);
		अगर (ret)
			अवरोध;

		ret = test_alloc_zeroed(dir->d_name, ONE_MEG);
		अगर (ret)
			अवरोध;

		ret = test_alloc_compat(dir->d_name);
		अगर (ret)
			अवरोध;

		ret = test_alloc_errors(dir->d_name);
		अगर (ret)
			अवरोध;
	पूर्ण
	बंद_सूची(d);

	वापस ret;
पूर्ण
