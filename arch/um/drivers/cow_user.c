<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Jeff Dike (jdike@अणुlinux.पूर्णांकel,addtoitपूर्ण.com)
 */

/*
 * _XOPEN_SOURCE is needed क्रम pपढ़ो, but we define _GNU_SOURCE, which defines
 * that.
 */
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <arpa/inet.h>
#समावेश <endian.h>
#समावेश "cow.h"
#समावेश "cow_sys.h"

#घोषणा PATH_LEN_V1 256

/* अचिन्हित समय_प्रकार works until year 2106 */
प्रकार __u32 समय32_t;

काष्ठा cow_header_v1 अणु
	__s32 magic;
	__s32 version;
	अक्षर backing_file[PATH_LEN_V1];
	समय32_t mसमय;
	__u64 size;
	__s32 sectorsize;
पूर्ण __attribute__((packed));

/*
 * Define PATH_LEN_V3 as the usual value of MAXPATHLEN, just hard-code it in
 * हाल other प्रणालीs have dअगरferent values क्रम MAXPATHLEN.
 *
 * The same must hold क्रम V2 - we want file क्रमmat compatibility, not anything
 * अन्यथा.
 */
#घोषणा PATH_LEN_V3 4096
#घोषणा PATH_LEN_V2 PATH_LEN_V3

काष्ठा cow_header_v2 अणु
	__u32 magic;
	__u32 version;
	अक्षर backing_file[PATH_LEN_V2];
	समय32_t mसमय;
	__u64 size;
	__s32 sectorsize;
पूर्ण __attribute__((packed));

/*
 * Changes from V2 -
 *	PATH_LEN_V3 as described above
 *	Explicitly specअगरy field bit lengths क्रम प्रणालीs with dअगरferent
 *		lengths क्रम the usual C types.  Not sure whether अक्षर or
 *		समय_प्रकार should be changed, this can be changed later without
 *		अवरोधing compatibility
 *	Add alignment field so that dअगरferent alignments can be used क्रम the
 *		biपंचांगap and data
 * 	Add cow_क्रमmat field to allow क्रम the possibility of dअगरferent ways
 *		of specअगरying the COW blocks.  For now, the only value is 0,
 * 		क्रम the traditional COW biपंचांगap.
 *	Move the backing_file field to the end of the header.  This allows
 *		क्रम the possibility of expanding it पूर्णांकo the padding required
 *		by the biपंचांगap alignment.
 * 	The biपंचांगap and data portions of the file will be aligned as specअगरied
 * 		by the alignment field.  This is to allow COW files to be
 *		put on devices with restrictions on access alignments, such as
 *		/dev/raw, with a 512 byte alignment restriction.  This also
 *		allows the data to be more aligned more strictly than on
 *		sector boundaries.  This is needed क्रम ubd-mmap, which needs
 *		the data to be page aligned.
 *	Fixed (finally!) the rounding bug
 */

/*
 * Until Dec2005, __attribute__((packed)) was left out from the below
 * definition, leading on 64-bit प्रणालीs to 4 bytes of padding after mसमय, to
 * align size to 8-byte alignment.  This shअगरted all fields above (no padding
 * was present on 32-bit, no other padding was added).
 *
 * However, this _can be detected_: it means that cow_क्रमmat (always 0 until
 * now) is shअगरted onto the first 4 bytes of backing_file, where it is otherwise
 * impossible to find 4 zeros. -bb */

काष्ठा cow_header_v3 अणु
	__u32 magic;
	__u32 version;
	__u32 mसमय;
	__u64 size;
	__u32 sectorsize;
	__u32 alignment;
	__u32 cow_क्रमmat;
	अक्षर backing_file[PATH_LEN_V3];
पूर्ण __attribute__((packed));

/* This is the broken layout used by some 64-bit binaries. */
काष्ठा cow_header_v3_broken अणु
	__u32 magic;
	__u32 version;
	__s64 mसमय;
	__u64 size;
	__u32 sectorsize;
	__u32 alignment;
	__u32 cow_क्रमmat;
	अक्षर backing_file[PATH_LEN_V3];
पूर्ण;

/* COW क्रमmat definitions - क्रम now, we have only the usual COW biपंचांगap */
#घोषणा COW_BITMAP 0

जोड़ cow_header अणु
	काष्ठा cow_header_v1 v1;
	काष्ठा cow_header_v2 v2;
	काष्ठा cow_header_v3 v3;
	काष्ठा cow_header_v3_broken v3_b;
पूर्ण;

