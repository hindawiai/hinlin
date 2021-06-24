<शैली गुरु>
#समावेश "dso.h"
#समावेश "symbol.h"
#समावेश "symsrc.h"

#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <byteswap.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/zभाग.स>
#समावेश <पूर्णांकernal/lib.h>

अटल bool check_need_swap(पूर्णांक file_endian)
अणु
	स्थिर पूर्णांक data = 1;
	u8 *check = (u8 *)&data;
	पूर्णांक host_endian;

	अगर (check[0] == 1)
		host_endian = ELFDATA2LSB;
	अन्यथा
		host_endian = ELFDATA2MSB;

	वापस host_endian != file_endian;
पूर्ण

#घोषणा NOTE_ALIGN(sz) (((sz) + 3) & ~3)

#घोषणा NT_GNU_BUILD_ID	3

अटल पूर्णांक पढ़ो_build_id(व्योम *note_data, माप_प्रकार note_len, काष्ठा build_id *bid,
			 bool need_swap)
अणु
	माप_प्रकार size = माप(bid->data);
	काष्ठा अणु
		u32 n_namesz;
		u32 n_descsz;
		u32 n_type;
	पूर्ण *nhdr;
	व्योम *ptr;

	ptr = note_data;
	जबतक (ptr < (note_data + note_len)) अणु
		स्थिर अक्षर *name;
		माप_प्रकार namesz, descsz;

		nhdr = ptr;
		अगर (need_swap) अणु
			nhdr->n_namesz = bswap_32(nhdr->n_namesz);
			nhdr->n_descsz = bswap_32(nhdr->n_descsz);
			nhdr->n_type = bswap_32(nhdr->n_type);
		पूर्ण

		namesz = NOTE_ALIGN(nhdr->n_namesz);
		descsz = NOTE_ALIGN(nhdr->n_descsz);

		ptr += माप(*nhdr);
		name = ptr;
		ptr += namesz;
		अगर (nhdr->n_type == NT_GNU_BUILD_ID &&
		    nhdr->n_namesz == माप("GNU")) अणु
			अगर (स_भेद(name, "GNU", माप("GNU")) == 0) अणु
				माप_प्रकार sz = min(size, descsz);
				स_नकल(bid->data, ptr, sz);
				स_रखो(bid->data + sz, 0, size - sz);
				bid->size = sz;
				वापस 0;
			पूर्ण
		पूर्ण
		ptr += descsz;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक filename__पढ़ो_debuglink(स्थिर अक्षर *filename __maybe_unused,
			     अक्षर *debuglink __maybe_unused,
			     माप_प्रकार size __maybe_unused)
अणु
	वापस -1;
पूर्ण

/*
 * Just try PT_NOTE header otherwise fails
 */
