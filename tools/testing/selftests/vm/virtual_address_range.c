<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017, Anshuman Khandual, IBM Corp.
 *
 * Works on architectures which support 128TB भव
 * address range and beyond.
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/mman.h>
#समावेश <sys/समय.स>

/*
 * Maximum address range mapped with a single mmap()
 * call is little bit more than 16GB. Hence 16GB is
 * chosen as the single chunk size क्रम address space
 * mapping.
 */
#घोषणा MAP_CHUNK_SIZE   17179869184UL /* 16GB */

/*
 * Address space till 128TB is mapped without any hपूर्णांक
 * and is enabled by शेष. Address space beyond 128TB
 * till 512TB is obtained by passing hपूर्णांक address as the
 * first argument पूर्णांकo mmap() प्रणाली call.
 *
 * The process heap address space is भागided पूर्णांकo two
 * dअगरferent areas one below 128TB and one above 128TB
 * till it reaches 512TB. One with size 128TB and the
 * other being 384TB.
 *
 * On Arm64 the address space is 256TB and no high mappings
 * are supported so far.
 */

#घोषणा NR_CHUNKS_128TB   8192UL /* Number of 16GB chunks क्रम 128TB */
#घोषणा NR_CHUNKS_256TB   (NR_CHUNKS_128TB * 2UL)
#घोषणा NR_CHUNKS_384TB   (NR_CHUNKS_128TB * 3UL)

#घोषणा ADDR_MARK_128TB  (1UL << 47) /* First address beyond 128TB */
#घोषणा ADDR_MARK_256TB  (1UL << 48) /* First address beyond 256TB */

#अगर_घोषित __aarch64__
#घोषणा HIGH_ADDR_MARK  ADDR_MARK_256TB
#घोषणा HIGH_ADDR_SHIFT 49
#घोषणा NR_CHUNKS_LOW   NR_CHUNKS_256TB
#घोषणा NR_CHUNKS_HIGH  0
#अन्यथा
#घोषणा HIGH_ADDR_MARK  ADDR_MARK_128TB
#घोषणा HIGH_ADDR_SHIFT 48
#घोषणा NR_CHUNKS_LOW   NR_CHUNKS_128TB
#घोषणा NR_CHUNKS_HIGH  NR_CHUNKS_384TB
#पूर्ण_अगर

अटल अक्षर *hind_addr(व्योम)
अणु
	पूर्णांक bits = HIGH_ADDR_SHIFT + अक्रम() % (63 - HIGH_ADDR_SHIFT);

	वापस (अक्षर *) (1UL << bits);
पूर्ण

अटल पूर्णांक validate_addr(अक्षर *ptr, पूर्णांक high_addr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) ptr;

	अगर (high_addr) अणु
		अगर (addr < HIGH_ADDR_MARK) अणु
			म_लिखो("Bad address %lx\n", addr);
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (addr > HIGH_ADDR_MARK) अणु
		म_लिखो("Bad address %lx\n", addr);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक validate_lower_address_hपूर्णांक(व्योम)
अणु
	अक्षर *ptr;

	ptr = mmap((व्योम *) (1UL << 45), MAP_CHUNK_SIZE, PROT_READ |
			PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	अगर (ptr == MAP_FAILED)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर *ptr[NR_CHUNKS_LOW];
	अक्षर *hptr[NR_CHUNKS_HIGH];
	अक्षर *hपूर्णांक;
	अचिन्हित दीर्घ i, lchunks, hchunks;

	क्रम (i = 0; i < NR_CHUNKS_LOW; i++) अणु
		ptr[i] = mmap(शून्य, MAP_CHUNK_SIZE, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		अगर (ptr[i] == MAP_FAILED) अणु
			अगर (validate_lower_address_hपूर्णांक())
				वापस 1;
			अवरोध;
		पूर्ण

		अगर (validate_addr(ptr[i], 0))
			वापस 1;
	पूर्ण
	lchunks = i;

	क्रम (i = 0; i < NR_CHUNKS_HIGH; i++) अणु
		hपूर्णांक = hind_addr();
		hptr[i] = mmap(hपूर्णांक, MAP_CHUNK_SIZE, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		अगर (hptr[i] == MAP_FAILED)
			अवरोध;

		अगर (validate_addr(hptr[i], 1))
			वापस 1;
	पूर्ण
	hchunks = i;

	क्रम (i = 0; i < lchunks; i++)
		munmap(ptr[i], MAP_CHUNK_SIZE);

	क्रम (i = 0; i < hchunks; i++)
		munmap(hptr[i], MAP_CHUNK_SIZE);

	वापस 0;
पूर्ण