#घोषणा COW_MAGIC 0x4f4f4f4d  /* MOOO */
#घोषणा COW_VERSION 3

#घोषणा DIV_ROUND(x, len) (((x) + (len) - 1) / (len))
#घोषणा ROUND_UP(x, align) DIV_ROUND(x, align) * (align)

व्योम cow_sizes(पूर्णांक version, __u64 size, पूर्णांक sectorsize, पूर्णांक align,
	       पूर्णांक biपंचांगap_offset, अचिन्हित दीर्घ *biपंचांगap_len_out,
	       पूर्णांक *data_offset_out)
अणु
	अगर (version < 3) अणु
		*biपंचांगap_len_out = (size + sectorsize - 1) / (8 * sectorsize);

		*data_offset_out = biपंचांगap_offset + *biपंचांगap_len_out;
		*data_offset_out = (*data_offset_out + sectorsize - 1) /
			sectorsize;
		*data_offset_out *= sectorsize;
	पूर्ण
	अन्यथा अणु
		*biपंचांगap_len_out = DIV_ROUND(size, sectorsize);
		*biपंचांगap_len_out = DIV_ROUND(*biपंचांगap_len_out, 8);

		*data_offset_out = biपंचांगap_offset + *biपंचांगap_len_out;
		*data_offset_out = ROUND_UP(*data_offset_out, align);
	पूर्ण
पूर्ण

अटल पूर्णांक असलolutize(अक्षर *to, पूर्णांक size, अक्षर *from)
अणु
	अक्षर save_cwd[256], *slash;
	पूर्णांक reमुख्यing;

	अगर (अ_लोwd(save_cwd, माप(save_cwd)) == शून्य) अणु
		cow_म_लिखो("absolutize : unable to get cwd - errno = %d\n",
			   त्रुटि_सं);
		वापस -1;
	पूर्ण
	slash = म_खोजप(from, '/');
	अगर (slash != शून्य) अणु
		*slash = '\0';
		अगर (स_बदलो(from)) अणु
			*slash = '/';
			cow_म_लिखो("absolutize : Can't cd to '%s' - "
				   "errno = %d\n", from, त्रुटि_सं);
			वापस -1;
		पूर्ण
		*slash = '/';
		अगर (अ_लोwd(to, size) == शून्य) अणु
			cow_म_लिखो("absolutize : unable to get cwd of '%s' - "
			       "errno = %d\n", from, त्रुटि_सं);
			वापस -1;
		पूर्ण
		reमुख्यing = size - म_माप(to);
		अगर (म_माप(slash) + 1 > reमुख्यing) अणु
			cow_म_लिखो("absolutize : unable to fit '%s' into %d "
			       "chars\n", from, size);
			वापस -1;
		पूर्ण
		म_जोड़ो(to, slash);
	पूर्ण
	अन्यथा अणु
		अगर (म_माप(save_cwd) + 1 + म_माप(from) + 1 > size) अणु
			cow_म_लिखो("absolutize : unable to fit '%s' into %d "
			       "chars\n", from, size);
			वापस -1;
		पूर्ण
		म_नकल(to, save_cwd);
		म_जोड़ो(to, "/");
		म_जोड़ो(to, from);
	पूर्ण
	अगर (स_बदलो(save_cwd)) अणु
		cow_म_लिखो("absolutize : Can't cd to '%s' - "
			   "errno = %d\n", save_cwd, त्रुटि_सं);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ग_लिखो_cow_header(अक्षर *cow_file, पूर्णांक fd, अक्षर *backing_file,
		     पूर्णांक sectorsize, पूर्णांक alignment, अचिन्हित दीर्घ दीर्घ *size)