पूर्णांक filename__पढ़ो_build_id(स्थिर अक्षर *filename, काष्ठा build_id *bid)
अणु
	खाता *fp;
	पूर्णांक ret = -1;
	bool need_swap = false;
	u8 e_ident[EI_NIDENT];
	माप_प्रकार buf_size;
	व्योम *buf;
	पूर्णांक i;

	fp = ख_खोलो(filename, "r");
	अगर (fp == शून्य)
		वापस -1;

	अगर (ख_पढ़ो(e_ident, माप(e_ident), 1, fp) != 1)
		जाओ out;

	अगर (स_भेद(e_ident, ELFMAG, SELFMAG) ||
	    e_ident[EI_VERSION] != EV_CURRENT)
		जाओ out;

	need_swap = check_need_swap(e_ident[EI_DATA]);

	/* क्रम simplicity */
	ख_जाओ(fp, 0, शुरू_से);

	अगर (e_ident[EI_CLASS] == ELFCLASS32) अणु
		Elf32_Ehdr ehdr;
		Elf32_Phdr *phdr;

		अगर (ख_पढ़ो(&ehdr, माप(ehdr), 1, fp) != 1)
			जाओ out;

		अगर (need_swap) अणु
			ehdr.e_phoff = bswap_32(ehdr.e_phoff);
			ehdr.e_phentsize = bswap_16(ehdr.e_phentsize);
			ehdr.e_phnum = bswap_16(ehdr.e_phnum);
		पूर्ण

		buf_size = ehdr.e_phentsize * ehdr.e_phnum;
		buf = दो_स्मृति(buf_size);
		अगर (buf == शून्य)
			जाओ out;

		ख_जाओ(fp, ehdr.e_phoff, शुरू_से);
		अगर (ख_पढ़ो(buf, buf_size, 1, fp) != 1)
			जाओ out_मुक्त;

		क्रम (i = 0, phdr = buf; i < ehdr.e_phnum; i++, phdr++) अणु
			व्योम *पंचांगp;
			दीर्घ offset;

			अगर (need_swap) अणु
				phdr->p_type = bswap_32(phdr->p_type);
				phdr->p_offset = bswap_32(phdr->p_offset);
				phdr->p_filesz = bswap_32(phdr->p_filesz);
			पूर्ण

			अगर (phdr->p_type != PT_NOTE)
				जारी;

			buf_size = phdr->p_filesz;
			offset = phdr->p_offset;
			पंचांगp = पुनः_स्मृति(buf, buf_size);
			अगर (पंचांगp == शून्य)
				जाओ out_मुक्त;

			buf = पंचांगp;
			ख_जाओ(fp, offset, शुरू_से);
			अगर (ख_पढ़ो(buf, buf_size, 1, fp) != 1)
				जाओ out_मुक्त;

			ret = पढ़ो_build_id(buf, buf_size, bid, need_swap);
			अगर (ret == 0)
				ret = bid->size;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		Elf64_Ehdr ehdr;
		Elf64_Phdr *phdr;

		अगर (ख_पढ़ो(&ehdr, माप(ehdr), 1, fp) != 1)
			जाओ out;

		अगर (need_swap) अणु
			ehdr.e_phoff = bswap_64(ehdr.e_phoff);
			ehdr.e_phentsize = bswap_16(ehdr.e_phentsize);
			ehdr.e_phnum = bswap_16(ehdr.e_phnum);
		पूर्ण

		buf_size = ehdr.e_phentsize * ehdr.e_phnum;
		buf = दो_स्मृति(buf_size);
		अगर (buf == शून्य)
			जाओ out;

		ख_जाओ(fp, ehdr.e_phoff, शुरू_से);
		अगर (ख_पढ़ो(buf, buf_size, 1, fp) != 1)
			जाओ out_मुक्त;

		क्रम (i = 0, phdr = buf; i < ehdr.e_phnum; i++, phdr++) अणु
			व्योम *पंचांगp;
			दीर्घ offset;

			अगर (need_swap) अणु
				phdr->p_type = bswap_32(phdr->p_type);
				phdr->p_offset = bswap_64(phdr->p_offset);
				phdr->p_filesz = bswap_64(phdr->p_filesz);
			पूर्ण

			अगर (phdr->p_type != PT_NOTE)
				जारी;

			buf_size = phdr->p_filesz;
			offset = phdr->p_offset;
			पंचांगp = पुनः_स्मृति(buf, buf_size);
			अगर (पंचांगp == शून्य)
				जाओ out_मुक्त;

			buf = पंचांगp;
			ख_जाओ(fp, offset, शुरू_से);
			अगर (ख_पढ़ो(buf, buf_size, 1, fp) != 1)
				जाओ out_मुक्त;

			ret = पढ़ो_build_id(buf, buf_size, bid, need_swap);
			अगर (ret == 0)
				ret = bid->size;
			अवरोध;
		पूर्ण
	पूर्ण
out_मुक्त:
	मुक्त(buf);
out:
	ख_बंद(fp);
	वापस ret;
पूर्ण

पूर्णांक sysfs__पढ़ो_build_id(स्थिर अक्षर *filename, काष्ठा build_id *bid)
अणु
	पूर्णांक fd;
	पूर्णांक ret = -1;
	काष्ठा stat stbuf;
	माप_प्रकार buf_size;
	व्योम *buf;

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0)
		वापस -1;

	अगर (ख_स्थिति(fd, &stbuf) < 0)
		जाओ out;

	buf_size = stbuf.st_size;
	buf = दो_स्मृति(buf_size);
	अगर (buf == शून्य)
		जाओ out;

	अगर (पढ़ो(fd, buf, buf_size) != (sमाप_प्रकार) buf_size)
		जाओ out_मुक्त;

	ret = पढ़ो_build_id(buf, buf_size, bid, false);
out_मुक्त:
	मुक्त(buf);
out:
	बंद(fd);
	वापस ret;
पूर्ण

