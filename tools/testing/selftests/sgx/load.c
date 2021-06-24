<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2016-20 Intel Corporation. */

#समावेश <निश्चित.स>
#समावेश <elf.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश "defines.h"
#समावेश "main.h"

व्योम encl_delete(काष्ठा encl *encl)
अणु
	अगर (encl->encl_base)
		munmap((व्योम *)encl->encl_base, encl->encl_size);

	अगर (encl->bin)
		munmap(encl->bin, encl->bin_size);

	अगर (encl->fd)
		बंद(encl->fd);

	अगर (encl->segment_tbl)
		मुक्त(encl->segment_tbl);

	स_रखो(encl, 0, माप(*encl));
पूर्ण

अटल bool encl_map_bin(स्थिर अक्षर *path, काष्ठा encl *encl)
अणु
	काष्ठा stat sb;
	व्योम *bin;
	पूर्णांक ret;
	पूर्णांक fd;

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)  अणु
		लिखो_त्रुटि("enclave executable open()");
		वापस false;
	पूर्ण

	ret = stat(path, &sb);
	अगर (ret) अणु
		लिखो_त्रुटि("enclave executable stat()");
		जाओ err;
	पूर्ण

	bin = mmap(शून्य, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	अगर (bin == MAP_FAILED) अणु
		लिखो_त्रुटि("enclave executable mmap()");
		जाओ err;
	पूर्ण

	encl->bin = bin;
	encl->bin_size = sb.st_size;

	बंद(fd);
	वापस true;

err:
	बंद(fd);
	वापस false;
पूर्ण

अटल bool encl_ioc_create(काष्ठा encl *encl)
अणु
	काष्ठा sgx_secs *secs = &encl->secs;
	काष्ठा sgx_enclave_create ioc;
	पूर्णांक rc;

	निश्चित(encl->encl_base != 0);

	स_रखो(secs, 0, माप(*secs));
	secs->ssa_frame_size = 1;
	secs->attributes = SGX_ATTR_MODE64BIT;
	secs->xfrm = 3;
	secs->base = encl->encl_base;
	secs->size = encl->encl_size;

	ioc.src = (अचिन्हित दीर्घ)secs;
	rc = ioctl(encl->fd, SGX_IOC_ENCLAVE_CREATE, &ioc);
	अगर (rc) अणु
		लिखो_त्रुटि("SGX_IOC_ENCLAVE_CREATE failed");
		munmap((व्योम *)secs->base, encl->encl_size);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool encl_ioc_add_pages(काष्ठा encl *encl, काष्ठा encl_segment *seg)
अणु
	काष्ठा sgx_enclave_add_pages ioc;
	काष्ठा sgx_secinfo secinfo;
	पूर्णांक rc;

	स_रखो(&secinfo, 0, माप(secinfo));
	secinfo.flags = seg->flags;

	ioc.src = (uपूर्णांक64_t)encl->src + seg->offset;
	ioc.offset = seg->offset;
	ioc.length = seg->size;
	ioc.secinfo = (अचिन्हित दीर्घ)&secinfo;
	ioc.flags = SGX_PAGE_MEASURE;

	rc = ioctl(encl->fd, SGX_IOC_ENCLAVE_ADD_PAGES, &ioc);
	अगर (rc < 0) अणु
		लिखो_त्रुटि("SGX_IOC_ENCLAVE_ADD_PAGES failed");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण



bool encl_load(स्थिर अक्षर *path, काष्ठा encl *encl)
अणु
	स्थिर अक्षर device_path[] = "/dev/sgx_enclave";
	Elf64_Phdr *phdr_tbl;
	off_t src_offset;
	Elf64_Ehdr *ehdr;
	काष्ठा stat sb;
	व्योम *ptr;
	पूर्णांक i, j;
	पूर्णांक ret;
	पूर्णांक fd = -1;

	स_रखो(encl, 0, माप(*encl));

	fd = खोलो(device_path, O_RDWR);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("Unable to open /dev/sgx_enclave");
		जाओ err;
	पूर्ण

	ret = stat(device_path, &sb);
	अगर (ret) अणु
		लिखो_त्रुटि("device file stat()");
		जाओ err;
	पूर्ण

	/*
	 * This just checks अगर the /dev file has these permission
	 * bits set.  It करोes not check that the current user is
	 * the owner or in the owning group.
	 */
	अगर (!(sb.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) अणु
		ख_लिखो(मानक_त्रुटि, "no execute permissions on device file %s\n", device_path);
		जाओ err;
	पूर्ण

	ptr = mmap(शून्य, PAGE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
	अगर (ptr == (व्योम *)-1) अणु
		लिखो_त्रुटि("mmap for read");
		जाओ err;
	पूर्ण
	munmap(ptr, PAGE_SIZE);

#घोषणा ERR_MSG \
"mmap() succeeded for PROT_READ, but failed for PROT_EXEC.\n" \
" Check that current user has execute permissions on %s and \n" \
" that /dev does not have noexec set: mount | grep \"/dev .*noexec\"\n" \
" If so, remount it executable: mount -o remount,exec /dev\n\n"

	ptr = mmap(शून्य, PAGE_SIZE, PROT_EXEC, MAP_SHARED, fd, 0);
	अगर (ptr == (व्योम *)-1) अणु
		ख_लिखो(मानक_त्रुटि, ERR_MSG, device_path);
		जाओ err;
	पूर्ण
	munmap(ptr, PAGE_SIZE);

	encl->fd = fd;

	अगर (!encl_map_bin(path, encl))
		जाओ err;

	ehdr = encl->bin;
	phdr_tbl = encl->bin + ehdr->e_phoff;

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		Elf64_Phdr *phdr = &phdr_tbl[i];

		अगर (phdr->p_type == PT_LOAD)
			encl->nr_segments++;
	पूर्ण

	encl->segment_tbl = सुस्मृति(encl->nr_segments,
				   माप(काष्ठा encl_segment));
	अगर (!encl->segment_tbl)
		जाओ err;

	क्रम (i = 0, j = 0; i < ehdr->e_phnum; i++) अणु
		Elf64_Phdr *phdr = &phdr_tbl[i];
		अचिन्हित पूर्णांक flags = phdr->p_flags;
		काष्ठा encl_segment *seg;

		अगर (phdr->p_type != PT_LOAD)
			जारी;

		seg = &encl->segment_tbl[j];

		अगर (!!(flags & ~(PF_R | PF_W | PF_X))) अणु
			ख_लिखो(मानक_त्रुटि,
				"%d has invalid segment flags 0x%02x.\n", i,
				phdr->p_flags);
			जाओ err;
		पूर्ण

		अगर (j == 0 && flags != (PF_R | PF_W)) अणु
			ख_लिखो(मानक_त्रुटि,
				"TCS has invalid segment flags 0x%02x.\n",
				phdr->p_flags);
			जाओ err;
		पूर्ण

		अगर (j == 0) अणु
			src_offset = phdr->p_offset & PAGE_MASK;

			seg->prot = PROT_READ | PROT_WRITE;
			seg->flags = SGX_PAGE_TYPE_TCS << 8;
		पूर्ण अन्यथा  अणु
			seg->prot = (phdr->p_flags & PF_R) ? PROT_READ : 0;
			seg->prot |= (phdr->p_flags & PF_W) ? PROT_WRITE : 0;
			seg->prot |= (phdr->p_flags & PF_X) ? PROT_EXEC : 0;
			seg->flags = (SGX_PAGE_TYPE_REG << 8) | seg->prot;
		पूर्ण

		seg->offset = (phdr->p_offset & PAGE_MASK) - src_offset;
		seg->size = (phdr->p_filesz + PAGE_SIZE - 1) & PAGE_MASK;

		म_लिखो("0x%016lx 0x%016lx 0x%02x\n", seg->offset, seg->size,
		       seg->prot);

		j++;
	पूर्ण

	निश्चित(j == encl->nr_segments);

	encl->src = encl->bin + src_offset;
	encl->src_size = encl->segment_tbl[j - 1].offset +
			 encl->segment_tbl[j - 1].size;

	क्रम (encl->encl_size = 4096; encl->encl_size < encl->src_size; )
		encl->encl_size <<= 1;

	वापस true;

err:
	अगर (fd != -1)
		बंद(fd);
	encl_delete(encl);
	वापस false;
पूर्ण

अटल bool encl_map_area(काष्ठा encl *encl)
अणु
	माप_प्रकार encl_size = encl->encl_size;
	व्योम *area;

	area = mmap(शून्य, encl_size * 2, PROT_NONE,
		    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	अगर (area == MAP_FAILED) अणु
		लिखो_त्रुटि("reservation mmap()");
		वापस false;
	पूर्ण

	encl->encl_base = ((uपूर्णांक64_t)area + encl_size - 1) & ~(encl_size - 1);

	munmap(area, encl->encl_base - (uपूर्णांक64_t)area);
	munmap((व्योम *)(encl->encl_base + encl_size),
	       (uपूर्णांक64_t)area + encl_size - encl->encl_base);

	वापस true;
पूर्ण

bool encl_build(काष्ठा encl *encl)
अणु
	काष्ठा sgx_enclave_init ioc;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!encl_map_area(encl))
		वापस false;

	अगर (!encl_ioc_create(encl))
		वापस false;

	/*
	 * Pages must be added beक्रमe mapping VMAs because their permissions
	 * cap the VMA permissions.
	 */
	क्रम (i = 0; i < encl->nr_segments; i++) अणु
		काष्ठा encl_segment *seg = &encl->segment_tbl[i];

		अगर (!encl_ioc_add_pages(encl, seg))
			वापस false;
	पूर्ण

	ioc.sigकाष्ठा = (uपूर्णांक64_t)&encl->sigकाष्ठा;
	ret = ioctl(encl->fd, SGX_IOC_ENCLAVE_INIT, &ioc);
	अगर (ret) अणु
		लिखो_त्रुटि("SGX_IOC_ENCLAVE_INIT failed");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