अणु
	काष्ठा cow_header_v3 *header;
	दीर्घ दीर्घ modसमय;
	पूर्णांक err;

	err = cow_seek_file(fd, 0);
	अगर (err < 0) अणु
		cow_म_लिखो("write_cow_header - lseek failed, err = %d\n", -err);
		जाओ out;
	पूर्ण

	err = -ENOMEM;
	header = cow_दो_स्मृति(माप(*header));
	अगर (header == शून्य) अणु
		cow_म_लिखो("write_cow_header - failed to allocate COW V3 "
			   "header\n");
		जाओ out;
	पूर्ण
	header->magic = htobe32(COW_MAGIC);
	header->version = htobe32(COW_VERSION);

	err = -EINVAL;
	अगर (म_माप(backing_file) > माप(header->backing_file) - 1) अणु
		/* Below, %zd is क्रम a माप_प्रकार value */
		cow_म_लिखो("Backing file name \"%s\" is too long - names are "
			   "limited to %zd characters\n", backing_file,
			   माप(header->backing_file) - 1);
		जाओ out_मुक्त;
	पूर्ण

	अगर (असलolutize(header->backing_file, माप(header->backing_file),
		      backing_file))
		जाओ out_मुक्त;

	err = os_file_modसमय(header->backing_file, &modसमय);
	अगर (err < 0) अणु
		cow_म_लिखो("write_cow_header - backing file '%s' mtime "
			   "request failed, err = %d\n", header->backing_file,
			   -err);
		जाओ out_मुक्त;
	पूर्ण

	err = cow_file_size(header->backing_file, size);
	अगर (err < 0) अणु
		cow_म_लिखो("write_cow_header - couldn't get size of "
			   "backing file '%s', err = %d\n",
			   header->backing_file, -err);
		जाओ out_मुक्त;
	पूर्ण

	header->mसमय = htobe32(modसमय);
	header->size = htobe64(*size);
	header->sectorsize = htobe32(sectorsize);
	header->alignment = htobe32(alignment);
	header->cow_क्रमmat = COW_BITMAP;

	err = cow_ग_लिखो_file(fd, header, माप(*header));
	अगर (err != माप(*header)) अणु
		cow_म_लिखो("write_cow_header - write of header to "
			   "new COW file '%s' failed, err = %d\n", cow_file,
			   -err);
		जाओ out_मुक्त;
	पूर्ण
	err = 0;
 out_मुक्त:
	cow_मुक्त(header);
 out:
	वापस err;
पूर्ण

पूर्णांक file_पढ़ोer(__u64 offset, अक्षर *buf, पूर्णांक len, व्योम *arg)
अणु
	पूर्णांक fd = *((पूर्णांक *) arg);

	वापस pपढ़ो(fd, buf, len, offset);
पूर्ण

/* XXX Need to sanity-check the values पढ़ो from the header */

पूर्णांक पढ़ो_cow_header(पूर्णांक (*पढ़ोer)(__u64, अक्षर *, पूर्णांक, व्योम *), व्योम *arg,
		    __u32 *version_out, अक्षर **backing_file_out,
		    दीर्घ दीर्घ *mसमय_out, अचिन्हित दीर्घ दीर्घ *size_out,
		    पूर्णांक *sectorsize_out, __u32 *align_out,
		    पूर्णांक *biपंचांगap_offset_out)