पूर्णांक symsrc__init(काष्ठा symsrc *ss, काष्ठा dso *dso, स्थिर अक्षर *name,
	         क्रमागत dso_binary_type type)
अणु
	पूर्णांक fd = खोलो(name, O_RDONLY);
	अगर (fd < 0)
		जाओ out_त्रुटि_सं;

	ss->name = strdup(name);
	अगर (!ss->name)
		जाओ out_बंद;

	ss->fd = fd;
	ss->type = type;

	वापस 0;
out_बंद:
	बंद(fd);
out_त्रुटि_सं:
	dso->load_त्रुटि_सं = त्रुटि_सं;
	वापस -1;
पूर्ण

bool symsrc__possibly_runसमय(काष्ठा symsrc *ss __maybe_unused)
अणु
	/* Assume all sym sources could be a runसमय image. */
	वापस true;
पूर्ण

bool symsrc__has_symtab(काष्ठा symsrc *ss __maybe_unused)
अणु
	वापस false;
पूर्ण

व्योम symsrc__destroy(काष्ठा symsrc *ss)
अणु
	zमुक्त(&ss->name);
	बंद(ss->fd);
पूर्ण

पूर्णांक dso__synthesize_plt_symbols(काष्ठा dso *dso __maybe_unused,
				काष्ठा symsrc *ss __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक fd__is_64_bit(पूर्णांक fd)
अणु
	u8 e_ident[EI_NIDENT];

	अगर (lseek(fd, 0, शुरू_से))
		वापस -1;

	अगर (पढ़ोn(fd, e_ident, माप(e_ident)) != माप(e_ident))
		वापस -1;

	अगर (स_भेद(e_ident, ELFMAG, SELFMAG) ||
	    e_ident[EI_VERSION] != EV_CURRENT)
		वापस -1;

	वापस e_ident[EI_CLASS] == ELFCLASS64;
पूर्ण

क्रमागत dso_type dso__type_fd(पूर्णांक fd)
अणु
	Elf64_Ehdr ehdr;
	पूर्णांक ret;

	ret = fd__is_64_bit(fd);
	अगर (ret < 0)
		वापस DSO__TYPE_UNKNOWN;

	अगर (ret)
		वापस DSO__TYPE_64BIT;

	अगर (पढ़ोn(fd, &ehdr, माप(ehdr)) != माप(ehdr))
		वापस DSO__TYPE_UNKNOWN;

	अगर (ehdr.e_machine == EM_X86_64)
		वापस DSO__TYPE_X32BIT;

	वापस DSO__TYPE_32BIT;
पूर्ण

पूर्णांक dso__load_sym(काष्ठा dso *dso, काष्ठा map *map __maybe_unused,
		  काष्ठा symsrc *ss,
		  काष्ठा symsrc *runसमय_ss __maybe_unused,
		  पूर्णांक kmodule __maybe_unused)
अणु
	काष्ठा build_id bid;
	पूर्णांक ret;

	ret = fd__is_64_bit(ss->fd);
	अगर (ret >= 0)
		dso->is_64_bit = ret;

	अगर (filename__पढ़ो_build_id(ss->name, &bid) > 0)
		dso__set_build_id(dso, &bid);
	वापस 0;
पूर्ण

पूर्णांक file__पढ़ो_maps(पूर्णांक fd __maybe_unused, bool exe __maybe_unused,
		    mapfn_t mapfn __maybe_unused, व्योम *data __maybe_unused,
		    bool *is_64_bit __maybe_unused)
अणु
	वापस -1;
पूर्ण

पूर्णांक kcore_extract__create(काष्ठा kcore_extract *kce __maybe_unused)
अणु
	वापस -1;
पूर्ण

व्योम kcore_extract__delete(काष्ठा kcore_extract *kce __maybe_unused)
अणु
पूर्ण

पूर्णांक kcore_copy(स्थिर अक्षर *from_dir __maybe_unused,
	       स्थिर अक्षर *to_dir __maybe_unused)
अणु
	वापस -1;
पूर्ण

व्योम symbol__elf_init(व्योम)
अणु
पूर्ण

अक्षर *dso__demangle_sym(काष्ठा dso *dso __maybe_unused,
			पूर्णांक kmodule __maybe_unused,
			स्थिर अक्षर *elf_name __maybe_unused)
अणु
	वापस शून्य;
पूर्ण