अणु
	जोड़ cow_header *header;
	अक्षर *file;
	पूर्णांक err, n;
	अचिन्हित दीर्घ version, magic;

	header = cow_दो_स्मृति(माप(*header));
	अगर (header == शून्य) अणु
	        cow_म_लिखो("read_cow_header - Failed to allocate header\n");
		वापस -ENOMEM;
	पूर्ण
	err = -EINVAL;
	n = (*पढ़ोer)(0, (अक्षर *) header, माप(*header), arg);
	अगर (n < दुरत्व(typeof(header->v1), backing_file)) अणु
		cow_म_लिखो("read_cow_header - short header\n");
		जाओ out;
	पूर्ण

	magic = header->v1.magic;
	अगर (magic == COW_MAGIC)
		version = header->v1.version;
	अन्यथा अगर (magic == be32toh(COW_MAGIC))
		version = be32toh(header->v1.version);
	/* No error prपूर्णांकed because the non-COW हाल comes through here */
	अन्यथा जाओ out;

	*version_out = version;

	अगर (version == 1) अणु
		अगर (n < माप(header->v1)) अणु
			cow_म_लिखो("read_cow_header - failed to read V1 "
				   "header\n");
			जाओ out;
		पूर्ण
		*mसमय_out = header->v1.mसमय;
		*size_out = header->v1.size;
		*sectorsize_out = header->v1.sectorsize;
		*biपंचांगap_offset_out = माप(header->v1);
		*align_out = *sectorsize_out;
		file = header->v1.backing_file;
	पूर्ण
	अन्यथा अगर (version == 2) अणु
		अगर (n < माप(header->v2)) अणु
			cow_म_लिखो("read_cow_header - failed to read V2 "
				   "header\n");
			जाओ out;
		पूर्ण
		*mसमय_out = be32toh(header->v2.mसमय);
		*size_out = be64toh(header->v2.size);
		*sectorsize_out = be32toh(header->v2.sectorsize);
		*biपंचांगap_offset_out = माप(header->v2);
		*align_out = *sectorsize_out;
		file = header->v2.backing_file;
	पूर्ण
	/* This is very subtle - see above at जोड़ cow_header definition */
	अन्यथा अगर (version == 3 && (*((पूर्णांक*)header->v3.backing_file) != 0)) अणु
		अगर (n < माप(header->v3)) अणु
			cow_म_लिखो("read_cow_header - failed to read V3 "
				   "header\n");
			जाओ out;
		पूर्ण
		*mसमय_out = be32toh(header->v3.mसमय);
		*size_out = be64toh(header->v3.size);
		*sectorsize_out = be32toh(header->v3.sectorsize);
		*align_out = be32toh(header->v3.alignment);
		अगर (*align_out == 0) अणु
			cow_म_लिखो("read_cow_header - invalid COW header, "
				   "align == 0\n");
		पूर्ण
		*biपंचांगap_offset_out = ROUND_UP(माप(header->v3), *align_out);
		file = header->v3.backing_file;
	पूर्ण
	अन्यथा अगर (version == 3) अणु
		cow_म_लिखो("read_cow_header - broken V3 file with"
			   " 64-bit layout - recovering content.\n");

		अगर (n < माप(header->v3_b)) अणु
			cow_म_लिखो("read_cow_header - failed to read V3 "
				   "header\n");
			जाओ out;
		पूर्ण

		/*
		 * this was used until Dec2005 - 64bits are needed to represent
		 * 2106+. I.e. we can safely करो this truncating cast.
		 *
		 * Additionally, we must use be32toh() instead of be64toh(), since
		 * the program used to use the क्रमmer (tested - I got mसमय
		 * mismatch "0 vs whatever").
		 *
		 * Ever heard about bug-to-bug-compatibility ? ;-) */
		*mसमय_out = (समय32_t) be32toh(header->v3_b.mसमय);

		*size_out = be64toh(header->v3_b.size);
		*sectorsize_out = be32toh(header->v3_b.sectorsize);
		*align_out = be32toh(header->v3_b.alignment);
		अगर (*align_out == 0) अणु
			cow_म_लिखो("read_cow_header - invalid COW header, "
				   "align == 0\n");
		पूर्ण
		*biपंचांगap_offset_out = ROUND_UP(माप(header->v3_b), *align_out);
		file = header->v3_b.backing_file;
	पूर्ण
	अन्यथा अणु
		cow_म_लिखो("read_cow_header - invalid COW version\n");
		जाओ out;
	पूर्ण
	err = -ENOMEM;
	*backing_file_out = cow_strdup(file);
	अगर (*backing_file_out == शून्य) अणु
		cow_म_लिखो("read_cow_header - failed to allocate backing "
			   "file\n");
		जाओ out;
	पूर्ण
	err = 0;
 out:
	cow_मुक्त(header);
	वापस err;
पूर्ण

पूर्णांक init_cow_file(पूर्णांक fd, अक्षर *cow_file, अक्षर *backing_file, पूर्णांक sectorsize,
		  पूर्णांक alignment, पूर्णांक *biपंचांगap_offset_out,
		  अचिन्हित दीर्घ *biपंचांगap_len_out, पूर्णांक *data_offset_out)
अणु
	अचिन्हित दीर्घ दीर्घ size, offset;
	अक्षर zero = 0;
	पूर्णांक err;

	err = ग_लिखो_cow_header(cow_file, fd, backing_file, sectorsize,
			       alignment, &size);
	अगर (err)
		जाओ out;

	*biपंचांगap_offset_out = ROUND_UP(माप(काष्ठा cow_header_v3), alignment);
	cow_sizes(COW_VERSION, size, sectorsize, alignment, *biपंचांगap_offset_out,
		  biपंचांगap_len_out, data_offset_out);

	offset = *data_offset_out + size - माप(zero);
	err = cow_seek_file(fd, offset);
	अगर (err < 0) अणु
		cow_म_लिखो("cow bitmap lseek failed : err = %d\n", -err);
		जाओ out;
	पूर्ण

	/*
	 * करोes not really matter how much we ग_लिखो it is just to set खातापूर्ण
	 * this also sets the entire COW biपंचांगap
	 * to zero without having to allocate it
	 */
	err = cow_ग_लिखो_file(fd, &zero, माप(zero));
	अगर (err != माप(zero)) अणु
		cow_म_लिखो("Write of bitmap to new COW file '%s' failed, "
			   "err = %d\n", cow_file, -err);
		अगर (err >= 0)
			err = -EINVAL;
		जाओ out;
	पूर्ण

	वापस 0;
 out:
	वापस err;
पूर्ण
